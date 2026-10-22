#اگر_غیر_تعریف_شدہ __gles2_gl2ext_h_
#تعریف_کرو __gles2_gl2ext_h_ 1

#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم

/*
** Copyright 2013-2026 The Khronos Group Inc.
** SPDX-License-Identifier: MIT
**
** This header is generated from the Khronos OpenGL / OpenGL ES XML
** API Registry. The current version of the Registry, generator scripts
** used to make the header, and the header can be found at
**   https://github.com/KhronosGroup/OpenGL-Registry
*/

#اگر_غیر_تعریف_شدہ GL_APIENTRYP
#تعریف_کرو GL_APIENTRYP GL_APIENTRY*
#اگر_ختم

#تعریف_کرو GL_GLEXT_نسخہ 20260803

/* Generated C header for:
 * API: gles2
 * Profile: common
 * Versions considered: 2\.[0-9]
 * Versions emitted: _nomatch_^
 * Default extensions included: gles2
 * Additional extensions included: _nomatch_^
 * Extensions removed: _nomatch_^
 */

#اگر_غیر_تعریف_شدہ GL_KHR_blend_equation_advanced
#تعریف_کرو GL_KHR_blend_equation_advanced 1
#تعریف_کرو GL_MULTIPLY_KHR                   0x9294
#تعریف_کرو GL_SCREEN_KHR                     0x9295
#تعریف_کرو GL_OVERLAY_KHR                    0x9296
#تعریف_کرو GL_DARKEN_KHR                     0x9297
#تعریف_کرو GL_LIGHTEN_KHR                    0x9298
#تعریف_کرو GL_COLORDODGE_KHR                 0x9299
#تعریف_کرو GL_COLORBURN_KHR                  0x929A
#تعریف_کرو GL_HARDLIGHT_KHR                  0x929B
#تعریف_کرو GL_SOFTLIGHT_KHR                  0x929C
#تعریف_کرو GL_DIFFERENCE_KHR                 0x929E
#تعریف_کرو GL_EXCLUSION_KHR                  0x92A0
#تعریف_کرو GL_HSL_HUE_KHR                    0x92AD
#تعریف_کرو GL_HSL_SATURATION_KHR             0x92AE
#تعریف_کرو GL_HSL_COLOR_KHR                  0x92AF
#تعریف_کرو GL_HSL_LUMINOSITY_KHR             0x92B0
قسمتعریف خالی (GL_APIENTRYP PFNGLBLENDBARRIERKHRPROC) (خالی);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glBlendBarrierKHR (خالی);
#اگر_ختم
#اگر_ختم /* GL_KHR_blend_equation_advanced */

#اگر_غیر_تعریف_شدہ GL_KHR_blend_equation_advanced_coherent
#تعریف_کرو GL_KHR_blend_equation_advanced_coherent 1
#تعریف_کرو GL_BLEND_ADVANCED_COHERENT_KHR    0x9285
#اگر_ختم /* GL_KHR_blend_equation_advanced_coherent */

#اگر_غیر_تعریف_شدہ GL_KHR_context_flush_control
#تعریف_کرو GL_KHR_context_flush_control 1
#تعریف_کرو GL_CONTEXT_RELEASE_BEHAVIOR_KHR   0x82FB
#تعریف_کرو GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_KHR 0x82FC
#اگر_ختم /* GL_KHR_context_flush_control */

#اگر_غیر_تعریف_شدہ GL_KHR_debug
#تعریف_کرو GL_KHR_debug 1
قسمتعریف خالی (GL_APIENTRY  *GLDEBUGPROCKHR)(GLenum ماخذ,GLenum type,GLuint id,GLenum severity,GLsizei لمبائی,ثابت GLchar *پیغام,ثابت خالی *userParam);
#تعریف_کرو GL_SAMPLER                        0x82E6
#تعریف_کرو GL_DEBUG_OUTPUT_SYNCHRONOUS_KHR   0x8242
#تعریف_کرو GL_DEBUG_اگلا_LOGGED_پیغام_لمبائی_KHR 0x8243
#تعریف_کرو GL_DEBUG_CALLBACK_FUNCTION_KHR    0x8244
#تعریف_کرو GL_DEBUG_CALLBACK_USER_PARAM_KHR  0x8245
#تعریف_کرو GL_DEBUG_ماخذ_API_KHR           0x8246
#تعریف_کرو GL_DEBUG_ماخذ_کھڑکی_SYSTEM_KHR 0x8247
#تعریف_کرو GL_DEBUG_ماخذ_SHADER_COMPILER_KHR 0x8248
#تعریف_کرو GL_DEBUG_ماخذ_تیسرا_PARTY_KHR   0x8249
#تعریف_کرو GL_DEBUG_ماخذ_APPLICATION_KHR   0x824A
#تعریف_کرو GL_DEBUG_ماخذ_OTHER_KHR         0x824B
#تعریف_کرو GL_DEBUG_TYPE_ERROR_KHR           0x824C
#تعریف_کرو GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_KHR 0x824D
#تعریف_کرو GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_KHR 0x824E
#تعریف_کرو GL_DEBUG_TYPE_PORTABILITY_KHR     0x824F
#تعریف_کرو GL_DEBUG_TYPE_PERFORMANCE_KHR     0x8250
#تعریف_کرو GL_DEBUG_TYPE_OTHER_KHR           0x8251
#تعریف_کرو GL_DEBUG_TYPE_MARKER_KHR          0x8268
#تعریف_کرو GL_DEBUG_TYPE_ڈالو_گروہ_KHR      0x8269
#تعریف_کرو GL_DEBUG_TYPE_نکالو_گروہ_KHR       0x826A
#تعریف_کرو GL_DEBUG_SEVERITY_NOTIFICATION_KHR 0x826B
#تعریف_کرو GL_MAX_DEBUG_گروہ_ڈھیر_گہرائی_KHR 0x826C
#تعریف_کرو GL_DEBUG_گروہ_ڈھیر_گہرائی_KHR    0x826D
#تعریف_کرو GL_بفر_KHR                     0x82E0
#تعریف_کرو GL_SHADER_KHR                     0x82E1
#تعریف_کرو GL_پروگرام_KHR                    0x82E2
#تعریف_کرو GL_راس_ARRAY_KHR               0x8074
#تعریف_کرو GL_QUERY_KHR                      0x82E3
#تعریف_کرو GL_پروگرام_PIPELINE_KHR           0x82E4
#تعریف_کرو GL_SAMPLER_KHR                    0x82E6
#تعریف_کرو GL_MAX_LABEL_لمبائی_KHR           0x82E8
#تعریف_کرو GL_MAX_DEBUG_پیغام_لمبائی_KHR   0x9143
#تعریف_کرو GL_MAX_DEBUG_LOGGED_MESSAGES_KHR  0x9144
#تعریف_کرو GL_DEBUG_LOGGED_MESSAGES_KHR      0x9145
#تعریف_کرو GL_DEBUG_SEVERITY_بلند_KHR        0x9146
#تعریف_کرو GL_DEBUG_SEVERITY_MEDIUM_KHR      0x9147
#تعریف_کرو GL_DEBUG_SEVERITY_کم_KHR         0x9148
#تعریف_کرو GL_DEBUG_OUTPUT_KHR               0x92E0
#تعریف_کرو GL_CONTEXT_FLAG_DEBUG_ثنائی_ہندسہ_KHR     0x00000002
#تعریف_کرو GL_ڈھیر_حد_سے_تجاوز_KHR             0x0503
#تعریف_کرو GL_ڈھیر_UNDERFLOW_KHR            0x0504
قسمتعریف خالی (GL_APIENTRYP PFNGLDEBUGMESSAGECONTROLKHRPROC) (GLenum ماخذ, GLenum type, GLenum severity, GLsizei گنتی, ثابت GLuint *ids, GLboolean enabled);
قسمتعریف خالی (GL_APIENTRYP PFNGLDEBUGMESSAGEINSERTKHRPROC) (GLenum ماخذ, GLenum type, GLuint id, GLenum severity, GLsizei لمبائی, ثابت GLchar *buf);
قسمتعریف خالی (GL_APIENTRYP PFNGLDEBUGMESSAGECALLBACKKHRPROC) (GLDEBUGPROCKHR callback, ثابت خالی *userParam);
قسمتعریف GLuint (GL_APIENTRYP PFNGLGETDEBUGMESSAGELOGKHRPROC) (GLuint گنتی, GLsizei buf_سائز, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *پیغام_Log);
قسمتعریف خالی (GL_APIENTRYP PFNGLPUSHDEBUGGROUPKHRPROC) (GLenum ماخذ, GLuint id, GLsizei لمبائی, ثابت GLchar *پیغام);
قسمتعریف خالی (GL_APIENTRYP PFNGLPOPDEBUGGROUPKHRPROC) (خالی);
قسمتعریف خالی (GL_APIENTRYP PFNGLOBJECTLABELKHRPROC) (GLenum identifier, GLuint name, GLsizei لمبائی, ثابت GLchar *label);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETOBJECTLABELKHRPROC) (GLenum identifier, GLuint name, GLsizei buf_سائز, GLsizei *لمبائی, GLchar *label);
قسمتعریف خالی (GL_APIENTRYP PFNGLOBJECTPTRLABELKHRPROC) (ثابت خالی *ptr, GLsizei لمبائی, ثابت GLchar *label);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETOBJECTPTRLABELKHRPROC) (ثابت خالی *ptr, GLsizei buf_سائز, GLsizei *لمبائی, GLchar *label);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETPOINTERVKHRPROC) (GLenum pname, خالی **params);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_Debug_پیغام_Control_KHR (GLenum ماخذ, GLenum type, GLenum severity, GLsizei گنتی, ثابت GLuint *ids, GLboolean enabled);
GL_APICALL خالی GL_APIENTRY gl_Debug_پیغام_داخل_کرو_KHR (GLenum ماخذ, GLenum type, GLuint id, GLenum severity, GLsizei لمبائی, ثابت GLchar *buf);
GL_APICALL خالی GL_APIENTRY gl_Debug_پیغام_Callback_KHR (GLDEBUGPROCKHR callback, ثابت خالی *userParam);
GL_APICALL GLuint GL_APIENTRY gl_Get_Debug_پیغام_Log_KHR (GLuint گنتی, GLsizei buf_سائز, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *پیغام_Log);
GL_APICALL خالی GL_APIENTRY gl_ڈالو_Debug_گروہ_KHR (GLenum ماخذ, GLuint id, GLsizei لمبائی, ثابت GLchar *پیغام);
GL_APICALL خالی GL_APIENTRY gl_نکالو_Debug_گروہ_KHR (خالی);
GL_APICALL خالی GL_APIENTRY glObjectLabelKHR (GLenum identifier, GLuint name, GLsizei لمبائی, ثابت GLchar *label);
GL_APICALL خالی GL_APIENTRY glGetObjectLabelKHR (GLenum identifier, GLuint name, GLsizei buf_سائز, GLsizei *لمبائی, GLchar *label);
GL_APICALL خالی GL_APIENTRY glObjectPtrLabelKHR (ثابت خالی *ptr, GLsizei لمبائی, ثابت GLchar *label);
GL_APICALL خالی GL_APIENTRY glGetObjectPtrLabelKHR (ثابت خالی *ptr, GLsizei buf_سائز, GLsizei *لمبائی, GLchar *label);
GL_APICALL خالی GL_APIENTRY glGetPointervKHR (GLenum pname, خالی **params);
#اگر_ختم
#اگر_ختم /* GL_KHR_debug */

#اگر_غیر_تعریف_شدہ GL_KHR_no_error
#تعریف_کرو GL_KHR_no_error 1
#تعریف_کرو GL_CONTEXT_FLAG_NO_ERROR_ثنائی_ہندسہ_KHR  0x00000008
#اگر_ختم /* GL_KHR_no_error */

#اگر_غیر_تعریف_شدہ GL_KHR_parallel_shader_compile
#تعریف_کرو GL_KHR_parallel_shader_compile 1
#تعریف_کرو GL_MAX_SHADER_COMPILER_دھاگے_KHR 0x91B0
#تعریف_کرو GL_COMPLETION_حالت_KHR          0x91B1
قسمتعریف خالی (GL_APIENTRYP PFNGLMAXSHADERCOMPILERTHREADSKHRPROC) (GLuint گنتی);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_Max_Shader_Compiler_دھاگے_KHR (GLuint گنتی);
#اگر_ختم
#اگر_ختم /* GL_KHR_parallel_shader_compile */

#اگر_غیر_تعریف_شدہ GL_KHR_robust_بفر_access_behavior
#تعریف_کرو GL_KHR_robust_بفر_access_behavior 1
#اگر_ختم /* GL_KHR_robust_buffer_access_behavior */

#اگر_غیر_تعریف_شدہ GL_KHR_robustness
#تعریف_کرو GL_KHR_robustness 1
#تعریف_کرو GL_CONTEXT_ROBUST_ACCESS_KHR      0x90F3
#تعریف_کرو GL_LOSE_CONTEXT_ON_RESET_KHR      0x8252
#تعریف_کرو GL_GUILTY_CONTEXT_RESET_KHR       0x8253
#تعریف_کرو GL_INNOCENT_CONTEXT_RESET_KHR     0x8254
#تعریف_کرو GL_UNKNOWN_CONTEXT_RESET_KHR      0x8255
#تعریف_کرو GL_RESET_NOTIFICATION_STRATEGY_KHR 0x8256
#تعریف_کرو GL_NO_RESET_NOTIFICATION_KHR      0x8261
#تعریف_کرو GL_CONTEXT_گمشدہ_KHR               0x0507
قسمتعریف GLenum (GL_APIENTRYP PFNGLGETGRAPHICSRESETSTATUSKHRPROC) (خالی);
قسمتعریف خالی (GL_APIENTRYP PFNGLREADNPIXELSKHRPROC) (GLint x, GLint y, GLsizei چوڑائی, GLsizei اونچائی, GLenum format, GLenum type, GLsizei buf_سائز, خالی *ڈیٹا);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETNUNIFORMFVKHRPROC) (GLuint پروگرام, GLint location, GLsizei buf_سائز, GLfloat *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETNUNIFORMIVKHRPROC) (GLuint پروگرام, GLint location, GLsizei buf_سائز, GLint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETNUNIFORMUIVKHRPROC) (GLuint پروگرام, GLint location, GLsizei buf_سائز, GLuint *params);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL GLenum GL_APIENTRY gl_Get_Graphics_Reset_حالت_KHR (خالی);
GL_APICALL خالی GL_APIENTRY glReadnPixelsKHR (GLint x, GLint y, GLsizei چوڑائی, GLsizei اونچائی, GLenum format, GLenum type, GLsizei buf_سائز, خالی *ڈیٹا);
GL_APICALL خالی GL_APIENTRY glGetnUniformfvKHR (GLuint پروگرام, GLint location, GLsizei buf_سائز, GLfloat *params);
GL_APICALL خالی GL_APIENTRY glGetnUniformivKHR (GLuint پروگرام, GLint location, GLsizei buf_سائز, GLint *params);
GL_APICALL خالی GL_APIENTRY glGetnUniformuivKHR (GLuint پروگرام, GLint location, GLsizei buf_سائز, GLuint *params);
#اگر_ختم
#اگر_ختم /* GL_KHR_robustness */

#اگر_غیر_تعریف_شدہ GL_KHR_shader_subgroup
#تعریف_کرو GL_KHR_shader_subgroup 1
#تعریف_کرو GL_SUBGROUP_سائز_KHR              0x9532
#تعریف_کرو GL_SUBGROUP_SUPPORTED_STAGES_KHR  0x9533
#تعریف_کرو GL_SUBGROUP_SUPPORTED_FEATURES_KHR 0x9534
#تعریف_کرو GL_SUBGROUP_QUAD_ALL_STAGES_KHR   0x9535
#تعریف_کرو GL_SUBGROUP_FEATURE_BASIC_ثنائی_ہندسہ_KHR 0x00000001
#تعریف_کرو GL_SUBGROUP_FEATURE_VOTE_ثنائی_ہندسہ_KHR  0x00000002
#تعریف_کرو GL_SUBGROUP_FEATURE_ARITHMETIC_ثنائی_ہندسہ_KHR 0x00000004
#تعریف_کرو GL_SUBGROUP_FEATURE_BALLOT_ثنائی_ہندسہ_KHR 0x00000008
#تعریف_کرو GL_SUBGROUP_FEATURE_SHUFFLE_ثنائی_ہندسہ_KHR 0x00000010
#تعریف_کرو GL_SUBGROUP_FEATURE_SHUFFLE_RELATIVE_ثنائی_ہندسہ_KHR 0x00000020
#تعریف_کرو GL_SUBGROUP_FEATURE_CLUSTERED_ثنائی_ہندسہ_KHR 0x00000040
#تعریف_کرو GL_SUBGROUP_FEATURE_QUAD_ثنائی_ہندسہ_KHR  0x00000080
#اگر_ختم /* GL_KHR_shader_subgroup */

#اگر_غیر_تعریف_شدہ GL_KHR_texture_compression_astc_hdr
#تعریف_کرو GL_KHR_texture_compression_astc_hdr 1
#تعریف_کرو GL_COMPRESSED_RGBA_ASTC_4x4_KHR   0x93B0
#تعریف_کرو GL_COMPRESSED_RGBA_ASTC_5x4_KHR   0x93B1
#تعریف_کرو GL_COMPRESSED_RGBA_ASTC_5x5_KHR   0x93B2
#تعریف_کرو GL_COMPRESSED_RGBA_ASTC_6x5_KHR   0x93B3
#تعریف_کرو GL_COMPRESSED_RGBA_ASTC_6x6_KHR   0x93B4
#تعریف_کرو GL_COMPRESSED_RGBA_ASTC_8x5_KHR   0x93B5
#تعریف_کرو GL_COMPRESSED_RGBA_ASTC_8x6_KHR   0x93B6
#تعریف_کرو GL_COMPRESSED_RGBA_ASTC_8x8_KHR   0x93B7
#تعریف_کرو GL_COMPRESSED_RGBA_ASTC_10x5_KHR  0x93B8
#تعریف_کرو GL_COMPRESSED_RGBA_ASTC_10x6_KHR  0x93B9
#تعریف_کرو GL_COMPRESSED_RGBA_ASTC_10x8_KHR  0x93BA
#تعریف_کرو GL_COMPRESSED_RGBA_ASTC_10x10_KHR 0x93BB
#تعریف_کرو GL_COMPRESSED_RGBA_ASTC_12x10_KHR 0x93BC
#تعریف_کرو GL_COMPRESSED_RGBA_ASTC_12x12_KHR 0x93BD
#تعریف_کرو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR 0x93D0
#تعریف_کرو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR 0x93D1
#تعریف_کرو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR 0x93D2
#تعریف_کرو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR 0x93D3
#تعریف_کرو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR 0x93D4
#تعریف_کرو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR 0x93D5
#تعریف_کرو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR 0x93D6
#تعریف_کرو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR 0x93D7
#تعریف_کرو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR 0x93D8
#تعریف_کرو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR 0x93D9
#تعریف_کرو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR 0x93DA
#تعریف_کرو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR 0x93DB
#تعریف_کرو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR 0x93DC
#تعریف_کرو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR 0x93DD
#اگر_ختم /* GL_KHR_texture_compression_astc_hdr */

#اگر_غیر_تعریف_شدہ GL_KHR_texture_compression_astc_ldr
#تعریف_کرو GL_KHR_texture_compression_astc_ldr 1
#اگر_ختم /* GL_KHR_texture_compression_astc_ldr */

#اگر_غیر_تعریف_شدہ GL_KHR_texture_compression_astc_sliced_3d
#تعریف_کرو GL_KHR_texture_compression_astc_sliced_3d 1
#اگر_ختم /* GL_KHR_texture_compression_astc_sliced_3d */

#اگر_غیر_تعریف_شدہ GL_OES_EGL_image
#تعریف_کرو GL_OES_EGL_image 1
قسمتعریف خالی *GLeglImageOES;
قسمتعریف خالی (GL_APIENTRYP PFNGLEGLIMAGETARGETTEXTURE2DOESPROC) (GLenum ہدف, GLeglImageOES image);
قسمتعریف خالی (GL_APIENTRYP PFNGLEGLIMAGETARGETRENDERBUFFERSTORAGEOESPROC) (GLenum ہدف, GLeglImageOES image);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_EGLImage_ہدف_Texture2_DOES (GLenum ہدف, GLeglImageOES image);
GL_APICALL خالی GL_APIENTRY gl_EGLImage_ہدف_Renderbuffer_Storage_OES (GLenum ہدف, GLeglImageOES image);
#اگر_ختم
#اگر_ختم /* GL_OES_EGL_image */

#اگر_غیر_تعریف_شدہ GL_OES_EGL_image_external
#تعریف_کرو GL_OES_EGL_image_external 1
#تعریف_کرو GL_TEXTURE_EXTERNAL_OES           0x8D65
#تعریف_کرو GL_TEXTURE_BINDING_EXTERNAL_OES   0x8D67
#تعریف_کرو GL_REQUIRED_TEXTURE_IMAGE_UNITS_OES 0x8D68
#تعریف_کرو GL_SAMPLER_EXTERNAL_OES           0x8D66
#اگر_ختم /* GL_OES_EGL_image_external */

#اگر_غیر_تعریف_شدہ GL_OES_EGL_image_external_essl3
#تعریف_کرو GL_OES_EGL_image_external_essl3 1
#اگر_ختم /* GL_OES_EGL_image_external_essl3 */

#اگر_غیر_تعریف_شدہ GL_OES_compressed_ETC1_RGB8_sub_texture
#تعریف_کرو GL_OES_compressed_ETC1_RGB8_sub_texture 1
#اگر_ختم /* GL_OES_compressed_ETC1_RGB8_sub_texture */

#اگر_غیر_تعریف_شدہ GL_OES_compressed_ETC1_RGB8_texture
#تعریف_کرو GL_OES_compressed_ETC1_RGB8_texture 1
#تعریف_کرو GL_ETC1_RGB8_OES                  0x8D64
#اگر_ختم /* GL_OES_compressed_ETC1_RGB8_texture */

#اگر_غیر_تعریف_شدہ GL_OES_compressed_paletted_texture
#تعریف_کرو GL_OES_compressed_paletted_texture 1
#تعریف_کرو GL_PALETTE4_RGB8_OES              0x8B90
#تعریف_کرو GL_PALETTE4_RGBA8_OES             0x8B91
#تعریف_کرو GL_PALETTE4_R5_G6_B5_OES          0x8B92
#تعریف_کرو GL_PALETTE4_RGBA4_OES             0x8B93
#تعریف_کرو GL_PALETTE4_RGB5_A1_OES           0x8B94
#تعریف_کرو GL_PALETTE8_RGB8_OES              0x8B95
#تعریف_کرو GL_PALETTE8_RGBA8_OES             0x8B96
#تعریف_کرو GL_PALETTE8_R5_G6_B5_OES          0x8B97
#تعریف_کرو GL_PALETTE8_RGBA4_OES             0x8B98
#تعریف_کرو GL_PALETTE8_RGB5_A1_OES           0x8B99
#اگر_ختم /* GL_OES_compressed_paletted_texture */

#اگر_غیر_تعریف_شدہ GL_OES_copy_image
#تعریف_کرو GL_OES_copy_image 1
قسمتعریف خالی (GL_APIENTRYP PFNGLCOPYIMAGESUBDATAOESPROC) (GLuint srcName, GLenum src_ہدف, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dst_ہدف, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei src_چوڑائی, GLsizei src_اونچائی, GLsizei src_گہرائی);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_Copy_Image_Sub_ڈیٹا_OES (GLuint srcName, GLenum src_ہدف, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dst_ہدف, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei src_چوڑائی, GLsizei src_اونچائی, GLsizei src_گہرائی);
#اگر_ختم
#اگر_ختم /* GL_OES_copy_image */

#اگر_غیر_تعریف_شدہ GL_OES_depth24
#تعریف_کرو GL_OES_depth24 1
#تعریف_کرو GL_گہرائی_COMPONENT24_OES          0x81A6
#اگر_ختم /* GL_OES_depth24 */

#اگر_غیر_تعریف_شدہ GL_OES_depth32
#تعریف_کرو GL_OES_depth32 1
#تعریف_کرو GL_گہرائی_COMPONENT32_OES          0x81A7
#اگر_ختم /* GL_OES_depth32 */

#اگر_غیر_تعریف_شدہ GL_OES_گہرائی_texture
#تعریف_کرو GL_OES_گہرائی_texture 1
#اگر_ختم /* GL_OES_depth_texture */

#اگر_غیر_تعریف_شدہ GL_OES_draw_buffers_اشاریہ_دار
#تعریف_کرو GL_OES_draw_buffers_اشاریہ_دار 1
#تعریف_کرو GL_MIN                            0x8007
#تعریف_کرو GL_MAX                            0x8008
قسمتعریف خالی (GL_APIENTRYP PFNGLENABLEIOESPROC) (GLenum ہدف, GLuint اشاریہ);
قسمتعریف خالی (GL_APIENTRYP PFNGLDISABLEIOESPROC) (GLenum ہدف, GLuint اشاریہ);
قسمتعریف خالی (GL_APIENTRYP PFNGLBLENDEQUATIONIOESPROC) (GLuint buf, GLenum منوال);
قسمتعریف خالی (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEIOESPROC) (GLuint buf, GLenum منوال_RGB, GLenum منوال_Alpha);
قسمتعریف خالی (GL_APIENTRYP PFNGLBLENDFUNCIOESPROC) (GLuint buf, GLenum src, GLenum dst);
قسمتعریف خالی (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEIOESPROC) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
قسمتعریف خالی (GL_APIENTRYP PFNGLCOLORMASKIOESPROC) (GLuint اشاریہ, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLISENABLEDIOESPROC) (GLenum ہدف, GLuint اشاریہ);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glEnableiOES (GLenum ہدف, GLuint اشاریہ);
GL_APICALL خالی GL_APIENTRY glDisableiOES (GLenum ہدف, GLuint اشاریہ);
GL_APICALL خالی GL_APIENTRY glBlendEquationiOES (GLuint buf, GLenum منوال);
GL_APICALL خالی GL_APIENTRY glBlendEquationSeparateiOES (GLuint buf, GLenum منوال_RGB, GLenum منوال_Alpha);
GL_APICALL خالی GL_APIENTRY glBlendFunciOES (GLuint buf, GLenum src, GLenum dst);
GL_APICALL خالی GL_APIENTRY glBlendFuncSeparateiOES (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
GL_APICALL خالی GL_APIENTRY glColorMaskiOES (GLuint اشاریہ, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
GL_APICALL GLboolean GL_APIENTRY glIsEnablediOES (GLenum ہدف, GLuint اشاریہ);
#اگر_ختم
#اگر_ختم /* GL_OES_draw_buffers_indexed */

#اگر_غیر_تعریف_شدہ GL_OES_draw_elements_بنیاد_راس
#تعریف_کرو GL_OES_draw_elements_بنیاد_راس 1
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWELEMENTSBASEVERTEXOESPROC) (GLenum منوال, GLsizei گنتی, GLenum type, ثابت خالی *indices, GLint basevertex);
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWRANGEELEMENTSBASEVERTEXOESPROC) (GLenum منوال, GLuint آغاز, GLuint انتہا, GLsizei گنتی, GLenum type, ثابت خالی *indices, GLint basevertex);
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXOESPROC) (GLenum منوال, GLsizei گنتی, GLenum type, ثابت خالی *indices, GLsizei instancecount, GLint basevertex);
قسمتعریف خالی (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSBASEVERTEXEXTPROC) (GLenum منوال, ثابت GLsizei *گنتی, GLenum type, ثابت خالی *ثابت*indices, GLsizei drawcount, ثابت GLint *basevertex);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_Draw_Elements_بنیاد_راس_OES (GLenum منوال, GLsizei گنتی, GLenum type, ثابت خالی *indices, GLint basevertex);
GL_APICALL خالی GL_APIENTRY gl_Draw_Range_Elements_بنیاد_راس_OES (GLenum منوال, GLuint آغاز, GLuint انتہا, GLsizei گنتی, GLenum type, ثابت خالی *indices, GLint basevertex);
GL_APICALL خالی GL_APIENTRY gl_Draw_Elements_Instanced_بنیاد_راس_OES (GLenum منوال, GLsizei گنتی, GLenum type, ثابت خالی *indices, GLsizei instancecount, GLint basevertex);
GL_APICALL خالی GL_APIENTRY gl_Multi_Draw_Elements_بنیاد_راس_EXT (GLenum منوال, ثابت GLsizei *گنتی, GLenum type, ثابت خالی *ثابت*indices, GLsizei drawcount, ثابت GLint *basevertex);
#اگر_ختم
#اگر_ختم /* GL_OES_draw_elements_base_vertex */

#اگر_غیر_تعریف_شدہ GL_OES_element_اشاریہ_uint
#تعریف_کرو GL_OES_element_اشاریہ_uint 1
#اگر_ختم /* GL_OES_element_index_uint */

#اگر_غیر_تعریف_شدہ GL_OES_fbo_render_mipmap
#تعریف_کرو GL_OES_fbo_render_mipmap 1
#اگر_ختم /* GL_OES_fbo_render_mipmap */

#اگر_غیر_تعریف_شدہ GL_OES_fragment_precision_بلند
#تعریف_کرو GL_OES_fragment_precision_بلند 1
#اگر_ختم /* GL_OES_fragment_precision_high */

#اگر_غیر_تعریف_شدہ GL_OES_geometry_نقطہ_سائز
#تعریف_کرو GL_OES_geometry_نقطہ_سائز 1
#اگر_ختم /* GL_OES_geometry_point_size */

#اگر_غیر_تعریف_شدہ GL_OES_geometry_shader
#تعریف_کرو GL_OES_geometry_shader 1
#تعریف_کرو GL_GEOMETRY_SHADER_OES            0x8DD9
#تعریف_کرو GL_GEOMETRY_SHADER_ثنائی_ہندسہ_OES        0x00000004
#تعریف_کرو GL_GEOMETRY_LINKED_VERTICES_برآمد_OES 0x8916
#تعریف_کرو GL_GEOMETRY_LINKED_داخلہ_TYPE_OES 0x8917
#تعریف_کرو GL_GEOMETRY_LINKED_OUTPUT_TYPE_OES 0x8918
#تعریف_کرو GL_GEOMETRY_SHADER_INVOCATIONS_OES 0x887F
#تعریف_کرو GL_LAYER_PROVOKING_راس_OES     0x825E
#تعریف_کرو GL_سطریں_ADJACENCY_OES            0x000A
#تعریف_کرو GL_سطر_STRIP_ADJACENCY_OES       0x000B
#تعریف_کرو GL_TRIANGLES_ADJACENCY_OES        0x000C
#تعریف_کرو GL_TRIANGLE_STRIP_ADJACENCY_OES   0x000D
#تعریف_کرو GL_MAX_GEOMETRY_یکساں_COMPONENTS_OES 0x8DDF
#تعریف_کرو GL_MAX_GEOMETRY_یکساں_بلاکیں_OES 0x8A2C
#تعریف_کرو GL_MAX_COMBINED_GEOMETRY_یکساں_COMPONENTS_OES 0x8A32
#تعریف_کرو GL_MAX_GEOMETRY_داخلہ_COMPONENTS_OES 0x9123
#تعریف_کرو GL_MAX_GEOMETRY_OUTPUT_COMPONENTS_OES 0x9124
#تعریف_کرو GL_MAX_GEOMETRY_OUTPUT_VERTICES_OES 0x8DE0
#تعریف_کرو GL_MAX_GEOMETRY_کل_OUTPUT_COMPONENTS_OES 0x8DE1
#تعریف_کرو GL_MAX_GEOMETRY_SHADER_INVOCATIONS_OES 0x8E5A
#تعریف_کرو GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_OES 0x8C29
#تعریف_کرو GL_MAX_GEOMETRY_ATOMIC_شمار_BUFFERS_OES 0x92CF
#تعریف_کرو GL_MAX_GEOMETRY_ATOMIC_COUNTERS_OES 0x92D5
#تعریف_کرو GL_MAX_GEOMETRY_IMAGE_UNIFORMS_OES 0x90CD
#تعریف_کرو GL_MAX_GEOMETRY_SHADER_STORAGE_بلاکیں_OES 0x90D7
#تعریف_کرو GL_پہلا_راس_CONVENTION_OES    0x8E4D
#تعریف_کرو GL_آخری_راس_CONVENTION_OES     0x8E4E
#تعریف_کرو GL_UNDEFINED_راس_OES           0x8260
#تعریف_کرو GL_PRIMITIVES_GENERATED_OES       0x8C87
#تعریف_کرو GL_FRAMEBUFFER_DEFAULT_LAYERS_OES 0x9312
#تعریف_کرو GL_MAX_FRAMEBUFFER_LAYERS_OES     0x9317
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_OES 0x8DA8
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_LAYERED_OES 0x8DA7
#تعریف_کرو GL_REFERENCED_BY_GEOMETRY_SHADER_OES 0x9309
قسمتعریف خالی (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREOESPROC) (GLenum ہدف, GLenum attachment, GLuint texture, GLint level);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glFramebufferTextureOES (GLenum ہدف, GLenum attachment, GLuint texture, GLint level);
#اگر_ختم
#اگر_ختم /* GL_OES_geometry_shader */

#اگر_غیر_تعریف_شدہ GL_OES_get_پروگرام_ثنائی
#تعریف_کرو GL_OES_get_پروگرام_ثنائی 1
#تعریف_کرو GL_پروگرام_ثنائی_لمبائی_OES      0x8741
#تعریف_کرو GL_عدد_پروگرام_ثنائی_FORMATS_OES 0x87FE
#تعریف_کرو GL_پروگرام_ثنائی_FORMATS_OES     0x87FF
قسمتعریف خالی (GL_APIENTRYP PFNGLGETPROGRAMBINARYOESPROC) (GLuint پروگرام, GLsizei buf_سائز, GLsizei *لمبائی, GLenum *ثنائی_Format, خالی *ثنائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMBINARYOESPROC) (GLuint پروگرام, GLenum ثنائی_Format, ثابت خالی *ثنائی, GLint لمبائی);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_Get_پروگرام_ثنائی_OES (GLuint پروگرام, GLsizei buf_سائز, GLsizei *لمبائی, GLenum *ثنائی_Format, خالی *ثنائی);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_ثنائی_OES (GLuint پروگرام, GLenum ثنائی_Format, ثابت خالی *ثنائی, GLint لمبائی);
#اگر_ختم
#اگر_ختم /* GL_OES_get_program_binary */

#اگر_غیر_تعریف_شدہ GL_OES_gpu_shader5
#تعریف_کرو GL_OES_gpu_shader5 1
#اگر_ختم /* GL_OES_gpu_shader5 */

#اگر_غیر_تعریف_شدہ GL_OES_mapbuffer
#تعریف_کرو GL_OES_mapbuffer 1
#تعریف_کرو GL_WRITE_ONLY_OES                 0x88B9
#تعریف_کرو GL_بفر_ACCESS_OES              0x88BB
#تعریف_کرو GL_بفر_MAPPED_OES              0x88BC
#تعریف_کرو GL_بفر_MAP_اشارہ_گر_OES         0x88BD
قسمتعریف خالی *(GL_APIENTRYP PFNGLMAPBUFFEROESPROC) (GLenum ہدف, GLenum access);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLUNMAPBUFFEROESPROC) (GLenum ہدف);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETBUFFERPOINTERVOESPROC) (GLenum ہدف, GLenum pname, خالی **params);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی *GL_APIENTRY gl_Map_بفر_OES (GLenum ہدف, GLenum access);
GL_APICALL GLboolean GL_APIENTRY gl_Unmap_بفر_OES (GLenum ہدف);
GL_APICALL خالی GL_APIENTRY gl_Get_بفر_Pointerv_OES (GLenum ہدف, GLenum pname, خالی **params);
#اگر_ختم
#اگر_ختم /* GL_OES_mapbuffer */

#اگر_غیر_تعریف_شدہ GL_OES_packed_گہرائی_stencil
#تعریف_کرو GL_OES_packed_گہرائی_stencil 1
#تعریف_کرو GL_گہرائی_STENCIL_OES              0x84F9
#تعریف_کرو GL_UNSIGNED_INT_24_8_OES          0x84FA
#تعریف_کرو GL_DEPTH24_STENCIL8_OES           0x88F0
#اگر_ختم /* GL_OES_packed_depth_stencil */

#اگر_غیر_تعریف_شدہ GL_OES_primitive_bounding_box
#تعریف_کرو GL_OES_primitive_bounding_box 1
#تعریف_کرو GL_PRIMITIVE_BOUNDING_BOX_OES     0x92BE
قسمتعریف خالی (GL_APIENTRYP PFNGLPRIMITIVEBOUNDINGBOXOESPROC) (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glPrimitiveBoundingBoxOES (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
#اگر_ختم
#اگر_ختم /* GL_OES_primitive_bounding_box */

#اگر_غیر_تعریف_شدہ GL_OES_required_internalformat
#تعریف_کرو GL_OES_required_internalformat 1
#تعریف_کرو GL_ALPHA8_OES                     0x803C
#تعریف_کرو GL_گہرائی_COMPONENT16_OES          0x81A5
#تعریف_کرو GL_LUMINANCE4_ALPHA4_OES          0x8043
#تعریف_کرو GL_LUMINANCE8_ALPHA8_OES          0x8045
#تعریف_کرو GL_LUMINANCE8_OES                 0x8040
#تعریف_کرو GL_RGBA4_OES                      0x8056
#تعریف_کرو GL_RGB5_A1_OES                    0x8057
#تعریف_کرو GL_RGB565_OES                     0x8D62
#تعریف_کرو GL_RGB8_OES                       0x8051
#تعریف_کرو GL_RGBA8_OES                      0x8058
#تعریف_کرو GL_RGB10_EXT                      0x8052
#تعریف_کرو GL_RGB10_A2_EXT                   0x8059
#اگر_ختم /* GL_OES_required_internalformat */

#اگر_غیر_تعریف_شدہ GL_OES_rgb8_rgba8
#تعریف_کرو GL_OES_rgb8_rgba8 1
#اگر_ختم /* GL_OES_rgb8_rgba8 */

#اگر_غیر_تعریف_شدہ GL_OES_sample_shading
#تعریف_کرو GL_OES_sample_shading 1
#تعریف_کرو GL_SAMPLE_SHADING_OES             0x8C36
#تعریف_کرو GL_MIN_SAMPLE_SHADING_قدر_OES   0x8C37
قسمتعریف خالی (GL_APIENTRYP PFNGLMINSAMPLESHADINGOESPROC) (GLfloat قدر);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glMinSampleShadingOES (GLfloat قدر);
#اگر_ختم
#اگر_ختم /* GL_OES_sample_shading */

#اگر_غیر_تعریف_شدہ GL_OES_sample_variables
#تعریف_کرو GL_OES_sample_variables 1
#اگر_ختم /* GL_OES_sample_variables */

#اگر_غیر_تعریف_شدہ GL_OES_shader_image_atomic
#تعریف_کرو GL_OES_shader_image_atomic 1
#اگر_ختم /* GL_OES_shader_image_atomic */

#اگر_غیر_تعریف_شدہ GL_OES_shader_io_بلاکیں
#تعریف_کرو GL_OES_shader_io_بلاکیں 1
#اگر_ختم /* GL_OES_shader_io_blocks */

#اگر_غیر_تعریف_شدہ GL_OES_shader_multisample_interpolation
#تعریف_کرو GL_OES_shader_multisample_interpolation 1
#تعریف_کرو GL_MIN_FRAGMENT_INTERPOLATION_انحراف_OES 0x8E5B
#تعریف_کرو GL_MAX_FRAGMENT_INTERPOLATION_انحراف_OES 0x8E5C
#تعریف_کرو GL_FRAGMENT_INTERPOLATION_انحراف_بٹ_OES 0x8E5D
#اگر_ختم /* GL_OES_shader_multisample_interpolation */

#اگر_غیر_تعریف_شدہ GL_OES_standard_derivatives
#تعریف_کرو GL_OES_standard_derivatives 1
#تعریف_کرو GL_FRAGMENT_SHADER_DERIVATIVE_HINT_OES 0x8B8B
#اگر_ختم /* GL_OES_standard_derivatives */

#اگر_غیر_تعریف_شدہ GL_OES_stencil1
#تعریف_کرو GL_OES_stencil1 1
#تعریف_کرو GL_STENCIL_INDEX1_OES             0x8D46
#اگر_ختم /* GL_OES_stencil1 */

#اگر_غیر_تعریف_شدہ GL_OES_stencil4
#تعریف_کرو GL_OES_stencil4 1
#تعریف_کرو GL_STENCIL_INDEX4_OES             0x8D47
#اگر_ختم /* GL_OES_stencil4 */

#اگر_غیر_تعریف_شدہ GL_OES_surfaceless_context
#تعریف_کرو GL_OES_surfaceless_context 1
#تعریف_کرو GL_FRAMEBUFFER_UNDEFINED_OES      0x8219
#اگر_ختم /* GL_OES_surfaceless_context */

#اگر_غیر_تعریف_شدہ GL_OES_tessellation_نقطہ_سائز
#تعریف_کرو GL_OES_tessellation_نقطہ_سائز 1
#اگر_ختم /* GL_OES_tessellation_point_size */

#اگر_غیر_تعریف_شدہ GL_OES_tessellation_shader
#تعریف_کرو GL_OES_tessellation_shader 1
#تعریف_کرو GL_PATCHES_OES                    0x000E
#تعریف_کرو GL_PATCH_VERTICES_OES             0x8E72
#تعریف_کرو GL_TESS_CONTROL_OUTPUT_VERTICES_OES 0x8E75
#تعریف_کرو GL_TESS_GEN_منوال_OES              0x8E76
#تعریف_کرو GL_TESS_GEN_SPACING_OES           0x8E77
#تعریف_کرو GL_TESS_GEN_راس_ترتیب_OES      0x8E78
#تعریف_کرو GL_TESS_GEN_نقطہ_منوال_OES        0x8E79
#تعریف_کرو GL_ISOLINES_OES                   0x8E7A
#تعریف_کرو GL_QUADS_OES                      0x0007
#تعریف_کرو GL_FRACTIONAL_ODD_OES             0x8E7B
#تعریف_کرو GL_FRACTIONAL_EVEN_OES            0x8E7C
#تعریف_کرو GL_MAX_PATCH_VERTICES_OES         0x8E7D
#تعریف_کرو GL_MAX_TESS_GEN_LEVEL_OES         0x8E7E
#تعریف_کرو GL_MAX_TESS_CONTROL_یکساں_COMPONENTS_OES 0x8E7F
#تعریف_کرو GL_MAX_TESS_EVALUATION_یکساں_COMPONENTS_OES 0x8E80
#تعریف_کرو GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS_OES 0x8E81
#تعریف_کرو GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS_OES 0x8E82
#تعریف_کرو GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS_OES 0x8E83
#تعریف_کرو GL_MAX_TESS_PATCH_COMPONENTS_OES  0x8E84
#تعریف_کرو GL_MAX_TESS_CONTROL_کل_OUTPUT_COMPONENTS_OES 0x8E85
#تعریف_کرو GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS_OES 0x8E86
#تعریف_کرو GL_MAX_TESS_CONTROL_یکساں_بلاکیں_OES 0x8E89
#تعریف_کرو GL_MAX_TESS_EVALUATION_یکساں_بلاکیں_OES 0x8E8A
#تعریف_کرو GL_MAX_TESS_CONTROL_داخلہ_COMPONENTS_OES 0x886C
#تعریف_کرو GL_MAX_TESS_EVALUATION_داخلہ_COMPONENTS_OES 0x886D
#تعریف_کرو GL_MAX_COMBINED_TESS_CONTROL_یکساں_COMPONENTS_OES 0x8E1E
#تعریف_کرو GL_MAX_COMBINED_TESS_EVALUATION_یکساں_COMPONENTS_OES 0x8E1F
#تعریف_کرو GL_MAX_TESS_CONTROL_ATOMIC_شمار_BUFFERS_OES 0x92CD
#تعریف_کرو GL_MAX_TESS_EVALUATION_ATOMIC_شمار_BUFFERS_OES 0x92CE
#تعریف_کرو GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS_OES 0x92D3
#تعریف_کرو GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS_OES 0x92D4
#تعریف_کرو GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS_OES 0x90CB
#تعریف_کرو GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS_OES 0x90CC
#تعریف_کرو GL_MAX_TESS_CONTROL_SHADER_STORAGE_بلاکیں_OES 0x90D8
#تعریف_کرو GL_MAX_TESS_EVALUATION_SHADER_STORAGE_بلاکیں_OES 0x90D9
#تعریف_کرو GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED_OES 0x8221
#تعریف_کرو GL_IS_فی_PATCH_OES               0x92E7
#تعریف_کرو GL_REFERENCED_BY_TESS_CONTROL_SHADER_OES 0x9307
#تعریف_کرو GL_REFERENCED_BY_TESS_EVALUATION_SHADER_OES 0x9308
#تعریف_کرو GL_TESS_CONTROL_SHADER_OES        0x8E88
#تعریف_کرو GL_TESS_EVALUATION_SHADER_OES     0x8E87
#تعریف_کرو GL_TESS_CONTROL_SHADER_ثنائی_ہندسہ_OES    0x00000008
#تعریف_کرو GL_TESS_EVALUATION_SHADER_ثنائی_ہندسہ_OES 0x00000010
قسمتعریف خالی (GL_APIENTRYP PFNGLPATCHPARAMETERIOESPROC) (GLenum pname, GLint قدر);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glPatchParameteriOES (GLenum pname, GLint قدر);
#اگر_ختم
#اگر_ختم /* GL_OES_tessellation_shader */

#اگر_غیر_تعریف_شدہ GL_OES_texture_3D
#تعریف_کرو GL_OES_texture_3D 1
#تعریف_کرو GL_TEXTURE_WRAP_R_OES             0x8072
#تعریف_کرو GL_TEXTURE_3D_OES                 0x806F
#تعریف_کرو GL_TEXTURE_BINDING_3D_OES         0x806A
#تعریف_کرو GL_MAX_3_D_TEXTURE_سائز_OES        0x8073
#تعریف_کرو GL_SAMPLER_3D_OES                 0x8B5F
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_3D_ZOFFSET_OES 0x8CD4
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXIMAGE3DOESPROC) (GLenum ہدف, GLint level, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLint border, GLenum format, GLenum type, ثابت خالی *pixels);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXSUBIMAGE3DOESPROC) (GLenum ہدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLenum format, GLenum type, ثابت خالی *pixels);
قسمتعریف خالی (GL_APIENTRYP PFNGLCOPYTEXSUBIMAGE3DOESPROC) (GLenum ہدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei چوڑائی, GLsizei اونچائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLCOMPRESSEDTEXIMAGE3DOESPROC) (GLenum ہدف, GLint level, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLint border, GLsizei image_سائز, ثابت خالی *ڈیٹا);
قسمتعریف خالی (GL_APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE3DOESPROC) (GLenum ہدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLenum format, GLsizei image_سائز, ثابت خالی *ڈیٹا);
قسمتعریف خالی (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE3DOESPROC) (GLenum ہدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glTexImage3DOES (GLenum ہدف, GLint level, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLint border, GLenum format, GLenum type, ثابت خالی *pixels);
GL_APICALL خالی GL_APIENTRY glTexSubImage3DOES (GLenum ہدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLenum format, GLenum type, ثابت خالی *pixels);
GL_APICALL خالی GL_APIENTRY glCopyTexSubImage3DOES (GLenum ہدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei چوڑائی, GLsizei اونچائی);
GL_APICALL خالی GL_APIENTRY glCompressedTexImage3DOES (GLenum ہدف, GLint level, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLint border, GLsizei image_سائز, ثابت خالی *ڈیٹا);
GL_APICALL خالی GL_APIENTRY glCompressedTexSubImage3DOES (GLenum ہدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLenum format, GLsizei image_سائز, ثابت خالی *ڈیٹا);
GL_APICALL خالی GL_APIENTRY glFramebufferTexture3DOES (GLenum ہدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
#اگر_ختم
#اگر_ختم /* GL_OES_texture_3D */

#اگر_غیر_تعریف_شدہ GL_OES_texture_border_clamp
#تعریف_کرو GL_OES_texture_border_clamp 1
#تعریف_کرو GL_TEXTURE_BORDER_COLOR_OES       0x1004
#تعریف_کرو GL_CLAMP_مقصد_BORDER_OES            0x812D
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXPARAMETERIIVOESPROC) (GLenum ہدف, GLenum pname, ثابت GLint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXPARAMETERIUIVOESPROC) (GLenum ہدف, GLenum pname, ثابت GLuint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETTEXPARAMETERIIVOESPROC) (GLenum ہدف, GLenum pname, GLint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETTEXPARAMETERIUIVOESPROC) (GLenum ہدف, GLenum pname, GLuint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLSAMPLERPARAMETERIIVOESPROC) (GLuint sampler, GLenum pname, ثابت GLint *param);
قسمتعریف خالی (GL_APIENTRYP PFNGLSAMPLERPARAMETERIUIVOESPROC) (GLuint sampler, GLenum pname, ثابت GLuint *param);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIIVOESPROC) (GLuint sampler, GLenum pname, GLint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIUIVOESPROC) (GLuint sampler, GLenum pname, GLuint *params);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glTexParameterIivOES (GLenum ہدف, GLenum pname, ثابت GLint *params);
GL_APICALL خالی GL_APIENTRY glTexParameterIuivOES (GLenum ہدف, GLenum pname, ثابت GLuint *params);
GL_APICALL خالی GL_APIENTRY glGetTexParameterIivOES (GLenum ہدف, GLenum pname, GLint *params);
GL_APICALL خالی GL_APIENTRY glGetTexParameterIuivOES (GLenum ہدف, GLenum pname, GLuint *params);
GL_APICALL خالی GL_APIENTRY glSamplerParameterIivOES (GLuint sampler, GLenum pname, ثابت GLint *param);
GL_APICALL خالی GL_APIENTRY glSamplerParameterIuivOES (GLuint sampler, GLenum pname, ثابت GLuint *param);
GL_APICALL خالی GL_APIENTRY glGetSamplerParameterIivOES (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL خالی GL_APIENTRY glGetSamplerParameterIuivOES (GLuint sampler, GLenum pname, GLuint *params);
#اگر_ختم
#اگر_ختم /* GL_OES_texture_border_clamp */

#اگر_غیر_تعریف_شدہ GL_OES_texture_بفر
#تعریف_کرو GL_OES_texture_بفر 1
#تعریف_کرو GL_TEXTURE_بفر_OES             0x8C2A
#تعریف_کرو GL_TEXTURE_بفر_BINDING_OES     0x8C2A
#تعریف_کرو GL_MAX_TEXTURE_بفر_سائز_OES    0x8C2B
#تعریف_کرو GL_TEXTURE_BINDING_بفر_OES     0x8C2C
#تعریف_کرو GL_TEXTURE_بفر_ڈیٹا_STORE_BINDING_OES 0x8C2D
#تعریف_کرو GL_TEXTURE_بفر_انحراف_ALIGNMENT_OES 0x919F
#تعریف_کرو GL_SAMPLER_بفر_OES             0x8DC2
#تعریف_کرو GL_INT_SAMPLER_بفر_OES         0x8DD0
#تعریف_کرو GL_UNSIGNED_INT_SAMPLER_بفر_OES 0x8DD8
#تعریف_کرو GL_IMAGE_بفر_OES               0x9051
#تعریف_کرو GL_INT_IMAGE_بفر_OES           0x905C
#تعریف_کرو GL_UNSIGNED_INT_IMAGE_بفر_OES  0x9067
#تعریف_کرو GL_TEXTURE_بفر_انحراف_OES      0x919D
#تعریف_کرو GL_TEXTURE_بفر_سائز_OES        0x919E
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXBUFFEROESPROC) (GLenum ہدف, GLenum internalformat, GLuint بفر_2);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXBUFFERRANGEOESPROC) (GLenum ہدف, GLenum internalformat, GLuint بفر_2, GLintptr انحراف_2, GLsizeiptr سائز);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_Tex_بفر_OES (GLenum ہدف, GLenum internalformat, GLuint بفر_2);
GL_APICALL خالی GL_APIENTRY gl_Tex_بفر_Range_OES (GLenum ہدف, GLenum internalformat, GLuint بفر_2, GLintptr انحراف_2, GLsizeiptr سائز);
#اگر_ختم
#اگر_ختم /* GL_OES_texture_buffer */

#اگر_غیر_تعریف_شدہ GL_OES_texture_compression_astc
#تعریف_کرو GL_OES_texture_compression_astc 1
#تعریف_کرو GL_COMPRESSED_RGBA_ASTC_3x3x3_OES 0x93C0
#تعریف_کرو GL_COMPRESSED_RGBA_ASTC_4x3x3_OES 0x93C1
#تعریف_کرو GL_COMPRESSED_RGBA_ASTC_4x4x3_OES 0x93C2
#تعریف_کرو GL_COMPRESSED_RGBA_ASTC_4x4x4_OES 0x93C3
#تعریف_کرو GL_COMPRESSED_RGBA_ASTC_5x4x4_OES 0x93C4
#تعریف_کرو GL_COMPRESSED_RGBA_ASTC_5x5x4_OES 0x93C5
#تعریف_کرو GL_COMPRESSED_RGBA_ASTC_5x5x5_OES 0x93C6
#تعریف_کرو GL_COMPRESSED_RGBA_ASTC_6x5x5_OES 0x93C7
#تعریف_کرو GL_COMPRESSED_RGBA_ASTC_6x6x5_OES 0x93C8
#تعریف_کرو GL_COMPRESSED_RGBA_ASTC_6x6x6_OES 0x93C9
#تعریف_کرو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_3x3x3_OES 0x93E0
#تعریف_کرو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x3x3_OES 0x93E1
#تعریف_کرو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4x3_OES 0x93E2
#تعریف_کرو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4x4_OES 0x93E3
#تعریف_کرو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4x4_OES 0x93E4
#تعریف_کرو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5x4_OES 0x93E5
#تعریف_کرو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5x5_OES 0x93E6
#تعریف_کرو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5x5_OES 0x93E7
#تعریف_کرو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6x5_OES 0x93E8
#تعریف_کرو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6x6_OES 0x93E9
#اگر_ختم /* GL_OES_texture_compression_astc */

#اگر_غیر_تعریف_شدہ GL_OES_texture_cube_map_array
#تعریف_کرو GL_OES_texture_cube_map_array 1
#تعریف_کرو GL_TEXTURE_CUBE_MAP_ARRAY_OES     0x9009
#تعریف_کرو GL_TEXTURE_BINDING_CUBE_MAP_ARRAY_OES 0x900A
#تعریف_کرو GL_SAMPLER_CUBE_MAP_ARRAY_OES     0x900C
#تعریف_کرو GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW_OES 0x900D
#تعریف_کرو GL_INT_SAMPLER_CUBE_MAP_ARRAY_OES 0x900E
#تعریف_کرو GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY_OES 0x900F
#تعریف_کرو GL_IMAGE_CUBE_MAP_ARRAY_OES       0x9054
#تعریف_کرو GL_INT_IMAGE_CUBE_MAP_ARRAY_OES   0x905F
#تعریف_کرو GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY_OES 0x906A
#اگر_ختم /* GL_OES_texture_cube_map_array */

#اگر_غیر_تعریف_شدہ GL_OES_texture_float
#تعریف_کرو GL_OES_texture_float 1
#اگر_ختم /* GL_OES_texture_float */

#اگر_غیر_تعریف_شدہ GL_OES_texture_float_خطی
#تعریف_کرو GL_OES_texture_float_خطی 1
#اگر_ختم /* GL_OES_texture_float_linear */

#اگر_غیر_تعریف_شدہ GL_OES_texture_half_float
#تعریف_کرو GL_OES_texture_half_float 1
#تعریف_کرو GL_HALF_FLOAT_OES                 0x8D61
#اگر_ختم /* GL_OES_texture_half_float */

#اگر_غیر_تعریف_شدہ GL_OES_texture_half_float_خطی
#تعریف_کرو GL_OES_texture_half_float_خطی 1
#اگر_ختم /* GL_OES_texture_half_float_linear */

#اگر_غیر_تعریف_شدہ GL_OES_texture_npot
#تعریف_کرو GL_OES_texture_npot 1
#اگر_ختم /* GL_OES_texture_npot */

#اگر_غیر_تعریف_شدہ GL_OES_texture_stencil8
#تعریف_کرو GL_OES_texture_stencil8 1
#تعریف_کرو GL_STENCIL_اشاریہ_OES              0x1901
#تعریف_کرو GL_STENCIL_INDEX8_OES             0x8D48
#اگر_ختم /* GL_OES_texture_stencil8 */

#اگر_غیر_تعریف_شدہ GL_OES_texture_storage_multisample_2d_array
#تعریف_کرو GL_OES_texture_storage_multisample_2d_array 1
#تعریف_کرو GL_TEXTURE_2D_MULTISAMPLE_ARRAY_OES 0x9102
#تعریف_کرو GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY_OES 0x9105
#تعریف_کرو GL_SAMPLER_2D_MULTISAMPLE_ARRAY_OES 0x910B
#تعریف_کرو GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY_OES 0x910C
#تعریف_کرو GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY_OES 0x910D
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXSTORAGE3DMULTISAMPLEOESPROC) (GLenum ہدف, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLboolean fixedsamplelocations);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glTexStorage3DMultisampleOES (GLenum ہدف, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLboolean fixedsamplelocations);
#اگر_ختم
#اگر_ختم /* GL_OES_texture_storage_multisample_2d_array */

#اگر_غیر_تعریف_شدہ GL_OES_texture_view
#تعریف_کرو GL_OES_texture_view 1
#تعریف_کرو GL_TEXTURE_VIEW_MIN_LEVEL_OES     0x82DB
#تعریف_کرو GL_TEXTURE_VIEW_عدد_سطحیں_OES    0x82DC
#تعریف_کرو GL_TEXTURE_VIEW_MIN_LAYER_OES     0x82DD
#تعریف_کرو GL_TEXTURE_VIEW_عدد_LAYERS_OES    0x82DE
#تعریف_کرو GL_TEXTURE_IMMUTABLE_سطحیں       0x82DF
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXTUREVIEWOESPROC) (GLuint texture, GLenum ہدف, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glTextureViewOES (GLuint texture, GLenum ہدف, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
#اگر_ختم
#اگر_ختم /* GL_OES_texture_view */

#اگر_غیر_تعریف_شدہ GL_OES_راس_array_object
#تعریف_کرو GL_OES_راس_array_object 1
#تعریف_کرو GL_راس_ARRAY_BINDING_OES       0x85B5
قسمتعریف خالی (GL_APIENTRYP PFNGLBINDVERTEXARRAYOESPROC) (GLuint array);
قسمتعریف خالی (GL_APIENTRYP PFNGLDELETEVERTEXARRAYSOESPROC) (GLsizei n, ثابت GLuint *arrays);
قسمتعریف خالی (GL_APIENTRYP PFNGLGENVERTEXARRAYSOESPROC) (GLsizei n, GLuint *arrays);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLISVERTEXARRAYOESPROC) (GLuint array);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_Bind_راس_Array_OES (GLuint array);
GL_APICALL خالی GL_APIENTRY gl_Delete_راس_Arrays_OES (GLsizei n, ثابت GLuint *arrays);
GL_APICALL خالی GL_APIENTRY gl_Gen_راس_Arrays_OES (GLsizei n, GLuint *arrays);
GL_APICALL GLboolean GL_APIENTRY gl_Is_راس_Array_OES (GLuint array);
#اگر_ختم
#اگر_ختم /* GL_OES_vertex_array_object */

#اگر_غیر_تعریف_شدہ GL_OES_راس_half_float
#تعریف_کرو GL_OES_راس_half_float 1
#اگر_ختم /* GL_OES_vertex_half_float */

#اگر_غیر_تعریف_شدہ GL_OES_راس_type_10_10_10_2
#تعریف_کرو GL_OES_راس_type_10_10_10_2 1
#تعریف_کرو GL_UNSIGNED_INT_10_10_10_2_OES    0x8DF6
#تعریف_کرو GL_INT_10_10_10_2_OES             0x8DF7
#اگر_ختم /* GL_OES_vertex_type_10_10_10_2 */

#اگر_غیر_تعریف_شدہ GL_OES_viewport_array
#تعریف_کرو GL_OES_viewport_array 1
#تعریف_کرو GL_MAX_VIEWPORTS_OES              0x825B
#تعریف_کرو GL_VIEWPORT_SUBPIXEL_بٹ_OES     0x825C
#تعریف_کرو GL_VIEWPORT_BOUNDS_RANGE_OES      0x825D
#تعریف_کرو GL_VIEWPORT_اشاریہ_PROVOKING_راس_OES 0x825F
قسمتعریف خالی (GL_APIENTRYP PFNGLVIEWPORTARRAYVOESPROC) (GLuint پہلا, GLsizei گنتی, ثابت GLfloat *v);
قسمتعریف خالی (GL_APIENTRYP PFNGLVIEWPORTINDEXEDFOESPROC) (GLuint اشاریہ, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
قسمتعریف خالی (GL_APIENTRYP PFNGLVIEWPORTINDEXEDFVOESPROC) (GLuint اشاریہ, ثابت GLfloat *v);
قسمتعریف خالی (GL_APIENTRYP PFNGLSCISSORARRAYVOESPROC) (GLuint پہلا, GLsizei گنتی, ثابت GLint *v);
قسمتعریف خالی (GL_APIENTRYP PFNGLSCISSORINDEXEDOESPROC) (GLuint اشاریہ, GLint بایاں, GLint bottom, GLsizei چوڑائی, GLsizei اونچائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLSCISSORINDEXEDVOESPROC) (GLuint اشاریہ, ثابت GLint *v);
قسمتعریف خالی (GL_APIENTRYP PFNGLDEPTHRANGEARRAYFVOESPROC) (GLuint پہلا, GLsizei گنتی, ثابت GLfloat *v);
قسمتعریف خالی (GL_APIENTRYP PFNGLDEPTHRANGEINDEXEDFOESPROC) (GLuint اشاریہ, GLfloat n, GLfloat f);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETFLOATI_VOESPROC) (GLenum ہدف, GLuint اشاریہ, GLfloat *ڈیٹا);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glViewportArrayvOES (GLuint پہلا, GLsizei گنتی, ثابت GLfloat *v);
GL_APICALL خالی GL_APIENTRY glViewportIndexedfOES (GLuint اشاریہ, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
GL_APICALL خالی GL_APIENTRY glViewportIndexedfvOES (GLuint اشاریہ, ثابت GLfloat *v);
GL_APICALL خالی GL_APIENTRY glScissorArrayvOES (GLuint پہلا, GLsizei گنتی, ثابت GLint *v);
GL_APICALL خالی GL_APIENTRY gl_Scissor_اشاریہ_دار_OES (GLuint اشاریہ, GLint بایاں, GLint bottom, GLsizei چوڑائی, GLsizei اونچائی);
GL_APICALL خالی GL_APIENTRY glScissorIndexedvOES (GLuint اشاریہ, ثابت GLint *v);
GL_APICALL خالی GL_APIENTRY gl_گہرائی_Range_Arrayfv_OES (GLuint پہلا, GLsizei گنتی, ثابت GLfloat *v);
GL_APICALL خالی GL_APIENTRY gl_گہرائی_Range_Indexedf_OES (GLuint اشاریہ, GLfloat n, GLfloat f);
GL_APICALL خالی GL_APIENTRY glGetFloati_vOES (GLenum ہدف, GLuint اشاریہ, GLfloat *ڈیٹا);
#اگر_ختم
#اگر_ختم /* GL_OES_viewport_array */

#اگر_غیر_تعریف_شدہ GL_AMD_compressed_3DC_texture
#تعریف_کرو GL_AMD_compressed_3DC_texture 1
#تعریف_کرو GL_3DC_X_AMD                      0x87F9
#تعریف_کرو GL_3DC_XY_AMD                     0x87FA
#اگر_ختم /* GL_AMD_compressed_3DC_texture */

#اگر_غیر_تعریف_شدہ GL_AMD_compressed_ATC_texture
#تعریف_کرو GL_AMD_compressed_ATC_texture 1
#تعریف_کرو GL_ATC_RGB_AMD                    0x8C92
#تعریف_کرو GL_ATC_RGBA_EXPLICIT_ALPHA_AMD    0x8C93
#تعریف_کرو GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD 0x87EE
#اگر_ختم /* GL_AMD_compressed_ATC_texture */

#اگر_غیر_تعریف_شدہ GL_AMD_framebuffer_multisample_advanced
#تعریف_کرو GL_AMD_framebuffer_multisample_advanced 1
#تعریف_کرو GL_RENDERBUFFER_STORAGE_SAMPLES_AMD 0x91B2
#تعریف_کرو GL_MAX_COLOR_FRAMEBUFFER_SAMPLES_AMD 0x91B3
#تعریف_کرو GL_MAX_COLOR_FRAMEBUFFER_STORAGE_SAMPLES_AMD 0x91B4
#تعریف_کرو GL_MAX_گہرائی_STENCIL_FRAMEBUFFER_SAMPLES_AMD 0x91B5
#تعریف_کرو GL_عدد_SUPPORTED_MULTISAMPLE_MODES_AMD 0x91B6
#تعریف_کرو GL_SUPPORTED_MULTISAMPLE_MODES_AMD 0x91B7
قسمتعریف خالی (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC) (GLenum ہدف, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC) (GLuint renderbuffer, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glRenderbufferStorageMultisampleAdvancedAMD (GLenum ہدف, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
GL_APICALL خالی GL_APIENTRY glNamedRenderbufferStorageMultisampleAdvancedAMD (GLuint renderbuffer, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
#اگر_ختم
#اگر_ختم /* GL_AMD_framebuffer_multisample_advanced */

#اگر_غیر_تعریف_شدہ GL_AMD_performance_monitor
#تعریف_کرو GL_AMD_performance_monitor 1
#تعریف_کرو GL_شمار_TYPE_AMD               0x8BC0
#تعریف_کرو GL_شمار_RANGE_AMD              0x8BC1
#تعریف_کرو GL_UNSIGNED_INT64_AMD             0x8BC2
#تعریف_کرو GL_PERCENTAGE_AMD                 0x8BC3
#تعریف_کرو GL_PERFMON_نتیجہ_دستیاب_AMD   0x8BC4
#تعریف_کرو GL_PERFMON_نتیجہ_سائز_AMD        0x8BC5
#تعریف_کرو GL_PERFMON_نتیجہ_AMD             0x8BC6
قسمتعریف خالی (GL_APIENTRYP PFNGLGETPERFMONITORGROUPSAMDPROC) (GLint *عدد_Groups, GLsizei groups_سائز, GLuint *groups);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETPERFMONITORCOUNTERSAMDPROC) (GLuint گروہ, GLint *عدد_Counters, GLint *max_فعال_Counters, GLsizei شمار_سائز, GLuint *counters);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETPERFMONITORGROUPSTRINGAMDPROC) (GLuint گروہ, GLsizei buf_سائز, GLsizei *لمبائی, GLchar *گروہ_String);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC) (GLuint گروہ, GLuint شمار_2, GLsizei buf_سائز, GLsizei *لمبائی, GLchar *شمار_String);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETPERFMONITORCOUNTERINFOAMDPROC) (GLuint گروہ, GLuint شمار_2, GLenum pname, خالی *ڈیٹا);
قسمتعریف خالی (GL_APIENTRYP PFNGLGENPERFMONITORSAMDPROC) (GLsizei n, GLuint *monitors);
قسمتعریف خالی (GL_APIENTRYP PFNGLDELETEPERFMONITORSAMDPROC) (GLsizei n, GLuint *monitors);
قسمتعریف خالی (GL_APIENTRYP PFNGLSELECTPERFMONITORCOUNTERSAMDPROC) (GLuint monitor, GLboolean enable, GLuint گروہ, GLint عدد_Counters, GLuint *شمار_List);
قسمتعریف خالی (GL_APIENTRYP PFNGLBEGINPERFMONITORAMDPROC) (GLuint monitor);
قسمتعریف خالی (GL_APIENTRYP PFNGLENDPERFMONITORAMDPROC) (GLuint monitor);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETPERFMONITORCOUNTERDATAAMDPROC) (GLuint monitor, GLenum pname, GLsizei ڈیٹا_سائز_2, GLuint *ڈیٹا, GLint *بائٹیں_Written);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glGetPerfMonitorGroupsAMD (GLint *عدد_Groups, GLsizei groups_سائز, GLuint *groups);
GL_APICALL خالی GL_APIENTRY glGetPerfMonitorCountersAMD (GLuint گروہ, GLint *عدد_Counters, GLint *max_فعال_Counters, GLsizei شمار_سائز, GLuint *counters);
GL_APICALL خالی GL_APIENTRY gl_Get_Perf_Monitor_گروہ_String_AMD (GLuint گروہ, GLsizei buf_سائز, GLsizei *لمبائی, GLchar *گروہ_String);
GL_APICALL خالی GL_APIENTRY gl_Get_Perf_Monitor_شمار_String_AMD (GLuint گروہ, GLuint شمار_2, GLsizei buf_سائز, GLsizei *لمبائی, GLchar *شمار_String);
GL_APICALL خالی GL_APIENTRY gl_Get_Perf_Monitor_شمار_Info_AMD (GLuint گروہ, GLuint شمار_2, GLenum pname, خالی *ڈیٹا);
GL_APICALL خالی GL_APIENTRY glGenPerfMonitorsAMD (GLsizei n, GLuint *monitors);
GL_APICALL خالی GL_APIENTRY glDeletePerfMonitorsAMD (GLsizei n, GLuint *monitors);
GL_APICALL خالی GL_APIENTRY glSelectPerfMonitorCountersAMD (GLuint monitor, GLboolean enable, GLuint گروہ, GLint عدد_Counters, GLuint *شمار_List);
GL_APICALL خالی GL_APIENTRY glBeginPerfMonitorAMD (GLuint monitor);
GL_APICALL خالی GL_APIENTRY gl_انتہا_Perf_Monitor_AMD (GLuint monitor);
GL_APICALL خالی GL_APIENTRY gl_Get_Perf_Monitor_شمار_ڈیٹا_AMD (GLuint monitor, GLenum pname, GLsizei ڈیٹا_سائز_2, GLuint *ڈیٹا, GLint *بائٹیں_Written);
#اگر_ختم
#اگر_ختم /* GL_AMD_performance_monitor */

#اگر_غیر_تعریف_شدہ GL_AMD_پروگرام_ثنائی_Z400
#تعریف_کرو GL_AMD_پروگرام_ثنائی_Z400 1
#تعریف_کرو GL_Z400_ثنائی_AMD                0x8740
#اگر_ختم /* GL_AMD_program_binary_Z400 */

#اگر_غیر_تعریف_شدہ GL_ANDROID_extension_pack_es31a
#تعریف_کرو GL_ANDROID_extension_pack_es31a 1
#اگر_ختم /* GL_ANDROID_extension_pack_es31a */

#اگر_غیر_تعریف_شدہ GL_ANGLE_گہرائی_texture
#تعریف_کرو GL_ANGLE_گہرائی_texture 1
#اگر_ختم /* GL_ANGLE_depth_texture */

#اگر_غیر_تعریف_شدہ GL_ANGLE_framebuffer_blit
#تعریف_کرو GL_ANGLE_framebuffer_blit 1
#تعریف_کرو GL_READ_FRAMEBUFFER_ANGLE         0x8CA8
#تعریف_کرو GL_DRAW_FRAMEBUFFER_ANGLE         0x8CA9
#تعریف_کرو GL_DRAW_FRAMEBUFFER_BINDING_ANGLE 0x8CA6
#تعریف_کرو GL_READ_FRAMEBUFFER_BINDING_ANGLE 0x8CAA
قسمتعریف خالی (GL_APIENTRYP PFNGLBLITFRAMEBUFFERANGLEPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield نقاب, GLenum filter);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glBlitFramebufferANGLE (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield نقاب, GLenum filter);
#اگر_ختم
#اگر_ختم /* GL_ANGLE_framebuffer_blit */

#اگر_غیر_تعریف_شدہ GL_ANGLE_framebuffer_multisample
#تعریف_کرو GL_ANGLE_framebuffer_multisample 1
#تعریف_کرو GL_RENDERBUFFER_SAMPLES_ANGLE     0x8CAB
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_ANGLE 0x8D56
#تعریف_کرو GL_MAX_SAMPLES_ANGLE              0x8D57
قسمتعریف خالی (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEANGLEPROC) (GLenum ہدف, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glRenderbufferStorageMultisampleANGLE (GLenum ہدف, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
#اگر_ختم
#اگر_ختم /* GL_ANGLE_framebuffer_multisample */

#اگر_غیر_تعریف_شدہ GL_ANGLE_instanced_arrays
#تعریف_کرو GL_ANGLE_instanced_arrays 1
#تعریف_کرو GL_راس_ATTRIB_ARRAY_مقسوم_علیہ_ANGLE 0x88FE
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDANGLEPROC) (GLenum منوال, GLint پہلا, GLsizei گنتی, GLsizei primcount);
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDANGLEPROC) (GLenum منوال, GLsizei گنتی, GLenum type, ثابت خالی *indices, GLsizei primcount);
قسمتعریف خالی (GL_APIENTRYP PFNGLVERTEXATTRIBDIVISORANGLEPROC) (GLuint اشاریہ, GLuint مقسوم_علیہ);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glDrawArraysInstancedANGLE (GLenum منوال, GLint پہلا, GLsizei گنتی, GLsizei primcount);
GL_APICALL خالی GL_APIENTRY glDrawElementsInstancedANGLE (GLenum منوال, GLsizei گنتی, GLenum type, ثابت خالی *indices, GLsizei primcount);
GL_APICALL خالی GL_APIENTRY gl_راس_Attrib_مقسوم_علیہ_ANGLE (GLuint اشاریہ, GLuint مقسوم_علیہ);
#اگر_ختم
#اگر_ختم /* GL_ANGLE_instanced_arrays */

#اگر_غیر_تعریف_شدہ GL_ANGLE_pack_الٹ_صف_ترتیب
#تعریف_کرو GL_ANGLE_pack_الٹ_صف_ترتیب 1
#تعریف_کرو GL_PACK_الٹ_صف_ترتیب_ANGLE   0x93A4
#اگر_ختم /* GL_ANGLE_pack_reverse_row_order */

#اگر_غیر_تعریف_شدہ GL_ANGLE_پروگرام_ثنائی
#تعریف_کرو GL_ANGLE_پروگرام_ثنائی 1
#تعریف_کرو GL_پروگرام_ثنائی_ANGLE           0x93A6
#اگر_ختم /* GL_ANGLE_program_binary */

#اگر_غیر_تعریف_شدہ GL_ANGLE_texture_compression_dxt3
#تعریف_کرو GL_ANGLE_texture_compression_dxt3 1
#تعریف_کرو GL_COMPRESSED_RGBA_S3TC_DXT3_ANGLE 0x83F2
#اگر_ختم /* GL_ANGLE_texture_compression_dxt3 */

#اگر_غیر_تعریف_شدہ GL_ANGLE_texture_compression_dxt5
#تعریف_کرو GL_ANGLE_texture_compression_dxt5 1
#تعریف_کرو GL_COMPRESSED_RGBA_S3TC_DXT5_ANGLE 0x83F3
#اگر_ختم /* GL_ANGLE_texture_compression_dxt5 */

#اگر_غیر_تعریف_شدہ GL_ANGLE_texture_usage
#تعریف_کرو GL_ANGLE_texture_usage 1
#تعریف_کرو GL_TEXTURE_USAGE_ANGLE            0x93A2
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_ANGLE   0x93A3
#اگر_ختم /* GL_ANGLE_texture_usage */

#اگر_غیر_تعریف_شدہ GL_ANGLE_translated_shader_ماخذ
#تعریف_کرو GL_ANGLE_translated_shader_ماخذ 1
#تعریف_کرو GL_TRANSLATED_SHADER_ماخذ_لمبائی_ANGLE 0x93A0
قسمتعریف خالی (GL_APIENTRYP PFNGLGETTRANSLATEDSHADERSOURCEANGLEPROC) (GLuint shader, GLsizei buf_سائز, GLsizei *لمبائی, GLchar *ماخذ);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_Get_Translated_Shader_ماخذ_ANGLE (GLuint shader, GLsizei buf_سائز, GLsizei *لمبائی, GLchar *ماخذ);
#اگر_ختم
#اگر_ختم /* GL_ANGLE_translated_shader_source */

#اگر_غیر_تعریف_شدہ GL_APPLE_clip_فاصلہ
#تعریف_کرو GL_APPLE_clip_فاصلہ 1
#تعریف_کرو GL_MAX_CLIP_DISTANCES_APPLE       0x0D32
#تعریف_کرو GL_CLIP_DISTANCE0_APPLE           0x3000
#تعریف_کرو GL_CLIP_DISTANCE1_APPLE           0x3001
#تعریف_کرو GL_CLIP_DISTANCE2_APPLE           0x3002
#تعریف_کرو GL_CLIP_DISTANCE3_APPLE           0x3003
#تعریف_کرو GL_CLIP_DISTANCE4_APPLE           0x3004
#تعریف_کرو GL_CLIP_DISTANCE5_APPLE           0x3005
#تعریف_کرو GL_CLIP_DISTANCE6_APPLE           0x3006
#تعریف_کرو GL_CLIP_DISTANCE7_APPLE           0x3007
#اگر_ختم /* GL_APPLE_clip_distance */

#اگر_غیر_تعریف_شدہ GL_APPLE_color_بفر_packed_float
#تعریف_کرو GL_APPLE_color_بفر_packed_float 1
#اگر_ختم /* GL_APPLE_color_buffer_packed_float */

#اگر_غیر_تعریف_شدہ GL_APPLE_copy_texture_سطحیں
#تعریف_کرو GL_APPLE_copy_texture_سطحیں 1
قسمتعریف خالی (GL_APIENTRYP PFNGLCOPYTEXTURELEVELSAPPLEPROC) (GLuint destinationTexture, GLuint ماخذ_Texture, GLint ماخذ_بنیاد_Level, GLsizei ماخذ_Level_گنتی);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_Copy_Texture_سطحیں_APPLE (GLuint destinationTexture, GLuint ماخذ_Texture, GLint ماخذ_بنیاد_Level, GLsizei ماخذ_Level_گنتی);
#اگر_ختم
#اگر_ختم /* GL_APPLE_copy_texture_levels */

#اگر_غیر_تعریف_شدہ GL_APPLE_framebuffer_multisample
#تعریف_کرو GL_APPLE_framebuffer_multisample 1
#تعریف_کرو GL_RENDERBUFFER_SAMPLES_APPLE     0x8CAB
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_APPLE 0x8D56
#تعریف_کرو GL_MAX_SAMPLES_APPLE              0x8D57
#تعریف_کرو GL_READ_FRAMEBUFFER_APPLE         0x8CA8
#تعریف_کرو GL_DRAW_FRAMEBUFFER_APPLE         0x8CA9
#تعریف_کرو GL_DRAW_FRAMEBUFFER_BINDING_APPLE 0x8CA6
#تعریف_کرو GL_READ_FRAMEBUFFER_BINDING_APPLE 0x8CAA
قسمتعریف خالی (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEAPPLEPROC) (GLenum ہدف, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLRESOLVEMULTISAMPLEFRAMEBUFFERAPPLEPROC) (خالی);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glRenderbufferStorageMultisampleAPPLE (GLenum ہدف, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
GL_APICALL خالی GL_APIENTRY glResolveMultisampleFramebufferAPPLE (خالی);
#اگر_ختم
#اگر_ختم /* GL_APPLE_framebuffer_multisample */

#اگر_غیر_تعریف_شدہ GL_APPLE_rgb_422
#تعریف_کرو GL_APPLE_rgb_422 1
#تعریف_کرو GL_RGB_422_APPLE                  0x8A1F
#تعریف_کرو GL_UNSIGNED_SHORT_8_8_APPLE       0x85BA
#تعریف_کرو GL_UNSIGNED_SHORT_8_8_REV_APPLE   0x85BB
#تعریف_کرو GL_RGB_RAW_422_APPLE              0x8A51
#اگر_ختم /* GL_APPLE_rgb_422 */

#اگر_غیر_تعریف_شدہ GL_APPLE_sync
#تعریف_کرو GL_APPLE_sync 1
#تعریف_کرو GL_SYNC_OBJECT_APPLE              0x8A53
#تعریف_کرو GL_MAX_SERVER_WAIT_TIMEOUT_APPLE  0x9111
#تعریف_کرو GL_OBJECT_TYPE_APPLE              0x9112
#تعریف_کرو GL_SYNC_CONDITION_APPLE           0x9113
#تعریف_کرو GL_SYNC_حالت_APPLE              0x9114
#تعریف_کرو GL_SYNC_FLAGS_APPLE               0x9115
#تعریف_کرو GL_SYNC_FENCE_APPLE               0x9116
#تعریف_کرو GL_SYNC_GPU_COMMANDS_COMPLETE_APPLE 0x9117
#تعریف_کرو GL_UNSIGNALED_APPLE               0x9118
#تعریف_کرو GL_SIGNALED_APPLE                 0x9119
#تعریف_کرو GL_ALREADY_SIGNALED_APPLE         0x911A
#تعریف_کرو GL_TIMEOUT_EXPIRED_APPLE          0x911B
#تعریف_کرو GL_CONDITION_SATISFIED_APPLE      0x911C
#تعریف_کرو GL_WAIT_FAILED_APPLE              0x911D
#تعریف_کرو GL_SYNC_FLUSH_COMMANDS_ثنائی_ہندسہ_APPLE  0x00000001
#تعریف_کرو GL_TIMEOUT_IGNORED_APPLE          0xFFFFFFFFFFFFFFFFull
قسمتعریف GLsync (GL_APIENTRYP PFNGLFENCESYNCAPPLEPROC) (GLenum condition, GLbitfield flags);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLISSYNCAPPLEPROC) (GLsync sync);
قسمتعریف خالی (GL_APIENTRYP PFNGLDELETESYNCAPPLEPROC) (GLsync sync);
قسمتعریف GLenum (GL_APIENTRYP PFNGLCLIENTWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
قسمتعریف خالی (GL_APIENTRYP PFNGLWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETINTEGER64VAPPLEPROC) (GLenum pname, GLint64 *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETSYNCIVAPPLEPROC) (GLsync sync, GLenum pname, GLsizei گنتی, GLsizei *لمبائی, GLint *اقدار);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL GLsync GL_APIENTRY glFenceSyncAPPLE (GLenum condition, GLbitfield flags);
GL_APICALL GLboolean GL_APIENTRY glIsSyncAPPLE (GLsync sync);
GL_APICALL خالی GL_APIENTRY glDeleteSyncAPPLE (GLsync sync);
GL_APICALL GLenum GL_APIENTRY glClientWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_APICALL خالی GL_APIENTRY glWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_APICALL خالی GL_APIENTRY glGetInteger64vAPPLE (GLenum pname, GLint64 *params);
GL_APICALL خالی GL_APIENTRY glGetSyncivAPPLE (GLsync sync, GLenum pname, GLsizei گنتی, GLsizei *لمبائی, GLint *اقدار);
#اگر_ختم
#اگر_ختم /* GL_APPLE_sync */

#اگر_غیر_تعریف_شدہ GL_APPLE_texture_format_BGRA8888
#تعریف_کرو GL_APPLE_texture_format_BGRA8888 1
#تعریف_کرو GL_BGRA_EXT                       0x80E1
#تعریف_کرو GL_BGRA8_EXT                      0x93A1
#اگر_ختم /* GL_APPLE_texture_format_BGRA8888 */

#اگر_غیر_تعریف_شدہ GL_APPLE_texture_max_level
#تعریف_کرو GL_APPLE_texture_max_level 1
#تعریف_کرو GL_TEXTURE_MAX_LEVEL_APPLE        0x813D
#اگر_ختم /* GL_APPLE_texture_max_level */

#اگر_غیر_تعریف_شدہ GL_APPLE_texture_packed_float
#تعریف_کرو GL_APPLE_texture_packed_float 1
#تعریف_کرو GL_UNSIGNED_INT_10F_11F_11F_REV_APPLE 0x8C3B
#تعریف_کرو GL_UNSIGNED_INT_5_9_9_9_REV_APPLE 0x8C3E
#تعریف_کرو GL_R11F_G11F_B10F_APPLE           0x8C3A
#تعریف_کرو GL_RGB9_E5_APPLE                  0x8C3D
#اگر_ختم /* GL_APPLE_texture_packed_float */

#اگر_غیر_تعریف_شدہ GL_ARM_mali_پروگرام_ثنائی
#تعریف_کرو GL_ARM_mali_پروگرام_ثنائی 1
#تعریف_کرو GL_MALI_پروگرام_ثنائی_ARM        0x8F61
#اگر_ختم /* GL_ARM_mali_program_binary */

#اگر_غیر_تعریف_شدہ GL_ARM_mali_shader_ثنائی
#تعریف_کرو GL_ARM_mali_shader_ثنائی 1
#تعریف_کرو GL_MALI_SHADER_ثنائی_ARM         0x8F60
#اگر_ختم /* GL_ARM_mali_shader_binary */

#اگر_غیر_تعریف_شدہ GL_ARM_rgba8
#تعریف_کرو GL_ARM_rgba8 1
#اگر_ختم /* GL_ARM_rgba8 */

#اگر_غیر_تعریف_شدہ GL_ARM_shader_core_properties
#تعریف_کرو GL_ARM_shader_core_properties 1
#تعریف_کرو GL_SHADER_CORE_گنتی_ARM          0x96F0
#تعریف_کرو GL_SHADER_CORE_فعال_گنتی_ARM   0x96F1
#تعریف_کرو GL_SHADER_CORE_PRESENT_نقاب_ARM   0x96F2
#تعریف_کرو GL_SHADER_CORE_MAX_WARP_گنتی_ARM 0x96F3
#تعریف_کرو GL_SHADER_CORE_PIXEL_شرح_ARM     0x96F4
#تعریف_کرو GL_SHADER_CORE_TEXEL_شرح_ARM     0x96F5
#تعریف_کرو GL_SHADER_CORE_FMA_شرح_ARM       0x96F6
قسمتعریف خالی (GL_APIENTRYP PFNGLMAXACTIVESHADERCORESARMPROC) (GLuint گنتی);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_Max_فعال_Shader_Cores_ARM (GLuint گنتی);
#اگر_ختم
#اگر_ختم /* GL_ARM_shader_core_properties */

#اگر_غیر_تعریف_شدہ GL_ARM_shader_framebuffer_fetch
#تعریف_کرو GL_ARM_shader_framebuffer_fetch 1
#تعریف_کرو GL_FETCH_فی_SAMPLE_ARM           0x8F65
#تعریف_کرو GL_FRAGMENT_SHADER_FRAMEBUFFER_FETCH_MRT_ARM 0x8F66
#اگر_ختم /* GL_ARM_shader_framebuffer_fetch */

#اگر_غیر_تعریف_شدہ GL_ARM_shader_framebuffer_fetch_گہرائی_stencil
#تعریف_کرو GL_ARM_shader_framebuffer_fetch_گہرائی_stencil 1
#اگر_ختم /* GL_ARM_shader_framebuffer_fetch_depth_stencil */

#اگر_غیر_تعریف_شدہ GL_ARM_texture_unnormalized_coordinates
#تعریف_کرو GL_ARM_texture_unnormalized_coordinates 1
#تعریف_کرو GL_TEXTURE_UNNORMALIZED_COORDINATES_ARM 0x8F6A
#اگر_ختم /* GL_ARM_texture_unnormalized_coordinates */

#اگر_غیر_تعریف_شدہ GL_DMP_پروگرام_ثنائی
#تعریف_کرو GL_DMP_پروگرام_ثنائی 1
#تعریف_کرو GL_SMAPHS30_پروگرام_ثنائی_DMP    0x9251
#تعریف_کرو GL_SMAPHS_پروگرام_ثنائی_DMP      0x9252
#تعریف_کرو GL_DMP_پروگرام_ثنائی_DMP         0x9253
#اگر_ختم /* GL_DMP_program_binary */

#اگر_غیر_تعریف_شدہ GL_DMP_shader_ثنائی
#تعریف_کرو GL_DMP_shader_ثنائی 1
#تعریف_کرو GL_SHADER_ثنائی_DMP              0x9250
#اگر_ختم /* GL_DMP_shader_binary */

#اگر_غیر_تعریف_شدہ GL_EXT_EGL_image_array
#تعریف_کرو GL_EXT_EGL_image_array 1
#اگر_ختم /* GL_EXT_EGL_image_array */

#اگر_غیر_تعریف_شدہ GL_EXT_EGL_image_storage
#تعریف_کرو GL_EXT_EGL_image_storage 1
قسمتعریف خالی (GL_APIENTRYP PFNGLEGLIMAGETARGETTEXSTORAGEEXTPROC) (GLenum ہدف, GLeglImageOES image, ثابت GLint* attrib_list);
قسمتعریف خالی (GL_APIENTRYP PFNGLEGLIMAGETARGETTEXTURESTORAGEEXTPROC) (GLuint texture, GLeglImageOES image, ثابت GLint* attrib_list);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_EGLImage_ہدف_Tex_Storage_EXT (GLenum ہدف, GLeglImageOES image, ثابت GLint* attrib_list);
GL_APICALL خالی GL_APIENTRY gl_EGLImage_ہدف_Texture_Storage_EXT (GLuint texture, GLeglImageOES image, ثابت GLint* attrib_list);
#اگر_ختم
#اگر_ختم /* GL_EXT_EGL_image_storage */

#اگر_غیر_تعریف_شدہ GL_EXT_EGL_image_storage_compression
#تعریف_کرو GL_EXT_EGL_image_storage_compression 1
#تعریف_کرو GL_SURFACE_COMPRESSION_EXT        0x96C0
#تعریف_کرو GL_SURFACE_COMPRESSION_FIXED_شرح_NONE_EXT 0x96C1
#تعریف_کرو GL_SURFACE_COMPRESSION_FIXED_شرح_DEFAULT_EXT 0x96C2
#اگر_ختم /* GL_EXT_EGL_image_storage_compression */

#اگر_غیر_تعریف_شدہ GL_EXT_YUV_ہدف
#تعریف_کرو GL_EXT_YUV_ہدف 1
#تعریف_کرو GL_SAMPLER_EXTERNAL_2D_Y2Y_EXT    0x8BE7
#اگر_ختم /* GL_EXT_YUV_target */

#اگر_غیر_تعریف_شدہ GL_EXT_بنیاد_instance
#تعریف_کرو GL_EXT_بنیاد_instance 1
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEEXTPROC) (GLenum منوال, GLint پہلا, GLsizei گنتی, GLsizei instancecount, GLuint baseinstance);
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEEXTPROC) (GLenum منوال, GLsizei گنتی, GLenum type, ثابت خالی *indices, GLsizei instancecount, GLuint baseinstance);
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEEXTPROC) (GLenum منوال, GLsizei گنتی, GLenum type, ثابت خالی *indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_Draw_Arrays_Instanced_بنیاد_Instance_EXT (GLenum منوال, GLint پہلا, GLsizei گنتی, GLsizei instancecount, GLuint baseinstance);
GL_APICALL خالی GL_APIENTRY gl_Draw_Elements_Instanced_بنیاد_Instance_EXT (GLenum منوال, GLsizei گنتی, GLenum type, ثابت خالی *indices, GLsizei instancecount, GLuint baseinstance);
GL_APICALL خالی GL_APIENTRY gl_Draw_Elements_Instanced_بنیاد_راس_بنیاد_Instance_EXT (GLenum منوال, GLsizei گنتی, GLenum type, ثابت خالی *indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance);
#اگر_ختم
#اگر_ختم /* GL_EXT_base_instance */

#اگر_غیر_تعریف_شدہ GL_EXT_blend_func_extended
#تعریف_کرو GL_EXT_blend_func_extended 1
#تعریف_کرو GL_SRC1_COLOR_EXT                 0x88F9
#تعریف_کرو GL_SRC1_ALPHA_EXT                 0x8589
#تعریف_کرو GL_ONE_MINUS_SRC1_COLOR_EXT       0x88FA
#تعریف_کرو GL_ONE_MINUS_SRC1_ALPHA_EXT       0x88FB
#تعریف_کرو GL_SRC_ALPHA_SATURATE_EXT         0x0308
#تعریف_کرو GL_LOCATION_اشاریہ_EXT             0x930F
#تعریف_کرو GL_MAX_DUAL_ماخذ_DRAW_BUFFERS_EXT 0x88FC
قسمتعریف خالی (GL_APIENTRYP PFNGLBINDFRAGDATALOCATIONINDEXEDEXTPROC) (GLuint پروگرام, GLuint color_نمبر, GLuint اشاریہ, ثابت GLchar *name);
قسمتعریف خالی (GL_APIENTRYP PFNGLBINDFRAGDATALOCATIONEXTPROC) (GLuint پروگرام, GLuint color, ثابت GLchar *name);
قسمتعریف GLint (GL_APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONINDEXEXTPROC) (GLuint پروگرام, GLenum پروگرام_Interface, ثابت GLchar *name);
قسمتعریف GLint (GL_APIENTRYP PFNGLGETFRAGDATAINDEXEXTPROC) (GLuint پروگرام, ثابت GLchar *name);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_Bind_Frag_ڈیٹا_Location_اشاریہ_دار_EXT (GLuint پروگرام, GLuint color_نمبر, GLuint اشاریہ, ثابت GLchar *name);
GL_APICALL خالی GL_APIENTRY gl_Bind_Frag_ڈیٹا_Location_EXT (GLuint پروگرام, GLuint color, ثابت GLchar *name);
GL_APICALL GLint GL_APIENTRY gl_Get_پروگرام_Resource_Location_اشاریہ_EXT (GLuint پروگرام, GLenum پروگرام_Interface, ثابت GLchar *name);
GL_APICALL GLint GL_APIENTRY gl_Get_Frag_ڈیٹا_اشاریہ_EXT (GLuint پروگرام, ثابت GLchar *name);
#اگر_ختم
#اگر_ختم /* GL_EXT_blend_func_extended */

#اگر_غیر_تعریف_شدہ GL_EXT_blend_minmax
#تعریف_کرو GL_EXT_blend_minmax 1
#تعریف_کرو GL_MIN_EXT                        0x8007
#تعریف_کرو GL_MAX_EXT                        0x8008
#اگر_ختم /* GL_EXT_blend_minmax */

#اگر_غیر_تعریف_شدہ GL_EXT_بفر_storage
#تعریف_کرو GL_EXT_بفر_storage 1
#تعریف_کرو GL_MAP_READ_ثنائی_ہندسہ                   0x0001
#تعریف_کرو GL_MAP_WRITE_ثنائی_ہندسہ                  0x0002
#تعریف_کرو GL_MAP_PERSISTENT_ثنائی_ہندسہ_EXT         0x0040
#تعریف_کرو GL_MAP_COHERENT_ثنائی_ہندسہ_EXT           0x0080
#تعریف_کرو GL_DYNAMIC_STORAGE_ثنائی_ہندسہ_EXT        0x0100
#تعریف_کرو GL_CLIENT_STORAGE_ثنائی_ہندسہ_EXT         0x0200
#تعریف_کرو GL_CLIENT_MAPPED_بفر_BARRIER_ثنائی_ہندسہ_EXT 0x00004000
#تعریف_کرو GL_بفر_IMMUTABLE_STORAGE_EXT   0x821F
#تعریف_کرو GL_بفر_STORAGE_FLAGS_EXT       0x8220
قسمتعریف خالی (GL_APIENTRYP PFNGLBUFFERSTORAGEEXTPROC) (GLenum ہدف, GLsizeiptr سائز, ثابت خالی *ڈیٹا, GLbitfield flags);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_بفر_Storage_EXT (GLenum ہدف, GLsizeiptr سائز, ثابت خالی *ڈیٹا, GLbitfield flags);
#اگر_ختم
#اگر_ختم /* GL_EXT_buffer_storage */

#اگر_غیر_تعریف_شدہ GL_EXT_clear_texture
#تعریف_کرو GL_EXT_clear_texture 1
قسمتعریف خالی (GL_APIENTRYP PFNGLCLEARTEXIMAGEEXTPROC) (GLuint texture, GLint level, GLenum format, GLenum type, ثابت خالی *ڈیٹا);
قسمتعریف خالی (GL_APIENTRYP PFNGLCLEARTEXSUBIMAGEEXTPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLenum format, GLenum type, ثابت خالی *ڈیٹا);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glClearTexImageEXT (GLuint texture, GLint level, GLenum format, GLenum type, ثابت خالی *ڈیٹا);
GL_APICALL خالی GL_APIENTRY glClearTexSubImageEXT (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLenum format, GLenum type, ثابت خالی *ڈیٹا);
#اگر_ختم
#اگر_ختم /* GL_EXT_clear_texture */

#اگر_غیر_تعریف_شدہ GL_EXT_clip_control
#تعریف_کرو GL_EXT_clip_control 1
#تعریف_کرو GL_زیریں_بایاں_EXT                 0x8CA1
#تعریف_کرو GL_بالائی_بایاں_EXT                 0x8CA2
#تعریف_کرو GL_NEGATIVE_ONE_مقصد_ONE_EXT        0x935E
#تعریف_کرو GL_ZERO_مقصد_ONE_EXT                0x935F
#تعریف_کرو GL_CLIP_ORIGIN_EXT                0x935C
#تعریف_کرو GL_CLIP_گہرائی_منوال_EXT            0x935D
قسمتعریف خالی (GL_APIENTRYP PFNGLCLIPCONTROLEXTPROC) (GLenum origin, GLenum گہرائی_2);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glClipControlEXT (GLenum origin, GLenum گہرائی_2);
#اگر_ختم
#اگر_ختم /* GL_EXT_clip_control */

#اگر_غیر_تعریف_شدہ GL_EXT_clip_cull_فاصلہ
#تعریف_کرو GL_EXT_clip_cull_فاصلہ 1
#تعریف_کرو GL_MAX_CLIP_DISTANCES_EXT         0x0D32
#تعریف_کرو GL_MAX_CULL_DISTANCES_EXT         0x82F9
#تعریف_کرو GL_MAX_COMBINED_CLIP_AND_CULL_DISTANCES_EXT 0x82FA
#تعریف_کرو GL_CLIP_DISTANCE0_EXT             0x3000
#تعریف_کرو GL_CLIP_DISTANCE1_EXT             0x3001
#تعریف_کرو GL_CLIP_DISTANCE2_EXT             0x3002
#تعریف_کرو GL_CLIP_DISTANCE3_EXT             0x3003
#تعریف_کرو GL_CLIP_DISTANCE4_EXT             0x3004
#تعریف_کرو GL_CLIP_DISTANCE5_EXT             0x3005
#تعریف_کرو GL_CLIP_DISTANCE6_EXT             0x3006
#تعریف_کرو GL_CLIP_DISTANCE7_EXT             0x3007
#اگر_ختم /* GL_EXT_clip_cull_distance */

#اگر_غیر_تعریف_شدہ GL_EXT_color_بفر_float
#تعریف_کرو GL_EXT_color_بفر_float 1
#اگر_ختم /* GL_EXT_color_buffer_float */

#اگر_غیر_تعریف_شدہ GL_EXT_color_بفر_half_float
#تعریف_کرو GL_EXT_color_بفر_half_float 1
#تعریف_کرو GL_RGBA16F_EXT                    0x881A
#تعریف_کرو GL_RGB16F_EXT                     0x881B
#تعریف_کرو GL_RG16F_EXT                      0x822F
#تعریف_کرو GL_R16F_EXT                       0x822D
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE_EXT 0x8211
#تعریف_کرو GL_UNSIGNED_NORMALIZED_EXT        0x8C17
#اگر_ختم /* GL_EXT_color_buffer_half_float */

#اگر_غیر_تعریف_شدہ GL_EXT_conservative_گہرائی
#تعریف_کرو GL_EXT_conservative_گہرائی 1
#اگر_ختم /* GL_EXT_conservative_depth */

#اگر_غیر_تعریف_شدہ GL_EXT_copy_image
#تعریف_کرو GL_EXT_copy_image 1
قسمتعریف خالی (GL_APIENTRYP PFNGLCOPYIMAGESUBDATAEXTPROC) (GLuint srcName, GLenum src_ہدف, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dst_ہدف, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei src_چوڑائی, GLsizei src_اونچائی, GLsizei src_گہرائی);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_Copy_Image_Sub_ڈیٹا_EXT (GLuint srcName, GLenum src_ہدف, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dst_ہدف, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei src_چوڑائی, GLsizei src_اونچائی, GLsizei src_گہرائی);
#اگر_ختم
#اگر_ختم /* GL_EXT_copy_image */

#اگر_غیر_تعریف_شدہ GL_EXT_debug_label
#تعریف_کرو GL_EXT_debug_label 1
#تعریف_کرو GL_پروگرام_PIPELINE_OBJECT_EXT    0x8A4F
#تعریف_کرو GL_پروگرام_OBJECT_EXT             0x8B40
#تعریف_کرو GL_SHADER_OBJECT_EXT              0x8B48
#تعریف_کرو GL_بفر_OBJECT_EXT              0x9151
#تعریف_کرو GL_QUERY_OBJECT_EXT               0x9153
#تعریف_کرو GL_راس_ARRAY_OBJECT_EXT        0x9154
#تعریف_کرو GL_TRANSFORM_FEEDBACK             0x8E22
قسمتعریف خالی (GL_APIENTRYP PFNGLLABELOBJECTEXTPROC) (GLenum type, GLuint object, GLsizei لمبائی, ثابت GLchar *label);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETOBJECTLABELEXTPROC) (GLenum type, GLuint object, GLsizei buf_سائز, GLsizei *لمبائی, GLchar *label);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glLabelObjectEXT (GLenum type, GLuint object, GLsizei لمبائی, ثابت GLchar *label);
GL_APICALL خالی GL_APIENTRY glGetObjectLabelEXT (GLenum type, GLuint object, GLsizei buf_سائز, GLsizei *لمبائی, GLchar *label);
#اگر_ختم
#اگر_ختم /* GL_EXT_debug_label */

#اگر_غیر_تعریف_شدہ GL_EXT_debug_marker
#تعریف_کرو GL_EXT_debug_marker 1
قسمتعریف خالی (GL_APIENTRYP PFNGLINSERTEVENTMARKEREXTPROC) (GLsizei لمبائی, ثابت GLchar *marker);
قسمتعریف خالی (GL_APIENTRYP PFNGLPUSHGROUPMARKEREXTPROC) (GLsizei لمبائی, ثابت GLchar *marker);
قسمتعریف خالی (GL_APIENTRYP PFNGLPOPGROUPMARKEREXTPROC) (خالی);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_داخل_کرو_Event_Marker_EXT (GLsizei لمبائی, ثابت GLchar *marker);
GL_APICALL خالی GL_APIENTRY gl_ڈالو_گروہ_Marker_EXT (GLsizei لمبائی, ثابت GLchar *marker);
GL_APICALL خالی GL_APIENTRY gl_نکالو_گروہ_Marker_EXT (خالی);
#اگر_ختم
#اگر_ختم /* GL_EXT_debug_marker */

#اگر_غیر_تعریف_شدہ GL_EXT_گہرائی_clamp
#تعریف_کرو GL_EXT_گہرائی_clamp 1
#تعریف_کرو GL_گہرائی_CLAMP_EXT                0x864F
#اگر_ختم /* GL_EXT_depth_clamp */

#اگر_غیر_تعریف_شدہ GL_EXT_discard_framebuffer
#تعریف_کرو GL_EXT_discard_framebuffer 1
#تعریف_کرو GL_COLOR_EXT                      0x1800
#تعریف_کرو GL_گہرائی_EXT                      0x1801
#تعریف_کرو GL_STENCIL_EXT                    0x1802
قسمتعریف خالی (GL_APIENTRYP PFNGLDISCARDFRAMEBUFFEREXTPROC) (GLenum ہدف, GLsizei عدد_Attachments, ثابت GLenum *attachments);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glDiscardFramebufferEXT (GLenum ہدف, GLsizei عدد_Attachments, ثابت GLenum *attachments);
#اگر_ختم
#اگر_ختم /* GL_EXT_discard_framebuffer */

#اگر_غیر_تعریف_شدہ GL_EXT_disjoint_timer_query
#تعریف_کرو GL_EXT_disjoint_timer_query 1
#تعریف_کرو GL_QUERY_شمار_بٹ_EXT         0x8864
#تعریف_کرو GL_CURRENT_QUERY_EXT              0x8865
#تعریف_کرو GL_QUERY_نتیجہ_EXT               0x8866
#تعریف_کرو GL_QUERY_نتیجہ_دستیاب_EXT     0x8867
#تعریف_کرو GL_وقت_ELAPSED_EXT               0x88BF
#تعریف_کرو GL_TIMESTAMP_EXT                  0x8E28
#تعریف_کرو GL_GPU_DISJOINT_EXT               0x8FBB
قسمتعریف خالی (GL_APIENTRYP PFNGLGENQUERIESEXTPROC) (GLsizei n, GLuint *ids);
قسمتعریف خالی (GL_APIENTRYP PFNGLDELETEQUERIESEXTPROC) (GLsizei n, ثابت GLuint *ids);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLISQUERYEXTPROC) (GLuint id);
قسمتعریف خالی (GL_APIENTRYP PFNGLBEGINQUERYEXTPROC) (GLenum ہدف, GLuint id);
قسمتعریف خالی (GL_APIENTRYP PFNGLENDQUERYEXTPROC) (GLenum ہدف);
قسمتعریف خالی (GL_APIENTRYP PFNGLQUERYCOUNTEREXTPROC) (GLuint id, GLenum ہدف);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETQUERYIVEXTPROC) (GLenum ہدف, GLenum pname, GLint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETQUERYOBJECTIVEXTPROC) (GLuint id, GLenum pname, GLint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETQUERYOBJECTUIVEXTPROC) (GLuint id, GLenum pname, GLuint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETQUERYOBJECTI64VEXTPROC) (GLuint id, GLenum pname, GLint64 *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETQUERYOBJECTUI64VEXTPROC) (GLuint id, GLenum pname, GLuint64 *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETINTEGER64VEXTPROC) (GLenum pname, GLint64 *ڈیٹا);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glGenQueriesEXT (GLsizei n, GLuint *ids);
GL_APICALL خالی GL_APIENTRY glDeleteQueriesEXT (GLsizei n, ثابت GLuint *ids);
GL_APICALL GLboolean GL_APIENTRY glIsQueryEXT (GLuint id);
GL_APICALL خالی GL_APIENTRY glBeginQueryEXT (GLenum ہدف, GLuint id);
GL_APICALL خالی GL_APIENTRY gl_انتہا_Query_EXT (GLenum ہدف);
GL_APICALL خالی GL_APIENTRY gl_Query_شمار_EXT (GLuint id, GLenum ہدف);
GL_APICALL خالی GL_APIENTRY glGetQueryivEXT (GLenum ہدف, GLenum pname, GLint *params);
GL_APICALL خالی GL_APIENTRY glGetQueryObjectivEXT (GLuint id, GLenum pname, GLint *params);
GL_APICALL خالی GL_APIENTRY glGetQueryObjectuivEXT (GLuint id, GLenum pname, GLuint *params);
GL_APICALL خالی GL_APIENTRY glGetQueryObjecti64vEXT (GLuint id, GLenum pname, GLint64 *params);
GL_APICALL خالی GL_APIENTRY glGetQueryObjectui64vEXT (GLuint id, GLenum pname, GLuint64 *params);
GL_APICALL خالی GL_APIENTRY glGetInteger64vEXT (GLenum pname, GLint64 *ڈیٹا);
#اگر_ختم
#اگر_ختم /* GL_EXT_disjoint_timer_query */

#اگر_غیر_تعریف_شدہ GL_EXT_draw_buffers
#تعریف_کرو GL_EXT_draw_buffers 1
#تعریف_کرو GL_MAX_COLOR_ATTACHMENTS_EXT      0x8CDF
#تعریف_کرو GL_MAX_DRAW_BUFFERS_EXT           0x8824
#تعریف_کرو GL_DRAW_BUFFER0_EXT               0x8825
#تعریف_کرو GL_DRAW_BUFFER1_EXT               0x8826
#تعریف_کرو GL_DRAW_BUFFER2_EXT               0x8827
#تعریف_کرو GL_DRAW_BUFFER3_EXT               0x8828
#تعریف_کرو GL_DRAW_BUFFER4_EXT               0x8829
#تعریف_کرو GL_DRAW_BUFFER5_EXT               0x882A
#تعریف_کرو GL_DRAW_BUFFER6_EXT               0x882B
#تعریف_کرو GL_DRAW_BUFFER7_EXT               0x882C
#تعریف_کرو GL_DRAW_BUFFER8_EXT               0x882D
#تعریف_کرو GL_DRAW_BUFFER9_EXT               0x882E
#تعریف_کرو GL_DRAW_BUFFER10_EXT              0x882F
#تعریف_کرو GL_DRAW_BUFFER11_EXT              0x8830
#تعریف_کرو GL_DRAW_BUFFER12_EXT              0x8831
#تعریف_کرو GL_DRAW_BUFFER13_EXT              0x8832
#تعریف_کرو GL_DRAW_BUFFER14_EXT              0x8833
#تعریف_کرو GL_DRAW_BUFFER15_EXT              0x8834
#تعریف_کرو GL_COLOR_ATTACHMENT0_EXT          0x8CE0
#تعریف_کرو GL_COLOR_ATTACHMENT1_EXT          0x8CE1
#تعریف_کرو GL_COLOR_ATTACHMENT2_EXT          0x8CE2
#تعریف_کرو GL_COLOR_ATTACHMENT3_EXT          0x8CE3
#تعریف_کرو GL_COLOR_ATTACHMENT4_EXT          0x8CE4
#تعریف_کرو GL_COLOR_ATTACHMENT5_EXT          0x8CE5
#تعریف_کرو GL_COLOR_ATTACHMENT6_EXT          0x8CE6
#تعریف_کرو GL_COLOR_ATTACHMENT7_EXT          0x8CE7
#تعریف_کرو GL_COLOR_ATTACHMENT8_EXT          0x8CE8
#تعریف_کرو GL_COLOR_ATTACHMENT9_EXT          0x8CE9
#تعریف_کرو GL_COLOR_ATTACHMENT10_EXT         0x8CEA
#تعریف_کرو GL_COLOR_ATTACHMENT11_EXT         0x8CEB
#تعریف_کرو GL_COLOR_ATTACHMENT12_EXT         0x8CEC
#تعریف_کرو GL_COLOR_ATTACHMENT13_EXT         0x8CED
#تعریف_کرو GL_COLOR_ATTACHMENT14_EXT         0x8CEE
#تعریف_کرو GL_COLOR_ATTACHMENT15_EXT         0x8CEF
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWBUFFERSEXTPROC) (GLsizei n, ثابت GLenum *bufs);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glDrawBuffersEXT (GLsizei n, ثابت GLenum *bufs);
#اگر_ختم
#اگر_ختم /* GL_EXT_draw_buffers */

#اگر_غیر_تعریف_شدہ GL_EXT_draw_buffers_اشاریہ_دار
#تعریف_کرو GL_EXT_draw_buffers_اشاریہ_دار 1
قسمتعریف خالی (GL_APIENTRYP PFNGLENABLEIEXTPROC) (GLenum ہدف, GLuint اشاریہ);
قسمتعریف خالی (GL_APIENTRYP PFNGLDISABLEIEXTPROC) (GLenum ہدف, GLuint اشاریہ);
قسمتعریف خالی (GL_APIENTRYP PFNGLBLENDEQUATIONIEXTPROC) (GLuint buf, GLenum منوال);
قسمتعریف خالی (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEIEXTPROC) (GLuint buf, GLenum منوال_RGB, GLenum منوال_Alpha);
قسمتعریف خالی (GL_APIENTRYP PFNGLBLENDFUNCIEXTPROC) (GLuint buf, GLenum src, GLenum dst);
قسمتعریف خالی (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEIEXTPROC) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
قسمتعریف خالی (GL_APIENTRYP PFNGLCOLORMASKIEXTPROC) (GLuint اشاریہ, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLISENABLEDIEXTPROC) (GLenum ہدف, GLuint اشاریہ);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glEnableiEXT (GLenum ہدف, GLuint اشاریہ);
GL_APICALL خالی GL_APIENTRY glDisableiEXT (GLenum ہدف, GLuint اشاریہ);
GL_APICALL خالی GL_APIENTRY glBlendEquationiEXT (GLuint buf, GLenum منوال);
GL_APICALL خالی GL_APIENTRY glBlendEquationSeparateiEXT (GLuint buf, GLenum منوال_RGB, GLenum منوال_Alpha);
GL_APICALL خالی GL_APIENTRY glBlendFunciEXT (GLuint buf, GLenum src, GLenum dst);
GL_APICALL خالی GL_APIENTRY glBlendFuncSeparateiEXT (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
GL_APICALL خالی GL_APIENTRY glColorMaskiEXT (GLuint اشاریہ, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
GL_APICALL GLboolean GL_APIENTRY glIsEnablediEXT (GLenum ہدف, GLuint اشاریہ);
#اگر_ختم
#اگر_ختم /* GL_EXT_draw_buffers_indexed */

#اگر_غیر_تعریف_شدہ GL_EXT_draw_elements_بنیاد_راس
#تعریف_کرو GL_EXT_draw_elements_بنیاد_راس 1
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWELEMENTSBASEVERTEXEXTPROC) (GLenum منوال, GLsizei گنتی, GLenum type, ثابت خالی *indices, GLint basevertex);
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWRANGEELEMENTSBASEVERTEXEXTPROC) (GLenum منوال, GLuint آغاز, GLuint انتہا, GLsizei گنتی, GLenum type, ثابت خالی *indices, GLint basevertex);
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXEXTPROC) (GLenum منوال, GLsizei گنتی, GLenum type, ثابت خالی *indices, GLsizei instancecount, GLint basevertex);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_Draw_Elements_بنیاد_راس_EXT (GLenum منوال, GLsizei گنتی, GLenum type, ثابت خالی *indices, GLint basevertex);
GL_APICALL خالی GL_APIENTRY gl_Draw_Range_Elements_بنیاد_راس_EXT (GLenum منوال, GLuint آغاز, GLuint انتہا, GLsizei گنتی, GLenum type, ثابت خالی *indices, GLint basevertex);
GL_APICALL خالی GL_APIENTRY gl_Draw_Elements_Instanced_بنیاد_راس_EXT (GLenum منوال, GLsizei گنتی, GLenum type, ثابت خالی *indices, GLsizei instancecount, GLint basevertex);
#اگر_ختم
#اگر_ختم /* GL_EXT_draw_elements_base_vertex */

#اگر_غیر_تعریف_شدہ GL_EXT_draw_instanced
#تعریف_کرو GL_EXT_draw_instanced 1
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDEXTPROC) (GLenum منوال, GLint آغاز, GLsizei گنتی, GLsizei primcount);
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDEXTPROC) (GLenum منوال, GLsizei گنتی, GLenum type, ثابت خالی *indices, GLsizei primcount);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glDrawArraysInstancedEXT (GLenum منوال, GLint آغاز, GLsizei گنتی, GLsizei primcount);
GL_APICALL خالی GL_APIENTRY glDrawElementsInstancedEXT (GLenum منوال, GLsizei گنتی, GLenum type, ثابت خالی *indices, GLsizei primcount);
#اگر_ختم
#اگر_ختم /* GL_EXT_draw_instanced */

#اگر_غیر_تعریف_شدہ GL_EXT_draw_transform_feedback
#تعریف_کرو GL_EXT_draw_transform_feedback 1
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKEXTPROC) (GLenum منوال, GLuint id);
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDEXTPROC) (GLenum منوال, GLuint id, GLsizei instancecount);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glDrawTransformFeedbackEXT (GLenum منوال, GLuint id);
GL_APICALL خالی GL_APIENTRY glDrawTransformFeedbackInstancedEXT (GLenum منوال, GLuint id, GLsizei instancecount);
#اگر_ختم
#اگر_ختم /* GL_EXT_draw_transform_feedback */

#اگر_غیر_تعریف_شدہ GL_EXT_external_بفر
#تعریف_کرو GL_EXT_external_بفر 1
قسمتعریف خالی *GLegl_Client_بفر_EXT;
قسمتعریف خالی (GL_APIENTRYP PFNGLBUFFERSTORAGEEXTERNALEXTPROC) (GLenum ہدف, GLintptr انحراف_2, GLsizeiptr سائز, GLegl_Client_بفر_EXT client_بفر, GLbitfield flags);
قسمتعریف خالی (GL_APIENTRYP PFNGLNAMEDBUFFERSTORAGEEXTERNALEXTPROC) (GLuint بفر_2, GLintptr انحراف_2, GLsizeiptr سائز, GLegl_Client_بفر_EXT client_بفر, GLbitfield flags);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_بفر_Storage_External_EXT (GLenum ہدف, GLintptr انحراف_2, GLsizeiptr سائز, GLegl_Client_بفر_EXT client_بفر, GLbitfield flags);
GL_APICALL خالی GL_APIENTRY gl_Named_بفر_Storage_External_EXT (GLuint بفر_2, GLintptr انحراف_2, GLsizeiptr سائز, GLegl_Client_بفر_EXT client_بفر, GLbitfield flags);
#اگر_ختم
#اگر_ختم /* GL_EXT_external_buffer */

#اگر_غیر_تعریف_شدہ GL_EXT_float_blend
#تعریف_کرو GL_EXT_float_blend 1
#اگر_ختم /* GL_EXT_float_blend */

#اگر_غیر_تعریف_شدہ GL_EXT_fragment_shading_شرح
#تعریف_کرو GL_EXT_fragment_shading_شرح 1
#تعریف_کرو GL_SHADING_شرح_1_X1_PIXELS_EXT    0x96A6
#تعریف_کرو GL_SHADING_شرح_1_X2_PIXELS_EXT    0x96A7
#تعریف_کرو GL_SHADING_شرح_2_X1_PIXELS_EXT    0x96A8
#تعریف_کرو GL_SHADING_شرح_2_X2_PIXELS_EXT    0x96A9
#تعریف_کرو GL_SHADING_شرح_1_X4_PIXELS_EXT    0x96AA
#تعریف_کرو GL_SHADING_شرح_4_X1_PIXELS_EXT    0x96AB
#تعریف_کرو GL_SHADING_شرح_4_X2_PIXELS_EXT    0x96AC
#تعریف_کرو GL_SHADING_شرح_2_X4_PIXELS_EXT    0x96AD
#تعریف_کرو GL_SHADING_شرح_4_X4_PIXELS_EXT    0x96AE
#تعریف_کرو GL_SHADING_شرح_EXT               0x96D0
#تعریف_کرو GL_SHADING_شرح_ATTACHMENT_EXT    0x96D1
#تعریف_کرو GL_FRAGMENT_SHADING_شرح_COMBINER_OP_KEEP_EXT 0x96D2
#تعریف_کرو GL_FRAGMENT_SHADING_شرح_COMBINER_OP_REPLACE_EXT 0x96D3
#تعریف_کرو GL_FRAGMENT_SHADING_شرح_COMBINER_OP_MIN_EXT 0x96D4
#تعریف_کرو GL_FRAGMENT_SHADING_شرح_COMBINER_OP_MAX_EXT 0x96D5
#تعریف_کرو GL_FRAGMENT_SHADING_شرح_COMBINER_OP_MUL_EXT 0x96D6
#تعریف_کرو GL_MIN_FRAGMENT_SHADING_شرح_ATTACHMENT_TEXEL_چوڑائی_EXT 0x96D7
#تعریف_کرو GL_MAX_FRAGMENT_SHADING_شرح_ATTACHMENT_TEXEL_چوڑائی_EXT 0x96D8
#تعریف_کرو GL_MIN_FRAGMENT_SHADING_شرح_ATTACHMENT_TEXEL_اونچائی_EXT 0x96D9
#تعریف_کرو GL_MAX_FRAGMENT_SHADING_شرح_ATTACHMENT_TEXEL_اونچائی_EXT 0x96DA
#تعریف_کرو GL_MAX_FRAGMENT_SHADING_شرح_ATTACHMENT_TEXEL_ASPECT_تناسب_EXT 0x96DB
#تعریف_کرو GL_MAX_FRAGMENT_SHADING_شرح_ATTACHMENT_LAYERS_EXT 0x96DC
#تعریف_کرو GL_FRAGMENT_SHADING_شرح_WITH_SHADER_گہرائی_STENCIL_WRITES_SUPPORTED_EXT 0x96DD
#تعریف_کرو GL_FRAGMENT_SHADING_شرح_WITH_SAMPLE_نقاب_SUPPORTED_EXT 0x96DE
#تعریف_کرو GL_FRAGMENT_SHADING_شرح_ATTACHMENT_WITH_DEFAULT_FRAMEBUFFER_SUPPORTED_EXT 0x96DF
#تعریف_کرو GL_FRAGMENT_SHADING_شرح_NON_TRIVIAL_COMBINERS_SUPPORTED_EXT 0x8F6F
قسمتعریف خالی (GL_APIENTRYP PFNGLGETFRAGMENTSHADINGRATESEXTPROC) (GLsizei samples, GLsizei max_گنتی, GLsizei *گنتی, GLenum *shadingRates);
قسمتعریف خالی (GL_APIENTRYP PFNGLSHADINGRATEEXTPROC) (GLenum شرح);
قسمتعریف خالی (GL_APIENTRYP PFNGLSHADINGRATECOMBINEROPSEXTPROC) (GLenum combinerOp0, GLenum combinerOp1);
قسمتعریف خالی (GL_APIENTRYP PFNGLFRAMEBUFFERSHADINGRATEEXTPROC) (GLenum ہدف, GLenum attachment, GLuint texture, GLint بنیاد_Layer, GLsizei عدد_Layers, GLsizei texel_چوڑائی, GLsizei texel_اونچائی);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glGetFragmentShadingRatesEXT (GLsizei samples, GLsizei max_گنتی, GLsizei *گنتی, GLenum *shadingRates);
GL_APICALL خالی GL_APIENTRY gl_Shading_شرح_EXT (GLenum شرح);
GL_APICALL خالی GL_APIENTRY gl_Shading_شرح_Combiner_Ops_EXT (GLenum combinerOp0, GLenum combinerOp1);
GL_APICALL خالی GL_APIENTRY gl_Framebuffer_Shading_شرح_EXT (GLenum ہدف, GLenum attachment, GLuint texture, GLint بنیاد_Layer, GLsizei عدد_Layers, GLsizei texel_چوڑائی, GLsizei texel_اونچائی);
#اگر_ختم
#اگر_ختم /* GL_EXT_fragment_shading_rate */

#اگر_غیر_تعریف_شدہ GL_EXT_framebuffer_blit_layers
#تعریف_کرو GL_EXT_framebuffer_blit_layers 1
قسمتعریف خالی (GL_APIENTRYP PFNGLBLITFRAMEBUFFERLAYERSEXTPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield نقاب, GLenum filter);
قسمتعریف خالی (GL_APIENTRYP PFNGLBLITFRAMEBUFFERLAYEREXTPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint srcLayer, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLint dstLayer, GLbitfield نقاب, GLenum filter);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glBlitFramebufferLayersEXT (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield نقاب, GLenum filter);
GL_APICALL خالی GL_APIENTRY glBlitFramebufferLayerEXT (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint srcLayer, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLint dstLayer, GLbitfield نقاب, GLenum filter);
#اگر_ختم
#اگر_ختم /* GL_EXT_framebuffer_blit_layers */

#اگر_غیر_تعریف_شدہ GL_EXT_geometry_نقطہ_سائز
#تعریف_کرو GL_EXT_geometry_نقطہ_سائز 1
#اگر_ختم /* GL_EXT_geometry_point_size */

#اگر_غیر_تعریف_شدہ GL_EXT_geometry_shader
#تعریف_کرو GL_EXT_geometry_shader 1
#تعریف_کرو GL_GEOMETRY_SHADER_EXT            0x8DD9
#تعریف_کرو GL_GEOMETRY_SHADER_ثنائی_ہندسہ_EXT        0x00000004
#تعریف_کرو GL_GEOMETRY_LINKED_VERTICES_برآمد_EXT 0x8916
#تعریف_کرو GL_GEOMETRY_LINKED_داخلہ_TYPE_EXT 0x8917
#تعریف_کرو GL_GEOMETRY_LINKED_OUTPUT_TYPE_EXT 0x8918
#تعریف_کرو GL_GEOMETRY_SHADER_INVOCATIONS_EXT 0x887F
#تعریف_کرو GL_LAYER_PROVOKING_راس_EXT     0x825E
#تعریف_کرو GL_سطریں_ADJACENCY_EXT            0x000A
#تعریف_کرو GL_سطر_STRIP_ADJACENCY_EXT       0x000B
#تعریف_کرو GL_TRIANGLES_ADJACENCY_EXT        0x000C
#تعریف_کرو GL_TRIANGLE_STRIP_ADJACENCY_EXT   0x000D
#تعریف_کرو GL_MAX_GEOMETRY_یکساں_COMPONENTS_EXT 0x8DDF
#تعریف_کرو GL_MAX_GEOMETRY_یکساں_بلاکیں_EXT 0x8A2C
#تعریف_کرو GL_MAX_COMBINED_GEOMETRY_یکساں_COMPONENTS_EXT 0x8A32
#تعریف_کرو GL_MAX_GEOMETRY_داخلہ_COMPONENTS_EXT 0x9123
#تعریف_کرو GL_MAX_GEOMETRY_OUTPUT_COMPONENTS_EXT 0x9124
#تعریف_کرو GL_MAX_GEOMETRY_OUTPUT_VERTICES_EXT 0x8DE0
#تعریف_کرو GL_MAX_GEOMETRY_کل_OUTPUT_COMPONENTS_EXT 0x8DE1
#تعریف_کرو GL_MAX_GEOMETRY_SHADER_INVOCATIONS_EXT 0x8E5A
#تعریف_کرو GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_EXT 0x8C29
#تعریف_کرو GL_MAX_GEOMETRY_ATOMIC_شمار_BUFFERS_EXT 0x92CF
#تعریف_کرو GL_MAX_GEOMETRY_ATOMIC_COUNTERS_EXT 0x92D5
#تعریف_کرو GL_MAX_GEOMETRY_IMAGE_UNIFORMS_EXT 0x90CD
#تعریف_کرو GL_MAX_GEOMETRY_SHADER_STORAGE_بلاکیں_EXT 0x90D7
#تعریف_کرو GL_پہلا_راس_CONVENTION_EXT    0x8E4D
#تعریف_کرو GL_آخری_راس_CONVENTION_EXT     0x8E4E
#تعریف_کرو GL_UNDEFINED_راس_EXT           0x8260
#تعریف_کرو GL_PRIMITIVES_GENERATED_EXT       0x8C87
#تعریف_کرو GL_FRAMEBUFFER_DEFAULT_LAYERS_EXT 0x9312
#تعریف_کرو GL_MAX_FRAMEBUFFER_LAYERS_EXT     0x9317
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_EXT 0x8DA8
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_LAYERED_EXT 0x8DA7
#تعریف_کرو GL_REFERENCED_BY_GEOMETRY_SHADER_EXT 0x9309
قسمتعریف خالی (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREEXTPROC) (GLenum ہدف, GLenum attachment, GLuint texture, GLint level);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glFramebufferTextureEXT (GLenum ہدف, GLenum attachment, GLuint texture, GLint level);
#اگر_ختم
#اگر_ختم /* GL_EXT_geometry_shader */

#اگر_غیر_تعریف_شدہ GL_EXT_gpu_shader5
#تعریف_کرو GL_EXT_gpu_shader5 1
#اگر_ختم /* GL_EXT_gpu_shader5 */

#اگر_غیر_تعریف_شدہ GL_EXT_instanced_arrays
#تعریف_کرو GL_EXT_instanced_arrays 1
#تعریف_کرو GL_راس_ATTRIB_ARRAY_مقسوم_علیہ_EXT 0x88FE
قسمتعریف خالی (GL_APIENTRYP PFNGLVERTEXATTRIBDIVISOREXTPROC) (GLuint اشاریہ, GLuint مقسوم_علیہ);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_راس_Attrib_مقسوم_علیہ_EXT (GLuint اشاریہ, GLuint مقسوم_علیہ);
#اگر_ختم
#اگر_ختم /* GL_EXT_instanced_arrays */

#اگر_غیر_تعریف_شدہ GL_EXT_map_بفر_range
#تعریف_کرو GL_EXT_map_بفر_range 1
#تعریف_کرو GL_MAP_READ_ثنائی_ہندسہ_EXT               0x0001
#تعریف_کرو GL_MAP_WRITE_ثنائی_ہندسہ_EXT              0x0002
#تعریف_کرو GL_MAP_INVALIDATE_RANGE_ثنائی_ہندسہ_EXT   0x0004
#تعریف_کرو GL_MAP_INVALIDATE_بفر_ثنائی_ہندسہ_EXT  0x0008
#تعریف_کرو GL_MAP_FLUSH_EXPLICIT_ثنائی_ہندسہ_EXT     0x0010
#تعریف_کرو GL_MAP_UNSYNCHRONIZED_ثنائی_ہندسہ_EXT     0x0020
قسمتعریف خالی *(GL_APIENTRYP PFNGLMAPBUFFERRANGEEXTPROC) (GLenum ہدف, GLintptr انحراف_2, GLsizeiptr لمبائی, GLbitfield access);
قسمتعریف خالی (GL_APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEEXTPROC) (GLenum ہدف, GLintptr انحراف_2, GLsizeiptr لمبائی);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی *GL_APIENTRY gl_Map_بفر_Range_EXT (GLenum ہدف, GLintptr انحراف_2, GLsizeiptr لمبائی, GLbitfield access);
GL_APICALL خالی GL_APIENTRY gl_Flush_Mapped_بفر_Range_EXT (GLenum ہدف, GLintptr انحراف_2, GLsizeiptr لمبائی);
#اگر_ختم
#اگر_ختم /* GL_EXT_map_buffer_range */

#اگر_غیر_تعریف_شدہ GL_EXT_حافظہ_object
#تعریف_کرو GL_EXT_حافظہ_object 1
#تعریف_کرو GL_TEXTURE_TILING_EXT             0x9580
#تعریف_کرو GL_DEDICATED_حافظہ_OBJECT_EXT    0x9581
#تعریف_کرو GL_PROTECTED_حافظہ_OBJECT_EXT    0x959B
#تعریف_کرو GL_عدد_TILING_TYPES_EXT           0x9582
#تعریف_کرو GL_TILING_TYPES_EXT               0x9583
#تعریف_کرو GL_OPTIMAL_TILING_EXT             0x9584
#تعریف_کرو GL_خطی_TILING_EXT              0x9585
#تعریف_کرو GL_عدد_DEVICE_UUIDS_EXT           0x9596
#تعریف_کرو GL_DEVICE_UUID_EXT                0x9597
#تعریف_کرو GL_DRIVER_UUID_EXT                0x9598
#تعریف_کرو GL_UUID_سائز_EXT                  16
قسمتعریف خالی (GL_APIENTRYP PFNGLGETUNSIGNEDBYTEVEXTPROC) (GLenum pname, GLubyte *ڈیٹا);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETUNSIGNEDBYTEI_VEXTPROC) (GLenum ہدف, GLuint اشاریہ, GLubyte *ڈیٹا);
قسمتعریف خالی (GL_APIENTRYP PFNGLDELETEMEMORYOBJECTSEXTPROC) (GLsizei n, ثابت GLuint *حافظہ_Objects);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLISMEMORYOBJECTEXTPROC) (GLuint حافظہ_Object);
قسمتعریف خالی (GL_APIENTRYP PFNGLCREATEMEMORYOBJECTSEXTPROC) (GLsizei n, GLuint *حافظہ_Objects);
قسمتعریف خالی (GL_APIENTRYP PFNGLMEMORYOBJECTPARAMETERIVEXTPROC) (GLuint حافظہ_Object, GLenum pname, ثابت GLint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETMEMORYOBJECTPARAMETERIVEXTPROC) (GLuint حافظہ_Object, GLenum pname, GLint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXSTORAGEMEM2DEXTPROC) (GLenum ہدف, GLsizei سطحیں, GLenum اندرونی_Format, GLsizei چوڑائی, GLsizei اونچائی, GLuint حافظہ, GLuint64 انحراف_2);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXSTORAGEMEM2DMULTISAMPLEEXTPROC) (GLenum ہدف, GLsizei samples, GLenum اندرونی_Format, GLsizei چوڑائی, GLsizei اونچائی, GLboolean fixedSampleLocations, GLuint حافظہ, GLuint64 انحراف_2);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXSTORAGEMEM3DEXTPROC) (GLenum ہدف, GLsizei سطحیں, GLenum اندرونی_Format, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLuint حافظہ, GLuint64 انحراف_2);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXSTORAGEMEM3DMULTISAMPLEEXTPROC) (GLenum ہدف, GLsizei samples, GLenum اندرونی_Format, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLboolean fixedSampleLocations, GLuint حافظہ, GLuint64 انحراف_2);
قسمتعریف خالی (GL_APIENTRYP PFNGLBUFFERSTORAGEMEMEXTPROC) (GLenum ہدف, GLsizeiptr سائز, GLuint حافظہ, GLuint64 انحراف_2);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXTURESTORAGEMEM2DEXTPROC) (GLuint texture, GLsizei سطحیں, GLenum اندرونی_Format, GLsizei چوڑائی, GLsizei اونچائی, GLuint حافظہ, GLuint64 انحراف_2);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXTURESTORAGEMEM2DMULTISAMPLEEXTPROC) (GLuint texture, GLsizei samples, GLenum اندرونی_Format, GLsizei چوڑائی, GLsizei اونچائی, GLboolean fixedSampleLocations, GLuint حافظہ, GLuint64 انحراف_2);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXTURESTORAGEMEM3DEXTPROC) (GLuint texture, GLsizei سطحیں, GLenum اندرونی_Format, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLuint حافظہ, GLuint64 انحراف_2);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXTURESTORAGEMEM3DMULTISAMPLEEXTPROC) (GLuint texture, GLsizei samples, GLenum اندرونی_Format, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLboolean fixedSampleLocations, GLuint حافظہ, GLuint64 انحراف_2);
قسمتعریف خالی (GL_APIENTRYP PFNGLNAMEDBUFFERSTORAGEMEMEXTPROC) (GLuint بفر_2, GLsizeiptr سائز, GLuint حافظہ, GLuint64 انحراف_2);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glGetUnsignedBytevEXT (GLenum pname, GLubyte *ڈیٹا);
GL_APICALL خالی GL_APIENTRY glGetUnsignedBytei_vEXT (GLenum ہدف, GLuint اشاریہ, GLubyte *ڈیٹا);
GL_APICALL خالی GL_APIENTRY gl_Delete_حافظہ_Objects_EXT (GLsizei n, ثابت GLuint *حافظہ_Objects);
GL_APICALL GLboolean GL_APIENTRY gl_Is_حافظہ_Object_EXT (GLuint حافظہ_Object);
GL_APICALL خالی GL_APIENTRY gl_Create_حافظہ_Objects_EXT (GLsizei n, GLuint *حافظہ_Objects);
GL_APICALL خالی GL_APIENTRY gl_حافظہ_Object_Parameteriv_EXT (GLuint حافظہ_Object, GLenum pname, ثابت GLint *params);
GL_APICALL خالی GL_APIENTRY gl_Get_حافظہ_Object_Parameteriv_EXT (GLuint حافظہ_Object, GLenum pname, GLint *params);
GL_APICALL خالی GL_APIENTRY glTexStorageMem2DEXT (GLenum ہدف, GLsizei سطحیں, GLenum اندرونی_Format, GLsizei چوڑائی, GLsizei اونچائی, GLuint حافظہ, GLuint64 انحراف_2);
GL_APICALL خالی GL_APIENTRY glTexStorageMem2DMultisampleEXT (GLenum ہدف, GLsizei samples, GLenum اندرونی_Format, GLsizei چوڑائی, GLsizei اونچائی, GLboolean fixedSampleLocations, GLuint حافظہ, GLuint64 انحراف_2);
GL_APICALL خالی GL_APIENTRY glTexStorageMem3DEXT (GLenum ہدف, GLsizei سطحیں, GLenum اندرونی_Format, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLuint حافظہ, GLuint64 انحراف_2);
GL_APICALL خالی GL_APIENTRY glTexStorageMem3DMultisampleEXT (GLenum ہدف, GLsizei samples, GLenum اندرونی_Format, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLboolean fixedSampleLocations, GLuint حافظہ, GLuint64 انحراف_2);
GL_APICALL خالی GL_APIENTRY gl_بفر_Storage_Mem_EXT (GLenum ہدف, GLsizeiptr سائز, GLuint حافظہ, GLuint64 انحراف_2);
GL_APICALL خالی GL_APIENTRY glTextureStorageMem2DEXT (GLuint texture, GLsizei سطحیں, GLenum اندرونی_Format, GLsizei چوڑائی, GLsizei اونچائی, GLuint حافظہ, GLuint64 انحراف_2);
GL_APICALL خالی GL_APIENTRY glTextureStorageMem2DMultisampleEXT (GLuint texture, GLsizei samples, GLenum اندرونی_Format, GLsizei چوڑائی, GLsizei اونچائی, GLboolean fixedSampleLocations, GLuint حافظہ, GLuint64 انحراف_2);
GL_APICALL خالی GL_APIENTRY glTextureStorageMem3DEXT (GLuint texture, GLsizei سطحیں, GLenum اندرونی_Format, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLuint حافظہ, GLuint64 انحراف_2);
GL_APICALL خالی GL_APIENTRY glTextureStorageMem3DMultisampleEXT (GLuint texture, GLsizei samples, GLenum اندرونی_Format, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLboolean fixedSampleLocations, GLuint حافظہ, GLuint64 انحراف_2);
GL_APICALL خالی GL_APIENTRY gl_Named_بفر_Storage_Mem_EXT (GLuint بفر_2, GLsizeiptr سائز, GLuint حافظہ, GLuint64 انحراف_2);
#اگر_ختم
#اگر_ختم /* GL_EXT_memory_object */

#اگر_غیر_تعریف_شدہ GL_EXT_حافظہ_object_fd
#تعریف_کرو GL_EXT_حافظہ_object_fd 1
#تعریف_کرو GL_HANDLE_TYPE_OPAQUE_FD_EXT      0x9586
قسمتعریف خالی (GL_APIENTRYP PFNGLIMPORTMEMORYFDEXTPROC) (GLuint حافظہ, GLuint64 سائز, GLenum handleType, GLint fd);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_Import_حافظہ_Fd_EXT (GLuint حافظہ, GLuint64 سائز, GLenum handleType, GLint fd);
#اگر_ختم
#اگر_ختم /* GL_EXT_memory_object_fd */

#اگر_غیر_تعریف_شدہ GL_EXT_حافظہ_object_win32
#تعریف_کرو GL_EXT_حافظہ_object_win32 1
#تعریف_کرو GL_HANDLE_TYPE_OPAQUE_WIN32_EXT   0x9587
#تعریف_کرو GL_HANDLE_TYPE_OPAQUE_WIN32_KMT_EXT 0x9588
#تعریف_کرو GL_DEVICE_LUID_EXT                0x9599
#تعریف_کرو GL_DEVICE_گرہ_نقاب_EXT           0x959A
#تعریف_کرو GL_LUID_سائز_EXT                  8
#تعریف_کرو GL_HANDLE_TYPE_D3D12_TILEPOOL_EXT 0x9589
#تعریف_کرو GL_HANDLE_TYPE_D3D12_RESOURCE_EXT 0x958A
#تعریف_کرو GL_HANDLE_TYPE_D3D11_IMAGE_EXT    0x958B
#تعریف_کرو GL_HANDLE_TYPE_D3D11_IMAGE_KMT_EXT 0x958C
قسمتعریف خالی (GL_APIENTRYP PFNGLIMPORTMEMORYWIN32HANDLEEXTPROC) (GLuint حافظہ, GLuint64 سائز, GLenum handleType, خالی *handle);
قسمتعریف خالی (GL_APIENTRYP PFNGLIMPORTMEMORYWIN32NAMEEXTPROC) (GLuint حافظہ, GLuint64 سائز, GLenum handleType, ثابت خالی *name);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_Import_حافظہ_Win32_Handle_EXT (GLuint حافظہ, GLuint64 سائز, GLenum handleType, خالی *handle);
GL_APICALL خالی GL_APIENTRY gl_Import_حافظہ_Win32_Name_EXT (GLuint حافظہ, GLuint64 سائز, GLenum handleType, ثابت خالی *name);
#اگر_ختم
#اگر_ختم /* GL_EXT_memory_object_win32 */

#اگر_غیر_تعریف_شدہ GL_EXT_mesh_shader
#تعریف_کرو GL_EXT_mesh_shader 1
#تعریف_کرو GL_MESH_SHADER_EXT                0x9559
#تعریف_کرو GL_TASK_SHADER_EXT                0x955A
#تعریف_کرو GL_MAX_MESH_یکساں_بلاکیں_EXT    0x8E60
#تعریف_کرو GL_MAX_MESH_TEXTURE_IMAGE_UNITS_EXT 0x8E61
#تعریف_کرو GL_MAX_MESH_IMAGE_UNIFORMS_EXT    0x8E62
#تعریف_کرو GL_MAX_MESH_یکساں_COMPONENTS_EXT 0x8E63
#تعریف_کرو GL_MAX_MESH_ATOMIC_شمار_BUFFERS_EXT 0x8E64
#تعریف_کرو GL_MAX_MESH_ATOMIC_COUNTERS_EXT   0x8E65
#تعریف_کرو GL_MAX_MESH_SHADER_STORAGE_بلاکیں_EXT 0x8E66
#تعریف_کرو GL_MAX_COMBINED_MESH_یکساں_COMPONENTS_EXT 0x8E67
#تعریف_کرو GL_MAX_TASK_یکساں_بلاکیں_EXT    0x8E68
#تعریف_کرو GL_MAX_TASK_TEXTURE_IMAGE_UNITS_EXT 0x8E69
#تعریف_کرو GL_MAX_TASK_IMAGE_UNIFORMS_EXT    0x8E6A
#تعریف_کرو GL_MAX_TASK_یکساں_COMPONENTS_EXT 0x8E6B
#تعریف_کرو GL_MAX_TASK_ATOMIC_شمار_BUFFERS_EXT 0x8E6C
#تعریف_کرو GL_MAX_TASK_ATOMIC_COUNTERS_EXT   0x8E6D
#تعریف_کرو GL_MAX_TASK_SHADER_STORAGE_بلاکیں_EXT 0x8E6E
#تعریف_کرو GL_MAX_COMBINED_TASK_یکساں_COMPONENTS_EXT 0x8E6F
#تعریف_کرو GL_MAX_TASK_WORK_گروہ_کل_گنتی_EXT 0x9740
#تعریف_کرو GL_MAX_MESH_WORK_گروہ_کل_گنتی_EXT 0x9741
#تعریف_کرو GL_MAX_MESH_WORK_گروہ_INVOCATIONS_EXT 0x9757
#تعریف_کرو GL_MAX_TASK_WORK_گروہ_INVOCATIONS_EXT 0x9759
#تعریف_کرو GL_MAX_TASK_PAYLOAD_سائز_EXT      0x9742
#تعریف_کرو GL_MAX_TASK_SHARED_حافظہ_سائز_EXT 0x9743
#تعریف_کرو GL_MAX_MESH_SHARED_حافظہ_سائز_EXT 0x9744
#تعریف_کرو GL_MAX_TASK_PAYLOAD_AND_SHARED_حافظہ_سائز_EXT 0x9745
#تعریف_کرو GL_MAX_MESH_PAYLOAD_AND_SHARED_حافظہ_سائز_EXT 0x9746
#تعریف_کرو GL_MAX_MESH_OUTPUT_حافظہ_سائز_EXT 0x9747
#تعریف_کرو GL_MAX_MESH_PAYLOAD_AND_OUTPUT_حافظہ_سائز_EXT 0x9748
#تعریف_کرو GL_MAX_MESH_OUTPUT_VERTICES_EXT   0x9538
#تعریف_کرو GL_MAX_MESH_OUTPUT_PRIMITIVES_EXT 0x9756
#تعریف_کرو GL_MAX_MESH_OUTPUT_COMPONENTS_EXT 0x9749
#تعریف_کرو GL_MAX_MESH_OUTPUT_LAYERS_EXT     0x974A
#تعریف_کرو GL_MAX_MESH_MULTIVIEW_VIEW_گنتی_EXT 0x9557
#تعریف_کرو GL_MESH_OUTPUT_فی_راس_GRANULARITY_EXT 0x92DF
#تعریف_کرو GL_MESH_OUTPUT_فی_PRIMITIVE_GRANULARITY_EXT 0x9543
#تعریف_کرو GL_MAX_PREFERRED_TASK_WORK_گروہ_INVOCATIONS_EXT 0x974B
#تعریف_کرو GL_MAX_PREFERRED_MESH_WORK_گروہ_INVOCATIONS_EXT 0x974C
#تعریف_کرو GL_MESH_PREFERS_LOCAL_INVOCATION_راس_OUTPUT_EXT 0x974D
#تعریف_کرو GL_MESH_PREFERS_LOCAL_INVOCATION_PRIMITIVE_OUTPUT_EXT 0x974E
#تعریف_کرو GL_MESH_PREFERS_COMPACT_راس_OUTPUT_EXT 0x974F
#تعریف_کرو GL_MESH_PREFERS_COMPACT_PRIMITIVE_OUTPUT_EXT 0x9750
#تعریف_کرو GL_MAX_TASK_WORK_گروہ_گنتی_EXT  0x9751
#تعریف_کرو GL_MAX_MESH_WORK_گروہ_گنتی_EXT  0x9752
#تعریف_کرو GL_MAX_MESH_WORK_گروہ_سائز_EXT   0x9758
#تعریف_کرو GL_MAX_TASK_WORK_گروہ_سائز_EXT   0x975A
#تعریف_کرو GL_MESH_WORK_گروہ_سائز_EXT       0x953E
#تعریف_کرو GL_TASK_WORK_گروہ_سائز_EXT       0x953F
#تعریف_کرو GL_MESH_VERTICES_برآمد_EXT          0x9579
#تعریف_کرو GL_MESH_PRIMITIVES_برآمد_EXT        0x957A
#تعریف_کرو GL_MESH_OUTPUT_TYPE_EXT           0x957B
#تعریف_کرو GL_یکساں_بلاک_REFERENCED_BY_MESH_SHADER_EXT 0x959C
#تعریف_کرو GL_یکساں_بلاک_REFERENCED_BY_TASK_SHADER_EXT 0x959D
#تعریف_کرو GL_REFERENCED_BY_MESH_SHADER_EXT  0x95A0
#تعریف_کرو GL_REFERENCED_BY_TASK_SHADER_EXT  0x95A1
#تعریف_کرو GL_TASK_SHADER_INVOCATIONS_EXT    0x9753
#تعریف_کرو GL_MESH_SHADER_INVOCATIONS_EXT    0x9754
#تعریف_کرو GL_MESH_PRIMITIVES_GENERATED_EXT  0x9755
#تعریف_کرو GL_MESH_SHADER_ثنائی_ہندسہ_EXT            0x00000040
#تعریف_کرو GL_TASK_SHADER_ثنائی_ہندسہ_EXT            0x00000080
#تعریف_کرو GL_MESH_SUBROUTINE_EXT            0x957C
#تعریف_کرو GL_TASK_SUBROUTINE_EXT            0x957D
#تعریف_کرو GL_MESH_SUBROUTINE_یکساں_EXT    0x957E
#تعریف_کرو GL_TASK_SUBROUTINE_یکساں_EXT    0x957F
#تعریف_کرو GL_ATOMIC_شمار_بفر_REFERENCED_BY_MESH_SHADER_EXT 0x959E
#تعریف_کرو GL_ATOMIC_شمار_بفر_REFERENCED_BY_TASK_SHADER_EXT 0x959F
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWMESHTASKSEXTPROC) (GLuint عدد_groups_x, GLuint عدد_groups_y, GLuint عدد_groups_z);
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWMESHTASKSINDIRECTEXTPROC) (GLintptr بالواسطہ);
قسمتعریف خالی (GL_APIENTRYP PFNGLMULTIDRAWMESHTASKSINDIRECTEXTPROC) (GLintptr بالواسطہ, GLsizei drawcount, GLsizei stride);
قسمتعریف خالی (GL_APIENTRYP PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTEXTPROC) (GLintptr بالواسطہ, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glDrawMeshTasksEXT (GLuint عدد_groups_x, GLuint عدد_groups_y, GLuint عدد_groups_z);
GL_APICALL خالی GL_APIENTRY gl_Draw_Mesh_Tasks_بالواسطہ_EXT (GLintptr بالواسطہ);
GL_APICALL خالی GL_APIENTRY gl_Multi_Draw_Mesh_Tasks_بالواسطہ_EXT (GLintptr بالواسطہ, GLsizei drawcount, GLsizei stride);
GL_APICALL خالی GL_APIENTRY gl_Multi_Draw_Mesh_Tasks_بالواسطہ_گنتی_EXT (GLintptr بالواسطہ, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
#اگر_ختم
#اگر_ختم /* GL_EXT_mesh_shader */

#اگر_غیر_تعریف_شدہ GL_EXT_multi_draw_arrays
#تعریف_کرو GL_EXT_multi_draw_arrays 1
قسمتعریف خالی (GL_APIENTRYP PFNGLMULTIDRAWARRAYSEXTPROC) (GLenum منوال, ثابت GLint *پہلا, ثابت GLsizei *گنتی, GLsizei primcount);
قسمتعریف خالی (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSEXTPROC) (GLenum منوال, ثابت GLsizei *گنتی, GLenum type, ثابت خالی *ثابت*indices, GLsizei primcount);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glMultiDrawArraysEXT (GLenum منوال, ثابت GLint *پہلا, ثابت GLsizei *گنتی, GLsizei primcount);
GL_APICALL خالی GL_APIENTRY glMultiDrawElementsEXT (GLenum منوال, ثابت GLsizei *گنتی, GLenum type, ثابت خالی *ثابت*indices, GLsizei primcount);
#اگر_ختم
#اگر_ختم /* GL_EXT_multi_draw_arrays */

#اگر_غیر_تعریف_شدہ GL_EXT_multi_draw_بالواسطہ
#تعریف_کرو GL_EXT_multi_draw_بالواسطہ 1
قسمتعریف خالی (GL_APIENTRYP PFNGLMULTIDRAWARRAYSINDIRECTEXTPROC) (GLenum منوال, ثابت خالی *بالواسطہ, GLsizei drawcount, GLsizei stride);
قسمتعریف خالی (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSINDIRECTEXTPROC) (GLenum منوال, GLenum type, ثابت خالی *بالواسطہ, GLsizei drawcount, GLsizei stride);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_Multi_Draw_Arrays_بالواسطہ_EXT (GLenum منوال, ثابت خالی *بالواسطہ, GLsizei drawcount, GLsizei stride);
GL_APICALL خالی GL_APIENTRY gl_Multi_Draw_Elements_بالواسطہ_EXT (GLenum منوال, GLenum type, ثابت خالی *بالواسطہ, GLsizei drawcount, GLsizei stride);
#اگر_ختم
#اگر_ختم /* GL_EXT_multi_draw_indirect */

#اگر_غیر_تعریف_شدہ GL_EXT_multisampled_compatibility
#تعریف_کرو GL_EXT_multisampled_compatibility 1
#تعریف_کرو GL_MULTISAMPLE_EXT                0x809D
#تعریف_کرو GL_SAMPLE_ALPHA_مقصد_ONE_EXT        0x809F
#اگر_ختم /* GL_EXT_multisampled_compatibility */

#اگر_غیر_تعریف_شدہ GL_EXT_multisampled_render_مقصد_texture
#تعریف_کرو GL_EXT_multisampled_render_مقصد_texture 1
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SAMPLES_EXT 0x8D6C
#تعریف_کرو GL_RENDERBUFFER_SAMPLES_EXT       0x8CAB
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT 0x8D56
#تعریف_کرو GL_MAX_SAMPLES_EXT                0x8D57
قسمتعریف خالی (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) (GLenum ہدف, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEEXTPROC) (GLenum ہدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glRenderbufferStorageMultisampleEXT (GLenum ہدف, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
GL_APICALL خالی GL_APIENTRY glFramebufferTexture2DMultisampleEXT (GLenum ہدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#اگر_ختم
#اگر_ختم /* GL_EXT_multisampled_render_to_texture */

#اگر_غیر_تعریف_شدہ GL_EXT_multisampled_render_مقصد_texture2
#تعریف_کرو GL_EXT_multisampled_render_مقصد_texture2 1
#اگر_ختم /* GL_EXT_multisampled_render_to_texture2 */

#اگر_غیر_تعریف_شدہ GL_EXT_multiview_draw_buffers
#تعریف_کرو GL_EXT_multiview_draw_buffers 1
#تعریف_کرو GL_COLOR_ATTACHMENT_EXT           0x90F0
#تعریف_کرو GL_MULTIVIEW_EXT                  0x90F1
#تعریف_کرو GL_DRAW_بفر_EXT                0x0C01
#تعریف_کرو GL_READ_بفر_EXT                0x0C02
#تعریف_کرو GL_MAX_MULTIVIEW_BUFFERS_EXT      0x90F2
قسمتعریف خالی (GL_APIENTRYP PFNGLREADBUFFERINDEXEDEXTPROC) (GLenum src, GLint اشاریہ);
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWBUFFERSINDEXEDEXTPROC) (GLint n, ثابت GLenum *location, ثابت GLint *indices);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETINTEGERI_VEXTPROC) (GLenum ہدف, GLuint اشاریہ, GLint *ڈیٹا);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_Read_بفر_اشاریہ_دار_EXT (GLenum src, GLint اشاریہ);
GL_APICALL خالی GL_APIENTRY gl_Draw_Buffers_اشاریہ_دار_EXT (GLint n, ثابت GLenum *location, ثابت GLint *indices);
GL_APICALL خالی GL_APIENTRY glGetIntegeri_vEXT (GLenum ہدف, GLuint اشاریہ, GLint *ڈیٹا);
#اگر_ختم
#اگر_ختم /* GL_EXT_multiview_draw_buffers */

#اگر_غیر_تعریف_شدہ GL_EXT_multiview_tessellation_geometry_shader
#تعریف_کرو GL_EXT_multiview_tessellation_geometry_shader 1
#اگر_ختم /* GL_EXT_multiview_tessellation_geometry_shader */

#اگر_غیر_تعریف_شدہ GL_EXT_multiview_texture_multisample
#تعریف_کرو GL_EXT_multiview_texture_multisample 1
#اگر_ختم /* GL_EXT_multiview_texture_multisample */

#اگر_غیر_تعریف_شدہ GL_EXT_multiview_timer_query
#تعریف_کرو GL_EXT_multiview_timer_query 1
#اگر_ختم /* GL_EXT_multiview_timer_query */

#اگر_غیر_تعریف_شدہ GL_EXT_occlusion_query_boolean
#تعریف_کرو GL_EXT_occlusion_query_boolean 1
#تعریف_کرو GL_ANY_SAMPLES_PASSED_EXT         0x8C2F
#تعریف_کرو GL_ANY_SAMPLES_PASSED_CONSERVATIVE_EXT 0x8D6A
#اگر_ختم /* GL_EXT_occlusion_query_boolean */

#اگر_غیر_تعریف_شدہ GL_EXT_polygon_انحراف_clamp
#تعریف_کرو GL_EXT_polygon_انحراف_clamp 1
#تعریف_کرو GL_POLYGON_انحراف_CLAMP_EXT       0x8E1B
قسمتعریف خالی (GL_APIENTRYP PFNGLPOLYGONOFFSETCLAMPEXTPROC) (GLfloat ضربی_عدد, GLfloat units, GLfloat clamp);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_Polygon_انحراف_Clamp_EXT (GLfloat ضربی_عدد, GLfloat units, GLfloat clamp);
#اگر_ختم
#اگر_ختم /* GL_EXT_polygon_offset_clamp */

#اگر_غیر_تعریف_شدہ GL_EXT_post_گہرائی_coverage
#تعریف_کرو GL_EXT_post_گہرائی_coverage 1
#اگر_ختم /* GL_EXT_post_depth_coverage */

#اگر_غیر_تعریف_شدہ GL_EXT_primitive_bounding_box
#تعریف_کرو GL_EXT_primitive_bounding_box 1
#تعریف_کرو GL_PRIMITIVE_BOUNDING_BOX_EXT     0x92BE
قسمتعریف خالی (GL_APIENTRYP PFNGLPRIMITIVEBOUNDINGBOXEXTPROC) (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glPrimitiveBoundingBoxEXT (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
#اگر_ختم
#اگر_ختم /* GL_EXT_primitive_bounding_box */

#اگر_غیر_تعریف_شدہ GL_EXT_protected_textures
#تعریف_کرو GL_EXT_protected_textures 1
#تعریف_کرو GL_CONTEXT_FLAG_PROTECTED_CONTENT_ثنائی_ہندسہ_EXT 0x00000010
#تعریف_کرو GL_TEXTURE_PROTECTED_EXT          0x8BFA
#اگر_ختم /* GL_EXT_protected_textures */

#اگر_غیر_تعریف_شدہ GL_EXT_pvrtc_sRGB
#تعریف_کرو GL_EXT_pvrtc_sRGB 1
#تعریف_کرو GL_COMPRESSED_SRGB_PVRTC_2BPPV1_EXT 0x8A54
#تعریف_کرو GL_COMPRESSED_SRGB_PVRTC_4BPPV1_EXT 0x8A55
#تعریف_کرو GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV1_EXT 0x8A56
#تعریف_کرو GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV1_EXT 0x8A57
#تعریف_کرو GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV2_IMG 0x93F0
#تعریف_کرو GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV2_IMG 0x93F1
#اگر_ختم /* GL_EXT_pvrtc_sRGB */

#اگر_غیر_تعریف_شدہ GL_EXT_raster_multisample
#تعریف_کرو GL_EXT_raster_multisample 1
#تعریف_کرو GL_RASTER_MULTISAMPLE_EXT         0x9327
#تعریف_کرو GL_RASTER_SAMPLES_EXT             0x9328
#تعریف_کرو GL_MAX_RASTER_SAMPLES_EXT         0x9329
#تعریف_کرو GL_RASTER_FIXED_SAMPLE_LOCATIONS_EXT 0x932A
#تعریف_کرو GL_MULTISAMPLE_RASTERIZATION_ALLOWED_EXT 0x932B
#تعریف_کرو GL_EFFECTIVE_RASTER_SAMPLES_EXT   0x932C
قسمتعریف خالی (GL_APIENTRYP PFNGLRASTERSAMPLESEXTPROC) (GLuint samples, GLboolean fixedsamplelocations);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glRasterSamplesEXT (GLuint samples, GLboolean fixedsamplelocations);
#اگر_ختم
#اگر_ختم /* GL_EXT_raster_multisample */

#اگر_غیر_تعریف_شدہ GL_EXT_read_format_bgra
#تعریف_کرو GL_EXT_read_format_bgra 1
#تعریف_کرو GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT 0x8365
#تعریف_کرو GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT 0x8366
#اگر_ختم /* GL_EXT_read_format_bgra */

#اگر_غیر_تعریف_شدہ GL_EXT_render_snorm
#تعریف_کرو GL_EXT_render_snorm 1
#تعریف_کرو GL_R8_SNORM                       0x8F94
#تعریف_کرو GL_RG8_SNORM                      0x8F95
#تعریف_کرو GL_RGBA8_SNORM                    0x8F97
#تعریف_کرو GL_R16_SNORM_EXT                  0x8F98
#تعریف_کرو GL_RG16_SNORM_EXT                 0x8F99
#تعریف_کرو GL_RGBA16_SNORM_EXT               0x8F9B
#اگر_ختم /* GL_EXT_render_snorm */

#اگر_غیر_تعریف_شدہ GL_EXT_robustness
#تعریف_کرو GL_EXT_robustness 1
#تعریف_کرو GL_GUILTY_CONTEXT_RESET_EXT       0x8253
#تعریف_کرو GL_INNOCENT_CONTEXT_RESET_EXT     0x8254
#تعریف_کرو GL_UNKNOWN_CONTEXT_RESET_EXT      0x8255
#تعریف_کرو GL_CONTEXT_ROBUST_ACCESS_EXT      0x90F3
#تعریف_کرو GL_RESET_NOTIFICATION_STRATEGY_EXT 0x8256
#تعریف_کرو GL_LOSE_CONTEXT_ON_RESET_EXT      0x8252
#تعریف_کرو GL_NO_RESET_NOTIFICATION_EXT      0x8261
قسمتعریف GLenum (GL_APIENTRYP PFNGLGETGRAPHICSRESETSTATUSEXTPROC) (خالی);
قسمتعریف خالی (GL_APIENTRYP PFNGLREADNPIXELSEXTPROC) (GLint x, GLint y, GLsizei چوڑائی, GLsizei اونچائی, GLenum format, GLenum type, GLsizei buf_سائز, خالی *ڈیٹا);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETNUNIFORMFVEXTPROC) (GLuint پروگرام, GLint location, GLsizei buf_سائز, GLfloat *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETNUNIFORMIVEXTPROC) (GLuint پروگرام, GLint location, GLsizei buf_سائز, GLint *params);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL GLenum GL_APIENTRY gl_Get_Graphics_Reset_حالت_EXT (خالی);
GL_APICALL خالی GL_APIENTRY glReadnPixelsEXT (GLint x, GLint y, GLsizei چوڑائی, GLsizei اونچائی, GLenum format, GLenum type, GLsizei buf_سائز, خالی *ڈیٹا);
GL_APICALL خالی GL_APIENTRY glGetnUniformfvEXT (GLuint پروگرام, GLint location, GLsizei buf_سائز, GLfloat *params);
GL_APICALL خالی GL_APIENTRY glGetnUniformivEXT (GLuint پروگرام, GLint location, GLsizei buf_سائز, GLint *params);
#اگر_ختم
#اگر_ختم /* GL_EXT_robustness */

#اگر_غیر_تعریف_شدہ GL_EXT_sRGB
#تعریف_کرو GL_EXT_sRGB 1
#تعریف_کرو GL_SRGB_EXT                       0x8C40
#تعریف_کرو GL_SRGB_ALPHA_EXT                 0x8C42
#تعریف_کرو GL_SRGB8_ALPHA8_EXT               0x8C43
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING_EXT 0x8210
#اگر_ختم /* GL_EXT_sRGB */

#اگر_غیر_تعریف_شدہ GL_EXT_sRGB_write_control
#تعریف_کرو GL_EXT_sRGB_write_control 1
#تعریف_کرو GL_FRAMEBUFFER_SRGB_EXT           0x8DB9
#اگر_ختم /* GL_EXT_sRGB_write_control */

#اگر_غیر_تعریف_شدہ GL_EXT_semaphore
#تعریف_کرو GL_EXT_semaphore 1
#تعریف_کرو GL_LAYOUT_GENERAL_EXT             0x958D
#تعریف_کرو GL_LAYOUT_COLOR_ATTACHMENT_EXT    0x958E
#تعریف_کرو GL_LAYOUT_گہرائی_STENCIL_ATTACHMENT_EXT 0x958F
#تعریف_کرو GL_LAYOUT_گہرائی_STENCIL_READ_ONLY_EXT 0x9590
#تعریف_کرو GL_LAYOUT_SHADER_READ_ONLY_EXT    0x9591
#تعریف_کرو GL_LAYOUT_TRANSFER_SRC_EXT        0x9592
#تعریف_کرو GL_LAYOUT_TRANSFER_DST_EXT        0x9593
#تعریف_کرو GL_LAYOUT_گہرائی_READ_ONLY_STENCIL_ATTACHMENT_EXT 0x9530
#تعریف_کرو GL_LAYOUT_گہرائی_ATTACHMENT_STENCIL_READ_ONLY_EXT 0x9531
قسمتعریف خالی (GL_APIENTRYP PFNGLGENSEMAPHORESEXTPROC) (GLsizei n, GLuint *semaphores);
قسمتعریف خالی (GL_APIENTRYP PFNGLDELETESEMAPHORESEXTPROC) (GLsizei n, ثابت GLuint *semaphores);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLISSEMAPHOREEXTPROC) (GLuint semaphore);
قسمتعریف خالی (GL_APIENTRYP PFNGLSEMAPHOREPARAMETERUI64VEXTPROC) (GLuint semaphore, GLenum pname, ثابت GLuint64 *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETSEMAPHOREPARAMETERUI64VEXTPROC) (GLuint semaphore, GLenum pname, GLuint64 *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLWAITSEMAPHOREEXTPROC) (GLuint semaphore, GLuint عدد_بفر_Barriers, ثابت GLuint *buffers, GLuint عدد_Texture_Barriers, ثابت GLuint *textures, ثابت GLenum *srcLayouts);
قسمتعریف خالی (GL_APIENTRYP PFNGLSIGNALSEMAPHOREEXTPROC) (GLuint semaphore, GLuint عدد_بفر_Barriers, ثابت GLuint *buffers, GLuint عدد_Texture_Barriers, ثابت GLuint *textures, ثابت GLenum *dstLayouts);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glGenSemaphoresEXT (GLsizei n, GLuint *semaphores);
GL_APICALL خالی GL_APIENTRY glDeleteSemaphoresEXT (GLsizei n, ثابت GLuint *semaphores);
GL_APICALL GLboolean GL_APIENTRY glIsSemaphoreEXT (GLuint semaphore);
GL_APICALL خالی GL_APIENTRY glSemaphoreParameterui64vEXT (GLuint semaphore, GLenum pname, ثابت GLuint64 *params);
GL_APICALL خالی GL_APIENTRY glGetSemaphoreParameterui64vEXT (GLuint semaphore, GLenum pname, GLuint64 *params);
GL_APICALL خالی GL_APIENTRY glWaitSemaphoreEXT (GLuint semaphore, GLuint عدد_بفر_Barriers, ثابت GLuint *buffers, GLuint عدد_Texture_Barriers, ثابت GLuint *textures, ثابت GLenum *srcLayouts);
GL_APICALL خالی GL_APIENTRY glSignalSemaphoreEXT (GLuint semaphore, GLuint عدد_بفر_Barriers, ثابت GLuint *buffers, GLuint عدد_Texture_Barriers, ثابت GLuint *textures, ثابت GLenum *dstLayouts);
#اگر_ختم
#اگر_ختم /* GL_EXT_semaphore */

#اگر_غیر_تعریف_شدہ GL_EXT_semaphore_fd
#تعریف_کرو GL_EXT_semaphore_fd 1
قسمتعریف خالی (GL_APIENTRYP PFNGLIMPORTSEMAPHOREFDEXTPROC) (GLuint semaphore, GLenum handleType, GLint fd);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glImportSemaphoreFdEXT (GLuint semaphore, GLenum handleType, GLint fd);
#اگر_ختم
#اگر_ختم /* GL_EXT_semaphore_fd */

#اگر_غیر_تعریف_شدہ GL_EXT_semaphore_win32
#تعریف_کرو GL_EXT_semaphore_win32 1
#تعریف_کرو GL_HANDLE_TYPE_D3D12_FENCE_EXT    0x9594
#تعریف_کرو GL_D3_D12_FENCE_قدر_EXT          0x9595
قسمتعریف خالی (GL_APIENTRYP PFNGLIMPORTSEMAPHOREWIN32HANDLEEXTPROC) (GLuint semaphore, GLenum handleType, خالی *handle);
قسمتعریف خالی (GL_APIENTRYP PFNGLIMPORTSEMAPHOREWIN32NAMEEXTPROC) (GLuint semaphore, GLenum handleType, ثابت خالی *name);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glImportSemaphoreWin32HandleEXT (GLuint semaphore, GLenum handleType, خالی *handle);
GL_APICALL خالی GL_APIENTRY glImportSemaphoreWin32NameEXT (GLuint semaphore, GLenum handleType, ثابت خالی *name);
#اگر_ختم
#اگر_ختم /* GL_EXT_semaphore_win32 */

#اگر_غیر_تعریف_شدہ GL_EXT_separate_گہرائی_stencil
#تعریف_کرو GL_EXT_separate_گہرائی_stencil 1
#اگر_ختم /* GL_EXT_separate_depth_stencil */

#اگر_غیر_تعریف_شدہ GL_EXT_separate_shader_objects
#تعریف_کرو GL_EXT_separate_shader_objects 1
#تعریف_کرو GL_فعال_پروگرام_EXT             0x8259
#تعریف_کرو GL_راس_SHADER_ثنائی_ہندسہ_EXT          0x00000001
#تعریف_کرو GL_FRAGMENT_SHADER_ثنائی_ہندسہ_EXT        0x00000002
#تعریف_کرو GL_ALL_SHADER_بٹ_EXT            0xFFFFFFFF
#تعریف_کرو GL_پروگرام_SEPARABLE_EXT          0x8258
#تعریف_کرو GL_پروگرام_PIPELINE_BINDING_EXT   0x825A
قسمتعریف خالی (GL_APIENTRYP PFNGLACTIVESHADERPROGRAMEXTPROC) (GLuint pipeline, GLuint پروگرام);
قسمتعریف خالی (GL_APIENTRYP PFNGLBINDPROGRAMPIPELINEEXTPROC) (GLuint pipeline);
قسمتعریف GLuint (GL_APIENTRYP PFNGLCREATESHADERPROGRAMVEXTPROC) (GLenum type, GLsizei گنتی, ثابت GLchar *ثابت*لڑیاں);
قسمتعریف خالی (GL_APIENTRYP PFNGLDELETEPROGRAMPIPELINESEXTPROC) (GLsizei n, ثابت GLuint *pipelines);
قسمتعریف خالی (GL_APIENTRYP PFNGLGENPROGRAMPIPELINESEXTPROC) (GLsizei n, GLuint *pipelines);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETPROGRAMPIPELINEINFOLOGEXTPROC) (GLuint pipeline, GLsizei buf_سائز, GLsizei *لمبائی, GLchar *infoLog);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETPROGRAMPIPELINEIVEXTPROC) (GLuint pipeline, GLenum pname, GLint *params);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLISPROGRAMPIPELINEEXTPROC) (GLuint pipeline);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMPARAMETERIEXTPROC) (GLuint پروگرام, GLenum pname, GLint قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM1FEXTPROC) (GLuint پروگرام, GLint location, GLfloat v0);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM1FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM1IEXTPROC) (GLuint پروگرام, GLint location, GLint v0);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM1IVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM2FEXTPROC) (GLuint پروگرام, GLint location, GLfloat v0, GLfloat v1);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM2FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM2IEXTPROC) (GLuint پروگرام, GLint location, GLint v0, GLint v1);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM2IVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM3FEXTPROC) (GLuint پروگرام, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM3FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM3IEXTPROC) (GLuint پروگرام, GLint location, GLint v0, GLint v1, GLint v2);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM3IVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM4FEXTPROC) (GLuint پروگرام, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM4FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM4IEXTPROC) (GLuint پروگرام, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM4IVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLUSEPROGRAMSTAGESEXTPROC) (GLuint pipeline, GLbitfield stages, GLuint پروگرام);
قسمتعریف خالی (GL_APIENTRYP PFNGLVALIDATEPROGRAMPIPELINEEXTPROC) (GLuint pipeline);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UIEXTPROC) (GLuint پروگرام, GLint location, GLuint v0);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UIEXTPROC) (GLuint پروگرام, GLint location, GLuint v0, GLuint v1);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UIEXTPROC) (GLuint پروگرام, GLint location, GLuint v0, GLuint v1, GLuint v2);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UIEXTPROC) (GLuint پروگرام, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UIVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UIVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UIVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UIVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_فعال_Shader_پروگرام_EXT (GLuint pipeline, GLuint پروگرام);
GL_APICALL خالی GL_APIENTRY gl_Bind_پروگرام_Pipeline_EXT (GLuint pipeline);
GL_APICALL GLuint GL_APIENTRY glCreateShaderProgramvEXT (GLenum type, GLsizei گنتی, ثابت GLchar *ثابت*لڑیاں);
GL_APICALL خالی GL_APIENTRY gl_Delete_پروگرام_Pipelines_EXT (GLsizei n, ثابت GLuint *pipelines);
GL_APICALL خالی GL_APIENTRY gl_Gen_پروگرام_Pipelines_EXT (GLsizei n, GLuint *pipelines);
GL_APICALL خالی GL_APIENTRY gl_Get_پروگرام_Pipeline_Info_Log_EXT (GLuint pipeline, GLsizei buf_سائز, GLsizei *لمبائی, GLchar *infoLog);
GL_APICALL خالی GL_APIENTRY gl_Get_پروگرام_Pipelineiv_EXT (GLuint pipeline, GLenum pname, GLint *params);
GL_APICALL GLboolean GL_APIENTRY gl_Is_پروگرام_Pipeline_EXT (GLuint pipeline);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Parameteri_EXT (GLuint پروگرام, GLenum pname, GLint قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform1f_EXT (GLuint پروگرام, GLint location, GLfloat v0);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform1fv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform1i_EXT (GLuint پروگرام, GLint location, GLint v0);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform1iv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform2f_EXT (GLuint پروگرام, GLint location, GLfloat v0, GLfloat v1);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform2fv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform2i_EXT (GLuint پروگرام, GLint location, GLint v0, GLint v1);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform2iv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform3f_EXT (GLuint پروگرام, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform3fv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform3i_EXT (GLuint پروگرام, GLint location, GLint v0, GLint v1, GLint v2);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform3iv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform4f_EXT (GLuint پروگرام, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform4fv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform4i_EXT (GLuint پروگرام, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform4iv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_یکساں_Matrix2fv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_یکساں_Matrix3fv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_یکساں_Matrix4fv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_Use_پروگرام_Stages_EXT (GLuint pipeline, GLbitfield stages, GLuint پروگرام);
GL_APICALL خالی GL_APIENTRY gl_Validate_پروگرام_Pipeline_EXT (GLuint pipeline);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform1ui_EXT (GLuint پروگرام, GLint location, GLuint v0);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform2ui_EXT (GLuint پروگرام, GLint location, GLuint v0, GLuint v1);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform3ui_EXT (GLuint پروگرام, GLint location, GLuint v0, GLuint v1, GLuint v2);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform4ui_EXT (GLuint پروگرام, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform1uiv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform2uiv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform3uiv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform4uiv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_یکساں_Matrix2x3fv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_یکساں_Matrix3x2fv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_یکساں_Matrix2x4fv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_یکساں_Matrix4x2fv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_یکساں_Matrix3x4fv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_یکساں_Matrix4x3fv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
#اگر_ختم
#اگر_ختم /* GL_EXT_separate_shader_objects */

#اگر_غیر_تعریف_شدہ GL_EXT_shader_framebuffer_fetch
#تعریف_کرو GL_EXT_shader_framebuffer_fetch 1
#تعریف_کرو GL_FRAGMENT_SHADER_DISCARDS_SAMPLES_EXT 0x8A52
#اگر_ختم /* GL_EXT_shader_framebuffer_fetch */

#اگر_غیر_تعریف_شدہ GL_EXT_shader_framebuffer_fetch_non_coherent
#تعریف_کرو GL_EXT_shader_framebuffer_fetch_non_coherent 1
قسمتعریف خالی (GL_APIENTRYP PFNGLFRAMEBUFFERFETCHBARRIEREXTPROC) (خالی);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glFramebufferFetchBarrierEXT (خالی);
#اگر_ختم
#اگر_ختم /* GL_EXT_shader_framebuffer_fetch_non_coherent */

#اگر_غیر_تعریف_شدہ GL_EXT_shader_گروہ_vote
#تعریف_کرو GL_EXT_shader_گروہ_vote 1
#اگر_ختم /* GL_EXT_shader_group_vote */

#اگر_غیر_تعریف_شدہ GL_EXT_shader_implicit_conversions
#تعریف_کرو GL_EXT_shader_implicit_conversions 1
#اگر_ختم /* GL_EXT_shader_implicit_conversions */

#اگر_غیر_تعریف_شدہ GL_EXT_shader_integer_mix
#تعریف_کرو GL_EXT_shader_integer_mix 1
#اگر_ختم /* GL_EXT_shader_integer_mix */

#اگر_غیر_تعریف_شدہ GL_EXT_shader_io_بلاکیں
#تعریف_کرو GL_EXT_shader_io_بلاکیں 1
#اگر_ختم /* GL_EXT_shader_io_blocks */

#اگر_غیر_تعریف_شدہ GL_EXT_shader_non_constant_global_initializers
#تعریف_کرو GL_EXT_shader_non_constant_global_initializers 1
#اگر_ختم /* GL_EXT_shader_non_constant_global_initializers */

#اگر_غیر_تعریف_شدہ GL_EXT_shader_pixel_local_storage
#تعریف_کرو GL_EXT_shader_pixel_local_storage 1
#تعریف_کرو GL_MAX_SHADER_PIXEL_LOCAL_STORAGE_FAST_سائز_EXT 0x8F63
#تعریف_کرو GL_MAX_SHADER_PIXEL_LOCAL_STORAGE_سائز_EXT 0x8F67
#تعریف_کرو GL_SHADER_PIXEL_LOCAL_STORAGE_EXT 0x8F64
#اگر_ختم /* GL_EXT_shader_pixel_local_storage */

#اگر_غیر_تعریف_شدہ GL_EXT_shader_pixel_local_storage2
#تعریف_کرو GL_EXT_shader_pixel_local_storage2 1
#تعریف_کرو GL_MAX_SHADER_COMBINED_LOCAL_STORAGE_FAST_سائز_EXT 0x9650
#تعریف_کرو GL_MAX_SHADER_COMBINED_LOCAL_STORAGE_سائز_EXT 0x9651
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_INSUFFICIENT_SHADER_COMBINED_LOCAL_STORAGE_EXT 0x9652
قسمتعریف خالی (GL_APIENTRYP PFNGLFRAMEBUFFERPIXELLOCALSTORAGESIZEEXTPROC) (GLuint ہدف, GLsizei سائز);
قسمتعریف GLsizei (GL_APIENTRYP PFNGLGETFRAMEBUFFERPIXELLOCALSTORAGESIZEEXTPROC) (GLuint ہدف);
قسمتعریف خالی (GL_APIENTRYP PFNGLCLEARPIXELLOCALSTORAGEUIEXTPROC) (GLsizei انحراف_2, GLsizei n, ثابت GLuint *اقدار);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_Framebuffer_Pixel_Local_Storage_سائز_EXT (GLuint ہدف, GLsizei سائز);
GL_APICALL GLsizei GL_APIENTRY gl_Get_Framebuffer_Pixel_Local_Storage_سائز_EXT (GLuint ہدف);
GL_APICALL خالی GL_APIENTRY glClearPixelLocalStorageuiEXT (GLsizei انحراف_2, GLsizei n, ثابت GLuint *اقدار);
#اگر_ختم
#اگر_ختم /* GL_EXT_shader_pixel_local_storage2 */

#اگر_غیر_تعریف_شدہ GL_EXT_shader_samples_identical
#تعریف_کرو GL_EXT_shader_samples_identical 1
#اگر_ختم /* GL_EXT_shader_samples_identical */

#اگر_غیر_تعریف_شدہ GL_EXT_shader_texture_lod
#تعریف_کرو GL_EXT_shader_texture_lod 1
#اگر_ختم /* GL_EXT_shader_texture_lod */

#اگر_غیر_تعریف_شدہ GL_EXT_shader_texture_samples
#تعریف_کرو GL_EXT_shader_texture_samples 1
#اگر_ختم /* GL_EXT_shader_texture_samples */

#اگر_غیر_تعریف_شدہ GL_EXT_shadow_samplers
#تعریف_کرو GL_EXT_shadow_samplers 1
#تعریف_کرو GL_TEXTURE_COMPARE_منوال_EXT       0x884C
#تعریف_کرو GL_TEXTURE_COMPARE_FUNC_EXT       0x884D
#تعریف_کرو GL_COMPARE_REF_مقصد_TEXTURE_EXT     0x884E
#تعریف_کرو GL_SAMPLER_2D_SHADOW_EXT          0x8B62
#اگر_ختم /* GL_EXT_shadow_samplers */

#اگر_غیر_تعریف_شدہ GL_EXT_sparse_texture
#تعریف_کرو GL_EXT_sparse_texture 1
#تعریف_کرو GL_TEXTURE_SPARSE_EXT             0x91A6
#تعریف_کرو GL_VIRTUAL_صفحہ_سائز_اشاریہ_EXT    0x91A7
#تعریف_کرو GL_عدد_SPARSE_سطحیں_EXT          0x91AA
#تعریف_کرو GL_عدد_VIRTUAL_صفحہ_SIZES_EXT     0x91A8
#تعریف_کرو GL_VIRTUAL_صفحہ_سائز_X_EXT        0x9195
#تعریف_کرو GL_VIRTUAL_صفحہ_سائز_Y_EXT        0x9196
#تعریف_کرو GL_VIRTUAL_صفحہ_سائز_Z_EXT        0x9197
#تعریف_کرو GL_TEXTURE_2D_ARRAY               0x8C1A
#تعریف_کرو GL_TEXTURE_3D                     0x806F
#تعریف_کرو GL_MAX_SPARSE_TEXTURE_سائز_EXT    0x9198
#تعریف_کرو GL_MAX_SPARSE_3_D_TEXTURE_سائز_EXT 0x9199
#تعریف_کرو GL_MAX_SPARSE_ARRAY_TEXTURE_LAYERS_EXT 0x919A
#تعریف_کرو GL_SPARSE_TEXTURE_بھرا_ARRAY_CUBE_MIPMAPS_EXT 0x91A9
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXPAGECOMMITMENTEXTPROC) (GLenum ہدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLboolean commit);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_Tex_صفحہ_Commitment_EXT (GLenum ہدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLboolean commit);
#اگر_ختم
#اگر_ختم /* GL_EXT_sparse_texture */

#اگر_غیر_تعریف_شدہ GL_EXT_sparse_texture2
#تعریف_کرو GL_EXT_sparse_texture2 1
#اگر_ختم /* GL_EXT_sparse_texture2 */

#اگر_غیر_تعریف_شدہ GL_EXT_tessellation_نقطہ_سائز
#تعریف_کرو GL_EXT_tessellation_نقطہ_سائز 1
#اگر_ختم /* GL_EXT_tessellation_point_size */

#اگر_غیر_تعریف_شدہ GL_EXT_tessellation_shader
#تعریف_کرو GL_EXT_tessellation_shader 1
#تعریف_کرو GL_PATCHES_EXT                    0x000E
#تعریف_کرو GL_PATCH_VERTICES_EXT             0x8E72
#تعریف_کرو GL_TESS_CONTROL_OUTPUT_VERTICES_EXT 0x8E75
#تعریف_کرو GL_TESS_GEN_منوال_EXT              0x8E76
#تعریف_کرو GL_TESS_GEN_SPACING_EXT           0x8E77
#تعریف_کرو GL_TESS_GEN_راس_ترتیب_EXT      0x8E78
#تعریف_کرو GL_TESS_GEN_نقطہ_منوال_EXT        0x8E79
#تعریف_کرو GL_ISOLINES_EXT                   0x8E7A
#تعریف_کرو GL_QUADS_EXT                      0x0007
#تعریف_کرو GL_FRACTIONAL_ODD_EXT             0x8E7B
#تعریف_کرو GL_FRACTIONAL_EVEN_EXT            0x8E7C
#تعریف_کرو GL_MAX_PATCH_VERTICES_EXT         0x8E7D
#تعریف_کرو GL_MAX_TESS_GEN_LEVEL_EXT         0x8E7E
#تعریف_کرو GL_MAX_TESS_CONTROL_یکساں_COMPONENTS_EXT 0x8E7F
#تعریف_کرو GL_MAX_TESS_EVALUATION_یکساں_COMPONENTS_EXT 0x8E80
#تعریف_کرو GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS_EXT 0x8E81
#تعریف_کرو GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS_EXT 0x8E82
#تعریف_کرو GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS_EXT 0x8E83
#تعریف_کرو GL_MAX_TESS_PATCH_COMPONENTS_EXT  0x8E84
#تعریف_کرو GL_MAX_TESS_CONTROL_کل_OUTPUT_COMPONENTS_EXT 0x8E85
#تعریف_کرو GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS_EXT 0x8E86
#تعریف_کرو GL_MAX_TESS_CONTROL_یکساں_بلاکیں_EXT 0x8E89
#تعریف_کرو GL_MAX_TESS_EVALUATION_یکساں_بلاکیں_EXT 0x8E8A
#تعریف_کرو GL_MAX_TESS_CONTROL_داخلہ_COMPONENTS_EXT 0x886C
#تعریف_کرو GL_MAX_TESS_EVALUATION_داخلہ_COMPONENTS_EXT 0x886D
#تعریف_کرو GL_MAX_COMBINED_TESS_CONTROL_یکساں_COMPONENTS_EXT 0x8E1E
#تعریف_کرو GL_MAX_COMBINED_TESS_EVALUATION_یکساں_COMPONENTS_EXT 0x8E1F
#تعریف_کرو GL_MAX_TESS_CONTROL_ATOMIC_شمار_BUFFERS_EXT 0x92CD
#تعریف_کرو GL_MAX_TESS_EVALUATION_ATOMIC_شمار_BUFFERS_EXT 0x92CE
#تعریف_کرو GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS_EXT 0x92D3
#تعریف_کرو GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS_EXT 0x92D4
#تعریف_کرو GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS_EXT 0x90CB
#تعریف_کرو GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS_EXT 0x90CC
#تعریف_کرو GL_MAX_TESS_CONTROL_SHADER_STORAGE_بلاکیں_EXT 0x90D8
#تعریف_کرو GL_MAX_TESS_EVALUATION_SHADER_STORAGE_بلاکیں_EXT 0x90D9
#تعریف_کرو GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED 0x8221
#تعریف_کرو GL_IS_فی_PATCH_EXT               0x92E7
#تعریف_کرو GL_REFERENCED_BY_TESS_CONTROL_SHADER_EXT 0x9307
#تعریف_کرو GL_REFERENCED_BY_TESS_EVALUATION_SHADER_EXT 0x9308
#تعریف_کرو GL_TESS_CONTROL_SHADER_EXT        0x8E88
#تعریف_کرو GL_TESS_EVALUATION_SHADER_EXT     0x8E87
#تعریف_کرو GL_TESS_CONTROL_SHADER_ثنائی_ہندسہ_EXT    0x00000008
#تعریف_کرو GL_TESS_EVALUATION_SHADER_ثنائی_ہندسہ_EXT 0x00000010
قسمتعریف خالی (GL_APIENTRYP PFNGLPATCHPARAMETERIEXTPROC) (GLenum pname, GLint قدر);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glPatchParameteriEXT (GLenum pname, GLint قدر);
#اگر_ختم
#اگر_ختم /* GL_EXT_tessellation_shader */

#اگر_غیر_تعریف_شدہ GL_EXT_texture_border_clamp
#تعریف_کرو GL_EXT_texture_border_clamp 1
#تعریف_کرو GL_TEXTURE_BORDER_COLOR_EXT       0x1004
#تعریف_کرو GL_CLAMP_مقصد_BORDER_EXT            0x812D
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXPARAMETERIIVEXTPROC) (GLenum ہدف, GLenum pname, ثابت GLint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXPARAMETERIUIVEXTPROC) (GLenum ہدف, GLenum pname, ثابت GLuint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETTEXPARAMETERIIVEXTPROC) (GLenum ہدف, GLenum pname, GLint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETTEXPARAMETERIUIVEXTPROC) (GLenum ہدف, GLenum pname, GLuint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLSAMPLERPARAMETERIIVEXTPROC) (GLuint sampler, GLenum pname, ثابت GLint *param);
قسمتعریف خالی (GL_APIENTRYP PFNGLSAMPLERPARAMETERIUIVEXTPROC) (GLuint sampler, GLenum pname, ثابت GLuint *param);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIIVEXTPROC) (GLuint sampler, GLenum pname, GLint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIUIVEXTPROC) (GLuint sampler, GLenum pname, GLuint *params);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glTexParameterIivEXT (GLenum ہدف, GLenum pname, ثابت GLint *params);
GL_APICALL خالی GL_APIENTRY glTexParameterIuivEXT (GLenum ہدف, GLenum pname, ثابت GLuint *params);
GL_APICALL خالی GL_APIENTRY glGetTexParameterIivEXT (GLenum ہدف, GLenum pname, GLint *params);
GL_APICALL خالی GL_APIENTRY glGetTexParameterIuivEXT (GLenum ہدف, GLenum pname, GLuint *params);
GL_APICALL خالی GL_APIENTRY glSamplerParameterIivEXT (GLuint sampler, GLenum pname, ثابت GLint *param);
GL_APICALL خالی GL_APIENTRY glSamplerParameterIuivEXT (GLuint sampler, GLenum pname, ثابت GLuint *param);
GL_APICALL خالی GL_APIENTRY glGetSamplerParameterIivEXT (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL خالی GL_APIENTRY glGetSamplerParameterIuivEXT (GLuint sampler, GLenum pname, GLuint *params);
#اگر_ختم
#اگر_ختم /* GL_EXT_texture_border_clamp */

#اگر_غیر_تعریف_شدہ GL_EXT_texture_بفر
#تعریف_کرو GL_EXT_texture_بفر 1
#تعریف_کرو GL_TEXTURE_بفر_EXT             0x8C2A
#تعریف_کرو GL_TEXTURE_بفر_BINDING_EXT     0x8C2A
#تعریف_کرو GL_MAX_TEXTURE_بفر_سائز_EXT    0x8C2B
#تعریف_کرو GL_TEXTURE_BINDING_بفر_EXT     0x8C2C
#تعریف_کرو GL_TEXTURE_بفر_ڈیٹا_STORE_BINDING_EXT 0x8C2D
#تعریف_کرو GL_TEXTURE_بفر_انحراف_ALIGNMENT_EXT 0x919F
#تعریف_کرو GL_SAMPLER_بفر_EXT             0x8DC2
#تعریف_کرو GL_INT_SAMPLER_بفر_EXT         0x8DD0
#تعریف_کرو GL_UNSIGNED_INT_SAMPLER_بفر_EXT 0x8DD8
#تعریف_کرو GL_IMAGE_بفر_EXT               0x9051
#تعریف_کرو GL_INT_IMAGE_بفر_EXT           0x905C
#تعریف_کرو GL_UNSIGNED_INT_IMAGE_بفر_EXT  0x9067
#تعریف_کرو GL_TEXTURE_بفر_انحراف_EXT      0x919D
#تعریف_کرو GL_TEXTURE_بفر_سائز_EXT        0x919E
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXBUFFEREXTPROC) (GLenum ہدف, GLenum internalformat, GLuint بفر_2);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXBUFFERRANGEEXTPROC) (GLenum ہدف, GLenum internalformat, GLuint بفر_2, GLintptr انحراف_2, GLsizeiptr سائز);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_Tex_بفر_EXT (GLenum ہدف, GLenum internalformat, GLuint بفر_2);
GL_APICALL خالی GL_APIENTRY gl_Tex_بفر_Range_EXT (GLenum ہدف, GLenum internalformat, GLuint بفر_2, GLintptr انحراف_2, GLsizeiptr سائز);
#اگر_ختم
#اگر_ختم /* GL_EXT_texture_buffer */

#اگر_غیر_تعریف_شدہ GL_EXT_texture_compression_astc_decode_منوال
#تعریف_کرو GL_EXT_texture_compression_astc_decode_منوال 1
#تعریف_کرو GL_TEXTURE_ASTC_DECODE_PRECISION_EXT 0x8F69
#اگر_ختم /* GL_EXT_texture_compression_astc_decode_mode */

#اگر_غیر_تعریف_شدہ GL_EXT_texture_compression_bptc
#تعریف_کرو GL_EXT_texture_compression_bptc 1
#تعریف_کرو GL_COMPRESSED_RGBA_BPTC_UNORM_EXT 0x8E8C
#تعریف_کرو GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_EXT 0x8E8D
#تعریف_کرو GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_EXT 0x8E8E
#تعریف_کرو GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_EXT 0x8E8F
#اگر_ختم /* GL_EXT_texture_compression_bptc */

#اگر_غیر_تعریف_شدہ GL_EXT_texture_compression_dxt1
#تعریف_کرو GL_EXT_texture_compression_dxt1 1
#تعریف_کرو GL_COMPRESSED_RGB_S3TC_DXT1_EXT   0x83F0
#تعریف_کرو GL_COMPRESSED_RGBA_S3TC_DXT1_EXT  0x83F1
#اگر_ختم /* GL_EXT_texture_compression_dxt1 */

#اگر_غیر_تعریف_شدہ GL_EXT_texture_compression_rgtc
#تعریف_کرو GL_EXT_texture_compression_rgtc 1
#تعریف_کرو GL_COMPRESSED_RED_RGTC1_EXT       0x8DBB
#تعریف_کرو GL_COMPRESSED_SIGNED_RED_RGTC1_EXT 0x8DBC
#تعریف_کرو GL_COMPRESSED_RED_GREEN_RGTC2_EXT 0x8DBD
#تعریف_کرو GL_COMPRESSED_SIGNED_RED_GREEN_RGTC2_EXT 0x8DBE
#اگر_ختم /* GL_EXT_texture_compression_rgtc */

#اگر_غیر_تعریف_شدہ GL_EXT_texture_compression_s3tc
#تعریف_کرو GL_EXT_texture_compression_s3tc 1
#تعریف_کرو GL_COMPRESSED_RGBA_S3TC_DXT3_EXT  0x83F2
#تعریف_کرو GL_COMPRESSED_RGBA_S3TC_DXT5_EXT  0x83F3
#اگر_ختم /* GL_EXT_texture_compression_s3tc */

#اگر_غیر_تعریف_شدہ GL_EXT_texture_compression_s3tc_srgb
#تعریف_کرو GL_EXT_texture_compression_s3tc_srgb 1
#تعریف_کرو GL_COMPRESSED_SRGB_S3TC_DXT1_EXT  0x8C4C
#تعریف_کرو GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT 0x8C4D
#تعریف_کرو GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT 0x8C4E
#تعریف_کرو GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT 0x8C4F
#اگر_ختم /* GL_EXT_texture_compression_s3tc_srgb */

#اگر_غیر_تعریف_شدہ GL_EXT_texture_cube_map_array
#تعریف_کرو GL_EXT_texture_cube_map_array 1
#تعریف_کرو GL_TEXTURE_CUBE_MAP_ARRAY_EXT     0x9009
#تعریف_کرو GL_TEXTURE_BINDING_CUBE_MAP_ARRAY_EXT 0x900A
#تعریف_کرو GL_SAMPLER_CUBE_MAP_ARRAY_EXT     0x900C
#تعریف_کرو GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW_EXT 0x900D
#تعریف_کرو GL_INT_SAMPLER_CUBE_MAP_ARRAY_EXT 0x900E
#تعریف_کرو GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY_EXT 0x900F
#تعریف_کرو GL_IMAGE_CUBE_MAP_ARRAY_EXT       0x9054
#تعریف_کرو GL_INT_IMAGE_CUBE_MAP_ARRAY_EXT   0x905F
#تعریف_کرو GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY_EXT 0x906A
#اگر_ختم /* GL_EXT_texture_cube_map_array */

#اگر_غیر_تعریف_شدہ GL_EXT_texture_filter_anisotropic
#تعریف_کرو GL_EXT_texture_filter_anisotropic 1
#تعریف_کرو GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#تعریف_کرو GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#اگر_ختم /* GL_EXT_texture_filter_anisotropic */

#اگر_غیر_تعریف_شدہ GL_EXT_texture_filter_minmax
#تعریف_کرو GL_EXT_texture_filter_minmax 1
#تعریف_کرو GL_TEXTURE_REDUCTION_منوال_EXT     0x9366
#تعریف_کرو GL_WEIGHTED_اوسط_قدر_EXT           0x9367
#اگر_ختم /* GL_EXT_texture_filter_minmax */

#اگر_غیر_تعریف_شدہ GL_EXT_texture_format_BGRA8888
#تعریف_کرو GL_EXT_texture_format_BGRA8888 1
#اگر_ختم /* GL_EXT_texture_format_BGRA8888 */

#اگر_غیر_تعریف_شدہ GL_EXT_texture_format_sRGB_override
#تعریف_کرو GL_EXT_texture_format_sRGB_override 1
#تعریف_کرو GL_TEXTURE_FORMAT_SRGB_OVERRIDE_EXT 0x8FBF
#اگر_ختم /* GL_EXT_texture_format_sRGB_override */

#اگر_غیر_تعریف_شدہ GL_EXT_texture_mirror_clamp_مقصد_کنارہ
#تعریف_کرو GL_EXT_texture_mirror_clamp_مقصد_کنارہ 1
#تعریف_کرو GL_MIRROR_CLAMP_مقصد_کنارہ_EXT       0x8743
#اگر_ختم /* GL_EXT_texture_mirror_clamp_to_edge */

#اگر_غیر_تعریف_شدہ GL_EXT_texture_norm16
#تعریف_کرو GL_EXT_texture_norm16 1
#تعریف_کرو GL_R16_EXT                        0x822A
#تعریف_کرو GL_RG16_EXT                       0x822C
#تعریف_کرو GL_RGBA16_EXT                     0x805B
#تعریف_کرو GL_RGB16_EXT                      0x8054
#تعریف_کرو GL_RGB16_SNORM_EXT                0x8F9A
#اگر_ختم /* GL_EXT_texture_norm16 */

#اگر_غیر_تعریف_شدہ GL_EXT_texture_query_lod
#تعریف_کرو GL_EXT_texture_query_lod 1
#اگر_ختم /* GL_EXT_texture_query_lod */

#اگر_غیر_تعریف_شدہ GL_EXT_texture_rg
#تعریف_کرو GL_EXT_texture_rg 1
#تعریف_کرو GL_RED_EXT                        0x1903
#تعریف_کرو GL_RG_EXT                         0x8227
#تعریف_کرو GL_R8_EXT                         0x8229
#تعریف_کرو GL_RG8_EXT                        0x822B
#اگر_ختم /* GL_EXT_texture_rg */

#اگر_غیر_تعریف_شدہ GL_EXT_texture_sRGB_R8
#تعریف_کرو GL_EXT_texture_sRGB_R8 1
#تعریف_کرو GL_SR8_EXT                        0x8FBD
#اگر_ختم /* GL_EXT_texture_sRGB_R8 */

#اگر_غیر_تعریف_شدہ GL_EXT_texture_sRGB_RG8
#تعریف_کرو GL_EXT_texture_sRGB_RG8 1
#تعریف_کرو GL_SRG8_EXT                       0x8FBE
#اگر_ختم /* GL_EXT_texture_sRGB_RG8 */

#اگر_غیر_تعریف_شدہ GL_EXT_texture_sRGB_decode
#تعریف_کرو GL_EXT_texture_sRGB_decode 1
#تعریف_کرو GL_TEXTURE_SRGB_DECODE_EXT        0x8A48
#تعریف_کرو GL_DECODE_EXT                     0x8A49
#تعریف_کرو GL_SKIP_DECODE_EXT                0x8A4A
#اگر_ختم /* GL_EXT_texture_sRGB_decode */

#اگر_غیر_تعریف_شدہ GL_EXT_texture_shadow_lod
#تعریف_کرو GL_EXT_texture_shadow_lod 1
#اگر_ختم /* GL_EXT_texture_shadow_lod */

#اگر_غیر_تعریف_شدہ GL_EXT_texture_storage
#تعریف_کرو GL_EXT_texture_storage 1
#تعریف_کرو GL_TEXTURE_IMMUTABLE_FORMAT_EXT   0x912F
#تعریف_کرو GL_ALPHA8_EXT                     0x803C
#تعریف_کرو GL_LUMINANCE8_EXT                 0x8040
#تعریف_کرو GL_LUMINANCE8_ALPHA8_EXT          0x8045
#تعریف_کرو GL_RGBA32F_EXT                    0x8814
#تعریف_کرو GL_RGB32F_EXT                     0x8815
#تعریف_کرو GL_ALPHA32F_EXT                   0x8816
#تعریف_کرو GL_LUMINANCE32F_EXT               0x8818
#تعریف_کرو GL_LUMINANCE_ALPHA32F_EXT         0x8819
#تعریف_کرو GL_ALPHA16F_EXT                   0x881C
#تعریف_کرو GL_LUMINANCE16F_EXT               0x881E
#تعریف_کرو GL_LUMINANCE_ALPHA16F_EXT         0x881F
#تعریف_کرو GL_R32F_EXT                       0x822E
#تعریف_کرو GL_RG32F_EXT                      0x8230
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXSTORAGE1DEXTPROC) (GLenum ہدف, GLsizei سطحیں, GLenum internalformat, GLsizei چوڑائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXSTORAGE2DEXTPROC) (GLenum ہدف, GLsizei سطحیں, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXSTORAGE3DEXTPROC) (GLenum ہدف, GLsizei سطحیں, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXTURESTORAGE1DEXTPROC) (GLuint texture, GLenum ہدف, GLsizei سطحیں, GLenum internalformat, GLsizei چوڑائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXTURESTORAGE2DEXTPROC) (GLuint texture, GLenum ہدف, GLsizei سطحیں, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXTURESTORAGE3DEXTPROC) (GLuint texture, GLenum ہدف, GLsizei سطحیں, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glTexStorage1DEXT (GLenum ہدف, GLsizei سطحیں, GLenum internalformat, GLsizei چوڑائی);
GL_APICALL خالی GL_APIENTRY glTexStorage2DEXT (GLenum ہدف, GLsizei سطحیں, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
GL_APICALL خالی GL_APIENTRY glTexStorage3DEXT (GLenum ہدف, GLsizei سطحیں, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2);
GL_APICALL خالی GL_APIENTRY glTextureStorage1DEXT (GLuint texture, GLenum ہدف, GLsizei سطحیں, GLenum internalformat, GLsizei چوڑائی);
GL_APICALL خالی GL_APIENTRY glTextureStorage2DEXT (GLuint texture, GLenum ہدف, GLsizei سطحیں, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
GL_APICALL خالی GL_APIENTRY glTextureStorage3DEXT (GLuint texture, GLenum ہدف, GLsizei سطحیں, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2);
#اگر_ختم
#اگر_ختم /* GL_EXT_texture_storage */

#اگر_غیر_تعریف_شدہ GL_EXT_texture_storage_compression
#تعریف_کرو GL_EXT_texture_storage_compression 1
#تعریف_کرو GL_عدد_SURFACE_COMPRESSION_FIXED_RATES_EXT 0x8F6E
#تعریف_کرو GL_SURFACE_COMPRESSION_FIXED_شرح_1_BPC_EXT 0x96C4
#تعریف_کرو GL_SURFACE_COMPRESSION_FIXED_شرح_2_BPC_EXT 0x96C5
#تعریف_کرو GL_SURFACE_COMPRESSION_FIXED_شرح_3_BPC_EXT 0x96C6
#تعریف_کرو GL_SURFACE_COMPRESSION_FIXED_شرح_4_BPC_EXT 0x96C7
#تعریف_کرو GL_SURFACE_COMPRESSION_FIXED_شرح_5_BPC_EXT 0x96C8
#تعریف_کرو GL_SURFACE_COMPRESSION_FIXED_شرح_6_BPC_EXT 0x96C9
#تعریف_کرو GL_SURFACE_COMPRESSION_FIXED_شرح_7_BPC_EXT 0x96CA
#تعریف_کرو GL_SURFACE_COMPRESSION_FIXED_شرح_8_BPC_EXT 0x96CB
#تعریف_کرو GL_SURFACE_COMPRESSION_FIXED_شرح_9_BPC_EXT 0x96CC
#تعریف_کرو GL_SURFACE_COMPRESSION_FIXED_شرح_10_BPC_EXT 0x96CD
#تعریف_کرو GL_SURFACE_COMPRESSION_FIXED_شرح_11_BPC_EXT 0x96CE
#تعریف_کرو GL_SURFACE_COMPRESSION_FIXED_شرح_12_BPC_EXT 0x96CF
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXSTORAGEATTRIBS2DEXTPROC) (GLenum ہدف, GLsizei سطحیں, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی, ثابت GLint* attrib_list);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXSTORAGEATTRIBS3DEXTPROC) (GLenum ہدف, GLsizei سطحیں, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, ثابت GLint* attrib_list);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glTexStorageAttribs2DEXT (GLenum ہدف, GLsizei سطحیں, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی, ثابت GLint* attrib_list);
GL_APICALL خالی GL_APIENTRY glTexStorageAttribs3DEXT (GLenum ہدف, GLsizei سطحیں, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, ثابت GLint* attrib_list);
#اگر_ختم
#اگر_ختم /* GL_EXT_texture_storage_compression */

#اگر_غیر_تعریف_شدہ GL_EXT_texture_type_2_10_10_10_REV
#تعریف_کرو GL_EXT_texture_type_2_10_10_10_REV 1
#تعریف_کرو GL_UNSIGNED_INT_2_10_10_10_REV_EXT 0x8368
#اگر_ختم /* GL_EXT_texture_type_2_10_10_10_REV */

#اگر_غیر_تعریف_شدہ GL_EXT_texture_view
#تعریف_کرو GL_EXT_texture_view 1
#تعریف_کرو GL_TEXTURE_VIEW_MIN_LEVEL_EXT     0x82DB
#تعریف_کرو GL_TEXTURE_VIEW_عدد_سطحیں_EXT    0x82DC
#تعریف_کرو GL_TEXTURE_VIEW_MIN_LAYER_EXT     0x82DD
#تعریف_کرو GL_TEXTURE_VIEW_عدد_LAYERS_EXT    0x82DE
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXTUREVIEWEXTPROC) (GLuint texture, GLenum ہدف, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glTextureViewEXT (GLuint texture, GLenum ہدف, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
#اگر_ختم
#اگر_ختم /* GL_EXT_texture_view */

#اگر_غیر_تعریف_شدہ GL_EXT_unpack_subimage
#تعریف_کرو GL_EXT_unpack_subimage 1
#تعریف_کرو GL_UNPACK_صف_لمبائی_EXT          0x0CF2
#تعریف_کرو GL_UNPACK_SKIP_صفیں_EXT           0x0CF3
#تعریف_کرو GL_UNPACK_SKIP_PIXELS_EXT         0x0CF4
#اگر_ختم /* GL_EXT_unpack_subimage */

#اگر_غیر_تعریف_شدہ GL_EXT_win32_keyed_mutex
#تعریف_کرو GL_EXT_win32_keyed_mutex 1
قسمتعریف GLboolean (GL_APIENTRYP PFNGLACQUIREKEYEDMUTEXWIN32EXTPROC) (GLuint حافظہ, GLuint64 کلید, GLuint timeout);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLRELEASEKEYEDMUTEXWIN32EXTPROC) (GLuint حافظہ, GLuint64 کلید);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL GLboolean GL_APIENTRY glAcquireKeyedMutexWin32EXT (GLuint حافظہ, GLuint64 کلید, GLuint timeout);
GL_APICALL GLboolean GL_APIENTRY glReleaseKeyedMutexWin32EXT (GLuint حافظہ, GLuint64 کلید);
#اگر_ختم
#اگر_ختم /* GL_EXT_win32_keyed_mutex */

#اگر_غیر_تعریف_شدہ GL_EXT_کھڑکی_rectangles
#تعریف_کرو GL_EXT_کھڑکی_rectangles 1
#تعریف_کرو GL_INCLUSIVE_EXT                  0x8F10
#تعریف_کرو GL_EXCLUSIVE_EXT                  0x8F11
#تعریف_کرو GL_کھڑکی_RECTANGLE_EXT           0x8F12
#تعریف_کرو GL_کھڑکی_RECTANGLE_منوال_EXT      0x8F13
#تعریف_کرو GL_MAX_کھڑکی_RECTANGLES_EXT      0x8F14
#تعریف_کرو GL_عدد_کھڑکی_RECTANGLES_EXT      0x8F15
قسمتعریف خالی (GL_APIENTRYP PFNGLWINDOWRECTANGLESEXTPROC) (GLenum منوال, GLsizei گنتی, ثابت GLint *box);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_کھڑکی_Rectangles_EXT (GLenum منوال, GLsizei گنتی, ثابت GLint *box);
#اگر_ختم
#اگر_ختم /* GL_EXT_window_rectangles */

#اگر_غیر_تعریف_شدہ GL_FJ_shader_ثنائی_GCCSO
#تعریف_کرو GL_FJ_shader_ثنائی_GCCSO 1
#تعریف_کرو GL_GCCSO_SHADER_ثنائی_FJ         0x9260
#اگر_ختم /* GL_FJ_shader_binary_GCCSO */

#اگر_غیر_تعریف_شدہ GL_HUAWEI_پروگرام_ثنائی
#تعریف_کرو GL_HUAWEI_پروگرام_ثنائی 1
#تعریف_کرو GL_پروگرام_ثنائی_HUAWEI          0x9771
#اگر_ختم /* GL_HUAWEI_program_binary */

#اگر_غیر_تعریف_شدہ GL_HUAWEI_shader_ثنائی
#تعریف_کرو GL_HUAWEI_shader_ثنائی 1
#تعریف_کرو GL_SHADER_ثنائی_HUAWEI           0x9770
#اگر_ختم /* GL_HUAWEI_shader_binary */

#اگر_غیر_تعریف_شدہ GL_IMG_bindless_texture
#تعریف_کرو GL_IMG_bindless_texture 1
قسمتعریف GLuint64 (GL_APIENTRYP PFNGLGETTEXTUREHANDLEIMGPROC) (GLuint texture);
قسمتعریف GLuint64 (GL_APIENTRYP PFNGLGETTEXTURESAMPLERHANDLEIMGPROC) (GLuint texture, GLuint sampler);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORMHANDLEUI64IMGPROC) (GLint location, GLuint64 قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORMHANDLEUI64VIMGPROC) (GLint location, GLsizei گنتی, ثابت GLuint64 *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64IMGPROC) (GLuint پروگرام, GLint location, GLuint64 قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64VIMGPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint64 *اقدار);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL GLuint64 GL_APIENTRY glGetTextureHandleIMG (GLuint texture);
GL_APICALL GLuint64 GL_APIENTRY glGetTextureSamplerHandleIMG (GLuint texture, GLuint sampler);
GL_APICALL خالی GL_APIENTRY gl_یکساں_Handleui64_IMG (GLint location, GLuint64 قدر);
GL_APICALL خالی GL_APIENTRY gl_یکساں_Handleui64v_IMG (GLint location, GLsizei گنتی, ثابت GLuint64 *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_یکساں_Handleui64_IMG (GLuint پروگرام, GLint location, GLuint64 قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_یکساں_Handleui64v_IMG (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint64 *اقدار);
#اگر_ختم
#اگر_ختم /* GL_IMG_bindless_texture */

#اگر_غیر_تعریف_شدہ GL_IMG_framebuffer_downsample
#تعریف_کرو GL_IMG_framebuffer_downsample 1
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_AND_DOWNSAMPLE_IMG 0x913C
#تعریف_کرو GL_عدد_DOWNSAMPLE_SCALES_IMG      0x913D
#تعریف_کرو GL_DOWNSAMPLE_SCALES_IMG          0x913E
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SCALE_IMG 0x913F
قسمتعریف خالی (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DDOWNSAMPLEIMGPROC) (GLenum ہدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint xscale, GLint yscale);
قسمتعریف خالی (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURELAYERDOWNSAMPLEIMGPROC) (GLenum ہدف, GLenum attachment, GLuint texture, GLint level, GLint layer, GLint xscale, GLint yscale);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glFramebufferTexture2DDownsampleIMG (GLenum ہدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint xscale, GLint yscale);
GL_APICALL خالی GL_APIENTRY glFramebufferTextureLayerDownsampleIMG (GLenum ہدف, GLenum attachment, GLuint texture, GLint level, GLint layer, GLint xscale, GLint yscale);
#اگر_ختم
#اگر_ختم /* GL_IMG_framebuffer_downsample */

#اگر_غیر_تعریف_شدہ GL_IMG_multisampled_render_مقصد_texture
#تعریف_کرو GL_IMG_multisampled_render_مقصد_texture 1
#تعریف_کرو GL_RENDERBUFFER_SAMPLES_IMG       0x9133
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_IMG 0x9134
#تعریف_کرو GL_MAX_SAMPLES_IMG                0x9135
#تعریف_کرو GL_TEXTURE_SAMPLES_IMG            0x9136
قسمتعریف خالی (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEIMGPROC) (GLenum ہدف, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEIMGPROC) (GLenum ہدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glRenderbufferStorageMultisampleIMG (GLenum ہدف, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
GL_APICALL خالی GL_APIENTRY glFramebufferTexture2DMultisampleIMG (GLenum ہدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#اگر_ختم
#اگر_ختم /* GL_IMG_multisampled_render_to_texture */

#اگر_غیر_تعریف_شدہ GL_IMG_پروگرام_ثنائی
#تعریف_کرو GL_IMG_پروگرام_ثنائی 1
#تعریف_کرو GL_SGX_پروگرام_ثنائی_IMG         0x9130
#اگر_ختم /* GL_IMG_program_binary */

#اگر_غیر_تعریف_شدہ GL_IMG_read_format
#تعریف_کرو GL_IMG_read_format 1
#تعریف_کرو GL_BGRA_IMG                       0x80E1
#تعریف_کرو GL_UNSIGNED_SHORT_4_4_4_4_REV_IMG 0x8365
#اگر_ختم /* GL_IMG_read_format */

#اگر_غیر_تعریف_شدہ GL_IMG_shader_ثنائی
#تعریف_کرو GL_IMG_shader_ثنائی 1
#تعریف_کرو GL_SGX_ثنائی_IMG                 0x8C0A
#اگر_ختم /* GL_IMG_shader_binary */

#اگر_غیر_تعریف_شدہ GL_IMG_texture_compression_pvrtc
#تعریف_کرو GL_IMG_texture_compression_pvrtc 1
#تعریف_کرو GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG 0x8C00
#تعریف_کرو GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG 0x8C01
#تعریف_کرو GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG 0x8C02
#تعریف_کرو GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG 0x8C03
#اگر_ختم /* GL_IMG_texture_compression_pvrtc */

#اگر_غیر_تعریف_شدہ GL_IMG_texture_compression_pvrtc2
#تعریف_کرو GL_IMG_texture_compression_pvrtc2 1
#تعریف_کرو GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG 0x9137
#تعریف_کرو GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG 0x9138
#اگر_ختم /* GL_IMG_texture_compression_pvrtc2 */

#اگر_غیر_تعریف_شدہ GL_IMG_texture_filter_cubic
#تعریف_کرو GL_IMG_texture_filter_cubic 1
#تعریف_کرو GL_CUBIC_IMG                      0x9139
#تعریف_کرو GL_CUBIC_MIPMAP_قریب_ترین_IMG       0x913A
#تعریف_کرو GL_CUBIC_MIPMAP_خطی_IMG        0x913B
#اگر_ختم /* GL_IMG_texture_filter_cubic */

#اگر_غیر_تعریف_شدہ GL_INTEL_blackhole_render
#تعریف_کرو GL_INTEL_blackhole_render 1
#تعریف_کرو GL_BLACKHOLE_RENDER_INTEL         0x83FC
#اگر_ختم /* GL_INTEL_blackhole_render */

#اگر_غیر_تعریف_شدہ GL_INTEL_conservative_rasterization
#تعریف_کرو GL_INTEL_conservative_rasterization 1
#تعریف_کرو GL_CONSERVATIVE_RASTERIZATION_INTEL 0x83FE
#اگر_ختم /* GL_INTEL_conservative_rasterization */

#اگر_غیر_تعریف_شدہ GL_INTEL_framebuffer_CMAA
#تعریف_کرو GL_INTEL_framebuffer_CMAA 1
قسمتعریف خالی (GL_APIENTRYP PFNGLAPPLYFRAMEBUFFERATTACHMENTCMAAINTELPROC) (خالی);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glApplyFramebufferAttachmentCMAAINTEL (خالی);
#اگر_ختم
#اگر_ختم /* GL_INTEL_framebuffer_CMAA */

#اگر_غیر_تعریف_شدہ GL_INTEL_performance_query
#تعریف_کرو GL_INTEL_performance_query 1
#تعریف_کرو GL_PERFQUERY_SINGLE_CONTEXT_INTEL 0x00000000
#تعریف_کرو GL_PERFQUERY_GLOBAL_CONTEXT_INTEL 0x00000001
#تعریف_کرو GL_PERFQUERY_WAIT_INTEL           0x83FB
#تعریف_کرو GL_PERFQUERY_FLUSH_INTEL          0x83FA
#تعریف_کرو GL_PERFQUERY_DONOT_FLUSH_INTEL    0x83F9
#تعریف_کرو GL_PERFQUERY_شمار_EVENT_INTEL  0x94F0
#تعریف_کرو GL_PERFQUERY_شمار_DURATION_NORM_INTEL 0x94F1
#تعریف_کرو GL_PERFQUERY_شمار_DURATION_RAW_INTEL 0x94F2
#تعریف_کرو GL_PERFQUERY_شمار_THROUGHPUT_INTEL 0x94F3
#تعریف_کرو GL_PERFQUERY_شمار_RAW_INTEL    0x94F4
#تعریف_کرو GL_PERFQUERY_شمار_TIMESTAMP_INTEL 0x94F5
#تعریف_کرو GL_PERFQUERY_شمار_ڈیٹا_UINT32_INTEL 0x94F8
#تعریف_کرو GL_PERFQUERY_شمار_ڈیٹا_UINT64_INTEL 0x94F9
#تعریف_کرو GL_PERFQUERY_شمار_ڈیٹا_FLOAT_INTEL 0x94FA
#تعریف_کرو GL_PERFQUERY_شمار_ڈیٹا_DOUBLE_INTEL 0x94FB
#تعریف_کرو GL_PERFQUERY_شمار_ڈیٹا_BOOL32_INTEL 0x94FC
#تعریف_کرو GL_PERFQUERY_QUERY_NAME_لمبائی_MAX_INTEL 0x94FD
#تعریف_کرو GL_PERFQUERY_شمار_NAME_لمبائی_MAX_INTEL 0x94FE
#تعریف_کرو GL_PERFQUERY_شمار_DESC_لمبائی_MAX_INTEL 0x94FF
#تعریف_کرو GL_PERFQUERY_GPA_EXTENDED_COUNTERS_INTEL 0x9500
قسمتعریف خالی (GL_APIENTRYP PFNGLBEGINPERFQUERYINTELPROC) (GLuint queryHandle);
قسمتعریف خالی (GL_APIENTRYP PFNGLCREATEPERFQUERYINTELPROC) (GLuint queryId, GLuint *queryHandle);
قسمتعریف خالی (GL_APIENTRYP PFNGLDELETEPERFQUERYINTELPROC) (GLuint queryHandle);
قسمتعریف خالی (GL_APIENTRYP PFNGLENDPERFQUERYINTELPROC) (GLuint queryHandle);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETFIRSTPERFQUERYIDINTELPROC) (GLuint *queryId);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETNEXTPERFQUERYIDINTELPROC) (GLuint queryId, GLuint *اگلا_Query_Id);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETPERFCOUNTERINFOINTELPROC) (GLuint queryId, GLuint شمار_Id, GLuint شمار_Name_لمبائی, GLchar *شمار_Name, GLuint شمار_Desc_لمبائی, GLchar *شمار_Desc, GLuint *شمار_انحراف, GLuint *شمار_ڈیٹا_سائز, GLuint *شمار_Type_Enum, GLuint *شمار_ڈیٹا_Type_Enum, GLuint64 *raw_شمار_Max_قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETPERFQUERYDATAINTELPROC) (GLuint queryHandle, GLuint flags, GLsizei ڈیٹا_سائز_2, خالی *ڈیٹا, GLuint *بائٹیں_Written);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETPERFQUERYIDBYNAMEINTELPROC) (GLchar *queryName, GLuint *queryId);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETPERFQUERYINFOINTELPROC) (GLuint queryId, GLuint query_Name_لمبائی, GLchar *queryName, GLuint *ڈیٹا_سائز_2, GLuint *noCounters, GLuint *noInstances, GLuint *caps_نقاب);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glBeginPerfQueryINTEL (GLuint queryHandle);
GL_APICALL خالی GL_APIENTRY glCreatePerfQueryINTEL (GLuint queryId, GLuint *queryHandle);
GL_APICALL خالی GL_APIENTRY glDeletePerfQueryINTEL (GLuint queryHandle);
GL_APICALL خالی GL_APIENTRY gl_انتہا_Perf_Query_INTEL (GLuint queryHandle);
GL_APICALL خالی GL_APIENTRY gl_Get_پہلا_Perf_Query_Id_INTEL (GLuint *queryId);
GL_APICALL خالی GL_APIENTRY gl_Get_اگلا_Perf_Query_Id_INTEL (GLuint queryId, GLuint *اگلا_Query_Id);
GL_APICALL خالی GL_APIENTRY gl_Get_Perf_شمار_Info_INTEL (GLuint queryId, GLuint شمار_Id, GLuint شمار_Name_لمبائی, GLchar *شمار_Name, GLuint شمار_Desc_لمبائی, GLchar *شمار_Desc, GLuint *شمار_انحراف, GLuint *شمار_ڈیٹا_سائز, GLuint *شمار_Type_Enum, GLuint *شمار_ڈیٹا_Type_Enum, GLuint64 *raw_شمار_Max_قدر);
GL_APICALL خالی GL_APIENTRY gl_Get_Perf_Query_ڈیٹا_INTEL (GLuint queryHandle, GLuint flags, GLsizei ڈیٹا_سائز_2, خالی *ڈیٹا, GLuint *بائٹیں_Written);
GL_APICALL خالی GL_APIENTRY glGetPerfQueryIdByNameINTEL (GLchar *queryName, GLuint *queryId);
GL_APICALL خالی GL_APIENTRY glGetPerfQueryInfoINTEL (GLuint queryId, GLuint query_Name_لمبائی, GLchar *queryName, GLuint *ڈیٹا_سائز_2, GLuint *noCounters, GLuint *noInstances, GLuint *caps_نقاب);
#اگر_ختم
#اگر_ختم /* GL_INTEL_performance_query */

#اگر_غیر_تعریف_شدہ GL_MESA_bgra
#تعریف_کرو GL_MESA_bgra 1
#تعریف_کرو GL_BGR_EXT                        0x80E0
#اگر_ختم /* GL_MESA_bgra */

#اگر_غیر_تعریف_شدہ GL_MESA_framebuffer_flip_x
#تعریف_کرو GL_MESA_framebuffer_flip_x 1
#تعریف_کرو GL_FRAMEBUFFER_FLIP_X_MESA        0x8BBC
#اگر_ختم /* GL_MESA_framebuffer_flip_x */

#اگر_غیر_تعریف_شدہ GL_MESA_framebuffer_flip_y
#تعریف_کرو GL_MESA_framebuffer_flip_y 1
#تعریف_کرو GL_FRAMEBUFFER_FLIP_Y_MESA        0x8BBB
قسمتعریف خالی (GL_APIENTRYP PFNGLFRAMEBUFFERPARAMETERIMESAPROC) (GLenum ہدف, GLenum pname, GLint param);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETFRAMEBUFFERPARAMETERIVMESAPROC) (GLenum ہدف, GLenum pname, GLint *params);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glFramebufferParameteriMESA (GLenum ہدف, GLenum pname, GLint param);
GL_APICALL خالی GL_APIENTRY glGetFramebufferParameterivMESA (GLenum ہدف, GLenum pname, GLint *params);
#اگر_ختم
#اگر_ختم /* GL_MESA_framebuffer_flip_y */

#اگر_غیر_تعریف_شدہ GL_MESA_framebuffer_تبادلہ_xy
#تعریف_کرو GL_MESA_framebuffer_تبادلہ_xy 1
#تعریف_کرو GL_FRAMEBUFFER_تبادلہ_XY_MESA       0x8BBD
#اگر_ختم /* GL_MESA_framebuffer_swap_xy */

#اگر_غیر_تعریف_شدہ GL_MESA_پروگرام_ثنائی_formats
#تعریف_کرو GL_MESA_پروگرام_ثنائی_formats 1
#تعریف_کرو GL_پروگرام_ثنائی_FORMAT_MESA     0x875F
#اگر_ختم /* GL_MESA_program_binary_formats */

#اگر_غیر_تعریف_شدہ GL_MESA_sampler_objects
#تعریف_کرو GL_MESA_sampler_objects 1
#تعریف_کرو GL_SAMPLER_BINDING                0x8919
قسمتعریف خالی (GL_APIENTRYP PFNGLGENSAMPLERSPROC) (GLsizei گنتی, GLuint *samplers);
قسمتعریف خالی (GL_APIENTRYP PFNGLDELETESAMPLERSPROC) (GLsizei گنتی, ثابت GLuint *samplers);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLISSAMPLERPROC) (GLuint sampler);
قسمتعریف خالی (GL_APIENTRYP PFNGLBINDSAMPLERPROC) (GLuint unit, GLuint sampler);
قسمتعریف خالی (GL_APIENTRYP PFNGLSAMPLERPARAMETERIPROC) (GLuint sampler, GLenum pname, GLint param);
قسمتعریف خالی (GL_APIENTRYP PFNGLSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, ثابت GLint *param);
قسمتعریف خالی (GL_APIENTRYP PFNGLSAMPLERPARAMETERFPROC) (GLuint sampler, GLenum pname, GLfloat param);
قسمتعریف خالی (GL_APIENTRYP PFNGLSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, ثابت GLfloat *param);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, GLint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, GLfloat *params);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glGenSamplers (GLsizei گنتی, GLuint *samplers);
GL_APICALL خالی GL_APIENTRY glDeleteSamplers (GLsizei گنتی, ثابت GLuint *samplers);
GL_APICALL GLboolean GL_APIENTRY glIsSampler (GLuint sampler);
GL_APICALL خالی GL_APIENTRY glBindSampler (GLuint unit, GLuint sampler);
GL_APICALL خالی GL_APIENTRY glSamplerParameteri (GLuint sampler, GLenum pname, GLint param);
GL_APICALL خالی GL_APIENTRY glSamplerParameteriv (GLuint sampler, GLenum pname, ثابت GLint *param);
GL_APICALL خالی GL_APIENTRY glSamplerParameterf (GLuint sampler, GLenum pname, GLfloat param);
GL_APICALL خالی GL_APIENTRY glSamplerParameterfv (GLuint sampler, GLenum pname, ثابت GLfloat *param);
GL_APICALL خالی GL_APIENTRY glGetSamplerParameteriv (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL خالی GL_APIENTRY glGetSamplerParameterfv (GLuint sampler, GLenum pname, GLfloat *params);
#اگر_ختم
#اگر_ختم /* GL_MESA_sampler_objects */

#اگر_غیر_تعریف_شدہ GL_MESA_shader_integer_functions
#تعریف_کرو GL_MESA_shader_integer_functions 1
#اگر_ختم /* GL_MESA_shader_integer_functions */

#اگر_غیر_تعریف_شدہ GL_MESA_texture_const_bandwidth
#تعریف_کرو GL_MESA_texture_const_bandwidth 1
#تعریف_کرو GL_CONST_BW_TILING_MESA           0x8BBE
#اگر_ختم /* GL_MESA_texture_const_bandwidth */

#اگر_غیر_تعریف_شدہ GL_NVX_blend_equation_advanced_multi_draw_buffers
#تعریف_کرو GL_NVX_blend_equation_advanced_multi_draw_buffers 1
#اگر_ختم /* GL_NVX_blend_equation_advanced_multi_draw_buffers */

#اگر_غیر_تعریف_شدہ GL_NV_bindless_texture
#تعریف_کرو GL_NV_bindless_texture 1
قسمتعریف GLuint64 (GL_APIENTRYP PFNGLGETTEXTUREHANDLENVPROC) (GLuint texture);
قسمتعریف GLuint64 (GL_APIENTRYP PFNGLGETTEXTURESAMPLERHANDLENVPROC) (GLuint texture, GLuint sampler);
قسمتعریف خالی (GL_APIENTRYP PFNGLMAKETEXTUREHANDLERESIDENTNVPROC) (GLuint64 handle);
قسمتعریف خالی (GL_APIENTRYP PFNGLMAKETEXTUREHANDLENONRESIDENTNVPROC) (GLuint64 handle);
قسمتعریف GLuint64 (GL_APIENTRYP PFNGLGETIMAGEHANDLENVPROC) (GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format);
قسمتعریف خالی (GL_APIENTRYP PFNGLMAKEIMAGEHANDLERESIDENTNVPROC) (GLuint64 handle, GLenum access);
قسمتعریف خالی (GL_APIENTRYP PFNGLMAKEIMAGEHANDLENONRESIDENTNVPROC) (GLuint64 handle);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORMHANDLEUI64NVPROC) (GLint location, GLuint64 قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORMHANDLEUI64VNVPROC) (GLint location, GLsizei گنتی, ثابت GLuint64 *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64NVPROC) (GLuint پروگرام, GLint location, GLuint64 قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64VNVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint64 *اقدار);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLISTEXTUREHANDLERESIDENTNVPROC) (GLuint64 handle);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLISIMAGEHANDLERESIDENTNVPROC) (GLuint64 handle);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL GLuint64 GL_APIENTRY glGetTextureHandleNV (GLuint texture);
GL_APICALL GLuint64 GL_APIENTRY glGetTextureSamplerHandleNV (GLuint texture, GLuint sampler);
GL_APICALL خالی GL_APIENTRY glMakeTextureHandleResidentNV (GLuint64 handle);
GL_APICALL خالی GL_APIENTRY glMakeTextureHandleNonResidentNV (GLuint64 handle);
GL_APICALL GLuint64 GL_APIENTRY glGetImageHandleNV (GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format);
GL_APICALL خالی GL_APIENTRY glMakeImageHandleResidentNV (GLuint64 handle, GLenum access);
GL_APICALL خالی GL_APIENTRY glMakeImageHandleNonResidentNV (GLuint64 handle);
GL_APICALL خالی GL_APIENTRY gl_یکساں_Handleui64_NV (GLint location, GLuint64 قدر);
GL_APICALL خالی GL_APIENTRY gl_یکساں_Handleui64v_NV (GLint location, GLsizei گنتی, ثابت GLuint64 *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_یکساں_Handleui64_NV (GLuint پروگرام, GLint location, GLuint64 قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_یکساں_Handleui64v_NV (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint64 *اقدار);
GL_APICALL GLboolean GL_APIENTRY glIsTextureHandleResidentNV (GLuint64 handle);
GL_APICALL GLboolean GL_APIENTRY glIsImageHandleResidentNV (GLuint64 handle);
#اگر_ختم
#اگر_ختم /* GL_NV_bindless_texture */

#اگر_غیر_تعریف_شدہ GL_NV_blend_equation_advanced
#تعریف_کرو GL_NV_blend_equation_advanced 1
#تعریف_کرو GL_BLEND_OVERLAP_NV               0x9281
#تعریف_کرو GL_BLEND_PREMULTIPLIED_SRC_NV     0x9280
#تعریف_کرو GL_BLUE_NV                        0x1905
#تعریف_کرو GL_COLORBURN_NV                   0x929A
#تعریف_کرو GL_COLORDODGE_NV                  0x9299
#تعریف_کرو GL_CONJOINT_NV                    0x9284
#تعریف_کرو GL_CONTRAST_NV                    0x92A1
#تعریف_کرو GL_DARKEN_NV                      0x9297
#تعریف_کرو GL_DIFFERENCE_NV                  0x929E
#تعریف_کرو GL_DISJOINT_NV                    0x9283
#تعریف_کرو GL_DST_ATOP_NV                    0x928F
#تعریف_کرو GL_DST_اندر_NV                      0x928B
#تعریف_کرو GL_DST_NV                         0x9287
#تعریف_کرو GL_DST_برآمد_NV                     0x928D
#تعریف_کرو GL_DST_OVER_NV                    0x9289
#تعریف_کرو GL_EXCLUSION_NV                   0x92A0
#تعریف_کرو GL_GREEN_NV                       0x1904
#تعریف_کرو GL_HARDLIGHT_NV                   0x929B
#تعریف_کرو GL_HARDMIX_NV                     0x92A9
#تعریف_کرو GL_HSL_COLOR_NV                   0x92AF
#تعریف_کرو GL_HSL_HUE_NV                     0x92AD
#تعریف_کرو GL_HSL_LUMINOSITY_NV              0x92B0
#تعریف_کرو GL_HSL_SATURATION_NV              0x92AE
#تعریف_کرو GL_INVERT_OVG_NV                  0x92B4
#تعریف_کرو GL_INVERT_RGB_NV                  0x92A3
#تعریف_کرو GL_LIGHTEN_NV                     0x9298
#تعریف_کرو GL_LINEARBURN_NV                  0x92A5
#تعریف_کرو GL_LINEARDODGE_NV                 0x92A4
#تعریف_کرو GL_LINEARLIGHT_NV                 0x92A7
#تعریف_کرو GL_MINUS_CLAMPED_NV               0x92B3
#تعریف_کرو GL_MINUS_NV                       0x929F
#تعریف_کرو GL_MULTIPLY_NV                    0x9294
#تعریف_کرو GL_OVERLAY_NV                     0x9296
#تعریف_کرو GL_PINLIGHT_NV                    0x92A8
#تعریف_کرو GL_PLUS_CLAMPED_ALPHA_NV          0x92B2
#تعریف_کرو GL_PLUS_CLAMPED_NV                0x92B1
#تعریف_کرو GL_PLUS_DARKER_NV                 0x9292
#تعریف_کرو GL_PLUS_NV                        0x9291
#تعریف_کرو GL_RED_NV                         0x1903
#تعریف_کرو GL_SCREEN_NV                      0x9295
#تعریف_کرو GL_SOFTLIGHT_NV                   0x929C
#تعریف_کرو GL_SRC_ATOP_NV                    0x928E
#تعریف_کرو GL_SRC_اندر_NV                      0x928A
#تعریف_کرو GL_SRC_NV                         0x9286
#تعریف_کرو GL_SRC_برآمد_NV                     0x928C
#تعریف_کرو GL_SRC_OVER_NV                    0x9288
#تعریف_کرو GL_UNCORRELATED_NV                0x9282
#تعریف_کرو GL_VIVIDLIGHT_NV                  0x92A6
#تعریف_کرو GL_XOR_NV                         0x1506
قسمتعریف خالی (GL_APIENTRYP PFNGLBLENDPARAMETERINVPROC) (GLenum pname, GLint قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLBLENDBARRIERNVPROC) (خالی);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glBlendParameteriNV (GLenum pname, GLint قدر);
GL_APICALL خالی GL_APIENTRY glBlendBarrierNV (خالی);
#اگر_ختم
#اگر_ختم /* GL_NV_blend_equation_advanced */

#اگر_غیر_تعریف_شدہ GL_NV_blend_equation_advanced_coherent
#تعریف_کرو GL_NV_blend_equation_advanced_coherent 1
#تعریف_کرو GL_BLEND_ADVANCED_COHERENT_NV     0x9285
#اگر_ختم /* GL_NV_blend_equation_advanced_coherent */

#اگر_غیر_تعریف_شدہ GL_NV_blend_minmax_ضربی_عدد
#تعریف_کرو GL_NV_blend_minmax_ضربی_عدد 1
#تعریف_کرو GL_ضربی_عدد_MIN_AMD                 0x901C
#تعریف_کرو GL_ضربی_عدد_MAX_AMD                 0x901D
#اگر_ختم /* GL_NV_blend_minmax_factor */

#اگر_غیر_تعریف_شدہ GL_NV_clip_space_w_scaling
#تعریف_کرو GL_NV_clip_space_w_scaling 1
#تعریف_کرو GL_VIEWPORT_POSITION_W_SCALE_NV   0x937C
#تعریف_کرو GL_VIEWPORT_POSITION_W_SCALE_X_COEFF_NV 0x937D
#تعریف_کرو GL_VIEWPORT_POSITION_W_SCALE_Y_COEFF_NV 0x937E
قسمتعریف خالی (GL_APIENTRYP PFNGLVIEWPORTPOSITIONWSCALENVPROC) (GLuint اشاریہ, GLfloat xcoeff, GLfloat ycoeff);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glViewportPositionWScaleNV (GLuint اشاریہ, GLfloat xcoeff, GLfloat ycoeff);
#اگر_ختم
#اگر_ختم /* GL_NV_clip_space_w_scaling */

#اگر_غیر_تعریف_شدہ GL_NV_compute_shader_derivatives
#تعریف_کرو GL_NV_compute_shader_derivatives 1
#اگر_ختم /* GL_NV_compute_shader_derivatives */

#اگر_غیر_تعریف_شدہ GL_NV_conditional_render
#تعریف_کرو GL_NV_conditional_render 1
#تعریف_کرو GL_QUERY_WAIT_NV                  0x8E13
#تعریف_کرو GL_QUERY_NO_WAIT_NV               0x8E14
#تعریف_کرو GL_QUERY_BY_REGION_WAIT_NV        0x8E15
#تعریف_کرو GL_QUERY_BY_REGION_NO_WAIT_NV     0x8E16
قسمتعریف خالی (GL_APIENTRYP PFNGLBEGINCONDITIONALRENDERNVPROC) (GLuint id, GLenum منوال);
قسمتعریف خالی (GL_APIENTRYP PFNGLENDCONDITIONALRENDERNVPROC) (خالی);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glBeginConditionalRenderNV (GLuint id, GLenum منوال);
GL_APICALL خالی GL_APIENTRY gl_انتہا_Conditional_Render_NV (خالی);
#اگر_ختم
#اگر_ختم /* GL_NV_conditional_render */

#اگر_غیر_تعریف_شدہ GL_NV_conservative_raster
#تعریف_کرو GL_NV_conservative_raster 1
#تعریف_کرو GL_CONSERVATIVE_RASTERIZATION_NV  0x9346
#تعریف_کرو GL_SUBPIXEL_PRECISION_BIAS_X_بٹ_NV 0x9347
#تعریف_کرو GL_SUBPIXEL_PRECISION_BIAS_Y_بٹ_NV 0x9348
#تعریف_کرو GL_MAX_SUBPIXEL_PRECISION_BIAS_بٹ_NV 0x9349
قسمتعریف خالی (GL_APIENTRYP PFNGLSUBPIXELPRECISIONBIASNVPROC) (GLuint xbits, GLuint ybits);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glSubpixelPrecisionBiasNV (GLuint xbits, GLuint ybits);
#اگر_ختم
#اگر_ختم /* GL_NV_conservative_raster */

#اگر_غیر_تعریف_شدہ GL_NV_conservative_raster_pre_snap
#تعریف_کرو GL_NV_conservative_raster_pre_snap 1
#تعریف_کرو GL_CONSERVATIVE_RASTER_منوال_PRE_SNAP_NV 0x9550
#اگر_ختم /* GL_NV_conservative_raster_pre_snap */

#اگر_غیر_تعریف_شدہ GL_NV_conservative_raster_pre_snap_triangles
#تعریف_کرو GL_NV_conservative_raster_pre_snap_triangles 1
#تعریف_کرو GL_CONSERVATIVE_RASTER_منوال_NV    0x954D
#تعریف_کرو GL_CONSERVATIVE_RASTER_منوال_POST_SNAP_NV 0x954E
#تعریف_کرو GL_CONSERVATIVE_RASTER_منوال_PRE_SNAP_TRIANGLES_NV 0x954F
قسمتعریف خالی (GL_APIENTRYP PFNGLCONSERVATIVERASTERPARAMETERINVPROC) (GLenum pname, GLint param);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glConservativeRasterParameteriNV (GLenum pname, GLint param);
#اگر_ختم
#اگر_ختم /* GL_NV_conservative_raster_pre_snap_triangles */

#اگر_غیر_تعریف_شدہ GL_NV_copy_بفر
#تعریف_کرو GL_NV_copy_بفر 1
#تعریف_کرو GL_COPY_READ_بفر_NV            0x8F36
#تعریف_کرو GL_COPY_WRITE_بفر_NV           0x8F37
قسمتعریف خالی (GL_APIENTRYP PFNGLCOPYBUFFERSUBDATANVPROC) (GLenum read_ہدف, GLenum write_ہدف, GLintptr read_انحراف, GLintptr write_انحراف, GLsizeiptr سائز);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_Copy_بفر_Sub_ڈیٹا_NV (GLenum read_ہدف, GLenum write_ہدف, GLintptr read_انحراف, GLintptr write_انحراف, GLsizeiptr سائز);
#اگر_ختم
#اگر_ختم /* GL_NV_copy_buffer */

#اگر_غیر_تعریف_شدہ GL_NV_coverage_sample
#تعریف_کرو GL_NV_coverage_sample 1
#تعریف_کرو GL_COVERAGE_COMPONENT_NV          0x8ED0
#تعریف_کرو GL_COVERAGE_COMPONENT4_NV         0x8ED1
#تعریف_کرو GL_COVERAGE_ATTACHMENT_NV         0x8ED2
#تعریف_کرو GL_COVERAGE_BUFFERS_NV            0x8ED3
#تعریف_کرو GL_COVERAGE_SAMPLES_NV            0x8ED4
#تعریف_کرو GL_COVERAGE_ALL_FRAGMENTS_NV      0x8ED5
#تعریف_کرو GL_COVERAGE_کنارہ_FRAGMENTS_NV     0x8ED6
#تعریف_کرو GL_COVERAGE_AUTOMATIC_NV          0x8ED7
#تعریف_کرو GL_COVERAGE_بفر_ثنائی_ہندسہ_NV         0x00008000
قسمتعریف خالی (GL_APIENTRYP PFNGLCOVERAGEMASKNVPROC) (GLboolean نقاب);
قسمتعریف خالی (GL_APIENTRYP PFNGLCOVERAGEOPERATIONNVPROC) (GLenum operation);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_Coverage_نقاب_NV (GLboolean نقاب);
GL_APICALL خالی GL_APIENTRY glCoverageOperationNV (GLenum operation);
#اگر_ختم
#اگر_ختم /* GL_NV_coverage_sample */

#اگر_غیر_تعریف_شدہ GL_NV_گہرائی_nonlinear
#تعریف_کرو GL_NV_گہرائی_nonlinear 1
#تعریف_کرو GL_گہرائی_COMPONENT16_NONLINEAR_NV 0x8E2C
#اگر_ختم /* GL_NV_depth_nonlinear */

#اگر_غیر_تعریف_شدہ GL_NV_draw_buffers
#تعریف_کرو GL_NV_draw_buffers 1
#تعریف_کرو GL_MAX_DRAW_BUFFERS_NV            0x8824
#تعریف_کرو GL_DRAW_BUFFER0_NV                0x8825
#تعریف_کرو GL_DRAW_BUFFER1_NV                0x8826
#تعریف_کرو GL_DRAW_BUFFER2_NV                0x8827
#تعریف_کرو GL_DRAW_BUFFER3_NV                0x8828
#تعریف_کرو GL_DRAW_BUFFER4_NV                0x8829
#تعریف_کرو GL_DRAW_BUFFER5_NV                0x882A
#تعریف_کرو GL_DRAW_BUFFER6_NV                0x882B
#تعریف_کرو GL_DRAW_BUFFER7_NV                0x882C
#تعریف_کرو GL_DRAW_BUFFER8_NV                0x882D
#تعریف_کرو GL_DRAW_BUFFER9_NV                0x882E
#تعریف_کرو GL_DRAW_BUFFER10_NV               0x882F
#تعریف_کرو GL_DRAW_BUFFER11_NV               0x8830
#تعریف_کرو GL_DRAW_BUFFER12_NV               0x8831
#تعریف_کرو GL_DRAW_BUFFER13_NV               0x8832
#تعریف_کرو GL_DRAW_BUFFER14_NV               0x8833
#تعریف_کرو GL_DRAW_BUFFER15_NV               0x8834
#تعریف_کرو GL_COLOR_ATTACHMENT0_NV           0x8CE0
#تعریف_کرو GL_COLOR_ATTACHMENT1_NV           0x8CE1
#تعریف_کرو GL_COLOR_ATTACHMENT2_NV           0x8CE2
#تعریف_کرو GL_COLOR_ATTACHMENT3_NV           0x8CE3
#تعریف_کرو GL_COLOR_ATTACHMENT4_NV           0x8CE4
#تعریف_کرو GL_COLOR_ATTACHMENT5_NV           0x8CE5
#تعریف_کرو GL_COLOR_ATTACHMENT6_NV           0x8CE6
#تعریف_کرو GL_COLOR_ATTACHMENT7_NV           0x8CE7
#تعریف_کرو GL_COLOR_ATTACHMENT8_NV           0x8CE8
#تعریف_کرو GL_COLOR_ATTACHMENT9_NV           0x8CE9
#تعریف_کرو GL_COLOR_ATTACHMENT10_NV          0x8CEA
#تعریف_کرو GL_COLOR_ATTACHMENT11_NV          0x8CEB
#تعریف_کرو GL_COLOR_ATTACHMENT12_NV          0x8CEC
#تعریف_کرو GL_COLOR_ATTACHMENT13_NV          0x8CED
#تعریف_کرو GL_COLOR_ATTACHMENT14_NV          0x8CEE
#تعریف_کرو GL_COLOR_ATTACHMENT15_NV          0x8CEF
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWBUFFERSNVPROC) (GLsizei n, ثابت GLenum *bufs);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glDrawBuffersNV (GLsizei n, ثابت GLenum *bufs);
#اگر_ختم
#اگر_ختم /* GL_NV_draw_buffers */

#اگر_غیر_تعریف_شدہ GL_NV_draw_instanced
#تعریف_کرو GL_NV_draw_instanced 1
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDNVPROC) (GLenum منوال, GLint پہلا, GLsizei گنتی, GLsizei primcount);
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDNVPROC) (GLenum منوال, GLsizei گنتی, GLenum type, ثابت خالی *indices, GLsizei primcount);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glDrawArraysInstancedNV (GLenum منوال, GLint پہلا, GLsizei گنتی, GLsizei primcount);
GL_APICALL خالی GL_APIENTRY glDrawElementsInstancedNV (GLenum منوال, GLsizei گنتی, GLenum type, ثابت خالی *indices, GLsizei primcount);
#اگر_ختم
#اگر_ختم /* GL_NV_draw_instanced */

#اگر_غیر_تعریف_شدہ GL_NV_draw_vulkan_image
#تعریف_کرو GL_NV_draw_vulkan_image 1
قسمتعریف خالی (GL_APIENTRY  *GLVULKANPROCNV)(خالی);
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWVKIMAGENVPROC) (GLuint64 vkImage, GLuint sampler, GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat z, GLfloat s0, GLfloat t0, GLfloat s1, GLfloat t1);
قسمتعریف GLVULKANPROCNV (GL_APIENTRYP PFNGLGETVKPROCADDRNVPROC) (ثابت GLchar *name);
قسمتعریف خالی (GL_APIENTRYP PFNGLWAITVKSEMAPHORENVPROC) (GLuint64 vkSemaphore);
قسمتعریف خالی (GL_APIENTRYP PFNGLSIGNALVKSEMAPHORENVPROC) (GLuint64 vkSemaphore);
قسمتعریف خالی (GL_APIENTRYP PFNGLSIGNALVKFENCENVPROC) (GLuint64 vkFence);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glDrawVkImageNV (GLuint64 vkImage, GLuint sampler, GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat z, GLfloat s0, GLfloat t0, GLfloat s1, GLfloat t1);
GL_APICALL GLVULKANPROCNV GL_APIENTRY glGetVkProcAddrNV (ثابت GLchar *name);
GL_APICALL خالی GL_APIENTRY glWaitVkSemaphoreNV (GLuint64 vkSemaphore);
GL_APICALL خالی GL_APIENTRY glSignalVkSemaphoreNV (GLuint64 vkSemaphore);
GL_APICALL خالی GL_APIENTRY glSignalVkFenceNV (GLuint64 vkFence);
#اگر_ختم
#اگر_ختم /* GL_NV_draw_vulkan_image */

#اگر_غیر_تعریف_شدہ GL_NV_explicit_attrib_location
#تعریف_کرو GL_NV_explicit_attrib_location 1
#اگر_ختم /* GL_NV_explicit_attrib_location */

#اگر_غیر_تعریف_شدہ GL_NV_fbo_color_attachments
#تعریف_کرو GL_NV_fbo_color_attachments 1
#تعریف_کرو GL_MAX_COLOR_ATTACHMENTS_NV       0x8CDF
#اگر_ختم /* GL_NV_fbo_color_attachments */

#اگر_غیر_تعریف_شدہ GL_NV_fence
#تعریف_کرو GL_NV_fence 1
#تعریف_کرو GL_ALL_COMPLETED_NV               0x84F2
#تعریف_کرو GL_FENCE_حالت_NV                0x84F3
#تعریف_کرو GL_FENCE_CONDITION_NV             0x84F4
قسمتعریف خالی (GL_APIENTRYP PFNGLDELETEFENCESNVPROC) (GLsizei n, ثابت GLuint *fences);
قسمتعریف خالی (GL_APIENTRYP PFNGLGENFENCESNVPROC) (GLsizei n, GLuint *fences);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLISFENCENVPROC) (GLuint fence);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLTESTFENCENVPROC) (GLuint fence);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETFENCEIVNVPROC) (GLuint fence, GLenum pname, GLint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLFINISHFENCENVPROC) (GLuint fence);
قسمتعریف خالی (GL_APIENTRYP PFNGLSETFENCENVPROC) (GLuint fence, GLenum condition);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glDeleteFencesNV (GLsizei n, ثابت GLuint *fences);
GL_APICALL خالی GL_APIENTRY glGenFencesNV (GLsizei n, GLuint *fences);
GL_APICALL GLboolean GL_APIENTRY glIsFenceNV (GLuint fence);
GL_APICALL GLboolean GL_APIENTRY glTestFenceNV (GLuint fence);
GL_APICALL خالی GL_APIENTRY glGetFenceivNV (GLuint fence, GLenum pname, GLint *params);
GL_APICALL خالی GL_APIENTRY gl_اختتام_Fence_NV (GLuint fence);
GL_APICALL خالی GL_APIENTRY gl_سیٹ_Fence_NV (GLuint fence, GLenum condition);
#اگر_ختم
#اگر_ختم /* GL_NV_fence */

#اگر_غیر_تعریف_شدہ GL_NV_fill_rectangle
#تعریف_کرو GL_NV_fill_rectangle 1
#تعریف_کرو GL_FILL_RECTANGLE_NV              0x933C
#اگر_ختم /* GL_NV_fill_rectangle */

#اگر_غیر_تعریف_شدہ GL_NV_fragment_coverage_مقصد_color
#تعریف_کرو GL_NV_fragment_coverage_مقصد_color 1
#تعریف_کرو GL_FRAGMENT_COVERAGE_مقصد_COLOR_NV  0x92DD
#تعریف_کرو GL_FRAGMENT_COVERAGE_COLOR_NV     0x92DE
قسمتعریف خالی (GL_APIENTRYP PFNGLFRAGMENTCOVERAGECOLORNVPROC) (GLuint color);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glFragmentCoverageColorNV (GLuint color);
#اگر_ختم
#اگر_ختم /* GL_NV_fragment_coverage_to_color */

#اگر_غیر_تعریف_شدہ GL_NV_fragment_shader_barycentric
#تعریف_کرو GL_NV_fragment_shader_barycentric 1
#اگر_ختم /* GL_NV_fragment_shader_barycentric */

#اگر_غیر_تعریف_شدہ GL_NV_fragment_shader_interlock
#تعریف_کرو GL_NV_fragment_shader_interlock 1
#اگر_ختم /* GL_NV_fragment_shader_interlock */

#اگر_غیر_تعریف_شدہ GL_NV_framebuffer_blit
#تعریف_کرو GL_NV_framebuffer_blit 1
#تعریف_کرو GL_READ_FRAMEBUFFER_NV            0x8CA8
#تعریف_کرو GL_DRAW_FRAMEBUFFER_NV            0x8CA9
#تعریف_کرو GL_DRAW_FRAMEBUFFER_BINDING_NV    0x8CA6
#تعریف_کرو GL_READ_FRAMEBUFFER_BINDING_NV    0x8CAA
قسمتعریف خالی (GL_APIENTRYP PFNGLBLITFRAMEBUFFERNVPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield نقاب, GLenum filter);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glBlitFramebufferNV (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield نقاب, GLenum filter);
#اگر_ختم
#اگر_ختم /* GL_NV_framebuffer_blit */

#اگر_غیر_تعریف_شدہ GL_NV_framebuffer_mixed_samples
#تعریف_کرو GL_NV_framebuffer_mixed_samples 1
#تعریف_کرو GL_COVERAGE_MODULATION_جدول_NV   0x9331
#تعریف_کرو GL_COLOR_SAMPLES_NV               0x8E20
#تعریف_کرو GL_گہرائی_SAMPLES_NV               0x932D
#تعریف_کرو GL_STENCIL_SAMPLES_NV             0x932E
#تعریف_کرو GL_MIXED_گہرائی_SAMPLES_SUPPORTED_NV 0x932F
#تعریف_کرو GL_MIXED_STENCIL_SAMPLES_SUPPORTED_NV 0x9330
#تعریف_کرو GL_COVERAGE_MODULATION_NV         0x9332
#تعریف_کرو GL_COVERAGE_MODULATION_جدول_سائز_NV 0x9333
قسمتعریف خالی (GL_APIENTRYP PFNGLCOVERAGEMODULATIONTABLENVPROC) (GLsizei n, ثابت GLfloat *v);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETCOVERAGEMODULATIONTABLENVPROC) (GLsizei buf_سائز, GLfloat *v);
قسمتعریف خالی (GL_APIENTRYP PFNGLCOVERAGEMODULATIONNVPROC) (GLenum components);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_Coverage_Modulation_جدول_NV (GLsizei n, ثابت GLfloat *v);
GL_APICALL خالی GL_APIENTRY gl_Get_Coverage_Modulation_جدول_NV (GLsizei buf_سائز, GLfloat *v);
GL_APICALL خالی GL_APIENTRY glCoverageModulationNV (GLenum components);
#اگر_ختم
#اگر_ختم /* GL_NV_framebuffer_mixed_samples */

#اگر_غیر_تعریف_شدہ GL_NV_framebuffer_multisample
#تعریف_کرو GL_NV_framebuffer_multisample 1
#تعریف_کرو GL_RENDERBUFFER_SAMPLES_NV        0x8CAB
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_NV 0x8D56
#تعریف_کرو GL_MAX_SAMPLES_NV                 0x8D57
قسمتعریف خالی (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLENVPROC) (GLenum ہدف, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glRenderbufferStorageMultisampleNV (GLenum ہدف, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
#اگر_ختم
#اگر_ختم /* GL_NV_framebuffer_multisample */

#اگر_غیر_تعریف_شدہ GL_NV_generate_mipmap_sRGB
#تعریف_کرو GL_NV_generate_mipmap_sRGB 1
#اگر_ختم /* GL_NV_generate_mipmap_sRGB */

#اگر_غیر_تعریف_شدہ GL_NV_geometry_shader_passthrough
#تعریف_کرو GL_NV_geometry_shader_passthrough 1
#اگر_ختم /* GL_NV_geometry_shader_passthrough */

#اگر_غیر_تعریف_شدہ GL_NV_gpu_shader5
#تعریف_کرو GL_NV_gpu_shader5 1
قسمتعریف khronos_int64_t GLint64EXT;
قسمتعریف khronos_uint64_t GLuint64EXT;
#تعریف_کرو GL_INT64_NV                       0x140E
#تعریف_کرو GL_UNSIGNED_INT64_NV              0x140F
#تعریف_کرو GL_INT8_NV                        0x8FE0
#تعریف_کرو GL_INT8_VEC2_NV                   0x8FE1
#تعریف_کرو GL_INT8_VEC3_NV                   0x8FE2
#تعریف_کرو GL_INT8_VEC4_NV                   0x8FE3
#تعریف_کرو GL_INT16_NV                       0x8FE4
#تعریف_کرو GL_INT16_VEC2_NV                  0x8FE5
#تعریف_کرو GL_INT16_VEC3_NV                  0x8FE6
#تعریف_کرو GL_INT16_VEC4_NV                  0x8FE7
#تعریف_کرو GL_INT64_VEC2_NV                  0x8FE9
#تعریف_کرو GL_INT64_VEC3_NV                  0x8FEA
#تعریف_کرو GL_INT64_VEC4_NV                  0x8FEB
#تعریف_کرو GL_UNSIGNED_INT8_NV               0x8FEC
#تعریف_کرو GL_UNSIGNED_INT8_VEC2_NV          0x8FED
#تعریف_کرو GL_UNSIGNED_INT8_VEC3_NV          0x8FEE
#تعریف_کرو GL_UNSIGNED_INT8_VEC4_NV          0x8FEF
#تعریف_کرو GL_UNSIGNED_INT16_NV              0x8FF0
#تعریف_کرو GL_UNSIGNED_INT16_VEC2_NV         0x8FF1
#تعریف_کرو GL_UNSIGNED_INT16_VEC3_NV         0x8FF2
#تعریف_کرو GL_UNSIGNED_INT16_VEC4_NV         0x8FF3
#تعریف_کرو GL_UNSIGNED_INT64_VEC2_NV         0x8FF5
#تعریف_کرو GL_UNSIGNED_INT64_VEC3_NV         0x8FF6
#تعریف_کرو GL_UNSIGNED_INT64_VEC4_NV         0x8FF7
#تعریف_کرو GL_FLOAT16_NV                     0x8FF8
#تعریف_کرو GL_FLOAT16_VEC2_NV                0x8FF9
#تعریف_کرو GL_FLOAT16_VEC3_NV                0x8FFA
#تعریف_کرو GL_FLOAT16_VEC4_NV                0x8FFB
#تعریف_کرو GL_PATCHES                        0x000E
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM1I64NVPROC) (GLint location, GLint64EXT x);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM2I64NVPROC) (GLint location, GLint64EXT x, GLint64EXT y);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM3I64NVPROC) (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM4I64NVPROC) (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM1I64VNVPROC) (GLint location, GLsizei گنتی, ثابت GLint64EXT *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM2I64VNVPROC) (GLint location, GLsizei گنتی, ثابت GLint64EXT *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM3I64VNVPROC) (GLint location, GLsizei گنتی, ثابت GLint64EXT *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM4I64VNVPROC) (GLint location, GLsizei گنتی, ثابت GLint64EXT *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM1UI64NVPROC) (GLint location, GLuint64EXT x);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM2UI64NVPROC) (GLint location, GLuint64EXT x, GLuint64EXT y);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM3UI64NVPROC) (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM4UI64NVPROC) (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM1UI64VNVPROC) (GLint location, GLsizei گنتی, ثابت GLuint64EXT *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM2UI64VNVPROC) (GLint location, GLsizei گنتی, ثابت GLuint64EXT *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM3UI64VNVPROC) (GLint location, GLsizei گنتی, ثابت GLuint64EXT *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM4UI64VNVPROC) (GLint location, GLsizei گنتی, ثابت GLuint64EXT *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETUNIFORMI64VNVPROC) (GLuint پروگرام, GLint location, GLint64EXT *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM1I64NVPROC) (GLuint پروگرام, GLint location, GLint64EXT x);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM2I64NVPROC) (GLuint پروگرام, GLint location, GLint64EXT x, GLint64EXT y);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM3I64NVPROC) (GLuint پروگرام, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM4I64NVPROC) (GLuint پروگرام, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM1I64VNVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint64EXT *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM2I64VNVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint64EXT *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM3I64VNVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint64EXT *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM4I64VNVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint64EXT *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UI64NVPROC) (GLuint پروگرام, GLint location, GLuint64EXT x);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UI64NVPROC) (GLuint پروگرام, GLint location, GLuint64EXT x, GLuint64EXT y);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UI64NVPROC) (GLuint پروگرام, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UI64NVPROC) (GLuint پروگرام, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UI64VNVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint64EXT *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UI64VNVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint64EXT *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UI64VNVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint64EXT *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UI64VNVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint64EXT *قدر);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glUniform1i64NV (GLint location, GLint64EXT x);
GL_APICALL خالی GL_APIENTRY glUniform2i64NV (GLint location, GLint64EXT x, GLint64EXT y);
GL_APICALL خالی GL_APIENTRY glUniform3i64NV (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
GL_APICALL خالی GL_APIENTRY glUniform4i64NV (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
GL_APICALL خالی GL_APIENTRY glUniform1i64vNV (GLint location, GLsizei گنتی, ثابت GLint64EXT *قدر);
GL_APICALL خالی GL_APIENTRY glUniform2i64vNV (GLint location, GLsizei گنتی, ثابت GLint64EXT *قدر);
GL_APICALL خالی GL_APIENTRY glUniform3i64vNV (GLint location, GLsizei گنتی, ثابت GLint64EXT *قدر);
GL_APICALL خالی GL_APIENTRY glUniform4i64vNV (GLint location, GLsizei گنتی, ثابت GLint64EXT *قدر);
GL_APICALL خالی GL_APIENTRY glUniform1ui64NV (GLint location, GLuint64EXT x);
GL_APICALL خالی GL_APIENTRY glUniform2ui64NV (GLint location, GLuint64EXT x, GLuint64EXT y);
GL_APICALL خالی GL_APIENTRY glUniform3ui64NV (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
GL_APICALL خالی GL_APIENTRY glUniform4ui64NV (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
GL_APICALL خالی GL_APIENTRY glUniform1ui64vNV (GLint location, GLsizei گنتی, ثابت GLuint64EXT *قدر);
GL_APICALL خالی GL_APIENTRY glUniform2ui64vNV (GLint location, GLsizei گنتی, ثابت GLuint64EXT *قدر);
GL_APICALL خالی GL_APIENTRY glUniform3ui64vNV (GLint location, GLsizei گنتی, ثابت GLuint64EXT *قدر);
GL_APICALL خالی GL_APIENTRY glUniform4ui64vNV (GLint location, GLsizei گنتی, ثابت GLuint64EXT *قدر);
GL_APICALL خالی GL_APIENTRY glGetUniformi64vNV (GLuint پروگرام, GLint location, GLint64EXT *params);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform1i64_NV (GLuint پروگرام, GLint location, GLint64EXT x);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform2i64_NV (GLuint پروگرام, GLint location, GLint64EXT x, GLint64EXT y);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform3i64_NV (GLuint پروگرام, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform4i64_NV (GLuint پروگرام, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform1i64v_NV (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint64EXT *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform2i64v_NV (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint64EXT *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform3i64v_NV (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint64EXT *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform4i64v_NV (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint64EXT *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform1ui64_NV (GLuint پروگرام, GLint location, GLuint64EXT x);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform2ui64_NV (GLuint پروگرام, GLint location, GLuint64EXT x, GLuint64EXT y);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform3ui64_NV (GLuint پروگرام, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform4ui64_NV (GLuint پروگرام, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform1ui64v_NV (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint64EXT *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform2ui64v_NV (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint64EXT *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform3ui64v_NV (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint64EXT *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform4ui64v_NV (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint64EXT *قدر);
#اگر_ختم
#اگر_ختم /* GL_NV_gpu_shader5 */

#اگر_غیر_تعریف_شدہ GL_NV_image_formats
#تعریف_کرو GL_NV_image_formats 1
#اگر_ختم /* GL_NV_image_formats */

#اگر_غیر_تعریف_شدہ GL_NV_instanced_arrays
#تعریف_کرو GL_NV_instanced_arrays 1
#تعریف_کرو GL_راس_ATTRIB_ARRAY_مقسوم_علیہ_NV 0x88FE
قسمتعریف خالی (GL_APIENTRYP PFNGLVERTEXATTRIBDIVISORNVPROC) (GLuint اشاریہ, GLuint مقسوم_علیہ);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_راس_Attrib_مقسوم_علیہ_NV (GLuint اشاریہ, GLuint مقسوم_علیہ);
#اگر_ختم
#اگر_ختم /* GL_NV_instanced_arrays */

#اگر_غیر_تعریف_شدہ GL_NV_internalformat_sample_query
#تعریف_کرو GL_NV_internalformat_sample_query 1
#تعریف_کرو GL_TEXTURE_2D_MULTISAMPLE         0x9100
#تعریف_کرو GL_TEXTURE_2D_MULTISAMPLE_ARRAY   0x9102
#تعریف_کرو GL_MULTISAMPLES_NV                0x9371
#تعریف_کرو GL_SUPERSAMPLE_SCALE_X_NV         0x9372
#تعریف_کرو GL_SUPERSAMPLE_SCALE_Y_NV         0x9373
#تعریف_کرو GL_CONFORMANT_NV                  0x9374
قسمتعریف خالی (GL_APIENTRYP PFNGLGETINTERNALFORMATSAMPLEIVNVPROC) (GLenum ہدف, GLenum internalformat, GLsizei samples, GLenum pname, GLsizei گنتی, GLint *params);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glGetInternalformatSampleivNV (GLenum ہدف, GLenum internalformat, GLsizei samples, GLenum pname, GLsizei گنتی, GLint *params);
#اگر_ختم
#اگر_ختم /* GL_NV_internalformat_sample_query */

#اگر_غیر_تعریف_شدہ GL_NV_حافظہ_attachment
#تعریف_کرو GL_NV_حافظہ_attachment 1
#تعریف_کرو GL_ATTACHED_حافظہ_OBJECT_NV      0x95A4
#تعریف_کرو GL_ATTACHED_حافظہ_انحراف_NV      0x95A5
#تعریف_کرو GL_حافظہ_ATTACHABLE_ALIGNMENT_NV 0x95A6
#تعریف_کرو GL_حافظہ_ATTACHABLE_سائز_NV      0x95A7
#تعریف_کرو GL_حافظہ_ATTACHABLE_NV           0x95A8
#تعریف_کرو GL_DETACHED_حافظہ_INCARNATION_NV 0x95A9
#تعریف_کرو GL_DETACHED_TEXTURES_NV           0x95AA
#تعریف_کرو GL_DETACHED_BUFFERS_NV            0x95AB
#تعریف_کرو GL_MAX_DETACHED_TEXTURES_NV       0x95AC
#تعریف_کرو GL_MAX_DETACHED_BUFFERS_NV        0x95AD
قسمتعریف خالی (GL_APIENTRYP PFNGLGETMEMORYOBJECTDETACHEDRESOURCESUIVNVPROC) (GLuint حافظہ, GLenum pname, GLint پہلا, GLsizei گنتی, GLuint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLRESETMEMORYOBJECTPARAMETERNVPROC) (GLuint حافظہ, GLenum pname);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXATTACHMEMORYNVPROC) (GLenum ہدف, GLuint حافظہ, GLuint64 انحراف_2);
قسمتعریف خالی (GL_APIENTRYP PFNGLBUFFERATTACHMEMORYNVPROC) (GLenum ہدف, GLuint حافظہ, GLuint64 انحراف_2);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXTUREATTACHMEMORYNVPROC) (GLuint texture, GLuint حافظہ, GLuint64 انحراف_2);
قسمتعریف خالی (GL_APIENTRYP PFNGLNAMEDBUFFERATTACHMEMORYNVPROC) (GLuint بفر_2, GLuint حافظہ, GLuint64 انحراف_2);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_Get_حافظہ_Object_Detached_Resourcesuiv_NV (GLuint حافظہ, GLenum pname, GLint پہلا, GLsizei گنتی, GLuint *params);
GL_APICALL خالی GL_APIENTRY gl_Reset_حافظہ_Object_Parameter_NV (GLuint حافظہ, GLenum pname);
GL_APICALL خالی GL_APIENTRY gl_Tex_Attach_حافظہ_NV (GLenum ہدف, GLuint حافظہ, GLuint64 انحراف_2);
GL_APICALL خالی GL_APIENTRY gl_بفر_Attach_حافظہ_NV (GLenum ہدف, GLuint حافظہ, GLuint64 انحراف_2);
GL_APICALL خالی GL_APIENTRY gl_Texture_Attach_حافظہ_NV (GLuint texture, GLuint حافظہ, GLuint64 انحراف_2);
GL_APICALL خالی GL_APIENTRY gl_Named_بفر_Attach_حافظہ_NV (GLuint بفر_2, GLuint حافظہ, GLuint64 انحراف_2);
#اگر_ختم
#اگر_ختم /* GL_NV_memory_attachment */

#اگر_غیر_تعریف_شدہ GL_NV_حافظہ_object_sparse
#تعریف_کرو GL_NV_حافظہ_object_sparse 1
قسمتعریف خالی (GL_APIENTRYP PFNGLBUFFERPAGECOMMITMENTMEMNVPROC) (GLenum ہدف, GLintptr انحراف_2, GLsizeiptr سائز, GLuint حافظہ, GLuint64 mem_انحراف, GLboolean commit);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXPAGECOMMITMENTMEMNVPROC) (GLenum ہدف, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLuint حافظہ, GLuint64 انحراف_2, GLboolean commit);
قسمتعریف خالی (GL_APIENTRYP PFNGLNAMEDBUFFERPAGECOMMITMENTMEMNVPROC) (GLuint بفر_2, GLintptr انحراف_2, GLsizeiptr سائز, GLuint حافظہ, GLuint64 mem_انحراف, GLboolean commit);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXTUREPAGECOMMITMENTMEMNVPROC) (GLuint texture, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLuint حافظہ, GLuint64 انحراف_2, GLboolean commit);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_بفر_صفحہ_Commitment_Mem_NV (GLenum ہدف, GLintptr انحراف_2, GLsizeiptr سائز, GLuint حافظہ, GLuint64 mem_انحراف, GLboolean commit);
GL_APICALL خالی GL_APIENTRY gl_Tex_صفحہ_Commitment_Mem_NV (GLenum ہدف, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLuint حافظہ, GLuint64 انحراف_2, GLboolean commit);
GL_APICALL خالی GL_APIENTRY gl_Named_بفر_صفحہ_Commitment_Mem_NV (GLuint بفر_2, GLintptr انحراف_2, GLsizeiptr سائز, GLuint حافظہ, GLuint64 mem_انحراف, GLboolean commit);
GL_APICALL خالی GL_APIENTRY gl_Texture_صفحہ_Commitment_Mem_NV (GLuint texture, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLuint حافظہ, GLuint64 انحراف_2, GLboolean commit);
#اگر_ختم
#اگر_ختم /* GL_NV_memory_object_sparse */

#اگر_غیر_تعریف_شدہ GL_NV_mesh_shader
#تعریف_کرو GL_NV_mesh_shader 1
#تعریف_کرو GL_MESH_SHADER_NV                 0x9559
#تعریف_کرو GL_TASK_SHADER_NV                 0x955A
#تعریف_کرو GL_MAX_MESH_یکساں_بلاکیں_NV     0x8E60
#تعریف_کرو GL_MAX_MESH_TEXTURE_IMAGE_UNITS_NV 0x8E61
#تعریف_کرو GL_MAX_MESH_IMAGE_UNIFORMS_NV     0x8E62
#تعریف_کرو GL_MAX_MESH_یکساں_COMPONENTS_NV 0x8E63
#تعریف_کرو GL_MAX_MESH_ATOMIC_شمار_BUFFERS_NV 0x8E64
#تعریف_کرو GL_MAX_MESH_ATOMIC_COUNTERS_NV    0x8E65
#تعریف_کرو GL_MAX_MESH_SHADER_STORAGE_بلاکیں_NV 0x8E66
#تعریف_کرو GL_MAX_COMBINED_MESH_یکساں_COMPONENTS_NV 0x8E67
#تعریف_کرو GL_MAX_TASK_یکساں_بلاکیں_NV     0x8E68
#تعریف_کرو GL_MAX_TASK_TEXTURE_IMAGE_UNITS_NV 0x8E69
#تعریف_کرو GL_MAX_TASK_IMAGE_UNIFORMS_NV     0x8E6A
#تعریف_کرو GL_MAX_TASK_یکساں_COMPONENTS_NV 0x8E6B
#تعریف_کرو GL_MAX_TASK_ATOMIC_شمار_BUFFERS_NV 0x8E6C
#تعریف_کرو GL_MAX_TASK_ATOMIC_COUNTERS_NV    0x8E6D
#تعریف_کرو GL_MAX_TASK_SHADER_STORAGE_بلاکیں_NV 0x8E6E
#تعریف_کرو GL_MAX_COMBINED_TASK_یکساں_COMPONENTS_NV 0x8E6F
#تعریف_کرو GL_MAX_MESH_WORK_گروہ_INVOCATIONS_NV 0x95A2
#تعریف_کرو GL_MAX_TASK_WORK_گروہ_INVOCATIONS_NV 0x95A3
#تعریف_کرو GL_MAX_MESH_کل_حافظہ_سائز_NV  0x9536
#تعریف_کرو GL_MAX_TASK_کل_حافظہ_سائز_NV  0x9537
#تعریف_کرو GL_MAX_MESH_OUTPUT_VERTICES_NV    0x9538
#تعریف_کرو GL_MAX_MESH_OUTPUT_PRIMITIVES_NV  0x9539
#تعریف_کرو GL_MAX_TASK_OUTPUT_گنتی_NV       0x953A
#تعریف_کرو GL_MAX_DRAW_MESH_TASKS_گنتی_NV   0x953D
#تعریف_کرو GL_MAX_MESH_VIEWS_NV              0x9557
#تعریف_کرو GL_MESH_OUTPUT_فی_راس_GRANULARITY_NV 0x92DF
#تعریف_کرو GL_MESH_OUTPUT_فی_PRIMITIVE_GRANULARITY_NV 0x9543
#تعریف_کرو GL_MAX_MESH_WORK_گروہ_سائز_NV    0x953B
#تعریف_کرو GL_MAX_TASK_WORK_گروہ_سائز_NV    0x953C
#تعریف_کرو GL_MESH_WORK_گروہ_سائز_NV        0x953E
#تعریف_کرو GL_TASK_WORK_گروہ_سائز_NV        0x953F
#تعریف_کرو GL_MESH_VERTICES_برآمد_NV           0x9579
#تعریف_کرو GL_MESH_PRIMITIVES_برآمد_NV         0x957A
#تعریف_کرو GL_MESH_OUTPUT_TYPE_NV            0x957B
#تعریف_کرو GL_یکساں_بلاک_REFERENCED_BY_MESH_SHADER_NV 0x959C
#تعریف_کرو GL_یکساں_بلاک_REFERENCED_BY_TASK_SHADER_NV 0x959D
#تعریف_کرو GL_REFERENCED_BY_MESH_SHADER_NV   0x95A0
#تعریف_کرو GL_REFERENCED_BY_TASK_SHADER_NV   0x95A1
#تعریف_کرو GL_MESH_SHADER_ثنائی_ہندسہ_NV             0x00000040
#تعریف_کرو GL_TASK_SHADER_ثنائی_ہندسہ_NV             0x00000080
#تعریف_کرو GL_MESH_SUBROUTINE_NV             0x957C
#تعریف_کرو GL_TASK_SUBROUTINE_NV             0x957D
#تعریف_کرو GL_MESH_SUBROUTINE_یکساں_NV     0x957E
#تعریف_کرو GL_TASK_SUBROUTINE_یکساں_NV     0x957F
#تعریف_کرو GL_ATOMIC_شمار_بفر_REFERENCED_BY_MESH_SHADER_NV 0x959E
#تعریف_کرو GL_ATOMIC_شمار_بفر_REFERENCED_BY_TASK_SHADER_NV 0x959F
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWMESHTASKSNVPROC) (GLuint پہلا, GLuint گنتی);
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWMESHTASKSINDIRECTNVPROC) (GLintptr بالواسطہ);
قسمتعریف خالی (GL_APIENTRYP PFNGLMULTIDRAWMESHTASKSINDIRECTNVPROC) (GLintptr بالواسطہ, GLsizei drawcount, GLsizei stride);
قسمتعریف خالی (GL_APIENTRYP PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTNVPROC) (GLintptr بالواسطہ, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glDrawMeshTasksNV (GLuint پہلا, GLuint گنتی);
GL_APICALL خالی GL_APIENTRY gl_Draw_Mesh_Tasks_بالواسطہ_NV (GLintptr بالواسطہ);
GL_APICALL خالی GL_APIENTRY gl_Multi_Draw_Mesh_Tasks_بالواسطہ_NV (GLintptr بالواسطہ, GLsizei drawcount, GLsizei stride);
GL_APICALL خالی GL_APIENTRY gl_Multi_Draw_Mesh_Tasks_بالواسطہ_گنتی_NV (GLintptr بالواسطہ, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
#اگر_ختم
#اگر_ختم /* GL_NV_mesh_shader */

#اگر_غیر_تعریف_شدہ GL_NV_non_مربع_matrices
#تعریف_کرو GL_NV_non_مربع_matrices 1
#تعریف_کرو GL_FLOAT_MAT2x3_NV                0x8B65
#تعریف_کرو GL_FLOAT_MAT2x4_NV                0x8B66
#تعریف_کرو GL_FLOAT_MAT3x2_NV                0x8B67
#تعریف_کرو GL_FLOAT_MAT3x4_NV                0x8B68
#تعریف_کرو GL_FLOAT_MAT4x2_NV                0x8B69
#تعریف_کرو GL_FLOAT_MAT4x3_NV                0x8B6A
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORMMATRIX2X3FVNVPROC) (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORMMATRIX3X2FVNVPROC) (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORMMATRIX2X4FVNVPROC) (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORMMATRIX4X2FVNVPROC) (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORMMATRIX3X4FVNVPROC) (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORMMATRIX4X3FVNVPROC) (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_یکساں_Matrix2x3fv_NV (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_یکساں_Matrix3x2fv_NV (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_یکساں_Matrix2x4fv_NV (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_یکساں_Matrix4x2fv_NV (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_یکساں_Matrix3x4fv_NV (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_یکساں_Matrix4x3fv_NV (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
#اگر_ختم
#اگر_ختم /* GL_NV_non_square_matrices */

#اگر_غیر_تعریف_شدہ GL_NV_pack_subimage
#تعریف_کرو GL_NV_pack_subimage 1
#تعریف_کرو GL_PACK_صف_لمبائی_NV             0x0D02
#تعریف_کرو GL_PACK_SKIP_صفیں_NV              0x0D03
#تعریف_کرو GL_PACK_SKIP_PIXELS_NV            0x0D04
#اگر_ختم /* GL_NV_pack_subimage */

#اگر_غیر_تعریف_شدہ GL_NV_راستہ_rendering
#تعریف_کرو GL_NV_راستہ_rendering 1
قسمتعریف دوہرا GLdouble;
#تعریف_کرو GL_راستہ_FORMAT_SVG_NV             0x9070
#تعریف_کرو GL_راستہ_FORMAT_PS_NV              0x9071
#تعریف_کرو GL_STANDARD_FONT_NAME_NV          0x9072
#تعریف_کرو GL_SYSTEM_FONT_NAME_NV            0x9073
#تعریف_کرو GL_FILE_NAME_NV                   0x9074
#تعریف_کرو GL_راستہ_STROKE_چوڑائی_NV           0x9075
#تعریف_کرو GL_راستہ_انتہا_CAPS_NV               0x9076
#تعریف_کرو GL_راستہ_INITIAL_انتہا_CAP_NV        0x9077
#تعریف_کرو GL_راستہ_TERMINAL_انتہا_CAP_NV       0x9078
#تعریف_کرو GL_راستہ_JOIN_STYLE_NV             0x9079
#تعریف_کرو GL_راستہ_MITER_حد_بندی_NV            0x907A
#تعریف_کرو GL_راستہ_DASH_CAPS_NV              0x907B
#تعریف_کرو GL_راستہ_INITIAL_DASH_CAP_NV       0x907C
#تعریف_کرو GL_راستہ_TERMINAL_DASH_CAP_NV      0x907D
#تعریف_کرو GL_راستہ_DASH_انحراف_NV            0x907E
#تعریف_کرو GL_راستہ_CLIENT_لمبائی_NV          0x907F
#تعریف_کرو GL_راستہ_FILL_منوال_NV              0x9080
#تعریف_کرو GL_راستہ_FILL_نقاب_NV              0x9081
#تعریف_کرو GL_راستہ_FILL_COVER_منوال_NV        0x9082
#تعریف_کرو GL_راستہ_STROKE_COVER_منوال_NV      0x9083
#تعریف_کرو GL_راستہ_STROKE_نقاب_NV            0x9084
#تعریف_کرو GL_گنتی_اوپر_NV                    0x9088
#تعریف_کرو GL_گنتی_نیچے_کو_NV                  0x9089
#تعریف_کرو GL_راستہ_OBJECT_BOUNDING_BOX_NV    0x908A
#تعریف_کرو GL_CONVEX_HULL_NV                 0x908B
#تعریف_کرو GL_BOUNDING_BOX_NV                0x908D
#تعریف_کرو GL_TRANSLATE_X_NV                 0x908E
#تعریف_کرو GL_TRANSLATE_Y_NV                 0x908F
#تعریف_کرو GL_TRANSLATE_2D_NV                0x9090
#تعریف_کرو GL_TRANSLATE_3D_NV                0x9091
#تعریف_کرو GL_AFFINE_2D_NV                   0x9092
#تعریف_کرو GL_AFFINE_3D_NV                   0x9094
#تعریف_کرو GL_TRANSPOSE_AFFINE_2D_NV         0x9096
#تعریف_کرو GL_TRANSPOSE_AFFINE_3D_NV         0x9098
#تعریف_کرو GL_UTF8_NV                        0x909A
#تعریف_کرو GL_UTF16_NV                       0x909B
#تعریف_کرو GL_BOUNDING_BOX_کا_BOUNDING_BOXES_NV 0x909C
#تعریف_کرو GL_راستہ_COMMAND_گنتی_NV          0x909D
#تعریف_کرو GL_راستہ_COORD_گنتی_NV            0x909E
#تعریف_کرو GL_راستہ_DASH_ARRAY_گنتی_NV       0x909F
#تعریف_کرو GL_راستہ_COMPUTED_لمبائی_NV        0x90A0
#تعریف_کرو GL_راستہ_FILL_BOUNDING_BOX_NV      0x90A1
#تعریف_کرو GL_راستہ_STROKE_BOUNDING_BOX_NV    0x90A2
#تعریف_کرو GL_مربع_NV                      0x90A3
#تعریف_کرو GL_باری_NV                       0x90A4
#تعریف_کرو GL_TRIANGULAR_NV                  0x90A5
#تعریف_کرو GL_BEVEL_NV                       0x90A6
#تعریف_کرو GL_MITER_REVERT_NV                0x90A7
#تعریف_کرو GL_MITER_TRUNCATE_NV              0x90A8
#تعریف_کرو GL_SKIP_MISSING_GLYPH_NV          0x90A9
#تعریف_کرو GL_USE_MISSING_GLYPH_NV           0x90AA
#تعریف_کرو GL_راستہ_ERROR_POSITION_NV         0x90AB
#تعریف_کرو GL_ACCUM_ADJACENT_جوڑے_NV        0x90AD
#تعریف_کرو GL_ADJACENT_جوڑے_NV              0x90AE
#تعریف_کرو GL_پہلا_مقصد_REST_NV               0x90AF
#تعریف_کرو GL_راستہ_GEN_منوال_NV               0x90B0
#تعریف_کرو GL_راستہ_GEN_COEFF_NV              0x90B1
#تعریف_کرو GL_راستہ_GEN_COMPONENTS_NV         0x90B3
#تعریف_کرو GL_راستہ_STENCIL_FUNC_NV           0x90B7
#تعریف_کرو GL_راستہ_STENCIL_REF_NV            0x90B8
#تعریف_کرو GL_راستہ_STENCIL_قدر_نقاب_NV     0x90B9
#تعریف_کرو GL_راستہ_STENCIL_گہرائی_انحراف_ضربی_عدد_NV 0x90BD
#تعریف_کرو GL_راستہ_STENCIL_گہرائی_انحراف_UNITS_NV 0x90BE
#تعریف_کرو GL_راستہ_COVER_گہرائی_FUNC_NV       0x90BF
#تعریف_کرو GL_راستہ_DASH_انحراف_RESET_NV      0x90B4
#تعریف_کرو GL_MOVE_مقصد_RESETS_NV              0x90B5
#تعریف_کرو GL_MOVE_مقصد_CONTINUES_NV           0x90B6
#تعریف_کرو GL_CLOSE_راستہ_NV                  0x00
#تعریف_کرو GL_MOVE_مقصد_NV                     0x02
#تعریف_کرو GL_RELATIVE_MOVE_مقصد_NV            0x03
#تعریف_کرو GL_سطر_مقصد_NV                     0x04
#تعریف_کرو GL_RELATIVE_سطر_مقصد_NV            0x05
#تعریف_کرو GL_HORIZONTAL_سطر_مقصد_NV          0x06
#تعریف_کرو GL_RELATIVE_HORIZONTAL_سطر_مقصد_NV 0x07
#تعریف_کرو GL_VERTICAL_سطر_مقصد_NV            0x08
#تعریف_کرو GL_RELATIVE_VERTICAL_سطر_مقصد_NV   0x09
#تعریف_کرو GL_QUADRATIC_خم_مقصد_NV          0x0A
#تعریف_کرو GL_RELATIVE_QUADRATIC_خم_مقصد_NV 0x0B
#تعریف_کرو GL_CUBIC_خم_مقصد_NV              0x0C
#تعریف_کرو GL_RELATIVE_CUBIC_خم_مقصد_NV     0x0D
#تعریف_کرو GL_SMOOTH_QUADRATIC_خم_مقصد_NV   0x0E
#تعریف_کرو GL_RELATIVE_SMOOTH_QUADRATIC_خم_مقصد_NV 0x0F
#تعریف_کرو GL_SMOOTH_CUBIC_خم_مقصد_NV       0x10
#تعریف_کرو GL_RELATIVE_SMOOTH_CUBIC_خم_مقصد_NV 0x11
#تعریف_کرو GL_SMALL_CCW_ARC_مقصد_NV            0x12
#تعریف_کرو GL_RELATIVE_SMALL_CCW_ARC_مقصد_NV   0x13
#تعریف_کرو GL_SMALL_CW_ARC_مقصد_NV             0x14
#تعریف_کرو GL_RELATIVE_SMALL_CW_ARC_مقصد_NV    0x15
#تعریف_کرو GL_LARGE_CCW_ARC_مقصد_NV            0x16
#تعریف_کرو GL_RELATIVE_LARGE_CCW_ARC_مقصد_NV   0x17
#تعریف_کرو GL_LARGE_CW_ARC_مقصد_NV             0x18
#تعریف_کرو GL_RELATIVE_LARGE_CW_ARC_مقصد_NV    0x19
#تعریف_کرو GL_RESTART_راستہ_NV                0xF0
#تعریف_کرو GL_DUP_پہلا_CUBIC_خم_مقصد_NV    0xF2
#تعریف_کرو GL_DUP_آخری_CUBIC_خم_مقصد_NV     0xF4
#تعریف_کرو GL_RECT_NV                        0xF6
#تعریف_کرو GL_CIRCULAR_CCW_ARC_مقصد_NV         0xF8
#تعریف_کرو GL_CIRCULAR_CW_ARC_مقصد_NV          0xFA
#تعریف_کرو GL_CIRCULAR_TANGENT_ARC_مقصد_NV     0xFC
#تعریف_کرو GL_ARC_مقصد_NV                      0xFE
#تعریف_کرو GL_RELATIVE_ARC_مقصد_NV             0xFF
#تعریف_کرو GL_BOLD_ثنائی_ہندسہ_NV                    0x01
#تعریف_کرو GL_ITALIC_ثنائی_ہندسہ_NV                  0x02
#تعریف_کرو GL_GLYPH_چوڑائی_ثنائی_ہندسہ_NV             0x01
#تعریف_کرو GL_GLYPH_اونچائی_ثنائی_ہندسہ_NV            0x02
#تعریف_کرو GL_GLYPH_HORIZONTAL_BEARING_X_ثنائی_ہندسہ_NV 0x04
#تعریف_کرو GL_GLYPH_HORIZONTAL_BEARING_Y_ثنائی_ہندسہ_NV 0x08
#تعریف_کرو GL_GLYPH_HORIZONTAL_BEARING_ADVANCE_ثنائی_ہندسہ_NV 0x10
#تعریف_کرو GL_GLYPH_VERTICAL_BEARING_X_ثنائی_ہندسہ_NV 0x20
#تعریف_کرو GL_GLYPH_VERTICAL_BEARING_Y_ثنائی_ہندسہ_NV 0x40
#تعریف_کرو GL_GLYPH_VERTICAL_BEARING_ADVANCE_ثنائی_ہندسہ_NV 0x80
#تعریف_کرو GL_GLYPH_HAS_KERNING_ثنائی_ہندسہ_NV       0x100
#تعریف_کرو GL_FONT_X_MIN_BOUNDS_ثنائی_ہندسہ_NV       0x00010000
#تعریف_کرو GL_FONT_Y_MIN_BOUNDS_ثنائی_ہندسہ_NV       0x00020000
#تعریف_کرو GL_FONT_X_MAX_BOUNDS_ثنائی_ہندسہ_NV       0x00040000
#تعریف_کرو GL_FONT_Y_MAX_BOUNDS_ثنائی_ہندسہ_NV       0x00080000
#تعریف_کرو GL_FONT_UNITS_فی_EM_ثنائی_ہندسہ_NV       0x00100000
#تعریف_کرو GL_FONT_ASCENDER_ثنائی_ہندسہ_NV           0x00200000
#تعریف_کرو GL_FONT_DESCENDER_ثنائی_ہندسہ_NV          0x00400000
#تعریف_کرو GL_FONT_اونچائی_ثنائی_ہندسہ_NV             0x00800000
#تعریف_کرو GL_FONT_MAX_ADVANCE_چوڑائی_ثنائی_ہندسہ_NV  0x01000000
#تعریف_کرو GL_FONT_MAX_ADVANCE_اونچائی_ثنائی_ہندسہ_NV 0x02000000
#تعریف_کرو GL_FONT_UNDERLINE_POSITION_ثنائی_ہندسہ_NV 0x04000000
#تعریف_کرو GL_FONT_UNDERLINE_THICKNESS_ثنائی_ہندسہ_NV 0x08000000
#تعریف_کرو GL_FONT_HAS_KERNING_ثنائی_ہندسہ_NV        0x10000000
#تعریف_کرو GL_ROUNDED_RECT_NV                0xE8
#تعریف_کرو GL_RELATIVE_ROUNDED_RECT_NV       0xE9
#تعریف_کرو GL_ROUNDED_RECT2_NV               0xEA
#تعریف_کرو GL_RELATIVE_ROUNDED_RECT2_NV      0xEB
#تعریف_کرو GL_ROUNDED_RECT4_NV               0xEC
#تعریف_کرو GL_RELATIVE_ROUNDED_RECT4_NV      0xED
#تعریف_کرو GL_ROUNDED_RECT8_NV               0xEE
#تعریف_کرو GL_RELATIVE_ROUNDED_RECT8_NV      0xEF
#تعریف_کرو GL_RELATIVE_RECT_NV               0xF7
#تعریف_کرو GL_FONT_GLYPHS_دستیاب_NV       0x9368
#تعریف_کرو GL_FONT_ہدف_UNAVAILABLE_NV     0x9369
#تعریف_کرو GL_FONT_UNAVAILABLE_NV            0x936A
#تعریف_کرو GL_FONT_UNINTELLIGIBLE_NV         0x936B
#تعریف_کرو GL_CONIC_خم_مقصد_NV              0x1A
#تعریف_کرو GL_RELATIVE_CONIC_خم_مقصد_NV     0x1B
#تعریف_کرو GL_FONT_عدد_GLYPH_INDICES_ثنائی_ہندسہ_NV  0x20000000
#تعریف_کرو GL_STANDARD_FONT_FORMAT_NV        0x936C
#تعریف_کرو GL_راستہ_PROJECTION_NV             0x1701
#تعریف_کرو GL_راستہ_MODELVIEW_NV              0x1700
#تعریف_کرو GL_راستہ_MODELVIEW_ڈھیر_گہرائی_NV  0x0BA3
#تعریف_کرو GL_راستہ_MODELVIEW_میٹرکس_NV       0x0BA6
#تعریف_کرو GL_راستہ_MAX_MODELVIEW_ڈھیر_گہرائی_NV 0x0D36
#تعریف_کرو GL_راستہ_TRANSPOSE_MODELVIEW_میٹرکس_NV 0x84E3
#تعریف_کرو GL_راستہ_PROJECTION_ڈھیر_گہرائی_NV 0x0BA4
#تعریف_کرو GL_راستہ_PROJECTION_میٹرکس_NV      0x0BA7
#تعریف_کرو GL_راستہ_MAX_PROJECTION_ڈھیر_گہرائی_NV 0x0D38
#تعریف_کرو GL_راستہ_TRANSPOSE_PROJECTION_میٹرکس_NV 0x84E4
#تعریف_کرو GL_FRAGMENT_داخلہ_NV              0x936D
قسمتعریف GLuint (GL_APIENTRYP PFNGLGENPATHSNVPROC) (GLsizei range);
قسمتعریف خالی (GL_APIENTRYP PFNGLDELETEPATHSNVPROC) (GLuint راستہ, GLsizei range);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLISPATHNVPROC) (GLuint راستہ);
قسمتعریف خالی (GL_APIENTRYP PFNGLPATHCOMMANDSNVPROC) (GLuint راستہ, GLsizei عدد_Commands, ثابت GLubyte *commands, GLsizei عدد_Coords, GLenum coordType, ثابت خالی *coords);
قسمتعریف خالی (GL_APIENTRYP PFNGLPATHCOORDSNVPROC) (GLuint راستہ, GLsizei عدد_Coords, GLenum coordType, ثابت خالی *coords);
قسمتعریف خالی (GL_APIENTRYP PFNGLPATHSUBCOMMANDSNVPROC) (GLuint راستہ, GLsizei command_آغاز, GLsizei commands_مقصد_Delete, GLsizei عدد_Commands, ثابت GLubyte *commands, GLsizei عدد_Coords, GLenum coordType, ثابت خالی *coords);
قسمتعریف خالی (GL_APIENTRYP PFNGLPATHSUBCOORDSNVPROC) (GLuint راستہ, GLsizei coord_آغاز, GLsizei عدد_Coords, GLenum coordType, ثابت خالی *coords);
قسمتعریف خالی (GL_APIENTRYP PFNGLPATHSTRINGNVPROC) (GLuint راستہ, GLenum format, GLsizei لمبائی, ثابت خالی *راستہ_String);
قسمتعریف خالی (GL_APIENTRYP PFNGLPATHGLYPHSNVPROC) (GLuint پہلا_راستہ_Name, GLenum font_ہدف, ثابت خالی *fontName, GLbitfield fontStyle, GLsizei عدد_Glyphs, GLenum type, ثابت خالی *charcodes, GLenum handleMissingGlyphs, GLuint راستہ_Parameter_Template, GLfloat emScale);
قسمتعریف خالی (GL_APIENTRYP PFNGLPATHGLYPHRANGENVPROC) (GLuint پہلا_راستہ_Name, GLenum font_ہدف, ثابت خالی *fontName, GLbitfield fontStyle, GLuint پہلا_Glyph, GLsizei عدد_Glyphs, GLenum handleMissingGlyphs, GLuint راستہ_Parameter_Template, GLfloat emScale);
قسمتعریف خالی (GL_APIENTRYP PFNGLWEIGHTPATHSNVPROC) (GLuint نتیجہ_راستہ, GLsizei عدد_Paths, ثابت GLuint *paths, ثابت GLfloat *weights);
قسمتعریف خالی (GL_APIENTRYP PFNGLCOPYPATHNVPROC) (GLuint نتیجہ_راستہ, GLuint src_راستہ);
قسمتعریف خالی (GL_APIENTRYP PFNGLINTERPOLATEPATHSNVPROC) (GLuint نتیجہ_راستہ, GLuint راستہ_A, GLuint راستہ_B, GLfloat وزن);
قسمتعریف خالی (GL_APIENTRYP PFNGLTRANSFORMPATHNVPROC) (GLuint نتیجہ_راستہ, GLuint src_راستہ, GLenum transformType, ثابت GLfloat *transform_اقدار);
قسمتعریف خالی (GL_APIENTRYP PFNGLPATHPARAMETERIVNVPROC) (GLuint راستہ, GLenum pname, ثابت GLint *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPATHPARAMETERINVPROC) (GLuint راستہ, GLenum pname, GLint قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPATHPARAMETERFVNVPROC) (GLuint راستہ, GLenum pname, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPATHPARAMETERFNVPROC) (GLuint راستہ, GLenum pname, GLfloat قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPATHDASHARRAYNVPROC) (GLuint راستہ, GLsizei dash_گنتی, ثابت GLfloat *dashArray);
قسمتعریف خالی (GL_APIENTRYP PFNGLPATHSTENCILFUNCNVPROC) (GLenum func, GLint ref, GLuint نقاب);
قسمتعریف خالی (GL_APIENTRYP PFNGLPATHSTENCILDEPTHOFFSETNVPROC) (GLfloat ضربی_عدد, GLfloat units);
قسمتعریف خالی (GL_APIENTRYP PFNGLSTENCILFILLPATHNVPROC) (GLuint راستہ, GLenum fill_منوال, GLuint نقاب);
قسمتعریف خالی (GL_APIENTRYP PFNGLSTENCILSTROKEPATHNVPROC) (GLuint راستہ, GLint reference, GLuint نقاب);
قسمتعریف خالی (GL_APIENTRYP PFNGLSTENCILFILLPATHINSTANCEDNVPROC) (GLsizei عدد_Paths, GLenum راستہ_Name_Type, ثابت خالی *paths, GLuint راستہ_بنیاد, GLenum fill_منوال, GLuint نقاب, GLenum transformType, ثابت GLfloat *transform_اقدار);
قسمتعریف خالی (GL_APIENTRYP PFNGLSTENCILSTROKEPATHINSTANCEDNVPROC) (GLsizei عدد_Paths, GLenum راستہ_Name_Type, ثابت خالی *paths, GLuint راستہ_بنیاد, GLint reference, GLuint نقاب, GLenum transformType, ثابت GLfloat *transform_اقدار);
قسمتعریف خالی (GL_APIENTRYP PFNGLPATHCOVERDEPTHFUNCNVPROC) (GLenum func);
قسمتعریف خالی (GL_APIENTRYP PFNGLCOVERFILLPATHNVPROC) (GLuint راستہ, GLenum cover_منوال);
قسمتعریف خالی (GL_APIENTRYP PFNGLCOVERSTROKEPATHNVPROC) (GLuint راستہ, GLenum cover_منوال);
قسمتعریف خالی (GL_APIENTRYP PFNGLCOVERFILLPATHINSTANCEDNVPROC) (GLsizei عدد_Paths, GLenum راستہ_Name_Type, ثابت خالی *paths, GLuint راستہ_بنیاد, GLenum cover_منوال, GLenum transformType, ثابت GLfloat *transform_اقدار);
قسمتعریف خالی (GL_APIENTRYP PFNGLCOVERSTROKEPATHINSTANCEDNVPROC) (GLsizei عدد_Paths, GLenum راستہ_Name_Type, ثابت خالی *paths, GLuint راستہ_بنیاد, GLenum cover_منوال, GLenum transformType, ثابت GLfloat *transform_اقدار);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETPATHPARAMETERIVNVPROC) (GLuint راستہ, GLenum pname, GLint *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETPATHPARAMETERFVNVPROC) (GLuint راستہ, GLenum pname, GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETPATHCOMMANDSNVPROC) (GLuint راستہ, GLubyte *commands);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETPATHCOORDSNVPROC) (GLuint راستہ, GLfloat *coords);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETPATHDASHARRAYNVPROC) (GLuint راستہ, GLfloat *dashArray);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETPATHMETRICSNVPROC) (GLbitfield metric_Query_نقاب, GLsizei عدد_Paths, GLenum راستہ_Name_Type, ثابت خالی *paths, GLuint راستہ_بنیاد, GLsizei stride, GLfloat *metrics);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETPATHMETRICRANGENVPROC) (GLbitfield metric_Query_نقاب, GLuint پہلا_راستہ_Name, GLsizei عدد_Paths, GLsizei stride, GLfloat *metrics);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETPATHSPACINGNVPROC) (GLenum راستہ_List_منوال, GLsizei عدد_Paths, GLenum راستہ_Name_Type, ثابت خالی *paths, GLuint راستہ_بنیاد, GLfloat advanceScale, GLfloat kerningScale, GLenum transformType, GLfloat *returnedSpacing);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLISPOINTINFILLPATHNVPROC) (GLuint راستہ, GLuint نقاب, GLfloat x, GLfloat y);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLISPOINTINSTROKEPATHNVPROC) (GLuint راستہ, GLfloat x, GLfloat y);
قسمتعریف GLfloat (GL_APIENTRYP PFNGLGETPATHLENGTHNVPROC) (GLuint راستہ, GLsizei آغاز_Segment, GLsizei عدد_Segments);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLPOINTALONGPATHNVPROC) (GLuint راستہ, GLsizei آغاز_Segment, GLsizei عدد_Segments, GLfloat فاصلہ, GLfloat *x, GLfloat *y, GLfloat *tangentX, GLfloat *tangentY);
قسمتعریف خالی (GL_APIENTRYP PFNGLMATRIXLOAD3X2FNVPROC) (GLenum میٹرکس_منوال, ثابت GLfloat *m);
قسمتعریف خالی (GL_APIENTRYP PFNGLMATRIXLOAD3X3FNVPROC) (GLenum میٹرکس_منوال, ثابت GLfloat *m);
قسمتعریف خالی (GL_APIENTRYP PFNGLMATRIXLOADTRANSPOSE3X3FNVPROC) (GLenum میٹرکس_منوال, ثابت GLfloat *m);
قسمتعریف خالی (GL_APIENTRYP PFNGLMATRIXMULT3X2FNVPROC) (GLenum میٹرکس_منوال, ثابت GLfloat *m);
قسمتعریف خالی (GL_APIENTRYP PFNGLMATRIXMULT3X3FNVPROC) (GLenum میٹرکس_منوال, ثابت GLfloat *m);
قسمتعریف خالی (GL_APIENTRYP PFNGLMATRIXMULTTRANSPOSE3X3FNVPROC) (GLenum میٹرکس_منوال, ثابت GLfloat *m);
قسمتعریف خالی (GL_APIENTRYP PFNGLSTENCILTHENCOVERFILLPATHNVPROC) (GLuint راستہ, GLenum fill_منوال, GLuint نقاب, GLenum cover_منوال);
قسمتعریف خالی (GL_APIENTRYP PFNGLSTENCILTHENCOVERSTROKEPATHNVPROC) (GLuint راستہ, GLint reference, GLuint نقاب, GLenum cover_منوال);
قسمتعریف خالی (GL_APIENTRYP PFNGLSTENCILTHENCOVERFILLPATHINSTANCEDNVPROC) (GLsizei عدد_Paths, GLenum راستہ_Name_Type, ثابت خالی *paths, GLuint راستہ_بنیاد, GLenum fill_منوال, GLuint نقاب, GLenum cover_منوال, GLenum transformType, ثابت GLfloat *transform_اقدار);
قسمتعریف خالی (GL_APIENTRYP PFNGLSTENCILTHENCOVERSTROKEPATHINSTANCEDNVPROC) (GLsizei عدد_Paths, GLenum راستہ_Name_Type, ثابت خالی *paths, GLuint راستہ_بنیاد, GLint reference, GLuint نقاب, GLenum cover_منوال, GLenum transformType, ثابت GLfloat *transform_اقدار);
قسمتعریف GLenum (GL_APIENTRYP PFNGLPATHGLYPHINDEXRANGENVPROC) (GLenum font_ہدف, ثابت خالی *fontName, GLbitfield fontStyle, GLuint راستہ_Parameter_Template, GLfloat emScale, GLuint *بنیاد_And_گنتی);
قسمتعریف GLenum (GL_APIENTRYP PFNGLPATHGLYPHINDEXARRAYNVPROC) (GLuint پہلا_راستہ_Name, GLenum font_ہدف, ثابت خالی *fontName, GLbitfield fontStyle, GLuint پہلا_Glyph_اشاریہ, GLsizei عدد_Glyphs, GLuint راستہ_Parameter_Template, GLfloat emScale);
قسمتعریف GLenum (GL_APIENTRYP PFNGLPATHMEMORYGLYPHINDEXARRAYNVPROC) (GLuint پہلا_راستہ_Name, GLenum font_ہدف, GLsizeiptr font_سائز, ثابت خالی *font_ڈیٹا, GLsizei face_اشاریہ, GLuint پہلا_Glyph_اشاریہ, GLsizei عدد_Glyphs, GLuint راستہ_Parameter_Template, GLfloat emScale);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMPATHFRAGMENTINPUTGENNVPROC) (GLuint پروگرام, GLint location, GLenum gen_منوال, GLint components, ثابت GLfloat *coeffs);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETPROGRAMRESOURCEFVNVPROC) (GLuint پروگرام, GLenum پروگرام_Interface, GLuint اشاریہ, GLsizei prop_گنتی, ثابت GLenum *props, GLsizei گنتی, GLsizei *لمبائی, GLfloat *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLMATRIXFRUSTUMEXTPROC) (GLenum منوال, GLdouble بایاں, GLdouble دایاں, GLdouble bottom, GLdouble چوٹی, GLdouble zNear, GLdouble zFar);
قسمتعریف خالی (GL_APIENTRYP PFNGLMATRIXLOADIDENTITYEXTPROC) (GLenum منوال);
قسمتعریف خالی (GL_APIENTRYP PFNGLMATRIXLOADTRANSPOSEFEXTPROC) (GLenum منوال, ثابت GLfloat *m);
قسمتعریف خالی (GL_APIENTRYP PFNGLMATRIXLOADTRANSPOSEDEXTPROC) (GLenum منوال, ثابت GLdouble *m);
قسمتعریف خالی (GL_APIENTRYP PFNGLMATRIXLOADFEXTPROC) (GLenum منوال, ثابت GLfloat *m);
قسمتعریف خالی (GL_APIENTRYP PFNGLMATRIXLOADDEXTPROC) (GLenum منوال, ثابت GLdouble *m);
قسمتعریف خالی (GL_APIENTRYP PFNGLMATRIXMULTTRANSPOSEFEXTPROC) (GLenum منوال, ثابت GLfloat *m);
قسمتعریف خالی (GL_APIENTRYP PFNGLMATRIXMULTTRANSPOSEDEXTPROC) (GLenum منوال, ثابت GLdouble *m);
قسمتعریف خالی (GL_APIENTRYP PFNGLMATRIXMULTFEXTPROC) (GLenum منوال, ثابت GLfloat *m);
قسمتعریف خالی (GL_APIENTRYP PFNGLMATRIXMULTDEXTPROC) (GLenum منوال, ثابت GLdouble *m);
قسمتعریف خالی (GL_APIENTRYP PFNGLMATRIXORTHOEXTPROC) (GLenum منوال, GLdouble بایاں, GLdouble دایاں, GLdouble bottom, GLdouble چوٹی, GLdouble zNear, GLdouble zFar);
قسمتعریف خالی (GL_APIENTRYP PFNGLMATRIXPOPEXTPROC) (GLenum منوال);
قسمتعریف خالی (GL_APIENTRYP PFNGLMATRIXPUSHEXTPROC) (GLenum منوال);
قسمتعریف خالی (GL_APIENTRYP PFNGLMATRIXROTATEFEXTPROC) (GLenum منوال, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
قسمتعریف خالی (GL_APIENTRYP PFNGLMATRIXROTATEDEXTPROC) (GLenum منوال, GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
قسمتعریف خالی (GL_APIENTRYP PFNGLMATRIXSCALEFEXTPROC) (GLenum منوال, GLfloat x, GLfloat y, GLfloat z);
قسمتعریف خالی (GL_APIENTRYP PFNGLMATRIXSCALEDEXTPROC) (GLenum منوال, GLdouble x, GLdouble y, GLdouble z);
قسمتعریف خالی (GL_APIENTRYP PFNGLMATRIXTRANSLATEFEXTPROC) (GLenum منوال, GLfloat x, GLfloat y, GLfloat z);
قسمتعریف خالی (GL_APIENTRYP PFNGLMATRIXTRANSLATEDEXTPROC) (GLenum منوال, GLdouble x, GLdouble y, GLdouble z);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL GLuint GL_APIENTRY glGenPathsNV (GLsizei range);
GL_APICALL خالی GL_APIENTRY glDeletePathsNV (GLuint راستہ, GLsizei range);
GL_APICALL GLboolean GL_APIENTRY gl_Is_راستہ_NV (GLuint راستہ);
GL_APICALL خالی GL_APIENTRY gl_راستہ_Commands_NV (GLuint راستہ, GLsizei عدد_Commands, ثابت GLubyte *commands, GLsizei عدد_Coords, GLenum coordType, ثابت خالی *coords);
GL_APICALL خالی GL_APIENTRY gl_راستہ_Coords_NV (GLuint راستہ, GLsizei عدد_Coords, GLenum coordType, ثابت خالی *coords);
GL_APICALL خالی GL_APIENTRY gl_راستہ_Sub_Commands_NV (GLuint راستہ, GLsizei command_آغاز, GLsizei commands_مقصد_Delete, GLsizei عدد_Commands, ثابت GLubyte *commands, GLsizei عدد_Coords, GLenum coordType, ثابت خالی *coords);
GL_APICALL خالی GL_APIENTRY gl_راستہ_Sub_Coords_NV (GLuint راستہ, GLsizei coord_آغاز, GLsizei عدد_Coords, GLenum coordType, ثابت خالی *coords);
GL_APICALL خالی GL_APIENTRY gl_راستہ_String_NV (GLuint راستہ, GLenum format, GLsizei لمبائی, ثابت خالی *راستہ_String);
GL_APICALL خالی GL_APIENTRY gl_راستہ_Glyphs_NV (GLuint پہلا_راستہ_Name, GLenum font_ہدف, ثابت خالی *fontName, GLbitfield fontStyle, GLsizei عدد_Glyphs, GLenum type, ثابت خالی *charcodes, GLenum handleMissingGlyphs, GLuint راستہ_Parameter_Template, GLfloat emScale);
GL_APICALL خالی GL_APIENTRY gl_راستہ_Glyph_Range_NV (GLuint پہلا_راستہ_Name, GLenum font_ہدف, ثابت خالی *fontName, GLbitfield fontStyle, GLuint پہلا_Glyph, GLsizei عدد_Glyphs, GLenum handleMissingGlyphs, GLuint راستہ_Parameter_Template, GLfloat emScale);
GL_APICALL خالی GL_APIENTRY gl_وزن_Paths_NV (GLuint نتیجہ_راستہ, GLsizei عدد_Paths, ثابت GLuint *paths, ثابت GLfloat *weights);
GL_APICALL خالی GL_APIENTRY gl_Copy_راستہ_NV (GLuint نتیجہ_راستہ, GLuint src_راستہ);
GL_APICALL خالی GL_APIENTRY glInterpolatePathsNV (GLuint نتیجہ_راستہ, GLuint راستہ_A, GLuint راستہ_B, GLfloat وزن);
GL_APICALL خالی GL_APIENTRY gl_Transform_راستہ_NV (GLuint نتیجہ_راستہ, GLuint src_راستہ, GLenum transformType, ثابت GLfloat *transform_اقدار);
GL_APICALL خالی GL_APIENTRY gl_راستہ_Parameteriv_NV (GLuint راستہ, GLenum pname, ثابت GLint *قدر);
GL_APICALL خالی GL_APIENTRY gl_راستہ_Parameteri_NV (GLuint راستہ, GLenum pname, GLint قدر);
GL_APICALL خالی GL_APIENTRY gl_راستہ_Parameterfv_NV (GLuint راستہ, GLenum pname, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_راستہ_Parameterf_NV (GLuint راستہ, GLenum pname, GLfloat قدر);
GL_APICALL خالی GL_APIENTRY gl_راستہ_Dash_Array_NV (GLuint راستہ, GLsizei dash_گنتی, ثابت GLfloat *dashArray);
GL_APICALL خالی GL_APIENTRY gl_راستہ_Stencil_Func_NV (GLenum func, GLint ref, GLuint نقاب);
GL_APICALL خالی GL_APIENTRY gl_راستہ_Stencil_گہرائی_انحراف_NV (GLfloat ضربی_عدد, GLfloat units);
GL_APICALL خالی GL_APIENTRY gl_Stencil_Fill_راستہ_NV (GLuint راستہ, GLenum fill_منوال, GLuint نقاب);
GL_APICALL خالی GL_APIENTRY gl_Stencil_Stroke_راستہ_NV (GLuint راستہ, GLint reference, GLuint نقاب);
GL_APICALL خالی GL_APIENTRY gl_Stencil_Fill_راستہ_Instanced_NV (GLsizei عدد_Paths, GLenum راستہ_Name_Type, ثابت خالی *paths, GLuint راستہ_بنیاد, GLenum fill_منوال, GLuint نقاب, GLenum transformType, ثابت GLfloat *transform_اقدار);
GL_APICALL خالی GL_APIENTRY gl_Stencil_Stroke_راستہ_Instanced_NV (GLsizei عدد_Paths, GLenum راستہ_Name_Type, ثابت خالی *paths, GLuint راستہ_بنیاد, GLint reference, GLuint نقاب, GLenum transformType, ثابت GLfloat *transform_اقدار);
GL_APICALL خالی GL_APIENTRY gl_راستہ_Cover_گہرائی_Func_NV (GLenum func);
GL_APICALL خالی GL_APIENTRY gl_Cover_Fill_راستہ_NV (GLuint راستہ, GLenum cover_منوال);
GL_APICALL خالی GL_APIENTRY gl_Cover_Stroke_راستہ_NV (GLuint راستہ, GLenum cover_منوال);
GL_APICALL خالی GL_APIENTRY gl_Cover_Fill_راستہ_Instanced_NV (GLsizei عدد_Paths, GLenum راستہ_Name_Type, ثابت خالی *paths, GLuint راستہ_بنیاد, GLenum cover_منوال, GLenum transformType, ثابت GLfloat *transform_اقدار);
GL_APICALL خالی GL_APIENTRY gl_Cover_Stroke_راستہ_Instanced_NV (GLsizei عدد_Paths, GLenum راستہ_Name_Type, ثابت خالی *paths, GLuint راستہ_بنیاد, GLenum cover_منوال, GLenum transformType, ثابت GLfloat *transform_اقدار);
GL_APICALL خالی GL_APIENTRY gl_Get_راستہ_Parameteriv_NV (GLuint راستہ, GLenum pname, GLint *قدر);
GL_APICALL خالی GL_APIENTRY gl_Get_راستہ_Parameterfv_NV (GLuint راستہ, GLenum pname, GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_Get_راستہ_Commands_NV (GLuint راستہ, GLubyte *commands);
GL_APICALL خالی GL_APIENTRY gl_Get_راستہ_Coords_NV (GLuint راستہ, GLfloat *coords);
GL_APICALL خالی GL_APIENTRY gl_Get_راستہ_Dash_Array_NV (GLuint راستہ, GLfloat *dashArray);
GL_APICALL خالی GL_APIENTRY gl_Get_راستہ_Metrics_NV (GLbitfield metric_Query_نقاب, GLsizei عدد_Paths, GLenum راستہ_Name_Type, ثابت خالی *paths, GLuint راستہ_بنیاد, GLsizei stride, GLfloat *metrics);
GL_APICALL خالی GL_APIENTRY gl_Get_راستہ_Metric_Range_NV (GLbitfield metric_Query_نقاب, GLuint پہلا_راستہ_Name, GLsizei عدد_Paths, GLsizei stride, GLfloat *metrics);
GL_APICALL خالی GL_APIENTRY gl_Get_راستہ_Spacing_NV (GLenum راستہ_List_منوال, GLsizei عدد_Paths, GLenum راستہ_Name_Type, ثابت خالی *paths, GLuint راستہ_بنیاد, GLfloat advanceScale, GLfloat kerningScale, GLenum transformType, GLfloat *returnedSpacing);
GL_APICALL GLboolean GL_APIENTRY gl_Is_نقطہ_اندر_Fill_راستہ_NV (GLuint راستہ, GLuint نقاب, GLfloat x, GLfloat y);
GL_APICALL GLboolean GL_APIENTRY gl_Is_نقطہ_اندر_Stroke_راستہ_NV (GLuint راستہ, GLfloat x, GLfloat y);
GL_APICALL GLfloat GL_APIENTRY gl_Get_راستہ_لمبائی_NV (GLuint راستہ, GLsizei آغاز_Segment, GLsizei عدد_Segments);
GL_APICALL GLboolean GL_APIENTRY gl_نقطہ_Along_راستہ_NV (GLuint راستہ, GLsizei آغاز_Segment, GLsizei عدد_Segments, GLfloat فاصلہ, GLfloat *x, GLfloat *y, GLfloat *tangentX, GLfloat *tangentY);
GL_APICALL خالی GL_APIENTRY gl_میٹرکس_Load3x2f_NV (GLenum میٹرکس_منوال, ثابت GLfloat *m);
GL_APICALL خالی GL_APIENTRY gl_میٹرکس_Load3x3f_NV (GLenum میٹرکس_منوال, ثابت GLfloat *m);
GL_APICALL خالی GL_APIENTRY gl_میٹرکس_بھرو_Transpose3x3f_NV (GLenum میٹرکس_منوال, ثابت GLfloat *m);
GL_APICALL خالی GL_APIENTRY gl_میٹرکس_Mult3x2f_NV (GLenum میٹرکس_منوال, ثابت GLfloat *m);
GL_APICALL خالی GL_APIENTRY gl_میٹرکس_Mult3x3f_NV (GLenum میٹرکس_منوال, ثابت GLfloat *m);
GL_APICALL خالی GL_APIENTRY gl_میٹرکس_Mult_Transpose3x3f_NV (GLenum میٹرکس_منوال, ثابت GLfloat *m);
GL_APICALL خالی GL_APIENTRY gl_Stencil_Then_Cover_Fill_راستہ_NV (GLuint راستہ, GLenum fill_منوال, GLuint نقاب, GLenum cover_منوال);
GL_APICALL خالی GL_APIENTRY gl_Stencil_Then_Cover_Stroke_راستہ_NV (GLuint راستہ, GLint reference, GLuint نقاب, GLenum cover_منوال);
GL_APICALL خالی GL_APIENTRY gl_Stencil_Then_Cover_Fill_راستہ_Instanced_NV (GLsizei عدد_Paths, GLenum راستہ_Name_Type, ثابت خالی *paths, GLuint راستہ_بنیاد, GLenum fill_منوال, GLuint نقاب, GLenum cover_منوال, GLenum transformType, ثابت GLfloat *transform_اقدار);
GL_APICALL خالی GL_APIENTRY gl_Stencil_Then_Cover_Stroke_راستہ_Instanced_NV (GLsizei عدد_Paths, GLenum راستہ_Name_Type, ثابت خالی *paths, GLuint راستہ_بنیاد, GLint reference, GLuint نقاب, GLenum cover_منوال, GLenum transformType, ثابت GLfloat *transform_اقدار);
GL_APICALL GLenum GL_APIENTRY gl_راستہ_Glyph_اشاریہ_Range_NV (GLenum font_ہدف, ثابت خالی *fontName, GLbitfield fontStyle, GLuint راستہ_Parameter_Template, GLfloat emScale, GLuint *بنیاد_And_گنتی);
GL_APICALL GLenum GL_APIENTRY gl_راستہ_Glyph_اشاریہ_Array_NV (GLuint پہلا_راستہ_Name, GLenum font_ہدف, ثابت خالی *fontName, GLbitfield fontStyle, GLuint پہلا_Glyph_اشاریہ, GLsizei عدد_Glyphs, GLuint راستہ_Parameter_Template, GLfloat emScale);
GL_APICALL GLenum GL_APIENTRY gl_راستہ_حافظہ_Glyph_اشاریہ_Array_NV (GLuint پہلا_راستہ_Name, GLenum font_ہدف, GLsizeiptr font_سائز, ثابت خالی *font_ڈیٹا, GLsizei face_اشاریہ, GLuint پہلا_Glyph_اشاریہ, GLsizei عدد_Glyphs, GLuint راستہ_Parameter_Template, GLfloat emScale);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_راستہ_Fragment_داخلہ_Gen_NV (GLuint پروگرام, GLint location, GLenum gen_منوال, GLint components, ثابت GLfloat *coeffs);
GL_APICALL خالی GL_APIENTRY gl_Get_پروگرام_Resourcefv_NV (GLuint پروگرام, GLenum پروگرام_Interface, GLuint اشاریہ, GLsizei prop_گنتی, ثابت GLenum *props, GLsizei گنتی, GLsizei *لمبائی, GLfloat *params);
GL_APICALL خالی GL_APIENTRY gl_میٹرکس_Frustum_EXT (GLenum منوال, GLdouble بایاں, GLdouble دایاں, GLdouble bottom, GLdouble چوٹی, GLdouble zNear, GLdouble zFar);
GL_APICALL خالی GL_APIENTRY gl_میٹرکس_بھرو_شناختی_عنصر_EXT (GLenum منوال);
GL_APICALL خالی GL_APIENTRY gl_میٹرکس_بھرو_Transposef_EXT (GLenum منوال, ثابت GLfloat *m);
GL_APICALL خالی GL_APIENTRY gl_میٹرکس_بھرو_Transposed_EXT (GLenum منوال, ثابت GLdouble *m);
GL_APICALL خالی GL_APIENTRY gl_میٹرکس_Loadf_EXT (GLenum منوال, ثابت GLfloat *m);
GL_APICALL خالی GL_APIENTRY gl_میٹرکس_Loadd_EXT (GLenum منوال, ثابت GLdouble *m);
GL_APICALL خالی GL_APIENTRY gl_میٹرکس_Mult_Transposef_EXT (GLenum منوال, ثابت GLfloat *m);
GL_APICALL خالی GL_APIENTRY gl_میٹرکس_Mult_Transposed_EXT (GLenum منوال, ثابت GLdouble *m);
GL_APICALL خالی GL_APIENTRY gl_میٹرکس_Multf_EXT (GLenum منوال, ثابت GLfloat *m);
GL_APICALL خالی GL_APIENTRY gl_میٹرکس_Multd_EXT (GLenum منوال, ثابت GLdouble *m);
GL_APICALL خالی GL_APIENTRY gl_میٹرکس_Ortho_EXT (GLenum منوال, GLdouble بایاں, GLdouble دایاں, GLdouble bottom, GLdouble چوٹی, GLdouble zNear, GLdouble zFar);
GL_APICALL خالی GL_APIENTRY gl_میٹرکس_نکالو_EXT (GLenum منوال);
GL_APICALL خالی GL_APIENTRY gl_میٹرکس_ڈالو_EXT (GLenum منوال);
GL_APICALL خالی GL_APIENTRY gl_میٹرکس_Rotatef_EXT (GLenum منوال, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL خالی GL_APIENTRY gl_میٹرکس_Rotated_EXT (GLenum منوال, GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
GL_APICALL خالی GL_APIENTRY gl_میٹرکس_Scalef_EXT (GLenum منوال, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL خالی GL_APIENTRY gl_میٹرکس_Scaled_EXT (GLenum منوال, GLdouble x, GLdouble y, GLdouble z);
GL_APICALL خالی GL_APIENTRY gl_میٹرکس_Translatef_EXT (GLenum منوال, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL خالی GL_APIENTRY gl_میٹرکس_Translated_EXT (GLenum منوال, GLdouble x, GLdouble y, GLdouble z);
#اگر_ختم
#اگر_ختم /* GL_NV_path_rendering */

#اگر_غیر_تعریف_شدہ GL_NV_راستہ_rendering_shared_کنارہ
#تعریف_کرو GL_NV_راستہ_rendering_shared_کنارہ 1
#تعریف_کرو GL_SHARED_کنارہ_NV                 0xC0
#اگر_ختم /* GL_NV_path_rendering_shared_edge */

#اگر_غیر_تعریف_شدہ GL_NV_pixel_بفر_object
#تعریف_کرو GL_NV_pixel_بفر_object 1
#تعریف_کرو GL_PIXEL_PACK_بفر_NV           0x88EB
#تعریف_کرو GL_PIXEL_UNPACK_بفر_NV         0x88EC
#تعریف_کرو GL_PIXEL_PACK_بفر_BINDING_NV   0x88ED
#تعریف_کرو GL_PIXEL_UNPACK_بفر_BINDING_NV 0x88EF
#اگر_ختم /* GL_NV_pixel_buffer_object */

#اگر_غیر_تعریف_شدہ GL_NV_polygon_منوال
#تعریف_کرو GL_NV_polygon_منوال 1
#تعریف_کرو GL_POLYGON_منوال_NV                0x0B40
#تعریف_کرو GL_POLYGON_انحراف_نقطہ_NV        0x2A01
#تعریف_کرو GL_POLYGON_انحراف_سطر_NV         0x2A02
#تعریف_کرو GL_نقطہ_NV                       0x1B00
#تعریف_کرو GL_سطر_NV                        0x1B01
#تعریف_کرو GL_FILL_NV                        0x1B02
قسمتعریف خالی (GL_APIENTRYP PFNGLPOLYGONMODENVPROC) (GLenum face, GLenum منوال);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_Polygon_منوال_NV (GLenum face, GLenum منوال);
#اگر_ختم
#اگر_ختم /* GL_NV_polygon_mode */

#اگر_غیر_تعریف_شدہ GL_NV_primitive_shading_شرح
#تعریف_کرو GL_NV_primitive_shading_شرح 1
#تعریف_کرو GL_SHADING_شرح_IMAGE_فی_PRIMITIVE_NV 0x95B1
#تعریف_کرو GL_SHADING_شرح_IMAGE_PALETTE_گنتی_NV 0x95B2
#اگر_ختم /* GL_NV_primitive_shading_rate */

#اگر_غیر_تعریف_شدہ GL_NV_read_بفر
#تعریف_کرو GL_NV_read_بفر 1
#تعریف_کرو GL_READ_بفر_NV                 0x0C02
قسمتعریف خالی (GL_APIENTRYP PFNGLREADBUFFERNVPROC) (GLenum منوال);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_Read_بفر_NV (GLenum منوال);
#اگر_ختم
#اگر_ختم /* GL_NV_read_buffer */

#اگر_غیر_تعریف_شدہ GL_NV_read_بفر_front
#تعریف_کرو GL_NV_read_بفر_front 1
#اگر_ختم /* GL_NV_read_buffer_front */

#اگر_غیر_تعریف_شدہ GL_NV_read_گہرائی
#تعریف_کرو GL_NV_read_گہرائی 1
#اگر_ختم /* GL_NV_read_depth */

#اگر_غیر_تعریف_شدہ GL_NV_read_گہرائی_stencil
#تعریف_کرو GL_NV_read_گہرائی_stencil 1
#اگر_ختم /* GL_NV_read_depth_stencil */

#اگر_غیر_تعریف_شدہ GL_NV_read_stencil
#تعریف_کرو GL_NV_read_stencil 1
#اگر_ختم /* GL_NV_read_stencil */

#اگر_غیر_تعریف_شدہ GL_NV_representative_fragment_test
#تعریف_کرو GL_NV_representative_fragment_test 1
#تعریف_کرو GL_REPRESENTATIVE_FRAGMENT_TEST_NV 0x937F
#اگر_ختم /* GL_NV_representative_fragment_test */

#اگر_غیر_تعریف_شدہ GL_NV_sRGB_formats
#تعریف_کرو GL_NV_sRGB_formats 1
#تعریف_کرو GL_SLUMINANCE_NV                  0x8C46
#تعریف_کرو GL_SLUMINANCE_ALPHA_NV            0x8C44
#تعریف_کرو GL_SRGB8_NV                       0x8C41
#تعریف_کرو GL_SLUMINANCE8_NV                 0x8C47
#تعریف_کرو GL_SLUMINANCE8_ALPHA8_NV          0x8C45
#تعریف_کرو GL_COMPRESSED_SRGB_S3TC_DXT1_NV   0x8C4C
#تعریف_کرو GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_NV 0x8C4D
#تعریف_کرو GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_NV 0x8C4E
#تعریف_کرو GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_NV 0x8C4F
#تعریف_کرو GL_ETC1_SRGB8_NV                  0x88EE
#اگر_ختم /* GL_NV_sRGB_formats */

#اگر_غیر_تعریف_شدہ GL_NV_sample_locations
#تعریف_کرو GL_NV_sample_locations 1
#تعریف_کرو GL_SAMPLE_LOCATION_SUBPIXEL_بٹ_NV 0x933D
#تعریف_کرو GL_SAMPLE_LOCATION_PIXEL_GRID_چوڑائی_NV 0x933E
#تعریف_کرو GL_SAMPLE_LOCATION_PIXEL_GRID_اونچائی_NV 0x933F
#تعریف_کرو GL_PROGRAMMABLE_SAMPLE_LOCATION_جدول_سائز_NV 0x9340
#تعریف_کرو GL_SAMPLE_LOCATION_NV             0x8E50
#تعریف_کرو GL_PROGRAMMABLE_SAMPLE_LOCATION_NV 0x9341
#تعریف_کرو GL_FRAMEBUFFER_PROGRAMMABLE_SAMPLE_LOCATIONS_NV 0x9342
#تعریف_کرو GL_FRAMEBUFFER_SAMPLE_LOCATION_PIXEL_GRID_NV 0x9343
قسمتعریف خالی (GL_APIENTRYP PFNGLFRAMEBUFFERSAMPLELOCATIONSFVNVPROC) (GLenum ہدف, GLuint آغاز, GLsizei گنتی, ثابت GLfloat *v);
قسمتعریف خالی (GL_APIENTRYP PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVNVPROC) (GLuint framebuffer, GLuint آغاز, GLsizei گنتی, ثابت GLfloat *v);
قسمتعریف خالی (GL_APIENTRYP PFNGLRESOLVEDEPTHVALUESNVPROC) (خالی);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glFramebufferSampleLocationsfvNV (GLenum ہدف, GLuint آغاز, GLsizei گنتی, ثابت GLfloat *v);
GL_APICALL خالی GL_APIENTRY glNamedFramebufferSampleLocationsfvNV (GLuint framebuffer, GLuint آغاز, GLsizei گنتی, ثابت GLfloat *v);
GL_APICALL خالی GL_APIENTRY gl_Resolve_گہرائی_اقدار_NV (خالی);
#اگر_ختم
#اگر_ختم /* GL_NV_sample_locations */

#اگر_غیر_تعریف_شدہ GL_NV_sample_نقاب_override_coverage
#تعریف_کرو GL_NV_sample_نقاب_override_coverage 1
#اگر_ختم /* GL_NV_sample_mask_override_coverage */

#اگر_غیر_تعریف_شدہ GL_NV_scissor_exclusive
#تعریف_کرو GL_NV_scissor_exclusive 1
#تعریف_کرو GL_SCISSOR_TEST_EXCLUSIVE_NV      0x9555
#تعریف_کرو GL_SCISSOR_BOX_EXCLUSIVE_NV       0x9556
قسمتعریف خالی (GL_APIENTRYP PFNGLSCISSOREXCLUSIVENVPROC) (GLint x, GLint y, GLsizei چوڑائی, GLsizei اونچائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLSCISSOREXCLUSIVEARRAYVNVPROC) (GLuint پہلا, GLsizei گنتی, ثابت GLint *v);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glScissorExclusiveNV (GLint x, GLint y, GLsizei چوڑائی, GLsizei اونچائی);
GL_APICALL خالی GL_APIENTRY glScissorExclusiveArrayvNV (GLuint پہلا, GLsizei گنتی, ثابت GLint *v);
#اگر_ختم
#اگر_ختم /* GL_NV_scissor_exclusive */

#اگر_غیر_تعریف_شدہ GL_NV_shader_atomic_fp16_سمتیہ
#تعریف_کرو GL_NV_shader_atomic_fp16_سمتیہ 1
#اگر_ختم /* GL_NV_shader_atomic_fp16_vector */

#اگر_غیر_تعریف_شدہ GL_NV_shader_noperspective_interpolation
#تعریف_کرو GL_NV_shader_noperspective_interpolation 1
#اگر_ختم /* GL_NV_shader_noperspective_interpolation */

#اگر_غیر_تعریف_شدہ GL_NV_shader_subgroup_partitioned
#تعریف_کرو GL_NV_shader_subgroup_partitioned 1
#تعریف_کرو GL_SUBGROUP_FEATURE_PARTITIONED_ثنائی_ہندسہ_NV 0x00000100
#اگر_ختم /* GL_NV_shader_subgroup_partitioned */

#اگر_غیر_تعریف_شدہ GL_NV_shader_texture_footprint
#تعریف_کرو GL_NV_shader_texture_footprint 1
#اگر_ختم /* GL_NV_shader_texture_footprint */

#اگر_غیر_تعریف_شدہ GL_NV_shading_شرح_image
#تعریف_کرو GL_NV_shading_شرح_image 1
#تعریف_کرو GL_SHADING_شرح_IMAGE_NV          0x9563
#تعریف_کرو GL_SHADING_شرح_NO_INVOCATIONS_NV 0x9564
#تعریف_کرو GL_SHADING_شرح_1_INVOCATION_فی_PIXEL_NV 0x9565
#تعریف_کرو GL_SHADING_شرح_1_INVOCATION_فی_1_X2_PIXELS_NV 0x9566
#تعریف_کرو GL_SHADING_شرح_1_INVOCATION_فی_2_X1_PIXELS_NV 0x9567
#تعریف_کرو GL_SHADING_شرح_1_INVOCATION_فی_2_X2_PIXELS_NV 0x9568
#تعریف_کرو GL_SHADING_شرح_1_INVOCATION_فی_2_X4_PIXELS_NV 0x9569
#تعریف_کرو GL_SHADING_شرح_1_INVOCATION_فی_4_X2_PIXELS_NV 0x956A
#تعریف_کرو GL_SHADING_شرح_1_INVOCATION_فی_4_X4_PIXELS_NV 0x956B
#تعریف_کرو GL_SHADING_شرح_2_INVOCATIONS_فی_PIXEL_NV 0x956C
#تعریف_کرو GL_SHADING_شرح_4_INVOCATIONS_فی_PIXEL_NV 0x956D
#تعریف_کرو GL_SHADING_شرح_8_INVOCATIONS_فی_PIXEL_NV 0x956E
#تعریف_کرو GL_SHADING_شرح_16_INVOCATIONS_فی_PIXEL_NV 0x956F
#تعریف_کرو GL_SHADING_شرح_IMAGE_BINDING_NV  0x955B
#تعریف_کرو GL_SHADING_شرح_IMAGE_TEXEL_چوڑائی_NV 0x955C
#تعریف_کرو GL_SHADING_شرح_IMAGE_TEXEL_اونچائی_NV 0x955D
#تعریف_کرو GL_SHADING_شرح_IMAGE_PALETTE_سائز_NV 0x955E
#تعریف_کرو GL_MAX_COARSE_FRAGMENT_SAMPLES_NV 0x955F
#تعریف_کرو GL_SHADING_شرح_SAMPLE_ترتیب_DEFAULT_NV 0x95AE
#تعریف_کرو GL_SHADING_شرح_SAMPLE_ترتیب_PIXEL_MAJOR_NV 0x95AF
#تعریف_کرو GL_SHADING_شرح_SAMPLE_ترتیب_SAMPLE_MAJOR_NV 0x95B0
قسمتعریف خالی (GL_APIENTRYP PFNGLBINDSHADINGRATEIMAGENVPROC) (GLuint texture);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETSHADINGRATEIMAGEPALETTENVPROC) (GLuint viewport, GLuint اندراج_2, GLenum *شرح);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETSHADINGRATESAMPLELOCATIONIVNVPROC) (GLenum شرح, GLuint samples, GLuint اشاریہ, GLint *location);
قسمتعریف خالی (GL_APIENTRYP PFNGLSHADINGRATEIMAGEBARRIERNVPROC) (GLboolean synchronize);
قسمتعریف خالی (GL_APIENTRYP PFNGLSHADINGRATEIMAGEPALETTENVPROC) (GLuint viewport, GLuint پہلا, GLsizei گنتی, ثابت GLenum *rates);
قسمتعریف خالی (GL_APIENTRYP PFNGLSHADINGRATESAMPLEORDERNVPROC) (GLenum ترتیب);
قسمتعریف خالی (GL_APIENTRYP PFNGLSHADINGRATESAMPLEORDERCUSTOMNVPROC) (GLenum شرح, GLuint samples, ثابت GLint *locations);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_Bind_Shading_شرح_Image_NV (GLuint texture);
GL_APICALL خالی GL_APIENTRY gl_Get_Shading_شرح_Image_Palette_NV (GLuint viewport, GLuint اندراج_2, GLenum *شرح);
GL_APICALL خالی GL_APIENTRY gl_Get_Shading_شرح_Sample_Locationiv_NV (GLenum شرح, GLuint samples, GLuint اشاریہ, GLint *location);
GL_APICALL خالی GL_APIENTRY gl_Shading_شرح_Image_Barrier_NV (GLboolean synchronize);
GL_APICALL خالی GL_APIENTRY gl_Shading_شرح_Image_Palette_NV (GLuint viewport, GLuint پہلا, GLsizei گنتی, ثابت GLenum *rates);
GL_APICALL خالی GL_APIENTRY gl_Shading_شرح_Sample_ترتیب_NV (GLenum ترتیب);
GL_APICALL خالی GL_APIENTRY gl_Shading_شرح_Sample_ترتیب_Custom_NV (GLenum شرح, GLuint samples, ثابت GLint *locations);
#اگر_ختم
#اگر_ختم /* GL_NV_shading_rate_image */

#اگر_غیر_تعریف_شدہ GL_NV_shadow_samplers_array
#تعریف_کرو GL_NV_shadow_samplers_array 1
#تعریف_کرو GL_SAMPLER_2D_ARRAY_SHADOW_NV     0x8DC4
#اگر_ختم /* GL_NV_shadow_samplers_array */

#اگر_غیر_تعریف_شدہ GL_NV_shadow_samplers_cube
#تعریف_کرو GL_NV_shadow_samplers_cube 1
#تعریف_کرو GL_SAMPLER_CUBE_SHADOW_NV         0x8DC5
#اگر_ختم /* GL_NV_shadow_samplers_cube */

#اگر_غیر_تعریف_شدہ GL_NV_stereo_view_rendering
#تعریف_کرو GL_NV_stereo_view_rendering 1
#اگر_ختم /* GL_NV_stereo_view_rendering */

#اگر_غیر_تعریف_شدہ GL_NV_texture_barrier
#تعریف_کرو GL_NV_texture_barrier 1
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXTUREBARRIERNVPROC) (خالی);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glTextureBarrierNV (خالی);
#اگر_ختم
#اگر_ختم /* GL_NV_texture_barrier */

#اگر_غیر_تعریف_شدہ GL_NV_texture_border_clamp
#تعریف_کرو GL_NV_texture_border_clamp 1
#تعریف_کرو GL_TEXTURE_BORDER_COLOR_NV        0x1004
#تعریف_کرو GL_CLAMP_مقصد_BORDER_NV             0x812D
#اگر_ختم /* GL_NV_texture_border_clamp */

#اگر_غیر_تعریف_شدہ GL_NV_texture_compression_s3tc_update
#تعریف_کرو GL_NV_texture_compression_s3tc_update 1
#اگر_ختم /* GL_NV_texture_compression_s3tc_update */

#اگر_غیر_تعریف_شدہ GL_NV_texture_npot_2D_mipmap
#تعریف_کرو GL_NV_texture_npot_2D_mipmap 1
#اگر_ختم /* GL_NV_texture_npot_2D_mipmap */

#اگر_غیر_تعریف_شدہ GL_NV_timeline_semaphore
#تعریف_کرو GL_NV_timeline_semaphore 1
#تعریف_کرو GL_TIMELINE_SEMAPHORE_قدر_NV    0x9595
#تعریف_کرو GL_SEMAPHORE_TYPE_NV              0x95B3
#تعریف_کرو GL_SEMAPHORE_TYPE_ثنائی_NV       0x95B4
#تعریف_کرو GL_SEMAPHORE_TYPE_TIMELINE_NV     0x95B5
#تعریف_کرو GL_MAX_TIMELINE_SEMAPHORE_قدر_DIFFERENCE_NV 0x95B6
قسمتعریف خالی (GL_APIENTRYP PFNGLCREATESEMAPHORESNVPROC) (GLsizei n, GLuint *semaphores);
قسمتعریف خالی (GL_APIENTRYP PFNGLSEMAPHOREPARAMETERIVNVPROC) (GLuint semaphore, GLenum pname, ثابت GLint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETSEMAPHOREPARAMETERIVNVPROC) (GLuint semaphore, GLenum pname, GLint *params);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glCreateSemaphoresNV (GLsizei n, GLuint *semaphores);
GL_APICALL خالی GL_APIENTRY glSemaphoreParameterivNV (GLuint semaphore, GLenum pname, ثابت GLint *params);
GL_APICALL خالی GL_APIENTRY glGetSemaphoreParameterivNV (GLuint semaphore, GLenum pname, GLint *params);
#اگر_ختم
#اگر_ختم /* GL_NV_timeline_semaphore */

#اگر_غیر_تعریف_شدہ GL_NV_viewport_array
#تعریف_کرو GL_NV_viewport_array 1
#تعریف_کرو GL_MAX_VIEWPORTS_NV               0x825B
#تعریف_کرو GL_VIEWPORT_SUBPIXEL_بٹ_NV      0x825C
#تعریف_کرو GL_VIEWPORT_BOUNDS_RANGE_NV       0x825D
#تعریف_کرو GL_VIEWPORT_اشاریہ_PROVOKING_راس_NV 0x825F
قسمتعریف خالی (GL_APIENTRYP PFNGLVIEWPORTARRAYVNVPROC) (GLuint پہلا, GLsizei گنتی, ثابت GLfloat *v);
قسمتعریف خالی (GL_APIENTRYP PFNGLVIEWPORTINDEXEDFNVPROC) (GLuint اشاریہ, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
قسمتعریف خالی (GL_APIENTRYP PFNGLVIEWPORTINDEXEDFVNVPROC) (GLuint اشاریہ, ثابت GLfloat *v);
قسمتعریف خالی (GL_APIENTRYP PFNGLSCISSORARRAYVNVPROC) (GLuint پہلا, GLsizei گنتی, ثابت GLint *v);
قسمتعریف خالی (GL_APIENTRYP PFNGLSCISSORINDEXEDNVPROC) (GLuint اشاریہ, GLint بایاں, GLint bottom, GLsizei چوڑائی, GLsizei اونچائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLSCISSORINDEXEDVNVPROC) (GLuint اشاریہ, ثابت GLint *v);
قسمتعریف خالی (GL_APIENTRYP PFNGLDEPTHRANGEARRAYFVNVPROC) (GLuint پہلا, GLsizei گنتی, ثابت GLfloat *v);
قسمتعریف خالی (GL_APIENTRYP PFNGLDEPTHRANGEINDEXEDFNVPROC) (GLuint اشاریہ, GLfloat n, GLfloat f);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETFLOATI_VNVPROC) (GLenum ہدف, GLuint اشاریہ, GLfloat *ڈیٹا);
قسمتعریف خالی (GL_APIENTRYP PFNGLENABLEINVPROC) (GLenum ہدف, GLuint اشاریہ);
قسمتعریف خالی (GL_APIENTRYP PFNGLDISABLEINVPROC) (GLenum ہدف, GLuint اشاریہ);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLISENABLEDINVPROC) (GLenum ہدف, GLuint اشاریہ);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glViewportArrayvNV (GLuint پہلا, GLsizei گنتی, ثابت GLfloat *v);
GL_APICALL خالی GL_APIENTRY glViewportIndexedfNV (GLuint اشاریہ, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
GL_APICALL خالی GL_APIENTRY glViewportIndexedfvNV (GLuint اشاریہ, ثابت GLfloat *v);
GL_APICALL خالی GL_APIENTRY glScissorArrayvNV (GLuint پہلا, GLsizei گنتی, ثابت GLint *v);
GL_APICALL خالی GL_APIENTRY gl_Scissor_اشاریہ_دار_NV (GLuint اشاریہ, GLint بایاں, GLint bottom, GLsizei چوڑائی, GLsizei اونچائی);
GL_APICALL خالی GL_APIENTRY glScissorIndexedvNV (GLuint اشاریہ, ثابت GLint *v);
GL_APICALL خالی GL_APIENTRY gl_گہرائی_Range_Arrayfv_NV (GLuint پہلا, GLsizei گنتی, ثابت GLfloat *v);
GL_APICALL خالی GL_APIENTRY gl_گہرائی_Range_Indexedf_NV (GLuint اشاریہ, GLfloat n, GLfloat f);
GL_APICALL خالی GL_APIENTRY glGetFloati_vNV (GLenum ہدف, GLuint اشاریہ, GLfloat *ڈیٹا);
GL_APICALL خالی GL_APIENTRY glEnableiNV (GLenum ہدف, GLuint اشاریہ);
GL_APICALL خالی GL_APIENTRY glDisableiNV (GLenum ہدف, GLuint اشاریہ);
GL_APICALL GLboolean GL_APIENTRY glIsEnablediNV (GLenum ہدف, GLuint اشاریہ);
#اگر_ختم
#اگر_ختم /* GL_NV_viewport_array */

#اگر_غیر_تعریف_شدہ GL_NV_viewport_array2
#تعریف_کرو GL_NV_viewport_array2 1
#اگر_ختم /* GL_NV_viewport_array2 */

#اگر_غیر_تعریف_شدہ GL_NV_viewport_swizzle
#تعریف_کرو GL_NV_viewport_swizzle 1
#تعریف_کرو GL_VIEWPORT_SWIZZLE_مثبت_X_NV 0x9350
#تعریف_کرو GL_VIEWPORT_SWIZZLE_NEGATIVE_X_NV 0x9351
#تعریف_کرو GL_VIEWPORT_SWIZZLE_مثبت_Y_NV 0x9352
#تعریف_کرو GL_VIEWPORT_SWIZZLE_NEGATIVE_Y_NV 0x9353
#تعریف_کرو GL_VIEWPORT_SWIZZLE_مثبت_Z_NV 0x9354
#تعریف_کرو GL_VIEWPORT_SWIZZLE_NEGATIVE_Z_NV 0x9355
#تعریف_کرو GL_VIEWPORT_SWIZZLE_مثبت_W_NV 0x9356
#تعریف_کرو GL_VIEWPORT_SWIZZLE_NEGATIVE_W_NV 0x9357
#تعریف_کرو GL_VIEWPORT_SWIZZLE_X_NV          0x9358
#تعریف_کرو GL_VIEWPORT_SWIZZLE_Y_NV          0x9359
#تعریف_کرو GL_VIEWPORT_SWIZZLE_Z_NV          0x935A
#تعریف_کرو GL_VIEWPORT_SWIZZLE_W_NV          0x935B
قسمتعریف خالی (GL_APIENTRYP PFNGLVIEWPORTSWIZZLENVPROC) (GLuint اشاریہ, GLenum swizzlex, GLenum swizzley, GLenum swizzlez, GLenum swizzlew);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glViewportSwizzleNV (GLuint اشاریہ, GLenum swizzlex, GLenum swizzley, GLenum swizzlez, GLenum swizzlew);
#اگر_ختم
#اگر_ختم /* GL_NV_viewport_swizzle */

#اگر_غیر_تعریف_شدہ GL_OVR_multiview
#تعریف_کرو GL_OVR_multiview 1
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_عدد_VIEWS_OVR 0x9630
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_بنیاد_VIEW_اشاریہ_OVR 0x9632
#تعریف_کرو GL_MAX_VIEWS_OVR                  0x9631
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_VIEW_TARGETS_OVR 0x9633
قسمتعریف خالی (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREMULTIVIEWOVRPROC) (GLenum ہدف, GLenum attachment, GLuint texture, GLint level, GLint بنیاد_View_اشاریہ, GLsizei عدد_Views_2);
قسمتعریف خالی (GL_APIENTRYP PFNGLNAMEDFRAMEBUFFERTEXTUREMULTIVIEWOVRPROC) (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint بنیاد_View_اشاریہ, GLsizei عدد_Views_2);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glFramebufferTextureMultiviewOVR (GLenum ہدف, GLenum attachment, GLuint texture, GLint level, GLint بنیاد_View_اشاریہ, GLsizei عدد_Views_2);
GL_APICALL خالی GL_APIENTRY glNamedFramebufferTextureMultiviewOVR (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint بنیاد_View_اشاریہ, GLsizei عدد_Views_2);
#اگر_ختم
#اگر_ختم /* GL_OVR_multiview */

#اگر_غیر_تعریف_شدہ GL_OVR_multiview2
#تعریف_کرو GL_OVR_multiview2 1
#اگر_ختم /* GL_OVR_multiview2 */

#اگر_غیر_تعریف_شدہ GL_OVR_multiview_multisampled_render_مقصد_texture
#تعریف_کرو GL_OVR_multiview_multisampled_render_مقصد_texture 1
قسمتعریف خالی (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREMULTISAMPLEMULTIVIEWOVRPROC) (GLenum ہدف, GLenum attachment, GLuint texture, GLint level, GLsizei samples, GLint بنیاد_View_اشاریہ, GLsizei عدد_Views_2);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glFramebufferTextureMultisampleMultiviewOVR (GLenum ہدف, GLenum attachment, GLuint texture, GLint level, GLsizei samples, GLint بنیاد_View_اشاریہ, GLsizei عدد_Views_2);
#اگر_ختم
#اگر_ختم /* GL_OVR_multiview_multisampled_render_to_texture */

#اگر_غیر_تعریف_شدہ GL_QCOM_YUV_texture_gather
#تعریف_کرو GL_QCOM_YUV_texture_gather 1
#اگر_ختم /* GL_QCOM_YUV_texture_gather */

#اگر_غیر_تعریف_شدہ GL_QCOM_alpha_test
#تعریف_کرو GL_QCOM_alpha_test 1
#تعریف_کرو GL_ALPHA_TEST_QCOM                0x0BC0
#تعریف_کرو GL_ALPHA_TEST_FUNC_QCOM           0x0BC1
#تعریف_کرو GL_ALPHA_TEST_REF_QCOM            0x0BC2
قسمتعریف خالی (GL_APIENTRYP PFNGLALPHAFUNCQCOMPROC) (GLenum func, GLclampf ref);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glAlphaFuncQCOM (GLenum func, GLclampf ref);
#اگر_ختم
#اگر_ختم /* GL_QCOM_alpha_test */

#اگر_غیر_تعریف_شدہ GL_QCOM_binning_control
#تعریف_کرو GL_QCOM_binning_control 1
#تعریف_کرو GL_BINNING_CONTROL_HINT_QCOM      0x8FB0
#تعریف_کرو GL_CPU_OPTIMIZED_QCOM             0x8FB1
#تعریف_کرو GL_GPU_OPTIMIZED_QCOM             0x8FB2
#تعریف_کرو GL_RENDER_براہ_راست_مقصد_FRAMEBUFFER_QCOM 0x8FB3
#اگر_ختم /* GL_QCOM_binning_control */

#اگر_غیر_تعریف_شدہ GL_QCOM_driver_control
#تعریف_کرو GL_QCOM_driver_control 1
قسمتعریف خالی (GL_APIENTRYP PFNGLGETDRIVERCONTROLSQCOMPROC) (GLint *عدد, GLsizei سائز, GLuint *driverControls);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETDRIVERCONTROLSTRINGQCOMPROC) (GLuint driverControl, GLsizei buf_سائز, GLsizei *لمبائی, GLchar *driverControlString);
قسمتعریف خالی (GL_APIENTRYP PFNGLENABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
قسمتعریف خالی (GL_APIENTRYP PFNGLDISABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glGetDriverControlsQCOM (GLint *عدد, GLsizei سائز, GLuint *driverControls);
GL_APICALL خالی GL_APIENTRY glGetDriverControlStringQCOM (GLuint driverControl, GLsizei buf_سائز, GLsizei *لمبائی, GLchar *driverControlString);
GL_APICALL خالی GL_APIENTRY glEnableDriverControlQCOM (GLuint driverControl);
GL_APICALL خالی GL_APIENTRY glDisableDriverControlQCOM (GLuint driverControl);
#اگر_ختم
#اگر_ختم /* GL_QCOM_driver_control */

#اگر_غیر_تعریف_شدہ GL_QCOM_extended_get
#تعریف_کرو GL_QCOM_extended_get 1
#تعریف_کرو GL_TEXTURE_چوڑائی_QCOM             0x8BD2
#تعریف_کرو GL_TEXTURE_اونچائی_QCOM            0x8BD3
#تعریف_کرو GL_TEXTURE_گہرائی_QCOM             0x8BD4
#تعریف_کرو GL_TEXTURE_اندرونی_FORMAT_QCOM   0x8BD5
#تعریف_کرو GL_TEXTURE_FORMAT_QCOM            0x8BD6
#تعریف_کرو GL_TEXTURE_TYPE_QCOM              0x8BD7
#تعریف_کرو GL_TEXTURE_IMAGE_VALID_QCOM       0x8BD8
#تعریف_کرو GL_TEXTURE_عدد_سطحیں_QCOM        0x8BD9
#تعریف_کرو GL_TEXTURE_ہدف_QCOM            0x8BDA
#تعریف_کرو GL_TEXTURE_OBJECT_VALID_QCOM      0x8BDB
#تعریف_کرو GL_STATE_RESTORE                  0x8BDC
قسمتعریف خالی (GL_APIENTRYP PFNGLEXTGETTEXTURESQCOMPROC) (GLuint *textures, GLint maxTextures, GLint *عدد_Textures);
قسمتعریف خالی (GL_APIENTRYP PFNGLEXTGETBUFFERSQCOMPROC) (GLuint *buffers, GLint maxBuffers, GLint *عدد_Buffers);
قسمتعریف خالی (GL_APIENTRYP PFNGLEXTGETRENDERBUFFERSQCOMPROC) (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *عدد_Renderbuffers);
قسمتعریف خالی (GL_APIENTRYP PFNGLEXTGETFRAMEBUFFERSQCOMPROC) (GLuint *framebuffers, GLint maxFramebuffers, GLint *عدد_Framebuffers);
قسمتعریف خالی (GL_APIENTRYP PFNGLEXTGETTEXLEVELPARAMETERIVQCOMPROC) (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLEXTTEXOBJECTSTATEOVERRIDEIQCOMPROC) (GLenum ہدف, GLenum pname, GLint param);
قسمتعریف خالی (GL_APIENTRYP PFNGLEXTGETTEXSUBIMAGEQCOMPROC) (GLenum ہدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLenum format, GLenum type, خالی *texels);
قسمتعریف خالی (GL_APIENTRYP PFNGLEXTGETBUFFERPOINTERVQCOMPROC) (GLenum ہدف, خالی **params);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glExtGetTexturesQCOM (GLuint *textures, GLint maxTextures, GLint *عدد_Textures);
GL_APICALL خالی GL_APIENTRY glExtGetBuffersQCOM (GLuint *buffers, GLint maxBuffers, GLint *عدد_Buffers);
GL_APICALL خالی GL_APIENTRY glExtGetRenderbuffersQCOM (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *عدد_Renderbuffers);
GL_APICALL خالی GL_APIENTRY glExtGetFramebuffersQCOM (GLuint *framebuffers, GLint maxFramebuffers, GLint *عدد_Framebuffers);
GL_APICALL خالی GL_APIENTRY glExtGetTexLevelParameterivQCOM (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
GL_APICALL خالی GL_APIENTRY glExtTexObjectStateOverrideiQCOM (GLenum ہدف, GLenum pname, GLint param);
GL_APICALL خالی GL_APIENTRY glExtGetTexSubImageQCOM (GLenum ہدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLenum format, GLenum type, خالی *texels);
GL_APICALL خالی GL_APIENTRY gl_Ext_Get_بفر_Pointerv_QCOM (GLenum ہدف, خالی **params);
#اگر_ختم
#اگر_ختم /* GL_QCOM_extended_get */

#اگر_غیر_تعریف_شدہ GL_QCOM_extended_get2
#تعریف_کرو GL_QCOM_extended_get2 1
قسمتعریف خالی (GL_APIENTRYP PFNGLEXTGETSHADERSQCOMPROC) (GLuint *shaders, GLint maxShaders, GLint *عدد_Shaders);
قسمتعریف خالی (GL_APIENTRYP PFNGLEXTGETPROGRAMSQCOMPROC) (GLuint *programs, GLint maxPrograms, GLint *عدد_Programs);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLEXTISPROGRAMBINARYQCOMPROC) (GLuint پروگرام);
قسمتعریف خالی (GL_APIENTRYP PFNGLEXTGETPROGRAMBINARYSOURCEQCOMPROC) (GLuint پروگرام, GLenum shadertype, GLchar *ماخذ, GLint *لمبائی);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glExtGetShadersQCOM (GLuint *shaders, GLint maxShaders, GLint *عدد_Shaders);
GL_APICALL خالی GL_APIENTRY glExtGetProgramsQCOM (GLuint *programs, GLint maxPrograms, GLint *عدد_Programs);
GL_APICALL GLboolean GL_APIENTRY gl_Ext_Is_پروگرام_ثنائی_QCOM (GLuint پروگرام);
GL_APICALL خالی GL_APIENTRY gl_Ext_Get_پروگرام_ثنائی_ماخذ_QCOM (GLuint پروگرام, GLenum shadertype, GLchar *ماخذ, GLint *لمبائی);
#اگر_ختم
#اگر_ختم /* GL_QCOM_extended_get2 */

#اگر_غیر_تعریف_شدہ GL_QCOM_چوکھٹا_extrapolation
#تعریف_کرو GL_QCOM_چوکھٹا_extrapolation 1
قسمتعریف خالی (GL_APIENTRYP PFNGLEXTRAPOLATETEX2DQCOMPROC) (GLuint src1, GLuint src2, GLuint output, GLfloat scale_ضربی_عدد);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glExtrapolateTex2DQCOM (GLuint src1, GLuint src2, GLuint output, GLfloat scale_ضربی_عدد);
#اگر_ختم
#اگر_ختم /* GL_QCOM_frame_extrapolation */

#اگر_غیر_تعریف_شدہ GL_QCOM_framebuffer_foveated
#تعریف_کرو GL_QCOM_framebuffer_foveated 1
#تعریف_کرو GL_FOVEATION_ENABLE_ثنائی_ہندسہ_QCOM      0x00000001
#تعریف_کرو GL_FOVEATION_SCALED_BIN_طریقہ_ثنائی_ہندسہ_QCOM 0x00000002
قسمتعریف خالی (GL_APIENTRYP PFNGLFRAMEBUFFERFOVEATIONCONFIGQCOMPROC) (GLuint framebuffer, GLuint عدد_Layers, GLuint focal_Points_فی_Layer, GLuint requestedFeatures, GLuint *providedFeatures);
قسمتعریف خالی (GL_APIENTRYP PFNGLFRAMEBUFFERFOVEATIONPARAMETERSQCOMPROC) (GLuint framebuffer, GLuint layer, GLuint focal_نقطہ, GLfloat focalX, GLfloat focalY, GLfloat gainX, GLfloat gainY, GLfloat foveaArea);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glFramebufferFoveationConfigQCOM (GLuint framebuffer, GLuint عدد_Layers, GLuint focal_Points_فی_Layer, GLuint requestedFeatures, GLuint *providedFeatures);
GL_APICALL خالی GL_APIENTRY glFramebufferFoveationParametersQCOM (GLuint framebuffer, GLuint layer, GLuint focal_نقطہ, GLfloat focalX, GLfloat focalY, GLfloat gainX, GLfloat gainY, GLfloat foveaArea);
#اگر_ختم
#اگر_ختم /* GL_QCOM_framebuffer_foveated */

#اگر_غیر_تعریف_شدہ GL_QCOM_motion_estimation
#تعریف_کرو GL_QCOM_motion_estimation 1
#تعریف_کرو GL_MOTION_ESTIMATION_تلاش_بلاک_X_QCOM 0x8C90
#تعریف_کرو GL_MOTION_ESTIMATION_تلاش_بلاک_Y_QCOM 0x8C91
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXESTIMATEMOTIONQCOMPROC) (GLuint ref, GLuint ہدف, GLuint output);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXESTIMATEMOTIONREGIONSQCOMPROC) (GLuint ref, GLuint ہدف, GLuint output, GLuint نقاب);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glTexEstimateMotionQCOM (GLuint ref, GLuint ہدف, GLuint output);
GL_APICALL خالی GL_APIENTRY glTexEstimateMotionRegionsQCOM (GLuint ref, GLuint ہدف, GLuint output, GLuint نقاب);
#اگر_ختم
#اگر_ختم /* GL_QCOM_motion_estimation */

#اگر_غیر_تعریف_شدہ GL_QCOM_perfmon_global_منوال
#تعریف_کرو GL_QCOM_perfmon_global_منوال 1
#تعریف_کرو GL_PERFMON_GLOBAL_منوال_QCOM       0x8FA0
#اگر_ختم /* GL_QCOM_perfmon_global_mode */

#اگر_غیر_تعریف_شدہ GL_QCOM_render_sRGB_R8_RG8
#تعریف_کرو GL_QCOM_render_sRGB_R8_RG8 1
#اگر_ختم /* GL_QCOM_render_sRGB_R8_RG8 */

#اگر_غیر_تعریف_شدہ GL_QCOM_render_shared_exponent
#تعریف_کرو GL_QCOM_render_shared_exponent 1
#اگر_ختم /* GL_QCOM_render_shared_exponent */

#اگر_غیر_تعریف_شدہ GL_QCOM_shader_framebuffer_fetch_noncoherent
#تعریف_کرو GL_QCOM_shader_framebuffer_fetch_noncoherent 1
#تعریف_کرو GL_FRAMEBUFFER_FETCH_NONCOHERENT_QCOM 0x96A2
قسمتعریف خالی (GL_APIENTRYP PFNGLFRAMEBUFFERFETCHBARRIERQCOMPROC) (خالی);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glFramebufferFetchBarrierQCOM (خالی);
#اگر_ختم
#اگر_ختم /* GL_QCOM_shader_framebuffer_fetch_noncoherent */

#اگر_غیر_تعریف_شدہ GL_QCOM_shader_framebuffer_fetch_شرح
#تعریف_کرو GL_QCOM_shader_framebuffer_fetch_شرح 1
#اگر_ختم /* GL_QCOM_shader_framebuffer_fetch_rate */

#اگر_غیر_تعریف_شدہ GL_QCOM_shading_شرح
#تعریف_کرو GL_QCOM_shading_شرح 1
#تعریف_کرو GL_SHADING_شرح_QCOM              0x96A4
#تعریف_کرو GL_SHADING_شرح_PRESERVE_ASPECT_تناسب_QCOM 0x96A5
#تعریف_کرو GL_SHADING_شرح_1_X1_PIXELS_QCOM   0x96A6
#تعریف_کرو GL_SHADING_شرح_1_X2_PIXELS_QCOM   0x96A7
#تعریف_کرو GL_SHADING_شرح_2_X1_PIXELS_QCOM   0x96A8
#تعریف_کرو GL_SHADING_شرح_2_X2_PIXELS_QCOM   0x96A9
#تعریف_کرو GL_SHADING_شرح_4_X2_PIXELS_QCOM   0x96AC
#تعریف_کرو GL_SHADING_شرح_4_X4_PIXELS_QCOM   0x96AE
قسمتعریف خالی (GL_APIENTRYP PFNGLSHADINGRATEQCOMPROC) (GLenum شرح);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_Shading_شرح_QCOM (GLenum شرح);
#اگر_ختم
#اگر_ختم /* GL_QCOM_shading_rate */

#اگر_غیر_تعریف_شدہ GL_QCOM_texture_foveated
#تعریف_کرو GL_QCOM_texture_foveated 1
#تعریف_کرو GL_TEXTURE_FOVEATED_FEATURE_بٹ_QCOM 0x8BFB
#تعریف_کرو GL_TEXTURE_FOVEATED_MIN_PIXEL_DENSITY_QCOM 0x8BFC
#تعریف_کرو GL_TEXTURE_FOVEATED_FEATURE_QUERY_QCOM 0x8BFD
#تعریف_کرو GL_TEXTURE_FOVEATED_عدد_FOCAL_POINTS_QUERY_QCOM 0x8BFE
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_FOVEATION_QCOM 0x8BFF
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXTUREFOVEATIONPARAMETERSQCOMPROC) (GLuint texture, GLuint layer, GLuint focal_نقطہ, GLfloat focalX, GLfloat focalY, GLfloat gainX, GLfloat gainY, GLfloat foveaArea);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glTextureFoveationParametersQCOM (GLuint texture, GLuint layer, GLuint focal_نقطہ, GLfloat focalX, GLfloat focalY, GLfloat gainX, GLfloat gainY, GLfloat foveaArea);
#اگر_ختم
#اگر_ختم /* GL_QCOM_texture_foveated */

#اگر_غیر_تعریف_شدہ GL_QCOM_texture_foveated2
#تعریف_کرو GL_QCOM_texture_foveated2 1
#تعریف_کرو GL_TEXTURE_FOVEATED_CUTOFF_DENSITY_QCOM 0x96A0
#اگر_ختم /* GL_QCOM_texture_foveated2 */

#اگر_غیر_تعریف_شدہ GL_QCOM_texture_foveated_subsampled_layout
#تعریف_کرو GL_QCOM_texture_foveated_subsampled_layout 1
#تعریف_کرو GL_FOVEATION_SUBSAMPLED_LAYOUT_طریقہ_ثنائی_ہندسہ_QCOM 0x00000004
#تعریف_کرو GL_MAX_SHADER_SUBSAMPLED_IMAGE_UNITS_QCOM 0x8FA1
#اگر_ختم /* GL_QCOM_texture_foveated_subsampled_layout */

#اگر_غیر_تعریف_شدہ GL_QCOM_texture_lod_bias
#تعریف_کرو GL_QCOM_texture_lod_bias 1
#تعریف_کرو GL_TEXTURE_LOD_BIAS_QCOM          0x8C96
#اگر_ختم /* GL_QCOM_texture_lod_bias */

#اگر_غیر_تعریف_شدہ GL_QCOM_tiled_rendering
#تعریف_کرو GL_QCOM_tiled_rendering 1
#تعریف_کرو GL_COLOR_بفر_BIT0_QCOM         0x00000001
#تعریف_کرو GL_COLOR_بفر_BIT1_QCOM         0x00000002
#تعریف_کرو GL_COLOR_بفر_BIT2_QCOM         0x00000004
#تعریف_کرو GL_COLOR_بفر_BIT3_QCOM         0x00000008
#تعریف_کرو GL_COLOR_بفر_BIT4_QCOM         0x00000010
#تعریف_کرو GL_COLOR_بفر_BIT5_QCOM         0x00000020
#تعریف_کرو GL_COLOR_بفر_BIT6_QCOM         0x00000040
#تعریف_کرو GL_COLOR_بفر_BIT7_QCOM         0x00000080
#تعریف_کرو GL_گہرائی_بفر_BIT0_QCOM         0x00000100
#تعریف_کرو GL_گہرائی_بفر_BIT1_QCOM         0x00000200
#تعریف_کرو GL_گہرائی_بفر_BIT2_QCOM         0x00000400
#تعریف_کرو GL_گہرائی_بفر_BIT3_QCOM         0x00000800
#تعریف_کرو GL_گہرائی_بفر_BIT4_QCOM         0x00001000
#تعریف_کرو GL_گہرائی_بفر_BIT5_QCOM         0x00002000
#تعریف_کرو GL_گہرائی_بفر_BIT6_QCOM         0x00004000
#تعریف_کرو GL_گہرائی_بفر_BIT7_QCOM         0x00008000
#تعریف_کرو GL_STENCIL_بفر_BIT0_QCOM       0x00010000
#تعریف_کرو GL_STENCIL_بفر_BIT1_QCOM       0x00020000
#تعریف_کرو GL_STENCIL_بفر_BIT2_QCOM       0x00040000
#تعریف_کرو GL_STENCIL_بفر_BIT3_QCOM       0x00080000
#تعریف_کرو GL_STENCIL_بفر_BIT4_QCOM       0x00100000
#تعریف_کرو GL_STENCIL_بفر_BIT5_QCOM       0x00200000
#تعریف_کرو GL_STENCIL_بفر_BIT6_QCOM       0x00400000
#تعریف_کرو GL_STENCIL_بفر_BIT7_QCOM       0x00800000
#تعریف_کرو GL_MULTISAMPLE_بفر_BIT0_QCOM   0x01000000
#تعریف_کرو GL_MULTISAMPLE_بفر_BIT1_QCOM   0x02000000
#تعریف_کرو GL_MULTISAMPLE_بفر_BIT2_QCOM   0x04000000
#تعریف_کرو GL_MULTISAMPLE_بفر_BIT3_QCOM   0x08000000
#تعریف_کرو GL_MULTISAMPLE_بفر_BIT4_QCOM   0x10000000
#تعریف_کرو GL_MULTISAMPLE_بفر_BIT5_QCOM   0x20000000
#تعریف_کرو GL_MULTISAMPLE_بفر_BIT6_QCOM   0x40000000
#تعریف_کرو GL_MULTISAMPLE_بفر_BIT7_QCOM   0x80000000
قسمتعریف خالی (GL_APIENTRYP PFNGLSTARTTILINGQCOMPROC) (GLuint x, GLuint y, GLuint چوڑائی, GLuint اونچائی, GLbitfield preserve_نقاب);
قسمتعریف خالی (GL_APIENTRYP PFNGLENDTILINGQCOMPROC) (GLbitfield preserve_نقاب);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_آغاز_Tiling_QCOM (GLuint x, GLuint y, GLuint چوڑائی, GLuint اونچائی, GLbitfield preserve_نقاب);
GL_APICALL خالی GL_APIENTRY gl_انتہا_Tiling_QCOM (GLbitfield preserve_نقاب);
#اگر_ختم
#اگر_ختم /* GL_QCOM_tiled_rendering */

#اگر_غیر_تعریف_شدہ GL_QCOM_writeonly_rendering
#تعریف_کرو GL_QCOM_writeonly_rendering 1
#تعریف_کرو GL_WRITEONLY_RENDERING_QCOM       0x8823
#اگر_ختم /* GL_QCOM_writeonly_rendering */

#اگر_غیر_تعریف_شدہ GL_QCOM_ycbcr_degamma
#تعریف_کرو GL_QCOM_ycbcr_degamma 1
#تعریف_کرو GL_TEXTURE_Y_DEGAMMA_QCOM         0x9710
#تعریف_کرو GL_TEXTURE_CBCR_DEGAMMA_QCOM      0x9711
#اگر_ختم /* GL_QCOM_ycbcr_degamma */

#اگر_غیر_تعریف_شدہ GL_VIV_shader_ثنائی
#تعریف_کرو GL_VIV_shader_ثنائی 1
#تعریف_کرو GL_SHADER_ثنائی_VIV              0x8FC4
#اگر_ختم /* GL_VIV_shader_binary */

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم
