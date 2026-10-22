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
#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_N3DS

#شامل "../SDL_sysvideo.h"
#شامل "SDL_n3dsevents_c.h"
#شامل "SDL_n3dsframebuffer_c.h"
#شامل "SDL_n3dsswkb.h"
#شامل "SDL_n3dstouch.h"
#شامل "SDL_n3dsvideo.h"

#تعریف_کرو N3DSVID_DRIVER_NAME "n3ds"

ساکن SDL_DisplayID جوڑو_N3_DSDisplay(gfxScreen_t screen);

ساکن bool N3DS_VideoInit(SDL_VideoDevice *_this);
ساکن خالی N3DS_VideoQuit(SDL_VideoDevice *_this);
ساکن bool N3DS_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
ساکن bool N3_DS_سیٹ_Display_منوال(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_منوال *منوال);
ساکن bool N3DS_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
ساکن bool N3_DS_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props);
ساکن خالی N3_DS_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);

ساخت SDL_Display_ڈیٹا
{
    gfxScreen_t screen;
};

ساخت SDL_Display_منوال_ڈیٹا
{
    GSPGPU_FramebufferFormat fmt;
};

ساکن ثابت ساخت
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

ساکن خالی N3DS_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->اندرونی_2);
    SDL_free(device);
}

ساکن SDL_VideoDevice *N3DS_CreateDevice(خالی)
{
    SDL_VideoDevice *device;
    SDL_Video_ڈیٹا *phdata;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    اگر (!device) {
        واپس تہی;
    }

    // Initialize internal data
    phdata = (SDL_Video_ڈیٹا *)SDL_calloc(1, حجم(SDL_Video_ڈیٹا));
    اگر (!phdata) {
        SDL_free(device);
        واپس تہی;
    }

    device->اندرونی_2 = phdata;

    device->VideoInit = N3DS_VideoInit;
    device->VideoQuit = N3DS_VideoQuit;

    device->GetDisplayModes = N3DS_GetDisplayModes;
    device->سیٹ_Display_منوال = N3_DS_سیٹ_Display_منوال;
    device->GetDisplayBounds = N3DS_GetDisplayBounds;

    device->CreateSDLWindow = N3_DS_Create_کھڑکی;
    device->Destroy_کھڑکی = N3_DS_Destroy_کھڑکی;

    device->HasScreenKeyboardSupport = N3DS_HasScreenKeyboardSupport;
    device->آغاز_متن_داخلہ = N3_DS_آغاز_متن_داخلہ;
    device->Stop_متن_داخلہ = N3_DS_Stop_متن_داخلہ;

    device->PumpEvents = N3DS_PumpEvents;

    device->Create_کھڑکی_Framebuffer = SDL_N3_DS_Create_کھڑکی_Framebuffer;
    device->Update_کھڑکی_Framebuffer = SDL_N3_DS_Update_کھڑکی_Framebuffer;
    device->Destroy_کھڑکی_Framebuffer = SDL_N3_DS_Destroy_کھڑکی_Framebuffer;

    device->آزاد = N3DS_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    واپس device;
}

VideoBootStrap N3DS_bootstrap = { N3DSVID_DRIVER_NAME, "N3DS Video Driver", N3DS_CreateDevice, تہی, /* no ShowMessageBox implementation */ false };

ساکن bool N3DS_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *اندرونی_2 = (SDL_Video_ڈیٹا *)_this->اندرونی_2;

    gfxInit(GSP_RGBA8_OES, GSP_RGBA8_OES, false);
    hidInit();

    اندرونی_2->چوٹی_display = جوڑو_N3_DSDisplay(GFX_چوٹی);
    اندرونی_2->touch_display = جوڑو_N3_DSDisplay(GFX_BOTTOM);

    N3DS_InitTouch();
    N3DS_SwkbInit();

    واپس true;
}

ساکن SDL_DisplayID جوڑو_N3_DSDisplay(gfxScreen_t screen)
{
    SDL_Display_منوال منوال;
    SDL_Display_منوال_ڈیٹا *modedata;
    SDL_VideoDisplay display;
    SDL_Display_ڈیٹا *display_driver_ڈیٹا = SDL_calloc(1, حجم(SDL_Display_ڈیٹا));
    اگر (!display_driver_ڈیٹا) {
        واپس 0;
    }

    SDL_zero(منوال);
    SDL_zero(display);

    display_driver_ڈیٹا->screen = screen;

    modedata = SDL_malloc(حجم(SDL_Display_منوال_ڈیٹا));
    اگر (!modedata) {
        واپس 0;
    }

    منوال.w = (screen == GFX_چوٹی) ? GSP_SCREEN_اونچائی_چوٹی : GSP_SCREEN_اونچائی_BOTTOM;
    منوال.h = GSP_SCREEN_چوڑائی;
    منوال.refresh_شرح = 60.0f;
    منوال.format = SDL_PIXELFORMAT_RGBA8888;
    منوال.اندرونی_2 = modedata;
    modedata->fmt = GSP_RGBA8_OES;

    display.name = (screen == GFX_چوٹی) ? "N3DS top screen" : "N3DS bottom screen";
    display.desktop_منوال = منوال;
    display.اندرونی_2 = display_driver_ڈیٹا;

    واپس SDL_جوڑو_Video_Display(&display, false);
}

ساکن خالی N3DS_VideoQuit(SDL_VideoDevice *_this)
{
    N3DS_SwkbQuit();
    N3DS_QuitTouch();

    hidExit();
    gfxExit();
}

ساکن bool N3DS_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_ڈیٹا *displaydata = display->اندرونی_2;
    SDL_Display_منوال_ڈیٹا *modedata;
    SDL_Display_منوال منوال;
    صحیح i;

    برائے (i = 0; i < SDL_arraysize(format_map); i++) {
        modedata = SDL_malloc(حجم(SDL_Display_منوال_ڈیٹا));
        اگر (!modedata)
            جاری;

        SDL_zero(منوال);
        منوال.w = (displaydata->screen == GFX_چوٹی) ? GSP_SCREEN_اونچائی_چوٹی : GSP_SCREEN_اونچائی_BOTTOM;
        منوال.h = GSP_SCREEN_چوڑائی;
        منوال.refresh_شرح = 60.0f;
        منوال.format = format_map[i].pixfmt;
        منوال.اندرونی_2 = modedata;
        modedata->fmt = format_map[i].gspfmt;

        اگر (!SDL_جوڑو_Fullscreen_Display_منوال(display, &منوال)) {
            SDL_free(modedata);
        }
    }

    واپس true;
}

ساکن bool N3_DS_سیٹ_Display_منوال(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_منوال *منوال)
{
    SDL_Display_ڈیٹا *displaydata = display->اندرونی_2;
    SDL_Display_منوال_ڈیٹا *modedata = منوال->اندرونی_2;

    gfx_سیٹ_Screen_Format(displaydata->screen, modedata->fmt);
    واپس true;
}

ساکن bool N3DS_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    SDL_Display_ڈیٹا *driver_ڈیٹا = display->اندرونی_2;

    اگر (!driver_ڈیٹا) {
        واپس false;
    }

    rect->x = 0;
    rect->y = (driver_ڈیٹا->screen == GFX_چوٹی) ? 0 : GSP_SCREEN_چوڑائی;
    rect->w = display->current_منوال->w;
    rect->h = display->current_منوال->h;
    واپس true;
}

ساکن bool N3_DS_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props)
{
    SDL_Display_ڈیٹا *display_ڈیٹا;
    SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2 = (SDL_کھڑکی_ڈیٹا *)SDL_calloc(1, حجم(SDL_کھڑکی_ڈیٹا));
    اگر (!کھڑکی_ڈیٹا_2) {
        واپس false;
    }
    display_ڈیٹا = SDL_Get_Display_Driver_ڈیٹا_For_کھڑکی(کھڑکی);
    کھڑکی_ڈیٹا_2->screen = display_ڈیٹا->screen;
    کھڑکی->اندرونی_2 = کھڑکی_ڈیٹا_2;
    SDL_سیٹ_Keyboard_Focus(کھڑکی);
    واپس true;
}

ساکن خالی N3_DS_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    اگر (!کھڑکی) {
        واپس;
    }
    SDL_free(کھڑکی->اندرونی_2);
}

#اگر_ختم // SDL_VIDEO_DRIVER_N3DS
