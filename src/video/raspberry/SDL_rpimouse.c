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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_RPI

#समावेश "SDL_rpivideo.h"
#समावेश "SDL_rpimouse.h"

#समावेश "../SDL_sysvideo.h"
#समावेश "../../events/SDL_mouse_c.h"
#समावेश "../../events/default_cursor.h"

// Copied from vc_vchi_dispmanx.h which is bugged and tries to include a non existing file
// Attributes changes flag mask
#घोषणा ELEMENT_CHANGE_LAYER         (1 << 0)
#घोषणा ELEMENT_CHANGE_OPACITY       (1 << 1)
#घोषणा ELEMENT_CHANGE_DEST_RECT     (1 << 2)
#घोषणा ELEMENT_CHANGE_SRC_RECT      (1 << 3)
#घोषणा ELEMENT_CHANGE_MASK_RESOURCE (1 << 4)
#घोषणा ELEMENT_CHANGE_TRANSFORM     (1 << 5)
// End copied from vc_vchi_dispmanx.h

अटल SDL_Cursor *RPI_CreateDefaultCursor(व्योम);
अटल SDL_Cursor *RPI_CreateCursor(SDL_Surface *surface, पूर्णांक hot_x, पूर्णांक hot_y);
अटल bool RPI_ShowCursor(SDL_Cursor *cursor);
अटल bool RPI_MoveCursor(SDL_Cursor *cursor);
अटल व्योम RPI_FreeCursor(SDL_Cursor *cursor);

अटल SDL_Cursor *global_cursor;

अटल SDL_Cursor *RPI_CreateDefaultCursor(व्योम)
{
    वापस SDL_CreateCursor(default_cdata, default_cmask, DEFAULT_CWIDTH, DEFAULT_CHEIGHT, DEFAULT_CHOTX, DEFAULT_CHOTY);
}

