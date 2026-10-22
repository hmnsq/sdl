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

#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_KMSDRM

#అన్తర్భావ "SDL_kmsdrmvideo.h"
#అన్తర్భావ "SDL_kmsdrmmouse.h"
#అన్తర్భావ "SDL_kmsdrmdyn.h"

#అన్తర్భావ "../../events/SDL_mouse_c.h"
#అన్తర్భావ "../../events/default_cursor.h"

#అన్తర్భావ "../SDL_pixels_c.h"

// !!! FIXME: atomic cursors are broken right now.
#నిర్వచించు USE_ATOMIC_CURSOR 0

స్థిర SDL_Cursor *KMSDRM_CreateDefaultCursor(శూన్య);
స్థిర SDL_Cursor *KMSDRM_CreateCursor(SDL_Surface *surface, పూర్ణాంకం hot_x, పూర్ణాంకం hot_y);
స్థిర bool KMSDRM_ShowCursor(SDL_Cursor *cursor);
స్థిర bool KMSDRM_MoveCursor(SDL_Cursor *cursor);
స్థిర శూన్య KMSDRM_FreeCursor(SDL_Cursor *cursor);

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

స్థిర SDL_Cursor *KMSDRM_CreateDefaultCursor(శూన్య)
{
    తిరిగి SDL_CreateCursor(default_cdata, default_cmask, DEFAULT_CWIDTH, DEFAULT_CHEIGHT, DEFAULT_CHOTX, DEFAULT_CHOTY);
}

/* Given a display's internal, destroy the cursor BO for it.
   To be called from KMSDRM_DestroyWindow(), as that's where we
   destroy the internal for the window's display. */
శూన్య KMSDRM_DestroyCursorBO(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_దత్తాంశం *dispdata = display->అంతర్గత;

    // Destroy the curso GBM BO.
    ఒకవేళ (dispdata->cursor_bo) {
        SDL_Video_దత్తాంశం *viddata = (SDL_Video_దత్తాంశం *) _this->అంతర్గత;
        ఒకవేళ (USE_ATOMIC_CURSOR && viddata->is_atomic) {
            ఒకవేళ (dispdata->cursor_plane) {
                // Unset the the cursor BO from the cursor plane.
                KMSDRM_PlaneInfo info;
                SDL_zero(info);
                info.plane = dispdata->cursor_plane;
                drm_atomic_సమితి_plane_props(dispdata, &info);
                // Wait until the cursor is unset from the cursor plane before destroying it's BO.
                ఒకవేళ (drm_atomic_commit(_this, dispdata, true, false)) {
                    SDL_సమితి_Error("Failed atomic commit in KMSDRM_DenitMouse.");
                }
                // Free the cursor plane, on which the cursor was being shown.
                free_plane(&dispdata->cursor_plane);
            }
        }

        KMSDRM_gbm_bo_destroy(dispdata->cursor_bo);
        dispdata->cursor_bo = ఖాళీ;
        dispdata->cursor_bo_drm_fd = -1;
    }
}

/* Given a display's internal, create the cursor BO for it.
   To be called from KMSDRM_CreateWindow(), as that's where we
   build a window and assign a display to it. */
bool KMSDRM_CreateCursorBO(SDL_VideoDisplay *display)
{
    SDL_VideoDevice *dev = SDL_GetVideoDevice();
    SDL_Video_దత్తాంశం *viddata = dev->అంతర్గత;
    SDL_Display_దత్తాంశం *dispdata = display->అంతర్గత;

    ఒకవేళ (USE_ATOMIC_CURSOR && viddata->is_atomic) {
        అమరిక_plane(dev, dispdata, &dispdata->cursor_plane, DRM_PLANE_TYPE_CURSOR);
    }

    ఒకవేళ (!KMSDRM_gbm_device_is_format_supported(viddata->gbm_dev,
                                               GBM_FORMAT_ARGB8888,
                                               GBM_BO_USE_CURSOR | GBM_BO_USE_WRITE)) {
        తిరిగి SDL_సమితి_Error("Unsupported pixel format for cursor");
    }

    ఒకవేళ (KMSDRM_drmGetCap(viddata->drm_fd,
                         DRM_CAP_CURSOR_వెడల్పు, &dispdata->cursor_w) ||
        KMSDRM_drmGetCap(viddata->drm_fd, DRM_CAP_CURSOR_ఎత్తు,
                         &dispdata->cursor_h)) {
        తిరిగి SDL_సమితి_Error("Could not get the recommended GBM cursor size");
    }

    ఒకవేళ (dispdata->cursor_w == 0 || dispdata->cursor_h == 0) {
        తిరిగి SDL_సమితి_Error("Could not get an usable GBM cursor size");
    }

    dispdata->cursor_bo = KMSDRM_gbm_bo_create(viddata->gbm_dev,
                                               dispdata->cursor_w, dispdata->cursor_h,
                                               GBM_FORMAT_ARGB8888, GBM_BO_USE_CURSOR | GBM_BO_USE_WRITE | GBM_BO_USE_రేఖీయ);

    ఒకవేళ (!dispdata->cursor_bo) {
        తిరిగి SDL_సమితి_Error("Could not create GBM cursor BO");
    }

    dispdata->cursor_bo_drm_fd = viddata->drm_fd;
    తిరిగి true;
}

// Remove a cursor buffer from a display's DRM cursor BO.
స్థిర bool KMSDRM_RemoveCursorFromBO(SDL_VideoDisplay *display)
{
    bool ఫలితం = true;

    SDL_Display_దత్తాంశం *dispdata = display->అంతర్గత;
    SDL_VideoDevice *video_device = SDL_GetVideoDevice();
    SDL_Video_దత్తాంశం *viddata = video_device->అంతర్గత;

    ఒకవేళ (USE_ATOMIC_CURSOR && viddata->is_atomic) {
        ఒకవేళ (dispdata->cursor_plane) {
            KMSDRM_PlaneInfo info;
            SDL_zero(info);
            info.plane = dispdata->cursor_plane;
            // The rest of the members are zeroed, so this takes away the cursor from the cursor plane.
            drm_atomic_సమితి_plane_props(dispdata, &info);
            ఒకవేళ (drm_atomic_commit(video_device, dispdata, true, false)) {
                ఫలితం = SDL_సమితి_Error("Failed atomic commit in KMSDRM_ShowCursor.");
            }
        }
    } లేకపోతే {
        స్థిరరాశి పూర్ణాంకం rc = KMSDRM_drm_బహుళకం_సమితి_Cursor(viddata->drm_fd, dispdata->crtc.crtc->crtc_id, 0, 0, 0);
        ఒకవేళ (rc < 0) {
            ఫలితం = SDL_సమితి_Error("drmModeSetCursor() failed: %s", strerror(-rc));
        }
    }

    తిరిగి ఫలితం;
}

// Dump a cursor buffer to a display's DRM cursor BO.
స్థిర bool KMSDRM_Dump_Cursor_గమ్యం_BO(SDL_VideoDisplay *display, SDL_Mouse *mouse, SDL_Cursor *cursor)
{
    SDL_Display_దత్తాంశం *dispdata = display->అంతర్గత;
    SDL_Cursor_దత్తాంశం *curdata = cursor->అంతర్గత;
    SDL_VideoDevice *video_device = SDL_GetVideoDevice();
    SDL_Video_దత్తాంశం *viddata = video_device->అంతర్గత;

    uint32_t bo_handle;
    size_t bo_stride;
    size_t bufsize;
    uint8_t *ready_బఫరు = ఖాళీ;
    uint8_t *src_అడ్డువరుస;

    పూర్ణాంకం i, rc;
    bool ఫలితం = true;

    ఒకవేళ (!curdata || !dispdata->cursor_bo) {
        తిరిగి SDL_సమితి_Error("Cursor or display not initialized properly.");
    }

    /* Prepare a buffer we can dump to our GBM BO (different
       size, alpha premultiplication...) */
    bo_stride = KMSDRM_gbm_bo_get_stride(dispdata->cursor_bo);
    bufsize = bo_stride * dispdata->cursor_h;

    ready_బఫరు = (uint8_t *)SDL_calloc(1, bufsize);

    ఒకవేళ (!ready_బఫరు) {
        ఫలితం = false;
        వెళ్ళు cleanup;
    }

    // Copy from the cursor buffer to a buffer that we can dump to the GBM BO.
    కొరకు (i = 0; i < curdata->h; i++) {
        src_అడ్డువరుస = &((uint8_t *)curdata->బఫరు_2)[i * curdata->w * 4];
        SDL_memcpy(ready_బఫరు + (i * bo_stride), src_అడ్డువరుస, (size_t)4 * curdata->w);
    }

    // Dump the cursor buffer to our GBM BO.
    ఒకవేళ (KMSDRM_gbm_bo_write(dispdata->cursor_bo, ready_బఫరు, bufsize)) {
        ఫలితం = SDL_సమితి_Error("Could not write to GBM cursor BO");
        వెళ్ళు cleanup;
    }

    ఒకవేళ (USE_ATOMIC_CURSOR && viddata->is_atomic) {
        // Get the fb_id for the GBM BO so we can show it on the cursor plane.
        KMSDRM_FBInfo *fb = KMSDRM_FBFromBO(video_device, dispdata->cursor_bo);
        KMSDRM_PlaneInfo info;

        ఒకవేళ (!fb) {
            ఫలితం = SDL_సమితి_Error("Failed to get cursor FB from BO");
            వెళ్ళు cleanup;
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
        drm_atomic_సమితి_plane_props(dispdata, &info);
        ఒకవేళ (drm_atomic_commit(video_device, dispdata, true, false)) {
            ఫలితం = SDL_సమితి_Error("Failed atomic commit in KMSDRM_ShowCursor.");
            వెళ్ళు cleanup;
        }
    } లేకపోతే {
        // Put the GBM BO buffer on screen using the DRM interface.
        bo_handle = KMSDRM_gbm_bo_get_handle(dispdata->cursor_bo).u32;
        ఒకవేళ (curdata->hot_x == 0 && curdata->hot_y == 0) {
            rc = KMSDRM_drm_బహుళకం_సమితి_Cursor(viddata->drm_fd, dispdata->crtc.crtc->crtc_id, bo_handle, dispdata->cursor_w, dispdata->cursor_h);
        } లేకపోతే {
            rc = KMSDRM_drm_బహుళకం_సమితి_Cursor2(viddata->drm_fd, dispdata->crtc.crtc->crtc_id, bo_handle, dispdata->cursor_w, dispdata->cursor_h, curdata->hot_x, curdata->hot_y);
        }
        ఒకవేళ (rc < 0) {
            ఫలితం = SDL_సమితి_Error("Failed to set DRM cursor: %s", strerror(-rc));
            వెళ్ళు cleanup;
        }
    }

cleanup:
    SDL_free(ready_బఫరు);
    తిరిగి ఫలితం;
}

// This is only for freeing the SDL_cursor.
స్థిర శూన్య KMSDRM_FreeCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_దత్తాంశం *curdata;

    // Even if the cursor is not ours, free it.
    ఒకవేళ (cursor) {
        curdata = cursor->అంతర్గత;
        // Free cursor buffer
        ఒకవేళ (curdata->బఫరు_2) {
            SDL_free(curdata->బఫరు_2);
            curdata->బఫరు_2 = ఖాళీ;
        }
        // Free cursor itself
        SDL_free(cursor->అంతర్గత);
        SDL_free(cursor);
    }
}

/* This simply gets the cursor soft-buffer ready.
   We don't copy it to a GBO BO until ShowCursor() because the cusor GBM BO (living
   in dispata) is destroyed and recreated when we recreate windows, etc. */
స్థిర SDL_Cursor *KMSDRM_CreateCursor(SDL_Surface *surface, పూర్ణాంకం hot_x, పూర్ణాంకం hot_y)
{
    SDL_Cursor_దత్తాంశం *curdata;
    SDL_Cursor *cursor, *ఫలితం;

    curdata = ఖాళీ;
    ఫలితం = ఖాళీ;

    cursor = (SDL_Cursor *)SDL_calloc(1, పరిమాణం(*cursor));
    ఒకవేళ (!cursor) {
        వెళ్ళు cleanup;
    }
    curdata = (SDL_Cursor_దత్తాంశం *)SDL_calloc(1, పరిమాణం(*curdata));
    ఒకవేళ (!curdata) {
        వెళ్ళు cleanup;
    }

    // hox_x and hot_y are the coordinates of the "tip of the cursor" from it's base.
    curdata->hot_x = hot_x;
    curdata->hot_y = hot_y;
    curdata->w = surface->w;
    curdata->h = surface->h;
    curdata->బఫరు_2 = ఖాళీ;

    /* Configure the cursor buffer info.
       This buffer has the original size of the cursor surface we are given. */
    curdata->బఫరు_pitch = surface->w;
    curdata->బఫరు_కొలత = (size_t)surface->w * surface->h * 4;
    curdata->బఫరు_2 = (uint32_t *)SDL_malloc(curdata->బఫరు_కొలత);

    ఒకవేళ (!curdata->బఫరు_2) {
        వెళ్ళు cleanup;
    }

    /* All code below assumes ARGB8888 format for the cursor surface,
       like other backends do. Also, the GBM BO pixels have to be
       alpha-premultiplied, but the SDL surface we receive has
       straight-alpha pixels, so we always have to convert. */
    SDL_PremultiplyAlpha(surface->w, surface->h,
                         surface->format, surface->pixels, surface->pitch,
                         SDL_PIXELFORMAT_ARGB8888, curdata->బఫరు_2, surface->w * 4, true);

    cursor->అంతర్గత = curdata;

    ఫలితం = cursor;

cleanup:
    ఒకవేళ (!ఫలితం) {
        ఒకవేళ (curdata) {
            SDL_free(curdata->బఫరు_2);
            SDL_free(curdata);
        }
        SDL_free(cursor);
    }

    తిరిగి ఫలితం;
}

// Show the specified cursor, or hide if cursor is NULL or has no focus.
స్థిర bool KMSDRM_ShowCursor(SDL_Cursor *cursor)
{
    SDL_VideoDisplay *display;
    SDL_కిటికీ *కిటికీ;
    SDL_Mouse *mouse = SDL_GetMouse();

    పూర్ణాంకం i;
    bool ఫలితం = true;

    // Get the mouse focused window, if any.
    కిటికీ = mouse->focus;

    ఒకవేళ (!కిటికీ || !cursor) {
        /* If no window is focused by mouse or cursor is NULL,
           since we have no window (no mouse->focus) and hence
           we have no display, we simply hide mouse on all displays.
           This happens on video quit, where we get here after
           the mouse focus has been unset, yet SDL wants to
           restore the system default cursor (makes no sense here). */
        SDL_DisplayID *displays = SDL_GetDisplays(ఖాళీ);
        ఒకవేళ (displays) {
            // Iterate on the displays, hiding the cursor.
            కొరకు (i = 0; i < displays[i]; i++) {
                display = SDL_GetVideoDisplay(displays[i]);
                ఫలితం = KMSDRM_RemoveCursorFromBO(display);
            }
            SDL_free(displays);
        }
    } లేకపోతే {
        display = SDL_Get_Video_Display_For_కిటికీ(కిటికీ);
        ఒకవేళ (display) {
            ఒకవేళ (cursor) {
                /* Dump the cursor to the display DRM cursor BO so it becomes visible
                   on that display. */
                ఫలితం = KMSDRM_Dump_Cursor_గమ్యం_BO(display, mouse, cursor);
            } లేకపోతే {
                // Hide the cursor on that display.
                ఫలితం = KMSDRM_RemoveCursorFromBO(display);
            }
        }
    }

    తిరిగి ఫలితం;
}

స్థిర శూన్య drm_atomic_movecursor(SDL_Display_దత్తాంశం *dispdata, స్థిరరాశి SDL_Cursor_దత్తాంశం *curdata, uint16_t x, uint16_t y)
{
    ఒకవేళ (dispdata->cursor_plane) {  // We can't move a non-existing cursor, but that's ok.
        // Do we have a set of changes already in the making? If not, allocate a new one.
        ఒకవేళ (!dispdata->atomic_req) {
            dispdata->atomic_req = KMSDRM_drm_బహుళకం_Atomic_Alloc();
        }
        కూడు_plane_property(dispdata->atomic_req, dispdata->cursor_plane, "CRTC_X", x - curdata->hot_x);
        కూడు_plane_property(dispdata->atomic_req, dispdata->cursor_plane, "CRTC_Y", y - curdata->hot_y);
    }
}

స్థిర bool KMSDRM_WarpMouseGlobal(దశాంశం x, దశాంశం y)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    ఒకవేళ (mouse && mouse->cur_cursor && mouse->focus) {
        SDL_కిటికీ *కిటికీ = mouse->focus;
        SDL_Display_దత్తాంశం *dispdata = SDL_Get_Display_Driver_దత్తాంశం_For_కిటికీ(కిటికీ);

        // Update internal mouse position.
        SDL_SendMouseMotion(0, mouse->focus, SDL_GLOBAL_MOUSE_ID, false, x, y);

        // And now update the cursor graphic position on screen.
        ఒకవేళ (dispdata->cursor_bo) {
            SDL_VideoDevice *dev = SDL_GetVideoDevice();
            SDL_Video_దత్తాంశం *viddata = dev->అంతర్గత;
            ఒకవేళ (USE_ATOMIC_CURSOR && viddata->is_atomic) {
                స్థిరరాశి SDL_Cursor_దత్తాంశం *curdata = (స్థిరరాశి SDL_Cursor_దత్తాంశం *) mouse->cur_cursor->అంతర్గత;
                drm_atomic_movecursor(dispdata, curdata, (uint16_t) (పూర్ణాంకం) x, (uint16_t) (పూర్ణాంకం) y);
            } లేకపోతే {
                స్థిరరాశి పూర్ణాంకం rc = KMSDRM_drm_బహుళకం_Move_Cursor(dispdata->cursor_bo_drm_fd, dispdata->crtc.crtc->crtc_id, (పూర్ణాంకం)x, (పూర్ణాంకం)y);
                ఒకవేళ (rc < 0) {
                    తిరిగి SDL_సమితి_Error("drmModeMoveCursor() failed: %s", strerror(-rc));
                }
            }
        } లేకపోతే {
            తిరిగి SDL_సమితి_Error("Cursor not initialized properly.");
        }
    } లేకపోతే {
        తిరిగి SDL_సమితి_Error("No mouse or current cursor.");
    }

    తిరిగి true;
}

స్థిర bool KMSDRM_WarpMouse(SDL_కిటికీ *కిటికీ, దశాంశం x, దశాంశం y)
{
    // Only one global/fullscreen window is supported
    తిరిగి KMSDRM_WarpMouseGlobal(x, y);
}

శూన్య KMSDRM_InitMouse(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Display_దత్తాంశం *dispdata = display->అంతర్గత;

    mouse->CreateCursor = KMSDRM_CreateCursor;
    mouse->ShowCursor = KMSDRM_ShowCursor;
    mouse->MoveCursor = KMSDRM_MoveCursor;
    mouse->FreeCursor = KMSDRM_FreeCursor;
    mouse->WarpMouse = KMSDRM_WarpMouse;
    mouse->WarpMouseGlobal = KMSDRM_WarpMouseGlobal;

    /* Only create the default cursor for this display if we haven't done so before,
       we don't want several cursors to be created for the same display. */
    ఒకవేళ (!dispdata->default_cursor_init) {
        SDL_సమితి_Default_Cursor(KMSDRM_CreateDefaultCursor());
        dispdata->default_cursor_init = true;
    }
}

శూన్య KMSDRM_QuitMouse(SDL_VideoDevice *_this)
{
    // TODO: ?
}

// This is called when a mouse motion event occurs
స్థిర bool KMSDRM_MoveCursor(SDL_Cursor *cursor)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    /* We must NOT call SDL_SendMouseMotion() here or we will enter recursivity!
       That's why we move the cursor graphic ONLY. */
    ఒకవేళ (mouse && mouse->cur_cursor && mouse->focus) {
        SDL_కిటికీ *కిటికీ = mouse->focus;
        SDL_Display_దత్తాంశం *dispdata = SDL_Get_Display_Driver_దత్తాంశం_For_కిటికీ(కిటికీ);
        SDL_VideoDevice *dev = SDL_GetVideoDevice();
        SDL_Video_దత్తాంశం *viddata = dev->అంతర్గత;

        ఒకవేళ (!dispdata->cursor_bo) {
            తిరిగి SDL_సమితి_Error("Cursor not initialized properly.");
        }

        ఒకవేళ (USE_ATOMIC_CURSOR && viddata->is_atomic) {
            /* !!! FIXME: Some programs expect cursor movement even while they don't do SwapWindow() calls,
               and since we ride on the atomic_commit() in SwapWindow() for cursor movement,
               cursor won't move in these situations. We could do an atomic_commit() here
               for each cursor movement request, but it cripples the movement to 30FPS,
               so a future solution is needed. SDLPoP "QUIT?" menu is an example of this
               situation. */
            స్థిరరాశి SDL_Cursor_దత్తాంశం *curdata = (స్థిరరాశి SDL_Cursor_దత్తాంశం *) mouse->cur_cursor->అంతర్గత;
            drm_atomic_movecursor(dispdata, curdata, (uint16_t) (పూర్ణాంకం) mouse->x, (uint16_t) (పూర్ణాంకం) mouse->y);
        } లేకపోతే {
            స్థిరరాశి పూర్ణాంకం rc = KMSDRM_drm_బహుళకం_Move_Cursor(dispdata->cursor_bo_drm_fd, dispdata->crtc.crtc->crtc_id, (పూర్ణాంకం)mouse->x, (పూర్ణాంకం)mouse->y);
            ఒకవేళ (rc < 0) {
                తిరిగి SDL_సమితి_Error("drmModeMoveCursor() failed: %s", strerror(-rc));
            }
        }
    }
    తిరిగి true;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_KMSDRM
