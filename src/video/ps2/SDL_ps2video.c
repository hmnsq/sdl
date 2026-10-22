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
#अन्तर्भाव "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_PS2

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

#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../SDL_pixels_c.h"
#अन्तर्भाव "../../events/SDL_events_c.h"

#अन्तर्भाव "SDL_ps2video.h"

// PS2 driver bootstrap functions

स्थिर bool PS2_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    परत true;
}

स्थिर शून्य PS2_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

स्थिर bool PS2_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_SetKeyboardFocus(window);

    // Window has been successfully created
    परत true;
}

स्थिर bool PS2_VideoInit(SDL_VideoDevice *_this)
{
    SDL_DisplayMode mode;

    SDL_zero(mode);
    mode.w = 640;
    mode.h = 448;
    mode.refresh_rate = 60.0f;

    // 32 bpp for default
    mode.format = SDL_PIXELFORMAT_ABGR8888;

    SDL_AddBasicVideoDisplay(&mode);

    परत true;
}

स्थिर शून्य PS2_VideoQuit(SDL_VideoDevice *_this)
{
}

स्थिर शून्य PS2_PumpEvents(SDL_VideoDevice *_this)
{
    // do nothing.
}

स्थिर SDL_VideoDevice *PS2_CreateDevice(शून्य)
{
    SDL_VideoDevice *device;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, आकार(SDL_VideoDevice));
    जर (!device) {
        परत रिक्त;
    }

    // Set the function pointers
    device->VideoInit = PS2_VideoInit;
    device->VideoQuit = PS2_VideoQuit;
    device->SetDisplayMode = PS2_SetDisplayMode;
    device->CreateSDLWindow = PS2_CreateWindow;
    device->PumpEvents = PS2_PumpEvents;
    device->मुक्त = PS2_DeleteDevice;

    परत device;
}

VideoBootStrap PS2_bootstrap = {
    "ps2",
    "PS2 Video Driver",
    PS2_CreateDevice,
    रिक्त, // no ShowMessageBox implementation
    false
};

#endif // SDL_VIDEO_DRIVER_PS2
