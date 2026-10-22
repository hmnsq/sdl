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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_RISCOS

#समावेश "SDL_riscosvideo.h"
#समावेश "SDL_riscosmouse.h"
#समावेश "../../events/SDL_mouse_c.h"

#समावेश <kernel.h>

अटल SDL_Cursor *RISCOS_CreateDefaultCursor(व्योम)
{
    SDL_Cursor *cursor = SDL_calloc(1, माप(*cursor));
    अगर (cursor) {
        // NULL is used to indicate the default cursor
        cursor->internal = शून्य;
    }

    वापस cursor;
}

अटल व्योम RISCOS_FreeCursor(SDL_Cursor *cursor)
{
    SDL_free(cursor);
}

अटल bool RISCOS_ShowCursor(SDL_Cursor *cursor)
{
    अगर (cursor) {
        // Turn the mouse pointer on
        _kernel_osbyte(106, 1, 0);
    } अन्यथा {
        // Turn the mouse pointer off
        _kernel_osbyte(106, 0, 0);
    }

    वापस true;
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

    वापस true;
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_RISCOS
