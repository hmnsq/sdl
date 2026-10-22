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

#اگر_غیر_تعریف_شدہ SDL_egl_h_
#تعریف_کرو SDL_egl_h_

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL

#شامل <SDL3/SDL_egl.h>

#شامل "SDL_sysvideo.h"

#تعریف_کرو SDL_EGL_MAX_DEVICES 8

// For systems that don't define these
قسمتعریف intptr_t EGLAttrib;
قسمتعریف خالی *EGLDeviceEXT;
قسمتعریف EGLDisplay (EGLAPIENTRYP PFNEGLGETDISPLAYPROC) (EGLNativeDisplayType display_id);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLINITIALIZEPROC) (EGLDisplay dpy, EGLint *major, EGLint *minor);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLTERMINATEPROC) (EGLDisplay dpy);
قسمتعریف __eglMustCastToProperFunctionPointerType (EGLAPIENTRYP PFNEGLGETPROCADDRESSPROC) (ثابت حرف *procname);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLCHOOSECONFIGPROC) (EGLDisplay dpy, ثابت EGLint *attrib_list, EGLConfig *configs, EGLint config_سائز, EGLint *عدد_config);
قسمتعریف EGLContext (EGLAPIENTRYP PFNEGLCREATECONTEXTPROC) (EGLDisplay dpy, EGLConfig config, EGLContext share_context, ثابت EGLint *attrib_list);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYCONTEXTPROC) (EGLDisplay dpy, EGLContext ctx);
قسمتعریف EGLSurface (EGLAPIENTRYP PFNEGLCREATEPBUFFERSURFACEPROC) (EGLDisplay dpy, EGLConfig config, ثابت EGLint *attrib_list);
قسمتعریف EGLSurface (EGLAPIENTRYP PFNEGLCREATEWINDOWSURFACEPROC) (EGLDisplay dpy, EGLConfig config, EGLNative_کھڑکی_Type win, ثابت EGLint *attrib_list);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSURFACEPROC) (EGLDisplay dpy, EGLSurface surface);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLMAKECURRENTPROC) (EGLDisplay dpy, EGLSurface draw, EGLSurface اقرأ, EGLContext ctx);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSPROC) (EGLDisplay dpy, EGLSurface surface);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLSWAPINTERVALPROC) (EGLDisplay dpy, EGLint interval);
قسمتعریف ثابت حرف *(EGLAPIENTRYP PFNEGLQUERYSTRINGPROC) (EGLDisplay dpy, EGLint name);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLGETCONFIGATTRIBPROC) (EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *قدر);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLWAITNATIVEPROC) (EGLint engine);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLWAITGLPROC) (خالی);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLBINDAPIPROC) (EGLenum api);
قسمتعریف EGLint (EGLAPIENTRYP PFNEGLGETERRORPROC) (خالی);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICESEXTPROC) (EGLint max_devices, EGLDeviceEXT *devices, EGLint *عدد_devices);
قسمتعریف EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYPROC) (EGLenum platform, خالی *native_display, ثابت EGLAttrib *attrib_list);
قسمتعریف EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYEXTPROC) (EGLenum platform, خالی *native_display, ثابت EGLint *attrib_list);
قسمتعریف EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESYNCKHRPROC) (EGLDisplay dpy, EGLenum type, ثابت EGLint *attrib_list);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync);
قسمتعریف EGLint (EGLAPIENTRYP PFNEGLDUPNATIVEFENCEFDANDROIDPROC) (EGLDisplay dpy, EGLSyncKHR sync);
قسمتعریف EGLint (EGLAPIENTRYP PFNEGLWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
قسمتعریف EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);

قسمتعریف ساخت SDL_EGL_Video_ڈیٹا
{
    SDL_SharedObject *opengl_dll_handle;
    SDL_SharedObject *egl_dll_handle;
    EGLDisplay egl_display;
    EGLConfig egl_config;
    صحیح egl_swapinterval;
    صحیح egl_surfacetype;
    صحیح egl_نسخہ_major, egl_نسخہ_minor;
    EGLint egl_required_visual_id;
    bool is_offscreen; // whether EGL display was offscreen
    EGLenum apitype;       // EGL_OPENGL_ES_API, EGL_OPENGL_API, etc

    PFNEGLGETDISPLAYPROC eglGetDisplay;
    PFNEGLINITIALIZEPROC eglInitialize;
    PFNEGLTERMINATEPROC eglTerminate;
    PFNEGLGETPROCADDRESSPROC egl_Get_Proc_پتہ;
    PFNEGLCHOOSECONFIGPROC egl_انتخاب_Config;
    PFNEGLCREATECONTEXTPROC eglCreateContext;
    PFNEGLDESTROYCONTEXTPROC eglDestroyContext;
    PFNEGLCREATEPBUFFERSURFACEPROC eglCreatePbufferSurface;
    PFNEGLCREATEWINDOWSURFACEPROC egl_Create_کھڑکی_Surface;
    PFNEGLDESTROYSURFACEPROC eglDestroySurface;
    PFNEGLMAKECURRENTPROC eglMakeCurrent;
    PFNEGLSWAPBUFFERSPROC egl_تبادلہ_Buffers;
    PFNEGLSWAPINTERVALPROC egl_تبادلہ_Interval;
    PFNEGLQUERYSTRINGPROC eglQueryString;
    PFNEGLGETCONFIGATTRIBPROC eglGetConfigAttrib;
    PFNEGLWAITNATIVEPROC eglWaitNative;
    PFNEGLWAITGLPROC eglWaitGL;
    PFNEGLBINDAPIPROC eglBindAPI;
    PFNEGLGETERRORPROC eglGetError;
    PFNEGLQUERYDEVICESEXTPROC eglQueryDevicesEXT;
    PFNEGLGETPLATFORMDISPLAYPROC eglGetPlatformDisplay;
    PFNEGLGETPLATFORMDISPLAYEXTPROC eglGetPlatformDisplayEXT;

    // Atomic functions
    PFNEGLCREATESYNCKHRPROC eglCreateSyncKHR;
    PFNEGLDESTROYSYNCKHRPROC eglDestroySyncKHR;
    PFNEGLDUPNATIVEFENCEFDANDROIDPROC eglDupNativeFenceFDANDROID;
    PFNEGLWAITSYNCKHRPROC eglWaitSyncKHR;
    PFNEGLCLIENTWAITSYNCKHRPROC eglClientWaitSyncKHR;

    // Atomic functions end
} SDL_EGL_Video_ڈیٹا;

// OpenGLES functions
قسمتعریف شمار SDL_EGL_ExtensionType
{
    SDL_EGL_DISPLAY_EXTENSION,
    SDL_EGL_CLIENT_EXTENSION
} SDL_EGL_ExtensionType;

خارجی bool SDL_EGL_HasExtension(SDL_VideoDevice *_this, SDL_EGL_ExtensionType type, ثابت حرف *ext);

خارجی bool SDL_EGL_GetAttribute(SDL_VideoDevice *_this, SDL_GLAttr attrib, صحیح *قدر);
خارجی bool SDL_EGL_بھرو_Library_Only(SDL_VideoDevice *_this, ثابت حرف *راستہ);
خارجی bool SDL_EGL_بھرو_Library(SDL_VideoDevice *_this, ثابت حرف *راستہ, NativeDisplayType native_display);
خارجی SDL_Function_اشارہ_گر SDL_EGL_Get_Proc_پتہ_اندرونی(SDL_VideoDevice *_this, ثابت حرف *proc);
خارجی خالی SDL_EGL_UnloadLibrary(SDL_VideoDevice *_this);
خارجی خالی SDL_EGL_سیٹ_Required_Visual_Id(SDL_VideoDevice *_this, صحیح visual_id);
خارجی bool SDL_EGL_انتخاب_Config(SDL_VideoDevice *_this);
خارجی bool SDL_EGL_سیٹ_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح interval);
خارجی bool SDL_EGL_Get_تبادلہ_Interval(SDL_VideoDevice *_this, صحیح *interval);
خارجی bool SDL_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
خارجی EGLSurface SDL_EGL_CreateSurface(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, Native_کھڑکی_Type nw);
خارجی خالی SDL_EGL_DestroySurface(SDL_VideoDevice *_this, EGLSurface egl_surface);

خارجی EGLSurface SDL_EGL_CreateOffscreenSurface(SDL_VideoDevice *_this, صحیح چوڑائی, صحیح اونچائی);
// Assumes that LoadLibraryOnly() has succeeded
خارجی bool SDL_EGL_InitializeOffscreen(SDL_VideoDevice *_this, صحیح device);

// These need to be wrapped to get the surface for the window by the platform GLES implementation
خارجی SDL_GLContext SDL_EGL_CreateContext(SDL_VideoDevice *_this, EGLSurface egl_surface);
خارجی bool SDL_EGL_MakeCurrent(SDL_VideoDevice *_this, EGLSurface egl_surface, SDL_GLContext context);
خارجی bool SDL_EGL_تبادلہ_Buffers(SDL_VideoDevice *_this, EGLSurface egl_surface);

// SDL Error-reporting
خارجی bool SDL_EGL_سیٹ_Error_Ex(ثابت حرف *پیغام, ثابت حرف *eglFunctionName, EGLint egl_Error_رمز);
#تعریف_کرو SDL_EGL_سیٹ_Error(پیغام, eglFunctionName) SDL_EGL_سیٹ_Error_Ex(پیغام, eglFunctionName, _this->egl_ڈیٹا->eglGetError())

// A few of useful macros

#تعریف_کرو SDL_EGL_تبادلہ_کھڑکی_impl(BACKEND)                                                        \
    bool BACKEND##_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)                  \
    {                                                                                           \
        واپس SDL_EGL_تبادلہ_Buffers(_this, کھڑکی->اندرونی_2->egl_surface);                       \
    }

#تعریف_کرو SDL_EGL_MakeCurrent_impl(BACKEND)                                                                    \
    bool BACKEND##_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_GLContext context)       \
    {                                                                                                        \
        واپس SDL_EGL_MakeCurrent(_this, کھڑکی ? کھڑکی->اندرونی_2->egl_surface : EGL_NO_SURFACE, context); \
    }

#تعریف_کرو SDL_EGL_CreateContext_impl(BACKEND)                                                     \
    SDL_GLContext BACKEND##_GLES_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)      \
    {                                                                                           \
        واپس SDL_EGL_CreateContext(_this, کھڑکی->اندرونی_2->egl_surface);                     \
    }

#اگر_ختم // SDL_VIDEO_OPENGL_EGL

#اگر_ختم // SDL_egl_h_
