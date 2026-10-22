#నిర్వచితం_కాకపోతే __eglext_h_
#నిర్వచించు __eglext_h_ 1

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

#నిర్వచించు EGL_EGLEXT_సంస్కరణ 20260319

/* Generated C header for:
 * API: egl
 * Versions considered: .*
 * Versions emitted: _nomatch_^
 * Default extensions included: egl
 * Additional extensions included: _nomatch_^
 * Extensions removed: _nomatch_^
 */

#నిర్వచితం_కాకపోతే EGL_KHR_cl_event
#నిర్వచించు EGL_KHR_cl_event 1
#నిర్వచించు EGL_CL_EVENT_HANDLE_KHR           0x309C
#నిర్వచించు EGL_SYNC_CL_EVENT_KHR             0x30FE
#నిర్వచించు EGL_SYNC_CL_EVENT_COMPLETE_KHR    0x30FF
#అయితే_ముగింపు /* EGL_KHR_cl_event */

#నిర్వచితం_కాకపోతే EGL_KHR_cl_event2
#నిర్వచించు EGL_KHR_cl_event2 1
రకనిర్వచనం శూన్య *EGLSyncKHR;
రకనిర్వచనం intptr_t EGLAttribKHR;
రకనిర్వచనం EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESYNC64KHRPROC) (EGLDisplay dpy, EGLenum type, స్థిరరాశి EGLAttribKHR *attrib_list);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncKHR EGLAPIENTRY eglCreateSync64KHR (EGLDisplay dpy, EGLenum type, స్థిరరాశి EGLAttribKHR *attrib_list);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_KHR_cl_event2 */

#నిర్వచితం_కాకపోతే EGL_KHR_client_get_all_proc_చిరునామాలు
#నిర్వచించు EGL_KHR_client_get_all_proc_చిరునామాలు 1
#అయితే_ముగింపు /* EGL_KHR_client_get_all_proc_addresses */

#నిర్వచితం_కాకపోతే EGL_KHR_config_attribs
#నిర్వచించు EGL_KHR_config_attribs 1
#నిర్వచించు EGL_CONFORMANT_KHR                0x3042
#నిర్వచించు EGL_VG_COLORSPACE_రేఖీయ_బిట్టు_KHR  0x0020
#నిర్వచించు EGL_VG_ALPHA_FORMAT_PRE_బిట్టు_KHR   0x0040
#అయితే_ముగింపు /* EGL_KHR_config_attribs */

#నిర్వచితం_కాకపోతే EGL_KHR_context_flush_control
#నిర్వచించు EGL_KHR_context_flush_control 1
#నిర్వచించు EGL_CONTEXT_RELEASE_BEHAVIOR_NONE_KHR 0
#నిర్వచించు EGL_CONTEXT_RELEASE_BEHAVIOR_KHR  0x2097
#నిర్వచించు EGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_KHR 0x2098
#అయితే_ముగింపు /* EGL_KHR_context_flush_control */

#నిర్వచితం_కాకపోతే EGL_KHR_create_context
#నిర్వచించు EGL_KHR_create_context 1
#నిర్వచించు EGL_CONTEXT_MAJOR_సంస్కరణ_KHR     0x3098
#నిర్వచించు EGL_CONTEXT_MINOR_సంస్కరణ_KHR     0x30FB
#నిర్వచించు EGL_CONTEXT_FLAGS_KHR             0x30FC
#నిర్వచించు EGL_CONTEXT_OPENGL_PROFILE_ముసుగు_KHR 0x30FD
#నిర్వచించు EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_KHR 0x31BD
#నిర్వచించు EGL_NO_RESET_NOTIFICATION_KHR     0x31BE
#నిర్వచించు EGL_LOSE_CONTEXT_ON_RESET_KHR     0x31BF
#నిర్వచించు EGL_CONTEXT_OPENGL_DEBUG_బిట్టు_KHR  0x00000001
#నిర్వచించు EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_బిట్టు_KHR 0x00000002
#నిర్వచించు EGL_CONTEXT_OPENGL_ROBUST_ACCESS_బిట్టు_KHR 0x00000004
#నిర్వచించు EGL_CONTEXT_OPENGL_CORE_PROFILE_బిట్టు_KHR 0x00000001
#నిర్వచించు EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_బిట్టు_KHR 0x00000002
#నిర్వచించు EGL_OPENGL_ES3_బిట్టు_KHR            0x00000040
#అయితే_ముగింపు /* EGL_KHR_create_context */

#నిర్వచితం_కాకపోతే EGL_KHR_create_context_no_error
#నిర్వచించు EGL_KHR_create_context_no_error 1
#నిర్వచించు EGL_CONTEXT_OPENGL_NO_ERROR_KHR   0x31B3
#అయితే_ముగింపు /* EGL_KHR_create_context_no_error */

#నిర్వచితం_కాకపోతే EGL_KHR_debug
#నిర్వచించు EGL_KHR_debug 1
రకనిర్వచనం శూన్య *EGLLabelKHR;
రకనిర్వచనం శూన్య *EGLObjectKHR;
రకనిర్వచనం శూన్య (EGLAPIENTRY  *EGLDEBUGPROCKHR)(EGLenum error,స్థిరరాశి అక్షరం *command,EGLint సందేశం_Type,EGLLabelKHR threadLabel,EGLLabelKHR objectLabel,స్థిరరాశి అక్షరం* సందేశం);
#నిర్వచించు EGL_OBJECT_THREAD_KHR             0x33B0
#నిర్వచించు EGL_OBJECT_DISPLAY_KHR            0x33B1
#నిర్వచించు EGL_OBJECT_CONTEXT_KHR            0x33B2
#నిర్వచించు EGL_OBJECT_SURFACE_KHR            0x33B3
#నిర్వచించు EGL_OBJECT_IMAGE_KHR              0x33B4
#నిర్వచించు EGL_OBJECT_SYNC_KHR               0x33B5
#నిర్వచించు EGL_OBJECT_ప్రవాహం_KHR             0x33B6
#నిర్వచించు EGL_DEBUG_సందేశం_CRITICAL_KHR        0x33B9
#నిర్వచించు EGL_DEBUG_సందేశం_ERROR_KHR           0x33BA
#నిర్వచించు EGL_DEBUG_సందేశం_WARN_KHR            0x33BB
#నిర్వచించు EGL_DEBUG_సందేశం_INFO_KHR            0x33BC
#నిర్వచించు EGL_DEBUG_CALLBACK_KHR            0x33B8
రకనిర్వచనం EGLint (EGLAPIENTRYP PFNEGLDEBUGMESSAGECONTROLKHRPROC) (EGLDEBUGPROCKHR callback, స్థిరరాశి EGLAttrib *attrib_list);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEBUGKHRPROC) (EGLint attribute, EGLAttrib *విలువ);
రకనిర్వచనం EGLint (EGLAPIENTRYP PFNEGLLABELOBJECTKHRPROC) (EGLDisplay display, EGLenum objectType, EGLObjectKHR object, EGLLabelKHR label);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLint EGLAPIENTRY egl_Debug_సందేశం_Control_KHR (EGLDEBUGPROCKHR callback, స్థిరరాశి EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDebugKHR (EGLint attribute, EGLAttrib *విలువ);
EGLAPI EGLint EGLAPIENTRY eglLabelObjectKHR (EGLDisplay display, EGLenum objectType, EGLObjectKHR object, EGLLabelKHR label);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_KHR_debug */

#నిర్వచితం_కాకపోతే EGL_KHR_display_reference
#నిర్వచించు EGL_KHR_display_reference 1
#నిర్వచించు EGL_TRACK_REFERENCES_KHR          0x3352
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDISPLAYATTRIBKHRPROC) (EGLDisplay dpy, EGLint name, EGLAttrib *విలువ);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDisplayAttribKHR (EGLDisplay dpy, EGLint name, EGLAttrib *విలువ);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_KHR_display_reference */

#నిర్వచితం_కాకపోతే EGL_KHR_fence_sync
#నిర్వచించు EGL_KHR_fence_sync 1
రకనిర్వచనం khronos_utime_nanoseconds_t EGLTimeKHR;
#నిర్వచితమైతే KHRONOS_SUPPORT_INT64
#నిర్వచించు EGL_SYNC_పూర్వ_COMMANDS_COMPLETE_KHR 0x30F0
#నిర్వచించు EGL_SYNC_CONDITION_KHR            0x30F8
#నిర్వచించు EGL_SYNC_FENCE_KHR                0x30F9
రకనిర్వచనం EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESYNCKHRPROC) (EGLDisplay dpy, EGLenum type, స్థిరరాశి EGLint *attrib_list);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync);
రకనిర్వచనం EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLGETSYNCATTRIBKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint attribute, EGLint *విలువ);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncKHR EGLAPIENTRY eglCreateSyncKHR (EGLDisplay dpy, EGLenum type, స్థిరరాశి EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySyncKHR (EGLDisplay dpy, EGLSyncKHR sync);
EGLAPI EGLint EGLAPIENTRY eglClientWaitSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);
EGLAPI EGLBoolean EGLAPIENTRY eglGetSyncAttribKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint attribute, EGLint *విలువ);
#అయితే_ముగింపు
#అయితే_ముగింపు /* KHRONOS_SUPPORT_INT64 */
#అయితే_ముగింపు /* EGL_KHR_fence_sync */

#నిర్వచితం_కాకపోతే EGL_KHR_get_all_proc_చిరునామాలు
#నిర్వచించు EGL_KHR_get_all_proc_చిరునామాలు 1
#అయితే_ముగింపు /* EGL_KHR_get_all_proc_addresses */

#నిర్వచితం_కాకపోతే EGL_KHR_gl_colorspace
#నిర్వచించు EGL_KHR_gl_colorspace 1
#నిర్వచించు EGL_GL_COLORSPACE_KHR             0x309D
#నిర్వచించు EGL_GL_COLORSPACE_SRGB_KHR        0x3089
#నిర్వచించు EGL_GL_COLORSPACE_రేఖీయ_KHR      0x308A
#అయితే_ముగింపు /* EGL_KHR_gl_colorspace */

#నిర్వచితం_కాకపోతే EGL_KHR_gl_renderbuffer_image
#నిర్వచించు EGL_KHR_gl_renderbuffer_image 1
#నిర్వచించు EGL_GL_RENDERBUFFER_KHR           0x30B9
#అయితే_ముగింపు /* EGL_KHR_gl_renderbuffer_image */

#నిర్వచితం_కాకపోతే EGL_KHR_gl_texture_2D_image
#నిర్వచించు EGL_KHR_gl_texture_2D_image 1
#నిర్వచించు EGL_GL_TEXTURE_2D_KHR             0x30B1
#నిర్వచించు EGL_GL_TEXTURE_LEVEL_KHR          0x30BC
#అయితే_ముగింపు /* EGL_KHR_gl_texture_2D_image */

#నిర్వచితం_కాకపోతే EGL_KHR_gl_texture_3D_image
#నిర్వచించు EGL_KHR_gl_texture_3D_image 1
#నిర్వచించు EGL_GL_TEXTURE_3D_KHR             0x30B2
#నిర్వచించు EGL_GL_TEXTURE_ZOFFSET_KHR        0x30BD
#అయితే_ముగింపు /* EGL_KHR_gl_texture_3D_image */

#నిర్వచితం_కాకపోతే EGL_KHR_gl_texture_cubemap_image
#నిర్వచించు EGL_KHR_gl_texture_cubemap_image 1
#నిర్వచించు EGL_GL_TEXTURE_CUBE_MAP_ధనాత్మక_X_KHR 0x30B3
#నిర్వచించు EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_X_KHR 0x30B4
#నిర్వచించు EGL_GL_TEXTURE_CUBE_MAP_ధనాత్మక_Y_KHR 0x30B5
#నిర్వచించు EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_KHR 0x30B6
#నిర్వచించు EGL_GL_TEXTURE_CUBE_MAP_ధనాత్మక_Z_KHR 0x30B7
#నిర్వచించు EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_KHR 0x30B8
#అయితే_ముగింపు /* EGL_KHR_gl_texture_cubemap_image */

#నిర్వచితం_కాకపోతే EGL_KHR_image
#నిర్వచించు EGL_KHR_image 1
రకనిర్వచనం శూన్య *EGLImageKHR;
#నిర్వచించు EGL_NATIVE_PIXMAP_KHR             0x30B0
#నిర్వచించు EGL_NO_IMAGE_KHR                  EGL_CAST(EGLImageKHR,0)
రకనిర్వచనం EGLImageKHR (EGLAPIENTRYP PFNEGLCREATEIMAGEKHRPROC) (EGLDisplay dpy, EGLContext ctx, EGLenum లక్ష్యం, EGLClient_బఫరు బఫరు_2, స్థిరరాశి EGLint *attrib_list);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYIMAGEKHRPROC) (EGLDisplay dpy, EGLImageKHR image);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLImageKHR EGLAPIENTRY eglCreateImageKHR (EGLDisplay dpy, EGLContext ctx, EGLenum లక్ష్యం, EGLClient_బఫరు బఫరు_2, స్థిరరాశి EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyImageKHR (EGLDisplay dpy, EGLImageKHR image);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_KHR_image */

#నిర్వచితం_కాకపోతే EGL_KHR_image_పునాది
#నిర్వచించు EGL_KHR_image_పునాది 1
#నిర్వచించు EGL_IMAGE_PRESERVED_KHR           0x30D2
#అయితే_ముగింపు /* EGL_KHR_image_base */

#నిర్వచితం_కాకపోతే EGL_KHR_image_pixmap
#నిర్వచించు EGL_KHR_image_pixmap 1
#అయితే_ముగింపు /* EGL_KHR_image_pixmap */

#నిర్వచితం_కాకపోతే EGL_KHR_తాళం_surface
#నిర్వచించు EGL_KHR_తాళం_surface 1
#నిర్వచించు EGL_READ_SURFACE_బిట్టు_KHR          0x0001
#నిర్వచించు EGL_WRITE_SURFACE_బిట్టు_KHR         0x0002
#నిర్వచించు EGL_తాళం_SURFACE_బిట్టు_KHR          0x0080
#నిర్వచించు EGL_OPTIMAL_FORMAT_బిట్టు_KHR        0x0100
#నిర్వచించు EGL_సరిపోలిక_FORMAT_KHR              0x3043
#నిర్వచించు EGL_FORMAT_RGB_565_EXACT_KHR      0x30C0
#నిర్వచించు EGL_FORMAT_RGB_565_KHR            0x30C1
#నిర్వచించు EGL_FORMAT_RGBA_8888_EXACT_KHR    0x30C2
#నిర్వచించు EGL_FORMAT_RGBA_8888_KHR          0x30C3
#నిర్వచించు EGL_MAP_PRESERVE_PIXELS_KHR       0x30C4
#నిర్వచించు EGL_తాళం_USAGE_HINT_KHR           0x30C5
#నిర్వచించు EGL_BITMAP_సూచిక_KHR            0x30C6
#నిర్వచించు EGL_BITMAP_PITCH_KHR              0x30C7
#నిర్వచించు EGL_BITMAP_ORIGIN_KHR             0x30C8
#నిర్వచించు EGL_BITMAP_PIXEL_RED_స్థానభ్రంశం_KHR   0x30C9
#నిర్వచించు EGL_BITMAP_PIXEL_GREEN_స్థానభ్రంశం_KHR 0x30CA
#నిర్వచించు EGL_BITMAP_PIXEL_BLUE_స్థానభ్రంశం_KHR  0x30CB
#నిర్వచించు EGL_BITMAP_PIXEL_ALPHA_స్థానభ్రంశం_KHR 0x30CC
#నిర్వచించు EGL_BITMAP_PIXEL_LUMINANCE_స్థానభ్రంశం_KHR 0x30CD
#నిర్వచించు EGL_క్రింది_ఎడమ_KHR                0x30CE
#నిర్వచించు EGL_పై_ఎడమ_KHR                0x30CF
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLLOCKSURFACEKHRPROC) (EGLDisplay dpy, EGLSurface surface, స్థిరరాశి EGLint *attrib_list);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLUNLOCKSURFACEKHRPROC) (EGLDisplay dpy, EGLSurface surface);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_తాళం_Surface_KHR (EGLDisplay dpy, EGLSurface surface, స్థిరరాశి EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglUnlockSurfaceKHR (EGLDisplay dpy, EGLSurface surface);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_KHR_lock_surface */

#నిర్వచితం_కాకపోతే EGL_KHR_తాళం_surface2
#నిర్వచించు EGL_KHR_తాళం_surface2 1
#నిర్వచించు EGL_BITMAP_PIXEL_కొలత_KHR         0x3110
#అయితే_ముగింపు /* EGL_KHR_lock_surface2 */

#నిర్వచితం_కాకపోతే EGL_KHR_తాళం_surface3
#నిర్వచించు EGL_KHR_తాళం_surface3 1
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSURFACE64KHRPROC) (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLAttribKHR *విలువ);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQuerySurface64KHR (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLAttribKHR *విలువ);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_KHR_lock_surface3 */

#నిర్వచితం_కాకపోతే EGL_KHR_mutable_render_బఫరు
#నిర్వచించు EGL_KHR_mutable_render_బఫరు 1
#నిర్వచించు EGL_MUTABLE_RENDER_బఫరు_బిట్టు_KHR 0x1000
#అయితే_ముగింపు /* EGL_KHR_mutable_render_buffer */

#నిర్వచితం_కాకపోతే EGL_KHR_no_config_context
#నిర్వచించు EGL_KHR_no_config_context 1
#నిర్వచించు EGL_NO_CONFIG_KHR                 EGL_CAST(EGLConfig,0)
#అయితే_ముగింపు /* EGL_KHR_no_config_context */

#నిర్వచితం_కాకపోతే EGL_KHR_partial_update
#నిర్వచించు EGL_KHR_partial_update 1
#నిర్వచించు EGL_బఫరు_AGE_KHR                0x313D
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLSETDAMAGEREGIONKHRPROC) (EGLDisplay dpy, EGLSurface surface, EGLint *rects, EGLint n_rects);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_సమితి_Damage_Region_KHR (EGLDisplay dpy, EGLSurface surface, EGLint *rects, EGLint n_rects);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_KHR_partial_update */

#నిర్వచితం_కాకపోతే EGL_KHR_platform_android
#నిర్వచించు EGL_KHR_platform_android 1
#నిర్వచించు EGL_PLATFORM_ANDROID_KHR          0x3141
#అయితే_ముగింపు /* EGL_KHR_platform_android */

#నిర్వచితం_కాకపోతే EGL_KHR_platform_gbm
#నిర్వచించు EGL_KHR_platform_gbm 1
#నిర్వచించు EGL_PLATFORM_GBM_KHR              0x31D7
#అయితే_ముగింపు /* EGL_KHR_platform_gbm */

#నిర్వచితం_కాకపోతే EGL_KHR_platform_wayland
#నిర్వచించు EGL_KHR_platform_wayland 1
#నిర్వచించు EGL_PLATFORM_WAYLAND_KHR          0x31D8
#అయితే_ముగింపు /* EGL_KHR_platform_wayland */

#నిర్వచితం_కాకపోతే EGL_KHR_platform_x11
#నిర్వచించు EGL_KHR_platform_x11 1
#నిర్వచించు EGL_PLATFORM_X11_KHR              0x31D5
#నిర్వచించు EGL_PLATFORM_X11_SCREEN_KHR       0x31D6
#అయితే_ముగింపు /* EGL_KHR_platform_x11 */

#నిర్వచితం_కాకపోతే EGL_KHR_reusable_sync
#నిర్వచించు EGL_KHR_reusable_sync 1
#నిర్వచితమైతే KHRONOS_SUPPORT_INT64
#నిర్వచించు EGL_SYNC_స్థితి_KHR               0x30F1
#నిర్వచించు EGL_SIGNALED_KHR                  0x30F2
#నిర్వచించు EGL_UNSIGNALED_KHR                0x30F3
#నిర్వచించు EGL_TIMEOUT_EXPIRED_KHR           0x30F5
#నిర్వచించు EGL_CONDITION_SATISFIED_KHR       0x30F6
#నిర్వచించు EGL_SYNC_TYPE_KHR                 0x30F7
#నిర్వచించు EGL_SYNC_REUSABLE_KHR             0x30FA
#నిర్వచించు EGL_SYNC_FLUSH_COMMANDS_బిట్టు_KHR   0x0001
#నిర్వచించు EGL_FOREVER_KHR                   0xFFFFFFFFFFFFFFFFull
#నిర్వచించు EGL_NO_SYNC_KHR                   EGL_CAST(EGLSyncKHR,0)
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLSIGNALSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLenum బహుళకం);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglSignalSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLenum బహుళకం);
#అయితే_ముగింపు
#అయితే_ముగింపు /* KHRONOS_SUPPORT_INT64 */
#అయితే_ముగింపు /* EGL_KHR_reusable_sync */

#నిర్వచితం_కాకపోతే EGL_KHR_ప్రవాహం
#నిర్వచించు EGL_KHR_ప్రవాహం 1
రకనిర్వచనం శూన్య *EGLStreamKHR;
రకనిర్వచనం khronos_uint64_t EGLuint64KHR;
#నిర్వచితమైతే KHRONOS_SUPPORT_INT64
#నిర్వచించు EGL_NO_ప్రవాహం_KHR                 EGL_CAST(EGLStreamKHR,0)
#నిర్వచించు EGL_వినియోగదారు_LATENCY_USEC_KHR     0x3210
#నిర్వచించు EGL_ఉత్పాదకుడు_చట్రం_KHR            0x3212
#నిర్వచించు EGL_వినియోగదారు_చట్రం_KHR            0x3213
#నిర్వచించు EGL_ప్రవాహం_STATE_KHR              0x3214
#నిర్వచించు EGL_ప్రవాహం_STATE_CREATED_KHR      0x3215
#నిర్వచించు EGL_ప్రవాహం_STATE_CONNECTING_KHR   0x3216
#నిర్వచించు EGL_ప్రవాహం_STATE_ఖాళీలు_KHR        0x3217
#నిర్వచించు EGL_ప్రవాహం_STATE_NEW_చట్రం_అందుబాటు_KHR 0x3218
#నిర్వచించు EGL_ప్రవాహం_STATE_OLD_చట్రం_అందుబాటు_KHR 0x3219
#నిర్వచించు EGL_ప్రవాహం_STATE_DISCONNECTED_KHR 0x321A
#నిర్వచించు EGL_BAD_ప్రవాహం_KHR                0x321B
#నిర్వచించు EGL_BAD_STATE_KHR                 0x321C
రకనిర్వచనం EGLStreamKHR (EGLAPIENTRYP PFNEGLCREATESTREAMKHRPROC) (EGLDisplay dpy, స్థిరరాశి EGLint *attrib_list);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSTREAMKHRPROC) (EGLDisplay dpy, EGLStreamKHR ప్రవాహం);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR ప్రవాహం, EGLenum attribute, EGLint విలువ);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMKHRPROC) (EGLDisplay dpy, EGLStreamKHR ప్రవాహం, EGLenum attribute, EGLint *విలువ);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMU64KHRPROC) (EGLDisplay dpy, EGLStreamKHR ప్రవాహం, EGLenum attribute, EGLuint64KHR *విలువ);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLStreamKHR EGLAPIENTRY egl_Create_ప్రవాహం_KHR (EGLDisplay dpy, స్థిరరాశి EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY egl_Destroy_ప్రవాహం_KHR (EGLDisplay dpy, EGLStreamKHR ప్రవాహం);
EGLAPI EGLBoolean EGLAPIENTRY egl_ప్రవాహం_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR ప్రవాహం, EGLenum attribute, EGLint విలువ);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_ప్రవాహం_KHR (EGLDisplay dpy, EGLStreamKHR ప్రవాహం, EGLenum attribute, EGLint *విలువ);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryStreamu64KHR (EGLDisplay dpy, EGLStreamKHR ప్రవాహం, EGLenum attribute, EGLuint64KHR *విలువ);
#అయితే_ముగింపు
#అయితే_ముగింపు /* KHRONOS_SUPPORT_INT64 */
#అయితే_ముగింపు /* EGL_KHR_stream */

#నిర్వచితం_కాకపోతే EGL_KHR_ప్రవాహం_attrib
#నిర్వచించు EGL_KHR_ప్రవాహం_attrib 1
#నిర్వచితమైతే KHRONOS_SUPPORT_INT64
రకనిర్వచనం EGLStreamKHR (EGLAPIENTRYP PFNEGLCREATESTREAMATTRIBKHRPROC) (EGLDisplay dpy, స్థిరరాశి EGLAttrib *attrib_list);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLSETSTREAMATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR ప్రవాహం, EGLenum attribute, EGLAttrib విలువ);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR ప్రవాహం, EGLenum attribute, EGLAttrib *విలువ);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERACQUIREATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR ప్రవాహం, స్థిరరాశి EGLAttrib *attrib_list);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERRELEASEATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR ప్రవాహం, స్థిరరాశి EGLAttrib *attrib_list);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLStreamKHR EGLAPIENTRY egl_Create_ప్రవాహం_Attrib_KHR (EGLDisplay dpy, స్థిరరాశి EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY egl_సమితి_ప్రవాహం_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR ప్రవాహం, EGLenum attribute, EGLAttrib విలువ);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_ప్రవాహం_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR ప్రవాహం, EGLenum attribute, EGLAttrib *విలువ);
EGLAPI EGLBoolean EGLAPIENTRY egl_ప్రవాహం_వినియోగదారు_Acquire_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR ప్రవాహం, స్థిరరాశి EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY egl_ప్రవాహం_వినియోగదారు_Release_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR ప్రవాహం, స్థిరరాశి EGLAttrib *attrib_list);
#అయితే_ముగింపు
#అయితే_ముగింపు /* KHRONOS_SUPPORT_INT64 */
#అయితే_ముగింపు /* EGL_KHR_stream_attrib */

#నిర్వచితం_కాకపోతే EGL_KHR_ప్రవాహం_వినియోగదారు_gltexture
#నిర్వచించు EGL_KHR_ప్రవాహం_వినియోగదారు_gltexture 1
#నిర్వచితమైతే EGL_KHR_ప్రవాహం
#నిర్వచించు EGL_వినియోగదారు_ACQUIRE_TIMEOUT_USEC_KHR 0x321E
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALKHRPROC) (EGLDisplay dpy, EGLStreamKHR ప్రవాహం);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERACQUIREKHRPROC) (EGLDisplay dpy, EGLStreamKHR ప్రవాహం);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERRELEASEKHRPROC) (EGLDisplay dpy, EGLStreamKHR ప్రవాహం);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_ప్రవాహం_వినియోగదారు_GLTexture_External_KHR (EGLDisplay dpy, EGLStreamKHR ప్రవాహం);
EGLAPI EGLBoolean EGLAPIENTRY egl_ప్రవాహం_వినియోగదారు_Acquire_KHR (EGLDisplay dpy, EGLStreamKHR ప్రవాహం);
EGLAPI EGLBoolean EGLAPIENTRY egl_ప్రవాహం_వినియోగదారు_Release_KHR (EGLDisplay dpy, EGLStreamKHR ప్రవాహం);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_KHR_stream */
#అయితే_ముగింపు /* EGL_KHR_stream_consumer_gltexture */

#నిర్వచితం_కాకపోతే EGL_KHR_ప్రవాహం_cross_process_fd
#నిర్వచించు EGL_KHR_ప్రవాహం_cross_process_fd 1
రకనిర్వచనం పూర్ణాంకం EGLNativeFileDescriptorKHR;
#నిర్వచితమైతే EGL_KHR_ప్రవాహం
#నిర్వచించు EGL_NO_FILE_DESCRIPTOR_KHR        EGL_CAST(EGLNativeFileDescriptorKHR,-1)
రకనిర్వచనం EGLNativeFileDescriptorKHR (EGLAPIENTRYP PFNEGLGETSTREAMFILEDESCRIPTORKHRPROC) (EGLDisplay dpy, EGLStreamKHR ప్రవాహం);
రకనిర్వచనం EGLStreamKHR (EGLAPIENTRYP PFNEGLCREATESTREAMFROMFILEDESCRIPTORKHRPROC) (EGLDisplay dpy, EGLNativeFileDescriptorKHR file_descriptor);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLNativeFileDescriptorKHR EGLAPIENTRY egl_Get_ప్రవాహం_File_Descriptor_KHR (EGLDisplay dpy, EGLStreamKHR ప్రవాహం);
EGLAPI EGLStreamKHR EGLAPIENTRY egl_Create_ప్రవాహం_From_File_Descriptor_KHR (EGLDisplay dpy, EGLNativeFileDescriptorKHR file_descriptor);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_KHR_stream */
#అయితే_ముగింపు /* EGL_KHR_stream_cross_process_fd */

#నిర్వచితం_కాకపోతే EGL_KHR_ప్రవాహం_fifo
#నిర్వచించు EGL_KHR_ప్రవాహం_fifo 1
#నిర్వచితమైతే EGL_KHR_ప్రవాహం
#నిర్వచించు EGL_ప్రవాహం_FIFO_నిడివి_KHR        0x31FC
#నిర్వచించు EGL_ప్రవాహం_సమయం_NOW_KHR           0x31FD
#నిర్వచించు EGL_ప్రవాహం_సమయం_వినియోగదారు_KHR      0x31FE
#నిర్వచించు EGL_ప్రవాహం_సమయం_ఉత్పాదకుడు_KHR      0x31FF
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMTIMEKHRPROC) (EGLDisplay dpy, EGLStreamKHR ప్రవాహం, EGLenum attribute, EGLTimeKHR *విలువ);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_ప్రవాహం_సమయం_KHR (EGLDisplay dpy, EGLStreamKHR ప్రవాహం, EGLenum attribute, EGLTimeKHR *విలువ);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_KHR_stream */
#అయితే_ముగింపు /* EGL_KHR_stream_fifo */

#నిర్వచితం_కాకపోతే EGL_KHR_ప్రవాహం_ఉత్పాదకుడు_aldatalocator
#నిర్వచించు EGL_KHR_ప్రవాహం_ఉత్పాదకుడు_aldatalocator 1
#నిర్వచితమైతే EGL_KHR_ప్రవాహం
#అయితే_ముగింపు /* EGL_KHR_stream */
#అయితే_ముగింపు /* EGL_KHR_stream_producer_aldatalocator */

#నిర్వచితం_కాకపోతే EGL_KHR_ప్రవాహం_ఉత్పాదకుడు_eglsurface
#నిర్వచించు EGL_KHR_ప్రవాహం_ఉత్పాదకుడు_eglsurface 1
#నిర్వచితమైతే EGL_KHR_ప్రవాహం
#నిర్వచించు EGL_ప్రవాహం_బిట్టు_KHR                0x0800
రకనిర్వచనం EGLSurface (EGLAPIENTRYP PFNEGLCREATESTREAMPRODUCERSURFACEKHRPROC) (EGLDisplay dpy, EGLConfig config, EGLStreamKHR ప్రవాహం, స్థిరరాశి EGLint *attrib_list);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSurface EGLAPIENTRY egl_Create_ప్రవాహం_ఉత్పాదకుడు_Surface_KHR (EGLDisplay dpy, EGLConfig config, EGLStreamKHR ప్రవాహం, స్థిరరాశి EGLint *attrib_list);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_KHR_stream */
#అయితే_ముగింపు /* EGL_KHR_stream_producer_eglsurface */

#నిర్వచితం_కాకపోతే EGL_KHR_surfaceless_context
#నిర్వచించు EGL_KHR_surfaceless_context 1
#అయితే_ముగింపు /* EGL_KHR_surfaceless_context */

#నిర్వచితం_కాకపోతే EGL_KHR_మార్పిడి_buffers_with_damage
#నిర్వచించు EGL_KHR_మార్పిడి_buffers_with_damage 1
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSWITHDAMAGEKHRPROC) (EGLDisplay dpy, EGLSurface surface, స్థిరరాశి EGLint *rects, EGLint n_rects);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_మార్పిడి_Buffers_With_Damage_KHR (EGLDisplay dpy, EGLSurface surface, స్థిరరాశి EGLint *rects, EGLint n_rects);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_KHR_swap_buffers_with_damage */

#నిర్వచితం_కాకపోతే EGL_KHR_vg_మాతృ_image
#నిర్వచించు EGL_KHR_vg_మాతృ_image 1
#నిర్వచించు EGL_VG_మాతృ_IMAGE_KHR           0x30BA
#అయితే_ముగింపు /* EGL_KHR_vg_parent_image */

#నిర్వచితం_కాకపోతే EGL_KHR_wait_sync
#నిర్వచించు EGL_KHR_wait_sync 1
రకనిర్వచనం EGLint (EGLAPIENTRYP PFNEGLWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLint EGLAPIENTRY eglWaitSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_KHR_wait_sync */

#నిర్వచితం_కాకపోతే EGL_ANDROID_GLES_layers
#నిర్వచించు EGL_ANDROID_GLES_layers 1
#అయితే_ముగింపు /* EGL_ANDROID_GLES_layers */

#నిర్వచితం_కాకపోతే EGL_ANDROID_blob_cache
#నిర్వచించు EGL_ANDROID_blob_cache 1
రకనిర్వచనం khronos_ssize_t EGLsizeiANDROID;
రకనిర్వచనం శూన్య (*EGLSetBlobFuncANDROID) (స్థిరరాశి శూన్య *కీలకం, EGLsizeiANDROID కీలకం_కొలత_2, స్థిరరాశి శూన్య *విలువ, EGLsizeiANDROID విలువ_కొలత_2);
రకనిర్వచనం EGLsizeiANDROID (*EGLGetBlobFuncANDROID) (స్థిరరాశి శూన్య *కీలకం, EGLsizeiANDROID కీలకం_కొలత_2, శూన్య *విలువ, EGLsizeiANDROID విలువ_కొలత_2);
రకనిర్వచనం శూన్య (EGLAPIENTRYP PFNEGLSETBLOBCACHEFUNCSANDROIDPROC) (EGLDisplay dpy, EGLSetBlobFuncANDROID సమితి, EGLGetBlobFuncANDROID get);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI శూన్య EGLAPIENTRY egl_సమితి_Blob_Cache_Funcs_ANDROID (EGLDisplay dpy, EGLSetBlobFuncANDROID సమితి, EGLGetBlobFuncANDROID get);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_ANDROID_blob_cache */

#నిర్వచితం_కాకపోతే EGL_ANDROID_create_native_client_బఫరు
#నిర్వచించు EGL_ANDROID_create_native_client_బఫరు 1
#నిర్వచించు EGL_NATIVE_బఫరు_USAGE_ANDROID   0x3143
#నిర్వచించు EGL_NATIVE_బఫరు_USAGE_PROTECTED_బిట్టు_ANDROID 0x00000001
#నిర్వచించు EGL_NATIVE_బఫరు_USAGE_RENDERBUFFER_బిట్టు_ANDROID 0x00000002
#నిర్వచించు EGL_NATIVE_బఫరు_USAGE_TEXTURE_బిట్టు_ANDROID 0x00000004
రకనిర్వచనం EGLClient_బఫరు (EGLAPIENTRYP PFNEGLCREATENATIVECLIENTBUFFERANDROIDPROC) (స్థిరరాశి EGLint *attrib_list);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLClient_బఫరు EGLAPIENTRY egl_Create_Native_Client_బఫరు_ANDROID (స్థిరరాశి EGLint *attrib_list);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_ANDROID_create_native_client_buffer */

#నిర్వచితం_కాకపోతే EGL_ANDROID_framebuffer_లక్ష్యం
#నిర్వచించు EGL_ANDROID_framebuffer_లక్ష్యం 1
#నిర్వచించు EGL_FRAMEBUFFER_లక్ష్యం_ANDROID    0x3147
#అయితే_ముగింపు /* EGL_ANDROID_framebuffer_target */

#నిర్వచితం_కాకపోతే EGL_ANDROID_front_బఫరు_auto_refresh
#నిర్వచించు EGL_ANDROID_front_బఫరు_auto_refresh 1
#నిర్వచించు EGL_FRONT_బఫరు_AUTO_REFRESH_ANDROID 0x314C
#అయితే_ముగింపు /* EGL_ANDROID_front_buffer_auto_refresh */

#నిర్వచితం_కాకపోతే EGL_ANDROID_get_చట్రం_timestamps
#నిర్వచించు EGL_ANDROID_get_చట్రం_timestamps 1
రకనిర్వచనం khronos_stime_nanoseconds_t EGLnsecsANDROID;
#నిర్వచించు EGL_TIMESTAMP_PENDING_ANDROID     EGL_CAST(EGLnsecsANDROID,-2)
#నిర్వచించు EGL_TIMESTAMP_INVALID_ANDROID     EGL_CAST(EGLnsecsANDROID,-1)
#నిర్వచించు EGL_TIMESTAMPS_ANDROID            0x3430
#నిర్వచించు EGL_సంయుక్త_DEADLINE_ANDROID    0x3431
#నిర్వచించు EGL_సంయుక్త_INTERVAL_ANDROID    0x3432
#నిర్వచించు EGL_సంయుక్త_గమ్యం_PRESENT_LATENCY_ANDROID 0x3433
#నిర్వచించు EGL_REQUESTED_PRESENT_సమయం_ANDROID 0x3434
#నిర్వచించు EGL_RENDERING_COMPLETE_సమయం_ANDROID 0x3435
#నిర్వచించు EGL_COMPOSITION_LATCH_సమయం_ANDROID 0x3436
#నిర్వచించు EGL_మొదటి_COMPOSITION_ప్రారంభం_సమయం_ANDROID 0x3437
#నిర్వచించు EGL_చివరి_COMPOSITION_ప్రారంభం_సమయం_ANDROID 0x3438
#నిర్వచించు EGL_మొదటి_COMPOSITION_GPU_ముగిసిన_సమయం_ANDROID 0x3439
#నిర్వచించు EGL_DISPLAY_PRESENT_సమయం_ANDROID  0x343A
#నిర్వచించు EGL_వరుస_నుండి_తీయి_READY_సమయం_ANDROID    0x343B
#నిర్వచించు EGL_READS_పూర్తి_సమయం_ANDROID       0x343C
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLGETCOMPOSITORTIMINGSUPPORTEDANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLint name);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLGETCOMPOSITORTIMINGANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLint అంకె_Timestamps,  స్థిరరాశి EGLint *పేర్లు, EGLnsecsANDROID *విలువలు);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLGETNEXTFRAMEIDANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR *చట్రం_Id);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLGETFRAMETIMESTAMPSUPPORTEDANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLint timestamp);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLGETFRAMETIMESTAMPSANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR చట్రం_Id, EGLint అంకె_Timestamps,  స్థిరరాశి EGLint *timestamps, EGLnsecsANDROID *విలువలు);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglGetCompositorTimingSupportedANDROID (EGLDisplay dpy, EGLSurface surface, EGLint name);
EGLAPI EGLBoolean EGLAPIENTRY eglGetCompositorTimingANDROID (EGLDisplay dpy, EGLSurface surface, EGLint అంకె_Timestamps,  స్థిరరాశి EGLint *పేర్లు, EGLnsecsANDROID *విలువలు);
EGLAPI EGLBoolean EGLAPIENTRY egl_Get_తదుపరి_చట్రం_Id_ANDROID (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR *చట్రం_Id);
EGLAPI EGLBoolean EGLAPIENTRY egl_Get_చట్రం_Timestamp_Supported_ANDROID (EGLDisplay dpy, EGLSurface surface, EGLint timestamp);
EGLAPI EGLBoolean EGLAPIENTRY egl_Get_చట్రం_Timestamps_ANDROID (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR చట్రం_Id, EGLint అంకె_Timestamps,  స్థిరరాశి EGLint *timestamps, EGLnsecsANDROID *విలువలు);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_ANDROID_get_frame_timestamps */

#నిర్వచితం_కాకపోతే EGL_ANDROID_get_native_client_బఫరు
#నిర్వచించు EGL_ANDROID_get_native_client_బఫరు 1
నిర్మాణం AHardware_బఫరు;
రకనిర్వచనం EGLClient_బఫరు (EGLAPIENTRYP PFNEGLGETNATIVECLIENTBUFFERANDROIDPROC) (స్థిరరాశి నిర్మాణం AHardware_బఫరు *బఫరు_2);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLClient_బఫరు EGLAPIENTRY egl_Get_Native_Client_బఫరు_ANDROID (స్థిరరాశి నిర్మాణం AHardware_బఫరు *బఫరు_2);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_ANDROID_get_native_client_buffer */

#నిర్వచితం_కాకపోతే EGL_ANDROID_image_native_బఫరు
#నిర్వచించు EGL_ANDROID_image_native_బఫరు 1
#నిర్వచించు EGL_NATIVE_బఫరు_ANDROID         0x3140
#అయితే_ముగింపు /* EGL_ANDROID_image_native_buffer */

#నిర్వచితం_కాకపోతే EGL_ANDROID_native_fence_sync
#నిర్వచించు EGL_ANDROID_native_fence_sync 1
#నిర్వచించు EGL_SYNC_NATIVE_FENCE_ANDROID     0x3144
#నిర్వచించు EGL_SYNC_NATIVE_FENCE_FD_ANDROID  0x3145
#నిర్వచించు EGL_SYNC_NATIVE_FENCE_SIGNALED_ANDROID 0x3146
#నిర్వచించు EGL_NO_NATIVE_FENCE_FD_ANDROID    -1
రకనిర్వచనం EGLint (EGLAPIENTRYP PFNEGLDUPNATIVEFENCEFDANDROIDPROC) (EGLDisplay dpy, EGLSyncKHR sync);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLint EGLAPIENTRY eglDupNativeFenceFDANDROID (EGLDisplay dpy, EGLSyncKHR sync);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_ANDROID_native_fence_sync */

#నిర్వచితం_కాకపోతే EGL_ANDROID_presentation_సమయం
#నిర్వచించు EGL_ANDROID_presentation_సమయం 1
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLPRESENTATIONTIMEANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLnsecsANDROID సమయం);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Presentation_సమయం_ANDROID (EGLDisplay dpy, EGLSurface surface, EGLnsecsANDROID సమయం);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_ANDROID_presentation_time */

#నిర్వచితం_కాకపోతే EGL_ANDROID_recordable
#నిర్వచించు EGL_ANDROID_recordable 1
#నిర్వచించు EGL_RECORDABLE_ANDROID            0x3142
#అయితే_ముగింపు /* EGL_ANDROID_recordable */

#నిర్వచితం_కాకపోతే EGL_ANDROID_telemetry_hint
#నిర్వచించు EGL_ANDROID_telemetry_hint 1
#నిర్వచించు EGL_TELEMETRY_HINT_ANDROID        0x3570
#అయితే_ముగింపు /* EGL_ANDROID_telemetry_hint */

#నిర్వచితం_కాకపోతే EGL_ANGLE_d3d_share_handle_client_బఫరు
#నిర్వచించు EGL_ANGLE_d3d_share_handle_client_బఫరు 1
#నిర్వచించు EGL_D3D_TEXTURE_2D_SHARE_HANDLE_ANGLE 0x3200
#అయితే_ముగింపు /* EGL_ANGLE_d3d_share_handle_client_buffer */

#నిర్వచితం_కాకపోతే EGL_ANGLE_device_d3d
#నిర్వచించు EGL_ANGLE_device_d3d 1
#నిర్వచించు EGL_D3D9_DEVICE_ANGLE             0x33A0
#నిర్వచించు EGL_D3D11_DEVICE_ANGLE            0x33A1
#అయితే_ముగింపు /* EGL_ANGLE_device_d3d */

#నిర్వచితం_కాకపోతే EGL_ANGLE_query_surface_సూచిక
#నిర్వచించు EGL_ANGLE_query_surface_సూచిక 1
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSURFACEPOINTERANGLEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint attribute, శూన్య **విలువ);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Surface_సూచిక_ANGLE (EGLDisplay dpy, EGLSurface surface, EGLint attribute, శూన్య **విలువ);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_ANGLE_query_surface_pointer */

#నిర్వచితం_కాకపోతే EGL_ANGLE_surface_d3d_texture_2d_share_handle
#నిర్వచించు EGL_ANGLE_surface_d3d_texture_2d_share_handle 1
#అయితే_ముగింపు /* EGL_ANGLE_surface_d3d_texture_2d_share_handle */

#నిర్వచితం_కాకపోతే EGL_ANGLE_sync_control_రేటు
#నిర్వచించు EGL_ANGLE_sync_control_రేటు 1
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLGETMSCRATEANGLEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint *numerator, EGLint *denominator);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Get_Msc_రేటు_ANGLE (EGLDisplay dpy, EGLSurface surface, EGLint *numerator, EGLint *denominator);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_ANGLE_sync_control_rate */

#నిర్వచితం_కాకపోతే EGL_ANGLE_కిటికీ_fixed_కొలత
#నిర్వచించు EGL_ANGLE_కిటికీ_fixed_కొలత 1
#నిర్వచించు EGL_FIXED_కొలత_ANGLE              0x3201
#అయితే_ముగింపు /* EGL_ANGLE_window_fixed_size */

#నిర్వచితం_కాకపోతే EGL_ARM_image_format
#నిర్వచించు EGL_ARM_image_format 1
#నిర్వచించు EGL_COLOR_COMPONENT_TYPE_UNSIGNED_INTEGER_ARM 0x3287
#నిర్వచించు EGL_COLOR_COMPONENT_TYPE_INTEGER_ARM 0x3288
#అయితే_ముగింపు /* EGL_ARM_image_format */

#నిర్వచితం_కాకపోతే EGL_ARM_implicit_external_sync
#నిర్వచించు EGL_ARM_implicit_external_sync 1
#నిర్వచించు EGL_SYNC_పూర్వ_COMMANDS_IMPLICIT_EXTERNAL_ARM 0x328A
#అయితే_ముగింపు /* EGL_ARM_implicit_external_sync */

#నిర్వచితం_కాకపోతే EGL_ARM_pixmap_multisample_discard
#నిర్వచించు EGL_ARM_pixmap_multisample_discard 1
#నిర్వచించు EGL_DISCARD_SAMPLES_ARM           0x3286
#అయితే_ముగింపు /* EGL_ARM_pixmap_multisample_discard */

#నిర్వచితం_కాకపోతే EGL_EXT_bind_గమ్యం_front
#నిర్వచించు EGL_EXT_bind_గమ్యం_front 1
#నిర్వచించు EGL_FRONT_బఫరు_EXT              0x3464
#అయితే_ముగింపు /* EGL_EXT_bind_to_front */

#నిర్వచితం_కాకపోతే EGL_EXT_బఫరు_age
#నిర్వచించు EGL_EXT_బఫరు_age 1
#నిర్వచించు EGL_బఫరు_AGE_EXT                0x313D
#అయితే_ముగింపు /* EGL_EXT_buffer_age */

#నిర్వచితం_కాకపోతే EGL_EXT_client_extensions
#నిర్వచించు EGL_EXT_client_extensions 1
#అయితే_ముగింపు /* EGL_EXT_client_extensions */

#నిర్వచితం_కాకపోతే EGL_EXT_client_sync
#నిర్వచించు EGL_EXT_client_sync 1
#నిర్వచించు EGL_SYNC_CLIENT_EXT               0x3364
#నిర్వచించు EGL_SYNC_CLIENT_SIGNAL_EXT        0x3365
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLCLIENTSIGNALSYNCEXTPROC) (EGLDisplay dpy, EGLSync sync, స్థిరరాశి EGLAttrib *attrib_list);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglClientSignalSyncEXT (EGLDisplay dpy, EGLSync sync, స్థిరరాశి EGLAttrib *attrib_list);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_EXT_client_sync */

#నిర్వచితం_కాకపోతే EGL_EXT_compositor
#నిర్వచించు EGL_EXT_compositor 1
#నిర్వచించు EGL_PRIMARY_COMPOSITOR_CONTEXT_EXT 0x3460
#నిర్వచించు EGL_EXTERNAL_REF_ID_EXT           0x3461
#నిర్వచించు EGL_COMPOSITOR_DROP_NEWEST_చట్రం_EXT 0x3462
#నిర్వచించు EGL_COMPOSITOR_KEEP_NEWEST_చట్రం_EXT 0x3463
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETCONTEXTLISTEXTPROC) (స్థిరరాశి EGLint *external_ref_ids, EGLint అంకె_entries);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETCONTEXTATTRIBUTESEXTPROC) (EGLint external_ref_id, స్థిరరాశి EGLint *context_లక్షణాలు, EGLint అంకె_entries);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETWINDOWLISTEXTPROC) (EGLint external_ref_id, స్థిరరాశి EGLint *external_win_ids, EGLint అంకె_entries);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETWINDOWATTRIBUTESEXTPROC) (EGLint external_win_id, స్థిరరాశి EGLint *కిటికీ_లక్షణాలు, EGLint అంకె_entries);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORBINDTEXWINDOWEXTPROC) (EGLint external_win_id);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETSIZEEXTPROC) (EGLint external_win_id, EGLint వెడల్పు, EGLint ఎత్తు);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSWAPPOLICYEXTPROC) (EGLint external_win_id, EGLint policy);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_సమితి_Context_List_EXT (స్థిరరాశి EGLint *external_ref_ids, EGLint అంకె_entries);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_సమితి_Context_లక్షణాలు_EXT (EGLint external_ref_id, స్థిరరాశి EGLint *context_లక్షణాలు, EGLint అంకె_entries);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_సమితి_కిటికీ_List_EXT (EGLint external_ref_id, స్థిరరాశి EGLint *external_win_ids, EGLint అంకె_entries);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_సమితి_కిటికీ_లక్షణాలు_EXT (EGLint external_win_id, స్థిరరాశి EGLint *కిటికీ_లక్షణాలు, EGLint అంకె_entries);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_Bind_Tex_కిటికీ_EXT (EGLint external_win_id);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_సమితి_కొలత_EXT (EGLint external_win_id, EGLint వెడల్పు, EGLint ఎత్తు);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_మార్పిడి_Policy_EXT (EGLint external_win_id, EGLint policy);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_EXT_compositor */

#నిర్వచితం_కాకపోతే EGL_EXT_config_select_సమూహం
#నిర్వచించు EGL_EXT_config_select_సమూహం 1
#నిర్వచించు EGL_CONFIG_SELECT_సమూహం_EXT       0x34C0
#అయితే_ముగింపు /* EGL_EXT_config_select_group */

#నిర్వచితం_కాకపోతే EGL_EXT_create_context_robustness
#నిర్వచించు EGL_EXT_create_context_robustness 1
#నిర్వచించు EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT 0x30BF
#నిర్వచించు EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_EXT 0x3138
#నిర్వచించు EGL_NO_RESET_NOTIFICATION_EXT     0x31BE
#నిర్వచించు EGL_LOSE_CONTEXT_ON_RESET_EXT     0x31BF
#అయితే_ముగింపు /* EGL_EXT_create_context_robustness */

#నిర్వచితం_కాకపోతే EGL_EXT_device_పునాది
#నిర్వచించు EGL_EXT_device_పునాది 1
రకనిర్వచనం శూన్య *EGLDeviceEXT;
#నిర్వచించు EGL_NO_DEVICE_EXT                 EGL_CAST(EGLDeviceEXT,0)
#నిర్వచించు EGL_BAD_DEVICE_EXT                0x322B
#నిర్వచించు EGL_DEVICE_EXT                    0x322C
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICEATTRIBEXTPROC) (EGLDeviceEXT device, EGLint attribute, EGLAttrib *విలువ);
రకనిర్వచనం స్థిరరాశి అక్షరం *(EGLAPIENTRYP PFNEGLQUERYDEVICESTRINGEXTPROC) (EGLDeviceEXT device, EGLint name);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICESEXTPROC) (EGLint max_devices, EGLDeviceEXT *devices, EGLint *అంకె_devices);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDISPLAYATTRIBEXTPROC) (EGLDisplay dpy, EGLint attribute, EGLAttrib *విలువ);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDeviceAttribEXT (EGLDeviceEXT device, EGLint attribute, EGLAttrib *విలువ);
EGLAPI స్థిరరాశి అక్షరం *EGLAPIENTRY eglQueryDeviceStringEXT (EGLDeviceEXT device, EGLint name);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDevicesEXT (EGLint max_devices, EGLDeviceEXT *devices, EGLint *అంకె_devices);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDisplayAttribEXT (EGLDisplay dpy, EGLint attribute, EGLAttrib *విలువ);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_EXT_device_base */

#నిర్వచితం_కాకపోతే EGL_EXT_device_drm
#నిర్వచించు EGL_EXT_device_drm 1
#నిర్వచించు EGL_DRM_DEVICE_FILE_EXT           0x3233
#నిర్వచించు EGL_DRM_MASTER_FD_EXT             0x333C
#అయితే_ముగింపు /* EGL_EXT_device_drm */

#నిర్వచితం_కాకపోతే EGL_EXT_device_drm_render_కణుపు
#నిర్వచించు EGL_EXT_device_drm_render_కణుపు 1
#నిర్వచించు EGL_DRM_RENDER_కణుపు_FILE_EXT      0x3377
#అయితే_ముగింపు /* EGL_EXT_device_drm_render_node */

#నిర్వచితం_కాకపోతే EGL_EXT_device_enumeration
#నిర్వచించు EGL_EXT_device_enumeration 1
#అయితే_ముగింపు /* EGL_EXT_device_enumeration */

#నిర్వచితం_కాకపోతే EGL_EXT_device_openwf
#నిర్వచించు EGL_EXT_device_openwf 1
#నిర్వచించు EGL_OPENWF_DEVICE_ID_EXT          0x3237
#నిర్వచించు EGL_OPENWF_DEVICE_EXT             0x333D
#అయితే_ముగింపు /* EGL_EXT_device_openwf */

#నిర్వచితం_కాకపోతే EGL_EXT_device_persistent_id
#నిర్వచించు EGL_EXT_device_persistent_id 1
#నిర్వచించు EGL_DEVICE_UUID_EXT               0x335C
#నిర్వచించు EGL_DRIVER_UUID_EXT               0x335D
#నిర్వచించు EGL_DRIVER_NAME_EXT               0x335E
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICEBINARYEXTPROC) (EGLDeviceEXT device, EGLint name, EGLint max_కొలత, శూన్య *విలువ, EGLint *కొలత);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Device_ద్విమాన_EXT (EGLDeviceEXT device, EGLint name, EGLint max_కొలత, శూన్య *విలువ, EGLint *కొలత);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_EXT_device_persistent_id */

#నిర్వచితం_కాకపోతే EGL_EXT_device_query
#నిర్వచించు EGL_EXT_device_query 1
#అయితే_ముగింపు /* EGL_EXT_device_query */

#నిర్వచితం_కాకపోతే EGL_EXT_device_query_name
#నిర్వచించు EGL_EXT_device_query_name 1
#నిర్వచించు EGL_RENDERER_EXT                  0x335F
#అయితే_ముగింపు /* EGL_EXT_device_query_name */

#నిర్వచితం_కాకపోతే EGL_EXT_device_type
#నిర్వచించు EGL_EXT_device_type 1
#నిర్వచించు EGL_DEVICE_TYPE_EXT               0x3590
#నిర్వచించు EGL_DEVICE_TYPE_OTHER_EXT         0x3591
#నిర్వచించు EGL_DEVICE_TYPE_INTEGRATED_GPU_EXT 0x3592
#నిర్వచించు EGL_DEVICE_TYPE_DISCRETE_GPU_EXT  0x3593
#నిర్వచించు EGL_DEVICE_TYPE_CPU_EXT           0x3594
#అయితే_ముగింపు /* EGL_EXT_device_type */

#నిర్వచితం_కాకపోతే EGL_EXT_display_alloc
#నిర్వచించు EGL_EXT_display_alloc 1
#నిర్వచించు EGL_ALLOC_NEW_DISPLAY_EXT         0x3379
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYDISPLAYEXTPROC) (EGLDisplay dpy);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyDisplayEXT (EGLDisplay dpy);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_EXT_display_alloc */

#నిర్వచితం_కాకపోతే EGL_EXT_explicit_device
#నిర్వచించు EGL_EXT_explicit_device 1
#అయితే_ముగింపు /* EGL_EXT_explicit_device */

#నిర్వచితం_కాకపోతే EGL_EXT_gl_colorspace_bt2020_hlg
#నిర్వచించు EGL_EXT_gl_colorspace_bt2020_hlg 1
#నిర్వచించు EGL_GL_COLORSPACE_BT2020_HLG_EXT  0x3540
#అయితే_ముగింపు /* EGL_EXT_gl_colorspace_bt2020_hlg */

#నిర్వచితం_కాకపోతే EGL_EXT_gl_colorspace_bt2020_రేఖీయ
#నిర్వచించు EGL_EXT_gl_colorspace_bt2020_రేఖీయ 1
#నిర్వచించు EGL_GL_COLORSPACE_BT2020_రేఖీయ_EXT 0x333F
#అయితే_ముగింపు /* EGL_EXT_gl_colorspace_bt2020_linear */

#నిర్వచితం_కాకపోతే EGL_EXT_gl_colorspace_bt2020_pq
#నిర్వచించు EGL_EXT_gl_colorspace_bt2020_pq 1
#నిర్వచించు EGL_GL_COLORSPACE_BT2020_PQ_EXT   0x3340
#అయితే_ముగింపు /* EGL_EXT_gl_colorspace_bt2020_pq */

#నిర్వచితం_కాకపోతే EGL_EXT_gl_colorspace_display_p3
#నిర్వచించు EGL_EXT_gl_colorspace_display_p3 1
#నిర్వచించు EGL_GL_COLORSPACE_DISPLAY_P3_EXT  0x3363
#అయితే_ముగింపు /* EGL_EXT_gl_colorspace_display_p3 */

#నిర్వచితం_కాకపోతే EGL_EXT_gl_colorspace_display_p3_రేఖీయ
#నిర్వచించు EGL_EXT_gl_colorspace_display_p3_రేఖీయ 1
#నిర్వచించు EGL_GL_COLORSPACE_DISPLAY_P3_రేఖీయ_EXT 0x3362
#అయితే_ముగింపు /* EGL_EXT_gl_colorspace_display_p3_linear */

#నిర్వచితం_కాకపోతే EGL_EXT_gl_colorspace_display_p3_passthrough
#నిర్వచించు EGL_EXT_gl_colorspace_display_p3_passthrough 1
#నిర్వచించు EGL_GL_COLORSPACE_DISPLAY_P3_PASSTHROUGH_EXT 0x3490
#అయితే_ముగింపు /* EGL_EXT_gl_colorspace_display_p3_passthrough */

#నిర్వచితం_కాకపోతే EGL_EXT_gl_colorspace_scrgb
#నిర్వచించు EGL_EXT_gl_colorspace_scrgb 1
#నిర్వచించు EGL_GL_COLORSPACE_SCRGB_EXT       0x3351
#అయితే_ముగింపు /* EGL_EXT_gl_colorspace_scrgb */

#నిర్వచితం_కాకపోతే EGL_EXT_gl_colorspace_scrgb_రేఖీయ
#నిర్వచించు EGL_EXT_gl_colorspace_scrgb_రేఖీయ 1
#నిర్వచించు EGL_GL_COLORSPACE_SCRGB_రేఖీయ_EXT 0x3350
#అయితే_ముగింపు /* EGL_EXT_gl_colorspace_scrgb_linear */

