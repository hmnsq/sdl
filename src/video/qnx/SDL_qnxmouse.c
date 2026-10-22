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

#అన్తర్భావ "SDL_internal.h"
#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "SDL_qnx.h"
#అన్తర్భావ "../../events/SDL_mouse_c.h"

#అన్తర్భావ <errno.h>


స్థిర పూర్ణాంకం SDLToScreenCursorShape(SDL_SystemCursor id)
{
    // This is reserved by screen, but still not used for anything.
    పూర్ణాంకం shape = -1;

    ఎంపిక(id)
    {
    స్థితి SDL_SYSTEM_CURSOR_DEFAULT:
    స్థితి SDL_SYSTEM_CURSOR_NOT_ALLOWED:
    స్థితి SDL_SYSTEM_CURSOR_NO_DROP:
        shape = SCREEN_CURSOR_SHAPE_ARROW;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_పాఠ్యం:
    స్థితి SDL_SYSTEM_CURSOR_VERTICAL_పాఠ్యం:
        shape = SCREEN_CURSOR_SHAPE_IBEAM;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_WAIT:
    స్థితి SDL_SYSTEM_CURSOR_పురోగతి:
        shape = SCREEN_CURSOR_SHAPE_WAIT;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_CROSSHAIR:
    స్థితి SDL_SYSTEM_CURSOR_CELL:
        shape = SCREEN_CURSOR_SHAPE_CROSS;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_NWSE_RESIZE:
    స్థితి SDL_SYSTEM_CURSOR_NESW_RESIZE:
    స్థితి SDL_SYSTEM_CURSOR_EW_RESIZE:
    స్థితి SDL_SYSTEM_CURSOR_NS_RESIZE:
    స్థితి SDL_SYSTEM_CURSOR_MOVE:
    స్థితి SDL_SYSTEM_CURSOR_NW_RESIZE:
    స్థితి SDL_SYSTEM_CURSOR_N_RESIZE:
    స్థితి SDL_SYSTEM_CURSOR_NE_RESIZE:
    స్థితి SDL_SYSTEM_CURSOR_E_RESIZE:
    స్థితి SDL_SYSTEM_CURSOR_SE_RESIZE:
    స్థితి SDL_SYSTEM_CURSOR_S_RESIZE:
    స్థితి SDL_SYSTEM_CURSOR_SW_RESIZE:
    స్థితి SDL_SYSTEM_CURSOR_W_RESIZE:
    స్థితి SDL_SYSTEM_CURSOR_నిలువు_RESIZE:
    స్థితి SDL_SYSTEM_CURSOR_అడ్డువరుస_RESIZE:
    స్థితి SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = SCREEN_CURSOR_SHAPE_MOVE;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_సూచిక:
    స్థితి SDL_SYSTEM_CURSOR_HELP:
    స్థితి SDL_SYSTEM_CURSOR_ALIAS:
    స్థితి SDL_SYSTEM_CURSOR_COPY:
        shape = SCREEN_CURSOR_SHAPE_HAND;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        shape = SCREEN_CURSOR_SHAPE_MENU;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_GRAB:
        shape = SCREEN_CURSOR_SHAPE_GRAB;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_GRABBING:
        shape = SCREEN_CURSOR_SHAPE_GRABBING;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_ZOOM_లోపల:
        shape = SCREEN_CURSOR_SHAPE_ZOOM_లోపల;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_ZOOM_బహిర్గతం:
        shape = SCREEN_CURSOR_SHAPE_ZOOM_బహిర్గతం;
        ఆపు;
    అప్రమేయ:
        ఆపు;
    }
    తిరిగి shape;
}

స్థిర SDL_Cursor *genericCreateCursor(పూర్ణాంకం shape)
{
    SDL_Cursor          *cursor;
    SDL_Cursor_దత్తాంశం      *impl;
    screen_session_t    session;
    screen_context_t    *context = getContext();

    cursor = SDL_calloc(1, పరిమాణం(SDL_Cursor));
    ఒకవేళ (cursor) {
        impl = SDL_calloc(1, పరిమాణం(SDL_Cursor_దత్తాంశం));;
        ఒకవేళ (impl == ఖాళీ) {
            SDL_free(cursor);
            SDL_బహిర్గతం_యొక్క_జ్ఞాపకం();
        }
        impl->realized_shape = shape;

        screen_create_session_type(&session, *context, SCREEN_EVENT_సూచిక);
        screen_సమితి_session_property_iv(session, SCREEN_PROPERTY_CURSOR, &shape);

        impl->session = session;
        impl->is_visible = true;
        cursor->అంతర్గత = (శూన్య*)impl;
    } లేకపోతే {
        SDL_బహిర్గతం_యొక్క_జ్ఞాపకం();
    }

    తిరిగి cursor;
}

