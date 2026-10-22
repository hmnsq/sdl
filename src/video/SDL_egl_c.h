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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifndef SDL_egl_h_
#define SDL_egl_h_

#ifdef SDL_VIDEO_OPENGL_EGL

#ଅନ୍ତର୍ଭାଵ <SDL3/SDL_egl.h>

#ଅନ୍ତର୍ଭାଵ "SDL_sysvideo.h"

#define SDL_EGL_MAX_DEVICES 8

// For systems that don't define these
ପ୍ରକାରବ୍ୟାଖ୍ୟା intptr_t EGLAttrib;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ *EGLDeviceEXT;
ପ୍ରକାରବ୍ୟାଖ୍ୟା EGLDisplay (EGLAPIENTRYP PFNEGLGETDISPLAYPROC) (EGLNativeDisplayType display_id);
ପ୍ରକାରବ୍ୟାଖ୍ୟା EGLBoolean (EGLAPIENTRYP PFNEGLINITIALIZEPROC) (EGLDisplay dpy, EGLint *major, EGLint *minor);
ପ୍ରକାରବ୍ୟାଖ୍ୟା EGLBoolean (EGLAPIENTRYP PFNEGLTERMINATEPROC) (EGLDisplay dpy);
ପ୍ରକାରବ୍ୟାଖ୍ୟା __eglMustCastToProperFunctionPointerType (EGLAPIENTRYP PFNEGLGETPROCADDRESSPROC) (ଅଚଳ ଅକ୍ଷର *procname);
ପ୍ରକାରବ୍ୟାଖ୍ୟା EGLBoolean (EGLAPIENTRYP PFNEGLCHOOSECONFIGPROC) (EGLDisplay dpy, ଅଚଳ EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *ଅଙ୍କ_config);
ପ୍ରକାରବ୍ୟାଖ୍ୟା EGLContext (EGLAPIENTRYP PFNEGLCREATECONTEXTPROC) (EGLDisplay dpy, EGLConfig config, EGLContext share_context, ଅଚଳ EGLint *attrib_list);
ପ୍ରକାରବ୍ୟାଖ୍ୟା EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYCONTEXTPROC) (EGLDisplay dpy, EGLContext ctx);
ପ୍ରକାରବ୍ୟାଖ୍ୟା EGLSurface (EGLAPIENTRYP PFNEGLCREATEPBUFFERSURFACEPROC) (EGLDisplay dpy, EGLConfig config, ଅଚଳ EGLint *attrib_list);
ପ୍ରକାରବ୍ୟାଖ୍ୟା EGLSurface (EGLAPIENTRYP PFNEGLCREATEWINDOWSURFACEPROC) (EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, ଅଚଳ EGLint *attrib_list);
ପ୍ରକାରବ୍ୟାଖ୍ୟା EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSURFACEPROC) (EGLDisplay dpy, EGLSurface surface);
ପ୍ରକାରବ୍ୟାଖ୍ୟା EGLBoolean (EGLAPIENTRYP PFNEGLMAKECURRENTPROC) (EGLDisplay dpy, EGLSurface draw, EGLSurface ପଠ, EGLContext ctx);
ପ୍ରକାରବ୍ୟାଖ୍ୟା EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSPROC) (EGLDisplay dpy, EGLSurface surface);
ପ୍ରକାରବ୍ୟାଖ୍ୟା EGLBoolean (EGLAPIENTRYP PFNEGLSWAPINTERVALPROC) (EGLDisplay dpy, EGLint interval);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଅଚଳ ଅକ୍ଷର *(EGLAPIENTRYP PFNEGLQUERYSTRINGPROC) (EGLDisplay dpy, EGLint name);
ପ୍ରକାରବ୍ୟାଖ୍ୟା EGLBoolean (EGLAPIENTRYP PFNEGLGETCONFIGATTRIBPROC) (EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା EGLBoolean (EGLAPIENTRYP PFNEGLWAITNATIVEPROC) (EGLint engine);
ପ୍ରକାରବ୍ୟାଖ୍ୟା EGLBoolean (EGLAPIENTRYP PFNEGLWAITGLPROC) (ଶୂନ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା EGLBoolean (EGLAPIENTRYP PFNEGLBINDAPIPROC) (EGLenum api);
ପ୍ରକାରବ୍ୟାଖ୍ୟା EGLint (EGLAPIENTRYP PFNEGLGETERRORPROC) (ଶୂନ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICESEXTPROC) (EGLint max_devices, EGLDeviceEXT *devices, EGLint *ଅଙ୍କ_devices);
ପ୍ରକାରବ୍ୟାଖ୍ୟା EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYPROC) (EGLenum platform, ଶୂନ୍ୟ *native_display, ଅଚଳ EGLAttrib *attrib_list);
ପ୍ରକାରବ୍ୟାଖ୍ୟା EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYEXTPROC) (EGLenum platform, ଶୂନ୍ୟ *native_display, ଅଚଳ EGLint *attrib_list);
ପ୍ରକାରବ୍ୟାଖ୍ୟା EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESYNCKHRPROC) (EGLDisplay dpy, EGLenum type, ଅଚଳ EGLint *attrib_list);
ପ୍ରକାରବ୍ୟାଖ୍ୟା EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync);
ପ୍ରକାରବ୍ୟାଖ୍ୟା EGLint (EGLAPIENTRYP PFNEGLDUPNATIVEFENCEFDANDROIDPROC) (EGLDisplay dpy, EGLSyncKHR sync);
ପ୍ରକାରବ୍ୟାଖ୍ୟା EGLint (EGLAPIENTRYP PFNEGLWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
ପ୍ରକାରବ୍ୟାଖ୍ୟା EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା SDL_EGL_VideoData
{
    SDL_SharedObject *opengl_dll_handle;
    SDL_SharedObject *egl_dll_handle;
    EGLDisplay egl_display;
    EGLConfig egl_config;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା egl_swapinterval;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା egl_surfacetype;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା egl_version_major, egl_version_minor;
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
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଗଣନା SDL_EGL_ExtensionType
{
    SDL_EGL_DISPLAY_EXTENSION,
    SDL_EGL_CLIENT_EXTENSION
} SDL_EGL_ExtensionType;

ବାହ୍ୟ bool SDL_EGL_HasExtension(SDL_VideoDevice *_this, SDL_EGL_ExtensionType type, ଅଚଳ ଅକ୍ଷର *ext);

ବାହ୍ୟ bool SDL_EGL_GetAttribute(SDL_VideoDevice *_this, SDL_GLAttr attrib, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *ମୂଲ୍ୟ);
ବାହ୍ୟ bool SDL_EGL_LoadLibraryOnly(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *path);
ବାହ୍ୟ bool SDL_EGL_LoadLibrary(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *path, NativeDisplayType native_display);
ବାହ୍ୟ SDL_FunctionPointer SDL_EGL_GetProcAddressInternal(SDL_VideoDevice *_this, ଅଚଳ ଅକ୍ଷର *proc);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_EGL_UnloadLibrary(SDL_VideoDevice *_this);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_EGL_SetRequiredVisualId(SDL_VideoDevice *_this, ପୂର୍ଣ୍ଣସଂଖ୍ୟା visual_id);
ବାହ୍ୟ bool SDL_EGL_ChooseConfig(SDL_VideoDevice *_this);
ବାହ୍ୟ bool SDL_EGL_SetSwapInterval(SDL_VideoDevice *_this, ପୂର୍ଣ୍ଣସଂଖ୍ୟା interval);
ବାହ୍ୟ bool SDL_EGL_GetSwapInterval(SDL_VideoDevice *_this, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *interval);
ବାହ୍ୟ bool SDL_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
ବାହ୍ୟ EGLSurface SDL_EGL_CreateSurface(SDL_VideoDevice *_this, SDL_Window *window, NativeWindowType nw);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_EGL_DestroySurface(SDL_VideoDevice *_this, EGLSurface egl_surface);

ବାହ୍ୟ EGLSurface SDL_EGL_CreateOffscreenSurface(SDL_VideoDevice *_this, ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height);
// Assumes that LoadLibraryOnly() has succeeded
ବାହ୍ୟ bool SDL_EGL_InitializeOffscreen(SDL_VideoDevice *_this, ପୂର୍ଣ୍ଣସଂଖ୍ୟା device);

// These need to be wrapped to get the surface for the window by the platform GLES implementation
ବାହ୍ୟ SDL_GLContext SDL_EGL_CreateContext(SDL_VideoDevice *_this, EGLSurface egl_surface);
ବାହ୍ୟ bool SDL_EGL_MakeCurrent(SDL_VideoDevice *_this, EGLSurface egl_surface, SDL_GLContext context);
ବାହ୍ୟ bool SDL_EGL_SwapBuffers(SDL_VideoDevice *_this, EGLSurface egl_surface);

// SDL Error-reporting
ବାହ୍ୟ bool SDL_EGL_SetErrorEx(ଅଚଳ ଅକ୍ଷର *message, ଅଚଳ ଅକ୍ଷର *eglFunctionName, EGLint eglErrorCode);
#define SDL_EGL_SetError(message, eglFunctionName) SDL_EGL_SetErrorEx(message, eglFunctionName, _this->egl_data->eglGetError())

// A few of useful macros

#define SDL_EGL_SwapWindow_impl(BACKEND)                                                        \
    bool BACKEND##_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)                  \
    {                                                                                           \
        ଫେରନ୍ତୁ SDL_EGL_SwapBuffers(_this, window->internal->egl_surface);                       \
    }

#define SDL_EGL_MakeCurrent_impl(BACKEND)                                                                    \
    bool BACKEND##_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)       \
    {                                                                                                        \
        ଫେରନ୍ତୁ SDL_EGL_MakeCurrent(_this, window ? window->internal->egl_surface : EGL_NO_SURFACE, context); \
    }

#define SDL_EGL_CreateContext_impl(BACKEND)                                                     \
    SDL_GLContext BACKEND##_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)      \
    {                                                                                           \
        ଫେରନ୍ତୁ SDL_EGL_CreateContext(_this, window->internal->egl_surface);                     \
    }

#endif // SDL_VIDEO_OPENGL_EGL

#endif // SDL_egl_h_
