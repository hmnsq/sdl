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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_ANDROID

// Android SDL video driver implementation

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_pixels_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_events_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_windowevents_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../SDL_hints_c.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_androidvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_androidgl.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_androidclipboard.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_androidevents.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_androidkeyboard.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_androidmouse.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_androidtouch.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_androidwindow.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_androidvulkan.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_androidmessagebox.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ANDROID_VID_DRIVER_NAME "android"

// Initialization/Query functions
ਸਥਿਰ bool Android_VideoInit(SDL_VideoDevice *_this);
ਸਥਿਰ ਖਾਲੀ Android_VideoQuit(SDL_VideoDevice *_this);

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_egl_c.h"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Android_GLES_Get_Proc_ਪਤਾ  SDL_EGL_Get_Proc_ਪਤਾ_ਅੰਦਰੂਨੀ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Android_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Android_GLES_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval SDL_EGL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Android_GLES_Get_ਅਦਲਾ_ਬਦਲੀ_Interval SDL_EGL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Android_GLES_DestroyContext   SDL_EGL_DestroyContext

// Android driver bootstrap functions

// These are filled in with real values in Android_SetScreenResolution on init (before SDL_main())
ਪੂਰਨ Android_Surface_ਚੌੜਾਈ = 0;
ਪੂਰਨ Android_Surface_ਉਚਾਈ = 0;
ਸਥਿਰ ਪੂਰਨ Android_Device_ਚੌੜਾਈ = 0;
ਸਥਿਰ ਪੂਰਨ Android_Device_ਉਚਾਈ = 0;
ਸਥਿਰ Uint32 Android_ScreenFormat = SDL_PIXELFORMAT_RGB565; // Default SurfaceView format, in case this is queried before being filled
ਦਸ਼ਮਲਵ Android_ScreenDensity = 1.0f;
ਸਥਿਰ ਦਸ਼ਮਲਵ Android_Screen_ਦਰ = 0.0f;
ਸਥਿਰ ਦਸ਼ਮਲਵ Android_ScreenHDRHeadroom = 1.0f;
ਸਥਿਰ SDL_DisplayOrientation Android_ScreenOrientation = SDL_ORIENTATION_UNKNOWN;
ਪੂਰਨ Android_ਸੁਰੱਖਿਅਤ_Inset_ਖੱਬਾ = 0;
ਪੂਰਨ Android_ਸੁਰੱਖਿਅਤ_Inset_ਸੱਜਾ = 0;
ਪੂਰਨ Android_ਸੁਰੱਖਿਅਤ_Inset_ਸਿਖਰ = 0;
ਪੂਰਨ Android_ਸੁਰੱਖਿਅਤ_Inset_Bottom = 0;
ਸਥਿਰ SDL_SystemTheme Android_SystemTheme;

ਸਥਿਰ bool Android_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    ਵਾਪਸ Android_JNI_SuspendScreenSaver(_this->suspend_screensaver);
}

ਸਥਿਰ ਖਾਲੀ Android_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->ਅੰਦਰੂਨੀ);
    SDL_free(device);
}

// Input is part of video for Android, so this goes here.
ਸਥਿਰ ਖਾਲੀ SDLCALL Android_Video_ਅੰਦਰੂਨੀ_Hint_Callback(
    ਖਾਲੀ *userdata,
    ਅਚਲ ਅੱਖਰ *name,
    ਅਚਲ ਅੱਖਰ *oldvalue,
    ਅਚਲ ਅੱਖਰ *newvalue)
{
    Android_JNI_ਸੈੱਟ_ਪਿੱਠ_Button_Trap_ਸਰਗਰਮ(SDL_GetStringBoolean(newvalue, false));
}

