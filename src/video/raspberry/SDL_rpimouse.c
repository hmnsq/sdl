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

#ifdef SDL_VIDEO_DRIVER_RPI

#അന്തര്ഭാവ "SDL_rpivideo.h"
#അന്തര്ഭാവ "SDL_rpimouse.h"

#അന്തര്ഭാവ "../SDL_sysvideo.h"
#അന്തര്ഭാവ "../../events/SDL_mouse_c.h"
#അന്തര്ഭാവ "../../events/default_cursor.h"

// Copied from vc_vchi_dispmanx.h which is bugged and tries to include a non existing file
// Attributes changes flag mask
#define ELEMENT_CHANGE_LAYER         (1 << 0)
#define ELEMENT_CHANGE_OPACITY       (1 << 1)
#define ELEMENT_CHANGE_DEST_RECT     (1 << 2)
#define ELEMENT_CHANGE_SRC_RECT      (1 << 3)
#define ELEMENT_CHANGE_MASK_RESOURCE (1 << 4)
#define ELEMENT_CHANGE_TRANSFORM     (1 << 5)
// End copied from vc_vchi_dispmanx.h

സ്ഥിതം SDL_Cursor *RPI_CreateDefaultCursor(ശൂന്യം);
സ്ഥിതം SDL_Cursor *RPI_CreateCursor(SDL_Surface *surface, പൂർണ്ണസംഖ്യ hot_x, പൂർണ്ണസംഖ്യ hot_y);
സ്ഥിതം bool RPI_ShowCursor(SDL_Cursor *cursor);
സ്ഥിതം bool RPI_MoveCursor(SDL_Cursor *cursor);
സ്ഥിതം ശൂന്യം RPI_FreeCursor(SDL_Cursor *cursor);

സ്ഥിതം SDL_Cursor *global_cursor;

സ്ഥിതം SDL_Cursor *RPI_CreateDefaultCursor(ശൂന്യം)
{
    തിരികെ SDL_CreateCursor(default_cdata, default_cmask, DEFAULT_CWIDTH, DEFAULT_CHEIGHT, DEFAULT_CHOTX, DEFAULT_CHOTY);
}

