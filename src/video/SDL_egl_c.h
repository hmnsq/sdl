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
#अन्तर्भाव "SDL_internal.h"

#ifndef SDL_egl_h_
#define SDL_egl_h_

#ifdef SDL_VIDEO_OPENGL_EGL

#अन्तर्भाव <SDL3/SDL_egl.h>

#अन्तर्भाव "SDL_sysvideo.h"

#define SDL_EGL_MAX_DEVICES 8

// For systems that don't define these
प्रकारव्याख्या intptr_t EGLAttrib;
प्रकारव्याख्या शून्य *EGLDeviceEXT;
प्रकारव्याख्या EGLDisplay (EGLAPIENTRYP PFNEGLGETDISPLAYPROC) (EGLNativeDisplayType display_id);
प्रकारव्याख्या EGLBoolean (EGLAPIENTRYP PFNEGLINITIALIZEPROC) (EGLDisplay dpy, EGLint *major, EGLint *minor);
प्रकारव्याख्या EGLBoolean (EGLAPIENTRYP PFNEGLTERMINATEPROC) (EGLDisplay dpy);
प्रकारव्याख्या __eglMustCastToProperFunctionPointerType (EGLAPIENTRYP PFNEGLGETPROCADDRESSPROC) (स्थिरांक अक्षर *procname);
प्रकारव्याख्या EGLBoolean (EGLAPIENTRYP PFNEGLCHOOSECONFIGPROC) (EGLDisplay dpy, स्थिरांक EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *अंक_config);
प्रकारव्याख्या EGLContext (EGLAPIENTRYP PFNEGLCREATECONTEXTPROC) (EGLDisplay dpy, EGLConfig config, EGLContext share_context, स्थिरांक EGLint *attrib_list);
प्रकारव्याख्या EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYCONTEXTPROC) (EGLDisplay dpy, EGLContext ctx);
प्रकारव्याख्या EGLSurface (EGLAPIENTRYP PFNEGLCREATEPBUFFERSURFACEPROC) (EGLDisplay dpy, EGLConfig config, स्थिरांक EGLint *attrib_list);
प्रकारव्याख्या EGLSurface (EGLAPIENTRYP PFNEGLCREATEWINDOWSURFACEPROC) (EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, स्थिरांक EGLint *attrib_list);
प्रकारव्याख्या EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSURFACEPROC) (EGLDisplay dpy, EGLSurface surface);
प्रकारव्याख्या EGLBoolean (EGLAPIENTRYP PFNEGLMAKECURRENTPROC) (EGLDisplay dpy, EGLSurface draw, EGLSurface पठ, EGLContext ctx);
प्रकारव्याख्या EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSPROC) (EGLDisplay dpy, EGLSurface surface);
प्रकारव्याख्या EGLBoolean (EGLAPIENTRYP PFNEGLSWAPINTERVALPROC) (EGLDisplay dpy, EGLint interval);
प्रकारव्याख्या स्थिरांक अक्षर *(EGLAPIENTRYP PFNEGLQUERYSTRINGPROC) (EGLDisplay dpy, EGLint name);
प्रकारव्याख्या EGLBoolean (EGLAPIENTRYP PFNEGLGETCONFIGATTRIBPROC) (EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *मूल्य);
प्रकारव्याख्या EGLBoolean (EGLAPIENTRYP PFNEGLWAITNATIVEPROC) (EGLint engine);
प्रकारव्याख्या EGLBoolean (EGLAPIENTRYP PFNEGLWAITGLPROC) (शून्य);
प्रकारव्याख्या EGLBoolean (EGLAPIENTRYP PFNEGLBINDAPIPROC) (EGLenum api);
प्रकारव्याख्या EGLint (EGLAPIENTRYP PFNEGLGETERRORPROC) (शून्य);
प्रकारव्याख्या EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICESEXTPROC) (EGLint max_devices, EGLDeviceEXT *devices, EGLint *अंक_devices);
प्रकारव्याख्या EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYPROC) (EGLenum platform, शून्य *native_display, स्थिरांक EGLAttrib *attrib_list);
प्रकारव्याख्या EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYEXTPROC) (EGLenum platform, शून्य *native_display, स्थिरांक EGLint *attrib_list);
प्रकारव्याख्या EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESYNCKHRPROC) (EGLDisplay dpy, EGLenum type, स्थिरांक EGLint *attrib_list);
प्रकारव्याख्या EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync);
प्रकारव्याख्या EGLint (EGLAPIENTRYP PFNEGLDUPNATIVEFENCEFDANDROIDPROC) (EGLDisplay dpy, EGLSyncKHR sync);
प्रकारव्याख्या EGLint (EGLAPIENTRYP PFNEGLWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
प्रकारव्याख्या EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);