#నిర్వచితం_కాకపోతే EGL_EXT_image_dma_buf_import
#నిర్వచించు EGL_EXT_image_dma_buf_import 1
#నిర్వచించు EGL_LINUX_DMA_BUF_EXT             0x3270
#నిర్వచించు EGL_LINUX_DRM_FOURCC_EXT          0x3271
#నిర్వచించు EGL_DMA_BUF_PLANE0_FD_EXT         0x3272
#నిర్వచించు EGL_DMA_BUF_PLANE0_స్థానభ్రంశం_EXT     0x3273
#నిర్వచించు EGL_DMA_BUF_PLANE0_PITCH_EXT      0x3274
#నిర్వచించు EGL_DMA_BUF_PLANE1_FD_EXT         0x3275
#నిర్వచించు EGL_DMA_BUF_PLANE1_స్థానభ్రంశం_EXT     0x3276
#నిర్వచించు EGL_DMA_BUF_PLANE1_PITCH_EXT      0x3277
#నిర్వచించు EGL_DMA_BUF_PLANE2_FD_EXT         0x3278
#నిర్వచించు EGL_DMA_BUF_PLANE2_స్థానభ్రంశం_EXT     0x3279
#నిర్వచించు EGL_DMA_BUF_PLANE2_PITCH_EXT      0x327A
#నిర్వచించు EGL_YUV_COLOR_SPACE_HINT_EXT      0x327B
#నిర్వచించు EGL_SAMPLE_RANGE_HINT_EXT         0x327C
#నిర్వచించు EGL_YUV_CHROMA_HORIZONTAL_SITING_HINT_EXT 0x327D
#నిర్వచించు EGL_YUV_CHROMA_VERTICAL_SITING_HINT_EXT 0x327E
#నిర్వచించు EGL_ITU_REC601_EXT                0x327F
#నిర్వచించు EGL_ITU_REC709_EXT                0x3280
#నిర్వచించు EGL_ITU_REC2020_EXT               0x3281
#నిర్వచించు EGL_YUV_నిండిన_RANGE_EXT            0x3282
#నిర్వచించు EGL_YUV_NARROW_RANGE_EXT          0x3283
#నిర్వచించు EGL_YUV_CHROMA_SITING_0_EXT       0x3284
#నిర్వచించు EGL_YUV_CHROMA_SITING_0_5_EXT     0x3285
#అయితే_ముగింపు /* EGL_EXT_image_dma_buf_import */

#నిర్వచితం_కాకపోతే EGL_EXT_image_dma_buf_import_modifiers
#నిర్వచించు EGL_EXT_image_dma_buf_import_modifiers 1
#నిర్వచించు EGL_DMA_BUF_PLANE3_FD_EXT         0x3440
#నిర్వచించు EGL_DMA_BUF_PLANE3_స్థానభ్రంశం_EXT     0x3441
#నిర్వచించు EGL_DMA_BUF_PLANE3_PITCH_EXT      0x3442
#నిర్వచించు EGL_DMA_BUF_PLANE0_MODIFIER_LO_EXT 0x3443
#నిర్వచించు EGL_DMA_BUF_PLANE0_MODIFIER_HI_EXT 0x3444
#నిర్వచించు EGL_DMA_BUF_PLANE1_MODIFIER_LO_EXT 0x3445
#నిర్వచించు EGL_DMA_BUF_PLANE1_MODIFIER_HI_EXT 0x3446
#నిర్వచించు EGL_DMA_BUF_PLANE2_MODIFIER_LO_EXT 0x3447
#నిర్వచించు EGL_DMA_BUF_PLANE2_MODIFIER_HI_EXT 0x3448
#నిర్వచించు EGL_DMA_BUF_PLANE3_MODIFIER_LO_EXT 0x3449
#నిర్వచించు EGL_DMA_BUF_PLANE3_MODIFIER_HI_EXT 0x344A
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDMABUFFORMATSEXTPROC) (EGLDisplay dpy, EGLint max_formats, EGLint *formats, EGLint *అంకె_formats);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDMABUFMODIFIERSEXTPROC) (EGLDisplay dpy, EGLint format, EGLint max_modifiers, EGLuint64KHR *modifiers, EGLBoolean *external_only, EGLint *అంకె_modifiers);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDmaBufFormatsEXT (EGLDisplay dpy, EGLint max_formats, EGLint *formats, EGLint *అంకె_formats);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDmaBufModifiersEXT (EGLDisplay dpy, EGLint format, EGLint max_modifiers, EGLuint64KHR *modifiers, EGLBoolean *external_only, EGLint *అంకె_modifiers);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_EXT_image_dma_buf_import_modifiers */

#నిర్వచితం_కాకపోతే EGL_EXT_image_gl_colorspace
#నిర్వచించు EGL_EXT_image_gl_colorspace 1
#నిర్వచించు EGL_GL_COLORSPACE_DEFAULT_EXT     0x314D
#అయితే_ముగింపు /* EGL_EXT_image_gl_colorspace */

#నిర్వచితం_కాకపోతే EGL_EXT_image_implicit_sync_control
#నిర్వచించు EGL_EXT_image_implicit_sync_control 1
#నిర్వచించు EGL_IMPORT_SYNC_TYPE_EXT          0x3470
#నిర్వచించు EGL_IMPORT_IMPLICIT_SYNC_EXT      0x3471
#నిర్వచించు EGL_IMPORT_EXPLICIT_SYNC_EXT      0x3472
#అయితే_ముగింపు /* EGL_EXT_image_implicit_sync_control */

#నిర్వచితం_కాకపోతే EGL_EXT_multiview_కిటికీ
#నిర్వచించు EGL_EXT_multiview_కిటికీ 1
#నిర్వచించు EGL_MULTIVIEW_VIEW_లెక్క_EXT      0x3134
#అయితే_ముగింపు /* EGL_EXT_multiview_window */

#నిర్వచితం_కాకపోతే EGL_EXT_output_పునాది
#నిర్వచించు EGL_EXT_output_పునాది 1
రకనిర్వచనం శూన్య *EGLOutputLayerEXT;
రకనిర్వచనం శూన్య *EGLOutput_పోర్టు_EXT;
#నిర్వచించు EGL_NO_OUTPUT_LAYER_EXT           EGL_CAST(EGLOutputLayerEXT,0)
#నిర్వచించు EGL_NO_OUTPUT_పోర్టు_EXT            EGL_CAST(EGLOutput_పోర్టు_EXT,0)
#నిర్వచించు EGL_BAD_OUTPUT_LAYER_EXT          0x322D
#నిర్వచించు EGL_BAD_OUTPUT_పోర్టు_EXT           0x322E
#నిర్వచించు EGL_మార్పిడి_INTERVAL_EXT             0x322F
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLGETOUTPUTLAYERSEXTPROC) (EGLDisplay dpy, స్థిరరాశి EGLAttrib *attrib_list, EGLOutputLayerEXT *layers, EGLint max_layers, EGLint *అంకె_layers);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLGETOUTPUTPORTSEXTPROC) (EGLDisplay dpy, స్థిరరాశి EGLAttrib *attrib_list, EGLOutput_పోర్టు_EXT *ports, EGLint max_ports, EGLint *అంకె_ports);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLOUTPUTLAYERATTRIBEXTPROC) (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib విలువ);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLQUERYOUTPUTLAYERATTRIBEXTPROC) (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib *విలువ);
రకనిర్వచనం స్థిరరాశి అక్షరం *(EGLAPIENTRYP PFNEGLQUERYOUTPUTLAYERSTRINGEXTPROC) (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint name);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLOUTPUTPORTATTRIBEXTPROC) (EGLDisplay dpy, EGLOutput_పోర్టు_EXT పోర్టు, EGLint attribute, EGLAttrib విలువ);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLQUERYOUTPUTPORTATTRIBEXTPROC) (EGLDisplay dpy, EGLOutput_పోర్టు_EXT పోర్టు, EGLint attribute, EGLAttrib *విలువ);
రకనిర్వచనం స్థిరరాశి అక్షరం *(EGLAPIENTRYP PFNEGLQUERYOUTPUTPORTSTRINGEXTPROC) (EGLDisplay dpy, EGLOutput_పోర్టు_EXT పోర్టు, EGLint name);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglGetOutputLayersEXT (EGLDisplay dpy, స్థిరరాశి EGLAttrib *attrib_list, EGLOutputLayerEXT *layers, EGLint max_layers, EGLint *అంకె_layers);
EGLAPI EGLBoolean EGLAPIENTRY eglGetOutputPortsEXT (EGLDisplay dpy, స్థిరరాశి EGLAttrib *attrib_list, EGLOutput_పోర్టు_EXT *ports, EGLint max_ports, EGLint *అంకె_ports);
EGLAPI EGLBoolean EGLAPIENTRY eglOutputLayerAttribEXT (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib విలువ);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryOutputLayerAttribEXT (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib *విలువ);
EGLAPI స్థిరరాశి అక్షరం *EGLAPIENTRY eglQueryOutputLayerStringEXT (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint name);
EGLAPI EGLBoolean EGLAPIENTRY egl_Output_పోర్టు_Attrib_EXT (EGLDisplay dpy, EGLOutput_పోర్టు_EXT పోర్టు, EGLint attribute, EGLAttrib విలువ);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Output_పోర్టు_Attrib_EXT (EGLDisplay dpy, EGLOutput_పోర్టు_EXT పోర్టు, EGLint attribute, EGLAttrib *విలువ);
EGLAPI స్థిరరాశి అక్షరం *EGLAPIENTRY egl_Query_Output_పోర్టు_String_EXT (EGLDisplay dpy, EGLOutput_పోర్టు_EXT పోర్టు, EGLint name);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_EXT_output_base */

#నిర్వచితం_కాకపోతే EGL_EXT_output_drm
#నిర్వచించు EGL_EXT_output_drm 1
#నిర్వచించు EGL_DRM_CRTC_EXT                  0x3234
#నిర్వచించు EGL_DRM_PLANE_EXT                 0x3235
#నిర్వచించు EGL_DRM_CONNECTOR_EXT             0x3236
#అయితే_ముగింపు /* EGL_EXT_output_drm */

#నిర్వచితం_కాకపోతే EGL_EXT_output_openwf
#నిర్వచించు EGL_EXT_output_openwf 1
#నిర్వచించు EGL_OPENWF_PIPELINE_ID_EXT        0x3238
#నిర్వచించు EGL_OPENWF_పోర్టు_ID_EXT            0x3239
#అయితే_ముగింపు /* EGL_EXT_output_openwf */

#నిర్వచితం_కాకపోతే EGL_EXT_pixel_format_float
#నిర్వచించు EGL_EXT_pixel_format_float 1
#నిర్వచించు EGL_COLOR_COMPONENT_TYPE_EXT      0x3339
#నిర్వచించు EGL_COLOR_COMPONENT_TYPE_FIXED_EXT 0x333A
#నిర్వచించు EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT 0x333B
#అయితే_ముగింపు /* EGL_EXT_pixel_format_float */

#నిర్వచితం_కాకపోతే EGL_EXT_platform_పునాది
#నిర్వచించు EGL_EXT_platform_పునాది 1
రకనిర్వచనం EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYEXTPROC) (EGLenum platform, శూన్య *native_display, స్థిరరాశి EGLint *attrib_list);
రకనిర్వచనం EGLSurface (EGLAPIENTRYP PFNEGLCREATEPLATFORMWINDOWSURFACEEXTPROC) (EGLDisplay dpy, EGLConfig config, శూన్య *native_కిటికీ, స్థిరరాశి EGLint *attrib_list);
రకనిర్వచనం EGLSurface (EGLAPIENTRYP PFNEGLCREATEPLATFORMPIXMAPSURFACEEXTPROC) (EGLDisplay dpy, EGLConfig config, శూన్య *native_pixmap, స్థిరరాశి EGLint *attrib_list);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLDisplay EGLAPIENTRY eglGetPlatformDisplayEXT (EGLenum platform, శూన్య *native_display, స్థిరరాశి EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY egl_Create_Platform_కిటికీ_Surface_EXT (EGLDisplay dpy, EGLConfig config, శూన్య *native_కిటికీ, స్థిరరాశి EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePlatformPixmapSurfaceEXT (EGLDisplay dpy, EGLConfig config, శూన్య *native_pixmap, స్థిరరాశి EGLint *attrib_list);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_EXT_platform_base */

#నిర్వచితం_కాకపోతే EGL_EXT_platform_device
#నిర్వచించు EGL_EXT_platform_device 1
#నిర్వచించు EGL_PLATFORM_DEVICE_EXT           0x313F
#అయితే_ముగింపు /* EGL_EXT_platform_device */

#నిర్వచితం_కాకపోతే EGL_EXT_platform_wayland
#నిర్వచించు EGL_EXT_platform_wayland 1
#నిర్వచించు EGL_PLATFORM_WAYLAND_EXT          0x31D8
#అయితే_ముగింపు /* EGL_EXT_platform_wayland */

#నిర్వచితం_కాకపోతే EGL_EXT_platform_x11
#నిర్వచించు EGL_EXT_platform_x11 1
#నిర్వచించు EGL_PLATFORM_X11_EXT              0x31D5
#నిర్వచించు EGL_PLATFORM_X11_SCREEN_EXT       0x31D6
#అయితే_ముగింపు /* EGL_EXT_platform_x11 */

#నిర్వచితం_కాకపోతే EGL_EXT_platform_xcb
#నిర్వచించు EGL_EXT_platform_xcb 1
#నిర్వచించు EGL_PLATFORM_XCB_EXT              0x31DC
#నిర్వచించు EGL_PLATFORM_XCB_SCREEN_EXT       0x31DE
#అయితే_ముగింపు /* EGL_EXT_platform_xcb */

#నిర్వచితం_కాకపోతే EGL_EXT_present_opaque
#నిర్వచించు EGL_EXT_present_opaque 1
#నిర్వచించు EGL_PRESENT_OPAQUE_EXT            0x31DF
#అయితే_ముగింపు /* EGL_EXT_present_opaque */

#నిర్వచితం_కాకపోతే EGL_EXT_protected_content
#నిర్వచించు EGL_EXT_protected_content 1
#నిర్వచించు EGL_PROTECTED_CONTENT_EXT         0x32C0
#అయితే_ముగింపు /* EGL_EXT_protected_content */

#నిర్వచితం_కాకపోతే EGL_EXT_protected_surface
#నిర్వచించు EGL_EXT_protected_surface 1
#అయితే_ముగింపు /* EGL_EXT_protected_surface */

#నిర్వచితం_కాకపోతే EGL_EXT_query_reset_notification_strategy
#నిర్వచించు EGL_EXT_query_reset_notification_strategy 1
#అయితే_ముగింపు /* EGL_EXT_query_reset_notification_strategy */

#నిర్వచితం_కాకపోతే EGL_EXT_ప్రవాహం_వినియోగదారు_egloutput
#నిర్వచించు EGL_EXT_ప్రవాహం_వినియోగదారు_egloutput 1
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMEROUTPUTEXTPROC) (EGLDisplay dpy, EGLStreamKHR ప్రవాహం, EGLOutputLayerEXT layer);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_ప్రవాహం_వినియోగదారు_Output_EXT (EGLDisplay dpy, EGLStreamKHR ప్రవాహం, EGLOutputLayerEXT layer);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_EXT_stream_consumer_egloutput */

#నిర్వచితం_కాకపోతే EGL_EXT_surface_CTA861_3_metadata
#నిర్వచించు EGL_EXT_surface_CTA861_3_metadata 1
#నిర్వచించు EGL_CTA861_3_MAX_CONTENT_LIGHT_LEVEL_EXT 0x3360
#నిర్వచించు EGL_CTA861_3_MAX_చట్రం_సరాసరి_LEVEL_EXT 0x3361
#అయితే_ముగింపు /* EGL_EXT_surface_CTA861_3_metadata */

#నిర్వచితం_కాకపోతే EGL_EXT_surface_SMPTE2086_metadata
#నిర్వచించు EGL_EXT_surface_SMPTE2086_metadata 1
#నిర్వచించు EGL_SMPTE2086_DISPLAY_PRIMARY_RX_EXT 0x3341
#నిర్వచించు EGL_SMPTE2086_DISPLAY_PRIMARY_RY_EXT 0x3342
#నిర్వచించు EGL_SMPTE2086_DISPLAY_PRIMARY_GX_EXT 0x3343
#నిర్వచించు EGL_SMPTE2086_DISPLAY_PRIMARY_GY_EXT 0x3344
#నిర్వచించు EGL_SMPTE2086_DISPLAY_PRIMARY_BX_EXT 0x3345
#నిర్వచించు EGL_SMPTE2086_DISPLAY_PRIMARY_BY_EXT 0x3346
#నిర్వచించు EGL_SMPTE2086_WHITE_బిందువు_X_EXT   0x3347
#నిర్వచించు EGL_SMPTE2086_WHITE_బిందువు_Y_EXT   0x3348
#నిర్వచించు EGL_SMPTE2086_MAX_LUMINANCE_EXT   0x3349
#నిర్వచించు EGL_SMPTE2086_MIN_LUMINANCE_EXT   0x334A
#నిర్వచించు EGL_METADATA_SCALING_EXT          50000
#అయితే_ముగింపు /* EGL_EXT_surface_SMPTE2086_metadata */

#నిర్వచితం_కాకపోతే EGL_EXT_surface_compression
#నిర్వచించు EGL_EXT_surface_compression 1
#నిర్వచించు EGL_SURFACE_COMPRESSION_EXT       0x34B0
#నిర్వచించు EGL_SURFACE_COMPRESSION_PLANE1_EXT 0x328E
#నిర్వచించు EGL_SURFACE_COMPRESSION_PLANE2_EXT 0x328F
#నిర్వచించు EGL_SURFACE_COMPRESSION_FIXED_రేటు_NONE_EXT 0x34B1
#నిర్వచించు EGL_SURFACE_COMPRESSION_FIXED_రేటు_DEFAULT_EXT 0x34B2
#నిర్వచించు EGL_SURFACE_COMPRESSION_FIXED_రేటు_1_BPC_EXT 0x34B4
#నిర్వచించు EGL_SURFACE_COMPRESSION_FIXED_రేటు_2_BPC_EXT 0x34B5
#నిర్వచించు EGL_SURFACE_COMPRESSION_FIXED_రేటు_3_BPC_EXT 0x34B6
#నిర్వచించు EGL_SURFACE_COMPRESSION_FIXED_రేటు_4_BPC_EXT 0x34B7
#నిర్వచించు EGL_SURFACE_COMPRESSION_FIXED_రేటు_5_BPC_EXT 0x34B8
#నిర్వచించు EGL_SURFACE_COMPRESSION_FIXED_రేటు_6_BPC_EXT 0x34B9
#నిర్వచించు EGL_SURFACE_COMPRESSION_FIXED_రేటు_7_BPC_EXT 0x34BA
#నిర్వచించు EGL_SURFACE_COMPRESSION_FIXED_రేటు_8_BPC_EXT 0x34BB
#నిర్వచించు EGL_SURFACE_COMPRESSION_FIXED_రేటు_9_BPC_EXT 0x34BC
#నిర్వచించు EGL_SURFACE_COMPRESSION_FIXED_రేటు_10_BPC_EXT 0x34BD
#నిర్వచించు EGL_SURFACE_COMPRESSION_FIXED_రేటు_11_BPC_EXT 0x34BE
#నిర్వచించు EGL_SURFACE_COMPRESSION_FIXED_రేటు_12_BPC_EXT 0x34BF
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSUPPORTEDCOMPRESSIONRATESEXTPROC) (EGLDisplay dpy, EGLConfig config, స్థిరరాశి EGLAttrib *attrib_list, EGLint *rates, EGLint రేటు_కొలత, EGLint *అంకె_rates);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQuerySupportedCompressionRatesEXT (EGLDisplay dpy, EGLConfig config, స్థిరరాశి EGLAttrib *attrib_list, EGLint *rates, EGLint రేటు_కొలత, EGLint *అంకె_rates);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_EXT_surface_compression */

#నిర్వచితం_కాకపోతే EGL_EXT_మార్పిడి_buffers_with_damage
#నిర్వచించు EGL_EXT_మార్పిడి_buffers_with_damage 1
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC) (EGLDisplay dpy, EGLSurface surface, స్థిరరాశి EGLint *rects, EGLint n_rects);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_మార్పిడి_Buffers_With_Damage_EXT (EGLDisplay dpy, EGLSurface surface, స్థిరరాశి EGLint *rects, EGLint n_rects);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_EXT_swap_buffers_with_damage */

#నిర్వచితం_కాకపోతే EGL_EXT_sync_reuse
#నిర్వచించు EGL_EXT_sync_reuse 1
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLUNSIGNALSYNCEXTPROC) (EGLDisplay dpy, EGLSync sync, స్థిరరాశి EGLAttrib *attrib_list);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglUnsignalSyncEXT (EGLDisplay dpy, EGLSync sync, స్థిరరాశి EGLAttrib *attrib_list);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_EXT_sync_reuse */

#నిర్వచితం_కాకపోతే EGL_EXT_yuv_surface
#నిర్వచించు EGL_EXT_yuv_surface 1
#నిర్వచించు EGL_YUV_క్రమం_EXT                 0x3301
#నిర్వచించు EGL_YUV_సంఖ్య_యొక్క_PLANES_EXT      0x3311
#నిర్వచించు EGL_YUV_SUBSAMPLE_EXT             0x3312
#నిర్వచించు EGL_YUV_లోతు_RANGE_EXT           0x3317
#నిర్వచించు EGL_YUV_CSC_STANDARD_EXT          0x330A
#నిర్వచించు EGL_YUV_PLANE_BPP_EXT             0x331A
#నిర్వచించు EGL_YUV_బఫరు_EXT                0x3300
#నిర్వచించు EGL_YUV_క్రమం_YUV_EXT             0x3302
#నిర్వచించు EGL_YUV_క్రమం_YVU_EXT             0x3303
#నిర్వచించు EGL_YUV_క్రమం_YUYV_EXT            0x3304
#నిర్వచించు EGL_YUV_క్రమం_UYVY_EXT            0x3305
#నిర్వచించు EGL_YUV_క్రమం_YVYU_EXT            0x3306
#నిర్వచించు EGL_YUV_క్రమం_VYUY_EXT            0x3307
#నిర్వచించు EGL_YUV_క్రమం_AYUV_EXT            0x3308
#నిర్వచించు EGL_YUV_SUBSAMPLE_4_2_0_EXT       0x3313
#నిర్వచించు EGL_YUV_SUBSAMPLE_4_2_2_EXT       0x3314
#నిర్వచించు EGL_YUV_SUBSAMPLE_4_4_4_EXT       0x3315
#నిర్వచించు EGL_YUV_లోతు_RANGE_LIMITED_EXT   0x3318
#నిర్వచించు EGL_YUV_లోతు_RANGE_నిండిన_EXT      0x3319
#నిర్వచించు EGL_YUV_CSC_STANDARD_601_EXT      0x330B
#నిర్వచించు EGL_YUV_CSC_STANDARD_709_EXT      0x330C
#నిర్వచించు EGL_YUV_CSC_STANDARD_2020_EXT     0x330D
#నిర్వచించు EGL_YUV_PLANE_BPP_0_EXT           0x331B
#నిర్వచించు EGL_YUV_PLANE_BPP_8_EXT           0x331C
#నిర్వచించు EGL_YUV_PLANE_BPP_10_EXT          0x331D
#అయితే_ముగింపు /* EGL_EXT_yuv_surface */

#నిర్వచితం_కాకపోతే EGL_HI_clientpixmap
#నిర్వచించు EGL_HI_clientpixmap 1
నిర్మాణం EGLClientPixmapHI {
    శూన్య  *p_దత్తాంశం;
    EGLint i_వెడల్పు;
    EGLint i_ఎత్తు;
    EGLint iStride;
};
#నిర్వచించు EGL_CLIENT_PIXMAP_సూచిక_HI      0x8F74
రకనిర్వచనం EGLSurface (EGLAPIENTRYP PFNEGLCREATEPIXMAPSURFACEHIPROC) (EGLDisplay dpy, EGLConfig config, నిర్మాణం EGLClientPixmapHI *pixmap);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSurface EGLAPIENTRY eglCreatePixmapSurfaceHI (EGLDisplay dpy, EGLConfig config, నిర్మాణం EGLClientPixmapHI *pixmap);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_HI_clientpixmap */

#నిర్వచితం_కాకపోతే EGL_HI_colorformats
#నిర్వచించు EGL_HI_colorformats 1
#నిర్వచించు EGL_COLOR_FORMAT_HI               0x8F70
#నిర్వచించు EGL_COLOR_RGB_HI                  0x8F71
#నిర్వచించు EGL_COLOR_RGBA_HI                 0x8F72
#నిర్వచించు EGL_COLOR_ARGB_HI                 0x8F73
#అయితే_ముగింపు /* EGL_HI_colorformats */

#నిర్వచితం_కాకపోతే EGL_IMG_context_ప్రాధాన్యత
#నిర్వచించు EGL_IMG_context_ప్రాధాన్యత 1
#నిర్వచించు EGL_CONTEXT_ప్రాధాన్యత_LEVEL_IMG    0x3100
#నిర్వచించు EGL_CONTEXT_ప్రాధాన్యత_ఎగువ_IMG     0x3101
#నిర్వచించు EGL_CONTEXT_ప్రాధాన్యత_MEDIUM_IMG   0x3102
#నిర్వచించు EGL_CONTEXT_ప్రాధాన్యత_దిగువ_IMG      0x3103
#అయితే_ముగింపు /* EGL_IMG_context_priority */

#నిర్వచితం_కాకపోతే EGL_IMG_image_plane_attribs
#నిర్వచించు EGL_IMG_image_plane_attribs 1
#నిర్వచించు EGL_NATIVE_బఫరు_MULTIPLANE_SEPARATE_IMG 0x3105
#నిర్వచించు EGL_NATIVE_బఫరు_PLANE_స్థానభ్రంశం_IMG 0x3106
#అయితే_ముగింపు /* EGL_IMG_image_plane_attribs */

#నిర్వచితం_కాకపోతే EGL_MESA_drm_image
#నిర్వచించు EGL_MESA_drm_image 1
#నిర్వచించు EGL_DRM_బఫరు_FORMAT_MESA        0x31D0
#నిర్వచించు EGL_DRM_బఫరు_USE_MESA           0x31D1
#నిర్వచించు EGL_DRM_బఫరు_FORMAT_ARGB32_MESA 0x31D2
#నిర్వచించు EGL_DRM_బఫరు_MESA               0x31D3
#నిర్వచించు EGL_DRM_బఫరు_STRIDE_MESA        0x31D4
#నిర్వచించు EGL_DRM_బఫరు_USE_SCANOUT_MESA   0x00000001
#నిర్వచించు EGL_DRM_బఫరు_USE_SHARE_MESA     0x00000002
#నిర్వచించు EGL_DRM_బఫరు_USE_CURSOR_MESA    0x00000004
రకనిర్వచనం EGLImageKHR (EGLAPIENTRYP PFNEGLCREATEDRMIMAGEMESAPROC) (EGLDisplay dpy, స్థిరరాశి EGLint *attrib_list);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLEXPORTDRMIMAGEMESAPROC) (EGLDisplay dpy, EGLImageKHR image, EGLint *name, EGLint *handle, EGLint *stride);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLImageKHR EGLAPIENTRY eglCreateDRMImageMESA (EGLDisplay dpy, స్థిరరాశి EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglExportDRMImageMESA (EGLDisplay dpy, EGLImageKHR image, EGLint *name, EGLint *handle, EGLint *stride);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_MESA_drm_image */

#నిర్వచితం_కాకపోతే EGL_MESA_image_dma_buf_export
#నిర్వచించు EGL_MESA_image_dma_buf_export 1
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLEXPORTDMABUFIMAGEQUERYMESAPROC) (EGLDisplay dpy, EGLImageKHR image, పూర్ణాంకం *fourcc, పూర్ణాంకం *అంకె_planes, EGLuint64KHR *modifiers);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLEXPORTDMABUFIMAGEMESAPROC) (EGLDisplay dpy, EGLImageKHR image, పూర్ణాంకం *fds, EGLint *strides, EGLint *offsets);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglExportDMABUFImageQueryMESA (EGLDisplay dpy, EGLImageKHR image, పూర్ణాంకం *fourcc, పూర్ణాంకం *అంకె_planes, EGLuint64KHR *modifiers);
EGLAPI EGLBoolean EGLAPIENTRY eglExportDMABUFImageMESA (EGLDisplay dpy, EGLImageKHR image, పూర్ణాంకం *fds, EGLint *strides, EGLint *offsets);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_MESA_image_dma_buf_export */

#నిర్వచితం_కాకపోతే EGL_MESA_platform_gbm
#నిర్వచించు EGL_MESA_platform_gbm 1
#నిర్వచించు EGL_PLATFORM_GBM_MESA             0x31D7
#అయితే_ముగింపు /* EGL_MESA_platform_gbm */

#నిర్వచితం_కాకపోతే EGL_MESA_platform_surfaceless
#నిర్వచించు EGL_MESA_platform_surfaceless 1
#నిర్వచించు EGL_PLATFORM_SURFACELESS_MESA     0x31DD
#అయితే_ముగింపు /* EGL_MESA_platform_surfaceless */

#నిర్వచితం_కాకపోతే EGL_MESA_query_driver
#నిర్వచించు EGL_MESA_query_driver 1
రకనిర్వచనం అక్షరం *(EGLAPIENTRYP PFNEGLGETDISPLAYDRIVERCONFIGPROC) (EGLDisplay dpy);
రకనిర్వచనం స్థిరరాశి అక్షరం *(EGLAPIENTRYP PFNEGLGETDISPLAYDRIVERNAMEPROC) (EGLDisplay dpy);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI అక్షరం *EGLAPIENTRY eglGetDisplayDriverConfig (EGLDisplay dpy);
EGLAPI స్థిరరాశి అక్షరం *EGLAPIENTRY eglGetDisplayDriverName (EGLDisplay dpy);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_MESA_query_driver */

#నిర్వచితం_కాకపోతే EGL_NOK_మార్పిడి_region
#నిర్వచించు EGL_NOK_మార్పిడి_region 1
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSREGIONNOKPROC) (EGLDisplay dpy, EGLSurface surface, EGLint అంకె_Rects_2, స్థిరరాశి EGLint *rects);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_మార్పిడి_Buffers_Region_NOK (EGLDisplay dpy, EGLSurface surface, EGLint అంకె_Rects_2, స్థిరరాశి EGLint *rects);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_NOK_swap_region */

#నిర్వచితం_కాకపోతే EGL_NOK_మార్పిడి_region2
#నిర్వచించు EGL_NOK_మార్పిడి_region2 1
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSREGION2NOKPROC) (EGLDisplay dpy, EGLSurface surface, EGLint అంకె_Rects_2, స్థిరరాశి EGLint *rects);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_మార్పిడి_Buffers_Region2_NOK (EGLDisplay dpy, EGLSurface surface, EGLint అంకె_Rects_2, స్థిరరాశి EGLint *rects);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_NOK_swap_region2 */

