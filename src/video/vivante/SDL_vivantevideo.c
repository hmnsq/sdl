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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_VIVANTE

// SDL internals
#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_ಒಳಹರಿವು_LINUXEV
#ಅನ್ತರ್ಭಾವ "../../core/linux/SDL_evdev.h"
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ "SDL_vivantevideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_vivanteplatform.h"
#ಅನ್ತರ್ಭಾವ "SDL_vivanteopengles.h"
#ಅನ್ತರ್ಭಾವ "SDL_vivantevulkan.h"

ಸ್ಥಿರ ಶೂನ್ಯ VIVANTE_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->ಆಂತರಿಕ);
    SDL_free(device);
}

ಸ್ಥಿರ SDL_VideoDevice *VIVANTE_Create(ಶೂನ್ಯ)
{
    SDL_VideoDevice *device;
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, ಗಾತ್ರ(SDL_VideoDevice));
    ಆದರೆ (!device) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    // Initialize internal data
    ದತ್ತಾಂಶ = (SDL_Video_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_Video_ದತ್ತಾಂಶ));
    ಆದರೆ (!ದತ್ತಾಂಶ) {
        SDL_free(device);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    device->ಆಂತರಿಕ = ದತ್ತಾಂಶ;

    // Setup amount of available displays
    device->ಅಂಕೆ_displays = 0;

    // Set device free function
    device->ಬಿಡುಗಡೆ = VIVANTE_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = VIVANTE_VideoInit;
    device->VideoQuit = VIVANTE_VideoQuit;
    device->CreateSDLWindow = VIVANTE_Create_ಕಿಟಕಿ;
    device->ಗಣ_ಕಿಟಕಿ_Title = VIVANTE_ಗಣ_ಕಿಟಕಿ_Title;
    device->ಗಣ_ಕಿಟಕಿ_Position = VIVANTE_ಗಣ_ಕಿಟಕಿ_Position;
    device->ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ = VIVANTE_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ;
    device->Show_ಕಿಟಕಿ = VIVANTE_Show_ಕಿಟಕಿ;
    device->Hide_ಕಿಟಕಿ = VIVANTE_Hide_ಕಿಟಕಿ;
    device->Destroy_ಕಿಟಕಿ = VIVANTE_Destroy_ಕಿಟಕಿ;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
    device->GL_ತುಂಬು_Library = VIVANTE_GLES_ತುಂಬು_Library;
    device->GL_Get_Proc_ವಿಳಾಸ = VIVANTE_GLES_Get_Proc_ವಿಳಾಸ;
    device->GL_UnloadLibrary = VIVANTE_GLES_UnloadLibrary;
    device->GL_CreateContext = VIVANTE_GLES_CreateContext;
    device->GL_MakeCurrent = VIVANTE_GLES_MakeCurrent;
    device->GL_ಗಣ_ಅದಲುಬದಲು_Interval = VIVANTE_GLES_ಗಣ_ಅದಲುಬದಲು_Interval;
    device->GL_Get_ಅದಲುಬದಲು_Interval = VIVANTE_GLES_Get_ಅದಲುಬದಲು_Interval;
    device->GL_ಅದಲುಬದಲು_ಕಿಟಕಿ = VIVANTE_GLES_ಅದಲುಬದಲು_ಕಿಟಕಿ;
    device->GL_DestroyContext = VIVANTE_GLES_DestroyContext;
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_VULKAN
    device->Vulkan_ತುಂಬು_Library = VIVANTE_Vulkan_ತುಂಬು_Library;
    device->Vulkan_UnloadLibrary = VIVANTE_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = VIVANTE_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = VIVANTE_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = VIVANTE_Vulkan_DestroySurface;
#ಆದರೆ_ಅಂತ್ಯ

    device->PumpEvents = VIVANTE_PumpEvents;

    ಹಿಂತಿರುಗಿ device;
}

VideoBootStrap VIVANTE_bootstrap = {
    "vivante",
    "Vivante EGL Video Driver",
    VIVANTE_Create,
    ಖಾಲಿ, // no ShowMessageBox implementation
    false
};

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/*****************************************************************************/

ಸ್ಥಿರ bool VIVANTE_ಕೂಡಿಸು_Video_Displays(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;
    SDL_VideoDisplay display;
    SDL_Display_ಬಹುಲಕ ಬಹುಲಕ;
    SDL_Display_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ;
    ಪೂರ್ಣಾಂಕ pitch = 0, bpp = 0;
    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ pixels = 0;

    ದತ್ತಾಂಶ = (SDL_Display_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_Display_ದತ್ತಾಂಶ));
    ಆದರೆ (!ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ false;
    }

    SDL_zero(ಬಹುಲಕ);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_VIVANTE_VDK
    ದತ್ತಾಂಶ->native_display = vdkGetDisplay(videodata->vdk_ಖಾಸಗಿ);

    vdkGetDisplayInfo(ದತ್ತಾಂಶ->native_display, &ಬಹುಲಕ.w, &ಬಹುಲಕ.h, &pixels, &pitch,
                      &bpp);
#ಇಲ್ಲದಿದ್ದರೆ
    ದತ್ತಾಂಶ->native_display = videodata->fb_Get_Display_By_ಸೂಚ್ಯಂಕ(0);

    videodata->fbGetDisplayInfo(ದತ್ತಾಂಶ->native_display, &ಬಹುಲಕ.w, &ಬಹುಲಕ.h,
                                &pixels, &pitch, &bpp);
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_VIVANTE_VDK

    ಆಯ್ಕೆ (bpp) {
    ಪೂರ್ವನಿಯೋಜಿತ: // Is another format used?
    ಸ್ಥಿತಿ 32:
        ಬಹುಲಕ.format = SDL_PIXELFORMAT_ARGB8888;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 16:
        ಬಹುಲಕ.format = SDL_PIXELFORMAT_RGB565;
        ನಿಲ್ಲಿಸು;
    }
    // FIXME: How do we query refresh rate?
    ಬಹುಲಕ.refresh_ದರ = 60.0f;

    SDL_zero(display);
    display.name = VIVANTE_GetDisplayName(_this);
    display.desktop_ಬಹುಲಕ = ಬಹುಲಕ;
    display.ಆಂತರಿಕ = ದತ್ತಾಂಶ;
    ಆದರೆ (SDL_ಕೂಡಿಸು_Video_Display(&display, false) == 0) {
        ಹಿಂತಿರುಗಿ false;
    }
    ಹಿಂತಿರುಗಿ true;
}

bool VIVANTE_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_VIVANTE_VDK
    videodata->vdk_ಖಾಸಗಿ = vdkInitialize();
    ಆದರೆ (!videodata->vdk_ಖಾಸಗಿ) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("vdkInitialize() failed");
    }
#ಇಲ್ಲದಿದ್ದರೆ
    videodata->egl_handle = SDL_ತುಂಬು_Object("libEGL.so.1");
    ಆದರೆ (!videodata->egl_handle) {
        videodata->egl_handle = SDL_ತುಂಬು_Object("libEGL.so");
        ಆದರೆ (!videodata->egl_handle) {
            ಹಿಂತಿರುಗಿ false;
        }
    }