స్థిర SDL_Cursor *createCursor(SDL_Surface * surface, పూర్ణాంకం hot_x, పూర్ణాంకం hot_y)
{
    తిరిగి genericCreateCursor(SCREEN_CURSOR_SHAPE_ARROW);
}

స్థిర SDL_Cursor *createSystemCursor(SDL_SystemCursor id)
{
    పూర్ణాంకం shape = SDLToScreenCursorShape(id);
    ఒకవేళ (shape < 0) {
        SDL_assert(0);
        తిరిగి ఖాళీ;
    }

    తిరిగి genericCreateCursor(shape);
}

స్థిర bool showCursor(SDL_Cursor * cursor)
{
    SDL_Cursor_దత్తాంశం      *impl;
    screen_session_t    session;
    పూర్ణాంకం shape;

    // SDL does not provide information about previous visibility to its
    // drivers. We need to track that ourselves.
    ఒకవేళ (cursor) {
        impl = (SDL_Cursor_దత్తాంశం*)cursor->అంతర్గత;
        SDL_assert(impl != ఖాళీ);
        ఒకవేళ (impl->is_visible) {
            తిరిగి true;
        }
        session = impl->session;
        shape = impl->realized_shape;
        impl->is_visible = true;
    } లేకపోతే {
        cursor = SDL_GetCursor();
        ఒకవేళ (cursor == ఖాళీ) {
            తిరిగి false;
        }
        impl = (SDL_Cursor_దత్తాంశం*)cursor->అంతర్గత;
        SDL_assert(impl != ఖాళీ);
        ఒకవేళ (!impl->is_visible) {
            తిరిగి 0;
        }
        session = impl->session;
        shape = SCREEN_CURSOR_SHAPE_NONE;
        impl->is_visible = false;
    }

    ఒకవేళ (screen_సమితి_session_property_iv(session, SCREEN_PROPERTY_CURSOR, &shape) < 0) {
        తిరిగి false;
    }

    తిరిగి true;
}

స్థిర శూన్య freeCursor(SDL_Cursor * cursor)
{
    SDL_Cursor_దత్తాంశం *impl = (SDL_Cursor_దత్తాంశం*)cursor->అంతర్గత;
    ఒకవేళ (impl != ఖాళీ) {
        screen_destroy_session(impl->session);
        SDL_free(impl);
    }
    SDL_free(cursor);
}

స్థిర bool సమితి_Relative_Mouse_బహుళకం_2(bool enabled)
{
    // We're tracking rel-position explicitly, but this is still needed so
    // SDL_SetRelativeMouseMode() & friends aren't a no-op.
    //
    // TODO: It may be possible to achieve this using SCREEN_PROPERTY_DISPLACEMENT instead.
    తిరిగి true;
}

శూన్య initMouse(SDL_VideoDevice *_this)
{
    SDL_Mouse       *mouse = SDL_GetMouse();
    SDL_Mouse_దత్తాంశం   *mouse_దత్తాంశం;

    mouse_దత్తాంశం = (SDL_Mouse_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_Mouse_దత్తాంశం));
    ఒకవేళ (mouse_దత్తాంశం == ఖాళీ) {
        తిరిగి;
    }
    SDL_zerop(mouse_దత్తాంశం);
    mouse->అంతర్గత = mouse_దత్తాంశం;

    mouse->CreateCursor = createCursor;
    mouse->CreateSystemCursor = createSystemCursor;
    mouse->ShowCursor = showCursor;
    mouse->FreeCursor = freeCursor;

    mouse->సమితి_Relative_Mouse_బహుళకం = సమితి_Relative_Mouse_బహుళకం_2;

    SDL_సమితి_Default_Cursor(createCursor(ఖాళీ, 0, 0));
}