#నిర్వచితం_కాకపోతే EGL_NOK_texture_from_pixmap
#నిర్వచించు EGL_NOK_texture_from_pixmap 1
#నిర్వచించు EGL_Y_INVERTED_NOK                0x307F
#అయితే_ముగింపు /* EGL_NOK_texture_from_pixmap */

#నిర్వచితం_కాకపోతే EGL_NV_3dvision_surface
#నిర్వచించు EGL_NV_3dvision_surface 1
#నిర్వచించు EGL_AUTO_STEREO_NV                0x3136
#అయితే_ముగింపు /* EGL_NV_3dvision_surface */

#నిర్వచితం_కాకపోతే EGL_NV_context_ప్రాధాన్యత_realtime
#నిర్వచించు EGL_NV_context_ప్రాధాన్యత_realtime 1
#నిర్వచించు EGL_CONTEXT_ప్రాధాన్యత_REALTIME_NV  0x3357
#అయితే_ముగింపు /* EGL_NV_context_priority_realtime */

#నిర్వచితం_కాకపోతే EGL_NV_coverage_sample
#నిర్వచించు EGL_NV_coverage_sample 1
#నిర్వచించు EGL_COVERAGE_BUFFERS_NV           0x30E0
#నిర్వచించు EGL_COVERAGE_SAMPLES_NV           0x30E1
#అయితే_ముగింపు /* EGL_NV_coverage_sample */

#నిర్వచితం_కాకపోతే EGL_NV_coverage_sample_resolve
#నిర్వచించు EGL_NV_coverage_sample_resolve 1
#నిర్వచించు EGL_COVERAGE_SAMPLE_RESOLVE_NV    0x3131
#నిర్వచించు EGL_COVERAGE_SAMPLE_RESOLVE_DEFAULT_NV 0x3132
#నిర్వచించు EGL_COVERAGE_SAMPLE_RESOLVE_NONE_NV 0x3133
#అయితే_ముగింపు /* EGL_NV_coverage_sample_resolve */

#నిర్వచితం_కాకపోతే EGL_NV_cuda_event
#నిర్వచించు EGL_NV_cuda_event 1
#నిర్వచించు EGL_CUDA_EVENT_HANDLE_NV          0x323B
#నిర్వచించు EGL_SYNC_CUDA_EVENT_NV            0x323C
#నిర్వచించు EGL_SYNC_CUDA_EVENT_COMPLETE_NV   0x323D
#అయితే_ముగింపు /* EGL_NV_cuda_event */

#నిర్వచితం_కాకపోతే EGL_NV_లోతు_nonlinear
#నిర్వచించు EGL_NV_లోతు_nonlinear 1
#నిర్వచించు EGL_లోతు_ENCODING_NV             0x30E2
#నిర్వచించు EGL_లోతు_ENCODING_NONE_NV        0
#నిర్వచించు EGL_లోతు_ENCODING_NONLINEAR_NV   0x30E3
#అయితే_ముగింపు /* EGL_NV_depth_nonlinear */

#నిర్వచితం_కాకపోతే EGL_NV_device_cuda
#నిర్వచించు EGL_NV_device_cuda 1
#నిర్వచించు EGL_CUDA_DEVICE_NV                0x323A
#అయితే_ముగింపు /* EGL_NV_device_cuda */

#నిర్వచితం_కాకపోతే EGL_NV_native_query
#నిర్వచించు EGL_NV_native_query 1
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLQUERYNATIVEDISPLAYNVPROC) (EGLDisplay dpy, EGLNativeDisplayType *display_id);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLQUERYNATIVEWINDOWNVPROC) (EGLDisplay dpy, EGLSurface surf, EGLNative_కిటికీ_Type *కిటికీ);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLQUERYNATIVEPIXMAPNVPROC) (EGLDisplay dpy, EGLSurface surf, EGLNativePixmapType *pixmap);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryNativeDisplayNV (EGLDisplay dpy, EGLNativeDisplayType *display_id);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Native_కిటికీ_NV (EGLDisplay dpy, EGLSurface surf, EGLNative_కిటికీ_Type *కిటికీ);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryNativePixmapNV (EGLDisplay dpy, EGLSurface surf, EGLNativePixmapType *pixmap);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_NV_native_query */

#నిర్వచితం_కాకపోతే EGL_NV_post_convert_rounding
#నిర్వచించు EGL_NV_post_convert_rounding 1
#అయితే_ముగింపు /* EGL_NV_post_convert_rounding */

#నిర్వచితం_కాకపోతే EGL_NV_post_sub_బఫరు
#నిర్వచించు EGL_NV_post_sub_బఫరు 1
#నిర్వచించు EGL_POST_SUB_బఫరు_SUPPORTED_NV  0x30BE
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLPOSTSUBBUFFERNVPROC) (EGLDisplay dpy, EGLSurface surface, EGLint x, EGLint y, EGLint వెడల్పు, EGLint ఎత్తు);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Post_Sub_బఫరు_NV (EGLDisplay dpy, EGLSurface surface, EGLint x, EGLint y, EGLint వెడల్పు, EGLint ఎత్తు);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_NV_post_sub_buffer */

#నిర్వచితం_కాకపోతే EGL_NV_quadruple_బఫరు
#నిర్వచించు EGL_NV_quadruple_బఫరు 1
#నిర్వచించు EGL_QUADRUPLE_బఫరు_NV           0x3231
#అయితే_ముగింపు /* EGL_NV_quadruple_buffer */

#నిర్వచితం_కాకపోతే EGL_NV_robustness_video_జ్ఞాపకం_purge
#నిర్వచించు EGL_NV_robustness_video_జ్ఞాపకం_purge 1
#నిర్వచించు EGL_GENERATE_RESET_ON_VIDEO_జ్ఞాపకం_PURGE_NV 0x334C
#అయితే_ముగింపు /* EGL_NV_robustness_video_memory_purge */

#నిర్వచితం_కాకపోతే EGL_NV_ప్రవాహం_వినియోగదారు_eglimage
#నిర్వచించు EGL_NV_ప్రవాహం_వినియోగదారు_eglimage 1
#నిర్వచించు EGL_ప్రవాహం_వినియోగదారు_IMAGE_NV      0x3373
#నిర్వచించు EGL_ప్రవాహం_IMAGE_కూడు_NV           0x3374
#నిర్వచించు EGL_ప్రవాహం_IMAGE_REMOVE_NV        0x3375
#నిర్వచించు EGL_ప్రవాహం_IMAGE_అందుబాటు_NV     0x3376
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMIMAGECONSUMERCONNECTNVPROC) (EGLDisplay dpy, EGLStreamKHR ప్రవాహం, EGLint అంకె_modifiers, స్థిరరాశి EGLuint64KHR *modifiers, స్థిరరాశి EGLAttrib *attrib_list);
రకనిర్వచనం EGLint (EGLAPIENTRYP PFNEGLQUERYSTREAMCONSUMEREVENTNVPROC) (EGLDisplay dpy, EGLStreamKHR ప్రవాహం, EGLTime timeout, EGLenum *event, EGLAttrib *aux);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMACQUIREIMAGENVPROC) (EGLDisplay dpy, EGLStreamKHR ప్రవాహం, EGLImage *pImage, EGLSync sync);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMRELEASEIMAGENVPROC) (EGLDisplay dpy, EGLStreamKHR ప్రవాహం, EGLImage image, EGLSync sync);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_ప్రవాహం_Image_వినియోగదారు_Connect_NV (EGLDisplay dpy, EGLStreamKHR ప్రవాహం, EGLint అంకె_modifiers, స్థిరరాశి EGLuint64KHR *modifiers, స్థిరరాశి EGLAttrib *attrib_list);
EGLAPI EGLint EGLAPIENTRY egl_Query_ప్రవాహం_వినియోగదారు_Event_NV (EGLDisplay dpy, EGLStreamKHR ప్రవాహం, EGLTime timeout, EGLenum *event, EGLAttrib *aux);
EGLAPI EGLBoolean EGLAPIENTRY egl_ప్రవాహం_Acquire_Image_NV (EGLDisplay dpy, EGLStreamKHR ప్రవాహం, EGLImage *pImage, EGLSync sync);
EGLAPI EGLBoolean EGLAPIENTRY egl_ప్రవాహం_Release_Image_NV (EGLDisplay dpy, EGLStreamKHR ప్రవాహం, EGLImage image, EGLSync sync);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_NV_stream_consumer_eglimage */

#నిర్వచితం_కాకపోతే EGL_NV_ప్రవాహం_వినియోగదారు_eglimage_use_scanout_attrib
#నిర్వచించు EGL_NV_ప్రవాహం_వినియోగదారు_eglimage_use_scanout_attrib 1
#నిర్వచించు EGL_ప్రవాహం_వినియోగదారు_IMAGE_USE_SCANOUT_NV 0x3378
#అయితే_ముగింపు /* EGL_NV_stream_consumer_eglimage_use_scanout_attrib */

#నిర్వచితం_కాకపోతే EGL_NV_ప్రవాహం_వినియోగదారు_gltexture_yuv
#నిర్వచించు EGL_NV_ప్రవాహం_వినియోగదారు_gltexture_yuv 1
#నిర్వచించు EGL_YUV_PLANE0_TEXTURE_UNIT_NV    0x332C
#నిర్వచించు EGL_YUV_PLANE1_TEXTURE_UNIT_NV    0x332D
#నిర్వచించు EGL_YUV_PLANE2_TEXTURE_UNIT_NV    0x332E
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALATTRIBSNVPROC) (EGLDisplay dpy, EGLStreamKHR ప్రవాహం, స్థిరరాశి EGLAttrib *attrib_list);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_ప్రవాహం_వినియోగదారు_GLTexture_External_Attribs_NV (EGLDisplay dpy, EGLStreamKHR ప్రవాహం, స్థిరరాశి EGLAttrib *attrib_list);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_NV_stream_consumer_gltexture_yuv */

#నిర్వచితం_కాకపోతే EGL_NV_ప్రవాహం_cross_display
#నిర్వచించు EGL_NV_ప్రవాహం_cross_display 1
#నిర్వచించు EGL_ప్రవాహం_CROSS_DISPLAY_NV       0x334E
#అయితే_ముగింపు /* EGL_NV_stream_cross_display */

#నిర్వచితం_కాకపోతే EGL_NV_ప్రవాహం_cross_object
#నిర్వచించు EGL_NV_ప్రవాహం_cross_object 1
#నిర్వచించు EGL_ప్రవాహం_CROSS_OBJECT_NV        0x334D
#అయితే_ముగింపు /* EGL_NV_stream_cross_object */

#నిర్వచితం_కాకపోతే EGL_NV_ప్రవాహం_cross_విభజన
#నిర్వచించు EGL_NV_ప్రవాహం_cross_విభజన 1
#నిర్వచించు EGL_ప్రవాహం_CROSS_విభజన_NV     0x323F
#అయితే_ముగింపు /* EGL_NV_stream_cross_partition */

#నిర్వచితం_కాకపోతే EGL_NV_ప్రవాహం_cross_process
#నిర్వచించు EGL_NV_ప్రవాహం_cross_process 1
#నిర్వచించు EGL_ప్రవాహం_CROSS_PROCESS_NV       0x3245
#అయితే_ముగింపు /* EGL_NV_stream_cross_process */

#నిర్వచితం_కాకపోతే EGL_NV_ప్రవాహం_cross_system
#నిర్వచించు EGL_NV_ప్రవాహం_cross_system 1
#నిర్వచించు EGL_ప్రవాహం_CROSS_SYSTEM_NV        0x334F
#అయితే_ముగింపు /* EGL_NV_stream_cross_system */

#నిర్వచితం_కాకపోతే EGL_NV_ప్రవాహం_dma
#నిర్వచించు EGL_NV_ప్రవాహం_dma 1
#నిర్వచించు EGL_ప్రవాహం_DMA_NV                 0x3371
#నిర్వచించు EGL_ప్రవాహం_DMA_SERVER_NV          0x3372
#అయితే_ముగింపు /* EGL_NV_stream_dma */

#నిర్వచితం_కాకపోతే EGL_NV_ప్రవాహం_fifo_తదుపరి
#నిర్వచించు EGL_NV_ప్రవాహం_fifo_తదుపరి 1
#నిర్వచించు EGL_PENDING_చట్రం_NV              0x3329
#నిర్వచించు EGL_ప్రవాహం_సమయం_PENDING_NV        0x332A
#అయితే_ముగింపు /* EGL_NV_stream_fifo_next */

#నిర్వచితం_కాకపోతే EGL_NV_ప్రవాహం_fifo_synchronous
#నిర్వచించు EGL_NV_ప్రవాహం_fifo_synchronous 1
#నిర్వచించు EGL_ప్రవాహం_FIFO_SYNCHRONOUS_NV    0x3336
#అయితే_ముగింపు /* EGL_NV_stream_fifo_synchronous */

#నిర్వచితం_కాకపోతే EGL_NV_ప్రవాహం_flush
#నిర్వచించు EGL_NV_ప్రవాహం_flush 1
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMFLUSHNVPROC) (EGLDisplay dpy, EGLStreamKHR ప్రవాహం);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_ప్రవాహం_Flush_NV (EGLDisplay dpy, EGLStreamKHR ప్రవాహం);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_NV_stream_flush */

#నిర్వచితం_కాకపోతే EGL_NV_ప్రవాహం_చట్రం_limits
#నిర్వచించు EGL_NV_ప్రవాహం_చట్రం_limits 1
#నిర్వచించు EGL_ఉత్పాదకుడు_MAX_చట్రం_HINT_NV    0x3337
#నిర్వచించు EGL_వినియోగదారు_MAX_చట్రం_HINT_NV    0x3338
#అయితే_ముగింపు /* EGL_NV_stream_frame_limits */

#నిర్వచితం_కాకపోతే EGL_NV_ప్రవాహం_metadata
#నిర్వచించు EGL_NV_ప్రవాహం_metadata 1
#నిర్వచించు EGL_MAX_ప్రవాహం_METADATA_ఖండాలు_NV 0x3250
#నిర్వచించు EGL_MAX_ప్రవాహం_METADATA_ఖండం_కొలత_NV 0x3251
#నిర్వచించు EGL_MAX_ప్రవాహం_METADATA_మొత్తం_కొలత_NV 0x3252
#నిర్వచించు EGL_ఉత్పాదకుడు_METADATA_NV          0x3253
#నిర్వచించు EGL_వినియోగదారు_METADATA_NV          0x3254
#నిర్వచించు EGL_PENDING_METADATA_NV           0x3328
#నిర్వచించు EGL_METADATA0_కొలత_NV             0x3255
#నిర్వచించు EGL_METADATA1_కొలత_NV             0x3256
#నిర్వచించు EGL_METADATA2_కొలత_NV             0x3257
#నిర్వచించు EGL_METADATA3_కొలత_NV             0x3258
#నిర్వచించు EGL_METADATA0_TYPE_NV             0x3259
#నిర్వచించు EGL_METADATA1_TYPE_NV             0x325A
#నిర్వచించు EGL_METADATA2_TYPE_NV             0x325B
#నిర్వచించు EGL_METADATA3_TYPE_NV             0x325C
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDISPLAYATTRIBNVPROC) (EGLDisplay dpy, EGLint attribute, EGLAttrib *విలువ);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLSETSTREAMMETADATANVPROC) (EGLDisplay dpy, EGLStreamKHR ప్రవాహం, EGLint n, EGLint స్థానభ్రంశం_2, EGLint కొలత, స్థిరరాశి శూన్య *దత్తాంశం);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMMETADATANVPROC) (EGLDisplay dpy, EGLStreamKHR ప్రవాహం, EGLenum name, EGLint n, EGLint స్థానభ్రంశం_2, EGLint కొలత, శూన్య *దత్తాంశం);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDisplayAttribNV (EGLDisplay dpy, EGLint attribute, EGLAttrib *విలువ);
EGLAPI EGLBoolean EGLAPIENTRY egl_సమితి_ప్రవాహం_Metadata_NV (EGLDisplay dpy, EGLStreamKHR ప్రవాహం, EGLint n, EGLint స్థానభ్రంశం_2, EGLint కొలత, స్థిరరాశి శూన్య *దత్తాంశం);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_ప్రవాహం_Metadata_NV (EGLDisplay dpy, EGLStreamKHR ప్రవాహం, EGLenum name, EGLint n, EGLint స్థానభ్రంశం_2, EGLint కొలత, శూన్య *దత్తాంశం);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_NV_stream_metadata */

#నిర్వచితం_కాకపోతే EGL_NV_ప్రవాహం_origin
#నిర్వచించు EGL_NV_ప్రవాహం_origin 1
#నిర్వచించు EGL_ప్రవాహం_చట్రం_ORIGIN_X_NV      0x3366
#నిర్వచించు EGL_ప్రవాహం_చట్రం_ORIGIN_Y_NV      0x3367
#నిర్వచించు EGL_ప్రవాహం_చట్రం_MAJOR_AXIS_NV    0x3368
#నిర్వచించు EGL_వినియోగదారు_AUTO_ORIENTATION_NV  0x3369
#నిర్వచించు EGL_ఉత్పాదకుడు_AUTO_ORIENTATION_NV  0x336A
#నిర్వచించు EGL_ఎడమ_NV                       0x336B
#నిర్వచించు EGL_కుడి_NV                      0x336C
#నిర్వచించు EGL_శిఖరం_NV                        0x336D
#నిర్వచించు EGL_BOTTOM_NV                     0x336E
#నిర్వచించు EGL_X_AXIS_NV                     0x336F
#నిర్వచించు EGL_Y_AXIS_NV                     0x3370
#అయితే_ముగింపు /* EGL_NV_stream_origin */

#నిర్వచితం_కాకపోతే EGL_NV_ప్రవాహం_remote
#నిర్వచించు EGL_NV_ప్రవాహం_remote 1
#నిర్వచించు EGL_ప్రవాహం_STATE_INITIALIZING_NV  0x3240
#నిర్వచించు EGL_ప్రవాహం_TYPE_NV                0x3241
#నిర్వచించు EGL_ప్రవాహం_PROTOCOL_NV            0x3242
#నిర్వచించు EGL_ప్రవాహం_ENDPOINT_NV            0x3243
#నిర్వచించు EGL_ప్రవాహం_LOCAL_NV               0x3244
#నిర్వచించు EGL_ప్రవాహం_ఉత్పాదకుడు_NV            0x3247
#నిర్వచించు EGL_ప్రవాహం_వినియోగదారు_NV            0x3248
#నిర్వచించు EGL_ప్రవాహం_PROTOCOL_FD_NV         0x3246
#అయితే_ముగింపు /* EGL_NV_stream_remote */

#నిర్వచితం_కాకపోతే EGL_NV_ప్రవాహం_reset
#నిర్వచించు EGL_NV_ప్రవాహం_reset 1
#నిర్వచించు EGL_SUPPORT_RESET_NV              0x3334
#నిర్వచించు EGL_SUPPORT_REUSE_NV              0x3335
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLRESETSTREAMNVPROC) (EGLDisplay dpy, EGLStreamKHR ప్రవాహం);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Reset_ప్రవాహం_NV (EGLDisplay dpy, EGLStreamKHR ప్రవాహం);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_NV_stream_reset */

#నిర్వచితం_కాకపోతే EGL_NV_ప్రవాహం_socket
#నిర్వచించు EGL_NV_ప్రవాహం_socket 1
#నిర్వచించు EGL_ప్రవాహం_PROTOCOL_SOCKET_NV     0x324B
#నిర్వచించు EGL_SOCKET_HANDLE_NV              0x324C
#నిర్వచించు EGL_SOCKET_TYPE_NV                0x324D
#అయితే_ముగింపు /* EGL_NV_stream_socket */

#నిర్వచితం_కాకపోతే EGL_NV_ప్రవాహం_socket_inet
#నిర్వచించు EGL_NV_ప్రవాహం_socket_inet 1
#నిర్వచించు EGL_SOCKET_TYPE_INET_NV           0x324F
#అయితే_ముగింపు /* EGL_NV_stream_socket_inet */

#నిర్వచితం_కాకపోతే EGL_NV_ప్రవాహం_socket_unix
#నిర్వచించు EGL_NV_ప్రవాహం_socket_unix 1
#నిర్వచించు EGL_SOCKET_TYPE_UNIX_NV           0x324E
#అయితే_ముగింపు /* EGL_NV_stream_socket_unix */

#నిర్వచితం_కాకపోతే EGL_NV_ప్రవాహం_sync
#నిర్వచించు EGL_NV_ప్రవాహం_sync 1
#నిర్వచించు EGL_SYNC_NEW_చట్రం_NV             0x321F
రకనిర్వచనం EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESTREAMSYNCNVPROC) (EGLDisplay dpy, EGLStreamKHR ప్రవాహం, EGLenum type, స్థిరరాశి EGLint *attrib_list);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncKHR EGLAPIENTRY egl_Create_ప్రవాహం_Sync_NV (EGLDisplay dpy, EGLStreamKHR ప్రవాహం, EGLenum type, స్థిరరాశి EGLint *attrib_list);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_NV_stream_sync */

#నిర్వచితం_కాకపోతే EGL_NV_sync
#నిర్వచించు EGL_NV_sync 1
రకనిర్వచనం శూన్య *EGLSyncNV;
రకనిర్వచనం khronos_utime_nanoseconds_t EGLTimeNV;
#నిర్వచితమైతే KHRONOS_SUPPORT_INT64
#నిర్వచించు EGL_SYNC_పూర్వ_COMMANDS_COMPLETE_NV 0x30E6
#నిర్వచించు EGL_SYNC_స్థితి_NV                0x30E7
#నిర్వచించు EGL_SIGNALED_NV                   0x30E8
#నిర్వచించు EGL_UNSIGNALED_NV                 0x30E9
#నిర్వచించు EGL_SYNC_FLUSH_COMMANDS_బిట్టు_NV    0x0001
#నిర్వచించు EGL_FOREVER_NV                    0xFFFFFFFFFFFFFFFFull
#నిర్వచించు EGL_ALREADY_SIGNALED_NV           0x30EA
#నిర్వచించు EGL_TIMEOUT_EXPIRED_NV            0x30EB
#నిర్వచించు EGL_CONDITION_SATISFIED_NV        0x30EC
#నిర్వచించు EGL_SYNC_TYPE_NV                  0x30ED
#నిర్వచించు EGL_SYNC_CONDITION_NV             0x30EE
#నిర్వచించు EGL_SYNC_FENCE_NV                 0x30EF
#నిర్వచించు EGL_NO_SYNC_NV                    EGL_CAST(EGLSyncNV,0)
రకనిర్వచనం EGLSyncNV (EGLAPIENTRYP PFNEGLCREATEFENCESYNCNVPROC) (EGLDisplay dpy, EGLenum condition, స్థిరరాశి EGLint *attrib_list);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCNVPROC) (EGLSyncNV sync);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLFENCENVPROC) (EGLSyncNV sync);
రకనిర్వచనం EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCNVPROC) (EGLSyncNV sync, EGLint flags, EGLTimeNV timeout);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLSIGNALSYNCNVPROC) (EGLSyncNV sync, EGLenum బహుళకం);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLGETSYNCATTRIBNVPROC) (EGLSyncNV sync, EGLint attribute, EGLint *విలువ);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncNV EGLAPIENTRY eglCreateFenceSyncNV (EGLDisplay dpy, EGLenum condition, స్థిరరాశి EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySyncNV (EGLSyncNV sync);
EGLAPI EGLBoolean EGLAPIENTRY eglFenceNV (EGLSyncNV sync);
EGLAPI EGLint EGLAPIENTRY eglClientWaitSyncNV (EGLSyncNV sync, EGLint flags, EGLTimeNV timeout);
EGLAPI EGLBoolean EGLAPIENTRY eglSignalSyncNV (EGLSyncNV sync, EGLenum బహుళకం);
EGLAPI EGLBoolean EGLAPIENTRY eglGetSyncAttribNV (EGLSyncNV sync, EGLint attribute, EGLint *విలువ);
#అయితే_ముగింపు
#అయితే_ముగింపు /* KHRONOS_SUPPORT_INT64 */
#అయితే_ముగింపు /* EGL_NV_sync */

#నిర్వచితం_కాకపోతే EGL_NV_system_సమయం
#నిర్వచించు EGL_NV_system_సమయం 1
రకనిర్వచనం khronos_utime_nanoseconds_t EGLuint64NV;
#నిర్వచితమైతే KHRONOS_SUPPORT_INT64
రకనిర్వచనం EGLuint64NV (EGLAPIENTRYP PFNEGLGETSYSTEMTIMEFREQUENCYNVPROC) (శూన్య);
రకనిర్వచనం EGLuint64NV (EGLAPIENTRYP PFNEGLGETSYSTEMTIMENVPROC) (శూన్య);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLuint64NV EGLAPIENTRY egl_Get_System_సమయం_Frequency_NV (శూన్య);
EGLAPI EGLuint64NV EGLAPIENTRY egl_Get_System_సమయం_NV (శూన్య);
#అయితే_ముగింపు
#అయితే_ముగింపు /* KHRONOS_SUPPORT_INT64 */
#అయితే_ముగింపు /* EGL_NV_system_time */

#నిర్వచితం_కాకపోతే EGL_NV_triple_బఫరు
#నిర్వచించు EGL_NV_triple_బఫరు 1
#నిర్వచించు EGL_TRIPLE_బఫరు_NV              0x3230
#అయితే_ముగింపు /* EGL_NV_triple_buffer */

#నిర్వచితం_కాకపోతే EGL_QNX_image_native_బఫరు
#నిర్వచించు EGL_QNX_image_native_బఫరు 1
#నిర్వచించు EGL_NATIVE_బఫరు_QNX             0x3551
#అయితే_ముగింపు /* EGL_QNX_image_native_buffer */

#నిర్వచితం_కాకపోతే EGL_QNX_platform_screen
#నిర్వచించు EGL_QNX_platform_screen 1
#నిర్వచించు EGL_PLATFORM_SCREEN_QNX           0x3550
#అయితే_ముగింపు /* EGL_QNX_platform_screen */

#నిర్వచితం_కాకపోతే EGL_TIZEN_image_native_బఫరు
#నిర్వచించు EGL_TIZEN_image_native_బఫరు 1
#నిర్వచించు EGL_NATIVE_బఫరు_TIZEN           0x32A0
#అయితే_ముగింపు /* EGL_TIZEN_image_native_buffer */

#నిర్వచితం_కాకపోతే EGL_TIZEN_image_native_surface
#నిర్వచించు EGL_TIZEN_image_native_surface 1
#నిర్వచించు EGL_NATIVE_SURFACE_TIZEN          0x32A1
#అయితే_ముగింపు /* EGL_TIZEN_image_native_surface */

#నిర్వచితం_కాకపోతే EGL_WL_bind_wayland_display
#నిర్వచించు EGL_WL_bind_wayland_display 1
#నిర్వచించు PFNEGLBINDWAYLANDDISPLAYWL PFNEGLBINDWAYLANDDISPLAYWLPROC
#నిర్వచించు PFNEGLUNBINDWAYLANDDISPLAYWL PFNEGLUNBINDWAYLANDDISPLAYWLPROC
#నిర్వచించు PFNEGLQUERYWAYLANDBUFFERWL PFNEGLQUERYWAYLANDBUFFERWLPROC
నిర్మాణం wl_display;
నిర్మాణం wl_resource;
#నిర్వచించు EGL_WAYLAND_బఫరు_WL             0x31D5
#నిర్వచించు EGL_WAYLAND_PLANE_WL              0x31D6
#నిర్వచించు EGL_TEXTURE_Y_U_V_WL              0x31D7
#నిర్వచించు EGL_TEXTURE_Y_UV_WL               0x31D8
#నిర్వచించు EGL_TEXTURE_Y_XUXV_WL             0x31D9
#నిర్వచించు EGL_TEXTURE_EXTERNAL_WL           0x31DA
#నిర్వచించు EGL_WAYLAND_Y_INVERTED_WL         0x31DB
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLBINDWAYLANDDISPLAYWLPROC) (EGLDisplay dpy, నిర్మాణం wl_display *display);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLUNBINDWAYLANDDISPLAYWLPROC) (EGLDisplay dpy, నిర్మాణం wl_display *display);
రకనిర్వచనం EGLBoolean (EGLAPIENTRYP PFNEGLQUERYWAYLANDBUFFERWLPROC) (EGLDisplay dpy, నిర్మాణం wl_resource *బఫరు_2, EGLint attribute, EGLint *విలువ);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglBindWaylandDisplayWL (EGLDisplay dpy, నిర్మాణం wl_display *display);
EGLAPI EGLBoolean EGLAPIENTRY eglUnbindWaylandDisplayWL (EGLDisplay dpy, నిర్మాణం wl_display *display);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Wayland_బఫరు_WL (EGLDisplay dpy, నిర్మాణం wl_resource *బఫరు_2, EGLint attribute, EGLint *విలువ);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_WL_bind_wayland_display */

#నిర్వచితం_కాకపోతే EGL_WL_create_wayland_బఫరు_from_image
#నిర్వచించు EGL_WL_create_wayland_బఫరు_from_image 1
#నిర్వచించు PFNEGLCREATEWAYLANDBUFFERFROMIMAGEWL PFNEGLCREATEWAYLANDBUFFERFROMIMAGEWLPROC
నిర్మాణం wl_బఫరు;
రకనిర్వచనం నిర్మాణం wl_బఫరు *(EGLAPIENTRYP PFNEGLCREATEWAYLANDBUFFERFROMIMAGEWLPROC) (EGLDisplay dpy, EGLImageKHR image);
#నిర్వచితమైతే EGL_EGLEXT_PROTOTYPES
EGLAPI నిర్మాణం wl_బఫరు *EGLAPIENTRY egl_Create_Wayland_బఫరు_From_Image_WL (EGLDisplay dpy, EGLImageKHR image);
#అయితే_ముగింపు
#అయితే_ముగింపు /* EGL_WL_create_wayland_buffer_from_image */

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు
