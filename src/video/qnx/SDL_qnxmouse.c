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

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"
#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_qnx.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"

#ಅನ್ತರ್ಭಾವ <errno.h>


ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ SDLToScreenCursorShape(SDL_SystemCursor id)
{
    // This is reserved by screen, but still not used for anything.
    ಪೂರ್ಣಾಙ್ಕ shape = -1;

    ವಿಕಲ್ಪ(id)
    {
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_DEFAULT:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_NOT_ALLOWED:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_NO_DROP:
        shape = SCREEN_CURSOR_SHAPE_ARROW;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_TEXT:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        shape = SCREEN_CURSOR_SHAPE_IBEAM;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_WAIT:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_PROGRESS:
        shape = SCREEN_CURSOR_SHAPE_WAIT;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_CROSSHAIR:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_CELL:
        shape = SCREEN_CURSOR_SHAPE_CROSS;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_NWSE_RESIZE:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_NESW_RESIZE:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_EW_RESIZE:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_NS_RESIZE:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_MOVE:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_NW_RESIZE:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_N_RESIZE:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_NE_RESIZE:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_E_RESIZE:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_SE_RESIZE:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_S_RESIZE:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_SW_RESIZE:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_W_RESIZE:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_COL_RESIZE:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_ROW_RESIZE:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = SCREEN_CURSOR_SHAPE_MOVE;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_POINTER:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_HELP:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_ALIAS:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_COPY:
        shape = SCREEN_CURSOR_SHAPE_HAND;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        shape = SCREEN_CURSOR_SHAPE_MENU;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_GRAB:
        shape = SCREEN_CURSOR_SHAPE_GRAB;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_GRABBING:
        shape = SCREEN_CURSOR_SHAPE_GRABBING;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_ZOOM_IN:
        shape = SCREEN_CURSOR_SHAPE_ZOOM_IN;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_ZOOM_OUT:
        shape = SCREEN_CURSOR_SHAPE_ZOOM_OUT;
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        ಭಙ್ಗ;
    }
    ಪ್ರತ್ಯಾಗಮ shape;
}

ಸ್ಥಿರ SDL_Cursor *genericCreateCursor(ಪೂರ್ಣಾಙ್ಕ shape)
{
    SDL_Cursor          *cursor;
    SDL_CursorData      *impl;
    screen_session_t    session;
    screen_context_t    *context = getContext();

    cursor = SDL_calloc(1, ಪರಿಮಾಣ(SDL_Cursor));
    ಯದಿ (cursor) {
        impl = SDL_calloc(1, ಪರಿಮಾಣ(SDL_CursorData));;
        ಯದಿ (impl == ರಿಕ್ತ) {
            SDL_free(cursor);
            SDL_OutOfMemory();
        }
        impl->realized_shape = shape;

        screen_create_session_type(&session, *context, SCREEN_EVENT_POINTER);
        screen_set_session_property_iv(session, SCREEN_PROPERTY_CURSOR, &shape);

        impl->session = session;
        impl->is_visible = true;
        cursor->internal = (ಶೂನ್ಯ*)impl;
    } ಅನ್ಯಥಾ {
        SDL_OutOfMemory();
    }

    ಪ್ರತ್ಯಾಗಮ cursor;
}

ಸ್ಥಿರ SDL_Cursor *createCursor(SDL_Surface * surface, ಪೂರ್ಣಾಙ್ಕ hot_x, ಪೂರ್ಣಾಙ್ಕ hot_y)
{
    ಪ್ರತ್ಯಾಗಮ genericCreateCursor(SCREEN_CURSOR_SHAPE_ARROW);
}

ಸ್ಥಿರ SDL_Cursor *createSystemCursor(SDL_SystemCursor id)
{
    ಪೂರ್ಣಾಙ್ಕ shape = SDLToScreenCursorShape(id);
    ಯದಿ (shape < 0) {
        SDL_assert(0);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಪ್ರತ್ಯಾಗಮ genericCreateCursor(shape);
}

ಸ್ಥಿರ bool showCursor(SDL_Cursor * cursor)
{
    SDL_CursorData      *impl;
    screen_session_t    session;
    ಪೂರ್ಣಾಙ್ಕ shape;

    // SDL does not provide information about previous visibility to its
    // drivers. We need to track that ourselves.
    ಯದಿ (cursor) {
        impl = (SDL_CursorData*)cursor->internal;
        SDL_assert(impl != ರಿಕ್ತ);
        ಯದಿ (impl->is_visible) {
            ಪ್ರತ್ಯಾಗಮ true;
        }
        session = impl->session;
        shape = impl->realized_shape;
        impl->is_visible = true;
    } ಅನ್ಯಥಾ {
        cursor = SDL_GetCursor();
        ಯದಿ (cursor == ರಿಕ್ತ) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
        impl = (SDL_CursorData*)cursor->internal;
        SDL_assert(impl != ರಿಕ್ತ);
        ಯದಿ (!impl->is_visible) {
            ಪ್ರತ್ಯಾಗಮ 0;
        }
        session = impl->session;
        shape = SCREEN_CURSOR_SHAPE_NONE;
        impl->is_visible = false;
    }

    ಯದಿ (screen_set_session_property_iv(session, SCREEN_PROPERTY_CURSOR, &shape) < 0) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ freeCursor(SDL_Cursor * cursor)
{
    SDL_CursorData *impl = (SDL_CursorData*)cursor->internal;
    ಯದಿ (impl != ರಿಕ್ತ) {
        screen_destroy_session(impl->session);
        SDL_free(impl);
    }
    SDL_free(cursor);
}

ಸ್ಥಿರ bool setRelativeMouseMode(bool enabled)
{
    // We're tracking rel-position explicitly, but this is still needed so
    // SDL_SetRelativeMouseMode() & friends aren't a no-op.
    //
    // TODO: It may be possible to achieve this using SCREEN_PROPERTY_DISPLACEMENT instead.
    ಪ್ರತ್ಯಾಗಮ true;
}

ಶೂನ್ಯ initMouse(SDL_VideoDevice *_this)
{
    SDL_Mouse       *mouse = SDL_GetMouse();
    SDL_MouseData   *mouse_data;

    mouse_data = (SDL_MouseData *)SDL_calloc(1, ಪರಿಮಾಣ(SDL_MouseData));
    ಯದಿ (mouse_data == ರಿಕ್ತ) {
        ಪ್ರತ್ಯಾಗಮ;
    }
    SDL_zerop(mouse_data);
    mouse->internal = mouse_data;

    mouse->CreateCursor = createCursor;
    mouse->CreateSystemCursor = createSystemCursor;
    mouse->ShowCursor = showCursor;
    mouse->FreeCursor = freeCursor;

    mouse->SetRelativeMouseMode = setRelativeMouseMode;

    SDL_SetDefaultCursor(createCursor(ರಿಕ್ತ, 0, 0));
}
