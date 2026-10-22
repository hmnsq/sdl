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
#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"

#ifdef SDL_VIDEO_DRIVER_NGAGE

#ಅನ್ತರ್ಭಾವ "SDL_ngagevideo.h"

#define NGAGE_VIDEO_DRIVER_NAME "N-Gage"

ಸ್ಥಿರ ಶೂನ್ಯ NGAGE_DeleteDevice(SDL_VideoDevice *device);
ಸ್ಥಿರ bool NGAGE_VideoInit(SDL_VideoDevice *device);
ಸ್ಥಿರ ಶೂನ್ಯ NGAGE_VideoQuit(SDL_VideoDevice *device);

ಸ್ಥಿರ bool NGAGE_GetDisplayBounds(SDL_VideoDevice *device, SDL_VideoDisplay *display, SDL_Rect *rect);
ಸ್ಥಿರ bool NGAGE_GetDisplayModes(SDL_VideoDevice *device, SDL_VideoDisplay *display);

ಸ್ಥಿರ ಶೂನ್ಯ NGAGE_PumpEvents(SDL_VideoDevice *device);

ಸ್ಥಿರ bool NGAGE_SuspendScreenSaver(SDL_VideoDevice *device);

ಸ್ಥಿರ SDL_VideoDevice *NGAGE_CreateDevice(ಶೂನ್ಯ)
{
    SDL_VideoDevice *device;
    SDL_VideoData *phdata;

    // Initialize all variables that we clean on shutdown.
    device = (SDL_VideoDevice *)SDL_calloc(1, ಪರಿಮಾಣ(SDL_VideoDevice));
    ಯದಿ (!device) {
        SDL_OutOfMemory();
        ಪ್ರತ್ಯಾಗಮ (SDL_VideoDevice *)0;
    }

    // Initialize internal N-Gage specific data.
    phdata = (SDL_VideoData *)SDL_calloc(1, ಪರಿಮಾಣ(SDL_VideoData));
    ಯದಿ (!phdata) {
        SDL_OutOfMemory();
        SDL_free(device);
        ಪ್ರತ್ಯಾಗಮ (SDL_VideoDevice *)0;
    }

    device->internal = phdata;

    device->name = "Nokia N-Gage";

    device->VideoInit = NGAGE_VideoInit;
    device->VideoQuit = NGAGE_VideoQuit;

    device->GetDisplayBounds = NGAGE_GetDisplayBounds;
    device->GetDisplayModes = NGAGE_GetDisplayModes;

    device->PumpEvents = NGAGE_PumpEvents;

    device->SuspendScreenSaver = NGAGE_SuspendScreenSaver;

    device->ಮುಕ್ತ = NGAGE_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    ಪ್ರತ್ಯಾಗಮ device;
}

VideoBootStrap NGAGE_bootstrap = {
    NGAGE_VIDEO_DRIVER_NAME,
    "N-Gage Video Driver",
    NGAGE_CreateDevice,
    0
};

ಸ್ಥಿರ ಶೂನ್ಯ NGAGE_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

ಸ್ಥಿರ bool NGAGE_VideoInit(SDL_VideoDevice *device)
{
    SDL_VideoData *phdata = (SDL_VideoData *)device->internal;

    ಯದಿ (!phdata) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    SDL_zero(phdata->mode);
    SDL_zero(phdata->display);

    phdata->mode.w = 176;
    phdata->mode.h = 208;
    phdata->mode.refresh_rate = 60.0f;
    phdata->mode.format = SDL_PIXELFORMAT_XRGB4444;

    phdata->display.name = "N-Gage";
    phdata->display.desktop_mode = phdata->mode;

    ಯದಿ (SDL_AddVideoDisplay(&phdata->display, false) == 0) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ NGAGE_VideoQuit(SDL_VideoDevice *device)
{
    SDL_VideoData *phdata = (SDL_VideoData *)device->internal;

    ಯದಿ (phdata) {
        SDL_zero(phdata->mode);
        SDL_zero(phdata->display);
    }
}

ಸ್ಥಿರ bool NGAGE_GetDisplayBounds(SDL_VideoDevice *device, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ಯದಿ (!display) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    rect->x = 0;
    rect->y = 0;
    rect->w = display->current_mode->w;
    rect->h = display->current_mode->h;

    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool NGAGE_GetDisplayModes(SDL_VideoDevice *device, SDL_VideoDisplay *display)
{
    SDL_VideoData *phdata = (SDL_VideoData *)device->internal;
    SDL_DisplayMode mode;

    SDL_zero(mode);
    mode.w = phdata->mode.w;
    mode.h = phdata->mode.h;
    mode.refresh_rate = phdata->mode.refresh_rate;
    mode.format = phdata->mode.format;

    ಯದಿ (!SDL_AddFullscreenDisplayMode(display, &mode)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

#ಅನ್ತರ್ಭಾವ "../../render/ngage/SDL_render_ngage_c.h"

ಸ್ಥಿರ ಶೂನ್ಯ NGAGE_PumpEvents(SDL_VideoDevice *device)
{
    NGAGE_PumpEventsInternal();
}

ಸ್ಥಿರ bool NGAGE_SuspendScreenSaver(SDL_VideoDevice *device)
{
    NGAGE_SuspendScreenSaverInternal(device->suspend_screensaver);
    ಪ್ರತ್ಯಾಗಮ true;
}

#endif // SDL_VIDEO_DRIVER_NGAGE
