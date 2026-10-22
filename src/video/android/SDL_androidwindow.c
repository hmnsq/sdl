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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_ANDROID

#ضمن "../SDL_sysvideo.h"
#ضمن "../../events/SDL_keyboard_c.h"
#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../../events/SDL_windowevents_c.h"
#ضمن "../../core/android/SDL_android.h"

#ضمن "SDL_androidvideo.h"
#ضمن "SDL_androidevents.h"
#ضمن "SDL_androidwindow.h"


// Currently only one window
SDL_کھڑکی *Android_کھڑکی = عدم;

bool Android_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props)
{
    SDL_کھڑکی_انکڑے *انکڑے;
    bool نتیجہ = true;

    إذا (!Android_Wait_سرگرم_And_جندرا_Activity()) {
        أرجع false;
    }

    إذا (Android_کھڑکی) {
        نتیجہ = SDL_سیٹ_Error("Android only supports one window");
        اذهب endfunction;
    }

    // Set orientation
    Android_JNI_سیٹ_Orientation(کھڑکی->w, کھڑکی->h, کھڑکی->flags & SDL_کھڑکی_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));

    // Adjust the window data to match the screen
    کھڑکی->x = 0;
    کھڑکی->y = 0;
    کھڑکی->w = Android_Surface_چوڑائی;
    کھڑکی->h = Android_Surface_اچائی;

    // One window, it always has focus
    SDL_سیٹ_Mouse_Focus(کھڑکی);
    SDL_سیٹ_Keyboard_Focus(کھڑکی);

    انکڑے = (SDL_کھڑکی_انکڑے *)SDL_calloc(1, حجم(*انکڑے));
    إذا (!انکڑے) {
        نتیجہ = false;
        اذهب endfunction;
    }

    انکڑے->native_کھڑکی = Android_JNI_Get_Native_کھڑکی();
    إذا (!انکڑے->native_کھڑکی) {
        SDL_free(انکڑے);
        نتیجہ = SDL_سیٹ_Error("Could not fetch native window");
        اذهب endfunction;
    }
    SDL_سیٹ_اشارہ_گر_Property(SDL_Get_کھڑکی_Properties(کھڑکی), SDL_PROP_کھڑکی_ANDROID_کھڑکی_اشارہ_گر, انکڑے->native_کھڑکی);

    /* Do not create EGLSurface for Vulkan window since it will then make the window
       incompatible with vkCreateAndroidSurfaceKHR */
#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    إذا (کھڑکی->flags & SDL_کھڑکی_OPENGL) {
        انکڑے->egl_surface = SDL_EGL_CreateSurface(_this, کھڑکی, (Native_کھڑکی_Type)انکڑے->native_کھڑکی);

        إذا (انکڑے->egl_surface == EGL_NO_SURFACE) {
            ANative_کھڑکی_release(انکڑے->native_کھڑکی);
            SDL_free(انکڑے);
            نتیجہ = false;
            اذهب endfunction;
        }
    }
    SDL_سیٹ_اشارہ_گر_Property(SDL_Get_کھڑکی_Properties(کھڑکی), SDL_PROP_کھڑکی_ANDROID_SURFACE_اشارہ_گر, انکڑے->egl_surface);
#جے_انت

    SDL_سیٹ_کھڑکی_محفوظ_Area_Insets(کھڑکی, Android_محفوظ_Inset_بایاں, Android_محفوظ_Inset_دایاں, Android_محفوظ_Inset_چوٹی, Android_محفوظ_Inset_Bottom);

    کھڑکی->اندرونی = انکڑے;
    Android_کھڑکی = کھڑکی;

endfunction:

    Android_UnlockActivityMutex();

    أرجع نتیجہ;
}

فراغ Android_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    Android_JNI_سیٹ_Activity_Title(کھڑکی->title);
}

SDL_Fullscreen_نتیجہ Android_سیٹ_کھڑکی_Fullscreen(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    Android_جندرا_Activity_Mutex();

    إذا (کھڑکی == Android_کھڑکی) {
        SDL_کھڑکی_انکڑے *انکڑے;
        صحيح old_w, old_h, new_w, new_h;

        // If the window is being destroyed don't change visible state
        إذا (!کھڑکی->is_destroying) {
            Android_JNI_سیٹ_کھڑکی_Style(fullscreen);
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

        انکڑے = کھڑکی->اندرونی;
        إذا (!انکڑے || !انکڑے->native_کھڑکی) {
            إذا (انکڑے && !انکڑے->native_کھڑکی) {
                SDL_سیٹ_Error("Missing native window");
            }
            اذهب endfunction;
        }

        old_w = کھڑکی->w;
        old_h = کھڑکی->h;

        new_w = ANative_کھڑکی_get_چوڑائی(انکڑے->native_کھڑکی);
        new_h = ANative_کھڑکی_get_اچائی(انکڑے->native_کھڑکی);

        إذا (new_w < 0 || new_h < 0) {
            SDL_سیٹ_Error("ANativeWindow_getWidth/Height() fails");
        }

        إذا (old_w != new_w || old_h != new_h) {
            SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESIZED, new_w, new_h);
        }
    }

endfunction:

    Android_UnlockActivityMutex();

    أرجع SDL_FULLSCREEN_SUCCEEDED;
}

فراغ Android_Minimize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    Android_JNI_Minimize_کھڑکی();
}

فراغ Android_سیٹ_کھڑکی_Resizable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool resizable)
{
    // Set orientation
    Android_JNI_سیٹ_Orientation(کھڑکی->w, کھڑکی->h, کھڑکی->flags & SDL_کھڑکی_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));
}

فراغ Android_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    Android_جندرا_Activity_Mutex();

    إذا (کھڑکی == Android_کھڑکی) {
        Android_کھڑکی = عدم;

        إذا (کھڑکی->اندرونی) {
            SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;

#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
            إذا (انکڑے->egl_surface != EGL_NO_SURFACE) {
                SDL_EGL_DestroySurface(_this, انکڑے->egl_surface);
            }
#جے_انت

            إذا (انکڑے->native_کھڑکی) {
                ANative_کھڑکی_release(انکڑے->native_کھڑکی);
            }
            SDL_free(کھڑکی->اندرونی);
            کھڑکی->اندرونی = عدم;
        }
    }

    Android_UnlockActivityMutex();
}

#جے_انت // SDL_VIDEO_DRIVER_ANDROID
