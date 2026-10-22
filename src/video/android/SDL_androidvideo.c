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
#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_ANDROID

// Android SDL video driver implementation

#شامل "../SDL_sysvideo.h"
#شامل "../SDL_pixels_c.h"
#شامل "../../events/SDL_events_c.h"
#شامل "../../events/SDL_windowevents_c.h"
#شامل "../../SDL_hints_c.h"

#شامل "SDL_androidvideo.h"
#شامل "SDL_androidgl.h"
#شامل "SDL_androidclipboard.h"
#شامل "SDL_androidevents.h"
#شامل "SDL_androidkeyboard.h"
#شامل "SDL_androidmouse.h"
#شامل "SDL_androidtouch.h"
#شامل "SDL_androidwindow.h"
#شامل "SDL_androidvulkan.h"
#شامل "SDL_androidmessagebox.h"

#تعریف_کرو ANDROID_VID_DRIVER_NAME "android"

// Initialization/Query functions
ساکن bool Android_VideoInit(SDL_VideoDevice *_this);
ساکن خالی Android_VideoQuit(SDL_VideoDevice *_this);

#شامل "../SDL_egl_c.h"
#تعریف_کرو Android_GLES_Get_Proc_پتہ  SDL_EGL_Get_Proc_پتہ_اندرونی
#تعریف_کرو Android_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#تعریف_کرو Android_GLES_سیٹ_تبادلہ_Interval SDL_EGL_سیٹ_تبادلہ_Interval
#تعریف_کرو Android_GLES_Get_تبادلہ_Interval SDL_EGL_Get_تبادلہ_Interval
#تعریف_کرو Android_GLES_DestroyContext   SDL_EGL_DestroyContext

// Android driver bootstrap functions

// These are filled in with real values in Android_SetScreenResolution on init (before SDL_main())
صحیح Android_Surface_چوڑائی = 0;
صحیح Android_Surface_اونچائی = 0;
ساکن صحیح Android_Device_چوڑائی = 0;
ساکن صحیح Android_Device_اونچائی = 0;
ساکن Uint32 Android_ScreenFormat = SDL_PIXELFORMAT_RGB565; // Default SurfaceView format, in case this is queried before being filled
اعشاری Android_ScreenDensity = 1.0f;
ساکن اعشاری Android_Screen_شرح = 0.0f;
ساکن اعشاری Android_ScreenHDRHeadroom = 1.0f;
ساکن SDL_DisplayOrientation Android_ScreenOrientation = SDL_ORIENTATION_UNKNOWN;
صحیح Android_محفوظ_Inset_بایاں = 0;
صحیح Android_محفوظ_Inset_دایاں = 0;
صحیح Android_محفوظ_Inset_چوٹی = 0;
صحیح Android_محفوظ_Inset_Bottom = 0;
ساکن SDL_SystemTheme Android_SystemTheme;

ساکن bool Android_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    واپس Android_JNI_SuspendScreenSaver(_this->suspend_screensaver);
}

ساکن خالی Android_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->اندرونی_2);
    SDL_free(device);
}

// Input is part of video for Android, so this goes here.
ساکن خالی SDLCALL Android_Video_اندرونی_Hint_Callback(
    خالی *userdata,
    ثابت حرف *name,
    ثابت حرف *oldvalue,
    ثابت حرف *newvalue)
{
    Android_JNI_سیٹ_عقب_Button_Trap_فعال(SDL_GetStringBoolean(newvalue, false));
}

ساکن SDL_VideoDevice *Android_CreateDevice(خالی)
{
    SDL_VideoDevice *device;
    SDL_Video_ڈیٹا *ڈیٹا;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    اگر (!device) {
        واپس تہی;
    }

    ڈیٹا = (SDL_Video_ڈیٹا *)SDL_calloc(1, حجم(SDL_Video_ڈیٹا));
    اگر (!ڈیٹا) {
        SDL_free(device);
        واپس تہی;
    }

    device->اندرونی_2 = ڈیٹا;
    device->system_theme = Android_SystemTheme;

    // Set the function pointers
    device->VideoInit = Android_VideoInit;
    device->VideoQuit = Android_VideoQuit;

    device->CreateSDLWindow = Android_Create_کھڑکی;
    device->سیٹ_کھڑکی_Title = Android_سیٹ_کھڑکی_Title;
    device->سیٹ_کھڑکی_Fullscreen = Android_سیٹ_کھڑکی_Fullscreen;
    device->Minimize_کھڑکی = Android_Minimize_کھڑکی;
    device->سیٹ_کھڑکی_Resizable = Android_سیٹ_کھڑکی_Resizable;
    device->Destroy_کھڑکی = Android_Destroy_کھڑکی;

    device->آزاد = Android_DeleteDevice;

    // GL pointers
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    device->GL_بھرو_Library = Android_GLES_بھرو_Library;
    device->GL_Get_Proc_پتہ = Android_GLES_Get_Proc_پتہ;
    device->GL_UnloadLibrary = Android_GLES_UnloadLibrary;
    device->GL_CreateContext = Android_GLES_CreateContext;
    device->GL_MakeCurrent = Android_GLES_MakeCurrent;
    device->GL_سیٹ_تبادلہ_Interval = Android_GLES_سیٹ_تبادلہ_Interval;
    device->GL_Get_تبادلہ_Interval = Android_GLES_Get_تبادلہ_Interval;
    device->GL_تبادلہ_کھڑکی = Android_GLES_تبادلہ_کھڑکی;
    device->GL_DestroyContext = Android_GLES_DestroyContext;
#اگر_ختم

#اگر_تعریف_شدہ SDL_VIDEO_VULKAN
    device->Vulkan_بھرو_Library = Android_Vulkan_بھرو_Library;
    device->Vulkan_UnloadLibrary = Android_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = Android_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = Android_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = Android_Vulkan_DestroySurface;
#اگر_ختم

    // Screensaver
    device->SuspendScreenSaver = Android_SuspendScreenSaver;

    // Screen keyboard
    device->HasScreenKeyboardSupport = Android_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = Android_ShowScreenKeyboard;
    device->HideScreenKeyboard = Android_HideScreenKeyboard;

    // Clipboard
    device->سیٹ_Clipboard_متن = Android_سیٹ_Clipboard_متن;
    device->Get_Clipboard_متن = Android_Get_Clipboard_متن;
    device->Has_Clipboard_متن = Android_Has_Clipboard_متن;

    device->device_caps = VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS;

    واپس device;
}

VideoBootStrap Android_bootstrap = {
    ANDROID_VID_DRIVER_NAME, "SDL Android video driver",
    Android_CreateDevice,
    Android_Show_پیغام_Box,
    false
};

bool Android_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;
    SDL_DisplayID displayID;
    SDL_VideoDisplay *display;
    SDL_Display_منوال منوال;

    videodata->isPaused = false;
    videodata->isPausing = false;

    SDL_zero(منوال);
    منوال.format = Android_ScreenFormat;
    منوال.w = Android_Device_چوڑائی;
    منوال.h = Android_Device_اونچائی;
    منوال.refresh_شرح = Android_Screen_شرح;

    displayID = SDL_جوڑو_Basic_Video_Display(&منوال);
    اگر (displayID == 0) {
        واپس false;
    }
    display = SDL_GetVideoDisplay(displayID);
    display->natural_orientation = Android_JNI_GetDisplayNaturalOrientation();
    display->current_orientation = Android_JNI_GetDisplayCurrentOrientation();
    display->content_scale = Android_ScreenDensity;
    Android_سیٹ_Screen_HDRHeadroom(Android_ScreenHDRHeadroom);

    SDL_جوڑو_Hint_Callback(SDL_HINT_ANDROID_TRAP_عقب_BUTTON, Android_Video_اندرونی_Hint_Callback, 0);

    Android_InitTouch();

    Android_InitMouse();

    // We're done!
    واپس true;
}

خالی Android_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_RemoveHintCallback(SDL_HINT_ANDROID_TRAP_عقب_BUTTON, Android_Video_اندرونی_Hint_Callback, 0);
    Android_QuitMouse();
    Android_QuitTouch();
}

خالی Android_سیٹ_Screen_Resolution(صحیح surface_چوڑائی, صحیح surface_اونچائی, صحیح device_چوڑائی, صحیح device_اونچائی, اعشاری density, اعشاری شرح)
{
    Android_Surface_چوڑائی = surface_چوڑائی;
    Android_Surface_اونچائی = surface_اونچائی;
    Android_Device_چوڑائی = device_چوڑائی;
    Android_Device_اونچائی = device_اونچائی;
    Android_ScreenDensity = (density > 0.0f) ? density : 1.0f;
    Android_Screen_شرح = شرح;
}

خالی Android_سیٹ_Screen_HDRHeadroom(اعشاری headroom)
{
    Android_ScreenHDRHeadroom = headroom;

    SDL_VideoDevice *device = SDL_GetVideoDevice();
    اگر (device && device->عدد_displays > 0) {
        SDL_VideoDisplay *display = device->displays[0];
        SDL_HDROutputProperties HDR;

        HDR.SDR_white_level = 1.0f;
        HDR.HDR_headroom = headroom;
        SDL_سیٹ_Display_HDRProperties(display, &HDR);
    }
}

ساکن Uint32 format_مقصد_pixel_Format(صحیح format)
{
    Uint32 pf;
    اگر (format == AHARDWAREBUFFER_FORMAT_R8G8B8A8_UNORM) { // 1
        pf = SDL_PIXELFORMAT_RGBA8888;
    } ورنہ اگر (format == AHARDWAREBUFFER_FORMAT_R8G8B8X8_UNORM) { // 2
        pf = SDL_PIXELFORMAT_RGBX8888;
    } ورنہ اگر (format == AHARDWAREBUFFER_FORMAT_R8G8B8_UNORM) { // 3
        pf = SDL_PIXELFORMAT_RGB24;
    } ورنہ اگر (format == AHARDWAREBUFFER_FORMAT_R5G6B5_UNORM) { // 4
        pf = SDL_PIXELFORMAT_RGB565;
    } ورنہ اگر (format == 5) {
        pf = SDL_PIXELFORMAT_BGRA8888;
    } ورنہ اگر (format == 6) {
        pf = SDL_PIXELFORMAT_RGBA5551;
    } ورنہ اگر (format == 7) {
        pf = SDL_PIXELFORMAT_RGBA4444;
    } ورنہ اگر (format == 0x115) {
        // HAL_PIXEL_FORMAT_BGR_565
        pf = SDL_PIXELFORMAT_RGB565;
    } ورنہ {
        pf = SDL_PIXELFORMAT_UNKNOWN;
    }
    واپس pf;
}

خالی Android_سیٹ_Format(صحیح format_wanted, صحیح format_got)
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

ساکن خالی Android_SendOrientationUpdate(خالی)
{
    /* If we've received a compatible resize event, update the
     * orientation immediately, otherwise wait for the display
     * resize event.
     */
    SDL_VideoDevice *device = SDL_GetVideoDevice();
    اگر (device && device->عدد_displays > 0) {
        SDL_VideoDisplay *display = device->displays[0];
        bool منوال_landscape = (display->desktop_منوال.w > display->desktop_منوال.h);
        bool sensor_landscape = (Android_ScreenOrientation == SDL_ORIENTATION_LANDSCAPE || Android_ScreenOrientation == SDL_ORIENTATION_LANDSCAPE_FLIPPED);
        اگر (sensor_landscape == منوال_landscape) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_ORIENTATION, Android_ScreenOrientation, 0);
        }
    }
}

خالی Android_سیٹ_Orientation(SDL_DisplayOrientation orientation)
{
    Android_ScreenOrientation = orientation;
    Android_SendOrientationUpdate();
}

خالی Android_SendResize(SDL_کھڑکی *کھڑکی)
{
    /*
      Update the resolution of the desktop mode, so that the window
      can be properly resized. The screen resolution change can for
      example happen when the Activity enters or exits immersive mode,
      which can happen after VideoInit().
    */
    SDL_VideoDevice *device = SDL_GetVideoDevice();
    اگر (device && device->عدد_displays > 0) {
        SDL_VideoDisplay *display = device->displays[0];
        SDL_Display_منوال desktop_منوال;

        SDL_zero(desktop_منوال);
        desktop_منوال.format = Android_ScreenFormat;
        desktop_منوال.w = Android_Device_چوڑائی;
        desktop_منوال.h = Android_Device_اونچائی;
        desktop_منوال.refresh_شرح = Android_Screen_شرح;
        SDL_سیٹ_Desktop_Display_منوال(display, &desktop_منوال);
        Android_SendOrientationUpdate();
    }

    اگر (کھڑکی) {
        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESIZED, Android_Surface_چوڑائی, Android_Surface_اونچائی);
    }
}

خالی Android_سیٹ_کھڑکی_محفوظ_Area_Insets(صحیح بایاں, صحیح دایاں, صحیح چوٹی, صحیح bottom)
{
    Android_محفوظ_Inset_بایاں = بایاں;
    Android_محفوظ_Inset_دایاں = دایاں;
    Android_محفوظ_Inset_چوٹی = چوٹی;
    Android_محفوظ_Inset_Bottom = bottom;

    اگر (Android_کھڑکی) {
        SDL_سیٹ_کھڑکی_محفوظ_Area_Insets(Android_کھڑکی, بایاں, دایاں, چوٹی, bottom);
    }
}

خالی Android_سیٹ_Dark_منوال(bool enabled)
{
    SDL_VideoDevice *device = SDL_GetVideoDevice();

    اگر (enabled) {
        Android_SystemTheme = SDL_SYSTEM_THEME_DARK;
    } ورنہ {
        Android_SystemTheme = SDL_SYSTEM_THEME_LIGHT;
    }

    اگر (device) {
        SDL_سیٹ_System_Theme(Android_SystemTheme);
    }
}

#اگر_ختم // SDL_VIDEO_DRIVER_ANDROID
