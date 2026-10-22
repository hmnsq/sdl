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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_N3DS

#ضمن "../SDL_sysvideo.h"
#ضمن "SDL_n3dsevents_c.h"
#ضمن "SDL_n3dsframebuffer_c.h"
#ضمن "SDL_n3dsswkb.h"
#ضمن "SDL_n3dstouch.h"
#ضمن "SDL_n3dsvideo.h"

#تعریف_کن N3DSVID_DRIVER_NAME "n3ds"

ساكن SDL_DisplayID جمع_کن_N3_DSDisplay(gfxScreen_t screen);

ساكن bool N3DS_VideoInit(SDL_VideoDevice *_this);
ساكن فراغ N3DS_VideoQuit(SDL_VideoDevice *_this);
ساكن bool N3DS_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
ساكن bool N3_DS_مجموعه_Display_نما(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_نما *نما);
ساكن bool N3DS_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
ساكن bool N3_DS_Create_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID create_props);
ساكن فراغ N3_DS_Destroy_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);

بنية SDL_Display_داده
{
    gfxScreen_t screen;
};

بنية SDL_Display_نما_داده
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
    SDL_free(device->داخلی);
    SDL_free(device);
}

ساكن SDL_VideoDevice *N3DS_CreateDevice(فراغ)
{
    SDL_VideoDevice *device;
    SDL_Video_داده *phdata;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (!device) {
        أرجع عدم;
    }

    // Initialize internal data
    phdata = (SDL_Video_داده *)SDL_calloc(1, حجم(SDL_Video_داده));
    إذا (!phdata) {
        SDL_free(device);
        أرجع عدم;
    }

    device->داخلی = phdata;

    device->VideoInit = N3DS_VideoInit;
    device->VideoQuit = N3DS_VideoQuit;

    device->GetDisplayModes = N3DS_GetDisplayModes;
    device->مجموعه_Display_نما = N3_DS_مجموعه_Display_نما;
    device->GetDisplayBounds = N3DS_GetDisplayBounds;

    device->CreateSDLWindow = N3_DS_Create_پنجره;
    device->Destroy_پنجره = N3_DS_Destroy_پنجره;

    device->HasScreenKeyboardSupport = N3DS_HasScreenKeyboardSupport;
    device->شروع_متن_درون_داد = N3_DS_شروع_متن_درون_داد;
    device->Stop_متن_درون_داد = N3_DS_Stop_متن_درون_داد;

    device->PumpEvents = N3DS_PumpEvents;

    device->Create_پنجره_Framebuffer = SDL_N3_DS_Create_پنجره_Framebuffer;
    device->Update_پنجره_Framebuffer = SDL_N3_DS_Update_پنجره_Framebuffer;
    device->Destroy_پنجره_Framebuffer = SDL_N3_DS_Destroy_پنجره_Framebuffer;

    device->حرر = N3DS_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    أرجع device;
}

VideoBootStrap N3DS_bootstrap = { N3DSVID_DRIVER_NAME, "N3DS Video Driver", N3DS_CreateDevice, عدم, /* no ShowMessageBox implementation */ false };

ساكن bool N3DS_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_داده *داخلی = (SDL_Video_داده *)_this->داخلی;

    gfxInit(GSP_RGBA8_OES, GSP_RGBA8_OES, false);
    hidInit();

    داخلی->بالاترین_display = جمع_کن_N3_DSDisplay(GFX_بالاترین);
    داخلی->touch_display = جمع_کن_N3_DSDisplay(GFX_BOTTOM);

    N3DS_InitTouch();
    N3DS_SwkbInit();

    أرجع true;
}

ساكن SDL_DisplayID جمع_کن_N3_DSDisplay(gfxScreen_t screen)
{
    SDL_Display_نما نما;
    SDL_Display_نما_داده *modedata;
    SDL_VideoDisplay display;
    SDL_Display_داده *display_driver_داده = SDL_calloc(1, حجم(SDL_Display_داده));
    إذا (!display_driver_داده) {
        أرجع 0;
    }

    SDL_zero(نما);
    SDL_zero(display);

    display_driver_داده->screen = screen;

    modedata = SDL_malloc(حجم(SDL_Display_نما_داده));
    إذا (!modedata) {
        أرجع 0;
    }

    نما.w = (screen == GFX_بالاترین) ? GSP_SCREEN_ارتفاع_بالاترین : GSP_SCREEN_ارتفاع_BOTTOM;
    نما.h = GSP_SCREEN_عرض;
    نما.refresh_نرخ = 60.0f;
    نما.format = SDL_PIXELFORMAT_RGBA8888;
    نما.داخلی = modedata;
    modedata->fmt = GSP_RGBA8_OES;

    display.name = (screen == GFX_بالاترین) ? "N3DS top screen" : "N3DS bottom screen";
    display.desktop_نما = نما;
    display.داخلی = display_driver_داده;

    أرجع SDL_جمع_کن_Video_Display(&display, false);
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
    SDL_Display_داده *displaydata = display->داخلی;
    SDL_Display_نما_داده *modedata;
    SDL_Display_نما نما;
    صحيح i;

    لكل (i = 0; i < SDL_arraysize(format_map); i++) {
        modedata = SDL_malloc(حجم(SDL_Display_نما_داده));
        إذا (!modedata)
            استمر;

        SDL_zero(نما);
        نما.w = (displaydata->screen == GFX_بالاترین) ? GSP_SCREEN_ارتفاع_بالاترین : GSP_SCREEN_ارتفاع_BOTTOM;
        نما.h = GSP_SCREEN_عرض;
        نما.refresh_نرخ = 60.0f;
        نما.format = format_map[i].pixfmt;
        نما.داخلی = modedata;
        modedata->fmt = format_map[i].gspfmt;

        إذا (!SDL_جمع_کن_Fullscreen_Display_نما(display, &نما)) {
            SDL_free(modedata);
        }
    }

    أرجع true;
}

ساكن bool N3_DS_مجموعه_Display_نما(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_نما *نما)
{
    SDL_Display_داده *displaydata = display->داخلی;
    SDL_Display_نما_داده *modedata = نما->داخلی;

    gfx_مجموعه_Screen_Format(displaydata->screen, modedata->fmt);
    أرجع true;
}

ساكن bool N3DS_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    SDL_Display_داده *driver_داده = display->داخلی;

    إذا (!driver_داده) {
        أرجع false;
    }

    rect->x = 0;
    rect->y = (driver_داده->screen == GFX_بالاترین) ? 0 : GSP_SCREEN_عرض;
    rect->w = display->current_نما->w;
    rect->h = display->current_نما->h;
    أرجع true;
}

ساكن bool N3_DS_Create_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID create_props)
{
    SDL_Display_داده *display_داده;
    SDL_پنجره_داده *پنجره_داده_2 = (SDL_پنجره_داده *)SDL_calloc(1, حجم(SDL_پنجره_داده));
    إذا (!پنجره_داده_2) {
        أرجع false;
    }
    display_داده = SDL_Get_Display_Driver_داده_For_پنجره(پنجره);
    پنجره_داده_2->screen = display_داده->screen;
    پنجره->داخلی = پنجره_داده_2;
    SDL_مجموعه_Keyboard_Focus(پنجره);
    أرجع true;
}

ساكن فراغ N3_DS_Destroy_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    إذا (!پنجره) {
        أرجع;
    }
    SDL_free(پنجره->داخلی);
}

#پایان_اگر // SDL_VIDEO_DRIVER_N3DS
