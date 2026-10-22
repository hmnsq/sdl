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

#ضمن "SDL_internal.h"

#اگر_تعریف_شده SDL_VIDEO_DRIVER_OPENHARMONY

#ضمن "SDL_openharmonymouse.h"

#ضمن "../../events/SDL_mouse_c.h"

#ضمن "../../core/openharmony/SDL_openharmony.h"

ساكن bool OPENHARMONY_ShowCursor(SDL_Cursor *cursor)
{
أرجع false;
#إذا 0
    إذا (!cursor) {
        cursor = OPENHARMONY_Create_خالی_Cursor();
    }
    إذا (cursor) {
        SDL_Cursor_داده *داده = cursor->داخلی;
        إذا (داده->custom_cursor) {
            إذا (!OPENHARMONY_JNI_مجموعه_Custom_Cursor(داده->custom_cursor)) {
                أرجع SDL_Unsupported();
            }
        } وإلا {
            إذا (!OPENHARMONY_JNI_مجموعه_System_Cursor(داده->system_cursor)) {
                أرجع SDL_Unsupported();
            }
        }
        أرجع true;
    } وإلا {
        // SDL error set inside OPENHARMONY_CreateEmptyCursor()
        أرجع false;
    }
#پایان_اگر
}

فراغ OPENHARMONY_InitMouse(فراغ)
{
    SDL_Mouse *mouse = SDL_GetMouse();
//!!! FIXME:    mouse->CreateCursor = OPENHARMONY_CreateCursor;
//!!! FIXME:    mouse->CreateSystemCursor = OPENHARMONY_CreateSystemCursor;
    mouse->ShowCursor = OPENHARMONY_ShowCursor;
//!!! FIXME:    mouse->FreeCursor = OPENHARMONY_FreeCursor;
//!!! FIXME:    mouse->SetRelativeMouseMode = OPENHARMONY_SetRelativeMouseMode;

//!!! FIXME:    SDL_SetDefaultCursor(OPENHARMONY_CreateDefaultCursor());
}

فراغ OPENHARMONY_QuitMouse(فراغ)
{
//!!! FIXME:    OPENHARMONY_DestroyEmptyCursor();
}

#پایان_اگر

