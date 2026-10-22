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

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_KMSDRM

#ಅನ್ತರ್ಭಾವ "SDL_kmsdrmvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_kmsdrmmouse.h"
#ಅನ್ತರ್ಭಾವ "SDL_kmsdrmdyn.h"

#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/default_cursor.h"

#ಅನ್ತರ್ಭಾವ "../SDL_pixels_c.h"

// !!! FIXME: atomic cursors are broken right now.
#ವ್ಯಾಖ್ಯಾನಿಸು USE_ATOMIC_CURSOR 0

ಸ್ಥಿರ SDL_Cursor *KMSDRM_CreateDefaultCursor(ಶೂನ್ಯ);
ಸ್ಥಿರ SDL_Cursor *KMSDRM_CreateCursor(SDL_Surface *surface, ಪೂರ್ಣಾಂಕ hot_x, ಪೂರ್ಣಾಂಕ hot_y);
ಸ್ಥಿರ bool KMSDRM_ShowCursor(SDL_Cursor *cursor);
ಸ್ಥಿರ bool KMSDRM_MoveCursor(SDL_Cursor *cursor);
ಸ್ಥಿರ ಶೂನ್ಯ KMSDRM_FreeCursor(SDL_Cursor *cursor);

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

ಸ್ಥಿರ SDL_Cursor *KMSDRM_CreateDefaultCursor(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ SDL_CreateCursor(default_cdata, default_cmask, DEFAULT_CWIDTH, DEFAULT_CHEIGHT, DEFAULT_CHOTX, DEFAULT_CHOTY);
}

/* Given a display's internal, destroy the cursor BO for it.
   To be called from KMSDRM_DestroyWindow(), as that's where we
   destroy the internal for the window's display. */
ಶೂನ್ಯ KMSDRM_DestroyCursorBO(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_ದತ್ತಾಂಶ *dispdata = display->ಆಂತರಿಕ;

    // Destroy the curso GBM BO.
    ಆದರೆ (dispdata->cursor_bo) {
        SDL_Video_ದತ್ತಾಂಶ *viddata = (SDL_Video_ದತ್ತಾಂಶ *) _this->ಆಂತರಿಕ;
        ಆದರೆ (USE_ATOMIC_CURSOR && viddata->is_atomic) {
            ಆದರೆ (dispdata->cursor_plane) {
                // Unset the the cursor BO from the cursor plane.
                KMSDRM_PlaneInfo info;
                SDL_zero(info);
                info.plane = dispdata->cursor_plane;
                drm_atomic_ಗಣ_plane_props(dispdata, &info);
                // Wait until the cursor is unset from the cursor plane before destroying it's BO.
                ಆದರೆ (drm_atomic_commit(_this, dispdata, true, false)) {
                    SDL_ಗಣ_Error("Failed atomic commit in KMSDRM_DenitMouse.");
                }
                // Free the cursor plane, on which the cursor was being shown.
                free_plane(&dispdata->cursor_plane);
            }
        }

        KMSDRM_gbm_bo_destroy(dispdata->cursor_bo);
        dispdata->cursor_bo = ಖಾಲಿ;
        dispdata->cursor_bo_drm_fd = -1;
    }
}

/* Given a display's internal, create the cursor BO for it.
   To be called from KMSDRM_CreateWindow(), as that's where we
   build a window and assign a display to it. */
bool KMSDRM_CreateCursorBO(SDL_VideoDisplay *display)
{
    SDL_VideoDevice *dev = SDL_GetVideoDevice();
    SDL_Video_ದತ್ತಾಂಶ *viddata = dev->ಆಂತರಿಕ;
    SDL_Display_ದತ್ತಾಂಶ *dispdata = display->ಆಂತರಿಕ;

    ಆದರೆ (USE_ATOMIC_CURSOR && viddata->is_atomic) {
        ಸಿದ್ಧತೆ_plane(dev, dispdata, &dispdata->cursor_plane, DRM_PLANE_TYPE_CURSOR);
    }

    ಆದರೆ (!KMSDRM_gbm_device_is_format_supported(viddata->gbm_dev,
                                               GBM_FORMAT_ARGB8888,
                                               GBM_BO_USE_CURSOR | GBM_BO_USE_WRITE)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Unsupported pixel format for cursor");
    }

    ಆದರೆ (KMSDRM_drmGetCap(viddata->drm_fd,
                         DRM_CAP_CURSOR_ಅಗಲ, &dispdata->cursor_w) ||
        KMSDRM_drmGetCap(viddata->drm_fd, DRM_CAP_CURSOR_ಎತ್ತರ,
                         &dispdata->cursor_h)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Could not get the recommended GBM cursor size");
    }

    ಆದರೆ (dispdata->cursor_w == 0 || dispdata->cursor_h == 0) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Could not get an usable GBM cursor size");
    }

    dispdata->cursor_bo = KMSDRM_gbm_bo_create(viddata->gbm_dev,
                                               dispdata->cursor_w, dispdata->cursor_h,
                                               GBM_FORMAT_ARGB8888, GBM_BO_USE_CURSOR | GBM_BO_USE_WRITE | GBM_BO_USE_ರೇಖೀಯ);

    ಆದರೆ (!dispdata->cursor_bo) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Could not create GBM cursor BO");
    }

    dispdata->cursor_bo_drm_fd = viddata->drm_fd;
    ಹಿಂತಿರುಗಿ true;
}

// Remove a cursor buffer from a display's DRM cursor BO.
ಸ್ಥಿರ bool KMSDRM_RemoveCursorFromBO(SDL_VideoDisplay *display)
{
    bool ಫಲಿತಾಂಶ = true;

    SDL_Display_ದತ್ತಾಂಶ *dispdata = display->ಆಂತರಿಕ;
    SDL_VideoDevice *video_device = SDL_GetVideoDevice();
    SDL_Video_ದತ್ತಾಂಶ *viddata = video_device->ಆಂತರಿಕ;

    ಆದರೆ (USE_ATOMIC_CURSOR && viddata->is_atomic) {
        ಆದರೆ (dispdata->cursor_plane) {
            KMSDRM_PlaneInfo info;
            SDL_zero(info);
            info.plane = dispdata->cursor_plane;
            // The rest of the members are zeroed, so this takes away the cursor from the cursor plane.
            drm_atomic_ಗಣ_plane_props(dispdata, &info);
            ಆದರೆ (drm_atomic_commit(video_device, dispdata, true, false)) {
                ಫಲಿತಾಂಶ = SDL_ಗಣ_Error("Failed atomic commit in KMSDRM_ShowCursor.");
            }
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ rc = KMSDRM_drm_ಬಹುಲಕ_ಗಣ_Cursor(viddata->drm_fd, dispdata->crtc.crtc->crtc_id, 0, 0, 0);
        ಆದರೆ (rc < 0) {
            ಫಲಿತಾಂಶ = SDL_ಗಣ_Error("drmModeSetCursor() failed: %s", strerror(-rc));
        }
    }

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

// Dump a cursor buffer to a display's DRM cursor BO.
ಸ್ಥಿರ bool KMSDRM_Dump_Cursor_ಗಮ್ಯ_BO(SDL_VideoDisplay *display, SDL_Mouse *mouse, SDL_Cursor *cursor)
{
    SDL_Display_ದತ್ತಾಂಶ *dispdata = display->ಆಂತರಿಕ;
    SDL_Cursor_ದತ್ತಾಂಶ *curdata = cursor->ಆಂತರಿಕ;
    SDL_VideoDevice *video_device = SDL_GetVideoDevice();
    SDL_Video_ದತ್ತಾಂಶ *viddata = video_device->ಆಂತರಿಕ;

    uint32_t bo_handle;
    size_t bo_stride;
    size_t bufsize;
    uint8_t *ready_ಬಫರ್ = ಖಾಲಿ;
    uint8_t *src_ಅಡ್ಡಸಾಲು;

    ಪೂರ್ಣಾಂಕ i, rc;
    bool ಫಲಿತಾಂಶ = true;

    ಆದರೆ (!curdata || !dispdata->cursor_bo) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Cursor or display not initialized properly.");
    }

    /* Prepare a buffer we can dump to our GBM BO (different
       size, alpha premultiplication...) */
    bo_stride = KMSDRM_gbm_bo_get_stride(dispdata->cursor_bo);
    bufsize = bo_stride * dispdata->cursor_h;

    ready_ಬಫರ್ = (uint8_t *)SDL_calloc(1, bufsize);

    ಆದರೆ (!ready_ಬಫರ್) {
        ಫಲಿತಾಂಶ = false;
        ಹೋಗು cleanup;
    }

    // Copy from the cursor buffer to a buffer that we can dump to the GBM BO.
    ಗಾಗಿ (i = 0; i < curdata->h; i++) {
        src_ಅಡ್ಡಸಾಲು = &((uint8_t *)curdata->ಬಫರ್_2)[i * curdata->w * 4];
        SDL_memcpy(ready_ಬಫರ್ + (i * bo_stride), src_ಅಡ್ಡಸಾಲು, (size_t)4 * curdata->w);
    }

    // Dump the cursor buffer to our GBM BO.
    ಆದರೆ (KMSDRM_gbm_bo_write(dispdata->cursor_bo, ready_ಬಫರ್, bufsize)) {
        ಫಲಿತಾಂಶ = SDL_ಗಣ_Error("Could not write to GBM cursor BO");
        ಹೋಗು cleanup;
    }

    ಆದರೆ (USE_ATOMIC_CURSOR && viddata->is_atomic) {
        // Get the fb_id for the GBM BO so we can show it on the cursor plane.
        KMSDRM_FBInfo *fb = KMSDRM_FBFromBO(video_device, dispdata->cursor_bo);
        KMSDRM_PlaneInfo info;

        ಆದರೆ (!fb) {
            ಫಲಿತಾಂಶ = SDL_ಗಣ_Error("Failed to get cursor FB from BO");
            ಹೋಗು cleanup;
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
        drm_atomic_ಗಣ_plane_props(dispdata, &info);
        ಆದರೆ (drm_atomic_commit(video_device, dispdata, true, false)) {
            ಫಲಿತಾಂಶ = SDL_ಗಣ_Error("Failed atomic commit in KMSDRM_ShowCursor.");
            ಹೋಗು cleanup;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        // Put the GBM BO buffer on screen using the DRM interface.
        bo_handle = KMSDRM_gbm_bo_get_handle(dispdata->cursor_bo).u32;
        ಆದರೆ (curdata->hot_x == 0 && curdata->hot_y == 0) {
            rc = KMSDRM_drm_ಬಹುಲಕ_ಗಣ_Cursor(viddata->drm_fd, dispdata->crtc.crtc->crtc_id, bo_handle, dispdata->cursor_w, dispdata->cursor_h);
        } ಇಲ್ಲದಿದ್ದರೆ {
            rc = KMSDRM_drm_ಬಹುಲಕ_ಗಣ_Cursor2(viddata->drm_fd, dispdata->crtc.crtc->crtc_id, bo_handle, dispdata->cursor_w, dispdata->cursor_h, curdata->hot_x, curdata->hot_y);
        }
        ಆದರೆ (rc < 0) {
            ಫಲಿತಾಂಶ = SDL_ಗಣ_Error("Failed to set DRM cursor: %s", strerror(-rc));
            ಹೋಗು cleanup;
        }
    }

cleanup:
    SDL_free(ready_ಬಫರ್);
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

// This is only for freeing the SDL_cursor.
ಸ್ಥಿರ ಶೂನ್ಯ KMSDRM_FreeCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_ದತ್ತಾಂಶ *curdata;

    // Even if the cursor is not ours, free it.
    ಆದರೆ (cursor) {
        curdata = cursor->ಆಂತರಿಕ;
        // Free cursor buffer
        ಆದರೆ (curdata->ಬಫರ್_2) {
            SDL_free(curdata->ಬಫರ್_2);
            curdata->ಬಫರ್_2 = ಖಾಲಿ;
        }
        // Free cursor itself
        SDL_free(cursor->ಆಂತರಿಕ);
        SDL_free(cursor);
    }
}

/* This simply gets the cursor soft-buffer ready.
   We don't copy it to a GBO BO until ShowCursor() because the cusor GBM BO (living
   in dispata) is destroyed and recreated when we recreate windows, etc. */
ಸ್ಥಿರ SDL_Cursor *KMSDRM_CreateCursor(SDL_Surface *surface, ಪೂರ್ಣಾಂಕ hot_x, ಪೂರ್ಣಾಂಕ hot_y)
{
    SDL_Cursor_ದತ್ತಾಂಶ *curdata;
    SDL_Cursor *cursor, *ಫಲಿತಾಂಶ;

    curdata = ಖಾಲಿ;
    ಫಲಿತಾಂಶ = ಖಾಲಿ;

    cursor = (SDL_Cursor *)SDL_calloc(1, ಗಾತ್ರ(*cursor));
    ಆದರೆ (!cursor) {
        ಹೋಗು cleanup;
    }
    curdata = (SDL_Cursor_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(*curdata));
    ಆದರೆ (!curdata) {
        ಹೋಗು cleanup;
    }

    // hox_x and hot_y are the coordinates of the "tip of the cursor" from it's base.
    curdata->hot_x = hot_x;
    curdata->hot_y = hot_y;
    curdata->w = surface->w;
    curdata->h = surface->h;
    curdata->ಬಫರ್_2 = ಖಾಲಿ;

    /* Configure the cursor buffer info.
       This buffer has the original size of the cursor surface we are given. */
    curdata->ಬಫರ್_pitch = surface->w;
    curdata->ಬಫರ್_ಗಾತ್ರ = (size_t)surface->w * surface->h * 4;
    curdata->ಬಫರ್_2 = (uint32_t *)SDL_malloc(curdata->ಬಫರ್_ಗಾತ್ರ);

    ಆದರೆ (!curdata->ಬಫರ್_2) {
        ಹೋಗು cleanup;
    }

    /* All code below assumes ARGB8888 format for the cursor surface,
       like other backends do. Also, the GBM BO pixels have to be
       alpha-premultiplied, but the SDL surface we receive has
       straight-alpha pixels, so we always have to convert. */
    SDL_PremultiplyAlpha(surface->w, surface->h,
                         surface->format, surface->pixels, surface->pitch,
                         SDL_PIXELFORMAT_ARGB8888, curdata->ಬಫರ್_2, surface->w * 4, true);

    cursor->ಆಂತರಿಕ = curdata;

    ಫಲಿತಾಂಶ = cursor;

cleanup:
    ಆದರೆ (!ಫಲಿತಾಂಶ) {
        ಆದರೆ (curdata) {
            SDL_free(curdata->ಬಫರ್_2);
            SDL_free(curdata);
        }
        SDL_free(cursor);
    }

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

// Show the specified cursor, or hide if cursor is NULL or has no focus.
ಸ್ಥಿರ bool KMSDRM_ShowCursor(SDL_Cursor *cursor)
{
    SDL_VideoDisplay *display;
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ;
    SDL_Mouse *mouse = SDL_GetMouse();

    ಪೂರ್ಣಾಂಕ i;
    bool ಫಲಿತಾಂಶ = true;

    // Get the mouse focused window, if any.
    ಕಿಟಕಿ = mouse->focus;

    ಆದರೆ (!ಕಿಟಕಿ || !cursor) {
        /* If no window is focused by mouse or cursor is NULL,
           since we have no window (no mouse->focus) and hence
           we have no display, we simply hide mouse on all displays.
           This happens on video quit, where we get here after
           the mouse focus has been unset, yet SDL wants to
           restore the system default cursor (makes no sense here). */
        SDL_DisplayID *displays = SDL_GetDisplays(ಖಾಲಿ);
        ಆದರೆ (displays) {
            // Iterate on the displays, hiding the cursor.
            ಗಾಗಿ (i = 0; i < displays[i]; i++) {
                display = SDL_GetVideoDisplay(displays[i]);
                ಫಲಿತಾಂಶ = KMSDRM_RemoveCursorFromBO(display);
            }
            SDL_free(displays);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        display = SDL_Get_Video_Display_For_ಕಿಟಕಿ(ಕಿಟಕಿ);
        ಆದರೆ (display) {
            ಆದರೆ (cursor) {
                /* Dump the cursor to the display DRM cursor BO so it becomes visible
                   on that display. */
                ಫಲಿತಾಂಶ = KMSDRM_Dump_Cursor_ಗಮ್ಯ_BO(display, mouse, cursor);
            } ಇಲ್ಲದಿದ್ದರೆ {
                // Hide the cursor on that display.
                ಫಲಿತಾಂಶ = KMSDRM_RemoveCursorFromBO(display);
            }
        }
    }

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

ಸ್ಥಿರ ಶೂನ್ಯ drm_atomic_movecursor(SDL_Display_ದತ್ತಾಂಶ *dispdata, ಸ್ಥಿರಾಂಕ SDL_Cursor_ದತ್ತಾಂಶ *curdata, uint16_t x, uint16_t y)
{
    ಆದರೆ (dispdata->cursor_plane) {  // We can't move a non-existing cursor, but that's ok.
        // Do we have a set of changes already in the making? If not, allocate a new one.
        ಆದರೆ (!dispdata->atomic_req) {
            dispdata->atomic_req = KMSDRM_drm_ಬಹುಲಕ_Atomic_Alloc();
        }
        ಕೂಡಿಸು_plane_property(dispdata->atomic_req, dispdata->cursor_plane, "CRTC_X", x - curdata->hot_x);
        ಕೂಡಿಸು_plane_property(dispdata->atomic_req, dispdata->cursor_plane, "CRTC_Y", y - curdata->hot_y);
    }
}

ಸ್ಥಿರ bool KMSDRM_WarpMouseGlobal(ದಶಮಾಂಶ x, ದಶಮಾಂಶ y)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    ಆದರೆ (mouse && mouse->cur_cursor && mouse->focus) {
        SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = mouse->focus;
        SDL_Display_ದತ್ತಾಂಶ *dispdata = SDL_Get_Display_Driver_ದತ್ತಾಂಶ_For_ಕಿಟಕಿ(ಕಿಟಕಿ);

        // Update internal mouse position.
        SDL_SendMouseMotion(0, mouse->focus, SDL_GLOBAL_MOUSE_ID, false, x, y);

        // And now update the cursor graphic position on screen.
        ಆದರೆ (dispdata->cursor_bo) {
            SDL_VideoDevice *dev = SDL_GetVideoDevice();
            SDL_Video_ದತ್ತಾಂಶ *viddata = dev->ಆಂತರಿಕ;
            ಆದರೆ (USE_ATOMIC_CURSOR && viddata->is_atomic) {
                ಸ್ಥಿರಾಂಕ SDL_Cursor_ದತ್ತಾಂಶ *curdata = (ಸ್ಥಿರಾಂಕ SDL_Cursor_ದತ್ತಾಂಶ *) mouse->cur_cursor->ಆಂತರಿಕ;
                drm_atomic_movecursor(dispdata, curdata, (uint16_t) (ಪೂರ್ಣಾಂಕ) x, (uint16_t) (ಪೂರ್ಣಾಂಕ) y);
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ rc = KMSDRM_drm_ಬಹುಲಕ_Move_Cursor(dispdata->cursor_bo_drm_fd, dispdata->crtc.crtc->crtc_id, (ಪೂರ್ಣಾಂಕ)x, (ಪೂರ್ಣಾಂಕ)y);
                ಆದರೆ (rc < 0) {
                    ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("drmModeMoveCursor() failed: %s", strerror(-rc));
                }
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Cursor not initialized properly.");
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("No mouse or current cursor.");
    }

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool KMSDRM_WarpMouse(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ದಶಮಾಂಶ x, ದಶಮಾಂಶ y)
{
    // Only one global/fullscreen window is supported
    ಹಿಂತಿರುಗಿ KMSDRM_WarpMouseGlobal(x, y);
}

ಶೂನ್ಯ KMSDRM_InitMouse(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Display_ದತ್ತಾಂಶ *dispdata = display->ಆಂತರಿಕ;

    mouse->CreateCursor = KMSDRM_CreateCursor;
    mouse->ShowCursor = KMSDRM_ShowCursor;
    mouse->MoveCursor = KMSDRM_MoveCursor;
    mouse->FreeCursor = KMSDRM_FreeCursor;
    mouse->WarpMouse = KMSDRM_WarpMouse;
    mouse->WarpMouseGlobal = KMSDRM_WarpMouseGlobal;

    /* Only create the default cursor for this display if we haven't done so before,
       we don't want several cursors to be created for the same display. */
    ಆದರೆ (!dispdata->default_cursor_init) {
        SDL_ಗಣ_Default_Cursor(KMSDRM_CreateDefaultCursor());
        dispdata->default_cursor_init = true;
    }
}

ಶೂನ್ಯ KMSDRM_QuitMouse(SDL_VideoDevice *_this)
{
    // TODO: ?
}

// This is called when a mouse motion event occurs
ಸ್ಥಿರ bool KMSDRM_MoveCursor(SDL_Cursor *cursor)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    /* We must NOT call SDL_SendMouseMotion() here or we will enter recursivity!
       That's why we move the cursor graphic ONLY. */
    ಆದರೆ (mouse && mouse->cur_cursor && mouse->focus) {
        SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = mouse->focus;
        SDL_Display_ದತ್ತಾಂಶ *dispdata = SDL_Get_Display_Driver_ದತ್ತಾಂಶ_For_ಕಿಟಕಿ(ಕಿಟಕಿ);
        SDL_VideoDevice *dev = SDL_GetVideoDevice();
        SDL_Video_ದತ್ತಾಂಶ *viddata = dev->ಆಂತರಿಕ;

        ಆದರೆ (!dispdata->cursor_bo) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Cursor not initialized properly.");
        }

        ಆದರೆ (USE_ATOMIC_CURSOR && viddata->is_atomic) {
            /* !!! FIXME: Some programs expect cursor movement even while they don't do SwapWindow() calls,
               and since we ride on the atomic_commit() in SwapWindow() for cursor movement,
               cursor won't move in these situations. We could do an atomic_commit() here
               for each cursor movement request, but it cripples the movement to 30FPS,
               so a future solution is needed. SDLPoP "QUIT?" menu is an example of this
               situation. */
            ಸ್ಥಿರಾಂಕ SDL_Cursor_ದತ್ತಾಂಶ *curdata = (ಸ್ಥಿರಾಂಕ SDL_Cursor_ದತ್ತಾಂಶ *) mouse->cur_cursor->ಆಂತರಿಕ;
            drm_atomic_movecursor(dispdata, curdata, (uint16_t) (ಪೂರ್ಣಾಂಕ) mouse->x, (uint16_t) (ಪೂರ್ಣಾಂಕ) mouse->y);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ rc = KMSDRM_drm_ಬಹುಲಕ_Move_Cursor(dispdata->cursor_bo_drm_fd, dispdata->crtc.crtc->crtc_id, (ಪೂರ್ಣಾಂಕ)mouse->x, (ಪೂರ್ಣಾಂಕ)mouse->y);
            ಆದರೆ (rc < 0) {
                ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("drmModeMoveCursor() failed: %s", strerror(-rc));
            }
        }
    }
    ಹಿಂತಿರುಗಿ true;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_KMSDRM
