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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_N3DS

#ضمن "../SDL_sysvideo.h"
#ضمن "SDL_n3dsevents_c.h"
#ضمن "SDL_n3dsframebuffer_c.h"
#ضمن "SDL_n3dsswkb.h"
#ضمن "SDL_n3dstouch.h"
#ضمن "SDL_n3dsvideo.h"

#تعریف_کرو N3DSVID_DRIVER_NAME "n3ds"

ساكن SDL_DisplayID جوڑو_N3_DSDisplay(gfxScreen_t screen);

ساكن bool N3DS_VideoInit(SDL_VideoDevice *_this);
ساكن فراغ N3DS_VideoQuit(SDL_VideoDevice *_this);
ساكن bool N3DS_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
ساكن bool N3_DS_سیٹ_Display_منوال(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_منوال *منوال);
ساكن bool N3DS_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
ساكن bool N3_DS_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props);
ساكن فراغ N3_DS_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);

بنية SDL_Display_انکڑے
{
    gfxScreen_t screen;
};

بنية SDL_Display_منوال_انکڑے
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
    SDL_free(device->اندرونی);
    SDL_free(device);
}

ساكن SDL_VideoDevice *N3DS_CreateDevice(فراغ)
{
    SDL_VideoDevice *device;
    SDL_Video_انکڑے *phdata;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (!device) {
        أرجع عدم;
    }

    // Initialize internal data
    phdata = (SDL_Video_انکڑے *)SDL_calloc(1, حجم(SDL_Video_انکڑے));
    إذا (!phdata) {
        SDL_free(device);
        أرجع عدم;
    }

    device->اندرونی = phdata;

    device->VideoInit = N3DS_VideoInit;
    device->VideoQuit = N3DS_VideoQuit;

    device->GetDisplayModes = N3DS_GetDisplayModes;
    device->سیٹ_Display_منوال = N3_DS_سیٹ_Display_منوال;
    device->GetDisplayBounds = N3DS_GetDisplayBounds;

    device->CreateSDLWindow = N3_DS_Create_کھڑکی;
    device->Destroy_کھڑکی = N3_DS_Destroy_کھڑکی;

    device->HasScreenKeyboardSupport = N3DS_HasScreenKeyboardSupport;
    device->شروع_متن_داخلہ = N3_DS_شروع_متن_داخلہ;
    device->Stop_متن_داخلہ = N3_DS_Stop_متن_داخلہ;

    device->PumpEvents = N3DS_PumpEvents;

    device->Create_کھڑکی_Framebuffer = SDL_N3_DS_Create_کھڑکی_Framebuffer;
    device->Update_کھڑکی_Framebuffer = SDL_N3_DS_Update_کھڑکی_Framebuffer;
    device->Destroy_کھڑکی_Framebuffer = SDL_N3_DS_Destroy_کھڑکی_Framebuffer;

    device->حرر = N3DS_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    أرجع device;
}

VideoBootStrap N3DS_bootstrap = { N3DSVID_DRIVER_NAME, "N3DS Video Driver", N3DS_CreateDevice, عدم, /* no ShowMessageBox implementation */ false };

ساكن bool N3DS_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_انکڑے *اندرونی = (SDL_Video_انکڑے *)_this->اندرونی;

    gfxInit(GSP_RGBA8_OES, GSP_RGBA8_OES, false);
    hidInit();

    اندرونی->چوٹی_display = جوڑو_N3_DSDisplay(GFX_چوٹی);
    اندرونی->touch_display = جوڑو_N3_DSDisplay(GFX_BOTTOM);

    N3DS_InitTouch();
    N3DS_SwkbInit();

    أرجع true;
}

