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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_egl_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_egl_h_

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL

#ਅਨ੍ਤਰ੍ਭਾਵ <SDL3/SDL_egl.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_sysvideo.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_EGL_MAX_DEVICES 8

// For systems that don't define these
ਕਿਸਮਪਰਿਭਾਸ਼ਾ intptr_t EGLAttrib;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ *EGLDeviceEXT;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLDisplay (EGLAPIENTRYP PFNEGLGETDISPLAYPROC) (EGLNativeDisplayType display_id);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLINITIALIZEPROC) (EGLDisplay dpy, EGLint *major, EGLint *minor);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLTERMINATEPROC) (EGLDisplay dpy);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ __eglMustCastToProperFunctionPointerType (EGLAPIENTRYP PFNEGLGETPROCADDRESSPROC) (ਅਚਲ ਅੱਖਰ *procname);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLCHOOSECONFIGPROC) (EGLDisplay dpy, ਅਚਲ EGLint *attrib_list, EGLConfig *configs, EGLint config_ਮਾਪ, EGLint *ਅੰਕ_config);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLContext (EGLAPIENTRYP PFNEGLCREATECONTEXTPROC) (EGLDisplay dpy, EGLConfig config, EGLContext share_context, ਅਚਲ EGLint *attrib_list);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYCONTEXTPROC) (EGLDisplay dpy, EGLContext ctx);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLSurface (EGLAPIENTRYP PFNEGLCREATEPBUFFERSURFACEPROC) (EGLDisplay dpy, EGLConfig config, ਅਚਲ EGLint *attrib_list);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLSurface (EGLAPIENTRYP PFNEGLCREATEWINDOWSURFACEPROC) (EGLDisplay dpy, EGLConfig config, EGLNative_ਖਿੜਕੀ_Type win, ਅਚਲ EGLint *attrib_list);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSURFACEPROC) (EGLDisplay dpy, EGLSurface surface);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLMAKECURRENTPROC) (EGLDisplay dpy, EGLSurface draw, EGLSurface ਪਠ, EGLContext ctx);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSPROC) (EGLDisplay dpy, EGLSurface surface);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLSWAPINTERVALPROC) (EGLDisplay dpy, EGLint interval);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਅਚਲ ਅੱਖਰ *(EGLAPIENTRYP PFNEGLQUERYSTRINGPROC) (EGLDisplay dpy, EGLint name);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLGETCONFIGATTRIBPROC) (EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLWAITNATIVEPROC) (EGLint engine);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLWAITGLPROC) (ਖਾਲੀ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLBINDAPIPROC) (EGLenum api);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLint (EGLAPIENTRYP PFNEGLGETERRORPROC) (ਖਾਲੀ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICESEXTPROC) (EGLint max_devices, EGLDeviceEXT *devices, EGLint *ਅੰਕ_devices);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYPROC) (EGLenum platform, ਖਾਲੀ *native_display, ਅਚਲ EGLAttrib *attrib_list);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYEXTPROC) (EGLenum platform, ਖਾਲੀ *native_display, ਅਚਲ EGLint *attrib_list);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESYNCKHRPROC) (EGLDisplay dpy, EGLenum type, ਅਚਲ EGLint *attrib_list);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLint (EGLAPIENTRYP PFNEGLDUPNATIVEFENCEFDANDROIDPROC) (EGLDisplay dpy, EGLSyncKHR sync);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLint (EGLAPIENTRYP PFNEGLWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SDL_EGL_Video_ਅੰਕੜੇ
{
    SDL_SharedObject *opengl_dll_handle;
    SDL_SharedObject *egl_dll_handle;
    EGLDisplay egl_display;
    EGLConfig egl_config;
    ਪੂਰਨ egl_swapinterval;
    ਪੂਰਨ egl_surfacetype;
    ਪੂਰਨ egl_ਸੰਸਕਰਣ_major, egl_ਸੰਸਕਰਣ_minor;
    EGLint egl_required_visual_id;
    bool is_offscreen; // whether EGL display was offscreen
    EGLenum apitype;       // EGL_OPENGL_ES_API, EGL_OPENGL_API, etc

    PFNEGLGETDISPLAYPROC eglGetDisplay;
    PFNEGLINITIALIZEPROC eglInitialize;
    PFNEGLTERMINATEPROC eglTerminate;
    PFNEGLGETPROCADDRESSPROC egl_Get_Proc_ਪਤਾ;
    PFNEGLCHOOSECONFIGPROC egl_ਚੁਣੋ_Config;
    PFNEGLCREATECONTEXTPROC eglCreateContext;
    PFNEGLDESTROYCONTEXTPROC eglDestroyContext;
    PFNEGLCREATEPBUFFERSURFACEPROC eglCreatePbufferSurface;
    PFNEGLCREATEWINDOWSURFACEPROC egl_Create_ਖਿੜਕੀ_Surface;
    PFNEGLDESTROYSURFACEPROC eglDestroySurface;
    PFNEGLMAKECURRENTPROC eglMakeCurrent;
    PFNEGLSWAPBUFFERSPROC egl_ਅਦਲਾ_ਬਦਲੀ_Buffers;
    PFNEGLSWAPINTERVALPROC egl_ਅਦਲਾ_ਬਦਲੀ_Interval;
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
} SDL_EGL_Video_ਅੰਕੜੇ;

// OpenGLES functions
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ SDL_EGL_ExtensionType
{
    SDL_EGL_DISPLAY_EXTENSION,
    SDL_EGL_CLIENT_EXTENSION
} SDL_EGL_ExtensionType;

ਬਾਹਰੀ bool SDL_EGL_HasExtension(SDL_VideoDevice *_this, SDL_EGL_ExtensionType type, ਅਚਲ ਅੱਖਰ *ext);

ਬਾਹਰੀ bool SDL_EGL_GetAttribute(SDL_VideoDevice *_this, SDL_GLAttr attrib, ਪੂਰਨ *ਮੁੱਲ);
ਬਾਹਰੀ bool SDL_EGL_ਲੱਦੋ_Library_Only(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ);
ਬਾਹਰੀ bool SDL_EGL_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ, NativeDisplayType native_display);
ਬਾਹਰੀ SDL_Function_ਸੂਚਕ SDL_EGL_Get_Proc_ਪਤਾ_ਅੰਦਰੂਨੀ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *proc);
ਬਾਹਰੀ ਖਾਲੀ SDL_EGL_UnloadLibrary(SDL_VideoDevice *_this);
ਬਾਹਰੀ ਖਾਲੀ SDL_EGL_ਸੈੱਟ_Required_Visual_Id(SDL_VideoDevice *_this, ਪੂਰਨ visual_id);
ਬਾਹਰੀ bool SDL_EGL_ਚੁਣੋ_Config(SDL_VideoDevice *_this);
ਬਾਹਰੀ bool SDL_EGL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ interval);
ਬਾਹਰੀ bool SDL_EGL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ *interval);
ਬਾਹਰੀ bool SDL_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
ਬਾਹਰੀ EGLSurface SDL_EGL_CreateSurface(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, Native_ਖਿੜਕੀ_Type nw);
ਬਾਹਰੀ ਖਾਲੀ SDL_EGL_DestroySurface(SDL_VideoDevice *_this, EGLSurface egl_surface);

