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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VIVANTE

// SDL internals
#ଅନ୍ତର୍ଭାଵ "../SDL_sysvideo.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_events_c.h"

#ifdef SDL_ନିବେଶ_LINUXEV
#ଅନ୍ତର୍ଭାଵ "../../core/linux/SDL_evdev.h"
#endif

#ଅନ୍ତର୍ଭାଵ "SDL_vivantevideo.h"
#ଅନ୍ତର୍ଭାଵ "SDL_vivanteplatform.h"
#ଅନ୍ତର୍ଭାଵ "SDL_vivanteopengles.h"
#ଅନ୍ତର୍ଭାଵ "SDL_vivantevulkan.h"

ସ୍ଥିର ଶୂନ୍ୟ VIVANTE_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

ସ୍ଥିର SDL_VideoDevice *VIVANTE_Create(ଶୂନ୍ୟ)
{
    SDL_VideoDevice *device;
    SDL_VideoData *data;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, ଆକାର(SDL_VideoDevice));
    ଯଦି (!device) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    // Initialize internal data
    data = (SDL_VideoData *)SDL_calloc(1, ଆକାର(SDL_VideoData));
    ଯଦି (!data) {
        SDL_free(device);
        ଫେରନ୍ତୁ ଖାଲି;
    }

    device->internal = data;

    // Setup amount of available displays
    device->ଅଙ୍କ_displays = 0;

    // Set device free function
    device->ମୁକ୍ତ = VIVANTE_Destroy;

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

    ଫେରନ୍ତୁ device;
}

VideoBootStrap VIVANTE_bootstrap = {
    "vivante",
    "Vivante EGL Video Driver",
    VIVANTE_Create,
    ଖାଲି, // no ShowMessageBox implementation
    false
};

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/*****************************************************************************/

ସ୍ଥିର bool VIVANTE_AddVideoDisplays(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_VideoDisplay display;
    SDL_DisplayMode mode;
    SDL_DisplayData *data;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା pitch = 0, bpp = 0;
    unsigned long pixels = 0;

    data = (SDL_DisplayData *)SDL_calloc(1, ଆକାର(SDL_DisplayData));
    ଯଦି (!data) {
        ଫେରନ୍ତୁ false;
    }

    SDL_zero(mode);
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    data->native_display = vdkGetDisplay(videodata->vdk_private);

    vdkGetDisplayInfo(data->native_display, &mode.w, &mode.h, &pixels, &pitch,
                      &bpp);
#ଅନ୍ୟଥା
    data->native_display = videodata->fbGetDisplayByIndex(0);

    videodata->fbGetDisplayInfo(data->native_display, &mode.w, &mode.h,
                                &pixels, &pitch, &bpp);
#endif // SDL_VIDEO_DRIVER_VIVANTE_VDK

    ବାଛ (bpp) {
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ: // Is another format used?
    ସ୍ଥିତି 32:
        mode.format = SDL_PIXELFORMAT_ARGB8888;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି 16:
        mode.format = SDL_PIXELFORMAT_RGB565;
        ଭାଙ୍ଗ;
    }
    // FIXME: How do we query refresh rate?
    mode.refresh_rate = 60.0f;

    SDL_zero(display);
    display.name = VIVANTE_GetDisplayName(_this);
    display.desktop_mode = mode;
    display.internal = data;
    ଯଦି (SDL_AddVideoDisplay(&display, false) == 0) {
        ଫେରନ୍ତୁ false;
    }
    ଫେରନ୍ତୁ true;
}

bool VIVANTE_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;

#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    videodata->vdk_private = vdkInitialize();
    ଯଦି (!videodata->vdk_private) {
        ଫେରନ୍ତୁ SDL_SetError("vdkInitialize() failed");
    }
#ଅନ୍ୟଥା
    videodata->egl_handle = SDL_LoadObject("libEGL.so.1");
    ଯଦି (!videodata->egl_handle) {
        videodata->egl_handle = SDL_LoadObject("libEGL.so");
        ଯଦି (!videodata->egl_handle) {
            ଫେରନ୍ତୁ false;
        }
    }
#define LOAD_FUNC(TYPE, NAME)                                               \
    videodata->NAME = (TYPE)SDL_LoadFunction(videodata->egl_handle, #NAME); \
    ଯଦି (!videodata->NAME)                                                   \
        ଫେରନ୍ତୁ false;

    LOAD_FUNC(EGLNativeDisplayType (EGLAPIENTRY *)(ଶୂନ୍ୟ *), fbGetDisplay);
    LOAD_FUNC(EGLNativeDisplayType (EGLAPIENTRY *)(ପୂର୍ଣ୍ଣସଂଖ୍ୟା), fbGetDisplayByIndex);
    LOAD_FUNC(ଶୂନ୍ୟ (EGLAPIENTRY *)(EGLNativeDisplayType, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *), fbGetDisplayGeometry);
    LOAD_FUNC(ଶୂନ୍ୟ (EGLAPIENTRY *)(EGLNativeDisplayType, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *, unsigned long *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *), fbGetDisplayInfo);
    LOAD_FUNC(ଶୂନ୍ୟ (EGLAPIENTRY *)(EGLNativeDisplayType), fbDestroyDisplay);
    LOAD_FUNC(EGLNativeWindowType (EGLAPIENTRY *)(EGLNativeDisplayType, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା), fbCreateWindow);
    LOAD_FUNC(ଶୂନ୍ୟ (EGLAPIENTRY *)(EGLNativeWindowType, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *), fbGetWindowGeometry);
    LOAD_FUNC(ଶୂନ୍ୟ (EGLAPIENTRY *)(EGLNativeWindowType, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା *), fbGetWindowInfo);
    LOAD_FUNC(ଶୂନ୍ୟ (EGLAPIENTRY *)(EGLNativeWindowType), fbDestroyWindow);
#endif

    ଯଦି (!VIVANTE_SetupPlatform(_this)) {
        ଫେରନ୍ତୁ false;
    }

    ଯଦି (!VIVANTE_AddVideoDisplays(_this)) {
        ଫେରନ୍ତୁ false;
    }

    VIVANTE_UpdateDisplayScale(_this);

#ifdef SDL_ନିବେଶ_LINUXEV
    ଯଦି (!SDL_EVDEV_Init()) {
        ଫେରନ୍ତୁ false;
    }
#endif

    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ VIVANTE_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;

#ifdef SDL_ନିବେଶ_LINUXEV
    SDL_EVDEV_Quit();
#endif

    VIVANTE_CleanupPlatform(_this);

#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    ଯଦି (videodata->vdk_private) {
        vdkExit(videodata->vdk_private);
        videodata->vdk_private = ଖାଲି;
    }
#ଅନ୍ୟଥା
    ଯଦି (videodata->egl_handle) {
        SDL_UnloadObject(videodata->egl_handle);
        videodata->egl_handle = ଖାଲି;
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
    data = (SDL_WindowData *)SDL_calloc(1, ଆକାର(SDL_WindowData));
    ଯଦି (!data) {
        ଫେରନ୍ତୁ false;
    }

    // Setup driver data for this window
    window->internal = data;

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_VIVANTE_DISPLAY_POINTER, displaydata->native_display);

#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    data->native_window = vdkCreateWindow(displaydata->native_display, window->x, window->y, window->w, window->h);
#ଅନ୍ୟଥା
    data->native_window = videodata->fbCreateWindow(displaydata->native_display, window->x, window->y, window->w, window->h);
#endif
    ଯଦି (!data->native_window) {
        ଫେରନ୍ତୁ SDL_SetError("VIVANTE: Can't create native window");
    }
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_VIVANTE_WINDOW_POINTER, data->native_window);

#ifdef SDL_VIDEO_OPENGL_EGL
    ଯଦି (window->flags & SDL_WINDOW_OPENGL) {
        data->egl_surface = SDL_EGL_CreateSurface(_this, window, data->native_window);
        ଯଦି (data->egl_surface == EGL_NO_SURFACE) {
            ଫେରନ୍ତୁ SDL_SetError("VIVANTE: Can't create EGL surface");
        }
    } ଅନ୍ୟଥା {
        data->egl_surface = EGL_NO_SURFACE;
    }
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_VIVANTE_SURFACE_POINTER, data->egl_surface);
#endif

    // Window has been successfully created
    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ VIVANTE_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_WindowData *data;

    data = window->internal;
    ଯଦି (data) {
#ifdef SDL_VIDEO_OPENGL_EGL
        ଯଦି (data->egl_surface != EGL_NO_SURFACE) {
            SDL_EGL_DestroySurface(_this, data->egl_surface);
        }
#endif

        ଯଦି (data->native_window) {
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
            vdkDestroyWindow(data->native_window);
#ଅନ୍ୟଥା
            videodata->fbDestroyWindow(data->native_window);
#endif
        }

        SDL_free(data);
    }
    window->internal = ଖାଲି;
}

ଶୂନ୍ୟ VIVANTE_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_WindowData *data = window->internal;
    vdkSetWindowTitle(data->native_window, window->title);
#endif
}

bool VIVANTE_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    // FIXME
    ଫେରନ୍ତୁ SDL_Unsupported();
}

ଶୂନ୍ୟ VIVANTE_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    // FIXME
}

ଶୂନ୍ୟ VIVANTE_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_WindowData *data = window->internal;
    vdkShowWindow(data->native_window);
#endif
    SDL_SetMouseFocus(window);
    SDL_SetKeyboardFocus(window);
}

ଶୂନ୍ୟ VIVANTE_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_WindowData *data = window->internal;
    vdkHideWindow(data->native_window);
#endif
    SDL_SetMouseFocus(ଖାଲି);
    SDL_SetKeyboardFocus(ଖାଲି);
}

/*****************************************************************************/
// SDL event functions
/*****************************************************************************/
ଶୂନ୍ୟ VIVANTE_PumpEvents(SDL_VideoDevice *_this)
{
#ifdef SDL_ନିବେଶ_LINUXEV
    SDL_EVDEV_Poll();
#endif
}

#endif // SDL_VIDEO_DRIVER_VIVANTE