// Create a cursor from a surface
സ്ഥിതം SDL_Cursor *RPI_CreateCursor(SDL_Surface *surface, പൂർണ്ണസംഖ്യ hot_x, പൂർണ്ണസംഖ്യ hot_y)
{
    പൂർണ്ണസംഖ്യ rc;
    SDL_CursorData *curdata;
    SDL_Cursor *cursor;
    VC_RECT_T dst_rect;
    Uint32 dummy;

    SDL_assert(surface->format == SDL_PIXELFORMAT_ARGB8888);
    SDL_assert(surface->pitch == surface->w * 4);

    cursor = (SDL_Cursor *)SDL_calloc(1, വലുപ്പം(*cursor));
    എങ്കിൽ (!cursor) {
        തിരികെ ശൂന്യ;
    }
    curdata = (SDL_CursorData *)SDL_calloc(1, വലുപ്പം(*curdata));
    എങ്കിൽ (!curdata) {
        SDL_free(cursor);
        തിരികെ ശൂന്യ;
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

    തിരികെ cursor;
}

// Show the specified cursor, or hide if cursor is NULL
സ്ഥിതം bool RPI_ShowCursor(SDL_Cursor *cursor)
{
    പൂർണ്ണസംഖ്യ rc;
    DISPMANX_UPDATE_HANDLE_T update;
    SDL_CursorData *curdata;
    VC_RECT_T src_rect, dst_rect;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_DisplayData *data;
    VC_DISPMANX_ALPHA_T alpha = { DISPMANX_FLAGS_ALPHA_FROM_SOURCE /* flags */, 255 /*opacity 0->255*/, 0 /* mask */ };
    uint32_t layer = SDL_RPI_MOUSELAYER;
    സ്ഥിരം അക്ഷരം *hint;

    എങ്കിൽ (cursor != global_cursor) {
        എങ്കിൽ (global_cursor) {
            curdata = global_cursor->internal;
            എങ്കിൽ (curdata && curdata->element > DISPMANX_NO_HANDLE) {
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

    എങ്കിൽ (!cursor) {
        തിരികെ true;
    }

    curdata = cursor->internal;
    എങ്കിൽ (!curdata) {
        തിരികെ false;
    }

    എങ്കിൽ (!mouse->focus) {
        തിരികെ false;
    }

    data = SDL_GetDisplayDriverDataForWindow(mouse->focus);
    എങ്കിൽ (!data) {
        തിരികെ false;
    }

    എങ്കിൽ (curdata->element == DISPMANX_NO_HANDLE) {
        vc_dispmanx_rect_set(&src_rect, 0, 0, curdata->w << 16, curdata->h << 16);
        vc_dispmanx_rect_set(&dst_rect, (പൂർണ്ണസംഖ്യ)mouse->x - curdata->hot_x, (പൂർണ്ണസംഖ്യ)mouse->y - curdata->hot_y, curdata->w, curdata->h);

        update = vc_dispmanx_update_start(0);
        SDL_assert(update);

        hint = SDL_GetHint(SDL_HINT_RPI_VIDEO_LAYER);
        എങ്കിൽ (hint) {
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

    തിരികെ true;
}

// Free a window manager cursor
സ്ഥിതം ശൂന്യം RPI_FreeCursor(SDL_Cursor *cursor)
{
    പൂർണ്ണസംഖ്യ rc;
    DISPMANX_UPDATE_HANDLE_T update;
    SDL_CursorData *curdata;

    എങ്കിൽ (cursor) {
        curdata = cursor->internal;

        എങ്കിൽ (curdata) {
            എങ്കിൽ (curdata->element != DISPMANX_NO_HANDLE) {
                update = vc_dispmanx_update_start(0);
                SDL_assert(update);
                rc = vc_dispmanx_element_remove(update, curdata->element);
                SDL_assert(rc == DISPMANX_SUCCESS);
                rc = vc_dispmanx_update_submit_sync(update);
                SDL_assert(rc == DISPMANX_SUCCESS);
            }

            എങ്കിൽ (curdata->resource != DISPMANX_NO_HANDLE) {
                rc = vc_dispmanx_resource_delete(curdata->resource);
                SDL_assert(rc == DISPMANX_SUCCESS);
            }

            SDL_free(cursor->internal);
        }
        SDL_free(cursor);
        എങ്കിൽ (cursor == global_cursor) {
            global_cursor = ശൂന്യ;
        }
    }
}

സ്ഥിതം bool RPI_WarpMouseGlobalGraphically(ദശാംശം x, ദശാംശം y)
{
    പൂർണ്ണസംഖ്യ rc;
    SDL_CursorData *curdata;
    DISPMANX_UPDATE_HANDLE_T update;
    VC_RECT_T dst_rect;
    VC_RECT_T src_rect;
    SDL_Mouse *mouse = SDL_GetMouse();

    എങ്കിൽ (!mouse || !mouse->cur_cursor || !mouse->cur_cursor->internal) {
        തിരികെ true;
    }

    curdata = mouse->cur_cursor->internal;
    എങ്കിൽ (curdata->element == DISPMANX_NO_HANDLE) {
        തിരികെ true;
    }

    update = vc_dispmanx_update_start(0);
    എങ്കിൽ (!update) {
        തിരികെ true;
    }

    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.width = curdata->w << 16;
    src_rect.height = curdata->h << 16;
    dst_rect.x = (പൂർണ്ണസംഖ്യ)x - curdata->hot_x;
    dst_rect.y = (പൂർണ്ണസംഖ്യ)y - curdata->hot_y;
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
    എങ്കിൽ (rc != DISPMANX_SUCCESS) {
        തിരികെ SDL_SetError("vc_dispmanx_element_change_attributes() failed");
    }

    // Submit asynchronously, otherwise the performance suffers a lot
    rc = vc_dispmanx_update_submit(update, 0, ശൂന്യ);
    എങ്കിൽ (rc != DISPMANX_SUCCESS) {
        തിരികെ SDL_SetError("vc_dispmanx_update_submit() failed");
    }
    തിരികെ true;
}

സ്ഥിതം bool RPI_WarpMouseGlobal(ദശാംശം x, ദശാംശം y)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    എങ്കിൽ (!mouse || !mouse->cur_cursor || !mouse->cur_cursor->internal) {
        തിരികെ true;
    }

    // Update internal mouse position.
    SDL_SendMouseMotion(0, mouse->focus, SDL_GLOBAL_MOUSE_ID, false, x, y);

    തിരികെ RPI_WarpMouseGlobalGraphically(x, y);
}

സ്ഥിതം bool RPI_WarpMouse(SDL_Window *window, ദശാംശം x, ദശാംശം y)
{
    തിരികെ RPI_WarpMouseGlobal(x, y);
}

ശൂന്യം RPI_InitMouse(SDL_VideoDevice *_this)
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

ശൂന്യം RPI_QuitMouse(SDL_VideoDevice *_this)
{
}

// This is called when a mouse motion event occurs
സ്ഥിതം bool RPI_MoveCursor(SDL_Cursor *cursor)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    /* We must NOT call SDL_SendMouseMotion() on the next call or we will enter recursivity,
     * so we create a version of WarpMouseGlobal without it. */
    തിരികെ RPI_WarpMouseGlobalGraphically(mouse->x, mouse->y);
}

#endif // SDL_VIDEO_DRIVER_RPI
