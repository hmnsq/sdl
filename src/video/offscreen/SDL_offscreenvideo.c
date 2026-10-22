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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_OFFSCREEN

/* Offscreen video driver is similar to dummy driver, however its purpose
 * is enabling applications to use some of the SDL video functionality
 * (notably context creation) while not requiring a display output.
 *
 * An example would be running a graphical program on a headless box
 * for automated testing.
 */

#ಅನ್ತರ್ಭಾವ "SDL_offscreenvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_offscreenevents_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_offscreenframebuffer_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_offscreenopengles.h"
#ಅನ್ತರ್ಭಾವ "SDL_offscreenvulkan.h"
#ಅನ್ತರ್ಭಾವ "SDL_offscreenwindow.h"

#ವ್ಯಾಖ್ಯಾನಿಸು OFFSCREENVID_DRIVER_NAME "offscreen"

// Initialization/Query functions
ಸ್ಥಿರ bool OFFSCREEN_VideoInit(SDL_VideoDevice *_this);
ಸ್ಥಿರ bool OFFSCREEN_ಗಣ_Display_ಬಹುಲಕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ);
ಸ್ಥಿರ ಶೂನ್ಯ OFFSCREEN_VideoQuit(SDL_VideoDevice *_this);

// OFFSCREEN driver bootstrap functions

ಸ್ಥಿರ ಶೂನ್ಯ OFFSCREEN_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

ಸ್ಥಿರ bool OFFSCREEN_ಲಭ್ಯ(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *drivername)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *hint = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    ಆದರೆ (hint && SDL_strstr(hint, drivername) != ಖಾಲಿ) {
        ಹಿಂತಿರುಗಿ true;
    }
    ಹಿಂತಿರುಗಿ false;
}

ಸ್ಥಿರ SDL_VideoDevice *OFFSCREEN_CreateDevice(ಶೂನ್ಯ)
{
    SDL_VideoDevice *device;

    ಆದರೆ (!OFFSCREEN_ಲಭ್ಯ(OFFSCREENVID_DRIVER_NAME)) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, ಗಾತ್ರ(SDL_VideoDevice));
    ಆದರೆ (!device) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    // General video
    device->VideoInit = OFFSCREEN_VideoInit;
    device->VideoQuit = OFFSCREEN_VideoQuit;
    device->ಗಣ_Display_ಬಹುಲಕ = OFFSCREEN_ಗಣ_Display_ಬಹುಲಕ;
    device->PumpEvents = OFFSCREEN_PumpEvents;
    device->Create_ಕಿಟಕಿ_Framebuffer = SDL_OFFSCREEN_Create_ಕಿಟಕಿ_Framebuffer;
    device->Update_ಕಿಟಕಿ_Framebuffer = SDL_OFFSCREEN_Update_ಕಿಟಕಿ_Framebuffer;
    device->Destroy_ಕಿಟಕಿ_Framebuffer = SDL_OFFSCREEN_Destroy_ಕಿಟಕಿ_Framebuffer;
    device->ಬಿಡುಗಡೆ = OFFSCREEN_DeleteDevice;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
    // GL context
    device->GL_ಅದಲುಬದಲು_ಕಿಟಕಿ = OFFSCREEN_GLES_ಅದಲುಬದಲು_ಕಿಟಕಿ;
    device->GL_MakeCurrent = OFFSCREEN_GLES_MakeCurrent;
    device->GL_CreateContext = OFFSCREEN_GLES_CreateContext;
    device->GL_DestroyContext = OFFSCREEN_GLES_DestroyContext;
    device->GL_ತುಂಬು_Library = OFFSCREEN_GLES_ತುಂಬು_Library;
    device->GL_UnloadLibrary = OFFSCREEN_GLES_UnloadLibrary;
    device->GL_Get_Proc_ವಿಳಾಸ = OFFSCREEN_GLES_Get_Proc_ವಿಳಾಸ;
    device->GL_Get_ಅದಲುಬದಲು_Interval = OFFSCREEN_GLES_Get_ಅದಲುಬದಲು_Interval;
    device->GL_ಗಣ_ಅದಲುಬದಲು_Interval = OFFSCREEN_GLES_ಗಣ_ಅದಲುಬದಲು_Interval;
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_VULKAN
    device->Vulkan_ತುಂಬು_Library = OFFSCREEN_Vulkan_ತುಂಬು_Library;
    device->Vulkan_UnloadLibrary = OFFSCREEN_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = OFFSCREEN_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = OFFSCREEN_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = OFFSCREEN_Vulkan_DestroySurface;
#ಆದರೆ_ಅಂತ್ಯ

    // "Window"
    device->CreateSDLWindow = OFFSCREEN_Create_ಕಿಟಕಿ;
    device->Destroy_ಕಿಟಕಿ = OFFSCREEN_Destroy_ಕಿಟಕಿ;
    device->ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ = OFFSCREEN_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ;

    // TODO: Is this needed?
    device->device_caps = VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;

    ಹಿಂತಿರುಗಿ device;
}

VideoBootStrap OFFSCREEN_bootstrap = {
    OFFSCREENVID_DRIVER_NAME, "SDL offscreen video driver",
    OFFSCREEN_CreateDevice,
    ಖಾಲಿ, // no ShowMessageBox implementation
    false
};

ಸ್ಥಿರ bool OFFSCREEN_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Display_ಬಹುಲಕ ಬಹುಲಕ;

    // Use a fake 32-bpp desktop mode
    SDL_zero(ಬಹುಲಕ);
    ಬಹುಲಕ.format = SDL_PIXELFORMAT_XRGB8888;
    ಬಹುಲಕ.w = 1024;
    ಬಹುಲಕ.h = 768;
    ಆದರೆ (SDL_ಕೂಡಿಸು_Basic_Video_Display(&ಬಹುಲಕ) == 0) {
        ಹಿಂತಿರುಗಿ false;
    }

    // We're done!
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool OFFSCREEN_ಗಣ_Display_ಬಹುಲಕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ)
{
    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ OFFSCREEN_VideoQuit(SDL_VideoDevice *_this)
{
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_OFFSCREEN
