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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_OPENHARMONY

// !!! FIXME: these are defined as "const uint32_t VARNAME = VALUE;" in native_interface_xcomponent.h, which becomes a global variable in _our_ C code! Maybe C++ handles this differently...?
#ವ್ಯಾಖ್ಯಾನಿಸು OH_XCOMPONENT_ID_LEN_MAX sdl_ohoswindow_OH_XCOMPONENT_ID_LEN_MAX
#ವ್ಯಾಖ್ಯಾನಿಸು OH_MAX_TOUCH_POINTS_ಸಂಖ್ಯೆ sdl_ohoswindow_OH_MAX_TOUCH_POINTS_ಸಂಖ್ಯೆ
#ಅನ್ತರ್ಭಾವ <ace/xcomponent/native_interface_xcomponent.h>

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_keyboard_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_windowevents_c.h"
#ಅನ್ತರ್ಭಾವ "../../core/openharmony/SDL_openharmony.h"

#ಅನ್ತರ್ಭಾವ "SDL_openharmonyvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_openharmonyevents.h"
#ಅನ್ತರ್ಭಾವ "SDL_openharmonywindow.h"


// Currently only one window
SDL_ಕಿಟಕಿ *OPENHARMONY_ಕಿಟಕಿ = ಖಾಲಿ;

bool OPENHARMONY_Create_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID create_props)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ;
    bool ಫಲಿತಾಂಶ = true;

    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //if (!OPENHARMONY_WaitActiveAndLockActivity()) {
    //    return false;
    //}

    ಆದರೆ (OPENHARMONY_ಕಿಟಕಿ) {
        ಫಲಿತಾಂಶ = SDL_ಗಣ_Error("SDL on OpenHarmony (currently) only supports one window");
        ಹೋಗು endfunction;
    }

    ಶೂನ್ಯ *voidxcomp, *native_ಕಿಟಕಿ;
    SDL_Open_Harmony_Get_Native_ಕಿಟಕಿ_ಸೂಚಕಗಳು(&voidxcomp, &native_ಕಿಟಕಿ);
    OH_NativeXComponent *native_xcomponent = (OH_NativeXComponent *) voidxcomp;
    ಆದರೆ (!native_xcomponent || !native_ಕಿಟಕಿ) {
        ಫಲಿತಾಂಶ = SDL_ಗಣ_Error("Don't have Native XComponent or Native Window");
        ಹೋಗು endfunction;
    }

#ಆದರೆ 0  // !!! FIXME
    // Set orientation
    Android_JNI_ಗಣ_Orientation(ಕಿಟಕಿ->w, ಕಿಟಕಿ->h, ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));
#ಆದರೆ_ಅಂತ್ಯ

    uint64_t w, h;
    OH_Native_XComponent_Get_XComponent_ಗಾತ್ರ(native_xcomponent, native_ಕಿಟಕಿ, &w, &h);

    // Adjust the window data to match the screen
    ಕಿಟಕಿ->x = 0;
    ಕಿಟಕಿ->y = 0;
    ಕಿಟಕಿ->w = (ಪೂರ್ಣಾಂಕ) w;
    ಕಿಟಕಿ->h = (ಪೂರ್ಣಾಂಕ) h;

    // One window, it always has focus
    SDL_ಗಣ_Mouse_Focus(ಕಿಟಕಿ);
    SDL_ಗಣ_Keyboard_Focus(ಕಿಟಕಿ);

    ದತ್ತಾಂಶ = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(*ದತ್ತಾಂಶ));
    ಆದರೆ (!ದತ್ತಾಂಶ) {
        ಫಲಿತಾಂಶ = false;
        ಹೋಗು endfunction;
    }

    ದತ್ತಾಂಶ->native_xcomponent = native_xcomponent;
    ದತ್ತಾಂಶ->native_ಕಿಟಕಿ = native_ಕಿಟಕಿ;
    SDL_ಗಣ_ಸೂಚಕ_Property(SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ), SDL_PROP_ಕಿಟಕಿ_OPENHARMONY_XCOMPONENT_ಸೂಚಕ, ದತ್ತಾಂಶ->native_xcomponent);
    SDL_ಗಣ_ಸೂಚಕ_Property(SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ), SDL_PROP_ಕಿಟಕಿ_OPENHARMONY_ಕಿಟಕಿ_ಸೂಚಕ, ದತ್ತಾಂಶ->native_ಕಿಟಕಿ);

    /* Do not create EGLSurface for Vulkan window since it will then make the window
       incompatible with vkCreateAndroidSurfaceKHR */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_OPENGL) {
        ದತ್ತಾಂಶ->egl_surface = SDL_EGL_CreateSurface(_this, ಕಿಟಕಿ, (Native_ಕಿಟಕಿ_Type)ದತ್ತಾಂಶ->native_ಕಿಟಕಿ);
        ಆದರೆ (ದತ್ತಾಂಶ->egl_surface == EGL_NO_SURFACE) {
            SDL_free(ದತ್ತಾಂಶ);
            ಫಲಿತಾಂಶ = false;
            ಹೋಗು endfunction;
        }
    }
    SDL_ಗಣ_ಸೂಚಕ_Property(SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ), SDL_PROP_ಕಿಟಕಿ_OPENHARMONY_SURFACE_ಸೂಚಕ, ದತ್ತಾಂಶ->egl_surface);
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ 0  // !!! FIXME
    SDL_ಗಣ_ಕಿಟಕಿ_ಸುರಕ್ಷಿತ_Area_Insets(ಕಿಟಕಿ, Android_ಸುರಕ್ಷಿತ_Inset_ಎಡ, Android_ಸುರಕ್ಷಿತ_Inset_ಬಲ, Android_ಸುರಕ್ಷಿತ_Inset_ತುದಿ, Android_ಸುರಕ್ಷಿತ_Inset_Bottom);
#ಆದರೆ_ಅಂತ್ಯ

    ಕಿಟಕಿ->ಆಂತರಿಕ = ದತ್ತಾಂಶ;
    OPENHARMONY_ಕಿಟಕಿ = ಕಿಟಕಿ;

endfunction:

    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //Android_UnlockActivityMutex();

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

ಶೂನ್ಯ OPENHARMONY_ಗಣ_ಕಿಟಕಿ_Title(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
#ಆದರೆ 0  // !!! FIXME
    Android_JNI_ಗಣ_Activity_Title(ಕಿಟಕಿ->title);
#ಆದರೆ_ಅಂತ್ಯ
}

SDL_Fullscreen_ಫಲಿತಾಂಶ OPENHARMONY_ಗಣ_ಕಿಟಕಿ_Fullscreen(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    ಆದರೆ (ಕಿಟಕಿ == OPENHARMONY_ಕಿಟಕಿ) {
        ಸ್ಥಿರಾಂಕ bool show_bars = (fullscreen == SDL_FULLSCREEN_OP_LEAVE);
        ಆದರೆ (!SDL_OpenHarmonyToggleSystemBars(show_bars, show_bars)) {
            ಹಿಂತಿರುಗಿ SDL_FULLSCREEN_FAILED;
        }
        // !!! FIXME: make sure this causes an XComponent resize event, that we can pick up later.
        ಹಿಂತಿರುಗಿ SDL_FULLSCREEN_PENDING;
    }
    ಹಿಂತಿರುಗಿ SDL_FULLSCREEN_FAILED;
}

ಶೂನ್ಯ OPENHARMONY_Minimize_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
#ಆದರೆ 0  // !!! FIXME
    Android_JNI_Minimize_ಕಿಟಕಿ();
#ಆದರೆ_ಅಂತ್ಯ
}

ಶೂನ್ಯ OPENHARMONY_ಗಣ_ಕಿಟಕಿ_Resizable(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool resizable)
{
#ಆದರೆ 0  // !!! FIXME
    // Set orientation
    Android_JNI_ಗಣ_Orientation(ಕಿಟಕಿ->w, ಕಿಟಕಿ->h, ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));
#ಆದರೆ_ಅಂತ್ಯ
}

ಶೂನ್ಯ OPENHARMONY_Destroy_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //Android_LockActivityMutex();

    ಆದರೆ (ಕಿಟಕಿ == OPENHARMONY_ಕಿಟಕಿ) {
        OPENHARMONY_ಕಿಟಕಿ = ಖಾಲಿ;

        ಆದರೆ (ಕಿಟಕಿ->ಆಂತರಿಕ) {
            SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
            ಆದರೆ (ದತ್ತಾಂಶ->egl_surface != EGL_NO_SURFACE) {
                SDL_EGL_DestroySurface(_this, ದತ್ತಾಂಶ->egl_surface);
            }
#ಆದರೆ_ಅಂತ್ಯ

            // the XComponent and native window live past the SDL_Window; it can be reused for future windows.

            SDL_free(ಕಿಟಕಿ->ಆಂತರಿಕ);
            ಕಿಟಕಿ->ಆಂತರಿಕ = ಖಾಲಿ;
        }
    }

    //Android_UnlockActivityMutex();
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_OPENHARMONY