// Create a cursor from a surface
अटल SDL_Cursor *RPI_CreateCursor(SDL_Surface *surface, पूर्णांक hot_x, पूर्णांक hot_y)
{
    पूर्णांक rc;
    SDL_Cursor_तथ्य *curdata;
    SDL_Cursor *cursor;
    VC_RECT_T dst_rect;
    Uint32 dummy;

    SDL_assert(surface->format == SDL_PIXELFORMAT_ARGB8888);
    SDL_assert(surface->pitch == surface->w * 4);

    cursor = (SDL_Cursor *)SDL_calloc(1, माप(*cursor));
    अगर (!cursor) {
        वापस शून्य;
    }
    curdata = (SDL_Cursor_तथ्य *)SDL_calloc(1, माप(*curdata));
    अगर (!curdata) {
        SDL_free(cursor);
        वापस शून्य;
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
    rc = vc_dispmanx_resource_write_तथ्य(curdata->resource, VC_IMAGE_ARGB8888, surface->pitch, surface->pixels, &dst_rect);
    SDL_assert(rc == DISPMANX_SUCCESS);

    cursor->internal = curdata;

    वापस cursor;
}

// Show the specified cursor, or hide if cursor is NULL
अटल bool RPI_ShowCursor(SDL_Cursor *cursor)
{
    पूर्णांक rc;
    DISPMANX_UPDATE_HANDLE_T update;
    SDL_Cursor_तथ्य *curdata;
    VC_RECT_T src_rect, dst_rect;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Display_तथ्य *तथ्य;
    VC_DISPMANX_ALPHA_T alpha = { DISPMANX_FLAGS_ALPHA_FROM_SOURCE /* flags */, 255 /*opacity 0->255*/, 0 /* mask */ };
    uint32_t layer = SDL_RPI_MOUSELAYER;
    स्थिर अक्षर *hint;

    अगर (cursor != global_cursor) {
        अगर (global_cursor) {
            curdata = global_cursor->internal;
            अगर (curdata && curdata->element > DISPMANX_NO_HANDLE) {
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

    अगर (!cursor) {
        वापस true;
    }

    curdata = cursor->internal;
    अगर (!curdata) {
        वापस false;
    }

    अगर (!mouse->focus) {
        वापस false;
    }

    तथ्य = SDL_Get_Display_Driver_तथ्य_For_Window(mouse->focus);
    अगर (!तथ्य) {
        वापस false;
    }

    अगर (curdata->element == DISPMANX_NO_HANDLE) {
        vc_dispmanx_rect_set(&src_rect, 0, 0, curdata->w << 16, curdata->h << 16);
        vc_dispmanx_rect_set(&dst_rect, (पूर्णांक)mouse->x - curdata->hot_x, (पूर्णांक)mouse->y - curdata->hot_y, curdata->w, curdata->h);

        update = vc_dispmanx_update_start(0);
        SDL_assert(update);

        hint = SDL_GetHint(SDL_HINT_RPI_VIDEO_LAYER);
        अगर (hint) {
            layer = SDL_atoi(hint) + 1;
        }

        curdata->element = vc_dispmanx_element_add(update,
                                                   तथ्य->dispman_display,
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

    वापस true;
}

// Free a window manager cursor
अटल व्योम RPI_FreeCursor(SDL_Cursor *cursor)
{
    पूर्णांक rc;
    DISPMANX_UPDATE_HANDLE_T update;
    SDL_Cursor_तथ्य *curdata;

    अगर (cursor) {
        curdata = cursor->internal;

        अगर (curdata) {
            अगर (curdata->element != DISPMANX_NO_HANDLE) {
                update = vc_dispmanx_update_start(0);
                SDL_assert(update);
                rc = vc_dispmanx_element_remove(update, curdata->element);
                SDL_assert(rc == DISPMANX_SUCCESS);
                rc = vc_dispmanx_update_submit_sync(update);
                SDL_assert(rc == DISPMANX_SUCCESS);
            }

            अगर (curdata->resource != DISPMANX_NO_HANDLE) {
                rc = vc_dispmanx_resource_delete(curdata->resource);
                SDL_assert(rc == DISPMANX_SUCCESS);
            }

            SDL_free(cursor->internal);
        }
        SDL_free(cursor);
        अगर (cursor == global_cursor) {
            global_cursor = शून्य;
        }
    }
}

अटल bool RPI_WarpMouseGlobalGraphically(भग्न x, भग्न y)
{
    पूर्णांक rc;
    SDL_Cursor_तथ्य *curdata;
    DISPMANX_UPDATE_HANDLE_T update;
    VC_RECT_T dst_rect;
    VC_RECT_T src_rect;
    SDL_Mouse *mouse = SDL_GetMouse();

    अगर (!mouse || !mouse->cur_cursor || !mouse->cur_cursor->internal) {
        वापस true;
    }

    curdata = mouse->cur_cursor->internal;
    अगर (curdata->element == DISPMANX_NO_HANDLE) {
        वापस true;
    }

    update = vc_dispmanx_update_start(0);
    अगर (!update) {
        वापस true;
    }

    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.width = curdata->w << 16;
    src_rect.height = curdata->h << 16;
    dst_rect.x = (पूर्णांक)x - curdata->hot_x;
    dst_rect.y = (पूर्णांक)y - curdata->hot_y;
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
    अगर (rc != DISPMANX_SUCCESS) {
        वापस SDL_SetError("vc_dispmanx_element_change_attributes() failed");
    }

    // Submit asynchronously, otherwise the performance suffers a lot
    rc = vc_dispmanx_update_submit(update, 0, शून्य);
    अगर (rc != DISPMANX_SUCCESS) {
        वापस SDL_SetError("vc_dispmanx_update_submit() failed");
    }
    वापस true;
}

अटल bool RPI_WarpMouseGlobal(भग्न x, भग्न y)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    अगर (!mouse || !mouse->cur_cursor || !mouse->cur_cursor->internal) {
        वापस true;
    }

    // Update internal mouse position.
    SDL_SendMouseMotion(0, mouse->focus, SDL_GLOBAL_MOUSE_ID, false, x, y);

    वापस RPI_WarpMouseGlobalGraphically(x, y);
}

अटल bool RPI_WarpMouse(SDL_Window *window, भग्न x, भग्न y)
{
    वापस RPI_WarpMouseGlobal(x, y);
}

व्योम RPI_InitMouse(SDL_VideoDevice *_this)
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

व्योम RPI_QuitMouse(SDL_VideoDevice *_this)
{
}

// This is called when a mouse motion event occurs
अटल bool RPI_MoveCursor(SDL_Cursor *cursor)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    /* We must NOT call SDL_SendMouseMotion() on the next call or we will enter recursivity,
     * so we create a version of WarpMouseGlobal without it. */
    वापस RPI_WarpMouseGlobalGraphically(mouse->x, mouse->y);
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_RPI
