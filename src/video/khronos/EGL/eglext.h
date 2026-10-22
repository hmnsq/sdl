#यदि_अपरिभाषितम् __eglext_h_
#परिभाषय __eglext_h_ 1

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

#परिभाषय EGL_EGLEXT_संस्करणम् 20260319

/* Generated C header for:
 * API: egl
 * Versions considered: .*
 * Versions emitted: _nomatch_^
 * Default extensions included: egl
 * Additional extensions included: _nomatch_^
 * Extensions removed: _nomatch_^
 */

#यदि_अपरिभाषितम् EGL_KHR_cl_event
#परिभाषय EGL_KHR_cl_event 1
#परिभाषय EGL_CL_EVENT_HANDLE_KHR           0x309C
#परिभाषय EGL_SYNC_CL_EVENT_KHR             0x30FE
#परिभाषय EGL_SYNC_CL_EVENT_COMPLETE_KHR    0x30FF
#यदि_अन्तः /* EGL_KHR_cl_event */

#यदि_अपरिभाषितम् EGL_KHR_cl_event2
#परिभाषय EGL_KHR_cl_event2 1
प्रकारनिर्देश शून्य *EGLSyncKHR;
प्रकारनिर्देश intptr_t EGLAttribKHR;
प्रकारनिर्देश EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESYNC64KHRPROC) (EGLDisplay dpy, EGLenum type, ध्रुव EGLAttribKHR *attrib_list);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncKHR EGLAPIENTRY eglCreateSync64KHR (EGLDisplay dpy, EGLenum type, ध्रुव EGLAttribKHR *attrib_list);
#यदि_अन्तः
#यदि_अन्तः /* EGL_KHR_cl_event2 */

#यदि_अपरिभाषितम् EGL_KHR_client_get_all_proc_स्थानाङ्काः
#परिभाषय EGL_KHR_client_get_all_proc_स्थानाङ्काः 1
#यदि_अन्तः /* EGL_KHR_client_get_all_proc_addresses */

#यदि_अपरिभाषितम् EGL_KHR_config_attribs
#परिभाषय EGL_KHR_config_attribs 1
#परिभाषय EGL_CONFORMANT_KHR                0x3042
#परिभाषय EGL_VG_COLORSPACE_रैखिकम्_BIT_KHR  0x0020
#परिभाषय EGL_VG_ALPHA_FORMAT_PRE_BIT_KHR   0x0040
#यदि_अन्तः /* EGL_KHR_config_attribs */

#यदि_अपरिभाषितम् EGL_KHR_context_flush_control
#परिभाषय EGL_KHR_context_flush_control 1
#परिभाषय EGL_CONTEXT_RELEASE_BEHAVIOR_NONE_KHR 0
#परिभाषय EGL_CONTEXT_RELEASE_BEHAVIOR_KHR  0x2097
#परिभाषय EGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_KHR 0x2098
#यदि_अन्तः /* EGL_KHR_context_flush_control */

#यदि_अपरिभाषितम् EGL_KHR_create_context
#परिभाषय EGL_KHR_create_context 1
#परिभाषय EGL_CONTEXT_MAJOR_संस्करणम्_KHR     0x3098
#परिभाषय EGL_CONTEXT_MINOR_संस्करणम्_KHR     0x30FB
#परिभाषय EGL_CONTEXT_FLAGS_KHR             0x30FC
#परिभाषय EGL_CONTEXT_OPENGL_PROFILE_आवरणम्_KHR 0x30FD
#परिभाषय EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_KHR 0x31BD
#परिभाषय EGL_NO_RESET_NOTIFICATION_KHR     0x31BE
#परिभाषय EGL_LOSE_CONTEXT_ON_RESET_KHR     0x31BF
#परिभाषय EGL_CONTEXT_OPENGL_DEBUG_BIT_KHR  0x00000001
#परिभाषय EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR 0x00000002
#परिभाषय EGL_CONTEXT_OPENGL_ROBUST_ACCESS_BIT_KHR 0x00000004
#परिभाषय EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR 0x00000001
#परिभाषय EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR 0x00000002
#परिभाषय EGL_OPENGL_ES3_BIT_KHR            0x00000040
#यदि_अन्तः /* EGL_KHR_create_context */

#यदि_अपरिभाषितम् EGL_KHR_create_context_no_error
#परिभाषय EGL_KHR_create_context_no_error 1
#परिभाषय EGL_CONTEXT_OPENGL_NO_ERROR_KHR   0x31B3
#यदि_अन्तः /* EGL_KHR_create_context_no_error */

#यदि_अपरिभाषितम् EGL_KHR_debug
#परिभाषय EGL_KHR_debug 1
प्रकारनिर्देश शून्य *EGLLabelKHR;
प्रकारनिर्देश शून्य *EGLObjectKHR;
प्रकारनिर्देश शून्य (EGLAPIENTRY  *EGLDEBUGPROCKHR)(EGLenum error,ध्रुव वर्ण *command,EGLint सन्देशः_Type,EGLLabelKHR threadLabel,EGLLabelKHR objectLabel,ध्रुव वर्ण* सन्देशः);
#परिभाषय EGL_OBJECT_THREAD_KHR             0x33B0
#परिभाषय EGL_OBJECT_DISPLAY_KHR            0x33B1
#परिभाषय EGL_OBJECT_CONTEXT_KHR            0x33B2
#परिभाषय EGL_OBJECT_SURFACE_KHR            0x33B3
#परिभाषय EGL_OBJECT_IMAGE_KHR              0x33B4
#परिभाषय EGL_OBJECT_SYNC_KHR               0x33B5
#परिभाषय EGL_OBJECT_प्रवाहः_KHR             0x33B6
#परिभाषय EGL_DEBUG_सन्देशः_CRITICAL_KHR        0x33B9
#परिभाषय EGL_DEBUG_सन्देशः_ERROR_KHR           0x33BA
#परिभाषय EGL_DEBUG_सन्देशः_WARN_KHR            0x33BB
#परिभाषय EGL_DEBUG_सन्देशः_INFO_KHR            0x33BC
#परिभाषय EGL_DEBUG_CALLBACK_KHR            0x33B8
प्रकारनिर्देश EGLint (EGLAPIENTRYP PFNEGLDEBUGMESSAGECONTROLKHRPROC) (EGLDEBUGPROCKHR callback, ध्रुव EGLAttrib *attrib_list);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEBUGKHRPROC) (EGLint attribute, EGLAttrib *मानम्);
प्रकारनिर्देश EGLint (EGLAPIENTRYP PFNEGLLABELOBJECTKHRPROC) (EGLDisplay display, EGLenum objectType, EGLObjectKHR object, EGLLabelKHR label);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLint EGLAPIENTRY egl_Debug_सन्देशः_Control_KHR (EGLDEBUGPROCKHR callback, ध्रुव EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDebugKHR (EGLint attribute, EGLAttrib *मानम्);
EGLAPI EGLint EGLAPIENTRY eglLabelObjectKHR (EGLDisplay display, EGLenum objectType, EGLObjectKHR object, EGLLabelKHR label);
#यदि_अन्तः
#यदि_अन्तः /* EGL_KHR_debug */

#यदि_अपरिभाषितम् EGL_KHR_display_reference
#परिभाषय EGL_KHR_display_reference 1
#परिभाषय EGL_TRACK_REFERENCES_KHR          0x3352
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDISPLAYATTRIBKHRPROC) (EGLDisplay dpy, EGLint name, EGLAttrib *मानम्);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDisplayAttribKHR (EGLDisplay dpy, EGLint name, EGLAttrib *मानम्);
#यदि_अन्तः
#यदि_अन्तः /* EGL_KHR_display_reference */

#यदि_अपरिभाषितम् EGL_KHR_fence_sync
#परिभाषय EGL_KHR_fence_sync 1
प्रकारनिर्देश khronos_utime_nanoseconds_t EGLTimeKHR;
#यदि_परिभाषितम् KHRONOS_SUPPORT_INT64
#परिभाषय EGL_SYNC_प्राक्_COMMANDS_COMPLETE_KHR 0x30F0
#परिभाषय EGL_SYNC_CONDITION_KHR            0x30F8
#परिभाषय EGL_SYNC_FENCE_KHR                0x30F9
प्रकारनिर्देश EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESYNCKHRPROC) (EGLDisplay dpy, EGLenum type, ध्रुव EGLint *attrib_list);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync);
प्रकारनिर्देश EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLGETSYNCATTRIBKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint attribute, EGLint *मानम्);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncKHR EGLAPIENTRY eglCreateSyncKHR (EGLDisplay dpy, EGLenum type, ध्रुव EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySyncKHR (EGLDisplay dpy, EGLSyncKHR sync);
EGLAPI EGLint EGLAPIENTRY eglClientWaitSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);
EGLAPI EGLBoolean EGLAPIENTRY eglGetSyncAttribKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint attribute, EGLint *मानम्);
#यदि_अन्तः
#यदि_अन्तः /* KHRONOS_SUPPORT_INT64 */
#यदि_अन्तः /* EGL_KHR_fence_sync */

#यदि_अपरिभाषितम् EGL_KHR_get_all_proc_स्थानाङ्काः
#परिभाषय EGL_KHR_get_all_proc_स्थानाङ्काः 1
#यदि_अन्तः /* EGL_KHR_get_all_proc_addresses */

#यदि_अपरिभाषितम् EGL_KHR_gl_colorspace
#परिभाषय EGL_KHR_gl_colorspace 1
#परिभाषय EGL_GL_COLORSPACE_KHR             0x309D
#परिभाषय EGL_GL_COLORSPACE_SRGB_KHR        0x3089
#परिभाषय EGL_GL_COLORSPACE_रैखिकम्_KHR      0x308A
#यदि_अन्तः /* EGL_KHR_gl_colorspace */

#यदि_अपरिभाषितम् EGL_KHR_gl_renderbuffer_image
#परिभाषय EGL_KHR_gl_renderbuffer_image 1
#परिभाषय EGL_GL_RENDERBUFFER_KHR           0x30B9
#यदि_अन्तः /* EGL_KHR_gl_renderbuffer_image */

#यदि_अपरिभाषितम् EGL_KHR_gl_texture_2D_image
#परिभाषय EGL_KHR_gl_texture_2D_image 1
#परिभाषय EGL_GL_TEXTURE_2D_KHR             0x30B1
#परिभाषय EGL_GL_TEXTURE_LEVEL_KHR          0x30BC
#यदि_अन्तः /* EGL_KHR_gl_texture_2D_image */

#यदि_अपरिभाषितम् EGL_KHR_gl_texture_3D_image
#परिभाषय EGL_KHR_gl_texture_3D_image 1
#परिभाषय EGL_GL_TEXTURE_3D_KHR             0x30B2
#परिभाषय EGL_GL_TEXTURE_ZOFFSET_KHR        0x30BD
#यदि_अन्तः /* EGL_KHR_gl_texture_3D_image */

#यदि_अपरिभाषितम् EGL_KHR_gl_texture_cubemap_image
#परिभाषय EGL_KHR_gl_texture_cubemap_image 1
#परिभाषय EGL_GL_TEXTURE_CUBE_MAP_धनात्मकम्_X_KHR 0x30B3
#परिभाषय EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_X_KHR 0x30B4
#परिभाषय EGL_GL_TEXTURE_CUBE_MAP_धनात्मकम्_Y_KHR 0x30B5
#परिभाषय EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_KHR 0x30B6
#परिभाषय EGL_GL_TEXTURE_CUBE_MAP_धनात्मकम्_Z_KHR 0x30B7
#परिभाषय EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_KHR 0x30B8
#यदि_अन्तः /* EGL_KHR_gl_texture_cubemap_image */

#यदि_अपरिभाषितम् EGL_KHR_image
#परिभाषय EGL_KHR_image 1
प्रकारनिर्देश शून्य *EGLImageKHR;
#परिभाषय EGL_NATIVE_PIXMAP_KHR             0x30B0
#परिभाषय EGL_NO_IMAGE_KHR                  EGL_CAST(EGLImageKHR,0)
प्रकारनिर्देश EGLImageKHR (EGLAPIENTRYP PFNEGLCREATEIMAGEKHRPROC) (EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClient_बफर बफर_2, ध्रुव EGLint *attrib_list);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYIMAGEKHRPROC) (EGLDisplay dpy, EGLImageKHR image);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLImageKHR EGLAPIENTRY eglCreateImageKHR (EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClient_बफर बफर_2, ध्रुव EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyImageKHR (EGLDisplay dpy, EGLImageKHR image);
#यदि_अन्तः
#यदि_अन्तः /* EGL_KHR_image */

#यदि_अपरिभाषितम् EGL_KHR_image_आधारः
#परिभाषय EGL_KHR_image_आधारः 1
#परिभाषय EGL_IMAGE_PRESERVED_KHR           0x30D2
#यदि_अन्तः /* EGL_KHR_image_base */

#यदि_अपरिभाषितम् EGL_KHR_image_pixmap
#परिभाषय EGL_KHR_image_pixmap 1
#यदि_अन्तः /* EGL_KHR_image_pixmap */

#यदि_अपरिभाषितम् EGL_KHR_तालकम्_surface
#परिभाषय EGL_KHR_तालकम्_surface 1
#परिभाषय EGL_READ_SURFACE_BIT_KHR          0x0001
#परिभाषय EGL_WRITE_SURFACE_BIT_KHR         0x0002
#परिभाषय EGL_तालकम्_SURFACE_BIT_KHR          0x0080
#परिभाषय EGL_OPTIMAL_FORMAT_BIT_KHR        0x0100
#परिभाषय EGL_मेलनम्_FORMAT_KHR              0x3043
#परिभाषय EGL_FORMAT_RGB_565_EXACT_KHR      0x30C0
#परिभाषय EGL_FORMAT_RGB_565_KHR            0x30C1
#परिभाषय EGL_FORMAT_RGBA_8888_EXACT_KHR    0x30C2
#परिभाषय EGL_FORMAT_RGBA_8888_KHR          0x30C3
#परिभाषय EGL_MAP_PRESERVE_PIXELS_KHR       0x30C4
#परिभाषय EGL_तालकम्_USAGE_HINT_KHR           0x30C5
#परिभाषय EGL_BITMAP_POINTER_KHR            0x30C6
#परिभाषय EGL_BITMAP_PITCH_KHR              0x30C7
#परिभाषय EGL_BITMAP_ORIGIN_KHR             0x30C8
#परिभाषय EGL_BITMAP_PIXEL_RED_विस्थापनम्_KHR   0x30C9
#परिभाषय EGL_BITMAP_PIXEL_GREEN_विस्थापनम्_KHR 0x30CA
#परिभाषय EGL_BITMAP_PIXEL_BLUE_विस्थापनम्_KHR  0x30CB
#परिभाषय EGL_BITMAP_PIXEL_ALPHA_विस्थापनम्_KHR 0x30CC
#परिभाषय EGL_BITMAP_PIXEL_LUMINANCE_विस्थापनम्_KHR 0x30CD
#परिभाषय EGL_अधस्तनम्_वामः_KHR                0x30CE
#परिभाषय EGL_ऊर्ध्वस्थम्_वामः_KHR                0x30CF
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLLOCKSURFACEKHRPROC) (EGLDisplay dpy, EGLSurface surface, ध्रुव EGLint *attrib_list);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLUNLOCKSURFACEKHRPROC) (EGLDisplay dpy, EGLSurface surface);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_तालकम्_Surface_KHR (EGLDisplay dpy, EGLSurface surface, ध्रुव EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglUnlockSurfaceKHR (EGLDisplay dpy, EGLSurface surface);
#यदि_अन्तः
#यदि_अन्तः /* EGL_KHR_lock_surface */

#यदि_अपरिभाषितम् EGL_KHR_तालकम्_surface2
#परिभाषय EGL_KHR_तालकम्_surface2 1
#परिभाषय EGL_BITMAP_PIXEL_आकार_KHR         0x3110
#यदि_अन्तः /* EGL_KHR_lock_surface2 */

#यदि_अपरिभाषितम् EGL_KHR_तालकम्_surface3
#परिभाषय EGL_KHR_तालकम्_surface3 1
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSURFACE64KHRPROC) (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLAttribKHR *मानम्);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQuerySurface64KHR (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLAttribKHR *मानम्);
#यदि_अन्तः
#यदि_अन्तः /* EGL_KHR_lock_surface3 */

