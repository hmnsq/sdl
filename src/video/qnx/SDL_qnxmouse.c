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

#অন্তর্ভাৱ "SDL_internal.h"
#অন্তর্ভাৱ "../SDL_sysvideo.h"
#অন্তর্ভাৱ "SDL_qnx.h"
#অন্তর্ভাৱ "../../events/SDL_mouse_c.h"

#অন্তর্ভাৱ <errno.h>


স্থির পূর্ণাঙ্ক SDLToScreenCursorShape(SDL_SystemCursor id)
{
    // This is reserved by screen, but still not used for anything.
    পূর্ণাঙ্ক shape = -1;

    ৱিকল্প(id)
    {
    পক্ষ SDL_SYSTEM_CURSOR_DEFAULT:
    পক্ষ SDL_SYSTEM_CURSOR_NOT_ALLOWED:
    পক্ষ SDL_SYSTEM_CURSOR_NO_DROP:
        shape = SCREEN_CURSOR_SHAPE_ARROW;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_TEXT:
    পক্ষ SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        shape = SCREEN_CURSOR_SHAPE_IBEAM;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_WAIT:
    পক্ষ SDL_SYSTEM_CURSOR_PROGRESS:
        shape = SCREEN_CURSOR_SHAPE_WAIT;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_CROSSHAIR:
    পক্ষ SDL_SYSTEM_CURSOR_CELL:
        shape = SCREEN_CURSOR_SHAPE_CROSS;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_NWSE_RESIZE:
    পক্ষ SDL_SYSTEM_CURSOR_NESW_RESIZE:
    পক্ষ SDL_SYSTEM_CURSOR_EW_RESIZE:
    পক্ষ SDL_SYSTEM_CURSOR_NS_RESIZE:
    পক্ষ SDL_SYSTEM_CURSOR_MOVE:
    পক্ষ SDL_SYSTEM_CURSOR_NW_RESIZE:
    পক্ষ SDL_SYSTEM_CURSOR_N_RESIZE:
    পক্ষ SDL_SYSTEM_CURSOR_NE_RESIZE:
    পক্ষ SDL_SYSTEM_CURSOR_E_RESIZE:
    পক্ষ SDL_SYSTEM_CURSOR_SE_RESIZE:
    পক্ষ SDL_SYSTEM_CURSOR_S_RESIZE:
    পক্ষ SDL_SYSTEM_CURSOR_SW_RESIZE:
    পক্ষ SDL_SYSTEM_CURSOR_W_RESIZE:
    পক্ষ SDL_SYSTEM_CURSOR_COL_RESIZE:
    পক্ষ SDL_SYSTEM_CURSOR_ROW_RESIZE:
    পক্ষ SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = SCREEN_CURSOR_SHAPE_MOVE;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_POINTER:
    পক্ষ SDL_SYSTEM_CURSOR_HELP:
    পক্ষ SDL_SYSTEM_CURSOR_ALIAS:
    পক্ষ SDL_SYSTEM_CURSOR_COPY:
        shape = SCREEN_CURSOR_SHAPE_HAND;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        shape = SCREEN_CURSOR_SHAPE_MENU;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_GRAB:
        shape = SCREEN_CURSOR_SHAPE_GRAB;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_GRABBING:
        shape = SCREEN_CURSOR_SHAPE_GRABBING;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_ZOOM_IN:
        shape = SCREEN_CURSOR_SHAPE_ZOOM_IN;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_ZOOM_OUT:
        shape = SCREEN_CURSOR_SHAPE_ZOOM_OUT;
        ভঙ্গ;
    স্ৱভাৱ:
        ভঙ্গ;
    }
    ঘূৰাই shape;
}

স্থির SDL_Cursor *genericCreateCursor(পূর্ণাঙ্ক shape)
{
    SDL_Cursor          *cursor;
    SDL_CursorData      *impl;
    screen_session_t    session;
    screen_context_t    *context = getContext();

    cursor = SDL_calloc(1, পরিমাণ(SDL_Cursor));
    যদি (cursor) {
        impl = SDL_calloc(1, পরিমাণ(SDL_CursorData));;
        যদি (impl == রিক্ত) {
            SDL_free(cursor);
            SDL_OutOfMemory();
        }
        impl->realized_shape = shape;

        screen_create_session_type(&session, *context, SCREEN_EVENT_POINTER);
        screen_set_session_property_iv(session, SCREEN_PROPERTY_CURSOR, &shape);

        impl->session = session;
        impl->is_visible = true;
        cursor->internal = (শূন্য*)impl;
    } অন্যথা {
        SDL_OutOfMemory();
    }

    ঘূৰাই cursor;
}

স্থির SDL_Cursor *createCursor(SDL_Surface * surface, পূর্ণাঙ্ক hot_x, পূর্ণাঙ্ক hot_y)
{
    ঘূৰাই genericCreateCursor(SCREEN_CURSOR_SHAPE_ARROW);
}

স্থির SDL_Cursor *createSystemCursor(SDL_SystemCursor id)
{
    পূর্ণাঙ্ক shape = SDLToScreenCursorShape(id);
    যদি (shape < 0) {
        SDL_assert(0);
        ঘূৰাই রিক্ত;
    }

    ঘূৰাই genericCreateCursor(shape);
}

স্থির bool showCursor(SDL_Cursor * cursor)
{
    SDL_CursorData      *impl;
    screen_session_t    session;
    পূর্ণাঙ্ক shape;

    // SDL does not provide information about previous visibility to its
    // drivers. We need to track that ourselves.
    যদি (cursor) {
        impl = (SDL_CursorData*)cursor->internal;
        SDL_assert(impl != রিক্ত);
        যদি (impl->is_visible) {
            ঘূৰাই true;
        }
        session = impl->session;
        shape = impl->realized_shape;
        impl->is_visible = true;
    } অন্যথা {
        cursor = SDL_GetCursor();
        যদি (cursor == রিক্ত) {
            ঘূৰাই false;
        }
        impl = (SDL_CursorData*)cursor->internal;
        SDL_assert(impl != রিক্ত);
        যদি (!impl->is_visible) {
            ঘূৰাই 0;
        }
        session = impl->session;
        shape = SCREEN_CURSOR_SHAPE_NONE;
        impl->is_visible = false;
    }

    যদি (screen_set_session_property_iv(session, SCREEN_PROPERTY_CURSOR, &shape) < 0) {
        ঘূৰাই false;
    }

    ঘূৰাই true;
}

স্থির শূন্য freeCursor(SDL_Cursor * cursor)
{
    SDL_CursorData *impl = (SDL_CursorData*)cursor->internal;
    যদি (impl != রিক্ত) {
        screen_destroy_session(impl->session);
        SDL_free(impl);
    }
    SDL_free(cursor);
}

স্থির bool setRelativeMouseMode(bool enabled)
{
    // We're tracking rel-position explicitly, but this is still needed so
    // SDL_SetRelativeMouseMode() & friends aren't a no-op.
    //
    // TODO: It may be possible to achieve this using SCREEN_PROPERTY_DISPLACEMENT instead.
    ঘূৰাই true;
}

শূন্য initMouse(SDL_VideoDevice *_this)
{
    SDL_Mouse       *mouse = SDL_GetMouse();
    SDL_MouseData   *mouse_data;

    mouse_data = (SDL_MouseData *)SDL_calloc(1, পরিমাণ(SDL_MouseData));
    যদি (mouse_data == রিক্ত) {
        ঘূৰাই;
    }
    SDL_zerop(mouse_data);
    mouse->internal = mouse_data;

    mouse->CreateCursor = createCursor;
    mouse->CreateSystemCursor = createSystemCursor;
    mouse->ShowCursor = showCursor;
    mouse->FreeCursor = freeCursor;

    mouse->SetRelativeMouseMode = setRelativeMouseMode;

    SDL_SetDefaultCursor(createCursor(রিক্ত, 0, 0));
}
