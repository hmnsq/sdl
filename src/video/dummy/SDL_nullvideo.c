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

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_DUMMY

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

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_pixels_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_events_c.h"
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_ਨਿਵੇਸ਼_LINUXEV
#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/linux/SDL_evdev.h"
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_nullvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_nullevents_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_nullframebuffer_c.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DUMMYVID_DRIVER_NAME       "dummy"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DUMMYVID_DRIVER_EVDEV_NAME "evdev"

// Initialization/Query functions
ਸਥਿਰ bool DUMMY_VideoInitCommon(SDL_VideoDevice *_this);
ਸਥਿਰ bool DUMMY_VideoInit(SDL_VideoDevice *_this);
ਸਥਿਰ ਖਾਲੀ DUMMY_VideoQuit(SDL_VideoDevice *_this);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_ਨਿਵੇਸ਼_LINUXEV
ਸਥਿਰ bool DUMMY_EVDEV_VideoInit(SDL_VideoDevice *_this);
ਸਥਿਰ ਖਾਲੀ DUMMY_EVDEV_VideoQuit(SDL_VideoDevice *_this);
#ਜੇ_ਅੰਤ

ਸਥਿਰ bool DUMMY_ਸੈੱਟ_ਖਿੜਕੀ_Position(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_MOVED, ਖਿੜਕੀ->pending.x, ਖਿੜਕੀ->pending.y);
    ਵਾਪਸ true;
}

ਸਥਿਰ ਖਾਲੀ DUMMY_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_RESIZED, ਖਿੜਕੀ->pending.w, ਖਿੜਕੀ->pending.h);
}

// DUMMY driver bootstrap functions

ਸਥਿਰ bool DUMMY_ਉਪਲਬਧ(ਅਚਲ ਅੱਖਰ *drivername)
{
    ਅਚਲ ਅੱਖਰ *hint = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    ਜੇ (hint && SDL_strstr(hint, drivername) != ਨਿਰਾ) {
        ਵਾਪਸ true;
    }
    ਵਾਪਸ false;
}

ਸਥਿਰ ਖਾਲੀ DUMMY_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

ਸਥਿਰ SDL_VideoDevice *DUMMY_ਅੰਦਰੂਨੀ_Create_Device(ਅਚਲ ਅੱਖਰ *enable_hint)
{
    SDL_VideoDevice *device;

    ਜੇ (!DUMMY_ਉਪਲਬਧ(enable_hint)) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, ਆਕਾਰ(SDL_VideoDevice));
    ਜੇ (!device) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    // Set the function pointers
    device->VideoInit = DUMMY_VideoInit;
    device->VideoQuit = DUMMY_VideoQuit;
    device->PumpEvents = DUMMY_PumpEvents;
    device->ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ = DUMMY_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Position = DUMMY_ਸੈੱਟ_ਖਿੜਕੀ_Position;
    device->Create_ਖਿੜਕੀ_Framebuffer = SDL_DUMMY_Create_ਖਿੜਕੀ_Framebuffer;
    device->Update_ਖਿੜਕੀ_Framebuffer = SDL_DUMMY_Update_ਖਿੜਕੀ_Framebuffer;
    device->Destroy_ਖਿੜਕੀ_Framebuffer = SDL_DUMMY_Destroy_ਖਿੜਕੀ_Framebuffer;
    device->ਮੁਕਤ = DUMMY_DeleteDevice;

    ਵਾਪਸ device;
}

ਸਥਿਰ SDL_VideoDevice *DUMMY_CreateDevice(ਖਾਲੀ)
{
    ਵਾਪਸ DUMMY_ਅੰਦਰੂਨੀ_Create_Device(DUMMYVID_DRIVER_NAME);
}

VideoBootStrap DUMMY_bootstrap = {
    DUMMYVID_DRIVER_NAME, "SDL dummy video driver",
    DUMMY_CreateDevice,
    ਨਿਰਾ, // no ShowMessageBox implementation
    false
};

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_ਨਿਵੇਸ਼_LINUXEV

ਸਥਿਰ bool DUMMY_EVDEV_VideoInit(SDL_VideoDevice *_this)
{
    ਜੇ (!DUMMY_VideoInitCommon(_this)) {
        ਵਾਪਸ false;
    }

    SDL_EVDEV_Init();
    ਵਾਪਸ true;
}

ਸਥਿਰ ਖਾਲੀ DUMMY_EVDEV_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_EVDEV_Quit();
}

ਸਥਿਰ ਖਾਲੀ DUMMY_EVDEV_Poll(SDL_VideoDevice *_this)
{
    (ਖਾਲੀ)_this;
    SDL_EVDEV_Poll();
}

ਸਥਿਰ SDL_VideoDevice *DUMMY_EVDEV_CreateDevice(ਖਾਲੀ)
{
    SDL_VideoDevice *device = DUMMY_ਅੰਦਰੂਨੀ_Create_Device(DUMMYVID_DRIVER_EVDEV_NAME);
    ਜੇ (device) {
        device->VideoInit = DUMMY_EVDEV_VideoInit;
        device->VideoQuit = DUMMY_EVDEV_VideoQuit;
        device->PumpEvents = DUMMY_EVDEV_Poll;
    }
    ਵਾਪਸ device;
}

VideoBootStrap DUMMY_evdev_bootstrap = {
    DUMMYVID_DRIVER_EVDEV_NAME, "SDL dummy video driver with evdev",
    DUMMY_EVDEV_CreateDevice,
    ਨਿਰਾ, // no ShowMessageBox implementation
    false
};

#ਜੇ_ਅੰਤ // SDL_INPUT_LINUXEV

ਸਥਿਰ bool DUMMY_ਸੈੱਟ_Relative_Mouse_ਬਹੁਲਕ(bool enabled)
{
    ਵਾਪਸ true;
}

bool DUMMY_VideoInitCommon(SDL_VideoDevice *_this)
{
    SDL_Display_ਬਹੁਲਕ ਬਹੁਲਕ;

    // Use a fake 32-bpp desktop mode
    SDL_zero(ਬਹੁਲਕ);
    ਬਹੁਲਕ.format = SDL_PIXELFORMAT_XRGB8888;
    ਬਹੁਲਕ.w = 1024;
    ਬਹੁਲਕ.h = 768;
    ਜੇ (SDL_ਜੋੜੋ_Basic_Video_Display(&ਬਹੁਲਕ) == 0) {
        ਵਾਪਸ false;
    }

    ਵਾਪਸ true;
}

bool DUMMY_VideoInit(SDL_VideoDevice *_this)
{
    ਜੇ (!DUMMY_VideoInitCommon(_this)) {
        ਵਾਪਸ false;
    }

    SDL_GetMouse()->ਸੈੱਟ_Relative_Mouse_ਬਹੁਲਕ = DUMMY_ਸੈੱਟ_Relative_Mouse_ਬਹੁਲਕ;
    ਵਾਪਸ true;
}

ਖਾਲੀ DUMMY_VideoQuit(SDL_VideoDevice *_this)
{
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_DUMMY
