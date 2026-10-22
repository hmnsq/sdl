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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_RPI

/* References
 * http://elinux.org/RPi_VideoCore_APIs
 * https://github.com/raspberrypi/firmware/blob/master/opt/vc/src/hello_pi/hello_triangle/triangle.c
 * http://cgit.freedesktop.org/wayland/weston/tree/src/rpi-renderer.c
 * http://cgit.freedesktop.org/wayland/weston/tree/src/compositor-rpi.c
 */

// SDL internals
#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_keyboard_c.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_ಒಳಹರಿವು_LINUXEV
#ಅನ್ತರ್ಭಾವ "../../core/linux/SDL_evdev.h"
#ಆದರೆ_ಅಂತ್ಯ

// RPI declarations
#ಅನ್ತರ್ಭಾವ "SDL_rpivideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_rpievents_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_rpiopengles.h"
#ಅನ್ತರ್ಭಾವ "SDL_rpimouse.h"

ಸ್ಥಿರ ಶೂನ್ಯ RPI_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->ಆಂತರಿಕ);
    SDL_free(device);
}

ಸ್ಥಿರ ಶೂನ್ಯ RPI_Get_Refresh_ದರ(ಪೂರ್ಣಾಂಕ *numerator, ಪೂರ್ಣಾಂಕ *denominator)
{
    TV_DISPLAY_STATE_T tvstate;
    ಆದರೆ (vc_tv_get_display_state(&tvstate) == 0) {
        // The width/height parameters are in the same position in the union
        // for HDMI and SDTV
        HDMI_PROPERTY_PARAM_T property;
        property.property = HDMI_PROPERTY_PIXEL_CLOCK_TYPE;
        vc_tv_hdmi_get_property(&property);
        ಆದರೆ (property.param1 == HDMI_PIXEL_CLOCK_TYPE_NTSC) {
            *numerator = tvstate.display.hdmi.ಚೌಕಟ್ಟು_ದರ_2 * 1000;
            *denominator = 1001;
        } ಇಲ್ಲದಿದ್ದರೆ {
            *numerator = tvstate.display.hdmi.ಚೌಕಟ್ಟು_ದರ_2;
            *denominator = 1;
        }
        ಹಿಂತಿರುಗಿ;
    }

    // Failed to get display state, default to 60
    *numerator = 60;
    *denominator = 1;
}

ಸ್ಥಿರ SDL_VideoDevice *RPI_Create(ಶೂನ್ಯ)
{
    SDL_VideoDevice *device;
    SDL_Video_ದತ್ತಾಂಶ *phdata;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, ಗಾತ್ರ(SDL_VideoDevice));
    ಆದರೆ (!device) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    // Initialize internal data
    phdata = (SDL_Video_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_Video_ದತ್ತಾಂಶ));
    ಆದರೆ (!phdata) {
        SDL_free(device);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    device->ಆಂತರಿಕ = phdata;

    // Setup amount of available displays
    device->ಅಂಕೆ_displays = 0;

    // Set device free function
    device->ಬಿಡುಗಡೆ = RPI_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = RPI_VideoInit;
    device->VideoQuit = RPI_VideoQuit;
    device->CreateSDLWindow = RPI_Create_ಕಿಟಕಿ;
    device->ಗಣ_ಕಿಟಕಿ_Title = RPI_ಗಣ_ಕಿಟಕಿ_Title;
    device->ಗಣ_ಕಿಟಕಿ_Position = RPI_ಗಣ_ಕಿಟಕಿ_Position;
    device->ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ = RPI_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ;
    device->Show_ಕಿಟಕಿ = RPI_Show_ಕಿಟಕಿ;
    device->Hide_ಕಿಟಕಿ = RPI_Hide_ಕಿಟಕಿ;
    device->Raise_ಕಿಟಕಿ = RPI_Raise_ಕಿಟಕಿ;
    device->Maximize_ಕಿಟಕಿ = RPI_Maximize_ಕಿಟಕಿ;
    device->Minimize_ಕಿಟಕಿ = RPI_Minimize_ಕಿಟಕಿ;
    device->Restore_ಕಿಟಕಿ = RPI_Restore_ಕಿಟಕಿ;
    device->Destroy_ಕಿಟಕಿ = RPI_Destroy_ಕಿಟಕಿ;
    device->GL_ತುಂಬು_Library = RPI_GLES_ತುಂಬು_Library;
    device->GL_Get_Proc_ವಿಳಾಸ = RPI_GLES_Get_Proc_ವಿಳಾಸ;
    device->GL_UnloadLibrary = RPI_GLES_UnloadLibrary;
    device->GL_CreateContext = RPI_GLES_CreateContext;
    device->GL_MakeCurrent = RPI_GLES_MakeCurrent;
    device->GL_ಗಣ_ಅದಲುಬದಲು_Interval = RPI_GLES_ಗಣ_ಅದಲುಬದಲು_Interval;
    device->GL_Get_ಅದಲುಬದಲು_Interval = RPI_GLES_Get_ಅದಲುಬದಲು_Interval;
    device->GL_ಅದಲುಬದಲು_ಕಿಟಕಿ = RPI_GLES_ಅದಲುಬದಲು_ಕಿಟಕಿ;
    device->GL_DestroyContext = RPI_GLES_DestroyContext;
    device->GL_ಗಣ_Default_Profile_Config = RPI_GLES_ಗಣ_Default_Profile_Config;

    device->PumpEvents = RPI_PumpEvents;

    ಹಿಂತಿರುಗಿ device;
}

VideoBootStrap RPI_bootstrap = {
    "rpi",
    "RPI Video Driver",
    RPI_Create,
    ಖಾಲಿ, // no ShowMessageBox implementation
    false
};

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/*****************************************************************************/

ಸ್ಥಿರ ಶೂನ್ಯ ಕೂಡಿಸು_Disp_Man_XDisplay(ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ display_id)
{
    DISPMANX_MODEINFO_T modeinfo;
    DISPMANX_DISPLAY_HANDLE_T handle;
    SDL_VideoDisplay display;
    SDL_Display_ಬಹುಲಕ ಬಹುಲಕ;
    SDL_Display_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ;

    handle = vc_dispmanx_display_open(display_id);
    ಆದರೆ (!handle) {
        ಹಿಂತಿರುಗಿ; // this display isn't available
    }

    ಆದರೆ (vc_dispmanx_display_get_info(handle, &modeinfo) < 0) {
        vc_dispmanx_display_close(handle);
        ಹಿಂತಿರುಗಿ;
    }

    // RPI_GetRefreshRate() doesn't distinguish between displays. I'm not sure the hardware distinguishes either
    SDL_zero(ಬಹುಲಕ);
    ಬಹುಲಕ.w = modeinfo.ಅಗಲ;
    ಬಹುಲಕ.h = modeinfo.ಎತ್ತರ;
    RPI_Get_Refresh_ದರ(&ಬಹುಲಕ.refresh_ದರ_numerator, &ಬಹುಲಕ.refresh_ದರ_denominator);

    // 32 bpp for default
    ಬಹುಲಕ.format = SDL_PIXELFORMAT_ABGR8888;

    SDL_zero(display);
    display.desktop_ಬಹುಲಕ = ಬಹುಲಕ;

    // Allocate display internal data
    ದತ್ತಾಂಶ = (SDL_Display_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_Display_ದತ್ತಾಂಶ));
    ಆದರೆ (!ದತ್ತಾಂಶ) {
        vc_dispmanx_display_close(handle);
        ಹಿಂತಿರುಗಿ; // oh well
    }

    ದತ್ತಾಂಶ->dispman_display = handle;

    display.ಆಂತರಿಕ = ದತ್ತಾಂಶ;

    SDL_ಕೂಡಿಸು_Video_Display(&display, false);
}

bool RPI_VideoInit(SDL_VideoDevice *_this)
{
    // Initialize BCM Host
    bcm_host_init();

    ಕೂಡಿಸು_Disp_Man_XDisplay(DISPMANX_ID_MAIN_LCD);    // your default display
    ಕೂಡಿಸು_Disp_Man_XDisplay(DISPMANX_ID_FORCE_OTHER); // an "other" display...maybe DSI-connected screen while HDMI is your main

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_ಒಳಹರಿವು_LINUXEV
    ಆದರೆ (!SDL_EVDEV_Init()) {
        ಹಿಂತಿರುಗಿ false;
    }
#ಆದರೆ_ಅಂತ್ಯ

    RPI_InitMouse(_this);

    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ RPI_VideoQuit(SDL_VideoDevice *_this)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_ಒಳಹರಿವು_LINUXEV
    SDL_EVDEV_Quit();
#ಆದರೆ_ಅಂತ್ಯ
}

ಸ್ಥಿರ ಶೂನ್ಯ RPI_vsync_callback(DISPMANX_UPDATE_HANDLE_T u, ಶೂನ್ಯ *ದತ್ತಾಂಶ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wdata = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)ದತ್ತಾಂಶ;

    SDL_ಬೀಗ_Mutex(wdata->vsync_cond_mutex);
    SDL_SignalCondition(wdata->vsync_cond);
    SDL_UnlockMutex(wdata->vsync_cond_mutex);
}

bool RPI_Create_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID create_props)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wdata;
    SDL_VideoDisplay *display;
    SDL_Display_ದತ್ತಾಂಶ *displaydata;
    VC_RECT_T dst_rect;
    VC_RECT_T src_rect;
    VC_DISPMANX_ALPHA_T dispman_alpha;
    DISPMANX_UPDATE_HANDLE_T dispman_update;
    uint32_t layer = SDL_RPI_VIDEOLAYER;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *env;

    // Disable alpha, otherwise the app looks composed with whatever dispman is showing (X11, console,etc)
    dispman_alpha.flags = DISPMANX_FLAGS_ALPHA_FIXED_ALL_PIXELS;
    dispman_alpha.opacity = 0xFF;
    dispman_alpha.ಮುಖವಾಡ = 0;

    // Allocate window internal data
    wdata = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ));
    ಆದರೆ (!wdata) {
        ಹಿಂತಿರುಗಿ false;
    }
    display = SDL_Get_Video_Display_For_ಕಿಟಕಿ(ಕಿಟಕಿ);
    displaydata = display->ಆಂತರಿಕ;

    // Windows have one size for now
    ಕಿಟಕಿ->w = display->desktop_ಬಹುಲಕ.w;
    ಕಿಟಕಿ->h = display->desktop_ಬಹುಲಕ.h;

    // OpenGL ES is the law here, buddy
    ಕಿಟಕಿ->flags |= SDL_ಕಿಟಕಿ_OPENGL;

    // Create a dispman element and associate a window to it
    dst_rect.x = 0;
    dst_rect.y = 0;
    dst_rect.ಅಗಲ = ಕಿಟಕಿ->w;
    dst_rect.ಎತ್ತರ = ಕಿಟಕಿ->h;

    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.ಅಗಲ = ಕಿಟಕಿ->w << 16;
    src_rect.ಎತ್ತರ = ಕಿಟಕಿ->h << 16;

    env = SDL_GetHint(SDL_HINT_RPI_VIDEO_LAYER);
    ಆದರೆ (env) {
        layer = SDL_atoi(env);
    }

    dispman_update = vc_dispmanx_update_ಆರಂಭ(0);
    wdata->dispman_ಕಿಟಕಿ.element = vc_dispmanx_element_ಕೂಡಿಸು(dispman_update,
                                                            displaydata->dispman_display,
                                                            layer /* layer */,
                                                            &dst_rect,
                                                            0 /*src*/,
                                                            &src_rect,
                                                            DISPMANX_PROTECTION_NONE,
                                                            &dispman_alpha /*alpha*/,
                                                            0 /*clamp*/,
                                                            0 /*transform*/);
    wdata->dispman_ಕಿಟಕಿ.ಅಗಲ = ಕಿಟಕಿ->w;
    wdata->dispman_ಕಿಟಕಿ.ಎತ್ತರ = ಕಿಟಕಿ->h;
    vc_dispmanx_update_submit_sync(dispman_update);

    ಆದರೆ (!_this->egl_ದತ್ತಾಂಶ) {
        ಆದರೆ (!SDL_GL_ತುಂಬು_Library(ಖಾಲಿ)) {
            ಹಿಂತಿರುಗಿ false;
        }
    }
    wdata->egl_surface = SDL_EGL_CreateSurface(_this, ಕಿಟಕಿ, (Native_ಕಿಟಕಿ_Type)&wdata->dispman_ಕಿಟಕಿ);

    ಆದರೆ (wdata->egl_surface == EGL_NO_SURFACE) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Could not create GLES window surface");
    }

    // Start generating vsync callbacks if necessary
    wdata->double_ಬಫರ್ = false;
    ಆದರೆ (SDL_GetHintBoolean(SDL_HINT_VIDEO_DOUBLE_ಬಫರ್, false)) {
        wdata->vsync_cond = SDL_CreateCondition();
        wdata->vsync_cond_mutex = SDL_CreateMutex();
        wdata->double_ಬಫರ್ = true;
        vc_dispmanx_vsync_callback(displaydata->dispman_display, RPI_vsync_callback, (ಶೂನ್ಯ *)wdata);
    }

    // Setup driver data for this window
    ಕಿಟಕಿ->ಆಂತರಿಕ = wdata;

    // One window, it always has focus
    SDL_ಗಣ_Mouse_Focus(ಕಿಟಕಿ);
    SDL_ಗಣ_Keyboard_Focus(ಕಿಟಕಿ);

    // Window has been successfully created
    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ RPI_Destroy_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    SDL_Display_ದತ್ತಾಂಶ *displaydata = SDL_Get_Display_Driver_ದತ್ತಾಂಶ_For_ಕಿಟಕಿ(ಕಿಟಕಿ);

    ಆದರೆ (ದತ್ತಾಂಶ) {
        ಆದರೆ (ದತ್ತಾಂಶ->double_ಬಫರ್) {
            // Wait for vsync, and then stop vsync callbacks and destroy related stuff, if needed
            SDL_ಬೀಗ_Mutex(ದತ್ತಾಂಶ->vsync_cond_mutex);
            SDL_WaitCondition(ದತ್ತಾಂಶ->vsync_cond, ದತ್ತಾಂಶ->vsync_cond_mutex);
            SDL_UnlockMutex(ದತ್ತಾಂಶ->vsync_cond_mutex);

            vc_dispmanx_vsync_callback(displaydata->dispman_display, ಖಾಲಿ, ಖಾಲಿ);

            SDL_DestroyCondition(ದತ್ತಾಂಶ->vsync_cond);
            SDL_DestroyMutex(ದತ್ತಾಂಶ->vsync_cond_mutex);
        }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
        ಆದರೆ (ದತ್ತಾಂಶ->egl_surface != EGL_NO_SURFACE) {
            SDL_EGL_DestroySurface(_this, ದತ್ತಾಂಶ->egl_surface);
        }
#ಆದರೆ_ಅಂತ್ಯ
        SDL_free(ದತ್ತಾಂಶ);
        ಕಿಟಕಿ->ಆಂತರಿಕ = ಖಾಲಿ;
    }
}

ಶೂನ್ಯ RPI_ಗಣ_ಕಿಟಕಿ_Title(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
}
bool RPI_ಗಣ_ಕಿಟಕಿ_Position(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಹಿಂತಿರುಗಿ SDL_Unsupported();
}
ಶೂನ್ಯ RPI_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
}
ಶೂನ್ಯ RPI_Show_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
}
ಶೂನ್ಯ RPI_Hide_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
}
ಶೂನ್ಯ RPI_Raise_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
}
ಶೂನ್ಯ RPI_Maximize_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
}
ಶೂನ್ಯ RPI_Minimize_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
}
ಶೂನ್ಯ RPI_Restore_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_RPI
