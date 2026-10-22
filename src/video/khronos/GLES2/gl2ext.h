#که_نه_تعریف_شوی __gles2_gl2ext_h_
#تعریف_کړه __gles2_gl2ext_h_ 1

#که_تعریف_شوی __cplusplus
خارجي "C" {
#د_که_پای

/*
** Copyright 2013-2026 The Khronos Group Inc.
** SPDX-License-Identifier: MIT
**
** This header is generated from the Khronos OpenGL / OpenGL ES XML
** API Registry. The current version of the Registry, generator scripts
** used to make the header, and the header can be found at
**   https://github.com/KhronosGroup/OpenGL-Registry
*/

#که_نه_تعریف_شوی GL_APIENTRYP
#تعریف_کړه GL_APIENTRYP GL_APIENTRY*
#د_که_پای

#تعریف_کړه GL_GLEXT_نسخه 20260803

/* Generated C header for:
 * API: gles2
 * Profile: common
 * Versions considered: 2\.[0-9]
 * Versions emitted: _nomatch_^
 * Default extensions included: gles2
 * Additional extensions included: _nomatch_^
 * Extensions removed: _nomatch_^
 */

#که_نه_تعریف_شوی GL_KHR_blend_equation_advanced
#تعریف_کړه GL_KHR_blend_equation_advanced 1
#تعریف_کړه GL_MULTIPLY_KHR                   0x9294
#تعریف_کړه GL_SCREEN_KHR                     0x9295
#تعریف_کړه GL_OVERLAY_KHR                    0x9296
#تعریف_کړه GL_DARKEN_KHR                     0x9297
#تعریف_کړه GL_LIGHTEN_KHR                    0x9298
#تعریف_کړه GL_COLORDODGE_KHR                 0x9299
#تعریف_کړه GL_COLORBURN_KHR                  0x929A
#تعریف_کړه GL_HARDLIGHT_KHR                  0x929B
#تعریف_کړه GL_SOFTLIGHT_KHR                  0x929C
#تعریف_کړه GL_DIFFERENCE_KHR                 0x929E
#تعریف_کړه GL_EXCLUSION_KHR                  0x92A0
#تعریف_کړه GL_HSL_HUE_KHR                    0x92AD
#تعریف_کړه GL_HSL_SATURATION_KHR             0x92AE
#تعریف_کړه GL_HSL_COLOR_KHR                  0x92AF
#تعریف_کړه GL_HSL_LUMINOSITY_KHR             0x92B0
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDBARRIERKHRPROC) (فراغ);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glBlendBarrierKHR (فراغ);
#د_که_پای
#د_که_پای /* GL_KHR_blend_equation_advanced */

#که_نه_تعریف_شوی GL_KHR_blend_equation_advanced_coherent
#تعریف_کړه GL_KHR_blend_equation_advanced_coherent 1
#تعریف_کړه GL_BLEND_ADVANCED_COHERENT_KHR    0x9285
#د_که_پای /* GL_KHR_blend_equation_advanced_coherent */

#که_نه_تعریف_شوی GL_KHR_context_flush_control
#تعریف_کړه GL_KHR_context_flush_control 1
#تعریف_کړه GL_CONTEXT_RELEASE_BEHAVIOR_KHR   0x82FB
#تعریف_کړه GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_KHR 0x82FC
#د_که_پای /* GL_KHR_context_flush_control */

#که_نه_تعریف_شوی GL_KHR_debug
#تعریف_کړه GL_KHR_debug 1
تعريفنوع فراغ (GL_APIENTRY  *GLDEBUGPROCKHR)(GLenum سرچینه,GLenum type,GLuint id,GLenum severity,GLsizei اوږدتیا,ثابت GLchar *پیغام,ثابت فراغ *userParam);
#تعریف_کړه GL_SAMPLER                        0x82E6
#تعریف_کړه GL_DEBUG_OUTPUT_SYNCHRONOUS_KHR   0x8242
#تعریف_کړه GL_DEBUG_بل_LOGGED_پیغام_اوږدتیا_KHR 0x8243
#تعریف_کړه GL_DEBUG_CALLBACK_FUNCTION_KHR    0x8244
#تعریف_کړه GL_DEBUG_CALLBACK_USER_PARAM_KHR  0x8245
#تعریف_کړه GL_DEBUG_سرچینه_API_KHR           0x8246
#تعریف_کړه GL_DEBUG_سرچینه_کړکۍ_SYSTEM_KHR 0x8247
#تعریف_کړه GL_DEBUG_سرچینه_SHADER_COMPILER_KHR 0x8248
#تعریف_کړه GL_DEBUG_سرچینه_دریم_PARTY_KHR   0x8249
#تعریف_کړه GL_DEBUG_سرچینه_APPLICATION_KHR   0x824A
#تعریف_کړه GL_DEBUG_سرچینه_OTHER_KHR         0x824B
#تعریف_کړه GL_DEBUG_TYPE_ERROR_KHR           0x824C
#تعریف_کړه GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_KHR 0x824D
#تعریف_کړه GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_KHR 0x824E
#تعریف_کړه GL_DEBUG_TYPE_PORTABILITY_KHR     0x824F
#تعریف_کړه GL_DEBUG_TYPE_PERFORMANCE_KHR     0x8250
#تعریف_کړه GL_DEBUG_TYPE_OTHER_KHR           0x8251
#تعریف_کړه GL_DEBUG_TYPE_MARKER_KHR          0x8268
#تعریف_کړه GL_DEBUG_TYPE_ټېل_ډله_KHR      0x8269
#تعریف_کړه GL_DEBUG_TYPE_راوباسه_ډله_KHR       0x826A
#تعریف_کړه GL_DEBUG_SEVERITY_NOTIFICATION_KHR 0x826B
#تعریف_کړه GL_MAX_DEBUG_ډله_ډېری_ژوروالی_KHR 0x826C
#تعریف_کړه GL_DEBUG_ډله_ډېری_ژوروالی_KHR    0x826D
#تعریف_کړه GL_بفر_KHR                     0x82E0
#تعریف_کړه GL_SHADER_KHR                     0x82E1
#تعریف_کړه GL_پروګرام_KHR                    0x82E2
#تعریف_کړه GL_راس_ARRAY_KHR               0x8074
#تعریف_کړه GL_QUERY_KHR                      0x82E3
#تعریف_کړه GL_پروګرام_PIPELINE_KHR           0x82E4
#تعریف_کړه GL_SAMPLER_KHR                    0x82E6
#تعریف_کړه GL_MAX_LABEL_اوږدتیا_KHR           0x82E8
#تعریف_کړه GL_MAX_DEBUG_پیغام_اوږدتیا_KHR   0x9143
#تعریف_کړه GL_MAX_DEBUG_LOGGED_MESSAGES_KHR  0x9144
#تعریف_کړه GL_DEBUG_LOGGED_MESSAGES_KHR      0x9145
#تعریف_کړه GL_DEBUG_SEVERITY_لوړ_KHR        0x9146
#تعریف_کړه GL_DEBUG_SEVERITY_MEDIUM_KHR      0x9147
#تعریف_کړه GL_DEBUG_SEVERITY_ټیټ_KHR         0x9148
#تعریف_کړه GL_DEBUG_OUTPUT_KHR               0x92E0
#تعریف_کړه GL_CONTEXT_FLAG_DEBUG_بټ_KHR     0x00000002
#تعریف_کړه GL_ډېری_ډکېدنه_KHR             0x0503
#تعریف_کړه GL_ډېری_UNDERFLOW_KHR            0x0504
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEBUGMESSAGECONTROLKHRPROC) (GLenum سرچینه, GLenum type, GLenum severity, GLsizei شمېر, ثابت GLuint *ids, GLboolean enabled);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEBUGMESSAGEINSERTKHRPROC) (GLenum سرچینه, GLenum type, GLuint id, GLenum severity, GLsizei اوږدتیا, ثابت GLchar *buf);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEBUGMESSAGECALLBACKKHRPROC) (GLDEBUGPROCKHR callback, ثابت فراغ *userParam);
تعريفنوع GLuint (GL_APIENTRYP PFNGLGETDEBUGMESSAGELOGKHRPROC) (GLuint شمېر, GLsizei buf_اندازه, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *پیغام_Log);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPUSHDEBUGGROUPKHRPROC) (GLenum سرچینه, GLuint id, GLsizei اوږدتیا, ثابت GLchar *پیغام);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOPDEBUGGROUPKHRPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLOBJECTLABELKHRPROC) (GLenum identifier, GLuint name, GLsizei اوږدتیا, ثابت GLchar *label);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETOBJECTLABELKHRPROC) (GLenum identifier, GLuint name, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLchar *label);
تعريفنوع فراغ (GL_APIENTRYP PFNGLOBJECTPTRLABELKHRPROC) (ثابت فراغ *ptr, GLsizei اوږدتیا, ثابت GLchar *label);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETOBJECTPTRLABELKHRPROC) (ثابت فراغ *ptr, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLchar *label);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPOINTERVKHRPROC) (GLenum pname, فراغ **params);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Debug_پیغام_Control_KHR (GLenum سرچینه, GLenum type, GLenum severity, GLsizei شمېر, ثابت GLuint *ids, GLboolean enabled);
GL_APICALL فراغ GL_APIENTRY gl_Debug_پیغام_ورننباسه_KHR (GLenum سرچینه, GLenum type, GLuint id, GLenum severity, GLsizei اوږدتیا, ثابت GLchar *buf);
GL_APICALL فراغ GL_APIENTRY gl_Debug_پیغام_Callback_KHR (GLDEBUGPROCKHR callback, ثابت فراغ *userParam);
GL_APICALL GLuint GL_APIENTRY gl_Get_Debug_پیغام_Log_KHR (GLuint شمېر, GLsizei buf_اندازه, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *پیغام_Log);
GL_APICALL فراغ GL_APIENTRY gl_ټېل_Debug_ډله_KHR (GLenum سرچینه, GLuint id, GLsizei اوږدتیا, ثابت GLchar *پیغام);
GL_APICALL فراغ GL_APIENTRY gl_راوباسه_Debug_ډله_KHR (فراغ);
GL_APICALL فراغ GL_APIENTRY glObjectLabelKHR (GLenum identifier, GLuint name, GLsizei اوږدتیا, ثابت GLchar *label);
GL_APICALL فراغ GL_APIENTRY glGetObjectLabelKHR (GLenum identifier, GLuint name, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLchar *label);
GL_APICALL فراغ GL_APIENTRY glObjectPtrLabelKHR (ثابت فراغ *ptr, GLsizei اوږدتیا, ثابت GLchar *label);
GL_APICALL فراغ GL_APIENTRY glGetObjectPtrLabelKHR (ثابت فراغ *ptr, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLchar *label);
GL_APICALL فراغ GL_APIENTRY glGetPointervKHR (GLenum pname, فراغ **params);
#د_که_پای
#د_که_پای /* GL_KHR_debug */

#که_نه_تعریف_شوی GL_KHR_no_error
#تعریف_کړه GL_KHR_no_error 1
#تعریف_کړه GL_CONTEXT_FLAG_NO_ERROR_بټ_KHR  0x00000008
#د_که_پای /* GL_KHR_no_error */

#که_نه_تعریف_شوی GL_KHR_parallel_shader_compile
#تعریف_کړه GL_KHR_parallel_shader_compile 1
#تعریف_کړه GL_MAX_SHADER_COMPILER_تارونه_KHR 0x91B0
#تعریف_کړه GL_COMPLETION_حالت_KHR          0x91B1
تعريفنوع فراغ (GL_APIENTRYP PFNGLMAXSHADERCOMPILERTHREADSKHRPROC) (GLuint شمېر);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Max_Shader_Compiler_تارونه_KHR (GLuint شمېر);
#د_که_پای
#د_که_پای /* GL_KHR_parallel_shader_compile */

#که_نه_تعریف_شوی GL_KHR_robust_بفر_access_behavior
#تعریف_کړه GL_KHR_robust_بفر_access_behavior 1
#د_که_پای /* GL_KHR_robust_buffer_access_behavior */

#که_نه_تعریف_شوی GL_KHR_robustness
#تعریف_کړه GL_KHR_robustness 1
#تعریف_کړه GL_CONTEXT_ROBUST_ACCESS_KHR      0x90F3
#تعریف_کړه GL_LOSE_CONTEXT_ON_RESET_KHR      0x8252
#تعریف_کړه GL_GUILTY_CONTEXT_RESET_KHR       0x8253
#تعریف_کړه GL_INNOCENT_CONTEXT_RESET_KHR     0x8254
#تعریف_کړه GL_UNKNOWN_CONTEXT_RESET_KHR      0x8255
#تعریف_کړه GL_RESET_NOTIFICATION_STRATEGY_KHR 0x8256
#تعریف_کړه GL_NO_RESET_NOTIFICATION_KHR      0x8261
#تعریف_کړه GL_CONTEXT_ورک_KHR               0x0507
تعريفنوع GLenum (GL_APIENTRYP PFNGLGETGRAPHICSRESETSTATUSKHRPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLREADNPIXELSKHRPROC) (GLint x, GLint y, GLsizei پلنوالی, GLsizei لوړوالی, GLenum format, GLenum type, GLsizei buf_اندازه, فراغ *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNUNIFORMFVKHRPROC) (GLuint پروګرام, GLint location, GLsizei buf_اندازه, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNUNIFORMIVKHRPROC) (GLuint پروګرام, GLint location, GLsizei buf_اندازه, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNUNIFORMUIVKHRPROC) (GLuint پروګرام, GLint location, GLsizei buf_اندازه, GLuint *params);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL GLenum GL_APIENTRY gl_Get_Graphics_Reset_حالت_KHR (فراغ);
GL_APICALL فراغ GL_APIENTRY glReadnPixelsKHR (GLint x, GLint y, GLsizei پلنوالی, GLsizei لوړوالی, GLenum format, GLenum type, GLsizei buf_اندازه, فراغ *معلومات);
GL_APICALL فراغ GL_APIENTRY glGetnUniformfvKHR (GLuint پروګرام, GLint location, GLsizei buf_اندازه, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY glGetnUniformivKHR (GLuint پروګرام, GLint location, GLsizei buf_اندازه, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetnUniformuivKHR (GLuint پروګرام, GLint location, GLsizei buf_اندازه, GLuint *params);
#د_که_پای
#د_که_پای /* GL_KHR_robustness */

#که_نه_تعریف_شوی GL_KHR_shader_subgroup
#تعریف_کړه GL_KHR_shader_subgroup 1
#تعریف_کړه GL_SUBGROUP_اندازه_KHR              0x9532
#تعریف_کړه GL_SUBGROUP_SUPPORTED_STAGES_KHR  0x9533
#تعریف_کړه GL_SUBGROUP_SUPPORTED_FEATURES_KHR 0x9534
#تعریف_کړه GL_SUBGROUP_QUAD_ALL_STAGES_KHR   0x9535
#تعریف_کړه GL_SUBGROUP_FEATURE_BASIC_بټ_KHR 0x00000001
#تعریف_کړه GL_SUBGROUP_FEATURE_VOTE_بټ_KHR  0x00000002
#تعریف_کړه GL_SUBGROUP_FEATURE_ARITHMETIC_بټ_KHR 0x00000004
#تعریف_کړه GL_SUBGROUP_FEATURE_BALLOT_بټ_KHR 0x00000008
#تعریف_کړه GL_SUBGROUP_FEATURE_SHUFFLE_بټ_KHR 0x00000010
#تعریف_کړه GL_SUBGROUP_FEATURE_SHUFFLE_RELATIVE_بټ_KHR 0x00000020
#تعریف_کړه GL_SUBGROUP_FEATURE_CLUSTERED_بټ_KHR 0x00000040
#تعریف_کړه GL_SUBGROUP_FEATURE_QUAD_بټ_KHR  0x00000080
#د_که_پای /* GL_KHR_shader_subgroup */

#که_نه_تعریف_شوی GL_KHR_texture_compression_astc_hdr
#تعریف_کړه GL_KHR_texture_compression_astc_hdr 1
#تعریف_کړه GL_COMPRESSED_RGBA_ASTC_4x4_KHR   0x93B0
#تعریف_کړه GL_COMPRESSED_RGBA_ASTC_5x4_KHR   0x93B1
#تعریف_کړه GL_COMPRESSED_RGBA_ASTC_5x5_KHR   0x93B2
#تعریف_کړه GL_COMPRESSED_RGBA_ASTC_6x5_KHR   0x93B3
#تعریف_کړه GL_COMPRESSED_RGBA_ASTC_6x6_KHR   0x93B4
#تعریف_کړه GL_COMPRESSED_RGBA_ASTC_8x5_KHR   0x93B5
#تعریف_کړه GL_COMPRESSED_RGBA_ASTC_8x6_KHR   0x93B6
#تعریف_کړه GL_COMPRESSED_RGBA_ASTC_8x8_KHR   0x93B7
#تعریف_کړه GL_COMPRESSED_RGBA_ASTC_10x5_KHR  0x93B8
#تعریف_کړه GL_COMPRESSED_RGBA_ASTC_10x6_KHR  0x93B9
#تعریف_کړه GL_COMPRESSED_RGBA_ASTC_10x8_KHR  0x93BA
#تعریف_کړه GL_COMPRESSED_RGBA_ASTC_10x10_KHR 0x93BB
#تعریف_کړه GL_COMPRESSED_RGBA_ASTC_12x10_KHR 0x93BC
#تعریف_کړه GL_COMPRESSED_RGBA_ASTC_12x12_KHR 0x93BD
#تعریف_کړه GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR 0x93D0
#تعریف_کړه GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR 0x93D1
#تعریف_کړه GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR 0x93D2
#تعریف_کړه GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR 0x93D3
#تعریف_کړه GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR 0x93D4
#تعریف_کړه GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR 0x93D5
#تعریف_کړه GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR 0x93D6
#تعریف_کړه GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR 0x93D7
#تعریف_کړه GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR 0x93D8
#تعریف_کړه GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR 0x93D9
#تعریف_کړه GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR 0x93DA
#تعریف_کړه GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR 0x93DB
#تعریف_کړه GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR 0x93DC
#تعریف_کړه GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR 0x93DD
#د_که_پای /* GL_KHR_texture_compression_astc_hdr */

#که_نه_تعریف_شوی GL_KHR_texture_compression_astc_ldr
#تعریف_کړه GL_KHR_texture_compression_astc_ldr 1
#د_که_پای /* GL_KHR_texture_compression_astc_ldr */

#که_نه_تعریف_شوی GL_KHR_texture_compression_astc_sliced_3d
#تعریف_کړه GL_KHR_texture_compression_astc_sliced_3d 1
#د_که_پای /* GL_KHR_texture_compression_astc_sliced_3d */

#که_نه_تعریف_شوی GL_OES_EGL_image
#تعریف_کړه GL_OES_EGL_image 1
تعريفنوع فراغ *GLeglImageOES;
تعريفنوع فراغ (GL_APIENTRYP PFNGLEGLIMAGETARGETTEXTURE2DOESPROC) (GLenum موخه, GLeglImageOES image);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEGLIMAGETARGETRENDERBUFFERSTORAGEOESPROC) (GLenum موخه, GLeglImageOES image);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_EGLImage_موخه_Texture2_DOES (GLenum موخه, GLeglImageOES image);
GL_APICALL فراغ GL_APIENTRY gl_EGLImage_موخه_Renderbuffer_Storage_OES (GLenum موخه, GLeglImageOES image);
#د_که_پای
#د_که_پای /* GL_OES_EGL_image */

#که_نه_تعریف_شوی GL_OES_EGL_image_external
#تعریف_کړه GL_OES_EGL_image_external 1
#تعریف_کړه GL_TEXTURE_EXTERNAL_OES           0x8D65
#تعریف_کړه GL_TEXTURE_BINDING_EXTERNAL_OES   0x8D67
#تعریف_کړه GL_REQUIRED_TEXTURE_IMAGE_UNITS_OES 0x8D68
#تعریف_کړه GL_SAMPLER_EXTERNAL_OES           0x8D66
#د_که_پای /* GL_OES_EGL_image_external */

#که_نه_تعریف_شوی GL_OES_EGL_image_external_essl3
#تعریف_کړه GL_OES_EGL_image_external_essl3 1
#د_که_پای /* GL_OES_EGL_image_external_essl3 */

#که_نه_تعریف_شوی GL_OES_compressed_ETC1_RGB8_sub_texture
#تعریف_کړه GL_OES_compressed_ETC1_RGB8_sub_texture 1
#د_که_پای /* GL_OES_compressed_ETC1_RGB8_sub_texture */

#که_نه_تعریف_شوی GL_OES_compressed_ETC1_RGB8_texture
#تعریف_کړه GL_OES_compressed_ETC1_RGB8_texture 1
#تعریف_کړه GL_ETC1_RGB8_OES                  0x8D64
#د_که_پای /* GL_OES_compressed_ETC1_RGB8_texture */

#که_نه_تعریف_شوی GL_OES_compressed_paletted_texture
#تعریف_کړه GL_OES_compressed_paletted_texture 1
#تعریف_کړه GL_PALETTE4_RGB8_OES              0x8B90
#تعریف_کړه GL_PALETTE4_RGBA8_OES             0x8B91
#تعریف_کړه GL_PALETTE4_R5_G6_B5_OES          0x8B92
#تعریف_کړه GL_PALETTE4_RGBA4_OES             0x8B93
#تعریف_کړه GL_PALETTE4_RGB5_A1_OES           0x8B94
#تعریف_کړه GL_PALETTE8_RGB8_OES              0x8B95
#تعریف_کړه GL_PALETTE8_RGBA8_OES             0x8B96
#تعریف_کړه GL_PALETTE8_R5_G6_B5_OES          0x8B97
#تعریف_کړه GL_PALETTE8_RGBA4_OES             0x8B98
#تعریف_کړه GL_PALETTE8_RGB5_A1_OES           0x8B99
#د_که_پای /* GL_OES_compressed_paletted_texture */

#که_نه_تعریف_شوی GL_OES_copy_image
#تعریف_کړه GL_OES_copy_image 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYIMAGESUBDATAOESPROC) (GLuint srcName, GLenum src_موخه, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dst_موخه, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei src_پلنوالی, GLsizei src_لوړوالی, GLsizei src_ژوروالی);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Copy_Image_Sub_معلومات_OES (GLuint srcName, GLenum src_موخه, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dst_موخه, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei src_پلنوالی, GLsizei src_لوړوالی, GLsizei src_ژوروالی);
#د_که_پای
#د_که_پای /* GL_OES_copy_image */

#که_نه_تعریف_شوی GL_OES_depth24
#تعریف_کړه GL_OES_depth24 1
#تعریف_کړه GL_ژوروالی_COMPONENT24_OES          0x81A6
#د_که_پای /* GL_OES_depth24 */

#که_نه_تعریف_شوی GL_OES_depth32
#تعریف_کړه GL_OES_depth32 1
#تعریف_کړه GL_ژوروالی_COMPONENT32_OES          0x81A7
#د_که_پای /* GL_OES_depth32 */

#که_نه_تعریف_شوی GL_OES_ژوروالی_texture
#تعریف_کړه GL_OES_ژوروالی_texture 1
#د_که_پای /* GL_OES_depth_texture */

#که_نه_تعریف_شوی GL_OES_draw_buffers_شاخصي
#تعریف_کړه GL_OES_draw_buffers_شاخصي 1
#تعریف_کړه GL_MIN                            0x8007
#تعریف_کړه GL_MAX                            0x8008
تعريفنوع فراغ (GL_APIENTRYP PFNGLENABLEIOESPROC) (GLenum موخه, GLuint شاخص);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISABLEIOESPROC) (GLenum موخه, GLuint شاخص);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONIOESPROC) (GLuint buf, GLenum ډېرپېښ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEIOESPROC) (GLuint buf, GLenum ډېرپېښ_RGB, GLenum ډېرپېښ_Alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDFUNCIOESPROC) (GLuint buf, GLenum src, GLenum dst);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEIOESPROC) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOLORMASKIOESPROC) (GLuint شاخص, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISENABLEDIOESPROC) (GLenum موخه, GLuint شاخص);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glEnableiOES (GLenum موخه, GLuint شاخص);
GL_APICALL فراغ GL_APIENTRY glDisableiOES (GLenum موخه, GLuint شاخص);
GL_APICALL فراغ GL_APIENTRY glBlendEquationiOES (GLuint buf, GLenum ډېرپېښ);
GL_APICALL فراغ GL_APIENTRY glBlendEquationSeparateiOES (GLuint buf, GLenum ډېرپېښ_RGB, GLenum ډېرپېښ_Alpha);
GL_APICALL فراغ GL_APIENTRY glBlendFunciOES (GLuint buf, GLenum src, GLenum dst);
GL_APICALL فراغ GL_APIENTRY glBlendFuncSeparateiOES (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
GL_APICALL فراغ GL_APIENTRY glColorMaskiOES (GLuint شاخص, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
GL_APICALL GLboolean GL_APIENTRY glIsEnablediOES (GLenum موخه, GLuint شاخص);
#د_که_پای
#د_که_پای /* GL_OES_draw_buffers_indexed */

#که_نه_تعریف_شوی GL_OES_draw_elements_بنسټ_راس
#تعریف_کړه GL_OES_draw_elements_بنسټ_راس 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSBASEVERTEXOESPROC) (GLenum ډېرپېښ, GLsizei شمېر, GLenum type, ثابت فراغ *indices, GLint basevertex);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWRANGEELEMENTSBASEVERTEXOESPROC) (GLenum ډېرپېښ, GLuint پیل, GLuint پای_ټکی, GLsizei شمېر, GLenum type, ثابت فراغ *indices, GLint basevertex);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXOESPROC) (GLenum ډېرپېښ, GLsizei شمېر, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLint basevertex);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSBASEVERTEXEXTPROC) (GLenum ډېرپېښ, ثابت GLsizei *شمېر, GLenum type, ثابت فراغ *ثابت*indices, GLsizei drawcount, ثابت GLint *basevertex);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Draw_Elements_بنسټ_راس_OES (GLenum ډېرپېښ, GLsizei شمېر, GLenum type, ثابت فراغ *indices, GLint basevertex);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Range_Elements_بنسټ_راس_OES (GLenum ډېرپېښ, GLuint پیل, GLuint پای_ټکی, GLsizei شمېر, GLenum type, ثابت فراغ *indices, GLint basevertex);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Elements_Instanced_بنسټ_راس_OES (GLenum ډېرپېښ, GLsizei شمېر, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLint basevertex);
GL_APICALL فراغ GL_APIENTRY gl_Multi_Draw_Elements_بنسټ_راس_EXT (GLenum ډېرپېښ, ثابت GLsizei *شمېر, GLenum type, ثابت فراغ *ثابت*indices, GLsizei drawcount, ثابت GLint *basevertex);
#د_که_پای
#د_که_پای /* GL_OES_draw_elements_base_vertex */

#که_نه_تعریف_شوی GL_OES_element_شاخص_uint
#تعریف_کړه GL_OES_element_شاخص_uint 1
#د_که_پای /* GL_OES_element_index_uint */

#که_نه_تعریف_شوی GL_OES_fbo_render_mipmap
#تعریف_کړه GL_OES_fbo_render_mipmap 1
#د_که_پای /* GL_OES_fbo_render_mipmap */

#که_نه_تعریف_شوی GL_OES_fragment_precision_لوړ
#تعریف_کړه GL_OES_fragment_precision_لوړ 1
#د_که_پای /* GL_OES_fragment_precision_high */

#که_نه_تعریف_شوی GL_OES_geometry_ټکی_اندازه
#تعریف_کړه GL_OES_geometry_ټکی_اندازه 1
#د_که_پای /* GL_OES_geometry_point_size */

#که_نه_تعریف_شوی GL_OES_geometry_shader
#تعریف_کړه GL_OES_geometry_shader 1
#تعریف_کړه GL_GEOMETRY_SHADER_OES            0x8DD9
#تعریف_کړه GL_GEOMETRY_SHADER_بټ_OES        0x00000004
#تعریف_کړه GL_GEOMETRY_LINKED_VERTICES_بهر_OES 0x8916
#تعریف_کړه GL_GEOMETRY_LINKED_ننوت_TYPE_OES 0x8917
#تعریف_کړه GL_GEOMETRY_LINKED_OUTPUT_TYPE_OES 0x8918
#تعریف_کړه GL_GEOMETRY_SHADER_INVOCATIONS_OES 0x887F
#تعریف_کړه GL_LAYER_PROVOKING_راس_OES     0x825E
#تعریف_کړه GL_کرښې_ADJACENCY_OES            0x000A
#تعریف_کړه GL_کرښه_STRIP_ADJACENCY_OES       0x000B
#تعریف_کړه GL_TRIANGLES_ADJACENCY_OES        0x000C
#تعریف_کړه GL_TRIANGLE_STRIP_ADJACENCY_OES   0x000D
#تعریف_کړه GL_MAX_GEOMETRY_یوشان_COMPONENTS_OES 0x8DDF
#تعریف_کړه GL_MAX_GEOMETRY_یوشان_بلاکونه_OES 0x8A2C
#تعریف_کړه GL_MAX_COMBINED_GEOMETRY_یوشان_COMPONENTS_OES 0x8A32
#تعریف_کړه GL_MAX_GEOMETRY_ننوت_COMPONENTS_OES 0x9123
#تعریف_کړه GL_MAX_GEOMETRY_OUTPUT_COMPONENTS_OES 0x9124
#تعریف_کړه GL_MAX_GEOMETRY_OUTPUT_VERTICES_OES 0x8DE0
#تعریف_کړه GL_MAX_GEOMETRY_ټول_OUTPUT_COMPONENTS_OES 0x8DE1
#تعریف_کړه GL_MAX_GEOMETRY_SHADER_INVOCATIONS_OES 0x8E5A
#تعریف_کړه GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_OES 0x8C29
#تعریف_کړه GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS_OES 0x92CF
#تعریف_کړه GL_MAX_GEOMETRY_ATOMIC_COUNTERS_OES 0x92D5
#تعریف_کړه GL_MAX_GEOMETRY_IMAGE_UNIFORMS_OES 0x90CD
#تعریف_کړه GL_MAX_GEOMETRY_SHADER_STORAGE_بلاکونه_OES 0x90D7
#تعریف_کړه GL_لومړی_راس_CONVENTION_OES    0x8E4D
#تعریف_کړه GL_وروستی_راس_CONVENTION_OES     0x8E4E
#تعریف_کړه GL_UNDEFINED_راس_OES           0x8260
#تعریف_کړه GL_PRIMITIVES_GENERATED_OES       0x8C87
#تعریف_کړه GL_FRAMEBUFFER_DEFAULT_LAYERS_OES 0x9312
#تعریف_کړه GL_MAX_FRAMEBUFFER_LAYERS_OES     0x9317
#تعریف_کړه GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_OES 0x8DA8
#تعریف_کړه GL_FRAMEBUFFER_ATTACHMENT_LAYERED_OES 0x8DA7
#تعریف_کړه GL_REFERENCED_BY_GEOMETRY_SHADER_OES 0x9309
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREOESPROC) (GLenum موخه, GLenum attachment, GLuint texture, GLint level);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferTextureOES (GLenum موخه, GLenum attachment, GLuint texture, GLint level);
#د_که_پای
#د_که_پای /* GL_OES_geometry_shader */

#که_نه_تعریف_شوی GL_OES_get_پروګرام_دوګونی
#تعریف_کړه GL_OES_get_پروګرام_دوګونی 1
#تعریف_کړه GL_پروګرام_دوګونی_اوږدتیا_OES      0x8741
#تعریف_کړه GL_عدد_پروګرام_دوګونی_FORMATS_OES 0x87FE
#تعریف_کړه GL_پروګرام_دوګونی_FORMATS_OES     0x87FF
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMBINARYOESPROC) (GLuint پروګرام, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLenum *دوګونی_Format, فراغ *دوګونی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMBINARYOESPROC) (GLuint پروګرام, GLenum دوګونی_Format, ثابت فراغ *دوګونی, GLint اوږدتیا);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Get_پروګرام_دوګونی_OES (GLuint پروګرام, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLenum *دوګونی_Format, فراغ *دوګونی);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_دوګونی_OES (GLuint پروګرام, GLenum دوګونی_Format, ثابت فراغ *دوګونی, GLint اوږدتیا);
#د_که_پای
#د_که_پای /* GL_OES_get_program_binary */

#که_نه_تعریف_شوی GL_OES_gpu_shader5
#تعریف_کړه GL_OES_gpu_shader5 1
#د_که_پای /* GL_OES_gpu_shader5 */

#که_نه_تعریف_شوی GL_OES_mapbuffer
#تعریف_کړه GL_OES_mapbuffer 1
#تعریف_کړه GL_WRITE_ONLY_OES                 0x88B9
#تعریف_کړه GL_بفر_ACCESS_OES              0x88BB
#تعریف_کړه GL_بفر_MAPPED_OES              0x88BC
#تعریف_کړه GL_بفر_MAP_اشاره_ګر_OES         0x88BD
تعريفنوع فراغ *(GL_APIENTRYP PFNGLMAPBUFFEROESPROC) (GLenum موخه, GLenum access);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLUNMAPBUFFEROESPROC) (GLenum موخه);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETBUFFERPOINTERVOESPROC) (GLenum موخه, GLenum pname, فراغ **params);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ *GL_APIENTRY gl_Map_بفر_OES (GLenum موخه, GLenum access);
GL_APICALL GLboolean GL_APIENTRY gl_Unmap_بفر_OES (GLenum موخه);
GL_APICALL فراغ GL_APIENTRY gl_Get_بفر_Pointerv_OES (GLenum موخه, GLenum pname, فراغ **params);
#د_که_پای
#د_که_پای /* GL_OES_mapbuffer */

#که_نه_تعریف_شوی GL_OES_packed_ژوروالی_stencil
#تعریف_کړه GL_OES_packed_ژوروالی_stencil 1
#تعریف_کړه GL_ژوروالی_STENCIL_OES              0x84F9
#تعریف_کړه GL_UNSIGNED_INT_24_8_OES          0x84FA
#تعریف_کړه GL_DEPTH24_STENCIL8_OES           0x88F0
#د_که_پای /* GL_OES_packed_depth_stencil */

#که_نه_تعریف_شوی GL_OES_primitive_bounding_box
#تعریف_کړه GL_OES_primitive_bounding_box 1
#تعریف_کړه GL_PRIMITIVE_BOUNDING_BOX_OES     0x92BE
تعريفنوع فراغ (GL_APIENTRYP PFNGLPRIMITIVEBOUNDINGBOXOESPROC) (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glPrimitiveBoundingBoxOES (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
#د_که_پای
#د_که_پای /* GL_OES_primitive_bounding_box */

#که_نه_تعریف_شوی GL_OES_required_internalformat
#تعریف_کړه GL_OES_required_internalformat 1
#تعریف_کړه GL_ALPHA8_OES                     0x803C
#تعریف_کړه GL_ژوروالی_COMPONENT16_OES          0x81A5
#تعریف_کړه GL_LUMINANCE4_ALPHA4_OES          0x8043
#تعریف_کړه GL_LUMINANCE8_ALPHA8_OES          0x8045
#تعریف_کړه GL_LUMINANCE8_OES                 0x8040
#تعریف_کړه GL_RGBA4_OES                      0x8056
#تعریف_کړه GL_RGB5_A1_OES                    0x8057
#تعریف_کړه GL_RGB565_OES                     0x8D62
#تعریف_کړه GL_RGB8_OES                       0x8051
#تعریف_کړه GL_RGBA8_OES                      0x8058
#تعریف_کړه GL_RGB10_EXT                      0x8052
#تعریف_کړه GL_RGB10_A2_EXT                   0x8059
#د_که_پای /* GL_OES_required_internalformat */

#که_نه_تعریف_شوی GL_OES_rgb8_rgba8
#تعریف_کړه GL_OES_rgb8_rgba8 1
#د_که_پای /* GL_OES_rgb8_rgba8 */

#که_نه_تعریف_شوی GL_OES_sample_shading
#تعریف_کړه GL_OES_sample_shading 1
#تعریف_کړه GL_SAMPLE_SHADING_OES             0x8C36
#تعریف_کړه GL_MIN_SAMPLE_SHADING_ارزښت_OES   0x8C37
تعريفنوع فراغ (GL_APIENTRYP PFNGLMINSAMPLESHADINGOESPROC) (GLfloat ارزښت);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glMinSampleShadingOES (GLfloat ارزښت);
#د_که_پای
#د_که_پای /* GL_OES_sample_shading */

#که_نه_تعریف_شوی GL_OES_sample_variables
#تعریف_کړه GL_OES_sample_variables 1
#د_که_پای /* GL_OES_sample_variables */

#که_نه_تعریف_شوی GL_OES_shader_image_atomic
#تعریف_کړه GL_OES_shader_image_atomic 1
#د_که_پای /* GL_OES_shader_image_atomic */

#که_نه_تعریف_شوی GL_OES_shader_io_بلاکونه
#تعریف_کړه GL_OES_shader_io_بلاکونه 1
#د_که_پای /* GL_OES_shader_io_blocks */

#که_نه_تعریف_شوی GL_OES_shader_multisample_interpolation
#تعریف_کړه GL_OES_shader_multisample_interpolation 1
#تعریف_کړه GL_MIN_FRAGMENT_INTERPOLATION_دننه_واټن_OES 0x8E5B
#تعریف_کړه GL_MAX_FRAGMENT_INTERPOLATION_دننه_واټن_OES 0x8E5C
#تعریف_کړه GL_FRAGMENT_INTERPOLATION_دننه_واټن_بټونه_OES 0x8E5D
#د_که_پای /* GL_OES_shader_multisample_interpolation */

#که_نه_تعریف_شوی GL_OES_standard_derivatives
#تعریف_کړه GL_OES_standard_derivatives 1
#تعریف_کړه GL_FRAGMENT_SHADER_DERIVATIVE_HINT_OES 0x8B8B
#د_که_پای /* GL_OES_standard_derivatives */

#که_نه_تعریف_شوی GL_OES_stencil1
#تعریف_کړه GL_OES_stencil1 1
#تعریف_کړه GL_STENCIL_INDEX1_OES             0x8D46
#د_که_پای /* GL_OES_stencil1 */

#که_نه_تعریف_شوی GL_OES_stencil4
#تعریف_کړه GL_OES_stencil4 1
#تعریف_کړه GL_STENCIL_INDEX4_OES             0x8D47
#د_که_پای /* GL_OES_stencil4 */

#که_نه_تعریف_شوی GL_OES_surfaceless_context
#تعریف_کړه GL_OES_surfaceless_context 1
#تعریف_کړه GL_FRAMEBUFFER_UNDEFINED_OES      0x8219
#د_که_پای /* GL_OES_surfaceless_context */

#که_نه_تعریف_شوی GL_OES_tessellation_ټکی_اندازه
#تعریف_کړه GL_OES_tessellation_ټکی_اندازه 1
#د_که_پای /* GL_OES_tessellation_point_size */

#که_نه_تعریف_شوی GL_OES_tessellation_shader
#تعریف_کړه GL_OES_tessellation_shader 1
#تعریف_کړه GL_PATCHES_OES                    0x000E
#تعریف_کړه GL_PATCH_VERTICES_OES             0x8E72
#تعریف_کړه GL_TESS_CONTROL_OUTPUT_VERTICES_OES 0x8E75
#تعریف_کړه GL_TESS_GEN_ډېرپېښ_OES              0x8E76
#تعریف_کړه GL_TESS_GEN_SPACING_OES           0x8E77
#تعریف_کړه GL_TESS_GEN_راس_ترتیب_OES      0x8E78
#تعریف_کړه GL_TESS_GEN_ټکی_ډېرپېښ_OES        0x8E79
#تعریف_کړه GL_ISOLINES_OES                   0x8E7A
#تعریف_کړه GL_QUADS_OES                      0x0007
#تعریف_کړه GL_FRACTIONAL_ODD_OES             0x8E7B
#تعریف_کړه GL_FRACTIONAL_EVEN_OES            0x8E7C
#تعریف_کړه GL_MAX_PATCH_VERTICES_OES         0x8E7D
#تعریف_کړه GL_MAX_TESS_GEN_LEVEL_OES         0x8E7E
#تعریف_کړه GL_MAX_TESS_CONTROL_یوشان_COMPONENTS_OES 0x8E7F
#تعریف_کړه GL_MAX_TESS_EVALUATION_یوشان_COMPONENTS_OES 0x8E80
#تعریف_کړه GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS_OES 0x8E81
#تعریف_کړه GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS_OES 0x8E82
#تعریف_کړه GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS_OES 0x8E83
#تعریف_کړه GL_MAX_TESS_PATCH_COMPONENTS_OES  0x8E84
#تعریف_کړه GL_MAX_TESS_CONTROL_ټول_OUTPUT_COMPONENTS_OES 0x8E85
#تعریف_کړه GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS_OES 0x8E86
#تعریف_کړه GL_MAX_TESS_CONTROL_یوشان_بلاکونه_OES 0x8E89
#تعریف_کړه GL_MAX_TESS_EVALUATION_یوشان_بلاکونه_OES 0x8E8A
#تعریف_کړه GL_MAX_TESS_CONTROL_ننوت_COMPONENTS_OES 0x886C
#تعریف_کړه GL_MAX_TESS_EVALUATION_ننوت_COMPONENTS_OES 0x886D
#تعریف_کړه GL_MAX_COMBINED_TESS_CONTROL_یوشان_COMPONENTS_OES 0x8E1E
#تعریف_کړه GL_MAX_COMBINED_TESS_EVALUATION_یوشان_COMPONENTS_OES 0x8E1F
#تعریف_کړه GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS_OES 0x92CD
#تعریف_کړه GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS_OES 0x92CE
#تعریف_کړه GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS_OES 0x92D3
#تعریف_کړه GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS_OES 0x92D4
#تعریف_کړه GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS_OES 0x90CB
#تعریف_کړه GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS_OES 0x90CC
#تعریف_کړه GL_MAX_TESS_CONTROL_SHADER_STORAGE_بلاکونه_OES 0x90D8
#تعریف_کړه GL_MAX_TESS_EVALUATION_SHADER_STORAGE_بلاکونه_OES 0x90D9
#تعریف_کړه GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED_OES 0x8221
#تعریف_کړه GL_IS_فی_PATCH_OES               0x92E7
#تعریف_کړه GL_REFERENCED_BY_TESS_CONTROL_SHADER_OES 0x9307
#تعریف_کړه GL_REFERENCED_BY_TESS_EVALUATION_SHADER_OES 0x9308
#تعریف_کړه GL_TESS_CONTROL_SHADER_OES        0x8E88
#تعریف_کړه GL_TESS_EVALUATION_SHADER_OES     0x8E87
#تعریف_کړه GL_TESS_CONTROL_SHADER_بټ_OES    0x00000008
#تعریف_کړه GL_TESS_EVALUATION_SHADER_بټ_OES 0x00000010
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATCHPARAMETERIOESPROC) (GLenum pname, GLint ارزښت);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glPatchParameteriOES (GLenum pname, GLint ارزښت);
#د_که_پای
#د_که_پای /* GL_OES_tessellation_shader */

#که_نه_تعریف_شوی GL_OES_texture_3D
#تعریف_کړه GL_OES_texture_3D 1
#تعریف_کړه GL_TEXTURE_WRAP_R_OES             0x8072
#تعریف_کړه GL_TEXTURE_3D_OES                 0x806F
#تعریف_کړه GL_TEXTURE_BINDING_3D_OES         0x806A
#تعریف_کړه GL_MAX_3_D_TEXTURE_اندازه_OES        0x8073
#تعریف_کړه GL_SAMPLER_3D_OES                 0x8B5F
#تعریف_کړه GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_3D_ZOFFSET_OES 0x8CD4
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXIMAGE3DOESPROC) (GLenum موخه, GLint level, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLint border, GLenum format, GLenum type, ثابت فراغ *pixels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSUBIMAGE3DOESPROC) (GLenum موخه, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLenum format, GLenum type, ثابت فراغ *pixels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYTEXSUBIMAGE3DOESPROC) (GLenum موخه, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei پلنوالی, GLsizei لوړوالی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOMPRESSEDTEXIMAGE3DOESPROC) (GLenum موخه, GLint level, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLint border, GLsizei image_اندازه, ثابت فراغ *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE3DOESPROC) (GLenum موخه, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLenum format, GLsizei image_اندازه, ثابت فراغ *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE3DOESPROC) (GLenum موخه, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTexImage3DOES (GLenum موخه, GLint level, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLint border, GLenum format, GLenum type, ثابت فراغ *pixels);
GL_APICALL فراغ GL_APIENTRY glTexSubImage3DOES (GLenum موخه, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLenum format, GLenum type, ثابت فراغ *pixels);
GL_APICALL فراغ GL_APIENTRY glCopyTexSubImage3DOES (GLenum موخه, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei پلنوالی, GLsizei لوړوالی);
GL_APICALL فراغ GL_APIENTRY glCompressedTexImage3DOES (GLenum موخه, GLint level, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLint border, GLsizei image_اندازه, ثابت فراغ *معلومات);
GL_APICALL فراغ GL_APIENTRY glCompressedTexSubImage3DOES (GLenum موخه, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLenum format, GLsizei image_اندازه, ثابت فراغ *معلومات);
GL_APICALL فراغ GL_APIENTRY glFramebufferTexture3DOES (GLenum موخه, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
#د_که_پای
#د_که_پای /* GL_OES_texture_3D */

#که_نه_تعریف_شوی GL_OES_texture_border_clamp
#تعریف_کړه GL_OES_texture_border_clamp 1
#تعریف_کړه GL_TEXTURE_BORDER_COLOR_OES       0x1004
#تعریف_کړه GL_CLAMP_منزل_BORDER_OES            0x812D
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERIIVOESPROC) (GLenum موخه, GLenum pname, ثابت GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERIUIVOESPROC) (GLenum موخه, GLenum pname, ثابت GLuint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXPARAMETERIIVOESPROC) (GLenum موخه, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXPARAMETERIUIVOESPROC) (GLenum موخه, GLenum pname, GLuint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIIVOESPROC) (GLuint sampler, GLenum pname, ثابت GLint *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIUIVOESPROC) (GLuint sampler, GLenum pname, ثابت GLuint *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIIVOESPROC) (GLuint sampler, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIUIVOESPROC) (GLuint sampler, GLenum pname, GLuint *params);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTexParameterIivOES (GLenum موخه, GLenum pname, ثابت GLint *params);
GL_APICALL فراغ GL_APIENTRY glTexParameterIuivOES (GLenum موخه, GLenum pname, ثابت GLuint *params);
GL_APICALL فراغ GL_APIENTRY glGetTexParameterIivOES (GLenum موخه, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetTexParameterIuivOES (GLenum موخه, GLenum pname, GLuint *params);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterIivOES (GLuint sampler, GLenum pname, ثابت GLint *param);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterIuivOES (GLuint sampler, GLenum pname, ثابت GLuint *param);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameterIivOES (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameterIuivOES (GLuint sampler, GLenum pname, GLuint *params);
#د_که_پای
#د_که_پای /* GL_OES_texture_border_clamp */

#که_نه_تعریف_شوی GL_OES_texture_بفر
#تعریف_کړه GL_OES_texture_بفر 1
#تعریف_کړه GL_TEXTURE_بفر_OES             0x8C2A
#تعریف_کړه GL_TEXTURE_بفر_BINDING_OES     0x8C2A
#تعریف_کړه GL_MAX_TEXTURE_بفر_اندازه_OES    0x8C2B
#تعریف_کړه GL_TEXTURE_BINDING_بفر_OES     0x8C2C
#تعریف_کړه GL_TEXTURE_بفر_معلومات_STORE_BINDING_OES 0x8C2D
#تعریف_کړه GL_TEXTURE_بفر_دننه_واټن_ALIGNMENT_OES 0x919F
#تعریف_کړه GL_SAMPLER_بفر_OES             0x8DC2
#تعریف_کړه GL_INT_SAMPLER_بفر_OES         0x8DD0
#تعریف_کړه GL_UNSIGNED_INT_SAMPLER_بفر_OES 0x8DD8
#تعریف_کړه GL_IMAGE_بفر_OES               0x9051
#تعریف_کړه GL_INT_IMAGE_بفر_OES           0x905C
#تعریف_کړه GL_UNSIGNED_INT_IMAGE_بفر_OES  0x9067
#تعریف_کړه GL_TEXTURE_بفر_دننه_واټن_OES      0x919D
#تعریف_کړه GL_TEXTURE_بفر_اندازه_OES        0x919E
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXBUFFEROESPROC) (GLenum موخه, GLenum internalformat, GLuint بفر_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXBUFFERRANGEOESPROC) (GLenum موخه, GLenum internalformat, GLuint بفر_2, GLintptr دننه_واټن_2, GLsizeiptr اندازه);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Tex_بفر_OES (GLenum موخه, GLenum internalformat, GLuint بفر_2);
GL_APICALL فراغ GL_APIENTRY gl_Tex_بفر_Range_OES (GLenum موخه, GLenum internalformat, GLuint بفر_2, GLintptr دننه_واټن_2, GLsizeiptr اندازه);
#د_که_پای
#د_که_پای /* GL_OES_texture_buffer */

#که_نه_تعریف_شوی GL_OES_texture_compression_astc
#تعریف_کړه GL_OES_texture_compression_astc 1
#تعریف_کړه GL_COMPRESSED_RGBA_ASTC_3x3x3_OES 0x93C0
#تعریف_کړه GL_COMPRESSED_RGBA_ASTC_4x3x3_OES 0x93C1
#تعریف_کړه GL_COMPRESSED_RGBA_ASTC_4x4x3_OES 0x93C2
#تعریف_کړه GL_COMPRESSED_RGBA_ASTC_4x4x4_OES 0x93C3
#تعریف_کړه GL_COMPRESSED_RGBA_ASTC_5x4x4_OES 0x93C4
#تعریف_کړه GL_COMPRESSED_RGBA_ASTC_5x5x4_OES 0x93C5
#تعریف_کړه GL_COMPRESSED_RGBA_ASTC_5x5x5_OES 0x93C6
#تعریف_کړه GL_COMPRESSED_RGBA_ASTC_6x5x5_OES 0x93C7
#تعریف_کړه GL_COMPRESSED_RGBA_ASTC_6x6x5_OES 0x93C8
#تعریف_کړه GL_COMPRESSED_RGBA_ASTC_6x6x6_OES 0x93C9
#تعریف_کړه GL_COMPRESSED_SRGB8_ALPHA8_ASTC_3x3x3_OES 0x93E0
#تعریف_کړه GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x3x3_OES 0x93E1
#تعریف_کړه GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4x3_OES 0x93E2
#تعریف_کړه GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4x4_OES 0x93E3
#تعریف_کړه GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4x4_OES 0x93E4
#تعریف_کړه GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5x4_OES 0x93E5
#تعریف_کړه GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5x5_OES 0x93E6
#تعریف_کړه GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5x5_OES 0x93E7
#تعریف_کړه GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6x5_OES 0x93E8
#تعریف_کړه GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6x6_OES 0x93E9
#د_که_پای /* GL_OES_texture_compression_astc */

#که_نه_تعریف_شوی GL_OES_texture_cube_map_array
#تعریف_کړه GL_OES_texture_cube_map_array 1
#تعریف_کړه GL_TEXTURE_CUBE_MAP_ARRAY_OES     0x9009
#تعریف_کړه GL_TEXTURE_BINDING_CUBE_MAP_ARRAY_OES 0x900A
#تعریف_کړه GL_SAMPLER_CUBE_MAP_ARRAY_OES     0x900C
#تعریف_کړه GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW_OES 0x900D
#تعریف_کړه GL_INT_SAMPLER_CUBE_MAP_ARRAY_OES 0x900E
#تعریف_کړه GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY_OES 0x900F
#تعریف_کړه GL_IMAGE_CUBE_MAP_ARRAY_OES       0x9054
#تعریف_کړه GL_INT_IMAGE_CUBE_MAP_ARRAY_OES   0x905F
#تعریف_کړه GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY_OES 0x906A
#د_که_پای /* GL_OES_texture_cube_map_array */

#که_نه_تعریف_شوی GL_OES_texture_float
#تعریف_کړه GL_OES_texture_float 1
#د_که_پای /* GL_OES_texture_float */

#که_نه_تعریف_شوی GL_OES_texture_float_خطي
#تعریف_کړه GL_OES_texture_float_خطي 1
#د_که_پای /* GL_OES_texture_float_linear */

#که_نه_تعریف_شوی GL_OES_texture_half_float
#تعریف_کړه GL_OES_texture_half_float 1
#تعریف_کړه GL_HALF_FLOAT_OES                 0x8D61
#د_که_پای /* GL_OES_texture_half_float */

#که_نه_تعریف_شوی GL_OES_texture_half_float_خطي
#تعریف_کړه GL_OES_texture_half_float_خطي 1
#د_که_پای /* GL_OES_texture_half_float_linear */

#که_نه_تعریف_شوی GL_OES_texture_npot
#تعریف_کړه GL_OES_texture_npot 1
#د_که_پای /* GL_OES_texture_npot */

#که_نه_تعریف_شوی GL_OES_texture_stencil8
#تعریف_کړه GL_OES_texture_stencil8 1
#تعریف_کړه GL_STENCIL_شاخص_OES              0x1901
#تعریف_کړه GL_STENCIL_INDEX8_OES             0x8D48
#د_که_پای /* GL_OES_texture_stencil8 */

#که_نه_تعریف_شوی GL_OES_texture_storage_multisample_2d_array
#تعریف_کړه GL_OES_texture_storage_multisample_2d_array 1
#تعریف_کړه GL_TEXTURE_2D_MULTISAMPLE_ARRAY_OES 0x9102
#تعریف_کړه GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY_OES 0x9105
#تعریف_کړه GL_SAMPLER_2D_MULTISAMPLE_ARRAY_OES 0x910B
#تعریف_کړه GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY_OES 0x910C
#تعریف_کړه GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY_OES 0x910D
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE3DMULTISAMPLEOESPROC) (GLenum موخه, GLsizei samples, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLboolean fixedsamplelocations);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTexStorage3DMultisampleOES (GLenum موخه, GLsizei samples, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLboolean fixedsamplelocations);
#د_که_پای
#د_که_پای /* GL_OES_texture_storage_multisample_2d_array */

#که_نه_تعریف_شوی GL_OES_texture_view
#تعریف_کړه GL_OES_texture_view 1
#تعریف_کړه GL_TEXTURE_VIEW_MIN_LEVEL_OES     0x82DB
#تعریف_کړه GL_TEXTURE_VIEW_عدد_پوړونه_OES    0x82DC
#تعریف_کړه GL_TEXTURE_VIEW_MIN_LAYER_OES     0x82DD
#تعریف_کړه GL_TEXTURE_VIEW_عدد_LAYERS_OES    0x82DE
#تعریف_کړه GL_TEXTURE_IMMUTABLE_پوړونه       0x82DF
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTUREVIEWOESPROC) (GLuint texture, GLenum موخه, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTextureViewOES (GLuint texture, GLenum موخه, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
#د_که_پای
#د_که_پای /* GL_OES_texture_view */

#که_نه_تعریف_شوی GL_OES_راس_array_object
#تعریف_کړه GL_OES_راس_array_object 1
#تعریف_کړه GL_راس_ARRAY_BINDING_OES       0x85B5
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDVERTEXARRAYOESPROC) (GLuint array);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEVERTEXARRAYSOESPROC) (GLsizei n, ثابت GLuint *arrays);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENVERTEXARRAYSOESPROC) (GLsizei n, GLuint *arrays);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISVERTEXARRAYOESPROC) (GLuint array);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Bind_راس_Array_OES (GLuint array);
GL_APICALL فراغ GL_APIENTRY gl_Delete_راس_Arrays_OES (GLsizei n, ثابت GLuint *arrays);
GL_APICALL فراغ GL_APIENTRY gl_Gen_راس_Arrays_OES (GLsizei n, GLuint *arrays);
GL_APICALL GLboolean GL_APIENTRY gl_Is_راس_Array_OES (GLuint array);
#د_که_پای
#د_که_پای /* GL_OES_vertex_array_object */

#که_نه_تعریف_شوی GL_OES_راس_half_float
#تعریف_کړه GL_OES_راس_half_float 1
#د_که_پای /* GL_OES_vertex_half_float */

#که_نه_تعریف_شوی GL_OES_راس_type_10_10_10_2
#تعریف_کړه GL_OES_راس_type_10_10_10_2 1
#تعریف_کړه GL_UNSIGNED_INT_10_10_10_2_OES    0x8DF6
#تعریف_کړه GL_INT_10_10_10_2_OES             0x8DF7
#د_که_پای /* GL_OES_vertex_type_10_10_10_2 */

#که_نه_تعریف_شوی GL_OES_viewport_array
#تعریف_کړه GL_OES_viewport_array 1
#تعریف_کړه GL_MAX_VIEWPORTS_OES              0x825B
#تعریف_کړه GL_VIEWPORT_SUBPIXEL_بټونه_OES     0x825C
#تعریف_کړه GL_VIEWPORT_BOUNDS_RANGE_OES      0x825D
#تعریف_کړه GL_VIEWPORT_شاخص_PROVOKING_راس_OES 0x825F
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTARRAYVOESPROC) (GLuint لومړی, GLsizei شمېر, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTINDEXEDFOESPROC) (GLuint شاخص, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTINDEXEDFVOESPROC) (GLuint شاخص, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSORARRAYVOESPROC) (GLuint لومړی, GLsizei شمېر, ثابت GLint *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSORINDEXEDOESPROC) (GLuint شاخص, GLint کیڼ, GLint bottom, GLsizei پلنوالی, GLsizei لوړوالی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSORINDEXEDVOESPROC) (GLuint شاخص, ثابت GLint *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHRANGEARRAYFVOESPROC) (GLuint لومړی, GLsizei شمېر, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHRANGEINDEXEDFOESPROC) (GLuint شاخص, GLfloat n, GLfloat f);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFLOATI_VOESPROC) (GLenum موخه, GLuint شاخص, GLfloat *معلومات);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glViewportArrayvOES (GLuint لومړی, GLsizei شمېر, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY glViewportIndexedfOES (GLuint شاخص, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
GL_APICALL فراغ GL_APIENTRY glViewportIndexedfvOES (GLuint شاخص, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY glScissorArrayvOES (GLuint لومړی, GLsizei شمېر, ثابت GLint *v);
GL_APICALL فراغ GL_APIENTRY gl_Scissor_شاخصي_OES (GLuint شاخص, GLint کیڼ, GLint bottom, GLsizei پلنوالی, GLsizei لوړوالی);
GL_APICALL فراغ GL_APIENTRY glScissorIndexedvOES (GLuint شاخص, ثابت GLint *v);
GL_APICALL فراغ GL_APIENTRY gl_ژوروالی_Range_Arrayfv_OES (GLuint لومړی, GLsizei شمېر, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY gl_ژوروالی_Range_Indexedf_OES (GLuint شاخص, GLfloat n, GLfloat f);
GL_APICALL فراغ GL_APIENTRY glGetFloati_vOES (GLenum موخه, GLuint شاخص, GLfloat *معلومات);
#د_که_پای
#د_که_پای /* GL_OES_viewport_array */

#که_نه_تعریف_شوی GL_AMD_compressed_3DC_texture
#تعریف_کړه GL_AMD_compressed_3DC_texture 1
#تعریف_کړه GL_3DC_X_AMD                      0x87F9
#تعریف_کړه GL_3DC_XY_AMD                     0x87FA
#د_که_پای /* GL_AMD_compressed_3DC_texture */

#که_نه_تعریف_شوی GL_AMD_compressed_ATC_texture
#تعریف_کړه GL_AMD_compressed_ATC_texture 1
#تعریف_کړه GL_ATC_RGB_AMD                    0x8C92
#تعریف_کړه GL_ATC_RGBA_EXPLICIT_ALPHA_AMD    0x8C93
#تعریف_کړه GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD 0x87EE
#د_که_پای /* GL_AMD_compressed_ATC_texture */

#که_نه_تعریف_شوی GL_AMD_framebuffer_multisample_advanced
#تعریف_کړه GL_AMD_framebuffer_multisample_advanced 1
#تعریف_کړه GL_RENDERBUFFER_STORAGE_SAMPLES_AMD 0x91B2
#تعریف_کړه GL_MAX_COLOR_FRAMEBUFFER_SAMPLES_AMD 0x91B3
#تعریف_کړه GL_MAX_COLOR_FRAMEBUFFER_STORAGE_SAMPLES_AMD 0x91B4
#تعریف_کړه GL_MAX_ژوروالی_STENCIL_FRAMEBUFFER_SAMPLES_AMD 0x91B5
#تعریف_کړه GL_عدد_SUPPORTED_MULTISAMPLE_MODES_AMD 0x91B6
#تعریف_کړه GL_SUPPORTED_MULTISAMPLE_MODES_AMD 0x91B7
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC) (GLenum موخه, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC) (GLuint renderbuffer, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glRenderbufferStorageMultisampleAdvancedAMD (GLenum موخه, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
GL_APICALL فراغ GL_APIENTRY glNamedRenderbufferStorageMultisampleAdvancedAMD (GLuint renderbuffer, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
#د_که_پای
#د_که_پای /* GL_AMD_framebuffer_multisample_advanced */

#که_نه_تعریف_شوی GL_AMD_performance_monitor
#تعریف_کړه GL_AMD_performance_monitor 1
#تعریف_کړه GL_COUNTER_TYPE_AMD               0x8BC0
#تعریف_کړه GL_COUNTER_RANGE_AMD              0x8BC1
#تعریف_کړه GL_UNSIGNED_INT64_AMD             0x8BC2
#تعریف_کړه GL_PERCENTAGE_AMD                 0x8BC3
#تعریف_کړه GL_PERFMON_پایله_شته_AMD   0x8BC4
#تعریف_کړه GL_PERFMON_پایله_اندازه_AMD        0x8BC5
#تعریف_کړه GL_PERFMON_پایله_AMD             0x8BC6
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFMONITORGROUPSAMDPROC) (GLint *عدد_Groups, GLsizei groups_اندازه, GLuint *groups);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFMONITORCOUNTERSAMDPROC) (GLuint ډله, GLint *عدد_Counters, GLint *max_فعال_Counters, GLsizei counter_اندازه, GLuint *counters);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFMONITORGROUPSTRINGAMDPROC) (GLuint ډله, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLchar *ډله_String);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC) (GLuint ډله, GLuint counter, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLchar *counterString);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFMONITORCOUNTERINFOAMDPROC) (GLuint ډله, GLuint counter, GLenum pname, فراغ *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENPERFMONITORSAMDPROC) (GLsizei n, GLuint *monitors);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEPERFMONITORSAMDPROC) (GLsizei n, GLuint *monitors);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSELECTPERFMONITORCOUNTERSAMDPROC) (GLuint monitor, GLboolean enable, GLuint ډله, GLint عدد_Counters, GLuint *counterList);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBEGINPERFMONITORAMDPROC) (GLuint monitor);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENDPERFMONITORAMDPROC) (GLuint monitor);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFMONITORCOUNTERDATAAMDPROC) (GLuint monitor, GLenum pname, GLsizei معلومات_اندازه_2, GLuint *معلومات, GLint *بایټونه_Written);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glGetPerfMonitorGroupsAMD (GLint *عدد_Groups, GLsizei groups_اندازه, GLuint *groups);
GL_APICALL فراغ GL_APIENTRY glGetPerfMonitorCountersAMD (GLuint ډله, GLint *عدد_Counters, GLint *max_فعال_Counters, GLsizei counter_اندازه, GLuint *counters);
GL_APICALL فراغ GL_APIENTRY gl_Get_Perf_Monitor_ډله_String_AMD (GLuint ډله, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLchar *ډله_String);
GL_APICALL فراغ GL_APIENTRY glGetPerfMonitorCounterStringAMD (GLuint ډله, GLuint counter, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLchar *counterString);
GL_APICALL فراغ GL_APIENTRY glGetPerfMonitorCounterInfoAMD (GLuint ډله, GLuint counter, GLenum pname, فراغ *معلومات);
GL_APICALL فراغ GL_APIENTRY glGenPerfMonitorsAMD (GLsizei n, GLuint *monitors);
GL_APICALL فراغ GL_APIENTRY glDeletePerfMonitorsAMD (GLsizei n, GLuint *monitors);
GL_APICALL فراغ GL_APIENTRY glSelectPerfMonitorCountersAMD (GLuint monitor, GLboolean enable, GLuint ډله, GLint عدد_Counters, GLuint *counterList);
GL_APICALL فراغ GL_APIENTRY glBeginPerfMonitorAMD (GLuint monitor);
GL_APICALL فراغ GL_APIENTRY gl_پای_ټکی_Perf_Monitor_AMD (GLuint monitor);
GL_APICALL فراغ GL_APIENTRY gl_Get_Perf_Monitor_Counter_معلومات_AMD (GLuint monitor, GLenum pname, GLsizei معلومات_اندازه_2, GLuint *معلومات, GLint *بایټونه_Written);
#د_که_پای
#د_که_پای /* GL_AMD_performance_monitor */

#که_نه_تعریف_شوی GL_AMD_پروګرام_دوګونی_Z400
#تعریف_کړه GL_AMD_پروګرام_دوګونی_Z400 1
#تعریف_کړه GL_Z400_دوګونی_AMD                0x8740
#د_که_پای /* GL_AMD_program_binary_Z400 */

#که_نه_تعریف_شوی GL_ANDROID_extension_pack_es31a
#تعریف_کړه GL_ANDROID_extension_pack_es31a 1
#د_که_پای /* GL_ANDROID_extension_pack_es31a */

#که_نه_تعریف_شوی GL_ANGLE_ژوروالی_texture
#تعریف_کړه GL_ANGLE_ژوروالی_texture 1
#د_که_پای /* GL_ANGLE_depth_texture */

#که_نه_تعریف_شوی GL_ANGLE_framebuffer_blit
#تعریف_کړه GL_ANGLE_framebuffer_blit 1
#تعریف_کړه GL_READ_FRAMEBUFFER_ANGLE         0x8CA8
#تعریف_کړه GL_DRAW_FRAMEBUFFER_ANGLE         0x8CA9
#تعریف_کړه GL_DRAW_FRAMEBUFFER_BINDING_ANGLE 0x8CA6
#تعریف_کړه GL_READ_FRAMEBUFFER_BINDING_ANGLE 0x8CAA
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLITFRAMEBUFFERANGLEPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield ماسک, GLenum filter);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glBlitFramebufferANGLE (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield ماسک, GLenum filter);
#د_که_پای
#د_که_پای /* GL_ANGLE_framebuffer_blit */

#که_نه_تعریف_شوی GL_ANGLE_framebuffer_multisample
#تعریف_کړه GL_ANGLE_framebuffer_multisample 1
#تعریف_کړه GL_RENDERBUFFER_SAMPLES_ANGLE     0x8CAB
#تعریف_کړه GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_ANGLE 0x8D56
#تعریف_کړه GL_MAX_SAMPLES_ANGLE              0x8D57
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEANGLEPROC) (GLenum موخه, GLsizei samples, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glRenderbufferStorageMultisampleANGLE (GLenum موخه, GLsizei samples, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
#د_که_پای
#د_که_پای /* GL_ANGLE_framebuffer_multisample */

#که_نه_تعریف_شوی GL_ANGLE_instanced_arrays
#تعریف_کړه GL_ANGLE_instanced_arrays 1
#تعریف_کړه GL_راس_ATTRIB_ARRAY_وېشونکی_ANGLE 0x88FE
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDANGLEPROC) (GLenum ډېرپېښ, GLint لومړی, GLsizei شمېر, GLsizei primcount);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDANGLEPROC) (GLenum ډېرپېښ, GLsizei شمېر, GLenum type, ثابت فراغ *indices, GLsizei primcount);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBDIVISORANGLEPROC) (GLuint شاخص, GLuint وېشونکی);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawArraysInstancedANGLE (GLenum ډېرپېښ, GLint لومړی, GLsizei شمېر, GLsizei primcount);
GL_APICALL فراغ GL_APIENTRY glDrawElementsInstancedANGLE (GLenum ډېرپېښ, GLsizei شمېر, GLenum type, ثابت فراغ *indices, GLsizei primcount);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib_وېشونکی_ANGLE (GLuint شاخص, GLuint وېشونکی);
#د_که_پای
#د_که_پای /* GL_ANGLE_instanced_arrays */

#که_نه_تعریف_شوی GL_ANGLE_pack_سرچپه_لیکه_ترتیب
#تعریف_کړه GL_ANGLE_pack_سرچپه_لیکه_ترتیب 1
#تعریف_کړه GL_PACK_سرچپه_لیکه_ترتیب_ANGLE   0x93A4
#د_که_پای /* GL_ANGLE_pack_reverse_row_order */

#که_نه_تعریف_شوی GL_ANGLE_پروګرام_دوګونی
#تعریف_کړه GL_ANGLE_پروګرام_دوګونی 1
#تعریف_کړه GL_پروګرام_دوګونی_ANGLE           0x93A6
#د_که_پای /* GL_ANGLE_program_binary */

#که_نه_تعریف_شوی GL_ANGLE_texture_compression_dxt3
#تعریف_کړه GL_ANGLE_texture_compression_dxt3 1
#تعریف_کړه GL_COMPRESSED_RGBA_S3TC_DXT3_ANGLE 0x83F2
#د_که_پای /* GL_ANGLE_texture_compression_dxt3 */

#که_نه_تعریف_شوی GL_ANGLE_texture_compression_dxt5
#تعریف_کړه GL_ANGLE_texture_compression_dxt5 1
#تعریف_کړه GL_COMPRESSED_RGBA_S3TC_DXT5_ANGLE 0x83F3
#د_که_پای /* GL_ANGLE_texture_compression_dxt5 */

#که_نه_تعریف_شوی GL_ANGLE_texture_usage
#تعریف_کړه GL_ANGLE_texture_usage 1
#تعریف_کړه GL_TEXTURE_USAGE_ANGLE            0x93A2
#تعریف_کړه GL_FRAMEBUFFER_ATTACHMENT_ANGLE   0x93A3
#د_که_پای /* GL_ANGLE_texture_usage */

#که_نه_تعریف_شوی GL_ANGLE_translated_shader_سرچینه
#تعریف_کړه GL_ANGLE_translated_shader_سرچینه 1
#تعریف_کړه GL_TRANSLATED_SHADER_سرچینه_اوږدتیا_ANGLE 0x93A0
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTRANSLATEDSHADERSOURCEANGLEPROC) (GLuint shader, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLchar *سرچینه);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Get_Translated_Shader_سرچینه_ANGLE (GLuint shader, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLchar *سرچینه);
#د_که_پای
#د_که_پای /* GL_ANGLE_translated_shader_source */

#که_نه_تعریف_شوی GL_APPLE_clip_واټن
#تعریف_کړه GL_APPLE_clip_واټن 1
#تعریف_کړه GL_MAX_CLIP_DISTANCES_APPLE       0x0D32
#تعریف_کړه GL_CLIP_DISTANCE0_APPLE           0x3000
#تعریف_کړه GL_CLIP_DISTANCE1_APPLE           0x3001
#تعریف_کړه GL_CLIP_DISTANCE2_APPLE           0x3002
#تعریف_کړه GL_CLIP_DISTANCE3_APPLE           0x3003
#تعریف_کړه GL_CLIP_DISTANCE4_APPLE           0x3004
#تعریف_کړه GL_CLIP_DISTANCE5_APPLE           0x3005
#تعریف_کړه GL_CLIP_DISTANCE6_APPLE           0x3006
#تعریف_کړه GL_CLIP_DISTANCE7_APPLE           0x3007
#د_که_پای /* GL_APPLE_clip_distance */

#که_نه_تعریف_شوی GL_APPLE_color_بفر_packed_float
#تعریف_کړه GL_APPLE_color_بفر_packed_float 1
#د_که_پای /* GL_APPLE_color_buffer_packed_float */

#که_نه_تعریف_شوی GL_APPLE_copy_texture_پوړونه
#تعریف_کړه GL_APPLE_copy_texture_پوړونه 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYTEXTURELEVELSAPPLEPROC) (GLuint destinationTexture, GLuint سرچینه_Texture, GLint سرچینه_بنسټ_Level, GLsizei سرچینه_Level_شمېر);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Copy_Texture_پوړونه_APPLE (GLuint destinationTexture, GLuint سرچینه_Texture, GLint سرچینه_بنسټ_Level, GLsizei سرچینه_Level_شمېر);
#د_که_پای
#د_که_پای /* GL_APPLE_copy_texture_levels */

#که_نه_تعریف_شوی GL_APPLE_framebuffer_multisample
#تعریف_کړه GL_APPLE_framebuffer_multisample 1
#تعریف_کړه GL_RENDERBUFFER_SAMPLES_APPLE     0x8CAB
#تعریف_کړه GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_APPLE 0x8D56
#تعریف_کړه GL_MAX_SAMPLES_APPLE              0x8D57
#تعریف_کړه GL_READ_FRAMEBUFFER_APPLE         0x8CA8
#تعریف_کړه GL_DRAW_FRAMEBUFFER_APPLE         0x8CA9
#تعریف_کړه GL_DRAW_FRAMEBUFFER_BINDING_APPLE 0x8CA6
#تعریف_کړه GL_READ_FRAMEBUFFER_BINDING_APPLE 0x8CAA
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEAPPLEPROC) (GLenum موخه, GLsizei samples, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRESOLVEMULTISAMPLEFRAMEBUFFERAPPLEPROC) (فراغ);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glRenderbufferStorageMultisampleAPPLE (GLenum موخه, GLsizei samples, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
GL_APICALL فراغ GL_APIENTRY glResolveMultisampleFramebufferAPPLE (فراغ);
#د_که_پای
#د_که_پای /* GL_APPLE_framebuffer_multisample */

#که_نه_تعریف_شوی GL_APPLE_rgb_422
#تعریف_کړه GL_APPLE_rgb_422 1
#تعریف_کړه GL_RGB_422_APPLE                  0x8A1F
#تعریف_کړه GL_UNSIGNED_SHORT_8_8_APPLE       0x85BA
#تعریف_کړه GL_UNSIGNED_SHORT_8_8_REV_APPLE   0x85BB
#تعریف_کړه GL_RGB_RAW_422_APPLE              0x8A51
#د_که_پای /* GL_APPLE_rgb_422 */

#که_نه_تعریف_شوی GL_APPLE_sync
#تعریف_کړه GL_APPLE_sync 1
#تعریف_کړه GL_SYNC_OBJECT_APPLE              0x8A53
#تعریف_کړه GL_MAX_SERVER_WAIT_TIMEOUT_APPLE  0x9111
#تعریف_کړه GL_OBJECT_TYPE_APPLE              0x9112
#تعریف_کړه GL_SYNC_CONDITION_APPLE           0x9113
#تعریف_کړه GL_SYNC_حالت_APPLE              0x9114
#تعریف_کړه GL_SYNC_FLAGS_APPLE               0x9115
#تعریف_کړه GL_SYNC_FENCE_APPLE               0x9116
#تعریف_کړه GL_SYNC_GPU_COMMANDS_COMPLETE_APPLE 0x9117
#تعریف_کړه GL_UNSIGNALED_APPLE               0x9118
#تعریف_کړه GL_SIGNALED_APPLE                 0x9119
#تعریف_کړه GL_ALREADY_SIGNALED_APPLE         0x911A
#تعریف_کړه GL_TIMEOUT_EXPIRED_APPLE          0x911B
#تعریف_کړه GL_CONDITION_SATISFIED_APPLE      0x911C
#تعریف_کړه GL_WAIT_FAILED_APPLE              0x911D
#تعریف_کړه GL_SYNC_FLUSH_COMMANDS_بټ_APPLE  0x00000001
#تعریف_کړه GL_TIMEOUT_IGNORED_APPLE          0xFFFFFFFFFFFFFFFFull
تعريفنوع GLsync (GL_APIENTRYP PFNGLFENCESYNCAPPLEPROC) (GLenum condition, GLbitfield flags);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISSYNCAPPLEPROC) (GLsync sync);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETESYNCAPPLEPROC) (GLsync sync);
تعريفنوع GLenum (GL_APIENTRYP PFNGLCLIENTWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
تعريفنوع فراغ (GL_APIENTRYP PFNGLWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTEGER64VAPPLEPROC) (GLenum pname, GLint64 *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSYNCIVAPPLEPROC) (GLsync sync, GLenum pname, GLsizei شمېر, GLsizei *اوږدتیا, GLint *ارزښتونه);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL GLsync GL_APIENTRY glFenceSyncAPPLE (GLenum condition, GLbitfield flags);
GL_APICALL GLboolean GL_APIENTRY glIsSyncAPPLE (GLsync sync);
GL_APICALL فراغ GL_APIENTRY glDeleteSyncAPPLE (GLsync sync);
GL_APICALL GLenum GL_APIENTRY glClientWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_APICALL فراغ GL_APIENTRY glWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_APICALL فراغ GL_APIENTRY glGetInteger64vAPPLE (GLenum pname, GLint64 *params);
GL_APICALL فراغ GL_APIENTRY glGetSyncivAPPLE (GLsync sync, GLenum pname, GLsizei شمېر, GLsizei *اوږدتیا, GLint *ارزښتونه);
#د_که_پای
#د_که_پای /* GL_APPLE_sync */

#که_نه_تعریف_شوی GL_APPLE_texture_format_BGRA8888
#تعریف_کړه GL_APPLE_texture_format_BGRA8888 1
#تعریف_کړه GL_BGRA_EXT                       0x80E1
#تعریف_کړه GL_BGRA8_EXT                      0x93A1
#د_که_پای /* GL_APPLE_texture_format_BGRA8888 */

#که_نه_تعریف_شوی GL_APPLE_texture_max_level
#تعریف_کړه GL_APPLE_texture_max_level 1
#تعریف_کړه GL_TEXTURE_MAX_LEVEL_APPLE        0x813D
#د_که_پای /* GL_APPLE_texture_max_level */

#که_نه_تعریف_شوی GL_APPLE_texture_packed_float
#تعریف_کړه GL_APPLE_texture_packed_float 1
#تعریف_کړه GL_UNSIGNED_INT_10F_11F_11F_REV_APPLE 0x8C3B
#تعریف_کړه GL_UNSIGNED_INT_5_9_9_9_REV_APPLE 0x8C3E
#تعریف_کړه GL_R11F_G11F_B10F_APPLE           0x8C3A
#تعریف_کړه GL_RGB9_E5_APPLE                  0x8C3D
#د_که_پای /* GL_APPLE_texture_packed_float */

#که_نه_تعریف_شوی GL_ARM_mali_پروګرام_دوګونی
#تعریف_کړه GL_ARM_mali_پروګرام_دوګونی 1
#تعریف_کړه GL_MALI_پروګرام_دوګونی_ARM        0x8F61
#د_که_پای /* GL_ARM_mali_program_binary */

#که_نه_تعریف_شوی GL_ARM_mali_shader_دوګونی
#تعریف_کړه GL_ARM_mali_shader_دوګونی 1
#تعریف_کړه GL_MALI_SHADER_دوګونی_ARM         0x8F60
#د_که_پای /* GL_ARM_mali_shader_binary */

#که_نه_تعریف_شوی GL_ARM_rgba8
#تعریف_کړه GL_ARM_rgba8 1
#د_که_پای /* GL_ARM_rgba8 */

#که_نه_تعریف_شوی GL_ARM_shader_core_properties
#تعریف_کړه GL_ARM_shader_core_properties 1
#تعریف_کړه GL_SHADER_CORE_شمېر_ARM          0x96F0
#تعریف_کړه GL_SHADER_CORE_فعال_شمېر_ARM   0x96F1
#تعریف_کړه GL_SHADER_CORE_PRESENT_ماسک_ARM   0x96F2
#تعریف_کړه GL_SHADER_CORE_MAX_WARP_شمېر_ARM 0x96F3
#تعریف_کړه GL_SHADER_CORE_PIXEL_شرح_ARM     0x96F4
#تعریف_کړه GL_SHADER_CORE_TEXEL_شرح_ARM     0x96F5
#تعریف_کړه GL_SHADER_CORE_FMA_شرح_ARM       0x96F6
تعريفنوع فراغ (GL_APIENTRYP PFNGLMAXACTIVESHADERCORESARMPROC) (GLuint شمېر);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Max_فعال_Shader_Cores_ARM (GLuint شمېر);
#د_که_پای
#د_که_پای /* GL_ARM_shader_core_properties */

#که_نه_تعریف_شوی GL_ARM_shader_framebuffer_fetch
#تعریف_کړه GL_ARM_shader_framebuffer_fetch 1
#تعریف_کړه GL_FETCH_فی_SAMPLE_ARM           0x8F65
#تعریف_کړه GL_FRAGMENT_SHADER_FRAMEBUFFER_FETCH_MRT_ARM 0x8F66
#د_که_پای /* GL_ARM_shader_framebuffer_fetch */

#که_نه_تعریف_شوی GL_ARM_shader_framebuffer_fetch_ژوروالی_stencil
#تعریف_کړه GL_ARM_shader_framebuffer_fetch_ژوروالی_stencil 1
#د_که_پای /* GL_ARM_shader_framebuffer_fetch_depth_stencil */

#که_نه_تعریف_شوی GL_ARM_texture_unnormalized_coordinates
#تعریف_کړه GL_ARM_texture_unnormalized_coordinates 1
#تعریف_کړه GL_TEXTURE_UNNORMALIZED_COORDINATES_ARM 0x8F6A
#د_که_پای /* GL_ARM_texture_unnormalized_coordinates */

#که_نه_تعریف_شوی GL_DMP_پروګرام_دوګونی
#تعریف_کړه GL_DMP_پروګرام_دوګونی 1
#تعریف_کړه GL_SMAPHS30_پروګرام_دوګونی_DMP    0x9251
#تعریف_کړه GL_SMAPHS_پروګرام_دوګونی_DMP      0x9252
#تعریف_کړه GL_DMP_پروګرام_دوګونی_DMP         0x9253
#د_که_پای /* GL_DMP_program_binary */

#که_نه_تعریف_شوی GL_DMP_shader_دوګونی
#تعریف_کړه GL_DMP_shader_دوګونی 1
#تعریف_کړه GL_SHADER_دوګونی_DMP              0x9250
#د_که_پای /* GL_DMP_shader_binary */

#که_نه_تعریف_شوی GL_EXT_EGL_image_array
#تعریف_کړه GL_EXT_EGL_image_array 1
#د_که_پای /* GL_EXT_EGL_image_array */

#که_نه_تعریف_شوی GL_EXT_EGL_image_storage
#تعریف_کړه GL_EXT_EGL_image_storage 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLEGLIMAGETARGETTEXSTORAGEEXTPROC) (GLenum موخه, GLeglImageOES image, ثابت GLint* attrib_list);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEGLIMAGETARGETTEXTURESTORAGEEXTPROC) (GLuint texture, GLeglImageOES image, ثابت GLint* attrib_list);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_EGLImage_موخه_Tex_Storage_EXT (GLenum موخه, GLeglImageOES image, ثابت GLint* attrib_list);
GL_APICALL فراغ GL_APIENTRY gl_EGLImage_موخه_Texture_Storage_EXT (GLuint texture, GLeglImageOES image, ثابت GLint* attrib_list);
#د_که_پای
#د_که_پای /* GL_EXT_EGL_image_storage */

#که_نه_تعریف_شوی GL_EXT_EGL_image_storage_compression
#تعریف_کړه GL_EXT_EGL_image_storage_compression 1
#تعریف_کړه GL_SURFACE_COMPRESSION_EXT        0x96C0
#تعریف_کړه GL_SURFACE_COMPRESSION_FIXED_شرح_NONE_EXT 0x96C1
#تعریف_کړه GL_SURFACE_COMPRESSION_FIXED_شرح_DEFAULT_EXT 0x96C2
#د_که_پای /* GL_EXT_EGL_image_storage_compression */

#که_نه_تعریف_شوی GL_EXT_YUV_موخه
#تعریف_کړه GL_EXT_YUV_موخه 1
#تعریف_کړه GL_SAMPLER_EXTERNAL_2D_Y2Y_EXT    0x8BE7
#د_که_پای /* GL_EXT_YUV_target */

#که_نه_تعریف_شوی GL_EXT_بنسټ_instance
#تعریف_کړه GL_EXT_بنسټ_instance 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEEXTPROC) (GLenum ډېرپېښ, GLint لومړی, GLsizei شمېر, GLsizei instancecount, GLuint baseinstance);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEEXTPROC) (GLenum ډېرپېښ, GLsizei شمېر, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLuint baseinstance);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEEXTPROC) (GLenum ډېرپېښ, GLsizei شمېر, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Draw_Arrays_Instanced_بنسټ_Instance_EXT (GLenum ډېرپېښ, GLint لومړی, GLsizei شمېر, GLsizei instancecount, GLuint baseinstance);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Elements_Instanced_بنسټ_Instance_EXT (GLenum ډېرپېښ, GLsizei شمېر, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLuint baseinstance);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Elements_Instanced_بنسټ_راس_بنسټ_Instance_EXT (GLenum ډېرپېښ, GLsizei شمېر, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance);
#د_که_پای
#د_که_پای /* GL_EXT_base_instance */

#که_نه_تعریف_شوی GL_EXT_blend_func_extended
#تعریف_کړه GL_EXT_blend_func_extended 1
#تعریف_کړه GL_SRC1_COLOR_EXT                 0x88F9
#تعریف_کړه GL_SRC1_ALPHA_EXT                 0x8589
#تعریف_کړه GL_ONE_MINUS_SRC1_COLOR_EXT       0x88FA
#تعریف_کړه GL_ONE_MINUS_SRC1_ALPHA_EXT       0x88FB
#تعریف_کړه GL_SRC_ALPHA_SATURATE_EXT         0x0308
#تعریف_کړه GL_LOCATION_شاخص_EXT             0x930F
#تعریف_کړه GL_MAX_DUAL_سرچینه_DRAW_BUFFERS_EXT 0x88FC
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDFRAGDATALOCATIONINDEXEDEXTPROC) (GLuint پروګرام, GLuint color_شمېره, GLuint شاخص, ثابت GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDFRAGDATALOCATIONEXTPROC) (GLuint پروګرام, GLuint color, ثابت GLchar *name);
تعريفنوع GLint (GL_APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONINDEXEXTPROC) (GLuint پروګرام, GLenum پروګرام_Interface, ثابت GLchar *name);
تعريفنوع GLint (GL_APIENTRYP PFNGLGETFRAGDATAINDEXEXTPROC) (GLuint پروګرام, ثابت GLchar *name);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Bind_Frag_معلومات_Location_شاخصي_EXT (GLuint پروګرام, GLuint color_شمېره, GLuint شاخص, ثابت GLchar *name);
GL_APICALL فراغ GL_APIENTRY gl_Bind_Frag_معلومات_Location_EXT (GLuint پروګرام, GLuint color, ثابت GLchar *name);
GL_APICALL GLint GL_APIENTRY gl_Get_پروګرام_Resource_Location_شاخص_EXT (GLuint پروګرام, GLenum پروګرام_Interface, ثابت GLchar *name);
GL_APICALL GLint GL_APIENTRY gl_Get_Frag_معلومات_شاخص_EXT (GLuint پروګرام, ثابت GLchar *name);
#د_که_پای
#د_که_پای /* GL_EXT_blend_func_extended */

#که_نه_تعریف_شوی GL_EXT_blend_minmax
#تعریف_کړه GL_EXT_blend_minmax 1
#تعریف_کړه GL_MIN_EXT                        0x8007
#تعریف_کړه GL_MAX_EXT                        0x8008
#د_که_پای /* GL_EXT_blend_minmax */

#که_نه_تعریف_شوی GL_EXT_بفر_storage
#تعریف_کړه GL_EXT_بفر_storage 1
#تعریف_کړه GL_MAP_READ_بټ                   0x0001
#تعریف_کړه GL_MAP_WRITE_بټ                  0x0002
#تعریف_کړه GL_MAP_PERSISTENT_بټ_EXT         0x0040
#تعریف_کړه GL_MAP_COHERENT_بټ_EXT           0x0080
#تعریف_کړه GL_DYNAMIC_STORAGE_بټ_EXT        0x0100
#تعریف_کړه GL_CLIENT_STORAGE_بټ_EXT         0x0200
#تعریف_کړه GL_CLIENT_MAPPED_بفر_BARRIER_بټ_EXT 0x00004000
#تعریف_کړه GL_بفر_IMMUTABLE_STORAGE_EXT   0x821F
#تعریف_کړه GL_بفر_STORAGE_FLAGS_EXT       0x8220
تعريفنوع فراغ (GL_APIENTRYP PFNGLBUFFERSTORAGEEXTPROC) (GLenum موخه, GLsizeiptr اندازه, ثابت فراغ *معلومات, GLbitfield flags);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_بفر_Storage_EXT (GLenum موخه, GLsizeiptr اندازه, ثابت فراغ *معلومات, GLbitfield flags);
#د_که_پای
#د_که_پای /* GL_EXT_buffer_storage */

#که_نه_تعریف_شوی GL_EXT_clear_texture
#تعریف_کړه GL_EXT_clear_texture 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARTEXIMAGEEXTPROC) (GLuint texture, GLint level, GLenum format, GLenum type, ثابت فراغ *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARTEXSUBIMAGEEXTPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLenum format, GLenum type, ثابت فراغ *معلومات);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glClearTexImageEXT (GLuint texture, GLint level, GLenum format, GLenum type, ثابت فراغ *معلومات);
GL_APICALL فراغ GL_APIENTRY glClearTexSubImageEXT (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLenum format, GLenum type, ثابت فراغ *معلومات);
#د_که_پای
#د_که_پای /* GL_EXT_clear_texture */

#که_نه_تعریف_شوی GL_EXT_clip_control
#تعریف_کړه GL_EXT_clip_control 1
#تعریف_کړه GL_ښکتنی_کیڼ_EXT                 0x8CA1
#تعریف_کړه GL_پاسنی_کیڼ_EXT                 0x8CA2
#تعریف_کړه GL_NEGATIVE_ONE_منزل_ONE_EXT        0x935E
#تعریف_کړه GL_ZERO_منزل_ONE_EXT                0x935F
#تعریف_کړه GL_CLIP_ORIGIN_EXT                0x935C
#تعریف_کړه GL_CLIP_ژوروالی_ډېرپېښ_EXT            0x935D
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLIPCONTROLEXTPROC) (GLenum origin, GLenum ژوروالی_2);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glClipControlEXT (GLenum origin, GLenum ژوروالی_2);
#د_که_پای
#د_که_پای /* GL_EXT_clip_control */

#که_نه_تعریف_شوی GL_EXT_clip_cull_واټن
#تعریف_کړه GL_EXT_clip_cull_واټن 1
#تعریف_کړه GL_MAX_CLIP_DISTANCES_EXT         0x0D32
#تعریف_کړه GL_MAX_CULL_DISTANCES_EXT         0x82F9
#تعریف_کړه GL_MAX_COMBINED_CLIP_AND_CULL_DISTANCES_EXT 0x82FA
#تعریف_کړه GL_CLIP_DISTANCE0_EXT             0x3000
#تعریف_کړه GL_CLIP_DISTANCE1_EXT             0x3001
#تعریف_کړه GL_CLIP_DISTANCE2_EXT             0x3002
#تعریف_کړه GL_CLIP_DISTANCE3_EXT             0x3003
#تعریف_کړه GL_CLIP_DISTANCE4_EXT             0x3004
#تعریف_کړه GL_CLIP_DISTANCE5_EXT             0x3005
#تعریف_کړه GL_CLIP_DISTANCE6_EXT             0x3006
#تعریف_کړه GL_CLIP_DISTANCE7_EXT             0x3007
#د_که_پای /* GL_EXT_clip_cull_distance */

#که_نه_تعریف_شوی GL_EXT_color_بفر_float
#تعریف_کړه GL_EXT_color_بفر_float 1
#د_که_پای /* GL_EXT_color_buffer_float */

#که_نه_تعریف_شوی GL_EXT_color_بفر_half_float
#تعریف_کړه GL_EXT_color_بفر_half_float 1
#تعریف_کړه GL_RGBA16F_EXT                    0x881A
#تعریف_کړه GL_RGB16F_EXT                     0x881B
#تعریف_کړه GL_RG16F_EXT                      0x822F
#تعریف_کړه GL_R16F_EXT                       0x822D
#تعریف_کړه GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE_EXT 0x8211
#تعریف_کړه GL_UNSIGNED_NORMALIZED_EXT        0x8C17
#د_که_پای /* GL_EXT_color_buffer_half_float */

#که_نه_تعریف_شوی GL_EXT_conservative_ژوروالی
#تعریف_کړه GL_EXT_conservative_ژوروالی 1
#د_که_پای /* GL_EXT_conservative_depth */

#که_نه_تعریف_شوی GL_EXT_copy_image
#تعریف_کړه GL_EXT_copy_image 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYIMAGESUBDATAEXTPROC) (GLuint srcName, GLenum src_موخه, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dst_موخه, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei src_پلنوالی, GLsizei src_لوړوالی, GLsizei src_ژوروالی);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Copy_Image_Sub_معلومات_EXT (GLuint srcName, GLenum src_موخه, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dst_موخه, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei src_پلنوالی, GLsizei src_لوړوالی, GLsizei src_ژوروالی);
#د_که_پای
#د_که_پای /* GL_EXT_copy_image */

#که_نه_تعریف_شوی GL_EXT_debug_label
#تعریف_کړه GL_EXT_debug_label 1
#تعریف_کړه GL_پروګرام_PIPELINE_OBJECT_EXT    0x8A4F
#تعریف_کړه GL_پروګرام_OBJECT_EXT             0x8B40
#تعریف_کړه GL_SHADER_OBJECT_EXT              0x8B48
#تعریف_کړه GL_بفر_OBJECT_EXT              0x9151
#تعریف_کړه GL_QUERY_OBJECT_EXT               0x9153
#تعریف_کړه GL_راس_ARRAY_OBJECT_EXT        0x9154
#تعریف_کړه GL_TRANSFORM_FEEDBACK             0x8E22
تعريفنوع فراغ (GL_APIENTRYP PFNGLLABELOBJECTEXTPROC) (GLenum type, GLuint object, GLsizei اوږدتیا, ثابت GLchar *label);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETOBJECTLABELEXTPROC) (GLenum type, GLuint object, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLchar *label);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glLabelObjectEXT (GLenum type, GLuint object, GLsizei اوږدتیا, ثابت GLchar *label);
GL_APICALL فراغ GL_APIENTRY glGetObjectLabelEXT (GLenum type, GLuint object, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLchar *label);
#د_که_پای
#د_که_پای /* GL_EXT_debug_label */

#که_نه_تعریف_شوی GL_EXT_debug_marker
#تعریف_کړه GL_EXT_debug_marker 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLINSERTEVENTMARKEREXTPROC) (GLsizei اوږدتیا, ثابت GLchar *marker);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPUSHGROUPMARKEREXTPROC) (GLsizei اوږدتیا, ثابت GLchar *marker);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOPGROUPMARKEREXTPROC) (فراغ);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_ورننباسه_Event_Marker_EXT (GLsizei اوږدتیا, ثابت GLchar *marker);
GL_APICALL فراغ GL_APIENTRY gl_ټېل_ډله_Marker_EXT (GLsizei اوږدتیا, ثابت GLchar *marker);
GL_APICALL فراغ GL_APIENTRY gl_راوباسه_ډله_Marker_EXT (فراغ);
#د_که_پای
#د_که_پای /* GL_EXT_debug_marker */

#که_نه_تعریف_شوی GL_EXT_ژوروالی_clamp
#تعریف_کړه GL_EXT_ژوروالی_clamp 1
#تعریف_کړه GL_ژوروالی_CLAMP_EXT                0x864F
#د_که_پای /* GL_EXT_depth_clamp */

#که_نه_تعریف_شوی GL_EXT_discard_framebuffer
#تعریف_کړه GL_EXT_discard_framebuffer 1
#تعریف_کړه GL_COLOR_EXT                      0x1800
#تعریف_کړه GL_ژوروالی_EXT                      0x1801
#تعریف_کړه GL_STENCIL_EXT                    0x1802
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISCARDFRAMEBUFFEREXTPROC) (GLenum موخه, GLsizei عدد_Attachments, ثابت GLenum *attachments);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDiscardFramebufferEXT (GLenum موخه, GLsizei عدد_Attachments, ثابت GLenum *attachments);
#د_که_پای
#د_که_پای /* GL_EXT_discard_framebuffer */

#که_نه_تعریف_شوی GL_EXT_disjoint_timer_query
#تعریف_کړه GL_EXT_disjoint_timer_query 1
#تعریف_کړه GL_QUERY_COUNTER_بټونه_EXT         0x8864
#تعریف_کړه GL_CURRENT_QUERY_EXT              0x8865
#تعریف_کړه GL_QUERY_پایله_EXT               0x8866
#تعریف_کړه GL_QUERY_پایله_شته_EXT     0x8867
#تعریف_کړه GL_وخت_ELAPSED_EXT               0x88BF
#تعریف_کړه GL_TIMESTAMP_EXT                  0x8E28
#تعریف_کړه GL_GPU_DISJOINT_EXT               0x8FBB
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENQUERIESEXTPROC) (GLsizei n, GLuint *ids);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEQUERIESEXTPROC) (GLsizei n, ثابت GLuint *ids);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISQUERYEXTPROC) (GLuint id);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBEGINQUERYEXTPROC) (GLenum موخه, GLuint id);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENDQUERYEXTPROC) (GLenum موخه);
تعريفنوع فراغ (GL_APIENTRYP PFNGLQUERYCOUNTEREXTPROC) (GLuint id, GLenum موخه);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETQUERYIVEXTPROC) (GLenum موخه, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETQUERYOBJECTIVEXTPROC) (GLuint id, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETQUERYOBJECTUIVEXTPROC) (GLuint id, GLenum pname, GLuint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETQUERYOBJECTI64VEXTPROC) (GLuint id, GLenum pname, GLint64 *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETQUERYOBJECTUI64VEXTPROC) (GLuint id, GLenum pname, GLuint64 *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTEGER64VEXTPROC) (GLenum pname, GLint64 *معلومات);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glGenQueriesEXT (GLsizei n, GLuint *ids);
GL_APICALL فراغ GL_APIENTRY glDeleteQueriesEXT (GLsizei n, ثابت GLuint *ids);
GL_APICALL GLboolean GL_APIENTRY glIsQueryEXT (GLuint id);
GL_APICALL فراغ GL_APIENTRY glBeginQueryEXT (GLenum موخه, GLuint id);
GL_APICALL فراغ GL_APIENTRY gl_پای_ټکی_Query_EXT (GLenum موخه);
GL_APICALL فراغ GL_APIENTRY glQueryCounterEXT (GLuint id, GLenum موخه);
GL_APICALL فراغ GL_APIENTRY glGetQueryivEXT (GLenum موخه, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetQueryObjectivEXT (GLuint id, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetQueryObjectuivEXT (GLuint id, GLenum pname, GLuint *params);
GL_APICALL فراغ GL_APIENTRY glGetQueryObjecti64vEXT (GLuint id, GLenum pname, GLint64 *params);
GL_APICALL فراغ GL_APIENTRY glGetQueryObjectui64vEXT (GLuint id, GLenum pname, GLuint64 *params);
GL_APICALL فراغ GL_APIENTRY glGetInteger64vEXT (GLenum pname, GLint64 *معلومات);
#د_که_پای
#د_که_پای /* GL_EXT_disjoint_timer_query */

#که_نه_تعریف_شوی GL_EXT_draw_buffers
#تعریف_کړه GL_EXT_draw_buffers 1
#تعریف_کړه GL_MAX_COLOR_ATTACHMENTS_EXT      0x8CDF
#تعریف_کړه GL_MAX_DRAW_BUFFERS_EXT           0x8824
#تعریف_کړه GL_DRAW_BUFFER0_EXT               0x8825
#تعریف_کړه GL_DRAW_BUFFER1_EXT               0x8826
#تعریف_کړه GL_DRAW_BUFFER2_EXT               0x8827
#تعریف_کړه GL_DRAW_BUFFER3_EXT               0x8828
#تعریف_کړه GL_DRAW_BUFFER4_EXT               0x8829
#تعریف_کړه GL_DRAW_BUFFER5_EXT               0x882A
#تعریف_کړه GL_DRAW_BUFFER6_EXT               0x882B
#تعریف_کړه GL_DRAW_BUFFER7_EXT               0x882C
#تعریف_کړه GL_DRAW_BUFFER8_EXT               0x882D
#تعریف_کړه GL_DRAW_BUFFER9_EXT               0x882E
#تعریف_کړه GL_DRAW_BUFFER10_EXT              0x882F
#تعریف_کړه GL_DRAW_BUFFER11_EXT              0x8830
#تعریف_کړه GL_DRAW_BUFFER12_EXT              0x8831
#تعریف_کړه GL_DRAW_BUFFER13_EXT              0x8832
#تعریف_کړه GL_DRAW_BUFFER14_EXT              0x8833
#تعریف_کړه GL_DRAW_BUFFER15_EXT              0x8834
#تعریف_کړه GL_COLOR_ATTACHMENT0_EXT          0x8CE0
#تعریف_کړه GL_COLOR_ATTACHMENT1_EXT          0x8CE1
#تعریف_کړه GL_COLOR_ATTACHMENT2_EXT          0x8CE2
#تعریف_کړه GL_COLOR_ATTACHMENT3_EXT          0x8CE3
#تعریف_کړه GL_COLOR_ATTACHMENT4_EXT          0x8CE4
#تعریف_کړه GL_COLOR_ATTACHMENT5_EXT          0x8CE5
#تعریف_کړه GL_COLOR_ATTACHMENT6_EXT          0x8CE6
#تعریف_کړه GL_COLOR_ATTACHMENT7_EXT          0x8CE7
#تعریف_کړه GL_COLOR_ATTACHMENT8_EXT          0x8CE8
#تعریف_کړه GL_COLOR_ATTACHMENT9_EXT          0x8CE9
#تعریف_کړه GL_COLOR_ATTACHMENT10_EXT         0x8CEA
#تعریف_کړه GL_COLOR_ATTACHMENT11_EXT         0x8CEB
#تعریف_کړه GL_COLOR_ATTACHMENT12_EXT         0x8CEC
#تعریف_کړه GL_COLOR_ATTACHMENT13_EXT         0x8CED
#تعریف_کړه GL_COLOR_ATTACHMENT14_EXT         0x8CEE
#تعریف_کړه GL_COLOR_ATTACHMENT15_EXT         0x8CEF
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWBUFFERSEXTPROC) (GLsizei n, ثابت GLenum *bufs);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawBuffersEXT (GLsizei n, ثابت GLenum *bufs);
#د_که_پای
#د_که_پای /* GL_EXT_draw_buffers */

#که_نه_تعریف_شوی GL_EXT_draw_buffers_شاخصي
#تعریف_کړه GL_EXT_draw_buffers_شاخصي 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLENABLEIEXTPROC) (GLenum موخه, GLuint شاخص);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISABLEIEXTPROC) (GLenum موخه, GLuint شاخص);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONIEXTPROC) (GLuint buf, GLenum ډېرپېښ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEIEXTPROC) (GLuint buf, GLenum ډېرپېښ_RGB, GLenum ډېرپېښ_Alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDFUNCIEXTPROC) (GLuint buf, GLenum src, GLenum dst);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEIEXTPROC) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOLORMASKIEXTPROC) (GLuint شاخص, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISENABLEDIEXTPROC) (GLenum موخه, GLuint شاخص);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glEnableiEXT (GLenum موخه, GLuint شاخص);
GL_APICALL فراغ GL_APIENTRY glDisableiEXT (GLenum موخه, GLuint شاخص);
GL_APICALL فراغ GL_APIENTRY glBlendEquationiEXT (GLuint buf, GLenum ډېرپېښ);
GL_APICALL فراغ GL_APIENTRY glBlendEquationSeparateiEXT (GLuint buf, GLenum ډېرپېښ_RGB, GLenum ډېرپېښ_Alpha);
GL_APICALL فراغ GL_APIENTRY glBlendFunciEXT (GLuint buf, GLenum src, GLenum dst);
GL_APICALL فراغ GL_APIENTRY glBlendFuncSeparateiEXT (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
GL_APICALL فراغ GL_APIENTRY glColorMaskiEXT (GLuint شاخص, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
GL_APICALL GLboolean GL_APIENTRY glIsEnablediEXT (GLenum موخه, GLuint شاخص);
#د_که_پای
#د_که_پای /* GL_EXT_draw_buffers_indexed */

#که_نه_تعریف_شوی GL_EXT_draw_elements_بنسټ_راس
#تعریف_کړه GL_EXT_draw_elements_بنسټ_راس 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSBASEVERTEXEXTPROC) (GLenum ډېرپېښ, GLsizei شمېر, GLenum type, ثابت فراغ *indices, GLint basevertex);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWRANGEELEMENTSBASEVERTEXEXTPROC) (GLenum ډېرپېښ, GLuint پیل, GLuint پای_ټکی, GLsizei شمېر, GLenum type, ثابت فراغ *indices, GLint basevertex);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXEXTPROC) (GLenum ډېرپېښ, GLsizei شمېر, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLint basevertex);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Draw_Elements_بنسټ_راس_EXT (GLenum ډېرپېښ, GLsizei شمېر, GLenum type, ثابت فراغ *indices, GLint basevertex);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Range_Elements_بنسټ_راس_EXT (GLenum ډېرپېښ, GLuint پیل, GLuint پای_ټکی, GLsizei شمېر, GLenum type, ثابت فراغ *indices, GLint basevertex);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Elements_Instanced_بنسټ_راس_EXT (GLenum ډېرپېښ, GLsizei شمېر, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLint basevertex);
#د_که_پای
#د_که_پای /* GL_EXT_draw_elements_base_vertex */

#که_نه_تعریف_شوی GL_EXT_draw_instanced
#تعریف_کړه GL_EXT_draw_instanced 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDEXTPROC) (GLenum ډېرپېښ, GLint پیل, GLsizei شمېر, GLsizei primcount);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDEXTPROC) (GLenum ډېرپېښ, GLsizei شمېر, GLenum type, ثابت فراغ *indices, GLsizei primcount);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawArraysInstancedEXT (GLenum ډېرپېښ, GLint پیل, GLsizei شمېر, GLsizei primcount);
GL_APICALL فراغ GL_APIENTRY glDrawElementsInstancedEXT (GLenum ډېرپېښ, GLsizei شمېر, GLenum type, ثابت فراغ *indices, GLsizei primcount);
#د_که_پای
#د_که_پای /* GL_EXT_draw_instanced */

#که_نه_تعریف_شوی GL_EXT_draw_transform_feedback
#تعریف_کړه GL_EXT_draw_transform_feedback 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKEXTPROC) (GLenum ډېرپېښ, GLuint id);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDEXTPROC) (GLenum ډېرپېښ, GLuint id, GLsizei instancecount);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawTransformFeedbackEXT (GLenum ډېرپېښ, GLuint id);
GL_APICALL فراغ GL_APIENTRY glDrawTransformFeedbackInstancedEXT (GLenum ډېرپېښ, GLuint id, GLsizei instancecount);
#د_که_پای
#د_که_پای /* GL_EXT_draw_transform_feedback */

#که_نه_تعریف_شوی GL_EXT_external_بفر
#تعریف_کړه GL_EXT_external_بفر 1
تعريفنوع فراغ *GLegl_Client_بفر_EXT;
تعريفنوع فراغ (GL_APIENTRYP PFNGLBUFFERSTORAGEEXTERNALEXTPROC) (GLenum موخه, GLintptr دننه_واټن_2, GLsizeiptr اندازه, GLegl_Client_بفر_EXT client_بفر, GLbitfield flags);
تعريفنوع فراغ (GL_APIENTRYP PFNGLNAMEDBUFFERSTORAGEEXTERNALEXTPROC) (GLuint بفر_2, GLintptr دننه_واټن_2, GLsizeiptr اندازه, GLegl_Client_بفر_EXT client_بفر, GLbitfield flags);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_بفر_Storage_External_EXT (GLenum موخه, GLintptr دننه_واټن_2, GLsizeiptr اندازه, GLegl_Client_بفر_EXT client_بفر, GLbitfield flags);
GL_APICALL فراغ GL_APIENTRY gl_Named_بفر_Storage_External_EXT (GLuint بفر_2, GLintptr دننه_واټن_2, GLsizeiptr اندازه, GLegl_Client_بفر_EXT client_بفر, GLbitfield flags);
#د_که_پای
#د_که_پای /* GL_EXT_external_buffer */

#که_نه_تعریف_شوی GL_EXT_float_blend
#تعریف_کړه GL_EXT_float_blend 1
#د_که_پای /* GL_EXT_float_blend */

#که_نه_تعریف_شوی GL_EXT_fragment_shading_شرح
#تعریف_کړه GL_EXT_fragment_shading_شرح 1
#تعریف_کړه GL_SHADING_شرح_1_X1_PIXELS_EXT    0x96A6
#تعریف_کړه GL_SHADING_شرح_1_X2_PIXELS_EXT    0x96A7
#تعریف_کړه GL_SHADING_شرح_2_X1_PIXELS_EXT    0x96A8
#تعریف_کړه GL_SHADING_شرح_2_X2_PIXELS_EXT    0x96A9
#تعریف_کړه GL_SHADING_شرح_1_X4_PIXELS_EXT    0x96AA
#تعریف_کړه GL_SHADING_شرح_4_X1_PIXELS_EXT    0x96AB
#تعریف_کړه GL_SHADING_شرح_4_X2_PIXELS_EXT    0x96AC
#تعریف_کړه GL_SHADING_شرح_2_X4_PIXELS_EXT    0x96AD
#تعریف_کړه GL_SHADING_شرح_4_X4_PIXELS_EXT    0x96AE
#تعریف_کړه GL_SHADING_شرح_EXT               0x96D0
#تعریف_کړه GL_SHADING_شرح_ATTACHMENT_EXT    0x96D1
#تعریف_کړه GL_FRAGMENT_SHADING_شرح_COMBINER_OP_KEEP_EXT 0x96D2
#تعریف_کړه GL_FRAGMENT_SHADING_شرح_COMBINER_OP_REPLACE_EXT 0x96D3
#تعریف_کړه GL_FRAGMENT_SHADING_شرح_COMBINER_OP_MIN_EXT 0x96D4
#تعریف_کړه GL_FRAGMENT_SHADING_شرح_COMBINER_OP_MAX_EXT 0x96D5
#تعریف_کړه GL_FRAGMENT_SHADING_شرح_COMBINER_OP_MUL_EXT 0x96D6
#تعریف_کړه GL_MIN_FRAGMENT_SHADING_شرح_ATTACHMENT_TEXEL_پلنوالی_EXT 0x96D7
#تعریف_کړه GL_MAX_FRAGMENT_SHADING_شرح_ATTACHMENT_TEXEL_پلنوالی_EXT 0x96D8
#تعریف_کړه GL_MIN_FRAGMENT_SHADING_شرح_ATTACHMENT_TEXEL_لوړوالی_EXT 0x96D9
#تعریف_کړه GL_MAX_FRAGMENT_SHADING_شرح_ATTACHMENT_TEXEL_لوړوالی_EXT 0x96DA
#تعریف_کړه GL_MAX_FRAGMENT_SHADING_شرح_ATTACHMENT_TEXEL_ASPECT_نسبت_EXT 0x96DB
#تعریف_کړه GL_MAX_FRAGMENT_SHADING_شرح_ATTACHMENT_LAYERS_EXT 0x96DC
#تعریف_کړه GL_FRAGMENT_SHADING_شرح_WITH_SHADER_ژوروالی_STENCIL_WRITES_SUPPORTED_EXT 0x96DD
#تعریف_کړه GL_FRAGMENT_SHADING_شرح_WITH_SAMPLE_ماسک_SUPPORTED_EXT 0x96DE
#تعریف_کړه GL_FRAGMENT_SHADING_شرح_ATTACHMENT_WITH_DEFAULT_FRAMEBUFFER_SUPPORTED_EXT 0x96DF
#تعریف_کړه GL_FRAGMENT_SHADING_شرح_NON_TRIVIAL_COMBINERS_SUPPORTED_EXT 0x8F6F
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFRAGMENTSHADINGRATESEXTPROC) (GLsizei samples, GLsizei max_شمېر, GLsizei *شمېر, GLenum *shadingRates);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADINGRATEEXTPROC) (GLenum شرح);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADINGRATECOMBINEROPSEXTPROC) (GLenum combinerOp0, GLenum combinerOp1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERSHADINGRATEEXTPROC) (GLenum موخه, GLenum attachment, GLuint texture, GLint بنسټ_Layer, GLsizei عدد_Layers, GLsizei texel_پلنوالی, GLsizei texel_لوړوالی);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glGetFragmentShadingRatesEXT (GLsizei samples, GLsizei max_شمېر, GLsizei *شمېر, GLenum *shadingRates);
GL_APICALL فراغ GL_APIENTRY gl_Shading_شرح_EXT (GLenum شرح);
GL_APICALL فراغ GL_APIENTRY gl_Shading_شرح_Combiner_Ops_EXT (GLenum combinerOp0, GLenum combinerOp1);
GL_APICALL فراغ GL_APIENTRY gl_Framebuffer_Shading_شرح_EXT (GLenum موخه, GLenum attachment, GLuint texture, GLint بنسټ_Layer, GLsizei عدد_Layers, GLsizei texel_پلنوالی, GLsizei texel_لوړوالی);
#د_که_پای
#د_که_پای /* GL_EXT_fragment_shading_rate */

#که_نه_تعریف_شوی GL_EXT_framebuffer_blit_layers
#تعریف_کړه GL_EXT_framebuffer_blit_layers 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLITFRAMEBUFFERLAYERSEXTPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield ماسک, GLenum filter);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLITFRAMEBUFFERLAYEREXTPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint srcLayer, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLint dstLayer, GLbitfield ماسک, GLenum filter);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glBlitFramebufferLayersEXT (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield ماسک, GLenum filter);
GL_APICALL فراغ GL_APIENTRY glBlitFramebufferLayerEXT (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint srcLayer, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLint dstLayer, GLbitfield ماسک, GLenum filter);
#د_که_پای
#د_که_پای /* GL_EXT_framebuffer_blit_layers */

#که_نه_تعریف_شوی GL_EXT_geometry_ټکی_اندازه
#تعریف_کړه GL_EXT_geometry_ټکی_اندازه 1
#د_که_پای /* GL_EXT_geometry_point_size */

#که_نه_تعریف_شوی GL_EXT_geometry_shader
#تعریف_کړه GL_EXT_geometry_shader 1
#تعریف_کړه GL_GEOMETRY_SHADER_EXT            0x8DD9
#تعریف_کړه GL_GEOMETRY_SHADER_بټ_EXT        0x00000004
#تعریف_کړه GL_GEOMETRY_LINKED_VERTICES_بهر_EXT 0x8916
#تعریف_کړه GL_GEOMETRY_LINKED_ننوت_TYPE_EXT 0x8917
#تعریف_کړه GL_GEOMETRY_LINKED_OUTPUT_TYPE_EXT 0x8918
#تعریف_کړه GL_GEOMETRY_SHADER_INVOCATIONS_EXT 0x887F
#تعریف_کړه GL_LAYER_PROVOKING_راس_EXT     0x825E
#تعریف_کړه GL_کرښې_ADJACENCY_EXT            0x000A
#تعریف_کړه GL_کرښه_STRIP_ADJACENCY_EXT       0x000B
#تعریف_کړه GL_TRIANGLES_ADJACENCY_EXT        0x000C
#تعریف_کړه GL_TRIANGLE_STRIP_ADJACENCY_EXT   0x000D
#تعریف_کړه GL_MAX_GEOMETRY_یوشان_COMPONENTS_EXT 0x8DDF
#تعریف_کړه GL_MAX_GEOMETRY_یوشان_بلاکونه_EXT 0x8A2C
#تعریف_کړه GL_MAX_COMBINED_GEOMETRY_یوشان_COMPONENTS_EXT 0x8A32
#تعریف_کړه GL_MAX_GEOMETRY_ننوت_COMPONENTS_EXT 0x9123
#تعریف_کړه GL_MAX_GEOMETRY_OUTPUT_COMPONENTS_EXT 0x9124
#تعریف_کړه GL_MAX_GEOMETRY_OUTPUT_VERTICES_EXT 0x8DE0
#تعریف_کړه GL_MAX_GEOMETRY_ټول_OUTPUT_COMPONENTS_EXT 0x8DE1
#تعریف_کړه GL_MAX_GEOMETRY_SHADER_INVOCATIONS_EXT 0x8E5A
#تعریف_کړه GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_EXT 0x8C29
#تعریف_کړه GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS_EXT 0x92CF
#تعریف_کړه GL_MAX_GEOMETRY_ATOMIC_COUNTERS_EXT 0x92D5
#تعریف_کړه GL_MAX_GEOMETRY_IMAGE_UNIFORMS_EXT 0x90CD
#تعریف_کړه GL_MAX_GEOMETRY_SHADER_STORAGE_بلاکونه_EXT 0x90D7
#تعریف_کړه GL_لومړی_راس_CONVENTION_EXT    0x8E4D
#تعریف_کړه GL_وروستی_راس_CONVENTION_EXT     0x8E4E
#تعریف_کړه GL_UNDEFINED_راس_EXT           0x8260
#تعریف_کړه GL_PRIMITIVES_GENERATED_EXT       0x8C87
#تعریف_کړه GL_FRAMEBUFFER_DEFAULT_LAYERS_EXT 0x9312
#تعریف_کړه GL_MAX_FRAMEBUFFER_LAYERS_EXT     0x9317
#تعریف_کړه GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_EXT 0x8DA8
#تعریف_کړه GL_FRAMEBUFFER_ATTACHMENT_LAYERED_EXT 0x8DA7
#تعریف_کړه GL_REFERENCED_BY_GEOMETRY_SHADER_EXT 0x9309
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREEXTPROC) (GLenum موخه, GLenum attachment, GLuint texture, GLint level);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferTextureEXT (GLenum موخه, GLenum attachment, GLuint texture, GLint level);
#د_که_پای
#د_که_پای /* GL_EXT_geometry_shader */

#که_نه_تعریف_شوی GL_EXT_gpu_shader5
#تعریف_کړه GL_EXT_gpu_shader5 1
#د_که_پای /* GL_EXT_gpu_shader5 */

#که_نه_تعریف_شوی GL_EXT_instanced_arrays
#تعریف_کړه GL_EXT_instanced_arrays 1
#تعریف_کړه GL_راس_ATTRIB_ARRAY_وېشونکی_EXT 0x88FE
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBDIVISOREXTPROC) (GLuint شاخص, GLuint وېشونکی);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib_وېشونکی_EXT (GLuint شاخص, GLuint وېشونکی);
#د_که_پای
#د_که_پای /* GL_EXT_instanced_arrays */

#که_نه_تعریف_شوی GL_EXT_map_بفر_range
#تعریف_کړه GL_EXT_map_بفر_range 1
#تعریف_کړه GL_MAP_READ_بټ_EXT               0x0001
#تعریف_کړه GL_MAP_WRITE_بټ_EXT              0x0002
#تعریف_کړه GL_MAP_INVALIDATE_RANGE_بټ_EXT   0x0004
#تعریف_کړه GL_MAP_INVALIDATE_بفر_بټ_EXT  0x0008
#تعریف_کړه GL_MAP_FLUSH_EXPLICIT_بټ_EXT     0x0010
#تعریف_کړه GL_MAP_UNSYNCHRONIZED_بټ_EXT     0x0020
تعريفنوع فراغ *(GL_APIENTRYP PFNGLMAPBUFFERRANGEEXTPROC) (GLenum موخه, GLintptr دننه_واټن_2, GLsizeiptr اوږدتیا, GLbitfield access);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEEXTPROC) (GLenum موخه, GLintptr دننه_واټن_2, GLsizeiptr اوږدتیا);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ *GL_APIENTRY gl_Map_بفر_Range_EXT (GLenum موخه, GLintptr دننه_واټن_2, GLsizeiptr اوږدتیا, GLbitfield access);
GL_APICALL فراغ GL_APIENTRY gl_Flush_Mapped_بفر_Range_EXT (GLenum موخه, GLintptr دننه_واټن_2, GLsizeiptr اوږدتیا);
#د_که_پای
#د_که_پای /* GL_EXT_map_buffer_range */

#که_نه_تعریف_شوی GL_EXT_حافظه_object
#تعریف_کړه GL_EXT_حافظه_object 1
#تعریف_کړه GL_TEXTURE_TILING_EXT             0x9580
#تعریف_کړه GL_DEDICATED_حافظه_OBJECT_EXT    0x9581
#تعریف_کړه GL_PROTECTED_حافظه_OBJECT_EXT    0x959B
#تعریف_کړه GL_عدد_TILING_TYPES_EXT           0x9582
#تعریف_کړه GL_TILING_TYPES_EXT               0x9583
#تعریف_کړه GL_OPTIMAL_TILING_EXT             0x9584
#تعریف_کړه GL_خطي_TILING_EXT              0x9585
#تعریف_کړه GL_عدد_DEVICE_UUIDS_EXT           0x9596
#تعریف_کړه GL_DEVICE_UUID_EXT                0x9597
#تعریف_کړه GL_DRIVER_UUID_EXT                0x9598
#تعریف_کړه GL_UUID_اندازه_EXT                  16
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETUNSIGNEDBYTEVEXTPROC) (GLenum pname, GLubyte *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETUNSIGNEDBYTEI_VEXTPROC) (GLenum موخه, GLuint شاخص, GLubyte *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEMEMORYOBJECTSEXTPROC) (GLsizei n, ثابت GLuint *حافظه_Objects);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISMEMORYOBJECTEXTPROC) (GLuint حافظه_Object);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCREATEMEMORYOBJECTSEXTPROC) (GLsizei n, GLuint *حافظه_Objects);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMEMORYOBJECTPARAMETERIVEXTPROC) (GLuint حافظه_Object, GLenum pname, ثابت GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETMEMORYOBJECTPARAMETERIVEXTPROC) (GLuint حافظه_Object, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGEMEM2DEXTPROC) (GLenum موخه, GLsizei پوړونه, GLenum دننی_Format, GLsizei پلنوالی, GLsizei لوړوالی, GLuint حافظه, GLuint64 دننه_واټن_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGEMEM2DMULTISAMPLEEXTPROC) (GLenum موخه, GLsizei samples, GLenum دننی_Format, GLsizei پلنوالی, GLsizei لوړوالی, GLboolean fixedSampleLocations, GLuint حافظه, GLuint64 دننه_واټن_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGEMEM3DEXTPROC) (GLenum موخه, GLsizei پوړونه, GLenum دننی_Format, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLuint حافظه, GLuint64 دننه_واټن_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGEMEM3DMULTISAMPLEEXTPROC) (GLenum موخه, GLsizei samples, GLenum دننی_Format, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLboolean fixedSampleLocations, GLuint حافظه, GLuint64 دننه_واټن_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBUFFERSTORAGEMEMEXTPROC) (GLenum موخه, GLsizeiptr اندازه, GLuint حافظه, GLuint64 دننه_واټن_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGEMEM2DEXTPROC) (GLuint texture, GLsizei پوړونه, GLenum دننی_Format, GLsizei پلنوالی, GLsizei لوړوالی, GLuint حافظه, GLuint64 دننه_واټن_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGEMEM2DMULTISAMPLEEXTPROC) (GLuint texture, GLsizei samples, GLenum دننی_Format, GLsizei پلنوالی, GLsizei لوړوالی, GLboolean fixedSampleLocations, GLuint حافظه, GLuint64 دننه_واټن_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGEMEM3DEXTPROC) (GLuint texture, GLsizei پوړونه, GLenum دننی_Format, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLuint حافظه, GLuint64 دننه_واټن_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGEMEM3DMULTISAMPLEEXTPROC) (GLuint texture, GLsizei samples, GLenum دننی_Format, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLboolean fixedSampleLocations, GLuint حافظه, GLuint64 دننه_واټن_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLNAMEDBUFFERSTORAGEMEMEXTPROC) (GLuint بفر_2, GLsizeiptr اندازه, GLuint حافظه, GLuint64 دننه_واټن_2);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glGetUnsignedBytevEXT (GLenum pname, GLubyte *معلومات);
GL_APICALL فراغ GL_APIENTRY glGetUnsignedBytei_vEXT (GLenum موخه, GLuint شاخص, GLubyte *معلومات);
GL_APICALL فراغ GL_APIENTRY gl_Delete_حافظه_Objects_EXT (GLsizei n, ثابت GLuint *حافظه_Objects);
GL_APICALL GLboolean GL_APIENTRY gl_Is_حافظه_Object_EXT (GLuint حافظه_Object);
GL_APICALL فراغ GL_APIENTRY gl_Create_حافظه_Objects_EXT (GLsizei n, GLuint *حافظه_Objects);
GL_APICALL فراغ GL_APIENTRY gl_حافظه_Object_Parameteriv_EXT (GLuint حافظه_Object, GLenum pname, ثابت GLint *params);
GL_APICALL فراغ GL_APIENTRY gl_Get_حافظه_Object_Parameteriv_EXT (GLuint حافظه_Object, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glTexStorageMem2DEXT (GLenum موخه, GLsizei پوړونه, GLenum دننی_Format, GLsizei پلنوالی, GLsizei لوړوالی, GLuint حافظه, GLuint64 دننه_واټن_2);
GL_APICALL فراغ GL_APIENTRY glTexStorageMem2DMultisampleEXT (GLenum موخه, GLsizei samples, GLenum دننی_Format, GLsizei پلنوالی, GLsizei لوړوالی, GLboolean fixedSampleLocations, GLuint حافظه, GLuint64 دننه_واټن_2);
GL_APICALL فراغ GL_APIENTRY glTexStorageMem3DEXT (GLenum موخه, GLsizei پوړونه, GLenum دننی_Format, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLuint حافظه, GLuint64 دننه_واټن_2);
GL_APICALL فراغ GL_APIENTRY glTexStorageMem3DMultisampleEXT (GLenum موخه, GLsizei samples, GLenum دننی_Format, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLboolean fixedSampleLocations, GLuint حافظه, GLuint64 دننه_واټن_2);
GL_APICALL فراغ GL_APIENTRY gl_بفر_Storage_Mem_EXT (GLenum موخه, GLsizeiptr اندازه, GLuint حافظه, GLuint64 دننه_واټن_2);
GL_APICALL فراغ GL_APIENTRY glTextureStorageMem2DEXT (GLuint texture, GLsizei پوړونه, GLenum دننی_Format, GLsizei پلنوالی, GLsizei لوړوالی, GLuint حافظه, GLuint64 دننه_واټن_2);
GL_APICALL فراغ GL_APIENTRY glTextureStorageMem2DMultisampleEXT (GLuint texture, GLsizei samples, GLenum دننی_Format, GLsizei پلنوالی, GLsizei لوړوالی, GLboolean fixedSampleLocations, GLuint حافظه, GLuint64 دننه_واټن_2);
GL_APICALL فراغ GL_APIENTRY glTextureStorageMem3DEXT (GLuint texture, GLsizei پوړونه, GLenum دننی_Format, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLuint حافظه, GLuint64 دننه_واټن_2);
GL_APICALL فراغ GL_APIENTRY glTextureStorageMem3DMultisampleEXT (GLuint texture, GLsizei samples, GLenum دننی_Format, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLboolean fixedSampleLocations, GLuint حافظه, GLuint64 دننه_واټن_2);
GL_APICALL فراغ GL_APIENTRY gl_Named_بفر_Storage_Mem_EXT (GLuint بفر_2, GLsizeiptr اندازه, GLuint حافظه, GLuint64 دننه_واټن_2);
#د_که_پای
#د_که_پای /* GL_EXT_memory_object */

#که_نه_تعریف_شوی GL_EXT_حافظه_object_fd
#تعریف_کړه GL_EXT_حافظه_object_fd 1
#تعریف_کړه GL_HANDLE_TYPE_OPAQUE_FD_EXT      0x9586
تعريفنوع فراغ (GL_APIENTRYP PFNGLIMPORTMEMORYFDEXTPROC) (GLuint حافظه, GLuint64 اندازه, GLenum handleType, GLint fd);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Import_حافظه_Fd_EXT (GLuint حافظه, GLuint64 اندازه, GLenum handleType, GLint fd);
#د_که_پای
#د_که_پای /* GL_EXT_memory_object_fd */

#که_نه_تعریف_شوی GL_EXT_حافظه_object_win32
#تعریف_کړه GL_EXT_حافظه_object_win32 1
#تعریف_کړه GL_HANDLE_TYPE_OPAQUE_WIN32_EXT   0x9587
#تعریف_کړه GL_HANDLE_TYPE_OPAQUE_WIN32_KMT_EXT 0x9588
#تعریف_کړه GL_DEVICE_LUID_EXT                0x9599
#تعریف_کړه GL_DEVICE_غوټه_ماسک_EXT           0x959A
#تعریف_کړه GL_LUID_اندازه_EXT                  8
#تعریف_کړه GL_HANDLE_TYPE_D3D12_TILEPOOL_EXT 0x9589
#تعریف_کړه GL_HANDLE_TYPE_D3D12_RESOURCE_EXT 0x958A
#تعریف_کړه GL_HANDLE_TYPE_D3D11_IMAGE_EXT    0x958B
#تعریف_کړه GL_HANDLE_TYPE_D3D11_IMAGE_KMT_EXT 0x958C
تعريفنوع فراغ (GL_APIENTRYP PFNGLIMPORTMEMORYWIN32HANDLEEXTPROC) (GLuint حافظه, GLuint64 اندازه, GLenum handleType, فراغ *handle);
تعريفنوع فراغ (GL_APIENTRYP PFNGLIMPORTMEMORYWIN32NAMEEXTPROC) (GLuint حافظه, GLuint64 اندازه, GLenum handleType, ثابت فراغ *name);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Import_حافظه_Win32_Handle_EXT (GLuint حافظه, GLuint64 اندازه, GLenum handleType, فراغ *handle);
GL_APICALL فراغ GL_APIENTRY gl_Import_حافظه_Win32_Name_EXT (GLuint حافظه, GLuint64 اندازه, GLenum handleType, ثابت فراغ *name);
#د_که_پای
#د_که_پای /* GL_EXT_memory_object_win32 */

#که_نه_تعریف_شوی GL_EXT_mesh_shader
#تعریف_کړه GL_EXT_mesh_shader 1
#تعریف_کړه GL_MESH_SHADER_EXT                0x9559
#تعریف_کړه GL_TASK_SHADER_EXT                0x955A
#تعریف_کړه GL_MAX_MESH_یوشان_بلاکونه_EXT    0x8E60
#تعریف_کړه GL_MAX_MESH_TEXTURE_IMAGE_UNITS_EXT 0x8E61
#تعریف_کړه GL_MAX_MESH_IMAGE_UNIFORMS_EXT    0x8E62
#تعریف_کړه GL_MAX_MESH_یوشان_COMPONENTS_EXT 0x8E63
#تعریف_کړه GL_MAX_MESH_ATOMIC_COUNTER_BUFFERS_EXT 0x8E64
#تعریف_کړه GL_MAX_MESH_ATOMIC_COUNTERS_EXT   0x8E65
#تعریف_کړه GL_MAX_MESH_SHADER_STORAGE_بلاکونه_EXT 0x8E66
#تعریف_کړه GL_MAX_COMBINED_MESH_یوشان_COMPONENTS_EXT 0x8E67
#تعریف_کړه GL_MAX_TASK_یوشان_بلاکونه_EXT    0x8E68
#تعریف_کړه GL_MAX_TASK_TEXTURE_IMAGE_UNITS_EXT 0x8E69
#تعریف_کړه GL_MAX_TASK_IMAGE_UNIFORMS_EXT    0x8E6A
#تعریف_کړه GL_MAX_TASK_یوشان_COMPONENTS_EXT 0x8E6B
#تعریف_کړه GL_MAX_TASK_ATOMIC_COUNTER_BUFFERS_EXT 0x8E6C
#تعریف_کړه GL_MAX_TASK_ATOMIC_COUNTERS_EXT   0x8E6D
#تعریف_کړه GL_MAX_TASK_SHADER_STORAGE_بلاکونه_EXT 0x8E6E
#تعریف_کړه GL_MAX_COMBINED_TASK_یوشان_COMPONENTS_EXT 0x8E6F
#تعریف_کړه GL_MAX_TASK_WORK_ډله_ټول_شمېر_EXT 0x9740
#تعریف_کړه GL_MAX_MESH_WORK_ډله_ټول_شمېر_EXT 0x9741
#تعریف_کړه GL_MAX_MESH_WORK_ډله_INVOCATIONS_EXT 0x9757
#تعریف_کړه GL_MAX_TASK_WORK_ډله_INVOCATIONS_EXT 0x9759
#تعریف_کړه GL_MAX_TASK_PAYLOAD_اندازه_EXT      0x9742
#تعریف_کړه GL_MAX_TASK_SHARED_حافظه_اندازه_EXT 0x9743
#تعریف_کړه GL_MAX_MESH_SHARED_حافظه_اندازه_EXT 0x9744
#تعریف_کړه GL_MAX_TASK_PAYLOAD_AND_SHARED_حافظه_اندازه_EXT 0x9745
#تعریف_کړه GL_MAX_MESH_PAYLOAD_AND_SHARED_حافظه_اندازه_EXT 0x9746
#تعریف_کړه GL_MAX_MESH_OUTPUT_حافظه_اندازه_EXT 0x9747
#تعریف_کړه GL_MAX_MESH_PAYLOAD_AND_OUTPUT_حافظه_اندازه_EXT 0x9748
#تعریف_کړه GL_MAX_MESH_OUTPUT_VERTICES_EXT   0x9538
#تعریف_کړه GL_MAX_MESH_OUTPUT_PRIMITIVES_EXT 0x9756
#تعریف_کړه GL_MAX_MESH_OUTPUT_COMPONENTS_EXT 0x9749
#تعریف_کړه GL_MAX_MESH_OUTPUT_LAYERS_EXT     0x974A
#تعریف_کړه GL_MAX_MESH_MULTIVIEW_VIEW_شمېر_EXT 0x9557
#تعریف_کړه GL_MESH_OUTPUT_فی_راس_GRANULARITY_EXT 0x92DF
#تعریف_کړه GL_MESH_OUTPUT_فی_PRIMITIVE_GRANULARITY_EXT 0x9543
#تعریف_کړه GL_MAX_PREFERRED_TASK_WORK_ډله_INVOCATIONS_EXT 0x974B
#تعریف_کړه GL_MAX_PREFERRED_MESH_WORK_ډله_INVOCATIONS_EXT 0x974C
#تعریف_کړه GL_MESH_PREFERS_LOCAL_INVOCATION_راس_OUTPUT_EXT 0x974D
#تعریف_کړه GL_MESH_PREFERS_LOCAL_INVOCATION_PRIMITIVE_OUTPUT_EXT 0x974E
#تعریف_کړه GL_MESH_PREFERS_COMPACT_راس_OUTPUT_EXT 0x974F
#تعریف_کړه GL_MESH_PREFERS_COMPACT_PRIMITIVE_OUTPUT_EXT 0x9750
#تعریف_کړه GL_MAX_TASK_WORK_ډله_شمېر_EXT  0x9751
#تعریف_کړه GL_MAX_MESH_WORK_ډله_شمېر_EXT  0x9752
#تعریف_کړه GL_MAX_MESH_WORK_ډله_اندازه_EXT   0x9758
#تعریف_کړه GL_MAX_TASK_WORK_ډله_اندازه_EXT   0x975A
#تعریف_کړه GL_MESH_WORK_ډله_اندازه_EXT       0x953E
#تعریف_کړه GL_TASK_WORK_ډله_اندازه_EXT       0x953F
#تعریف_کړه GL_MESH_VERTICES_بهر_EXT          0x9579
#تعریف_کړه GL_MESH_PRIMITIVES_بهر_EXT        0x957A
#تعریف_کړه GL_MESH_OUTPUT_TYPE_EXT           0x957B
#تعریف_کړه GL_یوشان_بلاک_REFERENCED_BY_MESH_SHADER_EXT 0x959C
#تعریف_کړه GL_یوشان_بلاک_REFERENCED_BY_TASK_SHADER_EXT 0x959D
#تعریف_کړه GL_REFERENCED_BY_MESH_SHADER_EXT  0x95A0
#تعریف_کړه GL_REFERENCED_BY_TASK_SHADER_EXT  0x95A1
#تعریف_کړه GL_TASK_SHADER_INVOCATIONS_EXT    0x9753
#تعریف_کړه GL_MESH_SHADER_INVOCATIONS_EXT    0x9754
#تعریف_کړه GL_MESH_PRIMITIVES_GENERATED_EXT  0x9755
#تعریف_کړه GL_MESH_SHADER_بټ_EXT            0x00000040
#تعریف_کړه GL_TASK_SHADER_بټ_EXT            0x00000080
#تعریف_کړه GL_MESH_SUBROUTINE_EXT            0x957C
#تعریف_کړه GL_TASK_SUBROUTINE_EXT            0x957D
#تعریف_کړه GL_MESH_SUBROUTINE_یوشان_EXT    0x957E
#تعریف_کړه GL_TASK_SUBROUTINE_یوشان_EXT    0x957F
#تعریف_کړه GL_ATOMIC_COUNTER_بفر_REFERENCED_BY_MESH_SHADER_EXT 0x959E
#تعریف_کړه GL_ATOMIC_COUNTER_بفر_REFERENCED_BY_TASK_SHADER_EXT 0x959F
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWMESHTASKSEXTPROC) (GLuint عدد_groups_x, GLuint عدد_groups_y, GLuint عدد_groups_z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWMESHTASKSINDIRECTEXTPROC) (GLintptr غیرمستقیم);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWMESHTASKSINDIRECTEXTPROC) (GLintptr غیرمستقیم, GLsizei drawcount, GLsizei stride);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTEXTPROC) (GLintptr غیرمستقیم, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawMeshTasksEXT (GLuint عدد_groups_x, GLuint عدد_groups_y, GLuint عدد_groups_z);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Mesh_Tasks_غیرمستقیم_EXT (GLintptr غیرمستقیم);
GL_APICALL فراغ GL_APIENTRY gl_Multi_Draw_Mesh_Tasks_غیرمستقیم_EXT (GLintptr غیرمستقیم, GLsizei drawcount, GLsizei stride);
GL_APICALL فراغ GL_APIENTRY gl_Multi_Draw_Mesh_Tasks_غیرمستقیم_شمېر_EXT (GLintptr غیرمستقیم, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
#د_که_پای
#د_که_پای /* GL_EXT_mesh_shader */

#که_نه_تعریف_شوی GL_EXT_multi_draw_arrays
#تعریف_کړه GL_EXT_multi_draw_arrays 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWARRAYSEXTPROC) (GLenum ډېرپېښ, ثابت GLint *لومړی, ثابت GLsizei *شمېر, GLsizei primcount);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSEXTPROC) (GLenum ډېرپېښ, ثابت GLsizei *شمېر, GLenum type, ثابت فراغ *ثابت*indices, GLsizei primcount);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glMultiDrawArraysEXT (GLenum ډېرپېښ, ثابت GLint *لومړی, ثابت GLsizei *شمېر, GLsizei primcount);
GL_APICALL فراغ GL_APIENTRY glMultiDrawElementsEXT (GLenum ډېرپېښ, ثابت GLsizei *شمېر, GLenum type, ثابت فراغ *ثابت*indices, GLsizei primcount);
#د_که_پای
#د_که_پای /* GL_EXT_multi_draw_arrays */

#که_نه_تعریف_شوی GL_EXT_multi_draw_غیرمستقیم
#تعریف_کړه GL_EXT_multi_draw_غیرمستقیم 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWARRAYSINDIRECTEXTPROC) (GLenum ډېرپېښ, ثابت فراغ *غیرمستقیم, GLsizei drawcount, GLsizei stride);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSINDIRECTEXTPROC) (GLenum ډېرپېښ, GLenum type, ثابت فراغ *غیرمستقیم, GLsizei drawcount, GLsizei stride);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Multi_Draw_Arrays_غیرمستقیم_EXT (GLenum ډېرپېښ, ثابت فراغ *غیرمستقیم, GLsizei drawcount, GLsizei stride);
GL_APICALL فراغ GL_APIENTRY gl_Multi_Draw_Elements_غیرمستقیم_EXT (GLenum ډېرپېښ, GLenum type, ثابت فراغ *غیرمستقیم, GLsizei drawcount, GLsizei stride);
#د_که_پای
#د_که_پای /* GL_EXT_multi_draw_indirect */

#که_نه_تعریف_شوی GL_EXT_multisampled_compatibility
#تعریف_کړه GL_EXT_multisampled_compatibility 1
#تعریف_کړه GL_MULTISAMPLE_EXT                0x809D
#تعریف_کړه GL_SAMPLE_ALPHA_منزل_ONE_EXT        0x809F
#د_که_پای /* GL_EXT_multisampled_compatibility */

#که_نه_تعریف_شوی GL_EXT_multisampled_render_منزل_texture
#تعریف_کړه GL_EXT_multisampled_render_منزل_texture 1
#تعریف_کړه GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SAMPLES_EXT 0x8D6C
#تعریف_کړه GL_RENDERBUFFER_SAMPLES_EXT       0x8CAB
#تعریف_کړه GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT 0x8D56
#تعریف_کړه GL_MAX_SAMPLES_EXT                0x8D57
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) (GLenum موخه, GLsizei samples, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEEXTPROC) (GLenum موخه, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glRenderbufferStorageMultisampleEXT (GLenum موخه, GLsizei samples, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
GL_APICALL فراغ GL_APIENTRY glFramebufferTexture2DMultisampleEXT (GLenum موخه, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#د_که_پای
#د_که_پای /* GL_EXT_multisampled_render_to_texture */

#که_نه_تعریف_شوی GL_EXT_multisampled_render_منزل_texture2
#تعریف_کړه GL_EXT_multisampled_render_منزل_texture2 1
#د_که_پای /* GL_EXT_multisampled_render_to_texture2 */

#که_نه_تعریف_شوی GL_EXT_multiview_draw_buffers
#تعریف_کړه GL_EXT_multiview_draw_buffers 1
#تعریف_کړه GL_COLOR_ATTACHMENT_EXT           0x90F0
#تعریف_کړه GL_MULTIVIEW_EXT                  0x90F1
#تعریف_کړه GL_DRAW_بفر_EXT                0x0C01
#تعریف_کړه GL_READ_بفر_EXT                0x0C02
#تعریف_کړه GL_MAX_MULTIVIEW_BUFFERS_EXT      0x90F2
تعريفنوع فراغ (GL_APIENTRYP PFNGLREADBUFFERINDEXEDEXTPROC) (GLenum src, GLint شاخص);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWBUFFERSINDEXEDEXTPROC) (GLint n, ثابت GLenum *location, ثابت GLint *indices);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTEGERI_VEXTPROC) (GLenum موخه, GLuint شاخص, GLint *معلومات);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Read_بفر_شاخصي_EXT (GLenum src, GLint شاخص);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Buffers_شاخصي_EXT (GLint n, ثابت GLenum *location, ثابت GLint *indices);
GL_APICALL فراغ GL_APIENTRY glGetIntegeri_vEXT (GLenum موخه, GLuint شاخص, GLint *معلومات);
#د_که_پای
#د_که_پای /* GL_EXT_multiview_draw_buffers */

#که_نه_تعریف_شوی GL_EXT_multiview_tessellation_geometry_shader
#تعریف_کړه GL_EXT_multiview_tessellation_geometry_shader 1
#د_که_پای /* GL_EXT_multiview_tessellation_geometry_shader */

#که_نه_تعریف_شوی GL_EXT_multiview_texture_multisample
#تعریف_کړه GL_EXT_multiview_texture_multisample 1
#د_که_پای /* GL_EXT_multiview_texture_multisample */

#که_نه_تعریف_شوی GL_EXT_multiview_timer_query
#تعریف_کړه GL_EXT_multiview_timer_query 1
#د_که_پای /* GL_EXT_multiview_timer_query */

#که_نه_تعریف_شوی GL_EXT_occlusion_query_boolean
#تعریف_کړه GL_EXT_occlusion_query_boolean 1
#تعریف_کړه GL_ANY_SAMPLES_PASSED_EXT         0x8C2F
#تعریف_کړه GL_ANY_SAMPLES_PASSED_CONSERVATIVE_EXT 0x8D6A
#د_که_پای /* GL_EXT_occlusion_query_boolean */

#که_نه_تعریف_شوی GL_EXT_polygon_دننه_واټن_clamp
#تعریف_کړه GL_EXT_polygon_دننه_واټن_clamp 1
#تعریف_کړه GL_POLYGON_دننه_واټن_CLAMP_EXT       0x8E1B
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOLYGONOFFSETCLAMPEXTPROC) (GLfloat ضریب, GLfloat units, GLfloat clamp);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Polygon_دننه_واټن_Clamp_EXT (GLfloat ضریب, GLfloat units, GLfloat clamp);
#د_که_پای
#د_که_پای /* GL_EXT_polygon_offset_clamp */

#که_نه_تعریف_شوی GL_EXT_post_ژوروالی_coverage
#تعریف_کړه GL_EXT_post_ژوروالی_coverage 1
#د_که_پای /* GL_EXT_post_depth_coverage */

#که_نه_تعریف_شوی GL_EXT_primitive_bounding_box
#تعریف_کړه GL_EXT_primitive_bounding_box 1
#تعریف_کړه GL_PRIMITIVE_BOUNDING_BOX_EXT     0x92BE
تعريفنوع فراغ (GL_APIENTRYP PFNGLPRIMITIVEBOUNDINGBOXEXTPROC) (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glPrimitiveBoundingBoxEXT (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
#د_که_پای
#د_که_پای /* GL_EXT_primitive_bounding_box */

#که_نه_تعریف_شوی GL_EXT_protected_textures
#تعریف_کړه GL_EXT_protected_textures 1
#تعریف_کړه GL_CONTEXT_FLAG_PROTECTED_CONTENT_بټ_EXT 0x00000010
#تعریف_کړه GL_TEXTURE_PROTECTED_EXT          0x8BFA
#د_که_پای /* GL_EXT_protected_textures */

#که_نه_تعریف_شوی GL_EXT_pvrtc_sRGB
#تعریف_کړه GL_EXT_pvrtc_sRGB 1
#تعریف_کړه GL_COMPRESSED_SRGB_PVRTC_2BPPV1_EXT 0x8A54
#تعریف_کړه GL_COMPRESSED_SRGB_PVRTC_4BPPV1_EXT 0x8A55
#تعریف_کړه GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV1_EXT 0x8A56
#تعریف_کړه GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV1_EXT 0x8A57
#تعریف_کړه GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV2_IMG 0x93F0
#تعریف_کړه GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV2_IMG 0x93F1
#د_که_پای /* GL_EXT_pvrtc_sRGB */

#که_نه_تعریف_شوی GL_EXT_raster_multisample
#تعریف_کړه GL_EXT_raster_multisample 1
#تعریف_کړه GL_RASTER_MULTISAMPLE_EXT         0x9327
#تعریف_کړه GL_RASTER_SAMPLES_EXT             0x9328
#تعریف_کړه GL_MAX_RASTER_SAMPLES_EXT         0x9329
#تعریف_کړه GL_RASTER_FIXED_SAMPLE_LOCATIONS_EXT 0x932A
#تعریف_کړه GL_MULTISAMPLE_RASTERIZATION_ALLOWED_EXT 0x932B
#تعریف_کړه GL_EFFECTIVE_RASTER_SAMPLES_EXT   0x932C
تعريفنوع فراغ (GL_APIENTRYP PFNGLRASTERSAMPLESEXTPROC) (GLuint samples, GLboolean fixedsamplelocations);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glRasterSamplesEXT (GLuint samples, GLboolean fixedsamplelocations);
#د_که_پای
#د_که_پای /* GL_EXT_raster_multisample */

#که_نه_تعریف_شوی GL_EXT_read_format_bgra
#تعریف_کړه GL_EXT_read_format_bgra 1
#تعریف_کړه GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT 0x8365
#تعریف_کړه GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT 0x8366
#د_که_پای /* GL_EXT_read_format_bgra */

#که_نه_تعریف_شوی GL_EXT_render_snorm
#تعریف_کړه GL_EXT_render_snorm 1
#تعریف_کړه GL_R8_SNORM                       0x8F94
#تعریف_کړه GL_RG8_SNORM                      0x8F95
#تعریف_کړه GL_RGBA8_SNORM                    0x8F97
#تعریف_کړه GL_R16_SNORM_EXT                  0x8F98
#تعریف_کړه GL_RG16_SNORM_EXT                 0x8F99
#تعریف_کړه GL_RGBA16_SNORM_EXT               0x8F9B
#د_که_پای /* GL_EXT_render_snorm */

#که_نه_تعریف_شوی GL_EXT_robustness
#تعریف_کړه GL_EXT_robustness 1
#تعریف_کړه GL_GUILTY_CONTEXT_RESET_EXT       0x8253
#تعریف_کړه GL_INNOCENT_CONTEXT_RESET_EXT     0x8254
#تعریف_کړه GL_UNKNOWN_CONTEXT_RESET_EXT      0x8255
#تعریف_کړه GL_CONTEXT_ROBUST_ACCESS_EXT      0x90F3
#تعریف_کړه GL_RESET_NOTIFICATION_STRATEGY_EXT 0x8256
#تعریف_کړه GL_LOSE_CONTEXT_ON_RESET_EXT      0x8252
#تعریف_کړه GL_NO_RESET_NOTIFICATION_EXT      0x8261
تعريفنوع GLenum (GL_APIENTRYP PFNGLGETGRAPHICSRESETSTATUSEXTPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLREADNPIXELSEXTPROC) (GLint x, GLint y, GLsizei پلنوالی, GLsizei لوړوالی, GLenum format, GLenum type, GLsizei buf_اندازه, فراغ *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNUNIFORMFVEXTPROC) (GLuint پروګرام, GLint location, GLsizei buf_اندازه, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNUNIFORMIVEXTPROC) (GLuint پروګرام, GLint location, GLsizei buf_اندازه, GLint *params);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL GLenum GL_APIENTRY gl_Get_Graphics_Reset_حالت_EXT (فراغ);
GL_APICALL فراغ GL_APIENTRY glReadnPixelsEXT (GLint x, GLint y, GLsizei پلنوالی, GLsizei لوړوالی, GLenum format, GLenum type, GLsizei buf_اندازه, فراغ *معلومات);
GL_APICALL فراغ GL_APIENTRY glGetnUniformfvEXT (GLuint پروګرام, GLint location, GLsizei buf_اندازه, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY glGetnUniformivEXT (GLuint پروګرام, GLint location, GLsizei buf_اندازه, GLint *params);
#د_که_پای
#د_که_پای /* GL_EXT_robustness */

#که_نه_تعریف_شوی GL_EXT_sRGB
#تعریف_کړه GL_EXT_sRGB 1
#تعریف_کړه GL_SRGB_EXT                       0x8C40
#تعریف_کړه GL_SRGB_ALPHA_EXT                 0x8C42
#تعریف_کړه GL_SRGB8_ALPHA8_EXT               0x8C43
#تعریف_کړه GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING_EXT 0x8210
#د_که_پای /* GL_EXT_sRGB */

#که_نه_تعریف_شوی GL_EXT_sRGB_write_control
#تعریف_کړه GL_EXT_sRGB_write_control 1
#تعریف_کړه GL_FRAMEBUFFER_SRGB_EXT           0x8DB9
#د_که_پای /* GL_EXT_sRGB_write_control */

#که_نه_تعریف_شوی GL_EXT_semaphore
#تعریف_کړه GL_EXT_semaphore 1
#تعریف_کړه GL_LAYOUT_GENERAL_EXT             0x958D
#تعریف_کړه GL_LAYOUT_COLOR_ATTACHMENT_EXT    0x958E
#تعریف_کړه GL_LAYOUT_ژوروالی_STENCIL_ATTACHMENT_EXT 0x958F
#تعریف_کړه GL_LAYOUT_ژوروالی_STENCIL_READ_ONLY_EXT 0x9590
#تعریف_کړه GL_LAYOUT_SHADER_READ_ONLY_EXT    0x9591
#تعریف_کړه GL_LAYOUT_TRANSFER_SRC_EXT        0x9592
#تعریف_کړه GL_LAYOUT_TRANSFER_DST_EXT        0x9593
#تعریف_کړه GL_LAYOUT_ژوروالی_READ_ONLY_STENCIL_ATTACHMENT_EXT 0x9530
#تعریف_کړه GL_LAYOUT_ژوروالی_ATTACHMENT_STENCIL_READ_ONLY_EXT 0x9531
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENSEMAPHORESEXTPROC) (GLsizei n, GLuint *semaphores);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETESEMAPHORESEXTPROC) (GLsizei n, ثابت GLuint *semaphores);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISSEMAPHOREEXTPROC) (GLuint semaphore);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSEMAPHOREPARAMETERUI64VEXTPROC) (GLuint semaphore, GLenum pname, ثابت GLuint64 *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSEMAPHOREPARAMETERUI64VEXTPROC) (GLuint semaphore, GLenum pname, GLuint64 *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLWAITSEMAPHOREEXTPROC) (GLuint semaphore, GLuint عدد_بفر_Barriers, ثابت GLuint *buffers, GLuint عدد_Texture_Barriers, ثابت GLuint *textures, ثابت GLenum *srcLayouts);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSIGNALSEMAPHOREEXTPROC) (GLuint semaphore, GLuint عدد_بفر_Barriers, ثابت GLuint *buffers, GLuint عدد_Texture_Barriers, ثابت GLuint *textures, ثابت GLenum *dstLayouts);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glGenSemaphoresEXT (GLsizei n, GLuint *semaphores);
GL_APICALL فراغ GL_APIENTRY glDeleteSemaphoresEXT (GLsizei n, ثابت GLuint *semaphores);
GL_APICALL GLboolean GL_APIENTRY glIsSemaphoreEXT (GLuint semaphore);
GL_APICALL فراغ GL_APIENTRY glSemaphoreParameterui64vEXT (GLuint semaphore, GLenum pname, ثابت GLuint64 *params);
GL_APICALL فراغ GL_APIENTRY glGetSemaphoreParameterui64vEXT (GLuint semaphore, GLenum pname, GLuint64 *params);
GL_APICALL فراغ GL_APIENTRY glWaitSemaphoreEXT (GLuint semaphore, GLuint عدد_بفر_Barriers, ثابت GLuint *buffers, GLuint عدد_Texture_Barriers, ثابت GLuint *textures, ثابت GLenum *srcLayouts);
GL_APICALL فراغ GL_APIENTRY glSignalSemaphoreEXT (GLuint semaphore, GLuint عدد_بفر_Barriers, ثابت GLuint *buffers, GLuint عدد_Texture_Barriers, ثابت GLuint *textures, ثابت GLenum *dstLayouts);
#د_که_پای
#د_که_پای /* GL_EXT_semaphore */

#که_نه_تعریف_شوی GL_EXT_semaphore_fd
#تعریف_کړه GL_EXT_semaphore_fd 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLIMPORTSEMAPHOREFDEXTPROC) (GLuint semaphore, GLenum handleType, GLint fd);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glImportSemaphoreFdEXT (GLuint semaphore, GLenum handleType, GLint fd);
#د_که_پای
#د_که_پای /* GL_EXT_semaphore_fd */

#که_نه_تعریف_شوی GL_EXT_semaphore_win32
#تعریف_کړه GL_EXT_semaphore_win32 1
#تعریف_کړه GL_HANDLE_TYPE_D3D12_FENCE_EXT    0x9594
#تعریف_کړه GL_D3_D12_FENCE_ارزښت_EXT          0x9595
تعريفنوع فراغ (GL_APIENTRYP PFNGLIMPORTSEMAPHOREWIN32HANDLEEXTPROC) (GLuint semaphore, GLenum handleType, فراغ *handle);
تعريفنوع فراغ (GL_APIENTRYP PFNGLIMPORTSEMAPHOREWIN32NAMEEXTPROC) (GLuint semaphore, GLenum handleType, ثابت فراغ *name);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glImportSemaphoreWin32HandleEXT (GLuint semaphore, GLenum handleType, فراغ *handle);
GL_APICALL فراغ GL_APIENTRY glImportSemaphoreWin32NameEXT (GLuint semaphore, GLenum handleType, ثابت فراغ *name);
#د_که_پای
#د_که_پای /* GL_EXT_semaphore_win32 */

#که_نه_تعریف_شوی GL_EXT_separate_ژوروالی_stencil
#تعریف_کړه GL_EXT_separate_ژوروالی_stencil 1
#د_که_پای /* GL_EXT_separate_depth_stencil */

#که_نه_تعریف_شوی GL_EXT_separate_shader_objects
#تعریف_کړه GL_EXT_separate_shader_objects 1
#تعریف_کړه GL_فعال_پروګرام_EXT             0x8259
#تعریف_کړه GL_راس_SHADER_بټ_EXT          0x00000001
#تعریف_کړه GL_FRAGMENT_SHADER_بټ_EXT        0x00000002
#تعریف_کړه GL_ALL_SHADER_بټونه_EXT            0xFFFFFFFF
#تعریف_کړه GL_پروګرام_SEPARABLE_EXT          0x8258
#تعریف_کړه GL_پروګرام_PIPELINE_BINDING_EXT   0x825A
تعريفنوع فراغ (GL_APIENTRYP PFNGLACTIVESHADERPROGRAMEXTPROC) (GLuint pipeline, GLuint پروګرام);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDPROGRAMPIPELINEEXTPROC) (GLuint pipeline);
تعريفنوع GLuint (GL_APIENTRYP PFNGLCREATESHADERPROGRAMVEXTPROC) (GLenum type, GLsizei شمېر, ثابت GLchar *ثابت*مزي_ګانې);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEPROGRAMPIPELINESEXTPROC) (GLsizei n, ثابت GLuint *pipelines);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENPROGRAMPIPELINESEXTPROC) (GLsizei n, GLuint *pipelines);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMPIPELINEINFOLOGEXTPROC) (GLuint pipeline, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLchar *infoLog);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMPIPELINEIVEXTPROC) (GLuint pipeline, GLenum pname, GLint *params);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISPROGRAMPIPELINEEXTPROC) (GLuint pipeline);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMPARAMETERIEXTPROC) (GLuint پروګرام, GLenum pname, GLint ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1FEXTPROC) (GLuint پروګرام, GLint location, GLfloat v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1FVEXTPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1IEXTPROC) (GLuint پروګرام, GLint location, GLint v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1IVEXTPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLint *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2FEXTPROC) (GLuint پروګرام, GLint location, GLfloat v0, GLfloat v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2FVEXTPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2IEXTPROC) (GLuint پروګرام, GLint location, GLint v0, GLint v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2IVEXTPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLint *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3FEXTPROC) (GLuint پروګرام, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3FVEXTPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3IEXTPROC) (GLuint پروګرام, GLint location, GLint v0, GLint v1, GLint v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3IVEXTPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLint *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4FEXTPROC) (GLuint پروګرام, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4FVEXTPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4IEXTPROC) (GLuint پروګرام, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4IVEXTPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLint *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUSEPROGRAMSTAGESEXTPROC) (GLuint pipeline, GLbitfield stages, GLuint پروګرام);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVALIDATEPROGRAMPIPELINEEXTPROC) (GLuint pipeline);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UIEXTPROC) (GLuint پروګرام, GLint location, GLuint v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UIEXTPROC) (GLuint پروګرام, GLint location, GLuint v0, GLuint v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UIEXTPROC) (GLuint پروګرام, GLint location, GLuint v0, GLuint v1, GLuint v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UIEXTPROC) (GLuint پروګرام, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UIVEXTPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLuint *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UIVEXTPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLuint *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UIVEXTPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLuint *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UIVEXTPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLuint *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_فعال_Shader_پروګرام_EXT (GLuint pipeline, GLuint پروګرام);
GL_APICALL فراغ GL_APIENTRY gl_Bind_پروګرام_Pipeline_EXT (GLuint pipeline);
GL_APICALL GLuint GL_APIENTRY glCreateShaderProgramvEXT (GLenum type, GLsizei شمېر, ثابت GLchar *ثابت*مزي_ګانې);
GL_APICALL فراغ GL_APIENTRY gl_Delete_پروګرام_Pipelines_EXT (GLsizei n, ثابت GLuint *pipelines);
GL_APICALL فراغ GL_APIENTRY gl_Gen_پروګرام_Pipelines_EXT (GLsizei n, GLuint *pipelines);
GL_APICALL فراغ GL_APIENTRY gl_Get_پروګرام_Pipeline_Info_Log_EXT (GLuint pipeline, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLchar *infoLog);
GL_APICALL فراغ GL_APIENTRY gl_Get_پروګرام_Pipelineiv_EXT (GLuint pipeline, GLenum pname, GLint *params);
GL_APICALL GLboolean GL_APIENTRY gl_Is_پروګرام_Pipeline_EXT (GLuint pipeline);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Parameteri_EXT (GLuint پروګرام, GLenum pname, GLint ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform1f_EXT (GLuint پروګرام, GLint location, GLfloat v0);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform1fv_EXT (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform1i_EXT (GLuint پروګرام, GLint location, GLint v0);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform1iv_EXT (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLint *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform2f_EXT (GLuint پروګرام, GLint location, GLfloat v0, GLfloat v1);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform2fv_EXT (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform2i_EXT (GLuint پروګرام, GLint location, GLint v0, GLint v1);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform2iv_EXT (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLint *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform3f_EXT (GLuint پروګرام, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform3fv_EXT (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform3i_EXT (GLuint پروګرام, GLint location, GLint v0, GLint v1, GLint v2);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform3iv_EXT (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLint *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform4f_EXT (GLuint پروګرام, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform4fv_EXT (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform4i_EXT (GLuint پروګرام, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform4iv_EXT (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLint *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_یوشان_Matrix2fv_EXT (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_یوشان_Matrix3fv_EXT (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_یوشان_Matrix4fv_EXT (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_Use_پروګرام_Stages_EXT (GLuint pipeline, GLbitfield stages, GLuint پروګرام);
GL_APICALL فراغ GL_APIENTRY gl_Validate_پروګرام_Pipeline_EXT (GLuint pipeline);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform1ui_EXT (GLuint پروګرام, GLint location, GLuint v0);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform2ui_EXT (GLuint پروګرام, GLint location, GLuint v0, GLuint v1);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform3ui_EXT (GLuint پروګرام, GLint location, GLuint v0, GLuint v1, GLuint v2);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform4ui_EXT (GLuint پروګرام, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform1uiv_EXT (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLuint *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform2uiv_EXT (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLuint *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform3uiv_EXT (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLuint *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform4uiv_EXT (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLuint *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_یوشان_Matrix2x3fv_EXT (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_یوشان_Matrix3x2fv_EXT (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_یوشان_Matrix2x4fv_EXT (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_یوشان_Matrix4x2fv_EXT (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_یوشان_Matrix3x4fv_EXT (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_یوشان_Matrix4x3fv_EXT (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
#د_که_پای
#د_که_پای /* GL_EXT_separate_shader_objects */

#که_نه_تعریف_شوی GL_EXT_shader_framebuffer_fetch
#تعریف_کړه GL_EXT_shader_framebuffer_fetch 1
#تعریف_کړه GL_FRAGMENT_SHADER_DISCARDS_SAMPLES_EXT 0x8A52
#د_که_پای /* GL_EXT_shader_framebuffer_fetch */

#که_نه_تعریف_شوی GL_EXT_shader_framebuffer_fetch_non_coherent
#تعریف_کړه GL_EXT_shader_framebuffer_fetch_non_coherent 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERFETCHBARRIEREXTPROC) (فراغ);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferFetchBarrierEXT (فراغ);
#د_که_پای
#د_که_پای /* GL_EXT_shader_framebuffer_fetch_non_coherent */

#که_نه_تعریف_شوی GL_EXT_shader_ډله_vote
#تعریف_کړه GL_EXT_shader_ډله_vote 1
#د_که_پای /* GL_EXT_shader_group_vote */

#که_نه_تعریف_شوی GL_EXT_shader_implicit_conversions
#تعریف_کړه GL_EXT_shader_implicit_conversions 1
#د_که_پای /* GL_EXT_shader_implicit_conversions */

#که_نه_تعریف_شوی GL_EXT_shader_integer_mix
#تعریف_کړه GL_EXT_shader_integer_mix 1
#د_که_پای /* GL_EXT_shader_integer_mix */

#که_نه_تعریف_شوی GL_EXT_shader_io_بلاکونه
#تعریف_کړه GL_EXT_shader_io_بلاکونه 1
#د_که_پای /* GL_EXT_shader_io_blocks */

#که_نه_تعریف_شوی GL_EXT_shader_non_constant_global_initializers
#تعریف_کړه GL_EXT_shader_non_constant_global_initializers 1
#د_که_پای /* GL_EXT_shader_non_constant_global_initializers */

#که_نه_تعریف_شوی GL_EXT_shader_pixel_local_storage
#تعریف_کړه GL_EXT_shader_pixel_local_storage 1
#تعریف_کړه GL_MAX_SHADER_PIXEL_LOCAL_STORAGE_FAST_اندازه_EXT 0x8F63
#تعریف_کړه GL_MAX_SHADER_PIXEL_LOCAL_STORAGE_اندازه_EXT 0x8F67
#تعریف_کړه GL_SHADER_PIXEL_LOCAL_STORAGE_EXT 0x8F64
#د_که_پای /* GL_EXT_shader_pixel_local_storage */

#که_نه_تعریف_شوی GL_EXT_shader_pixel_local_storage2
#تعریف_کړه GL_EXT_shader_pixel_local_storage2 1
#تعریف_کړه GL_MAX_SHADER_COMBINED_LOCAL_STORAGE_FAST_اندازه_EXT 0x9650
#تعریف_کړه GL_MAX_SHADER_COMBINED_LOCAL_STORAGE_اندازه_EXT 0x9651
#تعریف_کړه GL_FRAMEBUFFER_INCOMPLETE_INSUFFICIENT_SHADER_COMBINED_LOCAL_STORAGE_EXT 0x9652
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERPIXELLOCALSTORAGESIZEEXTPROC) (GLuint موخه, GLsizei اندازه);
تعريفنوع GLsizei (GL_APIENTRYP PFNGLGETFRAMEBUFFERPIXELLOCALSTORAGESIZEEXTPROC) (GLuint موخه);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARPIXELLOCALSTORAGEUIEXTPROC) (GLsizei دننه_واټن_2, GLsizei n, ثابت GLuint *ارزښتونه);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Framebuffer_Pixel_Local_Storage_اندازه_EXT (GLuint موخه, GLsizei اندازه);
GL_APICALL GLsizei GL_APIENTRY gl_Get_Framebuffer_Pixel_Local_Storage_اندازه_EXT (GLuint موخه);
GL_APICALL فراغ GL_APIENTRY glClearPixelLocalStorageuiEXT (GLsizei دننه_واټن_2, GLsizei n, ثابت GLuint *ارزښتونه);
#د_که_پای
#د_که_پای /* GL_EXT_shader_pixel_local_storage2 */

#که_نه_تعریف_شوی GL_EXT_shader_samples_identical
#تعریف_کړه GL_EXT_shader_samples_identical 1
#د_که_پای /* GL_EXT_shader_samples_identical */

#که_نه_تعریف_شوی GL_EXT_shader_texture_lod
#تعریف_کړه GL_EXT_shader_texture_lod 1
#د_که_پای /* GL_EXT_shader_texture_lod */

#که_نه_تعریف_شوی GL_EXT_shader_texture_samples
#تعریف_کړه GL_EXT_shader_texture_samples 1
#د_که_پای /* GL_EXT_shader_texture_samples */

#که_نه_تعریف_شوی GL_EXT_shadow_samplers
#تعریف_کړه GL_EXT_shadow_samplers 1
#تعریف_کړه GL_TEXTURE_COMPARE_ډېرپېښ_EXT       0x884C
#تعریف_کړه GL_TEXTURE_COMPARE_FUNC_EXT       0x884D
#تعریف_کړه GL_COMPARE_REF_منزل_TEXTURE_EXT     0x884E
#تعریف_کړه GL_SAMPLER_2D_SHADOW_EXT          0x8B62
#د_که_پای /* GL_EXT_shadow_samplers */

#که_نه_تعریف_شوی GL_EXT_sparse_texture
#تعریف_کړه GL_EXT_sparse_texture 1
#تعریف_کړه GL_TEXTURE_SPARSE_EXT             0x91A6
#تعریف_کړه GL_VIRTUAL_پاڼه_اندازه_شاخص_EXT    0x91A7
#تعریف_کړه GL_عدد_SPARSE_پوړونه_EXT          0x91AA
#تعریف_کړه GL_عدد_VIRTUAL_پاڼه_SIZES_EXT     0x91A8
#تعریف_کړه GL_VIRTUAL_پاڼه_اندازه_X_EXT        0x9195
#تعریف_کړه GL_VIRTUAL_پاڼه_اندازه_Y_EXT        0x9196
#تعریف_کړه GL_VIRTUAL_پاڼه_اندازه_Z_EXT        0x9197
#تعریف_کړه GL_TEXTURE_2D_ARRAY               0x8C1A
#تعریف_کړه GL_TEXTURE_3D                     0x806F
#تعریف_کړه GL_MAX_SPARSE_TEXTURE_اندازه_EXT    0x9198
#تعریف_کړه GL_MAX_SPARSE_3_D_TEXTURE_اندازه_EXT 0x9199
#تعریف_کړه GL_MAX_SPARSE_ARRAY_TEXTURE_LAYERS_EXT 0x919A
#تعریف_کړه GL_SPARSE_TEXTURE_ډک_ARRAY_CUBE_MIPMAPS_EXT 0x91A9
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPAGECOMMITMENTEXTPROC) (GLenum موخه, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLboolean commit);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Tex_پاڼه_Commitment_EXT (GLenum موخه, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLboolean commit);
#د_که_پای
#د_که_پای /* GL_EXT_sparse_texture */

#که_نه_تعریف_شوی GL_EXT_sparse_texture2
#تعریف_کړه GL_EXT_sparse_texture2 1
#د_که_پای /* GL_EXT_sparse_texture2 */

#که_نه_تعریف_شوی GL_EXT_tessellation_ټکی_اندازه
#تعریف_کړه GL_EXT_tessellation_ټکی_اندازه 1
#د_که_پای /* GL_EXT_tessellation_point_size */

#که_نه_تعریف_شوی GL_EXT_tessellation_shader
#تعریف_کړه GL_EXT_tessellation_shader 1
#تعریف_کړه GL_PATCHES_EXT                    0x000E
#تعریف_کړه GL_PATCH_VERTICES_EXT             0x8E72
#تعریف_کړه GL_TESS_CONTROL_OUTPUT_VERTICES_EXT 0x8E75
#تعریف_کړه GL_TESS_GEN_ډېرپېښ_EXT              0x8E76
#تعریف_کړه GL_TESS_GEN_SPACING_EXT           0x8E77
#تعریف_کړه GL_TESS_GEN_راس_ترتیب_EXT      0x8E78
#تعریف_کړه GL_TESS_GEN_ټکی_ډېرپېښ_EXT        0x8E79
#تعریف_کړه GL_ISOLINES_EXT                   0x8E7A
#تعریف_کړه GL_QUADS_EXT                      0x0007
#تعریف_کړه GL_FRACTIONAL_ODD_EXT             0x8E7B
#تعریف_کړه GL_FRACTIONAL_EVEN_EXT            0x8E7C
#تعریف_کړه GL_MAX_PATCH_VERTICES_EXT         0x8E7D
#تعریف_کړه GL_MAX_TESS_GEN_LEVEL_EXT         0x8E7E
#تعریف_کړه GL_MAX_TESS_CONTROL_یوشان_COMPONENTS_EXT 0x8E7F
#تعریف_کړه GL_MAX_TESS_EVALUATION_یوشان_COMPONENTS_EXT 0x8E80
#تعریف_کړه GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS_EXT 0x8E81
#تعریف_کړه GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS_EXT 0x8E82
#تعریف_کړه GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS_EXT 0x8E83
#تعریف_کړه GL_MAX_TESS_PATCH_COMPONENTS_EXT  0x8E84
#تعریف_کړه GL_MAX_TESS_CONTROL_ټول_OUTPUT_COMPONENTS_EXT 0x8E85
#تعریف_کړه GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS_EXT 0x8E86
#تعریف_کړه GL_MAX_TESS_CONTROL_یوشان_بلاکونه_EXT 0x8E89
#تعریف_کړه GL_MAX_TESS_EVALUATION_یوشان_بلاکونه_EXT 0x8E8A
#تعریف_کړه GL_MAX_TESS_CONTROL_ننوت_COMPONENTS_EXT 0x886C
#تعریف_کړه GL_MAX_TESS_EVALUATION_ننوت_COMPONENTS_EXT 0x886D
#تعریف_کړه GL_MAX_COMBINED_TESS_CONTROL_یوشان_COMPONENTS_EXT 0x8E1E
#تعریف_کړه GL_MAX_COMBINED_TESS_EVALUATION_یوشان_COMPONENTS_EXT 0x8E1F
#تعریف_کړه GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS_EXT 0x92CD
#تعریف_کړه GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS_EXT 0x92CE
#تعریف_کړه GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS_EXT 0x92D3
#تعریف_کړه GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS_EXT 0x92D4
#تعریف_کړه GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS_EXT 0x90CB
#تعریف_کړه GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS_EXT 0x90CC
#تعریف_کړه GL_MAX_TESS_CONTROL_SHADER_STORAGE_بلاکونه_EXT 0x90D8
#تعریف_کړه GL_MAX_TESS_EVALUATION_SHADER_STORAGE_بلاکونه_EXT 0x90D9
#تعریف_کړه GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED 0x8221
#تعریف_کړه GL_IS_فی_PATCH_EXT               0x92E7
#تعریف_کړه GL_REFERENCED_BY_TESS_CONTROL_SHADER_EXT 0x9307
#تعریف_کړه GL_REFERENCED_BY_TESS_EVALUATION_SHADER_EXT 0x9308
#تعریف_کړه GL_TESS_CONTROL_SHADER_EXT        0x8E88
#تعریف_کړه GL_TESS_EVALUATION_SHADER_EXT     0x8E87
#تعریف_کړه GL_TESS_CONTROL_SHADER_بټ_EXT    0x00000008
#تعریف_کړه GL_TESS_EVALUATION_SHADER_بټ_EXT 0x00000010
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATCHPARAMETERIEXTPROC) (GLenum pname, GLint ارزښت);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glPatchParameteriEXT (GLenum pname, GLint ارزښت);
#د_که_پای
#د_که_پای /* GL_EXT_tessellation_shader */

#که_نه_تعریف_شوی GL_EXT_texture_border_clamp
#تعریف_کړه GL_EXT_texture_border_clamp 1
#تعریف_کړه GL_TEXTURE_BORDER_COLOR_EXT       0x1004
#تعریف_کړه GL_CLAMP_منزل_BORDER_EXT            0x812D
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERIIVEXTPROC) (GLenum موخه, GLenum pname, ثابت GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERIUIVEXTPROC) (GLenum موخه, GLenum pname, ثابت GLuint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXPARAMETERIIVEXTPROC) (GLenum موخه, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXPARAMETERIUIVEXTPROC) (GLenum موخه, GLenum pname, GLuint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIIVEXTPROC) (GLuint sampler, GLenum pname, ثابت GLint *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIUIVEXTPROC) (GLuint sampler, GLenum pname, ثابت GLuint *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIIVEXTPROC) (GLuint sampler, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIUIVEXTPROC) (GLuint sampler, GLenum pname, GLuint *params);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTexParameterIivEXT (GLenum موخه, GLenum pname, ثابت GLint *params);
GL_APICALL فراغ GL_APIENTRY glTexParameterIuivEXT (GLenum موخه, GLenum pname, ثابت GLuint *params);
GL_APICALL فراغ GL_APIENTRY glGetTexParameterIivEXT (GLenum موخه, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetTexParameterIuivEXT (GLenum موخه, GLenum pname, GLuint *params);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterIivEXT (GLuint sampler, GLenum pname, ثابت GLint *param);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterIuivEXT (GLuint sampler, GLenum pname, ثابت GLuint *param);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameterIivEXT (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameterIuivEXT (GLuint sampler, GLenum pname, GLuint *params);
#د_که_پای
#د_که_پای /* GL_EXT_texture_border_clamp */

#که_نه_تعریف_شوی GL_EXT_texture_بفر
#تعریف_کړه GL_EXT_texture_بفر 1
#تعریف_کړه GL_TEXTURE_بفر_EXT             0x8C2A
#تعریف_کړه GL_TEXTURE_بفر_BINDING_EXT     0x8C2A
#تعریف_کړه GL_MAX_TEXTURE_بفر_اندازه_EXT    0x8C2B
#تعریف_کړه GL_TEXTURE_BINDING_بفر_EXT     0x8C2C
#تعریف_کړه GL_TEXTURE_بفر_معلومات_STORE_BINDING_EXT 0x8C2D
#تعریف_کړه GL_TEXTURE_بفر_دننه_واټن_ALIGNMENT_EXT 0x919F
#تعریف_کړه GL_SAMPLER_بفر_EXT             0x8DC2
#تعریف_کړه GL_INT_SAMPLER_بفر_EXT         0x8DD0
#تعریف_کړه GL_UNSIGNED_INT_SAMPLER_بفر_EXT 0x8DD8
#تعریف_کړه GL_IMAGE_بفر_EXT               0x9051
#تعریف_کړه GL_INT_IMAGE_بفر_EXT           0x905C
#تعریف_کړه GL_UNSIGNED_INT_IMAGE_بفر_EXT  0x9067
#تعریف_کړه GL_TEXTURE_بفر_دننه_واټن_EXT      0x919D
#تعریف_کړه GL_TEXTURE_بفر_اندازه_EXT        0x919E
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXBUFFEREXTPROC) (GLenum موخه, GLenum internalformat, GLuint بفر_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXBUFFERRANGEEXTPROC) (GLenum موخه, GLenum internalformat, GLuint بفر_2, GLintptr دننه_واټن_2, GLsizeiptr اندازه);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Tex_بفر_EXT (GLenum موخه, GLenum internalformat, GLuint بفر_2);
GL_APICALL فراغ GL_APIENTRY gl_Tex_بفر_Range_EXT (GLenum موخه, GLenum internalformat, GLuint بفر_2, GLintptr دننه_واټن_2, GLsizeiptr اندازه);
#د_که_پای
#د_که_پای /* GL_EXT_texture_buffer */

#که_نه_تعریف_شوی GL_EXT_texture_compression_astc_decode_ډېرپېښ
#تعریف_کړه GL_EXT_texture_compression_astc_decode_ډېرپېښ 1
#تعریف_کړه GL_TEXTURE_ASTC_DECODE_PRECISION_EXT 0x8F69
#د_که_پای /* GL_EXT_texture_compression_astc_decode_mode */

#که_نه_تعریف_شوی GL_EXT_texture_compression_bptc
#تعریف_کړه GL_EXT_texture_compression_bptc 1
#تعریف_کړه GL_COMPRESSED_RGBA_BPTC_UNORM_EXT 0x8E8C
#تعریف_کړه GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_EXT 0x8E8D
#تعریف_کړه GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_EXT 0x8E8E
#تعریف_کړه GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_EXT 0x8E8F
#د_که_پای /* GL_EXT_texture_compression_bptc */

#که_نه_تعریف_شوی GL_EXT_texture_compression_dxt1
#تعریف_کړه GL_EXT_texture_compression_dxt1 1
#تعریف_کړه GL_COMPRESSED_RGB_S3TC_DXT1_EXT   0x83F0
#تعریف_کړه GL_COMPRESSED_RGBA_S3TC_DXT1_EXT  0x83F1
#د_که_پای /* GL_EXT_texture_compression_dxt1 */

#که_نه_تعریف_شوی GL_EXT_texture_compression_rgtc
#تعریف_کړه GL_EXT_texture_compression_rgtc 1
#تعریف_کړه GL_COMPRESSED_RED_RGTC1_EXT       0x8DBB
#تعریف_کړه GL_COMPRESSED_SIGNED_RED_RGTC1_EXT 0x8DBC
#تعریف_کړه GL_COMPRESSED_RED_GREEN_RGTC2_EXT 0x8DBD
#تعریف_کړه GL_COMPRESSED_SIGNED_RED_GREEN_RGTC2_EXT 0x8DBE
#د_که_پای /* GL_EXT_texture_compression_rgtc */

#که_نه_تعریف_شوی GL_EXT_texture_compression_s3tc
#تعریف_کړه GL_EXT_texture_compression_s3tc 1
#تعریف_کړه GL_COMPRESSED_RGBA_S3TC_DXT3_EXT  0x83F2
#تعریف_کړه GL_COMPRESSED_RGBA_S3TC_DXT5_EXT  0x83F3
#د_که_پای /* GL_EXT_texture_compression_s3tc */

#که_نه_تعریف_شوی GL_EXT_texture_compression_s3tc_srgb
#تعریف_کړه GL_EXT_texture_compression_s3tc_srgb 1
#تعریف_کړه GL_COMPRESSED_SRGB_S3TC_DXT1_EXT  0x8C4C
#تعریف_کړه GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT 0x8C4D
#تعریف_کړه GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT 0x8C4E
#تعریف_کړه GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT 0x8C4F
#د_که_پای /* GL_EXT_texture_compression_s3tc_srgb */

#که_نه_تعریف_شوی GL_EXT_texture_cube_map_array
#تعریف_کړه GL_EXT_texture_cube_map_array 1
#تعریف_کړه GL_TEXTURE_CUBE_MAP_ARRAY_EXT     0x9009
#تعریف_کړه GL_TEXTURE_BINDING_CUBE_MAP_ARRAY_EXT 0x900A
#تعریف_کړه GL_SAMPLER_CUBE_MAP_ARRAY_EXT     0x900C
#تعریف_کړه GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW_EXT 0x900D
#تعریف_کړه GL_INT_SAMPLER_CUBE_MAP_ARRAY_EXT 0x900E
#تعریف_کړه GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY_EXT 0x900F
#تعریف_کړه GL_IMAGE_CUBE_MAP_ARRAY_EXT       0x9054
#تعریف_کړه GL_INT_IMAGE_CUBE_MAP_ARRAY_EXT   0x905F
#تعریف_کړه GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY_EXT 0x906A
#د_که_پای /* GL_EXT_texture_cube_map_array */

#که_نه_تعریف_شوی GL_EXT_texture_filter_anisotropic
#تعریف_کړه GL_EXT_texture_filter_anisotropic 1
#تعریف_کړه GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#تعریف_کړه GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#د_که_پای /* GL_EXT_texture_filter_anisotropic */

#که_نه_تعریف_شوی GL_EXT_texture_filter_minmax
#تعریف_کړه GL_EXT_texture_filter_minmax 1
#تعریف_کړه GL_TEXTURE_REDUCTION_ډېرپېښ_EXT     0x9366
#تعریف_کړه GL_WEIGHTED_اوسط_EXT           0x9367
#د_که_پای /* GL_EXT_texture_filter_minmax */

#که_نه_تعریف_شوی GL_EXT_texture_format_BGRA8888
#تعریف_کړه GL_EXT_texture_format_BGRA8888 1
#د_که_پای /* GL_EXT_texture_format_BGRA8888 */

#که_نه_تعریف_شوی GL_EXT_texture_format_sRGB_override
#تعریف_کړه GL_EXT_texture_format_sRGB_override 1
#تعریف_کړه GL_TEXTURE_FORMAT_SRGB_OVERRIDE_EXT 0x8FBF
#د_که_پای /* GL_EXT_texture_format_sRGB_override */

#که_نه_تعریف_شوی GL_EXT_texture_mirror_clamp_منزل_څنډه
#تعریف_کړه GL_EXT_texture_mirror_clamp_منزل_څنډه 1
#تعریف_کړه GL_MIRROR_CLAMP_منزل_څنډه_EXT       0x8743
#د_که_پای /* GL_EXT_texture_mirror_clamp_to_edge */

#که_نه_تعریف_شوی GL_EXT_texture_norm16
#تعریف_کړه GL_EXT_texture_norm16 1
#تعریف_کړه GL_R16_EXT                        0x822A
#تعریف_کړه GL_RG16_EXT                       0x822C
#تعریف_کړه GL_RGBA16_EXT                     0x805B
#تعریف_کړه GL_RGB16_EXT                      0x8054
#تعریف_کړه GL_RGB16_SNORM_EXT                0x8F9A
#د_که_پای /* GL_EXT_texture_norm16 */

#که_نه_تعریف_شوی GL_EXT_texture_query_lod
#تعریف_کړه GL_EXT_texture_query_lod 1
#د_که_پای /* GL_EXT_texture_query_lod */

#که_نه_تعریف_شوی GL_EXT_texture_rg
#تعریف_کړه GL_EXT_texture_rg 1
#تعریف_کړه GL_RED_EXT                        0x1903
#تعریف_کړه GL_RG_EXT                         0x8227
#تعریف_کړه GL_R8_EXT                         0x8229
#تعریف_کړه GL_RG8_EXT                        0x822B
#د_که_پای /* GL_EXT_texture_rg */

#که_نه_تعریف_شوی GL_EXT_texture_sRGB_R8
#تعریف_کړه GL_EXT_texture_sRGB_R8 1
#تعریف_کړه GL_SR8_EXT                        0x8FBD
#د_که_پای /* GL_EXT_texture_sRGB_R8 */

#که_نه_تعریف_شوی GL_EXT_texture_sRGB_RG8
#تعریف_کړه GL_EXT_texture_sRGB_RG8 1
#تعریف_کړه GL_SRG8_EXT                       0x8FBE
#د_که_پای /* GL_EXT_texture_sRGB_RG8 */

#که_نه_تعریف_شوی GL_EXT_texture_sRGB_decode
#تعریف_کړه GL_EXT_texture_sRGB_decode 1
#تعریف_کړه GL_TEXTURE_SRGB_DECODE_EXT        0x8A48
#تعریف_کړه GL_DECODE_EXT                     0x8A49
#تعریف_کړه GL_SKIP_DECODE_EXT                0x8A4A
#د_که_پای /* GL_EXT_texture_sRGB_decode */

#که_نه_تعریف_شوی GL_EXT_texture_shadow_lod
#تعریف_کړه GL_EXT_texture_shadow_lod 1
#د_که_پای /* GL_EXT_texture_shadow_lod */

#که_نه_تعریف_شوی GL_EXT_texture_storage
#تعریف_کړه GL_EXT_texture_storage 1
#تعریف_کړه GL_TEXTURE_IMMUTABLE_FORMAT_EXT   0x912F
#تعریف_کړه GL_ALPHA8_EXT                     0x803C
#تعریف_کړه GL_LUMINANCE8_EXT                 0x8040
#تعریف_کړه GL_LUMINANCE8_ALPHA8_EXT          0x8045
#تعریف_کړه GL_RGBA32F_EXT                    0x8814
#تعریف_کړه GL_RGB32F_EXT                     0x8815
#تعریف_کړه GL_ALPHA32F_EXT                   0x8816
#تعریف_کړه GL_LUMINANCE32F_EXT               0x8818
#تعریف_کړه GL_LUMINANCE_ALPHA32F_EXT         0x8819
#تعریف_کړه GL_ALPHA16F_EXT                   0x881C
#تعریف_کړه GL_LUMINANCE16F_EXT               0x881E
#تعریف_کړه GL_LUMINANCE_ALPHA16F_EXT         0x881F
#تعریف_کړه GL_R32F_EXT                       0x822E
#تعریف_کړه GL_RG32F_EXT                      0x8230
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE1DEXTPROC) (GLenum موخه, GLsizei پوړونه, GLenum internalformat, GLsizei پلنوالی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE2DEXTPROC) (GLenum موخه, GLsizei پوړونه, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE3DEXTPROC) (GLenum موخه, GLsizei پوړونه, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGE1DEXTPROC) (GLuint texture, GLenum موخه, GLsizei پوړونه, GLenum internalformat, GLsizei پلنوالی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGE2DEXTPROC) (GLuint texture, GLenum موخه, GLsizei پوړونه, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGE3DEXTPROC) (GLuint texture, GLenum موخه, GLsizei پوړونه, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTexStorage1DEXT (GLenum موخه, GLsizei پوړونه, GLenum internalformat, GLsizei پلنوالی);
GL_APICALL فراغ GL_APIENTRY glTexStorage2DEXT (GLenum موخه, GLsizei پوړونه, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
GL_APICALL فراغ GL_APIENTRY glTexStorage3DEXT (GLenum موخه, GLsizei پوړونه, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2);
GL_APICALL فراغ GL_APIENTRY glTextureStorage1DEXT (GLuint texture, GLenum موخه, GLsizei پوړونه, GLenum internalformat, GLsizei پلنوالی);
GL_APICALL فراغ GL_APIENTRY glTextureStorage2DEXT (GLuint texture, GLenum موخه, GLsizei پوړونه, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
GL_APICALL فراغ GL_APIENTRY glTextureStorage3DEXT (GLuint texture, GLenum موخه, GLsizei پوړونه, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2);
#د_که_پای
#د_که_پای /* GL_EXT_texture_storage */

#که_نه_تعریف_شوی GL_EXT_texture_storage_compression
#تعریف_کړه GL_EXT_texture_storage_compression 1
#تعریف_کړه GL_عدد_SURFACE_COMPRESSION_FIXED_RATES_EXT 0x8F6E
#تعریف_کړه GL_SURFACE_COMPRESSION_FIXED_شرح_1_BPC_EXT 0x96C4
#تعریف_کړه GL_SURFACE_COMPRESSION_FIXED_شرح_2_BPC_EXT 0x96C5
#تعریف_کړه GL_SURFACE_COMPRESSION_FIXED_شرح_3_BPC_EXT 0x96C6
#تعریف_کړه GL_SURFACE_COMPRESSION_FIXED_شرح_4_BPC_EXT 0x96C7
#تعریف_کړه GL_SURFACE_COMPRESSION_FIXED_شرح_5_BPC_EXT 0x96C8
#تعریف_کړه GL_SURFACE_COMPRESSION_FIXED_شرح_6_BPC_EXT 0x96C9
#تعریف_کړه GL_SURFACE_COMPRESSION_FIXED_شرح_7_BPC_EXT 0x96CA
#تعریف_کړه GL_SURFACE_COMPRESSION_FIXED_شرح_8_BPC_EXT 0x96CB
#تعریف_کړه GL_SURFACE_COMPRESSION_FIXED_شرح_9_BPC_EXT 0x96CC
#تعریف_کړه GL_SURFACE_COMPRESSION_FIXED_شرح_10_BPC_EXT 0x96CD
#تعریف_کړه GL_SURFACE_COMPRESSION_FIXED_شرح_11_BPC_EXT 0x96CE
#تعریف_کړه GL_SURFACE_COMPRESSION_FIXED_شرح_12_BPC_EXT 0x96CF
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGEATTRIBS2DEXTPROC) (GLenum موخه, GLsizei پوړونه, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی, ثابت GLint* attrib_list);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGEATTRIBS3DEXTPROC) (GLenum موخه, GLsizei پوړونه, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, ثابت GLint* attrib_list);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTexStorageAttribs2DEXT (GLenum موخه, GLsizei پوړونه, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی, ثابت GLint* attrib_list);
GL_APICALL فراغ GL_APIENTRY glTexStorageAttribs3DEXT (GLenum موخه, GLsizei پوړونه, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, ثابت GLint* attrib_list);
#د_که_پای
#د_که_پای /* GL_EXT_texture_storage_compression */

#که_نه_تعریف_شوی GL_EXT_texture_type_2_10_10_10_REV
#تعریف_کړه GL_EXT_texture_type_2_10_10_10_REV 1
#تعریف_کړه GL_UNSIGNED_INT_2_10_10_10_REV_EXT 0x8368
#د_که_پای /* GL_EXT_texture_type_2_10_10_10_REV */

#که_نه_تعریف_شوی GL_EXT_texture_view
#تعریف_کړه GL_EXT_texture_view 1
#تعریف_کړه GL_TEXTURE_VIEW_MIN_LEVEL_EXT     0x82DB
#تعریف_کړه GL_TEXTURE_VIEW_عدد_پوړونه_EXT    0x82DC
#تعریف_کړه GL_TEXTURE_VIEW_MIN_LAYER_EXT     0x82DD
#تعریف_کړه GL_TEXTURE_VIEW_عدد_LAYERS_EXT    0x82DE
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTUREVIEWEXTPROC) (GLuint texture, GLenum موخه, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTextureViewEXT (GLuint texture, GLenum موخه, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
#د_که_پای
#د_که_پای /* GL_EXT_texture_view */

#که_نه_تعریف_شوی GL_EXT_unpack_subimage
#تعریف_کړه GL_EXT_unpack_subimage 1
#تعریف_کړه GL_UNPACK_لیکه_اوږدتیا_EXT          0x0CF2
#تعریف_کړه GL_UNPACK_SKIP_لیکې_EXT           0x0CF3
#تعریف_کړه GL_UNPACK_SKIP_PIXELS_EXT         0x0CF4
#د_که_پای /* GL_EXT_unpack_subimage */

#که_نه_تعریف_شوی GL_EXT_win32_keyed_mutex
#تعریف_کړه GL_EXT_win32_keyed_mutex 1
تعريفنوع GLboolean (GL_APIENTRYP PFNGLACQUIREKEYEDMUTEXWIN32EXTPROC) (GLuint حافظه, GLuint64 کلی, GLuint timeout);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLRELEASEKEYEDMUTEXWIN32EXTPROC) (GLuint حافظه, GLuint64 کلی);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL GLboolean GL_APIENTRY glAcquireKeyedMutexWin32EXT (GLuint حافظه, GLuint64 کلی, GLuint timeout);
GL_APICALL GLboolean GL_APIENTRY glReleaseKeyedMutexWin32EXT (GLuint حافظه, GLuint64 کلی);
#د_که_پای
#د_که_پای /* GL_EXT_win32_keyed_mutex */

#که_نه_تعریف_شوی GL_EXT_کړکۍ_rectangles
#تعریف_کړه GL_EXT_کړکۍ_rectangles 1
#تعریف_کړه GL_INCLUSIVE_EXT                  0x8F10
#تعریف_کړه GL_EXCLUSIVE_EXT                  0x8F11
#تعریف_کړه GL_کړکۍ_RECTANGLE_EXT           0x8F12
#تعریف_کړه GL_کړکۍ_RECTANGLE_ډېرپېښ_EXT      0x8F13
#تعریف_کړه GL_MAX_کړکۍ_RECTANGLES_EXT      0x8F14
#تعریف_کړه GL_عدد_کړکۍ_RECTANGLES_EXT      0x8F15
تعريفنوع فراغ (GL_APIENTRYP PFNGLWINDOWRECTANGLESEXTPROC) (GLenum ډېرپېښ, GLsizei شمېر, ثابت GLint *box);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_کړکۍ_Rectangles_EXT (GLenum ډېرپېښ, GLsizei شمېر, ثابت GLint *box);
#د_که_پای
#د_که_پای /* GL_EXT_window_rectangles */

#که_نه_تعریف_شوی GL_FJ_shader_دوګونی_GCCSO
#تعریف_کړه GL_FJ_shader_دوګونی_GCCSO 1
#تعریف_کړه GL_GCCSO_SHADER_دوګونی_FJ         0x9260
#د_که_پای /* GL_FJ_shader_binary_GCCSO */

#که_نه_تعریف_شوی GL_HUAWEI_پروګرام_دوګونی
#تعریف_کړه GL_HUAWEI_پروګرام_دوګونی 1
#تعریف_کړه GL_پروګرام_دوګونی_HUAWEI          0x9771
#د_که_پای /* GL_HUAWEI_program_binary */

#که_نه_تعریف_شوی GL_HUAWEI_shader_دوګونی
#تعریف_کړه GL_HUAWEI_shader_دوګونی 1
#تعریف_کړه GL_SHADER_دوګونی_HUAWEI           0x9770
#د_که_پای /* GL_HUAWEI_shader_binary */

#که_نه_تعریف_شوی GL_IMG_bindless_texture
#تعریف_کړه GL_IMG_bindless_texture 1
تعريفنوع GLuint64 (GL_APIENTRYP PFNGLGETTEXTUREHANDLEIMGPROC) (GLuint texture);
تعريفنوع GLuint64 (GL_APIENTRYP PFNGLGETTEXTURESAMPLERHANDLEIMGPROC) (GLuint texture, GLuint sampler);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMHANDLEUI64IMGPROC) (GLint location, GLuint64 ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMHANDLEUI64VIMGPROC) (GLint location, GLsizei شمېر, ثابت GLuint64 *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64IMGPROC) (GLuint پروګرام, GLint location, GLuint64 ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64VIMGPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLuint64 *ارزښتونه);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL GLuint64 GL_APIENTRY glGetTextureHandleIMG (GLuint texture);
GL_APICALL GLuint64 GL_APIENTRY glGetTextureSamplerHandleIMG (GLuint texture, GLuint sampler);
GL_APICALL فراغ GL_APIENTRY gl_یوشان_Handleui64_IMG (GLint location, GLuint64 ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_یوشان_Handleui64v_IMG (GLint location, GLsizei شمېر, ثابت GLuint64 *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_یوشان_Handleui64_IMG (GLuint پروګرام, GLint location, GLuint64 ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_یوشان_Handleui64v_IMG (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLuint64 *ارزښتونه);
#د_که_پای
#د_که_پای /* GL_IMG_bindless_texture */

#که_نه_تعریف_شوی GL_IMG_framebuffer_downsample
#تعریف_کړه GL_IMG_framebuffer_downsample 1
#تعریف_کړه GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_AND_DOWNSAMPLE_IMG 0x913C
#تعریف_کړه GL_عدد_DOWNSAMPLE_SCALES_IMG      0x913D
#تعریف_کړه GL_DOWNSAMPLE_SCALES_IMG          0x913E
#تعریف_کړه GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SCALE_IMG 0x913F
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DDOWNSAMPLEIMGPROC) (GLenum موخه, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint xscale, GLint yscale);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURELAYERDOWNSAMPLEIMGPROC) (GLenum موخه, GLenum attachment, GLuint texture, GLint level, GLint layer, GLint xscale, GLint yscale);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferTexture2DDownsampleIMG (GLenum موخه, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint xscale, GLint yscale);
GL_APICALL فراغ GL_APIENTRY glFramebufferTextureLayerDownsampleIMG (GLenum موخه, GLenum attachment, GLuint texture, GLint level, GLint layer, GLint xscale, GLint yscale);
#د_که_پای
#د_که_پای /* GL_IMG_framebuffer_downsample */

#که_نه_تعریف_شوی GL_IMG_multisampled_render_منزل_texture
#تعریف_کړه GL_IMG_multisampled_render_منزل_texture 1
#تعریف_کړه GL_RENDERBUFFER_SAMPLES_IMG       0x9133
#تعریف_کړه GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_IMG 0x9134
#تعریف_کړه GL_MAX_SAMPLES_IMG                0x9135
#تعریف_کړه GL_TEXTURE_SAMPLES_IMG            0x9136
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEIMGPROC) (GLenum موخه, GLsizei samples, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEIMGPROC) (GLenum موخه, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glRenderbufferStorageMultisampleIMG (GLenum موخه, GLsizei samples, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
GL_APICALL فراغ GL_APIENTRY glFramebufferTexture2DMultisampleIMG (GLenum موخه, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#د_که_پای
#د_که_پای /* GL_IMG_multisampled_render_to_texture */

#که_نه_تعریف_شوی GL_IMG_پروګرام_دوګونی
#تعریف_کړه GL_IMG_پروګرام_دوګونی 1
#تعریف_کړه GL_SGX_پروګرام_دوګونی_IMG         0x9130
#د_که_پای /* GL_IMG_program_binary */

#که_نه_تعریف_شوی GL_IMG_read_format
#تعریف_کړه GL_IMG_read_format 1
#تعریف_کړه GL_BGRA_IMG                       0x80E1
#تعریف_کړه GL_UNSIGNED_SHORT_4_4_4_4_REV_IMG 0x8365
#د_که_پای /* GL_IMG_read_format */

#که_نه_تعریف_شوی GL_IMG_shader_دوګونی
#تعریف_کړه GL_IMG_shader_دوګونی 1
#تعریف_کړه GL_SGX_دوګونی_IMG                 0x8C0A
#د_که_پای /* GL_IMG_shader_binary */

#که_نه_تعریف_شوی GL_IMG_texture_compression_pvrtc
#تعریف_کړه GL_IMG_texture_compression_pvrtc 1
#تعریف_کړه GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG 0x8C00
#تعریف_کړه GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG 0x8C01
#تعریف_کړه GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG 0x8C02
#تعریف_کړه GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG 0x8C03
#د_که_پای /* GL_IMG_texture_compression_pvrtc */

#که_نه_تعریف_شوی GL_IMG_texture_compression_pvrtc2
#تعریف_کړه GL_IMG_texture_compression_pvrtc2 1
#تعریف_کړه GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG 0x9137
#تعریف_کړه GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG 0x9138
#د_که_پای /* GL_IMG_texture_compression_pvrtc2 */

#که_نه_تعریف_شوی GL_IMG_texture_filter_cubic
#تعریف_کړه GL_IMG_texture_filter_cubic 1
#تعریف_کړه GL_CUBIC_IMG                      0x9139
#تعریف_کړه GL_CUBIC_MIPMAP_تر_ټولو_نږدې_IMG       0x913A
#تعریف_کړه GL_CUBIC_MIPMAP_خطي_IMG        0x913B
#د_که_پای /* GL_IMG_texture_filter_cubic */

#که_نه_تعریف_شوی GL_INTEL_blackhole_render
#تعریف_کړه GL_INTEL_blackhole_render 1
#تعریف_کړه GL_BLACKHOLE_RENDER_INTEL         0x83FC
#د_که_پای /* GL_INTEL_blackhole_render */

#که_نه_تعریف_شوی GL_INTEL_conservative_rasterization
#تعریف_کړه GL_INTEL_conservative_rasterization 1
#تعریف_کړه GL_CONSERVATIVE_RASTERIZATION_INTEL 0x83FE
#د_که_پای /* GL_INTEL_conservative_rasterization */

#که_نه_تعریف_شوی GL_INTEL_framebuffer_CMAA
#تعریف_کړه GL_INTEL_framebuffer_CMAA 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLAPPLYFRAMEBUFFERATTACHMENTCMAAINTELPROC) (فراغ);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glApplyFramebufferAttachmentCMAAINTEL (فراغ);
#د_که_پای
#د_که_پای /* GL_INTEL_framebuffer_CMAA */

#که_نه_تعریف_شوی GL_INTEL_performance_query
#تعریف_کړه GL_INTEL_performance_query 1
#تعریف_کړه GL_PERFQUERY_SINGLE_CONTEXT_INTEL 0x00000000
#تعریف_کړه GL_PERFQUERY_GLOBAL_CONTEXT_INTEL 0x00000001
#تعریف_کړه GL_PERFQUERY_WAIT_INTEL           0x83FB
#تعریف_کړه GL_PERFQUERY_FLUSH_INTEL          0x83FA
#تعریف_کړه GL_PERFQUERY_DONOT_FLUSH_INTEL    0x83F9
#تعریف_کړه GL_PERFQUERY_COUNTER_EVENT_INTEL  0x94F0
#تعریف_کړه GL_PERFQUERY_COUNTER_DURATION_NORM_INTEL 0x94F1
#تعریف_کړه GL_PERFQUERY_COUNTER_DURATION_RAW_INTEL 0x94F2
#تعریف_کړه GL_PERFQUERY_COUNTER_THROUGHPUT_INTEL 0x94F3
#تعریف_کړه GL_PERFQUERY_COUNTER_RAW_INTEL    0x94F4
#تعریف_کړه GL_PERFQUERY_COUNTER_TIMESTAMP_INTEL 0x94F5
#تعریف_کړه GL_PERFQUERY_COUNTER_معلومات_UINT32_INTEL 0x94F8
#تعریف_کړه GL_PERFQUERY_COUNTER_معلومات_UINT64_INTEL 0x94F9
#تعریف_کړه GL_PERFQUERY_COUNTER_معلومات_FLOAT_INTEL 0x94FA
#تعریف_کړه GL_PERFQUERY_COUNTER_معلومات_DOUBLE_INTEL 0x94FB
#تعریف_کړه GL_PERFQUERY_COUNTER_معلومات_BOOL32_INTEL 0x94FC
#تعریف_کړه GL_PERFQUERY_QUERY_NAME_اوږدتیا_MAX_INTEL 0x94FD
#تعریف_کړه GL_PERFQUERY_COUNTER_NAME_اوږدتیا_MAX_INTEL 0x94FE
#تعریف_کړه GL_PERFQUERY_COUNTER_DESC_اوږدتیا_MAX_INTEL 0x94FF
#تعریف_کړه GL_PERFQUERY_GPA_EXTENDED_COUNTERS_INTEL 0x9500
تعريفنوع فراغ (GL_APIENTRYP PFNGLBEGINPERFQUERYINTELPROC) (GLuint queryHandle);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCREATEPERFQUERYINTELPROC) (GLuint queryId, GLuint *queryHandle);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEPERFQUERYINTELPROC) (GLuint queryHandle);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENDPERFQUERYINTELPROC) (GLuint queryHandle);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFIRSTPERFQUERYIDINTELPROC) (GLuint *queryId);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNEXTPERFQUERYIDINTELPROC) (GLuint queryId, GLuint *بل_Query_Id);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFCOUNTERINFOINTELPROC) (GLuint queryId, GLuint counterId, GLuint counter_Name_اوږدتیا, GLchar *counterName, GLuint counter_Desc_اوږدتیا, GLchar *counterDesc, GLuint *counter_دننه_واټن, GLuint *counter_معلومات_اندازه, GLuint *counterTypeEnum, GLuint *counter_معلومات_Type_Enum, GLuint64 *raw_Counter_Max_ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFQUERYDATAINTELPROC) (GLuint queryHandle, GLuint flags, GLsizei معلومات_اندازه_2, فراغ *معلومات, GLuint *بایټونه_Written);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFQUERYIDBYNAMEINTELPROC) (GLchar *queryName, GLuint *queryId);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFQUERYINFOINTELPROC) (GLuint queryId, GLuint query_Name_اوږدتیا, GLchar *queryName, GLuint *معلومات_اندازه_2, GLuint *noCounters, GLuint *noInstances, GLuint *caps_ماسک);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glBeginPerfQueryINTEL (GLuint queryHandle);
GL_APICALL فراغ GL_APIENTRY glCreatePerfQueryINTEL (GLuint queryId, GLuint *queryHandle);
GL_APICALL فراغ GL_APIENTRY glDeletePerfQueryINTEL (GLuint queryHandle);
GL_APICALL فراغ GL_APIENTRY gl_پای_ټکی_Perf_Query_INTEL (GLuint queryHandle);
GL_APICALL فراغ GL_APIENTRY gl_Get_لومړی_Perf_Query_Id_INTEL (GLuint *queryId);
GL_APICALL فراغ GL_APIENTRY gl_Get_بل_Perf_Query_Id_INTEL (GLuint queryId, GLuint *بل_Query_Id);
GL_APICALL فراغ GL_APIENTRY glGetPerfCounterInfoINTEL (GLuint queryId, GLuint counterId, GLuint counter_Name_اوږدتیا, GLchar *counterName, GLuint counter_Desc_اوږدتیا, GLchar *counterDesc, GLuint *counter_دننه_واټن, GLuint *counter_معلومات_اندازه, GLuint *counterTypeEnum, GLuint *counter_معلومات_Type_Enum, GLuint64 *raw_Counter_Max_ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_Get_Perf_Query_معلومات_INTEL (GLuint queryHandle, GLuint flags, GLsizei معلومات_اندازه_2, فراغ *معلومات, GLuint *بایټونه_Written);
GL_APICALL فراغ GL_APIENTRY glGetPerfQueryIdByNameINTEL (GLchar *queryName, GLuint *queryId);
GL_APICALL فراغ GL_APIENTRY glGetPerfQueryInfoINTEL (GLuint queryId, GLuint query_Name_اوږدتیا, GLchar *queryName, GLuint *معلومات_اندازه_2, GLuint *noCounters, GLuint *noInstances, GLuint *caps_ماسک);
#د_که_پای
#د_که_پای /* GL_INTEL_performance_query */

#که_نه_تعریف_شوی GL_MESA_bgra
#تعریف_کړه GL_MESA_bgra 1
#تعریف_کړه GL_BGR_EXT                        0x80E0
#د_که_پای /* GL_MESA_bgra */

#که_نه_تعریف_شوی GL_MESA_framebuffer_flip_x
#تعریف_کړه GL_MESA_framebuffer_flip_x 1
#تعریف_کړه GL_FRAMEBUFFER_FLIP_X_MESA        0x8BBC
#د_که_پای /* GL_MESA_framebuffer_flip_x */

#که_نه_تعریف_شوی GL_MESA_framebuffer_flip_y
#تعریف_کړه GL_MESA_framebuffer_flip_y 1
#تعریف_کړه GL_FRAMEBUFFER_FLIP_Y_MESA        0x8BBB
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERPARAMETERIMESAPROC) (GLenum موخه, GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFRAMEBUFFERPARAMETERIVMESAPROC) (GLenum موخه, GLenum pname, GLint *params);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferParameteriMESA (GLenum موخه, GLenum pname, GLint param);
GL_APICALL فراغ GL_APIENTRY glGetFramebufferParameterivMESA (GLenum موخه, GLenum pname, GLint *params);
#د_که_پای
#د_که_پای /* GL_MESA_framebuffer_flip_y */

#که_نه_تعریف_شوی GL_MESA_framebuffer_بدلون_xy
#تعریف_کړه GL_MESA_framebuffer_بدلون_xy 1
#تعریف_کړه GL_FRAMEBUFFER_بدلون_XY_MESA       0x8BBD
#د_که_پای /* GL_MESA_framebuffer_swap_xy */

#که_نه_تعریف_شوی GL_MESA_پروګرام_دوګونی_formats
#تعریف_کړه GL_MESA_پروګرام_دوګونی_formats 1
#تعریف_کړه GL_پروګرام_دوګونی_FORMAT_MESA     0x875F
#د_که_پای /* GL_MESA_program_binary_formats */

#که_نه_تعریف_شوی GL_MESA_sampler_objects
#تعریف_کړه GL_MESA_sampler_objects 1
#تعریف_کړه GL_SAMPLER_BINDING                0x8919
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENSAMPLERSPROC) (GLsizei شمېر, GLuint *samplers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETESAMPLERSPROC) (GLsizei شمېر, ثابت GLuint *samplers);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISSAMPLERPROC) (GLuint sampler);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDSAMPLERPROC) (GLuint unit, GLuint sampler);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIPROC) (GLuint sampler, GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, ثابت GLint *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERFPROC) (GLuint sampler, GLenum pname, GLfloat param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, ثابت GLfloat *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, GLfloat *params);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glGenSamplers (GLsizei شمېر, GLuint *samplers);
GL_APICALL فراغ GL_APIENTRY glDeleteSamplers (GLsizei شمېر, ثابت GLuint *samplers);
GL_APICALL GLboolean GL_APIENTRY glIsSampler (GLuint sampler);
GL_APICALL فراغ GL_APIENTRY glBindSampler (GLuint unit, GLuint sampler);
GL_APICALL فراغ GL_APIENTRY glSamplerParameteri (GLuint sampler, GLenum pname, GLint param);
GL_APICALL فراغ GL_APIENTRY glSamplerParameteriv (GLuint sampler, GLenum pname, ثابت GLint *param);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterf (GLuint sampler, GLenum pname, GLfloat param);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterfv (GLuint sampler, GLenum pname, ثابت GLfloat *param);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameteriv (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameterfv (GLuint sampler, GLenum pname, GLfloat *params);
#د_که_پای
#د_که_پای /* GL_MESA_sampler_objects */

#که_نه_تعریف_شوی GL_MESA_shader_integer_functions
#تعریف_کړه GL_MESA_shader_integer_functions 1
#د_که_پای /* GL_MESA_shader_integer_functions */

#که_نه_تعریف_شوی GL_MESA_texture_const_bandwidth
#تعریف_کړه GL_MESA_texture_const_bandwidth 1
#تعریف_کړه GL_CONST_BW_TILING_MESA           0x8BBE
#د_که_پای /* GL_MESA_texture_const_bandwidth */

#که_نه_تعریف_شوی GL_NVX_blend_equation_advanced_multi_draw_buffers
#تعریف_کړه GL_NVX_blend_equation_advanced_multi_draw_buffers 1
#د_که_پای /* GL_NVX_blend_equation_advanced_multi_draw_buffers */

#که_نه_تعریف_شوی GL_NV_bindless_texture
#تعریف_کړه GL_NV_bindless_texture 1
تعريفنوع GLuint64 (GL_APIENTRYP PFNGLGETTEXTUREHANDLENVPROC) (GLuint texture);
تعريفنوع GLuint64 (GL_APIENTRYP PFNGLGETTEXTURESAMPLERHANDLENVPROC) (GLuint texture, GLuint sampler);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMAKETEXTUREHANDLERESIDENTNVPROC) (GLuint64 handle);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMAKETEXTUREHANDLENONRESIDENTNVPROC) (GLuint64 handle);
تعريفنوع GLuint64 (GL_APIENTRYP PFNGLGETIMAGEHANDLENVPROC) (GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMAKEIMAGEHANDLERESIDENTNVPROC) (GLuint64 handle, GLenum access);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMAKEIMAGEHANDLENONRESIDENTNVPROC) (GLuint64 handle);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMHANDLEUI64NVPROC) (GLint location, GLuint64 ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMHANDLEUI64VNVPROC) (GLint location, GLsizei شمېر, ثابت GLuint64 *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64NVPROC) (GLuint پروګرام, GLint location, GLuint64 ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64VNVPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLuint64 *ارزښتونه);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISTEXTUREHANDLERESIDENTNVPROC) (GLuint64 handle);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISIMAGEHANDLERESIDENTNVPROC) (GLuint64 handle);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL GLuint64 GL_APIENTRY glGetTextureHandleNV (GLuint texture);
GL_APICALL GLuint64 GL_APIENTRY glGetTextureSamplerHandleNV (GLuint texture, GLuint sampler);
GL_APICALL فراغ GL_APIENTRY glMakeTextureHandleResidentNV (GLuint64 handle);
GL_APICALL فراغ GL_APIENTRY glMakeTextureHandleNonResidentNV (GLuint64 handle);
GL_APICALL GLuint64 GL_APIENTRY glGetImageHandleNV (GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format);
GL_APICALL فراغ GL_APIENTRY glMakeImageHandleResidentNV (GLuint64 handle, GLenum access);
GL_APICALL فراغ GL_APIENTRY glMakeImageHandleNonResidentNV (GLuint64 handle);
GL_APICALL فراغ GL_APIENTRY gl_یوشان_Handleui64_NV (GLint location, GLuint64 ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_یوشان_Handleui64v_NV (GLint location, GLsizei شمېر, ثابت GLuint64 *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_یوشان_Handleui64_NV (GLuint پروګرام, GLint location, GLuint64 ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_یوشان_Handleui64v_NV (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLuint64 *ارزښتونه);
GL_APICALL GLboolean GL_APIENTRY glIsTextureHandleResidentNV (GLuint64 handle);
GL_APICALL GLboolean GL_APIENTRY glIsImageHandleResidentNV (GLuint64 handle);
#د_که_پای
#د_که_پای /* GL_NV_bindless_texture */

#که_نه_تعریف_شوی GL_NV_blend_equation_advanced
#تعریف_کړه GL_NV_blend_equation_advanced 1
#تعریف_کړه GL_BLEND_OVERLAP_NV               0x9281
#تعریف_کړه GL_BLEND_PREMULTIPLIED_SRC_NV     0x9280
#تعریف_کړه GL_BLUE_NV                        0x1905
#تعریف_کړه GL_COLORBURN_NV                   0x929A
#تعریف_کړه GL_COLORDODGE_NV                  0x9299
#تعریف_کړه GL_CONJOINT_NV                    0x9284
#تعریف_کړه GL_CONTRAST_NV                    0x92A1
#تعریف_کړه GL_DARKEN_NV                      0x9297
#تعریف_کړه GL_DIFFERENCE_NV                  0x929E
#تعریف_کړه GL_DISJOINT_NV                    0x9283
#تعریف_کړه GL_DST_ATOP_NV                    0x928F
#تعریف_کړه GL_DST_دننه_NV                      0x928B
#تعریف_کړه GL_DST_NV                         0x9287
#تعریف_کړه GL_DST_بهر_NV                     0x928D
#تعریف_کړه GL_DST_OVER_NV                    0x9289
#تعریف_کړه GL_EXCLUSION_NV                   0x92A0
#تعریف_کړه GL_GREEN_NV                       0x1904
#تعریف_کړه GL_HARDLIGHT_NV                   0x929B
#تعریف_کړه GL_HARDMIX_NV                     0x92A9
#تعریف_کړه GL_HSL_COLOR_NV                   0x92AF
#تعریف_کړه GL_HSL_HUE_NV                     0x92AD
#تعریف_کړه GL_HSL_LUMINOSITY_NV              0x92B0
#تعریف_کړه GL_HSL_SATURATION_NV              0x92AE
#تعریف_کړه GL_INVERT_OVG_NV                  0x92B4
#تعریف_کړه GL_INVERT_RGB_NV                  0x92A3
#تعریف_کړه GL_LIGHTEN_NV                     0x9298
#تعریف_کړه GL_LINEARBURN_NV                  0x92A5
#تعریف_کړه GL_LINEARDODGE_NV                 0x92A4
#تعریف_کړه GL_LINEARLIGHT_NV                 0x92A7
#تعریف_کړه GL_MINUS_CLAMPED_NV               0x92B3
#تعریف_کړه GL_MINUS_NV                       0x929F
#تعریف_کړه GL_MULTIPLY_NV                    0x9294
#تعریف_کړه GL_OVERLAY_NV                     0x9296
#تعریف_کړه GL_PINLIGHT_NV                    0x92A8
#تعریف_کړه GL_PLUS_CLAMPED_ALPHA_NV          0x92B2
#تعریف_کړه GL_PLUS_CLAMPED_NV                0x92B1
#تعریف_کړه GL_PLUS_DARKER_NV                 0x9292
#تعریف_کړه GL_PLUS_NV                        0x9291
#تعریف_کړه GL_RED_NV                         0x1903
#تعریف_کړه GL_SCREEN_NV                      0x9295
#تعریف_کړه GL_SOFTLIGHT_NV                   0x929C
#تعریف_کړه GL_SRC_ATOP_NV                    0x928E
#تعریف_کړه GL_SRC_دننه_NV                      0x928A
#تعریف_کړه GL_SRC_NV                         0x9286
#تعریف_کړه GL_SRC_بهر_NV                     0x928C
#تعریف_کړه GL_SRC_OVER_NV                    0x9288
#تعریف_کړه GL_UNCORRELATED_NV                0x9282
#تعریف_کړه GL_VIVIDLIGHT_NV                  0x92A6
#تعریف_کړه GL_XOR_NV                         0x1506
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDPARAMETERINVPROC) (GLenum pname, GLint ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDBARRIERNVPROC) (فراغ);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glBlendParameteriNV (GLenum pname, GLint ارزښت);
GL_APICALL فراغ GL_APIENTRY glBlendBarrierNV (فراغ);
#د_که_پای
#د_که_پای /* GL_NV_blend_equation_advanced */

#که_نه_تعریف_شوی GL_NV_blend_equation_advanced_coherent
#تعریف_کړه GL_NV_blend_equation_advanced_coherent 1
#تعریف_کړه GL_BLEND_ADVANCED_COHERENT_NV     0x9285
#د_که_پای /* GL_NV_blend_equation_advanced_coherent */

#که_نه_تعریف_شوی GL_NV_blend_minmax_ضریب
#تعریف_کړه GL_NV_blend_minmax_ضریب 1
#تعریف_کړه GL_ضریب_MIN_AMD                 0x901C
#تعریف_کړه GL_ضریب_MAX_AMD                 0x901D
#د_که_پای /* GL_NV_blend_minmax_factor */

#که_نه_تعریف_شوی GL_NV_clip_space_w_scaling
#تعریف_کړه GL_NV_clip_space_w_scaling 1
#تعریف_کړه GL_VIEWPORT_POSITION_W_SCALE_NV   0x937C
#تعریف_کړه GL_VIEWPORT_POSITION_W_SCALE_X_COEFF_NV 0x937D
#تعریف_کړه GL_VIEWPORT_POSITION_W_SCALE_Y_COEFF_NV 0x937E
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTPOSITIONWSCALENVPROC) (GLuint شاخص, GLfloat xcoeff, GLfloat ycoeff);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glViewportPositionWScaleNV (GLuint شاخص, GLfloat xcoeff, GLfloat ycoeff);
#د_که_پای
#د_که_پای /* GL_NV_clip_space_w_scaling */

#که_نه_تعریف_شوی GL_NV_compute_shader_derivatives
#تعریف_کړه GL_NV_compute_shader_derivatives 1
#د_که_پای /* GL_NV_compute_shader_derivatives */

#که_نه_تعریف_شوی GL_NV_conditional_render
#تعریف_کړه GL_NV_conditional_render 1
#تعریف_کړه GL_QUERY_WAIT_NV                  0x8E13
#تعریف_کړه GL_QUERY_NO_WAIT_NV               0x8E14
#تعریف_کړه GL_QUERY_BY_REGION_WAIT_NV        0x8E15
#تعریف_کړه GL_QUERY_BY_REGION_NO_WAIT_NV     0x8E16
تعريفنوع فراغ (GL_APIENTRYP PFNGLBEGINCONDITIONALRENDERNVPROC) (GLuint id, GLenum ډېرپېښ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENDCONDITIONALRENDERNVPROC) (فراغ);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glBeginConditionalRenderNV (GLuint id, GLenum ډېرپېښ);
GL_APICALL فراغ GL_APIENTRY gl_پای_ټکی_Conditional_Render_NV (فراغ);
#د_که_پای
#د_که_پای /* GL_NV_conditional_render */

#که_نه_تعریف_شوی GL_NV_conservative_raster
#تعریف_کړه GL_NV_conservative_raster 1
#تعریف_کړه GL_CONSERVATIVE_RASTERIZATION_NV  0x9346
#تعریف_کړه GL_SUBPIXEL_PRECISION_BIAS_X_بټونه_NV 0x9347
#تعریف_کړه GL_SUBPIXEL_PRECISION_BIAS_Y_بټونه_NV 0x9348
#تعریف_کړه GL_MAX_SUBPIXEL_PRECISION_BIAS_بټونه_NV 0x9349
تعريفنوع فراغ (GL_APIENTRYP PFNGLSUBPIXELPRECISIONBIASNVPROC) (GLuint xbits, GLuint ybits);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glSubpixelPrecisionBiasNV (GLuint xbits, GLuint ybits);
#د_که_پای
#د_که_پای /* GL_NV_conservative_raster */

#که_نه_تعریف_شوی GL_NV_conservative_raster_pre_snap
#تعریف_کړه GL_NV_conservative_raster_pre_snap 1
#تعریف_کړه GL_CONSERVATIVE_RASTER_ډېرپېښ_PRE_SNAP_NV 0x9550
#د_که_پای /* GL_NV_conservative_raster_pre_snap */

#که_نه_تعریف_شوی GL_NV_conservative_raster_pre_snap_triangles
#تعریف_کړه GL_NV_conservative_raster_pre_snap_triangles 1
#تعریف_کړه GL_CONSERVATIVE_RASTER_ډېرپېښ_NV    0x954D
#تعریف_کړه GL_CONSERVATIVE_RASTER_ډېرپېښ_POST_SNAP_NV 0x954E
#تعریف_کړه GL_CONSERVATIVE_RASTER_ډېرپېښ_PRE_SNAP_TRIANGLES_NV 0x954F
تعريفنوع فراغ (GL_APIENTRYP PFNGLCONSERVATIVERASTERPARAMETERINVPROC) (GLenum pname, GLint param);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glConservativeRasterParameteriNV (GLenum pname, GLint param);
#د_که_پای
#د_که_پای /* GL_NV_conservative_raster_pre_snap_triangles */

#که_نه_تعریف_شوی GL_NV_copy_بفر
#تعریف_کړه GL_NV_copy_بفر 1
#تعریف_کړه GL_COPY_READ_بفر_NV            0x8F36
#تعریف_کړه GL_COPY_WRITE_بفر_NV           0x8F37
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYBUFFERSUBDATANVPROC) (GLenum read_موخه, GLenum write_موخه, GLintptr read_دننه_واټن, GLintptr write_دننه_واټن, GLsizeiptr اندازه);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Copy_بفر_Sub_معلومات_NV (GLenum read_موخه, GLenum write_موخه, GLintptr read_دننه_واټن, GLintptr write_دننه_واټن, GLsizeiptr اندازه);
#د_که_پای
#د_که_پای /* GL_NV_copy_buffer */

#که_نه_تعریف_شوی GL_NV_coverage_sample
#تعریف_کړه GL_NV_coverage_sample 1
#تعریف_کړه GL_COVERAGE_COMPONENT_NV          0x8ED0
#تعریف_کړه GL_COVERAGE_COMPONENT4_NV         0x8ED1
#تعریف_کړه GL_COVERAGE_ATTACHMENT_NV         0x8ED2
#تعریف_کړه GL_COVERAGE_BUFFERS_NV            0x8ED3
#تعریف_کړه GL_COVERAGE_SAMPLES_NV            0x8ED4
#تعریف_کړه GL_COVERAGE_ALL_FRAGMENTS_NV      0x8ED5
#تعریف_کړه GL_COVERAGE_څنډه_FRAGMENTS_NV     0x8ED6
#تعریف_کړه GL_COVERAGE_AUTOMATIC_NV          0x8ED7
#تعریف_کړه GL_COVERAGE_بفر_بټ_NV         0x00008000
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOVERAGEMASKNVPROC) (GLboolean ماسک);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOVERAGEOPERATIONNVPROC) (GLenum operation);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Coverage_ماسک_NV (GLboolean ماسک);
GL_APICALL فراغ GL_APIENTRY glCoverageOperationNV (GLenum operation);
#د_که_پای
#د_که_پای /* GL_NV_coverage_sample */

#که_نه_تعریف_شوی GL_NV_ژوروالی_nonlinear
#تعریف_کړه GL_NV_ژوروالی_nonlinear 1
#تعریف_کړه GL_ژوروالی_COMPONENT16_NONLINEAR_NV 0x8E2C
#د_که_پای /* GL_NV_depth_nonlinear */

#که_نه_تعریف_شوی GL_NV_draw_buffers
#تعریف_کړه GL_NV_draw_buffers 1
#تعریف_کړه GL_MAX_DRAW_BUFFERS_NV            0x8824
#تعریف_کړه GL_DRAW_BUFFER0_NV                0x8825
#تعریف_کړه GL_DRAW_BUFFER1_NV                0x8826
#تعریف_کړه GL_DRAW_BUFFER2_NV                0x8827
#تعریف_کړه GL_DRAW_BUFFER3_NV                0x8828
#تعریف_کړه GL_DRAW_BUFFER4_NV                0x8829
#تعریف_کړه GL_DRAW_BUFFER5_NV                0x882A
#تعریف_کړه GL_DRAW_BUFFER6_NV                0x882B
#تعریف_کړه GL_DRAW_BUFFER7_NV                0x882C
#تعریف_کړه GL_DRAW_BUFFER8_NV                0x882D
#تعریف_کړه GL_DRAW_BUFFER9_NV                0x882E
#تعریف_کړه GL_DRAW_BUFFER10_NV               0x882F
#تعریف_کړه GL_DRAW_BUFFER11_NV               0x8830
#تعریف_کړه GL_DRAW_BUFFER12_NV               0x8831
#تعریف_کړه GL_DRAW_BUFFER13_NV               0x8832
#تعریف_کړه GL_DRAW_BUFFER14_NV               0x8833
#تعریف_کړه GL_DRAW_BUFFER15_NV               0x8834
#تعریف_کړه GL_COLOR_ATTACHMENT0_NV           0x8CE0
#تعریف_کړه GL_COLOR_ATTACHMENT1_NV           0x8CE1
#تعریف_کړه GL_COLOR_ATTACHMENT2_NV           0x8CE2
#تعریف_کړه GL_COLOR_ATTACHMENT3_NV           0x8CE3
#تعریف_کړه GL_COLOR_ATTACHMENT4_NV           0x8CE4
#تعریف_کړه GL_COLOR_ATTACHMENT5_NV           0x8CE5
#تعریف_کړه GL_COLOR_ATTACHMENT6_NV           0x8CE6
#تعریف_کړه GL_COLOR_ATTACHMENT7_NV           0x8CE7
#تعریف_کړه GL_COLOR_ATTACHMENT8_NV           0x8CE8
#تعریف_کړه GL_COLOR_ATTACHMENT9_NV           0x8CE9
#تعریف_کړه GL_COLOR_ATTACHMENT10_NV          0x8CEA
#تعریف_کړه GL_COLOR_ATTACHMENT11_NV          0x8CEB
#تعریف_کړه GL_COLOR_ATTACHMENT12_NV          0x8CEC
#تعریف_کړه GL_COLOR_ATTACHMENT13_NV          0x8CED
#تعریف_کړه GL_COLOR_ATTACHMENT14_NV          0x8CEE
#تعریف_کړه GL_COLOR_ATTACHMENT15_NV          0x8CEF
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWBUFFERSNVPROC) (GLsizei n, ثابت GLenum *bufs);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawBuffersNV (GLsizei n, ثابت GLenum *bufs);
#د_که_پای
#د_که_پای /* GL_NV_draw_buffers */

#که_نه_تعریف_شوی GL_NV_draw_instanced
#تعریف_کړه GL_NV_draw_instanced 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDNVPROC) (GLenum ډېرپېښ, GLint لومړی, GLsizei شمېر, GLsizei primcount);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDNVPROC) (GLenum ډېرپېښ, GLsizei شمېر, GLenum type, ثابت فراغ *indices, GLsizei primcount);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawArraysInstancedNV (GLenum ډېرپېښ, GLint لومړی, GLsizei شمېر, GLsizei primcount);
GL_APICALL فراغ GL_APIENTRY glDrawElementsInstancedNV (GLenum ډېرپېښ, GLsizei شمېر, GLenum type, ثابت فراغ *indices, GLsizei primcount);
#د_که_پای
#د_که_پای /* GL_NV_draw_instanced */

#که_نه_تعریف_شوی GL_NV_draw_vulkan_image
#تعریف_کړه GL_NV_draw_vulkan_image 1
تعريفنوع فراغ (GL_APIENTRY  *GLVULKANPROCNV)(فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWVKIMAGENVPROC) (GLuint64 vkImage, GLuint sampler, GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat z, GLfloat s0, GLfloat t0, GLfloat s1, GLfloat t1);
تعريفنوع GLVULKANPROCNV (GL_APIENTRYP PFNGLGETVKPROCADDRNVPROC) (ثابت GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLWAITVKSEMAPHORENVPROC) (GLuint64 vkSemaphore);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSIGNALVKSEMAPHORENVPROC) (GLuint64 vkSemaphore);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSIGNALVKFENCENVPROC) (GLuint64 vkFence);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawVkImageNV (GLuint64 vkImage, GLuint sampler, GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat z, GLfloat s0, GLfloat t0, GLfloat s1, GLfloat t1);
GL_APICALL GLVULKANPROCNV GL_APIENTRY glGetVkProcAddrNV (ثابت GLchar *name);
GL_APICALL فراغ GL_APIENTRY glWaitVkSemaphoreNV (GLuint64 vkSemaphore);
GL_APICALL فراغ GL_APIENTRY glSignalVkSemaphoreNV (GLuint64 vkSemaphore);
GL_APICALL فراغ GL_APIENTRY glSignalVkFenceNV (GLuint64 vkFence);
#د_که_پای
#د_که_پای /* GL_NV_draw_vulkan_image */

#که_نه_تعریف_شوی GL_NV_explicit_attrib_location
#تعریف_کړه GL_NV_explicit_attrib_location 1
#د_که_پای /* GL_NV_explicit_attrib_location */

#که_نه_تعریف_شوی GL_NV_fbo_color_attachments
#تعریف_کړه GL_NV_fbo_color_attachments 1
#تعریف_کړه GL_MAX_COLOR_ATTACHMENTS_NV       0x8CDF
#د_که_پای /* GL_NV_fbo_color_attachments */

#که_نه_تعریف_شوی GL_NV_fence
#تعریف_کړه GL_NV_fence 1
#تعریف_کړه GL_ALL_COMPLETED_NV               0x84F2
#تعریف_کړه GL_FENCE_حالت_NV                0x84F3
#تعریف_کړه GL_FENCE_CONDITION_NV             0x84F4
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEFENCESNVPROC) (GLsizei n, ثابت GLuint *fences);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENFENCESNVPROC) (GLsizei n, GLuint *fences);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISFENCENVPROC) (GLuint fence);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLTESTFENCENVPROC) (GLuint fence);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFENCEIVNVPROC) (GLuint fence, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFINISHFENCENVPROC) (GLuint fence);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSETFENCENVPROC) (GLuint fence, GLenum condition);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDeleteFencesNV (GLsizei n, ثابت GLuint *fences);
GL_APICALL فراغ GL_APIENTRY glGenFencesNV (GLsizei n, GLuint *fences);
GL_APICALL GLboolean GL_APIENTRY glIsFenceNV (GLuint fence);
GL_APICALL GLboolean GL_APIENTRY glTestFenceNV (GLuint fence);
GL_APICALL فراغ GL_APIENTRY glGetFenceivNV (GLuint fence, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY gl_پای_Fence_NV (GLuint fence);
GL_APICALL فراغ GL_APIENTRY gl_سېټ_Fence_NV (GLuint fence, GLenum condition);
#د_که_پای
#د_که_پای /* GL_NV_fence */

#که_نه_تعریف_شوی GL_NV_fill_rectangle
#تعریف_کړه GL_NV_fill_rectangle 1
#تعریف_کړه GL_FILL_RECTANGLE_NV              0x933C
#د_که_پای /* GL_NV_fill_rectangle */

#که_نه_تعریف_شوی GL_NV_fragment_coverage_منزل_color
#تعریف_کړه GL_NV_fragment_coverage_منزل_color 1
#تعریف_کړه GL_FRAGMENT_COVERAGE_منزل_COLOR_NV  0x92DD
#تعریف_کړه GL_FRAGMENT_COVERAGE_COLOR_NV     0x92DE
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAGMENTCOVERAGECOLORNVPROC) (GLuint color);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFragmentCoverageColorNV (GLuint color);
#د_که_پای
#د_که_پای /* GL_NV_fragment_coverage_to_color */

#که_نه_تعریف_شوی GL_NV_fragment_shader_barycentric
#تعریف_کړه GL_NV_fragment_shader_barycentric 1
#د_که_پای /* GL_NV_fragment_shader_barycentric */

#که_نه_تعریف_شوی GL_NV_fragment_shader_interlock
#تعریف_کړه GL_NV_fragment_shader_interlock 1
#د_که_پای /* GL_NV_fragment_shader_interlock */

#که_نه_تعریف_شوی GL_NV_framebuffer_blit
#تعریف_کړه GL_NV_framebuffer_blit 1
#تعریف_کړه GL_READ_FRAMEBUFFER_NV            0x8CA8
#تعریف_کړه GL_DRAW_FRAMEBUFFER_NV            0x8CA9
#تعریف_کړه GL_DRAW_FRAMEBUFFER_BINDING_NV    0x8CA6
#تعریف_کړه GL_READ_FRAMEBUFFER_BINDING_NV    0x8CAA
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLITFRAMEBUFFERNVPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield ماسک, GLenum filter);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glBlitFramebufferNV (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield ماسک, GLenum filter);
#د_که_پای
#د_که_پای /* GL_NV_framebuffer_blit */

#که_نه_تعریف_شوی GL_NV_framebuffer_mixed_samples
#تعریف_کړه GL_NV_framebuffer_mixed_samples 1
#تعریف_کړه GL_COVERAGE_MODULATION_جدول_NV   0x9331
#تعریف_کړه GL_COLOR_SAMPLES_NV               0x8E20
#تعریف_کړه GL_ژوروالی_SAMPLES_NV               0x932D
#تعریف_کړه GL_STENCIL_SAMPLES_NV             0x932E
#تعریف_کړه GL_MIXED_ژوروالی_SAMPLES_SUPPORTED_NV 0x932F
#تعریف_کړه GL_MIXED_STENCIL_SAMPLES_SUPPORTED_NV 0x9330
#تعریف_کړه GL_COVERAGE_MODULATION_NV         0x9332
#تعریف_کړه GL_COVERAGE_MODULATION_جدول_اندازه_NV 0x9333
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOVERAGEMODULATIONTABLENVPROC) (GLsizei n, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETCOVERAGEMODULATIONTABLENVPROC) (GLsizei buf_اندازه, GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOVERAGEMODULATIONNVPROC) (GLenum components);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Coverage_Modulation_جدول_NV (GLsizei n, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY gl_Get_Coverage_Modulation_جدول_NV (GLsizei buf_اندازه, GLfloat *v);
GL_APICALL فراغ GL_APIENTRY glCoverageModulationNV (GLenum components);
#د_که_پای
#د_که_پای /* GL_NV_framebuffer_mixed_samples */

#که_نه_تعریف_شوی GL_NV_framebuffer_multisample
#تعریف_کړه GL_NV_framebuffer_multisample 1
#تعریف_کړه GL_RENDERBUFFER_SAMPLES_NV        0x8CAB
#تعریف_کړه GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_NV 0x8D56
#تعریف_کړه GL_MAX_SAMPLES_NV                 0x8D57
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLENVPROC) (GLenum موخه, GLsizei samples, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glRenderbufferStorageMultisampleNV (GLenum موخه, GLsizei samples, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
#د_که_پای
#د_که_پای /* GL_NV_framebuffer_multisample */

#که_نه_تعریف_شوی GL_NV_generate_mipmap_sRGB
#تعریف_کړه GL_NV_generate_mipmap_sRGB 1
#د_که_پای /* GL_NV_generate_mipmap_sRGB */

#که_نه_تعریف_شوی GL_NV_geometry_shader_passthrough
#تعریف_کړه GL_NV_geometry_shader_passthrough 1
#د_که_پای /* GL_NV_geometry_shader_passthrough */

#که_نه_تعریف_شوی GL_NV_gpu_shader5
#تعریف_کړه GL_NV_gpu_shader5 1
تعريفنوع khronos_int64_t GLint64EXT;
تعريفنوع khronos_uint64_t GLuint64EXT;
#تعریف_کړه GL_INT64_NV                       0x140E
#تعریف_کړه GL_UNSIGNED_INT64_NV              0x140F
#تعریف_کړه GL_INT8_NV                        0x8FE0
#تعریف_کړه GL_INT8_VEC2_NV                   0x8FE1
#تعریف_کړه GL_INT8_VEC3_NV                   0x8FE2
#تعریف_کړه GL_INT8_VEC4_NV                   0x8FE3
#تعریف_کړه GL_INT16_NV                       0x8FE4
#تعریف_کړه GL_INT16_VEC2_NV                  0x8FE5
#تعریف_کړه GL_INT16_VEC3_NV                  0x8FE6
#تعریف_کړه GL_INT16_VEC4_NV                  0x8FE7
#تعریف_کړه GL_INT64_VEC2_NV                  0x8FE9
#تعریف_کړه GL_INT64_VEC3_NV                  0x8FEA
#تعریف_کړه GL_INT64_VEC4_NV                  0x8FEB
#تعریف_کړه GL_UNSIGNED_INT8_NV               0x8FEC
#تعریف_کړه GL_UNSIGNED_INT8_VEC2_NV          0x8FED
#تعریف_کړه GL_UNSIGNED_INT8_VEC3_NV          0x8FEE
#تعریف_کړه GL_UNSIGNED_INT8_VEC4_NV          0x8FEF
#تعریف_کړه GL_UNSIGNED_INT16_NV              0x8FF0
#تعریف_کړه GL_UNSIGNED_INT16_VEC2_NV         0x8FF1
#تعریف_کړه GL_UNSIGNED_INT16_VEC3_NV         0x8FF2
#تعریف_کړه GL_UNSIGNED_INT16_VEC4_NV         0x8FF3
#تعریف_کړه GL_UNSIGNED_INT64_VEC2_NV         0x8FF5
#تعریف_کړه GL_UNSIGNED_INT64_VEC3_NV         0x8FF6
#تعریف_کړه GL_UNSIGNED_INT64_VEC4_NV         0x8FF7
#تعریف_کړه GL_FLOAT16_NV                     0x8FF8
#تعریف_کړه GL_FLOAT16_VEC2_NV                0x8FF9
#تعریف_کړه GL_FLOAT16_VEC3_NV                0x8FFA
#تعریف_کړه GL_FLOAT16_VEC4_NV                0x8FFB
#تعریف_کړه GL_PATCHES                        0x000E
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1I64NVPROC) (GLint location, GLint64EXT x);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2I64NVPROC) (GLint location, GLint64EXT x, GLint64EXT y);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3I64NVPROC) (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4I64NVPROC) (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1I64VNVPROC) (GLint location, GLsizei شمېر, ثابت GLint64EXT *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2I64VNVPROC) (GLint location, GLsizei شمېر, ثابت GLint64EXT *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3I64VNVPROC) (GLint location, GLsizei شمېر, ثابت GLint64EXT *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4I64VNVPROC) (GLint location, GLsizei شمېر, ثابت GLint64EXT *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1UI64NVPROC) (GLint location, GLuint64EXT x);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2UI64NVPROC) (GLint location, GLuint64EXT x, GLuint64EXT y);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3UI64NVPROC) (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4UI64NVPROC) (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1UI64VNVPROC) (GLint location, GLsizei شمېر, ثابت GLuint64EXT *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2UI64VNVPROC) (GLint location, GLsizei شمېر, ثابت GLuint64EXT *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3UI64VNVPROC) (GLint location, GLsizei شمېر, ثابت GLuint64EXT *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4UI64VNVPROC) (GLint location, GLsizei شمېر, ثابت GLuint64EXT *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETUNIFORMI64VNVPROC) (GLuint پروګرام, GLint location, GLint64EXT *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1I64NVPROC) (GLuint پروګرام, GLint location, GLint64EXT x);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2I64NVPROC) (GLuint پروګرام, GLint location, GLint64EXT x, GLint64EXT y);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3I64NVPROC) (GLuint پروګرام, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4I64NVPROC) (GLuint پروګرام, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1I64VNVPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLint64EXT *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2I64VNVPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLint64EXT *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3I64VNVPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLint64EXT *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4I64VNVPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLint64EXT *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UI64NVPROC) (GLuint پروګرام, GLint location, GLuint64EXT x);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UI64NVPROC) (GLuint پروګرام, GLint location, GLuint64EXT x, GLuint64EXT y);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UI64NVPROC) (GLuint پروګرام, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UI64NVPROC) (GLuint پروګرام, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UI64VNVPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLuint64EXT *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UI64VNVPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLuint64EXT *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UI64VNVPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLuint64EXT *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UI64VNVPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLuint64EXT *ارزښت);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glUniform1i64NV (GLint location, GLint64EXT x);
GL_APICALL فراغ GL_APIENTRY glUniform2i64NV (GLint location, GLint64EXT x, GLint64EXT y);
GL_APICALL فراغ GL_APIENTRY glUniform3i64NV (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
GL_APICALL فراغ GL_APIENTRY glUniform4i64NV (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
GL_APICALL فراغ GL_APIENTRY glUniform1i64vNV (GLint location, GLsizei شمېر, ثابت GLint64EXT *ارزښت);
GL_APICALL فراغ GL_APIENTRY glUniform2i64vNV (GLint location, GLsizei شمېر, ثابت GLint64EXT *ارزښت);
GL_APICALL فراغ GL_APIENTRY glUniform3i64vNV (GLint location, GLsizei شمېر, ثابت GLint64EXT *ارزښت);
GL_APICALL فراغ GL_APIENTRY glUniform4i64vNV (GLint location, GLsizei شمېر, ثابت GLint64EXT *ارزښت);
GL_APICALL فراغ GL_APIENTRY glUniform1ui64NV (GLint location, GLuint64EXT x);
GL_APICALL فراغ GL_APIENTRY glUniform2ui64NV (GLint location, GLuint64EXT x, GLuint64EXT y);
GL_APICALL فراغ GL_APIENTRY glUniform3ui64NV (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
GL_APICALL فراغ GL_APIENTRY glUniform4ui64NV (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
GL_APICALL فراغ GL_APIENTRY glUniform1ui64vNV (GLint location, GLsizei شمېر, ثابت GLuint64EXT *ارزښت);
GL_APICALL فراغ GL_APIENTRY glUniform2ui64vNV (GLint location, GLsizei شمېر, ثابت GLuint64EXT *ارزښت);
GL_APICALL فراغ GL_APIENTRY glUniform3ui64vNV (GLint location, GLsizei شمېر, ثابت GLuint64EXT *ارزښت);
GL_APICALL فراغ GL_APIENTRY glUniform4ui64vNV (GLint location, GLsizei شمېر, ثابت GLuint64EXT *ارزښت);
GL_APICALL فراغ GL_APIENTRY glGetUniformi64vNV (GLuint پروګرام, GLint location, GLint64EXT *params);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform1i64_NV (GLuint پروګرام, GLint location, GLint64EXT x);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform2i64_NV (GLuint پروګرام, GLint location, GLint64EXT x, GLint64EXT y);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform3i64_NV (GLuint پروګرام, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform4i64_NV (GLuint پروګرام, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform1i64v_NV (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLint64EXT *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform2i64v_NV (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLint64EXT *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform3i64v_NV (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLint64EXT *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform4i64v_NV (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLint64EXT *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform1ui64_NV (GLuint پروګرام, GLint location, GLuint64EXT x);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform2ui64_NV (GLuint پروګرام, GLint location, GLuint64EXT x, GLuint64EXT y);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform3ui64_NV (GLuint پروګرام, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform4ui64_NV (GLuint پروګرام, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform1ui64v_NV (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLuint64EXT *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform2ui64v_NV (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLuint64EXT *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform3ui64v_NV (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLuint64EXT *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform4ui64v_NV (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLuint64EXT *ارزښت);
#د_که_پای
#د_که_پای /* GL_NV_gpu_shader5 */

#که_نه_تعریف_شوی GL_NV_image_formats
#تعریف_کړه GL_NV_image_formats 1
#د_که_پای /* GL_NV_image_formats */

#که_نه_تعریف_شوی GL_NV_instanced_arrays
#تعریف_کړه GL_NV_instanced_arrays 1
#تعریف_کړه GL_راس_ATTRIB_ARRAY_وېشونکی_NV 0x88FE
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBDIVISORNVPROC) (GLuint شاخص, GLuint وېشونکی);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib_وېشونکی_NV (GLuint شاخص, GLuint وېشونکی);
#د_که_پای
#د_که_پای /* GL_NV_instanced_arrays */

#که_نه_تعریف_شوی GL_NV_internalformat_sample_query
#تعریف_کړه GL_NV_internalformat_sample_query 1
#تعریف_کړه GL_TEXTURE_2D_MULTISAMPLE         0x9100
#تعریف_کړه GL_TEXTURE_2D_MULTISAMPLE_ARRAY   0x9102
#تعریف_کړه GL_MULTISAMPLES_NV                0x9371
#تعریف_کړه GL_SUPERSAMPLE_SCALE_X_NV         0x9372
#تعریف_کړه GL_SUPERSAMPLE_SCALE_Y_NV         0x9373
#تعریف_کړه GL_CONFORMANT_NV                  0x9374
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTERNALFORMATSAMPLEIVNVPROC) (GLenum موخه, GLenum internalformat, GLsizei samples, GLenum pname, GLsizei شمېر, GLint *params);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glGetInternalformatSampleivNV (GLenum موخه, GLenum internalformat, GLsizei samples, GLenum pname, GLsizei شمېر, GLint *params);
#د_که_پای
#د_که_پای /* GL_NV_internalformat_sample_query */

#که_نه_تعریف_شوی GL_NV_حافظه_attachment
#تعریف_کړه GL_NV_حافظه_attachment 1
#تعریف_کړه GL_ATTACHED_حافظه_OBJECT_NV      0x95A4
#تعریف_کړه GL_ATTACHED_حافظه_دننه_واټن_NV      0x95A5
#تعریف_کړه GL_حافظه_ATTACHABLE_ALIGNMENT_NV 0x95A6
#تعریف_کړه GL_حافظه_ATTACHABLE_اندازه_NV      0x95A7
#تعریف_کړه GL_حافظه_ATTACHABLE_NV           0x95A8
#تعریف_کړه GL_DETACHED_حافظه_INCARNATION_NV 0x95A9
#تعریف_کړه GL_DETACHED_TEXTURES_NV           0x95AA
#تعریف_کړه GL_DETACHED_BUFFERS_NV            0x95AB
#تعریف_کړه GL_MAX_DETACHED_TEXTURES_NV       0x95AC
#تعریف_کړه GL_MAX_DETACHED_BUFFERS_NV        0x95AD
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETMEMORYOBJECTDETACHEDRESOURCESUIVNVPROC) (GLuint حافظه, GLenum pname, GLint لومړی, GLsizei شمېر, GLuint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRESETMEMORYOBJECTPARAMETERNVPROC) (GLuint حافظه, GLenum pname);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXATTACHMEMORYNVPROC) (GLenum موخه, GLuint حافظه, GLuint64 دننه_واټن_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBUFFERATTACHMEMORYNVPROC) (GLenum موخه, GLuint حافظه, GLuint64 دننه_واټن_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTUREATTACHMEMORYNVPROC) (GLuint texture, GLuint حافظه, GLuint64 دننه_واټن_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLNAMEDBUFFERATTACHMEMORYNVPROC) (GLuint بفر_2, GLuint حافظه, GLuint64 دننه_واټن_2);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Get_حافظه_Object_Detached_Resourcesuiv_NV (GLuint حافظه, GLenum pname, GLint لومړی, GLsizei شمېر, GLuint *params);
GL_APICALL فراغ GL_APIENTRY gl_Reset_حافظه_Object_Parameter_NV (GLuint حافظه, GLenum pname);
GL_APICALL فراغ GL_APIENTRY gl_Tex_Attach_حافظه_NV (GLenum موخه, GLuint حافظه, GLuint64 دننه_واټن_2);
GL_APICALL فراغ GL_APIENTRY gl_بفر_Attach_حافظه_NV (GLenum موخه, GLuint حافظه, GLuint64 دننه_واټن_2);
GL_APICALL فراغ GL_APIENTRY gl_Texture_Attach_حافظه_NV (GLuint texture, GLuint حافظه, GLuint64 دننه_واټن_2);
GL_APICALL فراغ GL_APIENTRY gl_Named_بفر_Attach_حافظه_NV (GLuint بفر_2, GLuint حافظه, GLuint64 دننه_واټن_2);
#د_که_پای
#د_که_پای /* GL_NV_memory_attachment */

#که_نه_تعریف_شوی GL_NV_حافظه_object_sparse
#تعریف_کړه GL_NV_حافظه_object_sparse 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLBUFFERPAGECOMMITMENTMEMNVPROC) (GLenum موخه, GLintptr دننه_واټن_2, GLsizeiptr اندازه, GLuint حافظه, GLuint64 mem_دننه_واټن, GLboolean commit);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPAGECOMMITMENTMEMNVPROC) (GLenum موخه, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLuint حافظه, GLuint64 دننه_واټن_2, GLboolean commit);
تعريفنوع فراغ (GL_APIENTRYP PFNGLNAMEDBUFFERPAGECOMMITMENTMEMNVPROC) (GLuint بفر_2, GLintptr دننه_واټن_2, GLsizeiptr اندازه, GLuint حافظه, GLuint64 mem_دننه_واټن, GLboolean commit);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTUREPAGECOMMITMENTMEMNVPROC) (GLuint texture, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLuint حافظه, GLuint64 دننه_واټن_2, GLboolean commit);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_بفر_پاڼه_Commitment_Mem_NV (GLenum موخه, GLintptr دننه_واټن_2, GLsizeiptr اندازه, GLuint حافظه, GLuint64 mem_دننه_واټن, GLboolean commit);
GL_APICALL فراغ GL_APIENTRY gl_Tex_پاڼه_Commitment_Mem_NV (GLenum موخه, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLuint حافظه, GLuint64 دننه_واټن_2, GLboolean commit);
GL_APICALL فراغ GL_APIENTRY gl_Named_بفر_پاڼه_Commitment_Mem_NV (GLuint بفر_2, GLintptr دننه_واټن_2, GLsizeiptr اندازه, GLuint حافظه, GLuint64 mem_دننه_واټن, GLboolean commit);
GL_APICALL فراغ GL_APIENTRY gl_Texture_پاڼه_Commitment_Mem_NV (GLuint texture, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLuint حافظه, GLuint64 دننه_واټن_2, GLboolean commit);
#د_که_پای
#د_که_پای /* GL_NV_memory_object_sparse */

#که_نه_تعریف_شوی GL_NV_mesh_shader
#تعریف_کړه GL_NV_mesh_shader 1
#تعریف_کړه GL_MESH_SHADER_NV                 0x9559
#تعریف_کړه GL_TASK_SHADER_NV                 0x955A
#تعریف_کړه GL_MAX_MESH_یوشان_بلاکونه_NV     0x8E60
#تعریف_کړه GL_MAX_MESH_TEXTURE_IMAGE_UNITS_NV 0x8E61
#تعریف_کړه GL_MAX_MESH_IMAGE_UNIFORMS_NV     0x8E62
#تعریف_کړه GL_MAX_MESH_یوشان_COMPONENTS_NV 0x8E63
#تعریف_کړه GL_MAX_MESH_ATOMIC_COUNTER_BUFFERS_NV 0x8E64
#تعریف_کړه GL_MAX_MESH_ATOMIC_COUNTERS_NV    0x8E65
#تعریف_کړه GL_MAX_MESH_SHADER_STORAGE_بلاکونه_NV 0x8E66
#تعریف_کړه GL_MAX_COMBINED_MESH_یوشان_COMPONENTS_NV 0x8E67
#تعریف_کړه GL_MAX_TASK_یوشان_بلاکونه_NV     0x8E68
#تعریف_کړه GL_MAX_TASK_TEXTURE_IMAGE_UNITS_NV 0x8E69
#تعریف_کړه GL_MAX_TASK_IMAGE_UNIFORMS_NV     0x8E6A
#تعریف_کړه GL_MAX_TASK_یوشان_COMPONENTS_NV 0x8E6B
#تعریف_کړه GL_MAX_TASK_ATOMIC_COUNTER_BUFFERS_NV 0x8E6C
#تعریف_کړه GL_MAX_TASK_ATOMIC_COUNTERS_NV    0x8E6D
#تعریف_کړه GL_MAX_TASK_SHADER_STORAGE_بلاکونه_NV 0x8E6E
#تعریف_کړه GL_MAX_COMBINED_TASK_یوشان_COMPONENTS_NV 0x8E6F
#تعریف_کړه GL_MAX_MESH_WORK_ډله_INVOCATIONS_NV 0x95A2
#تعریف_کړه GL_MAX_TASK_WORK_ډله_INVOCATIONS_NV 0x95A3
#تعریف_کړه GL_MAX_MESH_ټول_حافظه_اندازه_NV  0x9536
#تعریف_کړه GL_MAX_TASK_ټول_حافظه_اندازه_NV  0x9537
#تعریف_کړه GL_MAX_MESH_OUTPUT_VERTICES_NV    0x9538
#تعریف_کړه GL_MAX_MESH_OUTPUT_PRIMITIVES_NV  0x9539
#تعریف_کړه GL_MAX_TASK_OUTPUT_شمېر_NV       0x953A
#تعریف_کړه GL_MAX_DRAW_MESH_TASKS_شمېر_NV   0x953D
#تعریف_کړه GL_MAX_MESH_VIEWS_NV              0x9557
#تعریف_کړه GL_MESH_OUTPUT_فی_راس_GRANULARITY_NV 0x92DF
#تعریف_کړه GL_MESH_OUTPUT_فی_PRIMITIVE_GRANULARITY_NV 0x9543
#تعریف_کړه GL_MAX_MESH_WORK_ډله_اندازه_NV    0x953B
#تعریف_کړه GL_MAX_TASK_WORK_ډله_اندازه_NV    0x953C
#تعریف_کړه GL_MESH_WORK_ډله_اندازه_NV        0x953E
#تعریف_کړه GL_TASK_WORK_ډله_اندازه_NV        0x953F
#تعریف_کړه GL_MESH_VERTICES_بهر_NV           0x9579
#تعریف_کړه GL_MESH_PRIMITIVES_بهر_NV         0x957A
#تعریف_کړه GL_MESH_OUTPUT_TYPE_NV            0x957B
#تعریف_کړه GL_یوشان_بلاک_REFERENCED_BY_MESH_SHADER_NV 0x959C
#تعریف_کړه GL_یوشان_بلاک_REFERENCED_BY_TASK_SHADER_NV 0x959D
#تعریف_کړه GL_REFERENCED_BY_MESH_SHADER_NV   0x95A0
#تعریف_کړه GL_REFERENCED_BY_TASK_SHADER_NV   0x95A1
#تعریف_کړه GL_MESH_SHADER_بټ_NV             0x00000040
#تعریف_کړه GL_TASK_SHADER_بټ_NV             0x00000080
#تعریف_کړه GL_MESH_SUBROUTINE_NV             0x957C
#تعریف_کړه GL_TASK_SUBROUTINE_NV             0x957D
#تعریف_کړه GL_MESH_SUBROUTINE_یوشان_NV     0x957E
#تعریف_کړه GL_TASK_SUBROUTINE_یوشان_NV     0x957F
#تعریف_کړه GL_ATOMIC_COUNTER_بفر_REFERENCED_BY_MESH_SHADER_NV 0x959E
#تعریف_کړه GL_ATOMIC_COUNTER_بفر_REFERENCED_BY_TASK_SHADER_NV 0x959F
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWMESHTASKSNVPROC) (GLuint لومړی, GLuint شمېر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWMESHTASKSINDIRECTNVPROC) (GLintptr غیرمستقیم);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWMESHTASKSINDIRECTNVPROC) (GLintptr غیرمستقیم, GLsizei drawcount, GLsizei stride);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTNVPROC) (GLintptr غیرمستقیم, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawMeshTasksNV (GLuint لومړی, GLuint شمېر);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Mesh_Tasks_غیرمستقیم_NV (GLintptr غیرمستقیم);
GL_APICALL فراغ GL_APIENTRY gl_Multi_Draw_Mesh_Tasks_غیرمستقیم_NV (GLintptr غیرمستقیم, GLsizei drawcount, GLsizei stride);
GL_APICALL فراغ GL_APIENTRY gl_Multi_Draw_Mesh_Tasks_غیرمستقیم_شمېر_NV (GLintptr غیرمستقیم, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
#د_که_پای
#د_که_پای /* GL_NV_mesh_shader */

#که_نه_تعریف_شوی GL_NV_non_مربع_matrices
#تعریف_کړه GL_NV_non_مربع_matrices 1
#تعریف_کړه GL_FLOAT_MAT2x3_NV                0x8B65
#تعریف_کړه GL_FLOAT_MAT2x4_NV                0x8B66
#تعریف_کړه GL_FLOAT_MAT3x2_NV                0x8B67
#تعریف_کړه GL_FLOAT_MAT3x4_NV                0x8B68
#تعریف_کړه GL_FLOAT_MAT4x2_NV                0x8B69
#تعریف_کړه GL_FLOAT_MAT4x3_NV                0x8B6A
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX2X3FVNVPROC) (GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX3X2FVNVPROC) (GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX2X4FVNVPROC) (GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX4X2FVNVPROC) (GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX3X4FVNVPROC) (GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX4X3FVNVPROC) (GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_یوشان_Matrix2x3fv_NV (GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_یوشان_Matrix3x2fv_NV (GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_یوشان_Matrix2x4fv_NV (GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_یوشان_Matrix4x2fv_NV (GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_یوشان_Matrix3x4fv_NV (GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_یوشان_Matrix4x3fv_NV (GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
#د_که_پای
#د_که_پای /* GL_NV_non_square_matrices */

#که_نه_تعریف_شوی GL_NV_pack_subimage
#تعریف_کړه GL_NV_pack_subimage 1
#تعریف_کړه GL_PACK_لیکه_اوږدتیا_NV             0x0D02
#تعریف_کړه GL_PACK_SKIP_لیکې_NV              0x0D03
#تعریف_کړه GL_PACK_SKIP_PIXELS_NV            0x0D04
#د_که_پای /* GL_NV_pack_subimage */

#که_نه_تعریف_شوی GL_NV_لار_rendering
#تعریف_کړه GL_NV_لار_rendering 1
تعريفنوع مزدوج GLdouble;
#تعریف_کړه GL_لار_FORMAT_SVG_NV             0x9070
#تعریف_کړه GL_لار_FORMAT_PS_NV              0x9071
#تعریف_کړه GL_STANDARD_FONT_NAME_NV          0x9072
#تعریف_کړه GL_SYSTEM_FONT_NAME_NV            0x9073
#تعریف_کړه GL_FILE_NAME_NV                   0x9074
#تعریف_کړه GL_لار_STROKE_پلنوالی_NV           0x9075
#تعریف_کړه GL_لار_پای_ټکی_CAPS_NV               0x9076
#تعریف_کړه GL_لار_INITIAL_پای_ټکی_CAP_NV        0x9077
#تعریف_کړه GL_لار_TERMINAL_پای_ټکی_CAP_NV       0x9078
#تعریف_کړه GL_لار_JOIN_STYLE_NV             0x9079
#تعریف_کړه GL_لار_MITER_حد_NV            0x907A
#تعریف_کړه GL_لار_DASH_CAPS_NV              0x907B
#تعریف_کړه GL_لار_INITIAL_DASH_CAP_NV       0x907C
#تعریف_کړه GL_لار_TERMINAL_DASH_CAP_NV      0x907D
#تعریف_کړه GL_لار_DASH_دننه_واټن_NV            0x907E
#تعریف_کړه GL_لار_CLIENT_اوږدتیا_NV          0x907F
#تعریف_کړه GL_لار_FILL_ډېرپېښ_NV              0x9080
#تعریف_کړه GL_لار_FILL_ماسک_NV              0x9081
#تعریف_کړه GL_لار_FILL_COVER_ډېرپېښ_NV        0x9082
#تعریف_کړه GL_لار_STROKE_COVER_ډېرپېښ_NV      0x9083
#تعریف_کړه GL_لار_STROKE_ماسک_NV            0x9084
#تعریف_کړه GL_شمېر_پورته_NV                    0x9088
#تعریف_کړه GL_شمېر_ښکته_NV                  0x9089
#تعریف_کړه GL_لار_OBJECT_BOUNDING_BOX_NV    0x908A
#تعریف_کړه GL_CONVEX_HULL_NV                 0x908B
#تعریف_کړه GL_BOUNDING_BOX_NV                0x908D
#تعریف_کړه GL_TRANSLATE_X_NV                 0x908E
#تعریف_کړه GL_TRANSLATE_Y_NV                 0x908F
#تعریف_کړه GL_TRANSLATE_2D_NV                0x9090
#تعریف_کړه GL_TRANSLATE_3D_NV                0x9091
#تعریف_کړه GL_AFFINE_2D_NV                   0x9092
#تعریف_کړه GL_AFFINE_3D_NV                   0x9094
#تعریف_کړه GL_TRANSPOSE_AFFINE_2D_NV         0x9096
#تعریف_کړه GL_TRANSPOSE_AFFINE_3D_NV         0x9098
#تعریف_کړه GL_UTF8_NV                        0x909A
#تعریف_کړه GL_UTF16_NV                       0x909B
#تعریف_کړه GL_BOUNDING_BOX_د_BOUNDING_BOXES_NV 0x909C
#تعریف_کړه GL_لار_COMMAND_شمېر_NV          0x909D
#تعریف_کړه GL_لار_COORD_شمېر_NV            0x909E
#تعریف_کړه GL_لار_DASH_ARRAY_شمېر_NV       0x909F
#تعریف_کړه GL_لار_COMPUTED_اوږدتیا_NV        0x90A0
#تعریف_کړه GL_لار_FILL_BOUNDING_BOX_NV      0x90A1
#تعریف_کړه GL_لار_STROKE_BOUNDING_BOX_NV    0x90A2
#تعریف_کړه GL_مربع_NV                      0x90A3
#تعریف_کړه GL_پړاو_NV                       0x90A4
#تعریف_کړه GL_TRIANGULAR_NV                  0x90A5
#تعریف_کړه GL_BEVEL_NV                       0x90A6
#تعریف_کړه GL_MITER_REVERT_NV                0x90A7
#تعریف_کړه GL_MITER_TRUNCATE_NV              0x90A8
#تعریف_کړه GL_SKIP_MISSING_GLYPH_NV          0x90A9
#تعریف_کړه GL_USE_MISSING_GLYPH_NV           0x90AA
#تعریف_کړه GL_لار_ERROR_POSITION_NV         0x90AB
#تعریف_کړه GL_ACCUM_ADJACENT_جوړې_NV        0x90AD
#تعریف_کړه GL_ADJACENT_جوړې_NV              0x90AE
#تعریف_کړه GL_لومړی_منزل_REST_NV               0x90AF
#تعریف_کړه GL_لار_GEN_ډېرپېښ_NV               0x90B0
#تعریف_کړه GL_لار_GEN_COEFF_NV              0x90B1
#تعریف_کړه GL_لار_GEN_COMPONENTS_NV         0x90B3
#تعریف_کړه GL_لار_STENCIL_FUNC_NV           0x90B7
#تعریف_کړه GL_لار_STENCIL_REF_NV            0x90B8
#تعریف_کړه GL_لار_STENCIL_ارزښت_ماسک_NV     0x90B9
#تعریف_کړه GL_لار_STENCIL_ژوروالی_دننه_واټن_ضریب_NV 0x90BD
#تعریف_کړه GL_لار_STENCIL_ژوروالی_دننه_واټن_UNITS_NV 0x90BE
#تعریف_کړه GL_لار_COVER_ژوروالی_FUNC_NV       0x90BF
#تعریف_کړه GL_لار_DASH_دننه_واټن_RESET_NV      0x90B4
#تعریف_کړه GL_MOVE_منزل_RESETS_NV              0x90B5
#تعریف_کړه GL_MOVE_منزل_CONTINUES_NV           0x90B6
#تعریف_کړه GL_CLOSE_لار_NV                  0x00
#تعریف_کړه GL_MOVE_منزل_NV                     0x02
#تعریف_کړه GL_RELATIVE_MOVE_منزل_NV            0x03
#تعریف_کړه GL_کرښه_منزل_NV                     0x04
#تعریف_کړه GL_RELATIVE_کرښه_منزل_NV            0x05
#تعریف_کړه GL_HORIZONTAL_کرښه_منزل_NV          0x06
#تعریف_کړه GL_RELATIVE_HORIZONTAL_کرښه_منزل_NV 0x07
#تعریف_کړه GL_VERTICAL_کرښه_منزل_NV            0x08
#تعریف_کړه GL_RELATIVE_VERTICAL_کرښه_منزل_NV   0x09
#تعریف_کړه GL_QUADRATIC_منحني_منزل_NV          0x0A
#تعریف_کړه GL_RELATIVE_QUADRATIC_منحني_منزل_NV 0x0B
#تعریف_کړه GL_CUBIC_منحني_منزل_NV              0x0C
#تعریف_کړه GL_RELATIVE_CUBIC_منحني_منزل_NV     0x0D
#تعریف_کړه GL_SMOOTH_QUADRATIC_منحني_منزل_NV   0x0E
#تعریف_کړه GL_RELATIVE_SMOOTH_QUADRATIC_منحني_منزل_NV 0x0F
#تعریف_کړه GL_SMOOTH_CUBIC_منحني_منزل_NV       0x10
#تعریف_کړه GL_RELATIVE_SMOOTH_CUBIC_منحني_منزل_NV 0x11
#تعریف_کړه GL_SMALL_CCW_ARC_منزل_NV            0x12
#تعریف_کړه GL_RELATIVE_SMALL_CCW_ARC_منزل_NV   0x13
#تعریف_کړه GL_SMALL_CW_ARC_منزل_NV             0x14
#تعریف_کړه GL_RELATIVE_SMALL_CW_ARC_منزل_NV    0x15
#تعریف_کړه GL_LARGE_CCW_ARC_منزل_NV            0x16
#تعریف_کړه GL_RELATIVE_LARGE_CCW_ARC_منزل_NV   0x17
#تعریف_کړه GL_LARGE_CW_ARC_منزل_NV             0x18
#تعریف_کړه GL_RELATIVE_LARGE_CW_ARC_منزل_NV    0x19
#تعریف_کړه GL_RESTART_لار_NV                0xF0
#تعریف_کړه GL_DUP_لومړی_CUBIC_منحني_منزل_NV    0xF2
#تعریف_کړه GL_DUP_وروستی_CUBIC_منحني_منزل_NV     0xF4
#تعریف_کړه GL_RECT_NV                        0xF6
#تعریف_کړه GL_CIRCULAR_CCW_ARC_منزل_NV         0xF8
#تعریف_کړه GL_CIRCULAR_CW_ARC_منزل_NV          0xFA
#تعریف_کړه GL_CIRCULAR_TANGENT_ARC_منزل_NV     0xFC
#تعریف_کړه GL_ARC_منزل_NV                      0xFE
#تعریف_کړه GL_RELATIVE_ARC_منزل_NV             0xFF
#تعریف_کړه GL_BOLD_بټ_NV                    0x01
#تعریف_کړه GL_ITALIC_بټ_NV                  0x02
#تعریف_کړه GL_GLYPH_پلنوالی_بټ_NV             0x01
#تعریف_کړه GL_GLYPH_لوړوالی_بټ_NV            0x02
#تعریف_کړه GL_GLYPH_HORIZONTAL_BEARING_X_بټ_NV 0x04
#تعریف_کړه GL_GLYPH_HORIZONTAL_BEARING_Y_بټ_NV 0x08
#تعریف_کړه GL_GLYPH_HORIZONTAL_BEARING_ADVANCE_بټ_NV 0x10
#تعریف_کړه GL_GLYPH_VERTICAL_BEARING_X_بټ_NV 0x20
#تعریف_کړه GL_GLYPH_VERTICAL_BEARING_Y_بټ_NV 0x40
#تعریف_کړه GL_GLYPH_VERTICAL_BEARING_ADVANCE_بټ_NV 0x80
#تعریف_کړه GL_GLYPH_HAS_KERNING_بټ_NV       0x100
#تعریف_کړه GL_FONT_X_MIN_BOUNDS_بټ_NV       0x00010000
#تعریف_کړه GL_FONT_Y_MIN_BOUNDS_بټ_NV       0x00020000
#تعریف_کړه GL_FONT_X_MAX_BOUNDS_بټ_NV       0x00040000
#تعریف_کړه GL_FONT_Y_MAX_BOUNDS_بټ_NV       0x00080000
#تعریف_کړه GL_FONT_UNITS_فی_EM_بټ_NV       0x00100000
#تعریف_کړه GL_FONT_ASCENDER_بټ_NV           0x00200000
#تعریف_کړه GL_FONT_DESCENDER_بټ_NV          0x00400000
#تعریف_کړه GL_FONT_لوړوالی_بټ_NV             0x00800000
#تعریف_کړه GL_FONT_MAX_ADVANCE_پلنوالی_بټ_NV  0x01000000
#تعریف_کړه GL_FONT_MAX_ADVANCE_لوړوالی_بټ_NV 0x02000000
#تعریف_کړه GL_FONT_UNDERLINE_POSITION_بټ_NV 0x04000000
#تعریف_کړه GL_FONT_UNDERLINE_THICKNESS_بټ_NV 0x08000000
#تعریف_کړه GL_FONT_HAS_KERNING_بټ_NV        0x10000000
#تعریف_کړه GL_ROUNDED_RECT_NV                0xE8
#تعریف_کړه GL_RELATIVE_ROUNDED_RECT_NV       0xE9
#تعریف_کړه GL_ROUNDED_RECT2_NV               0xEA
#تعریف_کړه GL_RELATIVE_ROUNDED_RECT2_NV      0xEB
#تعریف_کړه GL_ROUNDED_RECT4_NV               0xEC
#تعریف_کړه GL_RELATIVE_ROUNDED_RECT4_NV      0xED
#تعریف_کړه GL_ROUNDED_RECT8_NV               0xEE
#تعریف_کړه GL_RELATIVE_ROUNDED_RECT8_NV      0xEF
#تعریف_کړه GL_RELATIVE_RECT_NV               0xF7
#تعریف_کړه GL_FONT_GLYPHS_شته_NV       0x9368
#تعریف_کړه GL_FONT_موخه_UNAVAILABLE_NV     0x9369
#تعریف_کړه GL_FONT_UNAVAILABLE_NV            0x936A
#تعریف_کړه GL_FONT_UNINTELLIGIBLE_NV         0x936B
#تعریف_کړه GL_CONIC_منحني_منزل_NV              0x1A
#تعریف_کړه GL_RELATIVE_CONIC_منحني_منزل_NV     0x1B
#تعریف_کړه GL_FONT_عدد_GLYPH_INDICES_بټ_NV  0x20000000
#تعریف_کړه GL_STANDARD_FONT_FORMAT_NV        0x936C
#تعریف_کړه GL_لار_PROJECTION_NV             0x1701
#تعریف_کړه GL_لار_MODELVIEW_NV              0x1700
#تعریف_کړه GL_لار_MODELVIEW_ډېری_ژوروالی_NV  0x0BA3
#تعریف_کړه GL_لار_MODELVIEW_ماتریکس_NV       0x0BA6
#تعریف_کړه GL_لار_MAX_MODELVIEW_ډېری_ژوروالی_NV 0x0D36
#تعریف_کړه GL_لار_TRANSPOSE_MODELVIEW_ماتریکس_NV 0x84E3
#تعریف_کړه GL_لار_PROJECTION_ډېری_ژوروالی_NV 0x0BA4
#تعریف_کړه GL_لار_PROJECTION_ماتریکس_NV      0x0BA7
#تعریف_کړه GL_لار_MAX_PROJECTION_ډېری_ژوروالی_NV 0x0D38
#تعریف_کړه GL_لار_TRANSPOSE_PROJECTION_ماتریکس_NV 0x84E4
#تعریف_کړه GL_FRAGMENT_ننوت_NV              0x936D
تعريفنوع GLuint (GL_APIENTRYP PFNGLGENPATHSNVPROC) (GLsizei range);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEPATHSNVPROC) (GLuint لار, GLsizei range);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISPATHNVPROC) (GLuint لار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHCOMMANDSNVPROC) (GLuint لار, GLsizei عدد_Commands, ثابت GLubyte *commands, GLsizei عدد_Coords, GLenum coordType, ثابت فراغ *coords);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHCOORDSNVPROC) (GLuint لار, GLsizei عدد_Coords, GLenum coordType, ثابت فراغ *coords);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHSUBCOMMANDSNVPROC) (GLuint لار, GLsizei command_پیل, GLsizei commands_منزل_Delete, GLsizei عدد_Commands, ثابت GLubyte *commands, GLsizei عدد_Coords, GLenum coordType, ثابت فراغ *coords);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHSUBCOORDSNVPROC) (GLuint لار, GLsizei coord_پیل, GLsizei عدد_Coords, GLenum coordType, ثابت فراغ *coords);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHSTRINGNVPROC) (GLuint لار, GLenum format, GLsizei اوږدتیا, ثابت فراغ *لار_String);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHGLYPHSNVPROC) (GLuint لومړی_لار_Name, GLenum font_موخه, ثابت فراغ *fontName, GLbitfield fontStyle, GLsizei عدد_Glyphs, GLenum type, ثابت فراغ *charcodes, GLenum handleMissingGlyphs, GLuint لار_Parameter_Template, GLfloat emScale);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHGLYPHRANGENVPROC) (GLuint لومړی_لار_Name, GLenum font_موخه, ثابت فراغ *fontName, GLbitfield fontStyle, GLuint لومړی_Glyph, GLsizei عدد_Glyphs, GLenum handleMissingGlyphs, GLuint لار_Parameter_Template, GLfloat emScale);
تعريفنوع فراغ (GL_APIENTRYP PFNGLWEIGHTPATHSNVPROC) (GLuint پایله_لار, GLsizei عدد_Paths, ثابت GLuint *paths, ثابت GLfloat *weights);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYPATHNVPROC) (GLuint پایله_لار, GLuint src_لار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLINTERPOLATEPATHSNVPROC) (GLuint پایله_لار, GLuint لار_A, GLuint لار_B, GLfloat وزن);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTRANSFORMPATHNVPROC) (GLuint پایله_لار, GLuint src_لار, GLenum transformType, ثابت GLfloat *transform_ارزښتونه);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHPARAMETERIVNVPROC) (GLuint لار, GLenum pname, ثابت GLint *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHPARAMETERINVPROC) (GLuint لار, GLenum pname, GLint ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHPARAMETERFVNVPROC) (GLuint لار, GLenum pname, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHPARAMETERFNVPROC) (GLuint لار, GLenum pname, GLfloat ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHDASHARRAYNVPROC) (GLuint لار, GLsizei dash_شمېر, ثابت GLfloat *dashArray);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHSTENCILFUNCNVPROC) (GLenum func, GLint ref, GLuint ماسک);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHSTENCILDEPTHOFFSETNVPROC) (GLfloat ضریب, GLfloat units);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILFILLPATHNVPROC) (GLuint لار, GLenum fill_ډېرپېښ, GLuint ماسک);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILSTROKEPATHNVPROC) (GLuint لار, GLint reference, GLuint ماسک);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILFILLPATHINSTANCEDNVPROC) (GLsizei عدد_Paths, GLenum لار_Name_Type, ثابت فراغ *paths, GLuint لار_بنسټ, GLenum fill_ډېرپېښ, GLuint ماسک, GLenum transformType, ثابت GLfloat *transform_ارزښتونه);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILSTROKEPATHINSTANCEDNVPROC) (GLsizei عدد_Paths, GLenum لار_Name_Type, ثابت فراغ *paths, GLuint لار_بنسټ, GLint reference, GLuint ماسک, GLenum transformType, ثابت GLfloat *transform_ارزښتونه);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHCOVERDEPTHFUNCNVPROC) (GLenum func);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOVERFILLPATHNVPROC) (GLuint لار, GLenum cover_ډېرپېښ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOVERSTROKEPATHNVPROC) (GLuint لار, GLenum cover_ډېرپېښ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOVERFILLPATHINSTANCEDNVPROC) (GLsizei عدد_Paths, GLenum لار_Name_Type, ثابت فراغ *paths, GLuint لار_بنسټ, GLenum cover_ډېرپېښ, GLenum transformType, ثابت GLfloat *transform_ارزښتونه);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOVERSTROKEPATHINSTANCEDNVPROC) (GLsizei عدد_Paths, GLenum لار_Name_Type, ثابت فراغ *paths, GLuint لار_بنسټ, GLenum cover_ډېرپېښ, GLenum transformType, ثابت GLfloat *transform_ارزښتونه);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPATHPARAMETERIVNVPROC) (GLuint لار, GLenum pname, GLint *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPATHPARAMETERFVNVPROC) (GLuint لار, GLenum pname, GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPATHCOMMANDSNVPROC) (GLuint لار, GLubyte *commands);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPATHCOORDSNVPROC) (GLuint لار, GLfloat *coords);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPATHDASHARRAYNVPROC) (GLuint لار, GLfloat *dashArray);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPATHMETRICSNVPROC) (GLbitfield metric_Query_ماسک, GLsizei عدد_Paths, GLenum لار_Name_Type, ثابت فراغ *paths, GLuint لار_بنسټ, GLsizei stride, GLfloat *metrics);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPATHMETRICRANGENVPROC) (GLbitfield metric_Query_ماسک, GLuint لومړی_لار_Name, GLsizei عدد_Paths, GLsizei stride, GLfloat *metrics);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPATHSPACINGNVPROC) (GLenum لار_List_ډېرپېښ, GLsizei عدد_Paths, GLenum لار_Name_Type, ثابت فراغ *paths, GLuint لار_بنسټ, GLfloat advanceScale, GLfloat kerningScale, GLenum transformType, GLfloat *returnedSpacing);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISPOINTINFILLPATHNVPROC) (GLuint لار, GLuint ماسک, GLfloat x, GLfloat y);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISPOINTINSTROKEPATHNVPROC) (GLuint لار, GLfloat x, GLfloat y);
تعريفنوع GLfloat (GL_APIENTRYP PFNGLGETPATHLENGTHNVPROC) (GLuint لار, GLsizei پیل_Segment, GLsizei عدد_Segments);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLPOINTALONGPATHNVPROC) (GLuint لار, GLsizei پیل_Segment, GLsizei عدد_Segments, GLfloat واټن, GLfloat *x, GLfloat *y, GLfloat *tangentX, GLfloat *tangentY);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXLOAD3X2FNVPROC) (GLenum ماتریکس_ډېرپېښ, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXLOAD3X3FNVPROC) (GLenum ماتریکس_ډېرپېښ, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXLOADTRANSPOSE3X3FNVPROC) (GLenum ماتریکس_ډېرپېښ, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXMULT3X2FNVPROC) (GLenum ماتریکس_ډېرپېښ, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXMULT3X3FNVPROC) (GLenum ماتریکس_ډېرپېښ, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXMULTTRANSPOSE3X3FNVPROC) (GLenum ماتریکس_ډېرپېښ, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILTHENCOVERFILLPATHNVPROC) (GLuint لار, GLenum fill_ډېرپېښ, GLuint ماسک, GLenum cover_ډېرپېښ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILTHENCOVERSTROKEPATHNVPROC) (GLuint لار, GLint reference, GLuint ماسک, GLenum cover_ډېرپېښ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILTHENCOVERFILLPATHINSTANCEDNVPROC) (GLsizei عدد_Paths, GLenum لار_Name_Type, ثابت فراغ *paths, GLuint لار_بنسټ, GLenum fill_ډېرپېښ, GLuint ماسک, GLenum cover_ډېرپېښ, GLenum transformType, ثابت GLfloat *transform_ارزښتونه);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILTHENCOVERSTROKEPATHINSTANCEDNVPROC) (GLsizei عدد_Paths, GLenum لار_Name_Type, ثابت فراغ *paths, GLuint لار_بنسټ, GLint reference, GLuint ماسک, GLenum cover_ډېرپېښ, GLenum transformType, ثابت GLfloat *transform_ارزښتونه);
تعريفنوع GLenum (GL_APIENTRYP PFNGLPATHGLYPHINDEXRANGENVPROC) (GLenum font_موخه, ثابت فراغ *fontName, GLbitfield fontStyle, GLuint لار_Parameter_Template, GLfloat emScale, GLuint *بنسټ_And_شمېر);
تعريفنوع GLenum (GL_APIENTRYP PFNGLPATHGLYPHINDEXARRAYNVPROC) (GLuint لومړی_لار_Name, GLenum font_موخه, ثابت فراغ *fontName, GLbitfield fontStyle, GLuint لومړی_Glyph_شاخص, GLsizei عدد_Glyphs, GLuint لار_Parameter_Template, GLfloat emScale);
تعريفنوع GLenum (GL_APIENTRYP PFNGLPATHMEMORYGLYPHINDEXARRAYNVPROC) (GLuint لومړی_لار_Name, GLenum font_موخه, GLsizeiptr font_اندازه, ثابت فراغ *font_معلومات, GLsizei face_شاخص, GLuint لومړی_Glyph_شاخص, GLsizei عدد_Glyphs, GLuint لار_Parameter_Template, GLfloat emScale);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMPATHFRAGMENTINPUTGENNVPROC) (GLuint پروګرام, GLint location, GLenum gen_ډېرپېښ, GLint components, ثابت GLfloat *coeffs);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMRESOURCEFVNVPROC) (GLuint پروګرام, GLenum پروګرام_Interface, GLuint شاخص, GLsizei prop_شمېر, ثابت GLenum *props, GLsizei شمېر, GLsizei *اوږدتیا, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXFRUSTUMEXTPROC) (GLenum ډېرپېښ, GLdouble کیڼ, GLdouble ښی, GLdouble bottom, GLdouble سر, GLdouble zNear, GLdouble zFar);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXLOADIDENTITYEXTPROC) (GLenum ډېرپېښ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXLOADTRANSPOSEFEXTPROC) (GLenum ډېرپېښ, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXLOADTRANSPOSEDEXTPROC) (GLenum ډېرپېښ, ثابت GLdouble *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXLOADFEXTPROC) (GLenum ډېرپېښ, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXLOADDEXTPROC) (GLenum ډېرپېښ, ثابت GLdouble *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXMULTTRANSPOSEFEXTPROC) (GLenum ډېرپېښ, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXMULTTRANSPOSEDEXTPROC) (GLenum ډېرپېښ, ثابت GLdouble *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXMULTFEXTPROC) (GLenum ډېرپېښ, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXMULTDEXTPROC) (GLenum ډېرپېښ, ثابت GLdouble *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXORTHOEXTPROC) (GLenum ډېرپېښ, GLdouble کیڼ, GLdouble ښی, GLdouble bottom, GLdouble سر, GLdouble zNear, GLdouble zFar);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXPOPEXTPROC) (GLenum ډېرپېښ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXPUSHEXTPROC) (GLenum ډېرپېښ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXROTATEFEXTPROC) (GLenum ډېرپېښ, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXROTATEDEXTPROC) (GLenum ډېرپېښ, GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXSCALEFEXTPROC) (GLenum ډېرپېښ, GLfloat x, GLfloat y, GLfloat z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXSCALEDEXTPROC) (GLenum ډېرپېښ, GLdouble x, GLdouble y, GLdouble z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXTRANSLATEFEXTPROC) (GLenum ډېرپېښ, GLfloat x, GLfloat y, GLfloat z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXTRANSLATEDEXTPROC) (GLenum ډېرپېښ, GLdouble x, GLdouble y, GLdouble z);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL GLuint GL_APIENTRY glGenPathsNV (GLsizei range);
GL_APICALL فراغ GL_APIENTRY glDeletePathsNV (GLuint لار, GLsizei range);
GL_APICALL GLboolean GL_APIENTRY gl_Is_لار_NV (GLuint لار);
GL_APICALL فراغ GL_APIENTRY gl_لار_Commands_NV (GLuint لار, GLsizei عدد_Commands, ثابت GLubyte *commands, GLsizei عدد_Coords, GLenum coordType, ثابت فراغ *coords);
GL_APICALL فراغ GL_APIENTRY gl_لار_Coords_NV (GLuint لار, GLsizei عدد_Coords, GLenum coordType, ثابت فراغ *coords);
GL_APICALL فراغ GL_APIENTRY gl_لار_Sub_Commands_NV (GLuint لار, GLsizei command_پیل, GLsizei commands_منزل_Delete, GLsizei عدد_Commands, ثابت GLubyte *commands, GLsizei عدد_Coords, GLenum coordType, ثابت فراغ *coords);
GL_APICALL فراغ GL_APIENTRY gl_لار_Sub_Coords_NV (GLuint لار, GLsizei coord_پیل, GLsizei عدد_Coords, GLenum coordType, ثابت فراغ *coords);
GL_APICALL فراغ GL_APIENTRY gl_لار_String_NV (GLuint لار, GLenum format, GLsizei اوږدتیا, ثابت فراغ *لار_String);
GL_APICALL فراغ GL_APIENTRY gl_لار_Glyphs_NV (GLuint لومړی_لار_Name, GLenum font_موخه, ثابت فراغ *fontName, GLbitfield fontStyle, GLsizei عدد_Glyphs, GLenum type, ثابت فراغ *charcodes, GLenum handleMissingGlyphs, GLuint لار_Parameter_Template, GLfloat emScale);
GL_APICALL فراغ GL_APIENTRY gl_لار_Glyph_Range_NV (GLuint لومړی_لار_Name, GLenum font_موخه, ثابت فراغ *fontName, GLbitfield fontStyle, GLuint لومړی_Glyph, GLsizei عدد_Glyphs, GLenum handleMissingGlyphs, GLuint لار_Parameter_Template, GLfloat emScale);
GL_APICALL فراغ GL_APIENTRY gl_وزن_Paths_NV (GLuint پایله_لار, GLsizei عدد_Paths, ثابت GLuint *paths, ثابت GLfloat *weights);
GL_APICALL فراغ GL_APIENTRY gl_Copy_لار_NV (GLuint پایله_لار, GLuint src_لار);
GL_APICALL فراغ GL_APIENTRY glInterpolatePathsNV (GLuint پایله_لار, GLuint لار_A, GLuint لار_B, GLfloat وزن);
GL_APICALL فراغ GL_APIENTRY gl_Transform_لار_NV (GLuint پایله_لار, GLuint src_لار, GLenum transformType, ثابت GLfloat *transform_ارزښتونه);
GL_APICALL فراغ GL_APIENTRY gl_لار_Parameteriv_NV (GLuint لار, GLenum pname, ثابت GLint *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_لار_Parameteri_NV (GLuint لار, GLenum pname, GLint ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_لار_Parameterfv_NV (GLuint لار, GLenum pname, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_لار_Parameterf_NV (GLuint لار, GLenum pname, GLfloat ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_لار_Dash_Array_NV (GLuint لار, GLsizei dash_شمېر, ثابت GLfloat *dashArray);
GL_APICALL فراغ GL_APIENTRY gl_لار_Stencil_Func_NV (GLenum func, GLint ref, GLuint ماسک);
GL_APICALL فراغ GL_APIENTRY gl_لار_Stencil_ژوروالی_دننه_واټن_NV (GLfloat ضریب, GLfloat units);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_Fill_لار_NV (GLuint لار, GLenum fill_ډېرپېښ, GLuint ماسک);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_Stroke_لار_NV (GLuint لار, GLint reference, GLuint ماسک);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_Fill_لار_Instanced_NV (GLsizei عدد_Paths, GLenum لار_Name_Type, ثابت فراغ *paths, GLuint لار_بنسټ, GLenum fill_ډېرپېښ, GLuint ماسک, GLenum transformType, ثابت GLfloat *transform_ارزښتونه);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_Stroke_لار_Instanced_NV (GLsizei عدد_Paths, GLenum لار_Name_Type, ثابت فراغ *paths, GLuint لار_بنسټ, GLint reference, GLuint ماسک, GLenum transformType, ثابت GLfloat *transform_ارزښتونه);
GL_APICALL فراغ GL_APIENTRY gl_لار_Cover_ژوروالی_Func_NV (GLenum func);
GL_APICALL فراغ GL_APIENTRY gl_Cover_Fill_لار_NV (GLuint لار, GLenum cover_ډېرپېښ);
GL_APICALL فراغ GL_APIENTRY gl_Cover_Stroke_لار_NV (GLuint لار, GLenum cover_ډېرپېښ);
GL_APICALL فراغ GL_APIENTRY gl_Cover_Fill_لار_Instanced_NV (GLsizei عدد_Paths, GLenum لار_Name_Type, ثابت فراغ *paths, GLuint لار_بنسټ, GLenum cover_ډېرپېښ, GLenum transformType, ثابت GLfloat *transform_ارزښتونه);
GL_APICALL فراغ GL_APIENTRY gl_Cover_Stroke_لار_Instanced_NV (GLsizei عدد_Paths, GLenum لار_Name_Type, ثابت فراغ *paths, GLuint لار_بنسټ, GLenum cover_ډېرپېښ, GLenum transformType, ثابت GLfloat *transform_ارزښتونه);
GL_APICALL فراغ GL_APIENTRY gl_Get_لار_Parameteriv_NV (GLuint لار, GLenum pname, GLint *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_Get_لار_Parameterfv_NV (GLuint لار, GLenum pname, GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_Get_لار_Commands_NV (GLuint لار, GLubyte *commands);
GL_APICALL فراغ GL_APIENTRY gl_Get_لار_Coords_NV (GLuint لار, GLfloat *coords);
GL_APICALL فراغ GL_APIENTRY gl_Get_لار_Dash_Array_NV (GLuint لار, GLfloat *dashArray);
GL_APICALL فراغ GL_APIENTRY gl_Get_لار_Metrics_NV (GLbitfield metric_Query_ماسک, GLsizei عدد_Paths, GLenum لار_Name_Type, ثابت فراغ *paths, GLuint لار_بنسټ, GLsizei stride, GLfloat *metrics);
GL_APICALL فراغ GL_APIENTRY gl_Get_لار_Metric_Range_NV (GLbitfield metric_Query_ماسک, GLuint لومړی_لار_Name, GLsizei عدد_Paths, GLsizei stride, GLfloat *metrics);
GL_APICALL فراغ GL_APIENTRY gl_Get_لار_Spacing_NV (GLenum لار_List_ډېرپېښ, GLsizei عدد_Paths, GLenum لار_Name_Type, ثابت فراغ *paths, GLuint لار_بنسټ, GLfloat advanceScale, GLfloat kerningScale, GLenum transformType, GLfloat *returnedSpacing);
GL_APICALL GLboolean GL_APIENTRY gl_Is_ټکی_دننه_Fill_لار_NV (GLuint لار, GLuint ماسک, GLfloat x, GLfloat y);
GL_APICALL GLboolean GL_APIENTRY gl_Is_ټکی_دننه_Stroke_لار_NV (GLuint لار, GLfloat x, GLfloat y);
GL_APICALL GLfloat GL_APIENTRY gl_Get_لار_اوږدتیا_NV (GLuint لار, GLsizei پیل_Segment, GLsizei عدد_Segments);
GL_APICALL GLboolean GL_APIENTRY gl_ټکی_Along_لار_NV (GLuint لار, GLsizei پیل_Segment, GLsizei عدد_Segments, GLfloat واټن, GLfloat *x, GLfloat *y, GLfloat *tangentX, GLfloat *tangentY);
GL_APICALL فراغ GL_APIENTRY gl_ماتریکس_Load3x2f_NV (GLenum ماتریکس_ډېرپېښ, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_ماتریکس_Load3x3f_NV (GLenum ماتریکس_ډېرپېښ, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_ماتریکس_بارول_Transpose3x3f_NV (GLenum ماتریکس_ډېرپېښ, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_ماتریکس_Mult3x2f_NV (GLenum ماتریکس_ډېرپېښ, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_ماتریکس_Mult3x3f_NV (GLenum ماتریکس_ډېرپېښ, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_ماتریکس_Mult_Transpose3x3f_NV (GLenum ماتریکس_ډېرپېښ, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_Then_Cover_Fill_لار_NV (GLuint لار, GLenum fill_ډېرپېښ, GLuint ماسک, GLenum cover_ډېرپېښ);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_Then_Cover_Stroke_لار_NV (GLuint لار, GLint reference, GLuint ماسک, GLenum cover_ډېرپېښ);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_Then_Cover_Fill_لار_Instanced_NV (GLsizei عدد_Paths, GLenum لار_Name_Type, ثابت فراغ *paths, GLuint لار_بنسټ, GLenum fill_ډېرپېښ, GLuint ماسک, GLenum cover_ډېرپېښ, GLenum transformType, ثابت GLfloat *transform_ارزښتونه);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_Then_Cover_Stroke_لار_Instanced_NV (GLsizei عدد_Paths, GLenum لار_Name_Type, ثابت فراغ *paths, GLuint لار_بنسټ, GLint reference, GLuint ماسک, GLenum cover_ډېرپېښ, GLenum transformType, ثابت GLfloat *transform_ارزښتونه);
GL_APICALL GLenum GL_APIENTRY gl_لار_Glyph_شاخص_Range_NV (GLenum font_موخه, ثابت فراغ *fontName, GLbitfield fontStyle, GLuint لار_Parameter_Template, GLfloat emScale, GLuint *بنسټ_And_شمېر);
GL_APICALL GLenum GL_APIENTRY gl_لار_Glyph_شاخص_Array_NV (GLuint لومړی_لار_Name, GLenum font_موخه, ثابت فراغ *fontName, GLbitfield fontStyle, GLuint لومړی_Glyph_شاخص, GLsizei عدد_Glyphs, GLuint لار_Parameter_Template, GLfloat emScale);
GL_APICALL GLenum GL_APIENTRY gl_لار_حافظه_Glyph_شاخص_Array_NV (GLuint لومړی_لار_Name, GLenum font_موخه, GLsizeiptr font_اندازه, ثابت فراغ *font_معلومات, GLsizei face_شاخص, GLuint لومړی_Glyph_شاخص, GLsizei عدد_Glyphs, GLuint لار_Parameter_Template, GLfloat emScale);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_لار_Fragment_ننوت_Gen_NV (GLuint پروګرام, GLint location, GLenum gen_ډېرپېښ, GLint components, ثابت GLfloat *coeffs);
GL_APICALL فراغ GL_APIENTRY gl_Get_پروګرام_Resourcefv_NV (GLuint پروګرام, GLenum پروګرام_Interface, GLuint شاخص, GLsizei prop_شمېر, ثابت GLenum *props, GLsizei شمېر, GLsizei *اوږدتیا, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY gl_ماتریکس_Frustum_EXT (GLenum ډېرپېښ, GLdouble کیڼ, GLdouble ښی, GLdouble bottom, GLdouble سر, GLdouble zNear, GLdouble zFar);
GL_APICALL فراغ GL_APIENTRY gl_ماتریکس_بارول_بې_اغېزه_عنصر_EXT (GLenum ډېرپېښ);
GL_APICALL فراغ GL_APIENTRY gl_ماتریکس_بارول_Transposef_EXT (GLenum ډېرپېښ, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_ماتریکس_بارول_Transposed_EXT (GLenum ډېرپېښ, ثابت GLdouble *m);
GL_APICALL فراغ GL_APIENTRY gl_ماتریکس_Loadf_EXT (GLenum ډېرپېښ, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_ماتریکس_Loadd_EXT (GLenum ډېرپېښ, ثابت GLdouble *m);
GL_APICALL فراغ GL_APIENTRY gl_ماتریکس_Mult_Transposef_EXT (GLenum ډېرپېښ, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_ماتریکس_Mult_Transposed_EXT (GLenum ډېرپېښ, ثابت GLdouble *m);
GL_APICALL فراغ GL_APIENTRY gl_ماتریکس_Multf_EXT (GLenum ډېرپېښ, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_ماتریکس_Multd_EXT (GLenum ډېرپېښ, ثابت GLdouble *m);
GL_APICALL فراغ GL_APIENTRY gl_ماتریکس_Ortho_EXT (GLenum ډېرپېښ, GLdouble کیڼ, GLdouble ښی, GLdouble bottom, GLdouble سر, GLdouble zNear, GLdouble zFar);
GL_APICALL فراغ GL_APIENTRY gl_ماتریکس_راوباسه_EXT (GLenum ډېرپېښ);
GL_APICALL فراغ GL_APIENTRY gl_ماتریکس_ټېل_EXT (GLenum ډېرپېښ);
GL_APICALL فراغ GL_APIENTRY gl_ماتریکس_Rotatef_EXT (GLenum ډېرپېښ, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL فراغ GL_APIENTRY gl_ماتریکس_Rotated_EXT (GLenum ډېرپېښ, GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
GL_APICALL فراغ GL_APIENTRY gl_ماتریکس_Scalef_EXT (GLenum ډېرپېښ, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL فراغ GL_APIENTRY gl_ماتریکس_Scaled_EXT (GLenum ډېرپېښ, GLdouble x, GLdouble y, GLdouble z);
GL_APICALL فراغ GL_APIENTRY gl_ماتریکس_Translatef_EXT (GLenum ډېرپېښ, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL فراغ GL_APIENTRY gl_ماتریکس_Translated_EXT (GLenum ډېرپېښ, GLdouble x, GLdouble y, GLdouble z);
#د_که_پای
#د_که_پای /* GL_NV_path_rendering */

#که_نه_تعریف_شوی GL_NV_لار_rendering_shared_څنډه
#تعریف_کړه GL_NV_لار_rendering_shared_څنډه 1
#تعریف_کړه GL_SHARED_څنډه_NV                 0xC0
#د_که_پای /* GL_NV_path_rendering_shared_edge */

#که_نه_تعریف_شوی GL_NV_pixel_بفر_object
#تعریف_کړه GL_NV_pixel_بفر_object 1
#تعریف_کړه GL_PIXEL_PACK_بفر_NV           0x88EB
#تعریف_کړه GL_PIXEL_UNPACK_بفر_NV         0x88EC
#تعریف_کړه GL_PIXEL_PACK_بفر_BINDING_NV   0x88ED
#تعریف_کړه GL_PIXEL_UNPACK_بفر_BINDING_NV 0x88EF
#د_که_پای /* GL_NV_pixel_buffer_object */

#که_نه_تعریف_شوی GL_NV_polygon_ډېرپېښ
#تعریف_کړه GL_NV_polygon_ډېرپېښ 1
#تعریف_کړه GL_POLYGON_ډېرپېښ_NV                0x0B40
#تعریف_کړه GL_POLYGON_دننه_واټن_ټکی_NV        0x2A01
#تعریف_کړه GL_POLYGON_دننه_واټن_کرښه_NV         0x2A02
#تعریف_کړه GL_ټکی_NV                       0x1B00
#تعریف_کړه GL_کرښه_NV                        0x1B01
#تعریف_کړه GL_FILL_NV                        0x1B02
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOLYGONMODENVPROC) (GLenum face, GLenum ډېرپېښ);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Polygon_ډېرپېښ_NV (GLenum face, GLenum ډېرپېښ);
#د_که_پای
#د_که_پای /* GL_NV_polygon_mode */

#که_نه_تعریف_شوی GL_NV_primitive_shading_شرح
#تعریف_کړه GL_NV_primitive_shading_شرح 1
#تعریف_کړه GL_SHADING_شرح_IMAGE_فی_PRIMITIVE_NV 0x95B1
#تعریف_کړه GL_SHADING_شرح_IMAGE_PALETTE_شمېر_NV 0x95B2
#د_که_پای /* GL_NV_primitive_shading_rate */

#که_نه_تعریف_شوی GL_NV_read_بفر
#تعریف_کړه GL_NV_read_بفر 1
#تعریف_کړه GL_READ_بفر_NV                 0x0C02
تعريفنوع فراغ (GL_APIENTRYP PFNGLREADBUFFERNVPROC) (GLenum ډېرپېښ);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Read_بفر_NV (GLenum ډېرپېښ);
#د_که_پای
#د_که_پای /* GL_NV_read_buffer */

#که_نه_تعریف_شوی GL_NV_read_بفر_front
#تعریف_کړه GL_NV_read_بفر_front 1
#د_که_پای /* GL_NV_read_buffer_front */

#که_نه_تعریف_شوی GL_NV_read_ژوروالی
#تعریف_کړه GL_NV_read_ژوروالی 1
#د_که_پای /* GL_NV_read_depth */

#که_نه_تعریف_شوی GL_NV_read_ژوروالی_stencil
#تعریف_کړه GL_NV_read_ژوروالی_stencil 1
#د_که_پای /* GL_NV_read_depth_stencil */

#که_نه_تعریف_شوی GL_NV_read_stencil
#تعریف_کړه GL_NV_read_stencil 1
#د_که_پای /* GL_NV_read_stencil */

#که_نه_تعریف_شوی GL_NV_representative_fragment_test
#تعریف_کړه GL_NV_representative_fragment_test 1
#تعریف_کړه GL_REPRESENTATIVE_FRAGMENT_TEST_NV 0x937F
#د_که_پای /* GL_NV_representative_fragment_test */

#که_نه_تعریف_شوی GL_NV_sRGB_formats
#تعریف_کړه GL_NV_sRGB_formats 1
#تعریف_کړه GL_SLUMINANCE_NV                  0x8C46
#تعریف_کړه GL_SLUMINANCE_ALPHA_NV            0x8C44
#تعریف_کړه GL_SRGB8_NV                       0x8C41
#تعریف_کړه GL_SLUMINANCE8_NV                 0x8C47
#تعریف_کړه GL_SLUMINANCE8_ALPHA8_NV          0x8C45
#تعریف_کړه GL_COMPRESSED_SRGB_S3TC_DXT1_NV   0x8C4C
#تعریف_کړه GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_NV 0x8C4D
#تعریف_کړه GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_NV 0x8C4E
#تعریف_کړه GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_NV 0x8C4F
#تعریف_کړه GL_ETC1_SRGB8_NV                  0x88EE
#د_که_پای /* GL_NV_sRGB_formats */

#که_نه_تعریف_شوی GL_NV_sample_locations
#تعریف_کړه GL_NV_sample_locations 1
#تعریف_کړه GL_SAMPLE_LOCATION_SUBPIXEL_بټونه_NV 0x933D
#تعریف_کړه GL_SAMPLE_LOCATION_PIXEL_GRID_پلنوالی_NV 0x933E
#تعریف_کړه GL_SAMPLE_LOCATION_PIXEL_GRID_لوړوالی_NV 0x933F
#تعریف_کړه GL_PROGRAMMABLE_SAMPLE_LOCATION_جدول_اندازه_NV 0x9340
#تعریف_کړه GL_SAMPLE_LOCATION_NV             0x8E50
#تعریف_کړه GL_PROGRAMMABLE_SAMPLE_LOCATION_NV 0x9341
#تعریف_کړه GL_FRAMEBUFFER_PROGRAMMABLE_SAMPLE_LOCATIONS_NV 0x9342
#تعریف_کړه GL_FRAMEBUFFER_SAMPLE_LOCATION_PIXEL_GRID_NV 0x9343
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERSAMPLELOCATIONSFVNVPROC) (GLenum موخه, GLuint پیل, GLsizei شمېر, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVNVPROC) (GLuint framebuffer, GLuint پیل, GLsizei شمېر, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRESOLVEDEPTHVALUESNVPROC) (فراغ);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferSampleLocationsfvNV (GLenum موخه, GLuint پیل, GLsizei شمېر, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY glNamedFramebufferSampleLocationsfvNV (GLuint framebuffer, GLuint پیل, GLsizei شمېر, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY gl_Resolve_ژوروالی_ارزښتونه_NV (فراغ);
#د_که_پای
#د_که_پای /* GL_NV_sample_locations */

#که_نه_تعریف_شوی GL_NV_sample_ماسک_override_coverage
#تعریف_کړه GL_NV_sample_ماسک_override_coverage 1
#د_که_پای /* GL_NV_sample_mask_override_coverage */

#که_نه_تعریف_شوی GL_NV_scissor_exclusive
#تعریف_کړه GL_NV_scissor_exclusive 1
#تعریف_کړه GL_SCISSOR_TEST_EXCLUSIVE_NV      0x9555
#تعریف_کړه GL_SCISSOR_BOX_EXCLUSIVE_NV       0x9556
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSOREXCLUSIVENVPROC) (GLint x, GLint y, GLsizei پلنوالی, GLsizei لوړوالی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSOREXCLUSIVEARRAYVNVPROC) (GLuint لومړی, GLsizei شمېر, ثابت GLint *v);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glScissorExclusiveNV (GLint x, GLint y, GLsizei پلنوالی, GLsizei لوړوالی);
GL_APICALL فراغ GL_APIENTRY glScissorExclusiveArrayvNV (GLuint لومړی, GLsizei شمېر, ثابت GLint *v);
#د_که_پای
#د_که_پای /* GL_NV_scissor_exclusive */

#که_نه_تعریف_شوی GL_NV_shader_atomic_fp16_ویکټور
#تعریف_کړه GL_NV_shader_atomic_fp16_ویکټور 1
#د_که_پای /* GL_NV_shader_atomic_fp16_vector */

#که_نه_تعریف_شوی GL_NV_shader_noperspective_interpolation
#تعریف_کړه GL_NV_shader_noperspective_interpolation 1
#د_که_پای /* GL_NV_shader_noperspective_interpolation */

#که_نه_تعریف_شوی GL_NV_shader_subgroup_partitioned
#تعریف_کړه GL_NV_shader_subgroup_partitioned 1
#تعریف_کړه GL_SUBGROUP_FEATURE_PARTITIONED_بټ_NV 0x00000100
#د_که_پای /* GL_NV_shader_subgroup_partitioned */

#که_نه_تعریف_شوی GL_NV_shader_texture_footprint
#تعریف_کړه GL_NV_shader_texture_footprint 1
#د_که_پای /* GL_NV_shader_texture_footprint */

#که_نه_تعریف_شوی GL_NV_shading_شرح_image
#تعریف_کړه GL_NV_shading_شرح_image 1
#تعریف_کړه GL_SHADING_شرح_IMAGE_NV          0x9563
#تعریف_کړه GL_SHADING_شرح_NO_INVOCATIONS_NV 0x9564
#تعریف_کړه GL_SHADING_شرح_1_INVOCATION_فی_PIXEL_NV 0x9565
#تعریف_کړه GL_SHADING_شرح_1_INVOCATION_فی_1_X2_PIXELS_NV 0x9566
#تعریف_کړه GL_SHADING_شرح_1_INVOCATION_فی_2_X1_PIXELS_NV 0x9567
#تعریف_کړه GL_SHADING_شرح_1_INVOCATION_فی_2_X2_PIXELS_NV 0x9568
#تعریف_کړه GL_SHADING_شرح_1_INVOCATION_فی_2_X4_PIXELS_NV 0x9569
#تعریف_کړه GL_SHADING_شرح_1_INVOCATION_فی_4_X2_PIXELS_NV 0x956A
#تعریف_کړه GL_SHADING_شرح_1_INVOCATION_فی_4_X4_PIXELS_NV 0x956B
#تعریف_کړه GL_SHADING_شرح_2_INVOCATIONS_فی_PIXEL_NV 0x956C
#تعریف_کړه GL_SHADING_شرح_4_INVOCATIONS_فی_PIXEL_NV 0x956D
#تعریف_کړه GL_SHADING_شرح_8_INVOCATIONS_فی_PIXEL_NV 0x956E
#تعریف_کړه GL_SHADING_شرح_16_INVOCATIONS_فی_PIXEL_NV 0x956F
#تعریف_کړه GL_SHADING_شرح_IMAGE_BINDING_NV  0x955B
#تعریف_کړه GL_SHADING_شرح_IMAGE_TEXEL_پلنوالی_NV 0x955C
#تعریف_کړه GL_SHADING_شرح_IMAGE_TEXEL_لوړوالی_NV 0x955D
#تعریف_کړه GL_SHADING_شرح_IMAGE_PALETTE_اندازه_NV 0x955E
#تعریف_کړه GL_MAX_COARSE_FRAGMENT_SAMPLES_NV 0x955F
#تعریف_کړه GL_SHADING_شرح_SAMPLE_ترتیب_DEFAULT_NV 0x95AE
#تعریف_کړه GL_SHADING_شرح_SAMPLE_ترتیب_PIXEL_MAJOR_NV 0x95AF
#تعریف_کړه GL_SHADING_شرح_SAMPLE_ترتیب_SAMPLE_MAJOR_NV 0x95B0
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDSHADINGRATEIMAGENVPROC) (GLuint texture);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSHADINGRATEIMAGEPALETTENVPROC) (GLuint viewport, GLuint ثبت, GLenum *شرح);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSHADINGRATESAMPLELOCATIONIVNVPROC) (GLenum شرح, GLuint samples, GLuint شاخص, GLint *location);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADINGRATEIMAGEBARRIERNVPROC) (GLboolean synchronize);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADINGRATEIMAGEPALETTENVPROC) (GLuint viewport, GLuint لومړی, GLsizei شمېر, ثابت GLenum *rates);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADINGRATESAMPLEORDERNVPROC) (GLenum ترتیب);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADINGRATESAMPLEORDERCUSTOMNVPROC) (GLenum شرح, GLuint samples, ثابت GLint *locations);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Bind_Shading_شرح_Image_NV (GLuint texture);
GL_APICALL فراغ GL_APIENTRY gl_Get_Shading_شرح_Image_Palette_NV (GLuint viewport, GLuint ثبت, GLenum *شرح);
GL_APICALL فراغ GL_APIENTRY gl_Get_Shading_شرح_Sample_Locationiv_NV (GLenum شرح, GLuint samples, GLuint شاخص, GLint *location);
GL_APICALL فراغ GL_APIENTRY gl_Shading_شرح_Image_Barrier_NV (GLboolean synchronize);
GL_APICALL فراغ GL_APIENTRY gl_Shading_شرح_Image_Palette_NV (GLuint viewport, GLuint لومړی, GLsizei شمېر, ثابت GLenum *rates);
GL_APICALL فراغ GL_APIENTRY gl_Shading_شرح_Sample_ترتیب_NV (GLenum ترتیب);
GL_APICALL فراغ GL_APIENTRY gl_Shading_شرح_Sample_ترتیب_Custom_NV (GLenum شرح, GLuint samples, ثابت GLint *locations);
#د_که_پای
#د_که_پای /* GL_NV_shading_rate_image */

#که_نه_تعریف_شوی GL_NV_shadow_samplers_array
#تعریف_کړه GL_NV_shadow_samplers_array 1
#تعریف_کړه GL_SAMPLER_2D_ARRAY_SHADOW_NV     0x8DC4
#د_که_پای /* GL_NV_shadow_samplers_array */

#که_نه_تعریف_شوی GL_NV_shadow_samplers_cube
#تعریف_کړه GL_NV_shadow_samplers_cube 1
#تعریف_کړه GL_SAMPLER_CUBE_SHADOW_NV         0x8DC5
#د_که_پای /* GL_NV_shadow_samplers_cube */

#که_نه_تعریف_شوی GL_NV_stereo_view_rendering
#تعریف_کړه GL_NV_stereo_view_rendering 1
#د_که_پای /* GL_NV_stereo_view_rendering */

#که_نه_تعریف_شوی GL_NV_texture_barrier
#تعریف_کړه GL_NV_texture_barrier 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTUREBARRIERNVPROC) (فراغ);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTextureBarrierNV (فراغ);
#د_که_پای
#د_که_پای /* GL_NV_texture_barrier */

#که_نه_تعریف_شوی GL_NV_texture_border_clamp
#تعریف_کړه GL_NV_texture_border_clamp 1
#تعریف_کړه GL_TEXTURE_BORDER_COLOR_NV        0x1004
#تعریف_کړه GL_CLAMP_منزل_BORDER_NV             0x812D
#د_که_پای /* GL_NV_texture_border_clamp */

#که_نه_تعریف_شوی GL_NV_texture_compression_s3tc_update
#تعریف_کړه GL_NV_texture_compression_s3tc_update 1
#د_که_پای /* GL_NV_texture_compression_s3tc_update */

#که_نه_تعریف_شوی GL_NV_texture_npot_2D_mipmap
#تعریف_کړه GL_NV_texture_npot_2D_mipmap 1
#د_که_پای /* GL_NV_texture_npot_2D_mipmap */

#که_نه_تعریف_شوی GL_NV_timeline_semaphore
#تعریف_کړه GL_NV_timeline_semaphore 1
#تعریف_کړه GL_TIMELINE_SEMAPHORE_ارزښت_NV    0x9595
#تعریف_کړه GL_SEMAPHORE_TYPE_NV              0x95B3
#تعریف_کړه GL_SEMAPHORE_TYPE_دوګونی_NV       0x95B4
#تعریف_کړه GL_SEMAPHORE_TYPE_TIMELINE_NV     0x95B5
#تعریف_کړه GL_MAX_TIMELINE_SEMAPHORE_ارزښت_DIFFERENCE_NV 0x95B6
تعريفنوع فراغ (GL_APIENTRYP PFNGLCREATESEMAPHORESNVPROC) (GLsizei n, GLuint *semaphores);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSEMAPHOREPARAMETERIVNVPROC) (GLuint semaphore, GLenum pname, ثابت GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSEMAPHOREPARAMETERIVNVPROC) (GLuint semaphore, GLenum pname, GLint *params);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glCreateSemaphoresNV (GLsizei n, GLuint *semaphores);
GL_APICALL فراغ GL_APIENTRY glSemaphoreParameterivNV (GLuint semaphore, GLenum pname, ثابت GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetSemaphoreParameterivNV (GLuint semaphore, GLenum pname, GLint *params);
#د_که_پای
#د_که_پای /* GL_NV_timeline_semaphore */

#که_نه_تعریف_شوی GL_NV_viewport_array
#تعریف_کړه GL_NV_viewport_array 1
#تعریف_کړه GL_MAX_VIEWPORTS_NV               0x825B
#تعریف_کړه GL_VIEWPORT_SUBPIXEL_بټونه_NV      0x825C
#تعریف_کړه GL_VIEWPORT_BOUNDS_RANGE_NV       0x825D
#تعریف_کړه GL_VIEWPORT_شاخص_PROVOKING_راس_NV 0x825F
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTARRAYVNVPROC) (GLuint لومړی, GLsizei شمېر, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTINDEXEDFNVPROC) (GLuint شاخص, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTINDEXEDFVNVPROC) (GLuint شاخص, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSORARRAYVNVPROC) (GLuint لومړی, GLsizei شمېر, ثابت GLint *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSORINDEXEDNVPROC) (GLuint شاخص, GLint کیڼ, GLint bottom, GLsizei پلنوالی, GLsizei لوړوالی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSORINDEXEDVNVPROC) (GLuint شاخص, ثابت GLint *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHRANGEARRAYFVNVPROC) (GLuint لومړی, GLsizei شمېر, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHRANGEINDEXEDFNVPROC) (GLuint شاخص, GLfloat n, GLfloat f);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFLOATI_VNVPROC) (GLenum موخه, GLuint شاخص, GLfloat *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENABLEINVPROC) (GLenum موخه, GLuint شاخص);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISABLEINVPROC) (GLenum موخه, GLuint شاخص);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISENABLEDINVPROC) (GLenum موخه, GLuint شاخص);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glViewportArrayvNV (GLuint لومړی, GLsizei شمېر, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY glViewportIndexedfNV (GLuint شاخص, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
GL_APICALL فراغ GL_APIENTRY glViewportIndexedfvNV (GLuint شاخص, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY glScissorArrayvNV (GLuint لومړی, GLsizei شمېر, ثابت GLint *v);
GL_APICALL فراغ GL_APIENTRY gl_Scissor_شاخصي_NV (GLuint شاخص, GLint کیڼ, GLint bottom, GLsizei پلنوالی, GLsizei لوړوالی);
GL_APICALL فراغ GL_APIENTRY glScissorIndexedvNV (GLuint شاخص, ثابت GLint *v);
GL_APICALL فراغ GL_APIENTRY gl_ژوروالی_Range_Arrayfv_NV (GLuint لومړی, GLsizei شمېر, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY gl_ژوروالی_Range_Indexedf_NV (GLuint شاخص, GLfloat n, GLfloat f);
GL_APICALL فراغ GL_APIENTRY glGetFloati_vNV (GLenum موخه, GLuint شاخص, GLfloat *معلومات);
GL_APICALL فراغ GL_APIENTRY glEnableiNV (GLenum موخه, GLuint شاخص);
GL_APICALL فراغ GL_APIENTRY glDisableiNV (GLenum موخه, GLuint شاخص);
GL_APICALL GLboolean GL_APIENTRY glIsEnablediNV (GLenum موخه, GLuint شاخص);
#د_که_پای
#د_که_پای /* GL_NV_viewport_array */

#که_نه_تعریف_شوی GL_NV_viewport_array2
#تعریف_کړه GL_NV_viewport_array2 1
#د_که_پای /* GL_NV_viewport_array2 */

#که_نه_تعریف_شوی GL_NV_viewport_swizzle
#تعریف_کړه GL_NV_viewport_swizzle 1
#تعریف_کړه GL_VIEWPORT_SWIZZLE_مثبت_X_NV 0x9350
#تعریف_کړه GL_VIEWPORT_SWIZZLE_NEGATIVE_X_NV 0x9351
#تعریف_کړه GL_VIEWPORT_SWIZZLE_مثبت_Y_NV 0x9352
#تعریف_کړه GL_VIEWPORT_SWIZZLE_NEGATIVE_Y_NV 0x9353
#تعریف_کړه GL_VIEWPORT_SWIZZLE_مثبت_Z_NV 0x9354
#تعریف_کړه GL_VIEWPORT_SWIZZLE_NEGATIVE_Z_NV 0x9355
#تعریف_کړه GL_VIEWPORT_SWIZZLE_مثبت_W_NV 0x9356
#تعریف_کړه GL_VIEWPORT_SWIZZLE_NEGATIVE_W_NV 0x9357
#تعریف_کړه GL_VIEWPORT_SWIZZLE_X_NV          0x9358
#تعریف_کړه GL_VIEWPORT_SWIZZLE_Y_NV          0x9359
#تعریف_کړه GL_VIEWPORT_SWIZZLE_Z_NV          0x935A
#تعریف_کړه GL_VIEWPORT_SWIZZLE_W_NV          0x935B
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTSWIZZLENVPROC) (GLuint شاخص, GLenum swizzlex, GLenum swizzley, GLenum swizzlez, GLenum swizzlew);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glViewportSwizzleNV (GLuint شاخص, GLenum swizzlex, GLenum swizzley, GLenum swizzlez, GLenum swizzlew);
#د_که_پای
#د_که_پای /* GL_NV_viewport_swizzle */

#که_نه_تعریف_شوی GL_OVR_multiview
#تعریف_کړه GL_OVR_multiview 1
#تعریف_کړه GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_عدد_VIEWS_OVR 0x9630
#تعریف_کړه GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_بنسټ_VIEW_شاخص_OVR 0x9632
#تعریف_کړه GL_MAX_VIEWS_OVR                  0x9631
#تعریف_کړه GL_FRAMEBUFFER_INCOMPLETE_VIEW_TARGETS_OVR 0x9633
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREMULTIVIEWOVRPROC) (GLenum موخه, GLenum attachment, GLuint texture, GLint level, GLint بنسټ_View_شاخص, GLsizei عدد_Views_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLNAMEDFRAMEBUFFERTEXTUREMULTIVIEWOVRPROC) (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint بنسټ_View_شاخص, GLsizei عدد_Views_2);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferTextureMultiviewOVR (GLenum موخه, GLenum attachment, GLuint texture, GLint level, GLint بنسټ_View_شاخص, GLsizei عدد_Views_2);
GL_APICALL فراغ GL_APIENTRY glNamedFramebufferTextureMultiviewOVR (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint بنسټ_View_شاخص, GLsizei عدد_Views_2);
#د_که_پای
#د_که_پای /* GL_OVR_multiview */

#که_نه_تعریف_شوی GL_OVR_multiview2
#تعریف_کړه GL_OVR_multiview2 1
#د_که_پای /* GL_OVR_multiview2 */

#که_نه_تعریف_شوی GL_OVR_multiview_multisampled_render_منزل_texture
#تعریف_کړه GL_OVR_multiview_multisampled_render_منزل_texture 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREMULTISAMPLEMULTIVIEWOVRPROC) (GLenum موخه, GLenum attachment, GLuint texture, GLint level, GLsizei samples, GLint بنسټ_View_شاخص, GLsizei عدد_Views_2);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferTextureMultisampleMultiviewOVR (GLenum موخه, GLenum attachment, GLuint texture, GLint level, GLsizei samples, GLint بنسټ_View_شاخص, GLsizei عدد_Views_2);
#د_که_پای
#د_که_پای /* GL_OVR_multiview_multisampled_render_to_texture */

#که_نه_تعریف_شوی GL_QCOM_YUV_texture_gather
#تعریف_کړه GL_QCOM_YUV_texture_gather 1
#د_که_پای /* GL_QCOM_YUV_texture_gather */

#که_نه_تعریف_شوی GL_QCOM_alpha_test
#تعریف_کړه GL_QCOM_alpha_test 1
#تعریف_کړه GL_ALPHA_TEST_QCOM                0x0BC0
#تعریف_کړه GL_ALPHA_TEST_FUNC_QCOM           0x0BC1
#تعریف_کړه GL_ALPHA_TEST_REF_QCOM            0x0BC2
تعريفنوع فراغ (GL_APIENTRYP PFNGLALPHAFUNCQCOMPROC) (GLenum func, GLclampf ref);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glAlphaFuncQCOM (GLenum func, GLclampf ref);
#د_که_پای
#د_که_پای /* GL_QCOM_alpha_test */

#که_نه_تعریف_شوی GL_QCOM_binning_control
#تعریف_کړه GL_QCOM_binning_control 1
#تعریف_کړه GL_BINNING_CONTROL_HINT_QCOM      0x8FB0
#تعریف_کړه GL_CPU_OPTIMIZED_QCOM             0x8FB1
#تعریف_کړه GL_GPU_OPTIMIZED_QCOM             0x8FB2
#تعریف_کړه GL_RENDER_مستقیم_منزل_FRAMEBUFFER_QCOM 0x8FB3
#د_که_پای /* GL_QCOM_binning_control */

#که_نه_تعریف_شوی GL_QCOM_driver_control
#تعریف_کړه GL_QCOM_driver_control 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETDRIVERCONTROLSQCOMPROC) (GLint *عدد, GLsizei اندازه, GLuint *driverControls);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETDRIVERCONTROLSTRINGQCOMPROC) (GLuint driverControl, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLchar *driverControlString);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glGetDriverControlsQCOM (GLint *عدد, GLsizei اندازه, GLuint *driverControls);
GL_APICALL فراغ GL_APIENTRY glGetDriverControlStringQCOM (GLuint driverControl, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLchar *driverControlString);
GL_APICALL فراغ GL_APIENTRY glEnableDriverControlQCOM (GLuint driverControl);
GL_APICALL فراغ GL_APIENTRY glDisableDriverControlQCOM (GLuint driverControl);
#د_که_پای
#د_که_پای /* GL_QCOM_driver_control */

#که_نه_تعریف_شوی GL_QCOM_extended_get
#تعریف_کړه GL_QCOM_extended_get 1
#تعریف_کړه GL_TEXTURE_پلنوالی_QCOM             0x8BD2
#تعریف_کړه GL_TEXTURE_لوړوالی_QCOM            0x8BD3
#تعریف_کړه GL_TEXTURE_ژوروالی_QCOM             0x8BD4
#تعریف_کړه GL_TEXTURE_دننی_FORMAT_QCOM   0x8BD5
#تعریف_کړه GL_TEXTURE_FORMAT_QCOM            0x8BD6
#تعریف_کړه GL_TEXTURE_TYPE_QCOM              0x8BD7
#تعریف_کړه GL_TEXTURE_IMAGE_VALID_QCOM       0x8BD8
#تعریف_کړه GL_TEXTURE_عدد_پوړونه_QCOM        0x8BD9
#تعریف_کړه GL_TEXTURE_موخه_QCOM            0x8BDA
#تعریف_کړه GL_TEXTURE_OBJECT_VALID_QCOM      0x8BDB
#تعریف_کړه GL_STATE_RESTORE                  0x8BDC
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETTEXTURESQCOMPROC) (GLuint *textures, GLint maxTextures, GLint *عدد_Textures);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETBUFFERSQCOMPROC) (GLuint *buffers, GLint maxBuffers, GLint *عدد_Buffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETRENDERBUFFERSQCOMPROC) (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *عدد_Renderbuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETFRAMEBUFFERSQCOMPROC) (GLuint *framebuffers, GLint maxFramebuffers, GLint *عدد_Framebuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETTEXLEVELPARAMETERIVQCOMPROC) (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTTEXOBJECTSTATEOVERRIDEIQCOMPROC) (GLenum موخه, GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETTEXSUBIMAGEQCOMPROC) (GLenum موخه, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLenum format, GLenum type, فراغ *texels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETBUFFERPOINTERVQCOMPROC) (GLenum موخه, فراغ **params);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glExtGetTexturesQCOM (GLuint *textures, GLint maxTextures, GLint *عدد_Textures);
GL_APICALL فراغ GL_APIENTRY glExtGetBuffersQCOM (GLuint *buffers, GLint maxBuffers, GLint *عدد_Buffers);
GL_APICALL فراغ GL_APIENTRY glExtGetRenderbuffersQCOM (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *عدد_Renderbuffers);
GL_APICALL فراغ GL_APIENTRY glExtGetFramebuffersQCOM (GLuint *framebuffers, GLint maxFramebuffers, GLint *عدد_Framebuffers);
GL_APICALL فراغ GL_APIENTRY glExtGetTexLevelParameterivQCOM (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glExtTexObjectStateOverrideiQCOM (GLenum موخه, GLenum pname, GLint param);
GL_APICALL فراغ GL_APIENTRY glExtGetTexSubImageQCOM (GLenum موخه, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLenum format, GLenum type, فراغ *texels);
GL_APICALL فراغ GL_APIENTRY gl_Ext_Get_بفر_Pointerv_QCOM (GLenum موخه, فراغ **params);
#د_که_پای
#د_که_پای /* GL_QCOM_extended_get */

#که_نه_تعریف_شوی GL_QCOM_extended_get2
#تعریف_کړه GL_QCOM_extended_get2 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETSHADERSQCOMPROC) (GLuint *shaders, GLint maxShaders, GLint *عدد_Shaders);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETPROGRAMSQCOMPROC) (GLuint *programs, GLint maxPrograms, GLint *عدد_Programs);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLEXTISPROGRAMBINARYQCOMPROC) (GLuint پروګرام);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETPROGRAMBINARYSOURCEQCOMPROC) (GLuint پروګرام, GLenum shadertype, GLchar *سرچینه, GLint *اوږدتیا);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glExtGetShadersQCOM (GLuint *shaders, GLint maxShaders, GLint *عدد_Shaders);
GL_APICALL فراغ GL_APIENTRY glExtGetProgramsQCOM (GLuint *programs, GLint maxPrograms, GLint *عدد_Programs);
GL_APICALL GLboolean GL_APIENTRY gl_Ext_Is_پروګرام_دوګونی_QCOM (GLuint پروګرام);
GL_APICALL فراغ GL_APIENTRY gl_Ext_Get_پروګرام_دوګونی_سرچینه_QCOM (GLuint پروګرام, GLenum shadertype, GLchar *سرچینه, GLint *اوږدتیا);
#د_که_پای
#د_که_پای /* GL_QCOM_extended_get2 */

#که_نه_تعریف_شوی GL_QCOM_چوکاټ_extrapolation
#تعریف_کړه GL_QCOM_چوکاټ_extrapolation 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTRAPOLATETEX2DQCOMPROC) (GLuint src1, GLuint src2, GLuint output, GLfloat scale_ضریب);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glExtrapolateTex2DQCOM (GLuint src1, GLuint src2, GLuint output, GLfloat scale_ضریب);
#د_که_پای
#د_که_پای /* GL_QCOM_frame_extrapolation */

#که_نه_تعریف_شوی GL_QCOM_framebuffer_foveated
#تعریف_کړه GL_QCOM_framebuffer_foveated 1
#تعریف_کړه GL_FOVEATION_ENABLE_بټ_QCOM      0x00000001
#تعریف_کړه GL_FOVEATION_SCALED_BIN_لاره_بټ_QCOM 0x00000002
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERFOVEATIONCONFIGQCOMPROC) (GLuint framebuffer, GLuint عدد_Layers, GLuint focal_Points_فی_Layer, GLuint requestedFeatures, GLuint *providedFeatures);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERFOVEATIONPARAMETERSQCOMPROC) (GLuint framebuffer, GLuint layer, GLuint focal_ټکی, GLfloat focalX, GLfloat focalY, GLfloat gainX, GLfloat gainY, GLfloat foveaArea);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferFoveationConfigQCOM (GLuint framebuffer, GLuint عدد_Layers, GLuint focal_Points_فی_Layer, GLuint requestedFeatures, GLuint *providedFeatures);
GL_APICALL فراغ GL_APIENTRY glFramebufferFoveationParametersQCOM (GLuint framebuffer, GLuint layer, GLuint focal_ټکی, GLfloat focalX, GLfloat focalY, GLfloat gainX, GLfloat gainY, GLfloat foveaArea);
#د_که_پای
#د_که_پای /* GL_QCOM_framebuffer_foveated */

#که_نه_تعریف_شوی GL_QCOM_motion_estimation
#تعریف_کړه GL_QCOM_motion_estimation 1
#تعریف_کړه GL_MOTION_ESTIMATION_پلټنه_بلاک_X_QCOM 0x8C90
#تعریف_کړه GL_MOTION_ESTIMATION_پلټنه_بلاک_Y_QCOM 0x8C91
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXESTIMATEMOTIONQCOMPROC) (GLuint ref, GLuint موخه, GLuint output);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXESTIMATEMOTIONREGIONSQCOMPROC) (GLuint ref, GLuint موخه, GLuint output, GLuint ماسک);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTexEstimateMotionQCOM (GLuint ref, GLuint موخه, GLuint output);
GL_APICALL فراغ GL_APIENTRY glTexEstimateMotionRegionsQCOM (GLuint ref, GLuint موخه, GLuint output, GLuint ماسک);
#د_که_پای
#د_که_پای /* GL_QCOM_motion_estimation */

#که_نه_تعریف_شوی GL_QCOM_perfmon_global_ډېرپېښ
#تعریف_کړه GL_QCOM_perfmon_global_ډېرپېښ 1
#تعریف_کړه GL_PERFMON_GLOBAL_ډېرپېښ_QCOM       0x8FA0
#د_که_پای /* GL_QCOM_perfmon_global_mode */

#که_نه_تعریف_شوی GL_QCOM_render_sRGB_R8_RG8
#تعریف_کړه GL_QCOM_render_sRGB_R8_RG8 1
#د_که_پای /* GL_QCOM_render_sRGB_R8_RG8 */

#که_نه_تعریف_شوی GL_QCOM_render_shared_exponent
#تعریف_کړه GL_QCOM_render_shared_exponent 1
#د_که_پای /* GL_QCOM_render_shared_exponent */

#که_نه_تعریف_شوی GL_QCOM_shader_framebuffer_fetch_noncoherent
#تعریف_کړه GL_QCOM_shader_framebuffer_fetch_noncoherent 1
#تعریف_کړه GL_FRAMEBUFFER_FETCH_NONCOHERENT_QCOM 0x96A2
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERFETCHBARRIERQCOMPROC) (فراغ);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferFetchBarrierQCOM (فراغ);
#د_که_پای
#د_که_پای /* GL_QCOM_shader_framebuffer_fetch_noncoherent */

#که_نه_تعریف_شوی GL_QCOM_shader_framebuffer_fetch_شرح
#تعریف_کړه GL_QCOM_shader_framebuffer_fetch_شرح 1
#د_که_پای /* GL_QCOM_shader_framebuffer_fetch_rate */

#که_نه_تعریف_شوی GL_QCOM_shading_شرح
#تعریف_کړه GL_QCOM_shading_شرح 1
#تعریف_کړه GL_SHADING_شرح_QCOM              0x96A4
#تعریف_کړه GL_SHADING_شرح_PRESERVE_ASPECT_نسبت_QCOM 0x96A5
#تعریف_کړه GL_SHADING_شرح_1_X1_PIXELS_QCOM   0x96A6
#تعریف_کړه GL_SHADING_شرح_1_X2_PIXELS_QCOM   0x96A7
#تعریف_کړه GL_SHADING_شرح_2_X1_PIXELS_QCOM   0x96A8
#تعریف_کړه GL_SHADING_شرح_2_X2_PIXELS_QCOM   0x96A9
#تعریف_کړه GL_SHADING_شرح_4_X2_PIXELS_QCOM   0x96AC
#تعریف_کړه GL_SHADING_شرح_4_X4_PIXELS_QCOM   0x96AE
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADINGRATEQCOMPROC) (GLenum شرح);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Shading_شرح_QCOM (GLenum شرح);
#د_که_پای
#د_که_پای /* GL_QCOM_shading_rate */

#که_نه_تعریف_شوی GL_QCOM_texture_foveated
#تعریف_کړه GL_QCOM_texture_foveated 1
#تعریف_کړه GL_TEXTURE_FOVEATED_FEATURE_بټونه_QCOM 0x8BFB
#تعریف_کړه GL_TEXTURE_FOVEATED_MIN_PIXEL_DENSITY_QCOM 0x8BFC
#تعریف_کړه GL_TEXTURE_FOVEATED_FEATURE_QUERY_QCOM 0x8BFD
#تعریف_کړه GL_TEXTURE_FOVEATED_عدد_FOCAL_POINTS_QUERY_QCOM 0x8BFE
#تعریف_کړه GL_FRAMEBUFFER_INCOMPLETE_FOVEATION_QCOM 0x8BFF
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTUREFOVEATIONPARAMETERSQCOMPROC) (GLuint texture, GLuint layer, GLuint focal_ټکی, GLfloat focalX, GLfloat focalY, GLfloat gainX, GLfloat gainY, GLfloat foveaArea);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTextureFoveationParametersQCOM (GLuint texture, GLuint layer, GLuint focal_ټکی, GLfloat focalX, GLfloat focalY, GLfloat gainX, GLfloat gainY, GLfloat foveaArea);
#د_که_پای
#د_که_پای /* GL_QCOM_texture_foveated */

#که_نه_تعریف_شوی GL_QCOM_texture_foveated2
#تعریف_کړه GL_QCOM_texture_foveated2 1
#تعریف_کړه GL_TEXTURE_FOVEATED_CUTOFF_DENSITY_QCOM 0x96A0
#د_که_پای /* GL_QCOM_texture_foveated2 */

#که_نه_تعریف_شوی GL_QCOM_texture_foveated_subsampled_layout
#تعریف_کړه GL_QCOM_texture_foveated_subsampled_layout 1
#تعریف_کړه GL_FOVEATION_SUBSAMPLED_LAYOUT_لاره_بټ_QCOM 0x00000004
#تعریف_کړه GL_MAX_SHADER_SUBSAMPLED_IMAGE_UNITS_QCOM 0x8FA1
#د_که_پای /* GL_QCOM_texture_foveated_subsampled_layout */

#که_نه_تعریف_شوی GL_QCOM_texture_lod_bias
#تعریف_کړه GL_QCOM_texture_lod_bias 1
#تعریف_کړه GL_TEXTURE_LOD_BIAS_QCOM          0x8C96
#د_که_پای /* GL_QCOM_texture_lod_bias */

#که_نه_تعریف_شوی GL_QCOM_tiled_rendering
#تعریف_کړه GL_QCOM_tiled_rendering 1
#تعریف_کړه GL_COLOR_بفر_BIT0_QCOM         0x00000001
#تعریف_کړه GL_COLOR_بفر_BIT1_QCOM         0x00000002
#تعریف_کړه GL_COLOR_بفر_BIT2_QCOM         0x00000004
#تعریف_کړه GL_COLOR_بفر_BIT3_QCOM         0x00000008
#تعریف_کړه GL_COLOR_بفر_BIT4_QCOM         0x00000010
#تعریف_کړه GL_COLOR_بفر_BIT5_QCOM         0x00000020
#تعریف_کړه GL_COLOR_بفر_BIT6_QCOM         0x00000040
#تعریف_کړه GL_COLOR_بفر_BIT7_QCOM         0x00000080
#تعریف_کړه GL_ژوروالی_بفر_BIT0_QCOM         0x00000100
#تعریف_کړه GL_ژوروالی_بفر_BIT1_QCOM         0x00000200
#تعریف_کړه GL_ژوروالی_بفر_BIT2_QCOM         0x00000400
#تعریف_کړه GL_ژوروالی_بفر_BIT3_QCOM         0x00000800
#تعریف_کړه GL_ژوروالی_بفر_BIT4_QCOM         0x00001000
#تعریف_کړه GL_ژوروالی_بفر_BIT5_QCOM         0x00002000
#تعریف_کړه GL_ژوروالی_بفر_BIT6_QCOM         0x00004000
#تعریف_کړه GL_ژوروالی_بفر_BIT7_QCOM         0x00008000
#تعریف_کړه GL_STENCIL_بفر_BIT0_QCOM       0x00010000
#تعریف_کړه GL_STENCIL_بفر_BIT1_QCOM       0x00020000
#تعریف_کړه GL_STENCIL_بفر_BIT2_QCOM       0x00040000
#تعریف_کړه GL_STENCIL_بفر_BIT3_QCOM       0x00080000
#تعریف_کړه GL_STENCIL_بفر_BIT4_QCOM       0x00100000
#تعریف_کړه GL_STENCIL_بفر_BIT5_QCOM       0x00200000
#تعریف_کړه GL_STENCIL_بفر_BIT6_QCOM       0x00400000
#تعریف_کړه GL_STENCIL_بفر_BIT7_QCOM       0x00800000
#تعریف_کړه GL_MULTISAMPLE_بفر_BIT0_QCOM   0x01000000
#تعریف_کړه GL_MULTISAMPLE_بفر_BIT1_QCOM   0x02000000
#تعریف_کړه GL_MULTISAMPLE_بفر_BIT2_QCOM   0x04000000
#تعریف_کړه GL_MULTISAMPLE_بفر_BIT3_QCOM   0x08000000
#تعریف_کړه GL_MULTISAMPLE_بفر_BIT4_QCOM   0x10000000
#تعریف_کړه GL_MULTISAMPLE_بفر_BIT5_QCOM   0x20000000
#تعریف_کړه GL_MULTISAMPLE_بفر_BIT6_QCOM   0x40000000
#تعریف_کړه GL_MULTISAMPLE_بفر_BIT7_QCOM   0x80000000
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTARTTILINGQCOMPROC) (GLuint x, GLuint y, GLuint پلنوالی, GLuint لوړوالی, GLbitfield preserve_ماسک);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENDTILINGQCOMPROC) (GLbitfield preserve_ماسک);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_پیل_Tiling_QCOM (GLuint x, GLuint y, GLuint پلنوالی, GLuint لوړوالی, GLbitfield preserve_ماسک);
GL_APICALL فراغ GL_APIENTRY gl_پای_ټکی_Tiling_QCOM (GLbitfield preserve_ماسک);
#د_که_پای
#د_که_پای /* GL_QCOM_tiled_rendering */

#که_نه_تعریف_شوی GL_QCOM_writeonly_rendering
#تعریف_کړه GL_QCOM_writeonly_rendering 1
#تعریف_کړه GL_WRITEONLY_RENDERING_QCOM       0x8823
#د_که_پای /* GL_QCOM_writeonly_rendering */

#که_نه_تعریف_شوی GL_QCOM_ycbcr_degamma
#تعریف_کړه GL_QCOM_ycbcr_degamma 1
#تعریف_کړه GL_TEXTURE_Y_DEGAMMA_QCOM         0x9710
#تعریف_کړه GL_TEXTURE_CBCR_DEGAMMA_QCOM      0x9711
#د_که_پای /* GL_QCOM_ycbcr_degamma */

#که_نه_تعریف_شوی GL_VIV_shader_دوګونی
#تعریف_کړه GL_VIV_shader_دوګونی 1
#تعریف_کړه GL_SHADER_دوګونی_VIV              0x8FC4
#د_که_پای /* GL_VIV_shader_binary */

#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای
