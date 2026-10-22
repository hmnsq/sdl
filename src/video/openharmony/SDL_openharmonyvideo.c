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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_OPENHARMONY

// HarmonyOS/OpenHarmony SDL video driver implementation

#ಅನ್ತರ್ಭಾವ <window_manager/oh_display_manager.h>

// !!! FIXME: these are defined as "const uint32_t VARNAME = VALUE;" in native_interface_xcomponent.h, which becomes a global variable in _our_ C code! Maybe C++ handles this differently...?
#ವ್ಯಾಖ್ಯಾನಿಸು OH_XCOMPONENT_ID_LEN_MAX sdl_ohosvideo_OH_XCOMPONENT_ID_LEN_MAX
#ವ್ಯಾಖ್ಯಾನಿಸು OH_MAX_TOUCH_POINTS_ಸಂಖ್ಯೆ sdl_ohosvideo_OH_MAX_TOUCH_POINTS_ಸಂಖ್ಯೆ
#ಅನ್ತರ್ಭಾವ <ace/xcomponent/native_interface_xcomponent.h>

// !!! FIXME: move stuff in from Android code

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../SDL_pixels_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_windowevents_c.h"

#ಅನ್ತರ್ಭಾವ "SDL_openharmonyvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_openharmonyopengl.h"
#ಅನ್ತರ್ಭಾವ "SDL_openharmonyclipboard.h"
#ಅನ್ತರ್ಭಾವ "SDL_openharmonyevents.h"
#ಅನ್ತರ್ಭಾವ "SDL_openharmonykeyboard.h"
#ಅನ್ತರ್ಭಾವ "SDL_openharmonymouse.h"
//#include "SDL_openharmonytouch.h"
#ಅನ್ತರ್ಭಾವ "SDL_openharmonywindow.h"
#ಅನ್ತರ್ಭಾವ "SDL_openharmonyvulkan.h"
//#include "SDL_openharmonymessagebox.h"

#ವ್ಯಾಖ್ಯಾನಿಸು OPENHARMONY_VID_DRIVER_NAME "openharmony"

#ಅನ್ತರ್ಭಾವ "../SDL_egl_c.h"
#ವ್ಯಾಖ್ಯಾನಿಸು OPENHARMONY_GLES_Get_Proc_ವಿಳಾಸ  SDL_EGL_Get_Proc_ವಿಳಾಸ_ಆಂತರಿಕ
#ವ್ಯಾಖ್ಯಾನಿಸು OPENHARMONY_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#ವ್ಯಾಖ್ಯಾನಿಸು OPENHARMONY_GLES_ಗಣ_ಅದಲುಬದಲು_Interval SDL_EGL_ಗಣ_ಅದಲುಬದಲು_Interval
#ವ್ಯಾಖ್ಯಾನಿಸು OPENHARMONY_GLES_Get_ಅದಲುಬದಲು_Interval SDL_EGL_Get_ಅದಲುಬದಲು_Interval
#ವ್ಯಾಖ್ಯಾನಿಸು OPENHARMONY_GLES_DestroyContext   SDL_EGL_DestroyContext


ಸ್ಥಿರ OH_NativeXComponent *native_xcomponent = ಖಾಲಿ;
ಸ್ಥಿರ ಶೂನ್ಯ *native_ಕಿಟಕಿ = ಖಾಲಿ;

ಶೂನ್ಯ SDL_Open_Harmony_Get_Native_ಕಿಟಕಿ_ಸೂಚಕಗಳು(ಶೂನ್ಯ **xcomponent, ಶೂನ್ಯ **ಕಿಟಕಿ)
{
    *xcomponent = (ಶೂನ್ಯ *) native_xcomponent;
    *ಕಿಟಕಿ = (ಶೂನ್ಯ *) native_ಕಿಟಕಿ;
}

ಶೂನ್ಯ SDL_OpenHarmonyVideoSurfaceDestroyed(ಶೂನ್ಯ *component, ಶೂನ್ಯ *ಕಿಟಕಿ)
{
    SDL_assert(native_xcomponent == ((OH_NativeXComponent *) component));  // right now we assume one surface, one window.
    native_xcomponent = ಖಾಲಿ;
    native_ಕಿಟಕಿ = ಖಾಲಿ;
}

ಶೂನ್ಯ SDL_Open_Harmony_Video_Surface_ಬದಲಾಯಿತು(ಶೂನ್ಯ *component, ಶೂನ್ಯ *ಕಿಟಕಿ)
{
    SDL_assert(native_xcomponent == ((OH_NativeXComponent *) component));  // right now we assume one surface, one window.
    uint64_t w, h;
    OH_Native_XComponent_Get_XComponent_ಗಾತ್ರ(native_xcomponent, native_ಕಿಟಕಿ, &w, &h);
    SDL_Send_ಕಿಟಕಿ_Event(OPENHARMONY_ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_RESIZED, (ಪೂರ್ಣಾಂಕ) w, (ಪೂರ್ಣಾಂಕ) h);
}

ಶೂನ್ಯ SDL_OpenHarmonyVideoSurfaceCreated(ಶೂನ್ಯ *component, ಶೂನ್ಯ *ಕಿಟಕಿ)
{
    SDL_assert(native_xcomponent == ಖಾಲಿ);  // right now we assume one surface, one window.
    native_xcomponent = (OH_NativeXComponent *) component;
    native_ಕಿಟಕಿ = ಕಿಟಕಿ;
}

ಸ್ಥಿರ bool OPENHARMONY_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    ಹಿಂತಿರುಗಿ SDL_OpenHarmonyChangeScreenSaver(!_this->suspend_screensaver);
}

ಸ್ಥಿರ bool OPENHARMONY_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;

    videodata->isPaused = false;
    videodata->isPausing = false;

    // !!! FIXME: eventually we'll want to enumerate displays, since you can probably plug in something
    // !!! FIXME:  through a USB-C to HDMI adapter, or maybe there will be separate "outer" screens vs
    // !!! FIXME:  an internal foldable one, but for now let's just get _something_ on _any_ display.
    uint64_t dispid64 = 0;
    ಆದರೆ (OH_NativeDisplayManager_GetDefaultDisplayId(&dispid64) != DISPLAY_MANAGER_OK) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Couldn't get default display id");
    }
    ಸ್ಥಿರಾಂಕ uint32_t dispid = (uint32_t) dispid64;

    NativeDisplayManager_DisplayInfo *dispinfo = ಖಾಲಿ;
    ಆದರೆ (OH_NativeDisplayManager_CreateDisplayById(dispid, &dispinfo) != DISPLAY_MANAGER_OK) {  // (should really be called "CreateDisplayInfo", not "CreateDisplay")
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Couldn't get default display info");
    }

    SDL_Display_ಬಹುಲಕ ಬಹುಲಕ;
    SDL_zero(ಬಹುಲಕ);
    ಬಹುಲಕ.format = SDL_PIXELFORMAT_BGRA8888;  // !!! FIXME
    ಬಹುಲಕ.w = (ಪೂರ್ಣಾಂಕ) dispinfo->physical_ಅಗಲ;
    ಬಹುಲಕ.h = (ಪೂರ್ಣಾಂಕ) dispinfo->physical_ಎತ್ತರ;
    ಬಹುಲಕ.refresh_ದರ = (ದಶಮಾಂಶ) dispinfo->refresh_ದರ_2;
    ಬಹುಲಕ.pixel_density = 1.0f;

    ಸ್ಥಿರಾಂಕ NativeDisplayManager_Rotation rotation = dispinfo->rotation;
    ಸ್ಥಿರಾಂಕ NativeDisplayManager_Orientation orientation = dispinfo->orientation;

    OH_NativeDisplayManager_DestroyDisplay(dispinfo);

    ಸ್ಥಿರಾಂಕ SDL_DisplayID displayID = SDL_ಕೂಡಿಸು_Basic_Video_Display(&ಬಹುಲಕ);
    ಆದರೆ (displayID == 0) {
        ಹಿಂತಿರುಗಿ false;
    }

    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    ಆಯ್ಕೆ (orientation) {
        ಸ್ಥಿತಿ DISPLAY_MANAGER_PORTRAIT: display->natural_orientation = SDL_ORIENTATION_PORTRAIT; ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ DISPLAY_MANAGER_LANDSCAPE: display->natural_orientation = SDL_ORIENTATION_LANDSCAPE; ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ DISPLAY_MANAGER_PORTRAIT_INVERTED: display->natural_orientation = SDL_ORIENTATION_PORTRAIT_FLIPPED; ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ DISPLAY_MANAGER_LANDSCAPE_INVERTED: display->natural_orientation = SDL_ORIENTATION_LANDSCAPE_FLIPPED; ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ: display->natural_orientation = SDL_ORIENTATION_UNKNOWN; ನಿಲ್ಲಿಸು;
    }

    // !!! FIXME: this is probably wrong, I think on OpenHarmony phones/tablets, these are setting both orientation and rotation, and this works out because most people are launching apps while holding the phone in portrait mode (0 rotation).
    // !!! FIXME: if I'm right, we should decide if this is a phone/tablet screen and just set the natural orientation to portrait and then use this code to calculate current orientation.
    ಆದರೆ (rotation == DISPLAY_MANAGER_ROTATION_90) {  // rotations are clockwise on OpenHarmony.
        ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ SDL_DisplayOrientation rotated[5] = { SDL_ORIENTATION_UNKNOWN, SDL_ORIENTATION_PORTRAIT, SDL_ORIENTATION_PORTRAIT_FLIPPED, SDL_ORIENTATION_LANDSCAPE_FLIPPED, SDL_ORIENTATION_LANDSCAPE };
        SDL_assert(((ಪೂರ್ಣಾಂಕ) display->natural_orientation) < SDL_arraysize(rotated));
        display->current_orientation = rotated[(ಪೂರ್ಣಾಂಕ) display->natural_orientation];
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (rotation == DISPLAY_MANAGER_ROTATION_180) {  // rotations are clockwise on OpenHarmony.
        ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ SDL_DisplayOrientation rotated[5] = { SDL_ORIENTATION_UNKNOWN, SDL_ORIENTATION_LANDSCAPE_FLIPPED, SDL_ORIENTATION_LANDSCAPE, SDL_ORIENTATION_PORTRAIT_FLIPPED, SDL_ORIENTATION_PORTRAIT };
        SDL_assert(((ಪೂರ್ಣಾಂಕ) display->natural_orientation) < SDL_arraysize(rotated));
        display->current_orientation = rotated[(ಪೂರ್ಣಾಂಕ) display->natural_orientation];
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (rotation == DISPLAY_MANAGER_ROTATION_270) {  // rotations are clockwise on OpenHarmony.
        ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ SDL_DisplayOrientation rotated[5] = { SDL_ORIENTATION_UNKNOWN, SDL_ORIENTATION_PORTRAIT_FLIPPED, SDL_ORIENTATION_PORTRAIT, SDL_ORIENTATION_LANDSCAPE, SDL_ORIENTATION_LANDSCAPE_FLIPPED };
        SDL_assert(((ಪೂರ್ಣಾಂಕ) display->natural_orientation) < SDL_arraysize(rotated));
        display->current_orientation = rotated[(ಪೂರ್ಣಾಂಕ) display->natural_orientation];
    } ಇಲ್ಲದಿದ್ದರೆ {
        display->current_orientation = display->natural_orientation;
    }

    display->content_scale = ಬಹುಲಕ.pixel_density;

    // !!! FIXME: look at SDL_OnApplicationDidChangeStatusBarOrientation() and do something similar.


// !!! FIXME
#ಆದರೆ 0
    OPENHARMONY_InitTouch();
    OPENHARMONY_InitMouse();
#ಆದರೆ_ಅಂತ್ಯ
    OPENHARMONY_InitClipboard(_this);

    // We're done!
    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ OPENHARMONY_VideoQuit(SDL_VideoDevice *_this)
{
    OPENHARMONY_QuitClipboard(_this);

// !!! FIXME
#ಆದರೆ 0
    OPENHARMONY_QuitMouse();
    OPENHARMONY_QuitTouch();
#ಆದರೆ_ಅಂತ್ಯ
}

ಸ್ಥಿರ ಶೂನ್ಯ OPENHARMONY_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->ಆಂತರಿಕ);
    SDL_free(device);
}

ಸ್ಥಿರ SDL_VideoDevice *OPENHARMONY_CreateDevice(ಶೂನ್ಯ)
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
    device->system_theme = SDL_GetOpenHarmonySystemTheme();

    // Set the function pointers
    device->VideoInit = OPENHARMONY_VideoInit;
    device->VideoQuit = OPENHARMONY_VideoQuit;

    device->CreateSDLWindow = OPENHARMONY_Create_ಕಿಟಕಿ;
    device->ಗಣ_ಕಿಟಕಿ_Title = OPENHARMONY_ಗಣ_ಕಿಟಕಿ_Title;
    device->ಗಣ_ಕಿಟಕಿ_Fullscreen = OPENHARMONY_ಗಣ_ಕಿಟಕಿ_Fullscreen;
    device->Minimize_ಕಿಟಕಿ = OPENHARMONY_Minimize_ಕಿಟಕಿ;
    device->ಗಣ_ಕಿಟಕಿ_Resizable = OPENHARMONY_ಗಣ_ಕಿಟಕಿ_Resizable;
    device->Destroy_ಕಿಟಕಿ = OPENHARMONY_Destroy_ಕಿಟಕಿ;

    device->ಬಿಡುಗಡೆ = OPENHARMONY_DeleteDevice;

    // GL pointers
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
    device->GL_ತುಂಬು_Library = OPENHARMONY_GLES_ತುಂಬು_Library;
    device->GL_Get_Proc_ವಿಳಾಸ = OPENHARMONY_GLES_Get_Proc_ವಿಳಾಸ;
    device->GL_UnloadLibrary = OPENHARMONY_GLES_UnloadLibrary;
    device->GL_CreateContext = OPENHARMONY_GLES_CreateContext;
    device->GL_MakeCurrent = OPENHARMONY_GLES_MakeCurrent;
    device->GL_ಗಣ_ಅದಲುಬದಲು_Interval = OPENHARMONY_GLES_ಗಣ_ಅದಲುಬದಲು_Interval;
    device->GL_Get_ಅದಲುಬದಲು_Interval = OPENHARMONY_GLES_Get_ಅದಲುಬದಲು_Interval;
    device->GL_ಅದಲುಬದಲು_ಕಿಟಕಿ = OPENHARMONY_GLES_ಅದಲುಬದಲು_ಕಿಟಕಿ;
    device->GL_DestroyContext = OPENHARMONY_GLES_DestroyContext;
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_VULKAN
    device->Vulkan_ತುಂಬು_Library = OPENHARMONY_Vulkan_ತುಂಬು_Library;
    device->Vulkan_UnloadLibrary = OPENHARMONY_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = OPENHARMONY_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = OPENHARMONY_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = OPENHARMONY_Vulkan_DestroySurface;
#ಆದರೆ_ಅಂತ್ಯ

    // Screensaver
    device->SuspendScreenSaver = OPENHARMONY_SuspendScreenSaver;

    device->PumpEvents = OPENHARMONY_PumpEvents;

    // Screen keyboard
    device->HasScreenKeyboardSupport = OPENHARMONY_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = OPENHARMONY_ShowScreenKeyboard;
    device->HideScreenKeyboard = OPENHARMONY_HideScreenKeyboard;

    // Clipboard
    device->Get_ಪಠ್ಯ_Mime_Types = OPENHARMONY_Get_ಪಠ್ಯ_Mime_Types;
    device->ಗಣ_Clipboard_ಪಠ್ಯ = OPENHARMONY_ಗಣ_Clipboard_ಪಠ್ಯ;
    device->Get_Clipboard_ಪಠ್ಯ = OPENHARMONY_Get_Clipboard_ಪಠ್ಯ;
    device->Has_Clipboard_ಪಠ್ಯ = OPENHARMONY_Has_Clipboard_ಪಠ್ಯ;

    device->device_caps = VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS;

    ಹಿಂತಿರುಗಿ device;
}

VideoBootStrap OPENHARMONY_bootstrap = {
    OPENHARMONY_VID_DRIVER_NAME, "SDL OpenHarmony/HarmonyOS video driver",
    OPENHARMONY_CreateDevice,
    /*!!! FIXME OPENHARMONY_ShowMessageBox*/ ಖಾಲಿ,
    false
};

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_OPENHARMONY
