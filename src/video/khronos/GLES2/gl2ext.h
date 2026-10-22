#جيڪڏهن_وصف_نه_ٿيل __gles2_gl2ext_h_
#وصف_ڪريو __gles2_gl2ext_h_ 1

#جيڪڏهن_وصف_ٿيل __cplusplus
خارجي "C" {
#جيڪڏهن_پورو

/*
** Copyright 2013-2026 The Khronos Group Inc.
** SPDX-License-Identifier: MIT
**
** This header is generated from the Khronos OpenGL / OpenGL ES XML
** API Registry. The current version of the Registry, generator scripts
** used to make the header, and the header can be found at
**   https://github.com/KhronosGroup/OpenGL-Registry
*/

#جيڪڏهن_وصف_نه_ٿيل GL_APIENTRYP
#وصف_ڪريو GL_APIENTRYP GL_APIENTRY*
#جيڪڏهن_پورو

#وصف_ڪريو GL_GLEXT_نسخو 20260803

/* Generated C header for:
 * API: gles2
 * Profile: common
 * Versions considered: 2\.[0-9]
 * Versions emitted: _nomatch_^
 * Default extensions included: gles2
 * Additional extensions included: _nomatch_^
 * Extensions removed: _nomatch_^
 */

#جيڪڏهن_وصف_نه_ٿيل GL_KHR_blend_equation_advanced
#وصف_ڪريو GL_KHR_blend_equation_advanced 1
#وصف_ڪريو GL_MULTIPLY_KHR                   0x9294
#وصف_ڪريو GL_SCREEN_KHR                     0x9295
#وصف_ڪريو GL_OVERLAY_KHR                    0x9296
#وصف_ڪريو GL_DARKEN_KHR                     0x9297
#وصف_ڪريو GL_LIGHTEN_KHR                    0x9298
#وصف_ڪريو GL_COLORDODGE_KHR                 0x9299
#وصف_ڪريو GL_COLORBURN_KHR                  0x929A
#وصف_ڪريو GL_HARDLIGHT_KHR                  0x929B
#وصف_ڪريو GL_SOFTLIGHT_KHR                  0x929C
#وصف_ڪريو GL_DIFFERENCE_KHR                 0x929E
#وصف_ڪريو GL_EXCLUSION_KHR                  0x92A0
#وصف_ڪريو GL_HSL_HUE_KHR                    0x92AD
#وصف_ڪريو GL_HSL_SATURATION_KHR             0x92AE
#وصف_ڪريو GL_HSL_COLOR_KHR                  0x92AF
#وصف_ڪريو GL_HSL_LUMINOSITY_KHR             0x92B0
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDBARRIERKHRPROC) (فراغ);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glBlendBarrierKHR (فراغ);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_KHR_blend_equation_advanced */

#جيڪڏهن_وصف_نه_ٿيل GL_KHR_blend_equation_advanced_coherent
#وصف_ڪريو GL_KHR_blend_equation_advanced_coherent 1
#وصف_ڪريو GL_BLEND_ADVANCED_COHERENT_KHR    0x9285
#جيڪڏهن_پورو /* GL_KHR_blend_equation_advanced_coherent */

#جيڪڏهن_وصف_نه_ٿيل GL_KHR_context_flush_control
#وصف_ڪريو GL_KHR_context_flush_control 1
#وصف_ڪريو GL_CONTEXT_RELEASE_BEHAVIOR_KHR   0x82FB
#وصف_ڪريو GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_KHR 0x82FC
#جيڪڏهن_پورو /* GL_KHR_context_flush_control */

#جيڪڏهن_وصف_نه_ٿيل GL_KHR_debug
#وصف_ڪريو GL_KHR_debug 1
تعريفنوع فراغ (GL_APIENTRY  *GLDEBUGPROCKHR)(GLenum ذريعو,GLenum type,GLuint id,GLenum severity,GLsizei ڊيگهائي,ثابت GLchar *پيغام,ثابت فراغ *userParam);
#وصف_ڪريو GL_SAMPLER                        0x82E6
#وصف_ڪريو GL_DEBUG_OUTPUT_SYNCHRONOUS_KHR   0x8242
#وصف_ڪريو GL_DEBUG_ايندڙ_LOGGED_پيغام_ڊيگهائي_KHR 0x8243
#وصف_ڪريو GL_DEBUG_CALLBACK_FUNCTION_KHR    0x8244
#وصف_ڪريو GL_DEBUG_CALLBACK_USER_PARAM_KHR  0x8245
#وصف_ڪريو GL_DEBUG_ذريعو_API_KHR           0x8246
#وصف_ڪريو GL_DEBUG_ذريعو_دري_SYSTEM_KHR 0x8247
#وصف_ڪريو GL_DEBUG_ذريعو_SHADER_COMPILER_KHR 0x8248
#وصف_ڪريو GL_DEBUG_ذريعو_ٽيون_PARTY_KHR   0x8249
#وصف_ڪريو GL_DEBUG_ذريعو_APPLICATION_KHR   0x824A
#وصف_ڪريو GL_DEBUG_ذريعو_OTHER_KHR         0x824B
#وصف_ڪريو GL_DEBUG_TYPE_ERROR_KHR           0x824C
#وصف_ڪريو GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_KHR 0x824D
#وصف_ڪريو GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_KHR 0x824E
#وصف_ڪريو GL_DEBUG_TYPE_PORTABILITY_KHR     0x824F
#وصف_ڪريو GL_DEBUG_TYPE_PERFORMANCE_KHR     0x8250
#وصف_ڪريو GL_DEBUG_TYPE_OTHER_KHR           0x8251
#وصف_ڪريو GL_DEBUG_TYPE_MARKER_KHR          0x8268
#وصف_ڪريو GL_DEBUG_TYPE_ڌڪو_گروهه_KHR      0x8269
#وصف_ڪريو GL_DEBUG_TYPE_ڪڍو_گروهه_KHR       0x826A
#وصف_ڪريو GL_DEBUG_SEVERITY_NOTIFICATION_KHR 0x826B
#وصف_ڪريو GL_MAX_DEBUG_گروهه_ڍير_اونهائي_KHR 0x826C
#وصف_ڪريو GL_DEBUG_گروهه_ڍير_اونهائي_KHR    0x826D
#وصف_ڪريو GL_بفر_KHR                     0x82E0
#وصف_ڪريو GL_SHADER_KHR                     0x82E1
#وصف_ڪريو GL_پروگرام_KHR                    0x82E2
#وصف_ڪريو GL_راس_ARRAY_KHR               0x8074
#وصف_ڪريو GL_QUERY_KHR                      0x82E3
#وصف_ڪريو GL_پروگرام_PIPELINE_KHR           0x82E4
#وصف_ڪريو GL_SAMPLER_KHR                    0x82E6
#وصف_ڪريو GL_MAX_LABEL_ڊيگهائي_KHR           0x82E8
#وصف_ڪريو GL_MAX_DEBUG_پيغام_ڊيگهائي_KHR   0x9143
#وصف_ڪريو GL_MAX_DEBUG_LOGGED_MESSAGES_KHR  0x9144
#وصف_ڪريو GL_DEBUG_LOGGED_MESSAGES_KHR      0x9145
#وصف_ڪريو GL_DEBUG_SEVERITY_مٿاهون_KHR        0x9146
#وصف_ڪريو GL_DEBUG_SEVERITY_MEDIUM_KHR      0x9147
#وصف_ڪريو GL_DEBUG_SEVERITY_هيٺيون_KHR         0x9148
#وصف_ڪريو GL_DEBUG_OUTPUT_KHR               0x92E0
#وصف_ڪريو GL_CONTEXT_FLAG_DEBUG_ٻٽو_انگ_KHR     0x00000002
#وصف_ڪريو GL_ڍير_حد_کان_مٿي_KHR             0x0503
#وصف_ڪريو GL_ڍير_UNDERFLOW_KHR            0x0504
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEBUGMESSAGECONTROLKHRPROC) (GLenum ذريعو, GLenum type, GLenum severity, GLsizei ڳڻپ, ثابت GLuint *ids, GLboolean enabled);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEBUGMESSAGEINSERTKHRPROC) (GLenum ذريعو, GLenum type, GLuint id, GLenum severity, GLsizei ڊيگهائي, ثابت GLchar *buf);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEBUGMESSAGECALLBACKKHRPROC) (GLDEBUGPROCKHR callback, ثابت فراغ *userParam);
تعريفنوع GLuint (GL_APIENTRYP PFNGLGETDEBUGMESSAGELOGKHRPROC) (GLuint ڳڻپ, GLsizei buf_سائيز, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *پيغام_Log);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPUSHDEBUGGROUPKHRPROC) (GLenum ذريعو, GLuint id, GLsizei ڊيگهائي, ثابت GLchar *پيغام);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOPDEBUGGROUPKHRPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLOBJECTLABELKHRPROC) (GLenum identifier, GLuint name, GLsizei ڊيگهائي, ثابت GLchar *label);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETOBJECTLABELKHRPROC) (GLenum identifier, GLuint name, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLchar *label);
تعريفنوع فراغ (GL_APIENTRYP PFNGLOBJECTPTRLABELKHRPROC) (ثابت فراغ *ptr, GLsizei ڊيگهائي, ثابت GLchar *label);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETOBJECTPTRLABELKHRPROC) (ثابت فراغ *ptr, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLchar *label);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPOINTERVKHRPROC) (GLenum pname, فراغ **params);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Debug_پيغام_Control_KHR (GLenum ذريعو, GLenum type, GLenum severity, GLsizei ڳڻپ, ثابت GLuint *ids, GLboolean enabled);
GL_APICALL فراغ GL_APIENTRY gl_Debug_پيغام_وجهو_KHR (GLenum ذريعو, GLenum type, GLuint id, GLenum severity, GLsizei ڊيگهائي, ثابت GLchar *buf);
GL_APICALL فراغ GL_APIENTRY gl_Debug_پيغام_Callback_KHR (GLDEBUGPROCKHR callback, ثابت فراغ *userParam);
GL_APICALL GLuint GL_APIENTRY gl_Get_Debug_پيغام_Log_KHR (GLuint ڳڻپ, GLsizei buf_سائيز, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *پيغام_Log);
GL_APICALL فراغ GL_APIENTRY gl_ڌڪو_Debug_گروهه_KHR (GLenum ذريعو, GLuint id, GLsizei ڊيگهائي, ثابت GLchar *پيغام);
GL_APICALL فراغ GL_APIENTRY gl_ڪڍو_Debug_گروهه_KHR (فراغ);
GL_APICALL فراغ GL_APIENTRY glObjectLabelKHR (GLenum identifier, GLuint name, GLsizei ڊيگهائي, ثابت GLchar *label);
GL_APICALL فراغ GL_APIENTRY glGetObjectLabelKHR (GLenum identifier, GLuint name, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLchar *label);
GL_APICALL فراغ GL_APIENTRY glObjectPtrLabelKHR (ثابت فراغ *ptr, GLsizei ڊيگهائي, ثابت GLchar *label);
GL_APICALL فراغ GL_APIENTRY glGetObjectPtrLabelKHR (ثابت فراغ *ptr, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLchar *label);
GL_APICALL فراغ GL_APIENTRY glGetPointervKHR (GLenum pname, فراغ **params);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_KHR_debug */

#جيڪڏهن_وصف_نه_ٿيل GL_KHR_no_error
#وصف_ڪريو GL_KHR_no_error 1
#وصف_ڪريو GL_CONTEXT_FLAG_NO_ERROR_ٻٽو_انگ_KHR  0x00000008
#جيڪڏهن_پورو /* GL_KHR_no_error */

#جيڪڏهن_وصف_نه_ٿيل GL_KHR_parallel_shader_compile
#وصف_ڪريو GL_KHR_parallel_shader_compile 1
#وصف_ڪريو GL_MAX_SHADER_COMPILER_ڌاڳا_KHR 0x91B0
#وصف_ڪريو GL_COMPLETION_حالت_KHR          0x91B1
تعريفنوع فراغ (GL_APIENTRYP PFNGLMAXSHADERCOMPILERTHREADSKHRPROC) (GLuint ڳڻپ);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Max_Shader_Compiler_ڌاڳا_KHR (GLuint ڳڻپ);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_KHR_parallel_shader_compile */

#جيڪڏهن_وصف_نه_ٿيل GL_KHR_robust_بفر_access_behavior
#وصف_ڪريو GL_KHR_robust_بفر_access_behavior 1
#جيڪڏهن_پورو /* GL_KHR_robust_buffer_access_behavior */

#جيڪڏهن_وصف_نه_ٿيل GL_KHR_robustness
#وصف_ڪريو GL_KHR_robustness 1
#وصف_ڪريو GL_CONTEXT_ROBUST_ACCESS_KHR      0x90F3
#وصف_ڪريو GL_LOSE_CONTEXT_ON_RESET_KHR      0x8252
#وصف_ڪريو GL_GUILTY_CONTEXT_RESET_KHR       0x8253
#وصف_ڪريو GL_INNOCENT_CONTEXT_RESET_KHR     0x8254
#وصف_ڪريو GL_UNKNOWN_CONTEXT_RESET_KHR      0x8255
#وصف_ڪريو GL_RESET_NOTIFICATION_STRATEGY_KHR 0x8256
#وصف_ڪريو GL_NO_RESET_NOTIFICATION_KHR      0x8261
#وصف_ڪريو GL_CONTEXT_گم_KHR               0x0507
تعريفنوع GLenum (GL_APIENTRYP PFNGLGETGRAPHICSRESETSTATUSKHRPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLREADNPIXELSKHRPROC) (GLint x, GLint y, GLsizei ويڪر, GLsizei اوچائي, GLenum format, GLenum type, GLsizei buf_سائيز, فراغ *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNUNIFORMFVKHRPROC) (GLuint پروگرام, GLint location, GLsizei buf_سائيز, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNUNIFORMIVKHRPROC) (GLuint پروگرام, GLint location, GLsizei buf_سائيز, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNUNIFORMUIVKHRPROC) (GLuint پروگرام, GLint location, GLsizei buf_سائيز, GLuint *params);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL GLenum GL_APIENTRY gl_Get_Graphics_Reset_حالت_KHR (فراغ);
GL_APICALL فراغ GL_APIENTRY glReadnPixelsKHR (GLint x, GLint y, GLsizei ويڪر, GLsizei اوچائي, GLenum format, GLenum type, GLsizei buf_سائيز, فراغ *معلومات);
GL_APICALL فراغ GL_APIENTRY glGetnUniformfvKHR (GLuint پروگرام, GLint location, GLsizei buf_سائيز, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY glGetnUniformivKHR (GLuint پروگرام, GLint location, GLsizei buf_سائيز, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetnUniformuivKHR (GLuint پروگرام, GLint location, GLsizei buf_سائيز, GLuint *params);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_KHR_robustness */

#جيڪڏهن_وصف_نه_ٿيل GL_KHR_shader_subgroup
#وصف_ڪريو GL_KHR_shader_subgroup 1
#وصف_ڪريو GL_SUBGROUP_سائيز_KHR              0x9532
#وصف_ڪريو GL_SUBGROUP_SUPPORTED_STAGES_KHR  0x9533
#وصف_ڪريو GL_SUBGROUP_SUPPORTED_FEATURES_KHR 0x9534
#وصف_ڪريو GL_SUBGROUP_QUAD_ALL_STAGES_KHR   0x9535
#وصف_ڪريو GL_SUBGROUP_FEATURE_BASIC_ٻٽو_انگ_KHR 0x00000001
#وصف_ڪريو GL_SUBGROUP_FEATURE_VOTE_ٻٽو_انگ_KHR  0x00000002
#وصف_ڪريو GL_SUBGROUP_FEATURE_ARITHMETIC_ٻٽو_انگ_KHR 0x00000004
#وصف_ڪريو GL_SUBGROUP_FEATURE_BALLOT_ٻٽو_انگ_KHR 0x00000008
#وصف_ڪريو GL_SUBGROUP_FEATURE_SHUFFLE_ٻٽو_انگ_KHR 0x00000010
#وصف_ڪريو GL_SUBGROUP_FEATURE_SHUFFLE_RELATIVE_ٻٽو_انگ_KHR 0x00000020
#وصف_ڪريو GL_SUBGROUP_FEATURE_CLUSTERED_ٻٽو_انگ_KHR 0x00000040
#وصف_ڪريو GL_SUBGROUP_FEATURE_QUAD_ٻٽو_انگ_KHR  0x00000080
#جيڪڏهن_پورو /* GL_KHR_shader_subgroup */

#جيڪڏهن_وصف_نه_ٿيل GL_KHR_texture_compression_astc_hdr
#وصف_ڪريو GL_KHR_texture_compression_astc_hdr 1
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_4x4_KHR   0x93B0
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_5x4_KHR   0x93B1
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_5x5_KHR   0x93B2
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_6x5_KHR   0x93B3
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_6x6_KHR   0x93B4
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_8x5_KHR   0x93B5
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_8x6_KHR   0x93B6
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_8x8_KHR   0x93B7
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_10x5_KHR  0x93B8
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_10x6_KHR  0x93B9
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_10x8_KHR  0x93BA
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_10x10_KHR 0x93BB
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_12x10_KHR 0x93BC
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_12x12_KHR 0x93BD
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR 0x93D0
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR 0x93D1
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR 0x93D2
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR 0x93D3
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR 0x93D4
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR 0x93D5
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR 0x93D6
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR 0x93D7
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR 0x93D8
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR 0x93D9
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR 0x93DA
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR 0x93DB
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR 0x93DC
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR 0x93DD
#جيڪڏهن_پورو /* GL_KHR_texture_compression_astc_hdr */

#جيڪڏهن_وصف_نه_ٿيل GL_KHR_texture_compression_astc_ldr
#وصف_ڪريو GL_KHR_texture_compression_astc_ldr 1
#جيڪڏهن_پورو /* GL_KHR_texture_compression_astc_ldr */

#جيڪڏهن_وصف_نه_ٿيل GL_KHR_texture_compression_astc_sliced_3d
#وصف_ڪريو GL_KHR_texture_compression_astc_sliced_3d 1
#جيڪڏهن_پورو /* GL_KHR_texture_compression_astc_sliced_3d */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_EGL_image
#وصف_ڪريو GL_OES_EGL_image 1
تعريفنوع فراغ *GLeglImageOES;
تعريفنوع فراغ (GL_APIENTRYP PFNGLEGLIMAGETARGETTEXTURE2DOESPROC) (GLenum هدف, GLeglImageOES image);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEGLIMAGETARGETRENDERBUFFERSTORAGEOESPROC) (GLenum هدف, GLeglImageOES image);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_EGLImage_هدف_Texture2_DOES (GLenum هدف, GLeglImageOES image);
GL_APICALL فراغ GL_APIENTRY gl_EGLImage_هدف_Renderbuffer_Storage_OES (GLenum هدف, GLeglImageOES image);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_OES_EGL_image */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_EGL_image_external
#وصف_ڪريو GL_OES_EGL_image_external 1
#وصف_ڪريو GL_TEXTURE_EXTERNAL_OES           0x8D65
#وصف_ڪريو GL_TEXTURE_BINDING_EXTERNAL_OES   0x8D67
#وصف_ڪريو GL_REQUIRED_TEXTURE_IMAGE_UNITS_OES 0x8D68
#وصف_ڪريو GL_SAMPLER_EXTERNAL_OES           0x8D66
#جيڪڏهن_پورو /* GL_OES_EGL_image_external */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_EGL_image_external_essl3
#وصف_ڪريو GL_OES_EGL_image_external_essl3 1
#جيڪڏهن_پورو /* GL_OES_EGL_image_external_essl3 */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_compressed_ETC1_RGB8_sub_texture
#وصف_ڪريو GL_OES_compressed_ETC1_RGB8_sub_texture 1
#جيڪڏهن_پورو /* GL_OES_compressed_ETC1_RGB8_sub_texture */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_compressed_ETC1_RGB8_texture
#وصف_ڪريو GL_OES_compressed_ETC1_RGB8_texture 1
#وصف_ڪريو GL_ETC1_RGB8_OES                  0x8D64
#جيڪڏهن_پورو /* GL_OES_compressed_ETC1_RGB8_texture */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_compressed_paletted_texture
#وصف_ڪريو GL_OES_compressed_paletted_texture 1
#وصف_ڪريو GL_PALETTE4_RGB8_OES              0x8B90
#وصف_ڪريو GL_PALETTE4_RGBA8_OES             0x8B91
#وصف_ڪريو GL_PALETTE4_R5_G6_B5_OES          0x8B92
#وصف_ڪريو GL_PALETTE4_RGBA4_OES             0x8B93
#وصف_ڪريو GL_PALETTE4_RGB5_A1_OES           0x8B94
#وصف_ڪريو GL_PALETTE8_RGB8_OES              0x8B95
#وصف_ڪريو GL_PALETTE8_RGBA8_OES             0x8B96
#وصف_ڪريو GL_PALETTE8_R5_G6_B5_OES          0x8B97
#وصف_ڪريو GL_PALETTE8_RGBA4_OES             0x8B98
#وصف_ڪريو GL_PALETTE8_RGB5_A1_OES           0x8B99
#جيڪڏهن_پورو /* GL_OES_compressed_paletted_texture */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_copy_image
#وصف_ڪريو GL_OES_copy_image 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYIMAGESUBDATAOESPROC) (GLuint srcName, GLenum src_هدف, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dst_هدف, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei src_ويڪر, GLsizei src_اوچائي, GLsizei src_اونهائي);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Copy_Image_Sub_معلومات_OES (GLuint srcName, GLenum src_هدف, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dst_هدف, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei src_ويڪر, GLsizei src_اوچائي, GLsizei src_اونهائي);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_OES_copy_image */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_depth24
#وصف_ڪريو GL_OES_depth24 1
#وصف_ڪريو GL_اونهائي_COMPONENT24_OES          0x81A6
#جيڪڏهن_پورو /* GL_OES_depth24 */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_depth32
#وصف_ڪريو GL_OES_depth32 1
#وصف_ڪريو GL_اونهائي_COMPONENT32_OES          0x81A7
#جيڪڏهن_پورو /* GL_OES_depth32 */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_اونهائي_texture
#وصف_ڪريو GL_OES_اونهائي_texture 1
#جيڪڏهن_پورو /* GL_OES_depth_texture */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_draw_buffers_اشاريي_وارو
#وصف_ڪريو GL_OES_draw_buffers_اشاريي_وارو 1
#وصف_ڪريو GL_MIN                            0x8007
#وصف_ڪريو GL_MAX                            0x8008
تعريفنوع فراغ (GL_APIENTRYP PFNGLENABLEIOESPROC) (GLenum هدف, GLuint اشاريو);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISABLEIOESPROC) (GLenum هدف, GLuint اشاريو);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONIOESPROC) (GLuint buf, GLenum گهڻائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEIOESPROC) (GLuint buf, GLenum گهڻائي_RGB, GLenum گهڻائي_Alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDFUNCIOESPROC) (GLuint buf, GLenum src, GLenum dst);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEIOESPROC) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOLORMASKIOESPROC) (GLuint اشاريو, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISENABLEDIOESPROC) (GLenum هدف, GLuint اشاريو);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glEnableiOES (GLenum هدف, GLuint اشاريو);
GL_APICALL فراغ GL_APIENTRY glDisableiOES (GLenum هدف, GLuint اشاريو);
GL_APICALL فراغ GL_APIENTRY glBlendEquationiOES (GLuint buf, GLenum گهڻائي);
GL_APICALL فراغ GL_APIENTRY glBlendEquationSeparateiOES (GLuint buf, GLenum گهڻائي_RGB, GLenum گهڻائي_Alpha);
GL_APICALL فراغ GL_APIENTRY glBlendFunciOES (GLuint buf, GLenum src, GLenum dst);
GL_APICALL فراغ GL_APIENTRY glBlendFuncSeparateiOES (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
GL_APICALL فراغ GL_APIENTRY glColorMaskiOES (GLuint اشاريو, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
GL_APICALL GLboolean GL_APIENTRY glIsEnablediOES (GLenum هدف, GLuint اشاريو);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_OES_draw_buffers_indexed */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_draw_elements_بنياد_راس
#وصف_ڪريو GL_OES_draw_elements_بنياد_راس 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSBASEVERTEXOESPROC) (GLenum گهڻائي, GLsizei ڳڻپ, GLenum type, ثابت فراغ *indices, GLint basevertex);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWRANGEELEMENTSBASEVERTEXOESPROC) (GLenum گهڻائي, GLuint شروعات, GLuint پڇاڙي, GLsizei ڳڻپ, GLenum type, ثابت فراغ *indices, GLint basevertex);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXOESPROC) (GLenum گهڻائي, GLsizei ڳڻپ, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLint basevertex);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSBASEVERTEXEXTPROC) (GLenum گهڻائي, ثابت GLsizei *ڳڻپ, GLenum type, ثابت فراغ *ثابت*indices, GLsizei drawcount, ثابت GLint *basevertex);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Draw_Elements_بنياد_راس_OES (GLenum گهڻائي, GLsizei ڳڻپ, GLenum type, ثابت فراغ *indices, GLint basevertex);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Range_Elements_بنياد_راس_OES (GLenum گهڻائي, GLuint شروعات, GLuint پڇاڙي, GLsizei ڳڻپ, GLenum type, ثابت فراغ *indices, GLint basevertex);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Elements_Instanced_بنياد_راس_OES (GLenum گهڻائي, GLsizei ڳڻپ, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLint basevertex);
GL_APICALL فراغ GL_APIENTRY gl_Multi_Draw_Elements_بنياد_راس_EXT (GLenum گهڻائي, ثابت GLsizei *ڳڻپ, GLenum type, ثابت فراغ *ثابت*indices, GLsizei drawcount, ثابت GLint *basevertex);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_OES_draw_elements_base_vertex */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_element_اشاريو_uint
#وصف_ڪريو GL_OES_element_اشاريو_uint 1
#جيڪڏهن_پورو /* GL_OES_element_index_uint */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_fbo_render_mipmap
#وصف_ڪريو GL_OES_fbo_render_mipmap 1
#جيڪڏهن_پورو /* GL_OES_fbo_render_mipmap */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_fragment_precision_مٿاهون
#وصف_ڪريو GL_OES_fragment_precision_مٿاهون 1
#جيڪڏهن_پورو /* GL_OES_fragment_precision_high */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_geometry_نقطو_سائيز
#وصف_ڪريو GL_OES_geometry_نقطو_سائيز 1
#جيڪڏهن_پورو /* GL_OES_geometry_point_size */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_geometry_shader
#وصف_ڪريو GL_OES_geometry_shader 1
#وصف_ڪريو GL_GEOMETRY_SHADER_OES            0x8DD9
#وصف_ڪريو GL_GEOMETRY_SHADER_ٻٽو_انگ_OES        0x00000004
#وصف_ڪريو GL_GEOMETRY_LINKED_VERTICES_ٻاهريون_OES 0x8916
#وصف_ڪريو GL_GEOMETRY_LINKED_داخلا_TYPE_OES 0x8917
#وصف_ڪريو GL_GEOMETRY_LINKED_OUTPUT_TYPE_OES 0x8918
#وصف_ڪريو GL_GEOMETRY_SHADER_INVOCATIONS_OES 0x887F
#وصف_ڪريو GL_LAYER_PROVOKING_راس_OES     0x825E
#وصف_ڪريو GL_سٽون_ADJACENCY_OES            0x000A
#وصف_ڪريو GL_سٽ_STRIP_ADJACENCY_OES       0x000B
#وصف_ڪريو GL_TRIANGLES_ADJACENCY_OES        0x000C
#وصف_ڪريو GL_TRIANGLE_STRIP_ADJACENCY_OES   0x000D
#وصف_ڪريو GL_MAX_GEOMETRY_هڪجهڙو_COMPONENTS_OES 0x8DDF
#وصف_ڪريو GL_MAX_GEOMETRY_هڪجهڙو_بلاڪون_OES 0x8A2C
#وصف_ڪريو GL_MAX_COMBINED_GEOMETRY_هڪجهڙو_COMPONENTS_OES 0x8A32
#وصف_ڪريو GL_MAX_GEOMETRY_داخلا_COMPONENTS_OES 0x9123
#وصف_ڪريو GL_MAX_GEOMETRY_OUTPUT_COMPONENTS_OES 0x9124
#وصف_ڪريو GL_MAX_GEOMETRY_OUTPUT_VERTICES_OES 0x8DE0
#وصف_ڪريو GL_MAX_GEOMETRY_ڪل_OUTPUT_COMPONENTS_OES 0x8DE1
#وصف_ڪريو GL_MAX_GEOMETRY_SHADER_INVOCATIONS_OES 0x8E5A
#وصف_ڪريو GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_OES 0x8C29
#وصف_ڪريو GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS_OES 0x92CF
#وصف_ڪريو GL_MAX_GEOMETRY_ATOMIC_COUNTERS_OES 0x92D5
#وصف_ڪريو GL_MAX_GEOMETRY_IMAGE_UNIFORMS_OES 0x90CD
#وصف_ڪريو GL_MAX_GEOMETRY_SHADER_STORAGE_بلاڪون_OES 0x90D7
#وصف_ڪريو GL_پهريون_راس_CONVENTION_OES    0x8E4D
#وصف_ڪريو GL_آخري_راس_CONVENTION_OES     0x8E4E
#وصف_ڪريو GL_UNDEFINED_راس_OES           0x8260
#وصف_ڪريو GL_PRIMITIVES_GENERATED_OES       0x8C87
#وصف_ڪريو GL_FRAMEBUFFER_DEFAULT_LAYERS_OES 0x9312
#وصف_ڪريو GL_MAX_FRAMEBUFFER_LAYERS_OES     0x9317
#وصف_ڪريو GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_OES 0x8DA8
#وصف_ڪريو GL_FRAMEBUFFER_ATTACHMENT_LAYERED_OES 0x8DA7
#وصف_ڪريو GL_REFERENCED_BY_GEOMETRY_SHADER_OES 0x9309
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREOESPROC) (GLenum هدف, GLenum attachment, GLuint texture, GLint level);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferTextureOES (GLenum هدف, GLenum attachment, GLuint texture, GLint level);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_OES_geometry_shader */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_get_پروگرام_ٻٽو
#وصف_ڪريو GL_OES_get_پروگرام_ٻٽو 1
#وصف_ڪريو GL_پروگرام_ٻٽو_ڊيگهائي_OES      0x8741
#وصف_ڪريو GL_انگ_پروگرام_ٻٽو_FORMATS_OES 0x87FE
#وصف_ڪريو GL_پروگرام_ٻٽو_FORMATS_OES     0x87FF
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMBINARYOESPROC) (GLuint پروگرام, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLenum *ٻٽو_Format, فراغ *ٻٽو);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMBINARYOESPROC) (GLuint پروگرام, GLenum ٻٽو_Format, ثابت فراغ *ٻٽو, GLint ڊيگهائي);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Get_پروگرام_ٻٽو_OES (GLuint پروگرام, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLenum *ٻٽو_Format, فراغ *ٻٽو);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_ٻٽو_OES (GLuint پروگرام, GLenum ٻٽو_Format, ثابت فراغ *ٻٽو, GLint ڊيگهائي);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_OES_get_program_binary */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_gpu_shader5
#وصف_ڪريو GL_OES_gpu_shader5 1
#جيڪڏهن_پورو /* GL_OES_gpu_shader5 */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_mapbuffer
#وصف_ڪريو GL_OES_mapbuffer 1
#وصف_ڪريو GL_WRITE_ONLY_OES                 0x88B9
#وصف_ڪريو GL_بفر_ACCESS_OES              0x88BB
#وصف_ڪريو GL_بفر_MAPPED_OES              0x88BC
#وصف_ڪريو GL_بفر_MAP_اشارو_OES         0x88BD
تعريفنوع فراغ *(GL_APIENTRYP PFNGLMAPBUFFEROESPROC) (GLenum هدف, GLenum access);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLUNMAPBUFFEROESPROC) (GLenum هدف);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETBUFFERPOINTERVOESPROC) (GLenum هدف, GLenum pname, فراغ **params);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ *GL_APIENTRY gl_Map_بفر_OES (GLenum هدف, GLenum access);
GL_APICALL GLboolean GL_APIENTRY gl_Unmap_بفر_OES (GLenum هدف);
GL_APICALL فراغ GL_APIENTRY gl_Get_بفر_Pointerv_OES (GLenum هدف, GLenum pname, فراغ **params);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_OES_mapbuffer */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_packed_اونهائي_stencil
#وصف_ڪريو GL_OES_packed_اونهائي_stencil 1
#وصف_ڪريو GL_اونهائي_STENCIL_OES              0x84F9
#وصف_ڪريو GL_UNSIGNED_INT_24_8_OES          0x84FA
#وصف_ڪريو GL_DEPTH24_STENCIL8_OES           0x88F0
#جيڪڏهن_پورو /* GL_OES_packed_depth_stencil */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_primitive_bounding_box
#وصف_ڪريو GL_OES_primitive_bounding_box 1
#وصف_ڪريو GL_PRIMITIVE_BOUNDING_BOX_OES     0x92BE
تعريفنوع فراغ (GL_APIENTRYP PFNGLPRIMITIVEBOUNDINGBOXOESPROC) (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glPrimitiveBoundingBoxOES (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_OES_primitive_bounding_box */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_required_internalformat
#وصف_ڪريو GL_OES_required_internalformat 1
#وصف_ڪريو GL_ALPHA8_OES                     0x803C
#وصف_ڪريو GL_اونهائي_COMPONENT16_OES          0x81A5
#وصف_ڪريو GL_LUMINANCE4_ALPHA4_OES          0x8043
#وصف_ڪريو GL_LUMINANCE8_ALPHA8_OES          0x8045
#وصف_ڪريو GL_LUMINANCE8_OES                 0x8040
#وصف_ڪريو GL_RGBA4_OES                      0x8056
#وصف_ڪريو GL_RGB5_A1_OES                    0x8057
#وصف_ڪريو GL_RGB565_OES                     0x8D62
#وصف_ڪريو GL_RGB8_OES                       0x8051
#وصف_ڪريو GL_RGBA8_OES                      0x8058
#وصف_ڪريو GL_RGB10_EXT                      0x8052
#وصف_ڪريو GL_RGB10_A2_EXT                   0x8059
#جيڪڏهن_پورو /* GL_OES_required_internalformat */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_rgb8_rgba8
#وصف_ڪريو GL_OES_rgb8_rgba8 1
#جيڪڏهن_پورو /* GL_OES_rgb8_rgba8 */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_sample_shading
#وصف_ڪريو GL_OES_sample_shading 1
#وصف_ڪريو GL_SAMPLE_SHADING_OES             0x8C36
#وصف_ڪريو GL_MIN_SAMPLE_SHADING_قدر_OES   0x8C37
تعريفنوع فراغ (GL_APIENTRYP PFNGLMINSAMPLESHADINGOESPROC) (GLfloat قدر);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glMinSampleShadingOES (GLfloat قدر);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_OES_sample_shading */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_sample_variables
#وصف_ڪريو GL_OES_sample_variables 1
#جيڪڏهن_پورو /* GL_OES_sample_variables */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_shader_image_atomic
#وصف_ڪريو GL_OES_shader_image_atomic 1
#جيڪڏهن_پورو /* GL_OES_shader_image_atomic */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_shader_io_بلاڪون
#وصف_ڪريو GL_OES_shader_io_بلاڪون 1
#جيڪڏهن_پورو /* GL_OES_shader_io_blocks */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_shader_multisample_interpolation
#وصف_ڪريو GL_OES_shader_multisample_interpolation 1
#وصف_ڪريو GL_MIN_FRAGMENT_INTERPOLATION_وٿي_OES 0x8E5B
#وصف_ڪريو GL_MAX_FRAGMENT_INTERPOLATION_وٿي_OES 0x8E5C
#وصف_ڪريو GL_FRAGMENT_INTERPOLATION_وٿي_بٽ_OES 0x8E5D
#جيڪڏهن_پورو /* GL_OES_shader_multisample_interpolation */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_standard_derivatives
#وصف_ڪريو GL_OES_standard_derivatives 1
#وصف_ڪريو GL_FRAGMENT_SHADER_DERIVATIVE_HINT_OES 0x8B8B
#جيڪڏهن_پورو /* GL_OES_standard_derivatives */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_stencil1
#وصف_ڪريو GL_OES_stencil1 1
#وصف_ڪريو GL_STENCIL_INDEX1_OES             0x8D46
#جيڪڏهن_پورو /* GL_OES_stencil1 */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_stencil4
#وصف_ڪريو GL_OES_stencil4 1
#وصف_ڪريو GL_STENCIL_INDEX4_OES             0x8D47
#جيڪڏهن_پورو /* GL_OES_stencil4 */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_surfaceless_context
#وصف_ڪريو GL_OES_surfaceless_context 1
#وصف_ڪريو GL_FRAMEBUFFER_UNDEFINED_OES      0x8219
#جيڪڏهن_پورو /* GL_OES_surfaceless_context */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_tessellation_نقطو_سائيز
#وصف_ڪريو GL_OES_tessellation_نقطو_سائيز 1
#جيڪڏهن_پورو /* GL_OES_tessellation_point_size */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_tessellation_shader
#وصف_ڪريو GL_OES_tessellation_shader 1
#وصف_ڪريو GL_PATCHES_OES                    0x000E
#وصف_ڪريو GL_PATCH_VERTICES_OES             0x8E72
#وصف_ڪريو GL_TESS_CONTROL_OUTPUT_VERTICES_OES 0x8E75
#وصف_ڪريو GL_TESS_GEN_گهڻائي_OES              0x8E76
#وصف_ڪريو GL_TESS_GEN_SPACING_OES           0x8E77
#وصف_ڪريو GL_TESS_GEN_راس_ترتيب_OES      0x8E78
#وصف_ڪريو GL_TESS_GEN_نقطو_گهڻائي_OES        0x8E79
#وصف_ڪريو GL_ISOLINES_OES                   0x8E7A
#وصف_ڪريو GL_QUADS_OES                      0x0007
#وصف_ڪريو GL_FRACTIONAL_ODD_OES             0x8E7B
#وصف_ڪريو GL_FRACTIONAL_EVEN_OES            0x8E7C
#وصف_ڪريو GL_MAX_PATCH_VERTICES_OES         0x8E7D
#وصف_ڪريو GL_MAX_TESS_GEN_LEVEL_OES         0x8E7E
#وصف_ڪريو GL_MAX_TESS_CONTROL_هڪجهڙو_COMPONENTS_OES 0x8E7F
#وصف_ڪريو GL_MAX_TESS_EVALUATION_هڪجهڙو_COMPONENTS_OES 0x8E80
#وصف_ڪريو GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS_OES 0x8E81
#وصف_ڪريو GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS_OES 0x8E82
#وصف_ڪريو GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS_OES 0x8E83
#وصف_ڪريو GL_MAX_TESS_PATCH_COMPONENTS_OES  0x8E84
#وصف_ڪريو GL_MAX_TESS_CONTROL_ڪل_OUTPUT_COMPONENTS_OES 0x8E85
#وصف_ڪريو GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS_OES 0x8E86
#وصف_ڪريو GL_MAX_TESS_CONTROL_هڪجهڙو_بلاڪون_OES 0x8E89
#وصف_ڪريو GL_MAX_TESS_EVALUATION_هڪجهڙو_بلاڪون_OES 0x8E8A
#وصف_ڪريو GL_MAX_TESS_CONTROL_داخلا_COMPONENTS_OES 0x886C
#وصف_ڪريو GL_MAX_TESS_EVALUATION_داخلا_COMPONENTS_OES 0x886D
#وصف_ڪريو GL_MAX_COMBINED_TESS_CONTROL_هڪجهڙو_COMPONENTS_OES 0x8E1E
#وصف_ڪريو GL_MAX_COMBINED_TESS_EVALUATION_هڪجهڙو_COMPONENTS_OES 0x8E1F
#وصف_ڪريو GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS_OES 0x92CD
#وصف_ڪريو GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS_OES 0x92CE
#وصف_ڪريو GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS_OES 0x92D3
#وصف_ڪريو GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS_OES 0x92D4
#وصف_ڪريو GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS_OES 0x90CB
#وصف_ڪريو GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS_OES 0x90CC
#وصف_ڪريو GL_MAX_TESS_CONTROL_SHADER_STORAGE_بلاڪون_OES 0x90D8
#وصف_ڪريو GL_MAX_TESS_EVALUATION_SHADER_STORAGE_بلاڪون_OES 0x90D9
#وصف_ڪريو GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED_OES 0x8221
#وصف_ڪريو GL_IS_في_PATCH_OES               0x92E7
#وصف_ڪريو GL_REFERENCED_BY_TESS_CONTROL_SHADER_OES 0x9307
#وصف_ڪريو GL_REFERENCED_BY_TESS_EVALUATION_SHADER_OES 0x9308
#وصف_ڪريو GL_TESS_CONTROL_SHADER_OES        0x8E88
#وصف_ڪريو GL_TESS_EVALUATION_SHADER_OES     0x8E87
#وصف_ڪريو GL_TESS_CONTROL_SHADER_ٻٽو_انگ_OES    0x00000008
#وصف_ڪريو GL_TESS_EVALUATION_SHADER_ٻٽو_انگ_OES 0x00000010
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATCHPARAMETERIOESPROC) (GLenum pname, GLint قدر);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glPatchParameteriOES (GLenum pname, GLint قدر);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_OES_tessellation_shader */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_texture_3D
#وصف_ڪريو GL_OES_texture_3D 1
#وصف_ڪريو GL_TEXTURE_WRAP_R_OES             0x8072
#وصف_ڪريو GL_TEXTURE_3D_OES                 0x806F
#وصف_ڪريو GL_TEXTURE_BINDING_3D_OES         0x806A
#وصف_ڪريو GL_MAX_3_D_TEXTURE_سائيز_OES        0x8073
#وصف_ڪريو GL_SAMPLER_3D_OES                 0x8B5F
#وصف_ڪريو GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_3D_ZOFFSET_OES 0x8CD4
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXIMAGE3DOESPROC) (GLenum هدف, GLint level, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLint border, GLenum format, GLenum type, ثابت فراغ *pixels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSUBIMAGE3DOESPROC) (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLenum format, GLenum type, ثابت فراغ *pixels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYTEXSUBIMAGE3DOESPROC) (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei ويڪر, GLsizei اوچائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOMPRESSEDTEXIMAGE3DOESPROC) (GLenum هدف, GLint level, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLint border, GLsizei image_سائيز, ثابت فراغ *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE3DOESPROC) (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLenum format, GLsizei image_سائيز, ثابت فراغ *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE3DOESPROC) (GLenum هدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTexImage3DOES (GLenum هدف, GLint level, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLint border, GLenum format, GLenum type, ثابت فراغ *pixels);
GL_APICALL فراغ GL_APIENTRY glTexSubImage3DOES (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLenum format, GLenum type, ثابت فراغ *pixels);
GL_APICALL فراغ GL_APIENTRY glCopyTexSubImage3DOES (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei ويڪر, GLsizei اوچائي);
GL_APICALL فراغ GL_APIENTRY glCompressedTexImage3DOES (GLenum هدف, GLint level, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLint border, GLsizei image_سائيز, ثابت فراغ *معلومات);
GL_APICALL فراغ GL_APIENTRY glCompressedTexSubImage3DOES (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLenum format, GLsizei image_سائيز, ثابت فراغ *معلومات);
GL_APICALL فراغ GL_APIENTRY glFramebufferTexture3DOES (GLenum هدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_OES_texture_3D */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_texture_border_clamp
#وصف_ڪريو GL_OES_texture_border_clamp 1
#وصف_ڪريو GL_TEXTURE_BORDER_COLOR_OES       0x1004
#وصف_ڪريو GL_CLAMP_منزل_BORDER_OES            0x812D
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERIIVOESPROC) (GLenum هدف, GLenum pname, ثابت GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERIUIVOESPROC) (GLenum هدف, GLenum pname, ثابت GLuint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXPARAMETERIIVOESPROC) (GLenum هدف, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXPARAMETERIUIVOESPROC) (GLenum هدف, GLenum pname, GLuint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIIVOESPROC) (GLuint sampler, GLenum pname, ثابت GLint *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIUIVOESPROC) (GLuint sampler, GLenum pname, ثابت GLuint *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIIVOESPROC) (GLuint sampler, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIUIVOESPROC) (GLuint sampler, GLenum pname, GLuint *params);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTexParameterIivOES (GLenum هدف, GLenum pname, ثابت GLint *params);
GL_APICALL فراغ GL_APIENTRY glTexParameterIuivOES (GLenum هدف, GLenum pname, ثابت GLuint *params);
GL_APICALL فراغ GL_APIENTRY glGetTexParameterIivOES (GLenum هدف, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetTexParameterIuivOES (GLenum هدف, GLenum pname, GLuint *params);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterIivOES (GLuint sampler, GLenum pname, ثابت GLint *param);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterIuivOES (GLuint sampler, GLenum pname, ثابت GLuint *param);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameterIivOES (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameterIuivOES (GLuint sampler, GLenum pname, GLuint *params);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_OES_texture_border_clamp */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_texture_بفر
#وصف_ڪريو GL_OES_texture_بفر 1
#وصف_ڪريو GL_TEXTURE_بفر_OES             0x8C2A
#وصف_ڪريو GL_TEXTURE_بفر_BINDING_OES     0x8C2A
#وصف_ڪريو GL_MAX_TEXTURE_بفر_سائيز_OES    0x8C2B
#وصف_ڪريو GL_TEXTURE_BINDING_بفر_OES     0x8C2C
#وصف_ڪريو GL_TEXTURE_بفر_معلومات_STORE_BINDING_OES 0x8C2D
#وصف_ڪريو GL_TEXTURE_بفر_وٿي_ALIGNMENT_OES 0x919F
#وصف_ڪريو GL_SAMPLER_بفر_OES             0x8DC2
#وصف_ڪريو GL_INT_SAMPLER_بفر_OES         0x8DD0
#وصف_ڪريو GL_UNSIGNED_INT_SAMPLER_بفر_OES 0x8DD8
#وصف_ڪريو GL_IMAGE_بفر_OES               0x9051
#وصف_ڪريو GL_INT_IMAGE_بفر_OES           0x905C
#وصف_ڪريو GL_UNSIGNED_INT_IMAGE_بفر_OES  0x9067
#وصف_ڪريو GL_TEXTURE_بفر_وٿي_OES      0x919D
#وصف_ڪريو GL_TEXTURE_بفر_سائيز_OES        0x919E
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXBUFFEROESPROC) (GLenum هدف, GLenum internalformat, GLuint بفر_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXBUFFERRANGEOESPROC) (GLenum هدف, GLenum internalformat, GLuint بفر_2, GLintptr وٿي_2, GLsizeiptr سائيز);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Tex_بفر_OES (GLenum هدف, GLenum internalformat, GLuint بفر_2);
GL_APICALL فراغ GL_APIENTRY gl_Tex_بفر_Range_OES (GLenum هدف, GLenum internalformat, GLuint بفر_2, GLintptr وٿي_2, GLsizeiptr سائيز);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_OES_texture_buffer */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_texture_compression_astc
#وصف_ڪريو GL_OES_texture_compression_astc 1
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_3x3x3_OES 0x93C0
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_4x3x3_OES 0x93C1
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_4x4x3_OES 0x93C2
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_4x4x4_OES 0x93C3
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_5x4x4_OES 0x93C4
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_5x5x4_OES 0x93C5
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_5x5x5_OES 0x93C6
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_6x5x5_OES 0x93C7
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_6x6x5_OES 0x93C8
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_6x6x6_OES 0x93C9
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_3x3x3_OES 0x93E0
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x3x3_OES 0x93E1
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4x3_OES 0x93E2
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4x4_OES 0x93E3
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4x4_OES 0x93E4
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5x4_OES 0x93E5
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5x5_OES 0x93E6
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5x5_OES 0x93E7
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6x5_OES 0x93E8
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6x6_OES 0x93E9
#جيڪڏهن_پورو /* GL_OES_texture_compression_astc */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_texture_cube_map_array
#وصف_ڪريو GL_OES_texture_cube_map_array 1
#وصف_ڪريو GL_TEXTURE_CUBE_MAP_ARRAY_OES     0x9009
#وصف_ڪريو GL_TEXTURE_BINDING_CUBE_MAP_ARRAY_OES 0x900A
#وصف_ڪريو GL_SAMPLER_CUBE_MAP_ARRAY_OES     0x900C
#وصف_ڪريو GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW_OES 0x900D
#وصف_ڪريو GL_INT_SAMPLER_CUBE_MAP_ARRAY_OES 0x900E
#وصف_ڪريو GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY_OES 0x900F
#وصف_ڪريو GL_IMAGE_CUBE_MAP_ARRAY_OES       0x9054
#وصف_ڪريو GL_INT_IMAGE_CUBE_MAP_ARRAY_OES   0x905F
#وصف_ڪريو GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY_OES 0x906A
#جيڪڏهن_پورو /* GL_OES_texture_cube_map_array */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_texture_float
#وصف_ڪريو GL_OES_texture_float 1
#جيڪڏهن_پورو /* GL_OES_texture_float */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_texture_float_لڪيري
#وصف_ڪريو GL_OES_texture_float_لڪيري 1
#جيڪڏهن_پورو /* GL_OES_texture_float_linear */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_texture_half_float
#وصف_ڪريو GL_OES_texture_half_float 1
#وصف_ڪريو GL_HALF_FLOAT_OES                 0x8D61
#جيڪڏهن_پورو /* GL_OES_texture_half_float */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_texture_half_float_لڪيري
#وصف_ڪريو GL_OES_texture_half_float_لڪيري 1
#جيڪڏهن_پورو /* GL_OES_texture_half_float_linear */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_texture_npot
#وصف_ڪريو GL_OES_texture_npot 1
#جيڪڏهن_پورو /* GL_OES_texture_npot */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_texture_stencil8
#وصف_ڪريو GL_OES_texture_stencil8 1
#وصف_ڪريو GL_STENCIL_اشاريو_OES              0x1901
#وصف_ڪريو GL_STENCIL_INDEX8_OES             0x8D48
#جيڪڏهن_پورو /* GL_OES_texture_stencil8 */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_texture_storage_multisample_2d_array
#وصف_ڪريو GL_OES_texture_storage_multisample_2d_array 1
#وصف_ڪريو GL_TEXTURE_2D_MULTISAMPLE_ARRAY_OES 0x9102
#وصف_ڪريو GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY_OES 0x9105
#وصف_ڪريو GL_SAMPLER_2D_MULTISAMPLE_ARRAY_OES 0x910B
#وصف_ڪريو GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY_OES 0x910C
#وصف_ڪريو GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY_OES 0x910D
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE3DMULTISAMPLEOESPROC) (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLboolean fixedsamplelocations);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTexStorage3DMultisampleOES (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLboolean fixedsamplelocations);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_OES_texture_storage_multisample_2d_array */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_texture_view
#وصف_ڪريو GL_OES_texture_view 1
#وصف_ڪريو GL_TEXTURE_VIEW_MIN_LEVEL_OES     0x82DB
#وصف_ڪريو GL_TEXTURE_VIEW_انگ_سطحون_OES    0x82DC
#وصف_ڪريو GL_TEXTURE_VIEW_MIN_LAYER_OES     0x82DD
#وصف_ڪريو GL_TEXTURE_VIEW_انگ_LAYERS_OES    0x82DE
#وصف_ڪريو GL_TEXTURE_IMMUTABLE_سطحون       0x82DF
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTUREVIEWOESPROC) (GLuint texture, GLenum هدف, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTextureViewOES (GLuint texture, GLenum هدف, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_OES_texture_view */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_راس_array_object
#وصف_ڪريو GL_OES_راس_array_object 1
#وصف_ڪريو GL_راس_ARRAY_BINDING_OES       0x85B5
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDVERTEXARRAYOESPROC) (GLuint array);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEVERTEXARRAYSOESPROC) (GLsizei n, ثابت GLuint *arrays);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENVERTEXARRAYSOESPROC) (GLsizei n, GLuint *arrays);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISVERTEXARRAYOESPROC) (GLuint array);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Bind_راس_Array_OES (GLuint array);
GL_APICALL فراغ GL_APIENTRY gl_Delete_راس_Arrays_OES (GLsizei n, ثابت GLuint *arrays);
GL_APICALL فراغ GL_APIENTRY gl_Gen_راس_Arrays_OES (GLsizei n, GLuint *arrays);
GL_APICALL GLboolean GL_APIENTRY gl_Is_راس_Array_OES (GLuint array);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_OES_vertex_array_object */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_راس_half_float
#وصف_ڪريو GL_OES_راس_half_float 1
#جيڪڏهن_پورو /* GL_OES_vertex_half_float */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_راس_type_10_10_10_2
#وصف_ڪريو GL_OES_راس_type_10_10_10_2 1
#وصف_ڪريو GL_UNSIGNED_INT_10_10_10_2_OES    0x8DF6
#وصف_ڪريو GL_INT_10_10_10_2_OES             0x8DF7
#جيڪڏهن_پورو /* GL_OES_vertex_type_10_10_10_2 */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_viewport_array
#وصف_ڪريو GL_OES_viewport_array 1
#وصف_ڪريو GL_MAX_VIEWPORTS_OES              0x825B
#وصف_ڪريو GL_VIEWPORT_SUBPIXEL_بٽ_OES     0x825C
#وصف_ڪريو GL_VIEWPORT_BOUNDS_RANGE_OES      0x825D
#وصف_ڪريو GL_VIEWPORT_اشاريو_PROVOKING_راس_OES 0x825F
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTARRAYVOESPROC) (GLuint پهريون, GLsizei ڳڻپ, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTINDEXEDFOESPROC) (GLuint اشاريو, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTINDEXEDFVOESPROC) (GLuint اشاريو, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSORARRAYVOESPROC) (GLuint پهريون, GLsizei ڳڻپ, ثابت GLint *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSORINDEXEDOESPROC) (GLuint اشاريو, GLint کاٻو, GLint bottom, GLsizei ويڪر, GLsizei اوچائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSORINDEXEDVOESPROC) (GLuint اشاريو, ثابت GLint *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHRANGEARRAYFVOESPROC) (GLuint پهريون, GLsizei ڳڻپ, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHRANGEINDEXEDFOESPROC) (GLuint اشاريو, GLfloat n, GLfloat f);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFLOATI_VOESPROC) (GLenum هدف, GLuint اشاريو, GLfloat *معلومات);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glViewportArrayvOES (GLuint پهريون, GLsizei ڳڻپ, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY glViewportIndexedfOES (GLuint اشاريو, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
GL_APICALL فراغ GL_APIENTRY glViewportIndexedfvOES (GLuint اشاريو, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY glScissorArrayvOES (GLuint پهريون, GLsizei ڳڻپ, ثابت GLint *v);
GL_APICALL فراغ GL_APIENTRY gl_Scissor_اشاريي_وارو_OES (GLuint اشاريو, GLint کاٻو, GLint bottom, GLsizei ويڪر, GLsizei اوچائي);
GL_APICALL فراغ GL_APIENTRY glScissorIndexedvOES (GLuint اشاريو, ثابت GLint *v);
GL_APICALL فراغ GL_APIENTRY gl_اونهائي_Range_Arrayfv_OES (GLuint پهريون, GLsizei ڳڻپ, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY gl_اونهائي_Range_Indexedf_OES (GLuint اشاريو, GLfloat n, GLfloat f);
GL_APICALL فراغ GL_APIENTRY glGetFloati_vOES (GLenum هدف, GLuint اشاريو, GLfloat *معلومات);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_OES_viewport_array */

#جيڪڏهن_وصف_نه_ٿيل GL_AMD_compressed_3DC_texture
#وصف_ڪريو GL_AMD_compressed_3DC_texture 1
#وصف_ڪريو GL_3DC_X_AMD                      0x87F9
#وصف_ڪريو GL_3DC_XY_AMD                     0x87FA
#جيڪڏهن_پورو /* GL_AMD_compressed_3DC_texture */

#جيڪڏهن_وصف_نه_ٿيل GL_AMD_compressed_ATC_texture
#وصف_ڪريو GL_AMD_compressed_ATC_texture 1
#وصف_ڪريو GL_ATC_RGB_AMD                    0x8C92
#وصف_ڪريو GL_ATC_RGBA_EXPLICIT_ALPHA_AMD    0x8C93
#وصف_ڪريو GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD 0x87EE
#جيڪڏهن_پورو /* GL_AMD_compressed_ATC_texture */

#جيڪڏهن_وصف_نه_ٿيل GL_AMD_framebuffer_multisample_advanced
#وصف_ڪريو GL_AMD_framebuffer_multisample_advanced 1
#وصف_ڪريو GL_RENDERBUFFER_STORAGE_SAMPLES_AMD 0x91B2
#وصف_ڪريو GL_MAX_COLOR_FRAMEBUFFER_SAMPLES_AMD 0x91B3
#وصف_ڪريو GL_MAX_COLOR_FRAMEBUFFER_STORAGE_SAMPLES_AMD 0x91B4
#وصف_ڪريو GL_MAX_اونهائي_STENCIL_FRAMEBUFFER_SAMPLES_AMD 0x91B5
#وصف_ڪريو GL_انگ_SUPPORTED_MULTISAMPLE_MODES_AMD 0x91B6
#وصف_ڪريو GL_SUPPORTED_MULTISAMPLE_MODES_AMD 0x91B7
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC) (GLenum هدف, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC) (GLuint renderbuffer, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glRenderbufferStorageMultisampleAdvancedAMD (GLenum هدف, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
GL_APICALL فراغ GL_APIENTRY glNamedRenderbufferStorageMultisampleAdvancedAMD (GLuint renderbuffer, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_AMD_framebuffer_multisample_advanced */

#جيڪڏهن_وصف_نه_ٿيل GL_AMD_performance_monitor
#وصف_ڪريو GL_AMD_performance_monitor 1
#وصف_ڪريو GL_COUNTER_TYPE_AMD               0x8BC0
#وصف_ڪريو GL_COUNTER_RANGE_AMD              0x8BC1
#وصف_ڪريو GL_UNSIGNED_INT64_AMD             0x8BC2
#وصف_ڪريو GL_PERCENTAGE_AMD                 0x8BC3
#وصف_ڪريو GL_PERFMON_نتيجو_موجود_AMD   0x8BC4
#وصف_ڪريو GL_PERFMON_نتيجو_سائيز_AMD        0x8BC5
#وصف_ڪريو GL_PERFMON_نتيجو_AMD             0x8BC6
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFMONITORGROUPSAMDPROC) (GLint *انگ_Groups, GLsizei groups_سائيز, GLuint *groups);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFMONITORCOUNTERSAMDPROC) (GLuint گروهه, GLint *انگ_Counters, GLint *max_سرگرم_Counters, GLsizei counter_سائيز, GLuint *counters);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFMONITORGROUPSTRINGAMDPROC) (GLuint گروهه, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLchar *گروهه_String);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC) (GLuint گروهه, GLuint counter, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLchar *counterString);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFMONITORCOUNTERINFOAMDPROC) (GLuint گروهه, GLuint counter, GLenum pname, فراغ *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENPERFMONITORSAMDPROC) (GLsizei n, GLuint *monitors);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEPERFMONITORSAMDPROC) (GLsizei n, GLuint *monitors);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSELECTPERFMONITORCOUNTERSAMDPROC) (GLuint monitor, GLboolean enable, GLuint گروهه, GLint انگ_Counters, GLuint *counterList);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBEGINPERFMONITORAMDPROC) (GLuint monitor);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENDPERFMONITORAMDPROC) (GLuint monitor);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFMONITORCOUNTERDATAAMDPROC) (GLuint monitor, GLenum pname, GLsizei معلومات_سائيز_2, GLuint *معلومات, GLint *بائيٽون_Written);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glGetPerfMonitorGroupsAMD (GLint *انگ_Groups, GLsizei groups_سائيز, GLuint *groups);
GL_APICALL فراغ GL_APIENTRY glGetPerfMonitorCountersAMD (GLuint گروهه, GLint *انگ_Counters, GLint *max_سرگرم_Counters, GLsizei counter_سائيز, GLuint *counters);
GL_APICALL فراغ GL_APIENTRY gl_Get_Perf_Monitor_گروهه_String_AMD (GLuint گروهه, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLchar *گروهه_String);
GL_APICALL فراغ GL_APIENTRY glGetPerfMonitorCounterStringAMD (GLuint گروهه, GLuint counter, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLchar *counterString);
GL_APICALL فراغ GL_APIENTRY glGetPerfMonitorCounterInfoAMD (GLuint گروهه, GLuint counter, GLenum pname, فراغ *معلومات);
GL_APICALL فراغ GL_APIENTRY glGenPerfMonitorsAMD (GLsizei n, GLuint *monitors);
GL_APICALL فراغ GL_APIENTRY glDeletePerfMonitorsAMD (GLsizei n, GLuint *monitors);
GL_APICALL فراغ GL_APIENTRY glSelectPerfMonitorCountersAMD (GLuint monitor, GLboolean enable, GLuint گروهه, GLint انگ_Counters, GLuint *counterList);
GL_APICALL فراغ GL_APIENTRY glBeginPerfMonitorAMD (GLuint monitor);
GL_APICALL فراغ GL_APIENTRY gl_پڇاڙي_Perf_Monitor_AMD (GLuint monitor);
GL_APICALL فراغ GL_APIENTRY gl_Get_Perf_Monitor_Counter_معلومات_AMD (GLuint monitor, GLenum pname, GLsizei معلومات_سائيز_2, GLuint *معلومات, GLint *بائيٽون_Written);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_AMD_performance_monitor */

#جيڪڏهن_وصف_نه_ٿيل GL_AMD_پروگرام_ٻٽو_Z400
#وصف_ڪريو GL_AMD_پروگرام_ٻٽو_Z400 1
#وصف_ڪريو GL_Z400_ٻٽو_AMD                0x8740
#جيڪڏهن_پورو /* GL_AMD_program_binary_Z400 */

#جيڪڏهن_وصف_نه_ٿيل GL_ANDROID_extension_pack_es31a
#وصف_ڪريو GL_ANDROID_extension_pack_es31a 1
#جيڪڏهن_پورو /* GL_ANDROID_extension_pack_es31a */

#جيڪڏهن_وصف_نه_ٿيل GL_ANGLE_اونهائي_texture
#وصف_ڪريو GL_ANGLE_اونهائي_texture 1
#جيڪڏهن_پورو /* GL_ANGLE_depth_texture */

#جيڪڏهن_وصف_نه_ٿيل GL_ANGLE_framebuffer_blit
#وصف_ڪريو GL_ANGLE_framebuffer_blit 1
#وصف_ڪريو GL_READ_FRAMEBUFFER_ANGLE         0x8CA8
#وصف_ڪريو GL_DRAW_FRAMEBUFFER_ANGLE         0x8CA9
#وصف_ڪريو GL_DRAW_FRAMEBUFFER_BINDING_ANGLE 0x8CA6
#وصف_ڪريو GL_READ_FRAMEBUFFER_BINDING_ANGLE 0x8CAA
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLITFRAMEBUFFERANGLEPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield نقاب, GLenum filter);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glBlitFramebufferANGLE (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield نقاب, GLenum filter);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_ANGLE_framebuffer_blit */

#جيڪڏهن_وصف_نه_ٿيل GL_ANGLE_framebuffer_multisample
#وصف_ڪريو GL_ANGLE_framebuffer_multisample 1
#وصف_ڪريو GL_RENDERBUFFER_SAMPLES_ANGLE     0x8CAB
#وصف_ڪريو GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_ANGLE 0x8D56
#وصف_ڪريو GL_MAX_SAMPLES_ANGLE              0x8D57
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEANGLEPROC) (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glRenderbufferStorageMultisampleANGLE (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_ANGLE_framebuffer_multisample */

#جيڪڏهن_وصف_نه_ٿيل GL_ANGLE_instanced_arrays
#وصف_ڪريو GL_ANGLE_instanced_arrays 1
#وصف_ڪريو GL_راس_ATTRIB_ARRAY_ورهائيندڙ_ANGLE 0x88FE
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDANGLEPROC) (GLenum گهڻائي, GLint پهريون, GLsizei ڳڻپ, GLsizei primcount);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDANGLEPROC) (GLenum گهڻائي, GLsizei ڳڻپ, GLenum type, ثابت فراغ *indices, GLsizei primcount);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBDIVISORANGLEPROC) (GLuint اشاريو, GLuint ورهائيندڙ);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawArraysInstancedANGLE (GLenum گهڻائي, GLint پهريون, GLsizei ڳڻپ, GLsizei primcount);
GL_APICALL فراغ GL_APIENTRY glDrawElementsInstancedANGLE (GLenum گهڻائي, GLsizei ڳڻپ, GLenum type, ثابت فراغ *indices, GLsizei primcount);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib_ورهائيندڙ_ANGLE (GLuint اشاريو, GLuint ورهائيندڙ);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_ANGLE_instanced_arrays */

#جيڪڏهن_وصف_نه_ٿيل GL_ANGLE_pack_ابتو_صف_ترتيب
#وصف_ڪريو GL_ANGLE_pack_ابتو_صف_ترتيب 1
#وصف_ڪريو GL_PACK_ابتو_صف_ترتيب_ANGLE   0x93A4
#جيڪڏهن_پورو /* GL_ANGLE_pack_reverse_row_order */

#جيڪڏهن_وصف_نه_ٿيل GL_ANGLE_پروگرام_ٻٽو
#وصف_ڪريو GL_ANGLE_پروگرام_ٻٽو 1
#وصف_ڪريو GL_پروگرام_ٻٽو_ANGLE           0x93A6
#جيڪڏهن_پورو /* GL_ANGLE_program_binary */

#جيڪڏهن_وصف_نه_ٿيل GL_ANGLE_texture_compression_dxt3
#وصف_ڪريو GL_ANGLE_texture_compression_dxt3 1
#وصف_ڪريو GL_COMPRESSED_RGBA_S3TC_DXT3_ANGLE 0x83F2
#جيڪڏهن_پورو /* GL_ANGLE_texture_compression_dxt3 */

#جيڪڏهن_وصف_نه_ٿيل GL_ANGLE_texture_compression_dxt5
#وصف_ڪريو GL_ANGLE_texture_compression_dxt5 1
#وصف_ڪريو GL_COMPRESSED_RGBA_S3TC_DXT5_ANGLE 0x83F3
#جيڪڏهن_پورو /* GL_ANGLE_texture_compression_dxt5 */

#جيڪڏهن_وصف_نه_ٿيل GL_ANGLE_texture_usage
#وصف_ڪريو GL_ANGLE_texture_usage 1
#وصف_ڪريو GL_TEXTURE_USAGE_ANGLE            0x93A2
#وصف_ڪريو GL_FRAMEBUFFER_ATTACHMENT_ANGLE   0x93A3
#جيڪڏهن_پورو /* GL_ANGLE_texture_usage */

#جيڪڏهن_وصف_نه_ٿيل GL_ANGLE_translated_shader_ذريعو
#وصف_ڪريو GL_ANGLE_translated_shader_ذريعو 1
#وصف_ڪريو GL_TRANSLATED_SHADER_ذريعو_ڊيگهائي_ANGLE 0x93A0
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTRANSLATEDSHADERSOURCEANGLEPROC) (GLuint shader, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLchar *ذريعو);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Get_Translated_Shader_ذريعو_ANGLE (GLuint shader, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLchar *ذريعو);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_ANGLE_translated_shader_source */

#جيڪڏهن_وصف_نه_ٿيل GL_APPLE_clip_مفاصلو
#وصف_ڪريو GL_APPLE_clip_مفاصلو 1
#وصف_ڪريو GL_MAX_CLIP_DISTANCES_APPLE       0x0D32
#وصف_ڪريو GL_CLIP_DISTANCE0_APPLE           0x3000
#وصف_ڪريو GL_CLIP_DISTANCE1_APPLE           0x3001
#وصف_ڪريو GL_CLIP_DISTANCE2_APPLE           0x3002
#وصف_ڪريو GL_CLIP_DISTANCE3_APPLE           0x3003
#وصف_ڪريو GL_CLIP_DISTANCE4_APPLE           0x3004
#وصف_ڪريو GL_CLIP_DISTANCE5_APPLE           0x3005
#وصف_ڪريو GL_CLIP_DISTANCE6_APPLE           0x3006
#وصف_ڪريو GL_CLIP_DISTANCE7_APPLE           0x3007
#جيڪڏهن_پورو /* GL_APPLE_clip_distance */

#جيڪڏهن_وصف_نه_ٿيل GL_APPLE_color_بفر_packed_float
#وصف_ڪريو GL_APPLE_color_بفر_packed_float 1
#جيڪڏهن_پورو /* GL_APPLE_color_buffer_packed_float */

#جيڪڏهن_وصف_نه_ٿيل GL_APPLE_copy_texture_سطحون
#وصف_ڪريو GL_APPLE_copy_texture_سطحون 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYTEXTURELEVELSAPPLEPROC) (GLuint destinationTexture, GLuint ذريعو_Texture, GLint ذريعو_بنياد_Level, GLsizei ذريعو_Level_ڳڻپ);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Copy_Texture_سطحون_APPLE (GLuint destinationTexture, GLuint ذريعو_Texture, GLint ذريعو_بنياد_Level, GLsizei ذريعو_Level_ڳڻپ);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_APPLE_copy_texture_levels */

#جيڪڏهن_وصف_نه_ٿيل GL_APPLE_framebuffer_multisample
#وصف_ڪريو GL_APPLE_framebuffer_multisample 1
#وصف_ڪريو GL_RENDERBUFFER_SAMPLES_APPLE     0x8CAB
#وصف_ڪريو GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_APPLE 0x8D56
#وصف_ڪريو GL_MAX_SAMPLES_APPLE              0x8D57
#وصف_ڪريو GL_READ_FRAMEBUFFER_APPLE         0x8CA8
#وصف_ڪريو GL_DRAW_FRAMEBUFFER_APPLE         0x8CA9
#وصف_ڪريو GL_DRAW_FRAMEBUFFER_BINDING_APPLE 0x8CA6
#وصف_ڪريو GL_READ_FRAMEBUFFER_BINDING_APPLE 0x8CAA
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEAPPLEPROC) (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRESOLVEMULTISAMPLEFRAMEBUFFERAPPLEPROC) (فراغ);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glRenderbufferStorageMultisampleAPPLE (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
GL_APICALL فراغ GL_APIENTRY glResolveMultisampleFramebufferAPPLE (فراغ);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_APPLE_framebuffer_multisample */

#جيڪڏهن_وصف_نه_ٿيل GL_APPLE_rgb_422
#وصف_ڪريو GL_APPLE_rgb_422 1
#وصف_ڪريو GL_RGB_422_APPLE                  0x8A1F
#وصف_ڪريو GL_UNSIGNED_SHORT_8_8_APPLE       0x85BA
#وصف_ڪريو GL_UNSIGNED_SHORT_8_8_REV_APPLE   0x85BB
#وصف_ڪريو GL_RGB_RAW_422_APPLE              0x8A51
#جيڪڏهن_پورو /* GL_APPLE_rgb_422 */

#جيڪڏهن_وصف_نه_ٿيل GL_APPLE_sync
#وصف_ڪريو GL_APPLE_sync 1
#وصف_ڪريو GL_SYNC_OBJECT_APPLE              0x8A53
#وصف_ڪريو GL_MAX_SERVER_WAIT_TIMEOUT_APPLE  0x9111
#وصف_ڪريو GL_OBJECT_TYPE_APPLE              0x9112
#وصف_ڪريو GL_SYNC_CONDITION_APPLE           0x9113
#وصف_ڪريو GL_SYNC_حالت_APPLE              0x9114
#وصف_ڪريو GL_SYNC_FLAGS_APPLE               0x9115
#وصف_ڪريو GL_SYNC_FENCE_APPLE               0x9116
#وصف_ڪريو GL_SYNC_GPU_COMMANDS_COMPLETE_APPLE 0x9117
#وصف_ڪريو GL_UNSIGNALED_APPLE               0x9118
#وصف_ڪريو GL_SIGNALED_APPLE                 0x9119
#وصف_ڪريو GL_ALREADY_SIGNALED_APPLE         0x911A
#وصف_ڪريو GL_TIMEOUT_EXPIRED_APPLE          0x911B
#وصف_ڪريو GL_CONDITION_SATISFIED_APPLE      0x911C
#وصف_ڪريو GL_WAIT_FAILED_APPLE              0x911D
#وصف_ڪريو GL_SYNC_FLUSH_COMMANDS_ٻٽو_انگ_APPLE  0x00000001
#وصف_ڪريو GL_TIMEOUT_IGNORED_APPLE          0xFFFFFFFFFFFFFFFFull
تعريفنوع GLsync (GL_APIENTRYP PFNGLFENCESYNCAPPLEPROC) (GLenum condition, GLbitfield flags);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISSYNCAPPLEPROC) (GLsync sync);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETESYNCAPPLEPROC) (GLsync sync);
تعريفنوع GLenum (GL_APIENTRYP PFNGLCLIENTWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
تعريفنوع فراغ (GL_APIENTRYP PFNGLWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTEGER64VAPPLEPROC) (GLenum pname, GLint64 *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSYNCIVAPPLEPROC) (GLsync sync, GLenum pname, GLsizei ڳڻپ, GLsizei *ڊيگهائي, GLint *قدرون);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL GLsync GL_APIENTRY glFenceSyncAPPLE (GLenum condition, GLbitfield flags);
GL_APICALL GLboolean GL_APIENTRY glIsSyncAPPLE (GLsync sync);
GL_APICALL فراغ GL_APIENTRY glDeleteSyncAPPLE (GLsync sync);
GL_APICALL GLenum GL_APIENTRY glClientWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_APICALL فراغ GL_APIENTRY glWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_APICALL فراغ GL_APIENTRY glGetInteger64vAPPLE (GLenum pname, GLint64 *params);
GL_APICALL فراغ GL_APIENTRY glGetSyncivAPPLE (GLsync sync, GLenum pname, GLsizei ڳڻپ, GLsizei *ڊيگهائي, GLint *قدرون);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_APPLE_sync */

#جيڪڏهن_وصف_نه_ٿيل GL_APPLE_texture_format_BGRA8888
#وصف_ڪريو GL_APPLE_texture_format_BGRA8888 1
#وصف_ڪريو GL_BGRA_EXT                       0x80E1
#وصف_ڪريو GL_BGRA8_EXT                      0x93A1
#جيڪڏهن_پورو /* GL_APPLE_texture_format_BGRA8888 */

#جيڪڏهن_وصف_نه_ٿيل GL_APPLE_texture_max_level
#وصف_ڪريو GL_APPLE_texture_max_level 1
#وصف_ڪريو GL_TEXTURE_MAX_LEVEL_APPLE        0x813D
#جيڪڏهن_پورو /* GL_APPLE_texture_max_level */

#جيڪڏهن_وصف_نه_ٿيل GL_APPLE_texture_packed_float
#وصف_ڪريو GL_APPLE_texture_packed_float 1
#وصف_ڪريو GL_UNSIGNED_INT_10F_11F_11F_REV_APPLE 0x8C3B
#وصف_ڪريو GL_UNSIGNED_INT_5_9_9_9_REV_APPLE 0x8C3E
#وصف_ڪريو GL_R11F_G11F_B10F_APPLE           0x8C3A
#وصف_ڪريو GL_RGB9_E5_APPLE                  0x8C3D
#جيڪڏهن_پورو /* GL_APPLE_texture_packed_float */

#جيڪڏهن_وصف_نه_ٿيل GL_ARM_mali_پروگرام_ٻٽو
#وصف_ڪريو GL_ARM_mali_پروگرام_ٻٽو 1
#وصف_ڪريو GL_MALI_پروگرام_ٻٽو_ARM        0x8F61
#جيڪڏهن_پورو /* GL_ARM_mali_program_binary */

#جيڪڏهن_وصف_نه_ٿيل GL_ARM_mali_shader_ٻٽو
#وصف_ڪريو GL_ARM_mali_shader_ٻٽو 1
#وصف_ڪريو GL_MALI_SHADER_ٻٽو_ARM         0x8F60
#جيڪڏهن_پورو /* GL_ARM_mali_shader_binary */

#جيڪڏهن_وصف_نه_ٿيل GL_ARM_rgba8
#وصف_ڪريو GL_ARM_rgba8 1
#جيڪڏهن_پورو /* GL_ARM_rgba8 */

#جيڪڏهن_وصف_نه_ٿيل GL_ARM_shader_core_properties
#وصف_ڪريو GL_ARM_shader_core_properties 1
#وصف_ڪريو GL_SHADER_CORE_ڳڻپ_ARM          0x96F0
#وصف_ڪريو GL_SHADER_CORE_سرگرم_ڳڻپ_ARM   0x96F1
#وصف_ڪريو GL_SHADER_CORE_PRESENT_نقاب_ARM   0x96F2
#وصف_ڪريو GL_SHADER_CORE_MAX_WARP_ڳڻپ_ARM 0x96F3
#وصف_ڪريو GL_SHADER_CORE_PIXEL_شرح_ARM     0x96F4
#وصف_ڪريو GL_SHADER_CORE_TEXEL_شرح_ARM     0x96F5
#وصف_ڪريو GL_SHADER_CORE_FMA_شرح_ARM       0x96F6
تعريفنوع فراغ (GL_APIENTRYP PFNGLMAXACTIVESHADERCORESARMPROC) (GLuint ڳڻپ);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Max_سرگرم_Shader_Cores_ARM (GLuint ڳڻپ);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_ARM_shader_core_properties */

#جيڪڏهن_وصف_نه_ٿيل GL_ARM_shader_framebuffer_fetch
#وصف_ڪريو GL_ARM_shader_framebuffer_fetch 1
#وصف_ڪريو GL_FETCH_في_SAMPLE_ARM           0x8F65
#وصف_ڪريو GL_FRAGMENT_SHADER_FRAMEBUFFER_FETCH_MRT_ARM 0x8F66
#جيڪڏهن_پورو /* GL_ARM_shader_framebuffer_fetch */

#جيڪڏهن_وصف_نه_ٿيل GL_ARM_shader_framebuffer_fetch_اونهائي_stencil
#وصف_ڪريو GL_ARM_shader_framebuffer_fetch_اونهائي_stencil 1
#جيڪڏهن_پورو /* GL_ARM_shader_framebuffer_fetch_depth_stencil */

#جيڪڏهن_وصف_نه_ٿيل GL_ARM_texture_unnormalized_coordinates
#وصف_ڪريو GL_ARM_texture_unnormalized_coordinates 1
#وصف_ڪريو GL_TEXTURE_UNNORMALIZED_COORDINATES_ARM 0x8F6A
#جيڪڏهن_پورو /* GL_ARM_texture_unnormalized_coordinates */

#جيڪڏهن_وصف_نه_ٿيل GL_DMP_پروگرام_ٻٽو
#وصف_ڪريو GL_DMP_پروگرام_ٻٽو 1
#وصف_ڪريو GL_SMAPHS30_پروگرام_ٻٽو_DMP    0x9251
#وصف_ڪريو GL_SMAPHS_پروگرام_ٻٽو_DMP      0x9252
#وصف_ڪريو GL_DMP_پروگرام_ٻٽو_DMP         0x9253
#جيڪڏهن_پورو /* GL_DMP_program_binary */

#جيڪڏهن_وصف_نه_ٿيل GL_DMP_shader_ٻٽو
#وصف_ڪريو GL_DMP_shader_ٻٽو 1
#وصف_ڪريو GL_SHADER_ٻٽو_DMP              0x9250
#جيڪڏهن_پورو /* GL_DMP_shader_binary */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_EGL_image_array
#وصف_ڪريو GL_EXT_EGL_image_array 1
#جيڪڏهن_پورو /* GL_EXT_EGL_image_array */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_EGL_image_storage
#وصف_ڪريو GL_EXT_EGL_image_storage 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLEGLIMAGETARGETTEXSTORAGEEXTPROC) (GLenum هدف, GLeglImageOES image, ثابت GLint* attrib_list);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEGLIMAGETARGETTEXTURESTORAGEEXTPROC) (GLuint texture, GLeglImageOES image, ثابت GLint* attrib_list);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_EGLImage_هدف_Tex_Storage_EXT (GLenum هدف, GLeglImageOES image, ثابت GLint* attrib_list);
GL_APICALL فراغ GL_APIENTRY gl_EGLImage_هدف_Texture_Storage_EXT (GLuint texture, GLeglImageOES image, ثابت GLint* attrib_list);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_EGL_image_storage */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_EGL_image_storage_compression
#وصف_ڪريو GL_EXT_EGL_image_storage_compression 1
#وصف_ڪريو GL_SURFACE_COMPRESSION_EXT        0x96C0
#وصف_ڪريو GL_SURFACE_COMPRESSION_FIXED_شرح_NONE_EXT 0x96C1
#وصف_ڪريو GL_SURFACE_COMPRESSION_FIXED_شرح_DEFAULT_EXT 0x96C2
#جيڪڏهن_پورو /* GL_EXT_EGL_image_storage_compression */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_YUV_هدف
#وصف_ڪريو GL_EXT_YUV_هدف 1
#وصف_ڪريو GL_SAMPLER_EXTERNAL_2D_Y2Y_EXT    0x8BE7
#جيڪڏهن_پورو /* GL_EXT_YUV_target */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_بنياد_instance
#وصف_ڪريو GL_EXT_بنياد_instance 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEEXTPROC) (GLenum گهڻائي, GLint پهريون, GLsizei ڳڻپ, GLsizei instancecount, GLuint baseinstance);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEEXTPROC) (GLenum گهڻائي, GLsizei ڳڻپ, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLuint baseinstance);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEEXTPROC) (GLenum گهڻائي, GLsizei ڳڻپ, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Draw_Arrays_Instanced_بنياد_Instance_EXT (GLenum گهڻائي, GLint پهريون, GLsizei ڳڻپ, GLsizei instancecount, GLuint baseinstance);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Elements_Instanced_بنياد_Instance_EXT (GLenum گهڻائي, GLsizei ڳڻپ, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLuint baseinstance);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Elements_Instanced_بنياد_راس_بنياد_Instance_EXT (GLenum گهڻائي, GLsizei ڳڻپ, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_base_instance */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_blend_func_extended
#وصف_ڪريو GL_EXT_blend_func_extended 1
#وصف_ڪريو GL_SRC1_COLOR_EXT                 0x88F9
#وصف_ڪريو GL_SRC1_ALPHA_EXT                 0x8589
#وصف_ڪريو GL_ONE_MINUS_SRC1_COLOR_EXT       0x88FA
#وصف_ڪريو GL_ONE_MINUS_SRC1_ALPHA_EXT       0x88FB
#وصف_ڪريو GL_SRC_ALPHA_SATURATE_EXT         0x0308
#وصف_ڪريو GL_LOCATION_اشاريو_EXT             0x930F
#وصف_ڪريو GL_MAX_DUAL_ذريعو_DRAW_BUFFERS_EXT 0x88FC
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDFRAGDATALOCATIONINDEXEDEXTPROC) (GLuint پروگرام, GLuint color_عدد, GLuint اشاريو, ثابت GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDFRAGDATALOCATIONEXTPROC) (GLuint پروگرام, GLuint color, ثابت GLchar *name);
تعريفنوع GLint (GL_APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONINDEXEXTPROC) (GLuint پروگرام, GLenum پروگرام_Interface, ثابت GLchar *name);
تعريفنوع GLint (GL_APIENTRYP PFNGLGETFRAGDATAINDEXEXTPROC) (GLuint پروگرام, ثابت GLchar *name);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Bind_Frag_معلومات_Location_اشاريي_وارو_EXT (GLuint پروگرام, GLuint color_عدد, GLuint اشاريو, ثابت GLchar *name);
GL_APICALL فراغ GL_APIENTRY gl_Bind_Frag_معلومات_Location_EXT (GLuint پروگرام, GLuint color, ثابت GLchar *name);
GL_APICALL GLint GL_APIENTRY gl_Get_پروگرام_Resource_Location_اشاريو_EXT (GLuint پروگرام, GLenum پروگرام_Interface, ثابت GLchar *name);
GL_APICALL GLint GL_APIENTRY gl_Get_Frag_معلومات_اشاريو_EXT (GLuint پروگرام, ثابت GLchar *name);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_blend_func_extended */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_blend_minmax
#وصف_ڪريو GL_EXT_blend_minmax 1
#وصف_ڪريو GL_MIN_EXT                        0x8007
#وصف_ڪريو GL_MAX_EXT                        0x8008
#جيڪڏهن_پورو /* GL_EXT_blend_minmax */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_بفر_storage
#وصف_ڪريو GL_EXT_بفر_storage 1
#وصف_ڪريو GL_MAP_READ_ٻٽو_انگ                   0x0001
#وصف_ڪريو GL_MAP_WRITE_ٻٽو_انگ                  0x0002
#وصف_ڪريو GL_MAP_PERSISTENT_ٻٽو_انگ_EXT         0x0040
#وصف_ڪريو GL_MAP_COHERENT_ٻٽو_انگ_EXT           0x0080
#وصف_ڪريو GL_DYNAMIC_STORAGE_ٻٽو_انگ_EXT        0x0100
#وصف_ڪريو GL_CLIENT_STORAGE_ٻٽو_انگ_EXT         0x0200
#وصف_ڪريو GL_CLIENT_MAPPED_بفر_BARRIER_ٻٽو_انگ_EXT 0x00004000
#وصف_ڪريو GL_بفر_IMMUTABLE_STORAGE_EXT   0x821F
#وصف_ڪريو GL_بفر_STORAGE_FLAGS_EXT       0x8220
تعريفنوع فراغ (GL_APIENTRYP PFNGLBUFFERSTORAGEEXTPROC) (GLenum هدف, GLsizeiptr سائيز, ثابت فراغ *معلومات, GLbitfield flags);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_بفر_Storage_EXT (GLenum هدف, GLsizeiptr سائيز, ثابت فراغ *معلومات, GLbitfield flags);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_buffer_storage */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_clear_texture
#وصف_ڪريو GL_EXT_clear_texture 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARTEXIMAGEEXTPROC) (GLuint texture, GLint level, GLenum format, GLenum type, ثابت فراغ *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARTEXSUBIMAGEEXTPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLenum format, GLenum type, ثابت فراغ *معلومات);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glClearTexImageEXT (GLuint texture, GLint level, GLenum format, GLenum type, ثابت فراغ *معلومات);
GL_APICALL فراغ GL_APIENTRY glClearTexSubImageEXT (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLenum format, GLenum type, ثابت فراغ *معلومات);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_clear_texture */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_clip_control
#وصف_ڪريو GL_EXT_clip_control 1
#وصف_ڪريو GL_هيٺاهون_کاٻو_EXT                 0x8CA1
#وصف_ڪريو GL_مٿانهون_کاٻو_EXT                 0x8CA2
#وصف_ڪريو GL_NEGATIVE_ONE_منزل_ONE_EXT        0x935E
#وصف_ڪريو GL_ZERO_منزل_ONE_EXT                0x935F
#وصف_ڪريو GL_CLIP_ORIGIN_EXT                0x935C
#وصف_ڪريو GL_CLIP_اونهائي_گهڻائي_EXT            0x935D
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLIPCONTROLEXTPROC) (GLenum origin, GLenum اونهائي_2);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glClipControlEXT (GLenum origin, GLenum اونهائي_2);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_clip_control */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_clip_cull_مفاصلو
#وصف_ڪريو GL_EXT_clip_cull_مفاصلو 1
#وصف_ڪريو GL_MAX_CLIP_DISTANCES_EXT         0x0D32
#وصف_ڪريو GL_MAX_CULL_DISTANCES_EXT         0x82F9
#وصف_ڪريو GL_MAX_COMBINED_CLIP_AND_CULL_DISTANCES_EXT 0x82FA
#وصف_ڪريو GL_CLIP_DISTANCE0_EXT             0x3000
#وصف_ڪريو GL_CLIP_DISTANCE1_EXT             0x3001
#وصف_ڪريو GL_CLIP_DISTANCE2_EXT             0x3002
#وصف_ڪريو GL_CLIP_DISTANCE3_EXT             0x3003
#وصف_ڪريو GL_CLIP_DISTANCE4_EXT             0x3004
#وصف_ڪريو GL_CLIP_DISTANCE5_EXT             0x3005
#وصف_ڪريو GL_CLIP_DISTANCE6_EXT             0x3006
#وصف_ڪريو GL_CLIP_DISTANCE7_EXT             0x3007
#جيڪڏهن_پورو /* GL_EXT_clip_cull_distance */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_color_بفر_float
#وصف_ڪريو GL_EXT_color_بفر_float 1
#جيڪڏهن_پورو /* GL_EXT_color_buffer_float */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_color_بفر_half_float
#وصف_ڪريو GL_EXT_color_بفر_half_float 1
#وصف_ڪريو GL_RGBA16F_EXT                    0x881A
#وصف_ڪريو GL_RGB16F_EXT                     0x881B
#وصف_ڪريو GL_RG16F_EXT                      0x822F
#وصف_ڪريو GL_R16F_EXT                       0x822D
#وصف_ڪريو GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE_EXT 0x8211
#وصف_ڪريو GL_UNSIGNED_NORMALIZED_EXT        0x8C17
#جيڪڏهن_پورو /* GL_EXT_color_buffer_half_float */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_conservative_اونهائي
#وصف_ڪريو GL_EXT_conservative_اونهائي 1
#جيڪڏهن_پورو /* GL_EXT_conservative_depth */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_copy_image
#وصف_ڪريو GL_EXT_copy_image 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYIMAGESUBDATAEXTPROC) (GLuint srcName, GLenum src_هدف, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dst_هدف, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei src_ويڪر, GLsizei src_اوچائي, GLsizei src_اونهائي);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Copy_Image_Sub_معلومات_EXT (GLuint srcName, GLenum src_هدف, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dst_هدف, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei src_ويڪر, GLsizei src_اوچائي, GLsizei src_اونهائي);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_copy_image */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_debug_label
#وصف_ڪريو GL_EXT_debug_label 1
#وصف_ڪريو GL_پروگرام_PIPELINE_OBJECT_EXT    0x8A4F
#وصف_ڪريو GL_پروگرام_OBJECT_EXT             0x8B40
#وصف_ڪريو GL_SHADER_OBJECT_EXT              0x8B48
#وصف_ڪريو GL_بفر_OBJECT_EXT              0x9151
#وصف_ڪريو GL_QUERY_OBJECT_EXT               0x9153
#وصف_ڪريو GL_راس_ARRAY_OBJECT_EXT        0x9154
#وصف_ڪريو GL_TRANSFORM_FEEDBACK             0x8E22
تعريفنوع فراغ (GL_APIENTRYP PFNGLLABELOBJECTEXTPROC) (GLenum type, GLuint object, GLsizei ڊيگهائي, ثابت GLchar *label);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETOBJECTLABELEXTPROC) (GLenum type, GLuint object, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLchar *label);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glLabelObjectEXT (GLenum type, GLuint object, GLsizei ڊيگهائي, ثابت GLchar *label);
GL_APICALL فراغ GL_APIENTRY glGetObjectLabelEXT (GLenum type, GLuint object, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLchar *label);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_debug_label */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_debug_marker
#وصف_ڪريو GL_EXT_debug_marker 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLINSERTEVENTMARKEREXTPROC) (GLsizei ڊيگهائي, ثابت GLchar *marker);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPUSHGROUPMARKEREXTPROC) (GLsizei ڊيگهائي, ثابت GLchar *marker);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOPGROUPMARKEREXTPROC) (فراغ);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_وجهو_Event_Marker_EXT (GLsizei ڊيگهائي, ثابت GLchar *marker);
GL_APICALL فراغ GL_APIENTRY gl_ڌڪو_گروهه_Marker_EXT (GLsizei ڊيگهائي, ثابت GLchar *marker);
GL_APICALL فراغ GL_APIENTRY gl_ڪڍو_گروهه_Marker_EXT (فراغ);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_debug_marker */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_اونهائي_clamp
#وصف_ڪريو GL_EXT_اونهائي_clamp 1
#وصف_ڪريو GL_اونهائي_CLAMP_EXT                0x864F
#جيڪڏهن_پورو /* GL_EXT_depth_clamp */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_discard_framebuffer
#وصف_ڪريو GL_EXT_discard_framebuffer 1
#وصف_ڪريو GL_COLOR_EXT                      0x1800
#وصف_ڪريو GL_اونهائي_EXT                      0x1801
#وصف_ڪريو GL_STENCIL_EXT                    0x1802
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISCARDFRAMEBUFFEREXTPROC) (GLenum هدف, GLsizei انگ_Attachments, ثابت GLenum *attachments);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDiscardFramebufferEXT (GLenum هدف, GLsizei انگ_Attachments, ثابت GLenum *attachments);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_discard_framebuffer */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_disjoint_timer_query
#وصف_ڪريو GL_EXT_disjoint_timer_query 1
#وصف_ڪريو GL_QUERY_COUNTER_بٽ_EXT         0x8864
#وصف_ڪريو GL_CURRENT_QUERY_EXT              0x8865
#وصف_ڪريو GL_QUERY_نتيجو_EXT               0x8866
#وصف_ڪريو GL_QUERY_نتيجو_موجود_EXT     0x8867
#وصف_ڪريو GL_وقت_ELAPSED_EXT               0x88BF
#وصف_ڪريو GL_TIMESTAMP_EXT                  0x8E28
#وصف_ڪريو GL_GPU_DISJOINT_EXT               0x8FBB
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENQUERIESEXTPROC) (GLsizei n, GLuint *ids);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEQUERIESEXTPROC) (GLsizei n, ثابت GLuint *ids);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISQUERYEXTPROC) (GLuint id);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBEGINQUERYEXTPROC) (GLenum هدف, GLuint id);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENDQUERYEXTPROC) (GLenum هدف);
تعريفنوع فراغ (GL_APIENTRYP PFNGLQUERYCOUNTEREXTPROC) (GLuint id, GLenum هدف);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETQUERYIVEXTPROC) (GLenum هدف, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETQUERYOBJECTIVEXTPROC) (GLuint id, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETQUERYOBJECTUIVEXTPROC) (GLuint id, GLenum pname, GLuint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETQUERYOBJECTI64VEXTPROC) (GLuint id, GLenum pname, GLint64 *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETQUERYOBJECTUI64VEXTPROC) (GLuint id, GLenum pname, GLuint64 *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTEGER64VEXTPROC) (GLenum pname, GLint64 *معلومات);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glGenQueriesEXT (GLsizei n, GLuint *ids);
GL_APICALL فراغ GL_APIENTRY glDeleteQueriesEXT (GLsizei n, ثابت GLuint *ids);
GL_APICALL GLboolean GL_APIENTRY glIsQueryEXT (GLuint id);
GL_APICALL فراغ GL_APIENTRY glBeginQueryEXT (GLenum هدف, GLuint id);
GL_APICALL فراغ GL_APIENTRY gl_پڇاڙي_Query_EXT (GLenum هدف);
GL_APICALL فراغ GL_APIENTRY glQueryCounterEXT (GLuint id, GLenum هدف);
GL_APICALL فراغ GL_APIENTRY glGetQueryivEXT (GLenum هدف, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetQueryObjectivEXT (GLuint id, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetQueryObjectuivEXT (GLuint id, GLenum pname, GLuint *params);
GL_APICALL فراغ GL_APIENTRY glGetQueryObjecti64vEXT (GLuint id, GLenum pname, GLint64 *params);
GL_APICALL فراغ GL_APIENTRY glGetQueryObjectui64vEXT (GLuint id, GLenum pname, GLuint64 *params);
GL_APICALL فراغ GL_APIENTRY glGetInteger64vEXT (GLenum pname, GLint64 *معلومات);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_disjoint_timer_query */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_draw_buffers
#وصف_ڪريو GL_EXT_draw_buffers 1
#وصف_ڪريو GL_MAX_COLOR_ATTACHMENTS_EXT      0x8CDF
#وصف_ڪريو GL_MAX_DRAW_BUFFERS_EXT           0x8824
#وصف_ڪريو GL_DRAW_BUFFER0_EXT               0x8825
#وصف_ڪريو GL_DRAW_BUFFER1_EXT               0x8826
#وصف_ڪريو GL_DRAW_BUFFER2_EXT               0x8827
#وصف_ڪريو GL_DRAW_BUFFER3_EXT               0x8828
#وصف_ڪريو GL_DRAW_BUFFER4_EXT               0x8829
#وصف_ڪريو GL_DRAW_BUFFER5_EXT               0x882A
#وصف_ڪريو GL_DRAW_BUFFER6_EXT               0x882B
#وصف_ڪريو GL_DRAW_BUFFER7_EXT               0x882C
#وصف_ڪريو GL_DRAW_BUFFER8_EXT               0x882D
#وصف_ڪريو GL_DRAW_BUFFER9_EXT               0x882E
#وصف_ڪريو GL_DRAW_BUFFER10_EXT              0x882F
#وصف_ڪريو GL_DRAW_BUFFER11_EXT              0x8830
#وصف_ڪريو GL_DRAW_BUFFER12_EXT              0x8831
#وصف_ڪريو GL_DRAW_BUFFER13_EXT              0x8832
#وصف_ڪريو GL_DRAW_BUFFER14_EXT              0x8833
#وصف_ڪريو GL_DRAW_BUFFER15_EXT              0x8834
#وصف_ڪريو GL_COLOR_ATTACHMENT0_EXT          0x8CE0
#وصف_ڪريو GL_COLOR_ATTACHMENT1_EXT          0x8CE1
#وصف_ڪريو GL_COLOR_ATTACHMENT2_EXT          0x8CE2
#وصف_ڪريو GL_COLOR_ATTACHMENT3_EXT          0x8CE3
#وصف_ڪريو GL_COLOR_ATTACHMENT4_EXT          0x8CE4
#وصف_ڪريو GL_COLOR_ATTACHMENT5_EXT          0x8CE5
#وصف_ڪريو GL_COLOR_ATTACHMENT6_EXT          0x8CE6
#وصف_ڪريو GL_COLOR_ATTACHMENT7_EXT          0x8CE7
#وصف_ڪريو GL_COLOR_ATTACHMENT8_EXT          0x8CE8
#وصف_ڪريو GL_COLOR_ATTACHMENT9_EXT          0x8CE9
#وصف_ڪريو GL_COLOR_ATTACHMENT10_EXT         0x8CEA
#وصف_ڪريو GL_COLOR_ATTACHMENT11_EXT         0x8CEB
#وصف_ڪريو GL_COLOR_ATTACHMENT12_EXT         0x8CEC
#وصف_ڪريو GL_COLOR_ATTACHMENT13_EXT         0x8CED
#وصف_ڪريو GL_COLOR_ATTACHMENT14_EXT         0x8CEE
#وصف_ڪريو GL_COLOR_ATTACHMENT15_EXT         0x8CEF
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWBUFFERSEXTPROC) (GLsizei n, ثابت GLenum *bufs);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawBuffersEXT (GLsizei n, ثابت GLenum *bufs);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_draw_buffers */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_draw_buffers_اشاريي_وارو
#وصف_ڪريو GL_EXT_draw_buffers_اشاريي_وارو 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLENABLEIEXTPROC) (GLenum هدف, GLuint اشاريو);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISABLEIEXTPROC) (GLenum هدف, GLuint اشاريو);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONIEXTPROC) (GLuint buf, GLenum گهڻائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEIEXTPROC) (GLuint buf, GLenum گهڻائي_RGB, GLenum گهڻائي_Alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDFUNCIEXTPROC) (GLuint buf, GLenum src, GLenum dst);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEIEXTPROC) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOLORMASKIEXTPROC) (GLuint اشاريو, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISENABLEDIEXTPROC) (GLenum هدف, GLuint اشاريو);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glEnableiEXT (GLenum هدف, GLuint اشاريو);
GL_APICALL فراغ GL_APIENTRY glDisableiEXT (GLenum هدف, GLuint اشاريو);
GL_APICALL فراغ GL_APIENTRY glBlendEquationiEXT (GLuint buf, GLenum گهڻائي);
GL_APICALL فراغ GL_APIENTRY glBlendEquationSeparateiEXT (GLuint buf, GLenum گهڻائي_RGB, GLenum گهڻائي_Alpha);
GL_APICALL فراغ GL_APIENTRY glBlendFunciEXT (GLuint buf, GLenum src, GLenum dst);
GL_APICALL فراغ GL_APIENTRY glBlendFuncSeparateiEXT (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
GL_APICALL فراغ GL_APIENTRY glColorMaskiEXT (GLuint اشاريو, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
GL_APICALL GLboolean GL_APIENTRY glIsEnablediEXT (GLenum هدف, GLuint اشاريو);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_draw_buffers_indexed */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_draw_elements_بنياد_راس
#وصف_ڪريو GL_EXT_draw_elements_بنياد_راس 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSBASEVERTEXEXTPROC) (GLenum گهڻائي, GLsizei ڳڻپ, GLenum type, ثابت فراغ *indices, GLint basevertex);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWRANGEELEMENTSBASEVERTEXEXTPROC) (GLenum گهڻائي, GLuint شروعات, GLuint پڇاڙي, GLsizei ڳڻپ, GLenum type, ثابت فراغ *indices, GLint basevertex);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXEXTPROC) (GLenum گهڻائي, GLsizei ڳڻپ, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLint basevertex);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Draw_Elements_بنياد_راس_EXT (GLenum گهڻائي, GLsizei ڳڻپ, GLenum type, ثابت فراغ *indices, GLint basevertex);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Range_Elements_بنياد_راس_EXT (GLenum گهڻائي, GLuint شروعات, GLuint پڇاڙي, GLsizei ڳڻپ, GLenum type, ثابت فراغ *indices, GLint basevertex);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Elements_Instanced_بنياد_راس_EXT (GLenum گهڻائي, GLsizei ڳڻپ, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLint basevertex);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_draw_elements_base_vertex */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_draw_instanced
#وصف_ڪريو GL_EXT_draw_instanced 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDEXTPROC) (GLenum گهڻائي, GLint شروعات, GLsizei ڳڻپ, GLsizei primcount);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDEXTPROC) (GLenum گهڻائي, GLsizei ڳڻپ, GLenum type, ثابت فراغ *indices, GLsizei primcount);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawArraysInstancedEXT (GLenum گهڻائي, GLint شروعات, GLsizei ڳڻپ, GLsizei primcount);
GL_APICALL فراغ GL_APIENTRY glDrawElementsInstancedEXT (GLenum گهڻائي, GLsizei ڳڻپ, GLenum type, ثابت فراغ *indices, GLsizei primcount);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_draw_instanced */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_draw_transform_feedback
#وصف_ڪريو GL_EXT_draw_transform_feedback 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKEXTPROC) (GLenum گهڻائي, GLuint id);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDEXTPROC) (GLenum گهڻائي, GLuint id, GLsizei instancecount);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawTransformFeedbackEXT (GLenum گهڻائي, GLuint id);
GL_APICALL فراغ GL_APIENTRY glDrawTransformFeedbackInstancedEXT (GLenum گهڻائي, GLuint id, GLsizei instancecount);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_draw_transform_feedback */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_external_بفر
#وصف_ڪريو GL_EXT_external_بفر 1
تعريفنوع فراغ *GLegl_Client_بفر_EXT;
تعريفنوع فراغ (GL_APIENTRYP PFNGLBUFFERSTORAGEEXTERNALEXTPROC) (GLenum هدف, GLintptr وٿي_2, GLsizeiptr سائيز, GLegl_Client_بفر_EXT client_بفر, GLbitfield flags);
تعريفنوع فراغ (GL_APIENTRYP PFNGLNAMEDBUFFERSTORAGEEXTERNALEXTPROC) (GLuint بفر_2, GLintptr وٿي_2, GLsizeiptr سائيز, GLegl_Client_بفر_EXT client_بفر, GLbitfield flags);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_بفر_Storage_External_EXT (GLenum هدف, GLintptr وٿي_2, GLsizeiptr سائيز, GLegl_Client_بفر_EXT client_بفر, GLbitfield flags);
GL_APICALL فراغ GL_APIENTRY gl_Named_بفر_Storage_External_EXT (GLuint بفر_2, GLintptr وٿي_2, GLsizeiptr سائيز, GLegl_Client_بفر_EXT client_بفر, GLbitfield flags);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_external_buffer */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_float_blend
#وصف_ڪريو GL_EXT_float_blend 1
#جيڪڏهن_پورو /* GL_EXT_float_blend */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_fragment_shading_شرح
#وصف_ڪريو GL_EXT_fragment_shading_شرح 1
#وصف_ڪريو GL_SHADING_شرح_1_X1_PIXELS_EXT    0x96A6
#وصف_ڪريو GL_SHADING_شرح_1_X2_PIXELS_EXT    0x96A7
#وصف_ڪريو GL_SHADING_شرح_2_X1_PIXELS_EXT    0x96A8
#وصف_ڪريو GL_SHADING_شرح_2_X2_PIXELS_EXT    0x96A9
#وصف_ڪريو GL_SHADING_شرح_1_X4_PIXELS_EXT    0x96AA
#وصف_ڪريو GL_SHADING_شرح_4_X1_PIXELS_EXT    0x96AB
#وصف_ڪريو GL_SHADING_شرح_4_X2_PIXELS_EXT    0x96AC
#وصف_ڪريو GL_SHADING_شرح_2_X4_PIXELS_EXT    0x96AD
#وصف_ڪريو GL_SHADING_شرح_4_X4_PIXELS_EXT    0x96AE
#وصف_ڪريو GL_SHADING_شرح_EXT               0x96D0
#وصف_ڪريو GL_SHADING_شرح_ATTACHMENT_EXT    0x96D1
#وصف_ڪريو GL_FRAGMENT_SHADING_شرح_COMBINER_OP_KEEP_EXT 0x96D2
#وصف_ڪريو GL_FRAGMENT_SHADING_شرح_COMBINER_OP_REPLACE_EXT 0x96D3
#وصف_ڪريو GL_FRAGMENT_SHADING_شرح_COMBINER_OP_MIN_EXT 0x96D4
#وصف_ڪريو GL_FRAGMENT_SHADING_شرح_COMBINER_OP_MAX_EXT 0x96D5
#وصف_ڪريو GL_FRAGMENT_SHADING_شرح_COMBINER_OP_MUL_EXT 0x96D6
#وصف_ڪريو GL_MIN_FRAGMENT_SHADING_شرح_ATTACHMENT_TEXEL_ويڪر_EXT 0x96D7
#وصف_ڪريو GL_MAX_FRAGMENT_SHADING_شرح_ATTACHMENT_TEXEL_ويڪر_EXT 0x96D8
#وصف_ڪريو GL_MIN_FRAGMENT_SHADING_شرح_ATTACHMENT_TEXEL_اوچائي_EXT 0x96D9
#وصف_ڪريو GL_MAX_FRAGMENT_SHADING_شرح_ATTACHMENT_TEXEL_اوچائي_EXT 0x96DA
#وصف_ڪريو GL_MAX_FRAGMENT_SHADING_شرح_ATTACHMENT_TEXEL_ASPECT_تناسب_EXT 0x96DB
#وصف_ڪريو GL_MAX_FRAGMENT_SHADING_شرح_ATTACHMENT_LAYERS_EXT 0x96DC
#وصف_ڪريو GL_FRAGMENT_SHADING_شرح_WITH_SHADER_اونهائي_STENCIL_WRITES_SUPPORTED_EXT 0x96DD
#وصف_ڪريو GL_FRAGMENT_SHADING_شرح_WITH_SAMPLE_نقاب_SUPPORTED_EXT 0x96DE
#وصف_ڪريو GL_FRAGMENT_SHADING_شرح_ATTACHMENT_WITH_DEFAULT_FRAMEBUFFER_SUPPORTED_EXT 0x96DF
#وصف_ڪريو GL_FRAGMENT_SHADING_شرح_NON_TRIVIAL_COMBINERS_SUPPORTED_EXT 0x8F6F
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFRAGMENTSHADINGRATESEXTPROC) (GLsizei samples, GLsizei max_ڳڻپ, GLsizei *ڳڻپ, GLenum *shadingRates);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADINGRATEEXTPROC) (GLenum شرح);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADINGRATECOMBINEROPSEXTPROC) (GLenum combinerOp0, GLenum combinerOp1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERSHADINGRATEEXTPROC) (GLenum هدف, GLenum attachment, GLuint texture, GLint بنياد_Layer, GLsizei انگ_Layers, GLsizei texel_ويڪر, GLsizei texel_اوچائي);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glGetFragmentShadingRatesEXT (GLsizei samples, GLsizei max_ڳڻپ, GLsizei *ڳڻپ, GLenum *shadingRates);
GL_APICALL فراغ GL_APIENTRY gl_Shading_شرح_EXT (GLenum شرح);
GL_APICALL فراغ GL_APIENTRY gl_Shading_شرح_Combiner_Ops_EXT (GLenum combinerOp0, GLenum combinerOp1);
GL_APICALL فراغ GL_APIENTRY gl_Framebuffer_Shading_شرح_EXT (GLenum هدف, GLenum attachment, GLuint texture, GLint بنياد_Layer, GLsizei انگ_Layers, GLsizei texel_ويڪر, GLsizei texel_اوچائي);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_fragment_shading_rate */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_framebuffer_blit_layers
#وصف_ڪريو GL_EXT_framebuffer_blit_layers 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLITFRAMEBUFFERLAYERSEXTPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield نقاب, GLenum filter);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLITFRAMEBUFFERLAYEREXTPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint srcLayer, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLint dstLayer, GLbitfield نقاب, GLenum filter);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glBlitFramebufferLayersEXT (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield نقاب, GLenum filter);
GL_APICALL فراغ GL_APIENTRY glBlitFramebufferLayerEXT (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint srcLayer, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLint dstLayer, GLbitfield نقاب, GLenum filter);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_framebuffer_blit_layers */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_geometry_نقطو_سائيز
#وصف_ڪريو GL_EXT_geometry_نقطو_سائيز 1
#جيڪڏهن_پورو /* GL_EXT_geometry_point_size */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_geometry_shader
#وصف_ڪريو GL_EXT_geometry_shader 1
#وصف_ڪريو GL_GEOMETRY_SHADER_EXT            0x8DD9
#وصف_ڪريو GL_GEOMETRY_SHADER_ٻٽو_انگ_EXT        0x00000004
#وصف_ڪريو GL_GEOMETRY_LINKED_VERTICES_ٻاهريون_EXT 0x8916
#وصف_ڪريو GL_GEOMETRY_LINKED_داخلا_TYPE_EXT 0x8917
#وصف_ڪريو GL_GEOMETRY_LINKED_OUTPUT_TYPE_EXT 0x8918
#وصف_ڪريو GL_GEOMETRY_SHADER_INVOCATIONS_EXT 0x887F
#وصف_ڪريو GL_LAYER_PROVOKING_راس_EXT     0x825E
#وصف_ڪريو GL_سٽون_ADJACENCY_EXT            0x000A
#وصف_ڪريو GL_سٽ_STRIP_ADJACENCY_EXT       0x000B
#وصف_ڪريو GL_TRIANGLES_ADJACENCY_EXT        0x000C
#وصف_ڪريو GL_TRIANGLE_STRIP_ADJACENCY_EXT   0x000D
#وصف_ڪريو GL_MAX_GEOMETRY_هڪجهڙو_COMPONENTS_EXT 0x8DDF
#وصف_ڪريو GL_MAX_GEOMETRY_هڪجهڙو_بلاڪون_EXT 0x8A2C
#وصف_ڪريو GL_MAX_COMBINED_GEOMETRY_هڪجهڙو_COMPONENTS_EXT 0x8A32
#وصف_ڪريو GL_MAX_GEOMETRY_داخلا_COMPONENTS_EXT 0x9123
#وصف_ڪريو GL_MAX_GEOMETRY_OUTPUT_COMPONENTS_EXT 0x9124
#وصف_ڪريو GL_MAX_GEOMETRY_OUTPUT_VERTICES_EXT 0x8DE0
#وصف_ڪريو GL_MAX_GEOMETRY_ڪل_OUTPUT_COMPONENTS_EXT 0x8DE1
#وصف_ڪريو GL_MAX_GEOMETRY_SHADER_INVOCATIONS_EXT 0x8E5A
#وصف_ڪريو GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_EXT 0x8C29
#وصف_ڪريو GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS_EXT 0x92CF
#وصف_ڪريو GL_MAX_GEOMETRY_ATOMIC_COUNTERS_EXT 0x92D5
#وصف_ڪريو GL_MAX_GEOMETRY_IMAGE_UNIFORMS_EXT 0x90CD
#وصف_ڪريو GL_MAX_GEOMETRY_SHADER_STORAGE_بلاڪون_EXT 0x90D7
#وصف_ڪريو GL_پهريون_راس_CONVENTION_EXT    0x8E4D
#وصف_ڪريو GL_آخري_راس_CONVENTION_EXT     0x8E4E
#وصف_ڪريو GL_UNDEFINED_راس_EXT           0x8260
#وصف_ڪريو GL_PRIMITIVES_GENERATED_EXT       0x8C87
#وصف_ڪريو GL_FRAMEBUFFER_DEFAULT_LAYERS_EXT 0x9312
#وصف_ڪريو GL_MAX_FRAMEBUFFER_LAYERS_EXT     0x9317
#وصف_ڪريو GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_EXT 0x8DA8
#وصف_ڪريو GL_FRAMEBUFFER_ATTACHMENT_LAYERED_EXT 0x8DA7
#وصف_ڪريو GL_REFERENCED_BY_GEOMETRY_SHADER_EXT 0x9309
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREEXTPROC) (GLenum هدف, GLenum attachment, GLuint texture, GLint level);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferTextureEXT (GLenum هدف, GLenum attachment, GLuint texture, GLint level);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_geometry_shader */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_gpu_shader5
#وصف_ڪريو GL_EXT_gpu_shader5 1
#جيڪڏهن_پورو /* GL_EXT_gpu_shader5 */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_instanced_arrays
#وصف_ڪريو GL_EXT_instanced_arrays 1
#وصف_ڪريو GL_راس_ATTRIB_ARRAY_ورهائيندڙ_EXT 0x88FE
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBDIVISOREXTPROC) (GLuint اشاريو, GLuint ورهائيندڙ);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib_ورهائيندڙ_EXT (GLuint اشاريو, GLuint ورهائيندڙ);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_instanced_arrays */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_map_بفر_range
#وصف_ڪريو GL_EXT_map_بفر_range 1
#وصف_ڪريو GL_MAP_READ_ٻٽو_انگ_EXT               0x0001
#وصف_ڪريو GL_MAP_WRITE_ٻٽو_انگ_EXT              0x0002
#وصف_ڪريو GL_MAP_INVALIDATE_RANGE_ٻٽو_انگ_EXT   0x0004
#وصف_ڪريو GL_MAP_INVALIDATE_بفر_ٻٽو_انگ_EXT  0x0008
#وصف_ڪريو GL_MAP_FLUSH_EXPLICIT_ٻٽو_انگ_EXT     0x0010
#وصف_ڪريو GL_MAP_UNSYNCHRONIZED_ٻٽو_انگ_EXT     0x0020
تعريفنوع فراغ *(GL_APIENTRYP PFNGLMAPBUFFERRANGEEXTPROC) (GLenum هدف, GLintptr وٿي_2, GLsizeiptr ڊيگهائي, GLbitfield access);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEEXTPROC) (GLenum هدف, GLintptr وٿي_2, GLsizeiptr ڊيگهائي);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ *GL_APIENTRY gl_Map_بفر_Range_EXT (GLenum هدف, GLintptr وٿي_2, GLsizeiptr ڊيگهائي, GLbitfield access);
GL_APICALL فراغ GL_APIENTRY gl_Flush_Mapped_بفر_Range_EXT (GLenum هدف, GLintptr وٿي_2, GLsizeiptr ڊيگهائي);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_map_buffer_range */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_يادگيري_object
#وصف_ڪريو GL_EXT_يادگيري_object 1
#وصف_ڪريو GL_TEXTURE_TILING_EXT             0x9580
#وصف_ڪريو GL_DEDICATED_يادگيري_OBJECT_EXT    0x9581
#وصف_ڪريو GL_PROTECTED_يادگيري_OBJECT_EXT    0x959B
#وصف_ڪريو GL_انگ_TILING_TYPES_EXT           0x9582
#وصف_ڪريو GL_TILING_TYPES_EXT               0x9583
#وصف_ڪريو GL_OPTIMAL_TILING_EXT             0x9584
#وصف_ڪريو GL_لڪيري_TILING_EXT              0x9585
#وصف_ڪريو GL_انگ_DEVICE_UUIDS_EXT           0x9596
#وصف_ڪريو GL_DEVICE_UUID_EXT                0x9597
#وصف_ڪريو GL_DRIVER_UUID_EXT                0x9598
#وصف_ڪريو GL_UUID_سائيز_EXT                  16
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETUNSIGNEDBYTEVEXTPROC) (GLenum pname, GLubyte *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETUNSIGNEDBYTEI_VEXTPROC) (GLenum هدف, GLuint اشاريو, GLubyte *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEMEMORYOBJECTSEXTPROC) (GLsizei n, ثابت GLuint *يادگيري_Objects);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISMEMORYOBJECTEXTPROC) (GLuint يادگيري_Object);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCREATEMEMORYOBJECTSEXTPROC) (GLsizei n, GLuint *يادگيري_Objects);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMEMORYOBJECTPARAMETERIVEXTPROC) (GLuint يادگيري_Object, GLenum pname, ثابت GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETMEMORYOBJECTPARAMETERIVEXTPROC) (GLuint يادگيري_Object, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGEMEM2DEXTPROC) (GLenum هدف, GLsizei سطحون, GLenum اندروني_Format, GLsizei ويڪر, GLsizei اوچائي, GLuint يادگيري, GLuint64 وٿي_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGEMEM2DMULTISAMPLEEXTPROC) (GLenum هدف, GLsizei samples, GLenum اندروني_Format, GLsizei ويڪر, GLsizei اوچائي, GLboolean fixedSampleLocations, GLuint يادگيري, GLuint64 وٿي_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGEMEM3DEXTPROC) (GLenum هدف, GLsizei سطحون, GLenum اندروني_Format, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLuint يادگيري, GLuint64 وٿي_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGEMEM3DMULTISAMPLEEXTPROC) (GLenum هدف, GLsizei samples, GLenum اندروني_Format, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLboolean fixedSampleLocations, GLuint يادگيري, GLuint64 وٿي_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBUFFERSTORAGEMEMEXTPROC) (GLenum هدف, GLsizeiptr سائيز, GLuint يادگيري, GLuint64 وٿي_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGEMEM2DEXTPROC) (GLuint texture, GLsizei سطحون, GLenum اندروني_Format, GLsizei ويڪر, GLsizei اوچائي, GLuint يادگيري, GLuint64 وٿي_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGEMEM2DMULTISAMPLEEXTPROC) (GLuint texture, GLsizei samples, GLenum اندروني_Format, GLsizei ويڪر, GLsizei اوچائي, GLboolean fixedSampleLocations, GLuint يادگيري, GLuint64 وٿي_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGEMEM3DEXTPROC) (GLuint texture, GLsizei سطحون, GLenum اندروني_Format, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLuint يادگيري, GLuint64 وٿي_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGEMEM3DMULTISAMPLEEXTPROC) (GLuint texture, GLsizei samples, GLenum اندروني_Format, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLboolean fixedSampleLocations, GLuint يادگيري, GLuint64 وٿي_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLNAMEDBUFFERSTORAGEMEMEXTPROC) (GLuint بفر_2, GLsizeiptr سائيز, GLuint يادگيري, GLuint64 وٿي_2);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glGetUnsignedBytevEXT (GLenum pname, GLubyte *معلومات);
GL_APICALL فراغ GL_APIENTRY glGetUnsignedBytei_vEXT (GLenum هدف, GLuint اشاريو, GLubyte *معلومات);
GL_APICALL فراغ GL_APIENTRY gl_Delete_يادگيري_Objects_EXT (GLsizei n, ثابت GLuint *يادگيري_Objects);
GL_APICALL GLboolean GL_APIENTRY gl_Is_يادگيري_Object_EXT (GLuint يادگيري_Object);
GL_APICALL فراغ GL_APIENTRY gl_Create_يادگيري_Objects_EXT (GLsizei n, GLuint *يادگيري_Objects);
GL_APICALL فراغ GL_APIENTRY gl_يادگيري_Object_Parameteriv_EXT (GLuint يادگيري_Object, GLenum pname, ثابت GLint *params);
GL_APICALL فراغ GL_APIENTRY gl_Get_يادگيري_Object_Parameteriv_EXT (GLuint يادگيري_Object, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glTexStorageMem2DEXT (GLenum هدف, GLsizei سطحون, GLenum اندروني_Format, GLsizei ويڪر, GLsizei اوچائي, GLuint يادگيري, GLuint64 وٿي_2);
GL_APICALL فراغ GL_APIENTRY glTexStorageMem2DMultisampleEXT (GLenum هدف, GLsizei samples, GLenum اندروني_Format, GLsizei ويڪر, GLsizei اوچائي, GLboolean fixedSampleLocations, GLuint يادگيري, GLuint64 وٿي_2);
GL_APICALL فراغ GL_APIENTRY glTexStorageMem3DEXT (GLenum هدف, GLsizei سطحون, GLenum اندروني_Format, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLuint يادگيري, GLuint64 وٿي_2);
GL_APICALL فراغ GL_APIENTRY glTexStorageMem3DMultisampleEXT (GLenum هدف, GLsizei samples, GLenum اندروني_Format, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLboolean fixedSampleLocations, GLuint يادگيري, GLuint64 وٿي_2);
GL_APICALL فراغ GL_APIENTRY gl_بفر_Storage_Mem_EXT (GLenum هدف, GLsizeiptr سائيز, GLuint يادگيري, GLuint64 وٿي_2);
GL_APICALL فراغ GL_APIENTRY glTextureStorageMem2DEXT (GLuint texture, GLsizei سطحون, GLenum اندروني_Format, GLsizei ويڪر, GLsizei اوچائي, GLuint يادگيري, GLuint64 وٿي_2);
GL_APICALL فراغ GL_APIENTRY glTextureStorageMem2DMultisampleEXT (GLuint texture, GLsizei samples, GLenum اندروني_Format, GLsizei ويڪر, GLsizei اوچائي, GLboolean fixedSampleLocations, GLuint يادگيري, GLuint64 وٿي_2);
GL_APICALL فراغ GL_APIENTRY glTextureStorageMem3DEXT (GLuint texture, GLsizei سطحون, GLenum اندروني_Format, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLuint يادگيري, GLuint64 وٿي_2);
GL_APICALL فراغ GL_APIENTRY glTextureStorageMem3DMultisampleEXT (GLuint texture, GLsizei samples, GLenum اندروني_Format, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLboolean fixedSampleLocations, GLuint يادگيري, GLuint64 وٿي_2);
GL_APICALL فراغ GL_APIENTRY gl_Named_بفر_Storage_Mem_EXT (GLuint بفر_2, GLsizeiptr سائيز, GLuint يادگيري, GLuint64 وٿي_2);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_memory_object */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_يادگيري_object_fd
#وصف_ڪريو GL_EXT_يادگيري_object_fd 1
#وصف_ڪريو GL_HANDLE_TYPE_OPAQUE_FD_EXT      0x9586
تعريفنوع فراغ (GL_APIENTRYP PFNGLIMPORTMEMORYFDEXTPROC) (GLuint يادگيري, GLuint64 سائيز, GLenum handleType, GLint fd);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Import_يادگيري_Fd_EXT (GLuint يادگيري, GLuint64 سائيز, GLenum handleType, GLint fd);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_memory_object_fd */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_يادگيري_object_win32
#وصف_ڪريو GL_EXT_يادگيري_object_win32 1
#وصف_ڪريو GL_HANDLE_TYPE_OPAQUE_WIN32_EXT   0x9587
#وصف_ڪريو GL_HANDLE_TYPE_OPAQUE_WIN32_KMT_EXT 0x9588
#وصف_ڪريو GL_DEVICE_LUID_EXT                0x9599
#وصف_ڪريو GL_DEVICE_ڳنڍ_نقاب_EXT           0x959A
#وصف_ڪريو GL_LUID_سائيز_EXT                  8
#وصف_ڪريو GL_HANDLE_TYPE_D3D12_TILEPOOL_EXT 0x9589
#وصف_ڪريو GL_HANDLE_TYPE_D3D12_RESOURCE_EXT 0x958A
#وصف_ڪريو GL_HANDLE_TYPE_D3D11_IMAGE_EXT    0x958B
#وصف_ڪريو GL_HANDLE_TYPE_D3D11_IMAGE_KMT_EXT 0x958C
تعريفنوع فراغ (GL_APIENTRYP PFNGLIMPORTMEMORYWIN32HANDLEEXTPROC) (GLuint يادگيري, GLuint64 سائيز, GLenum handleType, فراغ *handle);
تعريفنوع فراغ (GL_APIENTRYP PFNGLIMPORTMEMORYWIN32NAMEEXTPROC) (GLuint يادگيري, GLuint64 سائيز, GLenum handleType, ثابت فراغ *name);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Import_يادگيري_Win32_Handle_EXT (GLuint يادگيري, GLuint64 سائيز, GLenum handleType, فراغ *handle);
GL_APICALL فراغ GL_APIENTRY gl_Import_يادگيري_Win32_Name_EXT (GLuint يادگيري, GLuint64 سائيز, GLenum handleType, ثابت فراغ *name);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_memory_object_win32 */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_mesh_shader
#وصف_ڪريو GL_EXT_mesh_shader 1
#وصف_ڪريو GL_MESH_SHADER_EXT                0x9559
#وصف_ڪريو GL_TASK_SHADER_EXT                0x955A
#وصف_ڪريو GL_MAX_MESH_هڪجهڙو_بلاڪون_EXT    0x8E60
#وصف_ڪريو GL_MAX_MESH_TEXTURE_IMAGE_UNITS_EXT 0x8E61
#وصف_ڪريو GL_MAX_MESH_IMAGE_UNIFORMS_EXT    0x8E62
#وصف_ڪريو GL_MAX_MESH_هڪجهڙو_COMPONENTS_EXT 0x8E63
#وصف_ڪريو GL_MAX_MESH_ATOMIC_COUNTER_BUFFERS_EXT 0x8E64
#وصف_ڪريو GL_MAX_MESH_ATOMIC_COUNTERS_EXT   0x8E65
#وصف_ڪريو GL_MAX_MESH_SHADER_STORAGE_بلاڪون_EXT 0x8E66
#وصف_ڪريو GL_MAX_COMBINED_MESH_هڪجهڙو_COMPONENTS_EXT 0x8E67
#وصف_ڪريو GL_MAX_TASK_هڪجهڙو_بلاڪون_EXT    0x8E68
#وصف_ڪريو GL_MAX_TASK_TEXTURE_IMAGE_UNITS_EXT 0x8E69
#وصف_ڪريو GL_MAX_TASK_IMAGE_UNIFORMS_EXT    0x8E6A
#وصف_ڪريو GL_MAX_TASK_هڪجهڙو_COMPONENTS_EXT 0x8E6B
#وصف_ڪريو GL_MAX_TASK_ATOMIC_COUNTER_BUFFERS_EXT 0x8E6C
#وصف_ڪريو GL_MAX_TASK_ATOMIC_COUNTERS_EXT   0x8E6D
#وصف_ڪريو GL_MAX_TASK_SHADER_STORAGE_بلاڪون_EXT 0x8E6E
#وصف_ڪريو GL_MAX_COMBINED_TASK_هڪجهڙو_COMPONENTS_EXT 0x8E6F
#وصف_ڪريو GL_MAX_TASK_WORK_گروهه_ڪل_ڳڻپ_EXT 0x9740
#وصف_ڪريو GL_MAX_MESH_WORK_گروهه_ڪل_ڳڻپ_EXT 0x9741
#وصف_ڪريو GL_MAX_MESH_WORK_گروهه_INVOCATIONS_EXT 0x9757
#وصف_ڪريو GL_MAX_TASK_WORK_گروهه_INVOCATIONS_EXT 0x9759
#وصف_ڪريو GL_MAX_TASK_PAYLOAD_سائيز_EXT      0x9742
#وصف_ڪريو GL_MAX_TASK_SHARED_يادگيري_سائيز_EXT 0x9743
#وصف_ڪريو GL_MAX_MESH_SHARED_يادگيري_سائيز_EXT 0x9744
#وصف_ڪريو GL_MAX_TASK_PAYLOAD_AND_SHARED_يادگيري_سائيز_EXT 0x9745
#وصف_ڪريو GL_MAX_MESH_PAYLOAD_AND_SHARED_يادگيري_سائيز_EXT 0x9746
#وصف_ڪريو GL_MAX_MESH_OUTPUT_يادگيري_سائيز_EXT 0x9747
#وصف_ڪريو GL_MAX_MESH_PAYLOAD_AND_OUTPUT_يادگيري_سائيز_EXT 0x9748
#وصف_ڪريو GL_MAX_MESH_OUTPUT_VERTICES_EXT   0x9538
#وصف_ڪريو GL_MAX_MESH_OUTPUT_PRIMITIVES_EXT 0x9756
#وصف_ڪريو GL_MAX_MESH_OUTPUT_COMPONENTS_EXT 0x9749
#وصف_ڪريو GL_MAX_MESH_OUTPUT_LAYERS_EXT     0x974A
#وصف_ڪريو GL_MAX_MESH_MULTIVIEW_VIEW_ڳڻپ_EXT 0x9557
#وصف_ڪريو GL_MESH_OUTPUT_في_راس_GRANULARITY_EXT 0x92DF
#وصف_ڪريو GL_MESH_OUTPUT_في_PRIMITIVE_GRANULARITY_EXT 0x9543
#وصف_ڪريو GL_MAX_PREFERRED_TASK_WORK_گروهه_INVOCATIONS_EXT 0x974B
#وصف_ڪريو GL_MAX_PREFERRED_MESH_WORK_گروهه_INVOCATIONS_EXT 0x974C
#وصف_ڪريو GL_MESH_PREFERS_LOCAL_INVOCATION_راس_OUTPUT_EXT 0x974D
#وصف_ڪريو GL_MESH_PREFERS_LOCAL_INVOCATION_PRIMITIVE_OUTPUT_EXT 0x974E
#وصف_ڪريو GL_MESH_PREFERS_COMPACT_راس_OUTPUT_EXT 0x974F
#وصف_ڪريو GL_MESH_PREFERS_COMPACT_PRIMITIVE_OUTPUT_EXT 0x9750
#وصف_ڪريو GL_MAX_TASK_WORK_گروهه_ڳڻپ_EXT  0x9751
#وصف_ڪريو GL_MAX_MESH_WORK_گروهه_ڳڻپ_EXT  0x9752
#وصف_ڪريو GL_MAX_MESH_WORK_گروهه_سائيز_EXT   0x9758
#وصف_ڪريو GL_MAX_TASK_WORK_گروهه_سائيز_EXT   0x975A
#وصف_ڪريو GL_MESH_WORK_گروهه_سائيز_EXT       0x953E
#وصف_ڪريو GL_TASK_WORK_گروهه_سائيز_EXT       0x953F
#وصف_ڪريو GL_MESH_VERTICES_ٻاهريون_EXT          0x9579
#وصف_ڪريو GL_MESH_PRIMITIVES_ٻاهريون_EXT        0x957A
#وصف_ڪريو GL_MESH_OUTPUT_TYPE_EXT           0x957B
#وصف_ڪريو GL_هڪجهڙو_بلاڪ_REFERENCED_BY_MESH_SHADER_EXT 0x959C
#وصف_ڪريو GL_هڪجهڙو_بلاڪ_REFERENCED_BY_TASK_SHADER_EXT 0x959D
#وصف_ڪريو GL_REFERENCED_BY_MESH_SHADER_EXT  0x95A0
#وصف_ڪريو GL_REFERENCED_BY_TASK_SHADER_EXT  0x95A1
#وصف_ڪريو GL_TASK_SHADER_INVOCATIONS_EXT    0x9753
#وصف_ڪريو GL_MESH_SHADER_INVOCATIONS_EXT    0x9754
#وصف_ڪريو GL_MESH_PRIMITIVES_GENERATED_EXT  0x9755
#وصف_ڪريو GL_MESH_SHADER_ٻٽو_انگ_EXT            0x00000040
#وصف_ڪريو GL_TASK_SHADER_ٻٽو_انگ_EXT            0x00000080
#وصف_ڪريو GL_MESH_SUBROUTINE_EXT            0x957C
#وصف_ڪريو GL_TASK_SUBROUTINE_EXT            0x957D
#وصف_ڪريو GL_MESH_SUBROUTINE_هڪجهڙو_EXT    0x957E
#وصف_ڪريو GL_TASK_SUBROUTINE_هڪجهڙو_EXT    0x957F
#وصف_ڪريو GL_ATOMIC_COUNTER_بفر_REFERENCED_BY_MESH_SHADER_EXT 0x959E
#وصف_ڪريو GL_ATOMIC_COUNTER_بفر_REFERENCED_BY_TASK_SHADER_EXT 0x959F
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWMESHTASKSEXTPROC) (GLuint انگ_groups_x, GLuint انگ_groups_y, GLuint انگ_groups_z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWMESHTASKSINDIRECTEXTPROC) (GLintptr اڻسڌو);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWMESHTASKSINDIRECTEXTPROC) (GLintptr اڻسڌو, GLsizei drawcount, GLsizei stride);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTEXTPROC) (GLintptr اڻسڌو, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawMeshTasksEXT (GLuint انگ_groups_x, GLuint انگ_groups_y, GLuint انگ_groups_z);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Mesh_Tasks_اڻسڌو_EXT (GLintptr اڻسڌو);
GL_APICALL فراغ GL_APIENTRY gl_Multi_Draw_Mesh_Tasks_اڻسڌو_EXT (GLintptr اڻسڌو, GLsizei drawcount, GLsizei stride);
GL_APICALL فراغ GL_APIENTRY gl_Multi_Draw_Mesh_Tasks_اڻسڌو_ڳڻپ_EXT (GLintptr اڻسڌو, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_mesh_shader */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_multi_draw_arrays
#وصف_ڪريو GL_EXT_multi_draw_arrays 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWARRAYSEXTPROC) (GLenum گهڻائي, ثابت GLint *پهريون, ثابت GLsizei *ڳڻپ, GLsizei primcount);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSEXTPROC) (GLenum گهڻائي, ثابت GLsizei *ڳڻپ, GLenum type, ثابت فراغ *ثابت*indices, GLsizei primcount);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glMultiDrawArraysEXT (GLenum گهڻائي, ثابت GLint *پهريون, ثابت GLsizei *ڳڻپ, GLsizei primcount);
GL_APICALL فراغ GL_APIENTRY glMultiDrawElementsEXT (GLenum گهڻائي, ثابت GLsizei *ڳڻپ, GLenum type, ثابت فراغ *ثابت*indices, GLsizei primcount);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_multi_draw_arrays */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_multi_draw_اڻسڌو
#وصف_ڪريو GL_EXT_multi_draw_اڻسڌو 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWARRAYSINDIRECTEXTPROC) (GLenum گهڻائي, ثابت فراغ *اڻسڌو, GLsizei drawcount, GLsizei stride);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSINDIRECTEXTPROC) (GLenum گهڻائي, GLenum type, ثابت فراغ *اڻسڌو, GLsizei drawcount, GLsizei stride);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Multi_Draw_Arrays_اڻسڌو_EXT (GLenum گهڻائي, ثابت فراغ *اڻسڌو, GLsizei drawcount, GLsizei stride);
GL_APICALL فراغ GL_APIENTRY gl_Multi_Draw_Elements_اڻسڌو_EXT (GLenum گهڻائي, GLenum type, ثابت فراغ *اڻسڌو, GLsizei drawcount, GLsizei stride);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_multi_draw_indirect */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_multisampled_compatibility
#وصف_ڪريو GL_EXT_multisampled_compatibility 1
#وصف_ڪريو GL_MULTISAMPLE_EXT                0x809D
#وصف_ڪريو GL_SAMPLE_ALPHA_منزل_ONE_EXT        0x809F
#جيڪڏهن_پورو /* GL_EXT_multisampled_compatibility */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_multisampled_render_منزل_texture
#وصف_ڪريو GL_EXT_multisampled_render_منزل_texture 1
#وصف_ڪريو GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SAMPLES_EXT 0x8D6C
#وصف_ڪريو GL_RENDERBUFFER_SAMPLES_EXT       0x8CAB
#وصف_ڪريو GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT 0x8D56
#وصف_ڪريو GL_MAX_SAMPLES_EXT                0x8D57
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEEXTPROC) (GLenum هدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glRenderbufferStorageMultisampleEXT (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
GL_APICALL فراغ GL_APIENTRY glFramebufferTexture2DMultisampleEXT (GLenum هدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_multisampled_render_to_texture */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_multisampled_render_منزل_texture2
#وصف_ڪريو GL_EXT_multisampled_render_منزل_texture2 1
#جيڪڏهن_پورو /* GL_EXT_multisampled_render_to_texture2 */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_multiview_draw_buffers
#وصف_ڪريو GL_EXT_multiview_draw_buffers 1
#وصف_ڪريو GL_COLOR_ATTACHMENT_EXT           0x90F0
#وصف_ڪريو GL_MULTIVIEW_EXT                  0x90F1
#وصف_ڪريو GL_DRAW_بفر_EXT                0x0C01
#وصف_ڪريو GL_READ_بفر_EXT                0x0C02
#وصف_ڪريو GL_MAX_MULTIVIEW_BUFFERS_EXT      0x90F2
تعريفنوع فراغ (GL_APIENTRYP PFNGLREADBUFFERINDEXEDEXTPROC) (GLenum src, GLint اشاريو);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWBUFFERSINDEXEDEXTPROC) (GLint n, ثابت GLenum *location, ثابت GLint *indices);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTEGERI_VEXTPROC) (GLenum هدف, GLuint اشاريو, GLint *معلومات);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Read_بفر_اشاريي_وارو_EXT (GLenum src, GLint اشاريو);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Buffers_اشاريي_وارو_EXT (GLint n, ثابت GLenum *location, ثابت GLint *indices);
GL_APICALL فراغ GL_APIENTRY glGetIntegeri_vEXT (GLenum هدف, GLuint اشاريو, GLint *معلومات);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_multiview_draw_buffers */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_multiview_tessellation_geometry_shader
#وصف_ڪريو GL_EXT_multiview_tessellation_geometry_shader 1
#جيڪڏهن_پورو /* GL_EXT_multiview_tessellation_geometry_shader */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_multiview_texture_multisample
#وصف_ڪريو GL_EXT_multiview_texture_multisample 1
#جيڪڏهن_پورو /* GL_EXT_multiview_texture_multisample */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_multiview_timer_query
#وصف_ڪريو GL_EXT_multiview_timer_query 1
#جيڪڏهن_پورو /* GL_EXT_multiview_timer_query */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_occlusion_query_boolean
#وصف_ڪريو GL_EXT_occlusion_query_boolean 1
#وصف_ڪريو GL_ANY_SAMPLES_PASSED_EXT         0x8C2F
#وصف_ڪريو GL_ANY_SAMPLES_PASSED_CONSERVATIVE_EXT 0x8D6A
#جيڪڏهن_پورو /* GL_EXT_occlusion_query_boolean */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_polygon_وٿي_clamp
#وصف_ڪريو GL_EXT_polygon_وٿي_clamp 1
#وصف_ڪريو GL_POLYGON_وٿي_CLAMP_EXT       0x8E1B
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOLYGONOFFSETCLAMPEXTPROC) (GLfloat ضرب_ڪندڙ, GLfloat units, GLfloat clamp);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Polygon_وٿي_Clamp_EXT (GLfloat ضرب_ڪندڙ, GLfloat units, GLfloat clamp);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_polygon_offset_clamp */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_post_اونهائي_coverage
#وصف_ڪريو GL_EXT_post_اونهائي_coverage 1
#جيڪڏهن_پورو /* GL_EXT_post_depth_coverage */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_primitive_bounding_box
#وصف_ڪريو GL_EXT_primitive_bounding_box 1
#وصف_ڪريو GL_PRIMITIVE_BOUNDING_BOX_EXT     0x92BE
تعريفنوع فراغ (GL_APIENTRYP PFNGLPRIMITIVEBOUNDINGBOXEXTPROC) (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glPrimitiveBoundingBoxEXT (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_primitive_bounding_box */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_protected_textures
#وصف_ڪريو GL_EXT_protected_textures 1
#وصف_ڪريو GL_CONTEXT_FLAG_PROTECTED_CONTENT_ٻٽو_انگ_EXT 0x00000010
#وصف_ڪريو GL_TEXTURE_PROTECTED_EXT          0x8BFA
#جيڪڏهن_پورو /* GL_EXT_protected_textures */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_pvrtc_sRGB
#وصف_ڪريو GL_EXT_pvrtc_sRGB 1
#وصف_ڪريو GL_COMPRESSED_SRGB_PVRTC_2BPPV1_EXT 0x8A54
#وصف_ڪريو GL_COMPRESSED_SRGB_PVRTC_4BPPV1_EXT 0x8A55
#وصف_ڪريو GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV1_EXT 0x8A56
#وصف_ڪريو GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV1_EXT 0x8A57
#وصف_ڪريو GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV2_IMG 0x93F0
#وصف_ڪريو GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV2_IMG 0x93F1
#جيڪڏهن_پورو /* GL_EXT_pvrtc_sRGB */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_raster_multisample
#وصف_ڪريو GL_EXT_raster_multisample 1
#وصف_ڪريو GL_RASTER_MULTISAMPLE_EXT         0x9327
#وصف_ڪريو GL_RASTER_SAMPLES_EXT             0x9328
#وصف_ڪريو GL_MAX_RASTER_SAMPLES_EXT         0x9329
#وصف_ڪريو GL_RASTER_FIXED_SAMPLE_LOCATIONS_EXT 0x932A
#وصف_ڪريو GL_MULTISAMPLE_RASTERIZATION_ALLOWED_EXT 0x932B
#وصف_ڪريو GL_EFFECTIVE_RASTER_SAMPLES_EXT   0x932C
تعريفنوع فراغ (GL_APIENTRYP PFNGLRASTERSAMPLESEXTPROC) (GLuint samples, GLboolean fixedsamplelocations);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glRasterSamplesEXT (GLuint samples, GLboolean fixedsamplelocations);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_raster_multisample */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_read_format_bgra
#وصف_ڪريو GL_EXT_read_format_bgra 1
#وصف_ڪريو GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT 0x8365
#وصف_ڪريو GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT 0x8366
#جيڪڏهن_پورو /* GL_EXT_read_format_bgra */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_render_snorm
#وصف_ڪريو GL_EXT_render_snorm 1
#وصف_ڪريو GL_R8_SNORM                       0x8F94
#وصف_ڪريو GL_RG8_SNORM                      0x8F95
#وصف_ڪريو GL_RGBA8_SNORM                    0x8F97
#وصف_ڪريو GL_R16_SNORM_EXT                  0x8F98
#وصف_ڪريو GL_RG16_SNORM_EXT                 0x8F99
#وصف_ڪريو GL_RGBA16_SNORM_EXT               0x8F9B
#جيڪڏهن_پورو /* GL_EXT_render_snorm */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_robustness
#وصف_ڪريو GL_EXT_robustness 1
#وصف_ڪريو GL_GUILTY_CONTEXT_RESET_EXT       0x8253
#وصف_ڪريو GL_INNOCENT_CONTEXT_RESET_EXT     0x8254
#وصف_ڪريو GL_UNKNOWN_CONTEXT_RESET_EXT      0x8255
#وصف_ڪريو GL_CONTEXT_ROBUST_ACCESS_EXT      0x90F3
#وصف_ڪريو GL_RESET_NOTIFICATION_STRATEGY_EXT 0x8256
#وصف_ڪريو GL_LOSE_CONTEXT_ON_RESET_EXT      0x8252
#وصف_ڪريو GL_NO_RESET_NOTIFICATION_EXT      0x8261
تعريفنوع GLenum (GL_APIENTRYP PFNGLGETGRAPHICSRESETSTATUSEXTPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLREADNPIXELSEXTPROC) (GLint x, GLint y, GLsizei ويڪر, GLsizei اوچائي, GLenum format, GLenum type, GLsizei buf_سائيز, فراغ *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNUNIFORMFVEXTPROC) (GLuint پروگرام, GLint location, GLsizei buf_سائيز, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNUNIFORMIVEXTPROC) (GLuint پروگرام, GLint location, GLsizei buf_سائيز, GLint *params);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL GLenum GL_APIENTRY gl_Get_Graphics_Reset_حالت_EXT (فراغ);
GL_APICALL فراغ GL_APIENTRY glReadnPixelsEXT (GLint x, GLint y, GLsizei ويڪر, GLsizei اوچائي, GLenum format, GLenum type, GLsizei buf_سائيز, فراغ *معلومات);
GL_APICALL فراغ GL_APIENTRY glGetnUniformfvEXT (GLuint پروگرام, GLint location, GLsizei buf_سائيز, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY glGetnUniformivEXT (GLuint پروگرام, GLint location, GLsizei buf_سائيز, GLint *params);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_robustness */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_sRGB
#وصف_ڪريو GL_EXT_sRGB 1
#وصف_ڪريو GL_SRGB_EXT                       0x8C40
#وصف_ڪريو GL_SRGB_ALPHA_EXT                 0x8C42
#وصف_ڪريو GL_SRGB8_ALPHA8_EXT               0x8C43
#وصف_ڪريو GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING_EXT 0x8210
#جيڪڏهن_پورو /* GL_EXT_sRGB */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_sRGB_write_control
#وصف_ڪريو GL_EXT_sRGB_write_control 1
#وصف_ڪريو GL_FRAMEBUFFER_SRGB_EXT           0x8DB9
#جيڪڏهن_پورو /* GL_EXT_sRGB_write_control */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_semaphore
#وصف_ڪريو GL_EXT_semaphore 1
#وصف_ڪريو GL_LAYOUT_GENERAL_EXT             0x958D
#وصف_ڪريو GL_LAYOUT_COLOR_ATTACHMENT_EXT    0x958E
#وصف_ڪريو GL_LAYOUT_اونهائي_STENCIL_ATTACHMENT_EXT 0x958F
#وصف_ڪريو GL_LAYOUT_اونهائي_STENCIL_READ_ONLY_EXT 0x9590
#وصف_ڪريو GL_LAYOUT_SHADER_READ_ONLY_EXT    0x9591
#وصف_ڪريو GL_LAYOUT_TRANSFER_SRC_EXT        0x9592
#وصف_ڪريو GL_LAYOUT_TRANSFER_DST_EXT        0x9593
#وصف_ڪريو GL_LAYOUT_اونهائي_READ_ONLY_STENCIL_ATTACHMENT_EXT 0x9530
#وصف_ڪريو GL_LAYOUT_اونهائي_ATTACHMENT_STENCIL_READ_ONLY_EXT 0x9531
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENSEMAPHORESEXTPROC) (GLsizei n, GLuint *semaphores);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETESEMAPHORESEXTPROC) (GLsizei n, ثابت GLuint *semaphores);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISSEMAPHOREEXTPROC) (GLuint semaphore);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSEMAPHOREPARAMETERUI64VEXTPROC) (GLuint semaphore, GLenum pname, ثابت GLuint64 *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSEMAPHOREPARAMETERUI64VEXTPROC) (GLuint semaphore, GLenum pname, GLuint64 *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLWAITSEMAPHOREEXTPROC) (GLuint semaphore, GLuint انگ_بفر_Barriers, ثابت GLuint *buffers, GLuint انگ_Texture_Barriers, ثابت GLuint *textures, ثابت GLenum *srcLayouts);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSIGNALSEMAPHOREEXTPROC) (GLuint semaphore, GLuint انگ_بفر_Barriers, ثابت GLuint *buffers, GLuint انگ_Texture_Barriers, ثابت GLuint *textures, ثابت GLenum *dstLayouts);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glGenSemaphoresEXT (GLsizei n, GLuint *semaphores);
GL_APICALL فراغ GL_APIENTRY glDeleteSemaphoresEXT (GLsizei n, ثابت GLuint *semaphores);
GL_APICALL GLboolean GL_APIENTRY glIsSemaphoreEXT (GLuint semaphore);
GL_APICALL فراغ GL_APIENTRY glSemaphoreParameterui64vEXT (GLuint semaphore, GLenum pname, ثابت GLuint64 *params);
GL_APICALL فراغ GL_APIENTRY glGetSemaphoreParameterui64vEXT (GLuint semaphore, GLenum pname, GLuint64 *params);
GL_APICALL فراغ GL_APIENTRY glWaitSemaphoreEXT (GLuint semaphore, GLuint انگ_بفر_Barriers, ثابت GLuint *buffers, GLuint انگ_Texture_Barriers, ثابت GLuint *textures, ثابت GLenum *srcLayouts);
GL_APICALL فراغ GL_APIENTRY glSignalSemaphoreEXT (GLuint semaphore, GLuint انگ_بفر_Barriers, ثابت GLuint *buffers, GLuint انگ_Texture_Barriers, ثابت GLuint *textures, ثابت GLenum *dstLayouts);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_semaphore */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_semaphore_fd
#وصف_ڪريو GL_EXT_semaphore_fd 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLIMPORTSEMAPHOREFDEXTPROC) (GLuint semaphore, GLenum handleType, GLint fd);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glImportSemaphoreFdEXT (GLuint semaphore, GLenum handleType, GLint fd);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_semaphore_fd */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_semaphore_win32
#وصف_ڪريو GL_EXT_semaphore_win32 1
#وصف_ڪريو GL_HANDLE_TYPE_D3D12_FENCE_EXT    0x9594
#وصف_ڪريو GL_D3_D12_FENCE_قدر_EXT          0x9595
تعريفنوع فراغ (GL_APIENTRYP PFNGLIMPORTSEMAPHOREWIN32HANDLEEXTPROC) (GLuint semaphore, GLenum handleType, فراغ *handle);
تعريفنوع فراغ (GL_APIENTRYP PFNGLIMPORTSEMAPHOREWIN32NAMEEXTPROC) (GLuint semaphore, GLenum handleType, ثابت فراغ *name);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glImportSemaphoreWin32HandleEXT (GLuint semaphore, GLenum handleType, فراغ *handle);
GL_APICALL فراغ GL_APIENTRY glImportSemaphoreWin32NameEXT (GLuint semaphore, GLenum handleType, ثابت فراغ *name);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_semaphore_win32 */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_separate_اونهائي_stencil
#وصف_ڪريو GL_EXT_separate_اونهائي_stencil 1
#جيڪڏهن_پورو /* GL_EXT_separate_depth_stencil */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_separate_shader_objects
#وصف_ڪريو GL_EXT_separate_shader_objects 1
#وصف_ڪريو GL_سرگرم_پروگرام_EXT             0x8259
#وصف_ڪريو GL_راس_SHADER_ٻٽو_انگ_EXT          0x00000001
#وصف_ڪريو GL_FRAGMENT_SHADER_ٻٽو_انگ_EXT        0x00000002
#وصف_ڪريو GL_ALL_SHADER_بٽ_EXT            0xFFFFFFFF
#وصف_ڪريو GL_پروگرام_SEPARABLE_EXT          0x8258
#وصف_ڪريو GL_پروگرام_PIPELINE_BINDING_EXT   0x825A
تعريفنوع فراغ (GL_APIENTRYP PFNGLACTIVESHADERPROGRAMEXTPROC) (GLuint pipeline, GLuint پروگرام);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDPROGRAMPIPELINEEXTPROC) (GLuint pipeline);
تعريفنوع GLuint (GL_APIENTRYP PFNGLCREATESHADERPROGRAMVEXTPROC) (GLenum type, GLsizei ڳڻپ, ثابت GLchar *ثابت*لڙيون);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEPROGRAMPIPELINESEXTPROC) (GLsizei n, ثابت GLuint *pipelines);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENPROGRAMPIPELINESEXTPROC) (GLsizei n, GLuint *pipelines);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMPIPELINEINFOLOGEXTPROC) (GLuint pipeline, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLchar *infoLog);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMPIPELINEIVEXTPROC) (GLuint pipeline, GLenum pname, GLint *params);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISPROGRAMPIPELINEEXTPROC) (GLuint pipeline);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMPARAMETERIEXTPROC) (GLuint پروگرام, GLenum pname, GLint قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1FEXTPROC) (GLuint پروگرام, GLint location, GLfloat v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1IEXTPROC) (GLuint پروگرام, GLint location, GLint v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1IVEXTPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2FEXTPROC) (GLuint پروگرام, GLint location, GLfloat v0, GLfloat v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2IEXTPROC) (GLuint پروگرام, GLint location, GLint v0, GLint v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2IVEXTPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3FEXTPROC) (GLuint پروگرام, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3IEXTPROC) (GLuint پروگرام, GLint location, GLint v0, GLint v1, GLint v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3IVEXTPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4FEXTPROC) (GLuint پروگرام, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4IEXTPROC) (GLuint پروگرام, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4IVEXTPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUSEPROGRAMSTAGESEXTPROC) (GLuint pipeline, GLbitfield stages, GLuint پروگرام);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVALIDATEPROGRAMPIPELINEEXTPROC) (GLuint pipeline);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UIEXTPROC) (GLuint پروگرام, GLint location, GLuint v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UIEXTPROC) (GLuint پروگرام, GLint location, GLuint v0, GLuint v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UIEXTPROC) (GLuint پروگرام, GLint location, GLuint v0, GLuint v1, GLuint v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UIEXTPROC) (GLuint پروگرام, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UIVEXTPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLuint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UIVEXTPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLuint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UIVEXTPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLuint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UIVEXTPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLuint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_سرگرم_Shader_پروگرام_EXT (GLuint pipeline, GLuint پروگرام);
GL_APICALL فراغ GL_APIENTRY gl_Bind_پروگرام_Pipeline_EXT (GLuint pipeline);
GL_APICALL GLuint GL_APIENTRY glCreateShaderProgramvEXT (GLenum type, GLsizei ڳڻپ, ثابت GLchar *ثابت*لڙيون);
GL_APICALL فراغ GL_APIENTRY gl_Delete_پروگرام_Pipelines_EXT (GLsizei n, ثابت GLuint *pipelines);
GL_APICALL فراغ GL_APIENTRY gl_Gen_پروگرام_Pipelines_EXT (GLsizei n, GLuint *pipelines);
GL_APICALL فراغ GL_APIENTRY gl_Get_پروگرام_Pipeline_Info_Log_EXT (GLuint pipeline, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLchar *infoLog);
GL_APICALL فراغ GL_APIENTRY gl_Get_پروگرام_Pipelineiv_EXT (GLuint pipeline, GLenum pname, GLint *params);
GL_APICALL GLboolean GL_APIENTRY gl_Is_پروگرام_Pipeline_EXT (GLuint pipeline);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Parameteri_EXT (GLuint پروگرام, GLenum pname, GLint قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform1f_EXT (GLuint پروگرام, GLint location, GLfloat v0);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform1fv_EXT (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform1i_EXT (GLuint پروگرام, GLint location, GLint v0);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform1iv_EXT (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLint *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform2f_EXT (GLuint پروگرام, GLint location, GLfloat v0, GLfloat v1);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform2fv_EXT (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform2i_EXT (GLuint پروگرام, GLint location, GLint v0, GLint v1);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform2iv_EXT (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLint *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform3f_EXT (GLuint پروگرام, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform3fv_EXT (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform3i_EXT (GLuint پروگرام, GLint location, GLint v0, GLint v1, GLint v2);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform3iv_EXT (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLint *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform4f_EXT (GLuint پروگرام, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform4fv_EXT (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform4i_EXT (GLuint پروگرام, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform4iv_EXT (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLint *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_هڪجهڙو_Matrix2fv_EXT (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_هڪجهڙو_Matrix3fv_EXT (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_هڪجهڙو_Matrix4fv_EXT (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_Use_پروگرام_Stages_EXT (GLuint pipeline, GLbitfield stages, GLuint پروگرام);
GL_APICALL فراغ GL_APIENTRY gl_Validate_پروگرام_Pipeline_EXT (GLuint pipeline);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform1ui_EXT (GLuint پروگرام, GLint location, GLuint v0);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform2ui_EXT (GLuint پروگرام, GLint location, GLuint v0, GLuint v1);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform3ui_EXT (GLuint پروگرام, GLint location, GLuint v0, GLuint v1, GLuint v2);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform4ui_EXT (GLuint پروگرام, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform1uiv_EXT (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLuint *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform2uiv_EXT (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLuint *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform3uiv_EXT (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLuint *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform4uiv_EXT (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLuint *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_هڪجهڙو_Matrix2x3fv_EXT (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_هڪجهڙو_Matrix3x2fv_EXT (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_هڪجهڙو_Matrix2x4fv_EXT (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_هڪجهڙو_Matrix4x2fv_EXT (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_هڪجهڙو_Matrix3x4fv_EXT (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_هڪجهڙو_Matrix4x3fv_EXT (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_separate_shader_objects */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_shader_framebuffer_fetch
#وصف_ڪريو GL_EXT_shader_framebuffer_fetch 1
#وصف_ڪريو GL_FRAGMENT_SHADER_DISCARDS_SAMPLES_EXT 0x8A52
#جيڪڏهن_پورو /* GL_EXT_shader_framebuffer_fetch */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_shader_framebuffer_fetch_non_coherent
#وصف_ڪريو GL_EXT_shader_framebuffer_fetch_non_coherent 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERFETCHBARRIEREXTPROC) (فراغ);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferFetchBarrierEXT (فراغ);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_shader_framebuffer_fetch_non_coherent */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_shader_گروهه_vote
#وصف_ڪريو GL_EXT_shader_گروهه_vote 1
#جيڪڏهن_پورو /* GL_EXT_shader_group_vote */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_shader_implicit_conversions
#وصف_ڪريو GL_EXT_shader_implicit_conversions 1
#جيڪڏهن_پورو /* GL_EXT_shader_implicit_conversions */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_shader_integer_mix
#وصف_ڪريو GL_EXT_shader_integer_mix 1
#جيڪڏهن_پورو /* GL_EXT_shader_integer_mix */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_shader_io_بلاڪون
#وصف_ڪريو GL_EXT_shader_io_بلاڪون 1
#جيڪڏهن_پورو /* GL_EXT_shader_io_blocks */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_shader_non_constant_global_initializers
#وصف_ڪريو GL_EXT_shader_non_constant_global_initializers 1
#جيڪڏهن_پورو /* GL_EXT_shader_non_constant_global_initializers */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_shader_pixel_local_storage
#وصف_ڪريو GL_EXT_shader_pixel_local_storage 1
#وصف_ڪريو GL_MAX_SHADER_PIXEL_LOCAL_STORAGE_FAST_سائيز_EXT 0x8F63
#وصف_ڪريو GL_MAX_SHADER_PIXEL_LOCAL_STORAGE_سائيز_EXT 0x8F67
#وصف_ڪريو GL_SHADER_PIXEL_LOCAL_STORAGE_EXT 0x8F64
#جيڪڏهن_پورو /* GL_EXT_shader_pixel_local_storage */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_shader_pixel_local_storage2
#وصف_ڪريو GL_EXT_shader_pixel_local_storage2 1
#وصف_ڪريو GL_MAX_SHADER_COMBINED_LOCAL_STORAGE_FAST_سائيز_EXT 0x9650
#وصف_ڪريو GL_MAX_SHADER_COMBINED_LOCAL_STORAGE_سائيز_EXT 0x9651
#وصف_ڪريو GL_FRAMEBUFFER_INCOMPLETE_INSUFFICIENT_SHADER_COMBINED_LOCAL_STORAGE_EXT 0x9652
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERPIXELLOCALSTORAGESIZEEXTPROC) (GLuint هدف, GLsizei سائيز);
تعريفنوع GLsizei (GL_APIENTRYP PFNGLGETFRAMEBUFFERPIXELLOCALSTORAGESIZEEXTPROC) (GLuint هدف);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARPIXELLOCALSTORAGEUIEXTPROC) (GLsizei وٿي_2, GLsizei n, ثابت GLuint *قدرون);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Framebuffer_Pixel_Local_Storage_سائيز_EXT (GLuint هدف, GLsizei سائيز);
GL_APICALL GLsizei GL_APIENTRY gl_Get_Framebuffer_Pixel_Local_Storage_سائيز_EXT (GLuint هدف);
GL_APICALL فراغ GL_APIENTRY glClearPixelLocalStorageuiEXT (GLsizei وٿي_2, GLsizei n, ثابت GLuint *قدرون);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_shader_pixel_local_storage2 */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_shader_samples_identical
#وصف_ڪريو GL_EXT_shader_samples_identical 1
#جيڪڏهن_پورو /* GL_EXT_shader_samples_identical */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_shader_texture_lod
#وصف_ڪريو GL_EXT_shader_texture_lod 1
#جيڪڏهن_پورو /* GL_EXT_shader_texture_lod */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_shader_texture_samples
#وصف_ڪريو GL_EXT_shader_texture_samples 1
#جيڪڏهن_پورو /* GL_EXT_shader_texture_samples */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_shadow_samplers
#وصف_ڪريو GL_EXT_shadow_samplers 1
#وصف_ڪريو GL_TEXTURE_COMPARE_گهڻائي_EXT       0x884C
#وصف_ڪريو GL_TEXTURE_COMPARE_FUNC_EXT       0x884D
#وصف_ڪريو GL_COMPARE_REF_منزل_TEXTURE_EXT     0x884E
#وصف_ڪريو GL_SAMPLER_2D_SHADOW_EXT          0x8B62
#جيڪڏهن_پورو /* GL_EXT_shadow_samplers */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_sparse_texture
#وصف_ڪريو GL_EXT_sparse_texture 1
#وصف_ڪريو GL_TEXTURE_SPARSE_EXT             0x91A6
#وصف_ڪريو GL_VIRTUAL_صفحو_سائيز_اشاريو_EXT    0x91A7
#وصف_ڪريو GL_انگ_SPARSE_سطحون_EXT          0x91AA
#وصف_ڪريو GL_انگ_VIRTUAL_صفحو_SIZES_EXT     0x91A8
#وصف_ڪريو GL_VIRTUAL_صفحو_سائيز_X_EXT        0x9195
#وصف_ڪريو GL_VIRTUAL_صفحو_سائيز_Y_EXT        0x9196
#وصف_ڪريو GL_VIRTUAL_صفحو_سائيز_Z_EXT        0x9197
#وصف_ڪريو GL_TEXTURE_2D_ARRAY               0x8C1A
#وصف_ڪريو GL_TEXTURE_3D                     0x806F
#وصف_ڪريو GL_MAX_SPARSE_TEXTURE_سائيز_EXT    0x9198
#وصف_ڪريو GL_MAX_SPARSE_3_D_TEXTURE_سائيز_EXT 0x9199
#وصف_ڪريو GL_MAX_SPARSE_ARRAY_TEXTURE_LAYERS_EXT 0x919A
#وصف_ڪريو GL_SPARSE_TEXTURE_ڀريل_ARRAY_CUBE_MIPMAPS_EXT 0x91A9
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPAGECOMMITMENTEXTPROC) (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLboolean commit);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Tex_صفحو_Commitment_EXT (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLboolean commit);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_sparse_texture */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_sparse_texture2
#وصف_ڪريو GL_EXT_sparse_texture2 1
#جيڪڏهن_پورو /* GL_EXT_sparse_texture2 */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_tessellation_نقطو_سائيز
#وصف_ڪريو GL_EXT_tessellation_نقطو_سائيز 1
#جيڪڏهن_پورو /* GL_EXT_tessellation_point_size */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_tessellation_shader
#وصف_ڪريو GL_EXT_tessellation_shader 1
#وصف_ڪريو GL_PATCHES_EXT                    0x000E
#وصف_ڪريو GL_PATCH_VERTICES_EXT             0x8E72
#وصف_ڪريو GL_TESS_CONTROL_OUTPUT_VERTICES_EXT 0x8E75
#وصف_ڪريو GL_TESS_GEN_گهڻائي_EXT              0x8E76
#وصف_ڪريو GL_TESS_GEN_SPACING_EXT           0x8E77
#وصف_ڪريو GL_TESS_GEN_راس_ترتيب_EXT      0x8E78
#وصف_ڪريو GL_TESS_GEN_نقطو_گهڻائي_EXT        0x8E79
#وصف_ڪريو GL_ISOLINES_EXT                   0x8E7A
#وصف_ڪريو GL_QUADS_EXT                      0x0007
#وصف_ڪريو GL_FRACTIONAL_ODD_EXT             0x8E7B
#وصف_ڪريو GL_FRACTIONAL_EVEN_EXT            0x8E7C
#وصف_ڪريو GL_MAX_PATCH_VERTICES_EXT         0x8E7D
#وصف_ڪريو GL_MAX_TESS_GEN_LEVEL_EXT         0x8E7E
#وصف_ڪريو GL_MAX_TESS_CONTROL_هڪجهڙو_COMPONENTS_EXT 0x8E7F
#وصف_ڪريو GL_MAX_TESS_EVALUATION_هڪجهڙو_COMPONENTS_EXT 0x8E80
#وصف_ڪريو GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS_EXT 0x8E81
#وصف_ڪريو GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS_EXT 0x8E82
#وصف_ڪريو GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS_EXT 0x8E83
#وصف_ڪريو GL_MAX_TESS_PATCH_COMPONENTS_EXT  0x8E84
#وصف_ڪريو GL_MAX_TESS_CONTROL_ڪل_OUTPUT_COMPONENTS_EXT 0x8E85
#وصف_ڪريو GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS_EXT 0x8E86
#وصف_ڪريو GL_MAX_TESS_CONTROL_هڪجهڙو_بلاڪون_EXT 0x8E89
#وصف_ڪريو GL_MAX_TESS_EVALUATION_هڪجهڙو_بلاڪون_EXT 0x8E8A
#وصف_ڪريو GL_MAX_TESS_CONTROL_داخلا_COMPONENTS_EXT 0x886C
#وصف_ڪريو GL_MAX_TESS_EVALUATION_داخلا_COMPONENTS_EXT 0x886D
#وصف_ڪريو GL_MAX_COMBINED_TESS_CONTROL_هڪجهڙو_COMPONENTS_EXT 0x8E1E
#وصف_ڪريو GL_MAX_COMBINED_TESS_EVALUATION_هڪجهڙو_COMPONENTS_EXT 0x8E1F
#وصف_ڪريو GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS_EXT 0x92CD
#وصف_ڪريو GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS_EXT 0x92CE
#وصف_ڪريو GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS_EXT 0x92D3
#وصف_ڪريو GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS_EXT 0x92D4
#وصف_ڪريو GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS_EXT 0x90CB
#وصف_ڪريو GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS_EXT 0x90CC
#وصف_ڪريو GL_MAX_TESS_CONTROL_SHADER_STORAGE_بلاڪون_EXT 0x90D8
#وصف_ڪريو GL_MAX_TESS_EVALUATION_SHADER_STORAGE_بلاڪون_EXT 0x90D9
#وصف_ڪريو GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED 0x8221
#وصف_ڪريو GL_IS_في_PATCH_EXT               0x92E7
#وصف_ڪريو GL_REFERENCED_BY_TESS_CONTROL_SHADER_EXT 0x9307
#وصف_ڪريو GL_REFERENCED_BY_TESS_EVALUATION_SHADER_EXT 0x9308
#وصف_ڪريو GL_TESS_CONTROL_SHADER_EXT        0x8E88
#وصف_ڪريو GL_TESS_EVALUATION_SHADER_EXT     0x8E87
#وصف_ڪريو GL_TESS_CONTROL_SHADER_ٻٽو_انگ_EXT    0x00000008
#وصف_ڪريو GL_TESS_EVALUATION_SHADER_ٻٽو_انگ_EXT 0x00000010
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATCHPARAMETERIEXTPROC) (GLenum pname, GLint قدر);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glPatchParameteriEXT (GLenum pname, GLint قدر);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_tessellation_shader */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_texture_border_clamp
#وصف_ڪريو GL_EXT_texture_border_clamp 1
#وصف_ڪريو GL_TEXTURE_BORDER_COLOR_EXT       0x1004
#وصف_ڪريو GL_CLAMP_منزل_BORDER_EXT            0x812D
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERIIVEXTPROC) (GLenum هدف, GLenum pname, ثابت GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERIUIVEXTPROC) (GLenum هدف, GLenum pname, ثابت GLuint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXPARAMETERIIVEXTPROC) (GLenum هدف, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXPARAMETERIUIVEXTPROC) (GLenum هدف, GLenum pname, GLuint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIIVEXTPROC) (GLuint sampler, GLenum pname, ثابت GLint *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIUIVEXTPROC) (GLuint sampler, GLenum pname, ثابت GLuint *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIIVEXTPROC) (GLuint sampler, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIUIVEXTPROC) (GLuint sampler, GLenum pname, GLuint *params);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTexParameterIivEXT (GLenum هدف, GLenum pname, ثابت GLint *params);
GL_APICALL فراغ GL_APIENTRY glTexParameterIuivEXT (GLenum هدف, GLenum pname, ثابت GLuint *params);
GL_APICALL فراغ GL_APIENTRY glGetTexParameterIivEXT (GLenum هدف, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetTexParameterIuivEXT (GLenum هدف, GLenum pname, GLuint *params);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterIivEXT (GLuint sampler, GLenum pname, ثابت GLint *param);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterIuivEXT (GLuint sampler, GLenum pname, ثابت GLuint *param);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameterIivEXT (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameterIuivEXT (GLuint sampler, GLenum pname, GLuint *params);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_texture_border_clamp */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_texture_بفر
#وصف_ڪريو GL_EXT_texture_بفر 1
#وصف_ڪريو GL_TEXTURE_بفر_EXT             0x8C2A
#وصف_ڪريو GL_TEXTURE_بفر_BINDING_EXT     0x8C2A
#وصف_ڪريو GL_MAX_TEXTURE_بفر_سائيز_EXT    0x8C2B
#وصف_ڪريو GL_TEXTURE_BINDING_بفر_EXT     0x8C2C
#وصف_ڪريو GL_TEXTURE_بفر_معلومات_STORE_BINDING_EXT 0x8C2D
#وصف_ڪريو GL_TEXTURE_بفر_وٿي_ALIGNMENT_EXT 0x919F
#وصف_ڪريو GL_SAMPLER_بفر_EXT             0x8DC2
#وصف_ڪريو GL_INT_SAMPLER_بفر_EXT         0x8DD0
#وصف_ڪريو GL_UNSIGNED_INT_SAMPLER_بفر_EXT 0x8DD8
#وصف_ڪريو GL_IMAGE_بفر_EXT               0x9051
#وصف_ڪريو GL_INT_IMAGE_بفر_EXT           0x905C
#وصف_ڪريو GL_UNSIGNED_INT_IMAGE_بفر_EXT  0x9067
#وصف_ڪريو GL_TEXTURE_بفر_وٿي_EXT      0x919D
#وصف_ڪريو GL_TEXTURE_بفر_سائيز_EXT        0x919E
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXBUFFEREXTPROC) (GLenum هدف, GLenum internalformat, GLuint بفر_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXBUFFERRANGEEXTPROC) (GLenum هدف, GLenum internalformat, GLuint بفر_2, GLintptr وٿي_2, GLsizeiptr سائيز);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Tex_بفر_EXT (GLenum هدف, GLenum internalformat, GLuint بفر_2);
GL_APICALL فراغ GL_APIENTRY gl_Tex_بفر_Range_EXT (GLenum هدف, GLenum internalformat, GLuint بفر_2, GLintptr وٿي_2, GLsizeiptr سائيز);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_texture_buffer */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_texture_compression_astc_decode_گهڻائي
#وصف_ڪريو GL_EXT_texture_compression_astc_decode_گهڻائي 1
#وصف_ڪريو GL_TEXTURE_ASTC_DECODE_PRECISION_EXT 0x8F69
#جيڪڏهن_پورو /* GL_EXT_texture_compression_astc_decode_mode */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_texture_compression_bptc
#وصف_ڪريو GL_EXT_texture_compression_bptc 1
#وصف_ڪريو GL_COMPRESSED_RGBA_BPTC_UNORM_EXT 0x8E8C
#وصف_ڪريو GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_EXT 0x8E8D
#وصف_ڪريو GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_EXT 0x8E8E
#وصف_ڪريو GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_EXT 0x8E8F
#جيڪڏهن_پورو /* GL_EXT_texture_compression_bptc */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_texture_compression_dxt1
#وصف_ڪريو GL_EXT_texture_compression_dxt1 1
#وصف_ڪريو GL_COMPRESSED_RGB_S3TC_DXT1_EXT   0x83F0
#وصف_ڪريو GL_COMPRESSED_RGBA_S3TC_DXT1_EXT  0x83F1
#جيڪڏهن_پورو /* GL_EXT_texture_compression_dxt1 */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_texture_compression_rgtc
#وصف_ڪريو GL_EXT_texture_compression_rgtc 1
#وصف_ڪريو GL_COMPRESSED_RED_RGTC1_EXT       0x8DBB
#وصف_ڪريو GL_COMPRESSED_SIGNED_RED_RGTC1_EXT 0x8DBC
#وصف_ڪريو GL_COMPRESSED_RED_GREEN_RGTC2_EXT 0x8DBD
#وصف_ڪريو GL_COMPRESSED_SIGNED_RED_GREEN_RGTC2_EXT 0x8DBE
#جيڪڏهن_پورو /* GL_EXT_texture_compression_rgtc */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_texture_compression_s3tc
#وصف_ڪريو GL_EXT_texture_compression_s3tc 1
#وصف_ڪريو GL_COMPRESSED_RGBA_S3TC_DXT3_EXT  0x83F2
#وصف_ڪريو GL_COMPRESSED_RGBA_S3TC_DXT5_EXT  0x83F3
#جيڪڏهن_پورو /* GL_EXT_texture_compression_s3tc */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_texture_compression_s3tc_srgb
#وصف_ڪريو GL_EXT_texture_compression_s3tc_srgb 1
#وصف_ڪريو GL_COMPRESSED_SRGB_S3TC_DXT1_EXT  0x8C4C
#وصف_ڪريو GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT 0x8C4D
#وصف_ڪريو GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT 0x8C4E
#وصف_ڪريو GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT 0x8C4F
#جيڪڏهن_پورو /* GL_EXT_texture_compression_s3tc_srgb */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_texture_cube_map_array
#وصف_ڪريو GL_EXT_texture_cube_map_array 1
#وصف_ڪريو GL_TEXTURE_CUBE_MAP_ARRAY_EXT     0x9009
#وصف_ڪريو GL_TEXTURE_BINDING_CUBE_MAP_ARRAY_EXT 0x900A
#وصف_ڪريو GL_SAMPLER_CUBE_MAP_ARRAY_EXT     0x900C
#وصف_ڪريو GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW_EXT 0x900D
#وصف_ڪريو GL_INT_SAMPLER_CUBE_MAP_ARRAY_EXT 0x900E
#وصف_ڪريو GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY_EXT 0x900F
#وصف_ڪريو GL_IMAGE_CUBE_MAP_ARRAY_EXT       0x9054
#وصف_ڪريو GL_INT_IMAGE_CUBE_MAP_ARRAY_EXT   0x905F
#وصف_ڪريو GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY_EXT 0x906A
#جيڪڏهن_پورو /* GL_EXT_texture_cube_map_array */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_texture_filter_anisotropic
#وصف_ڪريو GL_EXT_texture_filter_anisotropic 1
#وصف_ڪريو GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#وصف_ڪريو GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#جيڪڏهن_پورو /* GL_EXT_texture_filter_anisotropic */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_texture_filter_minmax
#وصف_ڪريو GL_EXT_texture_filter_minmax 1
#وصف_ڪريو GL_TEXTURE_REDUCTION_گهڻائي_EXT     0x9366
#وصف_ڪريو GL_WEIGHTED_اوسط_EXT           0x9367
#جيڪڏهن_پورو /* GL_EXT_texture_filter_minmax */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_texture_format_BGRA8888
#وصف_ڪريو GL_EXT_texture_format_BGRA8888 1
#جيڪڏهن_پورو /* GL_EXT_texture_format_BGRA8888 */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_texture_format_sRGB_override
#وصف_ڪريو GL_EXT_texture_format_sRGB_override 1
#وصف_ڪريو GL_TEXTURE_FORMAT_SRGB_OVERRIDE_EXT 0x8FBF
#جيڪڏهن_پورو /* GL_EXT_texture_format_sRGB_override */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_texture_mirror_clamp_منزل_ڪنارو
#وصف_ڪريو GL_EXT_texture_mirror_clamp_منزل_ڪنارو 1
#وصف_ڪريو GL_MIRROR_CLAMP_منزل_ڪنارو_EXT       0x8743
#جيڪڏهن_پورو /* GL_EXT_texture_mirror_clamp_to_edge */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_texture_norm16
#وصف_ڪريو GL_EXT_texture_norm16 1
#وصف_ڪريو GL_R16_EXT                        0x822A
#وصف_ڪريو GL_RG16_EXT                       0x822C
#وصف_ڪريو GL_RGBA16_EXT                     0x805B
#وصف_ڪريو GL_RGB16_EXT                      0x8054
#وصف_ڪريو GL_RGB16_SNORM_EXT                0x8F9A
#جيڪڏهن_پورو /* GL_EXT_texture_norm16 */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_texture_query_lod
#وصف_ڪريو GL_EXT_texture_query_lod 1
#جيڪڏهن_پورو /* GL_EXT_texture_query_lod */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_texture_rg
#وصف_ڪريو GL_EXT_texture_rg 1
#وصف_ڪريو GL_RED_EXT                        0x1903
#وصف_ڪريو GL_RG_EXT                         0x8227
#وصف_ڪريو GL_R8_EXT                         0x8229
#وصف_ڪريو GL_RG8_EXT                        0x822B
#جيڪڏهن_پورو /* GL_EXT_texture_rg */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_texture_sRGB_R8
#وصف_ڪريو GL_EXT_texture_sRGB_R8 1
#وصف_ڪريو GL_SR8_EXT                        0x8FBD
#جيڪڏهن_پورو /* GL_EXT_texture_sRGB_R8 */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_texture_sRGB_RG8
#وصف_ڪريو GL_EXT_texture_sRGB_RG8 1
#وصف_ڪريو GL_SRG8_EXT                       0x8FBE
#جيڪڏهن_پورو /* GL_EXT_texture_sRGB_RG8 */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_texture_sRGB_decode
#وصف_ڪريو GL_EXT_texture_sRGB_decode 1
#وصف_ڪريو GL_TEXTURE_SRGB_DECODE_EXT        0x8A48
#وصف_ڪريو GL_DECODE_EXT                     0x8A49
#وصف_ڪريو GL_SKIP_DECODE_EXT                0x8A4A
#جيڪڏهن_پورو /* GL_EXT_texture_sRGB_decode */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_texture_shadow_lod
#وصف_ڪريو GL_EXT_texture_shadow_lod 1
#جيڪڏهن_پورو /* GL_EXT_texture_shadow_lod */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_texture_storage
#وصف_ڪريو GL_EXT_texture_storage 1
#وصف_ڪريو GL_TEXTURE_IMMUTABLE_FORMAT_EXT   0x912F
#وصف_ڪريو GL_ALPHA8_EXT                     0x803C
#وصف_ڪريو GL_LUMINANCE8_EXT                 0x8040
#وصف_ڪريو GL_LUMINANCE8_ALPHA8_EXT          0x8045
#وصف_ڪريو GL_RGBA32F_EXT                    0x8814
#وصف_ڪريو GL_RGB32F_EXT                     0x8815
#وصف_ڪريو GL_ALPHA32F_EXT                   0x8816
#وصف_ڪريو GL_LUMINANCE32F_EXT               0x8818
#وصف_ڪريو GL_LUMINANCE_ALPHA32F_EXT         0x8819
#وصف_ڪريو GL_ALPHA16F_EXT                   0x881C
#وصف_ڪريو GL_LUMINANCE16F_EXT               0x881E
#وصف_ڪريو GL_LUMINANCE_ALPHA16F_EXT         0x881F
#وصف_ڪريو GL_R32F_EXT                       0x822E
#وصف_ڪريو GL_RG32F_EXT                      0x8230
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE1DEXTPROC) (GLenum هدف, GLsizei سطحون, GLenum internalformat, GLsizei ويڪر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE2DEXTPROC) (GLenum هدف, GLsizei سطحون, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE3DEXTPROC) (GLenum هدف, GLsizei سطحون, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGE1DEXTPROC) (GLuint texture, GLenum هدف, GLsizei سطحون, GLenum internalformat, GLsizei ويڪر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGE2DEXTPROC) (GLuint texture, GLenum هدف, GLsizei سطحون, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGE3DEXTPROC) (GLuint texture, GLenum هدف, GLsizei سطحون, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTexStorage1DEXT (GLenum هدف, GLsizei سطحون, GLenum internalformat, GLsizei ويڪر);
GL_APICALL فراغ GL_APIENTRY glTexStorage2DEXT (GLenum هدف, GLsizei سطحون, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
GL_APICALL فراغ GL_APIENTRY glTexStorage3DEXT (GLenum هدف, GLsizei سطحون, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2);
GL_APICALL فراغ GL_APIENTRY glTextureStorage1DEXT (GLuint texture, GLenum هدف, GLsizei سطحون, GLenum internalformat, GLsizei ويڪر);
GL_APICALL فراغ GL_APIENTRY glTextureStorage2DEXT (GLuint texture, GLenum هدف, GLsizei سطحون, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
GL_APICALL فراغ GL_APIENTRY glTextureStorage3DEXT (GLuint texture, GLenum هدف, GLsizei سطحون, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_texture_storage */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_texture_storage_compression
#وصف_ڪريو GL_EXT_texture_storage_compression 1
#وصف_ڪريو GL_انگ_SURFACE_COMPRESSION_FIXED_RATES_EXT 0x8F6E
#وصف_ڪريو GL_SURFACE_COMPRESSION_FIXED_شرح_1_BPC_EXT 0x96C4
#وصف_ڪريو GL_SURFACE_COMPRESSION_FIXED_شرح_2_BPC_EXT 0x96C5
#وصف_ڪريو GL_SURFACE_COMPRESSION_FIXED_شرح_3_BPC_EXT 0x96C6
#وصف_ڪريو GL_SURFACE_COMPRESSION_FIXED_شرح_4_BPC_EXT 0x96C7
#وصف_ڪريو GL_SURFACE_COMPRESSION_FIXED_شرح_5_BPC_EXT 0x96C8
#وصف_ڪريو GL_SURFACE_COMPRESSION_FIXED_شرح_6_BPC_EXT 0x96C9
#وصف_ڪريو GL_SURFACE_COMPRESSION_FIXED_شرح_7_BPC_EXT 0x96CA
#وصف_ڪريو GL_SURFACE_COMPRESSION_FIXED_شرح_8_BPC_EXT 0x96CB
#وصف_ڪريو GL_SURFACE_COMPRESSION_FIXED_شرح_9_BPC_EXT 0x96CC
#وصف_ڪريو GL_SURFACE_COMPRESSION_FIXED_شرح_10_BPC_EXT 0x96CD
#وصف_ڪريو GL_SURFACE_COMPRESSION_FIXED_شرح_11_BPC_EXT 0x96CE
#وصف_ڪريو GL_SURFACE_COMPRESSION_FIXED_شرح_12_BPC_EXT 0x96CF
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGEATTRIBS2DEXTPROC) (GLenum هدف, GLsizei سطحون, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي, ثابت GLint* attrib_list);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGEATTRIBS3DEXTPROC) (GLenum هدف, GLsizei سطحون, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, ثابت GLint* attrib_list);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTexStorageAttribs2DEXT (GLenum هدف, GLsizei سطحون, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي, ثابت GLint* attrib_list);
GL_APICALL فراغ GL_APIENTRY glTexStorageAttribs3DEXT (GLenum هدف, GLsizei سطحون, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, ثابت GLint* attrib_list);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_texture_storage_compression */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_texture_type_2_10_10_10_REV
#وصف_ڪريو GL_EXT_texture_type_2_10_10_10_REV 1
#وصف_ڪريو GL_UNSIGNED_INT_2_10_10_10_REV_EXT 0x8368
#جيڪڏهن_پورو /* GL_EXT_texture_type_2_10_10_10_REV */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_texture_view
#وصف_ڪريو GL_EXT_texture_view 1
#وصف_ڪريو GL_TEXTURE_VIEW_MIN_LEVEL_EXT     0x82DB
#وصف_ڪريو GL_TEXTURE_VIEW_انگ_سطحون_EXT    0x82DC
#وصف_ڪريو GL_TEXTURE_VIEW_MIN_LAYER_EXT     0x82DD
#وصف_ڪريو GL_TEXTURE_VIEW_انگ_LAYERS_EXT    0x82DE
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTUREVIEWEXTPROC) (GLuint texture, GLenum هدف, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTextureViewEXT (GLuint texture, GLenum هدف, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_texture_view */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_unpack_subimage
#وصف_ڪريو GL_EXT_unpack_subimage 1
#وصف_ڪريو GL_UNPACK_صف_ڊيگهائي_EXT          0x0CF2
#وصف_ڪريو GL_UNPACK_SKIP_صفون_EXT           0x0CF3
#وصف_ڪريو GL_UNPACK_SKIP_PIXELS_EXT         0x0CF4
#جيڪڏهن_پورو /* GL_EXT_unpack_subimage */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_win32_keyed_mutex
#وصف_ڪريو GL_EXT_win32_keyed_mutex 1
تعريفنوع GLboolean (GL_APIENTRYP PFNGLACQUIREKEYEDMUTEXWIN32EXTPROC) (GLuint يادگيري, GLuint64 ڪنجي, GLuint timeout);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLRELEASEKEYEDMUTEXWIN32EXTPROC) (GLuint يادگيري, GLuint64 ڪنجي);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL GLboolean GL_APIENTRY glAcquireKeyedMutexWin32EXT (GLuint يادگيري, GLuint64 ڪنجي, GLuint timeout);
GL_APICALL GLboolean GL_APIENTRY glReleaseKeyedMutexWin32EXT (GLuint يادگيري, GLuint64 ڪنجي);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_win32_keyed_mutex */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_دري_rectangles
#وصف_ڪريو GL_EXT_دري_rectangles 1
#وصف_ڪريو GL_INCLUSIVE_EXT                  0x8F10
#وصف_ڪريو GL_EXCLUSIVE_EXT                  0x8F11
#وصف_ڪريو GL_دري_RECTANGLE_EXT           0x8F12
#وصف_ڪريو GL_دري_RECTANGLE_گهڻائي_EXT      0x8F13
#وصف_ڪريو GL_MAX_دري_RECTANGLES_EXT      0x8F14
#وصف_ڪريو GL_انگ_دري_RECTANGLES_EXT      0x8F15
تعريفنوع فراغ (GL_APIENTRYP PFNGLWINDOWRECTANGLESEXTPROC) (GLenum گهڻائي, GLsizei ڳڻپ, ثابت GLint *box);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_دري_Rectangles_EXT (GLenum گهڻائي, GLsizei ڳڻپ, ثابت GLint *box);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_window_rectangles */

#جيڪڏهن_وصف_نه_ٿيل GL_FJ_shader_ٻٽو_GCCSO
#وصف_ڪريو GL_FJ_shader_ٻٽو_GCCSO 1
#وصف_ڪريو GL_GCCSO_SHADER_ٻٽو_FJ         0x9260
#جيڪڏهن_پورو /* GL_FJ_shader_binary_GCCSO */

#جيڪڏهن_وصف_نه_ٿيل GL_HUAWEI_پروگرام_ٻٽو
#وصف_ڪريو GL_HUAWEI_پروگرام_ٻٽو 1
#وصف_ڪريو GL_پروگرام_ٻٽو_HUAWEI          0x9771
#جيڪڏهن_پورو /* GL_HUAWEI_program_binary */

#جيڪڏهن_وصف_نه_ٿيل GL_HUAWEI_shader_ٻٽو
#وصف_ڪريو GL_HUAWEI_shader_ٻٽو 1
#وصف_ڪريو GL_SHADER_ٻٽو_HUAWEI           0x9770
#جيڪڏهن_پورو /* GL_HUAWEI_shader_binary */

#جيڪڏهن_وصف_نه_ٿيل GL_IMG_bindless_texture
#وصف_ڪريو GL_IMG_bindless_texture 1
تعريفنوع GLuint64 (GL_APIENTRYP PFNGLGETTEXTUREHANDLEIMGPROC) (GLuint texture);
تعريفنوع GLuint64 (GL_APIENTRYP PFNGLGETTEXTURESAMPLERHANDLEIMGPROC) (GLuint texture, GLuint sampler);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMHANDLEUI64IMGPROC) (GLint location, GLuint64 قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMHANDLEUI64VIMGPROC) (GLint location, GLsizei ڳڻپ, ثابت GLuint64 *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64IMGPROC) (GLuint پروگرام, GLint location, GLuint64 قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64VIMGPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLuint64 *قدرون);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL GLuint64 GL_APIENTRY glGetTextureHandleIMG (GLuint texture);
GL_APICALL GLuint64 GL_APIENTRY glGetTextureSamplerHandleIMG (GLuint texture, GLuint sampler);
GL_APICALL فراغ GL_APIENTRY gl_هڪجهڙو_Handleui64_IMG (GLint location, GLuint64 قدر);
GL_APICALL فراغ GL_APIENTRY gl_هڪجهڙو_Handleui64v_IMG (GLint location, GLsizei ڳڻپ, ثابت GLuint64 *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_هڪجهڙو_Handleui64_IMG (GLuint پروگرام, GLint location, GLuint64 قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_هڪجهڙو_Handleui64v_IMG (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLuint64 *قدرون);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_IMG_bindless_texture */

#جيڪڏهن_وصف_نه_ٿيل GL_IMG_framebuffer_downsample
#وصف_ڪريو GL_IMG_framebuffer_downsample 1
#وصف_ڪريو GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_AND_DOWNSAMPLE_IMG 0x913C
#وصف_ڪريو GL_انگ_DOWNSAMPLE_SCALES_IMG      0x913D
#وصف_ڪريو GL_DOWNSAMPLE_SCALES_IMG          0x913E
#وصف_ڪريو GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SCALE_IMG 0x913F
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DDOWNSAMPLEIMGPROC) (GLenum هدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint xscale, GLint yscale);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURELAYERDOWNSAMPLEIMGPROC) (GLenum هدف, GLenum attachment, GLuint texture, GLint level, GLint layer, GLint xscale, GLint yscale);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferTexture2DDownsampleIMG (GLenum هدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint xscale, GLint yscale);
GL_APICALL فراغ GL_APIENTRY glFramebufferTextureLayerDownsampleIMG (GLenum هدف, GLenum attachment, GLuint texture, GLint level, GLint layer, GLint xscale, GLint yscale);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_IMG_framebuffer_downsample */

#جيڪڏهن_وصف_نه_ٿيل GL_IMG_multisampled_render_منزل_texture
#وصف_ڪريو GL_IMG_multisampled_render_منزل_texture 1
#وصف_ڪريو GL_RENDERBUFFER_SAMPLES_IMG       0x9133
#وصف_ڪريو GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_IMG 0x9134
#وصف_ڪريو GL_MAX_SAMPLES_IMG                0x9135
#وصف_ڪريو GL_TEXTURE_SAMPLES_IMG            0x9136
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEIMGPROC) (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEIMGPROC) (GLenum هدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glRenderbufferStorageMultisampleIMG (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
GL_APICALL فراغ GL_APIENTRY glFramebufferTexture2DMultisampleIMG (GLenum هدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_IMG_multisampled_render_to_texture */

#جيڪڏهن_وصف_نه_ٿيل GL_IMG_پروگرام_ٻٽو
#وصف_ڪريو GL_IMG_پروگرام_ٻٽو 1
#وصف_ڪريو GL_SGX_پروگرام_ٻٽو_IMG         0x9130
#جيڪڏهن_پورو /* GL_IMG_program_binary */

#جيڪڏهن_وصف_نه_ٿيل GL_IMG_read_format
#وصف_ڪريو GL_IMG_read_format 1
#وصف_ڪريو GL_BGRA_IMG                       0x80E1
#وصف_ڪريو GL_UNSIGNED_SHORT_4_4_4_4_REV_IMG 0x8365
#جيڪڏهن_پورو /* GL_IMG_read_format */

#جيڪڏهن_وصف_نه_ٿيل GL_IMG_shader_ٻٽو
#وصف_ڪريو GL_IMG_shader_ٻٽو 1
#وصف_ڪريو GL_SGX_ٻٽو_IMG                 0x8C0A
#جيڪڏهن_پورو /* GL_IMG_shader_binary */

#جيڪڏهن_وصف_نه_ٿيل GL_IMG_texture_compression_pvrtc
#وصف_ڪريو GL_IMG_texture_compression_pvrtc 1
#وصف_ڪريو GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG 0x8C00
#وصف_ڪريو GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG 0x8C01
#وصف_ڪريو GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG 0x8C02
#وصف_ڪريو GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG 0x8C03
#جيڪڏهن_پورو /* GL_IMG_texture_compression_pvrtc */

#جيڪڏهن_وصف_نه_ٿيل GL_IMG_texture_compression_pvrtc2
#وصف_ڪريو GL_IMG_texture_compression_pvrtc2 1
#وصف_ڪريو GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG 0x9137
#وصف_ڪريو GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG 0x9138
#جيڪڏهن_پورو /* GL_IMG_texture_compression_pvrtc2 */

#جيڪڏهن_وصف_نه_ٿيل GL_IMG_texture_filter_cubic
#وصف_ڪريو GL_IMG_texture_filter_cubic 1
#وصف_ڪريو GL_CUBIC_IMG                      0x9139
#وصف_ڪريو GL_CUBIC_MIPMAP_سڀ_کان_ويجهو_IMG       0x913A
#وصف_ڪريو GL_CUBIC_MIPMAP_لڪيري_IMG        0x913B
#جيڪڏهن_پورو /* GL_IMG_texture_filter_cubic */

#جيڪڏهن_وصف_نه_ٿيل GL_INTEL_blackhole_render
#وصف_ڪريو GL_INTEL_blackhole_render 1
#وصف_ڪريو GL_BLACKHOLE_RENDER_INTEL         0x83FC
#جيڪڏهن_پورو /* GL_INTEL_blackhole_render */

#جيڪڏهن_وصف_نه_ٿيل GL_INTEL_conservative_rasterization
#وصف_ڪريو GL_INTEL_conservative_rasterization 1
#وصف_ڪريو GL_CONSERVATIVE_RASTERIZATION_INTEL 0x83FE
#جيڪڏهن_پورو /* GL_INTEL_conservative_rasterization */

#جيڪڏهن_وصف_نه_ٿيل GL_INTEL_framebuffer_CMAA
#وصف_ڪريو GL_INTEL_framebuffer_CMAA 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLAPPLYFRAMEBUFFERATTACHMENTCMAAINTELPROC) (فراغ);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glApplyFramebufferAttachmentCMAAINTEL (فراغ);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_INTEL_framebuffer_CMAA */

#جيڪڏهن_وصف_نه_ٿيل GL_INTEL_performance_query
#وصف_ڪريو GL_INTEL_performance_query 1
#وصف_ڪريو GL_PERFQUERY_SINGLE_CONTEXT_INTEL 0x00000000
#وصف_ڪريو GL_PERFQUERY_GLOBAL_CONTEXT_INTEL 0x00000001
#وصف_ڪريو GL_PERFQUERY_WAIT_INTEL           0x83FB
#وصف_ڪريو GL_PERFQUERY_FLUSH_INTEL          0x83FA
#وصف_ڪريو GL_PERFQUERY_DONOT_FLUSH_INTEL    0x83F9
#وصف_ڪريو GL_PERFQUERY_COUNTER_EVENT_INTEL  0x94F0
#وصف_ڪريو GL_PERFQUERY_COUNTER_DURATION_NORM_INTEL 0x94F1
#وصف_ڪريو GL_PERFQUERY_COUNTER_DURATION_RAW_INTEL 0x94F2
#وصف_ڪريو GL_PERFQUERY_COUNTER_THROUGHPUT_INTEL 0x94F3
#وصف_ڪريو GL_PERFQUERY_COUNTER_RAW_INTEL    0x94F4
#وصف_ڪريو GL_PERFQUERY_COUNTER_TIMESTAMP_INTEL 0x94F5
#وصف_ڪريو GL_PERFQUERY_COUNTER_معلومات_UINT32_INTEL 0x94F8
#وصف_ڪريو GL_PERFQUERY_COUNTER_معلومات_UINT64_INTEL 0x94F9
#وصف_ڪريو GL_PERFQUERY_COUNTER_معلومات_FLOAT_INTEL 0x94FA
#وصف_ڪريو GL_PERFQUERY_COUNTER_معلومات_DOUBLE_INTEL 0x94FB
#وصف_ڪريو GL_PERFQUERY_COUNTER_معلومات_BOOL32_INTEL 0x94FC
#وصف_ڪريو GL_PERFQUERY_QUERY_NAME_ڊيگهائي_MAX_INTEL 0x94FD
#وصف_ڪريو GL_PERFQUERY_COUNTER_NAME_ڊيگهائي_MAX_INTEL 0x94FE
#وصف_ڪريو GL_PERFQUERY_COUNTER_DESC_ڊيگهائي_MAX_INTEL 0x94FF
#وصف_ڪريو GL_PERFQUERY_GPA_EXTENDED_COUNTERS_INTEL 0x9500
تعريفنوع فراغ (GL_APIENTRYP PFNGLBEGINPERFQUERYINTELPROC) (GLuint queryHandle);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCREATEPERFQUERYINTELPROC) (GLuint queryId, GLuint *queryHandle);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEPERFQUERYINTELPROC) (GLuint queryHandle);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENDPERFQUERYINTELPROC) (GLuint queryHandle);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFIRSTPERFQUERYIDINTELPROC) (GLuint *queryId);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNEXTPERFQUERYIDINTELPROC) (GLuint queryId, GLuint *ايندڙ_Query_Id);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFCOUNTERINFOINTELPROC) (GLuint queryId, GLuint counterId, GLuint counter_Name_ڊيگهائي, GLchar *counterName, GLuint counter_Desc_ڊيگهائي, GLchar *counterDesc, GLuint *counter_وٿي, GLuint *counter_معلومات_سائيز, GLuint *counterTypeEnum, GLuint *counter_معلومات_Type_Enum, GLuint64 *raw_Counter_Max_قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFQUERYDATAINTELPROC) (GLuint queryHandle, GLuint flags, GLsizei معلومات_سائيز_2, فراغ *معلومات, GLuint *بائيٽون_Written);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFQUERYIDBYNAMEINTELPROC) (GLchar *queryName, GLuint *queryId);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFQUERYINFOINTELPROC) (GLuint queryId, GLuint query_Name_ڊيگهائي, GLchar *queryName, GLuint *معلومات_سائيز_2, GLuint *noCounters, GLuint *noInstances, GLuint *caps_نقاب);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glBeginPerfQueryINTEL (GLuint queryHandle);
GL_APICALL فراغ GL_APIENTRY glCreatePerfQueryINTEL (GLuint queryId, GLuint *queryHandle);
GL_APICALL فراغ GL_APIENTRY glDeletePerfQueryINTEL (GLuint queryHandle);
GL_APICALL فراغ GL_APIENTRY gl_پڇاڙي_Perf_Query_INTEL (GLuint queryHandle);
GL_APICALL فراغ GL_APIENTRY gl_Get_پهريون_Perf_Query_Id_INTEL (GLuint *queryId);
GL_APICALL فراغ GL_APIENTRY gl_Get_ايندڙ_Perf_Query_Id_INTEL (GLuint queryId, GLuint *ايندڙ_Query_Id);
GL_APICALL فراغ GL_APIENTRY glGetPerfCounterInfoINTEL (GLuint queryId, GLuint counterId, GLuint counter_Name_ڊيگهائي, GLchar *counterName, GLuint counter_Desc_ڊيگهائي, GLchar *counterDesc, GLuint *counter_وٿي, GLuint *counter_معلومات_سائيز, GLuint *counterTypeEnum, GLuint *counter_معلومات_Type_Enum, GLuint64 *raw_Counter_Max_قدر);
GL_APICALL فراغ GL_APIENTRY gl_Get_Perf_Query_معلومات_INTEL (GLuint queryHandle, GLuint flags, GLsizei معلومات_سائيز_2, فراغ *معلومات, GLuint *بائيٽون_Written);
GL_APICALL فراغ GL_APIENTRY glGetPerfQueryIdByNameINTEL (GLchar *queryName, GLuint *queryId);
GL_APICALL فراغ GL_APIENTRY glGetPerfQueryInfoINTEL (GLuint queryId, GLuint query_Name_ڊيگهائي, GLchar *queryName, GLuint *معلومات_سائيز_2, GLuint *noCounters, GLuint *noInstances, GLuint *caps_نقاب);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_INTEL_performance_query */

#جيڪڏهن_وصف_نه_ٿيل GL_MESA_bgra
#وصف_ڪريو GL_MESA_bgra 1
#وصف_ڪريو GL_BGR_EXT                        0x80E0
#جيڪڏهن_پورو /* GL_MESA_bgra */

#جيڪڏهن_وصف_نه_ٿيل GL_MESA_framebuffer_flip_x
#وصف_ڪريو GL_MESA_framebuffer_flip_x 1
#وصف_ڪريو GL_FRAMEBUFFER_FLIP_X_MESA        0x8BBC
#جيڪڏهن_پورو /* GL_MESA_framebuffer_flip_x */

#جيڪڏهن_وصف_نه_ٿيل GL_MESA_framebuffer_flip_y
#وصف_ڪريو GL_MESA_framebuffer_flip_y 1
#وصف_ڪريو GL_FRAMEBUFFER_FLIP_Y_MESA        0x8BBB
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERPARAMETERIMESAPROC) (GLenum هدف, GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFRAMEBUFFERPARAMETERIVMESAPROC) (GLenum هدف, GLenum pname, GLint *params);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferParameteriMESA (GLenum هدف, GLenum pname, GLint param);
GL_APICALL فراغ GL_APIENTRY glGetFramebufferParameterivMESA (GLenum هدف, GLenum pname, GLint *params);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_MESA_framebuffer_flip_y */

#جيڪڏهن_وصف_نه_ٿيل GL_MESA_framebuffer_مٽا_سٽا_xy
#وصف_ڪريو GL_MESA_framebuffer_مٽا_سٽا_xy 1
#وصف_ڪريو GL_FRAMEBUFFER_مٽا_سٽا_XY_MESA       0x8BBD
#جيڪڏهن_پورو /* GL_MESA_framebuffer_swap_xy */

#جيڪڏهن_وصف_نه_ٿيل GL_MESA_پروگرام_ٻٽو_formats
#وصف_ڪريو GL_MESA_پروگرام_ٻٽو_formats 1
#وصف_ڪريو GL_پروگرام_ٻٽو_FORMAT_MESA     0x875F
#جيڪڏهن_پورو /* GL_MESA_program_binary_formats */

#جيڪڏهن_وصف_نه_ٿيل GL_MESA_sampler_objects
#وصف_ڪريو GL_MESA_sampler_objects 1
#وصف_ڪريو GL_SAMPLER_BINDING                0x8919
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENSAMPLERSPROC) (GLsizei ڳڻپ, GLuint *samplers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETESAMPLERSPROC) (GLsizei ڳڻپ, ثابت GLuint *samplers);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISSAMPLERPROC) (GLuint sampler);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDSAMPLERPROC) (GLuint unit, GLuint sampler);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIPROC) (GLuint sampler, GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, ثابت GLint *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERFPROC) (GLuint sampler, GLenum pname, GLfloat param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, ثابت GLfloat *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, GLfloat *params);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glGenSamplers (GLsizei ڳڻپ, GLuint *samplers);
GL_APICALL فراغ GL_APIENTRY glDeleteSamplers (GLsizei ڳڻپ, ثابت GLuint *samplers);
GL_APICALL GLboolean GL_APIENTRY glIsSampler (GLuint sampler);
GL_APICALL فراغ GL_APIENTRY glBindSampler (GLuint unit, GLuint sampler);
GL_APICALL فراغ GL_APIENTRY glSamplerParameteri (GLuint sampler, GLenum pname, GLint param);
GL_APICALL فراغ GL_APIENTRY glSamplerParameteriv (GLuint sampler, GLenum pname, ثابت GLint *param);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterf (GLuint sampler, GLenum pname, GLfloat param);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterfv (GLuint sampler, GLenum pname, ثابت GLfloat *param);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameteriv (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameterfv (GLuint sampler, GLenum pname, GLfloat *params);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_MESA_sampler_objects */

#جيڪڏهن_وصف_نه_ٿيل GL_MESA_shader_integer_functions
#وصف_ڪريو GL_MESA_shader_integer_functions 1
#جيڪڏهن_پورو /* GL_MESA_shader_integer_functions */

#جيڪڏهن_وصف_نه_ٿيل GL_MESA_texture_const_bandwidth
#وصف_ڪريو GL_MESA_texture_const_bandwidth 1
#وصف_ڪريو GL_CONST_BW_TILING_MESA           0x8BBE
#جيڪڏهن_پورو /* GL_MESA_texture_const_bandwidth */

#جيڪڏهن_وصف_نه_ٿيل GL_NVX_blend_equation_advanced_multi_draw_buffers
#وصف_ڪريو GL_NVX_blend_equation_advanced_multi_draw_buffers 1
#جيڪڏهن_پورو /* GL_NVX_blend_equation_advanced_multi_draw_buffers */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_bindless_texture
#وصف_ڪريو GL_NV_bindless_texture 1
تعريفنوع GLuint64 (GL_APIENTRYP PFNGLGETTEXTUREHANDLENVPROC) (GLuint texture);
تعريفنوع GLuint64 (GL_APIENTRYP PFNGLGETTEXTURESAMPLERHANDLENVPROC) (GLuint texture, GLuint sampler);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMAKETEXTUREHANDLERESIDENTNVPROC) (GLuint64 handle);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMAKETEXTUREHANDLENONRESIDENTNVPROC) (GLuint64 handle);
تعريفنوع GLuint64 (GL_APIENTRYP PFNGLGETIMAGEHANDLENVPROC) (GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMAKEIMAGEHANDLERESIDENTNVPROC) (GLuint64 handle, GLenum access);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMAKEIMAGEHANDLENONRESIDENTNVPROC) (GLuint64 handle);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMHANDLEUI64NVPROC) (GLint location, GLuint64 قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMHANDLEUI64VNVPROC) (GLint location, GLsizei ڳڻپ, ثابت GLuint64 *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64NVPROC) (GLuint پروگرام, GLint location, GLuint64 قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64VNVPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLuint64 *قدرون);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISTEXTUREHANDLERESIDENTNVPROC) (GLuint64 handle);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISIMAGEHANDLERESIDENTNVPROC) (GLuint64 handle);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL GLuint64 GL_APIENTRY glGetTextureHandleNV (GLuint texture);
GL_APICALL GLuint64 GL_APIENTRY glGetTextureSamplerHandleNV (GLuint texture, GLuint sampler);
GL_APICALL فراغ GL_APIENTRY glMakeTextureHandleResidentNV (GLuint64 handle);
GL_APICALL فراغ GL_APIENTRY glMakeTextureHandleNonResidentNV (GLuint64 handle);
GL_APICALL GLuint64 GL_APIENTRY glGetImageHandleNV (GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format);
GL_APICALL فراغ GL_APIENTRY glMakeImageHandleResidentNV (GLuint64 handle, GLenum access);
GL_APICALL فراغ GL_APIENTRY glMakeImageHandleNonResidentNV (GLuint64 handle);
GL_APICALL فراغ GL_APIENTRY gl_هڪجهڙو_Handleui64_NV (GLint location, GLuint64 قدر);
GL_APICALL فراغ GL_APIENTRY gl_هڪجهڙو_Handleui64v_NV (GLint location, GLsizei ڳڻپ, ثابت GLuint64 *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_هڪجهڙو_Handleui64_NV (GLuint پروگرام, GLint location, GLuint64 قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_هڪجهڙو_Handleui64v_NV (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLuint64 *قدرون);
GL_APICALL GLboolean GL_APIENTRY glIsTextureHandleResidentNV (GLuint64 handle);
GL_APICALL GLboolean GL_APIENTRY glIsImageHandleResidentNV (GLuint64 handle);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_NV_bindless_texture */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_blend_equation_advanced
#وصف_ڪريو GL_NV_blend_equation_advanced 1
#وصف_ڪريو GL_BLEND_OVERLAP_NV               0x9281
#وصف_ڪريو GL_BLEND_PREMULTIPLIED_SRC_NV     0x9280
#وصف_ڪريو GL_BLUE_NV                        0x1905
#وصف_ڪريو GL_COLORBURN_NV                   0x929A
#وصف_ڪريو GL_COLORDODGE_NV                  0x9299
#وصف_ڪريو GL_CONJOINT_NV                    0x9284
#وصف_ڪريو GL_CONTRAST_NV                    0x92A1
#وصف_ڪريو GL_DARKEN_NV                      0x9297
#وصف_ڪريو GL_DIFFERENCE_NV                  0x929E
#وصف_ڪريو GL_DISJOINT_NV                    0x9283
#وصف_ڪريو GL_DST_ATOP_NV                    0x928F
#وصف_ڪريو GL_DST_اندريون_NV                      0x928B
#وصف_ڪريو GL_DST_NV                         0x9287
#وصف_ڪريو GL_DST_ٻاهريون_NV                     0x928D
#وصف_ڪريو GL_DST_OVER_NV                    0x9289
#وصف_ڪريو GL_EXCLUSION_NV                   0x92A0
#وصف_ڪريو GL_GREEN_NV                       0x1904
#وصف_ڪريو GL_HARDLIGHT_NV                   0x929B
#وصف_ڪريو GL_HARDMIX_NV                     0x92A9
#وصف_ڪريو GL_HSL_COLOR_NV                   0x92AF
#وصف_ڪريو GL_HSL_HUE_NV                     0x92AD
#وصف_ڪريو GL_HSL_LUMINOSITY_NV              0x92B0
#وصف_ڪريو GL_HSL_SATURATION_NV              0x92AE
#وصف_ڪريو GL_INVERT_OVG_NV                  0x92B4
#وصف_ڪريو GL_INVERT_RGB_NV                  0x92A3
#وصف_ڪريو GL_LIGHTEN_NV                     0x9298
#وصف_ڪريو GL_LINEARBURN_NV                  0x92A5
#وصف_ڪريو GL_LINEARDODGE_NV                 0x92A4
#وصف_ڪريو GL_LINEARLIGHT_NV                 0x92A7
#وصف_ڪريو GL_MINUS_CLAMPED_NV               0x92B3
#وصف_ڪريو GL_MINUS_NV                       0x929F
#وصف_ڪريو GL_MULTIPLY_NV                    0x9294
#وصف_ڪريو GL_OVERLAY_NV                     0x9296
#وصف_ڪريو GL_PINLIGHT_NV                    0x92A8
#وصف_ڪريو GL_PLUS_CLAMPED_ALPHA_NV          0x92B2
#وصف_ڪريو GL_PLUS_CLAMPED_NV                0x92B1
#وصف_ڪريو GL_PLUS_DARKER_NV                 0x9292
#وصف_ڪريو GL_PLUS_NV                        0x9291
#وصف_ڪريو GL_RED_NV                         0x1903
#وصف_ڪريو GL_SCREEN_NV                      0x9295
#وصف_ڪريو GL_SOFTLIGHT_NV                   0x929C
#وصف_ڪريو GL_SRC_ATOP_NV                    0x928E
#وصف_ڪريو GL_SRC_اندريون_NV                      0x928A
#وصف_ڪريو GL_SRC_NV                         0x9286
#وصف_ڪريو GL_SRC_ٻاهريون_NV                     0x928C
#وصف_ڪريو GL_SRC_OVER_NV                    0x9288
#وصف_ڪريو GL_UNCORRELATED_NV                0x9282
#وصف_ڪريو GL_VIVIDLIGHT_NV                  0x92A6
#وصف_ڪريو GL_XOR_NV                         0x1506
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDPARAMETERINVPROC) (GLenum pname, GLint قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDBARRIERNVPROC) (فراغ);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glBlendParameteriNV (GLenum pname, GLint قدر);
GL_APICALL فراغ GL_APIENTRY glBlendBarrierNV (فراغ);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_NV_blend_equation_advanced */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_blend_equation_advanced_coherent
#وصف_ڪريو GL_NV_blend_equation_advanced_coherent 1
#وصف_ڪريو GL_BLEND_ADVANCED_COHERENT_NV     0x9285
#جيڪڏهن_پورو /* GL_NV_blend_equation_advanced_coherent */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_blend_minmax_ضرب_ڪندڙ
#وصف_ڪريو GL_NV_blend_minmax_ضرب_ڪندڙ 1
#وصف_ڪريو GL_ضرب_ڪندڙ_MIN_AMD                 0x901C
#وصف_ڪريو GL_ضرب_ڪندڙ_MAX_AMD                 0x901D
#جيڪڏهن_پورو /* GL_NV_blend_minmax_factor */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_clip_space_w_scaling
#وصف_ڪريو GL_NV_clip_space_w_scaling 1
#وصف_ڪريو GL_VIEWPORT_POSITION_W_SCALE_NV   0x937C
#وصف_ڪريو GL_VIEWPORT_POSITION_W_SCALE_X_COEFF_NV 0x937D
#وصف_ڪريو GL_VIEWPORT_POSITION_W_SCALE_Y_COEFF_NV 0x937E
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTPOSITIONWSCALENVPROC) (GLuint اشاريو, GLfloat xcoeff, GLfloat ycoeff);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glViewportPositionWScaleNV (GLuint اشاريو, GLfloat xcoeff, GLfloat ycoeff);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_NV_clip_space_w_scaling */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_compute_shader_derivatives
#وصف_ڪريو GL_NV_compute_shader_derivatives 1
#جيڪڏهن_پورو /* GL_NV_compute_shader_derivatives */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_conditional_render
#وصف_ڪريو GL_NV_conditional_render 1
#وصف_ڪريو GL_QUERY_WAIT_NV                  0x8E13
#وصف_ڪريو GL_QUERY_NO_WAIT_NV               0x8E14
#وصف_ڪريو GL_QUERY_BY_REGION_WAIT_NV        0x8E15
#وصف_ڪريو GL_QUERY_BY_REGION_NO_WAIT_NV     0x8E16
تعريفنوع فراغ (GL_APIENTRYP PFNGLBEGINCONDITIONALRENDERNVPROC) (GLuint id, GLenum گهڻائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENDCONDITIONALRENDERNVPROC) (فراغ);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glBeginConditionalRenderNV (GLuint id, GLenum گهڻائي);
GL_APICALL فراغ GL_APIENTRY gl_پڇاڙي_Conditional_Render_NV (فراغ);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_NV_conditional_render */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_conservative_raster
#وصف_ڪريو GL_NV_conservative_raster 1
#وصف_ڪريو GL_CONSERVATIVE_RASTERIZATION_NV  0x9346
#وصف_ڪريو GL_SUBPIXEL_PRECISION_BIAS_X_بٽ_NV 0x9347
#وصف_ڪريو GL_SUBPIXEL_PRECISION_BIAS_Y_بٽ_NV 0x9348
#وصف_ڪريو GL_MAX_SUBPIXEL_PRECISION_BIAS_بٽ_NV 0x9349
تعريفنوع فراغ (GL_APIENTRYP PFNGLSUBPIXELPRECISIONBIASNVPROC) (GLuint xbits, GLuint ybits);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glSubpixelPrecisionBiasNV (GLuint xbits, GLuint ybits);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_NV_conservative_raster */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_conservative_raster_pre_snap
#وصف_ڪريو GL_NV_conservative_raster_pre_snap 1
#وصف_ڪريو GL_CONSERVATIVE_RASTER_گهڻائي_PRE_SNAP_NV 0x9550
#جيڪڏهن_پورو /* GL_NV_conservative_raster_pre_snap */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_conservative_raster_pre_snap_triangles
#وصف_ڪريو GL_NV_conservative_raster_pre_snap_triangles 1
#وصف_ڪريو GL_CONSERVATIVE_RASTER_گهڻائي_NV    0x954D
#وصف_ڪريو GL_CONSERVATIVE_RASTER_گهڻائي_POST_SNAP_NV 0x954E
#وصف_ڪريو GL_CONSERVATIVE_RASTER_گهڻائي_PRE_SNAP_TRIANGLES_NV 0x954F
تعريفنوع فراغ (GL_APIENTRYP PFNGLCONSERVATIVERASTERPARAMETERINVPROC) (GLenum pname, GLint param);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glConservativeRasterParameteriNV (GLenum pname, GLint param);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_NV_conservative_raster_pre_snap_triangles */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_copy_بفر
#وصف_ڪريو GL_NV_copy_بفر 1
#وصف_ڪريو GL_COPY_READ_بفر_NV            0x8F36
#وصف_ڪريو GL_COPY_WRITE_بفر_NV           0x8F37
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYBUFFERSUBDATANVPROC) (GLenum read_هدف, GLenum write_هدف, GLintptr read_وٿي, GLintptr write_وٿي, GLsizeiptr سائيز);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Copy_بفر_Sub_معلومات_NV (GLenum read_هدف, GLenum write_هدف, GLintptr read_وٿي, GLintptr write_وٿي, GLsizeiptr سائيز);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_NV_copy_buffer */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_coverage_sample
#وصف_ڪريو GL_NV_coverage_sample 1
#وصف_ڪريو GL_COVERAGE_COMPONENT_NV          0x8ED0
#وصف_ڪريو GL_COVERAGE_COMPONENT4_NV         0x8ED1
#وصف_ڪريو GL_COVERAGE_ATTACHMENT_NV         0x8ED2
#وصف_ڪريو GL_COVERAGE_BUFFERS_NV            0x8ED3
#وصف_ڪريو GL_COVERAGE_SAMPLES_NV            0x8ED4
#وصف_ڪريو GL_COVERAGE_ALL_FRAGMENTS_NV      0x8ED5
#وصف_ڪريو GL_COVERAGE_ڪنارو_FRAGMENTS_NV     0x8ED6
#وصف_ڪريو GL_COVERAGE_AUTOMATIC_NV          0x8ED7
#وصف_ڪريو GL_COVERAGE_بفر_ٻٽو_انگ_NV         0x00008000
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOVERAGEMASKNVPROC) (GLboolean نقاب);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOVERAGEOPERATIONNVPROC) (GLenum operation);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Coverage_نقاب_NV (GLboolean نقاب);
GL_APICALL فراغ GL_APIENTRY glCoverageOperationNV (GLenum operation);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_NV_coverage_sample */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_اونهائي_nonlinear
#وصف_ڪريو GL_NV_اونهائي_nonlinear 1
#وصف_ڪريو GL_اونهائي_COMPONENT16_NONLINEAR_NV 0x8E2C
#جيڪڏهن_پورو /* GL_NV_depth_nonlinear */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_draw_buffers
#وصف_ڪريو GL_NV_draw_buffers 1
#وصف_ڪريو GL_MAX_DRAW_BUFFERS_NV            0x8824
#وصف_ڪريو GL_DRAW_BUFFER0_NV                0x8825
#وصف_ڪريو GL_DRAW_BUFFER1_NV                0x8826
#وصف_ڪريو GL_DRAW_BUFFER2_NV                0x8827
#وصف_ڪريو GL_DRAW_BUFFER3_NV                0x8828
#وصف_ڪريو GL_DRAW_BUFFER4_NV                0x8829
#وصف_ڪريو GL_DRAW_BUFFER5_NV                0x882A
#وصف_ڪريو GL_DRAW_BUFFER6_NV                0x882B
#وصف_ڪريو GL_DRAW_BUFFER7_NV                0x882C
#وصف_ڪريو GL_DRAW_BUFFER8_NV                0x882D
#وصف_ڪريو GL_DRAW_BUFFER9_NV                0x882E
#وصف_ڪريو GL_DRAW_BUFFER10_NV               0x882F
#وصف_ڪريو GL_DRAW_BUFFER11_NV               0x8830
#وصف_ڪريو GL_DRAW_BUFFER12_NV               0x8831
#وصف_ڪريو GL_DRAW_BUFFER13_NV               0x8832
#وصف_ڪريو GL_DRAW_BUFFER14_NV               0x8833
#وصف_ڪريو GL_DRAW_BUFFER15_NV               0x8834
#وصف_ڪريو GL_COLOR_ATTACHMENT0_NV           0x8CE0
#وصف_ڪريو GL_COLOR_ATTACHMENT1_NV           0x8CE1
#وصف_ڪريو GL_COLOR_ATTACHMENT2_NV           0x8CE2
#وصف_ڪريو GL_COLOR_ATTACHMENT3_NV           0x8CE3
#وصف_ڪريو GL_COLOR_ATTACHMENT4_NV           0x8CE4
#وصف_ڪريو GL_COLOR_ATTACHMENT5_NV           0x8CE5
#وصف_ڪريو GL_COLOR_ATTACHMENT6_NV           0x8CE6
#وصف_ڪريو GL_COLOR_ATTACHMENT7_NV           0x8CE7
#وصف_ڪريو GL_COLOR_ATTACHMENT8_NV           0x8CE8
#وصف_ڪريو GL_COLOR_ATTACHMENT9_NV           0x8CE9
#وصف_ڪريو GL_COLOR_ATTACHMENT10_NV          0x8CEA
#وصف_ڪريو GL_COLOR_ATTACHMENT11_NV          0x8CEB
#وصف_ڪريو GL_COLOR_ATTACHMENT12_NV          0x8CEC
#وصف_ڪريو GL_COLOR_ATTACHMENT13_NV          0x8CED
#وصف_ڪريو GL_COLOR_ATTACHMENT14_NV          0x8CEE
#وصف_ڪريو GL_COLOR_ATTACHMENT15_NV          0x8CEF
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWBUFFERSNVPROC) (GLsizei n, ثابت GLenum *bufs);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawBuffersNV (GLsizei n, ثابت GLenum *bufs);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_NV_draw_buffers */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_draw_instanced
#وصف_ڪريو GL_NV_draw_instanced 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDNVPROC) (GLenum گهڻائي, GLint پهريون, GLsizei ڳڻپ, GLsizei primcount);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDNVPROC) (GLenum گهڻائي, GLsizei ڳڻپ, GLenum type, ثابت فراغ *indices, GLsizei primcount);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawArraysInstancedNV (GLenum گهڻائي, GLint پهريون, GLsizei ڳڻپ, GLsizei primcount);
GL_APICALL فراغ GL_APIENTRY glDrawElementsInstancedNV (GLenum گهڻائي, GLsizei ڳڻپ, GLenum type, ثابت فراغ *indices, GLsizei primcount);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_NV_draw_instanced */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_draw_vulkan_image
#وصف_ڪريو GL_NV_draw_vulkan_image 1
تعريفنوع فراغ (GL_APIENTRY  *GLVULKANPROCNV)(فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWVKIMAGENVPROC) (GLuint64 vkImage, GLuint sampler, GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat z, GLfloat s0, GLfloat t0, GLfloat s1, GLfloat t1);
تعريفنوع GLVULKANPROCNV (GL_APIENTRYP PFNGLGETVKPROCADDRNVPROC) (ثابت GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLWAITVKSEMAPHORENVPROC) (GLuint64 vkSemaphore);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSIGNALVKSEMAPHORENVPROC) (GLuint64 vkSemaphore);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSIGNALVKFENCENVPROC) (GLuint64 vkFence);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawVkImageNV (GLuint64 vkImage, GLuint sampler, GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat z, GLfloat s0, GLfloat t0, GLfloat s1, GLfloat t1);
GL_APICALL GLVULKANPROCNV GL_APIENTRY glGetVkProcAddrNV (ثابت GLchar *name);
GL_APICALL فراغ GL_APIENTRY glWaitVkSemaphoreNV (GLuint64 vkSemaphore);
GL_APICALL فراغ GL_APIENTRY glSignalVkSemaphoreNV (GLuint64 vkSemaphore);
GL_APICALL فراغ GL_APIENTRY glSignalVkFenceNV (GLuint64 vkFence);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_NV_draw_vulkan_image */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_explicit_attrib_location
#وصف_ڪريو GL_NV_explicit_attrib_location 1
#جيڪڏهن_پورو /* GL_NV_explicit_attrib_location */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_fbo_color_attachments
#وصف_ڪريو GL_NV_fbo_color_attachments 1
#وصف_ڪريو GL_MAX_COLOR_ATTACHMENTS_NV       0x8CDF
#جيڪڏهن_پورو /* GL_NV_fbo_color_attachments */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_fence
#وصف_ڪريو GL_NV_fence 1
#وصف_ڪريو GL_ALL_COMPLETED_NV               0x84F2
#وصف_ڪريو GL_FENCE_حالت_NV                0x84F3
#وصف_ڪريو GL_FENCE_CONDITION_NV             0x84F4
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEFENCESNVPROC) (GLsizei n, ثابت GLuint *fences);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENFENCESNVPROC) (GLsizei n, GLuint *fences);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISFENCENVPROC) (GLuint fence);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLTESTFENCENVPROC) (GLuint fence);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFENCEIVNVPROC) (GLuint fence, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFINISHFENCENVPROC) (GLuint fence);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSETFENCENVPROC) (GLuint fence, GLenum condition);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDeleteFencesNV (GLsizei n, ثابت GLuint *fences);
GL_APICALL فراغ GL_APIENTRY glGenFencesNV (GLsizei n, GLuint *fences);
GL_APICALL GLboolean GL_APIENTRY glIsFenceNV (GLuint fence);
GL_APICALL GLboolean GL_APIENTRY glTestFenceNV (GLuint fence);
GL_APICALL فراغ GL_APIENTRY glGetFenceivNV (GLuint fence, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY gl_پڄاڻي_Fence_NV (GLuint fence);
GL_APICALL فراغ GL_APIENTRY gl_سيٽ_Fence_NV (GLuint fence, GLenum condition);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_NV_fence */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_fill_rectangle
#وصف_ڪريو GL_NV_fill_rectangle 1
#وصف_ڪريو GL_FILL_RECTANGLE_NV              0x933C
#جيڪڏهن_پورو /* GL_NV_fill_rectangle */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_fragment_coverage_منزل_color
#وصف_ڪريو GL_NV_fragment_coverage_منزل_color 1
#وصف_ڪريو GL_FRAGMENT_COVERAGE_منزل_COLOR_NV  0x92DD
#وصف_ڪريو GL_FRAGMENT_COVERAGE_COLOR_NV     0x92DE
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAGMENTCOVERAGECOLORNVPROC) (GLuint color);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFragmentCoverageColorNV (GLuint color);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_NV_fragment_coverage_to_color */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_fragment_shader_barycentric
#وصف_ڪريو GL_NV_fragment_shader_barycentric 1
#جيڪڏهن_پورو /* GL_NV_fragment_shader_barycentric */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_fragment_shader_interlock
#وصف_ڪريو GL_NV_fragment_shader_interlock 1
#جيڪڏهن_پورو /* GL_NV_fragment_shader_interlock */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_framebuffer_blit
#وصف_ڪريو GL_NV_framebuffer_blit 1
#وصف_ڪريو GL_READ_FRAMEBUFFER_NV            0x8CA8
#وصف_ڪريو GL_DRAW_FRAMEBUFFER_NV            0x8CA9
#وصف_ڪريو GL_DRAW_FRAMEBUFFER_BINDING_NV    0x8CA6
#وصف_ڪريو GL_READ_FRAMEBUFFER_BINDING_NV    0x8CAA
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLITFRAMEBUFFERNVPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield نقاب, GLenum filter);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glBlitFramebufferNV (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield نقاب, GLenum filter);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_NV_framebuffer_blit */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_framebuffer_mixed_samples
#وصف_ڪريو GL_NV_framebuffer_mixed_samples 1
#وصف_ڪريو GL_COVERAGE_MODULATION_جدول_NV   0x9331
#وصف_ڪريو GL_COLOR_SAMPLES_NV               0x8E20
#وصف_ڪريو GL_اونهائي_SAMPLES_NV               0x932D
#وصف_ڪريو GL_STENCIL_SAMPLES_NV             0x932E
#وصف_ڪريو GL_MIXED_اونهائي_SAMPLES_SUPPORTED_NV 0x932F
#وصف_ڪريو GL_MIXED_STENCIL_SAMPLES_SUPPORTED_NV 0x9330
#وصف_ڪريو GL_COVERAGE_MODULATION_NV         0x9332
#وصف_ڪريو GL_COVERAGE_MODULATION_جدول_سائيز_NV 0x9333
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOVERAGEMODULATIONTABLENVPROC) (GLsizei n, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETCOVERAGEMODULATIONTABLENVPROC) (GLsizei buf_سائيز, GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOVERAGEMODULATIONNVPROC) (GLenum components);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Coverage_Modulation_جدول_NV (GLsizei n, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY gl_Get_Coverage_Modulation_جدول_NV (GLsizei buf_سائيز, GLfloat *v);
GL_APICALL فراغ GL_APIENTRY glCoverageModulationNV (GLenum components);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_NV_framebuffer_mixed_samples */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_framebuffer_multisample
#وصف_ڪريو GL_NV_framebuffer_multisample 1
#وصف_ڪريو GL_RENDERBUFFER_SAMPLES_NV        0x8CAB
#وصف_ڪريو GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_NV 0x8D56
#وصف_ڪريو GL_MAX_SAMPLES_NV                 0x8D57
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLENVPROC) (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glRenderbufferStorageMultisampleNV (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_NV_framebuffer_multisample */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_generate_mipmap_sRGB
#وصف_ڪريو GL_NV_generate_mipmap_sRGB 1
#جيڪڏهن_پورو /* GL_NV_generate_mipmap_sRGB */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_geometry_shader_passthrough
#وصف_ڪريو GL_NV_geometry_shader_passthrough 1
#جيڪڏهن_پورو /* GL_NV_geometry_shader_passthrough */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_gpu_shader5
#وصف_ڪريو GL_NV_gpu_shader5 1
تعريفنوع khronos_int64_t GLint64EXT;
تعريفنوع khronos_uint64_t GLuint64EXT;
#وصف_ڪريو GL_INT64_NV                       0x140E
#وصف_ڪريو GL_UNSIGNED_INT64_NV              0x140F
#وصف_ڪريو GL_INT8_NV                        0x8FE0
#وصف_ڪريو GL_INT8_VEC2_NV                   0x8FE1
#وصف_ڪريو GL_INT8_VEC3_NV                   0x8FE2
#وصف_ڪريو GL_INT8_VEC4_NV                   0x8FE3
#وصف_ڪريو GL_INT16_NV                       0x8FE4
#وصف_ڪريو GL_INT16_VEC2_NV                  0x8FE5
#وصف_ڪريو GL_INT16_VEC3_NV                  0x8FE6
#وصف_ڪريو GL_INT16_VEC4_NV                  0x8FE7
#وصف_ڪريو GL_INT64_VEC2_NV                  0x8FE9
#وصف_ڪريو GL_INT64_VEC3_NV                  0x8FEA
#وصف_ڪريو GL_INT64_VEC4_NV                  0x8FEB
#وصف_ڪريو GL_UNSIGNED_INT8_NV               0x8FEC
#وصف_ڪريو GL_UNSIGNED_INT8_VEC2_NV          0x8FED
#وصف_ڪريو GL_UNSIGNED_INT8_VEC3_NV          0x8FEE
#وصف_ڪريو GL_UNSIGNED_INT8_VEC4_NV          0x8FEF
#وصف_ڪريو GL_UNSIGNED_INT16_NV              0x8FF0
#وصف_ڪريو GL_UNSIGNED_INT16_VEC2_NV         0x8FF1
#وصف_ڪريو GL_UNSIGNED_INT16_VEC3_NV         0x8FF2
#وصف_ڪريو GL_UNSIGNED_INT16_VEC4_NV         0x8FF3
#وصف_ڪريو GL_UNSIGNED_INT64_VEC2_NV         0x8FF5
#وصف_ڪريو GL_UNSIGNED_INT64_VEC3_NV         0x8FF6
#وصف_ڪريو GL_UNSIGNED_INT64_VEC4_NV         0x8FF7
#وصف_ڪريو GL_FLOAT16_NV                     0x8FF8
#وصف_ڪريو GL_FLOAT16_VEC2_NV                0x8FF9
#وصف_ڪريو GL_FLOAT16_VEC3_NV                0x8FFA
#وصف_ڪريو GL_FLOAT16_VEC4_NV                0x8FFB
#وصف_ڪريو GL_PATCHES                        0x000E
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1I64NVPROC) (GLint location, GLint64EXT x);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2I64NVPROC) (GLint location, GLint64EXT x, GLint64EXT y);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3I64NVPROC) (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4I64NVPROC) (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1I64VNVPROC) (GLint location, GLsizei ڳڻپ, ثابت GLint64EXT *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2I64VNVPROC) (GLint location, GLsizei ڳڻپ, ثابت GLint64EXT *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3I64VNVPROC) (GLint location, GLsizei ڳڻپ, ثابت GLint64EXT *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4I64VNVPROC) (GLint location, GLsizei ڳڻپ, ثابت GLint64EXT *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1UI64NVPROC) (GLint location, GLuint64EXT x);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2UI64NVPROC) (GLint location, GLuint64EXT x, GLuint64EXT y);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3UI64NVPROC) (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4UI64NVPROC) (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1UI64VNVPROC) (GLint location, GLsizei ڳڻپ, ثابت GLuint64EXT *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2UI64VNVPROC) (GLint location, GLsizei ڳڻپ, ثابت GLuint64EXT *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3UI64VNVPROC) (GLint location, GLsizei ڳڻپ, ثابت GLuint64EXT *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4UI64VNVPROC) (GLint location, GLsizei ڳڻپ, ثابت GLuint64EXT *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETUNIFORMI64VNVPROC) (GLuint پروگرام, GLint location, GLint64EXT *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1I64NVPROC) (GLuint پروگرام, GLint location, GLint64EXT x);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2I64NVPROC) (GLuint پروگرام, GLint location, GLint64EXT x, GLint64EXT y);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3I64NVPROC) (GLuint پروگرام, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4I64NVPROC) (GLuint پروگرام, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1I64VNVPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLint64EXT *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2I64VNVPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLint64EXT *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3I64VNVPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLint64EXT *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4I64VNVPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLint64EXT *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UI64NVPROC) (GLuint پروگرام, GLint location, GLuint64EXT x);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UI64NVPROC) (GLuint پروگرام, GLint location, GLuint64EXT x, GLuint64EXT y);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UI64NVPROC) (GLuint پروگرام, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UI64NVPROC) (GLuint پروگرام, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UI64VNVPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLuint64EXT *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UI64VNVPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLuint64EXT *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UI64VNVPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLuint64EXT *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UI64VNVPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLuint64EXT *قدر);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glUniform1i64NV (GLint location, GLint64EXT x);
GL_APICALL فراغ GL_APIENTRY glUniform2i64NV (GLint location, GLint64EXT x, GLint64EXT y);
GL_APICALL فراغ GL_APIENTRY glUniform3i64NV (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
GL_APICALL فراغ GL_APIENTRY glUniform4i64NV (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
GL_APICALL فراغ GL_APIENTRY glUniform1i64vNV (GLint location, GLsizei ڳڻپ, ثابت GLint64EXT *قدر);
GL_APICALL فراغ GL_APIENTRY glUniform2i64vNV (GLint location, GLsizei ڳڻپ, ثابت GLint64EXT *قدر);
GL_APICALL فراغ GL_APIENTRY glUniform3i64vNV (GLint location, GLsizei ڳڻپ, ثابت GLint64EXT *قدر);
GL_APICALL فراغ GL_APIENTRY glUniform4i64vNV (GLint location, GLsizei ڳڻپ, ثابت GLint64EXT *قدر);
GL_APICALL فراغ GL_APIENTRY glUniform1ui64NV (GLint location, GLuint64EXT x);
GL_APICALL فراغ GL_APIENTRY glUniform2ui64NV (GLint location, GLuint64EXT x, GLuint64EXT y);
GL_APICALL فراغ GL_APIENTRY glUniform3ui64NV (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
GL_APICALL فراغ GL_APIENTRY glUniform4ui64NV (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
GL_APICALL فراغ GL_APIENTRY glUniform1ui64vNV (GLint location, GLsizei ڳڻپ, ثابت GLuint64EXT *قدر);
GL_APICALL فراغ GL_APIENTRY glUniform2ui64vNV (GLint location, GLsizei ڳڻپ, ثابت GLuint64EXT *قدر);
GL_APICALL فراغ GL_APIENTRY glUniform3ui64vNV (GLint location, GLsizei ڳڻپ, ثابت GLuint64EXT *قدر);
GL_APICALL فراغ GL_APIENTRY glUniform4ui64vNV (GLint location, GLsizei ڳڻپ, ثابت GLuint64EXT *قدر);
GL_APICALL فراغ GL_APIENTRY glGetUniformi64vNV (GLuint پروگرام, GLint location, GLint64EXT *params);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform1i64_NV (GLuint پروگرام, GLint location, GLint64EXT x);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform2i64_NV (GLuint پروگرام, GLint location, GLint64EXT x, GLint64EXT y);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform3i64_NV (GLuint پروگرام, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform4i64_NV (GLuint پروگرام, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform1i64v_NV (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLint64EXT *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform2i64v_NV (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLint64EXT *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform3i64v_NV (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLint64EXT *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform4i64v_NV (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLint64EXT *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform1ui64_NV (GLuint پروگرام, GLint location, GLuint64EXT x);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform2ui64_NV (GLuint پروگرام, GLint location, GLuint64EXT x, GLuint64EXT y);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform3ui64_NV (GLuint پروگرام, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform4ui64_NV (GLuint پروگرام, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform1ui64v_NV (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLuint64EXT *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform2ui64v_NV (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLuint64EXT *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform3ui64v_NV (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLuint64EXT *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform4ui64v_NV (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLuint64EXT *قدر);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_NV_gpu_shader5 */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_image_formats
#وصف_ڪريو GL_NV_image_formats 1
#جيڪڏهن_پورو /* GL_NV_image_formats */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_instanced_arrays
#وصف_ڪريو GL_NV_instanced_arrays 1
#وصف_ڪريو GL_راس_ATTRIB_ARRAY_ورهائيندڙ_NV 0x88FE
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBDIVISORNVPROC) (GLuint اشاريو, GLuint ورهائيندڙ);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib_ورهائيندڙ_NV (GLuint اشاريو, GLuint ورهائيندڙ);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_NV_instanced_arrays */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_internalformat_sample_query
#وصف_ڪريو GL_NV_internalformat_sample_query 1
#وصف_ڪريو GL_TEXTURE_2D_MULTISAMPLE         0x9100
#وصف_ڪريو GL_TEXTURE_2D_MULTISAMPLE_ARRAY   0x9102
#وصف_ڪريو GL_MULTISAMPLES_NV                0x9371
#وصف_ڪريو GL_SUPERSAMPLE_SCALE_X_NV         0x9372
#وصف_ڪريو GL_SUPERSAMPLE_SCALE_Y_NV         0x9373
#وصف_ڪريو GL_CONFORMANT_NV                  0x9374
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTERNALFORMATSAMPLEIVNVPROC) (GLenum هدف, GLenum internalformat, GLsizei samples, GLenum pname, GLsizei ڳڻپ, GLint *params);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glGetInternalformatSampleivNV (GLenum هدف, GLenum internalformat, GLsizei samples, GLenum pname, GLsizei ڳڻپ, GLint *params);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_NV_internalformat_sample_query */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_يادگيري_attachment
#وصف_ڪريو GL_NV_يادگيري_attachment 1
#وصف_ڪريو GL_ATTACHED_يادگيري_OBJECT_NV      0x95A4
#وصف_ڪريو GL_ATTACHED_يادگيري_وٿي_NV      0x95A5
#وصف_ڪريو GL_يادگيري_ATTACHABLE_ALIGNMENT_NV 0x95A6
#وصف_ڪريو GL_يادگيري_ATTACHABLE_سائيز_NV      0x95A7
#وصف_ڪريو GL_يادگيري_ATTACHABLE_NV           0x95A8
#وصف_ڪريو GL_DETACHED_يادگيري_INCARNATION_NV 0x95A9
#وصف_ڪريو GL_DETACHED_TEXTURES_NV           0x95AA
#وصف_ڪريو GL_DETACHED_BUFFERS_NV            0x95AB
#وصف_ڪريو GL_MAX_DETACHED_TEXTURES_NV       0x95AC
#وصف_ڪريو GL_MAX_DETACHED_BUFFERS_NV        0x95AD
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETMEMORYOBJECTDETACHEDRESOURCESUIVNVPROC) (GLuint يادگيري, GLenum pname, GLint پهريون, GLsizei ڳڻپ, GLuint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRESETMEMORYOBJECTPARAMETERNVPROC) (GLuint يادگيري, GLenum pname);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXATTACHMEMORYNVPROC) (GLenum هدف, GLuint يادگيري, GLuint64 وٿي_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBUFFERATTACHMEMORYNVPROC) (GLenum هدف, GLuint يادگيري, GLuint64 وٿي_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTUREATTACHMEMORYNVPROC) (GLuint texture, GLuint يادگيري, GLuint64 وٿي_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLNAMEDBUFFERATTACHMEMORYNVPROC) (GLuint بفر_2, GLuint يادگيري, GLuint64 وٿي_2);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Get_يادگيري_Object_Detached_Resourcesuiv_NV (GLuint يادگيري, GLenum pname, GLint پهريون, GLsizei ڳڻپ, GLuint *params);
GL_APICALL فراغ GL_APIENTRY gl_Reset_يادگيري_Object_Parameter_NV (GLuint يادگيري, GLenum pname);
GL_APICALL فراغ GL_APIENTRY gl_Tex_Attach_يادگيري_NV (GLenum هدف, GLuint يادگيري, GLuint64 وٿي_2);
GL_APICALL فراغ GL_APIENTRY gl_بفر_Attach_يادگيري_NV (GLenum هدف, GLuint يادگيري, GLuint64 وٿي_2);
GL_APICALL فراغ GL_APIENTRY gl_Texture_Attach_يادگيري_NV (GLuint texture, GLuint يادگيري, GLuint64 وٿي_2);
GL_APICALL فراغ GL_APIENTRY gl_Named_بفر_Attach_يادگيري_NV (GLuint بفر_2, GLuint يادگيري, GLuint64 وٿي_2);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_NV_memory_attachment */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_يادگيري_object_sparse
#وصف_ڪريو GL_NV_يادگيري_object_sparse 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLBUFFERPAGECOMMITMENTMEMNVPROC) (GLenum هدف, GLintptr وٿي_2, GLsizeiptr سائيز, GLuint يادگيري, GLuint64 mem_وٿي, GLboolean commit);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPAGECOMMITMENTMEMNVPROC) (GLenum هدف, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLuint يادگيري, GLuint64 وٿي_2, GLboolean commit);
تعريفنوع فراغ (GL_APIENTRYP PFNGLNAMEDBUFFERPAGECOMMITMENTMEMNVPROC) (GLuint بفر_2, GLintptr وٿي_2, GLsizeiptr سائيز, GLuint يادگيري, GLuint64 mem_وٿي, GLboolean commit);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTUREPAGECOMMITMENTMEMNVPROC) (GLuint texture, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLuint يادگيري, GLuint64 وٿي_2, GLboolean commit);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_بفر_صفحو_Commitment_Mem_NV (GLenum هدف, GLintptr وٿي_2, GLsizeiptr سائيز, GLuint يادگيري, GLuint64 mem_وٿي, GLboolean commit);
GL_APICALL فراغ GL_APIENTRY gl_Tex_صفحو_Commitment_Mem_NV (GLenum هدف, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLuint يادگيري, GLuint64 وٿي_2, GLboolean commit);
GL_APICALL فراغ GL_APIENTRY gl_Named_بفر_صفحو_Commitment_Mem_NV (GLuint بفر_2, GLintptr وٿي_2, GLsizeiptr سائيز, GLuint يادگيري, GLuint64 mem_وٿي, GLboolean commit);
GL_APICALL فراغ GL_APIENTRY gl_Texture_صفحو_Commitment_Mem_NV (GLuint texture, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLuint يادگيري, GLuint64 وٿي_2, GLboolean commit);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_NV_memory_object_sparse */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_mesh_shader
#وصف_ڪريو GL_NV_mesh_shader 1
#وصف_ڪريو GL_MESH_SHADER_NV                 0x9559
#وصف_ڪريو GL_TASK_SHADER_NV                 0x955A
#وصف_ڪريو GL_MAX_MESH_هڪجهڙو_بلاڪون_NV     0x8E60
#وصف_ڪريو GL_MAX_MESH_TEXTURE_IMAGE_UNITS_NV 0x8E61
#وصف_ڪريو GL_MAX_MESH_IMAGE_UNIFORMS_NV     0x8E62
#وصف_ڪريو GL_MAX_MESH_هڪجهڙو_COMPONENTS_NV 0x8E63
#وصف_ڪريو GL_MAX_MESH_ATOMIC_COUNTER_BUFFERS_NV 0x8E64
#وصف_ڪريو GL_MAX_MESH_ATOMIC_COUNTERS_NV    0x8E65
#وصف_ڪريو GL_MAX_MESH_SHADER_STORAGE_بلاڪون_NV 0x8E66
#وصف_ڪريو GL_MAX_COMBINED_MESH_هڪجهڙو_COMPONENTS_NV 0x8E67
#وصف_ڪريو GL_MAX_TASK_هڪجهڙو_بلاڪون_NV     0x8E68
#وصف_ڪريو GL_MAX_TASK_TEXTURE_IMAGE_UNITS_NV 0x8E69
#وصف_ڪريو GL_MAX_TASK_IMAGE_UNIFORMS_NV     0x8E6A
#وصف_ڪريو GL_MAX_TASK_هڪجهڙو_COMPONENTS_NV 0x8E6B
#وصف_ڪريو GL_MAX_TASK_ATOMIC_COUNTER_BUFFERS_NV 0x8E6C
#وصف_ڪريو GL_MAX_TASK_ATOMIC_COUNTERS_NV    0x8E6D
#وصف_ڪريو GL_MAX_TASK_SHADER_STORAGE_بلاڪون_NV 0x8E6E
#وصف_ڪريو GL_MAX_COMBINED_TASK_هڪجهڙو_COMPONENTS_NV 0x8E6F
#وصف_ڪريو GL_MAX_MESH_WORK_گروهه_INVOCATIONS_NV 0x95A2
#وصف_ڪريو GL_MAX_TASK_WORK_گروهه_INVOCATIONS_NV 0x95A3
#وصف_ڪريو GL_MAX_MESH_ڪل_يادگيري_سائيز_NV  0x9536
#وصف_ڪريو GL_MAX_TASK_ڪل_يادگيري_سائيز_NV  0x9537
#وصف_ڪريو GL_MAX_MESH_OUTPUT_VERTICES_NV    0x9538
#وصف_ڪريو GL_MAX_MESH_OUTPUT_PRIMITIVES_NV  0x9539
#وصف_ڪريو GL_MAX_TASK_OUTPUT_ڳڻپ_NV       0x953A
#وصف_ڪريو GL_MAX_DRAW_MESH_TASKS_ڳڻپ_NV   0x953D
#وصف_ڪريو GL_MAX_MESH_VIEWS_NV              0x9557
#وصف_ڪريو GL_MESH_OUTPUT_في_راس_GRANULARITY_NV 0x92DF
#وصف_ڪريو GL_MESH_OUTPUT_في_PRIMITIVE_GRANULARITY_NV 0x9543
#وصف_ڪريو GL_MAX_MESH_WORK_گروهه_سائيز_NV    0x953B
#وصف_ڪريو GL_MAX_TASK_WORK_گروهه_سائيز_NV    0x953C
#وصف_ڪريو GL_MESH_WORK_گروهه_سائيز_NV        0x953E
#وصف_ڪريو GL_TASK_WORK_گروهه_سائيز_NV        0x953F
#وصف_ڪريو GL_MESH_VERTICES_ٻاهريون_NV           0x9579
#وصف_ڪريو GL_MESH_PRIMITIVES_ٻاهريون_NV         0x957A
#وصف_ڪريو GL_MESH_OUTPUT_TYPE_NV            0x957B
#وصف_ڪريو GL_هڪجهڙو_بلاڪ_REFERENCED_BY_MESH_SHADER_NV 0x959C
#وصف_ڪريو GL_هڪجهڙو_بلاڪ_REFERENCED_BY_TASK_SHADER_NV 0x959D
#وصف_ڪريو GL_REFERENCED_BY_MESH_SHADER_NV   0x95A0
#وصف_ڪريو GL_REFERENCED_BY_TASK_SHADER_NV   0x95A1
#وصف_ڪريو GL_MESH_SHADER_ٻٽو_انگ_NV             0x00000040
#وصف_ڪريو GL_TASK_SHADER_ٻٽو_انگ_NV             0x00000080
#وصف_ڪريو GL_MESH_SUBROUTINE_NV             0x957C
#وصف_ڪريو GL_TASK_SUBROUTINE_NV             0x957D
#وصف_ڪريو GL_MESH_SUBROUTINE_هڪجهڙو_NV     0x957E
#وصف_ڪريو GL_TASK_SUBROUTINE_هڪجهڙو_NV     0x957F
#وصف_ڪريو GL_ATOMIC_COUNTER_بفر_REFERENCED_BY_MESH_SHADER_NV 0x959E
#وصف_ڪريو GL_ATOMIC_COUNTER_بفر_REFERENCED_BY_TASK_SHADER_NV 0x959F
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWMESHTASKSNVPROC) (GLuint پهريون, GLuint ڳڻپ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWMESHTASKSINDIRECTNVPROC) (GLintptr اڻسڌو);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWMESHTASKSINDIRECTNVPROC) (GLintptr اڻسڌو, GLsizei drawcount, GLsizei stride);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTNVPROC) (GLintptr اڻسڌو, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawMeshTasksNV (GLuint پهريون, GLuint ڳڻپ);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Mesh_Tasks_اڻسڌو_NV (GLintptr اڻسڌو);
GL_APICALL فراغ GL_APIENTRY gl_Multi_Draw_Mesh_Tasks_اڻسڌو_NV (GLintptr اڻسڌو, GLsizei drawcount, GLsizei stride);
GL_APICALL فراغ GL_APIENTRY gl_Multi_Draw_Mesh_Tasks_اڻسڌو_ڳڻپ_NV (GLintptr اڻسڌو, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_NV_mesh_shader */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_non_چورس_matrices
#وصف_ڪريو GL_NV_non_چورس_matrices 1
#وصف_ڪريو GL_FLOAT_MAT2x3_NV                0x8B65
#وصف_ڪريو GL_FLOAT_MAT2x4_NV                0x8B66
#وصف_ڪريو GL_FLOAT_MAT3x2_NV                0x8B67
#وصف_ڪريو GL_FLOAT_MAT3x4_NV                0x8B68
#وصف_ڪريو GL_FLOAT_MAT4x2_NV                0x8B69
#وصف_ڪريو GL_FLOAT_MAT4x3_NV                0x8B6A
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX2X3FVNVPROC) (GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX3X2FVNVPROC) (GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX2X4FVNVPROC) (GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX4X2FVNVPROC) (GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX3X4FVNVPROC) (GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX4X3FVNVPROC) (GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_هڪجهڙو_Matrix2x3fv_NV (GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_هڪجهڙو_Matrix3x2fv_NV (GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_هڪجهڙو_Matrix2x4fv_NV (GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_هڪجهڙو_Matrix4x2fv_NV (GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_هڪجهڙو_Matrix3x4fv_NV (GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_هڪجهڙو_Matrix4x3fv_NV (GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_NV_non_square_matrices */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_pack_subimage
#وصف_ڪريو GL_NV_pack_subimage 1
#وصف_ڪريو GL_PACK_صف_ڊيگهائي_NV             0x0D02
#وصف_ڪريو GL_PACK_SKIP_صفون_NV              0x0D03
#وصف_ڪريو GL_PACK_SKIP_PIXELS_NV            0x0D04
#جيڪڏهن_پورو /* GL_NV_pack_subimage */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_رستو_rendering
#وصف_ڪريو GL_NV_رستو_rendering 1
تعريفنوع مزدوج GLdouble;
#وصف_ڪريو GL_رستو_FORMAT_SVG_NV             0x9070
#وصف_ڪريو GL_رستو_FORMAT_PS_NV              0x9071
#وصف_ڪريو GL_STANDARD_FONT_NAME_NV          0x9072
#وصف_ڪريو GL_SYSTEM_FONT_NAME_NV            0x9073
#وصف_ڪريو GL_FILE_NAME_NV                   0x9074
#وصف_ڪريو GL_رستو_STROKE_ويڪر_NV           0x9075
#وصف_ڪريو GL_رستو_پڇاڙي_CAPS_NV               0x9076
#وصف_ڪريو GL_رستو_INITIAL_پڇاڙي_CAP_NV        0x9077
#وصف_ڪريو GL_رستو_TERMINAL_پڇاڙي_CAP_NV       0x9078
#وصف_ڪريو GL_رستو_JOIN_STYLE_NV             0x9079
#وصف_ڪريو GL_رستو_MITER_حد_بندي_NV            0x907A
#وصف_ڪريو GL_رستو_DASH_CAPS_NV              0x907B
#وصف_ڪريو GL_رستو_INITIAL_DASH_CAP_NV       0x907C
#وصف_ڪريو GL_رستو_TERMINAL_DASH_CAP_NV      0x907D
#وصف_ڪريو GL_رستو_DASH_وٿي_NV            0x907E
#وصف_ڪريو GL_رستو_CLIENT_ڊيگهائي_NV          0x907F
#وصف_ڪريو GL_رستو_FILL_گهڻائي_NV              0x9080
#وصف_ڪريو GL_رستو_FILL_نقاب_NV              0x9081
#وصف_ڪريو GL_رستو_FILL_COVER_گهڻائي_NV        0x9082
#وصف_ڪريو GL_رستو_STROKE_COVER_گهڻائي_NV      0x9083
#وصف_ڪريو GL_رستو_STROKE_نقاب_NV            0x9084
#وصف_ڪريو GL_ڳڻپ_مٿي_NV                    0x9088
#وصف_ڪريو GL_ڳڻپ_هيٺ_ڏانهن_NV                  0x9089
#وصف_ڪريو GL_رستو_OBJECT_BOUNDING_BOX_NV    0x908A
#وصف_ڪريو GL_CONVEX_HULL_NV                 0x908B
#وصف_ڪريو GL_BOUNDING_BOX_NV                0x908D
#وصف_ڪريو GL_TRANSLATE_X_NV                 0x908E
#وصف_ڪريو GL_TRANSLATE_Y_NV                 0x908F
#وصف_ڪريو GL_TRANSLATE_2D_NV                0x9090
#وصف_ڪريو GL_TRANSLATE_3D_NV                0x9091
#وصف_ڪريو GL_AFFINE_2D_NV                   0x9092
#وصف_ڪريو GL_AFFINE_3D_NV                   0x9094
#وصف_ڪريو GL_TRANSPOSE_AFFINE_2D_NV         0x9096
#وصف_ڪريو GL_TRANSPOSE_AFFINE_3D_NV         0x9098
#وصف_ڪريو GL_UTF8_NV                        0x909A
#وصف_ڪريو GL_UTF16_NV                       0x909B
#وصف_ڪريو GL_BOUNDING_BOX_جو_BOUNDING_BOXES_NV 0x909C
#وصف_ڪريو GL_رستو_COMMAND_ڳڻپ_NV          0x909D
#وصف_ڪريو GL_رستو_COORD_ڳڻپ_NV            0x909E
#وصف_ڪريو GL_رستو_DASH_ARRAY_ڳڻپ_NV       0x909F
#وصف_ڪريو GL_رستو_COMPUTED_ڊيگهائي_NV        0x90A0
#وصف_ڪريو GL_رستو_FILL_BOUNDING_BOX_NV      0x90A1
#وصف_ڪريو GL_رستو_STROKE_BOUNDING_BOX_NV    0x90A2
#وصف_ڪريو GL_چورس_NV                      0x90A3
#وصف_ڪريو GL_ڦيرو_NV                       0x90A4
#وصف_ڪريو GL_TRIANGULAR_NV                  0x90A5
#وصف_ڪريو GL_BEVEL_NV                       0x90A6
#وصف_ڪريو GL_MITER_REVERT_NV                0x90A7
#وصف_ڪريو GL_MITER_TRUNCATE_NV              0x90A8
#وصف_ڪريو GL_SKIP_MISSING_GLYPH_NV          0x90A9
#وصف_ڪريو GL_USE_MISSING_GLYPH_NV           0x90AA
#وصف_ڪريو GL_رستو_ERROR_POSITION_NV         0x90AB
#وصف_ڪريو GL_ACCUM_ADJACENT_جوڙا_NV        0x90AD
#وصف_ڪريو GL_ADJACENT_جوڙا_NV              0x90AE
#وصف_ڪريو GL_پهريون_منزل_REST_NV               0x90AF
#وصف_ڪريو GL_رستو_GEN_گهڻائي_NV               0x90B0
#وصف_ڪريو GL_رستو_GEN_COEFF_NV              0x90B1
#وصف_ڪريو GL_رستو_GEN_COMPONENTS_NV         0x90B3
#وصف_ڪريو GL_رستو_STENCIL_FUNC_NV           0x90B7
#وصف_ڪريو GL_رستو_STENCIL_REF_NV            0x90B8
#وصف_ڪريو GL_رستو_STENCIL_قدر_نقاب_NV     0x90B9
#وصف_ڪريو GL_رستو_STENCIL_اونهائي_وٿي_ضرب_ڪندڙ_NV 0x90BD
#وصف_ڪريو GL_رستو_STENCIL_اونهائي_وٿي_UNITS_NV 0x90BE
#وصف_ڪريو GL_رستو_COVER_اونهائي_FUNC_NV       0x90BF
#وصف_ڪريو GL_رستو_DASH_وٿي_RESET_NV      0x90B4
#وصف_ڪريو GL_MOVE_منزل_RESETS_NV              0x90B5
#وصف_ڪريو GL_MOVE_منزل_CONTINUES_NV           0x90B6
#وصف_ڪريو GL_CLOSE_رستو_NV                  0x00
#وصف_ڪريو GL_MOVE_منزل_NV                     0x02
#وصف_ڪريو GL_RELATIVE_MOVE_منزل_NV            0x03
#وصف_ڪريو GL_سٽ_منزل_NV                     0x04
#وصف_ڪريو GL_RELATIVE_سٽ_منزل_NV            0x05
#وصف_ڪريو GL_HORIZONTAL_سٽ_منزل_NV          0x06
#وصف_ڪريو GL_RELATIVE_HORIZONTAL_سٽ_منزل_NV 0x07
#وصف_ڪريو GL_VERTICAL_سٽ_منزل_NV            0x08
#وصف_ڪريو GL_RELATIVE_VERTICAL_سٽ_منزل_NV   0x09
#وصف_ڪريو GL_QUADRATIC_وڪر_منزل_NV          0x0A
#وصف_ڪريو GL_RELATIVE_QUADRATIC_وڪر_منزل_NV 0x0B
#وصف_ڪريو GL_CUBIC_وڪر_منزل_NV              0x0C
#وصف_ڪريو GL_RELATIVE_CUBIC_وڪر_منزل_NV     0x0D
#وصف_ڪريو GL_SMOOTH_QUADRATIC_وڪر_منزل_NV   0x0E
#وصف_ڪريو GL_RELATIVE_SMOOTH_QUADRATIC_وڪر_منزل_NV 0x0F
#وصف_ڪريو GL_SMOOTH_CUBIC_وڪر_منزل_NV       0x10
#وصف_ڪريو GL_RELATIVE_SMOOTH_CUBIC_وڪر_منزل_NV 0x11
#وصف_ڪريو GL_SMALL_CCW_ARC_منزل_NV            0x12
#وصف_ڪريو GL_RELATIVE_SMALL_CCW_ARC_منزل_NV   0x13
#وصف_ڪريو GL_SMALL_CW_ARC_منزل_NV             0x14
#وصف_ڪريو GL_RELATIVE_SMALL_CW_ARC_منزل_NV    0x15
#وصف_ڪريو GL_LARGE_CCW_ARC_منزل_NV            0x16
#وصف_ڪريو GL_RELATIVE_LARGE_CCW_ARC_منزل_NV   0x17
#وصف_ڪريو GL_LARGE_CW_ARC_منزل_NV             0x18
#وصف_ڪريو GL_RELATIVE_LARGE_CW_ARC_منزل_NV    0x19
#وصف_ڪريو GL_RESTART_رستو_NV                0xF0
#وصف_ڪريو GL_DUP_پهريون_CUBIC_وڪر_منزل_NV    0xF2
#وصف_ڪريو GL_DUP_آخري_CUBIC_وڪر_منزل_NV     0xF4
#وصف_ڪريو GL_RECT_NV                        0xF6
#وصف_ڪريو GL_CIRCULAR_CCW_ARC_منزل_NV         0xF8
#وصف_ڪريو GL_CIRCULAR_CW_ARC_منزل_NV          0xFA
#وصف_ڪريو GL_CIRCULAR_TANGENT_ARC_منزل_NV     0xFC
#وصف_ڪريو GL_ARC_منزل_NV                      0xFE
#وصف_ڪريو GL_RELATIVE_ARC_منزل_NV             0xFF
#وصف_ڪريو GL_BOLD_ٻٽو_انگ_NV                    0x01
#وصف_ڪريو GL_ITALIC_ٻٽو_انگ_NV                  0x02
#وصف_ڪريو GL_GLYPH_ويڪر_ٻٽو_انگ_NV             0x01
#وصف_ڪريو GL_GLYPH_اوچائي_ٻٽو_انگ_NV            0x02
#وصف_ڪريو GL_GLYPH_HORIZONTAL_BEARING_X_ٻٽو_انگ_NV 0x04
#وصف_ڪريو GL_GLYPH_HORIZONTAL_BEARING_Y_ٻٽو_انگ_NV 0x08
#وصف_ڪريو GL_GLYPH_HORIZONTAL_BEARING_ADVANCE_ٻٽو_انگ_NV 0x10
#وصف_ڪريو GL_GLYPH_VERTICAL_BEARING_X_ٻٽو_انگ_NV 0x20
#وصف_ڪريو GL_GLYPH_VERTICAL_BEARING_Y_ٻٽو_انگ_NV 0x40
#وصف_ڪريو GL_GLYPH_VERTICAL_BEARING_ADVANCE_ٻٽو_انگ_NV 0x80
#وصف_ڪريو GL_GLYPH_HAS_KERNING_ٻٽو_انگ_NV       0x100
#وصف_ڪريو GL_FONT_X_MIN_BOUNDS_ٻٽو_انگ_NV       0x00010000
#وصف_ڪريو GL_FONT_Y_MIN_BOUNDS_ٻٽو_انگ_NV       0x00020000
#وصف_ڪريو GL_FONT_X_MAX_BOUNDS_ٻٽو_انگ_NV       0x00040000
#وصف_ڪريو GL_FONT_Y_MAX_BOUNDS_ٻٽو_انگ_NV       0x00080000
#وصف_ڪريو GL_FONT_UNITS_في_EM_ٻٽو_انگ_NV       0x00100000
#وصف_ڪريو GL_FONT_ASCENDER_ٻٽو_انگ_NV           0x00200000
#وصف_ڪريو GL_FONT_DESCENDER_ٻٽو_انگ_NV          0x00400000
#وصف_ڪريو GL_FONT_اوچائي_ٻٽو_انگ_NV             0x00800000
#وصف_ڪريو GL_FONT_MAX_ADVANCE_ويڪر_ٻٽو_انگ_NV  0x01000000
#وصف_ڪريو GL_FONT_MAX_ADVANCE_اوچائي_ٻٽو_انگ_NV 0x02000000
#وصف_ڪريو GL_FONT_UNDERLINE_POSITION_ٻٽو_انگ_NV 0x04000000
#وصف_ڪريو GL_FONT_UNDERLINE_THICKNESS_ٻٽو_انگ_NV 0x08000000
#وصف_ڪريو GL_FONT_HAS_KERNING_ٻٽو_انگ_NV        0x10000000
#وصف_ڪريو GL_ROUNDED_RECT_NV                0xE8
#وصف_ڪريو GL_RELATIVE_ROUNDED_RECT_NV       0xE9
#وصف_ڪريو GL_ROUNDED_RECT2_NV               0xEA
#وصف_ڪريو GL_RELATIVE_ROUNDED_RECT2_NV      0xEB
#وصف_ڪريو GL_ROUNDED_RECT4_NV               0xEC
#وصف_ڪريو GL_RELATIVE_ROUNDED_RECT4_NV      0xED
#وصف_ڪريو GL_ROUNDED_RECT8_NV               0xEE
#وصف_ڪريو GL_RELATIVE_ROUNDED_RECT8_NV      0xEF
#وصف_ڪريو GL_RELATIVE_RECT_NV               0xF7
#وصف_ڪريو GL_FONT_GLYPHS_موجود_NV       0x9368
#وصف_ڪريو GL_FONT_هدف_UNAVAILABLE_NV     0x9369
#وصف_ڪريو GL_FONT_UNAVAILABLE_NV            0x936A
#وصف_ڪريو GL_FONT_UNINTELLIGIBLE_NV         0x936B
#وصف_ڪريو GL_CONIC_وڪر_منزل_NV              0x1A
#وصف_ڪريو GL_RELATIVE_CONIC_وڪر_منزل_NV     0x1B
#وصف_ڪريو GL_FONT_انگ_GLYPH_INDICES_ٻٽو_انگ_NV  0x20000000
#وصف_ڪريو GL_STANDARD_FONT_FORMAT_NV        0x936C
#وصف_ڪريو GL_رستو_PROJECTION_NV             0x1701
#وصف_ڪريو GL_رستو_MODELVIEW_NV              0x1700
#وصف_ڪريو GL_رستو_MODELVIEW_ڍير_اونهائي_NV  0x0BA3
#وصف_ڪريو GL_رستو_MODELVIEW_ميٽرڪس_NV       0x0BA6
#وصف_ڪريو GL_رستو_MAX_MODELVIEW_ڍير_اونهائي_NV 0x0D36
#وصف_ڪريو GL_رستو_TRANSPOSE_MODELVIEW_ميٽرڪس_NV 0x84E3
#وصف_ڪريو GL_رستو_PROJECTION_ڍير_اونهائي_NV 0x0BA4
#وصف_ڪريو GL_رستو_PROJECTION_ميٽرڪس_NV      0x0BA7
#وصف_ڪريو GL_رستو_MAX_PROJECTION_ڍير_اونهائي_NV 0x0D38
#وصف_ڪريو GL_رستو_TRANSPOSE_PROJECTION_ميٽرڪس_NV 0x84E4
#وصف_ڪريو GL_FRAGMENT_داخلا_NV              0x936D
تعريفنوع GLuint (GL_APIENTRYP PFNGLGENPATHSNVPROC) (GLsizei range);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEPATHSNVPROC) (GLuint رستو, GLsizei range);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISPATHNVPROC) (GLuint رستو);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHCOMMANDSNVPROC) (GLuint رستو, GLsizei انگ_Commands, ثابت GLubyte *commands, GLsizei انگ_Coords, GLenum coordType, ثابت فراغ *coords);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHCOORDSNVPROC) (GLuint رستو, GLsizei انگ_Coords, GLenum coordType, ثابت فراغ *coords);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHSUBCOMMANDSNVPROC) (GLuint رستو, GLsizei command_شروعات, GLsizei commands_منزل_Delete, GLsizei انگ_Commands, ثابت GLubyte *commands, GLsizei انگ_Coords, GLenum coordType, ثابت فراغ *coords);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHSUBCOORDSNVPROC) (GLuint رستو, GLsizei coord_شروعات, GLsizei انگ_Coords, GLenum coordType, ثابت فراغ *coords);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHSTRINGNVPROC) (GLuint رستو, GLenum format, GLsizei ڊيگهائي, ثابت فراغ *رستو_String);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHGLYPHSNVPROC) (GLuint پهريون_رستو_Name, GLenum font_هدف, ثابت فراغ *fontName, GLbitfield fontStyle, GLsizei انگ_Glyphs, GLenum type, ثابت فراغ *charcodes, GLenum handleMissingGlyphs, GLuint رستو_Parameter_Template, GLfloat emScale);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHGLYPHRANGENVPROC) (GLuint پهريون_رستو_Name, GLenum font_هدف, ثابت فراغ *fontName, GLbitfield fontStyle, GLuint پهريون_Glyph, GLsizei انگ_Glyphs, GLenum handleMissingGlyphs, GLuint رستو_Parameter_Template, GLfloat emScale);
تعريفنوع فراغ (GL_APIENTRYP PFNGLWEIGHTPATHSNVPROC) (GLuint نتيجو_رستو, GLsizei انگ_Paths, ثابت GLuint *paths, ثابت GLfloat *weights);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYPATHNVPROC) (GLuint نتيجو_رستو, GLuint src_رستو);
تعريفنوع فراغ (GL_APIENTRYP PFNGLINTERPOLATEPATHSNVPROC) (GLuint نتيجو_رستو, GLuint رستو_A, GLuint رستو_B, GLfloat وزن);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTRANSFORMPATHNVPROC) (GLuint نتيجو_رستو, GLuint src_رستو, GLenum transformType, ثابت GLfloat *transform_قدرون);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHPARAMETERIVNVPROC) (GLuint رستو, GLenum pname, ثابت GLint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHPARAMETERINVPROC) (GLuint رستو, GLenum pname, GLint قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHPARAMETERFVNVPROC) (GLuint رستو, GLenum pname, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHPARAMETERFNVPROC) (GLuint رستو, GLenum pname, GLfloat قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHDASHARRAYNVPROC) (GLuint رستو, GLsizei dash_ڳڻپ, ثابت GLfloat *dashArray);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHSTENCILFUNCNVPROC) (GLenum func, GLint ref, GLuint نقاب);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHSTENCILDEPTHOFFSETNVPROC) (GLfloat ضرب_ڪندڙ, GLfloat units);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILFILLPATHNVPROC) (GLuint رستو, GLenum fill_گهڻائي, GLuint نقاب);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILSTROKEPATHNVPROC) (GLuint رستو, GLint reference, GLuint نقاب);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILFILLPATHINSTANCEDNVPROC) (GLsizei انگ_Paths, GLenum رستو_Name_Type, ثابت فراغ *paths, GLuint رستو_بنياد, GLenum fill_گهڻائي, GLuint نقاب, GLenum transformType, ثابت GLfloat *transform_قدرون);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILSTROKEPATHINSTANCEDNVPROC) (GLsizei انگ_Paths, GLenum رستو_Name_Type, ثابت فراغ *paths, GLuint رستو_بنياد, GLint reference, GLuint نقاب, GLenum transformType, ثابت GLfloat *transform_قدرون);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHCOVERDEPTHFUNCNVPROC) (GLenum func);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOVERFILLPATHNVPROC) (GLuint رستو, GLenum cover_گهڻائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOVERSTROKEPATHNVPROC) (GLuint رستو, GLenum cover_گهڻائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOVERFILLPATHINSTANCEDNVPROC) (GLsizei انگ_Paths, GLenum رستو_Name_Type, ثابت فراغ *paths, GLuint رستو_بنياد, GLenum cover_گهڻائي, GLenum transformType, ثابت GLfloat *transform_قدرون);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOVERSTROKEPATHINSTANCEDNVPROC) (GLsizei انگ_Paths, GLenum رستو_Name_Type, ثابت فراغ *paths, GLuint رستو_بنياد, GLenum cover_گهڻائي, GLenum transformType, ثابت GLfloat *transform_قدرون);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPATHPARAMETERIVNVPROC) (GLuint رستو, GLenum pname, GLint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPATHPARAMETERFVNVPROC) (GLuint رستو, GLenum pname, GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPATHCOMMANDSNVPROC) (GLuint رستو, GLubyte *commands);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPATHCOORDSNVPROC) (GLuint رستو, GLfloat *coords);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPATHDASHARRAYNVPROC) (GLuint رستو, GLfloat *dashArray);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPATHMETRICSNVPROC) (GLbitfield metric_Query_نقاب, GLsizei انگ_Paths, GLenum رستو_Name_Type, ثابت فراغ *paths, GLuint رستو_بنياد, GLsizei stride, GLfloat *metrics);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPATHMETRICRANGENVPROC) (GLbitfield metric_Query_نقاب, GLuint پهريون_رستو_Name, GLsizei انگ_Paths, GLsizei stride, GLfloat *metrics);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPATHSPACINGNVPROC) (GLenum رستو_List_گهڻائي, GLsizei انگ_Paths, GLenum رستو_Name_Type, ثابت فراغ *paths, GLuint رستو_بنياد, GLfloat advanceScale, GLfloat kerningScale, GLenum transformType, GLfloat *returnedSpacing);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISPOINTINFILLPATHNVPROC) (GLuint رستو, GLuint نقاب, GLfloat x, GLfloat y);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISPOINTINSTROKEPATHNVPROC) (GLuint رستو, GLfloat x, GLfloat y);
تعريفنوع GLfloat (GL_APIENTRYP PFNGLGETPATHLENGTHNVPROC) (GLuint رستو, GLsizei شروعات_Segment, GLsizei انگ_Segments);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLPOINTALONGPATHNVPROC) (GLuint رستو, GLsizei شروعات_Segment, GLsizei انگ_Segments, GLfloat مفاصلو, GLfloat *x, GLfloat *y, GLfloat *tangentX, GLfloat *tangentY);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXLOAD3X2FNVPROC) (GLenum ميٽرڪس_گهڻائي, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXLOAD3X3FNVPROC) (GLenum ميٽرڪس_گهڻائي, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXLOADTRANSPOSE3X3FNVPROC) (GLenum ميٽرڪس_گهڻائي, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXMULT3X2FNVPROC) (GLenum ميٽرڪس_گهڻائي, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXMULT3X3FNVPROC) (GLenum ميٽرڪس_گهڻائي, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXMULTTRANSPOSE3X3FNVPROC) (GLenum ميٽرڪس_گهڻائي, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILTHENCOVERFILLPATHNVPROC) (GLuint رستو, GLenum fill_گهڻائي, GLuint نقاب, GLenum cover_گهڻائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILTHENCOVERSTROKEPATHNVPROC) (GLuint رستو, GLint reference, GLuint نقاب, GLenum cover_گهڻائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILTHENCOVERFILLPATHINSTANCEDNVPROC) (GLsizei انگ_Paths, GLenum رستو_Name_Type, ثابت فراغ *paths, GLuint رستو_بنياد, GLenum fill_گهڻائي, GLuint نقاب, GLenum cover_گهڻائي, GLenum transformType, ثابت GLfloat *transform_قدرون);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILTHENCOVERSTROKEPATHINSTANCEDNVPROC) (GLsizei انگ_Paths, GLenum رستو_Name_Type, ثابت فراغ *paths, GLuint رستو_بنياد, GLint reference, GLuint نقاب, GLenum cover_گهڻائي, GLenum transformType, ثابت GLfloat *transform_قدرون);
تعريفنوع GLenum (GL_APIENTRYP PFNGLPATHGLYPHINDEXRANGENVPROC) (GLenum font_هدف, ثابت فراغ *fontName, GLbitfield fontStyle, GLuint رستو_Parameter_Template, GLfloat emScale, GLuint *بنياد_And_ڳڻپ);
تعريفنوع GLenum (GL_APIENTRYP PFNGLPATHGLYPHINDEXARRAYNVPROC) (GLuint پهريون_رستو_Name, GLenum font_هدف, ثابت فراغ *fontName, GLbitfield fontStyle, GLuint پهريون_Glyph_اشاريو, GLsizei انگ_Glyphs, GLuint رستو_Parameter_Template, GLfloat emScale);
تعريفنوع GLenum (GL_APIENTRYP PFNGLPATHMEMORYGLYPHINDEXARRAYNVPROC) (GLuint پهريون_رستو_Name, GLenum font_هدف, GLsizeiptr font_سائيز, ثابت فراغ *font_معلومات, GLsizei face_اشاريو, GLuint پهريون_Glyph_اشاريو, GLsizei انگ_Glyphs, GLuint رستو_Parameter_Template, GLfloat emScale);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMPATHFRAGMENTINPUTGENNVPROC) (GLuint پروگرام, GLint location, GLenum gen_گهڻائي, GLint components, ثابت GLfloat *coeffs);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMRESOURCEFVNVPROC) (GLuint پروگرام, GLenum پروگرام_Interface, GLuint اشاريو, GLsizei prop_ڳڻپ, ثابت GLenum *props, GLsizei ڳڻپ, GLsizei *ڊيگهائي, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXFRUSTUMEXTPROC) (GLenum گهڻائي, GLdouble کاٻو, GLdouble ساڄو, GLdouble bottom, GLdouble چوٽي, GLdouble zNear, GLdouble zFar);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXLOADIDENTITYEXTPROC) (GLenum گهڻائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXLOADTRANSPOSEFEXTPROC) (GLenum گهڻائي, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXLOADTRANSPOSEDEXTPROC) (GLenum گهڻائي, ثابت GLdouble *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXLOADFEXTPROC) (GLenum گهڻائي, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXLOADDEXTPROC) (GLenum گهڻائي, ثابت GLdouble *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXMULTTRANSPOSEFEXTPROC) (GLenum گهڻائي, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXMULTTRANSPOSEDEXTPROC) (GLenum گهڻائي, ثابت GLdouble *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXMULTFEXTPROC) (GLenum گهڻائي, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXMULTDEXTPROC) (GLenum گهڻائي, ثابت GLdouble *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXORTHOEXTPROC) (GLenum گهڻائي, GLdouble کاٻو, GLdouble ساڄو, GLdouble bottom, GLdouble چوٽي, GLdouble zNear, GLdouble zFar);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXPOPEXTPROC) (GLenum گهڻائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXPUSHEXTPROC) (GLenum گهڻائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXROTATEFEXTPROC) (GLenum گهڻائي, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXROTATEDEXTPROC) (GLenum گهڻائي, GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXSCALEFEXTPROC) (GLenum گهڻائي, GLfloat x, GLfloat y, GLfloat z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXSCALEDEXTPROC) (GLenum گهڻائي, GLdouble x, GLdouble y, GLdouble z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXTRANSLATEFEXTPROC) (GLenum گهڻائي, GLfloat x, GLfloat y, GLfloat z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXTRANSLATEDEXTPROC) (GLenum گهڻائي, GLdouble x, GLdouble y, GLdouble z);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL GLuint GL_APIENTRY glGenPathsNV (GLsizei range);
GL_APICALL فراغ GL_APIENTRY glDeletePathsNV (GLuint رستو, GLsizei range);
GL_APICALL GLboolean GL_APIENTRY gl_Is_رستو_NV (GLuint رستو);
GL_APICALL فراغ GL_APIENTRY gl_رستو_Commands_NV (GLuint رستو, GLsizei انگ_Commands, ثابت GLubyte *commands, GLsizei انگ_Coords, GLenum coordType, ثابت فراغ *coords);
GL_APICALL فراغ GL_APIENTRY gl_رستو_Coords_NV (GLuint رستو, GLsizei انگ_Coords, GLenum coordType, ثابت فراغ *coords);
GL_APICALL فراغ GL_APIENTRY gl_رستو_Sub_Commands_NV (GLuint رستو, GLsizei command_شروعات, GLsizei commands_منزل_Delete, GLsizei انگ_Commands, ثابت GLubyte *commands, GLsizei انگ_Coords, GLenum coordType, ثابت فراغ *coords);
GL_APICALL فراغ GL_APIENTRY gl_رستو_Sub_Coords_NV (GLuint رستو, GLsizei coord_شروعات, GLsizei انگ_Coords, GLenum coordType, ثابت فراغ *coords);
GL_APICALL فراغ GL_APIENTRY gl_رستو_String_NV (GLuint رستو, GLenum format, GLsizei ڊيگهائي, ثابت فراغ *رستو_String);
GL_APICALL فراغ GL_APIENTRY gl_رستو_Glyphs_NV (GLuint پهريون_رستو_Name, GLenum font_هدف, ثابت فراغ *fontName, GLbitfield fontStyle, GLsizei انگ_Glyphs, GLenum type, ثابت فراغ *charcodes, GLenum handleMissingGlyphs, GLuint رستو_Parameter_Template, GLfloat emScale);
GL_APICALL فراغ GL_APIENTRY gl_رستو_Glyph_Range_NV (GLuint پهريون_رستو_Name, GLenum font_هدف, ثابت فراغ *fontName, GLbitfield fontStyle, GLuint پهريون_Glyph, GLsizei انگ_Glyphs, GLenum handleMissingGlyphs, GLuint رستو_Parameter_Template, GLfloat emScale);
GL_APICALL فراغ GL_APIENTRY gl_وزن_Paths_NV (GLuint نتيجو_رستو, GLsizei انگ_Paths, ثابت GLuint *paths, ثابت GLfloat *weights);
GL_APICALL فراغ GL_APIENTRY gl_Copy_رستو_NV (GLuint نتيجو_رستو, GLuint src_رستو);
GL_APICALL فراغ GL_APIENTRY glInterpolatePathsNV (GLuint نتيجو_رستو, GLuint رستو_A, GLuint رستو_B, GLfloat وزن);
GL_APICALL فراغ GL_APIENTRY gl_Transform_رستو_NV (GLuint نتيجو_رستو, GLuint src_رستو, GLenum transformType, ثابت GLfloat *transform_قدرون);
GL_APICALL فراغ GL_APIENTRY gl_رستو_Parameteriv_NV (GLuint رستو, GLenum pname, ثابت GLint *قدر);
GL_APICALL فراغ GL_APIENTRY gl_رستو_Parameteri_NV (GLuint رستو, GLenum pname, GLint قدر);
GL_APICALL فراغ GL_APIENTRY gl_رستو_Parameterfv_NV (GLuint رستو, GLenum pname, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_رستو_Parameterf_NV (GLuint رستو, GLenum pname, GLfloat قدر);
GL_APICALL فراغ GL_APIENTRY gl_رستو_Dash_Array_NV (GLuint رستو, GLsizei dash_ڳڻپ, ثابت GLfloat *dashArray);
GL_APICALL فراغ GL_APIENTRY gl_رستو_Stencil_Func_NV (GLenum func, GLint ref, GLuint نقاب);
GL_APICALL فراغ GL_APIENTRY gl_رستو_Stencil_اونهائي_وٿي_NV (GLfloat ضرب_ڪندڙ, GLfloat units);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_Fill_رستو_NV (GLuint رستو, GLenum fill_گهڻائي, GLuint نقاب);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_Stroke_رستو_NV (GLuint رستو, GLint reference, GLuint نقاب);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_Fill_رستو_Instanced_NV (GLsizei انگ_Paths, GLenum رستو_Name_Type, ثابت فراغ *paths, GLuint رستو_بنياد, GLenum fill_گهڻائي, GLuint نقاب, GLenum transformType, ثابت GLfloat *transform_قدرون);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_Stroke_رستو_Instanced_NV (GLsizei انگ_Paths, GLenum رستو_Name_Type, ثابت فراغ *paths, GLuint رستو_بنياد, GLint reference, GLuint نقاب, GLenum transformType, ثابت GLfloat *transform_قدرون);
GL_APICALL فراغ GL_APIENTRY gl_رستو_Cover_اونهائي_Func_NV (GLenum func);
GL_APICALL فراغ GL_APIENTRY gl_Cover_Fill_رستو_NV (GLuint رستو, GLenum cover_گهڻائي);
GL_APICALL فراغ GL_APIENTRY gl_Cover_Stroke_رستو_NV (GLuint رستو, GLenum cover_گهڻائي);
GL_APICALL فراغ GL_APIENTRY gl_Cover_Fill_رستو_Instanced_NV (GLsizei انگ_Paths, GLenum رستو_Name_Type, ثابت فراغ *paths, GLuint رستو_بنياد, GLenum cover_گهڻائي, GLenum transformType, ثابت GLfloat *transform_قدرون);
GL_APICALL فراغ GL_APIENTRY gl_Cover_Stroke_رستو_Instanced_NV (GLsizei انگ_Paths, GLenum رستو_Name_Type, ثابت فراغ *paths, GLuint رستو_بنياد, GLenum cover_گهڻائي, GLenum transformType, ثابت GLfloat *transform_قدرون);
GL_APICALL فراغ GL_APIENTRY gl_Get_رستو_Parameteriv_NV (GLuint رستو, GLenum pname, GLint *قدر);
GL_APICALL فراغ GL_APIENTRY gl_Get_رستو_Parameterfv_NV (GLuint رستو, GLenum pname, GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_Get_رستو_Commands_NV (GLuint رستو, GLubyte *commands);
GL_APICALL فراغ GL_APIENTRY gl_Get_رستو_Coords_NV (GLuint رستو, GLfloat *coords);
GL_APICALL فراغ GL_APIENTRY gl_Get_رستو_Dash_Array_NV (GLuint رستو, GLfloat *dashArray);
GL_APICALL فراغ GL_APIENTRY gl_Get_رستو_Metrics_NV (GLbitfield metric_Query_نقاب, GLsizei انگ_Paths, GLenum رستو_Name_Type, ثابت فراغ *paths, GLuint رستو_بنياد, GLsizei stride, GLfloat *metrics);
GL_APICALL فراغ GL_APIENTRY gl_Get_رستو_Metric_Range_NV (GLbitfield metric_Query_نقاب, GLuint پهريون_رستو_Name, GLsizei انگ_Paths, GLsizei stride, GLfloat *metrics);
GL_APICALL فراغ GL_APIENTRY gl_Get_رستو_Spacing_NV (GLenum رستو_List_گهڻائي, GLsizei انگ_Paths, GLenum رستو_Name_Type, ثابت فراغ *paths, GLuint رستو_بنياد, GLfloat advanceScale, GLfloat kerningScale, GLenum transformType, GLfloat *returnedSpacing);
GL_APICALL GLboolean GL_APIENTRY gl_Is_نقطو_اندريون_Fill_رستو_NV (GLuint رستو, GLuint نقاب, GLfloat x, GLfloat y);
GL_APICALL GLboolean GL_APIENTRY gl_Is_نقطو_اندريون_Stroke_رستو_NV (GLuint رستو, GLfloat x, GLfloat y);
GL_APICALL GLfloat GL_APIENTRY gl_Get_رستو_ڊيگهائي_NV (GLuint رستو, GLsizei شروعات_Segment, GLsizei انگ_Segments);
GL_APICALL GLboolean GL_APIENTRY gl_نقطو_Along_رستو_NV (GLuint رستو, GLsizei شروعات_Segment, GLsizei انگ_Segments, GLfloat مفاصلو, GLfloat *x, GLfloat *y, GLfloat *tangentX, GLfloat *tangentY);
GL_APICALL فراغ GL_APIENTRY gl_ميٽرڪس_Load3x2f_NV (GLenum ميٽرڪس_گهڻائي, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_ميٽرڪس_Load3x3f_NV (GLenum ميٽرڪس_گهڻائي, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_ميٽرڪس_ڀريو_Transpose3x3f_NV (GLenum ميٽرڪس_گهڻائي, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_ميٽرڪس_Mult3x2f_NV (GLenum ميٽرڪس_گهڻائي, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_ميٽرڪس_Mult3x3f_NV (GLenum ميٽرڪس_گهڻائي, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_ميٽرڪس_Mult_Transpose3x3f_NV (GLenum ميٽرڪس_گهڻائي, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_Then_Cover_Fill_رستو_NV (GLuint رستو, GLenum fill_گهڻائي, GLuint نقاب, GLenum cover_گهڻائي);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_Then_Cover_Stroke_رستو_NV (GLuint رستو, GLint reference, GLuint نقاب, GLenum cover_گهڻائي);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_Then_Cover_Fill_رستو_Instanced_NV (GLsizei انگ_Paths, GLenum رستو_Name_Type, ثابت فراغ *paths, GLuint رستو_بنياد, GLenum fill_گهڻائي, GLuint نقاب, GLenum cover_گهڻائي, GLenum transformType, ثابت GLfloat *transform_قدرون);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_Then_Cover_Stroke_رستو_Instanced_NV (GLsizei انگ_Paths, GLenum رستو_Name_Type, ثابت فراغ *paths, GLuint رستو_بنياد, GLint reference, GLuint نقاب, GLenum cover_گهڻائي, GLenum transformType, ثابت GLfloat *transform_قدرون);
GL_APICALL GLenum GL_APIENTRY gl_رستو_Glyph_اشاريو_Range_NV (GLenum font_هدف, ثابت فراغ *fontName, GLbitfield fontStyle, GLuint رستو_Parameter_Template, GLfloat emScale, GLuint *بنياد_And_ڳڻپ);
GL_APICALL GLenum GL_APIENTRY gl_رستو_Glyph_اشاريو_Array_NV (GLuint پهريون_رستو_Name, GLenum font_هدف, ثابت فراغ *fontName, GLbitfield fontStyle, GLuint پهريون_Glyph_اشاريو, GLsizei انگ_Glyphs, GLuint رستو_Parameter_Template, GLfloat emScale);
GL_APICALL GLenum GL_APIENTRY gl_رستو_يادگيري_Glyph_اشاريو_Array_NV (GLuint پهريون_رستو_Name, GLenum font_هدف, GLsizeiptr font_سائيز, ثابت فراغ *font_معلومات, GLsizei face_اشاريو, GLuint پهريون_Glyph_اشاريو, GLsizei انگ_Glyphs, GLuint رستو_Parameter_Template, GLfloat emScale);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_رستو_Fragment_داخلا_Gen_NV (GLuint پروگرام, GLint location, GLenum gen_گهڻائي, GLint components, ثابت GLfloat *coeffs);
GL_APICALL فراغ GL_APIENTRY gl_Get_پروگرام_Resourcefv_NV (GLuint پروگرام, GLenum پروگرام_Interface, GLuint اشاريو, GLsizei prop_ڳڻپ, ثابت GLenum *props, GLsizei ڳڻپ, GLsizei *ڊيگهائي, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY gl_ميٽرڪس_Frustum_EXT (GLenum گهڻائي, GLdouble کاٻو, GLdouble ساڄو, GLdouble bottom, GLdouble چوٽي, GLdouble zNear, GLdouble zFar);
GL_APICALL فراغ GL_APIENTRY gl_ميٽرڪس_ڀريو_سڃاڻپ_عنصر_EXT (GLenum گهڻائي);
GL_APICALL فراغ GL_APIENTRY gl_ميٽرڪس_ڀريو_Transposef_EXT (GLenum گهڻائي, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_ميٽرڪس_ڀريو_Transposed_EXT (GLenum گهڻائي, ثابت GLdouble *m);
GL_APICALL فراغ GL_APIENTRY gl_ميٽرڪس_Loadf_EXT (GLenum گهڻائي, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_ميٽرڪس_Loadd_EXT (GLenum گهڻائي, ثابت GLdouble *m);
GL_APICALL فراغ GL_APIENTRY gl_ميٽرڪس_Mult_Transposef_EXT (GLenum گهڻائي, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_ميٽرڪس_Mult_Transposed_EXT (GLenum گهڻائي, ثابت GLdouble *m);
GL_APICALL فراغ GL_APIENTRY gl_ميٽرڪس_Multf_EXT (GLenum گهڻائي, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_ميٽرڪس_Multd_EXT (GLenum گهڻائي, ثابت GLdouble *m);
GL_APICALL فراغ GL_APIENTRY gl_ميٽرڪس_Ortho_EXT (GLenum گهڻائي, GLdouble کاٻو, GLdouble ساڄو, GLdouble bottom, GLdouble چوٽي, GLdouble zNear, GLdouble zFar);
GL_APICALL فراغ GL_APIENTRY gl_ميٽرڪس_ڪڍو_EXT (GLenum گهڻائي);
GL_APICALL فراغ GL_APIENTRY gl_ميٽرڪس_ڌڪو_EXT (GLenum گهڻائي);
GL_APICALL فراغ GL_APIENTRY gl_ميٽرڪس_Rotatef_EXT (GLenum گهڻائي, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL فراغ GL_APIENTRY gl_ميٽرڪس_Rotated_EXT (GLenum گهڻائي, GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
GL_APICALL فراغ GL_APIENTRY gl_ميٽرڪس_Scalef_EXT (GLenum گهڻائي, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL فراغ GL_APIENTRY gl_ميٽرڪس_Scaled_EXT (GLenum گهڻائي, GLdouble x, GLdouble y, GLdouble z);
GL_APICALL فراغ GL_APIENTRY gl_ميٽرڪس_Translatef_EXT (GLenum گهڻائي, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL فراغ GL_APIENTRY gl_ميٽرڪس_Translated_EXT (GLenum گهڻائي, GLdouble x, GLdouble y, GLdouble z);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_NV_path_rendering */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_رستو_rendering_shared_ڪنارو
#وصف_ڪريو GL_NV_رستو_rendering_shared_ڪنارو 1
#وصف_ڪريو GL_SHARED_ڪنارو_NV                 0xC0
#جيڪڏهن_پورو /* GL_NV_path_rendering_shared_edge */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_pixel_بفر_object
#وصف_ڪريو GL_NV_pixel_بفر_object 1
#وصف_ڪريو GL_PIXEL_PACK_بفر_NV           0x88EB
#وصف_ڪريو GL_PIXEL_UNPACK_بفر_NV         0x88EC
#وصف_ڪريو GL_PIXEL_PACK_بفر_BINDING_NV   0x88ED
#وصف_ڪريو GL_PIXEL_UNPACK_بفر_BINDING_NV 0x88EF
#جيڪڏهن_پورو /* GL_NV_pixel_buffer_object */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_polygon_گهڻائي
#وصف_ڪريو GL_NV_polygon_گهڻائي 1
#وصف_ڪريو GL_POLYGON_گهڻائي_NV                0x0B40
#وصف_ڪريو GL_POLYGON_وٿي_نقطو_NV        0x2A01
#وصف_ڪريو GL_POLYGON_وٿي_سٽ_NV         0x2A02
#وصف_ڪريو GL_نقطو_NV                       0x1B00
#وصف_ڪريو GL_سٽ_NV                        0x1B01
#وصف_ڪريو GL_FILL_NV                        0x1B02
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOLYGONMODENVPROC) (GLenum face, GLenum گهڻائي);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Polygon_گهڻائي_NV (GLenum face, GLenum گهڻائي);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_NV_polygon_mode */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_primitive_shading_شرح
#وصف_ڪريو GL_NV_primitive_shading_شرح 1
#وصف_ڪريو GL_SHADING_شرح_IMAGE_في_PRIMITIVE_NV 0x95B1
#وصف_ڪريو GL_SHADING_شرح_IMAGE_PALETTE_ڳڻپ_NV 0x95B2
#جيڪڏهن_پورو /* GL_NV_primitive_shading_rate */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_read_بفر
#وصف_ڪريو GL_NV_read_بفر 1
#وصف_ڪريو GL_READ_بفر_NV                 0x0C02
تعريفنوع فراغ (GL_APIENTRYP PFNGLREADBUFFERNVPROC) (GLenum گهڻائي);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Read_بفر_NV (GLenum گهڻائي);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_NV_read_buffer */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_read_بفر_front
#وصف_ڪريو GL_NV_read_بفر_front 1
#جيڪڏهن_پورو /* GL_NV_read_buffer_front */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_read_اونهائي
#وصف_ڪريو GL_NV_read_اونهائي 1
#جيڪڏهن_پورو /* GL_NV_read_depth */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_read_اونهائي_stencil
#وصف_ڪريو GL_NV_read_اونهائي_stencil 1
#جيڪڏهن_پورو /* GL_NV_read_depth_stencil */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_read_stencil
#وصف_ڪريو GL_NV_read_stencil 1
#جيڪڏهن_پورو /* GL_NV_read_stencil */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_representative_fragment_test
#وصف_ڪريو GL_NV_representative_fragment_test 1
#وصف_ڪريو GL_REPRESENTATIVE_FRAGMENT_TEST_NV 0x937F
#جيڪڏهن_پورو /* GL_NV_representative_fragment_test */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_sRGB_formats
#وصف_ڪريو GL_NV_sRGB_formats 1
#وصف_ڪريو GL_SLUMINANCE_NV                  0x8C46
#وصف_ڪريو GL_SLUMINANCE_ALPHA_NV            0x8C44
#وصف_ڪريو GL_SRGB8_NV                       0x8C41
#وصف_ڪريو GL_SLUMINANCE8_NV                 0x8C47
#وصف_ڪريو GL_SLUMINANCE8_ALPHA8_NV          0x8C45
#وصف_ڪريو GL_COMPRESSED_SRGB_S3TC_DXT1_NV   0x8C4C
#وصف_ڪريو GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_NV 0x8C4D
#وصف_ڪريو GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_NV 0x8C4E
#وصف_ڪريو GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_NV 0x8C4F
#وصف_ڪريو GL_ETC1_SRGB8_NV                  0x88EE
#جيڪڏهن_پورو /* GL_NV_sRGB_formats */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_sample_locations
#وصف_ڪريو GL_NV_sample_locations 1
#وصف_ڪريو GL_SAMPLE_LOCATION_SUBPIXEL_بٽ_NV 0x933D
#وصف_ڪريو GL_SAMPLE_LOCATION_PIXEL_GRID_ويڪر_NV 0x933E
#وصف_ڪريو GL_SAMPLE_LOCATION_PIXEL_GRID_اوچائي_NV 0x933F
#وصف_ڪريو GL_PROGRAMMABLE_SAMPLE_LOCATION_جدول_سائيز_NV 0x9340
#وصف_ڪريو GL_SAMPLE_LOCATION_NV             0x8E50
#وصف_ڪريو GL_PROGRAMMABLE_SAMPLE_LOCATION_NV 0x9341
#وصف_ڪريو GL_FRAMEBUFFER_PROGRAMMABLE_SAMPLE_LOCATIONS_NV 0x9342
#وصف_ڪريو GL_FRAMEBUFFER_SAMPLE_LOCATION_PIXEL_GRID_NV 0x9343
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERSAMPLELOCATIONSFVNVPROC) (GLenum هدف, GLuint شروعات, GLsizei ڳڻپ, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVNVPROC) (GLuint framebuffer, GLuint شروعات, GLsizei ڳڻپ, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRESOLVEDEPTHVALUESNVPROC) (فراغ);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferSampleLocationsfvNV (GLenum هدف, GLuint شروعات, GLsizei ڳڻپ, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY glNamedFramebufferSampleLocationsfvNV (GLuint framebuffer, GLuint شروعات, GLsizei ڳڻپ, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY gl_Resolve_اونهائي_قدرون_NV (فراغ);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_NV_sample_locations */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_sample_نقاب_override_coverage
#وصف_ڪريو GL_NV_sample_نقاب_override_coverage 1
#جيڪڏهن_پورو /* GL_NV_sample_mask_override_coverage */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_scissor_exclusive
#وصف_ڪريو GL_NV_scissor_exclusive 1
#وصف_ڪريو GL_SCISSOR_TEST_EXCLUSIVE_NV      0x9555
#وصف_ڪريو GL_SCISSOR_BOX_EXCLUSIVE_NV       0x9556
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSOREXCLUSIVENVPROC) (GLint x, GLint y, GLsizei ويڪر, GLsizei اوچائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSOREXCLUSIVEARRAYVNVPROC) (GLuint پهريون, GLsizei ڳڻپ, ثابت GLint *v);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glScissorExclusiveNV (GLint x, GLint y, GLsizei ويڪر, GLsizei اوچائي);
GL_APICALL فراغ GL_APIENTRY glScissorExclusiveArrayvNV (GLuint پهريون, GLsizei ڳڻپ, ثابت GLint *v);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_NV_scissor_exclusive */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_shader_atomic_fp16_ويڪٽر
#وصف_ڪريو GL_NV_shader_atomic_fp16_ويڪٽر 1
#جيڪڏهن_پورو /* GL_NV_shader_atomic_fp16_vector */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_shader_noperspective_interpolation
#وصف_ڪريو GL_NV_shader_noperspective_interpolation 1
#جيڪڏهن_پورو /* GL_NV_shader_noperspective_interpolation */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_shader_subgroup_partitioned
#وصف_ڪريو GL_NV_shader_subgroup_partitioned 1
#وصف_ڪريو GL_SUBGROUP_FEATURE_PARTITIONED_ٻٽو_انگ_NV 0x00000100
#جيڪڏهن_پورو /* GL_NV_shader_subgroup_partitioned */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_shader_texture_footprint
#وصف_ڪريو GL_NV_shader_texture_footprint 1
#جيڪڏهن_پورو /* GL_NV_shader_texture_footprint */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_shading_شرح_image
#وصف_ڪريو GL_NV_shading_شرح_image 1
#وصف_ڪريو GL_SHADING_شرح_IMAGE_NV          0x9563
#وصف_ڪريو GL_SHADING_شرح_NO_INVOCATIONS_NV 0x9564
#وصف_ڪريو GL_SHADING_شرح_1_INVOCATION_في_PIXEL_NV 0x9565
#وصف_ڪريو GL_SHADING_شرح_1_INVOCATION_في_1_X2_PIXELS_NV 0x9566
#وصف_ڪريو GL_SHADING_شرح_1_INVOCATION_في_2_X1_PIXELS_NV 0x9567
#وصف_ڪريو GL_SHADING_شرح_1_INVOCATION_في_2_X2_PIXELS_NV 0x9568
#وصف_ڪريو GL_SHADING_شرح_1_INVOCATION_في_2_X4_PIXELS_NV 0x9569
#وصف_ڪريو GL_SHADING_شرح_1_INVOCATION_في_4_X2_PIXELS_NV 0x956A
#وصف_ڪريو GL_SHADING_شرح_1_INVOCATION_في_4_X4_PIXELS_NV 0x956B
#وصف_ڪريو GL_SHADING_شرح_2_INVOCATIONS_في_PIXEL_NV 0x956C
#وصف_ڪريو GL_SHADING_شرح_4_INVOCATIONS_في_PIXEL_NV 0x956D
#وصف_ڪريو GL_SHADING_شرح_8_INVOCATIONS_في_PIXEL_NV 0x956E
#وصف_ڪريو GL_SHADING_شرح_16_INVOCATIONS_في_PIXEL_NV 0x956F
#وصف_ڪريو GL_SHADING_شرح_IMAGE_BINDING_NV  0x955B
#وصف_ڪريو GL_SHADING_شرح_IMAGE_TEXEL_ويڪر_NV 0x955C
#وصف_ڪريو GL_SHADING_شرح_IMAGE_TEXEL_اوچائي_NV 0x955D
#وصف_ڪريو GL_SHADING_شرح_IMAGE_PALETTE_سائيز_NV 0x955E
#وصف_ڪريو GL_MAX_COARSE_FRAGMENT_SAMPLES_NV 0x955F
#وصف_ڪريو GL_SHADING_شرح_SAMPLE_ترتيب_DEFAULT_NV 0x95AE
#وصف_ڪريو GL_SHADING_شرح_SAMPLE_ترتيب_PIXEL_MAJOR_NV 0x95AF
#وصف_ڪريو GL_SHADING_شرح_SAMPLE_ترتيب_SAMPLE_MAJOR_NV 0x95B0
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDSHADINGRATEIMAGENVPROC) (GLuint texture);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSHADINGRATEIMAGEPALETTENVPROC) (GLuint viewport, GLuint داخلا, GLenum *شرح);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSHADINGRATESAMPLELOCATIONIVNVPROC) (GLenum شرح, GLuint samples, GLuint اشاريو, GLint *location);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADINGRATEIMAGEBARRIERNVPROC) (GLboolean synchronize);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADINGRATEIMAGEPALETTENVPROC) (GLuint viewport, GLuint پهريون, GLsizei ڳڻپ, ثابت GLenum *rates);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADINGRATESAMPLEORDERNVPROC) (GLenum ترتيب);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADINGRATESAMPLEORDERCUSTOMNVPROC) (GLenum شرح, GLuint samples, ثابت GLint *locations);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Bind_Shading_شرح_Image_NV (GLuint texture);
GL_APICALL فراغ GL_APIENTRY gl_Get_Shading_شرح_Image_Palette_NV (GLuint viewport, GLuint داخلا, GLenum *شرح);
GL_APICALL فراغ GL_APIENTRY gl_Get_Shading_شرح_Sample_Locationiv_NV (GLenum شرح, GLuint samples, GLuint اشاريو, GLint *location);
GL_APICALL فراغ GL_APIENTRY gl_Shading_شرح_Image_Barrier_NV (GLboolean synchronize);
GL_APICALL فراغ GL_APIENTRY gl_Shading_شرح_Image_Palette_NV (GLuint viewport, GLuint پهريون, GLsizei ڳڻپ, ثابت GLenum *rates);
GL_APICALL فراغ GL_APIENTRY gl_Shading_شرح_Sample_ترتيب_NV (GLenum ترتيب);
GL_APICALL فراغ GL_APIENTRY gl_Shading_شرح_Sample_ترتيب_Custom_NV (GLenum شرح, GLuint samples, ثابت GLint *locations);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_NV_shading_rate_image */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_shadow_samplers_array
#وصف_ڪريو GL_NV_shadow_samplers_array 1
#وصف_ڪريو GL_SAMPLER_2D_ARRAY_SHADOW_NV     0x8DC4
#جيڪڏهن_پورو /* GL_NV_shadow_samplers_array */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_shadow_samplers_cube
#وصف_ڪريو GL_NV_shadow_samplers_cube 1
#وصف_ڪريو GL_SAMPLER_CUBE_SHADOW_NV         0x8DC5
#جيڪڏهن_پورو /* GL_NV_shadow_samplers_cube */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_stereo_view_rendering
#وصف_ڪريو GL_NV_stereo_view_rendering 1
#جيڪڏهن_پورو /* GL_NV_stereo_view_rendering */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_texture_barrier
#وصف_ڪريو GL_NV_texture_barrier 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTUREBARRIERNVPROC) (فراغ);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTextureBarrierNV (فراغ);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_NV_texture_barrier */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_texture_border_clamp
#وصف_ڪريو GL_NV_texture_border_clamp 1
#وصف_ڪريو GL_TEXTURE_BORDER_COLOR_NV        0x1004
#وصف_ڪريو GL_CLAMP_منزل_BORDER_NV             0x812D
#جيڪڏهن_پورو /* GL_NV_texture_border_clamp */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_texture_compression_s3tc_update
#وصف_ڪريو GL_NV_texture_compression_s3tc_update 1
#جيڪڏهن_پورو /* GL_NV_texture_compression_s3tc_update */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_texture_npot_2D_mipmap
#وصف_ڪريو GL_NV_texture_npot_2D_mipmap 1
#جيڪڏهن_پورو /* GL_NV_texture_npot_2D_mipmap */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_timeline_semaphore
#وصف_ڪريو GL_NV_timeline_semaphore 1
#وصف_ڪريو GL_TIMELINE_SEMAPHORE_قدر_NV    0x9595
#وصف_ڪريو GL_SEMAPHORE_TYPE_NV              0x95B3
#وصف_ڪريو GL_SEMAPHORE_TYPE_ٻٽو_NV       0x95B4
#وصف_ڪريو GL_SEMAPHORE_TYPE_TIMELINE_NV     0x95B5
#وصف_ڪريو GL_MAX_TIMELINE_SEMAPHORE_قدر_DIFFERENCE_NV 0x95B6
تعريفنوع فراغ (GL_APIENTRYP PFNGLCREATESEMAPHORESNVPROC) (GLsizei n, GLuint *semaphores);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSEMAPHOREPARAMETERIVNVPROC) (GLuint semaphore, GLenum pname, ثابت GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSEMAPHOREPARAMETERIVNVPROC) (GLuint semaphore, GLenum pname, GLint *params);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glCreateSemaphoresNV (GLsizei n, GLuint *semaphores);
GL_APICALL فراغ GL_APIENTRY glSemaphoreParameterivNV (GLuint semaphore, GLenum pname, ثابت GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetSemaphoreParameterivNV (GLuint semaphore, GLenum pname, GLint *params);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_NV_timeline_semaphore */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_viewport_array
#وصف_ڪريو GL_NV_viewport_array 1
#وصف_ڪريو GL_MAX_VIEWPORTS_NV               0x825B
#وصف_ڪريو GL_VIEWPORT_SUBPIXEL_بٽ_NV      0x825C
#وصف_ڪريو GL_VIEWPORT_BOUNDS_RANGE_NV       0x825D
#وصف_ڪريو GL_VIEWPORT_اشاريو_PROVOKING_راس_NV 0x825F
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTARRAYVNVPROC) (GLuint پهريون, GLsizei ڳڻپ, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTINDEXEDFNVPROC) (GLuint اشاريو, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTINDEXEDFVNVPROC) (GLuint اشاريو, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSORARRAYVNVPROC) (GLuint پهريون, GLsizei ڳڻپ, ثابت GLint *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSORINDEXEDNVPROC) (GLuint اشاريو, GLint کاٻو, GLint bottom, GLsizei ويڪر, GLsizei اوچائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSORINDEXEDVNVPROC) (GLuint اشاريو, ثابت GLint *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHRANGEARRAYFVNVPROC) (GLuint پهريون, GLsizei ڳڻپ, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHRANGEINDEXEDFNVPROC) (GLuint اشاريو, GLfloat n, GLfloat f);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFLOATI_VNVPROC) (GLenum هدف, GLuint اشاريو, GLfloat *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENABLEINVPROC) (GLenum هدف, GLuint اشاريو);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISABLEINVPROC) (GLenum هدف, GLuint اشاريو);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISENABLEDINVPROC) (GLenum هدف, GLuint اشاريو);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glViewportArrayvNV (GLuint پهريون, GLsizei ڳڻپ, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY glViewportIndexedfNV (GLuint اشاريو, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
GL_APICALL فراغ GL_APIENTRY glViewportIndexedfvNV (GLuint اشاريو, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY glScissorArrayvNV (GLuint پهريون, GLsizei ڳڻپ, ثابت GLint *v);
GL_APICALL فراغ GL_APIENTRY gl_Scissor_اشاريي_وارو_NV (GLuint اشاريو, GLint کاٻو, GLint bottom, GLsizei ويڪر, GLsizei اوچائي);
GL_APICALL فراغ GL_APIENTRY glScissorIndexedvNV (GLuint اشاريو, ثابت GLint *v);
GL_APICALL فراغ GL_APIENTRY gl_اونهائي_Range_Arrayfv_NV (GLuint پهريون, GLsizei ڳڻپ, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY gl_اونهائي_Range_Indexedf_NV (GLuint اشاريو, GLfloat n, GLfloat f);
GL_APICALL فراغ GL_APIENTRY glGetFloati_vNV (GLenum هدف, GLuint اشاريو, GLfloat *معلومات);
GL_APICALL فراغ GL_APIENTRY glEnableiNV (GLenum هدف, GLuint اشاريو);
GL_APICALL فراغ GL_APIENTRY glDisableiNV (GLenum هدف, GLuint اشاريو);
GL_APICALL GLboolean GL_APIENTRY glIsEnablediNV (GLenum هدف, GLuint اشاريو);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_NV_viewport_array */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_viewport_array2
#وصف_ڪريو GL_NV_viewport_array2 1
#جيڪڏهن_پورو /* GL_NV_viewport_array2 */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_viewport_swizzle
#وصف_ڪريو GL_NV_viewport_swizzle 1
#وصف_ڪريو GL_VIEWPORT_SWIZZLE_مثبت_X_NV 0x9350
#وصف_ڪريو GL_VIEWPORT_SWIZZLE_NEGATIVE_X_NV 0x9351
#وصف_ڪريو GL_VIEWPORT_SWIZZLE_مثبت_Y_NV 0x9352
#وصف_ڪريو GL_VIEWPORT_SWIZZLE_NEGATIVE_Y_NV 0x9353
#وصف_ڪريو GL_VIEWPORT_SWIZZLE_مثبت_Z_NV 0x9354
#وصف_ڪريو GL_VIEWPORT_SWIZZLE_NEGATIVE_Z_NV 0x9355
#وصف_ڪريو GL_VIEWPORT_SWIZZLE_مثبت_W_NV 0x9356
#وصف_ڪريو GL_VIEWPORT_SWIZZLE_NEGATIVE_W_NV 0x9357
#وصف_ڪريو GL_VIEWPORT_SWIZZLE_X_NV          0x9358
#وصف_ڪريو GL_VIEWPORT_SWIZZLE_Y_NV          0x9359
#وصف_ڪريو GL_VIEWPORT_SWIZZLE_Z_NV          0x935A
#وصف_ڪريو GL_VIEWPORT_SWIZZLE_W_NV          0x935B
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTSWIZZLENVPROC) (GLuint اشاريو, GLenum swizzlex, GLenum swizzley, GLenum swizzlez, GLenum swizzlew);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glViewportSwizzleNV (GLuint اشاريو, GLenum swizzlex, GLenum swizzley, GLenum swizzlez, GLenum swizzlew);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_NV_viewport_swizzle */

#جيڪڏهن_وصف_نه_ٿيل GL_OVR_multiview
#وصف_ڪريو GL_OVR_multiview 1
#وصف_ڪريو GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_انگ_VIEWS_OVR 0x9630
#وصف_ڪريو GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_بنياد_VIEW_اشاريو_OVR 0x9632
#وصف_ڪريو GL_MAX_VIEWS_OVR                  0x9631
#وصف_ڪريو GL_FRAMEBUFFER_INCOMPLETE_VIEW_TARGETS_OVR 0x9633
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREMULTIVIEWOVRPROC) (GLenum هدف, GLenum attachment, GLuint texture, GLint level, GLint بنياد_View_اشاريو, GLsizei انگ_Views_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLNAMEDFRAMEBUFFERTEXTUREMULTIVIEWOVRPROC) (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint بنياد_View_اشاريو, GLsizei انگ_Views_2);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferTextureMultiviewOVR (GLenum هدف, GLenum attachment, GLuint texture, GLint level, GLint بنياد_View_اشاريو, GLsizei انگ_Views_2);
GL_APICALL فراغ GL_APIENTRY glNamedFramebufferTextureMultiviewOVR (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint بنياد_View_اشاريو, GLsizei انگ_Views_2);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_OVR_multiview */

#جيڪڏهن_وصف_نه_ٿيل GL_OVR_multiview2
#وصف_ڪريو GL_OVR_multiview2 1
#جيڪڏهن_پورو /* GL_OVR_multiview2 */

#جيڪڏهن_وصف_نه_ٿيل GL_OVR_multiview_multisampled_render_منزل_texture
#وصف_ڪريو GL_OVR_multiview_multisampled_render_منزل_texture 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREMULTISAMPLEMULTIVIEWOVRPROC) (GLenum هدف, GLenum attachment, GLuint texture, GLint level, GLsizei samples, GLint بنياد_View_اشاريو, GLsizei انگ_Views_2);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferTextureMultisampleMultiviewOVR (GLenum هدف, GLenum attachment, GLuint texture, GLint level, GLsizei samples, GLint بنياد_View_اشاريو, GLsizei انگ_Views_2);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_OVR_multiview_multisampled_render_to_texture */

#جيڪڏهن_وصف_نه_ٿيل GL_QCOM_YUV_texture_gather
#وصف_ڪريو GL_QCOM_YUV_texture_gather 1
#جيڪڏهن_پورو /* GL_QCOM_YUV_texture_gather */

#جيڪڏهن_وصف_نه_ٿيل GL_QCOM_alpha_test
#وصف_ڪريو GL_QCOM_alpha_test 1
#وصف_ڪريو GL_ALPHA_TEST_QCOM                0x0BC0
#وصف_ڪريو GL_ALPHA_TEST_FUNC_QCOM           0x0BC1
#وصف_ڪريو GL_ALPHA_TEST_REF_QCOM            0x0BC2
تعريفنوع فراغ (GL_APIENTRYP PFNGLALPHAFUNCQCOMPROC) (GLenum func, GLclampf ref);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glAlphaFuncQCOM (GLenum func, GLclampf ref);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_QCOM_alpha_test */

#جيڪڏهن_وصف_نه_ٿيل GL_QCOM_binning_control
#وصف_ڪريو GL_QCOM_binning_control 1
#وصف_ڪريو GL_BINNING_CONTROL_HINT_QCOM      0x8FB0
#وصف_ڪريو GL_CPU_OPTIMIZED_QCOM             0x8FB1
#وصف_ڪريو GL_GPU_OPTIMIZED_QCOM             0x8FB2
#وصف_ڪريو GL_RENDER_سڌو_منزل_FRAMEBUFFER_QCOM 0x8FB3
#جيڪڏهن_پورو /* GL_QCOM_binning_control */

#جيڪڏهن_وصف_نه_ٿيل GL_QCOM_driver_control
#وصف_ڪريو GL_QCOM_driver_control 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETDRIVERCONTROLSQCOMPROC) (GLint *انگ, GLsizei سائيز, GLuint *driverControls);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETDRIVERCONTROLSTRINGQCOMPROC) (GLuint driverControl, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLchar *driverControlString);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glGetDriverControlsQCOM (GLint *انگ, GLsizei سائيز, GLuint *driverControls);
GL_APICALL فراغ GL_APIENTRY glGetDriverControlStringQCOM (GLuint driverControl, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLchar *driverControlString);
GL_APICALL فراغ GL_APIENTRY glEnableDriverControlQCOM (GLuint driverControl);
GL_APICALL فراغ GL_APIENTRY glDisableDriverControlQCOM (GLuint driverControl);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_QCOM_driver_control */

#جيڪڏهن_وصف_نه_ٿيل GL_QCOM_extended_get
#وصف_ڪريو GL_QCOM_extended_get 1
#وصف_ڪريو GL_TEXTURE_ويڪر_QCOM             0x8BD2
#وصف_ڪريو GL_TEXTURE_اوچائي_QCOM            0x8BD3
#وصف_ڪريو GL_TEXTURE_اونهائي_QCOM             0x8BD4
#وصف_ڪريو GL_TEXTURE_اندروني_FORMAT_QCOM   0x8BD5
#وصف_ڪريو GL_TEXTURE_FORMAT_QCOM            0x8BD6
#وصف_ڪريو GL_TEXTURE_TYPE_QCOM              0x8BD7
#وصف_ڪريو GL_TEXTURE_IMAGE_VALID_QCOM       0x8BD8
#وصف_ڪريو GL_TEXTURE_انگ_سطحون_QCOM        0x8BD9
#وصف_ڪريو GL_TEXTURE_هدف_QCOM            0x8BDA
#وصف_ڪريو GL_TEXTURE_OBJECT_VALID_QCOM      0x8BDB
#وصف_ڪريو GL_STATE_RESTORE                  0x8BDC
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETTEXTURESQCOMPROC) (GLuint *textures, GLint maxTextures, GLint *انگ_Textures);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETBUFFERSQCOMPROC) (GLuint *buffers, GLint maxBuffers, GLint *انگ_Buffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETRENDERBUFFERSQCOMPROC) (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *انگ_Renderbuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETFRAMEBUFFERSQCOMPROC) (GLuint *framebuffers, GLint maxFramebuffers, GLint *انگ_Framebuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETTEXLEVELPARAMETERIVQCOMPROC) (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTTEXOBJECTSTATEOVERRIDEIQCOMPROC) (GLenum هدف, GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETTEXSUBIMAGEQCOMPROC) (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLenum format, GLenum type, فراغ *texels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETBUFFERPOINTERVQCOMPROC) (GLenum هدف, فراغ **params);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glExtGetTexturesQCOM (GLuint *textures, GLint maxTextures, GLint *انگ_Textures);
GL_APICALL فراغ GL_APIENTRY glExtGetBuffersQCOM (GLuint *buffers, GLint maxBuffers, GLint *انگ_Buffers);
GL_APICALL فراغ GL_APIENTRY glExtGetRenderbuffersQCOM (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *انگ_Renderbuffers);
GL_APICALL فراغ GL_APIENTRY glExtGetFramebuffersQCOM (GLuint *framebuffers, GLint maxFramebuffers, GLint *انگ_Framebuffers);
GL_APICALL فراغ GL_APIENTRY glExtGetTexLevelParameterivQCOM (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glExtTexObjectStateOverrideiQCOM (GLenum هدف, GLenum pname, GLint param);
GL_APICALL فراغ GL_APIENTRY glExtGetTexSubImageQCOM (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLenum format, GLenum type, فراغ *texels);
GL_APICALL فراغ GL_APIENTRY gl_Ext_Get_بفر_Pointerv_QCOM (GLenum هدف, فراغ **params);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_QCOM_extended_get */

#جيڪڏهن_وصف_نه_ٿيل GL_QCOM_extended_get2
#وصف_ڪريو GL_QCOM_extended_get2 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETSHADERSQCOMPROC) (GLuint *shaders, GLint maxShaders, GLint *انگ_Shaders);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETPROGRAMSQCOMPROC) (GLuint *programs, GLint maxPrograms, GLint *انگ_Programs);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLEXTISPROGRAMBINARYQCOMPROC) (GLuint پروگرام);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETPROGRAMBINARYSOURCEQCOMPROC) (GLuint پروگرام, GLenum shadertype, GLchar *ذريعو, GLint *ڊيگهائي);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glExtGetShadersQCOM (GLuint *shaders, GLint maxShaders, GLint *انگ_Shaders);
GL_APICALL فراغ GL_APIENTRY glExtGetProgramsQCOM (GLuint *programs, GLint maxPrograms, GLint *انگ_Programs);
GL_APICALL GLboolean GL_APIENTRY gl_Ext_Is_پروگرام_ٻٽو_QCOM (GLuint پروگرام);
GL_APICALL فراغ GL_APIENTRY gl_Ext_Get_پروگرام_ٻٽو_ذريعو_QCOM (GLuint پروگرام, GLenum shadertype, GLchar *ذريعو, GLint *ڊيگهائي);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_QCOM_extended_get2 */

#جيڪڏهن_وصف_نه_ٿيل GL_QCOM_چوکٺو_extrapolation
#وصف_ڪريو GL_QCOM_چوکٺو_extrapolation 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTRAPOLATETEX2DQCOMPROC) (GLuint src1, GLuint src2, GLuint output, GLfloat scale_ضرب_ڪندڙ);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glExtrapolateTex2DQCOM (GLuint src1, GLuint src2, GLuint output, GLfloat scale_ضرب_ڪندڙ);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_QCOM_frame_extrapolation */

#جيڪڏهن_وصف_نه_ٿيل GL_QCOM_framebuffer_foveated
#وصف_ڪريو GL_QCOM_framebuffer_foveated 1
#وصف_ڪريو GL_FOVEATION_ENABLE_ٻٽو_انگ_QCOM      0x00000001
#وصف_ڪريو GL_FOVEATION_SCALED_BIN_طريقو_ٻٽو_انگ_QCOM 0x00000002
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERFOVEATIONCONFIGQCOMPROC) (GLuint framebuffer, GLuint انگ_Layers, GLuint focal_Points_في_Layer, GLuint requestedFeatures, GLuint *providedFeatures);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERFOVEATIONPARAMETERSQCOMPROC) (GLuint framebuffer, GLuint layer, GLuint focal_نقطو, GLfloat focalX, GLfloat focalY, GLfloat gainX, GLfloat gainY, GLfloat foveaArea);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferFoveationConfigQCOM (GLuint framebuffer, GLuint انگ_Layers, GLuint focal_Points_في_Layer, GLuint requestedFeatures, GLuint *providedFeatures);
GL_APICALL فراغ GL_APIENTRY glFramebufferFoveationParametersQCOM (GLuint framebuffer, GLuint layer, GLuint focal_نقطو, GLfloat focalX, GLfloat focalY, GLfloat gainX, GLfloat gainY, GLfloat foveaArea);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_QCOM_framebuffer_foveated */

#جيڪڏهن_وصف_نه_ٿيل GL_QCOM_motion_estimation
#وصف_ڪريو GL_QCOM_motion_estimation 1
#وصف_ڪريو GL_MOTION_ESTIMATION_ڳولا_بلاڪ_X_QCOM 0x8C90
#وصف_ڪريو GL_MOTION_ESTIMATION_ڳولا_بلاڪ_Y_QCOM 0x8C91
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXESTIMATEMOTIONQCOMPROC) (GLuint ref, GLuint هدف, GLuint output);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXESTIMATEMOTIONREGIONSQCOMPROC) (GLuint ref, GLuint هدف, GLuint output, GLuint نقاب);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTexEstimateMotionQCOM (GLuint ref, GLuint هدف, GLuint output);
GL_APICALL فراغ GL_APIENTRY glTexEstimateMotionRegionsQCOM (GLuint ref, GLuint هدف, GLuint output, GLuint نقاب);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_QCOM_motion_estimation */

#جيڪڏهن_وصف_نه_ٿيل GL_QCOM_perfmon_global_گهڻائي
#وصف_ڪريو GL_QCOM_perfmon_global_گهڻائي 1
#وصف_ڪريو GL_PERFMON_GLOBAL_گهڻائي_QCOM       0x8FA0
#جيڪڏهن_پورو /* GL_QCOM_perfmon_global_mode */

#جيڪڏهن_وصف_نه_ٿيل GL_QCOM_render_sRGB_R8_RG8
#وصف_ڪريو GL_QCOM_render_sRGB_R8_RG8 1
#جيڪڏهن_پورو /* GL_QCOM_render_sRGB_R8_RG8 */

#جيڪڏهن_وصف_نه_ٿيل GL_QCOM_render_shared_exponent
#وصف_ڪريو GL_QCOM_render_shared_exponent 1
#جيڪڏهن_پورو /* GL_QCOM_render_shared_exponent */

#جيڪڏهن_وصف_نه_ٿيل GL_QCOM_shader_framebuffer_fetch_noncoherent
#وصف_ڪريو GL_QCOM_shader_framebuffer_fetch_noncoherent 1
#وصف_ڪريو GL_FRAMEBUFFER_FETCH_NONCOHERENT_QCOM 0x96A2
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERFETCHBARRIERQCOMPROC) (فراغ);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferFetchBarrierQCOM (فراغ);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_QCOM_shader_framebuffer_fetch_noncoherent */

#جيڪڏهن_وصف_نه_ٿيل GL_QCOM_shader_framebuffer_fetch_شرح
#وصف_ڪريو GL_QCOM_shader_framebuffer_fetch_شرح 1
#جيڪڏهن_پورو /* GL_QCOM_shader_framebuffer_fetch_rate */

#جيڪڏهن_وصف_نه_ٿيل GL_QCOM_shading_شرح
#وصف_ڪريو GL_QCOM_shading_شرح 1
#وصف_ڪريو GL_SHADING_شرح_QCOM              0x96A4
#وصف_ڪريو GL_SHADING_شرح_PRESERVE_ASPECT_تناسب_QCOM 0x96A5
#وصف_ڪريو GL_SHADING_شرح_1_X1_PIXELS_QCOM   0x96A6
#وصف_ڪريو GL_SHADING_شرح_1_X2_PIXELS_QCOM   0x96A7
#وصف_ڪريو GL_SHADING_شرح_2_X1_PIXELS_QCOM   0x96A8
#وصف_ڪريو GL_SHADING_شرح_2_X2_PIXELS_QCOM   0x96A9
#وصف_ڪريو GL_SHADING_شرح_4_X2_PIXELS_QCOM   0x96AC
#وصف_ڪريو GL_SHADING_شرح_4_X4_PIXELS_QCOM   0x96AE
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADINGRATEQCOMPROC) (GLenum شرح);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Shading_شرح_QCOM (GLenum شرح);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_QCOM_shading_rate */

#جيڪڏهن_وصف_نه_ٿيل GL_QCOM_texture_foveated
#وصف_ڪريو GL_QCOM_texture_foveated 1
#وصف_ڪريو GL_TEXTURE_FOVEATED_FEATURE_بٽ_QCOM 0x8BFB
#وصف_ڪريو GL_TEXTURE_FOVEATED_MIN_PIXEL_DENSITY_QCOM 0x8BFC
#وصف_ڪريو GL_TEXTURE_FOVEATED_FEATURE_QUERY_QCOM 0x8BFD
#وصف_ڪريو GL_TEXTURE_FOVEATED_انگ_FOCAL_POINTS_QUERY_QCOM 0x8BFE
#وصف_ڪريو GL_FRAMEBUFFER_INCOMPLETE_FOVEATION_QCOM 0x8BFF
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTUREFOVEATIONPARAMETERSQCOMPROC) (GLuint texture, GLuint layer, GLuint focal_نقطو, GLfloat focalX, GLfloat focalY, GLfloat gainX, GLfloat gainY, GLfloat foveaArea);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTextureFoveationParametersQCOM (GLuint texture, GLuint layer, GLuint focal_نقطو, GLfloat focalX, GLfloat focalY, GLfloat gainX, GLfloat gainY, GLfloat foveaArea);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_QCOM_texture_foveated */

#جيڪڏهن_وصف_نه_ٿيل GL_QCOM_texture_foveated2
#وصف_ڪريو GL_QCOM_texture_foveated2 1
#وصف_ڪريو GL_TEXTURE_FOVEATED_CUTOFF_DENSITY_QCOM 0x96A0
#جيڪڏهن_پورو /* GL_QCOM_texture_foveated2 */

#جيڪڏهن_وصف_نه_ٿيل GL_QCOM_texture_foveated_subsampled_layout
#وصف_ڪريو GL_QCOM_texture_foveated_subsampled_layout 1
#وصف_ڪريو GL_FOVEATION_SUBSAMPLED_LAYOUT_طريقو_ٻٽو_انگ_QCOM 0x00000004
#وصف_ڪريو GL_MAX_SHADER_SUBSAMPLED_IMAGE_UNITS_QCOM 0x8FA1
#جيڪڏهن_پورو /* GL_QCOM_texture_foveated_subsampled_layout */

#جيڪڏهن_وصف_نه_ٿيل GL_QCOM_texture_lod_bias
#وصف_ڪريو GL_QCOM_texture_lod_bias 1
#وصف_ڪريو GL_TEXTURE_LOD_BIAS_QCOM          0x8C96
#جيڪڏهن_پورو /* GL_QCOM_texture_lod_bias */

#جيڪڏهن_وصف_نه_ٿيل GL_QCOM_tiled_rendering
#وصف_ڪريو GL_QCOM_tiled_rendering 1
#وصف_ڪريو GL_COLOR_بفر_BIT0_QCOM         0x00000001
#وصف_ڪريو GL_COLOR_بفر_BIT1_QCOM         0x00000002
#وصف_ڪريو GL_COLOR_بفر_BIT2_QCOM         0x00000004
#وصف_ڪريو GL_COLOR_بفر_BIT3_QCOM         0x00000008
#وصف_ڪريو GL_COLOR_بفر_BIT4_QCOM         0x00000010
#وصف_ڪريو GL_COLOR_بفر_BIT5_QCOM         0x00000020
#وصف_ڪريو GL_COLOR_بفر_BIT6_QCOM         0x00000040
#وصف_ڪريو GL_COLOR_بفر_BIT7_QCOM         0x00000080
#وصف_ڪريو GL_اونهائي_بفر_BIT0_QCOM         0x00000100
#وصف_ڪريو GL_اونهائي_بفر_BIT1_QCOM         0x00000200
#وصف_ڪريو GL_اونهائي_بفر_BIT2_QCOM         0x00000400
#وصف_ڪريو GL_اونهائي_بفر_BIT3_QCOM         0x00000800
#وصف_ڪريو GL_اونهائي_بفر_BIT4_QCOM         0x00001000
#وصف_ڪريو GL_اونهائي_بفر_BIT5_QCOM         0x00002000
#وصف_ڪريو GL_اونهائي_بفر_BIT6_QCOM         0x00004000
#وصف_ڪريو GL_اونهائي_بفر_BIT7_QCOM         0x00008000
#وصف_ڪريو GL_STENCIL_بفر_BIT0_QCOM       0x00010000
#وصف_ڪريو GL_STENCIL_بفر_BIT1_QCOM       0x00020000
#وصف_ڪريو GL_STENCIL_بفر_BIT2_QCOM       0x00040000
#وصف_ڪريو GL_STENCIL_بفر_BIT3_QCOM       0x00080000
#وصف_ڪريو GL_STENCIL_بفر_BIT4_QCOM       0x00100000
#وصف_ڪريو GL_STENCIL_بفر_BIT5_QCOM       0x00200000
#وصف_ڪريو GL_STENCIL_بفر_BIT6_QCOM       0x00400000
#وصف_ڪريو GL_STENCIL_بفر_BIT7_QCOM       0x00800000
#وصف_ڪريو GL_MULTISAMPLE_بفر_BIT0_QCOM   0x01000000
#وصف_ڪريو GL_MULTISAMPLE_بفر_BIT1_QCOM   0x02000000
#وصف_ڪريو GL_MULTISAMPLE_بفر_BIT2_QCOM   0x04000000
#وصف_ڪريو GL_MULTISAMPLE_بفر_BIT3_QCOM   0x08000000
#وصف_ڪريو GL_MULTISAMPLE_بفر_BIT4_QCOM   0x10000000
#وصف_ڪريو GL_MULTISAMPLE_بفر_BIT5_QCOM   0x20000000
#وصف_ڪريو GL_MULTISAMPLE_بفر_BIT6_QCOM   0x40000000
#وصف_ڪريو GL_MULTISAMPLE_بفر_BIT7_QCOM   0x80000000
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTARTTILINGQCOMPROC) (GLuint x, GLuint y, GLuint ويڪر, GLuint اوچائي, GLbitfield preserve_نقاب);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENDTILINGQCOMPROC) (GLbitfield preserve_نقاب);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_شروعات_Tiling_QCOM (GLuint x, GLuint y, GLuint ويڪر, GLuint اوچائي, GLbitfield preserve_نقاب);
GL_APICALL فراغ GL_APIENTRY gl_پڇاڙي_Tiling_QCOM (GLbitfield preserve_نقاب);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_QCOM_tiled_rendering */

#جيڪڏهن_وصف_نه_ٿيل GL_QCOM_writeonly_rendering
#وصف_ڪريو GL_QCOM_writeonly_rendering 1
#وصف_ڪريو GL_WRITEONLY_RENDERING_QCOM       0x8823
#جيڪڏهن_پورو /* GL_QCOM_writeonly_rendering */

#جيڪڏهن_وصف_نه_ٿيل GL_QCOM_ycbcr_degamma
#وصف_ڪريو GL_QCOM_ycbcr_degamma 1
#وصف_ڪريو GL_TEXTURE_Y_DEGAMMA_QCOM         0x9710
#وصف_ڪريو GL_TEXTURE_CBCR_DEGAMMA_QCOM      0x9711
#جيڪڏهن_پورو /* GL_QCOM_ycbcr_degamma */

#جيڪڏهن_وصف_نه_ٿيل GL_VIV_shader_ٻٽو
#وصف_ڪريو GL_VIV_shader_ٻٽو 1
#وصف_ڪريو GL_SHADER_ٻٽو_VIV              0x8FC4
#جيڪڏهن_پورو /* GL_VIV_shader_binary */

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو
