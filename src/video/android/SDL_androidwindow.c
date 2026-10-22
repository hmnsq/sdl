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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_ANDROID

#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "../../events/SDL_keyboard_c.h"
#అన్తర్భావ "../../events/SDL_mouse_c.h"
#అన్తర్భావ "../../events/SDL_windowevents_c.h"
#అన్తర్భావ "../../core/android/SDL_android.h"

#అన్తర్భావ "SDL_androidvideo.h"
#అన్తర్భావ "SDL_androidevents.h"
#అన్తర్భావ "SDL_androidwindow.h"


// Currently only one window
SDL_కిటికీ *Android_కిటికీ = ఖాళీ;

bool Android_Create_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID create_props)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం;
    bool ఫలితం = true;

    ఒకవేళ (!Android_Wait_చురుకైన_And_తాళం_Activity()) {
        తిరిగి false;
    }

    ఒకవేళ (Android_కిటికీ) {
        ఫలితం = SDL_సమితి_Error("Android only supports one window");
        వెళ్ళు endfunction;
    }

    // Set orientation
    Android_JNI_సమితి_Orientation(కిటికీ->w, కిటికీ->h, కిటికీ->flags & SDL_కిటికీ_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));

    // Adjust the window data to match the screen
    కిటికీ->x = 0;
    కిటికీ->y = 0;
    కిటికీ->w = Android_Surface_వెడల్పు;
    కిటికీ->h = Android_Surface_ఎత్తు;

    // One window, it always has focus
    SDL_సమితి_Mouse_Focus(కిటికీ);
    SDL_సమితి_Keyboard_Focus(కిటికీ);

    దత్తాంశం = (SDL_కిటికీ_దత్తాంశం *)SDL_calloc(1, పరిమాణం(*దత్తాంశం));
    ఒకవేళ (!దత్తాంశం) {
        ఫలితం = false;
        వెళ్ళు endfunction;
    }

    దత్తాంశం->native_కిటికీ = Android_JNI_Get_Native_కిటికీ();
    ఒకవేళ (!దత్తాంశం->native_కిటికీ) {
        SDL_free(దత్తాంశం);
        ఫలితం = SDL_సమితి_Error("Could not fetch native window");
        వెళ్ళు endfunction;
    }
    SDL_సమితి_సూచిక_Property(SDL_Get_కిటికీ_Properties(కిటికీ), SDL_PROP_కిటికీ_ANDROID_కిటికీ_సూచిక, దత్తాంశం->native_కిటికీ);

    /* Do not create EGLSurface for Vulkan window since it will then make the window
       incompatible with vkCreateAndroidSurfaceKHR */
#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_OPENGL) {
        దత్తాంశం->egl_surface = SDL_EGL_CreateSurface(_this, కిటికీ, (Native_కిటికీ_Type)దత్తాంశం->native_కిటికీ);

        ఒకవేళ (దత్తాంశం->egl_surface == EGL_NO_SURFACE) {
            ANative_కిటికీ_release(దత్తాంశం->native_కిటికీ);
            SDL_free(దత్తాంశం);
            ఫలితం = false;
            వెళ్ళు endfunction;
        }
    }
    SDL_సమితి_సూచిక_Property(SDL_Get_కిటికీ_Properties(కిటికీ), SDL_PROP_కిటికీ_ANDROID_SURFACE_సూచిక, దత్తాంశం->egl_surface);
#అయితే_ముగింపు

    SDL_సమితి_కిటికీ_సురక్షిత_Area_Insets(కిటికీ, Android_సురక్షిత_Inset_ఎడమ, Android_సురక్షిత_Inset_కుడి, Android_సురక్షిత_Inset_శిఖరం, Android_సురక్షిత_Inset_Bottom);

    కిటికీ->అంతర్గత = దత్తాంశం;
    Android_కిటికీ = కిటికీ;

endfunction:

    Android_UnlockActivityMutex();

    తిరిగి ఫలితం;
}

శూన్య Android_సమితి_కిటికీ_Title(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    Android_JNI_సమితి_Activity_Title(కిటికీ->title);
}

SDL_Fullscreen_ఫలితం Android_సమితి_కిటికీ_Fullscreen(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    Android_తాళం_Activity_Mutex();

    ఒకవేళ (కిటికీ == Android_కిటికీ) {
        SDL_కిటికీ_దత్తాంశం *దత్తాంశం;
        పూర్ణాంకం old_w, old_h, new_w, new_h;

        // If the window is being destroyed don't change visible state
        ఒకవేళ (!కిటికీ->is_destroying) {
            Android_JNI_సమితి_కిటికీ_Style(fullscreen);
        }

        /* Ensure our size matches reality after we've executed the window style change.
         *
         * It is possible that we've set width and height to the full-size display, but on
         * Samsung DeX or Chromebooks or other windowed Android environments, our window may
         * still not be the full display size.
         */
        ఒకవేళ (!SDL_IsDeXMode() && !SDL_IsChromebook()) {
            వెళ్ళు endfunction;
        }

        దత్తాంశం = కిటికీ->అంతర్గత;
        ఒకవేళ (!దత్తాంశం || !దత్తాంశం->native_కిటికీ) {
            ఒకవేళ (దత్తాంశం && !దత్తాంశం->native_కిటికీ) {
                SDL_సమితి_Error("Missing native window");
            }
            వెళ్ళు endfunction;
        }

        old_w = కిటికీ->w;
        old_h = కిటికీ->h;

        new_w = ANative_కిటికీ_get_వెడల్పు(దత్తాంశం->native_కిటికీ);
        new_h = ANative_కిటికీ_get_ఎత్తు(దత్తాంశం->native_కిటికీ);

        ఒకవేళ (new_w < 0 || new_h < 0) {
            SDL_సమితి_Error("ANativeWindow_getWidth/Height() fails");
        }

        ఒకవేళ (old_w != new_w || old_h != new_h) {
            SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_RESIZED, new_w, new_h);
        }
    }

endfunction:

    Android_UnlockActivityMutex();

    తిరిగి SDL_FULLSCREEN_SUCCEEDED;
}

శూన్య Android_Minimize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    Android_JNI_Minimize_కిటికీ();
}

శూన్య Android_సమితి_కిటికీ_Resizable(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool resizable)
{
    // Set orientation
    Android_JNI_సమితి_Orientation(కిటికీ->w, కిటికీ->h, కిటికీ->flags & SDL_కిటికీ_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));
}

శూన్య Android_Destroy_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    Android_తాళం_Activity_Mutex();

    ఒకవేళ (కిటికీ == Android_కిటికీ) {
        Android_కిటికీ = ఖాళీ;

        ఒకవేళ (కిటికీ->అంతర్గత) {
            SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;

#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
            ఒకవేళ (దత్తాంశం->egl_surface != EGL_NO_SURFACE) {
                SDL_EGL_DestroySurface(_this, దత్తాంశం->egl_surface);
            }
#అయితే_ముగింపు

            ఒకవేళ (దత్తాంశం->native_కిటికీ) {
                ANative_కిటికీ_release(దత్తాంశం->native_కిటికీ);
            }
            SDL_free(కిటికీ->అంతర్గత);
            కిటికీ->అంతర్గత = ఖాళీ;
        }
    }

    Android_UnlockActivityMutex();
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_ANDROID
