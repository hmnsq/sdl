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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_VIVANTE

// SDL internals
#ضمن "../SDL_sysvideo.h"
#ضمن "../../events/SDL_events_c.h"

#جيڪڏهن_وصف_ٿيل SDL_داخلا_LINUXEV
#ضمن "../../core/linux/SDL_evdev.h"
#جيڪڏهن_پورو

#ضمن "SDL_vivantevideo.h"
#ضمن "SDL_vivanteplatform.h"
#ضمن "SDL_vivanteopengles.h"
#ضمن "SDL_vivantevulkan.h"

ساكن فراغ VIVANTE_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->اندروني);
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

    device->اندروني = معلومات;

    // Setup amount of available displays
    device->انگ_displays = 0;

    // Set device free function
    device->حرر = VIVANTE_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = VIVANTE_VideoInit;
    device->VideoQuit = VIVANTE_VideoQuit;
    device->CreateSDLWindow = VIVANTE_Create_دري;
    device->سيٽ_دري_Title = VIVANTE_سيٽ_دري_Title;
    device->سيٽ_دري_Position = VIVANTE_سيٽ_دري_Position;
    device->سيٽ_دري_سائيز = VIVANTE_سيٽ_دري_سائيز;
    device->Show_دري = VIVANTE_Show_دري;
    device->Hide_دري = VIVANTE_Hide_دري;
    device->Destroy_دري = VIVANTE_Destroy_دري;

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
    device->GL_ڀريو_Library = VIVANTE_GLES_ڀريو_Library;
    device->GL_Get_Proc_پتو = VIVANTE_GLES_Get_Proc_پتو;
    device->GL_UnloadLibrary = VIVANTE_GLES_UnloadLibrary;
    device->GL_CreateContext = VIVANTE_GLES_CreateContext;
    device->GL_MakeCurrent = VIVANTE_GLES_MakeCurrent;
    device->GL_سيٽ_مٽا_سٽا_Interval = VIVANTE_GLES_سيٽ_مٽا_سٽا_Interval;
    device->GL_Get_مٽا_سٽا_Interval = VIVANTE_GLES_Get_مٽا_سٽا_Interval;
    device->GL_مٽا_سٽا_دري = VIVANTE_GLES_مٽا_سٽا_دري;
    device->GL_DestroyContext = VIVANTE_GLES_DestroyContext;
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_VULKAN
    device->Vulkan_ڀريو_Library = VIVANTE_Vulkan_ڀريو_Library;
    device->Vulkan_UnloadLibrary = VIVANTE_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = VIVANTE_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = VIVANTE_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = VIVANTE_Vulkan_DestroySurface;
#جيڪڏهن_پورو

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

ساكن bool VIVANTE_جوڙيو_Video_Displays(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *videodata = _this->اندروني;
    SDL_VideoDisplay display;
    SDL_Display_گهڻائي گهڻائي;
    SDL_Display_معلومات *معلومات;
    صحيح pitch = 0, bpp = 0;
    بنانشان ڊگهو pixels = 0;

    معلومات = (SDL_Display_معلومات *)SDL_calloc(1, حجم(SDL_Display_معلومات));
    إذا (!معلومات) {
        أرجع false;
    }

    SDL_zero(گهڻائي);
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_VIVANTE_VDK
    معلومات->native_display = vdkGetDisplay(videodata->vdk_ذاتي);

    vdkGetDisplayInfo(معلومات->native_display, &گهڻائي.w, &گهڻائي.h, &pixels, &pitch,
                      &bpp);
#وإلا
    معلومات->native_display = videodata->fb_Get_Display_By_اشاريو(0);

    videodata->fbGetDisplayInfo(معلومات->native_display, &گهڻائي.w, &گهڻائي.h,
                                &pixels, &pitch, &bpp);
#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_VIVANTE_VDK

    بدل (bpp) {
    افتراضي: // Is another format used?
    حالة 32:
        گهڻائي.format = SDL_PIXELFORMAT_ARGB8888;
        اكسر;
    حالة 16:
        گهڻائي.format = SDL_PIXELFORMAT_RGB565;
        اكسر;
    }
    // FIXME: How do we query refresh rate?
    گهڻائي.refresh_شرح = 60.0f;

    SDL_zero(display);
    display.name = VIVANTE_GetDisplayName(_this);
    display.desktop_گهڻائي = گهڻائي;
    display.اندروني = معلومات;
    إذا (SDL_جوڙيو_Video_Display(&display, false) == 0) {
        أرجع false;
    }
    أرجع true;
}

