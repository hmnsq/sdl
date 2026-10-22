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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_RISCOS

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_pixels_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_events_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_keyboard_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_riscosvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_riscosevents_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_riscosframebuffer_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_riscosmouse.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_riscosmodes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_riscoswindow.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_riscosmessagebox.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RISCOSVID_DRIVER_NAME "riscos"

// Initialization/Query functions
ਸਥਿਰ bool RISCOS_VideoInit(SDL_VideoDevice *_this);
ਸਥਿਰ ਖਾਲੀ RISCOS_VideoQuit(SDL_VideoDevice *_this);

// RISC OS driver bootstrap functions

ਸਥਿਰ ਖਾਲੀ RISCOS_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->ਅੰਦਰੂਨੀ);
    SDL_free(device);
}

ਸਥਿਰ SDL_VideoDevice *RISCOS_CreateDevice(ਖਾਲੀ)
{
    SDL_VideoDevice *device;
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, ਆਕਾਰ(SDL_VideoDevice));
    ਜੇ (!device) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    // Initialize internal data
    ਅੰਕੜੇ = (SDL_Video_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(SDL_Video_ਅੰਕੜੇ));
    ਜੇ (!ਅੰਕੜੇ) {
        SDL_free(device);
        ਵਾਪਸ ਨਿਰਾ;
    }

    device->ਅੰਦਰੂਨੀ = ਅੰਕੜੇ;

    // Set the function pointers
    device->VideoInit = RISCOS_VideoInit;
    device->VideoQuit = RISCOS_VideoQuit;
    device->PumpEvents = RISCOS_PumpEvents;

    device->GetDisplayModes = RISCOS_GetDisplayModes;
    device->ਸੈੱਟ_Display_ਬਹੁਲਕ = RISCOS_ਸੈੱਟ_Display_ਬਹੁਲਕ;

    device->CreateSDLWindow = RISCOS_Create_ਖਿੜਕੀ;
    device->Destroy_ਖਿੜਕੀ = RISCOS_Destroy_ਖਿੜਕੀ;

    device->Create_ਖਿੜਕੀ_Framebuffer = RISCOS_Create_ਖਿੜਕੀ_Framebuffer;
    device->Update_ਖਿੜਕੀ_Framebuffer = RISCOS_Update_ਖਿੜਕੀ_Framebuffer;
    device->Destroy_ਖਿੜਕੀ_Framebuffer = RISCOS_Destroy_ਖਿੜਕੀ_Framebuffer;

    device->ਮੁਕਤ = RISCOS_DeleteDevice;

    // TODO: Support windowed mode
    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    ਵਾਪਸ device;
}

VideoBootStrap RISCOS_bootstrap = {
    RISCOSVID_DRIVER_NAME, "SDL RISC OS video driver",
    RISCOS_CreateDevice,
    RISCOS_Show_ਸੁਨੇਹਾ_Box,
    false
};

ਸਥਿਰ bool RISCOS_VideoInit(SDL_VideoDevice *_this)
{
    ਜੇ (!RISCOS_InitEvents(_this)) {
        ਵਾਪਸ false;
    }

    ਜੇ (!RISCOS_InitMouse(_this)) {
        ਵਾਪਸ false;
    }

    // Assume we have a mouse and keyboard
    SDL_ਜੋੜੋ_Keyboard(SDL_DEFAULT_KEYBOARD_ID, ਨਿਰਾ);
    SDL_ਜੋੜੋ_Mouse(SDL_DEFAULT_MOUSE_ID, ਨਿਰਾ);

    ਜੇ (!RISCOS_InitModes(_this)) {
        ਵਾਪਸ false;
    }

    // We're done!
    ਵਾਪਸ true;
}

ਸਥਿਰ ਖਾਲੀ RISCOS_VideoQuit(SDL_VideoDevice *_this)
{
    RISCOS_QuitEvents(_this);
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_RISCOS
