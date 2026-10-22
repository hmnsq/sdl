#اگر_غیر_تعریف_شدہ __eglext_h_
#تعریف_کرو __eglext_h_ 1

#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم

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

#شامل <EGL/eglplatform.h>

#تعریف_کرو EGL_EGLEXT_نسخہ 20260319

/* Generated C header for:
 * API: egl
 * Versions considered: .*
 * Versions emitted: _nomatch_^
 * Default extensions included: egl
 * Additional extensions included: _nomatch_^
 * Extensions removed: _nomatch_^
 */

#اگر_غیر_تعریف_شدہ EGL_KHR_cl_event
#تعریف_کرو EGL_KHR_cl_event 1
#تعریف_کرو EGL_CL_EVENT_HANDLE_KHR           0x309C
#تعریف_کرو EGL_SYNC_CL_EVENT_KHR             0x30FE
#تعریف_کرو EGL_SYNC_CL_EVENT_COMPLETE_KHR    0x30FF
#اگر_ختم /* EGL_KHR_cl_event */

#اگر_غیر_تعریف_شدہ EGL_KHR_cl_event2
#تعریف_کرو EGL_KHR_cl_event2 1
قسمتعریف خالی *EGLSyncKHR;
قسمتعریف intptr_t EGLAttribKHR;
قسمتعریف EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESYNC64KHRPROC) (EGLDisplay dpy, EGLenum type, ثابت EGLAttribKHR *attrib_list);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncKHR EGLAPIENTRY eglCreateSync64KHR (EGLDisplay dpy, EGLenum type, ثابت EGLAttribKHR *attrib_list);
#اگر_ختم
#اگر_ختم /* EGL_KHR_cl_event2 */

#اگر_غیر_تعریف_شدہ EGL_KHR_client_get_all_proc_پتے
#تعریف_کرو EGL_KHR_client_get_all_proc_پتے 1
#اگر_ختم /* EGL_KHR_client_get_all_proc_addresses */

#اگر_غیر_تعریف_شدہ EGL_KHR_config_attribs
#تعریف_کرو EGL_KHR_config_attribs 1
#تعریف_کرو EGL_CONFORMANT_KHR                0x3042
#تعریف_کرو EGL_VG_COLORSPACE_خطی_ثنائی_ہندسہ_KHR  0x0020
#تعریف_کرو EGL_VG_ALPHA_FORMAT_PRE_ثنائی_ہندسہ_KHR   0x0040
#اگر_ختم /* EGL_KHR_config_attribs */

#اگر_غیر_تعریف_شدہ EGL_KHR_context_flush_control
#تعریف_کرو EGL_KHR_context_flush_control 1
#تعریف_کرو EGL_CONTEXT_RELEASE_BEHAVIOR_NONE_KHR 0
#تعریف_کرو EGL_CONTEXT_RELEASE_BEHAVIOR_KHR  0x2097
#تعریف_کرو EGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_KHR 0x2098
#اگر_ختم /* EGL_KHR_context_flush_control */

#اگر_غیر_تعریف_شدہ EGL_KHR_create_context
#تعریف_کرو EGL_KHR_create_context 1
#تعریف_کرو EGL_CONTEXT_MAJOR_نسخہ_KHR     0x3098
#تعریف_کرو EGL_CONTEXT_MINOR_نسخہ_KHR     0x30FB
#تعریف_کرو EGL_CONTEXT_FLAGS_KHR             0x30FC
#تعریف_کرو EGL_CONTEXT_OPENGL_PROFILE_نقاب_KHR 0x30FD
#تعریف_کرو EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_KHR 0x31BD
#تعریف_کرو EGL_NO_RESET_NOTIFICATION_KHR     0x31BE
#تعریف_کرو EGL_LOSE_CONTEXT_ON_RESET_KHR     0x31BF
#تعریف_کرو EGL_CONTEXT_OPENGL_DEBUG_ثنائی_ہندسہ_KHR  0x00000001
#تعریف_کرو EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_ثنائی_ہندسہ_KHR 0x00000002
#تعریف_کرو EGL_CONTEXT_OPENGL_ROBUST_ACCESS_ثنائی_ہندسہ_KHR 0x00000004
#تعریف_کرو EGL_CONTEXT_OPENGL_CORE_PROFILE_ثنائی_ہندسہ_KHR 0x00000001
#تعریف_کرو EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_ثنائی_ہندسہ_KHR 0x00000002
#تعریف_کرو EGL_OPENGL_ES3_ثنائی_ہندسہ_KHR            0x00000040
#اگر_ختم /* EGL_KHR_create_context */

#اگر_غیر_تعریف_شدہ EGL_KHR_create_context_no_error
#تعریف_کرو EGL_KHR_create_context_no_error 1
#تعریف_کرو EGL_CONTEXT_OPENGL_NO_ERROR_KHR   0x31B3
#اگر_ختم /* EGL_KHR_create_context_no_error */

#اگر_غیر_تعریف_شدہ EGL_KHR_debug
#تعریف_کرو EGL_KHR_debug 1
قسمتعریف خالی *EGLLabelKHR;
قسمتعریف خالی *EGLObjectKHR;
قسمتعریف خالی (EGLAPIENTRY  *EGLDEBUGPROCKHR)(EGLenum error,ثابت حرف *command,EGLint پیغام_Type,EGLLabelKHR threadLabel,EGLLabelKHR objectLabel,ثابت حرف* پیغام);
#تعریف_کرو EGL_OBJECT_THREAD_KHR             0x33B0
#تعریف_کرو EGL_OBJECT_DISPLAY_KHR            0x33B1
#تعریف_کرو EGL_OBJECT_CONTEXT_KHR            0x33B2
#تعریف_کرو EGL_OBJECT_SURFACE_KHR            0x33B3
#تعریف_کرو EGL_OBJECT_IMAGE_KHR              0x33B4
#تعریف_کرو EGL_OBJECT_SYNC_KHR               0x33B5
#تعریف_کرو EGL_OBJECT_دھارا_KHR             0x33B6
#تعریف_کرو EGL_DEBUG_پیغام_CRITICAL_KHR        0x33B9
#تعریف_کرو EGL_DEBUG_پیغام_ERROR_KHR           0x33BA
#تعریف_کرو EGL_DEBUG_پیغام_WARN_KHR            0x33BB
#تعریف_کرو EGL_DEBUG_پیغام_INFO_KHR            0x33BC
#تعریف_کرو EGL_DEBUG_CALLBACK_KHR            0x33B8
قسمتعریف EGLint (EGLAPIENTRYP PFNEGLDEBUGMESSAGECONTROLKHRPROC) (EGLDEBUGPROCKHR callback, ثابت EGLAttrib *attrib_list);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEBUGKHRPROC) (EGLint attribute, EGLAttrib *قدر);
قسمتعریف EGLint (EGLAPIENTRYP PFNEGLLABELOBJECTKHRPROC) (EGLDisplay display, EGLenum objectType, EGLObjectKHR object, EGLLabelKHR label);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLint EGLAPIENTRY egl_Debug_پیغام_Control_KHR (EGLDEBUGPROCKHR callback, ثابت EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDebugKHR (EGLint attribute, EGLAttrib *قدر);
EGLAPI EGLint EGLAPIENTRY eglLabelObjectKHR (EGLDisplay display, EGLenum objectType, EGLObjectKHR object, EGLLabelKHR label);
#اگر_ختم
#اگر_ختم /* EGL_KHR_debug */

#اگر_غیر_تعریف_شدہ EGL_KHR_display_reference
#تعریف_کرو EGL_KHR_display_reference 1
#تعریف_کرو EGL_TRACK_REFERENCES_KHR          0x3352
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDISPLAYATTRIBKHRPROC) (EGLDisplay dpy, EGLint name, EGLAttrib *قدر);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDisplayAttribKHR (EGLDisplay dpy, EGLint name, EGLAttrib *قدر);
#اگر_ختم
#اگر_ختم /* EGL_KHR_display_reference */

#اگر_غیر_تعریف_شدہ EGL_KHR_fence_sync
#تعریف_کرو EGL_KHR_fence_sync 1
قسمتعریف khronos_utime_nanoseconds_t EGLTimeKHR;
#اگر_تعریف_شدہ KHRONOS_SUPPORT_INT64
#تعریف_کرو EGL_SYNC_پیشگی_COMMANDS_COMPLETE_KHR 0x30F0
#تعریف_کرو EGL_SYNC_CONDITION_KHR            0x30F8
#تعریف_کرو EGL_SYNC_FENCE_KHR                0x30F9
قسمتعریف EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESYNCKHRPROC) (EGLDisplay dpy, EGLenum type, ثابت EGLint *attrib_list);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync);
قسمتعریف EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLGETSYNCATTRIBKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint attribute, EGLint *قدر);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncKHR EGLAPIENTRY eglCreateSyncKHR (EGLDisplay dpy, EGLenum type, ثابت EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySyncKHR (EGLDisplay dpy, EGLSyncKHR sync);
EGLAPI EGLint EGLAPIENTRY eglClientWaitSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);
EGLAPI EGLBoolean EGLAPIENTRY eglGetSyncAttribKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint attribute, EGLint *قدر);
#اگر_ختم
#اگر_ختم /* KHRONOS_SUPPORT_INT64 */
#اگر_ختم /* EGL_KHR_fence_sync */

#اگر_غیر_تعریف_شدہ EGL_KHR_get_all_proc_پتے
#تعریف_کرو EGL_KHR_get_all_proc_پتے 1
#اگر_ختم /* EGL_KHR_get_all_proc_addresses */

#اگر_غیر_تعریف_شدہ EGL_KHR_gl_colorspace
#تعریف_کرو EGL_KHR_gl_colorspace 1
#تعریف_کرو EGL_GL_COLORSPACE_KHR             0x309D
#تعریف_کرو EGL_GL_COLORSPACE_SRGB_KHR        0x3089
#تعریف_کرو EGL_GL_COLORSPACE_خطی_KHR      0x308A
#اگر_ختم /* EGL_KHR_gl_colorspace */

#اگر_غیر_تعریف_شدہ EGL_KHR_gl_renderbuffer_image
#تعریف_کرو EGL_KHR_gl_renderbuffer_image 1
#تعریف_کرو EGL_GL_RENDERBUFFER_KHR           0x30B9
#اگر_ختم /* EGL_KHR_gl_renderbuffer_image */

#اگر_غیر_تعریف_شدہ EGL_KHR_gl_texture_2D_image
#تعریف_کرو EGL_KHR_gl_texture_2D_image 1
#تعریف_کرو EGL_GL_TEXTURE_2D_KHR             0x30B1
#تعریف_کرو EGL_GL_TEXTURE_LEVEL_KHR          0x30BC
#اگر_ختم /* EGL_KHR_gl_texture_2D_image */

#اگر_غیر_تعریف_شدہ EGL_KHR_gl_texture_3D_image
#تعریف_کرو EGL_KHR_gl_texture_3D_image 1
#تعریف_کرو EGL_GL_TEXTURE_3D_KHR             0x30B2
#تعریف_کرو EGL_GL_TEXTURE_ZOFFSET_KHR        0x30BD
#اگر_ختم /* EGL_KHR_gl_texture_3D_image */

#اگر_غیر_تعریف_شدہ EGL_KHR_gl_texture_cubemap_image
#تعریف_کرو EGL_KHR_gl_texture_cubemap_image 1
#تعریف_کرو EGL_GL_TEXTURE_CUBE_MAP_مثبت_X_KHR 0x30B3
#تعریف_کرو EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_X_KHR 0x30B4
#تعریف_کرو EGL_GL_TEXTURE_CUBE_MAP_مثبت_Y_KHR 0x30B5
#تعریف_کرو EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_KHR 0x30B6
#تعریف_کرو EGL_GL_TEXTURE_CUBE_MAP_مثبت_Z_KHR 0x30B7
#تعریف_کرو EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_KHR 0x30B8
#اگر_ختم /* EGL_KHR_gl_texture_cubemap_image */

#اگر_غیر_تعریف_شدہ EGL_KHR_image
#تعریف_کرو EGL_KHR_image 1
قسمتعریف خالی *EGLImageKHR;
#تعریف_کرو EGL_NATIVE_PIXMAP_KHR             0x30B0
#تعریف_کرو EGL_NO_IMAGE_KHR                  EGL_CAST(EGLImageKHR,0)
قسمتعریف EGLImageKHR (EGLAPIENTRYP PFNEGLCREATEIMAGEKHRPROC) (EGLDisplay dpy, EGLContext ctx, EGLenum ہدف, EGLClient_بفر بفر_2, ثابت EGLint *attrib_list);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYIMAGEKHRPROC) (EGLDisplay dpy, EGLImageKHR image);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLImageKHR EGLAPIENTRY eglCreateImageKHR (EGLDisplay dpy, EGLContext ctx, EGLenum ہدف, EGLClient_بفر بفر_2, ثابت EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyImageKHR (EGLDisplay dpy, EGLImageKHR image);
#اگر_ختم
#اگر_ختم /* EGL_KHR_image */

#اگر_غیر_تعریف_شدہ EGL_KHR_image_بنیاد
#تعریف_کرو EGL_KHR_image_بنیاد 1
#تعریف_کرو EGL_IMAGE_PRESERVED_KHR           0x30D2
#اگر_ختم /* EGL_KHR_image_base */

#اگر_غیر_تعریف_شدہ EGL_KHR_image_pixmap
#تعریف_کرو EGL_KHR_image_pixmap 1
#اگر_ختم /* EGL_KHR_image_pixmap */

#اگر_غیر_تعریف_شدہ EGL_KHR_تالا_surface
#تعریف_کرو EGL_KHR_تالا_surface 1
#تعریف_کرو EGL_READ_SURFACE_ثنائی_ہندسہ_KHR          0x0001
#تعریف_کرو EGL_WRITE_SURFACE_ثنائی_ہندسہ_KHR         0x0002
#تعریف_کرو EGL_تالا_SURFACE_ثنائی_ہندسہ_KHR          0x0080
#تعریف_کرو EGL_OPTIMAL_FORMAT_ثنائی_ہندسہ_KHR        0x0100
#تعریف_کرو EGL_مطابقت_FORMAT_KHR              0x3043
#تعریف_کرو EGL_FORMAT_RGB_565_EXACT_KHR      0x30C0
#تعریف_کرو EGL_FORMAT_RGB_565_KHR            0x30C1
#تعریف_کرو EGL_FORMAT_RGBA_8888_EXACT_KHR    0x30C2
#تعریف_کرو EGL_FORMAT_RGBA_8888_KHR          0x30C3
#تعریف_کرو EGL_MAP_PRESERVE_PIXELS_KHR       0x30C4
#تعریف_کرو EGL_تالا_USAGE_HINT_KHR           0x30C5
#تعریف_کرو EGL_BITMAP_اشارہ_گر_KHR            0x30C6
#تعریف_کرو EGL_BITMAP_PITCH_KHR              0x30C7
#تعریف_کرو EGL_BITMAP_ORIGIN_KHR             0x30C8
#تعریف_کرو EGL_BITMAP_PIXEL_RED_انحراف_KHR   0x30C9
#تعریف_کرو EGL_BITMAP_PIXEL_GREEN_انحراف_KHR 0x30CA
#تعریف_کرو EGL_BITMAP_PIXEL_BLUE_انحراف_KHR  0x30CB
#تعریف_کرو EGL_BITMAP_PIXEL_ALPHA_انحراف_KHR 0x30CC
#تعریف_کرو EGL_BITMAP_PIXEL_LUMINANCE_انحراف_KHR 0x30CD
#تعریف_کرو EGL_زیریں_بایاں_KHR                0x30CE
#تعریف_کرو EGL_بالائی_بایاں_KHR                0x30CF
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLLOCKSURFACEKHRPROC) (EGLDisplay dpy, EGLSurface surface, ثابت EGLint *attrib_list);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLUNLOCKSURFACEKHRPROC) (EGLDisplay dpy, EGLSurface surface);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_تالا_Surface_KHR (EGLDisplay dpy, EGLSurface surface, ثابت EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglUnlockSurfaceKHR (EGLDisplay dpy, EGLSurface surface);
#اگر_ختم
#اگر_ختم /* EGL_KHR_lock_surface */

#اگر_غیر_تعریف_شدہ EGL_KHR_تالا_surface2
#تعریف_کرو EGL_KHR_تالا_surface2 1
#تعریف_کرو EGL_BITMAP_PIXEL_سائز_KHR         0x3110
#اگر_ختم /* EGL_KHR_lock_surface2 */

#اگر_غیر_تعریف_شدہ EGL_KHR_تالا_surface3
#تعریف_کرو EGL_KHR_تالا_surface3 1
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSURFACE64KHRPROC) (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLAttribKHR *قدر);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQuerySurface64KHR (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLAttribKHR *قدر);
#اگر_ختم
#اگر_ختم /* EGL_KHR_lock_surface3 */

#اگر_غیر_تعریف_شدہ EGL_KHR_mutable_render_بفر
#تعریف_کرو EGL_KHR_mutable_render_بفر 1
#تعریف_کرو EGL_MUTABLE_RENDER_بفر_ثنائی_ہندسہ_KHR 0x1000
#اگر_ختم /* EGL_KHR_mutable_render_buffer */

#اگر_غیر_تعریف_شدہ EGL_KHR_no_config_context
#تعریف_کرو EGL_KHR_no_config_context 1
#تعریف_کرو EGL_NO_CONFIG_KHR                 EGL_CAST(EGLConfig,0)
#اگر_ختم /* EGL_KHR_no_config_context */

#اگر_غیر_تعریف_شدہ EGL_KHR_partial_update
#تعریف_کرو EGL_KHR_partial_update 1
#تعریف_کرو EGL_بفر_AGE_KHR                0x313D
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLSETDAMAGEREGIONKHRPROC) (EGLDisplay dpy, EGLSurface surface, EGLint *rects, EGLint n_rects);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_سیٹ_Damage_Region_KHR (EGLDisplay dpy, EGLSurface surface, EGLint *rects, EGLint n_rects);
#اگر_ختم
#اگر_ختم /* EGL_KHR_partial_update */

#اگر_غیر_تعریف_شدہ EGL_KHR_platform_android
#تعریف_کرو EGL_KHR_platform_android 1
#تعریف_کرو EGL_PLATFORM_ANDROID_KHR          0x3141
#اگر_ختم /* EGL_KHR_platform_android */

#اگر_غیر_تعریف_شدہ EGL_KHR_platform_gbm
#تعریف_کرو EGL_KHR_platform_gbm 1
#تعریف_کرو EGL_PLATFORM_GBM_KHR              0x31D7
#اگر_ختم /* EGL_KHR_platform_gbm */

#اگر_غیر_تعریف_شدہ EGL_KHR_platform_wayland
#تعریف_کرو EGL_KHR_platform_wayland 1
#تعریف_کرو EGL_PLATFORM_WAYLAND_KHR          0x31D8
#اگر_ختم /* EGL_KHR_platform_wayland */

#اگر_غیر_تعریف_شدہ EGL_KHR_platform_x11
#تعریف_کرو EGL_KHR_platform_x11 1
#تعریف_کرو EGL_PLATFORM_X11_KHR              0x31D5
#تعریف_کرو EGL_PLATFORM_X11_SCREEN_KHR       0x31D6
#اگر_ختم /* EGL_KHR_platform_x11 */

#اگر_غیر_تعریف_شدہ EGL_KHR_reusable_sync
#تعریف_کرو EGL_KHR_reusable_sync 1
#اگر_تعریف_شدہ KHRONOS_SUPPORT_INT64
#تعریف_کرو EGL_SYNC_حالت_KHR               0x30F1
#تعریف_کرو EGL_SIGNALED_KHR                  0x30F2
#تعریف_کرو EGL_UNSIGNALED_KHR                0x30F3
#تعریف_کرو EGL_TIMEOUT_EXPIRED_KHR           0x30F5
#تعریف_کرو EGL_CONDITION_SATISFIED_KHR       0x30F6
#تعریف_کرو EGL_SYNC_TYPE_KHR                 0x30F7
#تعریف_کرو EGL_SYNC_REUSABLE_KHR             0x30FA
#تعریف_کرو EGL_SYNC_FLUSH_COMMANDS_ثنائی_ہندسہ_KHR   0x0001
#تعریف_کرو EGL_FOREVER_KHR                   0xFFFFFFFFFFFFFFFFull
#تعریف_کرو EGL_NO_SYNC_KHR                   EGL_CAST(EGLSyncKHR,0)
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLSIGNALSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLenum منوال);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglSignalSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLenum منوال);
#اگر_ختم
#اگر_ختم /* KHRONOS_SUPPORT_INT64 */
#اگر_ختم /* EGL_KHR_reusable_sync */

#اگر_غیر_تعریف_شدہ EGL_KHR_دھارا
#تعریف_کرو EGL_KHR_دھارا 1
قسمتعریف خالی *EGLStreamKHR;
قسمتعریف khronos_uint64_t EGLuint64KHR;
#اگر_تعریف_شدہ KHRONOS_SUPPORT_INT64
#تعریف_کرو EGL_NO_دھارا_KHR                 EGL_CAST(EGLStreamKHR,0)
#تعریف_کرو EGL_صارف_LATENCY_USEC_KHR     0x3210
#تعریف_کرو EGL_پیداکار_چوکھٹا_KHR            0x3212
#تعریف_کرو EGL_صارف_چوکھٹا_KHR            0x3213
#تعریف_کرو EGL_دھارا_STATE_KHR              0x3214
#تعریف_کرو EGL_دھارا_STATE_CREATED_KHR      0x3215
#تعریف_کرو EGL_دھارا_STATE_CONNECTING_KHR   0x3216
#تعریف_کرو EGL_دھارا_STATE_خالی_خانے_KHR        0x3217
#تعریف_کرو EGL_دھارا_STATE_NEW_چوکھٹا_دستیاب_KHR 0x3218
#تعریف_کرو EGL_دھارا_STATE_OLD_چوکھٹا_دستیاب_KHR 0x3219
#تعریف_کرو EGL_دھارا_STATE_DISCONNECTED_KHR 0x321A
#تعریف_کرو EGL_BAD_دھارا_KHR                0x321B
#تعریف_کرو EGL_BAD_STATE_KHR                 0x321C
قسمتعریف EGLStreamKHR (EGLAPIENTRYP PFNEGLCREATESTREAMKHRPROC) (EGLDisplay dpy, ثابت EGLint *attrib_list);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSTREAMKHRPROC) (EGLDisplay dpy, EGLStreamKHR دھارا);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR دھارا, EGLenum attribute, EGLint قدر);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMKHRPROC) (EGLDisplay dpy, EGLStreamKHR دھارا, EGLenum attribute, EGLint *قدر);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMU64KHRPROC) (EGLDisplay dpy, EGLStreamKHR دھارا, EGLenum attribute, EGLuint64KHR *قدر);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLStreamKHR EGLAPIENTRY egl_Create_دھارا_KHR (EGLDisplay dpy, ثابت EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY egl_Destroy_دھارا_KHR (EGLDisplay dpy, EGLStreamKHR دھارا);
EGLAPI EGLBoolean EGLAPIENTRY egl_دھارا_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR دھارا, EGLenum attribute, EGLint قدر);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_دھارا_KHR (EGLDisplay dpy, EGLStreamKHR دھارا, EGLenum attribute, EGLint *قدر);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryStreamu64KHR (EGLDisplay dpy, EGLStreamKHR دھارا, EGLenum attribute, EGLuint64KHR *قدر);
#اگر_ختم
#اگر_ختم /* KHRONOS_SUPPORT_INT64 */
#اگر_ختم /* EGL_KHR_stream */

#اگر_غیر_تعریف_شدہ EGL_KHR_دھارا_attrib
#تعریف_کرو EGL_KHR_دھارا_attrib 1
#اگر_تعریف_شدہ KHRONOS_SUPPORT_INT64
قسمتعریف EGLStreamKHR (EGLAPIENTRYP PFNEGLCREATESTREAMATTRIBKHRPROC) (EGLDisplay dpy, ثابت EGLAttrib *attrib_list);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLSETSTREAMATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR دھارا, EGLenum attribute, EGLAttrib قدر);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR دھارا, EGLenum attribute, EGLAttrib *قدر);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERACQUIREATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR دھارا, ثابت EGLAttrib *attrib_list);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERRELEASEATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR دھارا, ثابت EGLAttrib *attrib_list);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLStreamKHR EGLAPIENTRY egl_Create_دھارا_Attrib_KHR (EGLDisplay dpy, ثابت EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY egl_سیٹ_دھارا_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR دھارا, EGLenum attribute, EGLAttrib قدر);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_دھارا_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR دھارا, EGLenum attribute, EGLAttrib *قدر);
EGLAPI EGLBoolean EGLAPIENTRY egl_دھارا_صارف_Acquire_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR دھارا, ثابت EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY egl_دھارا_صارف_Release_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR دھارا, ثابت EGLAttrib *attrib_list);
#اگر_ختم
#اگر_ختم /* KHRONOS_SUPPORT_INT64 */
#اگر_ختم /* EGL_KHR_stream_attrib */

#اگر_غیر_تعریف_شدہ EGL_KHR_دھارا_صارف_gltexture
#تعریف_کرو EGL_KHR_دھارا_صارف_gltexture 1
#اگر_تعریف_شدہ EGL_KHR_دھارا
#تعریف_کرو EGL_صارف_ACQUIRE_TIMEOUT_USEC_KHR 0x321E
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALKHRPROC) (EGLDisplay dpy, EGLStreamKHR دھارا);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERACQUIREKHRPROC) (EGLDisplay dpy, EGLStreamKHR دھارا);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERRELEASEKHRPROC) (EGLDisplay dpy, EGLStreamKHR دھارا);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_دھارا_صارف_GLTexture_External_KHR (EGLDisplay dpy, EGLStreamKHR دھارا);
EGLAPI EGLBoolean EGLAPIENTRY egl_دھارا_صارف_Acquire_KHR (EGLDisplay dpy, EGLStreamKHR دھارا);
EGLAPI EGLBoolean EGLAPIENTRY egl_دھارا_صارف_Release_KHR (EGLDisplay dpy, EGLStreamKHR دھارا);
#اگر_ختم
#اگر_ختم /* EGL_KHR_stream */
#اگر_ختم /* EGL_KHR_stream_consumer_gltexture */

#اگر_غیر_تعریف_شدہ EGL_KHR_دھارا_cross_process_fd
#تعریف_کرو EGL_KHR_دھارا_cross_process_fd 1
قسمتعریف صحیح EGLNativeFileDescriptorKHR;
#اگر_تعریف_شدہ EGL_KHR_دھارا
#تعریف_کرو EGL_NO_FILE_DESCRIPTOR_KHR        EGL_CAST(EGLNativeFileDescriptorKHR,-1)
قسمتعریف EGLNativeFileDescriptorKHR (EGLAPIENTRYP PFNEGLGETSTREAMFILEDESCRIPTORKHRPROC) (EGLDisplay dpy, EGLStreamKHR دھارا);
قسمتعریف EGLStreamKHR (EGLAPIENTRYP PFNEGLCREATESTREAMFROMFILEDESCRIPTORKHRPROC) (EGLDisplay dpy, EGLNativeFileDescriptorKHR file_descriptor);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLNativeFileDescriptorKHR EGLAPIENTRY egl_Get_دھارا_File_Descriptor_KHR (EGLDisplay dpy, EGLStreamKHR دھارا);
EGLAPI EGLStreamKHR EGLAPIENTRY egl_Create_دھارا_From_File_Descriptor_KHR (EGLDisplay dpy, EGLNativeFileDescriptorKHR file_descriptor);
#اگر_ختم
#اگر_ختم /* EGL_KHR_stream */
#اگر_ختم /* EGL_KHR_stream_cross_process_fd */

#اگر_غیر_تعریف_شدہ EGL_KHR_دھارا_fifo
#تعریف_کرو EGL_KHR_دھارا_fifo 1
#اگر_تعریف_شدہ EGL_KHR_دھارا
#تعریف_کرو EGL_دھارا_FIFO_لمبائی_KHR        0x31FC
#تعریف_کرو EGL_دھارا_وقت_NOW_KHR           0x31FD
#تعریف_کرو EGL_دھارا_وقت_صارف_KHR      0x31FE
#تعریف_کرو EGL_دھارا_وقت_پیداکار_KHR      0x31FF
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMTIMEKHRPROC) (EGLDisplay dpy, EGLStreamKHR دھارا, EGLenum attribute, EGLTimeKHR *قدر);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_دھارا_وقت_KHR (EGLDisplay dpy, EGLStreamKHR دھارا, EGLenum attribute, EGLTimeKHR *قدر);
#اگر_ختم
#اگر_ختم /* EGL_KHR_stream */
#اگر_ختم /* EGL_KHR_stream_fifo */

#اگر_غیر_تعریف_شدہ EGL_KHR_دھارا_پیداکار_aldatalocator
#تعریف_کرو EGL_KHR_دھارا_پیداکار_aldatalocator 1
#اگر_تعریف_شدہ EGL_KHR_دھارا
#اگر_ختم /* EGL_KHR_stream */
#اگر_ختم /* EGL_KHR_stream_producer_aldatalocator */

