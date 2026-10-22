#جيڪڏهن_وصف_نه_ٿيل __eglext_h_
#وصف_ڪريو __eglext_h_ 1

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

#وصف_ڪريو EGL_EGLEXT_نسخو 20260319

/* Generated C header for:
 * API: egl
 * Versions considered: .*
 * Versions emitted: _nomatch_^
 * Default extensions included: egl
 * Additional extensions included: _nomatch_^
 * Extensions removed: _nomatch_^
 */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_cl_event
#وصف_ڪريو EGL_KHR_cl_event 1
#وصف_ڪريو EGL_CL_EVENT_HANDLE_KHR           0x309C
#وصف_ڪريو EGL_SYNC_CL_EVENT_KHR             0x30FE
#وصف_ڪريو EGL_SYNC_CL_EVENT_COMPLETE_KHR    0x30FF
#جيڪڏهن_پورو /* EGL_KHR_cl_event */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_cl_event2
#وصف_ڪريو EGL_KHR_cl_event2 1
تعريفنوع فراغ *EGLSyncKHR;
تعريفنوع intptr_t EGLAttribKHR;
تعريفنوع EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESYNC64KHRPROC) (EGLDisplay dpy, EGLenum type, ثابت EGLAttribKHR *attrib_list);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncKHR EGLAPIENTRY eglCreateSync64KHR (EGLDisplay dpy, EGLenum type, ثابت EGLAttribKHR *attrib_list);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_KHR_cl_event2 */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_client_get_all_proc_پتا
#وصف_ڪريو EGL_KHR_client_get_all_proc_پتا 1
#جيڪڏهن_پورو /* EGL_KHR_client_get_all_proc_addresses */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_config_attribs
#وصف_ڪريو EGL_KHR_config_attribs 1
#وصف_ڪريو EGL_CONFORMANT_KHR                0x3042
#وصف_ڪريو EGL_VG_COLORSPACE_لڪيري_ٻٽو_انگ_KHR  0x0020
#وصف_ڪريو EGL_VG_ALPHA_FORMAT_PRE_ٻٽو_انگ_KHR   0x0040
#جيڪڏهن_پورو /* EGL_KHR_config_attribs */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_context_flush_control
#وصف_ڪريو EGL_KHR_context_flush_control 1
#وصف_ڪريو EGL_CONTEXT_RELEASE_BEHAVIOR_NONE_KHR 0
#وصف_ڪريو EGL_CONTEXT_RELEASE_BEHAVIOR_KHR  0x2097
#وصف_ڪريو EGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_KHR 0x2098
#جيڪڏهن_پورو /* EGL_KHR_context_flush_control */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_create_context
#وصف_ڪريو EGL_KHR_create_context 1
#وصف_ڪريو EGL_CONTEXT_MAJOR_نسخو_KHR     0x3098
#وصف_ڪريو EGL_CONTEXT_MINOR_نسخو_KHR     0x30FB
#وصف_ڪريو EGL_CONTEXT_FLAGS_KHR             0x30FC
#وصف_ڪريو EGL_CONTEXT_OPENGL_PROFILE_نقاب_KHR 0x30FD
#وصف_ڪريو EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_KHR 0x31BD
#وصف_ڪريو EGL_NO_RESET_NOTIFICATION_KHR     0x31BE
#وصف_ڪريو EGL_LOSE_CONTEXT_ON_RESET_KHR     0x31BF
#وصف_ڪريو EGL_CONTEXT_OPENGL_DEBUG_ٻٽو_انگ_KHR  0x00000001
#وصف_ڪريو EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_ٻٽو_انگ_KHR 0x00000002
#وصف_ڪريو EGL_CONTEXT_OPENGL_ROBUST_ACCESS_ٻٽو_انگ_KHR 0x00000004
#وصف_ڪريو EGL_CONTEXT_OPENGL_CORE_PROFILE_ٻٽو_انگ_KHR 0x00000001
#وصف_ڪريو EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_ٻٽو_انگ_KHR 0x00000002
#وصف_ڪريو EGL_OPENGL_ES3_ٻٽو_انگ_KHR            0x00000040
#جيڪڏهن_پورو /* EGL_KHR_create_context */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_create_context_no_error
#وصف_ڪريو EGL_KHR_create_context_no_error 1
#وصف_ڪريو EGL_CONTEXT_OPENGL_NO_ERROR_KHR   0x31B3
#جيڪڏهن_پورو /* EGL_KHR_create_context_no_error */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_debug
#وصف_ڪريو EGL_KHR_debug 1
تعريفنوع فراغ *EGLLabelKHR;
تعريفنوع فراغ *EGLObjectKHR;
تعريفنوع فراغ (EGLAPIENTRY  *EGLDEBUGPROCKHR)(EGLenum error,ثابت حرف *command,EGLint پيغام_Type,EGLLabelKHR threadLabel,EGLLabelKHR objectLabel,ثابت حرف* پيغام);
#وصف_ڪريو EGL_OBJECT_THREAD_KHR             0x33B0
#وصف_ڪريو EGL_OBJECT_DISPLAY_KHR            0x33B1
#وصف_ڪريو EGL_OBJECT_CONTEXT_KHR            0x33B2
#وصف_ڪريو EGL_OBJECT_SURFACE_KHR            0x33B3
#وصف_ڪريو EGL_OBJECT_IMAGE_KHR              0x33B4
#وصف_ڪريو EGL_OBJECT_SYNC_KHR               0x33B5
#وصف_ڪريو EGL_OBJECT_وهڪرو_KHR             0x33B6
#وصف_ڪريو EGL_DEBUG_نياپو_CRITICAL_KHR        0x33B9
#وصف_ڪريو EGL_DEBUG_نياپو_ERROR_KHR           0x33BA
#وصف_ڪريو EGL_DEBUG_نياپو_WARN_KHR            0x33BB
#وصف_ڪريو EGL_DEBUG_نياپو_INFO_KHR            0x33BC
#وصف_ڪريو EGL_DEBUG_CALLBACK_KHR            0x33B8
تعريفنوع EGLint (EGLAPIENTRYP PFNEGLDEBUGMESSAGECONTROLKHRPROC) (EGLDEBUGPROCKHR callback, ثابت EGLAttrib *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEBUGKHRPROC) (EGLint attribute, EGLAttrib *قدر);
تعريفنوع EGLint (EGLAPIENTRYP PFNEGLLABELOBJECTKHRPROC) (EGLDisplay display, EGLenum objectType, EGLObjectKHR object, EGLLabelKHR label);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLint EGLAPIENTRY egl_Debug_پيغام_Control_KHR (EGLDEBUGPROCKHR callback, ثابت EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDebugKHR (EGLint attribute, EGLAttrib *قدر);
EGLAPI EGLint EGLAPIENTRY eglLabelObjectKHR (EGLDisplay display, EGLenum objectType, EGLObjectKHR object, EGLLabelKHR label);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_KHR_debug */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_display_reference
#وصف_ڪريو EGL_KHR_display_reference 1
#وصف_ڪريو EGL_TRACK_REFERENCES_KHR          0x3352
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDISPLAYATTRIBKHRPROC) (EGLDisplay dpy, EGLint name, EGLAttrib *قدر);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDisplayAttribKHR (EGLDisplay dpy, EGLint name, EGLAttrib *قدر);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_KHR_display_reference */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_fence_sync
#وصف_ڪريو EGL_KHR_fence_sync 1
تعريفنوع khronos_utime_nanoseconds_t EGLTimeKHR;
#جيڪڏهن_وصف_ٿيل KHRONOS_SUPPORT_INT64
#وصف_ڪريو EGL_SYNC_اڳواٽ_COMMANDS_COMPLETE_KHR 0x30F0
#وصف_ڪريو EGL_SYNC_CONDITION_KHR            0x30F8
#وصف_ڪريو EGL_SYNC_FENCE_KHR                0x30F9
تعريفنوع EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESYNCKHRPROC) (EGLDisplay dpy, EGLenum type, ثابت EGLint *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync);
تعريفنوع EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETSYNCATTRIBKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint attribute, EGLint *قدر);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncKHR EGLAPIENTRY eglCreateSyncKHR (EGLDisplay dpy, EGLenum type, ثابت EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySyncKHR (EGLDisplay dpy, EGLSyncKHR sync);
EGLAPI EGLint EGLAPIENTRY eglClientWaitSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);
EGLAPI EGLBoolean EGLAPIENTRY eglGetSyncAttribKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint attribute, EGLint *قدر);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* KHRONOS_SUPPORT_INT64 */
#جيڪڏهن_پورو /* EGL_KHR_fence_sync */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_get_all_proc_پتا
#وصف_ڪريو EGL_KHR_get_all_proc_پتا 1
#جيڪڏهن_پورو /* EGL_KHR_get_all_proc_addresses */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_gl_colorspace
#وصف_ڪريو EGL_KHR_gl_colorspace 1
#وصف_ڪريو EGL_GL_COLORSPACE_KHR             0x309D
#وصف_ڪريو EGL_GL_COLORSPACE_SRGB_KHR        0x3089
#وصف_ڪريو EGL_GL_COLORSPACE_لڪيري_KHR      0x308A
#جيڪڏهن_پورو /* EGL_KHR_gl_colorspace */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_gl_renderbuffer_image
#وصف_ڪريو EGL_KHR_gl_renderbuffer_image 1
#وصف_ڪريو EGL_GL_RENDERBUFFER_KHR           0x30B9
#جيڪڏهن_پورو /* EGL_KHR_gl_renderbuffer_image */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_gl_texture_2D_image
#وصف_ڪريو EGL_KHR_gl_texture_2D_image 1
#وصف_ڪريو EGL_GL_TEXTURE_2D_KHR             0x30B1
#وصف_ڪريو EGL_GL_TEXTURE_LEVEL_KHR          0x30BC
#جيڪڏهن_پورو /* EGL_KHR_gl_texture_2D_image */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_gl_texture_3D_image
#وصف_ڪريو EGL_KHR_gl_texture_3D_image 1
#وصف_ڪريو EGL_GL_TEXTURE_3D_KHR             0x30B2
#وصف_ڪريو EGL_GL_TEXTURE_ZOFFSET_KHR        0x30BD
#جيڪڏهن_پورو /* EGL_KHR_gl_texture_3D_image */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_gl_texture_cubemap_image
#وصف_ڪريو EGL_KHR_gl_texture_cubemap_image 1
#وصف_ڪريو EGL_GL_TEXTURE_CUBE_MAP_مثبت_X_KHR 0x30B3
#وصف_ڪريو EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_X_KHR 0x30B4
#وصف_ڪريو EGL_GL_TEXTURE_CUBE_MAP_مثبت_Y_KHR 0x30B5
#وصف_ڪريو EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_KHR 0x30B6
#وصف_ڪريو EGL_GL_TEXTURE_CUBE_MAP_مثبت_Z_KHR 0x30B7
#وصف_ڪريو EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_KHR 0x30B8
#جيڪڏهن_پورو /* EGL_KHR_gl_texture_cubemap_image */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_image
#وصف_ڪريو EGL_KHR_image 1
تعريفنوع فراغ *EGLImageKHR;
#وصف_ڪريو EGL_NATIVE_PIXMAP_KHR             0x30B0
#وصف_ڪريو EGL_NO_IMAGE_KHR                  EGL_CAST(EGLImageKHR,0)
تعريفنوع EGLImageKHR (EGLAPIENTRYP PFNEGLCREATEIMAGEKHRPROC) (EGLDisplay dpy, EGLContext ctx, EGLenum هدف, EGLClient_بفر بفر_2, ثابت EGLint *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYIMAGEKHRPROC) (EGLDisplay dpy, EGLImageKHR image);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLImageKHR EGLAPIENTRY eglCreateImageKHR (EGLDisplay dpy, EGLContext ctx, EGLenum هدف, EGLClient_بفر بفر_2, ثابت EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyImageKHR (EGLDisplay dpy, EGLImageKHR image);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_KHR_image */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_image_بنياد
#وصف_ڪريو EGL_KHR_image_بنياد 1
#وصف_ڪريو EGL_IMAGE_PRESERVED_KHR           0x30D2
#جيڪڏهن_پورو /* EGL_KHR_image_base */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_image_pixmap
#وصف_ڪريو EGL_KHR_image_pixmap 1
#جيڪڏهن_پورو /* EGL_KHR_image_pixmap */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_تالو_surface
#وصف_ڪريو EGL_KHR_تالو_surface 1
#وصف_ڪريو EGL_READ_SURFACE_ٻٽو_انگ_KHR          0x0001
#وصف_ڪريو EGL_WRITE_SURFACE_ٻٽو_انگ_KHR         0x0002
#وصف_ڪريو EGL_تالو_SURFACE_ٻٽو_انگ_KHR          0x0080
#وصف_ڪريو EGL_OPTIMAL_FORMAT_ٻٽو_انگ_KHR        0x0100
#وصف_ڪريو EGL_ميلاپ_FORMAT_KHR              0x3043
#وصف_ڪريو EGL_FORMAT_RGB_565_EXACT_KHR      0x30C0
#وصف_ڪريو EGL_FORMAT_RGB_565_KHR            0x30C1
#وصف_ڪريو EGL_FORMAT_RGBA_8888_EXACT_KHR    0x30C2
#وصف_ڪريو EGL_FORMAT_RGBA_8888_KHR          0x30C3
#وصف_ڪريو EGL_MAP_PRESERVE_PIXELS_KHR       0x30C4
#وصف_ڪريو EGL_تالو_USAGE_HINT_KHR           0x30C5
#وصف_ڪريو EGL_BITMAP_اشارو_KHR            0x30C6
#وصف_ڪريو EGL_BITMAP_PITCH_KHR              0x30C7
#وصف_ڪريو EGL_BITMAP_ORIGIN_KHR             0x30C8
#وصف_ڪريو EGL_BITMAP_PIXEL_RED_وٿي_KHR   0x30C9
#وصف_ڪريو EGL_BITMAP_PIXEL_GREEN_وٿي_KHR 0x30CA
#وصف_ڪريو EGL_BITMAP_PIXEL_BLUE_وٿي_KHR  0x30CB
#وصف_ڪريو EGL_BITMAP_PIXEL_ALPHA_وٿي_KHR 0x30CC
#وصف_ڪريو EGL_BITMAP_PIXEL_LUMINANCE_وٿي_KHR 0x30CD
#وصف_ڪريو EGL_هيٺاهون_کاٻو_KHR                0x30CE
#وصف_ڪريو EGL_مٿانهون_کاٻو_KHR                0x30CF
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLLOCKSURFACEKHRPROC) (EGLDisplay dpy, EGLSurface surface, ثابت EGLint *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLUNLOCKSURFACEKHRPROC) (EGLDisplay dpy, EGLSurface surface);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_تالو_Surface_KHR (EGLDisplay dpy, EGLSurface surface, ثابت EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglUnlockSurfaceKHR (EGLDisplay dpy, EGLSurface surface);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_KHR_lock_surface */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_تالو_surface2
#وصف_ڪريو EGL_KHR_تالو_surface2 1
#وصف_ڪريو EGL_BITMAP_PIXEL_سائيز_KHR         0x3110
#جيڪڏهن_پورو /* EGL_KHR_lock_surface2 */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_تالو_surface3
#وصف_ڪريو EGL_KHR_تالو_surface3 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSURFACE64KHRPROC) (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLAttribKHR *قدر);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQuerySurface64KHR (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLAttribKHR *قدر);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_KHR_lock_surface3 */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_mutable_render_بفر
#وصف_ڪريو EGL_KHR_mutable_render_بفر 1
#وصف_ڪريو EGL_MUTABLE_RENDER_بفر_ٻٽو_انگ_KHR 0x1000
#جيڪڏهن_پورو /* EGL_KHR_mutable_render_buffer */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_no_config_context
#وصف_ڪريو EGL_KHR_no_config_context 1
#وصف_ڪريو EGL_NO_CONFIG_KHR                 EGL_CAST(EGLConfig,0)
#جيڪڏهن_پورو /* EGL_KHR_no_config_context */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_partial_update
#وصف_ڪريو EGL_KHR_partial_update 1
#وصف_ڪريو EGL_بفر_AGE_KHR                0x313D
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSETDAMAGEREGIONKHRPROC) (EGLDisplay dpy, EGLSurface surface, EGLint *rects, EGLint n_rects);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_سيٽ_Damage_Region_KHR (EGLDisplay dpy, EGLSurface surface, EGLint *rects, EGLint n_rects);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_KHR_partial_update */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_platform_android
#وصف_ڪريو EGL_KHR_platform_android 1
#وصف_ڪريو EGL_PLATFORM_ANDROID_KHR          0x3141
#جيڪڏهن_پورو /* EGL_KHR_platform_android */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_platform_gbm
#وصف_ڪريو EGL_KHR_platform_gbm 1
#وصف_ڪريو EGL_PLATFORM_GBM_KHR              0x31D7
#جيڪڏهن_پورو /* EGL_KHR_platform_gbm */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_platform_wayland
#وصف_ڪريو EGL_KHR_platform_wayland 1
#وصف_ڪريو EGL_PLATFORM_WAYLAND_KHR          0x31D8
#جيڪڏهن_پورو /* EGL_KHR_platform_wayland */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_platform_x11
#وصف_ڪريو EGL_KHR_platform_x11 1
#وصف_ڪريو EGL_PLATFORM_X11_KHR              0x31D5
#وصف_ڪريو EGL_PLATFORM_X11_SCREEN_KHR       0x31D6
#جيڪڏهن_پورو /* EGL_KHR_platform_x11 */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_reusable_sync
#وصف_ڪريو EGL_KHR_reusable_sync 1
#جيڪڏهن_وصف_ٿيل KHRONOS_SUPPORT_INT64
#وصف_ڪريو EGL_SYNC_حالت_KHR               0x30F1
#وصف_ڪريو EGL_SIGNALED_KHR                  0x30F2
#وصف_ڪريو EGL_UNSIGNALED_KHR                0x30F3
#وصف_ڪريو EGL_TIMEOUT_EXPIRED_KHR           0x30F5
#وصف_ڪريو EGL_CONDITION_SATISFIED_KHR       0x30F6
#وصف_ڪريو EGL_SYNC_TYPE_KHR                 0x30F7
#وصف_ڪريو EGL_SYNC_REUSABLE_KHR             0x30FA
#وصف_ڪريو EGL_SYNC_FLUSH_COMMANDS_ٻٽو_انگ_KHR   0x0001
#وصف_ڪريو EGL_FOREVER_KHR                   0xFFFFFFFFFFFFFFFFull
#وصف_ڪريو EGL_NO_SYNC_KHR                   EGL_CAST(EGLSyncKHR,0)
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSIGNALSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLenum گهڻائي);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglSignalSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLenum گهڻائي);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* KHRONOS_SUPPORT_INT64 */
#جيڪڏهن_پورو /* EGL_KHR_reusable_sync */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_وهڪرو
#وصف_ڪريو EGL_KHR_وهڪرو 1
تعريفنوع فراغ *EGLStreamKHR;
تعريفنوع khronos_uint64_t EGLuint64KHR;
#جيڪڏهن_وصف_ٿيل KHRONOS_SUPPORT_INT64
#وصف_ڪريو EGL_NO_وهڪرو_KHR                 EGL_CAST(EGLStreamKHR,0)
#وصف_ڪريو EGL_استعمال_ڪندڙ_LATENCY_USEC_KHR     0x3210
#وصف_ڪريو EGL_پيداوار_ڪندڙ_چوکٺو_KHR            0x3212
#وصف_ڪريو EGL_استعمال_ڪندڙ_چوکٺو_KHR            0x3213
#وصف_ڪريو EGL_وهڪرو_STATE_KHR              0x3214
#وصف_ڪريو EGL_وهڪرو_STATE_CREATED_KHR      0x3215
#وصف_ڪريو EGL_وهڪرو_STATE_CONNECTING_KHR   0x3216
#وصف_ڪريو EGL_وهڪرو_STATE_خالي_جايون_KHR        0x3217
#وصف_ڪريو EGL_وهڪرو_STATE_NEW_چوکٺو_موجود_KHR 0x3218
#وصف_ڪريو EGL_وهڪرو_STATE_OLD_چوکٺو_موجود_KHR 0x3219
#وصف_ڪريو EGL_وهڪرو_STATE_DISCONNECTED_KHR 0x321A
#وصف_ڪريو EGL_BAD_وهڪرو_KHR                0x321B
#وصف_ڪريو EGL_BAD_STATE_KHR                 0x321C
تعريفنوع EGLStreamKHR (EGLAPIENTRYP PFNEGLCREATESTREAMKHRPROC) (EGLDisplay dpy, ثابت EGLint *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSTREAMKHRPROC) (EGLDisplay dpy, EGLStreamKHR وهڪرو);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR وهڪرو, EGLenum attribute, EGLint قدر);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMKHRPROC) (EGLDisplay dpy, EGLStreamKHR وهڪرو, EGLenum attribute, EGLint *قدر);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMU64KHRPROC) (EGLDisplay dpy, EGLStreamKHR وهڪرو, EGLenum attribute, EGLuint64KHR *قدر);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLStreamKHR EGLAPIENTRY egl_Create_وهڪرو_KHR (EGLDisplay dpy, ثابت EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY egl_Destroy_وهڪرو_KHR (EGLDisplay dpy, EGLStreamKHR وهڪرو);
EGLAPI EGLBoolean EGLAPIENTRY egl_وهڪرو_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR وهڪرو, EGLenum attribute, EGLint قدر);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_وهڪرو_KHR (EGLDisplay dpy, EGLStreamKHR وهڪرو, EGLenum attribute, EGLint *قدر);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryStreamu64KHR (EGLDisplay dpy, EGLStreamKHR وهڪرو, EGLenum attribute, EGLuint64KHR *قدر);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* KHRONOS_SUPPORT_INT64 */
#جيڪڏهن_پورو /* EGL_KHR_stream */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_وهڪرو_attrib
#وصف_ڪريو EGL_KHR_وهڪرو_attrib 1
#جيڪڏهن_وصف_ٿيل KHRONOS_SUPPORT_INT64
تعريفنوع EGLStreamKHR (EGLAPIENTRYP PFNEGLCREATESTREAMATTRIBKHRPROC) (EGLDisplay dpy, ثابت EGLAttrib *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSETSTREAMATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR وهڪرو, EGLenum attribute, EGLAttrib قدر);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR وهڪرو, EGLenum attribute, EGLAttrib *قدر);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERACQUIREATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR وهڪرو, ثابت EGLAttrib *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERRELEASEATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR وهڪرو, ثابت EGLAttrib *attrib_list);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLStreamKHR EGLAPIENTRY egl_Create_وهڪرو_Attrib_KHR (EGLDisplay dpy, ثابت EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY egl_سيٽ_وهڪرو_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR وهڪرو, EGLenum attribute, EGLAttrib قدر);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_وهڪرو_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR وهڪرو, EGLenum attribute, EGLAttrib *قدر);
EGLAPI EGLBoolean EGLAPIENTRY egl_وهڪرو_استعمال_ڪندڙ_Acquire_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR وهڪرو, ثابت EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY egl_وهڪرو_استعمال_ڪندڙ_Release_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR وهڪرو, ثابت EGLAttrib *attrib_list);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* KHRONOS_SUPPORT_INT64 */
#جيڪڏهن_پورو /* EGL_KHR_stream_attrib */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_وهڪرو_استعمال_ڪندڙ_gltexture
#وصف_ڪريو EGL_KHR_وهڪرو_استعمال_ڪندڙ_gltexture 1
#جيڪڏهن_وصف_ٿيل EGL_KHR_وهڪرو
#وصف_ڪريو EGL_استعمال_ڪندڙ_ACQUIRE_TIMEOUT_USEC_KHR 0x321E
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALKHRPROC) (EGLDisplay dpy, EGLStreamKHR وهڪرو);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERACQUIREKHRPROC) (EGLDisplay dpy, EGLStreamKHR وهڪرو);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERRELEASEKHRPROC) (EGLDisplay dpy, EGLStreamKHR وهڪرو);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_وهڪرو_استعمال_ڪندڙ_GLTexture_External_KHR (EGLDisplay dpy, EGLStreamKHR وهڪرو);
EGLAPI EGLBoolean EGLAPIENTRY egl_وهڪرو_استعمال_ڪندڙ_Acquire_KHR (EGLDisplay dpy, EGLStreamKHR وهڪرو);
EGLAPI EGLBoolean EGLAPIENTRY egl_وهڪرو_استعمال_ڪندڙ_Release_KHR (EGLDisplay dpy, EGLStreamKHR وهڪرو);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_KHR_stream */
#جيڪڏهن_پورو /* EGL_KHR_stream_consumer_gltexture */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_وهڪرو_cross_process_fd
#وصف_ڪريو EGL_KHR_وهڪرو_cross_process_fd 1
تعريفنوع صحيح EGLNativeFileDescriptorKHR;
#جيڪڏهن_وصف_ٿيل EGL_KHR_وهڪرو
#وصف_ڪريو EGL_NO_FILE_DESCRIPTOR_KHR        EGL_CAST(EGLNativeFileDescriptorKHR,-1)
تعريفنوع EGLNativeFileDescriptorKHR (EGLAPIENTRYP PFNEGLGETSTREAMFILEDESCRIPTORKHRPROC) (EGLDisplay dpy, EGLStreamKHR وهڪرو);
تعريفنوع EGLStreamKHR (EGLAPIENTRYP PFNEGLCREATESTREAMFROMFILEDESCRIPTORKHRPROC) (EGLDisplay dpy, EGLNativeFileDescriptorKHR file_descriptor);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLNativeFileDescriptorKHR EGLAPIENTRY egl_Get_وهڪرو_File_Descriptor_KHR (EGLDisplay dpy, EGLStreamKHR وهڪرو);
EGLAPI EGLStreamKHR EGLAPIENTRY egl_Create_وهڪرو_From_File_Descriptor_KHR (EGLDisplay dpy, EGLNativeFileDescriptorKHR file_descriptor);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_KHR_stream */
#جيڪڏهن_پورو /* EGL_KHR_stream_cross_process_fd */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_وهڪرو_fifo
#وصف_ڪريو EGL_KHR_وهڪرو_fifo 1
#جيڪڏهن_وصف_ٿيل EGL_KHR_وهڪرو
#وصف_ڪريو EGL_وهڪرو_FIFO_ڊيگهائي_KHR        0x31FC
#وصف_ڪريو EGL_وهڪرو_وقت_NOW_KHR           0x31FD
#وصف_ڪريو EGL_وهڪرو_وقت_استعمال_ڪندڙ_KHR      0x31FE
#وصف_ڪريو EGL_وهڪرو_وقت_پيداوار_ڪندڙ_KHR      0x31FF
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMTIMEKHRPROC) (EGLDisplay dpy, EGLStreamKHR وهڪرو, EGLenum attribute, EGLTimeKHR *قدر);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_وهڪرو_وقت_KHR (EGLDisplay dpy, EGLStreamKHR وهڪرو, EGLenum attribute, EGLTimeKHR *قدر);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_KHR_stream */
#جيڪڏهن_پورو /* EGL_KHR_stream_fifo */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_وهڪرو_پيداوار_ڪندڙ_aldatalocator
#وصف_ڪريو EGL_KHR_وهڪرو_پيداوار_ڪندڙ_aldatalocator 1
#جيڪڏهن_وصف_ٿيل EGL_KHR_وهڪرو
#جيڪڏهن_پورو /* EGL_KHR_stream */
#جيڪڏهن_پورو /* EGL_KHR_stream_producer_aldatalocator */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_وهڪرو_پيداوار_ڪندڙ_eglsurface
#وصف_ڪريو EGL_KHR_وهڪرو_پيداوار_ڪندڙ_eglsurface 1
#جيڪڏهن_وصف_ٿيل EGL_KHR_وهڪرو
#وصف_ڪريو EGL_وهڪرو_ٻٽو_انگ_KHR                0x0800
تعريفنوع EGLSurface (EGLAPIENTRYP PFNEGLCREATESTREAMPRODUCERSURFACEKHRPROC) (EGLDisplay dpy, EGLConfig config, EGLStreamKHR وهڪرو, ثابت EGLint *attrib_list);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSurface EGLAPIENTRY egl_Create_وهڪرو_پيداوار_ڪندڙ_Surface_KHR (EGLDisplay dpy, EGLConfig config, EGLStreamKHR وهڪرو, ثابت EGLint *attrib_list);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_KHR_stream */
#جيڪڏهن_پورو /* EGL_KHR_stream_producer_eglsurface */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_surfaceless_context
#وصف_ڪريو EGL_KHR_surfaceless_context 1
#جيڪڏهن_پورو /* EGL_KHR_surfaceless_context */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_مٽا_سٽا_buffers_with_damage
#وصف_ڪريو EGL_KHR_مٽا_سٽا_buffers_with_damage 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSWITHDAMAGEKHRPROC) (EGLDisplay dpy, EGLSurface surface, ثابت EGLint *rects, EGLint n_rects);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_مٽا_سٽا_Buffers_With_Damage_KHR (EGLDisplay dpy, EGLSurface surface, ثابت EGLint *rects, EGLint n_rects);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_KHR_swap_buffers_with_damage */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_vg_والد_image
#وصف_ڪريو EGL_KHR_vg_والد_image 1
#وصف_ڪريو EGL_VG_والد_IMAGE_KHR           0x30BA
#جيڪڏهن_پورو /* EGL_KHR_vg_parent_image */

#جيڪڏهن_وصف_نه_ٿيل EGL_KHR_wait_sync
#وصف_ڪريو EGL_KHR_wait_sync 1
تعريفنوع EGLint (EGLAPIENTRYP PFNEGLWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLint EGLAPIENTRY eglWaitSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_KHR_wait_sync */

#جيڪڏهن_وصف_نه_ٿيل EGL_ANDROID_GLES_layers
#وصف_ڪريو EGL_ANDROID_GLES_layers 1
#جيڪڏهن_پورو /* EGL_ANDROID_GLES_layers */

#جيڪڏهن_وصف_نه_ٿيل EGL_ANDROID_blob_cache
#وصف_ڪريو EGL_ANDROID_blob_cache 1
تعريفنوع khronos_ssize_t EGLsizeiANDROID;
تعريفنوع فراغ (*EGLSetBlobFuncANDROID) (ثابت فراغ *ڪنجي, EGLsizeiANDROID ڪنجي_سائيز_2, ثابت فراغ *قدر, EGLsizeiANDROID قدر_سائيز_2);
تعريفنوع EGLsizeiANDROID (*EGLGetBlobFuncANDROID) (ثابت فراغ *ڪنجي, EGLsizeiANDROID ڪنجي_سائيز_2, فراغ *قدر, EGLsizeiANDROID قدر_سائيز_2);
تعريفنوع فراغ (EGLAPIENTRYP PFNEGLSETBLOBCACHEFUNCSANDROIDPROC) (EGLDisplay dpy, EGLSetBlobFuncANDROID سيٽ, EGLGetBlobFuncANDROID get);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI فراغ EGLAPIENTRY egl_سيٽ_Blob_Cache_Funcs_ANDROID (EGLDisplay dpy, EGLSetBlobFuncANDROID سيٽ, EGLGetBlobFuncANDROID get);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_ANDROID_blob_cache */

#جيڪڏهن_وصف_نه_ٿيل EGL_ANDROID_create_native_client_بفر
#وصف_ڪريو EGL_ANDROID_create_native_client_بفر 1
#وصف_ڪريو EGL_NATIVE_بفر_USAGE_ANDROID   0x3143
#وصف_ڪريو EGL_NATIVE_بفر_USAGE_PROTECTED_ٻٽو_انگ_ANDROID 0x00000001
#وصف_ڪريو EGL_NATIVE_بفر_USAGE_RENDERBUFFER_ٻٽو_انگ_ANDROID 0x00000002
#وصف_ڪريو EGL_NATIVE_بفر_USAGE_TEXTURE_ٻٽو_انگ_ANDROID 0x00000004
تعريفنوع EGLClient_بفر (EGLAPIENTRYP PFNEGLCREATENATIVECLIENTBUFFERANDROIDPROC) (ثابت EGLint *attrib_list);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLClient_بفر EGLAPIENTRY egl_Create_Native_Client_بفر_ANDROID (ثابت EGLint *attrib_list);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_ANDROID_create_native_client_buffer */

#جيڪڏهن_وصف_نه_ٿيل EGL_ANDROID_framebuffer_هدف
#وصف_ڪريو EGL_ANDROID_framebuffer_هدف 1
#وصف_ڪريو EGL_FRAMEBUFFER_هدف_ANDROID    0x3147
#جيڪڏهن_پورو /* EGL_ANDROID_framebuffer_target */

#جيڪڏهن_وصف_نه_ٿيل EGL_ANDROID_front_بفر_auto_refresh
#وصف_ڪريو EGL_ANDROID_front_بفر_auto_refresh 1
#وصف_ڪريو EGL_FRONT_بفر_AUTO_REFRESH_ANDROID 0x314C
#جيڪڏهن_پورو /* EGL_ANDROID_front_buffer_auto_refresh */

#جيڪڏهن_وصف_نه_ٿيل EGL_ANDROID_get_چوکٺو_timestamps
#وصف_ڪريو EGL_ANDROID_get_چوکٺو_timestamps 1
تعريفنوع khronos_stime_nanoseconds_t EGLnsecsANDROID;
#وصف_ڪريو EGL_TIMESTAMP_PENDING_ANDROID     EGL_CAST(EGLnsecsANDROID,-2)
#وصف_ڪريو EGL_TIMESTAMP_INVALID_ANDROID     EGL_CAST(EGLnsecsANDROID,-1)
#وصف_ڪريو EGL_TIMESTAMPS_ANDROID            0x3430
#وصف_ڪريو EGL_مرکب_DEADLINE_ANDROID    0x3431
#وصف_ڪريو EGL_مرکب_INTERVAL_ANDROID    0x3432
#وصف_ڪريو EGL_مرکب_منزل_PRESENT_LATENCY_ANDROID 0x3433
#وصف_ڪريو EGL_REQUESTED_PRESENT_وقت_ANDROID 0x3434
#وصف_ڪريو EGL_RENDERING_COMPLETE_وقت_ANDROID 0x3435
#وصف_ڪريو EGL_COMPOSITION_LATCH_وقت_ANDROID 0x3436
#وصف_ڪريو EGL_پهريون_COMPOSITION_شروعات_وقت_ANDROID 0x3437
#وصف_ڪريو EGL_آخري_COMPOSITION_شروعات_وقت_ANDROID 0x3438
#وصف_ڪريو EGL_پهريون_COMPOSITION_GPU_ختم_وقت_ANDROID 0x3439
#وصف_ڪريو EGL_DISPLAY_PRESENT_وقت_ANDROID  0x343A
#وصف_ڪريو EGL_قطار_مان_ڪڍو_READY_وقت_ANDROID    0x343B
#وصف_ڪريو EGL_READS_پورو_وقت_ANDROID       0x343C
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETCOMPOSITORTIMINGSUPPORTEDANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLint name);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETCOMPOSITORTIMINGANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLint انگ_Timestamps,  ثابت EGLint *نالا, EGLnsecsANDROID *قدرون);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETNEXTFRAMEIDANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR *چوکٺو_Id);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETFRAMETIMESTAMPSUPPORTEDANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLint timestamp);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETFRAMETIMESTAMPSANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR چوکٺو_Id, EGLint انگ_Timestamps,  ثابت EGLint *timestamps, EGLnsecsANDROID *قدرون);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglGetCompositorTimingSupportedANDROID (EGLDisplay dpy, EGLSurface surface, EGLint name);
EGLAPI EGLBoolean EGLAPIENTRY eglGetCompositorTimingANDROID (EGLDisplay dpy, EGLSurface surface, EGLint انگ_Timestamps,  ثابت EGLint *نالا, EGLnsecsANDROID *قدرون);
EGLAPI EGLBoolean EGLAPIENTRY egl_Get_ايندڙ_چوکٺو_Id_ANDROID (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR *چوکٺو_Id);
EGLAPI EGLBoolean EGLAPIENTRY egl_Get_چوکٺو_Timestamp_Supported_ANDROID (EGLDisplay dpy, EGLSurface surface, EGLint timestamp);
EGLAPI EGLBoolean EGLAPIENTRY egl_Get_چوکٺو_Timestamps_ANDROID (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR چوکٺو_Id, EGLint انگ_Timestamps,  ثابت EGLint *timestamps, EGLnsecsANDROID *قدرون);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_ANDROID_get_frame_timestamps */

