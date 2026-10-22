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

#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_OPENHARMONY

#অন্তর্ভাব "SDL_openharmonymouse.h"

#অন্তর্ভাব "../../events/SDL_mouse_c.h"

#অন্তর্ভাব "../../core/openharmony/SDL_openharmony.h"

স্থির bool OPENHARMONY_ShowCursor(SDL_Cursor *cursor)
{
প্রত্যাগম false;
#যদি 0
    যদি (!cursor) {
        cursor = OPENHARMONY_CreateEmptyCursor();
    }
    যদি (cursor) {
        SDL_CursorData *data = cursor->internal;
        যদি (data->custom_cursor) {
            যদি (!OPENHARMONY_JNI_SetCustomCursor(data->custom_cursor)) {
                প্রত্যাগম SDL_Unsupported();
            }
        } অন্যথা {
            যদি (!OPENHARMONY_JNI_SetSystemCursor(data->system_cursor)) {
                প্রত্যাগম SDL_Unsupported();
            }
        }
        প্রত্যাগম true;
    } অন্যথা {
        // SDL error set inside OPENHARMONY_CreateEmptyCursor()
        প্রত্যাগম false;
    }
#endif
}

শূন্য OPENHARMONY_InitMouse(শূন্য)
{
    SDL_Mouse *mouse = SDL_GetMouse();
//!!! FIXME:    mouse->CreateCursor = OPENHARMONY_CreateCursor;
//!!! FIXME:    mouse->CreateSystemCursor = OPENHARMONY_CreateSystemCursor;
    mouse->ShowCursor = OPENHARMONY_ShowCursor;
//!!! FIXME:    mouse->FreeCursor = OPENHARMONY_FreeCursor;
//!!! FIXME:    mouse->SetRelativeMouseMode = OPENHARMONY_SetRelativeMouseMode;

//!!! FIXME:    SDL_SetDefaultCursor(OPENHARMONY_CreateDefaultCursor());
}

শূন্য OPENHARMONY_QuitMouse(শূন্য)
{
//!!! FIXME:    OPENHARMONY_DestroyEmptyCursor();
}

#endif

