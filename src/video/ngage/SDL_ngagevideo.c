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
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_NGAGE

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_ngagevideo.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ NGAGE_VIDEO_DRIVER_NAME "N-Gage"

ਸਥਿਰ ਖਾਲੀ NGAGE_DeleteDevice(SDL_VideoDevice *device);
ਸਥਿਰ bool NGAGE_VideoInit(SDL_VideoDevice *device);
ਸਥਿਰ ਖਾਲੀ NGAGE_VideoQuit(SDL_VideoDevice *device);

ਸਥਿਰ bool NGAGE_GetDisplayBounds(SDL_VideoDevice *device, SDL_VideoDisplay *display, SDL_Rect *rect);
ਸਥਿਰ bool NGAGE_GetDisplayModes(SDL_VideoDevice *device, SDL_VideoDisplay *display);

ਸਥਿਰ ਖਾਲੀ NGAGE_PumpEvents(SDL_VideoDevice *device);

ਸਥਿਰ bool NGAGE_SuspendScreenSaver(SDL_VideoDevice *device);

ਸਥਿਰ SDL_VideoDevice *NGAGE_CreateDevice(ਖਾਲੀ)
{
    SDL_VideoDevice *device;
    SDL_Video_ਅੰਕੜੇ *phdata;

    // Initialize all variables that we clean on shutdown.
    device = (SDL_VideoDevice *)SDL_calloc(1, ਆਕਾਰ(SDL_VideoDevice));
    ਜੇ (!device) {
        SDL_ਬਾਹਰਲਾ_ਦਾ_ਸਮ੍ਰਿਤੀ();
        ਵਾਪਸ (SDL_VideoDevice *)0;
    }

    // Initialize internal N-Gage specific data.
    phdata = (SDL_Video_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(SDL_Video_ਅੰਕੜੇ));
    ਜੇ (!phdata) {
        SDL_ਬਾਹਰਲਾ_ਦਾ_ਸਮ੍ਰਿਤੀ();
        SDL_free(device);
        ਵਾਪਸ (SDL_VideoDevice *)0;
    }

    device->ਅੰਦਰੂਨੀ = phdata;

    device->name = "Nokia N-Gage";

    device->VideoInit = NGAGE_VideoInit;
    device->VideoQuit = NGAGE_VideoQuit;

    device->GetDisplayBounds = NGAGE_GetDisplayBounds;
    device->GetDisplayModes = NGAGE_GetDisplayModes;

    device->PumpEvents = NGAGE_PumpEvents;

    device->SuspendScreenSaver = NGAGE_SuspendScreenSaver;

    device->ਮੁਕਤ = NGAGE_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    ਵਾਪਸ device;
}

VideoBootStrap NGAGE_bootstrap = {
    NGAGE_VIDEO_DRIVER_NAME,
    "N-Gage Video Driver",
    NGAGE_CreateDevice,
    0
};

ਸਥਿਰ ਖਾਲੀ NGAGE_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->ਅੰਦਰੂਨੀ);
    SDL_free(device);
}

ਸਥਿਰ bool NGAGE_VideoInit(SDL_VideoDevice *device)
{
    SDL_Video_ਅੰਕੜੇ *phdata = (SDL_Video_ਅੰਕੜੇ *)device->ਅੰਦਰੂਨੀ;

    ਜੇ (!phdata) {
        ਵਾਪਸ false;
    }

    SDL_zero(phdata->ਬਹੁਲਕ);
    SDL_zero(phdata->display);

    phdata->ਬਹੁਲਕ.w = 176;
    phdata->ਬਹੁਲਕ.h = 208;
    phdata->ਬਹੁਲਕ.refresh_ਦਰ = 60.0f;
    phdata->ਬਹੁਲਕ.format = SDL_PIXELFORMAT_XRGB4444;

    phdata->display.name = "N-Gage";
    phdata->display.desktop_ਬਹੁਲਕ = phdata->ਬਹੁਲਕ;

    ਜੇ (SDL_ਜੋੜੋ_Video_Display(&phdata->display, false) == 0) {
        ਵਾਪਸ false;
    }

    ਵਾਪਸ true;
}

ਸਥਿਰ ਖਾਲੀ NGAGE_VideoQuit(SDL_VideoDevice *device)
{
    SDL_Video_ਅੰਕੜੇ *phdata = (SDL_Video_ਅੰਕੜੇ *)device->ਅੰਦਰੂਨੀ;

    ਜੇ (phdata) {
        SDL_zero(phdata->ਬਹੁਲਕ);
        SDL_zero(phdata->display);
    }
}

ਸਥਿਰ bool NGAGE_GetDisplayBounds(SDL_VideoDevice *device, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ਜੇ (!display) {
        ਵਾਪਸ false;
    }

    rect->x = 0;
    rect->y = 0;
    rect->w = display->current_ਬਹੁਲਕ->w;
    rect->h = display->current_ਬਹੁਲਕ->h;

    ਵਾਪਸ true;
}

ਸਥਿਰ bool NGAGE_GetDisplayModes(SDL_VideoDevice *device, SDL_VideoDisplay *display)
{
    SDL_Video_ਅੰਕੜੇ *phdata = (SDL_Video_ਅੰਕੜੇ *)device->ਅੰਦਰੂਨੀ;
    SDL_Display_ਬਹੁਲਕ ਬਹੁਲਕ;

    SDL_zero(ਬਹੁਲਕ);
    ਬਹੁਲਕ.w = phdata->ਬਹੁਲਕ.w;
    ਬਹੁਲਕ.h = phdata->ਬਹੁਲਕ.h;
    ਬਹੁਲਕ.refresh_ਦਰ = phdata->ਬਹੁਲਕ.refresh_ਦਰ;
    ਬਹੁਲਕ.format = phdata->ਬਹੁਲਕ.format;

    ਜੇ (!SDL_ਜੋੜੋ_Fullscreen_Display_ਬਹੁਲਕ(display, &ਬਹੁਲਕ)) {
        ਵਾਪਸ false;
    }

    ਵਾਪਸ true;
}

#ਅਨ੍ਤਰ੍ਭਾਵ "../../render/ngage/SDL_render_ngage_c.h"

ਸਥਿਰ ਖਾਲੀ NGAGE_PumpEvents(SDL_VideoDevice *device)
{
    NGAGE_Pump_Events_ਅੰਦਰੂਨੀ();
}

ਸਥਿਰ bool NGAGE_SuspendScreenSaver(SDL_VideoDevice *device)
{
    NGAGE_Suspend_Screen_Saver_ਅੰਦਰੂਨੀ(device->suspend_screensaver);
    ਵਾਪਸ true;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_NGAGE
