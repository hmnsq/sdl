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

#समावेश "SDL_internal.h"
#समावेश "../SDL_sysvideo.h"
#समावेश "SDL_qnx.h"
#समावेश "../../events/SDL_mouse_c.h"

#समावेश <errno.h>


अटल पूर्णांक SDLToScreenCursorShape(SDL_SystemCursor id)
{
    // This is reserved by screen, but still not used for anything.
    पूर्णांक shape = -1;

    चयन(id)
    {
    हाल SDL_SYSTEM_CURSOR_DEFAULT:
    हाल SDL_SYSTEM_CURSOR_NOT_ALLOWED:
    हाल SDL_SYSTEM_CURSOR_NO_DROP:
        shape = SCREEN_CURSOR_SHAPE_ARROW;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_TEXT:
    हाल SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        shape = SCREEN_CURSOR_SHAPE_IBEAM;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_WAIT:
    हाल SDL_SYSTEM_CURSOR_PROGRESS:
        shape = SCREEN_CURSOR_SHAPE_WAIT;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_CROSSHAIR:
    हाल SDL_SYSTEM_CURSOR_CELL:
        shape = SCREEN_CURSOR_SHAPE_CROSS;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_NWSE_RESIZE:
    हाल SDL_SYSTEM_CURSOR_NESW_RESIZE:
    हाल SDL_SYSTEM_CURSOR_EW_RESIZE:
    हाल SDL_SYSTEM_CURSOR_NS_RESIZE:
    हाल SDL_SYSTEM_CURSOR_MOVE:
    हाल SDL_SYSTEM_CURSOR_NW_RESIZE:
    हाल SDL_SYSTEM_CURSOR_N_RESIZE:
    हाल SDL_SYSTEM_CURSOR_NE_RESIZE:
    हाल SDL_SYSTEM_CURSOR_E_RESIZE:
    हाल SDL_SYSTEM_CURSOR_SE_RESIZE:
    हाल SDL_SYSTEM_CURSOR_S_RESIZE:
    हाल SDL_SYSTEM_CURSOR_SW_RESIZE:
    हाल SDL_SYSTEM_CURSOR_W_RESIZE:
    हाल SDL_SYSTEM_CURSOR_COL_RESIZE:
    हाल SDL_SYSTEM_CURSOR_ROW_RESIZE:
    हाल SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = SCREEN_CURSOR_SHAPE_MOVE;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_POINTER:
    हाल SDL_SYSTEM_CURSOR_HELP:
    हाल SDL_SYSTEM_CURSOR_ALIAS:
    हाल SDL_SYSTEM_CURSOR_COPY:
        shape = SCREEN_CURSOR_SHAPE_HAND;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        shape = SCREEN_CURSOR_SHAPE_MENU;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_GRAB:
        shape = SCREEN_CURSOR_SHAPE_GRAB;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_GRABBING:
        shape = SCREEN_CURSOR_SHAPE_GRABBING;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_ZOOM_IN:
        shape = SCREEN_CURSOR_SHAPE_ZOOM_IN;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_ZOOM_OUT:
        shape = SCREEN_CURSOR_SHAPE_ZOOM_OUT;
        अवरोध;
    शेष:
        अवरोध;
    }
    वापस shape;
}

अटल SDL_Cursor *genericCreateCursor(पूर्णांक shape)
{
    SDL_Cursor          *cursor;
    SDL_Cursor_तथ्य      *impl;
    screen_session_t    session;
    screen_context_t    *context = getContext();

    cursor = SDL_calloc(1, माप(SDL_Cursor));
    अगर (cursor) {
        impl = SDL_calloc(1, माप(SDL_Cursor_तथ्य));;
        अगर (impl == शून्य) {
            SDL_free(cursor);
            SDL_OutOfMemory();
        }
        impl->realized_shape = shape;

        screen_create_session_type(&session, *context, SCREEN_EVENT_POINTER);
        screen_set_session_property_iv(session, SCREEN_PROPERTY_CURSOR, &shape);

        impl->session = session;
        impl->is_visible = true;
        cursor->internal = (व्योम*)impl;
    } अन्यथा {
        SDL_OutOfMemory();
    }

    वापस cursor;
}

अटल SDL_Cursor *createCursor(SDL_Surface * surface, पूर्णांक hot_x, पूर्णांक hot_y)
{
    वापस genericCreateCursor(SCREEN_CURSOR_SHAPE_ARROW);
}

अटल SDL_Cursor *createSystemCursor(SDL_SystemCursor id)
{
    पूर्णांक shape = SDLToScreenCursorShape(id);
    अगर (shape < 0) {
        SDL_assert(0);
        वापस शून्य;
    }

    वापस genericCreateCursor(shape);
}

अटल bool showCursor(SDL_Cursor * cursor)
{
    SDL_Cursor_तथ्य      *impl;
    screen_session_t    session;
    पूर्णांक shape;

    // SDL does not provide information about previous visibility to its
    // drivers. We need to track that ourselves.
    अगर (cursor) {
        impl = (SDL_Cursor_तथ्य*)cursor->internal;
        SDL_assert(impl != शून्य);
        अगर (impl->is_visible) {
            वापस true;
        }
        session = impl->session;
        shape = impl->realized_shape;
        impl->is_visible = true;
    } अन्यथा {
        cursor = SDL_GetCursor();
        अगर (cursor == शून्य) {
            वापस false;
        }
        impl = (SDL_Cursor_तथ्य*)cursor->internal;
        SDL_assert(impl != शून्य);
        अगर (!impl->is_visible) {
            वापस 0;
        }
        session = impl->session;
        shape = SCREEN_CURSOR_SHAPE_NONE;
        impl->is_visible = false;
    }

    अगर (screen_set_session_property_iv(session, SCREEN_PROPERTY_CURSOR, &shape) < 0) {
        वापस false;
    }

    वापस true;
}

अटल व्योम freeCursor(SDL_Cursor * cursor)
{
    SDL_Cursor_तथ्य *impl = (SDL_Cursor_तथ्य*)cursor->internal;
    अगर (impl != शून्य) {
        screen_destroy_session(impl->session);
        SDL_free(impl);
    }
    SDL_free(cursor);
}

अटल bool setRelativeMouseMode(bool enabled)
{
    // We're tracking rel-position explicitly, but this is still needed so
    // SDL_SetRelativeMouseMode() & friends aren't a no-op.
    //
    // TODO: It may be possible to achieve this using SCREEN_PROPERTY_DISPLACEMENT instead.
    वापस true;
}

व्योम initMouse(SDL_VideoDevice *_this)
{
    SDL_Mouse       *mouse = SDL_GetMouse();
    SDL_Mouse_तथ्य   *mouse_तथ्य;

    mouse_तथ्य = (SDL_Mouse_तथ्य *)SDL_calloc(1, माप(SDL_Mouse_तथ्य));
    अगर (mouse_तथ्य == शून्य) {
        वापस;
    }
    SDL_zerop(mouse_तथ्य);
    mouse->internal = mouse_तथ्य;

    mouse->CreateCursor = createCursor;
    mouse->CreateSystemCursor = createSystemCursor;
    mouse->ShowCursor = showCursor;
    mouse->FreeCursor = freeCursor;

    mouse->SetRelativeMouseMode = setRelativeMouseMode;

    SDL_SetDefaultCursor(createCursor(शून्य, 0, 0));
}
