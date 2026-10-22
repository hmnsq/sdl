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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_OPENHARMONY

// !!! FIXME: these are defined as "const uint32_t VARNAME = VALUE;" in native_interface_xcomponent.h, which becomes a global variable in _our_ C code! Maybe C++ handles this differently...?
#وصف_ڪريو OH_XCOMPONENT_ID_LEN_MAX sdl_ohoswindow_OH_XCOMPONENT_ID_LEN_MAX
#وصف_ڪريو OH_MAX_TOUCH_POINTS_عدد sdl_ohoswindow_OH_MAX_TOUCH_POINTS_عدد
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
SDL_دري *OPENHARMONY_دري = عدم;

bool OPENHARMONY_Create_دري(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID create_props)
{
    SDL_دري_معلومات *معلومات;
    bool نتيجو = true;

    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //if (!OPENHARMONY_WaitActiveAndLockActivity()) {
    //    return false;
    //}

    إذا (OPENHARMONY_دري) {
        نتيجو = SDL_سيٽ_Error("SDL on OpenHarmony (currently) only supports one window");
        اذهب endfunction;
    }

    فراغ *voidxcomp, *native_دري;
    SDL_Open_Harmony_Get_Native_دري_اشارا(&voidxcomp, &native_دري);
    OH_NativeXComponent *native_xcomponent = (OH_NativeXComponent *) voidxcomp;
    إذا (!native_xcomponent || !native_دري) {
        نتيجو = SDL_سيٽ_Error("Don't have Native XComponent or Native Window");
        اذهب endfunction;
    }

#إذا 0  // !!! FIXME
    // Set orientation
    Android_JNI_سيٽ_Orientation(دري->w, دري->h, دري->flags & SDL_دري_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));
#جيڪڏهن_پورو

    uint64_t w, h;
    OH_Native_XComponent_Get_XComponent_سائيز(native_xcomponent, native_دري, &w, &h);

    // Adjust the window data to match the screen
    دري->x = 0;
    دري->y = 0;
    دري->w = (صحيح) w;
    دري->h = (صحيح) h;

    // One window, it always has focus
    SDL_سيٽ_Mouse_Focus(دري);
    SDL_سيٽ_Keyboard_Focus(دري);

    معلومات = (SDL_دري_معلومات *)SDL_calloc(1, حجم(*معلومات));
    إذا (!معلومات) {
        نتيجو = false;
        اذهب endfunction;
    }

    معلومات->native_xcomponent = native_xcomponent;
    معلومات->native_دري = native_دري;
    SDL_سيٽ_اشارو_Property(SDL_Get_دري_Properties(دري), SDL_PROP_دري_OPENHARMONY_XCOMPONENT_اشارو, معلومات->native_xcomponent);
    SDL_سيٽ_اشارو_Property(SDL_Get_دري_Properties(دري), SDL_PROP_دري_OPENHARMONY_دري_اشارو, معلومات->native_دري);

    /* Do not create EGLSurface for Vulkan window since it will then make the window
       incompatible with vkCreateAndroidSurfaceKHR */
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
    إذا (دري->flags & SDL_دري_OPENGL) {
        معلومات->egl_surface = SDL_EGL_CreateSurface(_this, دري, (Native_دري_Type)معلومات->native_دري);
        إذا (معلومات->egl_surface == EGL_NO_SURFACE) {
            SDL_free(معلومات);
            نتيجو = false;
            اذهب endfunction;
        }
    }
    SDL_سيٽ_اشارو_Property(SDL_Get_دري_Properties(دري), SDL_PROP_دري_OPENHARMONY_SURFACE_اشارو, معلومات->egl_surface);
#جيڪڏهن_پورو

#إذا 0  // !!! FIXME
    SDL_سيٽ_دري_محفوظ_Area_Insets(دري, Android_محفوظ_Inset_کاٻو, Android_محفوظ_Inset_ساڄو, Android_محفوظ_Inset_چوٽي, Android_محفوظ_Inset_Bottom);
#جيڪڏهن_پورو

    دري->اندروني = معلومات;
    OPENHARMONY_دري = دري;

endfunction:

    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //Android_UnlockActivityMutex();

    أرجع نتيجو;
}

فراغ OPENHARMONY_سيٽ_دري_Title(SDL_VideoDevice *_this, SDL_دري *دري)
{
#إذا 0  // !!! FIXME
    Android_JNI_سيٽ_Activity_Title(دري->title);
#جيڪڏهن_پورو
}

SDL_Fullscreen_نتيجو OPENHARMONY_سيٽ_دري_Fullscreen(SDL_VideoDevice *_this, SDL_دري *دري, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    إذا (دري == OPENHARMONY_دري) {
        ثابت bool show_bars = (fullscreen == SDL_FULLSCREEN_OP_LEAVE);
        إذا (!SDL_OpenHarmonyToggleSystemBars(show_bars, show_bars)) {
            أرجع SDL_FULLSCREEN_FAILED;
        }
        // !!! FIXME: make sure this causes an XComponent resize event, that we can pick up later.
        أرجع SDL_FULLSCREEN_PENDING;
    }
    أرجع SDL_FULLSCREEN_FAILED;
}

فراغ OPENHARMONY_Minimize_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
#إذا 0  // !!! FIXME
    Android_JNI_Minimize_دري();
#جيڪڏهن_پورو
}

فراغ OPENHARMONY_سيٽ_دري_Resizable(SDL_VideoDevice *_this, SDL_دري *دري, bool resizable)
{
#إذا 0  // !!! FIXME
    // Set orientation
    Android_JNI_سيٽ_Orientation(دري->w, دري->h, دري->flags & SDL_دري_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));
#جيڪڏهن_پورو
}

فراغ OPENHARMONY_Destroy_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //Android_LockActivityMutex();

    إذا (دري == OPENHARMONY_دري) {
        OPENHARMONY_دري = عدم;

        إذا (دري->اندروني) {
            SDL_دري_معلومات *معلومات = دري->اندروني;

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
            إذا (معلومات->egl_surface != EGL_NO_SURFACE) {
                SDL_EGL_DestroySurface(_this, معلومات->egl_surface);
            }
#جيڪڏهن_پورو

            // the XComponent and native window live past the SDL_Window; it can be reused for future windows.

            SDL_free(دري->اندروني);
            دري->اندروني = عدم;
        }
    }

    //Android_UnlockActivityMutex();
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_OPENHARMONY
