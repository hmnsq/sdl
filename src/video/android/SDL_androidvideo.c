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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_ANDROID

// Android SDL video driver implementation

#ضمن "../SDL_sysvideo.h"
#ضمن "../SDL_pixels_c.h"
#ضمن "../../events/SDL_events_c.h"
#ضمن "../../events/SDL_windowevents_c.h"
#ضمن "../../SDL_hints_c.h"

#ضمن "SDL_androidvideo.h"
#ضمن "SDL_androidgl.h"
#ضمن "SDL_androidclipboard.h"
#ضمن "SDL_androidevents.h"
#ضمن "SDL_androidkeyboard.h"
#ضمن "SDL_androidmouse.h"
#ضمن "SDL_androidtouch.h"
#ضمن "SDL_androidwindow.h"
#ضمن "SDL_androidvulkan.h"
#ضمن "SDL_androidmessagebox.h"

#تعریف_کن ANDROID_VID_DRIVER_NAME "android"

// Initialization/Query functions
ساكن bool Android_VideoInit(SDL_VideoDevice *_this);
ساكن فراغ Android_VideoQuit(SDL_VideoDevice *_this);

#ضمن "../SDL_egl_c.h"
#تعریف_کن Android_GLES_Get_Proc_آدرس  SDL_EGL_Get_Proc_آدرس_داخلی
#تعریف_کن Android_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#تعریف_کن Android_GLES_مجموعه_جابجا_Interval SDL_EGL_مجموعه_جابجا_Interval
#تعریف_کن Android_GLES_Get_جابجا_Interval SDL_EGL_Get_جابجا_Interval
#تعریف_کن Android_GLES_DestroyContext   SDL_EGL_DestroyContext

// Android driver bootstrap functions

// These are filled in with real values in Android_SetScreenResolution on init (before SDL_main())
صحيح Android_Surface_عرض = 0;
صحيح Android_Surface_ارتفاع = 0;
ساكن صحيح Android_Device_عرض = 0;
ساكن صحيح Android_Device_ارتفاع = 0;
ساكن Uint32 Android_ScreenFormat = SDL_PIXELFORMAT_RGB565; // Default SurfaceView format, in case this is queried before being filled
عائم Android_ScreenDensity = 1.0f;
ساكن عائم Android_Screen_نرخ = 0.0f;
ساكن عائم Android_ScreenHDRHeadroom = 1.0f;
ساكن SDL_DisplayOrientation Android_ScreenOrientation = SDL_ORIENTATION_UNKNOWN;
صحيح Android_امن_Inset_چپ = 0;
صحيح Android_امن_Inset_راست = 0;
صحيح Android_امن_Inset_بالاترین = 0;
صحيح Android_امن_Inset_Bottom = 0;
ساكن SDL_SystemTheme Android_SystemTheme;

ساكن bool Android_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    أرجع Android_JNI_SuspendScreenSaver(_this->suspend_screensaver);
}

ساكن فراغ Android_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->داخلی);
    SDL_free(device);
}

// Input is part of video for Android, so this goes here.
ساكن فراغ SDLCALL Android_Video_داخلی_Hint_Callback(
    فراغ *userdata,
    ثابت حرف *name,
    ثابت حرف *oldvalue,
    ثابت حرف *newvalue)
{
    Android_JNI_مجموعه_پشت_Button_Trap_فعال(SDL_GetStringBoolean(newvalue, false));
}

ساكن SDL_VideoDevice *Android_CreateDevice(فراغ)
{
    SDL_VideoDevice *device;
    SDL_Video_داده *داده;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (!device) {
        أرجع عدم;
    }

    داده = (SDL_Video_داده *)SDL_calloc(1, حجم(SDL_Video_داده));
    إذا (!داده) {
        SDL_free(device);
        أرجع عدم;
    }

    device->داخلی = داده;
    device->system_theme = Android_SystemTheme;

    // Set the function pointers
    device->VideoInit = Android_VideoInit;
    device->VideoQuit = Android_VideoQuit;

    device->CreateSDLWindow = Android_Create_پنجره;
    device->مجموعه_پنجره_Title = Android_مجموعه_پنجره_Title;
    device->مجموعه_پنجره_Fullscreen = Android_مجموعه_پنجره_Fullscreen;
    device->Minimize_پنجره = Android_Minimize_پنجره;
    device->مجموعه_پنجره_Resizable = Android_مجموعه_پنجره_Resizable;
    device->Destroy_پنجره = Android_Destroy_پنجره;

    device->حرر = Android_DeleteDevice;

    // GL pointers
#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
    device->GL_بارگیری_Library = Android_GLES_بارگیری_Library;
    device->GL_Get_Proc_آدرس = Android_GLES_Get_Proc_آدرس;
    device->GL_UnloadLibrary = Android_GLES_UnloadLibrary;
    device->GL_CreateContext = Android_GLES_CreateContext;
    device->GL_MakeCurrent = Android_GLES_MakeCurrent;
    device->GL_مجموعه_جابجا_Interval = Android_GLES_مجموعه_جابجا_Interval;
    device->GL_Get_جابجا_Interval = Android_GLES_Get_جابجا_Interval;
    device->GL_جابجا_پنجره = Android_GLES_جابجا_پنجره;
    device->GL_DestroyContext = Android_GLES_DestroyContext;
#پایان_اگر

#اگر_تعریف_شده SDL_VIDEO_VULKAN
    device->Vulkan_بارگیری_Library = Android_Vulkan_بارگیری_Library;
    device->Vulkan_UnloadLibrary = Android_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = Android_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = Android_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = Android_Vulkan_DestroySurface;
#پایان_اگر

    // Screensaver
    device->SuspendScreenSaver = Android_SuspendScreenSaver;

    // Screen keyboard
    device->HasScreenKeyboardSupport = Android_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = Android_ShowScreenKeyboard;
    device->HideScreenKeyboard = Android_HideScreenKeyboard;

    // Clipboard
    device->مجموعه_Clipboard_متن = Android_مجموعه_Clipboard_متن;
    device->Get_Clipboard_متن = Android_Get_Clipboard_متن;
    device->Has_Clipboard_متن = Android_Has_Clipboard_متن;

    device->device_caps = VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS;

    أرجع device;
}

VideoBootStrap Android_bootstrap = {
    ANDROID_VID_DRIVER_NAME, "SDL Android video driver",
    Android_CreateDevice,
    Android_Show_پیام_Box,
    false
};

bool Android_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_داده *videodata = _this->داخلی;
    SDL_DisplayID displayID;
    SDL_VideoDisplay *display;
    SDL_Display_نما نما;

    videodata->isPaused = false;
    videodata->isPausing = false;

    SDL_zero(نما);
    نما.format = Android_ScreenFormat;
    نما.w = Android_Device_عرض;
    نما.h = Android_Device_ارتفاع;
    نما.refresh_نرخ = Android_Screen_نرخ;

    displayID = SDL_جمع_کن_Basic_Video_Display(&نما);
    إذا (displayID == 0) {
        أرجع false;
    }
    display = SDL_GetVideoDisplay(displayID);
    display->natural_orientation = Android_JNI_GetDisplayNaturalOrientation();
    display->current_orientation = Android_JNI_GetDisplayCurrentOrientation();
    display->content_scale = Android_ScreenDensity;
    Android_مجموعه_Screen_HDRHeadroom(Android_ScreenHDRHeadroom);

    SDL_جمع_کن_Hint_Callback(SDL_HINT_ANDROID_TRAP_پشت_BUTTON, Android_Video_داخلی_Hint_Callback, 0);

    Android_InitTouch();

    Android_InitMouse();

    // We're done!
    أرجع true;
}

فراغ Android_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_RemoveHintCallback(SDL_HINT_ANDROID_TRAP_پشت_BUTTON, Android_Video_داخلی_Hint_Callback, 0);
    Android_QuitMouse();
    Android_QuitTouch();
}

فراغ Android_مجموعه_Screen_Resolution(صحيح surface_عرض, صحيح surface_ارتفاع, صحيح device_عرض, صحيح device_ارتفاع, عائم density, عائم نرخ)
{
    Android_Surface_عرض = surface_عرض;
    Android_Surface_ارتفاع = surface_ارتفاع;
    Android_Device_عرض = device_عرض;
    Android_Device_ارتفاع = device_ارتفاع;
    Android_ScreenDensity = (density > 0.0f) ? density : 1.0f;
    Android_Screen_نرخ = نرخ;
}

فراغ Android_مجموعه_Screen_HDRHeadroom(عائم headroom)
{
    Android_ScreenHDRHeadroom = headroom;

    SDL_VideoDevice *device = SDL_GetVideoDevice();
    إذا (device && device->رقم_displays > 0) {
        SDL_VideoDisplay *display = device->displays[0];
        SDL_HDROutputProperties HDR;

        HDR.SDR_white_level = 1.0f;
        HDR.HDR_headroom = headroom;
        SDL_مجموعه_Display_HDRProperties(display, &HDR);
    }
}

ساكن Uint32 format_مقصد_pixel_Format(صحيح format)
{
    Uint32 pf;
    إذا (format == AHARDWAREBUFFER_FORMAT_R8G8B8A8_UNORM) { // 1
        pf = SDL_PIXELFORMAT_RGBA8888;
    } وإلا إذا (format == AHARDWAREBUFFER_FORMAT_R8G8B8X8_UNORM) { // 2
        pf = SDL_PIXELFORMAT_RGBX8888;
    } وإلا إذا (format == AHARDWAREBUFFER_FORMAT_R8G8B8_UNORM) { // 3
        pf = SDL_PIXELFORMAT_RGB24;
    } وإلا إذا (format == AHARDWAREBUFFER_FORMAT_R5G6B5_UNORM) { // 4
        pf = SDL_PIXELFORMAT_RGB565;
    } وإلا إذا (format == 5) {
        pf = SDL_PIXELFORMAT_BGRA8888;
    } وإلا إذا (format == 6) {
        pf = SDL_PIXELFORMAT_RGBA5551;
    } وإلا إذا (format == 7) {
        pf = SDL_PIXELFORMAT_RGBA4444;
    } وإلا إذا (format == 0x115) {
        // HAL_PIXEL_FORMAT_BGR_565
        pf = SDL_PIXELFORMAT_RGB565;
    } وإلا {
        pf = SDL_PIXELFORMAT_UNKNOWN;
    }
    أرجع pf;
}

فراغ Android_مجموعه_Format(صحيح format_wanted, صحيح format_got)
{
    Uint32 pf_wanted;
    Uint32 pf_got;

    pf_wanted = format_مقصد_pixel_Format(format_wanted);
    pf_got = format_مقصد_pixel_Format(format_got);

    Android_ScreenFormat = pf_got;

    SDL_Log("pixel format wanted %s (%d), got %s (%d)",
            SDL_GetPixelFormatName(pf_wanted), format_wanted,
            SDL_GetPixelFormatName(pf_got), format_got);
}

ساكن فراغ Android_SendOrientationUpdate(فراغ)
{
    /* If we've received a compatible resize event, update the
     * orientation immediately, otherwise wait for the display
     * resize event.
     */
    SDL_VideoDevice *device = SDL_GetVideoDevice();
    إذا (device && device->رقم_displays > 0) {
        SDL_VideoDisplay *display = device->displays[0];
        bool نما_landscape = (display->desktop_نما.w > display->desktop_نما.h);
        bool sensor_landscape = (Android_ScreenOrientation == SDL_ORIENTATION_LANDSCAPE || Android_ScreenOrientation == SDL_ORIENTATION_LANDSCAPE_FLIPPED);
        إذا (sensor_landscape == نما_landscape) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_ORIENTATION, Android_ScreenOrientation, 0);
        }
    }
}

فراغ Android_مجموعه_Orientation(SDL_DisplayOrientation orientation)
{
    Android_ScreenOrientation = orientation;
    Android_SendOrientationUpdate();
}

فراغ Android_SendResize(SDL_پنجره *پنجره)
{
    /*
      Update the resolution of the desktop mode, so that the window
      can be properly resized. The screen resolution change can for
      example happen when the Activity enters or exits immersive mode,
      which can happen after VideoInit().
    */
    SDL_VideoDevice *device = SDL_GetVideoDevice();
    إذا (device && device->رقم_displays > 0) {
        SDL_VideoDisplay *display = device->displays[0];
        SDL_Display_نما desktop_نما;

        SDL_zero(desktop_نما);
        desktop_نما.format = Android_ScreenFormat;
        desktop_نما.w = Android_Device_عرض;
        desktop_نما.h = Android_Device_ارتفاع;
        desktop_نما.refresh_نرخ = Android_Screen_نرخ;
        SDL_مجموعه_Desktop_Display_نما(display, &desktop_نما);
        Android_SendOrientationUpdate();
    }

    إذا (پنجره) {
        SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_RESIZED, Android_Surface_عرض, Android_Surface_ارتفاع);
    }
}

فراغ Android_مجموعه_پنجره_امن_Area_Insets(صحيح چپ, صحيح راست, صحيح بالاترین, صحيح bottom)
{
    Android_امن_Inset_چپ = چپ;
    Android_امن_Inset_راست = راست;
    Android_امن_Inset_بالاترین = بالاترین;
    Android_امن_Inset_Bottom = bottom;

    إذا (Android_پنجره) {
        SDL_مجموعه_پنجره_امن_Area_Insets(Android_پنجره, چپ, راست, بالاترین, bottom);
    }
}

فراغ Android_مجموعه_Dark_نما(bool enabled)
{
    SDL_VideoDevice *device = SDL_GetVideoDevice();

    إذا (enabled) {
        Android_SystemTheme = SDL_SYSTEM_THEME_DARK;
    } وإلا {
        Android_SystemTheme = SDL_SYSTEM_THEME_LIGHT;
    }

    إذا (device) {
        SDL_مجموعه_System_Theme(Android_SystemTheme);
    }
}

#پایان_اگر // SDL_VIDEO_DRIVER_ANDROID
