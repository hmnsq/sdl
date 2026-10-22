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

#ifdef SDL_VIDEO_DRIVER_RISCOS

#அந்தர்பாவ "SDL_riscosvideo.h"
#அந்தர்பாவ "SDL_riscosmouse.h"
#அந்தர்பாவ "../../events/SDL_mouse_c.h"

#அந்தர்பாவ <kernel.h>

நிலையான SDL_Cursor *RISCOS_CreateDefaultCursor(வெறுமை)
{
    SDL_Cursor *cursor = SDL_calloc(1, அளவு(*cursor));
    எனில் (cursor) {
        // NULL is used to indicate the default cursor
        cursor->internal = வெற்று;
    }

    திரும்பு cursor;
}

நிலையான வெறுமை RISCOS_FreeCursor(SDL_Cursor *cursor)
{
    SDL_free(cursor);
}

நிலையான bool RISCOS_ShowCursor(SDL_Cursor *cursor)
{
    எனில் (cursor) {
        // Turn the mouse pointer on
        _kernel_osbyte(106, 1, 0);
    } இல்லையெனில் {
        // Turn the mouse pointer off
        _kernel_osbyte(106, 0, 0);
    }

    திரும்பு true;
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

    SDL_SetDefaultCursor(RISCOS_CreateDefaultCursor());

    திரும்பு true;
}

#endif // SDL_VIDEO_DRIVER_RISCOS
