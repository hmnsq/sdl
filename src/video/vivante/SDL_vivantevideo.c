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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_VIVANTE

// SDL internals
#समावेश "../SDL_sysvideo.h"
#समावेश "../../events/SDL_events_c.h"

#अगर_घोषित SDL_निवेश_LINUXEV
#समावेश "../../core/linux/SDL_evdev.h"
#पूर्ण_अगर

#समावेश "SDL_vivantevideo.h"
#समावेश "SDL_vivanteplatform.h"
#समावेश "SDL_vivanteopengles.h"
#समावेश "SDL_vivantevulkan.h"

अटल व्योम VIVANTE_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

अटल SDL_VideoDevice *VIVANTE_Create(व्योम)
{
    SDL_VideoDevice *device;
    SDL_Video_तथ्य *तथ्य;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, माप(SDL_VideoDevice));
    अगर (!device) {
        वापस शून्य;
    }

    // Initialize internal data
    तथ्य = (SDL_Video_तथ्य *)SDL_calloc(1, माप(SDL_Video_तथ्य));
    अगर (!तथ्य) {
        SDL_free(device);
        वापस शून्य;
    }

    device->internal = तथ्य;

    // Setup amount of available displays
    device->अंक_displays = 0;

    // Set device free function
    device->मुक्त = VIVANTE_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = VIVANTE_VideoInit;
    device->VideoQuit = VIVANTE_VideoQuit;
    device->CreateSDLWindow = VIVANTE_CreateWindow;
    device->SetWindowTitle = VIVANTE_SetWindowTitle;
    device->SetWindowPosition = VIVANTE_SetWindowPosition;
    device->Set_Window_आकार = VIVANTE_Set_Window_आकार;
    device->ShowWindow = VIVANTE_ShowWindow;
    device->HideWindow = VIVANTE_HideWindow;
    device->DestroyWindow = VIVANTE_DestroyWindow;

#अगर_घोषित SDL_VIDEO_OPENGL_EGL
    device->GL_LoadLibrary = VIVANTE_GLES_LoadLibrary;
    device->GL_GetProcAddress = VIVANTE_GLES_GetProcAddress;
    device->GL_UnloadLibrary = VIVANTE_GLES_UnloadLibrary;
    device->GL_CreateContext = VIVANTE_GLES_CreateContext;
    device->GL_MakeCurrent = VIVANTE_GLES_MakeCurrent;
    device->GL_SetSwapInterval = VIVANTE_GLES_SetSwapInterval;
    device->GL_GetSwapInterval = VIVANTE_GLES_GetSwapInterval;
    device->GL_SwapWindow = VIVANTE_GLES_SwapWindow;
    device->GL_DestroyContext = VIVANTE_GLES_DestroyContext;
#पूर्ण_अगर

#अगर_घोषित SDL_VIDEO_VULKAN
    device->Vulkan_LoadLibrary = VIVANTE_Vulkan_LoadLibrary;
    device->Vulkan_UnloadLibrary = VIVANTE_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = VIVANTE_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = VIVANTE_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = VIVANTE_Vulkan_DestroySurface;
#पूर्ण_अगर

    device->PumpEvents = VIVANTE_PumpEvents;

    वापस device;
}

VideoBootStrap VIVANTE_bootstrap = {
    "vivante",
    "Vivante EGL Video Driver",
    VIVANTE_Create,
    शून्य, // no ShowMessageBox implementation
    false
};

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/*****************************************************************************/

अटल bool VIVANTE_AddVideoDisplays(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *videodata = _this->internal;
    SDL_VideoDisplay display;
    SDL_DisplayMode mode;
    SDL_Display_तथ्य *तथ्य;
    पूर्णांक pitch = 0, bpp = 0;
    अचिन्हित दीर्घ pixels = 0;

    तथ्य = (SDL_Display_तथ्य *)SDL_calloc(1, माप(SDL_Display_तथ्य));
    अगर (!तथ्य) {
        वापस false;
    }

    SDL_zero(mode);
#अगर_घोषित SDL_VIDEO_DRIVER_VIVANTE_VDK
    तथ्य->native_display = vdkGetDisplay(videodata->vdk_private);

    vdkGetDisplayInfo(तथ्य->native_display, &mode.w, &mode.h, &pixels, &pitch,
                      &bpp);
#अन्यथा
    तथ्य->native_display = videodata->fb_Get_Display_By_सूचकांक(0);

    videodata->fbGetDisplayInfo(तथ्य->native_display, &mode.w, &mode.h,
                                &pixels, &pitch, &bpp);
#पूर्ण_अगर // SDL_VIDEO_DRIVER_VIVANTE_VDK

    चयन (bpp) {
    शेष: // Is another format used?
    हाल 32:
        mode.format = SDL_PIXELFORMAT_ARGB8888;
        अवरोध;
    हाल 16:
        mode.format = SDL_PIXELFORMAT_RGB565;
        अवरोध;
    }
    // FIXME: How do we query refresh rate?
    mode.refresh_rate = 60.0f;

    SDL_zero(display);
    display.name = VIVANTE_GetDisplayName(_this);
    display.desktop_mode = mode;
    display.internal = तथ्य;
    अगर (SDL_AddVideoDisplay(&display, false) == 0) {
        वापस false;
    }
    वापस true;
}

bool VIVANTE_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *videodata = _this->internal;

#अगर_घोषित SDL_VIDEO_DRIVER_VIVANTE_VDK
    videodata->vdk_private = vdkInitialize();
    अगर (!videodata->vdk_private) {
        वापस SDL_SetError("vdkInitialize() failed");
    }
#अन्यथा
    videodata->egl_handle = SDL_LoadObject("libEGL.so.1");
    अगर (!videodata->egl_handle) {
        videodata->egl_handle = SDL_LoadObject("libEGL.so");
        अगर (!videodata->egl_handle) {
            वापस false;
        }
    }
#घोषणा LOAD_FUNC(TYPE, NAME)                                               \
    videodata->NAME = (TYPE)SDL_LoadFunction(videodata->egl_handle, #NAME); \
    अगर (!videodata->NAME)                                                   \
        वापस false;

    LOAD_FUNC(EGLNativeDisplayType (EGLAPIENTRY *)(व्योम *), fbGetDisplay);
    LOAD_FUNC(EGLNativeDisplayType (EGLAPIENTRY *)(पूर्णांक), fb_Get_Display_By_सूचकांक);
    LOAD_FUNC(व्योम (EGLAPIENTRY *)(EGLNativeDisplayType, पूर्णांक *, पूर्णांक *), fbGetDisplayGeometry);
    LOAD_FUNC(व्योम (EGLAPIENTRY *)(EGLNativeDisplayType, पूर्णांक *, पूर्णांक *, अचिन्हित दीर्घ *, पूर्णांक *, पूर्णांक *), fbGetDisplayInfo);
    LOAD_FUNC(व्योम (EGLAPIENTRY *)(EGLNativeDisplayType), fbDestroyDisplay);
    LOAD_FUNC(EGLNativeWindowType (EGLAPIENTRY *)(EGLNativeDisplayType, पूर्णांक, पूर्णांक, पूर्णांक, पूर्णांक), fbCreateWindow);
    LOAD_FUNC(व्योम (EGLAPIENTRY *)(EGLNativeWindowType, पूर्णांक *, पूर्णांक *, पूर्णांक *, पूर्णांक *), fbGetWindowGeometry);
    LOAD_FUNC(व्योम (EGLAPIENTRY *)(EGLNativeWindowType, पूर्णांक *, पूर्णांक *, पूर्णांक *, पूर्णांक *, पूर्णांक *, अचिन्हित पूर्णांक *), fbGetWindowInfo);
    LOAD_FUNC(व्योम (EGLAPIENTRY *)(EGLNativeWindowType), fbDestroyWindow);
#पूर्ण_अगर

    अगर (!VIVANTE_SetupPlatform(_this)) {
        वापस false;
    }

    अगर (!VIVANTE_AddVideoDisplays(_this)) {
        वापस false;
    }

    VIVANTE_UpdateDisplayScale(_this);

#अगर_घोषित SDL_निवेश_LINUXEV
    अगर (!SDL_EVDEV_Init()) {
        वापस false;
    }
#पूर्ण_अगर

    वापस true;
}

व्योम VIVANTE_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *videodata = _this->internal;

#अगर_घोषित SDL_निवेश_LINUXEV
    SDL_EVDEV_Quit();
#पूर्ण_अगर

    VIVANTE_CleanupPlatform(_this);

#अगर_घोषित SDL_VIDEO_DRIVER_VIVANTE_VDK
    अगर (videodata->vdk_private) {
        vdkExit(videodata->vdk_private);
        videodata->vdk_private = शून्य;
    }
#अन्यथा
    अगर (videodata->egl_handle) {
        SDL_UnloadObject(videodata->egl_handle);
        videodata->egl_handle = शून्य;
    }
#पूर्ण_अगर
}

bool VIVANTE_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_Video_तथ्य *videodata = _this->internal;
    SDL_Display_तथ्य *displaydata;
    SDL_Window_तथ्य *तथ्य;

    displaydata = SDL_Get_Display_Driver_तथ्य(SDL_GetPrimaryDisplay());

    // Allocate window internal data
    तथ्य = (SDL_Window_तथ्य *)SDL_calloc(1, माप(SDL_Window_तथ्य));
    अगर (!तथ्य) {
        वापस false;
    }

    // Setup driver data for this window
    window->internal = तथ्य;

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_VIVANTE_DISPLAY_POINTER, displaydata->native_display);

#अगर_घोषित SDL_VIDEO_DRIVER_VIVANTE_VDK
    तथ्य->native_window = vdkCreateWindow(displaydata->native_display, window->x, window->y, window->w, window->h);
#अन्यथा
    तथ्य->native_window = videodata->fbCreateWindow(displaydata->native_display, window->x, window->y, window->w, window->h);
#पूर्ण_अगर
    अगर (!तथ्य->native_window) {
        वापस SDL_SetError("VIVANTE: Can't create native window");
    }
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_VIVANTE_WINDOW_POINTER, तथ्य->native_window);

#अगर_घोषित SDL_VIDEO_OPENGL_EGL
    अगर (window->flags & SDL_WINDOW_OPENGL) {
        तथ्य->egl_surface = SDL_EGL_CreateSurface(_this, window, तथ्य->native_window);
        अगर (तथ्य->egl_surface == EGL_NO_SURFACE) {
            वापस SDL_SetError("VIVANTE: Can't create EGL surface");
        }
    } अन्यथा {
        तथ्य->egl_surface = EGL_NO_SURFACE;
    }
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_VIVANTE_SURFACE_POINTER, तथ्य->egl_surface);
#पूर्ण_अगर

    // Window has been successfully created
    वापस true;
}

व्योम VIVANTE_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Video_तथ्य *videodata = _this->internal;
    SDL_Window_तथ्य *तथ्य;

    तथ्य = window->internal;
    अगर (तथ्य) {
#अगर_घोषित SDL_VIDEO_OPENGL_EGL
        अगर (तथ्य->egl_surface != EGL_NO_SURFACE) {
            SDL_EGL_DestroySurface(_this, तथ्य->egl_surface);
        }
#पूर्ण_अगर

        अगर (तथ्य->native_window) {
#अगर_घोषित SDL_VIDEO_DRIVER_VIVANTE_VDK
            vdkDestroyWindow(तथ्य->native_window);
#अन्यथा
            videodata->fbDestroyWindow(तथ्य->native_window);
#पूर्ण_अगर
        }

        SDL_free(तथ्य);
    }
    window->internal = शून्य;
}

व्योम VIVANTE_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
#अगर_घोषित SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_Window_तथ्य *तथ्य = window->internal;
    vdkSetWindowTitle(तथ्य->native_window, window->title);
#पूर्ण_अगर
}

bool VIVANTE_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    // FIXME
    वापस SDL_Unsupported();
}

व्योम VIVANTE_Set_Window_आकार(SDL_VideoDevice *_this, SDL_Window *window)
{
    // FIXME
}

व्योम VIVANTE_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
#अगर_घोषित SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_Window_तथ्य *तथ्य = window->internal;
    vdkShowWindow(तथ्य->native_window);
#पूर्ण_अगर
    SDL_SetMouseFocus(window);
    SDL_SetKeyboardFocus(window);
}

व्योम VIVANTE_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
#अगर_घोषित SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_Window_तथ्य *तथ्य = window->internal;
    vdkHideWindow(तथ्य->native_window);
#पूर्ण_अगर
    SDL_SetMouseFocus(शून्य);
    SDL_SetKeyboardFocus(शून्य);
}

/*****************************************************************************/
// SDL event functions
/*****************************************************************************/
व्योम VIVANTE_PumpEvents(SDL_VideoDevice *_this)
{
#अगर_घोषित SDL_निवेश_LINUXEV
    SDL_EVDEV_Poll();
#पूर्ण_अगर
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_VIVANTE
