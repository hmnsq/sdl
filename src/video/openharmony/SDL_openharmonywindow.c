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

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_OPENHARMONY

// !!! FIXME: these are defined as "const uint32_t VARNAME = VALUE;" in native_interface_xcomponent.h, which becomes a global variable in _our_ C code! Maybe C++ handles this differently...?
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OH_XCOMPONENT_ID_LEN_MAX sdl_ohoswindow_OH_XCOMPONENT_ID_LEN_MAX
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OH_MAX_TOUCH_POINTS_ਸੰਖਿਆ sdl_ohoswindow_OH_MAX_TOUCH_POINTS_ਸੰਖਿਆ
#ਅਨ੍ਤਰ੍ਭਾਵ <ace/xcomponent/native_interface_xcomponent.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_keyboard_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_windowevents_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/openharmony/SDL_openharmony.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_openharmonyvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_openharmonyevents.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_openharmonywindow.h"


// Currently only one window
SDL_ਖਿੜਕੀ *OPENHARMONY_ਖਿੜਕੀ = ਨਿਰਾ;

bool OPENHARMONY_Create_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID create_props)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ;
    bool ਨਤੀਜਾ = true;

    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //if (!OPENHARMONY_WaitActiveAndLockActivity()) {
    //    return false;
    //}

    ਜੇ (OPENHARMONY_ਖਿੜਕੀ) {
        ਨਤੀਜਾ = SDL_ਸੈੱਟ_Error("SDL on OpenHarmony (currently) only supports one window");
        ਜਾਓ endfunction;
    }

    ਖਾਲੀ *voidxcomp, *native_ਖਿੜਕੀ;
    SDL_Open_Harmony_Get_Native_ਖਿੜਕੀ_ਸੂਚਕ_ਸਾਰੇ(&voidxcomp, &native_ਖਿੜਕੀ);
    OH_NativeXComponent *native_xcomponent = (OH_NativeXComponent *) voidxcomp;
    ਜੇ (!native_xcomponent || !native_ਖਿੜਕੀ) {
        ਨਤੀਜਾ = SDL_ਸੈੱਟ_Error("Don't have Native XComponent or Native Window");
        ਜਾਓ endfunction;
    }

#ਜੇ 0  // !!! FIXME
    // Set orientation
    Android_JNI_ਸੈੱਟ_Orientation(ਖਿੜਕੀ->w, ਖਿੜਕੀ->h, ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));
#ਜੇ_ਅੰਤ

    uint64_t w, h;
    OH_Native_XComponent_Get_XComponent_ਮਾਪ(native_xcomponent, native_ਖਿੜਕੀ, &w, &h);

    // Adjust the window data to match the screen
    ਖਿੜਕੀ->x = 0;
    ਖਿੜਕੀ->y = 0;
    ਖਿੜਕੀ->w = (ਪੂਰਨ) w;
    ਖਿੜਕੀ->h = (ਪੂਰਨ) h;

    // One window, it always has focus
    SDL_ਸੈੱਟ_Mouse_Focus(ਖਿੜਕੀ);
    SDL_ਸੈੱਟ_Keyboard_Focus(ਖਿੜਕੀ);

    ਅੰਕੜੇ = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(*ਅੰਕੜੇ));
    ਜੇ (!ਅੰਕੜੇ) {
        ਨਤੀਜਾ = false;
        ਜਾਓ endfunction;
    }

    ਅੰਕੜੇ->native_xcomponent = native_xcomponent;
    ਅੰਕੜੇ->native_ਖਿੜਕੀ = native_ਖਿੜਕੀ;
    SDL_ਸੈੱਟ_ਸੂਚਕ_Property(SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ), SDL_PROP_ਖਿੜਕੀ_OPENHARMONY_XCOMPONENT_ਸੂਚਕ, ਅੰਕੜੇ->native_xcomponent);
    SDL_ਸੈੱਟ_ਸੂਚਕ_Property(SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ), SDL_PROP_ਖਿੜਕੀ_OPENHARMONY_ਖਿੜਕੀ_ਸੂਚਕ, ਅੰਕੜੇ->native_ਖਿੜਕੀ);

    /* Do not create EGLSurface for Vulkan window since it will then make the window
       incompatible with vkCreateAndroidSurfaceKHR */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_OPENGL) {
        ਅੰਕੜੇ->egl_surface = SDL_EGL_CreateSurface(_this, ਖਿੜਕੀ, (Native_ਖਿੜਕੀ_Type)ਅੰਕੜੇ->native_ਖਿੜਕੀ);
        ਜੇ (ਅੰਕੜੇ->egl_surface == EGL_NO_SURFACE) {
            SDL_free(ਅੰਕੜੇ);
            ਨਤੀਜਾ = false;
            ਜਾਓ endfunction;
        }
    }
    SDL_ਸੈੱਟ_ਸੂਚਕ_Property(SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ), SDL_PROP_ਖਿੜਕੀ_OPENHARMONY_SURFACE_ਸੂਚਕ, ਅੰਕੜੇ->egl_surface);
#ਜੇ_ਅੰਤ

#ਜੇ 0  // !!! FIXME
    SDL_ਸੈੱਟ_ਖਿੜਕੀ_ਸੁਰੱਖਿਅਤ_Area_Insets(ਖਿੜਕੀ, Android_ਸੁਰੱਖਿਅਤ_Inset_ਖੱਬਾ, Android_ਸੁਰੱਖਿਅਤ_Inset_ਸੱਜਾ, Android_ਸੁਰੱਖਿਅਤ_Inset_ਸਿਖਰ, Android_ਸੁਰੱਖਿਅਤ_Inset_Bottom);
#ਜੇ_ਅੰਤ

    ਖਿੜਕੀ->ਅੰਦਰੂਨੀ = ਅੰਕੜੇ;
    OPENHARMONY_ਖਿੜਕੀ = ਖਿੜਕੀ;

endfunction:

    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //Android_UnlockActivityMutex();

    ਵਾਪਸ ਨਤੀਜਾ;
}

ਖਾਲੀ OPENHARMONY_ਸੈੱਟ_ਖਿੜਕੀ_Title(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
#ਜੇ 0  // !!! FIXME
    Android_JNI_ਸੈੱਟ_Activity_Title(ਖਿੜਕੀ->title);
#ਜੇ_ਅੰਤ
}

SDL_Fullscreen_ਨਤੀਜਾ OPENHARMONY_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    ਜੇ (ਖਿੜਕੀ == OPENHARMONY_ਖਿੜਕੀ) {
        ਅਚਲ bool show_bars = (fullscreen == SDL_FULLSCREEN_OP_LEAVE);
        ਜੇ (!SDL_OpenHarmonyToggleSystemBars(show_bars, show_bars)) {
            ਵਾਪਸ SDL_FULLSCREEN_FAILED;
        }
        // !!! FIXME: make sure this causes an XComponent resize event, that we can pick up later.
        ਵਾਪਸ SDL_FULLSCREEN_PENDING;
    }
    ਵਾਪਸ SDL_FULLSCREEN_FAILED;
}

ਖਾਲੀ OPENHARMONY_Minimize_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
#ਜੇ 0  // !!! FIXME
    Android_JNI_Minimize_ਖਿੜਕੀ();
#ਜੇ_ਅੰਤ
}

ਖਾਲੀ OPENHARMONY_ਸੈੱਟ_ਖਿੜਕੀ_Resizable(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool resizable)
{
#ਜੇ 0  // !!! FIXME
    // Set orientation
    Android_JNI_ਸੈੱਟ_Orientation(ਖਿੜਕੀ->w, ਖਿੜਕੀ->h, ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));
#ਜੇ_ਅੰਤ
}

ਖਾਲੀ OPENHARMONY_Destroy_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //Android_LockActivityMutex();

    ਜੇ (ਖਿੜਕੀ == OPENHARMONY_ਖਿੜਕੀ) {
        OPENHARMONY_ਖਿੜਕੀ = ਨਿਰਾ;

        ਜੇ (ਖਿੜਕੀ->ਅੰਦਰੂਨੀ) {
            SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
            ਜੇ (ਅੰਕੜੇ->egl_surface != EGL_NO_SURFACE) {
                SDL_EGL_DestroySurface(_this, ਅੰਕੜੇ->egl_surface);
            }
#ਜੇ_ਅੰਤ

            // the XComponent and native window live past the SDL_Window; it can be reused for future windows.

            SDL_free(ਖਿੜਕੀ->ਅੰਦਰੂਨੀ);
            ਖਿੜਕੀ->ਅੰਦਰੂਨੀ = ਨਿਰਾ;
        }
    }

    //Android_UnlockActivityMutex();
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_OPENHARMONY
