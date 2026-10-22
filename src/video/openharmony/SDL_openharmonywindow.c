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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_OPENHARMONY

// !!! FIXME: these are defined as "const uint32_t VARNAME = VALUE;" in native_interface_xcomponent.h, which becomes a global variable in _our_ C code! Maybe C++ handles this differently...?
#परिभाषय OH_XCOMPONENT_ID_LEN_MAX sdl_ohoswindow_OH_XCOMPONENT_ID_LEN_MAX
#परिभाषय OH_MAX_TOUCH_POINTS_सङ्ख्या sdl_ohoswindow_OH_MAX_TOUCH_POINTS_सङ्ख्या
#अन्तर्भाव <ace/xcomponent/native_interface_xcomponent.h>

#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../../events/SDL_keyboard_c.h"
#अन्तर्भाव "../../events/SDL_mouse_c.h"
#अन्तर्भाव "../../events/SDL_windowevents_c.h"
#अन्तर्भाव "../../core/openharmony/SDL_openharmony.h"

#अन्तर्भाव "SDL_openharmonyvideo.h"
#अन्तर्भाव "SDL_openharmonyevents.h"
#अन्तर्भाव "SDL_openharmonywindow.h"


// Currently only one window
SDL_गवाक्षः *OPENHARMONY_गवाक्षः = रिक्त;

bool OPENHARMONY_Create_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID create_props)
{
    SDL_गवाक्षः_दत्त *दत्त;
    bool परिणाम = true;

    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //if (!OPENHARMONY_WaitActiveAndLockActivity()) {
    //    return false;
    //}

    यदि (OPENHARMONY_गवाक्षः) {
        परिणाम = SDL_समुच्चयः_Error("SDL on OpenHarmony (currently) only supports one window");
        गच्छ endfunction;
    }

    शून्य *voidxcomp, *native_गवाक्षः;
    SDL_Open_Harmony_Get_Native_गवाक्षः_सूचकाः(&voidxcomp, &native_गवाक्षः);
    OH_NativeXComponent *native_xcomponent = (OH_NativeXComponent *) voidxcomp;
    यदि (!native_xcomponent || !native_गवाक्षः) {
        परिणाम = SDL_समुच्चयः_Error("Don't have Native XComponent or Native Window");
        गच्छ endfunction;
    }

#यदि 0  // !!! FIXME
    // Set orientation
    Android_JNI_समुच्चयः_Orientation(गवाक्षः->w, गवाक्षः->h, गवाक्षः->flags & SDL_गवाक्षः_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));
#यदि_अन्तः

    uint64_t w, h;
    OH_Native_XComponent_Get_XComponent_आकार(native_xcomponent, native_गवाक्षः, &w, &h);

    // Adjust the window data to match the screen
    गवाक्षः->x = 0;
    गवाक्षः->y = 0;
    गवाक्षः->w = (पूर्णाङ्क) w;
    गवाक्षः->h = (पूर्णाङ्क) h;

    // One window, it always has focus
    SDL_समुच्चयः_Mouse_Focus(गवाक्षः);
    SDL_समुच्चयः_Keyboard_Focus(गवाक्षः);

    दत्त = (SDL_गवाक्षः_दत्त *)SDL_calloc(1, परिमाण(*दत्त));
    यदि (!दत्त) {
        परिणाम = false;
        गच्छ endfunction;
    }

    दत्त->native_xcomponent = native_xcomponent;
    दत्त->native_गवाक्षः = native_गवाक्षः;
    SDL_समुच्चयः_Pointer_Property(SDL_Get_गवाक्षः_Properties(गवाक्षः), SDL_PROP_गवाक्षः_OPENHARMONY_XCOMPONENT_POINTER, दत्त->native_xcomponent);
    SDL_समुच्चयः_Pointer_Property(SDL_Get_गवाक्षः_Properties(गवाक्षः), SDL_PROP_गवाक्षः_OPENHARMONY_गवाक्षः_POINTER, दत्त->native_गवाक्षः);

    /* Do not create EGLSurface for Vulkan window since it will then make the window
       incompatible with vkCreateAndroidSurfaceKHR */
#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
    यदि (गवाक्षः->flags & SDL_गवाक्षः_OPENGL) {
        दत्त->egl_surface = SDL_EGL_CreateSurface(_this, गवाक्षः, (Native_गवाक्षः_Type)दत्त->native_गवाक्षः);
        यदि (दत्त->egl_surface == EGL_NO_SURFACE) {
            SDL_free(दत्त);
            परिणाम = false;
            गच्छ endfunction;
        }
    }
    SDL_समुच्चयः_Pointer_Property(SDL_Get_गवाक्षः_Properties(गवाक्षः), SDL_PROP_गवाक्षः_OPENHARMONY_SURFACE_POINTER, दत्त->egl_surface);
#यदि_अन्तः

#यदि 0  // !!! FIXME
    SDL_समुच्चयः_गवाक्षः_Safe_Area_Insets(गवाक्षः, Android_Safe_Inset_वामः, Android_Safe_Inset_दक्षिणः, Android_Safe_Inset_शिखरम्, Android_SafeInsetBottom);
#यदि_अन्तः

    गवाक्षः->आन्तरिकम् = दत्त;
    OPENHARMONY_गवाक्षः = गवाक्षः;

endfunction:

    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //Android_UnlockActivityMutex();

    प्रत्यागम परिणाम;
}

शून्य OPENHARMONY_समुच्चयः_गवाक्षः_Title(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
#यदि 0  // !!! FIXME
    Android_JNI_समुच्चयः_Activity_Title(गवाक्षः->title);
#यदि_अन्तः
}

SDL_Fullscreen_परिणाम OPENHARMONY_समुच्चयः_गवाक्षः_Fullscreen(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    यदि (गवाक्षः == OPENHARMONY_गवाक्षः) {
        ध्रुव bool show_bars = (fullscreen == SDL_FULLSCREEN_OP_LEAVE);
        यदि (!SDL_OpenHarmonyToggleSystemBars(show_bars, show_bars)) {
            प्रत्यागम SDL_FULLSCREEN_FAILED;
        }
        // !!! FIXME: make sure this causes an XComponent resize event, that we can pick up later.
        प्रत्यागम SDL_FULLSCREEN_PENDING;
    }
    प्रत्यागम SDL_FULLSCREEN_FAILED;
}

शून्य OPENHARMONY_Minimize_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
#यदि 0  // !!! FIXME
    Android_JNI_Minimize_गवाक्षः();
#यदि_अन्तः
}

शून्य OPENHARMONY_समुच्चयः_गवाक्षः_Resizable(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool resizable)
{
#यदि 0  // !!! FIXME
    // Set orientation
    Android_JNI_समुच्चयः_Orientation(गवाक्षः->w, गवाक्षः->h, गवाक्षः->flags & SDL_गवाक्षः_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));
#यदि_अन्तः
}

शून्य OPENHARMONY_Destroy_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //Android_LockActivityMutex();

    यदि (गवाक्षः == OPENHARMONY_गवाक्षः) {
        OPENHARMONY_गवाक्षः = रिक्त;

        यदि (गवाक्षः->आन्तरिकम्) {
            SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;

#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
            यदि (दत्त->egl_surface != EGL_NO_SURFACE) {
                SDL_EGL_DestroySurface(_this, दत्त->egl_surface);
            }
#यदि_अन्तः

            // the XComponent and native window live past the SDL_Window; it can be reused for future windows.

            SDL_free(गवाक्षः->आन्तरिकम्);
            गवाक्षः->आन्तरिकम् = रिक्त;
        }
    }

    //Android_UnlockActivityMutex();
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_OPENHARMONY
