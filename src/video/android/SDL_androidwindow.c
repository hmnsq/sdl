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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_ANDROID

#ضمن "../SDL_sysvideo.h"
#ضمن "../../events/SDL_keyboard_c.h"
#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../../events/SDL_windowevents_c.h"
#ضمن "../../core/android/SDL_android.h"

#ضمن "SDL_androidvideo.h"
#ضمن "SDL_androidevents.h"
#ضمن "SDL_androidwindow.h"


// Currently only one window
SDL_دري *Android_دري = عدم;

bool Android_Create_دري(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID create_props)
{
    SDL_دري_معلومات *معلومات;
    bool نتيجو = true;

    إذا (!Android_Wait_سرگرم_And_تالو_Activity()) {
        أرجع false;
    }

    إذا (Android_دري) {
        نتيجو = SDL_سيٽ_Error("Android only supports one window");
        اذهب endfunction;
    }

    // Set orientation
    Android_JNI_سيٽ_Orientation(دري->w, دري->h, دري->flags & SDL_دري_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));

    // Adjust the window data to match the screen
    دري->x = 0;
    دري->y = 0;
    دري->w = Android_Surface_ويڪر;
    دري->h = Android_Surface_اوچائي;

    // One window, it always has focus
    SDL_سيٽ_Mouse_Focus(دري);
    SDL_سيٽ_Keyboard_Focus(دري);

    معلومات = (SDL_دري_معلومات *)SDL_calloc(1, حجم(*معلومات));
    إذا (!معلومات) {
        نتيجو = false;
        اذهب endfunction;
    }

    معلومات->native_دري = Android_JNI_Get_Native_دري();
    إذا (!معلومات->native_دري) {
        SDL_free(معلومات);
        نتيجو = SDL_سيٽ_Error("Could not fetch native window");
        اذهب endfunction;
    }
    SDL_سيٽ_اشارو_Property(SDL_Get_دري_Properties(دري), SDL_PROP_دري_ANDROID_دري_اشارو, معلومات->native_دري);

    /* Do not create EGLSurface for Vulkan window since it will then make the window
       incompatible with vkCreateAndroidSurfaceKHR */
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
    إذا (دري->flags & SDL_دري_OPENGL) {
        معلومات->egl_surface = SDL_EGL_CreateSurface(_this, دري, (Native_دري_Type)معلومات->native_دري);

        إذا (معلومات->egl_surface == EGL_NO_SURFACE) {
            ANative_دري_release(معلومات->native_دري);
            SDL_free(معلومات);
            نتيجو = false;
            اذهب endfunction;
        }
    }
    SDL_سيٽ_اشارو_Property(SDL_Get_دري_Properties(دري), SDL_PROP_دري_ANDROID_SURFACE_اشارو, معلومات->egl_surface);
#جيڪڏهن_پورو

    SDL_سيٽ_دري_محفوظ_Area_Insets(دري, Android_محفوظ_Inset_کاٻو, Android_محفوظ_Inset_ساڄو, Android_محفوظ_Inset_چوٽي, Android_محفوظ_Inset_Bottom);

    دري->اندروني = معلومات;
    Android_دري = دري;

endfunction:

    Android_UnlockActivityMutex();

    أرجع نتيجو;
}

فراغ Android_سيٽ_دري_Title(SDL_VideoDevice *_this, SDL_دري *دري)
{
    Android_JNI_سيٽ_Activity_Title(دري->title);
}

SDL_Fullscreen_نتيجو Android_سيٽ_دري_Fullscreen(SDL_VideoDevice *_this, SDL_دري *دري, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    Android_تالو_Activity_Mutex();

    إذا (دري == Android_دري) {
        SDL_دري_معلومات *معلومات;
        صحيح old_w, old_h, new_w, new_h;

        // If the window is being destroyed don't change visible state
        إذا (!دري->is_destroying) {
            Android_JNI_سيٽ_دري_Style(fullscreen);
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

        معلومات = دري->اندروني;
        إذا (!معلومات || !معلومات->native_دري) {
            إذا (معلومات && !معلومات->native_دري) {
                SDL_سيٽ_Error("Missing native window");
            }
            اذهب endfunction;
        }

        old_w = دري->w;
        old_h = دري->h;

        new_w = ANative_دري_get_ويڪر(معلومات->native_دري);
        new_h = ANative_دري_get_اوچائي(معلومات->native_دري);

        إذا (new_w < 0 || new_h < 0) {
            SDL_سيٽ_Error("ANativeWindow_getWidth/Height() fails");
        }

        إذا (old_w != new_w || old_h != new_h) {
            SDL_Send_دري_Event(دري, SDL_EVENT_دري_RESIZED, new_w, new_h);
        }
    }

endfunction:

    Android_UnlockActivityMutex();

    أرجع SDL_FULLSCREEN_SUCCEEDED;
}

فراغ Android_Minimize_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    Android_JNI_Minimize_دري();
}

فراغ Android_سيٽ_دري_Resizable(SDL_VideoDevice *_this, SDL_دري *دري, bool resizable)
{
    // Set orientation
    Android_JNI_سيٽ_Orientation(دري->w, دري->h, دري->flags & SDL_دري_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));
}

فراغ Android_Destroy_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    Android_تالو_Activity_Mutex();

    إذا (دري == Android_دري) {
        Android_دري = عدم;

        إذا (دري->اندروني) {
            SDL_دري_معلومات *معلومات = دري->اندروني;

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
            إذا (معلومات->egl_surface != EGL_NO_SURFACE) {
                SDL_EGL_DestroySurface(_this, معلومات->egl_surface);
            }
#جيڪڏهن_پورو

            إذا (معلومات->native_دري) {
                ANative_دري_release(معلومات->native_دري);
            }
            SDL_free(دري->اندروني);
            دري->اندروني = عدم;
        }
    }

    Android_UnlockActivityMutex();
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_ANDROID
