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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_ANDROID

// Android SDL video driver implementation

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../SDL_pixels_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_windowevents_c.h"
#ಅನ್ತರ್ಭಾವ "../../SDL_hints_c.h"

#ಅನ್ತರ್ಭಾವ "SDL_androidvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_androidgl.h"
#ಅನ್ತರ್ಭಾವ "SDL_androidclipboard.h"
#ಅನ್ತರ್ಭಾವ "SDL_androidevents.h"
#ಅನ್ತರ್ಭಾವ "SDL_androidkeyboard.h"
#ಅನ್ತರ್ಭಾವ "SDL_androidmouse.h"
#ಅನ್ತರ್ಭಾವ "SDL_androidtouch.h"
#ಅನ್ತರ್ಭಾವ "SDL_androidwindow.h"
#ಅನ್ತರ್ಭಾವ "SDL_androidvulkan.h"
#ಅನ್ತರ್ಭಾವ "SDL_androidmessagebox.h"

#ವ್ಯಾಖ್ಯಾನಿಸು ANDROID_VID_DRIVER_NAME "android"

// Initialization/Query functions
ಸ್ಥಿರ bool Android_VideoInit(SDL_VideoDevice *_this);
ಸ್ಥಿರ ಶೂನ್ಯ Android_VideoQuit(SDL_VideoDevice *_this);

#ಅನ್ತರ್ಭಾವ "../SDL_egl_c.h"
#ವ್ಯಾಖ್ಯಾನಿಸು Android_GLES_Get_Proc_ವಿಳಾಸ  SDL_EGL_Get_Proc_ವಿಳಾಸ_ಆಂತರಿಕ
#ವ್ಯಾಖ್ಯಾನಿಸು Android_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#ವ್ಯಾಖ್ಯಾನಿಸು Android_GLES_ಗಣ_ಅದಲುಬದಲು_Interval SDL_EGL_ಗಣ_ಅದಲುಬದಲು_Interval
#ವ್ಯಾಖ್ಯಾನಿಸು Android_GLES_Get_ಅದಲುಬದಲು_Interval SDL_EGL_Get_ಅದಲುಬದಲು_Interval
#ವ್ಯಾಖ್ಯಾನಿಸು Android_GLES_DestroyContext   SDL_EGL_DestroyContext

// Android driver bootstrap functions

// These are filled in with real values in Android_SetScreenResolution on init (before SDL_main())
ಪೂರ್ಣಾಂಕ Android_Surface_ಅಗಲ = 0;
ಪೂರ್ಣಾಂಕ Android_Surface_ಎತ್ತರ = 0;
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ Android_Device_ಅಗಲ = 0;
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ Android_Device_ಎತ್ತರ = 0;
ಸ್ಥಿರ Uint32 Android_ScreenFormat = SDL_PIXELFORMAT_RGB565; // Default SurfaceView format, in case this is queried before being filled
ದಶಮಾಂಶ Android_ScreenDensity = 1.0f;
ಸ್ಥಿರ ದಶಮಾಂಶ Android_Screen_ದರ = 0.0f;
ಸ್ಥಿರ ದಶಮಾಂಶ Android_ScreenHDRHeadroom = 1.0f;
ಸ್ಥಿರ SDL_DisplayOrientation Android_ScreenOrientation = SDL_ORIENTATION_UNKNOWN;
ಪೂರ್ಣಾಂಕ Android_ಸುರಕ್ಷಿತ_Inset_ಎಡ = 0;
ಪೂರ್ಣಾಂಕ Android_ಸುರಕ್ಷಿತ_Inset_ಬಲ = 0;
ಪೂರ್ಣಾಂಕ Android_ಸುರಕ್ಷಿತ_Inset_ತುದಿ = 0;
ಪೂರ್ಣಾಂಕ Android_ಸುರಕ್ಷಿತ_Inset_Bottom = 0;
ಸ್ಥಿರ SDL_SystemTheme Android_SystemTheme;

ಸ್ಥಿರ bool Android_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    ಹಿಂತಿರುಗಿ Android_JNI_SuspendScreenSaver(_this->suspend_screensaver);
}

ಸ್ಥಿರ ಶೂನ್ಯ Android_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->ಆಂತರಿಕ);
    SDL_free(device);
}

// Input is part of video for Android, so this goes here.
ಸ್ಥಿರ ಶೂನ್ಯ SDLCALL Android_Video_ಆಂತರಿಕ_Hint_Callback(
    ಶೂನ್ಯ *userdata,
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name,
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *oldvalue,
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *newvalue)
{
    Android_JNI_ಗಣ_ಹಿಂಭಾಗ_Button_Trap_ಸಕ್ರಿಯ(SDL_GetStringBoolean(newvalue, false));
}

