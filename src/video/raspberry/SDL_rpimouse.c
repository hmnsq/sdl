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

#నిర్వచితమైతే SDL_VIDEO_DRIVER_RPI

#అన్తర్భావ "SDL_rpivideo.h"
#అన్తర్భావ "SDL_rpimouse.h"

#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "../../events/SDL_mouse_c.h"
#అన్తర్భావ "../../events/default_cursor.h"

// Copied from vc_vchi_dispmanx.h which is bugged and tries to include a non existing file
// Attributes changes flag mask
#నిర్వచించు ELEMENT_CHANGE_LAYER         (1 << 0)
#నిర్వచించు ELEMENT_CHANGE_OPACITY       (1 << 1)
#నిర్వచించు ELEMENT_CHANGE_DEST_RECT     (1 << 2)
#నిర్వచించు ELEMENT_CHANGE_SRC_RECT      (1 << 3)
#నిర్వచించు ELEMENT_CHANGE_ముసుగు_RESOURCE (1 << 4)
#నిర్వచించు ELEMENT_CHANGE_TRANSFORM     (1 << 5)
// End copied from vc_vchi_dispmanx.h

స్థిర SDL_Cursor *RPI_CreateDefaultCursor(శూన్య);
స్థిర SDL_Cursor *RPI_CreateCursor(SDL_Surface *surface, పూర్ణాంకం hot_x, పూర్ణాంకం hot_y);
స్థిర bool RPI_ShowCursor(SDL_Cursor *cursor);
స్థిర bool RPI_MoveCursor(SDL_Cursor *cursor);
స్థిర శూన్య RPI_FreeCursor(SDL_Cursor *cursor);

స్థిర SDL_Cursor *global_cursor;

స్థిర SDL_Cursor *RPI_CreateDefaultCursor(శూన్య)
{
    తిరిగి SDL_CreateCursor(default_cdata, default_cmask, DEFAULT_CWIDTH, DEFAULT_CHEIGHT, DEFAULT_CHOTX, DEFAULT_CHOTY);
}

// Create a cursor from a surface
స్థిర SDL_Cursor *RPI_CreateCursor(SDL_Surface *surface, పూర్ణాంకం hot_x, పూర్ణాంకం hot_y)
{
    పూర్ణాంకం rc;
    SDL_Cursor_దత్తాంశం *curdata;
    SDL_Cursor *cursor;
    VC_RECT_T dst_rect;
    Uint32 dummy;

    SDL_assert(surface->format == SDL_PIXELFORMAT_ARGB8888);
    SDL_assert(surface->pitch == surface->w * 4);

    cursor = (SDL_Cursor *)SDL_calloc(1, పరిమాణం(*cursor));
    ఒకవేళ (!cursor) {
        తిరిగి ఖాళీ;
    }
    curdata = (SDL_Cursor_దత్తాంశం *)SDL_calloc(1, పరిమాణం(*curdata));
    ఒకవేళ (!curdata) {
        SDL_free(cursor);
        తిరిగి ఖాళీ;
    }

    curdata->hot_x = hot_x;
    curdata->hot_y = hot_y;
    curdata->w = surface->w;
    curdata->h = surface->h;

    // This usage is inspired by Wayland/Weston RPI code, how they figured this out is anyone's guess
    curdata->resource = vc_dispmanx_resource_create(VC_IMAGE_ARGB8888, surface->w | (surface->pitch << 16), surface->h | (surface->h << 16), &dummy);
    SDL_assert(curdata->resource);
    vc_dispmanx_rect_సమితి(&dst_rect, 0, 0, curdata->w, curdata->h);
    /* A note from Weston:
     * vc_dispmanx_resource_write_data() ignores ifmt,
     * rect.x, rect.width, and uses stride only for computing
     * the size of the transfer as rect.height * stride.
     * Therefore we can only write rows starting at x=0.
     */
    rc = vc_dispmanx_resource_write_దత్తాంశం(curdata->resource, VC_IMAGE_ARGB8888, surface->pitch, surface->pixels, &dst_rect);
    SDL_assert(rc == DISPMANX_SUCCESS);

    cursor->అంతర్గత = curdata;

    తిరిగి cursor;
}

