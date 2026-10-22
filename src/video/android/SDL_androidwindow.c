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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_ANDROID

#ضمن "../SDL_sysvideo.h"
#ضمن "../../events/SDL_keyboard_c.h"
#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../../events/SDL_windowevents_c.h"
#ضمن "../../core/android/SDL_android.h"

#ضمن "SDL_androidvideo.h"
#ضمن "SDL_androidevents.h"
#ضمن "SDL_androidwindow.h"


// Currently only one window
SDL_پنجره *Android_پنجره = عدم;

bool Android_Create_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID create_props)
{
    SDL_پنجره_داده *داده;
    bool نتیجه = true;

    إذا (!Android_Wait_فعال_And_قفل_Activity()) {
        أرجع false;
    }

    إذا (Android_پنجره) {
        نتیجه = SDL_مجموعه_Error("Android only supports one window");
        اذهب endfunction;
    }

    // Set orientation
    Android_JNI_مجموعه_Orientation(پنجره->w, پنجره->h, پنجره->flags & SDL_پنجره_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));

    // Adjust the window data to match the screen
    پنجره->x = 0;
    پنجره->y = 0;
    پنجره->w = Android_Surface_عرض;
    پنجره->h = Android_Surface_ارتفاع;

    // One window, it always has focus
    SDL_مجموعه_Mouse_Focus(پنجره);
    SDL_مجموعه_Keyboard_Focus(پنجره);

    داده = (SDL_پنجره_داده *)SDL_calloc(1, حجم(*داده));
    إذا (!داده) {
        نتیجه = false;
        اذهب endfunction;
    }

    داده->native_پنجره = Android_JNI_Get_Native_پنجره();
    إذا (!داده->native_پنجره) {
        SDL_free(داده);
        نتیجه = SDL_مجموعه_Error("Could not fetch native window");
        اذهب endfunction;
    }
    SDL_مجموعه_اشاره_گر_Property(SDL_Get_پنجره_Properties(پنجره), SDL_PROP_پنجره_ANDROID_پنجره_اشاره_گر, داده->native_پنجره);

    /* Do not create EGLSurface for Vulkan window since it will then make the window
       incompatible with vkCreateAndroidSurfaceKHR */
#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
    إذا (پنجره->flags & SDL_پنجره_OPENGL) {
        داده->egl_surface = SDL_EGL_CreateSurface(_this, پنجره, (Native_پنجره_Type)داده->native_پنجره);

        إذا (داده->egl_surface == EGL_NO_SURFACE) {
            ANative_پنجره_release(داده->native_پنجره);
            SDL_free(داده);
            نتیجه = false;
            اذهب endfunction;
        }
    }
    SDL_مجموعه_اشاره_گر_Property(SDL_Get_پنجره_Properties(پنجره), SDL_PROP_پنجره_ANDROID_SURFACE_اشاره_گر, داده->egl_surface);
#پایان_اگر

    SDL_مجموعه_پنجره_امن_Area_Insets(پنجره, Android_امن_Inset_چپ, Android_امن_Inset_راست, Android_امن_Inset_بالاترین, Android_امن_Inset_Bottom);

    پنجره->داخلی = داده;
    Android_پنجره = پنجره;

endfunction:

    Android_UnlockActivityMutex();

    أرجع نتیجه;
}

فراغ Android_مجموعه_پنجره_Title(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    Android_JNI_مجموعه_Activity_Title(پنجره->title);
}

SDL_Fullscreen_نتیجه Android_مجموعه_پنجره_Fullscreen(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    Android_قفل_Activity_Mutex();

    إذا (پنجره == Android_پنجره) {
        SDL_پنجره_داده *داده;
        صحيح old_w, old_h, new_w, new_h;

        // If the window is being destroyed don't change visible state
        إذا (!پنجره->is_destroying) {
            Android_JNI_مجموعه_پنجره_Style(fullscreen);
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

        داده = پنجره->داخلی;
        إذا (!داده || !داده->native_پنجره) {
            إذا (داده && !داده->native_پنجره) {
                SDL_مجموعه_Error("Missing native window");
            }
            اذهب endfunction;
        }

        old_w = پنجره->w;
        old_h = پنجره->h;

        new_w = ANative_پنجره_get_عرض(داده->native_پنجره);
        new_h = ANative_پنجره_get_ارتفاع(داده->native_پنجره);

        إذا (new_w < 0 || new_h < 0) {
            SDL_مجموعه_Error("ANativeWindow_getWidth/Height() fails");
        }

        إذا (old_w != new_w || old_h != new_h) {
            SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_RESIZED, new_w, new_h);
        }
    }

endfunction:

    Android_UnlockActivityMutex();

    أرجع SDL_FULLSCREEN_SUCCEEDED;
}

فراغ Android_Minimize_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    Android_JNI_Minimize_پنجره();
}

فراغ Android_مجموعه_پنجره_Resizable(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool resizable)
{
    // Set orientation
    Android_JNI_مجموعه_Orientation(پنجره->w, پنجره->h, پنجره->flags & SDL_پنجره_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));
}

فراغ Android_Destroy_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    Android_قفل_Activity_Mutex();

    إذا (پنجره == Android_پنجره) {
        Android_پنجره = عدم;

        إذا (پنجره->داخلی) {
            SDL_پنجره_داده *داده = پنجره->داخلی;

#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
            إذا (داده->egl_surface != EGL_NO_SURFACE) {
                SDL_EGL_DestroySurface(_this, داده->egl_surface);
            }
#پایان_اگر

            إذا (داده->native_پنجره) {
                ANative_پنجره_release(داده->native_پنجره);
            }
            SDL_free(پنجره->داخلی);
            پنجره->داخلی = عدم;
        }
    }

    Android_UnlockActivityMutex();
}

#پایان_اگر // SDL_VIDEO_DRIVER_ANDROID
