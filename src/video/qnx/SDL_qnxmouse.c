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

#include "SDL_internal.h"
#include "../SDL_sysvideo.h"
#include "SDL_qnx.h"
#include "../../events/SDL_mouse_c.h"

#include <errno.h>


static 정수 SDLToScreenCursorShape(SDL_SystemCursor id)
{
    // This is reserved by screen, but still not used for anything.
    정수 shape = -1;

    switch(id)
    {
    case SDL_SYSTEM_CURSOR_DEFAULT:
    case SDL_SYSTEM_CURSOR_NOT_ALLOWED:
    case SDL_SYSTEM_CURSOR_NO_DROP:
        shape = SCREEN_CURSOR_SHAPE_ARROW;
        break;
    case SDL_SYSTEM_CURSOR_TEXT:
    case SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        shape = SCREEN_CURSOR_SHAPE_IBEAM;
        break;
    case SDL_SYSTEM_CURSOR_WAIT:
    case SDL_SYSTEM_CURSOR_PROGRESS:
        shape = SCREEN_CURSOR_SHAPE_WAIT;
        break;
    case SDL_SYSTEM_CURSOR_CROSSHAIR:
    case SDL_SYSTEM_CURSOR_CELL:
        shape = SCREEN_CURSOR_SHAPE_CROSS;
        break;
    case SDL_SYSTEM_CURSOR_NWSE_RESIZE:
    case SDL_SYSTEM_CURSOR_NESW_RESIZE:
    case SDL_SYSTEM_CURSOR_EW_RESIZE:
    case SDL_SYSTEM_CURSOR_NS_RESIZE:
    case SDL_SYSTEM_CURSOR_MOVE:
    case SDL_SYSTEM_CURSOR_NW_RESIZE:
    case SDL_SYSTEM_CURSOR_N_RESIZE:
    case SDL_SYSTEM_CURSOR_NE_RESIZE:
    case SDL_SYSTEM_CURSOR_E_RESIZE:
    case SDL_SYSTEM_CURSOR_SE_RESIZE:
    case SDL_SYSTEM_CURSOR_S_RESIZE:
    case SDL_SYSTEM_CURSOR_SW_RESIZE:
    case SDL_SYSTEM_CURSOR_W_RESIZE:
    case SDL_SYSTEM_CURSOR_COL_RESIZE:
    case SDL_SYSTEM_CURSOR_ROW_RESIZE:
    case SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = SCREEN_CURSOR_SHAPE_MOVE;
        break;
    case SDL_SYSTEM_CURSOR_POINTER:
    case SDL_SYSTEM_CURSOR_HELP:
    case SDL_SYSTEM_CURSOR_ALIAS:
    case SDL_SYSTEM_CURSOR_COPY:
        shape = SCREEN_CURSOR_SHAPE_HAND;
        break;
    case SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        shape = SCREEN_CURSOR_SHAPE_MENU;
        break;
    case SDL_SYSTEM_CURSOR_GRAB:
        shape = SCREEN_CURSOR_SHAPE_GRAB;
        break;
    case SDL_SYSTEM_CURSOR_GRABBING:
        shape = SCREEN_CURSOR_SHAPE_GRABBING;
        break;
    case SDL_SYSTEM_CURSOR_ZOOM_IN:
        shape = SCREEN_CURSOR_SHAPE_ZOOM_IN;
        break;
    case SDL_SYSTEM_CURSOR_ZOOM_OUT:
        shape = SCREEN_CURSOR_SHAPE_ZOOM_OUT;
        break;
    default:
        break;
    }
    반환 shape;
}

static SDL_Cursor *genericCreateCursor(정수 shape)
{
    SDL_Cursor          *cursor;
    SDL_CursorData      *impl;
    screen_session_t    session;
    screen_context_t    *context = getContext();

    cursor = SDL_calloc(1, sizeof(SDL_Cursor));
    만약 (cursor) {
        impl = SDL_calloc(1, sizeof(SDL_CursorData));;
        만약 (impl == NULL) {
            SDL_free(cursor);
            SDL_OutOfMemory();
        }
        impl->realized_shape = shape;

        screen_create_session_type(&session, *context, SCREEN_EVENT_POINTER);
        screen_set_session_property_iv(session, SCREEN_PROPERTY_CURSOR, &shape);

        impl->session = session;
        impl->is_visible = true;
        cursor->internal = (void*)impl;
    } 아니면 {
        SDL_OutOfMemory();
    }

    반환 cursor;
}

static SDL_Cursor *createCursor(SDL_Surface * surface, 정수 hot_x, 정수 hot_y)
{
    반환 genericCreateCursor(SCREEN_CURSOR_SHAPE_ARROW);
}

static SDL_Cursor *createSystemCursor(SDL_SystemCursor id)
{
    정수 shape = SDLToScreenCursorShape(id);
    만약 (shape < 0) {
        SDL_assert(0);
        반환 NULL;
    }

    반환 genericCreateCursor(shape);
}

static bool showCursor(SDL_Cursor * cursor)
{
    SDL_CursorData      *impl;
    screen_session_t    session;
    정수 shape;

    // SDL does not provide information about previous visibility to its
    // drivers. We need to track that ourselves.
    만약 (cursor) {
        impl = (SDL_CursorData*)cursor->internal;
        SDL_assert(impl != NULL);
        만약 (impl->is_visible) {
            반환 true;
        }
        session = impl->session;
        shape = impl->realized_shape;
        impl->is_visible = true;
    } 아니면 {
        cursor = SDL_GetCursor();
        만약 (cursor == NULL) {
            반환 false;
        }
        impl = (SDL_CursorData*)cursor->internal;
        SDL_assert(impl != NULL);
        만약 (!impl->is_visible) {
            반환 0;
        }
        session = impl->session;
        shape = SCREEN_CURSOR_SHAPE_NONE;
        impl->is_visible = false;
    }

    만약 (screen_set_session_property_iv(session, SCREEN_PROPERTY_CURSOR, &shape) < 0) {
        반환 false;
    }

    반환 true;
}

static void freeCursor(SDL_Cursor * cursor)
{
    SDL_CursorData *impl = (SDL_CursorData*)cursor->internal;
    만약 (impl != NULL) {
        screen_destroy_session(impl->session);
        SDL_free(impl);
    }
    SDL_free(cursor);
}

static bool setRelativeMouseMode(bool enabled)
{
    // We're tracking rel-position explicitly, but this is still needed so
    // SDL_SetRelativeMouseMode() & friends aren't a no-op.
    //
    // TODO: It may be possible to achieve this using SCREEN_PROPERTY_DISPLACEMENT instead.
    반환 true;
}

void initMouse(SDL_VideoDevice *_this)
{
    SDL_Mouse       *mouse = SDL_GetMouse();
    SDL_MouseData   *mouse_data;

    mouse_data = (SDL_MouseData *)SDL_calloc(1, sizeof(SDL_MouseData));
    만약 (mouse_data == NULL) {
        반환;
    }
    SDL_zerop(mouse_data);
    mouse->internal = mouse_data;

    mouse->CreateCursor = createCursor;
    mouse->CreateSystemCursor = createSystemCursor;
    mouse->ShowCursor = showCursor;
    mouse->FreeCursor = freeCursor;

    mouse->SetRelativeMouseMode = setRelativeMouseMode;

    SDL_SetDefaultCursor(createCursor(NULL, 0, 0));
}
