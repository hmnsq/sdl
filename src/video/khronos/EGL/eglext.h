#که_نه_تعریف_شوی __eglext_h_
#تعریف_کړه __eglext_h_ 1

#که_تعریف_شوی __cplusplus
خارجي "C" {
#د_که_پای

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

#تعریف_کړه EGL_EGLEXT_نسخه 20260319

/* Generated C header for:
 * API: egl
 * Versions considered: .*
 * Versions emitted: _nomatch_^
 * Default extensions included: egl
 * Additional extensions included: _nomatch_^
 * Extensions removed: _nomatch_^
 */

#که_نه_تعریف_شوی EGL_KHR_cl_event
#تعریف_کړه EGL_KHR_cl_event 1
#تعریف_کړه EGL_CL_EVENT_HANDLE_KHR           0x309C
#تعریف_کړه EGL_SYNC_CL_EVENT_KHR             0x30FE
#تعریف_کړه EGL_SYNC_CL_EVENT_COMPLETE_KHR    0x30FF
#د_که_پای /* EGL_KHR_cl_event */

#که_نه_تعریف_شوی EGL_KHR_cl_event2
#تعریف_کړه EGL_KHR_cl_event2 1
تعريفنوع فراغ *EGLSyncKHR;
تعريفنوع intptr_t EGLAttribKHR;
تعريفنوع EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESYNC64KHRPROC) (EGLDisplay dpy, EGLenum type, ثابت EGLAttribKHR *attrib_list);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncKHR EGLAPIENTRY eglCreateSync64KHR (EGLDisplay dpy, EGLenum type, ثابت EGLAttribKHR *attrib_list);
#د_که_پای
#د_که_پای /* EGL_KHR_cl_event2 */

#که_نه_تعریف_شوی EGL_KHR_client_get_all_proc_پتې
#تعریف_کړه EGL_KHR_client_get_all_proc_پتې 1
#د_که_پای /* EGL_KHR_client_get_all_proc_addresses */

#که_نه_تعریف_شوی EGL_KHR_config_attribs
#تعریف_کړه EGL_KHR_config_attribs 1
#تعریف_کړه EGL_CONFORMANT_KHR                0x3042
#تعریف_کړه EGL_VG_COLORSPACE_خطي_بټ_KHR  0x0020
#تعریف_کړه EGL_VG_ALPHA_FORMAT_PRE_بټ_KHR   0x0040
#د_که_پای /* EGL_KHR_config_attribs */

#که_نه_تعریف_شوی EGL_KHR_context_flush_control
#تعریف_کړه EGL_KHR_context_flush_control 1
#تعریف_کړه EGL_CONTEXT_RELEASE_BEHAVIOR_NONE_KHR 0
#تعریف_کړه EGL_CONTEXT_RELEASE_BEHAVIOR_KHR  0x2097
#تعریف_کړه EGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_KHR 0x2098
#د_که_پای /* EGL_KHR_context_flush_control */

#که_نه_تعریف_شوی EGL_KHR_create_context
#تعریف_کړه EGL_KHR_create_context 1
#تعریف_کړه EGL_CONTEXT_MAJOR_نسخه_KHR     0x3098
#تعریف_کړه EGL_CONTEXT_MINOR_نسخه_KHR     0x30FB
#تعریف_کړه EGL_CONTEXT_FLAGS_KHR             0x30FC
#تعریف_کړه EGL_CONTEXT_OPENGL_PROFILE_ماسک_KHR 0x30FD
#تعریف_کړه EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_KHR 0x31BD
#تعریف_کړه EGL_NO_RESET_NOTIFICATION_KHR     0x31BE
#تعریف_کړه EGL_LOSE_CONTEXT_ON_RESET_KHR     0x31BF
#تعریف_کړه EGL_CONTEXT_OPENGL_DEBUG_بټ_KHR  0x00000001
#تعریف_کړه EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_بټ_KHR 0x00000002
#تعریف_کړه EGL_CONTEXT_OPENGL_ROBUST_ACCESS_بټ_KHR 0x00000004
#تعریف_کړه EGL_CONTEXT_OPENGL_CORE_PROFILE_بټ_KHR 0x00000001
#تعریف_کړه EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_بټ_KHR 0x00000002
#تعریف_کړه EGL_OPENGL_ES3_بټ_KHR            0x00000040
#د_که_پای /* EGL_KHR_create_context */

#که_نه_تعریف_شوی EGL_KHR_create_context_no_error
#تعریف_کړه EGL_KHR_create_context_no_error 1
#تعریف_کړه EGL_CONTEXT_OPENGL_NO_ERROR_KHR   0x31B3
#د_که_پای /* EGL_KHR_create_context_no_error */

#که_نه_تعریف_شوی EGL_KHR_debug
#تعریف_کړه EGL_KHR_debug 1
تعريفنوع فراغ *EGLLabelKHR;
تعريفنوع فراغ *EGLObjectKHR;
تعريفنوع فراغ (EGLAPIENTRY  *EGLDEBUGPROCKHR)(EGLenum error,ثابت حرف *command,EGLint پیغام_Type,EGLLabelKHR threadLabel,EGLLabelKHR objectLabel,ثابت حرف* پیغام);
#تعریف_کړه EGL_OBJECT_THREAD_KHR             0x33B0
#تعریف_کړه EGL_OBJECT_DISPLAY_KHR            0x33B1
#تعریف_کړه EGL_OBJECT_CONTEXT_KHR            0x33B2
#تعریف_کړه EGL_OBJECT_SURFACE_KHR            0x33B3
#تعریف_کړه EGL_OBJECT_IMAGE_KHR              0x33B4
#تعریف_کړه EGL_OBJECT_SYNC_KHR               0x33B5
#تعریف_کړه EGL_OBJECT_بهیر_KHR             0x33B6
#تعریف_کړه EGL_DEBUG_پیغام_CRITICAL_KHR        0x33B9
#تعریف_کړه EGL_DEBUG_پیغام_ERROR_KHR           0x33BA
#تعریف_کړه EGL_DEBUG_پیغام_WARN_KHR            0x33BB
#تعریف_کړه EGL_DEBUG_پیغام_INFO_KHR            0x33BC
#تعریف_کړه EGL_DEBUG_CALLBACK_KHR            0x33B8
تعريفنوع EGLint (EGLAPIENTRYP PFNEGLDEBUGMESSAGECONTROLKHRPROC) (EGLDEBUGPROCKHR callback, ثابت EGLAttrib *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEBUGKHRPROC) (EGLint attribute, EGLAttrib *ارزښت);
تعريفنوع EGLint (EGLAPIENTRYP PFNEGLLABELOBJECTKHRPROC) (EGLDisplay display, EGLenum objectType, EGLObjectKHR object, EGLLabelKHR label);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLint EGLAPIENTRY egl_Debug_پیغام_Control_KHR (EGLDEBUGPROCKHR callback, ثابت EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDebugKHR (EGLint attribute, EGLAttrib *ارزښت);
EGLAPI EGLint EGLAPIENTRY eglLabelObjectKHR (EGLDisplay display, EGLenum objectType, EGLObjectKHR object, EGLLabelKHR label);
#د_که_پای
#د_که_پای /* EGL_KHR_debug */

#که_نه_تعریف_شوی EGL_KHR_display_reference
#تعریف_کړه EGL_KHR_display_reference 1
#تعریف_کړه EGL_TRACK_REFERENCES_KHR          0x3352
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDISPLAYATTRIBKHRPROC) (EGLDisplay dpy, EGLint name, EGLAttrib *ارزښت);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDisplayAttribKHR (EGLDisplay dpy, EGLint name, EGLAttrib *ارزښت);
#د_که_پای
#د_که_پای /* EGL_KHR_display_reference */

#که_نه_تعریف_شوی EGL_KHR_fence_sync
#تعریف_کړه EGL_KHR_fence_sync 1
تعريفنوع khronos_utime_nanoseconds_t EGLTimeKHR;
#که_تعریف_شوی KHRONOS_SUPPORT_INT64
#تعریف_کړه EGL_SYNC_مخکینی_COMMANDS_COMPLETE_KHR 0x30F0
#تعریف_کړه EGL_SYNC_CONDITION_KHR            0x30F8
#تعریف_کړه EGL_SYNC_FENCE_KHR                0x30F9
تعريفنوع EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESYNCKHRPROC) (EGLDisplay dpy, EGLenum type, ثابت EGLint *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync);
تعريفنوع EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETSYNCATTRIBKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint attribute, EGLint *ارزښت);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncKHR EGLAPIENTRY eglCreateSyncKHR (EGLDisplay dpy, EGLenum type, ثابت EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySyncKHR (EGLDisplay dpy, EGLSyncKHR sync);
EGLAPI EGLint EGLAPIENTRY eglClientWaitSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);
EGLAPI EGLBoolean EGLAPIENTRY eglGetSyncAttribKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint attribute, EGLint *ارزښت);
#د_که_پای
#د_که_پای /* KHRONOS_SUPPORT_INT64 */
#د_که_پای /* EGL_KHR_fence_sync */

#که_نه_تعریف_شوی EGL_KHR_get_all_proc_پتې
#تعریف_کړه EGL_KHR_get_all_proc_پتې 1
#د_که_پای /* EGL_KHR_get_all_proc_addresses */

#که_نه_تعریف_شوی EGL_KHR_gl_colorspace
#تعریف_کړه EGL_KHR_gl_colorspace 1
#تعریف_کړه EGL_GL_COLORSPACE_KHR             0x309D
#تعریف_کړه EGL_GL_COLORSPACE_SRGB_KHR        0x3089
#تعریف_کړه EGL_GL_COLORSPACE_خطي_KHR      0x308A
#د_که_پای /* EGL_KHR_gl_colorspace */

#که_نه_تعریف_شوی EGL_KHR_gl_renderbuffer_image
#تعریف_کړه EGL_KHR_gl_renderbuffer_image 1
#تعریف_کړه EGL_GL_RENDERBUFFER_KHR           0x30B9
#د_که_پای /* EGL_KHR_gl_renderbuffer_image */

#که_نه_تعریف_شوی EGL_KHR_gl_texture_2D_image
#تعریف_کړه EGL_KHR_gl_texture_2D_image 1
#تعریف_کړه EGL_GL_TEXTURE_2D_KHR             0x30B1
#تعریف_کړه EGL_GL_TEXTURE_LEVEL_KHR          0x30BC
#د_که_پای /* EGL_KHR_gl_texture_2D_image */

#که_نه_تعریف_شوی EGL_KHR_gl_texture_3D_image
#تعریف_کړه EGL_KHR_gl_texture_3D_image 1
#تعریف_کړه EGL_GL_TEXTURE_3D_KHR             0x30B2
#تعریف_کړه EGL_GL_TEXTURE_ZOFFSET_KHR        0x30BD
#د_که_پای /* EGL_KHR_gl_texture_3D_image */

#که_نه_تعریف_شوی EGL_KHR_gl_texture_cubemap_image
#تعریف_کړه EGL_KHR_gl_texture_cubemap_image 1
#تعریف_کړه EGL_GL_TEXTURE_CUBE_MAP_مثبت_X_KHR 0x30B3
#تعریف_کړه EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_X_KHR 0x30B4
#تعریف_کړه EGL_GL_TEXTURE_CUBE_MAP_مثبت_Y_KHR 0x30B5
#تعریف_کړه EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_KHR 0x30B6
#تعریف_کړه EGL_GL_TEXTURE_CUBE_MAP_مثبت_Z_KHR 0x30B7
#تعریف_کړه EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_KHR 0x30B8
#د_که_پای /* EGL_KHR_gl_texture_cubemap_image */

#که_نه_تعریف_شوی EGL_KHR_image
#تعریف_کړه EGL_KHR_image 1
تعريفنوع فراغ *EGLImageKHR;
#تعریف_کړه EGL_NATIVE_PIXMAP_KHR             0x30B0
#تعریف_کړه EGL_NO_IMAGE_KHR                  EGL_CAST(EGLImageKHR,0)
تعريفنوع EGLImageKHR (EGLAPIENTRYP PFNEGLCREATEIMAGEKHRPROC) (EGLDisplay dpy, EGLContext ctx, EGLenum موخه, EGLClient_بفر بفر_2, ثابت EGLint *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYIMAGEKHRPROC) (EGLDisplay dpy, EGLImageKHR image);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLImageKHR EGLAPIENTRY eglCreateImageKHR (EGLDisplay dpy, EGLContext ctx, EGLenum موخه, EGLClient_بفر بفر_2, ثابت EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyImageKHR (EGLDisplay dpy, EGLImageKHR image);
#د_که_پای
#د_که_پای /* EGL_KHR_image */

#که_نه_تعریف_شوی EGL_KHR_image_بنسټ
#تعریف_کړه EGL_KHR_image_بنسټ 1
#تعریف_کړه EGL_IMAGE_PRESERVED_KHR           0x30D2
#د_که_پای /* EGL_KHR_image_base */

#که_نه_تعریف_شوی EGL_KHR_image_pixmap
#تعریف_کړه EGL_KHR_image_pixmap 1
#د_که_پای /* EGL_KHR_image_pixmap */

#که_نه_تعریف_شوی EGL_KHR_قلف_surface
#تعریف_کړه EGL_KHR_قلف_surface 1
#تعریف_کړه EGL_READ_SURFACE_بټ_KHR          0x0001
#تعریف_کړه EGL_WRITE_SURFACE_بټ_KHR         0x0002
#تعریف_کړه EGL_قلف_SURFACE_بټ_KHR          0x0080
#تعریف_کړه EGL_OPTIMAL_FORMAT_بټ_KHR        0x0100
#تعریف_کړه EGL_سمون_FORMAT_KHR              0x3043
#تعریف_کړه EGL_FORMAT_RGB_565_EXACT_KHR      0x30C0
#تعریف_کړه EGL_FORMAT_RGB_565_KHR            0x30C1
#تعریف_کړه EGL_FORMAT_RGBA_8888_EXACT_KHR    0x30C2
#تعریف_کړه EGL_FORMAT_RGBA_8888_KHR          0x30C3
#تعریف_کړه EGL_MAP_PRESERVE_PIXELS_KHR       0x30C4
#تعریف_کړه EGL_قلف_USAGE_HINT_KHR           0x30C5
#تعریف_کړه EGL_BITMAP_اشاره_ګر_KHR            0x30C6
#تعریف_کړه EGL_BITMAP_PITCH_KHR              0x30C7
#تعریف_کړه EGL_BITMAP_ORIGIN_KHR             0x30C8
#تعریف_کړه EGL_BITMAP_PIXEL_RED_دننه_واټن_KHR   0x30C9
#تعریف_کړه EGL_BITMAP_PIXEL_GREEN_دننه_واټن_KHR 0x30CA
#تعریف_کړه EGL_BITMAP_PIXEL_BLUE_دننه_واټن_KHR  0x30CB
#تعریف_کړه EGL_BITMAP_PIXEL_ALPHA_دننه_واټن_KHR 0x30CC
#تعریف_کړه EGL_BITMAP_PIXEL_LUMINANCE_دننه_واټن_KHR 0x30CD
#تعریف_کړه EGL_ښکتنی_کیڼ_KHR                0x30CE
#تعریف_کړه EGL_پاسنی_کیڼ_KHR                0x30CF
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLLOCKSURFACEKHRPROC) (EGLDisplay dpy, EGLSurface surface, ثابت EGLint *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLUNLOCKSURFACEKHRPROC) (EGLDisplay dpy, EGLSurface surface);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_قلف_Surface_KHR (EGLDisplay dpy, EGLSurface surface, ثابت EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglUnlockSurfaceKHR (EGLDisplay dpy, EGLSurface surface);
#د_که_پای
#د_که_پای /* EGL_KHR_lock_surface */

#که_نه_تعریف_شوی EGL_KHR_قلف_surface2
#تعریف_کړه EGL_KHR_قلف_surface2 1
#تعریف_کړه EGL_BITMAP_PIXEL_اندازه_KHR         0x3110
#د_که_پای /* EGL_KHR_lock_surface2 */

#که_نه_تعریف_شوی EGL_KHR_قلف_surface3
#تعریف_کړه EGL_KHR_قلف_surface3 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSURFACE64KHRPROC) (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLAttribKHR *ارزښت);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQuerySurface64KHR (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLAttribKHR *ارزښت);
#د_که_پای
#د_که_پای /* EGL_KHR_lock_surface3 */

#که_نه_تعریف_شوی EGL_KHR_mutable_render_بفر
#تعریف_کړه EGL_KHR_mutable_render_بفر 1
#تعریف_کړه EGL_MUTABLE_RENDER_بفر_بټ_KHR 0x1000
#د_که_پای /* EGL_KHR_mutable_render_buffer */

#که_نه_تعریف_شوی EGL_KHR_no_config_context
#تعریف_کړه EGL_KHR_no_config_context 1
#تعریف_کړه EGL_NO_CONFIG_KHR                 EGL_CAST(EGLConfig,0)
#د_که_پای /* EGL_KHR_no_config_context */

#که_نه_تعریف_شوی EGL_KHR_partial_update
#تعریف_کړه EGL_KHR_partial_update 1
#تعریف_کړه EGL_بفر_AGE_KHR                0x313D
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSETDAMAGEREGIONKHRPROC) (EGLDisplay dpy, EGLSurface surface, EGLint *rects, EGLint n_rects);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_سېټ_Damage_Region_KHR (EGLDisplay dpy, EGLSurface surface, EGLint *rects, EGLint n_rects);
#د_که_پای
#د_که_پای /* EGL_KHR_partial_update */

#که_نه_تعریف_شوی EGL_KHR_platform_android
#تعریف_کړه EGL_KHR_platform_android 1
#تعریف_کړه EGL_PLATFORM_ANDROID_KHR          0x3141
#د_که_پای /* EGL_KHR_platform_android */

#که_نه_تعریف_شوی EGL_KHR_platform_gbm
#تعریف_کړه EGL_KHR_platform_gbm 1
#تعریف_کړه EGL_PLATFORM_GBM_KHR              0x31D7
#د_که_پای /* EGL_KHR_platform_gbm */

#که_نه_تعریف_شوی EGL_KHR_platform_wayland
#تعریف_کړه EGL_KHR_platform_wayland 1
#تعریف_کړه EGL_PLATFORM_WAYLAND_KHR          0x31D8
#د_که_پای /* EGL_KHR_platform_wayland */

#که_نه_تعریف_شوی EGL_KHR_platform_x11
#تعریف_کړه EGL_KHR_platform_x11 1
#تعریف_کړه EGL_PLATFORM_X11_KHR              0x31D5
#تعریف_کړه EGL_PLATFORM_X11_SCREEN_KHR       0x31D6
#د_که_پای /* EGL_KHR_platform_x11 */

#که_نه_تعریف_شوی EGL_KHR_reusable_sync
#تعریف_کړه EGL_KHR_reusable_sync 1
#که_تعریف_شوی KHRONOS_SUPPORT_INT64
#تعریف_کړه EGL_SYNC_حالت_KHR               0x30F1
#تعریف_کړه EGL_SIGNALED_KHR                  0x30F2
#تعریف_کړه EGL_UNSIGNALED_KHR                0x30F3
#تعریف_کړه EGL_TIMEOUT_EXPIRED_KHR           0x30F5
#تعریف_کړه EGL_CONDITION_SATISFIED_KHR       0x30F6
#تعریف_کړه EGL_SYNC_TYPE_KHR                 0x30F7
#تعریف_کړه EGL_SYNC_REUSABLE_KHR             0x30FA
#تعریف_کړه EGL_SYNC_FLUSH_COMMANDS_بټ_KHR   0x0001
#تعریف_کړه EGL_FOREVER_KHR                   0xFFFFFFFFFFFFFFFFull
#تعریف_کړه EGL_NO_SYNC_KHR                   EGL_CAST(EGLSyncKHR,0)
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSIGNALSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLenum ډېرپېښ);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglSignalSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLenum ډېرپېښ);
#د_که_پای
#د_که_پای /* KHRONOS_SUPPORT_INT64 */
#د_که_پای /* EGL_KHR_reusable_sync */

#که_نه_تعریف_شوی EGL_KHR_بهیر
#تعریف_کړه EGL_KHR_بهیر 1
تعريفنوع فراغ *EGLStreamKHR;
تعريفنوع khronos_uint64_t EGLuint64KHR;
#که_تعریف_شوی KHRONOS_SUPPORT_INT64
#تعریف_کړه EGL_NO_بهیر_KHR                 EGL_CAST(EGLStreamKHR,0)
#تعریف_کړه EGL_مصرفوونکی_LATENCY_USEC_KHR     0x3210
#تعریف_کړه EGL_تولیدوونکی_چوکاټ_KHR            0x3212
#تعریف_کړه EGL_مصرفوونکی_چوکاټ_KHR            0x3213
#تعریف_کړه EGL_بهیر_STATE_KHR              0x3214
#تعریف_کړه EGL_بهیر_STATE_CREATED_KHR      0x3215
#تعریف_کړه EGL_بهیر_STATE_CONNECTING_KHR   0x3216
#تعریف_کړه EGL_بهیر_STATE_تشه_KHR        0x3217
#تعریف_کړه EGL_بهیر_STATE_NEW_چوکاټ_شته_KHR 0x3218
#تعریف_کړه EGL_بهیر_STATE_OLD_چوکاټ_شته_KHR 0x3219
#تعریف_کړه EGL_بهیر_STATE_DISCONNECTED_KHR 0x321A
#تعریف_کړه EGL_BAD_بهیر_KHR                0x321B
#تعریف_کړه EGL_BAD_STATE_KHR                 0x321C
تعريفنوع EGLStreamKHR (EGLAPIENTRYP PFNEGLCREATESTREAMKHRPROC) (EGLDisplay dpy, ثابت EGLint *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSTREAMKHRPROC) (EGLDisplay dpy, EGLStreamKHR بهیر);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR بهیر, EGLenum attribute, EGLint ارزښت);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMKHRPROC) (EGLDisplay dpy, EGLStreamKHR بهیر, EGLenum attribute, EGLint *ارزښت);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMU64KHRPROC) (EGLDisplay dpy, EGLStreamKHR بهیر, EGLenum attribute, EGLuint64KHR *ارزښت);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLStreamKHR EGLAPIENTRY egl_Create_بهیر_KHR (EGLDisplay dpy, ثابت EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY egl_Destroy_بهیر_KHR (EGLDisplay dpy, EGLStreamKHR بهیر);
EGLAPI EGLBoolean EGLAPIENTRY egl_بهیر_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR بهیر, EGLenum attribute, EGLint ارزښت);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_بهیر_KHR (EGLDisplay dpy, EGLStreamKHR بهیر, EGLenum attribute, EGLint *ارزښت);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryStreamu64KHR (EGLDisplay dpy, EGLStreamKHR بهیر, EGLenum attribute, EGLuint64KHR *ارزښت);
#د_که_پای
#د_که_پای /* KHRONOS_SUPPORT_INT64 */
#د_که_پای /* EGL_KHR_stream */

#که_نه_تعریف_شوی EGL_KHR_بهیر_attrib
#تعریف_کړه EGL_KHR_بهیر_attrib 1
#که_تعریف_شوی KHRONOS_SUPPORT_INT64
تعريفنوع EGLStreamKHR (EGLAPIENTRYP PFNEGLCREATESTREAMATTRIBKHRPROC) (EGLDisplay dpy, ثابت EGLAttrib *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSETSTREAMATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR بهیر, EGLenum attribute, EGLAttrib ارزښت);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR بهیر, EGLenum attribute, EGLAttrib *ارزښت);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERACQUIREATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR بهیر, ثابت EGLAttrib *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERRELEASEATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR بهیر, ثابت EGLAttrib *attrib_list);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLStreamKHR EGLAPIENTRY egl_Create_بهیر_Attrib_KHR (EGLDisplay dpy, ثابت EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY egl_سېټ_بهیر_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR بهیر, EGLenum attribute, EGLAttrib ارزښت);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_بهیر_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR بهیر, EGLenum attribute, EGLAttrib *ارزښت);
EGLAPI EGLBoolean EGLAPIENTRY egl_بهیر_مصرفوونکی_Acquire_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR بهیر, ثابت EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY egl_بهیر_مصرفوونکی_Release_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR بهیر, ثابت EGLAttrib *attrib_list);
#د_که_پای
#د_که_پای /* KHRONOS_SUPPORT_INT64 */
#د_که_پای /* EGL_KHR_stream_attrib */

#که_نه_تعریف_شوی EGL_KHR_بهیر_مصرفوونکی_gltexture
#تعریف_کړه EGL_KHR_بهیر_مصرفوونکی_gltexture 1
#که_تعریف_شوی EGL_KHR_بهیر
#تعریف_کړه EGL_مصرفوونکی_ACQUIRE_TIMEOUT_USEC_KHR 0x321E
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALKHRPROC) (EGLDisplay dpy, EGLStreamKHR بهیر);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERACQUIREKHRPROC) (EGLDisplay dpy, EGLStreamKHR بهیر);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERRELEASEKHRPROC) (EGLDisplay dpy, EGLStreamKHR بهیر);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_بهیر_مصرفوونکی_GLTexture_External_KHR (EGLDisplay dpy, EGLStreamKHR بهیر);
EGLAPI EGLBoolean EGLAPIENTRY egl_بهیر_مصرفوونکی_Acquire_KHR (EGLDisplay dpy, EGLStreamKHR بهیر);
EGLAPI EGLBoolean EGLAPIENTRY egl_بهیر_مصرفوونکی_Release_KHR (EGLDisplay dpy, EGLStreamKHR بهیر);
#د_که_پای
#د_که_پای /* EGL_KHR_stream */
#د_که_پای /* EGL_KHR_stream_consumer_gltexture */

#که_نه_تعریف_شوی EGL_KHR_بهیر_cross_process_fd
#تعریف_کړه EGL_KHR_بهیر_cross_process_fd 1
تعريفنوع صحيح EGLNativeFileDescriptorKHR;
#که_تعریف_شوی EGL_KHR_بهیر
#تعریف_کړه EGL_NO_FILE_DESCRIPTOR_KHR        EGL_CAST(EGLNativeFileDescriptorKHR,-1)
تعريفنوع EGLNativeFileDescriptorKHR (EGLAPIENTRYP PFNEGLGETSTREAMFILEDESCRIPTORKHRPROC) (EGLDisplay dpy, EGLStreamKHR بهیر);
تعريفنوع EGLStreamKHR (EGLAPIENTRYP PFNEGLCREATESTREAMFROMFILEDESCRIPTORKHRPROC) (EGLDisplay dpy, EGLNativeFileDescriptorKHR file_descriptor);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLNativeFileDescriptorKHR EGLAPIENTRY egl_Get_بهیر_File_Descriptor_KHR (EGLDisplay dpy, EGLStreamKHR بهیر);
EGLAPI EGLStreamKHR EGLAPIENTRY egl_Create_بهیر_From_File_Descriptor_KHR (EGLDisplay dpy, EGLNativeFileDescriptorKHR file_descriptor);
#د_که_پای
#د_که_پای /* EGL_KHR_stream */
#د_که_پای /* EGL_KHR_stream_cross_process_fd */

#که_نه_تعریف_شوی EGL_KHR_بهیر_fifo
#تعریف_کړه EGL_KHR_بهیر_fifo 1
#که_تعریف_شوی EGL_KHR_بهیر
#تعریف_کړه EGL_بهیر_FIFO_اوږدتیا_KHR        0x31FC
#تعریف_کړه EGL_بهیر_وخت_NOW_KHR           0x31FD
#تعریف_کړه EGL_بهیر_وخت_مصرفوونکی_KHR      0x31FE
#تعریف_کړه EGL_بهیر_وخت_تولیدوونکی_KHR      0x31FF
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMTIMEKHRPROC) (EGLDisplay dpy, EGLStreamKHR بهیر, EGLenum attribute, EGLTimeKHR *ارزښت);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_بهیر_وخت_KHR (EGLDisplay dpy, EGLStreamKHR بهیر, EGLenum attribute, EGLTimeKHR *ارزښت);
#د_که_پای
#د_که_پای /* EGL_KHR_stream */
#د_که_پای /* EGL_KHR_stream_fifo */

#که_نه_تعریف_شوی EGL_KHR_بهیر_تولیدوونکی_aldatalocator
#تعریف_کړه EGL_KHR_بهیر_تولیدوونکی_aldatalocator 1
#که_تعریف_شوی EGL_KHR_بهیر
#د_که_پای /* EGL_KHR_stream */
#د_که_پای /* EGL_KHR_stream_producer_aldatalocator */

