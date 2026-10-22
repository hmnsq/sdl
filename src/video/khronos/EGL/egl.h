#अगर_अघोषित __egl_h_
#घोषणा __egl_h_ 1

#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर

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

#समावेश <EGL/eglplatform.h>

#अगर_अघोषित EGL_EGL_PROTOTYPES
#घोषणा EGL_EGL_PROTOTYPES 1
#पूर्ण_अगर

/* Generated on date 20260319 */

/* Generated C header for:
 * API: egl
 * Versions considered: .*
 * Versions emitted: .*
 * Default extensions included: None
 * Additional extensions included: _nomatch_^
 * Extensions removed: _nomatch_^
 */

#अगर_अघोषित EGL_VERSION_1_0
#घोषणा EGL_VERSION_1_0 1
प्रकार अचिन्हित पूर्णांक EGLBoolean;
प्रकार व्योम *EGLDisplay;
#समावेश <KHR/khrplatform.h>
#समावेश <EGL/eglplatform.h>
प्रकार व्योम *EGLConfig;
प्रकार व्योम *EGLSurface;
प्रकार व्योम *EGLContext;
प्रकार व्योम (*__eglMustCastToProperFunctionPointerType)(व्योम);
#घोषणा EGL_ALPHA_आकार                    0x3021
#घोषणा EGL_BAD_ACCESS                    0x3002
#घोषणा EGL_BAD_ALLOC                     0x3003
#घोषणा EGL_BAD_ATTRIBUTE                 0x3004
#घोषणा EGL_BAD_CONFIG                    0x3005
#घोषणा EGL_BAD_CONTEXT                   0x3006
#घोषणा EGL_BAD_CURRENT_SURFACE           0x3007
#घोषणा EGL_BAD_DISPLAY                   0x3008
#घोषणा EGL_BAD_MATCH                     0x3009
#घोषणा EGL_BAD_NATIVE_PIXMAP             0x300A
#घोषणा EGL_BAD_NATIVE_WINDOW             0x300B
#घोषणा EGL_BAD_PARAMETER                 0x300C
#घोषणा EGL_BAD_SURFACE                   0x300D
#घोषणा EGL_BLUE_आकार                     0x3022
#घोषणा EGL_बफर_आकार                   0x3020
#घोषणा EGL_CONFIG_CAVEAT                 0x3027
#घोषणा EGL_CONFIG_ID                     0x3028
#घोषणा EGL_CORE_NATIVE_ENGINE            0x305B
#घोषणा EGL_DEPTH_आकार                    0x3025
#घोषणा EGL_DONT_CARE                     EGL_CAST(EGLint,-1)
#घोषणा EGL_DRAW                          0x3059
#घोषणा EGL_EXTENSIONS                    0x3055
#घोषणा EGL_FALSE                         0
#घोषणा EGL_GREEN_आकार                    0x3023
#घोषणा EGL_HEIGHT                        0x3056
#घोषणा EGL_LARGEST_PBUFFER               0x3058
#घोषणा EGL_LEVEL                         0x3029
#घोषणा EGL_MAX_PBUFFER_HEIGHT            0x302A
#घोषणा EGL_MAX_PBUFFER_PIXELS            0x302B
#घोषणा EGL_MAX_PBUFFER_WIDTH             0x302C
#घोषणा EGL_NATIVE_RENDERABLE             0x302D
#घोषणा EGL_NATIVE_VISUAL_ID              0x302E
#घोषणा EGL_NATIVE_VISUAL_TYPE            0x302F
#घोषणा EGL_NONE                          0x3038
#घोषणा EGL_NON_CONFORMANT_CONFIG         0x3051
#घोषणा EGL_NOT_INITIALIZED               0x3001
#घोषणा EGL_NO_CONTEXT                    EGL_CAST(EGLContext,0)
#घोषणा EGL_NO_DISPLAY                    EGL_CAST(EGLDisplay,0)
#घोषणा EGL_NO_SURFACE                    EGL_CAST(EGLSurface,0)
#घोषणा EGL_PBUFFER_BIT                   0x0001
#घोषणा EGL_PIXMAP_BIT                    0x0002
#घोषणा EGL_READ                          0x305A
#घोषणा EGL_RED_आकार                      0x3024
#घोषणा EGL_SAMPLES                       0x3031
#घोषणा EGL_SAMPLE_BUFFERS                0x3032
#घोषणा EGL_SLOW_CONFIG                   0x3050
#घोषणा EGL_STENCIL_आकार                  0x3026
#घोषणा EGL_SUCCESS                       0x3000
#घोषणा EGL_SURFACE_TYPE                  0x3033
#घोषणा EGL_TRANSPARENT_BLUE_मूल्य        0x3035
#घोषणा EGL_TRANSPARENT_GREEN_मूल्य       0x3036
#घोषणा EGL_TRANSPARENT_RED_मूल्य         0x3037
#घोषणा EGL_TRANSPARENT_RGB               0x3052
#घोषणा EGL_TRANSPARENT_TYPE              0x3034
#घोषणा EGL_TRUE                          1
#घोषणा EGL_VENDOR                        0x3053
#घोषणा EGL_VERSION                       0x3054
#घोषणा EGL_WIDTH                         0x3057
#घोषणा EGL_WINDOW_BIT                    0x0004
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLCHOOSECONFIGPROC) (EGLDisplay dpy, स्थिर EGLint *attrib_list, EGLConfig *configs, EGLint config_आकार, EGLint *अंक_config);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLCOPYBUFFERSPROC) (EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType target);
प्रकार EGLContext (EGLAPIENTRYP PFNEGLCREATECONTEXTPROC) (EGLDisplay dpy, EGLConfig config, EGLContext share_context, स्थिर EGLint *attrib_list);
प्रकार EGLSurface (EGLAPIENTRYP PFNEGLCREATEPBUFFERSURFACEPROC) (EGLDisplay dpy, EGLConfig config, स्थिर EGLint *attrib_list);
प्रकार EGLSurface (EGLAPIENTRYP PFNEGLCREATEPIXMAPSURFACEPROC) (EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, स्थिर EGLint *attrib_list);
प्रकार EGLSurface (EGLAPIENTRYP PFNEGLCREATEWINDOWSURFACEPROC) (EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, स्थिर EGLint *attrib_list);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYCONTEXTPROC) (EGLDisplay dpy, EGLContext ctx);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSURFACEPROC) (EGLDisplay dpy, EGLSurface surface);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLGETCONFIGATTRIBPROC) (EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *मूल्य);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLGETCONFIGSPROC) (EGLDisplay dpy, EGLConfig *configs, EGLint config_आकार, EGLint *अंक_config);
प्रकार EGLDisplay (EGLAPIENTRYP PFNEGLGETCURRENTDISPLAYPROC) (व्योम);
प्रकार EGLSurface (EGLAPIENTRYP PFNEGLGETCURRENTSURFACEPROC) (EGLint readdraw);
प्रकार EGLDisplay (EGLAPIENTRYP PFNEGLGETDISPLAYPROC) (EGLNativeDisplayType display_id);
प्रकार EGLint (EGLAPIENTRYP PFNEGLGETERRORPROC) (व्योम);
प्रकार __eglMustCastToProperFunctionPointerType (EGLAPIENTRYP PFNEGLGETPROCADDRESSPROC) (स्थिर अक्षर *procname);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLINITIALIZEPROC) (EGLDisplay dpy, EGLint *major, EGLint *minor);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLMAKECURRENTPROC) (EGLDisplay dpy, EGLSurface draw, EGLSurface पढ़ो, EGLContext ctx);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLQUERYCONTEXTPROC) (EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint *मूल्य);
प्रकार स्थिर अक्षर *(EGLAPIENTRYP PFNEGLQUERYSTRINGPROC) (EGLDisplay dpy, EGLint name);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSURFACEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint *मूल्य);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSPROC) (EGLDisplay dpy, EGLSurface surface);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLTERMINATEPROC) (EGLDisplay dpy);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLWAITGLPROC) (व्योम);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLWAITNATIVEPROC) (EGLint engine);
#अगर EGL_EGL_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglChooseConfig (EGLDisplay dpy, स्थिर EGLint *attrib_list, EGLConfig *configs, EGLint config_आकार, EGLint *अंक_config);
EGLAPI EGLBoolean EGLAPIENTRY eglCopyBuffers (EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType target);
EGLAPI EGLContext EGLAPIENTRY eglCreateContext (EGLDisplay dpy, EGLConfig config, EGLContext share_context, स्थिर EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePbufferSurface (EGLDisplay dpy, EGLConfig config, स्थिर EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePixmapSurface (EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, स्थिर EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreateWindowSurface (EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, स्थिर EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyContext (EGLDisplay dpy, EGLContext ctx);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySurface (EGLDisplay dpy, EGLSurface surface);
EGLAPI EGLBoolean EGLAPIENTRY eglGetConfigAttrib (EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *मूल्य);
EGLAPI EGLBoolean EGLAPIENTRY eglGetConfigs (EGLDisplay dpy, EGLConfig *configs, EGLint config_आकार, EGLint *अंक_config);
EGLAPI EGLDisplay EGLAPIENTRY eglGetCurrentDisplay (व्योम);
EGLAPI EGLSurface EGLAPIENTRY eglGetCurrentSurface (EGLint readdraw);
EGLAPI EGLDisplay EGLAPIENTRY eglGetDisplay (EGLNativeDisplayType display_id);
EGLAPI EGLint EGLAPIENTRY eglGetError (व्योम);
EGLAPI __eglMustCastToProperFunctionPointerType EGLAPIENTRY eglGetProcAddress (स्थिर अक्षर *procname);
EGLAPI EGLBoolean EGLAPIENTRY eglInitialize (EGLDisplay dpy, EGLint *major, EGLint *minor);
EGLAPI EGLBoolean EGLAPIENTRY eglMakeCurrent (EGLDisplay dpy, EGLSurface draw, EGLSurface पढ़ो, EGLContext ctx);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryContext (EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint *मूल्य);
EGLAPI स्थिर अक्षर *EGLAPIENTRY eglQueryString (EGLDisplay dpy, EGLint name);
EGLAPI EGLBoolean EGLAPIENTRY eglQuerySurface (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint *मूल्य);
EGLAPI EGLBoolean EGLAPIENTRY eglSwapBuffers (EGLDisplay dpy, EGLSurface surface);
EGLAPI EGLBoolean EGLAPIENTRY eglTerminate (EGLDisplay dpy);
EGLAPI EGLBoolean EGLAPIENTRY eglWaitGL (व्योम);
EGLAPI EGLBoolean EGLAPIENTRY eglWaitNative (EGLint engine);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_VERSION_1_0 */

#अगर_अघोषित EGL_VERSION_1_1
#घोषणा EGL_VERSION_1_1 1
#घोषणा EGL_BACK_बफर                   0x3084
#घोषणा EGL_BIND_TO_TEXTURE_RGB           0x3039
#घोषणा EGL_BIND_TO_TEXTURE_RGBA          0x303A
#घोषणा EGL_CONTEXT_LOST                  0x300E
#घोषणा EGL_MIN_SWAP_INTERVAL             0x303B
#घोषणा EGL_MAX_SWAP_INTERVAL             0x303C
#घोषणा EGL_MIPMAP_TEXTURE                0x3082
#घोषणा EGL_MIPMAP_LEVEL                  0x3083
#घोषणा EGL_NO_TEXTURE                    0x305C
#घोषणा EGL_TEXTURE_2D                    0x305F
#घोषणा EGL_TEXTURE_FORMAT                0x3080
#घोषणा EGL_TEXTURE_RGB                   0x305D
#घोषणा EGL_TEXTURE_RGBA                  0x305E
#घोषणा EGL_TEXTURE_TARGET                0x3081
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLBINDTEXIMAGEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint बफर_2);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLRELEASETEXIMAGEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint बफर_2);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLSURFACEATTRIBPROC) (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint मूल्य);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLSWAPINTERVALPROC) (EGLDisplay dpy, EGLint interval);
#अगर EGL_EGL_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglBindTexImage (EGLDisplay dpy, EGLSurface surface, EGLint बफर_2);
EGLAPI EGLBoolean EGLAPIENTRY eglReleaseTexImage (EGLDisplay dpy, EGLSurface surface, EGLint बफर_2);
EGLAPI EGLBoolean EGLAPIENTRY eglSurfaceAttrib (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint मूल्य);
EGLAPI EGLBoolean EGLAPIENTRY eglSwapInterval (EGLDisplay dpy, EGLint interval);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_VERSION_1_1 */

