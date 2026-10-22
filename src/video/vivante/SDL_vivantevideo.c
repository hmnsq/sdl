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

#ifdef SDL_VIDEO_DRIVER_VIVANTE

// SDL internals
#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"

#ifdef SDL_ಒಳಹರಿವು_LINUXEV
#ಅನ್ತರ್ಭಾವ "../../core/linux/SDL_evdev.h"
#endif

#ಅನ್ತರ್ಭಾವ "SDL_vivantevideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_vivanteplatform.h"
#ಅನ್ತರ್ಭಾವ "SDL_vivanteopengles.h"
#ಅನ್ತರ್ಭಾವ "SDL_vivantevulkan.h"

ಸ್ಥಿರ ಶೂನ್ಯ VIVANTE_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

ಸ್ಥಿರ SDL_VideoDevice *VIVANTE_Create(ಶೂನ್ಯ)
{
    SDL_VideoDevice *device;
    SDL_VideoData *data;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, ಪರಿಮಾಣ(SDL_VideoDevice));
    ಯದಿ (!device) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    // Initialize internal data
    data = (SDL_VideoData *)SDL_calloc(1, ಪರಿಮಾಣ(SDL_VideoData));
    ಯದಿ (!data) {
        SDL_free(device);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    device->internal = data;

    // Setup amount of available displays
    device->ಅಂಕೆ_displays = 0;

    // Set device free function
    device->ಮುಕ್ತ = VIVANTE_Destroy;

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

    ಪ್ರತ್ಯಾಗಮ device;
}

VideoBootStrap VIVANTE_bootstrap = {
    "vivante",
    "Vivante EGL Video Driver",
    VIVANTE_Create,
    ರಿಕ್ತ, // no ShowMessageBox implementation
    false
};

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/*****************************************************************************/

ಸ್ಥಿರ bool VIVANTE_AddVideoDisplays(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_VideoDisplay display;
    SDL_DisplayMode mode;
    SDL_DisplayData *data;
    ಪೂರ್ಣಾಙ್ಕ pitch = 0, bpp = 0;
    unsigned long pixels = 0;

    data = (SDL_DisplayData *)SDL_calloc(1, ಪರಿಮಾಣ(SDL_DisplayData));
    ಯದಿ (!data) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    SDL_zero(mode);
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    data->native_display = vdkGetDisplay(videodata->vdk_private);

    vdkGetDisplayInfo(data->native_display, &mode.w, &mode.h, &pixels, &pitch,
                      &bpp);
#ಅನ್ಯಥಾ
    data->native_display = videodata->fbGetDisplayByIndex(0);

    videodata->fbGetDisplayInfo(data->native_display, &mode.w, &mode.h,
                                &pixels, &pitch, &bpp);
#endif // SDL_VIDEO_DRIVER_VIVANTE_VDK

    ವಿಕಲ್ಪ (bpp) {
    ಸ್ವಭಾವ: // Is another format used?
    ಪಕ್ಷ 32:
        mode.format = SDL_PIXELFORMAT_ARGB8888;
        ಭಙ್ಗ;
    ಪಕ್ಷ 16:
        mode.format = SDL_PIXELFORMAT_RGB565;
        ಭಙ್ಗ;
    }
    // FIXME: How do we query refresh rate?
    mode.refresh_rate = 60.0f;

    SDL_zero(display);
    display.name = VIVANTE_GetDisplayName(_this);
    display.desktop_mode = mode;
    display.internal = data;
    ಯದಿ (SDL_AddVideoDisplay(&display, false) == 0) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool VIVANTE_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;

#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    videodata->vdk_private = vdkInitialize();
    ಯದಿ (!videodata->vdk_private) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("vdkInitialize() failed");
    }
#ಅನ್ಯಥಾ
    videodata->egl_handle = SDL_LoadObject("libEGL.so.1");
    ಯದಿ (!videodata->egl_handle) {
        videodata->egl_handle = SDL_LoadObject("libEGL.so");
        ಯದಿ (!videodata->egl_handle) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
    }
