/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_KMSDRM

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_kmsdrmvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_kmsdrmmouse.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_kmsdrmdyn.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/default_cursor.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_pixels_c.h"

// !!! FIXME: atomic cursors are broken right now.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ USE_ATOMIC_CURSOR 0

ਸਥਿਰ SDL_Cursor *KMSDRM_CreateDefaultCursor(ਖਾਲੀ);
ਸਥਿਰ SDL_Cursor *KMSDRM_CreateCursor(SDL_Surface *surface, ਪੂਰਨ hot_x, ਪੂਰਨ hot_y);
ਸਥਿਰ bool KMSDRM_ShowCursor(SDL_Cursor *cursor);
ਸਥਿਰ bool KMSDRM_MoveCursor(SDL_Cursor *cursor);
ਸਥਿਰ ਖਾਲੀ KMSDRM_FreeCursor(SDL_Cursor *cursor);

/**************************************************************************************/
// BEFORE CODING ANYTHING MOUSE/CURSOR RELATED, REMEMBER THIS.
// How does SDL manage cursors internally? First, mouse != cursor. The mouse can have
// many cursors in mouse->cursors.
// -SDL tells us to create a cursor with KMSDRM_CreateCursor(). It can create many
// cursors with this, not only one.
// -SDL stores those cursors in a cursors array, in mouse->cursors.
// -Whenever it wants (or the programmer wants) takes a cursor from that array
// and shows it on screen with KMSDRM_ShowCursor().
// KMSDRM_ShowCursor() simply shows or hides the cursor it receives: it does NOT
// mind if it's mouse->cur_cursor, etc.
// -If KMSDRM_ShowCursor() returns successfully, that cursor becomes
// mouse->cur_cursor and mouse->cursor_visible is 1.
/**************************************************************************************/

ਸਥਿਰ SDL_Cursor *KMSDRM_CreateDefaultCursor(ਖਾਲੀ)
{
    ਵਾਪਸ SDL_CreateCursor(default_cdata, default_cmask, DEFAULT_CWIDTH, DEFAULT_CHEIGHT, DEFAULT_CHOTX, DEFAULT_CHOTY);
}

/* Given a display's internal, destroy the cursor BO for it.
   To be called from KMSDRM_DestroyWindow(), as that's where we
   destroy the internal for the window's display. */
ਖਾਲੀ KMSDRM_DestroyCursorBO(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_ਅੰਕੜੇ *dispdata = display->ਅੰਦਰੂਨੀ;

    // Destroy the curso GBM BO.
    ਜੇ (dispdata->cursor_bo) {
        SDL_Video_ਅੰਕੜੇ *viddata = (SDL_Video_ਅੰਕੜੇ *) _this->ਅੰਦਰੂਨੀ;
        ਜੇ (USE_ATOMIC_CURSOR && viddata->is_atomic) {
            ਜੇ (dispdata->cursor_plane) {
                // Unset the the cursor BO from the cursor plane.
                KMSDRM_PlaneInfo info;
                SDL_zero(info);
                info.plane = dispdata->cursor_plane;
                drm_atomic_ਸੈੱਟ_plane_props(dispdata, &info);
                // Wait until the cursor is unset from the cursor plane before destroying it's BO.
                ਜੇ (drm_atomic_commit(_this, dispdata, true, false)) {
                    SDL_ਸੈੱਟ_Error("Failed atomic commit in KMSDRM_DenitMouse.");
                }
                // Free the cursor plane, on which the cursor was being shown.
                free_plane(&dispdata->cursor_plane);
            }
        }

        KMSDRM_gbm_bo_destroy(dispdata->cursor_bo);
        dispdata->cursor_bo = ਨਿਰਾ;
        dispdata->cursor_bo_drm_fd = -1;
    }
}

/* Given a display's internal, create the cursor BO for it.
   To be called from KMSDRM_CreateWindow(), as that's where we
   build a window and assign a display to it. */
