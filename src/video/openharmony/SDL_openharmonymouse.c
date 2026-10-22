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

#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_OPENHARMONY

#അന്തര്ഭാവ "SDL_openharmonymouse.h"

#അന്തര്ഭാവ "../../events/SDL_mouse_c.h"

#അന്തര്ഭാവ "../../core/openharmony/SDL_openharmony.h"

സ്ഥിതം bool OPENHARMONY_ShowCursor(SDL_Cursor *cursor)
{
തിരികെ false;
#എങ്കിൽ 0
    എങ്കിൽ (!cursor) {
        cursor = OPENHARMONY_CreateEmptyCursor();
    }
    എങ്കിൽ (cursor) {
        SDL_CursorData *data = cursor->internal;
        എങ്കിൽ (data->custom_cursor) {
            എങ്കിൽ (!OPENHARMONY_JNI_SetCustomCursor(data->custom_cursor)) {
                തിരികെ SDL_Unsupported();
            }
        } അല്ലെങ്കിൽ {
            എങ്കിൽ (!OPENHARMONY_JNI_SetSystemCursor(data->system_cursor)) {
                തിരികെ SDL_Unsupported();
            }
        }
        തിരികെ true;
    } അല്ലെങ്കിൽ {
        // SDL error set inside OPENHARMONY_CreateEmptyCursor()
        തിരികെ false;
    }
#endif
}

ശൂന്യം OPENHARMONY_InitMouse(ശൂന്യം)
{
    SDL_Mouse *mouse = SDL_GetMouse();
//!!! FIXME:    mouse->CreateCursor = OPENHARMONY_CreateCursor;
//!!! FIXME:    mouse->CreateSystemCursor = OPENHARMONY_CreateSystemCursor;
    mouse->ShowCursor = OPENHARMONY_ShowCursor;
//!!! FIXME:    mouse->FreeCursor = OPENHARMONY_FreeCursor;
//!!! FIXME:    mouse->SetRelativeMouseMode = OPENHARMONY_SetRelativeMouseMode;

//!!! FIXME:    SDL_SetDefaultCursor(OPENHARMONY_CreateDefaultCursor());
}

ശൂന്യം OPENHARMONY_QuitMouse(ശൂന്യം)
{
//!!! FIXME:    OPENHARMONY_DestroyEmptyCursor();
}

#endif