#अगर_अघोषित EGL_VERSION_1_2
#घोषणा EGL_VERSION_1_2 1
प्रकार अचिन्हित पूर्णांक EGLenum;
प्रकार व्योम *EGLClient_बफर;
#घोषणा EGL_ALPHA_FORMAT                  0x3088
#घोषणा EGL_ALPHA_FORMAT_NONPRE           0x308B
#घोषणा EGL_ALPHA_FORMAT_PRE              0x308C
#घोषणा EGL_ALPHA_MASK_आकार               0x303E
#घोषणा EGL_बफर_PRESERVED              0x3094
#घोषणा EGL_बफर_DESTROYED              0x3095
#घोषणा EGL_CLIENT_APIS                   0x308D
#घोषणा EGL_COLORSPACE                    0x3087
#घोषणा EGL_COLORSPACE_sRGB               0x3089
#घोषणा EGL_COLORSPACE_LINEAR             0x308A
#घोषणा EGL_COLOR_बफर_TYPE             0x303F
#घोषणा EGL_CONTEXT_CLIENT_TYPE           0x3097
#घोषणा EGL_DISPLAY_SCALING               10000
#घोषणा EGL_HORIZONTAL_RESOLUTION         0x3090
#घोषणा EGL_LUMINANCE_बफर              0x308F
#घोषणा EGL_LUMINANCE_आकार                0x303D
#घोषणा EGL_OPENGL_ES_BIT                 0x0001
#घोषणा EGL_OPENVG_BIT                    0x0002
#घोषणा EGL_OPENGL_ES_API                 0x30A0
#घोषणा EGL_OPENVG_API                    0x30A1
#घोषणा EGL_OPENVG_IMAGE                  0x3096
#घोषणा EGL_PIXEL_ASPECT_RATIO            0x3092
#घोषणा EGL_RENDERABLE_TYPE               0x3040
#घोषणा EGL_RENDER_बफर                 0x3086
#घोषणा EGL_RGB_बफर                    0x308E
#घोषणा EGL_SINGLE_बफर                 0x3085
#घोषणा EGL_SWAP_BEHAVIOR                 0x3093
#घोषणा EGL_UNKNOWN                       EGL_CAST(EGLint,-1)
#घोषणा EGL_VERTICAL_RESOLUTION           0x3091
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLBINDAPIPROC) (EGLenum api);
प्रकार EGLenum (EGLAPIENTRYP PFNEGLQUERYAPIPROC) (व्योम);
प्रकार EGLSurface (EGLAPIENTRYP PFNEGLCREATEPBUFFERFROMCLIENTBUFFERPROC) (EGLDisplay dpy, EGLenum buftype, EGLClient_बफर बफर_2, EGLConfig config, स्थिर EGLint *attrib_list);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLRELEASETHREADPROC) (व्योम);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLWAITCLIENTPROC) (व्योम);
#अगर EGL_EGL_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglBindAPI (EGLenum api);
EGLAPI EGLenum EGLAPIENTRY eglQueryAPI (व्योम);
EGLAPI EGLSurface EGLAPIENTRY egl_Create_Pbuffer_From_Client_बफर (EGLDisplay dpy, EGLenum buftype, EGLClient_बफर बफर_2, EGLConfig config, स्थिर EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglReleaseThread (व्योम);
EGLAPI EGLBoolean EGLAPIENTRY eglWaitClient (व्योम);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_VERSION_1_2 */

#अगर_अघोषित EGL_VERSION_1_3
#घोषणा EGL_VERSION_1_3 1
#घोषणा EGL_CONFORMANT                    0x3042
#घोषणा EGL_CONTEXT_CLIENT_VERSION        0x3098
#घोषणा EGL_MATCH_NATIVE_PIXMAP           0x3041
#घोषणा EGL_OPENGL_ES2_BIT                0x0004
#घोषणा EGL_VG_ALPHA_FORMAT               0x3088
#घोषणा EGL_VG_ALPHA_FORMAT_NONPRE        0x308B
#घोषणा EGL_VG_ALPHA_FORMAT_PRE           0x308C
#घोषणा EGL_VG_ALPHA_FORMAT_PRE_BIT       0x0040
#घोषणा EGL_VG_COLORSPACE                 0x3087
#घोषणा EGL_VG_COLORSPACE_sRGB            0x3089
#घोषणा EGL_VG_COLORSPACE_LINEAR          0x308A
#घोषणा EGL_VG_COLORSPACE_LINEAR_BIT      0x0020
#पूर्ण_अगर /* EGL_VERSION_1_3 */

#अगर_अघोषित EGL_VERSION_1_4
#घोषणा EGL_VERSION_1_4 1
#घोषणा EGL_DEFAULT_DISPLAY               EGL_CAST(EGLNativeDisplayType,0)
#घोषणा EGL_MULTISAMPLE_RESOLVE_BOX_BIT   0x0200
#घोषणा EGL_MULTISAMPLE_RESOLVE           0x3099
#घोषणा EGL_MULTISAMPLE_RESOLVE_DEFAULT   0x309A
#घोषणा EGL_MULTISAMPLE_RESOLVE_BOX       0x309B
#घोषणा EGL_OPENGL_API                    0x30A2
#घोषणा EGL_OPENGL_BIT                    0x0008
#घोषणा EGL_SWAP_BEHAVIOR_PRESERVED_BIT   0x0400
प्रकार EGLContext (EGLAPIENTRYP PFNEGLGETCURRENTCONTEXTPROC) (व्योम);
#अगर EGL_EGL_PROTOTYPES
EGLAPI EGLContext EGLAPIENTRY eglGetCurrentContext (व्योम);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_VERSION_1_4 */

#अगर_अघोषित EGL_VERSION_1_5
#घोषणा EGL_VERSION_1_5 1
प्रकार व्योम *EGLSync;
प्रकार intptr_t EGLAttrib;
प्रकार khronos_utime_nanoseconds_t EGLTime;
प्रकार व्योम *EGLImage;
#घोषणा EGL_CONTEXT_MAJOR_VERSION         0x3098
#घोषणा EGL_CONTEXT_MINOR_VERSION         0x30FB
#घोषणा EGL_CONTEXT_OPENGL_PROFILE_MASK   0x30FD
#घोषणा EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY 0x31BD
#घोषणा EGL_NO_RESET_NOTIFICATION         0x31BE
#घोषणा EGL_LOSE_CONTEXT_ON_RESET         0x31BF
#घोषणा EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT 0x00000001
#घोषणा EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT 0x00000002
#घोषणा EGL_CONTEXT_OPENGL_DEBUG          0x31B0
#घोषणा EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE 0x31B1
#घोषणा EGL_CONTEXT_OPENGL_ROBUST_ACCESS  0x31B2
#घोषणा EGL_OPENGL_ES3_BIT                0x00000040
#घोषणा EGL_CL_EVENT_HANDLE               0x309C
#घोषणा EGL_SYNC_CL_EVENT                 0x30FE
#घोषणा EGL_SYNC_CL_EVENT_COMPLETE        0x30FF
#घोषणा EGL_SYNC_PRIOR_COMMANDS_COMPLETE  0x30F0
#घोषणा EGL_SYNC_TYPE                     0x30F7
#घोषणा EGL_SYNC_STATUS                   0x30F1
#घोषणा EGL_SYNC_CONDITION                0x30F8
#घोषणा EGL_SIGNALED                      0x30F2
#घोषणा EGL_UNSIGNALED                    0x30F3
#घोषणा EGL_SYNC_FLUSH_COMMANDS_BIT       0x0001
#घोषणा EGL_FOREVER                       0xFFFFFFFFFFFFFFFFull
#घोषणा EGL_TIMEOUT_EXPIRED               0x30F5
#घोषणा EGL_CONDITION_SATISFIED           0x30F6
#घोषणा EGL_NO_SYNC                       EGL_CAST(EGLSync,0)
#घोषणा EGL_SYNC_FENCE                    0x30F9
#घोषणा EGL_GL_COLORSPACE                 0x309D
#घोषणा EGL_GL_COLORSPACE_SRGB            0x3089
#घोषणा EGL_GL_COLORSPACE_LINEAR          0x308A
#घोषणा EGL_GL_RENDERBUFFER               0x30B9
#घोषणा EGL_GL_TEXTURE_2D                 0x30B1
#घोषणा EGL_GL_TEXTURE_LEVEL              0x30BC
#घोषणा EGL_GL_TEXTURE_3D                 0x30B2
#घोषणा EGL_GL_TEXTURE_ZOFFSET            0x30BD
#घोषणा EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_X 0x30B3
#घोषणा EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_X 0x30B4
#घोषणा EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_Y 0x30B5
#घोषणा EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Y 0x30B6
#घोषणा EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_Z 0x30B7
#घोषणा EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 0x30B8
#घोषणा EGL_IMAGE_PRESERVED               0x30D2
#घोषणा EGL_NO_IMAGE                      EGL_CAST(EGLImage,0)
प्रकार EGLSync (EGLAPIENTRYP PFNEGLCREATESYNCPROC) (EGLDisplay dpy, EGLenum type, स्थिर EGLAttrib *attrib_list);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCPROC) (EGLDisplay dpy, EGLSync sync);
प्रकार EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCPROC) (EGLDisplay dpy, EGLSync sync, EGLint flags, EGLTime timeout);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLGETSYNCATTRIBPROC) (EGLDisplay dpy, EGLSync sync, EGLint attribute, EGLAttrib *मूल्य);
प्रकार EGLImage (EGLAPIENTRYP PFNEGLCREATEIMAGEPROC) (EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClient_बफर बफर_2, स्थिर EGLAttrib *attrib_list);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYIMAGEPROC) (EGLDisplay dpy, EGLImage image);
प्रकार EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYPROC) (EGLenum platform, व्योम *native_display, स्थिर EGLAttrib *attrib_list);
प्रकार EGLSurface (EGLAPIENTRYP PFNEGLCREATEPLATFORMWINDOWSURFACEPROC) (EGLDisplay dpy, EGLConfig config, व्योम *native_window, स्थिर EGLAttrib *attrib_list);
प्रकार EGLSurface (EGLAPIENTRYP PFNEGLCREATEPLATFORMPIXMAPSURFACEPROC) (EGLDisplay dpy, EGLConfig config, व्योम *native_pixmap, स्थिर EGLAttrib *attrib_list);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLWAITSYNCPROC) (EGLDisplay dpy, EGLSync sync, EGLint flags);
#अगर EGL_EGL_PROTOTYPES
EGLAPI EGLSync EGLAPIENTRY eglCreateSync (EGLDisplay dpy, EGLenum type, स्थिर EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySync (EGLDisplay dpy, EGLSync sync);
EGLAPI EGLint EGLAPIENTRY eglClientWaitSync (EGLDisplay dpy, EGLSync sync, EGLint flags, EGLTime timeout);
EGLAPI EGLBoolean EGLAPIENTRY eglGetSyncAttrib (EGLDisplay dpy, EGLSync sync, EGLint attribute, EGLAttrib *मूल्य);
EGLAPI EGLImage EGLAPIENTRY eglCreateImage (EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClient_बफर बफर_2, स्थिर EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyImage (EGLDisplay dpy, EGLImage image);
EGLAPI EGLDisplay EGLAPIENTRY eglGetPlatformDisplay (EGLenum platform, व्योम *native_display, स्थिर EGLAttrib *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePlatformWindowSurface (EGLDisplay dpy, EGLConfig config, व्योम *native_window, स्थिर EGLAttrib *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePlatformPixmapSurface (EGLDisplay dpy, EGLConfig config, व्योम *native_pixmap, स्थिर EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglWaitSync (EGLDisplay dpy, EGLSync sync, EGLint flags);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_VERSION_1_5 */

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर
