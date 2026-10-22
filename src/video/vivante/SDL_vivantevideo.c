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
#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VIVANTE

// SDL internals
#অন্তর্ভাব "../SDL_sysvideo.h"
#অন্তর্ভাব "../../events/SDL_events_c.h"

#ifdef SDL_প্রবেশ_LINUXEV
#অন্তর্ভাব "../../core/linux/SDL_evdev.h"
#endif

#অন্তর্ভাব "SDL_vivantevideo.h"
#অন্তর্ভাব "SDL_vivanteplatform.h"
#অন্তর্ভাব "SDL_vivanteopengles.h"
#অন্তর্ভাব "SDL_vivantevulkan.h"

স্থির শূন্য VIVANTE_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

স্থির SDL_VideoDevice *VIVANTE_Create(শূন্য)
{
    SDL_VideoDevice *device;
    SDL_Video_তথ্য *তথ্য;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, আকার(SDL_VideoDevice));
    যদি (!device) {
        ফেরত ফাঁকা;
    }

    // Initialize internal data
    তথ্য = (SDL_Video_তথ্য *)SDL_calloc(1, আকার(SDL_Video_তথ্য));
    যদি (!তথ্য) {
        SDL_free(device);
        ফেরত ফাঁকা;
    }

    device->internal = তথ্য;

    // Setup amount of available displays
    device->অঙ্ক_displays = 0;

    // Set device free function
    device->মুক্ত = VIVANTE_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = VIVANTE_VideoInit;
    device->VideoQuit = VIVANTE_VideoQuit;
    device->CreateSDLWindow = VIVANTE_CreateWindow;
    device->SetWindowTitle = VIVANTE_SetWindowTitle;
    device->SetWindowPosition = VIVANTE_SetWindowPosition;
    device->Set_Window_আকার = VIVANTE_Set_Window_আকার;
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

    ফেরত device;
}

VideoBootStrap VIVANTE_bootstrap = {
    "vivante",
    "Vivante EGL Video Driver",
    VIVANTE_Create,
    ফাঁকা, // no ShowMessageBox implementation
    false
};

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/*****************************************************************************/

স্থির bool VIVANTE_AddVideoDisplays(SDL_VideoDevice *_this)
{
    SDL_Video_তথ্য *videodata = _this->internal;
    SDL_VideoDisplay display;
    SDL_DisplayMode mode;
    SDL_Display_তথ্য *তথ্য;
    পূর্ণসংখ্যা pitch = 0, bpp = 0;
    unsigned long pixels = 0;

    তথ্য = (SDL_Display_তথ্য *)SDL_calloc(1, আকার(SDL_Display_তথ্য));
    যদি (!তথ্য) {
        ফেরত false;
    }

    SDL_zero(mode);
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    তথ্য->native_display = vdkGetDisplay(videodata->vdk_private);

    vdkGetDisplayInfo(তথ্য->native_display, &mode.w, &mode.h, &pixels, &pitch,
                      &bpp);
#অন্যথা
    তথ্য->native_display = videodata->fb_Get_Display_By_সূচক(0);

    videodata->fbGetDisplayInfo(তথ্য->native_display, &mode.w, &mode.h,
                                &pixels, &pitch, &bpp);
#endif // SDL_VIDEO_DRIVER_VIVANTE_VDK

    নির্বাচন (bpp) {
    পূর্বনির্ধারিত: // Is another format used?
    ক্ষেত্র 32:
        mode.format = SDL_PIXELFORMAT_ARGB8888;
        বিরতি;
    ক্ষেত্র 16:
        mode.format = SDL_PIXELFORMAT_RGB565;
        বিরতি;
    }
    // FIXME: How do we query refresh rate?
    mode.refresh_rate = 60.0f;

    SDL_zero(display);
    display.name = VIVANTE_GetDisplayName(_this);
    display.desktop_mode = mode;
    display.internal = তথ্য;
    যদি (SDL_AddVideoDisplay(&display, false) == 0) {
        ফেরত false;
    }
    ফেরত true;
}

bool VIVANTE_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_তথ্য *videodata = _this->internal;

#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    videodata->vdk_private = vdkInitialize();
    যদি (!videodata->vdk_private) {
        ফেরত SDL_SetError("vdkInitialize() failed");
    }
#অন্যথা
    videodata->egl_handle = SDL_LoadObject("libEGL.so.1");
    যদি (!videodata->egl_handle) {
        videodata->egl_handle = SDL_LoadObject("libEGL.so");
        যদি (!videodata->egl_handle) {
            ফেরত false;
        }
    }
#define LOAD_FUNC(TYPE, NAME)                                               \
    videodata->NAME = (TYPE)SDL_LoadFunction(videodata->egl_handle, #NAME); \
    যদি (!videodata->NAME)                                                   \
        ফেরত false;

    LOAD_FUNC(EGLNativeDisplayType (EGLAPIENTRY *)(শূন্য *), fbGetDisplay);
    LOAD_FUNC(EGLNativeDisplayType (EGLAPIENTRY *)(পূর্ণসংখ্যা), fb_Get_Display_By_সূচক);
    LOAD_FUNC(শূন্য (EGLAPIENTRY *)(EGLNativeDisplayType, পূর্ণসংখ্যা *, পূর্ণসংখ্যা *), fbGetDisplayGeometry);
    LOAD_FUNC(শূন্য (EGLAPIENTRY *)(EGLNativeDisplayType, পূর্ণসংখ্যা *, পূর্ণসংখ্যা *, unsigned long *, পূর্ণসংখ্যা *, পূর্ণসংখ্যা *), fbGetDisplayInfo);
    LOAD_FUNC(শূন্য (EGLAPIENTRY *)(EGLNativeDisplayType), fbDestroyDisplay);
    LOAD_FUNC(EGLNativeWindowType (EGLAPIENTRY *)(EGLNativeDisplayType, পূর্ণসংখ্যা, পূর্ণসংখ্যা, পূর্ণসংখ্যা, পূর্ণসংখ্যা), fbCreateWindow);
    LOAD_FUNC(শূন্য (EGLAPIENTRY *)(EGLNativeWindowType, পূর্ণসংখ্যা *, পূর্ণসংখ্যা *, পূর্ণসংখ্যা *, পূর্ণসংখ্যা *), fbGetWindowGeometry);
    LOAD_FUNC(শূন্য (EGLAPIENTRY *)(EGLNativeWindowType, পূর্ণসংখ্যা *, পূর্ণসংখ্যা *, পূর্ণসংখ্যা *, পূর্ণসংখ্যা *, পূর্ণসংখ্যা *, unsigned পূর্ণসংখ্যা *), fbGetWindowInfo);
    LOAD_FUNC(শূন্য (EGLAPIENTRY *)(EGLNativeWindowType), fbDestroyWindow);
#endif

    যদি (!VIVANTE_SetupPlatform(_this)) {
        ফেরত false;
    }

    যদি (!VIVANTE_AddVideoDisplays(_this)) {
        ফেরত false;
    }

    VIVANTE_UpdateDisplayScale(_this);

#ifdef SDL_প্রবেশ_LINUXEV
    যদি (!SDL_EVDEV_Init()) {
        ফেরত false;
    }
#endif

    ফেরত true;
}

শূন্য VIVANTE_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_তথ্য *videodata = _this->internal;

#ifdef SDL_প্রবেশ_LINUXEV
    SDL_EVDEV_Quit();
#endif

    VIVANTE_CleanupPlatform(_this);

#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    যদি (videodata->vdk_private) {
        vdkExit(videodata->vdk_private);
        videodata->vdk_private = ফাঁকা;
    }
#অন্যথা
    যদি (videodata->egl_handle) {
        SDL_UnloadObject(videodata->egl_handle);
        videodata->egl_handle = ফাঁকা;
    }
#endif
}

bool VIVANTE_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_Video_তথ্য *videodata = _this->internal;
    SDL_Display_তথ্য *displaydata;
    SDL_Window_তথ্য *তথ্য;

    displaydata = SDL_Get_Display_Driver_তথ্য(SDL_GetPrimaryDisplay());

    // Allocate window internal data
    তথ্য = (SDL_Window_তথ্য *)SDL_calloc(1, আকার(SDL_Window_তথ্য));
    যদি (!তথ্য) {
        ফেরত false;
    }

    // Setup driver data for this window
    window->internal = তথ্য;

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_VIVANTE_DISPLAY_POINTER, displaydata->native_display);

#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    তথ্য->native_window = vdkCreateWindow(displaydata->native_display, window->x, window->y, window->w, window->h);
#অন্যথা
    তথ্য->native_window = videodata->fbCreateWindow(displaydata->native_display, window->x, window->y, window->w, window->h);
#endif
    যদি (!তথ্য->native_window) {
        ফেরত SDL_SetError("VIVANTE: Can't create native window");
    }
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_VIVANTE_WINDOW_POINTER, তথ্য->native_window);

#ifdef SDL_VIDEO_OPENGL_EGL
    যদি (window->flags & SDL_WINDOW_OPENGL) {
        তথ্য->egl_surface = SDL_EGL_CreateSurface(_this, window, তথ্য->native_window);
        যদি (তথ্য->egl_surface == EGL_NO_SURFACE) {
            ফেরত SDL_SetError("VIVANTE: Can't create EGL surface");
        }
    } অন্যথা {
        তথ্য->egl_surface = EGL_NO_SURFACE;
    }
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_VIVANTE_SURFACE_POINTER, তথ্য->egl_surface);
#endif

    // Window has been successfully created
    ফেরত true;
}

শূন্য VIVANTE_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Video_তথ্য *videodata = _this->internal;
    SDL_Window_তথ্য *তথ্য;

    তথ্য = window->internal;
    যদি (তথ্য) {
#ifdef SDL_VIDEO_OPENGL_EGL
        যদি (তথ্য->egl_surface != EGL_NO_SURFACE) {
            SDL_EGL_DestroySurface(_this, তথ্য->egl_surface);
        }
#endif

        যদি (তথ্য->native_window) {
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
            vdkDestroyWindow(তথ্য->native_window);
#অন্যথা
            videodata->fbDestroyWindow(তথ্য->native_window);
#endif
        }

        SDL_free(তথ্য);
    }
    window->internal = ফাঁকা;
}

শূন্য VIVANTE_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_Window_তথ্য *তথ্য = window->internal;
    vdkSetWindowTitle(তথ্য->native_window, window->title);
#endif
}

bool VIVANTE_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    // FIXME
    ফেরত SDL_Unsupported();
}

শূন্য VIVANTE_Set_Window_আকার(SDL_VideoDevice *_this, SDL_Window *window)
{
    // FIXME
}

শূন্য VIVANTE_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_Window_তথ্য *তথ্য = window->internal;
    vdkShowWindow(তথ্য->native_window);
#endif
    SDL_SetMouseFocus(window);
    SDL_SetKeyboardFocus(window);
}

শূন্য VIVANTE_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_Window_তথ্য *তথ্য = window->internal;
    vdkHideWindow(তথ্য->native_window);
#endif
    SDL_SetMouseFocus(ফাঁকা);
    SDL_SetKeyboardFocus(ফাঁকা);
}

/*****************************************************************************/
// SDL event functions
/*****************************************************************************/
শূন্য VIVANTE_PumpEvents(SDL_VideoDevice *_this)
{
#ifdef SDL_প্রবেশ_LINUXEV
    SDL_EVDEV_Poll();
#endif
}

#endif // SDL_VIDEO_DRIVER_VIVANTE
