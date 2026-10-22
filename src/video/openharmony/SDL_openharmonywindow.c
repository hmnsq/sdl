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

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_OPENHARMONY

// !!! FIXME: these are defined as "const uint32_t VARNAME = VALUE;" in native_interface_xcomponent.h, which becomes a global variable in _our_ C code! Maybe C++ handles this differently...?
#تعریف_کرو OH_XCOMPONENT_ID_LEN_MAX sdl_ohoswindow_OH_XCOMPONENT_ID_LEN_MAX
#تعریف_کرو OH_MAX_TOUCH_POINTS_نمبر sdl_ohoswindow_OH_MAX_TOUCH_POINTS_نمبر
#شامل <ace/xcomponent/native_interface_xcomponent.h>

#شامل "../SDL_sysvideo.h"
#شامل "../../events/SDL_keyboard_c.h"
#شامل "../../events/SDL_mouse_c.h"
#شامل "../../events/SDL_windowevents_c.h"
#شامل "../../core/openharmony/SDL_openharmony.h"

#شامل "SDL_openharmonyvideo.h"
#شامل "SDL_openharmonyevents.h"
#شامل "SDL_openharmonywindow.h"


// Currently only one window
SDL_کھڑکی *OPENHARMONY_کھڑکی = تہی;

bool OPENHARMONY_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا;
    bool نتیجہ = true;

    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //if (!OPENHARMONY_WaitActiveAndLockActivity()) {
    //    return false;
    //}

    اگر (OPENHARMONY_کھڑکی) {
        نتیجہ = SDL_سیٹ_Error("SDL on OpenHarmony (currently) only supports one window");
        جاؤ endfunction;
    }

    خالی *voidxcomp, *native_کھڑکی;
    SDL_Open_Harmony_Get_Native_کھڑکی_اشارے(&voidxcomp, &native_کھڑکی);
    OH_NativeXComponent *native_xcomponent = (OH_NativeXComponent *) voidxcomp;
    اگر (!native_xcomponent || !native_کھڑکی) {
        نتیجہ = SDL_سیٹ_Error("Don't have Native XComponent or Native Window");
        جاؤ endfunction;
    }

#اگر 0  // !!! FIXME
    // Set orientation
    Android_JNI_سیٹ_Orientation(کھڑکی->w, کھڑکی->h, کھڑکی->flags & SDL_کھڑکی_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));
#اگر_ختم

    uint64_t w, h;
    OH_Native_XComponent_Get_XComponent_سائز(native_xcomponent, native_کھڑکی, &w, &h);

    // Adjust the window data to match the screen
    کھڑکی->x = 0;
    کھڑکی->y = 0;
    کھڑکی->w = (صحیح) w;
    کھڑکی->h = (صحیح) h;

    // One window, it always has focus
    SDL_سیٹ_Mouse_Focus(کھڑکی);
    SDL_سیٹ_Keyboard_Focus(کھڑکی);

    ڈیٹا = (SDL_کھڑکی_ڈیٹا *)SDL_calloc(1, حجم(*ڈیٹا));
    اگر (!ڈیٹا) {
        نتیجہ = false;
        جاؤ endfunction;
    }

    ڈیٹا->native_xcomponent = native_xcomponent;
    ڈیٹا->native_کھڑکی = native_کھڑکی;
    SDL_سیٹ_اشارہ_گر_Property(SDL_Get_کھڑکی_Properties(کھڑکی), SDL_PROP_کھڑکی_OPENHARMONY_XCOMPONENT_اشارہ_گر, ڈیٹا->native_xcomponent);
    SDL_سیٹ_اشارہ_گر_Property(SDL_Get_کھڑکی_Properties(کھڑکی), SDL_PROP_کھڑکی_OPENHARMONY_کھڑکی_اشارہ_گر, ڈیٹا->native_کھڑکی);

    /* Do not create EGLSurface for Vulkan window since it will then make the window
       incompatible with vkCreateAndroidSurfaceKHR */
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    اگر (کھڑکی->flags & SDL_کھڑکی_OPENGL) {
        ڈیٹا->egl_surface = SDL_EGL_CreateSurface(_this, کھڑکی, (Native_کھڑکی_Type)ڈیٹا->native_کھڑکی);
        اگر (ڈیٹا->egl_surface == EGL_NO_SURFACE) {
            SDL_free(ڈیٹا);
            نتیجہ = false;
            جاؤ endfunction;
        }
    }
    SDL_سیٹ_اشارہ_گر_Property(SDL_Get_کھڑکی_Properties(کھڑکی), SDL_PROP_کھڑکی_OPENHARMONY_SURFACE_اشارہ_گر, ڈیٹا->egl_surface);
#اگر_ختم

#اگر 0  // !!! FIXME
    SDL_سیٹ_کھڑکی_محفوظ_Area_Insets(کھڑکی, Android_محفوظ_Inset_بایاں, Android_محفوظ_Inset_دایاں, Android_محفوظ_Inset_چوٹی, Android_محفوظ_Inset_Bottom);
#اگر_ختم

    کھڑکی->اندرونی_2 = ڈیٹا;
    OPENHARMONY_کھڑکی = کھڑکی;

endfunction:

    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //Android_UnlockActivityMutex();

    واپس نتیجہ;
}

خالی OPENHARMONY_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
#اگر 0  // !!! FIXME
    Android_JNI_سیٹ_Activity_Title(کھڑکی->title);
#اگر_ختم
}

SDL_Fullscreen_نتیجہ OPENHARMONY_سیٹ_کھڑکی_Fullscreen(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    اگر (کھڑکی == OPENHARMONY_کھڑکی) {
        ثابت bool show_bars = (fullscreen == SDL_FULLSCREEN_OP_LEAVE);
        اگر (!SDL_OpenHarmonyToggleSystemBars(show_bars, show_bars)) {
            واپس SDL_FULLSCREEN_FAILED;
        }
        // !!! FIXME: make sure this causes an XComponent resize event, that we can pick up later.
        واپس SDL_FULLSCREEN_PENDING;
    }
    واپس SDL_FULLSCREEN_FAILED;
}

خالی OPENHARMONY_Minimize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
#اگر 0  // !!! FIXME
    Android_JNI_Minimize_کھڑکی();
#اگر_ختم
}

خالی OPENHARMONY_سیٹ_کھڑکی_Resizable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool resizable)
{
#اگر 0  // !!! FIXME
    // Set orientation
    Android_JNI_سیٹ_Orientation(کھڑکی->w, کھڑکی->h, کھڑکی->flags & SDL_کھڑکی_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));
#اگر_ختم
}

خالی OPENHARMONY_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //Android_LockActivityMutex();

    اگر (کھڑکی == OPENHARMONY_کھڑکی) {
        OPENHARMONY_کھڑکی = تہی;

        اگر (کھڑکی->اندرونی_2) {
            SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
            اگر (ڈیٹا->egl_surface != EGL_NO_SURFACE) {
                SDL_EGL_DestroySurface(_this, ڈیٹا->egl_surface);
            }
#اگر_ختم

            // the XComponent and native window live past the SDL_Window; it can be reused for future windows.

            SDL_free(کھڑکی->اندرونی_2);
            کھڑکی->اندرونی_2 = تہی;
        }
    }

    //Android_UnlockActivityMutex();
}

#اگر_ختم // SDL_VIDEO_DRIVER_OPENHARMONY
