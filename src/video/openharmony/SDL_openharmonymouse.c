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

#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_OPENHARMONY

#અન્તર્ભાવ "SDL_openharmonymouse.h"

#અન્તર્ભાવ "../../events/SDL_mouse_c.h"

#અન્તર્ભાવ "../../core/openharmony/SDL_openharmony.h"

સ્થિર bool OPENHARMONY_ShowCursor(SDL_Cursor *cursor)
{
પાછા false;
#જો 0
    જો (!cursor) {
        cursor = OPENHARMONY_CreateEmptyCursor();
    }
    જો (cursor) {
        SDL_CursorData *data = cursor->internal;
        જો (data->custom_cursor) {
            જો (!OPENHARMONY_JNI_SetCustomCursor(data->custom_cursor)) {
                પાછા SDL_Unsupported();
            }
        } નહીંતર {
            જો (!OPENHARMONY_JNI_SetSystemCursor(data->system_cursor)) {
                પાછા SDL_Unsupported();
            }
        }
        પાછા true;
    } નહીંતર {
        // SDL error set inside OPENHARMONY_CreateEmptyCursor()
        પાછા false;
    }
#endif
}

શૂન્ય OPENHARMONY_InitMouse(શૂન્ય)
{
    SDL_Mouse *mouse = SDL_GetMouse();
//!!! FIXME:    mouse->CreateCursor = OPENHARMONY_CreateCursor;
//!!! FIXME:    mouse->CreateSystemCursor = OPENHARMONY_CreateSystemCursor;
    mouse->ShowCursor = OPENHARMONY_ShowCursor;
//!!! FIXME:    mouse->FreeCursor = OPENHARMONY_FreeCursor;
//!!! FIXME:    mouse->SetRelativeMouseMode = OPENHARMONY_SetRelativeMouseMode;

//!!! FIXME:    SDL_SetDefaultCursor(OPENHARMONY_CreateDefaultCursor());
}

શૂન્ય OPENHARMONY_QuitMouse(શૂન્ય)
{
//!!! FIXME:    OPENHARMONY_DestroyEmptyCursor();
}

#endif

