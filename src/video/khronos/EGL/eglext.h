#اگر_تعریف_نشده __eglext_h_
#تعریف_کن __eglext_h_ 1

#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر

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

#تعریف_کن EGL_EGLEXT_نسخه 20260319

/* Generated C header for:
 * API: egl
 * Versions considered: .*
 * Versions emitted: _nomatch_^
 * Default extensions included: egl
 * Additional extensions included: _nomatch_^
 * Extensions removed: _nomatch_^
 */

#اگر_تعریف_نشده EGL_KHR_cl_event
#تعریف_کن EGL_KHR_cl_event 1
#تعریف_کن EGL_CL_EVENT_HANDLE_KHR           0x309C
#تعریف_کن EGL_SYNC_CL_EVENT_KHR             0x30FE
#تعریف_کن EGL_SYNC_CL_EVENT_COMPLETE_KHR    0x30FF
#پایان_اگر /* EGL_KHR_cl_event */

#اگر_تعریف_نشده EGL_KHR_cl_event2
#تعریف_کن EGL_KHR_cl_event2 1
تعريفنوع فراغ *EGLSyncKHR;
تعريفنوع intptr_t EGLAttribKHR;
تعريفنوع EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESYNC64KHRPROC) (EGLDisplay dpy, EGLenum type, ثابت EGLAttribKHR *attrib_list);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncKHR EGLAPIENTRY eglCreateSync64KHR (EGLDisplay dpy, EGLenum type, ثابت EGLAttribKHR *attrib_list);
#پایان_اگر
#پایان_اگر /* EGL_KHR_cl_event2 */

#اگر_تعریف_نشده EGL_KHR_client_get_all_proc_آدرسها
#تعریف_کن EGL_KHR_client_get_all_proc_آدرسها 1
#پایان_اگر /* EGL_KHR_client_get_all_proc_addresses */

#اگر_تعریف_نشده EGL_KHR_config_attribs
#تعریف_کن EGL_KHR_config_attribs 1
#تعریف_کن EGL_CONFORMANT_KHR                0x3042
#تعریف_کن EGL_VG_COLORSPACE_خطی_بیت_KHR  0x0020
#تعریف_کن EGL_VG_ALPHA_FORMAT_PRE_بیت_KHR   0x0040
#پایان_اگر /* EGL_KHR_config_attribs */

#اگر_تعریف_نشده EGL_KHR_context_flush_control
#تعریف_کن EGL_KHR_context_flush_control 1
#تعریف_کن EGL_CONTEXT_RELEASE_BEHAVIOR_NONE_KHR 0
#تعریف_کن EGL_CONTEXT_RELEASE_BEHAVIOR_KHR  0x2097
#تعریف_کن EGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_KHR 0x2098
#پایان_اگر /* EGL_KHR_context_flush_control */

#اگر_تعریف_نشده EGL_KHR_create_context
#تعریف_کن EGL_KHR_create_context 1
#تعریف_کن EGL_CONTEXT_MAJOR_نسخه_KHR     0x3098
#تعریف_کن EGL_CONTEXT_MINOR_نسخه_KHR     0x30FB
#تعریف_کن EGL_CONTEXT_FLAGS_KHR             0x30FC
#تعریف_کن EGL_CONTEXT_OPENGL_PROFILE_ماسک_KHR 0x30FD
#تعریف_کن EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_KHR 0x31BD
#تعریف_کن EGL_NO_RESET_NOTIFICATION_KHR     0x31BE
#تعریف_کن EGL_LOSE_CONTEXT_ON_RESET_KHR     0x31BF
#تعریف_کن EGL_CONTEXT_OPENGL_DEBUG_بیت_KHR  0x00000001
#تعریف_کن EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_بیت_KHR 0x00000002
#تعریف_کن EGL_CONTEXT_OPENGL_ROBUST_ACCESS_بیت_KHR 0x00000004
#تعریف_کن EGL_CONTEXT_OPENGL_CORE_PROFILE_بیت_KHR 0x00000001
#تعریف_کن EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_بیت_KHR 0x00000002
#تعریف_کن EGL_OPENGL_ES3_بیت_KHR            0x00000040
#پایان_اگر /* EGL_KHR_create_context */

#اگر_تعریف_نشده EGL_KHR_create_context_no_error
#تعریف_کن EGL_KHR_create_context_no_error 1
#تعریف_کن EGL_CONTEXT_OPENGL_NO_ERROR_KHR   0x31B3
#پایان_اگر /* EGL_KHR_create_context_no_error */

#اگر_تعریف_نشده EGL_KHR_debug
#تعریف_کن EGL_KHR_debug 1
تعريفنوع فراغ *EGLLabelKHR;
تعريفنوع فراغ *EGLObjectKHR;
تعريفنوع فراغ (EGLAPIENTRY  *EGLDEBUGPROCKHR)(EGLenum error,ثابت حرف *command,EGLint پیام_Type,EGLLabelKHR threadLabel,EGLLabelKHR objectLabel,ثابت حرف* پیام);
#تعریف_کن EGL_OBJECT_THREAD_KHR             0x33B0
#تعریف_کن EGL_OBJECT_DISPLAY_KHR            0x33B1
#تعریف_کن EGL_OBJECT_CONTEXT_KHR            0x33B2
#تعریف_کن EGL_OBJECT_SURFACE_KHR            0x33B3
#تعریف_کن EGL_OBJECT_IMAGE_KHR              0x33B4
#تعریف_کن EGL_OBJECT_SYNC_KHR               0x33B5
#تعریف_کن EGL_OBJECT_جریان_KHR             0x33B6
#تعریف_کن EGL_DEBUG_پیام_CRITICAL_KHR        0x33B9
#تعریف_کن EGL_DEBUG_پیام_ERROR_KHR           0x33BA
#تعریف_کن EGL_DEBUG_پیام_WARN_KHR            0x33BB
#تعریف_کن EGL_DEBUG_پیام_INFO_KHR            0x33BC
#تعریف_کن EGL_DEBUG_CALLBACK_KHR            0x33B8
تعريفنوع EGLint (EGLAPIENTRYP PFNEGLDEBUGMESSAGECONTROLKHRPROC) (EGLDEBUGPROCKHR callback, ثابت EGLAttrib *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEBUGKHRPROC) (EGLint attribute, EGLAttrib *مقدار);
تعريفنوع EGLint (EGLAPIENTRYP PFNEGLLABELOBJECTKHRPROC) (EGLDisplay display, EGLenum objectType, EGLObjectKHR object, EGLLabelKHR label);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLint EGLAPIENTRY egl_Debug_پیام_Control_KHR (EGLDEBUGPROCKHR callback, ثابت EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDebugKHR (EGLint attribute, EGLAttrib *مقدار);
EGLAPI EGLint EGLAPIENTRY eglLabelObjectKHR (EGLDisplay display, EGLenum objectType, EGLObjectKHR object, EGLLabelKHR label);
#پایان_اگر
#پایان_اگر /* EGL_KHR_debug */

#اگر_تعریف_نشده EGL_KHR_display_reference
#تعریف_کن EGL_KHR_display_reference 1
#تعریف_کن EGL_TRACK_REFERENCES_KHR          0x3352
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDISPLAYATTRIBKHRPROC) (EGLDisplay dpy, EGLint name, EGLAttrib *مقدار);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDisplayAttribKHR (EGLDisplay dpy, EGLint name, EGLAttrib *مقدار);
#پایان_اگر
#پایان_اگر /* EGL_KHR_display_reference */

#اگر_تعریف_نشده EGL_KHR_fence_sync
#تعریف_کن EGL_KHR_fence_sync 1
تعريفنوع khronos_utime_nanoseconds_t EGLTimeKHR;
#اگر_تعریف_شده KHRONOS_SUPPORT_INT64
#تعریف_کن EGL_SYNC_پیشین_COMMANDS_COMPLETE_KHR 0x30F0
#تعریف_کن EGL_SYNC_CONDITION_KHR            0x30F8
#تعریف_کن EGL_SYNC_FENCE_KHR                0x30F9
تعريفنوع EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESYNCKHRPROC) (EGLDisplay dpy, EGLenum type, ثابت EGLint *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync);
تعريفنوع EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETSYNCATTRIBKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint attribute, EGLint *مقدار);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncKHR EGLAPIENTRY eglCreateSyncKHR (EGLDisplay dpy, EGLenum type, ثابت EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySyncKHR (EGLDisplay dpy, EGLSyncKHR sync);
EGLAPI EGLint EGLAPIENTRY eglClientWaitSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);
EGLAPI EGLBoolean EGLAPIENTRY eglGetSyncAttribKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint attribute, EGLint *مقدار);
#پایان_اگر
#پایان_اگر /* KHRONOS_SUPPORT_INT64 */
#پایان_اگر /* EGL_KHR_fence_sync */

#اگر_تعریف_نشده EGL_KHR_get_all_proc_آدرسها
#تعریف_کن EGL_KHR_get_all_proc_آدرسها 1
#پایان_اگر /* EGL_KHR_get_all_proc_addresses */

#اگر_تعریف_نشده EGL_KHR_gl_colorspace
#تعریف_کن EGL_KHR_gl_colorspace 1
#تعریف_کن EGL_GL_COLORSPACE_KHR             0x309D
#تعریف_کن EGL_GL_COLORSPACE_SRGB_KHR        0x3089
#تعریف_کن EGL_GL_COLORSPACE_خطی_KHR      0x308A
#پایان_اگر /* EGL_KHR_gl_colorspace */

#اگر_تعریف_نشده EGL_KHR_gl_renderbuffer_image
#تعریف_کن EGL_KHR_gl_renderbuffer_image 1
#تعریف_کن EGL_GL_RENDERBUFFER_KHR           0x30B9
#پایان_اگر /* EGL_KHR_gl_renderbuffer_image */

#اگر_تعریف_نشده EGL_KHR_gl_texture_2D_image
#تعریف_کن EGL_KHR_gl_texture_2D_image 1
#تعریف_کن EGL_GL_TEXTURE_2D_KHR             0x30B1
#تعریف_کن EGL_GL_TEXTURE_LEVEL_KHR          0x30BC
#پایان_اگر /* EGL_KHR_gl_texture_2D_image */

#اگر_تعریف_نشده EGL_KHR_gl_texture_3D_image
#تعریف_کن EGL_KHR_gl_texture_3D_image 1
#تعریف_کن EGL_GL_TEXTURE_3D_KHR             0x30B2
#تعریف_کن EGL_GL_TEXTURE_ZOFFSET_KHR        0x30BD
#پایان_اگر /* EGL_KHR_gl_texture_3D_image */

#اگر_تعریف_نشده EGL_KHR_gl_texture_cubemap_image
#تعریف_کن EGL_KHR_gl_texture_cubemap_image 1
#تعریف_کن EGL_GL_TEXTURE_CUBE_MAP_مثبت_X_KHR 0x30B3
#تعریف_کن EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_X_KHR 0x30B4
#تعریف_کن EGL_GL_TEXTURE_CUBE_MAP_مثبت_Y_KHR 0x30B5
#تعریف_کن EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_KHR 0x30B6
#تعریف_کن EGL_GL_TEXTURE_CUBE_MAP_مثبت_Z_KHR 0x30B7
#تعریف_کن EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_KHR 0x30B8
#پایان_اگر /* EGL_KHR_gl_texture_cubemap_image */

#اگر_تعریف_نشده EGL_KHR_image
#تعریف_کن EGL_KHR_image 1
تعريفنوع فراغ *EGLImageKHR;
#تعریف_کن EGL_NATIVE_PIXMAP_KHR             0x30B0
#تعریف_کن EGL_NO_IMAGE_KHR                  EGL_CAST(EGLImageKHR,0)
تعريفنوع EGLImageKHR (EGLAPIENTRYP PFNEGLCREATEIMAGEKHRPROC) (EGLDisplay dpy, EGLContext ctx, EGLenum هدف, EGLClient_میانگیر میانگیر_2, ثابت EGLint *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYIMAGEKHRPROC) (EGLDisplay dpy, EGLImageKHR image);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLImageKHR EGLAPIENTRY eglCreateImageKHR (EGLDisplay dpy, EGLContext ctx, EGLenum هدف, EGLClient_میانگیر میانگیر_2, ثابت EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyImageKHR (EGLDisplay dpy, EGLImageKHR image);
#پایان_اگر
#پایان_اگر /* EGL_KHR_image */

#اگر_تعریف_نشده EGL_KHR_image_پایه
#تعریف_کن EGL_KHR_image_پایه 1
#تعریف_کن EGL_IMAGE_PRESERVED_KHR           0x30D2
#پایان_اگر /* EGL_KHR_image_base */

#اگر_تعریف_نشده EGL_KHR_image_pixmap
#تعریف_کن EGL_KHR_image_pixmap 1
#پایان_اگر /* EGL_KHR_image_pixmap */

#اگر_تعریف_نشده EGL_KHR_قفل_surface
#تعریف_کن EGL_KHR_قفل_surface 1
#تعریف_کن EGL_READ_SURFACE_بیت_KHR          0x0001
#تعریف_کن EGL_WRITE_SURFACE_بیت_KHR         0x0002
#تعریف_کن EGL_قفل_SURFACE_بیت_KHR          0x0080
#تعریف_کن EGL_OPTIMAL_FORMAT_بیت_KHR        0x0100
#تعریف_کن EGL_تطابق_FORMAT_KHR              0x3043
#تعریف_کن EGL_FORMAT_RGB_565_EXACT_KHR      0x30C0
#تعریف_کن EGL_FORMAT_RGB_565_KHR            0x30C1
#تعریف_کن EGL_FORMAT_RGBA_8888_EXACT_KHR    0x30C2
#تعریف_کن EGL_FORMAT_RGBA_8888_KHR          0x30C3
#تعریف_کن EGL_MAP_PRESERVE_PIXELS_KHR       0x30C4
#تعریف_کن EGL_قفل_USAGE_HINT_KHR           0x30C5
#تعریف_کن EGL_BITMAP_اشاره_گر_KHR            0x30C6
#تعریف_کن EGL_BITMAP_PITCH_KHR              0x30C7
#تعریف_کن EGL_BITMAP_ORIGIN_KHR             0x30C8
#تعریف_کن EGL_BITMAP_PIXEL_RED_جابه_جایی_KHR   0x30C9
#تعریف_کن EGL_BITMAP_PIXEL_GREEN_جابه_جایی_KHR 0x30CA
#تعریف_کن EGL_BITMAP_PIXEL_BLUE_جابه_جایی_KHR  0x30CB
#تعریف_کن EGL_BITMAP_PIXEL_ALPHA_جابه_جایی_KHR 0x30CC
#تعریف_کن EGL_BITMAP_PIXEL_LUMINANCE_جابه_جایی_KHR 0x30CD
#تعریف_کن EGL_پایینی_چپ_KHR                0x30CE
#تعریف_کن EGL_فوقانی_چپ_KHR                0x30CF
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLLOCKSURFACEKHRPROC) (EGLDisplay dpy, EGLSurface surface, ثابت EGLint *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLUNLOCKSURFACEKHRPROC) (EGLDisplay dpy, EGLSurface surface);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_قفل_Surface_KHR (EGLDisplay dpy, EGLSurface surface, ثابت EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglUnlockSurfaceKHR (EGLDisplay dpy, EGLSurface surface);
#پایان_اگر
#پایان_اگر /* EGL_KHR_lock_surface */

#اگر_تعریف_نشده EGL_KHR_قفل_surface2
#تعریف_کن EGL_KHR_قفل_surface2 1
#تعریف_کن EGL_BITMAP_PIXEL_اندازه_KHR         0x3110
#پایان_اگر /* EGL_KHR_lock_surface2 */

#اگر_تعریف_نشده EGL_KHR_قفل_surface3
#تعریف_کن EGL_KHR_قفل_surface3 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSURFACE64KHRPROC) (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLAttribKHR *مقدار);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQuerySurface64KHR (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLAttribKHR *مقدار);
#پایان_اگر
#پایان_اگر /* EGL_KHR_lock_surface3 */

#اگر_تعریف_نشده EGL_KHR_mutable_render_میانگیر
#تعریف_کن EGL_KHR_mutable_render_میانگیر 1
#تعریف_کن EGL_MUTABLE_RENDER_میانگیر_بیت_KHR 0x1000
#پایان_اگر /* EGL_KHR_mutable_render_buffer */

#اگر_تعریف_نشده EGL_KHR_no_config_context
#تعریف_کن EGL_KHR_no_config_context 1
#تعریف_کن EGL_NO_CONFIG_KHR                 EGL_CAST(EGLConfig,0)
#پایان_اگر /* EGL_KHR_no_config_context */

#اگر_تعریف_نشده EGL_KHR_partial_update
#تعریف_کن EGL_KHR_partial_update 1
#تعریف_کن EGL_میانگیر_AGE_KHR                0x313D
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSETDAMAGEREGIONKHRPROC) (EGLDisplay dpy, EGLSurface surface, EGLint *rects, EGLint n_rects);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_مجموعه_Damage_Region_KHR (EGLDisplay dpy, EGLSurface surface, EGLint *rects, EGLint n_rects);
#پایان_اگر
#پایان_اگر /* EGL_KHR_partial_update */

#اگر_تعریف_نشده EGL_KHR_platform_android
#تعریف_کن EGL_KHR_platform_android 1
#تعریف_کن EGL_PLATFORM_ANDROID_KHR          0x3141
#پایان_اگر /* EGL_KHR_platform_android */

#اگر_تعریف_نشده EGL_KHR_platform_gbm
#تعریف_کن EGL_KHR_platform_gbm 1
#تعریف_کن EGL_PLATFORM_GBM_KHR              0x31D7
#پایان_اگر /* EGL_KHR_platform_gbm */

#اگر_تعریف_نشده EGL_KHR_platform_wayland
#تعریف_کن EGL_KHR_platform_wayland 1
#تعریف_کن EGL_PLATFORM_WAYLAND_KHR          0x31D8
#پایان_اگر /* EGL_KHR_platform_wayland */

#اگر_تعریف_نشده EGL_KHR_platform_x11
#تعریف_کن EGL_KHR_platform_x11 1
#تعریف_کن EGL_PLATFORM_X11_KHR              0x31D5
#تعریف_کن EGL_PLATFORM_X11_SCREEN_KHR       0x31D6
#پایان_اگر /* EGL_KHR_platform_x11 */

#اگر_تعریف_نشده EGL_KHR_reusable_sync
#تعریف_کن EGL_KHR_reusable_sync 1
#اگر_تعریف_شده KHRONOS_SUPPORT_INT64
#تعریف_کن EGL_SYNC_وضعیت_KHR               0x30F1
#تعریف_کن EGL_SIGNALED_KHR                  0x30F2
#تعریف_کن EGL_UNSIGNALED_KHR                0x30F3
#تعریف_کن EGL_TIMEOUT_EXPIRED_KHR           0x30F5
#تعریف_کن EGL_CONDITION_SATISFIED_KHR       0x30F6
#تعریف_کن EGL_SYNC_TYPE_KHR                 0x30F7
#تعریف_کن EGL_SYNC_REUSABLE_KHR             0x30FA
#تعریف_کن EGL_SYNC_FLUSH_COMMANDS_بیت_KHR   0x0001
#تعریف_کن EGL_FOREVER_KHR                   0xFFFFFFFFFFFFFFFFull
#تعریف_کن EGL_NO_SYNC_KHR                   EGL_CAST(EGLSyncKHR,0)
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSIGNALSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLenum نما);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglSignalSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLenum نما);
#پایان_اگر
#پایان_اگر /* KHRONOS_SUPPORT_INT64 */
#پایان_اگر /* EGL_KHR_reusable_sync */

#اگر_تعریف_نشده EGL_KHR_جریان
#تعریف_کن EGL_KHR_جریان 1
تعريفنوع فراغ *EGLStreamKHR;
تعريفنوع khronos_uint64_t EGLuint64KHR;
#اگر_تعریف_شده KHRONOS_SUPPORT_INT64
#تعریف_کن EGL_NO_جریان_KHR                 EGL_CAST(EGLStreamKHR,0)
#تعریف_کن EGL_مصرفکننده_LATENCY_USEC_KHR     0x3210
#تعریف_کن EGL_تولیدکننده_قاب_KHR            0x3212
#تعریف_کن EGL_مصرفکننده_قاب_KHR            0x3213
#تعریف_کن EGL_جریان_STATE_KHR              0x3214
#تعریف_کن EGL_جریان_STATE_CREATED_KHR      0x3215
#تعریف_کن EGL_جریان_STATE_CONNECTING_KHR   0x3216
#تعریف_کن EGL_جریان_STATE_خالی_KHR        0x3217
#تعریف_کن EGL_جریان_STATE_NEW_قاب_موجود_KHR 0x3218
#تعریف_کن EGL_جریان_STATE_OLD_قاب_موجود_KHR 0x3219
#تعریف_کن EGL_جریان_STATE_DISCONNECTED_KHR 0x321A
#تعریف_کن EGL_BAD_جریان_KHR                0x321B
#تعریف_کن EGL_BAD_STATE_KHR                 0x321C
تعريفنوع EGLStreamKHR (EGLAPIENTRYP PFNEGLCREATESTREAMKHRPROC) (EGLDisplay dpy, ثابت EGLint *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSTREAMKHRPROC) (EGLDisplay dpy, EGLStreamKHR جریان);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR جریان, EGLenum attribute, EGLint مقدار);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMKHRPROC) (EGLDisplay dpy, EGLStreamKHR جریان, EGLenum attribute, EGLint *مقدار);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMU64KHRPROC) (EGLDisplay dpy, EGLStreamKHR جریان, EGLenum attribute, EGLuint64KHR *مقدار);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLStreamKHR EGLAPIENTRY egl_Create_جریان_KHR (EGLDisplay dpy, ثابت EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY egl_Destroy_جریان_KHR (EGLDisplay dpy, EGLStreamKHR جریان);
EGLAPI EGLBoolean EGLAPIENTRY egl_جریان_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR جریان, EGLenum attribute, EGLint مقدار);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_جریان_KHR (EGLDisplay dpy, EGLStreamKHR جریان, EGLenum attribute, EGLint *مقدار);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryStreamu64KHR (EGLDisplay dpy, EGLStreamKHR جریان, EGLenum attribute, EGLuint64KHR *مقدار);
#پایان_اگر
#پایان_اگر /* KHRONOS_SUPPORT_INT64 */
#پایان_اگر /* EGL_KHR_stream */

#اگر_تعریف_نشده EGL_KHR_جریان_attrib
#تعریف_کن EGL_KHR_جریان_attrib 1
#اگر_تعریف_شده KHRONOS_SUPPORT_INT64
تعريفنوع EGLStreamKHR (EGLAPIENTRYP PFNEGLCREATESTREAMATTRIBKHRPROC) (EGLDisplay dpy, ثابت EGLAttrib *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSETSTREAMATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR جریان, EGLenum attribute, EGLAttrib مقدار);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR جریان, EGLenum attribute, EGLAttrib *مقدار);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERACQUIREATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR جریان, ثابت EGLAttrib *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERRELEASEATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR جریان, ثابت EGLAttrib *attrib_list);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLStreamKHR EGLAPIENTRY egl_Create_جریان_Attrib_KHR (EGLDisplay dpy, ثابت EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY egl_مجموعه_جریان_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR جریان, EGLenum attribute, EGLAttrib مقدار);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_جریان_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR جریان, EGLenum attribute, EGLAttrib *مقدار);
EGLAPI EGLBoolean EGLAPIENTRY egl_جریان_مصرفکننده_Acquire_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR جریان, ثابت EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY egl_جریان_مصرفکننده_Release_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR جریان, ثابت EGLAttrib *attrib_list);
#پایان_اگر
#پایان_اگر /* KHRONOS_SUPPORT_INT64 */
#پایان_اگر /* EGL_KHR_stream_attrib */

#اگر_تعریف_نشده EGL_KHR_جریان_مصرفکننده_gltexture
#تعریف_کن EGL_KHR_جریان_مصرفکننده_gltexture 1
#اگر_تعریف_شده EGL_KHR_جریان
#تعریف_کن EGL_مصرفکننده_ACQUIRE_TIMEOUT_USEC_KHR 0x321E
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALKHRPROC) (EGLDisplay dpy, EGLStreamKHR جریان);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERACQUIREKHRPROC) (EGLDisplay dpy, EGLStreamKHR جریان);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERRELEASEKHRPROC) (EGLDisplay dpy, EGLStreamKHR جریان);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_جریان_مصرفکننده_GLTexture_External_KHR (EGLDisplay dpy, EGLStreamKHR جریان);
EGLAPI EGLBoolean EGLAPIENTRY egl_جریان_مصرفکننده_Acquire_KHR (EGLDisplay dpy, EGLStreamKHR جریان);
EGLAPI EGLBoolean EGLAPIENTRY egl_جریان_مصرفکننده_Release_KHR (EGLDisplay dpy, EGLStreamKHR جریان);
#پایان_اگر
#پایان_اگر /* EGL_KHR_stream */
#پایان_اگر /* EGL_KHR_stream_consumer_gltexture */

#اگر_تعریف_نشده EGL_KHR_جریان_cross_process_fd
#تعریف_کن EGL_KHR_جریان_cross_process_fd 1
تعريفنوع صحيح EGLNativeFileDescriptorKHR;
#اگر_تعریف_شده EGL_KHR_جریان
#تعریف_کن EGL_NO_FILE_DESCRIPTOR_KHR        EGL_CAST(EGLNativeFileDescriptorKHR,-1)
تعريفنوع EGLNativeFileDescriptorKHR (EGLAPIENTRYP PFNEGLGETSTREAMFILEDESCRIPTORKHRPROC) (EGLDisplay dpy, EGLStreamKHR جریان);
تعريفنوع EGLStreamKHR (EGLAPIENTRYP PFNEGLCREATESTREAMFROMFILEDESCRIPTORKHRPROC) (EGLDisplay dpy, EGLNativeFileDescriptorKHR file_descriptor);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLNativeFileDescriptorKHR EGLAPIENTRY egl_Get_جریان_File_Descriptor_KHR (EGLDisplay dpy, EGLStreamKHR جریان);
EGLAPI EGLStreamKHR EGLAPIENTRY egl_Create_جریان_From_File_Descriptor_KHR (EGLDisplay dpy, EGLNativeFileDescriptorKHR file_descriptor);
#پایان_اگر
#پایان_اگر /* EGL_KHR_stream */
#پایان_اگر /* EGL_KHR_stream_cross_process_fd */

#اگر_تعریف_نشده EGL_KHR_جریان_fifo
#تعریف_کن EGL_KHR_جریان_fifo 1
#اگر_تعریف_شده EGL_KHR_جریان
#تعریف_کن EGL_جریان_FIFO_درازی_KHR        0x31FC
#تعریف_کن EGL_جریان_زمان_NOW_KHR           0x31FD
#تعریف_کن EGL_جریان_زمان_مصرفکننده_KHR      0x31FE
#تعریف_کن EGL_جریان_زمان_تولیدکننده_KHR      0x31FF
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMTIMEKHRPROC) (EGLDisplay dpy, EGLStreamKHR جریان, EGLenum attribute, EGLTimeKHR *مقدار);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_جریان_زمان_KHR (EGLDisplay dpy, EGLStreamKHR جریان, EGLenum attribute, EGLTimeKHR *مقدار);
#پایان_اگر
#پایان_اگر /* EGL_KHR_stream */
#پایان_اگر /* EGL_KHR_stream_fifo */

#اگر_تعریف_نشده EGL_KHR_جریان_تولیدکننده_aldatalocator
#تعریف_کن EGL_KHR_جریان_تولیدکننده_aldatalocator 1
#اگر_تعریف_شده EGL_KHR_جریان
#پایان_اگر /* EGL_KHR_stream */
#پایان_اگر /* EGL_KHR_stream_producer_aldatalocator */

