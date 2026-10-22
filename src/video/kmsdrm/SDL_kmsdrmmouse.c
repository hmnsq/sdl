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

#अन्तर्भाव "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_KMSDRM

#अन्तर्भाव "SDL_kmsdrmvideo.h"
#अन्तर्भाव "SDL_kmsdrmmouse.h"
#अन्तर्भाव "SDL_kmsdrmdyn.h"

#अन्तर्भाव "../../events/SDL_mouse_c.h"
#अन्तर्भाव "../../events/default_cursor.h"

#अन्तर्भाव "../SDL_pixels_c.h"

// !!! FIXME: atomic cursors are broken right now.
#define USE_ATOMIC_CURSOR 0

स्थिर SDL_Cursor *KMSDRM_CreateDefaultCursor(शून्य);
स्थिर SDL_Cursor *KMSDRM_CreateCursor(SDL_Surface *surface, पूर्णाङ्क hot_x, पूर्णाङ्क hot_y);
स्थिर bool KMSDRM_ShowCursor(SDL_Cursor *cursor);
स्थिर bool KMSDRM_MoveCursor(SDL_Cursor *cursor);
स्थिर शून्य KMSDRM_FreeCursor(SDL_Cursor *cursor);

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

स्थिर SDL_Cursor *KMSDRM_CreateDefaultCursor(शून्य)
{
    प्रत्यागम SDL_CreateCursor(default_cdata, default_cmask, DEFAULT_CWIDTH, DEFAULT_CHEIGHT, DEFAULT_CHOTX, DEFAULT_CHOTY);
}

/* Given a display's internal, destroy the cursor BO for it.
   To be called from KMSDRM_DestroyWindow(), as that's where we
   destroy the internal for the window's display. */
शून्य KMSDRM_DestroyCursorBO(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_DisplayData *dispdata = display->internal;

    // Destroy the curso GBM BO.
    यदि (dispdata->cursor_bo) {
        SDL_VideoData *viddata = (SDL_VideoData *) _this->internal;
        यदि (USE_ATOMIC_CURSOR && viddata->is_atomic) {
            यदि (dispdata->cursor_plane) {
                // Unset the the cursor BO from the cursor plane.
                KMSDRM_PlaneInfo info;
                SDL_zero(info);
                info.plane = dispdata->cursor_plane;
                drm_atomic_set_plane_props(dispdata, &info);
                // Wait until the cursor is unset from the cursor plane before destroying it's BO.
                यदि (drm_atomic_commit(_this, dispdata, true, false)) {
                    SDL_SetError("Failed atomic commit in KMSDRM_DenitMouse.");
                }
                // Free the cursor plane, on which the cursor was being shown.
                free_plane(&dispdata->cursor_plane);
            }
        }

        KMSDRM_gbm_bo_destroy(dispdata->cursor_bo);
        dispdata->cursor_bo = रिक्त;
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

    यदि (USE_ATOMIC_CURSOR && viddata->is_atomic) {
        setup_plane(dev, dispdata, &dispdata->cursor_plane, DRM_PLANE_TYPE_CURSOR);
    }

    यदि (!KMSDRM_gbm_device_is_format_supported(viddata->gbm_dev,
                                               GBM_FORMAT_ARGB8888,
                                               GBM_BO_USE_CURSOR | GBM_BO_USE_WRITE)) {
        प्रत्यागम SDL_SetError("Unsupported pixel format for cursor");
    }

    यदि (KMSDRM_drmGetCap(viddata->drm_fd,
                         DRM_CAP_CURSOR_WIDTH, &dispdata->cursor_w) ||
        KMSDRM_drmGetCap(viddata->drm_fd, DRM_CAP_CURSOR_HEIGHT,
                         &dispdata->cursor_h)) {
        प्रत्यागम SDL_SetError("Could not get the recommended GBM cursor size");
    }

    यदि (dispdata->cursor_w == 0 || dispdata->cursor_h == 0) {
        प्रत्यागम SDL_SetError("Could not get an usable GBM cursor size");
    }

    dispdata->cursor_bo = KMSDRM_gbm_bo_create(viddata->gbm_dev,
                                               dispdata->cursor_w, dispdata->cursor_h,
                                               GBM_FORMAT_ARGB8888, GBM_BO_USE_CURSOR | GBM_BO_USE_WRITE | GBM_BO_USE_LINEAR);

    यदि (!dispdata->cursor_bo) {
        प्रत्यागम SDL_SetError("Could not create GBM cursor BO");
    }

    dispdata->cursor_bo_drm_fd = viddata->drm_fd;
    प्रत्यागम true;
}

// Remove a cursor buffer from a display's DRM cursor BO.
स्थिर bool KMSDRM_RemoveCursorFromBO(SDL_VideoDisplay *display)
{
    bool result = true;

    SDL_DisplayData *dispdata = display->internal;
    SDL_VideoDevice *video_device = SDL_GetVideoDevice();
    SDL_VideoData *viddata = video_device->internal;

    यदि (USE_ATOMIC_CURSOR && viddata->is_atomic) {
        यदि (dispdata->cursor_plane) {
            KMSDRM_PlaneInfo info;
            SDL_zero(info);
            info.plane = dispdata->cursor_plane;
            // The rest of the members are zeroed, so this takes away the cursor from the cursor plane.
            drm_atomic_set_plane_props(dispdata, &info);
            यदि (drm_atomic_commit(video_device, dispdata, true, false)) {
                result = SDL_SetError("Failed atomic commit in KMSDRM_ShowCursor.");
            }
        }
    } अन्यथा {
        ध्रुव पूर्णाङ्क rc = KMSDRM_drmModeSetCursor(viddata->drm_fd, dispdata->crtc.crtc->crtc_id, 0, 0, 0);
        यदि (rc < 0) {
            result = SDL_SetError("drmModeSetCursor() failed: %s", म_त्रुटि(-rc));
        }
    }

    प्रत्यागम result;
}

// Dump a cursor buffer to a display's DRM cursor BO.
स्थिर bool KMSDRM_DumpCursorToBO(SDL_VideoDisplay *display, SDL_Mouse *mouse, SDL_Cursor *cursor)
{
    SDL_DisplayData *dispdata = display->internal;
    SDL_CursorData *curdata = cursor->internal;
    SDL_VideoDevice *video_device = SDL_GetVideoDevice();
    SDL_VideoData *viddata = video_device->internal;

    uint32_t bo_handle;
    माप_प्रकार bo_stride;
    माप_प्रकार bufsize;
    uint8_t *ready_buffer = रिक्त;
    uint8_t *src_row;

    पूर्णाङ्क i, rc;
    bool result = true;

    यदि (!curdata || !dispdata->cursor_bo) {
        प्रत्यागम SDL_SetError("Cursor or display not initialized properly.");
    }

    /* Prepare a buffer we can dump to our GBM BO (different
       size, alpha premultiplication...) */
    bo_stride = KMSDRM_gbm_bo_get_stride(dispdata->cursor_bo);
    bufsize = bo_stride * dispdata->cursor_h;

    ready_buffer = (uint8_t *)SDL_calloc(1, bufsize);

    यदि (!ready_buffer) {
        result = false;
        गच्छ cleanup;
    }

    // Copy from the cursor buffer to a buffer that we can dump to the GBM BO.
    प्रति (i = 0; i < curdata->h; i++) {
        src_row = &((uint8_t *)curdata->buffer)[i * curdata->w * 4];
        SDL_memcpy(ready_buffer + (i * bo_stride), src_row, (माप_प्रकार)4 * curdata->w);
    }

    // Dump the cursor buffer to our GBM BO.
    यदि (KMSDRM_gbm_bo_write(dispdata->cursor_bo, ready_buffer, bufsize)) {
        result = SDL_SetError("Could not write to GBM cursor BO");
        गच्छ cleanup;
    }

    यदि (USE_ATOMIC_CURSOR && viddata->is_atomic) {
        // Get the fb_id for the GBM BO so we can show it on the cursor plane.
        KMSDRM_FBInfo *fb = KMSDRM_FBFromBO(video_device, dispdata->cursor_bo);
        KMSDRM_PlaneInfo info;

        यदि (!fb) {
            result = SDL_SetError("Failed to get cursor FB from BO");
            गच्छ cleanup;
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
        यदि (drm_atomic_commit(video_device, dispdata, true, false)) {
            result = SDL_SetError("Failed atomic commit in KMSDRM_ShowCursor.");
            गच्छ cleanup;
        }
    } अन्यथा {
        // Put the GBM BO buffer on screen using the DRM interface.
        bo_handle = KMSDRM_gbm_bo_get_handle(dispdata->cursor_bo).u32;
        यदि (curdata->hot_x == 0 && curdata->hot_y == 0) {
            rc = KMSDRM_drmModeSetCursor(viddata->drm_fd, dispdata->crtc.crtc->crtc_id, bo_handle, dispdata->cursor_w, dispdata->cursor_h);
        } अन्यथा {
            rc = KMSDRM_drmModeSetCursor2(viddata->drm_fd, dispdata->crtc.crtc->crtc_id, bo_handle, dispdata->cursor_w, dispdata->cursor_h, curdata->hot_x, curdata->hot_y);
        }
        यदि (rc < 0) {
            result = SDL_SetError("Failed to set DRM cursor: %s", म_त्रुटि(-rc));
            गच्छ cleanup;
        }
    }

cleanup:
    SDL_free(ready_buffer);
    प्रत्यागम result;
}

// This is only for freeing the SDL_cursor.
स्थिर शून्य KMSDRM_FreeCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *curdata;

    // Even if the cursor is not ours, free it.
    यदि (cursor) {
        curdata = cursor->internal;
        // Free cursor buffer
        यदि (curdata->buffer) {
            SDL_free(curdata->buffer);
            curdata->buffer = रिक्त;
        }
        // Free cursor itself
        SDL_free(cursor->internal);
        SDL_free(cursor);
    }
}

/* This simply gets the cursor soft-buffer ready.
   We don't copy it to a GBO BO until ShowCursor() because the cusor GBM BO (living
   in dispata) is destroyed and recreated when we recreate windows, etc. */
स्थिर SDL_Cursor *KMSDRM_CreateCursor(SDL_Surface *surface, पूर्णाङ्क hot_x, पूर्णाङ्क hot_y)
{
    SDL_CursorData *curdata;
    SDL_Cursor *cursor, *result;

    curdata = रिक्त;
    result = रिक्त;

    cursor = (SDL_Cursor *)SDL_calloc(1, परिमाण(*cursor));
    यदि (!cursor) {
        गच्छ cleanup;
    }
    curdata = (SDL_CursorData *)SDL_calloc(1, परिमाण(*curdata));
    यदि (!curdata) {
        गच्छ cleanup;
    }

    // hox_x and hot_y are the coordinates of the "tip of the cursor" from it's base.
    curdata->hot_x = hot_x;
    curdata->hot_y = hot_y;
    curdata->w = surface->w;
    curdata->h = surface->h;
    curdata->buffer = रिक्त;

    /* Configure the cursor buffer info.
       This buffer has the original size of the cursor surface we are given. */
    curdata->buffer_pitch = surface->w;
    curdata->buffer_size = (माप_प्रकार)surface->w * surface->h * 4;
    curdata->buffer = (uint32_t *)SDL_malloc(curdata->buffer_size);

    यदि (!curdata->buffer) {
        गच्छ cleanup;
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
    यदि (!result) {
        यदि (curdata) {
            SDL_free(curdata->buffer);
            SDL_free(curdata);
        }
        SDL_free(cursor);
    }

    प्रत्यागम result;
}

// Show the specified cursor, or hide if cursor is NULL or has no focus.
स्थिर bool KMSDRM_ShowCursor(SDL_Cursor *cursor)
{
    SDL_VideoDisplay *display;
    SDL_Window *window;
    SDL_Mouse *mouse = SDL_GetMouse();

    पूर्णाङ्क i;
    bool result = true;

    // Get the mouse focused window, if any.
    window = mouse->focus;

    यदि (!window || !cursor) {
        /* If no window is focused by mouse or cursor is NULL,
           since we have no window (no mouse->focus) and hence
           we have no display, we simply hide mouse on all displays.
           This happens on video quit, where we get here after
           the mouse focus has been unset, yet SDL wants to
           restore the system default cursor (makes no sense here). */
        SDL_DisplayID *displays = SDL_GetDisplays(रिक्त);
        यदि (displays) {
            // Iterate on the displays, hiding the cursor.
            प्रति (i = 0; i < displays[i]; i++) {
                display = SDL_GetVideoDisplay(displays[i]);
                result = KMSDRM_RemoveCursorFromBO(display);
            }
            SDL_free(displays);
        }
    } अन्यथा {
        display = SDL_GetVideoDisplayForWindow(window);
        यदि (display) {
            यदि (cursor) {
                /* Dump the cursor to the display DRM cursor BO so it becomes visible
                   on that display. */
                result = KMSDRM_DumpCursorToBO(display, mouse, cursor);
            } अन्यथा {
                // Hide the cursor on that display.
                result = KMSDRM_RemoveCursorFromBO(display);
            }
        }
    }

    प्रत्यागम result;
}

स्थिर शून्य drm_atomic_movecursor(SDL_DisplayData *dispdata, ध्रुव SDL_CursorData *curdata, uint16_t x, uint16_t y)
{
    यदि (dispdata->cursor_plane) {  // We can't move a non-existing cursor, but that's ok.
        // Do we have a set of changes already in the making? If not, allocate a new one.
        यदि (!dispdata->atomic_req) {
            dispdata->atomic_req = KMSDRM_drmModeAtomicAlloc();
        }
        add_plane_property(dispdata->atomic_req, dispdata->cursor_plane, "CRTC_X", x - curdata->hot_x);
        add_plane_property(dispdata->atomic_req, dispdata->cursor_plane, "CRTC_Y", y - curdata->hot_y);
    }
}

स्थिर bool KMSDRM_WarpMouseGlobal(भिन्न x, भिन्न y)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    यदि (mouse && mouse->cur_cursor && mouse->focus) {
        SDL_Window *window = mouse->focus;
        SDL_DisplayData *dispdata = SDL_GetDisplayDriverDataForWindow(window);

        // Update internal mouse position.
        SDL_SendMouseMotion(0, mouse->focus, SDL_GLOBAL_MOUSE_ID, false, x, y);

        // And now update the cursor graphic position on screen.
        यदि (dispdata->cursor_bo) {
            SDL_VideoDevice *dev = SDL_GetVideoDevice();
            SDL_VideoData *viddata = dev->internal;
            यदि (USE_ATOMIC_CURSOR && viddata->is_atomic) {
                ध्रुव SDL_CursorData *curdata = (ध्रुव SDL_CursorData *) mouse->cur_cursor->internal;
                drm_atomic_movecursor(dispdata, curdata, (uint16_t) (पूर्णाङ्क) x, (uint16_t) (पूर्णाङ्क) y);
            } अन्यथा {
                ध्रुव पूर्णाङ्क rc = KMSDRM_drmModeMoveCursor(dispdata->cursor_bo_drm_fd, dispdata->crtc.crtc->crtc_id, (पूर्णाङ्क)x, (पूर्णाङ्क)y);
                यदि (rc < 0) {
                    प्रत्यागम SDL_SetError("drmModeMoveCursor() failed: %s", म_त्रुटि(-rc));
                }
            }
        } अन्यथा {
            प्रत्यागम SDL_SetError("Cursor not initialized properly.");
        }
    } अन्यथा {
        प्रत्यागम SDL_SetError("No mouse or current cursor.");
    }

    प्रत्यागम true;
}

स्थिर bool KMSDRM_WarpMouse(SDL_Window *window, भिन्न x, भिन्न y)
{
    // Only one global/fullscreen window is supported
    प्रत्यागम KMSDRM_WarpMouseGlobal(x, y);
}

शून्य KMSDRM_InitMouse(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
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
    यदि (!dispdata->default_cursor_init) {
        SDL_SetDefaultCursor(KMSDRM_CreateDefaultCursor());
        dispdata->default_cursor_init = true;
    }
}

शून्य KMSDRM_QuitMouse(SDL_VideoDevice *_this)
{
    // TODO: ?
}

// This is called when a mouse motion event occurs
स्थिर bool KMSDRM_MoveCursor(SDL_Cursor *cursor)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    /* We must NOT call SDL_SendMouseMotion() here or we will enter recursivity!
       That's why we move the cursor graphic ONLY. */
    यदि (mouse && mouse->cur_cursor && mouse->focus) {
        SDL_Window *window = mouse->focus;
        SDL_DisplayData *dispdata = SDL_GetDisplayDriverDataForWindow(window);
        SDL_VideoDevice *dev = SDL_GetVideoDevice();
        SDL_VideoData *viddata = dev->internal;

        यदि (!dispdata->cursor_bo) {
            प्रत्यागम SDL_SetError("Cursor not initialized properly.");
        }

        यदि (USE_ATOMIC_CURSOR && viddata->is_atomic) {
            /* !!! FIXME: Some programs expect cursor movement even while they don't do SwapWindow() calls,
               and since we ride on the atomic_commit() in SwapWindow() for cursor movement,
               cursor won't move in these situations. We could do an atomic_commit() here
               for each cursor movement request, but it cripples the movement to 30FPS,
               so a future solution is needed. SDLPoP "QUIT?" menu is an example of this
               situation. */
            ध्रुव SDL_CursorData *curdata = (ध्रुव SDL_CursorData *) mouse->cur_cursor->internal;
            drm_atomic_movecursor(dispdata, curdata, (uint16_t) (पूर्णाङ्क) mouse->x, (uint16_t) (पूर्णाङ्क) mouse->y);
        } अन्यथा {
            ध्रुव पूर्णाङ्क rc = KMSDRM_drmModeMoveCursor(dispdata->cursor_bo_drm_fd, dispdata->crtc.crtc->crtc_id, (पूर्णाङ्क)mouse->x, (पूर्णाङ्क)mouse->y);
            यदि (rc < 0) {
                प्रत्यागम SDL_SetError("drmModeMoveCursor() failed: %s", म_त्रुटि(-rc));
            }
        }
    }
    प्रत्यागम true;
}

#endif // SDL_VIDEO_DRIVER_KMSDRM