#اگر_غیر_تعریف_شدہ EGL_KHR_دھارا_پیداکار_eglsurface
#تعریف_کرو EGL_KHR_دھارا_پیداکار_eglsurface 1
#اگر_تعریف_شدہ EGL_KHR_دھارا
#تعریف_کرو EGL_دھارا_ثنائی_ہندسہ_KHR                0x0800
قسمتعریف EGLSurface (EGLAPIENTRYP PFNEGLCREATESTREAMPRODUCERSURFACEKHRPROC) (EGLDisplay dpy, EGLConfig config, EGLStreamKHR دھارا, ثابت EGLint *attrib_list);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSurface EGLAPIENTRY egl_Create_دھارا_پیداکار_Surface_KHR (EGLDisplay dpy, EGLConfig config, EGLStreamKHR دھارا, ثابت EGLint *attrib_list);
#اگر_ختم
#اگر_ختم /* EGL_KHR_stream */
#اگر_ختم /* EGL_KHR_stream_producer_eglsurface */

#اگر_غیر_تعریف_شدہ EGL_KHR_surfaceless_context
#تعریف_کرو EGL_KHR_surfaceless_context 1
#اگر_ختم /* EGL_KHR_surfaceless_context */

#اگر_غیر_تعریف_شدہ EGL_KHR_تبادلہ_buffers_with_damage
#تعریف_کرو EGL_KHR_تبادلہ_buffers_with_damage 1
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSWITHDAMAGEKHRPROC) (EGLDisplay dpy, EGLSurface surface, ثابت EGLint *rects, EGLint n_rects);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_تبادلہ_Buffers_With_Damage_KHR (EGLDisplay dpy, EGLSurface surface, ثابت EGLint *rects, EGLint n_rects);
#اگر_ختم
#اگر_ختم /* EGL_KHR_swap_buffers_with_damage */

#اگر_غیر_تعریف_شدہ EGL_KHR_vg_والد_image
#تعریف_کرو EGL_KHR_vg_والد_image 1
#تعریف_کرو EGL_VG_والد_IMAGE_KHR           0x30BA
#اگر_ختم /* EGL_KHR_vg_parent_image */

#اگر_غیر_تعریف_شدہ EGL_KHR_wait_sync
#تعریف_کرو EGL_KHR_wait_sync 1
قسمتعریف EGLint (EGLAPIENTRYP PFNEGLWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLint EGLAPIENTRY eglWaitSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
#اگر_ختم
#اگر_ختم /* EGL_KHR_wait_sync */

#اگر_غیر_تعریف_شدہ EGL_ANDROID_GLES_layers
#تعریف_کرو EGL_ANDROID_GLES_layers 1
#اگر_ختم /* EGL_ANDROID_GLES_layers */

#اگر_غیر_تعریف_شدہ EGL_ANDROID_blob_cache
#تعریف_کرو EGL_ANDROID_blob_cache 1
قسمتعریف khronos_ssize_t EGLsizeiANDROID;
قسمتعریف خالی (*EGLSetBlobFuncANDROID) (ثابت خالی *کلید, EGLsizeiANDROID کلید_سائز_2, ثابت خالی *قدر, EGLsizeiANDROID قدر_سائز_2);
قسمتعریف EGLsizeiANDROID (*EGLGetBlobFuncANDROID) (ثابت خالی *کلید, EGLsizeiANDROID کلید_سائز_2, خالی *قدر, EGLsizeiANDROID قدر_سائز_2);
قسمتعریف خالی (EGLAPIENTRYP PFNEGLSETBLOBCACHEFUNCSANDROIDPROC) (EGLDisplay dpy, EGLSetBlobFuncANDROID سیٹ, EGLGetBlobFuncANDROID get);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI خالی EGLAPIENTRY egl_سیٹ_Blob_Cache_Funcs_ANDROID (EGLDisplay dpy, EGLSetBlobFuncANDROID سیٹ, EGLGetBlobFuncANDROID get);
#اگر_ختم
#اگر_ختم /* EGL_ANDROID_blob_cache */

#اگر_غیر_تعریف_شدہ EGL_ANDROID_create_native_client_بفر
#تعریف_کرو EGL_ANDROID_create_native_client_بفر 1
#تعریف_کرو EGL_NATIVE_بفر_USAGE_ANDROID   0x3143
#تعریف_کرو EGL_NATIVE_بفر_USAGE_PROTECTED_ثنائی_ہندسہ_ANDROID 0x00000001
#تعریف_کرو EGL_NATIVE_بفر_USAGE_RENDERBUFFER_ثنائی_ہندسہ_ANDROID 0x00000002
#تعریف_کرو EGL_NATIVE_بفر_USAGE_TEXTURE_ثنائی_ہندسہ_ANDROID 0x00000004
قسمتعریف EGLClient_بفر (EGLAPIENTRYP PFNEGLCREATENATIVECLIENTBUFFERANDROIDPROC) (ثابت EGLint *attrib_list);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLClient_بفر EGLAPIENTRY egl_Create_Native_Client_بفر_ANDROID (ثابت EGLint *attrib_list);
#اگر_ختم
#اگر_ختم /* EGL_ANDROID_create_native_client_buffer */

#اگر_غیر_تعریف_شدہ EGL_ANDROID_framebuffer_ہدف
#تعریف_کرو EGL_ANDROID_framebuffer_ہدف 1
#تعریف_کرو EGL_FRAMEBUFFER_ہدف_ANDROID    0x3147
#اگر_ختم /* EGL_ANDROID_framebuffer_target */

#اگر_غیر_تعریف_شدہ EGL_ANDROID_front_بفر_auto_refresh
#تعریف_کرو EGL_ANDROID_front_بفر_auto_refresh 1
#تعریف_کرو EGL_FRONT_بفر_AUTO_REFRESH_ANDROID 0x314C
#اگر_ختم /* EGL_ANDROID_front_buffer_auto_refresh */

#اگر_غیر_تعریف_شدہ EGL_ANDROID_get_چوکھٹا_timestamps
#تعریف_کرو EGL_ANDROID_get_چوکھٹا_timestamps 1
قسمتعریف khronos_stime_nanoseconds_t EGLnsecsANDROID;
#تعریف_کرو EGL_TIMESTAMP_PENDING_ANDROID     EGL_CAST(EGLnsecsANDROID,-2)
#تعریف_کرو EGL_TIMESTAMP_INVALID_ANDROID     EGL_CAST(EGLnsecsANDROID,-1)
#تعریف_کرو EGL_TIMESTAMPS_ANDROID            0x3430
#تعریف_کرو EGL_مرکب_DEADLINE_ANDROID    0x3431
#تعریف_کرو EGL_مرکب_INTERVAL_ANDROID    0x3432
#تعریف_کرو EGL_مرکب_مقصد_PRESENT_LATENCY_ANDROID 0x3433
#تعریف_کرو EGL_REQUESTED_PRESENT_وقت_ANDROID 0x3434
#تعریف_کرو EGL_RENDERING_COMPLETE_وقت_ANDROID 0x3435
#تعریف_کرو EGL_COMPOSITION_LATCH_وقت_ANDROID 0x3436
#تعریف_کرو EGL_پہلا_COMPOSITION_آغاز_وقت_ANDROID 0x3437
#تعریف_کرو EGL_آخری_COMPOSITION_آغاز_وقت_ANDROID 0x3438
#تعریف_کرو EGL_پہلا_COMPOSITION_GPU_ختم_شدہ_وقت_ANDROID 0x3439
#تعریف_کرو EGL_DISPLAY_PRESENT_وقت_ANDROID  0x343A
#تعریف_کرو EGL_قطار_سے_نکالو_READY_وقت_ANDROID    0x343B
#تعریف_کرو EGL_READS_مکمل_وقت_ANDROID       0x343C
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLGETCOMPOSITORTIMINGSUPPORTEDANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLint name);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLGETCOMPOSITORTIMINGANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLint عدد_Timestamps,  ثابت EGLint *نام, EGLnsecsANDROID *اقدار);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLGETNEXTFRAMEIDANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR *چوکھٹا_Id);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLGETFRAMETIMESTAMPSUPPORTEDANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLint timestamp);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLGETFRAMETIMESTAMPSANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR چوکھٹا_Id, EGLint عدد_Timestamps,  ثابت EGLint *timestamps, EGLnsecsANDROID *اقدار);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglGetCompositorTimingSupportedANDROID (EGLDisplay dpy, EGLSurface surface, EGLint name);
EGLAPI EGLBoolean EGLAPIENTRY eglGetCompositorTimingANDROID (EGLDisplay dpy, EGLSurface surface, EGLint عدد_Timestamps,  ثابت EGLint *نام, EGLnsecsANDROID *اقدار);
EGLAPI EGLBoolean EGLAPIENTRY egl_Get_اگلا_چوکھٹا_Id_ANDROID (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR *چوکھٹا_Id);
EGLAPI EGLBoolean EGLAPIENTRY egl_Get_چوکھٹا_Timestamp_Supported_ANDROID (EGLDisplay dpy, EGLSurface surface, EGLint timestamp);
EGLAPI EGLBoolean EGLAPIENTRY egl_Get_چوکھٹا_Timestamps_ANDROID (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR چوکھٹا_Id, EGLint عدد_Timestamps,  ثابت EGLint *timestamps, EGLnsecsANDROID *اقدار);
#اگر_ختم
#اگر_ختم /* EGL_ANDROID_get_frame_timestamps */

#اگر_غیر_تعریف_شدہ EGL_ANDROID_get_native_client_بفر
#تعریف_کرو EGL_ANDROID_get_native_client_بفر 1
ساخت AHardware_بفر;
قسمتعریف EGLClient_بفر (EGLAPIENTRYP PFNEGLGETNATIVECLIENTBUFFERANDROIDPROC) (ثابت ساخت AHardware_بفر *بفر_2);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLClient_بفر EGLAPIENTRY egl_Get_Native_Client_بفر_ANDROID (ثابت ساخت AHardware_بفر *بفر_2);
#اگر_ختم
#اگر_ختم /* EGL_ANDROID_get_native_client_buffer */

#اگر_غیر_تعریف_شدہ EGL_ANDROID_image_native_بفر
#تعریف_کرو EGL_ANDROID_image_native_بفر 1
#تعریف_کرو EGL_NATIVE_بفر_ANDROID         0x3140
#اگر_ختم /* EGL_ANDROID_image_native_buffer */

#اگر_غیر_تعریف_شدہ EGL_ANDROID_native_fence_sync
#تعریف_کرو EGL_ANDROID_native_fence_sync 1
#تعریف_کرو EGL_SYNC_NATIVE_FENCE_ANDROID     0x3144
#تعریف_کرو EGL_SYNC_NATIVE_FENCE_FD_ANDROID  0x3145
#تعریف_کرو EGL_SYNC_NATIVE_FENCE_SIGNALED_ANDROID 0x3146
#تعریف_کرو EGL_NO_NATIVE_FENCE_FD_ANDROID    -1
قسمتعریف EGLint (EGLAPIENTRYP PFNEGLDUPNATIVEFENCEFDANDROIDPROC) (EGLDisplay dpy, EGLSyncKHR sync);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLint EGLAPIENTRY eglDupNativeFenceFDANDROID (EGLDisplay dpy, EGLSyncKHR sync);
#اگر_ختم
#اگر_ختم /* EGL_ANDROID_native_fence_sync */

#اگر_غیر_تعریف_شدہ EGL_ANDROID_presentation_وقت
#تعریف_کرو EGL_ANDROID_presentation_وقت 1
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLPRESENTATIONTIMEANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLnsecsANDROID وقت);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Presentation_وقت_ANDROID (EGLDisplay dpy, EGLSurface surface, EGLnsecsANDROID وقت);
#اگر_ختم
#اگر_ختم /* EGL_ANDROID_presentation_time */

#اگر_غیر_تعریف_شدہ EGL_ANDROID_recordable
#تعریف_کرو EGL_ANDROID_recordable 1
#تعریف_کرو EGL_RECORDABLE_ANDROID            0x3142
#اگر_ختم /* EGL_ANDROID_recordable */

#اگر_غیر_تعریف_شدہ EGL_ANDROID_telemetry_hint
#تعریف_کرو EGL_ANDROID_telemetry_hint 1
#تعریف_کرو EGL_TELEMETRY_HINT_ANDROID        0x3570
#اگر_ختم /* EGL_ANDROID_telemetry_hint */

#اگر_غیر_تعریف_شدہ EGL_ANGLE_d3d_share_handle_client_بفر
#تعریف_کرو EGL_ANGLE_d3d_share_handle_client_بفر 1
#تعریف_کرو EGL_D3D_TEXTURE_2D_SHARE_HANDLE_ANGLE 0x3200
#اگر_ختم /* EGL_ANGLE_d3d_share_handle_client_buffer */

#اگر_غیر_تعریف_شدہ EGL_ANGLE_device_d3d
#تعریف_کرو EGL_ANGLE_device_d3d 1
#تعریف_کرو EGL_D3D9_DEVICE_ANGLE             0x33A0
#تعریف_کرو EGL_D3D11_DEVICE_ANGLE            0x33A1
#اگر_ختم /* EGL_ANGLE_device_d3d */

#اگر_غیر_تعریف_شدہ EGL_ANGLE_query_surface_اشارہ_گر
#تعریف_کرو EGL_ANGLE_query_surface_اشارہ_گر 1
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSURFACEPOINTERANGLEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint attribute, خالی **قدر);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Surface_اشارہ_گر_ANGLE (EGLDisplay dpy, EGLSurface surface, EGLint attribute, خالی **قدر);
#اگر_ختم
#اگر_ختم /* EGL_ANGLE_query_surface_pointer */

#اگر_غیر_تعریف_شدہ EGL_ANGLE_surface_d3d_texture_2d_share_handle
#تعریف_کرو EGL_ANGLE_surface_d3d_texture_2d_share_handle 1
#اگر_ختم /* EGL_ANGLE_surface_d3d_texture_2d_share_handle */

#اگر_غیر_تعریف_شدہ EGL_ANGLE_sync_control_شرح
#تعریف_کرو EGL_ANGLE_sync_control_شرح 1
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLGETMSCRATEANGLEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint *numerator, EGLint *denominator);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Get_Msc_شرح_ANGLE (EGLDisplay dpy, EGLSurface surface, EGLint *numerator, EGLint *denominator);
#اگر_ختم
#اگر_ختم /* EGL_ANGLE_sync_control_rate */

#اگر_غیر_تعریف_شدہ EGL_ANGLE_کھڑکی_fixed_سائز
#تعریف_کرو EGL_ANGLE_کھڑکی_fixed_سائز 1
#تعریف_کرو EGL_FIXED_سائز_ANGLE              0x3201
#اگر_ختم /* EGL_ANGLE_window_fixed_size */

