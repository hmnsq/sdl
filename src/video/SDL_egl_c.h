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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితం_కాకపోతే SDL_egl_h_
#నిర్వచించు SDL_egl_h_

#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL

#అన్తర్భావ <SDL3/SDL_egl.h>

#అన్తర్భావ "SDL_sysvideo.h"

#నిర్వచించు SDL_EGL_MAX_DEVICES 8

// For systems that don't define these
రకనిర్వచనం intptr_t EGLAttrib;
రకనిర్వచనం శూన్య *EGLDeviceEXT;
రకనిర్వచనం EGLDisplay (EGLAPIENTRYP PFNEGLGETDISPLAYPROC) (EGLNativeDisplayType display_id);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLINITIALIZEPROC) (EGLDisplay dpy, EGLint *major, EGLint *minor);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLTERMINATEPROC) (EGLDisplay dpy);
రకనిర్వచనం __eglMustCastToProperFunctionPointerType (EGLAPIENTRYP PFNEGLGETPROCADDRESSPROC) (స్థిరరాశి అక్షరం *procname);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLCHOOSECONFIGPROC) (EGLDisplay dpy, స్థిరరాశి EGLint *attrib_list, EGLConfig *configs, EGLint config_కొలత, EGLint *అంకె_config);
రకనిర్వచనం EGLContext (EGLAPIENTRYP PFNEGLCREATECONTEXTPROC) (EGLDisplay dpy, EGLConfig config, EGLContext share_context, స్థిరరాశి EGLint *attrib_list);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYCONTEXTPROC) (EGLDisplay dpy, EGLContext ctx);
రకనిర్వచనం EGLSurface (EGLAPIENTRYP PFNEGLCREATEPBUFFERSURFACEPROC) (EGLDisplay dpy, EGLConfig config, స్థిరరాశి EGLint *attrib_list);
రకనిర్వచనం EGLSurface (EGLAPIENTRYP PFNEGLCREATEWINDOWSURFACEPROC) (EGLDisplay dpy, EGLConfig config, EGLNative_కిటికీ_Type win, స్థిరరాశి EGLint *attrib_list);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSURFACEPROC) (EGLDisplay dpy, EGLSurface surface);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLMAKECURRENTPROC) (EGLDisplay dpy, EGLSurface draw, EGLSurface పఠ, EGLContext ctx);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSPROC) (EGLDisplay dpy, EGLSurface surface);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLSWAPINTERVALPROC) (EGLDisplay dpy, EGLint interval);
రకనిర్వచనం స్థిరరాశి అక్షరం *(EGLAPIENTRYP PFNEGLQUERYSTRINGPROC) (EGLDisplay dpy, EGLint name);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLGETCONFIGATTRIBPROC) (EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *విలువ);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLWAITNATIVEPROC) (EGLint engine);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLWAITGLPROC) (శూన్య);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLBINDAPIPROC) (EGLenum api);
రకనిర్వచనం EGLint (EGLAPIENTRYP PFNEGLGETERRORPROC) (శూన్య);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICESEXTPROC) (EGLint max_devices, EGLDeviceEXT *devices, EGLint *అంకె_devices);
రకనిర్వచనం EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYPROC) (EGLenum platform, శూన్య *native_display, స్థిరరాశి EGLAttrib *attrib_list);
రకనిర్వచనం EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYEXTPROC) (EGLenum platform, శూన్య *native_display, స్థిరరాశి EGLint *attrib_list);
రకనిర్వచనం EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESYNCKHRPROC) (EGLDisplay dpy, EGLenum type, స్థిరరాశి EGLint *attrib_list);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync);
రకనిర్వచనం EGLint (EGLAPIENTRYP PFNEGLDUPNATIVEFENCEFDANDROIDPROC) (EGLDisplay dpy, EGLSyncKHR sync);
రకనిర్వచనం EGLint (EGLAPIENTRYP PFNEGLWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
రకనిర్వచనం EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);

రకనిర్వచనం నిర్మాణం SDL_EGL_Video_దత్తాంశం
{
    SDL_SharedObject *opengl_dll_handle;
    SDL_SharedObject *egl_dll_handle;
    EGLDisplay egl_display;
    EGLConfig egl_config;
    పూర్ణాంకం egl_swapinterval;
    పూర్ణాంకం egl_surfacetype;
    పూర్ణాంకం egl_సంస్కరణ_major, egl_సంస్కరణ_minor;
    EGLint egl_required_visual_id;
    bool is_offscreen; // whether EGL display was offscreen
    EGLenum apitype;       // EGL_OPENGL_ES_API, EGL_OPENGL_API, etc

    PFNEGLGETDISPLAYPROC eglGetDisplay;
    PFNEGLINITIALIZEPROC eglInitialize;
    PFNEGLTERMINATEPROC eglTerminate;
    PFNEGLGETPROCADDRESSPROC egl_Get_Proc_చిరునామా;
    PFNEGLCHOOSECONFIGPROC egl_ఎంచుకో_Config;
    PFNEGLCREATECONTEXTPROC eglCreateContext;
    PFNEGLDESTROYCONTEXTPROC eglDestroyContext;
    PFNEGLCREATEPBUFFERSURFACEPROC eglCreatePbufferSurface;
    PFNEGLCREATEWINDOWSURFACEPROC egl_Create_కిటికీ_Surface;
    PFNEGLDESTROYSURFACEPROC eglDestroySurface;
    PFNEGLMAKECURRENTPROC eglMakeCurrent;
    PFNEGLSWAPBUFFERSPROC egl_మార్పిడి_Buffers;
    PFNEGLSWAPINTERVALPROC egl_మార్పిడి_Interval;
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
} SDL_EGL_Video_దత్తాంశం;

