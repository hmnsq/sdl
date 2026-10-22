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

#که_تعریف_شوی SDL_VIDEO_DRIVER_ANDROID

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

#تعریف_کړه ANDROID_VID_DRIVER_NAME "android"

// Initialization/Query functions
ساكن bool Android_VideoInit(SDL_VideoDevice *_this);
ساكن فراغ Android_VideoQuit(SDL_VideoDevice *_this);

#ضمن "../SDL_egl_c.h"
#تعریف_کړه Android_GLES_Get_Proc_پته  SDL_EGL_Get_Proc_پته_دننی
#تعریف_کړه Android_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#تعریف_کړه Android_GLES_سېټ_بدلون_Interval SDL_EGL_سېټ_بدلون_Interval
#تعریف_کړه Android_GLES_Get_بدلون_Interval SDL_EGL_Get_بدلون_Interval
#تعریف_کړه Android_GLES_DestroyContext   SDL_EGL_DestroyContext

// Android driver bootstrap functions

// These are filled in with real values in Android_SetScreenResolution on init (before SDL_main())
صحيح Android_Surface_پلنوالی = 0;
صحيح Android_Surface_لوړوالی = 0;
ساكن صحيح Android_Device_پلنوالی = 0;
ساكن صحيح Android_Device_لوړوالی = 0;
ساكن Uint32 Android_ScreenFormat = SDL_PIXELFORMAT_RGB565; // Default SurfaceView format, in case this is queried before being filled
عائم Android_ScreenDensity = 1.0f;
ساكن عائم Android_Screen_شرح = 0.0f;
ساكن عائم Android_ScreenHDRHeadroom = 1.0f;
ساكن SDL_DisplayOrientation Android_ScreenOrientation = SDL_ORIENTATION_UNKNOWN;
صحيح Android_خوندي_Inset_کیڼ = 0;
صحيح Android_خوندي_Inset_ښی = 0;
صحيح Android_خوندي_Inset_سر = 0;
صحيح Android_خوندي_Inset_Bottom = 0;
ساكن SDL_SystemTheme Android_SystemTheme;

ساكن bool Android_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    أرجع Android_JNI_SuspendScreenSaver(_this->suspend_screensaver);
}

ساكن فراغ Android_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->دننی);
    SDL_free(device);
}

// Input is part of video for Android, so this goes here.
ساكن فراغ SDLCALL Android_Video_دننی_Hint_Callback(
    فراغ *userdata,
    ثابت حرف *name,
    ثابت حرف *oldvalue,
    ثابت حرف *newvalue)
{
    Android_JNI_سېټ_شا_Button_Trap_فعال(SDL_GetStringBoolean(newvalue, false));
}

