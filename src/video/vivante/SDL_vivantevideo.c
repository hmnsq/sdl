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

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_VIVANTE

// SDL internals
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_events_c.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_ਨਿਵੇਸ਼_LINUXEV
#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/linux/SDL_evdev.h"
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_vivantevideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_vivanteplatform.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_vivanteopengles.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_vivantevulkan.h"

ਸਥਿਰ ਖਾਲੀ VIVANTE_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->ਅੰਦਰੂਨੀ);
    SDL_free(device);
}

ਸਥਿਰ SDL_VideoDevice *VIVANTE_Create(ਖਾਲੀ)
{
    SDL_VideoDevice *device;
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, ਆਕਾਰ(SDL_VideoDevice));
    ਜੇ (!device) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    // Initialize internal data
    ਅੰਕੜੇ = (SDL_Video_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(SDL_Video_ਅੰਕੜੇ));
    ਜੇ (!ਅੰਕੜੇ) {
        SDL_free(device);
        ਵਾਪਸ ਨਿਰਾ;
    }

    device->ਅੰਦਰੂਨੀ = ਅੰਕੜੇ;

    // Setup amount of available displays
    device->ਅੰਕ_displays = 0;

    // Set device free function
    device->ਮੁਕਤ = VIVANTE_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = VIVANTE_VideoInit;
    device->VideoQuit = VIVANTE_VideoQuit;
    device->CreateSDLWindow = VIVANTE_Create_ਖਿੜਕੀ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Title = VIVANTE_ਸੈੱਟ_ਖਿੜਕੀ_Title;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Position = VIVANTE_ਸੈੱਟ_ਖਿੜਕੀ_Position;
    device->ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ = VIVANTE_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ;
    device->Show_ਖਿੜਕੀ = VIVANTE_Show_ਖਿੜਕੀ;
    device->Hide_ਖਿੜਕੀ = VIVANTE_Hide_ਖਿੜਕੀ;
    device->Destroy_ਖਿੜਕੀ = VIVANTE_Destroy_ਖਿੜਕੀ;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
    device->GL_ਲੱਦੋ_Library = VIVANTE_GLES_ਲੱਦੋ_Library;
    device->GL_Get_Proc_ਪਤਾ = VIVANTE_GLES_Get_Proc_ਪਤਾ;
    device->GL_UnloadLibrary = VIVANTE_GLES_UnloadLibrary;
    device->GL_CreateContext = VIVANTE_GLES_CreateContext;
    device->GL_MakeCurrent = VIVANTE_GLES_MakeCurrent;
    device->GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval = VIVANTE_GLES_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval;
    device->GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval = VIVANTE_GLES_Get_ਅਦਲਾ_ਬਦਲੀ_Interval;
    device->GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ = VIVANTE_GLES_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ;
    device->GL_DestroyContext = VIVANTE_GLES_DestroyContext;
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_VULKAN
    device->Vulkan_ਲੱਦੋ_Library = VIVANTE_Vulkan_ਲੱਦੋ_Library;
    device->Vulkan_UnloadLibrary = VIVANTE_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = VIVANTE_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = VIVANTE_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = VIVANTE_Vulkan_DestroySurface;
#ਜੇ_ਅੰਤ

    device->PumpEvents = VIVANTE_PumpEvents;

    ਵਾਪਸ device;
}

VideoBootStrap VIVANTE_bootstrap = {
    "vivante",
    "Vivante EGL Video Driver",
    VIVANTE_Create,
    ਨਿਰਾ, // no ShowMessageBox implementation
    false
};

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/*****************************************************************************/