// OpenGLES functions
రకనిర్వచనం గణన SDL_EGL_ExtensionType
{
    SDL_EGL_DISPLAY_EXTENSION,
    SDL_EGL_CLIENT_EXTENSION
} SDL_EGL_ExtensionType;

బాహ్య bool SDL_EGL_HasExtension(SDL_VideoDevice *_this, SDL_EGL_ExtensionType type, స్థిరరాశి అక్షరం *ext);

బాహ్య bool SDL_EGL_GetAttribute(SDL_VideoDevice *_this, SDL_GLAttr attrib, పూర్ణాంకం *విలువ);
బాహ్య bool SDL_EGL_ఎక్కించు_Library_Only(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం);
బాహ్య bool SDL_EGL_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం, NativeDisplayType native_display);
బాహ్య SDL_Function_సూచిక SDL_EGL_Get_Proc_చిరునామా_అంతర్గత(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *proc);
బాహ్య శూన్య SDL_EGL_UnloadLibrary(SDL_VideoDevice *_this);
బాహ్య శూన్య SDL_EGL_సమితి_Required_Visual_Id(SDL_VideoDevice *_this, పూర్ణాంకం visual_id);
బాహ్య bool SDL_EGL_ఎంచుకో_Config(SDL_VideoDevice *_this);
బాహ్య bool SDL_EGL_సమితి_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం interval);
బాహ్య bool SDL_EGL_Get_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం *interval);
బాహ్య bool SDL_EGL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);
బాహ్య EGLSurface SDL_EGL_CreateSurface(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, Native_కిటికీ_Type nw);
బాహ్య శూన్య SDL_EGL_DestroySurface(SDL_VideoDevice *_this, EGLSurface egl_surface);

బాహ్య EGLSurface SDL_EGL_CreateOffscreenSurface(SDL_VideoDevice *_this, పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు);
// Assumes that LoadLibraryOnly() has succeeded
బాహ్య bool SDL_EGL_InitializeOffscreen(SDL_VideoDevice *_this, పూర్ణాంకం device);

// These need to be wrapped to get the surface for the window by the platform GLES implementation
బాహ్య SDL_GLContext SDL_EGL_CreateContext(SDL_VideoDevice *_this, EGLSurface egl_surface);
బాహ్య bool SDL_EGL_MakeCurrent(SDL_VideoDevice *_this, EGLSurface egl_surface, SDL_GLContext context);
బాహ్య bool SDL_EGL_మార్పిడి_Buffers(SDL_VideoDevice *_this, EGLSurface egl_surface);

// SDL Error-reporting
బాహ్య bool SDL_EGL_సమితి_Error_Ex(స్థిరరాశి అక్షరం *సందేశం, స్థిరరాశి అక్షరం *eglFunctionName, EGLint egl_Error_సంకేతం);
#నిర్వచించు SDL_EGL_సమితి_Error(సందేశం, eglFunctionName) SDL_EGL_సమితి_Error_Ex(సందేశం, eglFunctionName, _this->egl_దత్తాంశం->eglGetError())

// A few of useful macros

#నిర్వచించు SDL_EGL_మార్పిడి_కిటికీ_impl(BACKEND)                                                        \
    bool BACKEND##_GLES_SwapWindow(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)                  \
    {                                                                                           \
        తిరిగి SDL_EGL_మార్పిడి_Buffers(_this, కిటికీ->అంతర్గత->egl_surface);                       \
    }

#నిర్వచించు SDL_EGL_MakeCurrent_impl(BACKEND)                                                                    \
    bool BACKEND##_GLES_MakeCurrent(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_GLContext context)       \
    {                                                                                                        \
        తిరిగి SDL_EGL_MakeCurrent(_this, కిటికీ ? కిటికీ->అంతర్గత->egl_surface : EGL_NO_SURFACE, context); \
    }

#నిర్వచించు SDL_EGL_CreateContext_impl(BACKEND)                                                     \
    SDL_GLContext BACKEND##_GLES_CreateContext(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)      \
    {                                                                                           \
        తిరిగి SDL_EGL_CreateContext(_this, కిటికీ->అంతర్గత->egl_surface);                     \
    }

#అయితే_ముగింపు // SDL_VIDEO_OPENGL_EGL

#అయితే_ముగింపు // SDL_egl_h_
