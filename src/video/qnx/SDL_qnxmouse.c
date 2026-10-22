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

#அந்தர்பாவ "SDL_internal.h"
#அந்தர்பாவ "../SDL_sysvideo.h"
#அந்தர்பாவ "SDL_qnx.h"
#அந்தர்பாவ "../../events/SDL_mouse_c.h"

#அந்தர்பாவ <errno.h>


நிலையான முழு SDLToScreenCursorShape(SDL_SystemCursor id)
{
    // This is reserved by screen, but still not used for anything.
    முழு shape = -1;

    தேர்வு(id)
    {
    நிலை SDL_SYSTEM_CURSOR_DEFAULT:
    நிலை SDL_SYSTEM_CURSOR_NOT_ALLOWED:
    நிலை SDL_SYSTEM_CURSOR_NO_DROP:
        shape = SCREEN_CURSOR_SHAPE_ARROW;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_TEXT:
    நிலை SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        shape = SCREEN_CURSOR_SHAPE_IBEAM;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_WAIT:
    நிலை SDL_SYSTEM_CURSOR_PROGRESS:
        shape = SCREEN_CURSOR_SHAPE_WAIT;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_CROSSHAIR:
    நிலை SDL_SYSTEM_CURSOR_CELL:
        shape = SCREEN_CURSOR_SHAPE_CROSS;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_NWSE_RESIZE:
    நிலை SDL_SYSTEM_CURSOR_NESW_RESIZE:
    நிலை SDL_SYSTEM_CURSOR_EW_RESIZE:
    நிலை SDL_SYSTEM_CURSOR_NS_RESIZE:
    நிலை SDL_SYSTEM_CURSOR_MOVE:
    நிலை SDL_SYSTEM_CURSOR_NW_RESIZE:
    நிலை SDL_SYSTEM_CURSOR_N_RESIZE:
    நிலை SDL_SYSTEM_CURSOR_NE_RESIZE:
    நிலை SDL_SYSTEM_CURSOR_E_RESIZE:
    நிலை SDL_SYSTEM_CURSOR_SE_RESIZE:
    நிலை SDL_SYSTEM_CURSOR_S_RESIZE:
    நிலை SDL_SYSTEM_CURSOR_SW_RESIZE:
    நிலை SDL_SYSTEM_CURSOR_W_RESIZE:
    நிலை SDL_SYSTEM_CURSOR_COL_RESIZE:
    நிலை SDL_SYSTEM_CURSOR_ROW_RESIZE:
    நிலை SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = SCREEN_CURSOR_SHAPE_MOVE;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_POINTER:
    நிலை SDL_SYSTEM_CURSOR_HELP:
    நிலை SDL_SYSTEM_CURSOR_ALIAS:
    நிலை SDL_SYSTEM_CURSOR_COPY:
        shape = SCREEN_CURSOR_SHAPE_HAND;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        shape = SCREEN_CURSOR_SHAPE_MENU;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_GRAB:
        shape = SCREEN_CURSOR_SHAPE_GRAB;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_GRABBING:
        shape = SCREEN_CURSOR_SHAPE_GRABBING;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_ZOOM_IN:
        shape = SCREEN_CURSOR_SHAPE_ZOOM_IN;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_ZOOM_OUT:
        shape = SCREEN_CURSOR_SHAPE_ZOOM_OUT;
        நிறுத்து;
    இயல்பு:
        நிறுத்து;
    }
    திரும்பு shape;
}

நிலையான SDL_Cursor *genericCreateCursor(முழு shape)
{
    SDL_Cursor          *cursor;
    SDL_CursorData      *impl;
    screen_session_t    session;
    screen_context_t    *context = getContext();

    cursor = SDL_calloc(1, அளவு(SDL_Cursor));
    எனில் (cursor) {
        impl = SDL_calloc(1, அளவு(SDL_CursorData));;
        எனில் (impl == வெற்று) {
            SDL_free(cursor);
            SDL_OutOfMemory();
        }
        impl->realized_shape = shape;

        screen_create_session_type(&session, *context, SCREEN_EVENT_POINTER);
        screen_set_session_property_iv(session, SCREEN_PROPERTY_CURSOR, &shape);

        impl->session = session;
        impl->is_visible = true;
        cursor->internal = (வெறுமை*)impl;
    } இல்லையெனில் {
        SDL_OutOfMemory();
    }

    திரும்பு cursor;
}

நிலையான SDL_Cursor *createCursor(SDL_Surface * surface, முழு hot_x, முழு hot_y)
{
    திரும்பு genericCreateCursor(SCREEN_CURSOR_SHAPE_ARROW);
}

நிலையான SDL_Cursor *createSystemCursor(SDL_SystemCursor id)
{
    முழு shape = SDLToScreenCursorShape(id);
    எனில் (shape < 0) {
        SDL_assert(0);
        திரும்பு வெற்று;
    }

    திரும்பு genericCreateCursor(shape);
}

நிலையான bool showCursor(SDL_Cursor * cursor)
{
    SDL_CursorData      *impl;
    screen_session_t    session;
    முழு shape;

    // SDL does not provide information about previous visibility to its
    // drivers. We need to track that ourselves.
    எனில் (cursor) {
        impl = (SDL_CursorData*)cursor->internal;
        SDL_assert(impl != வெற்று);
        எனில் (impl->is_visible) {
            திரும்பு true;
        }
        session = impl->session;
        shape = impl->realized_shape;
        impl->is_visible = true;
    } இல்லையெனில் {
        cursor = SDL_GetCursor();
        எனில் (cursor == வெற்று) {
            திரும்பு false;
        }
        impl = (SDL_CursorData*)cursor->internal;
        SDL_assert(impl != வெற்று);
        எனில் (!impl->is_visible) {
            திரும்பு 0;
        }
        session = impl->session;
        shape = SCREEN_CURSOR_SHAPE_NONE;
        impl->is_visible = false;
    }

    எனில் (screen_set_session_property_iv(session, SCREEN_PROPERTY_CURSOR, &shape) < 0) {
        திரும்பு false;
    }

    திரும்பு true;
}

நிலையான வெறுமை freeCursor(SDL_Cursor * cursor)
{
    SDL_CursorData *impl = (SDL_CursorData*)cursor->internal;
    எனில் (impl != வெற்று) {
        screen_destroy_session(impl->session);
        SDL_free(impl);
    }
    SDL_free(cursor);
}

நிலையான bool setRelativeMouseMode(bool enabled)
{
    // We're tracking rel-position explicitly, but this is still needed so
    // SDL_SetRelativeMouseMode() & friends aren't a no-op.
    //
    // TODO: It may be possible to achieve this using SCREEN_PROPERTY_DISPLACEMENT instead.
    திரும்பு true;
}

வெறுமை initMouse(SDL_VideoDevice *_this)
{
    SDL_Mouse       *mouse = SDL_GetMouse();
    SDL_MouseData   *mouse_data;

    mouse_data = (SDL_MouseData *)SDL_calloc(1, அளவு(SDL_MouseData));
    எனில் (mouse_data == வெற்று) {
        திரும்பு;
    }
    SDL_zerop(mouse_data);
    mouse->internal = mouse_data;

    mouse->CreateCursor = createCursor;
    mouse->CreateSystemCursor = createSystemCursor;
    mouse->ShowCursor = showCursor;
    mouse->FreeCursor = freeCursor;

    mouse->SetRelativeMouseMode = setRelativeMouseMode;

    SDL_SetDefaultCursor(createCursor(வெற்று, 0, 0));
}
