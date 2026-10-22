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

#ifdef SDL_VIDEO_DRIVER_ANDROID

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_keyboard_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_windowevents_c.h"
#ಅನ್ತರ್ಭಾವ "../../core/android/SDL_android.h"

#ಅನ್ತರ್ಭಾವ "SDL_androidvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_androidevents.h"
#ಅನ್ತರ್ಭಾವ "SDL_androidwindow.h"


// Currently only one window
SDL_Window *Android_Window = ರಿಕ್ತ;

bool Android_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_WindowData *data;
    bool result = true;

    ಯದಿ (!Android_WaitActiveAndLockActivity()) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಯದಿ (Android_Window) {
        result = SDL_SetError("Android only supports one window");
        ಗಚ್ಛ endfunction;
    }

    // Set orientation
    Android_JNI_SetOrientation(window->w, window->h, window->flags & SDL_WINDOW_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));

    // Adjust the window data to match the screen
    window->x = 0;
    window->y = 0;
    window->w = Android_SurfaceWidth;
    window->h = Android_SurfaceHeight;

    // One window, it always has focus
    SDL_SetMouseFocus(window);
    SDL_SetKeyboardFocus(window);

    data = (SDL_WindowData *)SDL_calloc(1, ಪರಿಮಾಣ(*data));
    ಯದಿ (!data) {
        result = false;
        ಗಚ್ಛ endfunction;
    }

    data->native_window = Android_JNI_GetNativeWindow();
    ಯದಿ (!data->native_window) {
        SDL_free(data);
        result = SDL_SetError("Could not fetch native window");
        ಗಚ್ಛ endfunction;
    }
    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_ANDROID_WINDOW_POINTER, data->native_window);

    /* Do not create EGLSurface for Vulkan window since it will then make the window
       incompatible with vkCreateAndroidSurfaceKHR */
#ifdef SDL_VIDEO_OPENGL_EGL
    ಯದಿ (window->flags & SDL_WINDOW_OPENGL) {
        data->egl_surface = SDL_EGL_CreateSurface(_this, window, (NativeWindowType)data->native_window);

        ಯದಿ (data->egl_surface == EGL_NO_SURFACE) {
            ANativeWindow_release(data->native_window);
            SDL_free(data);
            result = false;
            ಗಚ್ಛ endfunction;
        }
    }
    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_ANDROID_SURFACE_POINTER, data->egl_surface);
#endif

    SDL_SetWindowSafeAreaInsets(window, Android_Safe_Inset_ಎಡ, Android_Safe_Inset_ಬಲ, Android_Safe_Inset_ತುದಿ, Android_SafeInsetBottom);

    window->internal = data;
    Android_Window = window;

endfunction:

    Android_UnlockActivityMutex();

    ಪ್ರತ್ಯಾಗಮ result;
}

ಶೂನ್ಯ Android_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
    Android_JNI_SetActivityTitle(window->title);
}

SDL_FullscreenResult Android_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    Android_LockActivityMutex();

    ಯದಿ (window == Android_Window) {
        SDL_WindowData *data;
        ಪೂರ್ಣಾಙ್ಕ old_w, old_h, new_w, new_h;

        // If the window is being destroyed don't change visible state
        ಯದಿ (!window->is_destroying) {
            Android_JNI_SetWindowStyle(fullscreen);
        }

        /* Ensure our size matches reality after we've executed the window style change.
         *
         * It is possible that we've set width and height to the full-size display, but on
         * Samsung DeX or Chromebooks or other windowed Android environments, our window may
         * still not be the full display size.
         */
        ಯದಿ (!SDL_IsDeXMode() && !SDL_IsChromebook()) {
            ಗಚ್ಛ endfunction;
        }

        data = window->internal;
        ಯದಿ (!data || !data->native_window) {
            ಯದಿ (data && !data->native_window) {
                SDL_SetError("Missing native window");
            }
            ಗಚ್ಛ endfunction;
        }

        old_w = window->w;
        old_h = window->h;

        new_w = ANativeWindow_getWidth(data->native_window);
        new_h = ANativeWindow_getHeight(data->native_window);

        ಯದಿ (new_w < 0 || new_h < 0) {
            SDL_SetError("ANativeWindow_getWidth/Height() fails");
        }

        ಯದಿ (old_w != new_w || old_h != new_h) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, new_w, new_h);
        }
    }

endfunction:

    Android_UnlockActivityMutex();

    ಪ್ರತ್ಯಾಗಮ SDL_FULLSCREEN_SUCCEEDED;
}

ಶೂನ್ಯ Android_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    Android_JNI_MinimizeWindow();
}

ಶೂನ್ಯ Android_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable)
{
    // Set orientation
    Android_JNI_SetOrientation(window->w, window->h, window->flags & SDL_WINDOW_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));
}

ಶೂನ್ಯ Android_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    Android_LockActivityMutex();

    ಯದಿ (window == Android_Window) {
        Android_Window = ರಿಕ್ತ;

        ಯದಿ (window->internal) {
            SDL_WindowData *data = window->internal;

#ifdef SDL_VIDEO_OPENGL_EGL
            ಯದಿ (data->egl_surface != EGL_NO_SURFACE) {
                SDL_EGL_DestroySurface(_this, data->egl_surface);
            }
#endif

            ಯದಿ (data->native_window) {
                ANativeWindow_release(data->native_window);
            }
            SDL_free(window->internal);
            window->internal = ರಿಕ್ತ;
        }
    }

    Android_UnlockActivityMutex();
}

#endif // SDL_VIDEO_DRIVER_ANDROID
