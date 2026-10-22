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
#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_ANDROID

// Android SDL video driver implementation

#അന്തര്ഭാവ "../SDL_sysvideo.h"
#അന്തര്ഭാവ "../SDL_pixels_c.h"
#അന്തര്ഭാവ "../../events/SDL_events_c.h"
#അന്തര്ഭാവ "../../events/SDL_windowevents_c.h"
#അന്തര്ഭാവ "../../SDL_hints_c.h"

#അന്തര്ഭാവ "SDL_androidvideo.h"
#അന്തര്ഭാവ "SDL_androidgl.h"
#അന്തര്ഭാവ "SDL_androidclipboard.h"
#അന്തര്ഭാവ "SDL_androidevents.h"
#അന്തര്ഭാവ "SDL_androidkeyboard.h"
#അന്തര്ഭാവ "SDL_androidmouse.h"
#അന്തര്ഭാവ "SDL_androidtouch.h"
#അന്തര്ഭാവ "SDL_androidwindow.h"
#അന്തര്ഭാവ "SDL_androidvulkan.h"
#അന്തര്ഭാവ "SDL_androidmessagebox.h"

#define ANDROID_VID_DRIVER_NAME "android"

// Initialization/Query functions
സ്ഥിതം bool Android_VideoInit(SDL_VideoDevice *_this);
സ്ഥിതം ശൂന്യം Android_VideoQuit(SDL_VideoDevice *_this);

#അന്തര്ഭാവ "../SDL_egl_c.h"
#define Android_GLES_GetProcAddress  SDL_EGL_GetProcAddressInternal
#define Android_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#define Android_GLES_SetSwapInterval SDL_EGL_SetSwapInterval
#define Android_GLES_GetSwapInterval SDL_EGL_GetSwapInterval
#define Android_GLES_DestroyContext   SDL_EGL_DestroyContext

// Android driver bootstrap functions

// These are filled in with real values in Android_SetScreenResolution on init (before SDL_main())
പൂർണ്ണസംഖ്യ Android_SurfaceWidth = 0;
പൂർണ്ണസംഖ്യ Android_SurfaceHeight = 0;
സ്ഥിതം പൂർണ്ണസംഖ്യ Android_DeviceWidth = 0;
സ്ഥിതം പൂർണ്ണസംഖ്യ Android_DeviceHeight = 0;
സ്ഥിതം Uint32 Android_ScreenFormat = SDL_PIXELFORMAT_RGB565; // Default SurfaceView format, in case this is queried before being filled
ദശാംശം Android_ScreenDensity = 1.0f;
സ്ഥിതം ദശാംശം Android_ScreenRate = 0.0f;
സ്ഥിതം ദശാംശം Android_ScreenHDRHeadroom = 1.0f;
സ്ഥിതം SDL_DisplayOrientation Android_ScreenOrientation = SDL_ORIENTATION_UNKNOWN;
പൂർണ്ണസംഖ്യ Android_Safe_Inset_ഇടത് = 0;
പൂർണ്ണസംഖ്യ Android_Safe_Inset_വലത് = 0;
പൂർണ്ണസംഖ്യ Android_Safe_Inset_മുകൾ = 0;
പൂർണ്ണസംഖ്യ Android_SafeInsetBottom = 0;
സ്ഥിതം SDL_SystemTheme Android_SystemTheme;

സ്ഥിതം bool Android_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    തിരികെ Android_JNI_SuspendScreenSaver(_this->suspend_screensaver);
}

സ്ഥിതം ശൂന്യം Android_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

// Input is part of video for Android, so this goes here.
സ്ഥിതം ശൂന്യം SDLCALL Android_Video_InternalHintCallback(
    ശൂന്യം *userdata,
    സ്ഥിരം അക്ഷരം *name,
    സ്ഥിരം അക്ഷരം *oldvalue,
    സ്ഥിരം അക്ഷരം *newvalue)
{
    Android_JNI_SetBackButtonTrapActive(SDL_GetStringBoolean(newvalue, false));
}

സ്ഥിതം SDL_VideoDevice *Android_CreateDevice(ശൂന്യം)
{
    SDL_VideoDevice *device;
    SDL_VideoData *data;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, വലുപ്പം(SDL_VideoDevice));
    എങ്കിൽ (!device) {
        തിരികെ ശൂന്യ;
    }

    data = (SDL_VideoData *)SDL_calloc(1, വലുപ്പം(SDL_VideoData));
    എങ്കിൽ (!data) {
        SDL_free(device);
        തിരികെ ശൂന്യ;
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

    device->സ്വതന്ത്രം = Android_DeleteDevice;

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

    തിരികെ device;
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
    എങ്കിൽ (displayID == 0) {
        തിരികെ false;
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
    തിരികെ true;
}

ശൂന്യം Android_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_RemoveHintCallback(SDL_HINT_ANDROID_TRAP_BACK_BUTTON, Android_Video_InternalHintCallback, 0);
    Android_QuitMouse();
    Android_QuitTouch();
}

ശൂന്യം Android_SetScreenResolution(പൂർണ്ണസംഖ്യ surfaceWidth, പൂർണ്ണസംഖ്യ surfaceHeight, പൂർണ്ണസംഖ്യ deviceWidth, പൂർണ്ണസംഖ്യ deviceHeight, ദശാംശം density, ദശാംശം rate)
{
    Android_SurfaceWidth = surfaceWidth;
    Android_SurfaceHeight = surfaceHeight;
    Android_DeviceWidth = deviceWidth;
    Android_DeviceHeight = deviceHeight;
    Android_ScreenDensity = (density > 0.0f) ? density : 1.0f;
    Android_ScreenRate = rate;
}

ശൂന്യം Android_SetScreenHDRHeadroom(ദശാംശം headroom)
{
    Android_ScreenHDRHeadroom = headroom;

    SDL_VideoDevice *device = SDL_GetVideoDevice();
    എങ്കിൽ (device && device->അക്കം_displays > 0) {
        SDL_VideoDisplay *display = device->displays[0];
        SDL_HDROutputProperties HDR;

        HDR.SDR_white_level = 1.0f;
        HDR.HDR_headroom = headroom;
        SDL_SetDisplayHDRProperties(display, &HDR);
    }
}

സ്ഥിതം Uint32 format_to_pixelFormat(പൂർണ്ണസംഖ്യ format)
{
    Uint32 pf;
    എങ്കിൽ (format == AHARDWAREBUFFER_FORMAT_R8G8B8A8_UNORM) { // 1
        pf = SDL_PIXELFORMAT_RGBA8888;
    } അല്ലെങ്കിൽ എങ്കിൽ (format == AHARDWAREBUFFER_FORMAT_R8G8B8X8_UNORM) { // 2
        pf = SDL_PIXELFORMAT_RGBX8888;
    } അല്ലെങ്കിൽ എങ്കിൽ (format == AHARDWAREBUFFER_FORMAT_R8G8B8_UNORM) { // 3
        pf = SDL_PIXELFORMAT_RGB24;
    } അല്ലെങ്കിൽ എങ്കിൽ (format == AHARDWAREBUFFER_FORMAT_R5G6B5_UNORM) { // 4
        pf = SDL_PIXELFORMAT_RGB565;
    } അല്ലെങ്കിൽ എങ്കിൽ (format == 5) {
        pf = SDL_PIXELFORMAT_BGRA8888;
    } അല്ലെങ്കിൽ എങ്കിൽ (format == 6) {
        pf = SDL_PIXELFORMAT_RGBA5551;
    } അല്ലെങ്കിൽ എങ്കിൽ (format == 7) {
        pf = SDL_PIXELFORMAT_RGBA4444;
    } അല്ലെങ്കിൽ എങ്കിൽ (format == 0x115) {
        // HAL_PIXEL_FORMAT_BGR_565
        pf = SDL_PIXELFORMAT_RGB565;
    } അല്ലെങ്കിൽ {
        pf = SDL_PIXELFORMAT_UNKNOWN;
    }
    തിരികെ pf;
}

ശൂന്യം Android_SetFormat(പൂർണ്ണസംഖ്യ format_wanted, പൂർണ്ണസംഖ്യ format_got)
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

സ്ഥിതം ശൂന്യം Android_SendOrientationUpdate(ശൂന്യം)
{
    /* If we've received a compatible resize event, update the
     * orientation immediately, otherwise wait for the display
     * resize event.
     */
    SDL_VideoDevice *device = SDL_GetVideoDevice();
    എങ്കിൽ (device && device->അക്കം_displays > 0) {
        SDL_VideoDisplay *display = device->displays[0];
        bool mode_landscape = (display->desktop_mode.w > display->desktop_mode.h);
        bool sensor_landscape = (Android_ScreenOrientation == SDL_ORIENTATION_LANDSCAPE || Android_ScreenOrientation == SDL_ORIENTATION_LANDSCAPE_FLIPPED);
        എങ്കിൽ (sensor_landscape == mode_landscape) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_ORIENTATION, Android_ScreenOrientation, 0);
        }
    }
}

ശൂന്യം Android_SetOrientation(SDL_DisplayOrientation orientation)
{
    Android_ScreenOrientation = orientation;
    Android_SendOrientationUpdate();
}

ശൂന്യം Android_SendResize(SDL_Window *window)
{
    /*
      Update the resolution of the desktop mode, so that the window
      can be properly resized. The screen resolution change can for
      example happen when the Activity enters or exits immersive mode,
      which can happen after VideoInit().
    */
    SDL_VideoDevice *device = SDL_GetVideoDevice();
    എങ്കിൽ (device && device->അക്കം_displays > 0) {
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

    എങ്കിൽ (window) {
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, Android_SurfaceWidth, Android_SurfaceHeight);
    }
}

ശൂന്യം Android_SetWindowSafeAreaInsets(പൂർണ്ണസംഖ്യ ഇടത്, പൂർണ്ണസംഖ്യ വലത്, പൂർണ്ണസംഖ്യ മുകൾ, പൂർണ്ണസംഖ്യ bottom)
{
    Android_Safe_Inset_ഇടത് = ഇടത്;
    Android_Safe_Inset_വലത് = വലത്;
    Android_Safe_Inset_മുകൾ = മുകൾ;
    Android_SafeInsetBottom = bottom;

    എങ്കിൽ (Android_Window) {
        SDL_SetWindowSafeAreaInsets(Android_Window, ഇടത്, വലത്, മുകൾ, bottom);
    }
}

ശൂന്യം Android_SetDarkMode(bool enabled)
{
    SDL_VideoDevice *device = SDL_GetVideoDevice();

    എങ്കിൽ (enabled) {
        Android_SystemTheme = SDL_SYSTEM_THEME_DARK;
    } അല്ലെങ്കിൽ {
        Android_SystemTheme = SDL_SYSTEM_THEME_LIGHT;
    }

    എങ്കിൽ (device) {
        SDL_SetSystemTheme(Android_SystemTheme);
    }
}

#endif // SDL_VIDEO_DRIVER_ANDROID
