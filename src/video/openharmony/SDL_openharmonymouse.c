/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>

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

#ifdef SDL_VIDEO_DRIVER_OPENHARMONY

#ଅନ୍ତର୍ଭାଵ "SDL_openharmonymouse.h"

#ଅନ୍ତର୍ଭାଵ "../../events/SDL_mouse_c.h"

#ଅନ୍ତର୍ଭାଵ "../../core/openharmony/SDL_openharmony.h"

ସ୍ଥିର bool OPENHARMONY_ShowCursor(SDL_Cursor *cursor)
{
ଫେରନ୍ତୁ false;
#ଯଦି 0
    ଯଦି (!cursor) {
        cursor = OPENHARMONY_CreateEmptyCursor();
    }
    ଯଦି (cursor) {
        SDL_CursorData *data = cursor->internal;
        ଯଦି (data->custom_cursor) {
            ଯଦି (!OPENHARMONY_JNI_SetCustomCursor(data->custom_cursor)) {
                ଫେରନ୍ତୁ SDL_Unsupported();
            }
        } ଅନ୍ୟଥା {
            ଯଦି (!OPENHARMONY_JNI_SetSystemCursor(data->system_cursor)) {
                ଫେରନ୍ତୁ SDL_Unsupported();
            }
        }
        ଫେରନ୍ତୁ true;
    } ଅନ୍ୟଥା {
        // SDL error set inside OPENHARMONY_CreateEmptyCursor()
        ଫେରନ୍ତୁ false;
    }
#endif
}

ଶୂନ୍ୟ OPENHARMONY_InitMouse(ଶୂନ୍ୟ)
{
    SDL_Mouse *mouse = SDL_GetMouse();
//!!! FIXME:    mouse->CreateCursor = OPENHARMONY_CreateCursor;
//!!! FIXME:    mouse->CreateSystemCursor = OPENHARMONY_CreateSystemCursor;
    mouse->ShowCursor = OPENHARMONY_ShowCursor;
//!!! FIXME:    mouse->FreeCursor = OPENHARMONY_FreeCursor;
//!!! FIXME:    mouse->SetRelativeMouseMode = OPENHARMONY_SetRelativeMouseMode;

//!!! FIXME:    SDL_SetDefaultCursor(OPENHARMONY_CreateDefaultCursor());
}

ଶୂନ୍ୟ OPENHARMONY_QuitMouse(ଶୂନ୍ୟ)
{
//!!! FIXME:    OPENHARMONY_DestroyEmptyCursor();
}

#endif