#اگر_تعریف_نشده EGL_KHR_جریان_تولیدکننده_eglsurface
#تعریف_کن EGL_KHR_جریان_تولیدکننده_eglsurface 1
#اگر_تعریف_شده EGL_KHR_جریان
#تعریف_کن EGL_جریان_بیت_KHR                0x0800
تعريفنوع EGLSurface (EGLAPIENTRYP PFNEGLCREATESTREAMPRODUCERSURFACEKHRPROC) (EGLDisplay dpy, EGLConfig config, EGLStreamKHR جریان, ثابت EGLint *attrib_list);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSurface EGLAPIENTRY egl_Create_جریان_تولیدکننده_Surface_KHR (EGLDisplay dpy, EGLConfig config, EGLStreamKHR جریان, ثابت EGLint *attrib_list);
#پایان_اگر
#پایان_اگر /* EGL_KHR_stream */
#پایان_اگر /* EGL_KHR_stream_producer_eglsurface */

#اگر_تعریف_نشده EGL_KHR_surfaceless_context
#تعریف_کن EGL_KHR_surfaceless_context 1
#پایان_اگر /* EGL_KHR_surfaceless_context */

#اگر_تعریف_نشده EGL_KHR_جابجا_buffers_with_damage
#تعریف_کن EGL_KHR_جابجا_buffers_with_damage 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSWITHDAMAGEKHRPROC) (EGLDisplay dpy, EGLSurface surface, ثابت EGLint *rects, EGLint n_rects);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_جابجا_Buffers_With_Damage_KHR (EGLDisplay dpy, EGLSurface surface, ثابت EGLint *rects, EGLint n_rects);
#پایان_اگر
#پایان_اگر /* EGL_KHR_swap_buffers_with_damage */

#اگر_تعریف_نشده EGL_KHR_vg_والد_image
#تعریف_کن EGL_KHR_vg_والد_image 1
#تعریف_کن EGL_VG_والد_IMAGE_KHR           0x30BA
#پایان_اگر /* EGL_KHR_vg_parent_image */

#اگر_تعریف_نشده EGL_KHR_wait_sync
#تعریف_کن EGL_KHR_wait_sync 1
تعريفنوع EGLint (EGLAPIENTRYP PFNEGLWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLint EGLAPIENTRY eglWaitSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
#پایان_اگر
#پایان_اگر /* EGL_KHR_wait_sync */

#اگر_تعریف_نشده EGL_ANDROID_GLES_layers
#تعریف_کن EGL_ANDROID_GLES_layers 1
#پایان_اگر /* EGL_ANDROID_GLES_layers */

#اگر_تعریف_نشده EGL_ANDROID_blob_cache
#تعریف_کن EGL_ANDROID_blob_cache 1
تعريفنوع khronos_ssize_t EGLsizeiANDROID;
تعريفنوع فراغ (*EGLSetBlobFuncANDROID) (ثابت فراغ *کلید, EGLsizeiANDROID کلید_اندازه_2, ثابت فراغ *مقدار, EGLsizeiANDROID مقدار_اندازه_2);
تعريفنوع EGLsizeiANDROID (*EGLGetBlobFuncANDROID) (ثابت فراغ *کلید, EGLsizeiANDROID کلید_اندازه_2, فراغ *مقدار, EGLsizeiANDROID مقدار_اندازه_2);
تعريفنوع فراغ (EGLAPIENTRYP PFNEGLSETBLOBCACHEFUNCSANDROIDPROC) (EGLDisplay dpy, EGLSetBlobFuncANDROID مجموعه, EGLGetBlobFuncANDROID get);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI فراغ EGLAPIENTRY egl_مجموعه_Blob_Cache_Funcs_ANDROID (EGLDisplay dpy, EGLSetBlobFuncANDROID مجموعه, EGLGetBlobFuncANDROID get);
#پایان_اگر
#پایان_اگر /* EGL_ANDROID_blob_cache */

#اگر_تعریف_نشده EGL_ANDROID_create_native_client_میانگیر
#تعریف_کن EGL_ANDROID_create_native_client_میانگیر 1
#تعریف_کن EGL_NATIVE_میانگیر_USAGE_ANDROID   0x3143
#تعریف_کن EGL_NATIVE_میانگیر_USAGE_PROTECTED_بیت_ANDROID 0x00000001
#تعریف_کن EGL_NATIVE_میانگیر_USAGE_RENDERBUFFER_بیت_ANDROID 0x00000002
#تعریف_کن EGL_NATIVE_میانگیر_USAGE_TEXTURE_بیت_ANDROID 0x00000004
تعريفنوع EGLClient_میانگیر (EGLAPIENTRYP PFNEGLCREATENATIVECLIENTBUFFERANDROIDPROC) (ثابت EGLint *attrib_list);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLClient_میانگیر EGLAPIENTRY egl_Create_Native_Client_میانگیر_ANDROID (ثابت EGLint *attrib_list);
#پایان_اگر
#پایان_اگر /* EGL_ANDROID_create_native_client_buffer */

#اگر_تعریف_نشده EGL_ANDROID_framebuffer_هدف
#تعریف_کن EGL_ANDROID_framebuffer_هدف 1
#تعریف_کن EGL_FRAMEBUFFER_هدف_ANDROID    0x3147
#پایان_اگر /* EGL_ANDROID_framebuffer_target */

#اگر_تعریف_نشده EGL_ANDROID_front_میانگیر_auto_refresh
#تعریف_کن EGL_ANDROID_front_میانگیر_auto_refresh 1
#تعریف_کن EGL_FRONT_میانگیر_AUTO_REFRESH_ANDROID 0x314C
#پایان_اگر /* EGL_ANDROID_front_buffer_auto_refresh */

#اگر_تعریف_نشده EGL_ANDROID_get_قاب_timestamps
#تعریف_کن EGL_ANDROID_get_قاب_timestamps 1
تعريفنوع khronos_stime_nanoseconds_t EGLnsecsANDROID;
#تعریف_کن EGL_TIMESTAMP_PENDING_ANDROID     EGL_CAST(EGLnsecsANDROID,-2)
#تعریف_کن EGL_TIMESTAMP_INVALID_ANDROID     EGL_CAST(EGLnsecsANDROID,-1)
#تعریف_کن EGL_TIMESTAMPS_ANDROID            0x3430
#تعریف_کن EGL_مرکب_DEADLINE_ANDROID    0x3431
#تعریف_کن EGL_مرکب_INTERVAL_ANDROID    0x3432
#تعریف_کن EGL_مرکب_مقصد_PRESENT_LATENCY_ANDROID 0x3433
#تعریف_کن EGL_REQUESTED_PRESENT_زمان_ANDROID 0x3434
#تعریف_کن EGL_RENDERING_COMPLETE_زمان_ANDROID 0x3435
#تعریف_کن EGL_COMPOSITION_LATCH_زمان_ANDROID 0x3436
#تعریف_کن EGL_اولی_COMPOSITION_شروع_زمان_ANDROID 0x3437
#تعریف_کن EGL_آخرین_COMPOSITION_شروع_زمان_ANDROID 0x3438
#تعریف_کن EGL_اولی_COMPOSITION_GPU_پایانیافته_زمان_ANDROID 0x3439
#تعریف_کن EGL_DISPLAY_PRESENT_زمان_ANDROID  0x343A
#تعریف_کن EGL_خارج_از_صف_READY_زمان_ANDROID    0x343B
#تعریف_کن EGL_READS_انجامشده_زمان_ANDROID       0x343C
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETCOMPOSITORTIMINGSUPPORTEDANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLint name);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETCOMPOSITORTIMINGANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLint رقم_Timestamps,  ثابت EGLint *نامها, EGLnsecsANDROID *مقادیر);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETNEXTFRAMEIDANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR *قاب_Id);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETFRAMETIMESTAMPSUPPORTEDANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLint timestamp);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETFRAMETIMESTAMPSANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR قاب_Id, EGLint رقم_Timestamps,  ثابت EGLint *timestamps, EGLnsecsANDROID *مقادیر);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglGetCompositorTimingSupportedANDROID (EGLDisplay dpy, EGLSurface surface, EGLint name);
EGLAPI EGLBoolean EGLAPIENTRY eglGetCompositorTimingANDROID (EGLDisplay dpy, EGLSurface surface, EGLint رقم_Timestamps,  ثابت EGLint *نامها, EGLnsecsANDROID *مقادیر);
EGLAPI EGLBoolean EGLAPIENTRY egl_Get_بعدی_قاب_Id_ANDROID (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR *قاب_Id);
EGLAPI EGLBoolean EGLAPIENTRY egl_Get_قاب_Timestamp_Supported_ANDROID (EGLDisplay dpy, EGLSurface surface, EGLint timestamp);
EGLAPI EGLBoolean EGLAPIENTRY egl_Get_قاب_Timestamps_ANDROID (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR قاب_Id, EGLint رقم_Timestamps,  ثابت EGLint *timestamps, EGLnsecsANDROID *مقادیر);
#پایان_اگر
#پایان_اگر /* EGL_ANDROID_get_frame_timestamps */

#اگر_تعریف_نشده EGL_ANDROID_get_native_client_میانگیر
#تعریف_کن EGL_ANDROID_get_native_client_میانگیر 1
بنية AHardware_میانگیر;
تعريفنوع EGLClient_میانگیر (EGLAPIENTRYP PFNEGLGETNATIVECLIENTBUFFERANDROIDPROC) (ثابت بنية AHardware_میانگیر *میانگیر_2);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLClient_میانگیر EGLAPIENTRY egl_Get_Native_Client_میانگیر_ANDROID (ثابت بنية AHardware_میانگیر *میانگیر_2);
#پایان_اگر
#پایان_اگر /* EGL_ANDROID_get_native_client_buffer */

#اگر_تعریف_نشده EGL_ANDROID_image_native_میانگیر
#تعریف_کن EGL_ANDROID_image_native_میانگیر 1
#تعریف_کن EGL_NATIVE_میانگیر_ANDROID         0x3140
#پایان_اگر /* EGL_ANDROID_image_native_buffer */

#اگر_تعریف_نشده EGL_ANDROID_native_fence_sync
#تعریف_کن EGL_ANDROID_native_fence_sync 1
#تعریف_کن EGL_SYNC_NATIVE_FENCE_ANDROID     0x3144
#تعریف_کن EGL_SYNC_NATIVE_FENCE_FD_ANDROID  0x3145
#تعریف_کن EGL_SYNC_NATIVE_FENCE_SIGNALED_ANDROID 0x3146
#تعریف_کن EGL_NO_NATIVE_FENCE_FD_ANDROID    -1
تعريفنوع EGLint (EGLAPIENTRYP PFNEGLDUPNATIVEFENCEFDANDROIDPROC) (EGLDisplay dpy, EGLSyncKHR sync);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLint EGLAPIENTRY eglDupNativeFenceFDANDROID (EGLDisplay dpy, EGLSyncKHR sync);
#پایان_اگر
#پایان_اگر /* EGL_ANDROID_native_fence_sync */

#اگر_تعریف_نشده EGL_ANDROID_presentation_زمان
#تعریف_کن EGL_ANDROID_presentation_زمان 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLPRESENTATIONTIMEANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLnsecsANDROID زمان);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Presentation_زمان_ANDROID (EGLDisplay dpy, EGLSurface surface, EGLnsecsANDROID زمان);
#پایان_اگر
#پایان_اگر /* EGL_ANDROID_presentation_time */

#اگر_تعریف_نشده EGL_ANDROID_recordable
#تعریف_کن EGL_ANDROID_recordable 1
#تعریف_کن EGL_RECORDABLE_ANDROID            0x3142
#پایان_اگر /* EGL_ANDROID_recordable */

#اگر_تعریف_نشده EGL_ANDROID_telemetry_hint
#تعریف_کن EGL_ANDROID_telemetry_hint 1
#تعریف_کن EGL_TELEMETRY_HINT_ANDROID        0x3570
#پایان_اگر /* EGL_ANDROID_telemetry_hint */

#اگر_تعریف_نشده EGL_ANGLE_d3d_share_handle_client_میانگیر
#تعریف_کن EGL_ANGLE_d3d_share_handle_client_میانگیر 1
#تعریف_کن EGL_D3D_TEXTURE_2D_SHARE_HANDLE_ANGLE 0x3200
#پایان_اگر /* EGL_ANGLE_d3d_share_handle_client_buffer */

#اگر_تعریف_نشده EGL_ANGLE_device_d3d
#تعریف_کن EGL_ANGLE_device_d3d 1
#تعریف_کن EGL_D3D9_DEVICE_ANGLE             0x33A0
#تعریف_کن EGL_D3D11_DEVICE_ANGLE            0x33A1
#پایان_اگر /* EGL_ANGLE_device_d3d */

#اگر_تعریف_نشده EGL_ANGLE_query_surface_اشاره_گر
#تعریف_کن EGL_ANGLE_query_surface_اشاره_گر 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSURFACEPOINTERANGLEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint attribute, فراغ **مقدار);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Surface_اشاره_گر_ANGLE (EGLDisplay dpy, EGLSurface surface, EGLint attribute, فراغ **مقدار);
#پایان_اگر
#پایان_اگر /* EGL_ANGLE_query_surface_pointer */

#اگر_تعریف_نشده EGL_ANGLE_surface_d3d_texture_2d_share_handle
#تعریف_کن EGL_ANGLE_surface_d3d_texture_2d_share_handle 1
#پایان_اگر /* EGL_ANGLE_surface_d3d_texture_2d_share_handle */

#اگر_تعریف_نشده EGL_ANGLE_sync_control_نرخ
#تعریف_کن EGL_ANGLE_sync_control_نرخ 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETMSCRATEANGLEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint *numerator, EGLint *denominator);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Get_Msc_نرخ_ANGLE (EGLDisplay dpy, EGLSurface surface, EGLint *numerator, EGLint *denominator);
#پایان_اگر
#پایان_اگر /* EGL_ANGLE_sync_control_rate */

#اگر_تعریف_نشده EGL_ANGLE_پنجره_fixed_اندازه
#تعریف_کن EGL_ANGLE_پنجره_fixed_اندازه 1
#تعریف_کن EGL_FIXED_اندازه_ANGLE              0x3201
#پایان_اگر /* EGL_ANGLE_window_fixed_size */

