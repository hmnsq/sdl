#నిర్వచితం_కాకపోతే __egl_h_
#నిర్వచించు __egl_h_ 1

#నిర్వచితమైతే __cplusplus
బాహ్య "C" {
#అయితే_ముగింపు

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

#అన్తర్భావ <EGL/eglplatform.h>

#నిర్వచితం_కాకపోతే EGL_EGL_PROTOTYPES
#నిర్వచించు EGL_EGL_PROTOTYPES 1
#అయితే_ముగింపు

/* Generated on date 20260319 */

/* Generated C header for:
 * API: egl
 * Versions considered: .*
 * Versions emitted: .*
 * Default extensions included: None
 * Additional extensions included: _nomatch_^
 * Extensions removed: _nomatch_^
 */

#నిర్వచితం_కాకపోతే EGL_సంస్కరణ_1_0
#నిర్వచించు EGL_సంస్కరణ_1_0 1
రకనిర్వచనం గుర్తులేని పూర్ణాంకం EGLBoolean;
రకనిర్వచనం శూన్య *EGLDisplay;
#అన్తర్భావ <KHR/khrplatform.h>
#అన్తర్భావ <EGL/eglplatform.h>
రకనిర్వచనం శూన్య *EGLConfig;
రకనిర్వచనం శూన్య *EGLSurface;
రకనిర్వచనం శూన్య *EGLContext;
రకనిర్వచనం శూన్య (*__eglMustCastToProperFunctionPointerType)(శూన్య);
#నిర్వచించు EGL_ALPHA_కొలత                    0x3021
#నిర్వచించు EGL_BAD_ACCESS                    0x3002
#నిర్వచించు EGL_BAD_ALLOC                     0x3003
#నిర్వచించు EGL_BAD_ATTRIBUTE                 0x3004
#నిర్వచించు EGL_BAD_CONFIG                    0x3005
#నిర్వచించు EGL_BAD_CONTEXT                   0x3006
#నిర్వచించు EGL_BAD_CURRENT_SURFACE           0x3007
#నిర్వచించు EGL_BAD_DISPLAY                   0x3008
#నిర్వచించు EGL_BAD_సరిపోలిక                     0x3009
#నిర్వచించు EGL_BAD_NATIVE_PIXMAP             0x300A
#నిర్వచించు EGL_BAD_NATIVE_కిటికీ             0x300B
#నిర్వచించు EGL_BAD_PARAMETER                 0x300C
#నిర్వచించు EGL_BAD_SURFACE                   0x300D
#నిర్వచించు EGL_BLUE_కొలత                     0x3022
#నిర్వచించు EGL_బఫరు_కొలత                   0x3020
#నిర్వచించు EGL_CONFIG_CAVEAT                 0x3027
#నిర్వచించు EGL_CONFIG_ID                     0x3028
#నిర్వచించు EGL_CORE_NATIVE_ENGINE            0x305B
#నిర్వచించు EGL_లోతు_కొలత                    0x3025
#నిర్వచించు EGL_DONT_CARE                     EGL_CAST(EGLint,-1)
#నిర్వచించు EGL_DRAW                          0x3059
#నిర్వచించు EGL_EXTENSIONS                    0x3055
#నిర్వచించు EGL_FALSE                         0
#నిర్వచించు EGL_GREEN_కొలత                    0x3023
#నిర్వచించు EGL_ఎత్తు                        0x3056
#నిర్వచించు EGL_అతిపెద్ద_PBUFFER               0x3058
#నిర్వచించు EGL_LEVEL                         0x3029
#నిర్వచించు EGL_MAX_PBUFFER_ఎత్తు            0x302A
#నిర్వచించు EGL_MAX_PBUFFER_PIXELS            0x302B
#నిర్వచించు EGL_MAX_PBUFFER_వెడల్పు             0x302C
#నిర్వచించు EGL_NATIVE_RENDERABLE             0x302D
#నిర్వచించు EGL_NATIVE_VISUAL_ID              0x302E
#నిర్వచించు EGL_NATIVE_VISUAL_TYPE            0x302F
#నిర్వచించు EGL_NONE                          0x3038
#నిర్వచించు EGL_NON_CONFORMANT_CONFIG         0x3051
#నిర్వచించు EGL_NOT_INITIALIZED               0x3001
#నిర్వచించు EGL_NO_CONTEXT                    EGL_CAST(EGLContext,0)
#నిర్వచించు EGL_NO_DISPLAY                    EGL_CAST(EGLDisplay,0)
#నిర్వచించు EGL_NO_SURFACE                    EGL_CAST(EGLSurface,0)
#నిర్వచించు EGL_PBUFFER_బిట్టు                   0x0001
#నిర్వచించు EGL_PIXMAP_బిట్టు                    0x0002
#నిర్వచించు EGL_READ                          0x305A
#నిర్వచించు EGL_RED_కొలత                      0x3024
#నిర్వచించు EGL_SAMPLES                       0x3031
#నిర్వచించు EGL_SAMPLE_BUFFERS                0x3032
#నిర్వచించు EGL_SLOW_CONFIG                   0x3050
#నిర్వచించు EGL_STENCIL_కొలత                  0x3026
#నిర్వచించు EGL_SUCCESS                       0x3000
#నిర్వచించు EGL_SURFACE_TYPE                  0x3033
#నిర్వచించు EGL_TRANSPARENT_BLUE_విలువ        0x3035
#నిర్వచించు EGL_TRANSPARENT_GREEN_విలువ       0x3036
#నిర్వచించు EGL_TRANSPARENT_RED_విలువ         0x3037
#నిర్వచించు EGL_TRANSPARENT_RGB               0x3052
#నిర్వచించు EGL_TRANSPARENT_TYPE              0x3034
#నిర్వచించు EGL_TRUE                          1
#నిర్వచించు EGL_VENDOR                        0x3053
#నిర్వచించు EGL_సంస్కరణ                       0x3054
#నిర్వచించు EGL_వెడల్పు                         0x3057
#నిర్వచించు EGL_కిటికీ_బిట్టు                    0x0004
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLCHOOSECONFIGPROC) (EGLDisplay dpy, స్థిరరాశి EGLint *attrib_list, EGLConfig *configs, EGLint config_కొలత, EGLint *అంకె_config);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLCOPYBUFFERSPROC) (EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType లక్ష్యం);
రకనిర్వచనం EGLContext (EGLAPIENTRYP PFNEGLCREATECONTEXTPROC) (EGLDisplay dpy, EGLConfig config, EGLContext share_context, స్థిరరాశి EGLint *attrib_list);
రకనిర్వచనం EGLSurface (EGLAPIENTRYP PFNEGLCREATEPBUFFERSURFACEPROC) (EGLDisplay dpy, EGLConfig config, స్థిరరాశి EGLint *attrib_list);
రకనిర్వచనం EGLSurface (EGLAPIENTRYP PFNEGLCREATEPIXMAPSURFACEPROC) (EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, స్థిరరాశి EGLint *attrib_list);
రకనిర్వచనం EGLSurface (EGLAPIENTRYP PFNEGLCREATEWINDOWSURFACEPROC) (EGLDisplay dpy, EGLConfig config, EGLNative_కిటికీ_Type win, స్థిరరాశి EGLint *attrib_list);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYCONTEXTPROC) (EGLDisplay dpy, EGLContext ctx);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSURFACEPROC) (EGLDisplay dpy, EGLSurface surface);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLGETCONFIGATTRIBPROC) (EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *విలువ);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLGETCONFIGSPROC) (EGLDisplay dpy, EGLConfig *configs, EGLint config_కొలత, EGLint *అంకె_config);
రకనిర్వచనం EGLDisplay (EGLAPIENTRYP PFNEGLGETCURRENTDISPLAYPROC) (శూన్య);
రకనిర్వచనం EGLSurface (EGLAPIENTRYP PFNEGLGETCURRENTSURFACEPROC) (EGLint readdraw);
రకనిర్వచనం EGLDisplay (EGLAPIENTRYP PFNEGLGETDISPLAYPROC) (EGLNativeDisplayType display_id);
రకనిర్వచనం EGLint (EGLAPIENTRYP PFNEGLGETERRORPROC) (శూన్య);
రకనిర్వచనం __eglMustCastToProperFunctionPointerType (EGLAPIENTRYP PFNEGLGETPROCADDRESSPROC) (స్థిరరాశి అక్షరం *procname);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLINITIALIZEPROC) (EGLDisplay dpy, EGLint *major, EGLint *minor);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLMAKECURRENTPROC) (EGLDisplay dpy, EGLSurface draw, EGLSurface పఠ, EGLContext ctx);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLQUERYCONTEXTPROC) (EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint *విలువ);
రకనిర్వచనం స్థిరరాశి అక్షరం *(EGLAPIENTRYP PFNEGLQUERYSTRINGPROC) (EGLDisplay dpy, EGLint name);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSURFACEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint *విలువ);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSPROC) (EGLDisplay dpy, EGLSurface surface);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLTERMINATEPROC) (EGLDisplay dpy);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLWAITGLPROC) (శూన్య);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLWAITNATIVEPROC) (EGLint engine);
#ఒకవేళ EGL_EGL_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_ఎంచుకో_Config (EGLDisplay dpy, స్థిరరాశి EGLint *attrib_list, EGLConfig *configs, EGLint config_కొలత, EGLint *అంకె_config);
EGLAPI EGLBoolean EGLAPIENTRY eglCopyBuffers (EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType లక్ష్యం);
EGLAPI EGLContext EGLAPIENTRY eglCreateContext (EGLDisplay dpy, EGLConfig config, EGLContext share_context, స్థిరరాశి EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePbufferSurface (EGLDisplay dpy, EGLConfig config, స్థిరరాశి EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePixmapSurface (EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, స్థిరరాశి EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY egl_Create_కిటికీ_Surface (EGLDisplay dpy, EGLConfig config, EGLNative_కిటికీ_Type win, స్థిరరాశి EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyContext (EGLDisplay dpy, EGLContext ctx);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySurface (EGLDisplay dpy, EGLSurface surface);
EGLAPI EGLBoolean EGLAPIENTRY eglGetConfigAttrib (EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *విలువ);
EGLAPI EGLBoolean EGLAPIENTRY eglGetConfigs (EGLDisplay dpy, EGLConfig *configs, EGLint config_కొలత, EGLint *అంకె_config);
EGLAPI EGLDisplay EGLAPIENTRY eglGetCurrentDisplay (శూన్య);
EGLAPI EGLSurface EGLAPIENTRY eglGetCurrentSurface (EGLint readdraw);
EGLAPI EGLDisplay EGLAPIENTRY eglGetDisplay (EGLNativeDisplayType display_id);
EGLAPI EGLint EGLAPIENTRY eglGetError (శూన్య);
EGLAPI __eglMustCastToProperFunctionPointerType EGLAPIENTRY egl_Get_Proc_చిరునామా (స్థిరరాశి అక్షరం *procname);
EGLAPI EGLBoolean EGLAPIENTRY eglInitialize (EGLDisplay dpy, EGLint *major, EGLint *minor);
EGLAPI EGLBoolean EGLAPIENTRY eglMakeCurrent (EGLDisplay dpy, EGLSurface draw, EGLSurface పఠ, EGLContext ctx);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryContext (EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint *విలువ);
EGLAPI స్థిరరాశి అక్షరం *EGLAPIENTRY eglQueryString (EGLDisplay dpy, EGLint name);
EGLAPI EGLBoolean EGLAPIENTRY eglQuerySurface (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint *విలువ);
EGLAPI EGLBoolean EGLAPIENTRY egl_మార్పిడి_Buffers (EGLDisplay dpy, EGLSurface surface);
EGLAPI EGLBoolean EGLAPIENTRY eglTerminate (EGLDisplay dpy);
EGLAPI EGLBoolean EGLAPIENTRY eglWaitGL (శూన్య);
EGLAPI EGLBoolean EGLAPIENTRY eglWaitNative (EGLint engine);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_VERSION_1_0 */

#నిర్వచితం_కాకపోతే EGL_సంస్కరణ_1_1
#నిర్వచించు EGL_సంస్కరణ_1_1 1
#నిర్వచించు EGL_వెనుక_బఫరు                   0x3084
#నిర్వచించు EGL_BIND_గమ్యం_TEXTURE_RGB           0x3039
#నిర్వచించు EGL_BIND_గమ్యం_TEXTURE_RGBA          0x303A
#నిర్వచించు EGL_CONTEXT_కోల్పోయిన                  0x300E
#నిర్వచించు EGL_MIN_మార్పిడి_INTERVAL             0x303B
#నిర్వచించు EGL_MAX_మార్పిడి_INTERVAL             0x303C
#నిర్వచించు EGL_MIPMAP_TEXTURE                0x3082
#నిర్వచించు EGL_MIPMAP_LEVEL                  0x3083
#నిర్వచించు EGL_NO_TEXTURE                    0x305C
#నిర్వచించు EGL_TEXTURE_2D                    0x305F
#నిర్వచించు EGL_TEXTURE_FORMAT                0x3080
#నిర్వచించు EGL_TEXTURE_RGB                   0x305D
#నిర్వచించు EGL_TEXTURE_RGBA                  0x305E
#నిర్వచించు EGL_TEXTURE_లక్ష్యం                0x3081
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLBINDTEXIMAGEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint బఫరు_2);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLRELEASETEXIMAGEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint బఫరు_2);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLSURFACEATTRIBPROC) (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint విలువ);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLSWAPINTERVALPROC) (EGLDisplay dpy, EGLint interval);
#ఒకవేళ EGL_EGL_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglBindTexImage (EGLDisplay dpy, EGLSurface surface, EGLint బఫరు_2);
EGLAPI EGLBoolean EGLAPIENTRY eglReleaseTexImage (EGLDisplay dpy, EGLSurface surface, EGLint బఫరు_2);
EGLAPI EGLBoolean EGLAPIENTRY eglSurfaceAttrib (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint విలువ);
EGLAPI EGLBoolean EGLAPIENTRY egl_మార్పిడి_Interval (EGLDisplay dpy, EGLint interval);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_VERSION_1_1 */

#నిర్వచితం_కాకపోతే EGL_సంస్కరణ_1_2
#నిర్వచించు EGL_సంస్కరణ_1_2 1
రకనిర్వచనం గుర్తులేని పూర్ణాంకం EGLenum;
రకనిర్వచనం శూన్య *EGLClient_బఫరు;
#నిర్వచించు EGL_ALPHA_FORMAT                  0x3088
#నిర్వచించు EGL_ALPHA_FORMAT_NONPRE           0x308B
#నిర్వచించు EGL_ALPHA_FORMAT_PRE              0x308C
#నిర్వచించు EGL_ALPHA_ముసుగు_కొలత               0x303E
#నిర్వచించు EGL_బఫరు_PRESERVED              0x3094
#నిర్వచించు EGL_బఫరు_DESTROYED              0x3095
#నిర్వచించు EGL_CLIENT_APIS                   0x308D
#నిర్వచించు EGL_COLORSPACE                    0x3087
#నిర్వచించు EGL_COLORSPACE_sRGB               0x3089
#నిర్వచించు EGL_COLORSPACE_రేఖీయ             0x308A
#నిర్వచించు EGL_COLOR_బఫరు_TYPE             0x303F
#నిర్వచించు EGL_CONTEXT_CLIENT_TYPE           0x3097
#నిర్వచించు EGL_DISPLAY_SCALING               10000
#నిర్వచించు EGL_HORIZONTAL_RESOLUTION         0x3090
#నిర్వచించు EGL_LUMINANCE_బఫరు              0x308F
#నిర్వచించు EGL_LUMINANCE_కొలత                0x303D
#నిర్వచించు EGL_OPENGL_ES_బిట్టు                 0x0001
#నిర్వచించు EGL_OPENVG_బిట్టు                    0x0002
#నిర్వచించు EGL_OPENGL_ES_API                 0x30A0
#నిర్వచించు EGL_OPENVG_API                    0x30A1
#నిర్వచించు EGL_OPENVG_IMAGE                  0x3096
#నిర్వచించు EGL_PIXEL_ASPECT_నిష్పత్తి            0x3092
#నిర్వచించు EGL_RENDERABLE_TYPE               0x3040
#నిర్వచించు EGL_RENDER_బఫరు                 0x3086
#నిర్వచించు EGL_RGB_బఫరు                    0x308E
#నిర్వచించు EGL_SINGLE_బఫరు                 0x3085
#నిర్వచించు EGL_మార్పిడి_BEHAVIOR                 0x3093
#నిర్వచించు EGL_UNKNOWN                       EGL_CAST(EGLint,-1)
#నిర్వచించు EGL_VERTICAL_RESOLUTION           0x3091
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLBINDAPIPROC) (EGLenum api);
రకనిర్వచనం EGLenum (EGLAPIENTRYP PFNEGLQUERYAPIPROC) (శూన్య);
రకనిర్వచనం EGLSurface (EGLAPIENTRYP PFNEGLCREATEPBUFFERFROMCLIENTBUFFERPROC) (EGLDisplay dpy, EGLenum buftype, EGLClient_బఫరు బఫరు_2, EGLConfig config, స్థిరరాశి EGLint *attrib_list);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLRELEASETHREADPROC) (శూన్య);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLWAITCLIENTPROC) (శూన్య);
#ఒకవేళ EGL_EGL_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglBindAPI (EGLenum api);
EGLAPI EGLenum EGLAPIENTRY eglQueryAPI (శూన్య);
EGLAPI EGLSurface EGLAPIENTRY egl_Create_Pbuffer_From_Client_బఫరు (EGLDisplay dpy, EGLenum buftype, EGLClient_బఫరు బఫరు_2, EGLConfig config, స్థిరరాశి EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglReleaseThread (శూన్య);
EGLAPI EGLBoolean EGLAPIENTRY eglWaitClient (శూన్య);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_VERSION_1_2 */

#నిర్వచితం_కాకపోతే EGL_సంస్కరణ_1_3
#నిర్వచించు EGL_సంస్కరణ_1_3 1
#నిర్వచించు EGL_CONFORMANT                    0x3042
#నిర్వచించు EGL_CONTEXT_CLIENT_సంస్కరణ        0x3098
#నిర్వచించు EGL_సరిపోలిక_NATIVE_PIXMAP           0x3041
#నిర్వచించు EGL_OPENGL_ES2_బిట్టు                0x0004
#నిర్వచించు EGL_VG_ALPHA_FORMAT               0x3088
#నిర్వచించు EGL_VG_ALPHA_FORMAT_NONPRE        0x308B
#నిర్వచించు EGL_VG_ALPHA_FORMAT_PRE           0x308C
#నిర్వచించు EGL_VG_ALPHA_FORMAT_PRE_బిట్టు       0x0040
#నిర్వచించు EGL_VG_COLORSPACE                 0x3087
#నిర్వచించు EGL_VG_COLORSPACE_sRGB            0x3089
#నిర్వచించు EGL_VG_COLORSPACE_రేఖీయ          0x308A
#నిర్వచించు EGL_VG_COLORSPACE_రేఖీయ_బిట్టు      0x0020
#అయితే_ముగింపు /* EGL_VERSION_1_3 */

#నిర్వచితం_కాకపోతే EGL_సంస్కరణ_1_4
#నిర్వచించు EGL_సంస్కరణ_1_4 1
#నిర్వచించు EGL_DEFAULT_DISPLAY               EGL_CAST(EGLNativeDisplayType,0)
#నిర్వచించు EGL_MULTISAMPLE_RESOLVE_BOX_బిట్టు   0x0200
#నిర్వచించు EGL_MULTISAMPLE_RESOLVE           0x3099
#నిర్వచించు EGL_MULTISAMPLE_RESOLVE_DEFAULT   0x309A
#నిర్వచించు EGL_MULTISAMPLE_RESOLVE_BOX       0x309B
#నిర్వచించు EGL_OPENGL_API                    0x30A2
#నిర్వచించు EGL_OPENGL_బిట్టు                    0x0008
#నిర్వచించు EGL_మార్పిడి_BEHAVIOR_PRESERVED_బిట్టు   0x0400
రకనిర్వచనం EGLContext (EGLAPIENTRYP PFNEGLGETCURRENTCONTEXTPROC) (శూన్య);
#ఒకవేళ EGL_EGL_PROTOTYPES
EGLAPI EGLContext EGLAPIENTRY eglGetCurrentContext (శూన్య);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_VERSION_1_4 */

#నిర్వచితం_కాకపోతే EGL_సంస్కరణ_1_5
#నిర్వచించు EGL_సంస్కరణ_1_5 1
రకనిర్వచనం శూన్య *EGLSync;
రకనిర్వచనం intptr_t EGLAttrib;
రకనిర్వచనం khronos_utime_nanoseconds_t EGLTime;
రకనిర్వచనం శూన్య *EGLImage;
#నిర్వచించు EGL_CONTEXT_MAJOR_సంస్కరణ         0x3098
#నిర్వచించు EGL_CONTEXT_MINOR_సంస్కరణ         0x30FB
#నిర్వచించు EGL_CONTEXT_OPENGL_PROFILE_ముసుగు   0x30FD
#నిర్వచించు EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY 0x31BD
#నిర్వచించు EGL_NO_RESET_NOTIFICATION         0x31BE
#నిర్వచించు EGL_LOSE_CONTEXT_ON_RESET         0x31BF
#నిర్వచించు EGL_CONTEXT_OPENGL_CORE_PROFILE_బిట్టు 0x00000001
#నిర్వచించు EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_బిట్టు 0x00000002
#నిర్వచించు EGL_CONTEXT_OPENGL_DEBUG          0x31B0
#నిర్వచించు EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE 0x31B1
#నిర్వచించు EGL_CONTEXT_OPENGL_ROBUST_ACCESS  0x31B2
#నిర్వచించు EGL_OPENGL_ES3_బిట్టు                0x00000040
#నిర్వచించు EGL_CL_EVENT_HANDLE               0x309C
#నిర్వచించు EGL_SYNC_CL_EVENT                 0x30FE
#నిర్వచించు EGL_SYNC_CL_EVENT_COMPLETE        0x30FF
#నిర్వచించు EGL_SYNC_పూర్వ_COMMANDS_COMPLETE  0x30F0
#నిర్వచించు EGL_SYNC_TYPE                     0x30F7
#నిర్వచించు EGL_SYNC_స్థితి                   0x30F1
#నిర్వచించు EGL_SYNC_CONDITION                0x30F8
#నిర్వచించు EGL_SIGNALED                      0x30F2
#నిర్వచించు EGL_UNSIGNALED                    0x30F3
#నిర్వచించు EGL_SYNC_FLUSH_COMMANDS_బిట్టు       0x0001
#నిర్వచించు EGL_FOREVER                       0xFFFFFFFFFFFFFFFFull
#నిర్వచించు EGL_TIMEOUT_EXPIRED               0x30F5
#నిర్వచించు EGL_CONDITION_SATISFIED           0x30F6
#నిర్వచించు EGL_NO_SYNC                       EGL_CAST(EGLSync,0)
#నిర్వచించు EGL_SYNC_FENCE                    0x30F9
#నిర్వచించు EGL_GL_COLORSPACE                 0x309D
#నిర్వచించు EGL_GL_COLORSPACE_SRGB            0x3089
#నిర్వచించు EGL_GL_COLORSPACE_రేఖీయ          0x308A
#నిర్వచించు EGL_GL_RENDERBUFFER               0x30B9
#నిర్వచించు EGL_GL_TEXTURE_2D                 0x30B1
#నిర్వచించు EGL_GL_TEXTURE_LEVEL              0x30BC
#నిర్వచించు EGL_GL_TEXTURE_3D                 0x30B2
#నిర్వచించు EGL_GL_TEXTURE_ZOFFSET            0x30BD
#నిర్వచించు EGL_GL_TEXTURE_CUBE_MAP_ధనాత్మక_X 0x30B3
#నిర్వచించు EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_X 0x30B4
#నిర్వచించు EGL_GL_TEXTURE_CUBE_MAP_ధనాత్మక_Y 0x30B5
#నిర్వచించు EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Y 0x30B6
#నిర్వచించు EGL_GL_TEXTURE_CUBE_MAP_ధనాత్మక_Z 0x30B7
#నిర్వచించు EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 0x30B8
#నిర్వచించు EGL_IMAGE_PRESERVED               0x30D2
#నిర్వచించు EGL_NO_IMAGE                      EGL_CAST(EGLImage,0)
రకనిర్వచనం EGLSync (EGLAPIENTRYP PFNEGLCREATESYNCPROC) (EGLDisplay dpy, EGLenum type, స్థిరరాశి EGLAttrib *attrib_list);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCPROC) (EGLDisplay dpy, EGLSync sync);
రకనిర్వచనం EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCPROC) (EGLDisplay dpy, EGLSync sync, EGLint flags, EGLTime timeout);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLGETSYNCATTRIBPROC) (EGLDisplay dpy, EGLSync sync, EGLint attribute, EGLAttrib *విలువ);
రకనిర్వచనం EGLImage (EGLAPIENTRYP PFNEGLCREATEIMAGEPROC) (EGLDisplay dpy, EGLContext ctx, EGLenum లక్ష్యం, EGLClient_బఫరు బఫరు_2, స్థిరరాశి EGLAttrib *attrib_list);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYIMAGEPROC) (EGLDisplay dpy, EGLImage image);
రకనిర్వచనం EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYPROC) (EGLenum platform, శూన్య *native_display, స్థిరరాశి EGLAttrib *attrib_list);
రకనిర్వచనం EGLSurface (EGLAPIENTRYP PFNEGLCREATEPLATFORMWINDOWSURFACEPROC) (EGLDisplay dpy, EGLConfig config, శూన్య *native_కిటికీ, స్థిరరాశి EGLAttrib *attrib_list);
రకనిర్వచనం EGLSurface (EGLAPIENTRYP PFNEGLCREATEPLATFORMPIXMAPSURFACEPROC) (EGLDisplay dpy, EGLConfig config, శూన్య *native_pixmap, స్థిరరాశి EGLAttrib *attrib_list);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLWAITSYNCPROC) (EGLDisplay dpy, EGLSync sync, EGLint flags);
#ఒకవేళ EGL_EGL_PROTOTYPES
EGLAPI EGLSync EGLAPIENTRY eglCreateSync (EGLDisplay dpy, EGLenum type, స్థిరరాశి EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySync (EGLDisplay dpy, EGLSync sync);
EGLAPI EGLint EGLAPIENTRY eglClientWaitSync (EGLDisplay dpy, EGLSync sync, EGLint flags, EGLTime timeout);
EGLAPI EGLBoolean EGLAPIENTRY eglGetSyncAttrib (EGLDisplay dpy, EGLSync sync, EGLint attribute, EGLAttrib *విలువ);
EGLAPI EGLImage EGLAPIENTRY eglCreateImage (EGLDisplay dpy, EGLContext ctx, EGLenum లక్ష్యం, EGLClient_బఫరు బఫరు_2, స్థిరరాశి EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyImage (EGLDisplay dpy, EGLImage image);
EGLAPI EGLDisplay EGLAPIENTRY eglGetPlatformDisplay (EGLenum platform, శూన్య *native_display, స్థిరరాశి EGLAttrib *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY egl_Create_Platform_కిటికీ_Surface (EGLDisplay dpy, EGLConfig config, శూన్య *native_కిటికీ, స్థిరరాశి EGLAttrib *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePlatformPixmapSurface (EGLDisplay dpy, EGLConfig config, శూన్య *native_pixmap, స్థిరరాశి EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglWaitSync (EGLDisplay dpy, EGLSync sync, EGLint flags);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_VERSION_1_5 */

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు
