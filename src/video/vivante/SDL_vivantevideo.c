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

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_VIVANTE

// SDL internals
#شامل "../SDL_sysvideo.h"
#شامل "../../events/SDL_events_c.h"

#اگر_تعریف_شدہ SDL_داخلہ_LINUXEV
#شامل "../../core/linux/SDL_evdev.h"
#اگر_ختم

#شامل "SDL_vivantevideo.h"
#شامل "SDL_vivanteplatform.h"
#شامل "SDL_vivanteopengles.h"
#شامل "SDL_vivantevulkan.h"

ساکن خالی VIVANTE_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->اندرونی_2);
    SDL_free(device);
}

ساکن SDL_VideoDevice *VIVANTE_Create(خالی)
{
    SDL_VideoDevice *device;
    SDL_Video_ڈیٹا *ڈیٹا;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    اگر (!device) {
        واپس تہی;
    }

    // Initialize internal data
    ڈیٹا = (SDL_Video_ڈیٹا *)SDL_calloc(1, حجم(SDL_Video_ڈیٹا));
    اگر (!ڈیٹا) {
        SDL_free(device);
        واپس تہی;
    }

    device->اندرونی_2 = ڈیٹا;

    // Setup amount of available displays
    device->عدد_displays = 0;

    // Set device free function
    device->آزاد = VIVANTE_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = VIVANTE_VideoInit;
    device->VideoQuit = VIVANTE_VideoQuit;
    device->CreateSDLWindow = VIVANTE_Create_کھڑکی;
    device->سیٹ_کھڑکی_Title = VIVANTE_سیٹ_کھڑکی_Title;
    device->سیٹ_کھڑکی_Position = VIVANTE_سیٹ_کھڑکی_Position;
    device->سیٹ_کھڑکی_سائز = VIVANTE_سیٹ_کھڑکی_سائز;
    device->Show_کھڑکی = VIVANTE_Show_کھڑکی;
    device->Hide_کھڑکی = VIVANTE_Hide_کھڑکی;
    device->Destroy_کھڑکی = VIVANTE_Destroy_کھڑکی;

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    device->GL_بھرو_Library = VIVANTE_GLES_بھرو_Library;
    device->GL_Get_Proc_پتہ = VIVANTE_GLES_Get_Proc_پتہ;
    device->GL_UnloadLibrary = VIVANTE_GLES_UnloadLibrary;
    device->GL_CreateContext = VIVANTE_GLES_CreateContext;
    device->GL_MakeCurrent = VIVANTE_GLES_MakeCurrent;
    device->GL_سیٹ_تبادلہ_Interval = VIVANTE_GLES_سیٹ_تبادلہ_Interval;
    device->GL_Get_تبادلہ_Interval = VIVANTE_GLES_Get_تبادلہ_Interval;
    device->GL_تبادلہ_کھڑکی = VIVANTE_GLES_تبادلہ_کھڑکی;
    device->GL_DestroyContext = VIVANTE_GLES_DestroyContext;
#اگر_ختم

#اگر_تعریف_شدہ SDL_VIDEO_VULKAN
    device->Vulkan_بھرو_Library = VIVANTE_Vulkan_بھرو_Library;
    device->Vulkan_UnloadLibrary = VIVANTE_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = VIVANTE_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = VIVANTE_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = VIVANTE_Vulkan_DestroySurface;
#اگر_ختم

    device->PumpEvents = VIVANTE_PumpEvents;

    واپس device;
}

VideoBootStrap VIVANTE_bootstrap = {
    "vivante",
    "Vivante EGL Video Driver",
    VIVANTE_Create,
    تہی, // no ShowMessageBox implementation
    false
};

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/*****************************************************************************/

ساکن bool VIVANTE_جوڑو_Video_Displays(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;
    SDL_VideoDisplay display;
    SDL_Display_منوال منوال;
    SDL_Display_ڈیٹا *ڈیٹا;
    صحیح pitch = 0, bpp = 0;
    غیرعلامتی طویل pixels = 0;

    ڈیٹا = (SDL_Display_ڈیٹا *)SDL_calloc(1, حجم(SDL_Display_ڈیٹا));
    اگر (!ڈیٹا) {
        واپس false;
    }

    SDL_zero(منوال);
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_VIVANTE_VDK
    ڈیٹا->native_display = vdkGetDisplay(videodata->vdk_نجی);

    vdkGetDisplayInfo(ڈیٹا->native_display, &منوال.w, &منوال.h, &pixels, &pitch,
                      &bpp);
#ورنہ
    ڈیٹا->native_display = videodata->fb_Get_Display_By_اشاریہ(0);

    videodata->fbGetDisplayInfo(ڈیٹا->native_display, &منوال.w, &منوال.h,
                                &pixels, &pitch, &bpp);
#اگر_ختم // SDL_VIDEO_DRIVER_VIVANTE_VDK

    انتخاب (bpp) {
    طےشدہ: // Is another format used?
    حالت 32:
        منوال.format = SDL_PIXELFORMAT_ARGB8888;
        توڑو;
    حالت 16:
        منوال.format = SDL_PIXELFORMAT_RGB565;
        توڑو;
    }
    // FIXME: How do we query refresh rate?
    منوال.refresh_شرح = 60.0f;

    SDL_zero(display);
    display.name = VIVANTE_GetDisplayName(_this);
    display.desktop_منوال = منوال;
    display.اندرونی_2 = ڈیٹا;
    اگر (SDL_جوڑو_Video_Display(&display, false) == 0) {
        واپس false;
    }
    واپس true;
}

bool VIVANTE_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_VIVANTE_VDK
    videodata->vdk_نجی = vdkInitialize();
    اگر (!videodata->vdk_نجی) {
        واپس SDL_سیٹ_Error("vdkInitialize() failed");
    }
#ورنہ
    videodata->egl_handle = SDL_بھرو_Object("libEGL.so.1");
    اگر (!videodata->egl_handle) {
        videodata->egl_handle = SDL_بھرو_Object("libEGL.so");
        اگر (!videodata->egl_handle) {
            واپس false;
        }
    }
#تعریف_کرو بھرو_FUNC(TYPE, NAME)                                               \
    videodata->NAME = (TYPE)SDL_بھرو_Function(videodata->egl_handle, #NAME); \
    اگر (!videodata->NAME)                                                   \
        واپس false;

    بھرو_FUNC(EGLNativeDisplayType (EGLAPIENTRY *)(خالی *), fbGetDisplay);
    بھرو_FUNC(EGLNativeDisplayType (EGLAPIENTRY *)(صحیح), fb_Get_Display_By_اشاریہ);
    بھرو_FUNC(خالی (EGLAPIENTRY *)(EGLNativeDisplayType, صحیح *, صحیح *), fbGetDisplayGeometry);
    بھرو_FUNC(خالی (EGLAPIENTRY *)(EGLNativeDisplayType, صحیح *, صحیح *, غیرعلامتی طویل *, صحیح *, صحیح *), fbGetDisplayInfo);
    بھرو_FUNC(خالی (EGLAPIENTRY *)(EGLNativeDisplayType), fbDestroyDisplay);
    بھرو_FUNC(EGLNative_کھڑکی_Type (EGLAPIENTRY *)(EGLNativeDisplayType, صحیح, صحیح, صحیح, صحیح), fb_Create_کھڑکی);
    بھرو_FUNC(خالی (EGLAPIENTRY *)(EGLNative_کھڑکی_Type, صحیح *, صحیح *, صحیح *, صحیح *), fb_Get_کھڑکی_Geometry);
    بھرو_FUNC(خالی (EGLAPIENTRY *)(EGLNative_کھڑکی_Type, صحیح *, صحیح *, صحیح *, صحیح *, صحیح *, غیرعلامتی صحیح *), fb_Get_کھڑکی_Info);
    بھرو_FUNC(خالی (EGLAPIENTRY *)(EGLNative_کھڑکی_Type), fb_Destroy_کھڑکی);
#اگر_ختم

    اگر (!VIVANTE_تیاری_Platform(_this)) {
        واپس false;
    }

    اگر (!VIVANTE_جوڑو_Video_Displays(_this)) {
        واپس false;
    }

    VIVANTE_UpdateDisplayScale(_this);

#اگر_تعریف_شدہ SDL_داخلہ_LINUXEV
    اگر (!SDL_EVDEV_Init()) {
        واپس false;
    }
#اگر_ختم

    واپس true;
}

خالی VIVANTE_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;

#اگر_تعریف_شدہ SDL_داخلہ_LINUXEV
    SDL_EVDEV_Quit();
#اگر_ختم

    VIVANTE_CleanupPlatform(_this);

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_VIVANTE_VDK
    اگر (videodata->vdk_نجی) {
        vdkExit(videodata->vdk_نجی);
        videodata->vdk_نجی = تہی;
    }
#ورنہ
    اگر (videodata->egl_handle) {
        SDL_UnloadObject(videodata->egl_handle);
        videodata->egl_handle = تہی;
    }
