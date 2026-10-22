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

#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_OPENHARMONY

#समावेश "SDL_openharmonymouse.h"

#समावेश "../../events/SDL_mouse_c.h"

#समावेश "../../core/openharmony/SDL_openharmony.h"

अटल bool OPENHARMONY_ShowCursor(SDL_Cursor *cursor)
{
वापस false;
#अगर 0
    अगर (!cursor) {
        cursor = OPENHARMONY_CreateEmptyCursor();
    }
    अगर (cursor) {
        SDL_Cursor_तथ्य *तथ्य = cursor->internal;
        अगर (तथ्य->custom_cursor) {
            अगर (!OPENHARMONY_JNI_SetCustomCursor(तथ्य->custom_cursor)) {
                वापस SDL_Unsupported();
            }
        } अन्यथा {
            अगर (!OPENHARMONY_JNI_SetSystemCursor(तथ्य->system_cursor)) {
                वापस SDL_Unsupported();
            }
        }
        वापस true;
    } अन्यथा {
        // SDL error set inside OPENHARMONY_CreateEmptyCursor()
        वापस false;
    }
#पूर्ण_अगर
}

व्योम OPENHARMONY_InitMouse(व्योम)
{
    SDL_Mouse *mouse = SDL_GetMouse();
//!!! FIXME:    mouse->CreateCursor = OPENHARMONY_CreateCursor;
//!!! FIXME:    mouse->CreateSystemCursor = OPENHARMONY_CreateSystemCursor;
    mouse->ShowCursor = OPENHARMONY_ShowCursor;
//!!! FIXME:    mouse->FreeCursor = OPENHARMONY_FreeCursor;
//!!! FIXME:    mouse->SetRelativeMouseMode = OPENHARMONY_SetRelativeMouseMode;

//!!! FIXME:    SDL_SetDefaultCursor(OPENHARMONY_CreateDefaultCursor());
}

व्योम OPENHARMONY_QuitMouse(व्योम)
{
//!!! FIXME:    OPENHARMONY_DestroyEmptyCursor();
}

#पूर्ण_अगर

