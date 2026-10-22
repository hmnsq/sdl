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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_N3DS

#समावेश "../SDL_sysvideo.h"
#समावेश "SDL_n3dsevents_c.h"
#समावेश "SDL_n3dsframebuffer_c.h"
#समावेश "SDL_n3dsswkb.h"
#समावेश "SDL_n3dstouch.h"
#समावेश "SDL_n3dsvideo.h"

#घोषणा N3DSVID_DRIVER_NAME "n3ds"

अटल SDL_DisplayID AddN3DSDisplay(gfxScreen_t screen);

अटल bool N3DS_VideoInit(SDL_VideoDevice *_this);
अटल व्योम N3DS_VideoQuit(SDL_VideoDevice *_this);
अटल bool N3DS_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
अटल bool N3DS_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);
अटल bool N3DS_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
अटल bool N3DS_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
अटल व्योम N3DS_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);

काष्ठा SDL_Display_तथ्य
{
    gfxScreen_t screen;
};

काष्ठा SDL_Display_Mode_तथ्य
{
    GSPGPU_FramebufferFormat fmt;
};

अटल स्थिर काष्ठा
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

अटल व्योम N3DS_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

अटल SDL_VideoDevice *N3DS_CreateDevice(व्योम)
{
    SDL_VideoDevice *device;
    SDL_Video_तथ्य *phdata;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, माप(SDL_VideoDevice));
    अगर (!device) {
        वापस शून्य;
    }

    // Initialize internal data
    phdata = (SDL_Video_तथ्य *)SDL_calloc(1, माप(SDL_Video_तथ्य));
    अगर (!phdata) {
        SDL_free(device);
        वापस शून्य;
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
    device->Start_Text_निवेश = N3_DS_Start_Text_निवेश;
    device->Stop_Text_निवेश = N3_DS_Stop_Text_निवेश;

    device->PumpEvents = N3DS_PumpEvents;

    device->CreateWindowFramebuffer = SDL_N3DS_CreateWindowFramebuffer;
    device->UpdateWindowFramebuffer = SDL_N3DS_UpdateWindowFramebuffer;
    device->DestroyWindowFramebuffer = SDL_N3DS_DestroyWindowFramebuffer;

    device->मुक्त = N3DS_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    वापस device;
}

VideoBootStrap N3DS_bootstrap = { N3DSVID_DRIVER_NAME, "N3DS Video Driver", N3DS_CreateDevice, शून्य, /* no ShowMessageBox implementation */ false };

अटल bool N3DS_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *internal = (SDL_Video_तथ्य *)_this->internal;

    gfxInit(GSP_RGBA8_OES, GSP_RGBA8_OES, false);
    hidInit();

    internal->शीर्ष_display = AddN3DSDisplay(GFX_शीर्ष);
    internal->touch_display = AddN3DSDisplay(GFX_BOTTOM);

    N3DS_InitTouch();
    N3DS_SwkbInit();

    वापस true;
}

अटल SDL_DisplayID AddN3DSDisplay(gfxScreen_t screen)
{
    SDL_DisplayMode mode;
    SDL_Display_Mode_तथ्य *modedata;
    SDL_VideoDisplay display;
    SDL_Display_तथ्य *display_driver_तथ्य = SDL_calloc(1, माप(SDL_Display_तथ्य));
    अगर (!display_driver_तथ्य) {
        वापस 0;
    }

    SDL_zero(mode);
    SDL_zero(display);

    display_driver_तथ्य->screen = screen;

    modedata = SDL_malloc(माप(SDL_Display_Mode_तथ्य));
    अगर (!modedata) {
        वापस 0;
    }

    mode.w = (screen == GFX_शीर्ष) ? GSP_SCREEN_HEIGHT_शीर्ष : GSP_SCREEN_HEIGHT_BOTTOM;
    mode.h = GSP_SCREEN_WIDTH;
    mode.refresh_rate = 60.0f;
    mode.format = SDL_PIXELFORMAT_RGBA8888;
    mode.internal = modedata;
    modedata->fmt = GSP_RGBA8_OES;

    display.name = (screen == GFX_शीर्ष) ? "N3DS top screen" : "N3DS bottom screen";
    display.desktop_mode = mode;
    display.internal = display_driver_तथ्य;

    वापस SDL_AddVideoDisplay(&display, false);
}

अटल व्योम N3DS_VideoQuit(SDL_VideoDevice *_this)
{
    N3DS_SwkbQuit();
    N3DS_QuitTouch();

    hidExit();
    gfxExit();
}

अटल bool N3DS_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_तथ्य *displaydata = display->internal;
    SDL_Display_Mode_तथ्य *modedata;
    SDL_DisplayMode mode;
    पूर्णांक i;

    क्रम (i = 0; i < SDL_arraysize(format_map); i++) {
        modedata = SDL_malloc(माप(SDL_Display_Mode_तथ्य));
        अगर (!modedata)
            जारी;

        SDL_zero(mode);
        mode.w = (displaydata->screen == GFX_शीर्ष) ? GSP_SCREEN_HEIGHT_शीर्ष : GSP_SCREEN_HEIGHT_BOTTOM;
        mode.h = GSP_SCREEN_WIDTH;
        mode.refresh_rate = 60.0f;
        mode.format = format_map[i].pixfmt;
        mode.internal = modedata;
        modedata->fmt = format_map[i].gspfmt;

        अगर (!SDL_AddFullscreenDisplayMode(display, &mode)) {
            SDL_free(modedata);
        }
    }

    वापस true;
}

अटल bool N3DS_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    SDL_Display_तथ्य *displaydata = display->internal;
    SDL_Display_Mode_तथ्य *modedata = mode->internal;

    gfxSetScreenFormat(displaydata->screen, modedata->fmt);
    वापस true;
}

अटल bool N3DS_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    SDL_Display_तथ्य *driver_तथ्य = display->internal;

    अगर (!driver_तथ्य) {
        वापस false;
    }

    rect->x = 0;
    rect->y = (driver_तथ्य->screen == GFX_शीर्ष) ? 0 : GSP_SCREEN_WIDTH;
    rect->w = display->current_mode->w;
    rect->h = display->current_mode->h;
    वापस true;
}

अटल bool N3DS_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_Display_तथ्य *display_तथ्य;
    SDL_Window_तथ्य *window_तथ्य_2 = (SDL_Window_तथ्य *)SDL_calloc(1, माप(SDL_Window_तथ्य));
    अगर (!window_तथ्य_2) {
        वापस false;
    }
    display_तथ्य = SDL_Get_Display_Driver_तथ्य_For_Window(window);
    window_तथ्य_2->screen = display_तथ्य->screen;
    window->internal = window_तथ्य_2;
    SDL_SetKeyboardFocus(window);
    वापस true;
}

अटल व्योम N3DS_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    अगर (!window) {
        वापस;
    }
    SDL_free(window->internal);
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_N3DS
