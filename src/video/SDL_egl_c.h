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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ifndef SDL_egl_h_
#define SDL_egl_h_

#ifdef SDL_VIDEO_OPENGL_EGL

#ಅನ್ತರ್ಭಾವ <SDL3/SDL_egl.h>

#ಅನ್ತರ್ಭಾವ "SDL_sysvideo.h"

#define SDL_EGL_MAX_DEVICES 8

// For systems that don't define these
ಪ್ರಕಾರನಿರ್ದೇಶ intptr_t EGLAttrib;
ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ *EGLDeviceEXT;
ಪ್ರಕಾರನಿರ್ದೇಶ EGLDisplay (EGLAPIENTRYP PFNEGLGETDISPLAYPROC) (EGLNativeDisplayType display_id);
ಪ್ರಕಾರನಿರ್ದೇಶ EGLBoolean (EGLAPIENTRYP PFNEGLINITIALIZEPROC) (EGLDisplay dpy, EGLint *major, EGLint *minor);
ಪ್ರಕಾರನಿರ್ದೇಶ EGLBoolean (EGLAPIENTRYP PFNEGLTERMINATEPROC) (EGLDisplay dpy);
ಪ್ರಕಾರನಿರ್ದೇಶ __eglMustCastToProperFunctionPointerType (EGLAPIENTRYP PFNEGLGETPROCADDRESSPROC) (ಧ್ರುವ ವರ್ಣ *procname);
ಪ್ರಕಾರನಿರ್ದೇಶ EGLBoolean (EGLAPIENTRYP PFNEGLCHOOSECONFIGPROC) (EGLDisplay dpy, ಧ್ರುವ EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *ಅಂಕೆ_config);
ಪ್ರಕಾರನಿರ್ದೇಶ EGLContext (EGLAPIENTRYP PFNEGLCREATECONTEXTPROC) (EGLDisplay dpy, EGLConfig config, EGLContext share_context, ಧ್ರುವ EGLint *attrib_list);
ಪ್ರಕಾರನಿರ್ದೇಶ EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYCONTEXTPROC) (EGLDisplay dpy, EGLContext ctx);
ಪ್ರಕಾರನಿರ್ದೇಶ EGLSurface (EGLAPIENTRYP PFNEGLCREATEPBUFFERSURFACEPROC) (EGLDisplay dpy, EGLConfig config, ಧ್ರುವ EGLint *attrib_list);
ಪ್ರಕಾರನಿರ್ದೇಶ EGLSurface (EGLAPIENTRYP PFNEGLCREATEWINDOWSURFACEPROC) (EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, ಧ್ರುವ EGLint *attrib_list);
ಪ್ರಕಾರನಿರ್ದೇಶ EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSURFACEPROC) (EGLDisplay dpy, EGLSurface surface);
ಪ್ರಕಾರನಿರ್ದೇಶ EGLBoolean (EGLAPIENTRYP PFNEGLMAKECURRENTPROC) (EGLDisplay dpy, EGLSurface draw, EGLSurface ಪಠ, EGLContext ctx);
ಪ್ರಕಾರನಿರ್ದೇಶ EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSPROC) (EGLDisplay dpy, EGLSurface surface);
ಪ್ರಕಾರನಿರ್ದೇಶ EGLBoolean (EGLAPIENTRYP PFNEGLSWAPINTERVALPROC) (EGLDisplay dpy, EGLint interval);
ಪ್ರಕಾರನಿರ್ದೇಶ ಧ್ರುವ ವರ್ಣ *(EGLAPIENTRYP PFNEGLQUERYSTRINGPROC) (EGLDisplay dpy, EGLint name);
ಪ್ರಕಾರನಿರ್ದೇಶ EGLBoolean (EGLAPIENTRYP PFNEGLGETCONFIGATTRIBPROC) (EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *ಮೌಲ್ಯ);
ಪ್ರಕಾರನಿರ್ದೇಶ EGLBoolean (EGLAPIENTRYP PFNEGLWAITNATIVEPROC) (EGLint engine);
ಪ್ರಕಾರನಿರ್ದೇಶ EGLBoolean (EGLAPIENTRYP PFNEGLWAITGLPROC) (ಶೂನ್ಯ);
ಪ್ರಕಾರನಿರ್ದೇಶ EGLBoolean (EGLAPIENTRYP PFNEGLBINDAPIPROC) (EGLenum api);
ಪ್ರಕಾರನಿರ್ದೇಶ EGLint (EGLAPIENTRYP PFNEGLGETERRORPROC) (ಶೂನ್ಯ);
ಪ್ರಕಾರನಿರ್ದೇಶ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICESEXTPROC) (EGLint max_devices, EGLDeviceEXT *devices, EGLint *ಅಂಕೆ_devices);
ಪ್ರಕಾರನಿರ್ದೇಶ EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYPROC) (EGLenum platform, ಶೂನ್ಯ *native_display, ಧ್ರುವ EGLAttrib *attrib_list);
ಪ್ರಕಾರನಿರ್ದೇಶ EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYEXTPROC) (EGLenum platform, ಶೂನ್ಯ *native_display, ಧ್ರುವ EGLint *attrib_list);
ಪ್ರಕಾರನಿರ್ದೇಶ EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESYNCKHRPROC) (EGLDisplay dpy, EGLenum type, ಧ್ರುವ EGLint *attrib_list);
ಪ್ರಕಾರನಿರ್ದೇಶ EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync);
ಪ್ರಕಾರನಿರ್ದೇಶ EGLint (EGLAPIENTRYP PFNEGLDUPNATIVEFENCEFDANDROIDPROC) (EGLDisplay dpy, EGLSyncKHR sync);
ಪ್ರಕಾರನಿರ್ದೇಶ EGLint (EGLAPIENTRYP PFNEGLWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
ಪ್ರಕಾರನಿರ್ದೇಶ EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ SDL_EGL_VideoData
{
    SDL_SharedObject *opengl_dll_handle;
    SDL_SharedObject *egl_dll_handle;
    EGLDisplay egl_display;
    EGLConfig egl_config;
    ಪೂರ್ಣಾಙ್ಕ egl_swapinterval;
    ಪೂರ್ಣಾಙ್ಕ egl_surfacetype;
    ಪೂರ್ಣಾಙ್ಕ egl_version_major, egl_version_minor;
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
ಪ್ರಕಾರನಿರ್ದೇಶ ಗಣನಾ SDL_EGL_ExtensionType
{
    SDL_EGL_DISPLAY_EXTENSION,
    SDL_EGL_CLIENT_EXTENSION
} SDL_EGL_ExtensionType;

ಬಾಹ್ಯ bool SDL_EGL_HasExtension(SDL_VideoDevice *_this, SDL_EGL_ExtensionType type, ಧ್ರುವ ವರ್ಣ *ext);

ಬಾಹ್ಯ bool SDL_EGL_GetAttribute(SDL_VideoDevice *_this, SDL_GLAttr attrib, ಪೂರ್ಣಾಙ್ಕ *ಮೌಲ್ಯ);
ಬಾಹ್ಯ bool SDL_EGL_LoadLibraryOnly(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *path);
ಬಾಹ್ಯ bool SDL_EGL_LoadLibrary(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *path, NativeDisplayType native_display);
ಬಾಹ್ಯ SDL_FunctionPointer SDL_EGL_GetProcAddressInternal(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *proc);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_EGL_UnloadLibrary(SDL_VideoDevice *_this);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_EGL_SetRequiredVisualId(SDL_VideoDevice *_this, ಪೂರ್ಣಾಙ್ಕ visual_id);
ಬಾಹ್ಯ bool SDL_EGL_ChooseConfig(SDL_VideoDevice *_this);
ಬಾಹ್ಯ bool SDL_EGL_SetSwapInterval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಙ್ಕ interval);
ಬಾಹ್ಯ bool SDL_EGL_GetSwapInterval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಙ್ಕ *interval);
ಬಾಹ್ಯ bool SDL_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
ಬಾಹ್ಯ EGLSurface SDL_EGL_CreateSurface(SDL_VideoDevice *_this, SDL_Window *window, NativeWindowType nw);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_EGL_DestroySurface(SDL_VideoDevice *_this, EGLSurface egl_surface);

ಬಾಹ್ಯ EGLSurface SDL_EGL_CreateOffscreenSurface(SDL_VideoDevice *_this, ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height);
// Assumes that LoadLibraryOnly() has succeeded
ಬಾಹ್ಯ bool SDL_EGL_InitializeOffscreen(SDL_VideoDevice *_this, ಪೂರ್ಣಾಙ್ಕ device);

// These need to be wrapped to get the surface for the window by the platform GLES implementation
ಬಾಹ್ಯ SDL_GLContext SDL_EGL_CreateContext(SDL_VideoDevice *_this, EGLSurface egl_surface);
ಬಾಹ್ಯ bool SDL_EGL_MakeCurrent(SDL_VideoDevice *_this, EGLSurface egl_surface, SDL_GLContext context);
ಬಾಹ್ಯ bool SDL_EGL_SwapBuffers(SDL_VideoDevice *_this, EGLSurface egl_surface);

// SDL Error-reporting
ಬಾಹ್ಯ bool SDL_EGL_SetErrorEx(ಧ್ರುವ ವರ್ಣ *message, ಧ್ರುವ ವರ್ಣ *eglFunctionName, EGLint eglErrorCode);
#define SDL_EGL_SetError(message, eglFunctionName) SDL_EGL_SetErrorEx(message, eglFunctionName, _this->egl_data->eglGetError())

// A few of useful macros

#define SDL_EGL_SwapWindow_impl(BACKEND)                                                        \
    bool BACKEND##_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)                  \
    {                                                                                           \
        ಪ್ರತ್ಯಾಗಮ SDL_EGL_SwapBuffers(_this, window->internal->egl_surface);                       \
    }

#define SDL_EGL_MakeCurrent_impl(BACKEND)                                                                    \
    bool BACKEND##_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)       \
    {                                                                                                        \
        ಪ್ರತ್ಯಾಗಮ SDL_EGL_MakeCurrent(_this, window ? window->internal->egl_surface : EGL_NO_SURFACE, context); \
    }

#define SDL_EGL_CreateContext_impl(BACKEND)                                                     \
    SDL_GLContext BACKEND##_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)      \
    {                                                                                           \
        ಪ್ರತ್ಯಾಗಮ SDL_EGL_CreateContext(_this, window->internal->egl_surface);                     \
    }

#endif // SDL_VIDEO_OPENGL_EGL

#endif // SDL_egl_h_
