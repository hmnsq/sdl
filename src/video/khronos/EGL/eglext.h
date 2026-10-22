#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __eglext_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ __eglext_h_ 1

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ

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

#ਅਨ੍ਤਰ੍ਭਾਵ <EGL/eglplatform.h>

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EGLEXT_ਸੰਸਕਰਣ 20260319

/* Generated C header for:
 * API: egl
 * Versions considered: .*
 * Versions emitted: _nomatch_^
 * Default extensions included: egl
 * Additional extensions included: _nomatch_^
 * Extensions removed: _nomatch_^
 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_cl_event
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_cl_event 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CL_EVENT_HANDLE_KHR           0x309C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SYNC_CL_EVENT_KHR             0x30FE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SYNC_CL_EVENT_COMPLETE_KHR    0x30FF
#ਜੇ_ਅੰਤ /* EGL_KHR_cl_event */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_cl_event2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_cl_event2 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ *EGLSyncKHR;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ intptr_t EGLAttribKHR;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESYNC64KHRPROC) (EGLDisplay dpy, EGLenum type, ਅਚਲ EGLAttribKHR *attrib_list);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncKHR EGLAPIENTRY eglCreateSync64KHR (EGLDisplay dpy, EGLenum type, ਅਚਲ EGLAttribKHR *attrib_list);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_KHR_cl_event2 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_client_get_all_proc_ਪਤੇ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_client_get_all_proc_ਪਤੇ 1
#ਜੇ_ਅੰਤ /* EGL_KHR_client_get_all_proc_addresses */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_config_attribs
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_config_attribs 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONFORMANT_KHR                0x3042
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_VG_COLORSPACE_ਰੇਖਿਕ_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR  0x0020
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_VG_ALPHA_FORMAT_PRE_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR   0x0040
#ਜੇ_ਅੰਤ /* EGL_KHR_config_attribs */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_context_flush_control
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_context_flush_control 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONTEXT_RELEASE_BEHAVIOR_NONE_KHR 0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONTEXT_RELEASE_BEHAVIOR_KHR  0x2097
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_KHR 0x2098
#ਜੇ_ਅੰਤ /* EGL_KHR_context_flush_control */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_create_context
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_create_context 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONTEXT_MAJOR_ਸੰਸਕਰਣ_KHR     0x3098
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONTEXT_MINOR_ਸੰਸਕਰਣ_KHR     0x30FB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONTEXT_FLAGS_KHR             0x30FC
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONTEXT_OPENGL_PROFILE_ਨਕਾਬ_KHR 0x30FD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_KHR 0x31BD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NO_RESET_NOTIFICATION_KHR     0x31BE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_LOSE_CONTEXT_ON_RESET_KHR     0x31BF
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONTEXT_OPENGL_DEBUG_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR  0x00000001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR 0x00000002
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONTEXT_OPENGL_ROBUST_ACCESS_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR 0x00000004
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONTEXT_OPENGL_CORE_PROFILE_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR 0x00000001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR 0x00000002
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_OPENGL_ES3_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR            0x00000040
#ਜੇ_ਅੰਤ /* EGL_KHR_create_context */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_create_context_no_error
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_create_context_no_error 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONTEXT_OPENGL_NO_ERROR_KHR   0x31B3
#ਜੇ_ਅੰਤ /* EGL_KHR_create_context_no_error */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_debug
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_debug 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ *EGLLabelKHR;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ *EGLObjectKHR;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (EGLAPIENTRY  *EGLDEBUGPROCKHR)(EGLenum error,ਅਚਲ ਅੱਖਰ *command,EGLint ਸੁਨੇਹਾ_Type,EGLLabelKHR threadLabel,EGLLabelKHR objectLabel,ਅਚਲ ਅੱਖਰ* ਸੁਨੇਹਾ);
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_OBJECT_THREAD_KHR             0x33B0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_OBJECT_DISPLAY_KHR            0x33B1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_OBJECT_CONTEXT_KHR            0x33B2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_OBJECT_SURFACE_KHR            0x33B3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_OBJECT_IMAGE_KHR              0x33B4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_OBJECT_SYNC_KHR               0x33B5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_OBJECT_ਧਾਰਾ_KHR             0x33B6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DEBUG_ਸੁਨੇਹਾ_CRITICAL_KHR        0x33B9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DEBUG_ਸੁਨੇਹਾ_ERROR_KHR           0x33BA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DEBUG_ਸੁਨੇਹਾ_WARN_KHR            0x33BB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DEBUG_ਸੁਨੇਹਾ_INFO_KHR            0x33BC
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DEBUG_CALLBACK_KHR            0x33B8
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLint (EGLAPIENTRYP PFNEGLDEBUGMESSAGECONTROLKHRPROC) (EGLDEBUGPROCKHR callback, ਅਚਲ EGLAttrib *attrib_list);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEBUGKHRPROC) (EGLint attribute, EGLAttrib *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLint (EGLAPIENTRYP PFNEGLLABELOBJECTKHRPROC) (EGLDisplay display, EGLenum objectType, EGLObjectKHR object, EGLLabelKHR label);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLint EGLAPIENTRY egl_Debug_ਸੁਨੇਹਾ_Control_KHR (EGLDEBUGPROCKHR callback, ਅਚਲ EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDebugKHR (EGLint attribute, EGLAttrib *ਮੁੱਲ);
EGLAPI EGLint EGLAPIENTRY eglLabelObjectKHR (EGLDisplay display, EGLenum objectType, EGLObjectKHR object, EGLLabelKHR label);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_KHR_debug */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_display_reference
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_display_reference 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_TRACK_REFERENCES_KHR          0x3352
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDISPLAYATTRIBKHRPROC) (EGLDisplay dpy, EGLint name, EGLAttrib *ਮੁੱਲ);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDisplayAttribKHR (EGLDisplay dpy, EGLint name, EGLAttrib *ਮੁੱਲ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_KHR_display_reference */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_fence_sync
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_fence_sync 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ khronos_utime_nanoseconds_t EGLTimeKHR;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ KHRONOS_SUPPORT_INT64
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SYNC_ਪੂਰਵ_COMMANDS_COMPLETE_KHR 0x30F0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SYNC_CONDITION_KHR            0x30F8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SYNC_FENCE_KHR                0x30F9
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESYNCKHRPROC) (EGLDisplay dpy, EGLenum type, ਅਚਲ EGLint *attrib_list);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLGETSYNCATTRIBKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint attribute, EGLint *ਮੁੱਲ);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncKHR EGLAPIENTRY eglCreateSyncKHR (EGLDisplay dpy, EGLenum type, ਅਚਲ EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySyncKHR (EGLDisplay dpy, EGLSyncKHR sync);
EGLAPI EGLint EGLAPIENTRY eglClientWaitSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);
EGLAPI EGLBoolean EGLAPIENTRY eglGetSyncAttribKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint attribute, EGLint *ਮੁੱਲ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* KHRONOS_SUPPORT_INT64 */
#ਜੇ_ਅੰਤ /* EGL_KHR_fence_sync */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_get_all_proc_ਪਤੇ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_get_all_proc_ਪਤੇ 1
#ਜੇ_ਅੰਤ /* EGL_KHR_get_all_proc_addresses */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_gl_colorspace
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_gl_colorspace 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_COLORSPACE_KHR             0x309D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_COLORSPACE_SRGB_KHR        0x3089
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_COLORSPACE_ਰੇਖਿਕ_KHR      0x308A
#ਜੇ_ਅੰਤ /* EGL_KHR_gl_colorspace */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_gl_renderbuffer_image
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_gl_renderbuffer_image 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_RENDERBUFFER_KHR           0x30B9
#ਜੇ_ਅੰਤ /* EGL_KHR_gl_renderbuffer_image */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_gl_texture_2D_image
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_gl_texture_2D_image 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_TEXTURE_2D_KHR             0x30B1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_TEXTURE_LEVEL_KHR          0x30BC
#ਜੇ_ਅੰਤ /* EGL_KHR_gl_texture_2D_image */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_gl_texture_3D_image
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_gl_texture_3D_image 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_TEXTURE_3D_KHR             0x30B2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_TEXTURE_ZOFFSET_KHR        0x30BD
#ਜੇ_ਅੰਤ /* EGL_KHR_gl_texture_3D_image */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_gl_texture_cubemap_image
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_gl_texture_cubemap_image 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_TEXTURE_CUBE_MAP_ਸਕਾਰਾਤਮਕ_X_KHR 0x30B3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_X_KHR 0x30B4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_TEXTURE_CUBE_MAP_ਸਕਾਰਾਤਮਕ_Y_KHR 0x30B5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_KHR 0x30B6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_TEXTURE_CUBE_MAP_ਸਕਾਰਾਤਮਕ_Z_KHR 0x30B7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_KHR 0x30B8
#ਜੇ_ਅੰਤ /* EGL_KHR_gl_texture_cubemap_image */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_image
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_image 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ *EGLImageKHR;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NATIVE_PIXMAP_KHR             0x30B0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NO_IMAGE_KHR                  EGL_CAST(EGLImageKHR,0)
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLImageKHR (EGLAPIENTRYP PFNEGLCREATEIMAGEKHRPROC) (EGLDisplay dpy, EGLContext ctx, EGLenum ਨਿਸ਼ਾਨਾ, EGLClient_ਬਫਰ ਬਫਰ_2, ਅਚਲ EGLint *attrib_list);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYIMAGEKHRPROC) (EGLDisplay dpy, EGLImageKHR image);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLImageKHR EGLAPIENTRY eglCreateImageKHR (EGLDisplay dpy, EGLContext ctx, EGLenum ਨਿਸ਼ਾਨਾ, EGLClient_ਬਫਰ ਬਫਰ_2, ਅਚਲ EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyImageKHR (EGLDisplay dpy, EGLImageKHR image);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_KHR_image */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_image_ਅਧਾਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_image_ਅਧਾਰ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_IMAGE_PRESERVED_KHR           0x30D2
#ਜੇ_ਅੰਤ /* EGL_KHR_image_base */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_image_pixmap
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_image_pixmap 1
#ਜੇ_ਅੰਤ /* EGL_KHR_image_pixmap */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_ਤਾਲਾ_surface
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_ਤਾਲਾ_surface 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_READ_SURFACE_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR          0x0001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_WRITE_SURFACE_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR         0x0002
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਤਾਲਾ_SURFACE_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR          0x0080
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_OPTIMAL_FORMAT_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR        0x0100
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਮੇਲ_FORMAT_KHR              0x3043
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_FORMAT_RGB_565_EXACT_KHR      0x30C0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_FORMAT_RGB_565_KHR            0x30C1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_FORMAT_RGBA_8888_EXACT_KHR    0x30C2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_FORMAT_RGBA_8888_KHR          0x30C3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_MAP_PRESERVE_PIXELS_KHR       0x30C4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਤਾਲਾ_USAGE_HINT_KHR           0x30C5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_BITMAP_ਸੂਚਕ_KHR            0x30C6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_BITMAP_PITCH_KHR              0x30C7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_BITMAP_ORIGIN_KHR             0x30C8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_BITMAP_PIXEL_RED_ਵਿੱਥ_KHR   0x30C9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_BITMAP_PIXEL_GREEN_ਵਿੱਥ_KHR 0x30CA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_BITMAP_PIXEL_BLUE_ਵਿੱਥ_KHR  0x30CB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_BITMAP_PIXEL_ALPHA_ਵਿੱਥ_KHR 0x30CC
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_BITMAP_PIXEL_LUMINANCE_ਵਿੱਥ_KHR 0x30CD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਹੇਠਲਾ_ਖੱਬਾ_KHR                0x30CE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਉੱਤਲਾ_ਖੱਬਾ_KHR                0x30CF
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLLOCKSURFACEKHRPROC) (EGLDisplay dpy, EGLSurface surface, ਅਚਲ EGLint *attrib_list);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLUNLOCKSURFACEKHRPROC) (EGLDisplay dpy, EGLSurface surface);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_ਤਾਲਾ_Surface_KHR (EGLDisplay dpy, EGLSurface surface, ਅਚਲ EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglUnlockSurfaceKHR (EGLDisplay dpy, EGLSurface surface);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_KHR_lock_surface */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_ਤਾਲਾ_surface2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_ਤਾਲਾ_surface2 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_BITMAP_PIXEL_ਮਾਪ_KHR         0x3110
#ਜੇ_ਅੰਤ /* EGL_KHR_lock_surface2 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_ਤਾਲਾ_surface3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_ਤਾਲਾ_surface3 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSURFACE64KHRPROC) (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLAttribKHR *ਮੁੱਲ);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQuerySurface64KHR (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLAttribKHR *ਮੁੱਲ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_KHR_lock_surface3 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_mutable_render_ਬਫਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_mutable_render_ਬਫਰ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_MUTABLE_RENDER_ਬਫਰ_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR 0x1000
#ਜੇ_ਅੰਤ /* EGL_KHR_mutable_render_buffer */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_no_config_context
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_no_config_context 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NO_CONFIG_KHR                 EGL_CAST(EGLConfig,0)
#ਜੇ_ਅੰਤ /* EGL_KHR_no_config_context */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_partial_update
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_partial_update 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਬਫਰ_AGE_KHR                0x313D
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLSETDAMAGEREGIONKHRPROC) (EGLDisplay dpy, EGLSurface surface, EGLint *rects, EGLint n_rects);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_ਸੈੱਟ_Damage_Region_KHR (EGLDisplay dpy, EGLSurface surface, EGLint *rects, EGLint n_rects);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_KHR_partial_update */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_platform_android
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_platform_android 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_PLATFORM_ANDROID_KHR          0x3141
#ਜੇ_ਅੰਤ /* EGL_KHR_platform_android */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_platform_gbm
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_platform_gbm 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_PLATFORM_GBM_KHR              0x31D7
#ਜੇ_ਅੰਤ /* EGL_KHR_platform_gbm */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_platform_wayland
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_platform_wayland 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_PLATFORM_WAYLAND_KHR          0x31D8
#ਜੇ_ਅੰਤ /* EGL_KHR_platform_wayland */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_platform_x11
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_platform_x11 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_PLATFORM_X11_KHR              0x31D5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_PLATFORM_X11_SCREEN_KHR       0x31D6
#ਜੇ_ਅੰਤ /* EGL_KHR_platform_x11 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_reusable_sync
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_reusable_sync 1
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ KHRONOS_SUPPORT_INT64
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SYNC_ਸਥਿਤੀ_KHR               0x30F1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SIGNALED_KHR                  0x30F2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_UNSIGNALED_KHR                0x30F3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_TIMEOUT_EXPIRED_KHR           0x30F5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONDITION_SATISFIED_KHR       0x30F6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SYNC_TYPE_KHR                 0x30F7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SYNC_REUSABLE_KHR             0x30FA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SYNC_FLUSH_COMMANDS_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR   0x0001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_FOREVER_KHR                   0xFFFFFFFFFFFFFFFFull
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NO_SYNC_KHR                   EGL_CAST(EGLSyncKHR,0)
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLSIGNALSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLenum ਬਹੁਲਕ);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglSignalSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLenum ਬਹੁਲਕ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* KHRONOS_SUPPORT_INT64 */
#ਜੇ_ਅੰਤ /* EGL_KHR_reusable_sync */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_ਧਾਰਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_ਧਾਰਾ 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ *EGLStreamKHR;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ khronos_uint64_t EGLuint64KHR;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ KHRONOS_SUPPORT_INT64
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NO_ਧਾਰਾ_KHR                 EGL_CAST(EGLStreamKHR,0)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਖਪਤਕਾਰ_LATENCY_USEC_KHR     0x3210
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਉਤਪਾਦਕ_ਚੌਖਟਾ_KHR            0x3212
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਖਪਤਕਾਰ_ਚੌਖਟਾ_KHR            0x3213
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_STATE_KHR              0x3214
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_STATE_CREATED_KHR      0x3215
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_STATE_CONNECTING_KHR   0x3216
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_STATE_ਖਾਲੀ_ਥਾਵਾਂ_KHR        0x3217
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_STATE_NEW_ਚੌਖਟਾ_ਉਪਲਬਧ_KHR 0x3218
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_STATE_OLD_ਚੌਖਟਾ_ਉਪਲਬਧ_KHR 0x3219
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_STATE_DISCONNECTED_KHR 0x321A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_BAD_ਧਾਰਾ_KHR                0x321B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_BAD_STATE_KHR                 0x321C
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLStreamKHR (EGLAPIENTRYP PFNEGLCREATESTREAMKHRPROC) (EGLDisplay dpy, ਅਚਲ EGLint *attrib_list);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSTREAMKHRPROC) (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ, EGLenum attribute, EGLint ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMKHRPROC) (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ, EGLenum attribute, EGLint *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMU64KHRPROC) (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ, EGLenum attribute, EGLuint64KHR *ਮੁੱਲ);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLStreamKHR EGLAPIENTRY egl_Create_ਧਾਰਾ_KHR (EGLDisplay dpy, ਅਚਲ EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY egl_Destroy_ਧਾਰਾ_KHR (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ);
EGLAPI EGLBoolean EGLAPIENTRY egl_ਧਾਰਾ_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ, EGLenum attribute, EGLint ਮੁੱਲ);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_ਧਾਰਾ_KHR (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ, EGLenum attribute, EGLint *ਮੁੱਲ);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryStreamu64KHR (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ, EGLenum attribute, EGLuint64KHR *ਮੁੱਲ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* KHRONOS_SUPPORT_INT64 */
#ਜੇ_ਅੰਤ /* EGL_KHR_stream */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_ਧਾਰਾ_attrib
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_ਧਾਰਾ_attrib 1
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ KHRONOS_SUPPORT_INT64
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLStreamKHR (EGLAPIENTRYP PFNEGLCREATESTREAMATTRIBKHRPROC) (EGLDisplay dpy, ਅਚਲ EGLAttrib *attrib_list);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLSETSTREAMATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ, EGLenum attribute, EGLAttrib ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ, EGLenum attribute, EGLAttrib *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERACQUIREATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ, ਅਚਲ EGLAttrib *attrib_list);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERRELEASEATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ, ਅਚਲ EGLAttrib *attrib_list);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLStreamKHR EGLAPIENTRY egl_Create_ਧਾਰਾ_Attrib_KHR (EGLDisplay dpy, ਅਚਲ EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY egl_ਸੈੱਟ_ਧਾਰਾ_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ, EGLenum attribute, EGLAttrib ਮੁੱਲ);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_ਧਾਰਾ_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ, EGLenum attribute, EGLAttrib *ਮੁੱਲ);
EGLAPI EGLBoolean EGLAPIENTRY egl_ਧਾਰਾ_ਖਪਤਕਾਰ_Acquire_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ, ਅਚਲ EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY egl_ਧਾਰਾ_ਖਪਤਕਾਰ_Release_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ, ਅਚਲ EGLAttrib *attrib_list);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* KHRONOS_SUPPORT_INT64 */
#ਜੇ_ਅੰਤ /* EGL_KHR_stream_attrib */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_ਧਾਰਾ_ਖਪਤਕਾਰ_gltexture
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_ਧਾਰਾ_ਖਪਤਕਾਰ_gltexture 1
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_KHR_ਧਾਰਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਖਪਤਕਾਰ_ACQUIRE_TIMEOUT_USEC_KHR 0x321E
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALKHRPROC) (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERACQUIREKHRPROC) (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERRELEASEKHRPROC) (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_ਧਾਰਾ_ਖਪਤਕਾਰ_GLTexture_External_KHR (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ);
EGLAPI EGLBoolean EGLAPIENTRY egl_ਧਾਰਾ_ਖਪਤਕਾਰ_Acquire_KHR (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ);
EGLAPI EGLBoolean EGLAPIENTRY egl_ਧਾਰਾ_ਖਪਤਕਾਰ_Release_KHR (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_KHR_stream */
#ਜੇ_ਅੰਤ /* EGL_KHR_stream_consumer_gltexture */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_ਧਾਰਾ_cross_process_fd
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_ਧਾਰਾ_cross_process_fd 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੂਰਨ EGLNativeFileDescriptorKHR;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_KHR_ਧਾਰਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NO_FILE_DESCRIPTOR_KHR        EGL_CAST(EGLNativeFileDescriptorKHR,-1)
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLNativeFileDescriptorKHR (EGLAPIENTRYP PFNEGLGETSTREAMFILEDESCRIPTORKHRPROC) (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLStreamKHR (EGLAPIENTRYP PFNEGLCREATESTREAMFROMFILEDESCRIPTORKHRPROC) (EGLDisplay dpy, EGLNativeFileDescriptorKHR file_descriptor);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLNativeFileDescriptorKHR EGLAPIENTRY egl_Get_ਧਾਰਾ_File_Descriptor_KHR (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ);
EGLAPI EGLStreamKHR EGLAPIENTRY egl_Create_ਧਾਰਾ_From_File_Descriptor_KHR (EGLDisplay dpy, EGLNativeFileDescriptorKHR file_descriptor);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_KHR_stream */
#ਜੇ_ਅੰਤ /* EGL_KHR_stream_cross_process_fd */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_ਧਾਰਾ_fifo
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_ਧਾਰਾ_fifo 1
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_KHR_ਧਾਰਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_FIFO_ਲੰਮਾਈ_KHR        0x31FC
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_ਸਮਾਂ_NOW_KHR           0x31FD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_ਸਮਾਂ_ਖਪਤਕਾਰ_KHR      0x31FE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_ਸਮਾਂ_ਉਤਪਾਦਕ_KHR      0x31FF
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMTIMEKHRPROC) (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ, EGLenum attribute, EGLTimeKHR *ਮੁੱਲ);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_ਧਾਰਾ_ਸਮਾਂ_KHR (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ, EGLenum attribute, EGLTimeKHR *ਮੁੱਲ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_KHR_stream */
#ਜੇ_ਅੰਤ /* EGL_KHR_stream_fifo */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_ਧਾਰਾ_ਉਤਪਾਦਕ_aldatalocator
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_ਧਾਰਾ_ਉਤਪਾਦਕ_aldatalocator 1
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_KHR_ਧਾਰਾ
#ਜੇ_ਅੰਤ /* EGL_KHR_stream */
#ਜੇ_ਅੰਤ /* EGL_KHR_stream_producer_aldatalocator */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_ਧਾਰਾ_ਉਤਪਾਦਕ_eglsurface
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_ਧਾਰਾ_ਉਤਪਾਦਕ_eglsurface 1
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_KHR_ਧਾਰਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR                0x0800
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLSurface (EGLAPIENTRYP PFNEGLCREATESTREAMPRODUCERSURFACEKHRPROC) (EGLDisplay dpy, EGLConfig config, EGLStreamKHR ਧਾਰਾ, ਅਚਲ EGLint *attrib_list);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSurface EGLAPIENTRY egl_Create_ਧਾਰਾ_ਉਤਪਾਦਕ_Surface_KHR (EGLDisplay dpy, EGLConfig config, EGLStreamKHR ਧਾਰਾ, ਅਚਲ EGLint *attrib_list);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_KHR_stream */
#ਜੇ_ਅੰਤ /* EGL_KHR_stream_producer_eglsurface */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_surfaceless_context
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_surfaceless_context 1
#ਜੇ_ਅੰਤ /* EGL_KHR_surfaceless_context */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_ਅਦਲਾ_ਬਦਲੀ_buffers_with_damage
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_ਅਦਲਾ_ਬਦਲੀ_buffers_with_damage 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSWITHDAMAGEKHRPROC) (EGLDisplay dpy, EGLSurface surface, ਅਚਲ EGLint *rects, EGLint n_rects);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_ਅਦਲਾ_ਬਦਲੀ_Buffers_With_Damage_KHR (EGLDisplay dpy, EGLSurface surface, ਅਚਲ EGLint *rects, EGLint n_rects);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_KHR_swap_buffers_with_damage */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_vg_ਮਾਪਾ_image
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_vg_ਮਾਪਾ_image 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_VG_ਮਾਪਾ_IMAGE_KHR           0x30BA
#ਜੇ_ਅੰਤ /* EGL_KHR_vg_parent_image */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_KHR_wait_sync
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_KHR_wait_sync 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLint (EGLAPIENTRYP PFNEGLWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLint EGLAPIENTRY eglWaitSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_KHR_wait_sync */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_ANDROID_GLES_layers
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ANDROID_GLES_layers 1
#ਜੇ_ਅੰਤ /* EGL_ANDROID_GLES_layers */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_ANDROID_blob_cache
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ANDROID_blob_cache 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ khronos_ssize_t EGLsizeiANDROID;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (*EGLSetBlobFuncANDROID) (ਅਚਲ ਖਾਲੀ *ਕੁੰਜੀ, EGLsizeiANDROID ਕੁੰਜੀ_ਮਾਪ_2, ਅਚਲ ਖਾਲੀ *ਮੁੱਲ, EGLsizeiANDROID ਮੁੱਲ_ਮਾਪ_2);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLsizeiANDROID (*EGLGetBlobFuncANDROID) (ਅਚਲ ਖਾਲੀ *ਕੁੰਜੀ, EGLsizeiANDROID ਕੁੰਜੀ_ਮਾਪ_2, ਖਾਲੀ *ਮੁੱਲ, EGLsizeiANDROID ਮੁੱਲ_ਮਾਪ_2);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (EGLAPIENTRYP PFNEGLSETBLOBCACHEFUNCSANDROIDPROC) (EGLDisplay dpy, EGLSetBlobFuncANDROID ਸੈੱਟ, EGLGetBlobFuncANDROID get);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI ਖਾਲੀ EGLAPIENTRY egl_ਸੈੱਟ_Blob_Cache_Funcs_ANDROID (EGLDisplay dpy, EGLSetBlobFuncANDROID ਸੈੱਟ, EGLGetBlobFuncANDROID get);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_ANDROID_blob_cache */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_ANDROID_create_native_client_ਬਫਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ANDROID_create_native_client_ਬਫਰ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NATIVE_ਬਫਰ_USAGE_ANDROID   0x3143
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NATIVE_ਬਫਰ_USAGE_PROTECTED_ਦੋਆਧਾਰੀ_ਅੰਕ_ANDROID 0x00000001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NATIVE_ਬਫਰ_USAGE_RENDERBUFFER_ਦੋਆਧਾਰੀ_ਅੰਕ_ANDROID 0x00000002
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NATIVE_ਬਫਰ_USAGE_TEXTURE_ਦੋਆਧਾਰੀ_ਅੰਕ_ANDROID 0x00000004
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLClient_ਬਫਰ (EGLAPIENTRYP PFNEGLCREATENATIVECLIENTBUFFERANDROIDPROC) (ਅਚਲ EGLint *attrib_list);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLClient_ਬਫਰ EGLAPIENTRY egl_Create_Native_Client_ਬਫਰ_ANDROID (ਅਚਲ EGLint *attrib_list);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_ANDROID_create_native_client_buffer */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_ANDROID_framebuffer_ਨਿਸ਼ਾਨਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ANDROID_framebuffer_ਨਿਸ਼ਾਨਾ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_FRAMEBUFFER_ਨਿਸ਼ਾਨਾ_ANDROID    0x3147
#ਜੇ_ਅੰਤ /* EGL_ANDROID_framebuffer_target */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_ANDROID_front_ਬਫਰ_auto_refresh
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ANDROID_front_ਬਫਰ_auto_refresh 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_FRONT_ਬਫਰ_AUTO_REFRESH_ANDROID 0x314C
#ਜੇ_ਅੰਤ /* EGL_ANDROID_front_buffer_auto_refresh */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_ANDROID_get_ਚੌਖਟਾ_timestamps
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ANDROID_get_ਚੌਖਟਾ_timestamps 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ khronos_stime_nanoseconds_t EGLnsecsANDROID;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_TIMESTAMP_PENDING_ANDROID     EGL_CAST(EGLnsecsANDROID,-2)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_TIMESTAMP_INVALID_ANDROID     EGL_CAST(EGLnsecsANDROID,-1)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_TIMESTAMPS_ANDROID            0x3430
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਸੰਯੁਕਤ_DEADLINE_ANDROID    0x3431
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਸੰਯੁਕਤ_INTERVAL_ANDROID    0x3432
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਸੰਯੁਕਤ_ਮੰਜ਼ਿਲ_PRESENT_LATENCY_ANDROID 0x3433
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_REQUESTED_PRESENT_ਸਮਾਂ_ANDROID 0x3434
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_RENDERING_COMPLETE_ਸਮਾਂ_ANDROID 0x3435
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_COMPOSITION_LATCH_ਸਮਾਂ_ANDROID 0x3436
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਪਹਿਲਾ_COMPOSITION_ਸ਼ੁਰੂ_ਸਮਾਂ_ANDROID 0x3437
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਆਖਰੀ_COMPOSITION_ਸ਼ੁਰੂ_ਸਮਾਂ_ANDROID 0x3438
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਪਹਿਲਾ_COMPOSITION_GPU_ਮੁਕੰਮਲ_ਸਮਾਂ_ANDROID 0x3439
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DISPLAY_PRESENT_ਸਮਾਂ_ANDROID  0x343A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਕਤਾਰ_ਤੋਂ_ਕੱਢੋ_READY_ਸਮਾਂ_ANDROID    0x343B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_READS_ਪੂਰਾ_ਸਮਾਂ_ANDROID       0x343C
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLGETCOMPOSITORTIMINGSUPPORTEDANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLint name);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLGETCOMPOSITORTIMINGANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLint ਅੰਕ_Timestamps,  ਅਚਲ EGLint *ਨਾਂ, EGLnsecsANDROID *ਮੁੱਲਾਂ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLGETNEXTFRAMEIDANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR *ਚੌਖਟਾ_Id);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLGETFRAMETIMESTAMPSUPPORTEDANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLint timestamp);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLGETFRAMETIMESTAMPSANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR ਚੌਖਟਾ_Id, EGLint ਅੰਕ_Timestamps,  ਅਚਲ EGLint *timestamps, EGLnsecsANDROID *ਮੁੱਲਾਂ);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglGetCompositorTimingSupportedANDROID (EGLDisplay dpy, EGLSurface surface, EGLint name);
EGLAPI EGLBoolean EGLAPIENTRY eglGetCompositorTimingANDROID (EGLDisplay dpy, EGLSurface surface, EGLint ਅੰਕ_Timestamps,  ਅਚਲ EGLint *ਨਾਂ, EGLnsecsANDROID *ਮੁੱਲਾਂ);
EGLAPI EGLBoolean EGLAPIENTRY egl_Get_ਅਗਲਾ_ਚੌਖਟਾ_Id_ANDROID (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR *ਚੌਖਟਾ_Id);
EGLAPI EGLBoolean EGLAPIENTRY egl_Get_ਚੌਖਟਾ_Timestamp_Supported_ANDROID (EGLDisplay dpy, EGLSurface surface, EGLint timestamp);
EGLAPI EGLBoolean EGLAPIENTRY egl_Get_ਚੌਖਟਾ_Timestamps_ANDROID (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR ਚੌਖਟਾ_Id, EGLint ਅੰਕ_Timestamps,  ਅਚਲ EGLint *timestamps, EGLnsecsANDROID *ਮੁੱਲਾਂ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_ANDROID_get_frame_timestamps */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_ANDROID_get_native_client_ਬਫਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ANDROID_get_native_client_ਬਫਰ 1
ਬਣਤਰ AHardware_ਬਫਰ;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLClient_ਬਫਰ (EGLAPIENTRYP PFNEGLGETNATIVECLIENTBUFFERANDROIDPROC) (ਅਚਲ ਬਣਤਰ AHardware_ਬਫਰ *ਬਫਰ_2);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLClient_ਬਫਰ EGLAPIENTRY egl_Get_Native_Client_ਬਫਰ_ANDROID (ਅਚਲ ਬਣਤਰ AHardware_ਬਫਰ *ਬਫਰ_2);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_ANDROID_get_native_client_buffer */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_ANDROID_image_native_ਬਫਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ANDROID_image_native_ਬਫਰ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NATIVE_ਬਫਰ_ANDROID         0x3140
#ਜੇ_ਅੰਤ /* EGL_ANDROID_image_native_buffer */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_ANDROID_native_fence_sync
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ANDROID_native_fence_sync 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SYNC_NATIVE_FENCE_ANDROID     0x3144
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SYNC_NATIVE_FENCE_FD_ANDROID  0x3145
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SYNC_NATIVE_FENCE_SIGNALED_ANDROID 0x3146
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NO_NATIVE_FENCE_FD_ANDROID    -1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLint (EGLAPIENTRYP PFNEGLDUPNATIVEFENCEFDANDROIDPROC) (EGLDisplay dpy, EGLSyncKHR sync);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLint EGLAPIENTRY eglDupNativeFenceFDANDROID (EGLDisplay dpy, EGLSyncKHR sync);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_ANDROID_native_fence_sync */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_ANDROID_presentation_ਸਮਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ANDROID_presentation_ਸਮਾਂ 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLPRESENTATIONTIMEANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLnsecsANDROID ਸਮਾਂ);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Presentation_ਸਮਾਂ_ANDROID (EGLDisplay dpy, EGLSurface surface, EGLnsecsANDROID ਸਮਾਂ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_ANDROID_presentation_time */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_ANDROID_recordable
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ANDROID_recordable 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_RECORDABLE_ANDROID            0x3142
#ਜੇ_ਅੰਤ /* EGL_ANDROID_recordable */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_ANDROID_telemetry_hint
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ANDROID_telemetry_hint 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_TELEMETRY_HINT_ANDROID        0x3570
#ਜੇ_ਅੰਤ /* EGL_ANDROID_telemetry_hint */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_ANGLE_d3d_share_handle_client_ਬਫਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ANGLE_d3d_share_handle_client_ਬਫਰ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_D3D_TEXTURE_2D_SHARE_HANDLE_ANGLE 0x3200
#ਜੇ_ਅੰਤ /* EGL_ANGLE_d3d_share_handle_client_buffer */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_ANGLE_device_d3d
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ANGLE_device_d3d 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_D3D9_DEVICE_ANGLE             0x33A0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_D3D11_DEVICE_ANGLE            0x33A1
#ਜੇ_ਅੰਤ /* EGL_ANGLE_device_d3d */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_ANGLE_query_surface_ਸੂਚਕ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ANGLE_query_surface_ਸੂਚਕ 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSURFACEPOINTERANGLEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint attribute, ਖਾਲੀ **ਮੁੱਲ);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Surface_ਸੂਚਕ_ANGLE (EGLDisplay dpy, EGLSurface surface, EGLint attribute, ਖਾਲੀ **ਮੁੱਲ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_ANGLE_query_surface_pointer */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_ANGLE_surface_d3d_texture_2d_share_handle
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ANGLE_surface_d3d_texture_2d_share_handle 1
#ਜੇ_ਅੰਤ /* EGL_ANGLE_surface_d3d_texture_2d_share_handle */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_ANGLE_sync_control_ਦਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ANGLE_sync_control_ਦਰ 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLGETMSCRATEANGLEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint *numerator, EGLint *denominator);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Get_Msc_ਦਰ_ANGLE (EGLDisplay dpy, EGLSurface surface, EGLint *numerator, EGLint *denominator);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_ANGLE_sync_control_rate */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_ANGLE_ਖਿੜਕੀ_fixed_ਮਾਪ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ANGLE_ਖਿੜਕੀ_fixed_ਮਾਪ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_FIXED_ਮਾਪ_ANGLE              0x3201
#ਜੇ_ਅੰਤ /* EGL_ANGLE_window_fixed_size */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_ARM_image_format
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ARM_image_format 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_COLOR_COMPONENT_TYPE_UNSIGNED_INTEGER_ARM 0x3287
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_COLOR_COMPONENT_TYPE_INTEGER_ARM 0x3288
#ਜੇ_ਅੰਤ /* EGL_ARM_image_format */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_ARM_implicit_external_sync
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ARM_implicit_external_sync 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SYNC_ਪੂਰਵ_COMMANDS_IMPLICIT_EXTERNAL_ARM 0x328A
#ਜੇ_ਅੰਤ /* EGL_ARM_implicit_external_sync */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_ARM_pixmap_multisample_discard
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ARM_pixmap_multisample_discard 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DISCARD_SAMPLES_ARM           0x3286
#ਜੇ_ਅੰਤ /* EGL_ARM_pixmap_multisample_discard */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_bind_ਮੰਜ਼ਿਲ_front
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_bind_ਮੰਜ਼ਿਲ_front 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_FRONT_ਬਫਰ_EXT              0x3464
#ਜੇ_ਅੰਤ /* EGL_EXT_bind_to_front */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_ਬਫਰ_age
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_ਬਫਰ_age 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਬਫਰ_AGE_EXT                0x313D
#ਜੇ_ਅੰਤ /* EGL_EXT_buffer_age */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_client_extensions
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_client_extensions 1
#ਜੇ_ਅੰਤ /* EGL_EXT_client_extensions */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_client_sync
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_client_sync 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SYNC_CLIENT_EXT               0x3364
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SYNC_CLIENT_SIGNAL_EXT        0x3365
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLCLIENTSIGNALSYNCEXTPROC) (EGLDisplay dpy, EGLSync sync, ਅਚਲ EGLAttrib *attrib_list);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglClientSignalSyncEXT (EGLDisplay dpy, EGLSync sync, ਅਚਲ EGLAttrib *attrib_list);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_EXT_client_sync */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_compositor
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_compositor 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_PRIMARY_COMPOSITOR_CONTEXT_EXT 0x3460
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXTERNAL_REF_ID_EXT           0x3461
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_COMPOSITOR_DROP_NEWEST_ਚੌਖਟਾ_EXT 0x3462
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_COMPOSITOR_KEEP_NEWEST_ਚੌਖਟਾ_EXT 0x3463
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETCONTEXTLISTEXTPROC) (ਅਚਲ EGLint *external_ref_ids, EGLint ਅੰਕ_entries);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETCONTEXTATTRIBUTESEXTPROC) (EGLint external_ref_id, ਅਚਲ EGLint *context_ਗੁਣ, EGLint ਅੰਕ_entries);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETWINDOWLISTEXTPROC) (EGLint external_ref_id, ਅਚਲ EGLint *external_win_ids, EGLint ਅੰਕ_entries);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETWINDOWATTRIBUTESEXTPROC) (EGLint external_win_id, ਅਚਲ EGLint *ਖਿੜਕੀ_ਗੁਣ, EGLint ਅੰਕ_entries);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORBINDTEXWINDOWEXTPROC) (EGLint external_win_id);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETSIZEEXTPROC) (EGLint external_win_id, EGLint ਚੌੜਾਈ, EGLint ਉਚਾਈ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSWAPPOLICYEXTPROC) (EGLint external_win_id, EGLint policy);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_ਸੈੱਟ_Context_List_EXT (ਅਚਲ EGLint *external_ref_ids, EGLint ਅੰਕ_entries);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_ਸੈੱਟ_Context_ਗੁਣ_EXT (EGLint external_ref_id, ਅਚਲ EGLint *context_ਗੁਣ, EGLint ਅੰਕ_entries);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_ਸੈੱਟ_ਖਿੜਕੀ_List_EXT (EGLint external_ref_id, ਅਚਲ EGLint *external_win_ids, EGLint ਅੰਕ_entries);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_ਸੈੱਟ_ਖਿੜਕੀ_ਗੁਣ_EXT (EGLint external_win_id, ਅਚਲ EGLint *ਖਿੜਕੀ_ਗੁਣ, EGLint ਅੰਕ_entries);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_Bind_Tex_ਖਿੜਕੀ_EXT (EGLint external_win_id);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_ਸੈੱਟ_ਮਾਪ_EXT (EGLint external_win_id, EGLint ਚੌੜਾਈ, EGLint ਉਚਾਈ);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_ਅਦਲਾ_ਬਦਲੀ_Policy_EXT (EGLint external_win_id, EGLint policy);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_EXT_compositor */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_config_select_ਸਮੂਹ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_config_select_ਸਮੂਹ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONFIG_SELECT_ਸਮੂਹ_EXT       0x34C0
#ਜੇ_ਅੰਤ /* EGL_EXT_config_select_group */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_create_context_robustness
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_create_context_robustness 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT 0x30BF
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_EXT 0x3138
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NO_RESET_NOTIFICATION_EXT     0x31BE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_LOSE_CONTEXT_ON_RESET_EXT     0x31BF
#ਜੇ_ਅੰਤ /* EGL_EXT_create_context_robustness */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_device_ਅਧਾਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_device_ਅਧਾਰ 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ *EGLDeviceEXT;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NO_DEVICE_EXT                 EGL_CAST(EGLDeviceEXT,0)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_BAD_DEVICE_EXT                0x322B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DEVICE_EXT                    0x322C
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICEATTRIBEXTPROC) (EGLDeviceEXT device, EGLint attribute, EGLAttrib *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਅਚਲ ਅੱਖਰ *(EGLAPIENTRYP PFNEGLQUERYDEVICESTRINGEXTPROC) (EGLDeviceEXT device, EGLint name);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICESEXTPROC) (EGLint max_devices, EGLDeviceEXT *devices, EGLint *ਅੰਕ_devices);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDISPLAYATTRIBEXTPROC) (EGLDisplay dpy, EGLint attribute, EGLAttrib *ਮੁੱਲ);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDeviceAttribEXT (EGLDeviceEXT device, EGLint attribute, EGLAttrib *ਮੁੱਲ);
EGLAPI ਅਚਲ ਅੱਖਰ *EGLAPIENTRY eglQueryDeviceStringEXT (EGLDeviceEXT device, EGLint name);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDevicesEXT (EGLint max_devices, EGLDeviceEXT *devices, EGLint *ਅੰਕ_devices);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDisplayAttribEXT (EGLDisplay dpy, EGLint attribute, EGLAttrib *ਮੁੱਲ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_EXT_device_base */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_device_drm
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_device_drm 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DRM_DEVICE_FILE_EXT           0x3233
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DRM_MASTER_FD_EXT             0x333C
#ਜੇ_ਅੰਤ /* EGL_EXT_device_drm */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_device_drm_render_ਗੰਢ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_device_drm_render_ਗੰਢ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DRM_RENDER_ਗੰਢ_FILE_EXT      0x3377
#ਜੇ_ਅੰਤ /* EGL_EXT_device_drm_render_node */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_device_enumeration
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_device_enumeration 1
#ਜੇ_ਅੰਤ /* EGL_EXT_device_enumeration */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_device_openwf
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_device_openwf 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_OPENWF_DEVICE_ID_EXT          0x3237
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_OPENWF_DEVICE_EXT             0x333D
#ਜੇ_ਅੰਤ /* EGL_EXT_device_openwf */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_device_persistent_id
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_device_persistent_id 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DEVICE_UUID_EXT               0x335C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DRIVER_UUID_EXT               0x335D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DRIVER_NAME_EXT               0x335E
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICEBINARYEXTPROC) (EGLDeviceEXT device, EGLint name, EGLint max_ਮਾਪ, ਖਾਲੀ *ਮੁੱਲ, EGLint *ਮਾਪ);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Device_ਦੁਆਧਾਰੀ_EXT (EGLDeviceEXT device, EGLint name, EGLint max_ਮਾਪ, ਖਾਲੀ *ਮੁੱਲ, EGLint *ਮਾਪ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_EXT_device_persistent_id */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_device_query
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_device_query 1
#ਜੇ_ਅੰਤ /* EGL_EXT_device_query */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_device_query_name
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_device_query_name 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_RENDERER_EXT                  0x335F
#ਜੇ_ਅੰਤ /* EGL_EXT_device_query_name */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_device_type
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_device_type 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DEVICE_TYPE_EXT               0x3590
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DEVICE_TYPE_OTHER_EXT         0x3591
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DEVICE_TYPE_INTEGRATED_GPU_EXT 0x3592
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DEVICE_TYPE_DISCRETE_GPU_EXT  0x3593
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DEVICE_TYPE_CPU_EXT           0x3594
#ਜੇ_ਅੰਤ /* EGL_EXT_device_type */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_display_alloc
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_display_alloc 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ALLOC_NEW_DISPLAY_EXT         0x3379
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYDISPLAYEXTPROC) (EGLDisplay dpy);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyDisplayEXT (EGLDisplay dpy);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_EXT_display_alloc */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_explicit_device
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_explicit_device 1
#ਜੇ_ਅੰਤ /* EGL_EXT_explicit_device */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_gl_colorspace_bt2020_hlg
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_gl_colorspace_bt2020_hlg 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_COLORSPACE_BT2020_HLG_EXT  0x3540
#ਜੇ_ਅੰਤ /* EGL_EXT_gl_colorspace_bt2020_hlg */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_gl_colorspace_bt2020_ਰੇਖਿਕ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_gl_colorspace_bt2020_ਰੇਖਿਕ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_COLORSPACE_BT2020_ਰੇਖਿਕ_EXT 0x333F
#ਜੇ_ਅੰਤ /* EGL_EXT_gl_colorspace_bt2020_linear */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_gl_colorspace_bt2020_pq
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_gl_colorspace_bt2020_pq 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_COLORSPACE_BT2020_PQ_EXT   0x3340
#ਜੇ_ਅੰਤ /* EGL_EXT_gl_colorspace_bt2020_pq */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_gl_colorspace_display_p3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_gl_colorspace_display_p3 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_COLORSPACE_DISPLAY_P3_EXT  0x3363
#ਜੇ_ਅੰਤ /* EGL_EXT_gl_colorspace_display_p3 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_gl_colorspace_display_p3_ਰੇਖਿਕ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_gl_colorspace_display_p3_ਰੇਖਿਕ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_COLORSPACE_DISPLAY_P3_ਰੇਖਿਕ_EXT 0x3362
#ਜੇ_ਅੰਤ /* EGL_EXT_gl_colorspace_display_p3_linear */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_gl_colorspace_display_p3_passthrough
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_gl_colorspace_display_p3_passthrough 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_COLORSPACE_DISPLAY_P3_PASSTHROUGH_EXT 0x3490
#ਜੇ_ਅੰਤ /* EGL_EXT_gl_colorspace_display_p3_passthrough */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_gl_colorspace_scrgb
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_gl_colorspace_scrgb 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_COLORSPACE_SCRGB_EXT       0x3351
#ਜੇ_ਅੰਤ /* EGL_EXT_gl_colorspace_scrgb */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_gl_colorspace_scrgb_ਰੇਖਿਕ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_gl_colorspace_scrgb_ਰੇਖਿਕ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_COLORSPACE_SCRGB_ਰੇਖਿਕ_EXT 0x3350
#ਜੇ_ਅੰਤ /* EGL_EXT_gl_colorspace_scrgb_linear */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_image_dma_buf_import
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_image_dma_buf_import 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_LINUX_DMA_BUF_EXT             0x3270
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_LINUX_DRM_FOURCC_EXT          0x3271
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DMA_BUF_PLANE0_FD_EXT         0x3272
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DMA_BUF_PLANE0_ਵਿੱਥ_EXT     0x3273
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DMA_BUF_PLANE0_PITCH_EXT      0x3274
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DMA_BUF_PLANE1_FD_EXT         0x3275
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DMA_BUF_PLANE1_ਵਿੱਥ_EXT     0x3276
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DMA_BUF_PLANE1_PITCH_EXT      0x3277
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DMA_BUF_PLANE2_FD_EXT         0x3278
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DMA_BUF_PLANE2_ਵਿੱਥ_EXT     0x3279
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DMA_BUF_PLANE2_PITCH_EXT      0x327A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_YUV_COLOR_SPACE_HINT_EXT      0x327B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SAMPLE_RANGE_HINT_EXT         0x327C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_YUV_CHROMA_HORIZONTAL_SITING_HINT_EXT 0x327D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_YUV_CHROMA_VERTICAL_SITING_HINT_EXT 0x327E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ITU_REC601_EXT                0x327F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ITU_REC709_EXT                0x3280
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ITU_REC2020_EXT               0x3281
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_YUV_ਭਰਿਆ_RANGE_EXT            0x3282
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_YUV_NARROW_RANGE_EXT          0x3283
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_YUV_CHROMA_SITING_0_EXT       0x3284
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_YUV_CHROMA_SITING_0_5_EXT     0x3285
#ਜੇ_ਅੰਤ /* EGL_EXT_image_dma_buf_import */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_image_dma_buf_import_modifiers
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_image_dma_buf_import_modifiers 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DMA_BUF_PLANE3_FD_EXT         0x3440
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DMA_BUF_PLANE3_ਵਿੱਥ_EXT     0x3441
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DMA_BUF_PLANE3_PITCH_EXT      0x3442
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DMA_BUF_PLANE0_MODIFIER_LO_EXT 0x3443
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DMA_BUF_PLANE0_MODIFIER_HI_EXT 0x3444
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DMA_BUF_PLANE1_MODIFIER_LO_EXT 0x3445
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DMA_BUF_PLANE1_MODIFIER_HI_EXT 0x3446
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DMA_BUF_PLANE2_MODIFIER_LO_EXT 0x3447
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DMA_BUF_PLANE2_MODIFIER_HI_EXT 0x3448
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DMA_BUF_PLANE3_MODIFIER_LO_EXT 0x3449
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DMA_BUF_PLANE3_MODIFIER_HI_EXT 0x344A
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDMABUFFORMATSEXTPROC) (EGLDisplay dpy, EGLint max_formats, EGLint *formats, EGLint *ਅੰਕ_formats);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDMABUFMODIFIERSEXTPROC) (EGLDisplay dpy, EGLint format, EGLint max_modifiers, EGLuint64KHR *modifiers, EGLBoolean *external_only, EGLint *ਅੰਕ_modifiers);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDmaBufFormatsEXT (EGLDisplay dpy, EGLint max_formats, EGLint *formats, EGLint *ਅੰਕ_formats);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDmaBufModifiersEXT (EGLDisplay dpy, EGLint format, EGLint max_modifiers, EGLuint64KHR *modifiers, EGLBoolean *external_only, EGLint *ਅੰਕ_modifiers);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_EXT_image_dma_buf_import_modifiers */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_image_gl_colorspace
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_image_gl_colorspace 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GL_COLORSPACE_DEFAULT_EXT     0x314D
#ਜੇ_ਅੰਤ /* EGL_EXT_image_gl_colorspace */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_image_implicit_sync_control
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_image_implicit_sync_control 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_IMPORT_SYNC_TYPE_EXT          0x3470
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_IMPORT_IMPLICIT_SYNC_EXT      0x3471
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_IMPORT_EXPLICIT_SYNC_EXT      0x3472
#ਜੇ_ਅੰਤ /* EGL_EXT_image_implicit_sync_control */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_multiview_ਖਿੜਕੀ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_multiview_ਖਿੜਕੀ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_MULTIVIEW_VIEW_ਗਿਣਤੀ_EXT      0x3134
#ਜੇ_ਅੰਤ /* EGL_EXT_multiview_window */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_output_ਅਧਾਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_output_ਅਧਾਰ 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ *EGLOutputLayerEXT;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ *EGLOutput_ਪੋਰਟ_EXT;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NO_OUTPUT_LAYER_EXT           EGL_CAST(EGLOutputLayerEXT,0)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NO_OUTPUT_ਪੋਰਟ_EXT            EGL_CAST(EGLOutput_ਪੋਰਟ_EXT,0)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_BAD_OUTPUT_LAYER_EXT          0x322D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_BAD_OUTPUT_ਪੋਰਟ_EXT           0x322E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਅਦਲਾ_ਬਦਲੀ_INTERVAL_EXT             0x322F
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLGETOUTPUTLAYERSEXTPROC) (EGLDisplay dpy, ਅਚਲ EGLAttrib *attrib_list, EGLOutputLayerEXT *layers, EGLint max_layers, EGLint *ਅੰਕ_layers);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLGETOUTPUTPORTSEXTPROC) (EGLDisplay dpy, ਅਚਲ EGLAttrib *attrib_list, EGLOutput_ਪੋਰਟ_EXT *ports, EGLint max_ports, EGLint *ਅੰਕ_ports);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLOUTPUTLAYERATTRIBEXTPROC) (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYOUTPUTLAYERATTRIBEXTPROC) (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਅਚਲ ਅੱਖਰ *(EGLAPIENTRYP PFNEGLQUERYOUTPUTLAYERSTRINGEXTPROC) (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint name);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLOUTPUTPORTATTRIBEXTPROC) (EGLDisplay dpy, EGLOutput_ਪੋਰਟ_EXT ਪੋਰਟ, EGLint attribute, EGLAttrib ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYOUTPUTPORTATTRIBEXTPROC) (EGLDisplay dpy, EGLOutput_ਪੋਰਟ_EXT ਪੋਰਟ, EGLint attribute, EGLAttrib *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਅਚਲ ਅੱਖਰ *(EGLAPIENTRYP PFNEGLQUERYOUTPUTPORTSTRINGEXTPROC) (EGLDisplay dpy, EGLOutput_ਪੋਰਟ_EXT ਪੋਰਟ, EGLint name);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglGetOutputLayersEXT (EGLDisplay dpy, ਅਚਲ EGLAttrib *attrib_list, EGLOutputLayerEXT *layers, EGLint max_layers, EGLint *ਅੰਕ_layers);
EGLAPI EGLBoolean EGLAPIENTRY eglGetOutputPortsEXT (EGLDisplay dpy, ਅਚਲ EGLAttrib *attrib_list, EGLOutput_ਪੋਰਟ_EXT *ports, EGLint max_ports, EGLint *ਅੰਕ_ports);
EGLAPI EGLBoolean EGLAPIENTRY eglOutputLayerAttribEXT (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib ਮੁੱਲ);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryOutputLayerAttribEXT (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib *ਮੁੱਲ);
EGLAPI ਅਚਲ ਅੱਖਰ *EGLAPIENTRY eglQueryOutputLayerStringEXT (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint name);
EGLAPI EGLBoolean EGLAPIENTRY egl_Output_ਪੋਰਟ_Attrib_EXT (EGLDisplay dpy, EGLOutput_ਪੋਰਟ_EXT ਪੋਰਟ, EGLint attribute, EGLAttrib ਮੁੱਲ);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Output_ਪੋਰਟ_Attrib_EXT (EGLDisplay dpy, EGLOutput_ਪੋਰਟ_EXT ਪੋਰਟ, EGLint attribute, EGLAttrib *ਮੁੱਲ);
EGLAPI ਅਚਲ ਅੱਖਰ *EGLAPIENTRY egl_Query_Output_ਪੋਰਟ_String_EXT (EGLDisplay dpy, EGLOutput_ਪੋਰਟ_EXT ਪੋਰਟ, EGLint name);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_EXT_output_base */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_output_drm
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_output_drm 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DRM_CRTC_EXT                  0x3234
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DRM_PLANE_EXT                 0x3235
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DRM_CONNECTOR_EXT             0x3236
#ਜੇ_ਅੰਤ /* EGL_EXT_output_drm */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_output_openwf
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_output_openwf 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_OPENWF_PIPELINE_ID_EXT        0x3238
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_OPENWF_ਪੋਰਟ_ID_EXT            0x3239
#ਜੇ_ਅੰਤ /* EGL_EXT_output_openwf */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_pixel_format_float
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_pixel_format_float 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_COLOR_COMPONENT_TYPE_EXT      0x3339
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_COLOR_COMPONENT_TYPE_FIXED_EXT 0x333A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT 0x333B
#ਜੇ_ਅੰਤ /* EGL_EXT_pixel_format_float */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_platform_ਅਧਾਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_platform_ਅਧਾਰ 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYEXTPROC) (EGLenum platform, ਖਾਲੀ *native_display, ਅਚਲ EGLint *attrib_list);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLSurface (EGLAPIENTRYP PFNEGLCREATEPLATFORMWINDOWSURFACEEXTPROC) (EGLDisplay dpy, EGLConfig config, ਖਾਲੀ *native_ਖਿੜਕੀ, ਅਚਲ EGLint *attrib_list);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLSurface (EGLAPIENTRYP PFNEGLCREATEPLATFORMPIXMAPSURFACEEXTPROC) (EGLDisplay dpy, EGLConfig config, ਖਾਲੀ *native_pixmap, ਅਚਲ EGLint *attrib_list);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLDisplay EGLAPIENTRY eglGetPlatformDisplayEXT (EGLenum platform, ਖਾਲੀ *native_display, ਅਚਲ EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY egl_Create_Platform_ਖਿੜਕੀ_Surface_EXT (EGLDisplay dpy, EGLConfig config, ਖਾਲੀ *native_ਖਿੜਕੀ, ਅਚਲ EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePlatformPixmapSurfaceEXT (EGLDisplay dpy, EGLConfig config, ਖਾਲੀ *native_pixmap, ਅਚਲ EGLint *attrib_list);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_EXT_platform_base */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_platform_device
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_platform_device 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_PLATFORM_DEVICE_EXT           0x313F
#ਜੇ_ਅੰਤ /* EGL_EXT_platform_device */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_platform_wayland
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_platform_wayland 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_PLATFORM_WAYLAND_EXT          0x31D8
#ਜੇ_ਅੰਤ /* EGL_EXT_platform_wayland */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_platform_x11
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_platform_x11 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_PLATFORM_X11_EXT              0x31D5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_PLATFORM_X11_SCREEN_EXT       0x31D6
#ਜੇ_ਅੰਤ /* EGL_EXT_platform_x11 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_platform_xcb
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_platform_xcb 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_PLATFORM_XCB_EXT              0x31DC
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_PLATFORM_XCB_SCREEN_EXT       0x31DE
#ਜੇ_ਅੰਤ /* EGL_EXT_platform_xcb */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_present_opaque
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_present_opaque 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_PRESENT_OPAQUE_EXT            0x31DF
#ਜੇ_ਅੰਤ /* EGL_EXT_present_opaque */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_protected_content
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_protected_content 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_PROTECTED_CONTENT_EXT         0x32C0
#ਜੇ_ਅੰਤ /* EGL_EXT_protected_content */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_protected_surface
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_protected_surface 1
#ਜੇ_ਅੰਤ /* EGL_EXT_protected_surface */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_query_reset_notification_strategy
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_query_reset_notification_strategy 1
#ਜੇ_ਅੰਤ /* EGL_EXT_query_reset_notification_strategy */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_ਧਾਰਾ_ਖਪਤਕਾਰ_egloutput
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_ਧਾਰਾ_ਖਪਤਕਾਰ_egloutput 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMEROUTPUTEXTPROC) (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ, EGLOutputLayerEXT layer);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_ਧਾਰਾ_ਖਪਤਕਾਰ_Output_EXT (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ, EGLOutputLayerEXT layer);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_EXT_stream_consumer_egloutput */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_surface_CTA861_3_metadata
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_surface_CTA861_3_metadata 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CTA861_3_MAX_CONTENT_LIGHT_LEVEL_EXT 0x3360
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CTA861_3_MAX_ਚੌਖਟਾ_ਔਸਤਨ_LEVEL_EXT 0x3361
#ਜੇ_ਅੰਤ /* EGL_EXT_surface_CTA861_3_metadata */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_surface_SMPTE2086_metadata
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_surface_SMPTE2086_metadata 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SMPTE2086_DISPLAY_PRIMARY_RX_EXT 0x3341
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SMPTE2086_DISPLAY_PRIMARY_RY_EXT 0x3342
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SMPTE2086_DISPLAY_PRIMARY_GX_EXT 0x3343
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SMPTE2086_DISPLAY_PRIMARY_GY_EXT 0x3344
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SMPTE2086_DISPLAY_PRIMARY_BX_EXT 0x3345
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SMPTE2086_DISPLAY_PRIMARY_BY_EXT 0x3346
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SMPTE2086_WHITE_ਬਿੰਦੂ_X_EXT   0x3347
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SMPTE2086_WHITE_ਬਿੰਦੂ_Y_EXT   0x3348
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SMPTE2086_MAX_LUMINANCE_EXT   0x3349
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SMPTE2086_MIN_LUMINANCE_EXT   0x334A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_METADATA_SCALING_EXT          50000
#ਜੇ_ਅੰਤ /* EGL_EXT_surface_SMPTE2086_metadata */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_surface_compression
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_surface_compression 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SURFACE_COMPRESSION_EXT       0x34B0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SURFACE_COMPRESSION_PLANE1_EXT 0x328E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SURFACE_COMPRESSION_PLANE2_EXT 0x328F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SURFACE_COMPRESSION_FIXED_ਦਰ_NONE_EXT 0x34B1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SURFACE_COMPRESSION_FIXED_ਦਰ_DEFAULT_EXT 0x34B2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SURFACE_COMPRESSION_FIXED_ਦਰ_1_BPC_EXT 0x34B4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SURFACE_COMPRESSION_FIXED_ਦਰ_2_BPC_EXT 0x34B5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SURFACE_COMPRESSION_FIXED_ਦਰ_3_BPC_EXT 0x34B6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SURFACE_COMPRESSION_FIXED_ਦਰ_4_BPC_EXT 0x34B7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SURFACE_COMPRESSION_FIXED_ਦਰ_5_BPC_EXT 0x34B8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SURFACE_COMPRESSION_FIXED_ਦਰ_6_BPC_EXT 0x34B9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SURFACE_COMPRESSION_FIXED_ਦਰ_7_BPC_EXT 0x34BA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SURFACE_COMPRESSION_FIXED_ਦਰ_8_BPC_EXT 0x34BB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SURFACE_COMPRESSION_FIXED_ਦਰ_9_BPC_EXT 0x34BC
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SURFACE_COMPRESSION_FIXED_ਦਰ_10_BPC_EXT 0x34BD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SURFACE_COMPRESSION_FIXED_ਦਰ_11_BPC_EXT 0x34BE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SURFACE_COMPRESSION_FIXED_ਦਰ_12_BPC_EXT 0x34BF
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSUPPORTEDCOMPRESSIONRATESEXTPROC) (EGLDisplay dpy, EGLConfig config, ਅਚਲ EGLAttrib *attrib_list, EGLint *rates, EGLint ਦਰ_ਮਾਪ, EGLint *ਅੰਕ_rates);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQuerySupportedCompressionRatesEXT (EGLDisplay dpy, EGLConfig config, ਅਚਲ EGLAttrib *attrib_list, EGLint *rates, EGLint ਦਰ_ਮਾਪ, EGLint *ਅੰਕ_rates);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_EXT_surface_compression */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_ਅਦਲਾ_ਬਦਲੀ_buffers_with_damage
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_ਅਦਲਾ_ਬਦਲੀ_buffers_with_damage 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC) (EGLDisplay dpy, EGLSurface surface, ਅਚਲ EGLint *rects, EGLint n_rects);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_ਅਦਲਾ_ਬਦਲੀ_Buffers_With_Damage_EXT (EGLDisplay dpy, EGLSurface surface, ਅਚਲ EGLint *rects, EGLint n_rects);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_EXT_swap_buffers_with_damage */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_sync_reuse
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_sync_reuse 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLUNSIGNALSYNCEXTPROC) (EGLDisplay dpy, EGLSync sync, ਅਚਲ EGLAttrib *attrib_list);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglUnsignalSyncEXT (EGLDisplay dpy, EGLSync sync, ਅਚਲ EGLAttrib *attrib_list);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_EXT_sync_reuse */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_EXT_yuv_surface
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_EXT_yuv_surface 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_YUV_ਕ੍ਰਮ_EXT                 0x3301
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_YUV_ਸੰਖਿਆ_ਦਾ_PLANES_EXT      0x3311
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_YUV_SUBSAMPLE_EXT             0x3312
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_YUV_ਡੂੰਘਾਈ_RANGE_EXT           0x3317
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_YUV_CSC_STANDARD_EXT          0x330A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_YUV_PLANE_BPP_EXT             0x331A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_YUV_ਬਫਰ_EXT                0x3300
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_YUV_ਕ੍ਰਮ_YUV_EXT             0x3302
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_YUV_ਕ੍ਰਮ_YVU_EXT             0x3303
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_YUV_ਕ੍ਰਮ_YUYV_EXT            0x3304
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_YUV_ਕ੍ਰਮ_UYVY_EXT            0x3305
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_YUV_ਕ੍ਰਮ_YVYU_EXT            0x3306
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_YUV_ਕ੍ਰਮ_VYUY_EXT            0x3307
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_YUV_ਕ੍ਰਮ_AYUV_EXT            0x3308
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_YUV_SUBSAMPLE_4_2_0_EXT       0x3313
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_YUV_SUBSAMPLE_4_2_2_EXT       0x3314
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_YUV_SUBSAMPLE_4_4_4_EXT       0x3315
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_YUV_ਡੂੰਘਾਈ_RANGE_LIMITED_EXT   0x3318
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_YUV_ਡੂੰਘਾਈ_RANGE_ਭਰਿਆ_EXT      0x3319
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_YUV_CSC_STANDARD_601_EXT      0x330B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_YUV_CSC_STANDARD_709_EXT      0x330C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_YUV_CSC_STANDARD_2020_EXT     0x330D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_YUV_PLANE_BPP_0_EXT           0x331B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_YUV_PLANE_BPP_8_EXT           0x331C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_YUV_PLANE_BPP_10_EXT          0x331D
#ਜੇ_ਅੰਤ /* EGL_EXT_yuv_surface */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_HI_clientpixmap
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_HI_clientpixmap 1
ਬਣਤਰ EGLClientPixmapHI {
    ਖਾਲੀ  *p_ਅੰਕੜੇ;
    EGLint i_ਚੌੜਾਈ;
    EGLint i_ਉਚਾਈ;
    EGLint iStride;
};
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CLIENT_PIXMAP_ਸੂਚਕ_HI      0x8F74
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLSurface (EGLAPIENTRYP PFNEGLCREATEPIXMAPSURFACEHIPROC) (EGLDisplay dpy, EGLConfig config, ਬਣਤਰ EGLClientPixmapHI *pixmap);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSurface EGLAPIENTRY eglCreatePixmapSurfaceHI (EGLDisplay dpy, EGLConfig config, ਬਣਤਰ EGLClientPixmapHI *pixmap);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_HI_clientpixmap */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_HI_colorformats
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_HI_colorformats 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_COLOR_FORMAT_HI               0x8F70
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_COLOR_RGB_HI                  0x8F71
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_COLOR_RGBA_HI                 0x8F72
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_COLOR_ARGB_HI                 0x8F73
#ਜੇ_ਅੰਤ /* EGL_HI_colorformats */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_IMG_context_ਤਰਜੀਹ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_IMG_context_ਤਰਜੀਹ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONTEXT_ਤਰਜੀਹ_LEVEL_IMG    0x3100
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONTEXT_ਤਰਜੀਹ_ਉੱਚਾ_IMG     0x3101
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONTEXT_ਤਰਜੀਹ_MEDIUM_IMG   0x3102
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONTEXT_ਤਰਜੀਹ_ਨੀਵਾਂ_IMG      0x3103
#ਜੇ_ਅੰਤ /* EGL_IMG_context_priority */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_IMG_image_plane_attribs
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_IMG_image_plane_attribs 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NATIVE_ਬਫਰ_MULTIPLANE_SEPARATE_IMG 0x3105
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NATIVE_ਬਫਰ_PLANE_ਵਿੱਥ_IMG 0x3106
#ਜੇ_ਅੰਤ /* EGL_IMG_image_plane_attribs */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_MESA_drm_image
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_MESA_drm_image 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DRM_ਬਫਰ_FORMAT_MESA        0x31D0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DRM_ਬਫਰ_USE_MESA           0x31D1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DRM_ਬਫਰ_FORMAT_ARGB32_MESA 0x31D2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DRM_ਬਫਰ_MESA               0x31D3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DRM_ਬਫਰ_STRIDE_MESA        0x31D4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DRM_ਬਫਰ_USE_SCANOUT_MESA   0x00000001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DRM_ਬਫਰ_USE_SHARE_MESA     0x00000002
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_DRM_ਬਫਰ_USE_CURSOR_MESA    0x00000004
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLImageKHR (EGLAPIENTRYP PFNEGLCREATEDRMIMAGEMESAPROC) (EGLDisplay dpy, ਅਚਲ EGLint *attrib_list);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLEXPORTDRMIMAGEMESAPROC) (EGLDisplay dpy, EGLImageKHR image, EGLint *name, EGLint *handle, EGLint *stride);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLImageKHR EGLAPIENTRY eglCreateDRMImageMESA (EGLDisplay dpy, ਅਚਲ EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglExportDRMImageMESA (EGLDisplay dpy, EGLImageKHR image, EGLint *name, EGLint *handle, EGLint *stride);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_MESA_drm_image */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_MESA_image_dma_buf_export
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_MESA_image_dma_buf_export 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLEXPORTDMABUFIMAGEQUERYMESAPROC) (EGLDisplay dpy, EGLImageKHR image, ਪੂਰਨ *fourcc, ਪੂਰਨ *ਅੰਕ_planes, EGLuint64KHR *modifiers);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLEXPORTDMABUFIMAGEMESAPROC) (EGLDisplay dpy, EGLImageKHR image, ਪੂਰਨ *fds, EGLint *strides, EGLint *offsets);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglExportDMABUFImageQueryMESA (EGLDisplay dpy, EGLImageKHR image, ਪੂਰਨ *fourcc, ਪੂਰਨ *ਅੰਕ_planes, EGLuint64KHR *modifiers);
EGLAPI EGLBoolean EGLAPIENTRY eglExportDMABUFImageMESA (EGLDisplay dpy, EGLImageKHR image, ਪੂਰਨ *fds, EGLint *strides, EGLint *offsets);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_MESA_image_dma_buf_export */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_MESA_platform_gbm
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_MESA_platform_gbm 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_PLATFORM_GBM_MESA             0x31D7
#ਜੇ_ਅੰਤ /* EGL_MESA_platform_gbm */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_MESA_platform_surfaceless
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_MESA_platform_surfaceless 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_PLATFORM_SURFACELESS_MESA     0x31DD
#ਜੇ_ਅੰਤ /* EGL_MESA_platform_surfaceless */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_MESA_query_driver
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_MESA_query_driver 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਅੱਖਰ *(EGLAPIENTRYP PFNEGLGETDISPLAYDRIVERCONFIGPROC) (EGLDisplay dpy);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਅਚਲ ਅੱਖਰ *(EGLAPIENTRYP PFNEGLGETDISPLAYDRIVERNAMEPROC) (EGLDisplay dpy);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI ਅੱਖਰ *EGLAPIENTRY eglGetDisplayDriverConfig (EGLDisplay dpy);
EGLAPI ਅਚਲ ਅੱਖਰ *EGLAPIENTRY eglGetDisplayDriverName (EGLDisplay dpy);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_MESA_query_driver */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NOK_ਅਦਲਾ_ਬਦਲੀ_region
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NOK_ਅਦਲਾ_ਬਦਲੀ_region 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSREGIONNOKPROC) (EGLDisplay dpy, EGLSurface surface, EGLint ਅੰਕ_Rects_2, ਅਚਲ EGLint *rects);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_ਅਦਲਾ_ਬਦਲੀ_Buffers_Region_NOK (EGLDisplay dpy, EGLSurface surface, EGLint ਅੰਕ_Rects_2, ਅਚਲ EGLint *rects);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_NOK_swap_region */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NOK_ਅਦਲਾ_ਬਦਲੀ_region2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NOK_ਅਦਲਾ_ਬਦਲੀ_region2 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSREGION2NOKPROC) (EGLDisplay dpy, EGLSurface surface, EGLint ਅੰਕ_Rects_2, ਅਚਲ EGLint *rects);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_ਅਦਲਾ_ਬਦਲੀ_Buffers_Region2_NOK (EGLDisplay dpy, EGLSurface surface, EGLint ਅੰਕ_Rects_2, ਅਚਲ EGLint *rects);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_NOK_swap_region2 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NOK_texture_from_pixmap
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NOK_texture_from_pixmap 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_Y_INVERTED_NOK                0x307F
#ਜੇ_ਅੰਤ /* EGL_NOK_texture_from_pixmap */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_3dvision_surface
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_3dvision_surface 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_AUTO_STEREO_NV                0x3136
#ਜੇ_ਅੰਤ /* EGL_NV_3dvision_surface */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_context_ਤਰਜੀਹ_realtime
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_context_ਤਰਜੀਹ_realtime 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONTEXT_ਤਰਜੀਹ_REALTIME_NV  0x3357
#ਜੇ_ਅੰਤ /* EGL_NV_context_priority_realtime */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_coverage_sample
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_coverage_sample 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_COVERAGE_BUFFERS_NV           0x30E0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_COVERAGE_SAMPLES_NV           0x30E1
#ਜੇ_ਅੰਤ /* EGL_NV_coverage_sample */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_coverage_sample_resolve
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_coverage_sample_resolve 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_COVERAGE_SAMPLE_RESOLVE_NV    0x3131
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_COVERAGE_SAMPLE_RESOLVE_DEFAULT_NV 0x3132
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_COVERAGE_SAMPLE_RESOLVE_NONE_NV 0x3133
#ਜੇ_ਅੰਤ /* EGL_NV_coverage_sample_resolve */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_cuda_event
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_cuda_event 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CUDA_EVENT_HANDLE_NV          0x323B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SYNC_CUDA_EVENT_NV            0x323C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SYNC_CUDA_EVENT_COMPLETE_NV   0x323D
#ਜੇ_ਅੰਤ /* EGL_NV_cuda_event */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_ਡੂੰਘਾਈ_nonlinear
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_ਡੂੰਘਾਈ_nonlinear 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਡੂੰਘਾਈ_ENCODING_NV             0x30E2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਡੂੰਘਾਈ_ENCODING_NONE_NV        0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਡੂੰਘਾਈ_ENCODING_NONLINEAR_NV   0x30E3
#ਜੇ_ਅੰਤ /* EGL_NV_depth_nonlinear */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_device_cuda
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_device_cuda 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CUDA_DEVICE_NV                0x323A
#ਜੇ_ਅੰਤ /* EGL_NV_device_cuda */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_native_query
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_native_query 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYNATIVEDISPLAYNVPROC) (EGLDisplay dpy, EGLNativeDisplayType *display_id);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYNATIVEWINDOWNVPROC) (EGLDisplay dpy, EGLSurface surf, EGLNative_ਖਿੜਕੀ_Type *ਖਿੜਕੀ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYNATIVEPIXMAPNVPROC) (EGLDisplay dpy, EGLSurface surf, EGLNativePixmapType *pixmap);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryNativeDisplayNV (EGLDisplay dpy, EGLNativeDisplayType *display_id);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Native_ਖਿੜਕੀ_NV (EGLDisplay dpy, EGLSurface surf, EGLNative_ਖਿੜਕੀ_Type *ਖਿੜਕੀ);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryNativePixmapNV (EGLDisplay dpy, EGLSurface surf, EGLNativePixmapType *pixmap);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_NV_native_query */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_post_convert_rounding
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_post_convert_rounding 1
#ਜੇ_ਅੰਤ /* EGL_NV_post_convert_rounding */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_post_sub_ਬਫਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_post_sub_ਬਫਰ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_POST_SUB_ਬਫਰ_SUPPORTED_NV  0x30BE
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLPOSTSUBBUFFERNVPROC) (EGLDisplay dpy, EGLSurface surface, EGLint x, EGLint y, EGLint ਚੌੜਾਈ, EGLint ਉਚਾਈ);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Post_Sub_ਬਫਰ_NV (EGLDisplay dpy, EGLSurface surface, EGLint x, EGLint y, EGLint ਚੌੜਾਈ, EGLint ਉਚਾਈ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_NV_post_sub_buffer */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_quadruple_ਬਫਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_quadruple_ਬਫਰ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_QUADRUPLE_ਬਫਰ_NV           0x3231
#ਜੇ_ਅੰਤ /* EGL_NV_quadruple_buffer */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_robustness_video_ਸਮ੍ਰਿਤੀ_purge
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_robustness_video_ਸਮ੍ਰਿਤੀ_purge 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_GENERATE_RESET_ON_VIDEO_ਸਮ੍ਰਿਤੀ_PURGE_NV 0x334C
#ਜੇ_ਅੰਤ /* EGL_NV_robustness_video_memory_purge */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_ਧਾਰਾ_ਖਪਤਕਾਰ_eglimage
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_ਧਾਰਾ_ਖਪਤਕਾਰ_eglimage 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_ਖਪਤਕਾਰ_IMAGE_NV      0x3373
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_IMAGE_ਜੋੜੋ_NV           0x3374
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_IMAGE_REMOVE_NV        0x3375
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_IMAGE_ਉਪਲਬਧ_NV     0x3376
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMIMAGECONSUMERCONNECTNVPROC) (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ, EGLint ਅੰਕ_modifiers, ਅਚਲ EGLuint64KHR *modifiers, ਅਚਲ EGLAttrib *attrib_list);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLint (EGLAPIENTRYP PFNEGLQUERYSTREAMCONSUMEREVENTNVPROC) (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ, EGLTime timeout, EGLenum *event, EGLAttrib *aux);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMACQUIREIMAGENVPROC) (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ, EGLImage *pImage, EGLSync sync);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMRELEASEIMAGENVPROC) (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ, EGLImage image, EGLSync sync);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_ਧਾਰਾ_Image_ਖਪਤਕਾਰ_Connect_NV (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ, EGLint ਅੰਕ_modifiers, ਅਚਲ EGLuint64KHR *modifiers, ਅਚਲ EGLAttrib *attrib_list);
EGLAPI EGLint EGLAPIENTRY egl_Query_ਧਾਰਾ_ਖਪਤਕਾਰ_Event_NV (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ, EGLTime timeout, EGLenum *event, EGLAttrib *aux);
EGLAPI EGLBoolean EGLAPIENTRY egl_ਧਾਰਾ_Acquire_Image_NV (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ, EGLImage *pImage, EGLSync sync);
EGLAPI EGLBoolean EGLAPIENTRY egl_ਧਾਰਾ_Release_Image_NV (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ, EGLImage image, EGLSync sync);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_NV_stream_consumer_eglimage */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_ਧਾਰਾ_ਖਪਤਕਾਰ_eglimage_use_scanout_attrib
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_ਧਾਰਾ_ਖਪਤਕਾਰ_eglimage_use_scanout_attrib 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_ਖਪਤਕਾਰ_IMAGE_USE_SCANOUT_NV 0x3378
#ਜੇ_ਅੰਤ /* EGL_NV_stream_consumer_eglimage_use_scanout_attrib */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_ਧਾਰਾ_ਖਪਤਕਾਰ_gltexture_yuv
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_ਧਾਰਾ_ਖਪਤਕਾਰ_gltexture_yuv 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_YUV_PLANE0_TEXTURE_UNIT_NV    0x332C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_YUV_PLANE1_TEXTURE_UNIT_NV    0x332D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_YUV_PLANE2_TEXTURE_UNIT_NV    0x332E
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALATTRIBSNVPROC) (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ, ਅਚਲ EGLAttrib *attrib_list);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_ਧਾਰਾ_ਖਪਤਕਾਰ_GLTexture_External_Attribs_NV (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ, ਅਚਲ EGLAttrib *attrib_list);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_NV_stream_consumer_gltexture_yuv */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_ਧਾਰਾ_cross_display
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_ਧਾਰਾ_cross_display 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_CROSS_DISPLAY_NV       0x334E
#ਜੇ_ਅੰਤ /* EGL_NV_stream_cross_display */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_ਧਾਰਾ_cross_object
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_ਧਾਰਾ_cross_object 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_CROSS_OBJECT_NV        0x334D
#ਜੇ_ਅੰਤ /* EGL_NV_stream_cross_object */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_ਧਾਰਾ_cross_ਹਿੱਸੇ_ਕਰੋ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_ਧਾਰਾ_cross_ਹਿੱਸੇ_ਕਰੋ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_CROSS_ਹਿੱਸੇ_ਕਰੋ_NV     0x323F
#ਜੇ_ਅੰਤ /* EGL_NV_stream_cross_partition */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_ਧਾਰਾ_cross_process
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_ਧਾਰਾ_cross_process 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_CROSS_PROCESS_NV       0x3245
#ਜੇ_ਅੰਤ /* EGL_NV_stream_cross_process */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_ਧਾਰਾ_cross_system
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_ਧਾਰਾ_cross_system 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_CROSS_SYSTEM_NV        0x334F
#ਜੇ_ਅੰਤ /* EGL_NV_stream_cross_system */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_ਧਾਰਾ_dma
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_ਧਾਰਾ_dma 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_DMA_NV                 0x3371
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_DMA_SERVER_NV          0x3372
#ਜੇ_ਅੰਤ /* EGL_NV_stream_dma */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_ਧਾਰਾ_fifo_ਅਗਲਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_ਧਾਰਾ_fifo_ਅਗਲਾ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_PENDING_ਚੌਖਟਾ_NV              0x3329
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_ਸਮਾਂ_PENDING_NV        0x332A
#ਜੇ_ਅੰਤ /* EGL_NV_stream_fifo_next */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_ਧਾਰਾ_fifo_synchronous
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_ਧਾਰਾ_fifo_synchronous 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_FIFO_SYNCHRONOUS_NV    0x3336
#ਜੇ_ਅੰਤ /* EGL_NV_stream_fifo_synchronous */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_ਧਾਰਾ_flush
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_ਧਾਰਾ_flush 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMFLUSHNVPROC) (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_ਧਾਰਾ_Flush_NV (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_NV_stream_flush */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_ਧਾਰਾ_ਚੌਖਟਾ_limits
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_ਧਾਰਾ_ਚੌਖਟਾ_limits 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਉਤਪਾਦਕ_MAX_ਚੌਖਟਾ_HINT_NV    0x3337
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਖਪਤਕਾਰ_MAX_ਚੌਖਟਾ_HINT_NV    0x3338
#ਜੇ_ਅੰਤ /* EGL_NV_stream_frame_limits */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_ਧਾਰਾ_metadata
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_ਧਾਰਾ_metadata 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_MAX_ਧਾਰਾ_METADATA_ਖੰਡਾਂ_NV 0x3250
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_MAX_ਧਾਰਾ_METADATA_ਖੰਡ_ਮਾਪ_NV 0x3251
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_MAX_ਧਾਰਾ_METADATA_ਕੁੱਲ_ਮਾਪ_NV 0x3252
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਉਤਪਾਦਕ_METADATA_NV          0x3253
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਖਪਤਕਾਰ_METADATA_NV          0x3254
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_PENDING_METADATA_NV           0x3328
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_METADATA0_ਮਾਪ_NV             0x3255
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_METADATA1_ਮਾਪ_NV             0x3256
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_METADATA2_ਮਾਪ_NV             0x3257
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_METADATA3_ਮਾਪ_NV             0x3258
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_METADATA0_TYPE_NV             0x3259
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_METADATA1_TYPE_NV             0x325A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_METADATA2_TYPE_NV             0x325B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_METADATA3_TYPE_NV             0x325C
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDISPLAYATTRIBNVPROC) (EGLDisplay dpy, EGLint attribute, EGLAttrib *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLSETSTREAMMETADATANVPROC) (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ, EGLint n, EGLint ਵਿੱਥ_2, EGLint ਮਾਪ, ਅਚਲ ਖਾਲੀ *ਅੰਕੜੇ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMMETADATANVPROC) (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ, EGLenum name, EGLint n, EGLint ਵਿੱਥ_2, EGLint ਮਾਪ, ਖਾਲੀ *ਅੰਕੜੇ);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDisplayAttribNV (EGLDisplay dpy, EGLint attribute, EGLAttrib *ਮੁੱਲ);
EGLAPI EGLBoolean EGLAPIENTRY egl_ਸੈੱਟ_ਧਾਰਾ_Metadata_NV (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ, EGLint n, EGLint ਵਿੱਥ_2, EGLint ਮਾਪ, ਅਚਲ ਖਾਲੀ *ਅੰਕੜੇ);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_ਧਾਰਾ_Metadata_NV (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ, EGLenum name, EGLint n, EGLint ਵਿੱਥ_2, EGLint ਮਾਪ, ਖਾਲੀ *ਅੰਕੜੇ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_NV_stream_metadata */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_ਧਾਰਾ_origin
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_ਧਾਰਾ_origin 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_ਚੌਖਟਾ_ORIGIN_X_NV      0x3366
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_ਚੌਖਟਾ_ORIGIN_Y_NV      0x3367
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_ਚੌਖਟਾ_MAJOR_AXIS_NV    0x3368
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਖਪਤਕਾਰ_AUTO_ORIENTATION_NV  0x3369
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਉਤਪਾਦਕ_AUTO_ORIENTATION_NV  0x336A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਖੱਬਾ_NV                       0x336B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਸੱਜਾ_NV                      0x336C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਸਿਖਰ_NV                        0x336D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_BOTTOM_NV                     0x336E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_X_AXIS_NV                     0x336F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_Y_AXIS_NV                     0x3370
#ਜੇ_ਅੰਤ /* EGL_NV_stream_origin */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_ਧਾਰਾ_remote
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_ਧਾਰਾ_remote 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_STATE_INITIALIZING_NV  0x3240
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_TYPE_NV                0x3241
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_PROTOCOL_NV            0x3242
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_ENDPOINT_NV            0x3243
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_LOCAL_NV               0x3244
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_ਉਤਪਾਦਕ_NV            0x3247
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_ਖਪਤਕਾਰ_NV            0x3248
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_PROTOCOL_FD_NV         0x3246
#ਜੇ_ਅੰਤ /* EGL_NV_stream_remote */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_ਧਾਰਾ_reset
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_ਧਾਰਾ_reset 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SUPPORT_RESET_NV              0x3334
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SUPPORT_REUSE_NV              0x3335
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLRESETSTREAMNVPROC) (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Reset_ਧਾਰਾ_NV (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_NV_stream_reset */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_ਧਾਰਾ_socket
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_ਧਾਰਾ_socket 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ਧਾਰਾ_PROTOCOL_SOCKET_NV     0x324B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SOCKET_HANDLE_NV              0x324C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SOCKET_TYPE_NV                0x324D
#ਜੇ_ਅੰਤ /* EGL_NV_stream_socket */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_ਧਾਰਾ_socket_inet
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_ਧਾਰਾ_socket_inet 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SOCKET_TYPE_INET_NV           0x324F
#ਜੇ_ਅੰਤ /* EGL_NV_stream_socket_inet */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_ਧਾਰਾ_socket_unix
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_ਧਾਰਾ_socket_unix 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SOCKET_TYPE_UNIX_NV           0x324E
#ਜੇ_ਅੰਤ /* EGL_NV_stream_socket_unix */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_ਧਾਰਾ_sync
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_ਧਾਰਾ_sync 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SYNC_NEW_ਚੌਖਟਾ_NV             0x321F
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESTREAMSYNCNVPROC) (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ, EGLenum type, ਅਚਲ EGLint *attrib_list);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncKHR EGLAPIENTRY egl_Create_ਧਾਰਾ_Sync_NV (EGLDisplay dpy, EGLStreamKHR ਧਾਰਾ, EGLenum type, ਅਚਲ EGLint *attrib_list);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_NV_stream_sync */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_sync
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_sync 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ *EGLSyncNV;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ khronos_utime_nanoseconds_t EGLTimeNV;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ KHRONOS_SUPPORT_INT64
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SYNC_ਪੂਰਵ_COMMANDS_COMPLETE_NV 0x30E6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SYNC_ਸਥਿਤੀ_NV                0x30E7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SIGNALED_NV                   0x30E8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_UNSIGNALED_NV                 0x30E9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SYNC_FLUSH_COMMANDS_ਦੋਆਧਾਰੀ_ਅੰਕ_NV    0x0001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_FOREVER_NV                    0xFFFFFFFFFFFFFFFFull
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_ALREADY_SIGNALED_NV           0x30EA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_TIMEOUT_EXPIRED_NV            0x30EB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_CONDITION_SATISFIED_NV        0x30EC
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SYNC_TYPE_NV                  0x30ED
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SYNC_CONDITION_NV             0x30EE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_SYNC_FENCE_NV                 0x30EF
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NO_SYNC_NV                    EGL_CAST(EGLSyncNV,0)
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLSyncNV (EGLAPIENTRYP PFNEGLCREATEFENCESYNCNVPROC) (EGLDisplay dpy, EGLenum condition, ਅਚਲ EGLint *attrib_list);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCNVPROC) (EGLSyncNV sync);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLFENCENVPROC) (EGLSyncNV sync);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCNVPROC) (EGLSyncNV sync, EGLint flags, EGLTimeNV timeout);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLSIGNALSYNCNVPROC) (EGLSyncNV sync, EGLenum ਬਹੁਲਕ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLGETSYNCATTRIBNVPROC) (EGLSyncNV sync, EGLint attribute, EGLint *ਮੁੱਲ);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncNV EGLAPIENTRY eglCreateFenceSyncNV (EGLDisplay dpy, EGLenum condition, ਅਚਲ EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySyncNV (EGLSyncNV sync);
EGLAPI EGLBoolean EGLAPIENTRY eglFenceNV (EGLSyncNV sync);
EGLAPI EGLint EGLAPIENTRY eglClientWaitSyncNV (EGLSyncNV sync, EGLint flags, EGLTimeNV timeout);
EGLAPI EGLBoolean EGLAPIENTRY eglSignalSyncNV (EGLSyncNV sync, EGLenum ਬਹੁਲਕ);
EGLAPI EGLBoolean EGLAPIENTRY eglGetSyncAttribNV (EGLSyncNV sync, EGLint attribute, EGLint *ਮੁੱਲ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* KHRONOS_SUPPORT_INT64 */
#ਜੇ_ਅੰਤ /* EGL_NV_sync */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_system_ਸਮਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_system_ਸਮਾਂ 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ khronos_utime_nanoseconds_t EGLuint64NV;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ KHRONOS_SUPPORT_INT64
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLuint64NV (EGLAPIENTRYP PFNEGLGETSYSTEMTIMEFREQUENCYNVPROC) (ਖਾਲੀ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLuint64NV (EGLAPIENTRYP PFNEGLGETSYSTEMTIMENVPROC) (ਖਾਲੀ);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLuint64NV EGLAPIENTRY egl_Get_System_ਸਮਾਂ_Frequency_NV (ਖਾਲੀ);
EGLAPI EGLuint64NV EGLAPIENTRY egl_Get_System_ਸਮਾਂ_NV (ਖਾਲੀ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* KHRONOS_SUPPORT_INT64 */
#ਜੇ_ਅੰਤ /* EGL_NV_system_time */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_NV_triple_ਬਫਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NV_triple_ਬਫਰ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_TRIPLE_ਬਫਰ_NV              0x3230
#ਜੇ_ਅੰਤ /* EGL_NV_triple_buffer */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_QNX_image_native_ਬਫਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_QNX_image_native_ਬਫਰ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NATIVE_ਬਫਰ_QNX             0x3551
#ਜੇ_ਅੰਤ /* EGL_QNX_image_native_buffer */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_QNX_platform_screen
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_QNX_platform_screen 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_PLATFORM_SCREEN_QNX           0x3550
#ਜੇ_ਅੰਤ /* EGL_QNX_platform_screen */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_TIZEN_image_native_ਬਫਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_TIZEN_image_native_ਬਫਰ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NATIVE_ਬਫਰ_TIZEN           0x32A0
#ਜੇ_ਅੰਤ /* EGL_TIZEN_image_native_buffer */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_TIZEN_image_native_surface
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_TIZEN_image_native_surface 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_NATIVE_SURFACE_TIZEN          0x32A1
#ਜੇ_ਅੰਤ /* EGL_TIZEN_image_native_surface */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_WL_bind_wayland_display
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_WL_bind_wayland_display 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PFNEGLBINDWAYLANDDISPLAYWL PFNEGLBINDWAYLANDDISPLAYWLPROC
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PFNEGLUNBINDWAYLANDDISPLAYWL PFNEGLUNBINDWAYLANDDISPLAYWLPROC
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PFNEGLQUERYWAYLANDBUFFERWL PFNEGLQUERYWAYLANDBUFFERWLPROC
ਬਣਤਰ wl_display;
ਬਣਤਰ wl_resource;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_WAYLAND_ਬਫਰ_WL             0x31D5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_WAYLAND_PLANE_WL              0x31D6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_TEXTURE_Y_U_V_WL              0x31D7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_TEXTURE_Y_UV_WL               0x31D8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_TEXTURE_Y_XUXV_WL             0x31D9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_TEXTURE_EXTERNAL_WL           0x31DA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_WAYLAND_Y_INVERTED_WL         0x31DB
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLBINDWAYLANDDISPLAYWLPROC) (EGLDisplay dpy, ਬਣਤਰ wl_display *display);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLUNBINDWAYLANDDISPLAYWLPROC) (EGLDisplay dpy, ਬਣਤਰ wl_display *display);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYWAYLANDBUFFERWLPROC) (EGLDisplay dpy, ਬਣਤਰ wl_resource *ਬਫਰ_2, EGLint attribute, EGLint *ਮੁੱਲ);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglBindWaylandDisplayWL (EGLDisplay dpy, ਬਣਤਰ wl_display *display);
EGLAPI EGLBoolean EGLAPIENTRY eglUnbindWaylandDisplayWL (EGLDisplay dpy, ਬਣਤਰ wl_display *display);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Wayland_ਬਫਰ_WL (EGLDisplay dpy, ਬਣਤਰ wl_resource *ਬਫਰ_2, EGLint attribute, EGLint *ਮੁੱਲ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_WL_bind_wayland_display */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ EGL_WL_create_wayland_ਬਫਰ_from_image
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGL_WL_create_wayland_ਬਫਰ_from_image 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PFNEGLCREATEWAYLANDBUFFERFROMIMAGEWL PFNEGLCREATEWAYLANDBUFFERFROMIMAGEWLPROC
ਬਣਤਰ wl_ਬਫਰ;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ wl_ਬਫਰ *(EGLAPIENTRYP PFNEGLCREATEWAYLANDBUFFERFROMIMAGEWLPROC) (EGLDisplay dpy, EGLImageKHR image);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ EGL_EGLEXT_PROTOTYPES
EGLAPI ਬਣਤਰ wl_ਬਫਰ *EGLAPIENTRY egl_Create_Wayland_ਬਫਰ_From_Image_WL (EGLDisplay dpy, EGLImageKHR image);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* EGL_WL_create_wayland_buffer_from_image */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ
