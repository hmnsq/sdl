#جے_بنا_تعریف __egl_h_
#تعریف_کرو __egl_h_ 1

#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت

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

#ضمن <EGL/eglplatform.h>

#جے_بنا_تعریف EGL_EGL_PROTOTYPES
#تعریف_کرو EGL_EGL_PROTOTYPES 1
#جے_انت

/* Generated on date 20260319 */

/* Generated C header for:
 * API: egl
 * Versions considered: .*
 * Versions emitted: .*
 * Default extensions included: None
 * Additional extensions included: _nomatch_^
 * Extensions removed: _nomatch_^
 */

#جے_بنا_تعریف EGL_نسخہ_1_0
#تعریف_کرو EGL_نسخہ_1_0 1
تعريفنوع بنانشانی صحيح EGLBoolean;
تعريفنوع فراغ *EGLDisplay;
#ضمن <KHR/khrplatform.h>
#ضمن <EGL/eglplatform.h>
تعريفنوع فراغ *EGLConfig;
تعريفنوع فراغ *EGLSurface;
تعريفنوع فراغ *EGLContext;
تعريفنوع فراغ (*__eglMustCastToProperFunctionPointerType)(فراغ);
#تعریف_کرو EGL_ALPHA_ناپ                    0x3021
#تعریف_کرو EGL_BAD_ACCESS                    0x3002
#تعریف_کرو EGL_BAD_ALLOC                     0x3003
#تعریف_کرو EGL_BAD_ATTRIBUTE                 0x3004
#تعریف_کرو EGL_BAD_CONFIG                    0x3005
#تعریف_کرو EGL_BAD_CONTEXT                   0x3006
#تعریف_کرو EGL_BAD_CURRENT_SURFACE           0x3007
#تعریف_کرو EGL_BAD_DISPLAY                   0x3008
#تعریف_کرو EGL_BAD_میل                     0x3009
#تعریف_کرو EGL_BAD_NATIVE_PIXMAP             0x300A
#تعریف_کرو EGL_BAD_NATIVE_کھڑکی             0x300B
#تعریف_کرو EGL_BAD_PARAMETER                 0x300C
#تعریف_کرو EGL_BAD_SURFACE                   0x300D
#تعریف_کرو EGL_BLUE_ناپ                     0x3022
#تعریف_کرو EGL_بفر_ناپ                   0x3020
#تعریف_کرو EGL_CONFIG_CAVEAT                 0x3027
#تعریف_کرو EGL_CONFIG_ID                     0x3028
#تعریف_کرو EGL_CORE_NATIVE_ENGINE            0x305B
#تعریف_کرو EGL_ڈونگھائی_ناپ                    0x3025
#تعریف_کرو EGL_DONT_CARE                     EGL_CAST(EGLint,-1)
#تعریف_کرو EGL_DRAW                          0x3059
#تعریف_کرو EGL_EXTENSIONS                    0x3055
#تعریف_کرو EGL_FALSE                         0
#تعریف_کرو EGL_GREEN_ناپ                    0x3023
#تعریف_کرو EGL_اچائی                        0x3056
#تعریف_کرو EGL_سبھ_توں_وڈا_PBUFFER               0x3058
#تعریف_کرو EGL_LEVEL                         0x3029
#تعریف_کرو EGL_MAX_PBUFFER_اچائی            0x302A
#تعریف_کرو EGL_MAX_PBUFFER_PIXELS            0x302B
#تعریف_کرو EGL_MAX_PBUFFER_چوڑائی             0x302C
#تعریف_کرو EGL_NATIVE_RENDERABLE             0x302D
#تعریف_کرو EGL_NATIVE_VISUAL_ID              0x302E
#تعریف_کرو EGL_NATIVE_VISUAL_TYPE            0x302F
#تعریف_کرو EGL_NONE                          0x3038
#تعریف_کرو EGL_NON_CONFORMANT_CONFIG         0x3051
#تعریف_کرو EGL_NOT_INITIALIZED               0x3001
#تعریف_کرو EGL_NO_CONTEXT                    EGL_CAST(EGLContext,0)
#تعریف_کرو EGL_NO_DISPLAY                    EGL_CAST(EGLDisplay,0)
#تعریف_کرو EGL_NO_SURFACE                    EGL_CAST(EGLSurface,0)
#تعریف_کرو EGL_PBUFFER_ثنائی_ہندسہ                   0x0001
#تعریف_کرو EGL_PIXMAP_ثنائی_ہندسہ                    0x0002
#تعریف_کرو EGL_READ                          0x305A
#تعریف_کرو EGL_RED_ناپ                      0x3024
#تعریف_کرو EGL_SAMPLES                       0x3031
#تعریف_کرو EGL_SAMPLE_BUFFERS                0x3032
#تعریف_کرو EGL_SLOW_CONFIG                   0x3050
#تعریف_کرو EGL_STENCIL_ناپ                  0x3026
#تعریف_کرو EGL_SUCCESS                       0x3000
#تعریف_کرو EGL_SURFACE_TYPE                  0x3033
#تعریف_کرو EGL_TRANSPARENT_BLUE_قدر        0x3035
#تعریف_کرو EGL_TRANSPARENT_GREEN_قدر       0x3036
#تعریف_کرو EGL_TRANSPARENT_RED_قدر         0x3037
#تعریف_کرو EGL_TRANSPARENT_RGB               0x3052
#تعریف_کرو EGL_TRANSPARENT_TYPE              0x3034
#تعریف_کرو EGL_TRUE                          1
#تعریف_کرو EGL_VENDOR                        0x3053
#تعریف_کرو EGL_نسخہ                       0x3054
#تعریف_کرو EGL_چوڑائی                         0x3057
#تعریف_کرو EGL_کھڑکی_ثنائی_ہندسہ                    0x0004
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLCHOOSECONFIGPROC) (EGLDisplay dpy, ثابت EGLint *attrib_list, EGLConfig *configs, EGLint config_ناپ, EGLint *عدد_config);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLCOPYBUFFERSPROC) (EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType نشانہ);
تعريفنوع EGLContext (EGLAPIENTRYP PFNEGLCREATECONTEXTPROC) (EGLDisplay dpy, EGLConfig config, EGLContext share_context, ثابت EGLint *attrib_list);
تعريفنوع EGLSurface (EGLAPIENTRYP PFNEGLCREATEPBUFFERSURFACEPROC) (EGLDisplay dpy, EGLConfig config, ثابت EGLint *attrib_list);
تعريفنوع EGLSurface (EGLAPIENTRYP PFNEGLCREATEPIXMAPSURFACEPROC) (EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, ثابت EGLint *attrib_list);
تعريفنوع EGLSurface (EGLAPIENTRYP PFNEGLCREATEWINDOWSURFACEPROC) (EGLDisplay dpy, EGLConfig config, EGLNative_کھڑکی_Type win, ثابت EGLint *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYCONTEXTPROC) (EGLDisplay dpy, EGLContext ctx);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSURFACEPROC) (EGLDisplay dpy, EGLSurface surface);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETCONFIGATTRIBPROC) (EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *قدر);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETCONFIGSPROC) (EGLDisplay dpy, EGLConfig *configs, EGLint config_ناپ, EGLint *عدد_config);
تعريفنوع EGLDisplay (EGLAPIENTRYP PFNEGLGETCURRENTDISPLAYPROC) (فراغ);
تعريفنوع EGLSurface (EGLAPIENTRYP PFNEGLGETCURRENTSURFACEPROC) (EGLint readdraw);
تعريفنوع EGLDisplay (EGLAPIENTRYP PFNEGLGETDISPLAYPROC) (EGLNativeDisplayType display_id);
تعريفنوع EGLint (EGLAPIENTRYP PFNEGLGETERRORPROC) (فراغ);
تعريفنوع __eglMustCastToProperFunctionPointerType (EGLAPIENTRYP PFNEGLGETPROCADDRESSPROC) (ثابت حرف *procname);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLINITIALIZEPROC) (EGLDisplay dpy, EGLint *major, EGLint *minor);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLMAKECURRENTPROC) (EGLDisplay dpy, EGLSurface draw, EGLSurface اقرأ, EGLContext ctx);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYCONTEXTPROC) (EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint *قدر);
تعريفنوع ثابت حرف *(EGLAPIENTRYP PFNEGLQUERYSTRINGPROC) (EGLDisplay dpy, EGLint name);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSURFACEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint *قدر);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSPROC) (EGLDisplay dpy, EGLSurface surface);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLTERMINATEPROC) (EGLDisplay dpy);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLWAITGLPROC) (فراغ);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLWAITNATIVEPROC) (EGLint engine);
#إذا EGL_EGL_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_چنو_Config (EGLDisplay dpy, ثابت EGLint *attrib_list, EGLConfig *configs, EGLint config_ناپ, EGLint *عدد_config);
EGLAPI EGLBoolean EGLAPIENTRY eglCopyBuffers (EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType نشانہ);
EGLAPI EGLContext EGLAPIENTRY eglCreateContext (EGLDisplay dpy, EGLConfig config, EGLContext share_context, ثابت EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePbufferSurface (EGLDisplay dpy, EGLConfig config, ثابت EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePixmapSurface (EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, ثابت EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY egl_Create_کھڑکی_Surface (EGLDisplay dpy, EGLConfig config, EGLNative_کھڑکی_Type win, ثابت EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyContext (EGLDisplay dpy, EGLContext ctx);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySurface (EGLDisplay dpy, EGLSurface surface);
EGLAPI EGLBoolean EGLAPIENTRY eglGetConfigAttrib (EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *قدر);
EGLAPI EGLBoolean EGLAPIENTRY eglGetConfigs (EGLDisplay dpy, EGLConfig *configs, EGLint config_ناپ, EGLint *عدد_config);
EGLAPI EGLDisplay EGLAPIENTRY eglGetCurrentDisplay (فراغ);
EGLAPI EGLSurface EGLAPIENTRY eglGetCurrentSurface (EGLint readdraw);
EGLAPI EGLDisplay EGLAPIENTRY eglGetDisplay (EGLNativeDisplayType display_id);
EGLAPI EGLint EGLAPIENTRY eglGetError (فراغ);
EGLAPI __eglMustCastToProperFunctionPointerType EGLAPIENTRY egl_Get_Proc_پتہ (ثابت حرف *procname);
EGLAPI EGLBoolean EGLAPIENTRY eglInitialize (EGLDisplay dpy, EGLint *major, EGLint *minor);
EGLAPI EGLBoolean EGLAPIENTRY eglMakeCurrent (EGLDisplay dpy, EGLSurface draw, EGLSurface اقرأ, EGLContext ctx);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryContext (EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint *قدر);
EGLAPI ثابت حرف *EGLAPIENTRY eglQueryString (EGLDisplay dpy, EGLint name);
EGLAPI EGLBoolean EGLAPIENTRY eglQuerySurface (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint *قدر);
EGLAPI EGLBoolean EGLAPIENTRY egl_وٹاندرا_Buffers (EGLDisplay dpy, EGLSurface surface);
EGLAPI EGLBoolean EGLAPIENTRY eglTerminate (EGLDisplay dpy);
EGLAPI EGLBoolean EGLAPIENTRY eglWaitGL (فراغ);
EGLAPI EGLBoolean EGLAPIENTRY eglWaitNative (EGLint engine);
#جے_انت
#جے_انت /* EGL_VERSION_1_0 */

#جے_بنا_تعریف EGL_نسخہ_1_1
#تعریف_کرو EGL_نسخہ_1_1 1
#تعریف_کرو EGL_پٹھ_بفر                   0x3084
#تعریف_کرو EGL_BIND_منزل_TEXTURE_RGB           0x3039
#تعریف_کرو EGL_BIND_منزل_TEXTURE_RGBA          0x303A
#تعریف_کرو EGL_CONTEXT_گواچا                  0x300E
#تعریف_کرو EGL_MIN_وٹاندرا_INTERVAL             0x303B
#تعریف_کرو EGL_MAX_وٹاندرا_INTERVAL             0x303C
#تعریف_کرو EGL_MIPMAP_TEXTURE                0x3082
#تعریف_کرو EGL_MIPMAP_LEVEL                  0x3083
#تعریف_کرو EGL_NO_TEXTURE                    0x305C
#تعریف_کرو EGL_TEXTURE_2D                    0x305F
#تعریف_کرو EGL_TEXTURE_FORMAT                0x3080
#تعریف_کرو EGL_TEXTURE_RGB                   0x305D
#تعریف_کرو EGL_TEXTURE_RGBA                  0x305E
#تعریف_کرو EGL_TEXTURE_نشانہ                0x3081
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLBINDTEXIMAGEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint بفر_2);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLRELEASETEXIMAGEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint بفر_2);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSURFACEATTRIBPROC) (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint قدر);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSWAPINTERVALPROC) (EGLDisplay dpy, EGLint interval);
#إذا EGL_EGL_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglBindTexImage (EGLDisplay dpy, EGLSurface surface, EGLint بفر_2);
EGLAPI EGLBoolean EGLAPIENTRY eglReleaseTexImage (EGLDisplay dpy, EGLSurface surface, EGLint بفر_2);
EGLAPI EGLBoolean EGLAPIENTRY eglSurfaceAttrib (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint قدر);
EGLAPI EGLBoolean EGLAPIENTRY egl_وٹاندرا_Interval (EGLDisplay dpy, EGLint interval);
#جے_انت
#جے_انت /* EGL_VERSION_1_1 */

#جے_بنا_تعریف EGL_نسخہ_1_2
#تعریف_کرو EGL_نسخہ_1_2 1
تعريفنوع بنانشانی صحيح EGLenum;
تعريفنوع فراغ *EGLClient_بفر;
#تعریف_کرو EGL_ALPHA_FORMAT                  0x3088
#تعریف_کرو EGL_ALPHA_FORMAT_NONPRE           0x308B
#تعریف_کرو EGL_ALPHA_FORMAT_PRE              0x308C
#تعریف_کرو EGL_ALPHA_نقاب_ناپ               0x303E
#تعریف_کرو EGL_بفر_PRESERVED              0x3094
#تعریف_کرو EGL_بفر_DESTROYED              0x3095
#تعریف_کرو EGL_CLIENT_APIS                   0x308D
#تعریف_کرو EGL_COLORSPACE                    0x3087
#تعریف_کرو EGL_COLORSPACE_sRGB               0x3089
#تعریف_کرو EGL_COLORSPACE_خطی             0x308A
#تعریف_کرو EGL_COLOR_بفر_TYPE             0x303F
#تعریف_کرو EGL_CONTEXT_CLIENT_TYPE           0x3097
#تعریف_کرو EGL_DISPLAY_SCALING               10000
#تعریف_کرو EGL_HORIZONTAL_RESOLUTION         0x3090
#تعریف_کرو EGL_LUMINANCE_بفر              0x308F
#تعریف_کرو EGL_LUMINANCE_ناپ                0x303D
#تعریف_کرو EGL_OPENGL_ES_ثنائی_ہندسہ                 0x0001
#تعریف_کرو EGL_OPENVG_ثنائی_ہندسہ                    0x0002
#تعریف_کرو EGL_OPENGL_ES_API                 0x30A0
#تعریف_کرو EGL_OPENVG_API                    0x30A1
#تعریف_کرو EGL_OPENVG_IMAGE                  0x3096
#تعریف_کرو EGL_PIXEL_ASPECT_تناسب            0x3092
#تعریف_کرو EGL_RENDERABLE_TYPE               0x3040
#تعریف_کرو EGL_RENDER_بفر                 0x3086
#تعریف_کرو EGL_RGB_بفر                    0x308E
#تعریف_کرو EGL_SINGLE_بفر                 0x3085
#تعریف_کرو EGL_وٹاندرا_BEHAVIOR                 0x3093
#تعریف_کرو EGL_UNKNOWN                       EGL_CAST(EGLint,-1)
#تعریف_کرو EGL_VERTICAL_RESOLUTION           0x3091
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLBINDAPIPROC) (EGLenum api);
تعريفنوع EGLenum (EGLAPIENTRYP PFNEGLQUERYAPIPROC) (فراغ);
تعريفنوع EGLSurface (EGLAPIENTRYP PFNEGLCREATEPBUFFERFROMCLIENTBUFFERPROC) (EGLDisplay dpy, EGLenum buftype, EGLClient_بفر بفر_2, EGLConfig config, ثابت EGLint *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLRELEASETHREADPROC) (فراغ);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLWAITCLIENTPROC) (فراغ);
#إذا EGL_EGL_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglBindAPI (EGLenum api);
EGLAPI EGLenum EGLAPIENTRY eglQueryAPI (فراغ);
EGLAPI EGLSurface EGLAPIENTRY egl_Create_Pbuffer_From_Client_بفر (EGLDisplay dpy, EGLenum buftype, EGLClient_بفر بفر_2, EGLConfig config, ثابت EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglReleaseThread (فراغ);
EGLAPI EGLBoolean EGLAPIENTRY eglWaitClient (فراغ);
#جے_انت
#جے_انت /* EGL_VERSION_1_2 */

#جے_بنا_تعریف EGL_نسخہ_1_3
#تعریف_کرو EGL_نسخہ_1_3 1
#تعریف_کرو EGL_CONFORMANT                    0x3042
#تعریف_کرو EGL_CONTEXT_CLIENT_نسخہ        0x3098
#تعریف_کرو EGL_میل_NATIVE_PIXMAP           0x3041
#تعریف_کرو EGL_OPENGL_ES2_ثنائی_ہندسہ                0x0004
#تعریف_کرو EGL_VG_ALPHA_FORMAT               0x3088
#تعریف_کرو EGL_VG_ALPHA_FORMAT_NONPRE        0x308B
#تعریف_کرو EGL_VG_ALPHA_FORMAT_PRE           0x308C
#تعریف_کرو EGL_VG_ALPHA_FORMAT_PRE_ثنائی_ہندسہ       0x0040
#تعریف_کرو EGL_VG_COLORSPACE                 0x3087
#تعریف_کرو EGL_VG_COLORSPACE_sRGB            0x3089
#تعریف_کرو EGL_VG_COLORSPACE_خطی          0x308A
#تعریف_کرو EGL_VG_COLORSPACE_خطی_ثنائی_ہندسہ      0x0020
#جے_انت /* EGL_VERSION_1_3 */

#جے_بنا_تعریف EGL_نسخہ_1_4
#تعریف_کرو EGL_نسخہ_1_4 1
#تعریف_کرو EGL_DEFAULT_DISPLAY               EGL_CAST(EGLNativeDisplayType,0)
#تعریف_کرو EGL_MULTISAMPLE_RESOLVE_BOX_ثنائی_ہندسہ   0x0200
#تعریف_کرو EGL_MULTISAMPLE_RESOLVE           0x3099
#تعریف_کرو EGL_MULTISAMPLE_RESOLVE_DEFAULT   0x309A
#تعریف_کرو EGL_MULTISAMPLE_RESOLVE_BOX       0x309B
#تعریف_کرو EGL_OPENGL_API                    0x30A2
#تعریف_کرو EGL_OPENGL_ثنائی_ہندسہ                    0x0008
#تعریف_کرو EGL_وٹاندرا_BEHAVIOR_PRESERVED_ثنائی_ہندسہ   0x0400
تعريفنوع EGLContext (EGLAPIENTRYP PFNEGLGETCURRENTCONTEXTPROC) (فراغ);
#إذا EGL_EGL_PROTOTYPES
EGLAPI EGLContext EGLAPIENTRY eglGetCurrentContext (فراغ);
#جے_انت
#جے_انت /* EGL_VERSION_1_4 */

#جے_بنا_تعریف EGL_نسخہ_1_5
#تعریف_کرو EGL_نسخہ_1_5 1
تعريفنوع فراغ *EGLSync;
تعريفنوع intptr_t EGLAttrib;
تعريفنوع khronos_utime_nanoseconds_t EGLTime;
تعريفنوع فراغ *EGLImage;
#تعریف_کرو EGL_CONTEXT_MAJOR_نسخہ         0x3098
#تعریف_کرو EGL_CONTEXT_MINOR_نسخہ         0x30FB
#تعریف_کرو EGL_CONTEXT_OPENGL_PROFILE_نقاب   0x30FD
#تعریف_کرو EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY 0x31BD
#تعریف_کرو EGL_NO_RESET_NOTIFICATION         0x31BE
#تعریف_کرو EGL_LOSE_CONTEXT_ON_RESET         0x31BF
#تعریف_کرو EGL_CONTEXT_OPENGL_CORE_PROFILE_ثنائی_ہندسہ 0x00000001
#تعریف_کرو EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_ثنائی_ہندسہ 0x00000002
#تعریف_کرو EGL_CONTEXT_OPENGL_DEBUG          0x31B0
#تعریف_کرو EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE 0x31B1
#تعریف_کرو EGL_CONTEXT_OPENGL_ROBUST_ACCESS  0x31B2
#تعریف_کرو EGL_OPENGL_ES3_ثنائی_ہندسہ                0x00000040
#تعریف_کرو EGL_CL_EVENT_HANDLE               0x309C
#تعریف_کرو EGL_SYNC_CL_EVENT                 0x30FE
#تعریف_کرو EGL_SYNC_CL_EVENT_COMPLETE        0x30FF
#تعریف_کرو EGL_SYNC_پہلوں_COMMANDS_COMPLETE  0x30F0
#تعریف_کرو EGL_SYNC_TYPE                     0x30F7
#تعریف_کرو EGL_SYNC_حالت                   0x30F1
#تعریف_کرو EGL_SYNC_CONDITION                0x30F8
#تعریف_کرو EGL_SIGNALED                      0x30F2
#تعریف_کرو EGL_UNSIGNALED                    0x30F3
#تعریف_کرو EGL_SYNC_FLUSH_COMMANDS_ثنائی_ہندسہ       0x0001
#تعریف_کرو EGL_FOREVER                       0xFFFFFFFFFFFFFFFFull
#تعریف_کرو EGL_TIMEOUT_EXPIRED               0x30F5
#تعریف_کرو EGL_CONDITION_SATISFIED           0x30F6
#تعریف_کرو EGL_NO_SYNC                       EGL_CAST(EGLSync,0)
#تعریف_کرو EGL_SYNC_FENCE                    0x30F9
#تعریف_کرو EGL_GL_COLORSPACE                 0x309D
#تعریف_کرو EGL_GL_COLORSPACE_SRGB            0x3089
#تعریف_کرو EGL_GL_COLORSPACE_خطی          0x308A
#تعریف_کرو EGL_GL_RENDERBUFFER               0x30B9
#تعریف_کرو EGL_GL_TEXTURE_2D                 0x30B1
#تعریف_کرو EGL_GL_TEXTURE_LEVEL              0x30BC
#تعریف_کرو EGL_GL_TEXTURE_3D                 0x30B2
#تعریف_کرو EGL_GL_TEXTURE_ZOFFSET            0x30BD
#تعریف_کرو EGL_GL_TEXTURE_CUBE_MAP_مثبت_X 0x30B3
#تعریف_کرو EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_X 0x30B4
#تعریف_کرو EGL_GL_TEXTURE_CUBE_MAP_مثبت_Y 0x30B5
#تعریف_کرو EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Y 0x30B6
#تعریف_کرو EGL_GL_TEXTURE_CUBE_MAP_مثبت_Z 0x30B7
#تعریف_کرو EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 0x30B8
#تعریف_کرو EGL_IMAGE_PRESERVED               0x30D2
#تعریف_کرو EGL_NO_IMAGE                      EGL_CAST(EGLImage,0)
تعريفنوع EGLSync (EGLAPIENTRYP PFNEGLCREATESYNCPROC) (EGLDisplay dpy, EGLenum type, ثابت EGLAttrib *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCPROC) (EGLDisplay dpy, EGLSync sync);
تعريفنوع EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCPROC) (EGLDisplay dpy, EGLSync sync, EGLint flags, EGLTime timeout);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETSYNCATTRIBPROC) (EGLDisplay dpy, EGLSync sync, EGLint attribute, EGLAttrib *قدر);
تعريفنوع EGLImage (EGLAPIENTRYP PFNEGLCREATEIMAGEPROC) (EGLDisplay dpy, EGLContext ctx, EGLenum نشانہ, EGLClient_بفر بفر_2, ثابت EGLAttrib *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYIMAGEPROC) (EGLDisplay dpy, EGLImage image);
تعريفنوع EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYPROC) (EGLenum platform, فراغ *native_display, ثابت EGLAttrib *attrib_list);
تعريفنوع EGLSurface (EGLAPIENTRYP PFNEGLCREATEPLATFORMWINDOWSURFACEPROC) (EGLDisplay dpy, EGLConfig config, فراغ *native_کھڑکی, ثابت EGLAttrib *attrib_list);
تعريفنوع EGLSurface (EGLAPIENTRYP PFNEGLCREATEPLATFORMPIXMAPSURFACEPROC) (EGLDisplay dpy, EGLConfig config, فراغ *native_pixmap, ثابت EGLAttrib *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLWAITSYNCPROC) (EGLDisplay dpy, EGLSync sync, EGLint flags);
#إذا EGL_EGL_PROTOTYPES
EGLAPI EGLSync EGLAPIENTRY eglCreateSync (EGLDisplay dpy, EGLenum type, ثابت EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySync (EGLDisplay dpy, EGLSync sync);
EGLAPI EGLint EGLAPIENTRY eglClientWaitSync (EGLDisplay dpy, EGLSync sync, EGLint flags, EGLTime timeout);
EGLAPI EGLBoolean EGLAPIENTRY eglGetSyncAttrib (EGLDisplay dpy, EGLSync sync, EGLint attribute, EGLAttrib *قدر);
EGLAPI EGLImage EGLAPIENTRY eglCreateImage (EGLDisplay dpy, EGLContext ctx, EGLenum نشانہ, EGLClient_بفر بفر_2, ثابت EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyImage (EGLDisplay dpy, EGLImage image);
EGLAPI EGLDisplay EGLAPIENTRY eglGetPlatformDisplay (EGLenum platform, فراغ *native_display, ثابت EGLAttrib *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY egl_Create_Platform_کھڑکی_Surface (EGLDisplay dpy, EGLConfig config, فراغ *native_کھڑکی, ثابت EGLAttrib *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePlatformPixmapSurface (EGLDisplay dpy, EGLConfig config, فراغ *native_pixmap, ثابت EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglWaitSync (EGLDisplay dpy, EGLSync sync, EGLint flags);
#جے_انت
#جے_انت /* EGL_VERSION_1_5 */

#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت
