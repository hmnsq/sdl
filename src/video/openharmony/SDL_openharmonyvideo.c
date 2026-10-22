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

#ifdef SDL_VIDEO_DRIVER_OPENHARMONY

// HarmonyOS/OpenHarmony SDL video driver implementation

#അന്തര്ഭാവ <window_manager/oh_display_manager.h>

// !!! FIXME: these are defined as "const uint32_t VARNAME = VALUE;" in native_interface_xcomponent.h, which becomes a global variable in _our_ C code! Maybe C++ handles this differently...?
#define OH_XCOMPONENT_ID_LEN_MAX sdl_ohosvideo_OH_XCOMPONENT_ID_LEN_MAX
#define OH_MAX_TOUCH_POINTS_സംഖ്യ sdl_ohosvideo_OH_MAX_TOUCH_POINTS_സംഖ്യ
#അന്തര്ഭാവ <ace/xcomponent/native_interface_xcomponent.h>

// !!! FIXME: move stuff in from Android code

#അന്തര്ഭാവ "../SDL_sysvideo.h"
#അന്തര്ഭാവ "../SDL_pixels_c.h"
#അന്തര്ഭാവ "../../events/SDL_events_c.h"
#അന്തര്ഭാവ "../../events/SDL_windowevents_c.h"

#അന്തര്ഭാവ "SDL_openharmonyvideo.h"
#അന്തര്ഭാവ "SDL_openharmonyopengl.h"
#അന്തര്ഭാവ "SDL_openharmonyclipboard.h"
#അന്തര്ഭാവ "SDL_openharmonyevents.h"
#അന്തര്ഭാവ "SDL_openharmonykeyboard.h"
#അന്തര്ഭാവ "SDL_openharmonymouse.h"
//#include "SDL_openharmonytouch.h"
#അന്തര്ഭാവ "SDL_openharmonywindow.h"
#അന്തര്ഭാവ "SDL_openharmonyvulkan.h"
//#include "SDL_openharmonymessagebox.h"

#define OPENHARMONY_VID_DRIVER_NAME "openharmony"

#അന്തര്ഭാവ "../SDL_egl_c.h"
#define OPENHARMONY_GLES_GetProcAddress  SDL_EGL_GetProcAddressInternal
#define OPENHARMONY_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#define OPENHARMONY_GLES_SetSwapInterval SDL_EGL_SetSwapInterval
#define OPENHARMONY_GLES_GetSwapInterval SDL_EGL_GetSwapInterval
#define OPENHARMONY_GLES_DestroyContext   SDL_EGL_DestroyContext


സ്ഥിതം OH_NativeXComponent *native_xcomponent = ശൂന്യ;
സ്ഥിതം ശൂന്യം *native_window = ശൂന്യ;

ശൂന്യം SDL_OpenHarmonyGetNativeWindowPointers(ശൂന്യം **xcomponent, ശൂന്യം **window)
{
    *xcomponent = (ശൂന്യം *) native_xcomponent;
    *window = (ശൂന്യം *) native_window;
}

ശൂന്യം SDL_OpenHarmonyVideoSurfaceDestroyed(ശൂന്യം *component, ശൂന്യം *window)
{
    SDL_assert(native_xcomponent == ((OH_NativeXComponent *) component));  // right now we assume one surface, one window.
    native_xcomponent = ശൂന്യ;
    native_window = ശൂന്യ;
}

ശൂന്യം SDL_OpenHarmonyVideoSurfaceChanged(ശൂന്യം *component, ശൂന്യം *window)
{
    SDL_assert(native_xcomponent == ((OH_NativeXComponent *) component));  // right now we assume one surface, one window.
    uint64_t w, h;
    OH_NativeXComponent_GetXComponentSize(native_xcomponent, native_window, &w, &h);
    SDL_SendWindowEvent(OPENHARMONY_Window, SDL_EVENT_WINDOW_RESIZED, (പൂർണ്ണസംഖ്യ) w, (പൂർണ്ണസംഖ്യ) h);
}

ശൂന്യം SDL_OpenHarmonyVideoSurfaceCreated(ശൂന്യം *component, ശൂന്യം *window)
{
    SDL_assert(native_xcomponent == ശൂന്യ);  // right now we assume one surface, one window.
    native_xcomponent = (OH_NativeXComponent *) component;
    native_window = window;
}

സ്ഥിതം bool OPENHARMONY_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    തിരികെ SDL_OpenHarmonyChangeScreenSaver(!_this->suspend_screensaver);
}

സ്ഥിതം bool OPENHARMONY_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;

    videodata->isPaused = false;
    videodata->isPausing = false;

    // !!! FIXME: eventually we'll want to enumerate displays, since you can probably plug in something
    // !!! FIXME:  through a USB-C to HDMI adapter, or maybe there will be separate "outer" screens vs
    // !!! FIXME:  an internal foldable one, but for now let's just get _something_ on _any_ display.
    uint64_t dispid64 = 0;
    എങ്കിൽ (OH_NativeDisplayManager_GetDefaultDisplayId(&dispid64) != DISPLAY_MANAGER_OK) {
        തിരികെ SDL_SetError("Couldn't get default display id");
    }
    സ്ഥിരം uint32_t dispid = (uint32_t) dispid64;

    NativeDisplayManager_DisplayInfo *dispinfo = ശൂന്യ;
    എങ്കിൽ (OH_NativeDisplayManager_CreateDisplayById(dispid, &dispinfo) != DISPLAY_MANAGER_OK) {  // (should really be called "CreateDisplayInfo", not "CreateDisplay")
        തിരികെ SDL_SetError("Couldn't get default display info");
    }

    SDL_DisplayMode mode;
    SDL_zero(mode);
    mode.format = SDL_PIXELFORMAT_BGRA8888;  // !!! FIXME
    mode.w = (പൂർണ്ണസംഖ്യ) dispinfo->physicalWidth;
    mode.h = (പൂർണ്ണസംഖ്യ) dispinfo->physicalHeight;
    mode.refresh_rate = (ദശാംശം) dispinfo->refreshRate;
    mode.pixel_density = 1.0f;

    സ്ഥിരം NativeDisplayManager_Rotation rotation = dispinfo->rotation;
    സ്ഥിരം NativeDisplayManager_Orientation orientation = dispinfo->orientation;

    OH_NativeDisplayManager_DestroyDisplay(dispinfo);

    സ്ഥിരം SDL_DisplayID displayID = SDL_AddBasicVideoDisplay(&mode);
    എങ്കിൽ (displayID == 0) {
        തിരികെ false;
    }

    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    തിരഞ്ഞെടുപ്പ് (orientation) {
        അവസ്ഥ DISPLAY_MANAGER_PORTRAIT: display->natural_orientation = SDL_ORIENTATION_PORTRAIT; നിർത്തുക;
        അവസ്ഥ DISPLAY_MANAGER_LANDSCAPE: display->natural_orientation = SDL_ORIENTATION_LANDSCAPE; നിർത്തുക;
        അവസ്ഥ DISPLAY_MANAGER_PORTRAIT_INVERTED: display->natural_orientation = SDL_ORIENTATION_PORTRAIT_FLIPPED; നിർത്തുക;
        അവസ്ഥ DISPLAY_MANAGER_LANDSCAPE_INVERTED: display->natural_orientation = SDL_ORIENTATION_LANDSCAPE_FLIPPED; നിർത്തുക;
        സ്ഥിരസ്ഥിതി: display->natural_orientation = SDL_ORIENTATION_UNKNOWN; നിർത്തുക;
    }

    // !!! FIXME: this is probably wrong, I think on OpenHarmony phones/tablets, these are setting both orientation and rotation, and this works out because most people are launching apps while holding the phone in portrait mode (0 rotation).
    // !!! FIXME: if I'm right, we should decide if this is a phone/tablet screen and just set the natural orientation to portrait and then use this code to calculate current orientation.
    എങ്കിൽ (rotation == DISPLAY_MANAGER_ROTATION_90) {  // rotations are clockwise on OpenHarmony.
        സ്ഥിതം സ്ഥിരം SDL_DisplayOrientation rotated[5] = { SDL_ORIENTATION_UNKNOWN, SDL_ORIENTATION_PORTRAIT, SDL_ORIENTATION_PORTRAIT_FLIPPED, SDL_ORIENTATION_LANDSCAPE_FLIPPED, SDL_ORIENTATION_LANDSCAPE };
        SDL_assert(((പൂർണ്ണസംഖ്യ) display->natural_orientation) < SDL_arraysize(rotated));
        display->current_orientation = rotated[(പൂർണ്ണസംഖ്യ) display->natural_orientation];
    } അല്ലെങ്കിൽ എങ്കിൽ (rotation == DISPLAY_MANAGER_ROTATION_180) {  // rotations are clockwise on OpenHarmony.
        സ്ഥിതം സ്ഥിരം SDL_DisplayOrientation rotated[5] = { SDL_ORIENTATION_UNKNOWN, SDL_ORIENTATION_LANDSCAPE_FLIPPED, SDL_ORIENTATION_LANDSCAPE, SDL_ORIENTATION_PORTRAIT_FLIPPED, SDL_ORIENTATION_PORTRAIT };
        SDL_assert(((പൂർണ്ണസംഖ്യ) display->natural_orientation) < SDL_arraysize(rotated));
        display->current_orientation = rotated[(പൂർണ്ണസംഖ്യ) display->natural_orientation];
    } അല്ലെങ്കിൽ എങ്കിൽ (rotation == DISPLAY_MANAGER_ROTATION_270) {  // rotations are clockwise on OpenHarmony.
        സ്ഥിതം സ്ഥിരം SDL_DisplayOrientation rotated[5] = { SDL_ORIENTATION_UNKNOWN, SDL_ORIENTATION_PORTRAIT_FLIPPED, SDL_ORIENTATION_PORTRAIT, SDL_ORIENTATION_LANDSCAPE, SDL_ORIENTATION_LANDSCAPE_FLIPPED };
        SDL_assert(((പൂർണ്ണസംഖ്യ) display->natural_orientation) < SDL_arraysize(rotated));
        display->current_orientation = rotated[(പൂർണ്ണസംഖ്യ) display->natural_orientation];
    } അല്ലെങ്കിൽ {
        display->current_orientation = display->natural_orientation;
    }

    display->content_scale = mode.pixel_density;

    // !!! FIXME: look at SDL_OnApplicationDidChangeStatusBarOrientation() and do something similar.