#که_نه_تعریف_شوی EGL_KHR_بهیر_تولیدوونکی_eglsurface
#تعریف_کړه EGL_KHR_بهیر_تولیدوونکی_eglsurface 1
#که_تعریف_شوی EGL_KHR_بهیر
#تعریف_کړه EGL_بهیر_بټ_KHR                0x0800
تعريفنوع EGLSurface (EGLAPIENTRYP PFNEGLCREATESTREAMPRODUCERSURFACEKHRPROC) (EGLDisplay dpy, EGLConfig config, EGLStreamKHR بهیر, ثابت EGLint *attrib_list);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSurface EGLAPIENTRY egl_Create_بهیر_تولیدوونکی_Surface_KHR (EGLDisplay dpy, EGLConfig config, EGLStreamKHR بهیر, ثابت EGLint *attrib_list);
#د_که_پای
#د_که_پای /* EGL_KHR_stream */
#د_که_پای /* EGL_KHR_stream_producer_eglsurface */

#که_نه_تعریف_شوی EGL_KHR_surfaceless_context
#تعریف_کړه EGL_KHR_surfaceless_context 1
#د_که_پای /* EGL_KHR_surfaceless_context */

#که_نه_تعریف_شوی EGL_KHR_بدلون_buffers_with_damage
#تعریف_کړه EGL_KHR_بدلون_buffers_with_damage 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSWITHDAMAGEKHRPROC) (EGLDisplay dpy, EGLSurface surface, ثابت EGLint *rects, EGLint n_rects);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_بدلون_Buffers_With_Damage_KHR (EGLDisplay dpy, EGLSurface surface, ثابت EGLint *rects, EGLint n_rects);
#د_که_پای
#د_که_پای /* EGL_KHR_swap_buffers_with_damage */

#که_نه_تعریف_شوی EGL_KHR_vg_پلار_image
#تعریف_کړه EGL_KHR_vg_پلار_image 1
#تعریف_کړه EGL_VG_پلار_IMAGE_KHR           0x30BA
#د_که_پای /* EGL_KHR_vg_parent_image */

#که_نه_تعریف_شوی EGL_KHR_wait_sync
#تعریف_کړه EGL_KHR_wait_sync 1
تعريفنوع EGLint (EGLAPIENTRYP PFNEGLWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLint EGLAPIENTRY eglWaitSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
#د_که_پای
#د_که_پای /* EGL_KHR_wait_sync */

#که_نه_تعریف_شوی EGL_ANDROID_GLES_layers
#تعریف_کړه EGL_ANDROID_GLES_layers 1
#د_که_پای /* EGL_ANDROID_GLES_layers */

#که_نه_تعریف_شوی EGL_ANDROID_blob_cache
#تعریف_کړه EGL_ANDROID_blob_cache 1
تعريفنوع khronos_ssize_t EGLsizeiANDROID;
تعريفنوع فراغ (*EGLSetBlobFuncANDROID) (ثابت فراغ *کلی, EGLsizeiANDROID کلی_اندازه_2, ثابت فراغ *ارزښت, EGLsizeiANDROID ارزښت_اندازه_2);
تعريفنوع EGLsizeiANDROID (*EGLGetBlobFuncANDROID) (ثابت فراغ *کلی, EGLsizeiANDROID کلی_اندازه_2, فراغ *ارزښت, EGLsizeiANDROID ارزښت_اندازه_2);
تعريفنوع فراغ (EGLAPIENTRYP PFNEGLSETBLOBCACHEFUNCSANDROIDPROC) (EGLDisplay dpy, EGLSetBlobFuncANDROID سېټ, EGLGetBlobFuncANDROID get);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI فراغ EGLAPIENTRY egl_سېټ_Blob_Cache_Funcs_ANDROID (EGLDisplay dpy, EGLSetBlobFuncANDROID سېټ, EGLGetBlobFuncANDROID get);
#د_که_پای
#د_که_پای /* EGL_ANDROID_blob_cache */

#که_نه_تعریف_شوی EGL_ANDROID_create_native_client_بفر
#تعریف_کړه EGL_ANDROID_create_native_client_بفر 1
#تعریف_کړه EGL_NATIVE_بفر_USAGE_ANDROID   0x3143
#تعریف_کړه EGL_NATIVE_بفر_USAGE_PROTECTED_بټ_ANDROID 0x00000001
#تعریف_کړه EGL_NATIVE_بفر_USAGE_RENDERBUFFER_بټ_ANDROID 0x00000002
#تعریف_کړه EGL_NATIVE_بفر_USAGE_TEXTURE_بټ_ANDROID 0x00000004
تعريفنوع EGLClient_بفر (EGLAPIENTRYP PFNEGLCREATENATIVECLIENTBUFFERANDROIDPROC) (ثابت EGLint *attrib_list);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLClient_بفر EGLAPIENTRY egl_Create_Native_Client_بفر_ANDROID (ثابت EGLint *attrib_list);
#د_که_پای
#د_که_پای /* EGL_ANDROID_create_native_client_buffer */

#که_نه_تعریف_شوی EGL_ANDROID_framebuffer_موخه
#تعریف_کړه EGL_ANDROID_framebuffer_موخه 1
#تعریف_کړه EGL_FRAMEBUFFER_موخه_ANDROID    0x3147
#د_که_پای /* EGL_ANDROID_framebuffer_target */

#که_نه_تعریف_شوی EGL_ANDROID_front_بفر_auto_refresh
#تعریف_کړه EGL_ANDROID_front_بفر_auto_refresh 1
#تعریف_کړه EGL_FRONT_بفر_AUTO_REFRESH_ANDROID 0x314C
#د_که_پای /* EGL_ANDROID_front_buffer_auto_refresh */

#که_نه_تعریف_شوی EGL_ANDROID_get_چوکاټ_timestamps
#تعریف_کړه EGL_ANDROID_get_چوکاټ_timestamps 1
تعريفنوع khronos_stime_nanoseconds_t EGLnsecsANDROID;
#تعریف_کړه EGL_TIMESTAMP_PENDING_ANDROID     EGL_CAST(EGLnsecsANDROID,-2)
#تعریف_کړه EGL_TIMESTAMP_INVALID_ANDROID     EGL_CAST(EGLnsecsANDROID,-1)
#تعریف_کړه EGL_TIMESTAMPS_ANDROID            0x3430
#تعریف_کړه EGL_مرکب_DEADLINE_ANDROID    0x3431
#تعریف_کړه EGL_مرکب_INTERVAL_ANDROID    0x3432
#تعریف_کړه EGL_مرکب_منزل_PRESENT_LATENCY_ANDROID 0x3433
#تعریف_کړه EGL_REQUESTED_PRESENT_وخت_ANDROID 0x3434
#تعریف_کړه EGL_RENDERING_COMPLETE_وخت_ANDROID 0x3435
#تعریف_کړه EGL_COMPOSITION_LATCH_وخت_ANDROID 0x3436
#تعریف_کړه EGL_لومړی_COMPOSITION_پیل_وخت_ANDROID 0x3437
#تعریف_کړه EGL_وروستی_COMPOSITION_پیل_وخت_ANDROID 0x3438
#تعریف_کړه EGL_لومړی_COMPOSITION_GPU_پای_ته_رسېدلی_وخت_ANDROID 0x3439
#تعریف_کړه EGL_DISPLAY_PRESENT_وخت_ANDROID  0x343A
#تعریف_کړه EGL_له_کتار_ایستل_READY_وخت_ANDROID    0x343B
#تعریف_کړه EGL_READS_بشپړ_وخت_ANDROID       0x343C
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETCOMPOSITORTIMINGSUPPORTEDANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLint name);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETCOMPOSITORTIMINGANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLint عدد_Timestamps,  ثابت EGLint *نومونه, EGLnsecsANDROID *ارزښتونه);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETNEXTFRAMEIDANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR *چوکاټ_Id);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETFRAMETIMESTAMPSUPPORTEDANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLint timestamp);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETFRAMETIMESTAMPSANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR چوکاټ_Id, EGLint عدد_Timestamps,  ثابت EGLint *timestamps, EGLnsecsANDROID *ارزښتونه);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglGetCompositorTimingSupportedANDROID (EGLDisplay dpy, EGLSurface surface, EGLint name);
EGLAPI EGLBoolean EGLAPIENTRY eglGetCompositorTimingANDROID (EGLDisplay dpy, EGLSurface surface, EGLint عدد_Timestamps,  ثابت EGLint *نومونه, EGLnsecsANDROID *ارزښتونه);
EGLAPI EGLBoolean EGLAPIENTRY egl_Get_بل_چوکاټ_Id_ANDROID (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR *چوکاټ_Id);
EGLAPI EGLBoolean EGLAPIENTRY egl_Get_چوکاټ_Timestamp_Supported_ANDROID (EGLDisplay dpy, EGLSurface surface, EGLint timestamp);
EGLAPI EGLBoolean EGLAPIENTRY egl_Get_چوکاټ_Timestamps_ANDROID (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR چوکاټ_Id, EGLint عدد_Timestamps,  ثابت EGLint *timestamps, EGLnsecsANDROID *ارزښتونه);
#د_که_پای
#د_که_پای /* EGL_ANDROID_get_frame_timestamps */

#که_نه_تعریف_شوی EGL_ANDROID_get_native_client_بفر
#تعریف_کړه EGL_ANDROID_get_native_client_بفر 1
بنية AHardware_بفر;
تعريفنوع EGLClient_بفر (EGLAPIENTRYP PFNEGLGETNATIVECLIENTBUFFERANDROIDPROC) (ثابت بنية AHardware_بفر *بفر_2);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLClient_بفر EGLAPIENTRY egl_Get_Native_Client_بفر_ANDROID (ثابت بنية AHardware_بفر *بفر_2);
#د_که_پای
#د_که_پای /* EGL_ANDROID_get_native_client_buffer */

#که_نه_تعریف_شوی EGL_ANDROID_image_native_بفر
#تعریف_کړه EGL_ANDROID_image_native_بفر 1
#تعریف_کړه EGL_NATIVE_بفر_ANDROID         0x3140
#د_که_پای /* EGL_ANDROID_image_native_buffer */

#که_نه_تعریف_شوی EGL_ANDROID_native_fence_sync
#تعریف_کړه EGL_ANDROID_native_fence_sync 1
#تعریف_کړه EGL_SYNC_NATIVE_FENCE_ANDROID     0x3144
#تعریف_کړه EGL_SYNC_NATIVE_FENCE_FD_ANDROID  0x3145
#تعریف_کړه EGL_SYNC_NATIVE_FENCE_SIGNALED_ANDROID 0x3146
#تعریف_کړه EGL_NO_NATIVE_FENCE_FD_ANDROID    -1
تعريفنوع EGLint (EGLAPIENTRYP PFNEGLDUPNATIVEFENCEFDANDROIDPROC) (EGLDisplay dpy, EGLSyncKHR sync);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLint EGLAPIENTRY eglDupNativeFenceFDANDROID (EGLDisplay dpy, EGLSyncKHR sync);
#د_که_پای
#د_که_پای /* EGL_ANDROID_native_fence_sync */

#که_نه_تعریف_شوی EGL_ANDROID_presentation_وخت
#تعریف_کړه EGL_ANDROID_presentation_وخت 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLPRESENTATIONTIMEANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLnsecsANDROID وخت);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Presentation_وخت_ANDROID (EGLDisplay dpy, EGLSurface surface, EGLnsecsANDROID وخت);
#د_که_پای
#د_که_پای /* EGL_ANDROID_presentation_time */

#که_نه_تعریف_شوی EGL_ANDROID_recordable
#تعریف_کړه EGL_ANDROID_recordable 1
#تعریف_کړه EGL_RECORDABLE_ANDROID            0x3142
#د_که_پای /* EGL_ANDROID_recordable */

#که_نه_تعریف_شوی EGL_ANDROID_telemetry_hint
#تعریف_کړه EGL_ANDROID_telemetry_hint 1
#تعریف_کړه EGL_TELEMETRY_HINT_ANDROID        0x3570
#د_که_پای /* EGL_ANDROID_telemetry_hint */

#که_نه_تعریف_شوی EGL_ANGLE_d3d_share_handle_client_بفر
#تعریف_کړه EGL_ANGLE_d3d_share_handle_client_بفر 1
#تعریف_کړه EGL_D3D_TEXTURE_2D_SHARE_HANDLE_ANGLE 0x3200
#د_که_پای /* EGL_ANGLE_d3d_share_handle_client_buffer */

#که_نه_تعریف_شوی EGL_ANGLE_device_d3d
#تعریف_کړه EGL_ANGLE_device_d3d 1
#تعریف_کړه EGL_D3D9_DEVICE_ANGLE             0x33A0
#تعریف_کړه EGL_D3D11_DEVICE_ANGLE            0x33A1
#د_که_پای /* EGL_ANGLE_device_d3d */

#که_نه_تعریف_شوی EGL_ANGLE_query_surface_اشاره_ګر
#تعریف_کړه EGL_ANGLE_query_surface_اشاره_ګر 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSURFACEPOINTERANGLEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint attribute, فراغ **ارزښت);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Surface_اشاره_ګر_ANGLE (EGLDisplay dpy, EGLSurface surface, EGLint attribute, فراغ **ارزښت);
#د_که_پای
#د_که_پای /* EGL_ANGLE_query_surface_pointer */

#که_نه_تعریف_شوی EGL_ANGLE_surface_d3d_texture_2d_share_handle
#تعریف_کړه EGL_ANGLE_surface_d3d_texture_2d_share_handle 1
#د_که_پای /* EGL_ANGLE_surface_d3d_texture_2d_share_handle */

#که_نه_تعریف_شوی EGL_ANGLE_sync_control_شرح
#تعریف_کړه EGL_ANGLE_sync_control_شرح 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETMSCRATEANGLEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint *numerator, EGLint *denominator);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Get_Msc_شرح_ANGLE (EGLDisplay dpy, EGLSurface surface, EGLint *numerator, EGLint *denominator);
#د_که_پای
#د_که_پای /* EGL_ANGLE_sync_control_rate */

#که_نه_تعریف_شوی EGL_ANGLE_کړکۍ_fixed_اندازه
#تعریف_کړه EGL_ANGLE_کړکۍ_fixed_اندازه 1
#تعریف_کړه EGL_FIXED_اندازه_ANGLE              0x3201
#د_که_پای /* EGL_ANGLE_window_fixed_size */

