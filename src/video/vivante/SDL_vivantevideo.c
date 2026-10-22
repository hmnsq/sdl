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
#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VIVANTE

// SDL internals
#அந்தர்பாவ "../SDL_sysvideo.h"
#அந்தர்பாவ "../../events/SDL_events_c.h"

#ifdef SDL_உள்ளீடு_LINUXEV
#அந்தர்பாவ "../../core/linux/SDL_evdev.h"
#endif

#அந்தர்பாவ "SDL_vivantevideo.h"
#அந்தர்பாவ "SDL_vivanteplatform.h"
#அந்தர்பாவ "SDL_vivanteopengles.h"
#அந்தர்பாவ "SDL_vivantevulkan.h"

நிலையான வெறுமை VIVANTE_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

நிலையான SDL_VideoDevice *VIVANTE_Create(வெறுமை)
{
    SDL_VideoDevice *device;
    SDL_VideoData *data;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, அளவு(SDL_VideoDevice));
    எனில் (!device) {
        திரும்பு வெற்று;
    }

    // Initialize internal data
    data = (SDL_VideoData *)SDL_calloc(1, அளவு(SDL_VideoData));
    எனில் (!data) {
        SDL_free(device);
        திரும்பு வெற்று;
    }

    device->internal = data;

    // Setup amount of available displays
    device->இலக்கம்_displays = 0;

    // Set device free function
    device->விடுவி = VIVANTE_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = VIVANTE_VideoInit;
    device->VideoQuit = VIVANTE_VideoQuit;
    device->CreateSDLWindow = VIVANTE_CreateWindow;
    device->SetWindowTitle = VIVANTE_SetWindowTitle;
    device->SetWindowPosition = VIVANTE_SetWindowPosition;
    device->SetWindowSize = VIVANTE_SetWindowSize;
    device->ShowWindow = VIVANTE_ShowWindow;
    device->HideWindow = VIVANTE_HideWindow;
    device->DestroyWindow = VIVANTE_DestroyWindow;

#ifdef SDL_VIDEO_OPENGL_EGL
    device->GL_LoadLibrary = VIVANTE_GLES_LoadLibrary;
    device->GL_GetProcAddress = VIVANTE_GLES_GetProcAddress;
    device->GL_UnloadLibrary = VIVANTE_GLES_UnloadLibrary;
    device->GL_CreateContext = VIVANTE_GLES_CreateContext;
    device->GL_MakeCurrent = VIVANTE_GLES_MakeCurrent;
    device->GL_SetSwapInterval = VIVANTE_GLES_SetSwapInterval;
    device->GL_GetSwapInterval = VIVANTE_GLES_GetSwapInterval;
    device->GL_SwapWindow = VIVANTE_GLES_SwapWindow;
    device->GL_DestroyContext = VIVANTE_GLES_DestroyContext;
#endif

#ifdef SDL_VIDEO_VULKAN
    device->Vulkan_LoadLibrary = VIVANTE_Vulkan_LoadLibrary;
    device->Vulkan_UnloadLibrary = VIVANTE_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = VIVANTE_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = VIVANTE_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = VIVANTE_Vulkan_DestroySurface;
#endif

    device->PumpEvents = VIVANTE_PumpEvents;

    திரும்பு device;
}

VideoBootStrap VIVANTE_bootstrap = {
    "vivante",
    "Vivante EGL Video Driver",
    VIVANTE_Create,
    வெற்று, // no ShowMessageBox implementation
    false
};

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/*****************************************************************************/

நிலையான bool VIVANTE_AddVideoDisplays(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_VideoDisplay display;
    SDL_DisplayMode mode;
    SDL_DisplayData *data;
    முழு pitch = 0, bpp = 0;
    unsigned long pixels = 0;

    data = (SDL_DisplayData *)SDL_calloc(1, அளவு(SDL_DisplayData));
    எனில் (!data) {
        திரும்பு false;
    }

    SDL_zero(mode);
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    data->native_display = vdkGetDisplay(videodata->vdk_private);

    vdkGetDisplayInfo(data->native_display, &mode.w, &mode.h, &pixels, &pitch,
                      &bpp);
#இல்லையெனில்
    data->native_display = videodata->fbGetDisplayByIndex(0);

    videodata->fbGetDisplayInfo(data->native_display, &mode.w, &mode.h,
                                &pixels, &pitch, &bpp);
#endif // SDL_VIDEO_DRIVER_VIVANTE_VDK

    தேர்வு (bpp) {
    இயல்பு: // Is another format used?
    நிலை 32:
        mode.format = SDL_PIXELFORMAT_ARGB8888;
        நிறுத்து;
    நிலை 16:
        mode.format = SDL_PIXELFORMAT_RGB565;
        நிறுத்து;
    }
    // FIXME: How do we query refresh rate?
    mode.refresh_rate = 60.0f;

    SDL_zero(display);
    display.name = VIVANTE_GetDisplayName(_this);
    display.desktop_mode = mode;
    display.internal = data;
    எனில் (SDL_AddVideoDisplay(&display, false) == 0) {
        திரும்பு false;
    }
    திரும்பு true;
}

bool VIVANTE_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;

#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    videodata->vdk_private = vdkInitialize();
    எனில் (!videodata->vdk_private) {
        திரும்பு SDL_SetError("vdkInitialize() failed");
    }
#இல்லையெனில்
    videodata->egl_handle = SDL_LoadObject("libEGL.so.1");
    எனில் (!videodata->egl_handle) {
        videodata->egl_handle = SDL_LoadObject("libEGL.so");
        எனில் (!videodata->egl_handle) {
            திரும்பு false;
        }
    }
#define LOAD_FUNC(TYPE, NAME)                                               \
    videodata->NAME = (TYPE)SDL_LoadFunction(videodata->egl_handle, #NAME); \
    எனில் (!videodata->NAME)                                                   \
        திரும்பு false;

    LOAD_FUNC(EGLNativeDisplayType (EGLAPIENTRY *)(வெறுமை *), fbGetDisplay);
    LOAD_FUNC(EGLNativeDisplayType (EGLAPIENTRY *)(முழு), fbGetDisplayByIndex);
    LOAD_FUNC(வெறுமை (EGLAPIENTRY *)(EGLNativeDisplayType, முழு *, முழு *), fbGetDisplayGeometry);
    LOAD_FUNC(வெறுமை (EGLAPIENTRY *)(EGLNativeDisplayType, முழு *, முழு *, unsigned long *, முழு *, முழு *), fbGetDisplayInfo);
    LOAD_FUNC(வெறுமை (EGLAPIENTRY *)(EGLNativeDisplayType), fbDestroyDisplay);
    LOAD_FUNC(EGLNativeWindowType (EGLAPIENTRY *)(EGLNativeDisplayType, முழு, முழு, முழு, முழு), fbCreateWindow);
    LOAD_FUNC(வெறுமை (EGLAPIENTRY *)(EGLNativeWindowType, முழு *, முழு *, முழு *, முழு *), fbGetWindowGeometry);
    LOAD_FUNC(வெறுமை (EGLAPIENTRY *)(EGLNativeWindowType, முழு *, முழு *, முழு *, முழு *, முழு *, unsigned முழு *), fbGetWindowInfo);
    LOAD_FUNC(வெறுமை (EGLAPIENTRY *)(EGLNativeWindowType), fbDestroyWindow);
#endif

    எனில் (!VIVANTE_SetupPlatform(_this)) {
        திரும்பு false;
    }

    எனில் (!VIVANTE_AddVideoDisplays(_this)) {
        திரும்பு false;
    }

    VIVANTE_UpdateDisplayScale(_this);

#ifdef SDL_உள்ளீடு_LINUXEV
    எனில் (!SDL_EVDEV_Init()) {
        திரும்பு false;
    }
#endif

    திரும்பு true;
}

