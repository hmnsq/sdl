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

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_OPENHARMONY

// HarmonyOS/OpenHarmony SDL video driver implementation

#ਅਨ੍ਤਰ੍ਭਾਵ <window_manager/oh_display_manager.h>

// !!! FIXME: these are defined as "const uint32_t VARNAME = VALUE;" in native_interface_xcomponent.h, which becomes a global variable in _our_ C code! Maybe C++ handles this differently...?
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OH_XCOMPONENT_ID_LEN_MAX sdl_ohosvideo_OH_XCOMPONENT_ID_LEN_MAX
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OH_MAX_TOUCH_POINTS_ਸੰਖਿਆ sdl_ohosvideo_OH_MAX_TOUCH_POINTS_ਸੰਖਿਆ
#ਅਨ੍ਤਰ੍ਭਾਵ <ace/xcomponent/native_interface_xcomponent.h>

// !!! FIXME: move stuff in from Android code

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_pixels_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_events_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_windowevents_c.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_openharmonyvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_openharmonyopengl.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_openharmonyclipboard.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_openharmonyevents.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_openharmonykeyboard.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_openharmonymouse.h"
//#include "SDL_openharmonytouch.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_openharmonywindow.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_openharmonyvulkan.h"
//#include "SDL_openharmonymessagebox.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OPENHARMONY_VID_DRIVER_NAME "openharmony"

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_egl_c.h"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OPENHARMONY_GLES_Get_Proc_ਪਤਾ  SDL_EGL_Get_Proc_ਪਤਾ_ਅੰਦਰੂਨੀ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OPENHARMONY_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OPENHARMONY_GLES_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval SDL_EGL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OPENHARMONY_GLES_Get_ਅਦਲਾ_ਬਦਲੀ_Interval SDL_EGL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OPENHARMONY_GLES_DestroyContext   SDL_EGL_DestroyContext


ਸਥਿਰ OH_NativeXComponent *native_xcomponent = ਨਿਰਾ;
ਸਥਿਰ ਖਾਲੀ *native_ਖਿੜਕੀ = ਨਿਰਾ;

ਖਾਲੀ SDL_Open_Harmony_Get_Native_ਖਿੜਕੀ_ਸੂਚਕ_ਸਾਰੇ(ਖਾਲੀ **xcomponent, ਖਾਲੀ **ਖਿੜਕੀ)
{
    *xcomponent = (ਖਾਲੀ *) native_xcomponent;
    *ਖਿੜਕੀ = (ਖਾਲੀ *) native_ਖਿੜਕੀ;
}

ਖਾਲੀ SDL_OpenHarmonyVideoSurfaceDestroyed(ਖਾਲੀ *component, ਖਾਲੀ *ਖਿੜਕੀ)
{
    SDL_assert(native_xcomponent == ((OH_NativeXComponent *) component));  // right now we assume one surface, one window.
    native_xcomponent = ਨਿਰਾ;
    native_ਖਿੜਕੀ = ਨਿਰਾ;
}

ਖਾਲੀ SDL_Open_Harmony_Video_Surface_ਬਦਲਿਆ(ਖਾਲੀ *component, ਖਾਲੀ *ਖਿੜਕੀ)
{
    SDL_assert(native_xcomponent == ((OH_NativeXComponent *) component));  // right now we assume one surface, one window.
    uint64_t w, h;
    OH_Native_XComponent_Get_XComponent_ਮਾਪ(native_xcomponent, native_ਖਿੜਕੀ, &w, &h);
    SDL_Send_ਖਿੜਕੀ_Event(OPENHARMONY_ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_RESIZED, (ਪੂਰਨ) w, (ਪੂਰਨ) h);
}

ਖਾਲੀ SDL_OpenHarmonyVideoSurfaceCreated(ਖਾਲੀ *component, ਖਾਲੀ *ਖਿੜਕੀ)
{
    SDL_assert(native_xcomponent == ਨਿਰਾ);  // right now we assume one surface, one window.
    native_xcomponent = (OH_NativeXComponent *) component;
    native_ਖਿੜਕੀ = ਖਿੜਕੀ;
}

ਸਥਿਰ bool OPENHARMONY_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    ਵਾਪਸ SDL_OpenHarmonyChangeScreenSaver(!_this->suspend_screensaver);
}

