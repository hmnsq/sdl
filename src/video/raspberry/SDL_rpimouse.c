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

#ifdef SDL_VIDEO_DRIVER_RPI

#ضمن "SDL_rpivideo.h"
#ضمن "SDL_rpimouse.h"

#ضمن "../SDL_sysvideo.h"
#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../../events/default_cursor.h"

// Copied from vc_vchi_dispmanx.h which is bugged and tries to include a non existing file
// Attributes changes flag mask
#define ELEMENT_CHANGE_LAYER         (1 << 0)
#define ELEMENT_CHANGE_OPACITY       (1 << 1)
#define ELEMENT_CHANGE_DEST_RECT     (1 << 2)
#define ELEMENT_CHANGE_SRC_RECT      (1 << 3)
#define ELEMENT_CHANGE_MASK_RESOURCE (1 << 4)
#define ELEMENT_CHANGE_TRANSFORM     (1 << 5)
// End copied from vc_vchi_dispmanx.h

ساكن SDL_Cursor *RPI_CreateDefaultCursor(فراغ);
ساكن SDL_Cursor *RPI_CreateCursor(SDL_Surface *surface, صحيح hot_x, صحيح hot_y);
ساكن bool RPI_ShowCursor(SDL_Cursor *cursor);
ساكن bool RPI_MoveCursor(SDL_Cursor *cursor);
ساكن فراغ RPI_FreeCursor(SDL_Cursor *cursor);

ساكن SDL_Cursor *global_cursor;

ساكن SDL_Cursor *RPI_CreateDefaultCursor(فراغ)
{
    ܦܢܐ SDL_CreateCursor(default_cdata, default_cmask, DEFAULT_CWIDTH, DEFAULT_CHEIGHT, DEFAULT_CHOTX, DEFAULT_CHOTY);
}

// Create a cursor from a surface
ساكن SDL_Cursor *RPI_CreateCursor(SDL_Surface *surface, صحيح hot_x, صحيح hot_y)
{
    صحيح rc;
    SDL_CursorData *curdata;
    SDL_Cursor *cursor;
    VC_RECT_T dst_rect;
    Uint32 dummy;

    SDL_assert(surface->format == SDL_PIXELFORMAT_ARGB8888);
    SDL_assert(surface->pitch == surface->w * 4);

    cursor = (SDL_Cursor *)SDL_calloc(1, حجم(*cursor));
    ܐܢ (!cursor) {
        ܦܢܐ عدم;
    }
    curdata = (SDL_CursorData *)SDL_calloc(1, حجم(*curdata));
    ܐܢ (!curdata) {
        SDL_free(cursor);
        ܦܢܐ عدم;
    }

    curdata->hot_x = hot_x;
    curdata->hot_y = hot_y;
    curdata->w = surface->w;
    curdata->h = surface->h;

    // This usage is inspired by Wayland/Weston RPI code, how they figured this out is anyone's guess
    curdata->resource = vc_dispmanx_resource_create(VC_IMAGE_ARGB8888, surface->w | (surface->pitch << 16), surface->h | (surface->h << 16), &dummy);
    SDL_assert(curdata->resource);
    vc_dispmanx_rect_set(&dst_rect, 0, 0, curdata->w, curdata->h);
    /* A note from Weston:
     * vc_dispmanx_resource_write_data() ignores ifmt,
     * rect.x, rect.width, and uses stride only for computing
     * the size of the transfer as rect.height * stride.
     * Therefore we can only write rows starting at x=0.
     */
    rc = vc_dispmanx_resource_write_data(curdata->resource, VC_IMAGE_ARGB8888, surface->pitch, surface->pixels, &dst_rect);
    SDL_assert(rc == DISPMANX_SUCCESS);

    cursor->internal = curdata;

    ܦܢܐ cursor;
}

