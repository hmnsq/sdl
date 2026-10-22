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
#ضمن "SDL_internal.h"

#که_تعریف_شوی SDL_VIDEO_DRIVER_ANDROID

#ضمن "../SDL_sysvideo.h"
#ضمن "../../events/SDL_keyboard_c.h"
#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../../events/SDL_windowevents_c.h"
#ضمن "../../core/android/SDL_android.h"

#ضمن "SDL_androidvideo.h"
#ضمن "SDL_androidevents.h"
#ضمن "SDL_androidwindow.h"


// Currently only one window
SDL_کړکۍ *Android_کړکۍ = عدم;

bool Android_Create_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID create_props)
{
    SDL_کړکۍ_معلومات *معلومات;
    bool پایله = true;

    إذا (!Android_Wait_فعال_And_قلف_Activity()) {
        أرجع false;
    }

    إذا (Android_کړکۍ) {
        پایله = SDL_سېټ_Error("Android only supports one window");
        اذهب endfunction;
    }

    // Set orientation
    Android_JNI_سېټ_Orientation(کړکۍ->w, کړکۍ->h, کړکۍ->flags & SDL_کړکۍ_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));

    // Adjust the window data to match the screen
    کړکۍ->x = 0;
    کړکۍ->y = 0;
    کړکۍ->w = Android_Surface_پلنوالی;
    کړکۍ->h = Android_Surface_لوړوالی;

    // One window, it always has focus
    SDL_سېټ_Mouse_Focus(کړکۍ);
    SDL_سېټ_Keyboard_Focus(کړکۍ);

    معلومات = (SDL_کړکۍ_معلومات *)SDL_calloc(1, حجم(*معلومات));
    إذا (!معلومات) {
        پایله = false;
        اذهب endfunction;
    }

    معلومات->native_کړکۍ = Android_JNI_Get_Native_کړکۍ();
    إذا (!معلومات->native_کړکۍ) {
        SDL_free(معلومات);
        پایله = SDL_سېټ_Error("Could not fetch native window");
        اذهب endfunction;
    }
    SDL_سېټ_اشاره_ګر_Property(SDL_Get_کړکۍ_Properties(کړکۍ), SDL_PROP_کړکۍ_ANDROID_کړکۍ_اشاره_ګر, معلومات->native_کړکۍ);

    /* Do not create EGLSurface for Vulkan window since it will then make the window
       incompatible with vkCreateAndroidSurfaceKHR */
#که_تعریف_شوی SDL_VIDEO_OPENGL_EGL
    إذا (کړکۍ->flags & SDL_کړکۍ_OPENGL) {
        معلومات->egl_surface = SDL_EGL_CreateSurface(_this, کړکۍ, (Native_کړکۍ_Type)معلومات->native_کړکۍ);

        إذا (معلومات->egl_surface == EGL_NO_SURFACE) {
            ANative_کړکۍ_release(معلومات->native_کړکۍ);
            SDL_free(معلومات);
            پایله = false;
            اذهب endfunction;
        }
    }
    SDL_سېټ_اشاره_ګر_Property(SDL_Get_کړکۍ_Properties(کړکۍ), SDL_PROP_کړکۍ_ANDROID_SURFACE_اشاره_ګر, معلومات->egl_surface);
#د_که_پای

    SDL_سېټ_کړکۍ_خوندي_Area_Insets(کړکۍ, Android_خوندي_Inset_کیڼ, Android_خوندي_Inset_ښی, Android_خوندي_Inset_سر, Android_خوندي_Inset_Bottom);

    کړکۍ->دننی = معلومات;
    Android_کړکۍ = کړکۍ;

endfunction:

    Android_UnlockActivityMutex();

    أرجع پایله;
}

فراغ Android_سېټ_کړکۍ_Title(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    Android_JNI_سېټ_Activity_Title(کړکۍ->title);
}

SDL_Fullscreen_پایله Android_سېټ_کړکۍ_Fullscreen(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    Android_قلف_Activity_Mutex();

    إذا (کړکۍ == Android_کړکۍ) {
        SDL_کړکۍ_معلومات *معلومات;
        صحيح old_w, old_h, new_w, new_h;

        // If the window is being destroyed don't change visible state
        إذا (!کړکۍ->is_destroying) {
            Android_JNI_سېټ_کړکۍ_Style(fullscreen);
        }

        /* Ensure our size matches reality after we've executed the window style change.
         *
         * It is possible that we've set width and height to the full-size display, but on
         * Samsung DeX or Chromebooks or other windowed Android environments, our window may
         * still not be the full display size.
         */
        إذا (!SDL_IsDeXMode() && !SDL_IsChromebook()) {
            اذهب endfunction;
        }

        معلومات = کړکۍ->دننی;
        إذا (!معلومات || !معلومات->native_کړکۍ) {
            إذا (معلومات && !معلومات->native_کړکۍ) {
                SDL_سېټ_Error("Missing native window");
            }
            اذهب endfunction;
        }

        old_w = کړکۍ->w;
        old_h = کړکۍ->h;

        new_w = ANative_کړکۍ_get_پلنوالی(معلومات->native_کړکۍ);
        new_h = ANative_کړکۍ_get_لوړوالی(معلومات->native_کړکۍ);

        إذا (new_w < 0 || new_h < 0) {
            SDL_سېټ_Error("ANativeWindow_getWidth/Height() fails");
        }

        إذا (old_w != new_w || old_h != new_h) {
            SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_RESIZED, new_w, new_h);
        }
    }

endfunction:

    Android_UnlockActivityMutex();

    أرجع SDL_FULLSCREEN_SUCCEEDED;
}

فراغ Android_Minimize_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    Android_JNI_Minimize_کړکۍ();
}

فراغ Android_سېټ_کړکۍ_Resizable(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool resizable)
{
    // Set orientation
    Android_JNI_سېټ_Orientation(کړکۍ->w, کړکۍ->h, کړکۍ->flags & SDL_کړکۍ_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));
}

فراغ Android_Destroy_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    Android_قلف_Activity_Mutex();

    إذا (کړکۍ == Android_کړکۍ) {
        Android_کړکۍ = عدم;

        إذا (کړکۍ->دننی) {
            SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;

#که_تعریف_شوی SDL_VIDEO_OPENGL_EGL
            إذا (معلومات->egl_surface != EGL_NO_SURFACE) {
                SDL_EGL_DestroySurface(_this, معلومات->egl_surface);
            }
#د_که_پای

            إذا (معلومات->native_کړکۍ) {
                ANative_کړکۍ_release(معلومات->native_کړکۍ);
            }
            SDL_free(کړکۍ->دننی);
            کړکۍ->دننی = عدم;
        }
    }

    Android_UnlockActivityMutex();
}

#د_که_پای // SDL_VIDEO_DRIVER_ANDROID
