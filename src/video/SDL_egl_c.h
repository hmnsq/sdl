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

#यदि_अपरिभाषितम् SDL_egl_h_
#परिभाषय SDL_egl_h_

#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL

#अन्तर्भाव <SDL3/SDL_egl.h>

#अन्तर्भाव "SDL_sysvideo.h"

#परिभाषय SDL_EGL_MAX_DEVICES 8

// For systems that don't define these
प्रकारनिर्देश intptr_t EGLAttrib;
प्रकारनिर्देश शून्य *EGLDeviceEXT;
प्रकारनिर्देश EGLDisplay (EGLAPIENTRYP PFNEGLGETDISPLAYPROC) (EGLNativeDisplayType display_id);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLINITIALIZEPROC) (EGLDisplay dpy, EGLint *major, EGLint *minor);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLTERMINATEPROC) (EGLDisplay dpy);
प्रकारनिर्देश __eglMustCastToProperFunctionPointerType (EGLAPIENTRYP PFNEGLGETPROCADDRESSPROC) (ध्रुव वर्ण *procname);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLCHOOSECONFIGPROC) (EGLDisplay dpy, ध्रुव EGLint *attrib_list, EGLConfig *configs, EGLint config_आकार, EGLint *अङ्कः_config);
प्रकारनिर्देश EGLContext (EGLAPIENTRYP PFNEGLCREATECONTEXTPROC) (EGLDisplay dpy, EGLConfig config, EGLContext share_context, ध्रुव EGLint *attrib_list);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYCONTEXTPROC) (EGLDisplay dpy, EGLContext ctx);
प्रकारनिर्देश EGLSurface (EGLAPIENTRYP PFNEGLCREATEPBUFFERSURFACEPROC) (EGLDisplay dpy, EGLConfig config, ध्रुव EGLint *attrib_list);
प्रकारनिर्देश EGLSurface (EGLAPIENTRYP PFNEGLCREATEWINDOWSURFACEPROC) (EGLDisplay dpy, EGLConfig config, EGLNative_गवाक्षः_Type win, ध्रुव EGLint *attrib_list);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSURFACEPROC) (EGLDisplay dpy, EGLSurface surface);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLMAKECURRENTPROC) (EGLDisplay dpy, EGLSurface draw, EGLSurface पठ, EGLContext ctx);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSPROC) (EGLDisplay dpy, EGLSurface surface);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLSWAPINTERVALPROC) (EGLDisplay dpy, EGLint interval);
प्रकारनिर्देश ध्रुव वर्ण *(EGLAPIENTRYP PFNEGLQUERYSTRINGPROC) (EGLDisplay dpy, EGLint name);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLGETCONFIGATTRIBPROC) (EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *मानम्);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLWAITNATIVEPROC) (EGLint engine);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLWAITGLPROC) (शून्य);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLBINDAPIPROC) (EGLenum api);
प्रकारनिर्देश EGLint (EGLAPIENTRYP PFNEGLGETERRORPROC) (शून्य);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICESEXTPROC) (EGLint max_devices, EGLDeviceEXT *devices, EGLint *अङ्कः_devices);
प्रकारनिर्देश EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYPROC) (EGLenum platform, शून्य *native_display, ध्रुव EGLAttrib *attrib_list);
प्रकारनिर्देश EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYEXTPROC) (EGLenum platform, शून्य *native_display, ध्रुव EGLint *attrib_list);
प्रकारनिर्देश EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESYNCKHRPROC) (EGLDisplay dpy, EGLenum type, ध्रुव EGLint *attrib_list);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync);
प्रकारनिर्देश EGLint (EGLAPIENTRYP PFNEGLDUPNATIVEFENCEFDANDROIDPROC) (EGLDisplay dpy, EGLSyncKHR sync);
प्रकारनिर्देश EGLint (EGLAPIENTRYP PFNEGLWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
प्रकारनिर्देश EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);

प्रकारनिर्देश संरचना SDL_EGL_Video_दत्त
{
    SDL_SharedObject *opengl_dll_handle;
    SDL_SharedObject *egl_dll_handle;
    EGLDisplay egl_display;
    EGLConfig egl_config;
    पूर्णाङ्क egl_swapinterval;
    पूर्णाङ्क egl_surfacetype;
    पूर्णाङ्क egl_संस्करणम्_major, egl_संस्करणम्_minor;
    EGLint egl_required_visual_id;
    bool is_offscreen; // whether EGL display was offscreen
    EGLenum apitype;       // EGL_OPENGL_ES_API, EGL_OPENGL_API, etc

    PFNEGLGETDISPLAYPROC eglGetDisplay;
    PFNEGLINITIALIZEPROC eglInitialize;
    PFNEGLTERMINATEPROC eglTerminate;
    PFNEGLGETPROCADDRESSPROC egl_Get_Proc_स्थानाङ्कः;
    PFNEGLCHOOSECONFIGPROC egl_वृणु_Config;
    PFNEGLCREATECONTEXTPROC eglCreateContext;
    PFNEGLDESTROYCONTEXTPROC eglDestroyContext;
    PFNEGLCREATEPBUFFERSURFACEPROC eglCreatePbufferSurface;
    PFNEGLCREATEWINDOWSURFACEPROC egl_Create_गवाक्षः_Surface;
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
} SDL_EGL_Video_दत्त;

// OpenGLES functions
प्रकारनिर्देश गणना SDL_EGL_ExtensionType
{
    SDL_EGL_DISPLAY_EXTENSION,
    SDL_EGL_CLIENT_EXTENSION
} SDL_EGL_ExtensionType;

बाह्य bool SDL_EGL_HasExtension(SDL_VideoDevice *_this, SDL_EGL_ExtensionType type, ध्रुव वर्ण *ext);

बाह्य bool SDL_EGL_GetAttribute(SDL_VideoDevice *_this, SDL_GLAttr attrib, पूर्णाङ्क *मानम्);
बाह्य bool SDL_EGL_आरोपय_Library_Only(SDL_VideoDevice *_this, ध्रुव वर्ण *मार्गः);
बाह्य bool SDL_EGL_आरोपय_Library(SDL_VideoDevice *_this, ध्रुव वर्ण *मार्गः, NativeDisplayType native_display);
बाह्य SDL_FunctionPointer SDL_EGL_Get_Proc_स्थानाङ्कः_आन्तरिकम्(SDL_VideoDevice *_this, ध्रुव वर्ण *proc);
बाह्य शून्य SDL_EGL_UnloadLibrary(SDL_VideoDevice *_this);
बाह्य शून्य SDL_EGL_समुच्चयः_Required_Visual_Id(SDL_VideoDevice *_this, पूर्णाङ्क visual_id);
बाह्य bool SDL_EGL_वृणु_Config(SDL_VideoDevice *_this);
बाह्य bool SDL_EGL_समुच्चयः_Swap_Interval(SDL_VideoDevice *_this, पूर्णाङ्क interval);
बाह्य bool SDL_EGL_GetSwapInterval(SDL_VideoDevice *_this, पूर्णाङ्क *interval);
बाह्य bool SDL_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
बाह्य EGLSurface SDL_EGL_CreateSurface(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, Native_गवाक्षः_Type nw);
बाह्य शून्य SDL_EGL_DestroySurface(SDL_VideoDevice *_this, EGLSurface egl_surface);

बाह्य EGLSurface SDL_EGL_CreateOffscreenSurface(SDL_VideoDevice *_this, पूर्णाङ्क विस्तारः, पूर्णाङ्क height);
// Assumes that LoadLibraryOnly() has succeeded
बाह्य bool SDL_EGL_InitializeOffscreen(SDL_VideoDevice *_this, पूर्णाङ्क device);

// These need to be wrapped to get the surface for the window by the platform GLES implementation
बाह्य SDL_GLContext SDL_EGL_CreateContext(SDL_VideoDevice *_this, EGLSurface egl_surface);
बाह्य bool SDL_EGL_MakeCurrent(SDL_VideoDevice *_this, EGLSurface egl_surface, SDL_GLContext context);
बाह्य bool SDL_EGL_SwapBuffers(SDL_VideoDevice *_this, EGLSurface egl_surface);

// SDL Error-reporting
बाह्य bool SDL_EGL_समुच्चयः_Error_Ex(ध्रुव वर्ण *सन्देशः, ध्रुव वर्ण *eglFunctionName, EGLint egl_Error_संहिता);
#परिभाषय SDL_EGL_समुच्चयः_Error(सन्देशः, eglFunctionName) SDL_EGL_समुच्चयः_Error_Ex(सन्देशः, eglFunctionName, _this->egl_दत्त->eglGetError())

// A few of useful macros

#परिभाषय SDL_EGL_Swap_गवाक्षः_impl(BACKEND)                                                        \
    bool BACKEND##_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)                  \
    {                                                                                           \
        प्रत्यागम SDL_EGL_SwapBuffers(_this, गवाक्षः->आन्तरिकम्->egl_surface);                       \
    }

#परिभाषय SDL_EGL_MakeCurrent_impl(BACKEND)                                                                    \
    bool BACKEND##_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_GLContext context)       \
    {                                                                                                        \
        प्रत्यागम SDL_EGL_MakeCurrent(_this, गवाक्षः ? गवाक्षः->आन्तरिकम्->egl_surface : EGL_NO_SURFACE, context); \
    }

#परिभाषय SDL_EGL_CreateContext_impl(BACKEND)                                                     \
    SDL_GLContext BACKEND##_GLES_CreateContext(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)      \
    {                                                                                           \
        प्रत्यागम SDL_EGL_CreateContext(_this, गवाक्षः->आन्तरिकम्->egl_surface);                     \
    }

#यदि_अन्तः // SDL_VIDEO_OPENGL_EGL

#यदि_अन्तः // SDL_egl_h_
