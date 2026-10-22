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

#నిర్వచితమైతే SDL_VIDEO_DRIVER_VIVANTE

// SDL internals
#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "../../events/SDL_events_c.h"

#నిర్వచితమైతే SDL_ఆదానం_LINUXEV
#అన్తర్భావ "../../core/linux/SDL_evdev.h"
#అయితే_ముగింపు

#అన్తర్భావ "SDL_vivantevideo.h"
#అన్తర్భావ "SDL_vivanteplatform.h"
#అన్తర్భావ "SDL_vivanteopengles.h"
#అన్తర్భావ "SDL_vivantevulkan.h"

స్థిర శూన్య VIVANTE_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->అంతర్గత);
    SDL_free(device);
}

స్థిర SDL_VideoDevice *VIVANTE_Create(శూన్య)
{
    SDL_VideoDevice *device;
    SDL_Video_దత్తాంశం *దత్తాంశం;

    // Initialize SDL_VideoDevice structure
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

    // Setup amount of available displays
    device->అంకె_displays = 0;

    // Set device free function
    device->విడుదల = VIVANTE_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = VIVANTE_VideoInit;
    device->VideoQuit = VIVANTE_VideoQuit;
    device->CreateSDLWindow = VIVANTE_Create_కిటికీ;
    device->సమితి_కిటికీ_Title = VIVANTE_సమితి_కిటికీ_Title;
    device->సమితి_కిటికీ_Position = VIVANTE_సమితి_కిటికీ_Position;
    device->సమితి_కిటికీ_కొలత = VIVANTE_సమితి_కిటికీ_కొలత;
    device->Show_కిటికీ = VIVANTE_Show_కిటికీ;
    device->Hide_కిటికీ = VIVANTE_Hide_కిటికీ;
    device->Destroy_కిటికీ = VIVANTE_Destroy_కిటికీ;

#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
    device->GL_ఎక్కించు_Library = VIVANTE_GLES_ఎక్కించు_Library;
    device->GL_Get_Proc_చిరునామా = VIVANTE_GLES_Get_Proc_చిరునామా;
    device->GL_UnloadLibrary = VIVANTE_GLES_UnloadLibrary;
    device->GL_CreateContext = VIVANTE_GLES_CreateContext;
    device->GL_MakeCurrent = VIVANTE_GLES_MakeCurrent;
    device->GL_సమితి_మార్పిడి_Interval = VIVANTE_GLES_సమితి_మార్పిడి_Interval;
    device->GL_Get_మార్పిడి_Interval = VIVANTE_GLES_Get_మార్పిడి_Interval;
    device->GL_మార్పిడి_కిటికీ = VIVANTE_GLES_మార్పిడి_కిటికీ;
    device->GL_DestroyContext = VIVANTE_GLES_DestroyContext;
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_VIDEO_VULKAN
    device->Vulkan_ఎక్కించు_Library = VIVANTE_Vulkan_ఎక్కించు_Library;
    device->Vulkan_UnloadLibrary = VIVANTE_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = VIVANTE_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = VIVANTE_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = VIVANTE_Vulkan_DestroySurface;
#అయితే_ముగింపు

    device->PumpEvents = VIVANTE_PumpEvents;

    తిరిగి device;
}

VideoBootStrap VIVANTE_bootstrap = {
    "vivante",
    "Vivante EGL Video Driver",
    VIVANTE_Create,
    ఖాళీ, // no ShowMessageBox implementation
    false
};

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/*****************************************************************************/

స్థిర bool VIVANTE_కూడు_Video_Displays(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;
    SDL_VideoDisplay display;
    SDL_Display_బహుళకం బహుళకం;
    SDL_Display_దత్తాంశం *దత్తాంశం;
    పూర్ణాంకం pitch = 0, bpp = 0;
    గుర్తులేని దీర్ఘ pixels = 0;

    దత్తాంశం = (SDL_Display_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_Display_దత్తాంశం));
    ఒకవేళ (!దత్తాంశం) {
        తిరిగి false;
    }

    SDL_zero(బహుళకం);
#నిర్వచితమైతే SDL_VIDEO_DRIVER_VIVANTE_VDK
    దత్తాంశం->native_display = vdkGetDisplay(videodata->vdk_వ్యక్తిగత);

    vdkGetDisplayInfo(దత్తాంశం->native_display, &బహుళకం.w, &బహుళకం.h, &pixels, &pitch,
                      &bpp);
#లేకపోతే
    దత్తాంశం->native_display = videodata->fb_Get_Display_By_సూచీ(0);

    videodata->fbGetDisplayInfo(దత్తాంశం->native_display, &బహుళకం.w, &బహుళకం.h,
                                &pixels, &pitch, &bpp);
#అయితే_ముగింపు // SDL_VIDEO_DRIVER_VIVANTE_VDK

    ఎంపిక (bpp) {
    అప్రమేయ: // Is another format used?
    స్థితి 32:
        బహుళకం.format = SDL_PIXELFORMAT_ARGB8888;
        ఆపు;
    స్థితి 16:
        బహుళకం.format = SDL_PIXELFORMAT_RGB565;
        ఆపు;
    }
    // FIXME: How do we query refresh rate?
    బహుళకం.refresh_రేటు = 60.0f;

    SDL_zero(display);
    display.name = VIVANTE_GetDisplayName(_this);
    display.desktop_బహుళకం = బహుళకం;
    display.అంతర్గత = దత్తాంశం;
    ఒకవేళ (SDL_కూడు_Video_Display(&display, false) == 0) {
        తిరిగి false;
    }
    తిరిగి true;
}

bool VIVANTE_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;

#నిర్వచితమైతే SDL_VIDEO_DRIVER_VIVANTE_VDK
    videodata->vdk_వ్యక్తిగత = vdkInitialize();
    ఒకవేళ (!videodata->vdk_వ్యక్తిగత) {
        తిరిగి SDL_సమితి_Error("vdkInitialize() failed");
    }
#లేకపోతే
    videodata->egl_handle = SDL_ఎక్కించు_Object("libEGL.so.1");
    ఒకవేళ (!videodata->egl_handle) {
        videodata->egl_handle = SDL_ఎక్కించు_Object("libEGL.so");
        ఒకవేళ (!videodata->egl_handle) {
            తిరిగి false;
        }
    }
#నిర్వచించు ఎక్కించు_FUNC(TYPE, NAME)                                               \
    videodata->NAME = (TYPE)SDL_ఎక్కించు_Function(videodata->egl_handle, #NAME); \
    ఒకవేళ (!videodata->NAME)                                                   \
        తిరిగి false;

    ఎక్కించు_FUNC(EGLNativeDisplayType (EGLAPIENTRY *)(శూన్య *), fbGetDisplay);
    ఎక్కించు_FUNC(EGLNativeDisplayType (EGLAPIENTRY *)(పూర్ణాంకం), fb_Get_Display_By_సూచీ);
    ఎక్కించు_FUNC(శూన్య (EGLAPIENTRY *)(EGLNativeDisplayType, పూర్ణాంకం *, పూర్ణాంకం *), fbGetDisplayGeometry);
    ఎక్కించు_FUNC(శూన్య (EGLAPIENTRY *)(EGLNativeDisplayType, పూర్ణాంకం *, పూర్ణాంకం *, గుర్తులేని దీర్ఘ *, పూర్ణాంకం *, పూర్ణాంకం *), fbGetDisplayInfo);
    ఎక్కించు_FUNC(శూన్య (EGLAPIENTRY *)(EGLNativeDisplayType), fbDestroyDisplay);
    ఎక్కించు_FUNC(EGLNative_కిటికీ_Type (EGLAPIENTRY *)(EGLNativeDisplayType, పూర్ణాంకం, పూర్ణాంకం, పూర్ణాంకం, పూర్ణాంకం), fb_Create_కిటికీ);
    ఎక్కించు_FUNC(శూన్య (EGLAPIENTRY *)(EGLNative_కిటికీ_Type, పూర్ణాంకం *, పూర్ణాంకం *, పూర్ణాంకం *, పూర్ణాంకం *), fb_Get_కిటికీ_Geometry);
    ఎక్కించు_FUNC(శూన్య (EGLAPIENTRY *)(EGLNative_కిటికీ_Type, పూర్ణాంకం *, పూర్ణాంకం *, పూర్ణాంకం *, పూర్ణాంకం *, పూర్ణాంకం *, గుర్తులేని పూర్ణాంకం *), fb_Get_కిటికీ_Info);
    ఎక్కించు_FUNC(శూన్య (EGLAPIENTRY *)(EGLNative_కిటికీ_Type), fb_Destroy_కిటికీ);
#అయితే_ముగింపు

    ఒకవేళ (!VIVANTE_అమరిక_Platform(_this)) {
        తిరిగి false;
    }

    ఒకవేళ (!VIVANTE_కూడు_Video_Displays(_this)) {
        తిరిగి false;
    }

    VIVANTE_UpdateDisplayScale(_this);

#నిర్వచితమైతే SDL_ఆదానం_LINUXEV
    ఒకవేళ (!SDL_EVDEV_Init()) {
        తిరిగి false;
    }
#అయితే_ముగింపు

    తిరిగి true;
}

శూన్య VIVANTE_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;

#నిర్వచితమైతే SDL_ఆదానం_LINUXEV
    SDL_EVDEV_Quit();
#అయితే_ముగింపు

    VIVANTE_CleanupPlatform(_this);

#నిర్వచితమైతే SDL_VIDEO_DRIVER_VIVANTE_VDK
    ఒకవేళ (videodata->vdk_వ్యక్తిగత) {
        vdkExit(videodata->vdk_వ్యక్తిగత);
        videodata->vdk_వ్యక్తిగత = ఖాళీ;
    }
#లేకపోతే
    ఒకవేళ (videodata->egl_handle) {
        SDL_UnloadObject(videodata->egl_handle);
        videodata->egl_handle = ఖాళీ;
    }
#అయితే_ముగింపు
}

bool VIVANTE_Create_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID create_props)
{
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;
    SDL_Display_దత్తాంశం *displaydata;
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం;

    displaydata = SDL_Get_Display_Driver_దత్తాంశం(SDL_GetPrimaryDisplay());

    // Allocate window internal data
    దత్తాంశం = (SDL_కిటికీ_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_కిటికీ_దత్తాంశం));
    ఒకవేళ (!దత్తాంశం) {
        తిరిగి false;
    }

    // Setup driver data for this window
    కిటికీ->అంతర్గత = దత్తాంశం;

    SDL_PropertiesID props = SDL_Get_కిటికీ_Properties(కిటికీ);
    SDL_సమితి_సూచిక_Property(props, SDL_PROP_కిటికీ_VIVANTE_DISPLAY_సూచిక, displaydata->native_display);

#నిర్వచితమైతే SDL_VIDEO_DRIVER_VIVANTE_VDK
    దత్తాంశం->native_కిటికీ = vdk_Create_కిటికీ(displaydata->native_display, కిటికీ->x, కిటికీ->y, కిటికీ->w, కిటికీ->h);
#లేకపోతే
    దత్తాంశం->native_కిటికీ = videodata->fb_Create_కిటికీ(displaydata->native_display, కిటికీ->x, కిటికీ->y, కిటికీ->w, కిటికీ->h);
#అయితే_ముగింపు
    ఒకవేళ (!దత్తాంశం->native_కిటికీ) {
        తిరిగి SDL_సమితి_Error("VIVANTE: Can't create native window");
    }
    SDL_సమితి_సూచిక_Property(props, SDL_PROP_కిటికీ_VIVANTE_కిటికీ_సూచిక, దత్తాంశం->native_కిటికీ);

#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_OPENGL) {
        దత్తాంశం->egl_surface = SDL_EGL_CreateSurface(_this, కిటికీ, దత్తాంశం->native_కిటికీ);
        ఒకవేళ (దత్తాంశం->egl_surface == EGL_NO_SURFACE) {
            తిరిగి SDL_సమితి_Error("VIVANTE: Can't create EGL surface");
        }
    } లేకపోతే {
        దత్తాంశం->egl_surface = EGL_NO_SURFACE;
    }
    SDL_సమితి_సూచిక_Property(props, SDL_PROP_కిటికీ_VIVANTE_SURFACE_సూచిక, దత్తాంశం->egl_surface);
#అయితే_ముగింపు

    // Window has been successfully created
    తిరిగి true;
}

శూన్య VIVANTE_Destroy_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం;

    దత్తాంశం = కిటికీ->అంతర్గత;
    ఒకవేళ (దత్తాంశం) {
#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
        ఒకవేళ (దత్తాంశం->egl_surface != EGL_NO_SURFACE) {
            SDL_EGL_DestroySurface(_this, దత్తాంశం->egl_surface);
        }
#అయితే_ముగింపు

        ఒకవేళ (దత్తాంశం->native_కిటికీ) {
#నిర్వచితమైతే SDL_VIDEO_DRIVER_VIVANTE_VDK
            vdk_Destroy_కిటికీ(దత్తాంశం->native_కిటికీ);
#లేకపోతే
            videodata->fb_Destroy_కిటికీ(దత్తాంశం->native_కిటికీ);
#అయితే_ముగింపు
        }

        SDL_free(దత్తాంశం);
    }
    కిటికీ->అంతర్గత = ఖాళీ;
}

శూన్య VIVANTE_సమితి_కిటికీ_Title(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
#నిర్వచితమైతే SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    vdk_సమితి_కిటికీ_Title(దత్తాంశం->native_కిటికీ, కిటికీ->title);
#అయితే_ముగింపు
}

bool VIVANTE_సమితి_కిటికీ_Position(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    // FIXME
    తిరిగి SDL_Unsupported();
}

శూన్య VIVANTE_సమితి_కిటికీ_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    // FIXME
}

శూన్య VIVANTE_Show_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
#నిర్వచితమైతే SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    vdk_Show_కిటికీ(దత్తాంశం->native_కిటికీ);
#అయితే_ముగింపు
    SDL_సమితి_Mouse_Focus(కిటికీ);
    SDL_సమితి_Keyboard_Focus(కిటికీ);
}

శూన్య VIVANTE_Hide_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
#నిర్వచితమైతే SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    vdk_Hide_కిటికీ(దత్తాంశం->native_కిటికీ);
#అయితే_ముగింపు
    SDL_సమితి_Mouse_Focus(ఖాళీ);
    SDL_సమితి_Keyboard_Focus(ఖాళీ);
}

/*****************************************************************************/
// SDL event functions
/*****************************************************************************/
శూన్య VIVANTE_PumpEvents(SDL_VideoDevice *_this)
{
#నిర్వచితమైతే SDL_ఆదానం_LINUXEV
    SDL_EVDEV_Poll();
#అయితే_ముగింపు
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_VIVANTE
