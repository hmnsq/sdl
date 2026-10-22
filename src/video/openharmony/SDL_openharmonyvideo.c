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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_OPENHARMONY

// HarmonyOS/OpenHarmony SDL video driver implementation

#समावेश <window_manager/oh_display_manager.h>

// !!! FIXME: these are defined as "const uint32_t VARNAME = VALUE;" in native_interface_xcomponent.h, which becomes a global variable in _our_ C code! Maybe C++ handles this differently...?
#घोषणा OH_XCOMPONENT_ID_LEN_MAX sdl_ohosvideo_OH_XCOMPONENT_ID_LEN_MAX
#घोषणा OH_MAX_TOUCH_POINTS_संख्या sdl_ohosvideo_OH_MAX_TOUCH_POINTS_संख्या
#समावेश <ace/xcomponent/native_interface_xcomponent.h>

// !!! FIXME: move stuff in from Android code

#समावेश "../SDL_sysvideo.h"
#समावेश "../SDL_pixels_c.h"
#समावेश "../../events/SDL_events_c.h"
#समावेश "../../events/SDL_windowevents_c.h"

#समावेश "SDL_openharmonyvideo.h"
#समावेश "SDL_openharmonyopengl.h"
#समावेश "SDL_openharmonyclipboard.h"
#समावेश "SDL_openharmonyevents.h"
#समावेश "SDL_openharmonykeyboard.h"
#समावेश "SDL_openharmonymouse.h"
//#include "SDL_openharmonytouch.h"
#समावेश "SDL_openharmonywindow.h"
#समावेश "SDL_openharmonyvulkan.h"
//#include "SDL_openharmonymessagebox.h"

#घोषणा OPENHARMONY_VID_DRIVER_NAME "openharmony"

#समावेश "../SDL_egl_c.h"
#घोषणा OPENHARMONY_GLES_GetProcAddress  SDL_EGL_GetProcAddressInternal
#घोषणा OPENHARMONY_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#घोषणा OPENHARMONY_GLES_SetSwapInterval SDL_EGL_SetSwapInterval
#घोषणा OPENHARMONY_GLES_GetSwapInterval SDL_EGL_GetSwapInterval
#घोषणा OPENHARMONY_GLES_DestroyContext   SDL_EGL_DestroyContext


अटल OH_NativeXComponent *native_xcomponent = शून्य;
अटल व्योम *native_window = शून्य;

व्योम SDL_OpenHarmonyGetNativeWindowPointers(व्योम **xcomponent, व्योम **window)
{
    *xcomponent = (व्योम *) native_xcomponent;
    *window = (व्योम *) native_window;
}

व्योम SDL_OpenHarmonyVideoSurfaceDestroyed(व्योम *component, व्योम *window)
{
    SDL_assert(native_xcomponent == ((OH_NativeXComponent *) component));  // right now we assume one surface, one window.
    native_xcomponent = शून्य;
    native_window = शून्य;
}

व्योम SDL_OpenHarmonyVideoSurfaceChanged(व्योम *component, व्योम *window)
{
    SDL_assert(native_xcomponent == ((OH_NativeXComponent *) component));  // right now we assume one surface, one window.
    uint64_t w, h;
    OH_Native_XComponent_Get_XComponent_आकार(native_xcomponent, native_window, &w, &h);
    SDL_SendWindowEvent(OPENHARMONY_Window, SDL_EVENT_WINDOW_RESIZED, (पूर्णांक) w, (पूर्णांक) h);
}

व्योम SDL_OpenHarmonyVideoSurfaceCreated(व्योम *component, व्योम *window)
{
    SDL_assert(native_xcomponent == शून्य);  // right now we assume one surface, one window.
    native_xcomponent = (OH_NativeXComponent *) component;
    native_window = window;
}

अटल bool OPENHARMONY_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    वापस SDL_OpenHarmonyChangeScreenSaver(!_this->suspend_screensaver);
}

अटल bool OPENHARMONY_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *videodata = _this->internal;

    videodata->isPaused = false;
    videodata->isPausing = false;

    // !!! FIXME: eventually we'll want to enumerate displays, since you can probably plug in something
    // !!! FIXME:  through a USB-C to HDMI adapter, or maybe there will be separate "outer" screens vs
    // !!! FIXME:  an internal foldable one, but for now let's just get _something_ on _any_ display.
    uint64_t dispid64 = 0;
    अगर (OH_NativeDisplayManager_GetDefaultDisplayId(&dispid64) != DISPLAY_MANAGER_OK) {
        वापस SDL_SetError("Couldn't get default display id");
    }
    स्थिर uint32_t dispid = (uint32_t) dispid64;

    NativeDisplayManager_DisplayInfo *dispinfo = शून्य;
    अगर (OH_NativeDisplayManager_CreateDisplayById(dispid, &dispinfo) != DISPLAY_MANAGER_OK) {  // (should really be called "CreateDisplayInfo", not "CreateDisplay")
        वापस SDL_SetError("Couldn't get default display info");
    }

    SDL_DisplayMode mode;
    SDL_zero(mode);
    mode.format = SDL_PIXELFORMAT_BGRA8888;  // !!! FIXME
    mode.w = (पूर्णांक) dispinfo->physicalWidth;
    mode.h = (पूर्णांक) dispinfo->physicalHeight;
    mode.refresh_rate = (भग्न) dispinfo->refreshRate;
    mode.pixel_density = 1.0f;

    स्थिर NativeDisplayManager_Rotation rotation = dispinfo->rotation;
    स्थिर NativeDisplayManager_Orientation orientation = dispinfo->orientation;

    OH_NativeDisplayManager_DestroyDisplay(dispinfo);

    स्थिर SDL_DisplayID displayID = SDL_AddBasicVideoDisplay(&mode);
    अगर (displayID == 0) {
        वापस false;
    }

    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    चयन (orientation) {
        हाल DISPLAY_MANAGER_PORTRAIT: display->natural_orientation = SDL_ORIENTATION_PORTRAIT; अवरोध;
        हाल DISPLAY_MANAGER_LANDSCAPE: display->natural_orientation = SDL_ORIENTATION_LANDSCAPE; अवरोध;
        हाल DISPLAY_MANAGER_PORTRAIT_INVERTED: display->natural_orientation = SDL_ORIENTATION_PORTRAIT_FLIPPED; अवरोध;
        हाल DISPLAY_MANAGER_LANDSCAPE_INVERTED: display->natural_orientation = SDL_ORIENTATION_LANDSCAPE_FLIPPED; अवरोध;
        शेष: display->natural_orientation = SDL_ORIENTATION_UNKNOWN; अवरोध;
    }

    // !!! FIXME: this is probably wrong, I think on OpenHarmony phones/tablets, these are setting both orientation and rotation, and this works out because most people are launching apps while holding the phone in portrait mode (0 rotation).
    // !!! FIXME: if I'm right, we should decide if this is a phone/tablet screen and just set the natural orientation to portrait and then use this code to calculate current orientation.
    अगर (rotation == DISPLAY_MANAGER_ROTATION_90) {  // rotations are clockwise on OpenHarmony.
        अटल स्थिर SDL_DisplayOrientation rotated[5] = { SDL_ORIENTATION_UNKNOWN, SDL_ORIENTATION_PORTRAIT, SDL_ORIENTATION_PORTRAIT_FLIPPED, SDL_ORIENTATION_LANDSCAPE_FLIPPED, SDL_ORIENTATION_LANDSCAPE };
        SDL_assert(((पूर्णांक) display->natural_orientation) < SDL_arraysize(rotated));
        display->current_orientation = rotated[(पूर्णांक) display->natural_orientation];
    } अन्यथा अगर (rotation == DISPLAY_MANAGER_ROTATION_180) {  // rotations are clockwise on OpenHarmony.
        अटल स्थिर SDL_DisplayOrientation rotated[5] = { SDL_ORIENTATION_UNKNOWN, SDL_ORIENTATION_LANDSCAPE_FLIPPED, SDL_ORIENTATION_LANDSCAPE, SDL_ORIENTATION_PORTRAIT_FLIPPED, SDL_ORIENTATION_PORTRAIT };
        SDL_assert(((पूर्णांक) display->natural_orientation) < SDL_arraysize(rotated));
        display->current_orientation = rotated[(पूर्णांक) display->natural_orientation];
    } अन्यथा अगर (rotation == DISPLAY_MANAGER_ROTATION_270) {  // rotations are clockwise on OpenHarmony.
        अटल स्थिर SDL_DisplayOrientation rotated[5] = { SDL_ORIENTATION_UNKNOWN, SDL_ORIENTATION_PORTRAIT_FLIPPED, SDL_ORIENTATION_PORTRAIT, SDL_ORIENTATION_LANDSCAPE, SDL_ORIENTATION_LANDSCAPE_FLIPPED };
        SDL_assert(((पूर्णांक) display->natural_orientation) < SDL_arraysize(rotated));
        display->current_orientation = rotated[(पूर्णांक) display->natural_orientation];
    } अन्यथा {
        display->current_orientation = display->natural_orientation;
    }

    display->content_scale = mode.pixel_density;

    // !!! FIXME: look at SDL_OnApplicationDidChangeStatusBarOrientation() and do something similar.


// !!! FIXME
#अगर 0
    OPENHARMONY_InitTouch();
    OPENHARMONY_InitMouse();
#पूर्ण_अगर
    OPENHARMONY_InitClipboard(_this);

    // We're done!
    वापस true;
}

व्योम OPENHARMONY_VideoQuit(SDL_VideoDevice *_this)
{
    OPENHARMONY_QuitClipboard(_this);

// !!! FIXME
#अगर 0
    OPENHARMONY_QuitMouse();
    OPENHARMONY_QuitTouch();
#पूर्ण_अगर
}

अटल व्योम OPENHARMONY_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

अटल SDL_VideoDevice *OPENHARMONY_CreateDevice(व्योम)
{
    SDL_VideoDevice *device;
    SDL_Video_तथ्य *तथ्य;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, माप(SDL_VideoDevice));
    अगर (!device) {
        वापस शून्य;
    }

    तथ्य = (SDL_Video_तथ्य *)SDL_calloc(1, माप(SDL_Video_तथ्य));
    अगर (!तथ्य) {
        SDL_free(device);
        वापस शून्य;
    }

    device->internal = तथ्य;
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

    device->मुक्त = OPENHARMONY_DeleteDevice;

    // GL pointers
#अगर_घोषित SDL_VIDEO_OPENGL_EGL
    device->GL_LoadLibrary = OPENHARMONY_GLES_LoadLibrary;
    device->GL_GetProcAddress = OPENHARMONY_GLES_GetProcAddress;
    device->GL_UnloadLibrary = OPENHARMONY_GLES_UnloadLibrary;
    device->GL_CreateContext = OPENHARMONY_GLES_CreateContext;
    device->GL_MakeCurrent = OPENHARMONY_GLES_MakeCurrent;
    device->GL_SetSwapInterval = OPENHARMONY_GLES_SetSwapInterval;
    device->GL_GetSwapInterval = OPENHARMONY_GLES_GetSwapInterval;
    device->GL_SwapWindow = OPENHARMONY_GLES_SwapWindow;
    device->GL_DestroyContext = OPENHARMONY_GLES_DestroyContext;
#पूर्ण_अगर

#अगर_घोषित SDL_VIDEO_VULKAN
    device->Vulkan_LoadLibrary = OPENHARMONY_Vulkan_LoadLibrary;
    device->Vulkan_UnloadLibrary = OPENHARMONY_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = OPENHARMONY_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = OPENHARMONY_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = OPENHARMONY_Vulkan_DestroySurface;
#पूर्ण_अगर

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

    वापस device;
}

VideoBootStrap OPENHARMONY_bootstrap = {
    OPENHARMONY_VID_DRIVER_NAME, "SDL OpenHarmony/HarmonyOS video driver",
    OPENHARMONY_CreateDevice,
    /*!!! FIXME OPENHARMONY_ShowMessageBox*/ शून्य,
    false
};

#पूर्ण_अगर // SDL_VIDEO_DRIVER_OPENHARMONY