#اگر_ختم
}

bool VIVANTE_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props)
{
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;
    SDL_Display_ڈیٹا *displaydata;
    SDL_کھڑکی_ڈیٹا *ڈیٹا;

    displaydata = SDL_Get_Display_Driver_ڈیٹا(SDL_GetPrimaryDisplay());

    // Allocate window internal data
    ڈیٹا = (SDL_کھڑکی_ڈیٹا *)SDL_calloc(1, حجم(SDL_کھڑکی_ڈیٹا));
    اگر (!ڈیٹا) {
        واپس false;
    }

    // Setup driver data for this window
    کھڑکی->اندرونی_2 = ڈیٹا;

    SDL_PropertiesID props = SDL_Get_کھڑکی_Properties(کھڑکی);
    SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_VIVANTE_DISPLAY_اشارہ_گر, displaydata->native_display);

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_VIVANTE_VDK
    ڈیٹا->native_کھڑکی = vdk_Create_کھڑکی(displaydata->native_display, کھڑکی->x, کھڑکی->y, کھڑکی->w, کھڑکی->h);
#ورنہ
    ڈیٹا->native_کھڑکی = videodata->fb_Create_کھڑکی(displaydata->native_display, کھڑکی->x, کھڑکی->y, کھڑکی->w, کھڑکی->h);
#اگر_ختم
    اگر (!ڈیٹا->native_کھڑکی) {
        واپس SDL_سیٹ_Error("VIVANTE: Can't create native window");
    }
    SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_VIVANTE_کھڑکی_اشارہ_گر, ڈیٹا->native_کھڑکی);

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    اگر (کھڑکی->flags & SDL_کھڑکی_OPENGL) {
        ڈیٹا->egl_surface = SDL_EGL_CreateSurface(_this, کھڑکی, ڈیٹا->native_کھڑکی);
        اگر (ڈیٹا->egl_surface == EGL_NO_SURFACE) {
            واپس SDL_سیٹ_Error("VIVANTE: Can't create EGL surface");
        }
    } ورنہ {
        ڈیٹا->egl_surface = EGL_NO_SURFACE;
    }
    SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_VIVANTE_SURFACE_اشارہ_گر, ڈیٹا->egl_surface);
#اگر_ختم

    // Window has been successfully created
    واپس true;
}

خالی VIVANTE_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;
    SDL_کھڑکی_ڈیٹا *ڈیٹا;

    ڈیٹا = کھڑکی->اندرونی_2;
    اگر (ڈیٹا) {
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
        اگر (ڈیٹا->egl_surface != EGL_NO_SURFACE) {
            SDL_EGL_DestroySurface(_this, ڈیٹا->egl_surface);
        }
#اگر_ختم

        اگر (ڈیٹا->native_کھڑکی) {
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_VIVANTE_VDK
            vdk_Destroy_کھڑکی(ڈیٹا->native_کھڑکی);
#ورنہ
            videodata->fb_Destroy_کھڑکی(ڈیٹا->native_کھڑکی);
#اگر_ختم
        }

        SDL_free(ڈیٹا);
    }
    کھڑکی->اندرونی_2 = تہی;
}

خالی VIVANTE_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    vdk_سیٹ_کھڑکی_Title(ڈیٹا->native_کھڑکی, کھڑکی->title);
#اگر_ختم
}

bool VIVANTE_سیٹ_کھڑکی_Position(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    // FIXME
    واپس SDL_Unsupported();
}

خالی VIVANTE_سیٹ_کھڑکی_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    // FIXME
}

خالی VIVANTE_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    vdk_Show_کھڑکی(ڈیٹا->native_کھڑکی);
#اگر_ختم
    SDL_سیٹ_Mouse_Focus(کھڑکی);
    SDL_سیٹ_Keyboard_Focus(کھڑکی);
}

خالی VIVANTE_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    vdk_Hide_کھڑکی(ڈیٹا->native_کھڑکی);
#اگر_ختم
    SDL_سیٹ_Mouse_Focus(تہی);
    SDL_سیٹ_Keyboard_Focus(تہی);
}

/*****************************************************************************/
// SDL event functions
/*****************************************************************************/
خالی VIVANTE_PumpEvents(SDL_VideoDevice *_this)
{
#اگر_تعریف_شدہ SDL_داخلہ_LINUXEV
    SDL_EVDEV_Poll();
#اگر_ختم
}

#اگر_ختم // SDL_VIDEO_DRIVER_VIVANTE
