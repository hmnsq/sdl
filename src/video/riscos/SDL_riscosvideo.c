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

#அந்தர்பாவ "../SDL_sysvideo.h"
#அந்தர்பாவ "../SDL_pixels_c.h"
#அந்தர்பாவ "../../events/SDL_events_c.h"
#அந்தர்பாவ "../../events/SDL_keyboard_c.h"
#அந்தர்பாவ "../../events/SDL_mouse_c.h"

#அந்தர்பாவ "SDL_riscosvideo.h"
#அந்தர்பாவ "SDL_riscosevents_c.h"
#அந்தர்பாவ "SDL_riscosframebuffer_c.h"
#அந்தர்பாவ "SDL_riscosmouse.h"
#அந்தர்பாவ "SDL_riscosmodes.h"
#அந்தர்பாவ "SDL_riscoswindow.h"
#அந்தர்பாவ "SDL_riscosmessagebox.h"

#define RISCOSVID_DRIVER_NAME "riscos"

// Initialization/Query functions
நிலையான bool RISCOS_VideoInit(SDL_VideoDevice *_this);
நிலையான வெறுமை RISCOS_VideoQuit(SDL_VideoDevice *_this);

// RISC OS driver bootstrap functions

நிலையான வெறுமை RISCOS_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

நிலையான SDL_VideoDevice *RISCOS_CreateDevice(வெறுமை)
{
    SDL_VideoDevice *device;
    SDL_VideoData *data;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, அளவு(SDL_VideoDevice));
    எனில் (!device) {
        திரும்பு வெற்று;
    }

    // Initialize internal data
    data = (SDL_VideoData *)SDL_calloc(1, அளவு(SDL_VideoData));
    எனில் (!data) {
        SDL_free(device);
        திரும்பு வெற்று;
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

    device->விடுவி = RISCOS_DeleteDevice;

    // TODO: Support windowed mode
    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    திரும்பு device;
}

VideoBootStrap RISCOS_bootstrap = {
    RISCOSVID_DRIVER_NAME, "SDL RISC OS video driver",
    RISCOS_CreateDevice,
    RISCOS_ShowMessageBox,
    false
};

நிலையான bool RISCOS_VideoInit(SDL_VideoDevice *_this)
{
    எனில் (!RISCOS_InitEvents(_this)) {
        திரும்பு false;
    }

    எனில் (!RISCOS_InitMouse(_this)) {
        திரும்பு false;
    }

    // Assume we have a mouse and keyboard
    SDL_AddKeyboard(SDL_DEFAULT_KEYBOARD_ID, வெற்று);
    SDL_AddMouse(SDL_DEFAULT_MOUSE_ID, வெற்று);

    எனில் (!RISCOS_InitModes(_this)) {
        திரும்பு false;
    }

    // We're done!
    திரும்பு true;
}

நிலையான வெறுமை RISCOS_VideoQuit(SDL_VideoDevice *_this)
{
    RISCOS_QuitEvents(_this);
}

#endif // SDL_VIDEO_DRIVER_RISCOS
