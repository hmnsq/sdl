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

#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_OPENHARMONY

#அந்தர்பாவ "SDL_openharmonymouse.h"

#அந்தர்பாவ "../../events/SDL_mouse_c.h"

#அந்தர்பாவ "../../core/openharmony/SDL_openharmony.h"

நிலையான bool OPENHARMONY_ShowCursor(SDL_Cursor *cursor)
{
திரும்பு false;
#எனில் 0
    எனில் (!cursor) {
        cursor = OPENHARMONY_CreateEmptyCursor();
    }
    எனில் (cursor) {
        SDL_CursorData *data = cursor->internal;
        எனில் (data->custom_cursor) {
            எனில் (!OPENHARMONY_JNI_SetCustomCursor(data->custom_cursor)) {
                திரும்பு SDL_Unsupported();
            }
        } இல்லையெனில் {
            எனில் (!OPENHARMONY_JNI_SetSystemCursor(data->system_cursor)) {
                திரும்பு SDL_Unsupported();
            }
        }
        திரும்பு true;
    } இல்லையெனில் {
        // SDL error set inside OPENHARMONY_CreateEmptyCursor()
        திரும்பு false;
    }
#endif
}

வெறுமை OPENHARMONY_InitMouse(வெறுமை)
{
    SDL_Mouse *mouse = SDL_GetMouse();
//!!! FIXME:    mouse->CreateCursor = OPENHARMONY_CreateCursor;
//!!! FIXME:    mouse->CreateSystemCursor = OPENHARMONY_CreateSystemCursor;
    mouse->ShowCursor = OPENHARMONY_ShowCursor;
//!!! FIXME:    mouse->FreeCursor = OPENHARMONY_FreeCursor;
//!!! FIXME:    mouse->SetRelativeMouseMode = OPENHARMONY_SetRelativeMouseMode;

//!!! FIXME:    SDL_SetDefaultCursor(OPENHARMONY_CreateDefaultCursor());
}

வெறுமை OPENHARMONY_QuitMouse(வெறுமை)
{
//!!! FIXME:    OPENHARMONY_DestroyEmptyCursor();
}

#endif

