#اگر_تعریف_نشده __gles2_gl2ext_h_
#تعریف_کن __gles2_gl2ext_h_ 1

#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر

/*
** Copyright 2013-2026 The Khronos Group Inc.
** SPDX-License-Identifier: MIT
**
** This header is generated from the Khronos OpenGL / OpenGL ES XML
** API Registry. The current version of the Registry, generator scripts
** used to make the header, and the header can be found at
**   https://github.com/KhronosGroup/OpenGL-Registry
*/

#اگر_تعریف_نشده GL_APIENTRYP
#تعریف_کن GL_APIENTRYP GL_APIENTRY*
#پایان_اگر

#تعریف_کن GL_GLEXT_نسخه 20260803

/* Generated C header for:
 * API: gles2
 * Profile: common
 * Versions considered: 2\.[0-9]
 * Versions emitted: _nomatch_^
 * Default extensions included: gles2
 * Additional extensions included: _nomatch_^
 * Extensions removed: _nomatch_^
 */

#اگر_تعریف_نشده GL_KHR_blend_equation_advanced
#تعریف_کن GL_KHR_blend_equation_advanced 1
#تعریف_کن GL_MULTIPLY_KHR                   0x9294
#تعریف_کن GL_SCREEN_KHR                     0x9295
#تعریف_کن GL_OVERLAY_KHR                    0x9296
#تعریف_کن GL_DARKEN_KHR                     0x9297
#تعریف_کن GL_LIGHTEN_KHR                    0x9298
#تعریف_کن GL_COLORDODGE_KHR                 0x9299
#تعریف_کن GL_COLORBURN_KHR                  0x929A
#تعریف_کن GL_HARDLIGHT_KHR                  0x929B
#تعریف_کن GL_SOFTLIGHT_KHR                  0x929C
#تعریف_کن GL_DIFFERENCE_KHR                 0x929E
#تعریف_کن GL_EXCLUSION_KHR                  0x92A0
#تعریف_کن GL_HSL_HUE_KHR                    0x92AD
#تعریف_کن GL_HSL_SATURATION_KHR             0x92AE
#تعریف_کن GL_HSL_COLOR_KHR                  0x92AF
#تعریف_کن GL_HSL_LUMINOSITY_KHR             0x92B0
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDBARRIERKHRPROC) (فراغ);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glBlendBarrierKHR (فراغ);
#پایان_اگر
#پایان_اگر /* GL_KHR_blend_equation_advanced */

#اگر_تعریف_نشده GL_KHR_blend_equation_advanced_coherent
#تعریف_کن GL_KHR_blend_equation_advanced_coherent 1
#تعریف_کن GL_BLEND_ADVANCED_COHERENT_KHR    0x9285
#پایان_اگر /* GL_KHR_blend_equation_advanced_coherent */

#اگر_تعریف_نشده GL_KHR_context_flush_control
#تعریف_کن GL_KHR_context_flush_control 1
#تعریف_کن GL_CONTEXT_RELEASE_BEHAVIOR_KHR   0x82FB
#تعریف_کن GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_KHR 0x82FC
#پایان_اگر /* GL_KHR_context_flush_control */

#اگر_تعریف_نشده GL_KHR_debug
#تعریف_کن GL_KHR_debug 1
تعريفنوع فراغ (GL_APIENTRY  *GLDEBUGPROCKHR)(GLenum منبع,GLenum type,GLuint id,GLenum severity,GLsizei درازی,ثابت GLchar *پیام,ثابت فراغ *userParam);
#تعریف_کن GL_SAMPLER                        0x82E6
#تعریف_کن GL_DEBUG_OUTPUT_SYNCHRONOUS_KHR   0x8242
#تعریف_کن GL_DEBUG_بعدی_LOGGED_پیام_درازی_KHR 0x8243
#تعریف_کن GL_DEBUG_CALLBACK_FUNCTION_KHR    0x8244
#تعریف_کن GL_DEBUG_CALLBACK_USER_PARAM_KHR  0x8245
#تعریف_کن GL_DEBUG_منبع_API_KHR           0x8246
#تعریف_کن GL_DEBUG_منبع_پنجره_SYSTEM_KHR 0x8247
#تعریف_کن GL_DEBUG_منبع_SHADER_COMPILER_KHR 0x8248
#تعریف_کن GL_DEBUG_منبع_سوم_PARTY_KHR   0x8249
#تعریف_کن GL_DEBUG_منبع_APPLICATION_KHR   0x824A
#تعریف_کن GL_DEBUG_منبع_OTHER_KHR         0x824B
#تعریف_کن GL_DEBUG_TYPE_ERROR_KHR           0x824C
#تعریف_کن GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_KHR 0x824D
#تعریف_کن GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_KHR 0x824E
#تعریف_کن GL_DEBUG_TYPE_PORTABILITY_KHR     0x824F
#تعریف_کن GL_DEBUG_TYPE_PERFORMANCE_KHR     0x8250
#تعریف_کن GL_DEBUG_TYPE_OTHER_KHR           0x8251
#تعریف_کن GL_DEBUG_TYPE_MARKER_KHR          0x8268
#تعریف_کن GL_DEBUG_TYPE_افزودن_گروه_KHR      0x8269
#تعریف_کن GL_DEBUG_TYPE_برداشت_گروه_KHR       0x826A
#تعریف_کن GL_DEBUG_SEVERITY_NOTIFICATION_KHR 0x826B
#تعریف_کن GL_MAX_DEBUG_گروه_پشته_عمق_KHR 0x826C
#تعریف_کن GL_DEBUG_گروه_پشته_عمق_KHR    0x826D
#تعریف_کن GL_میانگیر_KHR                     0x82E0
#تعریف_کن GL_SHADER_KHR                     0x82E1
#تعریف_کن GL_برنامه_KHR                    0x82E2
#تعریف_کن GL_رأس_ARRAY_KHR               0x8074
#تعریف_کن GL_QUERY_KHR                      0x82E3
#تعریف_کن GL_برنامه_PIPELINE_KHR           0x82E4
#تعریف_کن GL_SAMPLER_KHR                    0x82E6
#تعریف_کن GL_MAX_LABEL_درازی_KHR           0x82E8
#تعریف_کن GL_MAX_DEBUG_پیام_درازی_KHR   0x9143
#تعریف_کن GL_MAX_DEBUG_LOGGED_MESSAGES_KHR  0x9144
#تعریف_کن GL_DEBUG_LOGGED_MESSAGES_KHR      0x9145
#تعریف_کن GL_DEBUG_SEVERITY_بالا_KHR        0x9146
#تعریف_کن GL_DEBUG_SEVERITY_MEDIUM_KHR      0x9147
#تعریف_کن GL_DEBUG_SEVERITY_کم_KHR         0x9148
#تعریف_کن GL_DEBUG_OUTPUT_KHR               0x92E0
#تعریف_کن GL_CONTEXT_FLAG_DEBUG_بیت_KHR     0x00000002
#تعریف_کن GL_پشته_سرریز_KHR             0x0503
#تعریف_کن GL_پشته_UNDERFLOW_KHR            0x0504
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEBUGMESSAGECONTROLKHRPROC) (GLenum منبع, GLenum type, GLenum severity, GLsizei شمار, ثابت GLuint *ids, GLboolean enabled);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEBUGMESSAGEINSERTKHRPROC) (GLenum منبع, GLenum type, GLuint id, GLenum severity, GLsizei درازی, ثابت GLchar *buf);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEBUGMESSAGECALLBACKKHRPROC) (GLDEBUGPROCKHR callback, ثابت فراغ *userParam);
تعريفنوع GLuint (GL_APIENTRYP PFNGLGETDEBUGMESSAGELOGKHRPROC) (GLuint شمار, GLsizei buf_اندازه, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *پیام_Log);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPUSHDEBUGGROUPKHRPROC) (GLenum منبع, GLuint id, GLsizei درازی, ثابت GLchar *پیام);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOPDEBUGGROUPKHRPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLOBJECTLABELKHRPROC) (GLenum identifier, GLuint name, GLsizei درازی, ثابت GLchar *label);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETOBJECTLABELKHRPROC) (GLenum identifier, GLuint name, GLsizei buf_اندازه, GLsizei *درازی, GLchar *label);
تعريفنوع فراغ (GL_APIENTRYP PFNGLOBJECTPTRLABELKHRPROC) (ثابت فراغ *ptr, GLsizei درازی, ثابت GLchar *label);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETOBJECTPTRLABELKHRPROC) (ثابت فراغ *ptr, GLsizei buf_اندازه, GLsizei *درازی, GLchar *label);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPOINTERVKHRPROC) (GLenum pname, فراغ **params);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Debug_پیام_Control_KHR (GLenum منبع, GLenum type, GLenum severity, GLsizei شمار, ثابت GLuint *ids, GLboolean enabled);
GL_APICALL فراغ GL_APIENTRY gl_Debug_پیام_درج_KHR (GLenum منبع, GLenum type, GLuint id, GLenum severity, GLsizei درازی, ثابت GLchar *buf);
GL_APICALL فراغ GL_APIENTRY gl_Debug_پیام_Callback_KHR (GLDEBUGPROCKHR callback, ثابت فراغ *userParam);
GL_APICALL GLuint GL_APIENTRY gl_Get_Debug_پیام_Log_KHR (GLuint شمار, GLsizei buf_اندازه, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *پیام_Log);
GL_APICALL فراغ GL_APIENTRY gl_افزودن_Debug_گروه_KHR (GLenum منبع, GLuint id, GLsizei درازی, ثابت GLchar *پیام);
GL_APICALL فراغ GL_APIENTRY gl_برداشت_Debug_گروه_KHR (فراغ);
GL_APICALL فراغ GL_APIENTRY glObjectLabelKHR (GLenum identifier, GLuint name, GLsizei درازی, ثابت GLchar *label);
GL_APICALL فراغ GL_APIENTRY glGetObjectLabelKHR (GLenum identifier, GLuint name, GLsizei buf_اندازه, GLsizei *درازی, GLchar *label);
GL_APICALL فراغ GL_APIENTRY glObjectPtrLabelKHR (ثابت فراغ *ptr, GLsizei درازی, ثابت GLchar *label);
GL_APICALL فراغ GL_APIENTRY glGetObjectPtrLabelKHR (ثابت فراغ *ptr, GLsizei buf_اندازه, GLsizei *درازی, GLchar *label);
GL_APICALL فراغ GL_APIENTRY glGetPointervKHR (GLenum pname, فراغ **params);
#پایان_اگر
#پایان_اگر /* GL_KHR_debug */

#اگر_تعریف_نشده GL_KHR_no_error
#تعریف_کن GL_KHR_no_error 1
#تعریف_کن GL_CONTEXT_FLAG_NO_ERROR_بیت_KHR  0x00000008
#پایان_اگر /* GL_KHR_no_error */

#اگر_تعریف_نشده GL_KHR_parallel_shader_compile
#تعریف_کن GL_KHR_parallel_shader_compile 1
#تعریف_کن GL_MAX_SHADER_COMPILER_نخها_KHR 0x91B0
#تعریف_کن GL_COMPLETION_وضعیت_KHR          0x91B1
تعريفنوع فراغ (GL_APIENTRYP PFNGLMAXSHADERCOMPILERTHREADSKHRPROC) (GLuint شمار);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Max_Shader_Compiler_نخها_KHR (GLuint شمار);
#پایان_اگر
#پایان_اگر /* GL_KHR_parallel_shader_compile */

#اگر_تعریف_نشده GL_KHR_robust_میانگیر_access_behavior
#تعریف_کن GL_KHR_robust_میانگیر_access_behavior 1
#پایان_اگر /* GL_KHR_robust_buffer_access_behavior */

#اگر_تعریف_نشده GL_KHR_robustness
#تعریف_کن GL_KHR_robustness 1
#تعریف_کن GL_CONTEXT_ROBUST_ACCESS_KHR      0x90F3
#تعریف_کن GL_LOSE_CONTEXT_ON_RESET_KHR      0x8252
#تعریف_کن GL_GUILTY_CONTEXT_RESET_KHR       0x8253
#تعریف_کن GL_INNOCENT_CONTEXT_RESET_KHR     0x8254
#تعریف_کن GL_UNKNOWN_CONTEXT_RESET_KHR      0x8255
#تعریف_کن GL_RESET_NOTIFICATION_STRATEGY_KHR 0x8256
#تعریف_کن GL_NO_RESET_NOTIFICATION_KHR      0x8261
#تعریف_کن GL_CONTEXT_گمشده_KHR               0x0507
تعريفنوع GLenum (GL_APIENTRYP PFNGLGETGRAPHICSRESETSTATUSKHRPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLREADNPIXELSKHRPROC) (GLint x, GLint y, GLsizei عرض, GLsizei ارتفاع, GLenum format, GLenum type, GLsizei buf_اندازه, فراغ *داده);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNUNIFORMFVKHRPROC) (GLuint برنامه, GLint location, GLsizei buf_اندازه, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNUNIFORMIVKHRPROC) (GLuint برنامه, GLint location, GLsizei buf_اندازه, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNUNIFORMUIVKHRPROC) (GLuint برنامه, GLint location, GLsizei buf_اندازه, GLuint *params);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL GLenum GL_APIENTRY gl_Get_Graphics_Reset_وضعیت_KHR (فراغ);
GL_APICALL فراغ GL_APIENTRY glReadnPixelsKHR (GLint x, GLint y, GLsizei عرض, GLsizei ارتفاع, GLenum format, GLenum type, GLsizei buf_اندازه, فراغ *داده);
GL_APICALL فراغ GL_APIENTRY glGetnUniformfvKHR (GLuint برنامه, GLint location, GLsizei buf_اندازه, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY glGetnUniformivKHR (GLuint برنامه, GLint location, GLsizei buf_اندازه, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetnUniformuivKHR (GLuint برنامه, GLint location, GLsizei buf_اندازه, GLuint *params);
#پایان_اگر
#پایان_اگر /* GL_KHR_robustness */

#اگر_تعریف_نشده GL_KHR_shader_subgroup
#تعریف_کن GL_KHR_shader_subgroup 1
#تعریف_کن GL_SUBGROUP_اندازه_KHR              0x9532
#تعریف_کن GL_SUBGROUP_SUPPORTED_STAGES_KHR  0x9533
#تعریف_کن GL_SUBGROUP_SUPPORTED_FEATURES_KHR 0x9534
#تعریف_کن GL_SUBGROUP_QUAD_ALL_STAGES_KHR   0x9535
#تعریف_کن GL_SUBGROUP_FEATURE_BASIC_بیت_KHR 0x00000001
#تعریف_کن GL_SUBGROUP_FEATURE_VOTE_بیت_KHR  0x00000002
#تعریف_کن GL_SUBGROUP_FEATURE_ARITHMETIC_بیت_KHR 0x00000004
#تعریف_کن GL_SUBGROUP_FEATURE_BALLOT_بیت_KHR 0x00000008
#تعریف_کن GL_SUBGROUP_FEATURE_SHUFFLE_بیت_KHR 0x00000010
#تعریف_کن GL_SUBGROUP_FEATURE_SHUFFLE_RELATIVE_بیت_KHR 0x00000020
#تعریف_کن GL_SUBGROUP_FEATURE_CLUSTERED_بیت_KHR 0x00000040
#تعریف_کن GL_SUBGROUP_FEATURE_QUAD_بیت_KHR  0x00000080
#پایان_اگر /* GL_KHR_shader_subgroup */

#اگر_تعریف_نشده GL_KHR_texture_compression_astc_hdr
#تعریف_کن GL_KHR_texture_compression_astc_hdr 1
#تعریف_کن GL_COMPRESSED_RGBA_ASTC_4x4_KHR   0x93B0
#تعریف_کن GL_COMPRESSED_RGBA_ASTC_5x4_KHR   0x93B1
#تعریف_کن GL_COMPRESSED_RGBA_ASTC_5x5_KHR   0x93B2
#تعریف_کن GL_COMPRESSED_RGBA_ASTC_6x5_KHR   0x93B3
#تعریف_کن GL_COMPRESSED_RGBA_ASTC_6x6_KHR   0x93B4
#تعریف_کن GL_COMPRESSED_RGBA_ASTC_8x5_KHR   0x93B5
#تعریف_کن GL_COMPRESSED_RGBA_ASTC_8x6_KHR   0x93B6
#تعریف_کن GL_COMPRESSED_RGBA_ASTC_8x8_KHR   0x93B7
#تعریف_کن GL_COMPRESSED_RGBA_ASTC_10x5_KHR  0x93B8
#تعریف_کن GL_COMPRESSED_RGBA_ASTC_10x6_KHR  0x93B9
#تعریف_کن GL_COMPRESSED_RGBA_ASTC_10x8_KHR  0x93BA
#تعریف_کن GL_COMPRESSED_RGBA_ASTC_10x10_KHR 0x93BB
#تعریف_کن GL_COMPRESSED_RGBA_ASTC_12x10_KHR 0x93BC
#تعریف_کن GL_COMPRESSED_RGBA_ASTC_12x12_KHR 0x93BD
#تعریف_کن GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR 0x93D0
#تعریف_کن GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR 0x93D1
#تعریف_کن GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR 0x93D2
#تعریف_کن GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR 0x93D3
#تعریف_کن GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR 0x93D4
#تعریف_کن GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR 0x93D5
#تعریف_کن GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR 0x93D6
#تعریف_کن GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR 0x93D7
#تعریف_کن GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR 0x93D8
#تعریف_کن GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR 0x93D9
#تعریف_کن GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR 0x93DA
#تعریف_کن GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR 0x93DB
#تعریف_کن GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR 0x93DC
#تعریف_کن GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR 0x93DD
#پایان_اگر /* GL_KHR_texture_compression_astc_hdr */

#اگر_تعریف_نشده GL_KHR_texture_compression_astc_ldr
#تعریف_کن GL_KHR_texture_compression_astc_ldr 1
#پایان_اگر /* GL_KHR_texture_compression_astc_ldr */

#اگر_تعریف_نشده GL_KHR_texture_compression_astc_sliced_3d
#تعریف_کن GL_KHR_texture_compression_astc_sliced_3d 1
#پایان_اگر /* GL_KHR_texture_compression_astc_sliced_3d */

#اگر_تعریف_نشده GL_OES_EGL_image
#تعریف_کن GL_OES_EGL_image 1
تعريفنوع فراغ *GLeglImageOES;
تعريفنوع فراغ (GL_APIENTRYP PFNGLEGLIMAGETARGETTEXTURE2DOESPROC) (GLenum هدف, GLeglImageOES image);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEGLIMAGETARGETRENDERBUFFERSTORAGEOESPROC) (GLenum هدف, GLeglImageOES image);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_EGLImage_هدف_Texture2_DOES (GLenum هدف, GLeglImageOES image);
GL_APICALL فراغ GL_APIENTRY gl_EGLImage_هدف_Renderbuffer_Storage_OES (GLenum هدف, GLeglImageOES image);
#پایان_اگر
#پایان_اگر /* GL_OES_EGL_image */

#اگر_تعریف_نشده GL_OES_EGL_image_external
#تعریف_کن GL_OES_EGL_image_external 1
#تعریف_کن GL_TEXTURE_EXTERNAL_OES           0x8D65
#تعریف_کن GL_TEXTURE_BINDING_EXTERNAL_OES   0x8D67
#تعریف_کن GL_REQUIRED_TEXTURE_IMAGE_UNITS_OES 0x8D68
#تعریف_کن GL_SAMPLER_EXTERNAL_OES           0x8D66
#پایان_اگر /* GL_OES_EGL_image_external */

#اگر_تعریف_نشده GL_OES_EGL_image_external_essl3
#تعریف_کن GL_OES_EGL_image_external_essl3 1
#پایان_اگر /* GL_OES_EGL_image_external_essl3 */

#اگر_تعریف_نشده GL_OES_compressed_ETC1_RGB8_sub_texture
#تعریف_کن GL_OES_compressed_ETC1_RGB8_sub_texture 1
#پایان_اگر /* GL_OES_compressed_ETC1_RGB8_sub_texture */

#اگر_تعریف_نشده GL_OES_compressed_ETC1_RGB8_texture
#تعریف_کن GL_OES_compressed_ETC1_RGB8_texture 1
#تعریف_کن GL_ETC1_RGB8_OES                  0x8D64
#پایان_اگر /* GL_OES_compressed_ETC1_RGB8_texture */

#اگر_تعریف_نشده GL_OES_compressed_paletted_texture
#تعریف_کن GL_OES_compressed_paletted_texture 1
#تعریف_کن GL_PALETTE4_RGB8_OES              0x8B90
#تعریف_کن GL_PALETTE4_RGBA8_OES             0x8B91
#تعریف_کن GL_PALETTE4_R5_G6_B5_OES          0x8B92
#تعریف_کن GL_PALETTE4_RGBA4_OES             0x8B93
#تعریف_کن GL_PALETTE4_RGB5_A1_OES           0x8B94
#تعریف_کن GL_PALETTE8_RGB8_OES              0x8B95
#تعریف_کن GL_PALETTE8_RGBA8_OES             0x8B96
#تعریف_کن GL_PALETTE8_R5_G6_B5_OES          0x8B97
#تعریف_کن GL_PALETTE8_RGBA4_OES             0x8B98
#تعریف_کن GL_PALETTE8_RGB5_A1_OES           0x8B99
#پایان_اگر /* GL_OES_compressed_paletted_texture */

#اگر_تعریف_نشده GL_OES_copy_image
#تعریف_کن GL_OES_copy_image 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYIMAGESUBDATAOESPROC) (GLuint srcName, GLenum src_هدف, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dst_هدف, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei src_عرض, GLsizei src_ارتفاع, GLsizei src_عمق);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Copy_Image_Sub_داده_OES (GLuint srcName, GLenum src_هدف, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dst_هدف, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei src_عرض, GLsizei src_ارتفاع, GLsizei src_عمق);
#پایان_اگر
#پایان_اگر /* GL_OES_copy_image */

#اگر_تعریف_نشده GL_OES_depth24
#تعریف_کن GL_OES_depth24 1
#تعریف_کن GL_عمق_COMPONENT24_OES          0x81A6
#پایان_اگر /* GL_OES_depth24 */

#اگر_تعریف_نشده GL_OES_depth32
#تعریف_کن GL_OES_depth32 1
#تعریف_کن GL_عمق_COMPONENT32_OES          0x81A7
#پایان_اگر /* GL_OES_depth32 */

#اگر_تعریف_نشده GL_OES_عمق_texture
#تعریف_کن GL_OES_عمق_texture 1
#پایان_اگر /* GL_OES_depth_texture */

#اگر_تعریف_نشده GL_OES_draw_buffers_نمایهای
#تعریف_کن GL_OES_draw_buffers_نمایهای 1
#تعریف_کن GL_MIN                            0x8007
#تعریف_کن GL_MAX                            0x8008
تعريفنوع فراغ (GL_APIENTRYP PFNGLENABLEIOESPROC) (GLenum هدف, GLuint شاخص);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISABLEIOESPROC) (GLenum هدف, GLuint شاخص);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONIOESPROC) (GLuint buf, GLenum نما);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEIOESPROC) (GLuint buf, GLenum نما_RGB, GLenum نما_Alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDFUNCIOESPROC) (GLuint buf, GLenum src, GLenum dst);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEIOESPROC) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOLORMASKIOESPROC) (GLuint شاخص, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISENABLEDIOESPROC) (GLenum هدف, GLuint شاخص);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glEnableiOES (GLenum هدف, GLuint شاخص);
GL_APICALL فراغ GL_APIENTRY glDisableiOES (GLenum هدف, GLuint شاخص);
GL_APICALL فراغ GL_APIENTRY glBlendEquationiOES (GLuint buf, GLenum نما);
GL_APICALL فراغ GL_APIENTRY glBlendEquationSeparateiOES (GLuint buf, GLenum نما_RGB, GLenum نما_Alpha);
GL_APICALL فراغ GL_APIENTRY glBlendFunciOES (GLuint buf, GLenum src, GLenum dst);
GL_APICALL فراغ GL_APIENTRY glBlendFuncSeparateiOES (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
GL_APICALL فراغ GL_APIENTRY glColorMaskiOES (GLuint شاخص, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
GL_APICALL GLboolean GL_APIENTRY glIsEnablediOES (GLenum هدف, GLuint شاخص);
#پایان_اگر
#پایان_اگر /* GL_OES_draw_buffers_indexed */

#اگر_تعریف_نشده GL_OES_draw_elements_پایه_رأس
#تعریف_کن GL_OES_draw_elements_پایه_رأس 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSBASEVERTEXOESPROC) (GLenum نما, GLsizei شمار, GLenum type, ثابت فراغ *indices, GLint basevertex);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWRANGEELEMENTSBASEVERTEXOESPROC) (GLenum نما, GLuint شروع, GLuint انتها, GLsizei شمار, GLenum type, ثابت فراغ *indices, GLint basevertex);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXOESPROC) (GLenum نما, GLsizei شمار, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLint basevertex);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSBASEVERTEXEXTPROC) (GLenum نما, ثابت GLsizei *شمار, GLenum type, ثابت فراغ *ثابت*indices, GLsizei drawcount, ثابت GLint *basevertex);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Draw_Elements_پایه_رأس_OES (GLenum نما, GLsizei شمار, GLenum type, ثابت فراغ *indices, GLint basevertex);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Range_Elements_پایه_رأس_OES (GLenum نما, GLuint شروع, GLuint انتها, GLsizei شمار, GLenum type, ثابت فراغ *indices, GLint basevertex);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Elements_Instanced_پایه_رأس_OES (GLenum نما, GLsizei شمار, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLint basevertex);
GL_APICALL فراغ GL_APIENTRY gl_Multi_Draw_Elements_پایه_رأس_EXT (GLenum نما, ثابت GLsizei *شمار, GLenum type, ثابت فراغ *ثابت*indices, GLsizei drawcount, ثابت GLint *basevertex);
#پایان_اگر
#پایان_اگر /* GL_OES_draw_elements_base_vertex */

#اگر_تعریف_نشده GL_OES_element_شاخص_uint
#تعریف_کن GL_OES_element_شاخص_uint 1
#پایان_اگر /* GL_OES_element_index_uint */

#اگر_تعریف_نشده GL_OES_fbo_render_mipmap
#تعریف_کن GL_OES_fbo_render_mipmap 1
#پایان_اگر /* GL_OES_fbo_render_mipmap */

#اگر_تعریف_نشده GL_OES_fragment_precision_بالا
#تعریف_کن GL_OES_fragment_precision_بالا 1
#پایان_اگر /* GL_OES_fragment_precision_high */

#اگر_تعریف_نشده GL_OES_geometry_نقطه_اندازه
#تعریف_کن GL_OES_geometry_نقطه_اندازه 1
#پایان_اگر /* GL_OES_geometry_point_size */

#اگر_تعریف_نشده GL_OES_geometry_shader
#تعریف_کن GL_OES_geometry_shader 1
#تعریف_کن GL_GEOMETRY_SHADER_OES            0x8DD9
#تعریف_کن GL_GEOMETRY_SHADER_بیت_OES        0x00000004
#تعریف_کن GL_GEOMETRY_LINKED_VERTICES_بیرون_OES 0x8916
#تعریف_کن GL_GEOMETRY_LINKED_درون_داد_TYPE_OES 0x8917
#تعریف_کن GL_GEOMETRY_LINKED_OUTPUT_TYPE_OES 0x8918
#تعریف_کن GL_GEOMETRY_SHADER_INVOCATIONS_OES 0x887F
#تعریف_کن GL_LAYER_PROVOKING_رأس_OES     0x825E
#تعریف_کن GL_سطرها_ADJACENCY_OES            0x000A
#تعریف_کن GL_سطر_STRIP_ADJACENCY_OES       0x000B
#تعریف_کن GL_TRIANGLES_ADJACENCY_OES        0x000C
#تعریف_کن GL_TRIANGLE_STRIP_ADJACENCY_OES   0x000D
#تعریف_کن GL_MAX_GEOMETRY_یکنواخت_COMPONENTS_OES 0x8DDF
#تعریف_کن GL_MAX_GEOMETRY_یکنواخت_بلوکها_OES 0x8A2C
#تعریف_کن GL_MAX_COMBINED_GEOMETRY_یکنواخت_COMPONENTS_OES 0x8A32
#تعریف_کن GL_MAX_GEOMETRY_درون_داد_COMPONENTS_OES 0x9123
#تعریف_کن GL_MAX_GEOMETRY_OUTPUT_COMPONENTS_OES 0x9124
#تعریف_کن GL_MAX_GEOMETRY_OUTPUT_VERTICES_OES 0x8DE0
#تعریف_کن GL_MAX_GEOMETRY_مجموع_OUTPUT_COMPONENTS_OES 0x8DE1
#تعریف_کن GL_MAX_GEOMETRY_SHADER_INVOCATIONS_OES 0x8E5A
#تعریف_کن GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_OES 0x8C29
#تعریف_کن GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS_OES 0x92CF
#تعریف_کن GL_MAX_GEOMETRY_ATOMIC_COUNTERS_OES 0x92D5
#تعریف_کن GL_MAX_GEOMETRY_IMAGE_UNIFORMS_OES 0x90CD
#تعریف_کن GL_MAX_GEOMETRY_SHADER_STORAGE_بلوکها_OES 0x90D7
#تعریف_کن GL_اولی_رأس_CONVENTION_OES    0x8E4D
#تعریف_کن GL_آخرین_رأس_CONVENTION_OES     0x8E4E
#تعریف_کن GL_UNDEFINED_رأس_OES           0x8260
#تعریف_کن GL_PRIMITIVES_GENERATED_OES       0x8C87
#تعریف_کن GL_FRAMEBUFFER_DEFAULT_LAYERS_OES 0x9312
#تعریف_کن GL_MAX_FRAMEBUFFER_LAYERS_OES     0x9317
#تعریف_کن GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_OES 0x8DA8
#تعریف_کن GL_FRAMEBUFFER_ATTACHMENT_LAYERED_OES 0x8DA7
#تعریف_کن GL_REFERENCED_BY_GEOMETRY_SHADER_OES 0x9309
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREOESPROC) (GLenum هدف, GLenum attachment, GLuint texture, GLint level);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferTextureOES (GLenum هدف, GLenum attachment, GLuint texture, GLint level);
#پایان_اگر
#پایان_اگر /* GL_OES_geometry_shader */

#اگر_تعریف_نشده GL_OES_get_برنامه_دودویی
#تعریف_کن GL_OES_get_برنامه_دودویی 1
#تعریف_کن GL_برنامه_دودویی_درازی_OES      0x8741
#تعریف_کن GL_رقم_برنامه_دودویی_FORMATS_OES 0x87FE
#تعریف_کن GL_برنامه_دودویی_FORMATS_OES     0x87FF
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMBINARYOESPROC) (GLuint برنامه, GLsizei buf_اندازه, GLsizei *درازی, GLenum *دودویی_Format, فراغ *دودویی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMBINARYOESPROC) (GLuint برنامه, GLenum دودویی_Format, ثابت فراغ *دودویی, GLint درازی);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Get_برنامه_دودویی_OES (GLuint برنامه, GLsizei buf_اندازه, GLsizei *درازی, GLenum *دودویی_Format, فراغ *دودویی);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_دودویی_OES (GLuint برنامه, GLenum دودویی_Format, ثابت فراغ *دودویی, GLint درازی);
#پایان_اگر
#پایان_اگر /* GL_OES_get_program_binary */

#اگر_تعریف_نشده GL_OES_gpu_shader5
#تعریف_کن GL_OES_gpu_shader5 1
#پایان_اگر /* GL_OES_gpu_shader5 */

#اگر_تعریف_نشده GL_OES_mapbuffer
#تعریف_کن GL_OES_mapbuffer 1
#تعریف_کن GL_WRITE_ONLY_OES                 0x88B9
#تعریف_کن GL_میانگیر_ACCESS_OES              0x88BB
#تعریف_کن GL_میانگیر_MAPPED_OES              0x88BC
#تعریف_کن GL_میانگیر_MAP_اشاره_گر_OES         0x88BD
تعريفنوع فراغ *(GL_APIENTRYP PFNGLMAPBUFFEROESPROC) (GLenum هدف, GLenum access);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLUNMAPBUFFEROESPROC) (GLenum هدف);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETBUFFERPOINTERVOESPROC) (GLenum هدف, GLenum pname, فراغ **params);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ *GL_APIENTRY gl_Map_میانگیر_OES (GLenum هدف, GLenum access);
GL_APICALL GLboolean GL_APIENTRY gl_Unmap_میانگیر_OES (GLenum هدف);
GL_APICALL فراغ GL_APIENTRY gl_Get_میانگیر_Pointerv_OES (GLenum هدف, GLenum pname, فراغ **params);
#پایان_اگر
#پایان_اگر /* GL_OES_mapbuffer */

#اگر_تعریف_نشده GL_OES_packed_عمق_stencil
#تعریف_کن GL_OES_packed_عمق_stencil 1
#تعریف_کن GL_عمق_STENCIL_OES              0x84F9
#تعریف_کن GL_UNSIGNED_INT_24_8_OES          0x84FA
#تعریف_کن GL_DEPTH24_STENCIL8_OES           0x88F0
#پایان_اگر /* GL_OES_packed_depth_stencil */

#اگر_تعریف_نشده GL_OES_primitive_bounding_box
#تعریف_کن GL_OES_primitive_bounding_box 1
#تعریف_کن GL_PRIMITIVE_BOUNDING_BOX_OES     0x92BE
تعريفنوع فراغ (GL_APIENTRYP PFNGLPRIMITIVEBOUNDINGBOXOESPROC) (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glPrimitiveBoundingBoxOES (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
#پایان_اگر
#پایان_اگر /* GL_OES_primitive_bounding_box */

#اگر_تعریف_نشده GL_OES_required_internalformat
#تعریف_کن GL_OES_required_internalformat 1
#تعریف_کن GL_ALPHA8_OES                     0x803C
#تعریف_کن GL_عمق_COMPONENT16_OES          0x81A5
#تعریف_کن GL_LUMINANCE4_ALPHA4_OES          0x8043
#تعریف_کن GL_LUMINANCE8_ALPHA8_OES          0x8045
#تعریف_کن GL_LUMINANCE8_OES                 0x8040
#تعریف_کن GL_RGBA4_OES                      0x8056
#تعریف_کن GL_RGB5_A1_OES                    0x8057
#تعریف_کن GL_RGB565_OES                     0x8D62
#تعریف_کن GL_RGB8_OES                       0x8051
#تعریف_کن GL_RGBA8_OES                      0x8058
#تعریف_کن GL_RGB10_EXT                      0x8052
#تعریف_کن GL_RGB10_A2_EXT                   0x8059
#پایان_اگر /* GL_OES_required_internalformat */

#اگر_تعریف_نشده GL_OES_rgb8_rgba8
#تعریف_کن GL_OES_rgb8_rgba8 1
#پایان_اگر /* GL_OES_rgb8_rgba8 */

#اگر_تعریف_نشده GL_OES_sample_shading
#تعریف_کن GL_OES_sample_shading 1
#تعریف_کن GL_SAMPLE_SHADING_OES             0x8C36
#تعریف_کن GL_MIN_SAMPLE_SHADING_مقدار_OES   0x8C37
تعريفنوع فراغ (GL_APIENTRYP PFNGLMINSAMPLESHADINGOESPROC) (GLfloat مقدار);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glMinSampleShadingOES (GLfloat مقدار);
#پایان_اگر
#پایان_اگر /* GL_OES_sample_shading */

#اگر_تعریف_نشده GL_OES_sample_variables
#تعریف_کن GL_OES_sample_variables 1
#پایان_اگر /* GL_OES_sample_variables */

#اگر_تعریف_نشده GL_OES_shader_image_atomic
#تعریف_کن GL_OES_shader_image_atomic 1
#پایان_اگر /* GL_OES_shader_image_atomic */

#اگر_تعریف_نشده GL_OES_shader_io_بلوکها
#تعریف_کن GL_OES_shader_io_بلوکها 1
#پایان_اگر /* GL_OES_shader_io_blocks */

#اگر_تعریف_نشده GL_OES_shader_multisample_interpolation
#تعریف_کن GL_OES_shader_multisample_interpolation 1
#تعریف_کن GL_MIN_FRAGMENT_INTERPOLATION_جابه_جایی_OES 0x8E5B
#تعریف_کن GL_MAX_FRAGMENT_INTERPOLATION_جابه_جایی_OES 0x8E5C
#تعریف_کن GL_FRAGMENT_INTERPOLATION_جابه_جایی_بیتها_OES 0x8E5D
#پایان_اگر /* GL_OES_shader_multisample_interpolation */

#اگر_تعریف_نشده GL_OES_standard_derivatives
#تعریف_کن GL_OES_standard_derivatives 1
#تعریف_کن GL_FRAGMENT_SHADER_DERIVATIVE_HINT_OES 0x8B8B
#پایان_اگر /* GL_OES_standard_derivatives */

#اگر_تعریف_نشده GL_OES_stencil1
#تعریف_کن GL_OES_stencil1 1
#تعریف_کن GL_STENCIL_INDEX1_OES             0x8D46
#پایان_اگر /* GL_OES_stencil1 */

#اگر_تعریف_نشده GL_OES_stencil4
#تعریف_کن GL_OES_stencil4 1
#تعریف_کن GL_STENCIL_INDEX4_OES             0x8D47
#پایان_اگر /* GL_OES_stencil4 */

#اگر_تعریف_نشده GL_OES_surfaceless_context
#تعریف_کن GL_OES_surfaceless_context 1
#تعریف_کن GL_FRAMEBUFFER_UNDEFINED_OES      0x8219
#پایان_اگر /* GL_OES_surfaceless_context */

#اگر_تعریف_نشده GL_OES_tessellation_نقطه_اندازه
#تعریف_کن GL_OES_tessellation_نقطه_اندازه 1
#پایان_اگر /* GL_OES_tessellation_point_size */

#اگر_تعریف_نشده GL_OES_tessellation_shader
#تعریف_کن GL_OES_tessellation_shader 1
#تعریف_کن GL_PATCHES_OES                    0x000E
#تعریف_کن GL_PATCH_VERTICES_OES             0x8E72
#تعریف_کن GL_TESS_CONTROL_OUTPUT_VERTICES_OES 0x8E75
#تعریف_کن GL_TESS_GEN_نما_OES              0x8E76
#تعریف_کن GL_TESS_GEN_SPACING_OES           0x8E77
#تعریف_کن GL_TESS_GEN_رأس_ترتیب_OES      0x8E78
#تعریف_کن GL_TESS_GEN_نقطه_نما_OES        0x8E79
#تعریف_کن GL_ISOLINES_OES                   0x8E7A
#تعریف_کن GL_QUADS_OES                      0x0007
#تعریف_کن GL_FRACTIONAL_ODD_OES             0x8E7B
#تعریف_کن GL_FRACTIONAL_EVEN_OES            0x8E7C
#تعریف_کن GL_MAX_PATCH_VERTICES_OES         0x8E7D
#تعریف_کن GL_MAX_TESS_GEN_LEVEL_OES         0x8E7E
#تعریف_کن GL_MAX_TESS_CONTROL_یکنواخت_COMPONENTS_OES 0x8E7F
#تعریف_کن GL_MAX_TESS_EVALUATION_یکنواخت_COMPONENTS_OES 0x8E80
#تعریف_کن GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS_OES 0x8E81
#تعریف_کن GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS_OES 0x8E82
#تعریف_کن GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS_OES 0x8E83
#تعریف_کن GL_MAX_TESS_PATCH_COMPONENTS_OES  0x8E84
#تعریف_کن GL_MAX_TESS_CONTROL_مجموع_OUTPUT_COMPONENTS_OES 0x8E85
#تعریف_کن GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS_OES 0x8E86
#تعریف_کن GL_MAX_TESS_CONTROL_یکنواخت_بلوکها_OES 0x8E89
#تعریف_کن GL_MAX_TESS_EVALUATION_یکنواخت_بلوکها_OES 0x8E8A
#تعریف_کن GL_MAX_TESS_CONTROL_درون_داد_COMPONENTS_OES 0x886C
#تعریف_کن GL_MAX_TESS_EVALUATION_درون_داد_COMPONENTS_OES 0x886D
#تعریف_کن GL_MAX_COMBINED_TESS_CONTROL_یکنواخت_COMPONENTS_OES 0x8E1E
#تعریف_کن GL_MAX_COMBINED_TESS_EVALUATION_یکنواخت_COMPONENTS_OES 0x8E1F
#تعریف_کن GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS_OES 0x92CD
#تعریف_کن GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS_OES 0x92CE
#تعریف_کن GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS_OES 0x92D3
#تعریف_کن GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS_OES 0x92D4
#تعریف_کن GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS_OES 0x90CB
#تعریف_کن GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS_OES 0x90CC
#تعریف_کن GL_MAX_TESS_CONTROL_SHADER_STORAGE_بلوکها_OES 0x90D8
#تعریف_کن GL_MAX_TESS_EVALUATION_SHADER_STORAGE_بلوکها_OES 0x90D9
#تعریف_کن GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED_OES 0x8221
#تعریف_کن GL_IS_در_هر_PATCH_OES               0x92E7
#تعریف_کن GL_REFERENCED_BY_TESS_CONTROL_SHADER_OES 0x9307
#تعریف_کن GL_REFERENCED_BY_TESS_EVALUATION_SHADER_OES 0x9308
#تعریف_کن GL_TESS_CONTROL_SHADER_OES        0x8E88
#تعریف_کن GL_TESS_EVALUATION_SHADER_OES     0x8E87
#تعریف_کن GL_TESS_CONTROL_SHADER_بیت_OES    0x00000008
#تعریف_کن GL_TESS_EVALUATION_SHADER_بیت_OES 0x00000010
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATCHPARAMETERIOESPROC) (GLenum pname, GLint مقدار);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glPatchParameteriOES (GLenum pname, GLint مقدار);
#پایان_اگر
#پایان_اگر /* GL_OES_tessellation_shader */

#اگر_تعریف_نشده GL_OES_texture_3D
#تعریف_کن GL_OES_texture_3D 1
#تعریف_کن GL_TEXTURE_WRAP_R_OES             0x8072
#تعریف_کن GL_TEXTURE_3D_OES                 0x806F
#تعریف_کن GL_TEXTURE_BINDING_3D_OES         0x806A
#تعریف_کن GL_MAX_3_D_TEXTURE_اندازه_OES        0x8073
#تعریف_کن GL_SAMPLER_3D_OES                 0x8B5F
#تعریف_کن GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_3D_ZOFFSET_OES 0x8CD4
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXIMAGE3DOESPROC) (GLenum هدف, GLint level, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLint border, GLenum format, GLenum type, ثابت فراغ *pixels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSUBIMAGE3DOESPROC) (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLenum format, GLenum type, ثابت فراغ *pixels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYTEXSUBIMAGE3DOESPROC) (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei عرض, GLsizei ارتفاع);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOMPRESSEDTEXIMAGE3DOESPROC) (GLenum هدف, GLint level, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLint border, GLsizei image_اندازه, ثابت فراغ *داده);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE3DOESPROC) (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLenum format, GLsizei image_اندازه, ثابت فراغ *داده);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE3DOESPROC) (GLenum هدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTexImage3DOES (GLenum هدف, GLint level, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLint border, GLenum format, GLenum type, ثابت فراغ *pixels);
GL_APICALL فراغ GL_APIENTRY glTexSubImage3DOES (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLenum format, GLenum type, ثابت فراغ *pixels);
GL_APICALL فراغ GL_APIENTRY glCopyTexSubImage3DOES (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei عرض, GLsizei ارتفاع);
GL_APICALL فراغ GL_APIENTRY glCompressedTexImage3DOES (GLenum هدف, GLint level, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLint border, GLsizei image_اندازه, ثابت فراغ *داده);
GL_APICALL فراغ GL_APIENTRY glCompressedTexSubImage3DOES (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLenum format, GLsizei image_اندازه, ثابت فراغ *داده);
GL_APICALL فراغ GL_APIENTRY glFramebufferTexture3DOES (GLenum هدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
#پایان_اگر
#پایان_اگر /* GL_OES_texture_3D */

#اگر_تعریف_نشده GL_OES_texture_border_clamp
#تعریف_کن GL_OES_texture_border_clamp 1
#تعریف_کن GL_TEXTURE_BORDER_COLOR_OES       0x1004
#تعریف_کن GL_CLAMP_مقصد_BORDER_OES            0x812D
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERIIVOESPROC) (GLenum هدف, GLenum pname, ثابت GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERIUIVOESPROC) (GLenum هدف, GLenum pname, ثابت GLuint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXPARAMETERIIVOESPROC) (GLenum هدف, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXPARAMETERIUIVOESPROC) (GLenum هدف, GLenum pname, GLuint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIIVOESPROC) (GLuint sampler, GLenum pname, ثابت GLint *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIUIVOESPROC) (GLuint sampler, GLenum pname, ثابت GLuint *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIIVOESPROC) (GLuint sampler, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIUIVOESPROC) (GLuint sampler, GLenum pname, GLuint *params);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTexParameterIivOES (GLenum هدف, GLenum pname, ثابت GLint *params);
GL_APICALL فراغ GL_APIENTRY glTexParameterIuivOES (GLenum هدف, GLenum pname, ثابت GLuint *params);
GL_APICALL فراغ GL_APIENTRY glGetTexParameterIivOES (GLenum هدف, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetTexParameterIuivOES (GLenum هدف, GLenum pname, GLuint *params);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterIivOES (GLuint sampler, GLenum pname, ثابت GLint *param);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterIuivOES (GLuint sampler, GLenum pname, ثابت GLuint *param);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameterIivOES (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameterIuivOES (GLuint sampler, GLenum pname, GLuint *params);
#پایان_اگر
#پایان_اگر /* GL_OES_texture_border_clamp */

#اگر_تعریف_نشده GL_OES_texture_میانگیر
#تعریف_کن GL_OES_texture_میانگیر 1
#تعریف_کن GL_TEXTURE_میانگیر_OES             0x8C2A
#تعریف_کن GL_TEXTURE_میانگیر_BINDING_OES     0x8C2A
#تعریف_کن GL_MAX_TEXTURE_میانگیر_اندازه_OES    0x8C2B
#تعریف_کن GL_TEXTURE_BINDING_میانگیر_OES     0x8C2C
#تعریف_کن GL_TEXTURE_میانگیر_داده_STORE_BINDING_OES 0x8C2D
#تعریف_کن GL_TEXTURE_میانگیر_جابه_جایی_ALIGNMENT_OES 0x919F
#تعریف_کن GL_SAMPLER_میانگیر_OES             0x8DC2
#تعریف_کن GL_INT_SAMPLER_میانگیر_OES         0x8DD0
#تعریف_کن GL_UNSIGNED_INT_SAMPLER_میانگیر_OES 0x8DD8
#تعریف_کن GL_IMAGE_میانگیر_OES               0x9051
#تعریف_کن GL_INT_IMAGE_میانگیر_OES           0x905C
#تعریف_کن GL_UNSIGNED_INT_IMAGE_میانگیر_OES  0x9067
#تعریف_کن GL_TEXTURE_میانگیر_جابه_جایی_OES      0x919D
#تعریف_کن GL_TEXTURE_میانگیر_اندازه_OES        0x919E
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXBUFFEROESPROC) (GLenum هدف, GLenum internalformat, GLuint میانگیر_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXBUFFERRANGEOESPROC) (GLenum هدف, GLenum internalformat, GLuint میانگیر_2, GLintptr جابه_جایی_2, GLsizeiptr اندازه);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Tex_میانگیر_OES (GLenum هدف, GLenum internalformat, GLuint میانگیر_2);
GL_APICALL فراغ GL_APIENTRY gl_Tex_میانگیر_Range_OES (GLenum هدف, GLenum internalformat, GLuint میانگیر_2, GLintptr جابه_جایی_2, GLsizeiptr اندازه);
#پایان_اگر
#پایان_اگر /* GL_OES_texture_buffer */

#اگر_تعریف_نشده GL_OES_texture_compression_astc
#تعریف_کن GL_OES_texture_compression_astc 1
#تعریف_کن GL_COMPRESSED_RGBA_ASTC_3x3x3_OES 0x93C0
#تعریف_کن GL_COMPRESSED_RGBA_ASTC_4x3x3_OES 0x93C1
#تعریف_کن GL_COMPRESSED_RGBA_ASTC_4x4x3_OES 0x93C2
#تعریف_کن GL_COMPRESSED_RGBA_ASTC_4x4x4_OES 0x93C3
#تعریف_کن GL_COMPRESSED_RGBA_ASTC_5x4x4_OES 0x93C4
#تعریف_کن GL_COMPRESSED_RGBA_ASTC_5x5x4_OES 0x93C5
#تعریف_کن GL_COMPRESSED_RGBA_ASTC_5x5x5_OES 0x93C6
#تعریف_کن GL_COMPRESSED_RGBA_ASTC_6x5x5_OES 0x93C7
#تعریف_کن GL_COMPRESSED_RGBA_ASTC_6x6x5_OES 0x93C8
#تعریف_کن GL_COMPRESSED_RGBA_ASTC_6x6x6_OES 0x93C9
#تعریف_کن GL_COMPRESSED_SRGB8_ALPHA8_ASTC_3x3x3_OES 0x93E0
#تعریف_کن GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x3x3_OES 0x93E1
#تعریف_کن GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4x3_OES 0x93E2
#تعریف_کن GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4x4_OES 0x93E3
#تعریف_کن GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4x4_OES 0x93E4
#تعریف_کن GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5x4_OES 0x93E5
#تعریف_کن GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5x5_OES 0x93E6
#تعریف_کن GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5x5_OES 0x93E7
#تعریف_کن GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6x5_OES 0x93E8
#تعریف_کن GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6x6_OES 0x93E9
#پایان_اگر /* GL_OES_texture_compression_astc */

#اگر_تعریف_نشده GL_OES_texture_cube_map_array
#تعریف_کن GL_OES_texture_cube_map_array 1
#تعریف_کن GL_TEXTURE_CUBE_MAP_ARRAY_OES     0x9009
#تعریف_کن GL_TEXTURE_BINDING_CUBE_MAP_ARRAY_OES 0x900A
#تعریف_کن GL_SAMPLER_CUBE_MAP_ARRAY_OES     0x900C
#تعریف_کن GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW_OES 0x900D
#تعریف_کن GL_INT_SAMPLER_CUBE_MAP_ARRAY_OES 0x900E
#تعریف_کن GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY_OES 0x900F
#تعریف_کن GL_IMAGE_CUBE_MAP_ARRAY_OES       0x9054
#تعریف_کن GL_INT_IMAGE_CUBE_MAP_ARRAY_OES   0x905F
#تعریف_کن GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY_OES 0x906A
#پایان_اگر /* GL_OES_texture_cube_map_array */

#اگر_تعریف_نشده GL_OES_texture_float
#تعریف_کن GL_OES_texture_float 1
#پایان_اگر /* GL_OES_texture_float */

#اگر_تعریف_نشده GL_OES_texture_float_خطی
#تعریف_کن GL_OES_texture_float_خطی 1
#پایان_اگر /* GL_OES_texture_float_linear */

#اگر_تعریف_نشده GL_OES_texture_half_float
#تعریف_کن GL_OES_texture_half_float 1
#تعریف_کن GL_HALF_FLOAT_OES                 0x8D61
#پایان_اگر /* GL_OES_texture_half_float */

#اگر_تعریف_نشده GL_OES_texture_half_float_خطی
#تعریف_کن GL_OES_texture_half_float_خطی 1
#پایان_اگر /* GL_OES_texture_half_float_linear */

#اگر_تعریف_نشده GL_OES_texture_npot
#تعریف_کن GL_OES_texture_npot 1
#پایان_اگر /* GL_OES_texture_npot */

#اگر_تعریف_نشده GL_OES_texture_stencil8
#تعریف_کن GL_OES_texture_stencil8 1
#تعریف_کن GL_STENCIL_شاخص_OES              0x1901
#تعریف_کن GL_STENCIL_INDEX8_OES             0x8D48
#پایان_اگر /* GL_OES_texture_stencil8 */

#اگر_تعریف_نشده GL_OES_texture_storage_multisample_2d_array
#تعریف_کن GL_OES_texture_storage_multisample_2d_array 1
#تعریف_کن GL_TEXTURE_2D_MULTISAMPLE_ARRAY_OES 0x9102
#تعریف_کن GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY_OES 0x9105
#تعریف_کن GL_SAMPLER_2D_MULTISAMPLE_ARRAY_OES 0x910B
#تعریف_کن GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY_OES 0x910C
#تعریف_کن GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY_OES 0x910D
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE3DMULTISAMPLEOESPROC) (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLboolean fixedsamplelocations);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTexStorage3DMultisampleOES (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLboolean fixedsamplelocations);
#پایان_اگر
#پایان_اگر /* GL_OES_texture_storage_multisample_2d_array */

#اگر_تعریف_نشده GL_OES_texture_view
#تعریف_کن GL_OES_texture_view 1
#تعریف_کن GL_TEXTURE_VIEW_MIN_LEVEL_OES     0x82DB
#تعریف_کن GL_TEXTURE_VIEW_رقم_سطوح_OES    0x82DC
#تعریف_کن GL_TEXTURE_VIEW_MIN_LAYER_OES     0x82DD
#تعریف_کن GL_TEXTURE_VIEW_رقم_LAYERS_OES    0x82DE
#تعریف_کن GL_TEXTURE_IMMUTABLE_سطوح       0x82DF
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTUREVIEWOESPROC) (GLuint texture, GLenum هدف, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTextureViewOES (GLuint texture, GLenum هدف, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
#پایان_اگر
#پایان_اگر /* GL_OES_texture_view */

#اگر_تعریف_نشده GL_OES_رأس_array_object
#تعریف_کن GL_OES_رأس_array_object 1
#تعریف_کن GL_رأس_ARRAY_BINDING_OES       0x85B5
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDVERTEXARRAYOESPROC) (GLuint array);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEVERTEXARRAYSOESPROC) (GLsizei n, ثابت GLuint *arrays);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENVERTEXARRAYSOESPROC) (GLsizei n, GLuint *arrays);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISVERTEXARRAYOESPROC) (GLuint array);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Bind_رأس_Array_OES (GLuint array);
GL_APICALL فراغ GL_APIENTRY gl_Delete_رأس_Arrays_OES (GLsizei n, ثابت GLuint *arrays);
GL_APICALL فراغ GL_APIENTRY gl_Gen_رأس_Arrays_OES (GLsizei n, GLuint *arrays);
GL_APICALL GLboolean GL_APIENTRY gl_Is_رأس_Array_OES (GLuint array);
#پایان_اگر
#پایان_اگر /* GL_OES_vertex_array_object */

#اگر_تعریف_نشده GL_OES_رأس_half_float
#تعریف_کن GL_OES_رأس_half_float 1
#پایان_اگر /* GL_OES_vertex_half_float */

#اگر_تعریف_نشده GL_OES_رأس_type_10_10_10_2
#تعریف_کن GL_OES_رأس_type_10_10_10_2 1
#تعریف_کن GL_UNSIGNED_INT_10_10_10_2_OES    0x8DF6
#تعریف_کن GL_INT_10_10_10_2_OES             0x8DF7
#پایان_اگر /* GL_OES_vertex_type_10_10_10_2 */

#اگر_تعریف_نشده GL_OES_viewport_array
#تعریف_کن GL_OES_viewport_array 1
#تعریف_کن GL_MAX_VIEWPORTS_OES              0x825B
#تعریف_کن GL_VIEWPORT_SUBPIXEL_بیتها_OES     0x825C
#تعریف_کن GL_VIEWPORT_BOUNDS_RANGE_OES      0x825D
#تعریف_کن GL_VIEWPORT_شاخص_PROVOKING_رأس_OES 0x825F
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTARRAYVOESPROC) (GLuint اولی, GLsizei شمار, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTINDEXEDFOESPROC) (GLuint شاخص, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTINDEXEDFVOESPROC) (GLuint شاخص, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSORARRAYVOESPROC) (GLuint اولی, GLsizei شمار, ثابت GLint *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSORINDEXEDOESPROC) (GLuint شاخص, GLint چپ, GLint bottom, GLsizei عرض, GLsizei ارتفاع);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSORINDEXEDVOESPROC) (GLuint شاخص, ثابت GLint *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHRANGEARRAYFVOESPROC) (GLuint اولی, GLsizei شمار, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHRANGEINDEXEDFOESPROC) (GLuint شاخص, GLfloat n, GLfloat f);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFLOATI_VOESPROC) (GLenum هدف, GLuint شاخص, GLfloat *داده);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glViewportArrayvOES (GLuint اولی, GLsizei شمار, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY glViewportIndexedfOES (GLuint شاخص, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
GL_APICALL فراغ GL_APIENTRY glViewportIndexedfvOES (GLuint شاخص, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY glScissorArrayvOES (GLuint اولی, GLsizei شمار, ثابت GLint *v);
GL_APICALL فراغ GL_APIENTRY gl_Scissor_نمایهای_OES (GLuint شاخص, GLint چپ, GLint bottom, GLsizei عرض, GLsizei ارتفاع);
GL_APICALL فراغ GL_APIENTRY glScissorIndexedvOES (GLuint شاخص, ثابت GLint *v);
GL_APICALL فراغ GL_APIENTRY gl_عمق_Range_Arrayfv_OES (GLuint اولی, GLsizei شمار, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY gl_عمق_Range_Indexedf_OES (GLuint شاخص, GLfloat n, GLfloat f);
GL_APICALL فراغ GL_APIENTRY glGetFloati_vOES (GLenum هدف, GLuint شاخص, GLfloat *داده);
#پایان_اگر
#پایان_اگر /* GL_OES_viewport_array */

#اگر_تعریف_نشده GL_AMD_compressed_3DC_texture
#تعریف_کن GL_AMD_compressed_3DC_texture 1
#تعریف_کن GL_3DC_X_AMD                      0x87F9
#تعریف_کن GL_3DC_XY_AMD                     0x87FA
#پایان_اگر /* GL_AMD_compressed_3DC_texture */

#اگر_تعریف_نشده GL_AMD_compressed_ATC_texture
#تعریف_کن GL_AMD_compressed_ATC_texture 1
#تعریف_کن GL_ATC_RGB_AMD                    0x8C92
#تعریف_کن GL_ATC_RGBA_EXPLICIT_ALPHA_AMD    0x8C93
#تعریف_کن GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD 0x87EE
#پایان_اگر /* GL_AMD_compressed_ATC_texture */

#اگر_تعریف_نشده GL_AMD_framebuffer_multisample_advanced
#تعریف_کن GL_AMD_framebuffer_multisample_advanced 1
#تعریف_کن GL_RENDERBUFFER_STORAGE_SAMPLES_AMD 0x91B2
#تعریف_کن GL_MAX_COLOR_FRAMEBUFFER_SAMPLES_AMD 0x91B3
#تعریف_کن GL_MAX_COLOR_FRAMEBUFFER_STORAGE_SAMPLES_AMD 0x91B4
#تعریف_کن GL_MAX_عمق_STENCIL_FRAMEBUFFER_SAMPLES_AMD 0x91B5
#تعریف_کن GL_رقم_SUPPORTED_MULTISAMPLE_MODES_AMD 0x91B6
#تعریف_کن GL_SUPPORTED_MULTISAMPLE_MODES_AMD 0x91B7
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC) (GLenum هدف, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
تعريفنوع فراغ (GL_APIENTRYP PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC) (GLuint renderbuffer, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glRenderbufferStorageMultisampleAdvancedAMD (GLenum هدف, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
GL_APICALL فراغ GL_APIENTRY glNamedRenderbufferStorageMultisampleAdvancedAMD (GLuint renderbuffer, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
#پایان_اگر
#پایان_اگر /* GL_AMD_framebuffer_multisample_advanced */

#اگر_تعریف_نشده GL_AMD_performance_monitor
#تعریف_کن GL_AMD_performance_monitor 1
#تعریف_کن GL_COUNTER_TYPE_AMD               0x8BC0
#تعریف_کن GL_COUNTER_RANGE_AMD              0x8BC1
#تعریف_کن GL_UNSIGNED_INT64_AMD             0x8BC2
#تعریف_کن GL_PERCENTAGE_AMD                 0x8BC3
#تعریف_کن GL_PERFMON_نتیجه_موجود_AMD   0x8BC4
#تعریف_کن GL_PERFMON_نتیجه_اندازه_AMD        0x8BC5
#تعریف_کن GL_PERFMON_نتیجه_AMD             0x8BC6
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFMONITORGROUPSAMDPROC) (GLint *رقم_Groups, GLsizei groups_اندازه, GLuint *groups);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFMONITORCOUNTERSAMDPROC) (GLuint گروه, GLint *رقم_Counters, GLint *max_فعال_Counters, GLsizei counter_اندازه, GLuint *counters);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFMONITORGROUPSTRINGAMDPROC) (GLuint گروه, GLsizei buf_اندازه, GLsizei *درازی, GLchar *گروه_String);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC) (GLuint گروه, GLuint counter, GLsizei buf_اندازه, GLsizei *درازی, GLchar *counterString);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFMONITORCOUNTERINFOAMDPROC) (GLuint گروه, GLuint counter, GLenum pname, فراغ *داده);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENPERFMONITORSAMDPROC) (GLsizei n, GLuint *monitors);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEPERFMONITORSAMDPROC) (GLsizei n, GLuint *monitors);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSELECTPERFMONITORCOUNTERSAMDPROC) (GLuint monitor, GLboolean enable, GLuint گروه, GLint رقم_Counters, GLuint *counterList);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBEGINPERFMONITORAMDPROC) (GLuint monitor);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENDPERFMONITORAMDPROC) (GLuint monitor);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFMONITORCOUNTERDATAAMDPROC) (GLuint monitor, GLenum pname, GLsizei داده_اندازه_2, GLuint *داده, GLint *بایتها_Written);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glGetPerfMonitorGroupsAMD (GLint *رقم_Groups, GLsizei groups_اندازه, GLuint *groups);
GL_APICALL فراغ GL_APIENTRY glGetPerfMonitorCountersAMD (GLuint گروه, GLint *رقم_Counters, GLint *max_فعال_Counters, GLsizei counter_اندازه, GLuint *counters);
GL_APICALL فراغ GL_APIENTRY gl_Get_Perf_Monitor_گروه_String_AMD (GLuint گروه, GLsizei buf_اندازه, GLsizei *درازی, GLchar *گروه_String);
GL_APICALL فراغ GL_APIENTRY glGetPerfMonitorCounterStringAMD (GLuint گروه, GLuint counter, GLsizei buf_اندازه, GLsizei *درازی, GLchar *counterString);
GL_APICALL فراغ GL_APIENTRY glGetPerfMonitorCounterInfoAMD (GLuint گروه, GLuint counter, GLenum pname, فراغ *داده);
GL_APICALL فراغ GL_APIENTRY glGenPerfMonitorsAMD (GLsizei n, GLuint *monitors);
GL_APICALL فراغ GL_APIENTRY glDeletePerfMonitorsAMD (GLsizei n, GLuint *monitors);
GL_APICALL فراغ GL_APIENTRY glSelectPerfMonitorCountersAMD (GLuint monitor, GLboolean enable, GLuint گروه, GLint رقم_Counters, GLuint *counterList);
GL_APICALL فراغ GL_APIENTRY glBeginPerfMonitorAMD (GLuint monitor);
GL_APICALL فراغ GL_APIENTRY gl_انتها_Perf_Monitor_AMD (GLuint monitor);
GL_APICALL فراغ GL_APIENTRY gl_Get_Perf_Monitor_Counter_داده_AMD (GLuint monitor, GLenum pname, GLsizei داده_اندازه_2, GLuint *داده, GLint *بایتها_Written);
#پایان_اگر
#پایان_اگر /* GL_AMD_performance_monitor */

#اگر_تعریف_نشده GL_AMD_برنامه_دودویی_Z400
#تعریف_کن GL_AMD_برنامه_دودویی_Z400 1
#تعریف_کن GL_Z400_دودویی_AMD                0x8740
#پایان_اگر /* GL_AMD_program_binary_Z400 */

#اگر_تعریف_نشده GL_ANDROID_extension_pack_es31a
#تعریف_کن GL_ANDROID_extension_pack_es31a 1
#پایان_اگر /* GL_ANDROID_extension_pack_es31a */

#اگر_تعریف_نشده GL_ANGLE_عمق_texture
#تعریف_کن GL_ANGLE_عمق_texture 1
#پایان_اگر /* GL_ANGLE_depth_texture */

#اگر_تعریف_نشده GL_ANGLE_framebuffer_blit
#تعریف_کن GL_ANGLE_framebuffer_blit 1
#تعریف_کن GL_READ_FRAMEBUFFER_ANGLE         0x8CA8
#تعریف_کن GL_DRAW_FRAMEBUFFER_ANGLE         0x8CA9
#تعریف_کن GL_DRAW_FRAMEBUFFER_BINDING_ANGLE 0x8CA6
#تعریف_کن GL_READ_FRAMEBUFFER_BINDING_ANGLE 0x8CAA
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLITFRAMEBUFFERANGLEPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield ماسک, GLenum filter);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glBlitFramebufferANGLE (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield ماسک, GLenum filter);
#پایان_اگر
#پایان_اگر /* GL_ANGLE_framebuffer_blit */

#اگر_تعریف_نشده GL_ANGLE_framebuffer_multisample
#تعریف_کن GL_ANGLE_framebuffer_multisample 1
#تعریف_کن GL_RENDERBUFFER_SAMPLES_ANGLE     0x8CAB
#تعریف_کن GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_ANGLE 0x8D56
#تعریف_کن GL_MAX_SAMPLES_ANGLE              0x8D57
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEANGLEPROC) (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glRenderbufferStorageMultisampleANGLE (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
#پایان_اگر
#پایان_اگر /* GL_ANGLE_framebuffer_multisample */

#اگر_تعریف_نشده GL_ANGLE_instanced_arrays
#تعریف_کن GL_ANGLE_instanced_arrays 1
#تعریف_کن GL_رأس_ATTRIB_ARRAY_مقسوم_علیه_ANGLE 0x88FE
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDANGLEPROC) (GLenum نما, GLint اولی, GLsizei شمار, GLsizei primcount);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDANGLEPROC) (GLenum نما, GLsizei شمار, GLenum type, ثابت فراغ *indices, GLsizei primcount);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBDIVISORANGLEPROC) (GLuint شاخص, GLuint مقسوم_علیه);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawArraysInstancedANGLE (GLenum نما, GLint اولی, GLsizei شمار, GLsizei primcount);
GL_APICALL فراغ GL_APIENTRY glDrawElementsInstancedANGLE (GLenum نما, GLsizei شمار, GLenum type, ثابت فراغ *indices, GLsizei primcount);
GL_APICALL فراغ GL_APIENTRY gl_رأس_Attrib_مقسوم_علیه_ANGLE (GLuint شاخص, GLuint مقسوم_علیه);
#پایان_اگر
#پایان_اگر /* GL_ANGLE_instanced_arrays */

#اگر_تعریف_نشده GL_ANGLE_pack_معکوس_ردیف_ترتیب
#تعریف_کن GL_ANGLE_pack_معکوس_ردیف_ترتیب 1
#تعریف_کن GL_PACK_معکوس_ردیف_ترتیب_ANGLE   0x93A4
#پایان_اگر /* GL_ANGLE_pack_reverse_row_order */

#اگر_تعریف_نشده GL_ANGLE_برنامه_دودویی
#تعریف_کن GL_ANGLE_برنامه_دودویی 1
#تعریف_کن GL_برنامه_دودویی_ANGLE           0x93A6
#پایان_اگر /* GL_ANGLE_program_binary */

#اگر_تعریف_نشده GL_ANGLE_texture_compression_dxt3
#تعریف_کن GL_ANGLE_texture_compression_dxt3 1
#تعریف_کن GL_COMPRESSED_RGBA_S3TC_DXT3_ANGLE 0x83F2
#پایان_اگر /* GL_ANGLE_texture_compression_dxt3 */

#اگر_تعریف_نشده GL_ANGLE_texture_compression_dxt5
#تعریف_کن GL_ANGLE_texture_compression_dxt5 1
#تعریف_کن GL_COMPRESSED_RGBA_S3TC_DXT5_ANGLE 0x83F3
#پایان_اگر /* GL_ANGLE_texture_compression_dxt5 */

#اگر_تعریف_نشده GL_ANGLE_texture_usage
#تعریف_کن GL_ANGLE_texture_usage 1
#تعریف_کن GL_TEXTURE_USAGE_ANGLE            0x93A2
#تعریف_کن GL_FRAMEBUFFER_ATTACHMENT_ANGLE   0x93A3
#پایان_اگر /* GL_ANGLE_texture_usage */

#اگر_تعریف_نشده GL_ANGLE_translated_shader_منبع
#تعریف_کن GL_ANGLE_translated_shader_منبع 1
#تعریف_کن GL_TRANSLATED_SHADER_منبع_درازی_ANGLE 0x93A0
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTRANSLATEDSHADERSOURCEANGLEPROC) (GLuint shader, GLsizei buf_اندازه, GLsizei *درازی, GLchar *منبع);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Get_Translated_Shader_منبع_ANGLE (GLuint shader, GLsizei buf_اندازه, GLsizei *درازی, GLchar *منبع);
#پایان_اگر
#پایان_اگر /* GL_ANGLE_translated_shader_source */

#اگر_تعریف_نشده GL_APPLE_clip_فاصله
#تعریف_کن GL_APPLE_clip_فاصله 1
#تعریف_کن GL_MAX_CLIP_DISTANCES_APPLE       0x0D32
#تعریف_کن GL_CLIP_DISTANCE0_APPLE           0x3000
#تعریف_کن GL_CLIP_DISTANCE1_APPLE           0x3001
#تعریف_کن GL_CLIP_DISTANCE2_APPLE           0x3002
#تعریف_کن GL_CLIP_DISTANCE3_APPLE           0x3003
#تعریف_کن GL_CLIP_DISTANCE4_APPLE           0x3004
#تعریف_کن GL_CLIP_DISTANCE5_APPLE           0x3005
#تعریف_کن GL_CLIP_DISTANCE6_APPLE           0x3006
#تعریف_کن GL_CLIP_DISTANCE7_APPLE           0x3007
#پایان_اگر /* GL_APPLE_clip_distance */

#اگر_تعریف_نشده GL_APPLE_color_میانگیر_packed_float
#تعریف_کن GL_APPLE_color_میانگیر_packed_float 1
#پایان_اگر /* GL_APPLE_color_buffer_packed_float */

#اگر_تعریف_نشده GL_APPLE_copy_texture_سطوح
#تعریف_کن GL_APPLE_copy_texture_سطوح 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYTEXTURELEVELSAPPLEPROC) (GLuint destinationTexture, GLuint منبع_Texture, GLint منبع_پایه_Level, GLsizei منبع_Level_شمار);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Copy_Texture_سطوح_APPLE (GLuint destinationTexture, GLuint منبع_Texture, GLint منبع_پایه_Level, GLsizei منبع_Level_شمار);
#پایان_اگر
#پایان_اگر /* GL_APPLE_copy_texture_levels */

#اگر_تعریف_نشده GL_APPLE_framebuffer_multisample
#تعریف_کن GL_APPLE_framebuffer_multisample 1
#تعریف_کن GL_RENDERBUFFER_SAMPLES_APPLE     0x8CAB
#تعریف_کن GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_APPLE 0x8D56
#تعریف_کن GL_MAX_SAMPLES_APPLE              0x8D57
#تعریف_کن GL_READ_FRAMEBUFFER_APPLE         0x8CA8
#تعریف_کن GL_DRAW_FRAMEBUFFER_APPLE         0x8CA9
#تعریف_کن GL_DRAW_FRAMEBUFFER_BINDING_APPLE 0x8CA6
#تعریف_کن GL_READ_FRAMEBUFFER_BINDING_APPLE 0x8CAA
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEAPPLEPROC) (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRESOLVEMULTISAMPLEFRAMEBUFFERAPPLEPROC) (فراغ);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glRenderbufferStorageMultisampleAPPLE (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
GL_APICALL فراغ GL_APIENTRY glResolveMultisampleFramebufferAPPLE (فراغ);
#پایان_اگر
#پایان_اگر /* GL_APPLE_framebuffer_multisample */

#اگر_تعریف_نشده GL_APPLE_rgb_422
#تعریف_کن GL_APPLE_rgb_422 1
#تعریف_کن GL_RGB_422_APPLE                  0x8A1F
#تعریف_کن GL_UNSIGNED_SHORT_8_8_APPLE       0x85BA
#تعریف_کن GL_UNSIGNED_SHORT_8_8_REV_APPLE   0x85BB
#تعریف_کن GL_RGB_RAW_422_APPLE              0x8A51
#پایان_اگر /* GL_APPLE_rgb_422 */

#اگر_تعریف_نشده GL_APPLE_sync
#تعریف_کن GL_APPLE_sync 1
#تعریف_کن GL_SYNC_OBJECT_APPLE              0x8A53
#تعریف_کن GL_MAX_SERVER_WAIT_TIMEOUT_APPLE  0x9111
#تعریف_کن GL_OBJECT_TYPE_APPLE              0x9112
#تعریف_کن GL_SYNC_CONDITION_APPLE           0x9113
#تعریف_کن GL_SYNC_وضعیت_APPLE              0x9114
#تعریف_کن GL_SYNC_FLAGS_APPLE               0x9115
#تعریف_کن GL_SYNC_FENCE_APPLE               0x9116
#تعریف_کن GL_SYNC_GPU_COMMANDS_COMPLETE_APPLE 0x9117
#تعریف_کن GL_UNSIGNALED_APPLE               0x9118
#تعریف_کن GL_SIGNALED_APPLE                 0x9119
#تعریف_کن GL_ALREADY_SIGNALED_APPLE         0x911A
#تعریف_کن GL_TIMEOUT_EXPIRED_APPLE          0x911B
#تعریف_کن GL_CONDITION_SATISFIED_APPLE      0x911C
#تعریف_کن GL_WAIT_FAILED_APPLE              0x911D
#تعریف_کن GL_SYNC_FLUSH_COMMANDS_بیت_APPLE  0x00000001
#تعریف_کن GL_TIMEOUT_IGNORED_APPLE          0xFFFFFFFFFFFFFFFFull
تعريفنوع GLsync (GL_APIENTRYP PFNGLFENCESYNCAPPLEPROC) (GLenum condition, GLbitfield flags);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISSYNCAPPLEPROC) (GLsync sync);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETESYNCAPPLEPROC) (GLsync sync);
تعريفنوع GLenum (GL_APIENTRYP PFNGLCLIENTWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
تعريفنوع فراغ (GL_APIENTRYP PFNGLWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTEGER64VAPPLEPROC) (GLenum pname, GLint64 *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSYNCIVAPPLEPROC) (GLsync sync, GLenum pname, GLsizei شمار, GLsizei *درازی, GLint *مقادیر);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL GLsync GL_APIENTRY glFenceSyncAPPLE (GLenum condition, GLbitfield flags);
GL_APICALL GLboolean GL_APIENTRY glIsSyncAPPLE (GLsync sync);
GL_APICALL فراغ GL_APIENTRY glDeleteSyncAPPLE (GLsync sync);
GL_APICALL GLenum GL_APIENTRY glClientWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_APICALL فراغ GL_APIENTRY glWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_APICALL فراغ GL_APIENTRY glGetInteger64vAPPLE (GLenum pname, GLint64 *params);
GL_APICALL فراغ GL_APIENTRY glGetSyncivAPPLE (GLsync sync, GLenum pname, GLsizei شمار, GLsizei *درازی, GLint *مقادیر);
#پایان_اگر
#پایان_اگر /* GL_APPLE_sync */

#اگر_تعریف_نشده GL_APPLE_texture_format_BGRA8888
#تعریف_کن GL_APPLE_texture_format_BGRA8888 1
#تعریف_کن GL_BGRA_EXT                       0x80E1
#تعریف_کن GL_BGRA8_EXT                      0x93A1
#پایان_اگر /* GL_APPLE_texture_format_BGRA8888 */

#اگر_تعریف_نشده GL_APPLE_texture_max_level
#تعریف_کن GL_APPLE_texture_max_level 1
#تعریف_کن GL_TEXTURE_MAX_LEVEL_APPLE        0x813D
#پایان_اگر /* GL_APPLE_texture_max_level */

#اگر_تعریف_نشده GL_APPLE_texture_packed_float
#تعریف_کن GL_APPLE_texture_packed_float 1
#تعریف_کن GL_UNSIGNED_INT_10F_11F_11F_REV_APPLE 0x8C3B
#تعریف_کن GL_UNSIGNED_INT_5_9_9_9_REV_APPLE 0x8C3E
#تعریف_کن GL_R11F_G11F_B10F_APPLE           0x8C3A
#تعریف_کن GL_RGB9_E5_APPLE                  0x8C3D
#پایان_اگر /* GL_APPLE_texture_packed_float */

#اگر_تعریف_نشده GL_ARM_mali_برنامه_دودویی
#تعریف_کن GL_ARM_mali_برنامه_دودویی 1
#تعریف_کن GL_MALI_برنامه_دودویی_ARM        0x8F61
#پایان_اگر /* GL_ARM_mali_program_binary */

#اگر_تعریف_نشده GL_ARM_mali_shader_دودویی
#تعریف_کن GL_ARM_mali_shader_دودویی 1
#تعریف_کن GL_MALI_SHADER_دودویی_ARM         0x8F60
#پایان_اگر /* GL_ARM_mali_shader_binary */

#اگر_تعریف_نشده GL_ARM_rgba8
#تعریف_کن GL_ARM_rgba8 1
#پایان_اگر /* GL_ARM_rgba8 */

#اگر_تعریف_نشده GL_ARM_shader_core_properties
#تعریف_کن GL_ARM_shader_core_properties 1
#تعریف_کن GL_SHADER_CORE_شمار_ARM          0x96F0
#تعریف_کن GL_SHADER_CORE_فعال_شمار_ARM   0x96F1
#تعریف_کن GL_SHADER_CORE_PRESENT_ماسک_ARM   0x96F2
#تعریف_کن GL_SHADER_CORE_MAX_WARP_شمار_ARM 0x96F3
#تعریف_کن GL_SHADER_CORE_PIXEL_نرخ_ARM     0x96F4
#تعریف_کن GL_SHADER_CORE_TEXEL_نرخ_ARM     0x96F5
#تعریف_کن GL_SHADER_CORE_FMA_نرخ_ARM       0x96F6
تعريفنوع فراغ (GL_APIENTRYP PFNGLMAXACTIVESHADERCORESARMPROC) (GLuint شمار);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Max_فعال_Shader_Cores_ARM (GLuint شمار);
#پایان_اگر
#پایان_اگر /* GL_ARM_shader_core_properties */

#اگر_تعریف_نشده GL_ARM_shader_framebuffer_fetch
#تعریف_کن GL_ARM_shader_framebuffer_fetch 1
#تعریف_کن GL_FETCH_در_هر_SAMPLE_ARM           0x8F65
#تعریف_کن GL_FRAGMENT_SHADER_FRAMEBUFFER_FETCH_MRT_ARM 0x8F66
#پایان_اگر /* GL_ARM_shader_framebuffer_fetch */

#اگر_تعریف_نشده GL_ARM_shader_framebuffer_fetch_عمق_stencil
#تعریف_کن GL_ARM_shader_framebuffer_fetch_عمق_stencil 1
#پایان_اگر /* GL_ARM_shader_framebuffer_fetch_depth_stencil */

#اگر_تعریف_نشده GL_ARM_texture_unnormalized_coordinates
#تعریف_کن GL_ARM_texture_unnormalized_coordinates 1
#تعریف_کن GL_TEXTURE_UNNORMALIZED_COORDINATES_ARM 0x8F6A
#پایان_اگر /* GL_ARM_texture_unnormalized_coordinates */

#اگر_تعریف_نشده GL_DMP_برنامه_دودویی
#تعریف_کن GL_DMP_برنامه_دودویی 1
#تعریف_کن GL_SMAPHS30_برنامه_دودویی_DMP    0x9251
#تعریف_کن GL_SMAPHS_برنامه_دودویی_DMP      0x9252
#تعریف_کن GL_DMP_برنامه_دودویی_DMP         0x9253
#پایان_اگر /* GL_DMP_program_binary */

#اگر_تعریف_نشده GL_DMP_shader_دودویی
#تعریف_کن GL_DMP_shader_دودویی 1
#تعریف_کن GL_SHADER_دودویی_DMP              0x9250
#پایان_اگر /* GL_DMP_shader_binary */

#اگر_تعریف_نشده GL_EXT_EGL_image_array
#تعریف_کن GL_EXT_EGL_image_array 1
#پایان_اگر /* GL_EXT_EGL_image_array */

#اگر_تعریف_نشده GL_EXT_EGL_image_storage
#تعریف_کن GL_EXT_EGL_image_storage 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLEGLIMAGETARGETTEXSTORAGEEXTPROC) (GLenum هدف, GLeglImageOES image, ثابت GLint* attrib_list);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEGLIMAGETARGETTEXTURESTORAGEEXTPROC) (GLuint texture, GLeglImageOES image, ثابت GLint* attrib_list);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_EGLImage_هدف_Tex_Storage_EXT (GLenum هدف, GLeglImageOES image, ثابت GLint* attrib_list);
GL_APICALL فراغ GL_APIENTRY gl_EGLImage_هدف_Texture_Storage_EXT (GLuint texture, GLeglImageOES image, ثابت GLint* attrib_list);
#پایان_اگر
#پایان_اگر /* GL_EXT_EGL_image_storage */

#اگر_تعریف_نشده GL_EXT_EGL_image_storage_compression
#تعریف_کن GL_EXT_EGL_image_storage_compression 1
#تعریف_کن GL_SURFACE_COMPRESSION_EXT        0x96C0
#تعریف_کن GL_SURFACE_COMPRESSION_FIXED_نرخ_NONE_EXT 0x96C1
#تعریف_کن GL_SURFACE_COMPRESSION_FIXED_نرخ_DEFAULT_EXT 0x96C2
#پایان_اگر /* GL_EXT_EGL_image_storage_compression */

#اگر_تعریف_نشده GL_EXT_YUV_هدف
#تعریف_کن GL_EXT_YUV_هدف 1
#تعریف_کن GL_SAMPLER_EXTERNAL_2D_Y2Y_EXT    0x8BE7
#پایان_اگر /* GL_EXT_YUV_target */

#اگر_تعریف_نشده GL_EXT_پایه_instance
#تعریف_کن GL_EXT_پایه_instance 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEEXTPROC) (GLenum نما, GLint اولی, GLsizei شمار, GLsizei instancecount, GLuint baseinstance);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEEXTPROC) (GLenum نما, GLsizei شمار, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLuint baseinstance);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEEXTPROC) (GLenum نما, GLsizei شمار, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Draw_Arrays_Instanced_پایه_Instance_EXT (GLenum نما, GLint اولی, GLsizei شمار, GLsizei instancecount, GLuint baseinstance);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Elements_Instanced_پایه_Instance_EXT (GLenum نما, GLsizei شمار, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLuint baseinstance);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Elements_Instanced_پایه_رأس_پایه_Instance_EXT (GLenum نما, GLsizei شمار, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance);
#پایان_اگر
#پایان_اگر /* GL_EXT_base_instance */

#اگر_تعریف_نشده GL_EXT_blend_func_extended
#تعریف_کن GL_EXT_blend_func_extended 1
#تعریف_کن GL_SRC1_COLOR_EXT                 0x88F9
#تعریف_کن GL_SRC1_ALPHA_EXT                 0x8589
#تعریف_کن GL_ONE_MINUS_SRC1_COLOR_EXT       0x88FA
#تعریف_کن GL_ONE_MINUS_SRC1_ALPHA_EXT       0x88FB
#تعریف_کن GL_SRC_ALPHA_SATURATE_EXT         0x0308
#تعریف_کن GL_LOCATION_شاخص_EXT             0x930F
#تعریف_کن GL_MAX_DUAL_منبع_DRAW_BUFFERS_EXT 0x88FC
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDFRAGDATALOCATIONINDEXEDEXTPROC) (GLuint برنامه, GLuint color_عدد, GLuint شاخص, ثابت GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDFRAGDATALOCATIONEXTPROC) (GLuint برنامه, GLuint color, ثابت GLchar *name);
تعريفنوع GLint (GL_APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONINDEXEXTPROC) (GLuint برنامه, GLenum برنامه_Interface, ثابت GLchar *name);
تعريفنوع GLint (GL_APIENTRYP PFNGLGETFRAGDATAINDEXEXTPROC) (GLuint برنامه, ثابت GLchar *name);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Bind_Frag_داده_Location_نمایهای_EXT (GLuint برنامه, GLuint color_عدد, GLuint شاخص, ثابت GLchar *name);
GL_APICALL فراغ GL_APIENTRY gl_Bind_Frag_داده_Location_EXT (GLuint برنامه, GLuint color, ثابت GLchar *name);
GL_APICALL GLint GL_APIENTRY gl_Get_برنامه_Resource_Location_شاخص_EXT (GLuint برنامه, GLenum برنامه_Interface, ثابت GLchar *name);
GL_APICALL GLint GL_APIENTRY gl_Get_Frag_داده_شاخص_EXT (GLuint برنامه, ثابت GLchar *name);
#پایان_اگر
#پایان_اگر /* GL_EXT_blend_func_extended */

#اگر_تعریف_نشده GL_EXT_blend_minmax
#تعریف_کن GL_EXT_blend_minmax 1
#تعریف_کن GL_MIN_EXT                        0x8007
#تعریف_کن GL_MAX_EXT                        0x8008
#پایان_اگر /* GL_EXT_blend_minmax */

#اگر_تعریف_نشده GL_EXT_میانگیر_storage
#تعریف_کن GL_EXT_میانگیر_storage 1
#تعریف_کن GL_MAP_READ_بیت                   0x0001
#تعریف_کن GL_MAP_WRITE_بیت                  0x0002
#تعریف_کن GL_MAP_PERSISTENT_بیت_EXT         0x0040
#تعریف_کن GL_MAP_COHERENT_بیت_EXT           0x0080
#تعریف_کن GL_DYNAMIC_STORAGE_بیت_EXT        0x0100
#تعریف_کن GL_CLIENT_STORAGE_بیت_EXT         0x0200
#تعریف_کن GL_CLIENT_MAPPED_میانگیر_BARRIER_بیت_EXT 0x00004000
#تعریف_کن GL_میانگیر_IMMUTABLE_STORAGE_EXT   0x821F
#تعریف_کن GL_میانگیر_STORAGE_FLAGS_EXT       0x8220
تعريفنوع فراغ (GL_APIENTRYP PFNGLBUFFERSTORAGEEXTPROC) (GLenum هدف, GLsizeiptr اندازه, ثابت فراغ *داده, GLbitfield flags);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_میانگیر_Storage_EXT (GLenum هدف, GLsizeiptr اندازه, ثابت فراغ *داده, GLbitfield flags);
#پایان_اگر
#پایان_اگر /* GL_EXT_buffer_storage */

#اگر_تعریف_نشده GL_EXT_clear_texture
#تعریف_کن GL_EXT_clear_texture 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARTEXIMAGEEXTPROC) (GLuint texture, GLint level, GLenum format, GLenum type, ثابت فراغ *داده);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARTEXSUBIMAGEEXTPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLenum format, GLenum type, ثابت فراغ *داده);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glClearTexImageEXT (GLuint texture, GLint level, GLenum format, GLenum type, ثابت فراغ *داده);
GL_APICALL فراغ GL_APIENTRY glClearTexSubImageEXT (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLenum format, GLenum type, ثابت فراغ *داده);
#پایان_اگر
#پایان_اگر /* GL_EXT_clear_texture */

#اگر_تعریف_نشده GL_EXT_clip_control
#تعریف_کن GL_EXT_clip_control 1
#تعریف_کن GL_پایینی_چپ_EXT                 0x8CA1
#تعریف_کن GL_فوقانی_چپ_EXT                 0x8CA2
#تعریف_کن GL_NEGATIVE_ONE_مقصد_ONE_EXT        0x935E
#تعریف_کن GL_ZERO_مقصد_ONE_EXT                0x935F
#تعریف_کن GL_CLIP_ORIGIN_EXT                0x935C
#تعریف_کن GL_CLIP_عمق_نما_EXT            0x935D
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLIPCONTROLEXTPROC) (GLenum origin, GLenum عمق_2);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glClipControlEXT (GLenum origin, GLenum عمق_2);
#پایان_اگر
#پایان_اگر /* GL_EXT_clip_control */

#اگر_تعریف_نشده GL_EXT_clip_cull_فاصله
#تعریف_کن GL_EXT_clip_cull_فاصله 1
#تعریف_کن GL_MAX_CLIP_DISTANCES_EXT         0x0D32
#تعریف_کن GL_MAX_CULL_DISTANCES_EXT         0x82F9
#تعریف_کن GL_MAX_COMBINED_CLIP_AND_CULL_DISTANCES_EXT 0x82FA
#تعریف_کن GL_CLIP_DISTANCE0_EXT             0x3000
#تعریف_کن GL_CLIP_DISTANCE1_EXT             0x3001
#تعریف_کن GL_CLIP_DISTANCE2_EXT             0x3002
#تعریف_کن GL_CLIP_DISTANCE3_EXT             0x3003
#تعریف_کن GL_CLIP_DISTANCE4_EXT             0x3004
#تعریف_کن GL_CLIP_DISTANCE5_EXT             0x3005
#تعریف_کن GL_CLIP_DISTANCE6_EXT             0x3006
#تعریف_کن GL_CLIP_DISTANCE7_EXT             0x3007
#پایان_اگر /* GL_EXT_clip_cull_distance */

#اگر_تعریف_نشده GL_EXT_color_میانگیر_float
#تعریف_کن GL_EXT_color_میانگیر_float 1
#پایان_اگر /* GL_EXT_color_buffer_float */

#اگر_تعریف_نشده GL_EXT_color_میانگیر_half_float
#تعریف_کن GL_EXT_color_میانگیر_half_float 1
#تعریف_کن GL_RGBA16F_EXT                    0x881A
#تعریف_کن GL_RGB16F_EXT                     0x881B
#تعریف_کن GL_RG16F_EXT                      0x822F
#تعریف_کن GL_R16F_EXT                       0x822D
#تعریف_کن GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE_EXT 0x8211
#تعریف_کن GL_UNSIGNED_NORMALIZED_EXT        0x8C17
#پایان_اگر /* GL_EXT_color_buffer_half_float */

#اگر_تعریف_نشده GL_EXT_conservative_عمق
#تعریف_کن GL_EXT_conservative_عمق 1
#پایان_اگر /* GL_EXT_conservative_depth */

#اگر_تعریف_نشده GL_EXT_copy_image
#تعریف_کن GL_EXT_copy_image 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYIMAGESUBDATAEXTPROC) (GLuint srcName, GLenum src_هدف, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dst_هدف, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei src_عرض, GLsizei src_ارتفاع, GLsizei src_عمق);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Copy_Image_Sub_داده_EXT (GLuint srcName, GLenum src_هدف, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dst_هدف, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei src_عرض, GLsizei src_ارتفاع, GLsizei src_عمق);
#پایان_اگر
#پایان_اگر /* GL_EXT_copy_image */

#اگر_تعریف_نشده GL_EXT_debug_label
#تعریف_کن GL_EXT_debug_label 1
#تعریف_کن GL_برنامه_PIPELINE_OBJECT_EXT    0x8A4F
#تعریف_کن GL_برنامه_OBJECT_EXT             0x8B40
#تعریف_کن GL_SHADER_OBJECT_EXT              0x8B48
#تعریف_کن GL_میانگیر_OBJECT_EXT              0x9151
#تعریف_کن GL_QUERY_OBJECT_EXT               0x9153
#تعریف_کن GL_رأس_ARRAY_OBJECT_EXT        0x9154
#تعریف_کن GL_TRANSFORM_FEEDBACK             0x8E22
تعريفنوع فراغ (GL_APIENTRYP PFNGLLABELOBJECTEXTPROC) (GLenum type, GLuint object, GLsizei درازی, ثابت GLchar *label);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETOBJECTLABELEXTPROC) (GLenum type, GLuint object, GLsizei buf_اندازه, GLsizei *درازی, GLchar *label);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glLabelObjectEXT (GLenum type, GLuint object, GLsizei درازی, ثابت GLchar *label);
GL_APICALL فراغ GL_APIENTRY glGetObjectLabelEXT (GLenum type, GLuint object, GLsizei buf_اندازه, GLsizei *درازی, GLchar *label);
#پایان_اگر
#پایان_اگر /* GL_EXT_debug_label */

#اگر_تعریف_نشده GL_EXT_debug_marker
#تعریف_کن GL_EXT_debug_marker 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLINSERTEVENTMARKEREXTPROC) (GLsizei درازی, ثابت GLchar *marker);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPUSHGROUPMARKEREXTPROC) (GLsizei درازی, ثابت GLchar *marker);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOPGROUPMARKEREXTPROC) (فراغ);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_درج_Event_Marker_EXT (GLsizei درازی, ثابت GLchar *marker);
GL_APICALL فراغ GL_APIENTRY gl_افزودن_گروه_Marker_EXT (GLsizei درازی, ثابت GLchar *marker);
GL_APICALL فراغ GL_APIENTRY gl_برداشت_گروه_Marker_EXT (فراغ);
#پایان_اگر
#پایان_اگر /* GL_EXT_debug_marker */

#اگر_تعریف_نشده GL_EXT_عمق_clamp
#تعریف_کن GL_EXT_عمق_clamp 1
#تعریف_کن GL_عمق_CLAMP_EXT                0x864F
#پایان_اگر /* GL_EXT_depth_clamp */

#اگر_تعریف_نشده GL_EXT_discard_framebuffer
#تعریف_کن GL_EXT_discard_framebuffer 1
#تعریف_کن GL_COLOR_EXT                      0x1800
#تعریف_کن GL_عمق_EXT                      0x1801
#تعریف_کن GL_STENCIL_EXT                    0x1802
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISCARDFRAMEBUFFEREXTPROC) (GLenum هدف, GLsizei رقم_Attachments, ثابت GLenum *attachments);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDiscardFramebufferEXT (GLenum هدف, GLsizei رقم_Attachments, ثابت GLenum *attachments);
#پایان_اگر
#پایان_اگر /* GL_EXT_discard_framebuffer */

#اگر_تعریف_نشده GL_EXT_disjoint_timer_query
#تعریف_کن GL_EXT_disjoint_timer_query 1
#تعریف_کن GL_QUERY_COUNTER_بیتها_EXT         0x8864
#تعریف_کن GL_CURRENT_QUERY_EXT              0x8865
#تعریف_کن GL_QUERY_نتیجه_EXT               0x8866
#تعریف_کن GL_QUERY_نتیجه_موجود_EXT     0x8867
#تعریف_کن GL_زمان_ELAPSED_EXT               0x88BF
#تعریف_کن GL_TIMESTAMP_EXT                  0x8E28
#تعریف_کن GL_GPU_DISJOINT_EXT               0x8FBB
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
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTEGER64VEXTPROC) (GLenum pname, GLint64 *داده);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glGenQueriesEXT (GLsizei n, GLuint *ids);
GL_APICALL فراغ GL_APIENTRY glDeleteQueriesEXT (GLsizei n, ثابت GLuint *ids);
GL_APICALL GLboolean GL_APIENTRY glIsQueryEXT (GLuint id);
GL_APICALL فراغ GL_APIENTRY glBeginQueryEXT (GLenum هدف, GLuint id);
GL_APICALL فراغ GL_APIENTRY gl_انتها_Query_EXT (GLenum هدف);
GL_APICALL فراغ GL_APIENTRY glQueryCounterEXT (GLuint id, GLenum هدف);
GL_APICALL فراغ GL_APIENTRY glGetQueryivEXT (GLenum هدف, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetQueryObjectivEXT (GLuint id, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetQueryObjectuivEXT (GLuint id, GLenum pname, GLuint *params);
GL_APICALL فراغ GL_APIENTRY glGetQueryObjecti64vEXT (GLuint id, GLenum pname, GLint64 *params);
GL_APICALL فراغ GL_APIENTRY glGetQueryObjectui64vEXT (GLuint id, GLenum pname, GLuint64 *params);
GL_APICALL فراغ GL_APIENTRY glGetInteger64vEXT (GLenum pname, GLint64 *داده);
#پایان_اگر
#پایان_اگر /* GL_EXT_disjoint_timer_query */

#اگر_تعریف_نشده GL_EXT_draw_buffers
#تعریف_کن GL_EXT_draw_buffers 1
#تعریف_کن GL_MAX_COLOR_ATTACHMENTS_EXT      0x8CDF
#تعریف_کن GL_MAX_DRAW_BUFFERS_EXT           0x8824
#تعریف_کن GL_DRAW_BUFFER0_EXT               0x8825
#تعریف_کن GL_DRAW_BUFFER1_EXT               0x8826
#تعریف_کن GL_DRAW_BUFFER2_EXT               0x8827
#تعریف_کن GL_DRAW_BUFFER3_EXT               0x8828
#تعریف_کن GL_DRAW_BUFFER4_EXT               0x8829
#تعریف_کن GL_DRAW_BUFFER5_EXT               0x882A
#تعریف_کن GL_DRAW_BUFFER6_EXT               0x882B
#تعریف_کن GL_DRAW_BUFFER7_EXT               0x882C
#تعریف_کن GL_DRAW_BUFFER8_EXT               0x882D
#تعریف_کن GL_DRAW_BUFFER9_EXT               0x882E
#تعریف_کن GL_DRAW_BUFFER10_EXT              0x882F
#تعریف_کن GL_DRAW_BUFFER11_EXT              0x8830
#تعریف_کن GL_DRAW_BUFFER12_EXT              0x8831
#تعریف_کن GL_DRAW_BUFFER13_EXT              0x8832
#تعریف_کن GL_DRAW_BUFFER14_EXT              0x8833
#تعریف_کن GL_DRAW_BUFFER15_EXT              0x8834
#تعریف_کن GL_COLOR_ATTACHMENT0_EXT          0x8CE0
#تعریف_کن GL_COLOR_ATTACHMENT1_EXT          0x8CE1
#تعریف_کن GL_COLOR_ATTACHMENT2_EXT          0x8CE2
#تعریف_کن GL_COLOR_ATTACHMENT3_EXT          0x8CE3
#تعریف_کن GL_COLOR_ATTACHMENT4_EXT          0x8CE4
#تعریف_کن GL_COLOR_ATTACHMENT5_EXT          0x8CE5
#تعریف_کن GL_COLOR_ATTACHMENT6_EXT          0x8CE6
#تعریف_کن GL_COLOR_ATTACHMENT7_EXT          0x8CE7
#تعریف_کن GL_COLOR_ATTACHMENT8_EXT          0x8CE8
#تعریف_کن GL_COLOR_ATTACHMENT9_EXT          0x8CE9
#تعریف_کن GL_COLOR_ATTACHMENT10_EXT         0x8CEA
#تعریف_کن GL_COLOR_ATTACHMENT11_EXT         0x8CEB
#تعریف_کن GL_COLOR_ATTACHMENT12_EXT         0x8CEC
#تعریف_کن GL_COLOR_ATTACHMENT13_EXT         0x8CED
#تعریف_کن GL_COLOR_ATTACHMENT14_EXT         0x8CEE
#تعریف_کن GL_COLOR_ATTACHMENT15_EXT         0x8CEF
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWBUFFERSEXTPROC) (GLsizei n, ثابت GLenum *bufs);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawBuffersEXT (GLsizei n, ثابت GLenum *bufs);
#پایان_اگر
#پایان_اگر /* GL_EXT_draw_buffers */

#اگر_تعریف_نشده GL_EXT_draw_buffers_نمایهای
#تعریف_کن GL_EXT_draw_buffers_نمایهای 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLENABLEIEXTPROC) (GLenum هدف, GLuint شاخص);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISABLEIEXTPROC) (GLenum هدف, GLuint شاخص);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONIEXTPROC) (GLuint buf, GLenum نما);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEIEXTPROC) (GLuint buf, GLenum نما_RGB, GLenum نما_Alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDFUNCIEXTPROC) (GLuint buf, GLenum src, GLenum dst);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEIEXTPROC) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOLORMASKIEXTPROC) (GLuint شاخص, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISENABLEDIEXTPROC) (GLenum هدف, GLuint شاخص);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glEnableiEXT (GLenum هدف, GLuint شاخص);
GL_APICALL فراغ GL_APIENTRY glDisableiEXT (GLenum هدف, GLuint شاخص);
GL_APICALL فراغ GL_APIENTRY glBlendEquationiEXT (GLuint buf, GLenum نما);
GL_APICALL فراغ GL_APIENTRY glBlendEquationSeparateiEXT (GLuint buf, GLenum نما_RGB, GLenum نما_Alpha);
GL_APICALL فراغ GL_APIENTRY glBlendFunciEXT (GLuint buf, GLenum src, GLenum dst);
GL_APICALL فراغ GL_APIENTRY glBlendFuncSeparateiEXT (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
GL_APICALL فراغ GL_APIENTRY glColorMaskiEXT (GLuint شاخص, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
GL_APICALL GLboolean GL_APIENTRY glIsEnablediEXT (GLenum هدف, GLuint شاخص);
#پایان_اگر
#پایان_اگر /* GL_EXT_draw_buffers_indexed */

#اگر_تعریف_نشده GL_EXT_draw_elements_پایه_رأس
#تعریف_کن GL_EXT_draw_elements_پایه_رأس 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSBASEVERTEXEXTPROC) (GLenum نما, GLsizei شمار, GLenum type, ثابت فراغ *indices, GLint basevertex);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWRANGEELEMENTSBASEVERTEXEXTPROC) (GLenum نما, GLuint شروع, GLuint انتها, GLsizei شمار, GLenum type, ثابت فراغ *indices, GLint basevertex);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXEXTPROC) (GLenum نما, GLsizei شمار, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLint basevertex);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Draw_Elements_پایه_رأس_EXT (GLenum نما, GLsizei شمار, GLenum type, ثابت فراغ *indices, GLint basevertex);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Range_Elements_پایه_رأس_EXT (GLenum نما, GLuint شروع, GLuint انتها, GLsizei شمار, GLenum type, ثابت فراغ *indices, GLint basevertex);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Elements_Instanced_پایه_رأس_EXT (GLenum نما, GLsizei شمار, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLint basevertex);
#پایان_اگر
#پایان_اگر /* GL_EXT_draw_elements_base_vertex */

#اگر_تعریف_نشده GL_EXT_draw_instanced
#تعریف_کن GL_EXT_draw_instanced 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDEXTPROC) (GLenum نما, GLint شروع, GLsizei شمار, GLsizei primcount);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDEXTPROC) (GLenum نما, GLsizei شمار, GLenum type, ثابت فراغ *indices, GLsizei primcount);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawArraysInstancedEXT (GLenum نما, GLint شروع, GLsizei شمار, GLsizei primcount);
GL_APICALL فراغ GL_APIENTRY glDrawElementsInstancedEXT (GLenum نما, GLsizei شمار, GLenum type, ثابت فراغ *indices, GLsizei primcount);
#پایان_اگر
#پایان_اگر /* GL_EXT_draw_instanced */

#اگر_تعریف_نشده GL_EXT_draw_transform_feedback
#تعریف_کن GL_EXT_draw_transform_feedback 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKEXTPROC) (GLenum نما, GLuint id);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDEXTPROC) (GLenum نما, GLuint id, GLsizei instancecount);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawTransformFeedbackEXT (GLenum نما, GLuint id);
GL_APICALL فراغ GL_APIENTRY glDrawTransformFeedbackInstancedEXT (GLenum نما, GLuint id, GLsizei instancecount);
#پایان_اگر
#پایان_اگر /* GL_EXT_draw_transform_feedback */

#اگر_تعریف_نشده GL_EXT_external_میانگیر
#تعریف_کن GL_EXT_external_میانگیر 1
تعريفنوع فراغ *GLegl_Client_میانگیر_EXT;
تعريفنوع فراغ (GL_APIENTRYP PFNGLBUFFERSTORAGEEXTERNALEXTPROC) (GLenum هدف, GLintptr جابه_جایی_2, GLsizeiptr اندازه, GLegl_Client_میانگیر_EXT client_میانگیر, GLbitfield flags);
تعريفنوع فراغ (GL_APIENTRYP PFNGLNAMEDBUFFERSTORAGEEXTERNALEXTPROC) (GLuint میانگیر_2, GLintptr جابه_جایی_2, GLsizeiptr اندازه, GLegl_Client_میانگیر_EXT client_میانگیر, GLbitfield flags);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_میانگیر_Storage_External_EXT (GLenum هدف, GLintptr جابه_جایی_2, GLsizeiptr اندازه, GLegl_Client_میانگیر_EXT client_میانگیر, GLbitfield flags);
GL_APICALL فراغ GL_APIENTRY gl_Named_میانگیر_Storage_External_EXT (GLuint میانگیر_2, GLintptr جابه_جایی_2, GLsizeiptr اندازه, GLegl_Client_میانگیر_EXT client_میانگیر, GLbitfield flags);
#پایان_اگر
#پایان_اگر /* GL_EXT_external_buffer */

#اگر_تعریف_نشده GL_EXT_float_blend
#تعریف_کن GL_EXT_float_blend 1
#پایان_اگر /* GL_EXT_float_blend */

#اگر_تعریف_نشده GL_EXT_fragment_shading_نرخ
#تعریف_کن GL_EXT_fragment_shading_نرخ 1
#تعریف_کن GL_SHADING_نرخ_1_X1_PIXELS_EXT    0x96A6
#تعریف_کن GL_SHADING_نرخ_1_X2_PIXELS_EXT    0x96A7
#تعریف_کن GL_SHADING_نرخ_2_X1_PIXELS_EXT    0x96A8
#تعریف_کن GL_SHADING_نرخ_2_X2_PIXELS_EXT    0x96A9
#تعریف_کن GL_SHADING_نرخ_1_X4_PIXELS_EXT    0x96AA
#تعریف_کن GL_SHADING_نرخ_4_X1_PIXELS_EXT    0x96AB
#تعریف_کن GL_SHADING_نرخ_4_X2_PIXELS_EXT    0x96AC
#تعریف_کن GL_SHADING_نرخ_2_X4_PIXELS_EXT    0x96AD
#تعریف_کن GL_SHADING_نرخ_4_X4_PIXELS_EXT    0x96AE
#تعریف_کن GL_SHADING_نرخ_EXT               0x96D0
#تعریف_کن GL_SHADING_نرخ_ATTACHMENT_EXT    0x96D1
#تعریف_کن GL_FRAGMENT_SHADING_نرخ_COMBINER_OP_KEEP_EXT 0x96D2
#تعریف_کن GL_FRAGMENT_SHADING_نرخ_COMBINER_OP_REPLACE_EXT 0x96D3
#تعریف_کن GL_FRAGMENT_SHADING_نرخ_COMBINER_OP_MIN_EXT 0x96D4
#تعریف_کن GL_FRAGMENT_SHADING_نرخ_COMBINER_OP_MAX_EXT 0x96D5
#تعریف_کن GL_FRAGMENT_SHADING_نرخ_COMBINER_OP_MUL_EXT 0x96D6
#تعریف_کن GL_MIN_FRAGMENT_SHADING_نرخ_ATTACHMENT_TEXEL_عرض_EXT 0x96D7
#تعریف_کن GL_MAX_FRAGMENT_SHADING_نرخ_ATTACHMENT_TEXEL_عرض_EXT 0x96D8
#تعریف_کن GL_MIN_FRAGMENT_SHADING_نرخ_ATTACHMENT_TEXEL_ارتفاع_EXT 0x96D9
#تعریف_کن GL_MAX_FRAGMENT_SHADING_نرخ_ATTACHMENT_TEXEL_ارتفاع_EXT 0x96DA
#تعریف_کن GL_MAX_FRAGMENT_SHADING_نرخ_ATTACHMENT_TEXEL_ASPECT_نسبت_EXT 0x96DB
#تعریف_کن GL_MAX_FRAGMENT_SHADING_نرخ_ATTACHMENT_LAYERS_EXT 0x96DC
#تعریف_کن GL_FRAGMENT_SHADING_نرخ_WITH_SHADER_عمق_STENCIL_WRITES_SUPPORTED_EXT 0x96DD
#تعریف_کن GL_FRAGMENT_SHADING_نرخ_WITH_SAMPLE_ماسک_SUPPORTED_EXT 0x96DE
#تعریف_کن GL_FRAGMENT_SHADING_نرخ_ATTACHMENT_WITH_DEFAULT_FRAMEBUFFER_SUPPORTED_EXT 0x96DF
#تعریف_کن GL_FRAGMENT_SHADING_نرخ_NON_TRIVIAL_COMBINERS_SUPPORTED_EXT 0x8F6F
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFRAGMENTSHADINGRATESEXTPROC) (GLsizei samples, GLsizei max_شمار, GLsizei *شمار, GLenum *shadingRates);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADINGRATEEXTPROC) (GLenum نرخ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADINGRATECOMBINEROPSEXTPROC) (GLenum combinerOp0, GLenum combinerOp1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERSHADINGRATEEXTPROC) (GLenum هدف, GLenum attachment, GLuint texture, GLint پایه_Layer, GLsizei رقم_Layers, GLsizei texel_عرض, GLsizei texel_ارتفاع);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glGetFragmentShadingRatesEXT (GLsizei samples, GLsizei max_شمار, GLsizei *شمار, GLenum *shadingRates);
GL_APICALL فراغ GL_APIENTRY gl_Shading_نرخ_EXT (GLenum نرخ);
GL_APICALL فراغ GL_APIENTRY gl_Shading_نرخ_Combiner_Ops_EXT (GLenum combinerOp0, GLenum combinerOp1);
GL_APICALL فراغ GL_APIENTRY gl_Framebuffer_Shading_نرخ_EXT (GLenum هدف, GLenum attachment, GLuint texture, GLint پایه_Layer, GLsizei رقم_Layers, GLsizei texel_عرض, GLsizei texel_ارتفاع);
#پایان_اگر
#پایان_اگر /* GL_EXT_fragment_shading_rate */

#اگر_تعریف_نشده GL_EXT_framebuffer_blit_layers
#تعریف_کن GL_EXT_framebuffer_blit_layers 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLITFRAMEBUFFERLAYERSEXTPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield ماسک, GLenum filter);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLITFRAMEBUFFERLAYEREXTPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint srcLayer, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLint dstLayer, GLbitfield ماسک, GLenum filter);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glBlitFramebufferLayersEXT (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield ماسک, GLenum filter);
GL_APICALL فراغ GL_APIENTRY glBlitFramebufferLayerEXT (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint srcLayer, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLint dstLayer, GLbitfield ماسک, GLenum filter);
#پایان_اگر
#پایان_اگر /* GL_EXT_framebuffer_blit_layers */

#اگر_تعریف_نشده GL_EXT_geometry_نقطه_اندازه
#تعریف_کن GL_EXT_geometry_نقطه_اندازه 1
#پایان_اگر /* GL_EXT_geometry_point_size */

#اگر_تعریف_نشده GL_EXT_geometry_shader
#تعریف_کن GL_EXT_geometry_shader 1
#تعریف_کن GL_GEOMETRY_SHADER_EXT            0x8DD9
#تعریف_کن GL_GEOMETRY_SHADER_بیت_EXT        0x00000004
#تعریف_کن GL_GEOMETRY_LINKED_VERTICES_بیرون_EXT 0x8916
#تعریف_کن GL_GEOMETRY_LINKED_درون_داد_TYPE_EXT 0x8917
#تعریف_کن GL_GEOMETRY_LINKED_OUTPUT_TYPE_EXT 0x8918
#تعریف_کن GL_GEOMETRY_SHADER_INVOCATIONS_EXT 0x887F
#تعریف_کن GL_LAYER_PROVOKING_رأس_EXT     0x825E
#تعریف_کن GL_سطرها_ADJACENCY_EXT            0x000A
#تعریف_کن GL_سطر_STRIP_ADJACENCY_EXT       0x000B
#تعریف_کن GL_TRIANGLES_ADJACENCY_EXT        0x000C
#تعریف_کن GL_TRIANGLE_STRIP_ADJACENCY_EXT   0x000D
#تعریف_کن GL_MAX_GEOMETRY_یکنواخت_COMPONENTS_EXT 0x8DDF
#تعریف_کن GL_MAX_GEOMETRY_یکنواخت_بلوکها_EXT 0x8A2C
#تعریف_کن GL_MAX_COMBINED_GEOMETRY_یکنواخت_COMPONENTS_EXT 0x8A32
#تعریف_کن GL_MAX_GEOMETRY_درون_داد_COMPONENTS_EXT 0x9123
#تعریف_کن GL_MAX_GEOMETRY_OUTPUT_COMPONENTS_EXT 0x9124
#تعریف_کن GL_MAX_GEOMETRY_OUTPUT_VERTICES_EXT 0x8DE0
#تعریف_کن GL_MAX_GEOMETRY_مجموع_OUTPUT_COMPONENTS_EXT 0x8DE1
#تعریف_کن GL_MAX_GEOMETRY_SHADER_INVOCATIONS_EXT 0x8E5A
#تعریف_کن GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_EXT 0x8C29
#تعریف_کن GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS_EXT 0x92CF
#تعریف_کن GL_MAX_GEOMETRY_ATOMIC_COUNTERS_EXT 0x92D5
#تعریف_کن GL_MAX_GEOMETRY_IMAGE_UNIFORMS_EXT 0x90CD
#تعریف_کن GL_MAX_GEOMETRY_SHADER_STORAGE_بلوکها_EXT 0x90D7
#تعریف_کن GL_اولی_رأس_CONVENTION_EXT    0x8E4D
#تعریف_کن GL_آخرین_رأس_CONVENTION_EXT     0x8E4E
#تعریف_کن GL_UNDEFINED_رأس_EXT           0x8260
#تعریف_کن GL_PRIMITIVES_GENERATED_EXT       0x8C87
#تعریف_کن GL_FRAMEBUFFER_DEFAULT_LAYERS_EXT 0x9312
#تعریف_کن GL_MAX_FRAMEBUFFER_LAYERS_EXT     0x9317
#تعریف_کن GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_EXT 0x8DA8
#تعریف_کن GL_FRAMEBUFFER_ATTACHMENT_LAYERED_EXT 0x8DA7
#تعریف_کن GL_REFERENCED_BY_GEOMETRY_SHADER_EXT 0x9309
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREEXTPROC) (GLenum هدف, GLenum attachment, GLuint texture, GLint level);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferTextureEXT (GLenum هدف, GLenum attachment, GLuint texture, GLint level);
#پایان_اگر
#پایان_اگر /* GL_EXT_geometry_shader */

#اگر_تعریف_نشده GL_EXT_gpu_shader5
#تعریف_کن GL_EXT_gpu_shader5 1
#پایان_اگر /* GL_EXT_gpu_shader5 */

#اگر_تعریف_نشده GL_EXT_instanced_arrays
#تعریف_کن GL_EXT_instanced_arrays 1
#تعریف_کن GL_رأس_ATTRIB_ARRAY_مقسوم_علیه_EXT 0x88FE
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBDIVISOREXTPROC) (GLuint شاخص, GLuint مقسوم_علیه);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_رأس_Attrib_مقسوم_علیه_EXT (GLuint شاخص, GLuint مقسوم_علیه);
#پایان_اگر
#پایان_اگر /* GL_EXT_instanced_arrays */

#اگر_تعریف_نشده GL_EXT_map_میانگیر_range
#تعریف_کن GL_EXT_map_میانگیر_range 1
#تعریف_کن GL_MAP_READ_بیت_EXT               0x0001
#تعریف_کن GL_MAP_WRITE_بیت_EXT              0x0002
#تعریف_کن GL_MAP_INVALIDATE_RANGE_بیت_EXT   0x0004
#تعریف_کن GL_MAP_INVALIDATE_میانگیر_بیت_EXT  0x0008
#تعریف_کن GL_MAP_FLUSH_EXPLICIT_بیت_EXT     0x0010
#تعریف_کن GL_MAP_UNSYNCHRONIZED_بیت_EXT     0x0020
تعريفنوع فراغ *(GL_APIENTRYP PFNGLMAPBUFFERRANGEEXTPROC) (GLenum هدف, GLintptr جابه_جایی_2, GLsizeiptr درازی, GLbitfield access);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEEXTPROC) (GLenum هدف, GLintptr جابه_جایی_2, GLsizeiptr درازی);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ *GL_APIENTRY gl_Map_میانگیر_Range_EXT (GLenum هدف, GLintptr جابه_جایی_2, GLsizeiptr درازی, GLbitfield access);
GL_APICALL فراغ GL_APIENTRY gl_Flush_Mapped_میانگیر_Range_EXT (GLenum هدف, GLintptr جابه_جایی_2, GLsizeiptr درازی);
#پایان_اگر
#پایان_اگر /* GL_EXT_map_buffer_range */

#اگر_تعریف_نشده GL_EXT_حافظه_object
#تعریف_کن GL_EXT_حافظه_object 1
#تعریف_کن GL_TEXTURE_TILING_EXT             0x9580
#تعریف_کن GL_DEDICATED_حافظه_OBJECT_EXT    0x9581
#تعریف_کن GL_PROTECTED_حافظه_OBJECT_EXT    0x959B
#تعریف_کن GL_رقم_TILING_TYPES_EXT           0x9582
#تعریف_کن GL_TILING_TYPES_EXT               0x9583
#تعریف_کن GL_OPTIMAL_TILING_EXT             0x9584
#تعریف_کن GL_خطی_TILING_EXT              0x9585
#تعریف_کن GL_رقم_DEVICE_UUIDS_EXT           0x9596
#تعریف_کن GL_DEVICE_UUID_EXT                0x9597
#تعریف_کن GL_DRIVER_UUID_EXT                0x9598
#تعریف_کن GL_UUID_اندازه_EXT                  16
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETUNSIGNEDBYTEVEXTPROC) (GLenum pname, GLubyte *داده);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETUNSIGNEDBYTEI_VEXTPROC) (GLenum هدف, GLuint شاخص, GLubyte *داده);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEMEMORYOBJECTSEXTPROC) (GLsizei n, ثابت GLuint *حافظه_Objects);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISMEMORYOBJECTEXTPROC) (GLuint حافظه_Object);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCREATEMEMORYOBJECTSEXTPROC) (GLsizei n, GLuint *حافظه_Objects);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMEMORYOBJECTPARAMETERIVEXTPROC) (GLuint حافظه_Object, GLenum pname, ثابت GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETMEMORYOBJECTPARAMETERIVEXTPROC) (GLuint حافظه_Object, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGEMEM2DEXTPROC) (GLenum هدف, GLsizei سطوح, GLenum داخلی_Format, GLsizei عرض, GLsizei ارتفاع, GLuint حافظه, GLuint64 جابه_جایی_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGEMEM2DMULTISAMPLEEXTPROC) (GLenum هدف, GLsizei samples, GLenum داخلی_Format, GLsizei عرض, GLsizei ارتفاع, GLboolean fixedSampleLocations, GLuint حافظه, GLuint64 جابه_جایی_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGEMEM3DEXTPROC) (GLenum هدف, GLsizei سطوح, GLenum داخلی_Format, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLuint حافظه, GLuint64 جابه_جایی_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGEMEM3DMULTISAMPLEEXTPROC) (GLenum هدف, GLsizei samples, GLenum داخلی_Format, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLboolean fixedSampleLocations, GLuint حافظه, GLuint64 جابه_جایی_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBUFFERSTORAGEMEMEXTPROC) (GLenum هدف, GLsizeiptr اندازه, GLuint حافظه, GLuint64 جابه_جایی_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGEMEM2DEXTPROC) (GLuint texture, GLsizei سطوح, GLenum داخلی_Format, GLsizei عرض, GLsizei ارتفاع, GLuint حافظه, GLuint64 جابه_جایی_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGEMEM2DMULTISAMPLEEXTPROC) (GLuint texture, GLsizei samples, GLenum داخلی_Format, GLsizei عرض, GLsizei ارتفاع, GLboolean fixedSampleLocations, GLuint حافظه, GLuint64 جابه_جایی_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGEMEM3DEXTPROC) (GLuint texture, GLsizei سطوح, GLenum داخلی_Format, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLuint حافظه, GLuint64 جابه_جایی_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGEMEM3DMULTISAMPLEEXTPROC) (GLuint texture, GLsizei samples, GLenum داخلی_Format, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLboolean fixedSampleLocations, GLuint حافظه, GLuint64 جابه_جایی_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLNAMEDBUFFERSTORAGEMEMEXTPROC) (GLuint میانگیر_2, GLsizeiptr اندازه, GLuint حافظه, GLuint64 جابه_جایی_2);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glGetUnsignedBytevEXT (GLenum pname, GLubyte *داده);
GL_APICALL فراغ GL_APIENTRY glGetUnsignedBytei_vEXT (GLenum هدف, GLuint شاخص, GLubyte *داده);
GL_APICALL فراغ GL_APIENTRY gl_Delete_حافظه_Objects_EXT (GLsizei n, ثابت GLuint *حافظه_Objects);
GL_APICALL GLboolean GL_APIENTRY gl_Is_حافظه_Object_EXT (GLuint حافظه_Object);
GL_APICALL فراغ GL_APIENTRY gl_Create_حافظه_Objects_EXT (GLsizei n, GLuint *حافظه_Objects);
GL_APICALL فراغ GL_APIENTRY gl_حافظه_Object_Parameteriv_EXT (GLuint حافظه_Object, GLenum pname, ثابت GLint *params);
GL_APICALL فراغ GL_APIENTRY gl_Get_حافظه_Object_Parameteriv_EXT (GLuint حافظه_Object, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glTexStorageMem2DEXT (GLenum هدف, GLsizei سطوح, GLenum داخلی_Format, GLsizei عرض, GLsizei ارتفاع, GLuint حافظه, GLuint64 جابه_جایی_2);
GL_APICALL فراغ GL_APIENTRY glTexStorageMem2DMultisampleEXT (GLenum هدف, GLsizei samples, GLenum داخلی_Format, GLsizei عرض, GLsizei ارتفاع, GLboolean fixedSampleLocations, GLuint حافظه, GLuint64 جابه_جایی_2);
GL_APICALL فراغ GL_APIENTRY glTexStorageMem3DEXT (GLenum هدف, GLsizei سطوح, GLenum داخلی_Format, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLuint حافظه, GLuint64 جابه_جایی_2);
GL_APICALL فراغ GL_APIENTRY glTexStorageMem3DMultisampleEXT (GLenum هدف, GLsizei samples, GLenum داخلی_Format, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLboolean fixedSampleLocations, GLuint حافظه, GLuint64 جابه_جایی_2);
GL_APICALL فراغ GL_APIENTRY gl_میانگیر_Storage_Mem_EXT (GLenum هدف, GLsizeiptr اندازه, GLuint حافظه, GLuint64 جابه_جایی_2);
GL_APICALL فراغ GL_APIENTRY glTextureStorageMem2DEXT (GLuint texture, GLsizei سطوح, GLenum داخلی_Format, GLsizei عرض, GLsizei ارتفاع, GLuint حافظه, GLuint64 جابه_جایی_2);
GL_APICALL فراغ GL_APIENTRY glTextureStorageMem2DMultisampleEXT (GLuint texture, GLsizei samples, GLenum داخلی_Format, GLsizei عرض, GLsizei ارتفاع, GLboolean fixedSampleLocations, GLuint حافظه, GLuint64 جابه_جایی_2);
GL_APICALL فراغ GL_APIENTRY glTextureStorageMem3DEXT (GLuint texture, GLsizei سطوح, GLenum داخلی_Format, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLuint حافظه, GLuint64 جابه_جایی_2);
GL_APICALL فراغ GL_APIENTRY glTextureStorageMem3DMultisampleEXT (GLuint texture, GLsizei samples, GLenum داخلی_Format, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLboolean fixedSampleLocations, GLuint حافظه, GLuint64 جابه_جایی_2);
GL_APICALL فراغ GL_APIENTRY gl_Named_میانگیر_Storage_Mem_EXT (GLuint میانگیر_2, GLsizeiptr اندازه, GLuint حافظه, GLuint64 جابه_جایی_2);
#پایان_اگر
#پایان_اگر /* GL_EXT_memory_object */

#اگر_تعریف_نشده GL_EXT_حافظه_object_fd
#تعریف_کن GL_EXT_حافظه_object_fd 1
#تعریف_کن GL_HANDLE_TYPE_OPAQUE_FD_EXT      0x9586
تعريفنوع فراغ (GL_APIENTRYP PFNGLIMPORTMEMORYFDEXTPROC) (GLuint حافظه, GLuint64 اندازه, GLenum handleType, GLint fd);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Import_حافظه_Fd_EXT (GLuint حافظه, GLuint64 اندازه, GLenum handleType, GLint fd);
#پایان_اگر
#پایان_اگر /* GL_EXT_memory_object_fd */

#اگر_تعریف_نشده GL_EXT_حافظه_object_win32
#تعریف_کن GL_EXT_حافظه_object_win32 1
#تعریف_کن GL_HANDLE_TYPE_OPAQUE_WIN32_EXT   0x9587
#تعریف_کن GL_HANDLE_TYPE_OPAQUE_WIN32_KMT_EXT 0x9588
#تعریف_کن GL_DEVICE_LUID_EXT                0x9599
#تعریف_کن GL_DEVICE_گره_ماسک_EXT           0x959A
#تعریف_کن GL_LUID_اندازه_EXT                  8
#تعریف_کن GL_HANDLE_TYPE_D3D12_TILEPOOL_EXT 0x9589
#تعریف_کن GL_HANDLE_TYPE_D3D12_RESOURCE_EXT 0x958A
#تعریف_کن GL_HANDLE_TYPE_D3D11_IMAGE_EXT    0x958B
#تعریف_کن GL_HANDLE_TYPE_D3D11_IMAGE_KMT_EXT 0x958C
تعريفنوع فراغ (GL_APIENTRYP PFNGLIMPORTMEMORYWIN32HANDLEEXTPROC) (GLuint حافظه, GLuint64 اندازه, GLenum handleType, فراغ *handle);
تعريفنوع فراغ (GL_APIENTRYP PFNGLIMPORTMEMORYWIN32NAMEEXTPROC) (GLuint حافظه, GLuint64 اندازه, GLenum handleType, ثابت فراغ *name);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Import_حافظه_Win32_Handle_EXT (GLuint حافظه, GLuint64 اندازه, GLenum handleType, فراغ *handle);
GL_APICALL فراغ GL_APIENTRY gl_Import_حافظه_Win32_Name_EXT (GLuint حافظه, GLuint64 اندازه, GLenum handleType, ثابت فراغ *name);
#پایان_اگر
#پایان_اگر /* GL_EXT_memory_object_win32 */

#اگر_تعریف_نشده GL_EXT_mesh_shader
#تعریف_کن GL_EXT_mesh_shader 1
#تعریف_کن GL_MESH_SHADER_EXT                0x9559
#تعریف_کن GL_TASK_SHADER_EXT                0x955A
#تعریف_کن GL_MAX_MESH_یکنواخت_بلوکها_EXT    0x8E60
#تعریف_کن GL_MAX_MESH_TEXTURE_IMAGE_UNITS_EXT 0x8E61
#تعریف_کن GL_MAX_MESH_IMAGE_UNIFORMS_EXT    0x8E62
#تعریف_کن GL_MAX_MESH_یکنواخت_COMPONENTS_EXT 0x8E63
#تعریف_کن GL_MAX_MESH_ATOMIC_COUNTER_BUFFERS_EXT 0x8E64
#تعریف_کن GL_MAX_MESH_ATOMIC_COUNTERS_EXT   0x8E65
#تعریف_کن GL_MAX_MESH_SHADER_STORAGE_بلوکها_EXT 0x8E66
#تعریف_کن GL_MAX_COMBINED_MESH_یکنواخت_COMPONENTS_EXT 0x8E67
#تعریف_کن GL_MAX_TASK_یکنواخت_بلوکها_EXT    0x8E68
#تعریف_کن GL_MAX_TASK_TEXTURE_IMAGE_UNITS_EXT 0x8E69
#تعریف_کن GL_MAX_TASK_IMAGE_UNIFORMS_EXT    0x8E6A
#تعریف_کن GL_MAX_TASK_یکنواخت_COMPONENTS_EXT 0x8E6B
#تعریف_کن GL_MAX_TASK_ATOMIC_COUNTER_BUFFERS_EXT 0x8E6C
#تعریف_کن GL_MAX_TASK_ATOMIC_COUNTERS_EXT   0x8E6D
#تعریف_کن GL_MAX_TASK_SHADER_STORAGE_بلوکها_EXT 0x8E6E
#تعریف_کن GL_MAX_COMBINED_TASK_یکنواخت_COMPONENTS_EXT 0x8E6F
#تعریف_کن GL_MAX_TASK_WORK_گروه_مجموع_شمار_EXT 0x9740
#تعریف_کن GL_MAX_MESH_WORK_گروه_مجموع_شمار_EXT 0x9741
#تعریف_کن GL_MAX_MESH_WORK_گروه_INVOCATIONS_EXT 0x9757
#تعریف_کن GL_MAX_TASK_WORK_گروه_INVOCATIONS_EXT 0x9759
#تعریف_کن GL_MAX_TASK_PAYLOAD_اندازه_EXT      0x9742
#تعریف_کن GL_MAX_TASK_SHARED_حافظه_اندازه_EXT 0x9743
#تعریف_کن GL_MAX_MESH_SHARED_حافظه_اندازه_EXT 0x9744
#تعریف_کن GL_MAX_TASK_PAYLOAD_AND_SHARED_حافظه_اندازه_EXT 0x9745
#تعریف_کن GL_MAX_MESH_PAYLOAD_AND_SHARED_حافظه_اندازه_EXT 0x9746
#تعریف_کن GL_MAX_MESH_OUTPUT_حافظه_اندازه_EXT 0x9747
#تعریف_کن GL_MAX_MESH_PAYLOAD_AND_OUTPUT_حافظه_اندازه_EXT 0x9748
#تعریف_کن GL_MAX_MESH_OUTPUT_VERTICES_EXT   0x9538
#تعریف_کن GL_MAX_MESH_OUTPUT_PRIMITIVES_EXT 0x9756
#تعریف_کن GL_MAX_MESH_OUTPUT_COMPONENTS_EXT 0x9749
#تعریف_کن GL_MAX_MESH_OUTPUT_LAYERS_EXT     0x974A
#تعریف_کن GL_MAX_MESH_MULTIVIEW_VIEW_شمار_EXT 0x9557
#تعریف_کن GL_MESH_OUTPUT_در_هر_رأس_GRANULARITY_EXT 0x92DF
#تعریف_کن GL_MESH_OUTPUT_در_هر_PRIMITIVE_GRANULARITY_EXT 0x9543
#تعریف_کن GL_MAX_PREFERRED_TASK_WORK_گروه_INVOCATIONS_EXT 0x974B
#تعریف_کن GL_MAX_PREFERRED_MESH_WORK_گروه_INVOCATIONS_EXT 0x974C
#تعریف_کن GL_MESH_PREFERS_LOCAL_INVOCATION_رأس_OUTPUT_EXT 0x974D
#تعریف_کن GL_MESH_PREFERS_LOCAL_INVOCATION_PRIMITIVE_OUTPUT_EXT 0x974E
#تعریف_کن GL_MESH_PREFERS_COMPACT_رأس_OUTPUT_EXT 0x974F
#تعریف_کن GL_MESH_PREFERS_COMPACT_PRIMITIVE_OUTPUT_EXT 0x9750
#تعریف_کن GL_MAX_TASK_WORK_گروه_شمار_EXT  0x9751
#تعریف_کن GL_MAX_MESH_WORK_گروه_شمار_EXT  0x9752
#تعریف_کن GL_MAX_MESH_WORK_گروه_اندازه_EXT   0x9758
#تعریف_کن GL_MAX_TASK_WORK_گروه_اندازه_EXT   0x975A
#تعریف_کن GL_MESH_WORK_گروه_اندازه_EXT       0x953E
#تعریف_کن GL_TASK_WORK_گروه_اندازه_EXT       0x953F
#تعریف_کن GL_MESH_VERTICES_بیرون_EXT          0x9579
#تعریف_کن GL_MESH_PRIMITIVES_بیرون_EXT        0x957A
#تعریف_کن GL_MESH_OUTPUT_TYPE_EXT           0x957B
#تعریف_کن GL_یکنواخت_بلوک_REFERENCED_BY_MESH_SHADER_EXT 0x959C
#تعریف_کن GL_یکنواخت_بلوک_REFERENCED_BY_TASK_SHADER_EXT 0x959D
#تعریف_کن GL_REFERENCED_BY_MESH_SHADER_EXT  0x95A0
#تعریف_کن GL_REFERENCED_BY_TASK_SHADER_EXT  0x95A1
#تعریف_کن GL_TASK_SHADER_INVOCATIONS_EXT    0x9753
#تعریف_کن GL_MESH_SHADER_INVOCATIONS_EXT    0x9754
#تعریف_کن GL_MESH_PRIMITIVES_GENERATED_EXT  0x9755
#تعریف_کن GL_MESH_SHADER_بیت_EXT            0x00000040
#تعریف_کن GL_TASK_SHADER_بیت_EXT            0x00000080
#تعریف_کن GL_MESH_SUBROUTINE_EXT            0x957C
#تعریف_کن GL_TASK_SUBROUTINE_EXT            0x957D
#تعریف_کن GL_MESH_SUBROUTINE_یکنواخت_EXT    0x957E
#تعریف_کن GL_TASK_SUBROUTINE_یکنواخت_EXT    0x957F
#تعریف_کن GL_ATOMIC_COUNTER_میانگیر_REFERENCED_BY_MESH_SHADER_EXT 0x959E
#تعریف_کن GL_ATOMIC_COUNTER_میانگیر_REFERENCED_BY_TASK_SHADER_EXT 0x959F
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWMESHTASKSEXTPROC) (GLuint رقم_groups_x, GLuint رقم_groups_y, GLuint رقم_groups_z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWMESHTASKSINDIRECTEXTPROC) (GLintptr غیرمستقیم);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWMESHTASKSINDIRECTEXTPROC) (GLintptr غیرمستقیم, GLsizei drawcount, GLsizei stride);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTEXTPROC) (GLintptr غیرمستقیم, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawMeshTasksEXT (GLuint رقم_groups_x, GLuint رقم_groups_y, GLuint رقم_groups_z);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Mesh_Tasks_غیرمستقیم_EXT (GLintptr غیرمستقیم);
GL_APICALL فراغ GL_APIENTRY gl_Multi_Draw_Mesh_Tasks_غیرمستقیم_EXT (GLintptr غیرمستقیم, GLsizei drawcount, GLsizei stride);
GL_APICALL فراغ GL_APIENTRY gl_Multi_Draw_Mesh_Tasks_غیرمستقیم_شمار_EXT (GLintptr غیرمستقیم, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
#پایان_اگر
#پایان_اگر /* GL_EXT_mesh_shader */

#اگر_تعریف_نشده GL_EXT_multi_draw_arrays
#تعریف_کن GL_EXT_multi_draw_arrays 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWARRAYSEXTPROC) (GLenum نما, ثابت GLint *اولی, ثابت GLsizei *شمار, GLsizei primcount);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSEXTPROC) (GLenum نما, ثابت GLsizei *شمار, GLenum type, ثابت فراغ *ثابت*indices, GLsizei primcount);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glMultiDrawArraysEXT (GLenum نما, ثابت GLint *اولی, ثابت GLsizei *شمار, GLsizei primcount);
GL_APICALL فراغ GL_APIENTRY glMultiDrawElementsEXT (GLenum نما, ثابت GLsizei *شمار, GLenum type, ثابت فراغ *ثابت*indices, GLsizei primcount);
#پایان_اگر
#پایان_اگر /* GL_EXT_multi_draw_arrays */

#اگر_تعریف_نشده GL_EXT_multi_draw_غیرمستقیم
#تعریف_کن GL_EXT_multi_draw_غیرمستقیم 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWARRAYSINDIRECTEXTPROC) (GLenum نما, ثابت فراغ *غیرمستقیم, GLsizei drawcount, GLsizei stride);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSINDIRECTEXTPROC) (GLenum نما, GLenum type, ثابت فراغ *غیرمستقیم, GLsizei drawcount, GLsizei stride);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Multi_Draw_Arrays_غیرمستقیم_EXT (GLenum نما, ثابت فراغ *غیرمستقیم, GLsizei drawcount, GLsizei stride);
GL_APICALL فراغ GL_APIENTRY gl_Multi_Draw_Elements_غیرمستقیم_EXT (GLenum نما, GLenum type, ثابت فراغ *غیرمستقیم, GLsizei drawcount, GLsizei stride);
#پایان_اگر
#پایان_اگر /* GL_EXT_multi_draw_indirect */

#اگر_تعریف_نشده GL_EXT_multisampled_compatibility
#تعریف_کن GL_EXT_multisampled_compatibility 1
#تعریف_کن GL_MULTISAMPLE_EXT                0x809D
#تعریف_کن GL_SAMPLE_ALPHA_مقصد_ONE_EXT        0x809F
#پایان_اگر /* GL_EXT_multisampled_compatibility */

#اگر_تعریف_نشده GL_EXT_multisampled_render_مقصد_texture
#تعریف_کن GL_EXT_multisampled_render_مقصد_texture 1
#تعریف_کن GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SAMPLES_EXT 0x8D6C
#تعریف_کن GL_RENDERBUFFER_SAMPLES_EXT       0x8CAB
#تعریف_کن GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT 0x8D56
#تعریف_کن GL_MAX_SAMPLES_EXT                0x8D57
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEEXTPROC) (GLenum هدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glRenderbufferStorageMultisampleEXT (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
GL_APICALL فراغ GL_APIENTRY glFramebufferTexture2DMultisampleEXT (GLenum هدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#پایان_اگر
#پایان_اگر /* GL_EXT_multisampled_render_to_texture */

#اگر_تعریف_نشده GL_EXT_multisampled_render_مقصد_texture2
#تعریف_کن GL_EXT_multisampled_render_مقصد_texture2 1
#پایان_اگر /* GL_EXT_multisampled_render_to_texture2 */

#اگر_تعریف_نشده GL_EXT_multiview_draw_buffers
#تعریف_کن GL_EXT_multiview_draw_buffers 1
#تعریف_کن GL_COLOR_ATTACHMENT_EXT           0x90F0
#تعریف_کن GL_MULTIVIEW_EXT                  0x90F1
#تعریف_کن GL_DRAW_میانگیر_EXT                0x0C01
#تعریف_کن GL_READ_میانگیر_EXT                0x0C02
#تعریف_کن GL_MAX_MULTIVIEW_BUFFERS_EXT      0x90F2
تعريفنوع فراغ (GL_APIENTRYP PFNGLREADBUFFERINDEXEDEXTPROC) (GLenum src, GLint شاخص);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWBUFFERSINDEXEDEXTPROC) (GLint n, ثابت GLenum *location, ثابت GLint *indices);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTEGERI_VEXTPROC) (GLenum هدف, GLuint شاخص, GLint *داده);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Read_میانگیر_نمایهای_EXT (GLenum src, GLint شاخص);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Buffers_نمایهای_EXT (GLint n, ثابت GLenum *location, ثابت GLint *indices);
GL_APICALL فراغ GL_APIENTRY glGetIntegeri_vEXT (GLenum هدف, GLuint شاخص, GLint *داده);
#پایان_اگر
#پایان_اگر /* GL_EXT_multiview_draw_buffers */

#اگر_تعریف_نشده GL_EXT_multiview_tessellation_geometry_shader
#تعریف_کن GL_EXT_multiview_tessellation_geometry_shader 1
#پایان_اگر /* GL_EXT_multiview_tessellation_geometry_shader */

#اگر_تعریف_نشده GL_EXT_multiview_texture_multisample
#تعریف_کن GL_EXT_multiview_texture_multisample 1
#پایان_اگر /* GL_EXT_multiview_texture_multisample */

#اگر_تعریف_نشده GL_EXT_multiview_timer_query
#تعریف_کن GL_EXT_multiview_timer_query 1
#پایان_اگر /* GL_EXT_multiview_timer_query */

#اگر_تعریف_نشده GL_EXT_occlusion_query_boolean
#تعریف_کن GL_EXT_occlusion_query_boolean 1
#تعریف_کن GL_ANY_SAMPLES_PASSED_EXT         0x8C2F
#تعریف_کن GL_ANY_SAMPLES_PASSED_CONSERVATIVE_EXT 0x8D6A
#پایان_اگر /* GL_EXT_occlusion_query_boolean */

#اگر_تعریف_نشده GL_EXT_polygon_جابه_جایی_clamp
#تعریف_کن GL_EXT_polygon_جابه_جایی_clamp 1
#تعریف_کن GL_POLYGON_جابه_جایی_CLAMP_EXT       0x8E1B
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOLYGONOFFSETCLAMPEXTPROC) (GLfloat ضریب, GLfloat units, GLfloat clamp);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Polygon_جابه_جایی_Clamp_EXT (GLfloat ضریب, GLfloat units, GLfloat clamp);
#پایان_اگر
#پایان_اگر /* GL_EXT_polygon_offset_clamp */

#اگر_تعریف_نشده GL_EXT_post_عمق_coverage
#تعریف_کن GL_EXT_post_عمق_coverage 1
#پایان_اگر /* GL_EXT_post_depth_coverage */

#اگر_تعریف_نشده GL_EXT_primitive_bounding_box
#تعریف_کن GL_EXT_primitive_bounding_box 1
#تعریف_کن GL_PRIMITIVE_BOUNDING_BOX_EXT     0x92BE
تعريفنوع فراغ (GL_APIENTRYP PFNGLPRIMITIVEBOUNDINGBOXEXTPROC) (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glPrimitiveBoundingBoxEXT (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
#پایان_اگر
#پایان_اگر /* GL_EXT_primitive_bounding_box */

#اگر_تعریف_نشده GL_EXT_protected_textures
#تعریف_کن GL_EXT_protected_textures 1
#تعریف_کن GL_CONTEXT_FLAG_PROTECTED_CONTENT_بیت_EXT 0x00000010
#تعریف_کن GL_TEXTURE_PROTECTED_EXT          0x8BFA
#پایان_اگر /* GL_EXT_protected_textures */

#اگر_تعریف_نشده GL_EXT_pvrtc_sRGB
#تعریف_کن GL_EXT_pvrtc_sRGB 1
#تعریف_کن GL_COMPRESSED_SRGB_PVRTC_2BPPV1_EXT 0x8A54
#تعریف_کن GL_COMPRESSED_SRGB_PVRTC_4BPPV1_EXT 0x8A55
#تعریف_کن GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV1_EXT 0x8A56
#تعریف_کن GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV1_EXT 0x8A57
#تعریف_کن GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV2_IMG 0x93F0
#تعریف_کن GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV2_IMG 0x93F1
#پایان_اگر /* GL_EXT_pvrtc_sRGB */

#اگر_تعریف_نشده GL_EXT_raster_multisample
#تعریف_کن GL_EXT_raster_multisample 1
#تعریف_کن GL_RASTER_MULTISAMPLE_EXT         0x9327
#تعریف_کن GL_RASTER_SAMPLES_EXT             0x9328
#تعریف_کن GL_MAX_RASTER_SAMPLES_EXT         0x9329
#تعریف_کن GL_RASTER_FIXED_SAMPLE_LOCATIONS_EXT 0x932A
#تعریف_کن GL_MULTISAMPLE_RASTERIZATION_ALLOWED_EXT 0x932B
#تعریف_کن GL_EFFECTIVE_RASTER_SAMPLES_EXT   0x932C
تعريفنوع فراغ (GL_APIENTRYP PFNGLRASTERSAMPLESEXTPROC) (GLuint samples, GLboolean fixedsamplelocations);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glRasterSamplesEXT (GLuint samples, GLboolean fixedsamplelocations);
#پایان_اگر
#پایان_اگر /* GL_EXT_raster_multisample */

#اگر_تعریف_نشده GL_EXT_read_format_bgra
#تعریف_کن GL_EXT_read_format_bgra 1
#تعریف_کن GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT 0x8365
#تعریف_کن GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT 0x8366
#پایان_اگر /* GL_EXT_read_format_bgra */

#اگر_تعریف_نشده GL_EXT_render_snorm
#تعریف_کن GL_EXT_render_snorm 1
#تعریف_کن GL_R8_SNORM                       0x8F94
#تعریف_کن GL_RG8_SNORM                      0x8F95
#تعریف_کن GL_RGBA8_SNORM                    0x8F97
#تعریف_کن GL_R16_SNORM_EXT                  0x8F98
#تعریف_کن GL_RG16_SNORM_EXT                 0x8F99
#تعریف_کن GL_RGBA16_SNORM_EXT               0x8F9B
#پایان_اگر /* GL_EXT_render_snorm */

#اگر_تعریف_نشده GL_EXT_robustness
#تعریف_کن GL_EXT_robustness 1
#تعریف_کن GL_GUILTY_CONTEXT_RESET_EXT       0x8253
#تعریف_کن GL_INNOCENT_CONTEXT_RESET_EXT     0x8254
#تعریف_کن GL_UNKNOWN_CONTEXT_RESET_EXT      0x8255
#تعریف_کن GL_CONTEXT_ROBUST_ACCESS_EXT      0x90F3
#تعریف_کن GL_RESET_NOTIFICATION_STRATEGY_EXT 0x8256
#تعریف_کن GL_LOSE_CONTEXT_ON_RESET_EXT      0x8252
#تعریف_کن GL_NO_RESET_NOTIFICATION_EXT      0x8261
تعريفنوع GLenum (GL_APIENTRYP PFNGLGETGRAPHICSRESETSTATUSEXTPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLREADNPIXELSEXTPROC) (GLint x, GLint y, GLsizei عرض, GLsizei ارتفاع, GLenum format, GLenum type, GLsizei buf_اندازه, فراغ *داده);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNUNIFORMFVEXTPROC) (GLuint برنامه, GLint location, GLsizei buf_اندازه, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNUNIFORMIVEXTPROC) (GLuint برنامه, GLint location, GLsizei buf_اندازه, GLint *params);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL GLenum GL_APIENTRY gl_Get_Graphics_Reset_وضعیت_EXT (فراغ);
GL_APICALL فراغ GL_APIENTRY glReadnPixelsEXT (GLint x, GLint y, GLsizei عرض, GLsizei ارتفاع, GLenum format, GLenum type, GLsizei buf_اندازه, فراغ *داده);
GL_APICALL فراغ GL_APIENTRY glGetnUniformfvEXT (GLuint برنامه, GLint location, GLsizei buf_اندازه, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY glGetnUniformivEXT (GLuint برنامه, GLint location, GLsizei buf_اندازه, GLint *params);
#پایان_اگر
#پایان_اگر /* GL_EXT_robustness */

#اگر_تعریف_نشده GL_EXT_sRGB
#تعریف_کن GL_EXT_sRGB 1
#تعریف_کن GL_SRGB_EXT                       0x8C40
#تعریف_کن GL_SRGB_ALPHA_EXT                 0x8C42
#تعریف_کن GL_SRGB8_ALPHA8_EXT               0x8C43
#تعریف_کن GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING_EXT 0x8210
#پایان_اگر /* GL_EXT_sRGB */

#اگر_تعریف_نشده GL_EXT_sRGB_write_control
#تعریف_کن GL_EXT_sRGB_write_control 1
#تعریف_کن GL_FRAMEBUFFER_SRGB_EXT           0x8DB9
#پایان_اگر /* GL_EXT_sRGB_write_control */

#اگر_تعریف_نشده GL_EXT_semaphore
#تعریف_کن GL_EXT_semaphore 1
#تعریف_کن GL_LAYOUT_GENERAL_EXT             0x958D
#تعریف_کن GL_LAYOUT_COLOR_ATTACHMENT_EXT    0x958E
#تعریف_کن GL_LAYOUT_عمق_STENCIL_ATTACHMENT_EXT 0x958F
#تعریف_کن GL_LAYOUT_عمق_STENCIL_READ_ONLY_EXT 0x9590
#تعریف_کن GL_LAYOUT_SHADER_READ_ONLY_EXT    0x9591
#تعریف_کن GL_LAYOUT_TRANSFER_SRC_EXT        0x9592
#تعریف_کن GL_LAYOUT_TRANSFER_DST_EXT        0x9593
#تعریف_کن GL_LAYOUT_عمق_READ_ONLY_STENCIL_ATTACHMENT_EXT 0x9530
#تعریف_کن GL_LAYOUT_عمق_ATTACHMENT_STENCIL_READ_ONLY_EXT 0x9531
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENSEMAPHORESEXTPROC) (GLsizei n, GLuint *semaphores);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETESEMAPHORESEXTPROC) (GLsizei n, ثابت GLuint *semaphores);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISSEMAPHOREEXTPROC) (GLuint semaphore);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSEMAPHOREPARAMETERUI64VEXTPROC) (GLuint semaphore, GLenum pname, ثابت GLuint64 *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSEMAPHOREPARAMETERUI64VEXTPROC) (GLuint semaphore, GLenum pname, GLuint64 *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLWAITSEMAPHOREEXTPROC) (GLuint semaphore, GLuint رقم_میانگیر_Barriers, ثابت GLuint *buffers, GLuint رقم_Texture_Barriers, ثابت GLuint *textures, ثابت GLenum *srcLayouts);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSIGNALSEMAPHOREEXTPROC) (GLuint semaphore, GLuint رقم_میانگیر_Barriers, ثابت GLuint *buffers, GLuint رقم_Texture_Barriers, ثابت GLuint *textures, ثابت GLenum *dstLayouts);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glGenSemaphoresEXT (GLsizei n, GLuint *semaphores);
GL_APICALL فراغ GL_APIENTRY glDeleteSemaphoresEXT (GLsizei n, ثابت GLuint *semaphores);
GL_APICALL GLboolean GL_APIENTRY glIsSemaphoreEXT (GLuint semaphore);
GL_APICALL فراغ GL_APIENTRY glSemaphoreParameterui64vEXT (GLuint semaphore, GLenum pname, ثابت GLuint64 *params);
GL_APICALL فراغ GL_APIENTRY glGetSemaphoreParameterui64vEXT (GLuint semaphore, GLenum pname, GLuint64 *params);
GL_APICALL فراغ GL_APIENTRY glWaitSemaphoreEXT (GLuint semaphore, GLuint رقم_میانگیر_Barriers, ثابت GLuint *buffers, GLuint رقم_Texture_Barriers, ثابت GLuint *textures, ثابت GLenum *srcLayouts);
GL_APICALL فراغ GL_APIENTRY glSignalSemaphoreEXT (GLuint semaphore, GLuint رقم_میانگیر_Barriers, ثابت GLuint *buffers, GLuint رقم_Texture_Barriers, ثابت GLuint *textures, ثابت GLenum *dstLayouts);
#پایان_اگر
#پایان_اگر /* GL_EXT_semaphore */

#اگر_تعریف_نشده GL_EXT_semaphore_fd
#تعریف_کن GL_EXT_semaphore_fd 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLIMPORTSEMAPHOREFDEXTPROC) (GLuint semaphore, GLenum handleType, GLint fd);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glImportSemaphoreFdEXT (GLuint semaphore, GLenum handleType, GLint fd);
#پایان_اگر
#پایان_اگر /* GL_EXT_semaphore_fd */

#اگر_تعریف_نشده GL_EXT_semaphore_win32
#تعریف_کن GL_EXT_semaphore_win32 1
#تعریف_کن GL_HANDLE_TYPE_D3D12_FENCE_EXT    0x9594
#تعریف_کن GL_D3_D12_FENCE_مقدار_EXT          0x9595
تعريفنوع فراغ (GL_APIENTRYP PFNGLIMPORTSEMAPHOREWIN32HANDLEEXTPROC) (GLuint semaphore, GLenum handleType, فراغ *handle);
تعريفنوع فراغ (GL_APIENTRYP PFNGLIMPORTSEMAPHOREWIN32NAMEEXTPROC) (GLuint semaphore, GLenum handleType, ثابت فراغ *name);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glImportSemaphoreWin32HandleEXT (GLuint semaphore, GLenum handleType, فراغ *handle);
GL_APICALL فراغ GL_APIENTRY glImportSemaphoreWin32NameEXT (GLuint semaphore, GLenum handleType, ثابت فراغ *name);
#پایان_اگر
#پایان_اگر /* GL_EXT_semaphore_win32 */

#اگر_تعریف_نشده GL_EXT_separate_عمق_stencil
#تعریف_کن GL_EXT_separate_عمق_stencil 1
#پایان_اگر /* GL_EXT_separate_depth_stencil */

#اگر_تعریف_نشده GL_EXT_separate_shader_objects
#تعریف_کن GL_EXT_separate_shader_objects 1
#تعریف_کن GL_فعال_برنامه_EXT             0x8259
#تعریف_کن GL_رأس_SHADER_بیت_EXT          0x00000001
#تعریف_کن GL_FRAGMENT_SHADER_بیت_EXT        0x00000002
#تعریف_کن GL_ALL_SHADER_بیتها_EXT            0xFFFFFFFF
#تعریف_کن GL_برنامه_SEPARABLE_EXT          0x8258
#تعریف_کن GL_برنامه_PIPELINE_BINDING_EXT   0x825A
تعريفنوع فراغ (GL_APIENTRYP PFNGLACTIVESHADERPROGRAMEXTPROC) (GLuint pipeline, GLuint برنامه);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDPROGRAMPIPELINEEXTPROC) (GLuint pipeline);
تعريفنوع GLuint (GL_APIENTRYP PFNGLCREATESHADERPROGRAMVEXTPROC) (GLenum type, GLsizei شمار, ثابت GLchar *ثابت*رشتهها);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEPROGRAMPIPELINESEXTPROC) (GLsizei n, ثابت GLuint *pipelines);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENPROGRAMPIPELINESEXTPROC) (GLsizei n, GLuint *pipelines);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMPIPELINEINFOLOGEXTPROC) (GLuint pipeline, GLsizei buf_اندازه, GLsizei *درازی, GLchar *infoLog);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMPIPELINEIVEXTPROC) (GLuint pipeline, GLenum pname, GLint *params);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISPROGRAMPIPELINEEXTPROC) (GLuint pipeline);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMPARAMETERIEXTPROC) (GLuint برنامه, GLenum pname, GLint مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1FEXTPROC) (GLuint برنامه, GLint location, GLfloat v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1FVEXTPROC) (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1IEXTPROC) (GLuint برنامه, GLint location, GLint v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1IVEXTPROC) (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLint *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2FEXTPROC) (GLuint برنامه, GLint location, GLfloat v0, GLfloat v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2FVEXTPROC) (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2IEXTPROC) (GLuint برنامه, GLint location, GLint v0, GLint v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2IVEXTPROC) (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLint *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3FEXTPROC) (GLuint برنامه, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3FVEXTPROC) (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3IEXTPROC) (GLuint برنامه, GLint location, GLint v0, GLint v1, GLint v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3IVEXTPROC) (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLint *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4FEXTPROC) (GLuint برنامه, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4FVEXTPROC) (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4IEXTPROC) (GLuint برنامه, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4IVEXTPROC) (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLint *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC) (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC) (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC) (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUSEPROGRAMSTAGESEXTPROC) (GLuint pipeline, GLbitfield stages, GLuint برنامه);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVALIDATEPROGRAMPIPELINEEXTPROC) (GLuint pipeline);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UIEXTPROC) (GLuint برنامه, GLint location, GLuint v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UIEXTPROC) (GLuint برنامه, GLint location, GLuint v0, GLuint v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UIEXTPROC) (GLuint برنامه, GLint location, GLuint v0, GLuint v1, GLuint v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UIEXTPROC) (GLuint برنامه, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UIVEXTPROC) (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLuint *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UIVEXTPROC) (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLuint *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UIVEXTPROC) (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLuint *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UIVEXTPROC) (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLuint *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC) (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC) (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC) (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC) (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC) (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC) (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_فعال_Shader_برنامه_EXT (GLuint pipeline, GLuint برنامه);
GL_APICALL فراغ GL_APIENTRY gl_Bind_برنامه_Pipeline_EXT (GLuint pipeline);
GL_APICALL GLuint GL_APIENTRY glCreateShaderProgramvEXT (GLenum type, GLsizei شمار, ثابت GLchar *ثابت*رشتهها);
GL_APICALL فراغ GL_APIENTRY gl_Delete_برنامه_Pipelines_EXT (GLsizei n, ثابت GLuint *pipelines);
GL_APICALL فراغ GL_APIENTRY gl_Gen_برنامه_Pipelines_EXT (GLsizei n, GLuint *pipelines);
GL_APICALL فراغ GL_APIENTRY gl_Get_برنامه_Pipeline_Info_Log_EXT (GLuint pipeline, GLsizei buf_اندازه, GLsizei *درازی, GLchar *infoLog);
GL_APICALL فراغ GL_APIENTRY gl_Get_برنامه_Pipelineiv_EXT (GLuint pipeline, GLenum pname, GLint *params);
GL_APICALL GLboolean GL_APIENTRY gl_Is_برنامه_Pipeline_EXT (GLuint pipeline);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Parameteri_EXT (GLuint برنامه, GLenum pname, GLint مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform1f_EXT (GLuint برنامه, GLint location, GLfloat v0);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform1fv_EXT (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform1i_EXT (GLuint برنامه, GLint location, GLint v0);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform1iv_EXT (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLint *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform2f_EXT (GLuint برنامه, GLint location, GLfloat v0, GLfloat v1);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform2fv_EXT (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform2i_EXT (GLuint برنامه, GLint location, GLint v0, GLint v1);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform2iv_EXT (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLint *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform3f_EXT (GLuint برنامه, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform3fv_EXT (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform3i_EXT (GLuint برنامه, GLint location, GLint v0, GLint v1, GLint v2);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform3iv_EXT (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLint *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform4f_EXT (GLuint برنامه, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform4fv_EXT (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform4i_EXT (GLuint برنامه, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform4iv_EXT (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLint *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_یکنواخت_Matrix2fv_EXT (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_یکنواخت_Matrix3fv_EXT (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_یکنواخت_Matrix4fv_EXT (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_Use_برنامه_Stages_EXT (GLuint pipeline, GLbitfield stages, GLuint برنامه);
GL_APICALL فراغ GL_APIENTRY gl_Validate_برنامه_Pipeline_EXT (GLuint pipeline);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform1ui_EXT (GLuint برنامه, GLint location, GLuint v0);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform2ui_EXT (GLuint برنامه, GLint location, GLuint v0, GLuint v1);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform3ui_EXT (GLuint برنامه, GLint location, GLuint v0, GLuint v1, GLuint v2);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform4ui_EXT (GLuint برنامه, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform1uiv_EXT (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLuint *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform2uiv_EXT (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLuint *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform3uiv_EXT (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLuint *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform4uiv_EXT (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLuint *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_یکنواخت_Matrix2x3fv_EXT (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_یکنواخت_Matrix3x2fv_EXT (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_یکنواخت_Matrix2x4fv_EXT (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_یکنواخت_Matrix4x2fv_EXT (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_یکنواخت_Matrix3x4fv_EXT (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_یکنواخت_Matrix4x3fv_EXT (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
#پایان_اگر
#پایان_اگر /* GL_EXT_separate_shader_objects */

#اگر_تعریف_نشده GL_EXT_shader_framebuffer_fetch
#تعریف_کن GL_EXT_shader_framebuffer_fetch 1
#تعریف_کن GL_FRAGMENT_SHADER_DISCARDS_SAMPLES_EXT 0x8A52
#پایان_اگر /* GL_EXT_shader_framebuffer_fetch */

#اگر_تعریف_نشده GL_EXT_shader_framebuffer_fetch_non_coherent
#تعریف_کن GL_EXT_shader_framebuffer_fetch_non_coherent 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERFETCHBARRIEREXTPROC) (فراغ);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferFetchBarrierEXT (فراغ);
#پایان_اگر
#پایان_اگر /* GL_EXT_shader_framebuffer_fetch_non_coherent */

#اگر_تعریف_نشده GL_EXT_shader_گروه_vote
#تعریف_کن GL_EXT_shader_گروه_vote 1
#پایان_اگر /* GL_EXT_shader_group_vote */

#اگر_تعریف_نشده GL_EXT_shader_implicit_conversions
#تعریف_کن GL_EXT_shader_implicit_conversions 1
#پایان_اگر /* GL_EXT_shader_implicit_conversions */

#اگر_تعریف_نشده GL_EXT_shader_integer_mix
#تعریف_کن GL_EXT_shader_integer_mix 1
#پایان_اگر /* GL_EXT_shader_integer_mix */

#اگر_تعریف_نشده GL_EXT_shader_io_بلوکها
#تعریف_کن GL_EXT_shader_io_بلوکها 1
#پایان_اگر /* GL_EXT_shader_io_blocks */

#اگر_تعریف_نشده GL_EXT_shader_non_constant_global_initializers
#تعریف_کن GL_EXT_shader_non_constant_global_initializers 1
#پایان_اگر /* GL_EXT_shader_non_constant_global_initializers */

#اگر_تعریف_نشده GL_EXT_shader_pixel_local_storage
#تعریف_کن GL_EXT_shader_pixel_local_storage 1
#تعریف_کن GL_MAX_SHADER_PIXEL_LOCAL_STORAGE_FAST_اندازه_EXT 0x8F63
#تعریف_کن GL_MAX_SHADER_PIXEL_LOCAL_STORAGE_اندازه_EXT 0x8F67
#تعریف_کن GL_SHADER_PIXEL_LOCAL_STORAGE_EXT 0x8F64
#پایان_اگر /* GL_EXT_shader_pixel_local_storage */

#اگر_تعریف_نشده GL_EXT_shader_pixel_local_storage2
#تعریف_کن GL_EXT_shader_pixel_local_storage2 1
#تعریف_کن GL_MAX_SHADER_COMBINED_LOCAL_STORAGE_FAST_اندازه_EXT 0x9650
#تعریف_کن GL_MAX_SHADER_COMBINED_LOCAL_STORAGE_اندازه_EXT 0x9651
#تعریف_کن GL_FRAMEBUFFER_INCOMPLETE_INSUFFICIENT_SHADER_COMBINED_LOCAL_STORAGE_EXT 0x9652
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERPIXELLOCALSTORAGESIZEEXTPROC) (GLuint هدف, GLsizei اندازه);
تعريفنوع GLsizei (GL_APIENTRYP PFNGLGETFRAMEBUFFERPIXELLOCALSTORAGESIZEEXTPROC) (GLuint هدف);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARPIXELLOCALSTORAGEUIEXTPROC) (GLsizei جابه_جایی_2, GLsizei n, ثابت GLuint *مقادیر);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Framebuffer_Pixel_Local_Storage_اندازه_EXT (GLuint هدف, GLsizei اندازه);
GL_APICALL GLsizei GL_APIENTRY gl_Get_Framebuffer_Pixel_Local_Storage_اندازه_EXT (GLuint هدف);
GL_APICALL فراغ GL_APIENTRY glClearPixelLocalStorageuiEXT (GLsizei جابه_جایی_2, GLsizei n, ثابت GLuint *مقادیر);
#پایان_اگر
#پایان_اگر /* GL_EXT_shader_pixel_local_storage2 */

#اگر_تعریف_نشده GL_EXT_shader_samples_identical
#تعریف_کن GL_EXT_shader_samples_identical 1
#پایان_اگر /* GL_EXT_shader_samples_identical */

#اگر_تعریف_نشده GL_EXT_shader_texture_lod
#تعریف_کن GL_EXT_shader_texture_lod 1
#پایان_اگر /* GL_EXT_shader_texture_lod */

#اگر_تعریف_نشده GL_EXT_shader_texture_samples
#تعریف_کن GL_EXT_shader_texture_samples 1
#پایان_اگر /* GL_EXT_shader_texture_samples */

#اگر_تعریف_نشده GL_EXT_shadow_samplers
#تعریف_کن GL_EXT_shadow_samplers 1
#تعریف_کن GL_TEXTURE_COMPARE_نما_EXT       0x884C
#تعریف_کن GL_TEXTURE_COMPARE_FUNC_EXT       0x884D
#تعریف_کن GL_COMPARE_REF_مقصد_TEXTURE_EXT     0x884E
#تعریف_کن GL_SAMPLER_2D_SHADOW_EXT          0x8B62
#پایان_اگر /* GL_EXT_shadow_samplers */

#اگر_تعریف_نشده GL_EXT_sparse_texture
#تعریف_کن GL_EXT_sparse_texture 1
#تعریف_کن GL_TEXTURE_SPARSE_EXT             0x91A6
#تعریف_کن GL_VIRTUAL_صفحه_اندازه_شاخص_EXT    0x91A7
#تعریف_کن GL_رقم_SPARSE_سطوح_EXT          0x91AA
#تعریف_کن GL_رقم_VIRTUAL_صفحه_SIZES_EXT     0x91A8
#تعریف_کن GL_VIRTUAL_صفحه_اندازه_X_EXT        0x9195
#تعریف_کن GL_VIRTUAL_صفحه_اندازه_Y_EXT        0x9196
#تعریف_کن GL_VIRTUAL_صفحه_اندازه_Z_EXT        0x9197
#تعریف_کن GL_TEXTURE_2D_ARRAY               0x8C1A
#تعریف_کن GL_TEXTURE_3D                     0x806F
#تعریف_کن GL_MAX_SPARSE_TEXTURE_اندازه_EXT    0x9198
#تعریف_کن GL_MAX_SPARSE_3_D_TEXTURE_اندازه_EXT 0x9199
#تعریف_کن GL_MAX_SPARSE_ARRAY_TEXTURE_LAYERS_EXT 0x919A
#تعریف_کن GL_SPARSE_TEXTURE_پر_ARRAY_CUBE_MIPMAPS_EXT 0x91A9
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPAGECOMMITMENTEXTPROC) (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLboolean commit);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Tex_صفحه_Commitment_EXT (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLboolean commit);
#پایان_اگر
#پایان_اگر /* GL_EXT_sparse_texture */

#اگر_تعریف_نشده GL_EXT_sparse_texture2
#تعریف_کن GL_EXT_sparse_texture2 1
#پایان_اگر /* GL_EXT_sparse_texture2 */

#اگر_تعریف_نشده GL_EXT_tessellation_نقطه_اندازه
#تعریف_کن GL_EXT_tessellation_نقطه_اندازه 1
#پایان_اگر /* GL_EXT_tessellation_point_size */

#اگر_تعریف_نشده GL_EXT_tessellation_shader
#تعریف_کن GL_EXT_tessellation_shader 1
#تعریف_کن GL_PATCHES_EXT                    0x000E
#تعریف_کن GL_PATCH_VERTICES_EXT             0x8E72
#تعریف_کن GL_TESS_CONTROL_OUTPUT_VERTICES_EXT 0x8E75
#تعریف_کن GL_TESS_GEN_نما_EXT              0x8E76
#تعریف_کن GL_TESS_GEN_SPACING_EXT           0x8E77
#تعریف_کن GL_TESS_GEN_رأس_ترتیب_EXT      0x8E78
#تعریف_کن GL_TESS_GEN_نقطه_نما_EXT        0x8E79
#تعریف_کن GL_ISOLINES_EXT                   0x8E7A
#تعریف_کن GL_QUADS_EXT                      0x0007
#تعریف_کن GL_FRACTIONAL_ODD_EXT             0x8E7B
#تعریف_کن GL_FRACTIONAL_EVEN_EXT            0x8E7C
#تعریف_کن GL_MAX_PATCH_VERTICES_EXT         0x8E7D
#تعریف_کن GL_MAX_TESS_GEN_LEVEL_EXT         0x8E7E
#تعریف_کن GL_MAX_TESS_CONTROL_یکنواخت_COMPONENTS_EXT 0x8E7F
#تعریف_کن GL_MAX_TESS_EVALUATION_یکنواخت_COMPONENTS_EXT 0x8E80
#تعریف_کن GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS_EXT 0x8E81
#تعریف_کن GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS_EXT 0x8E82
#تعریف_کن GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS_EXT 0x8E83
#تعریف_کن GL_MAX_TESS_PATCH_COMPONENTS_EXT  0x8E84
#تعریف_کن GL_MAX_TESS_CONTROL_مجموع_OUTPUT_COMPONENTS_EXT 0x8E85
#تعریف_کن GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS_EXT 0x8E86
#تعریف_کن GL_MAX_TESS_CONTROL_یکنواخت_بلوکها_EXT 0x8E89
#تعریف_کن GL_MAX_TESS_EVALUATION_یکنواخت_بلوکها_EXT 0x8E8A
#تعریف_کن GL_MAX_TESS_CONTROL_درون_داد_COMPONENTS_EXT 0x886C
#تعریف_کن GL_MAX_TESS_EVALUATION_درون_داد_COMPONENTS_EXT 0x886D
#تعریف_کن GL_MAX_COMBINED_TESS_CONTROL_یکنواخت_COMPONENTS_EXT 0x8E1E
#تعریف_کن GL_MAX_COMBINED_TESS_EVALUATION_یکنواخت_COMPONENTS_EXT 0x8E1F
#تعریف_کن GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS_EXT 0x92CD
#تعریف_کن GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS_EXT 0x92CE
#تعریف_کن GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS_EXT 0x92D3
#تعریف_کن GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS_EXT 0x92D4
#تعریف_کن GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS_EXT 0x90CB
#تعریف_کن GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS_EXT 0x90CC
#تعریف_کن GL_MAX_TESS_CONTROL_SHADER_STORAGE_بلوکها_EXT 0x90D8
#تعریف_کن GL_MAX_TESS_EVALUATION_SHADER_STORAGE_بلوکها_EXT 0x90D9
#تعریف_کن GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED 0x8221
#تعریف_کن GL_IS_در_هر_PATCH_EXT               0x92E7
#تعریف_کن GL_REFERENCED_BY_TESS_CONTROL_SHADER_EXT 0x9307
#تعریف_کن GL_REFERENCED_BY_TESS_EVALUATION_SHADER_EXT 0x9308
#تعریف_کن GL_TESS_CONTROL_SHADER_EXT        0x8E88
#تعریف_کن GL_TESS_EVALUATION_SHADER_EXT     0x8E87
#تعریف_کن GL_TESS_CONTROL_SHADER_بیت_EXT    0x00000008
#تعریف_کن GL_TESS_EVALUATION_SHADER_بیت_EXT 0x00000010
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATCHPARAMETERIEXTPROC) (GLenum pname, GLint مقدار);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glPatchParameteriEXT (GLenum pname, GLint مقدار);
#پایان_اگر
#پایان_اگر /* GL_EXT_tessellation_shader */

#اگر_تعریف_نشده GL_EXT_texture_border_clamp
#تعریف_کن GL_EXT_texture_border_clamp 1
#تعریف_کن GL_TEXTURE_BORDER_COLOR_EXT       0x1004
#تعریف_کن GL_CLAMP_مقصد_BORDER_EXT            0x812D
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERIIVEXTPROC) (GLenum هدف, GLenum pname, ثابت GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERIUIVEXTPROC) (GLenum هدف, GLenum pname, ثابت GLuint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXPARAMETERIIVEXTPROC) (GLenum هدف, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXPARAMETERIUIVEXTPROC) (GLenum هدف, GLenum pname, GLuint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIIVEXTPROC) (GLuint sampler, GLenum pname, ثابت GLint *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIUIVEXTPROC) (GLuint sampler, GLenum pname, ثابت GLuint *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIIVEXTPROC) (GLuint sampler, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIUIVEXTPROC) (GLuint sampler, GLenum pname, GLuint *params);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTexParameterIivEXT (GLenum هدف, GLenum pname, ثابت GLint *params);
GL_APICALL فراغ GL_APIENTRY glTexParameterIuivEXT (GLenum هدف, GLenum pname, ثابت GLuint *params);
GL_APICALL فراغ GL_APIENTRY glGetTexParameterIivEXT (GLenum هدف, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetTexParameterIuivEXT (GLenum هدف, GLenum pname, GLuint *params);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterIivEXT (GLuint sampler, GLenum pname, ثابت GLint *param);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterIuivEXT (GLuint sampler, GLenum pname, ثابت GLuint *param);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameterIivEXT (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameterIuivEXT (GLuint sampler, GLenum pname, GLuint *params);
#پایان_اگر
#پایان_اگر /* GL_EXT_texture_border_clamp */

#اگر_تعریف_نشده GL_EXT_texture_میانگیر
#تعریف_کن GL_EXT_texture_میانگیر 1
#تعریف_کن GL_TEXTURE_میانگیر_EXT             0x8C2A
#تعریف_کن GL_TEXTURE_میانگیر_BINDING_EXT     0x8C2A
#تعریف_کن GL_MAX_TEXTURE_میانگیر_اندازه_EXT    0x8C2B
#تعریف_کن GL_TEXTURE_BINDING_میانگیر_EXT     0x8C2C
#تعریف_کن GL_TEXTURE_میانگیر_داده_STORE_BINDING_EXT 0x8C2D
#تعریف_کن GL_TEXTURE_میانگیر_جابه_جایی_ALIGNMENT_EXT 0x919F
#تعریف_کن GL_SAMPLER_میانگیر_EXT             0x8DC2
#تعریف_کن GL_INT_SAMPLER_میانگیر_EXT         0x8DD0
#تعریف_کن GL_UNSIGNED_INT_SAMPLER_میانگیر_EXT 0x8DD8
#تعریف_کن GL_IMAGE_میانگیر_EXT               0x9051
#تعریف_کن GL_INT_IMAGE_میانگیر_EXT           0x905C
#تعریف_کن GL_UNSIGNED_INT_IMAGE_میانگیر_EXT  0x9067
#تعریف_کن GL_TEXTURE_میانگیر_جابه_جایی_EXT      0x919D
#تعریف_کن GL_TEXTURE_میانگیر_اندازه_EXT        0x919E
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXBUFFEREXTPROC) (GLenum هدف, GLenum internalformat, GLuint میانگیر_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXBUFFERRANGEEXTPROC) (GLenum هدف, GLenum internalformat, GLuint میانگیر_2, GLintptr جابه_جایی_2, GLsizeiptr اندازه);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Tex_میانگیر_EXT (GLenum هدف, GLenum internalformat, GLuint میانگیر_2);
GL_APICALL فراغ GL_APIENTRY gl_Tex_میانگیر_Range_EXT (GLenum هدف, GLenum internalformat, GLuint میانگیر_2, GLintptr جابه_جایی_2, GLsizeiptr اندازه);
#پایان_اگر
#پایان_اگر /* GL_EXT_texture_buffer */

#اگر_تعریف_نشده GL_EXT_texture_compression_astc_decode_نما
#تعریف_کن GL_EXT_texture_compression_astc_decode_نما 1
#تعریف_کن GL_TEXTURE_ASTC_DECODE_PRECISION_EXT 0x8F69
#پایان_اگر /* GL_EXT_texture_compression_astc_decode_mode */

#اگر_تعریف_نشده GL_EXT_texture_compression_bptc
#تعریف_کن GL_EXT_texture_compression_bptc 1
#تعریف_کن GL_COMPRESSED_RGBA_BPTC_UNORM_EXT 0x8E8C
#تعریف_کن GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_EXT 0x8E8D
#تعریف_کن GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_EXT 0x8E8E
#تعریف_کن GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_EXT 0x8E8F
#پایان_اگر /* GL_EXT_texture_compression_bptc */

#اگر_تعریف_نشده GL_EXT_texture_compression_dxt1
#تعریف_کن GL_EXT_texture_compression_dxt1 1
#تعریف_کن GL_COMPRESSED_RGB_S3TC_DXT1_EXT   0x83F0
#تعریف_کن GL_COMPRESSED_RGBA_S3TC_DXT1_EXT  0x83F1
#پایان_اگر /* GL_EXT_texture_compression_dxt1 */

#اگر_تعریف_نشده GL_EXT_texture_compression_rgtc
#تعریف_کن GL_EXT_texture_compression_rgtc 1
#تعریف_کن GL_COMPRESSED_RED_RGTC1_EXT       0x8DBB
#تعریف_کن GL_COMPRESSED_SIGNED_RED_RGTC1_EXT 0x8DBC
#تعریف_کن GL_COMPRESSED_RED_GREEN_RGTC2_EXT 0x8DBD
#تعریف_کن GL_COMPRESSED_SIGNED_RED_GREEN_RGTC2_EXT 0x8DBE
#پایان_اگر /* GL_EXT_texture_compression_rgtc */

#اگر_تعریف_نشده GL_EXT_texture_compression_s3tc
#تعریف_کن GL_EXT_texture_compression_s3tc 1
#تعریف_کن GL_COMPRESSED_RGBA_S3TC_DXT3_EXT  0x83F2
#تعریف_کن GL_COMPRESSED_RGBA_S3TC_DXT5_EXT  0x83F3
#پایان_اگر /* GL_EXT_texture_compression_s3tc */

#اگر_تعریف_نشده GL_EXT_texture_compression_s3tc_srgb
#تعریف_کن GL_EXT_texture_compression_s3tc_srgb 1
#تعریف_کن GL_COMPRESSED_SRGB_S3TC_DXT1_EXT  0x8C4C
#تعریف_کن GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT 0x8C4D
#تعریف_کن GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT 0x8C4E
#تعریف_کن GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT 0x8C4F
#پایان_اگر /* GL_EXT_texture_compression_s3tc_srgb */

#اگر_تعریف_نشده GL_EXT_texture_cube_map_array
#تعریف_کن GL_EXT_texture_cube_map_array 1
#تعریف_کن GL_TEXTURE_CUBE_MAP_ARRAY_EXT     0x9009
#تعریف_کن GL_TEXTURE_BINDING_CUBE_MAP_ARRAY_EXT 0x900A
#تعریف_کن GL_SAMPLER_CUBE_MAP_ARRAY_EXT     0x900C
#تعریف_کن GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW_EXT 0x900D
#تعریف_کن GL_INT_SAMPLER_CUBE_MAP_ARRAY_EXT 0x900E
#تعریف_کن GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY_EXT 0x900F
#تعریف_کن GL_IMAGE_CUBE_MAP_ARRAY_EXT       0x9054
#تعریف_کن GL_INT_IMAGE_CUBE_MAP_ARRAY_EXT   0x905F
#تعریف_کن GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY_EXT 0x906A
#پایان_اگر /* GL_EXT_texture_cube_map_array */

#اگر_تعریف_نشده GL_EXT_texture_filter_anisotropic
#تعریف_کن GL_EXT_texture_filter_anisotropic 1
#تعریف_کن GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#تعریف_کن GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#پایان_اگر /* GL_EXT_texture_filter_anisotropic */

#اگر_تعریف_نشده GL_EXT_texture_filter_minmax
#تعریف_کن GL_EXT_texture_filter_minmax 1
#تعریف_کن GL_TEXTURE_REDUCTION_نما_EXT     0x9366
#تعریف_کن GL_WEIGHTED_معدل_EXT           0x9367
#پایان_اگر /* GL_EXT_texture_filter_minmax */

#اگر_تعریف_نشده GL_EXT_texture_format_BGRA8888
#تعریف_کن GL_EXT_texture_format_BGRA8888 1
#پایان_اگر /* GL_EXT_texture_format_BGRA8888 */

#اگر_تعریف_نشده GL_EXT_texture_format_sRGB_override
#تعریف_کن GL_EXT_texture_format_sRGB_override 1
#تعریف_کن GL_TEXTURE_FORMAT_SRGB_OVERRIDE_EXT 0x8FBF
#پایان_اگر /* GL_EXT_texture_format_sRGB_override */

#اگر_تعریف_نشده GL_EXT_texture_mirror_clamp_مقصد_یال
#تعریف_کن GL_EXT_texture_mirror_clamp_مقصد_یال 1
#تعریف_کن GL_MIRROR_CLAMP_مقصد_یال_EXT       0x8743
#پایان_اگر /* GL_EXT_texture_mirror_clamp_to_edge */

#اگر_تعریف_نشده GL_EXT_texture_norm16
#تعریف_کن GL_EXT_texture_norm16 1
#تعریف_کن GL_R16_EXT                        0x822A
#تعریف_کن GL_RG16_EXT                       0x822C
#تعریف_کن GL_RGBA16_EXT                     0x805B
#تعریف_کن GL_RGB16_EXT                      0x8054
#تعریف_کن GL_RGB16_SNORM_EXT                0x8F9A
#پایان_اگر /* GL_EXT_texture_norm16 */

#اگر_تعریف_نشده GL_EXT_texture_query_lod
#تعریف_کن GL_EXT_texture_query_lod 1
#پایان_اگر /* GL_EXT_texture_query_lod */

#اگر_تعریف_نشده GL_EXT_texture_rg
#تعریف_کن GL_EXT_texture_rg 1
#تعریف_کن GL_RED_EXT                        0x1903
#تعریف_کن GL_RG_EXT                         0x8227
#تعریف_کن GL_R8_EXT                         0x8229
#تعریف_کن GL_RG8_EXT                        0x822B
#پایان_اگر /* GL_EXT_texture_rg */

#اگر_تعریف_نشده GL_EXT_texture_sRGB_R8
#تعریف_کن GL_EXT_texture_sRGB_R8 1
#تعریف_کن GL_SR8_EXT                        0x8FBD
#پایان_اگر /* GL_EXT_texture_sRGB_R8 */

#اگر_تعریف_نشده GL_EXT_texture_sRGB_RG8
#تعریف_کن GL_EXT_texture_sRGB_RG8 1
#تعریف_کن GL_SRG8_EXT                       0x8FBE
#پایان_اگر /* GL_EXT_texture_sRGB_RG8 */

#اگر_تعریف_نشده GL_EXT_texture_sRGB_decode
#تعریف_کن GL_EXT_texture_sRGB_decode 1
#تعریف_کن GL_TEXTURE_SRGB_DECODE_EXT        0x8A48
#تعریف_کن GL_DECODE_EXT                     0x8A49
#تعریف_کن GL_SKIP_DECODE_EXT                0x8A4A
#پایان_اگر /* GL_EXT_texture_sRGB_decode */

#اگر_تعریف_نشده GL_EXT_texture_shadow_lod
#تعریف_کن GL_EXT_texture_shadow_lod 1
#پایان_اگر /* GL_EXT_texture_shadow_lod */

#اگر_تعریف_نشده GL_EXT_texture_storage
#تعریف_کن GL_EXT_texture_storage 1
#تعریف_کن GL_TEXTURE_IMMUTABLE_FORMAT_EXT   0x912F
#تعریف_کن GL_ALPHA8_EXT                     0x803C
#تعریف_کن GL_LUMINANCE8_EXT                 0x8040
#تعریف_کن GL_LUMINANCE8_ALPHA8_EXT          0x8045
#تعریف_کن GL_RGBA32F_EXT                    0x8814
#تعریف_کن GL_RGB32F_EXT                     0x8815
#تعریف_کن GL_ALPHA32F_EXT                   0x8816
#تعریف_کن GL_LUMINANCE32F_EXT               0x8818
#تعریف_کن GL_LUMINANCE_ALPHA32F_EXT         0x8819
#تعریف_کن GL_ALPHA16F_EXT                   0x881C
#تعریف_کن GL_LUMINANCE16F_EXT               0x881E
#تعریف_کن GL_LUMINANCE_ALPHA16F_EXT         0x881F
#تعریف_کن GL_R32F_EXT                       0x822E
#تعریف_کن GL_RG32F_EXT                      0x8230
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE1DEXTPROC) (GLenum هدف, GLsizei سطوح, GLenum internalformat, GLsizei عرض);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE2DEXTPROC) (GLenum هدف, GLsizei سطوح, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE3DEXTPROC) (GLenum هدف, GLsizei سطوح, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGE1DEXTPROC) (GLuint texture, GLenum هدف, GLsizei سطوح, GLenum internalformat, GLsizei عرض);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGE2DEXTPROC) (GLuint texture, GLenum هدف, GLsizei سطوح, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGE3DEXTPROC) (GLuint texture, GLenum هدف, GLsizei سطوح, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTexStorage1DEXT (GLenum هدف, GLsizei سطوح, GLenum internalformat, GLsizei عرض);
GL_APICALL فراغ GL_APIENTRY glTexStorage2DEXT (GLenum هدف, GLsizei سطوح, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
GL_APICALL فراغ GL_APIENTRY glTexStorage3DEXT (GLenum هدف, GLsizei سطوح, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2);
GL_APICALL فراغ GL_APIENTRY glTextureStorage1DEXT (GLuint texture, GLenum هدف, GLsizei سطوح, GLenum internalformat, GLsizei عرض);
GL_APICALL فراغ GL_APIENTRY glTextureStorage2DEXT (GLuint texture, GLenum هدف, GLsizei سطوح, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
GL_APICALL فراغ GL_APIENTRY glTextureStorage3DEXT (GLuint texture, GLenum هدف, GLsizei سطوح, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2);
#پایان_اگر
#پایان_اگر /* GL_EXT_texture_storage */

#اگر_تعریف_نشده GL_EXT_texture_storage_compression
#تعریف_کن GL_EXT_texture_storage_compression 1
#تعریف_کن GL_رقم_SURFACE_COMPRESSION_FIXED_RATES_EXT 0x8F6E
#تعریف_کن GL_SURFACE_COMPRESSION_FIXED_نرخ_1_BPC_EXT 0x96C4
#تعریف_کن GL_SURFACE_COMPRESSION_FIXED_نرخ_2_BPC_EXT 0x96C5
#تعریف_کن GL_SURFACE_COMPRESSION_FIXED_نرخ_3_BPC_EXT 0x96C6
#تعریف_کن GL_SURFACE_COMPRESSION_FIXED_نرخ_4_BPC_EXT 0x96C7
#تعریف_کن GL_SURFACE_COMPRESSION_FIXED_نرخ_5_BPC_EXT 0x96C8
#تعریف_کن GL_SURFACE_COMPRESSION_FIXED_نرخ_6_BPC_EXT 0x96C9
#تعریف_کن GL_SURFACE_COMPRESSION_FIXED_نرخ_7_BPC_EXT 0x96CA
#تعریف_کن GL_SURFACE_COMPRESSION_FIXED_نرخ_8_BPC_EXT 0x96CB
#تعریف_کن GL_SURFACE_COMPRESSION_FIXED_نرخ_9_BPC_EXT 0x96CC
#تعریف_کن GL_SURFACE_COMPRESSION_FIXED_نرخ_10_BPC_EXT 0x96CD
#تعریف_کن GL_SURFACE_COMPRESSION_FIXED_نرخ_11_BPC_EXT 0x96CE
#تعریف_کن GL_SURFACE_COMPRESSION_FIXED_نرخ_12_BPC_EXT 0x96CF
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGEATTRIBS2DEXTPROC) (GLenum هدف, GLsizei سطوح, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع, ثابت GLint* attrib_list);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGEATTRIBS3DEXTPROC) (GLenum هدف, GLsizei سطوح, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, ثابت GLint* attrib_list);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTexStorageAttribs2DEXT (GLenum هدف, GLsizei سطوح, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع, ثابت GLint* attrib_list);
GL_APICALL فراغ GL_APIENTRY glTexStorageAttribs3DEXT (GLenum هدف, GLsizei سطوح, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, ثابت GLint* attrib_list);
#پایان_اگر
#پایان_اگر /* GL_EXT_texture_storage_compression */

#اگر_تعریف_نشده GL_EXT_texture_type_2_10_10_10_REV
#تعریف_کن GL_EXT_texture_type_2_10_10_10_REV 1
#تعریف_کن GL_UNSIGNED_INT_2_10_10_10_REV_EXT 0x8368
#پایان_اگر /* GL_EXT_texture_type_2_10_10_10_REV */

#اگر_تعریف_نشده GL_EXT_texture_view
#تعریف_کن GL_EXT_texture_view 1
#تعریف_کن GL_TEXTURE_VIEW_MIN_LEVEL_EXT     0x82DB
#تعریف_کن GL_TEXTURE_VIEW_رقم_سطوح_EXT    0x82DC
#تعریف_کن GL_TEXTURE_VIEW_MIN_LAYER_EXT     0x82DD
#تعریف_کن GL_TEXTURE_VIEW_رقم_LAYERS_EXT    0x82DE
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTUREVIEWEXTPROC) (GLuint texture, GLenum هدف, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTextureViewEXT (GLuint texture, GLenum هدف, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
#پایان_اگر
#پایان_اگر /* GL_EXT_texture_view */

#اگر_تعریف_نشده GL_EXT_unpack_subimage
#تعریف_کن GL_EXT_unpack_subimage 1
#تعریف_کن GL_UNPACK_ردیف_درازی_EXT          0x0CF2
#تعریف_کن GL_UNPACK_SKIP_ردیفها_EXT           0x0CF3
#تعریف_کن GL_UNPACK_SKIP_PIXELS_EXT         0x0CF4
#پایان_اگر /* GL_EXT_unpack_subimage */

#اگر_تعریف_نشده GL_EXT_win32_keyed_mutex
#تعریف_کن GL_EXT_win32_keyed_mutex 1
تعريفنوع GLboolean (GL_APIENTRYP PFNGLACQUIREKEYEDMUTEXWIN32EXTPROC) (GLuint حافظه, GLuint64 کلید, GLuint timeout);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLRELEASEKEYEDMUTEXWIN32EXTPROC) (GLuint حافظه, GLuint64 کلید);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL GLboolean GL_APIENTRY glAcquireKeyedMutexWin32EXT (GLuint حافظه, GLuint64 کلید, GLuint timeout);
GL_APICALL GLboolean GL_APIENTRY glReleaseKeyedMutexWin32EXT (GLuint حافظه, GLuint64 کلید);
#پایان_اگر
#پایان_اگر /* GL_EXT_win32_keyed_mutex */

#اگر_تعریف_نشده GL_EXT_پنجره_rectangles
#تعریف_کن GL_EXT_پنجره_rectangles 1
#تعریف_کن GL_INCLUSIVE_EXT                  0x8F10
#تعریف_کن GL_EXCLUSIVE_EXT                  0x8F11
#تعریف_کن GL_پنجره_RECTANGLE_EXT           0x8F12
#تعریف_کن GL_پنجره_RECTANGLE_نما_EXT      0x8F13
#تعریف_کن GL_MAX_پنجره_RECTANGLES_EXT      0x8F14
#تعریف_کن GL_رقم_پنجره_RECTANGLES_EXT      0x8F15
تعريفنوع فراغ (GL_APIENTRYP PFNGLWINDOWRECTANGLESEXTPROC) (GLenum نما, GLsizei شمار, ثابت GLint *box);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_پنجره_Rectangles_EXT (GLenum نما, GLsizei شمار, ثابت GLint *box);
#پایان_اگر
#پایان_اگر /* GL_EXT_window_rectangles */

#اگر_تعریف_نشده GL_FJ_shader_دودویی_GCCSO
#تعریف_کن GL_FJ_shader_دودویی_GCCSO 1
#تعریف_کن GL_GCCSO_SHADER_دودویی_FJ         0x9260
#پایان_اگر /* GL_FJ_shader_binary_GCCSO */

#اگر_تعریف_نشده GL_HUAWEI_برنامه_دودویی
#تعریف_کن GL_HUAWEI_برنامه_دودویی 1
#تعریف_کن GL_برنامه_دودویی_HUAWEI          0x9771
#پایان_اگر /* GL_HUAWEI_program_binary */

#اگر_تعریف_نشده GL_HUAWEI_shader_دودویی
#تعریف_کن GL_HUAWEI_shader_دودویی 1
#تعریف_کن GL_SHADER_دودویی_HUAWEI           0x9770
#پایان_اگر /* GL_HUAWEI_shader_binary */

#اگر_تعریف_نشده GL_IMG_bindless_texture
#تعریف_کن GL_IMG_bindless_texture 1
تعريفنوع GLuint64 (GL_APIENTRYP PFNGLGETTEXTUREHANDLEIMGPROC) (GLuint texture);
تعريفنوع GLuint64 (GL_APIENTRYP PFNGLGETTEXTURESAMPLERHANDLEIMGPROC) (GLuint texture, GLuint sampler);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMHANDLEUI64IMGPROC) (GLint location, GLuint64 مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMHANDLEUI64VIMGPROC) (GLint location, GLsizei شمار, ثابت GLuint64 *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64IMGPROC) (GLuint برنامه, GLint location, GLuint64 مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64VIMGPROC) (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLuint64 *مقادیر);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL GLuint64 GL_APIENTRY glGetTextureHandleIMG (GLuint texture);
GL_APICALL GLuint64 GL_APIENTRY glGetTextureSamplerHandleIMG (GLuint texture, GLuint sampler);
GL_APICALL فراغ GL_APIENTRY gl_یکنواخت_Handleui64_IMG (GLint location, GLuint64 مقدار);
GL_APICALL فراغ GL_APIENTRY gl_یکنواخت_Handleui64v_IMG (GLint location, GLsizei شمار, ثابت GLuint64 *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_یکنواخت_Handleui64_IMG (GLuint برنامه, GLint location, GLuint64 مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_یکنواخت_Handleui64v_IMG (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLuint64 *مقادیر);
#پایان_اگر
#پایان_اگر /* GL_IMG_bindless_texture */

#اگر_تعریف_نشده GL_IMG_framebuffer_downsample
#تعریف_کن GL_IMG_framebuffer_downsample 1
#تعریف_کن GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_AND_DOWNSAMPLE_IMG 0x913C
#تعریف_کن GL_رقم_DOWNSAMPLE_SCALES_IMG      0x913D
#تعریف_کن GL_DOWNSAMPLE_SCALES_IMG          0x913E
#تعریف_کن GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SCALE_IMG 0x913F
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DDOWNSAMPLEIMGPROC) (GLenum هدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint xscale, GLint yscale);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURELAYERDOWNSAMPLEIMGPROC) (GLenum هدف, GLenum attachment, GLuint texture, GLint level, GLint layer, GLint xscale, GLint yscale);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferTexture2DDownsampleIMG (GLenum هدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint xscale, GLint yscale);
GL_APICALL فراغ GL_APIENTRY glFramebufferTextureLayerDownsampleIMG (GLenum هدف, GLenum attachment, GLuint texture, GLint level, GLint layer, GLint xscale, GLint yscale);
#پایان_اگر
#پایان_اگر /* GL_IMG_framebuffer_downsample */

#اگر_تعریف_نشده GL_IMG_multisampled_render_مقصد_texture
#تعریف_کن GL_IMG_multisampled_render_مقصد_texture 1
#تعریف_کن GL_RENDERBUFFER_SAMPLES_IMG       0x9133
#تعریف_کن GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_IMG 0x9134
#تعریف_کن GL_MAX_SAMPLES_IMG                0x9135
#تعریف_کن GL_TEXTURE_SAMPLES_IMG            0x9136
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEIMGPROC) (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEIMGPROC) (GLenum هدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glRenderbufferStorageMultisampleIMG (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
GL_APICALL فراغ GL_APIENTRY glFramebufferTexture2DMultisampleIMG (GLenum هدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#پایان_اگر
#پایان_اگر /* GL_IMG_multisampled_render_to_texture */

#اگر_تعریف_نشده GL_IMG_برنامه_دودویی
#تعریف_کن GL_IMG_برنامه_دودویی 1
#تعریف_کن GL_SGX_برنامه_دودویی_IMG         0x9130
#پایان_اگر /* GL_IMG_program_binary */

#اگر_تعریف_نشده GL_IMG_read_format
#تعریف_کن GL_IMG_read_format 1
#تعریف_کن GL_BGRA_IMG                       0x80E1
#تعریف_کن GL_UNSIGNED_SHORT_4_4_4_4_REV_IMG 0x8365
#پایان_اگر /* GL_IMG_read_format */

#اگر_تعریف_نشده GL_IMG_shader_دودویی
#تعریف_کن GL_IMG_shader_دودویی 1
#تعریف_کن GL_SGX_دودویی_IMG                 0x8C0A
#پایان_اگر /* GL_IMG_shader_binary */

#اگر_تعریف_نشده GL_IMG_texture_compression_pvrtc
#تعریف_کن GL_IMG_texture_compression_pvrtc 1
#تعریف_کن GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG 0x8C00
#تعریف_کن GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG 0x8C01
#تعریف_کن GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG 0x8C02
#تعریف_کن GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG 0x8C03
#پایان_اگر /* GL_IMG_texture_compression_pvrtc */

#اگر_تعریف_نشده GL_IMG_texture_compression_pvrtc2
#تعریف_کن GL_IMG_texture_compression_pvrtc2 1
#تعریف_کن GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG 0x9137
#تعریف_کن GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG 0x9138
#پایان_اگر /* GL_IMG_texture_compression_pvrtc2 */

#اگر_تعریف_نشده GL_IMG_texture_filter_cubic
#تعریف_کن GL_IMG_texture_filter_cubic 1
#تعریف_کن GL_CUBIC_IMG                      0x9139
#تعریف_کن GL_CUBIC_MIPMAP_نزدیکترین_IMG       0x913A
#تعریف_کن GL_CUBIC_MIPMAP_خطی_IMG        0x913B
#پایان_اگر /* GL_IMG_texture_filter_cubic */

#اگر_تعریف_نشده GL_INTEL_blackhole_render
#تعریف_کن GL_INTEL_blackhole_render 1
#تعریف_کن GL_BLACKHOLE_RENDER_INTEL         0x83FC
#پایان_اگر /* GL_INTEL_blackhole_render */

#اگر_تعریف_نشده GL_INTEL_conservative_rasterization
#تعریف_کن GL_INTEL_conservative_rasterization 1
#تعریف_کن GL_CONSERVATIVE_RASTERIZATION_INTEL 0x83FE
#پایان_اگر /* GL_INTEL_conservative_rasterization */

#اگر_تعریف_نشده GL_INTEL_framebuffer_CMAA
#تعریف_کن GL_INTEL_framebuffer_CMAA 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLAPPLYFRAMEBUFFERATTACHMENTCMAAINTELPROC) (فراغ);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glApplyFramebufferAttachmentCMAAINTEL (فراغ);
#پایان_اگر
#پایان_اگر /* GL_INTEL_framebuffer_CMAA */

#اگر_تعریف_نشده GL_INTEL_performance_query
#تعریف_کن GL_INTEL_performance_query 1
#تعریف_کن GL_PERFQUERY_SINGLE_CONTEXT_INTEL 0x00000000
#تعریف_کن GL_PERFQUERY_GLOBAL_CONTEXT_INTEL 0x00000001
#تعریف_کن GL_PERFQUERY_WAIT_INTEL           0x83FB
#تعریف_کن GL_PERFQUERY_FLUSH_INTEL          0x83FA
#تعریف_کن GL_PERFQUERY_DONOT_FLUSH_INTEL    0x83F9
#تعریف_کن GL_PERFQUERY_COUNTER_EVENT_INTEL  0x94F0
#تعریف_کن GL_PERFQUERY_COUNTER_DURATION_NORM_INTEL 0x94F1
#تعریف_کن GL_PERFQUERY_COUNTER_DURATION_RAW_INTEL 0x94F2
#تعریف_کن GL_PERFQUERY_COUNTER_THROUGHPUT_INTEL 0x94F3
#تعریف_کن GL_PERFQUERY_COUNTER_RAW_INTEL    0x94F4
#تعریف_کن GL_PERFQUERY_COUNTER_TIMESTAMP_INTEL 0x94F5
#تعریف_کن GL_PERFQUERY_COUNTER_داده_UINT32_INTEL 0x94F8
#تعریف_کن GL_PERFQUERY_COUNTER_داده_UINT64_INTEL 0x94F9
#تعریف_کن GL_PERFQUERY_COUNTER_داده_FLOAT_INTEL 0x94FA
#تعریف_کن GL_PERFQUERY_COUNTER_داده_DOUBLE_INTEL 0x94FB
#تعریف_کن GL_PERFQUERY_COUNTER_داده_BOOL32_INTEL 0x94FC
#تعریف_کن GL_PERFQUERY_QUERY_NAME_درازی_MAX_INTEL 0x94FD
#تعریف_کن GL_PERFQUERY_COUNTER_NAME_درازی_MAX_INTEL 0x94FE
#تعریف_کن GL_PERFQUERY_COUNTER_DESC_درازی_MAX_INTEL 0x94FF
#تعریف_کن GL_PERFQUERY_GPA_EXTENDED_COUNTERS_INTEL 0x9500
تعريفنوع فراغ (GL_APIENTRYP PFNGLBEGINPERFQUERYINTELPROC) (GLuint queryHandle);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCREATEPERFQUERYINTELPROC) (GLuint queryId, GLuint *queryHandle);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEPERFQUERYINTELPROC) (GLuint queryHandle);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENDPERFQUERYINTELPROC) (GLuint queryHandle);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFIRSTPERFQUERYIDINTELPROC) (GLuint *queryId);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNEXTPERFQUERYIDINTELPROC) (GLuint queryId, GLuint *بعدی_Query_Id);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFCOUNTERINFOINTELPROC) (GLuint queryId, GLuint counterId, GLuint counter_Name_درازی, GLchar *counterName, GLuint counter_Desc_درازی, GLchar *counterDesc, GLuint *counter_جابه_جایی, GLuint *counter_داده_اندازه, GLuint *counterTypeEnum, GLuint *counter_داده_Type_Enum, GLuint64 *raw_Counter_Max_مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFQUERYDATAINTELPROC) (GLuint queryHandle, GLuint flags, GLsizei داده_اندازه_2, فراغ *داده, GLuint *بایتها_Written);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFQUERYIDBYNAMEINTELPROC) (GLchar *queryName, GLuint *queryId);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFQUERYINFOINTELPROC) (GLuint queryId, GLuint query_Name_درازی, GLchar *queryName, GLuint *داده_اندازه_2, GLuint *noCounters, GLuint *noInstances, GLuint *caps_ماسک);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glBeginPerfQueryINTEL (GLuint queryHandle);
GL_APICALL فراغ GL_APIENTRY glCreatePerfQueryINTEL (GLuint queryId, GLuint *queryHandle);
GL_APICALL فراغ GL_APIENTRY glDeletePerfQueryINTEL (GLuint queryHandle);
GL_APICALL فراغ GL_APIENTRY gl_انتها_Perf_Query_INTEL (GLuint queryHandle);
GL_APICALL فراغ GL_APIENTRY gl_Get_اولی_Perf_Query_Id_INTEL (GLuint *queryId);
GL_APICALL فراغ GL_APIENTRY gl_Get_بعدی_Perf_Query_Id_INTEL (GLuint queryId, GLuint *بعدی_Query_Id);
GL_APICALL فراغ GL_APIENTRY glGetPerfCounterInfoINTEL (GLuint queryId, GLuint counterId, GLuint counter_Name_درازی, GLchar *counterName, GLuint counter_Desc_درازی, GLchar *counterDesc, GLuint *counter_جابه_جایی, GLuint *counter_داده_اندازه, GLuint *counterTypeEnum, GLuint *counter_داده_Type_Enum, GLuint64 *raw_Counter_Max_مقدار);
GL_APICALL فراغ GL_APIENTRY gl_Get_Perf_Query_داده_INTEL (GLuint queryHandle, GLuint flags, GLsizei داده_اندازه_2, فراغ *داده, GLuint *بایتها_Written);
GL_APICALL فراغ GL_APIENTRY glGetPerfQueryIdByNameINTEL (GLchar *queryName, GLuint *queryId);
GL_APICALL فراغ GL_APIENTRY glGetPerfQueryInfoINTEL (GLuint queryId, GLuint query_Name_درازی, GLchar *queryName, GLuint *داده_اندازه_2, GLuint *noCounters, GLuint *noInstances, GLuint *caps_ماسک);
#پایان_اگر
#پایان_اگر /* GL_INTEL_performance_query */

#اگر_تعریف_نشده GL_MESA_bgra
#تعریف_کن GL_MESA_bgra 1
#تعریف_کن GL_BGR_EXT                        0x80E0
#پایان_اگر /* GL_MESA_bgra */

#اگر_تعریف_نشده GL_MESA_framebuffer_flip_x
#تعریف_کن GL_MESA_framebuffer_flip_x 1
#تعریف_کن GL_FRAMEBUFFER_FLIP_X_MESA        0x8BBC
#پایان_اگر /* GL_MESA_framebuffer_flip_x */

#اگر_تعریف_نشده GL_MESA_framebuffer_flip_y
#تعریف_کن GL_MESA_framebuffer_flip_y 1
#تعریف_کن GL_FRAMEBUFFER_FLIP_Y_MESA        0x8BBB
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERPARAMETERIMESAPROC) (GLenum هدف, GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFRAMEBUFFERPARAMETERIVMESAPROC) (GLenum هدف, GLenum pname, GLint *params);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferParameteriMESA (GLenum هدف, GLenum pname, GLint param);
GL_APICALL فراغ GL_APIENTRY glGetFramebufferParameterivMESA (GLenum هدف, GLenum pname, GLint *params);
#پایان_اگر
#پایان_اگر /* GL_MESA_framebuffer_flip_y */

#اگر_تعریف_نشده GL_MESA_framebuffer_جابجا_xy
#تعریف_کن GL_MESA_framebuffer_جابجا_xy 1
#تعریف_کن GL_FRAMEBUFFER_جابجا_XY_MESA       0x8BBD
#پایان_اگر /* GL_MESA_framebuffer_swap_xy */

#اگر_تعریف_نشده GL_MESA_برنامه_دودویی_formats
#تعریف_کن GL_MESA_برنامه_دودویی_formats 1
#تعریف_کن GL_برنامه_دودویی_FORMAT_MESA     0x875F
#پایان_اگر /* GL_MESA_program_binary_formats */

#اگر_تعریف_نشده GL_MESA_sampler_objects
#تعریف_کن GL_MESA_sampler_objects 1
#تعریف_کن GL_SAMPLER_BINDING                0x8919
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENSAMPLERSPROC) (GLsizei شمار, GLuint *samplers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETESAMPLERSPROC) (GLsizei شمار, ثابت GLuint *samplers);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISSAMPLERPROC) (GLuint sampler);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDSAMPLERPROC) (GLuint unit, GLuint sampler);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIPROC) (GLuint sampler, GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, ثابت GLint *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERFPROC) (GLuint sampler, GLenum pname, GLfloat param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, ثابت GLfloat *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, GLfloat *params);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glGenSamplers (GLsizei شمار, GLuint *samplers);
GL_APICALL فراغ GL_APIENTRY glDeleteSamplers (GLsizei شمار, ثابت GLuint *samplers);
GL_APICALL GLboolean GL_APIENTRY glIsSampler (GLuint sampler);
GL_APICALL فراغ GL_APIENTRY glBindSampler (GLuint unit, GLuint sampler);
GL_APICALL فراغ GL_APIENTRY glSamplerParameteri (GLuint sampler, GLenum pname, GLint param);
GL_APICALL فراغ GL_APIENTRY glSamplerParameteriv (GLuint sampler, GLenum pname, ثابت GLint *param);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterf (GLuint sampler, GLenum pname, GLfloat param);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterfv (GLuint sampler, GLenum pname, ثابت GLfloat *param);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameteriv (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameterfv (GLuint sampler, GLenum pname, GLfloat *params);
#پایان_اگر
#پایان_اگر /* GL_MESA_sampler_objects */

#اگر_تعریف_نشده GL_MESA_shader_integer_functions
#تعریف_کن GL_MESA_shader_integer_functions 1
#پایان_اگر /* GL_MESA_shader_integer_functions */

#اگر_تعریف_نشده GL_MESA_texture_const_bandwidth
#تعریف_کن GL_MESA_texture_const_bandwidth 1
#تعریف_کن GL_CONST_BW_TILING_MESA           0x8BBE
#پایان_اگر /* GL_MESA_texture_const_bandwidth */

#اگر_تعریف_نشده GL_NVX_blend_equation_advanced_multi_draw_buffers
#تعریف_کن GL_NVX_blend_equation_advanced_multi_draw_buffers 1
#پایان_اگر /* GL_NVX_blend_equation_advanced_multi_draw_buffers */

#اگر_تعریف_نشده GL_NV_bindless_texture
#تعریف_کن GL_NV_bindless_texture 1
تعريفنوع GLuint64 (GL_APIENTRYP PFNGLGETTEXTUREHANDLENVPROC) (GLuint texture);
تعريفنوع GLuint64 (GL_APIENTRYP PFNGLGETTEXTURESAMPLERHANDLENVPROC) (GLuint texture, GLuint sampler);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMAKETEXTUREHANDLERESIDENTNVPROC) (GLuint64 handle);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMAKETEXTUREHANDLENONRESIDENTNVPROC) (GLuint64 handle);
تعريفنوع GLuint64 (GL_APIENTRYP PFNGLGETIMAGEHANDLENVPROC) (GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMAKEIMAGEHANDLERESIDENTNVPROC) (GLuint64 handle, GLenum access);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMAKEIMAGEHANDLENONRESIDENTNVPROC) (GLuint64 handle);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMHANDLEUI64NVPROC) (GLint location, GLuint64 مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMHANDLEUI64VNVPROC) (GLint location, GLsizei شمار, ثابت GLuint64 *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64NVPROC) (GLuint برنامه, GLint location, GLuint64 مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64VNVPROC) (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLuint64 *مقادیر);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISTEXTUREHANDLERESIDENTNVPROC) (GLuint64 handle);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISIMAGEHANDLERESIDENTNVPROC) (GLuint64 handle);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL GLuint64 GL_APIENTRY glGetTextureHandleNV (GLuint texture);
GL_APICALL GLuint64 GL_APIENTRY glGetTextureSamplerHandleNV (GLuint texture, GLuint sampler);
GL_APICALL فراغ GL_APIENTRY glMakeTextureHandleResidentNV (GLuint64 handle);
GL_APICALL فراغ GL_APIENTRY glMakeTextureHandleNonResidentNV (GLuint64 handle);
GL_APICALL GLuint64 GL_APIENTRY glGetImageHandleNV (GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format);
GL_APICALL فراغ GL_APIENTRY glMakeImageHandleResidentNV (GLuint64 handle, GLenum access);
GL_APICALL فراغ GL_APIENTRY glMakeImageHandleNonResidentNV (GLuint64 handle);
GL_APICALL فراغ GL_APIENTRY gl_یکنواخت_Handleui64_NV (GLint location, GLuint64 مقدار);
GL_APICALL فراغ GL_APIENTRY gl_یکنواخت_Handleui64v_NV (GLint location, GLsizei شمار, ثابت GLuint64 *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_یکنواخت_Handleui64_NV (GLuint برنامه, GLint location, GLuint64 مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_یکنواخت_Handleui64v_NV (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLuint64 *مقادیر);
GL_APICALL GLboolean GL_APIENTRY glIsTextureHandleResidentNV (GLuint64 handle);
GL_APICALL GLboolean GL_APIENTRY glIsImageHandleResidentNV (GLuint64 handle);
#پایان_اگر
#پایان_اگر /* GL_NV_bindless_texture */

#اگر_تعریف_نشده GL_NV_blend_equation_advanced
#تعریف_کن GL_NV_blend_equation_advanced 1
#تعریف_کن GL_BLEND_OVERLAP_NV               0x9281
#تعریف_کن GL_BLEND_PREMULTIPLIED_SRC_NV     0x9280
#تعریف_کن GL_BLUE_NV                        0x1905
#تعریف_کن GL_COLORBURN_NV                   0x929A
#تعریف_کن GL_COLORDODGE_NV                  0x9299
#تعریف_کن GL_CONJOINT_NV                    0x9284
#تعریف_کن GL_CONTRAST_NV                    0x92A1
#تعریف_کن GL_DARKEN_NV                      0x9297
#تعریف_کن GL_DIFFERENCE_NV                  0x929E
#تعریف_کن GL_DISJOINT_NV                    0x9283
#تعریف_کن GL_DST_ATOP_NV                    0x928F
#تعریف_کن GL_DST_درون_NV                      0x928B
#تعریف_کن GL_DST_NV                         0x9287
#تعریف_کن GL_DST_بیرون_NV                     0x928D
#تعریف_کن GL_DST_OVER_NV                    0x9289
#تعریف_کن GL_EXCLUSION_NV                   0x92A0
#تعریف_کن GL_GREEN_NV                       0x1904
#تعریف_کن GL_HARDLIGHT_NV                   0x929B
#تعریف_کن GL_HARDMIX_NV                     0x92A9
#تعریف_کن GL_HSL_COLOR_NV                   0x92AF
#تعریف_کن GL_HSL_HUE_NV                     0x92AD
#تعریف_کن GL_HSL_LUMINOSITY_NV              0x92B0
#تعریف_کن GL_HSL_SATURATION_NV              0x92AE
#تعریف_کن GL_INVERT_OVG_NV                  0x92B4
#تعریف_کن GL_INVERT_RGB_NV                  0x92A3
#تعریف_کن GL_LIGHTEN_NV                     0x9298
#تعریف_کن GL_LINEARBURN_NV                  0x92A5
#تعریف_کن GL_LINEARDODGE_NV                 0x92A4
#تعریف_کن GL_LINEARLIGHT_NV                 0x92A7
#تعریف_کن GL_MINUS_CLAMPED_NV               0x92B3
#تعریف_کن GL_MINUS_NV                       0x929F
#تعریف_کن GL_MULTIPLY_NV                    0x9294
#تعریف_کن GL_OVERLAY_NV                     0x9296
#تعریف_کن GL_PINLIGHT_NV                    0x92A8
#تعریف_کن GL_PLUS_CLAMPED_ALPHA_NV          0x92B2
#تعریف_کن GL_PLUS_CLAMPED_NV                0x92B1
#تعریف_کن GL_PLUS_DARKER_NV                 0x9292
#تعریف_کن GL_PLUS_NV                        0x9291
#تعریف_کن GL_RED_NV                         0x1903
#تعریف_کن GL_SCREEN_NV                      0x9295
#تعریف_کن GL_SOFTLIGHT_NV                   0x929C
#تعریف_کن GL_SRC_ATOP_NV                    0x928E
#تعریف_کن GL_SRC_درون_NV                      0x928A
#تعریف_کن GL_SRC_NV                         0x9286
#تعریف_کن GL_SRC_بیرون_NV                     0x928C
#تعریف_کن GL_SRC_OVER_NV                    0x9288
#تعریف_کن GL_UNCORRELATED_NV                0x9282
#تعریف_کن GL_VIVIDLIGHT_NV                  0x92A6
#تعریف_کن GL_XOR_NV                         0x1506
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDPARAMETERINVPROC) (GLenum pname, GLint مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDBARRIERNVPROC) (فراغ);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glBlendParameteriNV (GLenum pname, GLint مقدار);
GL_APICALL فراغ GL_APIENTRY glBlendBarrierNV (فراغ);
#پایان_اگر
#پایان_اگر /* GL_NV_blend_equation_advanced */

#اگر_تعریف_نشده GL_NV_blend_equation_advanced_coherent
#تعریف_کن GL_NV_blend_equation_advanced_coherent 1
#تعریف_کن GL_BLEND_ADVANCED_COHERENT_NV     0x9285
#پایان_اگر /* GL_NV_blend_equation_advanced_coherent */

#اگر_تعریف_نشده GL_NV_blend_minmax_ضریب
#تعریف_کن GL_NV_blend_minmax_ضریب 1
#تعریف_کن GL_ضریب_MIN_AMD                 0x901C
#تعریف_کن GL_ضریب_MAX_AMD                 0x901D
#پایان_اگر /* GL_NV_blend_minmax_factor */

#اگر_تعریف_نشده GL_NV_clip_space_w_scaling
#تعریف_کن GL_NV_clip_space_w_scaling 1
#تعریف_کن GL_VIEWPORT_POSITION_W_SCALE_NV   0x937C
#تعریف_کن GL_VIEWPORT_POSITION_W_SCALE_X_COEFF_NV 0x937D
#تعریف_کن GL_VIEWPORT_POSITION_W_SCALE_Y_COEFF_NV 0x937E
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTPOSITIONWSCALENVPROC) (GLuint شاخص, GLfloat xcoeff, GLfloat ycoeff);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glViewportPositionWScaleNV (GLuint شاخص, GLfloat xcoeff, GLfloat ycoeff);
#پایان_اگر
#پایان_اگر /* GL_NV_clip_space_w_scaling */

#اگر_تعریف_نشده GL_NV_compute_shader_derivatives
#تعریف_کن GL_NV_compute_shader_derivatives 1
#پایان_اگر /* GL_NV_compute_shader_derivatives */

#اگر_تعریف_نشده GL_NV_conditional_render
#تعریف_کن GL_NV_conditional_render 1
#تعریف_کن GL_QUERY_WAIT_NV                  0x8E13
#تعریف_کن GL_QUERY_NO_WAIT_NV               0x8E14
#تعریف_کن GL_QUERY_BY_REGION_WAIT_NV        0x8E15
#تعریف_کن GL_QUERY_BY_REGION_NO_WAIT_NV     0x8E16
تعريفنوع فراغ (GL_APIENTRYP PFNGLBEGINCONDITIONALRENDERNVPROC) (GLuint id, GLenum نما);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENDCONDITIONALRENDERNVPROC) (فراغ);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glBeginConditionalRenderNV (GLuint id, GLenum نما);
GL_APICALL فراغ GL_APIENTRY gl_انتها_Conditional_Render_NV (فراغ);
#پایان_اگر
#پایان_اگر /* GL_NV_conditional_render */

#اگر_تعریف_نشده GL_NV_conservative_raster
#تعریف_کن GL_NV_conservative_raster 1
#تعریف_کن GL_CONSERVATIVE_RASTERIZATION_NV  0x9346
#تعریف_کن GL_SUBPIXEL_PRECISION_BIAS_X_بیتها_NV 0x9347
#تعریف_کن GL_SUBPIXEL_PRECISION_BIAS_Y_بیتها_NV 0x9348
#تعریف_کن GL_MAX_SUBPIXEL_PRECISION_BIAS_بیتها_NV 0x9349
تعريفنوع فراغ (GL_APIENTRYP PFNGLSUBPIXELPRECISIONBIASNVPROC) (GLuint xbits, GLuint ybits);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glSubpixelPrecisionBiasNV (GLuint xbits, GLuint ybits);
#پایان_اگر
#پایان_اگر /* GL_NV_conservative_raster */

#اگر_تعریف_نشده GL_NV_conservative_raster_pre_snap
#تعریف_کن GL_NV_conservative_raster_pre_snap 1
#تعریف_کن GL_CONSERVATIVE_RASTER_نما_PRE_SNAP_NV 0x9550
#پایان_اگر /* GL_NV_conservative_raster_pre_snap */

#اگر_تعریف_نشده GL_NV_conservative_raster_pre_snap_triangles
#تعریف_کن GL_NV_conservative_raster_pre_snap_triangles 1
#تعریف_کن GL_CONSERVATIVE_RASTER_نما_NV    0x954D
#تعریف_کن GL_CONSERVATIVE_RASTER_نما_POST_SNAP_NV 0x954E
#تعریف_کن GL_CONSERVATIVE_RASTER_نما_PRE_SNAP_TRIANGLES_NV 0x954F
تعريفنوع فراغ (GL_APIENTRYP PFNGLCONSERVATIVERASTERPARAMETERINVPROC) (GLenum pname, GLint param);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glConservativeRasterParameteriNV (GLenum pname, GLint param);
#پایان_اگر
#پایان_اگر /* GL_NV_conservative_raster_pre_snap_triangles */

#اگر_تعریف_نشده GL_NV_copy_میانگیر
#تعریف_کن GL_NV_copy_میانگیر 1
#تعریف_کن GL_COPY_READ_میانگیر_NV            0x8F36
#تعریف_کن GL_COPY_WRITE_میانگیر_NV           0x8F37
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYBUFFERSUBDATANVPROC) (GLenum read_هدف, GLenum write_هدف, GLintptr read_جابه_جایی, GLintptr write_جابه_جایی, GLsizeiptr اندازه);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Copy_میانگیر_Sub_داده_NV (GLenum read_هدف, GLenum write_هدف, GLintptr read_جابه_جایی, GLintptr write_جابه_جایی, GLsizeiptr اندازه);
#پایان_اگر
#پایان_اگر /* GL_NV_copy_buffer */

#اگر_تعریف_نشده GL_NV_coverage_sample
#تعریف_کن GL_NV_coverage_sample 1
#تعریف_کن GL_COVERAGE_COMPONENT_NV          0x8ED0
#تعریف_کن GL_COVERAGE_COMPONENT4_NV         0x8ED1
#تعریف_کن GL_COVERAGE_ATTACHMENT_NV         0x8ED2
#تعریف_کن GL_COVERAGE_BUFFERS_NV            0x8ED3
#تعریف_کن GL_COVERAGE_SAMPLES_NV            0x8ED4
#تعریف_کن GL_COVERAGE_ALL_FRAGMENTS_NV      0x8ED5
#تعریف_کن GL_COVERAGE_یال_FRAGMENTS_NV     0x8ED6
#تعریف_کن GL_COVERAGE_AUTOMATIC_NV          0x8ED7
#تعریف_کن GL_COVERAGE_میانگیر_بیت_NV         0x00008000
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOVERAGEMASKNVPROC) (GLboolean ماسک);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOVERAGEOPERATIONNVPROC) (GLenum operation);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Coverage_ماسک_NV (GLboolean ماسک);
GL_APICALL فراغ GL_APIENTRY glCoverageOperationNV (GLenum operation);
#پایان_اگر
#پایان_اگر /* GL_NV_coverage_sample */

#اگر_تعریف_نشده GL_NV_عمق_nonlinear
#تعریف_کن GL_NV_عمق_nonlinear 1
#تعریف_کن GL_عمق_COMPONENT16_NONLINEAR_NV 0x8E2C
#پایان_اگر /* GL_NV_depth_nonlinear */

#اگر_تعریف_نشده GL_NV_draw_buffers
#تعریف_کن GL_NV_draw_buffers 1
#تعریف_کن GL_MAX_DRAW_BUFFERS_NV            0x8824
#تعریف_کن GL_DRAW_BUFFER0_NV                0x8825
#تعریف_کن GL_DRAW_BUFFER1_NV                0x8826
#تعریف_کن GL_DRAW_BUFFER2_NV                0x8827
#تعریف_کن GL_DRAW_BUFFER3_NV                0x8828
#تعریف_کن GL_DRAW_BUFFER4_NV                0x8829
#تعریف_کن GL_DRAW_BUFFER5_NV                0x882A
#تعریف_کن GL_DRAW_BUFFER6_NV                0x882B
#تعریف_کن GL_DRAW_BUFFER7_NV                0x882C
#تعریف_کن GL_DRAW_BUFFER8_NV                0x882D
#تعریف_کن GL_DRAW_BUFFER9_NV                0x882E
#تعریف_کن GL_DRAW_BUFFER10_NV               0x882F
#تعریف_کن GL_DRAW_BUFFER11_NV               0x8830
#تعریف_کن GL_DRAW_BUFFER12_NV               0x8831
#تعریف_کن GL_DRAW_BUFFER13_NV               0x8832
#تعریف_کن GL_DRAW_BUFFER14_NV               0x8833
#تعریف_کن GL_DRAW_BUFFER15_NV               0x8834
#تعریف_کن GL_COLOR_ATTACHMENT0_NV           0x8CE0
#تعریف_کن GL_COLOR_ATTACHMENT1_NV           0x8CE1
#تعریف_کن GL_COLOR_ATTACHMENT2_NV           0x8CE2
#تعریف_کن GL_COLOR_ATTACHMENT3_NV           0x8CE3
#تعریف_کن GL_COLOR_ATTACHMENT4_NV           0x8CE4
#تعریف_کن GL_COLOR_ATTACHMENT5_NV           0x8CE5
#تعریف_کن GL_COLOR_ATTACHMENT6_NV           0x8CE6
#تعریف_کن GL_COLOR_ATTACHMENT7_NV           0x8CE7
#تعریف_کن GL_COLOR_ATTACHMENT8_NV           0x8CE8
#تعریف_کن GL_COLOR_ATTACHMENT9_NV           0x8CE9
#تعریف_کن GL_COLOR_ATTACHMENT10_NV          0x8CEA
#تعریف_کن GL_COLOR_ATTACHMENT11_NV          0x8CEB
#تعریف_کن GL_COLOR_ATTACHMENT12_NV          0x8CEC
#تعریف_کن GL_COLOR_ATTACHMENT13_NV          0x8CED
#تعریف_کن GL_COLOR_ATTACHMENT14_NV          0x8CEE
#تعریف_کن GL_COLOR_ATTACHMENT15_NV          0x8CEF
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWBUFFERSNVPROC) (GLsizei n, ثابت GLenum *bufs);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawBuffersNV (GLsizei n, ثابت GLenum *bufs);
#پایان_اگر
#پایان_اگر /* GL_NV_draw_buffers */

#اگر_تعریف_نشده GL_NV_draw_instanced
#تعریف_کن GL_NV_draw_instanced 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDNVPROC) (GLenum نما, GLint اولی, GLsizei شمار, GLsizei primcount);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDNVPROC) (GLenum نما, GLsizei شمار, GLenum type, ثابت فراغ *indices, GLsizei primcount);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawArraysInstancedNV (GLenum نما, GLint اولی, GLsizei شمار, GLsizei primcount);
GL_APICALL فراغ GL_APIENTRY glDrawElementsInstancedNV (GLenum نما, GLsizei شمار, GLenum type, ثابت فراغ *indices, GLsizei primcount);
#پایان_اگر
#پایان_اگر /* GL_NV_draw_instanced */

#اگر_تعریف_نشده GL_NV_draw_vulkan_image
#تعریف_کن GL_NV_draw_vulkan_image 1
تعريفنوع فراغ (GL_APIENTRY  *GLVULKANPROCNV)(فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWVKIMAGENVPROC) (GLuint64 vkImage, GLuint sampler, GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat z, GLfloat s0, GLfloat t0, GLfloat s1, GLfloat t1);
تعريفنوع GLVULKANPROCNV (GL_APIENTRYP PFNGLGETVKPROCADDRNVPROC) (ثابت GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLWAITVKSEMAPHORENVPROC) (GLuint64 vkSemaphore);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSIGNALVKSEMAPHORENVPROC) (GLuint64 vkSemaphore);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSIGNALVKFENCENVPROC) (GLuint64 vkFence);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawVkImageNV (GLuint64 vkImage, GLuint sampler, GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat z, GLfloat s0, GLfloat t0, GLfloat s1, GLfloat t1);
GL_APICALL GLVULKANPROCNV GL_APIENTRY glGetVkProcAddrNV (ثابت GLchar *name);
GL_APICALL فراغ GL_APIENTRY glWaitVkSemaphoreNV (GLuint64 vkSemaphore);
GL_APICALL فراغ GL_APIENTRY glSignalVkSemaphoreNV (GLuint64 vkSemaphore);
GL_APICALL فراغ GL_APIENTRY glSignalVkFenceNV (GLuint64 vkFence);
#پایان_اگر
#پایان_اگر /* GL_NV_draw_vulkan_image */

#اگر_تعریف_نشده GL_NV_explicit_attrib_location
#تعریف_کن GL_NV_explicit_attrib_location 1
#پایان_اگر /* GL_NV_explicit_attrib_location */

#اگر_تعریف_نشده GL_NV_fbo_color_attachments
#تعریف_کن GL_NV_fbo_color_attachments 1
#تعریف_کن GL_MAX_COLOR_ATTACHMENTS_NV       0x8CDF
#پایان_اگر /* GL_NV_fbo_color_attachments */

#اگر_تعریف_نشده GL_NV_fence
#تعریف_کن GL_NV_fence 1
#تعریف_کن GL_ALL_COMPLETED_NV               0x84F2
#تعریف_کن GL_FENCE_وضعیت_NV                0x84F3
#تعریف_کن GL_FENCE_CONDITION_NV             0x84F4
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEFENCESNVPROC) (GLsizei n, ثابت GLuint *fences);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENFENCESNVPROC) (GLsizei n, GLuint *fences);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISFENCENVPROC) (GLuint fence);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLTESTFENCENVPROC) (GLuint fence);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFENCEIVNVPROC) (GLuint fence, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFINISHFENCENVPROC) (GLuint fence);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSETFENCENVPROC) (GLuint fence, GLenum condition);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDeleteFencesNV (GLsizei n, ثابت GLuint *fences);
GL_APICALL فراغ GL_APIENTRY glGenFencesNV (GLsizei n, GLuint *fences);
GL_APICALL GLboolean GL_APIENTRY glIsFenceNV (GLuint fence);
GL_APICALL GLboolean GL_APIENTRY glTestFenceNV (GLuint fence);
GL_APICALL فراغ GL_APIENTRY glGetFenceivNV (GLuint fence, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY gl_پایان_Fence_NV (GLuint fence);
GL_APICALL فراغ GL_APIENTRY gl_مجموعه_Fence_NV (GLuint fence, GLenum condition);
#پایان_اگر
#پایان_اگر /* GL_NV_fence */

#اگر_تعریف_نشده GL_NV_fill_rectangle
#تعریف_کن GL_NV_fill_rectangle 1
#تعریف_کن GL_FILL_RECTANGLE_NV              0x933C
#پایان_اگر /* GL_NV_fill_rectangle */

#اگر_تعریف_نشده GL_NV_fragment_coverage_مقصد_color
#تعریف_کن GL_NV_fragment_coverage_مقصد_color 1
#تعریف_کن GL_FRAGMENT_COVERAGE_مقصد_COLOR_NV  0x92DD
#تعریف_کن GL_FRAGMENT_COVERAGE_COLOR_NV     0x92DE
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAGMENTCOVERAGECOLORNVPROC) (GLuint color);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFragmentCoverageColorNV (GLuint color);
#پایان_اگر
#پایان_اگر /* GL_NV_fragment_coverage_to_color */

#اگر_تعریف_نشده GL_NV_fragment_shader_barycentric
#تعریف_کن GL_NV_fragment_shader_barycentric 1
#پایان_اگر /* GL_NV_fragment_shader_barycentric */

#اگر_تعریف_نشده GL_NV_fragment_shader_interlock
#تعریف_کن GL_NV_fragment_shader_interlock 1
#پایان_اگر /* GL_NV_fragment_shader_interlock */

#اگر_تعریف_نشده GL_NV_framebuffer_blit
#تعریف_کن GL_NV_framebuffer_blit 1
#تعریف_کن GL_READ_FRAMEBUFFER_NV            0x8CA8
#تعریف_کن GL_DRAW_FRAMEBUFFER_NV            0x8CA9
#تعریف_کن GL_DRAW_FRAMEBUFFER_BINDING_NV    0x8CA6
#تعریف_کن GL_READ_FRAMEBUFFER_BINDING_NV    0x8CAA
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLITFRAMEBUFFERNVPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield ماسک, GLenum filter);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glBlitFramebufferNV (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield ماسک, GLenum filter);
#پایان_اگر
#پایان_اگر /* GL_NV_framebuffer_blit */

#اگر_تعریف_نشده GL_NV_framebuffer_mixed_samples
#تعریف_کن GL_NV_framebuffer_mixed_samples 1
#تعریف_کن GL_COVERAGE_MODULATION_جدول_NV   0x9331
#تعریف_کن GL_COLOR_SAMPLES_NV               0x8E20
#تعریف_کن GL_عمق_SAMPLES_NV               0x932D
#تعریف_کن GL_STENCIL_SAMPLES_NV             0x932E
#تعریف_کن GL_MIXED_عمق_SAMPLES_SUPPORTED_NV 0x932F
#تعریف_کن GL_MIXED_STENCIL_SAMPLES_SUPPORTED_NV 0x9330
#تعریف_کن GL_COVERAGE_MODULATION_NV         0x9332
#تعریف_کن GL_COVERAGE_MODULATION_جدول_اندازه_NV 0x9333
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOVERAGEMODULATIONTABLENVPROC) (GLsizei n, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETCOVERAGEMODULATIONTABLENVPROC) (GLsizei buf_اندازه, GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOVERAGEMODULATIONNVPROC) (GLenum components);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Coverage_Modulation_جدول_NV (GLsizei n, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY gl_Get_Coverage_Modulation_جدول_NV (GLsizei buf_اندازه, GLfloat *v);
GL_APICALL فراغ GL_APIENTRY glCoverageModulationNV (GLenum components);
#پایان_اگر
#پایان_اگر /* GL_NV_framebuffer_mixed_samples */

#اگر_تعریف_نشده GL_NV_framebuffer_multisample
#تعریف_کن GL_NV_framebuffer_multisample 1
#تعریف_کن GL_RENDERBUFFER_SAMPLES_NV        0x8CAB
#تعریف_کن GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_NV 0x8D56
#تعریف_کن GL_MAX_SAMPLES_NV                 0x8D57
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLENVPROC) (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glRenderbufferStorageMultisampleNV (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
#پایان_اگر
#پایان_اگر /* GL_NV_framebuffer_multisample */

#اگر_تعریف_نشده GL_NV_generate_mipmap_sRGB
#تعریف_کن GL_NV_generate_mipmap_sRGB 1
#پایان_اگر /* GL_NV_generate_mipmap_sRGB */

#اگر_تعریف_نشده GL_NV_geometry_shader_passthrough
#تعریف_کن GL_NV_geometry_shader_passthrough 1
#پایان_اگر /* GL_NV_geometry_shader_passthrough */

#اگر_تعریف_نشده GL_NV_gpu_shader5
#تعریف_کن GL_NV_gpu_shader5 1
تعريفنوع khronos_int64_t GLint64EXT;
تعريفنوع khronos_uint64_t GLuint64EXT;
#تعریف_کن GL_INT64_NV                       0x140E
#تعریف_کن GL_UNSIGNED_INT64_NV              0x140F
#تعریف_کن GL_INT8_NV                        0x8FE0
#تعریف_کن GL_INT8_VEC2_NV                   0x8FE1
#تعریف_کن GL_INT8_VEC3_NV                   0x8FE2
#تعریف_کن GL_INT8_VEC4_NV                   0x8FE3
#تعریف_کن GL_INT16_NV                       0x8FE4
#تعریف_کن GL_INT16_VEC2_NV                  0x8FE5
#تعریف_کن GL_INT16_VEC3_NV                  0x8FE6
#تعریف_کن GL_INT16_VEC4_NV                  0x8FE7
#تعریف_کن GL_INT64_VEC2_NV                  0x8FE9
#تعریف_کن GL_INT64_VEC3_NV                  0x8FEA
#تعریف_کن GL_INT64_VEC4_NV                  0x8FEB
#تعریف_کن GL_UNSIGNED_INT8_NV               0x8FEC
#تعریف_کن GL_UNSIGNED_INT8_VEC2_NV          0x8FED
#تعریف_کن GL_UNSIGNED_INT8_VEC3_NV          0x8FEE
#تعریف_کن GL_UNSIGNED_INT8_VEC4_NV          0x8FEF
#تعریف_کن GL_UNSIGNED_INT16_NV              0x8FF0
#تعریف_کن GL_UNSIGNED_INT16_VEC2_NV         0x8FF1
#تعریف_کن GL_UNSIGNED_INT16_VEC3_NV         0x8FF2
#تعریف_کن GL_UNSIGNED_INT16_VEC4_NV         0x8FF3
#تعریف_کن GL_UNSIGNED_INT64_VEC2_NV         0x8FF5
#تعریف_کن GL_UNSIGNED_INT64_VEC3_NV         0x8FF6
#تعریف_کن GL_UNSIGNED_INT64_VEC4_NV         0x8FF7
#تعریف_کن GL_FLOAT16_NV                     0x8FF8
#تعریف_کن GL_FLOAT16_VEC2_NV                0x8FF9
#تعریف_کن GL_FLOAT16_VEC3_NV                0x8FFA
#تعریف_کن GL_FLOAT16_VEC4_NV                0x8FFB
#تعریف_کن GL_PATCHES                        0x000E
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1I64NVPROC) (GLint location, GLint64EXT x);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2I64NVPROC) (GLint location, GLint64EXT x, GLint64EXT y);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3I64NVPROC) (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4I64NVPROC) (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1I64VNVPROC) (GLint location, GLsizei شمار, ثابت GLint64EXT *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2I64VNVPROC) (GLint location, GLsizei شمار, ثابت GLint64EXT *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3I64VNVPROC) (GLint location, GLsizei شمار, ثابت GLint64EXT *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4I64VNVPROC) (GLint location, GLsizei شمار, ثابت GLint64EXT *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1UI64NVPROC) (GLint location, GLuint64EXT x);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2UI64NVPROC) (GLint location, GLuint64EXT x, GLuint64EXT y);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3UI64NVPROC) (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4UI64NVPROC) (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1UI64VNVPROC) (GLint location, GLsizei شمار, ثابت GLuint64EXT *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2UI64VNVPROC) (GLint location, GLsizei شمار, ثابت GLuint64EXT *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3UI64VNVPROC) (GLint location, GLsizei شمار, ثابت GLuint64EXT *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4UI64VNVPROC) (GLint location, GLsizei شمار, ثابت GLuint64EXT *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETUNIFORMI64VNVPROC) (GLuint برنامه, GLint location, GLint64EXT *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1I64NVPROC) (GLuint برنامه, GLint location, GLint64EXT x);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2I64NVPROC) (GLuint برنامه, GLint location, GLint64EXT x, GLint64EXT y);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3I64NVPROC) (GLuint برنامه, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4I64NVPROC) (GLuint برنامه, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1I64VNVPROC) (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLint64EXT *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2I64VNVPROC) (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLint64EXT *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3I64VNVPROC) (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLint64EXT *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4I64VNVPROC) (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLint64EXT *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UI64NVPROC) (GLuint برنامه, GLint location, GLuint64EXT x);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UI64NVPROC) (GLuint برنامه, GLint location, GLuint64EXT x, GLuint64EXT y);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UI64NVPROC) (GLuint برنامه, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UI64NVPROC) (GLuint برنامه, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UI64VNVPROC) (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLuint64EXT *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UI64VNVPROC) (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLuint64EXT *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UI64VNVPROC) (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLuint64EXT *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UI64VNVPROC) (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLuint64EXT *مقدار);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glUniform1i64NV (GLint location, GLint64EXT x);
GL_APICALL فراغ GL_APIENTRY glUniform2i64NV (GLint location, GLint64EXT x, GLint64EXT y);
GL_APICALL فراغ GL_APIENTRY glUniform3i64NV (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
GL_APICALL فراغ GL_APIENTRY glUniform4i64NV (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
GL_APICALL فراغ GL_APIENTRY glUniform1i64vNV (GLint location, GLsizei شمار, ثابت GLint64EXT *مقدار);
GL_APICALL فراغ GL_APIENTRY glUniform2i64vNV (GLint location, GLsizei شمار, ثابت GLint64EXT *مقدار);
GL_APICALL فراغ GL_APIENTRY glUniform3i64vNV (GLint location, GLsizei شمار, ثابت GLint64EXT *مقدار);
GL_APICALL فراغ GL_APIENTRY glUniform4i64vNV (GLint location, GLsizei شمار, ثابت GLint64EXT *مقدار);
GL_APICALL فراغ GL_APIENTRY glUniform1ui64NV (GLint location, GLuint64EXT x);
GL_APICALL فراغ GL_APIENTRY glUniform2ui64NV (GLint location, GLuint64EXT x, GLuint64EXT y);
GL_APICALL فراغ GL_APIENTRY glUniform3ui64NV (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
GL_APICALL فراغ GL_APIENTRY glUniform4ui64NV (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
GL_APICALL فراغ GL_APIENTRY glUniform1ui64vNV (GLint location, GLsizei شمار, ثابت GLuint64EXT *مقدار);
GL_APICALL فراغ GL_APIENTRY glUniform2ui64vNV (GLint location, GLsizei شمار, ثابت GLuint64EXT *مقدار);
GL_APICALL فراغ GL_APIENTRY glUniform3ui64vNV (GLint location, GLsizei شمار, ثابت GLuint64EXT *مقدار);
GL_APICALL فراغ GL_APIENTRY glUniform4ui64vNV (GLint location, GLsizei شمار, ثابت GLuint64EXT *مقدار);
GL_APICALL فراغ GL_APIENTRY glGetUniformi64vNV (GLuint برنامه, GLint location, GLint64EXT *params);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform1i64_NV (GLuint برنامه, GLint location, GLint64EXT x);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform2i64_NV (GLuint برنامه, GLint location, GLint64EXT x, GLint64EXT y);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform3i64_NV (GLuint برنامه, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform4i64_NV (GLuint برنامه, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform1i64v_NV (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLint64EXT *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform2i64v_NV (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLint64EXT *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform3i64v_NV (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLint64EXT *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform4i64v_NV (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLint64EXT *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform1ui64_NV (GLuint برنامه, GLint location, GLuint64EXT x);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform2ui64_NV (GLuint برنامه, GLint location, GLuint64EXT x, GLuint64EXT y);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform3ui64_NV (GLuint برنامه, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform4ui64_NV (GLuint برنامه, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform1ui64v_NV (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLuint64EXT *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform2ui64v_NV (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLuint64EXT *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform3ui64v_NV (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLuint64EXT *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform4ui64v_NV (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLuint64EXT *مقدار);
#پایان_اگر
#پایان_اگر /* GL_NV_gpu_shader5 */

#اگر_تعریف_نشده GL_NV_image_formats
#تعریف_کن GL_NV_image_formats 1
#پایان_اگر /* GL_NV_image_formats */

#اگر_تعریف_نشده GL_NV_instanced_arrays
#تعریف_کن GL_NV_instanced_arrays 1
#تعریف_کن GL_رأس_ATTRIB_ARRAY_مقسوم_علیه_NV 0x88FE
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBDIVISORNVPROC) (GLuint شاخص, GLuint مقسوم_علیه);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_رأس_Attrib_مقسوم_علیه_NV (GLuint شاخص, GLuint مقسوم_علیه);
#پایان_اگر
#پایان_اگر /* GL_NV_instanced_arrays */

#اگر_تعریف_نشده GL_NV_internalformat_sample_query
#تعریف_کن GL_NV_internalformat_sample_query 1
#تعریف_کن GL_TEXTURE_2D_MULTISAMPLE         0x9100
#تعریف_کن GL_TEXTURE_2D_MULTISAMPLE_ARRAY   0x9102
#تعریف_کن GL_MULTISAMPLES_NV                0x9371
#تعریف_کن GL_SUPERSAMPLE_SCALE_X_NV         0x9372
#تعریف_کن GL_SUPERSAMPLE_SCALE_Y_NV         0x9373
#تعریف_کن GL_CONFORMANT_NV                  0x9374
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTERNALFORMATSAMPLEIVNVPROC) (GLenum هدف, GLenum internalformat, GLsizei samples, GLenum pname, GLsizei شمار, GLint *params);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glGetInternalformatSampleivNV (GLenum هدف, GLenum internalformat, GLsizei samples, GLenum pname, GLsizei شمار, GLint *params);
#پایان_اگر
#پایان_اگر /* GL_NV_internalformat_sample_query */

#اگر_تعریف_نشده GL_NV_حافظه_attachment
#تعریف_کن GL_NV_حافظه_attachment 1
#تعریف_کن GL_ATTACHED_حافظه_OBJECT_NV      0x95A4
#تعریف_کن GL_ATTACHED_حافظه_جابه_جایی_NV      0x95A5
#تعریف_کن GL_حافظه_ATTACHABLE_ALIGNMENT_NV 0x95A6
#تعریف_کن GL_حافظه_ATTACHABLE_اندازه_NV      0x95A7
#تعریف_کن GL_حافظه_ATTACHABLE_NV           0x95A8
#تعریف_کن GL_DETACHED_حافظه_INCARNATION_NV 0x95A9
#تعریف_کن GL_DETACHED_TEXTURES_NV           0x95AA
#تعریف_کن GL_DETACHED_BUFFERS_NV            0x95AB
#تعریف_کن GL_MAX_DETACHED_TEXTURES_NV       0x95AC
#تعریف_کن GL_MAX_DETACHED_BUFFERS_NV        0x95AD
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETMEMORYOBJECTDETACHEDRESOURCESUIVNVPROC) (GLuint حافظه, GLenum pname, GLint اولی, GLsizei شمار, GLuint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRESETMEMORYOBJECTPARAMETERNVPROC) (GLuint حافظه, GLenum pname);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXATTACHMEMORYNVPROC) (GLenum هدف, GLuint حافظه, GLuint64 جابه_جایی_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBUFFERATTACHMEMORYNVPROC) (GLenum هدف, GLuint حافظه, GLuint64 جابه_جایی_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTUREATTACHMEMORYNVPROC) (GLuint texture, GLuint حافظه, GLuint64 جابه_جایی_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLNAMEDBUFFERATTACHMEMORYNVPROC) (GLuint میانگیر_2, GLuint حافظه, GLuint64 جابه_جایی_2);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Get_حافظه_Object_Detached_Resourcesuiv_NV (GLuint حافظه, GLenum pname, GLint اولی, GLsizei شمار, GLuint *params);
GL_APICALL فراغ GL_APIENTRY gl_Reset_حافظه_Object_Parameter_NV (GLuint حافظه, GLenum pname);
GL_APICALL فراغ GL_APIENTRY gl_Tex_Attach_حافظه_NV (GLenum هدف, GLuint حافظه, GLuint64 جابه_جایی_2);
GL_APICALL فراغ GL_APIENTRY gl_میانگیر_Attach_حافظه_NV (GLenum هدف, GLuint حافظه, GLuint64 جابه_جایی_2);
GL_APICALL فراغ GL_APIENTRY gl_Texture_Attach_حافظه_NV (GLuint texture, GLuint حافظه, GLuint64 جابه_جایی_2);
GL_APICALL فراغ GL_APIENTRY gl_Named_میانگیر_Attach_حافظه_NV (GLuint میانگیر_2, GLuint حافظه, GLuint64 جابه_جایی_2);
#پایان_اگر
#پایان_اگر /* GL_NV_memory_attachment */

#اگر_تعریف_نشده GL_NV_حافظه_object_sparse
#تعریف_کن GL_NV_حافظه_object_sparse 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLBUFFERPAGECOMMITMENTMEMNVPROC) (GLenum هدف, GLintptr جابه_جایی_2, GLsizeiptr اندازه, GLuint حافظه, GLuint64 mem_جابه_جایی, GLboolean commit);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPAGECOMMITMENTMEMNVPROC) (GLenum هدف, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLuint حافظه, GLuint64 جابه_جایی_2, GLboolean commit);
تعريفنوع فراغ (GL_APIENTRYP PFNGLNAMEDBUFFERPAGECOMMITMENTMEMNVPROC) (GLuint میانگیر_2, GLintptr جابه_جایی_2, GLsizeiptr اندازه, GLuint حافظه, GLuint64 mem_جابه_جایی, GLboolean commit);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTUREPAGECOMMITMENTMEMNVPROC) (GLuint texture, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLuint حافظه, GLuint64 جابه_جایی_2, GLboolean commit);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_میانگیر_صفحه_Commitment_Mem_NV (GLenum هدف, GLintptr جابه_جایی_2, GLsizeiptr اندازه, GLuint حافظه, GLuint64 mem_جابه_جایی, GLboolean commit);
GL_APICALL فراغ GL_APIENTRY gl_Tex_صفحه_Commitment_Mem_NV (GLenum هدف, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLuint حافظه, GLuint64 جابه_جایی_2, GLboolean commit);
GL_APICALL فراغ GL_APIENTRY gl_Named_میانگیر_صفحه_Commitment_Mem_NV (GLuint میانگیر_2, GLintptr جابه_جایی_2, GLsizeiptr اندازه, GLuint حافظه, GLuint64 mem_جابه_جایی, GLboolean commit);
GL_APICALL فراغ GL_APIENTRY gl_Texture_صفحه_Commitment_Mem_NV (GLuint texture, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLuint حافظه, GLuint64 جابه_جایی_2, GLboolean commit);
#پایان_اگر
#پایان_اگر /* GL_NV_memory_object_sparse */

#اگر_تعریف_نشده GL_NV_mesh_shader
#تعریف_کن GL_NV_mesh_shader 1
#تعریف_کن GL_MESH_SHADER_NV                 0x9559
#تعریف_کن GL_TASK_SHADER_NV                 0x955A
#تعریف_کن GL_MAX_MESH_یکنواخت_بلوکها_NV     0x8E60
#تعریف_کن GL_MAX_MESH_TEXTURE_IMAGE_UNITS_NV 0x8E61
#تعریف_کن GL_MAX_MESH_IMAGE_UNIFORMS_NV     0x8E62
#تعریف_کن GL_MAX_MESH_یکنواخت_COMPONENTS_NV 0x8E63
#تعریف_کن GL_MAX_MESH_ATOMIC_COUNTER_BUFFERS_NV 0x8E64
#تعریف_کن GL_MAX_MESH_ATOMIC_COUNTERS_NV    0x8E65
#تعریف_کن GL_MAX_MESH_SHADER_STORAGE_بلوکها_NV 0x8E66
#تعریف_کن GL_MAX_COMBINED_MESH_یکنواخت_COMPONENTS_NV 0x8E67
#تعریف_کن GL_MAX_TASK_یکنواخت_بلوکها_NV     0x8E68
#تعریف_کن GL_MAX_TASK_TEXTURE_IMAGE_UNITS_NV 0x8E69
#تعریف_کن GL_MAX_TASK_IMAGE_UNIFORMS_NV     0x8E6A
#تعریف_کن GL_MAX_TASK_یکنواخت_COMPONENTS_NV 0x8E6B
#تعریف_کن GL_MAX_TASK_ATOMIC_COUNTER_BUFFERS_NV 0x8E6C
#تعریف_کن GL_MAX_TASK_ATOMIC_COUNTERS_NV    0x8E6D
#تعریف_کن GL_MAX_TASK_SHADER_STORAGE_بلوکها_NV 0x8E6E
#تعریف_کن GL_MAX_COMBINED_TASK_یکنواخت_COMPONENTS_NV 0x8E6F
#تعریف_کن GL_MAX_MESH_WORK_گروه_INVOCATIONS_NV 0x95A2
#تعریف_کن GL_MAX_TASK_WORK_گروه_INVOCATIONS_NV 0x95A3
#تعریف_کن GL_MAX_MESH_مجموع_حافظه_اندازه_NV  0x9536
#تعریف_کن GL_MAX_TASK_مجموع_حافظه_اندازه_NV  0x9537
#تعریف_کن GL_MAX_MESH_OUTPUT_VERTICES_NV    0x9538
#تعریف_کن GL_MAX_MESH_OUTPUT_PRIMITIVES_NV  0x9539
#تعریف_کن GL_MAX_TASK_OUTPUT_شمار_NV       0x953A
#تعریف_کن GL_MAX_DRAW_MESH_TASKS_شمار_NV   0x953D
#تعریف_کن GL_MAX_MESH_VIEWS_NV              0x9557
#تعریف_کن GL_MESH_OUTPUT_در_هر_رأس_GRANULARITY_NV 0x92DF
#تعریف_کن GL_MESH_OUTPUT_در_هر_PRIMITIVE_GRANULARITY_NV 0x9543
#تعریف_کن GL_MAX_MESH_WORK_گروه_اندازه_NV    0x953B
#تعریف_کن GL_MAX_TASK_WORK_گروه_اندازه_NV    0x953C
#تعریف_کن GL_MESH_WORK_گروه_اندازه_NV        0x953E
#تعریف_کن GL_TASK_WORK_گروه_اندازه_NV        0x953F
#تعریف_کن GL_MESH_VERTICES_بیرون_NV           0x9579
#تعریف_کن GL_MESH_PRIMITIVES_بیرون_NV         0x957A
#تعریف_کن GL_MESH_OUTPUT_TYPE_NV            0x957B
#تعریف_کن GL_یکنواخت_بلوک_REFERENCED_BY_MESH_SHADER_NV 0x959C
#تعریف_کن GL_یکنواخت_بلوک_REFERENCED_BY_TASK_SHADER_NV 0x959D
#تعریف_کن GL_REFERENCED_BY_MESH_SHADER_NV   0x95A0
#تعریف_کن GL_REFERENCED_BY_TASK_SHADER_NV   0x95A1
#تعریف_کن GL_MESH_SHADER_بیت_NV             0x00000040
#تعریف_کن GL_TASK_SHADER_بیت_NV             0x00000080
#تعریف_کن GL_MESH_SUBROUTINE_NV             0x957C
#تعریف_کن GL_TASK_SUBROUTINE_NV             0x957D
#تعریف_کن GL_MESH_SUBROUTINE_یکنواخت_NV     0x957E
#تعریف_کن GL_TASK_SUBROUTINE_یکنواخت_NV     0x957F
#تعریف_کن GL_ATOMIC_COUNTER_میانگیر_REFERENCED_BY_MESH_SHADER_NV 0x959E
#تعریف_کن GL_ATOMIC_COUNTER_میانگیر_REFERENCED_BY_TASK_SHADER_NV 0x959F
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWMESHTASKSNVPROC) (GLuint اولی, GLuint شمار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWMESHTASKSINDIRECTNVPROC) (GLintptr غیرمستقیم);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWMESHTASKSINDIRECTNVPROC) (GLintptr غیرمستقیم, GLsizei drawcount, GLsizei stride);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTNVPROC) (GLintptr غیرمستقیم, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawMeshTasksNV (GLuint اولی, GLuint شمار);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Mesh_Tasks_غیرمستقیم_NV (GLintptr غیرمستقیم);
GL_APICALL فراغ GL_APIENTRY gl_Multi_Draw_Mesh_Tasks_غیرمستقیم_NV (GLintptr غیرمستقیم, GLsizei drawcount, GLsizei stride);
GL_APICALL فراغ GL_APIENTRY gl_Multi_Draw_Mesh_Tasks_غیرمستقیم_شمار_NV (GLintptr غیرمستقیم, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
#پایان_اگر
#پایان_اگر /* GL_NV_mesh_shader */

#اگر_تعریف_نشده GL_NV_non_مربع_matrices
#تعریف_کن GL_NV_non_مربع_matrices 1
#تعریف_کن GL_FLOAT_MAT2x3_NV                0x8B65
#تعریف_کن GL_FLOAT_MAT2x4_NV                0x8B66
#تعریف_کن GL_FLOAT_MAT3x2_NV                0x8B67
#تعریف_کن GL_FLOAT_MAT3x4_NV                0x8B68
#تعریف_کن GL_FLOAT_MAT4x2_NV                0x8B69
#تعریف_کن GL_FLOAT_MAT4x3_NV                0x8B6A
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX2X3FVNVPROC) (GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX3X2FVNVPROC) (GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX2X4FVNVPROC) (GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX4X2FVNVPROC) (GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX3X4FVNVPROC) (GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX4X3FVNVPROC) (GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_یکنواخت_Matrix2x3fv_NV (GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_یکنواخت_Matrix3x2fv_NV (GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_یکنواخت_Matrix2x4fv_NV (GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_یکنواخت_Matrix4x2fv_NV (GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_یکنواخت_Matrix3x4fv_NV (GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_یکنواخت_Matrix4x3fv_NV (GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
#پایان_اگر
#پایان_اگر /* GL_NV_non_square_matrices */

#اگر_تعریف_نشده GL_NV_pack_subimage
#تعریف_کن GL_NV_pack_subimage 1
#تعریف_کن GL_PACK_ردیف_درازی_NV             0x0D02
#تعریف_کن GL_PACK_SKIP_ردیفها_NV              0x0D03
#تعریف_کن GL_PACK_SKIP_PIXELS_NV            0x0D04
#پایان_اگر /* GL_NV_pack_subimage */

#اگر_تعریف_نشده GL_NV_مسیر_rendering
#تعریف_کن GL_NV_مسیر_rendering 1
تعريفنوع مزدوج GLdouble;
#تعریف_کن GL_مسیر_FORMAT_SVG_NV             0x9070
#تعریف_کن GL_مسیر_FORMAT_PS_NV              0x9071
#تعریف_کن GL_STANDARD_FONT_NAME_NV          0x9072
#تعریف_کن GL_SYSTEM_FONT_NAME_NV            0x9073
#تعریف_کن GL_FILE_NAME_NV                   0x9074
#تعریف_کن GL_مسیر_STROKE_عرض_NV           0x9075
#تعریف_کن GL_مسیر_انتها_CAPS_NV               0x9076
#تعریف_کن GL_مسیر_INITIAL_انتها_CAP_NV        0x9077
#تعریف_کن GL_مسیر_TERMINAL_انتها_CAP_NV       0x9078
#تعریف_کن GL_مسیر_JOIN_STYLE_NV             0x9079
#تعریف_کن GL_مسیر_MITER_حد_NV            0x907A
#تعریف_کن GL_مسیر_DASH_CAPS_NV              0x907B
#تعریف_کن GL_مسیر_INITIAL_DASH_CAP_NV       0x907C
#تعریف_کن GL_مسیر_TERMINAL_DASH_CAP_NV      0x907D
#تعریف_کن GL_مسیر_DASH_جابه_جایی_NV            0x907E
#تعریف_کن GL_مسیر_CLIENT_درازی_NV          0x907F
#تعریف_کن GL_مسیر_FILL_نما_NV              0x9080
#تعریف_کن GL_مسیر_FILL_ماسک_NV              0x9081
#تعریف_کن GL_مسیر_FILL_COVER_نما_NV        0x9082
#تعریف_کن GL_مسیر_STROKE_COVER_نما_NV      0x9083
#تعریف_کن GL_مسیر_STROKE_ماسک_NV            0x9084
#تعریف_کن GL_شمار_به_بالا_NV                    0x9088
#تعریف_کن GL_شمار_پایین_NV                  0x9089
#تعریف_کن GL_مسیر_OBJECT_BOUNDING_BOX_NV    0x908A
#تعریف_کن GL_CONVEX_HULL_NV                 0x908B
#تعریف_کن GL_BOUNDING_BOX_NV                0x908D
#تعریف_کن GL_TRANSLATE_X_NV                 0x908E
#تعریف_کن GL_TRANSLATE_Y_NV                 0x908F
#تعریف_کن GL_TRANSLATE_2D_NV                0x9090
#تعریف_کن GL_TRANSLATE_3D_NV                0x9091
#تعریف_کن GL_AFFINE_2D_NV                   0x9092
#تعریف_کن GL_AFFINE_3D_NV                   0x9094
#تعریف_کن GL_TRANSPOSE_AFFINE_2D_NV         0x9096
#تعریف_کن GL_TRANSPOSE_AFFINE_3D_NV         0x9098
#تعریف_کن GL_UTF8_NV                        0x909A
#تعریف_کن GL_UTF16_NV                       0x909B
#تعریف_کن GL_BOUNDING_BOX_از_BOUNDING_BOXES_NV 0x909C
#تعریف_کن GL_مسیر_COMMAND_شمار_NV          0x909D
#تعریف_کن GL_مسیر_COORD_شمار_NV            0x909E
#تعریف_کن GL_مسیر_DASH_ARRAY_شمار_NV       0x909F
#تعریف_کن GL_مسیر_COMPUTED_درازی_NV        0x90A0
#تعریف_کن GL_مسیر_FILL_BOUNDING_BOX_NV      0x90A1
#تعریف_کن GL_مسیر_STROKE_BOUNDING_BOX_NV    0x90A2
#تعریف_کن GL_مربع_NV                      0x90A3
#تعریف_کن GL_دور_NV                       0x90A4
#تعریف_کن GL_TRIANGULAR_NV                  0x90A5
#تعریف_کن GL_BEVEL_NV                       0x90A6
#تعریف_کن GL_MITER_REVERT_NV                0x90A7
#تعریف_کن GL_MITER_TRUNCATE_NV              0x90A8
#تعریف_کن GL_SKIP_MISSING_GLYPH_NV          0x90A9
#تعریف_کن GL_USE_MISSING_GLYPH_NV           0x90AA
#تعریف_کن GL_مسیر_ERROR_POSITION_NV         0x90AB
#تعریف_کن GL_ACCUM_ADJACENT_جفتها_NV        0x90AD
#تعریف_کن GL_ADJACENT_جفتها_NV              0x90AE
#تعریف_کن GL_اولی_مقصد_REST_NV               0x90AF
#تعریف_کن GL_مسیر_GEN_نما_NV               0x90B0
#تعریف_کن GL_مسیر_GEN_COEFF_NV              0x90B1
#تعریف_کن GL_مسیر_GEN_COMPONENTS_NV         0x90B3
#تعریف_کن GL_مسیر_STENCIL_FUNC_NV           0x90B7
#تعریف_کن GL_مسیر_STENCIL_REF_NV            0x90B8
#تعریف_کن GL_مسیر_STENCIL_مقدار_ماسک_NV     0x90B9
#تعریف_کن GL_مسیر_STENCIL_عمق_جابه_جایی_ضریب_NV 0x90BD
#تعریف_کن GL_مسیر_STENCIL_عمق_جابه_جایی_UNITS_NV 0x90BE
#تعریف_کن GL_مسیر_COVER_عمق_FUNC_NV       0x90BF
#تعریف_کن GL_مسیر_DASH_جابه_جایی_RESET_NV      0x90B4
#تعریف_کن GL_MOVE_مقصد_RESETS_NV              0x90B5
#تعریف_کن GL_MOVE_مقصد_CONTINUES_NV           0x90B6
#تعریف_کن GL_CLOSE_مسیر_NV                  0x00
#تعریف_کن GL_MOVE_مقصد_NV                     0x02
#تعریف_کن GL_RELATIVE_MOVE_مقصد_NV            0x03
#تعریف_کن GL_سطر_مقصد_NV                     0x04
#تعریف_کن GL_RELATIVE_سطر_مقصد_NV            0x05
#تعریف_کن GL_HORIZONTAL_سطر_مقصد_NV          0x06
#تعریف_کن GL_RELATIVE_HORIZONTAL_سطر_مقصد_NV 0x07
#تعریف_کن GL_VERTICAL_سطر_مقصد_NV            0x08
#تعریف_کن GL_RELATIVE_VERTICAL_سطر_مقصد_NV   0x09
#تعریف_کن GL_QUADRATIC_منحنی_مقصد_NV          0x0A
#تعریف_کن GL_RELATIVE_QUADRATIC_منحنی_مقصد_NV 0x0B
#تعریف_کن GL_CUBIC_منحنی_مقصد_NV              0x0C
#تعریف_کن GL_RELATIVE_CUBIC_منحنی_مقصد_NV     0x0D
#تعریف_کن GL_SMOOTH_QUADRATIC_منحنی_مقصد_NV   0x0E
#تعریف_کن GL_RELATIVE_SMOOTH_QUADRATIC_منحنی_مقصد_NV 0x0F
#تعریف_کن GL_SMOOTH_CUBIC_منحنی_مقصد_NV       0x10
#تعریف_کن GL_RELATIVE_SMOOTH_CUBIC_منحنی_مقصد_NV 0x11
#تعریف_کن GL_SMALL_CCW_ARC_مقصد_NV            0x12
#تعریف_کن GL_RELATIVE_SMALL_CCW_ARC_مقصد_NV   0x13
#تعریف_کن GL_SMALL_CW_ARC_مقصد_NV             0x14
#تعریف_کن GL_RELATIVE_SMALL_CW_ARC_مقصد_NV    0x15
#تعریف_کن GL_LARGE_CCW_ARC_مقصد_NV            0x16
#تعریف_کن GL_RELATIVE_LARGE_CCW_ARC_مقصد_NV   0x17
#تعریف_کن GL_LARGE_CW_ARC_مقصد_NV             0x18
#تعریف_کن GL_RELATIVE_LARGE_CW_ARC_مقصد_NV    0x19
#تعریف_کن GL_RESTART_مسیر_NV                0xF0
#تعریف_کن GL_DUP_اولی_CUBIC_منحنی_مقصد_NV    0xF2
#تعریف_کن GL_DUP_آخرین_CUBIC_منحنی_مقصد_NV     0xF4
#تعریف_کن GL_RECT_NV                        0xF6
#تعریف_کن GL_CIRCULAR_CCW_ARC_مقصد_NV         0xF8
#تعریف_کن GL_CIRCULAR_CW_ARC_مقصد_NV          0xFA
#تعریف_کن GL_CIRCULAR_TANGENT_ARC_مقصد_NV     0xFC
#تعریف_کن GL_ARC_مقصد_NV                      0xFE
#تعریف_کن GL_RELATIVE_ARC_مقصد_NV             0xFF
#تعریف_کن GL_BOLD_بیت_NV                    0x01
#تعریف_کن GL_ITALIC_بیت_NV                  0x02
#تعریف_کن GL_GLYPH_عرض_بیت_NV             0x01
#تعریف_کن GL_GLYPH_ارتفاع_بیت_NV            0x02
#تعریف_کن GL_GLYPH_HORIZONTAL_BEARING_X_بیت_NV 0x04
#تعریف_کن GL_GLYPH_HORIZONTAL_BEARING_Y_بیت_NV 0x08
#تعریف_کن GL_GLYPH_HORIZONTAL_BEARING_ADVANCE_بیت_NV 0x10
#تعریف_کن GL_GLYPH_VERTICAL_BEARING_X_بیت_NV 0x20
#تعریف_کن GL_GLYPH_VERTICAL_BEARING_Y_بیت_NV 0x40
#تعریف_کن GL_GLYPH_VERTICAL_BEARING_ADVANCE_بیت_NV 0x80
#تعریف_کن GL_GLYPH_HAS_KERNING_بیت_NV       0x100
#تعریف_کن GL_FONT_X_MIN_BOUNDS_بیت_NV       0x00010000
#تعریف_کن GL_FONT_Y_MIN_BOUNDS_بیت_NV       0x00020000
#تعریف_کن GL_FONT_X_MAX_BOUNDS_بیت_NV       0x00040000
#تعریف_کن GL_FONT_Y_MAX_BOUNDS_بیت_NV       0x00080000
#تعریف_کن GL_FONT_UNITS_در_هر_EM_بیت_NV       0x00100000
#تعریف_کن GL_FONT_ASCENDER_بیت_NV           0x00200000
#تعریف_کن GL_FONT_DESCENDER_بیت_NV          0x00400000
#تعریف_کن GL_FONT_ارتفاع_بیت_NV             0x00800000
#تعریف_کن GL_FONT_MAX_ADVANCE_عرض_بیت_NV  0x01000000
#تعریف_کن GL_FONT_MAX_ADVANCE_ارتفاع_بیت_NV 0x02000000
#تعریف_کن GL_FONT_UNDERLINE_POSITION_بیت_NV 0x04000000
#تعریف_کن GL_FONT_UNDERLINE_THICKNESS_بیت_NV 0x08000000
#تعریف_کن GL_FONT_HAS_KERNING_بیت_NV        0x10000000
#تعریف_کن GL_ROUNDED_RECT_NV                0xE8
#تعریف_کن GL_RELATIVE_ROUNDED_RECT_NV       0xE9
#تعریف_کن GL_ROUNDED_RECT2_NV               0xEA
#تعریف_کن GL_RELATIVE_ROUNDED_RECT2_NV      0xEB
#تعریف_کن GL_ROUNDED_RECT4_NV               0xEC
#تعریف_کن GL_RELATIVE_ROUNDED_RECT4_NV      0xED
#تعریف_کن GL_ROUNDED_RECT8_NV               0xEE
#تعریف_کن GL_RELATIVE_ROUNDED_RECT8_NV      0xEF
#تعریف_کن GL_RELATIVE_RECT_NV               0xF7
#تعریف_کن GL_FONT_GLYPHS_موجود_NV       0x9368
#تعریف_کن GL_FONT_هدف_UNAVAILABLE_NV     0x9369
#تعریف_کن GL_FONT_UNAVAILABLE_NV            0x936A
#تعریف_کن GL_FONT_UNINTELLIGIBLE_NV         0x936B
#تعریف_کن GL_CONIC_منحنی_مقصد_NV              0x1A
#تعریف_کن GL_RELATIVE_CONIC_منحنی_مقصد_NV     0x1B
#تعریف_کن GL_FONT_رقم_GLYPH_INDICES_بیت_NV  0x20000000
#تعریف_کن GL_STANDARD_FONT_FORMAT_NV        0x936C
#تعریف_کن GL_مسیر_PROJECTION_NV             0x1701
#تعریف_کن GL_مسیر_MODELVIEW_NV              0x1700
#تعریف_کن GL_مسیر_MODELVIEW_پشته_عمق_NV  0x0BA3
#تعریف_کن GL_مسیر_MODELVIEW_ماتریس_NV       0x0BA6
#تعریف_کن GL_مسیر_MAX_MODELVIEW_پشته_عمق_NV 0x0D36
#تعریف_کن GL_مسیر_TRANSPOSE_MODELVIEW_ماتریس_NV 0x84E3
#تعریف_کن GL_مسیر_PROJECTION_پشته_عمق_NV 0x0BA4
#تعریف_کن GL_مسیر_PROJECTION_ماتریس_NV      0x0BA7
#تعریف_کن GL_مسیر_MAX_PROJECTION_پشته_عمق_NV 0x0D38
#تعریف_کن GL_مسیر_TRANSPOSE_PROJECTION_ماتریس_NV 0x84E4
#تعریف_کن GL_FRAGMENT_درون_داد_NV              0x936D
تعريفنوع GLuint (GL_APIENTRYP PFNGLGENPATHSNVPROC) (GLsizei range);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEPATHSNVPROC) (GLuint مسیر, GLsizei range);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISPATHNVPROC) (GLuint مسیر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHCOMMANDSNVPROC) (GLuint مسیر, GLsizei رقم_Commands, ثابت GLubyte *commands, GLsizei رقم_Coords, GLenum coordType, ثابت فراغ *coords);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHCOORDSNVPROC) (GLuint مسیر, GLsizei رقم_Coords, GLenum coordType, ثابت فراغ *coords);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHSUBCOMMANDSNVPROC) (GLuint مسیر, GLsizei command_شروع, GLsizei commands_مقصد_Delete, GLsizei رقم_Commands, ثابت GLubyte *commands, GLsizei رقم_Coords, GLenum coordType, ثابت فراغ *coords);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHSUBCOORDSNVPROC) (GLuint مسیر, GLsizei coord_شروع, GLsizei رقم_Coords, GLenum coordType, ثابت فراغ *coords);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHSTRINGNVPROC) (GLuint مسیر, GLenum format, GLsizei درازی, ثابت فراغ *مسیر_String);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHGLYPHSNVPROC) (GLuint اولی_مسیر_Name, GLenum font_هدف, ثابت فراغ *fontName, GLbitfield fontStyle, GLsizei رقم_Glyphs, GLenum type, ثابت فراغ *charcodes, GLenum handleMissingGlyphs, GLuint مسیر_Parameter_Template, GLfloat emScale);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHGLYPHRANGENVPROC) (GLuint اولی_مسیر_Name, GLenum font_هدف, ثابت فراغ *fontName, GLbitfield fontStyle, GLuint اولی_Glyph, GLsizei رقم_Glyphs, GLenum handleMissingGlyphs, GLuint مسیر_Parameter_Template, GLfloat emScale);
تعريفنوع فراغ (GL_APIENTRYP PFNGLWEIGHTPATHSNVPROC) (GLuint نتیجه_مسیر, GLsizei رقم_Paths, ثابت GLuint *paths, ثابت GLfloat *weights);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYPATHNVPROC) (GLuint نتیجه_مسیر, GLuint src_مسیر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLINTERPOLATEPATHSNVPROC) (GLuint نتیجه_مسیر, GLuint مسیر_A, GLuint مسیر_B, GLfloat وزن);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTRANSFORMPATHNVPROC) (GLuint نتیجه_مسیر, GLuint src_مسیر, GLenum transformType, ثابت GLfloat *transform_مقادیر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHPARAMETERIVNVPROC) (GLuint مسیر, GLenum pname, ثابت GLint *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHPARAMETERINVPROC) (GLuint مسیر, GLenum pname, GLint مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHPARAMETERFVNVPROC) (GLuint مسیر, GLenum pname, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHPARAMETERFNVPROC) (GLuint مسیر, GLenum pname, GLfloat مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHDASHARRAYNVPROC) (GLuint مسیر, GLsizei dash_شمار, ثابت GLfloat *dashArray);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHSTENCILFUNCNVPROC) (GLenum func, GLint ref, GLuint ماسک);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHSTENCILDEPTHOFFSETNVPROC) (GLfloat ضریب, GLfloat units);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILFILLPATHNVPROC) (GLuint مسیر, GLenum fill_نما, GLuint ماسک);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILSTROKEPATHNVPROC) (GLuint مسیر, GLint reference, GLuint ماسک);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILFILLPATHINSTANCEDNVPROC) (GLsizei رقم_Paths, GLenum مسیر_Name_Type, ثابت فراغ *paths, GLuint مسیر_پایه, GLenum fill_نما, GLuint ماسک, GLenum transformType, ثابت GLfloat *transform_مقادیر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILSTROKEPATHINSTANCEDNVPROC) (GLsizei رقم_Paths, GLenum مسیر_Name_Type, ثابت فراغ *paths, GLuint مسیر_پایه, GLint reference, GLuint ماسک, GLenum transformType, ثابت GLfloat *transform_مقادیر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHCOVERDEPTHFUNCNVPROC) (GLenum func);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOVERFILLPATHNVPROC) (GLuint مسیر, GLenum cover_نما);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOVERSTROKEPATHNVPROC) (GLuint مسیر, GLenum cover_نما);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOVERFILLPATHINSTANCEDNVPROC) (GLsizei رقم_Paths, GLenum مسیر_Name_Type, ثابت فراغ *paths, GLuint مسیر_پایه, GLenum cover_نما, GLenum transformType, ثابت GLfloat *transform_مقادیر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOVERSTROKEPATHINSTANCEDNVPROC) (GLsizei رقم_Paths, GLenum مسیر_Name_Type, ثابت فراغ *paths, GLuint مسیر_پایه, GLenum cover_نما, GLenum transformType, ثابت GLfloat *transform_مقادیر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPATHPARAMETERIVNVPROC) (GLuint مسیر, GLenum pname, GLint *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPATHPARAMETERFVNVPROC) (GLuint مسیر, GLenum pname, GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPATHCOMMANDSNVPROC) (GLuint مسیر, GLubyte *commands);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPATHCOORDSNVPROC) (GLuint مسیر, GLfloat *coords);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPATHDASHARRAYNVPROC) (GLuint مسیر, GLfloat *dashArray);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPATHMETRICSNVPROC) (GLbitfield metric_Query_ماسک, GLsizei رقم_Paths, GLenum مسیر_Name_Type, ثابت فراغ *paths, GLuint مسیر_پایه, GLsizei stride, GLfloat *metrics);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPATHMETRICRANGENVPROC) (GLbitfield metric_Query_ماسک, GLuint اولی_مسیر_Name, GLsizei رقم_Paths, GLsizei stride, GLfloat *metrics);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPATHSPACINGNVPROC) (GLenum مسیر_List_نما, GLsizei رقم_Paths, GLenum مسیر_Name_Type, ثابت فراغ *paths, GLuint مسیر_پایه, GLfloat advanceScale, GLfloat kerningScale, GLenum transformType, GLfloat *returnedSpacing);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISPOINTINFILLPATHNVPROC) (GLuint مسیر, GLuint ماسک, GLfloat x, GLfloat y);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISPOINTINSTROKEPATHNVPROC) (GLuint مسیر, GLfloat x, GLfloat y);
تعريفنوع GLfloat (GL_APIENTRYP PFNGLGETPATHLENGTHNVPROC) (GLuint مسیر, GLsizei شروع_Segment, GLsizei رقم_Segments);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLPOINTALONGPATHNVPROC) (GLuint مسیر, GLsizei شروع_Segment, GLsizei رقم_Segments, GLfloat فاصله, GLfloat *x, GLfloat *y, GLfloat *tangentX, GLfloat *tangentY);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXLOAD3X2FNVPROC) (GLenum ماتریس_نما, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXLOAD3X3FNVPROC) (GLenum ماتریس_نما, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXLOADTRANSPOSE3X3FNVPROC) (GLenum ماتریس_نما, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXMULT3X2FNVPROC) (GLenum ماتریس_نما, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXMULT3X3FNVPROC) (GLenum ماتریس_نما, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXMULTTRANSPOSE3X3FNVPROC) (GLenum ماتریس_نما, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILTHENCOVERFILLPATHNVPROC) (GLuint مسیر, GLenum fill_نما, GLuint ماسک, GLenum cover_نما);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILTHENCOVERSTROKEPATHNVPROC) (GLuint مسیر, GLint reference, GLuint ماسک, GLenum cover_نما);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILTHENCOVERFILLPATHINSTANCEDNVPROC) (GLsizei رقم_Paths, GLenum مسیر_Name_Type, ثابت فراغ *paths, GLuint مسیر_پایه, GLenum fill_نما, GLuint ماسک, GLenum cover_نما, GLenum transformType, ثابت GLfloat *transform_مقادیر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILTHENCOVERSTROKEPATHINSTANCEDNVPROC) (GLsizei رقم_Paths, GLenum مسیر_Name_Type, ثابت فراغ *paths, GLuint مسیر_پایه, GLint reference, GLuint ماسک, GLenum cover_نما, GLenum transformType, ثابت GLfloat *transform_مقادیر);
تعريفنوع GLenum (GL_APIENTRYP PFNGLPATHGLYPHINDEXRANGENVPROC) (GLenum font_هدف, ثابت فراغ *fontName, GLbitfield fontStyle, GLuint مسیر_Parameter_Template, GLfloat emScale, GLuint *پایه_And_شمار);
تعريفنوع GLenum (GL_APIENTRYP PFNGLPATHGLYPHINDEXARRAYNVPROC) (GLuint اولی_مسیر_Name, GLenum font_هدف, ثابت فراغ *fontName, GLbitfield fontStyle, GLuint اولی_Glyph_شاخص, GLsizei رقم_Glyphs, GLuint مسیر_Parameter_Template, GLfloat emScale);
تعريفنوع GLenum (GL_APIENTRYP PFNGLPATHMEMORYGLYPHINDEXARRAYNVPROC) (GLuint اولی_مسیر_Name, GLenum font_هدف, GLsizeiptr font_اندازه, ثابت فراغ *font_داده, GLsizei face_شاخص, GLuint اولی_Glyph_شاخص, GLsizei رقم_Glyphs, GLuint مسیر_Parameter_Template, GLfloat emScale);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMPATHFRAGMENTINPUTGENNVPROC) (GLuint برنامه, GLint location, GLenum gen_نما, GLint components, ثابت GLfloat *coeffs);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMRESOURCEFVNVPROC) (GLuint برنامه, GLenum برنامه_Interface, GLuint شاخص, GLsizei prop_شمار, ثابت GLenum *props, GLsizei شمار, GLsizei *درازی, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXFRUSTUMEXTPROC) (GLenum نما, GLdouble چپ, GLdouble راست, GLdouble bottom, GLdouble بالاترین, GLdouble zNear, GLdouble zFar);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXLOADIDENTITYEXTPROC) (GLenum نما);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXLOADTRANSPOSEFEXTPROC) (GLenum نما, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXLOADTRANSPOSEDEXTPROC) (GLenum نما, ثابت GLdouble *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXLOADFEXTPROC) (GLenum نما, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXLOADDEXTPROC) (GLenum نما, ثابت GLdouble *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXMULTTRANSPOSEFEXTPROC) (GLenum نما, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXMULTTRANSPOSEDEXTPROC) (GLenum نما, ثابت GLdouble *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXMULTFEXTPROC) (GLenum نما, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXMULTDEXTPROC) (GLenum نما, ثابت GLdouble *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXORTHOEXTPROC) (GLenum نما, GLdouble چپ, GLdouble راست, GLdouble bottom, GLdouble بالاترین, GLdouble zNear, GLdouble zFar);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXPOPEXTPROC) (GLenum نما);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXPUSHEXTPROC) (GLenum نما);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXROTATEFEXTPROC) (GLenum نما, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXROTATEDEXTPROC) (GLenum نما, GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXSCALEFEXTPROC) (GLenum نما, GLfloat x, GLfloat y, GLfloat z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXSCALEDEXTPROC) (GLenum نما, GLdouble x, GLdouble y, GLdouble z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXTRANSLATEFEXTPROC) (GLenum نما, GLfloat x, GLfloat y, GLfloat z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXTRANSLATEDEXTPROC) (GLenum نما, GLdouble x, GLdouble y, GLdouble z);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL GLuint GL_APIENTRY glGenPathsNV (GLsizei range);
GL_APICALL فراغ GL_APIENTRY glDeletePathsNV (GLuint مسیر, GLsizei range);
GL_APICALL GLboolean GL_APIENTRY gl_Is_مسیر_NV (GLuint مسیر);
GL_APICALL فراغ GL_APIENTRY gl_مسیر_Commands_NV (GLuint مسیر, GLsizei رقم_Commands, ثابت GLubyte *commands, GLsizei رقم_Coords, GLenum coordType, ثابت فراغ *coords);
GL_APICALL فراغ GL_APIENTRY gl_مسیر_Coords_NV (GLuint مسیر, GLsizei رقم_Coords, GLenum coordType, ثابت فراغ *coords);
GL_APICALL فراغ GL_APIENTRY gl_مسیر_Sub_Commands_NV (GLuint مسیر, GLsizei command_شروع, GLsizei commands_مقصد_Delete, GLsizei رقم_Commands, ثابت GLubyte *commands, GLsizei رقم_Coords, GLenum coordType, ثابت فراغ *coords);
GL_APICALL فراغ GL_APIENTRY gl_مسیر_Sub_Coords_NV (GLuint مسیر, GLsizei coord_شروع, GLsizei رقم_Coords, GLenum coordType, ثابت فراغ *coords);
GL_APICALL فراغ GL_APIENTRY gl_مسیر_String_NV (GLuint مسیر, GLenum format, GLsizei درازی, ثابت فراغ *مسیر_String);
GL_APICALL فراغ GL_APIENTRY gl_مسیر_Glyphs_NV (GLuint اولی_مسیر_Name, GLenum font_هدف, ثابت فراغ *fontName, GLbitfield fontStyle, GLsizei رقم_Glyphs, GLenum type, ثابت فراغ *charcodes, GLenum handleMissingGlyphs, GLuint مسیر_Parameter_Template, GLfloat emScale);
GL_APICALL فراغ GL_APIENTRY gl_مسیر_Glyph_Range_NV (GLuint اولی_مسیر_Name, GLenum font_هدف, ثابت فراغ *fontName, GLbitfield fontStyle, GLuint اولی_Glyph, GLsizei رقم_Glyphs, GLenum handleMissingGlyphs, GLuint مسیر_Parameter_Template, GLfloat emScale);
GL_APICALL فراغ GL_APIENTRY gl_وزن_Paths_NV (GLuint نتیجه_مسیر, GLsizei رقم_Paths, ثابت GLuint *paths, ثابت GLfloat *weights);
GL_APICALL فراغ GL_APIENTRY gl_Copy_مسیر_NV (GLuint نتیجه_مسیر, GLuint src_مسیر);
GL_APICALL فراغ GL_APIENTRY glInterpolatePathsNV (GLuint نتیجه_مسیر, GLuint مسیر_A, GLuint مسیر_B, GLfloat وزن);
GL_APICALL فراغ GL_APIENTRY gl_Transform_مسیر_NV (GLuint نتیجه_مسیر, GLuint src_مسیر, GLenum transformType, ثابت GLfloat *transform_مقادیر);
GL_APICALL فراغ GL_APIENTRY gl_مسیر_Parameteriv_NV (GLuint مسیر, GLenum pname, ثابت GLint *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_مسیر_Parameteri_NV (GLuint مسیر, GLenum pname, GLint مقدار);
GL_APICALL فراغ GL_APIENTRY gl_مسیر_Parameterfv_NV (GLuint مسیر, GLenum pname, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_مسیر_Parameterf_NV (GLuint مسیر, GLenum pname, GLfloat مقدار);
GL_APICALL فراغ GL_APIENTRY gl_مسیر_Dash_Array_NV (GLuint مسیر, GLsizei dash_شمار, ثابت GLfloat *dashArray);
GL_APICALL فراغ GL_APIENTRY gl_مسیر_Stencil_Func_NV (GLenum func, GLint ref, GLuint ماسک);
GL_APICALL فراغ GL_APIENTRY gl_مسیر_Stencil_عمق_جابه_جایی_NV (GLfloat ضریب, GLfloat units);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_Fill_مسیر_NV (GLuint مسیر, GLenum fill_نما, GLuint ماسک);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_Stroke_مسیر_NV (GLuint مسیر, GLint reference, GLuint ماسک);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_Fill_مسیر_Instanced_NV (GLsizei رقم_Paths, GLenum مسیر_Name_Type, ثابت فراغ *paths, GLuint مسیر_پایه, GLenum fill_نما, GLuint ماسک, GLenum transformType, ثابت GLfloat *transform_مقادیر);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_Stroke_مسیر_Instanced_NV (GLsizei رقم_Paths, GLenum مسیر_Name_Type, ثابت فراغ *paths, GLuint مسیر_پایه, GLint reference, GLuint ماسک, GLenum transformType, ثابت GLfloat *transform_مقادیر);
GL_APICALL فراغ GL_APIENTRY gl_مسیر_Cover_عمق_Func_NV (GLenum func);
GL_APICALL فراغ GL_APIENTRY gl_Cover_Fill_مسیر_NV (GLuint مسیر, GLenum cover_نما);
GL_APICALL فراغ GL_APIENTRY gl_Cover_Stroke_مسیر_NV (GLuint مسیر, GLenum cover_نما);
GL_APICALL فراغ GL_APIENTRY gl_Cover_Fill_مسیر_Instanced_NV (GLsizei رقم_Paths, GLenum مسیر_Name_Type, ثابت فراغ *paths, GLuint مسیر_پایه, GLenum cover_نما, GLenum transformType, ثابت GLfloat *transform_مقادیر);
GL_APICALL فراغ GL_APIENTRY gl_Cover_Stroke_مسیر_Instanced_NV (GLsizei رقم_Paths, GLenum مسیر_Name_Type, ثابت فراغ *paths, GLuint مسیر_پایه, GLenum cover_نما, GLenum transformType, ثابت GLfloat *transform_مقادیر);
GL_APICALL فراغ GL_APIENTRY gl_Get_مسیر_Parameteriv_NV (GLuint مسیر, GLenum pname, GLint *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_Get_مسیر_Parameterfv_NV (GLuint مسیر, GLenum pname, GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_Get_مسیر_Commands_NV (GLuint مسیر, GLubyte *commands);
GL_APICALL فراغ GL_APIENTRY gl_Get_مسیر_Coords_NV (GLuint مسیر, GLfloat *coords);
GL_APICALL فراغ GL_APIENTRY gl_Get_مسیر_Dash_Array_NV (GLuint مسیر, GLfloat *dashArray);
GL_APICALL فراغ GL_APIENTRY gl_Get_مسیر_Metrics_NV (GLbitfield metric_Query_ماسک, GLsizei رقم_Paths, GLenum مسیر_Name_Type, ثابت فراغ *paths, GLuint مسیر_پایه, GLsizei stride, GLfloat *metrics);
GL_APICALL فراغ GL_APIENTRY gl_Get_مسیر_Metric_Range_NV (GLbitfield metric_Query_ماسک, GLuint اولی_مسیر_Name, GLsizei رقم_Paths, GLsizei stride, GLfloat *metrics);
GL_APICALL فراغ GL_APIENTRY gl_Get_مسیر_Spacing_NV (GLenum مسیر_List_نما, GLsizei رقم_Paths, GLenum مسیر_Name_Type, ثابت فراغ *paths, GLuint مسیر_پایه, GLfloat advanceScale, GLfloat kerningScale, GLenum transformType, GLfloat *returnedSpacing);
GL_APICALL GLboolean GL_APIENTRY gl_Is_نقطه_درون_Fill_مسیر_NV (GLuint مسیر, GLuint ماسک, GLfloat x, GLfloat y);
GL_APICALL GLboolean GL_APIENTRY gl_Is_نقطه_درون_Stroke_مسیر_NV (GLuint مسیر, GLfloat x, GLfloat y);
GL_APICALL GLfloat GL_APIENTRY gl_Get_مسیر_درازی_NV (GLuint مسیر, GLsizei شروع_Segment, GLsizei رقم_Segments);
GL_APICALL GLboolean GL_APIENTRY gl_نقطه_Along_مسیر_NV (GLuint مسیر, GLsizei شروع_Segment, GLsizei رقم_Segments, GLfloat فاصله, GLfloat *x, GLfloat *y, GLfloat *tangentX, GLfloat *tangentY);
GL_APICALL فراغ GL_APIENTRY gl_ماتریس_Load3x2f_NV (GLenum ماتریس_نما, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_ماتریس_Load3x3f_NV (GLenum ماتریس_نما, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_ماتریس_بارگیری_Transpose3x3f_NV (GLenum ماتریس_نما, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_ماتریس_Mult3x2f_NV (GLenum ماتریس_نما, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_ماتریس_Mult3x3f_NV (GLenum ماتریس_نما, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_ماتریس_Mult_Transpose3x3f_NV (GLenum ماتریس_نما, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_Then_Cover_Fill_مسیر_NV (GLuint مسیر, GLenum fill_نما, GLuint ماسک, GLenum cover_نما);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_Then_Cover_Stroke_مسیر_NV (GLuint مسیر, GLint reference, GLuint ماسک, GLenum cover_نما);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_Then_Cover_Fill_مسیر_Instanced_NV (GLsizei رقم_Paths, GLenum مسیر_Name_Type, ثابت فراغ *paths, GLuint مسیر_پایه, GLenum fill_نما, GLuint ماسک, GLenum cover_نما, GLenum transformType, ثابت GLfloat *transform_مقادیر);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_Then_Cover_Stroke_مسیر_Instanced_NV (GLsizei رقم_Paths, GLenum مسیر_Name_Type, ثابت فراغ *paths, GLuint مسیر_پایه, GLint reference, GLuint ماسک, GLenum cover_نما, GLenum transformType, ثابت GLfloat *transform_مقادیر);
GL_APICALL GLenum GL_APIENTRY gl_مسیر_Glyph_شاخص_Range_NV (GLenum font_هدف, ثابت فراغ *fontName, GLbitfield fontStyle, GLuint مسیر_Parameter_Template, GLfloat emScale, GLuint *پایه_And_شمار);
GL_APICALL GLenum GL_APIENTRY gl_مسیر_Glyph_شاخص_Array_NV (GLuint اولی_مسیر_Name, GLenum font_هدف, ثابت فراغ *fontName, GLbitfield fontStyle, GLuint اولی_Glyph_شاخص, GLsizei رقم_Glyphs, GLuint مسیر_Parameter_Template, GLfloat emScale);
GL_APICALL GLenum GL_APIENTRY gl_مسیر_حافظه_Glyph_شاخص_Array_NV (GLuint اولی_مسیر_Name, GLenum font_هدف, GLsizeiptr font_اندازه, ثابت فراغ *font_داده, GLsizei face_شاخص, GLuint اولی_Glyph_شاخص, GLsizei رقم_Glyphs, GLuint مسیر_Parameter_Template, GLfloat emScale);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_مسیر_Fragment_درون_داد_Gen_NV (GLuint برنامه, GLint location, GLenum gen_نما, GLint components, ثابت GLfloat *coeffs);
GL_APICALL فراغ GL_APIENTRY gl_Get_برنامه_Resourcefv_NV (GLuint برنامه, GLenum برنامه_Interface, GLuint شاخص, GLsizei prop_شمار, ثابت GLenum *props, GLsizei شمار, GLsizei *درازی, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY gl_ماتریس_Frustum_EXT (GLenum نما, GLdouble چپ, GLdouble راست, GLdouble bottom, GLdouble بالاترین, GLdouble zNear, GLdouble zFar);
GL_APICALL فراغ GL_APIENTRY gl_ماتریس_بارگیری_عنصر_خنثی_EXT (GLenum نما);
GL_APICALL فراغ GL_APIENTRY gl_ماتریس_بارگیری_Transposef_EXT (GLenum نما, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_ماتریس_بارگیری_Transposed_EXT (GLenum نما, ثابت GLdouble *m);
GL_APICALL فراغ GL_APIENTRY gl_ماتریس_Loadf_EXT (GLenum نما, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_ماتریس_Loadd_EXT (GLenum نما, ثابت GLdouble *m);
GL_APICALL فراغ GL_APIENTRY gl_ماتریس_Mult_Transposef_EXT (GLenum نما, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_ماتریس_Mult_Transposed_EXT (GLenum نما, ثابت GLdouble *m);
GL_APICALL فراغ GL_APIENTRY gl_ماتریس_Multf_EXT (GLenum نما, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_ماتریس_Multd_EXT (GLenum نما, ثابت GLdouble *m);
GL_APICALL فراغ GL_APIENTRY gl_ماتریس_Ortho_EXT (GLenum نما, GLdouble چپ, GLdouble راست, GLdouble bottom, GLdouble بالاترین, GLdouble zNear, GLdouble zFar);
GL_APICALL فراغ GL_APIENTRY gl_ماتریس_برداشت_EXT (GLenum نما);
GL_APICALL فراغ GL_APIENTRY gl_ماتریس_افزودن_EXT (GLenum نما);
GL_APICALL فراغ GL_APIENTRY gl_ماتریس_Rotatef_EXT (GLenum نما, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL فراغ GL_APIENTRY gl_ماتریس_Rotated_EXT (GLenum نما, GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
GL_APICALL فراغ GL_APIENTRY gl_ماتریس_Scalef_EXT (GLenum نما, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL فراغ GL_APIENTRY gl_ماتریس_Scaled_EXT (GLenum نما, GLdouble x, GLdouble y, GLdouble z);
GL_APICALL فراغ GL_APIENTRY gl_ماتریس_Translatef_EXT (GLenum نما, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL فراغ GL_APIENTRY gl_ماتریس_Translated_EXT (GLenum نما, GLdouble x, GLdouble y, GLdouble z);
#پایان_اگر
#پایان_اگر /* GL_NV_path_rendering */

#اگر_تعریف_نشده GL_NV_مسیر_rendering_shared_یال
#تعریف_کن GL_NV_مسیر_rendering_shared_یال 1
#تعریف_کن GL_SHARED_یال_NV                 0xC0
#پایان_اگر /* GL_NV_path_rendering_shared_edge */

#اگر_تعریف_نشده GL_NV_pixel_میانگیر_object
#تعریف_کن GL_NV_pixel_میانگیر_object 1
#تعریف_کن GL_PIXEL_PACK_میانگیر_NV           0x88EB
#تعریف_کن GL_PIXEL_UNPACK_میانگیر_NV         0x88EC
#تعریف_کن GL_PIXEL_PACK_میانگیر_BINDING_NV   0x88ED
#تعریف_کن GL_PIXEL_UNPACK_میانگیر_BINDING_NV 0x88EF
#پایان_اگر /* GL_NV_pixel_buffer_object */

#اگر_تعریف_نشده GL_NV_polygon_نما
#تعریف_کن GL_NV_polygon_نما 1
#تعریف_کن GL_POLYGON_نما_NV                0x0B40
#تعریف_کن GL_POLYGON_جابه_جایی_نقطه_NV        0x2A01
#تعریف_کن GL_POLYGON_جابه_جایی_سطر_NV         0x2A02
#تعریف_کن GL_نقطه_NV                       0x1B00
#تعریف_کن GL_سطر_NV                        0x1B01
#تعریف_کن GL_FILL_NV                        0x1B02
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOLYGONMODENVPROC) (GLenum face, GLenum نما);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Polygon_نما_NV (GLenum face, GLenum نما);
#پایان_اگر
#پایان_اگر /* GL_NV_polygon_mode */

#اگر_تعریف_نشده GL_NV_primitive_shading_نرخ
#تعریف_کن GL_NV_primitive_shading_نرخ 1
#تعریف_کن GL_SHADING_نرخ_IMAGE_در_هر_PRIMITIVE_NV 0x95B1
#تعریف_کن GL_SHADING_نرخ_IMAGE_PALETTE_شمار_NV 0x95B2
#پایان_اگر /* GL_NV_primitive_shading_rate */

#اگر_تعریف_نشده GL_NV_read_میانگیر
#تعریف_کن GL_NV_read_میانگیر 1
#تعریف_کن GL_READ_میانگیر_NV                 0x0C02
تعريفنوع فراغ (GL_APIENTRYP PFNGLREADBUFFERNVPROC) (GLenum نما);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Read_میانگیر_NV (GLenum نما);
#پایان_اگر
#پایان_اگر /* GL_NV_read_buffer */

#اگر_تعریف_نشده GL_NV_read_میانگیر_front
#تعریف_کن GL_NV_read_میانگیر_front 1
#پایان_اگر /* GL_NV_read_buffer_front */

#اگر_تعریف_نشده GL_NV_read_عمق
#تعریف_کن GL_NV_read_عمق 1
#پایان_اگر /* GL_NV_read_depth */

#اگر_تعریف_نشده GL_NV_read_عمق_stencil
#تعریف_کن GL_NV_read_عمق_stencil 1
#پایان_اگر /* GL_NV_read_depth_stencil */

#اگر_تعریف_نشده GL_NV_read_stencil
#تعریف_کن GL_NV_read_stencil 1
#پایان_اگر /* GL_NV_read_stencil */

#اگر_تعریف_نشده GL_NV_representative_fragment_test
#تعریف_کن GL_NV_representative_fragment_test 1
#تعریف_کن GL_REPRESENTATIVE_FRAGMENT_TEST_NV 0x937F
#پایان_اگر /* GL_NV_representative_fragment_test */

#اگر_تعریف_نشده GL_NV_sRGB_formats
#تعریف_کن GL_NV_sRGB_formats 1
#تعریف_کن GL_SLUMINANCE_NV                  0x8C46
#تعریف_کن GL_SLUMINANCE_ALPHA_NV            0x8C44
#تعریف_کن GL_SRGB8_NV                       0x8C41
#تعریف_کن GL_SLUMINANCE8_NV                 0x8C47
#تعریف_کن GL_SLUMINANCE8_ALPHA8_NV          0x8C45
#تعریف_کن GL_COMPRESSED_SRGB_S3TC_DXT1_NV   0x8C4C
#تعریف_کن GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_NV 0x8C4D
#تعریف_کن GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_NV 0x8C4E
#تعریف_کن GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_NV 0x8C4F
#تعریف_کن GL_ETC1_SRGB8_NV                  0x88EE
#پایان_اگر /* GL_NV_sRGB_formats */

#اگر_تعریف_نشده GL_NV_sample_locations
#تعریف_کن GL_NV_sample_locations 1
#تعریف_کن GL_SAMPLE_LOCATION_SUBPIXEL_بیتها_NV 0x933D
#تعریف_کن GL_SAMPLE_LOCATION_PIXEL_GRID_عرض_NV 0x933E
#تعریف_کن GL_SAMPLE_LOCATION_PIXEL_GRID_ارتفاع_NV 0x933F
#تعریف_کن GL_PROGRAMMABLE_SAMPLE_LOCATION_جدول_اندازه_NV 0x9340
#تعریف_کن GL_SAMPLE_LOCATION_NV             0x8E50
#تعریف_کن GL_PROGRAMMABLE_SAMPLE_LOCATION_NV 0x9341
#تعریف_کن GL_FRAMEBUFFER_PROGRAMMABLE_SAMPLE_LOCATIONS_NV 0x9342
#تعریف_کن GL_FRAMEBUFFER_SAMPLE_LOCATION_PIXEL_GRID_NV 0x9343
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERSAMPLELOCATIONSFVNVPROC) (GLenum هدف, GLuint شروع, GLsizei شمار, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVNVPROC) (GLuint framebuffer, GLuint شروع, GLsizei شمار, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRESOLVEDEPTHVALUESNVPROC) (فراغ);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferSampleLocationsfvNV (GLenum هدف, GLuint شروع, GLsizei شمار, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY glNamedFramebufferSampleLocationsfvNV (GLuint framebuffer, GLuint شروع, GLsizei شمار, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY gl_Resolve_عمق_مقادیر_NV (فراغ);
#پایان_اگر
#پایان_اگر /* GL_NV_sample_locations */

#اگر_تعریف_نشده GL_NV_sample_ماسک_override_coverage
#تعریف_کن GL_NV_sample_ماسک_override_coverage 1
#پایان_اگر /* GL_NV_sample_mask_override_coverage */

#اگر_تعریف_نشده GL_NV_scissor_exclusive
#تعریف_کن GL_NV_scissor_exclusive 1
#تعریف_کن GL_SCISSOR_TEST_EXCLUSIVE_NV      0x9555
#تعریف_کن GL_SCISSOR_BOX_EXCLUSIVE_NV       0x9556
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSOREXCLUSIVENVPROC) (GLint x, GLint y, GLsizei عرض, GLsizei ارتفاع);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSOREXCLUSIVEARRAYVNVPROC) (GLuint اولی, GLsizei شمار, ثابت GLint *v);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glScissorExclusiveNV (GLint x, GLint y, GLsizei عرض, GLsizei ارتفاع);
GL_APICALL فراغ GL_APIENTRY glScissorExclusiveArrayvNV (GLuint اولی, GLsizei شمار, ثابت GLint *v);
#پایان_اگر
#پایان_اگر /* GL_NV_scissor_exclusive */

#اگر_تعریف_نشده GL_NV_shader_atomic_fp16_وکتور
#تعریف_کن GL_NV_shader_atomic_fp16_وکتور 1
#پایان_اگر /* GL_NV_shader_atomic_fp16_vector */

#اگر_تعریف_نشده GL_NV_shader_noperspective_interpolation
#تعریف_کن GL_NV_shader_noperspective_interpolation 1
#پایان_اگر /* GL_NV_shader_noperspective_interpolation */

#اگر_تعریف_نشده GL_NV_shader_subgroup_partitioned
#تعریف_کن GL_NV_shader_subgroup_partitioned 1
#تعریف_کن GL_SUBGROUP_FEATURE_PARTITIONED_بیت_NV 0x00000100
#پایان_اگر /* GL_NV_shader_subgroup_partitioned */

#اگر_تعریف_نشده GL_NV_shader_texture_footprint
#تعریف_کن GL_NV_shader_texture_footprint 1
#پایان_اگر /* GL_NV_shader_texture_footprint */

#اگر_تعریف_نشده GL_NV_shading_نرخ_image
#تعریف_کن GL_NV_shading_نرخ_image 1
#تعریف_کن GL_SHADING_نرخ_IMAGE_NV          0x9563
#تعریف_کن GL_SHADING_نرخ_NO_INVOCATIONS_NV 0x9564
#تعریف_کن GL_SHADING_نرخ_1_INVOCATION_در_هر_PIXEL_NV 0x9565
#تعریف_کن GL_SHADING_نرخ_1_INVOCATION_در_هر_1_X2_PIXELS_NV 0x9566
#تعریف_کن GL_SHADING_نرخ_1_INVOCATION_در_هر_2_X1_PIXELS_NV 0x9567
#تعریف_کن GL_SHADING_نرخ_1_INVOCATION_در_هر_2_X2_PIXELS_NV 0x9568
#تعریف_کن GL_SHADING_نرخ_1_INVOCATION_در_هر_2_X4_PIXELS_NV 0x9569
#تعریف_کن GL_SHADING_نرخ_1_INVOCATION_در_هر_4_X2_PIXELS_NV 0x956A
#تعریف_کن GL_SHADING_نرخ_1_INVOCATION_در_هر_4_X4_PIXELS_NV 0x956B
#تعریف_کن GL_SHADING_نرخ_2_INVOCATIONS_در_هر_PIXEL_NV 0x956C
#تعریف_کن GL_SHADING_نرخ_4_INVOCATIONS_در_هر_PIXEL_NV 0x956D
#تعریف_کن GL_SHADING_نرخ_8_INVOCATIONS_در_هر_PIXEL_NV 0x956E
#تعریف_کن GL_SHADING_نرخ_16_INVOCATIONS_در_هر_PIXEL_NV 0x956F
#تعریف_کن GL_SHADING_نرخ_IMAGE_BINDING_NV  0x955B
#تعریف_کن GL_SHADING_نرخ_IMAGE_TEXEL_عرض_NV 0x955C
#تعریف_کن GL_SHADING_نرخ_IMAGE_TEXEL_ارتفاع_NV 0x955D
#تعریف_کن GL_SHADING_نرخ_IMAGE_PALETTE_اندازه_NV 0x955E
#تعریف_کن GL_MAX_COARSE_FRAGMENT_SAMPLES_NV 0x955F
#تعریف_کن GL_SHADING_نرخ_SAMPLE_ترتیب_DEFAULT_NV 0x95AE
#تعریف_کن GL_SHADING_نرخ_SAMPLE_ترتیب_PIXEL_MAJOR_NV 0x95AF
#تعریف_کن GL_SHADING_نرخ_SAMPLE_ترتیب_SAMPLE_MAJOR_NV 0x95B0
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDSHADINGRATEIMAGENVPROC) (GLuint texture);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSHADINGRATEIMAGEPALETTENVPROC) (GLuint viewport, GLuint مدخل, GLenum *نرخ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSHADINGRATESAMPLELOCATIONIVNVPROC) (GLenum نرخ, GLuint samples, GLuint شاخص, GLint *location);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADINGRATEIMAGEBARRIERNVPROC) (GLboolean synchronize);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADINGRATEIMAGEPALETTENVPROC) (GLuint viewport, GLuint اولی, GLsizei شمار, ثابت GLenum *rates);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADINGRATESAMPLEORDERNVPROC) (GLenum ترتیب);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADINGRATESAMPLEORDERCUSTOMNVPROC) (GLenum نرخ, GLuint samples, ثابت GLint *locations);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Bind_Shading_نرخ_Image_NV (GLuint texture);
GL_APICALL فراغ GL_APIENTRY gl_Get_Shading_نرخ_Image_Palette_NV (GLuint viewport, GLuint مدخل, GLenum *نرخ);
GL_APICALL فراغ GL_APIENTRY gl_Get_Shading_نرخ_Sample_Locationiv_NV (GLenum نرخ, GLuint samples, GLuint شاخص, GLint *location);
GL_APICALL فراغ GL_APIENTRY gl_Shading_نرخ_Image_Barrier_NV (GLboolean synchronize);
GL_APICALL فراغ GL_APIENTRY gl_Shading_نرخ_Image_Palette_NV (GLuint viewport, GLuint اولی, GLsizei شمار, ثابت GLenum *rates);
GL_APICALL فراغ GL_APIENTRY gl_Shading_نرخ_Sample_ترتیب_NV (GLenum ترتیب);
GL_APICALL فراغ GL_APIENTRY gl_Shading_نرخ_Sample_ترتیب_Custom_NV (GLenum نرخ, GLuint samples, ثابت GLint *locations);
#پایان_اگر
#پایان_اگر /* GL_NV_shading_rate_image */

#اگر_تعریف_نشده GL_NV_shadow_samplers_array
#تعریف_کن GL_NV_shadow_samplers_array 1
#تعریف_کن GL_SAMPLER_2D_ARRAY_SHADOW_NV     0x8DC4
#پایان_اگر /* GL_NV_shadow_samplers_array */

#اگر_تعریف_نشده GL_NV_shadow_samplers_cube
#تعریف_کن GL_NV_shadow_samplers_cube 1
#تعریف_کن GL_SAMPLER_CUBE_SHADOW_NV         0x8DC5
#پایان_اگر /* GL_NV_shadow_samplers_cube */

#اگر_تعریف_نشده GL_NV_stereo_view_rendering
#تعریف_کن GL_NV_stereo_view_rendering 1
#پایان_اگر /* GL_NV_stereo_view_rendering */

#اگر_تعریف_نشده GL_NV_texture_barrier
#تعریف_کن GL_NV_texture_barrier 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTUREBARRIERNVPROC) (فراغ);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTextureBarrierNV (فراغ);
#پایان_اگر
#پایان_اگر /* GL_NV_texture_barrier */

#اگر_تعریف_نشده GL_NV_texture_border_clamp
#تعریف_کن GL_NV_texture_border_clamp 1
#تعریف_کن GL_TEXTURE_BORDER_COLOR_NV        0x1004
#تعریف_کن GL_CLAMP_مقصد_BORDER_NV             0x812D
#پایان_اگر /* GL_NV_texture_border_clamp */

#اگر_تعریف_نشده GL_NV_texture_compression_s3tc_update
#تعریف_کن GL_NV_texture_compression_s3tc_update 1
#پایان_اگر /* GL_NV_texture_compression_s3tc_update */

#اگر_تعریف_نشده GL_NV_texture_npot_2D_mipmap
#تعریف_کن GL_NV_texture_npot_2D_mipmap 1
#پایان_اگر /* GL_NV_texture_npot_2D_mipmap */

#اگر_تعریف_نشده GL_NV_timeline_semaphore
#تعریف_کن GL_NV_timeline_semaphore 1
#تعریف_کن GL_TIMELINE_SEMAPHORE_مقدار_NV    0x9595
#تعریف_کن GL_SEMAPHORE_TYPE_NV              0x95B3
#تعریف_کن GL_SEMAPHORE_TYPE_دودویی_NV       0x95B4
#تعریف_کن GL_SEMAPHORE_TYPE_TIMELINE_NV     0x95B5
#تعریف_کن GL_MAX_TIMELINE_SEMAPHORE_مقدار_DIFFERENCE_NV 0x95B6
تعريفنوع فراغ (GL_APIENTRYP PFNGLCREATESEMAPHORESNVPROC) (GLsizei n, GLuint *semaphores);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSEMAPHOREPARAMETERIVNVPROC) (GLuint semaphore, GLenum pname, ثابت GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSEMAPHOREPARAMETERIVNVPROC) (GLuint semaphore, GLenum pname, GLint *params);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glCreateSemaphoresNV (GLsizei n, GLuint *semaphores);
GL_APICALL فراغ GL_APIENTRY glSemaphoreParameterivNV (GLuint semaphore, GLenum pname, ثابت GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetSemaphoreParameterivNV (GLuint semaphore, GLenum pname, GLint *params);
#پایان_اگر
#پایان_اگر /* GL_NV_timeline_semaphore */

#اگر_تعریف_نشده GL_NV_viewport_array
#تعریف_کن GL_NV_viewport_array 1
#تعریف_کن GL_MAX_VIEWPORTS_NV               0x825B
#تعریف_کن GL_VIEWPORT_SUBPIXEL_بیتها_NV      0x825C
#تعریف_کن GL_VIEWPORT_BOUNDS_RANGE_NV       0x825D
#تعریف_کن GL_VIEWPORT_شاخص_PROVOKING_رأس_NV 0x825F
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTARRAYVNVPROC) (GLuint اولی, GLsizei شمار, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTINDEXEDFNVPROC) (GLuint شاخص, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTINDEXEDFVNVPROC) (GLuint شاخص, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSORARRAYVNVPROC) (GLuint اولی, GLsizei شمار, ثابت GLint *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSORINDEXEDNVPROC) (GLuint شاخص, GLint چپ, GLint bottom, GLsizei عرض, GLsizei ارتفاع);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSORINDEXEDVNVPROC) (GLuint شاخص, ثابت GLint *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHRANGEARRAYFVNVPROC) (GLuint اولی, GLsizei شمار, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHRANGEINDEXEDFNVPROC) (GLuint شاخص, GLfloat n, GLfloat f);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFLOATI_VNVPROC) (GLenum هدف, GLuint شاخص, GLfloat *داده);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENABLEINVPROC) (GLenum هدف, GLuint شاخص);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISABLEINVPROC) (GLenum هدف, GLuint شاخص);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISENABLEDINVPROC) (GLenum هدف, GLuint شاخص);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glViewportArrayvNV (GLuint اولی, GLsizei شمار, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY glViewportIndexedfNV (GLuint شاخص, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
GL_APICALL فراغ GL_APIENTRY glViewportIndexedfvNV (GLuint شاخص, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY glScissorArrayvNV (GLuint اولی, GLsizei شمار, ثابت GLint *v);
GL_APICALL فراغ GL_APIENTRY gl_Scissor_نمایهای_NV (GLuint شاخص, GLint چپ, GLint bottom, GLsizei عرض, GLsizei ارتفاع);
GL_APICALL فراغ GL_APIENTRY glScissorIndexedvNV (GLuint شاخص, ثابت GLint *v);
GL_APICALL فراغ GL_APIENTRY gl_عمق_Range_Arrayfv_NV (GLuint اولی, GLsizei شمار, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY gl_عمق_Range_Indexedf_NV (GLuint شاخص, GLfloat n, GLfloat f);
GL_APICALL فراغ GL_APIENTRY glGetFloati_vNV (GLenum هدف, GLuint شاخص, GLfloat *داده);
GL_APICALL فراغ GL_APIENTRY glEnableiNV (GLenum هدف, GLuint شاخص);
GL_APICALL فراغ GL_APIENTRY glDisableiNV (GLenum هدف, GLuint شاخص);
GL_APICALL GLboolean GL_APIENTRY glIsEnablediNV (GLenum هدف, GLuint شاخص);
#پایان_اگر
#پایان_اگر /* GL_NV_viewport_array */

#اگر_تعریف_نشده GL_NV_viewport_array2
#تعریف_کن GL_NV_viewport_array2 1
#پایان_اگر /* GL_NV_viewport_array2 */

#اگر_تعریف_نشده GL_NV_viewport_swizzle
#تعریف_کن GL_NV_viewport_swizzle 1
#تعریف_کن GL_VIEWPORT_SWIZZLE_مثبت_X_NV 0x9350
#تعریف_کن GL_VIEWPORT_SWIZZLE_NEGATIVE_X_NV 0x9351
#تعریف_کن GL_VIEWPORT_SWIZZLE_مثبت_Y_NV 0x9352
#تعریف_کن GL_VIEWPORT_SWIZZLE_NEGATIVE_Y_NV 0x9353
#تعریف_کن GL_VIEWPORT_SWIZZLE_مثبت_Z_NV 0x9354
#تعریف_کن GL_VIEWPORT_SWIZZLE_NEGATIVE_Z_NV 0x9355
#تعریف_کن GL_VIEWPORT_SWIZZLE_مثبت_W_NV 0x9356
#تعریف_کن GL_VIEWPORT_SWIZZLE_NEGATIVE_W_NV 0x9357
#تعریف_کن GL_VIEWPORT_SWIZZLE_X_NV          0x9358
#تعریف_کن GL_VIEWPORT_SWIZZLE_Y_NV          0x9359
#تعریف_کن GL_VIEWPORT_SWIZZLE_Z_NV          0x935A
#تعریف_کن GL_VIEWPORT_SWIZZLE_W_NV          0x935B
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTSWIZZLENVPROC) (GLuint شاخص, GLenum swizzlex, GLenum swizzley, GLenum swizzlez, GLenum swizzlew);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glViewportSwizzleNV (GLuint شاخص, GLenum swizzlex, GLenum swizzley, GLenum swizzlez, GLenum swizzlew);
#پایان_اگر
#پایان_اگر /* GL_NV_viewport_swizzle */

#اگر_تعریف_نشده GL_OVR_multiview
#تعریف_کن GL_OVR_multiview 1
#تعریف_کن GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_رقم_VIEWS_OVR 0x9630
#تعریف_کن GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_پایه_VIEW_شاخص_OVR 0x9632
#تعریف_کن GL_MAX_VIEWS_OVR                  0x9631
#تعریف_کن GL_FRAMEBUFFER_INCOMPLETE_VIEW_TARGETS_OVR 0x9633
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREMULTIVIEWOVRPROC) (GLenum هدف, GLenum attachment, GLuint texture, GLint level, GLint پایه_View_شاخص, GLsizei رقم_Views_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLNAMEDFRAMEBUFFERTEXTUREMULTIVIEWOVRPROC) (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint پایه_View_شاخص, GLsizei رقم_Views_2);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferTextureMultiviewOVR (GLenum هدف, GLenum attachment, GLuint texture, GLint level, GLint پایه_View_شاخص, GLsizei رقم_Views_2);
GL_APICALL فراغ GL_APIENTRY glNamedFramebufferTextureMultiviewOVR (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint پایه_View_شاخص, GLsizei رقم_Views_2);
#پایان_اگر
#پایان_اگر /* GL_OVR_multiview */

#اگر_تعریف_نشده GL_OVR_multiview2
#تعریف_کن GL_OVR_multiview2 1
#پایان_اگر /* GL_OVR_multiview2 */

#اگر_تعریف_نشده GL_OVR_multiview_multisampled_render_مقصد_texture
#تعریف_کن GL_OVR_multiview_multisampled_render_مقصد_texture 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREMULTISAMPLEMULTIVIEWOVRPROC) (GLenum هدف, GLenum attachment, GLuint texture, GLint level, GLsizei samples, GLint پایه_View_شاخص, GLsizei رقم_Views_2);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferTextureMultisampleMultiviewOVR (GLenum هدف, GLenum attachment, GLuint texture, GLint level, GLsizei samples, GLint پایه_View_شاخص, GLsizei رقم_Views_2);
#پایان_اگر
#پایان_اگر /* GL_OVR_multiview_multisampled_render_to_texture */

#اگر_تعریف_نشده GL_QCOM_YUV_texture_gather
#تعریف_کن GL_QCOM_YUV_texture_gather 1
#پایان_اگر /* GL_QCOM_YUV_texture_gather */

#اگر_تعریف_نشده GL_QCOM_alpha_test
#تعریف_کن GL_QCOM_alpha_test 1
#تعریف_کن GL_ALPHA_TEST_QCOM                0x0BC0
#تعریف_کن GL_ALPHA_TEST_FUNC_QCOM           0x0BC1
#تعریف_کن GL_ALPHA_TEST_REF_QCOM            0x0BC2
تعريفنوع فراغ (GL_APIENTRYP PFNGLALPHAFUNCQCOMPROC) (GLenum func, GLclampf ref);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glAlphaFuncQCOM (GLenum func, GLclampf ref);
#پایان_اگر
#پایان_اگر /* GL_QCOM_alpha_test */

#اگر_تعریف_نشده GL_QCOM_binning_control
#تعریف_کن GL_QCOM_binning_control 1
#تعریف_کن GL_BINNING_CONTROL_HINT_QCOM      0x8FB0
#تعریف_کن GL_CPU_OPTIMIZED_QCOM             0x8FB1
#تعریف_کن GL_GPU_OPTIMIZED_QCOM             0x8FB2
#تعریف_کن GL_RENDER_مستقیم_مقصد_FRAMEBUFFER_QCOM 0x8FB3
#پایان_اگر /* GL_QCOM_binning_control */

#اگر_تعریف_نشده GL_QCOM_driver_control
#تعریف_کن GL_QCOM_driver_control 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETDRIVERCONTROLSQCOMPROC) (GLint *رقم, GLsizei اندازه, GLuint *driverControls);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETDRIVERCONTROLSTRINGQCOMPROC) (GLuint driverControl, GLsizei buf_اندازه, GLsizei *درازی, GLchar *driverControlString);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glGetDriverControlsQCOM (GLint *رقم, GLsizei اندازه, GLuint *driverControls);
GL_APICALL فراغ GL_APIENTRY glGetDriverControlStringQCOM (GLuint driverControl, GLsizei buf_اندازه, GLsizei *درازی, GLchar *driverControlString);
GL_APICALL فراغ GL_APIENTRY glEnableDriverControlQCOM (GLuint driverControl);
GL_APICALL فراغ GL_APIENTRY glDisableDriverControlQCOM (GLuint driverControl);
#پایان_اگر
#پایان_اگر /* GL_QCOM_driver_control */

#اگر_تعریف_نشده GL_QCOM_extended_get
#تعریف_کن GL_QCOM_extended_get 1
#تعریف_کن GL_TEXTURE_عرض_QCOM             0x8BD2
#تعریف_کن GL_TEXTURE_ارتفاع_QCOM            0x8BD3
#تعریف_کن GL_TEXTURE_عمق_QCOM             0x8BD4
#تعریف_کن GL_TEXTURE_داخلی_FORMAT_QCOM   0x8BD5
#تعریف_کن GL_TEXTURE_FORMAT_QCOM            0x8BD6
#تعریف_کن GL_TEXTURE_TYPE_QCOM              0x8BD7
#تعریف_کن GL_TEXTURE_IMAGE_VALID_QCOM       0x8BD8
#تعریف_کن GL_TEXTURE_رقم_سطوح_QCOM        0x8BD9
#تعریف_کن GL_TEXTURE_هدف_QCOM            0x8BDA
#تعریف_کن GL_TEXTURE_OBJECT_VALID_QCOM      0x8BDB
#تعریف_کن GL_STATE_RESTORE                  0x8BDC
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETTEXTURESQCOMPROC) (GLuint *textures, GLint maxTextures, GLint *رقم_Textures);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETBUFFERSQCOMPROC) (GLuint *buffers, GLint maxBuffers, GLint *رقم_Buffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETRENDERBUFFERSQCOMPROC) (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *رقم_Renderbuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETFRAMEBUFFERSQCOMPROC) (GLuint *framebuffers, GLint maxFramebuffers, GLint *رقم_Framebuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETTEXLEVELPARAMETERIVQCOMPROC) (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTTEXOBJECTSTATEOVERRIDEIQCOMPROC) (GLenum هدف, GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETTEXSUBIMAGEQCOMPROC) (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLenum format, GLenum type, فراغ *texels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETBUFFERPOINTERVQCOMPROC) (GLenum هدف, فراغ **params);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glExtGetTexturesQCOM (GLuint *textures, GLint maxTextures, GLint *رقم_Textures);
GL_APICALL فراغ GL_APIENTRY glExtGetBuffersQCOM (GLuint *buffers, GLint maxBuffers, GLint *رقم_Buffers);
GL_APICALL فراغ GL_APIENTRY glExtGetRenderbuffersQCOM (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *رقم_Renderbuffers);
GL_APICALL فراغ GL_APIENTRY glExtGetFramebuffersQCOM (GLuint *framebuffers, GLint maxFramebuffers, GLint *رقم_Framebuffers);
GL_APICALL فراغ GL_APIENTRY glExtGetTexLevelParameterivQCOM (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glExtTexObjectStateOverrideiQCOM (GLenum هدف, GLenum pname, GLint param);
GL_APICALL فراغ GL_APIENTRY glExtGetTexSubImageQCOM (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLenum format, GLenum type, فراغ *texels);
GL_APICALL فراغ GL_APIENTRY gl_Ext_Get_میانگیر_Pointerv_QCOM (GLenum هدف, فراغ **params);
#پایان_اگر
#پایان_اگر /* GL_QCOM_extended_get */

#اگر_تعریف_نشده GL_QCOM_extended_get2
#تعریف_کن GL_QCOM_extended_get2 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETSHADERSQCOMPROC) (GLuint *shaders, GLint maxShaders, GLint *رقم_Shaders);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETPROGRAMSQCOMPROC) (GLuint *programs, GLint maxPrograms, GLint *رقم_Programs);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLEXTISPROGRAMBINARYQCOMPROC) (GLuint برنامه);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETPROGRAMBINARYSOURCEQCOMPROC) (GLuint برنامه, GLenum shadertype, GLchar *منبع, GLint *درازی);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glExtGetShadersQCOM (GLuint *shaders, GLint maxShaders, GLint *رقم_Shaders);
GL_APICALL فراغ GL_APIENTRY glExtGetProgramsQCOM (GLuint *programs, GLint maxPrograms, GLint *رقم_Programs);
GL_APICALL GLboolean GL_APIENTRY gl_Ext_Is_برنامه_دودویی_QCOM (GLuint برنامه);
GL_APICALL فراغ GL_APIENTRY gl_Ext_Get_برنامه_دودویی_منبع_QCOM (GLuint برنامه, GLenum shadertype, GLchar *منبع, GLint *درازی);
#پایان_اگر
#پایان_اگر /* GL_QCOM_extended_get2 */

#اگر_تعریف_نشده GL_QCOM_قاب_extrapolation
#تعریف_کن GL_QCOM_قاب_extrapolation 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTRAPOLATETEX2DQCOMPROC) (GLuint src1, GLuint src2, GLuint output, GLfloat scale_ضریب);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glExtrapolateTex2DQCOM (GLuint src1, GLuint src2, GLuint output, GLfloat scale_ضریب);
#پایان_اگر
#پایان_اگر /* GL_QCOM_frame_extrapolation */

#اگر_تعریف_نشده GL_QCOM_framebuffer_foveated
#تعریف_کن GL_QCOM_framebuffer_foveated 1
#تعریف_کن GL_FOVEATION_ENABLE_بیت_QCOM      0x00000001
#تعریف_کن GL_FOVEATION_SCALED_BIN_روش_بیت_QCOM 0x00000002
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERFOVEATIONCONFIGQCOMPROC) (GLuint framebuffer, GLuint رقم_Layers, GLuint focal_Points_در_هر_Layer, GLuint requestedFeatures, GLuint *providedFeatures);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERFOVEATIONPARAMETERSQCOMPROC) (GLuint framebuffer, GLuint layer, GLuint focal_نقطه, GLfloat focalX, GLfloat focalY, GLfloat gainX, GLfloat gainY, GLfloat foveaArea);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferFoveationConfigQCOM (GLuint framebuffer, GLuint رقم_Layers, GLuint focal_Points_در_هر_Layer, GLuint requestedFeatures, GLuint *providedFeatures);
GL_APICALL فراغ GL_APIENTRY glFramebufferFoveationParametersQCOM (GLuint framebuffer, GLuint layer, GLuint focal_نقطه, GLfloat focalX, GLfloat focalY, GLfloat gainX, GLfloat gainY, GLfloat foveaArea);
#پایان_اگر
#پایان_اگر /* GL_QCOM_framebuffer_foveated */

#اگر_تعریف_نشده GL_QCOM_motion_estimation
#تعریف_کن GL_QCOM_motion_estimation 1
#تعریف_کن GL_MOTION_ESTIMATION_جستجو_بلوک_X_QCOM 0x8C90
#تعریف_کن GL_MOTION_ESTIMATION_جستجو_بلوک_Y_QCOM 0x8C91
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXESTIMATEMOTIONQCOMPROC) (GLuint ref, GLuint هدف, GLuint output);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXESTIMATEMOTIONREGIONSQCOMPROC) (GLuint ref, GLuint هدف, GLuint output, GLuint ماسک);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTexEstimateMotionQCOM (GLuint ref, GLuint هدف, GLuint output);
GL_APICALL فراغ GL_APIENTRY glTexEstimateMotionRegionsQCOM (GLuint ref, GLuint هدف, GLuint output, GLuint ماسک);
#پایان_اگر
#پایان_اگر /* GL_QCOM_motion_estimation */

#اگر_تعریف_نشده GL_QCOM_perfmon_global_نما
#تعریف_کن GL_QCOM_perfmon_global_نما 1
#تعریف_کن GL_PERFMON_GLOBAL_نما_QCOM       0x8FA0
#پایان_اگر /* GL_QCOM_perfmon_global_mode */

#اگر_تعریف_نشده GL_QCOM_render_sRGB_R8_RG8
#تعریف_کن GL_QCOM_render_sRGB_R8_RG8 1
#پایان_اگر /* GL_QCOM_render_sRGB_R8_RG8 */

#اگر_تعریف_نشده GL_QCOM_render_shared_exponent
#تعریف_کن GL_QCOM_render_shared_exponent 1
#پایان_اگر /* GL_QCOM_render_shared_exponent */

#اگر_تعریف_نشده GL_QCOM_shader_framebuffer_fetch_noncoherent
#تعریف_کن GL_QCOM_shader_framebuffer_fetch_noncoherent 1
#تعریف_کن GL_FRAMEBUFFER_FETCH_NONCOHERENT_QCOM 0x96A2
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERFETCHBARRIERQCOMPROC) (فراغ);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferFetchBarrierQCOM (فراغ);
#پایان_اگر
#پایان_اگر /* GL_QCOM_shader_framebuffer_fetch_noncoherent */

#اگر_تعریف_نشده GL_QCOM_shader_framebuffer_fetch_نرخ
#تعریف_کن GL_QCOM_shader_framebuffer_fetch_نرخ 1
#پایان_اگر /* GL_QCOM_shader_framebuffer_fetch_rate */

#اگر_تعریف_نشده GL_QCOM_shading_نرخ
#تعریف_کن GL_QCOM_shading_نرخ 1
#تعریف_کن GL_SHADING_نرخ_QCOM              0x96A4
#تعریف_کن GL_SHADING_نرخ_PRESERVE_ASPECT_نسبت_QCOM 0x96A5
#تعریف_کن GL_SHADING_نرخ_1_X1_PIXELS_QCOM   0x96A6
#تعریف_کن GL_SHADING_نرخ_1_X2_PIXELS_QCOM   0x96A7
#تعریف_کن GL_SHADING_نرخ_2_X1_PIXELS_QCOM   0x96A8
#تعریف_کن GL_SHADING_نرخ_2_X2_PIXELS_QCOM   0x96A9
#تعریف_کن GL_SHADING_نرخ_4_X2_PIXELS_QCOM   0x96AC
#تعریف_کن GL_SHADING_نرخ_4_X4_PIXELS_QCOM   0x96AE
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADINGRATEQCOMPROC) (GLenum نرخ);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Shading_نرخ_QCOM (GLenum نرخ);
#پایان_اگر
#پایان_اگر /* GL_QCOM_shading_rate */

#اگر_تعریف_نشده GL_QCOM_texture_foveated
#تعریف_کن GL_QCOM_texture_foveated 1
#تعریف_کن GL_TEXTURE_FOVEATED_FEATURE_بیتها_QCOM 0x8BFB
#تعریف_کن GL_TEXTURE_FOVEATED_MIN_PIXEL_DENSITY_QCOM 0x8BFC
#تعریف_کن GL_TEXTURE_FOVEATED_FEATURE_QUERY_QCOM 0x8BFD
#تعریف_کن GL_TEXTURE_FOVEATED_رقم_FOCAL_POINTS_QUERY_QCOM 0x8BFE
#تعریف_کن GL_FRAMEBUFFER_INCOMPLETE_FOVEATION_QCOM 0x8BFF
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTUREFOVEATIONPARAMETERSQCOMPROC) (GLuint texture, GLuint layer, GLuint focal_نقطه, GLfloat focalX, GLfloat focalY, GLfloat gainX, GLfloat gainY, GLfloat foveaArea);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTextureFoveationParametersQCOM (GLuint texture, GLuint layer, GLuint focal_نقطه, GLfloat focalX, GLfloat focalY, GLfloat gainX, GLfloat gainY, GLfloat foveaArea);
#پایان_اگر
#پایان_اگر /* GL_QCOM_texture_foveated */

#اگر_تعریف_نشده GL_QCOM_texture_foveated2
#تعریف_کن GL_QCOM_texture_foveated2 1
#تعریف_کن GL_TEXTURE_FOVEATED_CUTOFF_DENSITY_QCOM 0x96A0
#پایان_اگر /* GL_QCOM_texture_foveated2 */

#اگر_تعریف_نشده GL_QCOM_texture_foveated_subsampled_layout
#تعریف_کن GL_QCOM_texture_foveated_subsampled_layout 1
#تعریف_کن GL_FOVEATION_SUBSAMPLED_LAYOUT_روش_بیت_QCOM 0x00000004
#تعریف_کن GL_MAX_SHADER_SUBSAMPLED_IMAGE_UNITS_QCOM 0x8FA1
#پایان_اگر /* GL_QCOM_texture_foveated_subsampled_layout */

#اگر_تعریف_نشده GL_QCOM_texture_lod_bias
#تعریف_کن GL_QCOM_texture_lod_bias 1
#تعریف_کن GL_TEXTURE_LOD_BIAS_QCOM          0x8C96
#پایان_اگر /* GL_QCOM_texture_lod_bias */

#اگر_تعریف_نشده GL_QCOM_tiled_rendering
#تعریف_کن GL_QCOM_tiled_rendering 1
#تعریف_کن GL_COLOR_میانگیر_BIT0_QCOM         0x00000001
#تعریف_کن GL_COLOR_میانگیر_BIT1_QCOM         0x00000002
#تعریف_کن GL_COLOR_میانگیر_BIT2_QCOM         0x00000004
#تعریف_کن GL_COLOR_میانگیر_BIT3_QCOM         0x00000008
#تعریف_کن GL_COLOR_میانگیر_BIT4_QCOM         0x00000010
#تعریف_کن GL_COLOR_میانگیر_BIT5_QCOM         0x00000020
#تعریف_کن GL_COLOR_میانگیر_BIT6_QCOM         0x00000040
#تعریف_کن GL_COLOR_میانگیر_BIT7_QCOM         0x00000080
#تعریف_کن GL_عمق_میانگیر_BIT0_QCOM         0x00000100
#تعریف_کن GL_عمق_میانگیر_BIT1_QCOM         0x00000200
#تعریف_کن GL_عمق_میانگیر_BIT2_QCOM         0x00000400
#تعریف_کن GL_عمق_میانگیر_BIT3_QCOM         0x00000800
#تعریف_کن GL_عمق_میانگیر_BIT4_QCOM         0x00001000
#تعریف_کن GL_عمق_میانگیر_BIT5_QCOM         0x00002000
#تعریف_کن GL_عمق_میانگیر_BIT6_QCOM         0x00004000
#تعریف_کن GL_عمق_میانگیر_BIT7_QCOM         0x00008000
#تعریف_کن GL_STENCIL_میانگیر_BIT0_QCOM       0x00010000
#تعریف_کن GL_STENCIL_میانگیر_BIT1_QCOM       0x00020000
#تعریف_کن GL_STENCIL_میانگیر_BIT2_QCOM       0x00040000
#تعریف_کن GL_STENCIL_میانگیر_BIT3_QCOM       0x00080000
#تعریف_کن GL_STENCIL_میانگیر_BIT4_QCOM       0x00100000
#تعریف_کن GL_STENCIL_میانگیر_BIT5_QCOM       0x00200000
#تعریف_کن GL_STENCIL_میانگیر_BIT6_QCOM       0x00400000
#تعریف_کن GL_STENCIL_میانگیر_BIT7_QCOM       0x00800000
#تعریف_کن GL_MULTISAMPLE_میانگیر_BIT0_QCOM   0x01000000
#تعریف_کن GL_MULTISAMPLE_میانگیر_BIT1_QCOM   0x02000000
#تعریف_کن GL_MULTISAMPLE_میانگیر_BIT2_QCOM   0x04000000
#تعریف_کن GL_MULTISAMPLE_میانگیر_BIT3_QCOM   0x08000000
#تعریف_کن GL_MULTISAMPLE_میانگیر_BIT4_QCOM   0x10000000
#تعریف_کن GL_MULTISAMPLE_میانگیر_BIT5_QCOM   0x20000000
#تعریف_کن GL_MULTISAMPLE_میانگیر_BIT6_QCOM   0x40000000
#تعریف_کن GL_MULTISAMPLE_میانگیر_BIT7_QCOM   0x80000000
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTARTTILINGQCOMPROC) (GLuint x, GLuint y, GLuint عرض, GLuint ارتفاع, GLbitfield preserve_ماسک);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENDTILINGQCOMPROC) (GLbitfield preserve_ماسک);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_شروع_Tiling_QCOM (GLuint x, GLuint y, GLuint عرض, GLuint ارتفاع, GLbitfield preserve_ماسک);
GL_APICALL فراغ GL_APIENTRY gl_انتها_Tiling_QCOM (GLbitfield preserve_ماسک);
#پایان_اگر
#پایان_اگر /* GL_QCOM_tiled_rendering */

#اگر_تعریف_نشده GL_QCOM_writeonly_rendering
#تعریف_کن GL_QCOM_writeonly_rendering 1
#تعریف_کن GL_WRITEONLY_RENDERING_QCOM       0x8823
#پایان_اگر /* GL_QCOM_writeonly_rendering */

#اگر_تعریف_نشده GL_QCOM_ycbcr_degamma
#تعریف_کن GL_QCOM_ycbcr_degamma 1
#تعریف_کن GL_TEXTURE_Y_DEGAMMA_QCOM         0x9710
#تعریف_کن GL_TEXTURE_CBCR_DEGAMMA_QCOM      0x9711
#پایان_اگر /* GL_QCOM_ycbcr_degamma */

#اگر_تعریف_نشده GL_VIV_shader_دودویی
#تعریف_کن GL_VIV_shader_دودویی 1
#تعریف_کن GL_SHADER_دودویی_VIV              0x8FC4
#پایان_اگر /* GL_VIV_shader_binary */

#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر
