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

#ଅନ୍ତର୍ଭାଵ "../SDL_sysvideo.h"
#ଅନ୍ତର୍ଭାଵ "../SDL_pixels_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_events_c.h"
#ifdef SDL_ନିବେଶ_LINUXEV
#ଅନ୍ତର୍ଭାଵ "../../core/linux/SDL_evdev.h"
#endif

#ଅନ୍ତର୍ଭାଵ "SDL_nullvideo.h"
#ଅନ୍ତର୍ଭାଵ "SDL_nullevents_c.h"
#ଅନ୍ତର୍ଭାଵ "SDL_nullframebuffer_c.h"

#define DUMMYVID_DRIVER_NAME       "dummy"
#define DUMMYVID_DRIVER_EVDEV_NAME "evdev"

// Initialization/Query functions
ସ୍ଥିର bool DUMMY_VideoInitCommon(SDL_VideoDevice *_this);
ସ୍ଥିର bool DUMMY_VideoInit(SDL_VideoDevice *_this);
ସ୍ଥିର ଶୂନ୍ୟ DUMMY_VideoQuit(SDL_VideoDevice *_this);
#ifdef SDL_ନିବେଶ_LINUXEV
ସ୍ଥିର bool DUMMY_EVDEV_VideoInit(SDL_VideoDevice *_this);
ସ୍ଥିର ଶୂନ୍ୟ DUMMY_EVDEV_VideoQuit(SDL_VideoDevice *_this);
#endif

ସ୍ଥିର bool DUMMY_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, window->pending.x, window->pending.y);
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର ଶୂନ୍ୟ DUMMY_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->pending.w, window->pending.h);
}

// DUMMY driver bootstrap functions

ସ୍ଥିର bool DUMMY_Available(ଅଚଳ ଅକ୍ଷର *drivername)
{
    ଅଚଳ ଅକ୍ଷର *hint = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    ଯଦି (hint && SDL_strstr(hint, drivername) != ଖାଲି) {
        ଫେରନ୍ତୁ true;
    }
    ଫେରନ୍ତୁ false;
}

ସ୍ଥିର ଶୂନ୍ୟ DUMMY_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

ସ୍ଥିର SDL_VideoDevice *DUMMY_InternalCreateDevice(ଅଚଳ ଅକ୍ଷର *enable_hint)
{
    SDL_VideoDevice *device;

    ଯଦି (!DUMMY_Available(enable_hint)) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, ଆକାର(SDL_VideoDevice));
    ଯଦି (!device) {
        ଫେରନ୍ତୁ ଖାଲି;
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
    device->ମୁକ୍ତ = DUMMY_DeleteDevice;

    ଫେରନ୍ତୁ device;
}

ସ୍ଥିର SDL_VideoDevice *DUMMY_CreateDevice(ଶୂନ୍ୟ)
{
    ଫେରନ୍ତୁ DUMMY_InternalCreateDevice(DUMMYVID_DRIVER_NAME);
}

VideoBootStrap DUMMY_bootstrap = {
    DUMMYVID_DRIVER_NAME, "SDL dummy video driver",
    DUMMY_CreateDevice,
    ଖାଲି, // no ShowMessageBox implementation
    false
};

#ifdef SDL_ନିବେଶ_LINUXEV

ସ୍ଥିର bool DUMMY_EVDEV_VideoInit(SDL_VideoDevice *_this)
{
    ଯଦି (!DUMMY_VideoInitCommon(_this)) {
        ଫେରନ୍ତୁ false;
    }

    SDL_EVDEV_Init();
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର ଶୂନ୍ୟ DUMMY_EVDEV_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_EVDEV_Quit();
}

ସ୍ଥିର ଶୂନ୍ୟ DUMMY_EVDEV_Poll(SDL_VideoDevice *_this)
{
    (ଶୂନ୍ୟ)_this;
    SDL_EVDEV_Poll();
}

ସ୍ଥିର SDL_VideoDevice *DUMMY_EVDEV_CreateDevice(ଶୂନ୍ୟ)
{
    SDL_VideoDevice *device = DUMMY_InternalCreateDevice(DUMMYVID_DRIVER_EVDEV_NAME);
    ଯଦି (device) {
        device->VideoInit = DUMMY_EVDEV_VideoInit;
        device->VideoQuit = DUMMY_EVDEV_VideoQuit;
        device->PumpEvents = DUMMY_EVDEV_Poll;
    }
    ଫେରନ୍ତୁ device;
}

VideoBootStrap DUMMY_evdev_bootstrap = {
    DUMMYVID_DRIVER_EVDEV_NAME, "SDL dummy video driver with evdev",
    DUMMY_EVDEV_CreateDevice,
    ଖାଲି, // no ShowMessageBox implementation
    false
};

#endif // SDL_INPUT_LINUXEV

ସ୍ଥିର bool DUMMY_SetRelativeMouseMode(bool enabled)
{
    ଫେରନ୍ତୁ true;
}

bool DUMMY_VideoInitCommon(SDL_VideoDevice *_this)
{
    SDL_DisplayMode mode;

    // Use a fake 32-bpp desktop mode
    SDL_zero(mode);
    mode.format = SDL_PIXELFORMAT_XRGB8888;
    mode.w = 1024;
    mode.h = 768;
    ଯଦି (SDL_AddBasicVideoDisplay(&mode) == 0) {
        ଫେରନ୍ତୁ false;
    }

    ଫେରନ୍ତୁ true;
}

bool DUMMY_VideoInit(SDL_VideoDevice *_this)
{
    ଯଦି (!DUMMY_VideoInitCommon(_this)) {
        ଫେରନ୍ତୁ false;
    }

    SDL_GetMouse()->SetRelativeMouseMode = DUMMY_SetRelativeMouseMode;
    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ DUMMY_VideoQuit(SDL_VideoDevice *_this)
{
}

#endif // SDL_VIDEO_DRIVER_DUMMY
