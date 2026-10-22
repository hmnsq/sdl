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


ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ SDLToScreenCursorShape(SDL_SystemCursor id)
{
    // This is reserved by screen, but still not used for anything.
    ಪೂರ್ಣಾಂಕ shape = -1;

    ಆಯ್ಕೆ(id)
    {
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_DEFAULT:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_NOT_ALLOWED:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_NO_DROP:
        shape = SCREEN_CURSOR_SHAPE_ARROW;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ಪಠ್ಯ:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_VERTICAL_ಪಠ್ಯ:
        shape = SCREEN_CURSOR_SHAPE_IBEAM;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_WAIT:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ಪ್ರಗತಿ:
        shape = SCREEN_CURSOR_SHAPE_WAIT;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_CROSSHAIR:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_CELL:
        shape = SCREEN_CURSOR_SHAPE_CROSS;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_NWSE_RESIZE:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_NESW_RESIZE:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_EW_RESIZE:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_NS_RESIZE:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_MOVE:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_NW_RESIZE:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_N_RESIZE:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_NE_RESIZE:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_E_RESIZE:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_SE_RESIZE:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_S_RESIZE:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_SW_RESIZE:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_W_RESIZE:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ಲಂಬಸಾಲು_RESIZE:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ಅಡ್ಡಸಾಲು_RESIZE:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = SCREEN_CURSOR_SHAPE_MOVE;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ಸೂಚಕ:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_HELP:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ALIAS:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_COPY:
        shape = SCREEN_CURSOR_SHAPE_HAND;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        shape = SCREEN_CURSOR_SHAPE_MENU;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_GRAB:
        shape = SCREEN_CURSOR_SHAPE_GRAB;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_GRABBING:
        shape = SCREEN_CURSOR_SHAPE_GRABBING;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ZOOM_ಒಳ:
        shape = SCREEN_CURSOR_SHAPE_ZOOM_ಒಳ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ZOOM_ಹೊರಹೋಗು:
        shape = SCREEN_CURSOR_SHAPE_ZOOM_ಹೊರಹೋಗು;
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ನಿಲ್ಲಿಸು;
    }
    ಹಿಂತಿರುಗಿ shape;
}

ಸ್ಥಿರ SDL_Cursor *genericCreateCursor(ಪೂರ್ಣಾಂಕ shape)
{
    SDL_Cursor          *cursor;
    SDL_Cursor_ದತ್ತಾಂಶ      *impl;
    screen_session_t    session;
    screen_context_t    *context = getContext();

    cursor = SDL_calloc(1, ಗಾತ್ರ(SDL_Cursor));
    ಆದರೆ (cursor) {
        impl = SDL_calloc(1, ಗಾತ್ರ(SDL_Cursor_ದತ್ತಾಂಶ));;
        ಆದರೆ (impl == ಖಾಲಿ) {
            SDL_free(cursor);
            SDL_ಹೊರಹೋಗು_ದ_ಸ್ಮರಣೆ();
        }
        impl->realized_shape = shape;

        screen_create_session_type(&session, *context, SCREEN_EVENT_ಸೂಚಕ);
        screen_ಗಣ_session_property_iv(session, SCREEN_PROPERTY_CURSOR, &shape);

        impl->session = session;
        impl->is_visible = true;
        cursor->ಆಂತರಿಕ = (ಶೂನ್ಯ*)impl;
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_ಹೊರಹೋಗು_ದ_ಸ್ಮರಣೆ();
    }

    ಹಿಂತಿರುಗಿ cursor;
}

ಸ್ಥಿರ SDL_Cursor *createCursor(SDL_Surface * surface, ಪೂರ್ಣಾಂಕ hot_x, ಪೂರ್ಣಾಂಕ hot_y)
{
    ಹಿಂತಿರುಗಿ genericCreateCursor(SCREEN_CURSOR_SHAPE_ARROW);
}

ಸ್ಥಿರ SDL_Cursor *createSystemCursor(SDL_SystemCursor id)
{
    ಪೂರ್ಣಾಂಕ shape = SDLToScreenCursorShape(id);
    ಆದರೆ (shape < 0) {
        SDL_assert(0);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಹಿಂತಿರುಗಿ genericCreateCursor(shape);
}

ಸ್ಥಿರ bool showCursor(SDL_Cursor * cursor)
{
    SDL_Cursor_ದತ್ತಾಂಶ      *impl;
    screen_session_t    session;
    ಪೂರ್ಣಾಂಕ shape;

    // SDL does not provide information about previous visibility to its
    // drivers. We need to track that ourselves.
    ಆದರೆ (cursor) {
        impl = (SDL_Cursor_ದತ್ತಾಂಶ*)cursor->ಆಂತರಿಕ;
        SDL_assert(impl != ಖಾಲಿ);
        ಆದರೆ (impl->is_visible) {
            ಹಿಂತಿರುಗಿ true;
        }
        session = impl->session;
        shape = impl->realized_shape;
        impl->is_visible = true;
    } ಇಲ್ಲದಿದ್ದರೆ {
        cursor = SDL_GetCursor();
        ಆದರೆ (cursor == ಖಾಲಿ) {
            ಹಿಂತಿರುಗಿ false;
        }
        impl = (SDL_Cursor_ದತ್ತಾಂಶ*)cursor->ಆಂತರಿಕ;
        SDL_assert(impl != ಖಾಲಿ);
        ಆದರೆ (!impl->is_visible) {
            ಹಿಂತಿರುಗಿ 0;
        }
        session = impl->session;
        shape = SCREEN_CURSOR_SHAPE_NONE;
        impl->is_visible = false;
    }

    ಆದರೆ (screen_ಗಣ_session_property_iv(session, SCREEN_PROPERTY_CURSOR, &shape) < 0) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ freeCursor(SDL_Cursor * cursor)
{
    SDL_Cursor_ದತ್ತಾಂಶ *impl = (SDL_Cursor_ದತ್ತಾಂಶ*)cursor->ಆಂತರಿಕ;
    ಆದರೆ (impl != ಖಾಲಿ) {
        screen_destroy_session(impl->session);
        SDL_free(impl);
    }
    SDL_free(cursor);
}

ಸ್ಥಿರ bool ಗಣ_Relative_Mouse_ಬಹುಲಕ_2(bool enabled)
{
    // We're tracking rel-position explicitly, but this is still needed so
    // SDL_SetRelativeMouseMode() & friends aren't a no-op.
    //
    // TODO: It may be possible to achieve this using SCREEN_PROPERTY_DISPLACEMENT instead.
    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ initMouse(SDL_VideoDevice *_this)
{
    SDL_Mouse       *mouse = SDL_GetMouse();
    SDL_Mouse_ದತ್ತಾಂಶ   *mouse_ದತ್ತಾಂಶ;

    mouse_ದತ್ತಾಂಶ = (SDL_Mouse_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_Mouse_ದತ್ತಾಂಶ));
    ಆದರೆ (mouse_ದತ್ತಾಂಶ == ಖಾಲಿ) {
        ಹಿಂತಿರುಗಿ;
    }
    SDL_zerop(mouse_ದತ್ತಾಂಶ);
    mouse->ಆಂತರಿಕ = mouse_ದತ್ತಾಂಶ;

    mouse->CreateCursor = createCursor;
    mouse->CreateSystemCursor = createSystemCursor;
    mouse->ShowCursor = showCursor;
    mouse->FreeCursor = freeCursor;

    mouse->ಗಣ_Relative_Mouse_ಬಹುಲಕ = ಗಣ_Relative_Mouse_ಬಹುಲಕ_2;

    SDL_ಗಣ_Default_Cursor(createCursor(ಖಾಲಿ, 0, 0));
}
