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

#که_تعریف_شوی SDL_VIDEO_DRIVER_DUMMY

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

#ضمن "../SDL_sysvideo.h"
#ضمن "../SDL_pixels_c.h"
#ضمن "../../events/SDL_events_c.h"
#که_تعریف_شوی SDL_ننوت_LINUXEV
#ضمن "../../core/linux/SDL_evdev.h"
#د_که_پای

#ضمن "SDL_nullvideo.h"
#ضمن "SDL_nullevents_c.h"
#ضمن "SDL_nullframebuffer_c.h"

#تعریف_کړه DUMMYVID_DRIVER_NAME       "dummy"
#تعریف_کړه DUMMYVID_DRIVER_EVDEV_NAME "evdev"

// Initialization/Query functions
ساكن bool DUMMY_VideoInitCommon(SDL_VideoDevice *_this);
ساكن bool DUMMY_VideoInit(SDL_VideoDevice *_this);
ساكن فراغ DUMMY_VideoQuit(SDL_VideoDevice *_this);
#که_تعریف_شوی SDL_ننوت_LINUXEV
ساكن bool DUMMY_EVDEV_VideoInit(SDL_VideoDevice *_this);
ساكن فراغ DUMMY_EVDEV_VideoQuit(SDL_VideoDevice *_this);
#د_که_پای

ساكن bool DUMMY_سېټ_کړکۍ_Position(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_MOVED, کړکۍ->pending.x, کړکۍ->pending.y);
    أرجع true;
}

ساكن فراغ DUMMY_سېټ_کړکۍ_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_RESIZED, کړکۍ->pending.w, کړکۍ->pending.h);
}

// DUMMY driver bootstrap functions

ساكن bool DUMMY_شته(ثابت حرف *drivername)
{
    ثابت حرف *hint = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    إذا (hint && SDL_strstr(hint, drivername) != عدم) {
        أرجع true;
    }
    أرجع false;
}

ساكن فراغ DUMMY_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

ساكن SDL_VideoDevice *DUMMY_دننی_Create_Device(ثابت حرف *enable_hint)
{
    SDL_VideoDevice *device;

    إذا (!DUMMY_شته(enable_hint)) {
        أرجع عدم;
    }

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (!device) {
        أرجع عدم;
    }

    // Set the function pointers
    device->VideoInit = DUMMY_VideoInit;
    device->VideoQuit = DUMMY_VideoQuit;
    device->PumpEvents = DUMMY_PumpEvents;
    device->سېټ_کړکۍ_اندازه = DUMMY_سېټ_کړکۍ_اندازه;
    device->سېټ_کړکۍ_Position = DUMMY_سېټ_کړکۍ_Position;
    device->Create_کړکۍ_Framebuffer = SDL_DUMMY_Create_کړکۍ_Framebuffer;
    device->Update_کړکۍ_Framebuffer = SDL_DUMMY_Update_کړکۍ_Framebuffer;
    device->Destroy_کړکۍ_Framebuffer = SDL_DUMMY_Destroy_کړکۍ_Framebuffer;
    device->حرر = DUMMY_DeleteDevice;

    أرجع device;
}

ساكن SDL_VideoDevice *DUMMY_CreateDevice(فراغ)
{
    أرجع DUMMY_دننی_Create_Device(DUMMYVID_DRIVER_NAME);
}

VideoBootStrap DUMMY_bootstrap = {
    DUMMYVID_DRIVER_NAME, "SDL dummy video driver",
    DUMMY_CreateDevice,
    عدم, // no ShowMessageBox implementation
    false
};

#که_تعریف_شوی SDL_ننوت_LINUXEV

ساكن bool DUMMY_EVDEV_VideoInit(SDL_VideoDevice *_this)
{
    إذا (!DUMMY_VideoInitCommon(_this)) {
        أرجع false;
    }

    SDL_EVDEV_Init();
    أرجع true;
}

ساكن فراغ DUMMY_EVDEV_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_EVDEV_Quit();
}

ساكن فراغ DUMMY_EVDEV_Poll(SDL_VideoDevice *_this)
{
    (فراغ)_this;
    SDL_EVDEV_Poll();
}

ساكن SDL_VideoDevice *DUMMY_EVDEV_CreateDevice(فراغ)
{
    SDL_VideoDevice *device = DUMMY_دننی_Create_Device(DUMMYVID_DRIVER_EVDEV_NAME);
    إذا (device) {
        device->VideoInit = DUMMY_EVDEV_VideoInit;
        device->VideoQuit = DUMMY_EVDEV_VideoQuit;
        device->PumpEvents = DUMMY_EVDEV_Poll;
    }
    أرجع device;
}

VideoBootStrap DUMMY_evdev_bootstrap = {
    DUMMYVID_DRIVER_EVDEV_NAME, "SDL dummy video driver with evdev",
    DUMMY_EVDEV_CreateDevice,
    عدم, // no ShowMessageBox implementation
    false
};

#د_که_پای // SDL_INPUT_LINUXEV

ساكن bool DUMMY_سېټ_Relative_Mouse_ډېرپېښ(bool enabled)
{
    أرجع true;
}

bool DUMMY_VideoInitCommon(SDL_VideoDevice *_this)
{
    SDL_Display_ډېرپېښ ډېرپېښ;

    // Use a fake 32-bpp desktop mode
    SDL_zero(ډېرپېښ);
    ډېرپېښ.format = SDL_PIXELFORMAT_XRGB8888;
    ډېرپېښ.w = 1024;
    ډېرپېښ.h = 768;
    إذا (SDL_جمع_کړه_Basic_Video_Display(&ډېرپېښ) == 0) {
        أرجع false;
    }

    أرجع true;
}

bool DUMMY_VideoInit(SDL_VideoDevice *_this)
{
    إذا (!DUMMY_VideoInitCommon(_this)) {
        أرجع false;
    }

    SDL_GetMouse()->سېټ_Relative_Mouse_ډېرپېښ = DUMMY_سېټ_Relative_Mouse_ډېرپېښ;
    أرجع true;
}

فراغ DUMMY_VideoQuit(SDL_VideoDevice *_this)
{
}

#د_که_پای // SDL_VIDEO_DRIVER_DUMMY