ਸਥਿਰ bool OPENHARMONY_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;

    videodata->isPaused = false;
    videodata->isPausing = false;

    // !!! FIXME: eventually we'll want to enumerate displays, since you can probably plug in something
    // !!! FIXME:  through a USB-C to HDMI adapter, or maybe there will be separate "outer" screens vs
    // !!! FIXME:  an internal foldable one, but for now let's just get _something_ on _any_ display.
    uint64_t dispid64 = 0;
    ਜੇ (OH_NativeDisplayManager_GetDefaultDisplayId(&dispid64) != DISPLAY_MANAGER_OK) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Couldn't get default display id");
    }
    ਅਚਲ uint32_t dispid = (uint32_t) dispid64;

    NativeDisplayManager_DisplayInfo *dispinfo = ਨਿਰਾ;
    ਜੇ (OH_NativeDisplayManager_CreateDisplayById(dispid, &dispinfo) != DISPLAY_MANAGER_OK) {  // (should really be called "CreateDisplayInfo", not "CreateDisplay")
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Couldn't get default display info");
    }

    SDL_Display_ਬਹੁਲਕ ਬਹੁਲਕ;
    SDL_zero(ਬਹੁਲਕ);
    ਬਹੁਲਕ.format = SDL_PIXELFORMAT_BGRA8888;  // !!! FIXME
    ਬਹੁਲਕ.w = (ਪੂਰਨ) dispinfo->physical_ਚੌੜਾਈ;
    ਬਹੁਲਕ.h = (ਪੂਰਨ) dispinfo->physical_ਉਚਾਈ;
    ਬਹੁਲਕ.refresh_ਦਰ = (ਦਸ਼ਮਲਵ) dispinfo->refresh_ਦਰ_2;
    ਬਹੁਲਕ.pixel_density = 1.0f;

    ਅਚਲ NativeDisplayManager_Rotation rotation = dispinfo->rotation;
    ਅਚਲ NativeDisplayManager_Orientation orientation = dispinfo->orientation;

    OH_NativeDisplayManager_DestroyDisplay(dispinfo);

    ਅਚਲ SDL_DisplayID displayID = SDL_ਜੋੜੋ_Basic_Video_Display(&ਬਹੁਲਕ);
    ਜੇ (displayID == 0) {
        ਵਾਪਸ false;
    }

    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    ਚੋਣ (orientation) {
        ਹਾਲਤ DISPLAY_MANAGER_PORTRAIT: display->natural_orientation = SDL_ORIENTATION_PORTRAIT; ਰੋਕੋ;
        ਹਾਲਤ DISPLAY_MANAGER_LANDSCAPE: display->natural_orientation = SDL_ORIENTATION_LANDSCAPE; ਰੋਕੋ;
        ਹਾਲਤ DISPLAY_MANAGER_PORTRAIT_INVERTED: display->natural_orientation = SDL_ORIENTATION_PORTRAIT_FLIPPED; ਰੋਕੋ;
        ਹਾਲਤ DISPLAY_MANAGER_LANDSCAPE_INVERTED: display->natural_orientation = SDL_ORIENTATION_LANDSCAPE_FLIPPED; ਰੋਕੋ;
        ਮੂਲ: display->natural_orientation = SDL_ORIENTATION_UNKNOWN; ਰੋਕੋ;
    }

    // !!! FIXME: this is probably wrong, I think on OpenHarmony phones/tablets, these are setting both orientation and rotation, and this works out because most people are launching apps while holding the phone in portrait mode (0 rotation).
    // !!! FIXME: if I'm right, we should decide if this is a phone/tablet screen and just set the natural orientation to portrait and then use this code to calculate current orientation.
    ਜੇ (rotation == DISPLAY_MANAGER_ROTATION_90) {  // rotations are clockwise on OpenHarmony.
        ਸਥਿਰ ਅਚਲ SDL_DisplayOrientation rotated[5] = { SDL_ORIENTATION_UNKNOWN, SDL_ORIENTATION_PORTRAIT, SDL_ORIENTATION_PORTRAIT_FLIPPED, SDL_ORIENTATION_LANDSCAPE_FLIPPED, SDL_ORIENTATION_LANDSCAPE };
        SDL_assert(((ਪੂਰਨ) display->natural_orientation) < SDL_arraysize(rotated));
        display->current_orientation = rotated[(ਪੂਰਨ) display->natural_orientation];
    } ਨਹੀਂਤਾਂ ਜੇ (rotation == DISPLAY_MANAGER_ROTATION_180) {  // rotations are clockwise on OpenHarmony.
        ਸਥਿਰ ਅਚਲ SDL_DisplayOrientation rotated[5] = { SDL_ORIENTATION_UNKNOWN, SDL_ORIENTATION_LANDSCAPE_FLIPPED, SDL_ORIENTATION_LANDSCAPE, SDL_ORIENTATION_PORTRAIT_FLIPPED, SDL_ORIENTATION_PORTRAIT };
        SDL_assert(((ਪੂਰਨ) display->natural_orientation) < SDL_arraysize(rotated));
        display->current_orientation = rotated[(ਪੂਰਨ) display->natural_orientation];
    } ਨਹੀਂਤਾਂ ਜੇ (rotation == DISPLAY_MANAGER_ROTATION_270) {  // rotations are clockwise on OpenHarmony.
        ਸਥਿਰ ਅਚਲ SDL_DisplayOrientation rotated[5] = { SDL_ORIENTATION_UNKNOWN, SDL_ORIENTATION_PORTRAIT_FLIPPED, SDL_ORIENTATION_PORTRAIT, SDL_ORIENTATION_LANDSCAPE, SDL_ORIENTATION_LANDSCAPE_FLIPPED };
        SDL_assert(((ਪੂਰਨ) display->natural_orientation) < SDL_arraysize(rotated));
        display->current_orientation = rotated[(ਪੂਰਨ) display->natural_orientation];
    } ਨਹੀਂਤਾਂ {
        display->current_orientation = display->natural_orientation;
    }

    display->content_scale = ਬਹੁਲਕ.pixel_density;

    // !!! FIXME: look at SDL_OnApplicationDidChangeStatusBarOrientation() and do something similar.


// !!! FIXME
#ਜੇ 0
    OPENHARMONY_InitTouch();
    OPENHARMONY_InitMouse();
#ਜੇ_ਅੰਤ
    OPENHARMONY_InitClipboard(_this);

    // We're done!
    ਵਾਪਸ true;
}

ਖਾਲੀ OPENHARMONY_VideoQuit(SDL_VideoDevice *_this)
{
    OPENHARMONY_QuitClipboard(_this);

// !!! FIXME
#ਜੇ 0
    OPENHARMONY_QuitMouse();
    OPENHARMONY_QuitTouch();
#ਜੇ_ਅੰਤ
}

ਸਥਿਰ ਖਾਲੀ OPENHARMONY_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->ਅੰਦਰੂਨੀ);
    SDL_free(device);
}

ਸਥਿਰ SDL_VideoDevice *OPENHARMONY_CreateDevice(ਖਾਲੀ)
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
    device->system_theme = SDL_GetOpenHarmonySystemTheme();

    // Set the function pointers
    device->VideoInit = OPENHARMONY_VideoInit;
    device->VideoQuit = OPENHARMONY_VideoQuit;

    device->CreateSDLWindow = OPENHARMONY_Create_ਖਿੜਕੀ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Title = OPENHARMONY_ਸੈੱਟ_ਖਿੜਕੀ_Title;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen = OPENHARMONY_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen;
    device->Minimize_ਖਿੜਕੀ = OPENHARMONY_Minimize_ਖਿੜਕੀ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Resizable = OPENHARMONY_ਸੈੱਟ_ਖਿੜਕੀ_Resizable;
    device->Destroy_ਖਿੜਕੀ = OPENHARMONY_Destroy_ਖਿੜਕੀ;

    device->ਮੁਕਤ = OPENHARMONY_DeleteDevice;

    // GL pointers
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
    device->GL_ਲੱਦੋ_Library = OPENHARMONY_GLES_ਲੱਦੋ_Library;
    device->GL_Get_Proc_ਪਤਾ = OPENHARMONY_GLES_Get_Proc_ਪਤਾ;
    device->GL_UnloadLibrary = OPENHARMONY_GLES_UnloadLibrary;
    device->GL_CreateContext = OPENHARMONY_GLES_CreateContext;
    device->GL_MakeCurrent = OPENHARMONY_GLES_MakeCurrent;
    device->GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval = OPENHARMONY_GLES_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval;
    device->GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval = OPENHARMONY_GLES_Get_ਅਦਲਾ_ਬਦਲੀ_Interval;
    device->GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ = OPENHARMONY_GLES_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ;
    device->GL_DestroyContext = OPENHARMONY_GLES_DestroyContext;
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_VULKAN
    device->Vulkan_ਲੱਦੋ_Library = OPENHARMONY_Vulkan_ਲੱਦੋ_Library;
    device->Vulkan_UnloadLibrary = OPENHARMONY_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = OPENHARMONY_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = OPENHARMONY_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = OPENHARMONY_Vulkan_DestroySurface;
#ਜੇ_ਅੰਤ

    // Screensaver
    device->SuspendScreenSaver = OPENHARMONY_SuspendScreenSaver;

    device->PumpEvents = OPENHARMONY_PumpEvents;

    // Screen keyboard
    device->HasScreenKeyboardSupport = OPENHARMONY_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = OPENHARMONY_ShowScreenKeyboard;
    device->HideScreenKeyboard = OPENHARMONY_HideScreenKeyboard;

    // Clipboard
    device->Get_ਪਾਠ_Mime_Types = OPENHARMONY_Get_ਪਾਠ_Mime_Types;
    device->ਸੈੱਟ_Clipboard_ਪਾਠ = OPENHARMONY_ਸੈੱਟ_Clipboard_ਪਾਠ;
    device->Get_Clipboard_ਪਾਠ = OPENHARMONY_Get_Clipboard_ਪਾਠ;
    device->Has_Clipboard_ਪਾਠ = OPENHARMONY_Has_Clipboard_ਪਾਠ;

    device->device_caps = VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS;

    ਵਾਪਸ device;
}

VideoBootStrap OPENHARMONY_bootstrap = {
    OPENHARMONY_VID_DRIVER_NAME, "SDL OpenHarmony/HarmonyOS video driver",
    OPENHARMONY_CreateDevice,
    /*!!! FIXME OPENHARMONY_ShowMessageBox*/ ਨਿਰਾ,
    false
};

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_OPENHARMONY
