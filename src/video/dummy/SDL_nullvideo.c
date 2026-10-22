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

#अगर_घोषित SDL_VIDEO_DRIVER_DUMMY

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

#समावेश "../SDL_sysvideo.h"
#समावेश "../SDL_pixels_c.h"
#समावेश "../../events/SDL_events_c.h"
#अगर_घोषित SDL_निवेश_LINUXEV
#समावेश "../../core/linux/SDL_evdev.h"
#पूर्ण_अगर

#समावेश "SDL_nullvideo.h"
#समावेश "SDL_nullevents_c.h"
#समावेश "SDL_nullframebuffer_c.h"

#घोषणा DUMMYVID_DRIVER_NAME       "dummy"
#घोषणा DUMMYVID_DRIVER_EVDEV_NAME "evdev"

// Initialization/Query functions
अटल bool DUMMY_VideoInitCommon(SDL_VideoDevice *_this);
अटल bool DUMMY_VideoInit(SDL_VideoDevice *_this);
अटल व्योम DUMMY_VideoQuit(SDL_VideoDevice *_this);
#अगर_घोषित SDL_निवेश_LINUXEV
अटल bool DUMMY_EVDEV_VideoInit(SDL_VideoDevice *_this);
अटल व्योम DUMMY_EVDEV_VideoQuit(SDL_VideoDevice *_this);
#पूर्ण_अगर

अटल bool DUMMY_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, window->pending.x, window->pending.y);
    वापस true;
}

अटल व्योम DUMMY_Set_Window_आकार(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->pending.w, window->pending.h);
}

// DUMMY driver bootstrap functions

अटल bool DUMMY_Available(स्थिर अक्षर *drivername)
{
    स्थिर अक्षर *hint = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    अगर (hint && SDL_strstr(hint, drivername) != शून्य) {
        वापस true;
    }
    वापस false;
}

अटल व्योम DUMMY_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

अटल SDL_VideoDevice *DUMMY_InternalCreateDevice(स्थिर अक्षर *enable_hint)
{
    SDL_VideoDevice *device;

    अगर (!DUMMY_Available(enable_hint)) {
        वापस शून्य;
    }

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, माप(SDL_VideoDevice));
    अगर (!device) {
        वापस शून्य;
    }

    // Set the function pointers
    device->VideoInit = DUMMY_VideoInit;
    device->VideoQuit = DUMMY_VideoQuit;
    device->PumpEvents = DUMMY_PumpEvents;
    device->Set_Window_आकार = DUMMY_Set_Window_आकार;
    device->SetWindowPosition = DUMMY_SetWindowPosition;
    device->CreateWindowFramebuffer = SDL_DUMMY_CreateWindowFramebuffer;
    device->UpdateWindowFramebuffer = SDL_DUMMY_UpdateWindowFramebuffer;
    device->DestroyWindowFramebuffer = SDL_DUMMY_DestroyWindowFramebuffer;
    device->मुक्त = DUMMY_DeleteDevice;

    वापस device;
}

अटल SDL_VideoDevice *DUMMY_CreateDevice(व्योम)
{
    वापस DUMMY_InternalCreateDevice(DUMMYVID_DRIVER_NAME);
}

VideoBootStrap DUMMY_bootstrap = {
    DUMMYVID_DRIVER_NAME, "SDL dummy video driver",
    DUMMY_CreateDevice,
    शून्य, // no ShowMessageBox implementation
    false
};

#अगर_घोषित SDL_निवेश_LINUXEV

अटल bool DUMMY_EVDEV_VideoInit(SDL_VideoDevice *_this)
{
    अगर (!DUMMY_VideoInitCommon(_this)) {
        वापस false;
    }

    SDL_EVDEV_Init();
    वापस true;
}

अटल व्योम DUMMY_EVDEV_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_EVDEV_Quit();
}

अटल व्योम DUMMY_EVDEV_Poll(SDL_VideoDevice *_this)
{
    (व्योम)_this;
    SDL_EVDEV_Poll();
}

अटल SDL_VideoDevice *DUMMY_EVDEV_CreateDevice(व्योम)
{
    SDL_VideoDevice *device = DUMMY_InternalCreateDevice(DUMMYVID_DRIVER_EVDEV_NAME);
    अगर (device) {
        device->VideoInit = DUMMY_EVDEV_VideoInit;
        device->VideoQuit = DUMMY_EVDEV_VideoQuit;
        device->PumpEvents = DUMMY_EVDEV_Poll;
    }
    वापस device;
}

VideoBootStrap DUMMY_evdev_bootstrap = {
    DUMMYVID_DRIVER_EVDEV_NAME, "SDL dummy video driver with evdev",
    DUMMY_EVDEV_CreateDevice,
    शून्य, // no ShowMessageBox implementation
    false
};

#पूर्ण_अगर // SDL_INPUT_LINUXEV

अटल bool DUMMY_SetRelativeMouseMode(bool enabled)
{
    वापस true;
}

bool DUMMY_VideoInitCommon(SDL_VideoDevice *_this)
{
    SDL_DisplayMode mode;

    // Use a fake 32-bpp desktop mode
    SDL_zero(mode);
    mode.format = SDL_PIXELFORMAT_XRGB8888;
    mode.w = 1024;
    mode.h = 768;
    अगर (SDL_AddBasicVideoDisplay(&mode) == 0) {
        वापस false;
    }

    वापस true;
}

bool DUMMY_VideoInit(SDL_VideoDevice *_this)
{
    अगर (!DUMMY_VideoInitCommon(_this)) {
        वापस false;
    }

    SDL_GetMouse()->SetRelativeMouseMode = DUMMY_SetRelativeMouseMode;
    वापस true;
}

व्योम DUMMY_VideoQuit(SDL_VideoDevice *_this)
{
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_DUMMY
