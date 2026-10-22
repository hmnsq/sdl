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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_OPENHARMONY

// !!! FIXME: these are defined as "const uint32_t VARNAME = VALUE;" in native_interface_xcomponent.h, which becomes a global variable in _our_ C code! Maybe C++ handles this differently...?
#تعریف_کن OH_XCOMPONENT_ID_LEN_MAX sdl_ohoswindow_OH_XCOMPONENT_ID_LEN_MAX
#تعریف_کن OH_MAX_TOUCH_POINTS_عدد sdl_ohoswindow_OH_MAX_TOUCH_POINTS_عدد
#ضمن <ace/xcomponent/native_interface_xcomponent.h>

#ضمن "../SDL_sysvideo.h"
#ضمن "../../events/SDL_keyboard_c.h"
#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../../events/SDL_windowevents_c.h"
#ضمن "../../core/openharmony/SDL_openharmony.h"

#ضمن "SDL_openharmonyvideo.h"
#ضمن "SDL_openharmonyevents.h"
#ضمن "SDL_openharmonywindow.h"


// Currently only one window
SDL_پنجره *OPENHARMONY_پنجره = عدم;

bool OPENHARMONY_Create_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID create_props)
{
    SDL_پنجره_داده *داده;
    bool نتیجه = true;

    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //if (!OPENHARMONY_WaitActiveAndLockActivity()) {
    //    return false;
    //}

    إذا (OPENHARMONY_پنجره) {
        نتیجه = SDL_مجموعه_Error("SDL on OpenHarmony (currently) only supports one window");
        اذهب endfunction;
    }

    فراغ *voidxcomp, *native_پنجره;
    SDL_Open_Harmony_Get_Native_پنجره_اشارهگرها(&voidxcomp, &native_پنجره);
    OH_NativeXComponent *native_xcomponent = (OH_NativeXComponent *) voidxcomp;
    إذا (!native_xcomponent || !native_پنجره) {
        نتیجه = SDL_مجموعه_Error("Don't have Native XComponent or Native Window");
        اذهب endfunction;
    }

#إذا 0  // !!! FIXME
    // Set orientation
    Android_JNI_مجموعه_Orientation(پنجره->w, پنجره->h, پنجره->flags & SDL_پنجره_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));
#پایان_اگر

    uint64_t w, h;
    OH_Native_XComponent_Get_XComponent_اندازه(native_xcomponent, native_پنجره, &w, &h);

    // Adjust the window data to match the screen
    پنجره->x = 0;
    پنجره->y = 0;
    پنجره->w = (صحيح) w;
    پنجره->h = (صحيح) h;

    // One window, it always has focus
    SDL_مجموعه_Mouse_Focus(پنجره);
    SDL_مجموعه_Keyboard_Focus(پنجره);

    داده = (SDL_پنجره_داده *)SDL_calloc(1, حجم(*داده));
    إذا (!داده) {
        نتیجه = false;
        اذهب endfunction;
    }

    داده->native_xcomponent = native_xcomponent;
    داده->native_پنجره = native_پنجره;
    SDL_مجموعه_اشاره_گر_Property(SDL_Get_پنجره_Properties(پنجره), SDL_PROP_پنجره_OPENHARMONY_XCOMPONENT_اشاره_گر, داده->native_xcomponent);
    SDL_مجموعه_اشاره_گر_Property(SDL_Get_پنجره_Properties(پنجره), SDL_PROP_پنجره_OPENHARMONY_پنجره_اشاره_گر, داده->native_پنجره);

    /* Do not create EGLSurface for Vulkan window since it will then make the window
       incompatible with vkCreateAndroidSurfaceKHR */
#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
    إذا (پنجره->flags & SDL_پنجره_OPENGL) {
        داده->egl_surface = SDL_EGL_CreateSurface(_this, پنجره, (Native_پنجره_Type)داده->native_پنجره);
        إذا (داده->egl_surface == EGL_NO_SURFACE) {
            SDL_free(داده);
            نتیجه = false;
            اذهب endfunction;
        }
    }
    SDL_مجموعه_اشاره_گر_Property(SDL_Get_پنجره_Properties(پنجره), SDL_PROP_پنجره_OPENHARMONY_SURFACE_اشاره_گر, داده->egl_surface);
#پایان_اگر

#إذا 0  // !!! FIXME
    SDL_مجموعه_پنجره_امن_Area_Insets(پنجره, Android_امن_Inset_چپ, Android_امن_Inset_راست, Android_امن_Inset_بالاترین, Android_امن_Inset_Bottom);
#پایان_اگر

    پنجره->داخلی = داده;
    OPENHARMONY_پنجره = پنجره;

endfunction:

    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //Android_UnlockActivityMutex();

    أرجع نتیجه;
}

فراغ OPENHARMONY_مجموعه_پنجره_Title(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
#إذا 0  // !!! FIXME
    Android_JNI_مجموعه_Activity_Title(پنجره->title);
#پایان_اگر
}

SDL_Fullscreen_نتیجه OPENHARMONY_مجموعه_پنجره_Fullscreen(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    إذا (پنجره == OPENHARMONY_پنجره) {
        ثابت bool show_bars = (fullscreen == SDL_FULLSCREEN_OP_LEAVE);
        إذا (!SDL_OpenHarmonyToggleSystemBars(show_bars, show_bars)) {
            أرجع SDL_FULLSCREEN_FAILED;
        }
        // !!! FIXME: make sure this causes an XComponent resize event, that we can pick up later.
        أرجع SDL_FULLSCREEN_PENDING;
    }
    أرجع SDL_FULLSCREEN_FAILED;
}

فراغ OPENHARMONY_Minimize_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
#إذا 0  // !!! FIXME
    Android_JNI_Minimize_پنجره();
#پایان_اگر
}

فراغ OPENHARMONY_مجموعه_پنجره_Resizable(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool resizable)
{
#إذا 0  // !!! FIXME
    // Set orientation
    Android_JNI_مجموعه_Orientation(پنجره->w, پنجره->h, پنجره->flags & SDL_پنجره_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));
#پایان_اگر
}

فراغ OPENHARMONY_Destroy_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //Android_LockActivityMutex();

    إذا (پنجره == OPENHARMONY_پنجره) {
        OPENHARMONY_پنجره = عدم;

        إذا (پنجره->داخلی) {
            SDL_پنجره_داده *داده = پنجره->داخلی;

#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
            إذا (داده->egl_surface != EGL_NO_SURFACE) {
                SDL_EGL_DestroySurface(_this, داده->egl_surface);
            }
#پایان_اگر

            // the XComponent and native window live past the SDL_Window; it can be reused for future windows.

            SDL_free(پنجره->داخلی);
            پنجره->داخلی = عدم;
        }
    }

    //Android_UnlockActivityMutex();
}

#پایان_اگر // SDL_VIDEO_DRIVER_OPENHARMONY
