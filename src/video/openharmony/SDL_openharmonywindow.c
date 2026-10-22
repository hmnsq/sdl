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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_OPENHARMONY

// !!! FIXME: these are defined as "const uint32_t VARNAME = VALUE;" in native_interface_xcomponent.h, which becomes a global variable in _our_ C code! Maybe C++ handles this differently...?
#تعریف_کرو OH_XCOMPONENT_ID_LEN_MAX sdl_ohoswindow_OH_XCOMPONENT_ID_LEN_MAX
#تعریف_کرو OH_MAX_TOUCH_POINTS_نمبر sdl_ohoswindow_OH_MAX_TOUCH_POINTS_نمبر
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
SDL_کھڑکی *OPENHARMONY_کھڑکی = عدم;

bool OPENHARMONY_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props)
{
    SDL_کھڑکی_انکڑے *انکڑے;
    bool نتیجہ = true;

    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //if (!OPENHARMONY_WaitActiveAndLockActivity()) {
    //    return false;
    //}

    إذا (OPENHARMONY_کھڑکی) {
        نتیجہ = SDL_سیٹ_Error("SDL on OpenHarmony (currently) only supports one window");
        اذهب endfunction;
    }

    فراغ *voidxcomp, *native_کھڑکی;
    SDL_Open_Harmony_Get_Native_کھڑکی_سوچکاں(&voidxcomp, &native_کھڑکی);
    OH_NativeXComponent *native_xcomponent = (OH_NativeXComponent *) voidxcomp;
    إذا (!native_xcomponent || !native_کھڑکی) {
        نتیجہ = SDL_سیٹ_Error("Don't have Native XComponent or Native Window");
        اذهب endfunction;
    }

#إذا 0  // !!! FIXME
    // Set orientation
    Android_JNI_سیٹ_Orientation(کھڑکی->w, کھڑکی->h, کھڑکی->flags & SDL_کھڑکی_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));
#جے_انت

    uint64_t w, h;
    OH_Native_XComponent_Get_XComponent_ناپ(native_xcomponent, native_کھڑکی, &w, &h);

    // Adjust the window data to match the screen
    کھڑکی->x = 0;
    کھڑکی->y = 0;
    کھڑکی->w = (صحيح) w;
    کھڑکی->h = (صحيح) h;

    // One window, it always has focus
    SDL_سیٹ_Mouse_Focus(کھڑکی);
    SDL_سیٹ_Keyboard_Focus(کھڑکی);

    انکڑے = (SDL_کھڑکی_انکڑے *)SDL_calloc(1, حجم(*انکڑے));
    إذا (!انکڑے) {
        نتیجہ = false;
        اذهب endfunction;
    }

    انکڑے->native_xcomponent = native_xcomponent;
    انکڑے->native_کھڑکی = native_کھڑکی;
    SDL_سیٹ_اشارہ_گر_Property(SDL_Get_کھڑکی_Properties(کھڑکی), SDL_PROP_کھڑکی_OPENHARMONY_XCOMPONENT_اشارہ_گر, انکڑے->native_xcomponent);
    SDL_سیٹ_اشارہ_گر_Property(SDL_Get_کھڑکی_Properties(کھڑکی), SDL_PROP_کھڑکی_OPENHARMONY_کھڑکی_اشارہ_گر, انکڑے->native_کھڑکی);

    /* Do not create EGLSurface for Vulkan window since it will then make the window
       incompatible with vkCreateAndroidSurfaceKHR */
#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    إذا (کھڑکی->flags & SDL_کھڑکی_OPENGL) {
        انکڑے->egl_surface = SDL_EGL_CreateSurface(_this, کھڑکی, (Native_کھڑکی_Type)انکڑے->native_کھڑکی);
        إذا (انکڑے->egl_surface == EGL_NO_SURFACE) {
            SDL_free(انکڑے);
            نتیجہ = false;
            اذهب endfunction;
        }
    }
    SDL_سیٹ_اشارہ_گر_Property(SDL_Get_کھڑکی_Properties(کھڑکی), SDL_PROP_کھڑکی_OPENHARMONY_SURFACE_اشارہ_گر, انکڑے->egl_surface);
#جے_انت

#إذا 0  // !!! FIXME
    SDL_سیٹ_کھڑکی_محفوظ_Area_Insets(کھڑکی, Android_محفوظ_Inset_بایاں, Android_محفوظ_Inset_دایاں, Android_محفوظ_Inset_چوٹی, Android_محفوظ_Inset_Bottom);
#جے_انت

    کھڑکی->اندرونی = انکڑے;
    OPENHARMONY_کھڑکی = کھڑکی;

endfunction:

    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //Android_UnlockActivityMutex();

    أرجع نتیجہ;
}

فراغ OPENHARMONY_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
#إذا 0  // !!! FIXME
    Android_JNI_سیٹ_Activity_Title(کھڑکی->title);
#جے_انت
}

SDL_Fullscreen_نتیجہ OPENHARMONY_سیٹ_کھڑکی_Fullscreen(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    إذا (کھڑکی == OPENHARMONY_کھڑکی) {
        ثابت bool show_bars = (fullscreen == SDL_FULLSCREEN_OP_LEAVE);
        إذا (!SDL_OpenHarmonyToggleSystemBars(show_bars, show_bars)) {
            أرجع SDL_FULLSCREEN_FAILED;
        }
        // !!! FIXME: make sure this causes an XComponent resize event, that we can pick up later.
        أرجع SDL_FULLSCREEN_PENDING;
    }
    أرجع SDL_FULLSCREEN_FAILED;
}

فراغ OPENHARMONY_Minimize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
#إذا 0  // !!! FIXME
    Android_JNI_Minimize_کھڑکی();
#جے_انت
}

فراغ OPENHARMONY_سیٹ_کھڑکی_Resizable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool resizable)
{
#إذا 0  // !!! FIXME
    // Set orientation
    Android_JNI_سیٹ_Orientation(کھڑکی->w, کھڑکی->h, کھڑکی->flags & SDL_کھڑکی_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));
#جے_انت
}

فراغ OPENHARMONY_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //Android_LockActivityMutex();

    إذا (کھڑکی == OPENHARMONY_کھڑکی) {
        OPENHARMONY_کھڑکی = عدم;

        إذا (کھڑکی->اندرونی) {
            SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;

#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
            إذا (انکڑے->egl_surface != EGL_NO_SURFACE) {
                SDL_EGL_DestroySurface(_this, انکڑے->egl_surface);
            }
#جے_انت

            // the XComponent and native window live past the SDL_Window; it can be reused for future windows.

            SDL_free(کھڑکی->اندرونی);
            کھڑکی->اندرونی = عدم;
        }
    }

    //Android_UnlockActivityMutex();
}

#جے_انت // SDL_VIDEO_DRIVER_OPENHARMONY
