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

#నిర్వచితమైతే SDL_VIDEO_DRIVER_DUMMY

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

#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "../SDL_pixels_c.h"
#అన్తర్భావ "../../events/SDL_events_c.h"
#నిర్వచితమైతే SDL_ఆదానం_LINUXEV
#అన్తర్భావ "../../core/linux/SDL_evdev.h"
#అయితే_ముగింపు

#అన్తర్భావ "SDL_nullvideo.h"
#అన్తర్భావ "SDL_nullevents_c.h"
#అన్తర్భావ "SDL_nullframebuffer_c.h"

#నిర్వచించు DUMMYVID_DRIVER_NAME       "dummy"
#నిర్వచించు DUMMYVID_DRIVER_EVDEV_NAME "evdev"

// Initialization/Query functions
స్థిర bool DUMMY_VideoInitCommon(SDL_VideoDevice *_this);
స్థిర bool DUMMY_VideoInit(SDL_VideoDevice *_this);
స్థిర శూన్య DUMMY_VideoQuit(SDL_VideoDevice *_this);
#నిర్వచితమైతే SDL_ఆదానం_LINUXEV
స్థిర bool DUMMY_EVDEV_VideoInit(SDL_VideoDevice *_this);
స్థిర శూన్య DUMMY_EVDEV_VideoQuit(SDL_VideoDevice *_this);
#అయితే_ముగింపు

స్థిర bool DUMMY_సమితి_కిటికీ_Position(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_MOVED, కిటికీ->pending.x, కిటికీ->pending.y);
    తిరిగి true;
}

స్థిర శూన్య DUMMY_సమితి_కిటికీ_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_RESIZED, కిటికీ->pending.w, కిటికీ->pending.h);
}

// DUMMY driver bootstrap functions

స్థిర bool DUMMY_అందుబాటు(స్థిరరాశి అక్షరం *drivername)
{
    స్థిరరాశి అక్షరం *hint = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    ఒకవేళ (hint && SDL_strstr(hint, drivername) != ఖాళీ) {
        తిరిగి true;
    }
    తిరిగి false;
}

స్థిర శూన్య DUMMY_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

స్థిర SDL_VideoDevice *DUMMY_అంతర్గత_Create_Device(స్థిరరాశి అక్షరం *enable_hint)
{
    SDL_VideoDevice *device;

    ఒకవేళ (!DUMMY_అందుబాటు(enable_hint)) {
        తిరిగి ఖాళీ;
    }

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, పరిమాణం(SDL_VideoDevice));
    ఒకవేళ (!device) {
        తిరిగి ఖాళీ;
    }

    // Set the function pointers
    device->VideoInit = DUMMY_VideoInit;
    device->VideoQuit = DUMMY_VideoQuit;
    device->PumpEvents = DUMMY_PumpEvents;
    device->సమితి_కిటికీ_కొలత = DUMMY_సమితి_కిటికీ_కొలత;
    device->సమితి_కిటికీ_Position = DUMMY_సమితి_కిటికీ_Position;
    device->Create_కిటికీ_Framebuffer = SDL_DUMMY_Create_కిటికీ_Framebuffer;
    device->Update_కిటికీ_Framebuffer = SDL_DUMMY_Update_కిటికీ_Framebuffer;
    device->Destroy_కిటికీ_Framebuffer = SDL_DUMMY_Destroy_కిటికీ_Framebuffer;
    device->విడుదల = DUMMY_DeleteDevice;

    తిరిగి device;
}

స్థిర SDL_VideoDevice *DUMMY_CreateDevice(శూన్య)
{
    తిరిగి DUMMY_అంతర్గత_Create_Device(DUMMYVID_DRIVER_NAME);
}

VideoBootStrap DUMMY_bootstrap = {
    DUMMYVID_DRIVER_NAME, "SDL dummy video driver",
    DUMMY_CreateDevice,
    ఖాళీ, // no ShowMessageBox implementation
    false
};

#నిర్వచితమైతే SDL_ఆదానం_LINUXEV

స్థిర bool DUMMY_EVDEV_VideoInit(SDL_VideoDevice *_this)
{
    ఒకవేళ (!DUMMY_VideoInitCommon(_this)) {
        తిరిగి false;
    }

    SDL_EVDEV_Init();
    తిరిగి true;
}

స్థిర శూన్య DUMMY_EVDEV_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_EVDEV_Quit();
}

స్థిర శూన్య DUMMY_EVDEV_Poll(SDL_VideoDevice *_this)
{
    (శూన్య)_this;
    SDL_EVDEV_Poll();
}

స్థిర SDL_VideoDevice *DUMMY_EVDEV_CreateDevice(శూన్య)
{
    SDL_VideoDevice *device = DUMMY_అంతర్గత_Create_Device(DUMMYVID_DRIVER_EVDEV_NAME);
    ఒకవేళ (device) {
        device->VideoInit = DUMMY_EVDEV_VideoInit;
        device->VideoQuit = DUMMY_EVDEV_VideoQuit;
        device->PumpEvents = DUMMY_EVDEV_Poll;
    }
    తిరిగి device;
}

VideoBootStrap DUMMY_evdev_bootstrap = {
    DUMMYVID_DRIVER_EVDEV_NAME, "SDL dummy video driver with evdev",
    DUMMY_EVDEV_CreateDevice,
    ఖాళీ, // no ShowMessageBox implementation
    false
};

#అయితే_ముగింపు // SDL_INPUT_LINUXEV

స్థిర bool DUMMY_సమితి_Relative_Mouse_బహుళకం(bool enabled)
{
    తిరిగి true;
}

bool DUMMY_VideoInitCommon(SDL_VideoDevice *_this)
{
    SDL_Display_బహుళకం బహుళకం;

    // Use a fake 32-bpp desktop mode
    SDL_zero(బహుళకం);
    బహుళకం.format = SDL_PIXELFORMAT_XRGB8888;
    బహుళకం.w = 1024;
    బహుళకం.h = 768;
    ఒకవేళ (SDL_కూడు_Basic_Video_Display(&బహుళకం) == 0) {
        తిరిగి false;
    }

    తిరిగి true;
}

bool DUMMY_VideoInit(SDL_VideoDevice *_this)
{
    ఒకవేళ (!DUMMY_VideoInitCommon(_this)) {
        తిరిగి false;
    }

    SDL_GetMouse()->సమితి_Relative_Mouse_బహుళకం = DUMMY_సమితి_Relative_Mouse_బహుళకం;
    తిరిగి true;
}

శూన్య DUMMY_VideoQuit(SDL_VideoDevice *_this)
{
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_DUMMY
