#यदि_अपरिभाषितम् __egl_h_
#परिभाषय __egl_h_ 1

#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः

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

#अन्तर्भाव <EGL/eglplatform.h>

#यदि_अपरिभाषितम् EGL_EGL_PROTOTYPES
#परिभाषय EGL_EGL_PROTOTYPES 1
#यदि_अन्तः

/* Generated on date 20260319 */

/* Generated C header for:
 * API: egl
 * Versions considered: .*
 * Versions emitted: .*
 * Default extensions included: None
 * Additional extensions included: _nomatch_^
 * Extensions removed: _nomatch_^
 */

#यदि_अपरिभाषितम् EGL_संस्करणम्_1_0
#परिभाषय EGL_संस्करणम्_1_0 1
प्रकारनिर्देश अचिह्नित पूर्णाङ्क EGLBoolean;
प्रकारनिर्देश शून्य *EGLDisplay;
#अन्तर्भाव <KHR/khrplatform.h>
#अन्तर्भाव <EGL/eglplatform.h>
प्रकारनिर्देश शून्य *EGLConfig;
प्रकारनिर्देश शून्य *EGLSurface;
प्रकारनिर्देश शून्य *EGLContext;
प्रकारनिर्देश शून्य (*__eglMustCastToProperFunctionPointerType)(शून्य);
#परिभाषय EGL_ALPHA_आकार                    0x3021
#परिभाषय EGL_BAD_ACCESS                    0x3002
#परिभाषय EGL_BAD_ALLOC                     0x3003
#परिभाषय EGL_BAD_ATTRIBUTE                 0x3004
#परिभाषय EGL_BAD_CONFIG                    0x3005
#परिभाषय EGL_BAD_CONTEXT                   0x3006
#परिभाषय EGL_BAD_CURRENT_SURFACE           0x3007
#परिभाषय EGL_BAD_DISPLAY                   0x3008
#परिभाषय EGL_BAD_मेलनम्                     0x3009
#परिभाषय EGL_BAD_NATIVE_PIXMAP             0x300A
#परिभाषय EGL_BAD_NATIVE_गवाक्षः             0x300B
#परिभाषय EGL_BAD_PARAMETER                 0x300C
#परिभाषय EGL_BAD_SURFACE                   0x300D
#परिभाषय EGL_BLUE_आकार                     0x3022
#परिभाषय EGL_बफर_आकार                   0x3020
#परिभाषय EGL_CONFIG_CAVEAT                 0x3027
#परिभाषय EGL_CONFIG_ID                     0x3028
#परिभाषय EGL_CORE_NATIVE_ENGINE            0x305B
#परिभाषय EGL_गभीरता_आकार                    0x3025
#परिभाषय EGL_DONT_CARE                     EGL_CAST(EGLint,-1)
#परिभाषय EGL_DRAW                          0x3059
#परिभाषय EGL_EXTENSIONS                    0x3055
#परिभाषय EGL_FALSE                         0
#परिभाषय EGL_GREEN_आकार                    0x3023
#परिभाषय EGL_HEIGHT                        0x3056
#परिभाषय EGL_LARGEST_PBUFFER               0x3058
#परिभाषय EGL_LEVEL                         0x3029
#परिभाषय EGL_MAX_PBUFFER_HEIGHT            0x302A
#परिभाषय EGL_MAX_PBUFFER_PIXELS            0x302B
#परिभाषय EGL_MAX_PBUFFER_विस्तारः             0x302C
#परिभाषय EGL_NATIVE_RENDERABLE             0x302D
#परिभाषय EGL_NATIVE_VISUAL_ID              0x302E
#परिभाषय EGL_NATIVE_VISUAL_TYPE            0x302F
#परिभाषय EGL_NONE                          0x3038
#परिभाषय EGL_NON_CONFORMANT_CONFIG         0x3051
#परिभाषय EGL_NOT_INITIALIZED               0x3001
#परिभाषय EGL_NO_CONTEXT                    EGL_CAST(EGLContext,0)
#परिभाषय EGL_NO_DISPLAY                    EGL_CAST(EGLDisplay,0)
#परिभाषय EGL_NO_SURFACE                    EGL_CAST(EGLSurface,0)
#परिभाषय EGL_PBUFFER_BIT                   0x0001
#परिभाषय EGL_PIXMAP_BIT                    0x0002
#परिभाषय EGL_READ                          0x305A
#परिभाषय EGL_RED_आकार                      0x3024
#परिभाषय EGL_SAMPLES                       0x3031
#परिभाषय EGL_SAMPLE_BUFFERS                0x3032
#परिभाषय EGL_SLOW_CONFIG                   0x3050
#परिभाषय EGL_STENCIL_आकार                  0x3026
#परिभाषय EGL_SUCCESS                       0x3000
#परिभाषय EGL_SURFACE_TYPE                  0x3033
#परिभाषय EGL_TRANSPARENT_BLUE_मानम्        0x3035
#परिभाषय EGL_TRANSPARENT_GREEN_मानम्       0x3036
#परिभाषय EGL_TRANSPARENT_RED_मानम्         0x3037
#परिभाषय EGL_TRANSPARENT_RGB               0x3052
#परिभाषय EGL_TRANSPARENT_TYPE              0x3034
#परिभाषय EGL_TRUE                          1
#परिभाषय EGL_VENDOR                        0x3053
#परिभाषय EGL_संस्करणम्                       0x3054
#परिभाषय EGL_विस्तारः                         0x3057
#परिभाषय EGL_गवाक्षः_BIT                    0x0004
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLCHOOSECONFIGPROC) (EGLDisplay dpy, ध्रुव EGLint *attrib_list, EGLConfig *configs, EGLint config_आकार, EGLint *अङ्कः_config);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLCOPYBUFFERSPROC) (EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType target);
प्रकारनिर्देश EGLContext (EGLAPIENTRYP PFNEGLCREATECONTEXTPROC) (EGLDisplay dpy, EGLConfig config, EGLContext share_context, ध्रुव EGLint *attrib_list);
प्रकारनिर्देश EGLSurface (EGLAPIENTRYP PFNEGLCREATEPBUFFERSURFACEPROC) (EGLDisplay dpy, EGLConfig config, ध्रुव EGLint *attrib_list);
प्रकारनिर्देश EGLSurface (EGLAPIENTRYP PFNEGLCREATEPIXMAPSURFACEPROC) (EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, ध्रुव EGLint *attrib_list);
प्रकारनिर्देश EGLSurface (EGLAPIENTRYP PFNEGLCREATEWINDOWSURFACEPROC) (EGLDisplay dpy, EGLConfig config, EGLNative_गवाक्षः_Type win, ध्रुव EGLint *attrib_list);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYCONTEXTPROC) (EGLDisplay dpy, EGLContext ctx);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSURFACEPROC) (EGLDisplay dpy, EGLSurface surface);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLGETCONFIGATTRIBPROC) (EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *मानम्);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLGETCONFIGSPROC) (EGLDisplay dpy, EGLConfig *configs, EGLint config_आकार, EGLint *अङ्कः_config);
प्रकारनिर्देश EGLDisplay (EGLAPIENTRYP PFNEGLGETCURRENTDISPLAYPROC) (शून्य);
प्रकारनिर्देश EGLSurface (EGLAPIENTRYP PFNEGLGETCURRENTSURFACEPROC) (EGLint readdraw);
प्रकारनिर्देश EGLDisplay (EGLAPIENTRYP PFNEGLGETDISPLAYPROC) (EGLNativeDisplayType display_id);
प्रकारनिर्देश EGLint (EGLAPIENTRYP PFNEGLGETERRORPROC) (शून्य);
प्रकारनिर्देश __eglMustCastToProperFunctionPointerType (EGLAPIENTRYP PFNEGLGETPROCADDRESSPROC) (ध्रुव वर्ण *procname);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLINITIALIZEPROC) (EGLDisplay dpy, EGLint *major, EGLint *minor);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLMAKECURRENTPROC) (EGLDisplay dpy, EGLSurface draw, EGLSurface पठ, EGLContext ctx);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLQUERYCONTEXTPROC) (EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint *मानम्);
प्रकारनिर्देश ध्रुव वर्ण *(EGLAPIENTRYP PFNEGLQUERYSTRINGPROC) (EGLDisplay dpy, EGLint name);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSURFACEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint *मानम्);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSPROC) (EGLDisplay dpy, EGLSurface surface);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLTERMINATEPROC) (EGLDisplay dpy);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLWAITGLPROC) (शून्य);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLWAITNATIVEPROC) (EGLint engine);
#यदि EGL_EGL_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_वृणु_Config (EGLDisplay dpy, ध्रुव EGLint *attrib_list, EGLConfig *configs, EGLint config_आकार, EGLint *अङ्कः_config);
EGLAPI EGLBoolean EGLAPIENTRY eglCopyBuffers (EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType target);
EGLAPI EGLContext EGLAPIENTRY eglCreateContext (EGLDisplay dpy, EGLConfig config, EGLContext share_context, ध्रुव EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePbufferSurface (EGLDisplay dpy, EGLConfig config, ध्रुव EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePixmapSurface (EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, ध्रुव EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY egl_Create_गवाक्षः_Surface (EGLDisplay dpy, EGLConfig config, EGLNative_गवाक्षः_Type win, ध्रुव EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyContext (EGLDisplay dpy, EGLContext ctx);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySurface (EGLDisplay dpy, EGLSurface surface);
EGLAPI EGLBoolean EGLAPIENTRY eglGetConfigAttrib (EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *मानम्);
EGLAPI EGLBoolean EGLAPIENTRY eglGetConfigs (EGLDisplay dpy, EGLConfig *configs, EGLint config_आकार, EGLint *अङ्कः_config);
EGLAPI EGLDisplay EGLAPIENTRY eglGetCurrentDisplay (शून्य);
EGLAPI EGLSurface EGLAPIENTRY eglGetCurrentSurface (EGLint readdraw);
EGLAPI EGLDisplay EGLAPIENTRY eglGetDisplay (EGLNativeDisplayType display_id);
EGLAPI EGLint EGLAPIENTRY eglGetError (शून्य);
EGLAPI __eglMustCastToProperFunctionPointerType EGLAPIENTRY egl_Get_Proc_स्थानाङ्कः (ध्रुव वर्ण *procname);
EGLAPI EGLBoolean EGLAPIENTRY eglInitialize (EGLDisplay dpy, EGLint *major, EGLint *minor);
EGLAPI EGLBoolean EGLAPIENTRY eglMakeCurrent (EGLDisplay dpy, EGLSurface draw, EGLSurface पठ, EGLContext ctx);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryContext (EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint *मानम्);
EGLAPI ध्रुव वर्ण *EGLAPIENTRY eglQueryString (EGLDisplay dpy, EGLint name);
EGLAPI EGLBoolean EGLAPIENTRY eglQuerySurface (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint *मानम्);
EGLAPI EGLBoolean EGLAPIENTRY eglSwapBuffers (EGLDisplay dpy, EGLSurface surface);
EGLAPI EGLBoolean EGLAPIENTRY eglTerminate (EGLDisplay dpy);
EGLAPI EGLBoolean EGLAPIENTRY eglWaitGL (शून्य);
EGLAPI EGLBoolean EGLAPIENTRY eglWaitNative (EGLint engine);
#यदि_अन्तः
#यदि_अन्तः /* EGL_VERSION_1_0 */

#यदि_अपरिभाषितम् EGL_संस्करणम्_1_1
#परिभाषय EGL_संस्करणम्_1_1 1
#परिभाषय EGL_पृष्ठभागः_बफर                   0x3084
#परिभाषय EGL_BIND_गन्तव्यम्_TEXTURE_RGB           0x3039
#परिभाषय EGL_BIND_गन्तव्यम्_TEXTURE_RGBA          0x303A
#परिभाषय EGL_CONTEXT_नष्टम्                  0x300E
#परिभाषय EGL_MIN_SWAP_INTERVAL             0x303B
#परिभाषय EGL_MAX_SWAP_INTERVAL             0x303C
#परिभाषय EGL_MIPMAP_TEXTURE                0x3082
#परिभाषय EGL_MIPMAP_LEVEL                  0x3083
#परिभाषय EGL_NO_TEXTURE                    0x305C
#परिभाषय EGL_TEXTURE_2D                    0x305F
#परिभाषय EGL_TEXTURE_FORMAT                0x3080
#परिभाषय EGL_TEXTURE_RGB                   0x305D
#परिभाषय EGL_TEXTURE_RGBA                  0x305E
#परिभाषय EGL_TEXTURE_TARGET                0x3081
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLBINDTEXIMAGEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint बफर_2);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLRELEASETEXIMAGEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint बफर_2);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLSURFACEATTRIBPROC) (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint मानम्);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLSWAPINTERVALPROC) (EGLDisplay dpy, EGLint interval);
#यदि EGL_EGL_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglBindTexImage (EGLDisplay dpy, EGLSurface surface, EGLint बफर_2);
EGLAPI EGLBoolean EGLAPIENTRY eglReleaseTexImage (EGLDisplay dpy, EGLSurface surface, EGLint बफर_2);
EGLAPI EGLBoolean EGLAPIENTRY eglSurfaceAttrib (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint मानम्);
EGLAPI EGLBoolean EGLAPIENTRY eglSwapInterval (EGLDisplay dpy, EGLint interval);
#यदि_अन्तः
#यदि_अन्तः /* EGL_VERSION_1_1 */

