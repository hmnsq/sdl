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

#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_KMSDRM

#അന്തര്ഭാവ "SDL_kmsdrmvideo.h"
#അന്തര്ഭാവ "SDL_kmsdrmmouse.h"
#അന്തര്ഭാവ "SDL_kmsdrmdyn.h"

#അന്തര്ഭാവ "../../events/SDL_mouse_c.h"
#അന്തര്ഭാവ "../../events/default_cursor.h"

#അന്തര്ഭാവ "../SDL_pixels_c.h"

// !!! FIXME: atomic cursors are broken right now.
#define USE_ATOMIC_CURSOR 0

സ്ഥിതം SDL_Cursor *KMSDRM_CreateDefaultCursor(ശൂന്യം);
സ്ഥിതം SDL_Cursor *KMSDRM_CreateCursor(SDL_Surface *surface, പൂർണ്ണസംഖ്യ hot_x, പൂർണ്ണസംഖ്യ hot_y);
സ്ഥിതം bool KMSDRM_ShowCursor(SDL_Cursor *cursor);
സ്ഥിതം bool KMSDRM_MoveCursor(SDL_Cursor *cursor);
സ്ഥിതം ശൂന്യം KMSDRM_FreeCursor(SDL_Cursor *cursor);

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

സ്ഥിതം SDL_Cursor *KMSDRM_CreateDefaultCursor(ശൂന്യം)
{
    തിരികെ SDL_CreateCursor(default_cdata, default_cmask, DEFAULT_CWIDTH, DEFAULT_CHEIGHT, DEFAULT_CHOTX, DEFAULT_CHOTY);
}

/* Given a display's internal, destroy the cursor BO for it.
   To be called from KMSDRM_DestroyWindow(), as that's where we
   destroy the internal for the window's display. */
ശൂന്യം KMSDRM_DestroyCursorBO(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_DisplayData *dispdata = display->internal;

    // Destroy the curso GBM BO.
    എങ്കിൽ (dispdata->cursor_bo) {
        SDL_VideoData *viddata = (SDL_VideoData *) _this->internal;
        എങ്കിൽ (USE_ATOMIC_CURSOR && viddata->is_atomic) {
            എങ്കിൽ (dispdata->cursor_plane) {
                // Unset the the cursor BO from the cursor plane.
                KMSDRM_PlaneInfo info;
                SDL_zero(info);
                info.plane = dispdata->cursor_plane;
                drm_atomic_set_plane_props(dispdata, &info);
                // Wait until the cursor is unset from the cursor plane before destroying it's BO.
                എങ്കിൽ (drm_atomic_commit(_this, dispdata, true, false)) {
                    SDL_SetError("Failed atomic commit in KMSDRM_DenitMouse.");
                }
                // Free the cursor plane, on which the cursor was being shown.
                free_plane(&dispdata->cursor_plane);
            }
        }

        KMSDRM_gbm_bo_destroy(dispdata->cursor_bo);
        dispdata->cursor_bo = ശൂന്യ;
        dispdata->cursor_bo_drm_fd = -1;
    }
}

/* Given a display's internal, create the cursor BO for it.
   To be called from KMSDRM_CreateWindow(), as that's where we
   build a window and assign a display to it. */
bool KMSDRM_CreateCursorBO(SDL_VideoDisplay *display)
{
    SDL_VideoDevice *dev = SDL_GetVideoDevice();
    SDL_VideoData *viddata = dev->internal;
    SDL_DisplayData *dispdata = display->internal;

    എങ്കിൽ (USE_ATOMIC_CURSOR && viddata->is_atomic) {
        setup_plane(dev, dispdata, &dispdata->cursor_plane, DRM_PLANE_TYPE_CURSOR);
    }

    എങ്കിൽ (!KMSDRM_gbm_device_is_format_supported(viddata->gbm_dev,
                                               GBM_FORMAT_ARGB8888,
                                               GBM_BO_USE_CURSOR | GBM_BO_USE_WRITE)) {
        തിരികെ SDL_SetError("Unsupported pixel format for cursor");
    }

    എങ്കിൽ (KMSDRM_drmGetCap(viddata->drm_fd,
                         DRM_CAP_CURSOR_WIDTH, &dispdata->cursor_w) ||
        KMSDRM_drmGetCap(viddata->drm_fd, DRM_CAP_CURSOR_HEIGHT,
                         &dispdata->cursor_h)) {
        തിരികെ SDL_SetError("Could not get the recommended GBM cursor size");
    }

    എങ്കിൽ (dispdata->cursor_w == 0 || dispdata->cursor_h == 0) {
        തിരികെ SDL_SetError("Could not get an usable GBM cursor size");
    }

    dispdata->cursor_bo = KMSDRM_gbm_bo_create(viddata->gbm_dev,
                                               dispdata->cursor_w, dispdata->cursor_h,
                                               GBM_FORMAT_ARGB8888, GBM_BO_USE_CURSOR | GBM_BO_USE_WRITE | GBM_BO_USE_LINEAR);

    എങ്കിൽ (!dispdata->cursor_bo) {
        തിരികെ SDL_SetError("Could not create GBM cursor BO");
    }

    dispdata->cursor_bo_drm_fd = viddata->drm_fd;
    തിരികെ true;
}

// Remove a cursor buffer from a display's DRM cursor BO.
സ്ഥിതം bool KMSDRM_RemoveCursorFromBO(SDL_VideoDisplay *display)
{
    bool result = true;

    SDL_DisplayData *dispdata = display->internal;
    SDL_VideoDevice *video_device = SDL_GetVideoDevice();
    SDL_VideoData *viddata = video_device->internal;

    എങ്കിൽ (USE_ATOMIC_CURSOR && viddata->is_atomic) {
        എങ്കിൽ (dispdata->cursor_plane) {
            KMSDRM_PlaneInfo info;
            SDL_zero(info);
            info.plane = dispdata->cursor_plane;
            // The rest of the members are zeroed, so this takes away the cursor from the cursor plane.
            drm_atomic_set_plane_props(dispdata, &info);
            എങ്കിൽ (drm_atomic_commit(video_device, dispdata, true, false)) {
                result = SDL_SetError("Failed atomic commit in KMSDRM_ShowCursor.");
            }
        }
    } അല്ലെങ്കിൽ {
        സ്ഥിരം പൂർണ്ണസംഖ്യ rc = KMSDRM_drmModeSetCursor(viddata->drm_fd, dispdata->crtc.crtc->crtc_id, 0, 0, 0);
        എങ്കിൽ (rc < 0) {
            result = SDL_SetError("drmModeSetCursor() failed: %s", strerror(-rc));
        }
    }

    തിരികെ result;
}

// Dump a cursor buffer to a display's DRM cursor BO.
സ്ഥിതം bool KMSDRM_DumpCursorToBO(SDL_VideoDisplay *display, SDL_Mouse *mouse, SDL_Cursor *cursor)
{
    SDL_DisplayData *dispdata = display->internal;
    SDL_CursorData *curdata = cursor->internal;
    SDL_VideoDevice *video_device = SDL_GetVideoDevice();
    SDL_VideoData *viddata = video_device->internal;

    uint32_t bo_handle;
    size_t bo_stride;
    size_t bufsize;
    uint8_t *ready_buffer = ശൂന്യ;
    uint8_t *src_row;

    പൂർണ്ണസംഖ്യ i, rc;
    bool result = true;

    എങ്കിൽ (!curdata || !dispdata->cursor_bo) {
        തിരികെ SDL_SetError("Cursor or display not initialized properly.");
    }

    /* Prepare a buffer we can dump to our GBM BO (different
       size, alpha premultiplication...) */
    bo_stride = KMSDRM_gbm_bo_get_stride(dispdata->cursor_bo);
    bufsize = bo_stride * dispdata->cursor_h;

    ready_buffer = (uint8_t *)SDL_calloc(1, bufsize);

    എങ്കിൽ (!ready_buffer) {
        result = false;
        പോകുക cleanup;
    }

    // Copy from the cursor buffer to a buffer that we can dump to the GBM BO.
    വേണ്ടി (i = 0; i < curdata->h; i++) {
        src_row = &((uint8_t *)curdata->buffer)[i * curdata->w * 4];
        SDL_memcpy(ready_buffer + (i * bo_stride), src_row, (size_t)4 * curdata->w);
    }

    // Dump the cursor buffer to our GBM BO.
    എങ്കിൽ (KMSDRM_gbm_bo_write(dispdata->cursor_bo, ready_buffer, bufsize)) {
        result = SDL_SetError("Could not write to GBM cursor BO");
        പോകുക cleanup;
    }

    എങ്കിൽ (USE_ATOMIC_CURSOR && viddata->is_atomic) {
        // Get the fb_id for the GBM BO so we can show it on the cursor plane.
        KMSDRM_FBInfo *fb = KMSDRM_FBFromBO(video_device, dispdata->cursor_bo);
        KMSDRM_PlaneInfo info;

        എങ്കിൽ (!fb) {
            result = SDL_SetError("Failed to get cursor FB from BO");
            പോകുക cleanup;
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
        എങ്കിൽ (drm_atomic_commit(video_device, dispdata, true, false)) {
            result = SDL_SetError("Failed atomic commit in KMSDRM_ShowCursor.");
            പോകുക cleanup;
        }
    } അല്ലെങ്കിൽ {
        // Put the GBM BO buffer on screen using the DRM interface.
        bo_handle = KMSDRM_gbm_bo_get_handle(dispdata->cursor_bo).u32;
        എങ്കിൽ (curdata->hot_x == 0 && curdata->hot_y == 0) {
            rc = KMSDRM_drmModeSetCursor(viddata->drm_fd, dispdata->crtc.crtc->crtc_id, bo_handle, dispdata->cursor_w, dispdata->cursor_h);
        } അല്ലെങ്കിൽ {
            rc = KMSDRM_drmModeSetCursor2(viddata->drm_fd, dispdata->crtc.crtc->crtc_id, bo_handle, dispdata->cursor_w, dispdata->cursor_h, curdata->hot_x, curdata->hot_y);
        }
        എങ്കിൽ (rc < 0) {
            result = SDL_SetError("Failed to set DRM cursor: %s", strerror(-rc));
            പോകുക cleanup;
        }
    }

cleanup:
    SDL_free(ready_buffer);
    തിരികെ result;
}

// This is only for freeing the SDL_cursor.
സ്ഥിതം ശൂന്യം KMSDRM_FreeCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *curdata;

    // Even if the cursor is not ours, free it.
    എങ്കിൽ (cursor) {
        curdata = cursor->internal;
        // Free cursor buffer
        എങ്കിൽ (curdata->buffer) {
            SDL_free(curdata->buffer);
            curdata->buffer = ശൂന്യ;
        }
        // Free cursor itself
        SDL_free(cursor->internal);
        SDL_free(cursor);
    }
}

/* This simply gets the cursor soft-buffer ready.
   We don't copy it to a GBO BO until ShowCursor() because the cusor GBM BO (living
   in dispata) is destroyed and recreated when we recreate windows, etc. */
സ്ഥിതം SDL_Cursor *KMSDRM_CreateCursor(SDL_Surface *surface, പൂർണ്ണസംഖ്യ hot_x, പൂർണ്ണസംഖ്യ hot_y)
{
    SDL_CursorData *curdata;
    SDL_Cursor *cursor, *result;

    curdata = ശൂന്യ;
    result = ശൂന്യ;

    cursor = (SDL_Cursor *)SDL_calloc(1, വലുപ്പം(*cursor));
    എങ്കിൽ (!cursor) {
        പോകുക cleanup;
    }
    curdata = (SDL_CursorData *)SDL_calloc(1, വലുപ്പം(*curdata));
    എങ്കിൽ (!curdata) {
        പോകുക cleanup;
    }

    // hox_x and hot_y are the coordinates of the "tip of the cursor" from it's base.
    curdata->hot_x = hot_x;
    curdata->hot_y = hot_y;
    curdata->w = surface->w;
    curdata->h = surface->h;
    curdata->buffer = ശൂന്യ;

    /* Configure the cursor buffer info.
       This buffer has the original size of the cursor surface we are given. */
    curdata->buffer_pitch = surface->w;
    curdata->buffer_size = (size_t)surface->w * surface->h * 4;
    curdata->buffer = (uint32_t *)SDL_malloc(curdata->buffer_size);

    എങ്കിൽ (!curdata->buffer) {
        പോകുക cleanup;
    }

    /* All code below assumes ARGB8888 format for the cursor surface,
       like other backends do. Also, the GBM BO pixels have to be
       alpha-premultiplied, but the SDL surface we receive has
       straight-alpha pixels, so we always have to convert. */
    SDL_PremultiplyAlpha(surface->w, surface->h,
                         surface->format, surface->pixels, surface->pitch,
                         SDL_PIXELFORMAT_ARGB8888, curdata->buffer, surface->w * 4, true);

    cursor->internal = curdata;

    result = cursor;

cleanup:
    എങ്കിൽ (!result) {
        എങ്കിൽ (curdata) {
            SDL_free(curdata->buffer);
            SDL_free(curdata);
        }
        SDL_free(cursor);
    }

    തിരികെ result;
}

