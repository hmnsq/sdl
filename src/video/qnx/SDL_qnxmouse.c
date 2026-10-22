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

#অন্তর্ভাব "SDL_internal.h"
#অন্তর্ভাব "../SDL_sysvideo.h"
#অন্তর্ভাব "SDL_qnx.h"
#অন্তর্ভাব "../../events/SDL_mouse_c.h"

#অন্তর্ভাব <errno.h>


স্থির পূর্ণসংখ্যা SDLToScreenCursorShape(SDL_SystemCursor id)
{
    // This is reserved by screen, but still not used for anything.
    পূর্ণসংখ্যা shape = -1;

    নির্বাচন(id)
    {
    ক্ষেত্র SDL_SYSTEM_CURSOR_DEFAULT:
    ক্ষেত্র SDL_SYSTEM_CURSOR_NOT_ALLOWED:
    ক্ষেত্র SDL_SYSTEM_CURSOR_NO_DROP:
        shape = SCREEN_CURSOR_SHAPE_ARROW;
        বিরতি;
    ক্ষেত্র SDL_SYSTEM_CURSOR_TEXT:
    ক্ষেত্র SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        shape = SCREEN_CURSOR_SHAPE_IBEAM;
        বিরতি;
    ক্ষেত্র SDL_SYSTEM_CURSOR_WAIT:
    ক্ষেত্র SDL_SYSTEM_CURSOR_PROGRESS:
        shape = SCREEN_CURSOR_SHAPE_WAIT;
        বিরতি;
    ক্ষেত্র SDL_SYSTEM_CURSOR_CROSSHAIR:
    ক্ষেত্র SDL_SYSTEM_CURSOR_CELL:
        shape = SCREEN_CURSOR_SHAPE_CROSS;
        বিরতি;
    ক্ষেত্র SDL_SYSTEM_CURSOR_NWSE_RESIZE:
    ক্ষেত্র SDL_SYSTEM_CURSOR_NESW_RESIZE:
    ক্ষেত্র SDL_SYSTEM_CURSOR_EW_RESIZE:
    ক্ষেত্র SDL_SYSTEM_CURSOR_NS_RESIZE:
    ক্ষেত্র SDL_SYSTEM_CURSOR_MOVE:
    ক্ষেত্র SDL_SYSTEM_CURSOR_NW_RESIZE:
    ক্ষেত্র SDL_SYSTEM_CURSOR_N_RESIZE:
    ক্ষেত্র SDL_SYSTEM_CURSOR_NE_RESIZE:
    ক্ষেত্র SDL_SYSTEM_CURSOR_E_RESIZE:
    ক্ষেত্র SDL_SYSTEM_CURSOR_SE_RESIZE:
    ক্ষেত্র SDL_SYSTEM_CURSOR_S_RESIZE:
    ক্ষেত্র SDL_SYSTEM_CURSOR_SW_RESIZE:
    ক্ষেত্র SDL_SYSTEM_CURSOR_W_RESIZE:
    ক্ষেত্র SDL_SYSTEM_CURSOR_COL_RESIZE:
    ক্ষেত্র SDL_SYSTEM_CURSOR_ROW_RESIZE:
    ক্ষেত্র SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = SCREEN_CURSOR_SHAPE_MOVE;
        বিরতি;
    ক্ষেত্র SDL_SYSTEM_CURSOR_POINTER:
    ক্ষেত্র SDL_SYSTEM_CURSOR_HELP:
    ক্ষেত্র SDL_SYSTEM_CURSOR_ALIAS:
    ক্ষেত্র SDL_SYSTEM_CURSOR_COPY:
        shape = SCREEN_CURSOR_SHAPE_HAND;
        বিরতি;
    ক্ষেত্র SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        shape = SCREEN_CURSOR_SHAPE_MENU;
        বিরতি;
    ক্ষেত্র SDL_SYSTEM_CURSOR_GRAB:
        shape = SCREEN_CURSOR_SHAPE_GRAB;
        বিরতি;
    ক্ষেত্র SDL_SYSTEM_CURSOR_GRABBING:
        shape = SCREEN_CURSOR_SHAPE_GRABBING;
        বিরতি;
    ক্ষেত্র SDL_SYSTEM_CURSOR_ZOOM_IN:
        shape = SCREEN_CURSOR_SHAPE_ZOOM_IN;
        বিরতি;
    ক্ষেত্র SDL_SYSTEM_CURSOR_ZOOM_OUT:
        shape = SCREEN_CURSOR_SHAPE_ZOOM_OUT;
        বিরতি;
    পূর্বনির্ধারিত:
        বিরতি;
    }
    ফেরত shape;
}

স্থির SDL_Cursor *genericCreateCursor(পূর্ণসংখ্যা shape)
{
    SDL_Cursor          *cursor;
    SDL_Cursor_তথ্য      *impl;
    screen_session_t    session;
    screen_context_t    *context = getContext();

    cursor = SDL_calloc(1, আকার(SDL_Cursor));
    যদি (cursor) {
        impl = SDL_calloc(1, আকার(SDL_Cursor_তথ্য));;
        যদি (impl == ফাঁকা) {
            SDL_free(cursor);
            SDL_OutOfMemory();
        }
        impl->realized_shape = shape;

        screen_create_session_type(&session, *context, SCREEN_EVENT_POINTER);
        screen_set_session_property_iv(session, SCREEN_PROPERTY_CURSOR, &shape);

        impl->session = session;
        impl->is_visible = true;
        cursor->internal = (শূন্য*)impl;
    } অন্যথা {
        SDL_OutOfMemory();
    }

    ফেরত cursor;
}

স্থির SDL_Cursor *createCursor(SDL_Surface * surface, পূর্ণসংখ্যা hot_x, পূর্ণসংখ্যা hot_y)
{
    ফেরত genericCreateCursor(SCREEN_CURSOR_SHAPE_ARROW);
}

স্থির SDL_Cursor *createSystemCursor(SDL_SystemCursor id)
{
    পূর্ণসংখ্যা shape = SDLToScreenCursorShape(id);
    যদি (shape < 0) {
        SDL_assert(0);
        ফেরত ফাঁকা;
    }

    ফেরত genericCreateCursor(shape);
}

স্থির bool showCursor(SDL_Cursor * cursor)
{
    SDL_Cursor_তথ্য      *impl;
    screen_session_t    session;
    পূর্ণসংখ্যা shape;

    // SDL does not provide information about previous visibility to its
    // drivers. We need to track that ourselves.
    যদি (cursor) {
        impl = (SDL_Cursor_তথ্য*)cursor->internal;
        SDL_assert(impl != ফাঁকা);
        যদি (impl->is_visible) {
            ফেরত true;
        }
        session = impl->session;
        shape = impl->realized_shape;
        impl->is_visible = true;
    } অন্যথা {
        cursor = SDL_GetCursor();
        যদি (cursor == ফাঁকা) {
            ফেরত false;
        }
        impl = (SDL_Cursor_তথ্য*)cursor->internal;
        SDL_assert(impl != ফাঁকা);
        যদি (!impl->is_visible) {
            ফেরত 0;
        }
        session = impl->session;
        shape = SCREEN_CURSOR_SHAPE_NONE;
        impl->is_visible = false;
    }

    যদি (screen_set_session_property_iv(session, SCREEN_PROPERTY_CURSOR, &shape) < 0) {
        ফেরত false;
    }

    ফেরত true;
}

স্থির শূন্য freeCursor(SDL_Cursor * cursor)
{
    SDL_Cursor_তথ্য *impl = (SDL_Cursor_তথ্য*)cursor->internal;
    যদি (impl != ফাঁকা) {
        screen_destroy_session(impl->session);
        SDL_free(impl);
    }
    SDL_free(cursor);
}

স্থির bool setRelativeMouseMode(bool enabled)
{
    // We're tracking rel-position explicitly, but this is still needed so
    // SDL_SetRelativeMouseMode() & friends aren't a no-op.
    //
    // TODO: It may be possible to achieve this using SCREEN_PROPERTY_DISPLACEMENT instead.
    ফেরত true;
}

শূন্য initMouse(SDL_VideoDevice *_this)
{
    SDL_Mouse       *mouse = SDL_GetMouse();
    SDL_Mouse_তথ্য   *mouse_তথ্য;

    mouse_তথ্য = (SDL_Mouse_তথ্য *)SDL_calloc(1, আকার(SDL_Mouse_তথ্য));
    যদি (mouse_তথ্য == ফাঁকা) {
        ফেরত;
    }
    SDL_zerop(mouse_তথ্য);
    mouse->internal = mouse_তথ্য;

    mouse->CreateCursor = createCursor;
    mouse->CreateSystemCursor = createSystemCursor;
    mouse->ShowCursor = showCursor;
    mouse->FreeCursor = freeCursor;

    mouse->SetRelativeMouseMode = setRelativeMouseMode;

    SDL_SetDefaultCursor(createCursor(ফাঁকা, 0, 0));
}