#यदि_अपरिभाषितम् EGL_संस्करणम्_1_2
#परिभाषय EGL_संस्करणम्_1_2 1
प्रकारनिर्देश अचिह्नित पूर्णाङ्क EGLenum;
प्रकारनिर्देश शून्य *EGLClient_बफर;
#परिभाषय EGL_ALPHA_FORMAT                  0x3088
#परिभाषय EGL_ALPHA_FORMAT_NONPRE           0x308B
#परिभाषय EGL_ALPHA_FORMAT_PRE              0x308C
#परिभाषय EGL_ALPHA_आवरणम्_आकार               0x303E
#परिभाषय EGL_बफर_PRESERVED              0x3094
#परिभाषय EGL_बफर_DESTROYED              0x3095
#परिभाषय EGL_CLIENT_APIS                   0x308D
#परिभाषय EGL_COLORSPACE                    0x3087
#परिभाषय EGL_COLORSPACE_sRGB               0x3089
#परिभाषय EGL_COLORSPACE_रैखिकम्             0x308A
#परिभाषय EGL_COLOR_बफर_TYPE             0x303F
#परिभाषय EGL_CONTEXT_CLIENT_TYPE           0x3097
#परिभाषय EGL_DISPLAY_SCALING               10000
#परिभाषय EGL_HORIZONTAL_RESOLUTION         0x3090
#परिभाषय EGL_LUMINANCE_बफर              0x308F
#परिभाषय EGL_LUMINANCE_आकार                0x303D
#परिभाषय EGL_OPENGL_ES_BIT                 0x0001
#परिभाषय EGL_OPENVG_BIT                    0x0002
#परिभाषय EGL_OPENGL_ES_API                 0x30A0
#परिभाषय EGL_OPENVG_API                    0x30A1
#परिभाषय EGL_OPENVG_IMAGE                  0x3096
#परिभाषय EGL_PIXEL_ASPECT_अनुपातः            0x3092
#परिभाषय EGL_RENDERABLE_TYPE               0x3040
#परिभाषय EGL_RENDER_बफर                 0x3086
#परिभाषय EGL_RGB_बफर                    0x308E
#परिभाषय EGL_SINGLE_बफर                 0x3085
#परिभाषय EGL_SWAP_BEHAVIOR                 0x3093
#परिभाषय EGL_UNKNOWN                       EGL_CAST(EGLint,-1)
#परिभाषय EGL_VERTICAL_RESOLUTION           0x3091
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLBINDAPIPROC) (EGLenum api);
प्रकारनिर्देश EGLenum (EGLAPIENTRYP PFNEGLQUERYAPIPROC) (शून्य);
प्रकारनिर्देश EGLSurface (EGLAPIENTRYP PFNEGLCREATEPBUFFERFROMCLIENTBUFFERPROC) (EGLDisplay dpy, EGLenum buftype, EGLClient_बफर बफर_2, EGLConfig config, ध्रुव EGLint *attrib_list);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLRELEASETHREADPROC) (शून्य);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLWAITCLIENTPROC) (शून्य);
#यदि EGL_EGL_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglBindAPI (EGLenum api);
EGLAPI EGLenum EGLAPIENTRY eglQueryAPI (शून्य);
EGLAPI EGLSurface EGLAPIENTRY egl_Create_Pbuffer_From_Client_बफर (EGLDisplay dpy, EGLenum buftype, EGLClient_बफर बफर_2, EGLConfig config, ध्रुव EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglReleaseThread (शून्य);
EGLAPI EGLBoolean EGLAPIENTRY eglWaitClient (शून्य);
#यदि_अन्तः
#यदि_अन्तः /* EGL_VERSION_1_2 */

#यदि_अपरिभाषितम् EGL_संस्करणम्_1_3
#परिभाषय EGL_संस्करणम्_1_3 1
#परिभाषय EGL_CONFORMANT                    0x3042
#परिभाषय EGL_CONTEXT_CLIENT_संस्करणम्        0x3098
#परिभाषय EGL_मेलनम्_NATIVE_PIXMAP           0x3041
#परिभाषय EGL_OPENGL_ES2_BIT                0x0004
#परिभाषय EGL_VG_ALPHA_FORMAT               0x3088
#परिभाषय EGL_VG_ALPHA_FORMAT_NONPRE        0x308B
#परिभाषय EGL_VG_ALPHA_FORMAT_PRE           0x308C
#परिभाषय EGL_VG_ALPHA_FORMAT_PRE_BIT       0x0040
#परिभाषय EGL_VG_COLORSPACE                 0x3087
#परिभाषय EGL_VG_COLORSPACE_sRGB            0x3089
#परिभाषय EGL_VG_COLORSPACE_रैखिकम्          0x308A
#परिभाषय EGL_VG_COLORSPACE_रैखिकम्_BIT      0x0020
#यदि_अन्तः /* EGL_VERSION_1_3 */

#यदि_अपरिभाषितम् EGL_संस्करणम्_1_4
#परिभाषय EGL_संस्करणम्_1_4 1
#परिभाषय EGL_DEFAULT_DISPLAY               EGL_CAST(EGLNativeDisplayType,0)
#परिभाषय EGL_MULTISAMPLE_RESOLVE_BOX_BIT   0x0200
#परिभाषय EGL_MULTISAMPLE_RESOLVE           0x3099
#परिभाषय EGL_MULTISAMPLE_RESOLVE_DEFAULT   0x309A
#परिभाषय EGL_MULTISAMPLE_RESOLVE_BOX       0x309B
#परिभाषय EGL_OPENGL_API                    0x30A2
#परिभाषय EGL_OPENGL_BIT                    0x0008
#परिभाषय EGL_SWAP_BEHAVIOR_PRESERVED_BIT   0x0400
प्रकारनिर्देश EGLContext (EGLAPIENTRYP PFNEGLGETCURRENTCONTEXTPROC) (शून्य);
#यदि EGL_EGL_PROTOTYPES
EGLAPI EGLContext EGLAPIENTRY eglGetCurrentContext (शून्य);
#यदि_अन्तः
#यदि_अन्तः /* EGL_VERSION_1_4 */

#यदि_अपरिभाषितम् EGL_संस्करणम्_1_5
#परिभाषय EGL_संस्करणम्_1_5 1
प्रकारनिर्देश शून्य *EGLSync;
प्रकारनिर्देश intptr_t EGLAttrib;
प्रकारनिर्देश khronos_utime_nanoseconds_t EGLTime;
प्रकारनिर्देश शून्य *EGLImage;
#परिभाषय EGL_CONTEXT_MAJOR_संस्करणम्         0x3098
#परिभाषय EGL_CONTEXT_MINOR_संस्करणम्         0x30FB
#परिभाषय EGL_CONTEXT_OPENGL_PROFILE_आवरणम्   0x30FD
#परिभाषय EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY 0x31BD
#परिभाषय EGL_NO_RESET_NOTIFICATION         0x31BE
#परिभाषय EGL_LOSE_CONTEXT_ON_RESET         0x31BF
#परिभाषय EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT 0x00000001
#परिभाषय EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT 0x00000002
#परिभाषय EGL_CONTEXT_OPENGL_DEBUG          0x31B0
#परिभाषय EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE 0x31B1
#परिभाषय EGL_CONTEXT_OPENGL_ROBUST_ACCESS  0x31B2
#परिभाषय EGL_OPENGL_ES3_BIT                0x00000040
#परिभाषय EGL_CL_EVENT_HANDLE               0x309C
#परिभाषय EGL_SYNC_CL_EVENT                 0x30FE
#परिभाषय EGL_SYNC_CL_EVENT_COMPLETE        0x30FF
#परिभाषय EGL_SYNC_प्राक्_COMMANDS_COMPLETE  0x30F0
#परिभाषय EGL_SYNC_TYPE                     0x30F7
#परिभाषय EGL_SYNC_स्थितिः                   0x30F1
#परिभाषय EGL_SYNC_CONDITION                0x30F8
#परिभाषय EGL_SIGNALED                      0x30F2
#परिभाषय EGL_UNSIGNALED                    0x30F3
#परिभाषय EGL_SYNC_FLUSH_COMMANDS_BIT       0x0001
#परिभाषय EGL_FOREVER                       0xFFFFFFFFFFFFFFFFull
#परिभाषय EGL_TIMEOUT_EXPIRED               0x30F5
#परिभाषय EGL_CONDITION_SATISFIED           0x30F6
#परिभाषय EGL_NO_SYNC                       EGL_CAST(EGLSync,0)
#परिभाषय EGL_SYNC_FENCE                    0x30F9
#परिभाषय EGL_GL_COLORSPACE                 0x309D
#परिभाषय EGL_GL_COLORSPACE_SRGB            0x3089
#परिभाषय EGL_GL_COLORSPACE_रैखिकम्          0x308A
#परिभाषय EGL_GL_RENDERBUFFER               0x30B9
#परिभाषय EGL_GL_TEXTURE_2D                 0x30B1
#परिभाषय EGL_GL_TEXTURE_LEVEL              0x30BC
#परिभाषय EGL_GL_TEXTURE_3D                 0x30B2
#परिभाषय EGL_GL_TEXTURE_ZOFFSET            0x30BD
#परिभाषय EGL_GL_TEXTURE_CUBE_MAP_धनात्मकम्_X 0x30B3
#परिभाषय EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_X 0x30B4
#परिभाषय EGL_GL_TEXTURE_CUBE_MAP_धनात्मकम्_Y 0x30B5
#परिभाषय EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Y 0x30B6
#परिभाषय EGL_GL_TEXTURE_CUBE_MAP_धनात्मकम्_Z 0x30B7
#परिभाषय EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 0x30B8
#परिभाषय EGL_IMAGE_PRESERVED               0x30D2
#परिभाषय EGL_NO_IMAGE                      EGL_CAST(EGLImage,0)
प्रकारनिर्देश EGLSync (EGLAPIENTRYP PFNEGLCREATESYNCPROC) (EGLDisplay dpy, EGLenum type, ध्रुव EGLAttrib *attrib_list);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCPROC) (EGLDisplay dpy, EGLSync sync);
प्रकारनिर्देश EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCPROC) (EGLDisplay dpy, EGLSync sync, EGLint flags, EGLTime timeout);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLGETSYNCATTRIBPROC) (EGLDisplay dpy, EGLSync sync, EGLint attribute, EGLAttrib *मानम्);
प्रकारनिर्देश EGLImage (EGLAPIENTRYP PFNEGLCREATEIMAGEPROC) (EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClient_बफर बफर_2, ध्रुव EGLAttrib *attrib_list);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYIMAGEPROC) (EGLDisplay dpy, EGLImage image);
प्रकारनिर्देश EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYPROC) (EGLenum platform, शून्य *native_display, ध्रुव EGLAttrib *attrib_list);
प्रकारनिर्देश EGLSurface (EGLAPIENTRYP PFNEGLCREATEPLATFORMWINDOWSURFACEPROC) (EGLDisplay dpy, EGLConfig config, शून्य *native_गवाक्षः, ध्रुव EGLAttrib *attrib_list);
प्रकारनिर्देश EGLSurface (EGLAPIENTRYP PFNEGLCREATEPLATFORMPIXMAPSURFACEPROC) (EGLDisplay dpy, EGLConfig config, शून्य *native_pixmap, ध्रुव EGLAttrib *attrib_list);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLWAITSYNCPROC) (EGLDisplay dpy, EGLSync sync, EGLint flags);
#यदि EGL_EGL_PROTOTYPES
EGLAPI EGLSync EGLAPIENTRY eglCreateSync (EGLDisplay dpy, EGLenum type, ध्रुव EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySync (EGLDisplay dpy, EGLSync sync);
EGLAPI EGLint EGLAPIENTRY eglClientWaitSync (EGLDisplay dpy, EGLSync sync, EGLint flags, EGLTime timeout);
EGLAPI EGLBoolean EGLAPIENTRY eglGetSyncAttrib (EGLDisplay dpy, EGLSync sync, EGLint attribute, EGLAttrib *मानम्);
EGLAPI EGLImage EGLAPIENTRY eglCreateImage (EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClient_बफर बफर_2, ध्रुव EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyImage (EGLDisplay dpy, EGLImage image);
EGLAPI EGLDisplay EGLAPIENTRY eglGetPlatformDisplay (EGLenum platform, शून्य *native_display, ध्रुव EGLAttrib *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY egl_Create_Platform_गवाक्षः_Surface (EGLDisplay dpy, EGLConfig config, शून्य *native_गवाक्षः, ध्रुव EGLAttrib *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePlatformPixmapSurface (EGLDisplay dpy, EGLConfig config, शून्य *native_pixmap, ध्रुव EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglWaitSync (EGLDisplay dpy, EGLSync sync, EGLint flags);
#यदि_अन्तः
#यदि_अन्तः /* EGL_VERSION_1_5 */

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः
