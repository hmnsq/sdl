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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_RPI

/* References
 * http://elinux.org/RPi_VideoCore_APIs
 * https://github.com/raspberrypi/firmware/blob/master/opt/vc/src/hello_pi/hello_triangle/triangle.c
 * http://cgit.freedesktop.org/wayland/weston/tree/src/rpi-renderer.c
 * http://cgit.freedesktop.org/wayland/weston/tree/src/compositor-rpi.c
 */

// SDL internals
#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../../events/SDL_mouse_c.h"
#अन्तर्भाव "../../events/SDL_keyboard_c.h"

#यदि_परिभाषितम् SDL_निवेशः_LINUXEV
#अन्तर्भाव "../../core/linux/SDL_evdev.h"
#यदि_अन्तः

// RPI declarations
#अन्तर्भाव "SDL_rpivideo.h"
#अन्तर्भाव "SDL_rpievents_c.h"
#अन्तर्भाव "SDL_rpiopengles.h"
#अन्तर्भाव "SDL_rpimouse.h"

स्थिर शून्य RPI_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->आन्तरिकम्);
    SDL_free(device);
}

स्थिर शून्य RPI_Get_Refresh_दरः(पूर्णाङ्क *numerator, पूर्णाङ्क *denominator)
{
    TV_DISPLAY_STATE_T tvstate;
    यदि (vc_tv_get_display_state(&tvstate) == 0) {
        // The width/height parameters are in the same position in the union
        // for HDMI and SDTV
        HDMI_PROPERTY_PARAM_T property;
        property.property = HDMI_PROPERTY_PIXEL_CLOCK_TYPE;
        vc_tv_hdmi_get_property(&property);
        यदि (property.param1 == HDMI_PIXEL_CLOCK_TYPE_NTSC) {
            *numerator = tvstate.display.hdmi.frame_दरः_2 * 1000;
            *denominator = 1001;
        } अन्यथा {
            *numerator = tvstate.display.hdmi.frame_दरः_2;
            *denominator = 1;
        }
        प्रत्यागम;
    }

    // Failed to get display state, default to 60
    *numerator = 60;
    *denominator = 1;
}

स्थिर SDL_VideoDevice *RPI_Create(शून्य)
{
    SDL_VideoDevice *device;
    SDL_Video_दत्त *phdata;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, परिमाण(SDL_VideoDevice));
    यदि (!device) {
        प्रत्यागम रिक्त;
    }

    // Initialize internal data
    phdata = (SDL_Video_दत्त *)SDL_calloc(1, परिमाण(SDL_Video_दत्त));
    यदि (!phdata) {
        SDL_free(device);
        प्रत्यागम रिक्त;
    }

    device->आन्तरिकम् = phdata;

    // Setup amount of available displays
    device->अङ्कः_displays = 0;

    // Set device free function
    device->मुक्त = RPI_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = RPI_VideoInit;
    device->VideoQuit = RPI_VideoQuit;
    device->CreateSDLWindow = RPI_Create_गवाक्षः;
    device->समुच्चयः_गवाक्षः_Title = RPI_समुच्चयः_गवाक्षः_Title;
    device->समुच्चयः_गवाक्षः_Position = RPI_समुच्चयः_गवाक्षः_Position;
    device->समुच्चयः_गवाक्षः_आकार = RPI_समुच्चयः_गवाक्षः_आकार;
    device->Show_गवाक्षः = RPI_Show_गवाक्षः;
    device->Hide_गवाक्षः = RPI_Hide_गवाक्षः;
    device->Raise_गवाक्षः = RPI_Raise_गवाक्षः;
    device->Maximize_गवाक्षः = RPI_Maximize_गवाक्षः;
    device->Minimize_गवाक्षः = RPI_Minimize_गवाक्षः;
    device->Restore_गवाक्षः = RPI_Restore_गवाक्षः;
    device->Destroy_गवाक्षः = RPI_Destroy_गवाक्षः;
    device->GL_आरोपय_Library = RPI_GLES_आरोपय_Library;
    device->GL_Get_Proc_स्थानाङ्कः = RPI_GLES_Get_Proc_स्थानाङ्कः;
    device->GL_UnloadLibrary = RPI_GLES_UnloadLibrary;
    device->GL_CreateContext = RPI_GLES_CreateContext;
    device->GL_MakeCurrent = RPI_GLES_MakeCurrent;
    device->GL_समुच्चयः_Swap_Interval = RPI_GLES_समुच्चयः_Swap_Interval;
    device->GL_GetSwapInterval = RPI_GLES_GetSwapInterval;
    device->GL_Swap_गवाक्षः = RPI_GLES_Swap_गवाक्षः;
    device->GL_DestroyContext = RPI_GLES_DestroyContext;
    device->GL_समुच्चयः_Default_Profile_Config = RPI_GLES_समुच्चयः_Default_Profile_Config;

    device->PumpEvents = RPI_PumpEvents;

    प्रत्यागम device;
}

