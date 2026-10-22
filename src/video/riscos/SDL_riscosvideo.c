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
#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_RISCOS

#অন্তর্ভাব "../SDL_sysvideo.h"
#অন্তর্ভাব "../SDL_pixels_c.h"
#অন্তর্ভাব "../../events/SDL_events_c.h"
#অন্তর্ভাব "../../events/SDL_keyboard_c.h"
#অন্তর্ভাব "../../events/SDL_mouse_c.h"

#অন্তর্ভাব "SDL_riscosvideo.h"
#অন্তর্ভাব "SDL_riscosevents_c.h"
#অন্তর্ভাব "SDL_riscosframebuffer_c.h"
#অন্তর্ভাব "SDL_riscosmouse.h"
#অন্তর্ভাব "SDL_riscosmodes.h"
#অন্তর্ভাব "SDL_riscoswindow.h"
#অন্তর্ভাব "SDL_riscosmessagebox.h"

#define RISCOSVID_DRIVER_NAME "riscos"

// Initialization/Query functions
স্থির bool RISCOS_VideoInit(SDL_VideoDevice *_this);
স্থির শূন্য RISCOS_VideoQuit(SDL_VideoDevice *_this);

// RISC OS driver bootstrap functions

স্থির শূন্য RISCOS_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

স্থির SDL_VideoDevice *RISCOS_CreateDevice(শূন্য)
{
    SDL_VideoDevice *device;
    SDL_Video_তথ্য *তথ্য;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, আকার(SDL_VideoDevice));
    যদি (!device) {
        ফেরত ফাঁকা;
    }

    // Initialize internal data
    তথ্য = (SDL_Video_তথ্য *)SDL_calloc(1, আকার(SDL_Video_তথ্য));
    যদি (!তথ্য) {
        SDL_free(device);
        ফেরত ফাঁকা;
    }

    device->internal = তথ্য;

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

    device->মুক্ত = RISCOS_DeleteDevice;

    // TODO: Support windowed mode
    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    ফেরত device;
}

VideoBootStrap RISCOS_bootstrap = {
    RISCOSVID_DRIVER_NAME, "SDL RISC OS video driver",
    RISCOS_CreateDevice,
    RISCOS_ShowMessageBox,
    false
};

স্থির bool RISCOS_VideoInit(SDL_VideoDevice *_this)
{
    যদি (!RISCOS_InitEvents(_this)) {
        ফেরত false;
    }

    যদি (!RISCOS_InitMouse(_this)) {
        ফেরত false;
    }

    // Assume we have a mouse and keyboard
    SDL_AddKeyboard(SDL_DEFAULT_KEYBOARD_ID, ফাঁকা);
    SDL_AddMouse(SDL_DEFAULT_MOUSE_ID, ফাঁকা);

    যদি (!RISCOS_InitModes(_this)) {
        ফেরত false;
    }

    // We're done!
    ফেরত true;
}

স্থির শূন্য RISCOS_VideoQuit(SDL_VideoDevice *_this)
{
    RISCOS_QuitEvents(_this);
}

#endif // SDL_VIDEO_DRIVER_RISCOS