#اگر_غیر_تعریف_شدہ EGL_ARM_image_format
#تعریف_کرو EGL_ARM_image_format 1
#تعریف_کرو EGL_COLOR_COMPONENT_TYPE_UNSIGNED_INTEGER_ARM 0x3287
#تعریف_کرو EGL_COLOR_COMPONENT_TYPE_INTEGER_ARM 0x3288
#اگر_ختم /* EGL_ARM_image_format */

#اگر_غیر_تعریف_شدہ EGL_ARM_implicit_external_sync
#تعریف_کرو EGL_ARM_implicit_external_sync 1
#تعریف_کرو EGL_SYNC_پیشگی_COMMANDS_IMPLICIT_EXTERNAL_ARM 0x328A
#اگر_ختم /* EGL_ARM_implicit_external_sync */

#اگر_غیر_تعریف_شدہ EGL_ARM_pixmap_multisample_discard
#تعریف_کرو EGL_ARM_pixmap_multisample_discard 1
#تعریف_کرو EGL_DISCARD_SAMPLES_ARM           0x3286
#اگر_ختم /* EGL_ARM_pixmap_multisample_discard */

#اگر_غیر_تعریف_شدہ EGL_EXT_bind_مقصد_front
#تعریف_کرو EGL_EXT_bind_مقصد_front 1
#تعریف_کرو EGL_FRONT_بفر_EXT              0x3464
#اگر_ختم /* EGL_EXT_bind_to_front */

#اگر_غیر_تعریف_شدہ EGL_EXT_بفر_age
#تعریف_کرو EGL_EXT_بفر_age 1
#تعریف_کرو EGL_بفر_AGE_EXT                0x313D
#اگر_ختم /* EGL_EXT_buffer_age */

#اگر_غیر_تعریف_شدہ EGL_EXT_client_extensions
#تعریف_کرو EGL_EXT_client_extensions 1
#اگر_ختم /* EGL_EXT_client_extensions */

#اگر_غیر_تعریف_شدہ EGL_EXT_client_sync
#تعریف_کرو EGL_EXT_client_sync 1
#تعریف_کرو EGL_SYNC_CLIENT_EXT               0x3364
#تعریف_کرو EGL_SYNC_CLIENT_SIGNAL_EXT        0x3365
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLCLIENTSIGNALSYNCEXTPROC) (EGLDisplay dpy, EGLSync sync, ثابت EGLAttrib *attrib_list);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglClientSignalSyncEXT (EGLDisplay dpy, EGLSync sync, ثابت EGLAttrib *attrib_list);
#اگر_ختم
#اگر_ختم /* EGL_EXT_client_sync */

#اگر_غیر_تعریف_شدہ EGL_EXT_compositor
#تعریف_کرو EGL_EXT_compositor 1
#تعریف_کرو EGL_PRIMARY_COMPOSITOR_CONTEXT_EXT 0x3460
#تعریف_کرو EGL_EXTERNAL_REF_ID_EXT           0x3461
#تعریف_کرو EGL_COMPOSITOR_DROP_NEWEST_چوکھٹا_EXT 0x3462
#تعریف_کرو EGL_COMPOSITOR_KEEP_NEWEST_چوکھٹا_EXT 0x3463
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETCONTEXTLISTEXTPROC) (ثابت EGLint *external_ref_ids, EGLint عدد_entries);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETCONTEXTATTRIBUTESEXTPROC) (EGLint external_ref_id, ثابت EGLint *context_اوصاف, EGLint عدد_entries);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETWINDOWLISTEXTPROC) (EGLint external_ref_id, ثابت EGLint *external_win_ids, EGLint عدد_entries);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETWINDOWATTRIBUTESEXTPROC) (EGLint external_win_id, ثابت EGLint *کھڑکی_اوصاف, EGLint عدد_entries);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORBINDTEXWINDOWEXTPROC) (EGLint external_win_id);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETSIZEEXTPROC) (EGLint external_win_id, EGLint چوڑائی, EGLint اونچائی);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSWAPPOLICYEXTPROC) (EGLint external_win_id, EGLint policy);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_سیٹ_Context_List_EXT (ثابت EGLint *external_ref_ids, EGLint عدد_entries);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_سیٹ_Context_اوصاف_EXT (EGLint external_ref_id, ثابت EGLint *context_اوصاف, EGLint عدد_entries);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_سیٹ_کھڑکی_List_EXT (EGLint external_ref_id, ثابت EGLint *external_win_ids, EGLint عدد_entries);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_سیٹ_کھڑکی_اوصاف_EXT (EGLint external_win_id, ثابت EGLint *کھڑکی_اوصاف, EGLint عدد_entries);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_Bind_Tex_کھڑکی_EXT (EGLint external_win_id);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_سیٹ_سائز_EXT (EGLint external_win_id, EGLint چوڑائی, EGLint اونچائی);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_تبادلہ_Policy_EXT (EGLint external_win_id, EGLint policy);
#اگر_ختم
#اگر_ختم /* EGL_EXT_compositor */

#اگر_غیر_تعریف_شدہ EGL_EXT_config_select_گروہ
#تعریف_کرو EGL_EXT_config_select_گروہ 1
#تعریف_کرو EGL_CONFIG_SELECT_گروہ_EXT       0x34C0
#اگر_ختم /* EGL_EXT_config_select_group */

#اگر_غیر_تعریف_شدہ EGL_EXT_create_context_robustness
#تعریف_کرو EGL_EXT_create_context_robustness 1
#تعریف_کرو EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT 0x30BF
#تعریف_کرو EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_EXT 0x3138
#تعریف_کرو EGL_NO_RESET_NOTIFICATION_EXT     0x31BE
#تعریف_کرو EGL_LOSE_CONTEXT_ON_RESET_EXT     0x31BF
#اگر_ختم /* EGL_EXT_create_context_robustness */

#اگر_غیر_تعریف_شدہ EGL_EXT_device_بنیاد
#تعریف_کرو EGL_EXT_device_بنیاد 1
قسمتعریف خالی *EGLDeviceEXT;
#تعریف_کرو EGL_NO_DEVICE_EXT                 EGL_CAST(EGLDeviceEXT,0)
#تعریف_کرو EGL_BAD_DEVICE_EXT                0x322B
#تعریف_کرو EGL_DEVICE_EXT                    0x322C
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICEATTRIBEXTPROC) (EGLDeviceEXT device, EGLint attribute, EGLAttrib *قدر);
قسمتعریف ثابت حرف *(EGLAPIENTRYP PFNEGLQUERYDEVICESTRINGEXTPROC) (EGLDeviceEXT device, EGLint name);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICESEXTPROC) (EGLint max_devices, EGLDeviceEXT *devices, EGLint *عدد_devices);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDISPLAYATTRIBEXTPROC) (EGLDisplay dpy, EGLint attribute, EGLAttrib *قدر);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDeviceAttribEXT (EGLDeviceEXT device, EGLint attribute, EGLAttrib *قدر);
EGLAPI ثابت حرف *EGLAPIENTRY eglQueryDeviceStringEXT (EGLDeviceEXT device, EGLint name);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDevicesEXT (EGLint max_devices, EGLDeviceEXT *devices, EGLint *عدد_devices);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDisplayAttribEXT (EGLDisplay dpy, EGLint attribute, EGLAttrib *قدر);
#اگر_ختم
#اگر_ختم /* EGL_EXT_device_base */

#اگر_غیر_تعریف_شدہ EGL_EXT_device_drm
#تعریف_کرو EGL_EXT_device_drm 1
#تعریف_کرو EGL_DRM_DEVICE_FILE_EXT           0x3233
#تعریف_کرو EGL_DRM_MASTER_FD_EXT             0x333C
#اگر_ختم /* EGL_EXT_device_drm */

#اگر_غیر_تعریف_شدہ EGL_EXT_device_drm_render_گرہ
#تعریف_کرو EGL_EXT_device_drm_render_گرہ 1
#تعریف_کرو EGL_DRM_RENDER_گرہ_FILE_EXT      0x3377
#اگر_ختم /* EGL_EXT_device_drm_render_node */

#اگر_غیر_تعریف_شدہ EGL_EXT_device_enumeration
#تعریف_کرو EGL_EXT_device_enumeration 1
#اگر_ختم /* EGL_EXT_device_enumeration */

#اگر_غیر_تعریف_شدہ EGL_EXT_device_openwf
#تعریف_کرو EGL_EXT_device_openwf 1
#تعریف_کرو EGL_OPENWF_DEVICE_ID_EXT          0x3237
#تعریف_کرو EGL_OPENWF_DEVICE_EXT             0x333D
#اگر_ختم /* EGL_EXT_device_openwf */

#اگر_غیر_تعریف_شدہ EGL_EXT_device_persistent_id
#تعریف_کرو EGL_EXT_device_persistent_id 1
#تعریف_کرو EGL_DEVICE_UUID_EXT               0x335C
#تعریف_کرو EGL_DRIVER_UUID_EXT               0x335D
#تعریف_کرو EGL_DRIVER_NAME_EXT               0x335E
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICEBINARYEXTPROC) (EGLDeviceEXT device, EGLint name, EGLint max_سائز, خالی *قدر, EGLint *سائز);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Device_ثنائی_EXT (EGLDeviceEXT device, EGLint name, EGLint max_سائز, خالی *قدر, EGLint *سائز);
#اگر_ختم
#اگر_ختم /* EGL_EXT_device_persistent_id */

#اگر_غیر_تعریف_شدہ EGL_EXT_device_query
#تعریف_کرو EGL_EXT_device_query 1
#اگر_ختم /* EGL_EXT_device_query */

#اگر_غیر_تعریف_شدہ EGL_EXT_device_query_name
#تعریف_کرو EGL_EXT_device_query_name 1
#تعریف_کرو EGL_RENDERER_EXT                  0x335F
#اگر_ختم /* EGL_EXT_device_query_name */

#اگر_غیر_تعریف_شدہ EGL_EXT_device_type
#تعریف_کرو EGL_EXT_device_type 1
#تعریف_کرو EGL_DEVICE_TYPE_EXT               0x3590
#تعریف_کرو EGL_DEVICE_TYPE_OTHER_EXT         0x3591
#تعریف_کرو EGL_DEVICE_TYPE_INTEGRATED_GPU_EXT 0x3592
#تعریف_کرو EGL_DEVICE_TYPE_DISCRETE_GPU_EXT  0x3593
#تعریف_کرو EGL_DEVICE_TYPE_CPU_EXT           0x3594
#اگر_ختم /* EGL_EXT_device_type */

#اگر_غیر_تعریف_شدہ EGL_EXT_display_alloc
#تعریف_کرو EGL_EXT_display_alloc 1
#تعریف_کرو EGL_ALLOC_NEW_DISPLAY_EXT         0x3379
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYDISPLAYEXTPROC) (EGLDisplay dpy);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyDisplayEXT (EGLDisplay dpy);
#اگر_ختم
#اگر_ختم /* EGL_EXT_display_alloc */

#اگر_غیر_تعریف_شدہ EGL_EXT_explicit_device
#تعریف_کرو EGL_EXT_explicit_device 1
#اگر_ختم /* EGL_EXT_explicit_device */

#اگر_غیر_تعریف_شدہ EGL_EXT_gl_colorspace_bt2020_hlg
#تعریف_کرو EGL_EXT_gl_colorspace_bt2020_hlg 1
#تعریف_کرو EGL_GL_COLORSPACE_BT2020_HLG_EXT  0x3540
#اگر_ختم /* EGL_EXT_gl_colorspace_bt2020_hlg */

#اگر_غیر_تعریف_شدہ EGL_EXT_gl_colorspace_bt2020_خطی
#تعریف_کرو EGL_EXT_gl_colorspace_bt2020_خطی 1
#تعریف_کرو EGL_GL_COLORSPACE_BT2020_خطی_EXT 0x333F
#اگر_ختم /* EGL_EXT_gl_colorspace_bt2020_linear */

#اگر_غیر_تعریف_شدہ EGL_EXT_gl_colorspace_bt2020_pq
#تعریف_کرو EGL_EXT_gl_colorspace_bt2020_pq 1
#تعریف_کرو EGL_GL_COLORSPACE_BT2020_PQ_EXT   0x3340
#اگر_ختم /* EGL_EXT_gl_colorspace_bt2020_pq */

#اگر_غیر_تعریف_شدہ EGL_EXT_gl_colorspace_display_p3
#تعریف_کرو EGL_EXT_gl_colorspace_display_p3 1
#تعریف_کرو EGL_GL_COLORSPACE_DISPLAY_P3_EXT  0x3363
#اگر_ختم /* EGL_EXT_gl_colorspace_display_p3 */

#اگر_غیر_تعریف_شدہ EGL_EXT_gl_colorspace_display_p3_خطی
#تعریف_کرو EGL_EXT_gl_colorspace_display_p3_خطی 1
#تعریف_کرو EGL_GL_COLORSPACE_DISPLAY_P3_خطی_EXT 0x3362
#اگر_ختم /* EGL_EXT_gl_colorspace_display_p3_linear */

#اگر_غیر_تعریف_شدہ EGL_EXT_gl_colorspace_display_p3_passthrough
#تعریف_کرو EGL_EXT_gl_colorspace_display_p3_passthrough 1
#تعریف_کرو EGL_GL_COLORSPACE_DISPLAY_P3_PASSTHROUGH_EXT 0x3490
#اگر_ختم /* EGL_EXT_gl_colorspace_display_p3_passthrough */

#اگر_غیر_تعریف_شدہ EGL_EXT_gl_colorspace_scrgb
#تعریف_کرو EGL_EXT_gl_colorspace_scrgb 1
#تعریف_کرو EGL_GL_COLORSPACE_SCRGB_EXT       0x3351
#اگر_ختم /* EGL_EXT_gl_colorspace_scrgb */

#اگر_غیر_تعریف_شدہ EGL_EXT_gl_colorspace_scrgb_خطی
#تعریف_کرو EGL_EXT_gl_colorspace_scrgb_خطی 1
#تعریف_کرو EGL_GL_COLORSPACE_SCRGB_خطی_EXT 0x3350
#اگر_ختم /* EGL_EXT_gl_colorspace_scrgb_linear */

