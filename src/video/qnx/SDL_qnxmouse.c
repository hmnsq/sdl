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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_qnx.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <errno.h>


ਸਥਿਰ ਪੂਰਨ SDLToScreenCursorShape(SDL_SystemCursor id)
{
    // This is reserved by screen, but still not used for anything.
    ਪੂਰਨ shape = -1;

    ਚੋਣ(id)
    {
    ਹਾਲਤ SDL_SYSTEM_CURSOR_DEFAULT:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_NOT_ALLOWED:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_NO_DROP:
        shape = SCREEN_CURSOR_SHAPE_ARROW;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_ਪਾਠ:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_VERTICAL_ਪਾਠ:
        shape = SCREEN_CURSOR_SHAPE_IBEAM;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_WAIT:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_ਤਰੱਕੀ:
        shape = SCREEN_CURSOR_SHAPE_WAIT;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_CROSSHAIR:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_CELL:
        shape = SCREEN_CURSOR_SHAPE_CROSS;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_NWSE_RESIZE:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_NESW_RESIZE:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_EW_RESIZE:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_NS_RESIZE:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_MOVE:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_NW_RESIZE:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_N_RESIZE:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_NE_RESIZE:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_E_RESIZE:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_SE_RESIZE:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_S_RESIZE:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_SW_RESIZE:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_W_RESIZE:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_ਖਾਨਾ_RESIZE:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_ਪੰਕਤੀ_RESIZE:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = SCREEN_CURSOR_SHAPE_MOVE;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_ਸੂਚਕ:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_HELP:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_ALIAS:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_COPY:
        shape = SCREEN_CURSOR_SHAPE_HAND;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        shape = SCREEN_CURSOR_SHAPE_MENU;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_GRAB:
        shape = SCREEN_CURSOR_SHAPE_GRAB;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_GRABBING:
        shape = SCREEN_CURSOR_SHAPE_GRABBING;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_ZOOM_ਵਿੱਚ:
        shape = SCREEN_CURSOR_SHAPE_ZOOM_ਵਿੱਚ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_ZOOM_ਬਾਹਰਲਾ:
        shape = SCREEN_CURSOR_SHAPE_ZOOM_ਬਾਹਰਲਾ;
        ਰੋਕੋ;
    ਮੂਲ:
        ਰੋਕੋ;
    }
    ਵਾਪਸ shape;
}

ਸਥਿਰ SDL_Cursor *genericCreateCursor(ਪੂਰਨ shape)
{
    SDL_Cursor          *cursor;
    SDL_Cursor_ਅੰਕੜੇ      *impl;
    screen_session_t    session;
    screen_context_t    *context = getContext();

    cursor = SDL_calloc(1, ਆਕਾਰ(SDL_Cursor));
    ਜੇ (cursor) {
        impl = SDL_calloc(1, ਆਕਾਰ(SDL_Cursor_ਅੰਕੜੇ));;
        ਜੇ (impl == ਨਿਰਾ) {
            SDL_free(cursor);
            SDL_ਬਾਹਰਲਾ_ਦਾ_ਸਮ੍ਰਿਤੀ();
        }
        impl->realized_shape = shape;

        screen_create_session_type(&session, *context, SCREEN_EVENT_ਸੂਚਕ);
        screen_ਸੈੱਟ_session_property_iv(session, SCREEN_PROPERTY_CURSOR, &shape);

        impl->session = session;
        impl->is_visible = true;
        cursor->ਅੰਦਰੂਨੀ = (ਖਾਲੀ*)impl;
    } ਨਹੀਂਤਾਂ {
        SDL_ਬਾਹਰਲਾ_ਦਾ_ਸਮ੍ਰਿਤੀ();
    }

    ਵਾਪਸ cursor;
}

ਸਥਿਰ SDL_Cursor *createCursor(SDL_Surface * surface, ਪੂਰਨ hot_x, ਪੂਰਨ hot_y)
{
    ਵਾਪਸ genericCreateCursor(SCREEN_CURSOR_SHAPE_ARROW);
}

ਸਥਿਰ SDL_Cursor *createSystemCursor(SDL_SystemCursor id)
{
    ਪੂਰਨ shape = SDLToScreenCursorShape(id);
    ਜੇ (shape < 0) {
        SDL_assert(0);
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਵਾਪਸ genericCreateCursor(shape);
}

ਸਥਿਰ bool showCursor(SDL_Cursor * cursor)
{
    SDL_Cursor_ਅੰਕੜੇ      *impl;
    screen_session_t    session;
    ਪੂਰਨ shape;

    // SDL does not provide information about previous visibility to its
    // drivers. We need to track that ourselves.
    ਜੇ (cursor) {
        impl = (SDL_Cursor_ਅੰਕੜੇ*)cursor->ਅੰਦਰੂਨੀ;
        SDL_assert(impl != ਨਿਰਾ);
        ਜੇ (impl->is_visible) {
            ਵਾਪਸ true;
        }
        session = impl->session;
        shape = impl->realized_shape;
        impl->is_visible = true;
    } ਨਹੀਂਤਾਂ {
        cursor = SDL_GetCursor();
        ਜੇ (cursor == ਨਿਰਾ) {
            ਵਾਪਸ false;
        }
        impl = (SDL_Cursor_ਅੰਕੜੇ*)cursor->ਅੰਦਰੂਨੀ;
        SDL_assert(impl != ਨਿਰਾ);
        ਜੇ (!impl->is_visible) {
            ਵਾਪਸ 0;
        }
        session = impl->session;
        shape = SCREEN_CURSOR_SHAPE_NONE;
        impl->is_visible = false;
    }

    ਜੇ (screen_ਸੈੱਟ_session_property_iv(session, SCREEN_PROPERTY_CURSOR, &shape) < 0) {
        ਵਾਪਸ false;
    }

    ਵਾਪਸ true;
}

ਸਥਿਰ ਖਾਲੀ freeCursor(SDL_Cursor * cursor)
{
    SDL_Cursor_ਅੰਕੜੇ *impl = (SDL_Cursor_ਅੰਕੜੇ*)cursor->ਅੰਦਰੂਨੀ;
    ਜੇ (impl != ਨਿਰਾ) {
        screen_destroy_session(impl->session);
        SDL_free(impl);
    }
    SDL_free(cursor);
}

ਸਥਿਰ bool ਸੈੱਟ_Relative_Mouse_ਬਹੁਲਕ_2(bool enabled)
{
    // We're tracking rel-position explicitly, but this is still needed so
    // SDL_SetRelativeMouseMode() & friends aren't a no-op.
    //
    // TODO: It may be possible to achieve this using SCREEN_PROPERTY_DISPLACEMENT instead.
    ਵਾਪਸ true;
}

ਖਾਲੀ initMouse(SDL_VideoDevice *_this)
{
    SDL_Mouse       *mouse = SDL_GetMouse();
    SDL_Mouse_ਅੰਕੜੇ   *mouse_ਅੰਕੜੇ;

    mouse_ਅੰਕੜੇ = (SDL_Mouse_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(SDL_Mouse_ਅੰਕੜੇ));
    ਜੇ (mouse_ਅੰਕੜੇ == ਨਿਰਾ) {
        ਵਾਪਸ;
    }
    SDL_zerop(mouse_ਅੰਕੜੇ);
    mouse->ਅੰਦਰੂਨੀ = mouse_ਅੰਕੜੇ;

    mouse->CreateCursor = createCursor;
    mouse->CreateSystemCursor = createSystemCursor;
    mouse->ShowCursor = showCursor;
    mouse->FreeCursor = freeCursor;

    mouse->ਸੈੱਟ_Relative_Mouse_ਬਹੁਲਕ = ਸੈੱਟ_Relative_Mouse_ਬਹੁਲਕ_2;

    SDL_ਸੈੱਟ_Default_Cursor(createCursor(ਨਿਰਾ, 0, 0));
}
