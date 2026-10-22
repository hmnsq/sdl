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
#अन्तर्भाव "SDL_internal.h"

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_ANDROID

#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../../events/SDL_keyboard_c.h"
#अन्तर्भाव "../../events/SDL_mouse_c.h"
#अन्तर्भाव "../../events/SDL_windowevents_c.h"
#अन्तर्भाव "../../core/android/SDL_android.h"

#अन्तर्भाव "SDL_androidvideo.h"
#अन्तर्भाव "SDL_androidevents.h"
#अन्तर्भाव "SDL_androidwindow.h"


// Currently only one window
SDL_गवाक्षः *Android_गवाक्षः = रिक्त;

bool Android_Create_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID create_props)
{
    SDL_गवाक्षः_दत्त *दत्त;
    bool परिणाम = true;

    यदि (!Android_Wait_सक्रिय_And_तालकम्_Activity()) {
        प्रत्यागम false;
    }

    यदि (Android_गवाक्षः) {
        परिणाम = SDL_समुच्चयः_Error("Android only supports one window");
        गच्छ endfunction;
    }

    // Set orientation
    Android_JNI_समुच्चयः_Orientation(गवाक्षः->w, गवाक्षः->h, गवाक्षः->flags & SDL_गवाक्षः_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));

    // Adjust the window data to match the screen
    गवाक्षः->x = 0;
    गवाक्षः->y = 0;
    गवाक्षः->w = Android_Surface_विस्तारः;
    गवाक्षः->h = Android_SurfaceHeight;

    // One window, it always has focus
    SDL_समुच्चयः_Mouse_Focus(गवाक्षः);
    SDL_समुच्चयः_Keyboard_Focus(गवाक्षः);

    दत्त = (SDL_गवाक्षः_दत्त *)SDL_calloc(1, परिमाण(*दत्त));
    यदि (!दत्त) {
        परिणाम = false;
        गच्छ endfunction;
    }

    दत्त->native_गवाक्षः = Android_JNI_Get_Native_गवाक्षः();
    यदि (!दत्त->native_गवाक्षः) {
        SDL_free(दत्त);
        परिणाम = SDL_समुच्चयः_Error("Could not fetch native window");
        गच्छ endfunction;
    }
    SDL_समुच्चयः_Pointer_Property(SDL_Get_गवाक्षः_Properties(गवाक्षः), SDL_PROP_गवाक्षः_ANDROID_गवाक्षः_POINTER, दत्त->native_गवाक्षः);

    /* Do not create EGLSurface for Vulkan window since it will then make the window
       incompatible with vkCreateAndroidSurfaceKHR */
#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
    यदि (गवाक्षः->flags & SDL_गवाक्षः_OPENGL) {
        दत्त->egl_surface = SDL_EGL_CreateSurface(_this, गवाक्षः, (Native_गवाक्षः_Type)दत्त->native_गवाक्षः);

        यदि (दत्त->egl_surface == EGL_NO_SURFACE) {
            ANative_गवाक्षः_release(दत्त->native_गवाक्षः);
            SDL_free(दत्त);
            परिणाम = false;
            गच्छ endfunction;
        }
    }
    SDL_समुच्चयः_Pointer_Property(SDL_Get_गवाक्षः_Properties(गवाक्षः), SDL_PROP_गवाक्षः_ANDROID_SURFACE_POINTER, दत्त->egl_surface);
#यदि_अन्तः

    SDL_समुच्चयः_गवाक्षः_Safe_Area_Insets(गवाक्षः, Android_Safe_Inset_वामः, Android_Safe_Inset_दक्षिणः, Android_Safe_Inset_शिखरम्, Android_SafeInsetBottom);

    गवाक्षः->आन्तरिकम् = दत्त;
    Android_गवाक्षः = गवाक्षः;

endfunction:

    Android_UnlockActivityMutex();

    प्रत्यागम परिणाम;
}

शून्य Android_समुच्चयः_गवाक्षः_Title(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    Android_JNI_समुच्चयः_Activity_Title(गवाक्षः->title);
}

SDL_Fullscreen_परिणाम Android_समुच्चयः_गवाक्षः_Fullscreen(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    Android_तालकम्_Activity_Mutex();

    यदि (गवाक्षः == Android_गवाक्षः) {
        SDL_गवाक्षः_दत्त *दत्त;
        पूर्णाङ्क old_w, old_h, new_w, new_h;

        // If the window is being destroyed don't change visible state
        यदि (!गवाक्षः->is_destroying) {
            Android_JNI_समुच्चयः_गवाक्षः_Style(fullscreen);
        }

        /* Ensure our size matches reality after we've executed the window style change.
         *
         * It is possible that we've set width and height to the full-size display, but on
         * Samsung DeX or Chromebooks or other windowed Android environments, our window may
         * still not be the full display size.
         */
        यदि (!SDL_IsDeXMode() && !SDL_IsChromebook()) {
            गच्छ endfunction;
        }

        दत्त = गवाक्षः->आन्तरिकम्;
        यदि (!दत्त || !दत्त->native_गवाक्षः) {
            यदि (दत्त && !दत्त->native_गवाक्षः) {
                SDL_समुच्चयः_Error("Missing native window");
            }
            गच्छ endfunction;
        }

        old_w = गवाक्षः->w;
        old_h = गवाक्षः->h;

        new_w = ANative_गवाक्षः_get_विस्तारः(दत्त->native_गवाक्षः);
        new_h = ANative_गवाक्षः_get_Height(दत्त->native_गवाक्षः);

        यदि (new_w < 0 || new_h < 0) {
            SDL_समुच्चयः_Error("ANativeWindow_getWidth/Height() fails");
        }

        यदि (old_w != new_w || old_h != new_h) {
            SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_RESIZED, new_w, new_h);
        }
    }

endfunction:

    Android_UnlockActivityMutex();

    प्रत्यागम SDL_FULLSCREEN_SUCCEEDED;
}

शून्य Android_Minimize_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    Android_JNI_Minimize_गवाक्षः();
}

शून्य Android_समुच्चयः_गवाक्षः_Resizable(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool resizable)
{
    // Set orientation
    Android_JNI_समुच्चयः_Orientation(गवाक्षः->w, गवाक्षः->h, गवाक्षः->flags & SDL_गवाक्षः_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));
}

शून्य Android_Destroy_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    Android_तालकम्_Activity_Mutex();

    यदि (गवाक्षः == Android_गवाक्षः) {
        Android_गवाक्षः = रिक्त;

        यदि (गवाक्षः->आन्तरिकम्) {
            SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;

#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
            यदि (दत्त->egl_surface != EGL_NO_SURFACE) {
                SDL_EGL_DestroySurface(_this, दत्त->egl_surface);
            }
#यदि_अन्तः

            यदि (दत्त->native_गवाक्षः) {
                ANative_गवाक्षः_release(दत्त->native_गवाक्षः);
            }
            SDL_free(गवाक्षः->आन्तरिकम्);
            गवाक्षः->आन्तरिकम् = रिक्त;
        }
    }

    Android_UnlockActivityMutex();
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_ANDROID
