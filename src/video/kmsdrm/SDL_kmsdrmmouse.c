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

#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_KMSDRM

#অন্তর্ভাব "SDL_kmsdrmvideo.h"
#অন্তর্ভাব "SDL_kmsdrmmouse.h"
#অন্তর্ভাব "SDL_kmsdrmdyn.h"

#অন্তর্ভাব "../../events/SDL_mouse_c.h"
#অন্তর্ভাব "../../events/default_cursor.h"

#অন্তর্ভাব "../SDL_pixels_c.h"

// !!! FIXME: atomic cursors are broken right now.
#define USE_ATOMIC_CURSOR 0

স্থির SDL_Cursor *KMSDRM_CreateDefaultCursor(শূন্য);
স্থির SDL_Cursor *KMSDRM_CreateCursor(SDL_Surface *surface, পূর্ণসংখ্যা hot_x, পূর্ণসংখ্যা hot_y);
স্থির bool KMSDRM_ShowCursor(SDL_Cursor *cursor);
স্থির bool KMSDRM_MoveCursor(SDL_Cursor *cursor);
স্থির শূন্য KMSDRM_FreeCursor(SDL_Cursor *cursor);

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

স্থির SDL_Cursor *KMSDRM_CreateDefaultCursor(শূন্য)
{
    ফেরত SDL_CreateCursor(default_cdata, default_cmask, DEFAULT_CWIDTH, DEFAULT_CHEIGHT, DEFAULT_CHOTX, DEFAULT_CHOTY);
}

/* Given a display's internal, destroy the cursor BO for it.
   To be called from KMSDRM_DestroyWindow(), as that's where we
   destroy the internal for the window's display. */
শূন্য KMSDRM_DestroyCursorBO(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_তথ্য *dispdata = display->internal;

    // Destroy the curso GBM BO.
    যদি (dispdata->cursor_bo) {
        SDL_Video_তথ্য *viddata = (SDL_Video_তথ্য *) _this->internal;
        যদি (USE_ATOMIC_CURSOR && viddata->is_atomic) {
            যদি (dispdata->cursor_plane) {
                // Unset the the cursor BO from the cursor plane.
                KMSDRM_PlaneInfo info;
                SDL_zero(info);
                info.plane = dispdata->cursor_plane;
                drm_atomic_set_plane_props(dispdata, &info);
                // Wait until the cursor is unset from the cursor plane before destroying it's BO.
                যদি (drm_atomic_commit(_this, dispdata, true, false)) {
                    SDL_SetError("Failed atomic commit in KMSDRM_DenitMouse.");
                }
                // Free the cursor plane, on which the cursor was being shown.
                free_plane(&dispdata->cursor_plane);
            }
        }

        KMSDRM_gbm_bo_destroy(dispdata->cursor_bo);
        dispdata->cursor_bo = ফাঁকা;
        dispdata->cursor_bo_drm_fd = -1;
    }
}

/* Given a display's internal, create the cursor BO for it.
   To be called from KMSDRM_CreateWindow(), as that's where we
   build a window and assign a display to it. */
bool KMSDRM_CreateCursorBO(SDL_VideoDisplay *display)
{
    SDL_VideoDevice *dev = SDL_GetVideoDevice();
    SDL_Video_তথ্য *viddata = dev->internal;
    SDL_Display_তথ্য *dispdata = display->internal;

    যদি (USE_ATOMIC_CURSOR && viddata->is_atomic) {
        setup_plane(dev, dispdata, &dispdata->cursor_plane, DRM_PLANE_TYPE_CURSOR);
    }

    যদি (!KMSDRM_gbm_device_is_format_supported(viddata->gbm_dev,
                                               GBM_FORMAT_ARGB8888,
                                               GBM_BO_USE_CURSOR | GBM_BO_USE_WRITE)) {
        ফেরত SDL_SetError("Unsupported pixel format for cursor");
    }

    যদি (KMSDRM_drmGetCap(viddata->drm_fd,
                         DRM_CAP_CURSOR_WIDTH, &dispdata->cursor_w) ||
        KMSDRM_drmGetCap(viddata->drm_fd, DRM_CAP_CURSOR_HEIGHT,
                         &dispdata->cursor_h)) {
        ফেরত SDL_SetError("Could not get the recommended GBM cursor size");
    }

    যদি (dispdata->cursor_w == 0 || dispdata->cursor_h == 0) {
        ফেরত SDL_SetError("Could not get an usable GBM cursor size");
    }

    dispdata->cursor_bo = KMSDRM_gbm_bo_create(viddata->gbm_dev,
                                               dispdata->cursor_w, dispdata->cursor_h,
                                               GBM_FORMAT_ARGB8888, GBM_BO_USE_CURSOR | GBM_BO_USE_WRITE | GBM_BO_USE_LINEAR);

    যদি (!dispdata->cursor_bo) {
        ফেরত SDL_SetError("Could not create GBM cursor BO");
    }

    dispdata->cursor_bo_drm_fd = viddata->drm_fd;
    ফেরত true;
}

