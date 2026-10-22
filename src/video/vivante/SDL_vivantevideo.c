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

#ifdef SDL_VIDEO_DRIVER_VIVANTE

// SDL internals
#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../../events/SDL_events_c.h"

#ifdef SDL_निवेशः_LINUXEV
#अन्तर्भाव "../../core/linux/SDL_evdev.h"
#endif

#अन्तर्भाव "SDL_vivantevideo.h"
#अन्तर्भाव "SDL_vivanteplatform.h"
#अन्तर्भाव "SDL_vivanteopengles.h"
#अन्तर्भाव "SDL_vivantevulkan.h"

स्थिर शून्य VIVANTE_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

स्थिर SDL_VideoDevice *VIVANTE_Create(शून्य)
{
    SDL_VideoDevice *device;
    SDL_VideoData *data;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, परिमाण(SDL_VideoDevice));
    सचे (!device) {
        पटिनिवत्त रिक्त;
    }

    // Initialize internal data
    data = (SDL_VideoData *)SDL_calloc(1, परिमाण(SDL_VideoData));
    सचे (!data) {
        SDL_free(device);
        पटिनिवत्त रिक्त;
    }

    device->internal = data;

    // Setup amount of available displays
    device->अङ्कः_displays = 0;

    // Set device free function
    device->मुक्त = VIVANTE_Destroy;

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

    पटिनिवत्त device;
}

VideoBootStrap VIVANTE_bootstrap = {
    "vivante",
    "Vivante EGL Video Driver",
    VIVANTE_Create,
    रिक्त, // no ShowMessageBox implementation
    false
};

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/*****************************************************************************/

स्थिर bool VIVANTE_AddVideoDisplays(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_VideoDisplay display;
    SDL_DisplayMode mode;
    SDL_DisplayData *data;
    पूर्णाङ्क pitch = 0, bpp = 0;
    unsigned long pixels = 0;

    data = (SDL_DisplayData *)SDL_calloc(1, परिमाण(SDL_DisplayData));
    सचे (!data) {
        पटिनिवत्त false;
    }

    SDL_zero(mode);
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    data->native_display = vdkGetDisplay(videodata->vdk_private);

    vdkGetDisplayInfo(data->native_display, &mode.w, &mode.h, &pixels, &pitch,
                      &bpp);
#अञ्ञथा
    data->native_display = videodata->fbGetDisplayByIndex(0);

    videodata->fbGetDisplayInfo(data->native_display, &mode.w, &mode.h,
                                &pixels, &pitch, &bpp);
#endif // SDL_VIDEO_DRIVER_VIVANTE_VDK

    विकल्प (bpp) {
    स्वभाव: // Is another format used?
    पक्ष 32:
        mode.format = SDL_PIXELFORMAT_ARGB8888;
        भङ्ग;
    पक्ष 16:
        mode.format = SDL_PIXELFORMAT_RGB565;
        भङ्ग;
    }
    // FIXME: How do we query refresh rate?
    mode.refresh_rate = 60.0f;

    SDL_zero(display);
    display.name = VIVANTE_GetDisplayName(_this);
    display.desktop_mode = mode;
    display.internal = data;
    सचे (SDL_AddVideoDisplay(&display, false) == 0) {
        पटिनिवत्त false;
    }
    पटिनिवत्त true;
}

bool VIVANTE_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;

#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    videodata->vdk_private = vdkInitialize();
    सचे (!videodata->vdk_private) {
        पटिनिवत्त SDL_SetError("vdkInitialize() failed");
    }
#अञ्ञथा
    videodata->egl_handle = SDL_LoadObject("libEGL.so.1");
    सचे (!videodata->egl_handle) {
        videodata->egl_handle = SDL_LoadObject("libEGL.so");
        सचे (!videodata->egl_handle) {
            पटिनिवत्त false;
        }
    }
