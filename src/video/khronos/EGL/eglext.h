#अगर_अघोषित __eglext_h_
#घोषणा __eglext_h_ 1

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

#घोषणा EGL_EGLEXT_VERSION 20260319

/* Generated C header for:
 * API: egl
 * Versions considered: .*
 * Versions emitted: _nomatch_^
 * Default extensions included: egl
 * Additional extensions included: _nomatch_^
 * Extensions removed: _nomatch_^
 */

#अगर_अघोषित EGL_KHR_cl_event
#घोषणा EGL_KHR_cl_event 1
#घोषणा EGL_CL_EVENT_HANDLE_KHR           0x309C
#घोषणा EGL_SYNC_CL_EVENT_KHR             0x30FE
#घोषणा EGL_SYNC_CL_EVENT_COMPLETE_KHR    0x30FF
#पूर्ण_अगर /* EGL_KHR_cl_event */

#अगर_अघोषित EGL_KHR_cl_event2
#घोषणा EGL_KHR_cl_event2 1
प्रकार व्योम *EGLSyncKHR;
प्रकार intptr_t EGLAttribKHR;
प्रकार EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESYNC64KHRPROC) (EGLDisplay dpy, EGLenum type, स्थिर EGLAttribKHR *attrib_list);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncKHR EGLAPIENTRY eglCreateSync64KHR (EGLDisplay dpy, EGLenum type, स्थिर EGLAttribKHR *attrib_list);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_KHR_cl_event2 */

#अगर_अघोषित EGL_KHR_client_get_all_proc_addresses
#घोषणा EGL_KHR_client_get_all_proc_addresses 1
#पूर्ण_अगर /* EGL_KHR_client_get_all_proc_addresses */

#अगर_अघोषित EGL_KHR_config_attribs
#घोषणा EGL_KHR_config_attribs 1
#घोषणा EGL_CONFORMANT_KHR                0x3042
#घोषणा EGL_VG_COLORSPACE_LINEAR_BIT_KHR  0x0020
#घोषणा EGL_VG_ALPHA_FORMAT_PRE_BIT_KHR   0x0040
#पूर्ण_अगर /* EGL_KHR_config_attribs */

#अगर_अघोषित EGL_KHR_context_flush_control
#घोषणा EGL_KHR_context_flush_control 1
#घोषणा EGL_CONTEXT_RELEASE_BEHAVIOR_NONE_KHR 0
#घोषणा EGL_CONTEXT_RELEASE_BEHAVIOR_KHR  0x2097
#घोषणा EGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_KHR 0x2098
#पूर्ण_अगर /* EGL_KHR_context_flush_control */

#अगर_अघोषित EGL_KHR_create_context
#घोषणा EGL_KHR_create_context 1
#घोषणा EGL_CONTEXT_MAJOR_VERSION_KHR     0x3098
#घोषणा EGL_CONTEXT_MINOR_VERSION_KHR     0x30FB
#घोषणा EGL_CONTEXT_FLAGS_KHR             0x30FC
#घोषणा EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR 0x30FD
#घोषणा EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_KHR 0x31BD
#घोषणा EGL_NO_RESET_NOTIFICATION_KHR     0x31BE
#घोषणा EGL_LOSE_CONTEXT_ON_RESET_KHR     0x31BF
#घोषणा EGL_CONTEXT_OPENGL_DEBUG_BIT_KHR  0x00000001
#घोषणा EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR 0x00000002
#घोषणा EGL_CONTEXT_OPENGL_ROBUST_ACCESS_BIT_KHR 0x00000004
#घोषणा EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR 0x00000001
#घोषणा EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR 0x00000002
#घोषणा EGL_OPENGL_ES3_BIT_KHR            0x00000040
#पूर्ण_अगर /* EGL_KHR_create_context */

#अगर_अघोषित EGL_KHR_create_context_no_error
#घोषणा EGL_KHR_create_context_no_error 1
#घोषणा EGL_CONTEXT_OPENGL_NO_ERROR_KHR   0x31B3
#पूर्ण_अगर /* EGL_KHR_create_context_no_error */

#अगर_अघोषित EGL_KHR_debug
#घोषणा EGL_KHR_debug 1
प्रकार व्योम *EGLLabelKHR;
प्रकार व्योम *EGLObjectKHR;
प्रकार व्योम (EGLAPIENTRY  *EGLDEBUGPROCKHR)(EGLenum error,स्थिर अक्षर *command,EGLint messageType,EGLLabelKHR threadLabel,EGLLabelKHR objectLabel,स्थिर अक्षर* message);
#घोषणा EGL_OBJECT_THREAD_KHR             0x33B0
#घोषणा EGL_OBJECT_DISPLAY_KHR            0x33B1
#घोषणा EGL_OBJECT_CONTEXT_KHR            0x33B2
#घोषणा EGL_OBJECT_SURFACE_KHR            0x33B3
#घोषणा EGL_OBJECT_IMAGE_KHR              0x33B4
#घोषणा EGL_OBJECT_SYNC_KHR               0x33B5
#घोषणा EGL_OBJECT_STREAM_KHR             0x33B6
#घोषणा EGL_DEBUG_संदेश_CRITICAL_KHR        0x33B9
#घोषणा EGL_DEBUG_संदेश_ERROR_KHR           0x33BA
#घोषणा EGL_DEBUG_संदेश_WARN_KHR            0x33BB
#घोषणा EGL_DEBUG_संदेश_INFO_KHR            0x33BC
#घोषणा EGL_DEBUG_CALLBACK_KHR            0x33B8
प्रकार EGLint (EGLAPIENTRYP PFNEGLDEBUGMESSAGECONTROLKHRPROC) (EGLDEBUGPROCKHR callback, स्थिर EGLAttrib *attrib_list);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEBUGKHRPROC) (EGLint attribute, EGLAttrib *मूल्य);
प्रकार EGLint (EGLAPIENTRYP PFNEGLLABELOBJECTKHRPROC) (EGLDisplay display, EGLenum objectType, EGLObjectKHR object, EGLLabelKHR label);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLint EGLAPIENTRY eglDebugMessageControlKHR (EGLDEBUGPROCKHR callback, स्थिर EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDebugKHR (EGLint attribute, EGLAttrib *मूल्य);
EGLAPI EGLint EGLAPIENTRY eglLabelObjectKHR (EGLDisplay display, EGLenum objectType, EGLObjectKHR object, EGLLabelKHR label);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_KHR_debug */

#अगर_अघोषित EGL_KHR_display_reference
#घोषणा EGL_KHR_display_reference 1
#घोषणा EGL_TRACK_REFERENCES_KHR          0x3352
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDISPLAYATTRIBKHRPROC) (EGLDisplay dpy, EGLint name, EGLAttrib *मूल्य);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDisplayAttribKHR (EGLDisplay dpy, EGLint name, EGLAttrib *मूल्य);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_KHR_display_reference */

#अगर_अघोषित EGL_KHR_fence_sync
#घोषणा EGL_KHR_fence_sync 1
प्रकार khronos_utime_nanoseconds_t EGLTimeKHR;
#अगर_घोषित KHRONOS_SUPPORT_INT64
#घोषणा EGL_SYNC_PRIOR_COMMANDS_COMPLETE_KHR 0x30F0
#घोषणा EGL_SYNC_CONDITION_KHR            0x30F8
#घोषणा EGL_SYNC_FENCE_KHR                0x30F9
प्रकार EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESYNCKHRPROC) (EGLDisplay dpy, EGLenum type, स्थिर EGLint *attrib_list);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync);
प्रकार EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLGETSYNCATTRIBKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint attribute, EGLint *मूल्य);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncKHR EGLAPIENTRY eglCreateSyncKHR (EGLDisplay dpy, EGLenum type, स्थिर EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySyncKHR (EGLDisplay dpy, EGLSyncKHR sync);
EGLAPI EGLint EGLAPIENTRY eglClientWaitSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);
EGLAPI EGLBoolean EGLAPIENTRY eglGetSyncAttribKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint attribute, EGLint *मूल्य);
#पूर्ण_अगर
#पूर्ण_अगर /* KHRONOS_SUPPORT_INT64 */
#पूर्ण_अगर /* EGL_KHR_fence_sync */

#अगर_अघोषित EGL_KHR_get_all_proc_addresses
#घोषणा EGL_KHR_get_all_proc_addresses 1
#पूर्ण_अगर /* EGL_KHR_get_all_proc_addresses */

#अगर_अघोषित EGL_KHR_gl_colorspace
#घोषणा EGL_KHR_gl_colorspace 1
#घोषणा EGL_GL_COLORSPACE_KHR             0x309D
#घोषणा EGL_GL_COLORSPACE_SRGB_KHR        0x3089
#घोषणा EGL_GL_COLORSPACE_LINEAR_KHR      0x308A
#पूर्ण_अगर /* EGL_KHR_gl_colorspace */

#अगर_अघोषित EGL_KHR_gl_renderbuffer_image
#घोषणा EGL_KHR_gl_renderbuffer_image 1
#घोषणा EGL_GL_RENDERBUFFER_KHR           0x30B9
#पूर्ण_अगर /* EGL_KHR_gl_renderbuffer_image */

#अगर_अघोषित EGL_KHR_gl_texture_2D_image
#घोषणा EGL_KHR_gl_texture_2D_image 1
#घोषणा EGL_GL_TEXTURE_2D_KHR             0x30B1
#घोषणा EGL_GL_TEXTURE_LEVEL_KHR          0x30BC
#पूर्ण_अगर /* EGL_KHR_gl_texture_2D_image */

#अगर_अघोषित EGL_KHR_gl_texture_3D_image
#घोषणा EGL_KHR_gl_texture_3D_image 1
#घोषणा EGL_GL_TEXTURE_3D_KHR             0x30B2
#घोषणा EGL_GL_TEXTURE_ZOFFSET_KHR        0x30BD
#पूर्ण_अगर /* EGL_KHR_gl_texture_3D_image */

#अगर_अघोषित EGL_KHR_gl_texture_cubemap_image
#घोषणा EGL_KHR_gl_texture_cubemap_image 1
#घोषणा EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_X_KHR 0x30B3
#घोषणा EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_X_KHR 0x30B4
#घोषणा EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_Y_KHR 0x30B5
#घोषणा EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_KHR 0x30B6
#घोषणा EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_Z_KHR 0x30B7
#घोषणा EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_KHR 0x30B8
#पूर्ण_अगर /* EGL_KHR_gl_texture_cubemap_image */

#अगर_अघोषित EGL_KHR_image
#घोषणा EGL_KHR_image 1
प्रकार व्योम *EGLImageKHR;
#घोषणा EGL_NATIVE_PIXMAP_KHR             0x30B0
#घोषणा EGL_NO_IMAGE_KHR                  EGL_CAST(EGLImageKHR,0)
प्रकार EGLImageKHR (EGLAPIENTRYP PFNEGLCREATEIMAGEKHRPROC) (EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClient_बफर बफर_2, स्थिर EGLint *attrib_list);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYIMAGEKHRPROC) (EGLDisplay dpy, EGLImageKHR image);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLImageKHR EGLAPIENTRY eglCreateImageKHR (EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClient_बफर बफर_2, स्थिर EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyImageKHR (EGLDisplay dpy, EGLImageKHR image);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_KHR_image */

#अगर_अघोषित EGL_KHR_image_base
#घोषणा EGL_KHR_image_base 1
#घोषणा EGL_IMAGE_PRESERVED_KHR           0x30D2
#पूर्ण_अगर /* EGL_KHR_image_base */

#अगर_अघोषित EGL_KHR_image_pixmap
#घोषणा EGL_KHR_image_pixmap 1
#पूर्ण_अगर /* EGL_KHR_image_pixmap */

#अगर_अघोषित EGL_KHR_lock_surface
#घोषणा EGL_KHR_lock_surface 1
#घोषणा EGL_READ_SURFACE_BIT_KHR          0x0001
#घोषणा EGL_WRITE_SURFACE_BIT_KHR         0x0002
#घोषणा EGL_LOCK_SURFACE_BIT_KHR          0x0080
#घोषणा EGL_OPTIMAL_FORMAT_BIT_KHR        0x0100
#घोषणा EGL_MATCH_FORMAT_KHR              0x3043
#घोषणा EGL_FORMAT_RGB_565_EXACT_KHR      0x30C0
#घोषणा EGL_FORMAT_RGB_565_KHR            0x30C1
#घोषणा EGL_FORMAT_RGBA_8888_EXACT_KHR    0x30C2
#घोषणा EGL_FORMAT_RGBA_8888_KHR          0x30C3
#घोषणा EGL_MAP_PRESERVE_PIXELS_KHR       0x30C4
#घोषणा EGL_LOCK_USAGE_HINT_KHR           0x30C5
#घोषणा EGL_BITMAP_POINTER_KHR            0x30C6
#घोषणा EGL_BITMAP_PITCH_KHR              0x30C7
#घोषणा EGL_BITMAP_ORIGIN_KHR             0x30C8
#घोषणा EGL_BITMAP_PIXEL_RED_OFFSET_KHR   0x30C9
#घोषणा EGL_BITMAP_PIXEL_GREEN_OFFSET_KHR 0x30CA
#घोषणा EGL_BITMAP_PIXEL_BLUE_OFFSET_KHR  0x30CB
#घोषणा EGL_BITMAP_PIXEL_ALPHA_OFFSET_KHR 0x30CC
#घोषणा EGL_BITMAP_PIXEL_LUMINANCE_OFFSET_KHR 0x30CD
#घोषणा EGL_LOWER_बायाँ_KHR                0x30CE
#घोषणा EGL_UPPER_बायाँ_KHR                0x30CF
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLLOCKSURFACEKHRPROC) (EGLDisplay dpy, EGLSurface surface, स्थिर EGLint *attrib_list);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLUNLOCKSURFACEKHRPROC) (EGLDisplay dpy, EGLSurface surface);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglLockSurfaceKHR (EGLDisplay dpy, EGLSurface surface, स्थिर EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglUnlockSurfaceKHR (EGLDisplay dpy, EGLSurface surface);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_KHR_lock_surface */

#अगर_अघोषित EGL_KHR_lock_surface2
#घोषणा EGL_KHR_lock_surface2 1
#घोषणा EGL_BITMAP_PIXEL_आकार_KHR         0x3110
#पूर्ण_अगर /* EGL_KHR_lock_surface2 */

#अगर_अघोषित EGL_KHR_lock_surface3
#घोषणा EGL_KHR_lock_surface3 1
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSURFACE64KHRPROC) (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLAttribKHR *मूल्य);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQuerySurface64KHR (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLAttribKHR *मूल्य);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_KHR_lock_surface3 */

