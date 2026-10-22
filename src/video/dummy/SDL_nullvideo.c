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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_DUMMY

/* Dummy SDL video driver implementation; this is just enough to make an
 *  SDL-based application THINK it's got a working video driver, for
 *  applications that call SDL_Init(SDL_INIT_VIDEO) when they don't need it,
 *  and also for use as a collection of stubs when porting SDL to a new
 *  platform for which you haven't yet written a valid video driver.
 *
 * This is also a great way to determine bottlenecks: if you think that SDL
 *  is a performance problem for a given platform, enable this driver, and
 *  then see if your application runs faster without video overhead.
 *
 * Initial work by Ryan C. Gordon (icculus@icculus.org). A good portion
 *  of this was cut-and-pasted from Stephane Peter's work in the AAlib
 *  SDL video driver.  Renamed to "DUMMY" by Sam Lantinga.
 */

#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../SDL_pixels_c.h"
#अन्तर्भाव "../../events/SDL_events_c.h"
#यदि_परिभाषितम् SDL_निवेशः_LINUXEV
#अन्तर्भाव "../../core/linux/SDL_evdev.h"
#यदि_अन्तः

#अन्तर्भाव "SDL_nullvideo.h"
#अन्तर्भाव "SDL_nullevents_c.h"
#अन्तर्भाव "SDL_nullframebuffer_c.h"

#परिभाषय DUMMYVID_DRIVER_NAME       "dummy"
#परिभाषय DUMMYVID_DRIVER_EVDEV_NAME "evdev"

// Initialization/Query functions
स्थिर bool DUMMY_VideoInitCommon(SDL_VideoDevice *_this);
स्थिर bool DUMMY_VideoInit(SDL_VideoDevice *_this);
स्थिर शून्य DUMMY_VideoQuit(SDL_VideoDevice *_this);
#यदि_परिभाषितम् SDL_निवेशः_LINUXEV
स्थिर bool DUMMY_EVDEV_VideoInit(SDL_VideoDevice *_this);
स्थिर शून्य DUMMY_EVDEV_VideoQuit(SDL_VideoDevice *_this);
#यदि_अन्तः

स्थिर bool DUMMY_समुच्चयः_गवाक्षः_Position(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_MOVED, गवाक्षः->pending.x, गवाक्षः->pending.y);
    प्रत्यागम true;
}

स्थिर शून्य DUMMY_समुच्चयः_गवाक्षः_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_RESIZED, गवाक्षः->pending.w, गवाक्षः->pending.h);
}

// DUMMY driver bootstrap functions

स्थिर bool DUMMY_उपलब्धम्(ध्रुव वर्ण *drivername)
{
    ध्रुव वर्ण *hint = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    यदि (hint && SDL_strstr(hint, drivername) != रिक्त) {
        प्रत्यागम true;
    }
    प्रत्यागम false;
}

स्थिर शून्य DUMMY_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

स्थिर SDL_VideoDevice *DUMMY_आन्तरिकम्_Create_Device(ध्रुव वर्ण *enable_hint)
{
    SDL_VideoDevice *device;

    यदि (!DUMMY_उपलब्धम्(enable_hint)) {
        प्रत्यागम रिक्त;
    }

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, परिमाण(SDL_VideoDevice));
    यदि (!device) {
        प्रत्यागम रिक्त;
    }

    // Set the function pointers
    device->VideoInit = DUMMY_VideoInit;
    device->VideoQuit = DUMMY_VideoQuit;
    device->PumpEvents = DUMMY_PumpEvents;
    device->समुच्चयः_गवाक्षः_आकार = DUMMY_समुच्चयः_गवाक्षः_आकार;
    device->समुच्चयः_गवाक्षः_Position = DUMMY_समुच्चयः_गवाक्षः_Position;
    device->Create_गवाक्षः_Framebuffer = SDL_DUMMY_Create_गवाक्षः_Framebuffer;
    device->Update_गवाक्षः_Framebuffer = SDL_DUMMY_Update_गवाक्षः_Framebuffer;
    device->Destroy_गवाक्षः_Framebuffer = SDL_DUMMY_Destroy_गवाक्षः_Framebuffer;
    device->मुक्त = DUMMY_DeleteDevice;

    प्रत्यागम device;
}

स्थिर SDL_VideoDevice *DUMMY_CreateDevice(शून्य)
{
    प्रत्यागम DUMMY_आन्तरिकम्_Create_Device(DUMMYVID_DRIVER_NAME);
}

VideoBootStrap DUMMY_bootstrap = {
    DUMMYVID_DRIVER_NAME, "SDL dummy video driver",
    DUMMY_CreateDevice,
    रिक्त, // no ShowMessageBox implementation
    false
};

#यदि_परिभाषितम् SDL_निवेशः_LINUXEV

स्थिर bool DUMMY_EVDEV_VideoInit(SDL_VideoDevice *_this)
{
    यदि (!DUMMY_VideoInitCommon(_this)) {
        प्रत्यागम false;
    }

    SDL_EVDEV_Init();
    प्रत्यागम true;
}

स्थिर शून्य DUMMY_EVDEV_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_EVDEV_Quit();
}

स्थिर शून्य DUMMY_EVDEV_Poll(SDL_VideoDevice *_this)
{
    (शून्य)_this;
    SDL_EVDEV_Poll();
}

स्थिर SDL_VideoDevice *DUMMY_EVDEV_CreateDevice(शून्य)
{
    SDL_VideoDevice *device = DUMMY_आन्तरिकम्_Create_Device(DUMMYVID_DRIVER_EVDEV_NAME);
    यदि (device) {
        device->VideoInit = DUMMY_EVDEV_VideoInit;
        device->VideoQuit = DUMMY_EVDEV_VideoQuit;
        device->PumpEvents = DUMMY_EVDEV_Poll;
    }
    प्रत्यागम device;
}

VideoBootStrap DUMMY_evdev_bootstrap = {
    DUMMYVID_DRIVER_EVDEV_NAME, "SDL dummy video driver with evdev",
    DUMMY_EVDEV_CreateDevice,
    रिक्त, // no ShowMessageBox implementation
    false
};

#यदि_अन्तः // SDL_INPUT_LINUXEV

स्थिर bool DUMMY_समुच्चयः_Relative_Mouse_बहुलकम्(bool enabled)
{
    प्रत्यागम true;
}

bool DUMMY_VideoInitCommon(SDL_VideoDevice *_this)
{
    SDL_Display_बहुलकम् बहुलकम्;

    // Use a fake 32-bpp desktop mode
    SDL_zero(बहुलकम्);
    बहुलकम्.format = SDL_PIXELFORMAT_XRGB8888;
    बहुलकम्.w = 1024;
    बहुलकम्.h = 768;
    यदि (SDL_सङ्कलय_Basic_Video_Display(&बहुलकम्) == 0) {
        प्रत्यागम false;
    }

    प्रत्यागम true;
}

bool DUMMY_VideoInit(SDL_VideoDevice *_this)
{
    यदि (!DUMMY_VideoInitCommon(_this)) {
        प्रत्यागम false;
    }

    SDL_GetMouse()->समुच्चयः_Relative_Mouse_बहुलकम् = DUMMY_समुच्चयः_Relative_Mouse_बहुलकम्;
    प्रत्यागम true;
}

शून्य DUMMY_VideoQuit(SDL_VideoDevice *_this)
{
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_DUMMY