#اگر_تعریف_نشده EGL_ARM_image_format
#تعریف_کن EGL_ARM_image_format 1
#تعریف_کن EGL_COLOR_COMPONENT_TYPE_UNSIGNED_INTEGER_ARM 0x3287
#تعریف_کن EGL_COLOR_COMPONENT_TYPE_INTEGER_ARM 0x3288
#پایان_اگر /* EGL_ARM_image_format */

#اگر_تعریف_نشده EGL_ARM_implicit_external_sync
#تعریف_کن EGL_ARM_implicit_external_sync 1
#تعریف_کن EGL_SYNC_پیشین_COMMANDS_IMPLICIT_EXTERNAL_ARM 0x328A
#پایان_اگر /* EGL_ARM_implicit_external_sync */

#اگر_تعریف_نشده EGL_ARM_pixmap_multisample_discard
#تعریف_کن EGL_ARM_pixmap_multisample_discard 1
#تعریف_کن EGL_DISCARD_SAMPLES_ARM           0x3286
#پایان_اگر /* EGL_ARM_pixmap_multisample_discard */

#اگر_تعریف_نشده EGL_EXT_bind_مقصد_front
#تعریف_کن EGL_EXT_bind_مقصد_front 1
#تعریف_کن EGL_FRONT_میانگیر_EXT              0x3464
#پایان_اگر /* EGL_EXT_bind_to_front */

#اگر_تعریف_نشده EGL_EXT_میانگیر_age
#تعریف_کن EGL_EXT_میانگیر_age 1
#تعریف_کن EGL_میانگیر_AGE_EXT                0x313D
#پایان_اگر /* EGL_EXT_buffer_age */

#اگر_تعریف_نشده EGL_EXT_client_extensions
#تعریف_کن EGL_EXT_client_extensions 1
#پایان_اگر /* EGL_EXT_client_extensions */

#اگر_تعریف_نشده EGL_EXT_client_sync
#تعریف_کن EGL_EXT_client_sync 1
#تعریف_کن EGL_SYNC_CLIENT_EXT               0x3364
#تعریف_کن EGL_SYNC_CLIENT_SIGNAL_EXT        0x3365
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLCLIENTSIGNALSYNCEXTPROC) (EGLDisplay dpy, EGLSync sync, ثابت EGLAttrib *attrib_list);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglClientSignalSyncEXT (EGLDisplay dpy, EGLSync sync, ثابت EGLAttrib *attrib_list);
#پایان_اگر
#پایان_اگر /* EGL_EXT_client_sync */

#اگر_تعریف_نشده EGL_EXT_compositor
#تعریف_کن EGL_EXT_compositor 1
#تعریف_کن EGL_PRIMARY_COMPOSITOR_CONTEXT_EXT 0x3460
#تعریف_کن EGL_EXTERNAL_REF_ID_EXT           0x3461
#تعریف_کن EGL_COMPOSITOR_DROP_NEWEST_قاب_EXT 0x3462
#تعریف_کن EGL_COMPOSITOR_KEEP_NEWEST_قاب_EXT 0x3463
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETCONTEXTLISTEXTPROC) (ثابت EGLint *external_ref_ids, EGLint رقم_entries);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETCONTEXTATTRIBUTESEXTPROC) (EGLint external_ref_id, ثابت EGLint *context_صفات, EGLint رقم_entries);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETWINDOWLISTEXTPROC) (EGLint external_ref_id, ثابت EGLint *external_win_ids, EGLint رقم_entries);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETWINDOWATTRIBUTESEXTPROC) (EGLint external_win_id, ثابت EGLint *پنجره_صفات, EGLint رقم_entries);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORBINDTEXWINDOWEXTPROC) (EGLint external_win_id);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETSIZEEXTPROC) (EGLint external_win_id, EGLint عرض, EGLint ارتفاع);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSWAPPOLICYEXTPROC) (EGLint external_win_id, EGLint policy);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_مجموعه_Context_List_EXT (ثابت EGLint *external_ref_ids, EGLint رقم_entries);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_مجموعه_Context_صفات_EXT (EGLint external_ref_id, ثابت EGLint *context_صفات, EGLint رقم_entries);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_مجموعه_پنجره_List_EXT (EGLint external_ref_id, ثابت EGLint *external_win_ids, EGLint رقم_entries);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_مجموعه_پنجره_صفات_EXT (EGLint external_win_id, ثابت EGLint *پنجره_صفات, EGLint رقم_entries);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_Bind_Tex_پنجره_EXT (EGLint external_win_id);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_مجموعه_اندازه_EXT (EGLint external_win_id, EGLint عرض, EGLint ارتفاع);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_جابجا_Policy_EXT (EGLint external_win_id, EGLint policy);
#پایان_اگر
#پایان_اگر /* EGL_EXT_compositor */

#اگر_تعریف_نشده EGL_EXT_config_select_گروه
#تعریف_کن EGL_EXT_config_select_گروه 1
#تعریف_کن EGL_CONFIG_SELECT_گروه_EXT       0x34C0
#پایان_اگر /* EGL_EXT_config_select_group */

#اگر_تعریف_نشده EGL_EXT_create_context_robustness
#تعریف_کن EGL_EXT_create_context_robustness 1
#تعریف_کن EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT 0x30BF
#تعریف_کن EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_EXT 0x3138
#تعریف_کن EGL_NO_RESET_NOTIFICATION_EXT     0x31BE
#تعریف_کن EGL_LOSE_CONTEXT_ON_RESET_EXT     0x31BF
#پایان_اگر /* EGL_EXT_create_context_robustness */

#اگر_تعریف_نشده EGL_EXT_device_پایه
#تعریف_کن EGL_EXT_device_پایه 1
تعريفنوع فراغ *EGLDeviceEXT;
#تعریف_کن EGL_NO_DEVICE_EXT                 EGL_CAST(EGLDeviceEXT,0)
#تعریف_کن EGL_BAD_DEVICE_EXT                0x322B
#تعریف_کن EGL_DEVICE_EXT                    0x322C
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICEATTRIBEXTPROC) (EGLDeviceEXT device, EGLint attribute, EGLAttrib *مقدار);
تعريفنوع ثابت حرف *(EGLAPIENTRYP PFNEGLQUERYDEVICESTRINGEXTPROC) (EGLDeviceEXT device, EGLint name);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICESEXTPROC) (EGLint max_devices, EGLDeviceEXT *devices, EGLint *رقم_devices);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDISPLAYATTRIBEXTPROC) (EGLDisplay dpy, EGLint attribute, EGLAttrib *مقدار);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDeviceAttribEXT (EGLDeviceEXT device, EGLint attribute, EGLAttrib *مقدار);
EGLAPI ثابت حرف *EGLAPIENTRY eglQueryDeviceStringEXT (EGLDeviceEXT device, EGLint name);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDevicesEXT (EGLint max_devices, EGLDeviceEXT *devices, EGLint *رقم_devices);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDisplayAttribEXT (EGLDisplay dpy, EGLint attribute, EGLAttrib *مقدار);
#پایان_اگر
#پایان_اگر /* EGL_EXT_device_base */

#اگر_تعریف_نشده EGL_EXT_device_drm
#تعریف_کن EGL_EXT_device_drm 1
#تعریف_کن EGL_DRM_DEVICE_FILE_EXT           0x3233
#تعریف_کن EGL_DRM_MASTER_FD_EXT             0x333C
#پایان_اگر /* EGL_EXT_device_drm */

#اگر_تعریف_نشده EGL_EXT_device_drm_render_گره
#تعریف_کن EGL_EXT_device_drm_render_گره 1
#تعریف_کن EGL_DRM_RENDER_گره_FILE_EXT      0x3377
#پایان_اگر /* EGL_EXT_device_drm_render_node */

#اگر_تعریف_نشده EGL_EXT_device_enumeration
#تعریف_کن EGL_EXT_device_enumeration 1
#پایان_اگر /* EGL_EXT_device_enumeration */

#اگر_تعریف_نشده EGL_EXT_device_openwf
#تعریف_کن EGL_EXT_device_openwf 1
#تعریف_کن EGL_OPENWF_DEVICE_ID_EXT          0x3237
#تعریف_کن EGL_OPENWF_DEVICE_EXT             0x333D
#پایان_اگر /* EGL_EXT_device_openwf */

#اگر_تعریف_نشده EGL_EXT_device_persistent_id
#تعریف_کن EGL_EXT_device_persistent_id 1
#تعریف_کن EGL_DEVICE_UUID_EXT               0x335C
#تعریف_کن EGL_DRIVER_UUID_EXT               0x335D
#تعریف_کن EGL_DRIVER_NAME_EXT               0x335E
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICEBINARYEXTPROC) (EGLDeviceEXT device, EGLint name, EGLint max_اندازه, فراغ *مقدار, EGLint *اندازه);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Device_دودویی_EXT (EGLDeviceEXT device, EGLint name, EGLint max_اندازه, فراغ *مقدار, EGLint *اندازه);
#پایان_اگر
#پایان_اگر /* EGL_EXT_device_persistent_id */

#اگر_تعریف_نشده EGL_EXT_device_query
#تعریف_کن EGL_EXT_device_query 1
#پایان_اگر /* EGL_EXT_device_query */

#اگر_تعریف_نشده EGL_EXT_device_query_name
#تعریف_کن EGL_EXT_device_query_name 1
#تعریف_کن EGL_RENDERER_EXT                  0x335F
#پایان_اگر /* EGL_EXT_device_query_name */

#اگر_تعریف_نشده EGL_EXT_device_type
#تعریف_کن EGL_EXT_device_type 1
#تعریف_کن EGL_DEVICE_TYPE_EXT               0x3590
#تعریف_کن EGL_DEVICE_TYPE_OTHER_EXT         0x3591
#تعریف_کن EGL_DEVICE_TYPE_INTEGRATED_GPU_EXT 0x3592
#تعریف_کن EGL_DEVICE_TYPE_DISCRETE_GPU_EXT  0x3593
#تعریف_کن EGL_DEVICE_TYPE_CPU_EXT           0x3594
#پایان_اگر /* EGL_EXT_device_type */

#اگر_تعریف_نشده EGL_EXT_display_alloc
#تعریف_کن EGL_EXT_display_alloc 1
#تعریف_کن EGL_ALLOC_NEW_DISPLAY_EXT         0x3379
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYDISPLAYEXTPROC) (EGLDisplay dpy);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyDisplayEXT (EGLDisplay dpy);
#پایان_اگر
#پایان_اگر /* EGL_EXT_display_alloc */

#اگر_تعریف_نشده EGL_EXT_explicit_device
#تعریف_کن EGL_EXT_explicit_device 1
#پایان_اگر /* EGL_EXT_explicit_device */

#اگر_تعریف_نشده EGL_EXT_gl_colorspace_bt2020_hlg
#تعریف_کن EGL_EXT_gl_colorspace_bt2020_hlg 1
#تعریف_کن EGL_GL_COLORSPACE_BT2020_HLG_EXT  0x3540
#پایان_اگر /* EGL_EXT_gl_colorspace_bt2020_hlg */

#اگر_تعریف_نشده EGL_EXT_gl_colorspace_bt2020_خطی
#تعریف_کن EGL_EXT_gl_colorspace_bt2020_خطی 1
#تعریف_کن EGL_GL_COLORSPACE_BT2020_خطی_EXT 0x333F
#پایان_اگر /* EGL_EXT_gl_colorspace_bt2020_linear */

#اگر_تعریف_نشده EGL_EXT_gl_colorspace_bt2020_pq
#تعریف_کن EGL_EXT_gl_colorspace_bt2020_pq 1
#تعریف_کن EGL_GL_COLORSPACE_BT2020_PQ_EXT   0x3340
#پایان_اگر /* EGL_EXT_gl_colorspace_bt2020_pq */

#اگر_تعریف_نشده EGL_EXT_gl_colorspace_display_p3
#تعریف_کن EGL_EXT_gl_colorspace_display_p3 1
#تعریف_کن EGL_GL_COLORSPACE_DISPLAY_P3_EXT  0x3363
#پایان_اگر /* EGL_EXT_gl_colorspace_display_p3 */

#اگر_تعریف_نشده EGL_EXT_gl_colorspace_display_p3_خطی
#تعریف_کن EGL_EXT_gl_colorspace_display_p3_خطی 1
#تعریف_کن EGL_GL_COLORSPACE_DISPLAY_P3_خطی_EXT 0x3362
#پایان_اگر /* EGL_EXT_gl_colorspace_display_p3_linear */

#اگر_تعریف_نشده EGL_EXT_gl_colorspace_display_p3_passthrough
#تعریف_کن EGL_EXT_gl_colorspace_display_p3_passthrough 1
#تعریف_کن EGL_GL_COLORSPACE_DISPLAY_P3_PASSTHROUGH_EXT 0x3490
#پایان_اگر /* EGL_EXT_gl_colorspace_display_p3_passthrough */

#اگر_تعریف_نشده EGL_EXT_gl_colorspace_scrgb
#تعریف_کن EGL_EXT_gl_colorspace_scrgb 1
#تعریف_کن EGL_GL_COLORSPACE_SCRGB_EXT       0x3351
#پایان_اگر /* EGL_EXT_gl_colorspace_scrgb */

#اگر_تعریف_نشده EGL_EXT_gl_colorspace_scrgb_خطی
#تعریف_کن EGL_EXT_gl_colorspace_scrgb_خطی 1
#تعریف_کن EGL_GL_COLORSPACE_SCRGB_خطی_EXT 0x3350
#پایان_اگر /* EGL_EXT_gl_colorspace_scrgb_linear */

#اگر_تعریف_نشده EGL_EXT_image_dma_buf_import
#تعریف_کن EGL_EXT_image_dma_buf_import 1
#تعریف_کن EGL_LINUX_DMA_BUF_EXT             0x3270
#تعریف_کن EGL_LINUX_DRM_FOURCC_EXT          0x3271
#تعریف_کن EGL_DMA_BUF_PLANE0_FD_EXT         0x3272
#تعریف_کن EGL_DMA_BUF_PLANE0_جابه_جایی_EXT     0x3273
#تعریف_کن EGL_DMA_BUF_PLANE0_PITCH_EXT      0x3274
#تعریف_کن EGL_DMA_BUF_PLANE1_FD_EXT         0x3275
#تعریف_کن EGL_DMA_BUF_PLANE1_جابه_جایی_EXT     0x3276
#تعریف_کن EGL_DMA_BUF_PLANE1_PITCH_EXT      0x3277
#تعریف_کن EGL_DMA_BUF_PLANE2_FD_EXT         0x3278
#تعریف_کن EGL_DMA_BUF_PLANE2_جابه_جایی_EXT     0x3279
#تعریف_کن EGL_DMA_BUF_PLANE2_PITCH_EXT      0x327A
#تعریف_کن EGL_YUV_COLOR_SPACE_HINT_EXT      0x327B
#تعریف_کن EGL_SAMPLE_RANGE_HINT_EXT         0x327C
#تعریف_کن EGL_YUV_CHROMA_HORIZONTAL_SITING_HINT_EXT 0x327D
#تعریف_کن EGL_YUV_CHROMA_VERTICAL_SITING_HINT_EXT 0x327E
#تعریف_کن EGL_ITU_REC601_EXT                0x327F
#تعریف_کن EGL_ITU_REC709_EXT                0x3280
#تعریف_کن EGL_ITU_REC2020_EXT               0x3281
#تعریف_کن EGL_YUV_پر_RANGE_EXT            0x3282
#تعریف_کن EGL_YUV_NARROW_RANGE_EXT          0x3283
#تعریف_کن EGL_YUV_CHROMA_SITING_0_EXT       0x3284
#تعریف_کن EGL_YUV_CHROMA_SITING_0_5_EXT     0x3285
#پایان_اگر /* EGL_EXT_image_dma_buf_import */

#اگر_تعریف_نشده EGL_EXT_image_dma_buf_import_modifiers
#تعریف_کن EGL_EXT_image_dma_buf_import_modifiers 1
#تعریف_کن EGL_DMA_BUF_PLANE3_FD_EXT         0x3440
#تعریف_کن EGL_DMA_BUF_PLANE3_جابه_جایی_EXT     0x3441
#تعریف_کن EGL_DMA_BUF_PLANE3_PITCH_EXT      0x3442
#تعریف_کن EGL_DMA_BUF_PLANE0_MODIFIER_LO_EXT 0x3443
#تعریف_کن EGL_DMA_BUF_PLANE0_MODIFIER_HI_EXT 0x3444
#تعریف_کن EGL_DMA_BUF_PLANE1_MODIFIER_LO_EXT 0x3445
#تعریف_کن EGL_DMA_BUF_PLANE1_MODIFIER_HI_EXT 0x3446
#تعریف_کن EGL_DMA_BUF_PLANE2_MODIFIER_LO_EXT 0x3447
#تعریف_کن EGL_DMA_BUF_PLANE2_MODIFIER_HI_EXT 0x3448
#تعریف_کن EGL_DMA_BUF_PLANE3_MODIFIER_LO_EXT 0x3449
#تعریف_کن EGL_DMA_BUF_PLANE3_MODIFIER_HI_EXT 0x344A
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDMABUFFORMATSEXTPROC) (EGLDisplay dpy, EGLint max_formats, EGLint *formats, EGLint *رقم_formats);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDMABUFMODIFIERSEXTPROC) (EGLDisplay dpy, EGLint format, EGLint max_modifiers, EGLuint64KHR *modifiers, EGLBoolean *external_only, EGLint *رقم_modifiers);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDmaBufFormatsEXT (EGLDisplay dpy, EGLint max_formats, EGLint *formats, EGLint *رقم_formats);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDmaBufModifiersEXT (EGLDisplay dpy, EGLint format, EGLint max_modifiers, EGLuint64KHR *modifiers, EGLBoolean *external_only, EGLint *رقم_modifiers);
#پایان_اگر
#پایان_اگر /* EGL_EXT_image_dma_buf_import_modifiers */

#اگر_تعریف_نشده EGL_EXT_image_gl_colorspace
#تعریف_کن EGL_EXT_image_gl_colorspace 1
#تعریف_کن EGL_GL_COLORSPACE_DEFAULT_EXT     0x314D
#پایان_اگر /* EGL_EXT_image_gl_colorspace */

#اگر_تعریف_نشده EGL_EXT_image_implicit_sync_control
#تعریف_کن EGL_EXT_image_implicit_sync_control 1
#تعریف_کن EGL_IMPORT_SYNC_TYPE_EXT          0x3470
#تعریف_کن EGL_IMPORT_IMPLICIT_SYNC_EXT      0x3471
#تعریف_کن EGL_IMPORT_EXPLICIT_SYNC_EXT      0x3472
#پایان_اگر /* EGL_EXT_image_implicit_sync_control */

#اگر_تعریف_نشده EGL_EXT_multiview_پنجره
#تعریف_کن EGL_EXT_multiview_پنجره 1
#تعریف_کن EGL_MULTIVIEW_VIEW_شمار_EXT      0x3134
#پایان_اگر /* EGL_EXT_multiview_window */

#اگر_تعریف_نشده EGL_EXT_output_پایه
#تعریف_کن EGL_EXT_output_پایه 1
تعريفنوع فراغ *EGLOutputLayerEXT;
تعريفنوع فراغ *EGLOutput_پورت_EXT;
#تعریف_کن EGL_NO_OUTPUT_LAYER_EXT           EGL_CAST(EGLOutputLayerEXT,0)
#تعریف_کن EGL_NO_OUTPUT_پورت_EXT            EGL_CAST(EGLOutput_پورت_EXT,0)
#تعریف_کن EGL_BAD_OUTPUT_LAYER_EXT          0x322D
#تعریف_کن EGL_BAD_OUTPUT_پورت_EXT           0x322E
#تعریف_کن EGL_جابجا_INTERVAL_EXT             0x322F
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETOUTPUTLAYERSEXTPROC) (EGLDisplay dpy, ثابت EGLAttrib *attrib_list, EGLOutputLayerEXT *layers, EGLint max_layers, EGLint *رقم_layers);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETOUTPUTPORTSEXTPROC) (EGLDisplay dpy, ثابت EGLAttrib *attrib_list, EGLOutput_پورت_EXT *ports, EGLint max_ports, EGLint *رقم_ports);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLOUTPUTLAYERATTRIBEXTPROC) (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib مقدار);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYOUTPUTLAYERATTRIBEXTPROC) (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib *مقدار);
تعريفنوع ثابت حرف *(EGLAPIENTRYP PFNEGLQUERYOUTPUTLAYERSTRINGEXTPROC) (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint name);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLOUTPUTPORTATTRIBEXTPROC) (EGLDisplay dpy, EGLOutput_پورت_EXT پورت, EGLint attribute, EGLAttrib مقدار);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYOUTPUTPORTATTRIBEXTPROC) (EGLDisplay dpy, EGLOutput_پورت_EXT پورت, EGLint attribute, EGLAttrib *مقدار);
تعريفنوع ثابت حرف *(EGLAPIENTRYP PFNEGLQUERYOUTPUTPORTSTRINGEXTPROC) (EGLDisplay dpy, EGLOutput_پورت_EXT پورت, EGLint name);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglGetOutputLayersEXT (EGLDisplay dpy, ثابت EGLAttrib *attrib_list, EGLOutputLayerEXT *layers, EGLint max_layers, EGLint *رقم_layers);
EGLAPI EGLBoolean EGLAPIENTRY eglGetOutputPortsEXT (EGLDisplay dpy, ثابت EGLAttrib *attrib_list, EGLOutput_پورت_EXT *ports, EGLint max_ports, EGLint *رقم_ports);
EGLAPI EGLBoolean EGLAPIENTRY eglOutputLayerAttribEXT (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib مقدار);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryOutputLayerAttribEXT (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib *مقدار);
EGLAPI ثابت حرف *EGLAPIENTRY eglQueryOutputLayerStringEXT (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint name);
EGLAPI EGLBoolean EGLAPIENTRY egl_Output_پورت_Attrib_EXT (EGLDisplay dpy, EGLOutput_پورت_EXT پورت, EGLint attribute, EGLAttrib مقدار);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Output_پورت_Attrib_EXT (EGLDisplay dpy, EGLOutput_پورت_EXT پورت, EGLint attribute, EGLAttrib *مقدار);
EGLAPI ثابت حرف *EGLAPIENTRY egl_Query_Output_پورت_String_EXT (EGLDisplay dpy, EGLOutput_پورت_EXT پورت, EGLint name);
#پایان_اگر
#پایان_اگر /* EGL_EXT_output_base */

#اگر_تعریف_نشده EGL_EXT_output_drm
#تعریف_کن EGL_EXT_output_drm 1
#تعریف_کن EGL_DRM_CRTC_EXT                  0x3234
#تعریف_کن EGL_DRM_PLANE_EXT                 0x3235
#تعریف_کن EGL_DRM_CONNECTOR_EXT             0x3236
#پایان_اگر /* EGL_EXT_output_drm */

#اگر_تعریف_نشده EGL_EXT_output_openwf
#تعریف_کن EGL_EXT_output_openwf 1
#تعریف_کن EGL_OPENWF_PIPELINE_ID_EXT        0x3238
#تعریف_کن EGL_OPENWF_پورت_ID_EXT            0x3239
#پایان_اگر /* EGL_EXT_output_openwf */

#اگر_تعریف_نشده EGL_EXT_pixel_format_float
#تعریف_کن EGL_EXT_pixel_format_float 1
#تعریف_کن EGL_COLOR_COMPONENT_TYPE_EXT      0x3339
#تعریف_کن EGL_COLOR_COMPONENT_TYPE_FIXED_EXT 0x333A
#تعریف_کن EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT 0x333B
#پایان_اگر /* EGL_EXT_pixel_format_float */

#اگر_تعریف_نشده EGL_EXT_platform_پایه
#تعریف_کن EGL_EXT_platform_پایه 1
تعريفنوع EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYEXTPROC) (EGLenum platform, فراغ *native_display, ثابت EGLint *attrib_list);
تعريفنوع EGLSurface (EGLAPIENTRYP PFNEGLCREATEPLATFORMWINDOWSURFACEEXTPROC) (EGLDisplay dpy, EGLConfig config, فراغ *native_پنجره, ثابت EGLint *attrib_list);
تعريفنوع EGLSurface (EGLAPIENTRYP PFNEGLCREATEPLATFORMPIXMAPSURFACEEXTPROC) (EGLDisplay dpy, EGLConfig config, فراغ *native_pixmap, ثابت EGLint *attrib_list);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLDisplay EGLAPIENTRY eglGetPlatformDisplayEXT (EGLenum platform, فراغ *native_display, ثابت EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY egl_Create_Platform_پنجره_Surface_EXT (EGLDisplay dpy, EGLConfig config, فراغ *native_پنجره, ثابت EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePlatformPixmapSurfaceEXT (EGLDisplay dpy, EGLConfig config, فراغ *native_pixmap, ثابت EGLint *attrib_list);
#پایان_اگر
#پایان_اگر /* EGL_EXT_platform_base */

#اگر_تعریف_نشده EGL_EXT_platform_device
#تعریف_کن EGL_EXT_platform_device 1
#تعریف_کن EGL_PLATFORM_DEVICE_EXT           0x313F
#پایان_اگر /* EGL_EXT_platform_device */

#اگر_تعریف_نشده EGL_EXT_platform_wayland
#تعریف_کن EGL_EXT_platform_wayland 1
#تعریف_کن EGL_PLATFORM_WAYLAND_EXT          0x31D8
#پایان_اگر /* EGL_EXT_platform_wayland */

#اگر_تعریف_نشده EGL_EXT_platform_x11
#تعریف_کن EGL_EXT_platform_x11 1
#تعریف_کن EGL_PLATFORM_X11_EXT              0x31D5
#تعریف_کن EGL_PLATFORM_X11_SCREEN_EXT       0x31D6
#پایان_اگر /* EGL_EXT_platform_x11 */

#اگر_تعریف_نشده EGL_EXT_platform_xcb
#تعریف_کن EGL_EXT_platform_xcb 1
#تعریف_کن EGL_PLATFORM_XCB_EXT              0x31DC
#تعریف_کن EGL_PLATFORM_XCB_SCREEN_EXT       0x31DE
#پایان_اگر /* EGL_EXT_platform_xcb */

#اگر_تعریف_نشده EGL_EXT_present_opaque
#تعریف_کن EGL_EXT_present_opaque 1
#تعریف_کن EGL_PRESENT_OPAQUE_EXT            0x31DF
#پایان_اگر /* EGL_EXT_present_opaque */

#اگر_تعریف_نشده EGL_EXT_protected_content
#تعریف_کن EGL_EXT_protected_content 1
#تعریف_کن EGL_PROTECTED_CONTENT_EXT         0x32C0
#پایان_اگر /* EGL_EXT_protected_content */

#اگر_تعریف_نشده EGL_EXT_protected_surface
#تعریف_کن EGL_EXT_protected_surface 1
#پایان_اگر /* EGL_EXT_protected_surface */

#اگر_تعریف_نشده EGL_EXT_query_reset_notification_strategy
#تعریف_کن EGL_EXT_query_reset_notification_strategy 1
#پایان_اگر /* EGL_EXT_query_reset_notification_strategy */

#اگر_تعریف_نشده EGL_EXT_جریان_مصرفکننده_egloutput
#تعریف_کن EGL_EXT_جریان_مصرفکننده_egloutput 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMEROUTPUTEXTPROC) (EGLDisplay dpy, EGLStreamKHR جریان, EGLOutputLayerEXT layer);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_جریان_مصرفکننده_Output_EXT (EGLDisplay dpy, EGLStreamKHR جریان, EGLOutputLayerEXT layer);
#پایان_اگر
#پایان_اگر /* EGL_EXT_stream_consumer_egloutput */

#اگر_تعریف_نشده EGL_EXT_surface_CTA861_3_metadata
#تعریف_کن EGL_EXT_surface_CTA861_3_metadata 1
#تعریف_کن EGL_CTA861_3_MAX_CONTENT_LIGHT_LEVEL_EXT 0x3360
#تعریف_کن EGL_CTA861_3_MAX_قاب_معدل_LEVEL_EXT 0x3361
#پایان_اگر /* EGL_EXT_surface_CTA861_3_metadata */

#اگر_تعریف_نشده EGL_EXT_surface_SMPTE2086_metadata
#تعریف_کن EGL_EXT_surface_SMPTE2086_metadata 1
#تعریف_کن EGL_SMPTE2086_DISPLAY_PRIMARY_RX_EXT 0x3341
#تعریف_کن EGL_SMPTE2086_DISPLAY_PRIMARY_RY_EXT 0x3342
#تعریف_کن EGL_SMPTE2086_DISPLAY_PRIMARY_GX_EXT 0x3343
#تعریف_کن EGL_SMPTE2086_DISPLAY_PRIMARY_GY_EXT 0x3344
#تعریف_کن EGL_SMPTE2086_DISPLAY_PRIMARY_BX_EXT 0x3345
#تعریف_کن EGL_SMPTE2086_DISPLAY_PRIMARY_BY_EXT 0x3346
#تعریف_کن EGL_SMPTE2086_WHITE_نقطه_X_EXT   0x3347
#تعریف_کن EGL_SMPTE2086_WHITE_نقطه_Y_EXT   0x3348
#تعریف_کن EGL_SMPTE2086_MAX_LUMINANCE_EXT   0x3349
#تعریف_کن EGL_SMPTE2086_MIN_LUMINANCE_EXT   0x334A
#تعریف_کن EGL_METADATA_SCALING_EXT          50000
#پایان_اگر /* EGL_EXT_surface_SMPTE2086_metadata */

#اگر_تعریف_نشده EGL_EXT_surface_compression
#تعریف_کن EGL_EXT_surface_compression 1
#تعریف_کن EGL_SURFACE_COMPRESSION_EXT       0x34B0
#تعریف_کن EGL_SURFACE_COMPRESSION_PLANE1_EXT 0x328E
#تعریف_کن EGL_SURFACE_COMPRESSION_PLANE2_EXT 0x328F
#تعریف_کن EGL_SURFACE_COMPRESSION_FIXED_نرخ_NONE_EXT 0x34B1
#تعریف_کن EGL_SURFACE_COMPRESSION_FIXED_نرخ_DEFAULT_EXT 0x34B2
#تعریف_کن EGL_SURFACE_COMPRESSION_FIXED_نرخ_1_BPC_EXT 0x34B4
#تعریف_کن EGL_SURFACE_COMPRESSION_FIXED_نرخ_2_BPC_EXT 0x34B5
#تعریف_کن EGL_SURFACE_COMPRESSION_FIXED_نرخ_3_BPC_EXT 0x34B6
#تعریف_کن EGL_SURFACE_COMPRESSION_FIXED_نرخ_4_BPC_EXT 0x34B7
#تعریف_کن EGL_SURFACE_COMPRESSION_FIXED_نرخ_5_BPC_EXT 0x34B8
#تعریف_کن EGL_SURFACE_COMPRESSION_FIXED_نرخ_6_BPC_EXT 0x34B9
#تعریف_کن EGL_SURFACE_COMPRESSION_FIXED_نرخ_7_BPC_EXT 0x34BA
#تعریف_کن EGL_SURFACE_COMPRESSION_FIXED_نرخ_8_BPC_EXT 0x34BB
#تعریف_کن EGL_SURFACE_COMPRESSION_FIXED_نرخ_9_BPC_EXT 0x34BC
#تعریف_کن EGL_SURFACE_COMPRESSION_FIXED_نرخ_10_BPC_EXT 0x34BD
#تعریف_کن EGL_SURFACE_COMPRESSION_FIXED_نرخ_11_BPC_EXT 0x34BE
#تعریف_کن EGL_SURFACE_COMPRESSION_FIXED_نرخ_12_BPC_EXT 0x34BF
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSUPPORTEDCOMPRESSIONRATESEXTPROC) (EGLDisplay dpy, EGLConfig config, ثابت EGLAttrib *attrib_list, EGLint *rates, EGLint نرخ_اندازه, EGLint *رقم_rates);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQuerySupportedCompressionRatesEXT (EGLDisplay dpy, EGLConfig config, ثابت EGLAttrib *attrib_list, EGLint *rates, EGLint نرخ_اندازه, EGLint *رقم_rates);
#پایان_اگر
#پایان_اگر /* EGL_EXT_surface_compression */

#اگر_تعریف_نشده EGL_EXT_جابجا_buffers_with_damage
#تعریف_کن EGL_EXT_جابجا_buffers_with_damage 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC) (EGLDisplay dpy, EGLSurface surface, ثابت EGLint *rects, EGLint n_rects);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_جابجا_Buffers_With_Damage_EXT (EGLDisplay dpy, EGLSurface surface, ثابت EGLint *rects, EGLint n_rects);
#پایان_اگر
#پایان_اگر /* EGL_EXT_swap_buffers_with_damage */

#اگر_تعریف_نشده EGL_EXT_sync_reuse
#تعریف_کن EGL_EXT_sync_reuse 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLUNSIGNALSYNCEXTPROC) (EGLDisplay dpy, EGLSync sync, ثابت EGLAttrib *attrib_list);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglUnsignalSyncEXT (EGLDisplay dpy, EGLSync sync, ثابت EGLAttrib *attrib_list);
#پایان_اگر
#پایان_اگر /* EGL_EXT_sync_reuse */

#اگر_تعریف_نشده EGL_EXT_yuv_surface
#تعریف_کن EGL_EXT_yuv_surface 1
#تعریف_کن EGL_YUV_ترتیب_EXT                 0x3301
#تعریف_کن EGL_YUV_عدد_از_PLANES_EXT      0x3311
#تعریف_کن EGL_YUV_SUBSAMPLE_EXT             0x3312
#تعریف_کن EGL_YUV_عمق_RANGE_EXT           0x3317
#تعریف_کن EGL_YUV_CSC_STANDARD_EXT          0x330A
#تعریف_کن EGL_YUV_PLANE_BPP_EXT             0x331A
#تعریف_کن EGL_YUV_میانگیر_EXT                0x3300
#تعریف_کن EGL_YUV_ترتیب_YUV_EXT             0x3302
#تعریف_کن EGL_YUV_ترتیب_YVU_EXT             0x3303
#تعریف_کن EGL_YUV_ترتیب_YUYV_EXT            0x3304
#تعریف_کن EGL_YUV_ترتیب_UYVY_EXT            0x3305
#تعریف_کن EGL_YUV_ترتیب_YVYU_EXT            0x3306
#تعریف_کن EGL_YUV_ترتیب_VYUY_EXT            0x3307
#تعریف_کن EGL_YUV_ترتیب_AYUV_EXT            0x3308
#تعریف_کن EGL_YUV_SUBSAMPLE_4_2_0_EXT       0x3313
#تعریف_کن EGL_YUV_SUBSAMPLE_4_2_2_EXT       0x3314
#تعریف_کن EGL_YUV_SUBSAMPLE_4_4_4_EXT       0x3315
#تعریف_کن EGL_YUV_عمق_RANGE_LIMITED_EXT   0x3318
#تعریف_کن EGL_YUV_عمق_RANGE_پر_EXT      0x3319
#تعریف_کن EGL_YUV_CSC_STANDARD_601_EXT      0x330B
#تعریف_کن EGL_YUV_CSC_STANDARD_709_EXT      0x330C
#تعریف_کن EGL_YUV_CSC_STANDARD_2020_EXT     0x330D
#تعریف_کن EGL_YUV_PLANE_BPP_0_EXT           0x331B
#تعریف_کن EGL_YUV_PLANE_BPP_8_EXT           0x331C
#تعریف_کن EGL_YUV_PLANE_BPP_10_EXT          0x331D
#پایان_اگر /* EGL_EXT_yuv_surface */

#اگر_تعریف_نشده EGL_HI_clientpixmap
#تعریف_کن EGL_HI_clientpixmap 1
بنية EGLClientPixmapHI {
    فراغ  *p_داده;
    EGLint i_عرض;
    EGLint i_ارتفاع;
    EGLint iStride;
};
#تعریف_کن EGL_CLIENT_PIXMAP_اشاره_گر_HI      0x8F74
تعريفنوع EGLSurface (EGLAPIENTRYP PFNEGLCREATEPIXMAPSURFACEHIPROC) (EGLDisplay dpy, EGLConfig config, بنية EGLClientPixmapHI *pixmap);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSurface EGLAPIENTRY eglCreatePixmapSurfaceHI (EGLDisplay dpy, EGLConfig config, بنية EGLClientPixmapHI *pixmap);
#پایان_اگر
#پایان_اگر /* EGL_HI_clientpixmap */

#اگر_تعریف_نشده EGL_HI_colorformats
#تعریف_کن EGL_HI_colorformats 1
#تعریف_کن EGL_COLOR_FORMAT_HI               0x8F70
#تعریف_کن EGL_COLOR_RGB_HI                  0x8F71
#تعریف_کن EGL_COLOR_RGBA_HI                 0x8F72
#تعریف_کن EGL_COLOR_ARGB_HI                 0x8F73
#پایان_اگر /* EGL_HI_colorformats */

#اگر_تعریف_نشده EGL_IMG_context_اولویت
#تعریف_کن EGL_IMG_context_اولویت 1
#تعریف_کن EGL_CONTEXT_اولویت_LEVEL_IMG    0x3100
#تعریف_کن EGL_CONTEXT_اولویت_بالا_IMG     0x3101
#تعریف_کن EGL_CONTEXT_اولویت_MEDIUM_IMG   0x3102
#تعریف_کن EGL_CONTEXT_اولویت_کم_IMG      0x3103
#پایان_اگر /* EGL_IMG_context_priority */

#اگر_تعریف_نشده EGL_IMG_image_plane_attribs
#تعریف_کن EGL_IMG_image_plane_attribs 1
#تعریف_کن EGL_NATIVE_میانگیر_MULTIPLANE_SEPARATE_IMG 0x3105
#تعریف_کن EGL_NATIVE_میانگیر_PLANE_جابه_جایی_IMG 0x3106
#پایان_اگر /* EGL_IMG_image_plane_attribs */

#اگر_تعریف_نشده EGL_MESA_drm_image
#تعریف_کن EGL_MESA_drm_image 1
#تعریف_کن EGL_DRM_میانگیر_FORMAT_MESA        0x31D0
#تعریف_کن EGL_DRM_میانگیر_USE_MESA           0x31D1
#تعریف_کن EGL_DRM_میانگیر_FORMAT_ARGB32_MESA 0x31D2
#تعریف_کن EGL_DRM_میانگیر_MESA               0x31D3
#تعریف_کن EGL_DRM_میانگیر_STRIDE_MESA        0x31D4
#تعریف_کن EGL_DRM_میانگیر_USE_SCANOUT_MESA   0x00000001
#تعریف_کن EGL_DRM_میانگیر_USE_SHARE_MESA     0x00000002
#تعریف_کن EGL_DRM_میانگیر_USE_CURSOR_MESA    0x00000004
تعريفنوع EGLImageKHR (EGLAPIENTRYP PFNEGLCREATEDRMIMAGEMESAPROC) (EGLDisplay dpy, ثابت EGLint *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLEXPORTDRMIMAGEMESAPROC) (EGLDisplay dpy, EGLImageKHR image, EGLint *name, EGLint *handle, EGLint *stride);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLImageKHR EGLAPIENTRY eglCreateDRMImageMESA (EGLDisplay dpy, ثابت EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglExportDRMImageMESA (EGLDisplay dpy, EGLImageKHR image, EGLint *name, EGLint *handle, EGLint *stride);
#پایان_اگر
#پایان_اگر /* EGL_MESA_drm_image */

#اگر_تعریف_نشده EGL_MESA_image_dma_buf_export
#تعریف_کن EGL_MESA_image_dma_buf_export 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLEXPORTDMABUFIMAGEQUERYMESAPROC) (EGLDisplay dpy, EGLImageKHR image, صحيح *fourcc, صحيح *رقم_planes, EGLuint64KHR *modifiers);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLEXPORTDMABUFIMAGEMESAPROC) (EGLDisplay dpy, EGLImageKHR image, صحيح *fds, EGLint *strides, EGLint *offsets);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglExportDMABUFImageQueryMESA (EGLDisplay dpy, EGLImageKHR image, صحيح *fourcc, صحيح *رقم_planes, EGLuint64KHR *modifiers);
EGLAPI EGLBoolean EGLAPIENTRY eglExportDMABUFImageMESA (EGLDisplay dpy, EGLImageKHR image, صحيح *fds, EGLint *strides, EGLint *offsets);
#پایان_اگر
#پایان_اگر /* EGL_MESA_image_dma_buf_export */

#اگر_تعریف_نشده EGL_MESA_platform_gbm
#تعریف_کن EGL_MESA_platform_gbm 1
#تعریف_کن EGL_PLATFORM_GBM_MESA             0x31D7
#پایان_اگر /* EGL_MESA_platform_gbm */

#اگر_تعریف_نشده EGL_MESA_platform_surfaceless
#تعریف_کن EGL_MESA_platform_surfaceless 1
#تعریف_کن EGL_PLATFORM_SURFACELESS_MESA     0x31DD
#پایان_اگر /* EGL_MESA_platform_surfaceless */

#اگر_تعریف_نشده EGL_MESA_query_driver
#تعریف_کن EGL_MESA_query_driver 1
تعريفنوع حرف *(EGLAPIENTRYP PFNEGLGETDISPLAYDRIVERCONFIGPROC) (EGLDisplay dpy);
تعريفنوع ثابت حرف *(EGLAPIENTRYP PFNEGLGETDISPLAYDRIVERNAMEPROC) (EGLDisplay dpy);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI حرف *EGLAPIENTRY eglGetDisplayDriverConfig (EGLDisplay dpy);
EGLAPI ثابت حرف *EGLAPIENTRY eglGetDisplayDriverName (EGLDisplay dpy);
#پایان_اگر
#پایان_اگر /* EGL_MESA_query_driver */

#اگر_تعریف_نشده EGL_NOK_جابجا_region
#تعریف_کن EGL_NOK_جابجا_region 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSREGIONNOKPROC) (EGLDisplay dpy, EGLSurface surface, EGLint رقم_Rects_2, ثابت EGLint *rects);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_جابجا_Buffers_Region_NOK (EGLDisplay dpy, EGLSurface surface, EGLint رقم_Rects_2, ثابت EGLint *rects);
#پایان_اگر
#پایان_اگر /* EGL_NOK_swap_region */

#اگر_تعریف_نشده EGL_NOK_جابجا_region2
#تعریف_کن EGL_NOK_جابجا_region2 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSREGION2NOKPROC) (EGLDisplay dpy, EGLSurface surface, EGLint رقم_Rects_2, ثابت EGLint *rects);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_جابجا_Buffers_Region2_NOK (EGLDisplay dpy, EGLSurface surface, EGLint رقم_Rects_2, ثابت EGLint *rects);
#پایان_اگر
#پایان_اگر /* EGL_NOK_swap_region2 */

#اگر_تعریف_نشده EGL_NOK_texture_from_pixmap
#تعریف_کن EGL_NOK_texture_from_pixmap 1
#تعریف_کن EGL_Y_INVERTED_NOK                0x307F
#پایان_اگر /* EGL_NOK_texture_from_pixmap */

#اگر_تعریف_نشده EGL_NV_3dvision_surface
#تعریف_کن EGL_NV_3dvision_surface 1
#تعریف_کن EGL_AUTO_STEREO_NV                0x3136
#پایان_اگر /* EGL_NV_3dvision_surface */

#اگر_تعریف_نشده EGL_NV_context_اولویت_realtime
#تعریف_کن EGL_NV_context_اولویت_realtime 1
#تعریف_کن EGL_CONTEXT_اولویت_REALTIME_NV  0x3357
#پایان_اگر /* EGL_NV_context_priority_realtime */

#اگر_تعریف_نشده EGL_NV_coverage_sample
#تعریف_کن EGL_NV_coverage_sample 1
#تعریف_کن EGL_COVERAGE_BUFFERS_NV           0x30E0
#تعریف_کن EGL_COVERAGE_SAMPLES_NV           0x30E1
#پایان_اگر /* EGL_NV_coverage_sample */

#اگر_تعریف_نشده EGL_NV_coverage_sample_resolve
#تعریف_کن EGL_NV_coverage_sample_resolve 1
#تعریف_کن EGL_COVERAGE_SAMPLE_RESOLVE_NV    0x3131
#تعریف_کن EGL_COVERAGE_SAMPLE_RESOLVE_DEFAULT_NV 0x3132
#تعریف_کن EGL_COVERAGE_SAMPLE_RESOLVE_NONE_NV 0x3133
#پایان_اگر /* EGL_NV_coverage_sample_resolve */

#اگر_تعریف_نشده EGL_NV_cuda_event
#تعریف_کن EGL_NV_cuda_event 1
#تعریف_کن EGL_CUDA_EVENT_HANDLE_NV          0x323B
#تعریف_کن EGL_SYNC_CUDA_EVENT_NV            0x323C
#تعریف_کن EGL_SYNC_CUDA_EVENT_COMPLETE_NV   0x323D
#پایان_اگر /* EGL_NV_cuda_event */

#اگر_تعریف_نشده EGL_NV_عمق_nonlinear
#تعریف_کن EGL_NV_عمق_nonlinear 1
#تعریف_کن EGL_عمق_ENCODING_NV             0x30E2
#تعریف_کن EGL_عمق_ENCODING_NONE_NV        0
#تعریف_کن EGL_عمق_ENCODING_NONLINEAR_NV   0x30E3
#پایان_اگر /* EGL_NV_depth_nonlinear */

#اگر_تعریف_نشده EGL_NV_device_cuda
#تعریف_کن EGL_NV_device_cuda 1
#تعریف_کن EGL_CUDA_DEVICE_NV                0x323A
#پایان_اگر /* EGL_NV_device_cuda */

#اگر_تعریف_نشده EGL_NV_native_query
#تعریف_کن EGL_NV_native_query 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYNATIVEDISPLAYNVPROC) (EGLDisplay dpy, EGLNativeDisplayType *display_id);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYNATIVEWINDOWNVPROC) (EGLDisplay dpy, EGLSurface surf, EGLNative_پنجره_Type *پنجره);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYNATIVEPIXMAPNVPROC) (EGLDisplay dpy, EGLSurface surf, EGLNativePixmapType *pixmap);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryNativeDisplayNV (EGLDisplay dpy, EGLNativeDisplayType *display_id);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Native_پنجره_NV (EGLDisplay dpy, EGLSurface surf, EGLNative_پنجره_Type *پنجره);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryNativePixmapNV (EGLDisplay dpy, EGLSurface surf, EGLNativePixmapType *pixmap);
#پایان_اگر
#پایان_اگر /* EGL_NV_native_query */

#اگر_تعریف_نشده EGL_NV_post_convert_rounding
#تعریف_کن EGL_NV_post_convert_rounding 1
#پایان_اگر /* EGL_NV_post_convert_rounding */

#اگر_تعریف_نشده EGL_NV_post_sub_میانگیر
#تعریف_کن EGL_NV_post_sub_میانگیر 1
#تعریف_کن EGL_POST_SUB_میانگیر_SUPPORTED_NV  0x30BE
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLPOSTSUBBUFFERNVPROC) (EGLDisplay dpy, EGLSurface surface, EGLint x, EGLint y, EGLint عرض, EGLint ارتفاع);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Post_Sub_میانگیر_NV (EGLDisplay dpy, EGLSurface surface, EGLint x, EGLint y, EGLint عرض, EGLint ارتفاع);
#پایان_اگر
#پایان_اگر /* EGL_NV_post_sub_buffer */

#اگر_تعریف_نشده EGL_NV_quadruple_میانگیر
#تعریف_کن EGL_NV_quadruple_میانگیر 1
#تعریف_کن EGL_QUADRUPLE_میانگیر_NV           0x3231
#پایان_اگر /* EGL_NV_quadruple_buffer */

#اگر_تعریف_نشده EGL_NV_robustness_video_حافظه_purge
#تعریف_کن EGL_NV_robustness_video_حافظه_purge 1
#تعریف_کن EGL_GENERATE_RESET_ON_VIDEO_حافظه_PURGE_NV 0x334C
#پایان_اگر /* EGL_NV_robustness_video_memory_purge */

#اگر_تعریف_نشده EGL_NV_جریان_مصرفکننده_eglimage
#تعریف_کن EGL_NV_جریان_مصرفکننده_eglimage 1
#تعریف_کن EGL_جریان_مصرفکننده_IMAGE_NV      0x3373
#تعریف_کن EGL_جریان_IMAGE_جمع_کن_NV           0x3374
#تعریف_کن EGL_جریان_IMAGE_REMOVE_NV        0x3375
#تعریف_کن EGL_جریان_IMAGE_موجود_NV     0x3376
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMIMAGECONSUMERCONNECTNVPROC) (EGLDisplay dpy, EGLStreamKHR جریان, EGLint رقم_modifiers, ثابت EGLuint64KHR *modifiers, ثابت EGLAttrib *attrib_list);
تعريفنوع EGLint (EGLAPIENTRYP PFNEGLQUERYSTREAMCONSUMEREVENTNVPROC) (EGLDisplay dpy, EGLStreamKHR جریان, EGLTime timeout, EGLenum *event, EGLAttrib *aux);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMACQUIREIMAGENVPROC) (EGLDisplay dpy, EGLStreamKHR جریان, EGLImage *pImage, EGLSync sync);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMRELEASEIMAGENVPROC) (EGLDisplay dpy, EGLStreamKHR جریان, EGLImage image, EGLSync sync);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_جریان_Image_مصرفکننده_Connect_NV (EGLDisplay dpy, EGLStreamKHR جریان, EGLint رقم_modifiers, ثابت EGLuint64KHR *modifiers, ثابت EGLAttrib *attrib_list);
EGLAPI EGLint EGLAPIENTRY egl_Query_جریان_مصرفکننده_Event_NV (EGLDisplay dpy, EGLStreamKHR جریان, EGLTime timeout, EGLenum *event, EGLAttrib *aux);
EGLAPI EGLBoolean EGLAPIENTRY egl_جریان_Acquire_Image_NV (EGLDisplay dpy, EGLStreamKHR جریان, EGLImage *pImage, EGLSync sync);
EGLAPI EGLBoolean EGLAPIENTRY egl_جریان_Release_Image_NV (EGLDisplay dpy, EGLStreamKHR جریان, EGLImage image, EGLSync sync);
#پایان_اگر
#پایان_اگر /* EGL_NV_stream_consumer_eglimage */

#اگر_تعریف_نشده EGL_NV_جریان_مصرفکننده_eglimage_use_scanout_attrib
#تعریف_کن EGL_NV_جریان_مصرفکننده_eglimage_use_scanout_attrib 1
#تعریف_کن EGL_جریان_مصرفکننده_IMAGE_USE_SCANOUT_NV 0x3378
#پایان_اگر /* EGL_NV_stream_consumer_eglimage_use_scanout_attrib */

#اگر_تعریف_نشده EGL_NV_جریان_مصرفکننده_gltexture_yuv
#تعریف_کن EGL_NV_جریان_مصرفکننده_gltexture_yuv 1
#تعریف_کن EGL_YUV_PLANE0_TEXTURE_UNIT_NV    0x332C
#تعریف_کن EGL_YUV_PLANE1_TEXTURE_UNIT_NV    0x332D
#تعریف_کن EGL_YUV_PLANE2_TEXTURE_UNIT_NV    0x332E
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALATTRIBSNVPROC) (EGLDisplay dpy, EGLStreamKHR جریان, ثابت EGLAttrib *attrib_list);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_جریان_مصرفکننده_GLTexture_External_Attribs_NV (EGLDisplay dpy, EGLStreamKHR جریان, ثابت EGLAttrib *attrib_list);
#پایان_اگر
#پایان_اگر /* EGL_NV_stream_consumer_gltexture_yuv */

#اگر_تعریف_نشده EGL_NV_جریان_cross_display
#تعریف_کن EGL_NV_جریان_cross_display 1
#تعریف_کن EGL_جریان_CROSS_DISPLAY_NV       0x334E
#پایان_اگر /* EGL_NV_stream_cross_display */

#اگر_تعریف_نشده EGL_NV_جریان_cross_object
#تعریف_کن EGL_NV_جریان_cross_object 1
#تعریف_کن EGL_جریان_CROSS_OBJECT_NV        0x334D
#پایان_اگر /* EGL_NV_stream_cross_object */

#اگر_تعریف_نشده EGL_NV_جریان_cross_افراز
#تعریف_کن EGL_NV_جریان_cross_افراز 1
#تعریف_کن EGL_جریان_CROSS_افراز_NV     0x323F
#پایان_اگر /* EGL_NV_stream_cross_partition */

#اگر_تعریف_نشده EGL_NV_جریان_cross_process
#تعریف_کن EGL_NV_جریان_cross_process 1
#تعریف_کن EGL_جریان_CROSS_PROCESS_NV       0x3245
#پایان_اگر /* EGL_NV_stream_cross_process */

#اگر_تعریف_نشده EGL_NV_جریان_cross_system
#تعریف_کن EGL_NV_جریان_cross_system 1
#تعریف_کن EGL_جریان_CROSS_SYSTEM_NV        0x334F
#پایان_اگر /* EGL_NV_stream_cross_system */

#اگر_تعریف_نشده EGL_NV_جریان_dma
#تعریف_کن EGL_NV_جریان_dma 1
#تعریف_کن EGL_جریان_DMA_NV                 0x3371
#تعریف_کن EGL_جریان_DMA_SERVER_NV          0x3372
#پایان_اگر /* EGL_NV_stream_dma */

#اگر_تعریف_نشده EGL_NV_جریان_fifo_بعدی
#تعریف_کن EGL_NV_جریان_fifo_بعدی 1
#تعریف_کن EGL_PENDING_قاب_NV              0x3329
#تعریف_کن EGL_جریان_زمان_PENDING_NV        0x332A
#پایان_اگر /* EGL_NV_stream_fifo_next */

#اگر_تعریف_نشده EGL_NV_جریان_fifo_synchronous
#تعریف_کن EGL_NV_جریان_fifo_synchronous 1
#تعریف_کن EGL_جریان_FIFO_SYNCHRONOUS_NV    0x3336
#پایان_اگر /* EGL_NV_stream_fifo_synchronous */

#اگر_تعریف_نشده EGL_NV_جریان_flush
#تعریف_کن EGL_NV_جریان_flush 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMFLUSHNVPROC) (EGLDisplay dpy, EGLStreamKHR جریان);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_جریان_Flush_NV (EGLDisplay dpy, EGLStreamKHR جریان);
#پایان_اگر
#پایان_اگر /* EGL_NV_stream_flush */

#اگر_تعریف_نشده EGL_NV_جریان_قاب_limits
#تعریف_کن EGL_NV_جریان_قاب_limits 1
#تعریف_کن EGL_تولیدکننده_MAX_قاب_HINT_NV    0x3337
#تعریف_کن EGL_مصرفکننده_MAX_قاب_HINT_NV    0x3338
#پایان_اگر /* EGL_NV_stream_frame_limits */

#اگر_تعریف_نشده EGL_NV_جریان_metadata
#تعریف_کن EGL_NV_جریان_metadata 1
#تعریف_کن EGL_MAX_جریان_METADATA_بلوکها_NV 0x3250
#تعریف_کن EGL_MAX_جریان_METADATA_بلوک_اندازه_NV 0x3251
#تعریف_کن EGL_MAX_جریان_METADATA_مجموع_اندازه_NV 0x3252
#تعریف_کن EGL_تولیدکننده_METADATA_NV          0x3253
#تعریف_کن EGL_مصرفکننده_METADATA_NV          0x3254
#تعریف_کن EGL_PENDING_METADATA_NV           0x3328
#تعریف_کن EGL_METADATA0_اندازه_NV             0x3255
#تعریف_کن EGL_METADATA1_اندازه_NV             0x3256
#تعریف_کن EGL_METADATA2_اندازه_NV             0x3257
#تعریف_کن EGL_METADATA3_اندازه_NV             0x3258
#تعریف_کن EGL_METADATA0_TYPE_NV             0x3259
#تعریف_کن EGL_METADATA1_TYPE_NV             0x325A
#تعریف_کن EGL_METADATA2_TYPE_NV             0x325B
#تعریف_کن EGL_METADATA3_TYPE_NV             0x325C
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDISPLAYATTRIBNVPROC) (EGLDisplay dpy, EGLint attribute, EGLAttrib *مقدار);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSETSTREAMMETADATANVPROC) (EGLDisplay dpy, EGLStreamKHR جریان, EGLint n, EGLint جابه_جایی_2, EGLint اندازه, ثابت فراغ *داده);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMMETADATANVPROC) (EGLDisplay dpy, EGLStreamKHR جریان, EGLenum name, EGLint n, EGLint جابه_جایی_2, EGLint اندازه, فراغ *داده);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDisplayAttribNV (EGLDisplay dpy, EGLint attribute, EGLAttrib *مقدار);
EGLAPI EGLBoolean EGLAPIENTRY egl_مجموعه_جریان_Metadata_NV (EGLDisplay dpy, EGLStreamKHR جریان, EGLint n, EGLint جابه_جایی_2, EGLint اندازه, ثابت فراغ *داده);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_جریان_Metadata_NV (EGLDisplay dpy, EGLStreamKHR جریان, EGLenum name, EGLint n, EGLint جابه_جایی_2, EGLint اندازه, فراغ *داده);
#پایان_اگر
#پایان_اگر /* EGL_NV_stream_metadata */

#اگر_تعریف_نشده EGL_NV_جریان_origin
#تعریف_کن EGL_NV_جریان_origin 1
#تعریف_کن EGL_جریان_قاب_ORIGIN_X_NV      0x3366
#تعریف_کن EGL_جریان_قاب_ORIGIN_Y_NV      0x3367
#تعریف_کن EGL_جریان_قاب_MAJOR_AXIS_NV    0x3368
#تعریف_کن EGL_مصرفکننده_AUTO_ORIENTATION_NV  0x3369
#تعریف_کن EGL_تولیدکننده_AUTO_ORIENTATION_NV  0x336A
#تعریف_کن EGL_چپ_NV                       0x336B
#تعریف_کن EGL_راست_NV                      0x336C
#تعریف_کن EGL_بالاترین_NV                        0x336D
#تعریف_کن EGL_BOTTOM_NV                     0x336E
#تعریف_کن EGL_X_AXIS_NV                     0x336F
#تعریف_کن EGL_Y_AXIS_NV                     0x3370
#پایان_اگر /* EGL_NV_stream_origin */

#اگر_تعریف_نشده EGL_NV_جریان_remote
#تعریف_کن EGL_NV_جریان_remote 1
#تعریف_کن EGL_جریان_STATE_INITIALIZING_NV  0x3240
#تعریف_کن EGL_جریان_TYPE_NV                0x3241
#تعریف_کن EGL_جریان_PROTOCOL_NV            0x3242
#تعریف_کن EGL_جریان_ENDPOINT_NV            0x3243
#تعریف_کن EGL_جریان_LOCAL_NV               0x3244
#تعریف_کن EGL_جریان_تولیدکننده_NV            0x3247
#تعریف_کن EGL_جریان_مصرفکننده_NV            0x3248
#تعریف_کن EGL_جریان_PROTOCOL_FD_NV         0x3246
#پایان_اگر /* EGL_NV_stream_remote */

#اگر_تعریف_نشده EGL_NV_جریان_reset
#تعریف_کن EGL_NV_جریان_reset 1
#تعریف_کن EGL_SUPPORT_RESET_NV              0x3334
#تعریف_کن EGL_SUPPORT_REUSE_NV              0x3335
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLRESETSTREAMNVPROC) (EGLDisplay dpy, EGLStreamKHR جریان);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Reset_جریان_NV (EGLDisplay dpy, EGLStreamKHR جریان);
#پایان_اگر
#پایان_اگر /* EGL_NV_stream_reset */

#اگر_تعریف_نشده EGL_NV_جریان_socket
#تعریف_کن EGL_NV_جریان_socket 1
#تعریف_کن EGL_جریان_PROTOCOL_SOCKET_NV     0x324B
#تعریف_کن EGL_SOCKET_HANDLE_NV              0x324C
#تعریف_کن EGL_SOCKET_TYPE_NV                0x324D
#پایان_اگر /* EGL_NV_stream_socket */

#اگر_تعریف_نشده EGL_NV_جریان_socket_inet
#تعریف_کن EGL_NV_جریان_socket_inet 1
#تعریف_کن EGL_SOCKET_TYPE_INET_NV           0x324F
#پایان_اگر /* EGL_NV_stream_socket_inet */

#اگر_تعریف_نشده EGL_NV_جریان_socket_unix
#تعریف_کن EGL_NV_جریان_socket_unix 1
#تعریف_کن EGL_SOCKET_TYPE_UNIX_NV           0x324E
#پایان_اگر /* EGL_NV_stream_socket_unix */

#اگر_تعریف_نشده EGL_NV_جریان_sync
#تعریف_کن EGL_NV_جریان_sync 1
#تعریف_کن EGL_SYNC_NEW_قاب_NV             0x321F
تعريفنوع EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESTREAMSYNCNVPROC) (EGLDisplay dpy, EGLStreamKHR جریان, EGLenum type, ثابت EGLint *attrib_list);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncKHR EGLAPIENTRY egl_Create_جریان_Sync_NV (EGLDisplay dpy, EGLStreamKHR جریان, EGLenum type, ثابت EGLint *attrib_list);
#پایان_اگر
#پایان_اگر /* EGL_NV_stream_sync */

#اگر_تعریف_نشده EGL_NV_sync
#تعریف_کن EGL_NV_sync 1
تعريفنوع فراغ *EGLSyncNV;
تعريفنوع khronos_utime_nanoseconds_t EGLTimeNV;
#اگر_تعریف_شده KHRONOS_SUPPORT_INT64
#تعریف_کن EGL_SYNC_پیشین_COMMANDS_COMPLETE_NV 0x30E6
#تعریف_کن EGL_SYNC_وضعیت_NV                0x30E7
#تعریف_کن EGL_SIGNALED_NV                   0x30E8
#تعریف_کن EGL_UNSIGNALED_NV                 0x30E9
#تعریف_کن EGL_SYNC_FLUSH_COMMANDS_بیت_NV    0x0001
#تعریف_کن EGL_FOREVER_NV                    0xFFFFFFFFFFFFFFFFull
#تعریف_کن EGL_ALREADY_SIGNALED_NV           0x30EA
#تعریف_کن EGL_TIMEOUT_EXPIRED_NV            0x30EB
#تعریف_کن EGL_CONDITION_SATISFIED_NV        0x30EC
#تعریف_کن EGL_SYNC_TYPE_NV                  0x30ED
#تعریف_کن EGL_SYNC_CONDITION_NV             0x30EE
#تعریف_کن EGL_SYNC_FENCE_NV                 0x30EF
#تعریف_کن EGL_NO_SYNC_NV                    EGL_CAST(EGLSyncNV,0)
تعريفنوع EGLSyncNV (EGLAPIENTRYP PFNEGLCREATEFENCESYNCNVPROC) (EGLDisplay dpy, EGLenum condition, ثابت EGLint *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCNVPROC) (EGLSyncNV sync);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLFENCENVPROC) (EGLSyncNV sync);
تعريفنوع EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCNVPROC) (EGLSyncNV sync, EGLint flags, EGLTimeNV timeout);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSIGNALSYNCNVPROC) (EGLSyncNV sync, EGLenum نما);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETSYNCATTRIBNVPROC) (EGLSyncNV sync, EGLint attribute, EGLint *مقدار);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncNV EGLAPIENTRY eglCreateFenceSyncNV (EGLDisplay dpy, EGLenum condition, ثابت EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySyncNV (EGLSyncNV sync);
EGLAPI EGLBoolean EGLAPIENTRY eglFenceNV (EGLSyncNV sync);
EGLAPI EGLint EGLAPIENTRY eglClientWaitSyncNV (EGLSyncNV sync, EGLint flags, EGLTimeNV timeout);
EGLAPI EGLBoolean EGLAPIENTRY eglSignalSyncNV (EGLSyncNV sync, EGLenum نما);
EGLAPI EGLBoolean EGLAPIENTRY eglGetSyncAttribNV (EGLSyncNV sync, EGLint attribute, EGLint *مقدار);
#پایان_اگر
#پایان_اگر /* KHRONOS_SUPPORT_INT64 */
#پایان_اگر /* EGL_NV_sync */

#اگر_تعریف_نشده EGL_NV_system_زمان
#تعریف_کن EGL_NV_system_زمان 1
تعريفنوع khronos_utime_nanoseconds_t EGLuint64NV;
#اگر_تعریف_شده KHRONOS_SUPPORT_INT64
تعريفنوع EGLuint64NV (EGLAPIENTRYP PFNEGLGETSYSTEMTIMEFREQUENCYNVPROC) (فراغ);
تعريفنوع EGLuint64NV (EGLAPIENTRYP PFNEGLGETSYSTEMTIMENVPROC) (فراغ);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLuint64NV EGLAPIENTRY egl_Get_System_زمان_Frequency_NV (فراغ);
EGLAPI EGLuint64NV EGLAPIENTRY egl_Get_System_زمان_NV (فراغ);
#پایان_اگر
#پایان_اگر /* KHRONOS_SUPPORT_INT64 */
#پایان_اگر /* EGL_NV_system_time */

#اگر_تعریف_نشده EGL_NV_triple_میانگیر
#تعریف_کن EGL_NV_triple_میانگیر 1
#تعریف_کن EGL_TRIPLE_میانگیر_NV              0x3230
#پایان_اگر /* EGL_NV_triple_buffer */

#اگر_تعریف_نشده EGL_QNX_image_native_میانگیر
#تعریف_کن EGL_QNX_image_native_میانگیر 1
#تعریف_کن EGL_NATIVE_میانگیر_QNX             0x3551
#پایان_اگر /* EGL_QNX_image_native_buffer */

#اگر_تعریف_نشده EGL_QNX_platform_screen
#تعریف_کن EGL_QNX_platform_screen 1
#تعریف_کن EGL_PLATFORM_SCREEN_QNX           0x3550
#پایان_اگر /* EGL_QNX_platform_screen */

#اگر_تعریف_نشده EGL_TIZEN_image_native_میانگیر
#تعریف_کن EGL_TIZEN_image_native_میانگیر 1
#تعریف_کن EGL_NATIVE_میانگیر_TIZEN           0x32A0
#پایان_اگر /* EGL_TIZEN_image_native_buffer */

#اگر_تعریف_نشده EGL_TIZEN_image_native_surface
#تعریف_کن EGL_TIZEN_image_native_surface 1
#تعریف_کن EGL_NATIVE_SURFACE_TIZEN          0x32A1
#پایان_اگر /* EGL_TIZEN_image_native_surface */

#اگر_تعریف_نشده EGL_WL_bind_wayland_display
#تعریف_کن EGL_WL_bind_wayland_display 1
#تعریف_کن PFNEGLBINDWAYLANDDISPLAYWL PFNEGLBINDWAYLANDDISPLAYWLPROC
#تعریف_کن PFNEGLUNBINDWAYLANDDISPLAYWL PFNEGLUNBINDWAYLANDDISPLAYWLPROC
#تعریف_کن PFNEGLQUERYWAYLANDBUFFERWL PFNEGLQUERYWAYLANDBUFFERWLPROC
بنية wl_display;
بنية wl_resource;
#تعریف_کن EGL_WAYLAND_میانگیر_WL             0x31D5
#تعریف_کن EGL_WAYLAND_PLANE_WL              0x31D6
#تعریف_کن EGL_TEXTURE_Y_U_V_WL              0x31D7
#تعریف_کن EGL_TEXTURE_Y_UV_WL               0x31D8
#تعریف_کن EGL_TEXTURE_Y_XUXV_WL             0x31D9
#تعریف_کن EGL_TEXTURE_EXTERNAL_WL           0x31DA
#تعریف_کن EGL_WAYLAND_Y_INVERTED_WL         0x31DB
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLBINDWAYLANDDISPLAYWLPROC) (EGLDisplay dpy, بنية wl_display *display);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLUNBINDWAYLANDDISPLAYWLPROC) (EGLDisplay dpy, بنية wl_display *display);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYWAYLANDBUFFERWLPROC) (EGLDisplay dpy, بنية wl_resource *میانگیر_2, EGLint attribute, EGLint *مقدار);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglBindWaylandDisplayWL (EGLDisplay dpy, بنية wl_display *display);
EGLAPI EGLBoolean EGLAPIENTRY eglUnbindWaylandDisplayWL (EGLDisplay dpy, بنية wl_display *display);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Wayland_میانگیر_WL (EGLDisplay dpy, بنية wl_resource *میانگیر_2, EGLint attribute, EGLint *مقدار);
#پایان_اگر
#پایان_اگر /* EGL_WL_bind_wayland_display */

#اگر_تعریف_نشده EGL_WL_create_wayland_میانگیر_from_image
#تعریف_کن EGL_WL_create_wayland_میانگیر_from_image 1
#تعریف_کن PFNEGLCREATEWAYLANDBUFFERFROMIMAGEWL PFNEGLCREATEWAYLANDBUFFERFROMIMAGEWLPROC
بنية wl_میانگیر;
تعريفنوع بنية wl_میانگیر *(EGLAPIENTRYP PFNEGLCREATEWAYLANDBUFFERFROMIMAGEWLPROC) (EGLDisplay dpy, EGLImageKHR image);
#اگر_تعریف_شده EGL_EGLEXT_PROTOTYPES
EGLAPI بنية wl_میانگیر *EGLAPIENTRY egl_Create_Wayland_میانگیر_From_Image_WL (EGLDisplay dpy, EGLImageKHR image);
#پایان_اگر
#پایان_اگر /* EGL_WL_create_wayland_buffer_from_image */

#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر
