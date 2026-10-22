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
#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_RISCOS

#અન્તર્ભાવ "../SDL_sysvideo.h"
#અન્તર્ભાવ "../SDL_pixels_c.h"
#અન્તર્ભાવ "../../events/SDL_events_c.h"
#અન્તર્ભાવ "../../events/SDL_keyboard_c.h"
#અન્તર્ભાવ "../../events/SDL_mouse_c.h"

#અન્તર્ભાવ "SDL_riscosvideo.h"
#અન્તર્ભાવ "SDL_riscosevents_c.h"
#અન્તર્ભાવ "SDL_riscosframebuffer_c.h"
#અન્તર્ભાવ "SDL_riscosmouse.h"
#અન્તર્ભાવ "SDL_riscosmodes.h"
#અન્તર્ભાવ "SDL_riscoswindow.h"
#અન્તર્ભાવ "SDL_riscosmessagebox.h"

#define RISCOSVID_DRIVER_NAME "riscos"

// Initialization/Query functions
સ્થિર bool RISCOS_VideoInit(SDL_VideoDevice *_this);
સ્થિર શૂન્ય RISCOS_VideoQuit(SDL_VideoDevice *_this);

// RISC OS driver bootstrap functions

સ્થિર શૂન્ય RISCOS_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

સ્થિર SDL_VideoDevice *RISCOS_CreateDevice(શૂન્ય)
{
    SDL_VideoDevice *device;
    SDL_VideoData *data;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, કદ(SDL_VideoDevice));
    જો (!device) {
        પાછા ખાલી;
    }

    // Initialize internal data
    data = (SDL_VideoData *)SDL_calloc(1, કદ(SDL_VideoData));
    જો (!data) {
        SDL_free(device);
        પાછા ખાલી;
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

    device->મુક્ત = RISCOS_DeleteDevice;

    // TODO: Support windowed mode
    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    પાછા device;
}

VideoBootStrap RISCOS_bootstrap = {
    RISCOSVID_DRIVER_NAME, "SDL RISC OS video driver",
    RISCOS_CreateDevice,
    RISCOS_ShowMessageBox,
    false
};

સ્થિર bool RISCOS_VideoInit(SDL_VideoDevice *_this)
{
    જો (!RISCOS_InitEvents(_this)) {
        પાછા false;
    }

    જો (!RISCOS_InitMouse(_this)) {
        પાછા false;
    }

    // Assume we have a mouse and keyboard
    SDL_AddKeyboard(SDL_DEFAULT_KEYBOARD_ID, ખાલી);
    SDL_AddMouse(SDL_DEFAULT_MOUSE_ID, ખાલી);

    જો (!RISCOS_InitModes(_this)) {
        પાછા false;
    }

    // We're done!
    પાછા true;
}

સ્થિર શૂન્ય RISCOS_VideoQuit(SDL_VideoDevice *_this)
{
    RISCOS_QuitEvents(_this);
}

#endif // SDL_VIDEO_DRIVER_RISCOS
