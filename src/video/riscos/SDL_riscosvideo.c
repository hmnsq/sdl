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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_RISCOS

#ଅନ୍ତର୍ଭାଵ "../SDL_sysvideo.h"
#ଅନ୍ତର୍ଭାଵ "../SDL_pixels_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_events_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_keyboard_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_mouse_c.h"

#ଅନ୍ତର୍ଭାଵ "SDL_riscosvideo.h"
#ଅନ୍ତର୍ଭାଵ "SDL_riscosevents_c.h"
#ଅନ୍ତର୍ଭାଵ "SDL_riscosframebuffer_c.h"
#ଅନ୍ତର୍ଭାଵ "SDL_riscosmouse.h"
#ଅନ୍ତର୍ଭାଵ "SDL_riscosmodes.h"
#ଅନ୍ତର୍ଭାଵ "SDL_riscoswindow.h"
#ଅନ୍ତର୍ଭାଵ "SDL_riscosmessagebox.h"

#define RISCOSVID_DRIVER_NAME "riscos"

// Initialization/Query functions
ସ୍ଥିର bool RISCOS_VideoInit(SDL_VideoDevice *_this);
ସ୍ଥିର ଶୂନ୍ୟ RISCOS_VideoQuit(SDL_VideoDevice *_this);

// RISC OS driver bootstrap functions

ସ୍ଥିର ଶୂନ୍ୟ RISCOS_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

ସ୍ଥିର SDL_VideoDevice *RISCOS_CreateDevice(ଶୂନ୍ୟ)
{
    SDL_VideoDevice *device;
    SDL_VideoData *data;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, ଆକାର(SDL_VideoDevice));
    ଯଦି (!device) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    // Initialize internal data
    data = (SDL_VideoData *)SDL_calloc(1, ଆକାର(SDL_VideoData));
    ଯଦି (!data) {
        SDL_free(device);
        ଫେରନ୍ତୁ ଖାଲି;
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

    device->ମୁକ୍ତ = RISCOS_DeleteDevice;

    // TODO: Support windowed mode
    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    ଫେରନ୍ତୁ device;
}

VideoBootStrap RISCOS_bootstrap = {
    RISCOSVID_DRIVER_NAME, "SDL RISC OS video driver",
    RISCOS_CreateDevice,
    RISCOS_ShowMessageBox,
    false
};

ସ୍ଥିର bool RISCOS_VideoInit(SDL_VideoDevice *_this)
{
    ଯଦି (!RISCOS_InitEvents(_this)) {
        ଫେରନ୍ତୁ false;
    }

    ଯଦି (!RISCOS_InitMouse(_this)) {
        ଫେରନ୍ତୁ false;
    }

    // Assume we have a mouse and keyboard
    SDL_AddKeyboard(SDL_DEFAULT_KEYBOARD_ID, ଖାଲି);
    SDL_AddMouse(SDL_DEFAULT_MOUSE_ID, ଖାଲି);

    ଯଦି (!RISCOS_InitModes(_this)) {
        ଫେରନ୍ତୁ false;
    }

    // We're done!
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର ଶୂନ୍ୟ RISCOS_VideoQuit(SDL_VideoDevice *_this)
{
    RISCOS_QuitEvents(_this);
}

#endif // SDL_VIDEO_DRIVER_RISCOS
