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
#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_RISCOS

#شامل "../SDL_sysvideo.h"
#شامل "../SDL_pixels_c.h"
#شامل "../../events/SDL_events_c.h"
#شامل "../../events/SDL_keyboard_c.h"
#شامل "../../events/SDL_mouse_c.h"

#شامل "SDL_riscosvideo.h"
#شامل "SDL_riscosevents_c.h"
#شامل "SDL_riscosframebuffer_c.h"
#شامل "SDL_riscosmouse.h"
#شامل "SDL_riscosmodes.h"
#شامل "SDL_riscoswindow.h"
#شامل "SDL_riscosmessagebox.h"

#تعریف_کرو RISCOSVID_DRIVER_NAME "riscos"

// Initialization/Query functions
ساکن bool RISCOS_VideoInit(SDL_VideoDevice *_this);
ساکن خالی RISCOS_VideoQuit(SDL_VideoDevice *_this);

// RISC OS driver bootstrap functions

ساکن خالی RISCOS_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->اندرونی_2);
    SDL_free(device);
}

ساکن SDL_VideoDevice *RISCOS_CreateDevice(خالی)
{
    SDL_VideoDevice *device;
    SDL_Video_ڈیٹا *ڈیٹا;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    اگر (!device) {
        واپس تہی;
    }

    // Initialize internal data
    ڈیٹا = (SDL_Video_ڈیٹا *)SDL_calloc(1, حجم(SDL_Video_ڈیٹا));
    اگر (!ڈیٹا) {
        SDL_free(device);
        واپس تہی;
    }

    device->اندرونی_2 = ڈیٹا;

    // Set the function pointers
    device->VideoInit = RISCOS_VideoInit;
    device->VideoQuit = RISCOS_VideoQuit;
    device->PumpEvents = RISCOS_PumpEvents;

    device->GetDisplayModes = RISCOS_GetDisplayModes;
    device->سیٹ_Display_منوال = RISCOS_سیٹ_Display_منوال;

    device->CreateSDLWindow = RISCOS_Create_کھڑکی;
    device->Destroy_کھڑکی = RISCOS_Destroy_کھڑکی;

    device->Create_کھڑکی_Framebuffer = RISCOS_Create_کھڑکی_Framebuffer;
    device->Update_کھڑکی_Framebuffer = RISCOS_Update_کھڑکی_Framebuffer;
    device->Destroy_کھڑکی_Framebuffer = RISCOS_Destroy_کھڑکی_Framebuffer;

    device->آزاد = RISCOS_DeleteDevice;

    // TODO: Support windowed mode
    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    واپس device;
}

VideoBootStrap RISCOS_bootstrap = {
    RISCOSVID_DRIVER_NAME, "SDL RISC OS video driver",
    RISCOS_CreateDevice,
    RISCOS_Show_پیغام_Box,
    false
};

ساکن bool RISCOS_VideoInit(SDL_VideoDevice *_this)
{
    اگر (!RISCOS_InitEvents(_this)) {
        واپس false;
    }

    اگر (!RISCOS_InitMouse(_this)) {
        واپس false;
    }

    // Assume we have a mouse and keyboard
    SDL_جوڑو_Keyboard(SDL_DEFAULT_KEYBOARD_ID, تہی);
    SDL_جوڑو_Mouse(SDL_DEFAULT_MOUSE_ID, تہی);

    اگر (!RISCOS_InitModes(_this)) {
        واپس false;
    }

    // We're done!
    واپس true;
}

ساکن خالی RISCOS_VideoQuit(SDL_VideoDevice *_this)
{
    RISCOS_QuitEvents(_this);
}

#اگر_ختم // SDL_VIDEO_DRIVER_RISCOS
