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

#ifdef SDL_VIDEO_DRIVER_OPENHARMONY

// !!! FIXME: these are defined as "const uint32_t VARNAME = VALUE;" in native_interface_xcomponent.h, which becomes a global variable in _our_ C code! Maybe C++ handles this differently...?
#define OH_XCOMPONENT_ID_LEN_MAX sdl_ohoswindow_OH_XCOMPONENT_ID_LEN_MAX
#define OH_MAX_TOUCH_POINTS_সংখ্যা sdl_ohoswindow_OH_MAX_TOUCH_POINTS_সংখ্যা
#অন্তর্ভাব <ace/xcomponent/native_interface_xcomponent.h>

#অন্তর্ভাব "../SDL_sysvideo.h"
#অন্তর্ভাব "../../events/SDL_keyboard_c.h"
#অন্তর্ভাব "../../events/SDL_mouse_c.h"
#অন্তর্ভাব "../../events/SDL_windowevents_c.h"
#অন্তর্ভাব "../../core/openharmony/SDL_openharmony.h"

#অন্তর্ভাব "SDL_openharmonyvideo.h"
#অন্তর্ভাব "SDL_openharmonyevents.h"
#অন্তর্ভাব "SDL_openharmonywindow.h"


// Currently only one window
SDL_Window *OPENHARMONY_Window = ফাঁকা;

bool OPENHARMONY_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_Window_তথ্য *তথ্য;
    bool ফলাফল = true;

    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //if (!OPENHARMONY_WaitActiveAndLockActivity()) {
    //    return false;
    //}

    যদি (OPENHARMONY_Window) {
        ফলাফল = SDL_SetError("SDL on OpenHarmony (currently) only supports one window");
        যাও endfunction;
    }

    শূন্য *voidxcomp, *native_window;
    SDL_OpenHarmonyGetNativeWindowPointers(&voidxcomp, &native_window);
    OH_NativeXComponent *native_xcomponent = (OH_NativeXComponent *) voidxcomp;
    যদি (!native_xcomponent || !native_window) {
        ফলাফল = SDL_SetError("Don't have Native XComponent or Native Window");
        যাও endfunction;
    }

#যদি 0  // !!! FIXME
    // Set orientation
    Android_JNI_SetOrientation(window->w, window->h, window->flags & SDL_WINDOW_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));
#endif

    uint64_t w, h;
    OH_Native_XComponent_Get_XComponent_আকার(native_xcomponent, native_window, &w, &h);

    // Adjust the window data to match the screen
    window->x = 0;
    window->y = 0;
    window->w = (পূর্ণসংখ্যা) w;
    window->h = (পূর্ণসংখ্যা) h;

    // One window, it always has focus
    SDL_SetMouseFocus(window);
    SDL_SetKeyboardFocus(window);

    তথ্য = (SDL_Window_তথ্য *)SDL_calloc(1, আকার(*তথ্য));
    যদি (!তথ্য) {
        ফলাফল = false;
        যাও endfunction;
    }

    তথ্য->native_xcomponent = native_xcomponent;
    তথ্য->native_window = native_window;
    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_OPENHARMONY_XCOMPONENT_POINTER, তথ্য->native_xcomponent);
    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_OPENHARMONY_WINDOW_POINTER, তথ্য->native_window);

    /* Do not create EGLSurface for Vulkan window since it will then make the window
       incompatible with vkCreateAndroidSurfaceKHR */
#ifdef SDL_VIDEO_OPENGL_EGL
    যদি (window->flags & SDL_WINDOW_OPENGL) {
        তথ্য->egl_surface = SDL_EGL_CreateSurface(_this, window, (NativeWindowType)তথ্য->native_window);
        যদি (তথ্য->egl_surface == EGL_NO_SURFACE) {
            SDL_free(তথ্য);
            ফলাফল = false;
            যাও endfunction;
        }
    }
    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_OPENHARMONY_SURFACE_POINTER, তথ্য->egl_surface);
#endif

#যদি 0  // !!! FIXME
    SDL_SetWindowSafeAreaInsets(window, Android_Safe_Inset_বাম, Android_Safe_Inset_ডান, Android_Safe_Inset_শীর্ষ, Android_SafeInsetBottom);
#endif

    window->internal = তথ্য;
    OPENHARMONY_Window = window;

endfunction:

    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //Android_UnlockActivityMutex();

    ফেরত ফলাফল;
}

শূন্য OPENHARMONY_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
#যদি 0  // !!! FIXME
    Android_JNI_SetActivityTitle(window->title);
#endif
}

SDL_Fullscreen_ফলাফল OPENHARMONY_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    যদি (window == OPENHARMONY_Window) {
        ধ্রুবক bool show_bars = (fullscreen == SDL_FULLSCREEN_OP_LEAVE);
        যদি (!SDL_OpenHarmonyToggleSystemBars(show_bars, show_bars)) {
            ফেরত SDL_FULLSCREEN_FAILED;
        }
        // !!! FIXME: make sure this causes an XComponent resize event, that we can pick up later.
        ফেরত SDL_FULLSCREEN_PENDING;
    }
    ফেরত SDL_FULLSCREEN_FAILED;
}

শূন্য OPENHARMONY_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
#যদি 0  // !!! FIXME
    Android_JNI_MinimizeWindow();
#endif
}

শূন্য OPENHARMONY_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable)
{
#যদি 0  // !!! FIXME
    // Set orientation
    Android_JNI_SetOrientation(window->w, window->h, window->flags & SDL_WINDOW_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));
#endif
}

শূন্য OPENHARMONY_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //Android_LockActivityMutex();

    যদি (window == OPENHARMONY_Window) {
        OPENHARMONY_Window = ফাঁকা;

        যদি (window->internal) {
            SDL_Window_তথ্য *তথ্য = window->internal;

#ifdef SDL_VIDEO_OPENGL_EGL
            যদি (তথ্য->egl_surface != EGL_NO_SURFACE) {
                SDL_EGL_DestroySurface(_this, তথ্য->egl_surface);
            }
#endif

            // the XComponent and native window live past the SDL_Window; it can be reused for future windows.

            SDL_free(window->internal);
            window->internal = ফাঁকা;
        }
    }

    //Android_UnlockActivityMutex();
}

#endif // SDL_VIDEO_DRIVER_OPENHARMONY
