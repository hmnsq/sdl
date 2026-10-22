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

#جے_بنا_تعریف SDL_egl_h_
#تعریف_کرو SDL_egl_h_

#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL

#ضمن <SDL3/SDL_egl.h>

#ضمن "SDL_sysvideo.h"

#تعریف_کرو SDL_EGL_MAX_DEVICES 8

// For systems that don't define these
تعريفنوع intptr_t EGLAttrib;
تعريفنوع فراغ *EGLDeviceEXT;
تعريفنوع EGLDisplay (EGLAPIENTRYP PFNEGLGETDISPLAYPROC) (EGLNativeDisplayType display_id);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLINITIALIZEPROC) (EGLDisplay dpy, EGLint *major, EGLint *minor);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLTERMINATEPROC) (EGLDisplay dpy);
تعريفنوع __eglMustCastToProperFunctionPointerType (EGLAPIENTRYP PFNEGLGETPROCADDRESSPROC) (ثابت حرف *procname);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLCHOOSECONFIGPROC) (EGLDisplay dpy, ثابت EGLint *attrib_list, EGLConfig *configs, EGLint config_ناپ, EGLint *عدد_config);
تعريفنوع EGLContext (EGLAPIENTRYP PFNEGLCREATECONTEXTPROC) (EGLDisplay dpy, EGLConfig config, EGLContext share_context, ثابت EGLint *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYCONTEXTPROC) (EGLDisplay dpy, EGLContext ctx);
تعريفنوع EGLSurface (EGLAPIENTRYP PFNEGLCREATEPBUFFERSURFACEPROC) (EGLDisplay dpy, EGLConfig config, ثابت EGLint *attrib_list);
تعريفنوع EGLSurface (EGLAPIENTRYP PFNEGLCREATEWINDOWSURFACEPROC) (EGLDisplay dpy, EGLConfig config, EGLNative_کھڑکی_Type win, ثابت EGLint *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSURFACEPROC) (EGLDisplay dpy, EGLSurface surface);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLMAKECURRENTPROC) (EGLDisplay dpy, EGLSurface draw, EGLSurface اقرأ, EGLContext ctx);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSPROC) (EGLDisplay dpy, EGLSurface surface);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSWAPINTERVALPROC) (EGLDisplay dpy, EGLint interval);
تعريفنوع ثابت حرف *(EGLAPIENTRYP PFNEGLQUERYSTRINGPROC) (EGLDisplay dpy, EGLint name);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETCONFIGATTRIBPROC) (EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *قدر);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLWAITNATIVEPROC) (EGLint engine);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLWAITGLPROC) (فراغ);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLBINDAPIPROC) (EGLenum api);
تعريفنوع EGLint (EGLAPIENTRYP PFNEGLGETERRORPROC) (فراغ);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICESEXTPROC) (EGLint max_devices, EGLDeviceEXT *devices, EGLint *عدد_devices);
تعريفنوع EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYPROC) (EGLenum platform, فراغ *native_display, ثابت EGLAttrib *attrib_list);
تعريفنوع EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYEXTPROC) (EGLenum platform, فراغ *native_display, ثابت EGLint *attrib_list);
تعريفنوع EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESYNCKHRPROC) (EGLDisplay dpy, EGLenum type, ثابت EGLint *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync);
تعريفنوع EGLint (EGLAPIENTRYP PFNEGLDUPNATIVEFENCEFDANDROIDPROC) (EGLDisplay dpy, EGLSyncKHR sync);
تعريفنوع EGLint (EGLAPIENTRYP PFNEGLWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
تعريفنوع EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);

تعريفنوع بنية SDL_EGL_Video_انکڑے
{
    SDL_SharedObject *opengl_dll_handle;
    SDL_SharedObject *egl_dll_handle;
    EGLDisplay egl_display;
    EGLConfig egl_config;
    صحيح egl_swapinterval;
    صحيح egl_surfacetype;
    صحيح egl_نسخہ_major, egl_نسخہ_minor;
    EGLint egl_required_visual_id;
    bool is_offscreen; // whether EGL display was offscreen
    EGLenum apitype;       // EGL_OPENGL_ES_API, EGL_OPENGL_API, etc

    PFNEGLGETDISPLAYPROC eglGetDisplay;
    PFNEGLINITIALIZEPROC eglInitialize;
    PFNEGLTERMINATEPROC eglTerminate;
    PFNEGLGETPROCADDRESSPROC egl_Get_Proc_پتہ;
    PFNEGLCHOOSECONFIGPROC egl_چنو_Config;
    PFNEGLCREATECONTEXTPROC eglCreateContext;
    PFNEGLDESTROYCONTEXTPROC eglDestroyContext;
    PFNEGLCREATEPBUFFERSURFACEPROC eglCreatePbufferSurface;
    PFNEGLCREATEWINDOWSURFACEPROC egl_Create_کھڑکی_Surface;
    PFNEGLDESTROYSURFACEPROC eglDestroySurface;
    PFNEGLMAKECURRENTPROC eglMakeCurrent;
    PFNEGLSWAPBUFFERSPROC egl_وٹاندرا_Buffers;
    PFNEGLSWAPINTERVALPROC egl_وٹاندرا_Interval;
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
} SDL_EGL_Video_انکڑے;

