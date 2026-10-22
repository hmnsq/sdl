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

#నిర్వచితమైతే SDL_VIDEO_DRIVER_OPENHARMONY

// HarmonyOS/OpenHarmony SDL video driver implementation

#అన్తర్భావ <window_manager/oh_display_manager.h>

// !!! FIXME: these are defined as "const uint32_t VARNAME = VALUE;" in native_interface_xcomponent.h, which becomes a global variable in _our_ C code! Maybe C++ handles this differently...?
#నిర్వచించు OH_XCOMPONENT_ID_LEN_MAX sdl_ohosvideo_OH_XCOMPONENT_ID_LEN_MAX
#నిర్వచించు OH_MAX_TOUCH_POINTS_సంఖ్య sdl_ohosvideo_OH_MAX_TOUCH_POINTS_సంఖ్య
#అన్తర్భావ <ace/xcomponent/native_interface_xcomponent.h>

// !!! FIXME: move stuff in from Android code

#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "../SDL_pixels_c.h"
#అన్తర్భావ "../../events/SDL_events_c.h"
#అన్తర్భావ "../../events/SDL_windowevents_c.h"

#అన్తర్భావ "SDL_openharmonyvideo.h"
#అన్తర్భావ "SDL_openharmonyopengl.h"
#అన్తర్భావ "SDL_openharmonyclipboard.h"
#అన్తర్భావ "SDL_openharmonyevents.h"
#అన్తర్భావ "SDL_openharmonykeyboard.h"
#అన్తర్భావ "SDL_openharmonymouse.h"
//#include "SDL_openharmonytouch.h"
#అన్తర్భావ "SDL_openharmonywindow.h"
#అన్తర్భావ "SDL_openharmonyvulkan.h"
//#include "SDL_openharmonymessagebox.h"

#నిర్వచించు OPENHARMONY_VID_DRIVER_NAME "openharmony"

#అన్తర్భావ "../SDL_egl_c.h"
#నిర్వచించు OPENHARMONY_GLES_Get_Proc_చిరునామా  SDL_EGL_Get_Proc_చిరునామా_అంతర్గత
#నిర్వచించు OPENHARMONY_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#నిర్వచించు OPENHARMONY_GLES_సమితి_మార్పిడి_Interval SDL_EGL_సమితి_మార్పిడి_Interval
#నిర్వచించు OPENHARMONY_GLES_Get_మార్పిడి_Interval SDL_EGL_Get_మార్పిడి_Interval
#నిర్వచించు OPENHARMONY_GLES_DestroyContext   SDL_EGL_DestroyContext


స్థిర OH_NativeXComponent *native_xcomponent = ఖాళీ;
స్థిర శూన్య *native_కిటికీ = ఖాళీ;

శూన్య SDL_Open_Harmony_Get_Native_కిటికీ_సూచికలు(శూన్య **xcomponent, శూన్య **కిటికీ)
{
    *xcomponent = (శూన్య *) native_xcomponent;
    *కిటికీ = (శూన్య *) native_కిటికీ;
}

శూన్య SDL_OpenHarmonyVideoSurfaceDestroyed(శూన్య *component, శూన్య *కిటికీ)
{
    SDL_assert(native_xcomponent == ((OH_NativeXComponent *) component));  // right now we assume one surface, one window.
    native_xcomponent = ఖాళీ;
    native_కిటికీ = ఖాళీ;
}

శూన్య SDL_Open_Harmony_Video_Surface_మారింది(శూన్య *component, శూన్య *కిటికీ)
{
    SDL_assert(native_xcomponent == ((OH_NativeXComponent *) component));  // right now we assume one surface, one window.
    uint64_t w, h;
    OH_Native_XComponent_Get_XComponent_కొలత(native_xcomponent, native_కిటికీ, &w, &h);
    SDL_Send_కిటికీ_Event(OPENHARMONY_కిటికీ, SDL_EVENT_కిటికీ_RESIZED, (పూర్ణాంకం) w, (పూర్ణాంకం) h);
}

శూన్య SDL_OpenHarmonyVideoSurfaceCreated(శూన్య *component, శూన్య *కిటికీ)
{
    SDL_assert(native_xcomponent == ఖాళీ);  // right now we assume one surface, one window.
    native_xcomponent = (OH_NativeXComponent *) component;
    native_కిటికీ = కిటికీ;
}

స్థిర bool OPENHARMONY_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    తిరిగి SDL_OpenHarmonyChangeScreenSaver(!_this->suspend_screensaver);
}

స్థిర bool OPENHARMONY_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;

    videodata->isPaused = false;
    videodata->isPausing = false;

    // !!! FIXME: eventually we'll want to enumerate displays, since you can probably plug in something
    // !!! FIXME:  through a USB-C to HDMI adapter, or maybe there will be separate "outer" screens vs
    // !!! FIXME:  an internal foldable one, but for now let's just get _something_ on _any_ display.
    uint64_t dispid64 = 0;
    ఒకవేళ (OH_NativeDisplayManager_GetDefaultDisplayId(&dispid64) != DISPLAY_MANAGER_OK) {
        తిరిగి SDL_సమితి_Error("Couldn't get default display id");
    }
    స్థిరరాశి uint32_t dispid = (uint32_t) dispid64;

    NativeDisplayManager_DisplayInfo *dispinfo = ఖాళీ;
    ఒకవేళ (OH_NativeDisplayManager_CreateDisplayById(dispid, &dispinfo) != DISPLAY_MANAGER_OK) {  // (should really be called "CreateDisplayInfo", not "CreateDisplay")
        తిరిగి SDL_సమితి_Error("Couldn't get default display info");
    }

    SDL_Display_బహుళకం బహుళకం;
    SDL_zero(బహుళకం);
    బహుళకం.format = SDL_PIXELFORMAT_BGRA8888;  // !!! FIXME
    బహుళకం.w = (పూర్ణాంకం) dispinfo->physical_వెడల్పు;
    బహుళకం.h = (పూర్ణాంకం) dispinfo->physical_ఎత్తు;
    బహుళకం.refresh_రేటు = (దశాంశం) dispinfo->refresh_రేటు_2;
    బహుళకం.pixel_density = 1.0f;

    స్థిరరాశి NativeDisplayManager_Rotation rotation = dispinfo->rotation;
    స్థిరరాశి NativeDisplayManager_Orientation orientation = dispinfo->orientation;

    OH_NativeDisplayManager_DestroyDisplay(dispinfo);

    స్థిరరాశి SDL_DisplayID displayID = SDL_కూడు_Basic_Video_Display(&బహుళకం);
    ఒకవేళ (displayID == 0) {
        తిరిగి false;
    }

    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    ఎంపిక (orientation) {
        స్థితి DISPLAY_MANAGER_PORTRAIT: display->natural_orientation = SDL_ORIENTATION_PORTRAIT; ఆపు;
        స్థితి DISPLAY_MANAGER_LANDSCAPE: display->natural_orientation = SDL_ORIENTATION_LANDSCAPE; ఆపు;
        స్థితి DISPLAY_MANAGER_PORTRAIT_INVERTED: display->natural_orientation = SDL_ORIENTATION_PORTRAIT_FLIPPED; ఆపు;
        స్థితి DISPLAY_MANAGER_LANDSCAPE_INVERTED: display->natural_orientation = SDL_ORIENTATION_LANDSCAPE_FLIPPED; ఆపు;
        అప్రమేయ: display->natural_orientation = SDL_ORIENTATION_UNKNOWN; ఆపు;
    }

    // !!! FIXME: this is probably wrong, I think on OpenHarmony phones/tablets, these are setting both orientation and rotation, and this works out because most people are launching apps while holding the phone in portrait mode (0 rotation).
    // !!! FIXME: if I'm right, we should decide if this is a phone/tablet screen and just set the natural orientation to portrait and then use this code to calculate current orientation.
    ఒకవేళ (rotation == DISPLAY_MANAGER_ROTATION_90) {  // rotations are clockwise on OpenHarmony.
        స్థిర స్థిరరాశి SDL_DisplayOrientation rotated[5] = { SDL_ORIENTATION_UNKNOWN, SDL_ORIENTATION_PORTRAIT, SDL_ORIENTATION_PORTRAIT_FLIPPED, SDL_ORIENTATION_LANDSCAPE_FLIPPED, SDL_ORIENTATION_LANDSCAPE };
        SDL_assert(((పూర్ణాంకం) display->natural_orientation) < SDL_arraysize(rotated));
        display->current_orientation = rotated[(పూర్ణాంకం) display->natural_orientation];
    } లేకపోతే ఒకవేళ (rotation == DISPLAY_MANAGER_ROTATION_180) {  // rotations are clockwise on OpenHarmony.
        స్థిర స్థిరరాశి SDL_DisplayOrientation rotated[5] = { SDL_ORIENTATION_UNKNOWN, SDL_ORIENTATION_LANDSCAPE_FLIPPED, SDL_ORIENTATION_LANDSCAPE, SDL_ORIENTATION_PORTRAIT_FLIPPED, SDL_ORIENTATION_PORTRAIT };
        SDL_assert(((పూర్ణాంకం) display->natural_orientation) < SDL_arraysize(rotated));
        display->current_orientation = rotated[(పూర్ణాంకం) display->natural_orientation];
    } లేకపోతే ఒకవేళ (rotation == DISPLAY_MANAGER_ROTATION_270) {  // rotations are clockwise on OpenHarmony.
        స్థిర స్థిరరాశి SDL_DisplayOrientation rotated[5] = { SDL_ORIENTATION_UNKNOWN, SDL_ORIENTATION_PORTRAIT_FLIPPED, SDL_ORIENTATION_PORTRAIT, SDL_ORIENTATION_LANDSCAPE, SDL_ORIENTATION_LANDSCAPE_FLIPPED };
        SDL_assert(((పూర్ణాంకం) display->natural_orientation) < SDL_arraysize(rotated));
        display->current_orientation = rotated[(పూర్ణాంకం) display->natural_orientation];
    } లేకపోతే {
        display->current_orientation = display->natural_orientation;
    }

    display->content_scale = బహుళకం.pixel_density;

    // !!! FIXME: look at SDL_OnApplicationDidChangeStatusBarOrientation() and do something similar.


// !!! FIXME
#ఒకవేళ 0
    OPENHARMONY_InitTouch();
    OPENHARMONY_InitMouse();
#అయితే_ముగింపు
    OPENHARMONY_InitClipboard(_this);

    // We're done!
    తిరిగి true;
}

శూన్య OPENHARMONY_VideoQuit(SDL_VideoDevice *_this)
{
    OPENHARMONY_QuitClipboard(_this);

// !!! FIXME
#ఒకవేళ 0
    OPENHARMONY_QuitMouse();
    OPENHARMONY_QuitTouch();
#అయితే_ముగింపు
}

స్థిర శూన్య OPENHARMONY_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->అంతర్గత);
    SDL_free(device);
}

స్థిర SDL_VideoDevice *OPENHARMONY_CreateDevice(శూన్య)
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
    device->system_theme = SDL_GetOpenHarmonySystemTheme();

    // Set the function pointers
    device->VideoInit = OPENHARMONY_VideoInit;
    device->VideoQuit = OPENHARMONY_VideoQuit;

    device->CreateSDLWindow = OPENHARMONY_Create_కిటికీ;
    device->సమితి_కిటికీ_Title = OPENHARMONY_సమితి_కిటికీ_Title;
    device->సమితి_కిటికీ_Fullscreen = OPENHARMONY_సమితి_కిటికీ_Fullscreen;
    device->Minimize_కిటికీ = OPENHARMONY_Minimize_కిటికీ;
    device->సమితి_కిటికీ_Resizable = OPENHARMONY_సమితి_కిటికీ_Resizable;
    device->Destroy_కిటికీ = OPENHARMONY_Destroy_కిటికీ;

    device->విడుదల = OPENHARMONY_DeleteDevice;

    // GL pointers
#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
    device->GL_ఎక్కించు_Library = OPENHARMONY_GLES_ఎక్కించు_Library;
    device->GL_Get_Proc_చిరునామా = OPENHARMONY_GLES_Get_Proc_చిరునామా;
    device->GL_UnloadLibrary = OPENHARMONY_GLES_UnloadLibrary;
    device->GL_CreateContext = OPENHARMONY_GLES_CreateContext;
    device->GL_MakeCurrent = OPENHARMONY_GLES_MakeCurrent;
    device->GL_సమితి_మార్పిడి_Interval = OPENHARMONY_GLES_సమితి_మార్పిడి_Interval;
    device->GL_Get_మార్పిడి_Interval = OPENHARMONY_GLES_Get_మార్పిడి_Interval;
    device->GL_మార్పిడి_కిటికీ = OPENHARMONY_GLES_మార్పిడి_కిటికీ;
    device->GL_DestroyContext = OPENHARMONY_GLES_DestroyContext;
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_VIDEO_VULKAN
    device->Vulkan_ఎక్కించు_Library = OPENHARMONY_Vulkan_ఎక్కించు_Library;
    device->Vulkan_UnloadLibrary = OPENHARMONY_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = OPENHARMONY_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = OPENHARMONY_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = OPENHARMONY_Vulkan_DestroySurface;
#అయితే_ముగింపు

    // Screensaver
    device->SuspendScreenSaver = OPENHARMONY_SuspendScreenSaver;

    device->PumpEvents = OPENHARMONY_PumpEvents;

    // Screen keyboard
    device->HasScreenKeyboardSupport = OPENHARMONY_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = OPENHARMONY_ShowScreenKeyboard;
    device->HideScreenKeyboard = OPENHARMONY_HideScreenKeyboard;

    // Clipboard
    device->Get_పాఠ్యం_Mime_Types = OPENHARMONY_Get_పాఠ్యం_Mime_Types;
    device->సమితి_Clipboard_పాఠ్యం = OPENHARMONY_సమితి_Clipboard_పాఠ్యం;
    device->Get_Clipboard_పాఠ్యం = OPENHARMONY_Get_Clipboard_పాఠ్యం;
    device->Has_Clipboard_పాఠ్యం = OPENHARMONY_Has_Clipboard_పాఠ్యం;

    device->device_caps = VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS;

    తిరిగి device;
}

VideoBootStrap OPENHARMONY_bootstrap = {
    OPENHARMONY_VID_DRIVER_NAME, "SDL OpenHarmony/HarmonyOS video driver",
    OPENHARMONY_CreateDevice,
    /*!!! FIXME OPENHARMONY_ShowMessageBox*/ ఖాళీ,
    false
};

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_OPENHARMONY
