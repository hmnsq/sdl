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

#నిర్వచితమైతే SDL_VIDEO_DRIVER_RPI

/* References
 * http://elinux.org/RPi_VideoCore_APIs
 * https://github.com/raspberrypi/firmware/blob/master/opt/vc/src/hello_pi/hello_triangle/triangle.c
 * http://cgit.freedesktop.org/wayland/weston/tree/src/rpi-renderer.c
 * http://cgit.freedesktop.org/wayland/weston/tree/src/compositor-rpi.c
 */

// SDL internals
#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "../../events/SDL_mouse_c.h"
#అన్తర్భావ "../../events/SDL_keyboard_c.h"

#నిర్వచితమైతే SDL_ఆదానం_LINUXEV
#అన్తర్భావ "../../core/linux/SDL_evdev.h"
#అయితే_ముగింపు

// RPI declarations
#అన్తర్భావ "SDL_rpivideo.h"
#అన్తర్భావ "SDL_rpievents_c.h"
#అన్తర్భావ "SDL_rpiopengles.h"
#అన్తర్భావ "SDL_rpimouse.h"

స్థిర శూన్య RPI_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->అంతర్గత);
    SDL_free(device);
}

స్థిర శూన్య RPI_Get_Refresh_రేటు(పూర్ణాంకం *numerator, పూర్ణాంకం *denominator)
{
    TV_DISPLAY_STATE_T tvstate;
    ఒకవేళ (vc_tv_get_display_state(&tvstate) == 0) {
        // The width/height parameters are in the same position in the union
        // for HDMI and SDTV
        HDMI_PROPERTY_PARAM_T property;
        property.property = HDMI_PROPERTY_PIXEL_CLOCK_TYPE;
        vc_tv_hdmi_get_property(&property);
        ఒకవేళ (property.param1 == HDMI_PIXEL_CLOCK_TYPE_NTSC) {
            *numerator = tvstate.display.hdmi.చట్రం_రేటు_2 * 1000;
            *denominator = 1001;
        } లేకపోతే {
            *numerator = tvstate.display.hdmi.చట్రం_రేటు_2;
            *denominator = 1;
        }
        తిరిగి;
    }

    // Failed to get display state, default to 60
    *numerator = 60;
    *denominator = 1;
}

స్థిర SDL_VideoDevice *RPI_Create(శూన్య)
{
    SDL_VideoDevice *device;
    SDL_Video_దత్తాంశం *phdata;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, పరిమాణం(SDL_VideoDevice));
    ఒకవేళ (!device) {
        తిరిగి ఖాళీ;
    }

    // Initialize internal data
    phdata = (SDL_Video_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_Video_దత్తాంశం));
    ఒకవేళ (!phdata) {
        SDL_free(device);
        తిరిగి ఖాళీ;
    }

    device->అంతర్గత = phdata;

    // Setup amount of available displays
    device->అంకె_displays = 0;

    // Set device free function
    device->విడుదల = RPI_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = RPI_VideoInit;
    device->VideoQuit = RPI_VideoQuit;
    device->CreateSDLWindow = RPI_Create_కిటికీ;
    device->సమితి_కిటికీ_Title = RPI_సమితి_కిటికీ_Title;
    device->సమితి_కిటికీ_Position = RPI_సమితి_కిటికీ_Position;
    device->సమితి_కిటికీ_కొలత = RPI_సమితి_కిటికీ_కొలత;
    device->Show_కిటికీ = RPI_Show_కిటికీ;
    device->Hide_కిటికీ = RPI_Hide_కిటికీ;
    device->Raise_కిటికీ = RPI_Raise_కిటికీ;
    device->Maximize_కిటికీ = RPI_Maximize_కిటికీ;
    device->Minimize_కిటికీ = RPI_Minimize_కిటికీ;
    device->Restore_కిటికీ = RPI_Restore_కిటికీ;
    device->Destroy_కిటికీ = RPI_Destroy_కిటికీ;
    device->GL_ఎక్కించు_Library = RPI_GLES_ఎక్కించు_Library;
    device->GL_Get_Proc_చిరునామా = RPI_GLES_Get_Proc_చిరునామా;
    device->GL_UnloadLibrary = RPI_GLES_UnloadLibrary;
    device->GL_CreateContext = RPI_GLES_CreateContext;
    device->GL_MakeCurrent = RPI_GLES_MakeCurrent;
    device->GL_సమితి_మార్పిడి_Interval = RPI_GLES_సమితి_మార్పిడి_Interval;
    device->GL_Get_మార్పిడి_Interval = RPI_GLES_Get_మార్పిడి_Interval;
    device->GL_మార్పిడి_కిటికీ = RPI_GLES_మార్పిడి_కిటికీ;
    device->GL_DestroyContext = RPI_GLES_DestroyContext;
    device->GL_సమితి_Default_Profile_Config = RPI_GLES_సమితి_Default_Profile_Config;

    device->PumpEvents = RPI_PumpEvents;

    తిరిగి device;
}

VideoBootStrap RPI_bootstrap = {
    "rpi",
    "RPI Video Driver",
    RPI_Create,
    ఖాళీ, // no ShowMessageBox implementation
    false
};

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/*****************************************************************************/

స్థిర శూన్య కూడు_Disp_Man_XDisplay(స్థిరరాశి పూర్ణాంకం display_id)
{
    DISPMANX_MODEINFO_T modeinfo;
    DISPMANX_DISPLAY_HANDLE_T handle;
    SDL_VideoDisplay display;
    SDL_Display_బహుళకం బహుళకం;
    SDL_Display_దత్తాంశం *దత్తాంశం;

    handle = vc_dispmanx_display_open(display_id);
    ఒకవేళ (!handle) {
        తిరిగి; // this display isn't available
    }

    ఒకవేళ (vc_dispmanx_display_get_info(handle, &modeinfo) < 0) {
        vc_dispmanx_display_close(handle);
        తిరిగి;
    }

    // RPI_GetRefreshRate() doesn't distinguish between displays. I'm not sure the hardware distinguishes either
    SDL_zero(బహుళకం);
    బహుళకం.w = modeinfo.వెడల్పు;
    బహుళకం.h = modeinfo.ఎత్తు;
    RPI_Get_Refresh_రేటు(&బహుళకం.refresh_రేటు_numerator, &బహుళకం.refresh_రేటు_denominator);

    // 32 bpp for default
    బహుళకం.format = SDL_PIXELFORMAT_ABGR8888;

    SDL_zero(display);
    display.desktop_బహుళకం = బహుళకం;

    // Allocate display internal data
    దత్తాంశం = (SDL_Display_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_Display_దత్తాంశం));
    ఒకవేళ (!దత్తాంశం) {
        vc_dispmanx_display_close(handle);
        తిరిగి; // oh well
    }

    దత్తాంశం->dispman_display = handle;

    display.అంతర్గత = దత్తాంశం;

    SDL_కూడు_Video_Display(&display, false);
}

bool RPI_VideoInit(SDL_VideoDevice *_this)
{
    // Initialize BCM Host
    bcm_host_init();

    కూడు_Disp_Man_XDisplay(DISPMANX_ID_MAIN_LCD);    // your default display
    కూడు_Disp_Man_XDisplay(DISPMANX_ID_FORCE_OTHER); // an "other" display...maybe DSI-connected screen while HDMI is your main

#నిర్వచితమైతే SDL_ఆదానం_LINUXEV
    ఒకవేళ (!SDL_EVDEV_Init()) {
        తిరిగి false;
    }
#అయితే_ముగింపు

    RPI_InitMouse(_this);

    తిరిగి true;
}

శూన్య RPI_VideoQuit(SDL_VideoDevice *_this)
{
#నిర్వచితమైతే SDL_ఆదానం_LINUXEV
    SDL_EVDEV_Quit();
#అయితే_ముగింపు
}

స్థిర శూన్య RPI_vsync_callback(DISPMANX_UPDATE_HANDLE_T u, శూన్య *దత్తాంశం)
{
    SDL_కిటికీ_దత్తాంశం *wdata = (SDL_కిటికీ_దత్తాంశం *)దత్తాంశం;

    SDL_తాళం_Mutex(wdata->vsync_cond_mutex);
    SDL_SignalCondition(wdata->vsync_cond);
    SDL_UnlockMutex(wdata->vsync_cond_mutex);
}

bool RPI_Create_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID create_props)
{
    SDL_కిటికీ_దత్తాంశం *wdata;
    SDL_VideoDisplay *display;
    SDL_Display_దత్తాంశం *displaydata;
    VC_RECT_T dst_rect;
    VC_RECT_T src_rect;
    VC_DISPMANX_ALPHA_T dispman_alpha;
    DISPMANX_UPDATE_HANDLE_T dispman_update;
    uint32_t layer = SDL_RPI_VIDEOLAYER;
    స్థిరరాశి అక్షరం *env;

    // Disable alpha, otherwise the app looks composed with whatever dispman is showing (X11, console,etc)
    dispman_alpha.flags = DISPMANX_FLAGS_ALPHA_FIXED_ALL_PIXELS;
    dispman_alpha.opacity = 0xFF;
    dispman_alpha.ముసుగు = 0;

    // Allocate window internal data
    wdata = (SDL_కిటికీ_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_కిటికీ_దత్తాంశం));
    ఒకవేళ (!wdata) {
        తిరిగి false;
    }
    display = SDL_Get_Video_Display_For_కిటికీ(కిటికీ);
    displaydata = display->అంతర్గత;

    // Windows have one size for now
    కిటికీ->w = display->desktop_బహుళకం.w;
    కిటికీ->h = display->desktop_బహుళకం.h;

    // OpenGL ES is the law here, buddy
    కిటికీ->flags |= SDL_కిటికీ_OPENGL;

    // Create a dispman element and associate a window to it
    dst_rect.x = 0;
    dst_rect.y = 0;
    dst_rect.వెడల్పు = కిటికీ->w;
    dst_rect.ఎత్తు = కిటికీ->h;

    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.వెడల్పు = కిటికీ->w << 16;
    src_rect.ఎత్తు = కిటికీ->h << 16;

    env = SDL_GetHint(SDL_HINT_RPI_VIDEO_LAYER);
    ఒకవేళ (env) {
        layer = SDL_atoi(env);
    }

    dispman_update = vc_dispmanx_update_ప్రారంభం(0);
    wdata->dispman_కిటికీ.element = vc_dispmanx_element_కూడు(dispman_update,
                                                            displaydata->dispman_display,
                                                            layer /* layer */,
                                                            &dst_rect,
                                                            0 /*src*/,
                                                            &src_rect,
                                                            DISPMANX_PROTECTION_NONE,
                                                            &dispman_alpha /*alpha*/,
                                                            0 /*clamp*/,
                                                            0 /*transform*/);
    wdata->dispman_కిటికీ.వెడల్పు = కిటికీ->w;
    wdata->dispman_కిటికీ.ఎత్తు = కిటికీ->h;
    vc_dispmanx_update_submit_sync(dispman_update);

    ఒకవేళ (!_this->egl_దత్తాంశం) {
        ఒకవేళ (!SDL_GL_ఎక్కించు_Library(ఖాళీ)) {
            తిరిగి false;
        }
    }
    wdata->egl_surface = SDL_EGL_CreateSurface(_this, కిటికీ, (Native_కిటికీ_Type)&wdata->dispman_కిటికీ);

    ఒకవేళ (wdata->egl_surface == EGL_NO_SURFACE) {
        తిరిగి SDL_సమితి_Error("Could not create GLES window surface");
    }

    // Start generating vsync callbacks if necessary
    wdata->double_బఫరు = false;
    ఒకవేళ (SDL_GetHintBoolean(SDL_HINT_VIDEO_DOUBLE_బఫరు, false)) {
        wdata->vsync_cond = SDL_CreateCondition();
        wdata->vsync_cond_mutex = SDL_CreateMutex();
        wdata->double_బఫరు = true;
        vc_dispmanx_vsync_callback(displaydata->dispman_display, RPI_vsync_callback, (శూన్య *)wdata);
    }

    // Setup driver data for this window
    కిటికీ->అంతర్గత = wdata;

    // One window, it always has focus
    SDL_సమితి_Mouse_Focus(కిటికీ);
    SDL_సమితి_Keyboard_Focus(కిటికీ);

    // Window has been successfully created
    తిరిగి true;
}

శూన్య RPI_Destroy_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    SDL_Display_దత్తాంశం *displaydata = SDL_Get_Display_Driver_దత్తాంశం_For_కిటికీ(కిటికీ);

    ఒకవేళ (దత్తాంశం) {
        ఒకవేళ (దత్తాంశం->double_బఫరు) {
            // Wait for vsync, and then stop vsync callbacks and destroy related stuff, if needed
            SDL_తాళం_Mutex(దత్తాంశం->vsync_cond_mutex);
            SDL_WaitCondition(దత్తాంశం->vsync_cond, దత్తాంశం->vsync_cond_mutex);
            SDL_UnlockMutex(దత్తాంశం->vsync_cond_mutex);

            vc_dispmanx_vsync_callback(displaydata->dispman_display, ఖాళీ, ఖాళీ);

            SDL_DestroyCondition(దత్తాంశం->vsync_cond);
            SDL_DestroyMutex(దత్తాంశం->vsync_cond_mutex);
        }

#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
        ఒకవేళ (దత్తాంశం->egl_surface != EGL_NO_SURFACE) {
            SDL_EGL_DestroySurface(_this, దత్తాంశం->egl_surface);
        }
#అయితే_ముగింపు
        SDL_free(దత్తాంశం);
        కిటికీ->అంతర్గత = ఖాళీ;
    }
}

శూన్య RPI_సమితి_కిటికీ_Title(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
}
bool RPI_సమితి_కిటికీ_Position(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    తిరిగి SDL_Unsupported();
}
శూన్య RPI_సమితి_కిటికీ_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
}
శూన్య RPI_Show_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
}
శూన్య RPI_Hide_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
}
శూన్య RPI_Raise_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
}
శూన్య RPI_Maximize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
}
శూన్య RPI_Minimize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
}
శూన్య RPI_Restore_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_RPI