bool KMSDRM_CreateCursorBO(SDL_VideoDisplay *display)
{
    SDL_VideoDevice *dev = SDL_GetVideoDevice();
    SDL_Video_ਅੰਕੜੇ *viddata = dev->ਅੰਦਰੂਨੀ;
    SDL_Display_ਅੰਕੜੇ *dispdata = display->ਅੰਦਰੂਨੀ;

    ਜੇ (USE_ATOMIC_CURSOR && viddata->is_atomic) {
        ਤਿਆਰੀ_plane(dev, dispdata, &dispdata->cursor_plane, DRM_PLANE_TYPE_CURSOR);
    }

    ਜੇ (!KMSDRM_gbm_device_is_format_supported(viddata->gbm_dev,
                                               GBM_FORMAT_ARGB8888,
                                               GBM_BO_USE_CURSOR | GBM_BO_USE_WRITE)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Unsupported pixel format for cursor");
    }

    ਜੇ (KMSDRM_drmGetCap(viddata->drm_fd,
                         DRM_CAP_CURSOR_ਚੌੜਾਈ, &dispdata->cursor_w) ||
        KMSDRM_drmGetCap(viddata->drm_fd, DRM_CAP_CURSOR_ਉਚਾਈ,
                         &dispdata->cursor_h)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Could not get the recommended GBM cursor size");
    }

    ਜੇ (dispdata->cursor_w == 0 || dispdata->cursor_h == 0) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Could not get an usable GBM cursor size");
    }

    dispdata->cursor_bo = KMSDRM_gbm_bo_create(viddata->gbm_dev,
                                               dispdata->cursor_w, dispdata->cursor_h,
                                               GBM_FORMAT_ARGB8888, GBM_BO_USE_CURSOR | GBM_BO_USE_WRITE | GBM_BO_USE_ਰੇਖਿਕ);

    ਜੇ (!dispdata->cursor_bo) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Could not create GBM cursor BO");
    }

    dispdata->cursor_bo_drm_fd = viddata->drm_fd;
    ਵਾਪਸ true;
}

// Remove a cursor buffer from a display's DRM cursor BO.
ਸਥਿਰ bool KMSDRM_RemoveCursorFromBO(SDL_VideoDisplay *display)
{
    bool ਨਤੀਜਾ = true;

    SDL_Display_ਅੰਕੜੇ *dispdata = display->ਅੰਦਰੂਨੀ;
    SDL_VideoDevice *video_device = SDL_GetVideoDevice();
    SDL_Video_ਅੰਕੜੇ *viddata = video_device->ਅੰਦਰੂਨੀ;

    ਜੇ (USE_ATOMIC_CURSOR && viddata->is_atomic) {
        ਜੇ (dispdata->cursor_plane) {
            KMSDRM_PlaneInfo info;
            SDL_zero(info);
            info.plane = dispdata->cursor_plane;
            // The rest of the members are zeroed, so this takes away the cursor from the cursor plane.
            drm_atomic_ਸੈੱਟ_plane_props(dispdata, &info);
            ਜੇ (drm_atomic_commit(video_device, dispdata, true, false)) {
                ਨਤੀਜਾ = SDL_ਸੈੱਟ_Error("Failed atomic commit in KMSDRM_ShowCursor.");
            }
        }
    } ਨਹੀਂਤਾਂ {
        ਅਚਲ ਪੂਰਨ rc = KMSDRM_drm_ਬਹੁਲਕ_ਸੈੱਟ_Cursor(viddata->drm_fd, dispdata->crtc.crtc->crtc_id, 0, 0, 0);
        ਜੇ (rc < 0) {
            ਨਤੀਜਾ = SDL_ਸੈੱਟ_Error("drmModeSetCursor() failed: %s", strerror(-rc));
        }
    }

    ਵਾਪਸ ਨਤੀਜਾ;
}

// Dump a cursor buffer to a display's DRM cursor BO.
ਸਥਿਰ bool KMSDRM_Dump_Cursor_ਮੰਜ਼ਿਲ_BO(SDL_VideoDisplay *display, SDL_Mouse *mouse, SDL_Cursor *cursor)
{
    SDL_Display_ਅੰਕੜੇ *dispdata = display->ਅੰਦਰੂਨੀ;
    SDL_Cursor_ਅੰਕੜੇ *curdata = cursor->ਅੰਦਰੂਨੀ;
    SDL_VideoDevice *video_device = SDL_GetVideoDevice();
    SDL_Video_ਅੰਕੜੇ *viddata = video_device->ਅੰਦਰੂਨੀ;

    uint32_t bo_handle;
    size_t bo_stride;
    size_t bufsize;
    uint8_t *ready_ਬਫਰ = ਨਿਰਾ;
    uint8_t *src_ਪੰਕਤੀ;

    ਪੂਰਨ i, rc;
    bool ਨਤੀਜਾ = true;

    ਜੇ (!curdata || !dispdata->cursor_bo) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Cursor or display not initialized properly.");
    }

    /* Prepare a buffer we can dump to our GBM BO (different
       size, alpha premultiplication...) */
    bo_stride = KMSDRM_gbm_bo_get_stride(dispdata->cursor_bo);
    bufsize = bo_stride * dispdata->cursor_h;

    ready_ਬਫਰ = (uint8_t *)SDL_calloc(1, bufsize);

    ਜੇ (!ready_ਬਫਰ) {
        ਨਤੀਜਾ = false;
        ਜਾਓ cleanup;
    }

    // Copy from the cursor buffer to a buffer that we can dump to the GBM BO.
    ਲਈ (i = 0; i < curdata->h; i++) {
        src_ਪੰਕਤੀ = &((uint8_t *)curdata->ਬਫਰ_2)[i * curdata->w * 4];
        SDL_memcpy(ready_ਬਫਰ + (i * bo_stride), src_ਪੰਕਤੀ, (size_t)4 * curdata->w);
    }

    // Dump the cursor buffer to our GBM BO.
    ਜੇ (KMSDRM_gbm_bo_write(dispdata->cursor_bo, ready_ਬਫਰ, bufsize)) {
        ਨਤੀਜਾ = SDL_ਸੈੱਟ_Error("Could not write to GBM cursor BO");
        ਜਾਓ cleanup;
    }

    ਜੇ (USE_ATOMIC_CURSOR && viddata->is_atomic) {
        // Get the fb_id for the GBM BO so we can show it on the cursor plane.
        KMSDRM_FBInfo *fb = KMSDRM_FBFromBO(video_device, dispdata->cursor_bo);
        KMSDRM_PlaneInfo info;

        ਜੇ (!fb) {
            ਨਤੀਜਾ = SDL_ਸੈੱਟ_Error("Failed to get cursor FB from BO");
            ਜਾਓ cleanup;
        }

        // Show the GBM BO buffer on the cursor plane.
        SDL_zero(info);
        info.plane = dispdata->cursor_plane;
        info.crtc_id = dispdata->crtc.crtc->crtc_id;
        info.fb_id = fb->fb_id;
        info.src_w = dispdata->cursor_w;
        info.src_h = dispdata->cursor_h;
        info.crtc_x = ((int32_t) SDL_roundf(mouse->x)) - curdata->hot_x;
        info.crtc_y = ((int32_t) SDL_roundf(mouse->y)) - curdata->hot_y;
        info.crtc_w = curdata->w;
        info.crtc_h = curdata->h;
        drm_atomic_ਸੈੱਟ_plane_props(dispdata, &info);
        ਜੇ (drm_atomic_commit(video_device, dispdata, true, false)) {
            ਨਤੀਜਾ = SDL_ਸੈੱਟ_Error("Failed atomic commit in KMSDRM_ShowCursor.");
            ਜਾਓ cleanup;
        }
    } ਨਹੀਂਤਾਂ {
        // Put the GBM BO buffer on screen using the DRM interface.
        bo_handle = KMSDRM_gbm_bo_get_handle(dispdata->cursor_bo).u32;
        ਜੇ (curdata->hot_x == 0 && curdata->hot_y == 0) {
            rc = KMSDRM_drm_ਬਹੁਲਕ_ਸੈੱਟ_Cursor(viddata->drm_fd, dispdata->crtc.crtc->crtc_id, bo_handle, dispdata->cursor_w, dispdata->cursor_h);
        } ਨਹੀਂਤਾਂ {
            rc = KMSDRM_drm_ਬਹੁਲਕ_ਸੈੱਟ_Cursor2(viddata->drm_fd, dispdata->crtc.crtc->crtc_id, bo_handle, dispdata->cursor_w, dispdata->cursor_h, curdata->hot_x, curdata->hot_y);
        }
        ਜੇ (rc < 0) {
            ਨਤੀਜਾ = SDL_ਸੈੱਟ_Error("Failed to set DRM cursor: %s", strerror(-rc));
            ਜਾਓ cleanup;
        }
    }

cleanup:
    SDL_free(ready_ਬਫਰ);
    ਵਾਪਸ ਨਤੀਜਾ;
}

// This is only for freeing the SDL_cursor.
ਸਥਿਰ ਖਾਲੀ KMSDRM_FreeCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_ਅੰਕੜੇ *curdata;

    // Even if the cursor is not ours, free it.
    ਜੇ (cursor) {
        curdata = cursor->ਅੰਦਰੂਨੀ;
        // Free cursor buffer
        ਜੇ (curdata->ਬਫਰ_2) {
            SDL_free(curdata->ਬਫਰ_2);
            curdata->ਬਫਰ_2 = ਨਿਰਾ;
        }
        // Free cursor itself
        SDL_free(cursor->ਅੰਦਰੂਨੀ);
        SDL_free(cursor);
    }
}

/* This simply gets the cursor soft-buffer ready.
   We don't copy it to a GBO BO until ShowCursor() because the cusor GBM BO (living
   in dispata) is destroyed and recreated when we recreate windows, etc. */
ਸਥਿਰ SDL_Cursor *KMSDRM_CreateCursor(SDL_Surface *surface, ਪੂਰਨ hot_x, ਪੂਰਨ hot_y)
{
    SDL_Cursor_ਅੰਕੜੇ *curdata;
    SDL_Cursor *cursor, *ਨਤੀਜਾ;

    curdata = ਨਿਰਾ;
    ਨਤੀਜਾ = ਨਿਰਾ;

    cursor = (SDL_Cursor *)SDL_calloc(1, ਆਕਾਰ(*cursor));
    ਜੇ (!cursor) {
        ਜਾਓ cleanup;
    }
    curdata = (SDL_Cursor_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(*curdata));
    ਜੇ (!curdata) {
        ਜਾਓ cleanup;
    }

    // hox_x and hot_y are the coordinates of the "tip of the cursor" from it's base.
    curdata->hot_x = hot_x;
    curdata->hot_y = hot_y;
    curdata->w = surface->w;
    curdata->h = surface->h;
    curdata->ਬਫਰ_2 = ਨਿਰਾ;

    /* Configure the cursor buffer info.
       This buffer has the original size of the cursor surface we are given. */
    curdata->ਬਫਰ_pitch = surface->w;
    curdata->ਬਫਰ_ਮਾਪ = (size_t)surface->w * surface->h * 4;
    curdata->ਬਫਰ_2 = (uint32_t *)SDL_malloc(curdata->ਬਫਰ_ਮਾਪ);

    ਜੇ (!curdata->ਬਫਰ_2) {
        ਜਾਓ cleanup;
    }

    /* All code below assumes ARGB8888 format for the cursor surface,
       like other backends do. Also, the GBM BO pixels have to be
       alpha-premultiplied, but the SDL surface we receive has
       straight-alpha pixels, so we always have to convert. */
    SDL_PremultiplyAlpha(surface->w, surface->h,
                         surface->format, surface->pixels, surface->pitch,
                         SDL_PIXELFORMAT_ARGB8888, curdata->ਬਫਰ_2, surface->w * 4, true);

    cursor->ਅੰਦਰੂਨੀ = curdata;

    ਨਤੀਜਾ = cursor;

cleanup:
    ਜੇ (!ਨਤੀਜਾ) {
        ਜੇ (curdata) {
            SDL_free(curdata->ਬਫਰ_2);
            SDL_free(curdata);
        }
        SDL_free(cursor);
    }

    ਵਾਪਸ ਨਤੀਜਾ;
}

// Show the specified cursor, or hide if cursor is NULL or has no focus.
ਸਥਿਰ bool KMSDRM_ShowCursor(SDL_Cursor *cursor)
{
    SDL_VideoDisplay *display;
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ;
    SDL_Mouse *mouse = SDL_GetMouse();

    ਪੂਰਨ i;
    bool ਨਤੀਜਾ = true;

    // Get the mouse focused window, if any.
    ਖਿੜਕੀ = mouse->focus;

    ਜੇ (!ਖਿੜਕੀ || !cursor) {
        /* If no window is focused by mouse or cursor is NULL,
           since we have no window (no mouse->focus) and hence
           we have no display, we simply hide mouse on all displays.
           This happens on video quit, where we get here after
           the mouse focus has been unset, yet SDL wants to
           restore the system default cursor (makes no sense here). */
        SDL_DisplayID *displays = SDL_GetDisplays(ਨਿਰਾ);
        ਜੇ (displays) {
            // Iterate on the displays, hiding the cursor.
            ਲਈ (i = 0; i < displays[i]; i++) {
                display = SDL_GetVideoDisplay(displays[i]);
                ਨਤੀਜਾ = KMSDRM_RemoveCursorFromBO(display);
            }
            SDL_free(displays);
        }
    } ਨਹੀਂਤਾਂ {
        display = SDL_Get_Video_Display_For_ਖਿੜਕੀ(ਖਿੜਕੀ);
        ਜੇ (display) {
            ਜੇ (cursor) {
                /* Dump the cursor to the display DRM cursor BO so it becomes visible
                   on that display. */
                ਨਤੀਜਾ = KMSDRM_Dump_Cursor_ਮੰਜ਼ਿਲ_BO(display, mouse, cursor);
            } ਨਹੀਂਤਾਂ {
                // Hide the cursor on that display.
                ਨਤੀਜਾ = KMSDRM_RemoveCursorFromBO(display);
            }
        }
    }

    ਵਾਪਸ ਨਤੀਜਾ;
}

ਸਥਿਰ ਖਾਲੀ drm_atomic_movecursor(SDL_Display_ਅੰਕੜੇ *dispdata, ਅਚਲ SDL_Cursor_ਅੰਕੜੇ *curdata, uint16_t x, uint16_t y)
{
    ਜੇ (dispdata->cursor_plane) {  // We can't move a non-existing cursor, but that's ok.
        // Do we have a set of changes already in the making? If not, allocate a new one.
        ਜੇ (!dispdata->atomic_req) {
            dispdata->atomic_req = KMSDRM_drm_ਬਹੁਲਕ_Atomic_Alloc();
        }
        ਜੋੜੋ_plane_property(dispdata->atomic_req, dispdata->cursor_plane, "CRTC_X", x - curdata->hot_x);
        ਜੋੜੋ_plane_property(dispdata->atomic_req, dispdata->cursor_plane, "CRTC_Y", y - curdata->hot_y);
    }
}

ਸਥਿਰ bool KMSDRM_WarpMouseGlobal(ਦਸ਼ਮਲਵ x, ਦਸ਼ਮਲਵ y)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    ਜੇ (mouse && mouse->cur_cursor && mouse->focus) {
        SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = mouse->focus;
        SDL_Display_ਅੰਕੜੇ *dispdata = SDL_Get_Display_Driver_ਅੰਕੜੇ_For_ਖਿੜਕੀ(ਖਿੜਕੀ);

        // Update internal mouse position.
        SDL_SendMouseMotion(0, mouse->focus, SDL_GLOBAL_MOUSE_ID, false, x, y);

        // And now update the cursor graphic position on screen.
        ਜੇ (dispdata->cursor_bo) {
            SDL_VideoDevice *dev = SDL_GetVideoDevice();
            SDL_Video_ਅੰਕੜੇ *viddata = dev->ਅੰਦਰੂਨੀ;
            ਜੇ (USE_ATOMIC_CURSOR && viddata->is_atomic) {
                ਅਚਲ SDL_Cursor_ਅੰਕੜੇ *curdata = (ਅਚਲ SDL_Cursor_ਅੰਕੜੇ *) mouse->cur_cursor->ਅੰਦਰੂਨੀ;
                drm_atomic_movecursor(dispdata, curdata, (uint16_t) (ਪੂਰਨ) x, (uint16_t) (ਪੂਰਨ) y);
            } ਨਹੀਂਤਾਂ {
                ਅਚਲ ਪੂਰਨ rc = KMSDRM_drm_ਬਹੁਲਕ_Move_Cursor(dispdata->cursor_bo_drm_fd, dispdata->crtc.crtc->crtc_id, (ਪੂਰਨ)x, (ਪੂਰਨ)y);
                ਜੇ (rc < 0) {
                    ਵਾਪਸ SDL_ਸੈੱਟ_Error("drmModeMoveCursor() failed: %s", strerror(-rc));
                }
            }
        } ਨਹੀਂਤਾਂ {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("Cursor not initialized properly.");
        }
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("No mouse or current cursor.");
    }

    ਵਾਪਸ true;
}

ਸਥਿਰ bool KMSDRM_WarpMouse(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਦਸ਼ਮਲਵ x, ਦਸ਼ਮਲਵ y)
{
    // Only one global/fullscreen window is supported
    ਵਾਪਸ KMSDRM_WarpMouseGlobal(x, y);
}

ਖਾਲੀ KMSDRM_InitMouse(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Display_ਅੰਕੜੇ *dispdata = display->ਅੰਦਰੂਨੀ;

    mouse->CreateCursor = KMSDRM_CreateCursor;
    mouse->ShowCursor = KMSDRM_ShowCursor;
    mouse->MoveCursor = KMSDRM_MoveCursor;
    mouse->FreeCursor = KMSDRM_FreeCursor;
    mouse->WarpMouse = KMSDRM_WarpMouse;
    mouse->WarpMouseGlobal = KMSDRM_WarpMouseGlobal;

    /* Only create the default cursor for this display if we haven't done so before,
       we don't want several cursors to be created for the same display. */
    ਜੇ (!dispdata->default_cursor_init) {
        SDL_ਸੈੱਟ_Default_Cursor(KMSDRM_CreateDefaultCursor());
        dispdata->default_cursor_init = true;
    }
}

ਖਾਲੀ KMSDRM_QuitMouse(SDL_VideoDevice *_this)
{
    // TODO: ?
}

// This is called when a mouse motion event occurs
ਸਥਿਰ bool KMSDRM_MoveCursor(SDL_Cursor *cursor)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    /* We must NOT call SDL_SendMouseMotion() here or we will enter recursivity!
       That's why we move the cursor graphic ONLY. */
    ਜੇ (mouse && mouse->cur_cursor && mouse->focus) {
        SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = mouse->focus;
        SDL_Display_ਅੰਕੜੇ *dispdata = SDL_Get_Display_Driver_ਅੰਕੜੇ_For_ਖਿੜਕੀ(ਖਿੜਕੀ);
        SDL_VideoDevice *dev = SDL_GetVideoDevice();
        SDL_Video_ਅੰਕੜੇ *viddata = dev->ਅੰਦਰੂਨੀ;

        ਜੇ (!dispdata->cursor_bo) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("Cursor not initialized properly.");
        }

        ਜੇ (USE_ATOMIC_CURSOR && viddata->is_atomic) {
            /* !!! FIXME: Some programs expect cursor movement even while they don't do SwapWindow() calls,
               and since we ride on the atomic_commit() in SwapWindow() for cursor movement,
               cursor won't move in these situations. We could do an atomic_commit() here
               for each cursor movement request, but it cripples the movement to 30FPS,
               so a future solution is needed. SDLPoP "QUIT?" menu is an example of this
               situation. */
            ਅਚਲ SDL_Cursor_ਅੰਕੜੇ *curdata = (ਅਚਲ SDL_Cursor_ਅੰਕੜੇ *) mouse->cur_cursor->ਅੰਦਰੂਨੀ;
            drm_atomic_movecursor(dispdata, curdata, (uint16_t) (ਪੂਰਨ) mouse->x, (uint16_t) (ਪੂਰਨ) mouse->y);
        } ਨਹੀਂਤਾਂ {
            ਅਚਲ ਪੂਰਨ rc = KMSDRM_drm_ਬਹੁਲਕ_Move_Cursor(dispdata->cursor_bo_drm_fd, dispdata->crtc.crtc->crtc_id, (ਪੂਰਨ)mouse->x, (ਪੂਰਨ)mouse->y);
            ਜੇ (rc < 0) {
                ਵਾਪਸ SDL_ਸੈੱਟ_Error("drmModeMoveCursor() failed: %s", strerror(-rc));
            }
        }
    }
    ਵਾਪਸ true;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_KMSDRM
