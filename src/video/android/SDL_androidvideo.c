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

#ifdef SDL_VIDEO_DRIVER_ANDROID

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

#define ANDROID_VID_DRIVER_NAME "android"

// Initialization/Query functions
ایستا bool Android_VideoInit(SDL_VideoDevice *_this);
ایستا تهی Android_VideoQuit(SDL_VideoDevice *_this);

#شامل "../SDL_egl_c.h"
#define Android_GLES_GetProcAddress  SDL_EGL_GetProcAddressInternal
#define Android_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#define Android_GLES_SetSwapInterval SDL_EGL_SetSwapInterval
#define Android_GLES_GetSwapInterval SDL_EGL_GetSwapInterval
#define Android_GLES_DestroyContext   SDL_EGL_DestroyContext

// Android driver bootstrap functions

// These are filled in with real values in Android_SetScreenResolution on init (before SDL_main())
صحیح Android_SurfaceWidth = 0;
صحیح Android_SurfaceHeight = 0;
ایستا صحیح Android_DeviceWidth = 0;
ایستا صحیح Android_DeviceHeight = 0;
ایستا Uint32 Android_ScreenFormat = SDL_PIXELFORMAT_RGB565; // Default SurfaceView format, in case this is queried before being filled
اعشاری Android_ScreenDensity = 1.0f;
ایستا اعشاری Android_ScreenRate = 0.0f;
ایستا اعشاری Android_ScreenHDRHeadroom = 1.0f;
ایستا SDL_DisplayOrientation Android_ScreenOrientation = SDL_ORIENTATION_UNKNOWN;
صحیح Android_Safe_Inset_چپ = 0;
صحیح Android_Safe_Inset_راست = 0;
صحیح Android_Safe_Inset_بالاترین = 0;
صحیح Android_SafeInsetBottom = 0;
ایستا SDL_SystemTheme Android_SystemTheme;

ایستا bool Android_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    بازگشت Android_JNI_SuspendScreenSaver(_this->suspend_screensaver);
}

ایستا تهی Android_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

// Input is part of video for Android, so this goes here.
ایستا تهی SDLCALL Android_Video_InternalHintCallback(
    تهی *userdata,
    ثابت نویسه *name,
    ثابت نویسه *oldvalue,
    ثابت نویسه *newvalue)
{
    Android_JNI_SetBackButtonTrapActive(SDL_GetStringBoolean(newvalue, false));
}

ایستا SDL_VideoDevice *Android_CreateDevice(تهی)
{
    SDL_VideoDevice *device;
    SDL_VideoData *data;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, اندازه(SDL_VideoDevice));
    اگر (!device) {
        بازگشت پوچ;
    }

    data = (SDL_VideoData *)SDL_calloc(1, اندازه(SDL_VideoData));
    اگر (!data) {
        SDL_free(device);
        بازگشت پوچ;
    }

    device->internal = data;
    device->system_theme = Android_SystemTheme;

    // Set the function pointers
    device->VideoInit = Android_VideoInit;
    device->VideoQuit = Android_VideoQuit;

    device->CreateSDLWindow = Android_CreateWindow;
    device->SetWindowTitle = Android_SetWindowTitle;
    device->SetWindowFullscreen = Android_SetWindowFullscreen;
    device->MinimizeWindow = Android_MinimizeWindow;
    device->SetWindowResizable = Android_SetWindowResizable;
    device->DestroyWindow = Android_DestroyWindow;

    device->آزاد = Android_DeleteDevice;

    // GL pointers
#ifdef SDL_VIDEO_OPENGL_EGL
    device->GL_LoadLibrary = Android_GLES_LoadLibrary;
    device->GL_GetProcAddress = Android_GLES_GetProcAddress;
    device->GL_UnloadLibrary = Android_GLES_UnloadLibrary;
    device->GL_CreateContext = Android_GLES_CreateContext;
    device->GL_MakeCurrent = Android_GLES_MakeCurrent;
    device->GL_SetSwapInterval = Android_GLES_SetSwapInterval;
    device->GL_GetSwapInterval = Android_GLES_GetSwapInterval;
    device->GL_SwapWindow = Android_GLES_SwapWindow;
    device->GL_DestroyContext = Android_GLES_DestroyContext;
#endif

#ifdef SDL_VIDEO_VULKAN
    device->Vulkan_LoadLibrary = Android_Vulkan_LoadLibrary;
    device->Vulkan_UnloadLibrary = Android_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = Android_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = Android_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = Android_Vulkan_DestroySurface;
#endif

    // Screensaver
    device->SuspendScreenSaver = Android_SuspendScreenSaver;

    // Screen keyboard
    device->HasScreenKeyboardSupport = Android_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = Android_ShowScreenKeyboard;
    device->HideScreenKeyboard = Android_HideScreenKeyboard;

    // Clipboard
    device->SetClipboardText = Android_SetClipboardText;
    device->GetClipboardText = Android_GetClipboardText;
    device->HasClipboardText = Android_HasClipboardText;

    device->device_caps = VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS;

    بازگشت device;
}

VideoBootStrap Android_bootstrap = {
    ANDROID_VID_DRIVER_NAME, "SDL Android video driver",
    Android_CreateDevice,
    Android_ShowMessageBox,
    false
};

bool Android_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_DisplayID displayID;
    SDL_VideoDisplay *display;
    SDL_DisplayMode mode;

    videodata->isPaused = false;
    videodata->isPausing = false;

    SDL_zero(mode);
    mode.format = Android_ScreenFormat;
    mode.w = Android_DeviceWidth;
    mode.h = Android_DeviceHeight;
    mode.refresh_rate = Android_ScreenRate;

    displayID = SDL_AddBasicVideoDisplay(&mode);
    اگر (displayID == 0) {
        بازگشت false;
    }
    display = SDL_GetVideoDisplay(displayID);
    display->natural_orientation = Android_JNI_GetDisplayNaturalOrientation();
    display->current_orientation = Android_JNI_GetDisplayCurrentOrientation();
    display->content_scale = Android_ScreenDensity;
    Android_SetScreenHDRHeadroom(Android_ScreenHDRHeadroom);

    SDL_AddHintCallback(SDL_HINT_ANDROID_TRAP_BACK_BUTTON, Android_Video_InternalHintCallback, 0);

    Android_InitTouch();

    Android_InitMouse();

    // We're done!
    بازگشت true;
}

تهی Android_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_RemoveHintCallback(SDL_HINT_ANDROID_TRAP_BACK_BUTTON, Android_Video_InternalHintCallback, 0);
    Android_QuitMouse();
    Android_QuitTouch();
}

تهی Android_SetScreenResolution(صحیح surfaceWidth, صحیح surfaceHeight, صحیح deviceWidth, صحیح deviceHeight, اعشاری density, اعشاری rate)
{
    Android_SurfaceWidth = surfaceWidth;
    Android_SurfaceHeight = surfaceHeight;
    Android_DeviceWidth = deviceWidth;
    Android_DeviceHeight = deviceHeight;
    Android_ScreenDensity = (density > 0.0f) ? density : 1.0f;
    Android_ScreenRate = rate;
}

تهی Android_SetScreenHDRHeadroom(اعشاری headroom)
{
    Android_ScreenHDRHeadroom = headroom;

    SDL_VideoDevice *device = SDL_GetVideoDevice();
    اگر (device && device->رقم_displays > 0) {
        SDL_VideoDisplay *display = device->displays[0];
        SDL_HDROutputProperties HDR;

        HDR.SDR_white_level = 1.0f;
        HDR.HDR_headroom = headroom;
        SDL_SetDisplayHDRProperties(display, &HDR);
    }
}

ایستا Uint32 format_to_pixelFormat(صحیح format)
{
    Uint32 pf;
    اگر (format == AHARDWAREBUFFER_FORMAT_R8G8B8A8_UNORM) { // 1
        pf = SDL_PIXELFORMAT_RGBA8888;
    } وگرنه اگر (format == AHARDWAREBUFFER_FORMAT_R8G8B8X8_UNORM) { // 2
        pf = SDL_PIXELFORMAT_RGBX8888;
    } وگرنه اگر (format == AHARDWAREBUFFER_FORMAT_R8G8B8_UNORM) { // 3
        pf = SDL_PIXELFORMAT_RGB24;
    } وگرنه اگر (format == AHARDWAREBUFFER_FORMAT_R5G6B5_UNORM) { // 4
        pf = SDL_PIXELFORMAT_RGB565;
    } وگرنه اگر (format == 5) {
        pf = SDL_PIXELFORMAT_BGRA8888;
    } وگرنه اگر (format == 6) {
        pf = SDL_PIXELFORMAT_RGBA5551;
    } وگرنه اگر (format == 7) {
        pf = SDL_PIXELFORMAT_RGBA4444;
    } وگرنه اگر (format == 0x115) {
        // HAL_PIXEL_FORMAT_BGR_565
        pf = SDL_PIXELFORMAT_RGB565;
    } وگرنه {
        pf = SDL_PIXELFORMAT_UNKNOWN;
    }
    بازگشت pf;
}

تهی Android_SetFormat(صحیح format_wanted, صحیح format_got)
{
    Uint32 pf_wanted;
    Uint32 pf_got;

    pf_wanted = format_to_pixelFormat(format_wanted);
    pf_got = format_to_pixelFormat(format_got);

    Android_ScreenFormat = pf_got;

    SDL_Log("pixel format wanted %s (%d), got %s (%d)",
            SDL_GetPixelFormatName(pf_wanted), format_wanted,
            SDL_GetPixelFormatName(pf_got), format_got);
}

ایستا تهی Android_SendOrientationUpdate(تهی)
{
    /* If we've received a compatible resize event, update the
     * orientation immediately, otherwise wait for the display
     * resize event.
     */
    SDL_VideoDevice *device = SDL_GetVideoDevice();
    اگر (device && device->رقم_displays > 0) {
        SDL_VideoDisplay *display = device->displays[0];
        bool mode_landscape = (display->desktop_mode.w > display->desktop_mode.h);
        bool sensor_landscape = (Android_ScreenOrientation == SDL_ORIENTATION_LANDSCAPE || Android_ScreenOrientation == SDL_ORIENTATION_LANDSCAPE_FLIPPED);
        اگر (sensor_landscape == mode_landscape) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_ORIENTATION, Android_ScreenOrientation, 0);
        }
    }
}

تهی Android_SetOrientation(SDL_DisplayOrientation orientation)
{
    Android_ScreenOrientation = orientation;
    Android_SendOrientationUpdate();
}

تهی Android_SendResize(SDL_Window *window)
{
    /*
      Update the resolution of the desktop mode, so that the window
      can be properly resized. The screen resolution change can for
      example happen when the Activity enters or exits immersive mode,
      which can happen after VideoInit().
    */
    SDL_VideoDevice *device = SDL_GetVideoDevice();
    اگر (device && device->رقم_displays > 0) {
        SDL_VideoDisplay *display = device->displays[0];
        SDL_DisplayMode desktop_mode;

        SDL_zero(desktop_mode);
        desktop_mode.format = Android_ScreenFormat;
        desktop_mode.w = Android_DeviceWidth;
        desktop_mode.h = Android_DeviceHeight;
        desktop_mode.refresh_rate = Android_ScreenRate;
        SDL_SetDesktopDisplayMode(display, &desktop_mode);
        Android_SendOrientationUpdate();
    }

    اگر (window) {
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, Android_SurfaceWidth, Android_SurfaceHeight);
    }
}

تهی Android_SetWindowSafeAreaInsets(صحیح چپ, صحیح راست, صحیح بالاترین, صحیح bottom)
{
    Android_Safe_Inset_چپ = چپ;
    Android_Safe_Inset_راست = راست;
    Android_Safe_Inset_بالاترین = بالاترین;
    Android_SafeInsetBottom = bottom;

    اگر (Android_Window) {
        SDL_SetWindowSafeAreaInsets(Android_Window, چپ, راست, بالاترین, bottom);
    }
}

تهی Android_SetDarkMode(bool enabled)
{
    SDL_VideoDevice *device = SDL_GetVideoDevice();

    اگر (enabled) {
        Android_SystemTheme = SDL_SYSTEM_THEME_DARK;
    } وگرنه {
        Android_SystemTheme = SDL_SYSTEM_THEME_LIGHT;
    }

    اگر (device) {
        SDL_SetSystemTheme(Android_SystemTheme);
    }
}

#endif // SDL_VIDEO_DRIVER_ANDROID
