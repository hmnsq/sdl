/*
  Simple DirectMedia Layer
  Copyright (C) 2026 BlackBerry Limited

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
#شامل "../SDL_sysvideo.h"
#شامل "SDL_qnx.h"
#شامل "../../events/SDL_mouse_c.h"

#شامل <errno.h>


ایستا صحیح SDLToScreenCursorShape(SDL_SystemCursor id)
{
    // This is reserved by screen, but still not used for anything.
    صحیح shape = -1;

    انتخاب(id)
    {
    حالت SDL_SYSTEM_CURSOR_DEFAULT:
    حالت SDL_SYSTEM_CURSOR_NOT_ALLOWED:
    حالت SDL_SYSTEM_CURSOR_NO_DROP:
        shape = SCREEN_CURSOR_SHAPE_ARROW;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_TEXT:
    حالت SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        shape = SCREEN_CURSOR_SHAPE_IBEAM;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_WAIT:
    حالت SDL_SYSTEM_CURSOR_PROGRESS:
        shape = SCREEN_CURSOR_SHAPE_WAIT;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_CROSSHAIR:
    حالت SDL_SYSTEM_CURSOR_CELL:
        shape = SCREEN_CURSOR_SHAPE_CROSS;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_NWSE_RESIZE:
    حالت SDL_SYSTEM_CURSOR_NESW_RESIZE:
    حالت SDL_SYSTEM_CURSOR_EW_RESIZE:
    حالت SDL_SYSTEM_CURSOR_NS_RESIZE:
    حالت SDL_SYSTEM_CURSOR_MOVE:
    حالت SDL_SYSTEM_CURSOR_NW_RESIZE:
    حالت SDL_SYSTEM_CURSOR_N_RESIZE:
    حالت SDL_SYSTEM_CURSOR_NE_RESIZE:
    حالت SDL_SYSTEM_CURSOR_E_RESIZE:
    حالت SDL_SYSTEM_CURSOR_SE_RESIZE:
    حالت SDL_SYSTEM_CURSOR_S_RESIZE:
    حالت SDL_SYSTEM_CURSOR_SW_RESIZE:
    حالت SDL_SYSTEM_CURSOR_W_RESIZE:
    حالت SDL_SYSTEM_CURSOR_COL_RESIZE:
    حالت SDL_SYSTEM_CURSOR_ROW_RESIZE:
    حالت SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = SCREEN_CURSOR_SHAPE_MOVE;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_POINTER:
    حالت SDL_SYSTEM_CURSOR_HELP:
    حالت SDL_SYSTEM_CURSOR_ALIAS:
    حالت SDL_SYSTEM_CURSOR_COPY:
        shape = SCREEN_CURSOR_SHAPE_HAND;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        shape = SCREEN_CURSOR_SHAPE_MENU;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_GRAB:
        shape = SCREEN_CURSOR_SHAPE_GRAB;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_GRABBING:
        shape = SCREEN_CURSOR_SHAPE_GRABBING;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_ZOOM_IN:
        shape = SCREEN_CURSOR_SHAPE_ZOOM_IN;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_ZOOM_OUT:
        shape = SCREEN_CURSOR_SHAPE_ZOOM_OUT;
        بشکن;
    پیشفرض:
        بشکن;
    }
    بازگشت shape;
}

ایستا SDL_Cursor *genericCreateCursor(صحیح shape)
{
    SDL_Cursor          *cursor;
    SDL_CursorData      *impl;
    screen_session_t    session;
    screen_context_t    *context = getContext();

    cursor = SDL_calloc(1, اندازه(SDL_Cursor));
    اگر (cursor) {
        impl = SDL_calloc(1, اندازه(SDL_CursorData));;
        اگر (impl == پوچ) {
            SDL_free(cursor);
            SDL_OutOfMemory();
        }
        impl->realized_shape = shape;

        screen_create_session_type(&session, *context, SCREEN_EVENT_POINTER);
        screen_set_session_property_iv(session, SCREEN_PROPERTY_CURSOR, &shape);

        impl->session = session;
        impl->is_visible = true;
        cursor->internal = (تهی*)impl;
    } وگرنه {
        SDL_OutOfMemory();
    }

    بازگشت cursor;
}

ایستا SDL_Cursor *createCursor(SDL_Surface * surface, صحیح hot_x, صحیح hot_y)
{
    بازگشت genericCreateCursor(SCREEN_CURSOR_SHAPE_ARROW);
}

ایستا SDL_Cursor *createSystemCursor(SDL_SystemCursor id)
{
    صحیح shape = SDLToScreenCursorShape(id);
    اگر (shape < 0) {
        SDL_assert(0);
        بازگشت پوچ;
    }

    بازگشت genericCreateCursor(shape);
}

ایستا bool showCursor(SDL_Cursor * cursor)
{
    SDL_CursorData      *impl;
    screen_session_t    session;
    صحیح shape;

    // SDL does not provide information about previous visibility to its
    // drivers. We need to track that ourselves.
    اگر (cursor) {
        impl = (SDL_CursorData*)cursor->internal;
        SDL_assert(impl != پوچ);
        اگر (impl->is_visible) {
            بازگشت true;
        }
        session = impl->session;
        shape = impl->realized_shape;
        impl->is_visible = true;
    } وگرنه {
        cursor = SDL_GetCursor();
        اگر (cursor == پوچ) {
            بازگشت false;
        }
        impl = (SDL_CursorData*)cursor->internal;
        SDL_assert(impl != پوچ);
        اگر (!impl->is_visible) {
            بازگشت 0;
        }
        session = impl->session;
        shape = SCREEN_CURSOR_SHAPE_NONE;
        impl->is_visible = false;
    }

    اگر (screen_set_session_property_iv(session, SCREEN_PROPERTY_CURSOR, &shape) < 0) {
        بازگشت false;
    }

    بازگشت true;
}

ایستا تهی freeCursor(SDL_Cursor * cursor)
{
    SDL_CursorData *impl = (SDL_CursorData*)cursor->internal;
    اگر (impl != پوچ) {
        screen_destroy_session(impl->session);
        SDL_free(impl);
    }
    SDL_free(cursor);
}

ایستا bool setRelativeMouseMode(bool enabled)
{
    // We're tracking rel-position explicitly, but this is still needed so
    // SDL_SetRelativeMouseMode() & friends aren't a no-op.
    //
    // TODO: It may be possible to achieve this using SCREEN_PROPERTY_DISPLACEMENT instead.
    بازگشت true;
}

تهی initMouse(SDL_VideoDevice *_this)
{
    SDL_Mouse       *mouse = SDL_GetMouse();
    SDL_MouseData   *mouse_data;

    mouse_data = (SDL_MouseData *)SDL_calloc(1, اندازه(SDL_MouseData));
    اگر (mouse_data == پوچ) {
        بازگشت;
    }
    SDL_zerop(mouse_data);
    mouse->internal = mouse_data;

    mouse->CreateCursor = createCursor;
    mouse->CreateSystemCursor = createSystemCursor;
    mouse->ShowCursor = showCursor;
    mouse->FreeCursor = freeCursor;

    mouse->SetRelativeMouseMode = setRelativeMouseMode;

    SDL_SetDefaultCursor(createCursor(پوچ, 0, 0));
}
