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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_OPENHARMONY

#ಅನ್ತರ್ಭಾವ "SDL_openharmonymouse.h"

#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"

#ಅನ್ತರ್ಭಾವ "../../core/openharmony/SDL_openharmony.h"

ಸ್ಥಿರ bool OPENHARMONY_ShowCursor(SDL_Cursor *cursor)
{
ಹಿಂತಿರುಗಿ false;
#ಆದರೆ 0
    ಆದರೆ (!cursor) {
        cursor = OPENHARMONY_Create_ಖಾಲಿಗಳು_Cursor();
    }
    ಆದರೆ (cursor) {
        SDL_Cursor_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = cursor->ಆಂತರಿಕ;
        ಆದರೆ (ದತ್ತಾಂಶ->custom_cursor) {
            ಆದರೆ (!OPENHARMONY_JNI_ಗಣ_Custom_Cursor(ದತ್ತಾಂಶ->custom_cursor)) {
                ಹಿಂತಿರುಗಿ SDL_Unsupported();
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಆದರೆ (!OPENHARMONY_JNI_ಗಣ_System_Cursor(ದತ್ತಾಂಶ->system_cursor)) {
                ಹಿಂತಿರುಗಿ SDL_Unsupported();
            }
        }
        ಹಿಂತಿರುಗಿ true;
    } ಇಲ್ಲದಿದ್ದರೆ {
        // SDL error set inside OPENHARMONY_CreateEmptyCursor()
        ಹಿಂತಿರುಗಿ false;
    }
#ಆದರೆ_ಅಂತ್ಯ
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

#ಆದರೆ_ಅಂತ್ಯ

