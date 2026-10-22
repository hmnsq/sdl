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

#அந்தர்பாவ "../SDL_sysvideo.h"
#அந்தர்பாவ "../SDL_pixels_c.h"
#அந்தர்பாவ "../../events/SDL_events_c.h"
#ifdef SDL_உள்ளீடு_LINUXEV
#அந்தர்பாவ "../../core/linux/SDL_evdev.h"
#endif

#அந்தர்பாவ "SDL_nullvideo.h"
#அந்தர்பாவ "SDL_nullevents_c.h"
#அந்தர்பாவ "SDL_nullframebuffer_c.h"

#define DUMMYVID_DRIVER_NAME       "dummy"
#define DUMMYVID_DRIVER_EVDEV_NAME "evdev"

// Initialization/Query functions
நிலையான bool DUMMY_VideoInitCommon(SDL_VideoDevice *_this);
நிலையான bool DUMMY_VideoInit(SDL_VideoDevice *_this);
நிலையான வெறுமை DUMMY_VideoQuit(SDL_VideoDevice *_this);
#ifdef SDL_உள்ளீடு_LINUXEV
நிலையான bool DUMMY_EVDEV_VideoInit(SDL_VideoDevice *_this);
நிலையான வெறுமை DUMMY_EVDEV_VideoQuit(SDL_VideoDevice *_this);
#endif

நிலையான bool DUMMY_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, window->pending.x, window->pending.y);
    திரும்பு true;
}

நிலையான வெறுமை DUMMY_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->pending.w, window->pending.h);
}

// DUMMY driver bootstrap functions

நிலையான bool DUMMY_Available(மாறிலி எழுத்து *drivername)
{
    மாறிலி எழுத்து *hint = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    எனில் (hint && SDL_strstr(hint, drivername) != வெற்று) {
        திரும்பு true;
    }
    திரும்பு false;
}

நிலையான வெறுமை DUMMY_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

நிலையான SDL_VideoDevice *DUMMY_InternalCreateDevice(மாறிலி எழுத்து *enable_hint)
{
    SDL_VideoDevice *device;

    எனில் (!DUMMY_Available(enable_hint)) {
        திரும்பு வெற்று;
    }

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, அளவு(SDL_VideoDevice));
    எனில் (!device) {
        திரும்பு வெற்று;
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
    device->விடுவி = DUMMY_DeleteDevice;

    திரும்பு device;
}

நிலையான SDL_VideoDevice *DUMMY_CreateDevice(வெறுமை)
{
    திரும்பு DUMMY_InternalCreateDevice(DUMMYVID_DRIVER_NAME);
}

VideoBootStrap DUMMY_bootstrap = {
    DUMMYVID_DRIVER_NAME, "SDL dummy video driver",
    DUMMY_CreateDevice,
    வெற்று, // no ShowMessageBox implementation
    false
};

#ifdef SDL_உள்ளீடு_LINUXEV

நிலையான bool DUMMY_EVDEV_VideoInit(SDL_VideoDevice *_this)
{
    எனில் (!DUMMY_VideoInitCommon(_this)) {
        திரும்பு false;
    }

    SDL_EVDEV_Init();
    திரும்பு true;
}

நிலையான வெறுமை DUMMY_EVDEV_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_EVDEV_Quit();
}

நிலையான வெறுமை DUMMY_EVDEV_Poll(SDL_VideoDevice *_this)
{
    (வெறுமை)_this;
    SDL_EVDEV_Poll();
}

நிலையான SDL_VideoDevice *DUMMY_EVDEV_CreateDevice(வெறுமை)
{
    SDL_VideoDevice *device = DUMMY_InternalCreateDevice(DUMMYVID_DRIVER_EVDEV_NAME);
    எனில் (device) {
        device->VideoInit = DUMMY_EVDEV_VideoInit;
        device->VideoQuit = DUMMY_EVDEV_VideoQuit;
        device->PumpEvents = DUMMY_EVDEV_Poll;
    }
    திரும்பு device;
}

VideoBootStrap DUMMY_evdev_bootstrap = {
    DUMMYVID_DRIVER_EVDEV_NAME, "SDL dummy video driver with evdev",
    DUMMY_EVDEV_CreateDevice,
    வெற்று, // no ShowMessageBox implementation
    false
};

#endif // SDL_INPUT_LINUXEV

நிலையான bool DUMMY_SetRelativeMouseMode(bool enabled)
{
    திரும்பு true;
}

bool DUMMY_VideoInitCommon(SDL_VideoDevice *_this)
{
    SDL_DisplayMode mode;

    // Use a fake 32-bpp desktop mode
    SDL_zero(mode);
    mode.format = SDL_PIXELFORMAT_XRGB8888;
    mode.w = 1024;
    mode.h = 768;
    எனில் (SDL_AddBasicVideoDisplay(&mode) == 0) {
        திரும்பு false;
    }

    திரும்பு true;
}

bool DUMMY_VideoInit(SDL_VideoDevice *_this)
{
    எனில் (!DUMMY_VideoInitCommon(_this)) {
        திரும்பு false;
    }

    SDL_GetMouse()->SetRelativeMouseMode = DUMMY_SetRelativeMouseMode;
    திரும்பு true;
}

வெறுமை DUMMY_VideoQuit(SDL_VideoDevice *_this)
{
}

#endif // SDL_VIDEO_DRIVER_DUMMY
