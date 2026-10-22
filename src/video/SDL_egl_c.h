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
#અન્તર્ભાવ "SDL_internal.h"

#ifndef SDL_egl_h_
#define SDL_egl_h_

#ifdef SDL_VIDEO_OPENGL_EGL

#અન્તર્ભાવ <SDL3/SDL_egl.h>

#અન્તર્ભાવ "SDL_sysvideo.h"

#define SDL_EGL_MAX_DEVICES 8

// For systems that don't define these
પ્રકારવ્યાખ્યા intptr_t EGLAttrib;
પ્રકારવ્યાખ્યા શૂન્ય *EGLDeviceEXT;
પ્રકારવ્યાખ્યા EGLDisplay (EGLAPIENTRYP PFNEGLGETDISPLAYPROC) (EGLNativeDisplayType display_id);
પ્રકારવ્યાખ્યા EGLBoolean (EGLAPIENTRYP PFNEGLINITIALIZEPROC) (EGLDisplay dpy, EGLint *major, EGLint *minor);
પ્રકારવ્યાખ્યા EGLBoolean (EGLAPIENTRYP PFNEGLTERMINATEPROC) (EGLDisplay dpy);
પ્રકારવ્યાખ્યા __eglMustCastToProperFunctionPointerType (EGLAPIENTRYP PFNEGLGETPROCADDRESSPROC) (અચલ અક્ષર *procname);
પ્રકારવ્યાખ્યા EGLBoolean (EGLAPIENTRYP PFNEGLCHOOSECONFIGPROC) (EGLDisplay dpy, અચલ EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *અંક_config);
પ્રકારવ્યાખ્યા EGLContext (EGLAPIENTRYP PFNEGLCREATECONTEXTPROC) (EGLDisplay dpy, EGLConfig config, EGLContext share_context, અચલ EGLint *attrib_list);
પ્રકારવ્યાખ્યા EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYCONTEXTPROC) (EGLDisplay dpy, EGLContext ctx);
પ્રકારવ્યાખ્યા EGLSurface (EGLAPIENTRYP PFNEGLCREATEPBUFFERSURFACEPROC) (EGLDisplay dpy, EGLConfig config, અચલ EGLint *attrib_list);
પ્રકારવ્યાખ્યા EGLSurface (EGLAPIENTRYP PFNEGLCREATEWINDOWSURFACEPROC) (EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, અચલ EGLint *attrib_list);
પ્રકારવ્યાખ્યા EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSURFACEPROC) (EGLDisplay dpy, EGLSurface surface);
પ્રકારવ્યાખ્યા EGLBoolean (EGLAPIENTRYP PFNEGLMAKECURRENTPROC) (EGLDisplay dpy, EGLSurface draw, EGLSurface પઠ, EGLContext ctx);
પ્રકારવ્યાખ્યા EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSPROC) (EGLDisplay dpy, EGLSurface surface);
પ્રકારવ્યાખ્યા EGLBoolean (EGLAPIENTRYP PFNEGLSWAPINTERVALPROC) (EGLDisplay dpy, EGLint interval);
પ્રકારવ્યાખ્યા અચલ અક્ષર *(EGLAPIENTRYP PFNEGLQUERYSTRINGPROC) (EGLDisplay dpy, EGLint name);
પ્રકારવ્યાખ્યા EGLBoolean (EGLAPIENTRYP PFNEGLGETCONFIGATTRIBPROC) (EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *કિંમત);
પ્રકારવ્યાખ્યા EGLBoolean (EGLAPIENTRYP PFNEGLWAITNATIVEPROC) (EGLint engine);
પ્રકારવ્યાખ્યા EGLBoolean (EGLAPIENTRYP PFNEGLWAITGLPROC) (શૂન્ય);
પ્રકારવ્યાખ્યા EGLBoolean (EGLAPIENTRYP PFNEGLBINDAPIPROC) (EGLenum api);
પ્રકારવ્યાખ્યા EGLint (EGLAPIENTRYP PFNEGLGETERRORPROC) (શૂન્ય);
પ્રકારવ્યાખ્યા EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICESEXTPROC) (EGLint max_devices, EGLDeviceEXT *devices, EGLint *અંક_devices);
પ્રકારવ્યાખ્યા EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYPROC) (EGLenum platform, શૂન્ય *native_display, અચલ EGLAttrib *attrib_list);
પ્રકારવ્યાખ્યા EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYEXTPROC) (EGLenum platform, શૂન્ય *native_display, અચલ EGLint *attrib_list);
પ્રકારવ્યાખ્યા EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESYNCKHRPROC) (EGLDisplay dpy, EGLenum type, અચલ EGLint *attrib_list);
પ્રકારવ્યાખ્યા EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync);
પ્રકારવ્યાખ્યા EGLint (EGLAPIENTRYP PFNEGLDUPNATIVEFENCEFDANDROIDPROC) (EGLDisplay dpy, EGLSyncKHR sync);
પ્રકારવ્યાખ્યા EGLint (EGLAPIENTRYP PFNEGLWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
પ્રકારવ્યાખ્યા EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);

પ્રકારવ્યાખ્યા સંરચના SDL_EGL_VideoData
{
    SDL_SharedObject *opengl_dll_handle;
    SDL_SharedObject *egl_dll_handle;
    EGLDisplay egl_display;
    EGLConfig egl_config;
    પૂર્ણાંક egl_swapinterval;
    પૂર્ણાંક egl_surfacetype;
    પૂર્ણાંક egl_version_major, egl_version_minor;
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
પ્રકારવ્યાખ્યા ગણના SDL_EGL_ExtensionType
{
    SDL_EGL_DISPLAY_EXTENSION,
    SDL_EGL_CLIENT_EXTENSION
} SDL_EGL_ExtensionType;

બાહ્ય bool SDL_EGL_HasExtension(SDL_VideoDevice *_this, SDL_EGL_ExtensionType type, અચલ અક્ષર *ext);

બાહ્ય bool SDL_EGL_GetAttribute(SDL_VideoDevice *_this, SDL_GLAttr attrib, પૂર્ણાંક *કિંમત);
બાહ્ય bool SDL_EGL_LoadLibraryOnly(SDL_VideoDevice *_this, અચલ અક્ષર *path);
બાહ્ય bool SDL_EGL_LoadLibrary(SDL_VideoDevice *_this, અચલ અક્ષર *path, NativeDisplayType native_display);
બાહ્ય SDL_FunctionPointer SDL_EGL_GetProcAddressInternal(SDL_VideoDevice *_this, અચલ અક્ષર *proc);
બાહ્ય શૂન્ય SDL_EGL_UnloadLibrary(SDL_VideoDevice *_this);
બાહ્ય શૂન્ય SDL_EGL_SetRequiredVisualId(SDL_VideoDevice *_this, પૂર્ણાંક visual_id);
બાહ્ય bool SDL_EGL_ChooseConfig(SDL_VideoDevice *_this);
બાહ્ય bool SDL_EGL_SetSwapInterval(SDL_VideoDevice *_this, પૂર્ણાંક interval);
બાહ્ય bool SDL_EGL_GetSwapInterval(SDL_VideoDevice *_this, પૂર્ણાંક *interval);
બાહ્ય bool SDL_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
બાહ્ય EGLSurface SDL_EGL_CreateSurface(SDL_VideoDevice *_this, SDL_Window *window, NativeWindowType nw);
બાહ્ય શૂન્ય SDL_EGL_DestroySurface(SDL_VideoDevice *_this, EGLSurface egl_surface);

બાહ્ય EGLSurface SDL_EGL_CreateOffscreenSurface(SDL_VideoDevice *_this, પૂર્ણાંક width, પૂર્ણાંક height);
// Assumes that LoadLibraryOnly() has succeeded
બાહ્ય bool SDL_EGL_InitializeOffscreen(SDL_VideoDevice *_this, પૂર્ણાંક device);

// These need to be wrapped to get the surface for the window by the platform GLES implementation
બાહ્ય SDL_GLContext SDL_EGL_CreateContext(SDL_VideoDevice *_this, EGLSurface egl_surface);
બાહ્ય bool SDL_EGL_MakeCurrent(SDL_VideoDevice *_this, EGLSurface egl_surface, SDL_GLContext context);
બાહ્ય bool SDL_EGL_SwapBuffers(SDL_VideoDevice *_this, EGLSurface egl_surface);

// SDL Error-reporting
બાહ્ય bool SDL_EGL_SetErrorEx(અચલ અક્ષર *message, અચલ અક્ષર *eglFunctionName, EGLint eglErrorCode);
#define SDL_EGL_SetError(message, eglFunctionName) SDL_EGL_SetErrorEx(message, eglFunctionName, _this->egl_data->eglGetError())

// A few of useful macros

#define SDL_EGL_SwapWindow_impl(BACKEND)                                                        \
    bool BACKEND##_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)                  \
    {                                                                                           \
        પાછા SDL_EGL_SwapBuffers(_this, window->internal->egl_surface);                       \
    }

#define SDL_EGL_MakeCurrent_impl(BACKEND)                                                                    \
    bool BACKEND##_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)       \
    {                                                                                                        \
        પાછા SDL_EGL_MakeCurrent(_this, window ? window->internal->egl_surface : EGL_NO_SURFACE, context); \
    }

#define SDL_EGL_CreateContext_impl(BACKEND)                                                     \
    SDL_GLContext BACKEND##_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)      \
    {                                                                                           \
        પાછા SDL_EGL_CreateContext(_this, window->internal->egl_surface);                     \
    }

#endif // SDL_VIDEO_OPENGL_EGL

#endif // SDL_egl_h_