ਸਥਿਰ bool VIVANTE_ਜੋੜੋ_Video_Displays(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;
    SDL_VideoDisplay display;
    SDL_Display_ਬਹੁਲਕ ਬਹੁਲਕ;
    SDL_Display_ਅੰਕੜੇ *ਅੰਕੜੇ;
    ਪੂਰਨ pitch = 0, bpp = 0;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ pixels = 0;

    ਅੰਕੜੇ = (SDL_Display_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(SDL_Display_ਅੰਕੜੇ));
    ਜੇ (!ਅੰਕੜੇ) {
        ਵਾਪਸ false;
    }

    SDL_zero(ਬਹੁਲਕ);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_VIVANTE_VDK
    ਅੰਕੜੇ->native_display = vdkGetDisplay(videodata->vdk_ਨਿੱਜੀ);

    vdkGetDisplayInfo(ਅੰਕੜੇ->native_display, &ਬਹੁਲਕ.w, &ਬਹੁਲਕ.h, &pixels, &pitch,
                      &bpp);
#ਨਹੀਂਤਾਂ
    ਅੰਕੜੇ->native_display = videodata->fb_Get_Display_By_ਸੂਚਕਾਂਕ(0);

    videodata->fbGetDisplayInfo(ਅੰਕੜੇ->native_display, &ਬਹੁਲਕ.w, &ਬਹੁਲਕ.h,
                                &pixels, &pitch, &bpp);
#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_VIVANTE_VDK

    ਚੋਣ (bpp) {
    ਮੂਲ: // Is another format used?
    ਹਾਲਤ 32:
        ਬਹੁਲਕ.format = SDL_PIXELFORMAT_ARGB8888;
        ਰੋਕੋ;
    ਹਾਲਤ 16:
        ਬਹੁਲਕ.format = SDL_PIXELFORMAT_RGB565;
        ਰੋਕੋ;
    }
    // FIXME: How do we query refresh rate?
    ਬਹੁਲਕ.refresh_ਦਰ = 60.0f;

    SDL_zero(display);
    display.name = VIVANTE_GetDisplayName(_this);
    display.desktop_ਬਹੁਲਕ = ਬਹੁਲਕ;
    display.ਅੰਦਰੂਨੀ = ਅੰਕੜੇ;
    ਜੇ (SDL_ਜੋੜੋ_Video_Display(&display, false) == 0) {
        ਵਾਪਸ false;
    }
    ਵਾਪਸ true;
}

bool VIVANTE_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_VIVANTE_VDK
    videodata->vdk_ਨਿੱਜੀ = vdkInitialize();
    ਜੇ (!videodata->vdk_ਨਿੱਜੀ) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("vdkInitialize() failed");
    }
#ਨਹੀਂਤਾਂ
    videodata->egl_handle = SDL_ਲੱਦੋ_Object("libEGL.so.1");
    ਜੇ (!videodata->egl_handle) {
        videodata->egl_handle = SDL_ਲੱਦੋ_Object("libEGL.so");
        ਜੇ (!videodata->egl_handle) {
            ਵਾਪਸ false;
        }
    }
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਲੱਦੋ_FUNC(TYPE, NAME)                                               \
    videodata->NAME = (TYPE)SDL_ਲੱਦੋ_Function(videodata->egl_handle, #NAME); \
    ਜੇ (!videodata->NAME)                                                   \
        ਵਾਪਸ false;

    ਲੱਦੋ_FUNC(EGLNativeDisplayType (EGLAPIENTRY *)(ਖਾਲੀ *), fbGetDisplay);
    ਲੱਦੋ_FUNC(EGLNativeDisplayType (EGLAPIENTRY *)(ਪੂਰਨ), fb_Get_Display_By_ਸੂਚਕਾਂਕ);
    ਲੱਦੋ_FUNC(ਖਾਲੀ (EGLAPIENTRY *)(EGLNativeDisplayType, ਪੂਰਨ *, ਪੂਰਨ *), fbGetDisplayGeometry);
    ਲੱਦੋ_FUNC(ਖਾਲੀ (EGLAPIENTRY *)(EGLNativeDisplayType, ਪੂਰਨ *, ਪੂਰਨ *, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ *, ਪੂਰਨ *, ਪੂਰਨ *), fbGetDisplayInfo);
    ਲੱਦੋ_FUNC(ਖਾਲੀ (EGLAPIENTRY *)(EGLNativeDisplayType), fbDestroyDisplay);
    ਲੱਦੋ_FUNC(EGLNative_ਖਿੜਕੀ_Type (EGLAPIENTRY *)(EGLNativeDisplayType, ਪੂਰਨ, ਪੂਰਨ, ਪੂਰਨ, ਪੂਰਨ), fb_Create_ਖਿੜਕੀ);
    ਲੱਦੋ_FUNC(ਖਾਲੀ (EGLAPIENTRY *)(EGLNative_ਖਿੜਕੀ_Type, ਪੂਰਨ *, ਪੂਰਨ *, ਪੂਰਨ *, ਪੂਰਨ *), fb_Get_ਖਿੜਕੀ_Geometry);
    ਲੱਦੋ_FUNC(ਖਾਲੀ (EGLAPIENTRY *)(EGLNative_ਖਿੜਕੀ_Type, ਪੂਰਨ *, ਪੂਰਨ *, ਪੂਰਨ *, ਪੂਰਨ *, ਪੂਰਨ *, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ *), fb_Get_ਖਿੜਕੀ_Info);
    ਲੱਦੋ_FUNC(ਖਾਲੀ (EGLAPIENTRY *)(EGLNative_ਖਿੜਕੀ_Type), fb_Destroy_ਖਿੜਕੀ);
#ਜੇ_ਅੰਤ

    ਜੇ (!VIVANTE_ਤਿਆਰੀ_Platform(_this)) {
        ਵਾਪਸ false;
    }

    ਜੇ (!VIVANTE_ਜੋੜੋ_Video_Displays(_this)) {
        ਵਾਪਸ false;
    }

    VIVANTE_UpdateDisplayScale(_this);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_ਨਿਵੇਸ਼_LINUXEV
    ਜੇ (!SDL_EVDEV_Init()) {
        ਵਾਪਸ false;
    }
#ਜੇ_ਅੰਤ

    ਵਾਪਸ true;
}

ਖਾਲੀ VIVANTE_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_ਨਿਵੇਸ਼_LINUXEV
    SDL_EVDEV_Quit();
#ਜੇ_ਅੰਤ

    VIVANTE_CleanupPlatform(_this);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_VIVANTE_VDK
    ਜੇ (videodata->vdk_ਨਿੱਜੀ) {
        vdkExit(videodata->vdk_ਨਿੱਜੀ);
        videodata->vdk_ਨਿੱਜੀ = ਨਿਰਾ;
    }
#ਨਹੀਂਤਾਂ
    ਜੇ (videodata->egl_handle) {
        SDL_UnloadObject(videodata->egl_handle);
        videodata->egl_handle = ਨਿਰਾ;
    }
#ਜੇ_ਅੰਤ
}

bool VIVANTE_Create_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID create_props)
{
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;
    SDL_Display_ਅੰਕੜੇ *displaydata;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ;

    displaydata = SDL_Get_Display_Driver_ਅੰਕੜੇ(SDL_GetPrimaryDisplay());

    // Allocate window internal data
    ਅੰਕੜੇ = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ));
    ਜੇ (!ਅੰਕੜੇ) {
        ਵਾਪਸ false;
    }

    // Setup driver data for this window
    ਖਿੜਕੀ->ਅੰਦਰੂਨੀ = ਅੰਕੜੇ;

    SDL_PropertiesID props = SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ);
    SDL_ਸੈੱਟ_ਸੂਚਕ_Property(props, SDL_PROP_ਖਿੜਕੀ_VIVANTE_DISPLAY_ਸੂਚਕ, displaydata->native_display);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_VIVANTE_VDK
    ਅੰਕੜੇ->native_ਖਿੜਕੀ = vdk_Create_ਖਿੜਕੀ(displaydata->native_display, ਖਿੜਕੀ->x, ਖਿੜਕੀ->y, ਖਿੜਕੀ->w, ਖਿੜਕੀ->h);
#ਨਹੀਂਤਾਂ
    ਅੰਕੜੇ->native_ਖਿੜਕੀ = videodata->fb_Create_ਖਿੜਕੀ(displaydata->native_display, ਖਿੜਕੀ->x, ਖਿੜਕੀ->y, ਖਿੜਕੀ->w, ਖਿੜਕੀ->h);
