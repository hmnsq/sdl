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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_VIVANTE

// SDL internals
#ضمن "../SDL_sysvideo.h"
#ضمن "../../events/SDL_events_c.h"

#جے_تعریف_شدہ SDL_داخلہ_LINUXEV
#ضمن "../../core/linux/SDL_evdev.h"
#جے_انت

#ضمن "SDL_vivantevideo.h"
#ضمن "SDL_vivanteplatform.h"
#ضمن "SDL_vivanteopengles.h"
#ضمن "SDL_vivantevulkan.h"

ساكن فراغ VIVANTE_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->اندرونی);
    SDL_free(device);
}

ساكن SDL_VideoDevice *VIVANTE_Create(فراغ)
{
    SDL_VideoDevice *device;
    SDL_Video_انکڑے *انکڑے;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (!device) {
        أرجع عدم;
    }

    // Initialize internal data
    انکڑے = (SDL_Video_انکڑے *)SDL_calloc(1, حجم(SDL_Video_انکڑے));
    إذا (!انکڑے) {
        SDL_free(device);
        أرجع عدم;
    }

    device->اندرونی = انکڑے;

    // Setup amount of available displays
    device->عدد_displays = 0;

    // Set device free function
    device->حرر = VIVANTE_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = VIVANTE_VideoInit;
    device->VideoQuit = VIVANTE_VideoQuit;
    device->CreateSDLWindow = VIVANTE_Create_کھڑکی;
    device->سیٹ_کھڑکی_Title = VIVANTE_سیٹ_کھڑکی_Title;
    device->سیٹ_کھڑکی_Position = VIVANTE_سیٹ_کھڑکی_Position;
    device->سیٹ_کھڑکی_ناپ = VIVANTE_سیٹ_کھڑکی_ناپ;
    device->Show_کھڑکی = VIVANTE_Show_کھڑکی;
    device->Hide_کھڑکی = VIVANTE_Hide_کھڑکی;
    device->Destroy_کھڑکی = VIVANTE_Destroy_کھڑکی;

#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    device->GL_لدو_Library = VIVANTE_GLES_لدو_Library;
    device->GL_Get_Proc_پتہ = VIVANTE_GLES_Get_Proc_پتہ;
    device->GL_UnloadLibrary = VIVANTE_GLES_UnloadLibrary;
    device->GL_CreateContext = VIVANTE_GLES_CreateContext;
    device->GL_MakeCurrent = VIVANTE_GLES_MakeCurrent;
    device->GL_سیٹ_وٹاندرا_Interval = VIVANTE_GLES_سیٹ_وٹاندرا_Interval;
    device->GL_Get_وٹاندرا_Interval = VIVANTE_GLES_Get_وٹاندرا_Interval;
    device->GL_وٹاندرا_کھڑکی = VIVANTE_GLES_وٹاندرا_کھڑکی;
    device->GL_DestroyContext = VIVANTE_GLES_DestroyContext;
#جے_انت

#جے_تعریف_شدہ SDL_VIDEO_VULKAN
    device->Vulkan_لدو_Library = VIVANTE_Vulkan_لدو_Library;
    device->Vulkan_UnloadLibrary = VIVANTE_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = VIVANTE_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = VIVANTE_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = VIVANTE_Vulkan_DestroySurface;
#جے_انت

    device->PumpEvents = VIVANTE_PumpEvents;

    أرجع device;
}

VideoBootStrap VIVANTE_bootstrap = {
    "vivante",
    "Vivante EGL Video Driver",
    VIVANTE_Create,
    عدم, // no ShowMessageBox implementation
    false
};

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/*****************************************************************************/