प्रकारव्याख्या संरचना SDL_EGL_VideoData
{
    SDL_SharedObject *opengl_dll_handle;
    SDL_SharedObject *egl_dll_handle;
    EGLDisplay egl_display;
    EGLConfig egl_config;
    पूर्णांक egl_swapinterval;
    पूर्णांक egl_surfacetype;
    पूर्णांक egl_version_major, egl_version_minor;
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
प्रकारव्याख्या गणना SDL_EGL_ExtensionType
{
    SDL_EGL_DISPLAY_EXTENSION,
    SDL_EGL_CLIENT_EXTENSION
} SDL_EGL_ExtensionType;

बाह्य bool SDL_EGL_HasExtension(SDL_VideoDevice *_this, SDL_EGL_ExtensionType type, स्थिरांक अक्षर *ext);

बाह्य bool SDL_EGL_GetAttribute(SDL_VideoDevice *_this, SDL_GLAttr attrib, पूर्णांक *मूल्य);
बाह्य bool SDL_EGL_LoadLibraryOnly(SDL_VideoDevice *_this, स्थिरांक अक्षर *path);
बाह्य bool SDL_EGL_LoadLibrary(SDL_VideoDevice *_this, स्थिरांक अक्षर *path, NativeDisplayType native_display);
बाह्य SDL_FunctionPointer SDL_EGL_GetProcAddressInternal(SDL_VideoDevice *_this, स्थिरांक अक्षर *proc);
बाह्य शून्य SDL_EGL_UnloadLibrary(SDL_VideoDevice *_this);
बाह्य शून्य SDL_EGL_SetRequiredVisualId(SDL_VideoDevice *_this, पूर्णांक visual_id);
बाह्य bool SDL_EGL_ChooseConfig(SDL_VideoDevice *_this);
बाह्य bool SDL_EGL_SetSwapInterval(SDL_VideoDevice *_this, पूर्णांक interval);
बाह्य bool SDL_EGL_GetSwapInterval(SDL_VideoDevice *_this, पूर्णांक *interval);
बाह्य bool SDL_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
बाह्य EGLSurface SDL_EGL_CreateSurface(SDL_VideoDevice *_this, SDL_Window *window, NativeWindowType nw);
बाह्य शून्य SDL_EGL_DestroySurface(SDL_VideoDevice *_this, EGLSurface egl_surface);

बाह्य EGLSurface SDL_EGL_CreateOffscreenSurface(SDL_VideoDevice *_this, पूर्णांक width, पूर्णांक height);
// Assumes that LoadLibraryOnly() has succeeded
बाह्य bool SDL_EGL_InitializeOffscreen(SDL_VideoDevice *_this, पूर्णांक device);

// These need to be wrapped to get the surface for the window by the platform GLES implementation
बाह्य SDL_GLContext SDL_EGL_CreateContext(SDL_VideoDevice *_this, EGLSurface egl_surface);
बाह्य bool SDL_EGL_MakeCurrent(SDL_VideoDevice *_this, EGLSurface egl_surface, SDL_GLContext context);
बाह्य bool SDL_EGL_SwapBuffers(SDL_VideoDevice *_this, EGLSurface egl_surface);

// SDL Error-reporting
बाह्य bool SDL_EGL_SetErrorEx(स्थिरांक अक्षर *message, स्थिरांक अक्षर *eglFunctionName, EGLint eglErrorCode);
#define SDL_EGL_SetError(message, eglFunctionName) SDL_EGL_SetErrorEx(message, eglFunctionName, _this->egl_data->eglGetError())

// A few of useful macros

#define SDL_EGL_SwapWindow_impl(BACKEND)                                                        \
    bool BACKEND##_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)                  \
    {                                                                                           \
        परत SDL_EGL_SwapBuffers(_this, window->internal->egl_surface);                       \
    }

#define SDL_EGL_MakeCurrent_impl(BACKEND)                                                                    \
    bool BACKEND##_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)       \
    {                                                                                                        \
        परत SDL_EGL_MakeCurrent(_this, window ? window->internal->egl_surface : EGL_NO_SURFACE, context); \
    }

#define SDL_EGL_CreateContext_impl(BACKEND)                                                     \
    SDL_GLContext BACKEND##_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)      \
    {                                                                                           \
        परत SDL_EGL_CreateContext(_this, window->internal->egl_surface);                     \
    }

#endif // SDL_VIDEO_OPENGL_EGL

#endif // SDL_egl_h_