#که_نه_تعریف_شوی EGL_ARM_image_format
#تعریف_کړه EGL_ARM_image_format 1
#تعریف_کړه EGL_COLOR_COMPONENT_TYPE_UNSIGNED_INTEGER_ARM 0x3287
#تعریف_کړه EGL_COLOR_COMPONENT_TYPE_INTEGER_ARM 0x3288
#د_که_پای /* EGL_ARM_image_format */

#که_نه_تعریف_شوی EGL_ARM_implicit_external_sync
#تعریف_کړه EGL_ARM_implicit_external_sync 1
#تعریف_کړه EGL_SYNC_مخکینی_COMMANDS_IMPLICIT_EXTERNAL_ARM 0x328A
#د_که_پای /* EGL_ARM_implicit_external_sync */

#که_نه_تعریف_شوی EGL_ARM_pixmap_multisample_discard
#تعریف_کړه EGL_ARM_pixmap_multisample_discard 1
#تعریف_کړه EGL_DISCARD_SAMPLES_ARM           0x3286
#د_که_پای /* EGL_ARM_pixmap_multisample_discard */

#که_نه_تعریف_شوی EGL_EXT_bind_منزل_front
#تعریف_کړه EGL_EXT_bind_منزل_front 1
#تعریف_کړه EGL_FRONT_بفر_EXT              0x3464
#د_که_پای /* EGL_EXT_bind_to_front */

#که_نه_تعریف_شوی EGL_EXT_بفر_age
#تعریف_کړه EGL_EXT_بفر_age 1
#تعریف_کړه EGL_بفر_AGE_EXT                0x313D
#د_که_پای /* EGL_EXT_buffer_age */

#که_نه_تعریف_شوی EGL_EXT_client_extensions
#تعریف_کړه EGL_EXT_client_extensions 1
#د_که_پای /* EGL_EXT_client_extensions */

#که_نه_تعریف_شوی EGL_EXT_client_sync
#تعریف_کړه EGL_EXT_client_sync 1
#تعریف_کړه EGL_SYNC_CLIENT_EXT               0x3364
#تعریف_کړه EGL_SYNC_CLIENT_SIGNAL_EXT        0x3365
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLCLIENTSIGNALSYNCEXTPROC) (EGLDisplay dpy, EGLSync sync, ثابت EGLAttrib *attrib_list);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglClientSignalSyncEXT (EGLDisplay dpy, EGLSync sync, ثابت EGLAttrib *attrib_list);
#د_که_پای
#د_که_پای /* EGL_EXT_client_sync */

#که_نه_تعریف_شوی EGL_EXT_compositor
#تعریف_کړه EGL_EXT_compositor 1
#تعریف_کړه EGL_PRIMARY_COMPOSITOR_CONTEXT_EXT 0x3460
#تعریف_کړه EGL_EXTERNAL_REF_ID_EXT           0x3461
#تعریف_کړه EGL_COMPOSITOR_DROP_NEWEST_چوکاټ_EXT 0x3462
#تعریف_کړه EGL_COMPOSITOR_KEEP_NEWEST_چوکاټ_EXT 0x3463
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETCONTEXTLISTEXTPROC) (ثابت EGLint *external_ref_ids, EGLint عدد_entries);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETCONTEXTATTRIBUTESEXTPROC) (EGLint external_ref_id, ثابت EGLint *context_ځانګړتیاوې, EGLint عدد_entries);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETWINDOWLISTEXTPROC) (EGLint external_ref_id, ثابت EGLint *external_win_ids, EGLint عدد_entries);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETWINDOWATTRIBUTESEXTPROC) (EGLint external_win_id, ثابت EGLint *کړکۍ_ځانګړتیاوې, EGLint عدد_entries);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORBINDTEXWINDOWEXTPROC) (EGLint external_win_id);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETSIZEEXTPROC) (EGLint external_win_id, EGLint پلنوالی, EGLint لوړوالی);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSWAPPOLICYEXTPROC) (EGLint external_win_id, EGLint policy);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_سېټ_Context_List_EXT (ثابت EGLint *external_ref_ids, EGLint عدد_entries);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_سېټ_Context_ځانګړتیاوې_EXT (EGLint external_ref_id, ثابت EGLint *context_ځانګړتیاوې, EGLint عدد_entries);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_سېټ_کړکۍ_List_EXT (EGLint external_ref_id, ثابت EGLint *external_win_ids, EGLint عدد_entries);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_سېټ_کړکۍ_ځانګړتیاوې_EXT (EGLint external_win_id, ثابت EGLint *کړکۍ_ځانګړتیاوې, EGLint عدد_entries);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_Bind_Tex_کړکۍ_EXT (EGLint external_win_id);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_سېټ_اندازه_EXT (EGLint external_win_id, EGLint پلنوالی, EGLint لوړوالی);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_بدلون_Policy_EXT (EGLint external_win_id, EGLint policy);
#د_که_پای
#د_که_پای /* EGL_EXT_compositor */

#که_نه_تعریف_شوی EGL_EXT_config_select_ډله
#تعریف_کړه EGL_EXT_config_select_ډله 1
#تعریف_کړه EGL_CONFIG_SELECT_ډله_EXT       0x34C0
#د_که_پای /* EGL_EXT_config_select_group */

#که_نه_تعریف_شوی EGL_EXT_create_context_robustness
#تعریف_کړه EGL_EXT_create_context_robustness 1
#تعریف_کړه EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT 0x30BF
#تعریف_کړه EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_EXT 0x3138
#تعریف_کړه EGL_NO_RESET_NOTIFICATION_EXT     0x31BE
#تعریف_کړه EGL_LOSE_CONTEXT_ON_RESET_EXT     0x31BF
#د_که_پای /* EGL_EXT_create_context_robustness */

#که_نه_تعریف_شوی EGL_EXT_device_بنسټ
#تعریف_کړه EGL_EXT_device_بنسټ 1
تعريفنوع فراغ *EGLDeviceEXT;
#تعریف_کړه EGL_NO_DEVICE_EXT                 EGL_CAST(EGLDeviceEXT,0)
#تعریف_کړه EGL_BAD_DEVICE_EXT                0x322B
#تعریف_کړه EGL_DEVICE_EXT                    0x322C
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICEATTRIBEXTPROC) (EGLDeviceEXT device, EGLint attribute, EGLAttrib *ارزښت);
تعريفنوع ثابت حرف *(EGLAPIENTRYP PFNEGLQUERYDEVICESTRINGEXTPROC) (EGLDeviceEXT device, EGLint name);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICESEXTPROC) (EGLint max_devices, EGLDeviceEXT *devices, EGLint *عدد_devices);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDISPLAYATTRIBEXTPROC) (EGLDisplay dpy, EGLint attribute, EGLAttrib *ارزښت);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDeviceAttribEXT (EGLDeviceEXT device, EGLint attribute, EGLAttrib *ارزښت);
EGLAPI ثابت حرف *EGLAPIENTRY eglQueryDeviceStringEXT (EGLDeviceEXT device, EGLint name);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDevicesEXT (EGLint max_devices, EGLDeviceEXT *devices, EGLint *عدد_devices);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDisplayAttribEXT (EGLDisplay dpy, EGLint attribute, EGLAttrib *ارزښت);
#د_که_پای
#د_که_پای /* EGL_EXT_device_base */

#که_نه_تعریف_شوی EGL_EXT_device_drm
#تعریف_کړه EGL_EXT_device_drm 1
#تعریف_کړه EGL_DRM_DEVICE_FILE_EXT           0x3233
#تعریف_کړه EGL_DRM_MASTER_FD_EXT             0x333C
#د_که_پای /* EGL_EXT_device_drm */

#که_نه_تعریف_شوی EGL_EXT_device_drm_render_غوټه
#تعریف_کړه EGL_EXT_device_drm_render_غوټه 1
#تعریف_کړه EGL_DRM_RENDER_غوټه_FILE_EXT      0x3377
#د_که_پای /* EGL_EXT_device_drm_render_node */

#که_نه_تعریف_شوی EGL_EXT_device_enumeration
#تعریف_کړه EGL_EXT_device_enumeration 1
#د_که_پای /* EGL_EXT_device_enumeration */

#که_نه_تعریف_شوی EGL_EXT_device_openwf
#تعریف_کړه EGL_EXT_device_openwf 1
#تعریف_کړه EGL_OPENWF_DEVICE_ID_EXT          0x3237
#تعریف_کړه EGL_OPENWF_DEVICE_EXT             0x333D
#د_که_پای /* EGL_EXT_device_openwf */

#که_نه_تعریف_شوی EGL_EXT_device_persistent_id
#تعریف_کړه EGL_EXT_device_persistent_id 1
#تعریف_کړه EGL_DEVICE_UUID_EXT               0x335C
#تعریف_کړه EGL_DRIVER_UUID_EXT               0x335D
#تعریف_کړه EGL_DRIVER_NAME_EXT               0x335E
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICEBINARYEXTPROC) (EGLDeviceEXT device, EGLint name, EGLint max_اندازه, فراغ *ارزښت, EGLint *اندازه);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Device_دوګونی_EXT (EGLDeviceEXT device, EGLint name, EGLint max_اندازه, فراغ *ارزښت, EGLint *اندازه);
#د_که_پای
#د_که_پای /* EGL_EXT_device_persistent_id */

#که_نه_تعریف_شوی EGL_EXT_device_query
#تعریف_کړه EGL_EXT_device_query 1
#د_که_پای /* EGL_EXT_device_query */

#که_نه_تعریف_شوی EGL_EXT_device_query_name
#تعریف_کړه EGL_EXT_device_query_name 1
#تعریف_کړه EGL_RENDERER_EXT                  0x335F
#د_که_پای /* EGL_EXT_device_query_name */

#که_نه_تعریف_شوی EGL_EXT_device_type
#تعریف_کړه EGL_EXT_device_type 1
#تعریف_کړه EGL_DEVICE_TYPE_EXT               0x3590
#تعریف_کړه EGL_DEVICE_TYPE_OTHER_EXT         0x3591
#تعریف_کړه EGL_DEVICE_TYPE_INTEGRATED_GPU_EXT 0x3592
#تعریف_کړه EGL_DEVICE_TYPE_DISCRETE_GPU_EXT  0x3593
#تعریف_کړه EGL_DEVICE_TYPE_CPU_EXT           0x3594
#د_که_پای /* EGL_EXT_device_type */

#که_نه_تعریف_شوی EGL_EXT_display_alloc
#تعریف_کړه EGL_EXT_display_alloc 1
#تعریف_کړه EGL_ALLOC_NEW_DISPLAY_EXT         0x3379
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYDISPLAYEXTPROC) (EGLDisplay dpy);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyDisplayEXT (EGLDisplay dpy);
#د_که_پای
#د_که_پای /* EGL_EXT_display_alloc */

#که_نه_تعریف_شوی EGL_EXT_explicit_device
#تعریف_کړه EGL_EXT_explicit_device 1
#د_که_پای /* EGL_EXT_explicit_device */

#که_نه_تعریف_شوی EGL_EXT_gl_colorspace_bt2020_hlg
#تعریف_کړه EGL_EXT_gl_colorspace_bt2020_hlg 1
#تعریف_کړه EGL_GL_COLORSPACE_BT2020_HLG_EXT  0x3540
#د_که_پای /* EGL_EXT_gl_colorspace_bt2020_hlg */

#که_نه_تعریف_شوی EGL_EXT_gl_colorspace_bt2020_خطي
#تعریف_کړه EGL_EXT_gl_colorspace_bt2020_خطي 1
#تعریف_کړه EGL_GL_COLORSPACE_BT2020_خطي_EXT 0x333F
#د_که_پای /* EGL_EXT_gl_colorspace_bt2020_linear */

#که_نه_تعریف_شوی EGL_EXT_gl_colorspace_bt2020_pq
#تعریف_کړه EGL_EXT_gl_colorspace_bt2020_pq 1
#تعریف_کړه EGL_GL_COLORSPACE_BT2020_PQ_EXT   0x3340
#د_که_پای /* EGL_EXT_gl_colorspace_bt2020_pq */

#که_نه_تعریف_شوی EGL_EXT_gl_colorspace_display_p3
#تعریف_کړه EGL_EXT_gl_colorspace_display_p3 1
#تعریف_کړه EGL_GL_COLORSPACE_DISPLAY_P3_EXT  0x3363
#د_که_پای /* EGL_EXT_gl_colorspace_display_p3 */

#که_نه_تعریف_شوی EGL_EXT_gl_colorspace_display_p3_خطي
#تعریف_کړه EGL_EXT_gl_colorspace_display_p3_خطي 1
#تعریف_کړه EGL_GL_COLORSPACE_DISPLAY_P3_خطي_EXT 0x3362
#د_که_پای /* EGL_EXT_gl_colorspace_display_p3_linear */

#که_نه_تعریف_شوی EGL_EXT_gl_colorspace_display_p3_passthrough
#تعریف_کړه EGL_EXT_gl_colorspace_display_p3_passthrough 1
#تعریف_کړه EGL_GL_COLORSPACE_DISPLAY_P3_PASSTHROUGH_EXT 0x3490
#د_که_پای /* EGL_EXT_gl_colorspace_display_p3_passthrough */

#که_نه_تعریف_شوی EGL_EXT_gl_colorspace_scrgb
#تعریف_کړه EGL_EXT_gl_colorspace_scrgb 1
#تعریف_کړه EGL_GL_COLORSPACE_SCRGB_EXT       0x3351
#د_که_پای /* EGL_EXT_gl_colorspace_scrgb */

#که_نه_تعریف_شوی EGL_EXT_gl_colorspace_scrgb_خطي
#تعریف_کړه EGL_EXT_gl_colorspace_scrgb_خطي 1
#تعریف_کړه EGL_GL_COLORSPACE_SCRGB_خطي_EXT 0x3350
#د_که_پای /* EGL_EXT_gl_colorspace_scrgb_linear */

