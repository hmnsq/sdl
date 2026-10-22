#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ __eglext_h_
#ವ್ಯಾಖ್ಯಾನಿಸು __eglext_h_ 1

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ

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

#ಅನ್ತರ್ಭಾವ <EGL/eglplatform.h>

#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EGLEXT_ಆವೃತ್ತಿ 20260319

/* Generated C header for:
 * API: egl
 * Versions considered: .*
 * Versions emitted: _nomatch_^
 * Default extensions included: egl
 * Additional extensions included: _nomatch_^
 * Extensions removed: _nomatch_^
 */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_cl_event
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_cl_event 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_CL_EVENT_HANDLE_KHR           0x309C
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SYNC_CL_EVENT_KHR             0x30FE
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SYNC_CL_EVENT_COMPLETE_KHR    0x30FF
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_cl_event */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_cl_event2
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_cl_event2 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ *EGLSyncKHR;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ intptr_t EGLAttribKHR;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESYNC64KHRPROC) (EGLDisplay dpy, EGLenum type, ಸ್ಥಿರಾಂಕ EGLAttribKHR *attrib_list);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncKHR EGLAPIENTRY eglCreateSync64KHR (EGLDisplay dpy, EGLenum type, ಸ್ಥಿರಾಂಕ EGLAttribKHR *attrib_list);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_cl_event2 */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_client_get_all_proc_ವಿಳಾಸಗಳು
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_client_get_all_proc_ವಿಳಾಸಗಳು 1
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_client_get_all_proc_addresses */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_config_attribs
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_config_attribs 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_CONFORMANT_KHR                0x3042
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_VG_COLORSPACE_ರೇಖೀಯ_ಬಿಟ್_KHR  0x0020
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_VG_ALPHA_FORMAT_PRE_ಬಿಟ್_KHR   0x0040
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_config_attribs */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_context_flush_control
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_context_flush_control 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_CONTEXT_RELEASE_BEHAVIOR_NONE_KHR 0
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_CONTEXT_RELEASE_BEHAVIOR_KHR  0x2097
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_KHR 0x2098
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_context_flush_control */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_create_context
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_create_context 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_CONTEXT_MAJOR_ಆವೃತ್ತಿ_KHR     0x3098
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_CONTEXT_MINOR_ಆವೃತ್ತಿ_KHR     0x30FB
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_CONTEXT_FLAGS_KHR             0x30FC
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_CONTEXT_OPENGL_PROFILE_ಮುಖವಾಡ_KHR 0x30FD
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_KHR 0x31BD
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NO_RESET_NOTIFICATION_KHR     0x31BE
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_LOSE_CONTEXT_ON_RESET_KHR     0x31BF
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_CONTEXT_OPENGL_DEBUG_ಬಿಟ್_KHR  0x00000001
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_ಬಿಟ್_KHR 0x00000002
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_CONTEXT_OPENGL_ROBUST_ACCESS_ಬಿಟ್_KHR 0x00000004
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_CONTEXT_OPENGL_CORE_PROFILE_ಬಿಟ್_KHR 0x00000001
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_ಬಿಟ್_KHR 0x00000002
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_OPENGL_ES3_ಬಿಟ್_KHR            0x00000040
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_create_context */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_create_context_no_error
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_create_context_no_error 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_CONTEXT_OPENGL_NO_ERROR_KHR   0x31B3
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_create_context_no_error */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_debug
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_debug 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ *EGLLabelKHR;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ *EGLObjectKHR;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (EGLAPIENTRY  *EGLDEBUGPROCKHR)(EGLenum error,ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *command,EGLint ಸಂದೇಶ_Type,EGLLabelKHR threadLabel,EGLLabelKHR objectLabel,ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ* ಸಂದೇಶ);
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_OBJECT_THREAD_KHR             0x33B0
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_OBJECT_DISPLAY_KHR            0x33B1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_OBJECT_CONTEXT_KHR            0x33B2
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_OBJECT_SURFACE_KHR            0x33B3
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_OBJECT_IMAGE_KHR              0x33B4
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_OBJECT_SYNC_KHR               0x33B5
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_OBJECT_ಹರಿವು_KHR             0x33B6
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DEBUG_ಸಂದೇಶ_CRITICAL_KHR        0x33B9
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DEBUG_ಸಂದೇಶ_ERROR_KHR           0x33BA
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DEBUG_ಸಂದೇಶ_WARN_KHR            0x33BB
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DEBUG_ಸಂದೇಶ_INFO_KHR            0x33BC
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DEBUG_CALLBACK_KHR            0x33B8
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLint (EGLAPIENTRYP PFNEGLDEBUGMESSAGECONTROLKHRPROC) (EGLDEBUGPROCKHR callback, ಸ್ಥಿರಾಂಕ EGLAttrib *attrib_list);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEBUGKHRPROC) (EGLint attribute, EGLAttrib *ಮೌಲ್ಯ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLint (EGLAPIENTRYP PFNEGLLABELOBJECTKHRPROC) (EGLDisplay display, EGLenum objectType, EGLObjectKHR object, EGLLabelKHR label);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLint EGLAPIENTRY egl_Debug_ಸಂದೇಶ_Control_KHR (EGLDEBUGPROCKHR callback, ಸ್ಥಿರಾಂಕ EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDebugKHR (EGLint attribute, EGLAttrib *ಮೌಲ್ಯ);
EGLAPI EGLint EGLAPIENTRY eglLabelObjectKHR (EGLDisplay display, EGLenum objectType, EGLObjectKHR object, EGLLabelKHR label);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_debug */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_display_reference
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_display_reference 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_TRACK_REFERENCES_KHR          0x3352
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDISPLAYATTRIBKHRPROC) (EGLDisplay dpy, EGLint name, EGLAttrib *ಮೌಲ್ಯ);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDisplayAttribKHR (EGLDisplay dpy, EGLint name, EGLAttrib *ಮೌಲ್ಯ);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_display_reference */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_fence_sync
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_fence_sync 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ khronos_utime_nanoseconds_t EGLTimeKHR;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ KHRONOS_SUPPORT_INT64
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SYNC_ಪೂರ್ವ_COMMANDS_COMPLETE_KHR 0x30F0
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SYNC_CONDITION_KHR            0x30F8
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SYNC_FENCE_KHR                0x30F9
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESYNCKHRPROC) (EGLDisplay dpy, EGLenum type, ಸ್ಥಿರಾಂಕ EGLint *attrib_list);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLGETSYNCATTRIBKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint attribute, EGLint *ಮೌಲ್ಯ);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncKHR EGLAPIENTRY eglCreateSyncKHR (EGLDisplay dpy, EGLenum type, ಸ್ಥಿರಾಂಕ EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySyncKHR (EGLDisplay dpy, EGLSyncKHR sync);
EGLAPI EGLint EGLAPIENTRY eglClientWaitSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);
EGLAPI EGLBoolean EGLAPIENTRY eglGetSyncAttribKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint attribute, EGLint *ಮೌಲ್ಯ);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* KHRONOS_SUPPORT_INT64 */
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_fence_sync */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_get_all_proc_ವಿಳಾಸಗಳು
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_get_all_proc_ವಿಳಾಸಗಳು 1
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_get_all_proc_addresses */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_gl_colorspace
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_gl_colorspace 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_GL_COLORSPACE_KHR             0x309D
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_GL_COLORSPACE_SRGB_KHR        0x3089
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_GL_COLORSPACE_ರೇಖೀಯ_KHR      0x308A
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_gl_colorspace */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_gl_renderbuffer_image
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_gl_renderbuffer_image 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_GL_RENDERBUFFER_KHR           0x30B9
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_gl_renderbuffer_image */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_gl_texture_2D_image
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_gl_texture_2D_image 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_GL_TEXTURE_2D_KHR             0x30B1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_GL_TEXTURE_LEVEL_KHR          0x30BC
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_gl_texture_2D_image */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_gl_texture_3D_image
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_gl_texture_3D_image 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_GL_TEXTURE_3D_KHR             0x30B2
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_GL_TEXTURE_ZOFFSET_KHR        0x30BD
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_gl_texture_3D_image */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_gl_texture_cubemap_image
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_gl_texture_cubemap_image 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_GL_TEXTURE_CUBE_MAP_ಧನಾತ್ಮಕ_X_KHR 0x30B3
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_X_KHR 0x30B4
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_GL_TEXTURE_CUBE_MAP_ಧನಾತ್ಮಕ_Y_KHR 0x30B5
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_KHR 0x30B6
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_GL_TEXTURE_CUBE_MAP_ಧನಾತ್ಮಕ_Z_KHR 0x30B7
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_KHR 0x30B8
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_gl_texture_cubemap_image */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_image
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_image 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ *EGLImageKHR;
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NATIVE_PIXMAP_KHR             0x30B0
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NO_IMAGE_KHR                  EGL_CAST(EGLImageKHR,0)
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLImageKHR (EGLAPIENTRYP PFNEGLCREATEIMAGEKHRPROC) (EGLDisplay dpy, EGLContext ctx, EGLenum ಗುರಿ, EGLClient_ಬಫರ್ ಬಫರ್_2, ಸ್ಥಿರಾಂಕ EGLint *attrib_list);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYIMAGEKHRPROC) (EGLDisplay dpy, EGLImageKHR image);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLImageKHR EGLAPIENTRY eglCreateImageKHR (EGLDisplay dpy, EGLContext ctx, EGLenum ಗುರಿ, EGLClient_ಬಫರ್ ಬಫರ್_2, ಸ್ಥಿರಾಂಕ EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyImageKHR (EGLDisplay dpy, EGLImageKHR image);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_image */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_image_ತಳ
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_image_ತಳ 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_IMAGE_PRESERVED_KHR           0x30D2
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_image_base */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_image_pixmap
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_image_pixmap 1
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_image_pixmap */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_ಬೀಗ_surface
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_ಬೀಗ_surface 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_READ_SURFACE_ಬಿಟ್_KHR          0x0001
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_WRITE_SURFACE_ಬಿಟ್_KHR         0x0002
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಬೀಗ_SURFACE_ಬಿಟ್_KHR          0x0080
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_OPTIMAL_FORMAT_ಬಿಟ್_KHR        0x0100
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹೊಂದಿಕೆ_FORMAT_KHR              0x3043
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_FORMAT_RGB_565_EXACT_KHR      0x30C0
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_FORMAT_RGB_565_KHR            0x30C1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_FORMAT_RGBA_8888_EXACT_KHR    0x30C2
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_FORMAT_RGBA_8888_KHR          0x30C3
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_MAP_PRESERVE_PIXELS_KHR       0x30C4
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಬೀಗ_USAGE_HINT_KHR           0x30C5
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_BITMAP_ಸೂಚಕ_KHR            0x30C6
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_BITMAP_PITCH_KHR              0x30C7
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_BITMAP_ORIGIN_KHR             0x30C8
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_BITMAP_PIXEL_RED_ಸ್ಥಾನಾಂತರ_KHR   0x30C9
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_BITMAP_PIXEL_GREEN_ಸ್ಥಾನಾಂತರ_KHR 0x30CA
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_BITMAP_PIXEL_BLUE_ಸ್ಥಾನಾಂತರ_KHR  0x30CB
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_BITMAP_PIXEL_ALPHA_ಸ್ಥಾನಾಂತರ_KHR 0x30CC
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_BITMAP_PIXEL_LUMINANCE_ಸ್ಥಾನಾಂತರ_KHR 0x30CD
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಅಧೋ_ಎಡ_KHR                0x30CE
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಊರ್ಧ್ವ_ಎಡ_KHR                0x30CF
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLLOCKSURFACEKHRPROC) (EGLDisplay dpy, EGLSurface surface, ಸ್ಥಿರಾಂಕ EGLint *attrib_list);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLUNLOCKSURFACEKHRPROC) (EGLDisplay dpy, EGLSurface surface);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_ಬೀಗ_Surface_KHR (EGLDisplay dpy, EGLSurface surface, ಸ್ಥಿರಾಂಕ EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglUnlockSurfaceKHR (EGLDisplay dpy, EGLSurface surface);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_lock_surface */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_ಬೀಗ_surface2
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_ಬೀಗ_surface2 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_BITMAP_PIXEL_ಗಾತ್ರ_KHR         0x3110
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_lock_surface2 */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_ಬೀಗ_surface3
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_ಬೀಗ_surface3 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSURFACE64KHRPROC) (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLAttribKHR *ಮೌಲ್ಯ);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQuerySurface64KHR (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLAttribKHR *ಮೌಲ್ಯ);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_lock_surface3 */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_mutable_render_ಬಫರ್
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_mutable_render_ಬಫರ್ 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_MUTABLE_RENDER_ಬಫರ್_ಬಿಟ್_KHR 0x1000
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_mutable_render_buffer */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_no_config_context
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_no_config_context 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NO_CONFIG_KHR                 EGL_CAST(EGLConfig,0)
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_no_config_context */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_partial_update
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_partial_update 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಬಫರ್_AGE_KHR                0x313D
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLSETDAMAGEREGIONKHRPROC) (EGLDisplay dpy, EGLSurface surface, EGLint *rects, EGLint n_rects);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_ಗಣ_Damage_Region_KHR (EGLDisplay dpy, EGLSurface surface, EGLint *rects, EGLint n_rects);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_partial_update */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_platform_android
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_platform_android 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_PLATFORM_ANDROID_KHR          0x3141
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_platform_android */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_platform_gbm
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_platform_gbm 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_PLATFORM_GBM_KHR              0x31D7
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_platform_gbm */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_platform_wayland
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_platform_wayland 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_PLATFORM_WAYLAND_KHR          0x31D8
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_platform_wayland */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_platform_x11
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_platform_x11 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_PLATFORM_X11_KHR              0x31D5
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_PLATFORM_X11_SCREEN_KHR       0x31D6
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_platform_x11 */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_reusable_sync
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_reusable_sync 1
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ KHRONOS_SUPPORT_INT64
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SYNC_ಸ್ಥಿತಿ_KHR               0x30F1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SIGNALED_KHR                  0x30F2
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_UNSIGNALED_KHR                0x30F3
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_TIMEOUT_EXPIRED_KHR           0x30F5
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_CONDITION_SATISFIED_KHR       0x30F6
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SYNC_TYPE_KHR                 0x30F7
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SYNC_REUSABLE_KHR             0x30FA
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SYNC_FLUSH_COMMANDS_ಬಿಟ್_KHR   0x0001
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_FOREVER_KHR                   0xFFFFFFFFFFFFFFFFull
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NO_SYNC_KHR                   EGL_CAST(EGLSyncKHR,0)
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLSIGNALSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLenum ಬಹುಲಕ);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglSignalSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLenum ಬಹುಲಕ);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* KHRONOS_SUPPORT_INT64 */
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_reusable_sync */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_ಹರಿವು
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_ಹರಿವು 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ *EGLStreamKHR;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ khronos_uint64_t EGLuint64KHR;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ KHRONOS_SUPPORT_INT64
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NO_ಹರಿವು_KHR                 EGL_CAST(EGLStreamKHR,0)
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಗ್ರಾಹಕ_LATENCY_USEC_KHR     0x3210
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಉತ್ಪಾದಕ_ಚೌಕಟ್ಟು_KHR            0x3212
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಗ್ರಾಹಕ_ಚೌಕಟ್ಟು_KHR            0x3213
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_STATE_KHR              0x3214
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_STATE_CREATED_KHR      0x3215
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_STATE_CONNECTING_KHR   0x3216
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_STATE_ಖಾಲಿಗಳು_KHR        0x3217
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_STATE_NEW_ಚೌಕಟ್ಟು_ಲಭ್ಯ_KHR 0x3218
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_STATE_OLD_ಚೌಕಟ್ಟು_ಲಭ್ಯ_KHR 0x3219
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_STATE_DISCONNECTED_KHR 0x321A
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_BAD_ಹರಿವು_KHR                0x321B
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_BAD_STATE_KHR                 0x321C
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLStreamKHR (EGLAPIENTRYP PFNEGLCREATESTREAMKHRPROC) (EGLDisplay dpy, ಸ್ಥಿರಾಂಕ EGLint *attrib_list);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSTREAMKHRPROC) (EGLDisplay dpy, EGLStreamKHR ಹರಿವು);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR ಹರಿವು, EGLenum attribute, EGLint ಮೌಲ್ಯ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMKHRPROC) (EGLDisplay dpy, EGLStreamKHR ಹರಿವು, EGLenum attribute, EGLint *ಮೌಲ್ಯ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMU64KHRPROC) (EGLDisplay dpy, EGLStreamKHR ಹರಿವು, EGLenum attribute, EGLuint64KHR *ಮೌಲ್ಯ);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLStreamKHR EGLAPIENTRY egl_Create_ಹರಿವು_KHR (EGLDisplay dpy, ಸ್ಥಿರಾಂಕ EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY egl_Destroy_ಹರಿವು_KHR (EGLDisplay dpy, EGLStreamKHR ಹರಿವು);
EGLAPI EGLBoolean EGLAPIENTRY egl_ಹರಿವು_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR ಹರಿವು, EGLenum attribute, EGLint ಮೌಲ್ಯ);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_ಹರಿವು_KHR (EGLDisplay dpy, EGLStreamKHR ಹರಿವು, EGLenum attribute, EGLint *ಮೌಲ್ಯ);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryStreamu64KHR (EGLDisplay dpy, EGLStreamKHR ಹರಿವು, EGLenum attribute, EGLuint64KHR *ಮೌಲ್ಯ);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* KHRONOS_SUPPORT_INT64 */
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_stream */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_ಹರಿವು_attrib
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_ಹರಿವು_attrib 1
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ KHRONOS_SUPPORT_INT64
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLStreamKHR (EGLAPIENTRYP PFNEGLCREATESTREAMATTRIBKHRPROC) (EGLDisplay dpy, ಸ್ಥಿರಾಂಕ EGLAttrib *attrib_list);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLSETSTREAMATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR ಹರಿವು, EGLenum attribute, EGLAttrib ಮೌಲ್ಯ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR ಹರಿವು, EGLenum attribute, EGLAttrib *ಮೌಲ್ಯ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERACQUIREATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR ಹರಿವು, ಸ್ಥಿರಾಂಕ EGLAttrib *attrib_list);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERRELEASEATTRIBKHRPROC) (EGLDisplay dpy, EGLStreamKHR ಹರಿವು, ಸ್ಥಿರಾಂಕ EGLAttrib *attrib_list);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLStreamKHR EGLAPIENTRY egl_Create_ಹರಿವು_Attrib_KHR (EGLDisplay dpy, ಸ್ಥಿರಾಂಕ EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY egl_ಗಣ_ಹರಿವು_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR ಹರಿವು, EGLenum attribute, EGLAttrib ಮೌಲ್ಯ);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_ಹರಿವು_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR ಹರಿವು, EGLenum attribute, EGLAttrib *ಮೌಲ್ಯ);
EGLAPI EGLBoolean EGLAPIENTRY egl_ಹರಿವು_ಗ್ರಾಹಕ_Acquire_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR ಹರಿವು, ಸ್ಥಿರಾಂಕ EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY egl_ಹರಿವು_ಗ್ರಾಹಕ_Release_Attrib_KHR (EGLDisplay dpy, EGLStreamKHR ಹರಿವು, ಸ್ಥಿರಾಂಕ EGLAttrib *attrib_list);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* KHRONOS_SUPPORT_INT64 */
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_stream_attrib */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_ಹರಿವು_ಗ್ರಾಹಕ_gltexture
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_ಹರಿವು_ಗ್ರಾಹಕ_gltexture 1
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_KHR_ಹರಿವು
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಗ್ರಾಹಕ_ACQUIRE_TIMEOUT_USEC_KHR 0x321E
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALKHRPROC) (EGLDisplay dpy, EGLStreamKHR ಹರಿವು);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERACQUIREKHRPROC) (EGLDisplay dpy, EGLStreamKHR ಹರಿವು);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERRELEASEKHRPROC) (EGLDisplay dpy, EGLStreamKHR ಹರಿವು);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_ಹರಿವು_ಗ್ರಾಹಕ_GLTexture_External_KHR (EGLDisplay dpy, EGLStreamKHR ಹರಿವು);
EGLAPI EGLBoolean EGLAPIENTRY egl_ಹರಿವು_ಗ್ರಾಹಕ_Acquire_KHR (EGLDisplay dpy, EGLStreamKHR ಹರಿವು);
EGLAPI EGLBoolean EGLAPIENTRY egl_ಹರಿವು_ಗ್ರಾಹಕ_Release_KHR (EGLDisplay dpy, EGLStreamKHR ಹರಿವು);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_stream */
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_stream_consumer_gltexture */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_ಹರಿವು_cross_process_fd
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_ಹರಿವು_cross_process_fd 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೂರ್ಣಾಂಕ EGLNativeFileDescriptorKHR;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_KHR_ಹರಿವು
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NO_FILE_DESCRIPTOR_KHR        EGL_CAST(EGLNativeFileDescriptorKHR,-1)
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLNativeFileDescriptorKHR (EGLAPIENTRYP PFNEGLGETSTREAMFILEDESCRIPTORKHRPROC) (EGLDisplay dpy, EGLStreamKHR ಹರಿವು);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLStreamKHR (EGLAPIENTRYP PFNEGLCREATESTREAMFROMFILEDESCRIPTORKHRPROC) (EGLDisplay dpy, EGLNativeFileDescriptorKHR file_descriptor);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLNativeFileDescriptorKHR EGLAPIENTRY egl_Get_ಹರಿವು_File_Descriptor_KHR (EGLDisplay dpy, EGLStreamKHR ಹರಿವು);
EGLAPI EGLStreamKHR EGLAPIENTRY egl_Create_ಹರಿವು_From_File_Descriptor_KHR (EGLDisplay dpy, EGLNativeFileDescriptorKHR file_descriptor);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_stream */
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_stream_cross_process_fd */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_ಹರಿವು_fifo
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_ಹರಿವು_fifo 1
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_KHR_ಹರಿವು
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_FIFO_ಉದ್ದಳತೆ_KHR        0x31FC
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_ಸಮಯ_NOW_KHR           0x31FD
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_ಸಮಯ_ಗ್ರಾಹಕ_KHR      0x31FE
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_ಸಮಯ_ಉತ್ಪಾದಕ_KHR      0x31FF
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMTIMEKHRPROC) (EGLDisplay dpy, EGLStreamKHR ಹರಿವು, EGLenum attribute, EGLTimeKHR *ಮೌಲ್ಯ);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_ಹರಿವು_ಸಮಯ_KHR (EGLDisplay dpy, EGLStreamKHR ಹರಿವು, EGLenum attribute, EGLTimeKHR *ಮೌಲ್ಯ);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_stream */
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_stream_fifo */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_ಹರಿವು_ಉತ್ಪಾದಕ_aldatalocator
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_ಹರಿವು_ಉತ್ಪಾದಕ_aldatalocator 1
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_KHR_ಹರಿವು
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_stream */
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_stream_producer_aldatalocator */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_ಹರಿವು_ಉತ್ಪಾದಕ_eglsurface
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_ಹರಿವು_ಉತ್ಪಾದಕ_eglsurface 1
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_KHR_ಹರಿವು
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_ಬಿಟ್_KHR                0x0800
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLSurface (EGLAPIENTRYP PFNEGLCREATESTREAMPRODUCERSURFACEKHRPROC) (EGLDisplay dpy, EGLConfig config, EGLStreamKHR ಹರಿವು, ಸ್ಥಿರಾಂಕ EGLint *attrib_list);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSurface EGLAPIENTRY egl_Create_ಹರಿವು_ಉತ್ಪಾದಕ_Surface_KHR (EGLDisplay dpy, EGLConfig config, EGLStreamKHR ಹರಿವು, ಸ್ಥಿರಾಂಕ EGLint *attrib_list);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_stream */
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_stream_producer_eglsurface */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_surfaceless_context
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_surfaceless_context 1
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_surfaceless_context */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_ಅದಲುಬದಲು_buffers_with_damage
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_ಅದಲುಬದಲು_buffers_with_damage 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSWITHDAMAGEKHRPROC) (EGLDisplay dpy, EGLSurface surface, ಸ್ಥಿರಾಂಕ EGLint *rects, EGLint n_rects);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_ಅದಲುಬದಲು_Buffers_With_Damage_KHR (EGLDisplay dpy, EGLSurface surface, ಸ್ಥಿರಾಂಕ EGLint *rects, EGLint n_rects);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_swap_buffers_with_damage */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_vg_ಪೋಷಕ_image
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_vg_ಪೋಷಕ_image 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_VG_ಪೋಷಕ_IMAGE_KHR           0x30BA
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_vg_parent_image */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_KHR_wait_sync
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_KHR_wait_sync 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLint (EGLAPIENTRYP PFNEGLWAITSYNCKHRPROC) (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLint EGLAPIENTRY eglWaitSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_KHR_wait_sync */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_ANDROID_GLES_layers
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ANDROID_GLES_layers 1
#ಆದರೆ_ಅಂತ್ಯ /* EGL_ANDROID_GLES_layers */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_ANDROID_blob_cache
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ANDROID_blob_cache 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ khronos_ssize_t EGLsizeiANDROID;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (*EGLSetBlobFuncANDROID) (ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ಕೀಲಿ, EGLsizeiANDROID ಕೀಲಿ_ಗಾತ್ರ_2, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ಮೌಲ್ಯ, EGLsizeiANDROID ಮೌಲ್ಯ_ಗಾತ್ರ_2);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLsizeiANDROID (*EGLGetBlobFuncANDROID) (ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ಕೀಲಿ, EGLsizeiANDROID ಕೀಲಿ_ಗಾತ್ರ_2, ಶೂನ್ಯ *ಮೌಲ್ಯ, EGLsizeiANDROID ಮೌಲ್ಯ_ಗಾತ್ರ_2);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (EGLAPIENTRYP PFNEGLSETBLOBCACHEFUNCSANDROIDPROC) (EGLDisplay dpy, EGLSetBlobFuncANDROID ಗಣ, EGLGetBlobFuncANDROID get);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI ಶೂನ್ಯ EGLAPIENTRY egl_ಗಣ_Blob_Cache_Funcs_ANDROID (EGLDisplay dpy, EGLSetBlobFuncANDROID ಗಣ, EGLGetBlobFuncANDROID get);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_ANDROID_blob_cache */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_ANDROID_create_native_client_ಬಫರ್
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ANDROID_create_native_client_ಬಫರ್ 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NATIVE_ಬಫರ್_USAGE_ANDROID   0x3143
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NATIVE_ಬಫರ್_USAGE_PROTECTED_ಬಿಟ್_ANDROID 0x00000001
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NATIVE_ಬಫರ್_USAGE_RENDERBUFFER_ಬಿಟ್_ANDROID 0x00000002
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NATIVE_ಬಫರ್_USAGE_TEXTURE_ಬಿಟ್_ANDROID 0x00000004
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLClient_ಬಫರ್ (EGLAPIENTRYP PFNEGLCREATENATIVECLIENTBUFFERANDROIDPROC) (ಸ್ಥಿರಾಂಕ EGLint *attrib_list);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLClient_ಬಫರ್ EGLAPIENTRY egl_Create_Native_Client_ಬಫರ್_ANDROID (ಸ್ಥಿರಾಂಕ EGLint *attrib_list);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_ANDROID_create_native_client_buffer */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_ANDROID_framebuffer_ಗುರಿ
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ANDROID_framebuffer_ಗುರಿ 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_FRAMEBUFFER_ಗುರಿ_ANDROID    0x3147
#ಆದರೆ_ಅಂತ್ಯ /* EGL_ANDROID_framebuffer_target */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_ANDROID_front_ಬಫರ್_auto_refresh
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ANDROID_front_ಬಫರ್_auto_refresh 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_FRONT_ಬಫರ್_AUTO_REFRESH_ANDROID 0x314C
#ಆದರೆ_ಅಂತ್ಯ /* EGL_ANDROID_front_buffer_auto_refresh */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_ANDROID_get_ಚೌಕಟ್ಟು_timestamps
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ANDROID_get_ಚೌಕಟ್ಟು_timestamps 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ khronos_stime_nanoseconds_t EGLnsecsANDROID;
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_TIMESTAMP_PENDING_ANDROID     EGL_CAST(EGLnsecsANDROID,-2)
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_TIMESTAMP_INVALID_ANDROID     EGL_CAST(EGLnsecsANDROID,-1)
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_TIMESTAMPS_ANDROID            0x3430
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಸಂಯುಕ್ತ_DEADLINE_ANDROID    0x3431
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಸಂಯುಕ್ತ_INTERVAL_ANDROID    0x3432
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಸಂಯುಕ್ತ_ಗಮ್ಯ_PRESENT_LATENCY_ANDROID 0x3433
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_REQUESTED_PRESENT_ಸಮಯ_ANDROID 0x3434
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_RENDERING_COMPLETE_ಸಮಯ_ANDROID 0x3435
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_COMPOSITION_LATCH_ಸಮಯ_ANDROID 0x3436
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಮೊದಲ_COMPOSITION_ಆರಂಭ_ಸಮಯ_ANDROID 0x3437
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಕೊನೆಯ_COMPOSITION_ಆರಂಭ_ಸಮಯ_ANDROID 0x3438
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಮೊದಲ_COMPOSITION_GPU_ಪೂರ್ಣಗೊಂಡ_ಸಮಯ_ANDROID 0x3439
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DISPLAY_PRESENT_ಸಮಯ_ANDROID  0x343A
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಸರತಿಯಿಂದ_ತೆಗೆ_READY_ಸಮಯ_ANDROID    0x343B
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_READS_ಮುಗಿದ_ಸಮಯ_ANDROID       0x343C
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLGETCOMPOSITORTIMINGSUPPORTEDANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLint name);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLGETCOMPOSITORTIMINGANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLint ಅಂಕೆ_Timestamps,  ಸ್ಥಿರಾಂಕ EGLint *ಹೆಸರುಗಳು, EGLnsecsANDROID *ಮೌಲ್ಯಗಳು);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLGETNEXTFRAMEIDANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR *ಚೌಕಟ್ಟು_Id);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLGETFRAMETIMESTAMPSUPPORTEDANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLint timestamp);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLGETFRAMETIMESTAMPSANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR ಚೌಕಟ್ಟು_Id, EGLint ಅಂಕೆ_Timestamps,  ಸ್ಥಿರಾಂಕ EGLint *timestamps, EGLnsecsANDROID *ಮೌಲ್ಯಗಳು);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglGetCompositorTimingSupportedANDROID (EGLDisplay dpy, EGLSurface surface, EGLint name);
EGLAPI EGLBoolean EGLAPIENTRY eglGetCompositorTimingANDROID (EGLDisplay dpy, EGLSurface surface, EGLint ಅಂಕೆ_Timestamps,  ಸ್ಥಿರಾಂಕ EGLint *ಹೆಸರುಗಳು, EGLnsecsANDROID *ಮೌಲ್ಯಗಳು);
EGLAPI EGLBoolean EGLAPIENTRY egl_Get_ಮುಂದಿನ_ಚೌಕಟ್ಟು_Id_ANDROID (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR *ಚೌಕಟ್ಟು_Id);
EGLAPI EGLBoolean EGLAPIENTRY egl_Get_ಚೌಕಟ್ಟು_Timestamp_Supported_ANDROID (EGLDisplay dpy, EGLSurface surface, EGLint timestamp);
EGLAPI EGLBoolean EGLAPIENTRY egl_Get_ಚೌಕಟ್ಟು_Timestamps_ANDROID (EGLDisplay dpy, EGLSurface surface, EGLuint64KHR ಚೌಕಟ್ಟು_Id, EGLint ಅಂಕೆ_Timestamps,  ಸ್ಥಿರಾಂಕ EGLint *timestamps, EGLnsecsANDROID *ಮೌಲ್ಯಗಳು);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_ANDROID_get_frame_timestamps */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_ANDROID_get_native_client_ಬಫರ್
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ANDROID_get_native_client_ಬಫರ್ 1
ರಚನೆ AHardware_ಬಫರ್;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLClient_ಬಫರ್ (EGLAPIENTRYP PFNEGLGETNATIVECLIENTBUFFERANDROIDPROC) (ಸ್ಥಿರಾಂಕ ರಚನೆ AHardware_ಬಫರ್ *ಬಫರ್_2);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLClient_ಬಫರ್ EGLAPIENTRY egl_Get_Native_Client_ಬಫರ್_ANDROID (ಸ್ಥಿರಾಂಕ ರಚನೆ AHardware_ಬಫರ್ *ಬಫರ್_2);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_ANDROID_get_native_client_buffer */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_ANDROID_image_native_ಬಫರ್
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ANDROID_image_native_ಬಫರ್ 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NATIVE_ಬಫರ್_ANDROID         0x3140
#ಆದರೆ_ಅಂತ್ಯ /* EGL_ANDROID_image_native_buffer */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_ANDROID_native_fence_sync
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ANDROID_native_fence_sync 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SYNC_NATIVE_FENCE_ANDROID     0x3144
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SYNC_NATIVE_FENCE_FD_ANDROID  0x3145
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SYNC_NATIVE_FENCE_SIGNALED_ANDROID 0x3146
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NO_NATIVE_FENCE_FD_ANDROID    -1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLint (EGLAPIENTRYP PFNEGLDUPNATIVEFENCEFDANDROIDPROC) (EGLDisplay dpy, EGLSyncKHR sync);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLint EGLAPIENTRY eglDupNativeFenceFDANDROID (EGLDisplay dpy, EGLSyncKHR sync);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_ANDROID_native_fence_sync */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_ANDROID_presentation_ಸಮಯ
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ANDROID_presentation_ಸಮಯ 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLPRESENTATIONTIMEANDROIDPROC) (EGLDisplay dpy, EGLSurface surface, EGLnsecsANDROID ಸಮಯ);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Presentation_ಸಮಯ_ANDROID (EGLDisplay dpy, EGLSurface surface, EGLnsecsANDROID ಸಮಯ);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_ANDROID_presentation_time */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_ANDROID_recordable
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ANDROID_recordable 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_RECORDABLE_ANDROID            0x3142
#ಆದರೆ_ಅಂತ್ಯ /* EGL_ANDROID_recordable */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_ANDROID_telemetry_hint
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ANDROID_telemetry_hint 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_TELEMETRY_HINT_ANDROID        0x3570
#ಆದರೆ_ಅಂತ್ಯ /* EGL_ANDROID_telemetry_hint */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_ANGLE_d3d_share_handle_client_ಬಫರ್
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ANGLE_d3d_share_handle_client_ಬಫರ್ 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_D3D_TEXTURE_2D_SHARE_HANDLE_ANGLE 0x3200
#ಆದರೆ_ಅಂತ್ಯ /* EGL_ANGLE_d3d_share_handle_client_buffer */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_ANGLE_device_d3d
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ANGLE_device_d3d 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_D3D9_DEVICE_ANGLE             0x33A0
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_D3D11_DEVICE_ANGLE            0x33A1
#ಆದರೆ_ಅಂತ್ಯ /* EGL_ANGLE_device_d3d */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_ANGLE_query_surface_ಸೂಚಕ
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ANGLE_query_surface_ಸೂಚಕ 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSURFACEPOINTERANGLEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint attribute, ಶೂನ್ಯ **ಮೌಲ್ಯ);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Surface_ಸೂಚಕ_ANGLE (EGLDisplay dpy, EGLSurface surface, EGLint attribute, ಶೂನ್ಯ **ಮೌಲ್ಯ);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_ANGLE_query_surface_pointer */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_ANGLE_surface_d3d_texture_2d_share_handle
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ANGLE_surface_d3d_texture_2d_share_handle 1
#ಆದರೆ_ಅಂತ್ಯ /* EGL_ANGLE_surface_d3d_texture_2d_share_handle */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_ANGLE_sync_control_ದರ
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ANGLE_sync_control_ದರ 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLGETMSCRATEANGLEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint *numerator, EGLint *denominator);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Get_Msc_ದರ_ANGLE (EGLDisplay dpy, EGLSurface surface, EGLint *numerator, EGLint *denominator);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_ANGLE_sync_control_rate */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_ANGLE_ಕಿಟಕಿ_fixed_ಗಾತ್ರ
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ANGLE_ಕಿಟಕಿ_fixed_ಗಾತ್ರ 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_FIXED_ಗಾತ್ರ_ANGLE              0x3201
#ಆದರೆ_ಅಂತ್ಯ /* EGL_ANGLE_window_fixed_size */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_ARM_image_format
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ARM_image_format 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_COLOR_COMPONENT_TYPE_UNSIGNED_INTEGER_ARM 0x3287
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_COLOR_COMPONENT_TYPE_INTEGER_ARM 0x3288
#ಆದರೆ_ಅಂತ್ಯ /* EGL_ARM_image_format */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_ARM_implicit_external_sync
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ARM_implicit_external_sync 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SYNC_ಪೂರ್ವ_COMMANDS_IMPLICIT_EXTERNAL_ARM 0x328A
#ಆದರೆ_ಅಂತ್ಯ /* EGL_ARM_implicit_external_sync */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_ARM_pixmap_multisample_discard
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ARM_pixmap_multisample_discard 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DISCARD_SAMPLES_ARM           0x3286
#ಆದರೆ_ಅಂತ್ಯ /* EGL_ARM_pixmap_multisample_discard */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_bind_ಗಮ್ಯ_front
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_bind_ಗಮ್ಯ_front 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_FRONT_ಬಫರ್_EXT              0x3464
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_bind_to_front */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_ಬಫರ್_age
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_ಬಫರ್_age 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಬಫರ್_AGE_EXT                0x313D
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_buffer_age */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_client_extensions
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_client_extensions 1
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_client_extensions */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_client_sync
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_client_sync 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SYNC_CLIENT_EXT               0x3364
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SYNC_CLIENT_SIGNAL_EXT        0x3365
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLCLIENTSIGNALSYNCEXTPROC) (EGLDisplay dpy, EGLSync sync, ಸ್ಥಿರಾಂಕ EGLAttrib *attrib_list);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglClientSignalSyncEXT (EGLDisplay dpy, EGLSync sync, ಸ್ಥಿರಾಂಕ EGLAttrib *attrib_list);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_client_sync */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_compositor
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_compositor 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_PRIMARY_COMPOSITOR_CONTEXT_EXT 0x3460
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXTERNAL_REF_ID_EXT           0x3461
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_COMPOSITOR_DROP_NEWEST_ಚೌಕಟ್ಟು_EXT 0x3462
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_COMPOSITOR_KEEP_NEWEST_ಚೌಕಟ್ಟು_EXT 0x3463
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETCONTEXTLISTEXTPROC) (ಸ್ಥಿರಾಂಕ EGLint *external_ref_ids, EGLint ಅಂಕೆ_entries);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETCONTEXTATTRIBUTESEXTPROC) (EGLint external_ref_id, ಸ್ಥಿರಾಂಕ EGLint *context_ಗುಣಲಕ್ಷಣಗಳು, EGLint ಅಂಕೆ_entries);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETWINDOWLISTEXTPROC) (EGLint external_ref_id, ಸ್ಥಿರಾಂಕ EGLint *external_win_ids, EGLint ಅಂಕೆ_entries);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETWINDOWATTRIBUTESEXTPROC) (EGLint external_win_id, ಸ್ಥಿರಾಂಕ EGLint *ಕಿಟಕಿ_ಗುಣಲಕ್ಷಣಗಳು, EGLint ಅಂಕೆ_entries);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORBINDTEXWINDOWEXTPROC) (EGLint external_win_id);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSETSIZEEXTPROC) (EGLint external_win_id, EGLint ಅಗಲ, EGLint ಎತ್ತರ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLCOMPOSITORSWAPPOLICYEXTPROC) (EGLint external_win_id, EGLint policy);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_ಗಣ_Context_List_EXT (ಸ್ಥಿರಾಂಕ EGLint *external_ref_ids, EGLint ಅಂಕೆ_entries);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_ಗಣ_Context_ಗುಣಲಕ್ಷಣಗಳು_EXT (EGLint external_ref_id, ಸ್ಥಿರಾಂಕ EGLint *context_ಗುಣಲಕ್ಷಣಗಳು, EGLint ಅಂಕೆ_entries);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_ಗಣ_ಕಿಟಕಿ_List_EXT (EGLint external_ref_id, ಸ್ಥಿರಾಂಕ EGLint *external_win_ids, EGLint ಅಂಕೆ_entries);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_ಗಣ_ಕಿಟಕಿ_ಗುಣಲಕ್ಷಣಗಳು_EXT (EGLint external_win_id, ಸ್ಥಿರಾಂಕ EGLint *ಕಿಟಕಿ_ಗುಣಲಕ್ಷಣಗಳು, EGLint ಅಂಕೆ_entries);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_Bind_Tex_ಕಿಟಕಿ_EXT (EGLint external_win_id);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_ಗಣ_ಗಾತ್ರ_EXT (EGLint external_win_id, EGLint ಅಗಲ, EGLint ಎತ್ತರ);
EGLAPI EGLBoolean EGLAPIENTRY egl_Compositor_ಅದಲುಬದಲು_Policy_EXT (EGLint external_win_id, EGLint policy);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_compositor */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_config_select_ಗುಂಪು
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_config_select_ಗುಂಪು 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_CONFIG_SELECT_ಗುಂಪು_EXT       0x34C0
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_config_select_group */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_create_context_robustness
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_create_context_robustness 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT 0x30BF
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_EXT 0x3138
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NO_RESET_NOTIFICATION_EXT     0x31BE
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_LOSE_CONTEXT_ON_RESET_EXT     0x31BF
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_create_context_robustness */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_device_ತಳ
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_device_ತಳ 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ *EGLDeviceEXT;
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NO_DEVICE_EXT                 EGL_CAST(EGLDeviceEXT,0)
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_BAD_DEVICE_EXT                0x322B
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DEVICE_EXT                    0x322C
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICEATTRIBEXTPROC) (EGLDeviceEXT device, EGLint attribute, EGLAttrib *ಮೌಲ್ಯ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *(EGLAPIENTRYP PFNEGLQUERYDEVICESTRINGEXTPROC) (EGLDeviceEXT device, EGLint name);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICESEXTPROC) (EGLint max_devices, EGLDeviceEXT *devices, EGLint *ಅಂಕೆ_devices);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDISPLAYATTRIBEXTPROC) (EGLDisplay dpy, EGLint attribute, EGLAttrib *ಮೌಲ್ಯ);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDeviceAttribEXT (EGLDeviceEXT device, EGLint attribute, EGLAttrib *ಮೌಲ್ಯ);
EGLAPI ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *EGLAPIENTRY eglQueryDeviceStringEXT (EGLDeviceEXT device, EGLint name);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDevicesEXT (EGLint max_devices, EGLDeviceEXT *devices, EGLint *ಅಂಕೆ_devices);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDisplayAttribEXT (EGLDisplay dpy, EGLint attribute, EGLAttrib *ಮೌಲ್ಯ);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_device_base */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_device_drm
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_device_drm 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DRM_DEVICE_FILE_EXT           0x3233
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DRM_MASTER_FD_EXT             0x333C
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_device_drm */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_device_drm_render_ಗಂಟು
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_device_drm_render_ಗಂಟು 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DRM_RENDER_ಗಂಟು_FILE_EXT      0x3377
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_device_drm_render_node */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_device_enumeration
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_device_enumeration 1
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_device_enumeration */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_device_openwf
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_device_openwf 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_OPENWF_DEVICE_ID_EXT          0x3237
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_OPENWF_DEVICE_EXT             0x333D
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_device_openwf */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_device_persistent_id
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_device_persistent_id 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DEVICE_UUID_EXT               0x335C
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DRIVER_UUID_EXT               0x335D
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DRIVER_NAME_EXT               0x335E
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDEVICEBINARYEXTPROC) (EGLDeviceEXT device, EGLint name, EGLint max_ಗಾತ್ರ, ಶೂನ್ಯ *ಮೌಲ್ಯ, EGLint *ಗಾತ್ರ_2);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Device_ದ್ವಿಮಾನ_EXT (EGLDeviceEXT device, EGLint name, EGLint max_ಗಾತ್ರ, ಶೂನ್ಯ *ಮೌಲ್ಯ, EGLint *ಗಾತ್ರ_2);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_device_persistent_id */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_device_query
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_device_query 1
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_device_query */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_device_query_name
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_device_query_name 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_RENDERER_EXT                  0x335F
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_device_query_name */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_device_type
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_device_type 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DEVICE_TYPE_EXT               0x3590
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DEVICE_TYPE_OTHER_EXT         0x3591
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DEVICE_TYPE_INTEGRATED_GPU_EXT 0x3592
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DEVICE_TYPE_DISCRETE_GPU_EXT  0x3593
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DEVICE_TYPE_CPU_EXT           0x3594
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_device_type */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_display_alloc
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_display_alloc 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ALLOC_NEW_DISPLAY_EXT         0x3379
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYDISPLAYEXTPROC) (EGLDisplay dpy);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyDisplayEXT (EGLDisplay dpy);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_display_alloc */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_explicit_device
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_explicit_device 1
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_explicit_device */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_gl_colorspace_bt2020_hlg
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_gl_colorspace_bt2020_hlg 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_GL_COLORSPACE_BT2020_HLG_EXT  0x3540
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_gl_colorspace_bt2020_hlg */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_gl_colorspace_bt2020_ರೇಖೀಯ
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_gl_colorspace_bt2020_ರೇಖೀಯ 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_GL_COLORSPACE_BT2020_ರೇಖೀಯ_EXT 0x333F
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_gl_colorspace_bt2020_linear */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_gl_colorspace_bt2020_pq
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_gl_colorspace_bt2020_pq 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_GL_COLORSPACE_BT2020_PQ_EXT   0x3340
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_gl_colorspace_bt2020_pq */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_gl_colorspace_display_p3
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_gl_colorspace_display_p3 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_GL_COLORSPACE_DISPLAY_P3_EXT  0x3363
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_gl_colorspace_display_p3 */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_gl_colorspace_display_p3_ರೇಖೀಯ
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_gl_colorspace_display_p3_ರೇಖೀಯ 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_GL_COLORSPACE_DISPLAY_P3_ರೇಖೀಯ_EXT 0x3362
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_gl_colorspace_display_p3_linear */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_gl_colorspace_display_p3_passthrough
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_gl_colorspace_display_p3_passthrough 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_GL_COLORSPACE_DISPLAY_P3_PASSTHROUGH_EXT 0x3490
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_gl_colorspace_display_p3_passthrough */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_gl_colorspace_scrgb
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_gl_colorspace_scrgb 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_GL_COLORSPACE_SCRGB_EXT       0x3351
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_gl_colorspace_scrgb */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_gl_colorspace_scrgb_ರೇಖೀಯ
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_gl_colorspace_scrgb_ರೇಖೀಯ 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_GL_COLORSPACE_SCRGB_ರೇಖೀಯ_EXT 0x3350
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_gl_colorspace_scrgb_linear */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_image_dma_buf_import
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_image_dma_buf_import 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_LINUX_DMA_BUF_EXT             0x3270
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_LINUX_DRM_FOURCC_EXT          0x3271
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DMA_BUF_PLANE0_FD_EXT         0x3272
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DMA_BUF_PLANE0_ಸ್ಥಾನಾಂತರ_EXT     0x3273
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DMA_BUF_PLANE0_PITCH_EXT      0x3274
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DMA_BUF_PLANE1_FD_EXT         0x3275
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DMA_BUF_PLANE1_ಸ್ಥಾನಾಂತರ_EXT     0x3276
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DMA_BUF_PLANE1_PITCH_EXT      0x3277
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DMA_BUF_PLANE2_FD_EXT         0x3278
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DMA_BUF_PLANE2_ಸ್ಥಾನಾಂತರ_EXT     0x3279
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DMA_BUF_PLANE2_PITCH_EXT      0x327A
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_YUV_COLOR_SPACE_HINT_EXT      0x327B
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SAMPLE_RANGE_HINT_EXT         0x327C
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_YUV_CHROMA_HORIZONTAL_SITING_HINT_EXT 0x327D
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_YUV_CHROMA_VERTICAL_SITING_HINT_EXT 0x327E
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ITU_REC601_EXT                0x327F
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ITU_REC709_EXT                0x3280
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ITU_REC2020_EXT               0x3281
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_YUV_ತುಂಬಿದ_RANGE_EXT            0x3282
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_YUV_NARROW_RANGE_EXT          0x3283
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_YUV_CHROMA_SITING_0_EXT       0x3284
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_YUV_CHROMA_SITING_0_5_EXT     0x3285
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_image_dma_buf_import */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_image_dma_buf_import_modifiers
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_image_dma_buf_import_modifiers 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DMA_BUF_PLANE3_FD_EXT         0x3440
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DMA_BUF_PLANE3_ಸ್ಥಾನಾಂತರ_EXT     0x3441
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DMA_BUF_PLANE3_PITCH_EXT      0x3442
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DMA_BUF_PLANE0_MODIFIER_LO_EXT 0x3443
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DMA_BUF_PLANE0_MODIFIER_HI_EXT 0x3444
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DMA_BUF_PLANE1_MODIFIER_LO_EXT 0x3445
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DMA_BUF_PLANE1_MODIFIER_HI_EXT 0x3446
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DMA_BUF_PLANE2_MODIFIER_LO_EXT 0x3447
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DMA_BUF_PLANE2_MODIFIER_HI_EXT 0x3448
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DMA_BUF_PLANE3_MODIFIER_LO_EXT 0x3449
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DMA_BUF_PLANE3_MODIFIER_HI_EXT 0x344A
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDMABUFFORMATSEXTPROC) (EGLDisplay dpy, EGLint max_formats, EGLint *formats, EGLint *ಅಂಕೆ_formats);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDMABUFMODIFIERSEXTPROC) (EGLDisplay dpy, EGLint format, EGLint max_modifiers, EGLuint64KHR *modifiers, EGLBoolean *external_only, EGLint *ಅಂಕೆ_modifiers);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDmaBufFormatsEXT (EGLDisplay dpy, EGLint max_formats, EGLint *formats, EGLint *ಅಂಕೆ_formats);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDmaBufModifiersEXT (EGLDisplay dpy, EGLint format, EGLint max_modifiers, EGLuint64KHR *modifiers, EGLBoolean *external_only, EGLint *ಅಂಕೆ_modifiers);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_image_dma_buf_import_modifiers */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_image_gl_colorspace
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_image_gl_colorspace 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_GL_COLORSPACE_DEFAULT_EXT     0x314D
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_image_gl_colorspace */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_image_implicit_sync_control
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_image_implicit_sync_control 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_IMPORT_SYNC_TYPE_EXT          0x3470
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_IMPORT_IMPLICIT_SYNC_EXT      0x3471
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_IMPORT_EXPLICIT_SYNC_EXT      0x3472
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_image_implicit_sync_control */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_multiview_ಕಿಟಕಿ
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_multiview_ಕಿಟಕಿ 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_MULTIVIEW_VIEW_ಎಣಿಕೆ_EXT      0x3134
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_multiview_window */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_output_ತಳ
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_output_ತಳ 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ *EGLOutputLayerEXT;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ *EGLOutput_ಪೋರ್ಟ್_EXT;
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NO_OUTPUT_LAYER_EXT           EGL_CAST(EGLOutputLayerEXT,0)
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NO_OUTPUT_ಪೋರ್ಟ್_EXT            EGL_CAST(EGLOutput_ಪೋರ್ಟ್_EXT,0)
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_BAD_OUTPUT_LAYER_EXT          0x322D
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_BAD_OUTPUT_ಪೋರ್ಟ್_EXT           0x322E
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಅದಲುಬದಲು_INTERVAL_EXT             0x322F
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLGETOUTPUTLAYERSEXTPROC) (EGLDisplay dpy, ಸ್ಥಿರಾಂಕ EGLAttrib *attrib_list, EGLOutputLayerEXT *layers, EGLint max_layers, EGLint *ಅಂಕೆ_layers);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLGETOUTPUTPORTSEXTPROC) (EGLDisplay dpy, ಸ್ಥಿರಾಂಕ EGLAttrib *attrib_list, EGLOutput_ಪೋರ್ಟ್_EXT *ports, EGLint max_ports, EGLint *ಅಂಕೆ_ports);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLOUTPUTLAYERATTRIBEXTPROC) (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib ಮೌಲ್ಯ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYOUTPUTLAYERATTRIBEXTPROC) (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib *ಮೌಲ್ಯ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *(EGLAPIENTRYP PFNEGLQUERYOUTPUTLAYERSTRINGEXTPROC) (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint name);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLOUTPUTPORTATTRIBEXTPROC) (EGLDisplay dpy, EGLOutput_ಪೋರ್ಟ್_EXT ಪೋರ್ಟ್, EGLint attribute, EGLAttrib ಮೌಲ್ಯ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYOUTPUTPORTATTRIBEXTPROC) (EGLDisplay dpy, EGLOutput_ಪೋರ್ಟ್_EXT ಪೋರ್ಟ್, EGLint attribute, EGLAttrib *ಮೌಲ್ಯ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *(EGLAPIENTRYP PFNEGLQUERYOUTPUTPORTSTRINGEXTPROC) (EGLDisplay dpy, EGLOutput_ಪೋರ್ಟ್_EXT ಪೋರ್ಟ್, EGLint name);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglGetOutputLayersEXT (EGLDisplay dpy, ಸ್ಥಿರಾಂಕ EGLAttrib *attrib_list, EGLOutputLayerEXT *layers, EGLint max_layers, EGLint *ಅಂಕೆ_layers);
EGLAPI EGLBoolean EGLAPIENTRY eglGetOutputPortsEXT (EGLDisplay dpy, ಸ್ಥಿರಾಂಕ EGLAttrib *attrib_list, EGLOutput_ಪೋರ್ಟ್_EXT *ports, EGLint max_ports, EGLint *ಅಂಕೆ_ports);
EGLAPI EGLBoolean EGLAPIENTRY eglOutputLayerAttribEXT (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib ಮೌಲ್ಯ);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryOutputLayerAttribEXT (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib *ಮೌಲ್ಯ);
EGLAPI ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *EGLAPIENTRY eglQueryOutputLayerStringEXT (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint name);
EGLAPI EGLBoolean EGLAPIENTRY egl_Output_ಪೋರ್ಟ್_Attrib_EXT (EGLDisplay dpy, EGLOutput_ಪೋರ್ಟ್_EXT ಪೋರ್ಟ್, EGLint attribute, EGLAttrib ಮೌಲ್ಯ);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Output_ಪೋರ್ಟ್_Attrib_EXT (EGLDisplay dpy, EGLOutput_ಪೋರ್ಟ್_EXT ಪೋರ್ಟ್, EGLint attribute, EGLAttrib *ಮೌಲ್ಯ);
EGLAPI ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *EGLAPIENTRY egl_Query_Output_ಪೋರ್ಟ್_String_EXT (EGLDisplay dpy, EGLOutput_ಪೋರ್ಟ್_EXT ಪೋರ್ಟ್, EGLint name);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_output_base */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_output_drm
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_output_drm 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DRM_CRTC_EXT                  0x3234
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DRM_PLANE_EXT                 0x3235
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DRM_CONNECTOR_EXT             0x3236
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_output_drm */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_output_openwf
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_output_openwf 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_OPENWF_PIPELINE_ID_EXT        0x3238
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_OPENWF_ಪೋರ್ಟ್_ID_EXT            0x3239
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_output_openwf */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_pixel_format_float
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_pixel_format_float 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_COLOR_COMPONENT_TYPE_EXT      0x3339
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_COLOR_COMPONENT_TYPE_FIXED_EXT 0x333A
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT 0x333B
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_pixel_format_float */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_platform_ತಳ
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_platform_ತಳ 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYEXTPROC) (EGLenum platform, ಶೂನ್ಯ *native_display, ಸ್ಥಿರಾಂಕ EGLint *attrib_list);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLSurface (EGLAPIENTRYP PFNEGLCREATEPLATFORMWINDOWSURFACEEXTPROC) (EGLDisplay dpy, EGLConfig config, ಶೂನ್ಯ *native_ಕಿಟಕಿ, ಸ್ಥಿರಾಂಕ EGLint *attrib_list);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLSurface (EGLAPIENTRYP PFNEGLCREATEPLATFORMPIXMAPSURFACEEXTPROC) (EGLDisplay dpy, EGLConfig config, ಶೂನ್ಯ *native_pixmap, ಸ್ಥಿರಾಂಕ EGLint *attrib_list);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLDisplay EGLAPIENTRY eglGetPlatformDisplayEXT (EGLenum platform, ಶೂನ್ಯ *native_display, ಸ್ಥಿರಾಂಕ EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY egl_Create_Platform_ಕಿಟಕಿ_Surface_EXT (EGLDisplay dpy, EGLConfig config, ಶೂನ್ಯ *native_ಕಿಟಕಿ, ಸ್ಥಿರಾಂಕ EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePlatformPixmapSurfaceEXT (EGLDisplay dpy, EGLConfig config, ಶೂನ್ಯ *native_pixmap, ಸ್ಥಿರಾಂಕ EGLint *attrib_list);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_platform_base */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_platform_device
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_platform_device 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_PLATFORM_DEVICE_EXT           0x313F
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_platform_device */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_platform_wayland
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_platform_wayland 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_PLATFORM_WAYLAND_EXT          0x31D8
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_platform_wayland */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_platform_x11
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_platform_x11 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_PLATFORM_X11_EXT              0x31D5
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_PLATFORM_X11_SCREEN_EXT       0x31D6
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_platform_x11 */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_platform_xcb
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_platform_xcb 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_PLATFORM_XCB_EXT              0x31DC
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_PLATFORM_XCB_SCREEN_EXT       0x31DE
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_platform_xcb */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_present_opaque
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_present_opaque 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_PRESENT_OPAQUE_EXT            0x31DF
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_present_opaque */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_protected_content
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_protected_content 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_PROTECTED_CONTENT_EXT         0x32C0
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_protected_content */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_protected_surface
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_protected_surface 1
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_protected_surface */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_query_reset_notification_strategy
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_query_reset_notification_strategy 1
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_query_reset_notification_strategy */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_ಹರಿವು_ಗ್ರಾಹಕ_egloutput
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_ಹರಿವು_ಗ್ರಾಹಕ_egloutput 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMEROUTPUTEXTPROC) (EGLDisplay dpy, EGLStreamKHR ಹರಿವು, EGLOutputLayerEXT layer);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_ಹರಿವು_ಗ್ರಾಹಕ_Output_EXT (EGLDisplay dpy, EGLStreamKHR ಹರಿವು, EGLOutputLayerEXT layer);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_stream_consumer_egloutput */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_surface_CTA861_3_metadata
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_surface_CTA861_3_metadata 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_CTA861_3_MAX_CONTENT_LIGHT_LEVEL_EXT 0x3360
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_CTA861_3_MAX_ಚೌಕಟ್ಟು_ಸರಾಸರಿ_ಮೌಲ್ಯ_LEVEL_EXT 0x3361
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_surface_CTA861_3_metadata */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_surface_SMPTE2086_metadata
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_surface_SMPTE2086_metadata 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SMPTE2086_DISPLAY_PRIMARY_RX_EXT 0x3341
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SMPTE2086_DISPLAY_PRIMARY_RY_EXT 0x3342
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SMPTE2086_DISPLAY_PRIMARY_GX_EXT 0x3343
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SMPTE2086_DISPLAY_PRIMARY_GY_EXT 0x3344
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SMPTE2086_DISPLAY_PRIMARY_BX_EXT 0x3345
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SMPTE2086_DISPLAY_PRIMARY_BY_EXT 0x3346
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SMPTE2086_WHITE_ಬಿಂದು_X_EXT   0x3347
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SMPTE2086_WHITE_ಬಿಂದು_Y_EXT   0x3348
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SMPTE2086_MAX_LUMINANCE_EXT   0x3349
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SMPTE2086_MIN_LUMINANCE_EXT   0x334A
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_METADATA_SCALING_EXT          50000
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_surface_SMPTE2086_metadata */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_surface_compression
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_surface_compression 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SURFACE_COMPRESSION_EXT       0x34B0
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SURFACE_COMPRESSION_PLANE1_EXT 0x328E
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SURFACE_COMPRESSION_PLANE2_EXT 0x328F
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SURFACE_COMPRESSION_FIXED_ದರ_NONE_EXT 0x34B1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SURFACE_COMPRESSION_FIXED_ದರ_DEFAULT_EXT 0x34B2
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SURFACE_COMPRESSION_FIXED_ದರ_1_BPC_EXT 0x34B4
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SURFACE_COMPRESSION_FIXED_ದರ_2_BPC_EXT 0x34B5
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SURFACE_COMPRESSION_FIXED_ದರ_3_BPC_EXT 0x34B6
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SURFACE_COMPRESSION_FIXED_ದರ_4_BPC_EXT 0x34B7
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SURFACE_COMPRESSION_FIXED_ದರ_5_BPC_EXT 0x34B8
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SURFACE_COMPRESSION_FIXED_ದರ_6_BPC_EXT 0x34B9
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SURFACE_COMPRESSION_FIXED_ದರ_7_BPC_EXT 0x34BA
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SURFACE_COMPRESSION_FIXED_ದರ_8_BPC_EXT 0x34BB
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SURFACE_COMPRESSION_FIXED_ದರ_9_BPC_EXT 0x34BC
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SURFACE_COMPRESSION_FIXED_ದರ_10_BPC_EXT 0x34BD
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SURFACE_COMPRESSION_FIXED_ದರ_11_BPC_EXT 0x34BE
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SURFACE_COMPRESSION_FIXED_ದರ_12_BPC_EXT 0x34BF
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSUPPORTEDCOMPRESSIONRATESEXTPROC) (EGLDisplay dpy, EGLConfig config, ಸ್ಥಿರಾಂಕ EGLAttrib *attrib_list, EGLint *rates, EGLint ದರ_ಗಾತ್ರ, EGLint *ಅಂಕೆ_rates);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQuerySupportedCompressionRatesEXT (EGLDisplay dpy, EGLConfig config, ಸ್ಥಿರಾಂಕ EGLAttrib *attrib_list, EGLint *rates, EGLint ದರ_ಗಾತ್ರ, EGLint *ಅಂಕೆ_rates);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_surface_compression */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_ಅದಲುಬದಲು_buffers_with_damage
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_ಅದಲುಬದಲು_buffers_with_damage 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC) (EGLDisplay dpy, EGLSurface surface, ಸ್ಥಿರಾಂಕ EGLint *rects, EGLint n_rects);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_ಅದಲುಬದಲು_Buffers_With_Damage_EXT (EGLDisplay dpy, EGLSurface surface, ಸ್ಥಿರಾಂಕ EGLint *rects, EGLint n_rects);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_swap_buffers_with_damage */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_sync_reuse
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_sync_reuse 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLUNSIGNALSYNCEXTPROC) (EGLDisplay dpy, EGLSync sync, ಸ್ಥಿರಾಂಕ EGLAttrib *attrib_list);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglUnsignalSyncEXT (EGLDisplay dpy, EGLSync sync, ಸ್ಥಿರಾಂಕ EGLAttrib *attrib_list);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_sync_reuse */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_EXT_yuv_surface
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_EXT_yuv_surface 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_YUV_ಕ್ರಮ_EXT                 0x3301
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_YUV_ಸಂಖ್ಯೆ_ದ_PLANES_EXT      0x3311
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_YUV_SUBSAMPLE_EXT             0x3312
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_YUV_ಆಳ_RANGE_EXT           0x3317
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_YUV_CSC_STANDARD_EXT          0x330A
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_YUV_PLANE_BPP_EXT             0x331A
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_YUV_ಬಫರ್_EXT                0x3300
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_YUV_ಕ್ರಮ_YUV_EXT             0x3302
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_YUV_ಕ್ರಮ_YVU_EXT             0x3303
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_YUV_ಕ್ರಮ_YUYV_EXT            0x3304
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_YUV_ಕ್ರಮ_UYVY_EXT            0x3305
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_YUV_ಕ್ರಮ_YVYU_EXT            0x3306
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_YUV_ಕ್ರಮ_VYUY_EXT            0x3307
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_YUV_ಕ್ರಮ_AYUV_EXT            0x3308
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_YUV_SUBSAMPLE_4_2_0_EXT       0x3313
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_YUV_SUBSAMPLE_4_2_2_EXT       0x3314
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_YUV_SUBSAMPLE_4_4_4_EXT       0x3315
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_YUV_ಆಳ_RANGE_LIMITED_EXT   0x3318
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_YUV_ಆಳ_RANGE_ತುಂಬಿದ_EXT      0x3319
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_YUV_CSC_STANDARD_601_EXT      0x330B
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_YUV_CSC_STANDARD_709_EXT      0x330C
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_YUV_CSC_STANDARD_2020_EXT     0x330D
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_YUV_PLANE_BPP_0_EXT           0x331B
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_YUV_PLANE_BPP_8_EXT           0x331C
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_YUV_PLANE_BPP_10_EXT          0x331D
#ಆದರೆ_ಅಂತ್ಯ /* EGL_EXT_yuv_surface */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_HI_clientpixmap
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_HI_clientpixmap 1
ರಚನೆ EGLClientPixmapHI {
    ಶೂನ್ಯ  *p_ದತ್ತಾಂಶ;
    EGLint i_ಅಗಲ;
    EGLint i_ಎತ್ತರ;
    EGLint iStride;
};
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_CLIENT_PIXMAP_ಸೂಚಕ_HI      0x8F74
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLSurface (EGLAPIENTRYP PFNEGLCREATEPIXMAPSURFACEHIPROC) (EGLDisplay dpy, EGLConfig config, ರಚನೆ EGLClientPixmapHI *pixmap);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSurface EGLAPIENTRY eglCreatePixmapSurfaceHI (EGLDisplay dpy, EGLConfig config, ರಚನೆ EGLClientPixmapHI *pixmap);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_HI_clientpixmap */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_HI_colorformats
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_HI_colorformats 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_COLOR_FORMAT_HI               0x8F70
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_COLOR_RGB_HI                  0x8F71
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_COLOR_RGBA_HI                 0x8F72
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_COLOR_ARGB_HI                 0x8F73
#ಆದರೆ_ಅಂತ್ಯ /* EGL_HI_colorformats */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_IMG_context_ಆದ್ಯತೆ
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_IMG_context_ಆದ್ಯತೆ 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_CONTEXT_ಆದ್ಯತೆ_LEVEL_IMG    0x3100
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_CONTEXT_ಆದ್ಯತೆ_ಮೇಲಿನ_IMG     0x3101
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_CONTEXT_ಆದ್ಯತೆ_MEDIUM_IMG   0x3102
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_CONTEXT_ಆದ್ಯತೆ_ಕೆಳಗಿನ_IMG      0x3103
#ಆದರೆ_ಅಂತ್ಯ /* EGL_IMG_context_priority */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_IMG_image_plane_attribs
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_IMG_image_plane_attribs 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NATIVE_ಬಫರ್_MULTIPLANE_SEPARATE_IMG 0x3105
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NATIVE_ಬಫರ್_PLANE_ಸ್ಥಾನಾಂತರ_IMG 0x3106
#ಆದರೆ_ಅಂತ್ಯ /* EGL_IMG_image_plane_attribs */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_MESA_drm_image
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_MESA_drm_image 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DRM_ಬಫರ್_FORMAT_MESA        0x31D0
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DRM_ಬಫರ್_USE_MESA           0x31D1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DRM_ಬಫರ್_FORMAT_ARGB32_MESA 0x31D2
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DRM_ಬಫರ್_MESA               0x31D3
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DRM_ಬಫರ್_STRIDE_MESA        0x31D4
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DRM_ಬಫರ್_USE_SCANOUT_MESA   0x00000001
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DRM_ಬಫರ್_USE_SHARE_MESA     0x00000002
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_DRM_ಬಫರ್_USE_CURSOR_MESA    0x00000004
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLImageKHR (EGLAPIENTRYP PFNEGLCREATEDRMIMAGEMESAPROC) (EGLDisplay dpy, ಸ್ಥಿರಾಂಕ EGLint *attrib_list);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLEXPORTDRMIMAGEMESAPROC) (EGLDisplay dpy, EGLImageKHR image, EGLint *name, EGLint *handle, EGLint *stride);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLImageKHR EGLAPIENTRY eglCreateDRMImageMESA (EGLDisplay dpy, ಸ್ಥಿರಾಂಕ EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglExportDRMImageMESA (EGLDisplay dpy, EGLImageKHR image, EGLint *name, EGLint *handle, EGLint *stride);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_MESA_drm_image */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_MESA_image_dma_buf_export
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_MESA_image_dma_buf_export 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLEXPORTDMABUFIMAGEQUERYMESAPROC) (EGLDisplay dpy, EGLImageKHR image, ಪೂರ್ಣಾಂಕ *fourcc, ಪೂರ್ಣಾಂಕ *ಅಂಕೆ_planes, EGLuint64KHR *modifiers);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLEXPORTDMABUFIMAGEMESAPROC) (EGLDisplay dpy, EGLImageKHR image, ಪೂರ್ಣಾಂಕ *fds, EGLint *strides, EGLint *offsets);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglExportDMABUFImageQueryMESA (EGLDisplay dpy, EGLImageKHR image, ಪೂರ್ಣಾಂಕ *fourcc, ಪೂರ್ಣಾಂಕ *ಅಂಕೆ_planes, EGLuint64KHR *modifiers);
EGLAPI EGLBoolean EGLAPIENTRY eglExportDMABUFImageMESA (EGLDisplay dpy, EGLImageKHR image, ಪೂರ್ಣಾಂಕ *fds, EGLint *strides, EGLint *offsets);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_MESA_image_dma_buf_export */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_MESA_platform_gbm
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_MESA_platform_gbm 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_PLATFORM_GBM_MESA             0x31D7
#ಆದರೆ_ಅಂತ್ಯ /* EGL_MESA_platform_gbm */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_MESA_platform_surfaceless
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_MESA_platform_surfaceless 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_PLATFORM_SURFACELESS_MESA     0x31DD
#ಆದರೆ_ಅಂತ್ಯ /* EGL_MESA_platform_surfaceless */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_MESA_query_driver
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_MESA_query_driver 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಅಕ್ಷರ *(EGLAPIENTRYP PFNEGLGETDISPLAYDRIVERCONFIGPROC) (EGLDisplay dpy);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *(EGLAPIENTRYP PFNEGLGETDISPLAYDRIVERNAMEPROC) (EGLDisplay dpy);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI ಅಕ್ಷರ *EGLAPIENTRY eglGetDisplayDriverConfig (EGLDisplay dpy);
EGLAPI ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *EGLAPIENTRY eglGetDisplayDriverName (EGLDisplay dpy);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_MESA_query_driver */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NOK_ಅದಲುಬದಲು_region
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NOK_ಅದಲುಬದಲು_region 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSREGIONNOKPROC) (EGLDisplay dpy, EGLSurface surface, EGLint ಅಂಕೆ_Rects_2, ಸ್ಥಿರಾಂಕ EGLint *rects);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_ಅದಲುಬದಲು_Buffers_Region_NOK (EGLDisplay dpy, EGLSurface surface, EGLint ಅಂಕೆ_Rects_2, ಸ್ಥಿರಾಂಕ EGLint *rects);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NOK_swap_region */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NOK_ಅದಲುಬದಲು_region2
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NOK_ಅದಲುಬದಲು_region2 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSREGION2NOKPROC) (EGLDisplay dpy, EGLSurface surface, EGLint ಅಂಕೆ_Rects_2, ಸ್ಥಿರಾಂಕ EGLint *rects);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_ಅದಲುಬದಲು_Buffers_Region2_NOK (EGLDisplay dpy, EGLSurface surface, EGLint ಅಂಕೆ_Rects_2, ಸ್ಥಿರಾಂಕ EGLint *rects);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NOK_swap_region2 */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NOK_texture_from_pixmap
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NOK_texture_from_pixmap 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_Y_INVERTED_NOK                0x307F
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NOK_texture_from_pixmap */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_3dvision_surface
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_3dvision_surface 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_AUTO_STEREO_NV                0x3136
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_3dvision_surface */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_context_ಆದ್ಯತೆ_realtime
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_context_ಆದ್ಯತೆ_realtime 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_CONTEXT_ಆದ್ಯತೆ_REALTIME_NV  0x3357
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_context_priority_realtime */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_coverage_sample
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_coverage_sample 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_COVERAGE_BUFFERS_NV           0x30E0
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_COVERAGE_SAMPLES_NV           0x30E1
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_coverage_sample */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_coverage_sample_resolve
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_coverage_sample_resolve 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_COVERAGE_SAMPLE_RESOLVE_NV    0x3131
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_COVERAGE_SAMPLE_RESOLVE_DEFAULT_NV 0x3132
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_COVERAGE_SAMPLE_RESOLVE_NONE_NV 0x3133
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_coverage_sample_resolve */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_cuda_event
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_cuda_event 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_CUDA_EVENT_HANDLE_NV          0x323B
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SYNC_CUDA_EVENT_NV            0x323C
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SYNC_CUDA_EVENT_COMPLETE_NV   0x323D
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_cuda_event */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_ಆಳ_nonlinear
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_ಆಳ_nonlinear 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಆಳ_ENCODING_NV             0x30E2
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಆಳ_ENCODING_NONE_NV        0
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಆಳ_ENCODING_NONLINEAR_NV   0x30E3
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_depth_nonlinear */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_device_cuda
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_device_cuda 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_CUDA_DEVICE_NV                0x323A
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_device_cuda */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_native_query
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_native_query 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYNATIVEDISPLAYNVPROC) (EGLDisplay dpy, EGLNativeDisplayType *display_id);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYNATIVEWINDOWNVPROC) (EGLDisplay dpy, EGLSurface surf, EGLNative_ಕಿಟಕಿ_Type *ಕಿಟಕಿ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYNATIVEPIXMAPNVPROC) (EGLDisplay dpy, EGLSurface surf, EGLNativePixmapType *pixmap);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryNativeDisplayNV (EGLDisplay dpy, EGLNativeDisplayType *display_id);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Native_ಕಿಟಕಿ_NV (EGLDisplay dpy, EGLSurface surf, EGLNative_ಕಿಟಕಿ_Type *ಕಿಟಕಿ);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryNativePixmapNV (EGLDisplay dpy, EGLSurface surf, EGLNativePixmapType *pixmap);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_native_query */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_post_convert_rounding
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_post_convert_rounding 1
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_post_convert_rounding */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_post_sub_ಬಫರ್
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_post_sub_ಬಫರ್ 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_POST_SUB_ಬಫರ್_SUPPORTED_NV  0x30BE
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLPOSTSUBBUFFERNVPROC) (EGLDisplay dpy, EGLSurface surface, EGLint x, EGLint y, EGLint ಅಗಲ, EGLint ಎತ್ತರ);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Post_Sub_ಬಫರ್_NV (EGLDisplay dpy, EGLSurface surface, EGLint x, EGLint y, EGLint ಅಗಲ, EGLint ಎತ್ತರ);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_post_sub_buffer */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_quadruple_ಬಫರ್
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_quadruple_ಬಫರ್ 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_QUADRUPLE_ಬಫರ್_NV           0x3231
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_quadruple_buffer */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_robustness_video_ಸ್ಮರಣೆ_purge
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_robustness_video_ಸ್ಮರಣೆ_purge 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_GENERATE_RESET_ON_VIDEO_ಸ್ಮರಣೆ_PURGE_NV 0x334C
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_robustness_video_memory_purge */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_ಹರಿವು_ಗ್ರಾಹಕ_eglimage
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_ಹರಿವು_ಗ್ರಾಹಕ_eglimage 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_ಗ್ರಾಹಕ_IMAGE_NV      0x3373
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_IMAGE_ಕೂಡಿಸು_NV           0x3374
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_IMAGE_REMOVE_NV        0x3375
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_IMAGE_ಲಭ್ಯ_NV     0x3376
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMIMAGECONSUMERCONNECTNVPROC) (EGLDisplay dpy, EGLStreamKHR ಹರಿವು, EGLint ಅಂಕೆ_modifiers, ಸ್ಥಿರಾಂಕ EGLuint64KHR *modifiers, ಸ್ಥಿರಾಂಕ EGLAttrib *attrib_list);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLint (EGLAPIENTRYP PFNEGLQUERYSTREAMCONSUMEREVENTNVPROC) (EGLDisplay dpy, EGLStreamKHR ಹರಿವು, EGLTime timeout, EGLenum *event, EGLAttrib *aux);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMACQUIREIMAGENVPROC) (EGLDisplay dpy, EGLStreamKHR ಹರಿವು, EGLImage *pImage, EGLSync sync);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMRELEASEIMAGENVPROC) (EGLDisplay dpy, EGLStreamKHR ಹರಿವು, EGLImage image, EGLSync sync);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_ಹರಿವು_Image_ಗ್ರಾಹಕ_Connect_NV (EGLDisplay dpy, EGLStreamKHR ಹರಿವು, EGLint ಅಂಕೆ_modifiers, ಸ್ಥಿರಾಂಕ EGLuint64KHR *modifiers, ಸ್ಥಿರಾಂಕ EGLAttrib *attrib_list);
EGLAPI EGLint EGLAPIENTRY egl_Query_ಹರಿವು_ಗ್ರಾಹಕ_Event_NV (EGLDisplay dpy, EGLStreamKHR ಹರಿವು, EGLTime timeout, EGLenum *event, EGLAttrib *aux);
EGLAPI EGLBoolean EGLAPIENTRY egl_ಹರಿವು_Acquire_Image_NV (EGLDisplay dpy, EGLStreamKHR ಹರಿವು, EGLImage *pImage, EGLSync sync);
EGLAPI EGLBoolean EGLAPIENTRY egl_ಹರಿವು_Release_Image_NV (EGLDisplay dpy, EGLStreamKHR ಹರಿವು, EGLImage image, EGLSync sync);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_stream_consumer_eglimage */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_ಹರಿವು_ಗ್ರಾಹಕ_eglimage_use_scanout_attrib
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_ಹರಿವು_ಗ್ರಾಹಕ_eglimage_use_scanout_attrib 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_ಗ್ರಾಹಕ_IMAGE_USE_SCANOUT_NV 0x3378
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_stream_consumer_eglimage_use_scanout_attrib */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_ಹರಿವು_ಗ್ರಾಹಕ_gltexture_yuv
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_ಹರಿವು_ಗ್ರಾಹಕ_gltexture_yuv 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_YUV_PLANE0_TEXTURE_UNIT_NV    0x332C
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_YUV_PLANE1_TEXTURE_UNIT_NV    0x332D
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_YUV_PLANE2_TEXTURE_UNIT_NV    0x332E
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALATTRIBSNVPROC) (EGLDisplay dpy, EGLStreamKHR ಹರಿವು, ಸ್ಥಿರಾಂಕ EGLAttrib *attrib_list);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_ಹರಿವು_ಗ್ರಾಹಕ_GLTexture_External_Attribs_NV (EGLDisplay dpy, EGLStreamKHR ಹರಿವು, ಸ್ಥಿರಾಂಕ EGLAttrib *attrib_list);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_stream_consumer_gltexture_yuv */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_ಹರಿವು_cross_display
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_ಹರಿವು_cross_display 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_CROSS_DISPLAY_NV       0x334E
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_stream_cross_display */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_ಹರಿವು_cross_object
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_ಹರಿವು_cross_object 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_CROSS_OBJECT_NV        0x334D
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_stream_cross_object */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_ಹರಿವು_cross_ವಿಭಜನೆ
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_ಹರಿವು_cross_ವಿಭಜನೆ 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_CROSS_ವಿಭಜನೆ_NV     0x323F
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_stream_cross_partition */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_ಹರಿವು_cross_process
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_ಹರಿವು_cross_process 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_CROSS_PROCESS_NV       0x3245
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_stream_cross_process */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_ಹರಿವು_cross_system
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_ಹರಿವು_cross_system 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_CROSS_SYSTEM_NV        0x334F
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_stream_cross_system */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_ಹರಿವು_dma
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_ಹರಿವು_dma 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_DMA_NV                 0x3371
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_DMA_SERVER_NV          0x3372
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_stream_dma */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_ಹರಿವು_fifo_ಮುಂದಿನ
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_ಹರಿವು_fifo_ಮುಂದಿನ 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_PENDING_ಚೌಕಟ್ಟು_NV              0x3329
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_ಸಮಯ_PENDING_NV        0x332A
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_stream_fifo_next */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_ಹರಿವು_fifo_synchronous
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_ಹರಿವು_fifo_synchronous 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_FIFO_SYNCHRONOUS_NV    0x3336
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_stream_fifo_synchronous */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_ಹರಿವು_flush
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_ಹರಿವು_flush 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLSTREAMFLUSHNVPROC) (EGLDisplay dpy, EGLStreamKHR ಹರಿವು);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_ಹರಿವು_Flush_NV (EGLDisplay dpy, EGLStreamKHR ಹರಿವು);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_stream_flush */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_ಹರಿವು_ಚೌಕಟ್ಟು_limits
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_ಹರಿವು_ಚೌಕಟ್ಟು_limits 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಉತ್ಪಾದಕ_MAX_ಚೌಕಟ್ಟು_HINT_NV    0x3337
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಗ್ರಾಹಕ_MAX_ಚೌಕಟ್ಟು_HINT_NV    0x3338
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_stream_frame_limits */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_ಹರಿವು_metadata
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_ಹರಿವು_metadata 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_MAX_ಹರಿವು_METADATA_ಖಂಡಗಳು_NV 0x3250
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_MAX_ಹರಿವು_METADATA_ಖಂಡ_ಗಾತ್ರ_NV 0x3251
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_MAX_ಹರಿವು_METADATA_ಒಟ್ಟು_ಗಾತ್ರ_NV 0x3252
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಉತ್ಪಾದಕ_METADATA_NV          0x3253
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಗ್ರಾಹಕ_METADATA_NV          0x3254
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_PENDING_METADATA_NV           0x3328
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_METADATA0_ಗಾತ್ರ_NV             0x3255
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_METADATA1_ಗಾತ್ರ_NV             0x3256
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_METADATA2_ಗಾತ್ರ_NV             0x3257
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_METADATA3_ಗಾತ್ರ_NV             0x3258
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_METADATA0_TYPE_NV             0x3259
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_METADATA1_TYPE_NV             0x325A
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_METADATA2_TYPE_NV             0x325B
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_METADATA3_TYPE_NV             0x325C
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDISPLAYATTRIBNVPROC) (EGLDisplay dpy, EGLint attribute, EGLAttrib *ಮೌಲ್ಯ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLSETSTREAMMETADATANVPROC) (EGLDisplay dpy, EGLStreamKHR ಹರಿವು, EGLint n, EGLint ಸ್ಥಾನಾಂತರ_2, EGLint ಗಾತ್ರ_2, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ದತ್ತಾಂಶ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSTREAMMETADATANVPROC) (EGLDisplay dpy, EGLStreamKHR ಹರಿವು, EGLenum name, EGLint n, EGLint ಸ್ಥಾನಾಂತರ_2, EGLint ಗಾತ್ರ_2, ಶೂನ್ಯ *ದತ್ತಾಂಶ);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDisplayAttribNV (EGLDisplay dpy, EGLint attribute, EGLAttrib *ಮೌಲ್ಯ);
EGLAPI EGLBoolean EGLAPIENTRY egl_ಗಣ_ಹರಿವು_Metadata_NV (EGLDisplay dpy, EGLStreamKHR ಹರಿವು, EGLint n, EGLint ಸ್ಥಾನಾಂತರ_2, EGLint ಗಾತ್ರ_2, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ದತ್ತಾಂಶ);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_ಹರಿವು_Metadata_NV (EGLDisplay dpy, EGLStreamKHR ಹರಿವು, EGLenum name, EGLint n, EGLint ಸ್ಥಾನಾಂತರ_2, EGLint ಗಾತ್ರ_2, ಶೂನ್ಯ *ದತ್ತಾಂಶ);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_stream_metadata */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_ಹರಿವು_origin
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_ಹರಿವು_origin 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_ಚೌಕಟ್ಟು_ORIGIN_X_NV      0x3366
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_ಚೌಕಟ್ಟು_ORIGIN_Y_NV      0x3367
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_ಚೌಕಟ್ಟು_MAJOR_AXIS_NV    0x3368
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಗ್ರಾಹಕ_AUTO_ORIENTATION_NV  0x3369
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಉತ್ಪಾದಕ_AUTO_ORIENTATION_NV  0x336A
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಎಡ_NV                       0x336B
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಬಲ_NV                      0x336C
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ತುದಿ_NV                        0x336D
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_BOTTOM_NV                     0x336E
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_X_AXIS_NV                     0x336F
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_Y_AXIS_NV                     0x3370
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_stream_origin */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_ಹರಿವು_remote
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_ಹರಿವು_remote 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_STATE_INITIALIZING_NV  0x3240
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_TYPE_NV                0x3241
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_PROTOCOL_NV            0x3242
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_ENDPOINT_NV            0x3243
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_LOCAL_NV               0x3244
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_ಉತ್ಪಾದಕ_NV            0x3247
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_ಗ್ರಾಹಕ_NV            0x3248
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_PROTOCOL_FD_NV         0x3246
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_stream_remote */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_ಹರಿವು_reset
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_ಹರಿವು_reset 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SUPPORT_RESET_NV              0x3334
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SUPPORT_REUSE_NV              0x3335
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLRESETSTREAMNVPROC) (EGLDisplay dpy, EGLStreamKHR ಹರಿವು);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY egl_Reset_ಹರಿವು_NV (EGLDisplay dpy, EGLStreamKHR ಹರಿವು);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_stream_reset */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_ಹರಿವು_socket
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_ಹರಿವು_socket 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ಹರಿವು_PROTOCOL_SOCKET_NV     0x324B
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SOCKET_HANDLE_NV              0x324C
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SOCKET_TYPE_NV                0x324D
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_stream_socket */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_ಹರಿವು_socket_inet
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_ಹರಿವು_socket_inet 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SOCKET_TYPE_INET_NV           0x324F
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_stream_socket_inet */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_ಹರಿವು_socket_unix
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_ಹರಿವು_socket_unix 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SOCKET_TYPE_UNIX_NV           0x324E
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_stream_socket_unix */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_ಹರಿವು_sync
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_ಹರಿವು_sync 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SYNC_NEW_ಚೌಕಟ್ಟು_NV             0x321F
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLSyncKHR (EGLAPIENTRYP PFNEGLCREATESTREAMSYNCNVPROC) (EGLDisplay dpy, EGLStreamKHR ಹರಿವು, EGLenum type, ಸ್ಥಿರಾಂಕ EGLint *attrib_list);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncKHR EGLAPIENTRY egl_Create_ಹರಿವು_Sync_NV (EGLDisplay dpy, EGLStreamKHR ಹರಿವು, EGLenum type, ಸ್ಥಿರಾಂಕ EGLint *attrib_list);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_stream_sync */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_sync
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_sync 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ *EGLSyncNV;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ khronos_utime_nanoseconds_t EGLTimeNV;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ KHRONOS_SUPPORT_INT64
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SYNC_ಪೂರ್ವ_COMMANDS_COMPLETE_NV 0x30E6
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SYNC_ಸ್ಥಿತಿ_NV                0x30E7
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SIGNALED_NV                   0x30E8
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_UNSIGNALED_NV                 0x30E9
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SYNC_FLUSH_COMMANDS_ಬಿಟ್_NV    0x0001
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_FOREVER_NV                    0xFFFFFFFFFFFFFFFFull
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_ALREADY_SIGNALED_NV           0x30EA
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_TIMEOUT_EXPIRED_NV            0x30EB
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_CONDITION_SATISFIED_NV        0x30EC
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SYNC_TYPE_NV                  0x30ED
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SYNC_CONDITION_NV             0x30EE
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_SYNC_FENCE_NV                 0x30EF
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NO_SYNC_NV                    EGL_CAST(EGLSyncNV,0)
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLSyncNV (EGLAPIENTRYP PFNEGLCREATEFENCESYNCNVPROC) (EGLDisplay dpy, EGLenum condition, ಸ್ಥಿರಾಂಕ EGLint *attrib_list);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCNVPROC) (EGLSyncNV sync);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLFENCENVPROC) (EGLSyncNV sync);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLint (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCNVPROC) (EGLSyncNV sync, EGLint flags, EGLTimeNV timeout);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLSIGNALSYNCNVPROC) (EGLSyncNV sync, EGLenum ಬಹುಲಕ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLGETSYNCATTRIBNVPROC) (EGLSyncNV sync, EGLint attribute, EGLint *ಮೌಲ್ಯ);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLSyncNV EGLAPIENTRY eglCreateFenceSyncNV (EGLDisplay dpy, EGLenum condition, ಸ್ಥಿರಾಂಕ EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySyncNV (EGLSyncNV sync);
EGLAPI EGLBoolean EGLAPIENTRY eglFenceNV (EGLSyncNV sync);
EGLAPI EGLint EGLAPIENTRY eglClientWaitSyncNV (EGLSyncNV sync, EGLint flags, EGLTimeNV timeout);
EGLAPI EGLBoolean EGLAPIENTRY eglSignalSyncNV (EGLSyncNV sync, EGLenum ಬಹುಲಕ);
EGLAPI EGLBoolean EGLAPIENTRY eglGetSyncAttribNV (EGLSyncNV sync, EGLint attribute, EGLint *ಮೌಲ್ಯ);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* KHRONOS_SUPPORT_INT64 */
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_sync */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_system_ಸಮಯ
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_system_ಸಮಯ 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ khronos_utime_nanoseconds_t EGLuint64NV;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ KHRONOS_SUPPORT_INT64
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLuint64NV (EGLAPIENTRYP PFNEGLGETSYSTEMTIMEFREQUENCYNVPROC) (ಶೂನ್ಯ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLuint64NV (EGLAPIENTRYP PFNEGLGETSYSTEMTIMENVPROC) (ಶೂನ್ಯ);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLuint64NV EGLAPIENTRY egl_Get_System_ಸಮಯ_Frequency_NV (ಶೂನ್ಯ);
EGLAPI EGLuint64NV EGLAPIENTRY egl_Get_System_ಸಮಯ_NV (ಶೂನ್ಯ);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* KHRONOS_SUPPORT_INT64 */
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_system_time */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_NV_triple_ಬಫರ್
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NV_triple_ಬಫರ್ 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_TRIPLE_ಬಫರ್_NV              0x3230
#ಆದರೆ_ಅಂತ್ಯ /* EGL_NV_triple_buffer */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_QNX_image_native_ಬಫರ್
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_QNX_image_native_ಬಫರ್ 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NATIVE_ಬಫರ್_QNX             0x3551
#ಆದರೆ_ಅಂತ್ಯ /* EGL_QNX_image_native_buffer */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_QNX_platform_screen
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_QNX_platform_screen 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_PLATFORM_SCREEN_QNX           0x3550
#ಆದರೆ_ಅಂತ್ಯ /* EGL_QNX_platform_screen */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_TIZEN_image_native_ಬಫರ್
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_TIZEN_image_native_ಬಫರ್ 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NATIVE_ಬಫರ್_TIZEN           0x32A0
#ಆದರೆ_ಅಂತ್ಯ /* EGL_TIZEN_image_native_buffer */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_TIZEN_image_native_surface
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_TIZEN_image_native_surface 1
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_NATIVE_SURFACE_TIZEN          0x32A1
#ಆದರೆ_ಅಂತ್ಯ /* EGL_TIZEN_image_native_surface */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_WL_bind_wayland_display
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_WL_bind_wayland_display 1
#ವ್ಯಾಖ್ಯಾನಿಸು PFNEGLBINDWAYLANDDISPLAYWL PFNEGLBINDWAYLANDDISPLAYWLPROC
#ವ್ಯಾಖ್ಯಾನಿಸು PFNEGLUNBINDWAYLANDDISPLAYWL PFNEGLUNBINDWAYLANDDISPLAYWLPROC
#ವ್ಯಾಖ್ಯಾನಿಸು PFNEGLQUERYWAYLANDBUFFERWL PFNEGLQUERYWAYLANDBUFFERWLPROC
ರಚನೆ wl_display;
ರಚನೆ wl_resource;
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_WAYLAND_ಬಫರ್_WL             0x31D5
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_WAYLAND_PLANE_WL              0x31D6
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_TEXTURE_Y_U_V_WL              0x31D7
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_TEXTURE_Y_UV_WL               0x31D8
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_TEXTURE_Y_XUXV_WL             0x31D9
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_TEXTURE_EXTERNAL_WL           0x31DA
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_WAYLAND_Y_INVERTED_WL         0x31DB
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLBINDWAYLANDDISPLAYWLPROC) (EGLDisplay dpy, ರಚನೆ wl_display *display);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLUNBINDWAYLANDDISPLAYWLPROC) (EGLDisplay dpy, ರಚನೆ wl_display *display);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ EGLBoolean (EGLAPIENTRYP PFNEGLQUERYWAYLANDBUFFERWLPROC) (EGLDisplay dpy, ರಚನೆ wl_resource *ಬಫರ್_2, EGLint attribute, EGLint *ಮೌಲ್ಯ);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglBindWaylandDisplayWL (EGLDisplay dpy, ರಚನೆ wl_display *display);
EGLAPI EGLBoolean EGLAPIENTRY eglUnbindWaylandDisplayWL (EGLDisplay dpy, ರಚನೆ wl_display *display);
EGLAPI EGLBoolean EGLAPIENTRY egl_Query_Wayland_ಬಫರ್_WL (EGLDisplay dpy, ರಚನೆ wl_resource *ಬಫರ್_2, EGLint attribute, EGLint *ಮೌಲ್ಯ);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_WL_bind_wayland_display */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ EGL_WL_create_wayland_ಬಫರ್_from_image
#ವ್ಯಾಖ್ಯಾನಿಸು EGL_WL_create_wayland_ಬಫರ್_from_image 1
#ವ್ಯಾಖ್ಯಾನಿಸು PFNEGLCREATEWAYLANDBUFFERFROMIMAGEWL PFNEGLCREATEWAYLANDBUFFERFROMIMAGEWLPROC
ರಚನೆ wl_ಬಫರ್;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ wl_ಬಫರ್ *(EGLAPIENTRYP PFNEGLCREATEWAYLANDBUFFERFROMIMAGEWLPROC) (EGLDisplay dpy, EGLImageKHR image);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ EGL_EGLEXT_PROTOTYPES
EGLAPI ರಚನೆ wl_ಬಫರ್ *EGLAPIENTRY egl_Create_Wayland_ಬಫರ್_From_Image_WL (EGLDisplay dpy, EGLImageKHR image);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* EGL_WL_create_wayland_buffer_from_image */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ
