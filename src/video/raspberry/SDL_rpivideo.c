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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_RPI

/* References
 * http://elinux.org/RPi_VideoCore_APIs
 * https://github.com/raspberrypi/firmware/blob/master/opt/vc/src/hello_pi/hello_triangle/triangle.c
 * http://cgit.freedesktop.org/wayland/weston/tree/src/rpi-renderer.c
 * http://cgit.freedesktop.org/wayland/weston/tree/src/compositor-rpi.c
 */

// SDL internals
#ضمن "../SDL_sysvideo.h"
#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../../events/SDL_keyboard_c.h"

#جے_تعریف_شدہ SDL_داخلہ_LINUXEV
#ضمن "../../core/linux/SDL_evdev.h"
#جے_انت

// RPI declarations
#ضمن "SDL_rpivideo.h"
#ضمن "SDL_rpievents_c.h"
#ضمن "SDL_rpiopengles.h"
#ضمن "SDL_rpimouse.h"

ساكن فراغ RPI_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->اندرونی);
    SDL_free(device);
}

ساكن فراغ RPI_Get_Refresh_شرح(صحيح *numerator, صحيح *denominator)
{
    TV_DISPLAY_STATE_T tvstate;
    إذا (vc_tv_get_display_state(&tvstate) == 0) {
        // The width/height parameters are in the same position in the union
        // for HDMI and SDTV
        HDMI_PROPERTY_PARAM_T property;
        property.property = HDMI_PROPERTY_PIXEL_CLOCK_TYPE;
        vc_tv_hdmi_get_property(&property);
        إذا (property.param1 == HDMI_PIXEL_CLOCK_TYPE_NTSC) {
            *numerator = tvstate.display.hdmi.چوکھٹا_شرح_2 * 1000;
            *denominator = 1001;
        } وإلا {
            *numerator = tvstate.display.hdmi.چوکھٹا_شرح_2;
            *denominator = 1;
        }
        أرجع;
    }

    // Failed to get display state, default to 60
    *numerator = 60;
    *denominator = 1;
}

ساكن SDL_VideoDevice *RPI_Create(فراغ)
{
    SDL_VideoDevice *device;
    SDL_Video_انکڑے *phdata;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (!device) {
        أرجع عدم;
    }

    // Initialize internal data
    phdata = (SDL_Video_انکڑے *)SDL_calloc(1, حجم(SDL_Video_انکڑے));
    إذا (!phdata) {
        SDL_free(device);
        أرجع عدم;
    }

    device->اندرونی = phdata;

    // Setup amount of available displays
    device->عدد_displays = 0;

    // Set device free function
    device->حرر = RPI_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = RPI_VideoInit;
    device->VideoQuit = RPI_VideoQuit;
    device->CreateSDLWindow = RPI_Create_کھڑکی;
    device->سیٹ_کھڑکی_Title = RPI_سیٹ_کھڑکی_Title;
    device->سیٹ_کھڑکی_Position = RPI_سیٹ_کھڑکی_Position;
    device->سیٹ_کھڑکی_ناپ = RPI_سیٹ_کھڑکی_ناپ;
    device->Show_کھڑکی = RPI_Show_کھڑکی;
    device->Hide_کھڑکی = RPI_Hide_کھڑکی;
    device->Raise_کھڑکی = RPI_Raise_کھڑکی;
    device->Maximize_کھڑکی = RPI_Maximize_کھڑکی;
    device->Minimize_کھڑکی = RPI_Minimize_کھڑکی;
    device->Restore_کھڑکی = RPI_Restore_کھڑکی;
    device->Destroy_کھڑکی = RPI_Destroy_کھڑکی;
    device->GL_لدو_Library = RPI_GLES_لدو_Library;
    device->GL_Get_Proc_پتہ = RPI_GLES_Get_Proc_پتہ;
    device->GL_UnloadLibrary = RPI_GLES_UnloadLibrary;
    device->GL_CreateContext = RPI_GLES_CreateContext;
    device->GL_MakeCurrent = RPI_GLES_MakeCurrent;
    device->GL_سیٹ_وٹاندرا_Interval = RPI_GLES_سیٹ_وٹاندرا_Interval;
    device->GL_Get_وٹاندرا_Interval = RPI_GLES_Get_وٹاندرا_Interval;
    device->GL_وٹاندرا_کھڑکی = RPI_GLES_وٹاندرا_کھڑکی;
    device->GL_DestroyContext = RPI_GLES_DestroyContext;
    device->GL_سیٹ_Default_Profile_Config = RPI_GLES_سیٹ_Default_Profile_Config;

    device->PumpEvents = RPI_PumpEvents;

    أرجع device;
}

VideoBootStrap RPI_bootstrap = {
    "rpi",
    "RPI Video Driver",
    RPI_Create,
    عدم, // no ShowMessageBox implementation
    false
};

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/*****************************************************************************/

ساكن فراغ جوڑو_Disp_Man_XDisplay(ثابت صحيح display_id)
{
    DISPMANX_MODEINFO_T modeinfo;
    DISPMANX_DISPLAY_HANDLE_T handle;
    SDL_VideoDisplay display;
    SDL_Display_منوال منوال;
    SDL_Display_انکڑے *انکڑے;

    handle = vc_dispmanx_display_open(display_id);
    إذا (!handle) {
        أرجع; // this display isn't available
    }

    إذا (vc_dispmanx_display_get_info(handle, &modeinfo) < 0) {
        vc_dispmanx_display_close(handle);
        أرجع;
    }

    // RPI_GetRefreshRate() doesn't distinguish between displays. I'm not sure the hardware distinguishes either
    SDL_zero(منوال);
    منوال.w = modeinfo.چوڑائی;
    منوال.h = modeinfo.اچائی;
    RPI_Get_Refresh_شرح(&منوال.refresh_شرح_numerator, &منوال.refresh_شرح_denominator);

    // 32 bpp for default
    منوال.format = SDL_PIXELFORMAT_ABGR8888;

    SDL_zero(display);
    display.desktop_منوال = منوال;

    // Allocate display internal data
    انکڑے = (SDL_Display_انکڑے *)SDL_calloc(1, حجم(SDL_Display_انکڑے));
    إذا (!انکڑے) {
        vc_dispmanx_display_close(handle);
        أرجع; // oh well
    }

    انکڑے->dispman_display = handle;

    display.اندرونی = انکڑے;

    SDL_جوڑو_Video_Display(&display, false);
}

bool RPI_VideoInit(SDL_VideoDevice *_this)
{
    // Initialize BCM Host
    bcm_host_init();

    جوڑو_Disp_Man_XDisplay(DISPMANX_ID_MAIN_LCD);    // your default display
    جوڑو_Disp_Man_XDisplay(DISPMANX_ID_FORCE_OTHER); // an "other" display...maybe DSI-connected screen while HDMI is your main

#جے_تعریف_شدہ SDL_داخلہ_LINUXEV
    إذا (!SDL_EVDEV_Init()) {
        أرجع false;
    }
#جے_انت

    RPI_InitMouse(_this);

    أرجع true;
}

فراغ RPI_VideoQuit(SDL_VideoDevice *_this)
{
#جے_تعریف_شدہ SDL_داخلہ_LINUXEV
    SDL_EVDEV_Quit();
#جے_انت
}

ساكن فراغ RPI_vsync_callback(DISPMANX_UPDATE_HANDLE_T u, فراغ *انکڑے)
{
    SDL_کھڑکی_انکڑے *wdata = (SDL_کھڑکی_انکڑے *)انکڑے;

    SDL_جندرا_Mutex(wdata->vsync_cond_mutex);
    SDL_SignalCondition(wdata->vsync_cond);
    SDL_UnlockMutex(wdata->vsync_cond_mutex);
}

bool RPI_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props)
{
    SDL_کھڑکی_انکڑے *wdata;
    SDL_VideoDisplay *display;
    SDL_Display_انکڑے *displaydata;
    VC_RECT_T dst_rect;
    VC_RECT_T src_rect;
    VC_DISPMANX_ALPHA_T dispman_alpha;
    DISPMANX_UPDATE_HANDLE_T dispman_update;
    uint32_t layer = SDL_RPI_VIDEOLAYER;
    ثابت حرف *env;

    // Disable alpha, otherwise the app looks composed with whatever dispman is showing (X11, console,etc)
    dispman_alpha.flags = DISPMANX_FLAGS_ALPHA_FIXED_ALL_PIXELS;
    dispman_alpha.opacity = 0xFF;
    dispman_alpha.نقاب = 0;

    // Allocate window internal data
    wdata = (SDL_کھڑکی_انکڑے *)SDL_calloc(1, حجم(SDL_کھڑکی_انکڑے));
    إذا (!wdata) {
        أرجع false;
    }
    display = SDL_Get_Video_Display_For_کھڑکی(کھڑکی);
    displaydata = display->اندرونی;

    // Windows have one size for now
    کھڑکی->w = display->desktop_منوال.w;
    کھڑکی->h = display->desktop_منوال.h;

    // OpenGL ES is the law here, buddy
    کھڑکی->flags |= SDL_کھڑکی_OPENGL;

    // Create a dispman element and associate a window to it
    dst_rect.x = 0;
    dst_rect.y = 0;
    dst_rect.چوڑائی = کھڑکی->w;
    dst_rect.اچائی = کھڑکی->h;

    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.چوڑائی = کھڑکی->w << 16;
    src_rect.اچائی = کھڑکی->h << 16;

    env = SDL_GetHint(SDL_HINT_RPI_VIDEO_LAYER);
    إذا (env) {
        layer = SDL_atoi(env);
    }

    dispman_update = vc_dispmanx_update_شروع(0);
    wdata->dispman_کھڑکی.element = vc_dispmanx_element_جوڑو(dispman_update,
                                                            displaydata->dispman_display,
                                                            layer /* layer */,
                                                            &dst_rect,
                                                            0 /*src*/,
                                                            &src_rect,
                                                            DISPMANX_PROTECTION_NONE,
                                                            &dispman_alpha /*alpha*/,
                                                            0 /*clamp*/,
                                                            0 /*transform*/);
    wdata->dispman_کھڑکی.چوڑائی = کھڑکی->w;
    wdata->dispman_کھڑکی.اچائی = کھڑکی->h;
    vc_dispmanx_update_submit_sync(dispman_update);

    إذا (!_this->egl_انکڑے) {
        إذا (!SDL_GL_لدو_Library(عدم)) {
            أرجع false;
        }
    }
    wdata->egl_surface = SDL_EGL_CreateSurface(_this, کھڑکی, (Native_کھڑکی_Type)&wdata->dispman_کھڑکی);

    إذا (wdata->egl_surface == EGL_NO_SURFACE) {
        أرجع SDL_سیٹ_Error("Could not create GLES window surface");
    }

    // Start generating vsync callbacks if necessary
    wdata->double_بفر = false;
    إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_DOUBLE_بفر, false)) {
        wdata->vsync_cond = SDL_CreateCondition();
        wdata->vsync_cond_mutex = SDL_CreateMutex();
        wdata->double_بفر = true;
        vc_dispmanx_vsync_callback(displaydata->dispman_display, RPI_vsync_callback, (فراغ *)wdata);
    }

    // Setup driver data for this window
    کھڑکی->اندرونی = wdata;

    // One window, it always has focus
    SDL_سیٹ_Mouse_Focus(کھڑکی);
    SDL_سیٹ_Keyboard_Focus(کھڑکی);

    // Window has been successfully created
    أرجع true;
}

فراغ RPI_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    SDL_Display_انکڑے *displaydata = SDL_Get_Display_Driver_انکڑے_For_کھڑکی(کھڑکی);

    إذا (انکڑے) {
        إذا (انکڑے->double_بفر) {
            // Wait for vsync, and then stop vsync callbacks and destroy related stuff, if needed
            SDL_جندرا_Mutex(انکڑے->vsync_cond_mutex);
            SDL_WaitCondition(انکڑے->vsync_cond, انکڑے->vsync_cond_mutex);
            SDL_UnlockMutex(انکڑے->vsync_cond_mutex);

            vc_dispmanx_vsync_callback(displaydata->dispman_display, عدم, عدم);

            SDL_DestroyCondition(انکڑے->vsync_cond);
            SDL_DestroyMutex(انکڑے->vsync_cond_mutex);
        }

#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
        إذا (انکڑے->egl_surface != EGL_NO_SURFACE) {
            SDL_EGL_DestroySurface(_this, انکڑے->egl_surface);
        }
#جے_انت
        SDL_free(انکڑے);
        کھڑکی->اندرونی = عدم;
    }
}

فراغ RPI_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
bool RPI_سیٹ_کھڑکی_Position(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    أرجع SDL_Unsupported();
}
فراغ RPI_سیٹ_کھڑکی_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
فراغ RPI_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
فراغ RPI_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
فراغ RPI_Raise_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
فراغ RPI_Maximize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
فراغ RPI_Minimize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
فراغ RPI_Restore_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}

#جے_انت // SDL_VIDEO_DRIVER_RPI
