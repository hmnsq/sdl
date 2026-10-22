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
#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_RISCOS

#അന്തര്ഭാവ "../SDL_sysvideo.h"
#അന്തര്ഭാവ "../SDL_pixels_c.h"
#അന്തര്ഭാവ "../../events/SDL_events_c.h"
#അന്തര്ഭാവ "../../events/SDL_keyboard_c.h"
#അന്തര്ഭാവ "../../events/SDL_mouse_c.h"

#അന്തര്ഭാവ "SDL_riscosvideo.h"
#അന്തര്ഭാവ "SDL_riscosevents_c.h"
#അന്തര്ഭാവ "SDL_riscosframebuffer_c.h"
#അന്തര്ഭാവ "SDL_riscosmouse.h"
#അന്തര്ഭാവ "SDL_riscosmodes.h"
#അന്തര്ഭാവ "SDL_riscoswindow.h"
#അന്തര്ഭാവ "SDL_riscosmessagebox.h"

#define RISCOSVID_DRIVER_NAME "riscos"

// Initialization/Query functions
സ്ഥിതം bool RISCOS_VideoInit(SDL_VideoDevice *_this);
സ്ഥിതം ശൂന്യം RISCOS_VideoQuit(SDL_VideoDevice *_this);

// RISC OS driver bootstrap functions

സ്ഥിതം ശൂന്യം RISCOS_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

സ്ഥിതം SDL_VideoDevice *RISCOS_CreateDevice(ശൂന്യം)
{
    SDL_VideoDevice *device;
    SDL_VideoData *data;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, വലുപ്പം(SDL_VideoDevice));
    എങ്കിൽ (!device) {
        തിരികെ ശൂന്യ;
    }

    // Initialize internal data
    data = (SDL_VideoData *)SDL_calloc(1, വലുപ്പം(SDL_VideoData));
    എങ്കിൽ (!data) {
        SDL_free(device);
        തിരികെ ശൂന്യ;
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

    device->സ്വതന്ത്രം = RISCOS_DeleteDevice;

    // TODO: Support windowed mode
    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    തിരികെ device;
}

VideoBootStrap RISCOS_bootstrap = {
    RISCOSVID_DRIVER_NAME, "SDL RISC OS video driver",
    RISCOS_CreateDevice,
    RISCOS_ShowMessageBox,
    false
};

സ്ഥിതം bool RISCOS_VideoInit(SDL_VideoDevice *_this)
{
    എങ്കിൽ (!RISCOS_InitEvents(_this)) {
        തിരികെ false;
    }

    എങ്കിൽ (!RISCOS_InitMouse(_this)) {
        തിരികെ false;
    }

    // Assume we have a mouse and keyboard
    SDL_AddKeyboard(SDL_DEFAULT_KEYBOARD_ID, ശൂന്യ);
    SDL_AddMouse(SDL_DEFAULT_MOUSE_ID, ശൂന്യ);

    എങ്കിൽ (!RISCOS_InitModes(_this)) {
        തിരികെ false;
    }

    // We're done!
    തിരികെ true;
}

സ്ഥിതം ശൂന്യം RISCOS_VideoQuit(SDL_VideoDevice *_this)
{
    RISCOS_QuitEvents(_this);
}

#endif // SDL_VIDEO_DRIVER_RISCOS