#define LOAD_FUNC(TYPE, NAME)                                               \
    videodata->NAME = (TYPE)SDL_LoadFunction(videodata->egl_handle, #NAME); \
    ಯದಿ (!videodata->NAME)                                                   \
        ಪ್ರತ್ಯಾಗಮ false;

    LOAD_FUNC(EGLNativeDisplayType (EGLAPIENTRY *)(ಶೂನ್ಯ *), fbGetDisplay);
    LOAD_FUNC(EGLNativeDisplayType (EGLAPIENTRY *)(ಪೂರ್ಣಾಙ್ಕ), fbGetDisplayByIndex);
    LOAD_FUNC(ಶೂನ್ಯ (EGLAPIENTRY *)(EGLNativeDisplayType, ಪೂರ್ಣಾಙ್ಕ *, ಪೂರ್ಣಾಙ್ಕ *), fbGetDisplayGeometry);
    LOAD_FUNC(ಶೂನ್ಯ (EGLAPIENTRY *)(EGLNativeDisplayType, ಪೂರ್ಣಾಙ್ಕ *, ಪೂರ್ಣಾಙ್ಕ *, unsigned long *, ಪೂರ್ಣಾಙ್ಕ *, ಪೂರ್ಣಾಙ್ಕ *), fbGetDisplayInfo);
    LOAD_FUNC(ಶೂನ್ಯ (EGLAPIENTRY *)(EGLNativeDisplayType), fbDestroyDisplay);
    LOAD_FUNC(EGLNativeWindowType (EGLAPIENTRY *)(EGLNativeDisplayType, ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ), fbCreateWindow);
    LOAD_FUNC(ಶೂನ್ಯ (EGLAPIENTRY *)(EGLNativeWindowType, ಪೂರ್ಣಾಙ್ಕ *, ಪೂರ್ಣಾಙ್ಕ *, ಪೂರ್ಣಾಙ್ಕ *, ಪೂರ್ಣಾಙ್ಕ *), fbGetWindowGeometry);
    LOAD_FUNC(ಶೂನ್ಯ (EGLAPIENTRY *)(EGLNativeWindowType, ಪೂರ್ಣಾಙ್ಕ *, ಪೂರ್ಣಾಙ್ಕ *, ಪೂರ್ಣಾಙ್ಕ *, ಪೂರ್ಣಾಙ್ಕ *, ಪೂರ್ಣಾಙ್ಕ *, unsigned ಪೂರ್ಣಾಙ್ಕ *), fbGetWindowInfo);
    LOAD_FUNC(ಶೂನ್ಯ (EGLAPIENTRY *)(EGLNativeWindowType), fbDestroyWindow);
#endif

    ಯದಿ (!VIVANTE_SetupPlatform(_this)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಯದಿ (!VIVANTE_AddVideoDisplays(_this)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    VIVANTE_UpdateDisplayScale(_this);

#ifdef SDL_ಒಳಹರಿವು_LINUXEV
    ಯದಿ (!SDL_EVDEV_Init()) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
#endif

    ಪ್ರತ್ಯಾಗಮ true;
}

ಶೂನ್ಯ VIVANTE_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;

#ifdef SDL_ಒಳಹರಿವು_LINUXEV
    SDL_EVDEV_Quit();
#endif

    VIVANTE_CleanupPlatform(_this);

#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    ಯದಿ (videodata->vdk_private) {
        vdkExit(videodata->vdk_private);
        videodata->vdk_private = ರಿಕ್ತ;
    }
#ಅನ್ಯಥಾ
    ಯದಿ (videodata->egl_handle) {
        SDL_UnloadObject(videodata->egl_handle);
        videodata->egl_handle = ರಿಕ್ತ;
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
    data = (SDL_WindowData *)SDL_calloc(1, ಪರಿಮಾಣ(SDL_WindowData));
    ಯದಿ (!data) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    // Setup driver data for this window
    window->internal = data;

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_VIVANTE_DISPLAY_POINTER, displaydata->native_display);

#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    data->native_window = vdkCreateWindow(displaydata->native_display, window->x, window->y, window->w, window->h);
#ಅನ್ಯಥಾ
    data->native_window = videodata->fbCreateWindow(displaydata->native_display, window->x, window->y, window->w, window->h);
#endif
    ಯದಿ (!data->native_window) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("VIVANTE: Can't create native window");
    }
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_VIVANTE_WINDOW_POINTER, data->native_window);

#ifdef SDL_VIDEO_OPENGL_EGL
    ಯದಿ (window->flags & SDL_WINDOW_OPENGL) {
        data->egl_surface = SDL_EGL_CreateSurface(_this, window, data->native_window);
        ಯದಿ (data->egl_surface == EGL_NO_SURFACE) {
            ಪ್ರತ್ಯಾಗಮ SDL_SetError("VIVANTE: Can't create EGL surface");
        }
    } ಅನ್ಯಥಾ {
        data->egl_surface = EGL_NO_SURFACE;
    }
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_VIVANTE_SURFACE_POINTER, data->egl_surface);
#endif

    // Window has been successfully created
    ಪ್ರತ್ಯಾಗಮ true;
}

ಶೂನ್ಯ VIVANTE_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_WindowData *data;

    data = window->internal;
    ಯದಿ (data) {
#ifdef SDL_VIDEO_OPENGL_EGL
        ಯದಿ (data->egl_surface != EGL_NO_SURFACE) {
            SDL_EGL_DestroySurface(_this, data->egl_surface);
        }
#endif

        ಯದಿ (data->native_window) {
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
            vdkDestroyWindow(data->native_window);
#ಅನ್ಯಥಾ
            videodata->fbDestroyWindow(data->native_window);
#endif
        }

        SDL_free(data);
    }
    window->internal = ರಿಕ್ತ;
}

ಶೂನ್ಯ VIVANTE_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_WindowData *data = window->internal;
    vdkSetWindowTitle(data->native_window, window->title);
#endif
}

bool VIVANTE_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    // FIXME
    ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
}

ಶೂನ್ಯ VIVANTE_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    // FIXME
}

ಶೂನ್ಯ VIVANTE_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_WindowData *data = window->internal;
    vdkShowWindow(data->native_window);
#endif
    SDL_SetMouseFocus(window);
    SDL_SetKeyboardFocus(window);
}

ಶೂನ್ಯ VIVANTE_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_WindowData *data = window->internal;
    vdkHideWindow(data->native_window);
#endif
    SDL_SetMouseFocus(ರಿಕ್ತ);
    SDL_SetKeyboardFocus(ರಿಕ್ತ);
}

/*****************************************************************************/
// SDL event functions
/*****************************************************************************/
ಶೂನ್ಯ VIVANTE_PumpEvents(SDL_VideoDevice *_this)
{
#ifdef SDL_ಒಳಹರಿವು_LINUXEV
    SDL_EVDEV_Poll();
#endif
}

#endif // SDL_VIDEO_DRIVER_VIVANTE
