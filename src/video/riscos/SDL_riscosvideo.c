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

#నిర్వచితమైతే SDL_VIDEO_DRIVER_RISCOS

#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "../SDL_pixels_c.h"
#అన్తర్భావ "../../events/SDL_events_c.h"
#అన్తర్భావ "../../events/SDL_keyboard_c.h"
#అన్తర్భావ "../../events/SDL_mouse_c.h"

#అన్తర్భావ "SDL_riscosvideo.h"
#అన్తర్భావ "SDL_riscosevents_c.h"
#అన్తర్భావ "SDL_riscosframebuffer_c.h"
#అన్తర్భావ "SDL_riscosmouse.h"
#అన్తర్భావ "SDL_riscosmodes.h"
#అన్తర్భావ "SDL_riscoswindow.h"
#అన్తర్భావ "SDL_riscosmessagebox.h"

#నిర్వచించు RISCOSVID_DRIVER_NAME "riscos"

// Initialization/Query functions
స్థిర bool RISCOS_VideoInit(SDL_VideoDevice *_this);
స్థిర శూన్య RISCOS_VideoQuit(SDL_VideoDevice *_this);

// RISC OS driver bootstrap functions

స్థిర శూన్య RISCOS_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->అంతర్గత);
    SDL_free(device);
}

స్థిర SDL_VideoDevice *RISCOS_CreateDevice(శూన్య)
{
    SDL_VideoDevice *device;
    SDL_Video_దత్తాంశం *దత్తాంశం;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, పరిమాణం(SDL_VideoDevice));
    ఒకవేళ (!device) {
        తిరిగి ఖాళీ;
    }

    // Initialize internal data
    దత్తాంశం = (SDL_Video_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_Video_దత్తాంశం));
    ఒకవేళ (!దత్తాంశం) {
        SDL_free(device);
        తిరిగి ఖాళీ;
    }

    device->అంతర్గత = దత్తాంశం;

    // Set the function pointers
    device->VideoInit = RISCOS_VideoInit;
    device->VideoQuit = RISCOS_VideoQuit;
    device->PumpEvents = RISCOS_PumpEvents;

    device->GetDisplayModes = RISCOS_GetDisplayModes;
    device->సమితి_Display_బహుళకం = RISCOS_సమితి_Display_బహుళకం;

    device->CreateSDLWindow = RISCOS_Create_కిటికీ;
    device->Destroy_కిటికీ = RISCOS_Destroy_కిటికీ;

    device->Create_కిటికీ_Framebuffer = RISCOS_Create_కిటికీ_Framebuffer;
    device->Update_కిటికీ_Framebuffer = RISCOS_Update_కిటికీ_Framebuffer;
    device->Destroy_కిటికీ_Framebuffer = RISCOS_Destroy_కిటికీ_Framebuffer;

    device->విడుదల = RISCOS_DeleteDevice;

    // TODO: Support windowed mode
    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    తిరిగి device;
}

VideoBootStrap RISCOS_bootstrap = {
    RISCOSVID_DRIVER_NAME, "SDL RISC OS video driver",
    RISCOS_CreateDevice,
    RISCOS_Show_సందేశం_Box,
    false
};

స్థిర bool RISCOS_VideoInit(SDL_VideoDevice *_this)
{
    ఒకవేళ (!RISCOS_InitEvents(_this)) {
        తిరిగి false;
    }

    ఒకవేళ (!RISCOS_InitMouse(_this)) {
        తిరిగి false;
    }

    // Assume we have a mouse and keyboard
    SDL_కూడు_Keyboard(SDL_DEFAULT_KEYBOARD_ID, ఖాళీ);
    SDL_కూడు_Mouse(SDL_DEFAULT_MOUSE_ID, ఖాళీ);

    ఒకవేళ (!RISCOS_InitModes(_this)) {
        తిరిగి false;
    }

    // We're done!
    తిరిగి true;
}

స్థిర శూన్య RISCOS_VideoQuit(SDL_VideoDevice *_this)
{
    RISCOS_QuitEvents(_this);
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_RISCOS
