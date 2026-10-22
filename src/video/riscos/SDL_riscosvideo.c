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

#ifdef SDL_VIDEO_DRIVER_RISCOS

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../SDL_pixels_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_keyboard_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"

#ಅನ್ತರ್ಭಾವ "SDL_riscosvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_riscosevents_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_riscosframebuffer_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_riscosmouse.h"
#ಅನ್ತರ್ಭಾವ "SDL_riscosmodes.h"
#ಅನ್ತರ್ಭಾವ "SDL_riscoswindow.h"
#ಅನ್ತರ್ಭಾವ "SDL_riscosmessagebox.h"

#define RISCOSVID_DRIVER_NAME "riscos"

// Initialization/Query functions
ಸ್ಥಿರ bool RISCOS_VideoInit(SDL_VideoDevice *_this);
ಸ್ಥಿರ ಶೂನ್ಯ RISCOS_VideoQuit(SDL_VideoDevice *_this);

// RISC OS driver bootstrap functions

ಸ್ಥಿರ ಶೂನ್ಯ RISCOS_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

ಸ್ಥಿರ SDL_VideoDevice *RISCOS_CreateDevice(ಶೂನ್ಯ)
{
    SDL_VideoDevice *device;
    SDL_VideoData *data;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, ಪರಿಮಾಣ(SDL_VideoDevice));
    ಯದಿ (!device) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    // Initialize internal data
    data = (SDL_VideoData *)SDL_calloc(1, ಪರಿಮಾಣ(SDL_VideoData));
    ಯದಿ (!data) {
        SDL_free(device);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    device->internal = data;

    // Set the function pointers
    device->VideoInit = RISCOS_VideoInit;
    device->VideoQuit = RISCOS_VideoQuit;
    device->PumpEvents = RISCOS_PumpEvents;

    device->GetDisplayModes = RISCOS_GetDisplayModes;
    device->SetDisplayMode = RISCOS_SetDisplayMode;

    device->CreateSDLWindow = RISCOS_CreateWindow;
    device->DestroyWindow = RISCOS_DestroyWindow;

    device->CreateWindowFramebuffer = RISCOS_CreateWindowFramebuffer;
    device->UpdateWindowFramebuffer = RISCOS_UpdateWindowFramebuffer;
    device->DestroyWindowFramebuffer = RISCOS_DestroyWindowFramebuffer;

    device->ಮುಕ್ತ = RISCOS_DeleteDevice;

    // TODO: Support windowed mode
    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    ಪ್ರತ್ಯಾಗಮ device;
}

VideoBootStrap RISCOS_bootstrap = {
    RISCOSVID_DRIVER_NAME, "SDL RISC OS video driver",
    RISCOS_CreateDevice,
    RISCOS_ShowMessageBox,
    false
};

ಸ್ಥಿರ bool RISCOS_VideoInit(SDL_VideoDevice *_this)
{
    ಯದಿ (!RISCOS_InitEvents(_this)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಯದಿ (!RISCOS_InitMouse(_this)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    // Assume we have a mouse and keyboard
    SDL_AddKeyboard(SDL_DEFAULT_KEYBOARD_ID, ರಿಕ್ತ);
    SDL_AddMouse(SDL_DEFAULT_MOUSE_ID, ರಿಕ್ತ);

    ಯದಿ (!RISCOS_InitModes(_this)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    // We're done!
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ RISCOS_VideoQuit(SDL_VideoDevice *_this)
{
    RISCOS_QuitEvents(_this);
}

#endif // SDL_VIDEO_DRIVER_RISCOS
