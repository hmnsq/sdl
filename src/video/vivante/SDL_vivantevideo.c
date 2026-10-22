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

#که_تعریف_شوی SDL_VIDEO_DRIVER_VIVANTE

// SDL internals
#ضمن "../SDL_sysvideo.h"
#ضمن "../../events/SDL_events_c.h"

#که_تعریف_شوی SDL_ننوت_LINUXEV
#ضمن "../../core/linux/SDL_evdev.h"
#د_که_پای

#ضمن "SDL_vivantevideo.h"
#ضمن "SDL_vivanteplatform.h"
#ضمن "SDL_vivanteopengles.h"
#ضمن "SDL_vivantevulkan.h"

ساكن فراغ VIVANTE_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->دننی);
    SDL_free(device);
}

ساكن SDL_VideoDevice *VIVANTE_Create(فراغ)
{
    SDL_VideoDevice *device;
    SDL_Video_معلومات *معلومات;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (!device) {
        أرجع عدم;
    }

    // Initialize internal data
    معلومات = (SDL_Video_معلومات *)SDL_calloc(1, حجم(SDL_Video_معلومات));
    إذا (!معلومات) {
        SDL_free(device);
        أرجع عدم;
    }

    device->دننی = معلومات;

    // Setup amount of available displays
    device->عدد_displays = 0;

    // Set device free function
    device->حرر = VIVANTE_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = VIVANTE_VideoInit;
    device->VideoQuit = VIVANTE_VideoQuit;
    device->CreateSDLWindow = VIVANTE_Create_کړکۍ;
    device->سېټ_کړکۍ_Title = VIVANTE_سېټ_کړکۍ_Title;
    device->سېټ_کړکۍ_Position = VIVANTE_سېټ_کړکۍ_Position;
    device->سېټ_کړکۍ_اندازه = VIVANTE_سېټ_کړکۍ_اندازه;
    device->Show_کړکۍ = VIVANTE_Show_کړکۍ;
    device->Hide_کړکۍ = VIVANTE_Hide_کړکۍ;
    device->Destroy_کړکۍ = VIVANTE_Destroy_کړکۍ;

#که_تعریف_شوی SDL_VIDEO_OPENGL_EGL
    device->GL_بارول_Library = VIVANTE_GLES_بارول_Library;
    device->GL_Get_Proc_پته = VIVANTE_GLES_Get_Proc_پته;
    device->GL_UnloadLibrary = VIVANTE_GLES_UnloadLibrary;
    device->GL_CreateContext = VIVANTE_GLES_CreateContext;
    device->GL_MakeCurrent = VIVANTE_GLES_MakeCurrent;
    device->GL_سېټ_بدلون_Interval = VIVANTE_GLES_سېټ_بدلون_Interval;
    device->GL_Get_بدلون_Interval = VIVANTE_GLES_Get_بدلون_Interval;
    device->GL_بدلون_کړکۍ = VIVANTE_GLES_بدلون_کړکۍ;
    device->GL_DestroyContext = VIVANTE_GLES_DestroyContext;
#د_که_پای

#که_تعریف_شوی SDL_VIDEO_VULKAN
    device->Vulkan_بارول_Library = VIVANTE_Vulkan_بارول_Library;
    device->Vulkan_UnloadLibrary = VIVANTE_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = VIVANTE_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = VIVANTE_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = VIVANTE_Vulkan_DestroySurface;
#د_که_پای

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

ساكن bool VIVANTE_جمع_کړه_Video_Displays(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *videodata = _this->دننی;
    SDL_VideoDisplay display;
    SDL_Display_ډېرپېښ ډېرپېښ;
    SDL_Display_معلومات *معلومات;
    صحيح pitch = 0, bpp = 0;
    بینښه اوږد pixels = 0;

    معلومات = (SDL_Display_معلومات *)SDL_calloc(1, حجم(SDL_Display_معلومات));
    إذا (!معلومات) {
        أرجع false;
    }

    SDL_zero(ډېرپېښ);
#که_تعریف_شوی SDL_VIDEO_DRIVER_VIVANTE_VDK
    معلومات->native_display = vdkGetDisplay(videodata->vdk_شخصي);

    vdkGetDisplayInfo(معلومات->native_display, &ډېرپېښ.w, &ډېرپېښ.h, &pixels, &pitch,
                      &bpp);
#وإلا
    معلومات->native_display = videodata->fb_Get_Display_By_شاخص(0);

    videodata->fbGetDisplayInfo(معلومات->native_display, &ډېرپېښ.w, &ډېرپېښ.h,
                                &pixels, &pitch, &bpp);
#د_که_پای // SDL_VIDEO_DRIVER_VIVANTE_VDK

    بدل (bpp) {
    افتراضي: // Is another format used?
    حالة 32:
        ډېرپېښ.format = SDL_PIXELFORMAT_ARGB8888;
        اكسر;
    حالة 16:
        ډېرپېښ.format = SDL_PIXELFORMAT_RGB565;
        اكسر;
    }
    // FIXME: How do we query refresh rate?
    ډېرپېښ.refresh_شرح = 60.0f;

    SDL_zero(display);
    display.name = VIVANTE_GetDisplayName(_this);
    display.desktop_ډېرپېښ = ډېرپېښ;
    display.دننی = معلومات;
    إذا (SDL_جمع_کړه_Video_Display(&display, false) == 0) {
        أرجع false;
    }
    أرجع true;
}

bool VIVANTE_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *videodata = _this->دننی;

#که_تعریف_شوی SDL_VIDEO_DRIVER_VIVANTE_VDK
    videodata->vdk_شخصي = vdkInitialize();
    إذا (!videodata->vdk_شخصي) {
        أرجع SDL_سېټ_Error("vdkInitialize() failed");
    }
#وإلا
    videodata->egl_handle = SDL_بارول_Object("libEGL.so.1");
    إذا (!videodata->egl_handle) {
        videodata->egl_handle = SDL_بارول_Object("libEGL.so");
        إذا (!videodata->egl_handle) {
            أرجع false;
        }
    }
#تعریف_کړه بارول_FUNC(TYPE, NAME)                                               \
    videodata->NAME = (TYPE)SDL_بارول_Function(videodata->egl_handle, #NAME); \
    إذا (!videodata->NAME)                                                   \
        أرجع false;

    بارول_FUNC(EGLNativeDisplayType (EGLAPIENTRY *)(فراغ *), fbGetDisplay);
    بارول_FUNC(EGLNativeDisplayType (EGLAPIENTRY *)(صحيح), fb_Get_Display_By_شاخص);
    بارول_FUNC(فراغ (EGLAPIENTRY *)(EGLNativeDisplayType, صحيح *, صحيح *), fbGetDisplayGeometry);
    بارول_FUNC(فراغ (EGLAPIENTRY *)(EGLNativeDisplayType, صحيح *, صحيح *, بینښه اوږد *, صحيح *, صحيح *), fbGetDisplayInfo);
    بارول_FUNC(فراغ (EGLAPIENTRY *)(EGLNativeDisplayType), fbDestroyDisplay);
    بارول_FUNC(EGLNative_کړکۍ_Type (EGLAPIENTRY *)(EGLNativeDisplayType, صحيح, صحيح, صحيح, صحيح), fb_Create_کړکۍ);
    بارول_FUNC(فراغ (EGLAPIENTRY *)(EGLNative_کړکۍ_Type, صحيح *, صحيح *, صحيح *, صحيح *), fb_Get_کړکۍ_Geometry);
    بارول_FUNC(فراغ (EGLAPIENTRY *)(EGLNative_کړکۍ_Type, صحيح *, صحيح *, صحيح *, صحيح *, صحيح *, بینښه صحيح *), fb_Get_کړکۍ_Info);
    بارول_FUNC(فراغ (EGLAPIENTRY *)(EGLNative_کړکۍ_Type), fb_Destroy_کړکۍ);
#د_که_پای

    إذا (!VIVANTE_تیاری_Platform(_this)) {
        أرجع false;
    }

    إذا (!VIVANTE_جمع_کړه_Video_Displays(_this)) {
        أرجع false;
    }

    VIVANTE_UpdateDisplayScale(_this);

#که_تعریف_شوی SDL_ننوت_LINUXEV
    إذا (!SDL_EVDEV_Init()) {
        أرجع false;
    }
#د_که_پای

    أرجع true;
}

فراغ VIVANTE_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *videodata = _this->دننی;

#که_تعریف_شوی SDL_ننوت_LINUXEV
    SDL_EVDEV_Quit();
#د_که_پای

    VIVANTE_CleanupPlatform(_this);

#که_تعریف_شوی SDL_VIDEO_DRIVER_VIVANTE_VDK
    إذا (videodata->vdk_شخصي) {
        vdkExit(videodata->vdk_شخصي);
        videodata->vdk_شخصي = عدم;
    }
#وإلا
    إذا (videodata->egl_handle) {
        SDL_UnloadObject(videodata->egl_handle);
        videodata->egl_handle = عدم;
    }
#د_که_پای
}

