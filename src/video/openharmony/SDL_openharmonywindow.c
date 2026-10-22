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

#که_تعریف_شوی SDL_VIDEO_DRIVER_OPENHARMONY

// !!! FIXME: these are defined as "const uint32_t VARNAME = VALUE;" in native_interface_xcomponent.h, which becomes a global variable in _our_ C code! Maybe C++ handles this differently...?
#تعریف_کړه OH_XCOMPONENT_ID_LEN_MAX sdl_ohoswindow_OH_XCOMPONENT_ID_LEN_MAX
#تعریف_کړه OH_MAX_TOUCH_POINTS_شمېره sdl_ohoswindow_OH_MAX_TOUCH_POINTS_شمېره
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
SDL_کړکۍ *OPENHARMONY_کړکۍ = عدم;

bool OPENHARMONY_Create_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID create_props)
{
    SDL_کړکۍ_معلومات *معلومات;
    bool پایله = true;

    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //if (!OPENHARMONY_WaitActiveAndLockActivity()) {
    //    return false;
    //}

    إذا (OPENHARMONY_کړکۍ) {
        پایله = SDL_سېټ_Error("SDL on OpenHarmony (currently) only supports one window");
        اذهب endfunction;
    }

    فراغ *voidxcomp, *native_کړکۍ;
    SDL_Open_Harmony_Get_Native_کړکۍ_اشارې(&voidxcomp, &native_کړکۍ);
    OH_NativeXComponent *native_xcomponent = (OH_NativeXComponent *) voidxcomp;
    إذا (!native_xcomponent || !native_کړکۍ) {
        پایله = SDL_سېټ_Error("Don't have Native XComponent or Native Window");
        اذهب endfunction;
    }

#إذا 0  // !!! FIXME
    // Set orientation
    Android_JNI_سېټ_Orientation(کړکۍ->w, کړکۍ->h, کړکۍ->flags & SDL_کړکۍ_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));
#د_که_پای

    uint64_t w, h;
    OH_Native_XComponent_Get_XComponent_اندازه(native_xcomponent, native_کړکۍ, &w, &h);

    // Adjust the window data to match the screen
    کړکۍ->x = 0;
    کړکۍ->y = 0;
    کړکۍ->w = (صحيح) w;
    کړکۍ->h = (صحيح) h;

    // One window, it always has focus
    SDL_سېټ_Mouse_Focus(کړکۍ);
    SDL_سېټ_Keyboard_Focus(کړکۍ);

    معلومات = (SDL_کړکۍ_معلومات *)SDL_calloc(1, حجم(*معلومات));
    إذا (!معلومات) {
        پایله = false;
        اذهب endfunction;
    }

    معلومات->native_xcomponent = native_xcomponent;
    معلومات->native_کړکۍ = native_کړکۍ;
    SDL_سېټ_اشاره_ګر_Property(SDL_Get_کړکۍ_Properties(کړکۍ), SDL_PROP_کړکۍ_OPENHARMONY_XCOMPONENT_اشاره_ګر, معلومات->native_xcomponent);
    SDL_سېټ_اشاره_ګر_Property(SDL_Get_کړکۍ_Properties(کړکۍ), SDL_PROP_کړکۍ_OPENHARMONY_کړکۍ_اشاره_ګر, معلومات->native_کړکۍ);

    /* Do not create EGLSurface for Vulkan window since it will then make the window
       incompatible with vkCreateAndroidSurfaceKHR */
#که_تعریف_شوی SDL_VIDEO_OPENGL_EGL
    إذا (کړکۍ->flags & SDL_کړکۍ_OPENGL) {
        معلومات->egl_surface = SDL_EGL_CreateSurface(_this, کړکۍ, (Native_کړکۍ_Type)معلومات->native_کړکۍ);
        إذا (معلومات->egl_surface == EGL_NO_SURFACE) {
            SDL_free(معلومات);
            پایله = false;
            اذهب endfunction;
        }
    }
    SDL_سېټ_اشاره_ګر_Property(SDL_Get_کړکۍ_Properties(کړکۍ), SDL_PROP_کړکۍ_OPENHARMONY_SURFACE_اشاره_ګر, معلومات->egl_surface);
#د_که_پای

#إذا 0  // !!! FIXME
    SDL_سېټ_کړکۍ_خوندي_Area_Insets(کړکۍ, Android_خوندي_Inset_کیڼ, Android_خوندي_Inset_ښی, Android_خوندي_Inset_سر, Android_خوندي_Inset_Bottom);
#د_که_پای

    کړکۍ->دننی = معلومات;
    OPENHARMONY_کړکۍ = کړکۍ;

endfunction:

    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //Android_UnlockActivityMutex();

    أرجع پایله;
}

فراغ OPENHARMONY_سېټ_کړکۍ_Title(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
#إذا 0  // !!! FIXME
    Android_JNI_سېټ_Activity_Title(کړکۍ->title);
#د_که_پای
}

SDL_Fullscreen_پایله OPENHARMONY_سېټ_کړکۍ_Fullscreen(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    إذا (کړکۍ == OPENHARMONY_کړکۍ) {
        ثابت bool show_bars = (fullscreen == SDL_FULLSCREEN_OP_LEAVE);
        إذا (!SDL_OpenHarmonyToggleSystemBars(show_bars, show_bars)) {
            أرجع SDL_FULLSCREEN_FAILED;
        }
        // !!! FIXME: make sure this causes an XComponent resize event, that we can pick up later.
        أرجع SDL_FULLSCREEN_PENDING;
    }
    أرجع SDL_FULLSCREEN_FAILED;
}

فراغ OPENHARMONY_Minimize_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
#إذا 0  // !!! FIXME
    Android_JNI_Minimize_کړکۍ();
#د_که_پای
}

فراغ OPENHARMONY_سېټ_کړکۍ_Resizable(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool resizable)
{
#إذا 0  // !!! FIXME
    // Set orientation
    Android_JNI_سېټ_Orientation(کړکۍ->w, کړکۍ->h, کړکۍ->flags & SDL_کړکۍ_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));
#د_که_پای
}

فراغ OPENHARMONY_Destroy_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //Android_LockActivityMutex();

    إذا (کړکۍ == OPENHARMONY_کړکۍ) {
        OPENHARMONY_کړکۍ = عدم;

        إذا (کړکۍ->دننی) {
            SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;

#که_تعریف_شوی SDL_VIDEO_OPENGL_EGL
            إذا (معلومات->egl_surface != EGL_NO_SURFACE) {
                SDL_EGL_DestroySurface(_this, معلومات->egl_surface);
            }
#د_که_پای

            // the XComponent and native window live past the SDL_Window; it can be reused for future windows.

            SDL_free(کړکۍ->دننی);
            کړکۍ->دننی = عدم;
        }
    }

    //Android_UnlockActivityMutex();
}

#د_که_پای // SDL_VIDEO_DRIVER_OPENHARMONY
