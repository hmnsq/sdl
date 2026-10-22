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
#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_DUMMY

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

#شامل "../SDL_sysvideo.h"
#شامل "../SDL_pixels_c.h"
#شامل "../../events/SDL_events_c.h"
#اگر_تعریف_شدہ SDL_داخلہ_LINUXEV
#شامل "../../core/linux/SDL_evdev.h"
#اگر_ختم

#شامل "SDL_nullvideo.h"
#شامل "SDL_nullevents_c.h"
#شامل "SDL_nullframebuffer_c.h"

#تعریف_کرو DUMMYVID_DRIVER_NAME       "dummy"
#تعریف_کرو DUMMYVID_DRIVER_EVDEV_NAME "evdev"

// Initialization/Query functions
ساکن bool DUMMY_VideoInitCommon(SDL_VideoDevice *_this);
ساکن bool DUMMY_VideoInit(SDL_VideoDevice *_this);
ساکن خالی DUMMY_VideoQuit(SDL_VideoDevice *_this);
#اگر_تعریف_شدہ SDL_داخلہ_LINUXEV
ساکن bool DUMMY_EVDEV_VideoInit(SDL_VideoDevice *_this);
ساکن خالی DUMMY_EVDEV_VideoQuit(SDL_VideoDevice *_this);
#اگر_ختم

ساکن bool DUMMY_سیٹ_کھڑکی_Position(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_MOVED, کھڑکی->pending.x, کھڑکی->pending.y);
    واپس true;
}

ساکن خالی DUMMY_سیٹ_کھڑکی_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESIZED, کھڑکی->pending.w, کھڑکی->pending.h);
}

// DUMMY driver bootstrap functions

ساکن bool DUMMY_دستیاب(ثابت حرف *drivername)
{
    ثابت حرف *hint = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    اگر (hint && SDL_strstr(hint, drivername) != تہی) {
        واپس true;
    }
    واپس false;
}

ساکن خالی DUMMY_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

ساکن SDL_VideoDevice *DUMMY_اندرونی_Create_Device(ثابت حرف *enable_hint)
{
    SDL_VideoDevice *device;

    اگر (!DUMMY_دستیاب(enable_hint)) {
        واپس تہی;
    }

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    اگر (!device) {
        واپس تہی;
    }

    // Set the function pointers
    device->VideoInit = DUMMY_VideoInit;
    device->VideoQuit = DUMMY_VideoQuit;
    device->PumpEvents = DUMMY_PumpEvents;
    device->سیٹ_کھڑکی_سائز = DUMMY_سیٹ_کھڑکی_سائز;
    device->سیٹ_کھڑکی_Position = DUMMY_سیٹ_کھڑکی_Position;
    device->Create_کھڑکی_Framebuffer = SDL_DUMMY_Create_کھڑکی_Framebuffer;
    device->Update_کھڑکی_Framebuffer = SDL_DUMMY_Update_کھڑکی_Framebuffer;
    device->Destroy_کھڑکی_Framebuffer = SDL_DUMMY_Destroy_کھڑکی_Framebuffer;
    device->آزاد = DUMMY_DeleteDevice;

    واپس device;
}

ساکن SDL_VideoDevice *DUMMY_CreateDevice(خالی)
{
    واپس DUMMY_اندرونی_Create_Device(DUMMYVID_DRIVER_NAME);
}

VideoBootStrap DUMMY_bootstrap = {
    DUMMYVID_DRIVER_NAME, "SDL dummy video driver",
    DUMMY_CreateDevice,
    تہی, // no ShowMessageBox implementation
    false
};

#اگر_تعریف_شدہ SDL_داخلہ_LINUXEV

ساکن bool DUMMY_EVDEV_VideoInit(SDL_VideoDevice *_this)
{
    اگر (!DUMMY_VideoInitCommon(_this)) {
        واپس false;
    }

    SDL_EVDEV_Init();
    واپس true;
}

ساکن خالی DUMMY_EVDEV_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_EVDEV_Quit();
}

ساکن خالی DUMMY_EVDEV_Poll(SDL_VideoDevice *_this)
{
    (خالی)_this;
    SDL_EVDEV_Poll();
}

ساکن SDL_VideoDevice *DUMMY_EVDEV_CreateDevice(خالی)
{
    SDL_VideoDevice *device = DUMMY_اندرونی_Create_Device(DUMMYVID_DRIVER_EVDEV_NAME);
    اگر (device) {
        device->VideoInit = DUMMY_EVDEV_VideoInit;
        device->VideoQuit = DUMMY_EVDEV_VideoQuit;
        device->PumpEvents = DUMMY_EVDEV_Poll;
    }
    واپس device;
}

VideoBootStrap DUMMY_evdev_bootstrap = {
    DUMMYVID_DRIVER_EVDEV_NAME, "SDL dummy video driver with evdev",
    DUMMY_EVDEV_CreateDevice,
    تہی, // no ShowMessageBox implementation
    false
};

#اگر_ختم // SDL_INPUT_LINUXEV

ساکن bool DUMMY_سیٹ_Relative_Mouse_منوال(bool enabled)
{
    واپس true;
}

bool DUMMY_VideoInitCommon(SDL_VideoDevice *_this)
{
    SDL_Display_منوال منوال;

    // Use a fake 32-bpp desktop mode
    SDL_zero(منوال);
    منوال.format = SDL_PIXELFORMAT_XRGB8888;
    منوال.w = 1024;
    منوال.h = 768;
    اگر (SDL_جوڑو_Basic_Video_Display(&منوال) == 0) {
        واپس false;
    }

    واپس true;
}

bool DUMMY_VideoInit(SDL_VideoDevice *_this)
{
    اگر (!DUMMY_VideoInitCommon(_this)) {
        واپس false;
    }

    SDL_GetMouse()->سیٹ_Relative_Mouse_منوال = DUMMY_سیٹ_Relative_Mouse_منوال;
    واپس true;
}

خالی DUMMY_VideoQuit(SDL_VideoDevice *_this)
{
}

#اگر_ختم // SDL_VIDEO_DRIVER_DUMMY