#که_نه_تعریف_شوی EGL_EXT_image_dma_buf_import
#تعریف_کړه EGL_EXT_image_dma_buf_import 1
#تعریف_کړه EGL_LINUX_DMA_BUF_EXT             0x3270
#تعریف_کړه EGL_LINUX_DRM_FOURCC_EXT          0x3271
#تعریف_کړه EGL_DMA_BUF_PLANE0_FD_EXT         0x3272
#تعریف_کړه EGL_DMA_BUF_PLANE0_دننه_واټن_EXT     0x3273
#تعریف_کړه EGL_DMA_BUF_PLANE0_PITCH_EXT      0x3274
#تعریف_کړه EGL_DMA_BUF_PLANE1_FD_EXT         0x3275
#تعریف_کړه EGL_DMA_BUF_PLANE1_دننه_واټن_EXT     0x3276
#تعریف_کړه EGL_DMA_BUF_PLANE1_PITCH_EXT      0x3277
#تعریف_کړه EGL_DMA_BUF_PLANE2_FD_EXT         0x3278
#تعریف_کړه EGL_DMA_BUF_PLANE2_دننه_واټن_EXT     0x3279
#تعریف_کړه EGL_DMA_BUF_PLANE2_PITCH_EXT      0x327A
#تعریف_کړه EGL_YUV_COLOR_SPACE_HINT_EXT      0x327B
#تعریف_کړه EGL_SAMPLE_RANGE_HINT_EXT         0x327C
#تعریف_کړه EGL_YUV_CHROMA_HORIZONTAL_SITING_HINT_EXT 0x327D
#تعریف_کړه EGL_YUV_CHROMA_VERTICAL_SITING_HINT_EXT 0x327E
#تعریف_کړه EGL_ITU_REC601_EXT                0x327F
#تعریف_کړه EGL_ITU_REC709_EXT                0x3280
#تعریف_کړه EGL_ITU_REC2020_EXT               0x3281
#تعریف_کړه EGL_YUV_ډک_RANGE_EXT            0x3282
#تعریف_کړه EGL_YUV_NARROW_RANGE_EXT          0x3283
#تعریف_کړه EGL_YUV_CHROMA_SITING_0_EXT       0x3284
#تعریف_کړه EGL_YUV_CHROMA_SITING_0_5_EXT     0x3285
#د_که_پای /* EGL_EXT_image_dma_buf_import */

#که_نه_تعریف_شوی EGL_EXT_image_dma_buf_import_modifiers
#تعریف_کړه EGL_EXT_image_dma_buf_import_modifiers 1
#تعریف_کړه EGL_DMA_BUF_PLANE3_FD_EXT         0x3440
#تعریف_کړه EGL_DMA_BUF_PLANE3_دننه_واټن_EXT     0x3441
#تعریف_کړه EGL_DMA_BUF_PLANE3_PITCH_EXT      0x3442
#تعریف_کړه EGL_DMA_BUF_PLANE0_MODIFIER_LO_EXT 0x3443
#تعریف_کړه EGL_DMA_BUF_PLANE0_MODIFIER_HI_EXT 0x3444
#تعریف_کړه EGL_DMA_BUF_PLANE1_MODIFIER_LO_EXT 0x3445
#تعریف_کړه EGL_DMA_BUF_PLANE1_MODIFIER_HI_EXT 0x3446
#تعریف_کړه EGL_DMA_BUF_PLANE2_MODIFIER_LO_EXT 0x3447
#تعریف_کړه EGL_DMA_BUF_PLANE2_MODIFIER_HI_EXT 0x3448
#تعریف_کړه EGL_DMA_BUF_PLANE3_MODIFIER_LO_EXT 0x3449
#تعریف_کړه EGL_DMA_BUF_PLANE3_MODIFIER_HI_EXT 0x344A
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDMABUFFORMATSEXTPROC) (EGLDisplay dpy, EGLint max_formats, EGLint *formats, EGLint *عدد_formats);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDMABUFMODIFIERSEXTPROC) (EGLDisplay dpy, EGLint format, EGLint max_modifiers, EGLuint64KHR *modifiers, EGLBoolean *external_only, EGLint *عدد_modifiers);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDmaBufFormatsEXT (EGLDisplay dpy, EGLint max_formats, EGLint *formats, EGLint *عدد_formats);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDmaBufModifiersEXT (EGLDisplay dpy, EGLint format, EGLint max_modifiers, EGLuint64KHR *modifiers, EGLBoolean *external_only, EGLint *عدد_modifiers);
#د_که_پای
#د_که_پای /* EGL_EXT_image_dma_buf_import_modifiers */

#که_نه_تعریف_شوی EGL_EXT_image_gl_colorspace
#تعریف_کړه EGL_EXT_image_gl_colorspace 1
#تعریف_کړه EGL_GL_COLORSPACE_DEFAULT_EXT     0x314D
#د_که_پای /* EGL_EXT_image_gl_colorspace */

#که_نه_تعریف_شوی EGL_EXT_image_implicit_sync_control
#تعریف_کړه EGL_EXT_image_implicit_sync_control 1
#تعریف_کړه EGL_IMPORT_SYNC_TYPE_EXT          0x3470
#تعریف_کړه EGL_IMPORT_IMPLICIT_SYNC_EXT      0x3471
#تعریف_کړه EGL_IMPORT_EXPLICIT_SYNC_EXT      0x3472
#د_که_پای /* EGL_EXT_image_implicit_sync_control */

#که_نه_تعریف_شوی EGL_EXT_multiview_کړکۍ
#تعریف_کړه EGL_EXT_multiview_کړکۍ 1
#تعریف_کړه EGL_MULTIVIEW_VIEW_شمېر_EXT      0x3134
#د_که_پای /* EGL_EXT_multiview_window */

#که_نه_تعریف_شوی EGL_EXT_output_بنسټ
#تعریف_کړه EGL_EXT_output_بنسټ 1
تعريفنوع فراغ *EGLOutputLayerEXT;
تعريفنوع فراغ *EGLOutput_پورټ_EXT;
#تعریف_کړه EGL_NO_OUTPUT_LAYER_EXT           EGL_CAST(EGLOutputLayerEXT,0)
#تعریف_کړه EGL_NO_OUTPUT_پورټ_EXT            EGL_CAST(EGLOutput_پورټ_EXT,0)
#تعریف_کړه EGL_BAD_OUTPUT_LAYER_EXT          0x322D
#تعریف_کړه EGL_BAD_OUTPUT_پورټ_EXT           0x322E
#تعریف_کړه EGL_بدلون_INTERVAL_EXT             0x322F
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETOUTPUTLAYERSEXTPROC) (EGLDisplay dpy, ثابت EGLAttrib *attrib_list, EGLOutputLayerEXT *layers, EGLint max_layers, EGLint *عدد_layers);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETOUTPUTPORTSEXTPROC) (EGLDisplay dpy, ثابت EGLAttrib *attrib_list, EGLOutput_پورټ_EXT *ports, EGLint max_ports, EGLint *عدد_ports);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLOUTPUTLAYERATTRIBEXTPROC) (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib ارزښت);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYOUTPUTLAYERATTRIBEXTPROC) (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib *ارزښت);
تعريفنوع ثابت حرف *(EGLAPIENTRYP PFNEGLQUERYOUTPUTLAYERSTRINGEXTPROC) (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint name);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLOUTPUTPORTATTRIBEXTPROC) (EGLDisplay dpy, EGLOutput_پورټ_EXT پورټ, EGLint attribute, EGLAttrib ارزښت);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYOUTPUTPORTATTRIBEXTPROC) (EGLDisplay dpy, EGLOutput_پورټ_EXT پورټ, EGLint attribute, EGLAttrib *ارزښت);
تعريفنوع ثابت حرف *(EGLAPIENTRYP PFNEGLQUERYOUTPUTPORTSTRINGEXTPROC) (EGLDisplay dpy, EGLOutput_پورټ_EXT پورټ, EGLint name);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglGetOutputLayersEXT (EGLDisplay dpy, ثابت EGLAttrib *attrib_list, EGLOutputLayerEXT *layers, EGLint max_layers, EGLint *عدد_layers);
EGLAPI EGLBoolean EGLAPIENTRY eglGetOutputPortsEXT (EGLDisplay dpy, ثابت EGLAttrib *attrib_list, EGLOutput_پورټ_EXT *ports, EGLint max_ports, EGLint *عدد_ports);
EGLAPI EGLBoolean EGLAPIENTRY eglOutputLayerAttribEXT (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib ارزښت);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryOutputLayerAttribEXT (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib *ارزښت);
EGLAPI ثابت حرف *EGLAPIENTRY eglQueryOutputLayerStringEXT (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint name);
EGLAPI EGLBoolean EGLAPIENTRY egl_Output_پورټ_Attrib_EXT (EGLDisplay dpy, EGLOutput_پورټ_EXT پورټ, EGLint attribute, EGLAttrib ارزښت);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Output_پورټ_Attrib_EXT (EGLDisplay dpy, EGLOutput_پورټ_EXT پورټ, EGLint attribute, EGLAttrib *ارزښت);
EGLAPI ثابت حرف *EGLAPIENTRY egl_Query_Output_پورټ_String_EXT (EGLDisplay dpy, EGLOutput_پورټ_EXT پورټ, EGLint name);
#د_که_پای
#د_که_پای /* EGL_EXT_output_base */

#که_نه_تعریف_شوی EGL_EXT_output_drm
#تعریف_کړه EGL_EXT_output_drm 1
#تعریف_کړه EGL_DRM_CRTC_EXT                  0x3234
#تعریف_کړه EGL_DRM_PLANE_EXT                 0x3235
#تعریف_کړه EGL_DRM_CONNECTOR_EXT             0x3236
#د_که_پای /* EGL_EXT_output_drm */

#که_نه_تعریف_شوی EGL_EXT_output_openwf
#تعریف_کړه EGL_EXT_output_openwf 1
#تعریف_کړه EGL_OPENWF_PIPELINE_ID_EXT        0x3238
#تعریف_کړه EGL_OPENWF_پورټ_ID_EXT            0x3239
#د_که_پای /* EGL_EXT_output_openwf */

#که_نه_تعریف_شوی EGL_EXT_pixel_format_float
#تعریف_کړه EGL_EXT_pixel_format_float 1
#تعریف_کړه EGL_COLOR_COMPONENT_TYPE_EXT      0x3339
#تعریف_کړه EGL_COLOR_COMPONENT_TYPE_FIXED_EXT 0x333A
#تعریف_کړه EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT 0x333B
#د_که_پای /* EGL_EXT_pixel_format_float */

#که_نه_تعریف_شوی EGL_EXT_platform_بنسټ
#تعریف_کړه EGL_EXT_platform_بنسټ 1
تعريفنوع EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYEXTPROC) (EGLenum platform, فراغ *native_display, ثابت EGLint *attrib_list);
تعريفنوع EGLSurface (EGLAPIENTRYP PFNEGLCREATEPLATFORMWINDOWSURFACEEXTPROC) (EGLDisplay dpy, EGLConfig config, فراغ *native_کړکۍ, ثابت EGLint *attrib_list);
تعريفنوع EGLSurface (EGLAPIENTRYP PFNEGLCREATEPLATFORMPIXMAPSURFACEEXTPROC) (EGLDisplay dpy, EGLConfig config, فراغ *native_pixmap, ثابت EGLint *attrib_list);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLDisplay EGLAPIENTRY eglGetPlatformDisplayEXT (EGLenum platform, فراغ *native_display, ثابت EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY egl_Create_Platform_کړکۍ_Surface_EXT (EGLDisplay dpy, EGLConfig config, فراغ *native_کړکۍ, ثابت EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePlatformPixmapSurfaceEXT (EGLDisplay dpy, EGLConfig config, فراغ *native_pixmap, ثابت EGLint *attrib_list);
#د_که_پای
#د_که_پای /* EGL_EXT_platform_base */

#که_نه_تعریف_شوی EGL_EXT_platform_device
#تعریف_کړه EGL_EXT_platform_device 1
#تعریف_کړه EGL_PLATFORM_DEVICE_EXT           0x313F
#د_که_پای /* EGL_EXT_platform_device */

#که_نه_تعریف_شوی EGL_EXT_platform_wayland
#تعریف_کړه EGL_EXT_platform_wayland 1
#تعریف_کړه EGL_PLATFORM_WAYLAND_EXT          0x31D8
#د_که_پای /* EGL_EXT_platform_wayland */

#که_نه_تعریف_شوی EGL_EXT_platform_x11
#تعریف_کړه EGL_EXT_platform_x11 1
#تعریف_کړه EGL_PLATFORM_X11_EXT              0x31D5
#تعریف_کړه EGL_PLATFORM_X11_SCREEN_EXT       0x31D6
#د_که_پای /* EGL_EXT_platform_x11 */

#که_نه_تعریف_شوی EGL_EXT_platform_xcb
#تعریف_کړه EGL_EXT_platform_xcb 1
#تعریف_کړه EGL_PLATFORM_XCB_EXT              0x31DC
#تعریف_کړه EGL_PLATFORM_XCB_SCREEN_EXT       0x31DE
#د_که_پای /* EGL_EXT_platform_xcb */

#که_نه_تعریف_شوی EGL_EXT_present_opaque
#تعریف_کړه EGL_EXT_present_opaque 1
#تعریف_کړه EGL_PRESENT_OPAQUE_EXT            0x31DF
#د_که_پای /* EGL_EXT_present_opaque */

#که_نه_تعریف_شوی EGL_EXT_protected_content
#تعریف_کړه EGL_EXT_protected_content 1
#تعریف_کړه EGL_PROTECTED_CONTENT_EXT         0x32C0
#د_که_پای /* EGL_EXT_protected_content */

#که_نه_تعریف_شوی EGL_EXT_protected_surface
#تعریف_کړه EGL_EXT_protected_surface 1
#د_که_پای /* EGL_EXT_protected_surface */

#که_نه_تعریف_شوی EGL_EXT_query_reset_notification_strategy
#تعریف_کړه EGL_EXT_query_reset_notification_strategy 1
#د_که_پای /* EGL_EXT_query_reset_notification_strategy */

#که_نه_تعریف_شوی EGL_EXT_بهیر_مصرفوونکی_egloutput
#تعریف_کړه EGL_EXT_بهیر_مصرفوونکی_egloutput 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMEROUTPUTEXTPROC) (EGLDisplay dpy, EGLStreamKHR بهیر, EGLOutputLayerEXT layer);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_بهیر_مصرفوونکی_Output_EXT (EGLDisplay dpy, EGLStreamKHR بهیر, EGLOutputLayerEXT layer);
#د_که_پای
#د_که_پای /* EGL_EXT_stream_consumer_egloutput */

#که_نه_تعریف_شوی EGL_EXT_surface_CTA861_3_metadata
#تعریف_کړه EGL_EXT_surface_CTA861_3_metadata 1
#تعریف_کړه EGL_CTA861_3_MAX_CONTENT_LIGHT_LEVEL_EXT 0x3360
#تعریف_کړه EGL_CTA861_3_MAX_چوکاټ_اوسط_LEVEL_EXT 0x3361
#د_که_پای /* EGL_EXT_surface_CTA861_3_metadata */

#که_نه_تعریف_شوی EGL_EXT_surface_SMPTE2086_metadata
#تعریف_کړه EGL_EXT_surface_SMPTE2086_metadata 1
#تعریف_کړه EGL_SMPTE2086_DISPLAY_PRIMARY_RX_EXT 0x3341
#تعریف_کړه EGL_SMPTE2086_DISPLAY_PRIMARY_RY_EXT 0x3342
#تعریف_کړه EGL_SMPTE2086_DISPLAY_PRIMARY_GX_EXT 0x3343
#تعریف_کړه EGL_SMPTE2086_DISPLAY_PRIMARY_GY_EXT 0x3344
#تعریف_کړه EGL_SMPTE2086_DISPLAY_PRIMARY_BX_EXT 0x3345
#تعریف_کړه EGL_SMPTE2086_DISPLAY_PRIMARY_BY_EXT 0x3346
#تعریف_کړه EGL_SMPTE2086_WHITE_ټکی_X_EXT   0x3347
#تعریف_کړه EGL_SMPTE2086_WHITE_ټکی_Y_EXT   0x3348
#تعریف_کړه EGL_SMPTE2086_MAX_LUMINANCE_EXT   0x3349
#تعریف_کړه EGL_SMPTE2086_MIN_LUMINANCE_EXT   0x334A
#تعریف_کړه EGL_METADATA_SCALING_EXT          50000
#د_که_پای /* EGL_EXT_surface_SMPTE2086_metadata */

#که_نه_تعریف_شوی EGL_EXT_surface_compression
#تعریف_کړه EGL_EXT_surface_compression 1
#تعریف_کړه EGL_SURFACE_COMPRESSION_EXT       0x34B0
#تعریف_کړه EGL_SURFACE_COMPRESSION_PLANE1_EXT 0x328E
#تعریف_کړه EGL_SURFACE_COMPRESSION_PLANE2_EXT 0x328F
#تعریف_کړه EGL_SURFACE_COMPRESSION_FIXED_شرح_NONE_EXT 0x34B1
#تعریف_کړه EGL_SURFACE_COMPRESSION_FIXED_شرح_DEFAULT_EXT 0x34B2
#تعریف_کړه EGL_SURFACE_COMPRESSION_FIXED_شرح_1_BPC_EXT 0x34B4
#تعریف_کړه EGL_SURFACE_COMPRESSION_FIXED_شرح_2_BPC_EXT 0x34B5
#تعریف_کړه EGL_SURFACE_COMPRESSION_FIXED_شرح_3_BPC_EXT 0x34B6
#تعریف_کړه EGL_SURFACE_COMPRESSION_FIXED_شرح_4_BPC_EXT 0x34B7
#تعریف_کړه EGL_SURFACE_COMPRESSION_FIXED_شرح_5_BPC_EXT 0x34B8
#تعریف_کړه EGL_SURFACE_COMPRESSION_FIXED_شرح_6_BPC_EXT 0x34B9
#تعریف_کړه EGL_SURFACE_COMPRESSION_FIXED_شرح_7_BPC_EXT 0x34BA
#تعریف_کړه EGL_SURFACE_COMPRESSION_FIXED_شرح_8_BPC_EXT 0x34BB
#تعریف_کړه EGL_SURFACE_COMPRESSION_FIXED_شرح_9_BPC_EXT 0x34BC
#تعریف_کړه EGL_SURFACE_COMPRESSION_FIXED_شرح_10_BPC_EXT 0x34BD
#تعریف_کړه EGL_SURFACE_COMPRESSION_FIXED_شرح_11_BPC_EXT 0x34BE
#تعریف_کړه EGL_SURFACE_COMPRESSION_FIXED_شرح_12_BPC_EXT 0x34BF
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSUPPORTEDCOMPRESSIONRATESEXTPROC) (EGLDisplay dpy, EGLConfig config, ثابت EGLAttrib *attrib_list, EGLint *rates, EGLint شرح_اندازه, EGLint *عدد_rates);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQuerySupportedCompressionRatesEXT (EGLDisplay dpy, EGLConfig config, ثابت EGLAttrib *attrib_list, EGLint *rates, EGLint شرح_اندازه, EGLint *عدد_rates);
#د_که_پای
#د_که_پای /* EGL_EXT_surface_compression */

#که_نه_تعریف_شوی EGL_EXT_بدلون_buffers_with_damage
#تعریف_کړه EGL_EXT_بدلون_buffers_with_damage 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC) (EGLDisplay dpy, EGLSurface surface, ثابت EGLint *rects, EGLint n_rects);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_بدلون_Buffers_With_Damage_EXT (EGLDisplay dpy, EGLSurface surface, ثابت EGLint *rects, EGLint n_rects);
#د_که_پای
#د_که_پای /* EGL_EXT_swap_buffers_with_damage */

#که_نه_تعریف_شوی EGL_EXT_sync_reuse
#تعریف_کړه EGL_EXT_sync_reuse 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLUNSIGNALSYNCEXTPROC) (EGLDisplay dpy, EGLSync sync, ثابت EGLAttrib *attrib_list);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglUnsignalSyncEXT (EGLDisplay dpy, EGLSync sync, ثابت EGLAttrib *attrib_list);
#د_که_پای
#د_که_پای /* EGL_EXT_sync_reuse */

#که_نه_تعریف_شوی EGL_EXT_yuv_surface
#تعریف_کړه EGL_EXT_yuv_surface 1
#تعریف_کړه EGL_YUV_ترتیب_EXT                 0x3301
#تعریف_کړه EGL_YUV_شمېره_د_PLANES_EXT      0x3311
#تعریف_کړه EGL_YUV_SUBSAMPLE_EXT             0x3312
#تعریف_کړه EGL_YUV_ژوروالی_RANGE_EXT           0x3317
#تعریف_کړه EGL_YUV_CSC_STANDARD_EXT          0x330A
#تعریف_کړه EGL_YUV_PLANE_BPP_EXT             0x331A
#تعریف_کړه EGL_YUV_بفر_EXT                0x3300
#تعریف_کړه EGL_YUV_ترتیب_YUV_EXT             0x3302
#تعریف_کړه EGL_YUV_ترتیب_YVU_EXT             0x3303
#تعریف_کړه EGL_YUV_ترتیب_YUYV_EXT            0x3304
#تعریف_کړه EGL_YUV_ترتیب_UYVY_EXT            0x3305
#تعریف_کړه EGL_YUV_ترتیب_YVYU_EXT            0x3306
#تعریف_کړه EGL_YUV_ترتیب_VYUY_EXT            0x3307
#تعریف_کړه EGL_YUV_ترتیب_AYUV_EXT            0x3308
#تعریف_کړه EGL_YUV_SUBSAMPLE_4_2_0_EXT       0x3313
#تعریف_کړه EGL_YUV_SUBSAMPLE_4_2_2_EXT       0x3314
#تعریف_کړه EGL_YUV_SUBSAMPLE_4_4_4_EXT       0x3315
#تعریف_کړه EGL_YUV_ژوروالی_RANGE_LIMITED_EXT   0x3318
#تعریف_کړه EGL_YUV_ژوروالی_RANGE_ډک_EXT      0x3319
#تعریف_کړه EGL_YUV_CSC_STANDARD_601_EXT      0x330B
#تعریف_کړه EGL_YUV_CSC_STANDARD_709_EXT      0x330C
#تعریف_کړه EGL_YUV_CSC_STANDARD_2020_EXT     0x330D
#تعریف_کړه EGL_YUV_PLANE_BPP_0_EXT           0x331B
#تعریف_کړه EGL_YUV_PLANE_BPP_8_EXT           0x331C
#تعریف_کړه EGL_YUV_PLANE_BPP_10_EXT          0x331D
#د_که_پای /* EGL_EXT_yuv_surface */

#که_نه_تعریف_شوی EGL_HI_clientpixmap
#تعریف_کړه EGL_HI_clientpixmap 1
بنية EGLClientPixmapHI {
    فراغ  *p_معلومات;
    EGLint i_پلنوالی;
    EGLint i_لوړوالی;
    EGLint iStride;
};
#تعریف_کړه EGL_CLIENT_PIXMAP_اشاره_ګر_HI      0x8F74
تعريفنوع EGLSurface (EGLAPIENTRYP PFNEGLCREATEPIXMAPSURFACEHIPROC) (EGLDisplay dpy, EGLConfig config, بنية EGLClientPixmapHI *pixmap);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSurface EGLAPIENTRY eglCreatePixmapSurfaceHI (EGLDisplay dpy, EGLConfig config, بنية EGLClientPixmapHI *pixmap);
#د_که_پای
#د_که_پای /* EGL_HI_clientpixmap */

#که_نه_تعریف_شوی EGL_HI_colorformats
#تعریف_کړه EGL_HI_colorformats 1
#تعریف_کړه EGL_COLOR_FORMAT_HI               0x8F70
#تعریف_کړه EGL_COLOR_RGB_HI                  0x8F71
#تعریف_کړه EGL_COLOR_RGBA_HI                 0x8F72
#تعریف_کړه EGL_COLOR_ARGB_HI                 0x8F73
#د_که_پای /* EGL_HI_colorformats */

#که_نه_تعریف_شوی EGL_IMG_context_لومړیتوب
#تعریف_کړه EGL_IMG_context_لومړیتوب 1
#تعریف_کړه EGL_CONTEXT_لومړیتوب_LEVEL_IMG    0x3100
#تعریف_کړه EGL_CONTEXT_لومړیتوب_لوړ_IMG     0x3101
#تعریف_کړه EGL_CONTEXT_لومړیتوب_MEDIUM_IMG   0x3102
#تعریف_کړه EGL_CONTEXT_لومړیتوب_ټیټ_IMG      0x3103
#د_که_پای /* EGL_IMG_context_priority */

#که_نه_تعریف_شوی EGL_IMG_image_plane_attribs
#تعریف_کړه EGL_IMG_image_plane_attribs 1
#تعریف_کړه EGL_NATIVE_بفر_MULTIPLANE_SEPARATE_IMG 0x3105
#تعریف_کړه EGL_NATIVE_بفر_PLANE_دننه_واټن_IMG 0x3106
#د_که_پای /* EGL_IMG_image_plane_attribs */

#که_نه_تعریف_شوی EGL_MESA_drm_image
#تعریف_کړه EGL_MESA_drm_image 1
#تعریف_کړه EGL_DRM_بفر_FORMAT_MESA        0x31D0
#تعریف_کړه EGL_DRM_بفر_USE_MESA           0x31D1
#تعریف_کړه EGL_DRM_بفر_FORMAT_ARGB32_MESA 0x31D2
#تعریف_کړه EGL_DRM_بفر_MESA               0x31D3
#تعریف_کړه EGL_DRM_بفر_STRIDE_MESA        0x31D4
#تعریف_کړه EGL_DRM_بفر_USE_SCANOUT_MESA   0x00000001
#تعریف_کړه EGL_DRM_بفر_USE_SHARE_MESA     0x00000002
#تعریف_کړه EGL_DRM_بفر_USE_CURSOR_MESA    0x00000004
تعريفنوع EGLImageKHR (EGLAPIENTRYP PFNEGLCREATEDRMIMAGEMESAPROC) (EGLDisplay dpy, ثابت EGLint *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLEXPORTDRMIMAGEMESAPROC) (EGLDisplay dpy, EGLImageKHR image, EGLint *name, EGLint *handle, EGLint *stride);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLImageKHR EGLAPIENTRY eglCreateDRMImageMESA (EGLDisplay dpy, ثابت EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglExportDRMImageMESA (EGLDisplay dpy, EGLImageKHR image, EGLint *name, EGLint *handle, EGLint *stride);
#د_که_پای
#د_که_پای /* EGL_MESA_drm_image */

#که_نه_تعریف_شوی EGL_MESA_image_dma_buf_export
#تعریف_کړه EGL_MESA_image_dma_buf_export 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLEXPORTDMABUFIMAGEQUERYMESAPROC) (EGLDisplay dpy, EGLImageKHR image, صحيح *fourcc, صحيح *عدد_planes, EGLuint64KHR *modifiers);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLEXPORTDMABUFIMAGEMESAPROC) (EGLDisplay dpy, EGLImageKHR image, صحيح *fds, EGLint *strides, EGLint *offsets);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglExportDMABUFImageQueryMESA (EGLDisplay dpy, EGLImageKHR image, صحيح *fourcc, صحيح *عدد_planes, EGLuint64KHR *modifiers);
EGLAPI EGLBoolean EGLAPIENTRY eglExportDMABUFImageMESA (EGLDisplay dpy, EGLImageKHR image, صحيح *fds, EGLint *strides, EGLint *offsets);
#د_که_پای
#د_که_پای /* EGL_MESA_image_dma_buf_export */

#که_نه_تعریف_شوی EGL_MESA_platform_gbm
#تعریف_کړه EGL_MESA_platform_gbm 1
#تعریف_کړه EGL_PLATFORM_GBM_MESA             0x31D7
#د_که_پای /* EGL_MESA_platform_gbm */

#که_نه_تعریف_شوی EGL_MESA_platform_surfaceless
#تعریف_کړه EGL_MESA_platform_surfaceless 1
#تعریف_کړه EGL_PLATFORM_SURFACELESS_MESA     0x31DD
#د_که_پای /* EGL_MESA_platform_surfaceless */

#که_نه_تعریف_شوی EGL_MESA_query_driver
#تعریف_کړه EGL_MESA_query_driver 1
تعريفنوع حرف *(EGLAPIENTRYP PFNEGLGETDISPLAYDRIVERCONFIGPROC) (EGLDisplay dpy);
تعريفنوع ثابت حرف *(EGLAPIENTRYP PFNEGLGETDISPLAYDRIVERNAMEPROC) (EGLDisplay dpy);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI حرف *EGLAPIENTRY eglGetDisplayDriverConfig (EGLDisplay dpy);
EGLAPI ثابت حرف *EGLAPIENTRY eglGetDisplayDriverName (EGLDisplay dpy);
#د_که_پای
#د_که_پای /* EGL_MESA_query_driver */

#که_نه_تعریف_شوی EGL_NOK_بدلون_region
#تعریف_کړه EGL_NOK_بدلون_region 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSREGIONNOKPROC) (EGLDisplay dpy, EGLSurface surface, EGLint عدد_Rects_2, ثابت EGLint *rects);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_بدلون_Buffers_Region_NOK (EGLDisplay dpy, EGLSurface surface, EGLint عدد_Rects_2, ثابت EGLint *rects);
#د_که_پای
#د_که_پای /* EGL_NOK_swap_region */

#که_نه_تعریف_شوی EGL_NOK_بدلون_region2
#تعریف_کړه EGL_NOK_بدلون_region2 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSREGION2NOKPROC) (EGLDisplay dpy, EGLSurface surface, EGLint عدد_Rects_2, ثابت EGLint *rects);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_بدلون_Buffers_Region2_NOK (EGLDisplay dpy, EGLSurface surface, EGLint عدد_Rects_2, ثابت EGLint *rects);
#د_که_پای
#د_که_پای /* EGL_NOK_swap_region2 */

#که_نه_تعریف_شوی EGL_NOK_texture_from_pixmap
#تعریف_کړه EGL_NOK_texture_from_pixmap 1
#تعریف_کړه EGL_Y_INVERTED_NOK                0x307F
#د_که_پای /* EGL_NOK_texture_from_pixmap */

#که_نه_تعریف_شوی EGL_NV_3dvision_surface
#تعریف_کړه EGL_NV_3dvision_surface 1
#تعریف_کړه EGL_AUTO_STEREO_NV                0x3136
#د_که_پای /* EGL_NV_3dvision_surface */

#که_نه_تعریف_شوی EGL_NV_context_لومړیتوب_realtime
#تعریف_کړه EGL_NV_context_لومړیتوب_realtime 1
#تعریف_کړه EGL_CONTEXT_لومړیتوب_REALTIME_NV  0x3357
#د_که_پای /* EGL_NV_context_priority_realtime */

#که_نه_تعریف_شوی EGL_NV_coverage_sample
#تعریف_کړه EGL_NV_coverage_sample 1
#تعریف_کړه EGL_COVERAGE_BUFFERS_NV           0x30E0
#تعریف_کړه EGL_COVERAGE_SAMPLES_NV           0x30E1
#د_که_پای /* EGL_NV_coverage_sample */

#که_نه_تعریف_شوی EGL_NV_coverage_sample_resolve
#تعریف_کړه EGL_NV_coverage_sample_resolve 1
#تعریف_کړه EGL_COVERAGE_SAMPLE_RESOLVE_NV    0x3131
#تعریف_کړه EGL_COVERAGE_SAMPLE_RESOLVE_DEFAULT_NV 0x3132
#تعریف_کړه EGL_COVERAGE_SAMPLE_RESOLVE_NONE_NV 0x3133
#د_که_پای /* EGL_NV_coverage_sample_resolve */

#که_نه_تعریف_شوی EGL_NV_cuda_event
#تعریف_کړه EGL_NV_cuda_event 1
#تعریف_کړه EGL_CUDA_EVENT_HANDLE_NV          0x323B
#تعریف_کړه EGL_SYNC_CUDA_EVENT_NV            0x323C
#تعریف_کړه EGL_SYNC_CUDA_EVENT_COMPLETE_NV   0x323D
#د_که_پای /* EGL_NV_cuda_event */

#که_نه_تعریف_شوی EGL_NV_ژوروالی_nonlinear
#تعریف_کړه EGL_NV_ژوروالی_nonlinear 1
#تعریف_کړه EGL_ژوروالی_ENCODING_NV             0x30E2
#تعریف_کړه EGL_ژوروالی_ENCODING_NONE_NV        0
#تعریف_کړه EGL_ژوروالی_ENCODING_NONLINEAR_NV   0x30E3
#د_که_پای /* EGL_NV_depth_nonlinear */

#که_نه_تعریف_شوی EGL_NV_device_cuda
#تعریف_کړه EGL_NV_device_cuda 1
#تعریف_کړه EGL_CUDA_DEVICE_NV                0x323A
#د_که_پای /* EGL_NV_device_cuda */

#که_نه_تعریف_شوی EGL_NV_native_query
#تعریف_کړه EGL_NV_native_query 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYNATIVEDISPLAYNVPROC) (EGLDisplay dpy, EGLNativeDisplayType *display_id);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYNATIVEWINDOWNVPROC) (EGLDisplay dpy, EGLSurface surf, EGLNative_کړکۍ_Type *کړکۍ);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYNATIVEPIXMAPNVPROC) (EGLDisplay dpy, EGLSurface surf, EGLNativePixmapType *pixmap);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryNativeDisplayNV (EGLDisplay dpy, EGLNativeDisplayType *display_id);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Native_کړکۍ_NV (EGLDisplay dpy, EGLSurface surf, EGLNative_کړکۍ_Type *کړکۍ);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryNativePixmapNV (EGLDisplay dpy, EGLSurface surf, EGLNativePixmapType *pixmap);
#د_که_پای
#د_که_پای /* EGL_NV_native_query */

#که_نه_تعریف_شوی EGL_NV_post_convert_rounding
#تعریف_کړه EGL_NV_post_convert_rounding 1
#د_که_پای /* EGL_NV_post_convert_rounding */

#که_نه_تعریف_شوی EGL_NV_post_sub_بفر
#تعریف_کړه EGL_NV_post_sub_بفر 1
#تعریف_کړه EGL_POST_SUB_بفر_SUPPORTED_NV  0x30BE
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLPOSTSUBBUFFERNVPROC) (EGLDisplay dpy, EGLSurface surface, EGLint x, EGLint y, EGLint پلنوالی, EGLint لوړوالی);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Post_Sub_بفر_NV (EGLDisplay dpy, EGLSurface surface, EGLint x, EGLint y, EGLint پلنوالی, EGLint لوړوالی);
#د_که_پای
#د_که_پای /* EGL_NV_post_sub_buffer */

#که_نه_تعریف_شوی EGL_NV_quadruple_بفر
#تعریف_کړه EGL_NV_quadruple_بفر 1
#تعریف_کړه EGL_QUADRUPLE_بفر_NV           0x3231
#د_که_پای /* EGL_NV_quadruple_buffer */

#که_نه_تعریف_شوی EGL_NV_robustness_video_حافظه_purge
#تعریف_کړه EGL_NV_robustness_video_حافظه_purge 1
#تعریف_کړه EGL_GENERATE_RESET_ON_VIDEO_حافظه_PURGE_NV 0x334C
#د_که_پای /* EGL_NV_robustness_video_memory_purge */

#که_نه_تعریف_شوی EGL_NV_بهیر_مصرفوونکی_eglimage
#تعریف_کړه EGL_NV_بهیر_مصرفوونکی_eglimage 1
#تعریف_کړه EGL_بهیر_مصرفوونکی_IMAGE_NV      0x3373
#تعریف_کړه EGL_بهیر_IMAGE_جمع_کړه_NV           0x3374
#تعریف_کړه EGL_بهیر_IMAGE_REMOVE_NV        0x3375
#تعریف_کړه EGL_بهیر_IMAGE_شته_NV     0x3376
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMIMAGECONSUMERCONNECTNVPROC) (EGLDisplay dpy, EGLStreamKHR بهیر, EGLint عدد_modifiers, ثابت EGLuint64KHR *modifiers, ثابت EGLAttrib *attrib_list);
تعريفنوع EGLint (EGLAPIENTRYP PFNEGLQUERYSTREAMCONSUMEREVENTNVPROC) (EGLDisplay dpy, EGLStreamKHR بهیر, EGLTime timeout, EGLenum *event, EGLAttrib *aux);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMACQUIREIMAGENVPROC) (EGLDisplay dpy, EGLStreamKHR بهیر, EGLImage *pImage, EGLSync sync);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMRELEASEIMAGENVPROC) (EGLDisplay dpy, EGLStreamKHR بهیر, EGLImage image, EGLSync sync);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_بهیر_Image_مصرفوونکی_Connect_NV (EGLDisplay dpy, EGLStreamKHR بهیر, EGLint عدد_modifiers, ثابت EGLuint64KHR *modifiers, ثابت EGLAttrib *attrib_list);
EGLAPI EGLint EGLAPIENTRY egl_Query_بهیر_مصرفوونکی_Event_NV (EGLDisplay dpy, EGLStreamKHR بهیر, EGLTime timeout, EGLenum *event, EGLAttrib *aux);
EGLAPI EGLBoolean EGLAPIENTRY egl_بهیر_Acquire_Image_NV (EGLDisplay dpy, EGLStreamKHR بهیر, EGLImage *pImage, EGLSync sync);
EGLAPI EGLBoolean EGLAPIENTRY egl_بهیر_Release_Image_NV (EGLDisplay dpy, EGLStreamKHR بهیر, EGLImage image, EGLSync sync);
#د_که_پای
#د_که_پای /* EGL_NV_stream_consumer_eglimage */

#که_نه_تعریف_شوی EGL_NV_بهیر_مصرفوونکی_eglimage_use_scanout_attrib
#تعریف_کړه EGL_NV_بهیر_مصرفوونکی_eglimage_use_scanout_attrib 1
#تعریف_کړه EGL_بهیر_مصرفوونکی_IMAGE_USE_SCANOUT_NV 0x3378
#د_که_پای /* EGL_NV_stream_consumer_eglimage_use_scanout_attrib */

#که_نه_تعریف_شوی EGL_NV_بهیر_مصرفوونکی_gltexture_yuv
#تعریف_کړه EGL_NV_بهیر_مصرفوونکی_gltexture_yuv 1
#تعریف_کړه EGL_YUV_PLANE0_TEXTURE_UNIT_NV    0x332C
#تعریف_کړه EGL_YUV_PLANE1_TEXTURE_UNIT_NV    0x332D
#تعریف_کړه EGL_YUV_PLANE2_TEXTURE_UNIT_NV    0x332E
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALATTRIBSNVPROC) (EGLDisplay dpy, EGLStreamKHR بهیر, ثابت EGLAttrib *attrib_list);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_بهیر_مصرفوونکی_GLTexture_External_Attribs_NV (EGLDisplay dpy, EGLStreamKHR بهیر, ثابت EGLAttrib *attrib_list);
#د_که_پای
#د_که_پای /* EGL_NV_stream_consumer_gltexture_yuv */

#که_نه_تعریف_شوی EGL_NV_بهیر_cross_display
#تعریف_کړه EGL_NV_بهیر_cross_display 1
#تعریف_کړه EGL_بهیر_CROSS_DISPLAY_NV       0x334E
#د_که_پای /* EGL_NV_stream_cross_display */

#که_نه_تعریف_شوی EGL_NV_بهیر_cross_object
#تعریف_کړه EGL_NV_بهیر_cross_object 1
#تعریف_کړه EGL_بهیر_CROSS_OBJECT_NV        0x334D
#د_که_پای /* EGL_NV_stream_cross_object */

#که_نه_تعریف_شوی EGL_NV_بهیر_cross_برخه_کول
#تعریف_کړه EGL_NV_بهیر_cross_برخه_کول 1
#تعریف_کړه EGL_بهیر_CROSS_برخه_کول_NV     0x323F
#د_که_پای /* EGL_NV_stream_cross_partition */

#که_نه_تعریف_شوی EGL_NV_بهیر_cross_process
#تعریف_کړه EGL_NV_بهیر_cross_process 1
#تعریف_کړه EGL_بهیر_CROSS_PROCESS_NV       0x3245
#د_که_پای /* EGL_NV_stream_cross_process */

#که_نه_تعریف_شوی EGL_NV_بهیر_cross_system
#تعریف_کړه EGL_NV_بهیر_cross_system 1
#تعریف_کړه EGL_بهیر_CROSS_SYSTEM_NV        0x334F
#د_که_پای /* EGL_NV_stream_cross_system */

#که_نه_تعریف_شوی EGL_NV_بهیر_dma
#تعریف_کړه EGL_NV_بهیر_dma 1
#تعریف_کړه EGL_بهیر_DMA_NV                 0x3371
#تعریف_کړه EGL_بهیر_DMA_SERVER_NV          0x3372
#د_که_پای /* EGL_NV_stream_dma */

#که_نه_تعریف_شوی EGL_NV_بهیر_fifo_بل
#تعریف_کړه EGL_NV_بهیر_fifo_بل 1
#تعریف_کړه EGL_PENDING_چوکاټ_NV              0x3329
#تعریف_کړه EGL_بهیر_وخت_PENDING_NV        0x332A
#د_که_پای /* EGL_NV_stream_fifo_next */

#که_نه_تعریف_شوی EGL_NV_بهیر_fifo_synchronous
#تعریف_کړه EGL_NV_بهیر_fifo_synchronous 1
#تعریف_کړه EGL_بهیر_FIFO_SYNCHRONOUS_NV    0x3336
#د_که_پای /* EGL_NV_stream_fifo_synchronous */

#که_نه_تعریف_شوی EGL_NV_بهیر_flush
#تعریف_کړه EGL_NV_بهیر_flush 1
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMFLUSHNVPROC) (EGLDisplay dpy, EGLStreamKHR بهیر);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_بهیر_Flush_NV (EGLDisplay dpy, EGLStreamKHR بهیر);
#د_که_پای
#د_که_پای /* EGL_NV_stream_flush */

#که_نه_تعریف_شوی EGL_NV_بهیر_چوکاټ_limits
#تعریف_کړه EGL_NV_بهیر_چوکاټ_limits 1
#تعریف_کړه EGL_تولیدوونکی_MAX_چوکاټ_HINT_NV    0x3337
#تعریف_کړه EGL_مصرفوونکی_MAX_چوکاټ_HINT_NV    0x3338
#د_که_پای /* EGL_NV_stream_frame_limits */

#که_نه_تعریف_شوی EGL_NV_بهیر_metadata
#تعریف_کړه EGL_NV_بهیر_metadata 1
#تعریف_کړه EGL_MAX_بهیر_METADATA_بلاکونه_NV 0x3250
#تعریف_کړه EGL_MAX_بهیر_METADATA_بلاک_اندازه_NV 0x3251
#تعریف_کړه EGL_MAX_بهیر_METADATA_ټول_اندازه_NV 0x3252
#تعریف_کړه EGL_تولیدوونکی_METADATA_NV          0x3253
#تعریف_کړه EGL_مصرفوونکی_METADATA_NV          0x3254
#تعریف_کړه EGL_PENDING_METADATA_NV           0x3328
#تعریف_کړه EGL_METADATA0_اندازه_NV             0x3255
#تعریف_کړه EGL_METADATA1_اندازه_NV             0x3256
#تعریف_کړه EGL_METADATA2_اندازه_NV             0x3257
#تعریف_کړه EGL_METADATA3_اندازه_NV             0x3258
#تعریف_کړه EGL_METADATA0_TYPE_NV             0x3259
#تعریف_کړه EGL_METADATA1_TYPE_NV             0x325A
#تعریف_کړه EGL_METADATA2_TYPE_NV             0x325B
#تعریف_کړه EGL_METADATA3_TYPE_NV             0x325C
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDISPLAYATTRIBNVPROC) (EGLDisplay dpy, EGLint attribute, EGLAttrib *ارزښت);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSETSTREAMMETADATANVPROC) (EGLDisplay dpy, EGLStreamKHR بهیر, EGLint n, EGLint دننه_واټن_2, EGLint اندازه, ثابت فراغ *معلومات);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMMETADATANVPROC) (EGLDisplay dpy, EGLStreamKHR بهیر, EGLenum name, EGLint n, EGLint دننه_واټن_2, EGLint اندازه, فراغ *معلومات);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDisplayAttribNV (EGLDisplay dpy, EGLint attribute, EGLAttrib *ارزښت);
EGLAPI EGLBoolean EGLAPIENTRY egl_سېټ_بهیر_Metadata_NV (EGLDisplay dpy, EGLStreamKHR بهیر, EGLint n, EGLint دننه_واټن_2, EGLint اندازه, ثابت فراغ *معلومات);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_بهیر_Metadata_NV (EGLDisplay dpy, EGLStreamKHR بهیر, EGLenum name, EGLint n, EGLint دننه_واټن_2, EGLint اندازه, فراغ *معلومات);
#د_که_پای
#د_که_پای /* EGL_NV_stream_metadata */

#که_نه_تعریف_شوی EGL_NV_بهیر_origin
#تعریف_کړه EGL_NV_بهیر_origin 1
#تعریف_کړه EGL_بهیر_چوکاټ_ORIGIN_X_NV      0x3366
#تعریف_کړه EGL_بهیر_چوکاټ_ORIGIN_Y_NV      0x3367
#تعریف_کړه EGL_بهیر_چوکاټ_MAJOR_AXIS_NV    0x3368
#تعریف_کړه EGL_مصرفوونکی_AUTO_ORIENTATION_NV  0x3369
#تعریف_کړه EGL_تولیدوونکی_AUTO_ORIENTATION_NV  0x336A
#تعریف_کړه EGL_کیڼ_NV                       0x336B
#تعریف_کړه EGL_ښی_NV                      0x336C
#تعریف_کړه EGL_سر_NV                        0x336D
#تعریف_کړه EGL_BOTTOM_NV                     0x336E
#تعریف_کړه EGL_X_AXIS_NV                     0x336F
#تعریف_کړه EGL_Y_AXIS_NV                     0x3370
#د_که_پای /* EGL_NV_stream_origin */

#که_نه_تعریف_شوی EGL_NV_بهیر_remote
#تعریف_کړه EGL_NV_بهیر_remote 1
#تعریف_کړه EGL_بهیر_STATE_INITIALIZING_NV  0x3240
#تعریف_کړه EGL_بهیر_TYPE_NV                0x3241
#تعریف_کړه EGL_بهیر_PROTOCOL_NV            0x3242
#تعریف_کړه EGL_بهیر_ENDPOINT_NV            0x3243
#تعریف_کړه EGL_بهیر_LOCAL_NV               0x3244
#تعریف_کړه EGL_بهیر_تولیدوونکی_NV            0x3247
#تعریف_کړه EGL_بهیر_مصرفوونکی_NV            0x3248
#تعریف_کړه EGL_بهیر_PROTOCOL_FD_NV         0x3246
#د_که_پای /* EGL_NV_stream_remote */

#که_نه_تعریف_شوی EGL_NV_بهیر_reset
#تعریف_کړه EGL_NV_بهیر_reset 1
#تعریف_کړه EGL_SUPPORT_RESET_NV              0x3334
#تعریف_کړه EGL_SUPPORT_REUSE_NV              0x3335
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLRESETSTREAMNVPROC) (EGLDisplay dpy, EGLStreamKHR بهیر);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Reset_بهیر_NV (EGLDisplay dpy, EGLStreamKHR بهیر);
#د_که_پای
#د_که_پای /* EGL_NV_stream_reset */

#که_نه_تعریف_شوی EGL_NV_بهیر_socket
#تعریف_کړه EGL_NV_بهیر_socket 1
#تعریف_کړه EGL_بهیر_PROTOCOL_SOCKET_NV     0x324B
#تعریف_کړه EGL_SOCKET_HANDLE_NV              0x324C
#تعریف_کړه EGL_SOCKET_TYPE_NV                0x324D
#د_که_پای /* EGL_NV_stream_socket */

#که_نه_تعریف_شوی EGL_NV_بهیر_socket_inet
#تعریف_کړه EGL_NV_بهیر_socket_inet 1
#تعریف_کړه EGL_SOCKET_TYPE_INET_NV           0x324F
#د_که_پای /* EGL_NV_stream_socket_inet */

#که_نه_تعریف_شوی EGL_NV_بهیر_socket_unix
#تعریف_کړه EGL_NV_بهیر_socket_unix 1
#تعریف_کړه EGL_SOCKET_TYPE_UNIX_NV           0x324E
#د_که_پای /* EGL_NV_stream_socket_unix */

#که_نه_تعریف_شوی EGL_NV_بهیر_sync
#تعریف_کړه EGL_NV_بهیر_sync 1
#تعریف_کړه EGL_SYNC_NEW_چوکاټ_NV             0x321F
تعريفنوع EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESTREAMSYNCNVPROC) (EGLDisplay dpy, EGLStreamKHR بهیر, EGLenum type, ثابت EGLint *attrib_list);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncKHR EGLAPIENTRY egl_Create_بهیر_Sync_NV (EGLDisplay dpy, EGLStreamKHR بهیر, EGLenum type, ثابت EGLint *attrib_list);
#د_که_پای
#د_که_پای /* EGL_NV_stream_sync */

#که_نه_تعریف_شوی EGL_NV_sync
#تعریف_کړه EGL_NV_sync 1
تعريفنوع فراغ *EGLSyncNV;
تعريفنوع khronos_utime_nanoseconds_t EGLTimeNV;
#که_تعریف_شوی KHRONOS_SUPPORT_INT64
#تعریف_کړه EGL_SYNC_مخکینی_COMMANDS_COMPLETE_NV 0x30E6
#تعریف_کړه EGL_SYNC_حالت_NV                0x30E7
#تعریف_کړه EGL_SIGNALED_NV                   0x30E8
#تعریف_کړه EGL_UNSIGNALED_NV                 0x30E9
#تعریف_کړه EGL_SYNC_FLUSH_COMMANDS_بټ_NV    0x0001
#تعریف_کړه EGL_FOREVER_NV                    0xFFFFFFFFFFFFFFFFull
#تعریف_کړه EGL_ALREADY_SIGNALED_NV           0x30EA
#تعریف_کړه EGL_TIMEOUT_EXPIRED_NV            0x30EB
#تعریف_کړه EGL_CONDITION_SATISFIED_NV        0x30EC
#تعریف_کړه EGL_SYNC_TYPE_NV                  0x30ED
#تعریف_کړه EGL_SYNC_CONDITION_NV             0x30EE
#تعریف_کړه EGL_SYNC_FENCE_NV                 0x30EF
#تعریف_کړه EGL_NO_SYNC_NV                    EGL_CAST(EGLSyncNV,0)
تعريفنوع EGLSyncNV (EGLAPIENTRYP PFNEGLCREATEFENCESYNCNVPROC) (EGLDisplay dpy, EGLenum condition, ثابت EGLint *attrib_list);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCNVPROC) (EGLSyncNV sync);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLFENCENVPROC) (EGLSyncNV sync);
تعريفنوع EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCNVPROC) (EGLSyncNV sync, EGLint flags, EGLTimeNV timeout);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLSIGNALSYNCNVPROC) (EGLSyncNV sync, EGLenum ډېرپېښ);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLGETSYNCATTRIBNVPROC) (EGLSyncNV sync, EGLint attribute, EGLint *ارزښت);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncNV EGLAPIENTRY eglCreateFenceSyncNV (EGLDisplay dpy, EGLenum condition, ثابت EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySyncNV (EGLSyncNV sync);
EGLAPI EGLBoolean EGLAPIENTRY eglFenceNV (EGLSyncNV sync);
EGLAPI EGLint EGLAPIENTRY eglClientWaitSyncNV (EGLSyncNV sync, EGLint flags, EGLTimeNV timeout);
EGLAPI EGLBoolean EGLAPIENTRY eglSignalSyncNV (EGLSyncNV sync, EGLenum ډېرپېښ);
EGLAPI EGLBoolean EGLAPIENTRY eglGetSyncAttribNV (EGLSyncNV sync, EGLint attribute, EGLint *ارزښت);
#د_که_پای
#د_که_پای /* KHRONOS_SUPPORT_INT64 */
#د_که_پای /* EGL_NV_sync */

#که_نه_تعریف_شوی EGL_NV_system_وخت
#تعریف_کړه EGL_NV_system_وخت 1
تعريفنوع khronos_utime_nanoseconds_t EGLuint64NV;
#که_تعریف_شوی KHRONOS_SUPPORT_INT64
تعريفنوع EGLuint64NV (EGLAPIENTRYP PFNEGLGETSYSTEMTIMEFREQUENCYNVPROC) (فراغ);
تعريفنوع EGLuint64NV (EGLAPIENTRYP PFNEGLGETSYSTEMTIMENVPROC) (فراغ);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLuint64NV EGLAPIENTRY egl_Get_System_وخت_Frequency_NV (فراغ);
EGLAPI EGLuint64NV EGLAPIENTRY egl_Get_System_وخت_NV (فراغ);
#د_که_پای
#د_که_پای /* KHRONOS_SUPPORT_INT64 */
#د_که_پای /* EGL_NV_system_time */

#که_نه_تعریف_شوی EGL_NV_triple_بفر
#تعریف_کړه EGL_NV_triple_بفر 1
#تعریف_کړه EGL_TRIPLE_بفر_NV              0x3230
#د_که_پای /* EGL_NV_triple_buffer */

#که_نه_تعریف_شوی EGL_QNX_image_native_بفر
#تعریف_کړه EGL_QNX_image_native_بفر 1
#تعریف_کړه EGL_NATIVE_بفر_QNX             0x3551
#د_که_پای /* EGL_QNX_image_native_buffer */

#که_نه_تعریف_شوی EGL_QNX_platform_screen
#تعریف_کړه EGL_QNX_platform_screen 1
#تعریف_کړه EGL_PLATFORM_SCREEN_QNX           0x3550
#د_که_پای /* EGL_QNX_platform_screen */

#که_نه_تعریف_شوی EGL_TIZEN_image_native_بفر
#تعریف_کړه EGL_TIZEN_image_native_بفر 1
#تعریف_کړه EGL_NATIVE_بفر_TIZEN           0x32A0
#د_که_پای /* EGL_TIZEN_image_native_buffer */

#که_نه_تعریف_شوی EGL_TIZEN_image_native_surface
#تعریف_کړه EGL_TIZEN_image_native_surface 1
#تعریف_کړه EGL_NATIVE_SURFACE_TIZEN          0x32A1
#د_که_پای /* EGL_TIZEN_image_native_surface */

#که_نه_تعریف_شوی EGL_WL_bind_wayland_display
#تعریف_کړه EGL_WL_bind_wayland_display 1
#تعریف_کړه PFNEGLBINDWAYLANDDISPLAYWL PFNEGLBINDWAYLANDDISPLAYWLPROC
#تعریف_کړه PFNEGLUNBINDWAYLANDDISPLAYWL PFNEGLUNBINDWAYLANDDISPLAYWLPROC
#تعریف_کړه PFNEGLQUERYWAYLANDBUFFERWL PFNEGLQUERYWAYLANDBUFFERWLPROC
بنية wl_display;
بنية wl_resource;
#تعریف_کړه EGL_WAYLAND_بفر_WL             0x31D5
#تعریف_کړه EGL_WAYLAND_PLANE_WL              0x31D6
#تعریف_کړه EGL_TEXTURE_Y_U_V_WL              0x31D7
#تعریف_کړه EGL_TEXTURE_Y_UV_WL               0x31D8
#تعریف_کړه EGL_TEXTURE_Y_XUXV_WL             0x31D9
#تعریف_کړه EGL_TEXTURE_EXTERNAL_WL           0x31DA
#تعریف_کړه EGL_WAYLAND_Y_INVERTED_WL         0x31DB
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLBINDWAYLANDDISPLAYWLPROC) (EGLDisplay dpy, بنية wl_display *display);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLUNBINDWAYLANDDISPLAYWLPROC) (EGLDisplay dpy, بنية wl_display *display);
تعريفنوع EGLBoolean (EGLAPIENTRYP PFNEGLQUERYWAYLANDBUFFERWLPROC) (EGLDisplay dpy, بنية wl_resource *بفر_2, EGLint attribute, EGLint *ارزښت);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglBindWaylandDisplayWL (EGLDisplay dpy, بنية wl_display *display);
EGLAPI EGLBoolean EGLAPIENTRY eglUnbindWaylandDisplayWL (EGLDisplay dpy, بنية wl_display *display);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Wayland_بفر_WL (EGLDisplay dpy, بنية wl_resource *بفر_2, EGLint attribute, EGLint *ارزښت);
#د_که_پای
#د_که_پای /* EGL_WL_bind_wayland_display */

#که_نه_تعریف_شوی EGL_WL_create_wayland_بفر_from_image
#تعریف_کړه EGL_WL_create_wayland_بفر_from_image 1
#تعریف_کړه PFNEGLCREATEWAYLANDBUFFERFROMIMAGEWL PFNEGLCREATEWAYLANDBUFFERFROMIMAGEWLPROC
بنية wl_بفر;
تعريفنوع بنية wl_بفر *(EGLAPIENTRYP PFNEGLCREATEWAYLANDBUFFERFROMIMAGEWLPROC) (EGLDisplay dpy, EGLImageKHR image);
#که_تعریف_شوی EGL_EGLEXT_PROTOTYPES
EGLAPI بنية wl_بفر *EGLAPIENTRY egl_Create_Wayland_بفر_From_Image_WL (EGLDisplay dpy, EGLImageKHR image);
#د_که_پای
#د_که_پای /* EGL_WL_create_wayland_buffer_from_image */

#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای
