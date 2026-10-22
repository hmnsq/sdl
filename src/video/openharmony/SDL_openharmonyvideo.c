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

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_OPENHARMONY

// HarmonyOS/OpenHarmony SDL video driver implementation

#شامل <window_manager/oh_display_manager.h>

// !!! FIXME: these are defined as "const uint32_t VARNAME = VALUE;" in native_interface_xcomponent.h, which becomes a global variable in _our_ C code! Maybe C++ handles this differently...?
#تعریف_کرو OH_XCOMPONENT_ID_LEN_MAX sdl_ohosvideo_OH_XCOMPONENT_ID_LEN_MAX
#تعریف_کرو OH_MAX_TOUCH_POINTS_نمبر sdl_ohosvideo_OH_MAX_TOUCH_POINTS_نمبر
#شامل <ace/xcomponent/native_interface_xcomponent.h>

// !!! FIXME: move stuff in from Android code

#شامل "../SDL_sysvideo.h"
#شامل "../SDL_pixels_c.h"
#شامل "../../events/SDL_events_c.h"
#شامل "../../events/SDL_windowevents_c.h"

#شامل "SDL_openharmonyvideo.h"
#شامل "SDL_openharmonyopengl.h"
#شامل "SDL_openharmonyclipboard.h"
#شامل "SDL_openharmonyevents.h"
#شامل "SDL_openharmonykeyboard.h"
#شامل "SDL_openharmonymouse.h"
//#include "SDL_openharmonytouch.h"
#شامل "SDL_openharmonywindow.h"
#شامل "SDL_openharmonyvulkan.h"
//#include "SDL_openharmonymessagebox.h"

#تعریف_کرو OPENHARMONY_VID_DRIVER_NAME "openharmony"

#شامل "../SDL_egl_c.h"
#تعریف_کرو OPENHARMONY_GLES_Get_Proc_پتہ  SDL_EGL_Get_Proc_پتہ_اندرونی
#تعریف_کرو OPENHARMONY_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#تعریف_کرو OPENHARMONY_GLES_سیٹ_تبادلہ_Interval SDL_EGL_سیٹ_تبادلہ_Interval
#تعریف_کرو OPENHARMONY_GLES_Get_تبادلہ_Interval SDL_EGL_Get_تبادلہ_Interval
#تعریف_کرو OPENHARMONY_GLES_DestroyContext   SDL_EGL_DestroyContext


ساکن OH_NativeXComponent *native_xcomponent = تہی;
ساکن خالی *native_کھڑکی = تہی;

خالی SDL_Open_Harmony_Get_Native_کھڑکی_اشارے(خالی **xcomponent, خالی **کھڑکی)
{
    *xcomponent = (خالی *) native_xcomponent;
    *کھڑکی = (خالی *) native_کھڑکی;
}

خالی SDL_OpenHarmonyVideoSurfaceDestroyed(خالی *component, خالی *کھڑکی)
{
    SDL_assert(native_xcomponent == ((OH_NativeXComponent *) component));  // right now we assume one surface, one window.
    native_xcomponent = تہی;
    native_کھڑکی = تہی;
}

خالی SDL_Open_Harmony_Video_Surface_بدلا(خالی *component, خالی *کھڑکی)
{
    SDL_assert(native_xcomponent == ((OH_NativeXComponent *) component));  // right now we assume one surface, one window.
    uint64_t w, h;
    OH_Native_XComponent_Get_XComponent_سائز(native_xcomponent, native_کھڑکی, &w, &h);
    SDL_Send_کھڑکی_Event(OPENHARMONY_کھڑکی, SDL_EVENT_کھڑکی_RESIZED, (صحیح) w, (صحیح) h);
}

خالی SDL_OpenHarmonyVideoSurfaceCreated(خالی *component, خالی *کھڑکی)
{
    SDL_assert(native_xcomponent == تہی);  // right now we assume one surface, one window.
    native_xcomponent = (OH_NativeXComponent *) component;
    native_کھڑکی = کھڑکی;
}

ساکن bool OPENHARMONY_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    واپس SDL_OpenHarmonyChangeScreenSaver(!_this->suspend_screensaver);
}

ساکن bool OPENHARMONY_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;

    videodata->isPaused = false;
    videodata->isPausing = false;

    // !!! FIXME: eventually we'll want to enumerate displays, since you can probably plug in something
    // !!! FIXME:  through a USB-C to HDMI adapter, or maybe there will be separate "outer" screens vs
    // !!! FIXME:  an internal foldable one, but for now let's just get _something_ on _any_ display.
    uint64_t dispid64 = 0;
    اگر (OH_NativeDisplayManager_GetDefaultDisplayId(&dispid64) != DISPLAY_MANAGER_OK) {
        واپس SDL_سیٹ_Error("Couldn't get default display id");
    }
    ثابت uint32_t dispid = (uint32_t) dispid64;

    NativeDisplayManager_DisplayInfo *dispinfo = تہی;
    اگر (OH_NativeDisplayManager_CreateDisplayById(dispid, &dispinfo) != DISPLAY_MANAGER_OK) {  // (should really be called "CreateDisplayInfo", not "CreateDisplay")
        واپس SDL_سیٹ_Error("Couldn't get default display info");
    }

    SDL_Display_منوال منوال;
    SDL_zero(منوال);
    منوال.format = SDL_PIXELFORMAT_BGRA8888;  // !!! FIXME
    منوال.w = (صحیح) dispinfo->physical_چوڑائی;
    منوال.h = (صحیح) dispinfo->physical_اونچائی;
    منوال.refresh_شرح = (اعشاری) dispinfo->refresh_شرح_2;
    منوال.pixel_density = 1.0f;

    ثابت NativeDisplayManager_Rotation rotation = dispinfo->rotation;
    ثابت NativeDisplayManager_Orientation orientation = dispinfo->orientation;

    OH_NativeDisplayManager_DestroyDisplay(dispinfo);

    ثابت SDL_DisplayID displayID = SDL_جوڑو_Basic_Video_Display(&منوال);
    اگر (displayID == 0) {
        واپس false;
    }

    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    انتخاب (orientation) {
        حالت DISPLAY_MANAGER_PORTRAIT: display->natural_orientation = SDL_ORIENTATION_PORTRAIT; توڑو;
        حالت DISPLAY_MANAGER_LANDSCAPE: display->natural_orientation = SDL_ORIENTATION_LANDSCAPE; توڑو;
        حالت DISPLAY_MANAGER_PORTRAIT_INVERTED: display->natural_orientation = SDL_ORIENTATION_PORTRAIT_FLIPPED; توڑو;
        حالت DISPLAY_MANAGER_LANDSCAPE_INVERTED: display->natural_orientation = SDL_ORIENTATION_LANDSCAPE_FLIPPED; توڑو;
        طےشدہ: display->natural_orientation = SDL_ORIENTATION_UNKNOWN; توڑو;
    }

    // !!! FIXME: this is probably wrong, I think on OpenHarmony phones/tablets, these are setting both orientation and rotation, and this works out because most people are launching apps while holding the phone in portrait mode (0 rotation).
    // !!! FIXME: if I'm right, we should decide if this is a phone/tablet screen and just set the natural orientation to portrait and then use this code to calculate current orientation.
    اگر (rotation == DISPLAY_MANAGER_ROTATION_90) {  // rotations are clockwise on OpenHarmony.
        ساکن ثابت SDL_DisplayOrientation rotated[5] = { SDL_ORIENTATION_UNKNOWN, SDL_ORIENTATION_PORTRAIT, SDL_ORIENTATION_PORTRAIT_FLIPPED, SDL_ORIENTATION_LANDSCAPE_FLIPPED, SDL_ORIENTATION_LANDSCAPE };
        SDL_assert(((صحیح) display->natural_orientation) < SDL_arraysize(rotated));
        display->current_orientation = rotated[(صحیح) display->natural_orientation];
    } ورنہ اگر (rotation == DISPLAY_MANAGER_ROTATION_180) {  // rotations are clockwise on OpenHarmony.
        ساکن ثابت SDL_DisplayOrientation rotated[5] = { SDL_ORIENTATION_UNKNOWN, SDL_ORIENTATION_LANDSCAPE_FLIPPED, SDL_ORIENTATION_LANDSCAPE, SDL_ORIENTATION_PORTRAIT_FLIPPED, SDL_ORIENTATION_PORTRAIT };
        SDL_assert(((صحیح) display->natural_orientation) < SDL_arraysize(rotated));
        display->current_orientation = rotated[(صحیح) display->natural_orientation];
    } ورنہ اگر (rotation == DISPLAY_MANAGER_ROTATION_270) {  // rotations are clockwise on OpenHarmony.
        ساکن ثابت SDL_DisplayOrientation rotated[5] = { SDL_ORIENTATION_UNKNOWN, SDL_ORIENTATION_PORTRAIT_FLIPPED, SDL_ORIENTATION_PORTRAIT, SDL_ORIENTATION_LANDSCAPE, SDL_ORIENTATION_LANDSCAPE_FLIPPED };
        SDL_assert(((صحیح) display->natural_orientation) < SDL_arraysize(rotated));
        display->current_orientation = rotated[(صحیح) display->natural_orientation];
    } ورنہ {
        display->current_orientation = display->natural_orientation;
    }

    display->content_scale = منوال.pixel_density;

    // !!! FIXME: look at SDL_OnApplicationDidChangeStatusBarOrientation() and do something similar.


// !!! FIXME
#اگر 0
    OPENHARMONY_InitTouch();
    OPENHARMONY_InitMouse();
#اگر_ختم
    OPENHARMONY_InitClipboard(_this);

    // We're done!
    واپس true;
}

خالی OPENHARMONY_VideoQuit(SDL_VideoDevice *_this)
{
    OPENHARMONY_QuitClipboard(_this);

// !!! FIXME
#اگر 0
    OPENHARMONY_QuitMouse();
    OPENHARMONY_QuitTouch();
#اگر_ختم
}

ساکن خالی OPENHARMONY_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->اندرونی_2);
    SDL_free(device);
}

ساکن SDL_VideoDevice *OPENHARMONY_CreateDevice(خالی)
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
    device->system_theme = SDL_GetOpenHarmonySystemTheme();

    // Set the function pointers
    device->VideoInit = OPENHARMONY_VideoInit;
    device->VideoQuit = OPENHARMONY_VideoQuit;

    device->CreateSDLWindow = OPENHARMONY_Create_کھڑکی;
    device->سیٹ_کھڑکی_Title = OPENHARMONY_سیٹ_کھڑکی_Title;
    device->سیٹ_کھڑکی_Fullscreen = OPENHARMONY_سیٹ_کھڑکی_Fullscreen;
    device->Minimize_کھڑکی = OPENHARMONY_Minimize_کھڑکی;
    device->سیٹ_کھڑکی_Resizable = OPENHARMONY_سیٹ_کھڑکی_Resizable;
    device->Destroy_کھڑکی = OPENHARMONY_Destroy_کھڑکی;

    device->آزاد = OPENHARMONY_DeleteDevice;

    // GL pointers
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    device->GL_بھرو_Library = OPENHARMONY_GLES_بھرو_Library;
    device->GL_Get_Proc_پتہ = OPENHARMONY_GLES_Get_Proc_پتہ;
    device->GL_UnloadLibrary = OPENHARMONY_GLES_UnloadLibrary;
    device->GL_CreateContext = OPENHARMONY_GLES_CreateContext;
    device->GL_MakeCurrent = OPENHARMONY_GLES_MakeCurrent;
    device->GL_سیٹ_تبادلہ_Interval = OPENHARMONY_GLES_سیٹ_تبادلہ_Interval;
    device->GL_Get_تبادلہ_Interval = OPENHARMONY_GLES_Get_تبادلہ_Interval;
    device->GL_تبادلہ_کھڑکی = OPENHARMONY_GLES_تبادلہ_کھڑکی;
    device->GL_DestroyContext = OPENHARMONY_GLES_DestroyContext;
#اگر_ختم

#اگر_تعریف_شدہ SDL_VIDEO_VULKAN
    device->Vulkan_بھرو_Library = OPENHARMONY_Vulkan_بھرو_Library;
    device->Vulkan_UnloadLibrary = OPENHARMONY_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = OPENHARMONY_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = OPENHARMONY_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = OPENHARMONY_Vulkan_DestroySurface;
#اگر_ختم

    // Screensaver
    device->SuspendScreenSaver = OPENHARMONY_SuspendScreenSaver;

    device->PumpEvents = OPENHARMONY_PumpEvents;

    // Screen keyboard
    device->HasScreenKeyboardSupport = OPENHARMONY_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = OPENHARMONY_ShowScreenKeyboard;
    device->HideScreenKeyboard = OPENHARMONY_HideScreenKeyboard;

    // Clipboard
    device->Get_متن_Mime_Types = OPENHARMONY_Get_متن_Mime_Types;
    device->سیٹ_Clipboard_متن = OPENHARMONY_سیٹ_Clipboard_متن;
    device->Get_Clipboard_متن = OPENHARMONY_Get_Clipboard_متن;
    device->Has_Clipboard_متن = OPENHARMONY_Has_Clipboard_متن;

    device->device_caps = VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS;

    واپس device;
}

VideoBootStrap OPENHARMONY_bootstrap = {
    OPENHARMONY_VID_DRIVER_NAME, "SDL OpenHarmony/HarmonyOS video driver",
    OPENHARMONY_CreateDevice,
    /*!!! FIXME OPENHARMONY_ShowMessageBox*/ تہی,
    false
};

#اگر_ختم // SDL_VIDEO_DRIVER_OPENHARMONY
