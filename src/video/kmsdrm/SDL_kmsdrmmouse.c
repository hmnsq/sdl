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

#ضمن "SDL_internal.h"

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_KMSDRM

#ضمن "SDL_kmsdrmvideo.h"
#ضمن "SDL_kmsdrmmouse.h"
#ضمن "SDL_kmsdrmdyn.h"

#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../../events/default_cursor.h"

#ضمن "../SDL_pixels_c.h"

// !!! FIXME: atomic cursors are broken right now.
#تعریف_کرو USE_ATOMIC_CURSOR 0

ساكن SDL_Cursor *KMSDRM_CreateDefaultCursor(فراغ);
ساكن SDL_Cursor *KMSDRM_CreateCursor(SDL_Surface *surface, صحيح hot_x, صحيح hot_y);
ساكن bool KMSDRM_ShowCursor(SDL_Cursor *cursor);
ساكن bool KMSDRM_MoveCursor(SDL_Cursor *cursor);
ساكن فراغ KMSDRM_FreeCursor(SDL_Cursor *cursor);

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

ساكن SDL_Cursor *KMSDRM_CreateDefaultCursor(فراغ)
{
    أرجع SDL_CreateCursor(default_cdata, default_cmask, DEFAULT_CWIDTH, DEFAULT_CHEIGHT, DEFAULT_CHOTX, DEFAULT_CHOTY);
}

/* Given a display's internal, destroy the cursor BO for it.
   To be called from KMSDRM_DestroyWindow(), as that's where we
   destroy the internal for the window's display. */
فراغ KMSDRM_DestroyCursorBO(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_انکڑے *dispdata = display->اندرونی;

    // Destroy the curso GBM BO.
    إذا (dispdata->cursor_bo) {
        SDL_Video_انکڑے *viddata = (SDL_Video_انکڑے *) _this->اندرونی;
        إذا (USE_ATOMIC_CURSOR && viddata->is_atomic) {
            إذا (dispdata->cursor_plane) {
                // Unset the the cursor BO from the cursor plane.
                KMSDRM_PlaneInfo info;
                SDL_zero(info);
                info.plane = dispdata->cursor_plane;
                drm_atomic_سیٹ_plane_props(dispdata, &info);
                // Wait until the cursor is unset from the cursor plane before destroying it's BO.
                إذا (drm_atomic_commit(_this, dispdata, true, false)) {
                    SDL_سیٹ_Error("Failed atomic commit in KMSDRM_DenitMouse.");
                }
                // Free the cursor plane, on which the cursor was being shown.
                free_plane(&dispdata->cursor_plane);
            }
        }

        KMSDRM_gbm_bo_destroy(dispdata->cursor_bo);
        dispdata->cursor_bo = عدم;
        dispdata->cursor_bo_drm_fd = -1;
    }
}

/* Given a display's internal, create the cursor BO for it.
   To be called from KMSDRM_CreateWindow(), as that's where we
   build a window and assign a display to it. */
bool KMSDRM_CreateCursorBO(SDL_VideoDisplay *display)
{
    SDL_VideoDevice *dev = SDL_GetVideoDevice();
    SDL_Video_انکڑے *viddata = dev->اندرونی;
    SDL_Display_انکڑے *dispdata = display->اندرونی;

    إذا (USE_ATOMIC_CURSOR && viddata->is_atomic) {
        تیاری_plane(dev, dispdata, &dispdata->cursor_plane, DRM_PLANE_TYPE_CURSOR);
    }

    إذا (!KMSDRM_gbm_device_is_format_supported(viddata->gbm_dev,
                                               GBM_FORMAT_ARGB8888,
                                               GBM_BO_USE_CURSOR | GBM_BO_USE_WRITE)) {
        أرجع SDL_سیٹ_Error("Unsupported pixel format for cursor");
    }

    إذا (KMSDRM_drmGetCap(viddata->drm_fd,
                         DRM_CAP_CURSOR_چوڑائی, &dispdata->cursor_w) ||
        KMSDRM_drmGetCap(viddata->drm_fd, DRM_CAP_CURSOR_اچائی,
                         &dispdata->cursor_h)) {
        أرجع SDL_سیٹ_Error("Could not get the recommended GBM cursor size");
    }

    إذا (dispdata->cursor_w == 0 || dispdata->cursor_h == 0) {
        أرجع SDL_سیٹ_Error("Could not get an usable GBM cursor size");
    }

    dispdata->cursor_bo = KMSDRM_gbm_bo_create(viddata->gbm_dev,
                                               dispdata->cursor_w, dispdata->cursor_h,
                                               GBM_FORMAT_ARGB8888, GBM_BO_USE_CURSOR | GBM_BO_USE_WRITE | GBM_BO_USE_خطی);

    إذا (!dispdata->cursor_bo) {
        أرجع SDL_سیٹ_Error("Could not create GBM cursor BO");
    }

    dispdata->cursor_bo_drm_fd = viddata->drm_fd;
    أرجع true;
}

// Remove a cursor buffer from a display's DRM cursor BO.
ساكن bool KMSDRM_RemoveCursorFromBO(SDL_VideoDisplay *display)
{
    bool نتیجہ = true;

    SDL_Display_انکڑے *dispdata = display->اندرونی;
    SDL_VideoDevice *video_device = SDL_GetVideoDevice();
    SDL_Video_انکڑے *viddata = video_device->اندرونی;

    إذا (USE_ATOMIC_CURSOR && viddata->is_atomic) {
        إذا (dispdata->cursor_plane) {
            KMSDRM_PlaneInfo info;
            SDL_zero(info);
            info.plane = dispdata->cursor_plane;
            // The rest of the members are zeroed, so this takes away the cursor from the cursor plane.
            drm_atomic_سیٹ_plane_props(dispdata, &info);
            إذا (drm_atomic_commit(video_device, dispdata, true, false)) {
                نتیجہ = SDL_سیٹ_Error("Failed atomic commit in KMSDRM_ShowCursor.");
            }
        }
    } وإلا {
        ثابت صحيح rc = KMSDRM_drm_منوال_سیٹ_Cursor(viddata->drm_fd, dispdata->crtc.crtc->crtc_id, 0, 0, 0);
        إذا (rc < 0) {
            نتیجہ = SDL_سیٹ_Error("drmModeSetCursor() failed: %s", strerror(-rc));
        }
    }

    أرجع نتیجہ;
}

// Dump a cursor buffer to a display's DRM cursor BO.
ساكن bool KMSDRM_Dump_Cursor_منزل_BO(SDL_VideoDisplay *display, SDL_Mouse *mouse, SDL_Cursor *cursor)
{
    SDL_Display_انکڑے *dispdata = display->اندرونی;
    SDL_Cursor_انکڑے *curdata = cursor->اندرونی;
    SDL_VideoDevice *video_device = SDL_GetVideoDevice();
    SDL_Video_انکڑے *viddata = video_device->اندرونی;

    uint32_t bo_handle;
    size_t bo_stride;
    size_t bufsize;
    uint8_t *ready_بفر = عدم;
    uint8_t *src_صف;

    صحيح i, rc;
    bool نتیجہ = true;

    إذا (!curdata || !dispdata->cursor_bo) {
        أرجع SDL_سیٹ_Error("Cursor or display not initialized properly.");
    }

    /* Prepare a buffer we can dump to our GBM BO (different
       size, alpha premultiplication...) */
    bo_stride = KMSDRM_gbm_bo_get_stride(dispdata->cursor_bo);
    bufsize = bo_stride * dispdata->cursor_h;

    ready_بفر = (uint8_t *)SDL_calloc(1, bufsize);

    إذا (!ready_بفر) {
        نتیجہ = false;
        اذهب cleanup;
    }

    // Copy from the cursor buffer to a buffer that we can dump to the GBM BO.
    لكل (i = 0; i < curdata->h; i++) {
        src_صف = &((uint8_t *)curdata->بفر_2)[i * curdata->w * 4];
        SDL_memcpy(ready_بفر + (i * bo_stride), src_صف, (size_t)4 * curdata->w);
    }

    // Dump the cursor buffer to our GBM BO.
    إذا (KMSDRM_gbm_bo_write(dispdata->cursor_bo, ready_بفر, bufsize)) {
        نتیجہ = SDL_سیٹ_Error("Could not write to GBM cursor BO");
        اذهب cleanup;
    }

    إذا (USE_ATOMIC_CURSOR && viddata->is_atomic) {
        // Get the fb_id for the GBM BO so we can show it on the cursor plane.
        KMSDRM_FBInfo *fb = KMSDRM_FBFromBO(video_device, dispdata->cursor_bo);
        KMSDRM_PlaneInfo info;

        إذا (!fb) {
            نتیجہ = SDL_سیٹ_Error("Failed to get cursor FB from BO");
            اذهب cleanup;
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
        drm_atomic_سیٹ_plane_props(dispdata, &info);
        إذا (drm_atomic_commit(video_device, dispdata, true, false)) {
            نتیجہ = SDL_سیٹ_Error("Failed atomic commit in KMSDRM_ShowCursor.");
            اذهب cleanup;
        }
    } وإلا {
        // Put the GBM BO buffer on screen using the DRM interface.
        bo_handle = KMSDRM_gbm_bo_get_handle(dispdata->cursor_bo).u32;
        إذا (curdata->hot_x == 0 && curdata->hot_y == 0) {
            rc = KMSDRM_drm_منوال_سیٹ_Cursor(viddata->drm_fd, dispdata->crtc.crtc->crtc_id, bo_handle, dispdata->cursor_w, dispdata->cursor_h);
        } وإلا {
            rc = KMSDRM_drm_منوال_سیٹ_Cursor2(viddata->drm_fd, dispdata->crtc.crtc->crtc_id, bo_handle, dispdata->cursor_w, dispdata->cursor_h, curdata->hot_x, curdata->hot_y);
        }
        إذا (rc < 0) {
            نتیجہ = SDL_سیٹ_Error("Failed to set DRM cursor: %s", strerror(-rc));
            اذهب cleanup;
        }
    }

cleanup:
    SDL_free(ready_بفر);
    أرجع نتیجہ;
}

// This is only for freeing the SDL_cursor.
ساكن فراغ KMSDRM_FreeCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_انکڑے *curdata;

    // Even if the cursor is not ours, free it.
    إذا (cursor) {
        curdata = cursor->اندرونی;
        // Free cursor buffer
        إذا (curdata->بفر_2) {
            SDL_free(curdata->بفر_2);
            curdata->بفر_2 = عدم;
        }
        // Free cursor itself
        SDL_free(cursor->اندرونی);
        SDL_free(cursor);
    }
}

/* This simply gets the cursor soft-buffer ready.
   We don't copy it to a GBO BO until ShowCursor() because the cusor GBM BO (living
   in dispata) is destroyed and recreated when we recreate windows, etc. */
ساكن SDL_Cursor *KMSDRM_CreateCursor(SDL_Surface *surface, صحيح hot_x, صحيح hot_y)
{
    SDL_Cursor_انکڑے *curdata;
    SDL_Cursor *cursor, *نتیجہ;

    curdata = عدم;
    نتیجہ = عدم;

    cursor = (SDL_Cursor *)SDL_calloc(1, حجم(*cursor));
    إذا (!cursor) {
        اذهب cleanup;
    }
    curdata = (SDL_Cursor_انکڑے *)SDL_calloc(1, حجم(*curdata));
    إذا (!curdata) {
        اذهب cleanup;
    }

    // hox_x and hot_y are the coordinates of the "tip of the cursor" from it's base.
    curdata->hot_x = hot_x;
    curdata->hot_y = hot_y;
    curdata->w = surface->w;
    curdata->h = surface->h;
    curdata->بفر_2 = عدم;

    /* Configure the cursor buffer info.
       This buffer has the original size of the cursor surface we are given. */
    curdata->بفر_pitch = surface->w;
    curdata->بفر_ناپ = (size_t)surface->w * surface->h * 4;
    curdata->بفر_2 = (uint32_t *)SDL_malloc(curdata->بفر_ناپ);

    إذا (!curdata->بفر_2) {
        اذهب cleanup;
    }

    /* All code below assumes ARGB8888 format for the cursor surface,
       like other backends do. Also, the GBM BO pixels have to be
       alpha-premultiplied, but the SDL surface we receive has
       straight-alpha pixels, so we always have to convert. */
    SDL_PremultiplyAlpha(surface->w, surface->h,
                         surface->format, surface->pixels, surface->pitch,
                         SDL_PIXELFORMAT_ARGB8888, curdata->بفر_2, surface->w * 4, true);

    cursor->اندرونی = curdata;

    نتیجہ = cursor;

cleanup:
    إذا (!نتیجہ) {
        إذا (curdata) {
            SDL_free(curdata->بفر_2);
            SDL_free(curdata);
        }
        SDL_free(cursor);
    }

    أرجع نتیجہ;
}

// Show the specified cursor, or hide if cursor is NULL or has no focus.
ساكن bool KMSDRM_ShowCursor(SDL_Cursor *cursor)
{
    SDL_VideoDisplay *display;
    SDL_کھڑکی *کھڑکی;
    SDL_Mouse *mouse = SDL_GetMouse();

    صحيح i;
    bool نتیجہ = true;

    // Get the mouse focused window, if any.
    کھڑکی = mouse->focus;

    إذا (!کھڑکی || !cursor) {
        /* If no window is focused by mouse or cursor is NULL,
           since we have no window (no mouse->focus) and hence
           we have no display, we simply hide mouse on all displays.
           This happens on video quit, where we get here after
           the mouse focus has been unset, yet SDL wants to
           restore the system default cursor (makes no sense here). */
        SDL_DisplayID *displays = SDL_GetDisplays(عدم);
        إذا (displays) {
            // Iterate on the displays, hiding the cursor.
            لكل (i = 0; i < displays[i]; i++) {
                display = SDL_GetVideoDisplay(displays[i]);
                نتیجہ = KMSDRM_RemoveCursorFromBO(display);
            }
            SDL_free(displays);
        }
    } وإلا {
        display = SDL_Get_Video_Display_For_کھڑکی(کھڑکی);
        إذا (display) {
            إذا (cursor) {
                /* Dump the cursor to the display DRM cursor BO so it becomes visible
                   on that display. */
                نتیجہ = KMSDRM_Dump_Cursor_منزل_BO(display, mouse, cursor);
            } وإلا {
                // Hide the cursor on that display.
                نتیجہ = KMSDRM_RemoveCursorFromBO(display);
            }
        }
    }

    أرجع نتیجہ;
}

ساكن فراغ drm_atomic_movecursor(SDL_Display_انکڑے *dispdata, ثابت SDL_Cursor_انکڑے *curdata, uint16_t x, uint16_t y)
{
    إذا (dispdata->cursor_plane) {  // We can't move a non-existing cursor, but that's ok.
        // Do we have a set of changes already in the making? If not, allocate a new one.
        إذا (!dispdata->atomic_req) {
            dispdata->atomic_req = KMSDRM_drm_منوال_Atomic_Alloc();
        }
        جوڑو_plane_property(dispdata->atomic_req, dispdata->cursor_plane, "CRTC_X", x - curdata->hot_x);
        جوڑو_plane_property(dispdata->atomic_req, dispdata->cursor_plane, "CRTC_Y", y - curdata->hot_y);
    }
}

ساكن bool KMSDRM_WarpMouseGlobal(عائم x, عائم y)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    إذا (mouse && mouse->cur_cursor && mouse->focus) {
        SDL_کھڑکی *کھڑکی = mouse->focus;
        SDL_Display_انکڑے *dispdata = SDL_Get_Display_Driver_انکڑے_For_کھڑکی(کھڑکی);

        // Update internal mouse position.
        SDL_SendMouseMotion(0, mouse->focus, SDL_GLOBAL_MOUSE_ID, false, x, y);

        // And now update the cursor graphic position on screen.
        إذا (dispdata->cursor_bo) {
            SDL_VideoDevice *dev = SDL_GetVideoDevice();
            SDL_Video_انکڑے *viddata = dev->اندرونی;
            إذا (USE_ATOMIC_CURSOR && viddata->is_atomic) {
                ثابت SDL_Cursor_انکڑے *curdata = (ثابت SDL_Cursor_انکڑے *) mouse->cur_cursor->اندرونی;
                drm_atomic_movecursor(dispdata, curdata, (uint16_t) (صحيح) x, (uint16_t) (صحيح) y);
            } وإلا {
                ثابت صحيح rc = KMSDRM_drm_منوال_Move_Cursor(dispdata->cursor_bo_drm_fd, dispdata->crtc.crtc->crtc_id, (صحيح)x, (صحيح)y);
                إذا (rc < 0) {
                    أرجع SDL_سیٹ_Error("drmModeMoveCursor() failed: %s", strerror(-rc));
                }
            }
        } وإلا {
            أرجع SDL_سیٹ_Error("Cursor not initialized properly.");
        }
    } وإلا {
        أرجع SDL_سیٹ_Error("No mouse or current cursor.");
    }

    أرجع true;
}

ساكن bool KMSDRM_WarpMouse(SDL_کھڑکی *کھڑکی, عائم x, عائم y)
{
    // Only one global/fullscreen window is supported
    أرجع KMSDRM_WarpMouseGlobal(x, y);
}

فراغ KMSDRM_InitMouse(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Display_انکڑے *dispdata = display->اندرونی;

    mouse->CreateCursor = KMSDRM_CreateCursor;
    mouse->ShowCursor = KMSDRM_ShowCursor;
    mouse->MoveCursor = KMSDRM_MoveCursor;
    mouse->FreeCursor = KMSDRM_FreeCursor;
    mouse->WarpMouse = KMSDRM_WarpMouse;
    mouse->WarpMouseGlobal = KMSDRM_WarpMouseGlobal;

    /* Only create the default cursor for this display if we haven't done so before,
       we don't want several cursors to be created for the same display. */
    إذا (!dispdata->default_cursor_init) {
        SDL_سیٹ_Default_Cursor(KMSDRM_CreateDefaultCursor());
        dispdata->default_cursor_init = true;
    }
}

فراغ KMSDRM_QuitMouse(SDL_VideoDevice *_this)
{
    // TODO: ?
}

// This is called when a mouse motion event occurs
ساكن bool KMSDRM_MoveCursor(SDL_Cursor *cursor)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    /* We must NOT call SDL_SendMouseMotion() here or we will enter recursivity!
       That's why we move the cursor graphic ONLY. */
    إذا (mouse && mouse->cur_cursor && mouse->focus) {
        SDL_کھڑکی *کھڑکی = mouse->focus;
        SDL_Display_انکڑے *dispdata = SDL_Get_Display_Driver_انکڑے_For_کھڑکی(کھڑکی);
        SDL_VideoDevice *dev = SDL_GetVideoDevice();
        SDL_Video_انکڑے *viddata = dev->اندرونی;

        إذا (!dispdata->cursor_bo) {
            أرجع SDL_سیٹ_Error("Cursor not initialized properly.");
        }

        إذا (USE_ATOMIC_CURSOR && viddata->is_atomic) {
            /* !!! FIXME: Some programs expect cursor movement even while they don't do SwapWindow() calls,
               and since we ride on the atomic_commit() in SwapWindow() for cursor movement,
               cursor won't move in these situations. We could do an atomic_commit() here
               for each cursor movement request, but it cripples the movement to 30FPS,
               so a future solution is needed. SDLPoP "QUIT?" menu is an example of this
               situation. */
            ثابت SDL_Cursor_انکڑے *curdata = (ثابت SDL_Cursor_انکڑے *) mouse->cur_cursor->اندرونی;
            drm_atomic_movecursor(dispdata, curdata, (uint16_t) (صحيح) mouse->x, (uint16_t) (صحيح) mouse->y);
        } وإلا {
            ثابت صحيح rc = KMSDRM_drm_منوال_Move_Cursor(dispdata->cursor_bo_drm_fd, dispdata->crtc.crtc->crtc_id, (صحيح)mouse->x, (صحيح)mouse->y);
            إذا (rc < 0) {
                أرجع SDL_سیٹ_Error("drmModeMoveCursor() failed: %s", strerror(-rc));
            }
        }
    }
    أرجع true;
}

#جے_انت // SDL_VIDEO_DRIVER_KMSDRM
