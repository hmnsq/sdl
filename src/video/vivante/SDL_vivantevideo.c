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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_VIVANTE

// SDL internals
#ضمن "../SDL_sysvideo.h"
#ضمن "../../events/SDL_events_c.h"

#اگر_تعریف_شده SDL_درون_داد_LINUXEV
#ضمن "../../core/linux/SDL_evdev.h"
#پایان_اگر

#ضمن "SDL_vivantevideo.h"
#ضمن "SDL_vivanteplatform.h"
#ضمن "SDL_vivanteopengles.h"
#ضمن "SDL_vivantevulkan.h"

ساكن فراغ VIVANTE_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->داخلی);
    SDL_free(device);
}

ساكن SDL_VideoDevice *VIVANTE_Create(فراغ)
{
    SDL_VideoDevice *device;
    SDL_Video_داده *داده;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (!device) {
        أرجع عدم;
    }

    // Initialize internal data
    داده = (SDL_Video_داده *)SDL_calloc(1, حجم(SDL_Video_داده));
    إذا (!داده) {
        SDL_free(device);
        أرجع عدم;
    }

    device->داخلی = داده;

    // Setup amount of available displays
    device->رقم_displays = 0;

    // Set device free function
    device->حرر = VIVANTE_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = VIVANTE_VideoInit;
    device->VideoQuit = VIVANTE_VideoQuit;
    device->CreateSDLWindow = VIVANTE_Create_پنجره;
    device->مجموعه_پنجره_Title = VIVANTE_مجموعه_پنجره_Title;
    device->مجموعه_پنجره_Position = VIVANTE_مجموعه_پنجره_Position;
    device->مجموعه_پنجره_اندازه = VIVANTE_مجموعه_پنجره_اندازه;
    device->Show_پنجره = VIVANTE_Show_پنجره;
    device->Hide_پنجره = VIVANTE_Hide_پنجره;
    device->Destroy_پنجره = VIVANTE_Destroy_پنجره;

#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
    device->GL_بارگیری_Library = VIVANTE_GLES_بارگیری_Library;
    device->GL_Get_Proc_آدرس = VIVANTE_GLES_Get_Proc_آدرس;
    device->GL_UnloadLibrary = VIVANTE_GLES_UnloadLibrary;
    device->GL_CreateContext = VIVANTE_GLES_CreateContext;
    device->GL_MakeCurrent = VIVANTE_GLES_MakeCurrent;
    device->GL_مجموعه_جابجا_Interval = VIVANTE_GLES_مجموعه_جابجا_Interval;
    device->GL_Get_جابجا_Interval = VIVANTE_GLES_Get_جابجا_Interval;
    device->GL_جابجا_پنجره = VIVANTE_GLES_جابجا_پنجره;
    device->GL_DestroyContext = VIVANTE_GLES_DestroyContext;
#پایان_اگر

#اگر_تعریف_شده SDL_VIDEO_VULKAN
    device->Vulkan_بارگیری_Library = VIVANTE_Vulkan_بارگیری_Library;
    device->Vulkan_UnloadLibrary = VIVANTE_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = VIVANTE_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = VIVANTE_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = VIVANTE_Vulkan_DestroySurface;
#پایان_اگر

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

ساكن bool VIVANTE_جمع_کن_Video_Displays(SDL_VideoDevice *_this)
{
    SDL_Video_داده *videodata = _this->داخلی;
    SDL_VideoDisplay display;
    SDL_Display_نما نما;
    SDL_Display_داده *داده;
    صحيح pitch = 0, bpp = 0;
    بیعلامت دراز pixels = 0;

    داده = (SDL_Display_داده *)SDL_calloc(1, حجم(SDL_Display_داده));
    إذا (!داده) {
        أرجع false;
    }

    SDL_zero(نما);
#اگر_تعریف_شده SDL_VIDEO_DRIVER_VIVANTE_VDK
    داده->native_display = vdkGetDisplay(videodata->vdk_خصوصی);

    vdkGetDisplayInfo(داده->native_display, &نما.w, &نما.h, &pixels, &pitch,
                      &bpp);
#وإلا
    داده->native_display = videodata->fb_Get_Display_By_شاخص(0);

    videodata->fbGetDisplayInfo(داده->native_display, &نما.w, &نما.h,
                                &pixels, &pitch, &bpp);
#پایان_اگر // SDL_VIDEO_DRIVER_VIVANTE_VDK

    بدل (bpp) {
    افتراضي: // Is another format used?
    حالة 32:
        نما.format = SDL_PIXELFORMAT_ARGB8888;
        اكسر;
    حالة 16:
        نما.format = SDL_PIXELFORMAT_RGB565;
        اكسر;
    }
    // FIXME: How do we query refresh rate?
    نما.refresh_نرخ = 60.0f;

    SDL_zero(display);
    display.name = VIVANTE_GetDisplayName(_this);
    display.desktop_نما = نما;
    display.داخلی = داده;
    إذا (SDL_جمع_کن_Video_Display(&display, false) == 0) {
        أرجع false;
    }
    أرجع true;
}

bool VIVANTE_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_داده *videodata = _this->داخلی;

#اگر_تعریف_شده SDL_VIDEO_DRIVER_VIVANTE_VDK
    videodata->vdk_خصوصی = vdkInitialize();
    إذا (!videodata->vdk_خصوصی) {
        أرجع SDL_مجموعه_Error("vdkInitialize() failed");
    }
#وإلا
    videodata->egl_handle = SDL_بارگیری_Object("libEGL.so.1");
    إذا (!videodata->egl_handle) {
        videodata->egl_handle = SDL_بارگیری_Object("libEGL.so");
        إذا (!videodata->egl_handle) {
            أرجع false;
        }
    }
#تعریف_کن بارگیری_FUNC(TYPE, NAME)                                               \
    videodata->NAME = (TYPE)SDL_بارگیری_Function(videodata->egl_handle, #NAME); \
    إذا (!videodata->NAME)                                                   \
        أرجع false;

    بارگیری_FUNC(EGLNativeDisplayType (EGLAPIENTRY *)(فراغ *), fbGetDisplay);
    بارگیری_FUNC(EGLNativeDisplayType (EGLAPIENTRY *)(صحيح), fb_Get_Display_By_شاخص);
    بارگیری_FUNC(فراغ (EGLAPIENTRY *)(EGLNativeDisplayType, صحيح *, صحيح *), fbGetDisplayGeometry);
    بارگیری_FUNC(فراغ (EGLAPIENTRY *)(EGLNativeDisplayType, صحيح *, صحيح *, بیعلامت دراز *, صحيح *, صحيح *), fbGetDisplayInfo);
    بارگیری_FUNC(فراغ (EGLAPIENTRY *)(EGLNativeDisplayType), fbDestroyDisplay);
    بارگیری_FUNC(EGLNative_پنجره_Type (EGLAPIENTRY *)(EGLNativeDisplayType, صحيح, صحيح, صحيح, صحيح), fb_Create_پنجره);
    بارگیری_FUNC(فراغ (EGLAPIENTRY *)(EGLNative_پنجره_Type, صحيح *, صحيح *, صحيح *, صحيح *), fb_Get_پنجره_Geometry);
    بارگیری_FUNC(فراغ (EGLAPIENTRY *)(EGLNative_پنجره_Type, صحيح *, صحيح *, صحيح *, صحيح *, صحيح *, بیعلامت صحيح *), fb_Get_پنجره_Info);
    بارگیری_FUNC(فراغ (EGLAPIENTRY *)(EGLNative_پنجره_Type), fb_Destroy_پنجره);
#پایان_اگر

    إذا (!VIVANTE_راهاندازی_Platform(_this)) {
        أرجع false;
    }

    إذا (!VIVANTE_جمع_کن_Video_Displays(_this)) {
        أرجع false;
    }

    VIVANTE_UpdateDisplayScale(_this);

#اگر_تعریف_شده SDL_درون_داد_LINUXEV
    إذا (!SDL_EVDEV_Init()) {
        أرجع false;
    }
#پایان_اگر

    أرجع true;
}

فراغ VIVANTE_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_داده *videodata = _this->داخلی;

#اگر_تعریف_شده SDL_درون_داد_LINUXEV
    SDL_EVDEV_Quit();
#پایان_اگر

    VIVANTE_CleanupPlatform(_this);

#اگر_تعریف_شده SDL_VIDEO_DRIVER_VIVANTE_VDK
    إذا (videodata->vdk_خصوصی) {
        vdkExit(videodata->vdk_خصوصی);
        videodata->vdk_خصوصی = عدم;
    }
#وإلا
    إذا (videodata->egl_handle) {
        SDL_UnloadObject(videodata->egl_handle);
        videodata->egl_handle = عدم;
    }
#پایان_اگر
}

