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
#अन्तर्भाव "SDL_internal.h"

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_N3DS

#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "SDL_n3dsevents_c.h"
#अन्तर्भाव "SDL_n3dsframebuffer_c.h"
#अन्तर्भाव "SDL_n3dsswkb.h"
#अन्तर्भाव "SDL_n3dstouch.h"
#अन्तर्भाव "SDL_n3dsvideo.h"

#परिभाषय N3DSVID_DRIVER_NAME "n3ds"

स्थिर SDL_DisplayID सङ्कलय_N3_DSDisplay(gfxScreen_t screen);

स्थिर bool N3DS_VideoInit(SDL_VideoDevice *_this);
स्थिर शून्य N3DS_VideoQuit(SDL_VideoDevice *_this);
स्थिर bool N3DS_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
स्थिर bool N3_DS_समुच्चयः_Display_बहुलकम्(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_बहुलकम् *बहुलकम्);
स्थिर bool N3DS_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
स्थिर bool N3_DS_Create_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID create_props);
स्थिर शून्य N3_DS_Destroy_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);

संरचना SDL_Display_दत्त
{
    gfxScreen_t screen;
};

संरचना SDL_Display_बहुलकम्_दत्त
{
    GSPGPU_FramebufferFormat fmt;
};

स्थिर ध्रुव संरचना
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

स्थिर शून्य N3DS_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->आन्तरिकम्);
    SDL_free(device);
}

स्थिर SDL_VideoDevice *N3DS_CreateDevice(शून्य)
{
    SDL_VideoDevice *device;
    SDL_Video_दत्त *phdata;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, परिमाण(SDL_VideoDevice));
    यदि (!device) {
        प्रत्यागम रिक्त;
    }

    // Initialize internal data
    phdata = (SDL_Video_दत्त *)SDL_calloc(1, परिमाण(SDL_Video_दत्त));
    यदि (!phdata) {
        SDL_free(device);
        प्रत्यागम रिक्त;
    }

    device->आन्तरिकम् = phdata;

    device->VideoInit = N3DS_VideoInit;
    device->VideoQuit = N3DS_VideoQuit;

    device->GetDisplayModes = N3DS_GetDisplayModes;
    device->समुच्चयः_Display_बहुलकम् = N3_DS_समुच्चयः_Display_बहुलकम्;
    device->GetDisplayBounds = N3DS_GetDisplayBounds;

    device->CreateSDLWindow = N3_DS_Create_गवाक्षः;
    device->Destroy_गवाक्षः = N3_DS_Destroy_गवाक्षः;

    device->HasScreenKeyboardSupport = N3DS_HasScreenKeyboardSupport;
    device->Start_Text_निवेशः = N3_DS_Start_Text_निवेशः;
    device->Stop_Text_निवेशः = N3_DS_Stop_Text_निवेशः;

    device->PumpEvents = N3DS_PumpEvents;

    device->Create_गवाक्षः_Framebuffer = SDL_N3_DS_Create_गवाक्षः_Framebuffer;
    device->Update_गवाक्षः_Framebuffer = SDL_N3_DS_Update_गवाक्षः_Framebuffer;
    device->Destroy_गवाक्षः_Framebuffer = SDL_N3_DS_Destroy_गवाक्षः_Framebuffer;

    device->मुक्त = N3DS_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    प्रत्यागम device;
}

VideoBootStrap N3DS_bootstrap = { N3DSVID_DRIVER_NAME, "N3DS Video Driver", N3DS_CreateDevice, रिक्त, /* no ShowMessageBox implementation */ false };

स्थिर bool N3DS_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *आन्तरिकम् = (SDL_Video_दत्त *)_this->आन्तरिकम्;

    gfxInit(GSP_RGBA8_OES, GSP_RGBA8_OES, false);
    hidInit();

    आन्तरिकम्->शिखरम्_display = सङ्कलय_N3_DSDisplay(GFX_शिखरम्);
    आन्तरिकम्->touch_display = सङ्कलय_N3_DSDisplay(GFX_BOTTOM);

    N3DS_InitTouch();
    N3DS_SwkbInit();

    प्रत्यागम true;
}

स्थिर SDL_DisplayID सङ्कलय_N3_DSDisplay(gfxScreen_t screen)
{
    SDL_Display_बहुलकम् बहुलकम्;
    SDL_Display_बहुलकम्_दत्त *modedata;
    SDL_VideoDisplay display;
    SDL_Display_दत्त *display_driver_दत्त = SDL_calloc(1, परिमाण(SDL_Display_दत्त));
    यदि (!display_driver_दत्त) {
        प्रत्यागम 0;
    }

    SDL_zero(बहुलकम्);
    SDL_zero(display);

    display_driver_दत्त->screen = screen;

    modedata = SDL_malloc(परिमाण(SDL_Display_बहुलकम्_दत्त));
    यदि (!modedata) {
        प्रत्यागम 0;
    }

    बहुलकम्.w = (screen == GFX_शिखरम्) ? GSP_SCREEN_HEIGHT_शिखरम् : GSP_SCREEN_HEIGHT_BOTTOM;
    बहुलकम्.h = GSP_SCREEN_विस्तारः;
    बहुलकम्.refresh_दरः = 60.0f;
    बहुलकम्.format = SDL_PIXELFORMAT_RGBA8888;
    बहुलकम्.आन्तरिकम् = modedata;
    modedata->fmt = GSP_RGBA8_OES;

    display.name = (screen == GFX_शिखरम्) ? "N3DS top screen" : "N3DS bottom screen";
    display.desktop_बहुलकम् = बहुलकम्;
    display.आन्तरिकम् = display_driver_दत्त;

    प्रत्यागम SDL_सङ्कलय_Video_Display(&display, false);
}

स्थिर शून्य N3DS_VideoQuit(SDL_VideoDevice *_this)
{
    N3DS_SwkbQuit();
    N3DS_QuitTouch();

    hidExit();
    gfxExit();
}

स्थिर bool N3DS_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_दत्त *displaydata = display->आन्तरिकम्;
    SDL_Display_बहुलकम्_दत्त *modedata;
    SDL_Display_बहुलकम् बहुलकम्;
    पूर्णाङ्क i;

    प्रति (i = 0; i < SDL_arraysize(format_map); i++) {
        modedata = SDL_malloc(परिमाण(SDL_Display_बहुलकम्_दत्त));
        यदि (!modedata)
            अनुवर्त;

        SDL_zero(बहुलकम्);
        बहुलकम्.w = (displaydata->screen == GFX_शिखरम्) ? GSP_SCREEN_HEIGHT_शिखरम् : GSP_SCREEN_HEIGHT_BOTTOM;
        बहुलकम्.h = GSP_SCREEN_विस्तारः;
        बहुलकम्.refresh_दरः = 60.0f;
        बहुलकम्.format = format_map[i].pixfmt;
        बहुलकम्.आन्तरिकम् = modedata;
        modedata->fmt = format_map[i].gspfmt;

        यदि (!SDL_सङ्कलय_Fullscreen_Display_बहुलकम्(display, &बहुलकम्)) {
            SDL_free(modedata);
        }
    }

    प्रत्यागम true;
}

स्थिर bool N3_DS_समुच्चयः_Display_बहुलकम्(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_बहुलकम् *बहुलकम्)
{
    SDL_Display_दत्त *displaydata = display->आन्तरिकम्;
    SDL_Display_बहुलकम्_दत्त *modedata = बहुलकम्->आन्तरिकम्;

    gfx_समुच्चयः_Screen_Format(displaydata->screen, modedata->fmt);
    प्रत्यागम true;
}

स्थिर bool N3DS_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    SDL_Display_दत्त *driver_दत्त = display->आन्तरिकम्;

    यदि (!driver_दत्त) {
        प्रत्यागम false;
    }

    rect->x = 0;
    rect->y = (driver_दत्त->screen == GFX_शिखरम्) ? 0 : GSP_SCREEN_विस्तारः;
    rect->w = display->current_बहुलकम्->w;
    rect->h = display->current_बहुलकम्->h;
    प्रत्यागम true;
}

स्थिर bool N3_DS_Create_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID create_props)
{
    SDL_Display_दत्त *display_दत्त;
    SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2 = (SDL_गवाक्षः_दत्त *)SDL_calloc(1, परिमाण(SDL_गवाक्षः_दत्त));
    यदि (!गवाक्षः_दत्त_2) {
        प्रत्यागम false;
    }
    display_दत्त = SDL_Get_Display_Driver_दत्त_For_गवाक्षः(गवाक्षः);
    गवाक्षः_दत्त_2->screen = display_दत्त->screen;
    गवाक्षः->आन्तरिकम् = गवाक्षः_दत्त_2;
    SDL_समुच्चयः_Keyboard_Focus(गवाक्षः);
    प्रत्यागम true;
}

स्थिर शून्य N3_DS_Destroy_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    यदि (!गवाक्षः) {
        प्रत्यागम;
    }
    SDL_free(गवाक्षः->आन्तरिकम्);
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_N3DS