// !!! FIXME
#എങ്കിൽ 0
    OPENHARMONY_InitTouch();
    OPENHARMONY_InitMouse();
#endif
    OPENHARMONY_InitClipboard(_this);

    // We're done!
    തിരികെ true;
}

ശൂന്യം OPENHARMONY_VideoQuit(SDL_VideoDevice *_this)
{
    OPENHARMONY_QuitClipboard(_this);

// !!! FIXME
#എങ്കിൽ 0
    OPENHARMONY_QuitMouse();
    OPENHARMONY_QuitTouch();
#endif
}

സ്ഥിതം ശൂന്യം OPENHARMONY_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

സ്ഥിതം SDL_VideoDevice *OPENHARMONY_CreateDevice(ശൂന്യം)
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

    device->സ്വതന്ത്രം = OPENHARMONY_DeleteDevice;

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

    തിരികെ device;
}

VideoBootStrap OPENHARMONY_bootstrap = {
    OPENHARMONY_VID_DRIVER_NAME, "SDL OpenHarmony/HarmonyOS video driver",
    OPENHARMONY_CreateDevice,
    /*!!! FIXME OPENHARMONY_ShowMessageBox*/ ശൂന്യ,
    false
};

#endif // SDL_VIDEO_DRIVER_OPENHARMONY
