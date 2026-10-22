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
#شامل "../SDL_sysvideo.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_NGAGE

#شامل "SDL_ngagevideo.h"

#تعریف_کرو NGAGE_VIDEO_DRIVER_NAME "N-Gage"

ساکن خالی NGAGE_DeleteDevice(SDL_VideoDevice *device);
ساکن bool NGAGE_VideoInit(SDL_VideoDevice *device);
ساکن خالی NGAGE_VideoQuit(SDL_VideoDevice *device);

ساکن bool NGAGE_GetDisplayBounds(SDL_VideoDevice *device, SDL_VideoDisplay *display, SDL_Rect *rect);
ساکن bool NGAGE_GetDisplayModes(SDL_VideoDevice *device, SDL_VideoDisplay *display);

ساکن خالی NGAGE_PumpEvents(SDL_VideoDevice *device);

ساکن bool NGAGE_SuspendScreenSaver(SDL_VideoDevice *device);

ساکن SDL_VideoDevice *NGAGE_CreateDevice(خالی)
{
    SDL_VideoDevice *device;
    SDL_Video_ڈیٹا *phdata;

    // Initialize all variables that we clean on shutdown.
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    اگر (!device) {
        SDL_برآمد_کا_حافظہ();
        واپس (SDL_VideoDevice *)0;
    }

    // Initialize internal N-Gage specific data.
    phdata = (SDL_Video_ڈیٹا *)SDL_calloc(1, حجم(SDL_Video_ڈیٹا));
    اگر (!phdata) {
        SDL_برآمد_کا_حافظہ();
        SDL_free(device);
        واپس (SDL_VideoDevice *)0;
    }

    device->اندرونی_2 = phdata;

    device->name = "Nokia N-Gage";

    device->VideoInit = NGAGE_VideoInit;
    device->VideoQuit = NGAGE_VideoQuit;

    device->GetDisplayBounds = NGAGE_GetDisplayBounds;
    device->GetDisplayModes = NGAGE_GetDisplayModes;

    device->PumpEvents = NGAGE_PumpEvents;

    device->SuspendScreenSaver = NGAGE_SuspendScreenSaver;

    device->آزاد = NGAGE_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    واپس device;
}

VideoBootStrap NGAGE_bootstrap = {
    NGAGE_VIDEO_DRIVER_NAME,
    "N-Gage Video Driver",
    NGAGE_CreateDevice,
    0
};

ساکن خالی NGAGE_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->اندرونی_2);
    SDL_free(device);
}

ساکن bool NGAGE_VideoInit(SDL_VideoDevice *device)
{
    SDL_Video_ڈیٹا *phdata = (SDL_Video_ڈیٹا *)device->اندرونی_2;

    اگر (!phdata) {
        واپس false;
    }

    SDL_zero(phdata->منوال);
    SDL_zero(phdata->display);

    phdata->منوال.w = 176;
    phdata->منوال.h = 208;
    phdata->منوال.refresh_شرح = 60.0f;
    phdata->منوال.format = SDL_PIXELFORMAT_XRGB4444;

    phdata->display.name = "N-Gage";
    phdata->display.desktop_منوال = phdata->منوال;

    اگر (SDL_جوڑو_Video_Display(&phdata->display, false) == 0) {
        واپس false;
    }

    واپس true;
}

ساکن خالی NGAGE_VideoQuit(SDL_VideoDevice *device)
{
    SDL_Video_ڈیٹا *phdata = (SDL_Video_ڈیٹا *)device->اندرونی_2;

    اگر (phdata) {
        SDL_zero(phdata->منوال);
        SDL_zero(phdata->display);
    }
}

ساکن bool NGAGE_GetDisplayBounds(SDL_VideoDevice *device, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    اگر (!display) {
        واپس false;
    }

    rect->x = 0;
    rect->y = 0;
    rect->w = display->current_منوال->w;
    rect->h = display->current_منوال->h;

    واپس true;
}

ساکن bool NGAGE_GetDisplayModes(SDL_VideoDevice *device, SDL_VideoDisplay *display)
{
    SDL_Video_ڈیٹا *phdata = (SDL_Video_ڈیٹا *)device->اندرونی_2;
    SDL_Display_منوال منوال;

    SDL_zero(منوال);
    منوال.w = phdata->منوال.w;
    منوال.h = phdata->منوال.h;
    منوال.refresh_شرح = phdata->منوال.refresh_شرح;
    منوال.format = phdata->منوال.format;

    اگر (!SDL_جوڑو_Fullscreen_Display_منوال(display, &منوال)) {
        واپس false;
    }

    واپس true;
}

#شامل "../../render/ngage/SDL_render_ngage_c.h"

ساکن خالی NGAGE_PumpEvents(SDL_VideoDevice *device)
{
    NGAGE_Pump_Events_اندرونی();
}

ساکن bool NGAGE_SuspendScreenSaver(SDL_VideoDevice *device)
{
    NGAGE_Suspend_Screen_Saver_اندرونی(device->suspend_screensaver);
    واپس true;
}

#اگر_ختم // SDL_VIDEO_DRIVER_NGAGE
