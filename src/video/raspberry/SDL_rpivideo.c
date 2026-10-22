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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_RPI

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

#جيڪڏهن_وصف_ٿيل SDL_داخلا_LINUXEV
#ضمن "../../core/linux/SDL_evdev.h"
#جيڪڏهن_پورو

// RPI declarations
#ضمن "SDL_rpivideo.h"
#ضمن "SDL_rpievents_c.h"
#ضمن "SDL_rpiopengles.h"
#ضمن "SDL_rpimouse.h"

ساكن فراغ RPI_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->اندروني);
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
            *numerator = tvstate.display.hdmi.چوکٺو_شرح_2 * 1000;
            *denominator = 1001;
        } وإلا {
            *numerator = tvstate.display.hdmi.چوکٺو_شرح_2;
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
    SDL_Video_معلومات *phdata;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (!device) {
        أرجع عدم;
    }

    // Initialize internal data
    phdata = (SDL_Video_معلومات *)SDL_calloc(1, حجم(SDL_Video_معلومات));
    إذا (!phdata) {
        SDL_free(device);
        أرجع عدم;
    }

    device->اندروني = phdata;

    // Setup amount of available displays
    device->انگ_displays = 0;

    // Set device free function
    device->حرر = RPI_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = RPI_VideoInit;
    device->VideoQuit = RPI_VideoQuit;
    device->CreateSDLWindow = RPI_Create_دري;
    device->سيٽ_دري_Title = RPI_سيٽ_دري_Title;
    device->سيٽ_دري_Position = RPI_سيٽ_دري_Position;
    device->سيٽ_دري_سائيز = RPI_سيٽ_دري_سائيز;
    device->Show_دري = RPI_Show_دري;
    device->Hide_دري = RPI_Hide_دري;
    device->Raise_دري = RPI_Raise_دري;
    device->Maximize_دري = RPI_Maximize_دري;
    device->Minimize_دري = RPI_Minimize_دري;
    device->Restore_دري = RPI_Restore_دري;
    device->Destroy_دري = RPI_Destroy_دري;
    device->GL_ڀريو_Library = RPI_GLES_ڀريو_Library;
    device->GL_Get_Proc_پتو = RPI_GLES_Get_Proc_پتو;
    device->GL_UnloadLibrary = RPI_GLES_UnloadLibrary;
    device->GL_CreateContext = RPI_GLES_CreateContext;
    device->GL_MakeCurrent = RPI_GLES_MakeCurrent;
    device->GL_سيٽ_مٽا_سٽا_Interval = RPI_GLES_سيٽ_مٽا_سٽا_Interval;
    device->GL_Get_مٽا_سٽا_Interval = RPI_GLES_Get_مٽا_سٽا_Interval;
    device->GL_مٽا_سٽا_دري = RPI_GLES_مٽا_سٽا_دري;
    device->GL_DestroyContext = RPI_GLES_DestroyContext;
    device->GL_سيٽ_Default_Profile_Config = RPI_GLES_سيٽ_Default_Profile_Config;

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

ساكن فراغ جوڙيو_Disp_Man_XDisplay(ثابت صحيح display_id)
{
    DISPMANX_MODEINFO_T modeinfo;
    DISPMANX_DISPLAY_HANDLE_T handle;
    SDL_VideoDisplay display;
    SDL_Display_گهڻائي گهڻائي;
    SDL_Display_معلومات *معلومات;

    handle = vc_dispmanx_display_open(display_id);
    إذا (!handle) {
        أرجع; // this display isn't available
    }

    إذا (vc_dispmanx_display_get_info(handle, &modeinfo) < 0) {
        vc_dispmanx_display_close(handle);
        أرجع;
    }

    // RPI_GetRefreshRate() doesn't distinguish between displays. I'm not sure the hardware distinguishes either
    SDL_zero(گهڻائي);
    گهڻائي.w = modeinfo.ويڪر;
    گهڻائي.h = modeinfo.اوچائي;
    RPI_Get_Refresh_شرح(&گهڻائي.refresh_شرح_numerator, &گهڻائي.refresh_شرح_denominator);

    // 32 bpp for default
    گهڻائي.format = SDL_PIXELFORMAT_ABGR8888;

    SDL_zero(display);
    display.desktop_گهڻائي = گهڻائي;

    // Allocate display internal data
    معلومات = (SDL_Display_معلومات *)SDL_calloc(1, حجم(SDL_Display_معلومات));
    إذا (!معلومات) {
        vc_dispmanx_display_close(handle);
        أرجع; // oh well
    }

    معلومات->dispman_display = handle;

    display.اندروني = معلومات;

    SDL_جوڙيو_Video_Display(&display, false);
}

bool RPI_VideoInit(SDL_VideoDevice *_this)
{
    // Initialize BCM Host
    bcm_host_init();

    جوڙيو_Disp_Man_XDisplay(DISPMANX_ID_MAIN_LCD);    // your default display
    جوڙيو_Disp_Man_XDisplay(DISPMANX_ID_FORCE_OTHER); // an "other" display...maybe DSI-connected screen while HDMI is your main

#جيڪڏهن_وصف_ٿيل SDL_داخلا_LINUXEV
    إذا (!SDL_EVDEV_Init()) {
        أرجع false;
    }
#جيڪڏهن_پورو

    RPI_InitMouse(_this);

    أرجع true;
}

فراغ RPI_VideoQuit(SDL_VideoDevice *_this)
{
#جيڪڏهن_وصف_ٿيل SDL_داخلا_LINUXEV
    SDL_EVDEV_Quit();
#جيڪڏهن_پورو
}

ساكن فراغ RPI_vsync_callback(DISPMANX_UPDATE_HANDLE_T u, فراغ *معلومات)
{
    SDL_دري_معلومات *wdata = (SDL_دري_معلومات *)معلومات;

    SDL_تالو_Mutex(wdata->vsync_cond_mutex);
    SDL_SignalCondition(wdata->vsync_cond);
    SDL_UnlockMutex(wdata->vsync_cond_mutex);
}

bool RPI_Create_دري(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID create_props)
{
    SDL_دري_معلومات *wdata;
    SDL_VideoDisplay *display;
    SDL_Display_معلومات *displaydata;
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
    wdata = (SDL_دري_معلومات *)SDL_calloc(1, حجم(SDL_دري_معلومات));
    إذا (!wdata) {
        أرجع false;
    }
    display = SDL_Get_Video_Display_For_دري(دري);
    displaydata = display->اندروني;

    // Windows have one size for now
    دري->w = display->desktop_گهڻائي.w;
    دري->h = display->desktop_گهڻائي.h;

    // OpenGL ES is the law here, buddy
    دري->flags |= SDL_دري_OPENGL;

    // Create a dispman element and associate a window to it
    dst_rect.x = 0;
    dst_rect.y = 0;
    dst_rect.ويڪر = دري->w;
    dst_rect.اوچائي = دري->h;

    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.ويڪر = دري->w << 16;
    src_rect.اوچائي = دري->h << 16;

    env = SDL_GetHint(SDL_HINT_RPI_VIDEO_LAYER);
    إذا (env) {
        layer = SDL_atoi(env);
    }

    dispman_update = vc_dispmanx_update_شروعات(0);
    wdata->dispman_دري.element = vc_dispmanx_element_جوڙيو(dispman_update,
                                                            displaydata->dispman_display,
                                                            layer /* layer */,
                                                            &dst_rect,
                                                            0 /*src*/,
                                                            &src_rect,
                                                            DISPMANX_PROTECTION_NONE,
                                                            &dispman_alpha /*alpha*/,
                                                            0 /*clamp*/,
                                                            0 /*transform*/);
    wdata->dispman_دري.ويڪر = دري->w;
    wdata->dispman_دري.اوچائي = دري->h;
    vc_dispmanx_update_submit_sync(dispman_update);

    إذا (!_this->egl_معلومات) {
        إذا (!SDL_GL_ڀريو_Library(عدم)) {
            أرجع false;
        }
    }
    wdata->egl_surface = SDL_EGL_CreateSurface(_this, دري, (Native_دري_Type)&wdata->dispman_دري);

    إذا (wdata->egl_surface == EGL_NO_SURFACE) {
        أرجع SDL_سيٽ_Error("Could not create GLES window surface");
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
    دري->اندروني = wdata;

    // One window, it always has focus
    SDL_سيٽ_Mouse_Focus(دري);
    SDL_سيٽ_Keyboard_Focus(دري);

    // Window has been successfully created
    أرجع true;
}

فراغ RPI_Destroy_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    SDL_Display_معلومات *displaydata = SDL_Get_Display_Driver_معلومات_For_دري(دري);

    إذا (معلومات) {
        إذا (معلومات->double_بفر) {
            // Wait for vsync, and then stop vsync callbacks and destroy related stuff, if needed
            SDL_تالو_Mutex(معلومات->vsync_cond_mutex);
            SDL_WaitCondition(معلومات->vsync_cond, معلومات->vsync_cond_mutex);
            SDL_UnlockMutex(معلومات->vsync_cond_mutex);

            vc_dispmanx_vsync_callback(displaydata->dispman_display, عدم, عدم);

            SDL_DestroyCondition(معلومات->vsync_cond);
            SDL_DestroyMutex(معلومات->vsync_cond_mutex);
        }

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
        إذا (معلومات->egl_surface != EGL_NO_SURFACE) {
            SDL_EGL_DestroySurface(_this, معلومات->egl_surface);
        }
#جيڪڏهن_پورو
        SDL_free(معلومات);
        دري->اندروني = عدم;
    }
}

فراغ RPI_سيٽ_دري_Title(SDL_VideoDevice *_this, SDL_دري *دري)
{
}
bool RPI_سيٽ_دري_Position(SDL_VideoDevice *_this, SDL_دري *دري)
{
    أرجع SDL_Unsupported();
}
فراغ RPI_سيٽ_دري_سائيز(SDL_VideoDevice *_this, SDL_دري *دري)
{
}
فراغ RPI_Show_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
}
فراغ RPI_Hide_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
}
فراغ RPI_Raise_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
}
فراغ RPI_Maximize_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
}
فراغ RPI_Minimize_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
}
فراغ RPI_Restore_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_RPI