bool VIVANTE_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *videodata = _this->اندروني;

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_VIVANTE_VDK
    videodata->vdk_ذاتي = vdkInitialize();
    إذا (!videodata->vdk_ذاتي) {
        أرجع SDL_سيٽ_Error("vdkInitialize() failed");
    }
#وإلا
    videodata->egl_handle = SDL_ڀريو_Object("libEGL.so.1");
    إذا (!videodata->egl_handle) {
        videodata->egl_handle = SDL_ڀريو_Object("libEGL.so");
        إذا (!videodata->egl_handle) {
            أرجع false;
        }
    }
#وصف_ڪريو ڀريو_FUNC(TYPE, NAME)                                               \
    videodata->NAME = (TYPE)SDL_ڀريو_Function(videodata->egl_handle, #NAME); \
    إذا (!videodata->NAME)                                                   \
        أرجع false;

    ڀريو_FUNC(EGLNativeDisplayType (EGLAPIENTRY *)(فراغ *), fbGetDisplay);
    ڀريو_FUNC(EGLNativeDisplayType (EGLAPIENTRY *)(صحيح), fb_Get_Display_By_اشاريو);
    ڀريو_FUNC(فراغ (EGLAPIENTRY *)(EGLNativeDisplayType, صحيح *, صحيح *), fbGetDisplayGeometry);
    ڀريو_FUNC(فراغ (EGLAPIENTRY *)(EGLNativeDisplayType, صحيح *, صحيح *, بنانشان ڊگهو *, صحيح *, صحيح *), fbGetDisplayInfo);
    ڀريو_FUNC(فراغ (EGLAPIENTRY *)(EGLNativeDisplayType), fbDestroyDisplay);
    ڀريو_FUNC(EGLNative_دري_Type (EGLAPIENTRY *)(EGLNativeDisplayType, صحيح, صحيح, صحيح, صحيح), fb_Create_دري);
    ڀريو_FUNC(فراغ (EGLAPIENTRY *)(EGLNative_دري_Type, صحيح *, صحيح *, صحيح *, صحيح *), fb_Get_دري_Geometry);
    ڀريو_FUNC(فراغ (EGLAPIENTRY *)(EGLNative_دري_Type, صحيح *, صحيح *, صحيح *, صحيح *, صحيح *, بنانشان صحيح *), fb_Get_دري_Info);
    ڀريو_FUNC(فراغ (EGLAPIENTRY *)(EGLNative_دري_Type), fb_Destroy_دري);
#جيڪڏهن_پورو

    إذا (!VIVANTE_تياري_Platform(_this)) {
        أرجع false;
    }

    إذا (!VIVANTE_جوڙيو_Video_Displays(_this)) {
        أرجع false;
    }

    VIVANTE_UpdateDisplayScale(_this);

#جيڪڏهن_وصف_ٿيل SDL_داخلا_LINUXEV
    إذا (!SDL_EVDEV_Init()) {
        أرجع false;
    }
#جيڪڏهن_پورو

    أرجع true;
}

فراغ VIVANTE_VideoQuit(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *videodata = _this->اندروني;

#جيڪڏهن_وصف_ٿيل SDL_داخلا_LINUXEV
    SDL_EVDEV_Quit();
#جيڪڏهن_پورو

    VIVANTE_CleanupPlatform(_this);

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_VIVANTE_VDK
    إذا (videodata->vdk_ذاتي) {
        vdkExit(videodata->vdk_ذاتي);
        videodata->vdk_ذاتي = عدم;
    }
#وإلا
    إذا (videodata->egl_handle) {
        SDL_UnloadObject(videodata->egl_handle);
        videodata->egl_handle = عدم;
    }
#جيڪڏهن_پورو
}

bool VIVANTE_Create_دري(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID create_props)
{
    SDL_Video_معلومات *videodata = _this->اندروني;
    SDL_Display_معلومات *displaydata;
    SDL_دري_معلومات *معلومات;

    displaydata = SDL_Get_Display_Driver_معلومات(SDL_GetPrimaryDisplay());

    // Allocate window internal data
    معلومات = (SDL_دري_معلومات *)SDL_calloc(1, حجم(SDL_دري_معلومات));
    إذا (!معلومات) {
        أرجع false;
    }

    // Setup driver data for this window
    دري->اندروني = معلومات;

    SDL_PropertiesID props = SDL_Get_دري_Properties(دري);
    SDL_سيٽ_اشارو_Property(props, SDL_PROP_دري_VIVANTE_DISPLAY_اشارو, displaydata->native_display);

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_VIVANTE_VDK
    معلومات->native_دري = vdk_Create_دري(displaydata->native_display, دري->x, دري->y, دري->w, دري->h);
#وإلا
    معلومات->native_دري = videodata->fb_Create_دري(displaydata->native_display, دري->x, دري->y, دري->w, دري->h);
#جيڪڏهن_پورو
    إذا (!معلومات->native_دري) {
        أرجع SDL_سيٽ_Error("VIVANTE: Can't create native window");
    }
    SDL_سيٽ_اشارو_Property(props, SDL_PROP_دري_VIVANTE_دري_اشارو, معلومات->native_دري);

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
    إذا (دري->flags & SDL_دري_OPENGL) {
        معلومات->egl_surface = SDL_EGL_CreateSurface(_this, دري, معلومات->native_دري);
        إذا (معلومات->egl_surface == EGL_NO_SURFACE) {
            أرجع SDL_سيٽ_Error("VIVANTE: Can't create EGL surface");
        }
    } وإلا {
        معلومات->egl_surface = EGL_NO_SURFACE;
    }
    SDL_سيٽ_اشارو_Property(props, SDL_PROP_دري_VIVANTE_SURFACE_اشارو, معلومات->egl_surface);
#جيڪڏهن_پورو

    // Window has been successfully created
    أرجع true;
}

فراغ VIVANTE_Destroy_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_Video_معلومات *videodata = _this->اندروني;
    SDL_دري_معلومات *معلومات;

    معلومات = دري->اندروني;
    إذا (معلومات) {
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
        إذا (معلومات->egl_surface != EGL_NO_SURFACE) {
            SDL_EGL_DestroySurface(_this, معلومات->egl_surface);
        }
#جيڪڏهن_پورو

        إذا (معلومات->native_دري) {
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_VIVANTE_VDK
            vdk_Destroy_دري(معلومات->native_دري);
#وإلا
            videodata->fb_Destroy_دري(معلومات->native_دري);
#جيڪڏهن_پورو
        }

        SDL_free(معلومات);
    }
    دري->اندروني = عدم;
}

فراغ VIVANTE_سيٽ_دري_Title(SDL_VideoDevice *_this, SDL_دري *دري)
{
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_دري_معلومات *معلومات = دري->اندروني;
    vdk_سيٽ_دري_Title(معلومات->native_دري, دري->title);
#جيڪڏهن_پورو
}

bool VIVANTE_سيٽ_دري_Position(SDL_VideoDevice *_this, SDL_دري *دري)
{
    // FIXME
    أرجع SDL_Unsupported();
}

فراغ VIVANTE_سيٽ_دري_سائيز(SDL_VideoDevice *_this, SDL_دري *دري)
{
    // FIXME
}

فراغ VIVANTE_Show_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_دري_معلومات *معلومات = دري->اندروني;
    vdk_Show_دري(معلومات->native_دري);
#جيڪڏهن_پورو
    SDL_سيٽ_Mouse_Focus(دري);
    SDL_سيٽ_Keyboard_Focus(دري);
}

فراغ VIVANTE_Hide_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_VIVANTE_VDK
    SDL_دري_معلومات *معلومات = دري->اندروني;
    vdk_Hide_دري(معلومات->native_دري);
#جيڪڏهن_پورو
    SDL_سيٽ_Mouse_Focus(عدم);
    SDL_سيٽ_Keyboard_Focus(عدم);
}

/*****************************************************************************/
// SDL event functions
/*****************************************************************************/
فراغ VIVANTE_PumpEvents(SDL_VideoDevice *_this)
{
#جيڪڏهن_وصف_ٿيل SDL_داخلا_LINUXEV
    SDL_EVDEV_Poll();
#جيڪڏهن_پورو
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_VIVANTE