ساكن SDL_VideoDevice *Android_CreateDevice(فراغ)
{
    SDL_VideoDevice *device;
    SDL_Video_معلومات *معلومات;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (!device) {
        أرجع عدم;
    }

    معلومات = (SDL_Video_معلومات *)SDL_calloc(1, حجم(SDL_Video_معلومات));
    إذا (!معلومات) {
        SDL_free(device);
        أرجع عدم;
    }

    device->دننی = معلومات;
    device->system_theme = Android_SystemTheme;

    // Set the function pointers
    device->VideoInit = Android_VideoInit;
    device->VideoQuit = Android_VideoQuit;

    device->CreateSDLWindow = Android_Create_کړکۍ;
    device->سېټ_کړکۍ_Title = Android_سېټ_کړکۍ_Title;
    device->سېټ_کړکۍ_Fullscreen = Android_سېټ_کړکۍ_Fullscreen;
    device->Minimize_کړکۍ = Android_Minimize_کړکۍ;
    device->سېټ_کړکۍ_Resizable = Android_سېټ_کړکۍ_Resizable;
    device->Destroy_کړکۍ = Android_Destroy_کړکۍ;

    device->حرر = Android_DeleteDevice;

    // GL pointers
#که_تعریف_شوی SDL_VIDEO_OPENGL_EGL
    device->GL_بارول_Library = Android_GLES_بارول_Library;
    device->GL_Get_Proc_پته = Android_GLES_Get_Proc_پته;
    device->GL_UnloadLibrary = Android_GLES_UnloadLibrary;
    device->GL_CreateContext = Android_GLES_CreateContext;
    device->GL_MakeCurrent = Android_GLES_MakeCurrent;
    device->GL_سېټ_بدلون_Interval = Android_GLES_سېټ_بدلون_Interval;
    device->GL_Get_بدلون_Interval = Android_GLES_Get_بدلون_Interval;
    device->GL_بدلون_کړکۍ = Android_GLES_بدلون_کړکۍ;
    device->GL_DestroyContext = Android_GLES_DestroyContext;
#د_که_پای

#که_تعریف_شوی SDL_VIDEO_VULKAN
    device->Vulkan_بارول_Library = Android_Vulkan_بارول_Library;
    device->Vulkan_UnloadLibrary = Android_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = Android_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = Android_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = Android_Vulkan_DestroySurface;
#د_که_پای

    // Screensaver
    device->SuspendScreenSaver = Android_SuspendScreenSaver;

    // Screen keyboard
    device->HasScreenKeyboardSupport = Android_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = Android_ShowScreenKeyboard;
    device->HideScreenKeyboard = Android_HideScreenKeyboard;

    // Clipboard
    device->سېټ_Clipboard_متن = Android_سېټ_Clipboard_متن;
    device->Get_Clipboard_متن = Android_Get_Clipboard_متن;
    device->Has_Clipboard_متن = Android_Has_Clipboard_متن;

    device->device_caps = VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS;

    أرجع device;
}

VideoBootStrap Android_bootstrap = {
    ANDROID_VID_DRIVER_NAME, "SDL Android video driver",
    Android_CreateDevice,
    Android_Show_پیغام_Box,
    false
};

bool Android_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *videodata = _this->دننی;
    SDL_DisplayID displayID;
    SDL_VideoDisplay *display;
    SDL_Display_ډېرپېښ ډېرپېښ;

    videodata->isPaused = false;
    videodata->isPausing = false;

    SDL_zero(ډېرپېښ);
    ډېرپېښ.format = Android_ScreenFormat;
    ډېرپېښ.w = Android_Device_پلنوالی;
    ډېرپېښ.h = Android_Device_لوړوالی;
    ډېرپېښ.refresh_شرح = Android_Screen_شرح;

    displayID = SDL_جمع_کړه_Basic_Video_Display(&ډېرپېښ);
    إذا (displayID == 0) {
        أرجع false;
    }
    display = SDL_GetVideoDisplay(displayID);
    display->natural_orientation = Android_JNI_GetDisplayNaturalOrientation();
    display->current_orientation = Android_JNI_GetDisplayCurrentOrientation();
    display->content_scale = Android_ScreenDensity;
    Android_سېټ_Screen_HDRHeadroom(Android_ScreenHDRHeadroom);

    SDL_جمع_کړه_Hint_Callback(SDL_HINT_ANDROID_TRAP_شا_BUTTON, Android_Video_دننی_Hint_Callback, 0);

    Android_InitTouch();

    Android_InitMouse();

    // We're done!
    أرجع true;
}

فراغ Android_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_RemoveHintCallback(SDL_HINT_ANDROID_TRAP_شا_BUTTON, Android_Video_دننی_Hint_Callback, 0);
    Android_QuitMouse();
    Android_QuitTouch();
}

فراغ Android_سېټ_Screen_Resolution(صحيح surface_پلنوالی, صحيح surface_لوړوالی, صحيح device_پلنوالی, صحيح device_لوړوالی, عائم density, عائم شرح)
{
    Android_Surface_پلنوالی = surface_پلنوالی;
    Android_Surface_لوړوالی = surface_لوړوالی;
    Android_Device_پلنوالی = device_پلنوالی;
    Android_Device_لوړوالی = device_لوړوالی;
    Android_ScreenDensity = (density > 0.0f) ? density : 1.0f;
    Android_Screen_شرح = شرح;
}

فراغ Android_سېټ_Screen_HDRHeadroom(عائم headroom)
{
    Android_ScreenHDRHeadroom = headroom;

    SDL_VideoDevice *device = SDL_GetVideoDevice();
    إذا (device && device->عدد_displays > 0) {
        SDL_VideoDisplay *display = device->displays[0];
        SDL_HDROutputProperties HDR;

        HDR.SDR_white_level = 1.0f;
        HDR.HDR_headroom = headroom;
        SDL_سېټ_Display_HDRProperties(display, &HDR);
    }
}

ساكن Uint32 format_منزل_pixel_Format(صحيح format)
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

فراغ Android_سېټ_Format(صحيح format_wanted, صحيح format_got)
{
    Uint32 pf_wanted;
    Uint32 pf_got;

    pf_wanted = format_منزل_pixel_Format(format_wanted);
    pf_got = format_منزل_pixel_Format(format_got);

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
    إذا (device && device->عدد_displays > 0) {
        SDL_VideoDisplay *display = device->displays[0];
        bool ډېرپېښ_landscape = (display->desktop_ډېرپېښ.w > display->desktop_ډېرپېښ.h);
        bool sensor_landscape = (Android_ScreenOrientation == SDL_ORIENTATION_LANDSCAPE || Android_ScreenOrientation == SDL_ORIENTATION_LANDSCAPE_FLIPPED);
        إذا (sensor_landscape == ډېرپېښ_landscape) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_ORIENTATION, Android_ScreenOrientation, 0);
        }
    }
}

فراغ Android_سېټ_Orientation(SDL_DisplayOrientation orientation)
{
    Android_ScreenOrientation = orientation;
    Android_SendOrientationUpdate();
}

فراغ Android_SendResize(SDL_کړکۍ *کړکۍ)
{
    /*
      Update the resolution of the desktop mode, so that the window
      can be properly resized. The screen resolution change can for
      example happen when the Activity enters or exits immersive mode,
      which can happen after VideoInit().
    */
    SDL_VideoDevice *device = SDL_GetVideoDevice();
    إذا (device && device->عدد_displays > 0) {
        SDL_VideoDisplay *display = device->displays[0];
        SDL_Display_ډېرپېښ desktop_ډېرپېښ;

        SDL_zero(desktop_ډېرپېښ);
        desktop_ډېرپېښ.format = Android_ScreenFormat;
        desktop_ډېرپېښ.w = Android_Device_پلنوالی;
        desktop_ډېرپېښ.h = Android_Device_لوړوالی;
        desktop_ډېرپېښ.refresh_شرح = Android_Screen_شرح;
        SDL_سېټ_Desktop_Display_ډېرپېښ(display, &desktop_ډېرپېښ);
        Android_SendOrientationUpdate();
    }

    إذا (کړکۍ) {
        SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_RESIZED, Android_Surface_پلنوالی, Android_Surface_لوړوالی);
    }
}

فراغ Android_سېټ_کړکۍ_خوندي_Area_Insets(صحيح کیڼ, صحيح ښی, صحيح سر, صحيح bottom)
{
    Android_خوندي_Inset_کیڼ = کیڼ;
    Android_خوندي_Inset_ښی = ښی;
    Android_خوندي_Inset_سر = سر;
    Android_خوندي_Inset_Bottom = bottom;

    إذا (Android_کړکۍ) {
        SDL_سېټ_کړکۍ_خوندي_Area_Insets(Android_کړکۍ, کیڼ, ښی, سر, bottom);
    }
}

فراغ Android_سېټ_Dark_ډېرپېښ(bool enabled)
{
    SDL_VideoDevice *device = SDL_GetVideoDevice();

    إذا (enabled) {
        Android_SystemTheme = SDL_SYSTEM_THEME_DARK;
    } وإلا {
        Android_SystemTheme = SDL_SYSTEM_THEME_LIGHT;
    }

    إذا (device) {
        SDL_سېټ_System_Theme(Android_SystemTheme);
    }
}

#د_که_پای // SDL_VIDEO_DRIVER_ANDROID