ساكن bool VIVANTE_جوڑو_Video_Displays(SDL_VideoDevice *_this)
{
    SDL_Video_انکڑے *videodata = _this->اندرونی;
    SDL_VideoDisplay display;
    SDL_Display_منوال منوال;
    SDL_Display_انکڑے *انکڑے;
    صحيح pitch = 0, bpp = 0;
    بنانشانی لما pixels = 0;

    انکڑے = (SDL_Display_انکڑے *)SDL_calloc(1, حجم(SDL_Display_انکڑے));
    إذا (!انکڑے) {
        أرجع false;
    }

    SDL_zero(منوال);
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_VIVANTE_VDK
    انکڑے->native_display = vdkGetDisplay(videodata->vdk_نجی);

    vdkGetDisplayInfo(انکڑے->native_display, &منوال.w, &منوال.h, &pixels, &pitch,
                      &bpp);
#وإلا
    انکڑے->native_display = videodata->fb_Get_Display_By_اشاریہ(0);

    videodata->fbGetDisplayInfo(انکڑے->native_display, &منوال.w, &منوال.h,
                                &pixels, &pitch, &bpp);
#جے_انت // SDL_VIDEO_DRIVER_VIVANTE_VDK

    بدل (bpp) {
    افتراضي: // Is another format used?
    حالة 32:
        منوال.format = SDL_PIXELFORMAT_ARGB8888;
        اكسر;
    حالة 16:
        منوال.format = SDL_PIXELFORMAT_RGB565;
        اكسر;
    }
    // FIXME: How do we query refresh rate?
    منوال.refresh_شرح = 60.0f;

    SDL_zero(display);
    display.name = VIVANTE_GetDisplayName(_this);
    display.desktop_منوال = منوال;
    display.اندرونی = انکڑے;
    إذا (SDL_جوڑو_Video_Display(&display, false) == 0) {
        أرجع false;
    }
    أرجع true;
}

bool VIVANTE_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_انکڑے *videodata = _this->اندرونی;

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_VIVANTE_VDK
    videodata->vdk_نجی = vdkInitialize();
    إذا (!videodata->vdk_نجی) {
        أرجع SDL_سیٹ_Error("vdkInitialize() failed");
    }
#وإلا
    videodata->egl_handle = SDL_لدو_Object("libEGL.so.1");
    إذا (!videodata->egl_handle) {
        videodata->egl_handle = SDL_لدو_Object("libEGL.so");
        إذا (!videodata->egl_handle) {
            أرجع false;
        }
    }
#تعریف_کرو لدو_FUNC(TYPE, NAME)                                               \
    videodata->NAME = (TYPE)SDL_لدو_Function(videodata->egl_handle, #NAME); \
    إذا (!videodata->NAME)                                                   \
        أرجع false;

    لدو_FUNC(EGLNativeDisplayType (EGLAPIENTRY *)(فراغ *), fbGetDisplay);
    لدو_FUNC(EGLNativeDisplayType (EGLAPIENTRY *)(صحيح), fb_Get_Display_By_اشاریہ);
    لدو_FUNC(فراغ (EGLAPIENTRY *)(EGLNativeDisplayType, صحيح *, صحيح *), fbGetDisplayGeometry);
    لدو_FUNC(فراغ (EGLAPIENTRY *)(EGLNativeDisplayType, صحيح *, صحيح *, بنانشانی لما *, صحيح *, صحيح *), fbGetDisplayInfo);
    لدو_FUNC(فراغ (EGLAPIENTRY *)(EGLNativeDisplayType), fbDestroyDisplay);
    لدو_FUNC(EGLNative_کھڑکی_Type (EGLAPIENTRY *)(EGLNativeDisplayType, صحيح, صحيح, صحيح, صحيح), fb_Create_کھڑکی);
    لدو_FUNC(فراغ (EGLAPIENTRY *)(EGLNative_کھڑکی_Type, صحيح *, صحيح *, صحيح *, صحيح *), fb_Get_کھڑکی_Geometry);
    لدو_FUNC(فراغ (EGLAPIENTRY *)(EGLNative_کھڑکی_Type, صحيح *, صحيح *, صحيح *, صحيح *, صحيح *, بنانشانی صحيح *), fb_Get_کھڑکی_Info);
    لدو_FUNC(فراغ (EGLAPIENTRY *)(EGLNative_کھڑکی_Type), fb_Destroy_کھڑکی);
#جے_انت

    إذا (!VIVANTE_تیاری_Platform(_this)) {
        أرجع false;
    }

    إذا (!VIVANTE_جوڑو_Video_Displays(_this)) {
        أرجع false;
    }

    VIVANTE_UpdateDisplayScale(_this);

#جے_تعریف_شدہ SDL_داخلہ_LINUXEV
    إذا (!SDL_EVDEV_Init()) {
        أرجع false;
    }
#جے_انت

    أرجع true;
}

فراغ VIVANTE_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_انکڑے *videodata = _this->اندرونی;

#جے_تعریف_شدہ SDL_داخلہ_LINUXEV
    SDL_EVDEV_Quit();
#جے_انت

    VIVANTE_CleanupPlatform(_this);

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_VIVANTE_VDK
    إذا (videodata->vdk_نجی) {
        vdkExit(videodata->vdk_نجی);
        videodata->vdk_نجی = عدم;
    }
#وإلا
    إذا (videodata->egl_handle) {
        SDL_UnloadObject(videodata->egl_handle);
        videodata->egl_handle = عدم;
    }
#جے_انت
}

bool VIVANTE_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props)
{
    SDL_Video_انکڑے *videodata = _this->اندرونی;
    SDL_Display_انکڑے *displaydata;
    SDL_کھڑکی_انکڑے *انکڑے;

    displaydata = SDL_Get_Display_Driver_انکڑے(SDL_GetPrimaryDisplay());

    // Allocate window internal data
    انکڑے = (SDL_کھڑکی_انکڑے *)SDL_calloc(1, حجم(SDL_کھڑکی_انکڑے));
    إذا (!انکڑے) {
        أرجع false;
    }

    // Setup driver data for this window
    کھڑکی->اندرونی = انکڑے;

    SDL_PropertiesID props = SDL_Get_کھڑکی_Properties(کھڑکی);
    SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_VIVANTE_DISPLAY_اشارہ_گر, displaydata->native_display);

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_VIVANTE_VDK
    انکڑے->native_کھڑکی = vdk_Create_کھڑکی(displaydata->native_display, کھڑکی->x, کھڑکی->y, کھڑکی->w, کھڑکی->h);
#وإلا
    انکڑے->native_کھڑکی = videodata->fb_Create_کھڑکی(displaydata->native_display, کھڑکی->x, کھڑکی->y, کھڑکی->w, کھڑکی->h);
#جے_انت
    إذا (!انکڑے->native_کھڑکی) {
        أرجع SDL_سیٹ_Error("VIVANTE: Can't create native window");
    }
    SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_VIVANTE_کھڑکی_اشارہ_گر, انکڑے->native_کھڑکی);

#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    إذا (کھڑکی->flags & SDL_کھڑکی_OPENGL) {
        انکڑے->egl_surface = SDL_EGL_CreateSurface(_this, کھڑکی, انکڑے->native_کھڑکی);
        إذا (انکڑے->egl_surface == EGL_NO_SURFACE) {
            أرجع SDL_سیٹ_Error("VIVANTE: Can't create EGL surface");
        }
    } وإلا {
        انکڑے->egl_surface = EGL_NO_SURFACE;
    }
    SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_VIVANTE_SURFACE_اشارہ_گر, انکڑے->egl_surface);
#جے_انت

    // Window has been successfully created
    أرجع true;
}

فراغ VIVANTE_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_انکڑے *videodata = _this->اندرونی;
    SDL_کھڑکی_انکڑے *انکڑے;

    انکڑے = کھڑکی->اندرونی;
    إذا (انکڑے) {
#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
        إذا (انکڑے->egl_surface != EGL_NO_SURFACE) {
            SDL_EGL_DestroySurface(_this, انکڑے->egl_surface);
        }
#جے_انت

        إذا (انکڑے->native_کھڑکی) {
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_VIVANTE_VDK
            vdk_Destroy_کھڑکی(انکڑے->native_کھڑکی);
#وإلا
            videodata->fb_Destroy_کھڑکی(انکڑے->native_کھڑکی);
#جے_انت
        }

        SDL_free(انکڑے);
    }
    کھڑکی->اندرونی = عدم;
}

فراغ VIVANTE_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    vdk_سیٹ_کھڑکی_Title(انکڑے->native_کھڑکی, کھڑکی->title);
#جے_انت
}

bool VIVANTE_سیٹ_کھڑکی_Position(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    // FIXME
    أرجع SDL_Unsupported();
}

فراغ VIVANTE_سیٹ_کھڑکی_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    // FIXME
}

فراغ VIVANTE_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    vdk_Show_کھڑکی(انکڑے->native_کھڑکی);
#جے_انت
    SDL_سیٹ_Mouse_Focus(کھڑکی);
    SDL_سیٹ_Keyboard_Focus(کھڑکی);
}

فراغ VIVANTE_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    vdk_Hide_کھڑکی(انکڑے->native_کھڑکی);
#جے_انت
    SDL_سیٹ_Mouse_Focus(عدم);
    SDL_سیٹ_Keyboard_Focus(عدم);
}

/*****************************************************************************/
// SDL event functions
/*****************************************************************************/
فراغ VIVANTE_PumpEvents(SDL_VideoDevice *_this)
{
#جے_تعریف_شدہ SDL_داخلہ_LINUXEV
    SDL_EVDEV_Poll();
#جے_انت
}

#جے_انت // SDL_VIDEO_DRIVER_VIVANTE