#यदि_अपरिभाषितम् EGL_KHR_mutable_render_बफर
#परिभाषय EGL_KHR_mutable_render_बफर 1
#परिभाषय EGL_MUTABLE_RENDER_बफर_BIT_KHR 0x1000
#यदि_अन्तः /* EGL_KHR_mutable_render_buffer */

#यदि_अपरिभाषितम् EGL_KHR_no_config_context
#परिभाषय EGL_KHR_no_config_context 1
#परिभाषय EGL_NO_CONFIG_KHR                 EGL_CAST(EGLConfig,0)
#यदि_अन्तः /* EGL_KHR_no_config_context */

#यदि_अपरिभाषितम् EGL_KHR_partial_update
#परिभाषय EGL_KHR_partial_update 1
#परिभाषय EGL_बफर_AGE_KHR                0x313D
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLSETDAMAGEREGIONKHRPROC) (EGLDisplay dpy, EGLSurface surface, EGLint *rects, EGLint n_rects);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_समुच्चयः_Damage_Region_KHR (EGLDisplay dpy, EGLSurface surface, EGLint *rects, EGLint n_rects);
#यदि_अन्तः
#यदि_अन्तः /* EGL_KHR_partial_update */

#यदि_अपरिभाषितम् EGL_KHR_platform_android
#परिभाषय EGL_KHR_platform_android 1
#परिभाषय EGL_PLATFORM_ANDROID_KHR          0x3141
#यदि_अन्तः /* EGL_KHR_platform_android */

#यदि_अपरिभाषितम् EGL_KHR_platform_gbm
#परिभाषय EGL_KHR_platform_gbm 1
#परिभाषय EGL_PLATFORM_GBM_KHR              0x31D7
#यदि_अन्तः /* EGL_KHR_platform_gbm */

#यदि_अपरिभाषितम् EGL_KHR_platform_wayland
#परिभाषय EGL_KHR_platform_wayland 1
#परिभाषय EGL_PLATFORM_WAYLAND_KHR          0x31D8
#यदि_अन्तः /* EGL_KHR_platform_wayland */

#यदि_अपरिभाषितम् EGL_KHR_platform_x11
#परिभाषय EGL_KHR_platform_x11 1
#परिभाषय EGL_PLATFORM_X11_KHR              0x31D5
#परिभाषय EGL_PLATFORM_X11_SCREEN_KHR       0x31D6
#यदि_अन्तः /* EGL_KHR_platform_x11 */

#यदि_अपरिभाषितम् EGL_KHR_reusable_sync
#परिभाषय EGL_KHR_reusable_sync 1
#यदि_परिभाषितम् KHRONOS_SUPPORT_INT64
#परिभाषय EGL_SYNC_स्थितिः_KHR               0x30F1
#परिभाषय EGL_SIGNALED_KHR                  0x30F2
#परिभाषय EGL_UNSIGNALED_KHR                0x30F3
#परिभाषय EGL_TIMEOUT_EXPIRED_KHR           0x30F5
#परिभाषय EGL_CONDITION_SATISFIED_KHR       0x30F6
#परिभाषय EGL_SYNC_TYPE_KHR                 0x30F7
#परिभाषय EGL_SYNC_REUSABLE_KHR             0x30FA
#परिभाषय EGL_SYNC_FLUSH_COMMANDS_BIT_KHR   0x0001
#परिभाषय EGL_FOREVER_KHR                   0xFFFFFFFFFFFFFFFFull
#परिभाषय EGL_NO_SYNC_KHR                   EGL_CAST(EGLSyncKHR,0)
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLSIGNALSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLenum बहुलकम्);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglSignalSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLenum बहुलकम्);
#यदि_अन्तः
#यदि_अन्तः /* KHRONOS_SUPPORT_INT64 */
#यदि_अन्तः /* EGL_KHR_reusable_sync */

#यदि_अपरिभाषितम् EGL_KHR_प्रवाहः
#परिभाषय EGL_KHR_प्रवाहः 1
प्रकारनिर्देश शून्य *EGLStreamKHR;
प्रकारनिर्देश khronos_uint64_t EGLuint64KHR;
#यदि_परिभाषितम् KHRONOS_SUPPORT_INT64
#परिभाषय EGL_NO_प्रवाहः_KHR                 EGL_CAST(EGLStreamKHR,0)
#परिभाषय EGL_उपभोक्ता_LATENCY_USEC_KHR     0x3210
#परिभाषय EGL_उत्पादकः_FRAME_KHR            0x3212
#परिभाषय EGL_उपभोक्ता_FRAME_KHR            0x3213
#परिभाषय EGL_प्रवाहः_STATE_KHR              0x3214
#परिभाषय EGL_प्रवाहः_STATE_CREATED_KHR      0x3215
#परिभाषय EGL_प्रवाहः_STATE_CONNECTING_KHR   0x3216
#परिभाषय EGL_प्रवाहः_STATE_रिक्तानि_KHR        0x3217
#परिभाषय EGL_प्रवाहः_STATE_NEW_FRAME_उपलब्धम्_KHR 0x3218
#परिभाषय EGL_प्रवाहः_STATE_OLD_FRAME_उपलब्धम्_KHR 0x3219
#परिभाषय EGL_प्रवाहः_STATE_DISCONNECTED_KHR 0x321A
#परिभाषय EGL_BAD_प्रवाहः_KHR                0x321B
#परिभाषय EGL_BAD_STATE_KHR                 0x321C
प्रकारनिर्देश EGLStreamKHR (EGLAPIENTRYP PFNEGLCREATESTREAMKHRPROC) (EGLDisplay dpy, ध्रुव EGLint *attrib_list);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSTREAMKHRPROC) (EGLDisplay dpy, EGLStreamKHR प्रवाहः);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR प्रवाहः, EGLenum attribute, EGLint मानम्);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMKHRPROC) (EGLDisplay dpy, EGLStreamKHR प्रवाहः, EGLenum attribute, EGLint *मानम्);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMU64KHRPROC) (EGLDisplay dpy, EGLStreamKHR प्रवाहः, EGLenum attribute, EGLuint64KHR *मानम्);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLStreamKHR EGLAPIENTRY egl_Create_प्रवाहः_KHR (EGLDisplay dpy, ध्रुव EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY egl_Destroy_प्रवाहः_KHR (EGLDisplay dpy, EGLStreamKHR प्रवाहः);
EGLAPI EGLBoolean EGLAPIENTRY egl_प्रवाहः_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR प्रवाहः, EGLenum attribute, EGLint मानम्);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_प्रवाहः_KHR (EGLDisplay dpy, EGLStreamKHR प्रवाहः, EGLenum attribute, EGLint *मानम्);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryStreamu64KHR (EGLDisplay dpy, EGLStreamKHR प्रवाहः, EGLenum attribute, EGLuint64KHR *मानम्);
#यदि_अन्तः
#यदि_अन्तः /* KHRONOS_SUPPORT_INT64 */
#यदि_अन्तः /* EGL_KHR_stream */

#यदि_अपरिभाषितम् EGL_KHR_प्रवाहः_attrib
#परिभाषय EGL_KHR_प्रवाहः_attrib 1
#यदि_परिभाषितम् KHRONOS_SUPPORT_INT64
प्रकारनिर्देश EGLStreamKHR (EGLAPIENTRYP PFNEGLCREATESTREAMATTRIBKHRPROC) (EGLDisplay dpy, ध्रुव EGLAttrib *attrib_list);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLSETSTREAMATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR प्रवाहः, EGLenum attribute, EGLAttrib मानम्);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR प्रवाहः, EGLenum attribute, EGLAttrib *मानम्);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERACQUIREATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR प्रवाहः, ध्रुव EGLAttrib *attrib_list);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERRELEASEATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR प्रवाहः, ध्रुव EGLAttrib *attrib_list);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLStreamKHR EGLAPIENTRY egl_Create_प्रवाहः_Attrib_KHR (EGLDisplay dpy, ध्रुव EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY egl_समुच्चयः_प्रवाहः_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR प्रवाहः, EGLenum attribute, EGLAttrib मानम्);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_प्रवाहः_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR प्रवाहः, EGLenum attribute, EGLAttrib *मानम्);
EGLAPI EGLBoolean EGLAPIENTRY egl_प्रवाहः_उपभोक्ता_Acquire_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR प्रवाहः, ध्रुव EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY egl_प्रवाहः_उपभोक्ता_Release_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR प्रवाहः, ध्रुव EGLAttrib *attrib_list);
#यदि_अन्तः
#यदि_अन्तः /* KHRONOS_SUPPORT_INT64 */
#यदि_अन्तः /* EGL_KHR_stream_attrib */

#यदि_अपरिभाषितम् EGL_KHR_प्रवाहः_उपभोक्ता_gltexture
#परिभाषय EGL_KHR_प्रवाहः_उपभोक्ता_gltexture 1
#यदि_परिभाषितम् EGL_KHR_प्रवाहः
#परिभाषय EGL_उपभोक्ता_ACQUIRE_TIMEOUT_USEC_KHR 0x321E
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALKHRPROC) (EGLDisplay dpy, EGLStreamKHR प्रवाहः);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERACQUIREKHRPROC) (EGLDisplay dpy, EGLStreamKHR प्रवाहः);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERRELEASEKHRPROC) (EGLDisplay dpy, EGLStreamKHR प्रवाहः);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_प्रवाहः_उपभोक्ता_GLTexture_External_KHR (EGLDisplay dpy, EGLStreamKHR प्रवाहः);
EGLAPI EGLBoolean EGLAPIENTRY egl_प्रवाहः_उपभोक्ता_Acquire_KHR (EGLDisplay dpy, EGLStreamKHR प्रवाहः);
EGLAPI EGLBoolean EGLAPIENTRY egl_प्रवाहः_उपभोक्ता_Release_KHR (EGLDisplay dpy, EGLStreamKHR प्रवाहः);
#यदि_अन्तः
#यदि_अन्तः /* EGL_KHR_stream */
#यदि_अन्तः /* EGL_KHR_stream_consumer_gltexture */

#यदि_अपरिभाषितम् EGL_KHR_प्रवाहः_cross_process_fd
#परिभाषय EGL_KHR_प्रवाहः_cross_process_fd 1
प्रकारनिर्देश पूर्णाङ्क EGLNativeFileDescriptorKHR;
#यदि_परिभाषितम् EGL_KHR_प्रवाहः
#परिभाषय EGL_NO_FILE_DESCRIPTOR_KHR        EGL_CAST(EGLNativeFileDescriptorKHR,-1)
प्रकारनिर्देश EGLNativeFileDescriptorKHR (EGLAPIENTRYP PFNEGLGETSTREAMFILEDESCRIPTORKHRPROC) (EGLDisplay dpy, EGLStreamKHR प्रवाहः);
प्रकारनिर्देश EGLStreamKHR (EGLAPIENTRYP PFNEGLCREATESTREAMFROMFILEDESCRIPTORKHRPROC) (EGLDisplay dpy, EGLNativeFileDescriptorKHR file_descriptor);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLNativeFileDescriptorKHR EGLAPIENTRY egl_Get_प्रवाहः_File_Descriptor_KHR (EGLDisplay dpy, EGLStreamKHR प्रवाहः);
EGLAPI EGLStreamKHR EGLAPIENTRY egl_Create_प्रवाहः_From_File_Descriptor_KHR (EGLDisplay dpy, EGLNativeFileDescriptorKHR file_descriptor);
#यदि_अन्तः
#यदि_अन्तः /* EGL_KHR_stream */
#यदि_अन्तः /* EGL_KHR_stream_cross_process_fd */

#यदि_अपरिभाषितम् EGL_KHR_प्रवाहः_fifo
#परिभाषय EGL_KHR_प्रवाहः_fifo 1
#यदि_परिभाषितम् EGL_KHR_प्रवाहः
#परिभाषय EGL_प्रवाहः_FIFO_दीर्घता_KHR        0x31FC
#परिभाषय EGL_प्रवाहः_TIME_NOW_KHR           0x31FD
#परिभाषय EGL_प्रवाहः_TIME_उपभोक्ता_KHR      0x31FE
#परिभाषय EGL_प्रवाहः_TIME_उत्पादकः_KHR      0x31FF
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMTIMEKHRPROC) (EGLDisplay dpy, EGLStreamKHR प्रवाहः, EGLenum attribute, EGLTimeKHR *मानम्);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_प्रवाहः_Time_KHR (EGLDisplay dpy, EGLStreamKHR प्रवाहः, EGLenum attribute, EGLTimeKHR *मानम्);
#यदि_अन्तः
#यदि_अन्तः /* EGL_KHR_stream */
#यदि_अन्तः /* EGL_KHR_stream_fifo */

#यदि_अपरिभाषितम् EGL_KHR_प्रवाहः_उत्पादकः_aldatalocator
#परिभाषय EGL_KHR_प्रवाहः_उत्पादकः_aldatalocator 1
#यदि_परिभाषितम् EGL_KHR_प्रवाहः
#यदि_अन्तः /* EGL_KHR_stream */
#यदि_अन्तः /* EGL_KHR_stream_producer_aldatalocator */

#यदि_अपरिभाषितम् EGL_KHR_प्रवाहः_उत्पादकः_eglsurface
#परिभाषय EGL_KHR_प्रवाहः_उत्पादकः_eglsurface 1
#यदि_परिभाषितम् EGL_KHR_प्रवाहः
#परिभाषय EGL_प्रवाहः_BIT_KHR                0x0800
प्रकारनिर्देश EGLSurface (EGLAPIENTRYP PFNEGLCREATESTREAMPRODUCERSURFACEKHRPROC) (EGLDisplay dpy, EGLConfig config, EGLStreamKHR प्रवाहः, ध्रुव EGLint *attrib_list);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSurface EGLAPIENTRY egl_Create_प्रवाहः_उत्पादकः_Surface_KHR (EGLDisplay dpy, EGLConfig config, EGLStreamKHR प्रवाहः, ध्रुव EGLint *attrib_list);
#यदि_अन्तः
#यदि_अन्तः /* EGL_KHR_stream */
#यदि_अन्तः /* EGL_KHR_stream_producer_eglsurface */

#यदि_अपरिभाषितम् EGL_KHR_surfaceless_context
#परिभाषय EGL_KHR_surfaceless_context 1
#यदि_अन्तः /* EGL_KHR_surfaceless_context */

#यदि_अपरिभाषितम् EGL_KHR_swap_buffers_with_damage
#परिभाषय EGL_KHR_swap_buffers_with_damage 1
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSWITHDAMAGEKHRPROC) (EGLDisplay dpy, EGLSurface surface, ध्रुव EGLint *rects, EGLint n_rects);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglSwapBuffersWithDamageKHR (EGLDisplay dpy, EGLSurface surface, ध्रुव EGLint *rects, EGLint n_rects);
#यदि_अन्तः
#यदि_अन्तः /* EGL_KHR_swap_buffers_with_damage */

#यदि_अपरिभाषितम् EGL_KHR_vg_parent_image
#परिभाषय EGL_KHR_vg_parent_image 1
#परिभाषय EGL_VG_PARENT_IMAGE_KHR           0x30BA
#यदि_अन्तः /* EGL_KHR_vg_parent_image */

#यदि_अपरिभाषितम् EGL_KHR_wait_sync
#परिभाषय EGL_KHR_wait_sync 1
प्रकारनिर्देश EGLint (EGLAPIENTRYP PFNEGLWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLint EGLAPIENTRY eglWaitSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
#यदि_अन्तः
#यदि_अन्तः /* EGL_KHR_wait_sync */

#यदि_अपरिभाषितम् EGL_ANDROID_GLES_layers
#परिभाषय EGL_ANDROID_GLES_layers 1
#यदि_अन्तः /* EGL_ANDROID_GLES_layers */

#यदि_अपरिभाषितम् EGL_ANDROID_blob_cache
#परिभाषय EGL_ANDROID_blob_cache 1
प्रकारनिर्देश khronos_ssize_t EGLsizeiANDROID;
प्रकारनिर्देश शून्य (*EGLSetBlobFuncANDROID) (ध्रुव शून्य *कुञ्चिका, EGLsizeiANDROID कुञ्चिका_आकार_2, ध्रुव शून्य *मानम्, EGLsizeiANDROID मानम्_आकार_2);
प्रकारनिर्देश EGLsizeiANDROID (*EGLGetBlobFuncANDROID) (ध्रुव शून्य *कुञ्चिका, EGLsizeiANDROID कुञ्चिका_आकार_2, शून्य *मानम्, EGLsizeiANDROID मानम्_आकार_2);
प्रकारनिर्देश शून्य (EGLAPIENTRYP PFNEGLSETBLOBCACHEFUNCSANDROIDPROC) (EGLDisplay dpy, EGLSetBlobFuncANDROID समुच्चयः, EGLGetBlobFuncANDROID get);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI शून्य EGLAPIENTRY egl_समुच्चयः_Blob_Cache_Funcs_ANDROID (EGLDisplay dpy, EGLSetBlobFuncANDROID समुच्चयः, EGLGetBlobFuncANDROID get);
#यदि_अन्तः
#यदि_अन्तः /* EGL_ANDROID_blob_cache */

#यदि_अपरिभाषितम् EGL_ANDROID_create_native_client_बफर
#परिभाषय EGL_ANDROID_create_native_client_बफर 1
#परिभाषय EGL_NATIVE_बफर_USAGE_ANDROID   0x3143
#परिभाषय EGL_NATIVE_बफर_USAGE_PROTECTED_BIT_ANDROID 0x00000001
#परिभाषय EGL_NATIVE_बफर_USAGE_RENDERBUFFER_BIT_ANDROID 0x00000002
#परिभाषय EGL_NATIVE_बफर_USAGE_TEXTURE_BIT_ANDROID 0x00000004
प्रकारनिर्देश EGLClient_बफर (EGLAPIENTRYP PFNEGLCREATENATIVECLIENTBUFFERANDROIDPROC) (ध्रुव EGLint *attrib_list);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLClient_बफर EGLAPIENTRY egl_Create_Native_Client_बफर_ANDROID (ध्रुव EGLint *attrib_list);
#यदि_अन्तः
#यदि_अन्तः /* EGL_ANDROID_create_native_client_buffer */

#यदि_अपरिभाषितम् EGL_ANDROID_framebuffer_target
#परिभाषय EGL_ANDROID_framebuffer_target 1
#परिभाषय EGL_FRAMEBUFFER_TARGET_ANDROID    0x3147
#यदि_अन्तः /* EGL_ANDROID_framebuffer_target */

#यदि_अपरिभाषितम् EGL_ANDROID_front_बफर_auto_refresh
#परिभाषय EGL_ANDROID_front_बफर_auto_refresh 1
#परिभाषय EGL_FRONT_बफर_AUTO_REFRESH_ANDROID 0x314C
#यदि_अन्तः /* EGL_ANDROID_front_buffer_auto_refresh */

#यदि_अपरिभाषितम् EGL_ANDROID_get_frame_timestamps
#परिभाषय EGL_ANDROID_get_frame_timestamps 1
प्रकारनिर्देश khronos_stime_nanoseconds_t EGLnsecsANDROID;
#परिभाषय EGL_TIMESTAMP_PENDING_ANDROID     EGL_CAST(EGLnsecsANDROID,-2)
#परिभाषय EGL_TIMESTAMP_INVALID_ANDROID     EGL_CAST(EGLnsecsANDROID,-1)
#परिभाषय EGL_TIMESTAMPS_ANDROID            0x3430
#परिभाषय EGL_संयुक्त_DEADLINE_ANDROID    0x3431
#परिभाषय EGL_संयुक्त_INTERVAL_ANDROID    0x3432
#परिभाषय EGL_संयुक्त_गन्तव्यम्_PRESENT_LATENCY_ANDROID 0x3433
#परिभाषय EGL_REQUESTED_PRESENT_TIME_ANDROID 0x3434
#परिभाषय EGL_RENDERING_COMPLETE_TIME_ANDROID 0x3435
#परिभाषय EGL_COMPOSITION_LATCH_TIME_ANDROID 0x3436
#परिभाषय EGL_FIRST_COMPOSITION_START_TIME_ANDROID 0x3437
#परिभाषय EGL_चरमः_COMPOSITION_START_TIME_ANDROID 0x3438
#परिभाषय EGL_FIRST_COMPOSITION_GPU_परिसमाप्तम्_TIME_ANDROID 0x3439
#परिभाषय EGL_DISPLAY_PRESENT_TIME_ANDROID  0x343A
#परिभाषय EGL_पङ्क्तेः_निष्कासय_READY_TIME_ANDROID    0x343B
#परिभाषय EGL_READS_समाप्तम्_TIME_ANDROID       0x343C
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLGETCOMPOSITORTIMINGSUPPORTEDANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLint name);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLGETCOMPOSITORTIMINGANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLint अङ्कः_Timestamps,  ध्रुव EGLint *नामानि, EGLnsecsANDROID *मानानि);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLGETNEXTFRAMEIDANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR *frameId);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLGETFRAMETIMESTAMPSUPPORTEDANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLint timestamp);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLGETFRAMETIMESTAMPSANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR frameId, EGLint अङ्कः_Timestamps,  ध्रुव EGLint *timestamps, EGLnsecsANDROID *मानानि);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglGetCompositorTimingSupportedANDROID (EGLDisplay dpy, EGLSurface surface, EGLint name);
EGLAPI EGLBoolean EGLAPIENTRY eglGetCompositorTimingANDROID (EGLDisplay dpy, EGLSurface surface, EGLint अङ्कः_Timestamps,  ध्रुव EGLint *नामानि, EGLnsecsANDROID *मानानि);
EGLAPI EGLBoolean EGLAPIENTRY egl_Get_अग्र_Frame_Id_ANDROID (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR *frameId);
EGLAPI EGLBoolean EGLAPIENTRY eglGetFrameTimestampSupportedANDROID (EGLDisplay dpy, EGLSurface surface, EGLint timestamp);
EGLAPI EGLBoolean EGLAPIENTRY eglGetFrameTimestampsANDROID (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR frameId, EGLint अङ्कः_Timestamps,  ध्रुव EGLint *timestamps, EGLnsecsANDROID *मानानि);
#यदि_अन्तः
#यदि_अन्तः /* EGL_ANDROID_get_frame_timestamps */

#यदि_अपरिभाषितम् EGL_ANDROID_get_native_client_बफर
#परिभाषय EGL_ANDROID_get_native_client_बफर 1
संरचना AHardware_बफर;
प्रकारनिर्देश EGLClient_बफर (EGLAPIENTRYP PFNEGLGETNATIVECLIENTBUFFERANDROIDPROC) (ध्रुव संरचना AHardware_बफर *बफर_2);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLClient_बफर EGLAPIENTRY egl_Get_Native_Client_बफर_ANDROID (ध्रुव संरचना AHardware_बफर *बफर_2);
#यदि_अन्तः
#यदि_अन्तः /* EGL_ANDROID_get_native_client_buffer */

#यदि_अपरिभाषितम् EGL_ANDROID_image_native_बफर
#परिभाषय EGL_ANDROID_image_native_बफर 1
#परिभाषय EGL_NATIVE_बफर_ANDROID         0x3140
#यदि_अन्तः /* EGL_ANDROID_image_native_buffer */

#यदि_अपरिभाषितम् EGL_ANDROID_native_fence_sync
#परिभाषय EGL_ANDROID_native_fence_sync 1
#परिभाषय EGL_SYNC_NATIVE_FENCE_ANDROID     0x3144
#परिभाषय EGL_SYNC_NATIVE_FENCE_FD_ANDROID  0x3145
#परिभाषय EGL_SYNC_NATIVE_FENCE_SIGNALED_ANDROID 0x3146
#परिभाषय EGL_NO_NATIVE_FENCE_FD_ANDROID    -1
प्रकारनिर्देश EGLint (EGLAPIENTRYP PFNEGLDUPNATIVEFENCEFDANDROIDPROC) (EGLDisplay dpy, EGLSyncKHR sync);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLint EGLAPIENTRY eglDupNativeFenceFDANDROID (EGLDisplay dpy, EGLSyncKHR sync);
#यदि_अन्तः
#यदि_अन्तः /* EGL_ANDROID_native_fence_sync */

#यदि_अपरिभाषितम् EGL_ANDROID_presentation_time
#परिभाषय EGL_ANDROID_presentation_time 1
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLPRESENTATIONTIMEANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLnsecsANDROID time);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglPresentationTimeANDROID (EGLDisplay dpy, EGLSurface surface, EGLnsecsANDROID time);
#यदि_अन्तः
#यदि_अन्तः /* EGL_ANDROID_presentation_time */

#यदि_अपरिभाषितम् EGL_ANDROID_recordable
#परिभाषय EGL_ANDROID_recordable 1
#परिभाषय EGL_RECORDABLE_ANDROID            0x3142
#यदि_अन्तः /* EGL_ANDROID_recordable */

#यदि_अपरिभाषितम् EGL_ANDROID_telemetry_hint
#परिभाषय EGL_ANDROID_telemetry_hint 1
#परिभाषय EGL_TELEMETRY_HINT_ANDROID        0x3570
#यदि_अन्तः /* EGL_ANDROID_telemetry_hint */

#यदि_अपरिभाषितम् EGL_ANGLE_d3d_share_handle_client_बफर
#परिभाषय EGL_ANGLE_d3d_share_handle_client_बफर 1
#परिभाषय EGL_D3D_TEXTURE_2D_SHARE_HANDLE_ANGLE 0x3200
#यदि_अन्तः /* EGL_ANGLE_d3d_share_handle_client_buffer */

#यदि_अपरिभाषितम् EGL_ANGLE_device_d3d
#परिभाषय EGL_ANGLE_device_d3d 1
#परिभाषय EGL_D3D9_DEVICE_ANGLE             0x33A0
#परिभाषय EGL_D3D11_DEVICE_ANGLE            0x33A1
#यदि_अन्तः /* EGL_ANGLE_device_d3d */

#यदि_अपरिभाषितम् EGL_ANGLE_query_surface_pointer
#परिभाषय EGL_ANGLE_query_surface_pointer 1
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSURFACEPOINTERANGLEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint attribute, शून्य **मानम्);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQuerySurfacePointerANGLE (EGLDisplay dpy, EGLSurface surface, EGLint attribute, शून्य **मानम्);
#यदि_अन्तः
#यदि_अन्तः /* EGL_ANGLE_query_surface_pointer */

#यदि_अपरिभाषितम् EGL_ANGLE_surface_d3d_texture_2d_share_handle
#परिभाषय EGL_ANGLE_surface_d3d_texture_2d_share_handle 1
#यदि_अन्तः /* EGL_ANGLE_surface_d3d_texture_2d_share_handle */

#यदि_अपरिभाषितम् EGL_ANGLE_sync_control_दरः
#परिभाषय EGL_ANGLE_sync_control_दरः 1
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLGETMSCRATEANGLEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint *numerator, EGLint *denominator);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Get_Msc_दरः_ANGLE (EGLDisplay dpy, EGLSurface surface, EGLint *numerator, EGLint *denominator);
#यदि_अन्तः
#यदि_अन्तः /* EGL_ANGLE_sync_control_rate */

#यदि_अपरिभाषितम् EGL_ANGLE_गवाक्षः_fixed_आकार
#परिभाषय EGL_ANGLE_गवाक्षः_fixed_आकार 1
#परिभाषय EGL_FIXED_आकार_ANGLE              0x3201
#यदि_अन्तः /* EGL_ANGLE_window_fixed_size */

#यदि_अपरिभाषितम् EGL_ARM_image_format
#परिभाषय EGL_ARM_image_format 1
#परिभाषय EGL_COLOR_COMPONENT_TYPE_UNSIGNED_INTEGER_ARM 0x3287
#परिभाषय EGL_COLOR_COMPONENT_TYPE_INTEGER_ARM 0x3288
#यदि_अन्तः /* EGL_ARM_image_format */

#यदि_अपरिभाषितम् EGL_ARM_implicit_external_sync
#परिभाषय EGL_ARM_implicit_external_sync 1
#परिभाषय EGL_SYNC_प्राक्_COMMANDS_IMPLICIT_EXTERNAL_ARM 0x328A
#यदि_अन्तः /* EGL_ARM_implicit_external_sync */

#यदि_अपरिभाषितम् EGL_ARM_pixmap_multisample_discard
#परिभाषय EGL_ARM_pixmap_multisample_discard 1
#परिभाषय EGL_DISCARD_SAMPLES_ARM           0x3286
#यदि_अन्तः /* EGL_ARM_pixmap_multisample_discard */

#यदि_अपरिभाषितम् EGL_EXT_bind_गन्तव्यम्_front
#परिभाषय EGL_EXT_bind_गन्तव्यम्_front 1
#परिभाषय EGL_FRONT_बफर_EXT              0x3464
#यदि_अन्तः /* EGL_EXT_bind_to_front */

#यदि_अपरिभाषितम् EGL_EXT_बफर_age
#परिभाषय EGL_EXT_बफर_age 1
#परिभाषय EGL_बफर_AGE_EXT                0x313D
#यदि_अन्तः /* EGL_EXT_buffer_age */

#यदि_अपरिभाषितम् EGL_EXT_client_extensions
#परिभाषय EGL_EXT_client_extensions 1
#यदि_अन्तः /* EGL_EXT_client_extensions */

#यदि_अपरिभाषितम् EGL_EXT_client_sync
#परिभाषय EGL_EXT_client_sync 1
#परिभाषय EGL_SYNC_CLIENT_EXT               0x3364
#परिभाषय EGL_SYNC_CLIENT_SIGNAL_EXT        0x3365
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLCLIENTSIGNALSYNCEXTPROC) (EGLDisplay dpy, EGLSync sync, ध्रुव EGLAttrib *attrib_list);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglClientSignalSyncEXT (EGLDisplay dpy, EGLSync sync, ध्रुव EGLAttrib *attrib_list);
#यदि_अन्तः
#यदि_अन्तः /* EGL_EXT_client_sync */

#यदि_अपरिभाषितम् EGL_EXT_compositor
#परिभाषय EGL_EXT_compositor 1
#परिभाषय EGL_PRIMARY_COMPOSITOR_CONTEXT_EXT 0x3460
#परिभाषय EGL_EXTERNAL_REF_ID_EXT           0x3461
#परिभाषय EGL_COMPOSITOR_DROP_NEWEST_FRAME_EXT 0x3462
#परिभाषय EGL_COMPOSITOR_KEEP_NEWEST_FRAME_EXT 0x3463
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETCONTEXTLISTEXTPROC) (ध्रुव EGLint *external_ref_ids, EGLint अङ्कः_entries);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETCONTEXTATTRIBUTESEXTPROC) (EGLint external_ref_id, ध्रुव EGLint *context_गुणाः, EGLint अङ्कः_entries);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETWINDOWLISTEXTPROC) (EGLint external_ref_id, ध्रुव EGLint *external_win_ids, EGLint अङ्कः_entries);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETWINDOWATTRIBUTESEXTPROC) (EGLint external_win_id, ध्रुव EGLint *गवाक्षः_गुणाः, EGLint अङ्कः_entries);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORBINDTEXWINDOWEXTPROC) (EGLint external_win_id);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETSIZEEXTPROC) (EGLint external_win_id, EGLint विस्तारः, EGLint height);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSWAPPOLICYEXTPROC) (EGLint external_win_id, EGLint policy);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_समुच्चयः_Context_List_EXT (ध्रुव EGLint *external_ref_ids, EGLint अङ्कः_entries);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_समुच्चयः_Context_गुणाः_EXT (EGLint external_ref_id, ध्रुव EGLint *context_गुणाः, EGLint अङ्कः_entries);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_समुच्चयः_गवाक्षः_List_EXT (EGLint external_ref_id, ध्रुव EGLint *external_win_ids, EGLint अङ्कः_entries);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_समुच्चयः_गवाक्षः_गुणाः_EXT (EGLint external_win_id, ध्रुव EGLint *गवाक्षः_गुणाः, EGLint अङ्कः_entries);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_Bind_Tex_गवाक्षः_EXT (EGLint external_win_id);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_समुच्चयः_आकार_EXT (EGLint external_win_id, EGLint विस्तारः, EGLint height);
EGLAPI EGLBoolean EGLAPIENTRY eglCompositorSwapPolicyEXT (EGLint external_win_id, EGLint policy);
#यदि_अन्तः
#यदि_अन्तः /* EGL_EXT_compositor */

#यदि_अपरिभाषितम् EGL_EXT_config_select_गणः
#परिभाषय EGL_EXT_config_select_गणः 1
#परिभाषय EGL_CONFIG_SELECT_गणः_EXT       0x34C0
#यदि_अन्तः /* EGL_EXT_config_select_group */

#यदि_अपरिभाषितम् EGL_EXT_create_context_robustness
#परिभाषय EGL_EXT_create_context_robustness 1
#परिभाषय EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT 0x30BF
#परिभाषय EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_EXT 0x3138
#परिभाषय EGL_NO_RESET_NOTIFICATION_EXT     0x31BE
#परिभाषय EGL_LOSE_CONTEXT_ON_RESET_EXT     0x31BF
#यदि_अन्तः /* EGL_EXT_create_context_robustness */

#यदि_अपरिभाषितम् EGL_EXT_device_आधारः
#परिभाषय EGL_EXT_device_आधारः 1
प्रकारनिर्देश शून्य *EGLDeviceEXT;
#परिभाषय EGL_NO_DEVICE_EXT                 EGL_CAST(EGLDeviceEXT,0)
#परिभाषय EGL_BAD_DEVICE_EXT                0x322B
#परिभाषय EGL_DEVICE_EXT                    0x322C
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICEATTRIBEXTPROC) (EGLDeviceEXT device, EGLint attribute, EGLAttrib *मानम्);
प्रकारनिर्देश ध्रुव वर्ण *(EGLAPIENTRYP PFNEGLQUERYDEVICESTRINGEXTPROC) (EGLDeviceEXT device, EGLint name);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICESEXTPROC) (EGLint max_devices, EGLDeviceEXT *devices, EGLint *अङ्कः_devices);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDISPLAYATTRIBEXTPROC) (EGLDisplay dpy, EGLint attribute, EGLAttrib *मानम्);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDeviceAttribEXT (EGLDeviceEXT device, EGLint attribute, EGLAttrib *मानम्);
EGLAPI ध्रुव वर्ण *EGLAPIENTRY eglQueryDeviceStringEXT (EGLDeviceEXT device, EGLint name);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDevicesEXT (EGLint max_devices, EGLDeviceEXT *devices, EGLint *अङ्कः_devices);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDisplayAttribEXT (EGLDisplay dpy, EGLint attribute, EGLAttrib *मानम्);
#यदि_अन्तः
#यदि_अन्तः /* EGL_EXT_device_base */

#यदि_अपरिभाषितम् EGL_EXT_device_drm
#परिभाषय EGL_EXT_device_drm 1
#परिभाषय EGL_DRM_DEVICE_FILE_EXT           0x3233
#परिभाषय EGL_DRM_MASTER_FD_EXT             0x333C
#यदि_अन्तः /* EGL_EXT_device_drm */

#यदि_अपरिभाषितम् EGL_EXT_device_drm_render_ग्रन्थिः
#परिभाषय EGL_EXT_device_drm_render_ग्रन्थिः 1
#परिभाषय EGL_DRM_RENDER_ग्रन्थिः_FILE_EXT      0x3377
#यदि_अन्तः /* EGL_EXT_device_drm_render_node */

#यदि_अपरिभाषितम् EGL_EXT_device_enumeration
#परिभाषय EGL_EXT_device_enumeration 1
#यदि_अन्तः /* EGL_EXT_device_enumeration */

#यदि_अपरिभाषितम् EGL_EXT_device_openwf
#परिभाषय EGL_EXT_device_openwf 1
#परिभाषय EGL_OPENWF_DEVICE_ID_EXT          0x3237
#परिभाषय EGL_OPENWF_DEVICE_EXT             0x333D
#यदि_अन्तः /* EGL_EXT_device_openwf */

#यदि_अपरिभाषितम् EGL_EXT_device_persistent_id
#परिभाषय EGL_EXT_device_persistent_id 1
#परिभाषय EGL_DEVICE_UUID_EXT               0x335C
#परिभाषय EGL_DRIVER_UUID_EXT               0x335D
#परिभाषय EGL_DRIVER_NAME_EXT               0x335E
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICEBINARYEXTPROC) (EGLDeviceEXT device, EGLint name, EGLint max_आकार, शून्य *मानम्, EGLint *आकार);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Device_द्विमान_EXT (EGLDeviceEXT device, EGLint name, EGLint max_आकार, शून्य *मानम्, EGLint *आकार);
#यदि_अन्तः
#यदि_अन्तः /* EGL_EXT_device_persistent_id */

#यदि_अपरिभाषितम् EGL_EXT_device_query
#परिभाषय EGL_EXT_device_query 1
#यदि_अन्तः /* EGL_EXT_device_query */

#यदि_अपरिभाषितम् EGL_EXT_device_query_name
#परिभाषय EGL_EXT_device_query_name 1
#परिभाषय EGL_RENDERER_EXT                  0x335F
#यदि_अन्तः /* EGL_EXT_device_query_name */

#यदि_अपरिभाषितम् EGL_EXT_device_type
#परिभाषय EGL_EXT_device_type 1
#परिभाषय EGL_DEVICE_TYPE_EXT               0x3590
#परिभाषय EGL_DEVICE_TYPE_OTHER_EXT         0x3591
#परिभाषय EGL_DEVICE_TYPE_INTEGRATED_GPU_EXT 0x3592
#परिभाषय EGL_DEVICE_TYPE_DISCRETE_GPU_EXT  0x3593
#परिभाषय EGL_DEVICE_TYPE_CPU_EXT           0x3594
#यदि_अन्तः /* EGL_EXT_device_type */

#यदि_अपरिभाषितम् EGL_EXT_display_alloc
#परिभाषय EGL_EXT_display_alloc 1
#परिभाषय EGL_ALLOC_NEW_DISPLAY_EXT         0x3379
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYDISPLAYEXTPROC) (EGLDisplay dpy);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyDisplayEXT (EGLDisplay dpy);
#यदि_अन्तः
#यदि_अन्तः /* EGL_EXT_display_alloc */

#यदि_अपरिभाषितम् EGL_EXT_explicit_device
#परिभाषय EGL_EXT_explicit_device 1
#यदि_अन्तः /* EGL_EXT_explicit_device */

#यदि_अपरिभाषितम् EGL_EXT_gl_colorspace_bt2020_hlg
#परिभाषय EGL_EXT_gl_colorspace_bt2020_hlg 1
#परिभाषय EGL_GL_COLORSPACE_BT2020_HLG_EXT  0x3540
#यदि_अन्तः /* EGL_EXT_gl_colorspace_bt2020_hlg */

#यदि_अपरिभाषितम् EGL_EXT_gl_colorspace_bt2020_रैखिकम्
#परिभाषय EGL_EXT_gl_colorspace_bt2020_रैखिकम् 1
#परिभाषय EGL_GL_COLORSPACE_BT2020_रैखिकम्_EXT 0x333F
#यदि_अन्तः /* EGL_EXT_gl_colorspace_bt2020_linear */

#यदि_अपरिभाषितम् EGL_EXT_gl_colorspace_bt2020_pq
#परिभाषय EGL_EXT_gl_colorspace_bt2020_pq 1
#परिभाषय EGL_GL_COLORSPACE_BT2020_PQ_EXT   0x3340
#यदि_अन्तः /* EGL_EXT_gl_colorspace_bt2020_pq */

#यदि_अपरिभाषितम् EGL_EXT_gl_colorspace_display_p3
#परिभाषय EGL_EXT_gl_colorspace_display_p3 1
#परिभाषय EGL_GL_COLORSPACE_DISPLAY_P3_EXT  0x3363
#यदि_अन्तः /* EGL_EXT_gl_colorspace_display_p3 */

#यदि_अपरिभाषितम् EGL_EXT_gl_colorspace_display_p3_रैखिकम्
#परिभाषय EGL_EXT_gl_colorspace_display_p3_रैखिकम् 1
#परिभाषय EGL_GL_COLORSPACE_DISPLAY_P3_रैखिकम्_EXT 0x3362
#यदि_अन्तः /* EGL_EXT_gl_colorspace_display_p3_linear */

#यदि_अपरिभाषितम् EGL_EXT_gl_colorspace_display_p3_passthrough
#परिभाषय EGL_EXT_gl_colorspace_display_p3_passthrough 1
#परिभाषय EGL_GL_COLORSPACE_DISPLAY_P3_PASSTHROUGH_EXT 0x3490
#यदि_अन्तः /* EGL_EXT_gl_colorspace_display_p3_passthrough */

#यदि_अपरिभाषितम् EGL_EXT_gl_colorspace_scrgb
#परिभाषय EGL_EXT_gl_colorspace_scrgb 1
#परिभाषय EGL_GL_COLORSPACE_SCRGB_EXT       0x3351
#यदि_अन्तः /* EGL_EXT_gl_colorspace_scrgb */

#यदि_अपरिभाषितम् EGL_EXT_gl_colorspace_scrgb_रैखिकम्
#परिभाषय EGL_EXT_gl_colorspace_scrgb_रैखिकम् 1
#परिभाषय EGL_GL_COLORSPACE_SCRGB_रैखिकम्_EXT 0x3350
#यदि_अन्तः /* EGL_EXT_gl_colorspace_scrgb_linear */

#यदि_अपरिभाषितम् EGL_EXT_image_dma_buf_import
#परिभाषय EGL_EXT_image_dma_buf_import 1
#परिभाषय EGL_LINUX_DMA_BUF_EXT             0x3270
#परिभाषय EGL_LINUX_DRM_FOURCC_EXT          0x3271
#परिभाषय EGL_DMA_BUF_PLANE0_FD_EXT         0x3272
#परिभाषय EGL_DMA_BUF_PLANE0_विस्थापनम्_EXT     0x3273
#परिभाषय EGL_DMA_BUF_PLANE0_PITCH_EXT      0x3274
#परिभाषय EGL_DMA_BUF_PLANE1_FD_EXT         0x3275
#परिभाषय EGL_DMA_BUF_PLANE1_विस्थापनम्_EXT     0x3276
#परिभाषय EGL_DMA_BUF_PLANE1_PITCH_EXT      0x3277
#परिभाषय EGL_DMA_BUF_PLANE2_FD_EXT         0x3278
#परिभाषय EGL_DMA_BUF_PLANE2_विस्थापनम्_EXT     0x3279
#परिभाषय EGL_DMA_BUF_PLANE2_PITCH_EXT      0x327A
#परिभाषय EGL_YUV_COLOR_SPACE_HINT_EXT      0x327B
#परिभाषय EGL_SAMPLE_RANGE_HINT_EXT         0x327C
#परिभाषय EGL_YUV_CHROMA_HORIZONTAL_SITING_HINT_EXT 0x327D
#परिभाषय EGL_YUV_CHROMA_VERTICAL_SITING_HINT_EXT 0x327E
#परिभाषय EGL_ITU_REC601_EXT                0x327F
#परिभाषय EGL_ITU_REC709_EXT                0x3280
#परिभाषय EGL_ITU_REC2020_EXT               0x3281
#परिभाषय EGL_YUV_पूर्णम्_RANGE_EXT            0x3282
#परिभाषय EGL_YUV_NARROW_RANGE_EXT          0x3283
#परिभाषय EGL_YUV_CHROMA_SITING_0_EXT       0x3284
#परिभाषय EGL_YUV_CHROMA_SITING_0_5_EXT     0x3285
#यदि_अन्तः /* EGL_EXT_image_dma_buf_import */

#यदि_अपरिभाषितम् EGL_EXT_image_dma_buf_import_modifiers
#परिभाषय EGL_EXT_image_dma_buf_import_modifiers 1
#परिभाषय EGL_DMA_BUF_PLANE3_FD_EXT         0x3440
#परिभाषय EGL_DMA_BUF_PLANE3_विस्थापनम्_EXT     0x3441
#परिभाषय EGL_DMA_BUF_PLANE3_PITCH_EXT      0x3442
#परिभाषय EGL_DMA_BUF_PLANE0_MODIFIER_LO_EXT 0x3443
#परिभाषय EGL_DMA_BUF_PLANE0_MODIFIER_HI_EXT 0x3444
#परिभाषय EGL_DMA_BUF_PLANE1_MODIFIER_LO_EXT 0x3445
#परिभाषय EGL_DMA_BUF_PLANE1_MODIFIER_HI_EXT 0x3446
#परिभाषय EGL_DMA_BUF_PLANE2_MODIFIER_LO_EXT 0x3447
#परिभाषय EGL_DMA_BUF_PLANE2_MODIFIER_HI_EXT 0x3448
#परिभाषय EGL_DMA_BUF_PLANE3_MODIFIER_LO_EXT 0x3449
#परिभाषय EGL_DMA_BUF_PLANE3_MODIFIER_HI_EXT 0x344A
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDMABUFFORMATSEXTPROC) (EGLDisplay dpy, EGLint max_formats, EGLint *formats, EGLint *अङ्कः_formats);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDMABUFMODIFIERSEXTPROC) (EGLDisplay dpy, EGLint format, EGLint max_modifiers, EGLuint64KHR *modifiers, EGLBoolean *external_only, EGLint *अङ्कः_modifiers);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDmaBufFormatsEXT (EGLDisplay dpy, EGLint max_formats, EGLint *formats, EGLint *अङ्कः_formats);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDmaBufModifiersEXT (EGLDisplay dpy, EGLint format, EGLint max_modifiers, EGLuint64KHR *modifiers, EGLBoolean *external_only, EGLint *अङ्कः_modifiers);
#यदि_अन्तः
#यदि_अन्तः /* EGL_EXT_image_dma_buf_import_modifiers */

#यदि_अपरिभाषितम् EGL_EXT_image_gl_colorspace
#परिभाषय EGL_EXT_image_gl_colorspace 1
#परिभाषय EGL_GL_COLORSPACE_DEFAULT_EXT     0x314D
#यदि_अन्तः /* EGL_EXT_image_gl_colorspace */

#यदि_अपरिभाषितम् EGL_EXT_image_implicit_sync_control
#परिभाषय EGL_EXT_image_implicit_sync_control 1
#परिभाषय EGL_IMPORT_SYNC_TYPE_EXT          0x3470
#परिभाषय EGL_IMPORT_IMPLICIT_SYNC_EXT      0x3471
#परिभाषय EGL_IMPORT_EXPLICIT_SYNC_EXT      0x3472
#यदि_अन्तः /* EGL_EXT_image_implicit_sync_control */

#यदि_अपरिभाषितम् EGL_EXT_multiview_गवाक्षः
#परिभाषय EGL_EXT_multiview_गवाक्षः 1
#परिभाषय EGL_MULTIVIEW_VIEW_गणनम्_EXT      0x3134
#यदि_अन्तः /* EGL_EXT_multiview_window */

#यदि_अपरिभाषितम् EGL_EXT_output_आधारः
#परिभाषय EGL_EXT_output_आधारः 1
प्रकारनिर्देश शून्य *EGLOutputLayerEXT;
प्रकारनिर्देश शून्य *EGLOutput_पत्तनम्_EXT;
#परिभाषय EGL_NO_OUTPUT_LAYER_EXT           EGL_CAST(EGLOutputLayerEXT,0)
#परिभाषय EGL_NO_OUTPUT_पत्तनम्_EXT            EGL_CAST(EGLOutput_पत्तनम्_EXT,0)
#परिभाषय EGL_BAD_OUTPUT_LAYER_EXT          0x322D
#परिभाषय EGL_BAD_OUTPUT_पत्तनम्_EXT           0x322E
#परिभाषय EGL_SWAP_INTERVAL_EXT             0x322F
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLGETOUTPUTLAYERSEXTPROC) (EGLDisplay dpy, ध्रुव EGLAttrib *attrib_list, EGLOutputLayerEXT *layers, EGLint max_layers, EGLint *अङ्कः_layers);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLGETOUTPUTPORTSEXTPROC) (EGLDisplay dpy, ध्रुव EGLAttrib *attrib_list, EGLOutput_पत्तनम्_EXT *ports, EGLint max_ports, EGLint *अङ्कः_ports);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLOUTPUTLAYERATTRIBEXTPROC) (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib मानम्);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLQUERYOUTPUTLAYERATTRIBEXTPROC) (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib *मानम्);
प्रकारनिर्देश ध्रुव वर्ण *(EGLAPIENTRYP PFNEGLQUERYOUTPUTLAYERSTRINGEXTPROC) (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint name);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLOUTPUTPORTATTRIBEXTPROC) (EGLDisplay dpy, EGLOutput_पत्तनम्_EXT पत्तनम्, EGLint attribute, EGLAttrib मानम्);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLQUERYOUTPUTPORTATTRIBEXTPROC) (EGLDisplay dpy, EGLOutput_पत्तनम्_EXT पत्तनम्, EGLint attribute, EGLAttrib *मानम्);
प्रकारनिर्देश ध्रुव वर्ण *(EGLAPIENTRYP PFNEGLQUERYOUTPUTPORTSTRINGEXTPROC) (EGLDisplay dpy, EGLOutput_पत्तनम्_EXT पत्तनम्, EGLint name);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglGetOutputLayersEXT (EGLDisplay dpy, ध्रुव EGLAttrib *attrib_list, EGLOutputLayerEXT *layers, EGLint max_layers, EGLint *अङ्कः_layers);
EGLAPI EGLBoolean EGLAPIENTRY eglGetOutputPortsEXT (EGLDisplay dpy, ध्रुव EGLAttrib *attrib_list, EGLOutput_पत्तनम्_EXT *ports, EGLint max_ports, EGLint *अङ्कः_ports);
EGLAPI EGLBoolean EGLAPIENTRY eglOutputLayerAttribEXT (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib मानम्);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryOutputLayerAttribEXT (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib *मानम्);
EGLAPI ध्रुव वर्ण *EGLAPIENTRY eglQueryOutputLayerStringEXT (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint name);
EGLAPI EGLBoolean EGLAPIENTRY egl_Output_पत्तनम्_Attrib_EXT (EGLDisplay dpy, EGLOutput_पत्तनम्_EXT पत्तनम्, EGLint attribute, EGLAttrib मानम्);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Output_पत्तनम्_Attrib_EXT (EGLDisplay dpy, EGLOutput_पत्तनम्_EXT पत्तनम्, EGLint attribute, EGLAttrib *मानम्);
EGLAPI ध्रुव वर्ण *EGLAPIENTRY egl_Query_Output_पत्तनम्_String_EXT (EGLDisplay dpy, EGLOutput_पत्तनम्_EXT पत्तनम्, EGLint name);
#यदि_अन्तः
#यदि_अन्तः /* EGL_EXT_output_base */

#यदि_अपरिभाषितम् EGL_EXT_output_drm
#परिभाषय EGL_EXT_output_drm 1
#परिभाषय EGL_DRM_CRTC_EXT                  0x3234
#परिभाषय EGL_DRM_PLANE_EXT                 0x3235
#परिभाषय EGL_DRM_CONNECTOR_EXT             0x3236
#यदि_अन्तः /* EGL_EXT_output_drm */

#यदि_अपरिभाषितम् EGL_EXT_output_openwf
#परिभाषय EGL_EXT_output_openwf 1
#परिभाषय EGL_OPENWF_PIPELINE_ID_EXT        0x3238
#परिभाषय EGL_OPENWF_पत्तनम्_ID_EXT            0x3239
#यदि_अन्तः /* EGL_EXT_output_openwf */

#यदि_अपरिभाषितम् EGL_EXT_pixel_format_float
#परिभाषय EGL_EXT_pixel_format_float 1
#परिभाषय EGL_COLOR_COMPONENT_TYPE_EXT      0x3339
#परिभाषय EGL_COLOR_COMPONENT_TYPE_FIXED_EXT 0x333A
#परिभाषय EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT 0x333B
#यदि_अन्तः /* EGL_EXT_pixel_format_float */

#यदि_अपरिभाषितम् EGL_EXT_platform_आधारः
#परिभाषय EGL_EXT_platform_आधारः 1
प्रकारनिर्देश EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYEXTPROC) (EGLenum platform, शून्य *native_display, ध्रुव EGLint *attrib_list);
प्रकारनिर्देश EGLSurface (EGLAPIENTRYP PFNEGLCREATEPLATFORMWINDOWSURFACEEXTPROC) (EGLDisplay dpy, EGLConfig config, शून्य *native_गवाक्षः, ध्रुव EGLint *attrib_list);
प्रकारनिर्देश EGLSurface (EGLAPIENTRYP PFNEGLCREATEPLATFORMPIXMAPSURFACEEXTPROC) (EGLDisplay dpy, EGLConfig config, शून्य *native_pixmap, ध्रुव EGLint *attrib_list);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLDisplay EGLAPIENTRY eglGetPlatformDisplayEXT (EGLenum platform, शून्य *native_display, ध्रुव EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY egl_Create_Platform_गवाक्षः_Surface_EXT (EGLDisplay dpy, EGLConfig config, शून्य *native_गवाक्षः, ध्रुव EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePlatformPixmapSurfaceEXT (EGLDisplay dpy, EGLConfig config, शून्य *native_pixmap, ध्रुव EGLint *attrib_list);
#यदि_अन्तः
#यदि_अन्तः /* EGL_EXT_platform_base */

#यदि_अपरिभाषितम् EGL_EXT_platform_device
#परिभाषय EGL_EXT_platform_device 1
#परिभाषय EGL_PLATFORM_DEVICE_EXT           0x313F
#यदि_अन्तः /* EGL_EXT_platform_device */

#यदि_अपरिभाषितम् EGL_EXT_platform_wayland
#परिभाषय EGL_EXT_platform_wayland 1
#परिभाषय EGL_PLATFORM_WAYLAND_EXT          0x31D8
#यदि_अन्तः /* EGL_EXT_platform_wayland */

#यदि_अपरिभाषितम् EGL_EXT_platform_x11
#परिभाषय EGL_EXT_platform_x11 1
#परिभाषय EGL_PLATFORM_X11_EXT              0x31D5
#परिभाषय EGL_PLATFORM_X11_SCREEN_EXT       0x31D6
#यदि_अन्तः /* EGL_EXT_platform_x11 */

#यदि_अपरिभाषितम् EGL_EXT_platform_xcb
#परिभाषय EGL_EXT_platform_xcb 1
#परिभाषय EGL_PLATFORM_XCB_EXT              0x31DC
#परिभाषय EGL_PLATFORM_XCB_SCREEN_EXT       0x31DE
#यदि_अन्तः /* EGL_EXT_platform_xcb */

#यदि_अपरिभाषितम् EGL_EXT_present_opaque
#परिभाषय EGL_EXT_present_opaque 1
#परिभाषय EGL_PRESENT_OPAQUE_EXT            0x31DF
#यदि_अन्तः /* EGL_EXT_present_opaque */

#यदि_अपरिभाषितम् EGL_EXT_protected_content
#परिभाषय EGL_EXT_protected_content 1
#परिभाषय EGL_PROTECTED_CONTENT_EXT         0x32C0
#यदि_अन्तः /* EGL_EXT_protected_content */

#यदि_अपरिभाषितम् EGL_EXT_protected_surface
#परिभाषय EGL_EXT_protected_surface 1
#यदि_अन्तः /* EGL_EXT_protected_surface */

#यदि_अपरिभाषितम् EGL_EXT_query_reset_notification_strategy
#परिभाषय EGL_EXT_query_reset_notification_strategy 1
#यदि_अन्तः /* EGL_EXT_query_reset_notification_strategy */

#यदि_अपरिभाषितम् EGL_EXT_प्रवाहः_उपभोक्ता_egloutput
#परिभाषय EGL_EXT_प्रवाहः_उपभोक्ता_egloutput 1
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMEROUTPUTEXTPROC) (EGLDisplay dpy, EGLStreamKHR प्रवाहः, EGLOutputLayerEXT layer);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_प्रवाहः_उपभोक्ता_Output_EXT (EGLDisplay dpy, EGLStreamKHR प्रवाहः, EGLOutputLayerEXT layer);
#यदि_अन्तः
#यदि_अन्तः /* EGL_EXT_stream_consumer_egloutput */

#यदि_अपरिभाषितम् EGL_EXT_surface_CTA861_3_metadata
#परिभाषय EGL_EXT_surface_CTA861_3_metadata 1
#परिभाषय EGL_CTA861_3_MAX_CONTENT_LIGHT_LEVEL_EXT 0x3360
#परिभाषय EGL_CTA861_3_MAX_FRAME_मध्यमानम्_LEVEL_EXT 0x3361
#यदि_अन्तः /* EGL_EXT_surface_CTA861_3_metadata */

#यदि_अपरिभाषितम् EGL_EXT_surface_SMPTE2086_metadata
#परिभाषय EGL_EXT_surface_SMPTE2086_metadata 1
#परिभाषय EGL_SMPTE2086_DISPLAY_PRIMARY_RX_EXT 0x3341
#परिभाषय EGL_SMPTE2086_DISPLAY_PRIMARY_RY_EXT 0x3342
#परिभाषय EGL_SMPTE2086_DISPLAY_PRIMARY_GX_EXT 0x3343
#परिभाषय EGL_SMPTE2086_DISPLAY_PRIMARY_GY_EXT 0x3344
#परिभाषय EGL_SMPTE2086_DISPLAY_PRIMARY_BX_EXT 0x3345
#परिभाषय EGL_SMPTE2086_DISPLAY_PRIMARY_BY_EXT 0x3346
#परिभाषय EGL_SMPTE2086_WHITE_POINT_X_EXT   0x3347
#परिभाषय EGL_SMPTE2086_WHITE_POINT_Y_EXT   0x3348
#परिभाषय EGL_SMPTE2086_MAX_LUMINANCE_EXT   0x3349
#परिभाषय EGL_SMPTE2086_MIN_LUMINANCE_EXT   0x334A
#परिभाषय EGL_METADATA_SCALING_EXT          50000
#यदि_अन्तः /* EGL_EXT_surface_SMPTE2086_metadata */

#यदि_अपरिभाषितम् EGL_EXT_surface_compression
#परिभाषय EGL_EXT_surface_compression 1
#परिभाषय EGL_SURFACE_COMPRESSION_EXT       0x34B0
#परिभाषय EGL_SURFACE_COMPRESSION_PLANE1_EXT 0x328E
#परिभाषय EGL_SURFACE_COMPRESSION_PLANE2_EXT 0x328F
#परिभाषय EGL_SURFACE_COMPRESSION_FIXED_दरः_NONE_EXT 0x34B1
#परिभाषय EGL_SURFACE_COMPRESSION_FIXED_दरः_DEFAULT_EXT 0x34B2
#परिभाषय EGL_SURFACE_COMPRESSION_FIXED_दरः_1_BPC_EXT 0x34B4
#परिभाषय EGL_SURFACE_COMPRESSION_FIXED_दरः_2_BPC_EXT 0x34B5
#परिभाषय EGL_SURFACE_COMPRESSION_FIXED_दरः_3_BPC_EXT 0x34B6
#परिभाषय EGL_SURFACE_COMPRESSION_FIXED_दरः_4_BPC_EXT 0x34B7
#परिभाषय EGL_SURFACE_COMPRESSION_FIXED_दरः_5_BPC_EXT 0x34B8
#परिभाषय EGL_SURFACE_COMPRESSION_FIXED_दरः_6_BPC_EXT 0x34B9
#परिभाषय EGL_SURFACE_COMPRESSION_FIXED_दरः_7_BPC_EXT 0x34BA
#परिभाषय EGL_SURFACE_COMPRESSION_FIXED_दरः_8_BPC_EXT 0x34BB
#परिभाषय EGL_SURFACE_COMPRESSION_FIXED_दरः_9_BPC_EXT 0x34BC
#परिभाषय EGL_SURFACE_COMPRESSION_FIXED_दरः_10_BPC_EXT 0x34BD
#परिभाषय EGL_SURFACE_COMPRESSION_FIXED_दरः_11_BPC_EXT 0x34BE
#परिभाषय EGL_SURFACE_COMPRESSION_FIXED_दरः_12_BPC_EXT 0x34BF
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSUPPORTEDCOMPRESSIONRATESEXTPROC) (EGLDisplay dpy, EGLConfig config, ध्रुव EGLAttrib *attrib_list, EGLint *rates, EGLint दरः_आकार, EGLint *अङ्कः_rates);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQuerySupportedCompressionRatesEXT (EGLDisplay dpy, EGLConfig config, ध्रुव EGLAttrib *attrib_list, EGLint *rates, EGLint दरः_आकार, EGLint *अङ्कः_rates);
#यदि_अन्तः
#यदि_अन्तः /* EGL_EXT_surface_compression */

#यदि_अपरिभाषितम् EGL_EXT_swap_buffers_with_damage
#परिभाषय EGL_EXT_swap_buffers_with_damage 1
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC) (EGLDisplay dpy, EGLSurface surface, ध्रुव EGLint *rects, EGLint n_rects);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglSwapBuffersWithDamageEXT (EGLDisplay dpy, EGLSurface surface, ध्रुव EGLint *rects, EGLint n_rects);
#यदि_अन्तः
#यदि_अन्तः /* EGL_EXT_swap_buffers_with_damage */

#यदि_अपरिभाषितम् EGL_EXT_sync_reuse
#परिभाषय EGL_EXT_sync_reuse 1
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLUNSIGNALSYNCEXTPROC) (EGLDisplay dpy, EGLSync sync, ध्रुव EGLAttrib *attrib_list);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglUnsignalSyncEXT (EGLDisplay dpy, EGLSync sync, ध्रुव EGLAttrib *attrib_list);
#यदि_अन्तः
#यदि_अन्तः /* EGL_EXT_sync_reuse */

#यदि_अपरिभाषितम् EGL_EXT_yuv_surface
#परिभाषय EGL_EXT_yuv_surface 1
#परिभाषय EGL_YUV_क्रमः_EXT                 0x3301
#परिभाषय EGL_YUV_सङ्ख्या_सम्बन्धि_PLANES_EXT      0x3311
#परिभाषय EGL_YUV_SUBSAMPLE_EXT             0x3312
#परिभाषय EGL_YUV_गभीरता_RANGE_EXT           0x3317
#परिभाषय EGL_YUV_CSC_STANDARD_EXT          0x330A
#परिभाषय EGL_YUV_PLANE_BPP_EXT             0x331A
#परिभाषय EGL_YUV_बफर_EXT                0x3300
#परिभाषय EGL_YUV_क्रमः_YUV_EXT             0x3302
#परिभाषय EGL_YUV_क्रमः_YVU_EXT             0x3303
#परिभाषय EGL_YUV_क्रमः_YUYV_EXT            0x3304
#परिभाषय EGL_YUV_क्रमः_UYVY_EXT            0x3305
#परिभाषय EGL_YUV_क्रमः_YVYU_EXT            0x3306
#परिभाषय EGL_YUV_क्रमः_VYUY_EXT            0x3307
#परिभाषय EGL_YUV_क्रमः_AYUV_EXT            0x3308
#परिभाषय EGL_YUV_SUBSAMPLE_4_2_0_EXT       0x3313
#परिभाषय EGL_YUV_SUBSAMPLE_4_2_2_EXT       0x3314
#परिभाषय EGL_YUV_SUBSAMPLE_4_4_4_EXT       0x3315
#परिभाषय EGL_YUV_गभीरता_RANGE_LIMITED_EXT   0x3318
#परिभाषय EGL_YUV_गभीरता_RANGE_पूर्णम्_EXT      0x3319
#परिभाषय EGL_YUV_CSC_STANDARD_601_EXT      0x330B
#परिभाषय EGL_YUV_CSC_STANDARD_709_EXT      0x330C
#परिभाषय EGL_YUV_CSC_STANDARD_2020_EXT     0x330D
#परिभाषय EGL_YUV_PLANE_BPP_0_EXT           0x331B
#परिभाषय EGL_YUV_PLANE_BPP_8_EXT           0x331C
#परिभाषय EGL_YUV_PLANE_BPP_10_EXT          0x331D
#यदि_अन्तः /* EGL_EXT_yuv_surface */

#यदि_अपरिभाषितम् EGL_HI_clientpixmap
#परिभाषय EGL_HI_clientpixmap 1
संरचना EGLClientPixmapHI {
    शून्य  *p_दत्त;
    EGLint i_विस्तारः;
    EGLint iHeight;
    EGLint iStride;
};
#परिभाषय EGL_CLIENT_PIXMAP_POINTER_HI      0x8F74
प्रकारनिर्देश EGLSurface (EGLAPIENTRYP PFNEGLCREATEPIXMAPSURFACEHIPROC) (EGLDisplay dpy, EGLConfig config, संरचना EGLClientPixmapHI *pixmap);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSurface EGLAPIENTRY eglCreatePixmapSurfaceHI (EGLDisplay dpy, EGLConfig config, संरचना EGLClientPixmapHI *pixmap);
#यदि_अन्तः
#यदि_अन्तः /* EGL_HI_clientpixmap */

#यदि_अपरिभाषितम् EGL_HI_colorformats
#परिभाषय EGL_HI_colorformats 1
#परिभाषय EGL_COLOR_FORMAT_HI               0x8F70
#परिभाषय EGL_COLOR_RGB_HI                  0x8F71
#परिभाषय EGL_COLOR_RGBA_HI                 0x8F72
#परिभाषय EGL_COLOR_ARGB_HI                 0x8F73
#यदि_अन्तः /* EGL_HI_colorformats */

#यदि_अपरिभाषितम् EGL_IMG_context_प्राथमिकता
#परिभाषय EGL_IMG_context_प्राथमिकता 1
#परिभाषय EGL_CONTEXT_प्राथमिकता_LEVEL_IMG    0x3100
#परिभाषय EGL_CONTEXT_प्राथमिकता_उच्चः_IMG     0x3101
#परिभाषय EGL_CONTEXT_प्राथमिकता_MEDIUM_IMG   0x3102
#परिभाषय EGL_CONTEXT_प्राथमिकता_नीचः_IMG      0x3103
#यदि_अन्तः /* EGL_IMG_context_priority */

#यदि_अपरिभाषितम् EGL_IMG_image_plane_attribs
#परिभाषय EGL_IMG_image_plane_attribs 1
#परिभाषय EGL_NATIVE_बफर_MULTIPLANE_SEPARATE_IMG 0x3105
#परिभाषय EGL_NATIVE_बफर_PLANE_विस्थापनम्_IMG 0x3106
#यदि_अन्तः /* EGL_IMG_image_plane_attribs */

#यदि_अपरिभाषितम् EGL_MESA_drm_image
#परिभाषय EGL_MESA_drm_image 1
#परिभाषय EGL_DRM_बफर_FORMAT_MESA        0x31D0
#परिभाषय EGL_DRM_बफर_USE_MESA           0x31D1
#परिभाषय EGL_DRM_बफर_FORMAT_ARGB32_MESA 0x31D2
#परिभाषय EGL_DRM_बफर_MESA               0x31D3
#परिभाषय EGL_DRM_बफर_STRIDE_MESA        0x31D4
#परिभाषय EGL_DRM_बफर_USE_SCANOUT_MESA   0x00000001
#परिभाषय EGL_DRM_बफर_USE_SHARE_MESA     0x00000002
#परिभाषय EGL_DRM_बफर_USE_CURSOR_MESA    0x00000004
प्रकारनिर्देश EGLImageKHR (EGLAPIENTRYP PFNEGLCREATEDRMIMAGEMESAPROC) (EGLDisplay dpy, ध्रुव EGLint *attrib_list);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLEXPORTDRMIMAGEMESAPROC) (EGLDisplay dpy, EGLImageKHR image, EGLint *name, EGLint *handle, EGLint *stride);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLImageKHR EGLAPIENTRY eglCreateDRMImageMESA (EGLDisplay dpy, ध्रुव EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglExportDRMImageMESA (EGLDisplay dpy, EGLImageKHR image, EGLint *name, EGLint *handle, EGLint *stride);
#यदि_अन्तः
#यदि_अन्तः /* EGL_MESA_drm_image */

#यदि_अपरिभाषितम् EGL_MESA_image_dma_buf_export
#परिभाषय EGL_MESA_image_dma_buf_export 1
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLEXPORTDMABUFIMAGEQUERYMESAPROC) (EGLDisplay dpy, EGLImageKHR image, पूर्णाङ्क *fourcc, पूर्णाङ्क *अङ्कः_planes, EGLuint64KHR *modifiers);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLEXPORTDMABUFIMAGEMESAPROC) (EGLDisplay dpy, EGLImageKHR image, पूर्णाङ्क *fds, EGLint *strides, EGLint *offsets);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglExportDMABUFImageQueryMESA (EGLDisplay dpy, EGLImageKHR image, पूर्णाङ्क *fourcc, पूर्णाङ्क *अङ्कः_planes, EGLuint64KHR *modifiers);
EGLAPI EGLBoolean EGLAPIENTRY eglExportDMABUFImageMESA (EGLDisplay dpy, EGLImageKHR image, पूर्णाङ्क *fds, EGLint *strides, EGLint *offsets);
#यदि_अन्तः
#यदि_अन्तः /* EGL_MESA_image_dma_buf_export */

#यदि_अपरिभाषितम् EGL_MESA_platform_gbm
#परिभाषय EGL_MESA_platform_gbm 1
#परिभाषय EGL_PLATFORM_GBM_MESA             0x31D7
#यदि_अन्तः /* EGL_MESA_platform_gbm */

#यदि_अपरिभाषितम् EGL_MESA_platform_surfaceless
#परिभाषय EGL_MESA_platform_surfaceless 1
#परिभाषय EGL_PLATFORM_SURFACELESS_MESA     0x31DD
#यदि_अन्तः /* EGL_MESA_platform_surfaceless */

#यदि_अपरिभाषितम् EGL_MESA_query_driver
#परिभाषय EGL_MESA_query_driver 1
प्रकारनिर्देश वर्ण *(EGLAPIENTRYP PFNEGLGETDISPLAYDRIVERCONFIGPROC) (EGLDisplay dpy);
प्रकारनिर्देश ध्रुव वर्ण *(EGLAPIENTRYP PFNEGLGETDISPLAYDRIVERNAMEPROC) (EGLDisplay dpy);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI वर्ण *EGLAPIENTRY eglGetDisplayDriverConfig (EGLDisplay dpy);
EGLAPI ध्रुव वर्ण *EGLAPIENTRY eglGetDisplayDriverName (EGLDisplay dpy);
#यदि_अन्तः
#यदि_अन्तः /* EGL_MESA_query_driver */

#यदि_अपरिभाषितम् EGL_NOK_swap_region
#परिभाषय EGL_NOK_swap_region 1
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSREGIONNOKPROC) (EGLDisplay dpy, EGLSurface surface, EGLint अङ्कः_Rects_2, ध्रुव EGLint *rects);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglSwapBuffersRegionNOK (EGLDisplay dpy, EGLSurface surface, EGLint अङ्कः_Rects_2, ध्रुव EGLint *rects);
#यदि_अन्तः
#यदि_अन्तः /* EGL_NOK_swap_region */

#यदि_अपरिभाषितम् EGL_NOK_swap_region2
#परिभाषय EGL_NOK_swap_region2 1
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSREGION2NOKPROC) (EGLDisplay dpy, EGLSurface surface, EGLint अङ्कः_Rects_2, ध्रुव EGLint *rects);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglSwapBuffersRegion2NOK (EGLDisplay dpy, EGLSurface surface, EGLint अङ्कः_Rects_2, ध्रुव EGLint *rects);
#यदि_अन्तः
#यदि_अन्तः /* EGL_NOK_swap_region2 */

#यदि_अपरिभाषितम् EGL_NOK_texture_from_pixmap
#परिभाषय EGL_NOK_texture_from_pixmap 1
#परिभाषय EGL_Y_INVERTED_NOK                0x307F
#यदि_अन्तः /* EGL_NOK_texture_from_pixmap */

#यदि_अपरिभाषितम् EGL_NV_3dvision_surface
#परिभाषय EGL_NV_3dvision_surface 1
#परिभाषय EGL_AUTO_STEREO_NV                0x3136
#यदि_अन्तः /* EGL_NV_3dvision_surface */

#यदि_अपरिभाषितम् EGL_NV_context_प्राथमिकता_realtime
#परिभाषय EGL_NV_context_प्राथमिकता_realtime 1
#परिभाषय EGL_CONTEXT_प्राथमिकता_REALTIME_NV  0x3357
#यदि_अन्तः /* EGL_NV_context_priority_realtime */

#यदि_अपरिभाषितम् EGL_NV_coverage_sample
#परिभाषय EGL_NV_coverage_sample 1
#परिभाषय EGL_COVERAGE_BUFFERS_NV           0x30E0
#परिभाषय EGL_COVERAGE_SAMPLES_NV           0x30E1
#यदि_अन्तः /* EGL_NV_coverage_sample */

#यदि_अपरिभाषितम् EGL_NV_coverage_sample_resolve
#परिभाषय EGL_NV_coverage_sample_resolve 1
#परिभाषय EGL_COVERAGE_SAMPLE_RESOLVE_NV    0x3131
#परिभाषय EGL_COVERAGE_SAMPLE_RESOLVE_DEFAULT_NV 0x3132
#परिभाषय EGL_COVERAGE_SAMPLE_RESOLVE_NONE_NV 0x3133
#यदि_अन्तः /* EGL_NV_coverage_sample_resolve */

#यदि_अपरिभाषितम् EGL_NV_cuda_event
#परिभाषय EGL_NV_cuda_event 1
#परिभाषय EGL_CUDA_EVENT_HANDLE_NV          0x323B
#परिभाषय EGL_SYNC_CUDA_EVENT_NV            0x323C
#परिभाषय EGL_SYNC_CUDA_EVENT_COMPLETE_NV   0x323D
#यदि_अन्तः /* EGL_NV_cuda_event */

#यदि_अपरिभाषितम् EGL_NV_गभीरता_nonlinear
#परिभाषय EGL_NV_गभीरता_nonlinear 1
#परिभाषय EGL_गभीरता_ENCODING_NV             0x30E2
#परिभाषय EGL_गभीरता_ENCODING_NONE_NV        0
#परिभाषय EGL_गभीरता_ENCODING_NONLINEAR_NV   0x30E3
#यदि_अन्तः /* EGL_NV_depth_nonlinear */

#यदि_अपरिभाषितम् EGL_NV_device_cuda
#परिभाषय EGL_NV_device_cuda 1
#परिभाषय EGL_CUDA_DEVICE_NV                0x323A
#यदि_अन्तः /* EGL_NV_device_cuda */

#यदि_अपरिभाषितम् EGL_NV_native_query
#परिभाषय EGL_NV_native_query 1
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLQUERYNATIVEDISPLAYNVPROC) (EGLDisplay dpy, EGLNativeDisplayType *display_id);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLQUERYNATIVEWINDOWNVPROC) (EGLDisplay dpy, EGLSurface surf, EGLNative_गवाक्षः_Type *गवाक्षः);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLQUERYNATIVEPIXMAPNVPROC) (EGLDisplay dpy, EGLSurface surf, EGLNativePixmapType *pixmap);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryNativeDisplayNV (EGLDisplay dpy, EGLNativeDisplayType *display_id);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Native_गवाक्षः_NV (EGLDisplay dpy, EGLSurface surf, EGLNative_गवाक्षः_Type *गवाक्षः);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryNativePixmapNV (EGLDisplay dpy, EGLSurface surf, EGLNativePixmapType *pixmap);
#यदि_अन्तः
#यदि_अन्तः /* EGL_NV_native_query */

#यदि_अपरिभाषितम् EGL_NV_post_convert_rounding
#परिभाषय EGL_NV_post_convert_rounding 1
#यदि_अन्तः /* EGL_NV_post_convert_rounding */

#यदि_अपरिभाषितम् EGL_NV_post_sub_बफर
#परिभाषय EGL_NV_post_sub_बफर 1
#परिभाषय EGL_POST_SUB_बफर_SUPPORTED_NV  0x30BE
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLPOSTSUBBUFFERNVPROC) (EGLDisplay dpy, EGLSurface surface, EGLint x, EGLint y, EGLint विस्तारः, EGLint height);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Post_Sub_बफर_NV (EGLDisplay dpy, EGLSurface surface, EGLint x, EGLint y, EGLint विस्तारः, EGLint height);
#यदि_अन्तः
#यदि_अन्तः /* EGL_NV_post_sub_buffer */

#यदि_अपरिभाषितम् EGL_NV_quadruple_बफर
#परिभाषय EGL_NV_quadruple_बफर 1
#परिभाषय EGL_QUADRUPLE_बफर_NV           0x3231
#यदि_अन्तः /* EGL_NV_quadruple_buffer */

#यदि_अपरिभाषितम् EGL_NV_robustness_video_स्मृतिः_purge
#परिभाषय EGL_NV_robustness_video_स्मृतिः_purge 1
#परिभाषय EGL_GENERATE_RESET_ON_VIDEO_स्मृतिः_PURGE_NV 0x334C
#यदि_अन्तः /* EGL_NV_robustness_video_memory_purge */

#यदि_अपरिभाषितम् EGL_NV_प्रवाहः_उपभोक्ता_eglimage
#परिभाषय EGL_NV_प्रवाहः_उपभोक्ता_eglimage 1
#परिभाषय EGL_प्रवाहः_उपभोक्ता_IMAGE_NV      0x3373
#परिभाषय EGL_प्रवाहः_IMAGE_सङ्कलय_NV           0x3374
#परिभाषय EGL_प्रवाहः_IMAGE_REMOVE_NV        0x3375
#परिभाषय EGL_प्रवाहः_IMAGE_उपलब्धम्_NV     0x3376
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMIMAGECONSUMERCONNECTNVPROC) (EGLDisplay dpy, EGLStreamKHR प्रवाहः, EGLint अङ्कः_modifiers, ध्रुव EGLuint64KHR *modifiers, ध्रुव EGLAttrib *attrib_list);
प्रकारनिर्देश EGLint (EGLAPIENTRYP PFNEGLQUERYSTREAMCONSUMEREVENTNVPROC) (EGLDisplay dpy, EGLStreamKHR प्रवाहः, EGLTime timeout, EGLenum *event, EGLAttrib *aux);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMACQUIREIMAGENVPROC) (EGLDisplay dpy, EGLStreamKHR प्रवाहः, EGLImage *pImage, EGLSync sync);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMRELEASEIMAGENVPROC) (EGLDisplay dpy, EGLStreamKHR प्रवाहः, EGLImage image, EGLSync sync);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_प्रवाहः_Image_उपभोक्ता_Connect_NV (EGLDisplay dpy, EGLStreamKHR प्रवाहः, EGLint अङ्कः_modifiers, ध्रुव EGLuint64KHR *modifiers, ध्रुव EGLAttrib *attrib_list);
EGLAPI EGLint EGLAPIENTRY egl_Query_प्रवाहः_उपभोक्ता_Event_NV (EGLDisplay dpy, EGLStreamKHR प्रवाहः, EGLTime timeout, EGLenum *event, EGLAttrib *aux);
EGLAPI EGLBoolean EGLAPIENTRY egl_प्रवाहः_Acquire_Image_NV (EGLDisplay dpy, EGLStreamKHR प्रवाहः, EGLImage *pImage, EGLSync sync);
EGLAPI EGLBoolean EGLAPIENTRY egl_प्रवाहः_Release_Image_NV (EGLDisplay dpy, EGLStreamKHR प्रवाहः, EGLImage image, EGLSync sync);
#यदि_अन्तः
#यदि_अन्तः /* EGL_NV_stream_consumer_eglimage */

#यदि_अपरिभाषितम् EGL_NV_प्रवाहः_उपभोक्ता_eglimage_use_scanout_attrib
#परिभाषय EGL_NV_प्रवाहः_उपभोक्ता_eglimage_use_scanout_attrib 1
#परिभाषय EGL_प्रवाहः_उपभोक्ता_IMAGE_USE_SCANOUT_NV 0x3378
#यदि_अन्तः /* EGL_NV_stream_consumer_eglimage_use_scanout_attrib */

#यदि_अपरिभाषितम् EGL_NV_प्रवाहः_उपभोक्ता_gltexture_yuv
#परिभाषय EGL_NV_प्रवाहः_उपभोक्ता_gltexture_yuv 1
#परिभाषय EGL_YUV_PLANE0_TEXTURE_UNIT_NV    0x332C
#परिभाषय EGL_YUV_PLANE1_TEXTURE_UNIT_NV    0x332D
#परिभाषय EGL_YUV_PLANE2_TEXTURE_UNIT_NV    0x332E
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALATTRIBSNVPROC) (EGLDisplay dpy, EGLStreamKHR प्रवाहः, ध्रुव EGLAttrib *attrib_list);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_प्रवाहः_उपभोक्ता_GLTexture_External_Attribs_NV (EGLDisplay dpy, EGLStreamKHR प्रवाहः, ध्रुव EGLAttrib *attrib_list);
#यदि_अन्तः
#यदि_अन्तः /* EGL_NV_stream_consumer_gltexture_yuv */

#यदि_अपरिभाषितम् EGL_NV_प्रवाहः_cross_display
#परिभाषय EGL_NV_प्रवाहः_cross_display 1
#परिभाषय EGL_प्रवाहः_CROSS_DISPLAY_NV       0x334E
#यदि_अन्तः /* EGL_NV_stream_cross_display */

#यदि_अपरिभाषितम् EGL_NV_प्रवाहः_cross_object
#परिभाषय EGL_NV_प्रवाहः_cross_object 1
#परिभाषय EGL_प्रवाहः_CROSS_OBJECT_NV        0x334D
#यदि_अन्तः /* EGL_NV_stream_cross_object */

#यदि_अपरिभाषितम् EGL_NV_प्रवाहः_cross_partition
#परिभाषय EGL_NV_प्रवाहः_cross_partition 1
#परिभाषय EGL_प्रवाहः_CROSS_PARTITION_NV     0x323F
#यदि_अन्तः /* EGL_NV_stream_cross_partition */

#यदि_अपरिभाषितम् EGL_NV_प्रवाहः_cross_process
#परिभाषय EGL_NV_प्रवाहः_cross_process 1
#परिभाषय EGL_प्रवाहः_CROSS_PROCESS_NV       0x3245
#यदि_अन्तः /* EGL_NV_stream_cross_process */

#यदि_अपरिभाषितम् EGL_NV_प्रवाहः_cross_system
#परिभाषय EGL_NV_प्रवाहः_cross_system 1
#परिभाषय EGL_प्रवाहः_CROSS_SYSTEM_NV        0x334F
#यदि_अन्तः /* EGL_NV_stream_cross_system */

#यदि_अपरिभाषितम् EGL_NV_प्रवाहः_dma
#परिभाषय EGL_NV_प्रवाहः_dma 1
#परिभाषय EGL_प्रवाहः_DMA_NV                 0x3371
#परिभाषय EGL_प्रवाहः_DMA_SERVER_NV          0x3372
#यदि_अन्तः /* EGL_NV_stream_dma */

#यदि_अपरिभाषितम् EGL_NV_प्रवाहः_fifo_अग्र
#परिभाषय EGL_NV_प्रवाहः_fifo_अग्र 1
#परिभाषय EGL_PENDING_FRAME_NV              0x3329
#परिभाषय EGL_प्रवाहः_TIME_PENDING_NV        0x332A
#यदि_अन्तः /* EGL_NV_stream_fifo_next */

#यदि_अपरिभाषितम् EGL_NV_प्रवाहः_fifo_synchronous
#परिभाषय EGL_NV_प्रवाहः_fifo_synchronous 1
#परिभाषय EGL_प्रवाहः_FIFO_SYNCHRONOUS_NV    0x3336
#यदि_अन्तः /* EGL_NV_stream_fifo_synchronous */

#यदि_अपरिभाषितम् EGL_NV_प्रवाहः_flush
#परिभाषय EGL_NV_प्रवाहः_flush 1
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMFLUSHNVPROC) (EGLDisplay dpy, EGLStreamKHR प्रवाहः);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_प्रवाहः_Flush_NV (EGLDisplay dpy, EGLStreamKHR प्रवाहः);
#यदि_अन्तः
#यदि_अन्तः /* EGL_NV_stream_flush */

#यदि_अपरिभाषितम् EGL_NV_प्रवाहः_frame_limits
#परिभाषय EGL_NV_प्रवाहः_frame_limits 1
#परिभाषय EGL_उत्पादकः_MAX_FRAME_HINT_NV    0x3337
#परिभाषय EGL_उपभोक्ता_MAX_FRAME_HINT_NV    0x3338
#यदि_अन्तः /* EGL_NV_stream_frame_limits */

#यदि_अपरिभाषितम् EGL_NV_प्रवाहः_metadata
#परिभाषय EGL_NV_प्रवाहः_metadata 1
#परिभाषय EGL_MAX_प्रवाहः_METADATA_खण्डानि_NV 0x3250
#परिभाषय EGL_MAX_प्रवाहः_METADATA_खण्डम्_आकार_NV 0x3251
#परिभाषय EGL_MAX_प्रवाहः_METADATA_योग_आकार_NV 0x3252
#परिभाषय EGL_उत्पादकः_METADATA_NV          0x3253
#परिभाषय EGL_उपभोक्ता_METADATA_NV          0x3254
#परिभाषय EGL_PENDING_METADATA_NV           0x3328
#परिभाषय EGL_METADATA0_आकार_NV             0x3255
#परिभाषय EGL_METADATA1_आकार_NV             0x3256
#परिभाषय EGL_METADATA2_आकार_NV             0x3257
#परिभाषय EGL_METADATA3_आकार_NV             0x3258
#परिभाषय EGL_METADATA0_TYPE_NV             0x3259
#परिभाषय EGL_METADATA1_TYPE_NV             0x325A
#परिभाषय EGL_METADATA2_TYPE_NV             0x325B
#परिभाषय EGL_METADATA3_TYPE_NV             0x325C
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDISPLAYATTRIBNVPROC) (EGLDisplay dpy, EGLint attribute, EGLAttrib *मानम्);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLSETSTREAMMETADATANVPROC) (EGLDisplay dpy, EGLStreamKHR प्रवाहः, EGLint n, EGLint विस्थापनम्_2, EGLint आकार, ध्रुव शून्य *दत्त);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMMETADATANVPROC) (EGLDisplay dpy, EGLStreamKHR प्रवाहः, EGLenum name, EGLint n, EGLint विस्थापनम्_2, EGLint आकार, शून्य *दत्त);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDisplayAttribNV (EGLDisplay dpy, EGLint attribute, EGLAttrib *मानम्);
EGLAPI EGLBoolean EGLAPIENTRY egl_समुच्चयः_प्रवाहः_Metadata_NV (EGLDisplay dpy, EGLStreamKHR प्रवाहः, EGLint n, EGLint विस्थापनम्_2, EGLint आकार, ध्रुव शून्य *दत्त);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_प्रवाहः_Metadata_NV (EGLDisplay dpy, EGLStreamKHR प्रवाहः, EGLenum name, EGLint n, EGLint विस्थापनम्_2, EGLint आकार, शून्य *दत्त);
#यदि_अन्तः
#यदि_अन्तः /* EGL_NV_stream_metadata */

#यदि_अपरिभाषितम् EGL_NV_प्रवाहः_origin
#परिभाषय EGL_NV_प्रवाहः_origin 1
#परिभाषय EGL_प्रवाहः_FRAME_ORIGIN_X_NV      0x3366
#परिभाषय EGL_प्रवाहः_FRAME_ORIGIN_Y_NV      0x3367
#परिभाषय EGL_प्रवाहः_FRAME_MAJOR_AXIS_NV    0x3368
#परिभाषय EGL_उपभोक्ता_AUTO_ORIENTATION_NV  0x3369
#परिभाषय EGL_उत्पादकः_AUTO_ORIENTATION_NV  0x336A
#परिभाषय EGL_वामः_NV                       0x336B
#परिभाषय EGL_दक्षिणः_NV                      0x336C
#परिभाषय EGL_शिखरम्_NV                        0x336D
#परिभाषय EGL_BOTTOM_NV                     0x336E
#परिभाषय EGL_X_AXIS_NV                     0x336F
#परिभाषय EGL_Y_AXIS_NV                     0x3370
#यदि_अन्तः /* EGL_NV_stream_origin */

#यदि_अपरिभाषितम् EGL_NV_प्रवाहः_remote
#परिभाषय EGL_NV_प्रवाहः_remote 1
#परिभाषय EGL_प्रवाहः_STATE_INITIALIZING_NV  0x3240
#परिभाषय EGL_प्रवाहः_TYPE_NV                0x3241
#परिभाषय EGL_प्रवाहः_PROTOCOL_NV            0x3242
#परिभाषय EGL_प्रवाहः_ENDPOINT_NV            0x3243
#परिभाषय EGL_प्रवाहः_LOCAL_NV               0x3244
#परिभाषय EGL_प्रवाहः_उत्पादकः_NV            0x3247
#परिभाषय EGL_प्रवाहः_उपभोक्ता_NV            0x3248
#परिभाषय EGL_प्रवाहः_PROTOCOL_FD_NV         0x3246
#यदि_अन्तः /* EGL_NV_stream_remote */

#यदि_अपरिभाषितम् EGL_NV_प्रवाहः_reset
#परिभाषय EGL_NV_प्रवाहः_reset 1
#परिभाषय EGL_SUPPORT_RESET_NV              0x3334
#परिभाषय EGL_SUPPORT_REUSE_NV              0x3335
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLRESETSTREAMNVPROC) (EGLDisplay dpy, EGLStreamKHR प्रवाहः);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Reset_प्रवाहः_NV (EGLDisplay dpy, EGLStreamKHR प्रवाहः);
#यदि_अन्तः
#यदि_अन्तः /* EGL_NV_stream_reset */

#यदि_अपरिभाषितम् EGL_NV_प्रवाहः_socket
#परिभाषय EGL_NV_प्रवाहः_socket 1
#परिभाषय EGL_प्रवाहः_PROTOCOL_SOCKET_NV     0x324B
#परिभाषय EGL_SOCKET_HANDLE_NV              0x324C
#परिभाषय EGL_SOCKET_TYPE_NV                0x324D
#यदि_अन्तः /* EGL_NV_stream_socket */

#यदि_अपरिभाषितम् EGL_NV_प्रवाहः_socket_inet
#परिभाषय EGL_NV_प्रवाहः_socket_inet 1
#परिभाषय EGL_SOCKET_TYPE_INET_NV           0x324F
#यदि_अन्तः /* EGL_NV_stream_socket_inet */

#यदि_अपरिभाषितम् EGL_NV_प्रवाहः_socket_unix
#परिभाषय EGL_NV_प्रवाहः_socket_unix 1
#परिभाषय EGL_SOCKET_TYPE_UNIX_NV           0x324E
#यदि_अन्तः /* EGL_NV_stream_socket_unix */

#यदि_अपरिभाषितम् EGL_NV_प्रवाहः_sync
#परिभाषय EGL_NV_प्रवाहः_sync 1
#परिभाषय EGL_SYNC_NEW_FRAME_NV             0x321F
प्रकारनिर्देश EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESTREAMSYNCNVPROC) (EGLDisplay dpy, EGLStreamKHR प्रवाहः, EGLenum type, ध्रुव EGLint *attrib_list);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncKHR EGLAPIENTRY egl_Create_प्रवाहः_Sync_NV (EGLDisplay dpy, EGLStreamKHR प्रवाहः, EGLenum type, ध्रुव EGLint *attrib_list);
#यदि_अन्तः
#यदि_अन्तः /* EGL_NV_stream_sync */

#यदि_अपरिभाषितम् EGL_NV_sync
#परिभाषय EGL_NV_sync 1
प्रकारनिर्देश शून्य *EGLSyncNV;
प्रकारनिर्देश khronos_utime_nanoseconds_t EGLTimeNV;
#यदि_परिभाषितम् KHRONOS_SUPPORT_INT64
#परिभाषय EGL_SYNC_प्राक्_COMMANDS_COMPLETE_NV 0x30E6
#परिभाषय EGL_SYNC_स्थितिः_NV                0x30E7
#परिभाषय EGL_SIGNALED_NV                   0x30E8
#परिभाषय EGL_UNSIGNALED_NV                 0x30E9
#परिभाषय EGL_SYNC_FLUSH_COMMANDS_BIT_NV    0x0001
#परिभाषय EGL_FOREVER_NV                    0xFFFFFFFFFFFFFFFFull
#परिभाषय EGL_ALREADY_SIGNALED_NV           0x30EA
#परिभाषय EGL_TIMEOUT_EXPIRED_NV            0x30EB
#परिभाषय EGL_CONDITION_SATISFIED_NV        0x30EC
#परिभाषय EGL_SYNC_TYPE_NV                  0x30ED
#परिभाषय EGL_SYNC_CONDITION_NV             0x30EE
#परिभाषय EGL_SYNC_FENCE_NV                 0x30EF
#परिभाषय EGL_NO_SYNC_NV                    EGL_CAST(EGLSyncNV,0)
प्रकारनिर्देश EGLSyncNV (EGLAPIENTRYP PFNEGLCREATEFENCESYNCNVPROC) (EGLDisplay dpy, EGLenum condition, ध्रुव EGLint *attrib_list);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCNVPROC) (EGLSyncNV sync);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLFENCENVPROC) (EGLSyncNV sync);
प्रकारनिर्देश EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCNVPROC) (EGLSyncNV sync, EGLint flags, EGLTimeNV timeout);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLSIGNALSYNCNVPROC) (EGLSyncNV sync, EGLenum बहुलकम्);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLGETSYNCATTRIBNVPROC) (EGLSyncNV sync, EGLint attribute, EGLint *मानम्);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncNV EGLAPIENTRY eglCreateFenceSyncNV (EGLDisplay dpy, EGLenum condition, ध्रुव EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySyncNV (EGLSyncNV sync);
EGLAPI EGLBoolean EGLAPIENTRY eglFenceNV (EGLSyncNV sync);
EGLAPI EGLint EGLAPIENTRY eglClientWaitSyncNV (EGLSyncNV sync, EGLint flags, EGLTimeNV timeout);
EGLAPI EGLBoolean EGLAPIENTRY eglSignalSyncNV (EGLSyncNV sync, EGLenum बहुलकम्);
EGLAPI EGLBoolean EGLAPIENTRY eglGetSyncAttribNV (EGLSyncNV sync, EGLint attribute, EGLint *मानम्);
#यदि_अन्तः
#यदि_अन्तः /* KHRONOS_SUPPORT_INT64 */
#यदि_अन्तः /* EGL_NV_sync */

#यदि_अपरिभाषितम् EGL_NV_system_time
#परिभाषय EGL_NV_system_time 1
प्रकारनिर्देश khronos_utime_nanoseconds_t EGLuint64NV;
#यदि_परिभाषितम् KHRONOS_SUPPORT_INT64
प्रकारनिर्देश EGLuint64NV (EGLAPIENTRYP PFNEGLGETSYSTEMTIMEFREQUENCYNVPROC) (शून्य);
प्रकारनिर्देश EGLuint64NV (EGLAPIENTRYP PFNEGLGETSYSTEMTIMENVPROC) (शून्य);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLuint64NV EGLAPIENTRY eglGetSystemTimeFrequencyNV (शून्य);
EGLAPI EGLuint64NV EGLAPIENTRY eglGetSystemTimeNV (शून्य);
#यदि_अन्तः
#यदि_अन्तः /* KHRONOS_SUPPORT_INT64 */
#यदि_अन्तः /* EGL_NV_system_time */

#यदि_अपरिभाषितम् EGL_NV_triple_बफर
#परिभाषय EGL_NV_triple_बफर 1
#परिभाषय EGL_TRIPLE_बफर_NV              0x3230
#यदि_अन्तः /* EGL_NV_triple_buffer */

#यदि_अपरिभाषितम् EGL_QNX_image_native_बफर
#परिभाषय EGL_QNX_image_native_बफर 1
#परिभाषय EGL_NATIVE_बफर_QNX             0x3551
#यदि_अन्तः /* EGL_QNX_image_native_buffer */

#यदि_अपरिभाषितम् EGL_QNX_platform_screen
#परिभाषय EGL_QNX_platform_screen 1
#परिभाषय EGL_PLATFORM_SCREEN_QNX           0x3550
#यदि_अन्तः /* EGL_QNX_platform_screen */

#यदि_अपरिभाषितम् EGL_TIZEN_image_native_बफर
#परिभाषय EGL_TIZEN_image_native_बफर 1
#परिभाषय EGL_NATIVE_बफर_TIZEN           0x32A0
#यदि_अन्तः /* EGL_TIZEN_image_native_buffer */

#यदि_अपरिभाषितम् EGL_TIZEN_image_native_surface
#परिभाषय EGL_TIZEN_image_native_surface 1
#परिभाषय EGL_NATIVE_SURFACE_TIZEN          0x32A1
#यदि_अन्तः /* EGL_TIZEN_image_native_surface */

#यदि_अपरिभाषितम् EGL_WL_bind_wayland_display
#परिभाषय EGL_WL_bind_wayland_display 1
#परिभाषय PFNEGLBINDWAYLANDDISPLAYWL PFNEGLBINDWAYLANDDISPLAYWLPROC
#परिभाषय PFNEGLUNBINDWAYLANDDISPLAYWL PFNEGLUNBINDWAYLANDDISPLAYWLPROC
#परिभाषय PFNEGLQUERYWAYLANDBUFFERWL PFNEGLQUERYWAYLANDBUFFERWLPROC
संरचना wl_display;
संरचना wl_resource;
#परिभाषय EGL_WAYLAND_बफर_WL             0x31D5
#परिभाषय EGL_WAYLAND_PLANE_WL              0x31D6
#परिभाषय EGL_TEXTURE_Y_U_V_WL              0x31D7
#परिभाषय EGL_TEXTURE_Y_UV_WL               0x31D8
#परिभाषय EGL_TEXTURE_Y_XUXV_WL             0x31D9
#परिभाषय EGL_TEXTURE_EXTERNAL_WL           0x31DA
#परिभाषय EGL_WAYLAND_Y_INVERTED_WL         0x31DB
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLBINDWAYLANDDISPLAYWLPROC) (EGLDisplay dpy, संरचना wl_display *display);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLUNBINDWAYLANDDISPLAYWLPROC) (EGLDisplay dpy, संरचना wl_display *display);
प्रकारनिर्देश EGLBoolean (EGLAPIENTRYP PFNEGLQUERYWAYLANDBUFFERWLPROC) (EGLDisplay dpy, संरचना wl_resource *बफर_2, EGLint attribute, EGLint *मानम्);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglBindWaylandDisplayWL (EGLDisplay dpy, संरचना wl_display *display);
EGLAPI EGLBoolean EGLAPIENTRY eglUnbindWaylandDisplayWL (EGLDisplay dpy, संरचना wl_display *display);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Wayland_बफर_WL (EGLDisplay dpy, संरचना wl_resource *बफर_2, EGLint attribute, EGLint *मानम्);
#यदि_अन्तः
#यदि_अन्तः /* EGL_WL_bind_wayland_display */

#यदि_अपरिभाषितम् EGL_WL_create_wayland_बफर_from_image
#परिभाषय EGL_WL_create_wayland_बफर_from_image 1
#परिभाषय PFNEGLCREATEWAYLANDBUFFERFROMIMAGEWL PFNEGLCREATEWAYLANDBUFFERFROMIMAGEWLPROC
संरचना wl_बफर;
प्रकारनिर्देश संरचना wl_बफर *(EGLAPIENTRYP PFNEGLCREATEWAYLANDBUFFERFROMIMAGEWLPROC) (EGLDisplay dpy, EGLImageKHR image);
#यदि_परिभाषितम् EGL_EGLEXT_PROTOTYPES
EGLAPI संरचना wl_बफर *EGLAPIENTRY egl_Create_Wayland_बफर_From_Image_WL (EGLDisplay dpy, EGLImageKHR image);
#यदि_अन्तः
#यदि_अन्तः /* EGL_WL_create_wayland_buffer_from_image */

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः
