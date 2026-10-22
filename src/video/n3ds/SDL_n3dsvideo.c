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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_N3DS

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_n3dsevents_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_n3dsframebuffer_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_n3dsswkb.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_n3dstouch.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_n3dsvideo.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ N3DSVID_DRIVER_NAME "n3ds"

ਸਥਿਰ SDL_DisplayID ਜੋੜੋ_N3_DSDisplay(gfxScreen_t screen);

ਸਥਿਰ bool N3DS_VideoInit(SDL_VideoDevice *_this);
ਸਥਿਰ ਖਾਲੀ N3DS_VideoQuit(SDL_VideoDevice *_this);
ਸਥਿਰ bool N3DS_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
ਸਥਿਰ bool N3_DS_ਸੈੱਟ_Display_ਬਹੁਲਕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ);
ਸਥਿਰ bool N3DS_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
ਸਥਿਰ bool N3_DS_Create_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID create_props);
ਸਥਿਰ ਖਾਲੀ N3_DS_Destroy_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);

ਬਣਤਰ SDL_Display_ਅੰਕੜੇ
{
    gfxScreen_t screen;
};

ਬਣਤਰ SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ
{
    GSPGPU_FramebufferFormat fmt;
};

ਸਥਿਰ ਅਚਲ ਬਣਤਰ
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

ਸਥਿਰ ਖਾਲੀ N3DS_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->ਅੰਦਰੂਨੀ);
    SDL_free(device);
}

ਸਥਿਰ SDL_VideoDevice *N3DS_CreateDevice(ਖਾਲੀ)
{
    SDL_VideoDevice *device;
    SDL_Video_ਅੰਕੜੇ *phdata;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, ਆਕਾਰ(SDL_VideoDevice));
    ਜੇ (!device) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    // Initialize internal data
    phdata = (SDL_Video_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(SDL_Video_ਅੰਕੜੇ));
    ਜੇ (!phdata) {
        SDL_free(device);
        ਵਾਪਸ ਨਿਰਾ;
    }

    device->ਅੰਦਰੂਨੀ = phdata;

    device->VideoInit = N3DS_VideoInit;
    device->VideoQuit = N3DS_VideoQuit;

    device->GetDisplayModes = N3DS_GetDisplayModes;
    device->ਸੈੱਟ_Display_ਬਹੁਲਕ = N3_DS_ਸੈੱਟ_Display_ਬਹੁਲਕ;
    device->GetDisplayBounds = N3DS_GetDisplayBounds;

    device->CreateSDLWindow = N3_DS_Create_ਖਿੜਕੀ;
    device->Destroy_ਖਿੜਕੀ = N3_DS_Destroy_ਖਿੜਕੀ;

    device->HasScreenKeyboardSupport = N3DS_HasScreenKeyboardSupport;
    device->ਸ਼ੁਰੂ_ਪਾਠ_ਨਿਵੇਸ਼ = N3_DS_ਸ਼ੁਰੂ_ਪਾਠ_ਨਿਵੇਸ਼;
    device->Stop_ਪਾਠ_ਨਿਵੇਸ਼ = N3_DS_Stop_ਪਾਠ_ਨਿਵੇਸ਼;

    device->PumpEvents = N3DS_PumpEvents;

    device->Create_ਖਿੜਕੀ_Framebuffer = SDL_N3_DS_Create_ਖਿੜਕੀ_Framebuffer;
    device->Update_ਖਿੜਕੀ_Framebuffer = SDL_N3_DS_Update_ਖਿੜਕੀ_Framebuffer;
    device->Destroy_ਖਿੜਕੀ_Framebuffer = SDL_N3_DS_Destroy_ਖਿੜਕੀ_Framebuffer;

    device->ਮੁਕਤ = N3DS_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    ਵਾਪਸ device;
}

VideoBootStrap N3DS_bootstrap = { N3DSVID_DRIVER_NAME, "N3DS Video Driver", N3DS_CreateDevice, ਨਿਰਾ, /* no ShowMessageBox implementation */ false };

ਸਥਿਰ bool N3DS_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ = (SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ;

    gfxInit(GSP_RGBA8_OES, GSP_RGBA8_OES, false);
    hidInit();

    ਅੰਦਰੂਨੀ->ਸਿਖਰ_display = ਜੋੜੋ_N3_DSDisplay(GFX_ਸਿਖਰ);
    ਅੰਦਰੂਨੀ->touch_display = ਜੋੜੋ_N3_DSDisplay(GFX_BOTTOM);

    N3DS_InitTouch();
    N3DS_SwkbInit();

    ਵਾਪਸ true;
}

ਸਥਿਰ SDL_DisplayID ਜੋੜੋ_N3_DSDisplay(gfxScreen_t screen)
{
    SDL_Display_ਬਹੁਲਕ ਬਹੁਲਕ;
    SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *modedata;
    SDL_VideoDisplay display;
    SDL_Display_ਅੰਕੜੇ *display_driver_ਅੰਕੜੇ = SDL_calloc(1, ਆਕਾਰ(SDL_Display_ਅੰਕੜੇ));
    ਜੇ (!display_driver_ਅੰਕੜੇ) {
        ਵਾਪਸ 0;
    }

    SDL_zero(ਬਹੁਲਕ);
    SDL_zero(display);

    display_driver_ਅੰਕੜੇ->screen = screen;

    modedata = SDL_malloc(ਆਕਾਰ(SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ));
    ਜੇ (!modedata) {
        ਵਾਪਸ 0;
    }

    ਬਹੁਲਕ.w = (screen == GFX_ਸਿਖਰ) ? GSP_SCREEN_ਉਚਾਈ_ਸਿਖਰ : GSP_SCREEN_ਉਚਾਈ_BOTTOM;
    ਬਹੁਲਕ.h = GSP_SCREEN_ਚੌੜਾਈ;
    ਬਹੁਲਕ.refresh_ਦਰ = 60.0f;
    ਬਹੁਲਕ.format = SDL_PIXELFORMAT_RGBA8888;
    ਬਹੁਲਕ.ਅੰਦਰੂਨੀ = modedata;
    modedata->fmt = GSP_RGBA8_OES;

    display.name = (screen == GFX_ਸਿਖਰ) ? "N3DS top screen" : "N3DS bottom screen";
    display.desktop_ਬਹੁਲਕ = ਬਹੁਲਕ;
    display.ਅੰਦਰੂਨੀ = display_driver_ਅੰਕੜੇ;

    ਵਾਪਸ SDL_ਜੋੜੋ_Video_Display(&display, false);
}

ਸਥਿਰ ਖਾਲੀ N3DS_VideoQuit(SDL_VideoDevice *_this)
{
    N3DS_SwkbQuit();
    N3DS_QuitTouch();

    hidExit();
    gfxExit();
}

ਸਥਿਰ bool N3DS_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_ਅੰਕੜੇ *displaydata = display->ਅੰਦਰੂਨੀ;
    SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *modedata;
    SDL_Display_ਬਹੁਲਕ ਬਹੁਲਕ;
    ਪੂਰਨ i;

    ਲਈ (i = 0; i < SDL_arraysize(format_map); i++) {
        modedata = SDL_malloc(ਆਕਾਰ(SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ));
        ਜੇ (!modedata)
            ਜਾਰੀ;

        SDL_zero(ਬਹੁਲਕ);
        ਬਹੁਲਕ.w = (displaydata->screen == GFX_ਸਿਖਰ) ? GSP_SCREEN_ਉਚਾਈ_ਸਿਖਰ : GSP_SCREEN_ਉਚਾਈ_BOTTOM;
        ਬਹੁਲਕ.h = GSP_SCREEN_ਚੌੜਾਈ;
        ਬਹੁਲਕ.refresh_ਦਰ = 60.0f;
        ਬਹੁਲਕ.format = format_map[i].pixfmt;
        ਬਹੁਲਕ.ਅੰਦਰੂਨੀ = modedata;
        modedata->fmt = format_map[i].gspfmt;

        ਜੇ (!SDL_ਜੋੜੋ_Fullscreen_Display_ਬਹੁਲਕ(display, &ਬਹੁਲਕ)) {
            SDL_free(modedata);
        }
    }

    ਵਾਪਸ true;
}

ਸਥਿਰ bool N3_DS_ਸੈੱਟ_Display_ਬਹੁਲਕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ)
{
    SDL_Display_ਅੰਕੜੇ *displaydata = display->ਅੰਦਰੂਨੀ;
    SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *modedata = ਬਹੁਲਕ->ਅੰਦਰੂਨੀ;

    gfx_ਸੈੱਟ_Screen_Format(displaydata->screen, modedata->fmt);
    ਵਾਪਸ true;
}

ਸਥਿਰ bool N3DS_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    SDL_Display_ਅੰਕੜੇ *driver_ਅੰਕੜੇ = display->ਅੰਦਰੂਨੀ;

    ਜੇ (!driver_ਅੰਕੜੇ) {
        ਵਾਪਸ false;
    }

    rect->x = 0;
    rect->y = (driver_ਅੰਕੜੇ->screen == GFX_ਸਿਖਰ) ? 0 : GSP_SCREEN_ਚੌੜਾਈ;
    rect->w = display->current_ਬਹੁਲਕ->w;
    rect->h = display->current_ਬਹੁਲਕ->h;
    ਵਾਪਸ true;
}

ਸਥਿਰ bool N3_DS_Create_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID create_props)
{
    SDL_Display_ਅੰਕੜੇ *display_ਅੰਕੜੇ;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2 = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ));
    ਜੇ (!ਖਿੜਕੀ_ਅੰਕੜੇ_2) {
        ਵਾਪਸ false;
    }
    display_ਅੰਕੜੇ = SDL_Get_Display_Driver_ਅੰਕੜੇ_For_ਖਿੜਕੀ(ਖਿੜਕੀ);
    ਖਿੜਕੀ_ਅੰਕੜੇ_2->screen = display_ਅੰਕੜੇ->screen;
    ਖਿੜਕੀ->ਅੰਦਰੂਨੀ = ਖਿੜਕੀ_ਅੰਕੜੇ_2;
    SDL_ਸੈੱਟ_Keyboard_Focus(ਖਿੜਕੀ);
    ਵਾਪਸ true;
}

ਸਥਿਰ ਖਾਲੀ N3_DS_Destroy_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਜੇ (!ਖਿੜਕੀ) {
        ਵਾਪਸ;
    }
    SDL_free(ਖਿੜਕੀ->ਅੰਦਰੂਨੀ);
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_N3DS
