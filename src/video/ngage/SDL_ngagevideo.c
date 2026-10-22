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
#అన్తర్భావ "../SDL_sysvideo.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_NGAGE

#అన్తర్భావ "SDL_ngagevideo.h"

#నిర్వచించు NGAGE_VIDEO_DRIVER_NAME "N-Gage"

స్థిర శూన్య NGAGE_DeleteDevice(SDL_VideoDevice *device);
స్థిర bool NGAGE_VideoInit(SDL_VideoDevice *device);
స్థిర శూన్య NGAGE_VideoQuit(SDL_VideoDevice *device);

స్థిర bool NGAGE_GetDisplayBounds(SDL_VideoDevice *device, SDL_VideoDisplay *display, SDL_Rect *rect);
స్థిర bool NGAGE_GetDisplayModes(SDL_VideoDevice *device, SDL_VideoDisplay *display);

స్థిర శూన్య NGAGE_PumpEvents(SDL_VideoDevice *device);

స్థిర bool NGAGE_SuspendScreenSaver(SDL_VideoDevice *device);

స్థిర SDL_VideoDevice *NGAGE_CreateDevice(శూన్య)
{
    SDL_VideoDevice *device;
    SDL_Video_దత్తాంశం *phdata;

    // Initialize all variables that we clean on shutdown.
    device = (SDL_VideoDevice *)SDL_calloc(1, పరిమాణం(SDL_VideoDevice));
    ఒకవేళ (!device) {
        SDL_బహిర్గతం_యొక్క_జ్ఞాపకం();
        తిరిగి (SDL_VideoDevice *)0;
    }

    // Initialize internal N-Gage specific data.
    phdata = (SDL_Video_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_Video_దత్తాంశం));
    ఒకవేళ (!phdata) {
        SDL_బహిర్గతం_యొక్క_జ్ఞాపకం();
        SDL_free(device);
        తిరిగి (SDL_VideoDevice *)0;
    }

    device->అంతర్గత = phdata;

    device->name = "Nokia N-Gage";

    device->VideoInit = NGAGE_VideoInit;
    device->VideoQuit = NGAGE_VideoQuit;

    device->GetDisplayBounds = NGAGE_GetDisplayBounds;
    device->GetDisplayModes = NGAGE_GetDisplayModes;

    device->PumpEvents = NGAGE_PumpEvents;

    device->SuspendScreenSaver = NGAGE_SuspendScreenSaver;

    device->విడుదల = NGAGE_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    తిరిగి device;
}

VideoBootStrap NGAGE_bootstrap = {
    NGAGE_VIDEO_DRIVER_NAME,
    "N-Gage Video Driver",
    NGAGE_CreateDevice,
    0
};

స్థిర శూన్య NGAGE_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->అంతర్గత);
    SDL_free(device);
}

స్థిర bool NGAGE_VideoInit(SDL_VideoDevice *device)
{
    SDL_Video_దత్తాంశం *phdata = (SDL_Video_దత్తాంశం *)device->అంతర్గత;

    ఒకవేళ (!phdata) {
        తిరిగి false;
    }

    SDL_zero(phdata->బహుళకం);
    SDL_zero(phdata->display);

    phdata->బహుళకం.w = 176;
    phdata->బహుళకం.h = 208;
    phdata->బహుళకం.refresh_రేటు = 60.0f;
    phdata->బహుళకం.format = SDL_PIXELFORMAT_XRGB4444;

    phdata->display.name = "N-Gage";
    phdata->display.desktop_బహుళకం = phdata->బహుళకం;

    ఒకవేళ (SDL_కూడు_Video_Display(&phdata->display, false) == 0) {
        తిరిగి false;
    }

    తిరిగి true;
}

స్థిర శూన్య NGAGE_VideoQuit(SDL_VideoDevice *device)
{
    SDL_Video_దత్తాంశం *phdata = (SDL_Video_దత్తాంశం *)device->అంతర్గత;

    ఒకవేళ (phdata) {
        SDL_zero(phdata->బహుళకం);
        SDL_zero(phdata->display);
    }
}

స్థిర bool NGAGE_GetDisplayBounds(SDL_VideoDevice *device, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ఒకవేళ (!display) {
        తిరిగి false;
    }

    rect->x = 0;
    rect->y = 0;
    rect->w = display->current_బహుళకం->w;
    rect->h = display->current_బహుళకం->h;

    తిరిగి true;
}

స్థిర bool NGAGE_GetDisplayModes(SDL_VideoDevice *device, SDL_VideoDisplay *display)
{
    SDL_Video_దత్తాంశం *phdata = (SDL_Video_దత్తాంశం *)device->అంతర్గత;
    SDL_Display_బహుళకం బహుళకం;

    SDL_zero(బహుళకం);
    బహుళకం.w = phdata->బహుళకం.w;
    బహుళకం.h = phdata->బహుళకం.h;
    బహుళకం.refresh_రేటు = phdata->బహుళకం.refresh_రేటు;
    బహుళకం.format = phdata->బహుళకం.format;

    ఒకవేళ (!SDL_కూడు_Fullscreen_Display_బహుళకం(display, &బహుళకం)) {
        తిరిగి false;
    }

    తిరిగి true;
}

#అన్తర్భావ "../../render/ngage/SDL_render_ngage_c.h"

స్థిర శూన్య NGAGE_PumpEvents(SDL_VideoDevice *device)
{
    NGAGE_Pump_Events_అంతర్గత();
}

స్థిర bool NGAGE_SuspendScreenSaver(SDL_VideoDevice *device)
{
    NGAGE_Suspend_Screen_Saver_అంతర్గత(device->suspend_screensaver);
    తిరిగి true;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_NGAGE
