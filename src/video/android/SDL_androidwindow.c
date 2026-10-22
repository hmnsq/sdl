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
#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_ANDROID

#شامل "../SDL_sysvideo.h"
#شامل "../../events/SDL_keyboard_c.h"
#شامل "../../events/SDL_mouse_c.h"
#شامل "../../events/SDL_windowevents_c.h"
#شامل "../../core/android/SDL_android.h"

#شامل "SDL_androidvideo.h"
#شامل "SDL_androidevents.h"
#شامل "SDL_androidwindow.h"


// Currently only one window
SDL_کھڑکی *Android_کھڑکی = تہی;

bool Android_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا;
    bool نتیجہ = true;

    اگر (!Android_Wait_فعال_And_تالا_Activity()) {
        واپس false;
    }

    اگر (Android_کھڑکی) {
        نتیجہ = SDL_سیٹ_Error("Android only supports one window");
        جاؤ endfunction;
    }

    // Set orientation
    Android_JNI_سیٹ_Orientation(کھڑکی->w, کھڑکی->h, کھڑکی->flags & SDL_کھڑکی_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));

    // Adjust the window data to match the screen
    کھڑکی->x = 0;
    کھڑکی->y = 0;
    کھڑکی->w = Android_Surface_چوڑائی;
    کھڑکی->h = Android_Surface_اونچائی;

    // One window, it always has focus
    SDL_سیٹ_Mouse_Focus(کھڑکی);
    SDL_سیٹ_Keyboard_Focus(کھڑکی);

    ڈیٹا = (SDL_کھڑکی_ڈیٹا *)SDL_calloc(1, حجم(*ڈیٹا));
    اگر (!ڈیٹا) {
        نتیجہ = false;
        جاؤ endfunction;
    }

    ڈیٹا->native_کھڑکی = Android_JNI_Get_Native_کھڑکی();
    اگر (!ڈیٹا->native_کھڑکی) {
        SDL_free(ڈیٹا);
        نتیجہ = SDL_سیٹ_Error("Could not fetch native window");
        جاؤ endfunction;
    }
    SDL_سیٹ_اشارہ_گر_Property(SDL_Get_کھڑکی_Properties(کھڑکی), SDL_PROP_کھڑکی_ANDROID_کھڑکی_اشارہ_گر, ڈیٹا->native_کھڑکی);

    /* Do not create EGLSurface for Vulkan window since it will then make the window
       incompatible with vkCreateAndroidSurfaceKHR */
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    اگر (کھڑکی->flags & SDL_کھڑکی_OPENGL) {
        ڈیٹا->egl_surface = SDL_EGL_CreateSurface(_this, کھڑکی, (Native_کھڑکی_Type)ڈیٹا->native_کھڑکی);

        اگر (ڈیٹا->egl_surface == EGL_NO_SURFACE) {
            ANative_کھڑکی_release(ڈیٹا->native_کھڑکی);
            SDL_free(ڈیٹا);
            نتیجہ = false;
            جاؤ endfunction;
        }
    }
    SDL_سیٹ_اشارہ_گر_Property(SDL_Get_کھڑکی_Properties(کھڑکی), SDL_PROP_کھڑکی_ANDROID_SURFACE_اشارہ_گر, ڈیٹا->egl_surface);
#اگر_ختم

    SDL_سیٹ_کھڑکی_محفوظ_Area_Insets(کھڑکی, Android_محفوظ_Inset_بایاں, Android_محفوظ_Inset_دایاں, Android_محفوظ_Inset_چوٹی, Android_محفوظ_Inset_Bottom);

    کھڑکی->اندرونی_2 = ڈیٹا;
    Android_کھڑکی = کھڑکی;

endfunction:

    Android_UnlockActivityMutex();

    واپس نتیجہ;
}

خالی Android_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    Android_JNI_سیٹ_Activity_Title(کھڑکی->title);
}

SDL_Fullscreen_نتیجہ Android_سیٹ_کھڑکی_Fullscreen(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    Android_تالا_Activity_Mutex();

    اگر (کھڑکی == Android_کھڑکی) {
        SDL_کھڑکی_ڈیٹا *ڈیٹا;
        صحیح old_w, old_h, new_w, new_h;

        // If the window is being destroyed don't change visible state
        اگر (!کھڑکی->is_destroying) {
            Android_JNI_سیٹ_کھڑکی_Style(fullscreen);
        }

        /* Ensure our size matches reality after we've executed the window style change.
         *
         * It is possible that we've set width and height to the full-size display, but on
         * Samsung DeX or Chromebooks or other windowed Android environments, our window may
         * still not be the full display size.
         */
        اگر (!SDL_IsDeXMode() && !SDL_IsChromebook()) {
            جاؤ endfunction;
        }

        ڈیٹا = کھڑکی->اندرونی_2;
        اگر (!ڈیٹا || !ڈیٹا->native_کھڑکی) {
            اگر (ڈیٹا && !ڈیٹا->native_کھڑکی) {
                SDL_سیٹ_Error("Missing native window");
            }
            جاؤ endfunction;
        }

        old_w = کھڑکی->w;
        old_h = کھڑکی->h;

        new_w = ANative_کھڑکی_get_چوڑائی(ڈیٹا->native_کھڑکی);
        new_h = ANative_کھڑکی_get_اونچائی(ڈیٹا->native_کھڑکی);

        اگر (new_w < 0 || new_h < 0) {
            SDL_سیٹ_Error("ANativeWindow_getWidth/Height() fails");
        }

        اگر (old_w != new_w || old_h != new_h) {
            SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESIZED, new_w, new_h);
        }
    }

endfunction:

    Android_UnlockActivityMutex();

    واپس SDL_FULLSCREEN_SUCCEEDED;
}

خالی Android_Minimize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    Android_JNI_Minimize_کھڑکی();
}

خالی Android_سیٹ_کھڑکی_Resizable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool resizable)
{
    // Set orientation
    Android_JNI_سیٹ_Orientation(کھڑکی->w, کھڑکی->h, کھڑکی->flags & SDL_کھڑکی_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));
}

خالی Android_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    Android_تالا_Activity_Mutex();

    اگر (کھڑکی == Android_کھڑکی) {
        Android_کھڑکی = تہی;

        اگر (کھڑکی->اندرونی_2) {
            SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
            اگر (ڈیٹا->egl_surface != EGL_NO_SURFACE) {
                SDL_EGL_DestroySurface(_this, ڈیٹا->egl_surface);
            }
#اگر_ختم

            اگر (ڈیٹا->native_کھڑکی) {
                ANative_کھڑکی_release(ڈیٹا->native_کھڑکی);
            }
            SDL_free(کھڑکی->اندرونی_2);
            کھڑکی->اندرونی_2 = تہی;
        }
    }

    Android_UnlockActivityMutex();
}

#اگر_ختم // SDL_VIDEO_DRIVER_ANDROID
