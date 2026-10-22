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

#ضمن "SDL_internal.h"
#ضمن "../SDL_sysvideo.h"
#ضمن "SDL_qnx.h"
#ضمن "../../events/SDL_mouse_c.h"

#ضمن <errno.h>


ساكن صحيح SDLToScreenCursorShape(SDL_SystemCursor id)
{
    // This is reserved by screen, but still not used for anything.
    صحيح shape = -1;

    بدل(id)
    {
    حالة SDL_SYSTEM_CURSOR_DEFAULT:
    حالة SDL_SYSTEM_CURSOR_NOT_ALLOWED:
    حالة SDL_SYSTEM_CURSOR_NO_DROP:
        shape = SCREEN_CURSOR_SHAPE_ARROW;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_متن:
    حالة SDL_SYSTEM_CURSOR_VERTICAL_متن:
        shape = SCREEN_CURSOR_SHAPE_IBEAM;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_WAIT:
    حالة SDL_SYSTEM_CURSOR_ترقی:
        shape = SCREEN_CURSOR_SHAPE_WAIT;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_CROSSHAIR:
    حالة SDL_SYSTEM_CURSOR_CELL:
        shape = SCREEN_CURSOR_SHAPE_CROSS;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_NWSE_RESIZE:
    حالة SDL_SYSTEM_CURSOR_NESW_RESIZE:
    حالة SDL_SYSTEM_CURSOR_EW_RESIZE:
    حالة SDL_SYSTEM_CURSOR_NS_RESIZE:
    حالة SDL_SYSTEM_CURSOR_MOVE:
    حالة SDL_SYSTEM_CURSOR_NW_RESIZE:
    حالة SDL_SYSTEM_CURSOR_N_RESIZE:
    حالة SDL_SYSTEM_CURSOR_NE_RESIZE:
    حالة SDL_SYSTEM_CURSOR_E_RESIZE:
    حالة SDL_SYSTEM_CURSOR_SE_RESIZE:
    حالة SDL_SYSTEM_CURSOR_S_RESIZE:
    حالة SDL_SYSTEM_CURSOR_SW_RESIZE:
    حالة SDL_SYSTEM_CURSOR_W_RESIZE:
    حالة SDL_SYSTEM_CURSOR_خانہ_RESIZE:
    حالة SDL_SYSTEM_CURSOR_صف_RESIZE:
    حالة SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = SCREEN_CURSOR_SHAPE_MOVE;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_اشارہ_گر:
    حالة SDL_SYSTEM_CURSOR_HELP:
    حالة SDL_SYSTEM_CURSOR_ALIAS:
    حالة SDL_SYSTEM_CURSOR_COPY:
        shape = SCREEN_CURSOR_SHAPE_HAND;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        shape = SCREEN_CURSOR_SHAPE_MENU;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_GRAB:
        shape = SCREEN_CURSOR_SHAPE_GRAB;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_GRABBING:
        shape = SCREEN_CURSOR_SHAPE_GRABBING;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_ZOOM_وچ:
        shape = SCREEN_CURSOR_SHAPE_ZOOM_وچ;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_ZOOM_باہرلا:
        shape = SCREEN_CURSOR_SHAPE_ZOOM_باہرلا;
        اكسر;
    افتراضي:
        اكسر;
    }
    أرجع shape;
}

ساكن SDL_Cursor *genericCreateCursor(صحيح shape)
{
    SDL_Cursor          *cursor;
    SDL_Cursor_انکڑے      *impl;
    screen_session_t    session;
    screen_context_t    *context = getContext();

    cursor = SDL_calloc(1, حجم(SDL_Cursor));
    إذا (cursor) {
        impl = SDL_calloc(1, حجم(SDL_Cursor_انکڑے));;
        إذا (impl == عدم) {
            SDL_free(cursor);
            SDL_باہرلا_دا_حافظہ();
        }
        impl->realized_shape = shape;

        screen_create_session_type(&session, *context, SCREEN_EVENT_اشارہ_گر);
        screen_سیٹ_session_property_iv(session, SCREEN_PROPERTY_CURSOR, &shape);

        impl->session = session;
        impl->is_visible = true;
        cursor->اندرونی = (فراغ*)impl;
    } وإلا {
        SDL_باہرلا_دا_حافظہ();
    }

    أرجع cursor;
}

ساكن SDL_Cursor *createCursor(SDL_Surface * surface, صحيح hot_x, صحيح hot_y)
{
    أرجع genericCreateCursor(SCREEN_CURSOR_SHAPE_ARROW);
}

ساكن SDL_Cursor *createSystemCursor(SDL_SystemCursor id)
{
    صحيح shape = SDLToScreenCursorShape(id);
    إذا (shape < 0) {
        SDL_assert(0);
        أرجع عدم;
    }

    أرجع genericCreateCursor(shape);
}

ساكن bool showCursor(SDL_Cursor * cursor)
{
    SDL_Cursor_انکڑے      *impl;
    screen_session_t    session;
    صحيح shape;

    // SDL does not provide information about previous visibility to its
    // drivers. We need to track that ourselves.
    إذا (cursor) {
        impl = (SDL_Cursor_انکڑے*)cursor->اندرونی;
        SDL_assert(impl != عدم);
        إذا (impl->is_visible) {
            أرجع true;
        }
        session = impl->session;
        shape = impl->realized_shape;
        impl->is_visible = true;
    } وإلا {
        cursor = SDL_GetCursor();
        إذا (cursor == عدم) {
            أرجع false;
        }
        impl = (SDL_Cursor_انکڑے*)cursor->اندرونی;
        SDL_assert(impl != عدم);
        إذا (!impl->is_visible) {
            أرجع 0;
        }
        session = impl->session;
        shape = SCREEN_CURSOR_SHAPE_NONE;
        impl->is_visible = false;
    }

    إذا (screen_سیٹ_session_property_iv(session, SCREEN_PROPERTY_CURSOR, &shape) < 0) {
        أرجع false;
    }

    أرجع true;
}

ساكن فراغ freeCursor(SDL_Cursor * cursor)
{
    SDL_Cursor_انکڑے *impl = (SDL_Cursor_انکڑے*)cursor->اندرونی;
    إذا (impl != عدم) {
        screen_destroy_session(impl->session);
        SDL_free(impl);
    }
    SDL_free(cursor);
}

ساكن bool سیٹ_Relative_Mouse_منوال_2(bool enabled)
{
    // We're tracking rel-position explicitly, but this is still needed so
    // SDL_SetRelativeMouseMode() & friends aren't a no-op.
    //
    // TODO: It may be possible to achieve this using SCREEN_PROPERTY_DISPLACEMENT instead.
    أرجع true;
}

فراغ initMouse(SDL_VideoDevice *_this)
{
    SDL_Mouse       *mouse = SDL_GetMouse();
    SDL_Mouse_انکڑے   *mouse_انکڑے;

    mouse_انکڑے = (SDL_Mouse_انکڑے *)SDL_calloc(1, حجم(SDL_Mouse_انکڑے));
    إذا (mouse_انکڑے == عدم) {
        أرجع;
    }
    SDL_zerop(mouse_انکڑے);
    mouse->اندرونی = mouse_انکڑے;

    mouse->CreateCursor = createCursor;
    mouse->CreateSystemCursor = createSystemCursor;
    mouse->ShowCursor = showCursor;
    mouse->FreeCursor = freeCursor;

    mouse->سیٹ_Relative_Mouse_منوال = سیٹ_Relative_Mouse_منوال_2;

    SDL_سیٹ_Default_Cursor(createCursor(عدم, 0, 0));
}
