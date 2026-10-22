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
#அந்தர்பாவ "SDL_internal.h"

#ifndef SDL_egl_h_
#define SDL_egl_h_

#ifdef SDL_VIDEO_OPENGL_EGL

#அந்தர்பாவ <SDL3/SDL_egl.h>

#அந்தர்பாவ "SDL_sysvideo.h"

#define SDL_EGL_MAX_DEVICES 8

// For systems that don't define these
வகைவரை intptr_t EGLAttrib;
வகைவரை வெறுமை *EGLDeviceEXT;
வகைவரை EGLDisplay (EGLAPIENTRYP PFNEGLGETDISPLAYPROC) (EGLNativeDisplayType display_id);
வகைவரை EGLBoolean (EGLAPIENTRYP PFNEGLINITIALIZEPROC) (EGLDisplay dpy, EGLint *major, EGLint *minor);
வகைவரை EGLBoolean (EGLAPIENTRYP PFNEGLTERMINATEPROC) (EGLDisplay dpy);
வகைவரை __eglMustCastToProperFunctionPointerType (EGLAPIENTRYP PFNEGLGETPROCADDRESSPROC) (மாறிலி எழுத்து *procname);
வகைவரை EGLBoolean (EGLAPIENTRYP PFNEGLCHOOSECONFIGPROC) (EGLDisplay dpy, மாறிலி EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *இலக்கம்_config);
வகைவரை EGLContext (EGLAPIENTRYP PFNEGLCREATECONTEXTPROC) (EGLDisplay dpy, EGLConfig config, EGLContext share_context, மாறிலி EGLint *attrib_list);
வகைவரை EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYCONTEXTPROC) (EGLDisplay dpy, EGLContext ctx);
வகைவரை EGLSurface (EGLAPIENTRYP PFNEGLCREATEPBUFFERSURFACEPROC) (EGLDisplay dpy, EGLConfig config, மாறிலி EGLint *attrib_list);
வகைவரை EGLSurface (EGLAPIENTRYP PFNEGLCREATEWINDOWSURFACEPROC) (EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, மாறிலி EGLint *attrib_list);
வகைவரை EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSURFACEPROC) (EGLDisplay dpy, EGLSurface surface);
வகைவரை EGLBoolean (EGLAPIENTRYP PFNEGLMAKECURRENTPROC) (EGLDisplay dpy, EGLSurface draw, EGLSurface பட, EGLContext ctx);
வகைவரை EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSPROC) (EGLDisplay dpy, EGLSurface surface);
வகைவரை EGLBoolean (EGLAPIENTRYP PFNEGLSWAPINTERVALPROC) (EGLDisplay dpy, EGLint interval);
வகைவரை மாறிலி எழுத்து *(EGLAPIENTRYP PFNEGLQUERYSTRINGPROC) (EGLDisplay dpy, EGLint name);
வகைவரை EGLBoolean (EGLAPIENTRYP PFNEGLGETCONFIGATTRIBPROC) (EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *மதிப்பு);
வகைவரை EGLBoolean (EGLAPIENTRYP PFNEGLWAITNATIVEPROC) (EGLint engine);
வகைவரை EGLBoolean (EGLAPIENTRYP PFNEGLWAITGLPROC) (வெறுமை);
வகைவரை EGLBoolean (EGLAPIENTRYP PFNEGLBINDAPIPROC) (EGLenum api);
வகைவரை EGLint (EGLAPIENTRYP PFNEGLGETERRORPROC) (வெறுமை);
வகைவரை EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICESEXTPROC) (EGLint max_devices, EGLDeviceEXT *devices, EGLint *இலக்கம்_devices);
வகைவரை EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYPROC) (EGLenum platform, வெறுமை *native_display, மாறிலி EGLAttrib *attrib_list);
வகைவரை EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYEXTPROC) (EGLenum platform, வெறுமை *native_display, மாறிலி EGLint *attrib_list);
வகைவரை EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESYNCKHRPROC) (EGLDisplay dpy, EGLenum type, மாறிலி EGLint *attrib_list);
வகைவரை EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync);
வகைவரை EGLint (EGLAPIENTRYP PFNEGLDUPNATIVEFENCEFDANDROIDPROC) (EGLDisplay dpy, EGLSyncKHR sync);
வகைவரை EGLint (EGLAPIENTRYP PFNEGLWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
வகைவரை EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);

வகைவரை கட்டமைப்பு SDL_EGL_VideoData
{
    SDL_SharedObject *opengl_dll_handle;
    SDL_SharedObject *egl_dll_handle;
    EGLDisplay egl_display;
    EGLConfig egl_config;
    முழு egl_swapinterval;
    முழு egl_surfacetype;
    முழு egl_version_major, egl_version_minor;
    EGLint egl_required_visual_id;
    bool is_offscreen; // whether EGL display was offscreen
    EGLenum apitype;       // EGL_OPENGL_ES_API, EGL_OPENGL_API, etc

    PFNEGLGETDISPLAYPROC eglGetDisplay;
    PFNEGLINITIALIZEPROC eglInitialize;
    PFNEGLTERMINATEPROC eglTerminate;
    PFNEGLGETPROCADDRESSPROC eglGetProcAddress;
    PFNEGLCHOOSECONFIGPROC eglChooseConfig;
    PFNEGLCREATECONTEXTPROC eglCreateContext;
    PFNEGLDESTROYCONTEXTPROC eglDestroyContext;
    PFNEGLCREATEPBUFFERSURFACEPROC eglCreatePbufferSurface;
    PFNEGLCREATEWINDOWSURFACEPROC eglCreateWindowSurface;
    PFNEGLDESTROYSURFACEPROC eglDestroySurface;
    PFNEGLMAKECURRENTPROC eglMakeCurrent;
    PFNEGLSWAPBUFFERSPROC eglSwapBuffers;
    PFNEGLSWAPINTERVALPROC eglSwapInterval;
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
} SDL_EGL_VideoData;

// OpenGLES functions
வகைவரை எண்ணிக்கை SDL_EGL_ExtensionType
{
    SDL_EGL_DISPLAY_EXTENSION,
    SDL_EGL_CLIENT_EXTENSION
} SDL_EGL_ExtensionType;

வெளி bool SDL_EGL_HasExtension(SDL_VideoDevice *_this, SDL_EGL_ExtensionType type, மாறிலி எழுத்து *ext);

வெளி bool SDL_EGL_GetAttribute(SDL_VideoDevice *_this, SDL_GLAttr attrib, முழு *மதிப்பு);
வெளி bool SDL_EGL_LoadLibraryOnly(SDL_VideoDevice *_this, மாறிலி எழுத்து *path);
வெளி bool SDL_EGL_LoadLibrary(SDL_VideoDevice *_this, மாறிலி எழுத்து *path, NativeDisplayType native_display);
வெளி SDL_FunctionPointer SDL_EGL_GetProcAddressInternal(SDL_VideoDevice *_this, மாறிலி எழுத்து *proc);
வெளி வெறுமை SDL_EGL_UnloadLibrary(SDL_VideoDevice *_this);
வெளி வெறுமை SDL_EGL_SetRequiredVisualId(SDL_VideoDevice *_this, முழு visual_id);
வெளி bool SDL_EGL_ChooseConfig(SDL_VideoDevice *_this);
வெளி bool SDL_EGL_SetSwapInterval(SDL_VideoDevice *_this, முழு interval);
வெளி bool SDL_EGL_GetSwapInterval(SDL_VideoDevice *_this, முழு *interval);
வெளி bool SDL_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
வெளி EGLSurface SDL_EGL_CreateSurface(SDL_VideoDevice *_this, SDL_Window *window, NativeWindowType nw);
வெளி வெறுமை SDL_EGL_DestroySurface(SDL_VideoDevice *_this, EGLSurface egl_surface);

வெளி EGLSurface SDL_EGL_CreateOffscreenSurface(SDL_VideoDevice *_this, முழு width, முழு height);
// Assumes that LoadLibraryOnly() has succeeded
வெளி bool SDL_EGL_InitializeOffscreen(SDL_VideoDevice *_this, முழு device);

// These need to be wrapped to get the surface for the window by the platform GLES implementation
வெளி SDL_GLContext SDL_EGL_CreateContext(SDL_VideoDevice *_this, EGLSurface egl_surface);
வெளி bool SDL_EGL_MakeCurrent(SDL_VideoDevice *_this, EGLSurface egl_surface, SDL_GLContext context);
வெளி bool SDL_EGL_SwapBuffers(SDL_VideoDevice *_this, EGLSurface egl_surface);

// SDL Error-reporting
வெளி bool SDL_EGL_SetErrorEx(மாறிலி எழுத்து *message, மாறிலி எழுத்து *eglFunctionName, EGLint eglErrorCode);
#define SDL_EGL_SetError(message, eglFunctionName) SDL_EGL_SetErrorEx(message, eglFunctionName, _this->egl_data->eglGetError())

// A few of useful macros

#define SDL_EGL_SwapWindow_impl(BACKEND)                                                        \
    bool BACKEND##_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)                  \
    {                                                                                           \
        திரும்பு SDL_EGL_SwapBuffers(_this, window->internal->egl_surface);                       \
    }

#define SDL_EGL_MakeCurrent_impl(BACKEND)                                                                    \
    bool BACKEND##_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)       \
    {                                                                                                        \
        திரும்பு SDL_EGL_MakeCurrent(_this, window ? window->internal->egl_surface : EGL_NO_SURFACE, context); \
    }

#define SDL_EGL_CreateContext_impl(BACKEND)                                                     \
    SDL_GLContext BACKEND##_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)      \
    {                                                                                           \
        திரும்பு SDL_EGL_CreateContext(_this, window->internal->egl_surface);                     \
    }

#endif // SDL_VIDEO_OPENGL_EGL

#endif // SDL_egl_h_