// Remove a cursor buffer from a display's DRM cursor BO.
স্থির bool KMSDRM_RemoveCursorFromBO(SDL_VideoDisplay *display)
{
    bool ফলাফল = true;

    SDL_Display_তথ্য *dispdata = display->internal;
    SDL_VideoDevice *video_device = SDL_GetVideoDevice();
    SDL_Video_তথ্য *viddata = video_device->internal;

    যদি (USE_ATOMIC_CURSOR && viddata->is_atomic) {
        যদি (dispdata->cursor_plane) {
            KMSDRM_PlaneInfo info;
            SDL_zero(info);
            info.plane = dispdata->cursor_plane;
            // The rest of the members are zeroed, so this takes away the cursor from the cursor plane.
            drm_atomic_set_plane_props(dispdata, &info);
            যদি (drm_atomic_commit(video_device, dispdata, true, false)) {
                ফলাফল = SDL_SetError("Failed atomic commit in KMSDRM_ShowCursor.");
            }
        }
    } অন্যথা {
        ধ্রুবক পূর্ণসংখ্যা rc = KMSDRM_drmModeSetCursor(viddata->drm_fd, dispdata->crtc.crtc->crtc_id, 0, 0, 0);
        যদি (rc < 0) {
            ফলাফল = SDL_SetError("drmModeSetCursor() failed: %s", strerror(-rc));
        }
    }

    ফেরত ফলাফল;
}

// Dump a cursor buffer to a display's DRM cursor BO.
স্থির bool KMSDRM_DumpCursorToBO(SDL_VideoDisplay *display, SDL_Mouse *mouse, SDL_Cursor *cursor)
{
    SDL_Display_তথ্য *dispdata = display->internal;
    SDL_Cursor_তথ্য *curdata = cursor->internal;
    SDL_VideoDevice *video_device = SDL_GetVideoDevice();
    SDL_Video_তথ্য *viddata = video_device->internal;

    uint32_t bo_handle;
    size_t bo_stride;
    size_t bufsize;
    uint8_t *ready_বাফার = ফাঁকা;
    uint8_t *src_row;

    পূর্ণসংখ্যা i, rc;
    bool ফলাফল = true;

    যদি (!curdata || !dispdata->cursor_bo) {
        ফেরত SDL_SetError("Cursor or display not initialized properly.");
    }

    /* Prepare a buffer we can dump to our GBM BO (different
       size, alpha premultiplication...) */
    bo_stride = KMSDRM_gbm_bo_get_stride(dispdata->cursor_bo);
    bufsize = bo_stride * dispdata->cursor_h;

    ready_বাফার = (uint8_t *)SDL_calloc(1, bufsize);

    যদি (!ready_বাফার) {
        ফলাফল = false;
        যাও cleanup;
    }

    // Copy from the cursor buffer to a buffer that we can dump to the GBM BO.
    জন্য (i = 0; i < curdata->h; i++) {
        src_row = &((uint8_t *)curdata->বাফার_2)[i * curdata->w * 4];
        SDL_memcpy(ready_বাফার + (i * bo_stride), src_row, (size_t)4 * curdata->w);
    }

    // Dump the cursor buffer to our GBM BO.
    যদি (KMSDRM_gbm_bo_write(dispdata->cursor_bo, ready_বাফার, bufsize)) {
        ফলাফল = SDL_SetError("Could not write to GBM cursor BO");
        যাও cleanup;
    }

    যদি (USE_ATOMIC_CURSOR && viddata->is_atomic) {
        // Get the fb_id for the GBM BO so we can show it on the cursor plane.
        KMSDRM_FBInfo *fb = KMSDRM_FBFromBO(video_device, dispdata->cursor_bo);
        KMSDRM_PlaneInfo info;

        যদি (!fb) {
            ফলাফল = SDL_SetError("Failed to get cursor FB from BO");
            যাও cleanup;
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
        drm_atomic_set_plane_props(dispdata, &info);
        যদি (drm_atomic_commit(video_device, dispdata, true, false)) {
            ফলাফল = SDL_SetError("Failed atomic commit in KMSDRM_ShowCursor.");
            যাও cleanup;
        }
    } অন্যথা {
        // Put the GBM BO buffer on screen using the DRM interface.
        bo_handle = KMSDRM_gbm_bo_get_handle(dispdata->cursor_bo).u32;
        যদি (curdata->hot_x == 0 && curdata->hot_y == 0) {
            rc = KMSDRM_drmModeSetCursor(viddata->drm_fd, dispdata->crtc.crtc->crtc_id, bo_handle, dispdata->cursor_w, dispdata->cursor_h);
        } অন্যথা {
            rc = KMSDRM_drmModeSetCursor2(viddata->drm_fd, dispdata->crtc.crtc->crtc_id, bo_handle, dispdata->cursor_w, dispdata->cursor_h, curdata->hot_x, curdata->hot_y);
        }
        যদি (rc < 0) {
            ফলাফল = SDL_SetError("Failed to set DRM cursor: %s", strerror(-rc));
            যাও cleanup;
        }
    }

cleanup:
    SDL_free(ready_বাফার);
    ফেরত ফলাফল;
}

// This is only for freeing the SDL_cursor.
স্থির শূন্য KMSDRM_FreeCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_তথ্য *curdata;

    // Even if the cursor is not ours, free it.
    যদি (cursor) {
        curdata = cursor->internal;
        // Free cursor buffer
        যদি (curdata->বাফার_2) {
            SDL_free(curdata->বাফার_2);
            curdata->বাফার_2 = ফাঁকা;
        }
        // Free cursor itself
        SDL_free(cursor->internal);
        SDL_free(cursor);
    }
}

/* This simply gets the cursor soft-buffer ready.
   We don't copy it to a GBO BO until ShowCursor() because the cusor GBM BO (living
   in dispata) is destroyed and recreated when we recreate windows, etc. */
স্থির SDL_Cursor *KMSDRM_CreateCursor(SDL_Surface *surface, পূর্ণসংখ্যা hot_x, পূর্ণসংখ্যা hot_y)
{
    SDL_Cursor_তথ্য *curdata;
    SDL_Cursor *cursor, *ফলাফল;

    curdata = ফাঁকা;
    ফলাফল = ফাঁকা;

    cursor = (SDL_Cursor *)SDL_calloc(1, আকার(*cursor));
    যদি (!cursor) {
        যাও cleanup;
    }
    curdata = (SDL_Cursor_তথ্য *)SDL_calloc(1, আকার(*curdata));
    যদি (!curdata) {
        যাও cleanup;
    }

    // hox_x and hot_y are the coordinates of the "tip of the cursor" from it's base.
    curdata->hot_x = hot_x;
    curdata->hot_y = hot_y;
    curdata->w = surface->w;
    curdata->h = surface->h;
    curdata->বাফার_2 = ফাঁকা;

    /* Configure the cursor buffer info.
       This buffer has the original size of the cursor surface we are given. */
    curdata->বাফার_pitch = surface->w;
    curdata->বাফার_আকার = (size_t)surface->w * surface->h * 4;
    curdata->বাফার_2 = (uint32_t *)SDL_malloc(curdata->বাফার_আকার);

    যদি (!curdata->বাফার_2) {
        যাও cleanup;
    }

    /* All code below assumes ARGB8888 format for the cursor surface,
       like other backends do. Also, the GBM BO pixels have to be
       alpha-premultiplied, but the SDL surface we receive has
       straight-alpha pixels, so we always have to convert. */
    SDL_PremultiplyAlpha(surface->w, surface->h,
                         surface->format, surface->pixels, surface->pitch,
                         SDL_PIXELFORMAT_ARGB8888, curdata->বাফার_2, surface->w * 4, true);

    cursor->internal = curdata;

    ফলাফল = cursor;

cleanup:
    যদি (!ফলাফল) {
        যদি (curdata) {
            SDL_free(curdata->বাফার_2);
            SDL_free(curdata);
        }
        SDL_free(cursor);
    }

    ফেরত ফলাফল;
}

// Show the specified cursor, or hide if cursor is NULL or has no focus.
স্থির bool KMSDRM_ShowCursor(SDL_Cursor *cursor)
{
    SDL_VideoDisplay *display;
    SDL_Window *window;
    SDL_Mouse *mouse = SDL_GetMouse();

    পূর্ণসংখ্যা i;
    bool ফলাফল = true;

    // Get the mouse focused window, if any.
    window = mouse->focus;

    যদি (!window || !cursor) {
        /* If no window is focused by mouse or cursor is NULL,
           since we have no window (no mouse->focus) and hence
           we have no display, we simply hide mouse on all displays.
           This happens on video quit, where we get here after
           the mouse focus has been unset, yet SDL wants to
           restore the system default cursor (makes no sense here). */
        SDL_DisplayID *displays = SDL_GetDisplays(ফাঁকা);
        যদি (displays) {
            // Iterate on the displays, hiding the cursor.
            জন্য (i = 0; i < displays[i]; i++) {
                display = SDL_GetVideoDisplay(displays[i]);
                ফলাফল = KMSDRM_RemoveCursorFromBO(display);
            }
            SDL_free(displays);
        }
    } অন্যথা {
        display = SDL_GetVideoDisplayForWindow(window);
        যদি (display) {
            যদি (cursor) {
                /* Dump the cursor to the display DRM cursor BO so it becomes visible
                   on that display. */
                ফলাফল = KMSDRM_DumpCursorToBO(display, mouse, cursor);
            } অন্যথা {
                // Hide the cursor on that display.
                ফলাফল = KMSDRM_RemoveCursorFromBO(display);
            }
        }
    }

    ফেরত ফলাফল;
}

স্থির শূন্য drm_atomic_movecursor(SDL_Display_তথ্য *dispdata, ধ্রুবক SDL_Cursor_তথ্য *curdata, uint16_t x, uint16_t y)
{
    যদি (dispdata->cursor_plane) {  // We can't move a non-existing cursor, but that's ok.
        // Do we have a set of changes already in the making? If not, allocate a new one.
        যদি (!dispdata->atomic_req) {
            dispdata->atomic_req = KMSDRM_drmModeAtomicAlloc();
        }
        add_plane_property(dispdata->atomic_req, dispdata->cursor_plane, "CRTC_X", x - curdata->hot_x);
        add_plane_property(dispdata->atomic_req, dispdata->cursor_plane, "CRTC_Y", y - curdata->hot_y);
    }
}

স্থির bool KMSDRM_WarpMouseGlobal(দশমিক x, দশমিক y)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    যদি (mouse && mouse->cur_cursor && mouse->focus) {
        SDL_Window *window = mouse->focus;
        SDL_Display_তথ্য *dispdata = SDL_Get_Display_Driver_তথ্য_For_Window(window);

        // Update internal mouse position.
        SDL_SendMouseMotion(0, mouse->focus, SDL_GLOBAL_MOUSE_ID, false, x, y);

        // And now update the cursor graphic position on screen.
        যদি (dispdata->cursor_bo) {
            SDL_VideoDevice *dev = SDL_GetVideoDevice();
            SDL_Video_তথ্য *viddata = dev->internal;
            যদি (USE_ATOMIC_CURSOR && viddata->is_atomic) {
                ধ্রুবক SDL_Cursor_তথ্য *curdata = (ধ্রুবক SDL_Cursor_তথ্য *) mouse->cur_cursor->internal;
                drm_atomic_movecursor(dispdata, curdata, (uint16_t) (পূর্ণসংখ্যা) x, (uint16_t) (পূর্ণসংখ্যা) y);
            } অন্যথা {
                ধ্রুবক পূর্ণসংখ্যা rc = KMSDRM_drmModeMoveCursor(dispdata->cursor_bo_drm_fd, dispdata->crtc.crtc->crtc_id, (পূর্ণসংখ্যা)x, (পূর্ণসংখ্যা)y);
                যদি (rc < 0) {
                    ফেরত SDL_SetError("drmModeMoveCursor() failed: %s", strerror(-rc));
                }
            }
        } অন্যথা {
            ফেরত SDL_SetError("Cursor not initialized properly.");
        }
    } অন্যথা {
        ফেরত SDL_SetError("No mouse or current cursor.");
    }

    ফেরত true;
}

স্থির bool KMSDRM_WarpMouse(SDL_Window *window, দশমিক x, দশমিক y)
{
    // Only one global/fullscreen window is supported
    ফেরত KMSDRM_WarpMouseGlobal(x, y);
}

শূন্য KMSDRM_InitMouse(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Display_তথ্য *dispdata = display->internal;

    mouse->CreateCursor = KMSDRM_CreateCursor;
    mouse->ShowCursor = KMSDRM_ShowCursor;
    mouse->MoveCursor = KMSDRM_MoveCursor;
    mouse->FreeCursor = KMSDRM_FreeCursor;
    mouse->WarpMouse = KMSDRM_WarpMouse;
    mouse->WarpMouseGlobal = KMSDRM_WarpMouseGlobal;

    /* Only create the default cursor for this display if we haven't done so before,
       we don't want several cursors to be created for the same display. */
    যদি (!dispdata->default_cursor_init) {
        SDL_SetDefaultCursor(KMSDRM_CreateDefaultCursor());
        dispdata->default_cursor_init = true;
    }
}

শূন্য KMSDRM_QuitMouse(SDL_VideoDevice *_this)
{
    // TODO: ?
}

// This is called when a mouse motion event occurs
স্থির bool KMSDRM_MoveCursor(SDL_Cursor *cursor)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    /* We must NOT call SDL_SendMouseMotion() here or we will enter recursivity!
       That's why we move the cursor graphic ONLY. */
    যদি (mouse && mouse->cur_cursor && mouse->focus) {
        SDL_Window *window = mouse->focus;
        SDL_Display_তথ্য *dispdata = SDL_Get_Display_Driver_তথ্য_For_Window(window);
        SDL_VideoDevice *dev = SDL_GetVideoDevice();
        SDL_Video_তথ্য *viddata = dev->internal;

        যদি (!dispdata->cursor_bo) {
            ফেরত SDL_SetError("Cursor not initialized properly.");
        }

        যদি (USE_ATOMIC_CURSOR && viddata->is_atomic) {
            /* !!! FIXME: Some programs expect cursor movement even while they don't do SwapWindow() calls,
               and since we ride on the atomic_commit() in SwapWindow() for cursor movement,
               cursor won't move in these situations. We could do an atomic_commit() here
               for each cursor movement request, but it cripples the movement to 30FPS,
               so a future solution is needed. SDLPoP "QUIT?" menu is an example of this
               situation. */
            ধ্রুবক SDL_Cursor_তথ্য *curdata = (ধ্রুবক SDL_Cursor_তথ্য *) mouse->cur_cursor->internal;
            drm_atomic_movecursor(dispdata, curdata, (uint16_t) (পূর্ণসংখ্যা) mouse->x, (uint16_t) (পূর্ণসংখ্যা) mouse->y);
        } অন্যথা {
            ধ্রুবক পূর্ণসংখ্যা rc = KMSDRM_drmModeMoveCursor(dispdata->cursor_bo_drm_fd, dispdata->crtc.crtc->crtc_id, (পূর্ণসংখ্যা)mouse->x, (পূর্ণসংখ্যা)mouse->y);
            যদি (rc < 0) {
                ফেরত SDL_SetError("drmModeMoveCursor() failed: %s", strerror(-rc));
            }
        }
    }
    ফেরত true;
}

#endif // SDL_VIDEO_DRIVER_KMSDRM
