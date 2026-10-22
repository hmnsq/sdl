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

#నిర్వచితమైతే SDL_VIDEO_DRIVER_OPENHARMONY

// !!! FIXME: these are defined as "const uint32_t VARNAME = VALUE;" in native_interface_xcomponent.h, which becomes a global variable in _our_ C code! Maybe C++ handles this differently...?
#నిర్వచించు OH_XCOMPONENT_ID_LEN_MAX sdl_ohoswindow_OH_XCOMPONENT_ID_LEN_MAX
#నిర్వచించు OH_MAX_TOUCH_POINTS_సంఖ్య sdl_ohoswindow_OH_MAX_TOUCH_POINTS_సంఖ్య
#అన్తర్భావ <ace/xcomponent/native_interface_xcomponent.h>

#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "../../events/SDL_keyboard_c.h"
#అన్తర్భావ "../../events/SDL_mouse_c.h"
#అన్తర్భావ "../../events/SDL_windowevents_c.h"
#అన్తర్భావ "../../core/openharmony/SDL_openharmony.h"

#అన్తర్భావ "SDL_openharmonyvideo.h"
#అన్తర్భావ "SDL_openharmonyevents.h"
#అన్తర్భావ "SDL_openharmonywindow.h"


// Currently only one window
SDL_కిటికీ *OPENHARMONY_కిటికీ = ఖాళీ;

bool OPENHARMONY_Create_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID create_props)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం;
    bool ఫలితం = true;

    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //if (!OPENHARMONY_WaitActiveAndLockActivity()) {
    //    return false;
    //}

    ఒకవేళ (OPENHARMONY_కిటికీ) {
        ఫలితం = SDL_సమితి_Error("SDL on OpenHarmony (currently) only supports one window");
        వెళ్ళు endfunction;
    }

    శూన్య *voidxcomp, *native_కిటికీ;
    SDL_Open_Harmony_Get_Native_కిటికీ_సూచికలు(&voidxcomp, &native_కిటికీ);
    OH_NativeXComponent *native_xcomponent = (OH_NativeXComponent *) voidxcomp;
    ఒకవేళ (!native_xcomponent || !native_కిటికీ) {
        ఫలితం = SDL_సమితి_Error("Don't have Native XComponent or Native Window");
        వెళ్ళు endfunction;
    }

#ఒకవేళ 0  // !!! FIXME
    // Set orientation
    Android_JNI_సమితి_Orientation(కిటికీ->w, కిటికీ->h, కిటికీ->flags & SDL_కిటికీ_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));
#అయితే_ముగింపు

    uint64_t w, h;
    OH_Native_XComponent_Get_XComponent_కొలత(native_xcomponent, native_కిటికీ, &w, &h);

    // Adjust the window data to match the screen
    కిటికీ->x = 0;
    కిటికీ->y = 0;
    కిటికీ->w = (పూర్ణాంకం) w;
    కిటికీ->h = (పూర్ణాంకం) h;

    // One window, it always has focus
    SDL_సమితి_Mouse_Focus(కిటికీ);
    SDL_సమితి_Keyboard_Focus(కిటికీ);

    దత్తాంశం = (SDL_కిటికీ_దత్తాంశం *)SDL_calloc(1, పరిమాణం(*దత్తాంశం));
    ఒకవేళ (!దత్తాంశం) {
        ఫలితం = false;
        వెళ్ళు endfunction;
    }

    దత్తాంశం->native_xcomponent = native_xcomponent;
    దత్తాంశం->native_కిటికీ = native_కిటికీ;
    SDL_సమితి_సూచిక_Property(SDL_Get_కిటికీ_Properties(కిటికీ), SDL_PROP_కిటికీ_OPENHARMONY_XCOMPONENT_సూచిక, దత్తాంశం->native_xcomponent);
    SDL_సమితి_సూచిక_Property(SDL_Get_కిటికీ_Properties(కిటికీ), SDL_PROP_కిటికీ_OPENHARMONY_కిటికీ_సూచిక, దత్తాంశం->native_కిటికీ);

    /* Do not create EGLSurface for Vulkan window since it will then make the window
       incompatible with vkCreateAndroidSurfaceKHR */
#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_OPENGL) {
        దత్తాంశం->egl_surface = SDL_EGL_CreateSurface(_this, కిటికీ, (Native_కిటికీ_Type)దత్తాంశం->native_కిటికీ);
        ఒకవేళ (దత్తాంశం->egl_surface == EGL_NO_SURFACE) {
            SDL_free(దత్తాంశం);
            ఫలితం = false;
            వెళ్ళు endfunction;
        }
    }
    SDL_సమితి_సూచిక_Property(SDL_Get_కిటికీ_Properties(కిటికీ), SDL_PROP_కిటికీ_OPENHARMONY_SURFACE_సూచిక, దత్తాంశం->egl_surface);
#అయితే_ముగింపు

#ఒకవేళ 0  // !!! FIXME
    SDL_సమితి_కిటికీ_సురక్షిత_Area_Insets(కిటికీ, Android_సురక్షిత_Inset_ఎడమ, Android_సురక్షిత_Inset_కుడి, Android_సురక్షిత_Inset_శిఖరం, Android_సురక్షిత_Inset_Bottom);
#అయితే_ముగింపు

    కిటికీ->అంతర్గత = దత్తాంశం;
    OPENHARMONY_కిటికీ = కిటికీ;

endfunction:

    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //Android_UnlockActivityMutex();

    తిరిగి ఫలితం;
}

శూన్య OPENHARMONY_సమితి_కిటికీ_Title(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
#ఒకవేళ 0  // !!! FIXME
    Android_JNI_సమితి_Activity_Title(కిటికీ->title);
#అయితే_ముగింపు
}

SDL_Fullscreen_ఫలితం OPENHARMONY_సమితి_కిటికీ_Fullscreen(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    ఒకవేళ (కిటికీ == OPENHARMONY_కిటికీ) {
        స్థిరరాశి bool show_bars = (fullscreen == SDL_FULLSCREEN_OP_LEAVE);
        ఒకవేళ (!SDL_OpenHarmonyToggleSystemBars(show_bars, show_bars)) {
            తిరిగి SDL_FULLSCREEN_FAILED;
        }
        // !!! FIXME: make sure this causes an XComponent resize event, that we can pick up later.
        తిరిగి SDL_FULLSCREEN_PENDING;
    }
    తిరిగి SDL_FULLSCREEN_FAILED;
}

శూన్య OPENHARMONY_Minimize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
#ఒకవేళ 0  // !!! FIXME
    Android_JNI_Minimize_కిటికీ();
#అయితే_ముగింపు
}

శూన్య OPENHARMONY_సమితి_కిటికీ_Resizable(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool resizable)
{
#ఒకవేళ 0  // !!! FIXME
    // Set orientation
    Android_JNI_సమితి_Orientation(కిటికీ->w, కిటికీ->h, కిటికీ->flags & SDL_కిటికీ_RESIZABLE, SDL_GetHint(SDL_HINT_ORIENTATIONS));
#అయితే_ముగింపు
}

శూన్య OPENHARMONY_Destroy_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    // !!! FIXME: Android has locking here; maybe it isn't necessary for OpenHarmony? What happens if we're in a background thread?
    //Android_LockActivityMutex();

    ఒకవేళ (కిటికీ == OPENHARMONY_కిటికీ) {
        OPENHARMONY_కిటికీ = ఖాళీ;

        ఒకవేళ (కిటికీ->అంతర్గత) {
            SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;

#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
            ఒకవేళ (దత్తాంశం->egl_surface != EGL_NO_SURFACE) {
                SDL_EGL_DestroySurface(_this, దత్తాంశం->egl_surface);
            }
#అయితే_ముగింపు

            // the XComponent and native window live past the SDL_Window; it can be reused for future windows.

            SDL_free(కిటికీ->అంతర్గత);
            కిటికీ->అంతర్గత = ఖాళీ;
        }
    }

    //Android_UnlockActivityMutex();
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_OPENHARMONY
