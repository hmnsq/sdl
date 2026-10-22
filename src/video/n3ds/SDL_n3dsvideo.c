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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_N3DS

#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "SDL_n3dsevents_c.h"
#అన్తర్భావ "SDL_n3dsframebuffer_c.h"
#అన్తర్భావ "SDL_n3dsswkb.h"
#అన్తర్భావ "SDL_n3dstouch.h"
#అన్తర్భావ "SDL_n3dsvideo.h"

#నిర్వచించు N3DSVID_DRIVER_NAME "n3ds"

స్థిర SDL_DisplayID కూడు_N3_DSDisplay(gfxScreen_t screen);

స్థిర bool N3DS_VideoInit(SDL_VideoDevice *_this);
స్థిర శూన్య N3DS_VideoQuit(SDL_VideoDevice *_this);
స్థిర bool N3DS_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display);
స్థిర bool N3_DS_సమితి_Display_బహుళకం(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_బహుళకం *బహుళకం);
స్థిర bool N3DS_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
స్థిర bool N3_DS_Create_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID create_props);
స్థిర శూన్య N3_DS_Destroy_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);

నిర్మాణం SDL_Display_దత్తాంశం
{
    gfxScreen_t screen;
};

నిర్మాణం SDL_Display_బహుళకం_దత్తాంశం
{
    GSPGPU_FramebufferFormat fmt;
};

స్థిర స్థిరరాశి నిర్మాణం
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

స్థిర శూన్య N3DS_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->అంతర్గత);
    SDL_free(device);
}

స్థిర SDL_VideoDevice *N3DS_CreateDevice(శూన్య)
{
    SDL_VideoDevice *device;
    SDL_Video_దత్తాంశం *phdata;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, పరిమాణం(SDL_VideoDevice));
    ఒకవేళ (!device) {
        తిరిగి ఖాళీ;
    }

    // Initialize internal data
    phdata = (SDL_Video_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_Video_దత్తాంశం));
    ఒకవేళ (!phdata) {
        SDL_free(device);
        తిరిగి ఖాళీ;
    }

    device->అంతర్గత = phdata;

    device->VideoInit = N3DS_VideoInit;
    device->VideoQuit = N3DS_VideoQuit;

    device->GetDisplayModes = N3DS_GetDisplayModes;
    device->సమితి_Display_బహుళకం = N3_DS_సమితి_Display_బహుళకం;
    device->GetDisplayBounds = N3DS_GetDisplayBounds;

    device->CreateSDLWindow = N3_DS_Create_కిటికీ;
    device->Destroy_కిటికీ = N3_DS_Destroy_కిటికీ;

    device->HasScreenKeyboardSupport = N3DS_HasScreenKeyboardSupport;
    device->ప్రారంభం_పాఠ్యం_ఆదానం = N3_DS_ప్రారంభం_పాఠ్యం_ఆదానం;
    device->Stop_పాఠ్యం_ఆదానం = N3_DS_Stop_పాఠ్యం_ఆదానం;

    device->PumpEvents = N3DS_PumpEvents;

    device->Create_కిటికీ_Framebuffer = SDL_N3_DS_Create_కిటికీ_Framebuffer;
    device->Update_కిటికీ_Framebuffer = SDL_N3_DS_Update_కిటికీ_Framebuffer;
    device->Destroy_కిటికీ_Framebuffer = SDL_N3_DS_Destroy_కిటికీ_Framebuffer;

    device->విడుదల = N3DS_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    తిరిగి device;
}

VideoBootStrap N3DS_bootstrap = { N3DSVID_DRIVER_NAME, "N3DS Video Driver", N3DS_CreateDevice, ఖాళీ, /* no ShowMessageBox implementation */ false };

స్థిర bool N3DS_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *అంతర్గత = (SDL_Video_దత్తాంశం *)_this->అంతర్గత;

    gfxInit(GSP_RGBA8_OES, GSP_RGBA8_OES, false);
    hidInit();

    అంతర్గత->శిఖరం_display = కూడు_N3_DSDisplay(GFX_శిఖరం);
    అంతర్గత->touch_display = కూడు_N3_DSDisplay(GFX_BOTTOM);

    N3DS_InitTouch();
    N3DS_SwkbInit();

    తిరిగి true;
}

స్థిర SDL_DisplayID కూడు_N3_DSDisplay(gfxScreen_t screen)
{
    SDL_Display_బహుళకం బహుళకం;
    SDL_Display_బహుళకం_దత్తాంశం *modedata;
    SDL_VideoDisplay display;
    SDL_Display_దత్తాంశం *display_driver_దత్తాంశం = SDL_calloc(1, పరిమాణం(SDL_Display_దత్తాంశం));
    ఒకవేళ (!display_driver_దత్తాంశం) {
        తిరిగి 0;
    }

    SDL_zero(బహుళకం);
    SDL_zero(display);

    display_driver_దత్తాంశం->screen = screen;

    modedata = SDL_malloc(పరిమాణం(SDL_Display_బహుళకం_దత్తాంశం));
    ఒకవేళ (!modedata) {
        తిరిగి 0;
    }

    బహుళకం.w = (screen == GFX_శిఖరం) ? GSP_SCREEN_ఎత్తు_శిఖరం : GSP_SCREEN_ఎత్తు_BOTTOM;
    బహుళకం.h = GSP_SCREEN_వెడల్పు;
    బహుళకం.refresh_రేటు = 60.0f;
    బహుళకం.format = SDL_PIXELFORMAT_RGBA8888;
    బహుళకం.అంతర్గత = modedata;
    modedata->fmt = GSP_RGBA8_OES;

    display.name = (screen == GFX_శిఖరం) ? "N3DS top screen" : "N3DS bottom screen";
    display.desktop_బహుళకం = బహుళకం;
    display.అంతర్గత = display_driver_దత్తాంశం;

    తిరిగి SDL_కూడు_Video_Display(&display, false);
}

స్థిర శూన్య N3DS_VideoQuit(SDL_VideoDevice *_this)
{
    N3DS_SwkbQuit();
    N3DS_QuitTouch();

    hidExit();
    gfxExit();
}

స్థిర bool N3DS_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_దత్తాంశం *displaydata = display->అంతర్గత;
    SDL_Display_బహుళకం_దత్తాంశం *modedata;
    SDL_Display_బహుళకం బహుళకం;
    పూర్ణాంకం i;

    కొరకు (i = 0; i < SDL_arraysize(format_map); i++) {
        modedata = SDL_malloc(పరిమాణం(SDL_Display_బహుళకం_దత్తాంశం));
        ఒకవేళ (!modedata)
            కొనసాగు;

        SDL_zero(బహుళకం);
        బహుళకం.w = (displaydata->screen == GFX_శిఖరం) ? GSP_SCREEN_ఎత్తు_శిఖరం : GSP_SCREEN_ఎత్తు_BOTTOM;
        బహుళకం.h = GSP_SCREEN_వెడల్పు;
        బహుళకం.refresh_రేటు = 60.0f;
        బహుళకం.format = format_map[i].pixfmt;
        బహుళకం.అంతర్గత = modedata;
        modedata->fmt = format_map[i].gspfmt;

        ఒకవేళ (!SDL_కూడు_Fullscreen_Display_బహుళకం(display, &బహుళకం)) {
            SDL_free(modedata);
        }
    }

    తిరిగి true;
}

స్థిర bool N3_DS_సమితి_Display_బహుళకం(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_బహుళకం *బహుళకం)
{
    SDL_Display_దత్తాంశం *displaydata = display->అంతర్గత;
    SDL_Display_బహుళకం_దత్తాంశం *modedata = బహుళకం->అంతర్గత;

    gfx_సమితి_Screen_Format(displaydata->screen, modedata->fmt);
    తిరిగి true;
}

స్థిర bool N3DS_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    SDL_Display_దత్తాంశం *driver_దత్తాంశం = display->అంతర్గత;

    ఒకవేళ (!driver_దత్తాంశం) {
        తిరిగి false;
    }

    rect->x = 0;
    rect->y = (driver_దత్తాంశం->screen == GFX_శిఖరం) ? 0 : GSP_SCREEN_వెడల్పు;
    rect->w = display->current_బహుళకం->w;
    rect->h = display->current_బహుళకం->h;
    తిరిగి true;
}

స్థిర bool N3_DS_Create_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID create_props)
{
    SDL_Display_దత్తాంశం *display_దత్తాంశం;
    SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2 = (SDL_కిటికీ_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_కిటికీ_దత్తాంశం));
    ఒకవేళ (!కిటికీ_దత్తాంశం_2) {
        తిరిగి false;
    }
    display_దత్తాంశం = SDL_Get_Display_Driver_దత్తాంశం_For_కిటికీ(కిటికీ);
    కిటికీ_దత్తాంశం_2->screen = display_దత్తాంశం->screen;
    కిటికీ->అంతర్గత = కిటికీ_దత్తాంశం_2;
    SDL_సమితి_Keyboard_Focus(కిటికీ);
    తిరిగి true;
}

స్థిర శూన్య N3_DS_Destroy_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    ఒకవేళ (!కిటికీ) {
        తిరిగి;
    }
    SDL_free(కిటికీ->అంతర్గత);
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_N3DS
