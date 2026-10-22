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
#ضمن "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_N3DS

#ضمن "../SDL_sysvideo.h"
#ضمن "SDL_n3dsevents_c.h"
#ضمن "SDL_n3dsframebuffer_c.h"
#ضمن "SDL_n3dsswkb.h"
#ضمن "SDL_n3dstouch.h"
#ضمن "SDL_n3dsvideo.h"

#define N3DSVID_DRIVER_NAME "n3ds"

ساكن SDL_DisplayID AddN3DSDisplay(gfxScreen_t screen);

ساكن bool N3DS_VideoInit(SDL_VideoDevice *_this);
ساكن فراغ N3DS_VideoQuit(SDL_VideoDevice *_this);
ساكن bool N3DS_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
ساكن bool N3DS_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);
ساكن bool N3DS_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
ساكن bool N3DS_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
ساكن فراغ N3DS_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);

بنية SDL_DisplayData
{
    gfxScreen_t screen;
};

بنية SDL_DisplayModeData
{
    GSPGPU_FramebufferFormat fmt;
};

ساكن ثابت بنية
{
    SDL_PixelFormat pixfmt;
    GSPGPU_FramebufferFormat gspfmt;
} format_map[] = {
    { SDL_PIXELFORMAT_RGBA8888, GSP_RGBA8_OES },
    { SDL_PIXELFORMAT_BGR24, GSP_BGR8_OES },
    { SDL_PIXELFORMAT_RGB565, GSP_RGB565_OES },
    { SDL_PIXELFORMAT_RGBA5551, GSP_RGB5_A1_OES },
    { SDL_PIXELFORMAT_RGBA4444, GSP_RGBA4_OES }
};

// N3DS driver bootstrap functions

ساكن فراغ N3DS_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

ساكن SDL_VideoDevice *N3DS_CreateDevice(فراغ)
{
    SDL_VideoDevice *device;
    SDL_VideoData *phdata;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (!device) {
        أرجع عدم;
    }

    // Initialize internal data
    phdata = (SDL_VideoData *)SDL_calloc(1, حجم(SDL_VideoData));
    إذا (!phdata) {
        SDL_free(device);
        أرجع عدم;
    }

    device->internal = phdata;

    device->VideoInit = N3DS_VideoInit;
    device->VideoQuit = N3DS_VideoQuit;

    device->GetDisplayModes = N3DS_GetDisplayModes;
    device->SetDisplayMode = N3DS_SetDisplayMode;
    device->GetDisplayBounds = N3DS_GetDisplayBounds;

    device->CreateSDLWindow = N3DS_CreateWindow;
    device->DestroyWindow = N3DS_DestroyWindow;

    device->HasScreenKeyboardSupport = N3DS_HasScreenKeyboardSupport;
    device->Start_Text_داخلہ = N3_DS_Start_Text_داخلہ;
    device->Stop_Text_داخلہ = N3_DS_Stop_Text_داخلہ;

    device->PumpEvents = N3DS_PumpEvents;

    device->CreateWindowFramebuffer = SDL_N3DS_CreateWindowFramebuffer;
    device->UpdateWindowFramebuffer = SDL_N3DS_UpdateWindowFramebuffer;
    device->DestroyWindowFramebuffer = SDL_N3DS_DestroyWindowFramebuffer;

    device->حرر = N3DS_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    أرجع device;
}

VideoBootStrap N3DS_bootstrap = { N3DSVID_DRIVER_NAME, "N3DS Video Driver", N3DS_CreateDevice, عدم, /* no ShowMessageBox implementation */ false };

ساكن bool N3DS_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoData *internal = (SDL_VideoData *)_this->internal;

    gfxInit(GSP_RGBA8_OES, GSP_RGBA8_OES, false);
    hidInit();

    internal->چوٹی_display = AddN3DSDisplay(GFX_چوٹی);
    internal->touch_display = AddN3DSDisplay(GFX_BOTTOM);

    N3DS_InitTouch();
    N3DS_SwkbInit();

    أرجع true;
}

