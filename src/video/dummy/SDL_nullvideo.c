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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_DUMMY

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
#جے_تعریف_شدہ SDL_داخلہ_LINUXEV
#ضمن "../../core/linux/SDL_evdev.h"
#جے_انت

#ضمن "SDL_nullvideo.h"
#ضمن "SDL_nullevents_c.h"
#ضمن "SDL_nullframebuffer_c.h"

#تعریف_کرو DUMMYVID_DRIVER_NAME       "dummy"
#تعریف_کرو DUMMYVID_DRIVER_EVDEV_NAME "evdev"

// Initialization/Query functions
ساكن bool DUMMY_VideoInitCommon(SDL_VideoDevice *_this);
ساكن bool DUMMY_VideoInit(SDL_VideoDevice *_this);
ساكن فراغ DUMMY_VideoQuit(SDL_VideoDevice *_this);
#جے_تعریف_شدہ SDL_داخلہ_LINUXEV
ساكن bool DUMMY_EVDEV_VideoInit(SDL_VideoDevice *_this);
ساكن فراغ DUMMY_EVDEV_VideoQuit(SDL_VideoDevice *_this);
#جے_انت

ساكن bool DUMMY_سیٹ_کھڑکی_Position(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_MOVED, کھڑکی->pending.x, کھڑکی->pending.y);
    أرجع true;
}

ساكن فراغ DUMMY_سیٹ_کھڑکی_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESIZED, کھڑکی->pending.w, کھڑکی->pending.h);
}

// DUMMY driver bootstrap functions

ساكن bool DUMMY_دستیاب(ثابت حرف *drivername)
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

ساكن SDL_VideoDevice *DUMMY_اندرونی_Create_Device(ثابت حرف *enable_hint)
{
    SDL_VideoDevice *device;

    إذا (!DUMMY_دستیاب(enable_hint)) {
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
    device->سیٹ_کھڑکی_ناپ = DUMMY_سیٹ_کھڑکی_ناپ;
    device->سیٹ_کھڑکی_Position = DUMMY_سیٹ_کھڑکی_Position;
    device->Create_کھڑکی_Framebuffer = SDL_DUMMY_Create_کھڑکی_Framebuffer;
    device->Update_کھڑکی_Framebuffer = SDL_DUMMY_Update_کھڑکی_Framebuffer;
    device->Destroy_کھڑکی_Framebuffer = SDL_DUMMY_Destroy_کھڑکی_Framebuffer;
    device->حرر = DUMMY_DeleteDevice;

    أرجع device;
}

ساكن SDL_VideoDevice *DUMMY_CreateDevice(فراغ)
{
    أرجع DUMMY_اندرونی_Create_Device(DUMMYVID_DRIVER_NAME);
}

VideoBootStrap DUMMY_bootstrap = {
    DUMMYVID_DRIVER_NAME, "SDL dummy video driver",
    DUMMY_CreateDevice,
    عدم, // no ShowMessageBox implementation
    false
};

#جے_تعریف_شدہ SDL_داخلہ_LINUXEV

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
    SDL_VideoDevice *device = DUMMY_اندرونی_Create_Device(DUMMYVID_DRIVER_EVDEV_NAME);
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

#جے_انت // SDL_INPUT_LINUXEV

ساكن bool DUMMY_سیٹ_Relative_Mouse_منوال(bool enabled)
{
    أرجع true;
}

bool DUMMY_VideoInitCommon(SDL_VideoDevice *_this)
{
    SDL_Display_منوال منوال;

    // Use a fake 32-bpp desktop mode
    SDL_zero(منوال);
    منوال.format = SDL_PIXELFORMAT_XRGB8888;
    منوال.w = 1024;
    منوال.h = 768;
    إذا (SDL_جوڑو_Basic_Video_Display(&منوال) == 0) {
        أرجع false;
    }

    أرجع true;
}

bool DUMMY_VideoInit(SDL_VideoDevice *_this)
{
    إذا (!DUMMY_VideoInitCommon(_this)) {
        أرجع false;
    }

    SDL_GetMouse()->سیٹ_Relative_Mouse_منوال = DUMMY_سیٹ_Relative_Mouse_منوال;
    أرجع true;
}

فراغ DUMMY_VideoQuit(SDL_VideoDevice *_this)
{
}

#جے_انت // SDL_VIDEO_DRIVER_DUMMY
