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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_N3DS

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_n3dsevents_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_n3dsframebuffer_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_n3dsswkb.h"
#ಅನ್ತರ್ಭಾವ "SDL_n3dstouch.h"
#ಅನ್ತರ್ಭಾವ "SDL_n3dsvideo.h"

#ವ್ಯಾಖ್ಯಾನಿಸು N3DSVID_DRIVER_NAME "n3ds"

ಸ್ಥಿರ SDL_DisplayID ಕೂಡಿಸು_N3_DSDisplay(gfxScreen_t screen);

ಸ್ಥಿರ bool N3DS_VideoInit(SDL_VideoDevice *_this);
ಸ್ಥಿರ ಶೂನ್ಯ N3DS_VideoQuit(SDL_VideoDevice *_this);
ಸ್ಥಿರ bool N3DS_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
ಸ್ಥಿರ bool N3_DS_ಗಣ_Display_ಬಹುಲಕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ);
ಸ್ಥಿರ bool N3DS_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
ಸ್ಥಿರ bool N3_DS_Create_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID create_props);
ಸ್ಥಿರ ಶೂನ್ಯ N3_DS_Destroy_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);

ರಚನೆ SDL_Display_ದತ್ತಾಂಶ
{
    gfxScreen_t screen;
};

ರಚನೆ SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ
{
    GSPGPU_FramebufferFormat fmt;
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ
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

ಸ್ಥಿರ ಶೂನ್ಯ N3DS_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->ಆಂತರಿಕ);
    SDL_free(device);
}

ಸ್ಥಿರ SDL_VideoDevice *N3DS_CreateDevice(ಶೂನ್ಯ)
{
    SDL_VideoDevice *device;
    SDL_Video_ದತ್ತಾಂಶ *phdata;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, ಗಾತ್ರ(SDL_VideoDevice));
    ಆದರೆ (!device) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    // Initialize internal data
    phdata = (SDL_Video_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_Video_ದತ್ತಾಂಶ));
    ಆದರೆ (!phdata) {
        SDL_free(device);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    device->ಆಂತರಿಕ = phdata;

    device->VideoInit = N3DS_VideoInit;
    device->VideoQuit = N3DS_VideoQuit;

    device->GetDisplayModes = N3DS_GetDisplayModes;
    device->ಗಣ_Display_ಬಹುಲಕ = N3_DS_ಗಣ_Display_ಬಹುಲಕ;
    device->GetDisplayBounds = N3DS_GetDisplayBounds;

    device->CreateSDLWindow = N3_DS_Create_ಕಿಟಕಿ;
    device->Destroy_ಕಿಟಕಿ = N3_DS_Destroy_ಕಿಟಕಿ;

    device->HasScreenKeyboardSupport = N3DS_HasScreenKeyboardSupport;
    device->ಆರಂಭ_ಪಠ್ಯ_ಒಳಹರಿವು = N3_DS_ಆರಂಭ_ಪಠ್ಯ_ಒಳಹರಿವು;
    device->Stop_ಪಠ್ಯ_ಒಳಹರಿವು = N3_DS_Stop_ಪಠ್ಯ_ಒಳಹರಿವು;

    device->PumpEvents = N3DS_PumpEvents;

    device->Create_ಕಿಟಕಿ_Framebuffer = SDL_N3_DS_Create_ಕಿಟಕಿ_Framebuffer;
    device->Update_ಕಿಟಕಿ_Framebuffer = SDL_N3_DS_Update_ಕಿಟಕಿ_Framebuffer;
    device->Destroy_ಕಿಟಕಿ_Framebuffer = SDL_N3_DS_Destroy_ಕಿಟಕಿ_Framebuffer;

    device->ಬಿಡುಗಡೆ = N3DS_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    ಹಿಂತಿರುಗಿ device;
}

VideoBootStrap N3DS_bootstrap = { N3DSVID_DRIVER_NAME, "N3DS Video Driver", N3DS_CreateDevice, ಖಾಲಿ, /* no ShowMessageBox implementation */ false };

ಸ್ಥಿರ bool N3DS_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *ಆಂತರಿಕ = (SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ;

    gfxInit(GSP_RGBA8_OES, GSP_RGBA8_OES, false);
    hidInit();

    ಆಂತರಿಕ->ತುದಿ_display = ಕೂಡಿಸು_N3_DSDisplay(GFX_ತುದಿ);
    ಆಂತರಿಕ->touch_display = ಕೂಡಿಸು_N3_DSDisplay(GFX_BOTTOM);

    N3DS_InitTouch();
    N3DS_SwkbInit();

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ SDL_DisplayID ಕೂಡಿಸು_N3_DSDisplay(gfxScreen_t screen)
{
    SDL_Display_ಬಹುಲಕ ಬಹುಲಕ;
    SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *modedata;
    SDL_VideoDisplay display;
    SDL_Display_ದತ್ತಾಂಶ *display_driver_ದತ್ತಾಂಶ = SDL_calloc(1, ಗಾತ್ರ(SDL_Display_ದತ್ತಾಂಶ));
    ಆದರೆ (!display_driver_ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ 0;
    }

    SDL_zero(ಬಹುಲಕ);
    SDL_zero(display);

    display_driver_ದತ್ತಾಂಶ->screen = screen;

    modedata = SDL_malloc(ಗಾತ್ರ(SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ));
    ಆದರೆ (!modedata) {
        ಹಿಂತಿರುಗಿ 0;
    }

    ಬಹುಲಕ.w = (screen == GFX_ತುದಿ) ? GSP_SCREEN_ಎತ್ತರ_ತುದಿ : GSP_SCREEN_ಎತ್ತರ_BOTTOM;
    ಬಹುಲಕ.h = GSP_SCREEN_ಅಗಲ;
    ಬಹುಲಕ.refresh_ದರ = 60.0f;
    ಬಹುಲಕ.format = SDL_PIXELFORMAT_RGBA8888;
    ಬಹುಲಕ.ಆಂತರಿಕ = modedata;
    modedata->fmt = GSP_RGBA8_OES;

    display.name = (screen == GFX_ತುದಿ) ? "N3DS top screen" : "N3DS bottom screen";
    display.desktop_ಬಹುಲಕ = ಬಹುಲಕ;
    display.ಆಂತರಿಕ = display_driver_ದತ್ತಾಂಶ;

    ಹಿಂತಿರುಗಿ SDL_ಕೂಡಿಸು_Video_Display(&display, false);
}

ಸ್ಥಿರ ಶೂನ್ಯ N3DS_VideoQuit(SDL_VideoDevice *_this)
{
    N3DS_SwkbQuit();
    N3DS_QuitTouch();

    hidExit();
    gfxExit();
}

ಸ್ಥಿರ bool N3DS_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_ದತ್ತಾಂಶ *displaydata = display->ಆಂತರಿಕ;
    SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *modedata;
    SDL_Display_ಬಹುಲಕ ಬಹುಲಕ;
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; i < SDL_arraysize(format_map); i++) {
        modedata = SDL_malloc(ಗಾತ್ರ(SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ));
        ಆದರೆ (!modedata)
            ಮುಂದುವರಿ;

        SDL_zero(ಬಹುಲಕ);
        ಬಹುಲಕ.w = (displaydata->screen == GFX_ತುದಿ) ? GSP_SCREEN_ಎತ್ತರ_ತುದಿ : GSP_SCREEN_ಎತ್ತರ_BOTTOM;
        ಬಹುಲಕ.h = GSP_SCREEN_ಅಗಲ;
        ಬಹುಲಕ.refresh_ದರ = 60.0f;
        ಬಹುಲಕ.format = format_map[i].pixfmt;
        ಬಹುಲಕ.ಆಂತರಿಕ = modedata;
        modedata->fmt = format_map[i].gspfmt;

        ಆದರೆ (!SDL_ಕೂಡಿಸು_Fullscreen_Display_ಬಹುಲಕ(display, &ಬಹುಲಕ)) {
            SDL_free(modedata);
        }
    }

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool N3_DS_ಗಣ_Display_ಬಹುಲಕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ)
{
    SDL_Display_ದತ್ತಾಂಶ *displaydata = display->ಆಂತರಿಕ;
    SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *modedata = ಬಹುಲಕ->ಆಂತರಿಕ;

    gfx_ಗಣ_Screen_Format(displaydata->screen, modedata->fmt);
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool N3DS_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    SDL_Display_ದತ್ತಾಂಶ *driver_ದತ್ತಾಂಶ = display->ಆಂತರಿಕ;

    ಆದರೆ (!driver_ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ false;
    }

    rect->x = 0;
    rect->y = (driver_ದತ್ತಾಂಶ->screen == GFX_ತುದಿ) ? 0 : GSP_SCREEN_ಅಗಲ;
    rect->w = display->current_ಬಹುಲಕ->w;
    rect->h = display->current_ಬಹುಲಕ->h;
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool N3_DS_Create_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID create_props)
{
    SDL_Display_ದತ್ತಾಂಶ *display_ದತ್ತಾಂಶ;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2 = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ));
    ಆದರೆ (!ಕಿಟಕಿ_ದತ್ತಾಂಶ_2) {
        ಹಿಂತಿರುಗಿ false;
    }
    display_ದತ್ತಾಂಶ = SDL_Get_Display_Driver_ದತ್ತಾಂಶ_For_ಕಿಟಕಿ(ಕಿಟಕಿ);
    ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->screen = display_ದತ್ತಾಂಶ->screen;
    ಕಿಟಕಿ->ಆಂತರಿಕ = ಕಿಟಕಿ_ದತ್ತಾಂಶ_2;
    SDL_ಗಣ_Keyboard_Focus(ಕಿಟಕಿ);
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ N3_DS_Destroy_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಆದರೆ (!ಕಿಟಕಿ) {
        ಹಿಂತಿರುಗಿ;
    }
    SDL_free(ಕಿಟಕಿ->ಆಂತರಿಕ);
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_N3DS
