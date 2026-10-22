#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __egl_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ __egl_h_ 1

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ

/*
** Copyright 2013-2020 The Khronos Group Inc.
** SPDX-License-Identifier: Apache-2.0
**
** This header is generated from the Khronos EGL XML API Registry.
** The current version of the Registry, generator scripts
** used to make the header, and the header can be found at
**   http://www.khronos.org/registry/egl
**
** Khronos $Git commit SHA1: e80a2e0050 $ on $Git commit date: 2026-03-19 06:21:49 +0100 $
*/

#ਅਨ੍ਤਰ੍ਭਾਵ <EGL/eglplatform.h>

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EGL_PROTOTYPES
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EGL_PROTOTYPES 1
#ਜੇ_ਅੰਤ

/* Generated on date 20260319 */

/* Generated C header for:
 * API: egl
 * Versions considered: .*
 * Versions emitted: .*
 * Default extensions included: None
 * Additional extensions included: _nomatch_^
 * Extensions removed: _nomatch_^
 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_ਸੰਸਕਰਣ_1_0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਸੰਸਕਰਣ_1_0 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ EGLBoolean;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ *EGLDisplay;
#ਅਨ੍ਤਰ੍ਭਾਵ <KHR/khrplatform.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <EGL/eglplatform.h>
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ *EGLConfig;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ *EGLSurface;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ *EGLContext;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (*__eglMustCastToProperFunctionPointerType)(ਖਾਲੀ);
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ALPHA_ਮਾਪ                    0x3021
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_BAD_ACCESS                    0x3002
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_BAD_ALLOC                     0x3003
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_BAD_ATTRIBUTE                 0x3004
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_BAD_CONFIG                    0x3005
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_BAD_CONTEXT                   0x3006
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_BAD_CURRENT_SURFACE           0x3007
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_BAD_DISPLAY                   0x3008
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_BAD_ਮੇਲ                     0x3009
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_BAD_NATIVE_PIXMAP             0x300A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_BAD_NATIVE_ਖਿੜਕੀ             0x300B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_BAD_PARAMETER                 0x300C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_BAD_SURFACE                   0x300D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_BLUE_ਮਾਪ                     0x3022
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਬਫਰ_ਮਾਪ                   0x3020
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONFIG_CAVEAT                 0x3027
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONFIG_ID                     0x3028
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CORE_NATIVE_ENGINE            0x305B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਡੂੰਘਾਈ_ਮਾਪ                    0x3025
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DONT_CARE                     EGL_CAST(EGLint,-1)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DRAW                          0x3059
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXTENSIONS                    0x3055
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_FALSE                         0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GREEN_ਮਾਪ                    0x3023
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਉਚਾਈ                        0x3056
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਸਭ_ਤੋਂ_ਵੱਡਾ_PBUFFER               0x3058
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_LEVEL                         0x3029
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_MAX_PBUFFER_ਉਚਾਈ            0x302A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_MAX_PBUFFER_PIXELS            0x302B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_MAX_PBUFFER_ਚੌੜਾਈ             0x302C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NATIVE_RENDERABLE             0x302D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NATIVE_VISUAL_ID              0x302E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NATIVE_VISUAL_TYPE            0x302F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NONE                          0x3038
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NON_CONFORMANT_CONFIG         0x3051
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NOT_INITIALIZED               0x3001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NO_CONTEXT                    EGL_CAST(EGLContext,0)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NO_DISPLAY                    EGL_CAST(EGLDisplay,0)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NO_SURFACE                    EGL_CAST(EGLSurface,0)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_PBUFFER_ਦੋਆਧਾਰੀ_ਅੰਕ                   0x0001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_PIXMAP_ਦੋਆਧਾਰੀ_ਅੰਕ                    0x0002
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_READ                          0x305A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_RED_ਮਾਪ                      0x3024
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SAMPLES                       0x3031
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SAMPLE_BUFFERS                0x3032
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SLOW_CONFIG                   0x3050
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_STENCIL_ਮਾਪ                  0x3026
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SUCCESS                       0x3000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SURFACE_TYPE                  0x3033
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_TRANSPARENT_BLUE_ਮੁੱਲ        0x3035
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_TRANSPARENT_GREEN_ਮੁੱਲ       0x3036
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_TRANSPARENT_RED_ਮੁੱਲ         0x3037
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_TRANSPARENT_RGB               0x3052
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_TRANSPARENT_TYPE              0x3034
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_TRUE                          1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_VENDOR                        0x3053
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਸੰਸਕਰਣ                       0x3054
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਚੌੜਾਈ                         0x3057
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਖਿੜਕੀ_ਦੋਆਧਾਰੀ_ਅੰਕ                    0x0004
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLCHOOSECONFIGPROC) (EGLDisplay dpy, ਅਚਲ EGLint *attrib_list, EGLConfig *configs, EGLint config_ਮਾਪ, EGLint *ਅੰਕ_config);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLCOPYBUFFERSPROC) (EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType ਨਿਸ਼ਾਨਾ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLContext (EGLAPIENTRYP PFNEGLCREATECONTEXTPROC) (EGLDisplay dpy, EGLConfig config, EGLContext share_context, ਅਚਲ EGLint *attrib_list);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLSurface (EGLAPIENTRYP PFNEGLCREATEPBUFFERSURFACEPROC) (EGLDisplay dpy, EGLConfig config, ਅਚਲ EGLint *attrib_list);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLSurface (EGLAPIENTRYP PFNEGLCREATEPIXMAPSURFACEPROC) (EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, ਅਚਲ EGLint *attrib_list);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLSurface (EGLAPIENTRYP PFNEGLCREATEWINDOWSURFACEPROC) (EGLDisplay dpy, EGLConfig config, EGLNative_ਖਿੜਕੀ_Type win, ਅਚਲ EGLint *attrib_list);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYCONTEXTPROC) (EGLDisplay dpy, EGLContext ctx);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSURFACEPROC) (EGLDisplay dpy, EGLSurface surface);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLGETCONFIGATTRIBPROC) (EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLGETCONFIGSPROC) (EGLDisplay dpy, EGLConfig *configs, EGLint config_ਮਾਪ, EGLint *ਅੰਕ_config);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLDisplay (EGLAPIENTRYP PFNEGLGETCURRENTDISPLAYPROC) (ਖਾਲੀ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLSurface (EGLAPIENTRYP PFNEGLGETCURRENTSURFACEPROC) (EGLint readdraw);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLDisplay (EGLAPIENTRYP PFNEGLGETDISPLAYPROC) (EGLNativeDisplayType display_id);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLint (EGLAPIENTRYP PFNEGLGETERRORPROC) (ਖਾਲੀ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ __eglMustCastToProperFunctionPointerType (EGLAPIENTRYP PFNEGLGETPROCADDRESSPROC) (ਅਚਲ ਅੱਖਰ *procname);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLINITIALIZEPROC) (EGLDisplay dpy, EGLint *major, EGLint *minor);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLMAKECURRENTPROC) (EGLDisplay dpy, EGLSurface draw, EGLSurface ਪਠ, EGLContext ctx);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYCONTEXTPROC) (EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਅਚਲ ਅੱਖਰ *(EGLAPIENTRYP PFNEGLQUERYSTRINGPROC) (EGLDisplay dpy, EGLint name);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSURFACEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSPROC) (EGLDisplay dpy, EGLSurface surface);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLTERMINATEPROC) (EGLDisplay dpy);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLWAITGLPROC) (ਖਾਲੀ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLWAITNATIVEPROC) (EGLint engine);
#ਜੇ EGL_EGL_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_ਚੁਣੋ_Config (EGLDisplay dpy, ਅਚਲ EGLint *attrib_list, EGLConfig *configs, EGLint config_ਮਾਪ, EGLint *ਅੰਕ_config);
EGLAPI EGLBoolean EGLAPIENTRY eglCopyBuffers (EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType ਨਿਸ਼ਾਨਾ);
EGLAPI EGLContext EGLAPIENTRY eglCreateContext (EGLDisplay dpy, EGLConfig config, EGLContext share_context, ਅਚਲ EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePbufferSurface (EGLDisplay dpy, EGLConfig config, ਅਚਲ EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePixmapSurface (EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, ਅਚਲ EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY egl_Create_ਖਿੜਕੀ_Surface (EGLDisplay dpy, EGLConfig config, EGLNative_ਖਿੜਕੀ_Type win, ਅਚਲ EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyContext (EGLDisplay dpy, EGLContext ctx);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySurface (EGLDisplay dpy, EGLSurface surface);
EGLAPI EGLBoolean EGLAPIENTRY eglGetConfigAttrib (EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *ਮੁੱਲ);
EGLAPI EGLBoolean EGLAPIENTRY eglGetConfigs (EGLDisplay dpy, EGLConfig *configs, EGLint config_ਮਾਪ, EGLint *ਅੰਕ_config);
EGLAPI EGLDisplay EGLAPIENTRY eglGetCurrentDisplay (ਖਾਲੀ);
EGLAPI EGLSurface EGLAPIENTRY eglGetCurrentSurface (EGLint readdraw);
EGLAPI EGLDisplay EGLAPIENTRY eglGetDisplay (EGLNativeDisplayType display_id);
EGLAPI EGLint EGLAPIENTRY eglGetError (ਖਾਲੀ);
EGLAPI __eglMustCastToProperFunctionPointerType EGLAPIENTRY egl_Get_Proc_ਪਤਾ (ਅਚਲ ਅੱਖਰ *procname);
EGLAPI EGLBoolean EGLAPIENTRY eglInitialize (EGLDisplay dpy, EGLint *major, EGLint *minor);
EGLAPI EGLBoolean EGLAPIENTRY eglMakeCurrent (EGLDisplay dpy, EGLSurface draw, EGLSurface ਪਠ, EGLContext ctx);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryContext (EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint *ਮੁੱਲ);
EGLAPI ਅਚਲ ਅੱਖਰ *EGLAPIENTRY eglQueryString (EGLDisplay dpy, EGLint name);
EGLAPI EGLBoolean EGLAPIENTRY eglQuerySurface (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint *ਮੁੱਲ);
EGLAPI EGLBoolean EGLAPIENTRY egl_ਅਦਲਾ_ਬਦਲੀ_Buffers (EGLDisplay dpy, EGLSurface surface);
EGLAPI EGLBoolean EGLAPIENTRY eglTerminate (EGLDisplay dpy);
EGLAPI EGLBoolean EGLAPIENTRY eglWaitGL (ਖਾਲੀ);
EGLAPI EGLBoolean EGLAPIENTRY eglWaitNative (EGLint engine);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_VERSION_1_0 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_ਸੰਸਕਰਣ_1_1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਸੰਸਕਰਣ_1_1 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਪਿੱਠ_ਬਫਰ                   0x3084
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_BIND_ਮੰਜ਼ਿਲ_TEXTURE_RGB           0x3039
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_BIND_ਮੰਜ਼ਿਲ_TEXTURE_RGBA          0x303A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONTEXT_ਗੁਆਚਾ                  0x300E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_MIN_ਅਦਲਾ_ਬਦਲੀ_INTERVAL             0x303B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_MAX_ਅਦਲਾ_ਬਦਲੀ_INTERVAL             0x303C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_MIPMAP_TEXTURE                0x3082
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_MIPMAP_LEVEL                  0x3083
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NO_TEXTURE                    0x305C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_TEXTURE_2D                    0x305F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_TEXTURE_FORMAT                0x3080
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_TEXTURE_RGB                   0x305D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_TEXTURE_RGBA                  0x305E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_TEXTURE_ਨਿਸ਼ਾਨਾ                0x3081
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLBINDTEXIMAGEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint ਬਫਰ_2);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLRELEASETEXIMAGEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint ਬਫਰ_2);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLSURFACEATTRIBPROC) (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLSWAPINTERVALPROC) (EGLDisplay dpy, EGLint interval);
#ਜੇ EGL_EGL_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglBindTexImage (EGLDisplay dpy, EGLSurface surface, EGLint ਬਫਰ_2);
EGLAPI EGLBoolean EGLAPIENTRY eglReleaseTexImage (EGLDisplay dpy, EGLSurface surface, EGLint ਬਫਰ_2);
EGLAPI EGLBoolean EGLAPIENTRY eglSurfaceAttrib (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint ਮੁੱਲ);
EGLAPI EGLBoolean EGLAPIENTRY egl_ਅਦਲਾ_ਬਦਲੀ_Interval (EGLDisplay dpy, EGLint interval);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_VERSION_1_1 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_ਸੰਸਕਰਣ_1_2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਸੰਸਕਰਣ_1_2 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ EGLenum;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ *EGLClient_ਬਫਰ;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ALPHA_FORMAT                  0x3088
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ALPHA_FORMAT_NONPRE           0x308B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ALPHA_FORMAT_PRE              0x308C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ALPHA_ਨਕਾਬ_ਮਾਪ               0x303E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਬਫਰ_PRESERVED              0x3094
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਬਫਰ_DESTROYED              0x3095
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CLIENT_APIS                   0x308D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_COLORSPACE                    0x3087
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_COLORSPACE_sRGB               0x3089
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_COLORSPACE_ਰੇਖਿਕ             0x308A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_COLOR_ਬਫਰ_TYPE             0x303F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONTEXT_CLIENT_TYPE           0x3097
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DISPLAY_SCALING               10000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_HORIZONTAL_RESOLUTION         0x3090
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_LUMINANCE_ਬਫਰ              0x308F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_LUMINANCE_ਮਾਪ                0x303D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_OPENGL_ES_ਦੋਆਧਾਰੀ_ਅੰਕ                 0x0001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_OPENVG_ਦੋਆਧਾਰੀ_ਅੰਕ                    0x0002
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_OPENGL_ES_API                 0x30A0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_OPENVG_API                    0x30A1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_OPENVG_IMAGE                  0x3096
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_PIXEL_ASPECT_ਅਨੁਪਾਤ            0x3092
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_RENDERABLE_TYPE               0x3040
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_RENDER_ਬਫਰ                 0x3086
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_RGB_ਬਫਰ                    0x308E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SINGLE_ਬਫਰ                 0x3085
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਅਦਲਾ_ਬਦਲੀ_BEHAVIOR                 0x3093
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_UNKNOWN                       EGL_CAST(EGLint,-1)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_VERTICAL_RESOLUTION           0x3091
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLBINDAPIPROC) (EGLenum api);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLenum (EGLAPIENTRYP PFNEGLQUERYAPIPROC) (ਖਾਲੀ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLSurface (EGLAPIENTRYP PFNEGLCREATEPBUFFERFROMCLIENTBUFFERPROC) (EGLDisplay dpy, EGLenum buftype, EGLClient_ਬਫਰ ਬਫਰ_2, EGLConfig config, ਅਚਲ EGLint *attrib_list);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLRELEASETHREADPROC) (ਖਾਲੀ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLWAITCLIENTPROC) (ਖਾਲੀ);
#ਜੇ EGL_EGL_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglBindAPI (EGLenum api);
EGLAPI EGLenum EGLAPIENTRY eglQueryAPI (ਖਾਲੀ);
EGLAPI EGLSurface EGLAPIENTRY egl_Create_Pbuffer_From_Client_ਬਫਰ (EGLDisplay dpy, EGLenum buftype, EGLClient_ਬਫਰ ਬਫਰ_2, EGLConfig config, ਅਚਲ EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglReleaseThread (ਖਾਲੀ);
EGLAPI EGLBoolean EGLAPIENTRY eglWaitClient (ਖਾਲੀ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_VERSION_1_2 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_ਸੰਸਕਰਣ_1_3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਸੰਸਕਰਣ_1_3 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONFORMANT                    0x3042
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONTEXT_CLIENT_ਸੰਸਕਰਣ        0x3098
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਮੇਲ_NATIVE_PIXMAP           0x3041
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_OPENGL_ES2_ਦੋਆਧਾਰੀ_ਅੰਕ                0x0004
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_VG_ALPHA_FORMAT               0x3088
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_VG_ALPHA_FORMAT_NONPRE        0x308B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_VG_ALPHA_FORMAT_PRE           0x308C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_VG_ALPHA_FORMAT_PRE_ਦੋਆਧਾਰੀ_ਅੰਕ       0x0040
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_VG_COLORSPACE                 0x3087
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_VG_COLORSPACE_sRGB            0x3089
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_VG_COLORSPACE_ਰੇਖਿਕ          0x308A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_VG_COLORSPACE_ਰੇਖਿਕ_ਦੋਆਧਾਰੀ_ਅੰਕ      0x0020
#ਜੇ_ਅੰਤ /* EGL_VERSION_1_3 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_ਸੰਸਕਰਣ_1_4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਸੰਸਕਰਣ_1_4 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DEFAULT_DISPLAY               EGL_CAST(EGLNativeDisplayType,0)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_MULTISAMPLE_RESOLVE_BOX_ਦੋਆਧਾਰੀ_ਅੰਕ   0x0200
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_MULTISAMPLE_RESOLVE           0x3099
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_MULTISAMPLE_RESOLVE_DEFAULT   0x309A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_MULTISAMPLE_RESOLVE_BOX       0x309B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_OPENGL_API                    0x30A2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_OPENGL_ਦੋਆਧਾਰੀ_ਅੰਕ                    0x0008
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਅਦਲਾ_ਬਦਲੀ_BEHAVIOR_PRESERVED_ਦੋਆਧਾਰੀ_ਅੰਕ   0x0400
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLContext (EGLAPIENTRYP PFNEGLGETCURRENTCONTEXTPROC) (ਖਾਲੀ);
#ਜੇ EGL_EGL_PROTOTYPES
EGLAPI EGLContext EGLAPIENTRY eglGetCurrentContext (ਖਾਲੀ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_VERSION_1_4 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_ਸੰਸਕਰਣ_1_5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਸੰਸਕਰਣ_1_5 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ *EGLSync;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ intptr_t EGLAttrib;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ khronos_utime_nanoseconds_t EGLTime;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ *EGLImage;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONTEXT_MAJOR_ਸੰਸਕਰਣ         0x3098
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONTEXT_MINOR_ਸੰਸਕਰਣ         0x30FB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONTEXT_OPENGL_PROFILE_ਨਕਾਬ   0x30FD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY 0x31BD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NO_RESET_NOTIFICATION         0x31BE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_LOSE_CONTEXT_ON_RESET         0x31BF
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONTEXT_OPENGL_CORE_PROFILE_ਦੋਆਧਾਰੀ_ਅੰਕ 0x00000001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_ਦੋਆਧਾਰੀ_ਅੰਕ 0x00000002
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONTEXT_OPENGL_DEBUG          0x31B0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE 0x31B1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONTEXT_OPENGL_ROBUST_ACCESS  0x31B2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_OPENGL_ES3_ਦੋਆਧਾਰੀ_ਅੰਕ                0x00000040
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CL_EVENT_HANDLE               0x309C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SYNC_CL_EVENT                 0x30FE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SYNC_CL_EVENT_COMPLETE        0x30FF
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SYNC_ਪੂਰਵ_COMMANDS_COMPLETE  0x30F0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SYNC_TYPE                     0x30F7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SYNC_ਸਥਿਤੀ                   0x30F1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SYNC_CONDITION                0x30F8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SIGNALED                      0x30F2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_UNSIGNALED                    0x30F3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SYNC_FLUSH_COMMANDS_ਦੋਆਧਾਰੀ_ਅੰਕ       0x0001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_FOREVER                       0xFFFFFFFFFFFFFFFFull
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_TIMEOUT_EXPIRED               0x30F5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONDITION_SATISFIED           0x30F6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NO_SYNC                       EGL_CAST(EGLSync,0)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SYNC_FENCE                    0x30F9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_COLORSPACE                 0x309D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_COLORSPACE_SRGB            0x3089
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_COLORSPACE_ਰੇਖਿਕ          0x308A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_RENDERBUFFER               0x30B9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_TEXTURE_2D                 0x30B1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_TEXTURE_LEVEL              0x30BC
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_TEXTURE_3D                 0x30B2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_TEXTURE_ZOFFSET            0x30BD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_TEXTURE_CUBE_MAP_ਸਕਾਰਾਤਮਕ_X 0x30B3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_X 0x30B4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_TEXTURE_CUBE_MAP_ਸਕਾਰਾਤਮਕ_Y 0x30B5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Y 0x30B6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_TEXTURE_CUBE_MAP_ਸਕਾਰਾਤਮਕ_Z 0x30B7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 0x30B8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_IMAGE_PRESERVED               0x30D2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NO_IMAGE                      EGL_CAST(EGLImage,0)
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLSync (EGLAPIENTRYP PFNEGLCREATESYNCPROC) (EGLDisplay dpy, EGLenum type, ਅਚਲ EGLAttrib *attrib_list);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCPROC) (EGLDisplay dpy, EGLSync sync);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCPROC) (EGLDisplay dpy, EGLSync sync, EGLint flags, EGLTime timeout);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLGETSYNCATTRIBPROC) (EGLDisplay dpy, EGLSync sync, EGLint attribute, EGLAttrib *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLImage (EGLAPIENTRYP PFNEGLCREATEIMAGEPROC) (EGLDisplay dpy, EGLContext ctx, EGLenum ਨਿਸ਼ਾਨਾ, EGLClient_ਬਫਰ ਬਫਰ_2, ਅਚਲ EGLAttrib *attrib_list);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYIMAGEPROC) (EGLDisplay dpy, EGLImage image);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYPROC) (EGLenum platform, ਖਾਲੀ *native_display, ਅਚਲ EGLAttrib *attrib_list);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLSurface (EGLAPIENTRYP PFNEGLCREATEPLATFORMWINDOWSURFACEPROC) (EGLDisplay dpy, EGLConfig config, ਖਾਲੀ *native_ਖਿੜਕੀ, ਅਚਲ EGLAttrib *attrib_list);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLSurface (EGLAPIENTRYP PFNEGLCREATEPLATFORMPIXMAPSURFACEPROC) (EGLDisplay dpy, EGLConfig config, ਖਾਲੀ *native_pixmap, ਅਚਲ EGLAttrib *attrib_list);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLWAITSYNCPROC) (EGLDisplay dpy, EGLSync sync, EGLint flags);
#ਜੇ EGL_EGL_PROTOTYPES
EGLAPI EGLSync EGLAPIENTRY eglCreateSync (EGLDisplay dpy, EGLenum type, ਅਚਲ EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySync (EGLDisplay dpy, EGLSync sync);
EGLAPI EGLint EGLAPIENTRY eglClientWaitSync (EGLDisplay dpy, EGLSync sync, EGLint flags, EGLTime timeout);
EGLAPI EGLBoolean EGLAPIENTRY eglGetSyncAttrib (EGLDisplay dpy, EGLSync sync, EGLint attribute, EGLAttrib *ਮੁੱਲ);
EGLAPI EGLImage EGLAPIENTRY eglCreateImage (EGLDisplay dpy, EGLContext ctx, EGLenum ਨਿਸ਼ਾਨਾ, EGLClient_ਬਫਰ ਬਫਰ_2, ਅਚਲ EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyImage (EGLDisplay dpy, EGLImage image);
EGLAPI EGLDisplay EGLAPIENTRY eglGetPlatformDisplay (EGLenum platform, ਖਾਲੀ *native_display, ਅਚਲ EGLAttrib *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY egl_Create_Platform_ਖਿੜਕੀ_Surface (EGLDisplay dpy, EGLConfig config, ਖਾਲੀ *native_ਖਿੜਕੀ, ਅਚਲ EGLAttrib *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePlatformPixmapSurface (EGLDisplay dpy, EGLConfig config, ਖਾਲੀ *native_pixmap, ਅਚਲ EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglWaitSync (EGLDisplay dpy, EGLSync sync, EGLint flags);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_VERSION_1_5 */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ
