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
#ضمن "SDL_internal.h"

#اگر_تعریف_شده SDL_VIDEO_DRIVER_OFFSCREEN

/* Offscreen video driver is similar to dummy driver, however its purpose
 * is enabling applications to use some of the SDL video functionality
 * (notably context creation) while not requiring a display output.
 *
 * An example would be running a graphical program on a headless box
 * for automated testing.
 */

#ضمن "SDL_offscreenvideo.h"
#ضمن "SDL_offscreenevents_c.h"
#ضمن "SDL_offscreenframebuffer_c.h"
#ضمن "SDL_offscreenopengles.h"
#ضمن "SDL_offscreenvulkan.h"
#ضمن "SDL_offscreenwindow.h"

#تعریف_کن OFFSCREENVID_DRIVER_NAME "offscreen"

// Initialization/Query functions
ساكن bool OFFSCREEN_VideoInit(SDL_VideoDevice *_this);
ساكن bool OFFSCREEN_مجموعه_Display_نما(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_نما *نما);
ساكن فراغ OFFSCREEN_VideoQuit(SDL_VideoDevice *_this);

// OFFSCREEN driver bootstrap functions

ساكن فراغ OFFSCREEN_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

ساكن bool OFFSCREEN_موجود(ثابت حرف *drivername)
{
    ثابت حرف *hint = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    إذا (hint && SDL_strstr(hint, drivername) != عدم) {
        أرجع true;
    }
    أرجع false;
}

ساكن SDL_VideoDevice *OFFSCREEN_CreateDevice(فراغ)
{
    SDL_VideoDevice *device;

    إذا (!OFFSCREEN_موجود(OFFSCREENVID_DRIVER_NAME)) {
        أرجع عدم;
    }

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (!device) {
        أرجع عدم;
    }

    // General video
    device->VideoInit = OFFSCREEN_VideoInit;
    device->VideoQuit = OFFSCREEN_VideoQuit;
    device->مجموعه_Display_نما = OFFSCREEN_مجموعه_Display_نما;
    device->PumpEvents = OFFSCREEN_PumpEvents;
    device->Create_پنجره_Framebuffer = SDL_OFFSCREEN_Create_پنجره_Framebuffer;
    device->Update_پنجره_Framebuffer = SDL_OFFSCREEN_Update_پنجره_Framebuffer;
    device->Destroy_پنجره_Framebuffer = SDL_OFFSCREEN_Destroy_پنجره_Framebuffer;
    device->حرر = OFFSCREEN_DeleteDevice;

#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
    // GL context
    device->GL_جابجا_پنجره = OFFSCREEN_GLES_جابجا_پنجره;
    device->GL_MakeCurrent = OFFSCREEN_GLES_MakeCurrent;
    device->GL_CreateContext = OFFSCREEN_GLES_CreateContext;
    device->GL_DestroyContext = OFFSCREEN_GLES_DestroyContext;
    device->GL_بارگیری_Library = OFFSCREEN_GLES_بارگیری_Library;
    device->GL_UnloadLibrary = OFFSCREEN_GLES_UnloadLibrary;
    device->GL_Get_Proc_آدرس = OFFSCREEN_GLES_Get_Proc_آدرس;
    device->GL_Get_جابجا_Interval = OFFSCREEN_GLES_Get_جابجا_Interval;
    device->GL_مجموعه_جابجا_Interval = OFFSCREEN_GLES_مجموعه_جابجا_Interval;
#پایان_اگر

#اگر_تعریف_شده SDL_VIDEO_VULKAN
    device->Vulkan_بارگیری_Library = OFFSCREEN_Vulkan_بارگیری_Library;
    device->Vulkan_UnloadLibrary = OFFSCREEN_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = OFFSCREEN_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = OFFSCREEN_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = OFFSCREEN_Vulkan_DestroySurface;
#پایان_اگر

    // "Window"
    device->CreateSDLWindow = OFFSCREEN_Create_پنجره;
    device->Destroy_پنجره = OFFSCREEN_Destroy_پنجره;
    device->مجموعه_پنجره_اندازه = OFFSCREEN_مجموعه_پنجره_اندازه;

    // TODO: Is this needed?
    device->device_caps = VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;

    أرجع device;
}

VideoBootStrap OFFSCREEN_bootstrap = {
    OFFSCREENVID_DRIVER_NAME, "SDL offscreen video driver",
    OFFSCREEN_CreateDevice,
    عدم, // no ShowMessageBox implementation
    false
};

ساكن bool OFFSCREEN_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Display_نما نما;

    // Use a fake 32-bpp desktop mode
    SDL_zero(نما);
    نما.format = SDL_PIXELFORMAT_XRGB8888;
    نما.w = 1024;
    نما.h = 768;
    إذا (SDL_جمع_کن_Basic_Video_Display(&نما) == 0) {
        أرجع false;
    }

    // We're done!
    أرجع true;
}

ساكن bool OFFSCREEN_مجموعه_Display_نما(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_نما *نما)
{
    أرجع true;
}

فراغ OFFSCREEN_VideoQuit(SDL_VideoDevice *_this)
{
}

#پایان_اگر // SDL_VIDEO_DRIVER_OFFSCREEN