bool VIVANTE_Create_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID create_props)
{
    SDL_Video_معلومات *videodata = _this->دننی;
    SDL_Display_معلومات *displaydata;
    SDL_کړکۍ_معلومات *معلومات;

    displaydata = SDL_Get_Display_Driver_معلومات(SDL_GetPrimaryDisplay());

    // Allocate window internal data
    معلومات = (SDL_کړکۍ_معلومات *)SDL_calloc(1, حجم(SDL_کړکۍ_معلومات));
    إذا (!معلومات) {
        أرجع false;
    }

    // Setup driver data for this window
    کړکۍ->دننی = معلومات;

    SDL_PropertiesID props = SDL_Get_کړکۍ_Properties(کړکۍ);
    SDL_سېټ_اشاره_ګر_Property(props, SDL_PROP_کړکۍ_VIVANTE_DISPLAY_اشاره_ګر, displaydata->native_display);

#که_تعریف_شوی SDL_VIDEO_DRIVER_VIVANTE_VDK
    معلومات->native_کړکۍ = vdk_Create_کړکۍ(displaydata->native_display, کړکۍ->x, کړکۍ->y, کړکۍ->w, کړکۍ->h);
#وإلا
    معلومات->native_کړکۍ = videodata->fb_Create_کړکۍ(displaydata->native_display, کړکۍ->x, کړکۍ->y, کړکۍ->w, کړکۍ->h);
#د_که_پای
    إذا (!معلومات->native_کړکۍ) {
        أرجع SDL_سېټ_Error("VIVANTE: Can't create native window");
    }
    SDL_سېټ_اشاره_ګر_Property(props, SDL_PROP_کړکۍ_VIVANTE_کړکۍ_اشاره_ګر, معلومات->native_کړکۍ);

#که_تعریف_شوی SDL_VIDEO_OPENGL_EGL
    إذا (کړکۍ->flags & SDL_کړکۍ_OPENGL) {
        معلومات->egl_surface = SDL_EGL_CreateSurface(_this, کړکۍ, معلومات->native_کړکۍ);
        إذا (معلومات->egl_surface == EGL_NO_SURFACE) {
            أرجع SDL_سېټ_Error("VIVANTE: Can't create EGL surface");
        }
    } وإلا {
        معلومات->egl_surface = EGL_NO_SURFACE;
    }
    SDL_سېټ_اشاره_ګر_Property(props, SDL_PROP_کړکۍ_VIVANTE_SURFACE_اشاره_ګر, معلومات->egl_surface);
#د_که_پای

    // Window has been successfully created
    أرجع true;
}

فراغ VIVANTE_Destroy_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_Video_معلومات *videodata = _this->دننی;
    SDL_کړکۍ_معلومات *معلومات;

    معلومات = کړکۍ->دننی;
    إذا (معلومات) {
#که_تعریف_شوی SDL_VIDEO_OPENGL_EGL
        إذا (معلومات->egl_surface != EGL_NO_SURFACE) {
            SDL_EGL_DestroySurface(_this, معلومات->egl_surface);
        }
#د_که_پای

        إذا (معلومات->native_کړکۍ) {
#که_تعریف_شوی SDL_VIDEO_DRIVER_VIVANTE_VDK
            vdk_Destroy_کړکۍ(معلومات->native_کړکۍ);
#وإلا
            videodata->fb_Destroy_کړکۍ(معلومات->native_کړکۍ);
#د_که_پای
        }

        SDL_free(معلومات);
    }
    کړکۍ->دننی = عدم;
}

فراغ VIVANTE_سېټ_کړکۍ_Title(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
#که_تعریف_شوی SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    vdk_سېټ_کړکۍ_Title(معلومات->native_کړکۍ, کړکۍ->title);
#د_که_پای
}

bool VIVANTE_سېټ_کړکۍ_Position(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    // FIXME
    أرجع SDL_Unsupported();
}

فراغ VIVANTE_سېټ_کړکۍ_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    // FIXME
}

فراغ VIVANTE_Show_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
#که_تعریف_شوی SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    vdk_Show_کړکۍ(معلومات->native_کړکۍ);
#د_که_پای
    SDL_سېټ_Mouse_Focus(کړکۍ);
    SDL_سېټ_Keyboard_Focus(کړکۍ);
}

فراغ VIVANTE_Hide_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
#که_تعریف_شوی SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    vdk_Hide_کړکۍ(معلومات->native_کړکۍ);
#د_که_پای
    SDL_سېټ_Mouse_Focus(عدم);
    SDL_سېټ_Keyboard_Focus(عدم);
}

/*****************************************************************************/
// SDL event functions
/*****************************************************************************/
فراغ VIVANTE_PumpEvents(SDL_VideoDevice *_this)
{
#که_تعریف_شوی SDL_ننوت_LINUXEV
    SDL_EVDEV_Poll();
#د_که_پای
}

#د_که_پای // SDL_VIDEO_DRIVER_VIVANTE
