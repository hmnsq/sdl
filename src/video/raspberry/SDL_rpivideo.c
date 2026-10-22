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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_RPI

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

#اگر_تعریف_شده SDL_درون_داد_LINUXEV
#ضمن "../../core/linux/SDL_evdev.h"
#پایان_اگر

// RPI declarations
#ضمن "SDL_rpivideo.h"
#ضمن "SDL_rpievents_c.h"
#ضمن "SDL_rpiopengles.h"
#ضمن "SDL_rpimouse.h"

ساكن فراغ RPI_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->داخلی);
    SDL_free(device);
}

ساكن فراغ RPI_Get_Refresh_نرخ(صحيح *numerator, صحيح *denominator)
{
    TV_DISPLAY_STATE_T tvstate;
    إذا (vc_tv_get_display_state(&tvstate) == 0) {
        // The width/height parameters are in the same position in the union
        // for HDMI and SDTV
        HDMI_PROPERTY_PARAM_T property;
        property.property = HDMI_PROPERTY_PIXEL_CLOCK_TYPE;
        vc_tv_hdmi_get_property(&property);
        إذا (property.param1 == HDMI_PIXEL_CLOCK_TYPE_NTSC) {
            *numerator = tvstate.display.hdmi.قاب_نرخ_2 * 1000;
            *denominator = 1001;
        } وإلا {
            *numerator = tvstate.display.hdmi.قاب_نرخ_2;
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
    SDL_Video_داده *phdata;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (!device) {
        أرجع عدم;
    }

    // Initialize internal data
    phdata = (SDL_Video_داده *)SDL_calloc(1, حجم(SDL_Video_داده));
    إذا (!phdata) {
        SDL_free(device);
        أرجع عدم;
    }

    device->داخلی = phdata;

    // Setup amount of available displays
    device->رقم_displays = 0;

    // Set device free function
    device->حرر = RPI_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = RPI_VideoInit;
    device->VideoQuit = RPI_VideoQuit;
    device->CreateSDLWindow = RPI_Create_پنجره;
    device->مجموعه_پنجره_Title = RPI_مجموعه_پنجره_Title;
    device->مجموعه_پنجره_Position = RPI_مجموعه_پنجره_Position;
    device->مجموعه_پنجره_اندازه = RPI_مجموعه_پنجره_اندازه;
    device->Show_پنجره = RPI_Show_پنجره;
    device->Hide_پنجره = RPI_Hide_پنجره;
    device->Raise_پنجره = RPI_Raise_پنجره;
    device->Maximize_پنجره = RPI_Maximize_پنجره;
    device->Minimize_پنجره = RPI_Minimize_پنجره;
    device->Restore_پنجره = RPI_Restore_پنجره;
    device->Destroy_پنجره = RPI_Destroy_پنجره;
    device->GL_بارگیری_Library = RPI_GLES_بارگیری_Library;
    device->GL_Get_Proc_آدرس = RPI_GLES_Get_Proc_آدرس;
    device->GL_UnloadLibrary = RPI_GLES_UnloadLibrary;
    device->GL_CreateContext = RPI_GLES_CreateContext;
    device->GL_MakeCurrent = RPI_GLES_MakeCurrent;
    device->GL_مجموعه_جابجا_Interval = RPI_GLES_مجموعه_جابجا_Interval;
    device->GL_Get_جابجا_Interval = RPI_GLES_Get_جابجا_Interval;
    device->GL_جابجا_پنجره = RPI_GLES_جابجا_پنجره;
    device->GL_DestroyContext = RPI_GLES_DestroyContext;
    device->GL_مجموعه_Default_Profile_Config = RPI_GLES_مجموعه_Default_Profile_Config;

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

ساكن فراغ جمع_کن_Disp_Man_XDisplay(ثابت صحيح display_id)
{
    DISPMANX_MODEINFO_T modeinfo;
    DISPMANX_DISPLAY_HANDLE_T handle;
    SDL_VideoDisplay display;
    SDL_Display_نما نما;
    SDL_Display_داده *داده;

    handle = vc_dispmanx_display_open(display_id);
    إذا (!handle) {
        أرجع; // this display isn't available
    }

    إذا (vc_dispmanx_display_get_info(handle, &modeinfo) < 0) {
        vc_dispmanx_display_close(handle);
        أرجع;
    }

    // RPI_GetRefreshRate() doesn't distinguish between displays. I'm not sure the hardware distinguishes either
    SDL_zero(نما);
    نما.w = modeinfo.عرض;
    نما.h = modeinfo.ارتفاع;
    RPI_Get_Refresh_نرخ(&نما.refresh_نرخ_numerator, &نما.refresh_نرخ_denominator);

    // 32 bpp for default
    نما.format = SDL_PIXELFORMAT_ABGR8888;

    SDL_zero(display);
    display.desktop_نما = نما;

    // Allocate display internal data
    داده = (SDL_Display_داده *)SDL_calloc(1, حجم(SDL_Display_داده));
    إذا (!داده) {
        vc_dispmanx_display_close(handle);
        أرجع; // oh well
    }

    داده->dispman_display = handle;

    display.داخلی = داده;

    SDL_جمع_کن_Video_Display(&display, false);
}

bool RPI_VideoInit(SDL_VideoDevice *_this)
{
    // Initialize BCM Host
    bcm_host_init();

    جمع_کن_Disp_Man_XDisplay(DISPMANX_ID_MAIN_LCD);    // your default display
    جمع_کن_Disp_Man_XDisplay(DISPMANX_ID_FORCE_OTHER); // an "other" display...maybe DSI-connected screen while HDMI is your main

#اگر_تعریف_شده SDL_درون_داد_LINUXEV
    إذا (!SDL_EVDEV_Init()) {
        أرجع false;
    }
#پایان_اگر

    RPI_InitMouse(_this);

    أرجع true;
}

فراغ RPI_VideoQuit(SDL_VideoDevice *_this)
{
#اگر_تعریف_شده SDL_درون_داد_LINUXEV
    SDL_EVDEV_Quit();
#پایان_اگر
}

ساكن فراغ RPI_vsync_callback(DISPMANX_UPDATE_HANDLE_T u, فراغ *داده)
{
    SDL_پنجره_داده *wdata = (SDL_پنجره_داده *)داده;

    SDL_قفل_Mutex(wdata->vsync_cond_mutex);
    SDL_SignalCondition(wdata->vsync_cond);
    SDL_UnlockMutex(wdata->vsync_cond_mutex);
}

bool RPI_Create_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID create_props)
{
    SDL_پنجره_داده *wdata;
    SDL_VideoDisplay *display;
    SDL_Display_داده *displaydata;
    VC_RECT_T dst_rect;
    VC_RECT_T src_rect;
    VC_DISPMANX_ALPHA_T dispman_alpha;
    DISPMANX_UPDATE_HANDLE_T dispman_update;
    uint32_t layer = SDL_RPI_VIDEOLAYER;
    ثابت حرف *env;

    // Disable alpha, otherwise the app looks composed with whatever dispman is showing (X11, console,etc)
    dispman_alpha.flags = DISPMANX_FLAGS_ALPHA_FIXED_ALL_PIXELS;
    dispman_alpha.opacity = 0xFF;
    dispman_alpha.ماسک = 0;

    // Allocate window internal data
    wdata = (SDL_پنجره_داده *)SDL_calloc(1, حجم(SDL_پنجره_داده));
    إذا (!wdata) {
        أرجع false;
    }
    display = SDL_Get_Video_Display_For_پنجره(پنجره);
    displaydata = display->داخلی;

    // Windows have one size for now
    پنجره->w = display->desktop_نما.w;
    پنجره->h = display->desktop_نما.h;

    // OpenGL ES is the law here, buddy
    پنجره->flags |= SDL_پنجره_OPENGL;

    // Create a dispman element and associate a window to it
    dst_rect.x = 0;
    dst_rect.y = 0;
    dst_rect.عرض = پنجره->w;
    dst_rect.ارتفاع = پنجره->h;

    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.عرض = پنجره->w << 16;
    src_rect.ارتفاع = پنجره->h << 16;

    env = SDL_GetHint(SDL_HINT_RPI_VIDEO_LAYER);
    إذا (env) {
        layer = SDL_atoi(env);
    }

    dispman_update = vc_dispmanx_update_شروع(0);
    wdata->dispman_پنجره.element = vc_dispmanx_element_جمع_کن(dispman_update,
                                                            displaydata->dispman_display,
                                                            layer /* layer */,
                                                            &dst_rect,
                                                            0 /*src*/,
                                                            &src_rect,
                                                            DISPMANX_PROTECTION_NONE,
                                                            &dispman_alpha /*alpha*/,
                                                            0 /*clamp*/,
                                                            0 /*transform*/);
    wdata->dispman_پنجره.عرض = پنجره->w;
    wdata->dispman_پنجره.ارتفاع = پنجره->h;
    vc_dispmanx_update_submit_sync(dispman_update);

    إذا (!_this->egl_داده) {
        إذا (!SDL_GL_بارگیری_Library(عدم)) {
            أرجع false;
        }
    }
    wdata->egl_surface = SDL_EGL_CreateSurface(_this, پنجره, (Native_پنجره_Type)&wdata->dispman_پنجره);

    إذا (wdata->egl_surface == EGL_NO_SURFACE) {
        أرجع SDL_مجموعه_Error("Could not create GLES window surface");
    }

    // Start generating vsync callbacks if necessary
    wdata->double_میانگیر = false;
    إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_DOUBLE_میانگیر, false)) {
        wdata->vsync_cond = SDL_CreateCondition();
        wdata->vsync_cond_mutex = SDL_CreateMutex();
        wdata->double_میانگیر = true;
        vc_dispmanx_vsync_callback(displaydata->dispman_display, RPI_vsync_callback, (فراغ *)wdata);
    }

    // Setup driver data for this window
    پنجره->داخلی = wdata;

    // One window, it always has focus
    SDL_مجموعه_Mouse_Focus(پنجره);
    SDL_مجموعه_Keyboard_Focus(پنجره);

    // Window has been successfully created
    أرجع true;
}

فراغ RPI_Destroy_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    SDL_Display_داده *displaydata = SDL_Get_Display_Driver_داده_For_پنجره(پنجره);

    إذا (داده) {
        إذا (داده->double_میانگیر) {
            // Wait for vsync, and then stop vsync callbacks and destroy related stuff, if needed
            SDL_قفل_Mutex(داده->vsync_cond_mutex);
            SDL_WaitCondition(داده->vsync_cond, داده->vsync_cond_mutex);
            SDL_UnlockMutex(داده->vsync_cond_mutex);

            vc_dispmanx_vsync_callback(displaydata->dispman_display, عدم, عدم);

            SDL_DestroyCondition(داده->vsync_cond);
            SDL_DestroyMutex(داده->vsync_cond_mutex);
        }

#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
        إذا (داده->egl_surface != EGL_NO_SURFACE) {
            SDL_EGL_DestroySurface(_this, داده->egl_surface);
        }
#پایان_اگر
        SDL_free(داده);
        پنجره->داخلی = عدم;
    }
}

فراغ RPI_مجموعه_پنجره_Title(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
}
bool RPI_مجموعه_پنجره_Position(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    أرجع SDL_Unsupported();
}
فراغ RPI_مجموعه_پنجره_اندازه(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
}
فراغ RPI_Show_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
}
فراغ RPI_Hide_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
}
فراغ RPI_Raise_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
}
فراغ RPI_Maximize_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
}
فراغ RPI_Minimize_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
}
فراغ RPI_Restore_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
}

#پایان_اگر // SDL_VIDEO_DRIVER_RPI
