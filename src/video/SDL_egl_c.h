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
#অন্তর্ভাৱ "SDL_internal.h"

#ifndef SDL_egl_h_
#define SDL_egl_h_

#ifdef SDL_VIDEO_OPENGL_EGL

#অন্তর্ভাৱ <SDL3/SDL_egl.h>

#অন্তর্ভাৱ "SDL_sysvideo.h"

#define SDL_EGL_MAX_DEVICES 8

// For systems that don't define these
প্রকারনির্দেশ intptr_t EGLAttrib;
প্রকারনির্দেশ শূন্য *EGLDeviceEXT;
প্রকারনির্দেশ EGLDisplay (EGLAPIENTRYP PFNEGLGETDISPLAYPROC) (EGLNativeDisplayType display_id);
প্রকারনির্দেশ EGLBoolean (EGLAPIENTRYP PFNEGLINITIALIZEPROC) (EGLDisplay dpy, EGLint *major, EGLint *minor);
প্রকারনির্দেশ EGLBoolean (EGLAPIENTRYP PFNEGLTERMINATEPROC) (EGLDisplay dpy);
প্রকারনির্দেশ __eglMustCastToProperFunctionPointerType (EGLAPIENTRYP PFNEGLGETPROCADDRESSPROC) (ধ্রুৱ ৱর্ণ *procname);
প্রকারনির্দেশ EGLBoolean (EGLAPIENTRYP PFNEGLCHOOSECONFIGPROC) (EGLDisplay dpy, ধ্রুৱ EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *অঙ্ক_config);
প্রকারনির্দেশ EGLContext (EGLAPIENTRYP PFNEGLCREATECONTEXTPROC) (EGLDisplay dpy, EGLConfig config, EGLContext share_context, ধ্রুৱ EGLint *attrib_list);
প্রকারনির্দেশ EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYCONTEXTPROC) (EGLDisplay dpy, EGLContext ctx);
প্রকারনির্দেশ EGLSurface (EGLAPIENTRYP PFNEGLCREATEPBUFFERSURFACEPROC) (EGLDisplay dpy, EGLConfig config, ধ্রুৱ EGLint *attrib_list);
প্রকারনির্দেশ EGLSurface (EGLAPIENTRYP PFNEGLCREATEWINDOWSURFACEPROC) (EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, ধ্রুৱ EGLint *attrib_list);
প্রকারনির্দেশ EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSURFACEPROC) (EGLDisplay dpy, EGLSurface surface);
প্রকারনির্দেশ EGLBoolean (EGLAPIENTRYP PFNEGLMAKECURRENTPROC) (EGLDisplay dpy, EGLSurface draw, EGLSurface পঠ, EGLContext ctx);
প্রকারনির্দেশ EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSPROC) (EGLDisplay dpy, EGLSurface surface);
প্রকারনির্দেশ EGLBoolean (EGLAPIENTRYP PFNEGLSWAPINTERVALPROC) (EGLDisplay dpy, EGLint interval);
প্রকারনির্দেশ ধ্রুৱ ৱর্ণ *(EGLAPIENTRYP PFNEGLQUERYSTRINGPROC) (EGLDisplay dpy, EGLint name);
প্রকারনির্দেশ EGLBoolean (EGLAPIENTRYP PFNEGLGETCONFIGATTRIBPROC) (EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *মান);
প্রকারনির্দেশ EGLBoolean (EGLAPIENTRYP PFNEGLWAITNATIVEPROC) (EGLint engine);
প্রকারনির্দেশ EGLBoolean (EGLAPIENTRYP PFNEGLWAITGLPROC) (শূন্য);
প্রকারনির্দেশ EGLBoolean (EGLAPIENTRYP PFNEGLBINDAPIPROC) (EGLenum api);
প্রকারনির্দেশ EGLint (EGLAPIENTRYP PFNEGLGETERRORPROC) (শূন্য);
প্রকারনির্দেশ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICESEXTPROC) (EGLint max_devices, EGLDeviceEXT *devices, EGLint *অঙ্ক_devices);
প্রকারনির্দেশ EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYPROC) (EGLenum platform, শূন্য *native_display, ধ্রুৱ EGLAttrib *attrib_list);
প্রকারনির্দেশ EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYEXTPROC) (EGLenum platform, শূন্য *native_display, ধ্রুৱ EGLint *attrib_list);
প্রকারনির্দেশ EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESYNCKHRPROC) (EGLDisplay dpy, EGLenum type, ধ্রুৱ EGLint *attrib_list);
প্রকারনির্দেশ EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync);
প্রকারনির্দেশ EGLint (EGLAPIENTRYP PFNEGLDUPNATIVEFENCEFDANDROIDPROC) (EGLDisplay dpy, EGLSyncKHR sync);
প্রকারনির্দেশ EGLint (EGLAPIENTRYP PFNEGLWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
প্রকারনির্দেশ EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);

প্রকারনির্দেশ সংরচনা SDL_EGL_VideoData
{
    SDL_SharedObject *opengl_dll_handle;
    SDL_SharedObject *egl_dll_handle;
    EGLDisplay egl_display;
    EGLConfig egl_config;
    পূর্ণাঙ্ক egl_swapinterval;
    পূর্ণাঙ্ক egl_surfacetype;
    পূর্ণাঙ্ক egl_version_major, egl_version_minor;
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
প্রকারনির্দেশ গণনা SDL_EGL_ExtensionType
{
    SDL_EGL_DISPLAY_EXTENSION,
    SDL_EGL_CLIENT_EXTENSION
} SDL_EGL_ExtensionType;

বাহ্য bool SDL_EGL_HasExtension(SDL_VideoDevice *_this, SDL_EGL_ExtensionType type, ধ্রুৱ ৱর্ণ *ext);

বাহ্য bool SDL_EGL_GetAttribute(SDL_VideoDevice *_this, SDL_GLAttr attrib, পূর্ণাঙ্ক *মান);
বাহ্য bool SDL_EGL_LoadLibraryOnly(SDL_VideoDevice *_this, ধ্রুৱ ৱর্ণ *path);
বাহ্য bool SDL_EGL_LoadLibrary(SDL_VideoDevice *_this, ধ্রুৱ ৱর্ণ *path, NativeDisplayType native_display);
বাহ্য SDL_FunctionPointer SDL_EGL_GetProcAddressInternal(SDL_VideoDevice *_this, ধ্রুৱ ৱর্ণ *proc);
বাহ্য শূন্য SDL_EGL_UnloadLibrary(SDL_VideoDevice *_this);
বাহ্য শূন্য SDL_EGL_SetRequiredVisualId(SDL_VideoDevice *_this, পূর্ণাঙ্ক visual_id);
বাহ্য bool SDL_EGL_ChooseConfig(SDL_VideoDevice *_this);
বাহ্য bool SDL_EGL_SetSwapInterval(SDL_VideoDevice *_this, পূর্ণাঙ্ক interval);
বাহ্য bool SDL_EGL_GetSwapInterval(SDL_VideoDevice *_this, পূর্ণাঙ্ক *interval);
বাহ্য bool SDL_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
বাহ্য EGLSurface SDL_EGL_CreateSurface(SDL_VideoDevice *_this, SDL_Window *window, NativeWindowType nw);
বাহ্য শূন্য SDL_EGL_DestroySurface(SDL_VideoDevice *_this, EGLSurface egl_surface);

বাহ্য EGLSurface SDL_EGL_CreateOffscreenSurface(SDL_VideoDevice *_this, পূর্ণাঙ্ক width, পূর্ণাঙ্ক height);
// Assumes that LoadLibraryOnly() has succeeded
বাহ্য bool SDL_EGL_InitializeOffscreen(SDL_VideoDevice *_this, পূর্ণাঙ্ক device);

// These need to be wrapped to get the surface for the window by the platform GLES implementation
বাহ্য SDL_GLContext SDL_EGL_CreateContext(SDL_VideoDevice *_this, EGLSurface egl_surface);
বাহ্য bool SDL_EGL_MakeCurrent(SDL_VideoDevice *_this, EGLSurface egl_surface, SDL_GLContext context);
বাহ্য bool SDL_EGL_SwapBuffers(SDL_VideoDevice *_this, EGLSurface egl_surface);

// SDL Error-reporting
বাহ্য bool SDL_EGL_SetErrorEx(ধ্রুৱ ৱর্ণ *message, ধ্রুৱ ৱর্ণ *eglFunctionName, EGLint eglErrorCode);
#define SDL_EGL_SetError(message, eglFunctionName) SDL_EGL_SetErrorEx(message, eglFunctionName, _this->egl_data->eglGetError())

// A few of useful macros

#define SDL_EGL_SwapWindow_impl(BACKEND)                                                        \
    bool BACKEND##_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)                  \
    {                                                                                           \
        ঘূৰাই SDL_EGL_SwapBuffers(_this, window->internal->egl_surface);                       \
    }

#define SDL_EGL_MakeCurrent_impl(BACKEND)                                                                    \
    bool BACKEND##_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)       \
    {                                                                                                        \
        ঘূৰাই SDL_EGL_MakeCurrent(_this, window ? window->internal->egl_surface : EGL_NO_SURFACE, context); \
    }

#define SDL_EGL_CreateContext_impl(BACKEND)                                                     \
    SDL_GLContext BACKEND##_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)      \
    {                                                                                           \
        ঘূৰাই SDL_EGL_CreateContext(_this, window->internal->egl_surface);                     \
    }

#endif // SDL_VIDEO_OPENGL_EGL

#endif // SDL_egl_h_
