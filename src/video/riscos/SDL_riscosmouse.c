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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_RISCOS

#ಅನ್ತರ್ಭಾವ "SDL_riscosvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_riscosmouse.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"

#ಅನ್ತರ್ಭಾವ <kernel.h>

ಸ್ಥಿರ SDL_Cursor *RISCOS_CreateDefaultCursor(ಶೂನ್ಯ)
{
    SDL_Cursor *cursor = SDL_calloc(1, ಗಾತ್ರ(*cursor));
    ಆದರೆ (cursor) {
        // NULL is used to indicate the default cursor
        cursor->ಆಂತರಿಕ = ಖಾಲಿ;
    }

    ಹಿಂತಿರುಗಿ cursor;
}

ಸ್ಥಿರ ಶೂನ್ಯ RISCOS_FreeCursor(SDL_Cursor *cursor)
{
    SDL_free(cursor);
}

ಸ್ಥಿರ bool RISCOS_ShowCursor(SDL_Cursor *cursor)
{
    ಆದರೆ (cursor) {
        // Turn the mouse pointer on
        _kernel_osbyte(106, 1, 0);
    } ಇಲ್ಲದಿದ್ದರೆ {
        // Turn the mouse pointer off
        _kernel_osbyte(106, 0, 0);
    }

    ಹಿಂತಿರುಗಿ true;
}

bool RISCOS_InitMouse(SDL_VideoDevice *_this)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    // mouse->CreateCursor = RISCOS_CreateCursor;
    // mouse->CreateSystemCursor = RISCOS_CreateSystemCursor;
    mouse->ShowCursor = RISCOS_ShowCursor;
    mouse->FreeCursor = RISCOS_FreeCursor;
    // mouse->WarpMouse = RISCOS_WarpMouse;
    // mouse->WarpMouseGlobal = RISCOS_WarpMouseGlobal;
    // mouse->SetRelativeMouseMode = RISCOS_SetRelativeMouseMode;
    // mouse->CaptureMouse = RISCOS_CaptureMouse;
    // mouse->GetGlobalMouseState = RISCOS_GetGlobalMouseState;

    SDL_ಗಣ_Default_Cursor(RISCOS_CreateDefaultCursor());

    ಹಿಂತಿರುಗಿ true;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_RISCOS
