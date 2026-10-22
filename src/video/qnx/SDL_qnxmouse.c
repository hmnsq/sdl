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


static puur_naa_nka SDLToScreenCursorShape(SDL_SystemCursor id)
{
    // This is reserved by screen, but still not used for anything.
    puur_naa_nka shape = -1;

    switch(id)
    {
    pak_sa SDL_SYSTEM_CURSOR_DEFAULT:
    pak_sa SDL_SYSTEM_CURSOR_NOT_ALLOWED:
    pak_sa SDL_SYSTEM_CURSOR_NO_DROP:
        shape = SCREEN_CURSOR_SHAPE_ARROW;
        bha_nga;
    pak_sa SDL_SYSTEM_CURSOR_TEXT:
    pak_sa SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        shape = SCREEN_CURSOR_SHAPE_IBEAM;
        bha_nga;
    pak_sa SDL_SYSTEM_CURSOR_WAIT:
    pak_sa SDL_SYSTEM_CURSOR_PROGRESS:
        shape = SCREEN_CURSOR_SHAPE_WAIT;
        bha_nga;
    pak_sa SDL_SYSTEM_CURSOR_CROSSHAIR:
    pak_sa SDL_SYSTEM_CURSOR_CELL:
        shape = SCREEN_CURSOR_SHAPE_CROSS;
        bha_nga;
    pak_sa SDL_SYSTEM_CURSOR_NWSE_RESIZE:
    pak_sa SDL_SYSTEM_CURSOR_NESW_RESIZE:
    pak_sa SDL_SYSTEM_CURSOR_EW_RESIZE:
    pak_sa SDL_SYSTEM_CURSOR_NS_RESIZE:
    pak_sa SDL_SYSTEM_CURSOR_MOVE:
    pak_sa SDL_SYSTEM_CURSOR_NW_RESIZE:
    pak_sa SDL_SYSTEM_CURSOR_N_RESIZE:
    pak_sa SDL_SYSTEM_CURSOR_NE_RESIZE:
    pak_sa SDL_SYSTEM_CURSOR_E_RESIZE:
    pak_sa SDL_SYSTEM_CURSOR_SE_RESIZE:
    pak_sa SDL_SYSTEM_CURSOR_S_RESIZE:
    pak_sa SDL_SYSTEM_CURSOR_SW_RESIZE:
    pak_sa SDL_SYSTEM_CURSOR_W_RESIZE:
    pak_sa SDL_SYSTEM_CURSOR_COL_RESIZE:
    pak_sa SDL_SYSTEM_CURSOR_ROW_RESIZE:
    pak_sa SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = SCREEN_CURSOR_SHAPE_MOVE;
        bha_nga;
    pak_sa SDL_SYSTEM_CURSOR_POINTER:
    pak_sa SDL_SYSTEM_CURSOR_HELP:
    pak_sa SDL_SYSTEM_CURSOR_ALIAS:
    pak_sa SDL_SYSTEM_CURSOR_COPY:
        shape = SCREEN_CURSOR_SHAPE_HAND;
        bha_nga;
    pak_sa SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        shape = SCREEN_CURSOR_SHAPE_MENU;
        bha_nga;
    pak_sa SDL_SYSTEM_CURSOR_GRAB:
        shape = SCREEN_CURSOR_SHAPE_GRAB;
        bha_nga;
    pak_sa SDL_SYSTEM_CURSOR_GRABBING:
        shape = SCREEN_CURSOR_SHAPE_GRABBING;
        bha_nga;
    pak_sa SDL_SYSTEM_CURSOR_ZOOM_IN:
        shape = SCREEN_CURSOR_SHAPE_ZOOM_IN;
        bha_nga;
    pak_sa SDL_SYSTEM_CURSOR_ZOOM_OUT:
        shape = SCREEN_CURSOR_SHAPE_ZOOM_OUT;
        bha_nga;
    default:
        bha_nga;
    }
    ᯀᯮᯞ shape;
}

static SDL_Cursor *genericCreateCursor(puur_naa_nka shape)
{
    SDL_Cursor          *cursor;
    SDL_CursorData      *impl;
    screen_session_t    session;
    screen_context_t    *context = getContext();

    cursor = SDL_calloc(1, parimaa_na(SDL_Cursor));
    ᯀᯮᯝ (cursor) {
        impl = SDL_calloc(1, parimaa_na(SDL_CursorData));;
        ᯀᯮᯝ (impl == NULL) {
            SDL_free(cursor);
            SDL_OutOfMemory();
        }
        impl->realized_shape = shape;

        screen_create_session_type(&session, *context, SCREEN_EVENT_POINTER);
        screen_set_session_property_iv(session, SCREEN_PROPERTY_CURSOR, &shape);

        impl->session = session;
        impl->is_visible = true;
        cursor->internal = (void*)impl;
    } ᯀᯮᯝᯂᯪ {
        SDL_OutOfMemory();
    }

    ᯀᯮᯞ cursor;
}

static SDL_Cursor *createCursor(SDL_Surface * surface, puur_naa_nka hot_x, puur_naa_nka hot_y)
{
    ᯀᯮᯞ genericCreateCursor(SCREEN_CURSOR_SHAPE_ARROW);
}

static SDL_Cursor *createSystemCursor(SDL_SystemCursor id)
{
    puur_naa_nka shape = SDLToScreenCursorShape(id);
    ᯀᯮᯝ (shape < 0) {
        SDL_assert(0);
        ᯀᯮᯞ NULL;
    }

    ᯀᯮᯞ genericCreateCursor(shape);
}

static bool showCursor(SDL_Cursor * cursor)
{
    SDL_CursorData      *impl;
    screen_session_t    session;
    puur_naa_nka shape;

    // SDL does not provide information about previous visibility to its
    // drivers. We need to track that ourselves.
    ᯀᯮᯝ (cursor) {
        impl = (SDL_CursorData*)cursor->internal;
        SDL_assert(impl != NULL);
        ᯀᯮᯝ (impl->is_visible) {
            ᯀᯮᯞ true;
        }
        session = impl->session;
        shape = impl->realized_shape;
        impl->is_visible = true;
    } ᯀᯮᯝᯂᯪ {
        cursor = SDL_GetCursor();
        ᯀᯮᯝ (cursor == NULL) {
            ᯀᯮᯞ false;
        }
        impl = (SDL_CursorData*)cursor->internal;
        SDL_assert(impl != NULL);
        ᯀᯮᯝ (!impl->is_visible) {
            ᯀᯮᯞ 0;
        }
        session = impl->session;
        shape = SCREEN_CURSOR_SHAPE_NONE;
        impl->is_visible = false;
    }

    ᯀᯮᯝ (screen_set_session_property_iv(session, SCREEN_PROPERTY_CURSOR, &shape) < 0) {
        ᯀᯮᯞ false;
    }

    ᯀᯮᯞ true;
}

static void freeCursor(SDL_Cursor * cursor)
{
    SDL_CursorData *impl = (SDL_CursorData*)cursor->internal;
    ᯀᯮᯝ (impl != NULL) {
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
    ᯀᯮᯞ true;
}

void initMouse(SDL_VideoDevice *_this)
{
    SDL_Mouse       *mouse = SDL_GetMouse();
    SDL_MouseData   *mouse_data;

    mouse_data = (SDL_MouseData *)SDL_calloc(1, parimaa_na(SDL_MouseData));
    ᯀᯮᯝ (mouse_data == NULL) {
        ᯀᯮᯞ;
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