// OpenGLES functions
تعريفنوع تعداد SDL_EGL_ExtensionType
{
    SDL_EGL_DISPLAY_EXTENSION,
    SDL_EGL_CLIENT_EXTENSION
} SDL_EGL_ExtensionType;

خارجي bool SDL_EGL_HasExtension(SDL_VideoDevice *_this, SDL_EGL_ExtensionType type, ثابت حرف *ext);

خارجي bool SDL_EGL_GetAttribute(SDL_VideoDevice *_this, SDL_GLAttr attrib, صحيح *قدر);
خارجي bool SDL_EGL_لدو_Library_Only(SDL_VideoDevice *_this, ثابت حرف *رستہ);
خارجي bool SDL_EGL_لدو_Library(SDL_VideoDevice *_this, ثابت حرف *رستہ, NativeDisplayType native_display);
خارجي SDL_Function_اشارہ_گر SDL_EGL_Get_Proc_پتہ_اندرونی(SDL_VideoDevice *_this, ثابت حرف *proc);
خارجي فراغ SDL_EGL_UnloadLibrary(SDL_VideoDevice *_this);
خارجي فراغ SDL_EGL_سیٹ_Required_Visual_Id(SDL_VideoDevice *_this, صحيح visual_id);
خارجي bool SDL_EGL_چنو_Config(SDL_VideoDevice *_this);
خارجي bool SDL_EGL_سیٹ_وٹاندرا_Interval(SDL_VideoDevice *_this, صحيح interval);
خارجي bool SDL_EGL_Get_وٹاندرا_Interval(SDL_VideoDevice *_this, صحيح *interval);
خارجي bool SDL_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
خارجي EGLSurface SDL_EGL_CreateSurface(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, Native_کھڑکی_Type nw);
خارجي فراغ SDL_EGL_DestroySurface(SDL_VideoDevice *_this, EGLSurface egl_surface);

خارجي EGLSurface SDL_EGL_CreateOffscreenSurface(SDL_VideoDevice *_this, صحيح چوڑائی, صحيح اچائی);
// Assumes that LoadLibraryOnly() has succeeded
خارجي bool SDL_EGL_InitializeOffscreen(SDL_VideoDevice *_this, صحيح device);

// These need to be wrapped to get the surface for the window by the platform GLES implementation
خارجي SDL_GLContext SDL_EGL_CreateContext(SDL_VideoDevice *_this, EGLSurface egl_surface);
خارجي bool SDL_EGL_MakeCurrent(SDL_VideoDevice *_this, EGLSurface egl_surface, SDL_GLContext context);
خارجي bool SDL_EGL_وٹاندرا_Buffers(SDL_VideoDevice *_this, EGLSurface egl_surface);

// SDL Error-reporting
خارجي bool SDL_EGL_سیٹ_Error_Ex(ثابت حرف *سنیہا, ثابت حرف *eglFunctionName, EGLint egl_Error_کوڈ);
#تعریف_کرو SDL_EGL_سیٹ_Error(سنیہا, eglFunctionName) SDL_EGL_سیٹ_Error_Ex(سنیہا, eglFunctionName, _this->egl_انکڑے->eglGetError())

// A few of useful macros

#تعریف_کرو SDL_EGL_وٹاندرا_کھڑکی_impl(BACKEND)                                                        \
    bool BACKEND##_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)                  \
    {                                                                                           \
        أرجع SDL_EGL_وٹاندرا_Buffers(_this, کھڑکی->اندرونی->egl_surface);                       \
    }

#تعریف_کرو SDL_EGL_MakeCurrent_impl(BACKEND)                                                                    \
    bool BACKEND##_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_GLContext context)       \
    {                                                                                                        \
        أرجع SDL_EGL_MakeCurrent(_this, کھڑکی ? کھڑکی->اندرونی->egl_surface : EGL_NO_SURFACE, context); \
    }

#تعریف_کرو SDL_EGL_CreateContext_impl(BACKEND)                                                     \
    SDL_GLContext BACKEND##_GLES_CreateContext(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)      \
    {                                                                                           \
        أرجع SDL_EGL_CreateContext(_this, کھڑکی->اندرونی->egl_surface);                     \
    }

#جے_انت // SDL_VIDEO_OPENGL_EGL

#جے_انت // SDL_egl_h_
