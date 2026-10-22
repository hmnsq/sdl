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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_DUMMY

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
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_ಒಳಹರಿವು_LINUXEV
#ಅನ್ತರ್ಭಾವ "../../core/linux/SDL_evdev.h"
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ "SDL_nullvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_nullevents_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_nullframebuffer_c.h"

#ವ್ಯಾಖ್ಯಾನಿಸು DUMMYVID_DRIVER_NAME       "dummy"
#ವ್ಯಾಖ್ಯಾನಿಸು DUMMYVID_DRIVER_EVDEV_NAME "evdev"

// Initialization/Query functions
ಸ್ಥಿರ bool DUMMY_VideoInitCommon(SDL_VideoDevice *_this);
ಸ್ಥಿರ bool DUMMY_VideoInit(SDL_VideoDevice *_this);
ಸ್ಥಿರ ಶೂನ್ಯ DUMMY_VideoQuit(SDL_VideoDevice *_this);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_ಒಳಹರಿವು_LINUXEV
ಸ್ಥಿರ bool DUMMY_EVDEV_VideoInit(SDL_VideoDevice *_this);
ಸ್ಥಿರ ಶೂನ್ಯ DUMMY_EVDEV_VideoQuit(SDL_VideoDevice *_this);
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ bool DUMMY_ಗಣ_ಕಿಟಕಿ_Position(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_MOVED, ಕಿಟಕಿ->pending.x, ಕಿಟಕಿ->pending.y);
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ DUMMY_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_RESIZED, ಕಿಟಕಿ->pending.w, ಕಿಟಕಿ->pending.h);
}

// DUMMY driver bootstrap functions

ಸ್ಥಿರ bool DUMMY_ಲಭ್ಯ(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *drivername)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *hint = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    ಆದರೆ (hint && SDL_strstr(hint, drivername) != ಖಾಲಿ) {
        ಹಿಂತಿರುಗಿ true;
    }
    ಹಿಂತಿರುಗಿ false;
}

ಸ್ಥಿರ ಶೂನ್ಯ DUMMY_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

ಸ್ಥಿರ SDL_VideoDevice *DUMMY_ಆಂತರಿಕ_Create_Device(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *enable_hint)
{
    SDL_VideoDevice *device;

    ಆದರೆ (!DUMMY_ಲಭ್ಯ(enable_hint)) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, ಗಾತ್ರ(SDL_VideoDevice));
    ಆದರೆ (!device) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    // Set the function pointers
    device->VideoInit = DUMMY_VideoInit;
    device->VideoQuit = DUMMY_VideoQuit;
    device->PumpEvents = DUMMY_PumpEvents;
    device->ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ = DUMMY_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ;
    device->ಗಣ_ಕಿಟಕಿ_Position = DUMMY_ಗಣ_ಕಿಟಕಿ_Position;
    device->Create_ಕಿಟಕಿ_Framebuffer = SDL_DUMMY_Create_ಕಿಟಕಿ_Framebuffer;
    device->Update_ಕಿಟಕಿ_Framebuffer = SDL_DUMMY_Update_ಕಿಟಕಿ_Framebuffer;
    device->Destroy_ಕಿಟಕಿ_Framebuffer = SDL_DUMMY_Destroy_ಕಿಟಕಿ_Framebuffer;
    device->ಬಿಡುಗಡೆ = DUMMY_DeleteDevice;

    ಹಿಂತಿರುಗಿ device;
}

ಸ್ಥಿರ SDL_VideoDevice *DUMMY_CreateDevice(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ DUMMY_ಆಂತರಿಕ_Create_Device(DUMMYVID_DRIVER_NAME);
}

VideoBootStrap DUMMY_bootstrap = {
    DUMMYVID_DRIVER_NAME, "SDL dummy video driver",
    DUMMY_CreateDevice,
    ಖಾಲಿ, // no ShowMessageBox implementation
    false
};

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_ಒಳಹರಿವು_LINUXEV

ಸ್ಥಿರ bool DUMMY_EVDEV_VideoInit(SDL_VideoDevice *_this)
{
    ಆದರೆ (!DUMMY_VideoInitCommon(_this)) {
        ಹಿಂತಿರುಗಿ false;
    }

    SDL_EVDEV_Init();
    ಹಿಂತಿರುಗಿ true;
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
    SDL_VideoDevice *device = DUMMY_ಆಂತರಿಕ_Create_Device(DUMMYVID_DRIVER_EVDEV_NAME);
    ಆದರೆ (device) {
        device->VideoInit = DUMMY_EVDEV_VideoInit;
        device->VideoQuit = DUMMY_EVDEV_VideoQuit;
        device->PumpEvents = DUMMY_EVDEV_Poll;
    }
    ಹಿಂತಿರುಗಿ device;
}

VideoBootStrap DUMMY_evdev_bootstrap = {
    DUMMYVID_DRIVER_EVDEV_NAME, "SDL dummy video driver with evdev",
    DUMMY_EVDEV_CreateDevice,
    ಖಾಲಿ, // no ShowMessageBox implementation
    false
};

#ಆದರೆ_ಅಂತ್ಯ // SDL_INPUT_LINUXEV

ಸ್ಥಿರ bool DUMMY_ಗಣ_Relative_Mouse_ಬಹುಲಕ(bool enabled)
{
    ಹಿಂತಿರುಗಿ true;
}

bool DUMMY_VideoInitCommon(SDL_VideoDevice *_this)
{
    SDL_Display_ಬಹುಲಕ ಬಹುಲಕ;

    // Use a fake 32-bpp desktop mode
    SDL_zero(ಬಹುಲಕ);
    ಬಹುಲಕ.format = SDL_PIXELFORMAT_XRGB8888;
    ಬಹುಲಕ.w = 1024;
    ಬಹುಲಕ.h = 768;
    ಆದರೆ (SDL_ಕೂಡಿಸು_Basic_Video_Display(&ಬಹುಲಕ) == 0) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಹಿಂತಿರುಗಿ true;
}

bool DUMMY_VideoInit(SDL_VideoDevice *_this)
{
    ಆದರೆ (!DUMMY_VideoInitCommon(_this)) {
        ಹಿಂತಿರುಗಿ false;
    }

    SDL_GetMouse()->ಗಣ_Relative_Mouse_ಬಹುಲಕ = DUMMY_ಗಣ_Relative_Mouse_ಬಹುಲಕ;
    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ DUMMY_VideoQuit(SDL_VideoDevice *_this)
{
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_DUMMY
