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
#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_RPI

#شامل "SDL_rpivideo.h"
#شامل "SDL_rpimouse.h"

#شامل "../SDL_sysvideo.h"
#شامل "../../events/SDL_mouse_c.h"
#شامل "../../events/default_cursor.h"

// Copied from vc_vchi_dispmanx.h which is bugged and tries to include a non existing file
// Attributes changes flag mask
#تعریف_کرو ELEMENT_CHANGE_LAYER         (1 << 0)
#تعریف_کرو ELEMENT_CHANGE_OPACITY       (1 << 1)
#تعریف_کرو ELEMENT_CHANGE_DEST_RECT     (1 << 2)
#تعریف_کرو ELEMENT_CHANGE_SRC_RECT      (1 << 3)
#تعریف_کرو ELEMENT_CHANGE_نقاب_RESOURCE (1 << 4)
#تعریف_کرو ELEMENT_CHANGE_TRANSFORM     (1 << 5)
// End copied from vc_vchi_dispmanx.h

ساکن SDL_Cursor *RPI_CreateDefaultCursor(خالی);
ساکن SDL_Cursor *RPI_CreateCursor(SDL_Surface *surface, صحیح hot_x, صحیح hot_y);
ساکن bool RPI_ShowCursor(SDL_Cursor *cursor);
ساکن bool RPI_MoveCursor(SDL_Cursor *cursor);
ساکن خالی RPI_FreeCursor(SDL_Cursor *cursor);

ساکن SDL_Cursor *global_cursor;

ساکن SDL_Cursor *RPI_CreateDefaultCursor(خالی)
{
    واپس SDL_CreateCursor(default_cdata, default_cmask, DEFAULT_CWIDTH, DEFAULT_CHEIGHT, DEFAULT_CHOTX, DEFAULT_CHOTY);
}

// Create a cursor from a surface
ساکن SDL_Cursor *RPI_CreateCursor(SDL_Surface *surface, صحیح hot_x, صحیح hot_y)
{
    صحیح rc;
    SDL_Cursor_ڈیٹا *curdata;
    SDL_Cursor *cursor;
    VC_RECT_T dst_rect;
    Uint32 dummy;

    SDL_assert(surface->format == SDL_PIXELFORMAT_ARGB8888);
    SDL_assert(surface->pitch == surface->w * 4);

    cursor = (SDL_Cursor *)SDL_calloc(1, حجم(*cursor));
    اگر (!cursor) {
        واپس تہی;
    }
    curdata = (SDL_Cursor_ڈیٹا *)SDL_calloc(1, حجم(*curdata));
    اگر (!curdata) {
        SDL_free(cursor);
        واپس تہی;
    }

    curdata->hot_x = hot_x;
    curdata->hot_y = hot_y;
    curdata->w = surface->w;
    curdata->h = surface->h;

    // This usage is inspired by Wayland/Weston RPI code, how they figured this out is anyone's guess
    curdata->resource = vc_dispmanx_resource_create(VC_IMAGE_ARGB8888, surface->w | (surface->pitch << 16), surface->h | (surface->h << 16), &dummy);
    SDL_assert(curdata->resource);
    vc_dispmanx_rect_سیٹ(&dst_rect, 0, 0, curdata->w, curdata->h);
    /* A note from Weston:
     * vc_dispmanx_resource_write_data() ignores ifmt,
     * rect.x, rect.width, and uses stride only for computing
     * the size of the transfer as rect.height * stride.
     * Therefore we can only write rows starting at x=0.
     */
    rc = vc_dispmanx_resource_write_ڈیٹا(curdata->resource, VC_IMAGE_ARGB8888, surface->pitch, surface->pixels, &dst_rect);
    SDL_assert(rc == DISPMANX_SUCCESS);

    cursor->اندرونی_2 = curdata;

    واپس cursor;
}

// Show the specified cursor, or hide if cursor is NULL
ساکن bool RPI_ShowCursor(SDL_Cursor *cursor)
{
    صحیح rc;
    DISPMANX_UPDATE_HANDLE_T update;
    SDL_Cursor_ڈیٹا *curdata;
    VC_RECT_T src_rect, dst_rect;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Display_ڈیٹا *ڈیٹا;
    VC_DISPMANX_ALPHA_T alpha = { DISPMANX_FLAGS_ALPHA_FROM_ماخذ /* flags */, 255 /*opacity 0->255*/, 0 /*نقاب*/ };
    uint32_t layer = SDL_RPI_MOUSELAYER;
    ثابت حرف *hint;

    اگر (cursor != global_cursor) {
        اگر (global_cursor) {
            curdata = global_cursor->اندرونی_2;
            اگر (curdata && curdata->element > DISPMANX_NO_HANDLE) {
                update = vc_dispmanx_update_آغاز(0);
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

    اگر (!cursor) {
        واپس true;
    }

    curdata = cursor->اندرونی_2;
    اگر (!curdata) {
        واپس false;
    }

    اگر (!mouse->focus) {
        واپس false;
    }

    ڈیٹا = SDL_Get_Display_Driver_ڈیٹا_For_کھڑکی(mouse->focus);
    اگر (!ڈیٹا) {
        واپس false;
    }

    اگر (curdata->element == DISPMANX_NO_HANDLE) {
        vc_dispmanx_rect_سیٹ(&src_rect, 0, 0, curdata->w << 16, curdata->h << 16);
        vc_dispmanx_rect_سیٹ(&dst_rect, (صحیح)mouse->x - curdata->hot_x, (صحیح)mouse->y - curdata->hot_y, curdata->w, curdata->h);

        update = vc_dispmanx_update_آغاز(0);
        SDL_assert(update);

        hint = SDL_GetHint(SDL_HINT_RPI_VIDEO_LAYER);
        اگر (hint) {
            layer = SDL_atoi(hint) + 1;
        }

        curdata->element = vc_dispmanx_element_جوڑو(update,
                                                   ڈیٹا->dispman_display,
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

    واپس true;
}

// Free a window manager cursor
ساکن خالی RPI_FreeCursor(SDL_Cursor *cursor)
{
    صحیح rc;
    DISPMANX_UPDATE_HANDLE_T update;
    SDL_Cursor_ڈیٹا *curdata;

    اگر (cursor) {
        curdata = cursor->اندرونی_2;

        اگر (curdata) {
            اگر (curdata->element != DISPMANX_NO_HANDLE) {
                update = vc_dispmanx_update_آغاز(0);
                SDL_assert(update);
                rc = vc_dispmanx_element_remove(update, curdata->element);
                SDL_assert(rc == DISPMANX_SUCCESS);
                rc = vc_dispmanx_update_submit_sync(update);
                SDL_assert(rc == DISPMANX_SUCCESS);
            }

            اگر (curdata->resource != DISPMANX_NO_HANDLE) {
                rc = vc_dispmanx_resource_delete(curdata->resource);
                SDL_assert(rc == DISPMANX_SUCCESS);
            }

            SDL_free(cursor->اندرونی_2);
        }
        SDL_free(cursor);
        اگر (cursor == global_cursor) {
            global_cursor = تہی;
        }
    }
}

ساکن bool RPI_WarpMouseGlobalGraphically(اعشاری x, اعشاری y)
{
    صحیح rc;
    SDL_Cursor_ڈیٹا *curdata;
    DISPMANX_UPDATE_HANDLE_T update;
    VC_RECT_T dst_rect;
    VC_RECT_T src_rect;
    SDL_Mouse *mouse = SDL_GetMouse();

    اگر (!mouse || !mouse->cur_cursor || !mouse->cur_cursor->اندرونی_2) {
        واپس true;
    }

    curdata = mouse->cur_cursor->اندرونی_2;
    اگر (curdata->element == DISPMANX_NO_HANDLE) {
        واپس true;
    }

    update = vc_dispmanx_update_آغاز(0);
    اگر (!update) {
        واپس true;
    }

    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.چوڑائی = curdata->w << 16;
    src_rect.اونچائی = curdata->h << 16;
    dst_rect.x = (صحیح)x - curdata->hot_x;
    dst_rect.y = (صحیح)y - curdata->hot_y;
    dst_rect.چوڑائی = curdata->w;
    dst_rect.اونچائی = curdata->h;

    rc = vc_dispmanx_element_change_اوصاف(
        update,
        curdata->element,
        0,
        0,
        0,
        &dst_rect,
        &src_rect,
        DISPMANX_NO_HANDLE,
        DISPMANX_NO_ROTATE);
    اگر (rc != DISPMANX_SUCCESS) {
        واپس SDL_سیٹ_Error("vc_dispmanx_element_change_attributes() failed");
    }

    // Submit asynchronously, otherwise the performance suffers a lot
    rc = vc_dispmanx_update_submit(update, 0, تہی);
    اگر (rc != DISPMANX_SUCCESS) {
        واپس SDL_سیٹ_Error("vc_dispmanx_update_submit() failed");
    }
    واپس true;
}

ساکن bool RPI_WarpMouseGlobal(اعشاری x, اعشاری y)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    اگر (!mouse || !mouse->cur_cursor || !mouse->cur_cursor->اندرونی_2) {
        واپس true;
    }

    // Update internal mouse position.
    SDL_SendMouseMotion(0, mouse->focus, SDL_GLOBAL_MOUSE_ID, false, x, y);

    واپس RPI_WarpMouseGlobalGraphically(x, y);
}

ساکن bool RPI_WarpMouse(SDL_کھڑکی *کھڑکی, اعشاری x, اعشاری y)
{
    واپس RPI_WarpMouseGlobal(x, y);
}

خالی RPI_InitMouse(SDL_VideoDevice *_this)
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

    SDL_سیٹ_Default_Cursor(RPI_CreateDefaultCursor());
}

خالی RPI_QuitMouse(SDL_VideoDevice *_this)
{
}

// This is called when a mouse motion event occurs
ساکن bool RPI_MoveCursor(SDL_Cursor *cursor)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    /* We must NOT call SDL_SendMouseMotion() on the next call or we will enter recursivity,
     * so we create a version of WarpMouseGlobal without it. */
    واپس RPI_WarpMouseGlobalGraphically(mouse->x, mouse->y);
}

#اگر_ختم // SDL_VIDEO_DRIVER_RPI