ساكن SDL_DisplayID جوڑو_N3_DSDisplay(gfxScreen_t screen)
{
    SDL_Display_منوال منوال;
    SDL_Display_منوال_انکڑے *modedata;
    SDL_VideoDisplay display;
    SDL_Display_انکڑے *display_driver_انکڑے = SDL_calloc(1, حجم(SDL_Display_انکڑے));
    إذا (!display_driver_انکڑے) {
        أرجع 0;
    }

    SDL_zero(منوال);
    SDL_zero(display);

    display_driver_انکڑے->screen = screen;

    modedata = SDL_malloc(حجم(SDL_Display_منوال_انکڑے));
    إذا (!modedata) {
        أرجع 0;
    }

    منوال.w = (screen == GFX_چوٹی) ? GSP_SCREEN_اچائی_چوٹی : GSP_SCREEN_اچائی_BOTTOM;
    منوال.h = GSP_SCREEN_چوڑائی;
    منوال.refresh_شرح = 60.0f;
    منوال.format = SDL_PIXELFORMAT_RGBA8888;
    منوال.اندرونی = modedata;
    modedata->fmt = GSP_RGBA8_OES;

    display.name = (screen == GFX_چوٹی) ? "N3DS top screen" : "N3DS bottom screen";
    display.desktop_منوال = منوال;
    display.اندرونی = display_driver_انکڑے;

    أرجع SDL_جوڑو_Video_Display(&display, false);
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
    SDL_Display_انکڑے *displaydata = display->اندرونی;
    SDL_Display_منوال_انکڑے *modedata;
    SDL_Display_منوال منوال;
    صحيح i;

    لكل (i = 0; i < SDL_arraysize(format_map); i++) {
        modedata = SDL_malloc(حجم(SDL_Display_منوال_انکڑے));
        إذا (!modedata)
            استمر;

        SDL_zero(منوال);
        منوال.w = (displaydata->screen == GFX_چوٹی) ? GSP_SCREEN_اچائی_چوٹی : GSP_SCREEN_اچائی_BOTTOM;
        منوال.h = GSP_SCREEN_چوڑائی;
        منوال.refresh_شرح = 60.0f;
        منوال.format = format_map[i].pixfmt;
        منوال.اندرونی = modedata;
        modedata->fmt = format_map[i].gspfmt;

        إذا (!SDL_جوڑو_Fullscreen_Display_منوال(display, &منوال)) {
            SDL_free(modedata);
        }
    }

    أرجع true;
}

ساكن bool N3_DS_سیٹ_Display_منوال(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_منوال *منوال)
{
    SDL_Display_انکڑے *displaydata = display->اندرونی;
    SDL_Display_منوال_انکڑے *modedata = منوال->اندرونی;

    gfx_سیٹ_Screen_Format(displaydata->screen, modedata->fmt);
    أرجع true;
}

ساكن bool N3DS_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    SDL_Display_انکڑے *driver_انکڑے = display->اندرونی;

    إذا (!driver_انکڑے) {
        أرجع false;
    }

    rect->x = 0;
    rect->y = (driver_انکڑے->screen == GFX_چوٹی) ? 0 : GSP_SCREEN_چوڑائی;
    rect->w = display->current_منوال->w;
    rect->h = display->current_منوال->h;
    أرجع true;
}

ساكن bool N3_DS_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props)
{
    SDL_Display_انکڑے *display_انکڑے;
    SDL_کھڑکی_انکڑے *کھڑکی_انکڑے_2 = (SDL_کھڑکی_انکڑے *)SDL_calloc(1, حجم(SDL_کھڑکی_انکڑے));
    إذا (!کھڑکی_انکڑے_2) {
        أرجع false;
    }
    display_انکڑے = SDL_Get_Display_Driver_انکڑے_For_کھڑکی(کھڑکی);
    کھڑکی_انکڑے_2->screen = display_انکڑے->screen;
    کھڑکی->اندرونی = کھڑکی_انکڑے_2;
    SDL_سیٹ_Keyboard_Focus(کھڑکی);
    أرجع true;
}

ساكن فراغ N3_DS_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    إذا (!کھڑکی) {
        أرجع;
    }
    SDL_free(کھڑکی->اندرونی);
}

#جے_انت // SDL_VIDEO_DRIVER_N3DS