#अगर_अघोषित EGL_KHR_mutable_render_बफर
#घोषणा EGL_KHR_mutable_render_बफर 1
#घोषणा EGL_MUTABLE_RENDER_बफर_BIT_KHR 0x1000
#पूर्ण_अगर /* EGL_KHR_mutable_render_buffer */

#अगर_अघोषित EGL_KHR_no_config_context
#घोषणा EGL_KHR_no_config_context 1
#घोषणा EGL_NO_CONFIG_KHR                 EGL_CAST(EGLConfig,0)
#पूर्ण_अगर /* EGL_KHR_no_config_context */

#अगर_अघोषित EGL_KHR_partial_update
#घोषणा EGL_KHR_partial_update 1
#घोषणा EGL_बफर_AGE_KHR                0x313D
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLSETDAMAGEREGIONKHRPROC) (EGLDisplay dpy, EGLSurface surface, EGLint *rects, EGLint n_rects);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglSetDamageRegionKHR (EGLDisplay dpy, EGLSurface surface, EGLint *rects, EGLint n_rects);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_KHR_partial_update */

#अगर_अघोषित EGL_KHR_platform_android
#घोषणा EGL_KHR_platform_android 1
#घोषणा EGL_PLATFORM_ANDROID_KHR          0x3141
#पूर्ण_अगर /* EGL_KHR_platform_android */

#अगर_अघोषित EGL_KHR_platform_gbm
#घोषणा EGL_KHR_platform_gbm 1
#घोषणा EGL_PLATFORM_GBM_KHR              0x31D7
#पूर्ण_अगर /* EGL_KHR_platform_gbm */

#अगर_अघोषित EGL_KHR_platform_wayland
#घोषणा EGL_KHR_platform_wayland 1
#घोषणा EGL_PLATFORM_WAYLAND_KHR          0x31D8
#पूर्ण_अगर /* EGL_KHR_platform_wayland */

#अगर_अघोषित EGL_KHR_platform_x11
#घोषणा EGL_KHR_platform_x11 1
#घोषणा EGL_PLATFORM_X11_KHR              0x31D5
#घोषणा EGL_PLATFORM_X11_SCREEN_KHR       0x31D6
#पूर्ण_अगर /* EGL_KHR_platform_x11 */

#अगर_अघोषित EGL_KHR_reusable_sync
#घोषणा EGL_KHR_reusable_sync 1
#अगर_घोषित KHRONOS_SUPPORT_INT64
#घोषणा EGL_SYNC_STATUS_KHR               0x30F1
#घोषणा EGL_SIGNALED_KHR                  0x30F2
#घोषणा EGL_UNSIGNALED_KHR                0x30F3
#घोषणा EGL_TIMEOUT_EXPIRED_KHR           0x30F5
#घोषणा EGL_CONDITION_SATISFIED_KHR       0x30F6
#घोषणा EGL_SYNC_TYPE_KHR                 0x30F7
#घोषणा EGL_SYNC_REUSABLE_KHR             0x30FA
#घोषणा EGL_SYNC_FLUSH_COMMANDS_BIT_KHR   0x0001
#घोषणा EGL_FOREVER_KHR                   0xFFFFFFFFFFFFFFFFull
#घोषणा EGL_NO_SYNC_KHR                   EGL_CAST(EGLSyncKHR,0)
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLSIGNALSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLenum mode);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglSignalSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLenum mode);
#पूर्ण_अगर
#पूर्ण_अगर /* KHRONOS_SUPPORT_INT64 */
#पूर्ण_अगर /* EGL_KHR_reusable_sync */

#अगर_अघोषित EGL_KHR_stream
#घोषणा EGL_KHR_stream 1
प्रकार व्योम *EGLStreamKHR;
प्रकार khronos_uint64_t EGLuint64KHR;
#अगर_घोषित KHRONOS_SUPPORT_INT64
#घोषणा EGL_NO_STREAM_KHR                 EGL_CAST(EGLStreamKHR,0)
#घोषणा EGL_CONSUMER_LATENCY_USEC_KHR     0x3210
#घोषणा EGL_PRODUCER_FRAME_KHR            0x3212
#घोषणा EGL_CONSUMER_FRAME_KHR            0x3213
#घोषणा EGL_STREAM_STATE_KHR              0x3214
#घोषणा EGL_STREAM_STATE_CREATED_KHR      0x3215
#घोषणा EGL_STREAM_STATE_CONNECTING_KHR   0x3216
#घोषणा EGL_STREAM_STATE_EMPTY_KHR        0x3217
#घोषणा EGL_STREAM_STATE_NEW_FRAME_AVAILABLE_KHR 0x3218
#घोषणा EGL_STREAM_STATE_OLD_FRAME_AVAILABLE_KHR 0x3219
#घोषणा EGL_STREAM_STATE_DISCONNECTED_KHR 0x321A
#घोषणा EGL_BAD_STREAM_KHR                0x321B
#घोषणा EGL_BAD_STATE_KHR                 0x321C
प्रकार EGLStreamKHR (EGLAPIENTRYP PFNEGLCREATESTREAMKHRPROC) (EGLDisplay dpy, स्थिर EGLint *attrib_list);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSTREAMKHRPROC) (EGLDisplay dpy, EGLStreamKHR stream);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR stream, EGLenum attribute, EGLint मूल्य);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMKHRPROC) (EGLDisplay dpy, EGLStreamKHR stream, EGLenum attribute, EGLint *मूल्य);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMU64KHRPROC) (EGLDisplay dpy, EGLStreamKHR stream, EGLenum attribute, EGLuint64KHR *मूल्य);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLStreamKHR EGLAPIENTRY eglCreateStreamKHR (EGLDisplay dpy, स्थिर EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyStreamKHR (EGLDisplay dpy, EGLStreamKHR stream);
EGLAPI EGLBoolean EGLAPIENTRY eglStreamAttribKHR (EGLDisplay dpy, EGLStreamKHR stream, EGLenum attribute, EGLint मूल्य);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryStreamKHR (EGLDisplay dpy, EGLStreamKHR stream, EGLenum attribute, EGLint *मूल्य);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryStreamu64KHR (EGLDisplay dpy, EGLStreamKHR stream, EGLenum attribute, EGLuint64KHR *मूल्य);
#पूर्ण_अगर
#पूर्ण_अगर /* KHRONOS_SUPPORT_INT64 */
#पूर्ण_अगर /* EGL_KHR_stream */

#अगर_अघोषित EGL_KHR_stream_attrib
#घोषणा EGL_KHR_stream_attrib 1
#अगर_घोषित KHRONOS_SUPPORT_INT64
प्रकार EGLStreamKHR (EGLAPIENTRYP PFNEGLCREATESTREAMATTRIBKHRPROC) (EGLDisplay dpy, स्थिर EGLAttrib *attrib_list);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLSETSTREAMATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR stream, EGLenum attribute, EGLAttrib मूल्य);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR stream, EGLenum attribute, EGLAttrib *मूल्य);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERACQUIREATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR stream, स्थिर EGLAttrib *attrib_list);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERRELEASEATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR stream, स्थिर EGLAttrib *attrib_list);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLStreamKHR EGLAPIENTRY eglCreateStreamAttribKHR (EGLDisplay dpy, स्थिर EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglSetStreamAttribKHR (EGLDisplay dpy, EGLStreamKHR stream, EGLenum attribute, EGLAttrib मूल्य);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryStreamAttribKHR (EGLDisplay dpy, EGLStreamKHR stream, EGLenum attribute, EGLAttrib *मूल्य);
EGLAPI EGLBoolean EGLAPIENTRY eglStreamConsumerAcquireAttribKHR (EGLDisplay dpy, EGLStreamKHR stream, स्थिर EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglStreamConsumerReleaseAttribKHR (EGLDisplay dpy, EGLStreamKHR stream, स्थिर EGLAttrib *attrib_list);
#पूर्ण_अगर
#पूर्ण_अगर /* KHRONOS_SUPPORT_INT64 */
#पूर्ण_अगर /* EGL_KHR_stream_attrib */

#अगर_अघोषित EGL_KHR_stream_consumer_gltexture
#घोषणा EGL_KHR_stream_consumer_gltexture 1
#अगर_घोषित EGL_KHR_stream
#घोषणा EGL_CONSUMER_ACQUIRE_TIMEOUT_USEC_KHR 0x321E
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALKHRPROC) (EGLDisplay dpy, EGLStreamKHR stream);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERACQUIREKHRPROC) (EGLDisplay dpy, EGLStreamKHR stream);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERRELEASEKHRPROC) (EGLDisplay dpy, EGLStreamKHR stream);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglStreamConsumerGLTextureExternalKHR (EGLDisplay dpy, EGLStreamKHR stream);
EGLAPI EGLBoolean EGLAPIENTRY eglStreamConsumerAcquireKHR (EGLDisplay dpy, EGLStreamKHR stream);
EGLAPI EGLBoolean EGLAPIENTRY eglStreamConsumerReleaseKHR (EGLDisplay dpy, EGLStreamKHR stream);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_KHR_stream */
#पूर्ण_अगर /* EGL_KHR_stream_consumer_gltexture */

#अगर_अघोषित EGL_KHR_stream_cross_process_fd
#घोषणा EGL_KHR_stream_cross_process_fd 1
प्रकार पूर्णांक EGLNativeFileDescriptorKHR;
#अगर_घोषित EGL_KHR_stream
#घोषणा EGL_NO_FILE_DESCRIPTOR_KHR        EGL_CAST(EGLNativeFileDescriptorKHR,-1)
प्रकार EGLNativeFileDescriptorKHR (EGLAPIENTRYP PFNEGLGETSTREAMFILEDESCRIPTORKHRPROC) (EGLDisplay dpy, EGLStreamKHR stream);
प्रकार EGLStreamKHR (EGLAPIENTRYP PFNEGLCREATESTREAMFROMFILEDESCRIPTORKHRPROC) (EGLDisplay dpy, EGLNativeFileDescriptorKHR file_descriptor);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLNativeFileDescriptorKHR EGLAPIENTRY eglGetStreamFileDescriptorKHR (EGLDisplay dpy, EGLStreamKHR stream);
EGLAPI EGLStreamKHR EGLAPIENTRY eglCreateStreamFromFileDescriptorKHR (EGLDisplay dpy, EGLNativeFileDescriptorKHR file_descriptor);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_KHR_stream */
#पूर्ण_अगर /* EGL_KHR_stream_cross_process_fd */

#अगर_अघोषित EGL_KHR_stream_fifo
#घोषणा EGL_KHR_stream_fifo 1
#अगर_घोषित EGL_KHR_stream
#घोषणा EGL_STREAM_FIFO_लंबाई_KHR        0x31FC
#घोषणा EGL_STREAM_TIME_NOW_KHR           0x31FD
#घोषणा EGL_STREAM_TIME_CONSUMER_KHR      0x31FE
#घोषणा EGL_STREAM_TIME_PRODUCER_KHR      0x31FF
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMTIMEKHRPROC) (EGLDisplay dpy, EGLStreamKHR stream, EGLenum attribute, EGLTimeKHR *मूल्य);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryStreamTimeKHR (EGLDisplay dpy, EGLStreamKHR stream, EGLenum attribute, EGLTimeKHR *मूल्य);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_KHR_stream */
#पूर्ण_अगर /* EGL_KHR_stream_fifo */

#अगर_अघोषित EGL_KHR_stream_producer_aldatalocator
#घोषणा EGL_KHR_stream_producer_aldatalocator 1
#अगर_घोषित EGL_KHR_stream
#पूर्ण_अगर /* EGL_KHR_stream */
#पूर्ण_अगर /* EGL_KHR_stream_producer_aldatalocator */

#अगर_अघोषित EGL_KHR_stream_producer_eglsurface
#घोषणा EGL_KHR_stream_producer_eglsurface 1
#अगर_घोषित EGL_KHR_stream
#घोषणा EGL_STREAM_BIT_KHR                0x0800
प्रकार EGLSurface (EGLAPIENTRYP PFNEGLCREATESTREAMPRODUCERSURFACEKHRPROC) (EGLDisplay dpy, EGLConfig config, EGLStreamKHR stream, स्थिर EGLint *attrib_list);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSurface EGLAPIENTRY eglCreateStreamProducerSurfaceKHR (EGLDisplay dpy, EGLConfig config, EGLStreamKHR stream, स्थिर EGLint *attrib_list);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_KHR_stream */
#पूर्ण_अगर /* EGL_KHR_stream_producer_eglsurface */

#अगर_अघोषित EGL_KHR_surfaceless_context
#घोषणा EGL_KHR_surfaceless_context 1
#पूर्ण_अगर /* EGL_KHR_surfaceless_context */

#अगर_अघोषित EGL_KHR_swap_buffers_with_damage
#घोषणा EGL_KHR_swap_buffers_with_damage 1
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSWITHDAMAGEKHRPROC) (EGLDisplay dpy, EGLSurface surface, स्थिर EGLint *rects, EGLint n_rects);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglSwapBuffersWithDamageKHR (EGLDisplay dpy, EGLSurface surface, स्थिर EGLint *rects, EGLint n_rects);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_KHR_swap_buffers_with_damage */

#अगर_अघोषित EGL_KHR_vg_parent_image
#घोषणा EGL_KHR_vg_parent_image 1
#घोषणा EGL_VG_PARENT_IMAGE_KHR           0x30BA
#पूर्ण_अगर /* EGL_KHR_vg_parent_image */

#अगर_अघोषित EGL_KHR_wait_sync
#घोषणा EGL_KHR_wait_sync 1
प्रकार EGLint (EGLAPIENTRYP PFNEGLWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLint EGLAPIENTRY eglWaitSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_KHR_wait_sync */

#अगर_अघोषित EGL_ANDROID_GLES_layers
#घोषणा EGL_ANDROID_GLES_layers 1
#पूर्ण_अगर /* EGL_ANDROID_GLES_layers */

#अगर_अघोषित EGL_ANDROID_blob_cache
#घोषणा EGL_ANDROID_blob_cache 1
प्रकार khronos_ssize_t EGLsizeiANDROID;
प्रकार व्योम (*EGLSetBlobFuncANDROID) (स्थिर व्योम *कुंजी, EGLsizeiANDROID कुंजी_आकार_2, स्थिर व्योम *मूल्य, EGLsizeiANDROID मूल्य_आकार_2);
प्रकार EGLsizeiANDROID (*EGLGetBlobFuncANDROID) (स्थिर व्योम *कुंजी, EGLsizeiANDROID कुंजी_आकार_2, व्योम *मूल्य, EGLsizeiANDROID मूल्य_आकार_2);
प्रकार व्योम (EGLAPIENTRYP PFNEGLSETBLOBCACHEFUNCSANDROIDPROC) (EGLDisplay dpy, EGLSetBlobFuncANDROID set, EGLGetBlobFuncANDROID get);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI व्योम EGLAPIENTRY eglSetBlobCacheFuncsANDROID (EGLDisplay dpy, EGLSetBlobFuncANDROID set, EGLGetBlobFuncANDROID get);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_ANDROID_blob_cache */

#अगर_अघोषित EGL_ANDROID_create_native_client_बफर
#घोषणा EGL_ANDROID_create_native_client_बफर 1
#घोषणा EGL_NATIVE_बफर_USAGE_ANDROID   0x3143
#घोषणा EGL_NATIVE_बफर_USAGE_PROTECTED_BIT_ANDROID 0x00000001
#घोषणा EGL_NATIVE_बफर_USAGE_RENDERBUFFER_BIT_ANDROID 0x00000002
#घोषणा EGL_NATIVE_बफर_USAGE_TEXTURE_BIT_ANDROID 0x00000004
प्रकार EGLClient_बफर (EGLAPIENTRYP PFNEGLCREATENATIVECLIENTBUFFERANDROIDPROC) (स्थिर EGLint *attrib_list);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLClient_बफर EGLAPIENTRY egl_Create_Native_Client_बफर_ANDROID (स्थिर EGLint *attrib_list);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_ANDROID_create_native_client_buffer */

#अगर_अघोषित EGL_ANDROID_framebuffer_target
#घोषणा EGL_ANDROID_framebuffer_target 1
#घोषणा EGL_FRAMEBUFFER_TARGET_ANDROID    0x3147
#पूर्ण_अगर /* EGL_ANDROID_framebuffer_target */

#अगर_अघोषित EGL_ANDROID_front_बफर_auto_refresh
#घोषणा EGL_ANDROID_front_बफर_auto_refresh 1
#घोषणा EGL_FRONT_बफर_AUTO_REFRESH_ANDROID 0x314C
#पूर्ण_अगर /* EGL_ANDROID_front_buffer_auto_refresh */

#अगर_अघोषित EGL_ANDROID_get_frame_timestamps
#घोषणा EGL_ANDROID_get_frame_timestamps 1
प्रकार khronos_stime_nanoseconds_t EGLnsecsANDROID;
#घोषणा EGL_TIMESTAMP_PENDING_ANDROID     EGL_CAST(EGLnsecsANDROID,-2)
#घोषणा EGL_TIMESTAMP_INVALID_ANDROID     EGL_CAST(EGLnsecsANDROID,-1)
#घोषणा EGL_TIMESTAMPS_ANDROID            0x3430
#घोषणा EGL_COMPOSITE_DEADLINE_ANDROID    0x3431
#घोषणा EGL_COMPOSITE_INTERVAL_ANDROID    0x3432
#घोषणा EGL_COMPOSITE_TO_PRESENT_LATENCY_ANDROID 0x3433
#घोषणा EGL_REQUESTED_PRESENT_TIME_ANDROID 0x3434
#घोषणा EGL_RENDERING_COMPLETE_TIME_ANDROID 0x3435
#घोषणा EGL_COMPOSITION_LATCH_TIME_ANDROID 0x3436
#घोषणा EGL_FIRST_COMPOSITION_START_TIME_ANDROID 0x3437
#घोषणा EGL_LAST_COMPOSITION_START_TIME_ANDROID 0x3438
#घोषणा EGL_FIRST_COMPOSITION_GPU_FINISHED_TIME_ANDROID 0x3439
#घोषणा EGL_DISPLAY_PRESENT_TIME_ANDROID  0x343A
#घोषणा EGL_DEQUEUE_READY_TIME_ANDROID    0x343B
#घोषणा EGL_READS_DONE_TIME_ANDROID       0x343C
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLGETCOMPOSITORTIMINGSUPPORTEDANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLint name);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLGETCOMPOSITORTIMINGANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLint अंक_Timestamps,  स्थिर EGLint *names, EGLnsecsANDROID *मूल्यावली);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLGETNEXTFRAMEIDANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR *frameId);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLGETFRAMETIMESTAMPSUPPORTEDANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLint timestamp);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLGETFRAMETIMESTAMPSANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR frameId, EGLint अंक_Timestamps,  स्थिर EGLint *timestamps, EGLnsecsANDROID *मूल्यावली);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglGetCompositorTimingSupportedANDROID (EGLDisplay dpy, EGLSurface surface, EGLint name);
EGLAPI EGLBoolean EGLAPIENTRY eglGetCompositorTimingANDROID (EGLDisplay dpy, EGLSurface surface, EGLint अंक_Timestamps,  स्थिर EGLint *names, EGLnsecsANDROID *मूल्यावली);
EGLAPI EGLBoolean EGLAPIENTRY egl_Get_अग्र_Frame_Id_ANDROID (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR *frameId);
EGLAPI EGLBoolean EGLAPIENTRY eglGetFrameTimestampSupportedANDROID (EGLDisplay dpy, EGLSurface surface, EGLint timestamp);
EGLAPI EGLBoolean EGLAPIENTRY eglGetFrameTimestampsANDROID (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR frameId, EGLint अंक_Timestamps,  स्थिर EGLint *timestamps, EGLnsecsANDROID *मूल्यावली);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_ANDROID_get_frame_timestamps */

#अगर_अघोषित EGL_ANDROID_get_native_client_बफर
#घोषणा EGL_ANDROID_get_native_client_बफर 1
काष्ठा AHardware_बफर;
प्रकार EGLClient_बफर (EGLAPIENTRYP PFNEGLGETNATIVECLIENTBUFFERANDROIDPROC) (स्थिर काष्ठा AHardware_बफर *बफर_2);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLClient_बफर EGLAPIENTRY egl_Get_Native_Client_बफर_ANDROID (स्थिर काष्ठा AHardware_बफर *बफर_2);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_ANDROID_get_native_client_buffer */

#अगर_अघोषित EGL_ANDROID_image_native_बफर
#घोषणा EGL_ANDROID_image_native_बफर 1
#घोषणा EGL_NATIVE_बफर_ANDROID         0x3140
#पूर्ण_अगर /* EGL_ANDROID_image_native_buffer */

#अगर_अघोषित EGL_ANDROID_native_fence_sync
#घोषणा EGL_ANDROID_native_fence_sync 1
#घोषणा EGL_SYNC_NATIVE_FENCE_ANDROID     0x3144
#घोषणा EGL_SYNC_NATIVE_FENCE_FD_ANDROID  0x3145
#घोषणा EGL_SYNC_NATIVE_FENCE_SIGNALED_ANDROID 0x3146
#घोषणा EGL_NO_NATIVE_FENCE_FD_ANDROID    -1
प्रकार EGLint (EGLAPIENTRYP PFNEGLDUPNATIVEFENCEFDANDROIDPROC) (EGLDisplay dpy, EGLSyncKHR sync);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLint EGLAPIENTRY eglDupNativeFenceFDANDROID (EGLDisplay dpy, EGLSyncKHR sync);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_ANDROID_native_fence_sync */

#अगर_अघोषित EGL_ANDROID_presentation_time
#घोषणा EGL_ANDROID_presentation_time 1
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLPRESENTATIONTIMEANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLnsecsANDROID समय);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglPresentationTimeANDROID (EGLDisplay dpy, EGLSurface surface, EGLnsecsANDROID समय);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_ANDROID_presentation_time */

#अगर_अघोषित EGL_ANDROID_recordable
#घोषणा EGL_ANDROID_recordable 1
#घोषणा EGL_RECORDABLE_ANDROID            0x3142
#पूर्ण_अगर /* EGL_ANDROID_recordable */

#अगर_अघोषित EGL_ANDROID_telemetry_hint
#घोषणा EGL_ANDROID_telemetry_hint 1
#घोषणा EGL_TELEMETRY_HINT_ANDROID        0x3570
#पूर्ण_अगर /* EGL_ANDROID_telemetry_hint */

#अगर_अघोषित EGL_ANGLE_d3d_share_handle_client_बफर
#घोषणा EGL_ANGLE_d3d_share_handle_client_बफर 1
#घोषणा EGL_D3D_TEXTURE_2D_SHARE_HANDLE_ANGLE 0x3200
#पूर्ण_अगर /* EGL_ANGLE_d3d_share_handle_client_buffer */

#अगर_अघोषित EGL_ANGLE_device_d3d
#घोषणा EGL_ANGLE_device_d3d 1
#घोषणा EGL_D3D9_DEVICE_ANGLE             0x33A0
#घोषणा EGL_D3D11_DEVICE_ANGLE            0x33A1
#पूर्ण_अगर /* EGL_ANGLE_device_d3d */

#अगर_अघोषित EGL_ANGLE_query_surface_pointer
#घोषणा EGL_ANGLE_query_surface_pointer 1
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSURFACEPOINTERANGLEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint attribute, व्योम **मूल्य);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQuerySurfacePointerANGLE (EGLDisplay dpy, EGLSurface surface, EGLint attribute, व्योम **मूल्य);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_ANGLE_query_surface_pointer */

#अगर_अघोषित EGL_ANGLE_surface_d3d_texture_2d_share_handle
#घोषणा EGL_ANGLE_surface_d3d_texture_2d_share_handle 1
#पूर्ण_अगर /* EGL_ANGLE_surface_d3d_texture_2d_share_handle */

#अगर_अघोषित EGL_ANGLE_sync_control_rate
#घोषणा EGL_ANGLE_sync_control_rate 1
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLGETMSCRATEANGLEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint *numerator, EGLint *denominator);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglGetMscRateANGLE (EGLDisplay dpy, EGLSurface surface, EGLint *numerator, EGLint *denominator);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_ANGLE_sync_control_rate */

#अगर_अघोषित EGL_ANGLE_window_fixed_आकार
#घोषणा EGL_ANGLE_window_fixed_आकार 1
#घोषणा EGL_FIXED_आकार_ANGLE              0x3201
#पूर्ण_अगर /* EGL_ANGLE_window_fixed_size */

#अगर_अघोषित EGL_ARM_image_format
#घोषणा EGL_ARM_image_format 1
#घोषणा EGL_COLOR_COMPONENT_TYPE_UNSIGNED_INTEGER_ARM 0x3287
#घोषणा EGL_COLOR_COMPONENT_TYPE_INTEGER_ARM 0x3288
#पूर्ण_अगर /* EGL_ARM_image_format */

#अगर_अघोषित EGL_ARM_implicit_external_sync
#घोषणा EGL_ARM_implicit_external_sync 1
#घोषणा EGL_SYNC_PRIOR_COMMANDS_IMPLICIT_EXTERNAL_ARM 0x328A
#पूर्ण_अगर /* EGL_ARM_implicit_external_sync */

#अगर_अघोषित EGL_ARM_pixmap_multisample_discard
#घोषणा EGL_ARM_pixmap_multisample_discard 1
#घोषणा EGL_DISCARD_SAMPLES_ARM           0x3286
#पूर्ण_अगर /* EGL_ARM_pixmap_multisample_discard */

#अगर_अघोषित EGL_EXT_bind_to_front
#घोषणा EGL_EXT_bind_to_front 1
#घोषणा EGL_FRONT_बफर_EXT              0x3464
#पूर्ण_अगर /* EGL_EXT_bind_to_front */

#अगर_अघोषित EGL_EXT_बफर_age
#घोषणा EGL_EXT_बफर_age 1
#घोषणा EGL_बफर_AGE_EXT                0x313D
#पूर्ण_अगर /* EGL_EXT_buffer_age */

#अगर_अघोषित EGL_EXT_client_extensions
#घोषणा EGL_EXT_client_extensions 1
#पूर्ण_अगर /* EGL_EXT_client_extensions */

#अगर_अघोषित EGL_EXT_client_sync
#घोषणा EGL_EXT_client_sync 1
#घोषणा EGL_SYNC_CLIENT_EXT               0x3364
#घोषणा EGL_SYNC_CLIENT_SIGNAL_EXT        0x3365
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLCLIENTSIGNALSYNCEXTPROC) (EGLDisplay dpy, EGLSync sync, स्थिर EGLAttrib *attrib_list);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglClientSignalSyncEXT (EGLDisplay dpy, EGLSync sync, स्थिर EGLAttrib *attrib_list);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_EXT_client_sync */

#अगर_अघोषित EGL_EXT_compositor
#घोषणा EGL_EXT_compositor 1
#घोषणा EGL_PRIMARY_COMPOSITOR_CONTEXT_EXT 0x3460
#घोषणा EGL_EXTERNAL_REF_ID_EXT           0x3461
#घोषणा EGL_COMPOSITOR_DROP_NEWEST_FRAME_EXT 0x3462
#घोषणा EGL_COMPOSITOR_KEEP_NEWEST_FRAME_EXT 0x3463
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETCONTEXTLISTEXTPROC) (स्थिर EGLint *external_ref_ids, EGLint अंक_entries);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETCONTEXTATTRIBUTESEXTPROC) (EGLint external_ref_id, स्थिर EGLint *context_attributes, EGLint अंक_entries);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETWINDOWLISTEXTPROC) (EGLint external_ref_id, स्थिर EGLint *external_win_ids, EGLint अंक_entries);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETWINDOWATTRIBUTESEXTPROC) (EGLint external_win_id, स्थिर EGLint *window_attributes, EGLint अंक_entries);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORBINDTEXWINDOWEXTPROC) (EGLint external_win_id);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETSIZEEXTPROC) (EGLint external_win_id, EGLint width, EGLint height);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSWAPPOLICYEXTPROC) (EGLint external_win_id, EGLint policy);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglCompositorSetContextListEXT (स्थिर EGLint *external_ref_ids, EGLint अंक_entries);
EGLAPI EGLBoolean EGLAPIENTRY eglCompositorSetContextAttributesEXT (EGLint external_ref_id, स्थिर EGLint *context_attributes, EGLint अंक_entries);
EGLAPI EGLBoolean EGLAPIENTRY eglCompositorSetWindowListEXT (EGLint external_ref_id, स्थिर EGLint *external_win_ids, EGLint अंक_entries);
EGLAPI EGLBoolean EGLAPIENTRY eglCompositorSetWindowAttributesEXT (EGLint external_win_id, स्थिर EGLint *window_attributes, EGLint अंक_entries);
EGLAPI EGLBoolean EGLAPIENTRY eglCompositorBindTexWindowEXT (EGLint external_win_id);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_Set_आकार_EXT (EGLint external_win_id, EGLint width, EGLint height);
EGLAPI EGLBoolean EGLAPIENTRY eglCompositorSwapPolicyEXT (EGLint external_win_id, EGLint policy);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_EXT_compositor */

#अगर_अघोषित EGL_EXT_config_select_group
#घोषणा EGL_EXT_config_select_group 1
#घोषणा EGL_CONFIG_SELECT_GROUP_EXT       0x34C0
#पूर्ण_अगर /* EGL_EXT_config_select_group */

#अगर_अघोषित EGL_EXT_create_context_robustness
#घोषणा EGL_EXT_create_context_robustness 1
#घोषणा EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT 0x30BF
#घोषणा EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_EXT 0x3138
#घोषणा EGL_NO_RESET_NOTIFICATION_EXT     0x31BE
#घोषणा EGL_LOSE_CONTEXT_ON_RESET_EXT     0x31BF
#पूर्ण_अगर /* EGL_EXT_create_context_robustness */

#अगर_अघोषित EGL_EXT_device_base
#घोषणा EGL_EXT_device_base 1
प्रकार व्योम *EGLDeviceEXT;
#घोषणा EGL_NO_DEVICE_EXT                 EGL_CAST(EGLDeviceEXT,0)
#घोषणा EGL_BAD_DEVICE_EXT                0x322B
#घोषणा EGL_DEVICE_EXT                    0x322C
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICEATTRIBEXTPROC) (EGLDeviceEXT device, EGLint attribute, EGLAttrib *मूल्य);
प्रकार स्थिर अक्षर *(EGLAPIENTRYP PFNEGLQUERYDEVICESTRINGEXTPROC) (EGLDeviceEXT device, EGLint name);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICESEXTPROC) (EGLint max_devices, EGLDeviceEXT *devices, EGLint *अंक_devices);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDISPLAYATTRIBEXTPROC) (EGLDisplay dpy, EGLint attribute, EGLAttrib *मूल्य);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDeviceAttribEXT (EGLDeviceEXT device, EGLint attribute, EGLAttrib *मूल्य);
EGLAPI स्थिर अक्षर *EGLAPIENTRY eglQueryDeviceStringEXT (EGLDeviceEXT device, EGLint name);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDevicesEXT (EGLint max_devices, EGLDeviceEXT *devices, EGLint *अंक_devices);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDisplayAttribEXT (EGLDisplay dpy, EGLint attribute, EGLAttrib *मूल्य);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_EXT_device_base */

#अगर_अघोषित EGL_EXT_device_drm
#घोषणा EGL_EXT_device_drm 1
#घोषणा EGL_DRM_DEVICE_FILE_EXT           0x3233
#घोषणा EGL_DRM_MASTER_FD_EXT             0x333C
#पूर्ण_अगर /* EGL_EXT_device_drm */

#अगर_अघोषित EGL_EXT_device_drm_render_गाँठ
#घोषणा EGL_EXT_device_drm_render_गाँठ 1
#घोषणा EGL_DRM_RENDER_गाँठ_FILE_EXT      0x3377
#पूर्ण_अगर /* EGL_EXT_device_drm_render_node */

#अगर_अघोषित EGL_EXT_device_enumeration
#घोषणा EGL_EXT_device_enumeration 1
#पूर्ण_अगर /* EGL_EXT_device_enumeration */

#अगर_अघोषित EGL_EXT_device_openwf
#घोषणा EGL_EXT_device_openwf 1
#घोषणा EGL_OPENWF_DEVICE_ID_EXT          0x3237
#घोषणा EGL_OPENWF_DEVICE_EXT             0x333D
#पूर्ण_अगर /* EGL_EXT_device_openwf */

#अगर_अघोषित EGL_EXT_device_persistent_id
#घोषणा EGL_EXT_device_persistent_id 1
#घोषणा EGL_DEVICE_UUID_EXT               0x335C
#घोषणा EGL_DRIVER_UUID_EXT               0x335D
#घोषणा EGL_DRIVER_NAME_EXT               0x335E
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICEBINARYEXTPROC) (EGLDeviceEXT device, EGLint name, EGLint max_आकार, व्योम *मूल्य, EGLint *आकार);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Device_द्विआधारी_EXT (EGLDeviceEXT device, EGLint name, EGLint max_आकार, व्योम *मूल्य, EGLint *आकार);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_EXT_device_persistent_id */

#अगर_अघोषित EGL_EXT_device_query
#घोषणा EGL_EXT_device_query 1
#पूर्ण_अगर /* EGL_EXT_device_query */

#अगर_अघोषित EGL_EXT_device_query_name
#घोषणा EGL_EXT_device_query_name 1
#घोषणा EGL_RENDERER_EXT                  0x335F
#पूर्ण_अगर /* EGL_EXT_device_query_name */

#अगर_अघोषित EGL_EXT_device_type
#घोषणा EGL_EXT_device_type 1
#घोषणा EGL_DEVICE_TYPE_EXT               0x3590
#घोषणा EGL_DEVICE_TYPE_OTHER_EXT         0x3591
#घोषणा EGL_DEVICE_TYPE_INTEGRATED_GPU_EXT 0x3592
#घोषणा EGL_DEVICE_TYPE_DISCRETE_GPU_EXT  0x3593
#घोषणा EGL_DEVICE_TYPE_CPU_EXT           0x3594
#पूर्ण_अगर /* EGL_EXT_device_type */

#अगर_अघोषित EGL_EXT_display_alloc
#घोषणा EGL_EXT_display_alloc 1
#घोषणा EGL_ALLOC_NEW_DISPLAY_EXT         0x3379
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYDISPLAYEXTPROC) (EGLDisplay dpy);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyDisplayEXT (EGLDisplay dpy);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_EXT_display_alloc */

#अगर_अघोषित EGL_EXT_explicit_device
#घोषणा EGL_EXT_explicit_device 1
#पूर्ण_अगर /* EGL_EXT_explicit_device */

#अगर_अघोषित EGL_EXT_gl_colorspace_bt2020_hlg
#घोषणा EGL_EXT_gl_colorspace_bt2020_hlg 1
#घोषणा EGL_GL_COLORSPACE_BT2020_HLG_EXT  0x3540
#पूर्ण_अगर /* EGL_EXT_gl_colorspace_bt2020_hlg */

#अगर_अघोषित EGL_EXT_gl_colorspace_bt2020_linear
#घोषणा EGL_EXT_gl_colorspace_bt2020_linear 1
#घोषणा EGL_GL_COLORSPACE_BT2020_LINEAR_EXT 0x333F
#पूर्ण_अगर /* EGL_EXT_gl_colorspace_bt2020_linear */

#अगर_अघोषित EGL_EXT_gl_colorspace_bt2020_pq
#घोषणा EGL_EXT_gl_colorspace_bt2020_pq 1
#घोषणा EGL_GL_COLORSPACE_BT2020_PQ_EXT   0x3340
#पूर्ण_अगर /* EGL_EXT_gl_colorspace_bt2020_pq */

#अगर_अघोषित EGL_EXT_gl_colorspace_display_p3
#घोषणा EGL_EXT_gl_colorspace_display_p3 1
#घोषणा EGL_GL_COLORSPACE_DISPLAY_P3_EXT  0x3363
#पूर्ण_अगर /* EGL_EXT_gl_colorspace_display_p3 */

#अगर_अघोषित EGL_EXT_gl_colorspace_display_p3_linear
#घोषणा EGL_EXT_gl_colorspace_display_p3_linear 1
#घोषणा EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT 0x3362
#पूर्ण_अगर /* EGL_EXT_gl_colorspace_display_p3_linear */

#अगर_अघोषित EGL_EXT_gl_colorspace_display_p3_passthrough
#घोषणा EGL_EXT_gl_colorspace_display_p3_passthrough 1
#घोषणा EGL_GL_COLORSPACE_DISPLAY_P3_PASSTHROUGH_EXT 0x3490
#पूर्ण_अगर /* EGL_EXT_gl_colorspace_display_p3_passthrough */

#अगर_अघोषित EGL_EXT_gl_colorspace_scrgb
#घोषणा EGL_EXT_gl_colorspace_scrgb 1
#घोषणा EGL_GL_COLORSPACE_SCRGB_EXT       0x3351
#पूर्ण_अगर /* EGL_EXT_gl_colorspace_scrgb */

#अगर_अघोषित EGL_EXT_gl_colorspace_scrgb_linear
#घोषणा EGL_EXT_gl_colorspace_scrgb_linear 1
#घोषणा EGL_GL_COLORSPACE_SCRGB_LINEAR_EXT 0x3350
#पूर्ण_अगर /* EGL_EXT_gl_colorspace_scrgb_linear */

#अगर_अघोषित EGL_EXT_image_dma_buf_import
#घोषणा EGL_EXT_image_dma_buf_import 1
#घोषणा EGL_LINUX_DMA_BUF_EXT             0x3270
#घोषणा EGL_LINUX_DRM_FOURCC_EXT          0x3271
#घोषणा EGL_DMA_BUF_PLANE0_FD_EXT         0x3272
#घोषणा EGL_DMA_BUF_PLANE0_OFFSET_EXT     0x3273
#घोषणा EGL_DMA_BUF_PLANE0_PITCH_EXT      0x3274
#घोषणा EGL_DMA_BUF_PLANE1_FD_EXT         0x3275
#घोषणा EGL_DMA_BUF_PLANE1_OFFSET_EXT     0x3276
#घोषणा EGL_DMA_BUF_PLANE1_PITCH_EXT      0x3277
#घोषणा EGL_DMA_BUF_PLANE2_FD_EXT         0x3278
#घोषणा EGL_DMA_BUF_PLANE2_OFFSET_EXT     0x3279
#घोषणा EGL_DMA_BUF_PLANE2_PITCH_EXT      0x327A
#घोषणा EGL_YUV_COLOR_SPACE_HINT_EXT      0x327B
#घोषणा EGL_SAMPLE_RANGE_HINT_EXT         0x327C
#घोषणा EGL_YUV_CHROMA_HORIZONTAL_SITING_HINT_EXT 0x327D
#घोषणा EGL_YUV_CHROMA_VERTICAL_SITING_HINT_EXT 0x327E
#घोषणा EGL_ITU_REC601_EXT                0x327F
#घोषणा EGL_ITU_REC709_EXT                0x3280
#घोषणा EGL_ITU_REC2020_EXT               0x3281
#घोषणा EGL_YUV_FULL_RANGE_EXT            0x3282
#घोषणा EGL_YUV_NARROW_RANGE_EXT          0x3283
#घोषणा EGL_YUV_CHROMA_SITING_0_EXT       0x3284
#घोषणा EGL_YUV_CHROMA_SITING_0_5_EXT     0x3285
#पूर्ण_अगर /* EGL_EXT_image_dma_buf_import */

#अगर_अघोषित EGL_EXT_image_dma_buf_import_modifiers
#घोषणा EGL_EXT_image_dma_buf_import_modifiers 1
#घोषणा EGL_DMA_BUF_PLANE3_FD_EXT         0x3440
#घोषणा EGL_DMA_BUF_PLANE3_OFFSET_EXT     0x3441
#घोषणा EGL_DMA_BUF_PLANE3_PITCH_EXT      0x3442
#घोषणा EGL_DMA_BUF_PLANE0_MODIFIER_LO_EXT 0x3443
#घोषणा EGL_DMA_BUF_PLANE0_MODIFIER_HI_EXT 0x3444
#घोषणा EGL_DMA_BUF_PLANE1_MODIFIER_LO_EXT 0x3445
#घोषणा EGL_DMA_BUF_PLANE1_MODIFIER_HI_EXT 0x3446
#घोषणा EGL_DMA_BUF_PLANE2_MODIFIER_LO_EXT 0x3447
#घोषणा EGL_DMA_BUF_PLANE2_MODIFIER_HI_EXT 0x3448
#घोषणा EGL_DMA_BUF_PLANE3_MODIFIER_LO_EXT 0x3449
#घोषणा EGL_DMA_BUF_PLANE3_MODIFIER_HI_EXT 0x344A
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDMABUFFORMATSEXTPROC) (EGLDisplay dpy, EGLint max_formats, EGLint *formats, EGLint *अंक_formats);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDMABUFMODIFIERSEXTPROC) (EGLDisplay dpy, EGLint format, EGLint max_modifiers, EGLuint64KHR *modifiers, EGLBoolean *external_only, EGLint *अंक_modifiers);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDmaBufFormatsEXT (EGLDisplay dpy, EGLint max_formats, EGLint *formats, EGLint *अंक_formats);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDmaBufModifiersEXT (EGLDisplay dpy, EGLint format, EGLint max_modifiers, EGLuint64KHR *modifiers, EGLBoolean *external_only, EGLint *अंक_modifiers);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_EXT_image_dma_buf_import_modifiers */

#अगर_अघोषित EGL_EXT_image_gl_colorspace
#घोषणा EGL_EXT_image_gl_colorspace 1
#घोषणा EGL_GL_COLORSPACE_DEFAULT_EXT     0x314D
#पूर्ण_अगर /* EGL_EXT_image_gl_colorspace */

#अगर_अघोषित EGL_EXT_image_implicit_sync_control
#घोषणा EGL_EXT_image_implicit_sync_control 1
#घोषणा EGL_IMPORT_SYNC_TYPE_EXT          0x3470
#घोषणा EGL_IMPORT_IMPLICIT_SYNC_EXT      0x3471
#घोषणा EGL_IMPORT_EXPLICIT_SYNC_EXT      0x3472
#पूर्ण_अगर /* EGL_EXT_image_implicit_sync_control */

#अगर_अघोषित EGL_EXT_multiview_window
#घोषणा EGL_EXT_multiview_window 1
#घोषणा EGL_MULTIVIEW_VIEW_गिनती_EXT      0x3134
#पूर्ण_अगर /* EGL_EXT_multiview_window */

#अगर_अघोषित EGL_EXT_output_base
#घोषणा EGL_EXT_output_base 1
प्रकार व्योम *EGLOutputLayerEXT;
प्रकार व्योम *EGLOutputPortEXT;
#घोषणा EGL_NO_OUTPUT_LAYER_EXT           EGL_CAST(EGLOutputLayerEXT,0)
#घोषणा EGL_NO_OUTPUT_PORT_EXT            EGL_CAST(EGLOutputPortEXT,0)
#घोषणा EGL_BAD_OUTPUT_LAYER_EXT          0x322D
#घोषणा EGL_BAD_OUTPUT_PORT_EXT           0x322E
#घोषणा EGL_SWAP_INTERVAL_EXT             0x322F
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLGETOUTPUTLAYERSEXTPROC) (EGLDisplay dpy, स्थिर EGLAttrib *attrib_list, EGLOutputLayerEXT *layers, EGLint max_layers, EGLint *अंक_layers);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLGETOUTPUTPORTSEXTPROC) (EGLDisplay dpy, स्थिर EGLAttrib *attrib_list, EGLOutputPortEXT *ports, EGLint max_ports, EGLint *अंक_ports);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLOUTPUTLAYERATTRIBEXTPROC) (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib मूल्य);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLQUERYOUTPUTLAYERATTRIBEXTPROC) (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib *मूल्य);
प्रकार स्थिर अक्षर *(EGLAPIENTRYP PFNEGLQUERYOUTPUTLAYERSTRINGEXTPROC) (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint name);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLOUTPUTPORTATTRIBEXTPROC) (EGLDisplay dpy, EGLOutputPortEXT port, EGLint attribute, EGLAttrib मूल्य);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLQUERYOUTPUTPORTATTRIBEXTPROC) (EGLDisplay dpy, EGLOutputPortEXT port, EGLint attribute, EGLAttrib *मूल्य);
प्रकार स्थिर अक्षर *(EGLAPIENTRYP PFNEGLQUERYOUTPUTPORTSTRINGEXTPROC) (EGLDisplay dpy, EGLOutputPortEXT port, EGLint name);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglGetOutputLayersEXT (EGLDisplay dpy, स्थिर EGLAttrib *attrib_list, EGLOutputLayerEXT *layers, EGLint max_layers, EGLint *अंक_layers);
EGLAPI EGLBoolean EGLAPIENTRY eglGetOutputPortsEXT (EGLDisplay dpy, स्थिर EGLAttrib *attrib_list, EGLOutputPortEXT *ports, EGLint max_ports, EGLint *अंक_ports);
EGLAPI EGLBoolean EGLAPIENTRY eglOutputLayerAttribEXT (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib मूल्य);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryOutputLayerAttribEXT (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib *मूल्य);
EGLAPI स्थिर अक्षर *EGLAPIENTRY eglQueryOutputLayerStringEXT (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint name);
EGLAPI EGLBoolean EGLAPIENTRY eglOutputPortAttribEXT (EGLDisplay dpy, EGLOutputPortEXT port, EGLint attribute, EGLAttrib मूल्य);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryOutputPortAttribEXT (EGLDisplay dpy, EGLOutputPortEXT port, EGLint attribute, EGLAttrib *मूल्य);
EGLAPI स्थिर अक्षर *EGLAPIENTRY eglQueryOutputPortStringEXT (EGLDisplay dpy, EGLOutputPortEXT port, EGLint name);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_EXT_output_base */

#अगर_अघोषित EGL_EXT_output_drm
#घोषणा EGL_EXT_output_drm 1
#घोषणा EGL_DRM_CRTC_EXT                  0x3234
#घोषणा EGL_DRM_PLANE_EXT                 0x3235
#घोषणा EGL_DRM_CONNECTOR_EXT             0x3236
#पूर्ण_अगर /* EGL_EXT_output_drm */

#अगर_अघोषित EGL_EXT_output_openwf
#घोषणा EGL_EXT_output_openwf 1
#घोषणा EGL_OPENWF_PIPELINE_ID_EXT        0x3238
#घोषणा EGL_OPENWF_PORT_ID_EXT            0x3239
#पूर्ण_अगर /* EGL_EXT_output_openwf */

#अगर_अघोषित EGL_EXT_pixel_format_float
#घोषणा EGL_EXT_pixel_format_float 1
#घोषणा EGL_COLOR_COMPONENT_TYPE_EXT      0x3339
#घोषणा EGL_COLOR_COMPONENT_TYPE_FIXED_EXT 0x333A
#घोषणा EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT 0x333B
#पूर्ण_अगर /* EGL_EXT_pixel_format_float */

#अगर_अघोषित EGL_EXT_platform_base
#घोषणा EGL_EXT_platform_base 1
प्रकार EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYEXTPROC) (EGLenum platform, व्योम *native_display, स्थिर EGLint *attrib_list);
प्रकार EGLSurface (EGLAPIENTRYP PFNEGLCREATEPLATFORMWINDOWSURFACEEXTPROC) (EGLDisplay dpy, EGLConfig config, व्योम *native_window, स्थिर EGLint *attrib_list);
प्रकार EGLSurface (EGLAPIENTRYP PFNEGLCREATEPLATFORMPIXMAPSURFACEEXTPROC) (EGLDisplay dpy, EGLConfig config, व्योम *native_pixmap, स्थिर EGLint *attrib_list);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLDisplay EGLAPIENTRY eglGetPlatformDisplayEXT (EGLenum platform, व्योम *native_display, स्थिर EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePlatformWindowSurfaceEXT (EGLDisplay dpy, EGLConfig config, व्योम *native_window, स्थिर EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePlatformPixmapSurfaceEXT (EGLDisplay dpy, EGLConfig config, व्योम *native_pixmap, स्थिर EGLint *attrib_list);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_EXT_platform_base */

#अगर_अघोषित EGL_EXT_platform_device
#घोषणा EGL_EXT_platform_device 1
#घोषणा EGL_PLATFORM_DEVICE_EXT           0x313F
#पूर्ण_अगर /* EGL_EXT_platform_device */

#अगर_अघोषित EGL_EXT_platform_wayland
#घोषणा EGL_EXT_platform_wayland 1
#घोषणा EGL_PLATFORM_WAYLAND_EXT          0x31D8
#पूर्ण_अगर /* EGL_EXT_platform_wayland */

#अगर_अघोषित EGL_EXT_platform_x11
#घोषणा EGL_EXT_platform_x11 1
#घोषणा EGL_PLATFORM_X11_EXT              0x31D5
#घोषणा EGL_PLATFORM_X11_SCREEN_EXT       0x31D6
#पूर्ण_अगर /* EGL_EXT_platform_x11 */

#अगर_अघोषित EGL_EXT_platform_xcb
#घोषणा EGL_EXT_platform_xcb 1
#घोषणा EGL_PLATFORM_XCB_EXT              0x31DC
#घोषणा EGL_PLATFORM_XCB_SCREEN_EXT       0x31DE
#पूर्ण_अगर /* EGL_EXT_platform_xcb */

#अगर_अघोषित EGL_EXT_present_opaque
#घोषणा EGL_EXT_present_opaque 1
#घोषणा EGL_PRESENT_OPAQUE_EXT            0x31DF
#पूर्ण_अगर /* EGL_EXT_present_opaque */

#अगर_अघोषित EGL_EXT_protected_content
#घोषणा EGL_EXT_protected_content 1
#घोषणा EGL_PROTECTED_CONTENT_EXT         0x32C0
#पूर्ण_अगर /* EGL_EXT_protected_content */

#अगर_अघोषित EGL_EXT_protected_surface
#घोषणा EGL_EXT_protected_surface 1
#पूर्ण_अगर /* EGL_EXT_protected_surface */

#अगर_अघोषित EGL_EXT_query_reset_notification_strategy
#घोषणा EGL_EXT_query_reset_notification_strategy 1
#पूर्ण_अगर /* EGL_EXT_query_reset_notification_strategy */

#अगर_अघोषित EGL_EXT_stream_consumer_egloutput
#घोषणा EGL_EXT_stream_consumer_egloutput 1
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMEROUTPUTEXTPROC) (EGLDisplay dpy, EGLStreamKHR stream, EGLOutputLayerEXT layer);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglStreamConsumerOutputEXT (EGLDisplay dpy, EGLStreamKHR stream, EGLOutputLayerEXT layer);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_EXT_stream_consumer_egloutput */

#अगर_अघोषित EGL_EXT_surface_CTA861_3_metadata
#घोषणा EGL_EXT_surface_CTA861_3_metadata 1
#घोषणा EGL_CTA861_3_MAX_CONTENT_LIGHT_LEVEL_EXT 0x3360
#घोषणा EGL_CTA861_3_MAX_FRAME_AVERAGE_LEVEL_EXT 0x3361
#पूर्ण_अगर /* EGL_EXT_surface_CTA861_3_metadata */

#अगर_अघोषित EGL_EXT_surface_SMPTE2086_metadata
#घोषणा EGL_EXT_surface_SMPTE2086_metadata 1
#घोषणा EGL_SMPTE2086_DISPLAY_PRIMARY_RX_EXT 0x3341
#घोषणा EGL_SMPTE2086_DISPLAY_PRIMARY_RY_EXT 0x3342
#घोषणा EGL_SMPTE2086_DISPLAY_PRIMARY_GX_EXT 0x3343
#घोषणा EGL_SMPTE2086_DISPLAY_PRIMARY_GY_EXT 0x3344
#घोषणा EGL_SMPTE2086_DISPLAY_PRIMARY_BX_EXT 0x3345
#घोषणा EGL_SMPTE2086_DISPLAY_PRIMARY_BY_EXT 0x3346
#घोषणा EGL_SMPTE2086_WHITE_POINT_X_EXT   0x3347
#घोषणा EGL_SMPTE2086_WHITE_POINT_Y_EXT   0x3348
#घोषणा EGL_SMPTE2086_MAX_LUMINANCE_EXT   0x3349
#घोषणा EGL_SMPTE2086_MIN_LUMINANCE_EXT   0x334A
#घोषणा EGL_METADATA_SCALING_EXT          50000
#पूर्ण_अगर /* EGL_EXT_surface_SMPTE2086_metadata */

#अगर_अघोषित EGL_EXT_surface_compression
#घोषणा EGL_EXT_surface_compression 1
#घोषणा EGL_SURFACE_COMPRESSION_EXT       0x34B0
#घोषणा EGL_SURFACE_COMPRESSION_PLANE1_EXT 0x328E
#घोषणा EGL_SURFACE_COMPRESSION_PLANE2_EXT 0x328F
#घोषणा EGL_SURFACE_COMPRESSION_FIXED_RATE_NONE_EXT 0x34B1
#घोषणा EGL_SURFACE_COMPRESSION_FIXED_RATE_DEFAULT_EXT 0x34B2
#घोषणा EGL_SURFACE_COMPRESSION_FIXED_RATE_1BPC_EXT 0x34B4
#घोषणा EGL_SURFACE_COMPRESSION_FIXED_RATE_2BPC_EXT 0x34B5
#घोषणा EGL_SURFACE_COMPRESSION_FIXED_RATE_3BPC_EXT 0x34B6
#घोषणा EGL_SURFACE_COMPRESSION_FIXED_RATE_4BPC_EXT 0x34B7
#घोषणा EGL_SURFACE_COMPRESSION_FIXED_RATE_5BPC_EXT 0x34B8
#घोषणा EGL_SURFACE_COMPRESSION_FIXED_RATE_6BPC_EXT 0x34B9
#घोषणा EGL_SURFACE_COMPRESSION_FIXED_RATE_7BPC_EXT 0x34BA
#घोषणा EGL_SURFACE_COMPRESSION_FIXED_RATE_8BPC_EXT 0x34BB
#घोषणा EGL_SURFACE_COMPRESSION_FIXED_RATE_9BPC_EXT 0x34BC
#घोषणा EGL_SURFACE_COMPRESSION_FIXED_RATE_10BPC_EXT 0x34BD
#घोषणा EGL_SURFACE_COMPRESSION_FIXED_RATE_11BPC_EXT 0x34BE
#घोषणा EGL_SURFACE_COMPRESSION_FIXED_RATE_12BPC_EXT 0x34BF
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSUPPORTEDCOMPRESSIONRATESEXTPROC) (EGLDisplay dpy, EGLConfig config, स्थिर EGLAttrib *attrib_list, EGLint *rates, EGLint rate_आकार, EGLint *अंक_rates);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQuerySupportedCompressionRatesEXT (EGLDisplay dpy, EGLConfig config, स्थिर EGLAttrib *attrib_list, EGLint *rates, EGLint rate_आकार, EGLint *अंक_rates);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_EXT_surface_compression */

#अगर_अघोषित EGL_EXT_swap_buffers_with_damage
#घोषणा EGL_EXT_swap_buffers_with_damage 1
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC) (EGLDisplay dpy, EGLSurface surface, स्थिर EGLint *rects, EGLint n_rects);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglSwapBuffersWithDamageEXT (EGLDisplay dpy, EGLSurface surface, स्थिर EGLint *rects, EGLint n_rects);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_EXT_swap_buffers_with_damage */

#अगर_अघोषित EGL_EXT_sync_reuse
#घोषणा EGL_EXT_sync_reuse 1
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLUNSIGNALSYNCEXTPROC) (EGLDisplay dpy, EGLSync sync, स्थिर EGLAttrib *attrib_list);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglUnsignalSyncEXT (EGLDisplay dpy, EGLSync sync, स्थिर EGLAttrib *attrib_list);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_EXT_sync_reuse */

#अगर_अघोषित EGL_EXT_yuv_surface
#घोषणा EGL_EXT_yuv_surface 1
#घोषणा EGL_YUV_ORDER_EXT                 0x3301
#घोषणा EGL_YUV_संख्या_OF_PLANES_EXT      0x3311
#घोषणा EGL_YUV_SUBSAMPLE_EXT             0x3312
#घोषणा EGL_YUV_DEPTH_RANGE_EXT           0x3317
#घोषणा EGL_YUV_CSC_STANDARD_EXT          0x330A
#घोषणा EGL_YUV_PLANE_BPP_EXT             0x331A
#घोषणा EGL_YUV_बफर_EXT                0x3300
#घोषणा EGL_YUV_ORDER_YUV_EXT             0x3302
#घोषणा EGL_YUV_ORDER_YVU_EXT             0x3303
#घोषणा EGL_YUV_ORDER_YUYV_EXT            0x3304
#घोषणा EGL_YUV_ORDER_UYVY_EXT            0x3305
#घोषणा EGL_YUV_ORDER_YVYU_EXT            0x3306
#घोषणा EGL_YUV_ORDER_VYUY_EXT            0x3307
#घोषणा EGL_YUV_ORDER_AYUV_EXT            0x3308
#घोषणा EGL_YUV_SUBSAMPLE_4_2_0_EXT       0x3313
#घोषणा EGL_YUV_SUBSAMPLE_4_2_2_EXT       0x3314
#घोषणा EGL_YUV_SUBSAMPLE_4_4_4_EXT       0x3315
#घोषणा EGL_YUV_DEPTH_RANGE_LIMITED_EXT   0x3318
#घोषणा EGL_YUV_DEPTH_RANGE_FULL_EXT      0x3319
#घोषणा EGL_YUV_CSC_STANDARD_601_EXT      0x330B
#घोषणा EGL_YUV_CSC_STANDARD_709_EXT      0x330C
#घोषणा EGL_YUV_CSC_STANDARD_2020_EXT     0x330D
#घोषणा EGL_YUV_PLANE_BPP_0_EXT           0x331B
#घोषणा EGL_YUV_PLANE_BPP_8_EXT           0x331C
#घोषणा EGL_YUV_PLANE_BPP_10_EXT          0x331D
#पूर्ण_अगर /* EGL_EXT_yuv_surface */

#अगर_अघोषित EGL_HI_clientpixmap
#घोषणा EGL_HI_clientpixmap 1
काष्ठा EGLClientPixmapHI {
    व्योम  *p_तथ्य;
    EGLint iWidth;
    EGLint iHeight;
    EGLint iStride;
};
#घोषणा EGL_CLIENT_PIXMAP_POINTER_HI      0x8F74
प्रकार EGLSurface (EGLAPIENTRYP PFNEGLCREATEPIXMAPSURFACEHIPROC) (EGLDisplay dpy, EGLConfig config, काष्ठा EGLClientPixmapHI *pixmap);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSurface EGLAPIENTRY eglCreatePixmapSurfaceHI (EGLDisplay dpy, EGLConfig config, काष्ठा EGLClientPixmapHI *pixmap);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_HI_clientpixmap */

#अगर_अघोषित EGL_HI_colorformats
#घोषणा EGL_HI_colorformats 1
#घोषणा EGL_COLOR_FORMAT_HI               0x8F70
#घोषणा EGL_COLOR_RGB_HI                  0x8F71
#घोषणा EGL_COLOR_RGBA_HI                 0x8F72
#घोषणा EGL_COLOR_ARGB_HI                 0x8F73
#पूर्ण_अगर /* EGL_HI_colorformats */

#अगर_अघोषित EGL_IMG_context_priority
#घोषणा EGL_IMG_context_priority 1
#घोषणा EGL_CONTEXT_PRIORITY_LEVEL_IMG    0x3100
#घोषणा EGL_CONTEXT_PRIORITY_ऊपरी_IMG     0x3101
#घोषणा EGL_CONTEXT_PRIORITY_MEDIUM_IMG   0x3102
#घोषणा EGL_CONTEXT_PRIORITY_निचला_IMG      0x3103
#पूर्ण_अगर /* EGL_IMG_context_priority */

#अगर_अघोषित EGL_IMG_image_plane_attribs
#घोषणा EGL_IMG_image_plane_attribs 1
#घोषणा EGL_NATIVE_बफर_MULTIPLANE_SEPARATE_IMG 0x3105
#घोषणा EGL_NATIVE_बफर_PLANE_OFFSET_IMG 0x3106
#पूर्ण_अगर /* EGL_IMG_image_plane_attribs */

#अगर_अघोषित EGL_MESA_drm_image
#घोषणा EGL_MESA_drm_image 1
#घोषणा EGL_DRM_बफर_FORMAT_MESA        0x31D0
#घोषणा EGL_DRM_बफर_USE_MESA           0x31D1
#घोषणा EGL_DRM_बफर_FORMAT_ARGB32_MESA 0x31D2
#घोषणा EGL_DRM_बफर_MESA               0x31D3
#घोषणा EGL_DRM_बफर_STRIDE_MESA        0x31D4
#घोषणा EGL_DRM_बफर_USE_SCANOUT_MESA   0x00000001
#घोषणा EGL_DRM_बफर_USE_SHARE_MESA     0x00000002
#घोषणा EGL_DRM_बफर_USE_CURSOR_MESA    0x00000004
प्रकार EGLImageKHR (EGLAPIENTRYP PFNEGLCREATEDRMIMAGEMESAPROC) (EGLDisplay dpy, स्थिर EGLint *attrib_list);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLEXPORTDRMIMAGEMESAPROC) (EGLDisplay dpy, EGLImageKHR image, EGLint *name, EGLint *handle, EGLint *stride);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLImageKHR EGLAPIENTRY eglCreateDRMImageMESA (EGLDisplay dpy, स्थिर EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglExportDRMImageMESA (EGLDisplay dpy, EGLImageKHR image, EGLint *name, EGLint *handle, EGLint *stride);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_MESA_drm_image */

#अगर_अघोषित EGL_MESA_image_dma_buf_export
#घोषणा EGL_MESA_image_dma_buf_export 1
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLEXPORTDMABUFIMAGEQUERYMESAPROC) (EGLDisplay dpy, EGLImageKHR image, पूर्णांक *fourcc, पूर्णांक *अंक_planes, EGLuint64KHR *modifiers);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLEXPORTDMABUFIMAGEMESAPROC) (EGLDisplay dpy, EGLImageKHR image, पूर्णांक *fds, EGLint *strides, EGLint *offsets);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglExportDMABUFImageQueryMESA (EGLDisplay dpy, EGLImageKHR image, पूर्णांक *fourcc, पूर्णांक *अंक_planes, EGLuint64KHR *modifiers);
EGLAPI EGLBoolean EGLAPIENTRY eglExportDMABUFImageMESA (EGLDisplay dpy, EGLImageKHR image, पूर्णांक *fds, EGLint *strides, EGLint *offsets);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_MESA_image_dma_buf_export */

#अगर_अघोषित EGL_MESA_platform_gbm
#घोषणा EGL_MESA_platform_gbm 1
#घोषणा EGL_PLATFORM_GBM_MESA             0x31D7
#पूर्ण_अगर /* EGL_MESA_platform_gbm */

#अगर_अघोषित EGL_MESA_platform_surfaceless
#घोषणा EGL_MESA_platform_surfaceless 1
#घोषणा EGL_PLATFORM_SURFACELESS_MESA     0x31DD
#पूर्ण_अगर /* EGL_MESA_platform_surfaceless */

#अगर_अघोषित EGL_MESA_query_driver
#घोषणा EGL_MESA_query_driver 1
प्रकार अक्षर *(EGLAPIENTRYP PFNEGLGETDISPLAYDRIVERCONFIGPROC) (EGLDisplay dpy);
प्रकार स्थिर अक्षर *(EGLAPIENTRYP PFNEGLGETDISPLAYDRIVERNAMEPROC) (EGLDisplay dpy);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI अक्षर *EGLAPIENTRY eglGetDisplayDriverConfig (EGLDisplay dpy);
EGLAPI स्थिर अक्षर *EGLAPIENTRY eglGetDisplayDriverName (EGLDisplay dpy);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_MESA_query_driver */