// Show the specified cursor, or hide if cursor is NULL
స్థిర bool RPI_ShowCursor(SDL_Cursor *cursor)
{
    పూర్ణాంకం rc;
    DISPMANX_UPDATE_HANDLE_T update;
    SDL_Cursor_దత్తాంశం *curdata;
    VC_RECT_T src_rect, dst_rect;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Display_దత్తాంశం *దత్తాంశం;
    VC_DISPMANX_ALPHA_T alpha = { DISPMANX_FLAGS_ALPHA_FROM_ఆధారం /* flags */, 255 /*opacity 0->255*/, 0 /*ముసుగు*/ };
    uint32_t layer = SDL_RPI_MOUSELAYER;
    స్థిరరాశి అక్షరం *hint;

    ఒకవేళ (cursor != global_cursor) {
        ఒకవేళ (global_cursor) {
            curdata = global_cursor->అంతర్గత;
            ఒకవేళ (curdata && curdata->element > DISPMANX_NO_HANDLE) {
                update = vc_dispmanx_update_ప్రారంభం(0);
                SDL_assert(update);
                rc = vc_dispmanx_element_remove(update, curdata->element);
                SDL_assert(rc == DISPMANX_SUCCESS);
                rc = vc_dispmanx_update_submit_sync(update);
                SDL_assert(rc == DISPMANX_SUCCESS);
                curdata->element = DISPMANX_NO_HANDLE;
            }
        }
        global_cursor = cursor;
    }

    ఒకవేళ (!cursor) {
        తిరిగి true;
    }

    curdata = cursor->అంతర్గత;
    ఒకవేళ (!curdata) {
        తిరిగి false;
    }

    ఒకవేళ (!mouse->focus) {
        తిరిగి false;
    }

    దత్తాంశం = SDL_Get_Display_Driver_దత్తాంశం_For_కిటికీ(mouse->focus);
    ఒకవేళ (!దత్తాంశం) {
        తిరిగి false;
    }

    ఒకవేళ (curdata->element == DISPMANX_NO_HANDLE) {
        vc_dispmanx_rect_సమితి(&src_rect, 0, 0, curdata->w << 16, curdata->h << 16);
        vc_dispmanx_rect_సమితి(&dst_rect, (పూర్ణాంకం)mouse->x - curdata->hot_x, (పూర్ణాంకం)mouse->y - curdata->hot_y, curdata->w, curdata->h);

        update = vc_dispmanx_update_ప్రారంభం(0);
        SDL_assert(update);

        hint = SDL_GetHint(SDL_HINT_RPI_VIDEO_LAYER);
        ఒకవేళ (hint) {
            layer = SDL_atoi(hint) + 1;
        }

        curdata->element = vc_dispmanx_element_కూడు(update,
                                                   దత్తాంశం->dispman_display,
                                                   layer,
                                                   &dst_rect,
                                                   curdata->resource,
                                                   &src_rect,
                                                   DISPMANX_PROTECTION_NONE,
                                                   &alpha,
                                                   DISPMANX_NO_HANDLE, // clamp
                                                   DISPMANX_NO_ROTATE);
        SDL_assert(curdata->element > DISPMANX_NO_HANDLE);
        rc = vc_dispmanx_update_submit_sync(update);
        SDL_assert(rc == DISPMANX_SUCCESS);
    }

    తిరిగి true;
}

// Free a window manager cursor
స్థిర శూన్య RPI_FreeCursor(SDL_Cursor *cursor)
{
    పూర్ణాంకం rc;
    DISPMANX_UPDATE_HANDLE_T update;
    SDL_Cursor_దత్తాంశం *curdata;

    ఒకవేళ (cursor) {
        curdata = cursor->అంతర్గత;

        ఒకవేళ (curdata) {
            ఒకవేళ (curdata->element != DISPMANX_NO_HANDLE) {
                update = vc_dispmanx_update_ప్రారంభం(0);
                SDL_assert(update);
                rc = vc_dispmanx_element_remove(update, curdata->element);
                SDL_assert(rc == DISPMANX_SUCCESS);
                rc = vc_dispmanx_update_submit_sync(update);
                SDL_assert(rc == DISPMANX_SUCCESS);
            }

            ఒకవేళ (curdata->resource != DISPMANX_NO_HANDLE) {
                rc = vc_dispmanx_resource_delete(curdata->resource);
                SDL_assert(rc == DISPMANX_SUCCESS);
            }

            SDL_free(cursor->అంతర్గత);
        }
        SDL_free(cursor);
        ఒకవేళ (cursor == global_cursor) {
            global_cursor = ఖాళీ;
        }
    }
}

స్థిర bool RPI_WarpMouseGlobalGraphically(దశాంశం x, దశాంశం y)
{
    పూర్ణాంకం rc;
    SDL_Cursor_దత్తాంశం *curdata;
    DISPMANX_UPDATE_HANDLE_T update;
    VC_RECT_T dst_rect;
    VC_RECT_T src_rect;
    SDL_Mouse *mouse = SDL_GetMouse();

    ఒకవేళ (!mouse || !mouse->cur_cursor || !mouse->cur_cursor->అంతర్గత) {
        తిరిగి true;
    }

    curdata = mouse->cur_cursor->అంతర్గత;
    ఒకవేళ (curdata->element == DISPMANX_NO_HANDLE) {
        తిరిగి true;
    }

    update = vc_dispmanx_update_ప్రారంభం(0);
    ఒకవేళ (!update) {
        తిరిగి true;
    }

    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.వెడల్పు = curdata->w << 16;
    src_rect.ఎత్తు = curdata->h << 16;
    dst_rect.x = (పూర్ణాంకం)x - curdata->hot_x;
    dst_rect.y = (పూర్ణాంకం)y - curdata->hot_y;
    dst_rect.వెడల్పు = curdata->w;
    dst_rect.ఎత్తు = curdata->h;

    rc = vc_dispmanx_element_change_లక్షణాలు(
        update,
        curdata->element,
        0,
        0,
        0,
        &dst_rect,
        &src_rect,
        DISPMANX_NO_HANDLE,
        DISPMANX_NO_ROTATE);
    ఒకవేళ (rc != DISPMANX_SUCCESS) {
        తిరిగి SDL_సమితి_Error("vc_dispmanx_element_change_attributes() failed");
    }

    // Submit asynchronously, otherwise the performance suffers a lot
    rc = vc_dispmanx_update_submit(update, 0, ఖాళీ);
    ఒకవేళ (rc != DISPMANX_SUCCESS) {
        తిరిగి SDL_సమితి_Error("vc_dispmanx_update_submit() failed");
    }
    తిరిగి true;
}

స్థిర bool RPI_WarpMouseGlobal(దశాంశం x, దశాంశం y)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    ఒకవేళ (!mouse || !mouse->cur_cursor || !mouse->cur_cursor->అంతర్గత) {
        తిరిగి true;
    }

    // Update internal mouse position.
    SDL_SendMouseMotion(0, mouse->focus, SDL_GLOBAL_MOUSE_ID, false, x, y);

    తిరిగి RPI_WarpMouseGlobalGraphically(x, y);
}

స్థిర bool RPI_WarpMouse(SDL_కిటికీ *కిటికీ, దశాంశం x, దశాంశం y)
{
    తిరిగి RPI_WarpMouseGlobal(x, y);
}

శూన్య RPI_InitMouse(SDL_VideoDevice *_this)
{
    /* FIXME: Using UDEV it should be possible to scan all mice
     * but there's no point in doing so as there's no multimice support...yet!
     */
    SDL_Mouse *mouse = SDL_GetMouse();

    mouse->CreateCursor = RPI_CreateCursor;
    mouse->ShowCursor = RPI_ShowCursor;
    mouse->MoveCursor = RPI_MoveCursor;
    mouse->FreeCursor = RPI_FreeCursor;
    mouse->WarpMouse = RPI_WarpMouse;
    mouse->WarpMouseGlobal = RPI_WarpMouseGlobal;

    SDL_సమితి_Default_Cursor(RPI_CreateDefaultCursor());
}

శూన్య RPI_QuitMouse(SDL_VideoDevice *_this)
{
}

// This is called when a mouse motion event occurs
స్థిర bool RPI_MoveCursor(SDL_Cursor *cursor)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    /* We must NOT call SDL_SendMouseMotion() on the next call or we will enter recursivity,
     * so we create a version of WarpMouseGlobal without it. */
    తిరిగి RPI_WarpMouseGlobalGraphically(mouse->x, mouse->y);
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_RPI
