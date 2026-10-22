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

#અન્તર્ભાવ "SDL_internal.h"
#અન્તર્ભાવ "../SDL_sysvideo.h"
#અન્તર્ભાવ "SDL_qnx.h"
#અન્તર્ભાવ "../../events/SDL_mouse_c.h"

#અન્તર્ભાવ <errno.h>


સ્થિર પૂર્ણાંક SDLToScreenCursorShape(SDL_SystemCursor id)
{
    // This is reserved by screen, but still not used for anything.
    પૂર્ણાંક shape = -1;

    પસંદગી(id)
    {
    સ્થિતિ SDL_SYSTEM_CURSOR_DEFAULT:
    સ્થિતિ SDL_SYSTEM_CURSOR_NOT_ALLOWED:
    સ્થિતિ SDL_SYSTEM_CURSOR_NO_DROP:
        shape = SCREEN_CURSOR_SHAPE_ARROW;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_TEXT:
    સ્થિતિ SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        shape = SCREEN_CURSOR_SHAPE_IBEAM;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_WAIT:
    સ્થિતિ SDL_SYSTEM_CURSOR_PROGRESS:
        shape = SCREEN_CURSOR_SHAPE_WAIT;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_CROSSHAIR:
    સ્થિતિ SDL_SYSTEM_CURSOR_CELL:
        shape = SCREEN_CURSOR_SHAPE_CROSS;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_NWSE_RESIZE:
    સ્થિતિ SDL_SYSTEM_CURSOR_NESW_RESIZE:
    સ્થિતિ SDL_SYSTEM_CURSOR_EW_RESIZE:
    સ્થિતિ SDL_SYSTEM_CURSOR_NS_RESIZE:
    સ્થિતિ SDL_SYSTEM_CURSOR_MOVE:
    સ્થિતિ SDL_SYSTEM_CURSOR_NW_RESIZE:
    સ્થિતિ SDL_SYSTEM_CURSOR_N_RESIZE:
    સ્થિતિ SDL_SYSTEM_CURSOR_NE_RESIZE:
    સ્થિતિ SDL_SYSTEM_CURSOR_E_RESIZE:
    સ્થિતિ SDL_SYSTEM_CURSOR_SE_RESIZE:
    સ્થિતિ SDL_SYSTEM_CURSOR_S_RESIZE:
    સ્થિતિ SDL_SYSTEM_CURSOR_SW_RESIZE:
    સ્થિતિ SDL_SYSTEM_CURSOR_W_RESIZE:
    સ્થિતિ SDL_SYSTEM_CURSOR_COL_RESIZE:
    સ્થિતિ SDL_SYSTEM_CURSOR_ROW_RESIZE:
    સ્થિતિ SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = SCREEN_CURSOR_SHAPE_MOVE;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_POINTER:
    સ્થિતિ SDL_SYSTEM_CURSOR_HELP:
    સ્થિતિ SDL_SYSTEM_CURSOR_ALIAS:
    સ્થિતિ SDL_SYSTEM_CURSOR_COPY:
        shape = SCREEN_CURSOR_SHAPE_HAND;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        shape = SCREEN_CURSOR_SHAPE_MENU;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_GRAB:
        shape = SCREEN_CURSOR_SHAPE_GRAB;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_GRABBING:
        shape = SCREEN_CURSOR_SHAPE_GRABBING;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_ZOOM_IN:
        shape = SCREEN_CURSOR_SHAPE_ZOOM_IN;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_ZOOM_OUT:
        shape = SCREEN_CURSOR_SHAPE_ZOOM_OUT;
        તોડો;
    મૂળભૂત:
        તોડો;
    }
    પાછા shape;
}

સ્થિર SDL_Cursor *genericCreateCursor(પૂર્ણાંક shape)
{
    SDL_Cursor          *cursor;
    SDL_CursorData      *impl;
    screen_session_t    session;
    screen_context_t    *context = getContext();

    cursor = SDL_calloc(1, કદ(SDL_Cursor));
    જો (cursor) {
        impl = SDL_calloc(1, કદ(SDL_CursorData));;
        જો (impl == ખાલી) {
            SDL_free(cursor);
            SDL_OutOfMemory();
        }
        impl->realized_shape = shape;

        screen_create_session_type(&session, *context, SCREEN_EVENT_POINTER);
        screen_set_session_property_iv(session, SCREEN_PROPERTY_CURSOR, &shape);

        impl->session = session;
        impl->is_visible = true;
        cursor->internal = (શૂન્ય*)impl;
    } નહીંતર {
        SDL_OutOfMemory();
    }

    પાછા cursor;
}

સ્થિર SDL_Cursor *createCursor(SDL_Surface * surface, પૂર્ણાંક hot_x, પૂર્ણાંક hot_y)
{
    પાછા genericCreateCursor(SCREEN_CURSOR_SHAPE_ARROW);
}

સ્થિર SDL_Cursor *createSystemCursor(SDL_SystemCursor id)
{
    પૂર્ણાંક shape = SDLToScreenCursorShape(id);
    જો (shape < 0) {
        SDL_assert(0);
        પાછા ખાલી;
    }

    પાછા genericCreateCursor(shape);
}

સ્થિર bool showCursor(SDL_Cursor * cursor)
{
    SDL_CursorData      *impl;
    screen_session_t    session;
    પૂર્ણાંક shape;

    // SDL does not provide information about previous visibility to its
    // drivers. We need to track that ourselves.
    જો (cursor) {
        impl = (SDL_CursorData*)cursor->internal;
        SDL_assert(impl != ખાલી);
        જો (impl->is_visible) {
            પાછા true;
        }
        session = impl->session;
        shape = impl->realized_shape;
        impl->is_visible = true;
    } નહીંતર {
        cursor = SDL_GetCursor();
        જો (cursor == ખાલી) {
            પાછા false;
        }
        impl = (SDL_CursorData*)cursor->internal;
        SDL_assert(impl != ખાલી);
        જો (!impl->is_visible) {
            પાછા 0;
        }
        session = impl->session;
        shape = SCREEN_CURSOR_SHAPE_NONE;
        impl->is_visible = false;
    }

    જો (screen_set_session_property_iv(session, SCREEN_PROPERTY_CURSOR, &shape) < 0) {
        પાછા false;
    }

    પાછા true;
}

સ્થિર શૂન્ય freeCursor(SDL_Cursor * cursor)
{
    SDL_CursorData *impl = (SDL_CursorData*)cursor->internal;
    જો (impl != ખાલી) {
        screen_destroy_session(impl->session);
        SDL_free(impl);
    }
    SDL_free(cursor);
}

સ્થિર bool setRelativeMouseMode(bool enabled)
{
    // We're tracking rel-position explicitly, but this is still needed so
    // SDL_SetRelativeMouseMode() & friends aren't a no-op.
    //
    // TODO: It may be possible to achieve this using SCREEN_PROPERTY_DISPLACEMENT instead.
    પાછા true;
}

શૂન્ય initMouse(SDL_VideoDevice *_this)
{
    SDL_Mouse       *mouse = SDL_GetMouse();
    SDL_MouseData   *mouse_data;

    mouse_data = (SDL_MouseData *)SDL_calloc(1, કદ(SDL_MouseData));
    જો (mouse_data == ખાલી) {
        પાછા;
    }
    SDL_zerop(mouse_data);
    mouse->internal = mouse_data;

    mouse->CreateCursor = createCursor;
    mouse->CreateSystemCursor = createSystemCursor;
    mouse->ShowCursor = showCursor;
    mouse->FreeCursor = freeCursor;

    mouse->SetRelativeMouseMode = setRelativeMouseMode;

    SDL_SetDefaultCursor(createCursor(ખાલી, 0, 0));
}
