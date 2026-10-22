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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_OPENHARMONY

// HarmonyOS/OpenHarmony SDL video driver implementation

#ضمن <window_manager/oh_display_manager.h>

// !!! FIXME: these are defined as "const uint32_t VARNAME = VALUE;" in native_interface_xcomponent.h, which becomes a global variable in _our_ C code! Maybe C++ handles this differently...?
#وصف_ڪريو OH_XCOMPONENT_ID_LEN_MAX sdl_ohosvideo_OH_XCOMPONENT_ID_LEN_MAX
#وصف_ڪريو OH_MAX_TOUCH_POINTS_عدد sdl_ohosvideo_OH_MAX_TOUCH_POINTS_عدد
#ضمن <ace/xcomponent/native_interface_xcomponent.h>

// !!! FIXME: move stuff in from Android code

#ضمن "../SDL_sysvideo.h"
#ضمن "../SDL_pixels_c.h"
#ضمن "../../events/SDL_events_c.h"
#ضمن "../../events/SDL_windowevents_c.h"

#ضمن "SDL_openharmonyvideo.h"
#ضمن "SDL_openharmonyopengl.h"
#ضمن "SDL_openharmonyclipboard.h"
#ضمن "SDL_openharmonyevents.h"
#ضمن "SDL_openharmonykeyboard.h"
#ضمن "SDL_openharmonymouse.h"
//#include "SDL_openharmonytouch.h"
#ضمن "SDL_openharmonywindow.h"
#ضمن "SDL_openharmonyvulkan.h"
//#include "SDL_openharmonymessagebox.h"

#وصف_ڪريو OPENHARMONY_VID_DRIVER_NAME "openharmony"

#ضمن "../SDL_egl_c.h"
#وصف_ڪريو OPENHARMONY_GLES_Get_Proc_پتو  SDL_EGL_Get_Proc_پتو_اندروني
#وصف_ڪريو OPENHARMONY_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#وصف_ڪريو OPENHARMONY_GLES_سيٽ_مٽا_سٽا_Interval SDL_EGL_سيٽ_مٽا_سٽا_Interval
#وصف_ڪريو OPENHARMONY_GLES_Get_مٽا_سٽا_Interval SDL_EGL_Get_مٽا_سٽا_Interval
#وصف_ڪريو OPENHARMONY_GLES_DestroyContext   SDL_EGL_DestroyContext


ساكن OH_NativeXComponent *native_xcomponent = عدم;
ساكن فراغ *native_دري = عدم;

فراغ SDL_Open_Harmony_Get_Native_دري_اشارا(فراغ **xcomponent, فراغ **دري)
{
    *xcomponent = (فراغ *) native_xcomponent;
    *دري = (فراغ *) native_دري;
}

فراغ SDL_OpenHarmonyVideoSurfaceDestroyed(فراغ *component, فراغ *دري)
{
    SDL_assert(native_xcomponent == ((OH_NativeXComponent *) component));  // right now we assume one surface, one window.
    native_xcomponent = عدم;
    native_دري = عدم;
}

فراغ SDL_Open_Harmony_Video_Surface_بدليو(فراغ *component, فراغ *دري)
{
    SDL_assert(native_xcomponent == ((OH_NativeXComponent *) component));  // right now we assume one surface, one window.
    uint64_t w, h;
    OH_Native_XComponent_Get_XComponent_سائيز(native_xcomponent, native_دري, &w, &h);
    SDL_Send_دري_Event(OPENHARMONY_دري, SDL_EVENT_دري_RESIZED, (صحيح) w, (صحيح) h);
}

فراغ SDL_OpenHarmonyVideoSurfaceCreated(فراغ *component, فراغ *دري)
{
    SDL_assert(native_xcomponent == عدم);  // right now we assume one surface, one window.
    native_xcomponent = (OH_NativeXComponent *) component;
    native_دري = دري;
}

ساكن bool OPENHARMONY_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    أرجع SDL_OpenHarmonyChangeScreenSaver(!_this->suspend_screensaver);
}

ساكن bool OPENHARMONY_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *videodata = _this->اندروني;

    videodata->isPaused = false;
    videodata->isPausing = false;

    // !!! FIXME: eventually we'll want to enumerate displays, since you can probably plug in something
    // !!! FIXME:  through a USB-C to HDMI adapter, or maybe there will be separate "outer" screens vs
    // !!! FIXME:  an internal foldable one, but for now let's just get _something_ on _any_ display.
    uint64_t dispid64 = 0;
    إذا (OH_NativeDisplayManager_GetDefaultDisplayId(&dispid64) != DISPLAY_MANAGER_OK) {
        أرجع SDL_سيٽ_Error("Couldn't get default display id");
    }
    ثابت uint32_t dispid = (uint32_t) dispid64;

    NativeDisplayManager_DisplayInfo *dispinfo = عدم;
    إذا (OH_NativeDisplayManager_CreateDisplayById(dispid, &dispinfo) != DISPLAY_MANAGER_OK) {  // (should really be called "CreateDisplayInfo", not "CreateDisplay")
        أرجع SDL_سيٽ_Error("Couldn't get default display info");
    }

    SDL_Display_گهڻائي گهڻائي;
    SDL_zero(گهڻائي);
    گهڻائي.format = SDL_PIXELFORMAT_BGRA8888;  // !!! FIXME
    گهڻائي.w = (صحيح) dispinfo->physical_ويڪر;
    گهڻائي.h = (صحيح) dispinfo->physical_اوچائي;
    گهڻائي.refresh_شرح = (عائم) dispinfo->refresh_شرح_2;
    گهڻائي.pixel_density = 1.0f;

    ثابت NativeDisplayManager_Rotation rotation = dispinfo->rotation;
    ثابت NativeDisplayManager_Orientation orientation = dispinfo->orientation;

    OH_NativeDisplayManager_DestroyDisplay(dispinfo);

    ثابت SDL_DisplayID displayID = SDL_جوڙيو_Basic_Video_Display(&گهڻائي);
    إذا (displayID == 0) {
        أرجع false;
    }

    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    بدل (orientation) {
        حالة DISPLAY_MANAGER_PORTRAIT: display->natural_orientation = SDL_ORIENTATION_PORTRAIT; اكسر;
        حالة DISPLAY_MANAGER_LANDSCAPE: display->natural_orientation = SDL_ORIENTATION_LANDSCAPE; اكسر;
        حالة DISPLAY_MANAGER_PORTRAIT_INVERTED: display->natural_orientation = SDL_ORIENTATION_PORTRAIT_FLIPPED; اكسر;
        حالة DISPLAY_MANAGER_LANDSCAPE_INVERTED: display->natural_orientation = SDL_ORIENTATION_LANDSCAPE_FLIPPED; اكسر;
        افتراضي: display->natural_orientation = SDL_ORIENTATION_UNKNOWN; اكسر;
    }

    // !!! FIXME: this is probably wrong, I think on OpenHarmony phones/tablets, these are setting both orientation and rotation, and this works out because most people are launching apps while holding the phone in portrait mode (0 rotation).
    // !!! FIXME: if I'm right, we should decide if this is a phone/tablet screen and just set the natural orientation to portrait and then use this code to calculate current orientation.
    إذا (rotation == DISPLAY_MANAGER_ROTATION_90) {  // rotations are clockwise on OpenHarmony.
        ساكن ثابت SDL_DisplayOrientation rotated[5] = { SDL_ORIENTATION_UNKNOWN, SDL_ORIENTATION_PORTRAIT, SDL_ORIENTATION_PORTRAIT_FLIPPED, SDL_ORIENTATION_LANDSCAPE_FLIPPED, SDL_ORIENTATION_LANDSCAPE };
        SDL_assert(((صحيح) display->natural_orientation) < SDL_arraysize(rotated));
        display->current_orientation = rotated[(صحيح) display->natural_orientation];
    } وإلا إذا (rotation == DISPLAY_MANAGER_ROTATION_180) {  // rotations are clockwise on OpenHarmony.
        ساكن ثابت SDL_DisplayOrientation rotated[5] = { SDL_ORIENTATION_UNKNOWN, SDL_ORIENTATION_LANDSCAPE_FLIPPED, SDL_ORIENTATION_LANDSCAPE, SDL_ORIENTATION_PORTRAIT_FLIPPED, SDL_ORIENTATION_PORTRAIT };
        SDL_assert(((صحيح) display->natural_orientation) < SDL_arraysize(rotated));
        display->current_orientation = rotated[(صحيح) display->natural_orientation];
    } وإلا إذا (rotation == DISPLAY_MANAGER_ROTATION_270) {  // rotations are clockwise on OpenHarmony.
        ساكن ثابت SDL_DisplayOrientation rotated[5] = { SDL_ORIENTATION_UNKNOWN, SDL_ORIENTATION_PORTRAIT_FLIPPED, SDL_ORIENTATION_PORTRAIT, SDL_ORIENTATION_LANDSCAPE, SDL_ORIENTATION_LANDSCAPE_FLIPPED };
        SDL_assert(((صحيح) display->natural_orientation) < SDL_arraysize(rotated));
        display->current_orientation = rotated[(صحيح) display->natural_orientation];
    } وإلا {
        display->current_orientation = display->natural_orientation;
    }

    display->content_scale = گهڻائي.pixel_density;

    // !!! FIXME: look at SDL_OnApplicationDidChangeStatusBarOrientation() and do something similar.


// !!! FIXME
#إذا 0
    OPENHARMONY_InitTouch();
    OPENHARMONY_InitMouse();
#جيڪڏهن_پورو
    OPENHARMONY_InitClipboard(_this);

    // We're done!
    أرجع true;
}

فراغ OPENHARMONY_VideoQuit(SDL_VideoDevice *_this)
{
    OPENHARMONY_QuitClipboard(_this);

// !!! FIXME
#إذا 0
    OPENHARMONY_QuitMouse();
    OPENHARMONY_QuitTouch();
#جيڪڏهن_پورو
}

ساكن فراغ OPENHARMONY_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->اندروني);
    SDL_free(device);
}

ساكن SDL_VideoDevice *OPENHARMONY_CreateDevice(فراغ)
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

    device->اندروني = معلومات;
    device->system_theme = SDL_GetOpenHarmonySystemTheme();

    // Set the function pointers
    device->VideoInit = OPENHARMONY_VideoInit;
    device->VideoQuit = OPENHARMONY_VideoQuit;

    device->CreateSDLWindow = OPENHARMONY_Create_دري;
    device->سيٽ_دري_Title = OPENHARMONY_سيٽ_دري_Title;
    device->سيٽ_دري_Fullscreen = OPENHARMONY_سيٽ_دري_Fullscreen;
    device->Minimize_دري = OPENHARMONY_Minimize_دري;
    device->سيٽ_دري_Resizable = OPENHARMONY_سيٽ_دري_Resizable;
    device->Destroy_دري = OPENHARMONY_Destroy_دري;

    device->حرر = OPENHARMONY_DeleteDevice;

    // GL pointers
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
    device->GL_ڀريو_Library = OPENHARMONY_GLES_ڀريو_Library;
    device->GL_Get_Proc_پتو = OPENHARMONY_GLES_Get_Proc_پتو;
    device->GL_UnloadLibrary = OPENHARMONY_GLES_UnloadLibrary;
    device->GL_CreateContext = OPENHARMONY_GLES_CreateContext;
    device->GL_MakeCurrent = OPENHARMONY_GLES_MakeCurrent;
    device->GL_سيٽ_مٽا_سٽا_Interval = OPENHARMONY_GLES_سيٽ_مٽا_سٽا_Interval;
    device->GL_Get_مٽا_سٽا_Interval = OPENHARMONY_GLES_Get_مٽا_سٽا_Interval;
    device->GL_مٽا_سٽا_دري = OPENHARMONY_GLES_مٽا_سٽا_دري;
    device->GL_DestroyContext = OPENHARMONY_GLES_DestroyContext;
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_VULKAN
    device->Vulkan_ڀريو_Library = OPENHARMONY_Vulkan_ڀريو_Library;
    device->Vulkan_UnloadLibrary = OPENHARMONY_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = OPENHARMONY_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = OPENHARMONY_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = OPENHARMONY_Vulkan_DestroySurface;
#جيڪڏهن_پورو

    // Screensaver
    device->SuspendScreenSaver = OPENHARMONY_SuspendScreenSaver;

    device->PumpEvents = OPENHARMONY_PumpEvents;

    // Screen keyboard
    device->HasScreenKeyboardSupport = OPENHARMONY_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = OPENHARMONY_ShowScreenKeyboard;
    device->HideScreenKeyboard = OPENHARMONY_HideScreenKeyboard;

    // Clipboard
    device->Get_متن_Mime_Types = OPENHARMONY_Get_متن_Mime_Types;
    device->سيٽ_Clipboard_متن = OPENHARMONY_سيٽ_Clipboard_متن;
    device->Get_Clipboard_متن = OPENHARMONY_Get_Clipboard_متن;
    device->Has_Clipboard_متن = OPENHARMONY_Has_Clipboard_متن;

    device->device_caps = VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS;

    أرجع device;
}

VideoBootStrap OPENHARMONY_bootstrap = {
    OPENHARMONY_VID_DRIVER_NAME, "SDL OpenHarmony/HarmonyOS video driver",
    OPENHARMONY_CreateDevice,
    /*!!! FIXME OPENHARMONY_ShowMessageBox*/ عدم,
    false
};

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_OPENHARMONY
