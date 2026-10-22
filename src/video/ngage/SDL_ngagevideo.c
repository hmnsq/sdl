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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_NGAGE

#अन्तर्भाव "SDL_ngagevideo.h"

#परिभाषय NGAGE_VIDEO_DRIVER_NAME "N-Gage"

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
    SDL_Video_दत्त *phdata;

    // Initialize all variables that we clean on shutdown.
    device = (SDL_VideoDevice *)SDL_calloc(1, परिमाण(SDL_VideoDevice));
    यदि (!device) {
        SDL_बहिर्गमनम्_सम्बन्धि_स्मृतिः();
        प्रत्यागम (SDL_VideoDevice *)0;
    }

    // Initialize internal N-Gage specific data.
    phdata = (SDL_Video_दत्त *)SDL_calloc(1, परिमाण(SDL_Video_दत्त));
    यदि (!phdata) {
        SDL_बहिर्गमनम्_सम्बन्धि_स्मृतिः();
        SDL_free(device);
        प्रत्यागम (SDL_VideoDevice *)0;
    }

    device->आन्तरिकम् = phdata;

    device->name = "Nokia N-Gage";

    device->VideoInit = NGAGE_VideoInit;
    device->VideoQuit = NGAGE_VideoQuit;

    device->GetDisplayBounds = NGAGE_GetDisplayBounds;
    device->GetDisplayModes = NGAGE_GetDisplayModes;

    device->PumpEvents = NGAGE_PumpEvents;

    device->SuspendScreenSaver = NGAGE_SuspendScreenSaver;

    device->मुक्त = NGAGE_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    प्रत्यागम device;
}

VideoBootStrap NGAGE_bootstrap = {
    NGAGE_VIDEO_DRIVER_NAME,
    "N-Gage Video Driver",
    NGAGE_CreateDevice,
    0
};

स्थिर शून्य NGAGE_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->आन्तरिकम्);
    SDL_free(device);
}

स्थिर bool NGAGE_VideoInit(SDL_VideoDevice *device)
{
    SDL_Video_दत्त *phdata = (SDL_Video_दत्त *)device->आन्तरिकम्;

    यदि (!phdata) {
        प्रत्यागम false;
    }

    SDL_zero(phdata->बहुलकम्);
    SDL_zero(phdata->display);

    phdata->बहुलकम्.w = 176;
    phdata->बहुलकम्.h = 208;
    phdata->बहुलकम्.refresh_दरः = 60.0f;
    phdata->बहुलकम्.format = SDL_PIXELFORMAT_XRGB4444;

    phdata->display.name = "N-Gage";
    phdata->display.desktop_बहुलकम् = phdata->बहुलकम्;

    यदि (SDL_सङ्कलय_Video_Display(&phdata->display, false) == 0) {
        प्रत्यागम false;
    }

    प्रत्यागम true;
}

स्थिर शून्य NGAGE_VideoQuit(SDL_VideoDevice *device)
{
    SDL_Video_दत्त *phdata = (SDL_Video_दत्त *)device->आन्तरिकम्;

    यदि (phdata) {
        SDL_zero(phdata->बहुलकम्);
        SDL_zero(phdata->display);
    }
}

स्थिर bool NGAGE_GetDisplayBounds(SDL_VideoDevice *device, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    यदि (!display) {
        प्रत्यागम false;
    }

    rect->x = 0;
    rect->y = 0;
    rect->w = display->current_बहुलकम्->w;
    rect->h = display->current_बहुलकम्->h;

    प्रत्यागम true;
}

स्थिर bool NGAGE_GetDisplayModes(SDL_VideoDevice *device, SDL_VideoDisplay *display)
{
    SDL_Video_दत्त *phdata = (SDL_Video_दत्त *)device->आन्तरिकम्;
    SDL_Display_बहुलकम् बहुलकम्;

    SDL_zero(बहुलकम्);
    बहुलकम्.w = phdata->बहुलकम्.w;
    बहुलकम्.h = phdata->बहुलकम्.h;
    बहुलकम्.refresh_दरः = phdata->बहुलकम्.refresh_दरः;
    बहुलकम्.format = phdata->बहुलकम्.format;

    यदि (!SDL_सङ्कलय_Fullscreen_Display_बहुलकम्(display, &बहुलकम्)) {
        प्रत्यागम false;
    }

    प्रत्यागम true;
}

#अन्तर्भाव "../../render/ngage/SDL_render_ngage_c.h"

स्थिर शून्य NGAGE_PumpEvents(SDL_VideoDevice *device)
{
    NGAGE_Pump_Events_आन्तरिकम्();
}

स्थिर bool NGAGE_SuspendScreenSaver(SDL_VideoDevice *device)
{
    NGAGE_Suspend_Screen_Saver_आन्तरिकम्(device->suspend_screensaver);
    प्रत्यागम true;
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_NGAGE