// Show the specified cursor, or hide if cursor is NULL or has no focus.
സ്ഥിതം bool KMSDRM_ShowCursor(SDL_Cursor *cursor)
{
    SDL_VideoDisplay *display;
    SDL_Window *window;
    SDL_Mouse *mouse = SDL_GetMouse();

    പൂർണ്ണസംഖ്യ i;
    bool result = true;

    // Get the mouse focused window, if any.
    window = mouse->focus;

    എങ്കിൽ (!window || !cursor) {
        /* If no window is focused by mouse or cursor is NULL,
           since we have no window (no mouse->focus) and hence
           we have no display, we simply hide mouse on all displays.
           This happens on video quit, where we get here after
           the mouse focus has been unset, yet SDL wants to
           restore the system default cursor (makes no sense here). */
        SDL_DisplayID *displays = SDL_GetDisplays(ശൂന്യ);
        എങ്കിൽ (displays) {
            // Iterate on the displays, hiding the cursor.
            വേണ്ടി (i = 0; i < displays[i]; i++) {
                display = SDL_GetVideoDisplay(displays[i]);
                result = KMSDRM_RemoveCursorFromBO(display);
            }
            SDL_free(displays);
        }
    } അല്ലെങ്കിൽ {
        display = SDL_GetVideoDisplayForWindow(window);
        എങ്കിൽ (display) {
            എങ്കിൽ (cursor) {
                /* Dump the cursor to the display DRM cursor BO so it becomes visible
                   on that display. */
                result = KMSDRM_DumpCursorToBO(display, mouse, cursor);
            } അല്ലെങ്കിൽ {
                // Hide the cursor on that display.
                result = KMSDRM_RemoveCursorFromBO(display);
            }
        }
    }

    തിരികെ result;
}

സ്ഥിതം ശൂന്യം drm_atomic_movecursor(SDL_DisplayData *dispdata, സ്ഥിരം SDL_CursorData *curdata, uint16_t x, uint16_t y)
{
    എങ്കിൽ (dispdata->cursor_plane) {  // We can't move a non-existing cursor, but that's ok.
        // Do we have a set of changes already in the making? If not, allocate a new one.
        എങ്കിൽ (!dispdata->atomic_req) {
            dispdata->atomic_req = KMSDRM_drmModeAtomicAlloc();
        }
        add_plane_property(dispdata->atomic_req, dispdata->cursor_plane, "CRTC_X", x - curdata->hot_x);
        add_plane_property(dispdata->atomic_req, dispdata->cursor_plane, "CRTC_Y", y - curdata->hot_y);
    }
}

സ്ഥിതം bool KMSDRM_WarpMouseGlobal(ദശാംശം x, ദശാംശം y)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    എങ്കിൽ (mouse && mouse->cur_cursor && mouse->focus) {
        SDL_Window *window = mouse->focus;
        SDL_DisplayData *dispdata = SDL_GetDisplayDriverDataForWindow(window);

        // Update internal mouse position.
        SDL_SendMouseMotion(0, mouse->focus, SDL_GLOBAL_MOUSE_ID, false, x, y);

        // And now update the cursor graphic position on screen.
        എങ്കിൽ (dispdata->cursor_bo) {
            SDL_VideoDevice *dev = SDL_GetVideoDevice();
            SDL_VideoData *viddata = dev->internal;
            എങ്കിൽ (USE_ATOMIC_CURSOR && viddata->is_atomic) {
                സ്ഥിരം SDL_CursorData *curdata = (സ്ഥിരം SDL_CursorData *) mouse->cur_cursor->internal;
                drm_atomic_movecursor(dispdata, curdata, (uint16_t) (പൂർണ്ണസംഖ്യ) x, (uint16_t) (പൂർണ്ണസംഖ്യ) y);
            } അല്ലെങ്കിൽ {
                സ്ഥിരം പൂർണ്ണസംഖ്യ rc = KMSDRM_drmModeMoveCursor(dispdata->cursor_bo_drm_fd, dispdata->crtc.crtc->crtc_id, (പൂർണ്ണസംഖ്യ)x, (പൂർണ്ണസംഖ്യ)y);
                എങ്കിൽ (rc < 0) {
                    തിരികെ SDL_SetError("drmModeMoveCursor() failed: %s", strerror(-rc));
                }
            }
        } അല്ലെങ്കിൽ {
            തിരികെ SDL_SetError("Cursor not initialized properly.");
        }
    } അല്ലെങ്കിൽ {
        തിരികെ SDL_SetError("No mouse or current cursor.");
    }

    തിരികെ true;
}

സ്ഥിതം bool KMSDRM_WarpMouse(SDL_Window *window, ദശാംശം x, ദശാംശം y)
{
    // Only one global/fullscreen window is supported
    തിരികെ KMSDRM_WarpMouseGlobal(x, y);
}

ശൂന്യം KMSDRM_InitMouse(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_DisplayData *dispdata = display->internal;

    mouse->CreateCursor = KMSDRM_CreateCursor;
    mouse->ShowCursor = KMSDRM_ShowCursor;
    mouse->MoveCursor = KMSDRM_MoveCursor;
    mouse->FreeCursor = KMSDRM_FreeCursor;
    mouse->WarpMouse = KMSDRM_WarpMouse;
    mouse->WarpMouseGlobal = KMSDRM_WarpMouseGlobal;

    /* Only create the default cursor for this display if we haven't done so before,
       we don't want several cursors to be created for the same display. */
    എങ്കിൽ (!dispdata->default_cursor_init) {
        SDL_SetDefaultCursor(KMSDRM_CreateDefaultCursor());
        dispdata->default_cursor_init = true;
    }
}

ശൂന്യം KMSDRM_QuitMouse(SDL_VideoDevice *_this)
{
    // TODO: ?
}

// This is called when a mouse motion event occurs
സ്ഥിതം bool KMSDRM_MoveCursor(SDL_Cursor *cursor)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    /* We must NOT call SDL_SendMouseMotion() here or we will enter recursivity!
       That's why we move the cursor graphic ONLY. */
    എങ്കിൽ (mouse && mouse->cur_cursor && mouse->focus) {
        SDL_Window *window = mouse->focus;
        SDL_DisplayData *dispdata = SDL_GetDisplayDriverDataForWindow(window);
        SDL_VideoDevice *dev = SDL_GetVideoDevice();
        SDL_VideoData *viddata = dev->internal;

        എങ്കിൽ (!dispdata->cursor_bo) {
            തിരികെ SDL_SetError("Cursor not initialized properly.");
        }

        എങ്കിൽ (USE_ATOMIC_CURSOR && viddata->is_atomic) {
            /* !!! FIXME: Some programs expect cursor movement even while they don't do SwapWindow() calls,
               and since we ride on the atomic_commit() in SwapWindow() for cursor movement,
               cursor won't move in these situations. We could do an atomic_commit() here
               for each cursor movement request, but it cripples the movement to 30FPS,
               so a future solution is needed. SDLPoP "QUIT?" menu is an example of this
               situation. */
            സ്ഥിരം SDL_CursorData *curdata = (സ്ഥിരം SDL_CursorData *) mouse->cur_cursor->internal;
            drm_atomic_movecursor(dispdata, curdata, (uint16_t) (പൂർണ്ണസംഖ്യ) mouse->x, (uint16_t) (പൂർണ്ണസംഖ്യ) mouse->y);
        } അല്ലെങ്കിൽ {
            സ്ഥിരം പൂർണ്ണസംഖ്യ rc = KMSDRM_drmModeMoveCursor(dispdata->cursor_bo_drm_fd, dispdata->crtc.crtc->crtc_id, (പൂർണ്ണസംഖ്യ)mouse->x, (പൂർണ്ണസംഖ്യ)mouse->y);
            എങ്കിൽ (rc < 0) {
                തിരികെ SDL_SetError("drmModeMoveCursor() failed: %s", strerror(-rc));
            }
        }
    }
    തിരികെ true;
}

#endif // SDL_VIDEO_DRIVER_KMSDRM
