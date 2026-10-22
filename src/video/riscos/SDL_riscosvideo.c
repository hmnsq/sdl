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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_RISCOS

#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../SDL_pixels_c.h"
#अन्तर्भाव "../../events/SDL_events_c.h"
#अन्तर्भाव "../../events/SDL_keyboard_c.h"
#अन्तर्भाव "../../events/SDL_mouse_c.h"

#अन्तर्भाव "SDL_riscosvideo.h"
#अन्तर्भाव "SDL_riscosevents_c.h"
#अन्तर्भाव "SDL_riscosframebuffer_c.h"
#अन्तर्भाव "SDL_riscosmouse.h"
#अन्तर्भाव "SDL_riscosmodes.h"
#अन्तर्भाव "SDL_riscoswindow.h"
#अन्तर्भाव "SDL_riscosmessagebox.h"

#परिभाषय RISCOSVID_DRIVER_NAME "riscos"

// Initialization/Query functions
स्थिर bool RISCOS_VideoInit(SDL_VideoDevice *_this);
स्थिर शून्य RISCOS_VideoQuit(SDL_VideoDevice *_this);

// RISC OS driver bootstrap functions

स्थिर शून्य RISCOS_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->आन्तरिकम्);
    SDL_free(device);
}

स्थिर SDL_VideoDevice *RISCOS_CreateDevice(शून्य)
{
    SDL_VideoDevice *device;
    SDL_Video_दत्त *दत्त;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, परिमाण(SDL_VideoDevice));
    यदि (!device) {
        प्रत्यागम रिक्त;
    }

    // Initialize internal data
    दत्त = (SDL_Video_दत्त *)SDL_calloc(1, परिमाण(SDL_Video_दत्त));
    यदि (!दत्त) {
        SDL_free(device);
        प्रत्यागम रिक्त;
    }

    device->आन्तरिकम् = दत्त;

    // Set the function pointers
    device->VideoInit = RISCOS_VideoInit;
    device->VideoQuit = RISCOS_VideoQuit;
    device->PumpEvents = RISCOS_PumpEvents;

    device->GetDisplayModes = RISCOS_GetDisplayModes;
    device->समुच्चयः_Display_बहुलकम् = RISCOS_समुच्चयः_Display_बहुलकम्;

    device->CreateSDLWindow = RISCOS_Create_गवाक्षः;
    device->Destroy_गवाक्षः = RISCOS_Destroy_गवाक्षः;

    device->Create_गवाक्षः_Framebuffer = RISCOS_Create_गवाक्षः_Framebuffer;
    device->Update_गवाक्षः_Framebuffer = RISCOS_Update_गवाक्षः_Framebuffer;
    device->Destroy_गवाक्षः_Framebuffer = RISCOS_Destroy_गवाक्षः_Framebuffer;

    device->मुक्त = RISCOS_DeleteDevice;

    // TODO: Support windowed mode
    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    प्रत्यागम device;
}

VideoBootStrap RISCOS_bootstrap = {
    RISCOSVID_DRIVER_NAME, "SDL RISC OS video driver",
    RISCOS_CreateDevice,
    RISCOS_Show_सन्देशः_Box,
    false
};

स्थिर bool RISCOS_VideoInit(SDL_VideoDevice *_this)
{
    यदि (!RISCOS_InitEvents(_this)) {
        प्रत्यागम false;
    }

    यदि (!RISCOS_InitMouse(_this)) {
        प्रत्यागम false;
    }

    // Assume we have a mouse and keyboard
    SDL_सङ्कलय_Keyboard(SDL_DEFAULT_KEYBOARD_ID, रिक्त);
    SDL_सङ्कलय_Mouse(SDL_DEFAULT_MOUSE_ID, रिक्त);

    यदि (!RISCOS_InitModes(_this)) {
        प्रत्यागम false;
    }

    // We're done!
    प्रत्यागम true;
}

स्थिर शून्य RISCOS_VideoQuit(SDL_VideoDevice *_this)
{
    RISCOS_QuitEvents(_this);
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_RISCOS
