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

#که_تعریف_شوی SDL_VIDEO_DRIVER_PS2

/* PS2 SDL video driver implementation; this is just enough to make an
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
 *  SDL video driver.  Renamed to "PS2" by Sam Lantinga.
 */

#ضمن "../SDL_sysvideo.h"
#ضمن "../SDL_pixels_c.h"
#ضمن "../../events/SDL_events_c.h"

#ضمن "SDL_ps2video.h"

// PS2 driver bootstrap functions

ساكن bool PS2_سېټ_Display_ډېرپېښ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ډېرپېښ *ډېرپېښ)
{
    أرجع true;
}

ساكن فراغ PS2_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

ساكن bool PS2_Create_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID create_props)
{
    SDL_سېټ_Keyboard_Focus(کړکۍ);

    // Window has been successfully created
    أرجع true;
}

ساكن bool PS2_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Display_ډېرپېښ ډېرپېښ;

    SDL_zero(ډېرپېښ);
    ډېرپېښ.w = 640;
    ډېرپېښ.h = 448;
    ډېرپېښ.refresh_شرح = 60.0f;

    // 32 bpp for default
    ډېرپېښ.format = SDL_PIXELFORMAT_ABGR8888;

    SDL_جمع_کړه_Basic_Video_Display(&ډېرپېښ);

    أرجع true;
}

ساكن فراغ PS2_VideoQuit(SDL_VideoDevice *_this)
{
}

ساكن فراغ PS2_PumpEvents(SDL_VideoDevice *_this)
{
    // do nothing.
}

ساكن SDL_VideoDevice *PS2_CreateDevice(فراغ)
{
    SDL_VideoDevice *device;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (!device) {
        أرجع عدم;
    }

    // Set the function pointers
    device->VideoInit = PS2_VideoInit;
    device->VideoQuit = PS2_VideoQuit;
    device->سېټ_Display_ډېرپېښ = PS2_سېټ_Display_ډېرپېښ;
    device->CreateSDLWindow = PS2_Create_کړکۍ;
    device->PumpEvents = PS2_PumpEvents;
    device->حرر = PS2_DeleteDevice;

    أرجع device;
}

VideoBootStrap PS2_bootstrap = {
    "ps2",
    "PS2 Video Driver",
    PS2_CreateDevice,
    عدم, // no ShowMessageBox implementation
    false
};

#د_که_پای // SDL_VIDEO_DRIVER_PS2