#ਜੇ_ਅੰਤ
    ਜੇ (!ਅੰਕੜੇ->native_ਖਿੜਕੀ) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("VIVANTE: Can't create native window");
    }
    SDL_ਸੈੱਟ_ਸੂਚਕ_Property(props, SDL_PROP_ਖਿੜਕੀ_VIVANTE_ਖਿੜਕੀ_ਸੂਚਕ, ਅੰਕੜੇ->native_ਖਿੜਕੀ);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_OPENGL) {
        ਅੰਕੜੇ->egl_surface = SDL_EGL_CreateSurface(_this, ਖਿੜਕੀ, ਅੰਕੜੇ->native_ਖਿੜਕੀ);
        ਜੇ (ਅੰਕੜੇ->egl_surface == EGL_NO_SURFACE) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("VIVANTE: Can't create EGL surface");
        }
    } ਨਹੀਂਤਾਂ {
        ਅੰਕੜੇ->egl_surface = EGL_NO_SURFACE;
    }
    SDL_ਸੈੱਟ_ਸੂਚਕ_Property(props, SDL_PROP_ਖਿੜਕੀ_VIVANTE_SURFACE_ਸੂਚਕ, ਅੰਕੜੇ->egl_surface);
#ਜੇ_ਅੰਤ

    // Window has been successfully created
    ਵਾਪਸ true;
}

ਖਾਲੀ VIVANTE_Destroy_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ;

    ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    ਜੇ (ਅੰਕੜੇ) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
        ਜੇ (ਅੰਕੜੇ->egl_surface != EGL_NO_SURFACE) {
            SDL_EGL_DestroySurface(_this, ਅੰਕੜੇ->egl_surface);
        }
#ਜੇ_ਅੰਤ

        ਜੇ (ਅੰਕੜੇ->native_ਖਿੜਕੀ) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_VIVANTE_VDK
            vdk_Destroy_ਖਿੜਕੀ(ਅੰਕੜੇ->native_ਖਿੜਕੀ);
#ਨਹੀਂਤਾਂ
            videodata->fb_Destroy_ਖਿੜਕੀ(ਅੰਕੜੇ->native_ਖਿੜਕੀ);
#ਜੇ_ਅੰਤ
        }

        SDL_free(ਅੰਕੜੇ);
    }
    ਖਿੜਕੀ->ਅੰਦਰੂਨੀ = ਨਿਰਾ;
}

ਖਾਲੀ VIVANTE_ਸੈੱਟ_ਖਿੜਕੀ_Title(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    vdk_ਸੈੱਟ_ਖਿੜਕੀ_Title(ਅੰਕੜੇ->native_ਖਿੜਕੀ, ਖਿੜਕੀ->title);
#ਜੇ_ਅੰਤ
}

bool VIVANTE_ਸੈੱਟ_ਖਿੜਕੀ_Position(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    // FIXME
    ਵਾਪਸ SDL_Unsupported();
}

ਖਾਲੀ VIVANTE_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    // FIXME
}

ਖਾਲੀ VIVANTE_Show_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    vdk_Show_ਖਿੜਕੀ(ਅੰਕੜੇ->native_ਖਿੜਕੀ);
#ਜੇ_ਅੰਤ
    SDL_ਸੈੱਟ_Mouse_Focus(ਖਿੜਕੀ);
    SDL_ਸੈੱਟ_Keyboard_Focus(ਖਿੜਕੀ);
}

ਖਾਲੀ VIVANTE_Hide_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    vdk_Hide_ਖਿੜਕੀ(ਅੰਕੜੇ->native_ਖਿੜਕੀ);
#ਜੇ_ਅੰਤ
    SDL_ਸੈੱਟ_Mouse_Focus(ਨਿਰਾ);
    SDL_ਸੈੱਟ_Keyboard_Focus(ਨਿਰਾ);
}

/*****************************************************************************/
// SDL event functions
/*****************************************************************************/
ਖਾਲੀ VIVANTE_PumpEvents(SDL_VideoDevice *_this)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_ਨਿਵੇਸ਼_LINUXEV
    SDL_EVDEV_Poll();
#ਜੇ_ਅੰਤ
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_VIVANTE