#define LOAD_FUNC(TYPE, NAME)                                               \
    videodata->NAME = (TYPE)SDL_LoadFunction(videodata->egl_handle, #NAME); \
    सचे (!videodata->NAME)                                                   \
        पटिनिवत्त false;

    LOAD_FUNC(EGLNativeDisplayType (EGLAPIENTRY *)(शून्य *), fbGetDisplay);
    LOAD_FUNC(EGLNativeDisplayType (EGLAPIENTRY *)(पूर्णाङ्क), fbGetDisplayByIndex);
    LOAD_FUNC(शून्य (EGLAPIENTRY *)(EGLNativeDisplayType, पूर्णाङ्क *, पूर्णाङ्क *), fbGetDisplayGeometry);
    LOAD_FUNC(शून्य (EGLAPIENTRY *)(EGLNativeDisplayType, पूर्णाङ्क *, पूर्णाङ्क *, unsigned long *, पूर्णाङ्क *, पूर्णाङ्क *), fbGetDisplayInfo);
    LOAD_FUNC(शून्य (EGLAPIENTRY *)(EGLNativeDisplayType), fbDestroyDisplay);
    LOAD_FUNC(EGLNativeWindowType (EGLAPIENTRY *)(EGLNativeDisplayType, पूर्णाङ्क, पूर्णाङ्क, पूर्णाङ्क, पूर्णाङ्क), fbCreateWindow);
    LOAD_FUNC(शून्य (EGLAPIENTRY *)(EGLNativeWindowType, पूर्णाङ्क *, पूर्णाङ्क *, पूर्णाङ्क *, पूर्णाङ्क *), fbGetWindowGeometry);
    LOAD_FUNC(शून्य (EGLAPIENTRY *)(EGLNativeWindowType, पूर्णाङ्क *, पूर्णाङ्क *, पूर्णाङ्क *, पूर्णाङ्क *, पूर्णाङ्क *, unsigned पूर्णाङ्क *), fbGetWindowInfo);
    LOAD_FUNC(शून्य (EGLAPIENTRY *)(EGLNativeWindowType), fbDestroyWindow);
#endif

    सचे (!VIVANTE_SetupPlatform(_this)) {
        पटिनिवत्त false;
    }

    सचे (!VIVANTE_AddVideoDisplays(_this)) {
        पटिनिवत्त false;
    }

    VIVANTE_UpdateDisplayScale(_this);

#ifdef SDL_निवेशः_LINUXEV
    सचे (!SDL_EVDEV_Init()) {
        पटिनिवत्त false;
    }
#endif

    पटिनिवत्त true;
}

शून्य VIVANTE_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;

#ifdef SDL_निवेशः_LINUXEV
    SDL_EVDEV_Quit();
#endif

    VIVANTE_CleanupPlatform(_this);

#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    सचे (videodata->vdk_private) {
        vdkExit(videodata->vdk_private);
        videodata->vdk_private = रिक्त;
    }
#अञ्ञथा
    सचे (videodata->egl_handle) {
        SDL_UnloadObject(videodata->egl_handle);
        videodata->egl_handle = रिक्त;
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
    data = (SDL_WindowData *)SDL_calloc(1, परिमाण(SDL_WindowData));
    सचे (!data) {
        पटिनिवत्त false;
    }

    // Setup driver data for this window
    window->internal = data;

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_VIVANTE_DISPLAY_POINTER, displaydata->native_display);

#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    data->native_window = vdkCreateWindow(displaydata->native_display, window->x, window->y, window->w, window->h);
#अञ्ञथा
    data->native_window = videodata->fbCreateWindow(displaydata->native_display, window->x, window->y, window->w, window->h);
#endif
    सचे (!data->native_window) {
        पटिनिवत्त SDL_SetError("VIVANTE: Can't create native window");
    }
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_VIVANTE_WINDOW_POINTER, data->native_window);

#ifdef SDL_VIDEO_OPENGL_EGL
    सचे (window->flags & SDL_WINDOW_OPENGL) {
        data->egl_surface = SDL_EGL_CreateSurface(_this, window, data->native_window);
        सचे (data->egl_surface == EGL_NO_SURFACE) {
            पटिनिवत्त SDL_SetError("VIVANTE: Can't create EGL surface");
        }
    } अञ्ञथा {
        data->egl_surface = EGL_NO_SURFACE;
    }
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_VIVANTE_SURFACE_POINTER, data->egl_surface);
#endif

    // Window has been successfully created
    पटिनिवत्त true;
}

शून्य VIVANTE_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_WindowData *data;

    data = window->internal;
    सचे (data) {
#ifdef SDL_VIDEO_OPENGL_EGL
        सचे (data->egl_surface != EGL_NO_SURFACE) {
            SDL_EGL_DestroySurface(_this, data->egl_surface);
        }
#endif

        सचे (data->native_window) {
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
            vdkDestroyWindow(data->native_window);
#अञ्ञथा
            videodata->fbDestroyWindow(data->native_window);
#endif
        }

        SDL_free(data);
    }
    window->internal = रिक्त;
}

शून्य VIVANTE_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_WindowData *data = window->internal;
    vdkSetWindowTitle(data->native_window, window->title);
#endif
}

bool VIVANTE_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    // FIXME
    पटिनिवत्त SDL_Unsupported();
}

शून्य VIVANTE_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    // FIXME
}

शून्य VIVANTE_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_WindowData *data = window->internal;
    vdkShowWindow(data->native_window);
#endif
    SDL_SetMouseFocus(window);
    SDL_SetKeyboardFocus(window);
}

शून्य VIVANTE_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_WindowData *data = window->internal;
    vdkHideWindow(data->native_window);
#endif
    SDL_SetMouseFocus(रिक्त);
    SDL_SetKeyboardFocus(रिक्त);
}

/*****************************************************************************/
// SDL event functions
/*****************************************************************************/
शून्य VIVANTE_PumpEvents(SDL_VideoDevice *_this)
{
#ifdef SDL_निवेशः_LINUXEV
    SDL_EVDEV_Poll();
#endif
}

#endif // SDL_VIDEO_DRIVER_VIVANTE
