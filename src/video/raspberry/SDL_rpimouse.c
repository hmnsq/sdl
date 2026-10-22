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

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_RPI

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_rpivideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_rpimouse.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/default_cursor.h"

// Copied from vc_vchi_dispmanx.h which is bugged and tries to include a non existing file
// Attributes changes flag mask
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ELEMENT_CHANGE_LAYER         (1 << 0)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ELEMENT_CHANGE_OPACITY       (1 << 1)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ELEMENT_CHANGE_DEST_RECT     (1 << 2)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ELEMENT_CHANGE_SRC_RECT      (1 << 3)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ELEMENT_CHANGE_ਨਕਾਬ_RESOURCE (1 << 4)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ELEMENT_CHANGE_TRANSFORM     (1 << 5)
// End copied from vc_vchi_dispmanx.h

ਸਥਿਰ SDL_Cursor *RPI_CreateDefaultCursor(ਖਾਲੀ);
ਸਥਿਰ SDL_Cursor *RPI_CreateCursor(SDL_Surface *surface, ਪੂਰਨ hot_x, ਪੂਰਨ hot_y);
ਸਥਿਰ bool RPI_ShowCursor(SDL_Cursor *cursor);
ਸਥਿਰ bool RPI_MoveCursor(SDL_Cursor *cursor);
ਸਥਿਰ ਖਾਲੀ RPI_FreeCursor(SDL_Cursor *cursor);

ਸਥਿਰ SDL_Cursor *global_cursor;

ਸਥਿਰ SDL_Cursor *RPI_CreateDefaultCursor(ਖਾਲੀ)
{
    ਵਾਪਸ SDL_CreateCursor(default_cdata, default_cmask, DEFAULT_CWIDTH, DEFAULT_CHEIGHT, DEFAULT_CHOTX, DEFAULT_CHOTY);
}

// Create a cursor from a surface
ਸਥਿਰ SDL_Cursor *RPI_CreateCursor(SDL_Surface *surface, ਪੂਰਨ hot_x, ਪੂਰਨ hot_y)
{
    ਪੂਰਨ rc;
    SDL_Cursor_ਅੰਕੜੇ *curdata;
    SDL_Cursor *cursor;
    VC_RECT_T dst_rect;
    Uint32 dummy;

    SDL_assert(surface->format == SDL_PIXELFORMAT_ARGB8888);
    SDL_assert(surface->pitch == surface->w * 4);

    cursor = (SDL_Cursor *)SDL_calloc(1, ਆਕਾਰ(*cursor));
    ਜੇ (!cursor) {
        ਵਾਪਸ ਨਿਰਾ;
    }
    curdata = (SDL_Cursor_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(*curdata));
    ਜੇ (!curdata) {
        SDL_free(cursor);
        ਵਾਪਸ ਨਿਰਾ;
    }

    curdata->hot_x = hot_x;
    curdata->hot_y = hot_y;
    curdata->w = surface->w;
    curdata->h = surface->h;

    // This usage is inspired by Wayland/Weston RPI code, how they figured this out is anyone's guess
    curdata->resource = vc_dispmanx_resource_create(VC_IMAGE_ARGB8888, surface->w | (surface->pitch << 16), surface->h | (surface->h << 16), &dummy);
    SDL_assert(curdata->resource);
    vc_dispmanx_rect_ਸੈੱਟ(&dst_rect, 0, 0, curdata->w, curdata->h);
    /* A note from Weston:
     * vc_dispmanx_resource_write_data() ignores ifmt,
     * rect.x, rect.width, and uses stride only for computing
     * the size of the transfer as rect.height * stride.
     * Therefore we can only write rows starting at x=0.
     */
    rc = vc_dispmanx_resource_write_ਅੰਕੜੇ(curdata->resource, VC_IMAGE_ARGB8888, surface->pitch, surface->pixels, &dst_rect);
    SDL_assert(rc == DISPMANX_SUCCESS);

    cursor->ਅੰਦਰੂਨੀ = curdata;

    ਵਾਪਸ cursor;
}

// Show the specified cursor, or hide if cursor is NULL
ਸਥਿਰ bool RPI_ShowCursor(SDL_Cursor *cursor)
{
    ਪੂਰਨ rc;
    DISPMANX_UPDATE_HANDLE_T update;
    SDL_Cursor_ਅੰਕੜੇ *curdata;
    VC_RECT_T src_rect, dst_rect;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Display_ਅੰਕੜੇ *ਅੰਕੜੇ;
    VC_DISPMANX_ALPHA_T alpha = { DISPMANX_FLAGS_ALPHA_FROM_ਸਰੋਤ /* flags */, 255 /*opacity 0->255*/, 0 /*ਨਕਾਬ*/ };
    uint32_t layer = SDL_RPI_MOUSELAYER;
    ਅਚਲ ਅੱਖਰ *hint;

    ਜੇ (cursor != global_cursor) {
        ਜੇ (global_cursor) {
            curdata = global_cursor->ਅੰਦਰੂਨੀ;
            ਜੇ (curdata && curdata->element > DISPMANX_NO_HANDLE) {
                update = vc_dispmanx_update_ਸ਼ੁਰੂ(0);
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

    ਜੇ (!cursor) {
        ਵਾਪਸ true;
    }

    curdata = cursor->ਅੰਦਰੂਨੀ;
    ਜੇ (!curdata) {
        ਵਾਪਸ false;
    }

    ਜੇ (!mouse->focus) {
        ਵਾਪਸ false;
    }

    ਅੰਕੜੇ = SDL_Get_Display_Driver_ਅੰਕੜੇ_For_ਖਿੜਕੀ(mouse->focus);
    ਜੇ (!ਅੰਕੜੇ) {
        ਵਾਪਸ false;
    }

    ਜੇ (curdata->element == DISPMANX_NO_HANDLE) {
        vc_dispmanx_rect_ਸੈੱਟ(&src_rect, 0, 0, curdata->w << 16, curdata->h << 16);
        vc_dispmanx_rect_ਸੈੱਟ(&dst_rect, (ਪੂਰਨ)mouse->x - curdata->hot_x, (ਪੂਰਨ)mouse->y - curdata->hot_y, curdata->w, curdata->h);

        update = vc_dispmanx_update_ਸ਼ੁਰੂ(0);
        SDL_assert(update);

        hint = SDL_GetHint(SDL_HINT_RPI_VIDEO_LAYER);
        ਜੇ (hint) {
            layer = SDL_atoi(hint) + 1;
        }

        curdata->element = vc_dispmanx_element_ਜੋੜੋ(update,
                                                   ਅੰਕੜੇ->dispman_display,
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

    ਵਾਪਸ true;
}

// Free a window manager cursor
ਸਥਿਰ ਖਾਲੀ RPI_FreeCursor(SDL_Cursor *cursor)
{
    ਪੂਰਨ rc;
    DISPMANX_UPDATE_HANDLE_T update;
    SDL_Cursor_ਅੰਕੜੇ *curdata;

    ਜੇ (cursor) {
        curdata = cursor->ਅੰਦਰੂਨੀ;

        ਜੇ (curdata) {
            ਜੇ (curdata->element != DISPMANX_NO_HANDLE) {
                update = vc_dispmanx_update_ਸ਼ੁਰੂ(0);
                SDL_assert(update);
                rc = vc_dispmanx_element_remove(update, curdata->element);
                SDL_assert(rc == DISPMANX_SUCCESS);
                rc = vc_dispmanx_update_submit_sync(update);
                SDL_assert(rc == DISPMANX_SUCCESS);
            }

            ਜੇ (curdata->resource != DISPMANX_NO_HANDLE) {
                rc = vc_dispmanx_resource_delete(curdata->resource);
                SDL_assert(rc == DISPMANX_SUCCESS);
            }

            SDL_free(cursor->ਅੰਦਰੂਨੀ);
        }
        SDL_free(cursor);
        ਜੇ (cursor == global_cursor) {
            global_cursor = ਨਿਰਾ;
        }
    }
}

ਸਥਿਰ bool RPI_WarpMouseGlobalGraphically(ਦਸ਼ਮਲਵ x, ਦਸ਼ਮਲਵ y)
{
    ਪੂਰਨ rc;
    SDL_Cursor_ਅੰਕੜੇ *curdata;
    DISPMANX_UPDATE_HANDLE_T update;
    VC_RECT_T dst_rect;
    VC_RECT_T src_rect;
    SDL_Mouse *mouse = SDL_GetMouse();

    ਜੇ (!mouse || !mouse->cur_cursor || !mouse->cur_cursor->ਅੰਦਰੂਨੀ) {
        ਵਾਪਸ true;
    }

    curdata = mouse->cur_cursor->ਅੰਦਰੂਨੀ;
    ਜੇ (curdata->element == DISPMANX_NO_HANDLE) {
        ਵਾਪਸ true;
    }

    update = vc_dispmanx_update_ਸ਼ੁਰੂ(0);
    ਜੇ (!update) {
        ਵਾਪਸ true;
    }

    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.ਚੌੜਾਈ = curdata->w << 16;
    src_rect.ਉਚਾਈ = curdata->h << 16;
    dst_rect.x = (ਪੂਰਨ)x - curdata->hot_x;
    dst_rect.y = (ਪੂਰਨ)y - curdata->hot_y;
    dst_rect.ਚੌੜਾਈ = curdata->w;
    dst_rect.ਉਚਾਈ = curdata->h;

    rc = vc_dispmanx_element_change_ਗੁਣ(
        update,
        curdata->element,
        0,
        0,
        0,
        &dst_rect,
        &src_rect,
        DISPMANX_NO_HANDLE,
        DISPMANX_NO_ROTATE);
    ਜੇ (rc != DISPMANX_SUCCESS) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("vc_dispmanx_element_change_attributes() failed");
    }

    // Submit asynchronously, otherwise the performance suffers a lot
    rc = vc_dispmanx_update_submit(update, 0, ਨਿਰਾ);
    ਜੇ (rc != DISPMANX_SUCCESS) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("vc_dispmanx_update_submit() failed");
    }
    ਵਾਪਸ true;
}

ਸਥਿਰ bool RPI_WarpMouseGlobal(ਦਸ਼ਮਲਵ x, ਦਸ਼ਮਲਵ y)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    ਜੇ (!mouse || !mouse->cur_cursor || !mouse->cur_cursor->ਅੰਦਰੂਨੀ) {
        ਵਾਪਸ true;
    }

    // Update internal mouse position.
    SDL_SendMouseMotion(0, mouse->focus, SDL_GLOBAL_MOUSE_ID, false, x, y);

    ਵਾਪਸ RPI_WarpMouseGlobalGraphically(x, y);
}

ਸਥਿਰ bool RPI_WarpMouse(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਦਸ਼ਮਲਵ x, ਦਸ਼ਮਲਵ y)
{
    ਵਾਪਸ RPI_WarpMouseGlobal(x, y);
}

ਖਾਲੀ RPI_InitMouse(SDL_VideoDevice *_this)
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

    SDL_ਸੈੱਟ_Default_Cursor(RPI_CreateDefaultCursor());
}

ਖਾਲੀ RPI_QuitMouse(SDL_VideoDevice *_this)
{
}

// This is called when a mouse motion event occurs
ਸਥਿਰ bool RPI_MoveCursor(SDL_Cursor *cursor)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    /* We must NOT call SDL_SendMouseMotion() on the next call or we will enter recursivity,
     * so we create a version of WarpMouseGlobal without it. */
    ਵਾਪਸ RPI_WarpMouseGlobalGraphically(mouse->x, mouse->y);
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_RPI