#ವ್ಯಾಖ್ಯಾನಿಸು ತುಂಬು_FUNC(TYPE, NAME)                                               \
    videodata->NAME = (TYPE)SDL_ತುಂಬು_Function(videodata->egl_handle, #NAME); \
    ಆದರೆ (!videodata->NAME)                                                   \
        ಹಿಂತಿರುಗಿ false;

    ತುಂಬು_FUNC(EGLNativeDisplayType (EGLAPIENTRY *)(ಶೂನ್ಯ *), fbGetDisplay);
    ತುಂಬು_FUNC(EGLNativeDisplayType (EGLAPIENTRY *)(ಪೂರ್ಣಾಂಕ), fb_Get_Display_By_ಸೂಚ್ಯಂಕ);
    ತುಂಬು_FUNC(ಶೂನ್ಯ (EGLAPIENTRY *)(EGLNativeDisplayType, ಪೂರ್ಣಾಂಕ *, ಪೂರ್ಣಾಂಕ *), fbGetDisplayGeometry);
    ತುಂಬು_FUNC(ಶೂನ್ಯ (EGLAPIENTRY *)(EGLNativeDisplayType, ಪೂರ್ಣಾಂಕ *, ಪೂರ್ಣಾಂಕ *, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ *, ಪೂರ್ಣಾಂಕ *, ಪೂರ್ಣಾಂಕ *), fbGetDisplayInfo);
    ತುಂಬು_FUNC(ಶೂನ್ಯ (EGLAPIENTRY *)(EGLNativeDisplayType), fbDestroyDisplay);
    ತುಂಬು_FUNC(EGLNative_ಕಿಟಕಿ_Type (EGLAPIENTRY *)(EGLNativeDisplayType, ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ), fb_Create_ಕಿಟಕಿ);
    ತುಂಬು_FUNC(ಶೂನ್ಯ (EGLAPIENTRY *)(EGLNative_ಕಿಟಕಿ_Type, ಪೂರ್ಣಾಂಕ *, ಪೂರ್ಣಾಂಕ *, ಪೂರ್ಣಾಂಕ *, ಪೂರ್ಣಾಂಕ *), fb_Get_ಕಿಟಕಿ_Geometry);
    ತುಂಬು_FUNC(ಶೂನ್ಯ (EGLAPIENTRY *)(EGLNative_ಕಿಟಕಿ_Type, ಪೂರ್ಣಾಂಕ *, ಪೂರ್ಣಾಂಕ *, ಪೂರ್ಣಾಂಕ *, ಪೂರ್ಣಾಂಕ *, ಪೂರ್ಣಾಂಕ *, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ *), fb_Get_ಕಿಟಕಿ_Info);
    ತುಂಬು_FUNC(ಶೂನ್ಯ (EGLAPIENTRY *)(EGLNative_ಕಿಟಕಿ_Type), fb_Destroy_ಕಿಟಕಿ);
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (!VIVANTE_ಸಿದ್ಧತೆ_Platform(_this)) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (!VIVANTE_ಕೂಡಿಸು_Video_Displays(_this)) {
        ಹಿಂತಿರುಗಿ false;
    }

    VIVANTE_UpdateDisplayScale(_this);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_ಒಳಹರಿವು_LINUXEV
    ಆದರೆ (!SDL_EVDEV_Init()) {
        ಹಿಂತಿರುಗಿ false;
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ VIVANTE_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_ಒಳಹರಿವು_LINUXEV
    SDL_EVDEV_Quit();
#ಆದರೆ_ಅಂತ್ಯ

    VIVANTE_CleanupPlatform(_this);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_VIVANTE_VDK
    ಆದರೆ (videodata->vdk_ಖಾಸಗಿ) {
        vdkExit(videodata->vdk_ಖಾಸಗಿ);
        videodata->vdk_ಖಾಸಗಿ = ಖಾಲಿ;
    }
#ಇಲ್ಲದಿದ್ದರೆ
    ಆದರೆ (videodata->egl_handle) {
        SDL_UnloadObject(videodata->egl_handle);
        videodata->egl_handle = ಖಾಲಿ;
    }
#ಆದರೆ_ಅಂತ್ಯ
}

bool VIVANTE_Create_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID create_props)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;
    SDL_Display_ದತ್ತಾಂಶ *displaydata;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ;

    displaydata = SDL_Get_Display_Driver_ದತ್ತಾಂಶ(SDL_GetPrimaryDisplay());

    // Allocate window internal data
    ದತ್ತಾಂಶ = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ));
    ಆದರೆ (!ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ false;
    }

    // Setup driver data for this window
    ಕಿಟಕಿ->ಆಂತರಿಕ = ದತ್ತಾಂಶ;

    SDL_PropertiesID props = SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ);
    SDL_ಗಣ_ಸೂಚಕ_Property(props, SDL_PROP_ಕಿಟಕಿ_VIVANTE_DISPLAY_ಸೂಚಕ, displaydata->native_display);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_VIVANTE_VDK
    ದತ್ತಾಂಶ->native_ಕಿಟಕಿ = vdk_Create_ಕಿಟಕಿ(displaydata->native_display, ಕಿಟಕಿ->x, ಕಿಟಕಿ->y, ಕಿಟಕಿ->w, ಕಿಟಕಿ->h);
#ಇಲ್ಲದಿದ್ದರೆ
    ದತ್ತಾಂಶ->native_ಕಿಟಕಿ = videodata->fb_Create_ಕಿಟಕಿ(displaydata->native_display, ಕಿಟಕಿ->x, ಕಿಟಕಿ->y, ಕಿಟಕಿ->w, ಕಿಟಕಿ->h);