ਬਾਹਰੀ EGLSurface SDL_EGL_CreateOffscreenSurface(SDL_VideoDevice *_this, ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ);
// Assumes that LoadLibraryOnly() has succeeded
ਬਾਹਰੀ bool SDL_EGL_InitializeOffscreen(SDL_VideoDevice *_this, ਪੂਰਨ device);

// These need to be wrapped to get the surface for the window by the platform GLES implementation
ਬਾਹਰੀ SDL_GLContext SDL_EGL_CreateContext(SDL_VideoDevice *_this, EGLSurface egl_surface);
ਬਾਹਰੀ bool SDL_EGL_MakeCurrent(SDL_VideoDevice *_this, EGLSurface egl_surface, SDL_GLContext context);
ਬਾਹਰੀ bool SDL_EGL_ਅਦਲਾ_ਬਦਲੀ_Buffers(SDL_VideoDevice *_this, EGLSurface egl_surface);

// SDL Error-reporting
ਬਾਹਰੀ bool SDL_EGL_ਸੈੱਟ_Error_Ex(ਅਚਲ ਅੱਖਰ *ਸੁਨੇਹਾ, ਅਚਲ ਅੱਖਰ *eglFunctionName, EGLint egl_Error_ਕੋਡ);
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_EGL_ਸੈੱਟ_Error(ਸੁਨੇਹਾ, eglFunctionName) SDL_EGL_ਸੈੱਟ_Error_Ex(ਸੁਨੇਹਾ, eglFunctionName, _this->egl_ਅੰਕੜੇ->eglGetError())

// A few of useful macros

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_EGL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ_impl(BACKEND)                                                        \
    bool BACKEND##_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)                  \
    {                                                                                           \
        ਵਾਪਸ SDL_EGL_ਅਦਲਾ_ਬਦਲੀ_Buffers(_this, ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->egl_surface);                       \
    }

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_EGL_MakeCurrent_impl(BACKEND)                                                                    \
    bool BACKEND##_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_GLContext context)       \
    {                                                                                                        \
        ਵਾਪਸ SDL_EGL_MakeCurrent(_this, ਖਿੜਕੀ ? ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->egl_surface : EGL_NO_SURFACE, context); \
    }

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_EGL_CreateContext_impl(BACKEND)                                                     \
    SDL_GLContext BACKEND##_GLES_CreateContext(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)      \
    {                                                                                           \
        ਵਾਪਸ SDL_EGL_CreateContext(_this, ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->egl_surface);                     \
    }

#ਜੇ_ਅੰਤ // SDL_VIDEO_OPENGL_EGL

#ਜੇ_ਅੰਤ // SDL_egl_h_
