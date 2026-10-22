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

#include "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_OPENHARMONY

#include "SDL_openharmonymouse.h"

#include "../../events/SDL_mouse_c.h"

#include "../../core/openharmony/SDL_openharmony.h"

static bool OPENHARMONY_ShowCursor(SDL_Cursor *cursor)
{
반환 false;
#만약 0
    만약 (!cursor) {
        cursor = OPENHARMONY_CreateEmptyCursor();
    }
    만약 (cursor) {
        SDL_CursorData *data = cursor->internal;
        만약 (data->custom_cursor) {
            만약 (!OPENHARMONY_JNI_SetCustomCursor(data->custom_cursor)) {
                반환 SDL_Unsupported();
            }
        } 아니면 {
            만약 (!OPENHARMONY_JNI_SetSystemCursor(data->system_cursor)) {
                반환 SDL_Unsupported();
            }
        }
        반환 true;
    } 아니면 {
        // SDL error set inside OPENHARMONY_CreateEmptyCursor()
        반환 false;
    }
#endif
}

void OPENHARMONY_InitMouse(void)
{
    SDL_Mouse *mouse = SDL_GetMouse();
//!!! FIXME:    mouse->CreateCursor = OPENHARMONY_CreateCursor;
//!!! FIXME:    mouse->CreateSystemCursor = OPENHARMONY_CreateSystemCursor;
    mouse->ShowCursor = OPENHARMONY_ShowCursor;
//!!! FIXME:    mouse->FreeCursor = OPENHARMONY_FreeCursor;
//!!! FIXME:    mouse->SetRelativeMouseMode = OPENHARMONY_SetRelativeMouseMode;

//!!! FIXME:    SDL_SetDefaultCursor(OPENHARMONY_CreateDefaultCursor());
}

void OPENHARMONY_QuitMouse(void)
{
//!!! FIXME:    OPENHARMONY_DestroyEmptyCursor();
}

#endif

