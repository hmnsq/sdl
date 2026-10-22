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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_VIVANTE

// SDL internals
#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../../events/SDL_events_c.h"

#यदि_परिभाषितम् SDL_निवेशः_LINUXEV
#अन्तर्भाव "../../core/linux/SDL_evdev.h"
#यदि_अन्तः

#अन्तर्भाव "SDL_vivantevideo.h"
#अन्तर्भाव "SDL_vivanteplatform.h"
#अन्तर्भाव "SDL_vivanteopengles.h"
#अन्तर्भाव "SDL_vivantevulkan.h"

स्थिर शून्य VIVANTE_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->आन्तरिकम्);
    SDL_free(device);
}

स्थिर SDL_VideoDevice *VIVANTE_Create(शून्य)
{
    SDL_VideoDevice *device;
    SDL_Video_दत्त *दत्त;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, परिमाण(SDL_VideoDevice));
    यदि (!device) {
        प्रत्यागम रिक्त;
    }

    // Initialize internal data
    दत्त = (SDL_Video_दत्त *)SDL_calloc(1, परिमाण(SDL_Video_दत्त));
    यदि (!दत्त) {
        SDL_free(device);
        प्रत्यागम रिक्त;
    }

    device->आन्तरिकम् = दत्त;

    // Setup amount of available displays
    device->अङ्कः_displays = 0;

    // Set device free function
    device->मुक्त = VIVANTE_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = VIVANTE_VideoInit;
    device->VideoQuit = VIVANTE_VideoQuit;
    device->CreateSDLWindow = VIVANTE_Create_गवाक्षः;
    device->समुच्चयः_गवाक्षः_Title = VIVANTE_समुच्चयः_गवाक्षः_Title;
    device->समुच्चयः_गवाक्षः_Position = VIVANTE_समुच्चयः_गवाक्षः_Position;
    device->समुच्चयः_गवाक्षः_आकार = VIVANTE_समुच्चयः_गवाक्षः_आकार;
    device->Show_गवाक्षः = VIVANTE_Show_गवाक्षः;
    device->Hide_गवाक्षः = VIVANTE_Hide_गवाक्षः;
    device->Destroy_गवाक्षः = VIVANTE_Destroy_गवाक्षः;

#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
    device->GL_आरोपय_Library = VIVANTE_GLES_आरोपय_Library;
    device->GL_Get_Proc_स्थानाङ्कः = VIVANTE_GLES_Get_Proc_स्थानाङ्कः;
    device->GL_UnloadLibrary = VIVANTE_GLES_UnloadLibrary;
    device->GL_CreateContext = VIVANTE_GLES_CreateContext;
    device->GL_MakeCurrent = VIVANTE_GLES_MakeCurrent;
    device->GL_समुच्चयः_Swap_Interval = VIVANTE_GLES_समुच्चयः_Swap_Interval;
    device->GL_GetSwapInterval = VIVANTE_GLES_GetSwapInterval;
    device->GL_Swap_गवाक्षः = VIVANTE_GLES_Swap_गवाक्षः;
    device->GL_DestroyContext = VIVANTE_GLES_DestroyContext;
#यदि_अन्तः

#यदि_परिभाषितम् SDL_VIDEO_VULKAN
    device->Vulkan_आरोपय_Library = VIVANTE_Vulkan_आरोपय_Library;
    device->Vulkan_UnloadLibrary = VIVANTE_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = VIVANTE_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = VIVANTE_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = VIVANTE_Vulkan_DestroySurface;
#यदि_अन्तः

    device->PumpEvents = VIVANTE_PumpEvents;

    प्रत्यागम device;
}

VideoBootStrap VIVANTE_bootstrap = {
    "vivante",
    "Vivante EGL Video Driver",
    VIVANTE_Create,
    रिक्त, // no ShowMessageBox implementation
    false
};

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/*****************************************************************************/

स्थिर bool VIVANTE_सङ्कलय_Video_Displays(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;
    SDL_VideoDisplay display;
    SDL_Display_बहुलकम् बहुलकम्;
    SDL_Display_दत्त *दत्त;
    पूर्णाङ्क pitch = 0, bpp = 0;
    अचिह्नित दीर्घ pixels = 0;

    दत्त = (SDL_Display_दत्त *)SDL_calloc(1, परिमाण(SDL_Display_दत्त));
    यदि (!दत्त) {
        प्रत्यागम false;
    }

    SDL_zero(बहुलकम्);
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_VIVANTE_VDK
    दत्त->native_display = vdkGetDisplay(videodata->vdk_वैयक्तिकम्);

    vdkGetDisplayInfo(दत्त->native_display, &बहुलकम्.w, &बहुलकम्.h, &pixels, &pitch,
                      &bpp);
#अन्यथा
    दत्त->native_display = videodata->fb_Get_Display_By_सूचकांक(0);

    videodata->fbGetDisplayInfo(दत्त->native_display, &बहुलकम्.w, &बहुलकम्.h,
                                &pixels, &pitch, &bpp);
#यदि_अन्तः // SDL_VIDEO_DRIVER_VIVANTE_VDK

    विकल्प (bpp) {
    स्वभाव: // Is another format used?
    पक्ष 32:
        बहुलकम्.format = SDL_PIXELFORMAT_ARGB8888;
        भङ्ग;
    पक्ष 16:
        बहुलकम्.format = SDL_PIXELFORMAT_RGB565;
        भङ्ग;
    }
    // FIXME: How do we query refresh rate?
    बहुलकम्.refresh_दरः = 60.0f;

    SDL_zero(display);
    display.name = VIVANTE_GetDisplayName(_this);
    display.desktop_बहुलकम् = बहुलकम्;
    display.आन्तरिकम् = दत्त;
    यदि (SDL_सङ्कलय_Video_Display(&display, false) == 0) {
        प्रत्यागम false;
    }
    प्रत्यागम true;
}

bool VIVANTE_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_VIVANTE_VDK
    videodata->vdk_वैयक्तिकम् = vdkInitialize();
    यदि (!videodata->vdk_वैयक्तिकम्) {
        प्रत्यागम SDL_समुच्चयः_Error("vdkInitialize() failed");
    }
#अन्यथा
    videodata->egl_handle = SDL_आरोपय_Object("libEGL.so.1");
    यदि (!videodata->egl_handle) {
        videodata->egl_handle = SDL_आरोपय_Object("libEGL.so");
        यदि (!videodata->egl_handle) {
            प्रत्यागम false;
        }
    }
#परिभाषय आरोपय_FUNC(TYPE, NAME)                                               \
    videodata->NAME = (TYPE)SDL_आरोपय_Function(videodata->egl_handle, #NAME); \
    यदि (!videodata->NAME)                                                   \
        प्रत्यागम false;

    आरोपय_FUNC(EGLNativeDisplayType (EGLAPIENTRY *)(शून्य *), fbGetDisplay);
    आरोपय_FUNC(EGLNativeDisplayType (EGLAPIENTRY *)(पूर्णाङ्क), fb_Get_Display_By_सूचकांक);
    आरोपय_FUNC(शून्य (EGLAPIENTRY *)(EGLNativeDisplayType, पूर्णाङ्क *, पूर्णाङ्क *), fbGetDisplayGeometry);
    आरोपय_FUNC(शून्य (EGLAPIENTRY *)(EGLNativeDisplayType, पूर्णाङ्क *, पूर्णाङ्क *, अचिह्नित दीर्घ *, पूर्णाङ्क *, पूर्णाङ्क *), fbGetDisplayInfo);
    आरोपय_FUNC(शून्य (EGLAPIENTRY *)(EGLNativeDisplayType), fbDestroyDisplay);
    आरोपय_FUNC(EGLNative_गवाक्षः_Type (EGLAPIENTRY *)(EGLNativeDisplayType, पूर्णाङ्क, पूर्णाङ्क, पूर्णाङ्क, पूर्णाङ्क), fb_Create_गवाक्षः);
    आरोपय_FUNC(शून्य (EGLAPIENTRY *)(EGLNative_गवाक्षः_Type, पूर्णाङ्क *, पूर्णाङ्क *, पूर्णाङ्क *, पूर्णाङ्क *), fb_Get_गवाक्षः_Geometry);
    आरोपय_FUNC(शून्य (EGLAPIENTRY *)(EGLNative_गवाक्षः_Type, पूर्णाङ्क *, पूर्णाङ्क *, पूर्णाङ्क *, पूर्णाङ्क *, पूर्णाङ्क *, अचिह्नित पूर्णाङ्क *), fb_Get_गवाक्षः_Info);
    आरोपय_FUNC(शून्य (EGLAPIENTRY *)(EGLNative_गवाक्षः_Type), fb_Destroy_गवाक्षः);
#यदि_अन्तः

    यदि (!VIVANTE_सज्जता_Platform(_this)) {
        प्रत्यागम false;
    }

    यदि (!VIVANTE_सङ्कलय_Video_Displays(_this)) {
        प्रत्यागम false;
    }

    VIVANTE_UpdateDisplayScale(_this);

#यदि_परिभाषितम् SDL_निवेशः_LINUXEV
    यदि (!SDL_EVDEV_Init()) {
        प्रत्यागम false;
    }
#यदि_अन्तः

    प्रत्यागम true;
}

शून्य VIVANTE_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;

#यदि_परिभाषितम् SDL_निवेशः_LINUXEV
    SDL_EVDEV_Quit();
#यदि_अन्तः

    VIVANTE_CleanupPlatform(_this);

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_VIVANTE_VDK
    यदि (videodata->vdk_वैयक्तिकम्) {
        vdkExit(videodata->vdk_वैयक्तिकम्);
        videodata->vdk_वैयक्तिकम् = रिक्त;
    }
#अन्यथा
    यदि (videodata->egl_handle) {
        SDL_UnloadObject(videodata->egl_handle);
        videodata->egl_handle = रिक्त;
    }
#यदि_अन्तः
}

bool VIVANTE_Create_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID create_props)
{
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;
    SDL_Display_दत्त *displaydata;
    SDL_गवाक्षः_दत्त *दत्त;

    displaydata = SDL_Get_Display_Driver_दत्त(SDL_GetPrimaryDisplay());

    // Allocate window internal data
    दत्त = (SDL_गवाक्षः_दत्त *)SDL_calloc(1, परिमाण(SDL_गवाक्षः_दत्त));
    यदि (!दत्त) {
        प्रत्यागम false;
    }

    // Setup driver data for this window
    गवाक्षः->आन्तरिकम् = दत्त;

    SDL_PropertiesID props = SDL_Get_गवाक्षः_Properties(गवाक्षः);
    SDL_समुच्चयः_Pointer_Property(props, SDL_PROP_गवाक्षः_VIVANTE_DISPLAY_POINTER, displaydata->native_display);

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_VIVANTE_VDK
    दत्त->native_गवाक्षः = vdk_Create_गवाक्षः(displaydata->native_display, गवाक्षः->x, गवाक्षः->y, गवाक्षः->w, गवाक्षः->h);
#अन्यथा
    दत्त->native_गवाक्षः = videodata->fb_Create_गवाक्षः(displaydata->native_display, गवाक्षः->x, गवाक्षः->y, गवाक्षः->w, गवाक्षः->h);
#यदि_अन्तः
    यदि (!दत्त->native_गवाक्षः) {
        प्रत्यागम SDL_समुच्चयः_Error("VIVANTE: Can't create native window");
    }
    SDL_समुच्चयः_Pointer_Property(props, SDL_PROP_गवाक्षः_VIVANTE_गवाक्षः_POINTER, दत्त->native_गवाक्षः);

#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
    यदि (गवाक्षः->flags & SDL_गवाक्षः_OPENGL) {
        दत्त->egl_surface = SDL_EGL_CreateSurface(_this, गवाक्षः, दत्त->native_गवाक्षः);
        यदि (दत्त->egl_surface == EGL_NO_SURFACE) {
            प्रत्यागम SDL_समुच्चयः_Error("VIVANTE: Can't create EGL surface");
        }
    } अन्यथा {
        दत्त->egl_surface = EGL_NO_SURFACE;
    }
    SDL_समुच्चयः_Pointer_Property(props, SDL_PROP_गवाक्षः_VIVANTE_SURFACE_POINTER, दत्त->egl_surface);
#यदि_अन्तः

    // Window has been successfully created
    प्रत्यागम true;
}

शून्य VIVANTE_Destroy_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;
    SDL_गवाक्षः_दत्त *दत्त;

    दत्त = गवाक्षः->आन्तरिकम्;
    यदि (दत्त) {
#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
        यदि (दत्त->egl_surface != EGL_NO_SURFACE) {
            SDL_EGL_DestroySurface(_this, दत्त->egl_surface);
        }
#यदि_अन्तः

        यदि (दत्त->native_गवाक्षः) {
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_VIVANTE_VDK
            vdk_Destroy_गवाक्षः(दत्त->native_गवाक्षः);
#अन्यथा
            videodata->fb_Destroy_गवाक्षः(दत्त->native_गवाक्षः);
#यदि_अन्तः
        }

        SDL_free(दत्त);
    }
    गवाक्षः->आन्तरिकम् = रिक्त;
}

शून्य VIVANTE_समुच्चयः_गवाक्षः_Title(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    vdk_समुच्चयः_गवाक्षः_Title(दत्त->native_गवाक्षः, गवाक्षः->title);
#यदि_अन्तः
}

bool VIVANTE_समुच्चयः_गवाक्षः_Position(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    // FIXME
    प्रत्यागम SDL_Unsupported();
}

शून्य VIVANTE_समुच्चयः_गवाक्षः_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    // FIXME
}

शून्य VIVANTE_Show_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    vdk_Show_गवाक्षः(दत्त->native_गवाक्षः);
#यदि_अन्तः
    SDL_समुच्चयः_Mouse_Focus(गवाक्षः);
    SDL_समुच्चयः_Keyboard_Focus(गवाक्षः);
}

शून्य VIVANTE_Hide_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    vdk_Hide_गवाक्षः(दत्त->native_गवाक्षः);
#यदि_अन्तः
    SDL_समुच्चयः_Mouse_Focus(रिक्त);
    SDL_समुच्चयः_Keyboard_Focus(रिक्त);
}

/*****************************************************************************/
// SDL event functions
/*****************************************************************************/
शून्य VIVANTE_PumpEvents(SDL_VideoDevice *_this)
{
#यदि_परिभाषितम् SDL_निवेशः_LINUXEV
    SDL_EVDEV_Poll();
#यदि_अन्तः
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_VIVANTE
