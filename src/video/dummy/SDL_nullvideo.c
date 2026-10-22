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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

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

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../SDL_pixels_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"
#ifdef SDL_ಒಳಹರಿವು_LINUXEV
#ಅನ್ತರ್ಭಾವ "../../core/linux/SDL_evdev.h"
#endif

#ಅನ್ತರ್ಭಾವ "SDL_nullvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_nullevents_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_nullframebuffer_c.h"

#define DUMMYVID_DRIVER_NAME       "dummy"
#define DUMMYVID_DRIVER_EVDEV_NAME "evdev"

// Initialization/Query functions
ಸ್ಥಿರ bool DUMMY_VideoInitCommon(SDL_VideoDevice *_this);
ಸ್ಥಿರ bool DUMMY_VideoInit(SDL_VideoDevice *_this);
ಸ್ಥಿರ ಶೂನ್ಯ DUMMY_VideoQuit(SDL_VideoDevice *_this);
#ifdef SDL_ಒಳಹರಿವು_LINUXEV
ಸ್ಥಿರ bool DUMMY_EVDEV_VideoInit(SDL_VideoDevice *_this);
ಸ್ಥಿರ ಶೂನ್ಯ DUMMY_EVDEV_VideoQuit(SDL_VideoDevice *_this);
#endif

ಸ್ಥಿರ bool DUMMY_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, window->pending.x, window->pending.y);
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ DUMMY_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->pending.w, window->pending.h);
}

// DUMMY driver bootstrap functions

ಸ್ಥಿರ bool DUMMY_Available(ಧ್ರುವ ವರ್ಣ *drivername)
{
    ಧ್ರುವ ವರ್ಣ *hint = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    ಯದಿ (hint && SDL_strstr(hint, drivername) != ರಿಕ್ತ) {
        ಪ್ರತ್ಯಾಗಮ true;
    }
    ಪ್ರತ್ಯಾಗಮ false;
}

ಸ್ಥಿರ ಶೂನ್ಯ DUMMY_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

ಸ್ಥಿರ SDL_VideoDevice *DUMMY_InternalCreateDevice(ಧ್ರುವ ವರ್ಣ *enable_hint)
{
    SDL_VideoDevice *device;

    ಯದಿ (!DUMMY_Available(enable_hint)) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, ಪರಿಮಾಣ(SDL_VideoDevice));
    ಯದಿ (!device) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
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
    device->ಮುಕ್ತ = DUMMY_DeleteDevice;

    ಪ್ರತ್ಯಾಗಮ device;
}

ಸ್ಥಿರ SDL_VideoDevice *DUMMY_CreateDevice(ಶೂನ್ಯ)
{
    ಪ್ರತ್ಯಾಗಮ DUMMY_InternalCreateDevice(DUMMYVID_DRIVER_NAME);
}

VideoBootStrap DUMMY_bootstrap = {
    DUMMYVID_DRIVER_NAME, "SDL dummy video driver",
    DUMMY_CreateDevice,
    ರಿಕ್ತ, // no ShowMessageBox implementation
    false
};

#ifdef SDL_ಒಳಹರಿವು_LINUXEV

ಸ್ಥಿರ bool DUMMY_EVDEV_VideoInit(SDL_VideoDevice *_this)
{
    ಯದಿ (!DUMMY_VideoInitCommon(_this)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    SDL_EVDEV_Init();
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ DUMMY_EVDEV_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_EVDEV_Quit();
}

ಸ್ಥಿರ ಶೂನ್ಯ DUMMY_EVDEV_Poll(SDL_VideoDevice *_this)
{
    (ಶೂನ್ಯ)_this;
    SDL_EVDEV_Poll();
}

ಸ್ಥಿರ SDL_VideoDevice *DUMMY_EVDEV_CreateDevice(ಶೂನ್ಯ)
{
    SDL_VideoDevice *device = DUMMY_InternalCreateDevice(DUMMYVID_DRIVER_EVDEV_NAME);
    ಯದಿ (device) {
        device->VideoInit = DUMMY_EVDEV_VideoInit;
        device->VideoQuit = DUMMY_EVDEV_VideoQuit;
        device->PumpEvents = DUMMY_EVDEV_Poll;
    }
    ಪ್ರತ್ಯಾಗಮ device;
}

VideoBootStrap DUMMY_evdev_bootstrap = {
    DUMMYVID_DRIVER_EVDEV_NAME, "SDL dummy video driver with evdev",
    DUMMY_EVDEV_CreateDevice,
    ರಿಕ್ತ, // no ShowMessageBox implementation
    false
};

#endif // SDL_INPUT_LINUXEV

ಸ್ಥಿರ bool DUMMY_SetRelativeMouseMode(bool enabled)
{
    ಪ್ರತ್ಯಾಗಮ true;
}

bool DUMMY_VideoInitCommon(SDL_VideoDevice *_this)
{
    SDL_DisplayMode mode;

    // Use a fake 32-bpp desktop mode
    SDL_zero(mode);
    mode.format = SDL_PIXELFORMAT_XRGB8888;
    mode.w = 1024;
    mode.h = 768;
    ಯದಿ (SDL_AddBasicVideoDisplay(&mode) == 0) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

bool DUMMY_VideoInit(SDL_VideoDevice *_this)
{
    ಯದಿ (!DUMMY_VideoInitCommon(_this)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    SDL_GetMouse()->SetRelativeMouseMode = DUMMY_SetRelativeMouseMode;
    ಪ್ರತ್ಯಾಗಮ true;
}

ಶೂನ್ಯ DUMMY_VideoQuit(SDL_VideoDevice *_this)
{
}

#endif // SDL_VIDEO_DRIVER_DUMMY
