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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_OPENHARMONY

// HarmonyOS/OpenHarmony SDL video driver implementation

#ଅନ୍ତର୍ଭାଵ <window_manager/oh_display_manager.h>

// !!! FIXME: these are defined as "const uint32_t VARNAME = VALUE;" in native_interface_xcomponent.h, which becomes a global variable in _our_ C code! Maybe C++ handles this differently...?
#define OH_XCOMPONENT_ID_LEN_MAX sdl_ohosvideo_OH_XCOMPONENT_ID_LEN_MAX
#define OH_MAX_TOUCH_POINTS_ସଂଖ୍ୟା sdl_ohosvideo_OH_MAX_TOUCH_POINTS_ସଂଖ୍ୟା
#ଅନ୍ତର୍ଭାଵ <ace/xcomponent/native_interface_xcomponent.h>

// !!! FIXME: move stuff in from Android code

#ଅନ୍ତର୍ଭାଵ "../SDL_sysvideo.h"
#ଅନ୍ତର୍ଭାଵ "../SDL_pixels_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_events_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_windowevents_c.h"

#ଅନ୍ତର୍ଭାଵ "SDL_openharmonyvideo.h"
#ଅନ୍ତର୍ଭାଵ "SDL_openharmonyopengl.h"
#ଅନ୍ତର୍ଭାଵ "SDL_openharmonyclipboard.h"
#ଅନ୍ତର୍ଭାଵ "SDL_openharmonyevents.h"
#ଅନ୍ତର୍ଭାଵ "SDL_openharmonykeyboard.h"
#ଅନ୍ତର୍ଭାଵ "SDL_openharmonymouse.h"
//#include "SDL_openharmonytouch.h"
#ଅନ୍ତର୍ଭାଵ "SDL_openharmonywindow.h"
#ଅନ୍ତର୍ଭାଵ "SDL_openharmonyvulkan.h"
//#include "SDL_openharmonymessagebox.h"

#define OPENHARMONY_VID_DRIVER_NAME "openharmony"

#ଅନ୍ତର୍ଭାଵ "../SDL_egl_c.h"
#define OPENHARMONY_GLES_GetProcAddress  SDL_EGL_GetProcAddressInternal
#define OPENHARMONY_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#define OPENHARMONY_GLES_SetSwapInterval SDL_EGL_SetSwapInterval
#define OPENHARMONY_GLES_GetSwapInterval SDL_EGL_GetSwapInterval
#define OPENHARMONY_GLES_DestroyContext   SDL_EGL_DestroyContext


ସ୍ଥିର OH_NativeXComponent *native_xcomponent = ଖାଲି;
ସ୍ଥିର ଶୂନ୍ୟ *native_window = ଖାଲି;

ଶୂନ୍ୟ SDL_OpenHarmonyGetNativeWindowPointers(ଶୂନ୍ୟ **xcomponent, ଶୂନ୍ୟ **window)
{
    *xcomponent = (ଶୂନ୍ୟ *) native_xcomponent;
    *window = (ଶୂନ୍ୟ *) native_window;
}

ଶୂନ୍ୟ SDL_OpenHarmonyVideoSurfaceDestroyed(ଶୂନ୍ୟ *component, ଶୂନ୍ୟ *window)
{
    SDL_assert(native_xcomponent == ((OH_NativeXComponent *) component));  // right now we assume one surface, one window.
    native_xcomponent = ଖାଲି;
    native_window = ଖାଲି;
}

ଶୂନ୍ୟ SDL_OpenHarmonyVideoSurfaceChanged(ଶୂନ୍ୟ *component, ଶୂନ୍ୟ *window)
{
    SDL_assert(native_xcomponent == ((OH_NativeXComponent *) component));  // right now we assume one surface, one window.
    uint64_t w, h;
    OH_NativeXComponent_GetXComponentSize(native_xcomponent, native_window, &w, &h);
    SDL_SendWindowEvent(OPENHARMONY_Window, SDL_EVENT_WINDOW_RESIZED, (ପୂର୍ଣ୍ଣସଂଖ୍ୟା) w, (ପୂର୍ଣ୍ଣସଂଖ୍ୟା) h);
}

ଶୂନ୍ୟ SDL_OpenHarmonyVideoSurfaceCreated(ଶୂନ୍ୟ *component, ଶୂନ୍ୟ *window)
{
    SDL_assert(native_xcomponent == ଖାଲି);  // right now we assume one surface, one window.
    native_xcomponent = (OH_NativeXComponent *) component;
    native_window = window;
}

ସ୍ଥିର bool OPENHARMONY_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    ଫେରନ୍ତୁ SDL_OpenHarmonyChangeScreenSaver(!_this->suspend_screensaver);
}

ସ୍ଥିର bool OPENHARMONY_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoData *videodata = _this->internal;

    videodata->isPaused = false;
    videodata->isPausing = false;

    // !!! FIXME: eventually we'll want to enumerate displays, since you can probably plug in something
    // !!! FIXME:  through a USB-C to HDMI adapter, or maybe there will be separate "outer" screens vs
    // !!! FIXME:  an internal foldable one, but for now let's just get _something_ on _any_ display.
    uint64_t dispid64 = 0;
    ଯଦି (OH_NativeDisplayManager_GetDefaultDisplayId(&dispid64) != DISPLAY_MANAGER_OK) {
        ଫେରନ୍ତୁ SDL_SetError("Couldn't get default display id");
    }
    ଅଚଳ uint32_t dispid = (uint32_t) dispid64;

    NativeDisplayManager_DisplayInfo *dispinfo = ଖାଲି;
    ଯଦି (OH_NativeDisplayManager_CreateDisplayById(dispid, &dispinfo) != DISPLAY_MANAGER_OK) {  // (should really be called "CreateDisplayInfo", not "CreateDisplay")
        ଫେରନ୍ତୁ SDL_SetError("Couldn't get default display info");
    }

    SDL_DisplayMode mode;
    SDL_zero(mode);
    mode.format = SDL_PIXELFORMAT_BGRA8888;  // !!! FIXME
    mode.w = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା) dispinfo->physicalWidth;
    mode.h = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା) dispinfo->physicalHeight;
    mode.refresh_rate = (ଦଶମିକ) dispinfo->refreshRate;
    mode.pixel_density = 1.0f;

    ଅଚଳ NativeDisplayManager_Rotation rotation = dispinfo->rotation;
    ଅଚଳ NativeDisplayManager_Orientation orientation = dispinfo->orientation;

    OH_NativeDisplayManager_DestroyDisplay(dispinfo);

    ଅଚଳ SDL_DisplayID displayID = SDL_AddBasicVideoDisplay(&mode);
    ଯଦି (displayID == 0) {
        ଫେରନ୍ତୁ false;
    }

    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    ବାଛ (orientation) {
        ସ୍ଥିତି DISPLAY_MANAGER_PORTRAIT: display->natural_orientation = SDL_ORIENTATION_PORTRAIT; ଭାଙ୍ଗ;
        ସ୍ଥିତି DISPLAY_MANAGER_LANDSCAPE: display->natural_orientation = SDL_ORIENTATION_LANDSCAPE; ଭାଙ୍ଗ;
        ସ୍ଥିତି DISPLAY_MANAGER_PORTRAIT_INVERTED: display->natural_orientation = SDL_ORIENTATION_PORTRAIT_FLIPPED; ଭାଙ୍ଗ;
        ସ୍ଥିତି DISPLAY_MANAGER_LANDSCAPE_INVERTED: display->natural_orientation = SDL_ORIENTATION_LANDSCAPE_FLIPPED; ଭାଙ୍ଗ;
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ: display->natural_orientation = SDL_ORIENTATION_UNKNOWN; ଭାଙ୍ଗ;
    }

    // !!! FIXME: this is probably wrong, I think on OpenHarmony phones/tablets, these are setting both orientation and rotation, and this works out because most people are launching apps while holding the phone in portrait mode (0 rotation).
    // !!! FIXME: if I'm right, we should decide if this is a phone/tablet screen and just set the natural orientation to portrait and then use this code to calculate current orientation.
    ଯଦି (rotation == DISPLAY_MANAGER_ROTATION_90) {  // rotations are clockwise on OpenHarmony.
        ସ୍ଥିର ଅଚଳ SDL_DisplayOrientation rotated[5] = { SDL_ORIENTATION_UNKNOWN, SDL_ORIENTATION_PORTRAIT, SDL_ORIENTATION_PORTRAIT_FLIPPED, SDL_ORIENTATION_LANDSCAPE_FLIPPED, SDL_ORIENTATION_LANDSCAPE };
        SDL_assert(((ପୂର୍ଣ୍ଣସଂଖ୍ୟା) display->natural_orientation) < SDL_arraysize(rotated));
        display->current_orientation = rotated[(ପୂର୍ଣ୍ଣସଂଖ୍ୟା) display->natural_orientation];
    } ଅନ୍ୟଥା ଯଦି (rotation == DISPLAY_MANAGER_ROTATION_180) {  // rotations are clockwise on OpenHarmony.
        ସ୍ଥିର ଅଚଳ SDL_DisplayOrientation rotated[5] = { SDL_ORIENTATION_UNKNOWN, SDL_ORIENTATION_LANDSCAPE_FLIPPED, SDL_ORIENTATION_LANDSCAPE, SDL_ORIENTATION_PORTRAIT_FLIPPED, SDL_ORIENTATION_PORTRAIT };
        SDL_assert(((ପୂର୍ଣ୍ଣସଂଖ୍ୟା) display->natural_orientation) < SDL_arraysize(rotated));
        display->current_orientation = rotated[(ପୂର୍ଣ୍ଣସଂଖ୍ୟା) display->natural_orientation];
    } ଅନ୍ୟଥା ଯଦି (rotation == DISPLAY_MANAGER_ROTATION_270) {  // rotations are clockwise on OpenHarmony.
        ସ୍ଥିର ଅଚଳ SDL_DisplayOrientation rotated[5] = { SDL_ORIENTATION_UNKNOWN, SDL_ORIENTATION_PORTRAIT_FLIPPED, SDL_ORIENTATION_PORTRAIT, SDL_ORIENTATION_LANDSCAPE, SDL_ORIENTATION_LANDSCAPE_FLIPPED };
        SDL_assert(((ପୂର୍ଣ୍ଣସଂଖ୍ୟା) display->natural_orientation) < SDL_arraysize(rotated));
        display->current_orientation = rotated[(ପୂର୍ଣ୍ଣସଂଖ୍ୟା) display->natural_orientation];
    } ଅନ୍ୟଥା {
        display->current_orientation = display->natural_orientation;
    }

    display->content_scale = mode.pixel_density;

    // !!! FIXME: look at SDL_OnApplicationDidChangeStatusBarOrientation() and do something similar.


