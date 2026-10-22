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

#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"
#ଅନ୍ତର୍ଭାଵ "../SDL_sysvideo.h"
#ଅନ୍ତର୍ଭାଵ "SDL_qnx.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_mouse_c.h"

#ଅନ୍ତର୍ଭାଵ <errno.h>


ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା SDLToScreenCursorShape(SDL_SystemCursor id)
{
    // This is reserved by screen, but still not used for anything.
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା shape = -1;

    ବାଛ(id)
    {
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_DEFAULT:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_NOT_ALLOWED:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_NO_DROP:
        shape = SCREEN_CURSOR_SHAPE_ARROW;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_TEXT:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        shape = SCREEN_CURSOR_SHAPE_IBEAM;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_WAIT:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_PROGRESS:
        shape = SCREEN_CURSOR_SHAPE_WAIT;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_CROSSHAIR:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_CELL:
        shape = SCREEN_CURSOR_SHAPE_CROSS;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_NWSE_RESIZE:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_NESW_RESIZE:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_EW_RESIZE:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_NS_RESIZE:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_MOVE:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_NW_RESIZE:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_N_RESIZE:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_NE_RESIZE:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_E_RESIZE:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_SE_RESIZE:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_S_RESIZE:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_SW_RESIZE:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_W_RESIZE:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_COL_RESIZE:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_ROW_RESIZE:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = SCREEN_CURSOR_SHAPE_MOVE;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_POINTER:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_HELP:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_ALIAS:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_COPY:
        shape = SCREEN_CURSOR_SHAPE_HAND;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        shape = SCREEN_CURSOR_SHAPE_MENU;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_GRAB:
        shape = SCREEN_CURSOR_SHAPE_GRAB;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_GRABBING:
        shape = SCREEN_CURSOR_SHAPE_GRABBING;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_ZOOM_IN:
        shape = SCREEN_CURSOR_SHAPE_ZOOM_IN;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_ZOOM_OUT:
        shape = SCREEN_CURSOR_SHAPE_ZOOM_OUT;
        ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଭାଙ୍ଗ;
    }
    ଫେରନ୍ତୁ shape;
}

ସ୍ଥିର SDL_Cursor *genericCreateCursor(ପୂର୍ଣ୍ଣସଂଖ୍ୟା shape)
{
    SDL_Cursor          *cursor;
    SDL_CursorData      *impl;
    screen_session_t    session;
    screen_context_t    *context = getContext();

    cursor = SDL_calloc(1, ଆକାର(SDL_Cursor));
    ଯଦି (cursor) {
        impl = SDL_calloc(1, ଆକାର(SDL_CursorData));;
        ଯଦି (impl == ଖାଲି) {
            SDL_free(cursor);
            SDL_OutOfMemory();
        }
        impl->realized_shape = shape;

        screen_create_session_type(&session, *context, SCREEN_EVENT_POINTER);
        screen_set_session_property_iv(session, SCREEN_PROPERTY_CURSOR, &shape);

        impl->session = session;
        impl->is_visible = true;
        cursor->internal = (ଶୂନ୍ୟ*)impl;
    } ଅନ୍ୟଥା {
        SDL_OutOfMemory();
    }

    ଫେରନ୍ତୁ cursor;
}

ସ୍ଥିର SDL_Cursor *createCursor(SDL_Surface * surface, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_y)
{
    ଫେରନ୍ତୁ genericCreateCursor(SCREEN_CURSOR_SHAPE_ARROW);
}

ସ୍ଥିର SDL_Cursor *createSystemCursor(SDL_SystemCursor id)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା shape = SDLToScreenCursorShape(id);
    ଯଦି (shape < 0) {
        SDL_assert(0);
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ଫେରନ୍ତୁ genericCreateCursor(shape);
}

ସ୍ଥିର bool showCursor(SDL_Cursor * cursor)
{
    SDL_CursorData      *impl;
    screen_session_t    session;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା shape;

    // SDL does not provide information about previous visibility to its
    // drivers. We need to track that ourselves.
    ଯଦି (cursor) {
        impl = (SDL_CursorData*)cursor->internal;
        SDL_assert(impl != ଖାଲି);
        ଯଦି (impl->is_visible) {
            ଫେରନ୍ତୁ true;
        }
        session = impl->session;
        shape = impl->realized_shape;
        impl->is_visible = true;
    } ଅନ୍ୟଥା {
        cursor = SDL_GetCursor();
        ଯଦି (cursor == ଖାଲି) {
            ଫେରନ୍ତୁ false;
        }
        impl = (SDL_CursorData*)cursor->internal;
        SDL_assert(impl != ଖାଲି);
        ଯଦି (!impl->is_visible) {
            ଫେରନ୍ତୁ 0;
        }
        session = impl->session;
        shape = SCREEN_CURSOR_SHAPE_NONE;
        impl->is_visible = false;
    }

    ଯଦି (screen_set_session_property_iv(session, SCREEN_PROPERTY_CURSOR, &shape) < 0) {
        ଫେରନ୍ତୁ false;
    }

    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର ଶୂନ୍ୟ freeCursor(SDL_Cursor * cursor)
{
    SDL_CursorData *impl = (SDL_CursorData*)cursor->internal;
    ଯଦି (impl != ଖାଲି) {
        screen_destroy_session(impl->session);
        SDL_free(impl);
    }
    SDL_free(cursor);
}

ସ୍ଥିର bool setRelativeMouseMode(bool enabled)
{
    // We're tracking rel-position explicitly, but this is still needed so
    // SDL_SetRelativeMouseMode() & friends aren't a no-op.
    //
    // TODO: It may be possible to achieve this using SCREEN_PROPERTY_DISPLACEMENT instead.
    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ initMouse(SDL_VideoDevice *_this)
{
    SDL_Mouse       *mouse = SDL_GetMouse();
    SDL_MouseData   *mouse_data;

    mouse_data = (SDL_MouseData *)SDL_calloc(1, ଆକାର(SDL_MouseData));
    ଯଦି (mouse_data == ଖାଲି) {
        ଫେରନ୍ତୁ;
    }
    SDL_zerop(mouse_data);
    mouse->internal = mouse_data;

    mouse->CreateCursor = createCursor;
    mouse->CreateSystemCursor = createSystemCursor;
    mouse->ShowCursor = showCursor;
    mouse->FreeCursor = freeCursor;

    mouse->SetRelativeMouseMode = setRelativeMouseMode;

    SDL_SetDefaultCursor(createCursor(ଖାଲି, 0, 0));
}
