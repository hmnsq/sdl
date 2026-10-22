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

#अगर_घोषित SDL_VIDEO_DRIVER_OPENHARMONY

// !!! FIXME: these are defined as "const uint32_t VARNAME = VALUE;" in native_interface_xcomponent.h, which becomes a global variable in _our_ C code! Maybe C++ handles this differently...?
#घोषणा OH_XCOMPONENT_ID_LEN_MAX sdl_ohoswindow_OH_XCOMPONENT_ID_LEN_MAX
#घोषणा OH_MAX_TOUCH_POINTS_संख्या sdl_ohoswindow_OH_MAX_TOUCH_POINTS_संख्या
#समावेश <ace/xcomponent/native_interface_xcomponent.h>

#समावेश "../SDL_sysvideo.h"
#समावेश "../../events/SDL_keyboard_c.h"
#समावेश "../../events/SDL_mouse_c.h"
#समावेश "../../events/SDL_windowevents_c.h"
#समावेश "../../core/openharmony/SDL_openharmony.h"

#समावेश "SDL_openharmonyvideo.h"
#समावेश "SDL_openharmonyevents.h"
#समावेश "SDL_openharmonywindow.h"


// Currently only one window
SDL_Window *OPENHARMONY_Window = शून्य;

bool OPENHARMONY_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_Window_तथ्य *तथ्य;
    bool परिणाम = true;

    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //if (!OPENHARMONY_WaitActiveAndLockActivity()) {
    //    return false;
    //}

    अगर (OPENHARMONY_Window) {
        परिणाम = SDL_SetError("SDL on OpenHarmony (currently) only supports one window");
        जाओ endfunction;
    }

    व्योम *voidxcomp, *native_window;
    SDL_OpenHarmonyGetNativeWindowPointers(&voidxcomp, &native_window);
    OH_NativeXComponent *native_xcomponent = (OH_NativeXComponent *) voidxcomp;
    अगर (!native_xcomponent || !native_window) {
        परिणाम = SDL_SetError("Don't have Native XComponent or Native Window");
        जाओ endfunction;
    }

#अगर 0  // !!! FIXME
    // Set orientation
    Android_JNI_SetOrientation(window->w, window->h, window->flags & SDL_WINDOW_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));
#पूर्ण_अगर

    uint64_t w, h;
    OH_Native_XComponent_Get_XComponent_आकार(native_xcomponent, native_window, &w, &h);

    // Adjust the window data to match the screen
    window->x = 0;
    window->y = 0;
    window->w = (पूर्णांक) w;
    window->h = (पूर्णांक) h;

    // One window, it always has focus
    SDL_SetMouseFocus(window);
    SDL_SetKeyboardFocus(window);

    तथ्य = (SDL_Window_तथ्य *)SDL_calloc(1, माप(*तथ्य));
    अगर (!तथ्य) {
        परिणाम = false;
        जाओ endfunction;
    }

    तथ्य->native_xcomponent = native_xcomponent;
    तथ्य->native_window = native_window;
    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_OPENHARMONY_XCOMPONENT_POINTER, तथ्य->native_xcomponent);
    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_OPENHARMONY_WINDOW_POINTER, तथ्य->native_window);

    /* Do not create EGLSurface for Vulkan window since it will then make the window
       incompatible with vkCreateAndroidSurfaceKHR */
#अगर_घोषित SDL_VIDEO_OPENGL_EGL
    अगर (window->flags & SDL_WINDOW_OPENGL) {
        तथ्य->egl_surface = SDL_EGL_CreateSurface(_this, window, (NativeWindowType)तथ्य->native_window);
        अगर (तथ्य->egl_surface == EGL_NO_SURFACE) {
            SDL_free(तथ्य);
            परिणाम = false;
            जाओ endfunction;
        }
    }
    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_OPENHARMONY_SURFACE_POINTER, तथ्य->egl_surface);
#पूर्ण_अगर

#अगर 0  // !!! FIXME
    SDL_SetWindowSafeAreaInsets(window, Android_Safe_Inset_बायाँ, Android_Safe_Inset_दायाँ, Android_Safe_Inset_शीर्ष, Android_SafeInsetBottom);
#पूर्ण_अगर

    window->internal = तथ्य;
    OPENHARMONY_Window = window;

endfunction:

    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //Android_UnlockActivityMutex();

    वापस परिणाम;
}

व्योम OPENHARMONY_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
#अगर 0  // !!! FIXME
    Android_JNI_SetActivityTitle(window->title);
#पूर्ण_अगर
}

SDL_Fullscreen_परिणाम OPENHARMONY_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    अगर (window == OPENHARMONY_Window) {
        स्थिर bool show_bars = (fullscreen == SDL_FULLSCREEN_OP_LEAVE);
        अगर (!SDL_OpenHarmonyToggleSystemBars(show_bars, show_bars)) {
            वापस SDL_FULLSCREEN_FAILED;
        }
        // !!! FIXME: make sure this causes an XComponent resize event, that we can pick up later.
        वापस SDL_FULLSCREEN_PENDING;
    }
    वापस SDL_FULLSCREEN_FAILED;
}

व्योम OPENHARMONY_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
#अगर 0  // !!! FIXME
    Android_JNI_MinimizeWindow();
#पूर्ण_अगर
}

व्योम OPENHARMONY_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable)
{
#अगर 0  // !!! FIXME
    // Set orientation
    Android_JNI_SetOrientation(window->w, window->h, window->flags & SDL_WINDOW_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));
#पूर्ण_अगर
}

व्योम OPENHARMONY_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //Android_LockActivityMutex();

    अगर (window == OPENHARMONY_Window) {
        OPENHARMONY_Window = शून्य;

        अगर (window->internal) {
            SDL_Window_तथ्य *तथ्य = window->internal;

#अगर_घोषित SDL_VIDEO_OPENGL_EGL
            अगर (तथ्य->egl_surface != EGL_NO_SURFACE) {
                SDL_EGL_DestroySurface(_this, तथ्य->egl_surface);
            }
#पूर्ण_अगर

            // the XComponent and native window live past the SDL_Window; it can be reused for future windows.

            SDL_free(window->internal);
            window->internal = शून्य;
        }
    }

    //Android_UnlockActivityMutex();
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_OPENHARMONY
