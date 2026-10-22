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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_OFFSCREEN

/* Offscreen video driver is similar to dummy driver, however its purpose
 * is enabling applications to use some of the SDL video functionality
 * (notably context creation) while not requiring a display output.
 *
 * An example would be running a graphical program on a headless box
 * for automated testing.
 */

#ଅନ୍ତର୍ଭାଵ "SDL_offscreenvideo.h"
#ଅନ୍ତର୍ଭାଵ "SDL_offscreenevents_c.h"
#ଅନ୍ତର୍ଭାଵ "SDL_offscreenframebuffer_c.h"
#ଅନ୍ତର୍ଭାଵ "SDL_offscreenopengles.h"
#ଅନ୍ତର୍ଭାଵ "SDL_offscreenvulkan.h"
#ଅନ୍ତର୍ଭାଵ "SDL_offscreenwindow.h"

#define OFFSCREENVID_DRIVER_NAME "offscreen"

// Initialization/Query functions
ସ୍ଥିର bool OFFSCREEN_VideoInit(SDL_VideoDevice *_this);
ସ୍ଥିର bool OFFSCREEN_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode);
ସ୍ଥିର ଶୂନ୍ୟ OFFSCREEN_VideoQuit(SDL_VideoDevice *_this);

// OFFSCREEN driver bootstrap functions

ସ୍ଥିର ଶୂନ୍ୟ OFFSCREEN_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

ସ୍ଥିର bool OFFSCREEN_Available(ଅଚଳ ଅକ୍ଷର *drivername)
{
    ଅଚଳ ଅକ୍ଷର *hint = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    ଯଦି (hint && SDL_strstr(hint, drivername) != ଖାଲି) {
        ଫେରନ୍ତୁ true;
    }
    ଫେରନ୍ତୁ false;
}

ସ୍ଥିର SDL_VideoDevice *OFFSCREEN_CreateDevice(ଶୂନ୍ୟ)
{
    SDL_VideoDevice *device;

    ଯଦି (!OFFSCREEN_Available(OFFSCREENVID_DRIVER_NAME)) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, ଆକାର(SDL_VideoDevice));
    ଯଦି (!device) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    // General video
    device->VideoInit = OFFSCREEN_VideoInit;
    device->VideoQuit = OFFSCREEN_VideoQuit;
    device->SetDisplayMode = OFFSCREEN_SetDisplayMode;
    device->PumpEvents = OFFSCREEN_PumpEvents;
    device->CreateWindowFramebuffer = SDL_OFFSCREEN_CreateWindowFramebuffer;
    device->UpdateWindowFramebuffer = SDL_OFFSCREEN_UpdateWindowFramebuffer;
    device->DestroyWindowFramebuffer = SDL_OFFSCREEN_DestroyWindowFramebuffer;
    device->ମୁକ୍ତ = OFFSCREEN_DeleteDevice;

#ifdef SDL_VIDEO_OPENGL_EGL
    // GL context
    device->GL_SwapWindow = OFFSCREEN_GLES_SwapWindow;
    device->GL_MakeCurrent = OFFSCREEN_GLES_MakeCurrent;
    device->GL_CreateContext = OFFSCREEN_GLES_CreateContext;
    device->GL_DestroyContext = OFFSCREEN_GLES_DestroyContext;
    device->GL_LoadLibrary = OFFSCREEN_GLES_LoadLibrary;
    device->GL_UnloadLibrary = OFFSCREEN_GLES_UnloadLibrary;
    device->GL_GetProcAddress = OFFSCREEN_GLES_GetProcAddress;
    device->GL_GetSwapInterval = OFFSCREEN_GLES_GetSwapInterval;
    device->GL_SetSwapInterval = OFFSCREEN_GLES_SetSwapInterval;
#endif

#ifdef SDL_VIDEO_VULKAN
    device->Vulkan_LoadLibrary = OFFSCREEN_Vulkan_LoadLibrary;
    device->Vulkan_UnloadLibrary = OFFSCREEN_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = OFFSCREEN_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = OFFSCREEN_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = OFFSCREEN_Vulkan_DestroySurface;
#endif

    // "Window"
    device->CreateSDLWindow = OFFSCREEN_CreateWindow;
    device->DestroyWindow = OFFSCREEN_DestroyWindow;
    device->SetWindowSize = OFFSCREEN_SetWindowSize;

    // TODO: Is this needed?
    device->device_caps = VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;

    ଫେରନ୍ତୁ device;
}

VideoBootStrap OFFSCREEN_bootstrap = {
    OFFSCREENVID_DRIVER_NAME, "SDL offscreen video driver",
    OFFSCREEN_CreateDevice,
    ଖାଲି, // no ShowMessageBox implementation
    false
};

ସ୍ଥିର bool OFFSCREEN_VideoInit(SDL_VideoDevice *_this)
{
    SDL_DisplayMode mode;

    // Use a fake 32-bpp desktop mode
    SDL_zero(mode);
    mode.format = SDL_PIXELFORMAT_XRGB8888;
    mode.w = 1024;
    mode.h = 768;
    ଯଦି (SDL_AddBasicVideoDisplay(&mode) == 0) {
        ଫେରନ୍ତୁ false;
    }

    // We're done!
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool OFFSCREEN_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ OFFSCREEN_VideoQuit(SDL_VideoDevice *_this)
{
}

#endif // SDL_VIDEO_DRIVER_OFFSCREEN