வெறுமை VIVANTE_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;

#ifdef SDL_உள்ளீடு_LINUXEV
    SDL_EVDEV_Quit();
#endif

    VIVANTE_CleanupPlatform(_this);

#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    எனில் (videodata->vdk_private) {
        vdkExit(videodata->vdk_private);
        videodata->vdk_private = வெற்று;
    }
#இல்லையெனில்
    எனில் (videodata->egl_handle) {
        SDL_UnloadObject(videodata->egl_handle);
        videodata->egl_handle = வெற்று;
    }
#endif
}

bool VIVANTE_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_DisplayData *displaydata;
    SDL_WindowData *data;

    displaydata = SDL_GetDisplayDriverData(SDL_GetPrimaryDisplay());

    // Allocate window internal data
    data = (SDL_WindowData *)SDL_calloc(1, அளவு(SDL_WindowData));
    எனில் (!data) {
        திரும்பு false;
    }

    // Setup driver data for this window
    window->internal = data;

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_VIVANTE_DISPLAY_POINTER, displaydata->native_display);

#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    data->native_window = vdkCreateWindow(displaydata->native_display, window->x, window->y, window->w, window->h);
#இல்லையெனில்
    data->native_window = videodata->fbCreateWindow(displaydata->native_display, window->x, window->y, window->w, window->h);
#endif
    எனில் (!data->native_window) {
        திரும்பு SDL_SetError("VIVANTE: Can't create native window");
    }
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_VIVANTE_WINDOW_POINTER, data->native_window);

#ifdef SDL_VIDEO_OPENGL_EGL
    எனில் (window->flags & SDL_WINDOW_OPENGL) {
        data->egl_surface = SDL_EGL_CreateSurface(_this, window, data->native_window);
        எனில் (data->egl_surface == EGL_NO_SURFACE) {
            திரும்பு SDL_SetError("VIVANTE: Can't create EGL surface");
        }
    } இல்லையெனில் {
        data->egl_surface = EGL_NO_SURFACE;
    }
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_VIVANTE_SURFACE_POINTER, data->egl_surface);
#endif

    // Window has been successfully created
    திரும்பு true;
}

வெறுமை VIVANTE_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_WindowData *data;

    data = window->internal;
    எனில் (data) {
#ifdef SDL_VIDEO_OPENGL_EGL
        எனில் (data->egl_surface != EGL_NO_SURFACE) {
            SDL_EGL_DestroySurface(_this, data->egl_surface);
        }
#endif

        எனில் (data->native_window) {
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
            vdkDestroyWindow(data->native_window);
#இல்லையெனில்
            videodata->fbDestroyWindow(data->native_window);
#endif
        }

        SDL_free(data);
    }
    window->internal = வெற்று;
}

வெறுமை VIVANTE_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_WindowData *data = window->internal;
    vdkSetWindowTitle(data->native_window, window->title);
#endif
}

bool VIVANTE_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    // FIXME
    திரும்பு SDL_Unsupported();
}

வெறுமை VIVANTE_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    // FIXME
}

வெறுமை VIVANTE_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_WindowData *data = window->internal;
    vdkShowWindow(data->native_window);
#endif
    SDL_SetMouseFocus(window);
    SDL_SetKeyboardFocus(window);
}

வெறுமை VIVANTE_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_WindowData *data = window->internal;
    vdkHideWindow(data->native_window);
#endif
    SDL_SetMouseFocus(வெற்று);
    SDL_SetKeyboardFocus(வெற்று);
}

/*****************************************************************************/
// SDL event functions
/*****************************************************************************/
வெறுமை VIVANTE_PumpEvents(SDL_VideoDevice *_this)
{
#ifdef SDL_உள்ளீடு_LINUXEV
    SDL_EVDEV_Poll();
#endif
}

#endif // SDL_VIDEO_DRIVER_VIVANTE
