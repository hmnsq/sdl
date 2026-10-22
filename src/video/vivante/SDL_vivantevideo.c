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
#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VIVANTE

// SDL internals
#അന്തര്ഭാവ "../SDL_sysvideo.h"
#അന്തര്ഭാവ "../../events/SDL_events_c.h"

#ifdef SDL_നിവേശം_LINUXEV
#അന്തര്ഭാവ "../../core/linux/SDL_evdev.h"
#endif

#അന്തര്ഭാവ "SDL_vivantevideo.h"
#അന്തര്ഭാവ "SDL_vivanteplatform.h"
#അന്തര്ഭാവ "SDL_vivanteopengles.h"
#അന്തര്ഭാവ "SDL_vivantevulkan.h"

സ്ഥിതം ശൂന്യം VIVANTE_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

സ്ഥിതം SDL_VideoDevice *VIVANTE_Create(ശൂന്യം)
{
    SDL_VideoDevice *device;
    SDL_VideoData *data;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, വലുപ്പം(SDL_VideoDevice));
    എങ്കിൽ (!device) {
        തിരികെ ശൂന്യ;
    }

    // Initialize internal data
    data = (SDL_VideoData *)SDL_calloc(1, വലുപ്പം(SDL_VideoData));
    എങ്കിൽ (!data) {
        SDL_free(device);
        തിരികെ ശൂന്യ;
    }

    device->internal = data;

    // Setup amount of available displays
    device->അക്കം_displays = 0;

    // Set device free function
    device->സ്വതന്ത്രം = VIVANTE_Destroy;

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

    തിരികെ device;
}

VideoBootStrap VIVANTE_bootstrap = {
    "vivante",
    "Vivante EGL Video Driver",
    VIVANTE_Create,
    ശൂന്യ, // no ShowMessageBox implementation
    false
};

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/*****************************************************************************/

സ്ഥിതം bool VIVANTE_AddVideoDisplays(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_VideoDisplay display;
    SDL_DisplayMode mode;
    SDL_DisplayData *data;
    പൂർണ്ണസംഖ്യ pitch = 0, bpp = 0;
    unsigned long pixels = 0;

    data = (SDL_DisplayData *)SDL_calloc(1, വലുപ്പം(SDL_DisplayData));
    എങ്കിൽ (!data) {
        തിരികെ false;
    }

    SDL_zero(mode);
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    data->native_display = vdkGetDisplay(videodata->vdk_private);

    vdkGetDisplayInfo(data->native_display, &mode.w, &mode.h, &pixels, &pitch,
                      &bpp);
#അല്ലെങ്കിൽ
    data->native_display = videodata->fbGetDisplayByIndex(0);

    videodata->fbGetDisplayInfo(data->native_display, &mode.w, &mode.h,
                                &pixels, &pitch, &bpp);
#endif // SDL_VIDEO_DRIVER_VIVANTE_VDK

    തിരഞ്ഞെടുപ്പ് (bpp) {
    സ്ഥിരസ്ഥിതി: // Is another format used?
    അവസ്ഥ 32:
        mode.format = SDL_PIXELFORMAT_ARGB8888;
        നിർത്തുക;
    അവസ്ഥ 16:
        mode.format = SDL_PIXELFORMAT_RGB565;
        നിർത്തുക;
    }
    // FIXME: How do we query refresh rate?
    mode.refresh_rate = 60.0f;

    SDL_zero(display);
    display.name = VIVANTE_GetDisplayName(_this);
    display.desktop_mode = mode;
    display.internal = data;
    എങ്കിൽ (SDL_AddVideoDisplay(&display, false) == 0) {
        തിരികെ false;
    }
    തിരികെ true;
}

bool VIVANTE_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;

#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    videodata->vdk_private = vdkInitialize();
    എങ്കിൽ (!videodata->vdk_private) {
        തിരികെ SDL_SetError("vdkInitialize() failed");
    }
#അല്ലെങ്കിൽ
    videodata->egl_handle = SDL_LoadObject("libEGL.so.1");
    എങ്കിൽ (!videodata->egl_handle) {
        videodata->egl_handle = SDL_LoadObject("libEGL.so");
        എങ്കിൽ (!videodata->egl_handle) {
            തിരികെ false;
        }
    }
#define LOAD_FUNC(TYPE, NAME)                                               \
    videodata->NAME = (TYPE)SDL_LoadFunction(videodata->egl_handle, #NAME); \
    എങ്കിൽ (!videodata->NAME)                                                   \
        തിരികെ false;

    LOAD_FUNC(EGLNativeDisplayType (EGLAPIENTRY *)(ശൂന്യം *), fbGetDisplay);
    LOAD_FUNC(EGLNativeDisplayType (EGLAPIENTRY *)(പൂർണ്ണസംഖ്യ), fbGetDisplayByIndex);
    LOAD_FUNC(ശൂന്യം (EGLAPIENTRY *)(EGLNativeDisplayType, പൂർണ്ണസംഖ്യ *, പൂർണ്ണസംഖ്യ *), fbGetDisplayGeometry);
    LOAD_FUNC(ശൂന്യം (EGLAPIENTRY *)(EGLNativeDisplayType, പൂർണ്ണസംഖ്യ *, പൂർണ്ണസംഖ്യ *, unsigned long *, പൂർണ്ണസംഖ്യ *, പൂർണ്ണസംഖ്യ *), fbGetDisplayInfo);
    LOAD_FUNC(ശൂന്യം (EGLAPIENTRY *)(EGLNativeDisplayType), fbDestroyDisplay);
    LOAD_FUNC(EGLNativeWindowType (EGLAPIENTRY *)(EGLNativeDisplayType, പൂർണ്ണസംഖ്യ, പൂർണ്ണസംഖ്യ, പൂർണ്ണസംഖ്യ, പൂർണ്ണസംഖ്യ), fbCreateWindow);
    LOAD_FUNC(ശൂന്യം (EGLAPIENTRY *)(EGLNativeWindowType, പൂർണ്ണസംഖ്യ *, പൂർണ്ണസംഖ്യ *, പൂർണ്ണസംഖ്യ *, പൂർണ്ണസംഖ്യ *), fbGetWindowGeometry);
    LOAD_FUNC(ശൂന്യം (EGLAPIENTRY *)(EGLNativeWindowType, പൂർണ്ണസംഖ്യ *, പൂർണ്ണസംഖ്യ *, പൂർണ്ണസംഖ്യ *, പൂർണ്ണസംഖ്യ *, പൂർണ്ണസംഖ്യ *, unsigned പൂർണ്ണസംഖ്യ *), fbGetWindowInfo);
    LOAD_FUNC(ശൂന്യം (EGLAPIENTRY *)(EGLNativeWindowType), fbDestroyWindow);
#endif

    എങ്കിൽ (!VIVANTE_SetupPlatform(_this)) {
        തിരികെ false;
    }

    എങ്കിൽ (!VIVANTE_AddVideoDisplays(_this)) {
        തിരികെ false;
    }

    VIVANTE_UpdateDisplayScale(_this);

#ifdef SDL_നിവേശം_LINUXEV
    എങ്കിൽ (!SDL_EVDEV_Init()) {
        തിരികെ false;
    }
#endif

    തിരികെ true;
}

ശൂന്യം VIVANTE_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;

#ifdef SDL_നിവേശം_LINUXEV
    SDL_EVDEV_Quit();
#endif

    VIVANTE_CleanupPlatform(_this);

#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    എങ്കിൽ (videodata->vdk_private) {
        vdkExit(videodata->vdk_private);
        videodata->vdk_private = ശൂന്യ;
    }
#അല്ലെങ്കിൽ
    എങ്കിൽ (videodata->egl_handle) {
        SDL_UnloadObject(videodata->egl_handle);
        videodata->egl_handle = ശൂന്യ;
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
    data = (SDL_WindowData *)SDL_calloc(1, വലുപ്പം(SDL_WindowData));
    എങ്കിൽ (!data) {
        തിരികെ false;
    }

    // Setup driver data for this window
    window->internal = data;

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_VIVANTE_DISPLAY_POINTER, displaydata->native_display);

#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    data->native_window = vdkCreateWindow(displaydata->native_display, window->x, window->y, window->w, window->h);
#അല്ലെങ്കിൽ
    data->native_window = videodata->fbCreateWindow(displaydata->native_display, window->x, window->y, window->w, window->h);
#endif
    എങ്കിൽ (!data->native_window) {
        തിരികെ SDL_SetError("VIVANTE: Can't create native window");
    }
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_VIVANTE_WINDOW_POINTER, data->native_window);

#ifdef SDL_VIDEO_OPENGL_EGL
    എങ്കിൽ (window->flags & SDL_WINDOW_OPENGL) {
        data->egl_surface = SDL_EGL_CreateSurface(_this, window, data->native_window);
        എങ്കിൽ (data->egl_surface == EGL_NO_SURFACE) {
            തിരികെ SDL_SetError("VIVANTE: Can't create EGL surface");
        }
    } അല്ലെങ്കിൽ {
        data->egl_surface = EGL_NO_SURFACE;
    }
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_VIVANTE_SURFACE_POINTER, data->egl_surface);
#endif

    // Window has been successfully created
    തിരികെ true;
}

ശൂന്യം VIVANTE_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_WindowData *data;

    data = window->internal;
    എങ്കിൽ (data) {
#ifdef SDL_VIDEO_OPENGL_EGL
        എങ്കിൽ (data->egl_surface != EGL_NO_SURFACE) {
            SDL_EGL_DestroySurface(_this, data->egl_surface);
        }
#endif

        എങ്കിൽ (data->native_window) {
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
            vdkDestroyWindow(data->native_window);
#അല്ലെങ്കിൽ
            videodata->fbDestroyWindow(data->native_window);
#endif
        }

        SDL_free(data);
    }
    window->internal = ശൂന്യ;
}

ശൂന്യം VIVANTE_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_WindowData *data = window->internal;
    vdkSetWindowTitle(data->native_window, window->title);
#endif
}

bool VIVANTE_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    // FIXME
    തിരികെ SDL_Unsupported();
}

ശൂന്യം VIVANTE_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    // FIXME
}

ശൂന്യം VIVANTE_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_WindowData *data = window->internal;
    vdkShowWindow(data->native_window);
#endif
    SDL_SetMouseFocus(window);
    SDL_SetKeyboardFocus(window);
}

ശൂന്യം VIVANTE_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_WindowData *data = window->internal;
    vdkHideWindow(data->native_window);
#endif
    SDL_SetMouseFocus(ശൂന്യ);
    SDL_SetKeyboardFocus(ശൂന്യ);
}

/*****************************************************************************/
// SDL event functions
/*****************************************************************************/
ശൂന്യം VIVANTE_PumpEvents(SDL_VideoDevice *_this)
{
#ifdef SDL_നിവേശം_LINUXEV
    SDL_EVDEV_Poll();
#endif
}

#endif // SDL_VIDEO_DRIVER_VIVANTE
