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
#अन्तर्भाव "../SDL_sysvideo.h"

#ifdef SDL_VIDEO_DRIVER_NGAGE

#अन्तर्भाव "SDL_ngagevideo.h"

#define NGAGE_VIDEO_DRIVER_NAME "N-Gage"

स्थिर शून्य NGAGE_DeleteDevice(SDL_VideoDevice *device);
स्थिर bool NGAGE_VideoInit(SDL_VideoDevice *device);
स्थिर शून्य NGAGE_VideoQuit(SDL_VideoDevice *device);

स्थिर bool NGAGE_GetDisplayBounds(SDL_VideoDevice *device, SDL_VideoDisplay *display, SDL_Rect *rect);
स्थिर bool NGAGE_GetDisplayModes(SDL_VideoDevice *device, SDL_VideoDisplay *display);

स्थिर शून्य NGAGE_PumpEvents(SDL_VideoDevice *device);

स्थिर bool NGAGE_SuspendScreenSaver(SDL_VideoDevice *device);

स्थिर SDL_VideoDevice *NGAGE_CreateDevice(शून्य)
{
    SDL_VideoDevice *device;
    SDL_VideoData *phdata;

    // Initialize all variables that we clean on shutdown.
    device = (SDL_VideoDevice *)SDL_calloc(1, आकार(SDL_VideoDevice));
    जर (!device) {
        SDL_OutOfMemory();
        परत (SDL_VideoDevice *)0;
    }

    // Initialize internal N-Gage specific data.
    phdata = (SDL_VideoData *)SDL_calloc(1, आकार(SDL_VideoData));
    जर (!phdata) {
        SDL_OutOfMemory();
        SDL_free(device);
        परत (SDL_VideoDevice *)0;
    }

    device->internal = phdata;

    device->name = "Nokia N-Gage";

    device->VideoInit = NGAGE_VideoInit;
    device->VideoQuit = NGAGE_VideoQuit;

    device->GetDisplayBounds = NGAGE_GetDisplayBounds;
    device->GetDisplayModes = NGAGE_GetDisplayModes;

    device->PumpEvents = NGAGE_PumpEvents;

    device->SuspendScreenSaver = NGAGE_SuspendScreenSaver;

    device->मुक्त = NGAGE_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    परत device;
}

VideoBootStrap NGAGE_bootstrap = {
    NGAGE_VIDEO_DRIVER_NAME,
    "N-Gage Video Driver",
    NGAGE_CreateDevice,
    0
};

स्थिर शून्य NGAGE_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

स्थिर bool NGAGE_VideoInit(SDL_VideoDevice *device)
{
    SDL_VideoData *phdata = (SDL_VideoData *)device->internal;

    जर (!phdata) {
        परत false;
    }

    SDL_zero(phdata->mode);
    SDL_zero(phdata->display);

    phdata->mode.w = 176;
    phdata->mode.h = 208;
    phdata->mode.refresh_rate = 60.0f;
    phdata->mode.format = SDL_PIXELFORMAT_XRGB4444;

    phdata->display.name = "N-Gage";
    phdata->display.desktop_mode = phdata->mode;

    जर (SDL_AddVideoDisplay(&phdata->display, false) == 0) {
        परत false;
    }

    परत true;
}

स्थिर शून्य NGAGE_VideoQuit(SDL_VideoDevice *device)
{
    SDL_VideoData *phdata = (SDL_VideoData *)device->internal;

    जर (phdata) {
        SDL_zero(phdata->mode);
        SDL_zero(phdata->display);
    }
}

स्थिर bool NGAGE_GetDisplayBounds(SDL_VideoDevice *device, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    जर (!display) {
        परत false;
    }

    rect->x = 0;
    rect->y = 0;
    rect->w = display->current_mode->w;
    rect->h = display->current_mode->h;

    परत true;
}

स्थिर bool NGAGE_GetDisplayModes(SDL_VideoDevice *device, SDL_VideoDisplay *display)
{
    SDL_VideoData *phdata = (SDL_VideoData *)device->internal;
    SDL_DisplayMode mode;

    SDL_zero(mode);
    mode.w = phdata->mode.w;
    mode.h = phdata->mode.h;
    mode.refresh_rate = phdata->mode.refresh_rate;
    mode.format = phdata->mode.format;

    जर (!SDL_AddFullscreenDisplayMode(display, &mode)) {
        परत false;
    }

    परत true;
}

#अन्तर्भाव "../../render/ngage/SDL_render_ngage_c.h"

स्थिर शून्य NGAGE_PumpEvents(SDL_VideoDevice *device)
{
    NGAGE_PumpEventsInternal();
}

स्थिर bool NGAGE_SuspendScreenSaver(SDL_VideoDevice *device)
{
    NGAGE_SuspendScreenSaverInternal(device->suspend_screensaver);
    परत true;
}

#endif // SDL_VIDEO_DRIVER_NGAGE
