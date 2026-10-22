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

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_OPENHARMONY

#ಅನ್ತರ್ಭಾವ "SDL_openharmonymouse.h"

#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"

#ಅನ್ತರ್ಭಾವ "../../core/openharmony/SDL_openharmony.h"

ಸ್ಥಿರ bool OPENHARMONY_ShowCursor(SDL_Cursor *cursor)
{
ಪ್ರತ್ಯಾಗಮ false;
#ಯದಿ 0
    ಯದಿ (!cursor) {
        cursor = OPENHARMONY_CreateEmptyCursor();
    }
    ಯದಿ (cursor) {
        SDL_CursorData *data = cursor->internal;
        ಯದಿ (data->custom_cursor) {
            ಯದಿ (!OPENHARMONY_JNI_SetCustomCursor(data->custom_cursor)) {
                ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
            }
        } ಅನ್ಯಥಾ {
            ಯದಿ (!OPENHARMONY_JNI_SetSystemCursor(data->system_cursor)) {
                ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
            }
        }
        ಪ್ರತ್ಯಾಗಮ true;
    } ಅನ್ಯಥಾ {
        // SDL error set inside OPENHARMONY_CreateEmptyCursor()
        ಪ್ರತ್ಯಾಗಮ false;
    }
#endif
}

ಶೂನ್ಯ OPENHARMONY_InitMouse(ಶೂನ್ಯ)
{
    SDL_Mouse *mouse = SDL_GetMouse();
//!!! FIXME:    mouse->CreateCursor = OPENHARMONY_CreateCursor;
//!!! FIXME:    mouse->CreateSystemCursor = OPENHARMONY_CreateSystemCursor;
    mouse->ShowCursor = OPENHARMONY_ShowCursor;
//!!! FIXME:    mouse->FreeCursor = OPENHARMONY_FreeCursor;
//!!! FIXME:    mouse->SetRelativeMouseMode = OPENHARMONY_SetRelativeMouseMode;

//!!! FIXME:    SDL_SetDefaultCursor(OPENHARMONY_CreateDefaultCursor());
}

ಶೂನ್ಯ OPENHARMONY_QuitMouse(ಶೂನ್ಯ)
{
//!!! FIXME:    OPENHARMONY_DestroyEmptyCursor();
}

#endif

