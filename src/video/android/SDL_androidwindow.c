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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_ANDROID

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_keyboard_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_windowevents_c.h"
#ಅನ್ತರ್ಭಾವ "../../core/android/SDL_android.h"

#ಅನ್ತರ್ಭಾವ "SDL_androidvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_androidevents.h"
#ಅನ್ತರ್ಭಾವ "SDL_androidwindow.h"


// Currently only one window
SDL_ಕಿಟಕಿ *Android_ಕಿಟಕಿ = ಖಾಲಿ;

bool Android_Create_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID create_props)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ;
    bool ಫಲಿತಾಂಶ = true;

    ಆದರೆ (!Android_Wait_ಸಕ್ರಿಯ_And_ಬೀಗ_Activity()) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (Android_ಕಿಟಕಿ) {
        ಫಲಿತಾಂಶ = SDL_ಗಣ_Error("Android only supports one window");
        ಹೋಗು endfunction;
    }

    // Set orientation
    Android_JNI_ಗಣ_Orientation(ಕಿಟಕಿ->w, ಕಿಟಕಿ->h, ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));

    // Adjust the window data to match the screen
    ಕಿಟಕಿ->x = 0;
    ಕಿಟಕಿ->y = 0;
    ಕಿಟಕಿ->w = Android_Surface_ಅಗಲ;
    ಕಿಟಕಿ->h = Android_Surface_ಎತ್ತರ;

    // One window, it always has focus
    SDL_ಗಣ_Mouse_Focus(ಕಿಟಕಿ);
    SDL_ಗಣ_Keyboard_Focus(ಕಿಟಕಿ);

    ದತ್ತಾಂಶ = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(*ದತ್ತಾಂಶ));
    ಆದರೆ (!ದತ್ತಾಂಶ) {
        ಫಲಿತಾಂಶ = false;
        ಹೋಗು endfunction;
    }

    ದತ್ತಾಂಶ->native_ಕಿಟಕಿ = Android_JNI_Get_Native_ಕಿಟಕಿ();
    ಆದರೆ (!ದತ್ತಾಂಶ->native_ಕಿಟಕಿ) {
        SDL_free(ದತ್ತಾಂಶ);
        ಫಲಿತಾಂಶ = SDL_ಗಣ_Error("Could not fetch native window");
        ಹೋಗು endfunction;
    }
    SDL_ಗಣ_ಸೂಚಕ_Property(SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ), SDL_PROP_ಕಿಟಕಿ_ANDROID_ಕಿಟಕಿ_ಸೂಚಕ, ದತ್ತಾಂಶ->native_ಕಿಟಕಿ);

    /* Do not create EGLSurface for Vulkan window since it will then make the window
       incompatible with vkCreateAndroidSurfaceKHR */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_OPENGL) {
        ದತ್ತಾಂಶ->egl_surface = SDL_EGL_CreateSurface(_this, ಕಿಟಕಿ, (Native_ಕಿಟಕಿ_Type)ದತ್ತಾಂಶ->native_ಕಿಟಕಿ);

        ಆದರೆ (ದತ್ತಾಂಶ->egl_surface == EGL_NO_SURFACE) {
            ANative_ಕಿಟಕಿ_release(ದತ್ತಾಂಶ->native_ಕಿಟಕಿ);
            SDL_free(ದತ್ತಾಂಶ);
            ಫಲಿತಾಂಶ = false;
            ಹೋಗು endfunction;
        }
    }
    SDL_ಗಣ_ಸೂಚಕ_Property(SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ), SDL_PROP_ಕಿಟಕಿ_ANDROID_SURFACE_ಸೂಚಕ, ದತ್ತಾಂಶ->egl_surface);
#ಆದರೆ_ಅಂತ್ಯ

    SDL_ಗಣ_ಕಿಟಕಿ_ಸುರಕ್ಷಿತ_Area_Insets(ಕಿಟಕಿ, Android_ಸುರಕ್ಷಿತ_Inset_ಎಡ, Android_ಸುರಕ್ಷಿತ_Inset_ಬಲ, Android_ಸುರಕ್ಷಿತ_Inset_ತುದಿ, Android_ಸುರಕ್ಷಿತ_Inset_Bottom);

    ಕಿಟಕಿ->ಆಂತರಿಕ = ದತ್ತಾಂಶ;
    Android_ಕಿಟಕಿ = ಕಿಟಕಿ;

endfunction:

    Android_UnlockActivityMutex();

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

ಶೂನ್ಯ Android_ಗಣ_ಕಿಟಕಿ_Title(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    Android_JNI_ಗಣ_Activity_Title(ಕಿಟಕಿ->title);
}

SDL_Fullscreen_ಫಲಿತಾಂಶ Android_ಗಣ_ಕಿಟಕಿ_Fullscreen(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    Android_ಬೀಗ_Activity_Mutex();

    ಆದರೆ (ಕಿಟಕಿ == Android_ಕಿಟಕಿ) {
        SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ;
        ಪೂರ್ಣಾಂಕ old_w, old_h, new_w, new_h;

        // If the window is being destroyed don't change visible state
        ಆದರೆ (!ಕಿಟಕಿ->is_destroying) {
            Android_JNI_ಗಣ_ಕಿಟಕಿ_Style(fullscreen);
        }

        /* Ensure our size matches reality after we've executed the window style change.
         *
         * It is possible that we've set width and height to the full-size display, but on
         * Samsung DeX or Chromebooks or other windowed Android environments, our window may
         * still not be the full display size.
         */
        ಆದರೆ (!SDL_IsDeXMode() && !SDL_IsChromebook()) {
            ಹೋಗು endfunction;
        }

        ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
        ಆದರೆ (!ದತ್ತಾಂಶ || !ದತ್ತಾಂಶ->native_ಕಿಟಕಿ) {
            ಆದರೆ (ದತ್ತಾಂಶ && !ದತ್ತಾಂಶ->native_ಕಿಟಕಿ) {
                SDL_ಗಣ_Error("Missing native window");
            }
            ಹೋಗು endfunction;
        }

        old_w = ಕಿಟಕಿ->w;
        old_h = ಕಿಟಕಿ->h;

        new_w = ANative_ಕಿಟಕಿ_get_ಅಗಲ(ದತ್ತಾಂಶ->native_ಕಿಟಕಿ);
        new_h = ANative_ಕಿಟಕಿ_get_ಎತ್ತರ(ದತ್ತಾಂಶ->native_ಕಿಟಕಿ);

        ಆದರೆ (new_w < 0 || new_h < 0) {
            SDL_ಗಣ_Error("ANativeWindow_getWidth/Height() fails");
        }

        ಆದರೆ (old_w != new_w || old_h != new_h) {
            SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_RESIZED, new_w, new_h);
        }
    }

endfunction:

    Android_UnlockActivityMutex();

    ಹಿಂತಿರುಗಿ SDL_FULLSCREEN_SUCCEEDED;
}

ಶೂನ್ಯ Android_Minimize_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    Android_JNI_Minimize_ಕಿಟಕಿ();
}

ಶೂನ್ಯ Android_ಗಣ_ಕಿಟಕಿ_Resizable(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool resizable)
{
    // Set orientation
    Android_JNI_ಗಣ_Orientation(ಕಿಟಕಿ->w, ಕಿಟಕಿ->h, ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));
}

ಶೂನ್ಯ Android_Destroy_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    Android_ಬೀಗ_Activity_Mutex();

    ಆದರೆ (ಕಿಟಕಿ == Android_ಕಿಟಕಿ) {
        Android_ಕಿಟಕಿ = ಖಾಲಿ;

        ಆದರೆ (ಕಿಟಕಿ->ಆಂತರಿಕ) {
            SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
            ಆದರೆ (ದತ್ತಾಂಶ->egl_surface != EGL_NO_SURFACE) {
                SDL_EGL_DestroySurface(_this, ದತ್ತಾಂಶ->egl_surface);
            }
#ಆದರೆ_ಅಂತ್ಯ

            ಆದರೆ (ದತ್ತಾಂಶ->native_ಕಿಟಕಿ) {
                ANative_ಕಿಟಕಿ_release(ದತ್ತಾಂಶ->native_ಕಿಟಕಿ);
            }
            SDL_free(ಕಿಟಕಿ->ಆಂತರಿಕ);
            ಕಿಟಕಿ->ಆಂತರಿಕ = ಖಾಲಿ;
        }
    }

    Android_UnlockActivityMutex();
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_ANDROID
