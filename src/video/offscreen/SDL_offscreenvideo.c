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

#నిర్వచితమైతే SDL_VIDEO_DRIVER_OFFSCREEN

/* Offscreen video driver is similar to dummy driver, however its purpose
 * is enabling applications to use some of the SDL video functionality
 * (notably context creation) while not requiring a display output.
 *
 * An example would be running a graphical program on a headless box
 * for automated testing.
 */

#అన్తర్భావ "SDL_offscreenvideo.h"
#అన్తర్భావ "SDL_offscreenevents_c.h"
#అన్తర్భావ "SDL_offscreenframebuffer_c.h"
#అన్తర్భావ "SDL_offscreenopengles.h"
#అన్తర్భావ "SDL_offscreenvulkan.h"
#అన్తర్భావ "SDL_offscreenwindow.h"

#నిర్వచించు OFFSCREENVID_DRIVER_NAME "offscreen"

// Initialization/Query functions
స్థిర bool OFFSCREEN_VideoInit(SDL_VideoDevice *_this);
స్థిర bool OFFSCREEN_సమితి_Display_బహుళకం(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_బహుళకం *బహుళకం);
స్థిర శూన్య OFFSCREEN_VideoQuit(SDL_VideoDevice *_this);

// OFFSCREEN driver bootstrap functions

స్థిర శూన్య OFFSCREEN_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

స్థిర bool OFFSCREEN_అందుబాటు(స్థిరరాశి అక్షరం *drivername)
{
    స్థిరరాశి అక్షరం *hint = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    ఒకవేళ (hint && SDL_strstr(hint, drivername) != ఖాళీ) {
        తిరిగి true;
    }
    తిరిగి false;
}

స్థిర SDL_VideoDevice *OFFSCREEN_CreateDevice(శూన్య)
{
    SDL_VideoDevice *device;

    ఒకవేళ (!OFFSCREEN_అందుబాటు(OFFSCREENVID_DRIVER_NAME)) {
        తిరిగి ఖాళీ;
    }

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, పరిమాణం(SDL_VideoDevice));
    ఒకవేళ (!device) {
        తిరిగి ఖాళీ;
    }

    // General video
    device->VideoInit = OFFSCREEN_VideoInit;
    device->VideoQuit = OFFSCREEN_VideoQuit;
    device->సమితి_Display_బహుళకం = OFFSCREEN_సమితి_Display_బహుళకం;
    device->PumpEvents = OFFSCREEN_PumpEvents;
    device->Create_కిటికీ_Framebuffer = SDL_OFFSCREEN_Create_కిటికీ_Framebuffer;
    device->Update_కిటికీ_Framebuffer = SDL_OFFSCREEN_Update_కిటికీ_Framebuffer;
    device->Destroy_కిటికీ_Framebuffer = SDL_OFFSCREEN_Destroy_కిటికీ_Framebuffer;
    device->విడుదల = OFFSCREEN_DeleteDevice;

#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
    // GL context
    device->GL_మార్పిడి_కిటికీ = OFFSCREEN_GLES_మార్పిడి_కిటికీ;
    device->GL_MakeCurrent = OFFSCREEN_GLES_MakeCurrent;
    device->GL_CreateContext = OFFSCREEN_GLES_CreateContext;
    device->GL_DestroyContext = OFFSCREEN_GLES_DestroyContext;
    device->GL_ఎక్కించు_Library = OFFSCREEN_GLES_ఎక్కించు_Library;
    device->GL_UnloadLibrary = OFFSCREEN_GLES_UnloadLibrary;
    device->GL_Get_Proc_చిరునామా = OFFSCREEN_GLES_Get_Proc_చిరునామా;
    device->GL_Get_మార్పిడి_Interval = OFFSCREEN_GLES_Get_మార్పిడి_Interval;
    device->GL_సమితి_మార్పిడి_Interval = OFFSCREEN_GLES_సమితి_మార్పిడి_Interval;
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_VIDEO_VULKAN
    device->Vulkan_ఎక్కించు_Library = OFFSCREEN_Vulkan_ఎక్కించు_Library;
    device->Vulkan_UnloadLibrary = OFFSCREEN_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = OFFSCREEN_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = OFFSCREEN_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = OFFSCREEN_Vulkan_DestroySurface;
#అయితే_ముగింపు

    // "Window"
    device->CreateSDLWindow = OFFSCREEN_Create_కిటికీ;
    device->Destroy_కిటికీ = OFFSCREEN_Destroy_కిటికీ;
    device->సమితి_కిటికీ_కొలత = OFFSCREEN_సమితి_కిటికీ_కొలత;

    // TODO: Is this needed?
    device->device_caps = VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;

    తిరిగి device;
}

VideoBootStrap OFFSCREEN_bootstrap = {
    OFFSCREENVID_DRIVER_NAME, "SDL offscreen video driver",
    OFFSCREEN_CreateDevice,
    ఖాళీ, // no ShowMessageBox implementation
    false
};

స్థిర bool OFFSCREEN_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Display_బహుళకం బహుళకం;

    // Use a fake 32-bpp desktop mode
    SDL_zero(బహుళకం);
    బహుళకం.format = SDL_PIXELFORMAT_XRGB8888;
    బహుళకం.w = 1024;
    బహుళకం.h = 768;
    ఒకవేళ (SDL_కూడు_Basic_Video_Display(&బహుళకం) == 0) {
        తిరిగి false;
    }

    // We're done!
    తిరిగి true;
}

స్థిర bool OFFSCREEN_సమితి_Display_బహుళకం(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_బహుళకం *బహుళకం)
{
    తిరిగి true;
}

శూన్య OFFSCREEN_VideoQuit(SDL_VideoDevice *_this)
{
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_OFFSCREEN
