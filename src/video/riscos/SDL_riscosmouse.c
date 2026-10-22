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

#నిర్వచితమైతే SDL_VIDEO_DRIVER_RISCOS

#అన్తర్భావ "SDL_riscosvideo.h"
#అన్తర్భావ "SDL_riscosmouse.h"
#అన్తర్భావ "../../events/SDL_mouse_c.h"

#అన్తర్భావ <kernel.h>

స్థిర SDL_Cursor *RISCOS_CreateDefaultCursor(శూన్య)
{
    SDL_Cursor *cursor = SDL_calloc(1, పరిమాణం(*cursor));
    ఒకవేళ (cursor) {
        // NULL is used to indicate the default cursor
        cursor->అంతర్గత = ఖాళీ;
    }

    తిరిగి cursor;
}

స్థిర శూన్య RISCOS_FreeCursor(SDL_Cursor *cursor)
{
    SDL_free(cursor);
}

స్థిర bool RISCOS_ShowCursor(SDL_Cursor *cursor)
{
    ఒకవేళ (cursor) {
        // Turn the mouse pointer on
        _kernel_osbyte(106, 1, 0);
    } లేకపోతే {
        // Turn the mouse pointer off
        _kernel_osbyte(106, 0, 0);
    }

    తిరిగి true;
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

    SDL_సమితి_Default_Cursor(RISCOS_CreateDefaultCursor());

    తిరిగి true;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_RISCOS
