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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_ANDROID

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_keyboard_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_windowevents_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/android/SDL_android.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_androidvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_androidevents.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_androidwindow.h"


// Currently only one window
SDL_ਖਿੜਕੀ *Android_ਖਿੜਕੀ = ਨਿਰਾ;

bool Android_Create_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID create_props)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ;
    bool ਨਤੀਜਾ = true;

    ਜੇ (!Android_Wait_ਸਰਗਰਮ_And_ਤਾਲਾ_Activity()) {
        ਵਾਪਸ false;
    }

    ਜੇ (Android_ਖਿੜਕੀ) {
        ਨਤੀਜਾ = SDL_ਸੈੱਟ_Error("Android only supports one window");
        ਜਾਓ endfunction;
    }

    // Set orientation
    Android_JNI_ਸੈੱਟ_Orientation(ਖਿੜਕੀ->w, ਖਿੜਕੀ->h, ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));

    // Adjust the window data to match the screen
    ਖਿੜਕੀ->x = 0;
    ਖਿੜਕੀ->y = 0;
    ਖਿੜਕੀ->w = Android_Surface_ਚੌੜਾਈ;
    ਖਿੜਕੀ->h = Android_Surface_ਉਚਾਈ;

    // One window, it always has focus
    SDL_ਸੈੱਟ_Mouse_Focus(ਖਿੜਕੀ);
    SDL_ਸੈੱਟ_Keyboard_Focus(ਖਿੜਕੀ);

    ਅੰਕੜੇ = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(*ਅੰਕੜੇ));
    ਜੇ (!ਅੰਕੜੇ) {
        ਨਤੀਜਾ = false;
        ਜਾਓ endfunction;
    }

    ਅੰਕੜੇ->native_ਖਿੜਕੀ = Android_JNI_Get_Native_ਖਿੜਕੀ();
    ਜੇ (!ਅੰਕੜੇ->native_ਖਿੜਕੀ) {
        SDL_free(ਅੰਕੜੇ);
        ਨਤੀਜਾ = SDL_ਸੈੱਟ_Error("Could not fetch native window");
        ਜਾਓ endfunction;
    }
    SDL_ਸੈੱਟ_ਸੂਚਕ_Property(SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ), SDL_PROP_ਖਿੜਕੀ_ANDROID_ਖਿੜਕੀ_ਸੂਚਕ, ਅੰਕੜੇ->native_ਖਿੜਕੀ);

    /* Do not create EGLSurface for Vulkan window since it will then make the window
       incompatible with vkCreateAndroidSurfaceKHR */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_OPENGL) {
        ਅੰਕੜੇ->egl_surface = SDL_EGL_CreateSurface(_this, ਖਿੜਕੀ, (Native_ਖਿੜਕੀ_Type)ਅੰਕੜੇ->native_ਖਿੜਕੀ);

        ਜੇ (ਅੰਕੜੇ->egl_surface == EGL_NO_SURFACE) {
            ANative_ਖਿੜਕੀ_release(ਅੰਕੜੇ->native_ਖਿੜਕੀ);
            SDL_free(ਅੰਕੜੇ);
            ਨਤੀਜਾ = false;
            ਜਾਓ endfunction;
        }
    }
    SDL_ਸੈੱਟ_ਸੂਚਕ_Property(SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ), SDL_PROP_ਖਿੜਕੀ_ANDROID_SURFACE_ਸੂਚਕ, ਅੰਕੜੇ->egl_surface);
#ਜੇ_ਅੰਤ

    SDL_ਸੈੱਟ_ਖਿੜਕੀ_ਸੁਰੱਖਿਅਤ_Area_Insets(ਖਿੜਕੀ, Android_ਸੁਰੱਖਿਅਤ_Inset_ਖੱਬਾ, Android_ਸੁਰੱਖਿਅਤ_Inset_ਸੱਜਾ, Android_ਸੁਰੱਖਿਅਤ_Inset_ਸਿਖਰ, Android_ਸੁਰੱਖਿਅਤ_Inset_Bottom);

    ਖਿੜਕੀ->ਅੰਦਰੂਨੀ = ਅੰਕੜੇ;
    Android_ਖਿੜਕੀ = ਖਿੜਕੀ;

endfunction:

    Android_UnlockActivityMutex();

    ਵਾਪਸ ਨਤੀਜਾ;
}

ਖਾਲੀ Android_ਸੈੱਟ_ਖਿੜਕੀ_Title(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    Android_JNI_ਸੈੱਟ_Activity_Title(ਖਿੜਕੀ->title);
}

SDL_Fullscreen_ਨਤੀਜਾ Android_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    Android_ਤਾਲਾ_Activity_Mutex();

    ਜੇ (ਖਿੜਕੀ == Android_ਖਿੜਕੀ) {
        SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ;
        ਪੂਰਨ old_w, old_h, new_w, new_h;

        // If the window is being destroyed don't change visible state
        ਜੇ (!ਖਿੜਕੀ->is_destroying) {
            Android_JNI_ਸੈੱਟ_ਖਿੜਕੀ_Style(fullscreen);
        }

        /* Ensure our size matches reality after we've executed the window style change.
         *
         * It is possible that we've set width and height to the full-size display, but on
         * Samsung DeX or Chromebooks or other windowed Android environments, our window may
         * still not be the full display size.
         */
        ਜੇ (!SDL_IsDeXMode() && !SDL_IsChromebook()) {
            ਜਾਓ endfunction;
        }

        ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
        ਜੇ (!ਅੰਕੜੇ || !ਅੰਕੜੇ->native_ਖਿੜਕੀ) {
            ਜੇ (ਅੰਕੜੇ && !ਅੰਕੜੇ->native_ਖਿੜਕੀ) {
                SDL_ਸੈੱਟ_Error("Missing native window");
            }
            ਜਾਓ endfunction;
        }

        old_w = ਖਿੜਕੀ->w;
        old_h = ਖਿੜਕੀ->h;

        new_w = ANative_ਖਿੜਕੀ_get_ਚੌੜਾਈ(ਅੰਕੜੇ->native_ਖਿੜਕੀ);
        new_h = ANative_ਖਿੜਕੀ_get_ਉਚਾਈ(ਅੰਕੜੇ->native_ਖਿੜਕੀ);

        ਜੇ (new_w < 0 || new_h < 0) {
            SDL_ਸੈੱਟ_Error("ANativeWindow_getWidth/Height() fails");
        }

        ਜੇ (old_w != new_w || old_h != new_h) {
            SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_RESIZED, new_w, new_h);
        }
    }

endfunction:

    Android_UnlockActivityMutex();

    ਵਾਪਸ SDL_FULLSCREEN_SUCCEEDED;
}

ਖਾਲੀ Android_Minimize_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    Android_JNI_Minimize_ਖਿੜਕੀ();
}

ਖਾਲੀ Android_ਸੈੱਟ_ਖਿੜਕੀ_Resizable(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool resizable)
{
    // Set orientation
    Android_JNI_ਸੈੱਟ_Orientation(ਖਿੜਕੀ->w, ਖਿੜਕੀ->h, ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));
}

ਖਾਲੀ Android_Destroy_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    Android_ਤਾਲਾ_Activity_Mutex();

    ਜੇ (ਖਿੜਕੀ == Android_ਖਿੜਕੀ) {
        Android_ਖਿੜਕੀ = ਨਿਰਾ;

        ਜੇ (ਖਿੜਕੀ->ਅੰਦਰੂਨੀ) {
            SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
            ਜੇ (ਅੰਕੜੇ->egl_surface != EGL_NO_SURFACE) {
                SDL_EGL_DestroySurface(_this, ਅੰਕੜੇ->egl_surface);
            }
#ਜੇ_ਅੰਤ

            ਜੇ (ਅੰਕੜੇ->native_ਖਿੜਕੀ) {
                ANative_ਖਿੜਕੀ_release(ਅੰਕੜੇ->native_ਖਿੜਕੀ);
            }
            SDL_free(ਖਿੜਕੀ->ਅੰਦਰੂਨੀ);
            ਖਿੜਕੀ->ਅੰਦਰੂਨੀ = ਨਿਰਾ;
        }
    }

    Android_UnlockActivityMutex();
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_ANDROID
