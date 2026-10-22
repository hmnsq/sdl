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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_OPENHARMONY

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_openharmonymouse.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/openharmony/SDL_openharmony.h"

ਸਥਿਰ bool OPENHARMONY_ShowCursor(SDL_Cursor *cursor)
{
ਵਾਪਸ false;
#ਜੇ 0
    ਜੇ (!cursor) {
        cursor = OPENHARMONY_Create_ਖਾਲੀ_ਥਾਵਾਂ_Cursor();
    }
    ਜੇ (cursor) {
        SDL_Cursor_ਅੰਕੜੇ *ਅੰਕੜੇ = cursor->ਅੰਦਰੂਨੀ;
        ਜੇ (ਅੰਕੜੇ->custom_cursor) {
            ਜੇ (!OPENHARMONY_JNI_ਸੈੱਟ_Custom_Cursor(ਅੰਕੜੇ->custom_cursor)) {
                ਵਾਪਸ SDL_Unsupported();
            }
        } ਨਹੀਂਤਾਂ {
            ਜੇ (!OPENHARMONY_JNI_ਸੈੱਟ_System_Cursor(ਅੰਕੜੇ->system_cursor)) {
                ਵਾਪਸ SDL_Unsupported();
            }
        }
        ਵਾਪਸ true;
    } ਨਹੀਂਤਾਂ {
        // SDL error set inside OPENHARMONY_CreateEmptyCursor()
        ਵਾਪਸ false;
    }
#ਜੇ_ਅੰਤ
}

ਖਾਲੀ OPENHARMONY_InitMouse(ਖਾਲੀ)
{
    SDL_Mouse *mouse = SDL_GetMouse();
//!!! FIXME:    mouse->CreateCursor = OPENHARMONY_CreateCursor;
//!!! FIXME:    mouse->CreateSystemCursor = OPENHARMONY_CreateSystemCursor;
    mouse->ShowCursor = OPENHARMONY_ShowCursor;
//!!! FIXME:    mouse->FreeCursor = OPENHARMONY_FreeCursor;
//!!! FIXME:    mouse->SetRelativeMouseMode = OPENHARMONY_SetRelativeMouseMode;

//!!! FIXME:    SDL_SetDefaultCursor(OPENHARMONY_CreateDefaultCursor());
}

ਖਾਲੀ OPENHARMONY_QuitMouse(ਖਾਲੀ)
{
//!!! FIXME:    OPENHARMONY_DestroyEmptyCursor();
}

#ਜੇ_ਅੰਤ

