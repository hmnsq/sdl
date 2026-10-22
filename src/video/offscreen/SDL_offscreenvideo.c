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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_OFFSCREEN

/* Offscreen video driver is similar to dummy driver, however its purpose
 * is enabling applications to use some of the SDL video functionality
 * (notably context creation) while not requiring a display output.
 *
 * An example would be running a graphical program on a headless box
 * for automated testing.
 */

#अन्तर्भाव "SDL_offscreenvideo.h"
#अन्तर्भाव "SDL_offscreenevents_c.h"
#अन्तर्भाव "SDL_offscreenframebuffer_c.h"
#अन्तर्भाव "SDL_offscreenopengles.h"
#अन्तर्भाव "SDL_offscreenvulkan.h"
#अन्तर्भाव "SDL_offscreenwindow.h"

#परिभाषय OFFSCREENVID_DRIVER_NAME "offscreen"

// Initialization/Query functions
स्थिर bool OFFSCREEN_VideoInit(SDL_VideoDevice *_this);
स्थिर bool OFFSCREEN_समुच्चयः_Display_बहुलकम्(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_बहुलकम् *बहुलकम्);
स्थिर शून्य OFFSCREEN_VideoQuit(SDL_VideoDevice *_this);

// OFFSCREEN driver bootstrap functions

स्थिर शून्य OFFSCREEN_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

स्थिर bool OFFSCREEN_उपलब्धम्(ध्रुव वर्ण *drivername)
{
    ध्रुव वर्ण *hint = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    यदि (hint && SDL_strstr(hint, drivername) != रिक्त) {
        प्रत्यागम true;
    }
    प्रत्यागम false;
}

स्थिर SDL_VideoDevice *OFFSCREEN_CreateDevice(शून्य)
{
    SDL_VideoDevice *device;

    यदि (!OFFSCREEN_उपलब्धम्(OFFSCREENVID_DRIVER_NAME)) {
        प्रत्यागम रिक्त;
    }

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, परिमाण(SDL_VideoDevice));
    यदि (!device) {
        प्रत्यागम रिक्त;
    }

    // General video
    device->VideoInit = OFFSCREEN_VideoInit;
    device->VideoQuit = OFFSCREEN_VideoQuit;
    device->समुच्चयः_Display_बहुलकम् = OFFSCREEN_समुच्चयः_Display_बहुलकम्;
    device->PumpEvents = OFFSCREEN_PumpEvents;
    device->Create_गवाक्षः_Framebuffer = SDL_OFFSCREEN_Create_गवाक्षः_Framebuffer;
    device->Update_गवाक्षः_Framebuffer = SDL_OFFSCREEN_Update_गवाक्षः_Framebuffer;
    device->Destroy_गवाक्षः_Framebuffer = SDL_OFFSCREEN_Destroy_गवाक्षः_Framebuffer;
    device->मुक्त = OFFSCREEN_DeleteDevice;

#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
    // GL context
    device->GL_Swap_गवाक्षः = OFFSCREEN_GLES_Swap_गवाक्षः;
    device->GL_MakeCurrent = OFFSCREEN_GLES_MakeCurrent;
    device->GL_CreateContext = OFFSCREEN_GLES_CreateContext;
    device->GL_DestroyContext = OFFSCREEN_GLES_DestroyContext;
    device->GL_आरोपय_Library = OFFSCREEN_GLES_आरोपय_Library;
    device->GL_UnloadLibrary = OFFSCREEN_GLES_UnloadLibrary;
    device->GL_Get_Proc_स्थानाङ्कः = OFFSCREEN_GLES_Get_Proc_स्थानाङ्कः;
    device->GL_GetSwapInterval = OFFSCREEN_GLES_GetSwapInterval;
    device->GL_समुच्चयः_Swap_Interval = OFFSCREEN_GLES_समुच्चयः_Swap_Interval;
#यदि_अन्तः

#यदि_परिभाषितम् SDL_VIDEO_VULKAN
    device->Vulkan_आरोपय_Library = OFFSCREEN_Vulkan_आरोपय_Library;
    device->Vulkan_UnloadLibrary = OFFSCREEN_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = OFFSCREEN_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = OFFSCREEN_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = OFFSCREEN_Vulkan_DestroySurface;
#यदि_अन्तः

    // "Window"
    device->CreateSDLWindow = OFFSCREEN_Create_गवाक्षः;
    device->Destroy_गवाक्षः = OFFSCREEN_Destroy_गवाक्षः;
    device->समुच्चयः_गवाक्षः_आकार = OFFSCREEN_समुच्चयः_गवाक्षः_आकार;

    // TODO: Is this needed?
    device->device_caps = VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;

    प्रत्यागम device;
}

VideoBootStrap OFFSCREEN_bootstrap = {
    OFFSCREENVID_DRIVER_NAME, "SDL offscreen video driver",
    OFFSCREEN_CreateDevice,
    रिक्त, // no ShowMessageBox implementation
    false
};

स्थिर bool OFFSCREEN_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Display_बहुलकम् बहुलकम्;

    // Use a fake 32-bpp desktop mode
    SDL_zero(बहुलकम्);
    बहुलकम्.format = SDL_PIXELFORMAT_XRGB8888;
    बहुलकम्.w = 1024;
    बहुलकम्.h = 768;
    यदि (SDL_सङ्कलय_Basic_Video_Display(&बहुलकम्) == 0) {
        प्रत्यागम false;
    }

    // We're done!
    प्रत्यागम true;
}

स्थिर bool OFFSCREEN_समुच्चयः_Display_बहुलकम्(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_बहुलकम् *बहुलकम्)
{
    प्रत्यागम true;
}

शून्य OFFSCREEN_VideoQuit(SDL_VideoDevice *_this)
{
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_OFFSCREEN
