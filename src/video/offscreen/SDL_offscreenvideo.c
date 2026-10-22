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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_OFFSCREEN

/* Offscreen video driver is similar to dummy driver, however its purpose
 * is enabling applications to use some of the SDL video functionality
 * (notably context creation) while not requiring a display output.
 *
 * An example would be running a graphical program on a headless box
 * for automated testing.
 */

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_offscreenvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_offscreenevents_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_offscreenframebuffer_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_offscreenopengles.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_offscreenvulkan.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_offscreenwindow.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OFFSCREENVID_DRIVER_NAME "offscreen"

// Initialization/Query functions
ਸਥਿਰ bool OFFSCREEN_VideoInit(SDL_VideoDevice *_this);
ਸਥਿਰ bool OFFSCREEN_ਸੈੱਟ_Display_ਬਹੁਲਕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ);
ਸਥਿਰ ਖਾਲੀ OFFSCREEN_VideoQuit(SDL_VideoDevice *_this);

// OFFSCREEN driver bootstrap functions

ਸਥਿਰ ਖਾਲੀ OFFSCREEN_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

ਸਥਿਰ bool OFFSCREEN_ਉਪਲਬਧ(ਅਚਲ ਅੱਖਰ *drivername)
{
    ਅਚਲ ਅੱਖਰ *hint = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    ਜੇ (hint && SDL_strstr(hint, drivername) != ਨਿਰਾ) {
        ਵਾਪਸ true;
    }
    ਵਾਪਸ false;
}

ਸਥਿਰ SDL_VideoDevice *OFFSCREEN_CreateDevice(ਖਾਲੀ)
{
    SDL_VideoDevice *device;

    ਜੇ (!OFFSCREEN_ਉਪਲਬਧ(OFFSCREENVID_DRIVER_NAME)) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, ਆਕਾਰ(SDL_VideoDevice));
    ਜੇ (!device) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    // General video
    device->VideoInit = OFFSCREEN_VideoInit;
    device->VideoQuit = OFFSCREEN_VideoQuit;
    device->ਸੈੱਟ_Display_ਬਹੁਲਕ = OFFSCREEN_ਸੈੱਟ_Display_ਬਹੁਲਕ;
    device->PumpEvents = OFFSCREEN_PumpEvents;
    device->Create_ਖਿੜਕੀ_Framebuffer = SDL_OFFSCREEN_Create_ਖਿੜਕੀ_Framebuffer;
    device->Update_ਖਿੜਕੀ_Framebuffer = SDL_OFFSCREEN_Update_ਖਿੜਕੀ_Framebuffer;
    device->Destroy_ਖਿੜਕੀ_Framebuffer = SDL_OFFSCREEN_Destroy_ਖਿੜਕੀ_Framebuffer;
    device->ਮੁਕਤ = OFFSCREEN_DeleteDevice;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
    // GL context
    device->GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ = OFFSCREEN_GLES_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ;
    device->GL_MakeCurrent = OFFSCREEN_GLES_MakeCurrent;
    device->GL_CreateContext = OFFSCREEN_GLES_CreateContext;
    device->GL_DestroyContext = OFFSCREEN_GLES_DestroyContext;
    device->GL_ਲੱਦੋ_Library = OFFSCREEN_GLES_ਲੱਦੋ_Library;
    device->GL_UnloadLibrary = OFFSCREEN_GLES_UnloadLibrary;
    device->GL_Get_Proc_ਪਤਾ = OFFSCREEN_GLES_Get_Proc_ਪਤਾ;
    device->GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval = OFFSCREEN_GLES_Get_ਅਦਲਾ_ਬਦਲੀ_Interval;
    device->GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval = OFFSCREEN_GLES_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval;
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_VULKAN
    device->Vulkan_ਲੱਦੋ_Library = OFFSCREEN_Vulkan_ਲੱਦੋ_Library;
    device->Vulkan_UnloadLibrary = OFFSCREEN_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = OFFSCREEN_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = OFFSCREEN_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = OFFSCREEN_Vulkan_DestroySurface;
#ਜੇ_ਅੰਤ

    // "Window"
    device->CreateSDLWindow = OFFSCREEN_Create_ਖਿੜਕੀ;
    device->Destroy_ਖਿੜਕੀ = OFFSCREEN_Destroy_ਖਿੜਕੀ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ = OFFSCREEN_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ;

    // TODO: Is this needed?
    device->device_caps = VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;

    ਵਾਪਸ device;
}

VideoBootStrap OFFSCREEN_bootstrap = {
    OFFSCREENVID_DRIVER_NAME, "SDL offscreen video driver",
    OFFSCREEN_CreateDevice,
    ਨਿਰਾ, // no ShowMessageBox implementation
    false
};

ਸਥਿਰ bool OFFSCREEN_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Display_ਬਹੁਲਕ ਬਹੁਲਕ;

    // Use a fake 32-bpp desktop mode
    SDL_zero(ਬਹੁਲਕ);
    ਬਹੁਲਕ.format = SDL_PIXELFORMAT_XRGB8888;
    ਬਹੁਲਕ.w = 1024;
    ਬਹੁਲਕ.h = 768;
    ਜੇ (SDL_ਜੋੜੋ_Basic_Video_Display(&ਬਹੁਲਕ) == 0) {
        ਵਾਪਸ false;
    }

    // We're done!
    ਵਾਪਸ true;
}

ਸਥਿਰ bool OFFSCREEN_ਸੈੱਟ_Display_ਬਹੁਲਕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ)
{
    ਵਾਪਸ true;
}

ਖਾਲੀ OFFSCREEN_VideoQuit(SDL_VideoDevice *_this)
{
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_OFFSCREEN
