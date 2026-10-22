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


ساکن صحیح SDLToScreenCursorShape(SDL_SystemCursor id)
{
    // This is reserved by screen, but still not used for anything.
    صحیح shape = -1;

    انتخاب(id)
    {
    حالت SDL_SYSTEM_CURSOR_DEFAULT:
    حالت SDL_SYSTEM_CURSOR_NOT_ALLOWED:
    حالت SDL_SYSTEM_CURSOR_NO_DROP:
        shape = SCREEN_CURSOR_SHAPE_ARROW;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_متن:
    حالت SDL_SYSTEM_CURSOR_VERTICAL_متن:
        shape = SCREEN_CURSOR_SHAPE_IBEAM;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_WAIT:
    حالت SDL_SYSTEM_CURSOR_پیش_رفت:
        shape = SCREEN_CURSOR_SHAPE_WAIT;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_CROSSHAIR:
    حالت SDL_SYSTEM_CURSOR_CELL:
        shape = SCREEN_CURSOR_SHAPE_CROSS;
        توڑو;
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
    حالت SDL_SYSTEM_CURSOR_ستون_RESIZE:
    حالت SDL_SYSTEM_CURSOR_صف_RESIZE:
    حالت SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = SCREEN_CURSOR_SHAPE_MOVE;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_اشارہ_گر:
    حالت SDL_SYSTEM_CURSOR_HELP:
    حالت SDL_SYSTEM_CURSOR_ALIAS:
    حالت SDL_SYSTEM_CURSOR_COPY:
        shape = SCREEN_CURSOR_SHAPE_HAND;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        shape = SCREEN_CURSOR_SHAPE_MENU;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_GRAB:
        shape = SCREEN_CURSOR_SHAPE_GRAB;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_GRABBING:
        shape = SCREEN_CURSOR_SHAPE_GRABBING;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_ZOOM_اندر:
        shape = SCREEN_CURSOR_SHAPE_ZOOM_اندر;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_ZOOM_برآمد:
        shape = SCREEN_CURSOR_SHAPE_ZOOM_برآمد;
        توڑو;
    طےشدہ:
        توڑو;
    }
    واپس shape;
}

ساکن SDL_Cursor *genericCreateCursor(صحیح shape)
{
    SDL_Cursor          *cursor;
    SDL_Cursor_ڈیٹا      *impl;
    screen_session_t    session;
    screen_context_t    *context = getContext();

    cursor = SDL_calloc(1, حجم(SDL_Cursor));
    اگر (cursor) {
        impl = SDL_calloc(1, حجم(SDL_Cursor_ڈیٹا));;
        اگر (impl == تہی) {
            SDL_free(cursor);
            SDL_برآمد_کا_حافظہ();
        }
        impl->realized_shape = shape;

        screen_create_session_type(&session, *context, SCREEN_EVENT_اشارہ_گر);
        screen_سیٹ_session_property_iv(session, SCREEN_PROPERTY_CURSOR, &shape);

        impl->session = session;
        impl->is_visible = true;
        cursor->اندرونی_2 = (خالی*)impl;
    } ورنہ {
        SDL_برآمد_کا_حافظہ();
    }

    واپس cursor;
}

ساکن SDL_Cursor *createCursor(SDL_Surface * surface, صحیح hot_x, صحیح hot_y)
{
    واپس genericCreateCursor(SCREEN_CURSOR_SHAPE_ARROW);
}

ساکن SDL_Cursor *createSystemCursor(SDL_SystemCursor id)
{
    صحیح shape = SDLToScreenCursorShape(id);
    اگر (shape < 0) {
        SDL_assert(0);
        واپس تہی;
    }

    واپس genericCreateCursor(shape);
}

ساکن bool showCursor(SDL_Cursor * cursor)
{
    SDL_Cursor_ڈیٹا      *impl;
    screen_session_t    session;
    صحیح shape;

    // SDL does not provide information about previous visibility to its
    // drivers. We need to track that ourselves.
    اگر (cursor) {
        impl = (SDL_Cursor_ڈیٹا*)cursor->اندرونی_2;
        SDL_assert(impl != تہی);
        اگر (impl->is_visible) {
            واپس true;
        }
        session = impl->session;
        shape = impl->realized_shape;
        impl->is_visible = true;
    } ورنہ {
        cursor = SDL_GetCursor();
        اگر (cursor == تہی) {
            واپس false;
        }
        impl = (SDL_Cursor_ڈیٹا*)cursor->اندرونی_2;
        SDL_assert(impl != تہی);
        اگر (!impl->is_visible) {
            واپس 0;
        }
        session = impl->session;
        shape = SCREEN_CURSOR_SHAPE_NONE;
        impl->is_visible = false;
    }

    اگر (screen_سیٹ_session_property_iv(session, SCREEN_PROPERTY_CURSOR, &shape) < 0) {
        واپس false;
    }

    واپس true;
}

ساکن خالی freeCursor(SDL_Cursor * cursor)
{
    SDL_Cursor_ڈیٹا *impl = (SDL_Cursor_ڈیٹا*)cursor->اندرونی_2;
    اگر (impl != تہی) {
        screen_destroy_session(impl->session);
        SDL_free(impl);
    }
    SDL_free(cursor);
}

ساکن bool سیٹ_Relative_Mouse_منوال_2(bool enabled)
{
    // We're tracking rel-position explicitly, but this is still needed so
    // SDL_SetRelativeMouseMode() & friends aren't a no-op.
    //
    // TODO: It may be possible to achieve this using SCREEN_PROPERTY_DISPLACEMENT instead.
    واپس true;
}

خالی initMouse(SDL_VideoDevice *_this)
{
    SDL_Mouse       *mouse = SDL_GetMouse();
    SDL_Mouse_ڈیٹا   *mouse_ڈیٹا;

    mouse_ڈیٹا = (SDL_Mouse_ڈیٹا *)SDL_calloc(1, حجم(SDL_Mouse_ڈیٹا));
    اگر (mouse_ڈیٹا == تہی) {
        واپس;
    }
    SDL_zerop(mouse_ڈیٹا);
    mouse->اندرونی_2 = mouse_ڈیٹا;

    mouse->CreateCursor = createCursor;
    mouse->CreateSystemCursor = createSystemCursor;
    mouse->ShowCursor = showCursor;
    mouse->FreeCursor = freeCursor;

    mouse->سیٹ_Relative_Mouse_منوال = سیٹ_Relative_Mouse_منوال_2;

    SDL_سیٹ_Default_Cursor(createCursor(تہی, 0, 0));
}