ساكن SDL_DisplayID AddN3DSDisplay(gfxScreen_t screen)
{
    SDL_DisplayMode mode;
    SDL_DisplayModeData *modedata;
    SDL_VideoDisplay display;
    SDL_DisplayData *display_driver_data = SDL_calloc(1, حجم(SDL_DisplayData));
    إذا (!display_driver_data) {
        أرجع 0;
    }

    SDL_zero(mode);
    SDL_zero(display);

    display_driver_data->screen = screen;

    modedata = SDL_malloc(حجم(SDL_DisplayModeData));
    إذا (!modedata) {
        أرجع 0;
    }

    mode.w = (screen == GFX_چوٹی) ? GSP_SCREEN_HEIGHT_چوٹی : GSP_SCREEN_HEIGHT_BOTTOM;
    mode.h = GSP_SCREEN_WIDTH;
    mode.refresh_rate = 60.0f;
    mode.format = SDL_PIXELFORMAT_RGBA8888;
    mode.internal = modedata;
    modedata->fmt = GSP_RGBA8_OES;

    display.name = (screen == GFX_چوٹی) ? "N3DS top screen" : "N3DS bottom screen";
    display.desktop_mode = mode;
    display.internal = display_driver_data;

    أرجع SDL_AddVideoDisplay(&display, false);
}

ساكن فراغ N3DS_VideoQuit(SDL_VideoDevice *_this)
{
    N3DS_SwkbQuit();
    N3DS_QuitTouch();

    hidExit();
    gfxExit();
}

ساكن bool N3DS_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_DisplayData *displaydata = display->internal;
    SDL_DisplayModeData *modedata;
    SDL_DisplayMode mode;
    صحيح i;

    لكل (i = 0; i < SDL_arraysize(format_map); i++) {
        modedata = SDL_malloc(حجم(SDL_DisplayModeData));
        إذا (!modedata)
            استمر;

        SDL_zero(mode);
        mode.w = (displaydata->screen == GFX_چوٹی) ? GSP_SCREEN_HEIGHT_چوٹی : GSP_SCREEN_HEIGHT_BOTTOM;
        mode.h = GSP_SCREEN_WIDTH;
        mode.refresh_rate = 60.0f;
        mode.format = format_map[i].pixfmt;
        mode.internal = modedata;
        modedata->fmt = format_map[i].gspfmt;

        إذا (!SDL_AddFullscreenDisplayMode(display, &mode)) {
            SDL_free(modedata);
        }
    }

    أرجع true;
}

ساكن bool N3DS_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    SDL_DisplayData *displaydata = display->internal;
    SDL_DisplayModeData *modedata = mode->internal;

    gfxSetScreenFormat(displaydata->screen, modedata->fmt);
    أرجع true;
}

ساكن bool N3DS_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    SDL_DisplayData *driver_data = display->internal;

    إذا (!driver_data) {
        أرجع false;
    }

    rect->x = 0;
    rect->y = (driver_data->screen == GFX_چوٹی) ? 0 : GSP_SCREEN_WIDTH;
    rect->w = display->current_mode->w;
    rect->h = display->current_mode->h;
    أرجع true;
}

ساكن bool N3DS_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_DisplayData *display_data;
    SDL_WindowData *window_data = (SDL_WindowData *)SDL_calloc(1, حجم(SDL_WindowData));
    إذا (!window_data) {
        أرجع false;
    }
    display_data = SDL_GetDisplayDriverDataForWindow(window);
    window_data->screen = display_data->screen;
    window->internal = window_data;
    SDL_SetKeyboardFocus(window);
    أرجع true;
}

ساكن فراغ N3DS_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    إذا (!window) {
        أرجع;
    }
    SDL_free(window->internal);
}

#endif // SDL_VIDEO_DRIVER_N3DS
