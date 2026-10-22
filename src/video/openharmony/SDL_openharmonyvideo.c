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
#अन्तर्भाव "SDL_internal.h"

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_OPENHARMONY

// HarmonyOS/OpenHarmony SDL video driver implementation

#अन्तर्भाव <window_manager/oh_display_manager.h>

// !!! FIXME: these are defined as "const uint32_t VARNAME = VALUE;" in native_interface_xcomponent.h, which becomes a global variable in _our_ C code! Maybe C++ handles this differently...?
#परिभाषय OH_XCOMPONENT_ID_LEN_MAX sdl_ohosvideo_OH_XCOMPONENT_ID_LEN_MAX
#परिभाषय OH_MAX_TOUCH_POINTS_सङ्ख्या sdl_ohosvideo_OH_MAX_TOUCH_POINTS_सङ्ख्या
#अन्तर्भाव <ace/xcomponent/native_interface_xcomponent.h>

// !!! FIXME: move stuff in from Android code

#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../SDL_pixels_c.h"
#अन्तर्भाव "../../events/SDL_events_c.h"
#अन्तर्भाव "../../events/SDL_windowevents_c.h"

#अन्तर्भाव "SDL_openharmonyvideo.h"
#अन्तर्भाव "SDL_openharmonyopengl.h"
#अन्तर्भाव "SDL_openharmonyclipboard.h"
#अन्तर्भाव "SDL_openharmonyevents.h"
#अन्तर्भाव "SDL_openharmonykeyboard.h"
#अन्तर्भाव "SDL_openharmonymouse.h"
//#include "SDL_openharmonytouch.h"
#अन्तर्भाव "SDL_openharmonywindow.h"
#अन्तर्भाव "SDL_openharmonyvulkan.h"
//#include "SDL_openharmonymessagebox.h"

#परिभाषय OPENHARMONY_VID_DRIVER_NAME "openharmony"

#अन्तर्भाव "../SDL_egl_c.h"
#परिभाषय OPENHARMONY_GLES_Get_Proc_स्थानाङ्कः  SDL_EGL_Get_Proc_स्थानाङ्कः_आन्तरिकम्
#परिभाषय OPENHARMONY_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#परिभाषय OPENHARMONY_GLES_समुच्चयः_Swap_Interval SDL_EGL_समुच्चयः_Swap_Interval
#परिभाषय OPENHARMONY_GLES_GetSwapInterval SDL_EGL_GetSwapInterval
#परिभाषय OPENHARMONY_GLES_DestroyContext   SDL_EGL_DestroyContext


स्थिर OH_NativeXComponent *native_xcomponent = रिक्त;
स्थिर शून्य *native_गवाक्षः = रिक्त;

शून्य SDL_Open_Harmony_Get_Native_गवाक्षः_सूचकाः(शून्य **xcomponent, शून्य **गवाक्षः)
{
    *xcomponent = (शून्य *) native_xcomponent;
    *गवाक्षः = (शून्य *) native_गवाक्षः;
}

शून्य SDL_OpenHarmonyVideoSurfaceDestroyed(शून्य *component, शून्य *गवाक्षः)
{
    SDL_assert(native_xcomponent == ((OH_NativeXComponent *) component));  // right now we assume one surface, one window.
    native_xcomponent = रिक्त;
    native_गवाक्षः = रिक्त;
}

शून्य SDL_Open_Harmony_Video_Surface_परिवर्तितम्(शून्य *component, शून्य *गवाक्षः)
{
    SDL_assert(native_xcomponent == ((OH_NativeXComponent *) component));  // right now we assume one surface, one window.
    uint64_t w, h;
    OH_Native_XComponent_Get_XComponent_आकार(native_xcomponent, native_गवाक्षः, &w, &h);
    SDL_Send_गवाक्षः_Event(OPENHARMONY_गवाक्षः, SDL_EVENT_गवाक्षः_RESIZED, (पूर्णाङ्क) w, (पूर्णाङ्क) h);
}

शून्य SDL_OpenHarmonyVideoSurfaceCreated(शून्य *component, शून्य *गवाक्षः)
{
    SDL_assert(native_xcomponent == रिक्त);  // right now we assume one surface, one window.
    native_xcomponent = (OH_NativeXComponent *) component;
    native_गवाक्षः = गवाक्षः;
}

स्थिर bool OPENHARMONY_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    प्रत्यागम SDL_OpenHarmonyChangeScreenSaver(!_this->suspend_screensaver);
}

स्थिर bool OPENHARMONY_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;

    videodata->isPaused = false;
    videodata->isPausing = false;

    // !!! FIXME: eventually we'll want to enumerate displays, since you can probably plug in something
    // !!! FIXME:  through a USB-C to HDMI adapter, or maybe there will be separate "outer" screens vs
    // !!! FIXME:  an internal foldable one, but for now let's just get _something_ on _any_ display.
    uint64_t dispid64 = 0;
    यदि (OH_NativeDisplayManager_GetDefaultDisplayId(&dispid64) != DISPLAY_MANAGER_OK) {
        प्रत्यागम SDL_समुच्चयः_Error("Couldn't get default display id");
    }
    ध्रुव uint32_t dispid = (uint32_t) dispid64;

    NativeDisplayManager_DisplayInfo *dispinfo = रिक्त;
    यदि (OH_NativeDisplayManager_CreateDisplayById(dispid, &dispinfo) != DISPLAY_MANAGER_OK) {  // (should really be called "CreateDisplayInfo", not "CreateDisplay")
        प्रत्यागम SDL_समुच्चयः_Error("Couldn't get default display info");
    }

    SDL_Display_बहुलकम् बहुलकम्;
    SDL_zero(बहुलकम्);
    बहुलकम्.format = SDL_PIXELFORMAT_BGRA8888;  // !!! FIXME
    बहुलकम्.w = (पूर्णाङ्क) dispinfo->physical_विस्तारः;
    बहुलकम्.h = (पूर्णाङ्क) dispinfo->physicalHeight;
    बहुलकम्.refresh_दरः = (भिन्न) dispinfo->refresh_दरः_2;
    बहुलकम्.pixel_density = 1.0f;

    ध्रुव NativeDisplayManager_Rotation rotation = dispinfo->rotation;
    ध्रुव NativeDisplayManager_Orientation orientation = dispinfo->orientation;

    OH_NativeDisplayManager_DestroyDisplay(dispinfo);

    ध्रुव SDL_DisplayID displayID = SDL_सङ्कलय_Basic_Video_Display(&बहुलकम्);
    यदि (displayID == 0) {
        प्रत्यागम false;
    }

    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    विकल्प (orientation) {
        पक्ष DISPLAY_MANAGER_PORTRAIT: display->natural_orientation = SDL_ORIENTATION_PORTRAIT; भङ्ग;
        पक्ष DISPLAY_MANAGER_LANDSCAPE: display->natural_orientation = SDL_ORIENTATION_LANDSCAPE; भङ्ग;
        पक्ष DISPLAY_MANAGER_PORTRAIT_INVERTED: display->natural_orientation = SDL_ORIENTATION_PORTRAIT_FLIPPED; भङ्ग;
        पक्ष DISPLAY_MANAGER_LANDSCAPE_INVERTED: display->natural_orientation = SDL_ORIENTATION_LANDSCAPE_FLIPPED; भङ्ग;
        स्वभाव: display->natural_orientation = SDL_ORIENTATION_UNKNOWN; भङ्ग;
    }

    // !!! FIXME: this is probably wrong, I think on OpenHarmony phones/tablets, these are setting both orientation and rotation, and this works out because most people are launching apps while holding the phone in portrait mode (0 rotation).
    // !!! FIXME: if I'm right, we should decide if this is a phone/tablet screen and just set the natural orientation to portrait and then use this code to calculate current orientation.
    यदि (rotation == DISPLAY_MANAGER_ROTATION_90) {  // rotations are clockwise on OpenHarmony.
        स्थिर ध्रुव SDL_DisplayOrientation rotated[5] = { SDL_ORIENTATION_UNKNOWN, SDL_ORIENTATION_PORTRAIT, SDL_ORIENTATION_PORTRAIT_FLIPPED, SDL_ORIENTATION_LANDSCAPE_FLIPPED, SDL_ORIENTATION_LANDSCAPE };
        SDL_assert(((पूर्णाङ्क) display->natural_orientation) < SDL_arraysize(rotated));
        display->current_orientation = rotated[(पूर्णाङ्क) display->natural_orientation];
    } अन्यथा यदि (rotation == DISPLAY_MANAGER_ROTATION_180) {  // rotations are clockwise on OpenHarmony.
        स्थिर ध्रुव SDL_DisplayOrientation rotated[5] = { SDL_ORIENTATION_UNKNOWN, SDL_ORIENTATION_LANDSCAPE_FLIPPED, SDL_ORIENTATION_LANDSCAPE, SDL_ORIENTATION_PORTRAIT_FLIPPED, SDL_ORIENTATION_PORTRAIT };
        SDL_assert(((पूर्णाङ्क) display->natural_orientation) < SDL_arraysize(rotated));
        display->current_orientation = rotated[(पूर्णाङ्क) display->natural_orientation];
    } अन्यथा यदि (rotation == DISPLAY_MANAGER_ROTATION_270) {  // rotations are clockwise on OpenHarmony.
        स्थिर ध्रुव SDL_DisplayOrientation rotated[5] = { SDL_ORIENTATION_UNKNOWN, SDL_ORIENTATION_PORTRAIT_FLIPPED, SDL_ORIENTATION_PORTRAIT, SDL_ORIENTATION_LANDSCAPE, SDL_ORIENTATION_LANDSCAPE_FLIPPED };
        SDL_assert(((पूर्णाङ्क) display->natural_orientation) < SDL_arraysize(rotated));
        display->current_orientation = rotated[(पूर्णाङ्क) display->natural_orientation];
    } अन्यथा {
        display->current_orientation = display->natural_orientation;
    }

    display->content_scale = बहुलकम्.pixel_density;

    // !!! FIXME: look at SDL_OnApplicationDidChangeStatusBarOrientation() and do something similar.


// !!! FIXME
#यदि 0
    OPENHARMONY_InitTouch();
    OPENHARMONY_InitMouse();
#यदि_अन्तः
    OPENHARMONY_InitClipboard(_this);

    // We're done!
    प्रत्यागम true;
}

शून्य OPENHARMONY_VideoQuit(SDL_VideoDevice *_this)
{
    OPENHARMONY_QuitClipboard(_this);

// !!! FIXME
#यदि 0
    OPENHARMONY_QuitMouse();
    OPENHARMONY_QuitTouch();
#यदि_अन्तः
}

स्थिर शून्य OPENHARMONY_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device->आन्तरिकम्);
    SDL_free(device);
}

स्थिर SDL_VideoDevice *OPENHARMONY_CreateDevice(शून्य)
{
    SDL_VideoDevice *device;
    SDL_Video_दत्त *दत्त;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *)SDL_calloc(1, परिमाण(SDL_VideoDevice));
    यदि (!device) {
        प्रत्यागम रिक्त;
    }

    दत्त = (SDL_Video_दत्त *)SDL_calloc(1, परिमाण(SDL_Video_दत्त));
    यदि (!दत्त) {
        SDL_free(device);
        प्रत्यागम रिक्त;
    }

    device->आन्तरिकम् = दत्त;
    device->system_theme = SDL_GetOpenHarmonySystemTheme();

    // Set the function pointers
    device->VideoInit = OPENHARMONY_VideoInit;
    device->VideoQuit = OPENHARMONY_VideoQuit;

    device->CreateSDLWindow = OPENHARMONY_Create_गवाक्षः;
    device->समुच्चयः_गवाक्षः_Title = OPENHARMONY_समुच्चयः_गवाक्षः_Title;
    device->समुच्चयः_गवाक्षः_Fullscreen = OPENHARMONY_समुच्चयः_गवाक्षः_Fullscreen;
    device->Minimize_गवाक्षः = OPENHARMONY_Minimize_गवाक्षः;
    device->समुच्चयः_गवाक्षः_Resizable = OPENHARMONY_समुच्चयः_गवाक्षः_Resizable;
    device->Destroy_गवाक्षः = OPENHARMONY_Destroy_गवाक्षः;

    device->मुक्त = OPENHARMONY_DeleteDevice;

    // GL pointers
#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
    device->GL_आरोपय_Library = OPENHARMONY_GLES_आरोपय_Library;
    device->GL_Get_Proc_स्थानाङ्कः = OPENHARMONY_GLES_Get_Proc_स्थानाङ्कः;
    device->GL_UnloadLibrary = OPENHARMONY_GLES_UnloadLibrary;
    device->GL_CreateContext = OPENHARMONY_GLES_CreateContext;
    device->GL_MakeCurrent = OPENHARMONY_GLES_MakeCurrent;
    device->GL_समुच्चयः_Swap_Interval = OPENHARMONY_GLES_समुच्चयः_Swap_Interval;
    device->GL_GetSwapInterval = OPENHARMONY_GLES_GetSwapInterval;
    device->GL_Swap_गवाक्षः = OPENHARMONY_GLES_Swap_गवाक्षः;
    device->GL_DestroyContext = OPENHARMONY_GLES_DestroyContext;
#यदि_अन्तः

#यदि_परिभाषितम् SDL_VIDEO_VULKAN
    device->Vulkan_आरोपय_Library = OPENHARMONY_Vulkan_आरोपय_Library;
    device->Vulkan_UnloadLibrary = OPENHARMONY_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = OPENHARMONY_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = OPENHARMONY_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = OPENHARMONY_Vulkan_DestroySurface;
#यदि_अन्तः

    // Screensaver
    device->SuspendScreenSaver = OPENHARMONY_SuspendScreenSaver;

    device->PumpEvents = OPENHARMONY_PumpEvents;

    // Screen keyboard
    device->HasScreenKeyboardSupport = OPENHARMONY_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = OPENHARMONY_ShowScreenKeyboard;
    device->HideScreenKeyboard = OPENHARMONY_HideScreenKeyboard;

    // Clipboard
    device->GetTextMimeTypes = OPENHARMONY_GetTextMimeTypes;
    device->समुच्चयः_Clipboard_Text = OPENHARMONY_समुच्चयः_Clipboard_Text;
    device->GetClipboardText = OPENHARMONY_GetClipboardText;
    device->HasClipboardText = OPENHARMONY_HasClipboardText;

    device->device_caps = VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS;

    प्रत्यागम device;
}

VideoBootStrap OPENHARMONY_bootstrap = {
    OPENHARMONY_VID_DRIVER_NAME, "SDL OpenHarmony/HarmonyOS video driver",
    OPENHARMONY_CreateDevice,
    /*!!! FIXME OPENHARMONY_ShowMessageBox*/ रिक्त,
    false
};

#यदि_अन्तः // SDL_VIDEO_DRIVER_OPENHARMONY
