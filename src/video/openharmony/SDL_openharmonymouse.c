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

#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_OPENHARMONY

#شامل "SDL_openharmonymouse.h"

#شامل "../../events/SDL_mouse_c.h"

#شامل "../../core/openharmony/SDL_openharmony.h"

ساکن bool OPENHARMONY_ShowCursor(SDL_Cursor *cursor)
{
واپس false;
#اگر 0
    اگر (!cursor) {
        cursor = OPENHARMONY_Create_خالی_خانے_Cursor();
    }
    اگر (cursor) {
        SDL_Cursor_ڈیٹا *ڈیٹا = cursor->اندرونی_2;
        اگر (ڈیٹا->custom_cursor) {
            اگر (!OPENHARMONY_JNI_سیٹ_Custom_Cursor(ڈیٹا->custom_cursor)) {
                واپس SDL_Unsupported();
            }
        } ورنہ {
            اگر (!OPENHARMONY_JNI_سیٹ_System_Cursor(ڈیٹا->system_cursor)) {
                واپس SDL_Unsupported();
            }
        }
        واپس true;
    } ورنہ {
        // SDL error set inside OPENHARMONY_CreateEmptyCursor()
        واپس false;
    }
#اگر_ختم
}

خالی OPENHARMONY_InitMouse(خالی)
{
    SDL_Mouse *mouse = SDL_GetMouse();
//!!! FIXME:    mouse->CreateCursor = OPENHARMONY_CreateCursor;
//!!! FIXME:    mouse->CreateSystemCursor = OPENHARMONY_CreateSystemCursor;
    mouse->ShowCursor = OPENHARMONY_ShowCursor;
//!!! FIXME:    mouse->FreeCursor = OPENHARMONY_FreeCursor;
//!!! FIXME:    mouse->SetRelativeMouseMode = OPENHARMONY_SetRelativeMouseMode;

//!!! FIXME:    SDL_SetDefaultCursor(OPENHARMONY_CreateDefaultCursor());
}

خالی OPENHARMONY_QuitMouse(خالی)
{
//!!! FIXME:    OPENHARMONY_DestroyEmptyCursor();
}

#اگر_ختم