// Show the specified cursor, or hide if cursor is NULL
ساكن bool RPI_ShowCursor(SDL_Cursor *cursor)
{
    صحيح rc;
    DISPMANX_UPDATE_HANDLE_T update;
    SDL_CursorData *curdata;
    VC_RECT_T src_rect, dst_rect;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_DisplayData *data;
    VC_DISPMANX_ALPHA_T alpha = { DISPMANX_FLAGS_ALPHA_FROM_SOURCE /* flags */, 255 /*opacity 0->255*/, 0 /* mask */ };
    uint32_t layer = SDL_RPI_MOUSELAYER;
    ثابت حرف *hint;

    ܐܢ (cursor != global_cursor) {
        ܐܢ (global_cursor) {
            curdata = global_cursor->internal;
            ܐܢ (curdata && curdata->element > DISPMANX_NO_HANDLE) {
                update = vc_dispmanx_update_start(0);
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

    ܐܢ (!cursor) {
        ܦܢܐ true;
    }

    curdata = cursor->internal;
    ܐܢ (!curdata) {
        ܦܢܐ false;
    }

    ܐܢ (!mouse->focus) {
        ܦܢܐ false;
    }

    data = SDL_GetDisplayDriverDataForWindow(mouse->focus);
    ܐܢ (!data) {
        ܦܢܐ false;
    }

    ܐܢ (curdata->element == DISPMANX_NO_HANDLE) {
        vc_dispmanx_rect_set(&src_rect, 0, 0, curdata->w << 16, curdata->h << 16);
        vc_dispmanx_rect_set(&dst_rect, (صحيح)mouse->x - curdata->hot_x, (صحيح)mouse->y - curdata->hot_y, curdata->w, curdata->h);

        update = vc_dispmanx_update_start(0);
        SDL_assert(update);

        hint = SDL_GetHint(SDL_HINT_RPI_VIDEO_LAYER);
        ܐܢ (hint) {
            layer = SDL_atoi(hint) + 1;
        }

        curdata->element = vc_dispmanx_element_add(update,
                                                   data->dispman_display,
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

    ܦܢܐ true;
}

// Free a window manager cursor
ساكن فراغ RPI_FreeCursor(SDL_Cursor *cursor)
{
    صحيح rc;
    DISPMANX_UPDATE_HANDLE_T update;
    SDL_CursorData *curdata;

    ܐܢ (cursor) {
        curdata = cursor->internal;

        ܐܢ (curdata) {
            ܐܢ (curdata->element != DISPMANX_NO_HANDLE) {
                update = vc_dispmanx_update_start(0);
                SDL_assert(update);
                rc = vc_dispmanx_element_remove(update, curdata->element);
                SDL_assert(rc == DISPMANX_SUCCESS);
                rc = vc_dispmanx_update_submit_sync(update);
                SDL_assert(rc == DISPMANX_SUCCESS);
            }

            ܐܢ (curdata->resource != DISPMANX_NO_HANDLE) {
                rc = vc_dispmanx_resource_delete(curdata->resource);
                SDL_assert(rc == DISPMANX_SUCCESS);
            }

            SDL_free(cursor->internal);
        }
        SDL_free(cursor);
        ܐܢ (cursor == global_cursor) {
            global_cursor = عدم;
        }
    }
}

ساكن bool RPI_WarpMouseGlobalGraphically(عائم x, عائم y)
{
    صحيح rc;
    SDL_CursorData *curdata;
    DISPMANX_UPDATE_HANDLE_T update;
    VC_RECT_T dst_rect;
    VC_RECT_T src_rect;
    SDL_Mouse *mouse = SDL_GetMouse();

    ܐܢ (!mouse || !mouse->cur_cursor || !mouse->cur_cursor->internal) {
        ܦܢܐ true;
    }

    curdata = mouse->cur_cursor->internal;
    ܐܢ (curdata->element == DISPMANX_NO_HANDLE) {
        ܦܢܐ true;
    }

    update = vc_dispmanx_update_start(0);
    ܐܢ (!update) {
        ܦܢܐ true;
    }

    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.width = curdata->w << 16;
    src_rect.height = curdata->h << 16;
    dst_rect.x = (صحيح)x - curdata->hot_x;
    dst_rect.y = (صحيح)y - curdata->hot_y;
    dst_rect.width = curdata->w;
    dst_rect.height = curdata->h;

    rc = vc_dispmanx_element_change_attributes(
        update,
        curdata->element,
        0,
        0,
        0,
        &dst_rect,
        &src_rect,
        DISPMANX_NO_HANDLE,
        DISPMANX_NO_ROTATE);
    ܐܢ (rc != DISPMANX_SUCCESS) {
        ܦܢܐ SDL_SetError("vc_dispmanx_element_change_attributes() failed");
    }

    // Submit asynchronously, otherwise the performance suffers a lot
    rc = vc_dispmanx_update_submit(update, 0, عدم);
    ܐܢ (rc != DISPMANX_SUCCESS) {
        ܦܢܐ SDL_SetError("vc_dispmanx_update_submit() failed");
    }
    ܦܢܐ true;
}

ساكن bool RPI_WarpMouseGlobal(عائم x, عائم y)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    ܐܢ (!mouse || !mouse->cur_cursor || !mouse->cur_cursor->internal) {
        ܦܢܐ true;
    }

    // Update internal mouse position.
    SDL_SendMouseMotion(0, mouse->focus, SDL_GLOBAL_MOUSE_ID, false, x, y);

    ܦܢܐ RPI_WarpMouseGlobalGraphically(x, y);
}

ساكن bool RPI_WarpMouse(SDL_Window *window, عائم x, عائم y)
{
    ܦܢܐ RPI_WarpMouseGlobal(x, y);
}

فراغ RPI_InitMouse(SDL_VideoDevice *_this)
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

    SDL_SetDefaultCursor(RPI_CreateDefaultCursor());
}

فراغ RPI_QuitMouse(SDL_VideoDevice *_this)
{
}

// This is called when a mouse motion event occurs
ساكن bool RPI_MoveCursor(SDL_Cursor *cursor)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    /* We must NOT call SDL_SendMouseMotion() on the next call or we will enter recursivity,
     * so we create a version of WarpMouseGlobal without it. */
    ܦܢܐ RPI_WarpMouseGlobalGraphically(mouse->x, mouse->y);
}

#endif // SDL_VIDEO_DRIVER_RPI