ಸ್ಥಿರ SDL_VideoDevice *Android_CreateDevice(ಶೂನ್ಯ)
{
    SDL_VideoDevice *device;
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, ಗಾತ್ರ(SDL_VideoDevice));
    ಆದರೆ (!device) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ದತ್ತಾಂಶ = (SDL_Video_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_Video_ದತ್ತಾಂಶ));
    ಆದರೆ (!ದತ್ತಾಂಶ) {
        SDL_free(device);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    device->ಆಂತರಿಕ = ದತ್ತಾಂಶ;
    device->system_theme = Android_SystemTheme;

    // Set the function pointers
    device->VideoInit = Android_VideoInit;
    device->VideoQuit = Android_VideoQuit;

    device->CreateSDLWindow = Android_Create_ಕಿಟಕಿ;
    device->ಗಣ_ಕಿಟಕಿ_Title = Android_ಗಣ_ಕಿಟಕಿ_Title;
    device->ಗಣ_ಕಿಟಕಿ_Fullscreen = Android_ಗಣ_ಕಿಟಕಿ_Fullscreen;
    device->Minimize_ಕಿಟಕಿ = Android_Minimize_ಕಿಟಕಿ;
    device->ಗಣ_ಕಿಟಕಿ_Resizable = Android_ಗಣ_ಕಿಟಕಿ_Resizable;
    device->Destroy_ಕಿಟಕಿ = Android_Destroy_ಕಿಟಕಿ;

    device->ಬಿಡುಗಡೆ = Android_DeleteDevice;

    // GL pointers
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
    device->GL_ತುಂಬು_Library = Android_GLES_ತುಂಬು_Library;
    device->GL_Get_Proc_ವಿಳಾಸ = Android_GLES_Get_Proc_ವಿಳಾಸ;
    device->GL_UnloadLibrary = Android_GLES_UnloadLibrary;
    device->GL_CreateContext = Android_GLES_CreateContext;
    device->GL_MakeCurrent = Android_GLES_MakeCurrent;
    device->GL_ಗಣ_ಅದಲುಬದಲು_Interval = Android_GLES_ಗಣ_ಅದಲುಬದಲು_Interval;
    device->GL_Get_ಅದಲುಬದಲು_Interval = Android_GLES_Get_ಅದಲುಬದಲು_Interval;
    device->GL_ಅದಲುಬದಲು_ಕಿಟಕಿ = Android_GLES_ಅದಲುಬದಲು_ಕಿಟಕಿ;
    device->GL_DestroyContext = Android_GLES_DestroyContext;
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_VULKAN
    device->Vulkan_ತುಂಬು_Library = Android_Vulkan_ತುಂಬು_Library;
    device->Vulkan_UnloadLibrary = Android_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = Android_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = Android_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = Android_Vulkan_DestroySurface;
#ಆದರೆ_ಅಂತ್ಯ

    // Screensaver
    device->SuspendScreenSaver = Android_SuspendScreenSaver;

    // Screen keyboard
    device->HasScreenKeyboardSupport = Android_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = Android_ShowScreenKeyboard;
    device->HideScreenKeyboard = Android_HideScreenKeyboard;

    // Clipboard
    device->ಗಣ_Clipboard_ಪಠ್ಯ = Android_ಗಣ_Clipboard_ಪಠ್ಯ;
    device->Get_Clipboard_ಪಠ್ಯ = Android_Get_Clipboard_ಪಠ್ಯ;
    device->Has_Clipboard_ಪಠ್ಯ = Android_Has_Clipboard_ಪಠ್ಯ;

    device->device_caps = VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS;

    ಹಿಂತಿರುಗಿ device;
}

VideoBootStrap Android_bootstrap = {
    ANDROID_VID_DRIVER_NAME, "SDL Android video driver",
    Android_CreateDevice,
    Android_Show_ಸಂದೇಶ_Box,
    false
};

