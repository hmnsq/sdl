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
#അന്തര്ഭാവ "SDL_internal.h"

#ifndef SDL_egl_h_
#define SDL_egl_h_

#ifdef SDL_VIDEO_OPENGL_EGL

#അന്തര്ഭാവ <SDL3/SDL_egl.h>

#അന്തര്ഭാവ "SDL_sysvideo.h"

#define SDL_EGL_MAX_DEVICES 8

// For systems that don't define these
തരനിർവചനം intptr_t EGLAttrib;
തരനിർവചനം ശൂന്യം *EGLDeviceEXT;
തരനിർവചനം EGLDisplay (EGLAPIENTRYP PFNEGLGETDISPLAYPROC) (EGLNativeDisplayType display_id);
തരനിർവചനം EGLBoolean (EGLAPIENTRYP PFNEGLINITIALIZEPROC) (EGLDisplay dpy, EGLint *major, EGLint *minor);
തരനിർവചനം EGLBoolean (EGLAPIENTRYP PFNEGLTERMINATEPROC) (EGLDisplay dpy);
തരനിർവചനം __eglMustCastToProperFunctionPointerType (EGLAPIENTRYP PFNEGLGETPROCADDRESSPROC) (സ്ഥിരം അക്ഷരം *procname);
തരനിർവചനം EGLBoolean (EGLAPIENTRYP PFNEGLCHOOSECONFIGPROC) (EGLDisplay dpy, സ്ഥിരം EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *അക്കം_config);
തരനിർവചനം EGLContext (EGLAPIENTRYP PFNEGLCREATECONTEXTPROC) (EGLDisplay dpy, EGLConfig config, EGLContext share_context, സ്ഥിരം EGLint *attrib_list);
തരനിർവചനം EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYCONTEXTPROC) (EGLDisplay dpy, EGLContext ctx);
തരനിർവചനം EGLSurface (EGLAPIENTRYP PFNEGLCREATEPBUFFERSURFACEPROC) (EGLDisplay dpy, EGLConfig config, സ്ഥിരം EGLint *attrib_list);
തരനിർവചനം EGLSurface (EGLAPIENTRYP PFNEGLCREATEWINDOWSURFACEPROC) (EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, സ്ഥിരം EGLint *attrib_list);
തരനിർവചനം EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSURFACEPROC) (EGLDisplay dpy, EGLSurface surface);
തരനിർവചനം EGLBoolean (EGLAPIENTRYP PFNEGLMAKECURRENTPROC) (EGLDisplay dpy, EGLSurface draw, EGLSurface പഠ, EGLContext ctx);
തരനിർവചനം EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSPROC) (EGLDisplay dpy, EGLSurface surface);
തരനിർവചനം EGLBoolean (EGLAPIENTRYP PFNEGLSWAPINTERVALPROC) (EGLDisplay dpy, EGLint interval);
തരനിർവചനം സ്ഥിരം അക്ഷരം *(EGLAPIENTRYP PFNEGLQUERYSTRINGPROC) (EGLDisplay dpy, EGLint name);
തരനിർവചനം EGLBoolean (EGLAPIENTRYP PFNEGLGETCONFIGATTRIBPROC) (EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *മൂല്യം);
തരനിർവചനം EGLBoolean (EGLAPIENTRYP PFNEGLWAITNATIVEPROC) (EGLint engine);
തരനിർവചനം EGLBoolean (EGLAPIENTRYP PFNEGLWAITGLPROC) (ശൂന്യം);
തരനിർവചനം EGLBoolean (EGLAPIENTRYP PFNEGLBINDAPIPROC) (EGLenum api);
തരനിർവചനം EGLint (EGLAPIENTRYP PFNEGLGETERRORPROC) (ശൂന്യം);
തരനിർവചനം EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICESEXTPROC) (EGLint max_devices, EGLDeviceEXT *devices, EGLint *അക്കം_devices);
തരനിർവചനം EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYPROC) (EGLenum platform, ശൂന്യം *native_display, സ്ഥിരം EGLAttrib *attrib_list);
തരനിർവചനം EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYEXTPROC) (EGLenum platform, ശൂന്യം *native_display, സ്ഥിരം EGLint *attrib_list);
തരനിർവചനം EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESYNCKHRPROC) (EGLDisplay dpy, EGLenum type, സ്ഥിരം EGLint *attrib_list);
തരനിർവചനം EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync);
തരനിർവചനം EGLint (EGLAPIENTRYP PFNEGLDUPNATIVEFENCEFDANDROIDPROC) (EGLDisplay dpy, EGLSyncKHR sync);
തരനിർവചനം EGLint (EGLAPIENTRYP PFNEGLWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
തരനിർവചനം EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);

തരനിർവചനം ഘടന SDL_EGL_VideoData
{
    SDL_SharedObject *opengl_dll_handle;
    SDL_SharedObject *egl_dll_handle;
    EGLDisplay egl_display;
    EGLConfig egl_config;
    പൂർണ്ണസംഖ്യ egl_swapinterval;
    പൂർണ്ണസംഖ്യ egl_surfacetype;
    പൂർണ്ണസംഖ്യ egl_version_major, egl_version_minor;
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
തരനിർവചനം എണ്ണൽ SDL_EGL_ExtensionType
{
    SDL_EGL_DISPLAY_EXTENSION,
    SDL_EGL_CLIENT_EXTENSION
} SDL_EGL_ExtensionType;

ബാഹ്യ bool SDL_EGL_HasExtension(SDL_VideoDevice *_this, SDL_EGL_ExtensionType type, സ്ഥിരം അക്ഷരം *ext);

ബാഹ്യ bool SDL_EGL_GetAttribute(SDL_VideoDevice *_this, SDL_GLAttr attrib, പൂർണ്ണസംഖ്യ *മൂല്യം);
ബാഹ്യ bool SDL_EGL_LoadLibraryOnly(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *path);
ബാഹ്യ bool SDL_EGL_LoadLibrary(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *path, NativeDisplayType native_display);
ബാഹ്യ SDL_FunctionPointer SDL_EGL_GetProcAddressInternal(SDL_VideoDevice *_this, സ്ഥിരം അക്ഷരം *proc);
ബാഹ്യ ശൂന്യം SDL_EGL_UnloadLibrary(SDL_VideoDevice *_this);
ബാഹ്യ ശൂന്യം SDL_EGL_SetRequiredVisualId(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ visual_id);
ബാഹ്യ bool SDL_EGL_ChooseConfig(SDL_VideoDevice *_this);
ബാഹ്യ bool SDL_EGL_SetSwapInterval(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ interval);
ബാഹ്യ bool SDL_EGL_GetSwapInterval(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ *interval);
ബാഹ്യ bool SDL_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
ബാഹ്യ EGLSurface SDL_EGL_CreateSurface(SDL_VideoDevice *_this, SDL_Window *window, NativeWindowType nw);
ബാഹ്യ ശൂന്യം SDL_EGL_DestroySurface(SDL_VideoDevice *_this, EGLSurface egl_surface);

ബാഹ്യ EGLSurface SDL_EGL_CreateOffscreenSurface(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ width, പൂർണ്ണസംഖ്യ height);
// Assumes that LoadLibraryOnly() has succeeded
ബാഹ്യ bool SDL_EGL_InitializeOffscreen(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ device);

// These need to be wrapped to get the surface for the window by the platform GLES implementation
ബാഹ്യ SDL_GLContext SDL_EGL_CreateContext(SDL_VideoDevice *_this, EGLSurface egl_surface);
ബാഹ്യ bool SDL_EGL_MakeCurrent(SDL_VideoDevice *_this, EGLSurface egl_surface, SDL_GLContext context);
ബാഹ്യ bool SDL_EGL_SwapBuffers(SDL_VideoDevice *_this, EGLSurface egl_surface);

// SDL Error-reporting
ബാഹ്യ bool SDL_EGL_SetErrorEx(സ്ഥിരം അക്ഷരം *message, സ്ഥിരം അക്ഷരം *eglFunctionName, EGLint eglErrorCode);
#define SDL_EGL_SetError(message, eglFunctionName) SDL_EGL_SetErrorEx(message, eglFunctionName, _this->egl_data->eglGetError())

// A few of useful macros

#define SDL_EGL_SwapWindow_impl(BACKEND)                                                        \
    bool BACKEND##_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window)                  \
    {                                                                                           \
        തിരികെ SDL_EGL_SwapBuffers(_this, window->internal->egl_surface);                       \
    }

#define SDL_EGL_MakeCurrent_impl(BACKEND)                                                                    \
    bool BACKEND##_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context)       \
    {                                                                                                        \
        തിരികെ SDL_EGL_MakeCurrent(_this, window ? window->internal->egl_surface : EGL_NO_SURFACE, context); \
    }

#define SDL_EGL_CreateContext_impl(BACKEND)                                                     \
    SDL_GLContext BACKEND##_GLES_CreateContext(SDL_VideoDevice *_this, SDL_Window *window)      \
    {                                                                                           \
        തിരികെ SDL_EGL_CreateContext(_this, window->internal->egl_surface);                     \
    }

#endif // SDL_VIDEO_OPENGL_EGL

#endif // SDL_egl_h_
