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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_NGAGE

#ಅನ್ತರ್ಭಾವ "SDL_ngagevideo.h"

#ವ್ಯಾಖ್ಯಾನಿಸು NGAGE_VIDEO_DRIVER_NAME "N-Gage"

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
    SDL_Video_ದತ್ತಾಂಶ *phdata;

    // Initialize all variables that we clean on shutdown.
    device = (SDL_VideoDevice *)SDL_calloc(1, ಗಾತ್ರ(SDL_VideoDevice));
    ಆದರೆ (!device) {
        SDL_ಹೊರಹೋಗು_ದ_ಸ್ಮರಣೆ();
        ಹಿಂತಿರುಗಿ (SDL_VideoDevice *)0;
    }

    // Initialize internal N-Gage specific data.
    phdata = (SDL_Video_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_Video_ದತ್ತಾಂಶ));
    ಆದರೆ (!phdata) {
        SDL_ಹೊರಹೋಗು_ದ_ಸ್ಮರಣೆ();
        SDL_free(device);
        ಹಿಂತಿರುಗಿ (SDL_VideoDevice *)0;
    }

    device->ಆಂತರಿಕ = phdata;

    device->name = "Nokia N-Gage";

    device->VideoInit = NGAGE_VideoInit;
    device->VideoQuit = NGAGE_VideoQuit;

    device->GetDisplayBounds = NGAGE_GetDisplayBounds;
    device->GetDisplayModes = NGAGE_GetDisplayModes;

    device->PumpEvents = NGAGE_PumpEvents;

    device->SuspendScreenSaver = NGAGE_SuspendScreenSaver;

    device->ಬಿಡುಗಡೆ = NGAGE_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    ಹಿಂತಿರುಗಿ device;
}

VideoBootStrap NGAGE_bootstrap = {
    NGAGE_VIDEO_DRIVER_NAME,
    "N-Gage Video Driver",
    NGAGE_CreateDevice,
    0
};

ಸ್ಥಿರ ಶೂನ್ಯ NGAGE_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->ಆಂತರಿಕ);
    SDL_free(device);
}

ಸ್ಥಿರ bool NGAGE_VideoInit(SDL_VideoDevice *device)
{
    SDL_Video_ದತ್ತಾಂಶ *phdata = (SDL_Video_ದತ್ತಾಂಶ *)device->ಆಂತರಿಕ;

    ಆದರೆ (!phdata) {
        ಹಿಂತಿರುಗಿ false;
    }

    SDL_zero(phdata->ಬಹುಲಕ);
    SDL_zero(phdata->display);

    phdata->ಬಹುಲಕ.w = 176;
    phdata->ಬಹುಲಕ.h = 208;
    phdata->ಬಹುಲಕ.refresh_ದರ = 60.0f;
    phdata->ಬಹುಲಕ.format = SDL_PIXELFORMAT_XRGB4444;

    phdata->display.name = "N-Gage";
    phdata->display.desktop_ಬಹುಲಕ = phdata->ಬಹುಲಕ;

    ಆದರೆ (SDL_ಕೂಡಿಸು_Video_Display(&phdata->display, false) == 0) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ NGAGE_VideoQuit(SDL_VideoDevice *device)
{
    SDL_Video_ದತ್ತಾಂಶ *phdata = (SDL_Video_ದತ್ತಾಂಶ *)device->ಆಂತರಿಕ;

    ಆದರೆ (phdata) {
        SDL_zero(phdata->ಬಹುಲಕ);
        SDL_zero(phdata->display);
    }
}

ಸ್ಥಿರ bool NGAGE_GetDisplayBounds(SDL_VideoDevice *device, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ಆದರೆ (!display) {
        ಹಿಂತಿರುಗಿ false;
    }

    rect->x = 0;
    rect->y = 0;
    rect->w = display->current_ಬಹುಲಕ->w;
    rect->h = display->current_ಬಹುಲಕ->h;

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool NGAGE_GetDisplayModes(SDL_VideoDevice *device, SDL_VideoDisplay *display)
{
    SDL_Video_ದತ್ತಾಂಶ *phdata = (SDL_Video_ದತ್ತಾಂಶ *)device->ಆಂತರಿಕ;
    SDL_Display_ಬಹುಲಕ ಬಹುಲಕ;

    SDL_zero(ಬಹುಲಕ);
    ಬಹುಲಕ.w = phdata->ಬಹುಲಕ.w;
    ಬಹುಲಕ.h = phdata->ಬಹುಲಕ.h;
    ಬಹುಲಕ.refresh_ದರ = phdata->ಬಹುಲಕ.refresh_ದರ;
    ಬಹುಲಕ.format = phdata->ಬಹುಲಕ.format;

    ಆದರೆ (!SDL_ಕೂಡಿಸು_Fullscreen_Display_ಬಹುಲಕ(display, &ಬಹುಲಕ)) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಹಿಂತಿರುಗಿ true;
}

#ಅನ್ತರ್ಭಾವ "../../render/ngage/SDL_render_ngage_c.h"

ಸ್ಥಿರ ಶೂನ್ಯ NGAGE_PumpEvents(SDL_VideoDevice *device)
{
    NGAGE_Pump_Events_ಆಂತರಿಕ();
}

ಸ್ಥಿರ bool NGAGE_SuspendScreenSaver(SDL_VideoDevice *device)
{
    NGAGE_Suspend_Screen_Saver_ಆಂತರಿಕ(device->suspend_screensaver);
    ಹಿಂತಿರುಗಿ true;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_NGAGE
