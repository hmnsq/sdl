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

#ifdef SDL_VIDEO_DRIVER_DUMMY

/* Dummy SDL video driver implementation; this is just enough to make an
 *  SDL-based application THINK it's got a working video driver, for
 *  applications that call SDL_Init(SDL_INIT_VIDEO) when they don't need it,
 *  and also for use as a collection of stubs when porting SDL to a new
 *  platform for which you haven't yet written a valid video driver.
 *
 * This is also a great way to determine bottlenecks: if you think that SDL
 *  is a performance problem for a given platform, enable this driver, and
 *  then see if your application runs faster without video overhead.
 *
 * Initial work by Ryan C. Gordon (icculus@icculus.org). A good portion
 *  of this was cut-and-pasted from Stephane Peter's work in the AAlib
 *  SDL video driver.  Renamed to "DUMMY" by Sam Lantinga.
 */

#അന്തര്ഭാവ "../SDL_sysvideo.h"
#അന്തര്ഭാവ "../SDL_pixels_c.h"
#അന്തര്ഭാവ "../../events/SDL_events_c.h"
#ifdef SDL_നിവേശം_LINUXEV
#അന്തര്ഭാവ "../../core/linux/SDL_evdev.h"
#endif

#അന്തര്ഭാവ "SDL_nullvideo.h"
#അന്തര്ഭാവ "SDL_nullevents_c.h"
#അന്തര്ഭാവ "SDL_nullframebuffer_c.h"

#define DUMMYVID_DRIVER_NAME       "dummy"
#define DUMMYVID_DRIVER_EVDEV_NAME "evdev"

// Initialization/Query functions
സ്ഥിതം bool DUMMY_VideoInitCommon(SDL_VideoDevice *_this);
സ്ഥിതം bool DUMMY_VideoInit(SDL_VideoDevice *_this);
സ്ഥിതം ശൂന്യം DUMMY_VideoQuit(SDL_VideoDevice *_this);
#ifdef SDL_നിവേശം_LINUXEV
സ്ഥിതം bool DUMMY_EVDEV_VideoInit(SDL_VideoDevice *_this);
സ്ഥിതം ശൂന്യം DUMMY_EVDEV_VideoQuit(SDL_VideoDevice *_this);
#endif

സ്ഥിതം bool DUMMY_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, window->pending.x, window->pending.y);
    തിരികെ true;
}

സ്ഥിതം ശൂന്യം DUMMY_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->pending.w, window->pending.h);
}

// DUMMY driver bootstrap functions

സ്ഥിതം bool DUMMY_Available(സ്ഥിരം അക്ഷരം *drivername)
{
    സ്ഥിരം അക്ഷരം *hint = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    എങ്കിൽ (hint && SDL_strstr(hint, drivername) != ശൂന്യ) {
        തിരികെ true;
    }
    തിരികെ false;
}

സ്ഥിതം ശൂന്യം DUMMY_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

സ്ഥിതം SDL_VideoDevice *DUMMY_InternalCreateDevice(സ്ഥിരം അക്ഷരം *enable_hint)
{
    SDL_VideoDevice *device;

    എങ്കിൽ (!DUMMY_Available(enable_hint)) {
        തിരികെ ശൂന്യ;
    }

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, വലുപ്പം(SDL_VideoDevice));
    എങ്കിൽ (!device) {
        തിരികെ ശൂന്യ;
    }

    // Set the function pointers
    device->VideoInit = DUMMY_VideoInit;
    device->VideoQuit = DUMMY_VideoQuit;
    device->PumpEvents = DUMMY_PumpEvents;
    device->SetWindowSize = DUMMY_SetWindowSize;
    device->SetWindowPosition = DUMMY_SetWindowPosition;
    device->CreateWindowFramebuffer = SDL_DUMMY_CreateWindowFramebuffer;
    device->UpdateWindowFramebuffer = SDL_DUMMY_UpdateWindowFramebuffer;
    device->DestroyWindowFramebuffer = SDL_DUMMY_DestroyWindowFramebuffer;
    device->സ്വതന്ത്രം = DUMMY_DeleteDevice;

    തിരികെ device;
}

സ്ഥിതം SDL_VideoDevice *DUMMY_CreateDevice(ശൂന്യം)
{
    തിരികെ DUMMY_InternalCreateDevice(DUMMYVID_DRIVER_NAME);
}

VideoBootStrap DUMMY_bootstrap = {
    DUMMYVID_DRIVER_NAME, "SDL dummy video driver",
    DUMMY_CreateDevice,
    ശൂന്യ, // no ShowMessageBox implementation
    false
};

#ifdef SDL_നിവേശം_LINUXEV

സ്ഥിതം bool DUMMY_EVDEV_VideoInit(SDL_VideoDevice *_this)
{
    എങ്കിൽ (!DUMMY_VideoInitCommon(_this)) {
        തിരികെ false;
    }

    SDL_EVDEV_Init();
    തിരികെ true;
}

സ്ഥിതം ശൂന്യം DUMMY_EVDEV_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_EVDEV_Quit();
}

സ്ഥിതം ശൂന്യം DUMMY_EVDEV_Poll(SDL_VideoDevice *_this)
{
    (ശൂന്യം)_this;
    SDL_EVDEV_Poll();
}

സ്ഥിതം SDL_VideoDevice *DUMMY_EVDEV_CreateDevice(ശൂന്യം)
{
    SDL_VideoDevice *device = DUMMY_InternalCreateDevice(DUMMYVID_DRIVER_EVDEV_NAME);
    എങ്കിൽ (device) {
        device->VideoInit = DUMMY_EVDEV_VideoInit;
        device->VideoQuit = DUMMY_EVDEV_VideoQuit;
        device->PumpEvents = DUMMY_EVDEV_Poll;
    }
    തിരികെ device;
}

VideoBootStrap DUMMY_evdev_bootstrap = {
    DUMMYVID_DRIVER_EVDEV_NAME, "SDL dummy video driver with evdev",
    DUMMY_EVDEV_CreateDevice,
    ശൂന്യ, // no ShowMessageBox implementation
    false
};

#endif // SDL_INPUT_LINUXEV

സ്ഥിതം bool DUMMY_SetRelativeMouseMode(bool enabled)
{
    തിരികെ true;
}

bool DUMMY_VideoInitCommon(SDL_VideoDevice *_this)
{
    SDL_DisplayMode mode;

    // Use a fake 32-bpp desktop mode
    SDL_zero(mode);
    mode.format = SDL_PIXELFORMAT_XRGB8888;
    mode.w = 1024;
    mode.h = 768;
    എങ്കിൽ (SDL_AddBasicVideoDisplay(&mode) == 0) {
        തിരികെ false;
    }

    തിരികെ true;
}

bool DUMMY_VideoInit(SDL_VideoDevice *_this)
{
    എങ്കിൽ (!DUMMY_VideoInitCommon(_this)) {
        തിരികെ false;
    }

    SDL_GetMouse()->SetRelativeMouseMode = DUMMY_SetRelativeMouseMode;
    തിരികെ true;
}

ശൂന്യം DUMMY_VideoQuit(SDL_VideoDevice *_this)
{
}

#endif // SDL_VIDEO_DRIVER_DUMMY