#اگر_غیر_تعریف_شدہ EGL_EXT_image_dma_buf_import
#تعریف_کرو EGL_EXT_image_dma_buf_import 1
#تعریف_کرو EGL_LINUX_DMA_BUF_EXT             0x3270
#تعریف_کرو EGL_LINUX_DRM_FOURCC_EXT          0x3271
#تعریف_کرو EGL_DMA_BUF_PLANE0_FD_EXT         0x3272
#تعریف_کرو EGL_DMA_BUF_PLANE0_انحراف_EXT     0x3273
#تعریف_کرو EGL_DMA_BUF_PLANE0_PITCH_EXT      0x3274
#تعریف_کرو EGL_DMA_BUF_PLANE1_FD_EXT         0x3275
#تعریف_کرو EGL_DMA_BUF_PLANE1_انحراف_EXT     0x3276
#تعریف_کرو EGL_DMA_BUF_PLANE1_PITCH_EXT      0x3277
#تعریف_کرو EGL_DMA_BUF_PLANE2_FD_EXT         0x3278
#تعریف_کرو EGL_DMA_BUF_PLANE2_انحراف_EXT     0x3279
#تعریف_کرو EGL_DMA_BUF_PLANE2_PITCH_EXT      0x327A
#تعریف_کرو EGL_YUV_COLOR_SPACE_HINT_EXT      0x327B
#تعریف_کرو EGL_SAMPLE_RANGE_HINT_EXT         0x327C
#تعریف_کرو EGL_YUV_CHROMA_HORIZONTAL_SITING_HINT_EXT 0x327D
#تعریف_کرو EGL_YUV_CHROMA_VERTICAL_SITING_HINT_EXT 0x327E
#تعریف_کرو EGL_ITU_REC601_EXT                0x327F
#تعریف_کرو EGL_ITU_REC709_EXT                0x3280
#تعریف_کرو EGL_ITU_REC2020_EXT               0x3281
#تعریف_کرو EGL_YUV_بھرا_RANGE_EXT            0x3282
#تعریف_کرو EGL_YUV_NARROW_RANGE_EXT          0x3283
#تعریف_کرو EGL_YUV_CHROMA_SITING_0_EXT       0x3284
#تعریف_کرو EGL_YUV_CHROMA_SITING_0_5_EXT     0x3285
#اگر_ختم /* EGL_EXT_image_dma_buf_import */

#اگر_غیر_تعریف_شدہ EGL_EXT_image_dma_buf_import_modifiers
#تعریف_کرو EGL_EXT_image_dma_buf_import_modifiers 1
#تعریف_کرو EGL_DMA_BUF_PLANE3_FD_EXT         0x3440
#تعریف_کرو EGL_DMA_BUF_PLANE3_انحراف_EXT     0x3441
#تعریف_کرو EGL_DMA_BUF_PLANE3_PITCH_EXT      0x3442
#تعریف_کرو EGL_DMA_BUF_PLANE0_MODIFIER_LO_EXT 0x3443
#تعریف_کرو EGL_DMA_BUF_PLANE0_MODIFIER_HI_EXT 0x3444
#تعریف_کرو EGL_DMA_BUF_PLANE1_MODIFIER_LO_EXT 0x3445
#تعریف_کرو EGL_DMA_BUF_PLANE1_MODIFIER_HI_EXT 0x3446
#تعریف_کرو EGL_DMA_BUF_PLANE2_MODIFIER_LO_EXT 0x3447
#تعریف_کرو EGL_DMA_BUF_PLANE2_MODIFIER_HI_EXT 0x3448
#تعریف_کرو EGL_DMA_BUF_PLANE3_MODIFIER_LO_EXT 0x3449
#تعریف_کرو EGL_DMA_BUF_PLANE3_MODIFIER_HI_EXT 0x344A
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDMABUFFORMATSEXTPROC) (EGLDisplay dpy, EGLint max_formats, EGLint *formats, EGLint *عدد_formats);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDMABUFMODIFIERSEXTPROC) (EGLDisplay dpy, EGLint format, EGLint max_modifiers, EGLuint64KHR *modifiers, EGLBoolean *external_only, EGLint *عدد_modifiers);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDmaBufFormatsEXT (EGLDisplay dpy, EGLint max_formats, EGLint *formats, EGLint *عدد_formats);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDmaBufModifiersEXT (EGLDisplay dpy, EGLint format, EGLint max_modifiers, EGLuint64KHR *modifiers, EGLBoolean *external_only, EGLint *عدد_modifiers);
#اگر_ختم
#اگر_ختم /* EGL_EXT_image_dma_buf_import_modifiers */

#اگر_غیر_تعریف_شدہ EGL_EXT_image_gl_colorspace
#تعریف_کرو EGL_EXT_image_gl_colorspace 1
#تعریف_کرو EGL_GL_COLORSPACE_DEFAULT_EXT     0x314D
#اگر_ختم /* EGL_EXT_image_gl_colorspace */

#اگر_غیر_تعریف_شدہ EGL_EXT_image_implicit_sync_control
#تعریف_کرو EGL_EXT_image_implicit_sync_control 1
#تعریف_کرو EGL_IMPORT_SYNC_TYPE_EXT          0x3470
#تعریف_کرو EGL_IMPORT_IMPLICIT_SYNC_EXT      0x3471
#تعریف_کرو EGL_IMPORT_EXPLICIT_SYNC_EXT      0x3472
#اگر_ختم /* EGL_EXT_image_implicit_sync_control */

#اگر_غیر_تعریف_شدہ EGL_EXT_multiview_کھڑکی
#تعریف_کرو EGL_EXT_multiview_کھڑکی 1
#تعریف_کرو EGL_MULTIVIEW_VIEW_گنتی_EXT      0x3134
#اگر_ختم /* EGL_EXT_multiview_window */

#اگر_غیر_تعریف_شدہ EGL_EXT_output_بنیاد
#تعریف_کرو EGL_EXT_output_بنیاد 1
قسمتعریف خالی *EGLOutputLayerEXT;
قسمتعریف خالی *EGLOutput_پورٹ_EXT;
#تعریف_کرو EGL_NO_OUTPUT_LAYER_EXT           EGL_CAST(EGLOutputLayerEXT,0)
#تعریف_کرو EGL_NO_OUTPUT_پورٹ_EXT            EGL_CAST(EGLOutput_پورٹ_EXT,0)
#تعریف_کرو EGL_BAD_OUTPUT_LAYER_EXT          0x322D
#تعریف_کرو EGL_BAD_OUTPUT_پورٹ_EXT           0x322E
#تعریف_کرو EGL_تبادلہ_INTERVAL_EXT             0x322F
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLGETOUTPUTLAYERSEXTPROC) (EGLDisplay dpy, ثابت EGLAttrib *attrib_list, EGLOutputLayerEXT *layers, EGLint max_layers, EGLint *عدد_layers);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLGETOUTPUTPORTSEXTPROC) (EGLDisplay dpy, ثابت EGLAttrib *attrib_list, EGLOutput_پورٹ_EXT *ports, EGLint max_ports, EGLint *عدد_ports);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLOUTPUTLAYERATTRIBEXTPROC) (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib قدر);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLQUERYOUTPUTLAYERATTRIBEXTPROC) (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib *قدر);
قسمتعریف ثابت حرف *(EGLAPIENTRYP PFNEGLQUERYOUTPUTLAYERSTRINGEXTPROC) (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint name);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLOUTPUTPORTATTRIBEXTPROC) (EGLDisplay dpy, EGLOutput_پورٹ_EXT پورٹ, EGLint attribute, EGLAttrib قدر);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLQUERYOUTPUTPORTATTRIBEXTPROC) (EGLDisplay dpy, EGLOutput_پورٹ_EXT پورٹ, EGLint attribute, EGLAttrib *قدر);
قسمتعریف ثابت حرف *(EGLAPIENTRYP PFNEGLQUERYOUTPUTPORTSTRINGEXTPROC) (EGLDisplay dpy, EGLOutput_پورٹ_EXT پورٹ, EGLint name);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglGetOutputLayersEXT (EGLDisplay dpy, ثابت EGLAttrib *attrib_list, EGLOutputLayerEXT *layers, EGLint max_layers, EGLint *عدد_layers);
EGLAPI EGLBoolean EGLAPIENTRY eglGetOutputPortsEXT (EGLDisplay dpy, ثابت EGLAttrib *attrib_list, EGLOutput_پورٹ_EXT *ports, EGLint max_ports, EGLint *عدد_ports);
EGLAPI EGLBoolean EGLAPIENTRY eglOutputLayerAttribEXT (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib قدر);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryOutputLayerAttribEXT (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib *قدر);
EGLAPI ثابت حرف *EGLAPIENTRY eglQueryOutputLayerStringEXT (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint name);
EGLAPI EGLBoolean EGLAPIENTRY egl_Output_پورٹ_Attrib_EXT (EGLDisplay dpy, EGLOutput_پورٹ_EXT پورٹ, EGLint attribute, EGLAttrib قدر);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Output_پورٹ_Attrib_EXT (EGLDisplay dpy, EGLOutput_پورٹ_EXT پورٹ, EGLint attribute, EGLAttrib *قدر);
EGLAPI ثابت حرف *EGLAPIENTRY egl_Query_Output_پورٹ_String_EXT (EGLDisplay dpy, EGLOutput_پورٹ_EXT پورٹ, EGLint name);
#اگر_ختم
#اگر_ختم /* EGL_EXT_output_base */

#اگر_غیر_تعریف_شدہ EGL_EXT_output_drm
#تعریف_کرو EGL_EXT_output_drm 1
#تعریف_کرو EGL_DRM_CRTC_EXT                  0x3234
#تعریف_کرو EGL_DRM_PLANE_EXT                 0x3235
#تعریف_کرو EGL_DRM_CONNECTOR_EXT             0x3236
#اگر_ختم /* EGL_EXT_output_drm */

#اگر_غیر_تعریف_شدہ EGL_EXT_output_openwf
#تعریف_کرو EGL_EXT_output_openwf 1
#تعریف_کرو EGL_OPENWF_PIPELINE_ID_EXT        0x3238
#تعریف_کرو EGL_OPENWF_پورٹ_ID_EXT            0x3239
#اگر_ختم /* EGL_EXT_output_openwf */

#اگر_غیر_تعریف_شدہ EGL_EXT_pixel_format_float
#تعریف_کرو EGL_EXT_pixel_format_float 1
#تعریف_کرو EGL_COLOR_COMPONENT_TYPE_EXT      0x3339
#تعریف_کرو EGL_COLOR_COMPONENT_TYPE_FIXED_EXT 0x333A
#تعریف_کرو EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT 0x333B
#اگر_ختم /* EGL_EXT_pixel_format_float */

#اگر_غیر_تعریف_شدہ EGL_EXT_platform_بنیاد
#تعریف_کرو EGL_EXT_platform_بنیاد 1
قسمتعریف EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYEXTPROC) (EGLenum platform, خالی *native_display, ثابت EGLint *attrib_list);
قسمتعریف EGLSurface (EGLAPIENTRYP PFNEGLCREATEPLATFORMWINDOWSURFACEEXTPROC) (EGLDisplay dpy, EGLConfig config, خالی *native_کھڑکی, ثابت EGLint *attrib_list);
قسمتعریف EGLSurface (EGLAPIENTRYP PFNEGLCREATEPLATFORMPIXMAPSURFACEEXTPROC) (EGLDisplay dpy, EGLConfig config, خالی *native_pixmap, ثابت EGLint *attrib_list);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLDisplay EGLAPIENTRY eglGetPlatformDisplayEXT (EGLenum platform, خالی *native_display, ثابت EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY egl_Create_Platform_کھڑکی_Surface_EXT (EGLDisplay dpy, EGLConfig config, خالی *native_کھڑکی, ثابت EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePlatformPixmapSurfaceEXT (EGLDisplay dpy, EGLConfig config, خالی *native_pixmap, ثابت EGLint *attrib_list);
#اگر_ختم
#اگر_ختم /* EGL_EXT_platform_base */

#اگر_غیر_تعریف_شدہ EGL_EXT_platform_device
#تعریف_کرو EGL_EXT_platform_device 1
#تعریف_کرو EGL_PLATFORM_DEVICE_EXT           0x313F
#اگر_ختم /* EGL_EXT_platform_device */

#اگر_غیر_تعریف_شدہ EGL_EXT_platform_wayland
#تعریف_کرو EGL_EXT_platform_wayland 1
#تعریف_کرو EGL_PLATFORM_WAYLAND_EXT          0x31D8
#اگر_ختم /* EGL_EXT_platform_wayland */

#اگر_غیر_تعریف_شدہ EGL_EXT_platform_x11
#تعریف_کرو EGL_EXT_platform_x11 1
#تعریف_کرو EGL_PLATFORM_X11_EXT              0x31D5
#تعریف_کرو EGL_PLATFORM_X11_SCREEN_EXT       0x31D6
#اگر_ختم /* EGL_EXT_platform_x11 */

#اگر_غیر_تعریف_شدہ EGL_EXT_platform_xcb
#تعریف_کرو EGL_EXT_platform_xcb 1
#تعریف_کرو EGL_PLATFORM_XCB_EXT              0x31DC
#تعریف_کرو EGL_PLATFORM_XCB_SCREEN_EXT       0x31DE
#اگر_ختم /* EGL_EXT_platform_xcb */

#اگر_غیر_تعریف_شدہ EGL_EXT_present_opaque
#تعریف_کرو EGL_EXT_present_opaque 1
#تعریف_کرو EGL_PRESENT_OPAQUE_EXT            0x31DF
#اگر_ختم /* EGL_EXT_present_opaque */

#اگر_غیر_تعریف_شدہ EGL_EXT_protected_content
#تعریف_کرو EGL_EXT_protected_content 1
#تعریف_کرو EGL_PROTECTED_CONTENT_EXT         0x32C0
#اگر_ختم /* EGL_EXT_protected_content */

#اگر_غیر_تعریف_شدہ EGL_EXT_protected_surface
#تعریف_کرو EGL_EXT_protected_surface 1
#اگر_ختم /* EGL_EXT_protected_surface */

#اگر_غیر_تعریف_شدہ EGL_EXT_query_reset_notification_strategy
#تعریف_کرو EGL_EXT_query_reset_notification_strategy 1
#اگر_ختم /* EGL_EXT_query_reset_notification_strategy */

#اگر_غیر_تعریف_شدہ EGL_EXT_دھارا_صارف_egloutput
#تعریف_کرو EGL_EXT_دھارا_صارف_egloutput 1
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMEROUTPUTEXTPROC) (EGLDisplay dpy, EGLStreamKHR دھارا, EGLOutputLayerEXT layer);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_دھارا_صارف_Output_EXT (EGLDisplay dpy, EGLStreamKHR دھارا, EGLOutputLayerEXT layer);
#اگر_ختم
#اگر_ختم /* EGL_EXT_stream_consumer_egloutput */

#اگر_غیر_تعریف_شدہ EGL_EXT_surface_CTA861_3_metadata
#تعریف_کرو EGL_EXT_surface_CTA861_3_metadata 1
#تعریف_کرو EGL_CTA861_3_MAX_CONTENT_LIGHT_LEVEL_EXT 0x3360
#تعریف_کرو EGL_CTA861_3_MAX_چوکھٹا_اوسط_قدر_LEVEL_EXT 0x3361
#اگر_ختم /* EGL_EXT_surface_CTA861_3_metadata */

#اگر_غیر_تعریف_شدہ EGL_EXT_surface_SMPTE2086_metadata
#تعریف_کرو EGL_EXT_surface_SMPTE2086_metadata 1
#تعریف_کرو EGL_SMPTE2086_DISPLAY_PRIMARY_RX_EXT 0x3341
#تعریف_کرو EGL_SMPTE2086_DISPLAY_PRIMARY_RY_EXT 0x3342
#تعریف_کرو EGL_SMPTE2086_DISPLAY_PRIMARY_GX_EXT 0x3343
#تعریف_کرو EGL_SMPTE2086_DISPLAY_PRIMARY_GY_EXT 0x3344
#تعریف_کرو EGL_SMPTE2086_DISPLAY_PRIMARY_BX_EXT 0x3345
#تعریف_کرو EGL_SMPTE2086_DISPLAY_PRIMARY_BY_EXT 0x3346
#تعریف_کرو EGL_SMPTE2086_WHITE_نقطہ_X_EXT   0x3347
#تعریف_کرو EGL_SMPTE2086_WHITE_نقطہ_Y_EXT   0x3348
#تعریف_کرو EGL_SMPTE2086_MAX_LUMINANCE_EXT   0x3349
#تعریف_کرو EGL_SMPTE2086_MIN_LUMINANCE_EXT   0x334A
#تعریف_کرو EGL_METADATA_SCALING_EXT          50000
#اگر_ختم /* EGL_EXT_surface_SMPTE2086_metadata */

#اگر_غیر_تعریف_شدہ EGL_EXT_surface_compression
#تعریف_کرو EGL_EXT_surface_compression 1
#تعریف_کرو EGL_SURFACE_COMPRESSION_EXT       0x34B0
#تعریف_کرو EGL_SURFACE_COMPRESSION_PLANE1_EXT 0x328E
#تعریف_کرو EGL_SURFACE_COMPRESSION_PLANE2_EXT 0x328F
#تعریف_کرو EGL_SURFACE_COMPRESSION_FIXED_شرح_NONE_EXT 0x34B1
#تعریف_کرو EGL_SURFACE_COMPRESSION_FIXED_شرح_DEFAULT_EXT 0x34B2
#تعریف_کرو EGL_SURFACE_COMPRESSION_FIXED_شرح_1_BPC_EXT 0x34B4
#تعریف_کرو EGL_SURFACE_COMPRESSION_FIXED_شرح_2_BPC_EXT 0x34B5
#تعریف_کرو EGL_SURFACE_COMPRESSION_FIXED_شرح_3_BPC_EXT 0x34B6
#تعریف_کرو EGL_SURFACE_COMPRESSION_FIXED_شرح_4_BPC_EXT 0x34B7
#تعریف_کرو EGL_SURFACE_COMPRESSION_FIXED_شرح_5_BPC_EXT 0x34B8
#تعریف_کرو EGL_SURFACE_COMPRESSION_FIXED_شرح_6_BPC_EXT 0x34B9
#تعریف_کرو EGL_SURFACE_COMPRESSION_FIXED_شرح_7_BPC_EXT 0x34BA
#تعریف_کرو EGL_SURFACE_COMPRESSION_FIXED_شرح_8_BPC_EXT 0x34BB
#تعریف_کرو EGL_SURFACE_COMPRESSION_FIXED_شرح_9_BPC_EXT 0x34BC
#تعریف_کرو EGL_SURFACE_COMPRESSION_FIXED_شرح_10_BPC_EXT 0x34BD
#تعریف_کرو EGL_SURFACE_COMPRESSION_FIXED_شرح_11_BPC_EXT 0x34BE
#تعریف_کرو EGL_SURFACE_COMPRESSION_FIXED_شرح_12_BPC_EXT 0x34BF
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSUPPORTEDCOMPRESSIONRATESEXTPROC) (EGLDisplay dpy, EGLConfig config, ثابت EGLAttrib *attrib_list, EGLint *rates, EGLint شرح_سائز, EGLint *عدد_rates);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQuerySupportedCompressionRatesEXT (EGLDisplay dpy, EGLConfig config, ثابت EGLAttrib *attrib_list, EGLint *rates, EGLint شرح_سائز, EGLint *عدد_rates);
#اگر_ختم
#اگر_ختم /* EGL_EXT_surface_compression */

#اگر_غیر_تعریف_شدہ EGL_EXT_تبادلہ_buffers_with_damage
#تعریف_کرو EGL_EXT_تبادلہ_buffers_with_damage 1
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC) (EGLDisplay dpy, EGLSurface surface, ثابت EGLint *rects, EGLint n_rects);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_تبادلہ_Buffers_With_Damage_EXT (EGLDisplay dpy, EGLSurface surface, ثابت EGLint *rects, EGLint n_rects);
#اگر_ختم
#اگر_ختم /* EGL_EXT_swap_buffers_with_damage */

#اگر_غیر_تعریف_شدہ EGL_EXT_sync_reuse
#تعریف_کرو EGL_EXT_sync_reuse 1
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLUNSIGNALSYNCEXTPROC) (EGLDisplay dpy, EGLSync sync, ثابت EGLAttrib *attrib_list);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglUnsignalSyncEXT (EGLDisplay dpy, EGLSync sync, ثابت EGLAttrib *attrib_list);
#اگر_ختم
#اگر_ختم /* EGL_EXT_sync_reuse */

#اگر_غیر_تعریف_شدہ EGL_EXT_yuv_surface
#تعریف_کرو EGL_EXT_yuv_surface 1
#تعریف_کرو EGL_YUV_ترتیب_EXT                 0x3301
#تعریف_کرو EGL_YUV_نمبر_کا_PLANES_EXT      0x3311
#تعریف_کرو EGL_YUV_SUBSAMPLE_EXT             0x3312
#تعریف_کرو EGL_YUV_گہرائی_RANGE_EXT           0x3317
#تعریف_کرو EGL_YUV_CSC_STANDARD_EXT          0x330A
#تعریف_کرو EGL_YUV_PLANE_BPP_EXT             0x331A
#تعریف_کرو EGL_YUV_بفر_EXT                0x3300
#تعریف_کرو EGL_YUV_ترتیب_YUV_EXT             0x3302
#تعریف_کرو EGL_YUV_ترتیب_YVU_EXT             0x3303
#تعریف_کرو EGL_YUV_ترتیب_YUYV_EXT            0x3304
#تعریف_کرو EGL_YUV_ترتیب_UYVY_EXT            0x3305
#تعریف_کرو EGL_YUV_ترتیب_YVYU_EXT            0x3306
#تعریف_کرو EGL_YUV_ترتیب_VYUY_EXT            0x3307
#تعریف_کرو EGL_YUV_ترتیب_AYUV_EXT            0x3308
#تعریف_کرو EGL_YUV_SUBSAMPLE_4_2_0_EXT       0x3313
#تعریف_کرو EGL_YUV_SUBSAMPLE_4_2_2_EXT       0x3314
#تعریف_کرو EGL_YUV_SUBSAMPLE_4_4_4_EXT       0x3315
#تعریف_کرو EGL_YUV_گہرائی_RANGE_LIMITED_EXT   0x3318
#تعریف_کرو EGL_YUV_گہرائی_RANGE_بھرا_EXT      0x3319
#تعریف_کرو EGL_YUV_CSC_STANDARD_601_EXT      0x330B
#تعریف_کرو EGL_YUV_CSC_STANDARD_709_EXT      0x330C
#تعریف_کرو EGL_YUV_CSC_STANDARD_2020_EXT     0x330D
#تعریف_کرو EGL_YUV_PLANE_BPP_0_EXT           0x331B
#تعریف_کرو EGL_YUV_PLANE_BPP_8_EXT           0x331C
#تعریف_کرو EGL_YUV_PLANE_BPP_10_EXT          0x331D
#اگر_ختم /* EGL_EXT_yuv_surface */

#اگر_غیر_تعریف_شدہ EGL_HI_clientpixmap
#تعریف_کرو EGL_HI_clientpixmap 1
ساخت EGLClientPixmapHI {
    خالی  *p_ڈیٹا;
    EGLint i_چوڑائی;
    EGLint i_اونچائی;
    EGLint iStride;
};
#تعریف_کرو EGL_CLIENT_PIXMAP_اشارہ_گر_HI      0x8F74
قسمتعریف EGLSurface (EGLAPIENTRYP PFNEGLCREATEPIXMAPSURFACEHIPROC) (EGLDisplay dpy, EGLConfig config, ساخت EGLClientPixmapHI *pixmap);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSurface EGLAPIENTRY eglCreatePixmapSurfaceHI (EGLDisplay dpy, EGLConfig config, ساخت EGLClientPixmapHI *pixmap);
#اگر_ختم
#اگر_ختم /* EGL_HI_clientpixmap */

#اگر_غیر_تعریف_شدہ EGL_HI_colorformats
#تعریف_کرو EGL_HI_colorformats 1
#تعریف_کرو EGL_COLOR_FORMAT_HI               0x8F70
#تعریف_کرو EGL_COLOR_RGB_HI                  0x8F71
#تعریف_کرو EGL_COLOR_RGBA_HI                 0x8F72
#تعریف_کرو EGL_COLOR_ARGB_HI                 0x8F73
#اگر_ختم /* EGL_HI_colorformats */

#اگر_غیر_تعریف_شدہ EGL_IMG_context_ترجیح
#تعریف_کرو EGL_IMG_context_ترجیح 1
#تعریف_کرو EGL_CONTEXT_ترجیح_LEVEL_IMG    0x3100
#تعریف_کرو EGL_CONTEXT_ترجیح_بلند_IMG     0x3101
#تعریف_کرو EGL_CONTEXT_ترجیح_MEDIUM_IMG   0x3102
#تعریف_کرو EGL_CONTEXT_ترجیح_کم_IMG      0x3103
#اگر_ختم /* EGL_IMG_context_priority */

#اگر_غیر_تعریف_شدہ EGL_IMG_image_plane_attribs
#تعریف_کرو EGL_IMG_image_plane_attribs 1
#تعریف_کرو EGL_NATIVE_بفر_MULTIPLANE_SEPARATE_IMG 0x3105
#تعریف_کرو EGL_NATIVE_بفر_PLANE_انحراف_IMG 0x3106
#اگر_ختم /* EGL_IMG_image_plane_attribs */

#اگر_غیر_تعریف_شدہ EGL_MESA_drm_image
#تعریف_کرو EGL_MESA_drm_image 1
#تعریف_کرو EGL_DRM_بفر_FORMAT_MESA        0x31D0
#تعریف_کرو EGL_DRM_بفر_USE_MESA           0x31D1
#تعریف_کرو EGL_DRM_بفر_FORMAT_ARGB32_MESA 0x31D2
#تعریف_کرو EGL_DRM_بفر_MESA               0x31D3
#تعریف_کرو EGL_DRM_بفر_STRIDE_MESA        0x31D4
#تعریف_کرو EGL_DRM_بفر_USE_SCANOUT_MESA   0x00000001
#تعریف_کرو EGL_DRM_بفر_USE_SHARE_MESA     0x00000002
#تعریف_کرو EGL_DRM_بفر_USE_CURSOR_MESA    0x00000004
قسمتعریف EGLImageKHR (EGLAPIENTRYP PFNEGLCREATEDRMIMAGEMESAPROC) (EGLDisplay dpy, ثابت EGLint *attrib_list);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLEXPORTDRMIMAGEMESAPROC) (EGLDisplay dpy, EGLImageKHR image, EGLint *name, EGLint *handle, EGLint *stride);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLImageKHR EGLAPIENTRY eglCreateDRMImageMESA (EGLDisplay dpy, ثابت EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglExportDRMImageMESA (EGLDisplay dpy, EGLImageKHR image, EGLint *name, EGLint *handle, EGLint *stride);
#اگر_ختم
#اگر_ختم /* EGL_MESA_drm_image */

#اگر_غیر_تعریف_شدہ EGL_MESA_image_dma_buf_export
#تعریف_کرو EGL_MESA_image_dma_buf_export 1
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLEXPORTDMABUFIMAGEQUERYMESAPROC) (EGLDisplay dpy, EGLImageKHR image, صحیح *fourcc, صحیح *عدد_planes, EGLuint64KHR *modifiers);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLEXPORTDMABUFIMAGEMESAPROC) (EGLDisplay dpy, EGLImageKHR image, صحیح *fds, EGLint *strides, EGLint *offsets);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglExportDMABUFImageQueryMESA (EGLDisplay dpy, EGLImageKHR image, صحیح *fourcc, صحیح *عدد_planes, EGLuint64KHR *modifiers);
EGLAPI EGLBoolean EGLAPIENTRY eglExportDMABUFImageMESA (EGLDisplay dpy, EGLImageKHR image, صحیح *fds, EGLint *strides, EGLint *offsets);
#اگر_ختم
#اگر_ختم /* EGL_MESA_image_dma_buf_export */

#اگر_غیر_تعریف_شدہ EGL_MESA_platform_gbm
#تعریف_کرو EGL_MESA_platform_gbm 1
#تعریف_کرو EGL_PLATFORM_GBM_MESA             0x31D7
#اگر_ختم /* EGL_MESA_platform_gbm */

#اگر_غیر_تعریف_شدہ EGL_MESA_platform_surfaceless
#تعریف_کرو EGL_MESA_platform_surfaceless 1
#تعریف_کرو EGL_PLATFORM_SURFACELESS_MESA     0x31DD
#اگر_ختم /* EGL_MESA_platform_surfaceless */

#اگر_غیر_تعریف_شدہ EGL_MESA_query_driver
#تعریف_کرو EGL_MESA_query_driver 1
قسمتعریف حرف *(EGLAPIENTRYP PFNEGLGETDISPLAYDRIVERCONFIGPROC) (EGLDisplay dpy);
قسمتعریف ثابت حرف *(EGLAPIENTRYP PFNEGLGETDISPLAYDRIVERNAMEPROC) (EGLDisplay dpy);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI حرف *EGLAPIENTRY eglGetDisplayDriverConfig (EGLDisplay dpy);
EGLAPI ثابت حرف *EGLAPIENTRY eglGetDisplayDriverName (EGLDisplay dpy);
#اگر_ختم
#اگر_ختم /* EGL_MESA_query_driver */

