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
#अन्तर्भाव "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_RISCOS

#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../SDL_pixels_c.h"
#अन्तर्भाव "../../events/SDL_events_c.h"
#अन्तर्भाव "../../events/SDL_keyboard_c.h"
#अन्तर्भाव "../../events/SDL_mouse_c.h"

#अन्तर्भाव "SDL_riscosvideo.h"
#अन्तर्भाव "SDL_riscosevents_c.h"
#अन्तर्भाव "SDL_riscosframebuffer_c.h"
#अन्तर्भाव "SDL_riscosmouse.h"
#अन्तर्भाव "SDL_riscosmodes.h"
#अन्तर्भाव "SDL_riscoswindow.h"
#अन्तर्भाव "SDL_riscosmessagebox.h"

#define RISCOSVID_DRIVER_NAME "riscos"

// Initialization/Query functions
स्थिर bool RISCOS_VideoInit(SDL_VideoDevice *_this);
स्थिर शून्य RISCOS_VideoQuit(SDL_VideoDevice *_this);

// RISC OS driver bootstrap functions

स्थिर शून्य RISCOS_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

स्थिर SDL_VideoDevice *RISCOS_CreateDevice(शून्य)
{
    SDL_VideoDevice *device;
    SDL_VideoData *data;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, परिमाण(SDL_VideoDevice));
    जइ (!device) {
        प्रत्यागम रिक्त;
    }

    // Initialize internal data
    data = (SDL_VideoData *)SDL_calloc(1, परिमाण(SDL_VideoData));
    जइ (!data) {
        SDL_free(device);
        प्रत्यागम रिक्त;
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

    device->मुक्त = RISCOS_DeleteDevice;

    // TODO: Support windowed mode
    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    प्रत्यागम device;
}

VideoBootStrap RISCOS_bootstrap = {
    RISCOSVID_DRIVER_NAME, "SDL RISC OS video driver",
    RISCOS_CreateDevice,
    RISCOS_ShowMessageBox,
    false
};

स्थिर bool RISCOS_VideoInit(SDL_VideoDevice *_this)
{
    जइ (!RISCOS_InitEvents(_this)) {
        प्रत्यागम false;
    }

    जइ (!RISCOS_InitMouse(_this)) {
        प्रत्यागम false;
    }

    // Assume we have a mouse and keyboard
    SDL_AddKeyboard(SDL_DEFAULT_KEYBOARD_ID, रिक्त);
    SDL_AddMouse(SDL_DEFAULT_MOUSE_ID, रिक्त);

    जइ (!RISCOS_InitModes(_this)) {
        प्रत्यागम false;
    }

    // We're done!
    प्रत्यागम true;
}

स्थिर शून्य RISCOS_VideoQuit(SDL_VideoDevice *_this)
{
    RISCOS_QuitEvents(_this);
}

#endif // SDL_VIDEO_DRIVER_RISCOS