// !!! FIXME
#ଯଦି 0
    OPENHARMONY_InitTouch();
    OPENHARMONY_InitMouse();
#endif
    OPENHARMONY_InitClipboard(_this);

    // We're done!
    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ OPENHARMONY_VideoQuit(SDL_VideoDevice *_this)
{
    OPENHARMONY_QuitClipboard(_this);

// !!! FIXME
#ଯଦି 0
    OPENHARMONY_QuitMouse();
    OPENHARMONY_QuitTouch();
#endif
}

ସ୍ଥିର ଶୂନ୍ୟ OPENHARMONY_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

ସ୍ଥିର SDL_VideoDevice *OPENHARMONY_CreateDevice(ଶୂନ୍ୟ)
{
    SDL_VideoDevice *device;
    SDL_VideoData *data;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, ଆକାର(SDL_VideoDevice));
    ଯଦି (!device) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    data = (SDL_VideoData *)SDL_calloc(1, ଆକାର(SDL_VideoData));
    ଯଦି (!data) {
        SDL_free(device);
        ଫେରନ୍ତୁ ଖାଲି;
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

    device->ମୁକ୍ତ = OPENHARMONY_DeleteDevice;

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

    ଫେରନ୍ତୁ device;
}

VideoBootStrap OPENHARMONY_bootstrap = {
    OPENHARMONY_VID_DRIVER_NAME, "SDL OpenHarmony/HarmonyOS video driver",
    OPENHARMONY_CreateDevice,
    /*!!! FIXME OPENHARMONY_ShowMessageBox*/ ଖାଲି,
    false
};

#endif // SDL_VIDEO_DRIVER_OPENHARMONY
