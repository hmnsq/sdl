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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_PS2

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

#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "../SDL_pixels_c.h"
#అన్తర్భావ "../../events/SDL_events_c.h"

#అన్తర్భావ "SDL_ps2video.h"

// PS2 driver bootstrap functions

స్థిర bool PS2_సమితి_Display_బహుళకం(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_బహుళకం *బహుళకం)
{
    తిరిగి true;
}

స్థిర శూన్య PS2_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

స్థిర bool PS2_Create_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID create_props)
{
    SDL_సమితి_Keyboard_Focus(కిటికీ);

    // Window has been successfully created
    తిరిగి true;
}

స్థిర bool PS2_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Display_బహుళకం బహుళకం;

    SDL_zero(బహుళకం);
    బహుళకం.w = 640;
    బహుళకం.h = 448;
    బహుళకం.refresh_రేటు = 60.0f;

    // 32 bpp for default
    బహుళకం.format = SDL_PIXELFORMAT_ABGR8888;

    SDL_కూడు_Basic_Video_Display(&బహుళకం);

    తిరిగి true;
}

స్థిర శూన్య PS2_VideoQuit(SDL_VideoDevice *_this)
{
}

స్థిర శూన్య PS2_PumpEvents(SDL_VideoDevice *_this)
{
    // do nothing.
}

స్థిర SDL_VideoDevice *PS2_CreateDevice(శూన్య)
{
    SDL_VideoDevice *device;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, పరిమాణం(SDL_VideoDevice));
    ఒకవేళ (!device) {
        తిరిగి ఖాళీ;
    }

    // Set the function pointers
    device->VideoInit = PS2_VideoInit;
    device->VideoQuit = PS2_VideoQuit;
    device->సమితి_Display_బహుళకం = PS2_సమితి_Display_బహుళకం;
    device->CreateSDLWindow = PS2_Create_కిటికీ;
    device->PumpEvents = PS2_PumpEvents;
    device->విడుదల = PS2_DeleteDevice;

    తిరిగి device;
}

VideoBootStrap PS2_bootstrap = {
    "ps2",
    "PS2 Video Driver",
    PS2_CreateDevice,
    ఖాళీ, // no ShowMessageBox implementation
    false
};

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_PS2
