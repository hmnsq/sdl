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

#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_OPENHARMONY

#అన్తర్భావ "SDL_openharmonymouse.h"

#అన్తర్భావ "../../events/SDL_mouse_c.h"

#అన్తర్భావ "../../core/openharmony/SDL_openharmony.h"

స్థిర bool OPENHARMONY_ShowCursor(SDL_Cursor *cursor)
{
తిరిగి false;
#ఒకవేళ 0
    ఒకవేళ (!cursor) {
        cursor = OPENHARMONY_Create_ఖాళీలు_Cursor();
    }
    ఒకవేళ (cursor) {
        SDL_Cursor_దత్తాంశం *దత్తాంశం = cursor->అంతర్గత;
        ఒకవేళ (దత్తాంశం->custom_cursor) {
            ఒకవేళ (!OPENHARMONY_JNI_సమితి_Custom_Cursor(దత్తాంశం->custom_cursor)) {
                తిరిగి SDL_Unsupported();
            }
        } లేకపోతే {
            ఒకవేళ (!OPENHARMONY_JNI_సమితి_System_Cursor(దత్తాంశం->system_cursor)) {
                తిరిగి SDL_Unsupported();
            }
        }
        తిరిగి true;
    } లేకపోతే {
        // SDL error set inside OPENHARMONY_CreateEmptyCursor()
        తిరిగి false;
    }
#అయితే_ముగింపు
}

శూన్య OPENHARMONY_InitMouse(శూన్య)
{
    SDL_Mouse *mouse = SDL_GetMouse();
//!!! FIXME:    mouse->CreateCursor = OPENHARMONY_CreateCursor;
//!!! FIXME:    mouse->CreateSystemCursor = OPENHARMONY_CreateSystemCursor;
    mouse->ShowCursor = OPENHARMONY_ShowCursor;
//!!! FIXME:    mouse->FreeCursor = OPENHARMONY_FreeCursor;
//!!! FIXME:    mouse->SetRelativeMouseMode = OPENHARMONY_SetRelativeMouseMode;

//!!! FIXME:    SDL_SetDefaultCursor(OPENHARMONY_CreateDefaultCursor());
}

శూన్య OPENHARMONY_QuitMouse(శూన్య)
{
//!!! FIXME:    OPENHARMONY_DestroyEmptyCursor();
}

#అయితే_ముగింపు