ਸਥਿਰ SDL_VideoDevice *Android_CreateDevice(ਖਾਲੀ)
{
    SDL_VideoDevice *device;
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, ਆਕਾਰ(SDL_VideoDevice));
    ਜੇ (!device) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਅੰਕੜੇ = (SDL_Video_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(SDL_Video_ਅੰਕੜੇ));
    ਜੇ (!ਅੰਕੜੇ) {
        SDL_free(device);
        ਵਾਪਸ ਨਿਰਾ;
    }

    device->ਅੰਦਰੂਨੀ = ਅੰਕੜੇ;
    device->system_theme = Android_SystemTheme;

    // Set the function pointers
    device->VideoInit = Android_VideoInit;
    device->VideoQuit = Android_VideoQuit;

    device->CreateSDLWindow = Android_Create_ਖਿੜਕੀ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Title = Android_ਸੈੱਟ_ਖਿੜਕੀ_Title;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen = Android_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen;
    device->Minimize_ਖਿੜਕੀ = Android_Minimize_ਖਿੜਕੀ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Resizable = Android_ਸੈੱਟ_ਖਿੜਕੀ_Resizable;
    device->Destroy_ਖਿੜਕੀ = Android_Destroy_ਖਿੜਕੀ;

    device->ਮੁਕਤ = Android_DeleteDevice;

    // GL pointers
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
    device->GL_ਲੱਦੋ_Library = Android_GLES_ਲੱਦੋ_Library;
    device->GL_Get_Proc_ਪਤਾ = Android_GLES_Get_Proc_ਪਤਾ;
    device->GL_UnloadLibrary = Android_GLES_UnloadLibrary;
    device->GL_CreateContext = Android_GLES_CreateContext;
    device->GL_MakeCurrent = Android_GLES_MakeCurrent;
    device->GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval = Android_GLES_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval;
    device->GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval = Android_GLES_Get_ਅਦਲਾ_ਬਦਲੀ_Interval;
    device->GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ = Android_GLES_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ;
    device->GL_DestroyContext = Android_GLES_DestroyContext;
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_VULKAN
    device->Vulkan_ਲੱਦੋ_Library = Android_Vulkan_ਲੱਦੋ_Library;
    device->Vulkan_UnloadLibrary = Android_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = Android_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = Android_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = Android_Vulkan_DestroySurface;
#ਜੇ_ਅੰਤ

    // Screensaver
    device->SuspendScreenSaver = Android_SuspendScreenSaver;

    // Screen keyboard
    device->HasScreenKeyboardSupport = Android_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = Android_ShowScreenKeyboard;
    device->HideScreenKeyboard = Android_HideScreenKeyboard;

    // Clipboard
    device->ਸੈੱਟ_Clipboard_ਪਾਠ = Android_ਸੈੱਟ_Clipboard_ਪਾਠ;
    device->Get_Clipboard_ਪਾਠ = Android_Get_Clipboard_ਪਾਠ;
    device->Has_Clipboard_ਪਾਠ = Android_Has_Clipboard_ਪਾਠ;

    device->device_caps = VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS;

    ਵਾਪਸ device;
}

VideoBootStrap Android_bootstrap = {
    ANDROID_VID_DRIVER_NAME, "SDL Android video driver",
    Android_CreateDevice,
    Android_Show_ਸੁਨੇਹਾ_Box,
    false
};

bool Android_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;
    SDL_DisplayID displayID;
    SDL_VideoDisplay *display;
    SDL_Display_ਬਹੁਲਕ ਬਹੁਲਕ;

    videodata->isPaused = false;
    videodata->isPausing = false;

    SDL_zero(ਬਹੁਲਕ);
    ਬਹੁਲਕ.format = Android_ScreenFormat;
    ਬਹੁਲਕ.w = Android_Device_ਚੌੜਾਈ;
    ਬਹੁਲਕ.h = Android_Device_ਉਚਾਈ;
    ਬਹੁਲਕ.refresh_ਦਰ = Android_Screen_ਦਰ;

    displayID = SDL_ਜੋੜੋ_Basic_Video_Display(&ਬਹੁਲਕ);
    ਜੇ (displayID == 0) {
        ਵਾਪਸ false;
    }
    display = SDL_GetVideoDisplay(displayID);
    display->natural_orientation = Android_JNI_GetDisplayNaturalOrientation();
    display->current_orientation = Android_JNI_GetDisplayCurrentOrientation();
    display->content_scale = Android_ScreenDensity;
    Android_ਸੈੱਟ_Screen_HDRHeadroom(Android_ScreenHDRHeadroom);

    SDL_ਜੋੜੋ_Hint_Callback(SDL_HINT_ANDROID_TRAP_ਪਿੱਠ_BUTTON, Android_Video_ਅੰਦਰੂਨੀ_Hint_Callback, 0);

    Android_InitTouch();

    Android_InitMouse();

    // We're done!
    ਵਾਪਸ true;
}

ਖਾਲੀ Android_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_RemoveHintCallback(SDL_HINT_ANDROID_TRAP_ਪਿੱਠ_BUTTON, Android_Video_ਅੰਦਰੂਨੀ_Hint_Callback, 0);
    Android_QuitMouse();
    Android_QuitTouch();
}

ਖਾਲੀ Android_ਸੈੱਟ_Screen_Resolution(ਪੂਰਨ surface_ਚੌੜਾਈ, ਪੂਰਨ surface_ਉਚਾਈ, ਪੂਰਨ device_ਚੌੜਾਈ, ਪੂਰਨ device_ਉਚਾਈ, ਦਸ਼ਮਲਵ density, ਦਸ਼ਮਲਵ ਦਰ)
{
    Android_Surface_ਚੌੜਾਈ = surface_ਚੌੜਾਈ;
    Android_Surface_ਉਚਾਈ = surface_ਉਚਾਈ;
    Android_Device_ਚੌੜਾਈ = device_ਚੌੜਾਈ;
    Android_Device_ਉਚਾਈ = device_ਉਚਾਈ;
    Android_ScreenDensity = (density > 0.0f) ? density : 1.0f;
    Android_Screen_ਦਰ = ਦਰ;
}

ਖਾਲੀ Android_ਸੈੱਟ_Screen_HDRHeadroom(ਦਸ਼ਮਲਵ headroom)
{
    Android_ScreenHDRHeadroom = headroom;

    SDL_VideoDevice *device = SDL_GetVideoDevice();
    ਜੇ (device && device->ਅੰਕ_displays > 0) {
        SDL_VideoDisplay *display = device->displays[0];
        SDL_HDROutputProperties HDR;

        HDR.SDR_white_level = 1.0f;
        HDR.HDR_headroom = headroom;
        SDL_ਸੈੱਟ_Display_HDRProperties(display, &HDR);
    }
}

ਸਥਿਰ Uint32 format_ਮੰਜ਼ਿਲ_pixel_Format(ਪੂਰਨ format)
{
    Uint32 pf;
    ਜੇ (format == AHARDWAREBUFFER_FORMAT_R8G8B8A8_UNORM) { // 1
        pf = SDL_PIXELFORMAT_RGBA8888;
    } ਨਹੀਂਤਾਂ ਜੇ (format == AHARDWAREBUFFER_FORMAT_R8G8B8X8_UNORM) { // 2
        pf = SDL_PIXELFORMAT_RGBX8888;
    } ਨਹੀਂਤਾਂ ਜੇ (format == AHARDWAREBUFFER_FORMAT_R8G8B8_UNORM) { // 3
        pf = SDL_PIXELFORMAT_RGB24;
    } ਨਹੀਂਤਾਂ ਜੇ (format == AHARDWAREBUFFER_FORMAT_R5G6B5_UNORM) { // 4
        pf = SDL_PIXELFORMAT_RGB565;
    } ਨਹੀਂਤਾਂ ਜੇ (format == 5) {
        pf = SDL_PIXELFORMAT_BGRA8888;
    } ਨਹੀਂਤਾਂ ਜੇ (format == 6) {
        pf = SDL_PIXELFORMAT_RGBA5551;
    } ਨਹੀਂਤਾਂ ਜੇ (format == 7) {
        pf = SDL_PIXELFORMAT_RGBA4444;
    } ਨਹੀਂਤਾਂ ਜੇ (format == 0x115) {
        // HAL_PIXEL_FORMAT_BGR_565
        pf = SDL_PIXELFORMAT_RGB565;
    } ਨਹੀਂਤਾਂ {
        pf = SDL_PIXELFORMAT_UNKNOWN;
    }
    ਵਾਪਸ pf;
}

ਖਾਲੀ Android_ਸੈੱਟ_Format(ਪੂਰਨ format_wanted, ਪੂਰਨ format_got)
{
    Uint32 pf_wanted;
    Uint32 pf_got;

    pf_wanted = format_ਮੰਜ਼ਿਲ_pixel_Format(format_wanted);
    pf_got = format_ਮੰਜ਼ਿਲ_pixel_Format(format_got);

    Android_ScreenFormat = pf_got;

    SDL_Log("pixel format wanted %s (%d), got %s (%d)",
            SDL_GetPixelFormatName(pf_wanted), format_wanted,
            SDL_GetPixelFormatName(pf_got), format_got);
}

ਸਥਿਰ ਖਾਲੀ Android_SendOrientationUpdate(ਖਾਲੀ)
{
    /* If we've received a compatible resize event, update the
     * orientation immediately, otherwise wait for the display
     * resize event.
     */
    SDL_VideoDevice *device = SDL_GetVideoDevice();
    ਜੇ (device && device->ਅੰਕ_displays > 0) {
        SDL_VideoDisplay *display = device->displays[0];
        bool ਬਹੁਲਕ_landscape = (display->desktop_ਬਹੁਲਕ.w > display->desktop_ਬਹੁਲਕ.h);
        bool sensor_landscape = (Android_ScreenOrientation == SDL_ORIENTATION_LANDSCAPE || Android_ScreenOrientation == SDL_ORIENTATION_LANDSCAPE_FLIPPED);
        ਜੇ (sensor_landscape == ਬਹੁਲਕ_landscape) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_ORIENTATION, Android_ScreenOrientation, 0);
        }
    }
}

ਖਾਲੀ Android_ਸੈੱਟ_Orientation(SDL_DisplayOrientation orientation)
{
    Android_ScreenOrientation = orientation;
    Android_SendOrientationUpdate();
}

ਖਾਲੀ Android_SendResize(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    /*
      Update the resolution of the desktop mode, so that the window
      can be properly resized. The screen resolution change can for
      example happen when the Activity enters or exits immersive mode,
      which can happen after VideoInit().
    */
    SDL_VideoDevice *device = SDL_GetVideoDevice();
    ਜੇ (device && device->ਅੰਕ_displays > 0) {
        SDL_VideoDisplay *display = device->displays[0];
        SDL_Display_ਬਹੁਲਕ desktop_ਬਹੁਲਕ;

        SDL_zero(desktop_ਬਹੁਲਕ);
        desktop_ਬਹੁਲਕ.format = Android_ScreenFormat;
        desktop_ਬਹੁਲਕ.w = Android_Device_ਚੌੜਾਈ;
        desktop_ਬਹੁਲਕ.h = Android_Device_ਉਚਾਈ;
        desktop_ਬਹੁਲਕ.refresh_ਦਰ = Android_Screen_ਦਰ;
        SDL_ਸੈੱਟ_Desktop_Display_ਬਹੁਲਕ(display, &desktop_ਬਹੁਲਕ);
        Android_SendOrientationUpdate();
    }

    ਜੇ (ਖਿੜਕੀ) {
        SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_RESIZED, Android_Surface_ਚੌੜਾਈ, Android_Surface_ਉਚਾਈ);
    }
}

ਖਾਲੀ Android_ਸੈੱਟ_ਖਿੜਕੀ_ਸੁਰੱਖਿਅਤ_Area_Insets(ਪੂਰਨ ਖੱਬਾ, ਪੂਰਨ ਸੱਜਾ, ਪੂਰਨ ਸਿਖਰ, ਪੂਰਨ bottom)
{
    Android_ਸੁਰੱਖਿਅਤ_Inset_ਖੱਬਾ = ਖੱਬਾ;
    Android_ਸੁਰੱਖਿਅਤ_Inset_ਸੱਜਾ = ਸੱਜਾ;
    Android_ਸੁਰੱਖਿਅਤ_Inset_ਸਿਖਰ = ਸਿਖਰ;
    Android_ਸੁਰੱਖਿਅਤ_Inset_Bottom = bottom;

    ਜੇ (Android_ਖਿੜਕੀ) {
        SDL_ਸੈੱਟ_ਖਿੜਕੀ_ਸੁਰੱਖਿਅਤ_Area_Insets(Android_ਖਿੜਕੀ, ਖੱਬਾ, ਸੱਜਾ, ਸਿਖਰ, bottom);
    }
}

ਖਾਲੀ Android_ਸੈੱਟ_Dark_ਬਹੁਲਕ(bool enabled)
{
    SDL_VideoDevice *device = SDL_GetVideoDevice();

    ਜੇ (enabled) {
        Android_SystemTheme = SDL_SYSTEM_THEME_DARK;
    } ਨਹੀਂਤਾਂ {
        Android_SystemTheme = SDL_SYSTEM_THEME_LIGHT;
    }

    ਜੇ (device) {
        SDL_ਸੈੱਟ_System_Theme(Android_SystemTheme);
    }
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_ANDROID