VideoBootStrap RPI_bootstrap = {
    "rpi",
    "RPI Video Driver",
    RPI_Create,
    रिक्त, // no ShowMessageBox implementation
    false
};

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/*****************************************************************************/

स्थिर शून्य सङ्कलय_Disp_Man_XDisplay(ध्रुव पूर्णाङ्क display_id)
{
    DISPMANX_MODEINFO_T modeinfo;
    DISPMANX_DISPLAY_HANDLE_T handle;
    SDL_VideoDisplay display;
    SDL_Display_बहुलकम् बहुलकम्;
    SDL_Display_दत्त *दत्त;

    handle = vc_dispmanx_display_open(display_id);
    यदि (!handle) {
        प्रत्यागम; // this display isn't available
    }

    यदि (vc_dispmanx_display_get_info(handle, &modeinfo) < 0) {
        vc_dispmanx_display_close(handle);
        प्रत्यागम;
    }

    // RPI_GetRefreshRate() doesn't distinguish between displays. I'm not sure the hardware distinguishes either
    SDL_zero(बहुलकम्);
    बहुलकम्.w = modeinfo.विस्तारः;
    बहुलकम्.h = modeinfo.height;
    RPI_Get_Refresh_दरः(&बहुलकम्.refresh_दरः_numerator, &बहुलकम्.refresh_दरः_denominator);

    // 32 bpp for default
    बहुलकम्.format = SDL_PIXELFORMAT_ABGR8888;

    SDL_zero(display);
    display.desktop_बहुलकम् = बहुलकम्;

    // Allocate display internal data
    दत्त = (SDL_Display_दत्त *)SDL_calloc(1, परिमाण(SDL_Display_दत्त));
    यदि (!दत्त) {
        vc_dispmanx_display_close(handle);
        प्रत्यागम; // oh well
    }

    दत्त->dispman_display = handle;

    display.आन्तरिकम् = दत्त;

    SDL_सङ्कलय_Video_Display(&display, false);
}

bool RPI_VideoInit(SDL_VideoDevice *_this)
{
    // Initialize BCM Host
    bcm_host_init();

    सङ्कलय_Disp_Man_XDisplay(DISPMANX_ID_MAIN_LCD);    // your default display
    सङ्कलय_Disp_Man_XDisplay(DISPMANX_ID_FORCE_OTHER); // an "other" display...maybe DSI-connected screen while HDMI is your main

#यदि_परिभाषितम् SDL_निवेशः_LINUXEV
    यदि (!SDL_EVDEV_Init()) {
        प्रत्यागम false;
    }
#यदि_अन्तः

    RPI_InitMouse(_this);

    प्रत्यागम true;
}

शून्य RPI_VideoQuit(SDL_VideoDevice *_this)
{
#यदि_परिभाषितम् SDL_निवेशः_LINUXEV
    SDL_EVDEV_Quit();
#यदि_अन्तः
}

स्थिर शून्य RPI_vsync_callback(DISPMANX_UPDATE_HANDLE_T u, शून्य *दत्त)
{
    SDL_गवाक्षः_दत्त *wdata = (SDL_गवाक्षः_दत्त *)दत्त;

    SDL_तालकम्_Mutex(wdata->vsync_cond_mutex);
    SDL_SignalCondition(wdata->vsync_cond);
    SDL_UnlockMutex(wdata->vsync_cond_mutex);
}

bool RPI_Create_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID create_props)
{
    SDL_गवाक्षः_दत्त *wdata;
    SDL_VideoDisplay *display;
    SDL_Display_दत्त *displaydata;
    VC_RECT_T dst_rect;
    VC_RECT_T src_rect;
    VC_DISPMANX_ALPHA_T dispman_alpha;
    DISPMANX_UPDATE_HANDLE_T dispman_update;
    uint32_t layer = SDL_RPI_VIDEOLAYER;
    ध्रुव वर्ण *env;

    // Disable alpha, otherwise the app looks composed with whatever dispman is showing (X11, console,etc)
    dispman_alpha.flags = DISPMANX_FLAGS_ALPHA_FIXED_ALL_PIXELS;
    dispman_alpha.opacity = 0xFF;
    dispman_alpha.आवरणम् = 0;

    // Allocate window internal data
    wdata = (SDL_गवाक्षः_दत्त *)SDL_calloc(1, परिमाण(SDL_गवाक्षः_दत्त));
    यदि (!wdata) {
        प्रत्यागम false;
    }
    display = SDL_Get_Video_Display_For_गवाक्षः(गवाक्षः);
    displaydata = display->आन्तरिकम्;

    // Windows have one size for now
    गवाक्षः->w = display->desktop_बहुलकम्.w;
    गवाक्षः->h = display->desktop_बहुलकम्.h;

    // OpenGL ES is the law here, buddy
    गवाक्षः->flags |= SDL_गवाक्षः_OPENGL;

    // Create a dispman element and associate a window to it
    dst_rect.x = 0;
    dst_rect.y = 0;
    dst_rect.विस्तारः = गवाक्षः->w;
    dst_rect.height = गवाक्षः->h;

    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.विस्तारः = गवाक्षः->w << 16;
    src_rect.height = गवाक्षः->h << 16;

    env = SDL_GetHint(SDL_HINT_RPI_VIDEO_LAYER);
    यदि (env) {
        layer = SDL_atoi(env);
    }

    dispman_update = vc_dispmanx_update_start(0);
    wdata->dispman_गवाक्षः.element = vc_dispmanx_element_सङ्कलय(dispman_update,
                                                            displaydata->dispman_display,
                                                            layer /* layer */,
                                                            &dst_rect,
                                                            0 /*src*/,
                                                            &src_rect,
                                                            DISPMANX_PROTECTION_NONE,
                                                            &dispman_alpha /*alpha*/,
                                                            0 /*clamp*/,
                                                            0 /*transform*/);
    wdata->dispman_गवाक्षः.विस्तारः = गवाक्षः->w;
    wdata->dispman_गवाक्षः.height = गवाक्षः->h;
    vc_dispmanx_update_submit_sync(dispman_update);

    यदि (!_this->egl_दत्त) {
        यदि (!SDL_GL_आरोपय_Library(रिक्त)) {
            प्रत्यागम false;
        }
    }
    wdata->egl_surface = SDL_EGL_CreateSurface(_this, गवाक्षः, (Native_गवाक्षः_Type)&wdata->dispman_गवाक्षः);

    यदि (wdata->egl_surface == EGL_NO_SURFACE) {
        प्रत्यागम SDL_समुच्चयः_Error("Could not create GLES window surface");
    }

    // Start generating vsync callbacks if necessary
    wdata->double_बफर = false;
    यदि (SDL_GetHintBoolean(SDL_HINT_VIDEO_DOUBLE_बफर, false)) {
        wdata->vsync_cond = SDL_CreateCondition();
        wdata->vsync_cond_mutex = SDL_CreateMutex();
        wdata->double_बफर = true;
        vc_dispmanx_vsync_callback(displaydata->dispman_display, RPI_vsync_callback, (शून्य *)wdata);
    }

    // Setup driver data for this window
    गवाक्षः->आन्तरिकम् = wdata;

    // One window, it always has focus
    SDL_समुच्चयः_Mouse_Focus(गवाक्षः);
    SDL_समुच्चयः_Keyboard_Focus(गवाक्षः);

    // Window has been successfully created
    प्रत्यागम true;
}

शून्य RPI_Destroy_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    SDL_Display_दत्त *displaydata = SDL_Get_Display_Driver_दत्त_For_गवाक्षः(गवाक्षः);

    यदि (दत्त) {
        यदि (दत्त->double_बफर) {
            // Wait for vsync, and then stop vsync callbacks and destroy related stuff, if needed
            SDL_तालकम्_Mutex(दत्त->vsync_cond_mutex);
            SDL_WaitCondition(दत्त->vsync_cond, दत्त->vsync_cond_mutex);
            SDL_UnlockMutex(दत्त->vsync_cond_mutex);

            vc_dispmanx_vsync_callback(displaydata->dispman_display, रिक्त, रिक्त);

            SDL_DestroyCondition(दत्त->vsync_cond);
            SDL_DestroyMutex(दत्त->vsync_cond_mutex);
        }

#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
        यदि (दत्त->egl_surface != EGL_NO_SURFACE) {
            SDL_EGL_DestroySurface(_this, दत्त->egl_surface);
        }
#यदि_अन्तः
        SDL_free(दत्त);
        गवाक्षः->आन्तरिकम् = रिक्त;
    }
}

शून्य RPI_समुच्चयः_गवाक्षः_Title(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
}
bool RPI_समुच्चयः_गवाक्षः_Position(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    प्रत्यागम SDL_Unsupported();
}
शून्य RPI_समुच्चयः_गवाक्षः_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
}
शून्य RPI_Show_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
}
शून्य RPI_Hide_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
}
शून्य RPI_Raise_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
}
शून्य RPI_Maximize_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
}
शून्य RPI_Minimize_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
}
शून्य RPI_Restore_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_RPI
