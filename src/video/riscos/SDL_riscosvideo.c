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

#که_تعریف_شوی SDL_VIDEO_DRIVER_RISCOS

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

#تعریف_کړه RISCOSVID_DRIVER_NAME "riscos"

// Initialization/Query functions
ساكن bool RISCOS_VideoInit(SDL_VideoDevice *_this);
ساكن فراغ RISCOS_VideoQuit(SDL_VideoDevice *_this);

// RISC OS driver bootstrap functions

ساكن فراغ RISCOS_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->دننی);
    SDL_free(device);
}

ساكن SDL_VideoDevice *RISCOS_CreateDevice(فراغ)
{
    SDL_VideoDevice *device;
    SDL_Video_معلومات *معلومات;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (!device) {
        أرجع عدم;
    }

    // Initialize internal data
    معلومات = (SDL_Video_معلومات *)SDL_calloc(1, حجم(SDL_Video_معلومات));
    إذا (!معلومات) {
        SDL_free(device);
        أرجع عدم;
    }

    device->دننی = معلومات;

    // Set the function pointers
    device->VideoInit = RISCOS_VideoInit;
    device->VideoQuit = RISCOS_VideoQuit;
    device->PumpEvents = RISCOS_PumpEvents;

    device->GetDisplayModes = RISCOS_GetDisplayModes;
    device->سېټ_Display_ډېرپېښ = RISCOS_سېټ_Display_ډېرپېښ;

    device->CreateSDLWindow = RISCOS_Create_کړکۍ;
    device->Destroy_کړکۍ = RISCOS_Destroy_کړکۍ;

    device->Create_کړکۍ_Framebuffer = RISCOS_Create_کړکۍ_Framebuffer;
    device->Update_کړکۍ_Framebuffer = RISCOS_Update_کړکۍ_Framebuffer;
    device->Destroy_کړکۍ_Framebuffer = RISCOS_Destroy_کړکۍ_Framebuffer;

    device->حرر = RISCOS_DeleteDevice;

    // TODO: Support windowed mode
    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    أرجع device;
}

VideoBootStrap RISCOS_bootstrap = {
    RISCOSVID_DRIVER_NAME, "SDL RISC OS video driver",
    RISCOS_CreateDevice,
    RISCOS_Show_پیغام_Box,
    false
};

ساكن bool RISCOS_VideoInit(SDL_VideoDevice *_this)
{
    إذا (!RISCOS_InitEvents(_this)) {
        أرجع false;
    }

    إذا (!RISCOS_InitMouse(_this)) {
        أرجع false;
    }

    // Assume we have a mouse and keyboard
    SDL_جمع_کړه_Keyboard(SDL_DEFAULT_KEYBOARD_ID, عدم);
    SDL_جمع_کړه_Mouse(SDL_DEFAULT_MOUSE_ID, عدم);

    إذا (!RISCOS_InitModes(_this)) {
        أرجع false;
    }

    // We're done!
    أرجع true;
}

ساكن فراغ RISCOS_VideoQuit(SDL_VideoDevice *_this)
{
    RISCOS_QuitEvents(_this);
}

#د_که_پای // SDL_VIDEO_DRIVER_RISCOS
