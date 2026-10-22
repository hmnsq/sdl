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
#ضمن "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_RISCOS

#ضمن "../SDL_sysvideo.h"
#ضمن "../SDL_pixels_c.h"
#ضمن "../../events/SDL_events_c.h"
#ضمن "../../events/SDL_keyboard_c.h"
#ضمن "../../events/SDL_mouse_c.h"

#ضمن "SDL_riscosvideo.h"
#ضمن "SDL_riscosevents_c.h"
#ضمن "SDL_riscosframebuffer_c.h"
#ضمن "SDL_riscosmouse.h"
#ضمن "SDL_riscosmodes.h"
#ضمن "SDL_riscoswindow.h"
#ضمن "SDL_riscosmessagebox.h"

#define RISCOSVID_DRIVER_NAME "riscos"

// Initialization/Query functions
ساكن bool RISCOS_VideoInit(SDL_VideoDevice *_this);
ساكن فراغ RISCOS_VideoQuit(SDL_VideoDevice *_this);

// RISC OS driver bootstrap functions

ساكن فراغ RISCOS_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

ساكن SDL_VideoDevice *RISCOS_CreateDevice(فراغ)
{
    SDL_VideoDevice *device;
    SDL_VideoData *data;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    𐡄𐡍 (!device) {
        أرجع عدم;
    }

    // Initialize internal data
    data = (SDL_VideoData *)SDL_calloc(1, حجم(SDL_VideoData));
    𐡄𐡍 (!data) {
        SDL_free(device);
        أرجع عدم;
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

    device->حرر = RISCOS_DeleteDevice;

    // TODO: Support windowed mode
    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    أرجع device;
}

VideoBootStrap RISCOS_bootstrap = {
    RISCOSVID_DRIVER_NAME, "SDL RISC OS video driver",
    RISCOS_CreateDevice,
    RISCOS_ShowMessageBox,
    false
};

ساكن bool RISCOS_VideoInit(SDL_VideoDevice *_this)
{
    𐡄𐡍 (!RISCOS_InitEvents(_this)) {
        أرجع false;
    }

    𐡄𐡍 (!RISCOS_InitMouse(_this)) {
        أرجع false;
    }

    // Assume we have a mouse and keyboard
    SDL_AddKeyboard(SDL_DEFAULT_KEYBOARD_ID, عدم);
    SDL_AddMouse(SDL_DEFAULT_MOUSE_ID, عدم);

    𐡄𐡍 (!RISCOS_InitModes(_this)) {
        أرجع false;
    }

    // We're done!
    أرجع true;
}

ساكن فراغ RISCOS_VideoQuit(SDL_VideoDevice *_this)
{
    RISCOS_QuitEvents(_this);
}

#endif // SDL_VIDEO_DRIVER_RISCOS
