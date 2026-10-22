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

#ವ್ಯಾಖ್ಯಾನಿಸು RISCOSVID_DRIVER_NAME "riscos"

// Initialization/Query functions
ಸ್ಥಿರ bool RISCOS_VideoInit(SDL_VideoDevice *_this);
ಸ್ಥಿರ ಶೂನ್ಯ RISCOS_VideoQuit(SDL_VideoDevice *_this);

// RISC OS driver bootstrap functions

ಸ್ಥಿರ ಶೂನ್ಯ RISCOS_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->ಆಂತರಿಕ);
    SDL_free(device);
}

ಸ್ಥಿರ SDL_VideoDevice *RISCOS_CreateDevice(ಶೂನ್ಯ)
{
    SDL_VideoDevice *device;
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, ಗಾತ್ರ(SDL_VideoDevice));
    ಆದರೆ (!device) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    // Initialize internal data
    ದತ್ತಾಂಶ = (SDL_Video_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_Video_ದತ್ತಾಂಶ));
    ಆದರೆ (!ದತ್ತಾಂಶ) {
        SDL_free(device);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    device->ಆಂತರಿಕ = ದತ್ತಾಂಶ;

    // Set the function pointers
    device->VideoInit = RISCOS_VideoInit;
    device->VideoQuit = RISCOS_VideoQuit;
    device->PumpEvents = RISCOS_PumpEvents;

    device->GetDisplayModes = RISCOS_GetDisplayModes;
    device->ಗಣ_Display_ಬಹುಲಕ = RISCOS_ಗಣ_Display_ಬಹುಲಕ;

    device->CreateSDLWindow = RISCOS_Create_ಕಿಟಕಿ;
    device->Destroy_ಕಿಟಕಿ = RISCOS_Destroy_ಕಿಟಕಿ;

    device->Create_ಕಿಟಕಿ_Framebuffer = RISCOS_Create_ಕಿಟಕಿ_Framebuffer;
    device->Update_ಕಿಟಕಿ_Framebuffer = RISCOS_Update_ಕಿಟಕಿ_Framebuffer;
    device->Destroy_ಕಿಟಕಿ_Framebuffer = RISCOS_Destroy_ಕಿಟಕಿ_Framebuffer;

    device->ಬಿಡುಗಡೆ = RISCOS_DeleteDevice;

    // TODO: Support windowed mode
    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    ಹಿಂತಿರುಗಿ device;
}

VideoBootStrap RISCOS_bootstrap = {
    RISCOSVID_DRIVER_NAME, "SDL RISC OS video driver",
    RISCOS_CreateDevice,
    RISCOS_Show_ಸಂದೇಶ_Box,
    false
};

ಸ್ಥಿರ bool RISCOS_VideoInit(SDL_VideoDevice *_this)
{
    ಆದರೆ (!RISCOS_InitEvents(_this)) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (!RISCOS_InitMouse(_this)) {
        ಹಿಂತಿರುಗಿ false;
    }

    // Assume we have a mouse and keyboard
    SDL_ಕೂಡಿಸು_Keyboard(SDL_DEFAULT_KEYBOARD_ID, ಖಾಲಿ);
    SDL_ಕೂಡಿಸು_Mouse(SDL_DEFAULT_MOUSE_ID, ಖಾಲಿ);

    ಆದರೆ (!RISCOS_InitModes(_this)) {
        ಹಿಂತಿರುಗಿ false;
    }

    // We're done!
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ RISCOS_VideoQuit(SDL_VideoDevice *_this)
{
    RISCOS_QuitEvents(_this);
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_RISCOS