#اگر_غیر_تعریف_شدہ EGL_NOK_تبادلہ_region
#تعریف_کرو EGL_NOK_تبادلہ_region 1
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSREGIONNOKPROC) (EGLDisplay dpy, EGLSurface surface, EGLint عدد_Rects_2, ثابت EGLint *rects);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_تبادلہ_Buffers_Region_NOK (EGLDisplay dpy, EGLSurface surface, EGLint عدد_Rects_2, ثابت EGLint *rects);
#اگر_ختم
#اگر_ختم /* EGL_NOK_swap_region */

#اگر_غیر_تعریف_شدہ EGL_NOK_تبادلہ_region2
#تعریف_کرو EGL_NOK_تبادلہ_region2 1
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSREGION2NOKPROC) (EGLDisplay dpy, EGLSurface surface, EGLint عدد_Rects_2, ثابت EGLint *rects);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_تبادلہ_Buffers_Region2_NOK (EGLDisplay dpy, EGLSurface surface, EGLint عدد_Rects_2, ثابت EGLint *rects);
#اگر_ختم
#اگر_ختم /* EGL_NOK_swap_region2 */

#اگر_غیر_تعریف_شدہ EGL_NOK_texture_from_pixmap
#تعریف_کرو EGL_NOK_texture_from_pixmap 1
#تعریف_کرو EGL_Y_INVERTED_NOK                0x307F
#اگر_ختم /* EGL_NOK_texture_from_pixmap */

#اگر_غیر_تعریف_شدہ EGL_NV_3dvision_surface
#تعریف_کرو EGL_NV_3dvision_surface 1
#تعریف_کرو EGL_AUTO_STEREO_NV                0x3136
#اگر_ختم /* EGL_NV_3dvision_surface */

#اگر_غیر_تعریف_شدہ EGL_NV_context_ترجیح_realtime
#تعریف_کرو EGL_NV_context_ترجیح_realtime 1
#تعریف_کرو EGL_CONTEXT_ترجیح_REALTIME_NV  0x3357
#اگر_ختم /* EGL_NV_context_priority_realtime */

#اگر_غیر_تعریف_شدہ EGL_NV_coverage_sample
#تعریف_کرو EGL_NV_coverage_sample 1
#تعریف_کرو EGL_COVERAGE_BUFFERS_NV           0x30E0
#تعریف_کرو EGL_COVERAGE_SAMPLES_NV           0x30E1
#اگر_ختم /* EGL_NV_coverage_sample */

#اگر_غیر_تعریف_شدہ EGL_NV_coverage_sample_resolve
#تعریف_کرو EGL_NV_coverage_sample_resolve 1
#تعریف_کرو EGL_COVERAGE_SAMPLE_RESOLVE_NV    0x3131
#تعریف_کرو EGL_COVERAGE_SAMPLE_RESOLVE_DEFAULT_NV 0x3132
#تعریف_کرو EGL_COVERAGE_SAMPLE_RESOLVE_NONE_NV 0x3133
#اگر_ختم /* EGL_NV_coverage_sample_resolve */

#اگر_غیر_تعریف_شدہ EGL_NV_cuda_event
#تعریف_کرو EGL_NV_cuda_event 1
#تعریف_کرو EGL_CUDA_EVENT_HANDLE_NV          0x323B
#تعریف_کرو EGL_SYNC_CUDA_EVENT_NV            0x323C
#تعریف_کرو EGL_SYNC_CUDA_EVENT_COMPLETE_NV   0x323D
#اگر_ختم /* EGL_NV_cuda_event */

#اگر_غیر_تعریف_شدہ EGL_NV_گہرائی_nonlinear
#تعریف_کرو EGL_NV_گہرائی_nonlinear 1
#تعریف_کرو EGL_گہرائی_ENCODING_NV             0x30E2
#تعریف_کرو EGL_گہرائی_ENCODING_NONE_NV        0
#تعریف_کرو EGL_گہرائی_ENCODING_NONLINEAR_NV   0x30E3
#اگر_ختم /* EGL_NV_depth_nonlinear */

#اگر_غیر_تعریف_شدہ EGL_NV_device_cuda
#تعریف_کرو EGL_NV_device_cuda 1
#تعریف_کرو EGL_CUDA_DEVICE_NV                0x323A
#اگر_ختم /* EGL_NV_device_cuda */

#اگر_غیر_تعریف_شدہ EGL_NV_native_query
#تعریف_کرو EGL_NV_native_query 1
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLQUERYNATIVEDISPLAYNVPROC) (EGLDisplay dpy, EGLNativeDisplayType *display_id);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLQUERYNATIVEWINDOWNVPROC) (EGLDisplay dpy, EGLSurface surf, EGLNative_کھڑکی_Type *کھڑکی);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLQUERYNATIVEPIXMAPNVPROC) (EGLDisplay dpy, EGLSurface surf, EGLNativePixmapType *pixmap);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryNativeDisplayNV (EGLDisplay dpy, EGLNativeDisplayType *display_id);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Native_کھڑکی_NV (EGLDisplay dpy, EGLSurface surf, EGLNative_کھڑکی_Type *کھڑکی);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryNativePixmapNV (EGLDisplay dpy, EGLSurface surf, EGLNativePixmapType *pixmap);
#اگر_ختم
#اگر_ختم /* EGL_NV_native_query */

#اگر_غیر_تعریف_شدہ EGL_NV_post_convert_rounding
#تعریف_کرو EGL_NV_post_convert_rounding 1
#اگر_ختم /* EGL_NV_post_convert_rounding */

#اگر_غیر_تعریف_شدہ EGL_NV_post_sub_بفر
#تعریف_کرو EGL_NV_post_sub_بفر 1
#تعریف_کرو EGL_POST_SUB_بفر_SUPPORTED_NV  0x30BE
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLPOSTSUBBUFFERNVPROC) (EGLDisplay dpy, EGLSurface surface, EGLint x, EGLint y, EGLint چوڑائی, EGLint اونچائی);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Post_Sub_بفر_NV (EGLDisplay dpy, EGLSurface surface, EGLint x, EGLint y, EGLint چوڑائی, EGLint اونچائی);
#اگر_ختم
#اگر_ختم /* EGL_NV_post_sub_buffer */

#اگر_غیر_تعریف_شدہ EGL_NV_quadruple_بفر
#تعریف_کرو EGL_NV_quadruple_بفر 1
#تعریف_کرو EGL_QUADRUPLE_بفر_NV           0x3231
#اگر_ختم /* EGL_NV_quadruple_buffer */

#اگر_غیر_تعریف_شدہ EGL_NV_robustness_video_حافظہ_purge
#تعریف_کرو EGL_NV_robustness_video_حافظہ_purge 1
#تعریف_کرو EGL_GENERATE_RESET_ON_VIDEO_حافظہ_PURGE_NV 0x334C
#اگر_ختم /* EGL_NV_robustness_video_memory_purge */

#اگر_غیر_تعریف_شدہ EGL_NV_دھارا_صارف_eglimage
#تعریف_کرو EGL_NV_دھارا_صارف_eglimage 1
#تعریف_کرو EGL_دھارا_صارف_IMAGE_NV      0x3373
#تعریف_کرو EGL_دھارا_IMAGE_جوڑو_NV           0x3374
#تعریف_کرو EGL_دھارا_IMAGE_REMOVE_NV        0x3375
#تعریف_کرو EGL_دھارا_IMAGE_دستیاب_NV     0x3376
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMIMAGECONSUMERCONNECTNVPROC) (EGLDisplay dpy, EGLStreamKHR دھارا, EGLint عدد_modifiers, ثابت EGLuint64KHR *modifiers, ثابت EGLAttrib *attrib_list);
قسمتعریف EGLint (EGLAPIENTRYP PFNEGLQUERYSTREAMCONSUMEREVENTNVPROC) (EGLDisplay dpy, EGLStreamKHR دھارا, EGLTime timeout, EGLenum *event, EGLAttrib *aux);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMACQUIREIMAGENVPROC) (EGLDisplay dpy, EGLStreamKHR دھارا, EGLImage *pImage, EGLSync sync);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMRELEASEIMAGENVPROC) (EGLDisplay dpy, EGLStreamKHR دھارا, EGLImage image, EGLSync sync);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_دھارا_Image_صارف_Connect_NV (EGLDisplay dpy, EGLStreamKHR دھارا, EGLint عدد_modifiers, ثابت EGLuint64KHR *modifiers, ثابت EGLAttrib *attrib_list);
EGLAPI EGLint EGLAPIENTRY egl_Query_دھارا_صارف_Event_NV (EGLDisplay dpy, EGLStreamKHR دھارا, EGLTime timeout, EGLenum *event, EGLAttrib *aux);
EGLAPI EGLBoolean EGLAPIENTRY egl_دھارا_Acquire_Image_NV (EGLDisplay dpy, EGLStreamKHR دھارا, EGLImage *pImage, EGLSync sync);
EGLAPI EGLBoolean EGLAPIENTRY egl_دھارا_Release_Image_NV (EGLDisplay dpy, EGLStreamKHR دھارا, EGLImage image, EGLSync sync);
#اگر_ختم
#اگر_ختم /* EGL_NV_stream_consumer_eglimage */

#اگر_غیر_تعریف_شدہ EGL_NV_دھارا_صارف_eglimage_use_scanout_attrib
#تعریف_کرو EGL_NV_دھارا_صارف_eglimage_use_scanout_attrib 1
#تعریف_کرو EGL_دھارا_صارف_IMAGE_USE_SCANOUT_NV 0x3378
#اگر_ختم /* EGL_NV_stream_consumer_eglimage_use_scanout_attrib */

#اگر_غیر_تعریف_شدہ EGL_NV_دھارا_صارف_gltexture_yuv
#تعریف_کرو EGL_NV_دھارا_صارف_gltexture_yuv 1
#تعریف_کرو EGL_YUV_PLANE0_TEXTURE_UNIT_NV    0x332C
#تعریف_کرو EGL_YUV_PLANE1_TEXTURE_UNIT_NV    0x332D
#تعریف_کرو EGL_YUV_PLANE2_TEXTURE_UNIT_NV    0x332E
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALATTRIBSNVPROC) (EGLDisplay dpy, EGLStreamKHR دھارا, ثابت EGLAttrib *attrib_list);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_دھارا_صارف_GLTexture_External_Attribs_NV (EGLDisplay dpy, EGLStreamKHR دھارا, ثابت EGLAttrib *attrib_list);
#اگر_ختم
#اگر_ختم /* EGL_NV_stream_consumer_gltexture_yuv */

#اگر_غیر_تعریف_شدہ EGL_NV_دھارا_cross_display
#تعریف_کرو EGL_NV_دھارا_cross_display 1
#تعریف_کرو EGL_دھارا_CROSS_DISPLAY_NV       0x334E
#اگر_ختم /* EGL_NV_stream_cross_display */

#اگر_غیر_تعریف_شدہ EGL_NV_دھارا_cross_object
#تعریف_کرو EGL_NV_دھارا_cross_object 1
#تعریف_کرو EGL_دھارا_CROSS_OBJECT_NV        0x334D
#اگر_ختم /* EGL_NV_stream_cross_object */

#اگر_غیر_تعریف_شدہ EGL_NV_دھارا_cross_تقسیم
#تعریف_کرو EGL_NV_دھارا_cross_تقسیم 1
#تعریف_کرو EGL_دھارا_CROSS_تقسیم_NV     0x323F
#اگر_ختم /* EGL_NV_stream_cross_partition */

#اگر_غیر_تعریف_شدہ EGL_NV_دھارا_cross_process
#تعریف_کرو EGL_NV_دھارا_cross_process 1
#تعریف_کرو EGL_دھارا_CROSS_PROCESS_NV       0x3245
#اگر_ختم /* EGL_NV_stream_cross_process */

#اگر_غیر_تعریف_شدہ EGL_NV_دھارا_cross_system
#تعریف_کرو EGL_NV_دھارا_cross_system 1
#تعریف_کرو EGL_دھارا_CROSS_SYSTEM_NV        0x334F
#اگر_ختم /* EGL_NV_stream_cross_system */

#اگر_غیر_تعریف_شدہ EGL_NV_دھارا_dma
#تعریف_کرو EGL_NV_دھارا_dma 1
#تعریف_کرو EGL_دھارا_DMA_NV                 0x3371
#تعریف_کرو EGL_دھارا_DMA_SERVER_NV          0x3372
#اگر_ختم /* EGL_NV_stream_dma */

#اگر_غیر_تعریف_شدہ EGL_NV_دھارا_fifo_اگلا
#تعریف_کرو EGL_NV_دھارا_fifo_اگلا 1
#تعریف_کرو EGL_PENDING_چوکھٹا_NV              0x3329
#تعریف_کرو EGL_دھارا_وقت_PENDING_NV        0x332A
#اگر_ختم /* EGL_NV_stream_fifo_next */

#اگر_غیر_تعریف_شدہ EGL_NV_دھارا_fifo_synchronous
#تعریف_کرو EGL_NV_دھارا_fifo_synchronous 1
#تعریف_کرو EGL_دھارا_FIFO_SYNCHRONOUS_NV    0x3336
#اگر_ختم /* EGL_NV_stream_fifo_synchronous */

#اگر_غیر_تعریف_شدہ EGL_NV_دھارا_flush
#تعریف_کرو EGL_NV_دھارا_flush 1
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMFLUSHNVPROC) (EGLDisplay dpy, EGLStreamKHR دھارا);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_دھارا_Flush_NV (EGLDisplay dpy, EGLStreamKHR دھارا);
#اگر_ختم
#اگر_ختم /* EGL_NV_stream_flush */

#اگر_غیر_تعریف_شدہ EGL_NV_دھارا_چوکھٹا_limits
#تعریف_کرو EGL_NV_دھارا_چوکھٹا_limits 1
#تعریف_کرو EGL_پیداکار_MAX_چوکھٹا_HINT_NV    0x3337
#تعریف_کرو EGL_صارف_MAX_چوکھٹا_HINT_NV    0x3338
#اگر_ختم /* EGL_NV_stream_frame_limits */

#اگر_غیر_تعریف_شدہ EGL_NV_دھارا_metadata
#تعریف_کرو EGL_NV_دھارا_metadata 1
#تعریف_کرو EGL_MAX_دھارا_METADATA_بلاکیں_NV 0x3250
#تعریف_کرو EGL_MAX_دھارا_METADATA_بلاک_سائز_NV 0x3251
#تعریف_کرو EGL_MAX_دھارا_METADATA_کل_سائز_NV 0x3252
#تعریف_کرو EGL_پیداکار_METADATA_NV          0x3253
#تعریف_کرو EGL_صارف_METADATA_NV          0x3254
#تعریف_کرو EGL_PENDING_METADATA_NV           0x3328
#تعریف_کرو EGL_METADATA0_سائز_NV             0x3255
#تعریف_کرو EGL_METADATA1_سائز_NV             0x3256
#تعریف_کرو EGL_METADATA2_سائز_NV             0x3257
#تعریف_کرو EGL_METADATA3_سائز_NV             0x3258
#تعریف_کرو EGL_METADATA0_TYPE_NV             0x3259
#تعریف_کرو EGL_METADATA1_TYPE_NV             0x325A
#تعریف_کرو EGL_METADATA2_TYPE_NV             0x325B
#تعریف_کرو EGL_METADATA3_TYPE_NV             0x325C
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDISPLAYATTRIBNVPROC) (EGLDisplay dpy, EGLint attribute, EGLAttrib *قدر);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLSETSTREAMMETADATANVPROC) (EGLDisplay dpy, EGLStreamKHR دھارا, EGLint n, EGLint انحراف_2, EGLint سائز, ثابت خالی *ڈیٹا);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMMETADATANVPROC) (EGLDisplay dpy, EGLStreamKHR دھارا, EGLenum name, EGLint n, EGLint انحراف_2, EGLint سائز, خالی *ڈیٹا);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDisplayAttribNV (EGLDisplay dpy, EGLint attribute, EGLAttrib *قدر);
EGLAPI EGLBoolean EGLAPIENTRY egl_سیٹ_دھارا_Metadata_NV (EGLDisplay dpy, EGLStreamKHR دھارا, EGLint n, EGLint انحراف_2, EGLint سائز, ثابت خالی *ڈیٹا);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_دھارا_Metadata_NV (EGLDisplay dpy, EGLStreamKHR دھارا, EGLenum name, EGLint n, EGLint انحراف_2, EGLint سائز, خالی *ڈیٹا);
#اگر_ختم
#اگر_ختم /* EGL_NV_stream_metadata */

#اگر_غیر_تعریف_شدہ EGL_NV_دھارا_origin
#تعریف_کرو EGL_NV_دھارا_origin 1
#تعریف_کرو EGL_دھارا_چوکھٹا_ORIGIN_X_NV      0x3366
#تعریف_کرو EGL_دھارا_چوکھٹا_ORIGIN_Y_NV      0x3367
#تعریف_کرو EGL_دھارا_چوکھٹا_MAJOR_AXIS_NV    0x3368
#تعریف_کرو EGL_صارف_AUTO_ORIENTATION_NV  0x3369
#تعریف_کرو EGL_پیداکار_AUTO_ORIENTATION_NV  0x336A
#تعریف_کرو EGL_بایاں_NV                       0x336B
#تعریف_کرو EGL_دایاں_NV                      0x336C
#تعریف_کرو EGL_چوٹی_NV                        0x336D
#تعریف_کرو EGL_BOTTOM_NV                     0x336E
#تعریف_کرو EGL_X_AXIS_NV                     0x336F
#تعریف_کرو EGL_Y_AXIS_NV                     0x3370
#اگر_ختم /* EGL_NV_stream_origin */

#اگر_غیر_تعریف_شدہ EGL_NV_دھارا_remote
#تعریف_کرو EGL_NV_دھارا_remote 1
#تعریف_کرو EGL_دھارا_STATE_INITIALIZING_NV  0x3240
#تعریف_کرو EGL_دھارا_TYPE_NV                0x3241
#تعریف_کرو EGL_دھارا_PROTOCOL_NV            0x3242
#تعریف_کرو EGL_دھارا_ENDPOINT_NV            0x3243
#تعریف_کرو EGL_دھارا_LOCAL_NV               0x3244
#تعریف_کرو EGL_دھارا_پیداکار_NV            0x3247
#تعریف_کرو EGL_دھارا_صارف_NV            0x3248
#تعریف_کرو EGL_دھارا_PROTOCOL_FD_NV         0x3246
#اگر_ختم /* EGL_NV_stream_remote */

#اگر_غیر_تعریف_شدہ EGL_NV_دھارا_reset
#تعریف_کرو EGL_NV_دھارا_reset 1
#تعریف_کرو EGL_SUPPORT_RESET_NV              0x3334
#تعریف_کرو EGL_SUPPORT_REUSE_NV              0x3335
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLRESETSTREAMNVPROC) (EGLDisplay dpy, EGLStreamKHR دھارا);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Reset_دھارا_NV (EGLDisplay dpy, EGLStreamKHR دھارا);
#اگر_ختم
#اگر_ختم /* EGL_NV_stream_reset */

#اگر_غیر_تعریف_شدہ EGL_NV_دھارا_socket
#تعریف_کرو EGL_NV_دھارا_socket 1
#تعریف_کرو EGL_دھارا_PROTOCOL_SOCKET_NV     0x324B
#تعریف_کرو EGL_SOCKET_HANDLE_NV              0x324C
#تعریف_کرو EGL_SOCKET_TYPE_NV                0x324D
#اگر_ختم /* EGL_NV_stream_socket */

#اگر_غیر_تعریف_شدہ EGL_NV_دھارا_socket_inet
#تعریف_کرو EGL_NV_دھارا_socket_inet 1
#تعریف_کرو EGL_SOCKET_TYPE_INET_NV           0x324F
#اگر_ختم /* EGL_NV_stream_socket_inet */

#اگر_غیر_تعریف_شدہ EGL_NV_دھارا_socket_unix
#تعریف_کرو EGL_NV_دھارا_socket_unix 1
#تعریف_کرو EGL_SOCKET_TYPE_UNIX_NV           0x324E
#اگر_ختم /* EGL_NV_stream_socket_unix */

#اگر_غیر_تعریف_شدہ EGL_NV_دھارا_sync
#تعریف_کرو EGL_NV_دھارا_sync 1
#تعریف_کرو EGL_SYNC_NEW_چوکھٹا_NV             0x321F
قسمتعریف EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESTREAMSYNCNVPROC) (EGLDisplay dpy, EGLStreamKHR دھارا, EGLenum type, ثابت EGLint *attrib_list);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncKHR EGLAPIENTRY egl_Create_دھارا_Sync_NV (EGLDisplay dpy, EGLStreamKHR دھارا, EGLenum type, ثابت EGLint *attrib_list);
#اگر_ختم
#اگر_ختم /* EGL_NV_stream_sync */

#اگر_غیر_تعریف_شدہ EGL_NV_sync
#تعریف_کرو EGL_NV_sync 1
قسمتعریف خالی *EGLSyncNV;
قسمتعریف khronos_utime_nanoseconds_t EGLTimeNV;
#اگر_تعریف_شدہ KHRONOS_SUPPORT_INT64
#تعریف_کرو EGL_SYNC_پیشگی_COMMANDS_COMPLETE_NV 0x30E6
#تعریف_کرو EGL_SYNC_حالت_NV                0x30E7
#تعریف_کرو EGL_SIGNALED_NV                   0x30E8
#تعریف_کرو EGL_UNSIGNALED_NV                 0x30E9
#تعریف_کرو EGL_SYNC_FLUSH_COMMANDS_ثنائی_ہندسہ_NV    0x0001
#تعریف_کرو EGL_FOREVER_NV                    0xFFFFFFFFFFFFFFFFull
#تعریف_کرو EGL_ALREADY_SIGNALED_NV           0x30EA
#تعریف_کرو EGL_TIMEOUT_EXPIRED_NV            0x30EB
#تعریف_کرو EGL_CONDITION_SATISFIED_NV        0x30EC
#تعریف_کرو EGL_SYNC_TYPE_NV                  0x30ED
#تعریف_کرو EGL_SYNC_CONDITION_NV             0x30EE
#تعریف_کرو EGL_SYNC_FENCE_NV                 0x30EF
#تعریف_کرو EGL_NO_SYNC_NV                    EGL_CAST(EGLSyncNV,0)
قسمتعریف EGLSyncNV (EGLAPIENTRYP PFNEGLCREATEFENCESYNCNVPROC) (EGLDisplay dpy, EGLenum condition, ثابت EGLint *attrib_list);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCNVPROC) (EGLSyncNV sync);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLFENCENVPROC) (EGLSyncNV sync);
قسمتعریف EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCNVPROC) (EGLSyncNV sync, EGLint flags, EGLTimeNV timeout);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLSIGNALSYNCNVPROC) (EGLSyncNV sync, EGLenum منوال);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLGETSYNCATTRIBNVPROC) (EGLSyncNV sync, EGLint attribute, EGLint *قدر);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncNV EGLAPIENTRY eglCreateFenceSyncNV (EGLDisplay dpy, EGLenum condition, ثابت EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySyncNV (EGLSyncNV sync);
EGLAPI EGLBoolean EGLAPIENTRY eglFenceNV (EGLSyncNV sync);
EGLAPI EGLint EGLAPIENTRY eglClientWaitSyncNV (EGLSyncNV sync, EGLint flags, EGLTimeNV timeout);
EGLAPI EGLBoolean EGLAPIENTRY eglSignalSyncNV (EGLSyncNV sync, EGLenum منوال);
EGLAPI EGLBoolean EGLAPIENTRY eglGetSyncAttribNV (EGLSyncNV sync, EGLint attribute, EGLint *قدر);
#اگر_ختم
#اگر_ختم /* KHRONOS_SUPPORT_INT64 */
#اگر_ختم /* EGL_NV_sync */

#اگر_غیر_تعریف_شدہ EGL_NV_system_وقت
#تعریف_کرو EGL_NV_system_وقت 1
قسمتعریف khronos_utime_nanoseconds_t EGLuint64NV;
#اگر_تعریف_شدہ KHRONOS_SUPPORT_INT64
قسمتعریف EGLuint64NV (EGLAPIENTRYP PFNEGLGETSYSTEMTIMEFREQUENCYNVPROC) (خالی);
قسمتعریف EGLuint64NV (EGLAPIENTRYP PFNEGLGETSYSTEMTIMENVPROC) (خالی);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLuint64NV EGLAPIENTRY egl_Get_System_وقت_Frequency_NV (خالی);
EGLAPI EGLuint64NV EGLAPIENTRY egl_Get_System_وقت_NV (خالی);
#اگر_ختم
#اگر_ختم /* KHRONOS_SUPPORT_INT64 */
#اگر_ختم /* EGL_NV_system_time */

#اگر_غیر_تعریف_شدہ EGL_NV_triple_بفر
#تعریف_کرو EGL_NV_triple_بفر 1
#تعریف_کرو EGL_TRIPLE_بفر_NV              0x3230
#اگر_ختم /* EGL_NV_triple_buffer */

#اگر_غیر_تعریف_شدہ EGL_QNX_image_native_بفر
#تعریف_کرو EGL_QNX_image_native_بفر 1
#تعریف_کرو EGL_NATIVE_بفر_QNX             0x3551
#اگر_ختم /* EGL_QNX_image_native_buffer */

#اگر_غیر_تعریف_شدہ EGL_QNX_platform_screen
#تعریف_کرو EGL_QNX_platform_screen 1
#تعریف_کرو EGL_PLATFORM_SCREEN_QNX           0x3550
#اگر_ختم /* EGL_QNX_platform_screen */

#اگر_غیر_تعریف_شدہ EGL_TIZEN_image_native_بفر
#تعریف_کرو EGL_TIZEN_image_native_بفر 1
#تعریف_کرو EGL_NATIVE_بفر_TIZEN           0x32A0
#اگر_ختم /* EGL_TIZEN_image_native_buffer */

#اگر_غیر_تعریف_شدہ EGL_TIZEN_image_native_surface
#تعریف_کرو EGL_TIZEN_image_native_surface 1
#تعریف_کرو EGL_NATIVE_SURFACE_TIZEN          0x32A1
#اگر_ختم /* EGL_TIZEN_image_native_surface */

#اگر_غیر_تعریف_شدہ EGL_WL_bind_wayland_display
#تعریف_کرو EGL_WL_bind_wayland_display 1
#تعریف_کرو PFNEGLBINDWAYLANDDISPLAYWL PFNEGLBINDWAYLANDDISPLAYWLPROC
#تعریف_کرو PFNEGLUNBINDWAYLANDDISPLAYWL PFNEGLUNBINDWAYLANDDISPLAYWLPROC
#تعریف_کرو PFNEGLQUERYWAYLANDBUFFERWL PFNEGLQUERYWAYLANDBUFFERWLPROC
ساخت wl_display;
ساخت wl_resource;
#تعریف_کرو EGL_WAYLAND_بفر_WL             0x31D5
#تعریف_کرو EGL_WAYLAND_PLANE_WL              0x31D6
#تعریف_کرو EGL_TEXTURE_Y_U_V_WL              0x31D7
#تعریف_کرو EGL_TEXTURE_Y_UV_WL               0x31D8
#تعریف_کرو EGL_TEXTURE_Y_XUXV_WL             0x31D9
#تعریف_کرو EGL_TEXTURE_EXTERNAL_WL           0x31DA
#تعریف_کرو EGL_WAYLAND_Y_INVERTED_WL         0x31DB
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLBINDWAYLANDDISPLAYWLPROC) (EGLDisplay dpy, ساخت wl_display *display);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLUNBINDWAYLANDDISPLAYWLPROC) (EGLDisplay dpy, ساخت wl_display *display);
قسمتعریف EGLBoolean (EGLAPIENTRYP PFNEGLQUERYWAYLANDBUFFERWLPROC) (EGLDisplay dpy, ساخت wl_resource *بفر_2, EGLint attribute, EGLint *قدر);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglBindWaylandDisplayWL (EGLDisplay dpy, ساخت wl_display *display);
EGLAPI EGLBoolean EGLAPIENTRY eglUnbindWaylandDisplayWL (EGLDisplay dpy, ساخت wl_display *display);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Wayland_بفر_WL (EGLDisplay dpy, ساخت wl_resource *بفر_2, EGLint attribute, EGLint *قدر);
#اگر_ختم
#اگر_ختم /* EGL_WL_bind_wayland_display */

#اگر_غیر_تعریف_شدہ EGL_WL_create_wayland_بفر_from_image
#تعریف_کرو EGL_WL_create_wayland_بفر_from_image 1
#تعریف_کرو PFNEGLCREATEWAYLANDBUFFERFROMIMAGEWL PFNEGLCREATEWAYLANDBUFFERFROMIMAGEWLPROC
ساخت wl_بفر;
قسمتعریف ساخت wl_بفر *(EGLAPIENTRYP PFNEGLCREATEWAYLANDBUFFERFROMIMAGEWLPROC) (EGLDisplay dpy, EGLImageKHR image);
#اگر_تعریف_شدہ EGL_EGLEXT_PROTOTYPES
EGLAPI ساخت wl_بفر *EGLAPIENTRY egl_Create_Wayland_بفر_From_Image_WL (EGLDisplay dpy, EGLImageKHR image);
#اگر_ختم
#اگر_ختم /* EGL_WL_create_wayland_buffer_from_image */

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم
