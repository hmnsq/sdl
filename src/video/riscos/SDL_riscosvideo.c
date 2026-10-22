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

#अगर_घोषित SDL_VIDEO_DRIVER_RISCOS

#समावेश "../SDL_sysvideo.h"
#समावेश "../SDL_pixels_c.h"
#समावेश "../../events/SDL_events_c.h"
#समावेश "../../events/SDL_keyboard_c.h"
#समावेश "../../events/SDL_mouse_c.h"

#समावेश "SDL_riscosvideo.h"
#समावेश "SDL_riscosevents_c.h"
#समावेश "SDL_riscosframebuffer_c.h"
#समावेश "SDL_riscosmouse.h"
#समावेश "SDL_riscosmodes.h"
#समावेश "SDL_riscoswindow.h"
#समावेश "SDL_riscosmessagebox.h"

#घोषणा RISCOSVID_DRIVER_NAME "riscos"

// Initialization/Query functions
अटल bool RISCOS_VideoInit(SDL_VideoDevice *_this);
अटल व्योम RISCOS_VideoQuit(SDL_VideoDevice *_this);

// RISC OS driver bootstrap functions

अटल व्योम RISCOS_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

अटल SDL_VideoDevice *RISCOS_CreateDevice(व्योम)
{
    SDL_VideoDevice *device;
    SDL_Video_तथ्य *तथ्य;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, माप(SDL_VideoDevice));
    अगर (!device) {
        वापस शून्य;
    }

    // Initialize internal data
    तथ्य = (SDL_Video_तथ्य *)SDL_calloc(1, माप(SDL_Video_तथ्य));
    अगर (!तथ्य) {
        SDL_free(device);
        वापस शून्य;
    }

    device->internal = तथ्य;

    // Set the function pointers
    device->VideoInit = RISCOS_VideoInit;
    device->VideoQuit = RISCOS_VideoQuit;
    device->PumpEvents = RISCOS_PumpEvents;

    device->GetDisplayModes = RISCOS_GetDisplayModes;
    device->SetDisplayMode = RISCOS_SetDisplayMode;

    device->CreateSDLWindow = RISCOS_CreateWindow;
    device->DestroyWindow = RISCOS_DestroyWindow;

    device->CreateWindowFramebuffer = RISCOS_CreateWindowFramebuffer;
    device->UpdateWindowFramebuffer = RISCOS_UpdateWindowFramebuffer;
    device->DestroyWindowFramebuffer = RISCOS_DestroyWindowFramebuffer;

    device->मुक्त = RISCOS_DeleteDevice;

    // TODO: Support windowed mode
    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    वापस device;
}

VideoBootStrap RISCOS_bootstrap = {
    RISCOSVID_DRIVER_NAME, "SDL RISC OS video driver",
    RISCOS_CreateDevice,
    RISCOS_ShowMessageBox,
    false
};

अटल bool RISCOS_VideoInit(SDL_VideoDevice *_this)
{
    अगर (!RISCOS_InitEvents(_this)) {
        वापस false;
    }

    अगर (!RISCOS_InitMouse(_this)) {
        वापस false;
    }

    // Assume we have a mouse and keyboard
    SDL_AddKeyboard(SDL_DEFAULT_KEYBOARD_ID, शून्य);
    SDL_AddMouse(SDL_DEFAULT_MOUSE_ID, शून्य);

    अगर (!RISCOS_InitModes(_this)) {
        वापस false;
    }

    // We're done!
    वापस true;
}

अटल व्योम RISCOS_VideoQuit(SDL_VideoDevice *_this)
{
    RISCOS_QuitEvents(_this);
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_RISCOS
