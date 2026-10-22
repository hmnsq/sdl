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

#അന്തര്ഭാവ "SDL_internal.h"
#അന്തര്ഭാവ "../SDL_sysvideo.h"
#അന്തര്ഭാവ "SDL_qnx.h"
#അന്തര്ഭാവ "../../events/SDL_mouse_c.h"

#അന്തര്ഭാവ <errno.h>


സ്ഥിതം പൂർണ്ണസംഖ്യ SDLToScreenCursorShape(SDL_SystemCursor id)
{
    // This is reserved by screen, but still not used for anything.
    പൂർണ്ണസംഖ്യ shape = -1;

    തിരഞ്ഞെടുപ്പ്(id)
    {
    അവസ്ഥ SDL_SYSTEM_CURSOR_DEFAULT:
    അവസ്ഥ SDL_SYSTEM_CURSOR_NOT_ALLOWED:
    അവസ്ഥ SDL_SYSTEM_CURSOR_NO_DROP:
        shape = SCREEN_CURSOR_SHAPE_ARROW;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_TEXT:
    അവസ്ഥ SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        shape = SCREEN_CURSOR_SHAPE_IBEAM;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_WAIT:
    അവസ്ഥ SDL_SYSTEM_CURSOR_PROGRESS:
        shape = SCREEN_CURSOR_SHAPE_WAIT;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_CROSSHAIR:
    അവസ്ഥ SDL_SYSTEM_CURSOR_CELL:
        shape = SCREEN_CURSOR_SHAPE_CROSS;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_NWSE_RESIZE:
    അവസ്ഥ SDL_SYSTEM_CURSOR_NESW_RESIZE:
    അവസ്ഥ SDL_SYSTEM_CURSOR_EW_RESIZE:
    അവസ്ഥ SDL_SYSTEM_CURSOR_NS_RESIZE:
    അവസ്ഥ SDL_SYSTEM_CURSOR_MOVE:
    അവസ്ഥ SDL_SYSTEM_CURSOR_NW_RESIZE:
    അവസ്ഥ SDL_SYSTEM_CURSOR_N_RESIZE:
    അവസ്ഥ SDL_SYSTEM_CURSOR_NE_RESIZE:
    അവസ്ഥ SDL_SYSTEM_CURSOR_E_RESIZE:
    അവസ്ഥ SDL_SYSTEM_CURSOR_SE_RESIZE:
    അവസ്ഥ SDL_SYSTEM_CURSOR_S_RESIZE:
    അവസ്ഥ SDL_SYSTEM_CURSOR_SW_RESIZE:
    അവസ്ഥ SDL_SYSTEM_CURSOR_W_RESIZE:
    അവസ്ഥ SDL_SYSTEM_CURSOR_COL_RESIZE:
    അവസ്ഥ SDL_SYSTEM_CURSOR_ROW_RESIZE:
    അവസ്ഥ SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = SCREEN_CURSOR_SHAPE_MOVE;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_POINTER:
    അവസ്ഥ SDL_SYSTEM_CURSOR_HELP:
    അവസ്ഥ SDL_SYSTEM_CURSOR_ALIAS:
    അവസ്ഥ SDL_SYSTEM_CURSOR_COPY:
        shape = SCREEN_CURSOR_SHAPE_HAND;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        shape = SCREEN_CURSOR_SHAPE_MENU;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_GRAB:
        shape = SCREEN_CURSOR_SHAPE_GRAB;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_GRABBING:
        shape = SCREEN_CURSOR_SHAPE_GRABBING;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_ZOOM_IN:
        shape = SCREEN_CURSOR_SHAPE_ZOOM_IN;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_ZOOM_OUT:
        shape = SCREEN_CURSOR_SHAPE_ZOOM_OUT;
        നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
        നിർത്തുക;
    }
    തിരികെ shape;
}

സ്ഥിതം SDL_Cursor *genericCreateCursor(പൂർണ്ണസംഖ്യ shape)
{
    SDL_Cursor          *cursor;
    SDL_CursorData      *impl;
    screen_session_t    session;
    screen_context_t    *context = getContext();

    cursor = SDL_calloc(1, വലുപ്പം(SDL_Cursor));
    എങ്കിൽ (cursor) {
        impl = SDL_calloc(1, വലുപ്പം(SDL_CursorData));;
        എങ്കിൽ (impl == ശൂന്യ) {
            SDL_free(cursor);
            SDL_OutOfMemory();
        }
        impl->realized_shape = shape;

        screen_create_session_type(&session, *context, SCREEN_EVENT_POINTER);
        screen_set_session_property_iv(session, SCREEN_PROPERTY_CURSOR, &shape);

        impl->session = session;
        impl->is_visible = true;
        cursor->internal = (ശൂന്യം*)impl;
    } അല്ലെങ്കിൽ {
        SDL_OutOfMemory();
    }

    തിരികെ cursor;
}

സ്ഥിതം SDL_Cursor *createCursor(SDL_Surface * surface, പൂർണ്ണസംഖ്യ hot_x, പൂർണ്ണസംഖ്യ hot_y)
{
    തിരികെ genericCreateCursor(SCREEN_CURSOR_SHAPE_ARROW);
}

സ്ഥിതം SDL_Cursor *createSystemCursor(SDL_SystemCursor id)
{
    പൂർണ്ണസംഖ്യ shape = SDLToScreenCursorShape(id);
    എങ്കിൽ (shape < 0) {
        SDL_assert(0);
        തിരികെ ശൂന്യ;
    }

    തിരികെ genericCreateCursor(shape);
}

സ്ഥിതം bool showCursor(SDL_Cursor * cursor)
{
    SDL_CursorData      *impl;
    screen_session_t    session;
    പൂർണ്ണസംഖ്യ shape;

    // SDL does not provide information about previous visibility to its
    // drivers. We need to track that ourselves.
    എങ്കിൽ (cursor) {
        impl = (SDL_CursorData*)cursor->internal;
        SDL_assert(impl != ശൂന്യ);
        എങ്കിൽ (impl->is_visible) {
            തിരികെ true;
        }
        session = impl->session;
        shape = impl->realized_shape;
        impl->is_visible = true;
    } അല്ലെങ്കിൽ {
        cursor = SDL_GetCursor();
        എങ്കിൽ (cursor == ശൂന്യ) {
            തിരികെ false;
        }
        impl = (SDL_CursorData*)cursor->internal;
        SDL_assert(impl != ശൂന്യ);
        എങ്കിൽ (!impl->is_visible) {
            തിരികെ 0;
        }
        session = impl->session;
        shape = SCREEN_CURSOR_SHAPE_NONE;
        impl->is_visible = false;
    }

    എങ്കിൽ (screen_set_session_property_iv(session, SCREEN_PROPERTY_CURSOR, &shape) < 0) {
        തിരികെ false;
    }

    തിരികെ true;
}

സ്ഥിതം ശൂന്യം freeCursor(SDL_Cursor * cursor)
{
    SDL_CursorData *impl = (SDL_CursorData*)cursor->internal;
    എങ്കിൽ (impl != ശൂന്യ) {
        screen_destroy_session(impl->session);
        SDL_free(impl);
    }
    SDL_free(cursor);
}

സ്ഥിതം bool setRelativeMouseMode(bool enabled)
{
    // We're tracking rel-position explicitly, but this is still needed so
    // SDL_SetRelativeMouseMode() & friends aren't a no-op.
    //
    // TODO: It may be possible to achieve this using SCREEN_PROPERTY_DISPLACEMENT instead.
    തിരികെ true;
}

ശൂന്യം initMouse(SDL_VideoDevice *_this)
{
    SDL_Mouse       *mouse = SDL_GetMouse();
    SDL_MouseData   *mouse_data;

    mouse_data = (SDL_MouseData *)SDL_calloc(1, വലുപ്പം(SDL_MouseData));
    എങ്കിൽ (mouse_data == ശൂന്യ) {
        തിരികെ;
    }
    SDL_zerop(mouse_data);
    mouse->internal = mouse_data;

    mouse->CreateCursor = createCursor;
    mouse->CreateSystemCursor = createSystemCursor;
    mouse->ShowCursor = showCursor;
    mouse->FreeCursor = freeCursor;

    mouse->SetRelativeMouseMode = setRelativeMouseMode;

    SDL_SetDefaultCursor(createCursor(ശൂന്യ, 0, 0));
}