#جيڪڏهن_وصف_نه_ٿيل EGL_ANDROID_get_native_client_بفر
#وصف_ڪريو EGL_ANDROID_get_native_client_بفر 1
بنية AHardware_بفر;
تعريفنوع EGLClient_بفر (EGLAPIENTRYP PFNEGLGETNATIVECLIENTBUFFERANDROIDPROC) (ثابت بنية AHardware_بفر *بفر_2);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLClient_بفر EGLAPIENTRY egl_Get_Native_Client_بفر_ANDROID (ثابت بنية AHardware_بفر *بفر_2);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_ANDROID_get_native_client_buffer */

#جيڪڏهن_وصف_نه_ٿيل EGL_ANDROID_image_native_بفر
#وصف_ڪريو EGL_ANDROID_image_native_بفر 1
#وصف_ڪريو EGL_NATIVE_بفر_ANDROID         0x3140
#جيڪڏهن_پورو /* EGL_ANDROID_image_native_buffer */

#جيڪڏهن_وصف_نه_ٿيل EGL_ANDROID_native_fence_sync
#وصف_ڪريو EGL_ANDROID_native_fence_sync 1
#وصف_ڪريو EGL_SYNC_NATIVE_FENCE_ANDROID     0x3144
#وصف_ڪريو EGL_SYNC_NATIVE_FENCE_FD_ANDROID  0x3145
#وصف_ڪريو EGL_SYNC_NATIVE_FENCE_SIGNALED_ANDROID 0x3146
#وصف_ڪريو EGL_NO_NATIVE_FENCE_FD_ANDROID    -1
تعريفنوع EGLint (EGLAPIENTRYP PFNEGLDUPNATIVEFENCEFDANDROIDPROC) (EGLDisplay dpy, EGLSyncKHR sync);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLint EGLAPIENTRY eglDupNativeFenceFDANDROID (EGLDisplay dpy, EGLSyncKHR sync);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_ANDROID_native_fence_sync */

#جيڪڏهن_وصف_نه_ٿيل EGL_ANDROID_presentation_وقت
#وصف_ڪريو EGL_ANDROID_presentation_وقت 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLPRESENTATIONTIMEANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLnsecsANDROID وقت);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Presentation_وقت_ANDROID (EGLDisplay dpy, EGLSurface surface, EGLnsecsANDROID وقت);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_ANDROID_presentation_time */

#جيڪڏهن_وصف_نه_ٿيل EGL_ANDROID_recordable
#وصف_ڪريو EGL_ANDROID_recordable 1
#وصف_ڪريو EGL_RECORDABLE_ANDROID            0x3142
#جيڪڏهن_پورو /* EGL_ANDROID_recordable */

#جيڪڏهن_وصف_نه_ٿيل EGL_ANDROID_telemetry_hint
#وصف_ڪريو EGL_ANDROID_telemetry_hint 1
#وصف_ڪريو EGL_TELEMETRY_HINT_ANDROID        0x3570
#جيڪڏهن_پورو /* EGL_ANDROID_telemetry_hint */

#جيڪڏهن_وصف_نه_ٿيل EGL_ANGLE_d3d_share_handle_client_بفر
#وصف_ڪريو EGL_ANGLE_d3d_share_handle_client_بفر 1
#وصف_ڪريو EGL_D3D_TEXTURE_2D_SHARE_HANDLE_ANGLE 0x3200
#جيڪڏهن_پورو /* EGL_ANGLE_d3d_share_handle_client_buffer */

#جيڪڏهن_وصف_نه_ٿيل EGL_ANGLE_device_d3d
#وصف_ڪريو EGL_ANGLE_device_d3d 1
#وصف_ڪريو EGL_D3D9_DEVICE_ANGLE             0x33A0
#وصف_ڪريو EGL_D3D11_DEVICE_ANGLE            0x33A1
#جيڪڏهن_پورو /* EGL_ANGLE_device_d3d */

#جيڪڏهن_وصف_نه_ٿيل EGL_ANGLE_query_surface_اشارو
#وصف_ڪريو EGL_ANGLE_query_surface_اشارو 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSURFACEPOINTERANGLEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint attribute, فراغ **قدر);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Surface_اشارو_ANGLE (EGLDisplay dpy, EGLSurface surface, EGLint attribute, فراغ **قدر);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_ANGLE_query_surface_pointer */

#جيڪڏهن_وصف_نه_ٿيل EGL_ANGLE_surface_d3d_texture_2d_share_handle
#وصف_ڪريو EGL_ANGLE_surface_d3d_texture_2d_share_handle 1
#جيڪڏهن_پورو /* EGL_ANGLE_surface_d3d_texture_2d_share_handle */

#جيڪڏهن_وصف_نه_ٿيل EGL_ANGLE_sync_control_شرح
#وصف_ڪريو EGL_ANGLE_sync_control_شرح 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETMSCRATEANGLEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint *numerator, EGLint *denominator);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Get_Msc_شرح_ANGLE (EGLDisplay dpy, EGLSurface surface, EGLint *numerator, EGLint *denominator);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_ANGLE_sync_control_rate */

#جيڪڏهن_وصف_نه_ٿيل EGL_ANGLE_دري_fixed_سائيز
#وصف_ڪريو EGL_ANGLE_دري_fixed_سائيز 1
#وصف_ڪريو EGL_FIXED_سائيز_ANGLE              0x3201
#جيڪڏهن_پورو /* EGL_ANGLE_window_fixed_size */

#جيڪڏهن_وصف_نه_ٿيل EGL_ARM_image_format
#وصف_ڪريو EGL_ARM_image_format 1
#وصف_ڪريو EGL_COLOR_COMPONENT_TYPE_UNSIGNED_INTEGER_ARM 0x3287
#وصف_ڪريو EGL_COLOR_COMPONENT_TYPE_INTEGER_ARM 0x3288
#جيڪڏهن_پورو /* EGL_ARM_image_format */

#جيڪڏهن_وصف_نه_ٿيل EGL_ARM_implicit_external_sync
#وصف_ڪريو EGL_ARM_implicit_external_sync 1
#وصف_ڪريو EGL_SYNC_اڳواٽ_COMMANDS_IMPLICIT_EXTERNAL_ARM 0x328A
#جيڪڏهن_پورو /* EGL_ARM_implicit_external_sync */

#جيڪڏهن_وصف_نه_ٿيل EGL_ARM_pixmap_multisample_discard
#وصف_ڪريو EGL_ARM_pixmap_multisample_discard 1
#وصف_ڪريو EGL_DISCARD_SAMPLES_ARM           0x3286
#جيڪڏهن_پورو /* EGL_ARM_pixmap_multisample_discard */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_bind_منزل_front
#وصف_ڪريو EGL_EXT_bind_منزل_front 1
#وصف_ڪريو EGL_FRONT_بفر_EXT              0x3464
#جيڪڏهن_پورو /* EGL_EXT_bind_to_front */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_بفر_age
#وصف_ڪريو EGL_EXT_بفر_age 1
#وصف_ڪريو EGL_بفر_AGE_EXT                0x313D
#جيڪڏهن_پورو /* EGL_EXT_buffer_age */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_client_extensions
#وصف_ڪريو EGL_EXT_client_extensions 1
#جيڪڏهن_پورو /* EGL_EXT_client_extensions */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_client_sync
#وصف_ڪريو EGL_EXT_client_sync 1
#وصف_ڪريو EGL_SYNC_CLIENT_EXT               0x3364
#وصف_ڪريو EGL_SYNC_CLIENT_SIGNAL_EXT        0x3365
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLCLIENTSIGNALSYNCEXTPROC) (EGLDisplay dpy, EGLSync sync, ثابت EGLAttrib *attrib_list);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglClientSignalSyncEXT (EGLDisplay dpy, EGLSync sync, ثابت EGLAttrib *attrib_list);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_EXT_client_sync */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_compositor
#وصف_ڪريو EGL_EXT_compositor 1
#وصف_ڪريو EGL_PRIMARY_COMPOSITOR_CONTEXT_EXT 0x3460
#وصف_ڪريو EGL_EXTERNAL_REF_ID_EXT           0x3461
#وصف_ڪريو EGL_COMPOSITOR_DROP_NEWEST_چوکٺو_EXT 0x3462
#وصف_ڪريو EGL_COMPOSITOR_KEEP_NEWEST_چوکٺو_EXT 0x3463
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETCONTEXTLISTEXTPROC) (ثابت EGLint *external_ref_ids, EGLint انگ_entries);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETCONTEXTATTRIBUTESEXTPROC) (EGLint external_ref_id, ثابت EGLint *context_خاصيتون, EGLint انگ_entries);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETWINDOWLISTEXTPROC) (EGLint external_ref_id, ثابت EGLint *external_win_ids, EGLint انگ_entries);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETWINDOWATTRIBUTESEXTPROC) (EGLint external_win_id, ثابت EGLint *دري_خاصيتون, EGLint انگ_entries);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORBINDTEXWINDOWEXTPROC) (EGLint external_win_id);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETSIZEEXTPROC) (EGLint external_win_id, EGLint ويڪر, EGLint اوچائي);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSWAPPOLICYEXTPROC) (EGLint external_win_id, EGLint policy);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_سيٽ_Context_List_EXT (ثابت EGLint *external_ref_ids, EGLint انگ_entries);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_سيٽ_Context_خاصيتون_EXT (EGLint external_ref_id, ثابت EGLint *context_خاصيتون, EGLint انگ_entries);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_سيٽ_دري_List_EXT (EGLint external_ref_id, ثابت EGLint *external_win_ids, EGLint انگ_entries);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_سيٽ_دري_خاصيتون_EXT (EGLint external_win_id, ثابت EGLint *دري_خاصيتون, EGLint انگ_entries);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_Bind_Tex_دري_EXT (EGLint external_win_id);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_سيٽ_سائيز_EXT (EGLint external_win_id, EGLint ويڪر, EGLint اوچائي);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_مٽا_سٽا_Policy_EXT (EGLint external_win_id, EGLint policy);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_EXT_compositor */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_config_select_گروهه
#وصف_ڪريو EGL_EXT_config_select_گروهه 1
#وصف_ڪريو EGL_CONFIG_SELECT_گروهه_EXT       0x34C0
#جيڪڏهن_پورو /* EGL_EXT_config_select_group */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_create_context_robustness
#وصف_ڪريو EGL_EXT_create_context_robustness 1
#وصف_ڪريو EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT 0x30BF
#وصف_ڪريو EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_EXT 0x3138
#وصف_ڪريو EGL_NO_RESET_NOTIFICATION_EXT     0x31BE
#وصف_ڪريو EGL_LOSE_CONTEXT_ON_RESET_EXT     0x31BF
#جيڪڏهن_پورو /* EGL_EXT_create_context_robustness */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_device_بنياد
#وصف_ڪريو EGL_EXT_device_بنياد 1
تعريفنوع فراغ *EGLDeviceEXT;
#وصف_ڪريو EGL_NO_DEVICE_EXT                 EGL_CAST(EGLDeviceEXT,0)
#وصف_ڪريو EGL_BAD_DEVICE_EXT                0x322B
#وصف_ڪريو EGL_DEVICE_EXT                    0x322C
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICEATTRIBEXTPROC) (EGLDeviceEXT device, EGLint attribute, EGLAttrib *قدر);
تعريفنوع ثابت حرف *(EGLAPIENTRYP PFNEGLQUERYDEVICESTRINGEXTPROC) (EGLDeviceEXT device, EGLint name);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICESEXTPROC) (EGLint max_devices, EGLDeviceEXT *devices, EGLint *انگ_devices);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDISPLAYATTRIBEXTPROC) (EGLDisplay dpy, EGLint attribute, EGLAttrib *قدر);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDeviceAttribEXT (EGLDeviceEXT device, EGLint attribute, EGLAttrib *قدر);
EGLAPI ثابت حرف *EGLAPIENTRY eglQueryDeviceStringEXT (EGLDeviceEXT device, EGLint name);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDevicesEXT (EGLint max_devices, EGLDeviceEXT *devices, EGLint *انگ_devices);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDisplayAttribEXT (EGLDisplay dpy, EGLint attribute, EGLAttrib *قدر);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_EXT_device_base */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_device_drm
#وصف_ڪريو EGL_EXT_device_drm 1
#وصف_ڪريو EGL_DRM_DEVICE_FILE_EXT           0x3233
#وصف_ڪريو EGL_DRM_MASTER_FD_EXT             0x333C
#جيڪڏهن_پورو /* EGL_EXT_device_drm */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_device_drm_render_ڳنڍ
#وصف_ڪريو EGL_EXT_device_drm_render_ڳنڍ 1
#وصف_ڪريو EGL_DRM_RENDER_ڳنڍ_FILE_EXT      0x3377
#جيڪڏهن_پورو /* EGL_EXT_device_drm_render_node */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_device_enumeration
#وصف_ڪريو EGL_EXT_device_enumeration 1
#جيڪڏهن_پورو /* EGL_EXT_device_enumeration */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_device_openwf
#وصف_ڪريو EGL_EXT_device_openwf 1
#وصف_ڪريو EGL_OPENWF_DEVICE_ID_EXT          0x3237
#وصف_ڪريو EGL_OPENWF_DEVICE_EXT             0x333D
#جيڪڏهن_پورو /* EGL_EXT_device_openwf */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_device_persistent_id
#وصف_ڪريو EGL_EXT_device_persistent_id 1
#وصف_ڪريو EGL_DEVICE_UUID_EXT               0x335C
#وصف_ڪريو EGL_DRIVER_UUID_EXT               0x335D
#وصف_ڪريو EGL_DRIVER_NAME_EXT               0x335E
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICEBINARYEXTPROC) (EGLDeviceEXT device, EGLint name, EGLint max_سائيز, فراغ *قدر, EGLint *سائيز);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Device_ٻٽو_EXT (EGLDeviceEXT device, EGLint name, EGLint max_سائيز, فراغ *قدر, EGLint *سائيز);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_EXT_device_persistent_id */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_device_query
#وصف_ڪريو EGL_EXT_device_query 1
#جيڪڏهن_پورو /* EGL_EXT_device_query */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_device_query_name
#وصف_ڪريو EGL_EXT_device_query_name 1
#وصف_ڪريو EGL_RENDERER_EXT                  0x335F
#جيڪڏهن_پورو /* EGL_EXT_device_query_name */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_device_type
#وصف_ڪريو EGL_EXT_device_type 1
#وصف_ڪريو EGL_DEVICE_TYPE_EXT               0x3590
#وصف_ڪريو EGL_DEVICE_TYPE_OTHER_EXT         0x3591
#وصف_ڪريو EGL_DEVICE_TYPE_INTEGRATED_GPU_EXT 0x3592
#وصف_ڪريو EGL_DEVICE_TYPE_DISCRETE_GPU_EXT  0x3593
#وصف_ڪريو EGL_DEVICE_TYPE_CPU_EXT           0x3594
#جيڪڏهن_پورو /* EGL_EXT_device_type */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_display_alloc
#وصف_ڪريو EGL_EXT_display_alloc 1
#وصف_ڪريو EGL_ALLOC_NEW_DISPLAY_EXT         0x3379
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYDISPLAYEXTPROC) (EGLDisplay dpy);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyDisplayEXT (EGLDisplay dpy);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_EXT_display_alloc */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_explicit_device
#وصف_ڪريو EGL_EXT_explicit_device 1
#جيڪڏهن_پورو /* EGL_EXT_explicit_device */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_gl_colorspace_bt2020_hlg
#وصف_ڪريو EGL_EXT_gl_colorspace_bt2020_hlg 1
#وصف_ڪريو EGL_GL_COLORSPACE_BT2020_HLG_EXT  0x3540
#جيڪڏهن_پورو /* EGL_EXT_gl_colorspace_bt2020_hlg */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_gl_colorspace_bt2020_لڪيري
#وصف_ڪريو EGL_EXT_gl_colorspace_bt2020_لڪيري 1
#وصف_ڪريو EGL_GL_COLORSPACE_BT2020_لڪيري_EXT 0x333F
#جيڪڏهن_پورو /* EGL_EXT_gl_colorspace_bt2020_linear */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_gl_colorspace_bt2020_pq
#وصف_ڪريو EGL_EXT_gl_colorspace_bt2020_pq 1
#وصف_ڪريو EGL_GL_COLORSPACE_BT2020_PQ_EXT   0x3340
#جيڪڏهن_پورو /* EGL_EXT_gl_colorspace_bt2020_pq */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_gl_colorspace_display_p3
#وصف_ڪريو EGL_EXT_gl_colorspace_display_p3 1
#وصف_ڪريو EGL_GL_COLORSPACE_DISPLAY_P3_EXT  0x3363
#جيڪڏهن_پورو /* EGL_EXT_gl_colorspace_display_p3 */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_gl_colorspace_display_p3_لڪيري
#وصف_ڪريو EGL_EXT_gl_colorspace_display_p3_لڪيري 1
#وصف_ڪريو EGL_GL_COLORSPACE_DISPLAY_P3_لڪيري_EXT 0x3362
#جيڪڏهن_پورو /* EGL_EXT_gl_colorspace_display_p3_linear */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_gl_colorspace_display_p3_passthrough
#وصف_ڪريو EGL_EXT_gl_colorspace_display_p3_passthrough 1
#وصف_ڪريو EGL_GL_COLORSPACE_DISPLAY_P3_PASSTHROUGH_EXT 0x3490
#جيڪڏهن_پورو /* EGL_EXT_gl_colorspace_display_p3_passthrough */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_gl_colorspace_scrgb
#وصف_ڪريو EGL_EXT_gl_colorspace_scrgb 1
#وصف_ڪريو EGL_GL_COLORSPACE_SCRGB_EXT       0x3351
#جيڪڏهن_پورو /* EGL_EXT_gl_colorspace_scrgb */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_gl_colorspace_scrgb_لڪيري
#وصف_ڪريو EGL_EXT_gl_colorspace_scrgb_لڪيري 1
#وصف_ڪريو EGL_GL_COLORSPACE_SCRGB_لڪيري_EXT 0x3350
#جيڪڏهن_پورو /* EGL_EXT_gl_colorspace_scrgb_linear */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_image_dma_buf_import
#وصف_ڪريو EGL_EXT_image_dma_buf_import 1
#وصف_ڪريو EGL_LINUX_DMA_BUF_EXT             0x3270
#وصف_ڪريو EGL_LINUX_DRM_FOURCC_EXT          0x3271
#وصف_ڪريو EGL_DMA_BUF_PLANE0_FD_EXT         0x3272
#وصف_ڪريو EGL_DMA_BUF_PLANE0_وٿي_EXT     0x3273
#وصف_ڪريو EGL_DMA_BUF_PLANE0_PITCH_EXT      0x3274
#وصف_ڪريو EGL_DMA_BUF_PLANE1_FD_EXT         0x3275
#وصف_ڪريو EGL_DMA_BUF_PLANE1_وٿي_EXT     0x3276
#وصف_ڪريو EGL_DMA_BUF_PLANE1_PITCH_EXT      0x3277
#وصف_ڪريو EGL_DMA_BUF_PLANE2_FD_EXT         0x3278
#وصف_ڪريو EGL_DMA_BUF_PLANE2_وٿي_EXT     0x3279
#وصف_ڪريو EGL_DMA_BUF_PLANE2_PITCH_EXT      0x327A
#وصف_ڪريو EGL_YUV_COLOR_SPACE_HINT_EXT      0x327B
#وصف_ڪريو EGL_SAMPLE_RANGE_HINT_EXT         0x327C
#وصف_ڪريو EGL_YUV_CHROMA_HORIZONTAL_SITING_HINT_EXT 0x327D
#وصف_ڪريو EGL_YUV_CHROMA_VERTICAL_SITING_HINT_EXT 0x327E
#وصف_ڪريو EGL_ITU_REC601_EXT                0x327F
#وصف_ڪريو EGL_ITU_REC709_EXT                0x3280
#وصف_ڪريو EGL_ITU_REC2020_EXT               0x3281
#وصف_ڪريو EGL_YUV_ڀريل_RANGE_EXT            0x3282
#وصف_ڪريو EGL_YUV_NARROW_RANGE_EXT          0x3283
#وصف_ڪريو EGL_YUV_CHROMA_SITING_0_EXT       0x3284
#وصف_ڪريو EGL_YUV_CHROMA_SITING_0_5_EXT     0x3285
#جيڪڏهن_پورو /* EGL_EXT_image_dma_buf_import */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_image_dma_buf_import_modifiers
#وصف_ڪريو EGL_EXT_image_dma_buf_import_modifiers 1
#وصف_ڪريو EGL_DMA_BUF_PLANE3_FD_EXT         0x3440
#وصف_ڪريو EGL_DMA_BUF_PLANE3_وٿي_EXT     0x3441
#وصف_ڪريو EGL_DMA_BUF_PLANE3_PITCH_EXT      0x3442
#وصف_ڪريو EGL_DMA_BUF_PLANE0_MODIFIER_LO_EXT 0x3443
#وصف_ڪريو EGL_DMA_BUF_PLANE0_MODIFIER_HI_EXT 0x3444
#وصف_ڪريو EGL_DMA_BUF_PLANE1_MODIFIER_LO_EXT 0x3445
#وصف_ڪريو EGL_DMA_BUF_PLANE1_MODIFIER_HI_EXT 0x3446
#وصف_ڪريو EGL_DMA_BUF_PLANE2_MODIFIER_LO_EXT 0x3447
#وصف_ڪريو EGL_DMA_BUF_PLANE2_MODIFIER_HI_EXT 0x3448
#وصف_ڪريو EGL_DMA_BUF_PLANE3_MODIFIER_LO_EXT 0x3449
#وصف_ڪريو EGL_DMA_BUF_PLANE3_MODIFIER_HI_EXT 0x344A
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDMABUFFORMATSEXTPROC) (EGLDisplay dpy, EGLint max_formats, EGLint *formats, EGLint *انگ_formats);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDMABUFMODIFIERSEXTPROC) (EGLDisplay dpy, EGLint format, EGLint max_modifiers, EGLuint64KHR *modifiers, EGLBoolean *external_only, EGLint *انگ_modifiers);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDmaBufFormatsEXT (EGLDisplay dpy, EGLint max_formats, EGLint *formats, EGLint *انگ_formats);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDmaBufModifiersEXT (EGLDisplay dpy, EGLint format, EGLint max_modifiers, EGLuint64KHR *modifiers, EGLBoolean *external_only, EGLint *انگ_modifiers);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_EXT_image_dma_buf_import_modifiers */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_image_gl_colorspace
#وصف_ڪريو EGL_EXT_image_gl_colorspace 1
#وصف_ڪريو EGL_GL_COLORSPACE_DEFAULT_EXT     0x314D
#جيڪڏهن_پورو /* EGL_EXT_image_gl_colorspace */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_image_implicit_sync_control
#وصف_ڪريو EGL_EXT_image_implicit_sync_control 1
#وصف_ڪريو EGL_IMPORT_SYNC_TYPE_EXT          0x3470
#وصف_ڪريو EGL_IMPORT_IMPLICIT_SYNC_EXT      0x3471
#وصف_ڪريو EGL_IMPORT_EXPLICIT_SYNC_EXT      0x3472
#جيڪڏهن_پورو /* EGL_EXT_image_implicit_sync_control */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_multiview_دري
#وصف_ڪريو EGL_EXT_multiview_دري 1
#وصف_ڪريو EGL_MULTIVIEW_VIEW_ڳڻپ_EXT      0x3134
#جيڪڏهن_پورو /* EGL_EXT_multiview_window */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_output_بنياد
#وصف_ڪريو EGL_EXT_output_بنياد 1
تعريفنوع فراغ *EGLOutputLayerEXT;
تعريفنوع فراغ *EGLOutput_پورٽ_EXT;
#وصف_ڪريو EGL_NO_OUTPUT_LAYER_EXT           EGL_CAST(EGLOutputLayerEXT,0)
#وصف_ڪريو EGL_NO_OUTPUT_پورٽ_EXT            EGL_CAST(EGLOutput_پورٽ_EXT,0)
#وصف_ڪريو EGL_BAD_OUTPUT_LAYER_EXT          0x322D
#وصف_ڪريو EGL_BAD_OUTPUT_پورٽ_EXT           0x322E
#وصف_ڪريو EGL_مٽا_سٽا_INTERVAL_EXT             0x322F
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETOUTPUTLAYERSEXTPROC) (EGLDisplay dpy, ثابت EGLAttrib *attrib_list, EGLOutputLayerEXT *layers, EGLint max_layers, EGLint *انگ_layers);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETOUTPUTPORTSEXTPROC) (EGLDisplay dpy, ثابت EGLAttrib *attrib_list, EGLOutput_پورٽ_EXT *ports, EGLint max_ports, EGLint *انگ_ports);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLOUTPUTLAYERATTRIBEXTPROC) (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib قدر);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYOUTPUTLAYERATTRIBEXTPROC) (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib *قدر);
تعريفنوع ثابت حرف *(EGLAPIENTRYP PFNEGLQUERYOUTPUTLAYERSTRINGEXTPROC) (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint name);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLOUTPUTPORTATTRIBEXTPROC) (EGLDisplay dpy, EGLOutput_پورٽ_EXT پورٽ, EGLint attribute, EGLAttrib قدر);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYOUTPUTPORTATTRIBEXTPROC) (EGLDisplay dpy, EGLOutput_پورٽ_EXT پورٽ, EGLint attribute, EGLAttrib *قدر);
تعريفنوع ثابت حرف *(EGLAPIENTRYP PFNEGLQUERYOUTPUTPORTSTRINGEXTPROC) (EGLDisplay dpy, EGLOutput_پورٽ_EXT پورٽ, EGLint name);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglGetOutputLayersEXT (EGLDisplay dpy, ثابت EGLAttrib *attrib_list, EGLOutputLayerEXT *layers, EGLint max_layers, EGLint *انگ_layers);
EGLAPI EGLBoolean EGLAPIENTRY eglGetOutputPortsEXT (EGLDisplay dpy, ثابت EGLAttrib *attrib_list, EGLOutput_پورٽ_EXT *ports, EGLint max_ports, EGLint *انگ_ports);
EGLAPI EGLBoolean EGLAPIENTRY eglOutputLayerAttribEXT (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib قدر);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryOutputLayerAttribEXT (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib *قدر);
EGLAPI ثابت حرف *EGLAPIENTRY eglQueryOutputLayerStringEXT (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint name);
EGLAPI EGLBoolean EGLAPIENTRY egl_Output_پورٽ_Attrib_EXT (EGLDisplay dpy, EGLOutput_پورٽ_EXT پورٽ, EGLint attribute, EGLAttrib قدر);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Output_پورٽ_Attrib_EXT (EGLDisplay dpy, EGLOutput_پورٽ_EXT پورٽ, EGLint attribute, EGLAttrib *قدر);
EGLAPI ثابت حرف *EGLAPIENTRY egl_Query_Output_پورٽ_String_EXT (EGLDisplay dpy, EGLOutput_پورٽ_EXT پورٽ, EGLint name);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_EXT_output_base */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_output_drm
#وصف_ڪريو EGL_EXT_output_drm 1
#وصف_ڪريو EGL_DRM_CRTC_EXT                  0x3234
#وصف_ڪريو EGL_DRM_PLANE_EXT                 0x3235
#وصف_ڪريو EGL_DRM_CONNECTOR_EXT             0x3236
#جيڪڏهن_پورو /* EGL_EXT_output_drm */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_output_openwf
#وصف_ڪريو EGL_EXT_output_openwf 1
#وصف_ڪريو EGL_OPENWF_PIPELINE_ID_EXT        0x3238
#وصف_ڪريو EGL_OPENWF_پورٽ_ID_EXT            0x3239
#جيڪڏهن_پورو /* EGL_EXT_output_openwf */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_pixel_format_float
#وصف_ڪريو EGL_EXT_pixel_format_float 1
#وصف_ڪريو EGL_COLOR_COMPONENT_TYPE_EXT      0x3339
#وصف_ڪريو EGL_COLOR_COMPONENT_TYPE_FIXED_EXT 0x333A
#وصف_ڪريو EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT 0x333B
#جيڪڏهن_پورو /* EGL_EXT_pixel_format_float */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_platform_بنياد
#وصف_ڪريو EGL_EXT_platform_بنياد 1
تعريفنوع EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYEXTPROC) (EGLenum platform, فراغ *native_display, ثابت EGLint *attrib_list);
تعريفنوع EGLSurface (EGLAPIENTRYP PFNEGLCREATEPLATFORMWINDOWSURFACEEXTPROC) (EGLDisplay dpy, EGLConfig config, فراغ *native_دري, ثابت EGLint *attrib_list);
تعريفنوع EGLSurface (EGLAPIENTRYP PFNEGLCREATEPLATFORMPIXMAPSURFACEEXTPROC) (EGLDisplay dpy, EGLConfig config, فراغ *native_pixmap, ثابت EGLint *attrib_list);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLDisplay EGLAPIENTRY eglGetPlatformDisplayEXT (EGLenum platform, فراغ *native_display, ثابت EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY egl_Create_Platform_دري_Surface_EXT (EGLDisplay dpy, EGLConfig config, فراغ *native_دري, ثابت EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePlatformPixmapSurfaceEXT (EGLDisplay dpy, EGLConfig config, فراغ *native_pixmap, ثابت EGLint *attrib_list);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_EXT_platform_base */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_platform_device
#وصف_ڪريو EGL_EXT_platform_device 1
#وصف_ڪريو EGL_PLATFORM_DEVICE_EXT           0x313F
#جيڪڏهن_پورو /* EGL_EXT_platform_device */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_platform_wayland
#وصف_ڪريو EGL_EXT_platform_wayland 1
#وصف_ڪريو EGL_PLATFORM_WAYLAND_EXT          0x31D8
#جيڪڏهن_پورو /* EGL_EXT_platform_wayland */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_platform_x11
#وصف_ڪريو EGL_EXT_platform_x11 1
#وصف_ڪريو EGL_PLATFORM_X11_EXT              0x31D5
#وصف_ڪريو EGL_PLATFORM_X11_SCREEN_EXT       0x31D6
#جيڪڏهن_پورو /* EGL_EXT_platform_x11 */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_platform_xcb
#وصف_ڪريو EGL_EXT_platform_xcb 1
#وصف_ڪريو EGL_PLATFORM_XCB_EXT              0x31DC
#وصف_ڪريو EGL_PLATFORM_XCB_SCREEN_EXT       0x31DE
#جيڪڏهن_پورو /* EGL_EXT_platform_xcb */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_present_opaque
#وصف_ڪريو EGL_EXT_present_opaque 1
#وصف_ڪريو EGL_PRESENT_OPAQUE_EXT            0x31DF
#جيڪڏهن_پورو /* EGL_EXT_present_opaque */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_protected_content
#وصف_ڪريو EGL_EXT_protected_content 1
#وصف_ڪريو EGL_PROTECTED_CONTENT_EXT         0x32C0
#جيڪڏهن_پورو /* EGL_EXT_protected_content */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_protected_surface
#وصف_ڪريو EGL_EXT_protected_surface 1
#جيڪڏهن_پورو /* EGL_EXT_protected_surface */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_query_reset_notification_strategy
#وصف_ڪريو EGL_EXT_query_reset_notification_strategy 1
#جيڪڏهن_پورو /* EGL_EXT_query_reset_notification_strategy */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_وهڪرو_استعمال_ڪندڙ_egloutput
#وصف_ڪريو EGL_EXT_وهڪرو_استعمال_ڪندڙ_egloutput 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMEROUTPUTEXTPROC) (EGLDisplay dpy, EGLStreamKHR وهڪرو, EGLOutputLayerEXT layer);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_وهڪرو_استعمال_ڪندڙ_Output_EXT (EGLDisplay dpy, EGLStreamKHR وهڪرو, EGLOutputLayerEXT layer);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_EXT_stream_consumer_egloutput */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_surface_CTA861_3_metadata
#وصف_ڪريو EGL_EXT_surface_CTA861_3_metadata 1
#وصف_ڪريو EGL_CTA861_3_MAX_CONTENT_LIGHT_LEVEL_EXT 0x3360
#وصف_ڪريو EGL_CTA861_3_MAX_چوکٺو_اوسط_LEVEL_EXT 0x3361
#جيڪڏهن_پورو /* EGL_EXT_surface_CTA861_3_metadata */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_surface_SMPTE2086_metadata
#وصف_ڪريو EGL_EXT_surface_SMPTE2086_metadata 1
#وصف_ڪريو EGL_SMPTE2086_DISPLAY_PRIMARY_RX_EXT 0x3341
#وصف_ڪريو EGL_SMPTE2086_DISPLAY_PRIMARY_RY_EXT 0x3342
#وصف_ڪريو EGL_SMPTE2086_DISPLAY_PRIMARY_GX_EXT 0x3343
#وصف_ڪريو EGL_SMPTE2086_DISPLAY_PRIMARY_GY_EXT 0x3344
#وصف_ڪريو EGL_SMPTE2086_DISPLAY_PRIMARY_BX_EXT 0x3345
#وصف_ڪريو EGL_SMPTE2086_DISPLAY_PRIMARY_BY_EXT 0x3346
#وصف_ڪريو EGL_SMPTE2086_WHITE_نقطو_X_EXT   0x3347
#وصف_ڪريو EGL_SMPTE2086_WHITE_نقطو_Y_EXT   0x3348
#وصف_ڪريو EGL_SMPTE2086_MAX_LUMINANCE_EXT   0x3349
#وصف_ڪريو EGL_SMPTE2086_MIN_LUMINANCE_EXT   0x334A
#وصف_ڪريو EGL_METADATA_SCALING_EXT          50000
#جيڪڏهن_پورو /* EGL_EXT_surface_SMPTE2086_metadata */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_surface_compression
#وصف_ڪريو EGL_EXT_surface_compression 1
#وصف_ڪريو EGL_SURFACE_COMPRESSION_EXT       0x34B0
#وصف_ڪريو EGL_SURFACE_COMPRESSION_PLANE1_EXT 0x328E
#وصف_ڪريو EGL_SURFACE_COMPRESSION_PLANE2_EXT 0x328F
#وصف_ڪريو EGL_SURFACE_COMPRESSION_FIXED_شرح_NONE_EXT 0x34B1
#وصف_ڪريو EGL_SURFACE_COMPRESSION_FIXED_شرح_DEFAULT_EXT 0x34B2
#وصف_ڪريو EGL_SURFACE_COMPRESSION_FIXED_شرح_1_BPC_EXT 0x34B4
#وصف_ڪريو EGL_SURFACE_COMPRESSION_FIXED_شرح_2_BPC_EXT 0x34B5
#وصف_ڪريو EGL_SURFACE_COMPRESSION_FIXED_شرح_3_BPC_EXT 0x34B6
#وصف_ڪريو EGL_SURFACE_COMPRESSION_FIXED_شرح_4_BPC_EXT 0x34B7
#وصف_ڪريو EGL_SURFACE_COMPRESSION_FIXED_شرح_5_BPC_EXT 0x34B8
#وصف_ڪريو EGL_SURFACE_COMPRESSION_FIXED_شرح_6_BPC_EXT 0x34B9
#وصف_ڪريو EGL_SURFACE_COMPRESSION_FIXED_شرح_7_BPC_EXT 0x34BA
#وصف_ڪريو EGL_SURFACE_COMPRESSION_FIXED_شرح_8_BPC_EXT 0x34BB
#وصف_ڪريو EGL_SURFACE_COMPRESSION_FIXED_شرح_9_BPC_EXT 0x34BC
#وصف_ڪريو EGL_SURFACE_COMPRESSION_FIXED_شرح_10_BPC_EXT 0x34BD
#وصف_ڪريو EGL_SURFACE_COMPRESSION_FIXED_شرح_11_BPC_EXT 0x34BE
#وصف_ڪريو EGL_SURFACE_COMPRESSION_FIXED_شرح_12_BPC_EXT 0x34BF
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSUPPORTEDCOMPRESSIONRATESEXTPROC) (EGLDisplay dpy, EGLConfig config, ثابت EGLAttrib *attrib_list, EGLint *rates, EGLint شرح_سائيز, EGLint *انگ_rates);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQuerySupportedCompressionRatesEXT (EGLDisplay dpy, EGLConfig config, ثابت EGLAttrib *attrib_list, EGLint *rates, EGLint شرح_سائيز, EGLint *انگ_rates);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_EXT_surface_compression */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_مٽا_سٽا_buffers_with_damage
#وصف_ڪريو EGL_EXT_مٽا_سٽا_buffers_with_damage 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC) (EGLDisplay dpy, EGLSurface surface, ثابت EGLint *rects, EGLint n_rects);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_مٽا_سٽا_Buffers_With_Damage_EXT (EGLDisplay dpy, EGLSurface surface, ثابت EGLint *rects, EGLint n_rects);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_EXT_swap_buffers_with_damage */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_sync_reuse
#وصف_ڪريو EGL_EXT_sync_reuse 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLUNSIGNALSYNCEXTPROC) (EGLDisplay dpy, EGLSync sync, ثابت EGLAttrib *attrib_list);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglUnsignalSyncEXT (EGLDisplay dpy, EGLSync sync, ثابت EGLAttrib *attrib_list);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_EXT_sync_reuse */

#جيڪڏهن_وصف_نه_ٿيل EGL_EXT_yuv_surface
#وصف_ڪريو EGL_EXT_yuv_surface 1
#وصف_ڪريو EGL_YUV_ترتيب_EXT                 0x3301
#وصف_ڪريو EGL_YUV_عدد_جو_PLANES_EXT      0x3311
#وصف_ڪريو EGL_YUV_SUBSAMPLE_EXT             0x3312
#وصف_ڪريو EGL_YUV_اونهائي_RANGE_EXT           0x3317
#وصف_ڪريو EGL_YUV_CSC_STANDARD_EXT          0x330A
#وصف_ڪريو EGL_YUV_PLANE_BPP_EXT             0x331A
#وصف_ڪريو EGL_YUV_بفر_EXT                0x3300
#وصف_ڪريو EGL_YUV_ترتيب_YUV_EXT             0x3302
#وصف_ڪريو EGL_YUV_ترتيب_YVU_EXT             0x3303
#وصف_ڪريو EGL_YUV_ترتيب_YUYV_EXT            0x3304
#وصف_ڪريو EGL_YUV_ترتيب_UYVY_EXT            0x3305
#وصف_ڪريو EGL_YUV_ترتيب_YVYU_EXT            0x3306
#وصف_ڪريو EGL_YUV_ترتيب_VYUY_EXT            0x3307
#وصف_ڪريو EGL_YUV_ترتيب_AYUV_EXT            0x3308
#وصف_ڪريو EGL_YUV_SUBSAMPLE_4_2_0_EXT       0x3313
#وصف_ڪريو EGL_YUV_SUBSAMPLE_4_2_2_EXT       0x3314
#وصف_ڪريو EGL_YUV_SUBSAMPLE_4_4_4_EXT       0x3315
#وصف_ڪريو EGL_YUV_اونهائي_RANGE_LIMITED_EXT   0x3318
#وصف_ڪريو EGL_YUV_اونهائي_RANGE_ڀريل_EXT      0x3319
#وصف_ڪريو EGL_YUV_CSC_STANDARD_601_EXT      0x330B
#وصف_ڪريو EGL_YUV_CSC_STANDARD_709_EXT      0x330C
#وصف_ڪريو EGL_YUV_CSC_STANDARD_2020_EXT     0x330D
#وصف_ڪريو EGL_YUV_PLANE_BPP_0_EXT           0x331B
#وصف_ڪريو EGL_YUV_PLANE_BPP_8_EXT           0x331C
#وصف_ڪريو EGL_YUV_PLANE_BPP_10_EXT          0x331D
#جيڪڏهن_پورو /* EGL_EXT_yuv_surface */

#جيڪڏهن_وصف_نه_ٿيل EGL_HI_clientpixmap
#وصف_ڪريو EGL_HI_clientpixmap 1
بنية EGLClientPixmapHI {
    فراغ  *p_معلومات;
    EGLint i_ويڪر;
    EGLint i_اوچائي;
    EGLint iStride;
};
#وصف_ڪريو EGL_CLIENT_PIXMAP_اشارو_HI      0x8F74
تعريفنوع EGLSurface (EGLAPIENTRYP PFNEGLCREATEPIXMAPSURFACEHIPROC) (EGLDisplay dpy, EGLConfig config, بنية EGLClientPixmapHI *pixmap);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSurface EGLAPIENTRY eglCreatePixmapSurfaceHI (EGLDisplay dpy, EGLConfig config, بنية EGLClientPixmapHI *pixmap);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_HI_clientpixmap */

#جيڪڏهن_وصف_نه_ٿيل EGL_HI_colorformats
#وصف_ڪريو EGL_HI_colorformats 1
#وصف_ڪريو EGL_COLOR_FORMAT_HI               0x8F70
#وصف_ڪريو EGL_COLOR_RGB_HI                  0x8F71
#وصف_ڪريو EGL_COLOR_RGBA_HI                 0x8F72
#وصف_ڪريو EGL_COLOR_ARGB_HI                 0x8F73
#جيڪڏهن_پورو /* EGL_HI_colorformats */

#جيڪڏهن_وصف_نه_ٿيل EGL_IMG_context_ترجيح
#وصف_ڪريو EGL_IMG_context_ترجيح 1
#وصف_ڪريو EGL_CONTEXT_ترجيح_LEVEL_IMG    0x3100
#وصف_ڪريو EGL_CONTEXT_ترجيح_مٿاهون_IMG     0x3101
#وصف_ڪريو EGL_CONTEXT_ترجيح_MEDIUM_IMG   0x3102
#وصف_ڪريو EGL_CONTEXT_ترجيح_هيٺيون_IMG      0x3103
#جيڪڏهن_پورو /* EGL_IMG_context_priority */

#جيڪڏهن_وصف_نه_ٿيل EGL_IMG_image_plane_attribs
#وصف_ڪريو EGL_IMG_image_plane_attribs 1
#وصف_ڪريو EGL_NATIVE_بفر_MULTIPLANE_SEPARATE_IMG 0x3105
#وصف_ڪريو EGL_NATIVE_بفر_PLANE_وٿي_IMG 0x3106
#جيڪڏهن_پورو /* EGL_IMG_image_plane_attribs */

#جيڪڏهن_وصف_نه_ٿيل EGL_MESA_drm_image
#وصف_ڪريو EGL_MESA_drm_image 1
#وصف_ڪريو EGL_DRM_بفر_FORMAT_MESA        0x31D0
#وصف_ڪريو EGL_DRM_بفر_USE_MESA           0x31D1
#وصف_ڪريو EGL_DRM_بفر_FORMAT_ARGB32_MESA 0x31D2
#وصف_ڪريو EGL_DRM_بفر_MESA               0x31D3
#وصف_ڪريو EGL_DRM_بفر_STRIDE_MESA        0x31D4
#وصف_ڪريو EGL_DRM_بفر_USE_SCANOUT_MESA   0x00000001
#وصف_ڪريو EGL_DRM_بفر_USE_SHARE_MESA     0x00000002
#وصف_ڪريو EGL_DRM_بفر_USE_CURSOR_MESA    0x00000004
تعريفنوع EGLImageKHR (EGLAPIENTRYP PFNEGLCREATEDRMIMAGEMESAPROC) (EGLDisplay dpy, ثابت EGLint *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLEXPORTDRMIMAGEMESAPROC) (EGLDisplay dpy, EGLImageKHR image, EGLint *name, EGLint *handle, EGLint *stride);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLImageKHR EGLAPIENTRY eglCreateDRMImageMESA (EGLDisplay dpy, ثابت EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglExportDRMImageMESA (EGLDisplay dpy, EGLImageKHR image, EGLint *name, EGLint *handle, EGLint *stride);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_MESA_drm_image */

#جيڪڏهن_وصف_نه_ٿيل EGL_MESA_image_dma_buf_export
#وصف_ڪريو EGL_MESA_image_dma_buf_export 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLEXPORTDMABUFIMAGEQUERYMESAPROC) (EGLDisplay dpy, EGLImageKHR image, صحيح *fourcc, صحيح *انگ_planes, EGLuint64KHR *modifiers);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLEXPORTDMABUFIMAGEMESAPROC) (EGLDisplay dpy, EGLImageKHR image, صحيح *fds, EGLint *strides, EGLint *offsets);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglExportDMABUFImageQueryMESA (EGLDisplay dpy, EGLImageKHR image, صحيح *fourcc, صحيح *انگ_planes, EGLuint64KHR *modifiers);
EGLAPI EGLBoolean EGLAPIENTRY eglExportDMABUFImageMESA (EGLDisplay dpy, EGLImageKHR image, صحيح *fds, EGLint *strides, EGLint *offsets);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_MESA_image_dma_buf_export */

#جيڪڏهن_وصف_نه_ٿيل EGL_MESA_platform_gbm
#وصف_ڪريو EGL_MESA_platform_gbm 1
#وصف_ڪريو EGL_PLATFORM_GBM_MESA             0x31D7
#جيڪڏهن_پورو /* EGL_MESA_platform_gbm */

#جيڪڏهن_وصف_نه_ٿيل EGL_MESA_platform_surfaceless
#وصف_ڪريو EGL_MESA_platform_surfaceless 1
#وصف_ڪريو EGL_PLATFORM_SURFACELESS_MESA     0x31DD
#جيڪڏهن_پورو /* EGL_MESA_platform_surfaceless */

#جيڪڏهن_وصف_نه_ٿيل EGL_MESA_query_driver
#وصف_ڪريو EGL_MESA_query_driver 1
تعريفنوع حرف *(EGLAPIENTRYP PFNEGLGETDISPLAYDRIVERCONFIGPROC) (EGLDisplay dpy);
تعريفنوع ثابت حرف *(EGLAPIENTRYP PFNEGLGETDISPLAYDRIVERNAMEPROC) (EGLDisplay dpy);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI حرف *EGLAPIENTRY eglGetDisplayDriverConfig (EGLDisplay dpy);
EGLAPI ثابت حرف *EGLAPIENTRY eglGetDisplayDriverName (EGLDisplay dpy);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_MESA_query_driver */

#جيڪڏهن_وصف_نه_ٿيل EGL_NOK_مٽا_سٽا_region
#وصف_ڪريو EGL_NOK_مٽا_سٽا_region 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSREGIONNOKPROC) (EGLDisplay dpy, EGLSurface surface, EGLint انگ_Rects_2, ثابت EGLint *rects);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_مٽا_سٽا_Buffers_Region_NOK (EGLDisplay dpy, EGLSurface surface, EGLint انگ_Rects_2, ثابت EGLint *rects);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_NOK_swap_region */

#جيڪڏهن_وصف_نه_ٿيل EGL_NOK_مٽا_سٽا_region2
#وصف_ڪريو EGL_NOK_مٽا_سٽا_region2 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSREGION2NOKPROC) (EGLDisplay dpy, EGLSurface surface, EGLint انگ_Rects_2, ثابت EGLint *rects);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_مٽا_سٽا_Buffers_Region2_NOK (EGLDisplay dpy, EGLSurface surface, EGLint انگ_Rects_2, ثابت EGLint *rects);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_NOK_swap_region2 */

#جيڪڏهن_وصف_نه_ٿيل EGL_NOK_texture_from_pixmap
#وصف_ڪريو EGL_NOK_texture_from_pixmap 1
#وصف_ڪريو EGL_Y_INVERTED_NOK                0x307F
#جيڪڏهن_پورو /* EGL_NOK_texture_from_pixmap */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_3dvision_surface
#وصف_ڪريو EGL_NV_3dvision_surface 1
#وصف_ڪريو EGL_AUTO_STEREO_NV                0x3136
#جيڪڏهن_پورو /* EGL_NV_3dvision_surface */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_context_ترجيح_realtime
#وصف_ڪريو EGL_NV_context_ترجيح_realtime 1
#وصف_ڪريو EGL_CONTEXT_ترجيح_REALTIME_NV  0x3357
#جيڪڏهن_پورو /* EGL_NV_context_priority_realtime */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_coverage_sample
#وصف_ڪريو EGL_NV_coverage_sample 1
#وصف_ڪريو EGL_COVERAGE_BUFFERS_NV           0x30E0
#وصف_ڪريو EGL_COVERAGE_SAMPLES_NV           0x30E1
#جيڪڏهن_پورو /* EGL_NV_coverage_sample */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_coverage_sample_resolve
#وصف_ڪريو EGL_NV_coverage_sample_resolve 1
#وصف_ڪريو EGL_COVERAGE_SAMPLE_RESOLVE_NV    0x3131
#وصف_ڪريو EGL_COVERAGE_SAMPLE_RESOLVE_DEFAULT_NV 0x3132
#وصف_ڪريو EGL_COVERAGE_SAMPLE_RESOLVE_NONE_NV 0x3133
#جيڪڏهن_پورو /* EGL_NV_coverage_sample_resolve */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_cuda_event
#وصف_ڪريو EGL_NV_cuda_event 1
#وصف_ڪريو EGL_CUDA_EVENT_HANDLE_NV          0x323B
#وصف_ڪريو EGL_SYNC_CUDA_EVENT_NV            0x323C
#وصف_ڪريو EGL_SYNC_CUDA_EVENT_COMPLETE_NV   0x323D
#جيڪڏهن_پورو /* EGL_NV_cuda_event */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_اونهائي_nonlinear
#وصف_ڪريو EGL_NV_اونهائي_nonlinear 1
#وصف_ڪريو EGL_اونهائي_ENCODING_NV             0x30E2
#وصف_ڪريو EGL_اونهائي_ENCODING_NONE_NV        0
#وصف_ڪريو EGL_اونهائي_ENCODING_NONLINEAR_NV   0x30E3
#جيڪڏهن_پورو /* EGL_NV_depth_nonlinear */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_device_cuda
#وصف_ڪريو EGL_NV_device_cuda 1
#وصف_ڪريو EGL_CUDA_DEVICE_NV                0x323A
#جيڪڏهن_پورو /* EGL_NV_device_cuda */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_native_query
#وصف_ڪريو EGL_NV_native_query 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYNATIVEDISPLAYNVPROC) (EGLDisplay dpy, EGLNativeDisplayType *display_id);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYNATIVEWINDOWNVPROC) (EGLDisplay dpy, EGLSurface surf, EGLNative_دري_Type *دري);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYNATIVEPIXMAPNVPROC) (EGLDisplay dpy, EGLSurface surf, EGLNativePixmapType *pixmap);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryNativeDisplayNV (EGLDisplay dpy, EGLNativeDisplayType *display_id);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Native_دري_NV (EGLDisplay dpy, EGLSurface surf, EGLNative_دري_Type *دري);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryNativePixmapNV (EGLDisplay dpy, EGLSurface surf, EGLNativePixmapType *pixmap);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_NV_native_query */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_post_convert_rounding
#وصف_ڪريو EGL_NV_post_convert_rounding 1
#جيڪڏهن_پورو /* EGL_NV_post_convert_rounding */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_post_sub_بفر
#وصف_ڪريو EGL_NV_post_sub_بفر 1
#وصف_ڪريو EGL_POST_SUB_بفر_SUPPORTED_NV  0x30BE
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLPOSTSUBBUFFERNVPROC) (EGLDisplay dpy, EGLSurface surface, EGLint x, EGLint y, EGLint ويڪر, EGLint اوچائي);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Post_Sub_بفر_NV (EGLDisplay dpy, EGLSurface surface, EGLint x, EGLint y, EGLint ويڪر, EGLint اوچائي);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_NV_post_sub_buffer */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_quadruple_بفر
#وصف_ڪريو EGL_NV_quadruple_بفر 1
#وصف_ڪريو EGL_QUADRUPLE_بفر_NV           0x3231
#جيڪڏهن_پورو /* EGL_NV_quadruple_buffer */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_robustness_video_يادگيري_purge
#وصف_ڪريو EGL_NV_robustness_video_يادگيري_purge 1
#وصف_ڪريو EGL_GENERATE_RESET_ON_VIDEO_يادگيري_PURGE_NV 0x334C
#جيڪڏهن_پورو /* EGL_NV_robustness_video_memory_purge */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_وهڪرو_استعمال_ڪندڙ_eglimage
#وصف_ڪريو EGL_NV_وهڪرو_استعمال_ڪندڙ_eglimage 1
#وصف_ڪريو EGL_وهڪرو_استعمال_ڪندڙ_IMAGE_NV      0x3373
#وصف_ڪريو EGL_وهڪرو_IMAGE_جوڙيو_NV           0x3374
#وصف_ڪريو EGL_وهڪرو_IMAGE_REMOVE_NV        0x3375
#وصف_ڪريو EGL_وهڪرو_IMAGE_موجود_NV     0x3376
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMIMAGECONSUMERCONNECTNVPROC) (EGLDisplay dpy, EGLStreamKHR وهڪرو, EGLint انگ_modifiers, ثابت EGLuint64KHR *modifiers, ثابت EGLAttrib *attrib_list);
تعريفنوع EGLint (EGLAPIENTRYP PFNEGLQUERYSTREAMCONSUMEREVENTNVPROC) (EGLDisplay dpy, EGLStreamKHR وهڪرو, EGLTime timeout, EGLenum *event, EGLAttrib *aux);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMACQUIREIMAGENVPROC) (EGLDisplay dpy, EGLStreamKHR وهڪرو, EGLImage *pImage, EGLSync sync);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMRELEASEIMAGENVPROC) (EGLDisplay dpy, EGLStreamKHR وهڪرو, EGLImage image, EGLSync sync);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_وهڪرو_Image_استعمال_ڪندڙ_Connect_NV (EGLDisplay dpy, EGLStreamKHR وهڪرو, EGLint انگ_modifiers, ثابت EGLuint64KHR *modifiers, ثابت EGLAttrib *attrib_list);
EGLAPI EGLint EGLAPIENTRY egl_Query_وهڪرو_استعمال_ڪندڙ_Event_NV (EGLDisplay dpy, EGLStreamKHR وهڪرو, EGLTime timeout, EGLenum *event, EGLAttrib *aux);
EGLAPI EGLBoolean EGLAPIENTRY egl_وهڪرو_Acquire_Image_NV (EGLDisplay dpy, EGLStreamKHR وهڪرو, EGLImage *pImage, EGLSync sync);
EGLAPI EGLBoolean EGLAPIENTRY egl_وهڪرو_Release_Image_NV (EGLDisplay dpy, EGLStreamKHR وهڪرو, EGLImage image, EGLSync sync);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_NV_stream_consumer_eglimage */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_وهڪرو_استعمال_ڪندڙ_eglimage_use_scanout_attrib
#وصف_ڪريو EGL_NV_وهڪرو_استعمال_ڪندڙ_eglimage_use_scanout_attrib 1
#وصف_ڪريو EGL_وهڪرو_استعمال_ڪندڙ_IMAGE_USE_SCANOUT_NV 0x3378
#جيڪڏهن_پورو /* EGL_NV_stream_consumer_eglimage_use_scanout_attrib */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_وهڪرو_استعمال_ڪندڙ_gltexture_yuv
#وصف_ڪريو EGL_NV_وهڪرو_استعمال_ڪندڙ_gltexture_yuv 1
#وصف_ڪريو EGL_YUV_PLANE0_TEXTURE_UNIT_NV    0x332C
#وصف_ڪريو EGL_YUV_PLANE1_TEXTURE_UNIT_NV    0x332D
#وصف_ڪريو EGL_YUV_PLANE2_TEXTURE_UNIT_NV    0x332E
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALATTRIBSNVPROC) (EGLDisplay dpy, EGLStreamKHR وهڪرو, ثابت EGLAttrib *attrib_list);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_وهڪرو_استعمال_ڪندڙ_GLTexture_External_Attribs_NV (EGLDisplay dpy, EGLStreamKHR وهڪرو, ثابت EGLAttrib *attrib_list);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_NV_stream_consumer_gltexture_yuv */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_وهڪرو_cross_display
#وصف_ڪريو EGL_NV_وهڪرو_cross_display 1
#وصف_ڪريو EGL_وهڪرو_CROSS_DISPLAY_NV       0x334E
#جيڪڏهن_پورو /* EGL_NV_stream_cross_display */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_وهڪرو_cross_object
#وصف_ڪريو EGL_NV_وهڪرو_cross_object 1
#وصف_ڪريو EGL_وهڪرو_CROSS_OBJECT_NV        0x334D
#جيڪڏهن_پورو /* EGL_NV_stream_cross_object */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_وهڪرو_cross_حصا_ڪريو
#وصف_ڪريو EGL_NV_وهڪرو_cross_حصا_ڪريو 1
#وصف_ڪريو EGL_وهڪرو_CROSS_حصا_ڪريو_NV     0x323F
#جيڪڏهن_پورو /* EGL_NV_stream_cross_partition */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_وهڪرو_cross_process
#وصف_ڪريو EGL_NV_وهڪرو_cross_process 1
#وصف_ڪريو EGL_وهڪرو_CROSS_PROCESS_NV       0x3245
#جيڪڏهن_پورو /* EGL_NV_stream_cross_process */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_وهڪرو_cross_system
#وصف_ڪريو EGL_NV_وهڪرو_cross_system 1
#وصف_ڪريو EGL_وهڪرو_CROSS_SYSTEM_NV        0x334F
#جيڪڏهن_پورو /* EGL_NV_stream_cross_system */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_وهڪرو_dma
#وصف_ڪريو EGL_NV_وهڪرو_dma 1
#وصف_ڪريو EGL_وهڪرو_DMA_NV                 0x3371
#وصف_ڪريو EGL_وهڪرو_DMA_SERVER_NV          0x3372
#جيڪڏهن_پورو /* EGL_NV_stream_dma */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_وهڪرو_fifo_ايندڙ
#وصف_ڪريو EGL_NV_وهڪرو_fifo_ايندڙ 1
#وصف_ڪريو EGL_PENDING_چوکٺو_NV              0x3329
#وصف_ڪريو EGL_وهڪرو_وقت_PENDING_NV        0x332A
#جيڪڏهن_پورو /* EGL_NV_stream_fifo_next */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_وهڪرو_fifo_synchronous
#وصف_ڪريو EGL_NV_وهڪرو_fifo_synchronous 1
#وصف_ڪريو EGL_وهڪرو_FIFO_SYNCHRONOUS_NV    0x3336
#جيڪڏهن_پورو /* EGL_NV_stream_fifo_synchronous */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_وهڪرو_flush
#وصف_ڪريو EGL_NV_وهڪرو_flush 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMFLUSHNVPROC) (EGLDisplay dpy, EGLStreamKHR وهڪرو);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_وهڪرو_Flush_NV (EGLDisplay dpy, EGLStreamKHR وهڪرو);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_NV_stream_flush */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_وهڪرو_چوکٺو_limits
#وصف_ڪريو EGL_NV_وهڪرو_چوکٺو_limits 1
#وصف_ڪريو EGL_پيداوار_ڪندڙ_MAX_چوکٺو_HINT_NV    0x3337
#وصف_ڪريو EGL_استعمال_ڪندڙ_MAX_چوکٺو_HINT_NV    0x3338
#جيڪڏهن_پورو /* EGL_NV_stream_frame_limits */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_وهڪرو_metadata
#وصف_ڪريو EGL_NV_وهڪرو_metadata 1
#وصف_ڪريو EGL_MAX_وهڪرو_METADATA_بلاڪون_NV 0x3250
#وصف_ڪريو EGL_MAX_وهڪرو_METADATA_بلاڪ_سائيز_NV 0x3251
#وصف_ڪريو EGL_MAX_وهڪرو_METADATA_ڪل_سائيز_NV 0x3252
#وصف_ڪريو EGL_پيداوار_ڪندڙ_METADATA_NV          0x3253
#وصف_ڪريو EGL_استعمال_ڪندڙ_METADATA_NV          0x3254
#وصف_ڪريو EGL_PENDING_METADATA_NV           0x3328
#وصف_ڪريو EGL_METADATA0_سائيز_NV             0x3255
#وصف_ڪريو EGL_METADATA1_سائيز_NV             0x3256
#وصف_ڪريو EGL_METADATA2_سائيز_NV             0x3257
#وصف_ڪريو EGL_METADATA3_سائيز_NV             0x3258
#وصف_ڪريو EGL_METADATA0_TYPE_NV             0x3259
#وصف_ڪريو EGL_METADATA1_TYPE_NV             0x325A
#وصف_ڪريو EGL_METADATA2_TYPE_NV             0x325B
#وصف_ڪريو EGL_METADATA3_TYPE_NV             0x325C
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDISPLAYATTRIBNVPROC) (EGLDisplay dpy, EGLint attribute, EGLAttrib *قدر);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSETSTREAMMETADATANVPROC) (EGLDisplay dpy, EGLStreamKHR وهڪرو, EGLint n, EGLint وٿي_2, EGLint سائيز, ثابت فراغ *معلومات);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMMETADATANVPROC) (EGLDisplay dpy, EGLStreamKHR وهڪرو, EGLenum name, EGLint n, EGLint وٿي_2, EGLint سائيز, فراغ *معلومات);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDisplayAttribNV (EGLDisplay dpy, EGLint attribute, EGLAttrib *قدر);
EGLAPI EGLBoolean EGLAPIENTRY egl_سيٽ_وهڪرو_Metadata_NV (EGLDisplay dpy, EGLStreamKHR وهڪرو, EGLint n, EGLint وٿي_2, EGLint سائيز, ثابت فراغ *معلومات);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_وهڪرو_Metadata_NV (EGLDisplay dpy, EGLStreamKHR وهڪرو, EGLenum name, EGLint n, EGLint وٿي_2, EGLint سائيز, فراغ *معلومات);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_NV_stream_metadata */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_وهڪرو_origin
#وصف_ڪريو EGL_NV_وهڪرو_origin 1
#وصف_ڪريو EGL_وهڪرو_چوکٺو_ORIGIN_X_NV      0x3366
#وصف_ڪريو EGL_وهڪرو_چوکٺو_ORIGIN_Y_NV      0x3367
#وصف_ڪريو EGL_وهڪرو_چوکٺو_MAJOR_AXIS_NV    0x3368
#وصف_ڪريو EGL_استعمال_ڪندڙ_AUTO_ORIENTATION_NV  0x3369
#وصف_ڪريو EGL_پيداوار_ڪندڙ_AUTO_ORIENTATION_NV  0x336A
#وصف_ڪريو EGL_کاٻو_NV                       0x336B
#وصف_ڪريو EGL_ساڄو_NV                      0x336C
#وصف_ڪريو EGL_چوٽي_NV                        0x336D
#وصف_ڪريو EGL_BOTTOM_NV                     0x336E
#وصف_ڪريو EGL_X_AXIS_NV                     0x336F
#وصف_ڪريو EGL_Y_AXIS_NV                     0x3370
#جيڪڏهن_پورو /* EGL_NV_stream_origin */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_وهڪرو_remote
#وصف_ڪريو EGL_NV_وهڪرو_remote 1
#وصف_ڪريو EGL_وهڪرو_STATE_INITIALIZING_NV  0x3240
#وصف_ڪريو EGL_وهڪرو_TYPE_NV                0x3241
#وصف_ڪريو EGL_وهڪرو_PROTOCOL_NV            0x3242
#وصف_ڪريو EGL_وهڪرو_ENDPOINT_NV            0x3243
#وصف_ڪريو EGL_وهڪرو_LOCAL_NV               0x3244
#وصف_ڪريو EGL_وهڪرو_پيداوار_ڪندڙ_NV            0x3247
#وصف_ڪريو EGL_وهڪرو_استعمال_ڪندڙ_NV            0x3248
#وصف_ڪريو EGL_وهڪرو_PROTOCOL_FD_NV         0x3246
#جيڪڏهن_پورو /* EGL_NV_stream_remote */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_وهڪرو_reset
#وصف_ڪريو EGL_NV_وهڪرو_reset 1
#وصف_ڪريو EGL_SUPPORT_RESET_NV              0x3334
#وصف_ڪريو EGL_SUPPORT_REUSE_NV              0x3335
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLRESETSTREAMNVPROC) (EGLDisplay dpy, EGLStreamKHR وهڪرو);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Reset_وهڪرو_NV (EGLDisplay dpy, EGLStreamKHR وهڪرو);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_NV_stream_reset */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_وهڪرو_socket
#وصف_ڪريو EGL_NV_وهڪرو_socket 1
#وصف_ڪريو EGL_وهڪرو_PROTOCOL_SOCKET_NV     0x324B
#وصف_ڪريو EGL_SOCKET_HANDLE_NV              0x324C
#وصف_ڪريو EGL_SOCKET_TYPE_NV                0x324D
#جيڪڏهن_پورو /* EGL_NV_stream_socket */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_وهڪرو_socket_inet
#وصف_ڪريو EGL_NV_وهڪرو_socket_inet 1
#وصف_ڪريو EGL_SOCKET_TYPE_INET_NV           0x324F
#جيڪڏهن_پورو /* EGL_NV_stream_socket_inet */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_وهڪرو_socket_unix
#وصف_ڪريو EGL_NV_وهڪرو_socket_unix 1
#وصف_ڪريو EGL_SOCKET_TYPE_UNIX_NV           0x324E
#جيڪڏهن_پورو /* EGL_NV_stream_socket_unix */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_وهڪرو_sync
#وصف_ڪريو EGL_NV_وهڪرو_sync 1
#وصف_ڪريو EGL_SYNC_NEW_چوکٺو_NV             0x321F
تعريفنوع EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESTREAMSYNCNVPROC) (EGLDisplay dpy, EGLStreamKHR وهڪرو, EGLenum type, ثابت EGLint *attrib_list);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncKHR EGLAPIENTRY egl_Create_وهڪرو_Sync_NV (EGLDisplay dpy, EGLStreamKHR وهڪرو, EGLenum type, ثابت EGLint *attrib_list);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_NV_stream_sync */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_sync
#وصف_ڪريو EGL_NV_sync 1
تعريفنوع فراغ *EGLSyncNV;
تعريفنوع khronos_utime_nanoseconds_t EGLTimeNV;
#جيڪڏهن_وصف_ٿيل KHRONOS_SUPPORT_INT64
#وصف_ڪريو EGL_SYNC_اڳواٽ_COMMANDS_COMPLETE_NV 0x30E6
#وصف_ڪريو EGL_SYNC_حالت_NV                0x30E7
#وصف_ڪريو EGL_SIGNALED_NV                   0x30E8
#وصف_ڪريو EGL_UNSIGNALED_NV                 0x30E9
#وصف_ڪريو EGL_SYNC_FLUSH_COMMANDS_ٻٽو_انگ_NV    0x0001
#وصف_ڪريو EGL_FOREVER_NV                    0xFFFFFFFFFFFFFFFFull
#وصف_ڪريو EGL_ALREADY_SIGNALED_NV           0x30EA
#وصف_ڪريو EGL_TIMEOUT_EXPIRED_NV            0x30EB
#وصف_ڪريو EGL_CONDITION_SATISFIED_NV        0x30EC
#وصف_ڪريو EGL_SYNC_TYPE_NV                  0x30ED
#وصف_ڪريو EGL_SYNC_CONDITION_NV             0x30EE
#وصف_ڪريو EGL_SYNC_FENCE_NV                 0x30EF
#وصف_ڪريو EGL_NO_SYNC_NV                    EGL_CAST(EGLSyncNV,0)
تعريفنوع EGLSyncNV (EGLAPIENTRYP PFNEGLCREATEFENCESYNCNVPROC) (EGLDisplay dpy, EGLenum condition, ثابت EGLint *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCNVPROC) (EGLSyncNV sync);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLFENCENVPROC) (EGLSyncNV sync);
تعريفنوع EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCNVPROC) (EGLSyncNV sync, EGLint flags, EGLTimeNV timeout);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSIGNALSYNCNVPROC) (EGLSyncNV sync, EGLenum گهڻائي);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETSYNCATTRIBNVPROC) (EGLSyncNV sync, EGLint attribute, EGLint *قدر);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncNV EGLAPIENTRY eglCreateFenceSyncNV (EGLDisplay dpy, EGLenum condition, ثابت EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySyncNV (EGLSyncNV sync);
EGLAPI EGLBoolean EGLAPIENTRY eglFenceNV (EGLSyncNV sync);
EGLAPI EGLint EGLAPIENTRY eglClientWaitSyncNV (EGLSyncNV sync, EGLint flags, EGLTimeNV timeout);
EGLAPI EGLBoolean EGLAPIENTRY eglSignalSyncNV (EGLSyncNV sync, EGLenum گهڻائي);
EGLAPI EGLBoolean EGLAPIENTRY eglGetSyncAttribNV (EGLSyncNV sync, EGLint attribute, EGLint *قدر);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* KHRONOS_SUPPORT_INT64 */
#جيڪڏهن_پورو /* EGL_NV_sync */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_system_وقت
#وصف_ڪريو EGL_NV_system_وقت 1
تعريفنوع khronos_utime_nanoseconds_t EGLuint64NV;
#جيڪڏهن_وصف_ٿيل KHRONOS_SUPPORT_INT64
تعريفنوع EGLuint64NV (EGLAPIENTRYP PFNEGLGETSYSTEMTIMEFREQUENCYNVPROC) (فراغ);
تعريفنوع EGLuint64NV (EGLAPIENTRYP PFNEGLGETSYSTEMTIMENVPROC) (فراغ);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLuint64NV EGLAPIENTRY egl_Get_System_وقت_Frequency_NV (فراغ);
EGLAPI EGLuint64NV EGLAPIENTRY egl_Get_System_وقت_NV (فراغ);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* KHRONOS_SUPPORT_INT64 */
#جيڪڏهن_پورو /* EGL_NV_system_time */

#جيڪڏهن_وصف_نه_ٿيل EGL_NV_triple_بفر
#وصف_ڪريو EGL_NV_triple_بفر 1
#وصف_ڪريو EGL_TRIPLE_بفر_NV              0x3230
#جيڪڏهن_پورو /* EGL_NV_triple_buffer */

#جيڪڏهن_وصف_نه_ٿيل EGL_QNX_image_native_بفر
#وصف_ڪريو EGL_QNX_image_native_بفر 1
#وصف_ڪريو EGL_NATIVE_بفر_QNX             0x3551
#جيڪڏهن_پورو /* EGL_QNX_image_native_buffer */

#جيڪڏهن_وصف_نه_ٿيل EGL_QNX_platform_screen
#وصف_ڪريو EGL_QNX_platform_screen 1
#وصف_ڪريو EGL_PLATFORM_SCREEN_QNX           0x3550
#جيڪڏهن_پورو /* EGL_QNX_platform_screen */

#جيڪڏهن_وصف_نه_ٿيل EGL_TIZEN_image_native_بفر
#وصف_ڪريو EGL_TIZEN_image_native_بفر 1
#وصف_ڪريو EGL_NATIVE_بفر_TIZEN           0x32A0
#جيڪڏهن_پورو /* EGL_TIZEN_image_native_buffer */

#جيڪڏهن_وصف_نه_ٿيل EGL_TIZEN_image_native_surface
#وصف_ڪريو EGL_TIZEN_image_native_surface 1
#وصف_ڪريو EGL_NATIVE_SURFACE_TIZEN          0x32A1
#جيڪڏهن_پورو /* EGL_TIZEN_image_native_surface */

#جيڪڏهن_وصف_نه_ٿيل EGL_WL_bind_wayland_display
#وصف_ڪريو EGL_WL_bind_wayland_display 1
#وصف_ڪريو PFNEGLBINDWAYLANDDISPLAYWL PFNEGLBINDWAYLANDDISPLAYWLPROC
#وصف_ڪريو PFNEGLUNBINDWAYLANDDISPLAYWL PFNEGLUNBINDWAYLANDDISPLAYWLPROC
#وصف_ڪريو PFNEGLQUERYWAYLANDBUFFERWL PFNEGLQUERYWAYLANDBUFFERWLPROC
بنية wl_display;
بنية wl_resource;
#وصف_ڪريو EGL_WAYLAND_بفر_WL             0x31D5
#وصف_ڪريو EGL_WAYLAND_PLANE_WL              0x31D6
#وصف_ڪريو EGL_TEXTURE_Y_U_V_WL              0x31D7
#وصف_ڪريو EGL_TEXTURE_Y_UV_WL               0x31D8
#وصف_ڪريو EGL_TEXTURE_Y_XUXV_WL             0x31D9
#وصف_ڪريو EGL_TEXTURE_EXTERNAL_WL           0x31DA
#وصف_ڪريو EGL_WAYLAND_Y_INVERTED_WL         0x31DB
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLBINDWAYLANDDISPLAYWLPROC) (EGLDisplay dpy, بنية wl_display *display);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLUNBINDWAYLANDDISPLAYWLPROC) (EGLDisplay dpy, بنية wl_display *display);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYWAYLANDBUFFERWLPROC) (EGLDisplay dpy, بنية wl_resource *بفر_2, EGLint attribute, EGLint *قدر);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglBindWaylandDisplayWL (EGLDisplay dpy, بنية wl_display *display);
EGLAPI EGLBoolean EGLAPIENTRY eglUnbindWaylandDisplayWL (EGLDisplay dpy, بنية wl_display *display);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Wayland_بفر_WL (EGLDisplay dpy, بنية wl_resource *بفر_2, EGLint attribute, EGLint *قدر);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_WL_bind_wayland_display */

#جيڪڏهن_وصف_نه_ٿيل EGL_WL_create_wayland_بفر_from_image
#وصف_ڪريو EGL_WL_create_wayland_بفر_from_image 1
#وصف_ڪريو PFNEGLCREATEWAYLANDBUFFERFROMIMAGEWL PFNEGLCREATEWAYLANDBUFFERFROMIMAGEWLPROC
بنية wl_بفر;
تعريفنوع بنية wl_بفر *(EGLAPIENTRYP PFNEGLCREATEWAYLANDBUFFERFROMIMAGEWLPROC) (EGLDisplay dpy, EGLImageKHR image);
#جيڪڏهن_وصف_ٿيل EGL_EGLEXT_PROTOTYPES
EGLAPI بنية wl_بفر *EGLAPIENTRY egl_Create_Wayland_بفر_From_Image_WL (EGLDisplay dpy, EGLImageKHR image);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* EGL_WL_create_wayland_buffer_from_image */

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو
