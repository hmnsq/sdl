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

#अन्तर्भाव "SDL_internal.h"
#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "SDL_qnx.h"
#अन्तर्भाव "../../events/SDL_mouse_c.h"

#अन्तर्भाव <errno.h>


स्थिर पूर्णाङ्क SDLToScreenCursorShape(SDL_SystemCursor id)
{
    // This is reserved by screen, but still not used for anything.
    पूर्णाङ्क shape = -1;

    विकल्प(id)
    {
    पक्ष SDL_SYSTEM_CURSOR_DEFAULT:
    पक्ष SDL_SYSTEM_CURSOR_NOT_ALLOWED:
    पक्ष SDL_SYSTEM_CURSOR_NO_DROP:
        shape = SCREEN_CURSOR_SHAPE_ARROW;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_TEXT:
    पक्ष SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        shape = SCREEN_CURSOR_SHAPE_IBEAM;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_WAIT:
    पक्ष SDL_SYSTEM_CURSOR_प्रगतिः:
        shape = SCREEN_CURSOR_SHAPE_WAIT;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_CROSSHAIR:
    पक्ष SDL_SYSTEM_CURSOR_CELL:
        shape = SCREEN_CURSOR_SHAPE_CROSS;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_NWSE_RESIZE:
    पक्ष SDL_SYSTEM_CURSOR_NESW_RESIZE:
    पक्ष SDL_SYSTEM_CURSOR_EW_RESIZE:
    पक्ष SDL_SYSTEM_CURSOR_NS_RESIZE:
    पक्ष SDL_SYSTEM_CURSOR_MOVE:
    पक्ष SDL_SYSTEM_CURSOR_NW_RESIZE:
    पक्ष SDL_SYSTEM_CURSOR_N_RESIZE:
    पक्ष SDL_SYSTEM_CURSOR_NE_RESIZE:
    पक्ष SDL_SYSTEM_CURSOR_E_RESIZE:
    पक्ष SDL_SYSTEM_CURSOR_SE_RESIZE:
    पक्ष SDL_SYSTEM_CURSOR_S_RESIZE:
    पक्ष SDL_SYSTEM_CURSOR_SW_RESIZE:
    पक्ष SDL_SYSTEM_CURSOR_W_RESIZE:
    पक्ष SDL_SYSTEM_CURSOR_COL_RESIZE:
    पक्ष SDL_SYSTEM_CURSOR_ROW_RESIZE:
    पक्ष SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = SCREEN_CURSOR_SHAPE_MOVE;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_POINTER:
    पक्ष SDL_SYSTEM_CURSOR_HELP:
    पक्ष SDL_SYSTEM_CURSOR_ALIAS:
    पक्ष SDL_SYSTEM_CURSOR_COPY:
        shape = SCREEN_CURSOR_SHAPE_HAND;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        shape = SCREEN_CURSOR_SHAPE_MENU;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_GRAB:
        shape = SCREEN_CURSOR_SHAPE_GRAB;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_GRABBING:
        shape = SCREEN_CURSOR_SHAPE_GRABBING;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_ZOOM_अन्तर्:
        shape = SCREEN_CURSOR_SHAPE_ZOOM_अन्तर्;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_ZOOM_बहिर्गमनम्:
        shape = SCREEN_CURSOR_SHAPE_ZOOM_बहिर्गमनम्;
        भङ्ग;
    स्वभाव:
        भङ्ग;
    }
    प्रत्यागम shape;
}

स्थिर SDL_Cursor *genericCreateCursor(पूर्णाङ्क shape)
{
    SDL_Cursor          *cursor;
    SDL_Cursor_दत्त      *impl;
    screen_session_t    session;
    screen_context_t    *context = getContext();

    cursor = SDL_calloc(1, परिमाण(SDL_Cursor));
    यदि (cursor) {
        impl = SDL_calloc(1, परिमाण(SDL_Cursor_दत्त));;
        यदि (impl == रिक्त) {
            SDL_free(cursor);
            SDL_बहिर्गमनम्_सम्बन्धि_स्मृतिः();
        }
        impl->realized_shape = shape;

        screen_create_session_type(&session, *context, SCREEN_EVENT_POINTER);
        screen_समुच्चयः_session_property_iv(session, SCREEN_PROPERTY_CURSOR, &shape);

        impl->session = session;
        impl->is_visible = true;
        cursor->आन्तरिकम् = (शून्य*)impl;
    } अन्यथा {
        SDL_बहिर्गमनम्_सम्बन्धि_स्मृतिः();
    }

    प्रत्यागम cursor;
}

स्थिर SDL_Cursor *createCursor(SDL_Surface * surface, पूर्णाङ्क hot_x, पूर्णाङ्क hot_y)
{
    प्रत्यागम genericCreateCursor(SCREEN_CURSOR_SHAPE_ARROW);
}

स्थिर SDL_Cursor *createSystemCursor(SDL_SystemCursor id)
{
    पूर्णाङ्क shape = SDLToScreenCursorShape(id);
    यदि (shape < 0) {
        SDL_assert(0);
        प्रत्यागम रिक्त;
    }

    प्रत्यागम genericCreateCursor(shape);
}

स्थिर bool showCursor(SDL_Cursor * cursor)
{
    SDL_Cursor_दत्त      *impl;
    screen_session_t    session;
    पूर्णाङ्क shape;

    // SDL does not provide information about previous visibility to its
    // drivers. We need to track that ourselves.
    यदि (cursor) {
        impl = (SDL_Cursor_दत्त*)cursor->आन्तरिकम्;
        SDL_assert(impl != रिक्त);
        यदि (impl->is_visible) {
            प्रत्यागम true;
        }
        session = impl->session;
        shape = impl->realized_shape;
        impl->is_visible = true;
    } अन्यथा {
        cursor = SDL_GetCursor();
        यदि (cursor == रिक्त) {
            प्रत्यागम false;
        }
        impl = (SDL_Cursor_दत्त*)cursor->आन्तरिकम्;
        SDL_assert(impl != रिक्त);
        यदि (!impl->is_visible) {
            प्रत्यागम 0;
        }
        session = impl->session;
        shape = SCREEN_CURSOR_SHAPE_NONE;
        impl->is_visible = false;
    }

    यदि (screen_समुच्चयः_session_property_iv(session, SCREEN_PROPERTY_CURSOR, &shape) < 0) {
        प्रत्यागम false;
    }

    प्रत्यागम true;
}

स्थिर शून्य freeCursor(SDL_Cursor * cursor)
{
    SDL_Cursor_दत्त *impl = (SDL_Cursor_दत्त*)cursor->आन्तरिकम्;
    यदि (impl != रिक्त) {
        screen_destroy_session(impl->session);
        SDL_free(impl);
    }
    SDL_free(cursor);
}

स्थिर bool समुच्चयः_Relative_Mouse_बहुलकम्_2(bool enabled)
{
    // We're tracking rel-position explicitly, but this is still needed so
    // SDL_SetRelativeMouseMode() & friends aren't a no-op.
    //
    // TODO: It may be possible to achieve this using SCREEN_PROPERTY_DISPLACEMENT instead.
    प्रत्यागम true;
}

शून्य initMouse(SDL_VideoDevice *_this)
{
    SDL_Mouse       *mouse = SDL_GetMouse();
    SDL_Mouse_दत्त   *mouse_दत्त;

    mouse_दत्त = (SDL_Mouse_दत्त *)SDL_calloc(1, परिमाण(SDL_Mouse_दत्त));
    यदि (mouse_दत्त == रिक्त) {
        प्रत्यागम;
    }
    SDL_zerop(mouse_दत्त);
    mouse->आन्तरिकम् = mouse_दत्त;

    mouse->CreateCursor = createCursor;
    mouse->CreateSystemCursor = createSystemCursor;
    mouse->ShowCursor = showCursor;
    mouse->FreeCursor = freeCursor;

    mouse->समुच्चयः_Relative_Mouse_बहुलकम् = समुच्चयः_Relative_Mouse_बहुलकम्_2;

    SDL_समुच्चयः_Default_Cursor(createCursor(रिक्त, 0, 0));
}