#ಆದರೆ_ಅಂತ್ಯ
    ಆದರೆ (!ದತ್ತಾಂಶ->native_ಕಿಟಕಿ) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("VIVANTE: Can't create native window");
    }
    SDL_ಗಣ_ಸೂಚಕ_Property(props, SDL_PROP_ಕಿಟಕಿ_VIVANTE_ಕಿಟಕಿ_ಸೂಚಕ, ದತ್ತಾಂಶ->native_ಕಿಟಕಿ);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_OPENGL) {
        ದತ್ತಾಂಶ->egl_surface = SDL_EGL_CreateSurface(_this, ಕಿಟಕಿ, ದತ್ತಾಂಶ->native_ಕಿಟಕಿ);
        ಆದರೆ (ದತ್ತಾಂಶ->egl_surface == EGL_NO_SURFACE) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("VIVANTE: Can't create EGL surface");
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ದತ್ತಾಂಶ->egl_surface = EGL_NO_SURFACE;
    }
    SDL_ಗಣ_ಸೂಚಕ_Property(props, SDL_PROP_ಕಿಟಕಿ_VIVANTE_SURFACE_ಸೂಚಕ, ದತ್ತಾಂಶ->egl_surface);
#ಆದರೆ_ಅಂತ್ಯ

    // Window has been successfully created
    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ VIVANTE_Destroy_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ;

    ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    ಆದರೆ (ದತ್ತಾಂಶ) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
        ಆದರೆ (ದತ್ತಾಂಶ->egl_surface != EGL_NO_SURFACE) {
            SDL_EGL_DestroySurface(_this, ದತ್ತಾಂಶ->egl_surface);
        }
#ಆದರೆ_ಅಂತ್ಯ

        ಆದರೆ (ದತ್ತಾಂಶ->native_ಕಿಟಕಿ) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_VIVANTE_VDK
            vdk_Destroy_ಕಿಟಕಿ(ದತ್ತಾಂಶ->native_ಕಿಟಕಿ);
#ಇಲ್ಲದಿದ್ದರೆ
            videodata->fb_Destroy_ಕಿಟಕಿ(ದತ್ತಾಂಶ->native_ಕಿಟಕಿ);
#ಆದರೆ_ಅಂತ್ಯ
        }

        SDL_free(ದತ್ತಾಂಶ);
    }
    ಕಿಟಕಿ->ಆಂತರಿಕ = ಖಾಲಿ;
}

ಶೂನ್ಯ VIVANTE_ಗಣ_ಕಿಟಕಿ_Title(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    vdk_ಗಣ_ಕಿಟಕಿ_Title(ದತ್ತಾಂಶ->native_ಕಿಟಕಿ, ಕಿಟಕಿ->title);
#ಆದರೆ_ಅಂತ್ಯ
}

bool VIVANTE_ಗಣ_ಕಿಟಕಿ_Position(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    // FIXME
    ಹಿಂತಿರುಗಿ SDL_Unsupported();
}

ಶೂನ್ಯ VIVANTE_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    // FIXME
}

ಶೂನ್ಯ VIVANTE_Show_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    vdk_Show_ಕಿಟಕಿ(ದತ್ತಾಂಶ->native_ಕಿಟಕಿ);
#ಆದರೆ_ಅಂತ್ಯ
    SDL_ಗಣ_Mouse_Focus(ಕಿಟಕಿ);
    SDL_ಗಣ_Keyboard_Focus(ಕಿಟಕಿ);
}

ಶೂನ್ಯ VIVANTE_Hide_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    vdk_Hide_ಕಿಟಕಿ(ದತ್ತಾಂಶ->native_ಕಿಟಕಿ);
#ಆದರೆ_ಅಂತ್ಯ
    SDL_ಗಣ_Mouse_Focus(ಖಾಲಿ);
    SDL_ಗಣ_Keyboard_Focus(ಖಾಲಿ);
}

/*****************************************************************************/
// SDL event functions
/*****************************************************************************/
ಶೂನ್ಯ VIVANTE_PumpEvents(SDL_VideoDevice *_this)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_ಒಳಹರಿವು_LINUXEV
    SDL_EVDEV_Poll();
#ಆದರೆ_ಅಂತ್ಯ
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_VIVANTE