bool Android_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;
    SDL_DisplayID displayID;
    SDL_VideoDisplay *display;
    SDL_Display_ಬಹುಲಕ ಬಹುಲಕ;

    videodata->isPaused = false;
    videodata->isPausing = false;

    SDL_zero(ಬಹುಲಕ);
    ಬಹುಲಕ.format = Android_ScreenFormat;
    ಬಹುಲಕ.w = Android_Device_ಅಗಲ;
    ಬಹುಲಕ.h = Android_Device_ಎತ್ತರ;
    ಬಹುಲಕ.refresh_ದರ = Android_Screen_ದರ;

    displayID = SDL_ಕೂಡಿಸು_Basic_Video_Display(&ಬಹುಲಕ);
    ಆದರೆ (displayID == 0) {
        ಹಿಂತಿರುಗಿ false;
    }
    display = SDL_GetVideoDisplay(displayID);
    display->natural_orientation = Android_JNI_GetDisplayNaturalOrientation();
    display->current_orientation = Android_JNI_GetDisplayCurrentOrientation();
    display->content_scale = Android_ScreenDensity;
    Android_ಗಣ_Screen_HDRHeadroom(Android_ScreenHDRHeadroom);

    SDL_ಕೂಡಿಸು_Hint_Callback(SDL_HINT_ANDROID_TRAP_ಹಿಂಭಾಗ_BUTTON, Android_Video_ಆಂತರಿಕ_Hint_Callback, 0);

    Android_InitTouch();

    Android_InitMouse();

    // We're done!
    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ Android_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_RemoveHintCallback(SDL_HINT_ANDROID_TRAP_ಹಿಂಭಾಗ_BUTTON, Android_Video_ಆಂತರಿಕ_Hint_Callback, 0);
    Android_QuitMouse();
    Android_QuitTouch();
}

ಶೂನ್ಯ Android_ಗಣ_Screen_Resolution(ಪೂರ್ಣಾಂಕ surface_ಅಗಲ, ಪೂರ್ಣಾಂಕ surface_ಎತ್ತರ, ಪೂರ್ಣಾಂಕ device_ಅಗಲ, ಪೂರ್ಣಾಂಕ device_ಎತ್ತರ, ದಶಮಾಂಶ density, ದಶಮಾಂಶ ದರ)
{
    Android_Surface_ಅಗಲ = surface_ಅಗಲ;
    Android_Surface_ಎತ್ತರ = surface_ಎತ್ತರ;
    Android_Device_ಅಗಲ = device_ಅಗಲ;
    Android_Device_ಎತ್ತರ = device_ಎತ್ತರ;
    Android_ScreenDensity = (density > 0.0f) ? density : 1.0f;
    Android_Screen_ದರ = ದರ;
}

ಶೂನ್ಯ Android_ಗಣ_Screen_HDRHeadroom(ದಶಮಾಂಶ headroom)
{
    Android_ScreenHDRHeadroom = headroom;

    SDL_VideoDevice *device = SDL_GetVideoDevice();
    ಆದರೆ (device && device->ಅಂಕೆ_displays > 0) {
        SDL_VideoDisplay *display = device->displays[0];
        SDL_HDROutputProperties HDR;

        HDR.SDR_white_level = 1.0f;
        HDR.HDR_headroom = headroom;
        SDL_ಗಣ_Display_HDRProperties(display, &HDR);
    }
}

ಸ್ಥಿರ Uint32 format_ಗಮ್ಯ_pixel_Format(ಪೂರ್ಣಾಂಕ format)
{
    Uint32 pf;
    ಆದರೆ (format == AHARDWAREBUFFER_FORMAT_R8G8B8A8_UNORM) { // 1
        pf = SDL_PIXELFORMAT_RGBA8888;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (format == AHARDWAREBUFFER_FORMAT_R8G8B8X8_UNORM) { // 2
        pf = SDL_PIXELFORMAT_RGBX8888;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (format == AHARDWAREBUFFER_FORMAT_R8G8B8_UNORM) { // 3
        pf = SDL_PIXELFORMAT_RGB24;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (format == AHARDWAREBUFFER_FORMAT_R5G6B5_UNORM) { // 4
        pf = SDL_PIXELFORMAT_RGB565;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (format == 5) {
        pf = SDL_PIXELFORMAT_BGRA8888;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (format == 6) {
        pf = SDL_PIXELFORMAT_RGBA5551;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (format == 7) {
        pf = SDL_PIXELFORMAT_RGBA4444;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (format == 0x115) {
        // HAL_PIXEL_FORMAT_BGR_565
        pf = SDL_PIXELFORMAT_RGB565;
    } ಇಲ್ಲದಿದ್ದರೆ {
        pf = SDL_PIXELFORMAT_UNKNOWN;
    }
    ಹಿಂತಿರುಗಿ pf;
}

ಶೂನ್ಯ Android_ಗಣ_Format(ಪೂರ್ಣಾಂಕ format_wanted, ಪೂರ್ಣಾಂಕ format_got)
{
    Uint32 pf_wanted;
    Uint32 pf_got;

    pf_wanted = format_ಗಮ್ಯ_pixel_Format(format_wanted);
    pf_got = format_ಗಮ್ಯ_pixel_Format(format_got);

    Android_ScreenFormat = pf_got;

    SDL_Log("pixel format wanted %s (%d), got %s (%d)",
            SDL_GetPixelFormatName(pf_wanted), format_wanted,
            SDL_GetPixelFormatName(pf_got), format_got);
}

ಸ್ಥಿರ ಶೂನ್ಯ Android_SendOrientationUpdate(ಶೂನ್ಯ)
{
    /* If we've received a compatible resize event, update the
     * orientation immediately, otherwise wait for the display
     * resize event.
     */
    SDL_VideoDevice *device = SDL_GetVideoDevice();
    ಆದರೆ (device && device->ಅಂಕೆ_displays > 0) {
        SDL_VideoDisplay *display = device->displays[0];
        bool ಬಹುಲಕ_landscape = (display->desktop_ಬಹುಲಕ.w > display->desktop_ಬಹುಲಕ.h);
        bool sensor_landscape = (Android_ScreenOrientation == SDL_ORIENTATION_LANDSCAPE || Android_ScreenOrientation == SDL_ORIENTATION_LANDSCAPE_FLIPPED);
        ಆದರೆ (sensor_landscape == ಬಹುಲಕ_landscape) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_ORIENTATION, Android_ScreenOrientation, 0);
        }
    }
}

ಶೂನ್ಯ Android_ಗಣ_Orientation(SDL_DisplayOrientation orientation)
{
    Android_ScreenOrientation = orientation;
    Android_SendOrientationUpdate();
}

ಶೂನ್ಯ Android_SendResize(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    /*
      Update the resolution of the desktop mode, so that the window
      can be properly resized. The screen resolution change can for
      example happen when the Activity enters or exits immersive mode,
      which can happen after VideoInit().
    */
    SDL_VideoDevice *device = SDL_GetVideoDevice();
    ಆದರೆ (device && device->ಅಂಕೆ_displays > 0) {
        SDL_VideoDisplay *display = device->displays[0];
        SDL_Display_ಬಹುಲಕ desktop_ಬಹುಲಕ;

        SDL_zero(desktop_ಬಹುಲಕ);
        desktop_ಬಹುಲಕ.format = Android_ScreenFormat;
        desktop_ಬಹುಲಕ.w = Android_Device_ಅಗಲ;
        desktop_ಬಹುಲಕ.h = Android_Device_ಎತ್ತರ;
        desktop_ಬಹುಲಕ.refresh_ದರ = Android_Screen_ದರ;
        SDL_ಗಣ_Desktop_Display_ಬಹುಲಕ(display, &desktop_ಬಹುಲಕ);
        Android_SendOrientationUpdate();
    }

    ಆದರೆ (ಕಿಟಕಿ) {
        SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_RESIZED, Android_Surface_ಅಗಲ, Android_Surface_ಎತ್ತರ);
    }
}

ಶೂನ್ಯ Android_ಗಣ_ಕಿಟಕಿ_ಸುರಕ್ಷಿತ_Area_Insets(ಪೂರ್ಣಾಂಕ ಎಡ, ಪೂರ್ಣಾಂಕ ಬಲ, ಪೂರ್ಣಾಂಕ ತುದಿ, ಪೂರ್ಣಾಂಕ bottom)
{
    Android_ಸುರಕ್ಷಿತ_Inset_ಎಡ = ಎಡ;
    Android_ಸುರಕ್ಷಿತ_Inset_ಬಲ = ಬಲ;
    Android_ಸುರಕ್ಷಿತ_Inset_ತುದಿ = ತುದಿ;
    Android_ಸುರಕ್ಷಿತ_Inset_Bottom = bottom;

    ಆದರೆ (Android_ಕಿಟಕಿ) {
        SDL_ಗಣ_ಕಿಟಕಿ_ಸುರಕ್ಷಿತ_Area_Insets(Android_ಕಿಟಕಿ, ಎಡ, ಬಲ, ತುದಿ, bottom);
    }
}

ಶೂನ್ಯ Android_ಗಣ_Dark_ಬಹುಲಕ(bool enabled)
{
    SDL_VideoDevice *device = SDL_GetVideoDevice();

    ಆದರೆ (enabled) {
        Android_SystemTheme = SDL_SYSTEM_THEME_DARK;
    } ಇಲ್ಲದಿದ್ದರೆ {
        Android_SystemTheme = SDL_SYSTEM_THEME_LIGHT;
    }

    ಆದರೆ (device) {
        SDL_ಗಣ_System_Theme(Android_SystemTheme);
    }
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_ANDROID
