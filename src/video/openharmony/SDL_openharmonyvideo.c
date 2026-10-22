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
#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_OPENHARMONY

// HarmonyOS/OpenHarmony SDL video driver implementation

#অন্তর্ভাব <window_manager/oh_display_manager.h>

// !!! FIXME: these are defined as "const uint32_t VARNAME = VALUE;" in native_interface_xcomponent.h, which becomes a global variable in _our_ C code! Maybe C++ handles this differently...?
#define OH_XCOMPONENT_ID_LEN_MAX sdl_ohosvideo_OH_XCOMPONENT_ID_LEN_MAX
#define OH_MAX_TOUCH_POINTS_সংখ্যা sdl_ohosvideo_OH_MAX_TOUCH_POINTS_সংখ্যা
#অন্তর্ভাব <ace/xcomponent/native_interface_xcomponent.h>

// !!! FIXME: move stuff in from Android code

#অন্তর্ভাব "../SDL_sysvideo.h"
#অন্তর্ভাব "../SDL_pixels_c.h"
#অন্তর্ভাব "../../events/SDL_events_c.h"
#অন্তর্ভাব "../../events/SDL_windowevents_c.h"

#অন্তর্ভাব "SDL_openharmonyvideo.h"
#অন্তর্ভাব "SDL_openharmonyopengl.h"
#অন্তর্ভাব "SDL_openharmonyclipboard.h"
#অন্তর্ভাব "SDL_openharmonyevents.h"
#অন্তর্ভাব "SDL_openharmonykeyboard.h"
#অন্তর্ভাব "SDL_openharmonymouse.h"
//#include "SDL_openharmonytouch.h"
#অন্তর্ভাব "SDL_openharmonywindow.h"
#অন্তর্ভাব "SDL_openharmonyvulkan.h"
//#include "SDL_openharmonymessagebox.h"

#define OPENHARMONY_VID_DRIVER_NAME "openharmony"

#অন্তর্ভাব "../SDL_egl_c.h"
#define OPENHARMONY_GLES_GetProcAddress  SDL_EGL_GetProcAddressInternal
#define OPENHARMONY_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#define OPENHARMONY_GLES_SetSwapInterval SDL_EGL_SetSwapInterval
#define OPENHARMONY_GLES_GetSwapInterval SDL_EGL_GetSwapInterval
#define OPENHARMONY_GLES_DestroyContext   SDL_EGL_DestroyContext


স্থির OH_NativeXComponent *native_xcomponent = ফাঁকা;
স্থির শূন্য *native_window = ফাঁকা;

শূন্য SDL_OpenHarmonyGetNativeWindowPointers(শূন্য **xcomponent, শূন্য **window)
{
    *xcomponent = (শূন্য *) native_xcomponent;
    *window = (শূন্য *) native_window;
}

শূন্য SDL_OpenHarmonyVideoSurfaceDestroyed(শূন্য *component, শূন্য *window)
{
    SDL_assert(native_xcomponent == ((OH_NativeXComponent *) component));  // right now we assume one surface, one window.
    native_xcomponent = ফাঁকা;
    native_window = ফাঁকা;
}

শূন্য SDL_OpenHarmonyVideoSurfaceChanged(শূন্য *component, শূন্য *window)
{
    SDL_assert(native_xcomponent == ((OH_NativeXComponent *) component));  // right now we assume one surface, one window.
    uint64_t w, h;
    OH_Native_XComponent_Get_XComponent_আকার(native_xcomponent, native_window, &w, &h);
    SDL_SendWindowEvent(OPENHARMONY_Window, SDL_EVENT_WINDOW_RESIZED, (পূর্ণসংখ্যা) w, (পূর্ণসংখ্যা) h);
}

শূন্য SDL_OpenHarmonyVideoSurfaceCreated(শূন্য *component, শূন্য *window)
{
    SDL_assert(native_xcomponent == ফাঁকা);  // right now we assume one surface, one window.
    native_xcomponent = (OH_NativeXComponent *) component;
    native_window = window;
}

স্থির bool OPENHARMONY_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    ফেরত SDL_OpenHarmonyChangeScreenSaver(!_this->suspend_screensaver);
}

স্থির bool OPENHARMONY_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_তথ্য *videodata = _this->internal;

    videodata->isPaused = false;
    videodata->isPausing = false;

    // !!! FIXME: eventually we'll want to enumerate displays, since you can probably plug in something
    // !!! FIXME:  through a USB-C to HDMI adapter, or maybe there will be separate "outer" screens vs
    // !!! FIXME:  an internal foldable one, but for now let's just get _something_ on _any_ display.
    uint64_t dispid64 = 0;
    যদি (OH_NativeDisplayManager_GetDefaultDisplayId(&dispid64) != DISPLAY_MANAGER_OK) {
        ফেরত SDL_SetError("Couldn't get default display id");
    }
    ধ্রুবক uint32_t dispid = (uint32_t) dispid64;

    NativeDisplayManager_DisplayInfo *dispinfo = ফাঁকা;
    যদি (OH_NativeDisplayManager_CreateDisplayById(dispid, &dispinfo) != DISPLAY_MANAGER_OK) {  // (should really be called "CreateDisplayInfo", not "CreateDisplay")
        ফেরত SDL_SetError("Couldn't get default display info");
    }

    SDL_DisplayMode mode;
    SDL_zero(mode);
    mode.format = SDL_PIXELFORMAT_BGRA8888;  // !!! FIXME
    mode.w = (পূর্ণসংখ্যা) dispinfo->physicalWidth;
    mode.h = (পূর্ণসংখ্যা) dispinfo->physicalHeight;
    mode.refresh_rate = (দশমিক) dispinfo->refreshRate;
    mode.pixel_density = 1.0f;

    ধ্রুবক NativeDisplayManager_Rotation rotation = dispinfo->rotation;
    ধ্রুবক NativeDisplayManager_Orientation orientation = dispinfo->orientation;

    OH_NativeDisplayManager_DestroyDisplay(dispinfo);

    ধ্রুবক SDL_DisplayID displayID = SDL_AddBasicVideoDisplay(&mode);
    যদি (displayID == 0) {
        ফেরত false;
    }

    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    নির্বাচন (orientation) {
        ক্ষেত্র DISPLAY_MANAGER_PORTRAIT: display->natural_orientation = SDL_ORIENTATION_PORTRAIT; বিরতি;
        ক্ষেত্র DISPLAY_MANAGER_LANDSCAPE: display->natural_orientation = SDL_ORIENTATION_LANDSCAPE; বিরতি;
        ক্ষেত্র DISPLAY_MANAGER_PORTRAIT_INVERTED: display->natural_orientation = SDL_ORIENTATION_PORTRAIT_FLIPPED; বিরতি;
        ক্ষেত্র DISPLAY_MANAGER_LANDSCAPE_INVERTED: display->natural_orientation = SDL_ORIENTATION_LANDSCAPE_FLIPPED; বিরতি;
        পূর্বনির্ধারিত: display->natural_orientation = SDL_ORIENTATION_UNKNOWN; বিরতি;
    }

    // !!! FIXME: this is probably wrong, I think on OpenHarmony phones/tablets, these are setting both orientation and rotation, and this works out because most people are launching apps while holding the phone in portrait mode (0 rotation).
    // !!! FIXME: if I'm right, we should decide if this is a phone/tablet screen and just set the natural orientation to portrait and then use this code to calculate current orientation.
    যদি (rotation == DISPLAY_MANAGER_ROTATION_90) {  // rotations are clockwise on OpenHarmony.
        স্থির ধ্রুবক SDL_DisplayOrientation rotated[5] = { SDL_ORIENTATION_UNKNOWN, SDL_ORIENTATION_PORTRAIT, SDL_ORIENTATION_PORTRAIT_FLIPPED, SDL_ORIENTATION_LANDSCAPE_FLIPPED, SDL_ORIENTATION_LANDSCAPE };
        SDL_assert(((পূর্ণসংখ্যা) display->natural_orientation) < SDL_arraysize(rotated));
        display->current_orientation = rotated[(পূর্ণসংখ্যা) display->natural_orientation];
    } অন্যথা যদি (rotation == DISPLAY_MANAGER_ROTATION_180) {  // rotations are clockwise on OpenHarmony.
        স্থির ধ্রুবক SDL_DisplayOrientation rotated[5] = { SDL_ORIENTATION_UNKNOWN, SDL_ORIENTATION_LANDSCAPE_FLIPPED, SDL_ORIENTATION_LANDSCAPE, SDL_ORIENTATION_PORTRAIT_FLIPPED, SDL_ORIENTATION_PORTRAIT };
        SDL_assert(((পূর্ণসংখ্যা) display->natural_orientation) < SDL_arraysize(rotated));
        display->current_orientation = rotated[(পূর্ণসংখ্যা) display->natural_orientation];
    } অন্যথা যদি (rotation == DISPLAY_MANAGER_ROTATION_270) {  // rotations are clockwise on OpenHarmony.
        স্থির ধ্রুবক SDL_DisplayOrientation rotated[5] = { SDL_ORIENTATION_UNKNOWN, SDL_ORIENTATION_PORTRAIT_FLIPPED, SDL_ORIENTATION_PORTRAIT, SDL_ORIENTATION_LANDSCAPE, SDL_ORIENTATION_LANDSCAPE_FLIPPED };
        SDL_assert(((পূর্ণসংখ্যা) display->natural_orientation) < SDL_arraysize(rotated));
        display->current_orientation = rotated[(পূর্ণসংখ্যা) display->natural_orientation];
    } অন্যথা {
        display->current_orientation = display->natural_orientation;
    }

    display->content_scale = mode.pixel_density;

    // !!! FIXME: look at SDL_OnApplicationDidChangeStatusBarOrientation() and do something similar.


// !!! FIXME
#যদি 0
    OPENHARMONY_InitTouch();
    OPENHARMONY_InitMouse();
#endif
    OPENHARMONY_InitClipboard(_this);

    // We're done!
    ফেরত true;
}

শূন্য OPENHARMONY_VideoQuit(SDL_VideoDevice *_this)
{
    OPENHARMONY_QuitClipboard(_this);

// !!! FIXME
#যদি 0
    OPENHARMONY_QuitMouse();
    OPENHARMONY_QuitTouch();
#endif
}

স্থির শূন্য OPENHARMONY_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

স্থির SDL_VideoDevice *OPENHARMONY_CreateDevice(শূন্য)
{
    SDL_VideoDevice *device;
    SDL_Video_তথ্য *তথ্য;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, আকার(SDL_VideoDevice));
    যদি (!device) {
        ফেরত ফাঁকা;
    }

    তথ্য = (SDL_Video_তথ্য *)SDL_calloc(1, আকার(SDL_Video_তথ্য));
    যদি (!তথ্য) {
        SDL_free(device);
        ফেরত ফাঁকা;
    }

    device->internal = তথ্য;
    device->system_theme = SDL_GetOpenHarmonySystemTheme();

    // Set the function pointers
    device->VideoInit = OPENHARMONY_VideoInit;
    device->VideoQuit = OPENHARMONY_VideoQuit;

    device->CreateSDLWindow = OPENHARMONY_CreateWindow;
    device->SetWindowTitle = OPENHARMONY_SetWindowTitle;
    device->SetWindowFullscreen = OPENHARMONY_SetWindowFullscreen;
    device->MinimizeWindow = OPENHARMONY_MinimizeWindow;
    device->SetWindowResizable = OPENHARMONY_SetWindowResizable;
    device->DestroyWindow = OPENHARMONY_DestroyWindow;

    device->মুক্ত = OPENHARMONY_DeleteDevice;

    // GL pointers
#ifdef SDL_VIDEO_OPENGL_EGL
    device->GL_LoadLibrary = OPENHARMONY_GLES_LoadLibrary;
    device->GL_GetProcAddress = OPENHARMONY_GLES_GetProcAddress;
    device->GL_UnloadLibrary = OPENHARMONY_GLES_UnloadLibrary;
    device->GL_CreateContext = OPENHARMONY_GLES_CreateContext;
    device->GL_MakeCurrent = OPENHARMONY_GLES_MakeCurrent;
    device->GL_SetSwapInterval = OPENHARMONY_GLES_SetSwapInterval;
    device->GL_GetSwapInterval = OPENHARMONY_GLES_GetSwapInterval;
    device->GL_SwapWindow = OPENHARMONY_GLES_SwapWindow;
    device->GL_DestroyContext = OPENHARMONY_GLES_DestroyContext;
#endif

#ifdef SDL_VIDEO_VULKAN
    device->Vulkan_LoadLibrary = OPENHARMONY_Vulkan_LoadLibrary;
    device->Vulkan_UnloadLibrary = OPENHARMONY_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = OPENHARMONY_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = OPENHARMONY_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = OPENHARMONY_Vulkan_DestroySurface;
#endif

    // Screensaver
    device->SuspendScreenSaver = OPENHARMONY_SuspendScreenSaver;

    device->PumpEvents = OPENHARMONY_PumpEvents;

    // Screen keyboard
    device->HasScreenKeyboardSupport = OPENHARMONY_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = OPENHARMONY_ShowScreenKeyboard;
    device->HideScreenKeyboard = OPENHARMONY_HideScreenKeyboard;

    // Clipboard
    device->GetTextMimeTypes = OPENHARMONY_GetTextMimeTypes;
    device->SetClipboardText = OPENHARMONY_SetClipboardText;
    device->GetClipboardText = OPENHARMONY_GetClipboardText;
    device->HasClipboardText = OPENHARMONY_HasClipboardText;

    device->device_caps = VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS;

    ফেরত device;
}

VideoBootStrap OPENHARMONY_bootstrap = {
    OPENHARMONY_VID_DRIVER_NAME, "SDL OpenHarmony/HarmonyOS video driver",
    OPENHARMONY_CreateDevice,
    /*!!! FIXME OPENHARMONY_ShowMessageBox*/ ফাঁকা,
    false
};

#endif // SDL_VIDEO_DRIVER_OPENHARMONY
