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
#ضمن "../SDL_sysvideo.h"

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_NGAGE

#ضمن "SDL_ngagevideo.h"

#وصف_ڪريو NGAGE_VIDEO_DRIVER_NAME "N-Gage"

ساكن فراغ NGAGE_DeleteDevice(SDL_VideoDevice *device);
ساكن bool NGAGE_VideoInit(SDL_VideoDevice *device);
ساكن فراغ NGAGE_VideoQuit(SDL_VideoDevice *device);

ساكن bool NGAGE_GetDisplayBounds(SDL_VideoDevice *device, SDL_VideoDisplay *display, SDL_Rect *rect);
ساكن bool NGAGE_GetDisplayModes(SDL_VideoDevice *device, SDL_VideoDisplay *display);

ساكن فراغ NGAGE_PumpEvents(SDL_VideoDevice *device);

ساكن bool NGAGE_SuspendScreenSaver(SDL_VideoDevice *device);

ساكن SDL_VideoDevice *NGAGE_CreateDevice(فراغ)
{
    SDL_VideoDevice *device;
    SDL_Video_معلومات *phdata;

    // Initialize all variables that we clean on shutdown.
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (!device) {
        SDL_ٻاهريون_جو_يادگيري();
        أرجع (SDL_VideoDevice *)0;
    }

    // Initialize internal N-Gage specific data.
    phdata = (SDL_Video_معلومات *)SDL_calloc(1, حجم(SDL_Video_معلومات));
    إذا (!phdata) {
        SDL_ٻاهريون_جو_يادگيري();
        SDL_free(device);
        أرجع (SDL_VideoDevice *)0;
    }

    device->اندروني = phdata;

    device->name = "Nokia N-Gage";

    device->VideoInit = NGAGE_VideoInit;
    device->VideoQuit = NGAGE_VideoQuit;

    device->GetDisplayBounds = NGAGE_GetDisplayBounds;
    device->GetDisplayModes = NGAGE_GetDisplayModes;

    device->PumpEvents = NGAGE_PumpEvents;

    device->SuspendScreenSaver = NGAGE_SuspendScreenSaver;

    device->حرر = NGAGE_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    أرجع device;
}

VideoBootStrap NGAGE_bootstrap = {
    NGAGE_VIDEO_DRIVER_NAME,
    "N-Gage Video Driver",
    NGAGE_CreateDevice,
    0
};

ساكن فراغ NGAGE_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->اندروني);
    SDL_free(device);
}

ساكن bool NGAGE_VideoInit(SDL_VideoDevice *device)
{
    SDL_Video_معلومات *phdata = (SDL_Video_معلومات *)device->اندروني;

    إذا (!phdata) {
        أرجع false;
    }

    SDL_zero(phdata->گهڻائي);
    SDL_zero(phdata->display);

    phdata->گهڻائي.w = 176;
    phdata->گهڻائي.h = 208;
    phdata->گهڻائي.refresh_شرح = 60.0f;
    phdata->گهڻائي.format = SDL_PIXELFORMAT_XRGB4444;

    phdata->display.name = "N-Gage";
    phdata->display.desktop_گهڻائي = phdata->گهڻائي;

    إذا (SDL_جوڙيو_Video_Display(&phdata->display, false) == 0) {
        أرجع false;
    }

    أرجع true;
}

ساكن فراغ NGAGE_VideoQuit(SDL_VideoDevice *device)
{
    SDL_Video_معلومات *phdata = (SDL_Video_معلومات *)device->اندروني;

    إذا (phdata) {
        SDL_zero(phdata->گهڻائي);
        SDL_zero(phdata->display);
    }
}

ساكن bool NGAGE_GetDisplayBounds(SDL_VideoDevice *device, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    إذا (!display) {
        أرجع false;
    }

    rect->x = 0;
    rect->y = 0;
    rect->w = display->current_گهڻائي->w;
    rect->h = display->current_گهڻائي->h;

    أرجع true;
}

ساكن bool NGAGE_GetDisplayModes(SDL_VideoDevice *device, SDL_VideoDisplay *display)
{
    SDL_Video_معلومات *phdata = (SDL_Video_معلومات *)device->اندروني;
    SDL_Display_گهڻائي گهڻائي;

    SDL_zero(گهڻائي);
    گهڻائي.w = phdata->گهڻائي.w;
    گهڻائي.h = phdata->گهڻائي.h;
    گهڻائي.refresh_شرح = phdata->گهڻائي.refresh_شرح;
    گهڻائي.format = phdata->گهڻائي.format;

    إذا (!SDL_جوڙيو_Fullscreen_Display_گهڻائي(display, &گهڻائي)) {
        أرجع false;
    }

    أرجع true;
}

#ضمن "../../render/ngage/SDL_render_ngage_c.h"

ساكن فراغ NGAGE_PumpEvents(SDL_VideoDevice *device)
{
    NGAGE_Pump_Events_اندروني();
}

ساكن bool NGAGE_SuspendScreenSaver(SDL_VideoDevice *device)
{
    NGAGE_Suspend_Screen_Saver_اندروني(device->suspend_screensaver);
    أرجع true;
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_NGAGE
