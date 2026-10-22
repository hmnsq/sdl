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

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_OFFSCREEN

/* Offscreen video driver is similar to dummy driver, however its purpose
 * is enabling applications to use some of the SDL video functionality
 * (notably context creation) while not requiring a display output.
 *
 * An example would be running a graphical program on a headless box
 * for automated testing.
 */

#شامل "SDL_offscreenvideo.h"
#شامل "SDL_offscreenevents_c.h"
#شامل "SDL_offscreenframebuffer_c.h"
#شامل "SDL_offscreenopengles.h"
#شامل "SDL_offscreenvulkan.h"
#شامل "SDL_offscreenwindow.h"

#تعریف_کرو OFFSCREENVID_DRIVER_NAME "offscreen"

// Initialization/Query functions
ساکن bool OFFSCREEN_VideoInit(SDL_VideoDevice *_this);
ساکن bool OFFSCREEN_سیٹ_Display_منوال(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_منوال *منوال);
ساکن خالی OFFSCREEN_VideoQuit(SDL_VideoDevice *_this);

// OFFSCREEN driver bootstrap functions

ساکن خالی OFFSCREEN_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

ساکن bool OFFSCREEN_دستیاب(ثابت حرف *drivername)
{
    ثابت حرف *hint = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    اگر (hint && SDL_strstr(hint, drivername) != تہی) {
        واپس true;
    }
    واپس false;
}

ساکن SDL_VideoDevice *OFFSCREEN_CreateDevice(خالی)
{
    SDL_VideoDevice *device;

    اگر (!OFFSCREEN_دستیاب(OFFSCREENVID_DRIVER_NAME)) {
        واپس تہی;
    }

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    اگر (!device) {
        واپس تہی;
    }

    // General video
    device->VideoInit = OFFSCREEN_VideoInit;
    device->VideoQuit = OFFSCREEN_VideoQuit;
    device->سیٹ_Display_منوال = OFFSCREEN_سیٹ_Display_منوال;
    device->PumpEvents = OFFSCREEN_PumpEvents;
    device->Create_کھڑکی_Framebuffer = SDL_OFFSCREEN_Create_کھڑکی_Framebuffer;
    device->Update_کھڑکی_Framebuffer = SDL_OFFSCREEN_Update_کھڑکی_Framebuffer;
    device->Destroy_کھڑکی_Framebuffer = SDL_OFFSCREEN_Destroy_کھڑکی_Framebuffer;
    device->آزاد = OFFSCREEN_DeleteDevice;

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    // GL context
    device->GL_تبادلہ_کھڑکی = OFFSCREEN_GLES_تبادلہ_کھڑکی;
    device->GL_MakeCurrent = OFFSCREEN_GLES_MakeCurrent;
    device->GL_CreateContext = OFFSCREEN_GLES_CreateContext;
    device->GL_DestroyContext = OFFSCREEN_GLES_DestroyContext;
    device->GL_بھرو_Library = OFFSCREEN_GLES_بھرو_Library;
    device->GL_UnloadLibrary = OFFSCREEN_GLES_UnloadLibrary;
    device->GL_Get_Proc_پتہ = OFFSCREEN_GLES_Get_Proc_پتہ;
    device->GL_Get_تبادلہ_Interval = OFFSCREEN_GLES_Get_تبادلہ_Interval;
    device->GL_سیٹ_تبادلہ_Interval = OFFSCREEN_GLES_سیٹ_تبادلہ_Interval;
#اگر_ختم

#اگر_تعریف_شدہ SDL_VIDEO_VULKAN
    device->Vulkan_بھرو_Library = OFFSCREEN_Vulkan_بھرو_Library;
    device->Vulkan_UnloadLibrary = OFFSCREEN_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = OFFSCREEN_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = OFFSCREEN_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = OFFSCREEN_Vulkan_DestroySurface;
#اگر_ختم

    // "Window"
    device->CreateSDLWindow = OFFSCREEN_Create_کھڑکی;
    device->Destroy_کھڑکی = OFFSCREEN_Destroy_کھڑکی;
    device->سیٹ_کھڑکی_سائز = OFFSCREEN_سیٹ_کھڑکی_سائز;

    // TODO: Is this needed?
    device->device_caps = VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;

    واپس device;
}

VideoBootStrap OFFSCREEN_bootstrap = {
    OFFSCREENVID_DRIVER_NAME, "SDL offscreen video driver",
    OFFSCREEN_CreateDevice,
    تہی, // no ShowMessageBox implementation
    false
};

ساکن bool OFFSCREEN_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Display_منوال منوال;

    // Use a fake 32-bpp desktop mode
    SDL_zero(منوال);
    منوال.format = SDL_PIXELFORMAT_XRGB8888;
    منوال.w = 1024;
    منوال.h = 768;
    اگر (SDL_جوڑو_Basic_Video_Display(&منوال) == 0) {
        واپس false;
    }

    // We're done!
    واپس true;
}

ساکن bool OFFSCREEN_سیٹ_Display_منوال(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_منوال *منوال)
{
    واپس true;
}

خالی OFFSCREEN_VideoQuit(SDL_VideoDevice *_this)
{
}

#اگر_ختم // SDL_VIDEO_DRIVER_OFFSCREEN
