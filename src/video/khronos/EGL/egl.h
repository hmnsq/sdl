#جيڪڏهن_وصف_نه_ٿيل __egl_h_
#وصف_ڪريو __egl_h_ 1

#جيڪڏهن_وصف_ٿيل __cplusplus
خارجي "C" {
#جيڪڏهن_پورو

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

#جيڪڏهن_وصف_نه_ٿيل EGL_EGL_PROTOTYPES
#وصف_ڪريو EGL_EGL_PROTOTYPES 1
#جيڪڏهن_پورو

/* Generated on date 20260319 */

/* Generated C header for:
 * API: egl
 * Versions considered: .*
 * Versions emitted: .*
 * Default extensions included: None
 * Additional extensions included: _nomatch_^
 * Extensions removed: _nomatch_^
 */

#جيڪڏهن_وصف_نه_ٿيل EGL_نسخو_1_0
#وصف_ڪريو EGL_نسخو_1_0 1
تعريفنوع بنانشان صحيح EGLBoolean;
تعريفنوع فراغ *EGLDisplay;
#ضمن <KHR/khrplatform.h>
#ضمن <EGL/eglplatform.h>
تعريفنوع فراغ *EGLConfig;
تعريفنوع فراغ *EGLSurface;
تعريفنوع فراغ *EGLContext;
تعريفنوع فراغ (*__eglMustCastToProperFunctionPointerType)(فراغ);
#وصف_ڪريو EGL_ALPHA_سائيز                    0x3021
#وصف_ڪريو EGL_BAD_ACCESS                    0x3002
#وصف_ڪريو EGL_BAD_ALLOC                     0x3003
#وصف_ڪريو EGL_BAD_ATTRIBUTE                 0x3004
#وصف_ڪريو EGL_BAD_CONFIG                    0x3005
#وصف_ڪريو EGL_BAD_CONTEXT                   0x3006
#وصف_ڪريو EGL_BAD_CURRENT_SURFACE           0x3007
#وصف_ڪريو EGL_BAD_DISPLAY                   0x3008
#وصف_ڪريو EGL_BAD_ميلاپ                     0x3009
#وصف_ڪريو EGL_BAD_NATIVE_PIXMAP             0x300A
#وصف_ڪريو EGL_BAD_NATIVE_دري             0x300B
#وصف_ڪريو EGL_BAD_PARAMETER                 0x300C
#وصف_ڪريو EGL_BAD_SURFACE                   0x300D
#وصف_ڪريو EGL_BLUE_سائيز                     0x3022
#وصف_ڪريو EGL_بفر_سائيز                   0x3020
#وصف_ڪريو EGL_CONFIG_CAVEAT                 0x3027
#وصف_ڪريو EGL_CONFIG_ID                     0x3028
#وصف_ڪريو EGL_CORE_NATIVE_ENGINE            0x305B
#وصف_ڪريو EGL_اونهائي_سائيز                    0x3025
#وصف_ڪريو EGL_DONT_CARE                     EGL_CAST(EGLint,-1)
#وصف_ڪريو EGL_DRAW                          0x3059
#وصف_ڪريو EGL_EXTENSIONS                    0x3055
#وصف_ڪريو EGL_FALSE                         0
#وصف_ڪريو EGL_GREEN_سائيز                    0x3023
#وصف_ڪريو EGL_اوچائي                        0x3056
#وصف_ڪريو EGL_سڀ_کان_وڏو_PBUFFER               0x3058
#وصف_ڪريو EGL_LEVEL                         0x3029
#وصف_ڪريو EGL_MAX_PBUFFER_اوچائي            0x302A
#وصف_ڪريو EGL_MAX_PBUFFER_PIXELS            0x302B
#وصف_ڪريو EGL_MAX_PBUFFER_ويڪر             0x302C
#وصف_ڪريو EGL_NATIVE_RENDERABLE             0x302D
#وصف_ڪريو EGL_NATIVE_VISUAL_ID              0x302E
#وصف_ڪريو EGL_NATIVE_VISUAL_TYPE            0x302F
#وصف_ڪريو EGL_NONE                          0x3038
#وصف_ڪريو EGL_NON_CONFORMANT_CONFIG         0x3051
#وصف_ڪريو EGL_NOT_INITIALIZED               0x3001
#وصف_ڪريو EGL_NO_CONTEXT                    EGL_CAST(EGLContext,0)
#وصف_ڪريو EGL_NO_DISPLAY                    EGL_CAST(EGLDisplay,0)
#وصف_ڪريو EGL_NO_SURFACE                    EGL_CAST(EGLSurface,0)
#وصف_ڪريو EGL_PBUFFER_ٻٽو_انگ                   0x0001
#وصف_ڪريو EGL_PIXMAP_ٻٽو_انگ                    0x0002
#وصف_ڪريو EGL_READ                          0x305A
#وصف_ڪريو EGL_RED_سائيز                      0x3024
#وصف_ڪريو EGL_SAMPLES                       0x3031
#وصف_ڪريو EGL_SAMPLE_BUFFERS                0x3032
#وصف_ڪريو EGL_SLOW_CONFIG                   0x3050
#وصف_ڪريو EGL_STENCIL_سائيز                  0x3026
#وصف_ڪريو EGL_SUCCESS                       0x3000
#وصف_ڪريو EGL_SURFACE_TYPE                  0x3033
#وصف_ڪريو EGL_TRANSPARENT_BLUE_قدر        0x3035
#وصف_ڪريو EGL_TRANSPARENT_GREEN_قدر       0x3036
#وصف_ڪريو EGL_TRANSPARENT_RED_قدر         0x3037
#وصف_ڪريو EGL_TRANSPARENT_RGB               0x3052
#وصف_ڪريو EGL_TRANSPARENT_TYPE              0x3034
#وصف_ڪريو EGL_TRUE                          1
#وصف_ڪريو EGL_VENDOR                        0x3053
#وصف_ڪريو EGL_نسخو                       0x3054
#وصف_ڪريو EGL_ويڪر                         0x3057
#وصف_ڪريو EGL_دري_ٻٽو_انگ                    0x0004
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLCHOOSECONFIGPROC) (EGLDisplay dpy, ثابت EGLint *attrib_list, EGLConfig *configs, EGLint config_سائيز, EGLint *انگ_config);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLCOPYBUFFERSPROC) (EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType هدف);
تعريفنوع EGLContext (EGLAPIENTRYP PFNEGLCREATECONTEXTPROC) (EGLDisplay dpy, EGLConfig config, EGLContext share_context, ثابت EGLint *attrib_list);
تعريفنوع EGLSurface (EGLAPIENTRYP PFNEGLCREATEPBUFFERSURFACEPROC) (EGLDisplay dpy, EGLConfig config, ثابت EGLint *attrib_list);
تعريفنوع EGLSurface (EGLAPIENTRYP PFNEGLCREATEPIXMAPSURFACEPROC) (EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, ثابت EGLint *attrib_list);
تعريفنوع EGLSurface (EGLAPIENTRYP PFNEGLCREATEWINDOWSURFACEPROC) (EGLDisplay dpy, EGLConfig config, EGLNative_دري_Type win, ثابت EGLint *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYCONTEXTPROC) (EGLDisplay dpy, EGLContext ctx);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSURFACEPROC) (EGLDisplay dpy, EGLSurface surface);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETCONFIGATTRIBPROC) (EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *قدر);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETCONFIGSPROC) (EGLDisplay dpy, EGLConfig *configs, EGLint config_سائيز, EGLint *انگ_config);
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
EGLAPI EGLBoolean EGLAPIENTRY egl_چونڊيو_Config (EGLDisplay dpy, ثابت EGLint *attrib_list, EGLConfig *configs, EGLint config_سائيز, EGLint *انگ_config);
EGLAPI EGLBoolean EGLAPIENTRY eglCopyBuffers (EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType هدف);
EGLAPI EGLContext EGLAPIENTRY eglCreateContext (EGLDisplay dpy, EGLConfig config, EGLContext share_context, ثابت EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePbufferSurface (EGLDisplay dpy, EGLConfig config, ثابت EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePixmapSurface (EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, ثابت EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY egl_Create_دري_Surface (EGLDisplay dpy, EGLConfig config, EGLNative_دري_Type win, ثابت EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyContext (EGLDisplay dpy, EGLContext ctx);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySurface (EGLDisplay dpy, EGLSurface surface);
EGLAPI EGLBoolean EGLAPIENTRY eglGetConfigAttrib (EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *قدر);
EGLAPI EGLBoolean EGLAPIENTRY eglGetConfigs (EGLDisplay dpy, EGLConfig *configs, EGLint config_سائيز, EGLint *انگ_config);
EGLAPI EGLDisplay EGLAPIENTRY eglGetCurrentDisplay (فراغ);
EGLAPI EGLSurface EGLAPIENTRY eglGetCurrentSurface (EGLint readdraw);
EGLAPI EGLDisplay EGLAPIENTRY eglGetDisplay (EGLNativeDisplayType display_id);
EGLAPI EGLint EGLAPIENTRY eglGetError (فراغ);
EGLAPI __eglMustCastToProperFunctionPointerType EGLAPIENTRY egl_Get_Proc_پتو (ثابت حرف *procname);
EGLAPI EGLBoolean EGLAPIENTRY eglInitialize (EGLDisplay dpy, EGLint *major, EGLint *minor);
EGLAPI EGLBoolean EGLAPIENTRY eglMakeCurrent (EGLDisplay dpy, EGLSurface draw, EGLSurface اقرأ, EGLContext ctx);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryContext (EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint *قدر);
EGLAPI ثابت حرف *EGLAPIENTRY eglQueryString (EGLDisplay dpy, EGLint name);
EGLAPI EGLBoolean EGLAPIENTRY eglQuerySurface (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint *قدر);
EGLAPI EGLBoolean EGLAPIENTRY egl_مٽا_سٽا_Buffers (EGLDisplay dpy, EGLSurface surface);
EGLAPI EGLBoolean EGLAPIENTRY eglTerminate (EGLDisplay dpy);
EGLAPI EGLBoolean EGLAPIENTRY eglWaitGL (فراغ);
EGLAPI EGLBoolean EGLAPIENTRY eglWaitNative (EGLint engine);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_VERSION_1_0 */

#جيڪڏهن_وصف_نه_ٿيل EGL_نسخو_1_1
#وصف_ڪريو EGL_نسخو_1_1 1
#وصف_ڪريو EGL_پٺ_بفر                   0x3084
#وصف_ڪريو EGL_BIND_منزل_TEXTURE_RGB           0x3039
#وصف_ڪريو EGL_BIND_منزل_TEXTURE_RGBA          0x303A
#وصف_ڪريو EGL_CONTEXT_گم                  0x300E
#وصف_ڪريو EGL_MIN_مٽا_سٽا_INTERVAL             0x303B
#وصف_ڪريو EGL_MAX_مٽا_سٽا_INTERVAL             0x303C
#وصف_ڪريو EGL_MIPMAP_TEXTURE                0x3082
#وصف_ڪريو EGL_MIPMAP_LEVEL                  0x3083
#وصف_ڪريو EGL_NO_TEXTURE                    0x305C
#وصف_ڪريو EGL_TEXTURE_2D                    0x305F
#وصف_ڪريو EGL_TEXTURE_FORMAT                0x3080
#وصف_ڪريو EGL_TEXTURE_RGB                   0x305D
#وصف_ڪريو EGL_TEXTURE_RGBA                  0x305E
#وصف_ڪريو EGL_TEXTURE_هدف                0x3081
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLBINDTEXIMAGEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint بفر_2);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLRELEASETEXIMAGEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint بفر_2);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSURFACEATTRIBPROC) (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint قدر);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSWAPINTERVALPROC) (EGLDisplay dpy, EGLint interval);
#إذا EGL_EGL_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglBindTexImage (EGLDisplay dpy, EGLSurface surface, EGLint بفر_2);
EGLAPI EGLBoolean EGLAPIENTRY eglReleaseTexImage (EGLDisplay dpy, EGLSurface surface, EGLint بفر_2);
EGLAPI EGLBoolean EGLAPIENTRY eglSurfaceAttrib (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint قدر);
EGLAPI EGLBoolean EGLAPIENTRY egl_مٽا_سٽا_Interval (EGLDisplay dpy, EGLint interval);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_VERSION_1_1 */

#جيڪڏهن_وصف_نه_ٿيل EGL_نسخو_1_2
#وصف_ڪريو EGL_نسخو_1_2 1
تعريفنوع بنانشان صحيح EGLenum;
تعريفنوع فراغ *EGLClient_بفر;
#وصف_ڪريو EGL_ALPHA_FORMAT                  0x3088
#وصف_ڪريو EGL_ALPHA_FORMAT_NONPRE           0x308B
#وصف_ڪريو EGL_ALPHA_FORMAT_PRE              0x308C
#وصف_ڪريو EGL_ALPHA_نقاب_سائيز               0x303E
#وصف_ڪريو EGL_بفر_PRESERVED              0x3094
#وصف_ڪريو EGL_بفر_DESTROYED              0x3095
#وصف_ڪريو EGL_CLIENT_APIS                   0x308D
#وصف_ڪريو EGL_COLORSPACE                    0x3087
#وصف_ڪريو EGL_COLORSPACE_sRGB               0x3089
#وصف_ڪريو EGL_COLORSPACE_لڪيري             0x308A
#وصف_ڪريو EGL_COLOR_بفر_TYPE             0x303F
#وصف_ڪريو EGL_CONTEXT_CLIENT_TYPE           0x3097
#وصف_ڪريو EGL_DISPLAY_SCALING               10000
#وصف_ڪريو EGL_HORIZONTAL_RESOLUTION         0x3090
#وصف_ڪريو EGL_LUMINANCE_بفر              0x308F
#وصف_ڪريو EGL_LUMINANCE_سائيز                0x303D
#وصف_ڪريو EGL_OPENGL_ES_ٻٽو_انگ                 0x0001
#وصف_ڪريو EGL_OPENVG_ٻٽو_انگ                    0x0002
#وصف_ڪريو EGL_OPENGL_ES_API                 0x30A0
#وصف_ڪريو EGL_OPENVG_API                    0x30A1
#وصف_ڪريو EGL_OPENVG_IMAGE                  0x3096
#وصف_ڪريو EGL_PIXEL_ASPECT_تناسب            0x3092
#وصف_ڪريو EGL_RENDERABLE_TYPE               0x3040
#وصف_ڪريو EGL_RENDER_بفر                 0x3086
#وصف_ڪريو EGL_RGB_بفر                    0x308E
#وصف_ڪريو EGL_SINGLE_بفر                 0x3085
#وصف_ڪريو EGL_مٽا_سٽا_BEHAVIOR                 0x3093
#وصف_ڪريو EGL_UNKNOWN                       EGL_CAST(EGLint,-1)
#وصف_ڪريو EGL_VERTICAL_RESOLUTION           0x3091
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
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_VERSION_1_2 */

#جيڪڏهن_وصف_نه_ٿيل EGL_نسخو_1_3
#وصف_ڪريو EGL_نسخو_1_3 1
#وصف_ڪريو EGL_CONFORMANT                    0x3042
#وصف_ڪريو EGL_CONTEXT_CLIENT_نسخو        0x3098
#وصف_ڪريو EGL_ميلاپ_NATIVE_PIXMAP           0x3041
#وصف_ڪريو EGL_OPENGL_ES2_ٻٽو_انگ                0x0004
#وصف_ڪريو EGL_VG_ALPHA_FORMAT               0x3088
#وصف_ڪريو EGL_VG_ALPHA_FORMAT_NONPRE        0x308B
#وصف_ڪريو EGL_VG_ALPHA_FORMAT_PRE           0x308C
#وصف_ڪريو EGL_VG_ALPHA_FORMAT_PRE_ٻٽو_انگ       0x0040
#وصف_ڪريو EGL_VG_COLORSPACE                 0x3087
#وصف_ڪريو EGL_VG_COLORSPACE_sRGB            0x3089
#وصف_ڪريو EGL_VG_COLORSPACE_لڪيري          0x308A
#وصف_ڪريو EGL_VG_COLORSPACE_لڪيري_ٻٽو_انگ      0x0020
#جيڪڏهن_پورو /* EGL_VERSION_1_3 */

#جيڪڏهن_وصف_نه_ٿيل EGL_نسخو_1_4
#وصف_ڪريو EGL_نسخو_1_4 1
#وصف_ڪريو EGL_DEFAULT_DISPLAY               EGL_CAST(EGLNativeDisplayType,0)
#وصف_ڪريو EGL_MULTISAMPLE_RESOLVE_BOX_ٻٽو_انگ   0x0200
#وصف_ڪريو EGL_MULTISAMPLE_RESOLVE           0x3099
#وصف_ڪريو EGL_MULTISAMPLE_RESOLVE_DEFAULT   0x309A
#وصف_ڪريو EGL_MULTISAMPLE_RESOLVE_BOX       0x309B
#وصف_ڪريو EGL_OPENGL_API                    0x30A2
#وصف_ڪريو EGL_OPENGL_ٻٽو_انگ                    0x0008
#وصف_ڪريو EGL_مٽا_سٽا_BEHAVIOR_PRESERVED_ٻٽو_انگ   0x0400
تعريفنوع EGLContext (EGLAPIENTRYP PFNEGLGETCURRENTCONTEXTPROC) (فراغ);
#إذا EGL_EGL_PROTOTYPES
EGLAPI EGLContext EGLAPIENTRY eglGetCurrentContext (فراغ);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_VERSION_1_4 */

#جيڪڏهن_وصف_نه_ٿيل EGL_نسخو_1_5
#وصف_ڪريو EGL_نسخو_1_5 1
تعريفنوع فراغ *EGLSync;
تعريفنوع intptr_t EGLAttrib;
تعريفنوع khronos_utime_nanoseconds_t EGLTime;
تعريفنوع فراغ *EGLImage;
#وصف_ڪريو EGL_CONTEXT_MAJOR_نسخو         0x3098
#وصف_ڪريو EGL_CONTEXT_MINOR_نسخو         0x30FB
#وصف_ڪريو EGL_CONTEXT_OPENGL_PROFILE_نقاب   0x30FD
#وصف_ڪريو EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY 0x31BD
#وصف_ڪريو EGL_NO_RESET_NOTIFICATION         0x31BE
#وصف_ڪريو EGL_LOSE_CONTEXT_ON_RESET         0x31BF
#وصف_ڪريو EGL_CONTEXT_OPENGL_CORE_PROFILE_ٻٽو_انگ 0x00000001
#وصف_ڪريو EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_ٻٽو_انگ 0x00000002
#وصف_ڪريو EGL_CONTEXT_OPENGL_DEBUG          0x31B0
#وصف_ڪريو EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE 0x31B1
#وصف_ڪريو EGL_CONTEXT_OPENGL_ROBUST_ACCESS  0x31B2
#وصف_ڪريو EGL_OPENGL_ES3_ٻٽو_انگ                0x00000040
#وصف_ڪريو EGL_CL_EVENT_HANDLE               0x309C
#وصف_ڪريو EGL_SYNC_CL_EVENT                 0x30FE
#وصف_ڪريو EGL_SYNC_CL_EVENT_COMPLETE        0x30FF
#وصف_ڪريو EGL_SYNC_اڳواٽ_COMMANDS_COMPLETE  0x30F0
#وصف_ڪريو EGL_SYNC_TYPE                     0x30F7
#وصف_ڪريو EGL_SYNC_حالت                   0x30F1
#وصف_ڪريو EGL_SYNC_CONDITION                0x30F8
#وصف_ڪريو EGL_SIGNALED                      0x30F2
#وصف_ڪريو EGL_UNSIGNALED                    0x30F3
#وصف_ڪريو EGL_SYNC_FLUSH_COMMANDS_ٻٽو_انگ       0x0001
#وصف_ڪريو EGL_FOREVER                       0xFFFFFFFFFFFFFFFFull
#وصف_ڪريو EGL_TIMEOUT_EXPIRED               0x30F5
#وصف_ڪريو EGL_CONDITION_SATISFIED           0x30F6
#وصف_ڪريو EGL_NO_SYNC                       EGL_CAST(EGLSync,0)
#وصف_ڪريو EGL_SYNC_FENCE                    0x30F9
#وصف_ڪريو EGL_GL_COLORSPACE                 0x309D
#وصف_ڪريو EGL_GL_COLORSPACE_SRGB            0x3089
#وصف_ڪريو EGL_GL_COLORSPACE_لڪيري          0x308A
#وصف_ڪريو EGL_GL_RENDERBUFFER               0x30B9
#وصف_ڪريو EGL_GL_TEXTURE_2D                 0x30B1
#وصف_ڪريو EGL_GL_TEXTURE_LEVEL              0x30BC
#وصف_ڪريو EGL_GL_TEXTURE_3D                 0x30B2
#وصف_ڪريو EGL_GL_TEXTURE_ZOFFSET            0x30BD
#وصف_ڪريو EGL_GL_TEXTURE_CUBE_MAP_مثبت_X 0x30B3
#وصف_ڪريو EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_X 0x30B4
#وصف_ڪريو EGL_GL_TEXTURE_CUBE_MAP_مثبت_Y 0x30B5
#وصف_ڪريو EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Y 0x30B6
#وصف_ڪريو EGL_GL_TEXTURE_CUBE_MAP_مثبت_Z 0x30B7
#وصف_ڪريو EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 0x30B8
#وصف_ڪريو EGL_IMAGE_PRESERVED               0x30D2
#وصف_ڪريو EGL_NO_IMAGE                      EGL_CAST(EGLImage,0)
تعريفنوع EGLSync (EGLAPIENTRYP PFNEGLCREATESYNCPROC) (EGLDisplay dpy, EGLenum type, ثابت EGLAttrib *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCPROC) (EGLDisplay dpy, EGLSync sync);
تعريفنوع EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCPROC) (EGLDisplay dpy, EGLSync sync, EGLint flags, EGLTime timeout);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETSYNCATTRIBPROC) (EGLDisplay dpy, EGLSync sync, EGLint attribute, EGLAttrib *قدر);
تعريفنوع EGLImage (EGLAPIENTRYP PFNEGLCREATEIMAGEPROC) (EGLDisplay dpy, EGLContext ctx, EGLenum هدف, EGLClient_بفر بفر_2, ثابت EGLAttrib *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYIMAGEPROC) (EGLDisplay dpy, EGLImage image);
تعريفنوع EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYPROC) (EGLenum platform, فراغ *native_display, ثابت EGLAttrib *attrib_list);
تعريفنوع EGLSurface (EGLAPIENTRYP PFNEGLCREATEPLATFORMWINDOWSURFACEPROC) (EGLDisplay dpy, EGLConfig config, فراغ *native_دري, ثابت EGLAttrib *attrib_list);
تعريفنوع EGLSurface (EGLAPIENTRYP PFNEGLCREATEPLATFORMPIXMAPSURFACEPROC) (EGLDisplay dpy, EGLConfig config, فراغ *native_pixmap, ثابت EGLAttrib *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLWAITSYNCPROC) (EGLDisplay dpy, EGLSync sync, EGLint flags);
#إذا EGL_EGL_PROTOTYPES
EGLAPI EGLSync EGLAPIENTRY eglCreateSync (EGLDisplay dpy, EGLenum type, ثابت EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySync (EGLDisplay dpy, EGLSync sync);
EGLAPI EGLint EGLAPIENTRY eglClientWaitSync (EGLDisplay dpy, EGLSync sync, EGLint flags, EGLTime timeout);
EGLAPI EGLBoolean EGLAPIENTRY eglGetSyncAttrib (EGLDisplay dpy, EGLSync sync, EGLint attribute, EGLAttrib *قدر);
EGLAPI EGLImage EGLAPIENTRY eglCreateImage (EGLDisplay dpy, EGLContext ctx, EGLenum هدف, EGLClient_بفر بفر_2, ثابت EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyImage (EGLDisplay dpy, EGLImage image);
EGLAPI EGLDisplay EGLAPIENTRY eglGetPlatformDisplay (EGLenum platform, فراغ *native_display, ثابت EGLAttrib *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY egl_Create_Platform_دري_Surface (EGLDisplay dpy, EGLConfig config, فراغ *native_دري, ثابت EGLAttrib *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePlatformPixmapSurface (EGLDisplay dpy, EGLConfig config, فراغ *native_pixmap, ثابت EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglWaitSync (EGLDisplay dpy, EGLSync sync, EGLint flags);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_VERSION_1_5 */

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو
