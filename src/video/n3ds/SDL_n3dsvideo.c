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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_N3DS

#ضمن "../SDL_sysvideo.h"
#ضمن "SDL_n3dsevents_c.h"
#ضمن "SDL_n3dsframebuffer_c.h"
#ضمن "SDL_n3dsswkb.h"
#ضمن "SDL_n3dstouch.h"
#ضمن "SDL_n3dsvideo.h"

#وصف_ڪريو N3DSVID_DRIVER_NAME "n3ds"

ساكن SDL_DisplayID جوڙيو_N3_DSDisplay(gfxScreen_t screen);

ساكن bool N3DS_VideoInit(SDL_VideoDevice *_this);
ساكن فراغ N3DS_VideoQuit(SDL_VideoDevice *_this);
ساكن bool N3DS_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
ساكن bool N3_DS_سيٽ_Display_گهڻائي(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_گهڻائي *گهڻائي);
ساكن bool N3DS_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
ساكن bool N3_DS_Create_دري(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID create_props);
ساكن فراغ N3_DS_Destroy_دري(SDL_VideoDevice *_this, SDL_دري *دري);

بنية SDL_Display_معلومات
{
    gfxScreen_t screen;
};

بنية SDL_Display_گهڻائي_معلومات
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
    SDL_free(device->اندروني);
    SDL_free(device);
}

ساكن SDL_VideoDevice *N3DS_CreateDevice(فراغ)
{
    SDL_VideoDevice *device;
    SDL_Video_معلومات *phdata;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (!device) {
        أرجع عدم;
    }

    // Initialize internal data
    phdata = (SDL_Video_معلومات *)SDL_calloc(1, حجم(SDL_Video_معلومات));
    إذا (!phdata) {
        SDL_free(device);
        أرجع عدم;
    }

    device->اندروني = phdata;

    device->VideoInit = N3DS_VideoInit;
    device->VideoQuit = N3DS_VideoQuit;

    device->GetDisplayModes = N3DS_GetDisplayModes;
    device->سيٽ_Display_گهڻائي = N3_DS_سيٽ_Display_گهڻائي;
    device->GetDisplayBounds = N3DS_GetDisplayBounds;

    device->CreateSDLWindow = N3_DS_Create_دري;
    device->Destroy_دري = N3_DS_Destroy_دري;

    device->HasScreenKeyboardSupport = N3DS_HasScreenKeyboardSupport;
    device->شروعات_متن_داخلا = N3_DS_شروعات_متن_داخلا;
    device->Stop_متن_داخلا = N3_DS_Stop_متن_داخلا;

    device->PumpEvents = N3DS_PumpEvents;

    device->Create_دري_Framebuffer = SDL_N3_DS_Create_دري_Framebuffer;
    device->Update_دري_Framebuffer = SDL_N3_DS_Update_دري_Framebuffer;
    device->Destroy_دري_Framebuffer = SDL_N3_DS_Destroy_دري_Framebuffer;

    device->حرر = N3DS_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    أرجع device;
}

VideoBootStrap N3DS_bootstrap = { N3DSVID_DRIVER_NAME, "N3DS Video Driver", N3DS_CreateDevice, عدم, /* no ShowMessageBox implementation */ false };

ساكن bool N3DS_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *اندروني = (SDL_Video_معلومات *)_this->اندروني;

    gfxInit(GSP_RGBA8_OES, GSP_RGBA8_OES, false);
    hidInit();

    اندروني->چوٽي_display = جوڙيو_N3_DSDisplay(GFX_چوٽي);
    اندروني->touch_display = جوڙيو_N3_DSDisplay(GFX_BOTTOM);

    N3DS_InitTouch();
    N3DS_SwkbInit();

    أرجع true;
}

ساكن SDL_DisplayID جوڙيو_N3_DSDisplay(gfxScreen_t screen)
{
    SDL_Display_گهڻائي گهڻائي;
    SDL_Display_گهڻائي_معلومات *modedata;
    SDL_VideoDisplay display;
    SDL_Display_معلومات *display_driver_معلومات = SDL_calloc(1, حجم(SDL_Display_معلومات));
    إذا (!display_driver_معلومات) {
        أرجع 0;
    }

    SDL_zero(گهڻائي);
    SDL_zero(display);

    display_driver_معلومات->screen = screen;

    modedata = SDL_malloc(حجم(SDL_Display_گهڻائي_معلومات));
    إذا (!modedata) {
        أرجع 0;
    }

    گهڻائي.w = (screen == GFX_چوٽي) ? GSP_SCREEN_اوچائي_چوٽي : GSP_SCREEN_اوچائي_BOTTOM;
    گهڻائي.h = GSP_SCREEN_ويڪر;
    گهڻائي.refresh_شرح = 60.0f;
    گهڻائي.format = SDL_PIXELFORMAT_RGBA8888;
    گهڻائي.اندروني = modedata;
    modedata->fmt = GSP_RGBA8_OES;

    display.name = (screen == GFX_چوٽي) ? "N3DS top screen" : "N3DS bottom screen";
    display.desktop_گهڻائي = گهڻائي;
    display.اندروني = display_driver_معلومات;

    أرجع SDL_جوڙيو_Video_Display(&display, false);
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
    SDL_Display_معلومات *displaydata = display->اندروني;
    SDL_Display_گهڻائي_معلومات *modedata;
    SDL_Display_گهڻائي گهڻائي;
    صحيح i;

    لكل (i = 0; i < SDL_arraysize(format_map); i++) {
        modedata = SDL_malloc(حجم(SDL_Display_گهڻائي_معلومات));
        إذا (!modedata)
            استمر;

        SDL_zero(گهڻائي);
        گهڻائي.w = (displaydata->screen == GFX_چوٽي) ? GSP_SCREEN_اوچائي_چوٽي : GSP_SCREEN_اوچائي_BOTTOM;
        گهڻائي.h = GSP_SCREEN_ويڪر;
        گهڻائي.refresh_شرح = 60.0f;
        گهڻائي.format = format_map[i].pixfmt;
        گهڻائي.اندروني = modedata;
        modedata->fmt = format_map[i].gspfmt;

        إذا (!SDL_جوڙيو_Fullscreen_Display_گهڻائي(display, &گهڻائي)) {
            SDL_free(modedata);
        }
    }

    أرجع true;
}

ساكن bool N3_DS_سيٽ_Display_گهڻائي(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_گهڻائي *گهڻائي)
{
    SDL_Display_معلومات *displaydata = display->اندروني;
    SDL_Display_گهڻائي_معلومات *modedata = گهڻائي->اندروني;

    gfx_سيٽ_Screen_Format(displaydata->screen, modedata->fmt);
    أرجع true;
}

ساكن bool N3DS_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    SDL_Display_معلومات *driver_معلومات = display->اندروني;

    إذا (!driver_معلومات) {
        أرجع false;
    }

    rect->x = 0;
    rect->y = (driver_معلومات->screen == GFX_چوٽي) ? 0 : GSP_SCREEN_ويڪر;
    rect->w = display->current_گهڻائي->w;
    rect->h = display->current_گهڻائي->h;
    أرجع true;
}

ساكن bool N3_DS_Create_دري(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID create_props)
{
    SDL_Display_معلومات *display_معلومات;
    SDL_دري_معلومات *دري_معلومات_2 = (SDL_دري_معلومات *)SDL_calloc(1, حجم(SDL_دري_معلومات));
    إذا (!دري_معلومات_2) {
        أرجع false;
    }
    display_معلومات = SDL_Get_Display_Driver_معلومات_For_دري(دري);
    دري_معلومات_2->screen = display_معلومات->screen;
    دري->اندروني = دري_معلومات_2;
    SDL_سيٽ_Keyboard_Focus(دري);
    أرجع true;
}

ساكن فراغ N3_DS_Destroy_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    إذا (!دري) {
        أرجع;
    }
    SDL_free(دري->اندروني);
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_N3DS