bool VIVANTE_Create_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID create_props)
{
    SDL_Video_داده *videodata = _this->داخلی;
    SDL_Display_داده *displaydata;
    SDL_پنجره_داده *داده;

    displaydata = SDL_Get_Display_Driver_داده(SDL_GetPrimaryDisplay());

    // Allocate window internal data
    داده = (SDL_پنجره_داده *)SDL_calloc(1, حجم(SDL_پنجره_داده));
    إذا (!داده) {
        أرجع false;
    }

    // Setup driver data for this window
    پنجره->داخلی = داده;

    SDL_PropertiesID props = SDL_Get_پنجره_Properties(پنجره);
    SDL_مجموعه_اشاره_گر_Property(props, SDL_PROP_پنجره_VIVANTE_DISPLAY_اشاره_گر, displaydata->native_display);

#اگر_تعریف_شده SDL_VIDEO_DRIVER_VIVANTE_VDK
    داده->native_پنجره = vdk_Create_پنجره(displaydata->native_display, پنجره->x, پنجره->y, پنجره->w, پنجره->h);
#وإلا
    داده->native_پنجره = videodata->fb_Create_پنجره(displaydata->native_display, پنجره->x, پنجره->y, پنجره->w, پنجره->h);
#پایان_اگر
    إذا (!داده->native_پنجره) {
        أرجع SDL_مجموعه_Error("VIVANTE: Can't create native window");
    }
    SDL_مجموعه_اشاره_گر_Property(props, SDL_PROP_پنجره_VIVANTE_پنجره_اشاره_گر, داده->native_پنجره);

#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
    إذا (پنجره->flags & SDL_پنجره_OPENGL) {
        داده->egl_surface = SDL_EGL_CreateSurface(_this, پنجره, داده->native_پنجره);
        إذا (داده->egl_surface == EGL_NO_SURFACE) {
            أرجع SDL_مجموعه_Error("VIVANTE: Can't create EGL surface");
        }
    } وإلا {
        داده->egl_surface = EGL_NO_SURFACE;
    }
    SDL_مجموعه_اشاره_گر_Property(props, SDL_PROP_پنجره_VIVANTE_SURFACE_اشاره_گر, داده->egl_surface);
#پایان_اگر

    // Window has been successfully created
    أرجع true;
}

فراغ VIVANTE_Destroy_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_Video_داده *videodata = _this->داخلی;
    SDL_پنجره_داده *داده;

    داده = پنجره->داخلی;
    إذا (داده) {
#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
        إذا (داده->egl_surface != EGL_NO_SURFACE) {
            SDL_EGL_DestroySurface(_this, داده->egl_surface);
        }
#پایان_اگر

        إذا (داده->native_پنجره) {
#اگر_تعریف_شده SDL_VIDEO_DRIVER_VIVANTE_VDK
            vdk_Destroy_پنجره(داده->native_پنجره);
#وإلا
            videodata->fb_Destroy_پنجره(داده->native_پنجره);
#پایان_اگر
        }

        SDL_free(داده);
    }
    پنجره->داخلی = عدم;
}

فراغ VIVANTE_مجموعه_پنجره_Title(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
#اگر_تعریف_شده SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_پنجره_داده *داده = پنجره->داخلی;
    vdk_مجموعه_پنجره_Title(داده->native_پنجره, پنجره->title);
#پایان_اگر
}

bool VIVANTE_مجموعه_پنجره_Position(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    // FIXME
    أرجع SDL_Unsupported();
}

فراغ VIVANTE_مجموعه_پنجره_اندازه(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    // FIXME
}

فراغ VIVANTE_Show_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
#اگر_تعریف_شده SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_پنجره_داده *داده = پنجره->داخلی;
    vdk_Show_پنجره(داده->native_پنجره);
#پایان_اگر
    SDL_مجموعه_Mouse_Focus(پنجره);
    SDL_مجموعه_Keyboard_Focus(پنجره);
}

فراغ VIVANTE_Hide_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
#اگر_تعریف_شده SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_پنجره_داده *داده = پنجره->داخلی;
    vdk_Hide_پنجره(داده->native_پنجره);
#پایان_اگر
    SDL_مجموعه_Mouse_Focus(عدم);
    SDL_مجموعه_Keyboard_Focus(عدم);
}

/*****************************************************************************/
// SDL event functions
/*****************************************************************************/
فراغ VIVANTE_PumpEvents(SDL_VideoDevice *_this)
{
#اگر_تعریف_شده SDL_درون_داد_LINUXEV
    SDL_EVDEV_Poll();
#پایان_اگر
}

#پایان_اگر // SDL_VIDEO_DRIVER_VIVANTE