#अगर_अघोषित EGL_NOK_swap_region
#घोषणा EGL_NOK_swap_region 1
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSREGIONNOKPROC) (EGLDisplay dpy, EGLSurface surface, EGLint अंक_Rects_2, स्थिर EGLint *rects);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglSwapBuffersRegionNOK (EGLDisplay dpy, EGLSurface surface, EGLint अंक_Rects_2, स्थिर EGLint *rects);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_NOK_swap_region */

#अगर_अघोषित EGL_NOK_swap_region2
#घोषणा EGL_NOK_swap_region2 1
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSREGION2NOKPROC) (EGLDisplay dpy, EGLSurface surface, EGLint अंक_Rects_2, स्थिर EGLint *rects);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglSwapBuffersRegion2NOK (EGLDisplay dpy, EGLSurface surface, EGLint अंक_Rects_2, स्थिर EGLint *rects);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_NOK_swap_region2 */

#अगर_अघोषित EGL_NOK_texture_from_pixmap
#घोषणा EGL_NOK_texture_from_pixmap 1
#घोषणा EGL_Y_INVERTED_NOK                0x307F
#पूर्ण_अगर /* EGL_NOK_texture_from_pixmap */

#अगर_अघोषित EGL_NV_3dvision_surface
#घोषणा EGL_NV_3dvision_surface 1
#घोषणा EGL_AUTO_STEREO_NV                0x3136
#पूर्ण_अगर /* EGL_NV_3dvision_surface */

#अगर_अघोषित EGL_NV_context_priority_realtime
#घोषणा EGL_NV_context_priority_realtime 1
#घोषणा EGL_CONTEXT_PRIORITY_REALTIME_NV  0x3357
#पूर्ण_अगर /* EGL_NV_context_priority_realtime */

#अगर_अघोषित EGL_NV_coverage_sample
#घोषणा EGL_NV_coverage_sample 1
#घोषणा EGL_COVERAGE_BUFFERS_NV           0x30E0
#घोषणा EGL_COVERAGE_SAMPLES_NV           0x30E1
#पूर्ण_अगर /* EGL_NV_coverage_sample */

#अगर_अघोषित EGL_NV_coverage_sample_resolve
#घोषणा EGL_NV_coverage_sample_resolve 1
#घोषणा EGL_COVERAGE_SAMPLE_RESOLVE_NV    0x3131
#घोषणा EGL_COVERAGE_SAMPLE_RESOLVE_DEFAULT_NV 0x3132
#घोषणा EGL_COVERAGE_SAMPLE_RESOLVE_NONE_NV 0x3133
#पूर्ण_अगर /* EGL_NV_coverage_sample_resolve */

#अगर_अघोषित EGL_NV_cuda_event
#घोषणा EGL_NV_cuda_event 1
#घोषणा EGL_CUDA_EVENT_HANDLE_NV          0x323B
#घोषणा EGL_SYNC_CUDA_EVENT_NV            0x323C
#घोषणा EGL_SYNC_CUDA_EVENT_COMPLETE_NV   0x323D
#पूर्ण_अगर /* EGL_NV_cuda_event */

#अगर_अघोषित EGL_NV_depth_nonlinear
#घोषणा EGL_NV_depth_nonlinear 1
#घोषणा EGL_DEPTH_ENCODING_NV             0x30E2
#घोषणा EGL_DEPTH_ENCODING_NONE_NV        0
#घोषणा EGL_DEPTH_ENCODING_NONLINEAR_NV   0x30E3
#पूर्ण_अगर /* EGL_NV_depth_nonlinear */

#अगर_अघोषित EGL_NV_device_cuda
#घोषणा EGL_NV_device_cuda 1
#घोषणा EGL_CUDA_DEVICE_NV                0x323A
#पूर्ण_अगर /* EGL_NV_device_cuda */

#अगर_अघोषित EGL_NV_native_query
#घोषणा EGL_NV_native_query 1
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLQUERYNATIVEDISPLAYNVPROC) (EGLDisplay dpy, EGLNativeDisplayType *display_id);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLQUERYNATIVEWINDOWNVPROC) (EGLDisplay dpy, EGLSurface surf, EGLNativeWindowType *window);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLQUERYNATIVEPIXMAPNVPROC) (EGLDisplay dpy, EGLSurface surf, EGLNativePixmapType *pixmap);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryNativeDisplayNV (EGLDisplay dpy, EGLNativeDisplayType *display_id);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryNativeWindowNV (EGLDisplay dpy, EGLSurface surf, EGLNativeWindowType *window);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryNativePixmapNV (EGLDisplay dpy, EGLSurface surf, EGLNativePixmapType *pixmap);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_NV_native_query */

#अगर_अघोषित EGL_NV_post_convert_rounding
#घोषणा EGL_NV_post_convert_rounding 1
#पूर्ण_अगर /* EGL_NV_post_convert_rounding */

#अगर_अघोषित EGL_NV_post_sub_बफर
#घोषणा EGL_NV_post_sub_बफर 1
#घोषणा EGL_POST_SUB_बफर_SUPPORTED_NV  0x30BE
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLPOSTSUBBUFFERNVPROC) (EGLDisplay dpy, EGLSurface surface, EGLint x, EGLint y, EGLint width, EGLint height);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Post_Sub_बफर_NV (EGLDisplay dpy, EGLSurface surface, EGLint x, EGLint y, EGLint width, EGLint height);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_NV_post_sub_buffer */

#अगर_अघोषित EGL_NV_quadruple_बफर
#घोषणा EGL_NV_quadruple_बफर 1
#घोषणा EGL_QUADRUPLE_बफर_NV           0x3231
#पूर्ण_अगर /* EGL_NV_quadruple_buffer */

#अगर_अघोषित EGL_NV_robustness_video_memory_purge
#घोषणा EGL_NV_robustness_video_memory_purge 1
#घोषणा EGL_GENERATE_RESET_ON_VIDEO_MEMORY_PURGE_NV 0x334C
#पूर्ण_अगर /* EGL_NV_robustness_video_memory_purge */

#अगर_अघोषित EGL_NV_stream_consumer_eglimage
#घोषणा EGL_NV_stream_consumer_eglimage 1
#घोषणा EGL_STREAM_CONSUMER_IMAGE_NV      0x3373
#घोषणा EGL_STREAM_IMAGE_ADD_NV           0x3374
#घोषणा EGL_STREAM_IMAGE_REMOVE_NV        0x3375
#घोषणा EGL_STREAM_IMAGE_AVAILABLE_NV     0x3376
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMIMAGECONSUMERCONNECTNVPROC) (EGLDisplay dpy, EGLStreamKHR stream, EGLint अंक_modifiers, स्थिर EGLuint64KHR *modifiers, स्थिर EGLAttrib *attrib_list);
प्रकार EGLint (EGLAPIENTRYP PFNEGLQUERYSTREAMCONSUMEREVENTNVPROC) (EGLDisplay dpy, EGLStreamKHR stream, EGLTime timeout, EGLenum *event, EGLAttrib *aux);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMACQUIREIMAGENVPROC) (EGLDisplay dpy, EGLStreamKHR stream, EGLImage *pImage, EGLSync sync);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMRELEASEIMAGENVPROC) (EGLDisplay dpy, EGLStreamKHR stream, EGLImage image, EGLSync sync);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglStreamImageConsumerConnectNV (EGLDisplay dpy, EGLStreamKHR stream, EGLint अंक_modifiers, स्थिर EGLuint64KHR *modifiers, स्थिर EGLAttrib *attrib_list);
EGLAPI EGLint EGLAPIENTRY eglQueryStreamConsumerEventNV (EGLDisplay dpy, EGLStreamKHR stream, EGLTime timeout, EGLenum *event, EGLAttrib *aux);
EGLAPI EGLBoolean EGLAPIENTRY eglStreamAcquireImageNV (EGLDisplay dpy, EGLStreamKHR stream, EGLImage *pImage, EGLSync sync);
EGLAPI EGLBoolean EGLAPIENTRY eglStreamReleaseImageNV (EGLDisplay dpy, EGLStreamKHR stream, EGLImage image, EGLSync sync);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_NV_stream_consumer_eglimage */

#अगर_अघोषित EGL_NV_stream_consumer_eglimage_use_scanout_attrib
#घोषणा EGL_NV_stream_consumer_eglimage_use_scanout_attrib 1
#घोषणा EGL_STREAM_CONSUMER_IMAGE_USE_SCANOUT_NV 0x3378
#पूर्ण_अगर /* EGL_NV_stream_consumer_eglimage_use_scanout_attrib */

#अगर_अघोषित EGL_NV_stream_consumer_gltexture_yuv
#घोषणा EGL_NV_stream_consumer_gltexture_yuv 1
#घोषणा EGL_YUV_PLANE0_TEXTURE_UNIT_NV    0x332C
#घोषणा EGL_YUV_PLANE1_TEXTURE_UNIT_NV    0x332D
#घोषणा EGL_YUV_PLANE2_TEXTURE_UNIT_NV    0x332E
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALATTRIBSNVPROC) (EGLDisplay dpy, EGLStreamKHR stream, स्थिर EGLAttrib *attrib_list);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglStreamConsumerGLTextureExternalAttribsNV (EGLDisplay dpy, EGLStreamKHR stream, स्थिर EGLAttrib *attrib_list);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_NV_stream_consumer_gltexture_yuv */

#अगर_अघोषित EGL_NV_stream_cross_display
#घोषणा EGL_NV_stream_cross_display 1
#घोषणा EGL_STREAM_CROSS_DISPLAY_NV       0x334E
#पूर्ण_अगर /* EGL_NV_stream_cross_display */

#अगर_अघोषित EGL_NV_stream_cross_object
#घोषणा EGL_NV_stream_cross_object 1
#घोषणा EGL_STREAM_CROSS_OBJECT_NV        0x334D
#पूर्ण_अगर /* EGL_NV_stream_cross_object */

#अगर_अघोषित EGL_NV_stream_cross_partition
#घोषणा EGL_NV_stream_cross_partition 1
#घोषणा EGL_STREAM_CROSS_PARTITION_NV     0x323F
#पूर्ण_अगर /* EGL_NV_stream_cross_partition */

#अगर_अघोषित EGL_NV_stream_cross_process
#घोषणा EGL_NV_stream_cross_process 1
#घोषणा EGL_STREAM_CROSS_PROCESS_NV       0x3245
#पूर्ण_अगर /* EGL_NV_stream_cross_process */

#अगर_अघोषित EGL_NV_stream_cross_system
#घोषणा EGL_NV_stream_cross_system 1
#घोषणा EGL_STREAM_CROSS_SYSTEM_NV        0x334F
#पूर्ण_अगर /* EGL_NV_stream_cross_system */

#अगर_अघोषित EGL_NV_stream_dma
#घोषणा EGL_NV_stream_dma 1
#घोषणा EGL_STREAM_DMA_NV                 0x3371
#घोषणा EGL_STREAM_DMA_SERVER_NV          0x3372
#पूर्ण_अगर /* EGL_NV_stream_dma */

#अगर_अघोषित EGL_NV_stream_fifo_अग्र
#घोषणा EGL_NV_stream_fifo_अग्र 1
#घोषणा EGL_PENDING_FRAME_NV              0x3329
#घोषणा EGL_STREAM_TIME_PENDING_NV        0x332A
#पूर्ण_अगर /* EGL_NV_stream_fifo_next */

#अगर_अघोषित EGL_NV_stream_fifo_synchronous
#घोषणा EGL_NV_stream_fifo_synchronous 1
#घोषणा EGL_STREAM_FIFO_SYNCHRONOUS_NV    0x3336
#पूर्ण_अगर /* EGL_NV_stream_fifo_synchronous */

#अगर_अघोषित EGL_NV_stream_flush
#घोषणा EGL_NV_stream_flush 1
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMFLUSHNVPROC) (EGLDisplay dpy, EGLStreamKHR stream);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglStreamFlushNV (EGLDisplay dpy, EGLStreamKHR stream);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_NV_stream_flush */

#अगर_अघोषित EGL_NV_stream_frame_limits
#घोषणा EGL_NV_stream_frame_limits 1
#घोषणा EGL_PRODUCER_MAX_FRAME_HINT_NV    0x3337
#घोषणा EGL_CONSUMER_MAX_FRAME_HINT_NV    0x3338
#पूर्ण_अगर /* EGL_NV_stream_frame_limits */

#अगर_अघोषित EGL_NV_stream_metadata
#घोषणा EGL_NV_stream_metadata 1
#घोषणा EGL_MAX_STREAM_METADATA_BLOCKS_NV 0x3250
#घोषणा EGL_MAX_STREAM_METADATA_BLOCK_आकार_NV 0x3251
#घोषणा EGL_MAX_STREAM_METADATA_योग_आकार_NV 0x3252
#घोषणा EGL_PRODUCER_METADATA_NV          0x3253
#घोषणा EGL_CONSUMER_METADATA_NV          0x3254
#घोषणा EGL_PENDING_METADATA_NV           0x3328
#घोषणा EGL_METADATA0_आकार_NV             0x3255
#घोषणा EGL_METADATA1_आकार_NV             0x3256
#घोषणा EGL_METADATA2_आकार_NV             0x3257
#घोषणा EGL_METADATA3_आकार_NV             0x3258
#घोषणा EGL_METADATA0_TYPE_NV             0x3259
#घोषणा EGL_METADATA1_TYPE_NV             0x325A
#घोषणा EGL_METADATA2_TYPE_NV             0x325B
#घोषणा EGL_METADATA3_TYPE_NV             0x325C
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDISPLAYATTRIBNVPROC) (EGLDisplay dpy, EGLint attribute, EGLAttrib *मूल्य);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLSETSTREAMMETADATANVPROC) (EGLDisplay dpy, EGLStreamKHR stream, EGLint n, EGLint offset, EGLint आकार, स्थिर व्योम *तथ्य);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMMETADATANVPROC) (EGLDisplay dpy, EGLStreamKHR stream, EGLenum name, EGLint n, EGLint offset, EGLint आकार, व्योम *तथ्य);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDisplayAttribNV (EGLDisplay dpy, EGLint attribute, EGLAttrib *मूल्य);
EGLAPI EGLBoolean EGLAPIENTRY eglSetStreamMetadataNV (EGLDisplay dpy, EGLStreamKHR stream, EGLint n, EGLint offset, EGLint आकार, स्थिर व्योम *तथ्य);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryStreamMetadataNV (EGLDisplay dpy, EGLStreamKHR stream, EGLenum name, EGLint n, EGLint offset, EGLint आकार, व्योम *तथ्य);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_NV_stream_metadata */

#अगर_अघोषित EGL_NV_stream_origin
#घोषणा EGL_NV_stream_origin 1
#घोषणा EGL_STREAM_FRAME_ORIGIN_X_NV      0x3366
#घोषणा EGL_STREAM_FRAME_ORIGIN_Y_NV      0x3367
#घोषणा EGL_STREAM_FRAME_MAJOR_AXIS_NV    0x3368
#घोषणा EGL_CONSUMER_AUTO_ORIENTATION_NV  0x3369
#घोषणा EGL_PRODUCER_AUTO_ORIENTATION_NV  0x336A
#घोषणा EGL_बायाँ_NV                       0x336B
#घोषणा EGL_दायाँ_NV                      0x336C
#घोषणा EGL_शीर्ष_NV                        0x336D
#घोषणा EGL_BOTTOM_NV                     0x336E
#घोषणा EGL_X_AXIS_NV                     0x336F
#घोषणा EGL_Y_AXIS_NV                     0x3370
#पूर्ण_अगर /* EGL_NV_stream_origin */

#अगर_अघोषित EGL_NV_stream_remote
#घोषणा EGL_NV_stream_remote 1
#घोषणा EGL_STREAM_STATE_INITIALIZING_NV  0x3240
#घोषणा EGL_STREAM_TYPE_NV                0x3241
#घोषणा EGL_STREAM_PROTOCOL_NV            0x3242
#घोषणा EGL_STREAM_ENDPOINT_NV            0x3243
#घोषणा EGL_STREAM_LOCAL_NV               0x3244
#घोषणा EGL_STREAM_PRODUCER_NV            0x3247
#घोषणा EGL_STREAM_CONSUMER_NV            0x3248
#घोषणा EGL_STREAM_PROTOCOL_FD_NV         0x3246
#पूर्ण_अगर /* EGL_NV_stream_remote */

#अगर_अघोषित EGL_NV_stream_reset
#घोषणा EGL_NV_stream_reset 1
#घोषणा EGL_SUPPORT_RESET_NV              0x3334
#घोषणा EGL_SUPPORT_REUSE_NV              0x3335
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLRESETSTREAMNVPROC) (EGLDisplay dpy, EGLStreamKHR stream);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglResetStreamNV (EGLDisplay dpy, EGLStreamKHR stream);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_NV_stream_reset */

#अगर_अघोषित EGL_NV_stream_socket
#घोषणा EGL_NV_stream_socket 1
#घोषणा EGL_STREAM_PROTOCOL_SOCKET_NV     0x324B
#घोषणा EGL_SOCKET_HANDLE_NV              0x324C
#घोषणा EGL_SOCKET_TYPE_NV                0x324D
#पूर्ण_अगर /* EGL_NV_stream_socket */

#अगर_अघोषित EGL_NV_stream_socket_inet
#घोषणा EGL_NV_stream_socket_inet 1
#घोषणा EGL_SOCKET_TYPE_INET_NV           0x324F
#पूर्ण_अगर /* EGL_NV_stream_socket_inet */

#अगर_अघोषित EGL_NV_stream_socket_unix
#घोषणा EGL_NV_stream_socket_unix 1
#घोषणा EGL_SOCKET_TYPE_UNIX_NV           0x324E
#पूर्ण_अगर /* EGL_NV_stream_socket_unix */

#अगर_अघोषित EGL_NV_stream_sync
#घोषणा EGL_NV_stream_sync 1
#घोषणा EGL_SYNC_NEW_FRAME_NV             0x321F
प्रकार EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESTREAMSYNCNVPROC) (EGLDisplay dpy, EGLStreamKHR stream, EGLenum type, स्थिर EGLint *attrib_list);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncKHR EGLAPIENTRY eglCreateStreamSyncNV (EGLDisplay dpy, EGLStreamKHR stream, EGLenum type, स्थिर EGLint *attrib_list);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_NV_stream_sync */

#अगर_अघोषित EGL_NV_sync
#घोषणा EGL_NV_sync 1
प्रकार व्योम *EGLSyncNV;
प्रकार khronos_utime_nanoseconds_t EGLTimeNV;
#अगर_घोषित KHRONOS_SUPPORT_INT64
#घोषणा EGL_SYNC_PRIOR_COMMANDS_COMPLETE_NV 0x30E6
#घोषणा EGL_SYNC_STATUS_NV                0x30E7
#घोषणा EGL_SIGNALED_NV                   0x30E8
#घोषणा EGL_UNSIGNALED_NV                 0x30E9
#घोषणा EGL_SYNC_FLUSH_COMMANDS_BIT_NV    0x0001
#घोषणा EGL_FOREVER_NV                    0xFFFFFFFFFFFFFFFFull
#घोषणा EGL_ALREADY_SIGNALED_NV           0x30EA
#घोषणा EGL_TIMEOUT_EXPIRED_NV            0x30EB
#घोषणा EGL_CONDITION_SATISFIED_NV        0x30EC
#घोषणा EGL_SYNC_TYPE_NV                  0x30ED
#घोषणा EGL_SYNC_CONDITION_NV             0x30EE
#घोषणा EGL_SYNC_FENCE_NV                 0x30EF
#घोषणा EGL_NO_SYNC_NV                    EGL_CAST(EGLSyncNV,0)
प्रकार EGLSyncNV (EGLAPIENTRYP PFNEGLCREATEFENCESYNCNVPROC) (EGLDisplay dpy, EGLenum condition, स्थिर EGLint *attrib_list);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCNVPROC) (EGLSyncNV sync);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLFENCENVPROC) (EGLSyncNV sync);
प्रकार EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCNVPROC) (EGLSyncNV sync, EGLint flags, EGLTimeNV timeout);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLSIGNALSYNCNVPROC) (EGLSyncNV sync, EGLenum mode);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLGETSYNCATTRIBNVPROC) (EGLSyncNV sync, EGLint attribute, EGLint *मूल्य);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncNV EGLAPIENTRY eglCreateFenceSyncNV (EGLDisplay dpy, EGLenum condition, स्थिर EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySyncNV (EGLSyncNV sync);
EGLAPI EGLBoolean EGLAPIENTRY eglFenceNV (EGLSyncNV sync);
EGLAPI EGLint EGLAPIENTRY eglClientWaitSyncNV (EGLSyncNV sync, EGLint flags, EGLTimeNV timeout);
EGLAPI EGLBoolean EGLAPIENTRY eglSignalSyncNV (EGLSyncNV sync, EGLenum mode);
EGLAPI EGLBoolean EGLAPIENTRY eglGetSyncAttribNV (EGLSyncNV sync, EGLint attribute, EGLint *मूल्य);
#पूर्ण_अगर
#पूर्ण_अगर /* KHRONOS_SUPPORT_INT64 */
#पूर्ण_अगर /* EGL_NV_sync */

#अगर_अघोषित EGL_NV_system_time
#घोषणा EGL_NV_system_time 1
प्रकार khronos_utime_nanoseconds_t EGLuint64NV;
#अगर_घोषित KHRONOS_SUPPORT_INT64
प्रकार EGLuint64NV (EGLAPIENTRYP PFNEGLGETSYSTEMTIMEFREQUENCYNVPROC) (व्योम);
प्रकार EGLuint64NV (EGLAPIENTRYP PFNEGLGETSYSTEMTIMENVPROC) (व्योम);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLuint64NV EGLAPIENTRY eglGetSystemTimeFrequencyNV (व्योम);
EGLAPI EGLuint64NV EGLAPIENTRY eglGetSystemTimeNV (व्योम);
#पूर्ण_अगर
#पूर्ण_अगर /* KHRONOS_SUPPORT_INT64 */
#पूर्ण_अगर /* EGL_NV_system_time */

#अगर_अघोषित EGL_NV_triple_बफर
#घोषणा EGL_NV_triple_बफर 1
#घोषणा EGL_TRIPLE_बफर_NV              0x3230
#पूर्ण_अगर /* EGL_NV_triple_buffer */

#अगर_अघोषित EGL_QNX_image_native_बफर
#घोषणा EGL_QNX_image_native_बफर 1
#घोषणा EGL_NATIVE_बफर_QNX             0x3551
#पूर्ण_अगर /* EGL_QNX_image_native_buffer */

#अगर_अघोषित EGL_QNX_platform_screen
#घोषणा EGL_QNX_platform_screen 1
#घोषणा EGL_PLATFORM_SCREEN_QNX           0x3550
#पूर्ण_अगर /* EGL_QNX_platform_screen */

#अगर_अघोषित EGL_TIZEN_image_native_बफर
#घोषणा EGL_TIZEN_image_native_बफर 1
#घोषणा EGL_NATIVE_बफर_TIZEN           0x32A0
#पूर्ण_अगर /* EGL_TIZEN_image_native_buffer */

#अगर_अघोषित EGL_TIZEN_image_native_surface
#घोषणा EGL_TIZEN_image_native_surface 1
#घोषणा EGL_NATIVE_SURFACE_TIZEN          0x32A1
#पूर्ण_अगर /* EGL_TIZEN_image_native_surface */

#अगर_अघोषित EGL_WL_bind_wayland_display
#घोषणा EGL_WL_bind_wayland_display 1
#घोषणा PFNEGLBINDWAYLANDDISPLAYWL PFNEGLBINDWAYLANDDISPLAYWLPROC
#घोषणा PFNEGLUNBINDWAYLANDDISPLAYWL PFNEGLUNBINDWAYLANDDISPLAYWLPROC
#घोषणा PFNEGLQUERYWAYLANDBUFFERWL PFNEGLQUERYWAYLANDBUFFERWLPROC
काष्ठा wl_display;
काष्ठा wl_resource;
#घोषणा EGL_WAYLAND_बफर_WL             0x31D5
#घोषणा EGL_WAYLAND_PLANE_WL              0x31D6
#घोषणा EGL_TEXTURE_Y_U_V_WL              0x31D7
#घोषणा EGL_TEXTURE_Y_UV_WL               0x31D8
#घोषणा EGL_TEXTURE_Y_XUXV_WL             0x31D9
#घोषणा EGL_TEXTURE_EXTERNAL_WL           0x31DA
#घोषणा EGL_WAYLAND_Y_INVERTED_WL         0x31DB
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLBINDWAYLANDDISPLAYWLPROC) (EGLDisplay dpy, काष्ठा wl_display *display);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLUNBINDWAYLANDDISPLAYWLPROC) (EGLDisplay dpy, काष्ठा wl_display *display);
प्रकार EGLBoolean (EGLAPIENTRYP PFNEGLQUERYWAYLANDBUFFERWLPROC) (EGLDisplay dpy, काष्ठा wl_resource *बफर_2, EGLint attribute, EGLint *मूल्य);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglBindWaylandDisplayWL (EGLDisplay dpy, काष्ठा wl_display *display);
EGLAPI EGLBoolean EGLAPIENTRY eglUnbindWaylandDisplayWL (EGLDisplay dpy, काष्ठा wl_display *display);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Wayland_बफर_WL (EGLDisplay dpy, काष्ठा wl_resource *बफर_2, EGLint attribute, EGLint *मूल्य);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_WL_bind_wayland_display */

#अगर_अघोषित EGL_WL_create_wayland_बफर_from_image
#घोषणा EGL_WL_create_wayland_बफर_from_image 1
#घोषणा PFNEGLCREATEWAYLANDBUFFERFROMIMAGEWL PFNEGLCREATEWAYLANDBUFFERFROMIMAGEWLPROC
काष्ठा wl_बफर;
प्रकार काष्ठा wl_बफर *(EGLAPIENTRYP PFNEGLCREATEWAYLANDBUFFERFROMIMAGEWLPROC) (EGLDisplay dpy, EGLImageKHR image);
#अगर_घोषित EGL_EGLEXT_PROTOTYPES
EGLAPI काष्ठा wl_बफर *EGLAPIENTRY egl_Create_Wayland_बफर_From_Image_WL (EGLDisplay dpy, EGLImageKHR image);
#पूर्ण_अगर
#पूर्ण_अगर /* EGL_WL_create_wayland_buffer_from_image */

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर
