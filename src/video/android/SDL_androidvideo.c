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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_ANDROID

// Android SDL video driver implementation

#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "../SDL_pixels_c.h"
#అన్తర్భావ "../../events/SDL_events_c.h"
#అన్తర్భావ "../../events/SDL_windowevents_c.h"
#అన్తర్భావ "../../SDL_hints_c.h"

#అన్తర్భావ "SDL_androidvideo.h"
#అన్తర్భావ "SDL_androidgl.h"
#అన్తర్భావ "SDL_androidclipboard.h"
#అన్తర్భావ "SDL_androidevents.h"
#అన్తర్భావ "SDL_androidkeyboard.h"
#అన్తర్భావ "SDL_androidmouse.h"
#అన్తర్భావ "SDL_androidtouch.h"
#అన్తర్భావ "SDL_androidwindow.h"
#అన్తర్భావ "SDL_androidvulkan.h"
#అన్తర్భావ "SDL_androidmessagebox.h"

#నిర్వచించు ANDROID_VID_DRIVER_NAME "android"

// Initialization/Query functions
స్థిర bool Android_VideoInit(SDL_VideoDevice *_this);
స్థిర శూన్య Android_VideoQuit(SDL_VideoDevice *_this);

#అన్తర్భావ "../SDL_egl_c.h"
#నిర్వచించు Android_GLES_Get_Proc_చిరునామా  SDL_EGL_Get_Proc_చిరునామా_అంతర్గత
#నిర్వచించు Android_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#నిర్వచించు Android_GLES_సమితి_మార్పిడి_Interval SDL_EGL_సమితి_మార్పిడి_Interval
#నిర్వచించు Android_GLES_Get_మార్పిడి_Interval SDL_EGL_Get_మార్పిడి_Interval
#నిర్వచించు Android_GLES_DestroyContext   SDL_EGL_DestroyContext

// Android driver bootstrap functions

// These are filled in with real values in Android_SetScreenResolution on init (before SDL_main())
పూర్ణాంకం Android_Surface_వెడల్పు = 0;
పూర్ణాంకం Android_Surface_ఎత్తు = 0;
స్థిర పూర్ణాంకం Android_Device_వెడల్పు = 0;
స్థిర పూర్ణాంకం Android_Device_ఎత్తు = 0;
స్థిర Uint32 Android_ScreenFormat = SDL_PIXELFORMAT_RGB565; // Default SurfaceView format, in case this is queried before being filled
దశాంశం Android_ScreenDensity = 1.0f;
స్థిర దశాంశం Android_Screen_రేటు = 0.0f;
స్థిర దశాంశం Android_ScreenHDRHeadroom = 1.0f;
స్థిర SDL_DisplayOrientation Android_ScreenOrientation = SDL_ORIENTATION_UNKNOWN;
పూర్ణాంకం Android_సురక్షిత_Inset_ఎడమ = 0;
పూర్ణాంకం Android_సురక్షిత_Inset_కుడి = 0;
పూర్ణాంకం Android_సురక్షిత_Inset_శిఖరం = 0;
పూర్ణాంకం Android_సురక్షిత_Inset_Bottom = 0;
స్థిర SDL_SystemTheme Android_SystemTheme;

స్థిర bool Android_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    తిరిగి Android_JNI_SuspendScreenSaver(_this->suspend_screensaver);
}

స్థిర శూన్య Android_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->అంతర్గత);
    SDL_free(device);
}

// Input is part of video for Android, so this goes here.
స్థిర శూన్య SDLCALL Android_Video_అంతర్గత_Hint_Callback(
    శూన్య *userdata,
    స్థిరరాశి అక్షరం *name,
    స్థిరరాశి అక్షరం *oldvalue,
    స్థిరరాశి అక్షరం *newvalue)
{
    Android_JNI_సమితి_వెనుక_Button_Trap_చురుకైన(SDL_GetStringBoolean(newvalue, false));
}

స్థిర SDL_VideoDevice *Android_CreateDevice(శూన్య)
{
    SDL_VideoDevice *device;
    SDL_Video_దత్తాంశం *దత్తాంశం;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, పరిమాణం(SDL_VideoDevice));
    ఒకవేళ (!device) {
        తిరిగి ఖాళీ;
    }

    దత్తాంశం = (SDL_Video_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_Video_దత్తాంశం));
    ఒకవేళ (!దత్తాంశం) {
        SDL_free(device);
        తిరిగి ఖాళీ;
    }

    device->అంతర్గత = దత్తాంశం;
    device->system_theme = Android_SystemTheme;

    // Set the function pointers
    device->VideoInit = Android_VideoInit;
    device->VideoQuit = Android_VideoQuit;

    device->CreateSDLWindow = Android_Create_కిటికీ;
    device->సమితి_కిటికీ_Title = Android_సమితి_కిటికీ_Title;
    device->సమితి_కిటికీ_Fullscreen = Android_సమితి_కిటికీ_Fullscreen;
    device->Minimize_కిటికీ = Android_Minimize_కిటికీ;
    device->సమితి_కిటికీ_Resizable = Android_సమితి_కిటికీ_Resizable;
    device->Destroy_కిటికీ = Android_Destroy_కిటికీ;

    device->విడుదల = Android_DeleteDevice;

    // GL pointers
#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
    device->GL_ఎక్కించు_Library = Android_GLES_ఎక్కించు_Library;
    device->GL_Get_Proc_చిరునామా = Android_GLES_Get_Proc_చిరునామా;
    device->GL_UnloadLibrary = Android_GLES_UnloadLibrary;
    device->GL_CreateContext = Android_GLES_CreateContext;
    device->GL_MakeCurrent = Android_GLES_MakeCurrent;
    device->GL_సమితి_మార్పిడి_Interval = Android_GLES_సమితి_మార్పిడి_Interval;
    device->GL_Get_మార్పిడి_Interval = Android_GLES_Get_మార్పిడి_Interval;
    device->GL_మార్పిడి_కిటికీ = Android_GLES_మార్పిడి_కిటికీ;
    device->GL_DestroyContext = Android_GLES_DestroyContext;
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_VIDEO_VULKAN
    device->Vulkan_ఎక్కించు_Library = Android_Vulkan_ఎక్కించు_Library;
    device->Vulkan_UnloadLibrary = Android_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = Android_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = Android_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = Android_Vulkan_DestroySurface;
#అయితే_ముగింపు

    // Screensaver
    device->SuspendScreenSaver = Android_SuspendScreenSaver;

    // Screen keyboard
    device->HasScreenKeyboardSupport = Android_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = Android_ShowScreenKeyboard;
    device->HideScreenKeyboard = Android_HideScreenKeyboard;

    // Clipboard
    device->సమితి_Clipboard_పాఠ్యం = Android_సమితి_Clipboard_పాఠ్యం;
    device->Get_Clipboard_పాఠ్యం = Android_Get_Clipboard_పాఠ్యం;
    device->Has_Clipboard_పాఠ్యం = Android_Has_Clipboard_పాఠ్యం;

    device->device_caps = VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS;

    తిరిగి device;
}

VideoBootStrap Android_bootstrap = {
    ANDROID_VID_DRIVER_NAME, "SDL Android video driver",
    Android_CreateDevice,
    Android_Show_సందేశం_Box,
    false
};

bool Android_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;
    SDL_DisplayID displayID;
    SDL_VideoDisplay *display;
    SDL_Display_బహుళకం బహుళకం;

    videodata->isPaused = false;
    videodata->isPausing = false;

    SDL_zero(బహుళకం);
    బహుళకం.format = Android_ScreenFormat;
    బహుళకం.w = Android_Device_వెడల్పు;
    బహుళకం.h = Android_Device_ఎత్తు;
    బహుళకం.refresh_రేటు = Android_Screen_రేటు;

    displayID = SDL_కూడు_Basic_Video_Display(&బహుళకం);
    ఒకవేళ (displayID == 0) {
        తిరిగి false;
    }
    display = SDL_GetVideoDisplay(displayID);
    display->natural_orientation = Android_JNI_GetDisplayNaturalOrientation();
    display->current_orientation = Android_JNI_GetDisplayCurrentOrientation();
    display->content_scale = Android_ScreenDensity;
    Android_సమితి_Screen_HDRHeadroom(Android_ScreenHDRHeadroom);

    SDL_కూడు_Hint_Callback(SDL_HINT_ANDROID_TRAP_వెనుక_BUTTON, Android_Video_అంతర్గత_Hint_Callback, 0);

    Android_InitTouch();

    Android_InitMouse();

    // We're done!
    తిరిగి true;
}

శూన్య Android_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_RemoveHintCallback(SDL_HINT_ANDROID_TRAP_వెనుక_BUTTON, Android_Video_అంతర్గత_Hint_Callback, 0);
    Android_QuitMouse();
    Android_QuitTouch();
}

శూన్య Android_సమితి_Screen_Resolution(పూర్ణాంకం surface_వెడల్పు, పూర్ణాంకం surface_ఎత్తు, పూర్ణాంకం device_వెడల్పు, పూర్ణాంకం device_ఎత్తు, దశాంశం density, దశాంశం రేటు)
{
    Android_Surface_వెడల్పు = surface_వెడల్పు;
    Android_Surface_ఎత్తు = surface_ఎత్తు;
    Android_Device_వెడల్పు = device_వెడల్పు;
    Android_Device_ఎత్తు = device_ఎత్తు;
    Android_ScreenDensity = (density > 0.0f) ? density : 1.0f;
    Android_Screen_రేటు = రేటు;
}

శూన్య Android_సమితి_Screen_HDRHeadroom(దశాంశం headroom)
{
    Android_ScreenHDRHeadroom = headroom;

    SDL_VideoDevice *device = SDL_GetVideoDevice();
    ఒకవేళ (device && device->అంకె_displays > 0) {
        SDL_VideoDisplay *display = device->displays[0];
        SDL_HDROutputProperties HDR;

        HDR.SDR_white_level = 1.0f;
        HDR.HDR_headroom = headroom;
        SDL_సమితి_Display_HDRProperties(display, &HDR);
    }
}

స్థిర Uint32 format_గమ్యం_pixel_Format(పూర్ణాంకం format)
{
    Uint32 pf;
    ఒకవేళ (format == AHARDWAREBUFFER_FORMAT_R8G8B8A8_UNORM) { // 1
        pf = SDL_PIXELFORMAT_RGBA8888;
    } లేకపోతే ఒకవేళ (format == AHARDWAREBUFFER_FORMAT_R8G8B8X8_UNORM) { // 2
        pf = SDL_PIXELFORMAT_RGBX8888;
    } లేకపోతే ఒకవేళ (format == AHARDWAREBUFFER_FORMAT_R8G8B8_UNORM) { // 3
        pf = SDL_PIXELFORMAT_RGB24;
    } లేకపోతే ఒకవేళ (format == AHARDWAREBUFFER_FORMAT_R5G6B5_UNORM) { // 4
        pf = SDL_PIXELFORMAT_RGB565;
    } లేకపోతే ఒకవేళ (format == 5) {
        pf = SDL_PIXELFORMAT_BGRA8888;
    } లేకపోతే ఒకవేళ (format == 6) {
        pf = SDL_PIXELFORMAT_RGBA5551;
    } లేకపోతే ఒకవేళ (format == 7) {
        pf = SDL_PIXELFORMAT_RGBA4444;
    } లేకపోతే ఒకవేళ (format == 0x115) {
        // HAL_PIXEL_FORMAT_BGR_565
        pf = SDL_PIXELFORMAT_RGB565;
    } లేకపోతే {
        pf = SDL_PIXELFORMAT_UNKNOWN;
    }
    తిరిగి pf;
}

శూన్య Android_సమితి_Format(పూర్ణాంకం format_wanted, పూర్ణాంకం format_got)
{
    Uint32 pf_wanted;
    Uint32 pf_got;

    pf_wanted = format_గమ్యం_pixel_Format(format_wanted);
    pf_got = format_గమ్యం_pixel_Format(format_got);

    Android_ScreenFormat = pf_got;

    SDL_Log("pixel format wanted %s (%d), got %s (%d)",
            SDL_GetPixelFormatName(pf_wanted), format_wanted,
            SDL_GetPixelFormatName(pf_got), format_got);
}

స్థిర శూన్య Android_SendOrientationUpdate(శూన్య)
{
    /* If we've received a compatible resize event, update the
     * orientation immediately, otherwise wait for the display
     * resize event.
     */
    SDL_VideoDevice *device = SDL_GetVideoDevice();
    ఒకవేళ (device && device->అంకె_displays > 0) {
        SDL_VideoDisplay *display = device->displays[0];
        bool బహుళకం_landscape = (display->desktop_బహుళకం.w > display->desktop_బహుళకం.h);
        bool sensor_landscape = (Android_ScreenOrientation == SDL_ORIENTATION_LANDSCAPE || Android_ScreenOrientation == SDL_ORIENTATION_LANDSCAPE_FLIPPED);
        ఒకవేళ (sensor_landscape == బహుళకం_landscape) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_ORIENTATION, Android_ScreenOrientation, 0);
        }
    }
}

శూన్య Android_సమితి_Orientation(SDL_DisplayOrientation orientation)
{
    Android_ScreenOrientation = orientation;
    Android_SendOrientationUpdate();
}

శూన్య Android_SendResize(SDL_కిటికీ *కిటికీ)
{
    /*
      Update the resolution of the desktop mode, so that the window
      can be properly resized. The screen resolution change can for
      example happen when the Activity enters or exits immersive mode,
      which can happen after VideoInit().
    */
    SDL_VideoDevice *device = SDL_GetVideoDevice();
    ఒకవేళ (device && device->అంకె_displays > 0) {
        SDL_VideoDisplay *display = device->displays[0];
        SDL_Display_బహుళకం desktop_బహుళకం;

        SDL_zero(desktop_బహుళకం);
        desktop_బహుళకం.format = Android_ScreenFormat;
        desktop_బహుళకం.w = Android_Device_వెడల్పు;
        desktop_బహుళకం.h = Android_Device_ఎత్తు;
        desktop_బహుళకం.refresh_రేటు = Android_Screen_రేటు;
        SDL_సమితి_Desktop_Display_బహుళకం(display, &desktop_బహుళకం);
        Android_SendOrientationUpdate();
    }

    ఒకవేళ (కిటికీ) {
        SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_RESIZED, Android_Surface_వెడల్పు, Android_Surface_ఎత్తు);
    }
}

శూన్య Android_సమితి_కిటికీ_సురక్షిత_Area_Insets(పూర్ణాంకం ఎడమ, పూర్ణాంకం కుడి, పూర్ణాంకం శిఖరం, పూర్ణాంకం bottom)
{
    Android_సురక్షిత_Inset_ఎడమ = ఎడమ;
    Android_సురక్షిత_Inset_కుడి = కుడి;
    Android_సురక్షిత_Inset_శిఖరం = శిఖరం;
    Android_సురక్షిత_Inset_Bottom = bottom;

    ఒకవేళ (Android_కిటికీ) {
        SDL_సమితి_కిటికీ_సురక్షిత_Area_Insets(Android_కిటికీ, ఎడమ, కుడి, శిఖరం, bottom);
    }
}

శూన్య Android_సమితి_Dark_బహుళకం(bool enabled)
{
    SDL_VideoDevice *device = SDL_GetVideoDevice();

    ఒకవేళ (enabled) {
        Android_SystemTheme = SDL_SYSTEM_THEME_DARK;
    } లేకపోతే {
        Android_SystemTheme = SDL_SYSTEM_THEME_LIGHT;
    }

    ఒకవేళ (device) {
        SDL_సమితి_System_Theme(Android_SystemTheme);
    }
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_ANDROID
