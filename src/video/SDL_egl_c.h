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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_egl_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_egl_h_

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL

#ಅನ್ತರ್ಭಾವ <SDL3/SDL_egl.h>

#ಅನ್ತರ್ಭಾವ "SDL_sysvideo.h"

#ವ್ಯಾಖ್ಯಾನಿಸು SDL_EGL_MAX_DEVICES 8

// For systems that don't define these
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ intptr_t EGLAttrib;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ *EGLDeviceEXT;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLDisplay (EGLAPIENTRYP PFNEGLGETDISPLAYPROC) (EGLNativeDisplayType display_id);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLINITIALIZEPROC) (EGLDisplay dpy, EGLint *major, EGLint *minor);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLTERMINATEPROC) (EGLDisplay dpy);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ __eglMustCastToProperFunctionPointerType (EGLAPIENTRYP PFNEGLGETPROCADDRESSPROC) (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *procname);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLCHOOSECONFIGPROC) (EGLDisplay dpy, ಸ್ಥಿರಾಂಕ EGLint *attrib_list, EGLConfig *configs, EGLint config_ಗಾತ್ರ, EGLint *ಅಂಕೆ_config);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLContext (EGLAPIENTRYP PFNEGLCREATECONTEXTPROC) (EGLDisplay dpy, EGLConfig config, EGLContext share_context, ಸ್ಥಿರಾಂಕ EGLint *attrib_list);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYCONTEXTPROC) (EGLDisplay dpy, EGLContext ctx);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLSurface (EGLAPIENTRYP PFNEGLCREATEPBUFFERSURFACEPROC) (EGLDisplay dpy, EGLConfig config, ಸ್ಥಿರಾಂಕ EGLint *attrib_list);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLSurface (EGLAPIENTRYP PFNEGLCREATEWINDOWSURFACEPROC) (EGLDisplay dpy, EGLConfig config, EGLNative_ಕಿಟಕಿ_Type win, ಸ್ಥಿರಾಂಕ EGLint *attrib_list);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSURFACEPROC) (EGLDisplay dpy, EGLSurface surface);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLMAKECURRENTPROC) (EGLDisplay dpy, EGLSurface draw, EGLSurface ಪಠ, EGLContext ctx);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSPROC) (EGLDisplay dpy, EGLSurface surface);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLSWAPINTERVALPROC) (EGLDisplay dpy, EGLint interval);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *(EGLAPIENTRYP PFNEGLQUERYSTRINGPROC) (EGLDisplay dpy, EGLint name);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLGETCONFIGATTRIBPROC) (EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *ಮೌಲ್ಯ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLWAITNATIVEPROC) (EGLint engine);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLWAITGLPROC) (ಶೂನ್ಯ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLBINDAPIPROC) (EGLenum api);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLint (EGLAPIENTRYP PFNEGLGETERRORPROC) (ಶೂನ್ಯ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICESEXTPROC) (EGLint max_devices, EGLDeviceEXT *devices, EGLint *ಅಂಕೆ_devices);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYPROC) (EGLenum platform, ಶೂನ್ಯ *native_display, ಸ್ಥಿರಾಂಕ EGLAttrib *attrib_list);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYEXTPROC) (EGLenum platform, ಶೂನ್ಯ *native_display, ಸ್ಥಿರಾಂಕ EGLint *attrib_list);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESYNCKHRPROC) (EGLDisplay dpy, EGLenum type, ಸ್ಥಿರಾಂಕ EGLint *attrib_list);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLint (EGLAPIENTRYP PFNEGLDUPNATIVEFENCEFDANDROIDPROC) (EGLDisplay dpy, EGLSyncKHR sync);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLint (EGLAPIENTRYP PFNEGLWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_EGL_Video_ದತ್ತಾಂಶ
{
    SDL_SharedObject *opengl_dll_handle;
    SDL_SharedObject *egl_dll_handle;
    EGLDisplay egl_display;
    EGLConfig egl_config;
    ಪೂರ್ಣಾಂಕ egl_swapinterval;
    ಪೂರ್ಣಾಂಕ egl_surfacetype;
    ಪೂರ್ಣಾಂಕ egl_ಆವೃತ್ತಿ_major, egl_ಆವೃತ್ತಿ_minor;
    EGLint egl_required_visual_id;
    bool is_offscreen; // whether EGL display was offscreen
    EGLenum apitype;       // EGL_OPENGL_ES_API, EGL_OPENGL_API, etc

    PFNEGLGETDISPLAYPROC eglGetDisplay;
    PFNEGLINITIALIZEPROC eglInitialize;
    PFNEGLTERMINATEPROC eglTerminate;
    PFNEGLGETPROCADDRESSPROC egl_Get_Proc_ವಿಳಾಸ;
    PFNEGLCHOOSECONFIGPROC egl_ಆರಿಸು_Config;
    PFNEGLCREATECONTEXTPROC eglCreateContext;
    PFNEGLDESTROYCONTEXTPROC eglDestroyContext;
    PFNEGLCREATEPBUFFERSURFACEPROC eglCreatePbufferSurface;
    PFNEGLCREATEWINDOWSURFACEPROC egl_Create_ಕಿಟಕಿ_Surface;
    PFNEGLDESTROYSURFACEPROC eglDestroySurface;
    PFNEGLMAKECURRENTPROC eglMakeCurrent;
    PFNEGLSWAPBUFFERSPROC egl_ಅದಲುಬದಲು_Buffers;
    PFNEGLSWAPINTERVALPROC egl_ಅದಲುಬದಲು_Interval;
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
} SDL_EGL_Video_ದತ್ತಾಂಶ;

// OpenGLES functions
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ SDL_EGL_ExtensionType
{
    SDL_EGL_DISPLAY_EXTENSION,
    SDL_EGL_CLIENT_EXTENSION
} SDL_EGL_ExtensionType;

ಬಾಹ್ಯ bool SDL_EGL_HasExtension(SDL_VideoDevice *_this, SDL_EGL_ExtensionType type, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ext);

ಬಾಹ್ಯ bool SDL_EGL_GetAttribute(SDL_VideoDevice *_this, SDL_GLAttr attrib, ಪೂರ್ಣಾಂಕ *ಮೌಲ್ಯ);
ಬಾಹ್ಯ bool SDL_EGL_ತುಂಬು_Library_Only(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ);
ಬಾಹ್ಯ bool SDL_EGL_ತುಂಬು_Library(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ, NativeDisplayType native_display);
ಬಾಹ್ಯ SDL_Function_ಸೂಚಕ SDL_EGL_Get_Proc_ವಿಳಾಸ_ಆಂತರಿಕ(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *proc);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_EGL_UnloadLibrary(SDL_VideoDevice *_this);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_EGL_ಗಣ_Required_Visual_Id(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ visual_id);
ಬಾಹ್ಯ bool SDL_EGL_ಆರಿಸು_Config(SDL_VideoDevice *_this);
ಬಾಹ್ಯ bool SDL_EGL_ಗಣ_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ interval);
ಬಾಹ್ಯ bool SDL_EGL_Get_ಅದಲುಬದಲು_Interval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ *interval);
ಬಾಹ್ಯ bool SDL_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
ಬಾಹ್ಯ EGLSurface SDL_EGL_CreateSurface(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, Native_ಕಿಟಕಿ_Type nw);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_EGL_DestroySurface(SDL_VideoDevice *_this, EGLSurface egl_surface);

ಬಾಹ್ಯ EGLSurface SDL_EGL_CreateOffscreenSurface(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ);
// Assumes that LoadLibraryOnly() has succeeded
ಬಾಹ್ಯ bool SDL_EGL_InitializeOffscreen(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ device);

// These need to be wrapped to get the surface for the window by the platform GLES implementation
ಬಾಹ್ಯ SDL_GLContext SDL_EGL_CreateContext(SDL_VideoDevice *_this, EGLSurface egl_surface);
ಬಾಹ್ಯ bool SDL_EGL_MakeCurrent(SDL_VideoDevice *_this, EGLSurface egl_surface, SDL_GLContext context);
ಬಾಹ್ಯ bool SDL_EGL_ಅದಲುಬದಲು_Buffers(SDL_VideoDevice *_this, EGLSurface egl_surface);

// SDL Error-reporting
ಬಾಹ್ಯ bool SDL_EGL_ಗಣ_Error_Ex(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸಂದೇಶ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *eglFunctionName, EGLint egl_Error_ಸಂಕೇತ);
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_EGL_ಗಣ_Error(ಸಂದೇಶ, eglFunctionName) SDL_EGL_ಗಣ_Error_Ex(ಸಂದೇಶ, eglFunctionName, _this->egl_ದತ್ತಾಂಶ->eglGetError())

// A few of useful macros

#ವ್ಯಾಖ್ಯಾನಿಸು SDL_EGL_ಅದಲುಬದಲು_ಕಿಟಕಿ_impl(BACKEND)                                                        \
    bool BACKEND##_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)                  \
    {                                                                                           \
        ಹಿಂತಿರುಗಿ SDL_EGL_ಅದಲುಬದಲು_Buffers(_this, ಕಿಟಕಿ->ಆಂತರಿಕ->egl_surface);                       \
    }

#ವ್ಯಾಖ್ಯಾನಿಸು SDL_EGL_MakeCurrent_impl(BACKEND)                                                                    \
    bool BACKEND##_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_GLContext context)       \
    {                                                                                                        \
        ಹಿಂತಿರುಗಿ SDL_EGL_MakeCurrent(_this, ಕಿಟಕಿ ? ಕಿಟಕಿ->ಆಂತರಿಕ->egl_surface : EGL_NO_SURFACE, context); \
    }

#ವ್ಯಾಖ್ಯಾನಿಸು SDL_EGL_CreateContext_impl(BACKEND)                                                     \
    SDL_GLContext BACKEND##_GLES_CreateContext(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)      \
    {                                                                                           \
        ಹಿಂತಿರುಗಿ SDL_EGL_CreateContext(_this, ಕಿಟಕಿ->ಆಂತರಿಕ->egl_surface);                     \
    }

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_OPENGL_EGL

#ಆದರೆ_ಅಂತ್ಯ // SDL_egl_h_
