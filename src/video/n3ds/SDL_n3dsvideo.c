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
#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_N3DS

#অন্তর্ভাব "../SDL_sysvideo.h"
#অন্তর্ভাব "SDL_n3dsevents_c.h"
#অন্তর্ভাব "SDL_n3dsframebuffer_c.h"
#অন্তর্ভাব "SDL_n3dsswkb.h"
#অন্তর্ভাব "SDL_n3dstouch.h"
#অন্তর্ভাব "SDL_n3dsvideo.h"

#define N3DSVID_DRIVER_NAME "n3ds"

স্থির SDL_DisplayID AddN3DSDisplay(gfxScreen_t screen);

স্থির bool N3DS_VideoInit(SDL_VideoDevice *_this);
স্থির শূন্য N3DS_VideoQuit(SDL_VideoDevice *_this);
স্থির bool N3DS_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
স্থির bool N3DS_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);
স্থির bool N3DS_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
স্থির bool N3DS_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
স্থির শূন্য N3DS_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);

কাঠামো SDL_Display_তথ্য
{
    gfxScreen_t screen;
};

কাঠামো SDL_Display_Mode_তথ্য
{
    GSPGPU_FramebufferFormat fmt;
};

স্থির ধ্রুবক কাঠামো
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

স্থির শূন্য N3DS_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

স্থির SDL_VideoDevice *N3DS_CreateDevice(শূন্য)
{
    SDL_VideoDevice *device;
    SDL_Video_তথ্য *phdata;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, আকার(SDL_VideoDevice));
    যদি (!device) {
        ফেরত ফাঁকা;
    }

    // Initialize internal data
    phdata = (SDL_Video_তথ্য *)SDL_calloc(1, আকার(SDL_Video_তথ্য));
    যদি (!phdata) {
        SDL_free(device);
        ফেরত ফাঁকা;
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
    device->Start_Text_প্রবেশ = N3_DS_Start_Text_প্রবেশ;
    device->Stop_Text_প্রবেশ = N3_DS_Stop_Text_প্রবেশ;

    device->PumpEvents = N3DS_PumpEvents;

    device->CreateWindowFramebuffer = SDL_N3DS_CreateWindowFramebuffer;
    device->UpdateWindowFramebuffer = SDL_N3DS_UpdateWindowFramebuffer;
    device->DestroyWindowFramebuffer = SDL_N3DS_DestroyWindowFramebuffer;

    device->মুক্ত = N3DS_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    ফেরত device;
}

VideoBootStrap N3DS_bootstrap = { N3DSVID_DRIVER_NAME, "N3DS Video Driver", N3DS_CreateDevice, ফাঁকা, /* no ShowMessageBox implementation */ false };

স্থির bool N3DS_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_তথ্য *internal = (SDL_Video_তথ্য *)_this->internal;

    gfxInit(GSP_RGBA8_OES, GSP_RGBA8_OES, false);
    hidInit();

    internal->শীর্ষ_display = AddN3DSDisplay(GFX_শীর্ষ);
    internal->touch_display = AddN3DSDisplay(GFX_BOTTOM);

    N3DS_InitTouch();
    N3DS_SwkbInit();

    ফেরত true;
}

স্থির SDL_DisplayID AddN3DSDisplay(gfxScreen_t screen)
{
    SDL_DisplayMode mode;
    SDL_Display_Mode_তথ্য *modedata;
    SDL_VideoDisplay display;
    SDL_Display_তথ্য *display_driver_তথ্য = SDL_calloc(1, আকার(SDL_Display_তথ্য));
    যদি (!display_driver_তথ্য) {
        ফেরত 0;
    }

    SDL_zero(mode);
    SDL_zero(display);

    display_driver_তথ্য->screen = screen;

    modedata = SDL_malloc(আকার(SDL_Display_Mode_তথ্য));
    যদি (!modedata) {
        ফেরত 0;
    }

    mode.w = (screen == GFX_শীর্ষ) ? GSP_SCREEN_HEIGHT_শীর্ষ : GSP_SCREEN_HEIGHT_BOTTOM;
    mode.h = GSP_SCREEN_WIDTH;
    mode.refresh_rate = 60.0f;
    mode.format = SDL_PIXELFORMAT_RGBA8888;
    mode.internal = modedata;
    modedata->fmt = GSP_RGBA8_OES;

    display.name = (screen == GFX_শীর্ষ) ? "N3DS top screen" : "N3DS bottom screen";
    display.desktop_mode = mode;
    display.internal = display_driver_তথ্য;

    ফেরত SDL_AddVideoDisplay(&display, false);
}

স্থির শূন্য N3DS_VideoQuit(SDL_VideoDevice *_this)
{
    N3DS_SwkbQuit();
    N3DS_QuitTouch();

    hidExit();
    gfxExit();
}

স্থির bool N3DS_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_তথ্য *displaydata = display->internal;
    SDL_Display_Mode_তথ্য *modedata;
    SDL_DisplayMode mode;
    পূর্ণসংখ্যা i;

    জন্য (i = 0; i < SDL_arraysize(format_map); i++) {
        modedata = SDL_malloc(আকার(SDL_Display_Mode_তথ্য));
        যদি (!modedata)
            চালু;

        SDL_zero(mode);
        mode.w = (displaydata->screen == GFX_শীর্ষ) ? GSP_SCREEN_HEIGHT_শীর্ষ : GSP_SCREEN_HEIGHT_BOTTOM;
        mode.h = GSP_SCREEN_WIDTH;
        mode.refresh_rate = 60.0f;
        mode.format = format_map[i].pixfmt;
        mode.internal = modedata;
        modedata->fmt = format_map[i].gspfmt;

        যদি (!SDL_AddFullscreenDisplayMode(display, &mode)) {
            SDL_free(modedata);
        }
    }

    ফেরত true;
}

স্থির bool N3DS_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    SDL_Display_তথ্য *displaydata = display->internal;
    SDL_Display_Mode_তথ্য *modedata = mode->internal;

    gfxSetScreenFormat(displaydata->screen, modedata->fmt);
    ফেরত true;
}

স্থির bool N3DS_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    SDL_Display_তথ্য *driver_তথ্য = display->internal;

    যদি (!driver_তথ্য) {
        ফেরত false;
    }

    rect->x = 0;
    rect->y = (driver_তথ্য->screen == GFX_শীর্ষ) ? 0 : GSP_SCREEN_WIDTH;
    rect->w = display->current_mode->w;
    rect->h = display->current_mode->h;
    ফেরত true;
}

স্থির bool N3DS_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_Display_তথ্য *display_তথ্য;
    SDL_Window_তথ্য *window_তথ্য_2 = (SDL_Window_তথ্য *)SDL_calloc(1, আকার(SDL_Window_তথ্য));
    যদি (!window_তথ্য_2) {
        ফেরত false;
    }
    display_তথ্য = SDL_Get_Display_Driver_তথ্য_For_Window(window);
    window_তথ্য_2->screen = display_তথ্য->screen;
    window->internal = window_তথ্য_2;
    SDL_SetKeyboardFocus(window);
    ফেরত true;
}

স্থির শূন্য N3DS_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    যদি (!window) {
        ফেরত;
    }
    SDL_free(window->internal);
}

#endif // SDL_VIDEO_DRIVER_N3DS
