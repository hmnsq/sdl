#جے_بنا_تعریف __gles2_gl2ext_h_
#تعریف_کرو __gles2_gl2ext_h_ 1

#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت

/*
** Copyright 2013-2026 The Khronos Group Inc.
** SPDX-License-Identifier: MIT
**
** This header is generated from the Khronos OpenGL / OpenGL ES XML
** API Registry. The current version of the Registry, generator scripts
** used to make the header, and the header can be found at
**   https://github.com/KhronosGroup/OpenGL-Registry
*/

#جے_بنا_تعریف GL_APIENTRYP
#تعریف_کرو GL_APIENTRYP GL_APIENTRY*
#جے_انت

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

#جے_بنا_تعریف GL_KHR_blend_equation_advanced
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
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDBARRIERKHRPROC) (فراغ);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glBlendBarrierKHR (فراغ);
#جے_انت
#جے_انت /* GL_KHR_blend_equation_advanced */

#جے_بنا_تعریف GL_KHR_blend_equation_advanced_coherent
#تعریف_کرو GL_KHR_blend_equation_advanced_coherent 1
#تعریف_کرو GL_BLEND_ADVANCED_COHERENT_KHR    0x9285
#جے_انت /* GL_KHR_blend_equation_advanced_coherent */

#جے_بنا_تعریف GL_KHR_context_flush_control
#تعریف_کرو GL_KHR_context_flush_control 1
#تعریف_کرو GL_CONTEXT_RELEASE_BEHAVIOR_KHR   0x82FB
#تعریف_کرو GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_KHR 0x82FC
#جے_انت /* GL_KHR_context_flush_control */

#جے_بنا_تعریف GL_KHR_debug
#تعریف_کرو GL_KHR_debug 1
تعريفنوع فراغ (GL_APIENTRY  *GLDEBUGPROCKHR)(GLenum سروت,GLenum type,GLuint id,GLenum severity,GLsizei لمائی,ثابت GLchar *سنیہا,ثابت فراغ *userParam);
#تعریف_کرو GL_SAMPLER                        0x82E6
#تعریف_کرو GL_DEBUG_OUTPUT_SYNCHRONOUS_KHR   0x8242
#تعریف_کرو GL_DEBUG_اگلا_LOGGED_سنیہا_لمائی_KHR 0x8243
#تعریف_کرو GL_DEBUG_CALLBACK_FUNCTION_KHR    0x8244
#تعریف_کرو GL_DEBUG_CALLBACK_USER_PARAM_KHR  0x8245
#تعریف_کرو GL_DEBUG_سروت_API_KHR           0x8246
#تعریف_کرو GL_DEBUG_سروت_کھڑکی_SYSTEM_KHR 0x8247
#تعریف_کرو GL_DEBUG_سروت_SHADER_COMPILER_KHR 0x8248
#تعریف_کرو GL_DEBUG_سروت_تیجا_PARTY_KHR   0x8249
#تعریف_کرو GL_DEBUG_سروت_APPLICATION_KHR   0x824A
#تعریف_کرو GL_DEBUG_سروت_OTHER_KHR         0x824B
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
#تعریف_کرو GL_MAX_DEBUG_گروہ_ڈھیر_ڈونگھائی_KHR 0x826C
#تعریف_کرو GL_DEBUG_گروہ_ڈھیر_ڈونگھائی_KHR    0x826D
#تعریف_کرو GL_بفر_KHR                     0x82E0
#تعریف_کرو GL_SHADER_KHR                     0x82E1
#تعریف_کرو GL_پروگرام_KHR                    0x82E2
#تعریف_کرو GL_راس_ARRAY_KHR               0x8074
#تعریف_کرو GL_QUERY_KHR                      0x82E3
#تعریف_کرو GL_پروگرام_PIPELINE_KHR           0x82E4
#تعریف_کرو GL_SAMPLER_KHR                    0x82E6
#تعریف_کرو GL_MAX_LABEL_لمائی_KHR           0x82E8
#تعریف_کرو GL_MAX_DEBUG_سنیہا_لمائی_KHR   0x9143
#تعریف_کرو GL_MAX_DEBUG_LOGGED_MESSAGES_KHR  0x9144
#تعریف_کرو GL_DEBUG_LOGGED_MESSAGES_KHR      0x9145
#تعریف_کرو GL_DEBUG_SEVERITY_بلند_KHR        0x9146
#تعریف_کرو GL_DEBUG_SEVERITY_MEDIUM_KHR      0x9147
#تعریف_کرو GL_DEBUG_SEVERITY_کم_KHR         0x9148
#تعریف_کرو GL_DEBUG_OUTPUT_KHR               0x92E0
#تعریف_کرو GL_CONTEXT_FLAG_DEBUG_ثنائی_ہندسہ_KHR     0x00000002
#تعریف_کرو GL_ڈھیر_حد_توں_ودھ_KHR             0x0503
#تعریف_کرو GL_ڈھیر_UNDERFLOW_KHR            0x0504
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEBUGMESSAGECONTROLKHRPROC) (GLenum سروت, GLenum type, GLenum severity, GLsizei گنتی, ثابت GLuint *ids, GLboolean enabled);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEBUGMESSAGEINSERTKHRPROC) (GLenum سروت, GLenum type, GLuint id, GLenum severity, GLsizei لمائی, ثابت GLchar *buf);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEBUGMESSAGECALLBACKKHRPROC) (GLDEBUGPROCKHR callback, ثابت فراغ *userParam);
تعريفنوع GLuint (GL_APIENTRYP PFNGLGETDEBUGMESSAGELOGKHRPROC) (GLuint گنتی, GLsizei buf_ناپ, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *سنیہا_Log);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPUSHDEBUGGROUPKHRPROC) (GLenum سروت, GLuint id, GLsizei لمائی, ثابت GLchar *سنیہا);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOPDEBUGGROUPKHRPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLOBJECTLABELKHRPROC) (GLenum identifier, GLuint name, GLsizei لمائی, ثابت GLchar *label);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETOBJECTLABELKHRPROC) (GLenum identifier, GLuint name, GLsizei buf_ناپ, GLsizei *لمائی, GLchar *label);
تعريفنوع فراغ (GL_APIENTRYP PFNGLOBJECTPTRLABELKHRPROC) (ثابت فراغ *ptr, GLsizei لمائی, ثابت GLchar *label);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETOBJECTPTRLABELKHRPROC) (ثابت فراغ *ptr, GLsizei buf_ناپ, GLsizei *لمائی, GLchar *label);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPOINTERVKHRPROC) (GLenum pname, فراغ **params);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Debug_سنیہا_Control_KHR (GLenum سروت, GLenum type, GLenum severity, GLsizei گنتی, ثابت GLuint *ids, GLboolean enabled);
GL_APICALL فراغ GL_APIENTRY gl_Debug_سنیہا_داخل_کرو_KHR (GLenum سروت, GLenum type, GLuint id, GLenum severity, GLsizei لمائی, ثابت GLchar *buf);
GL_APICALL فراغ GL_APIENTRY gl_Debug_سنیہا_Callback_KHR (GLDEBUGPROCKHR callback, ثابت فراغ *userParam);
GL_APICALL GLuint GL_APIENTRY gl_Get_Debug_سنیہا_Log_KHR (GLuint گنتی, GLsizei buf_ناپ, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *سنیہا_Log);
GL_APICALL فراغ GL_APIENTRY gl_ڈالو_Debug_گروہ_KHR (GLenum سروت, GLuint id, GLsizei لمائی, ثابت GLchar *سنیہا);
GL_APICALL فراغ GL_APIENTRY gl_نکالو_Debug_گروہ_KHR (فراغ);
GL_APICALL فراغ GL_APIENTRY glObjectLabelKHR (GLenum identifier, GLuint name, GLsizei لمائی, ثابت GLchar *label);
GL_APICALL فراغ GL_APIENTRY glGetObjectLabelKHR (GLenum identifier, GLuint name, GLsizei buf_ناپ, GLsizei *لمائی, GLchar *label);
GL_APICALL فراغ GL_APIENTRY glObjectPtrLabelKHR (ثابت فراغ *ptr, GLsizei لمائی, ثابت GLchar *label);
GL_APICALL فراغ GL_APIENTRY glGetObjectPtrLabelKHR (ثابت فراغ *ptr, GLsizei buf_ناپ, GLsizei *لمائی, GLchar *label);
GL_APICALL فراغ GL_APIENTRY glGetPointervKHR (GLenum pname, فراغ **params);
#جے_انت
#جے_انت /* GL_KHR_debug */

#جے_بنا_تعریف GL_KHR_no_error
#تعریف_کرو GL_KHR_no_error 1
#تعریف_کرو GL_CONTEXT_FLAG_NO_ERROR_ثنائی_ہندسہ_KHR  0x00000008
#جے_انت /* GL_KHR_no_error */

#جے_بنا_تعریف GL_KHR_parallel_shader_compile
#تعریف_کرو GL_KHR_parallel_shader_compile 1
#تعریف_کرو GL_MAX_SHADER_COMPILER_دھاگے_KHR 0x91B0
#تعریف_کرو GL_COMPLETION_حالت_KHR          0x91B1
تعريفنوع فراغ (GL_APIENTRYP PFNGLMAXSHADERCOMPILERTHREADSKHRPROC) (GLuint گنتی);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Max_Shader_Compiler_دھاگے_KHR (GLuint گنتی);
#جے_انت
#جے_انت /* GL_KHR_parallel_shader_compile */

#جے_بنا_تعریف GL_KHR_robust_بفر_access_behavior
#تعریف_کرو GL_KHR_robust_بفر_access_behavior 1
#جے_انت /* GL_KHR_robust_buffer_access_behavior */

#جے_بنا_تعریف GL_KHR_robustness
#تعریف_کرو GL_KHR_robustness 1
#تعریف_کرو GL_CONTEXT_ROBUST_ACCESS_KHR      0x90F3
#تعریف_کرو GL_LOSE_CONTEXT_ON_RESET_KHR      0x8252
#تعریف_کرو GL_GUILTY_CONTEXT_RESET_KHR       0x8253
#تعریف_کرو GL_INNOCENT_CONTEXT_RESET_KHR     0x8254
#تعریف_کرو GL_UNKNOWN_CONTEXT_RESET_KHR      0x8255
#تعریف_کرو GL_RESET_NOTIFICATION_STRATEGY_KHR 0x8256
#تعریف_کرو GL_NO_RESET_NOTIFICATION_KHR      0x8261
#تعریف_کرو GL_CONTEXT_گواچا_KHR               0x0507
تعريفنوع GLenum (GL_APIENTRYP PFNGLGETGRAPHICSRESETSTATUSKHRPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLREADNPIXELSKHRPROC) (GLint x, GLint y, GLsizei چوڑائی, GLsizei اچائی, GLenum format, GLenum type, GLsizei buf_ناپ, فراغ *انکڑے);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNUNIFORMFVKHRPROC) (GLuint پروگرام, GLint location, GLsizei buf_ناپ, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNUNIFORMIVKHRPROC) (GLuint پروگرام, GLint location, GLsizei buf_ناپ, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNUNIFORMUIVKHRPROC) (GLuint پروگرام, GLint location, GLsizei buf_ناپ, GLuint *params);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL GLenum GL_APIENTRY gl_Get_Graphics_Reset_حالت_KHR (فراغ);
GL_APICALL فراغ GL_APIENTRY glReadnPixelsKHR (GLint x, GLint y, GLsizei چوڑائی, GLsizei اچائی, GLenum format, GLenum type, GLsizei buf_ناپ, فراغ *انکڑے);
GL_APICALL فراغ GL_APIENTRY glGetnUniformfvKHR (GLuint پروگرام, GLint location, GLsizei buf_ناپ, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY glGetnUniformivKHR (GLuint پروگرام, GLint location, GLsizei buf_ناپ, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetnUniformuivKHR (GLuint پروگرام, GLint location, GLsizei buf_ناپ, GLuint *params);
#جے_انت
#جے_انت /* GL_KHR_robustness */

#جے_بنا_تعریف GL_KHR_shader_subgroup
#تعریف_کرو GL_KHR_shader_subgroup 1
#تعریف_کرو GL_SUBGROUP_ناپ_KHR              0x9532
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
#جے_انت /* GL_KHR_shader_subgroup */

#جے_بنا_تعریف GL_KHR_texture_compression_astc_hdr
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
#جے_انت /* GL_KHR_texture_compression_astc_hdr */

#جے_بنا_تعریف GL_KHR_texture_compression_astc_ldr
#تعریف_کرو GL_KHR_texture_compression_astc_ldr 1
#جے_انت /* GL_KHR_texture_compression_astc_ldr */

#جے_بنا_تعریف GL_KHR_texture_compression_astc_sliced_3d
#تعریف_کرو GL_KHR_texture_compression_astc_sliced_3d 1
#جے_انت /* GL_KHR_texture_compression_astc_sliced_3d */

#جے_بنا_تعریف GL_OES_EGL_image
#تعریف_کرو GL_OES_EGL_image 1
تعريفنوع فراغ *GLeglImageOES;
تعريفنوع فراغ (GL_APIENTRYP PFNGLEGLIMAGETARGETTEXTURE2DOESPROC) (GLenum نشانہ, GLeglImageOES image);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEGLIMAGETARGETRENDERBUFFERSTORAGEOESPROC) (GLenum نشانہ, GLeglImageOES image);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_EGLImage_نشانہ_Texture2_DOES (GLenum نشانہ, GLeglImageOES image);
GL_APICALL فراغ GL_APIENTRY gl_EGLImage_نشانہ_Renderbuffer_Storage_OES (GLenum نشانہ, GLeglImageOES image);
#جے_انت
#جے_انت /* GL_OES_EGL_image */

#جے_بنا_تعریف GL_OES_EGL_image_external
#تعریف_کرو GL_OES_EGL_image_external 1
#تعریف_کرو GL_TEXTURE_EXTERNAL_OES           0x8D65
#تعریف_کرو GL_TEXTURE_BINDING_EXTERNAL_OES   0x8D67
#تعریف_کرو GL_REQUIRED_TEXTURE_IMAGE_UNITS_OES 0x8D68
#تعریف_کرو GL_SAMPLER_EXTERNAL_OES           0x8D66
#جے_انت /* GL_OES_EGL_image_external */

#جے_بنا_تعریف GL_OES_EGL_image_external_essl3
#تعریف_کرو GL_OES_EGL_image_external_essl3 1
#جے_انت /* GL_OES_EGL_image_external_essl3 */

#جے_بنا_تعریف GL_OES_compressed_ETC1_RGB8_sub_texture
#تعریف_کرو GL_OES_compressed_ETC1_RGB8_sub_texture 1
#جے_انت /* GL_OES_compressed_ETC1_RGB8_sub_texture */

#جے_بنا_تعریف GL_OES_compressed_ETC1_RGB8_texture
#تعریف_کرو GL_OES_compressed_ETC1_RGB8_texture 1
#تعریف_کرو GL_ETC1_RGB8_OES                  0x8D64
#جے_انت /* GL_OES_compressed_ETC1_RGB8_texture */

#جے_بنا_تعریف GL_OES_compressed_paletted_texture
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
#جے_انت /* GL_OES_compressed_paletted_texture */

#جے_بنا_تعریف GL_OES_copy_image
#تعریف_کرو GL_OES_copy_image 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYIMAGESUBDATAOESPROC) (GLuint srcName, GLenum src_نشانہ, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dst_نشانہ, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei src_چوڑائی, GLsizei src_اچائی, GLsizei src_ڈونگھائی);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Copy_Image_Sub_انکڑے_OES (GLuint srcName, GLenum src_نشانہ, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dst_نشانہ, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei src_چوڑائی, GLsizei src_اچائی, GLsizei src_ڈونگھائی);
#جے_انت
#جے_انت /* GL_OES_copy_image */

#جے_بنا_تعریف GL_OES_depth24
#تعریف_کرو GL_OES_depth24 1
#تعریف_کرو GL_ڈونگھائی_COMPONENT24_OES          0x81A6
#جے_انت /* GL_OES_depth24 */

#جے_بنا_تعریف GL_OES_depth32
#تعریف_کرو GL_OES_depth32 1
#تعریف_کرو GL_ڈونگھائی_COMPONENT32_OES          0x81A7
#جے_انت /* GL_OES_depth32 */

#جے_بنا_تعریف GL_OES_ڈونگھائی_texture
#تعریف_کرو GL_OES_ڈونگھائی_texture 1
#جے_انت /* GL_OES_depth_texture */

#جے_بنا_تعریف GL_OES_draw_buffers_اشاریہ_دار
#تعریف_کرو GL_OES_draw_buffers_اشاریہ_دار 1
#تعریف_کرو GL_MIN                            0x8007
#تعریف_کرو GL_MAX                            0x8008
تعريفنوع فراغ (GL_APIENTRYP PFNGLENABLEIOESPROC) (GLenum نشانہ, GLuint اشاریہ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISABLEIOESPROC) (GLenum نشانہ, GLuint اشاریہ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONIOESPROC) (GLuint buf, GLenum منوال);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEIOESPROC) (GLuint buf, GLenum منوال_RGB, GLenum منوال_Alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDFUNCIOESPROC) (GLuint buf, GLenum src, GLenum dst);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEIOESPROC) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOLORMASKIOESPROC) (GLuint اشاریہ, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISENABLEDIOESPROC) (GLenum نشانہ, GLuint اشاریہ);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glEnableiOES (GLenum نشانہ, GLuint اشاریہ);
GL_APICALL فراغ GL_APIENTRY glDisableiOES (GLenum نشانہ, GLuint اشاریہ);
GL_APICALL فراغ GL_APIENTRY glBlendEquationiOES (GLuint buf, GLenum منوال);
GL_APICALL فراغ GL_APIENTRY glBlendEquationSeparateiOES (GLuint buf, GLenum منوال_RGB, GLenum منوال_Alpha);
GL_APICALL فراغ GL_APIENTRY glBlendFunciOES (GLuint buf, GLenum src, GLenum dst);
GL_APICALL فراغ GL_APIENTRY glBlendFuncSeparateiOES (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
GL_APICALL فراغ GL_APIENTRY glColorMaskiOES (GLuint اشاریہ, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
GL_APICALL GLboolean GL_APIENTRY glIsEnablediOES (GLenum نشانہ, GLuint اشاریہ);
#جے_انت
#جے_انت /* GL_OES_draw_buffers_indexed */

#جے_بنا_تعریف GL_OES_draw_elements_ادھار_راس
#تعریف_کرو GL_OES_draw_elements_ادھار_راس 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSBASEVERTEXOESPROC) (GLenum منوال, GLsizei گنتی, GLenum type, ثابت فراغ *indices, GLint basevertex);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWRANGEELEMENTSBASEVERTEXOESPROC) (GLenum منوال, GLuint شروع, GLuint سرا, GLsizei گنتی, GLenum type, ثابت فراغ *indices, GLint basevertex);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXOESPROC) (GLenum منوال, GLsizei گنتی, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLint basevertex);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSBASEVERTEXEXTPROC) (GLenum منوال, ثابت GLsizei *گنتی, GLenum type, ثابت فراغ *ثابت*indices, GLsizei drawcount, ثابت GLint *basevertex);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Draw_Elements_ادھار_راس_OES (GLenum منوال, GLsizei گنتی, GLenum type, ثابت فراغ *indices, GLint basevertex);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Range_Elements_ادھار_راس_OES (GLenum منوال, GLuint شروع, GLuint سرا, GLsizei گنتی, GLenum type, ثابت فراغ *indices, GLint basevertex);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Elements_Instanced_ادھار_راس_OES (GLenum منوال, GLsizei گنتی, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLint basevertex);
GL_APICALL فراغ GL_APIENTRY gl_Multi_Draw_Elements_ادھار_راس_EXT (GLenum منوال, ثابت GLsizei *گنتی, GLenum type, ثابت فراغ *ثابت*indices, GLsizei drawcount, ثابت GLint *basevertex);
#جے_انت
#جے_انت /* GL_OES_draw_elements_base_vertex */

#جے_بنا_تعریف GL_OES_element_اشاریہ_uint
#تعریف_کرو GL_OES_element_اشاریہ_uint 1
#جے_انت /* GL_OES_element_index_uint */

#جے_بنا_تعریف GL_OES_fbo_render_mipmap
#تعریف_کرو GL_OES_fbo_render_mipmap 1
#جے_انت /* GL_OES_fbo_render_mipmap */

#جے_بنا_تعریف GL_OES_fragment_precision_بلند
#تعریف_کرو GL_OES_fragment_precision_بلند 1
#جے_انت /* GL_OES_fragment_precision_high */

#جے_بنا_تعریف GL_OES_geometry_نقطہ_ناپ
#تعریف_کرو GL_OES_geometry_نقطہ_ناپ 1
#جے_انت /* GL_OES_geometry_point_size */

#جے_بنا_تعریف GL_OES_geometry_shader
#تعریف_کرو GL_OES_geometry_shader 1
#تعریف_کرو GL_GEOMETRY_SHADER_OES            0x8DD9
#تعریف_کرو GL_GEOMETRY_SHADER_ثنائی_ہندسہ_OES        0x00000004
#تعریف_کرو GL_GEOMETRY_LINKED_VERTICES_باہرلا_OES 0x8916
#تعریف_کرو GL_GEOMETRY_LINKED_داخلہ_TYPE_OES 0x8917
#تعریف_کرو GL_GEOMETRY_LINKED_OUTPUT_TYPE_OES 0x8918
#تعریف_کرو GL_GEOMETRY_SHADER_INVOCATIONS_OES 0x887F
#تعریف_کرو GL_LAYER_PROVOKING_راس_OES     0x825E
#تعریف_کرو GL_سطریں_ADJACENCY_OES            0x000A
#تعریف_کرو GL_سطر_STRIP_ADJACENCY_OES       0x000B
#تعریف_کرو GL_TRIANGLES_ADJACENCY_OES        0x000C
#تعریف_کرو GL_TRIANGLE_STRIP_ADJACENCY_OES   0x000D
#تعریف_کرو GL_MAX_GEOMETRY_اکسار_COMPONENTS_OES 0x8DDF
#تعریف_کرو GL_MAX_GEOMETRY_اکسار_بلاکاں_OES 0x8A2C
#تعریف_کرو GL_MAX_COMBINED_GEOMETRY_اکسار_COMPONENTS_OES 0x8A32
#تعریف_کرو GL_MAX_GEOMETRY_داخلہ_COMPONENTS_OES 0x9123
#تعریف_کرو GL_MAX_GEOMETRY_OUTPUT_COMPONENTS_OES 0x9124
#تعریف_کرو GL_MAX_GEOMETRY_OUTPUT_VERTICES_OES 0x8DE0
#تعریف_کرو GL_MAX_GEOMETRY_کل_OUTPUT_COMPONENTS_OES 0x8DE1
#تعریف_کرو GL_MAX_GEOMETRY_SHADER_INVOCATIONS_OES 0x8E5A
#تعریف_کرو GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_OES 0x8C29
#تعریف_کرو GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS_OES 0x92CF
#تعریف_کرو GL_MAX_GEOMETRY_ATOMIC_COUNTERS_OES 0x92D5
#تعریف_کرو GL_MAX_GEOMETRY_IMAGE_UNIFORMS_OES 0x90CD
#تعریف_کرو GL_MAX_GEOMETRY_SHADER_STORAGE_بلاکاں_OES 0x90D7
#تعریف_کرو GL_پہلا_راس_CONVENTION_OES    0x8E4D
#تعریف_کرو GL_آخری_راس_CONVENTION_OES     0x8E4E
#تعریف_کرو GL_UNDEFINED_راس_OES           0x8260
#تعریف_کرو GL_PRIMITIVES_GENERATED_OES       0x8C87
#تعریف_کرو GL_FRAMEBUFFER_DEFAULT_LAYERS_OES 0x9312
#تعریف_کرو GL_MAX_FRAMEBUFFER_LAYERS_OES     0x9317
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_OES 0x8DA8
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_LAYERED_OES 0x8DA7
#تعریف_کرو GL_REFERENCED_BY_GEOMETRY_SHADER_OES 0x9309
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREOESPROC) (GLenum نشانہ, GLenum attachment, GLuint texture, GLint level);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferTextureOES (GLenum نشانہ, GLenum attachment, GLuint texture, GLint level);
#جے_انت
#جے_انت /* GL_OES_geometry_shader */

#جے_بنا_تعریف GL_OES_get_پروگرام_ثنائی
#تعریف_کرو GL_OES_get_پروگرام_ثنائی 1
#تعریف_کرو GL_پروگرام_ثنائی_لمائی_OES      0x8741
#تعریف_کرو GL_عدد_پروگرام_ثنائی_FORMATS_OES 0x87FE
#تعریف_کرو GL_پروگرام_ثنائی_FORMATS_OES     0x87FF
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMBINARYOESPROC) (GLuint پروگرام, GLsizei buf_ناپ, GLsizei *لمائی, GLenum *ثنائی_Format, فراغ *ثنائی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMBINARYOESPROC) (GLuint پروگرام, GLenum ثنائی_Format, ثابت فراغ *ثنائی, GLint لمائی);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Get_پروگرام_ثنائی_OES (GLuint پروگرام, GLsizei buf_ناپ, GLsizei *لمائی, GLenum *ثنائی_Format, فراغ *ثنائی);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_ثنائی_OES (GLuint پروگرام, GLenum ثنائی_Format, ثابت فراغ *ثنائی, GLint لمائی);
#جے_انت
#جے_انت /* GL_OES_get_program_binary */

#جے_بنا_تعریف GL_OES_gpu_shader5
#تعریف_کرو GL_OES_gpu_shader5 1
#جے_انت /* GL_OES_gpu_shader5 */

#جے_بنا_تعریف GL_OES_mapbuffer
#تعریف_کرو GL_OES_mapbuffer 1
#تعریف_کرو GL_WRITE_ONLY_OES                 0x88B9
#تعریف_کرو GL_بفر_ACCESS_OES              0x88BB
#تعریف_کرو GL_بفر_MAPPED_OES              0x88BC
#تعریف_کرو GL_بفر_MAP_اشارہ_گر_OES         0x88BD
تعريفنوع فراغ *(GL_APIENTRYP PFNGLMAPBUFFEROESPROC) (GLenum نشانہ, GLenum access);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLUNMAPBUFFEROESPROC) (GLenum نشانہ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETBUFFERPOINTERVOESPROC) (GLenum نشانہ, GLenum pname, فراغ **params);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ *GL_APIENTRY gl_Map_بفر_OES (GLenum نشانہ, GLenum access);
GL_APICALL GLboolean GL_APIENTRY gl_Unmap_بفر_OES (GLenum نشانہ);
GL_APICALL فراغ GL_APIENTRY gl_Get_بفر_Pointerv_OES (GLenum نشانہ, GLenum pname, فراغ **params);
#جے_انت
#جے_انت /* GL_OES_mapbuffer */

#جے_بنا_تعریف GL_OES_packed_ڈونگھائی_stencil
#تعریف_کرو GL_OES_packed_ڈونگھائی_stencil 1
#تعریف_کرو GL_ڈونگھائی_STENCIL_OES              0x84F9
#تعریف_کرو GL_UNSIGNED_INT_24_8_OES          0x84FA
#تعریف_کرو GL_DEPTH24_STENCIL8_OES           0x88F0
#جے_انت /* GL_OES_packed_depth_stencil */

#جے_بنا_تعریف GL_OES_primitive_bounding_box
#تعریف_کرو GL_OES_primitive_bounding_box 1
#تعریف_کرو GL_PRIMITIVE_BOUNDING_BOX_OES     0x92BE
تعريفنوع فراغ (GL_APIENTRYP PFNGLPRIMITIVEBOUNDINGBOXOESPROC) (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glPrimitiveBoundingBoxOES (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
#جے_انت
#جے_انت /* GL_OES_primitive_bounding_box */

#جے_بنا_تعریف GL_OES_required_internalformat
#تعریف_کرو GL_OES_required_internalformat 1
#تعریف_کرو GL_ALPHA8_OES                     0x803C
#تعریف_کرو GL_ڈونگھائی_COMPONENT16_OES          0x81A5
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
#جے_انت /* GL_OES_required_internalformat */

#جے_بنا_تعریف GL_OES_rgb8_rgba8
#تعریف_کرو GL_OES_rgb8_rgba8 1
#جے_انت /* GL_OES_rgb8_rgba8 */

#جے_بنا_تعریف GL_OES_sample_shading
#تعریف_کرو GL_OES_sample_shading 1
#تعریف_کرو GL_SAMPLE_SHADING_OES             0x8C36
#تعریف_کرو GL_MIN_SAMPLE_SHADING_قدر_OES   0x8C37
تعريفنوع فراغ (GL_APIENTRYP PFNGLMINSAMPLESHADINGOESPROC) (GLfloat قدر);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glMinSampleShadingOES (GLfloat قدر);
#جے_انت
#جے_انت /* GL_OES_sample_shading */

#جے_بنا_تعریف GL_OES_sample_variables
#تعریف_کرو GL_OES_sample_variables 1
#جے_انت /* GL_OES_sample_variables */

#جے_بنا_تعریف GL_OES_shader_image_atomic
#تعریف_کرو GL_OES_shader_image_atomic 1
#جے_انت /* GL_OES_shader_image_atomic */

#جے_بنا_تعریف GL_OES_shader_io_بلاکاں
#تعریف_کرو GL_OES_shader_io_بلاکاں 1
#جے_انت /* GL_OES_shader_io_blocks */

#جے_بنا_تعریف GL_OES_shader_multisample_interpolation
#تعریف_کرو GL_OES_shader_multisample_interpolation 1
#تعریف_کرو GL_MIN_FRAGMENT_INTERPOLATION_وتھ_OES 0x8E5B
#تعریف_کرو GL_MAX_FRAGMENT_INTERPOLATION_وتھ_OES 0x8E5C
#تعریف_کرو GL_FRAGMENT_INTERPOLATION_وتھ_بٹ_OES 0x8E5D
#جے_انت /* GL_OES_shader_multisample_interpolation */

#جے_بنا_تعریف GL_OES_standard_derivatives
#تعریف_کرو GL_OES_standard_derivatives 1
#تعریف_کرو GL_FRAGMENT_SHADER_DERIVATIVE_HINT_OES 0x8B8B
#جے_انت /* GL_OES_standard_derivatives */

#جے_بنا_تعریف GL_OES_stencil1
#تعریف_کرو GL_OES_stencil1 1
#تعریف_کرو GL_STENCIL_INDEX1_OES             0x8D46
#جے_انت /* GL_OES_stencil1 */

#جے_بنا_تعریف GL_OES_stencil4
#تعریف_کرو GL_OES_stencil4 1
#تعریف_کرو GL_STENCIL_INDEX4_OES             0x8D47
#جے_انت /* GL_OES_stencil4 */

#جے_بنا_تعریف GL_OES_surfaceless_context
#تعریف_کرو GL_OES_surfaceless_context 1
#تعریف_کرو GL_FRAMEBUFFER_UNDEFINED_OES      0x8219
#جے_انت /* GL_OES_surfaceless_context */

#جے_بنا_تعریف GL_OES_tessellation_نقطہ_ناپ
#تعریف_کرو GL_OES_tessellation_نقطہ_ناپ 1
#جے_انت /* GL_OES_tessellation_point_size */

#جے_بنا_تعریف GL_OES_tessellation_shader
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
#تعریف_کرو GL_MAX_TESS_CONTROL_اکسار_COMPONENTS_OES 0x8E7F
#تعریف_کرو GL_MAX_TESS_EVALUATION_اکسار_COMPONENTS_OES 0x8E80
#تعریف_کرو GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS_OES 0x8E81
#تعریف_کرو GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS_OES 0x8E82
#تعریف_کرو GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS_OES 0x8E83
#تعریف_کرو GL_MAX_TESS_PATCH_COMPONENTS_OES  0x8E84
#تعریف_کرو GL_MAX_TESS_CONTROL_کل_OUTPUT_COMPONENTS_OES 0x8E85
#تعریف_کرو GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS_OES 0x8E86
#تعریف_کرو GL_MAX_TESS_CONTROL_اکسار_بلاکاں_OES 0x8E89
#تعریف_کرو GL_MAX_TESS_EVALUATION_اکسار_بلاکاں_OES 0x8E8A
#تعریف_کرو GL_MAX_TESS_CONTROL_داخلہ_COMPONENTS_OES 0x886C
#تعریف_کرو GL_MAX_TESS_EVALUATION_داخلہ_COMPONENTS_OES 0x886D
#تعریف_کرو GL_MAX_COMBINED_TESS_CONTROL_اکسار_COMPONENTS_OES 0x8E1E
#تعریف_کرو GL_MAX_COMBINED_TESS_EVALUATION_اکسار_COMPONENTS_OES 0x8E1F
#تعریف_کرو GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS_OES 0x92CD
#تعریف_کرو GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS_OES 0x92CE
#تعریف_کرو GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS_OES 0x92D3
#تعریف_کرو GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS_OES 0x92D4
#تعریف_کرو GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS_OES 0x90CB
#تعریف_کرو GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS_OES 0x90CC
#تعریف_کرو GL_MAX_TESS_CONTROL_SHADER_STORAGE_بلاکاں_OES 0x90D8
#تعریف_کرو GL_MAX_TESS_EVALUATION_SHADER_STORAGE_بلاکاں_OES 0x90D9
#تعریف_کرو GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED_OES 0x8221
#تعریف_کرو GL_IS_فی_PATCH_OES               0x92E7
#تعریف_کرو GL_REFERENCED_BY_TESS_CONTROL_SHADER_OES 0x9307
#تعریف_کرو GL_REFERENCED_BY_TESS_EVALUATION_SHADER_OES 0x9308
#تعریف_کرو GL_TESS_CONTROL_SHADER_OES        0x8E88
#تعریف_کرو GL_TESS_EVALUATION_SHADER_OES     0x8E87
#تعریف_کرو GL_TESS_CONTROL_SHADER_ثنائی_ہندسہ_OES    0x00000008
#تعریف_کرو GL_TESS_EVALUATION_SHADER_ثنائی_ہندسہ_OES 0x00000010
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATCHPARAMETERIOESPROC) (GLenum pname, GLint قدر);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glPatchParameteriOES (GLenum pname, GLint قدر);
#جے_انت
#جے_انت /* GL_OES_tessellation_shader */

#جے_بنا_تعریف GL_OES_texture_3D
#تعریف_کرو GL_OES_texture_3D 1
#تعریف_کرو GL_TEXTURE_WRAP_R_OES             0x8072
#تعریف_کرو GL_TEXTURE_3D_OES                 0x806F
#تعریف_کرو GL_TEXTURE_BINDING_3D_OES         0x806A
#تعریف_کرو GL_MAX_3_D_TEXTURE_ناپ_OES        0x8073
#تعریف_کرو GL_SAMPLER_3D_OES                 0x8B5F
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_3D_ZOFFSET_OES 0x8CD4
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXIMAGE3DOESPROC) (GLenum نشانہ, GLint level, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2, GLint border, GLenum format, GLenum type, ثابت فراغ *pixels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSUBIMAGE3DOESPROC) (GLenum نشانہ, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2, GLenum format, GLenum type, ثابت فراغ *pixels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYTEXSUBIMAGE3DOESPROC) (GLenum نشانہ, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei چوڑائی, GLsizei اچائی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOMPRESSEDTEXIMAGE3DOESPROC) (GLenum نشانہ, GLint level, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2, GLint border, GLsizei image_ناپ, ثابت فراغ *انکڑے);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE3DOESPROC) (GLenum نشانہ, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2, GLenum format, GLsizei image_ناپ, ثابت فراغ *انکڑے);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE3DOESPROC) (GLenum نشانہ, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTexImage3DOES (GLenum نشانہ, GLint level, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2, GLint border, GLenum format, GLenum type, ثابت فراغ *pixels);
GL_APICALL فراغ GL_APIENTRY glTexSubImage3DOES (GLenum نشانہ, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2, GLenum format, GLenum type, ثابت فراغ *pixels);
GL_APICALL فراغ GL_APIENTRY glCopyTexSubImage3DOES (GLenum نشانہ, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei چوڑائی, GLsizei اچائی);
GL_APICALL فراغ GL_APIENTRY glCompressedTexImage3DOES (GLenum نشانہ, GLint level, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2, GLint border, GLsizei image_ناپ, ثابت فراغ *انکڑے);
GL_APICALL فراغ GL_APIENTRY glCompressedTexSubImage3DOES (GLenum نشانہ, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2, GLenum format, GLsizei image_ناپ, ثابت فراغ *انکڑے);
GL_APICALL فراغ GL_APIENTRY glFramebufferTexture3DOES (GLenum نشانہ, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
#جے_انت
#جے_انت /* GL_OES_texture_3D */

#جے_بنا_تعریف GL_OES_texture_border_clamp
#تعریف_کرو GL_OES_texture_border_clamp 1
#تعریف_کرو GL_TEXTURE_BORDER_COLOR_OES       0x1004
#تعریف_کرو GL_CLAMP_منزل_BORDER_OES            0x812D
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERIIVOESPROC) (GLenum نشانہ, GLenum pname, ثابت GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERIUIVOESPROC) (GLenum نشانہ, GLenum pname, ثابت GLuint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXPARAMETERIIVOESPROC) (GLenum نشانہ, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXPARAMETERIUIVOESPROC) (GLenum نشانہ, GLenum pname, GLuint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIIVOESPROC) (GLuint sampler, GLenum pname, ثابت GLint *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIUIVOESPROC) (GLuint sampler, GLenum pname, ثابت GLuint *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIIVOESPROC) (GLuint sampler, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIUIVOESPROC) (GLuint sampler, GLenum pname, GLuint *params);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTexParameterIivOES (GLenum نشانہ, GLenum pname, ثابت GLint *params);
GL_APICALL فراغ GL_APIENTRY glTexParameterIuivOES (GLenum نشانہ, GLenum pname, ثابت GLuint *params);
GL_APICALL فراغ GL_APIENTRY glGetTexParameterIivOES (GLenum نشانہ, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetTexParameterIuivOES (GLenum نشانہ, GLenum pname, GLuint *params);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterIivOES (GLuint sampler, GLenum pname, ثابت GLint *param);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterIuivOES (GLuint sampler, GLenum pname, ثابت GLuint *param);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameterIivOES (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameterIuivOES (GLuint sampler, GLenum pname, GLuint *params);
#جے_انت
#جے_انت /* GL_OES_texture_border_clamp */

#جے_بنا_تعریف GL_OES_texture_بفر
#تعریف_کرو GL_OES_texture_بفر 1
#تعریف_کرو GL_TEXTURE_بفر_OES             0x8C2A
#تعریف_کرو GL_TEXTURE_بفر_BINDING_OES     0x8C2A
#تعریف_کرو GL_MAX_TEXTURE_بفر_ناپ_OES    0x8C2B
#تعریف_کرو GL_TEXTURE_BINDING_بفر_OES     0x8C2C
#تعریف_کرو GL_TEXTURE_بفر_انکڑے_STORE_BINDING_OES 0x8C2D
#تعریف_کرو GL_TEXTURE_بفر_وتھ_ALIGNMENT_OES 0x919F
#تعریف_کرو GL_SAMPLER_بفر_OES             0x8DC2
#تعریف_کرو GL_INT_SAMPLER_بفر_OES         0x8DD0
#تعریف_کرو GL_UNSIGNED_INT_SAMPLER_بفر_OES 0x8DD8
#تعریف_کرو GL_IMAGE_بفر_OES               0x9051
#تعریف_کرو GL_INT_IMAGE_بفر_OES           0x905C
#تعریف_کرو GL_UNSIGNED_INT_IMAGE_بفر_OES  0x9067
#تعریف_کرو GL_TEXTURE_بفر_وتھ_OES      0x919D
#تعریف_کرو GL_TEXTURE_بفر_ناپ_OES        0x919E
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXBUFFEROESPROC) (GLenum نشانہ, GLenum internalformat, GLuint بفر_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXBUFFERRANGEOESPROC) (GLenum نشانہ, GLenum internalformat, GLuint بفر_2, GLintptr وتھ_2, GLsizeiptr ناپ);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Tex_بفر_OES (GLenum نشانہ, GLenum internalformat, GLuint بفر_2);
GL_APICALL فراغ GL_APIENTRY gl_Tex_بفر_Range_OES (GLenum نشانہ, GLenum internalformat, GLuint بفر_2, GLintptr وتھ_2, GLsizeiptr ناپ);
#جے_انت
#جے_انت /* GL_OES_texture_buffer */

#جے_بنا_تعریف GL_OES_texture_compression_astc
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
#جے_انت /* GL_OES_texture_compression_astc */

#جے_بنا_تعریف GL_OES_texture_cube_map_array
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
#جے_انت /* GL_OES_texture_cube_map_array */

#جے_بنا_تعریف GL_OES_texture_float
#تعریف_کرو GL_OES_texture_float 1
#جے_انت /* GL_OES_texture_float */

#جے_بنا_تعریف GL_OES_texture_float_خطی
#تعریف_کرو GL_OES_texture_float_خطی 1
#جے_انت /* GL_OES_texture_float_linear */

#جے_بنا_تعریف GL_OES_texture_half_float
#تعریف_کرو GL_OES_texture_half_float 1
#تعریف_کرو GL_HALF_FLOAT_OES                 0x8D61
#جے_انت /* GL_OES_texture_half_float */

#جے_بنا_تعریف GL_OES_texture_half_float_خطی
#تعریف_کرو GL_OES_texture_half_float_خطی 1
#جے_انت /* GL_OES_texture_half_float_linear */

#جے_بنا_تعریف GL_OES_texture_npot
#تعریف_کرو GL_OES_texture_npot 1
#جے_انت /* GL_OES_texture_npot */

#جے_بنا_تعریف GL_OES_texture_stencil8
#تعریف_کرو GL_OES_texture_stencil8 1
#تعریف_کرو GL_STENCIL_اشاریہ_OES              0x1901
#تعریف_کرو GL_STENCIL_INDEX8_OES             0x8D48
#جے_انت /* GL_OES_texture_stencil8 */

#جے_بنا_تعریف GL_OES_texture_storage_multisample_2d_array
#تعریف_کرو GL_OES_texture_storage_multisample_2d_array 1
#تعریف_کرو GL_TEXTURE_2D_MULTISAMPLE_ARRAY_OES 0x9102
#تعریف_کرو GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY_OES 0x9105
#تعریف_کرو GL_SAMPLER_2D_MULTISAMPLE_ARRAY_OES 0x910B
#تعریف_کرو GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY_OES 0x910C
#تعریف_کرو GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY_OES 0x910D
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE3DMULTISAMPLEOESPROC) (GLenum نشانہ, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2, GLboolean fixedsamplelocations);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTexStorage3DMultisampleOES (GLenum نشانہ, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2, GLboolean fixedsamplelocations);
#جے_انت
#جے_انت /* GL_OES_texture_storage_multisample_2d_array */

#جے_بنا_تعریف GL_OES_texture_view
#تعریف_کرو GL_OES_texture_view 1
#تعریف_کرو GL_TEXTURE_VIEW_MIN_LEVEL_OES     0x82DB
#تعریف_کرو GL_TEXTURE_VIEW_عدد_پدھراں_OES    0x82DC
#تعریف_کرو GL_TEXTURE_VIEW_MIN_LAYER_OES     0x82DD
#تعریف_کرو GL_TEXTURE_VIEW_عدد_LAYERS_OES    0x82DE
#تعریف_کرو GL_TEXTURE_IMMUTABLE_پدھراں       0x82DF
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTUREVIEWOESPROC) (GLuint texture, GLenum نشانہ, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTextureViewOES (GLuint texture, GLenum نشانہ, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
#جے_انت
#جے_انت /* GL_OES_texture_view */

#جے_بنا_تعریف GL_OES_راس_array_object
#تعریف_کرو GL_OES_راس_array_object 1
#تعریف_کرو GL_راس_ARRAY_BINDING_OES       0x85B5
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDVERTEXARRAYOESPROC) (GLuint array);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEVERTEXARRAYSOESPROC) (GLsizei n, ثابت GLuint *arrays);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENVERTEXARRAYSOESPROC) (GLsizei n, GLuint *arrays);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISVERTEXARRAYOESPROC) (GLuint array);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Bind_راس_Array_OES (GLuint array);
GL_APICALL فراغ GL_APIENTRY gl_Delete_راس_Arrays_OES (GLsizei n, ثابت GLuint *arrays);
GL_APICALL فراغ GL_APIENTRY gl_Gen_راس_Arrays_OES (GLsizei n, GLuint *arrays);
GL_APICALL GLboolean GL_APIENTRY gl_Is_راس_Array_OES (GLuint array);
#جے_انت
#جے_انت /* GL_OES_vertex_array_object */

#جے_بنا_تعریف GL_OES_راس_half_float
#تعریف_کرو GL_OES_راس_half_float 1
#جے_انت /* GL_OES_vertex_half_float */

#جے_بنا_تعریف GL_OES_راس_type_10_10_10_2
#تعریف_کرو GL_OES_راس_type_10_10_10_2 1
#تعریف_کرو GL_UNSIGNED_INT_10_10_10_2_OES    0x8DF6
#تعریف_کرو GL_INT_10_10_10_2_OES             0x8DF7
#جے_انت /* GL_OES_vertex_type_10_10_10_2 */

#جے_بنا_تعریف GL_OES_viewport_array
#تعریف_کرو GL_OES_viewport_array 1
#تعریف_کرو GL_MAX_VIEWPORTS_OES              0x825B
#تعریف_کرو GL_VIEWPORT_SUBPIXEL_بٹ_OES     0x825C
#تعریف_کرو GL_VIEWPORT_BOUNDS_RANGE_OES      0x825D
#تعریف_کرو GL_VIEWPORT_اشاریہ_PROVOKING_راس_OES 0x825F
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTARRAYVOESPROC) (GLuint پہلا, GLsizei گنتی, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTINDEXEDFOESPROC) (GLuint اشاریہ, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTINDEXEDFVOESPROC) (GLuint اشاریہ, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSORARRAYVOESPROC) (GLuint پہلا, GLsizei گنتی, ثابت GLint *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSORINDEXEDOESPROC) (GLuint اشاریہ, GLint بایاں, GLint bottom, GLsizei چوڑائی, GLsizei اچائی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSORINDEXEDVOESPROC) (GLuint اشاریہ, ثابت GLint *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHRANGEARRAYFVOESPROC) (GLuint پہلا, GLsizei گنتی, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHRANGEINDEXEDFOESPROC) (GLuint اشاریہ, GLfloat n, GLfloat f);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFLOATI_VOESPROC) (GLenum نشانہ, GLuint اشاریہ, GLfloat *انکڑے);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glViewportArrayvOES (GLuint پہلا, GLsizei گنتی, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY glViewportIndexedfOES (GLuint اشاریہ, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
GL_APICALL فراغ GL_APIENTRY glViewportIndexedfvOES (GLuint اشاریہ, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY glScissorArrayvOES (GLuint پہلا, GLsizei گنتی, ثابت GLint *v);
GL_APICALL فراغ GL_APIENTRY gl_Scissor_اشاریہ_دار_OES (GLuint اشاریہ, GLint بایاں, GLint bottom, GLsizei چوڑائی, GLsizei اچائی);
GL_APICALL فراغ GL_APIENTRY glScissorIndexedvOES (GLuint اشاریہ, ثابت GLint *v);
GL_APICALL فراغ GL_APIENTRY gl_ڈونگھائی_Range_Arrayfv_OES (GLuint پہلا, GLsizei گنتی, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY gl_ڈونگھائی_Range_Indexedf_OES (GLuint اشاریہ, GLfloat n, GLfloat f);
GL_APICALL فراغ GL_APIENTRY glGetFloati_vOES (GLenum نشانہ, GLuint اشاریہ, GLfloat *انکڑے);
#جے_انت
#جے_انت /* GL_OES_viewport_array */

#جے_بنا_تعریف GL_AMD_compressed_3DC_texture
#تعریف_کرو GL_AMD_compressed_3DC_texture 1
#تعریف_کرو GL_3DC_X_AMD                      0x87F9
#تعریف_کرو GL_3DC_XY_AMD                     0x87FA
#جے_انت /* GL_AMD_compressed_3DC_texture */

#جے_بنا_تعریف GL_AMD_compressed_ATC_texture
#تعریف_کرو GL_AMD_compressed_ATC_texture 1
#تعریف_کرو GL_ATC_RGB_AMD                    0x8C92
#تعریف_کرو GL_ATC_RGBA_EXPLICIT_ALPHA_AMD    0x8C93
#تعریف_کرو GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD 0x87EE
#جے_انت /* GL_AMD_compressed_ATC_texture */

#جے_بنا_تعریف GL_AMD_framebuffer_multisample_advanced
#تعریف_کرو GL_AMD_framebuffer_multisample_advanced 1
#تعریف_کرو GL_RENDERBUFFER_STORAGE_SAMPLES_AMD 0x91B2
#تعریف_کرو GL_MAX_COLOR_FRAMEBUFFER_SAMPLES_AMD 0x91B3
#تعریف_کرو GL_MAX_COLOR_FRAMEBUFFER_STORAGE_SAMPLES_AMD 0x91B4
#تعریف_کرو GL_MAX_ڈونگھائی_STENCIL_FRAMEBUFFER_SAMPLES_AMD 0x91B5
#تعریف_کرو GL_عدد_SUPPORTED_MULTISAMPLE_MODES_AMD 0x91B6
#تعریف_کرو GL_SUPPORTED_MULTISAMPLE_MODES_AMD 0x91B7
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC) (GLenum نشانہ, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC) (GLuint renderbuffer, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glRenderbufferStorageMultisampleAdvancedAMD (GLenum نشانہ, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی);
GL_APICALL فراغ GL_APIENTRY glNamedRenderbufferStorageMultisampleAdvancedAMD (GLuint renderbuffer, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی);
#جے_انت
#جے_انت /* GL_AMD_framebuffer_multisample_advanced */

#جے_بنا_تعریف GL_AMD_performance_monitor
#تعریف_کرو GL_AMD_performance_monitor 1
#تعریف_کرو GL_COUNTER_TYPE_AMD               0x8BC0
#تعریف_کرو GL_COUNTER_RANGE_AMD              0x8BC1
#تعریف_کرو GL_UNSIGNED_INT64_AMD             0x8BC2
#تعریف_کرو GL_PERCENTAGE_AMD                 0x8BC3
#تعریف_کرو GL_PERFMON_نتیجہ_دستیاب_AMD   0x8BC4
#تعریف_کرو GL_PERFMON_نتیجہ_ناپ_AMD        0x8BC5
#تعریف_کرو GL_PERFMON_نتیجہ_AMD             0x8BC6
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFMONITORGROUPSAMDPROC) (GLint *عدد_Groups, GLsizei groups_ناپ, GLuint *groups);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFMONITORCOUNTERSAMDPROC) (GLuint گروہ, GLint *عدد_Counters, GLint *max_سرگرم_Counters, GLsizei counter_ناپ, GLuint *counters);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFMONITORGROUPSTRINGAMDPROC) (GLuint گروہ, GLsizei buf_ناپ, GLsizei *لمائی, GLchar *گروہ_String);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC) (GLuint گروہ, GLuint counter, GLsizei buf_ناپ, GLsizei *لمائی, GLchar *counterString);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFMONITORCOUNTERINFOAMDPROC) (GLuint گروہ, GLuint counter, GLenum pname, فراغ *انکڑے);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENPERFMONITORSAMDPROC) (GLsizei n, GLuint *monitors);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEPERFMONITORSAMDPROC) (GLsizei n, GLuint *monitors);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSELECTPERFMONITORCOUNTERSAMDPROC) (GLuint monitor, GLboolean enable, GLuint گروہ, GLint عدد_Counters, GLuint *counterList);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBEGINPERFMONITORAMDPROC) (GLuint monitor);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENDPERFMONITORAMDPROC) (GLuint monitor);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFMONITORCOUNTERDATAAMDPROC) (GLuint monitor, GLenum pname, GLsizei انکڑے_ناپ_2, GLuint *انکڑے, GLint *بائٹاں_Written);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glGetPerfMonitorGroupsAMD (GLint *عدد_Groups, GLsizei groups_ناپ, GLuint *groups);
GL_APICALL فراغ GL_APIENTRY glGetPerfMonitorCountersAMD (GLuint گروہ, GLint *عدد_Counters, GLint *max_سرگرم_Counters, GLsizei counter_ناپ, GLuint *counters);
GL_APICALL فراغ GL_APIENTRY gl_Get_Perf_Monitor_گروہ_String_AMD (GLuint گروہ, GLsizei buf_ناپ, GLsizei *لمائی, GLchar *گروہ_String);
GL_APICALL فراغ GL_APIENTRY glGetPerfMonitorCounterStringAMD (GLuint گروہ, GLuint counter, GLsizei buf_ناپ, GLsizei *لمائی, GLchar *counterString);
GL_APICALL فراغ GL_APIENTRY glGetPerfMonitorCounterInfoAMD (GLuint گروہ, GLuint counter, GLenum pname, فراغ *انکڑے);
GL_APICALL فراغ GL_APIENTRY glGenPerfMonitorsAMD (GLsizei n, GLuint *monitors);
GL_APICALL فراغ GL_APIENTRY glDeletePerfMonitorsAMD (GLsizei n, GLuint *monitors);
GL_APICALL فراغ GL_APIENTRY glSelectPerfMonitorCountersAMD (GLuint monitor, GLboolean enable, GLuint گروہ, GLint عدد_Counters, GLuint *counterList);
GL_APICALL فراغ GL_APIENTRY glBeginPerfMonitorAMD (GLuint monitor);
GL_APICALL فراغ GL_APIENTRY gl_سرا_Perf_Monitor_AMD (GLuint monitor);
GL_APICALL فراغ GL_APIENTRY gl_Get_Perf_Monitor_Counter_انکڑے_AMD (GLuint monitor, GLenum pname, GLsizei انکڑے_ناپ_2, GLuint *انکڑے, GLint *بائٹاں_Written);
#جے_انت
#جے_انت /* GL_AMD_performance_monitor */

#جے_بنا_تعریف GL_AMD_پروگرام_ثنائی_Z400
#تعریف_کرو GL_AMD_پروگرام_ثنائی_Z400 1
#تعریف_کرو GL_Z400_ثنائی_AMD                0x8740
#جے_انت /* GL_AMD_program_binary_Z400 */

#جے_بنا_تعریف GL_ANDROID_extension_pack_es31a
#تعریف_کرو GL_ANDROID_extension_pack_es31a 1
#جے_انت /* GL_ANDROID_extension_pack_es31a */

#جے_بنا_تعریف GL_ANGLE_ڈونگھائی_texture
#تعریف_کرو GL_ANGLE_ڈونگھائی_texture 1
#جے_انت /* GL_ANGLE_depth_texture */

#جے_بنا_تعریف GL_ANGLE_framebuffer_blit
#تعریف_کرو GL_ANGLE_framebuffer_blit 1
#تعریف_کرو GL_READ_FRAMEBUFFER_ANGLE         0x8CA8
#تعریف_کرو GL_DRAW_FRAMEBUFFER_ANGLE         0x8CA9
#تعریف_کرو GL_DRAW_FRAMEBUFFER_BINDING_ANGLE 0x8CA6
#تعریف_کرو GL_READ_FRAMEBUFFER_BINDING_ANGLE 0x8CAA
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLITFRAMEBUFFERANGLEPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield نقاب, GLenum filter);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glBlitFramebufferANGLE (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield نقاب, GLenum filter);
#جے_انت
#جے_انت /* GL_ANGLE_framebuffer_blit */

#جے_بنا_تعریف GL_ANGLE_framebuffer_multisample
#تعریف_کرو GL_ANGLE_framebuffer_multisample 1
#تعریف_کرو GL_RENDERBUFFER_SAMPLES_ANGLE     0x8CAB
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_ANGLE 0x8D56
#تعریف_کرو GL_MAX_SAMPLES_ANGLE              0x8D57
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEANGLEPROC) (GLenum نشانہ, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glRenderbufferStorageMultisampleANGLE (GLenum نشانہ, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی);
#جے_انت
#جے_انت /* GL_ANGLE_framebuffer_multisample */

#جے_بنا_تعریف GL_ANGLE_instanced_arrays
#تعریف_کرو GL_ANGLE_instanced_arrays 1
#تعریف_کرو GL_راس_ATTRIB_ARRAY_مقسوم_علیہ_ANGLE 0x88FE
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDANGLEPROC) (GLenum منوال, GLint پہلا, GLsizei گنتی, GLsizei primcount);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDANGLEPROC) (GLenum منوال, GLsizei گنتی, GLenum type, ثابت فراغ *indices, GLsizei primcount);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBDIVISORANGLEPROC) (GLuint اشاریہ, GLuint مقسوم_علیہ);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawArraysInstancedANGLE (GLenum منوال, GLint پہلا, GLsizei گنتی, GLsizei primcount);
GL_APICALL فراغ GL_APIENTRY glDrawElementsInstancedANGLE (GLenum منوال, GLsizei گنتی, GLenum type, ثابت فراغ *indices, GLsizei primcount);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib_مقسوم_علیہ_ANGLE (GLuint اشاریہ, GLuint مقسوم_علیہ);
#جے_انت
#جے_انت /* GL_ANGLE_instanced_arrays */

#جے_بنا_تعریف GL_ANGLE_pack_الٹ_صف_ترتیب
#تعریف_کرو GL_ANGLE_pack_الٹ_صف_ترتیب 1
#تعریف_کرو GL_PACK_الٹ_صف_ترتیب_ANGLE   0x93A4
#جے_انت /* GL_ANGLE_pack_reverse_row_order */

#جے_بنا_تعریف GL_ANGLE_پروگرام_ثنائی
#تعریف_کرو GL_ANGLE_پروگرام_ثنائی 1
#تعریف_کرو GL_پروگرام_ثنائی_ANGLE           0x93A6
#جے_انت /* GL_ANGLE_program_binary */

#جے_بنا_تعریف GL_ANGLE_texture_compression_dxt3
#تعریف_کرو GL_ANGLE_texture_compression_dxt3 1
#تعریف_کرو GL_COMPRESSED_RGBA_S3TC_DXT3_ANGLE 0x83F2
#جے_انت /* GL_ANGLE_texture_compression_dxt3 */

#جے_بنا_تعریف GL_ANGLE_texture_compression_dxt5
#تعریف_کرو GL_ANGLE_texture_compression_dxt5 1
#تعریف_کرو GL_COMPRESSED_RGBA_S3TC_DXT5_ANGLE 0x83F3
#جے_انت /* GL_ANGLE_texture_compression_dxt5 */

#جے_بنا_تعریف GL_ANGLE_texture_usage
#تعریف_کرو GL_ANGLE_texture_usage 1
#تعریف_کرو GL_TEXTURE_USAGE_ANGLE            0x93A2
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_ANGLE   0x93A3
#جے_انت /* GL_ANGLE_texture_usage */

#جے_بنا_تعریف GL_ANGLE_translated_shader_سروت
#تعریف_کرو GL_ANGLE_translated_shader_سروت 1
#تعریف_کرو GL_TRANSLATED_SHADER_سروت_لمائی_ANGLE 0x93A0
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTRANSLATEDSHADERSOURCEANGLEPROC) (GLuint shader, GLsizei buf_ناپ, GLsizei *لمائی, GLchar *سروت);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Get_Translated_Shader_سروت_ANGLE (GLuint shader, GLsizei buf_ناپ, GLsizei *لمائی, GLchar *سروت);
#جے_انت
#جے_انت /* GL_ANGLE_translated_shader_source */

#جے_بنا_تعریف GL_APPLE_clip_فاصلہ
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
#جے_انت /* GL_APPLE_clip_distance */

#جے_بنا_تعریف GL_APPLE_color_بفر_packed_float
#تعریف_کرو GL_APPLE_color_بفر_packed_float 1
#جے_انت /* GL_APPLE_color_buffer_packed_float */

#جے_بنا_تعریف GL_APPLE_copy_texture_پدھراں
#تعریف_کرو GL_APPLE_copy_texture_پدھراں 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYTEXTURELEVELSAPPLEPROC) (GLuint destinationTexture, GLuint سروت_Texture, GLint سروت_ادھار_Level, GLsizei سروت_Level_گنتی);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Copy_Texture_پدھراں_APPLE (GLuint destinationTexture, GLuint سروت_Texture, GLint سروت_ادھار_Level, GLsizei سروت_Level_گنتی);
#جے_انت
#جے_انت /* GL_APPLE_copy_texture_levels */

#جے_بنا_تعریف GL_APPLE_framebuffer_multisample
#تعریف_کرو GL_APPLE_framebuffer_multisample 1
#تعریف_کرو GL_RENDERBUFFER_SAMPLES_APPLE     0x8CAB
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_APPLE 0x8D56
#تعریف_کرو GL_MAX_SAMPLES_APPLE              0x8D57
#تعریف_کرو GL_READ_FRAMEBUFFER_APPLE         0x8CA8
#تعریف_کرو GL_DRAW_FRAMEBUFFER_APPLE         0x8CA9
#تعریف_کرو GL_DRAW_FRAMEBUFFER_BINDING_APPLE 0x8CA6
#تعریف_کرو GL_READ_FRAMEBUFFER_BINDING_APPLE 0x8CAA
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEAPPLEPROC) (GLenum نشانہ, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRESOLVEMULTISAMPLEFRAMEBUFFERAPPLEPROC) (فراغ);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glRenderbufferStorageMultisampleAPPLE (GLenum نشانہ, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی);
GL_APICALL فراغ GL_APIENTRY glResolveMultisampleFramebufferAPPLE (فراغ);
#جے_انت
#جے_انت /* GL_APPLE_framebuffer_multisample */

#جے_بنا_تعریف GL_APPLE_rgb_422
#تعریف_کرو GL_APPLE_rgb_422 1
#تعریف_کرو GL_RGB_422_APPLE                  0x8A1F
#تعریف_کرو GL_UNSIGNED_SHORT_8_8_APPLE       0x85BA
#تعریف_کرو GL_UNSIGNED_SHORT_8_8_REV_APPLE   0x85BB
#تعریف_کرو GL_RGB_RAW_422_APPLE              0x8A51
#جے_انت /* GL_APPLE_rgb_422 */

#جے_بنا_تعریف GL_APPLE_sync
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
تعريفنوع GLsync (GL_APIENTRYP PFNGLFENCESYNCAPPLEPROC) (GLenum condition, GLbitfield flags);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISSYNCAPPLEPROC) (GLsync sync);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETESYNCAPPLEPROC) (GLsync sync);
تعريفنوع GLenum (GL_APIENTRYP PFNGLCLIENTWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
تعريفنوع فراغ (GL_APIENTRYP PFNGLWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTEGER64VAPPLEPROC) (GLenum pname, GLint64 *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSYNCIVAPPLEPROC) (GLsync sync, GLenum pname, GLsizei گنتی, GLsizei *لمائی, GLint *اقدار);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL GLsync GL_APIENTRY glFenceSyncAPPLE (GLenum condition, GLbitfield flags);
GL_APICALL GLboolean GL_APIENTRY glIsSyncAPPLE (GLsync sync);
GL_APICALL فراغ GL_APIENTRY glDeleteSyncAPPLE (GLsync sync);
GL_APICALL GLenum GL_APIENTRY glClientWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_APICALL فراغ GL_APIENTRY glWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_APICALL فراغ GL_APIENTRY glGetInteger64vAPPLE (GLenum pname, GLint64 *params);
GL_APICALL فراغ GL_APIENTRY glGetSyncivAPPLE (GLsync sync, GLenum pname, GLsizei گنتی, GLsizei *لمائی, GLint *اقدار);
#جے_انت
#جے_انت /* GL_APPLE_sync */

#جے_بنا_تعریف GL_APPLE_texture_format_BGRA8888
#تعریف_کرو GL_APPLE_texture_format_BGRA8888 1
#تعریف_کرو GL_BGRA_EXT                       0x80E1
#تعریف_کرو GL_BGRA8_EXT                      0x93A1
#جے_انت /* GL_APPLE_texture_format_BGRA8888 */

#جے_بنا_تعریف GL_APPLE_texture_max_level
#تعریف_کرو GL_APPLE_texture_max_level 1
#تعریف_کرو GL_TEXTURE_MAX_LEVEL_APPLE        0x813D
#جے_انت /* GL_APPLE_texture_max_level */

#جے_بنا_تعریف GL_APPLE_texture_packed_float
#تعریف_کرو GL_APPLE_texture_packed_float 1
#تعریف_کرو GL_UNSIGNED_INT_10F_11F_11F_REV_APPLE 0x8C3B
#تعریف_کرو GL_UNSIGNED_INT_5_9_9_9_REV_APPLE 0x8C3E
#تعریف_کرو GL_R11F_G11F_B10F_APPLE           0x8C3A
#تعریف_کرو GL_RGB9_E5_APPLE                  0x8C3D
#جے_انت /* GL_APPLE_texture_packed_float */

#جے_بنا_تعریف GL_ARM_mali_پروگرام_ثنائی
#تعریف_کرو GL_ARM_mali_پروگرام_ثنائی 1
#تعریف_کرو GL_MALI_پروگرام_ثنائی_ARM        0x8F61
#جے_انت /* GL_ARM_mali_program_binary */

#جے_بنا_تعریف GL_ARM_mali_shader_ثنائی
#تعریف_کرو GL_ARM_mali_shader_ثنائی 1
#تعریف_کرو GL_MALI_SHADER_ثنائی_ARM         0x8F60
#جے_انت /* GL_ARM_mali_shader_binary */

#جے_بنا_تعریف GL_ARM_rgba8
#تعریف_کرو GL_ARM_rgba8 1
#جے_انت /* GL_ARM_rgba8 */

#جے_بنا_تعریف GL_ARM_shader_core_properties
#تعریف_کرو GL_ARM_shader_core_properties 1
#تعریف_کرو GL_SHADER_CORE_گنتی_ARM          0x96F0
#تعریف_کرو GL_SHADER_CORE_سرگرم_گنتی_ARM   0x96F1
#تعریف_کرو GL_SHADER_CORE_PRESENT_نقاب_ARM   0x96F2
#تعریف_کرو GL_SHADER_CORE_MAX_WARP_گنتی_ARM 0x96F3
#تعریف_کرو GL_SHADER_CORE_PIXEL_شرح_ARM     0x96F4
#تعریف_کرو GL_SHADER_CORE_TEXEL_شرح_ARM     0x96F5
#تعریف_کرو GL_SHADER_CORE_FMA_شرح_ARM       0x96F6
تعريفنوع فراغ (GL_APIENTRYP PFNGLMAXACTIVESHADERCORESARMPROC) (GLuint گنتی);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Max_سرگرم_Shader_Cores_ARM (GLuint گنتی);
#جے_انت
#جے_انت /* GL_ARM_shader_core_properties */

#جے_بنا_تعریف GL_ARM_shader_framebuffer_fetch
#تعریف_کرو GL_ARM_shader_framebuffer_fetch 1
#تعریف_کرو GL_FETCH_فی_SAMPLE_ARM           0x8F65
#تعریف_کرو GL_FRAGMENT_SHADER_FRAMEBUFFER_FETCH_MRT_ARM 0x8F66
#جے_انت /* GL_ARM_shader_framebuffer_fetch */

#جے_بنا_تعریف GL_ARM_shader_framebuffer_fetch_ڈونگھائی_stencil
#تعریف_کرو GL_ARM_shader_framebuffer_fetch_ڈونگھائی_stencil 1
#جے_انت /* GL_ARM_shader_framebuffer_fetch_depth_stencil */

#جے_بنا_تعریف GL_ARM_texture_unnormalized_coordinates
#تعریف_کرو GL_ARM_texture_unnormalized_coordinates 1
#تعریف_کرو GL_TEXTURE_UNNORMALIZED_COORDINATES_ARM 0x8F6A
#جے_انت /* GL_ARM_texture_unnormalized_coordinates */

#جے_بنا_تعریف GL_DMP_پروگرام_ثنائی
#تعریف_کرو GL_DMP_پروگرام_ثنائی 1
#تعریف_کرو GL_SMAPHS30_پروگرام_ثنائی_DMP    0x9251
#تعریف_کرو GL_SMAPHS_پروگرام_ثنائی_DMP      0x9252
#تعریف_کرو GL_DMP_پروگرام_ثنائی_DMP         0x9253
#جے_انت /* GL_DMP_program_binary */

#جے_بنا_تعریف GL_DMP_shader_ثنائی
#تعریف_کرو GL_DMP_shader_ثنائی 1
#تعریف_کرو GL_SHADER_ثنائی_DMP              0x9250
#جے_انت /* GL_DMP_shader_binary */

#جے_بنا_تعریف GL_EXT_EGL_image_array
#تعریف_کرو GL_EXT_EGL_image_array 1
#جے_انت /* GL_EXT_EGL_image_array */

#جے_بنا_تعریف GL_EXT_EGL_image_storage
#تعریف_کرو GL_EXT_EGL_image_storage 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLEGLIMAGETARGETTEXSTORAGEEXTPROC) (GLenum نشانہ, GLeglImageOES image, ثابت GLint* attrib_list);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEGLIMAGETARGETTEXTURESTORAGEEXTPROC) (GLuint texture, GLeglImageOES image, ثابت GLint* attrib_list);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_EGLImage_نشانہ_Tex_Storage_EXT (GLenum نشانہ, GLeglImageOES image, ثابت GLint* attrib_list);
GL_APICALL فراغ GL_APIENTRY gl_EGLImage_نشانہ_Texture_Storage_EXT (GLuint texture, GLeglImageOES image, ثابت GLint* attrib_list);
#جے_انت
#جے_انت /* GL_EXT_EGL_image_storage */

#جے_بنا_تعریف GL_EXT_EGL_image_storage_compression
#تعریف_کرو GL_EXT_EGL_image_storage_compression 1
#تعریف_کرو GL_SURFACE_COMPRESSION_EXT        0x96C0
#تعریف_کرو GL_SURFACE_COMPRESSION_FIXED_شرح_NONE_EXT 0x96C1
#تعریف_کرو GL_SURFACE_COMPRESSION_FIXED_شرح_DEFAULT_EXT 0x96C2
#جے_انت /* GL_EXT_EGL_image_storage_compression */

#جے_بنا_تعریف GL_EXT_YUV_نشانہ
#تعریف_کرو GL_EXT_YUV_نشانہ 1
#تعریف_کرو GL_SAMPLER_EXTERNAL_2D_Y2Y_EXT    0x8BE7
#جے_انت /* GL_EXT_YUV_target */

#جے_بنا_تعریف GL_EXT_ادھار_instance
#تعریف_کرو GL_EXT_ادھار_instance 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEEXTPROC) (GLenum منوال, GLint پہلا, GLsizei گنتی, GLsizei instancecount, GLuint baseinstance);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEEXTPROC) (GLenum منوال, GLsizei گنتی, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLuint baseinstance);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEEXTPROC) (GLenum منوال, GLsizei گنتی, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Draw_Arrays_Instanced_ادھار_Instance_EXT (GLenum منوال, GLint پہلا, GLsizei گنتی, GLsizei instancecount, GLuint baseinstance);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Elements_Instanced_ادھار_Instance_EXT (GLenum منوال, GLsizei گنتی, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLuint baseinstance);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Elements_Instanced_ادھار_راس_ادھار_Instance_EXT (GLenum منوال, GLsizei گنتی, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance);
#جے_انت
#جے_انت /* GL_EXT_base_instance */

#جے_بنا_تعریف GL_EXT_blend_func_extended
#تعریف_کرو GL_EXT_blend_func_extended 1
#تعریف_کرو GL_SRC1_COLOR_EXT                 0x88F9
#تعریف_کرو GL_SRC1_ALPHA_EXT                 0x8589
#تعریف_کرو GL_ONE_MINUS_SRC1_COLOR_EXT       0x88FA
#تعریف_کرو GL_ONE_MINUS_SRC1_ALPHA_EXT       0x88FB
#تعریف_کرو GL_SRC_ALPHA_SATURATE_EXT         0x0308
#تعریف_کرو GL_LOCATION_اشاریہ_EXT             0x930F
#تعریف_کرو GL_MAX_DUAL_سروت_DRAW_BUFFERS_EXT 0x88FC
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDFRAGDATALOCATIONINDEXEDEXTPROC) (GLuint پروگرام, GLuint color_نمبر, GLuint اشاریہ, ثابت GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDFRAGDATALOCATIONEXTPROC) (GLuint پروگرام, GLuint color, ثابت GLchar *name);
تعريفنوع GLint (GL_APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONINDEXEXTPROC) (GLuint پروگرام, GLenum پروگرام_Interface, ثابت GLchar *name);
تعريفنوع GLint (GL_APIENTRYP PFNGLGETFRAGDATAINDEXEXTPROC) (GLuint پروگرام, ثابت GLchar *name);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Bind_Frag_انکڑے_Location_اشاریہ_دار_EXT (GLuint پروگرام, GLuint color_نمبر, GLuint اشاریہ, ثابت GLchar *name);
GL_APICALL فراغ GL_APIENTRY gl_Bind_Frag_انکڑے_Location_EXT (GLuint پروگرام, GLuint color, ثابت GLchar *name);
GL_APICALL GLint GL_APIENTRY gl_Get_پروگرام_Resource_Location_اشاریہ_EXT (GLuint پروگرام, GLenum پروگرام_Interface, ثابت GLchar *name);
GL_APICALL GLint GL_APIENTRY gl_Get_Frag_انکڑے_اشاریہ_EXT (GLuint پروگرام, ثابت GLchar *name);
#جے_انت
#جے_انت /* GL_EXT_blend_func_extended */

#جے_بنا_تعریف GL_EXT_blend_minmax
#تعریف_کرو GL_EXT_blend_minmax 1
#تعریف_کرو GL_MIN_EXT                        0x8007
#تعریف_کرو GL_MAX_EXT                        0x8008
#جے_انت /* GL_EXT_blend_minmax */

#جے_بنا_تعریف GL_EXT_بفر_storage
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
تعريفنوع فراغ (GL_APIENTRYP PFNGLBUFFERSTORAGEEXTPROC) (GLenum نشانہ, GLsizeiptr ناپ, ثابت فراغ *انکڑے, GLbitfield flags);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_بفر_Storage_EXT (GLenum نشانہ, GLsizeiptr ناپ, ثابت فراغ *انکڑے, GLbitfield flags);
#جے_انت
#جے_انت /* GL_EXT_buffer_storage */

#جے_بنا_تعریف GL_EXT_clear_texture
#تعریف_کرو GL_EXT_clear_texture 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARTEXIMAGEEXTPROC) (GLuint texture, GLint level, GLenum format, GLenum type, ثابت فراغ *انکڑے);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARTEXSUBIMAGEEXTPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2, GLenum format, GLenum type, ثابت فراغ *انکڑے);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glClearTexImageEXT (GLuint texture, GLint level, GLenum format, GLenum type, ثابت فراغ *انکڑے);
GL_APICALL فراغ GL_APIENTRY glClearTexSubImageEXT (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2, GLenum format, GLenum type, ثابت فراغ *انکڑے);
#جے_انت
#جے_انت /* GL_EXT_clear_texture */

#جے_بنا_تعریف GL_EXT_clip_control
#تعریف_کرو GL_EXT_clip_control 1
#تعریف_کرو GL_ہیٹھلا_بایاں_EXT                 0x8CA1
#تعریف_کرو GL_اتلا_بایاں_EXT                 0x8CA2
#تعریف_کرو GL_NEGATIVE_ONE_منزل_ONE_EXT        0x935E
#تعریف_کرو GL_ZERO_منزل_ONE_EXT                0x935F
#تعریف_کرو GL_CLIP_ORIGIN_EXT                0x935C
#تعریف_کرو GL_CLIP_ڈونگھائی_منوال_EXT            0x935D
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLIPCONTROLEXTPROC) (GLenum origin, GLenum ڈونگھائی_2);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glClipControlEXT (GLenum origin, GLenum ڈونگھائی_2);
#جے_انت
#جے_انت /* GL_EXT_clip_control */

#جے_بنا_تعریف GL_EXT_clip_cull_فاصلہ
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
#جے_انت /* GL_EXT_clip_cull_distance */

#جے_بنا_تعریف GL_EXT_color_بفر_float
#تعریف_کرو GL_EXT_color_بفر_float 1
#جے_انت /* GL_EXT_color_buffer_float */

#جے_بنا_تعریف GL_EXT_color_بفر_half_float
#تعریف_کرو GL_EXT_color_بفر_half_float 1
#تعریف_کرو GL_RGBA16F_EXT                    0x881A
#تعریف_کرو GL_RGB16F_EXT                     0x881B
#تعریف_کرو GL_RG16F_EXT                      0x822F
#تعریف_کرو GL_R16F_EXT                       0x822D
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE_EXT 0x8211
#تعریف_کرو GL_UNSIGNED_NORMALIZED_EXT        0x8C17
#جے_انت /* GL_EXT_color_buffer_half_float */

#جے_بنا_تعریف GL_EXT_conservative_ڈونگھائی
#تعریف_کرو GL_EXT_conservative_ڈونگھائی 1
#جے_انت /* GL_EXT_conservative_depth */

#جے_بنا_تعریف GL_EXT_copy_image
#تعریف_کرو GL_EXT_copy_image 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYIMAGESUBDATAEXTPROC) (GLuint srcName, GLenum src_نشانہ, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dst_نشانہ, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei src_چوڑائی, GLsizei src_اچائی, GLsizei src_ڈونگھائی);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Copy_Image_Sub_انکڑے_EXT (GLuint srcName, GLenum src_نشانہ, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dst_نشانہ, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei src_چوڑائی, GLsizei src_اچائی, GLsizei src_ڈونگھائی);
#جے_انت
#جے_انت /* GL_EXT_copy_image */

#جے_بنا_تعریف GL_EXT_debug_label
#تعریف_کرو GL_EXT_debug_label 1
#تعریف_کرو GL_پروگرام_PIPELINE_OBJECT_EXT    0x8A4F
#تعریف_کرو GL_پروگرام_OBJECT_EXT             0x8B40
#تعریف_کرو GL_SHADER_OBJECT_EXT              0x8B48
#تعریف_کرو GL_بفر_OBJECT_EXT              0x9151
#تعریف_کرو GL_QUERY_OBJECT_EXT               0x9153
#تعریف_کرو GL_راس_ARRAY_OBJECT_EXT        0x9154
#تعریف_کرو GL_TRANSFORM_FEEDBACK             0x8E22
تعريفنوع فراغ (GL_APIENTRYP PFNGLLABELOBJECTEXTPROC) (GLenum type, GLuint object, GLsizei لمائی, ثابت GLchar *label);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETOBJECTLABELEXTPROC) (GLenum type, GLuint object, GLsizei buf_ناپ, GLsizei *لمائی, GLchar *label);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glLabelObjectEXT (GLenum type, GLuint object, GLsizei لمائی, ثابت GLchar *label);
GL_APICALL فراغ GL_APIENTRY glGetObjectLabelEXT (GLenum type, GLuint object, GLsizei buf_ناپ, GLsizei *لمائی, GLchar *label);
#جے_انت
#جے_انت /* GL_EXT_debug_label */

#جے_بنا_تعریف GL_EXT_debug_marker
#تعریف_کرو GL_EXT_debug_marker 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLINSERTEVENTMARKEREXTPROC) (GLsizei لمائی, ثابت GLchar *marker);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPUSHGROUPMARKEREXTPROC) (GLsizei لمائی, ثابت GLchar *marker);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOPGROUPMARKEREXTPROC) (فراغ);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_داخل_کرو_Event_Marker_EXT (GLsizei لمائی, ثابت GLchar *marker);
GL_APICALL فراغ GL_APIENTRY gl_ڈالو_گروہ_Marker_EXT (GLsizei لمائی, ثابت GLchar *marker);
GL_APICALL فراغ GL_APIENTRY gl_نکالو_گروہ_Marker_EXT (فراغ);
#جے_انت
#جے_انت /* GL_EXT_debug_marker */

#جے_بنا_تعریف GL_EXT_ڈونگھائی_clamp
#تعریف_کرو GL_EXT_ڈونگھائی_clamp 1
#تعریف_کرو GL_ڈونگھائی_CLAMP_EXT                0x864F
#جے_انت /* GL_EXT_depth_clamp */

#جے_بنا_تعریف GL_EXT_discard_framebuffer
#تعریف_کرو GL_EXT_discard_framebuffer 1
#تعریف_کرو GL_COLOR_EXT                      0x1800
#تعریف_کرو GL_ڈونگھائی_EXT                      0x1801
#تعریف_کرو GL_STENCIL_EXT                    0x1802
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISCARDFRAMEBUFFEREXTPROC) (GLenum نشانہ, GLsizei عدد_Attachments, ثابت GLenum *attachments);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDiscardFramebufferEXT (GLenum نشانہ, GLsizei عدد_Attachments, ثابت GLenum *attachments);
#جے_انت
#جے_انت /* GL_EXT_discard_framebuffer */

#جے_بنا_تعریف GL_EXT_disjoint_timer_query
#تعریف_کرو GL_EXT_disjoint_timer_query 1
#تعریف_کرو GL_QUERY_COUNTER_بٹ_EXT         0x8864
#تعریف_کرو GL_CURRENT_QUERY_EXT              0x8865
#تعریف_کرو GL_QUERY_نتیجہ_EXT               0x8866
#تعریف_کرو GL_QUERY_نتیجہ_دستیاب_EXT     0x8867
#تعریف_کرو GL_ویلا_ELAPSED_EXT               0x88BF
#تعریف_کرو GL_TIMESTAMP_EXT                  0x8E28
#تعریف_کرو GL_GPU_DISJOINT_EXT               0x8FBB
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENQUERIESEXTPROC) (GLsizei n, GLuint *ids);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEQUERIESEXTPROC) (GLsizei n, ثابت GLuint *ids);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISQUERYEXTPROC) (GLuint id);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBEGINQUERYEXTPROC) (GLenum نشانہ, GLuint id);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENDQUERYEXTPROC) (GLenum نشانہ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLQUERYCOUNTEREXTPROC) (GLuint id, GLenum نشانہ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETQUERYIVEXTPROC) (GLenum نشانہ, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETQUERYOBJECTIVEXTPROC) (GLuint id, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETQUERYOBJECTUIVEXTPROC) (GLuint id, GLenum pname, GLuint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETQUERYOBJECTI64VEXTPROC) (GLuint id, GLenum pname, GLint64 *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETQUERYOBJECTUI64VEXTPROC) (GLuint id, GLenum pname, GLuint64 *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTEGER64VEXTPROC) (GLenum pname, GLint64 *انکڑے);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glGenQueriesEXT (GLsizei n, GLuint *ids);
GL_APICALL فراغ GL_APIENTRY glDeleteQueriesEXT (GLsizei n, ثابت GLuint *ids);
GL_APICALL GLboolean GL_APIENTRY glIsQueryEXT (GLuint id);
GL_APICALL فراغ GL_APIENTRY glBeginQueryEXT (GLenum نشانہ, GLuint id);
GL_APICALL فراغ GL_APIENTRY gl_سرا_Query_EXT (GLenum نشانہ);
GL_APICALL فراغ GL_APIENTRY glQueryCounterEXT (GLuint id, GLenum نشانہ);
GL_APICALL فراغ GL_APIENTRY glGetQueryivEXT (GLenum نشانہ, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetQueryObjectivEXT (GLuint id, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetQueryObjectuivEXT (GLuint id, GLenum pname, GLuint *params);
GL_APICALL فراغ GL_APIENTRY glGetQueryObjecti64vEXT (GLuint id, GLenum pname, GLint64 *params);
GL_APICALL فراغ GL_APIENTRY glGetQueryObjectui64vEXT (GLuint id, GLenum pname, GLuint64 *params);
GL_APICALL فراغ GL_APIENTRY glGetInteger64vEXT (GLenum pname, GLint64 *انکڑے);
#جے_انت
#جے_انت /* GL_EXT_disjoint_timer_query */

#جے_بنا_تعریف GL_EXT_draw_buffers
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
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWBUFFERSEXTPROC) (GLsizei n, ثابت GLenum *bufs);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawBuffersEXT (GLsizei n, ثابت GLenum *bufs);
#جے_انت
#جے_انت /* GL_EXT_draw_buffers */

#جے_بنا_تعریف GL_EXT_draw_buffers_اشاریہ_دار
#تعریف_کرو GL_EXT_draw_buffers_اشاریہ_دار 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLENABLEIEXTPROC) (GLenum نشانہ, GLuint اشاریہ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISABLEIEXTPROC) (GLenum نشانہ, GLuint اشاریہ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONIEXTPROC) (GLuint buf, GLenum منوال);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEIEXTPROC) (GLuint buf, GLenum منوال_RGB, GLenum منوال_Alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDFUNCIEXTPROC) (GLuint buf, GLenum src, GLenum dst);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEIEXTPROC) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOLORMASKIEXTPROC) (GLuint اشاریہ, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISENABLEDIEXTPROC) (GLenum نشانہ, GLuint اشاریہ);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glEnableiEXT (GLenum نشانہ, GLuint اشاریہ);
GL_APICALL فراغ GL_APIENTRY glDisableiEXT (GLenum نشانہ, GLuint اشاریہ);
GL_APICALL فراغ GL_APIENTRY glBlendEquationiEXT (GLuint buf, GLenum منوال);
GL_APICALL فراغ GL_APIENTRY glBlendEquationSeparateiEXT (GLuint buf, GLenum منوال_RGB, GLenum منوال_Alpha);
GL_APICALL فراغ GL_APIENTRY glBlendFunciEXT (GLuint buf, GLenum src, GLenum dst);
GL_APICALL فراغ GL_APIENTRY glBlendFuncSeparateiEXT (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
GL_APICALL فراغ GL_APIENTRY glColorMaskiEXT (GLuint اشاریہ, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
GL_APICALL GLboolean GL_APIENTRY glIsEnablediEXT (GLenum نشانہ, GLuint اشاریہ);
#جے_انت
#جے_انت /* GL_EXT_draw_buffers_indexed */

#جے_بنا_تعریف GL_EXT_draw_elements_ادھار_راس
#تعریف_کرو GL_EXT_draw_elements_ادھار_راس 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSBASEVERTEXEXTPROC) (GLenum منوال, GLsizei گنتی, GLenum type, ثابت فراغ *indices, GLint basevertex);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWRANGEELEMENTSBASEVERTEXEXTPROC) (GLenum منوال, GLuint شروع, GLuint سرا, GLsizei گنتی, GLenum type, ثابت فراغ *indices, GLint basevertex);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXEXTPROC) (GLenum منوال, GLsizei گنتی, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLint basevertex);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Draw_Elements_ادھار_راس_EXT (GLenum منوال, GLsizei گنتی, GLenum type, ثابت فراغ *indices, GLint basevertex);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Range_Elements_ادھار_راس_EXT (GLenum منوال, GLuint شروع, GLuint سرا, GLsizei گنتی, GLenum type, ثابت فراغ *indices, GLint basevertex);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Elements_Instanced_ادھار_راس_EXT (GLenum منوال, GLsizei گنتی, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLint basevertex);
#جے_انت
#جے_انت /* GL_EXT_draw_elements_base_vertex */

#جے_بنا_تعریف GL_EXT_draw_instanced
#تعریف_کرو GL_EXT_draw_instanced 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDEXTPROC) (GLenum منوال, GLint شروع, GLsizei گنتی, GLsizei primcount);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDEXTPROC) (GLenum منوال, GLsizei گنتی, GLenum type, ثابت فراغ *indices, GLsizei primcount);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawArraysInstancedEXT (GLenum منوال, GLint شروع, GLsizei گنتی, GLsizei primcount);
GL_APICALL فراغ GL_APIENTRY glDrawElementsInstancedEXT (GLenum منوال, GLsizei گنتی, GLenum type, ثابت فراغ *indices, GLsizei primcount);
#جے_انت
#جے_انت /* GL_EXT_draw_instanced */

#جے_بنا_تعریف GL_EXT_draw_transform_feedback
#تعریف_کرو GL_EXT_draw_transform_feedback 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKEXTPROC) (GLenum منوال, GLuint id);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDEXTPROC) (GLenum منوال, GLuint id, GLsizei instancecount);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawTransformFeedbackEXT (GLenum منوال, GLuint id);
GL_APICALL فراغ GL_APIENTRY glDrawTransformFeedbackInstancedEXT (GLenum منوال, GLuint id, GLsizei instancecount);
#جے_انت
#جے_انت /* GL_EXT_draw_transform_feedback */

#جے_بنا_تعریف GL_EXT_external_بفر
#تعریف_کرو GL_EXT_external_بفر 1
تعريفنوع فراغ *GLegl_Client_بفر_EXT;
تعريفنوع فراغ (GL_APIENTRYP PFNGLBUFFERSTORAGEEXTERNALEXTPROC) (GLenum نشانہ, GLintptr وتھ_2, GLsizeiptr ناپ, GLegl_Client_بفر_EXT client_بفر, GLbitfield flags);
تعريفنوع فراغ (GL_APIENTRYP PFNGLNAMEDBUFFERSTORAGEEXTERNALEXTPROC) (GLuint بفر_2, GLintptr وتھ_2, GLsizeiptr ناپ, GLegl_Client_بفر_EXT client_بفر, GLbitfield flags);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_بفر_Storage_External_EXT (GLenum نشانہ, GLintptr وتھ_2, GLsizeiptr ناپ, GLegl_Client_بفر_EXT client_بفر, GLbitfield flags);
GL_APICALL فراغ GL_APIENTRY gl_Named_بفر_Storage_External_EXT (GLuint بفر_2, GLintptr وتھ_2, GLsizeiptr ناپ, GLegl_Client_بفر_EXT client_بفر, GLbitfield flags);
#جے_انت
#جے_انت /* GL_EXT_external_buffer */

#جے_بنا_تعریف GL_EXT_float_blend
#تعریف_کرو GL_EXT_float_blend 1
#جے_انت /* GL_EXT_float_blend */

#جے_بنا_تعریف GL_EXT_fragment_shading_شرح
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
#تعریف_کرو GL_MIN_FRAGMENT_SHADING_شرح_ATTACHMENT_TEXEL_اچائی_EXT 0x96D9
#تعریف_کرو GL_MAX_FRAGMENT_SHADING_شرح_ATTACHMENT_TEXEL_اچائی_EXT 0x96DA
#تعریف_کرو GL_MAX_FRAGMENT_SHADING_شرح_ATTACHMENT_TEXEL_ASPECT_تناسب_EXT 0x96DB
#تعریف_کرو GL_MAX_FRAGMENT_SHADING_شرح_ATTACHMENT_LAYERS_EXT 0x96DC
#تعریف_کرو GL_FRAGMENT_SHADING_شرح_WITH_SHADER_ڈونگھائی_STENCIL_WRITES_SUPPORTED_EXT 0x96DD
#تعریف_کرو GL_FRAGMENT_SHADING_شرح_WITH_SAMPLE_نقاب_SUPPORTED_EXT 0x96DE
#تعریف_کرو GL_FRAGMENT_SHADING_شرح_ATTACHMENT_WITH_DEFAULT_FRAMEBUFFER_SUPPORTED_EXT 0x96DF
#تعریف_کرو GL_FRAGMENT_SHADING_شرح_NON_TRIVIAL_COMBINERS_SUPPORTED_EXT 0x8F6F
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFRAGMENTSHADINGRATESEXTPROC) (GLsizei samples, GLsizei max_گنتی, GLsizei *گنتی, GLenum *shadingRates);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADINGRATEEXTPROC) (GLenum شرح);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADINGRATECOMBINEROPSEXTPROC) (GLenum combinerOp0, GLenum combinerOp1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERSHADINGRATEEXTPROC) (GLenum نشانہ, GLenum attachment, GLuint texture, GLint ادھار_Layer, GLsizei عدد_Layers, GLsizei texel_چوڑائی, GLsizei texel_اچائی);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glGetFragmentShadingRatesEXT (GLsizei samples, GLsizei max_گنتی, GLsizei *گنتی, GLenum *shadingRates);
GL_APICALL فراغ GL_APIENTRY gl_Shading_شرح_EXT (GLenum شرح);
GL_APICALL فراغ GL_APIENTRY gl_Shading_شرح_Combiner_Ops_EXT (GLenum combinerOp0, GLenum combinerOp1);
GL_APICALL فراغ GL_APIENTRY gl_Framebuffer_Shading_شرح_EXT (GLenum نشانہ, GLenum attachment, GLuint texture, GLint ادھار_Layer, GLsizei عدد_Layers, GLsizei texel_چوڑائی, GLsizei texel_اچائی);
#جے_انت
#جے_انت /* GL_EXT_fragment_shading_rate */

#جے_بنا_تعریف GL_EXT_framebuffer_blit_layers
#تعریف_کرو GL_EXT_framebuffer_blit_layers 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLITFRAMEBUFFERLAYERSEXTPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield نقاب, GLenum filter);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLITFRAMEBUFFERLAYEREXTPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint srcLayer, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLint dstLayer, GLbitfield نقاب, GLenum filter);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glBlitFramebufferLayersEXT (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield نقاب, GLenum filter);
GL_APICALL فراغ GL_APIENTRY glBlitFramebufferLayerEXT (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint srcLayer, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLint dstLayer, GLbitfield نقاب, GLenum filter);
#جے_انت
#جے_انت /* GL_EXT_framebuffer_blit_layers */

#جے_بنا_تعریف GL_EXT_geometry_نقطہ_ناپ
#تعریف_کرو GL_EXT_geometry_نقطہ_ناپ 1
#جے_انت /* GL_EXT_geometry_point_size */

#جے_بنا_تعریف GL_EXT_geometry_shader
#تعریف_کرو GL_EXT_geometry_shader 1
#تعریف_کرو GL_GEOMETRY_SHADER_EXT            0x8DD9
#تعریف_کرو GL_GEOMETRY_SHADER_ثنائی_ہندسہ_EXT        0x00000004
#تعریف_کرو GL_GEOMETRY_LINKED_VERTICES_باہرلا_EXT 0x8916
#تعریف_کرو GL_GEOMETRY_LINKED_داخلہ_TYPE_EXT 0x8917
#تعریف_کرو GL_GEOMETRY_LINKED_OUTPUT_TYPE_EXT 0x8918
#تعریف_کرو GL_GEOMETRY_SHADER_INVOCATIONS_EXT 0x887F
#تعریف_کرو GL_LAYER_PROVOKING_راس_EXT     0x825E
#تعریف_کرو GL_سطریں_ADJACENCY_EXT            0x000A
#تعریف_کرو GL_سطر_STRIP_ADJACENCY_EXT       0x000B
#تعریف_کرو GL_TRIANGLES_ADJACENCY_EXT        0x000C
#تعریف_کرو GL_TRIANGLE_STRIP_ADJACENCY_EXT   0x000D
#تعریف_کرو GL_MAX_GEOMETRY_اکسار_COMPONENTS_EXT 0x8DDF
#تعریف_کرو GL_MAX_GEOMETRY_اکسار_بلاکاں_EXT 0x8A2C
#تعریف_کرو GL_MAX_COMBINED_GEOMETRY_اکسار_COMPONENTS_EXT 0x8A32
#تعریف_کرو GL_MAX_GEOMETRY_داخلہ_COMPONENTS_EXT 0x9123
#تعریف_کرو GL_MAX_GEOMETRY_OUTPUT_COMPONENTS_EXT 0x9124
#تعریف_کرو GL_MAX_GEOMETRY_OUTPUT_VERTICES_EXT 0x8DE0
#تعریف_کرو GL_MAX_GEOMETRY_کل_OUTPUT_COMPONENTS_EXT 0x8DE1
#تعریف_کرو GL_MAX_GEOMETRY_SHADER_INVOCATIONS_EXT 0x8E5A
#تعریف_کرو GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_EXT 0x8C29
#تعریف_کرو GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS_EXT 0x92CF
#تعریف_کرو GL_MAX_GEOMETRY_ATOMIC_COUNTERS_EXT 0x92D5
#تعریف_کرو GL_MAX_GEOMETRY_IMAGE_UNIFORMS_EXT 0x90CD
#تعریف_کرو GL_MAX_GEOMETRY_SHADER_STORAGE_بلاکاں_EXT 0x90D7
#تعریف_کرو GL_پہلا_راس_CONVENTION_EXT    0x8E4D
#تعریف_کرو GL_آخری_راس_CONVENTION_EXT     0x8E4E
#تعریف_کرو GL_UNDEFINED_راس_EXT           0x8260
#تعریف_کرو GL_PRIMITIVES_GENERATED_EXT       0x8C87
#تعریف_کرو GL_FRAMEBUFFER_DEFAULT_LAYERS_EXT 0x9312
#تعریف_کرو GL_MAX_FRAMEBUFFER_LAYERS_EXT     0x9317
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_EXT 0x8DA8
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_LAYERED_EXT 0x8DA7
#تعریف_کرو GL_REFERENCED_BY_GEOMETRY_SHADER_EXT 0x9309
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREEXTPROC) (GLenum نشانہ, GLenum attachment, GLuint texture, GLint level);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferTextureEXT (GLenum نشانہ, GLenum attachment, GLuint texture, GLint level);
#جے_انت
#جے_انت /* GL_EXT_geometry_shader */

#جے_بنا_تعریف GL_EXT_gpu_shader5
#تعریف_کرو GL_EXT_gpu_shader5 1
#جے_انت /* GL_EXT_gpu_shader5 */

#جے_بنا_تعریف GL_EXT_instanced_arrays
#تعریف_کرو GL_EXT_instanced_arrays 1
#تعریف_کرو GL_راس_ATTRIB_ARRAY_مقسوم_علیہ_EXT 0x88FE
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBDIVISOREXTPROC) (GLuint اشاریہ, GLuint مقسوم_علیہ);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib_مقسوم_علیہ_EXT (GLuint اشاریہ, GLuint مقسوم_علیہ);
#جے_انت
#جے_انت /* GL_EXT_instanced_arrays */

#جے_بنا_تعریف GL_EXT_map_بفر_range
#تعریف_کرو GL_EXT_map_بفر_range 1
#تعریف_کرو GL_MAP_READ_ثنائی_ہندسہ_EXT               0x0001
#تعریف_کرو GL_MAP_WRITE_ثنائی_ہندسہ_EXT              0x0002
#تعریف_کرو GL_MAP_INVALIDATE_RANGE_ثنائی_ہندسہ_EXT   0x0004
#تعریف_کرو GL_MAP_INVALIDATE_بفر_ثنائی_ہندسہ_EXT  0x0008
#تعریف_کرو GL_MAP_FLUSH_EXPLICIT_ثنائی_ہندسہ_EXT     0x0010
#تعریف_کرو GL_MAP_UNSYNCHRONIZED_ثنائی_ہندسہ_EXT     0x0020
تعريفنوع فراغ *(GL_APIENTRYP PFNGLMAPBUFFERRANGEEXTPROC) (GLenum نشانہ, GLintptr وتھ_2, GLsizeiptr لمائی, GLbitfield access);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEEXTPROC) (GLenum نشانہ, GLintptr وتھ_2, GLsizeiptr لمائی);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ *GL_APIENTRY gl_Map_بفر_Range_EXT (GLenum نشانہ, GLintptr وتھ_2, GLsizeiptr لمائی, GLbitfield access);
GL_APICALL فراغ GL_APIENTRY gl_Flush_Mapped_بفر_Range_EXT (GLenum نشانہ, GLintptr وتھ_2, GLsizeiptr لمائی);
#جے_انت
#جے_انت /* GL_EXT_map_buffer_range */

#جے_بنا_تعریف GL_EXT_حافظہ_object
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
#تعریف_کرو GL_UUID_ناپ_EXT                  16
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETUNSIGNEDBYTEVEXTPROC) (GLenum pname, GLubyte *انکڑے);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETUNSIGNEDBYTEI_VEXTPROC) (GLenum نشانہ, GLuint اشاریہ, GLubyte *انکڑے);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEMEMORYOBJECTSEXTPROC) (GLsizei n, ثابت GLuint *حافظہ_Objects);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISMEMORYOBJECTEXTPROC) (GLuint حافظہ_Object);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCREATEMEMORYOBJECTSEXTPROC) (GLsizei n, GLuint *حافظہ_Objects);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMEMORYOBJECTPARAMETERIVEXTPROC) (GLuint حافظہ_Object, GLenum pname, ثابت GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETMEMORYOBJECTPARAMETERIVEXTPROC) (GLuint حافظہ_Object, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGEMEM2DEXTPROC) (GLenum نشانہ, GLsizei پدھراں, GLenum اندرونی_Format, GLsizei چوڑائی, GLsizei اچائی, GLuint حافظہ, GLuint64 وتھ_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGEMEM2DMULTISAMPLEEXTPROC) (GLenum نشانہ, GLsizei samples, GLenum اندرونی_Format, GLsizei چوڑائی, GLsizei اچائی, GLboolean fixedSampleLocations, GLuint حافظہ, GLuint64 وتھ_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGEMEM3DEXTPROC) (GLenum نشانہ, GLsizei پدھراں, GLenum اندرونی_Format, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2, GLuint حافظہ, GLuint64 وتھ_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGEMEM3DMULTISAMPLEEXTPROC) (GLenum نشانہ, GLsizei samples, GLenum اندرونی_Format, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2, GLboolean fixedSampleLocations, GLuint حافظہ, GLuint64 وتھ_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBUFFERSTORAGEMEMEXTPROC) (GLenum نشانہ, GLsizeiptr ناپ, GLuint حافظہ, GLuint64 وتھ_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGEMEM2DEXTPROC) (GLuint texture, GLsizei پدھراں, GLenum اندرونی_Format, GLsizei چوڑائی, GLsizei اچائی, GLuint حافظہ, GLuint64 وتھ_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGEMEM2DMULTISAMPLEEXTPROC) (GLuint texture, GLsizei samples, GLenum اندرونی_Format, GLsizei چوڑائی, GLsizei اچائی, GLboolean fixedSampleLocations, GLuint حافظہ, GLuint64 وتھ_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGEMEM3DEXTPROC) (GLuint texture, GLsizei پدھراں, GLenum اندرونی_Format, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2, GLuint حافظہ, GLuint64 وتھ_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGEMEM3DMULTISAMPLEEXTPROC) (GLuint texture, GLsizei samples, GLenum اندرونی_Format, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2, GLboolean fixedSampleLocations, GLuint حافظہ, GLuint64 وتھ_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLNAMEDBUFFERSTORAGEMEMEXTPROC) (GLuint بفر_2, GLsizeiptr ناپ, GLuint حافظہ, GLuint64 وتھ_2);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glGetUnsignedBytevEXT (GLenum pname, GLubyte *انکڑے);
GL_APICALL فراغ GL_APIENTRY glGetUnsignedBytei_vEXT (GLenum نشانہ, GLuint اشاریہ, GLubyte *انکڑے);
GL_APICALL فراغ GL_APIENTRY gl_Delete_حافظہ_Objects_EXT (GLsizei n, ثابت GLuint *حافظہ_Objects);
GL_APICALL GLboolean GL_APIENTRY gl_Is_حافظہ_Object_EXT (GLuint حافظہ_Object);
GL_APICALL فراغ GL_APIENTRY gl_Create_حافظہ_Objects_EXT (GLsizei n, GLuint *حافظہ_Objects);
GL_APICALL فراغ GL_APIENTRY gl_حافظہ_Object_Parameteriv_EXT (GLuint حافظہ_Object, GLenum pname, ثابت GLint *params);
GL_APICALL فراغ GL_APIENTRY gl_Get_حافظہ_Object_Parameteriv_EXT (GLuint حافظہ_Object, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glTexStorageMem2DEXT (GLenum نشانہ, GLsizei پدھراں, GLenum اندرونی_Format, GLsizei چوڑائی, GLsizei اچائی, GLuint حافظہ, GLuint64 وتھ_2);
GL_APICALL فراغ GL_APIENTRY glTexStorageMem2DMultisampleEXT (GLenum نشانہ, GLsizei samples, GLenum اندرونی_Format, GLsizei چوڑائی, GLsizei اچائی, GLboolean fixedSampleLocations, GLuint حافظہ, GLuint64 وتھ_2);
GL_APICALL فراغ GL_APIENTRY glTexStorageMem3DEXT (GLenum نشانہ, GLsizei پدھراں, GLenum اندرونی_Format, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2, GLuint حافظہ, GLuint64 وتھ_2);
GL_APICALL فراغ GL_APIENTRY glTexStorageMem3DMultisampleEXT (GLenum نشانہ, GLsizei samples, GLenum اندرونی_Format, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2, GLboolean fixedSampleLocations, GLuint حافظہ, GLuint64 وتھ_2);
GL_APICALL فراغ GL_APIENTRY gl_بفر_Storage_Mem_EXT (GLenum نشانہ, GLsizeiptr ناپ, GLuint حافظہ, GLuint64 وتھ_2);
GL_APICALL فراغ GL_APIENTRY glTextureStorageMem2DEXT (GLuint texture, GLsizei پدھراں, GLenum اندرونی_Format, GLsizei چوڑائی, GLsizei اچائی, GLuint حافظہ, GLuint64 وتھ_2);
GL_APICALL فراغ GL_APIENTRY glTextureStorageMem2DMultisampleEXT (GLuint texture, GLsizei samples, GLenum اندرونی_Format, GLsizei چوڑائی, GLsizei اچائی, GLboolean fixedSampleLocations, GLuint حافظہ, GLuint64 وتھ_2);
GL_APICALL فراغ GL_APIENTRY glTextureStorageMem3DEXT (GLuint texture, GLsizei پدھراں, GLenum اندرونی_Format, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2, GLuint حافظہ, GLuint64 وتھ_2);
GL_APICALL فراغ GL_APIENTRY glTextureStorageMem3DMultisampleEXT (GLuint texture, GLsizei samples, GLenum اندرونی_Format, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2, GLboolean fixedSampleLocations, GLuint حافظہ, GLuint64 وتھ_2);
GL_APICALL فراغ GL_APIENTRY gl_Named_بفر_Storage_Mem_EXT (GLuint بفر_2, GLsizeiptr ناپ, GLuint حافظہ, GLuint64 وتھ_2);
#جے_انت
#جے_انت /* GL_EXT_memory_object */

#جے_بنا_تعریف GL_EXT_حافظہ_object_fd
#تعریف_کرو GL_EXT_حافظہ_object_fd 1
#تعریف_کرو GL_HANDLE_TYPE_OPAQUE_FD_EXT      0x9586
تعريفنوع فراغ (GL_APIENTRYP PFNGLIMPORTMEMORYFDEXTPROC) (GLuint حافظہ, GLuint64 ناپ, GLenum handleType, GLint fd);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Import_حافظہ_Fd_EXT (GLuint حافظہ, GLuint64 ناپ, GLenum handleType, GLint fd);
#جے_انت
#جے_انت /* GL_EXT_memory_object_fd */

#جے_بنا_تعریف GL_EXT_حافظہ_object_win32
#تعریف_کرو GL_EXT_حافظہ_object_win32 1
#تعریف_کرو GL_HANDLE_TYPE_OPAQUE_WIN32_EXT   0x9587
#تعریف_کرو GL_HANDLE_TYPE_OPAQUE_WIN32_KMT_EXT 0x9588
#تعریف_کرو GL_DEVICE_LUID_EXT                0x9599
#تعریف_کرو GL_DEVICE_گرہ_نقاب_EXT           0x959A
#تعریف_کرو GL_LUID_ناپ_EXT                  8
#تعریف_کرو GL_HANDLE_TYPE_D3D12_TILEPOOL_EXT 0x9589
#تعریف_کرو GL_HANDLE_TYPE_D3D12_RESOURCE_EXT 0x958A
#تعریف_کرو GL_HANDLE_TYPE_D3D11_IMAGE_EXT    0x958B
#تعریف_کرو GL_HANDLE_TYPE_D3D11_IMAGE_KMT_EXT 0x958C
تعريفنوع فراغ (GL_APIENTRYP PFNGLIMPORTMEMORYWIN32HANDLEEXTPROC) (GLuint حافظہ, GLuint64 ناپ, GLenum handleType, فراغ *handle);
تعريفنوع فراغ (GL_APIENTRYP PFNGLIMPORTMEMORYWIN32NAMEEXTPROC) (GLuint حافظہ, GLuint64 ناپ, GLenum handleType, ثابت فراغ *name);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Import_حافظہ_Win32_Handle_EXT (GLuint حافظہ, GLuint64 ناپ, GLenum handleType, فراغ *handle);
GL_APICALL فراغ GL_APIENTRY gl_Import_حافظہ_Win32_Name_EXT (GLuint حافظہ, GLuint64 ناپ, GLenum handleType, ثابت فراغ *name);
#جے_انت
#جے_انت /* GL_EXT_memory_object_win32 */

#جے_بنا_تعریف GL_EXT_mesh_shader
#تعریف_کرو GL_EXT_mesh_shader 1
#تعریف_کرو GL_MESH_SHADER_EXT                0x9559
#تعریف_کرو GL_TASK_SHADER_EXT                0x955A
#تعریف_کرو GL_MAX_MESH_اکسار_بلاکاں_EXT    0x8E60
#تعریف_کرو GL_MAX_MESH_TEXTURE_IMAGE_UNITS_EXT 0x8E61
#تعریف_کرو GL_MAX_MESH_IMAGE_UNIFORMS_EXT    0x8E62
#تعریف_کرو GL_MAX_MESH_اکسار_COMPONENTS_EXT 0x8E63
#تعریف_کرو GL_MAX_MESH_ATOMIC_COUNTER_BUFFERS_EXT 0x8E64
#تعریف_کرو GL_MAX_MESH_ATOMIC_COUNTERS_EXT   0x8E65
#تعریف_کرو GL_MAX_MESH_SHADER_STORAGE_بلاکاں_EXT 0x8E66
#تعریف_کرو GL_MAX_COMBINED_MESH_اکسار_COMPONENTS_EXT 0x8E67
#تعریف_کرو GL_MAX_TASK_اکسار_بلاکاں_EXT    0x8E68
#تعریف_کرو GL_MAX_TASK_TEXTURE_IMAGE_UNITS_EXT 0x8E69
#تعریف_کرو GL_MAX_TASK_IMAGE_UNIFORMS_EXT    0x8E6A
#تعریف_کرو GL_MAX_TASK_اکسار_COMPONENTS_EXT 0x8E6B
#تعریف_کرو GL_MAX_TASK_ATOMIC_COUNTER_BUFFERS_EXT 0x8E6C
#تعریف_کرو GL_MAX_TASK_ATOMIC_COUNTERS_EXT   0x8E6D
#تعریف_کرو GL_MAX_TASK_SHADER_STORAGE_بلاکاں_EXT 0x8E6E
#تعریف_کرو GL_MAX_COMBINED_TASK_اکسار_COMPONENTS_EXT 0x8E6F
#تعریف_کرو GL_MAX_TASK_WORK_گروہ_کل_گنتی_EXT 0x9740
#تعریف_کرو GL_MAX_MESH_WORK_گروہ_کل_گنتی_EXT 0x9741
#تعریف_کرو GL_MAX_MESH_WORK_گروہ_INVOCATIONS_EXT 0x9757
#تعریف_کرو GL_MAX_TASK_WORK_گروہ_INVOCATIONS_EXT 0x9759
#تعریف_کرو GL_MAX_TASK_PAYLOAD_ناپ_EXT      0x9742
#تعریف_کرو GL_MAX_TASK_SHARED_حافظہ_ناپ_EXT 0x9743
#تعریف_کرو GL_MAX_MESH_SHARED_حافظہ_ناپ_EXT 0x9744
#تعریف_کرو GL_MAX_TASK_PAYLOAD_AND_SHARED_حافظہ_ناپ_EXT 0x9745
#تعریف_کرو GL_MAX_MESH_PAYLOAD_AND_SHARED_حافظہ_ناپ_EXT 0x9746
#تعریف_کرو GL_MAX_MESH_OUTPUT_حافظہ_ناپ_EXT 0x9747
#تعریف_کرو GL_MAX_MESH_PAYLOAD_AND_OUTPUT_حافظہ_ناپ_EXT 0x9748
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
#تعریف_کرو GL_MAX_MESH_WORK_گروہ_ناپ_EXT   0x9758
#تعریف_کرو GL_MAX_TASK_WORK_گروہ_ناپ_EXT   0x975A
#تعریف_کرو GL_MESH_WORK_گروہ_ناپ_EXT       0x953E
#تعریف_کرو GL_TASK_WORK_گروہ_ناپ_EXT       0x953F
#تعریف_کرو GL_MESH_VERTICES_باہرلا_EXT          0x9579
#تعریف_کرو GL_MESH_PRIMITIVES_باہرلا_EXT        0x957A
#تعریف_کرو GL_MESH_OUTPUT_TYPE_EXT           0x957B
#تعریف_کرو GL_اکسار_بلاک_REFERENCED_BY_MESH_SHADER_EXT 0x959C
#تعریف_کرو GL_اکسار_بلاک_REFERENCED_BY_TASK_SHADER_EXT 0x959D
#تعریف_کرو GL_REFERENCED_BY_MESH_SHADER_EXT  0x95A0
#تعریف_کرو GL_REFERENCED_BY_TASK_SHADER_EXT  0x95A1
#تعریف_کرو GL_TASK_SHADER_INVOCATIONS_EXT    0x9753
#تعریف_کرو GL_MESH_SHADER_INVOCATIONS_EXT    0x9754
#تعریف_کرو GL_MESH_PRIMITIVES_GENERATED_EXT  0x9755
#تعریف_کرو GL_MESH_SHADER_ثنائی_ہندسہ_EXT            0x00000040
#تعریف_کرو GL_TASK_SHADER_ثنائی_ہندسہ_EXT            0x00000080
#تعریف_کرو GL_MESH_SUBROUTINE_EXT            0x957C
#تعریف_کرو GL_TASK_SUBROUTINE_EXT            0x957D
#تعریف_کرو GL_MESH_SUBROUTINE_اکسار_EXT    0x957E
#تعریف_کرو GL_TASK_SUBROUTINE_اکسار_EXT    0x957F
#تعریف_کرو GL_ATOMIC_COUNTER_بفر_REFERENCED_BY_MESH_SHADER_EXT 0x959E
#تعریف_کرو GL_ATOMIC_COUNTER_بفر_REFERENCED_BY_TASK_SHADER_EXT 0x959F
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWMESHTASKSEXTPROC) (GLuint عدد_groups_x, GLuint عدد_groups_y, GLuint عدد_groups_z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWMESHTASKSINDIRECTEXTPROC) (GLintptr اسدھا);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWMESHTASKSINDIRECTEXTPROC) (GLintptr اسدھا, GLsizei drawcount, GLsizei stride);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTEXTPROC) (GLintptr اسدھا, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawMeshTasksEXT (GLuint عدد_groups_x, GLuint عدد_groups_y, GLuint عدد_groups_z);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Mesh_Tasks_اسدھا_EXT (GLintptr اسدھا);
GL_APICALL فراغ GL_APIENTRY gl_Multi_Draw_Mesh_Tasks_اسدھا_EXT (GLintptr اسدھا, GLsizei drawcount, GLsizei stride);
GL_APICALL فراغ GL_APIENTRY gl_Multi_Draw_Mesh_Tasks_اسدھا_گنتی_EXT (GLintptr اسدھا, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
#جے_انت
#جے_انت /* GL_EXT_mesh_shader */

#جے_بنا_تعریف GL_EXT_multi_draw_arrays
#تعریف_کرو GL_EXT_multi_draw_arrays 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWARRAYSEXTPROC) (GLenum منوال, ثابت GLint *پہلا, ثابت GLsizei *گنتی, GLsizei primcount);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSEXTPROC) (GLenum منوال, ثابت GLsizei *گنتی, GLenum type, ثابت فراغ *ثابت*indices, GLsizei primcount);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glMultiDrawArraysEXT (GLenum منوال, ثابت GLint *پہلا, ثابت GLsizei *گنتی, GLsizei primcount);
GL_APICALL فراغ GL_APIENTRY glMultiDrawElementsEXT (GLenum منوال, ثابت GLsizei *گنتی, GLenum type, ثابت فراغ *ثابت*indices, GLsizei primcount);
#جے_انت
#جے_انت /* GL_EXT_multi_draw_arrays */

#جے_بنا_تعریف GL_EXT_multi_draw_اسدھا
#تعریف_کرو GL_EXT_multi_draw_اسدھا 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWARRAYSINDIRECTEXTPROC) (GLenum منوال, ثابت فراغ *اسدھا, GLsizei drawcount, GLsizei stride);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSINDIRECTEXTPROC) (GLenum منوال, GLenum type, ثابت فراغ *اسدھا, GLsizei drawcount, GLsizei stride);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Multi_Draw_Arrays_اسدھا_EXT (GLenum منوال, ثابت فراغ *اسدھا, GLsizei drawcount, GLsizei stride);
GL_APICALL فراغ GL_APIENTRY gl_Multi_Draw_Elements_اسدھا_EXT (GLenum منوال, GLenum type, ثابت فراغ *اسدھا, GLsizei drawcount, GLsizei stride);
#جے_انت
#جے_انت /* GL_EXT_multi_draw_indirect */

#جے_بنا_تعریف GL_EXT_multisampled_compatibility
#تعریف_کرو GL_EXT_multisampled_compatibility 1
#تعریف_کرو GL_MULTISAMPLE_EXT                0x809D
#تعریف_کرو GL_SAMPLE_ALPHA_منزل_ONE_EXT        0x809F
#جے_انت /* GL_EXT_multisampled_compatibility */

#جے_بنا_تعریف GL_EXT_multisampled_render_منزل_texture
#تعریف_کرو GL_EXT_multisampled_render_منزل_texture 1
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SAMPLES_EXT 0x8D6C
#تعریف_کرو GL_RENDERBUFFER_SAMPLES_EXT       0x8CAB
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT 0x8D56
#تعریف_کرو GL_MAX_SAMPLES_EXT                0x8D57
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) (GLenum نشانہ, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEEXTPROC) (GLenum نشانہ, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glRenderbufferStorageMultisampleEXT (GLenum نشانہ, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی);
GL_APICALL فراغ GL_APIENTRY glFramebufferTexture2DMultisampleEXT (GLenum نشانہ, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#جے_انت
#جے_انت /* GL_EXT_multisampled_render_to_texture */

#جے_بنا_تعریف GL_EXT_multisampled_render_منزل_texture2
#تعریف_کرو GL_EXT_multisampled_render_منزل_texture2 1
#جے_انت /* GL_EXT_multisampled_render_to_texture2 */

#جے_بنا_تعریف GL_EXT_multiview_draw_buffers
#تعریف_کرو GL_EXT_multiview_draw_buffers 1
#تعریف_کرو GL_COLOR_ATTACHMENT_EXT           0x90F0
#تعریف_کرو GL_MULTIVIEW_EXT                  0x90F1
#تعریف_کرو GL_DRAW_بفر_EXT                0x0C01
#تعریف_کرو GL_READ_بفر_EXT                0x0C02
#تعریف_کرو GL_MAX_MULTIVIEW_BUFFERS_EXT      0x90F2
تعريفنوع فراغ (GL_APIENTRYP PFNGLREADBUFFERINDEXEDEXTPROC) (GLenum src, GLint اشاریہ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWBUFFERSINDEXEDEXTPROC) (GLint n, ثابت GLenum *location, ثابت GLint *indices);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTEGERI_VEXTPROC) (GLenum نشانہ, GLuint اشاریہ, GLint *انکڑے);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Read_بفر_اشاریہ_دار_EXT (GLenum src, GLint اشاریہ);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Buffers_اشاریہ_دار_EXT (GLint n, ثابت GLenum *location, ثابت GLint *indices);
GL_APICALL فراغ GL_APIENTRY glGetIntegeri_vEXT (GLenum نشانہ, GLuint اشاریہ, GLint *انکڑے);
#جے_انت
#جے_انت /* GL_EXT_multiview_draw_buffers */

#جے_بنا_تعریف GL_EXT_multiview_tessellation_geometry_shader
#تعریف_کرو GL_EXT_multiview_tessellation_geometry_shader 1
#جے_انت /* GL_EXT_multiview_tessellation_geometry_shader */

#جے_بنا_تعریف GL_EXT_multiview_texture_multisample
#تعریف_کرو GL_EXT_multiview_texture_multisample 1
#جے_انت /* GL_EXT_multiview_texture_multisample */

#جے_بنا_تعریف GL_EXT_multiview_timer_query
#تعریف_کرو GL_EXT_multiview_timer_query 1
#جے_انت /* GL_EXT_multiview_timer_query */

#جے_بنا_تعریف GL_EXT_occlusion_query_boolean
#تعریف_کرو GL_EXT_occlusion_query_boolean 1
#تعریف_کرو GL_ANY_SAMPLES_PASSED_EXT         0x8C2F
#تعریف_کرو GL_ANY_SAMPLES_PASSED_CONSERVATIVE_EXT 0x8D6A
#جے_انت /* GL_EXT_occlusion_query_boolean */

#جے_بنا_تعریف GL_EXT_polygon_وتھ_clamp
#تعریف_کرو GL_EXT_polygon_وتھ_clamp 1
#تعریف_کرو GL_POLYGON_وتھ_CLAMP_EXT       0x8E1B
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOLYGONOFFSETCLAMPEXTPROC) (GLfloat ضارب, GLfloat units, GLfloat clamp);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Polygon_وتھ_Clamp_EXT (GLfloat ضارب, GLfloat units, GLfloat clamp);
#جے_انت
#جے_انت /* GL_EXT_polygon_offset_clamp */

#جے_بنا_تعریف GL_EXT_post_ڈونگھائی_coverage
#تعریف_کرو GL_EXT_post_ڈونگھائی_coverage 1
#جے_انت /* GL_EXT_post_depth_coverage */

#جے_بنا_تعریف GL_EXT_primitive_bounding_box
#تعریف_کرو GL_EXT_primitive_bounding_box 1
#تعریف_کرو GL_PRIMITIVE_BOUNDING_BOX_EXT     0x92BE
تعريفنوع فراغ (GL_APIENTRYP PFNGLPRIMITIVEBOUNDINGBOXEXTPROC) (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glPrimitiveBoundingBoxEXT (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
#جے_انت
#جے_انت /* GL_EXT_primitive_bounding_box */

#جے_بنا_تعریف GL_EXT_protected_textures
#تعریف_کرو GL_EXT_protected_textures 1
#تعریف_کرو GL_CONTEXT_FLAG_PROTECTED_CONTENT_ثنائی_ہندسہ_EXT 0x00000010
#تعریف_کرو GL_TEXTURE_PROTECTED_EXT          0x8BFA
#جے_انت /* GL_EXT_protected_textures */

#جے_بنا_تعریف GL_EXT_pvrtc_sRGB
#تعریف_کرو GL_EXT_pvrtc_sRGB 1
#تعریف_کرو GL_COMPRESSED_SRGB_PVRTC_2BPPV1_EXT 0x8A54
#تعریف_کرو GL_COMPRESSED_SRGB_PVRTC_4BPPV1_EXT 0x8A55
#تعریف_کرو GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV1_EXT 0x8A56
#تعریف_کرو GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV1_EXT 0x8A57
#تعریف_کرو GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV2_IMG 0x93F0
#تعریف_کرو GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV2_IMG 0x93F1
#جے_انت /* GL_EXT_pvrtc_sRGB */

#جے_بنا_تعریف GL_EXT_raster_multisample
#تعریف_کرو GL_EXT_raster_multisample 1
#تعریف_کرو GL_RASTER_MULTISAMPLE_EXT         0x9327
#تعریف_کرو GL_RASTER_SAMPLES_EXT             0x9328
#تعریف_کرو GL_MAX_RASTER_SAMPLES_EXT         0x9329
#تعریف_کرو GL_RASTER_FIXED_SAMPLE_LOCATIONS_EXT 0x932A
#تعریف_کرو GL_MULTISAMPLE_RASTERIZATION_ALLOWED_EXT 0x932B
#تعریف_کرو GL_EFFECTIVE_RASTER_SAMPLES_EXT   0x932C
تعريفنوع فراغ (GL_APIENTRYP PFNGLRASTERSAMPLESEXTPROC) (GLuint samples, GLboolean fixedsamplelocations);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glRasterSamplesEXT (GLuint samples, GLboolean fixedsamplelocations);
#جے_انت
#جے_انت /* GL_EXT_raster_multisample */

#جے_بنا_تعریف GL_EXT_read_format_bgra
#تعریف_کرو GL_EXT_read_format_bgra 1
#تعریف_کرو GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT 0x8365
#تعریف_کرو GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT 0x8366
#جے_انت /* GL_EXT_read_format_bgra */

#جے_بنا_تعریف GL_EXT_render_snorm
#تعریف_کرو GL_EXT_render_snorm 1
#تعریف_کرو GL_R8_SNORM                       0x8F94
#تعریف_کرو GL_RG8_SNORM                      0x8F95
#تعریف_کرو GL_RGBA8_SNORM                    0x8F97
#تعریف_کرو GL_R16_SNORM_EXT                  0x8F98
#تعریف_کرو GL_RG16_SNORM_EXT                 0x8F99
#تعریف_کرو GL_RGBA16_SNORM_EXT               0x8F9B
#جے_انت /* GL_EXT_render_snorm */

#جے_بنا_تعریف GL_EXT_robustness
#تعریف_کرو GL_EXT_robustness 1
#تعریف_کرو GL_GUILTY_CONTEXT_RESET_EXT       0x8253
#تعریف_کرو GL_INNOCENT_CONTEXT_RESET_EXT     0x8254
#تعریف_کرو GL_UNKNOWN_CONTEXT_RESET_EXT      0x8255
#تعریف_کرو GL_CONTEXT_ROBUST_ACCESS_EXT      0x90F3
#تعریف_کرو GL_RESET_NOTIFICATION_STRATEGY_EXT 0x8256
#تعریف_کرو GL_LOSE_CONTEXT_ON_RESET_EXT      0x8252
#تعریف_کرو GL_NO_RESET_NOTIFICATION_EXT      0x8261
تعريفنوع GLenum (GL_APIENTRYP PFNGLGETGRAPHICSRESETSTATUSEXTPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLREADNPIXELSEXTPROC) (GLint x, GLint y, GLsizei چوڑائی, GLsizei اچائی, GLenum format, GLenum type, GLsizei buf_ناپ, فراغ *انکڑے);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNUNIFORMFVEXTPROC) (GLuint پروگرام, GLint location, GLsizei buf_ناپ, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNUNIFORMIVEXTPROC) (GLuint پروگرام, GLint location, GLsizei buf_ناپ, GLint *params);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL GLenum GL_APIENTRY gl_Get_Graphics_Reset_حالت_EXT (فراغ);
GL_APICALL فراغ GL_APIENTRY glReadnPixelsEXT (GLint x, GLint y, GLsizei چوڑائی, GLsizei اچائی, GLenum format, GLenum type, GLsizei buf_ناپ, فراغ *انکڑے);
GL_APICALL فراغ GL_APIENTRY glGetnUniformfvEXT (GLuint پروگرام, GLint location, GLsizei buf_ناپ, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY glGetnUniformivEXT (GLuint پروگرام, GLint location, GLsizei buf_ناپ, GLint *params);
#جے_انت
#جے_انت /* GL_EXT_robustness */

#جے_بنا_تعریف GL_EXT_sRGB
#تعریف_کرو GL_EXT_sRGB 1
#تعریف_کرو GL_SRGB_EXT                       0x8C40
#تعریف_کرو GL_SRGB_ALPHA_EXT                 0x8C42
#تعریف_کرو GL_SRGB8_ALPHA8_EXT               0x8C43
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING_EXT 0x8210
#جے_انت /* GL_EXT_sRGB */

#جے_بنا_تعریف GL_EXT_sRGB_write_control
#تعریف_کرو GL_EXT_sRGB_write_control 1
#تعریف_کرو GL_FRAMEBUFFER_SRGB_EXT           0x8DB9
#جے_انت /* GL_EXT_sRGB_write_control */

#جے_بنا_تعریف GL_EXT_semaphore
#تعریف_کرو GL_EXT_semaphore 1
#تعریف_کرو GL_LAYOUT_GENERAL_EXT             0x958D
#تعریف_کرو GL_LAYOUT_COLOR_ATTACHMENT_EXT    0x958E
#تعریف_کرو GL_LAYOUT_ڈونگھائی_STENCIL_ATTACHMENT_EXT 0x958F
#تعریف_کرو GL_LAYOUT_ڈونگھائی_STENCIL_READ_ONLY_EXT 0x9590
#تعریف_کرو GL_LAYOUT_SHADER_READ_ONLY_EXT    0x9591
#تعریف_کرو GL_LAYOUT_TRANSFER_SRC_EXT        0x9592
#تعریف_کرو GL_LAYOUT_TRANSFER_DST_EXT        0x9593
#تعریف_کرو GL_LAYOUT_ڈونگھائی_READ_ONLY_STENCIL_ATTACHMENT_EXT 0x9530
#تعریف_کرو GL_LAYOUT_ڈونگھائی_ATTACHMENT_STENCIL_READ_ONLY_EXT 0x9531
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENSEMAPHORESEXTPROC) (GLsizei n, GLuint *semaphores);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETESEMAPHORESEXTPROC) (GLsizei n, ثابت GLuint *semaphores);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISSEMAPHOREEXTPROC) (GLuint semaphore);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSEMAPHOREPARAMETERUI64VEXTPROC) (GLuint semaphore, GLenum pname, ثابت GLuint64 *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSEMAPHOREPARAMETERUI64VEXTPROC) (GLuint semaphore, GLenum pname, GLuint64 *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLWAITSEMAPHOREEXTPROC) (GLuint semaphore, GLuint عدد_بفر_Barriers, ثابت GLuint *buffers, GLuint عدد_Texture_Barriers, ثابت GLuint *textures, ثابت GLenum *srcLayouts);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSIGNALSEMAPHOREEXTPROC) (GLuint semaphore, GLuint عدد_بفر_Barriers, ثابت GLuint *buffers, GLuint عدد_Texture_Barriers, ثابت GLuint *textures, ثابت GLenum *dstLayouts);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glGenSemaphoresEXT (GLsizei n, GLuint *semaphores);
GL_APICALL فراغ GL_APIENTRY glDeleteSemaphoresEXT (GLsizei n, ثابت GLuint *semaphores);
GL_APICALL GLboolean GL_APIENTRY glIsSemaphoreEXT (GLuint semaphore);
GL_APICALL فراغ GL_APIENTRY glSemaphoreParameterui64vEXT (GLuint semaphore, GLenum pname, ثابت GLuint64 *params);
GL_APICALL فراغ GL_APIENTRY glGetSemaphoreParameterui64vEXT (GLuint semaphore, GLenum pname, GLuint64 *params);
GL_APICALL فراغ GL_APIENTRY glWaitSemaphoreEXT (GLuint semaphore, GLuint عدد_بفر_Barriers, ثابت GLuint *buffers, GLuint عدد_Texture_Barriers, ثابت GLuint *textures, ثابت GLenum *srcLayouts);
GL_APICALL فراغ GL_APIENTRY glSignalSemaphoreEXT (GLuint semaphore, GLuint عدد_بفر_Barriers, ثابت GLuint *buffers, GLuint عدد_Texture_Barriers, ثابت GLuint *textures, ثابت GLenum *dstLayouts);
#جے_انت
#جے_انت /* GL_EXT_semaphore */

#جے_بنا_تعریف GL_EXT_semaphore_fd
#تعریف_کرو GL_EXT_semaphore_fd 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLIMPORTSEMAPHOREFDEXTPROC) (GLuint semaphore, GLenum handleType, GLint fd);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glImportSemaphoreFdEXT (GLuint semaphore, GLenum handleType, GLint fd);
#جے_انت
#جے_انت /* GL_EXT_semaphore_fd */

#جے_بنا_تعریف GL_EXT_semaphore_win32
#تعریف_کرو GL_EXT_semaphore_win32 1
#تعریف_کرو GL_HANDLE_TYPE_D3D12_FENCE_EXT    0x9594
#تعریف_کرو GL_D3_D12_FENCE_قدر_EXT          0x9595
تعريفنوع فراغ (GL_APIENTRYP PFNGLIMPORTSEMAPHOREWIN32HANDLEEXTPROC) (GLuint semaphore, GLenum handleType, فراغ *handle);
تعريفنوع فراغ (GL_APIENTRYP PFNGLIMPORTSEMAPHOREWIN32NAMEEXTPROC) (GLuint semaphore, GLenum handleType, ثابت فراغ *name);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glImportSemaphoreWin32HandleEXT (GLuint semaphore, GLenum handleType, فراغ *handle);
GL_APICALL فراغ GL_APIENTRY glImportSemaphoreWin32NameEXT (GLuint semaphore, GLenum handleType, ثابت فراغ *name);
#جے_انت
#جے_انت /* GL_EXT_semaphore_win32 */

#جے_بنا_تعریف GL_EXT_separate_ڈونگھائی_stencil
#تعریف_کرو GL_EXT_separate_ڈونگھائی_stencil 1
#جے_انت /* GL_EXT_separate_depth_stencil */

#جے_بنا_تعریف GL_EXT_separate_shader_objects
#تعریف_کرو GL_EXT_separate_shader_objects 1
#تعریف_کرو GL_سرگرم_پروگرام_EXT             0x8259
#تعریف_کرو GL_راس_SHADER_ثنائی_ہندسہ_EXT          0x00000001
#تعریف_کرو GL_FRAGMENT_SHADER_ثنائی_ہندسہ_EXT        0x00000002
#تعریف_کرو GL_ALL_SHADER_بٹ_EXT            0xFFFFFFFF
#تعریف_کرو GL_پروگرام_SEPARABLE_EXT          0x8258
#تعریف_کرو GL_پروگرام_PIPELINE_BINDING_EXT   0x825A
تعريفنوع فراغ (GL_APIENTRYP PFNGLACTIVESHADERPROGRAMEXTPROC) (GLuint pipeline, GLuint پروگرام);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDPROGRAMPIPELINEEXTPROC) (GLuint pipeline);
تعريفنوع GLuint (GL_APIENTRYP PFNGLCREATESHADERPROGRAMVEXTPROC) (GLenum type, GLsizei گنتی, ثابت GLchar *ثابت*لڑیاں);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEPROGRAMPIPELINESEXTPROC) (GLsizei n, ثابت GLuint *pipelines);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENPROGRAMPIPELINESEXTPROC) (GLsizei n, GLuint *pipelines);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMPIPELINEINFOLOGEXTPROC) (GLuint pipeline, GLsizei buf_ناپ, GLsizei *لمائی, GLchar *infoLog);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMPIPELINEIVEXTPROC) (GLuint pipeline, GLenum pname, GLint *params);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISPROGRAMPIPELINEEXTPROC) (GLuint pipeline);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMPARAMETERIEXTPROC) (GLuint پروگرام, GLenum pname, GLint قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1FEXTPROC) (GLuint پروگرام, GLint location, GLfloat v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1IEXTPROC) (GLuint پروگرام, GLint location, GLint v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1IVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2FEXTPROC) (GLuint پروگرام, GLint location, GLfloat v0, GLfloat v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2IEXTPROC) (GLuint پروگرام, GLint location, GLint v0, GLint v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2IVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3FEXTPROC) (GLuint پروگرام, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3IEXTPROC) (GLuint پروگرام, GLint location, GLint v0, GLint v1, GLint v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3IVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4FEXTPROC) (GLuint پروگرام, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4IEXTPROC) (GLuint پروگرام, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4IVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUSEPROGRAMSTAGESEXTPROC) (GLuint pipeline, GLbitfield stages, GLuint پروگرام);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVALIDATEPROGRAMPIPELINEEXTPROC) (GLuint pipeline);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UIEXTPROC) (GLuint پروگرام, GLint location, GLuint v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UIEXTPROC) (GLuint پروگرام, GLint location, GLuint v0, GLuint v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UIEXTPROC) (GLuint پروگرام, GLint location, GLuint v0, GLuint v1, GLuint v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UIEXTPROC) (GLuint پروگرام, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UIVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UIVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UIVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UIVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_سرگرم_Shader_پروگرام_EXT (GLuint pipeline, GLuint پروگرام);
GL_APICALL فراغ GL_APIENTRY gl_Bind_پروگرام_Pipeline_EXT (GLuint pipeline);
GL_APICALL GLuint GL_APIENTRY glCreateShaderProgramvEXT (GLenum type, GLsizei گنتی, ثابت GLchar *ثابت*لڑیاں);
GL_APICALL فراغ GL_APIENTRY gl_Delete_پروگرام_Pipelines_EXT (GLsizei n, ثابت GLuint *pipelines);
GL_APICALL فراغ GL_APIENTRY gl_Gen_پروگرام_Pipelines_EXT (GLsizei n, GLuint *pipelines);
GL_APICALL فراغ GL_APIENTRY gl_Get_پروگرام_Pipeline_Info_Log_EXT (GLuint pipeline, GLsizei buf_ناپ, GLsizei *لمائی, GLchar *infoLog);
GL_APICALL فراغ GL_APIENTRY gl_Get_پروگرام_Pipelineiv_EXT (GLuint pipeline, GLenum pname, GLint *params);
GL_APICALL GLboolean GL_APIENTRY gl_Is_پروگرام_Pipeline_EXT (GLuint pipeline);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Parameteri_EXT (GLuint پروگرام, GLenum pname, GLint قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform1f_EXT (GLuint پروگرام, GLint location, GLfloat v0);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform1fv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform1i_EXT (GLuint پروگرام, GLint location, GLint v0);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform1iv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform2f_EXT (GLuint پروگرام, GLint location, GLfloat v0, GLfloat v1);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform2fv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform2i_EXT (GLuint پروگرام, GLint location, GLint v0, GLint v1);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform2iv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform3f_EXT (GLuint پروگرام, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform3fv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform3i_EXT (GLuint پروگرام, GLint location, GLint v0, GLint v1, GLint v2);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform3iv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform4f_EXT (GLuint پروگرام, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform4fv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform4i_EXT (GLuint پروگرام, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform4iv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_اکسار_Matrix2fv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_اکسار_Matrix3fv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_اکسار_Matrix4fv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_Use_پروگرام_Stages_EXT (GLuint pipeline, GLbitfield stages, GLuint پروگرام);
GL_APICALL فراغ GL_APIENTRY gl_Validate_پروگرام_Pipeline_EXT (GLuint pipeline);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform1ui_EXT (GLuint پروگرام, GLint location, GLuint v0);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform2ui_EXT (GLuint پروگرام, GLint location, GLuint v0, GLuint v1);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform3ui_EXT (GLuint پروگرام, GLint location, GLuint v0, GLuint v1, GLuint v2);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform4ui_EXT (GLuint پروگرام, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform1uiv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform2uiv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform3uiv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform4uiv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_اکسار_Matrix2x3fv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_اکسار_Matrix3x2fv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_اکسار_Matrix2x4fv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_اکسار_Matrix4x2fv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_اکسار_Matrix3x4fv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_اکسار_Matrix4x3fv_EXT (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
#جے_انت
#جے_انت /* GL_EXT_separate_shader_objects */

#جے_بنا_تعریف GL_EXT_shader_framebuffer_fetch
#تعریف_کرو GL_EXT_shader_framebuffer_fetch 1
#تعریف_کرو GL_FRAGMENT_SHADER_DISCARDS_SAMPLES_EXT 0x8A52
#جے_انت /* GL_EXT_shader_framebuffer_fetch */

#جے_بنا_تعریف GL_EXT_shader_framebuffer_fetch_non_coherent
#تعریف_کرو GL_EXT_shader_framebuffer_fetch_non_coherent 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERFETCHBARRIEREXTPROC) (فراغ);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferFetchBarrierEXT (فراغ);
#جے_انت
#جے_انت /* GL_EXT_shader_framebuffer_fetch_non_coherent */

#جے_بنا_تعریف GL_EXT_shader_گروہ_vote
#تعریف_کرو GL_EXT_shader_گروہ_vote 1
#جے_انت /* GL_EXT_shader_group_vote */

#جے_بنا_تعریف GL_EXT_shader_implicit_conversions
#تعریف_کرو GL_EXT_shader_implicit_conversions 1
#جے_انت /* GL_EXT_shader_implicit_conversions */

#جے_بنا_تعریف GL_EXT_shader_integer_mix
#تعریف_کرو GL_EXT_shader_integer_mix 1
#جے_انت /* GL_EXT_shader_integer_mix */

#جے_بنا_تعریف GL_EXT_shader_io_بلاکاں
#تعریف_کرو GL_EXT_shader_io_بلاکاں 1
#جے_انت /* GL_EXT_shader_io_blocks */

#جے_بنا_تعریف GL_EXT_shader_non_constant_global_initializers
#تعریف_کرو GL_EXT_shader_non_constant_global_initializers 1
#جے_انت /* GL_EXT_shader_non_constant_global_initializers */

#جے_بنا_تعریف GL_EXT_shader_pixel_local_storage
#تعریف_کرو GL_EXT_shader_pixel_local_storage 1
#تعریف_کرو GL_MAX_SHADER_PIXEL_LOCAL_STORAGE_FAST_ناپ_EXT 0x8F63
#تعریف_کرو GL_MAX_SHADER_PIXEL_LOCAL_STORAGE_ناپ_EXT 0x8F67
#تعریف_کرو GL_SHADER_PIXEL_LOCAL_STORAGE_EXT 0x8F64
#جے_انت /* GL_EXT_shader_pixel_local_storage */

#جے_بنا_تعریف GL_EXT_shader_pixel_local_storage2
#تعریف_کرو GL_EXT_shader_pixel_local_storage2 1
#تعریف_کرو GL_MAX_SHADER_COMBINED_LOCAL_STORAGE_FAST_ناپ_EXT 0x9650
#تعریف_کرو GL_MAX_SHADER_COMBINED_LOCAL_STORAGE_ناپ_EXT 0x9651
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_INSUFFICIENT_SHADER_COMBINED_LOCAL_STORAGE_EXT 0x9652
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERPIXELLOCALSTORAGESIZEEXTPROC) (GLuint نشانہ, GLsizei ناپ);
تعريفنوع GLsizei (GL_APIENTRYP PFNGLGETFRAMEBUFFERPIXELLOCALSTORAGESIZEEXTPROC) (GLuint نشانہ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARPIXELLOCALSTORAGEUIEXTPROC) (GLsizei وتھ_2, GLsizei n, ثابت GLuint *اقدار);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Framebuffer_Pixel_Local_Storage_ناپ_EXT (GLuint نشانہ, GLsizei ناپ);
GL_APICALL GLsizei GL_APIENTRY gl_Get_Framebuffer_Pixel_Local_Storage_ناپ_EXT (GLuint نشانہ);
GL_APICALL فراغ GL_APIENTRY glClearPixelLocalStorageuiEXT (GLsizei وتھ_2, GLsizei n, ثابت GLuint *اقدار);
#جے_انت
#جے_انت /* GL_EXT_shader_pixel_local_storage2 */

#جے_بنا_تعریف GL_EXT_shader_samples_identical
#تعریف_کرو GL_EXT_shader_samples_identical 1
#جے_انت /* GL_EXT_shader_samples_identical */

#جے_بنا_تعریف GL_EXT_shader_texture_lod
#تعریف_کرو GL_EXT_shader_texture_lod 1
#جے_انت /* GL_EXT_shader_texture_lod */

#جے_بنا_تعریف GL_EXT_shader_texture_samples
#تعریف_کرو GL_EXT_shader_texture_samples 1
#جے_انت /* GL_EXT_shader_texture_samples */

#جے_بنا_تعریف GL_EXT_shadow_samplers
#تعریف_کرو GL_EXT_shadow_samplers 1
#تعریف_کرو GL_TEXTURE_COMPARE_منوال_EXT       0x884C
#تعریف_کرو GL_TEXTURE_COMPARE_FUNC_EXT       0x884D
#تعریف_کرو GL_COMPARE_REF_منزل_TEXTURE_EXT     0x884E
#تعریف_کرو GL_SAMPLER_2D_SHADOW_EXT          0x8B62
#جے_انت /* GL_EXT_shadow_samplers */

#جے_بنا_تعریف GL_EXT_sparse_texture
#تعریف_کرو GL_EXT_sparse_texture 1
#تعریف_کرو GL_TEXTURE_SPARSE_EXT             0x91A6
#تعریف_کرو GL_VIRTUAL_ورقہ_ناپ_اشاریہ_EXT    0x91A7
#تعریف_کرو GL_عدد_SPARSE_پدھراں_EXT          0x91AA
#تعریف_کرو GL_عدد_VIRTUAL_ورقہ_SIZES_EXT     0x91A8
#تعریف_کرو GL_VIRTUAL_ورقہ_ناپ_X_EXT        0x9195
#تعریف_کرو GL_VIRTUAL_ورقہ_ناپ_Y_EXT        0x9196
#تعریف_کرو GL_VIRTUAL_ورقہ_ناپ_Z_EXT        0x9197
#تعریف_کرو GL_TEXTURE_2D_ARRAY               0x8C1A
#تعریف_کرو GL_TEXTURE_3D                     0x806F
#تعریف_کرو GL_MAX_SPARSE_TEXTURE_ناپ_EXT    0x9198
#تعریف_کرو GL_MAX_SPARSE_3_D_TEXTURE_ناپ_EXT 0x9199
#تعریف_کرو GL_MAX_SPARSE_ARRAY_TEXTURE_LAYERS_EXT 0x919A
#تعریف_کرو GL_SPARSE_TEXTURE_بھریا_ARRAY_CUBE_MIPMAPS_EXT 0x91A9
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPAGECOMMITMENTEXTPROC) (GLenum نشانہ, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2, GLboolean commit);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Tex_ورقہ_Commitment_EXT (GLenum نشانہ, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2, GLboolean commit);
#جے_انت
#جے_انت /* GL_EXT_sparse_texture */

#جے_بنا_تعریف GL_EXT_sparse_texture2
#تعریف_کرو GL_EXT_sparse_texture2 1
#جے_انت /* GL_EXT_sparse_texture2 */

#جے_بنا_تعریف GL_EXT_tessellation_نقطہ_ناپ
#تعریف_کرو GL_EXT_tessellation_نقطہ_ناپ 1
#جے_انت /* GL_EXT_tessellation_point_size */

#جے_بنا_تعریف GL_EXT_tessellation_shader
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
#تعریف_کرو GL_MAX_TESS_CONTROL_اکسار_COMPONENTS_EXT 0x8E7F
#تعریف_کرو GL_MAX_TESS_EVALUATION_اکسار_COMPONENTS_EXT 0x8E80
#تعریف_کرو GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS_EXT 0x8E81
#تعریف_کرو GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS_EXT 0x8E82
#تعریف_کرو GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS_EXT 0x8E83
#تعریف_کرو GL_MAX_TESS_PATCH_COMPONENTS_EXT  0x8E84
#تعریف_کرو GL_MAX_TESS_CONTROL_کل_OUTPUT_COMPONENTS_EXT 0x8E85
#تعریف_کرو GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS_EXT 0x8E86
#تعریف_کرو GL_MAX_TESS_CONTROL_اکسار_بلاکاں_EXT 0x8E89
#تعریف_کرو GL_MAX_TESS_EVALUATION_اکسار_بلاکاں_EXT 0x8E8A
#تعریف_کرو GL_MAX_TESS_CONTROL_داخلہ_COMPONENTS_EXT 0x886C
#تعریف_کرو GL_MAX_TESS_EVALUATION_داخلہ_COMPONENTS_EXT 0x886D
#تعریف_کرو GL_MAX_COMBINED_TESS_CONTROL_اکسار_COMPONENTS_EXT 0x8E1E
#تعریف_کرو GL_MAX_COMBINED_TESS_EVALUATION_اکسار_COMPONENTS_EXT 0x8E1F
#تعریف_کرو GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS_EXT 0x92CD
#تعریف_کرو GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS_EXT 0x92CE
#تعریف_کرو GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS_EXT 0x92D3
#تعریف_کرو GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS_EXT 0x92D4
#تعریف_کرو GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS_EXT 0x90CB
#تعریف_کرو GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS_EXT 0x90CC
#تعریف_کرو GL_MAX_TESS_CONTROL_SHADER_STORAGE_بلاکاں_EXT 0x90D8
#تعریف_کرو GL_MAX_TESS_EVALUATION_SHADER_STORAGE_بلاکاں_EXT 0x90D9
#تعریف_کرو GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED 0x8221
#تعریف_کرو GL_IS_فی_PATCH_EXT               0x92E7
#تعریف_کرو GL_REFERENCED_BY_TESS_CONTROL_SHADER_EXT 0x9307
#تعریف_کرو GL_REFERENCED_BY_TESS_EVALUATION_SHADER_EXT 0x9308
#تعریف_کرو GL_TESS_CONTROL_SHADER_EXT        0x8E88
#تعریف_کرو GL_TESS_EVALUATION_SHADER_EXT     0x8E87
#تعریف_کرو GL_TESS_CONTROL_SHADER_ثنائی_ہندسہ_EXT    0x00000008
#تعریف_کرو GL_TESS_EVALUATION_SHADER_ثنائی_ہندسہ_EXT 0x00000010
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATCHPARAMETERIEXTPROC) (GLenum pname, GLint قدر);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glPatchParameteriEXT (GLenum pname, GLint قدر);
#جے_انت
#جے_انت /* GL_EXT_tessellation_shader */

#جے_بنا_تعریف GL_EXT_texture_border_clamp
#تعریف_کرو GL_EXT_texture_border_clamp 1
#تعریف_کرو GL_TEXTURE_BORDER_COLOR_EXT       0x1004
#تعریف_کرو GL_CLAMP_منزل_BORDER_EXT            0x812D
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERIIVEXTPROC) (GLenum نشانہ, GLenum pname, ثابت GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERIUIVEXTPROC) (GLenum نشانہ, GLenum pname, ثابت GLuint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXPARAMETERIIVEXTPROC) (GLenum نشانہ, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXPARAMETERIUIVEXTPROC) (GLenum نشانہ, GLenum pname, GLuint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIIVEXTPROC) (GLuint sampler, GLenum pname, ثابت GLint *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIUIVEXTPROC) (GLuint sampler, GLenum pname, ثابت GLuint *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIIVEXTPROC) (GLuint sampler, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIUIVEXTPROC) (GLuint sampler, GLenum pname, GLuint *params);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTexParameterIivEXT (GLenum نشانہ, GLenum pname, ثابت GLint *params);
GL_APICALL فراغ GL_APIENTRY glTexParameterIuivEXT (GLenum نشانہ, GLenum pname, ثابت GLuint *params);
GL_APICALL فراغ GL_APIENTRY glGetTexParameterIivEXT (GLenum نشانہ, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetTexParameterIuivEXT (GLenum نشانہ, GLenum pname, GLuint *params);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterIivEXT (GLuint sampler, GLenum pname, ثابت GLint *param);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterIuivEXT (GLuint sampler, GLenum pname, ثابت GLuint *param);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameterIivEXT (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameterIuivEXT (GLuint sampler, GLenum pname, GLuint *params);
#جے_انت
#جے_انت /* GL_EXT_texture_border_clamp */

#جے_بنا_تعریف GL_EXT_texture_بفر
#تعریف_کرو GL_EXT_texture_بفر 1
#تعریف_کرو GL_TEXTURE_بفر_EXT             0x8C2A
#تعریف_کرو GL_TEXTURE_بفر_BINDING_EXT     0x8C2A
#تعریف_کرو GL_MAX_TEXTURE_بفر_ناپ_EXT    0x8C2B
#تعریف_کرو GL_TEXTURE_BINDING_بفر_EXT     0x8C2C
#تعریف_کرو GL_TEXTURE_بفر_انکڑے_STORE_BINDING_EXT 0x8C2D
#تعریف_کرو GL_TEXTURE_بفر_وتھ_ALIGNMENT_EXT 0x919F
#تعریف_کرو GL_SAMPLER_بفر_EXT             0x8DC2
#تعریف_کرو GL_INT_SAMPLER_بفر_EXT         0x8DD0
#تعریف_کرو GL_UNSIGNED_INT_SAMPLER_بفر_EXT 0x8DD8
#تعریف_کرو GL_IMAGE_بفر_EXT               0x9051
#تعریف_کرو GL_INT_IMAGE_بفر_EXT           0x905C
#تعریف_کرو GL_UNSIGNED_INT_IMAGE_بفر_EXT  0x9067
#تعریف_کرو GL_TEXTURE_بفر_وتھ_EXT      0x919D
#تعریف_کرو GL_TEXTURE_بفر_ناپ_EXT        0x919E
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXBUFFEREXTPROC) (GLenum نشانہ, GLenum internalformat, GLuint بفر_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXBUFFERRANGEEXTPROC) (GLenum نشانہ, GLenum internalformat, GLuint بفر_2, GLintptr وتھ_2, GLsizeiptr ناپ);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Tex_بفر_EXT (GLenum نشانہ, GLenum internalformat, GLuint بفر_2);
GL_APICALL فراغ GL_APIENTRY gl_Tex_بفر_Range_EXT (GLenum نشانہ, GLenum internalformat, GLuint بفر_2, GLintptr وتھ_2, GLsizeiptr ناپ);
#جے_انت
#جے_انت /* GL_EXT_texture_buffer */

#جے_بنا_تعریف GL_EXT_texture_compression_astc_decode_منوال
#تعریف_کرو GL_EXT_texture_compression_astc_decode_منوال 1
#تعریف_کرو GL_TEXTURE_ASTC_DECODE_PRECISION_EXT 0x8F69
#جے_انت /* GL_EXT_texture_compression_astc_decode_mode */

#جے_بنا_تعریف GL_EXT_texture_compression_bptc
#تعریف_کرو GL_EXT_texture_compression_bptc 1
#تعریف_کرو GL_COMPRESSED_RGBA_BPTC_UNORM_EXT 0x8E8C
#تعریف_کرو GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_EXT 0x8E8D
#تعریف_کرو GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_EXT 0x8E8E
#تعریف_کرو GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_EXT 0x8E8F
#جے_انت /* GL_EXT_texture_compression_bptc */

#جے_بنا_تعریف GL_EXT_texture_compression_dxt1
#تعریف_کرو GL_EXT_texture_compression_dxt1 1
#تعریف_کرو GL_COMPRESSED_RGB_S3TC_DXT1_EXT   0x83F0
#تعریف_کرو GL_COMPRESSED_RGBA_S3TC_DXT1_EXT  0x83F1
#جے_انت /* GL_EXT_texture_compression_dxt1 */

#جے_بنا_تعریف GL_EXT_texture_compression_rgtc
#تعریف_کرو GL_EXT_texture_compression_rgtc 1
#تعریف_کرو GL_COMPRESSED_RED_RGTC1_EXT       0x8DBB
#تعریف_کرو GL_COMPRESSED_SIGNED_RED_RGTC1_EXT 0x8DBC
#تعریف_کرو GL_COMPRESSED_RED_GREEN_RGTC2_EXT 0x8DBD
#تعریف_کرو GL_COMPRESSED_SIGNED_RED_GREEN_RGTC2_EXT 0x8DBE
#جے_انت /* GL_EXT_texture_compression_rgtc */

#جے_بنا_تعریف GL_EXT_texture_compression_s3tc
#تعریف_کرو GL_EXT_texture_compression_s3tc 1
#تعریف_کرو GL_COMPRESSED_RGBA_S3TC_DXT3_EXT  0x83F2
#تعریف_کرو GL_COMPRESSED_RGBA_S3TC_DXT5_EXT  0x83F3
#جے_انت /* GL_EXT_texture_compression_s3tc */

#جے_بنا_تعریف GL_EXT_texture_compression_s3tc_srgb
#تعریف_کرو GL_EXT_texture_compression_s3tc_srgb 1
#تعریف_کرو GL_COMPRESSED_SRGB_S3TC_DXT1_EXT  0x8C4C
#تعریف_کرو GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT 0x8C4D
#تعریف_کرو GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT 0x8C4E
#تعریف_کرو GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT 0x8C4F
#جے_انت /* GL_EXT_texture_compression_s3tc_srgb */

#جے_بنا_تعریف GL_EXT_texture_cube_map_array
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
#جے_انت /* GL_EXT_texture_cube_map_array */

#جے_بنا_تعریف GL_EXT_texture_filter_anisotropic
#تعریف_کرو GL_EXT_texture_filter_anisotropic 1
#تعریف_کرو GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#تعریف_کرو GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#جے_انت /* GL_EXT_texture_filter_anisotropic */

#جے_بنا_تعریف GL_EXT_texture_filter_minmax
#تعریف_کرو GL_EXT_texture_filter_minmax 1
#تعریف_کرو GL_TEXTURE_REDUCTION_منوال_EXT     0x9366
#تعریف_کرو GL_WEIGHTED_اوسطن_EXT           0x9367
#جے_انت /* GL_EXT_texture_filter_minmax */

#جے_بنا_تعریف GL_EXT_texture_format_BGRA8888
#تعریف_کرو GL_EXT_texture_format_BGRA8888 1
#جے_انت /* GL_EXT_texture_format_BGRA8888 */

#جے_بنا_تعریف GL_EXT_texture_format_sRGB_override
#تعریف_کرو GL_EXT_texture_format_sRGB_override 1
#تعریف_کرو GL_TEXTURE_FORMAT_SRGB_OVERRIDE_EXT 0x8FBF
#جے_انت /* GL_EXT_texture_format_sRGB_override */

#جے_بنا_تعریف GL_EXT_texture_mirror_clamp_منزل_کنارا
#تعریف_کرو GL_EXT_texture_mirror_clamp_منزل_کنارا 1
#تعریف_کرو GL_MIRROR_CLAMP_منزل_کنارا_EXT       0x8743
#جے_انت /* GL_EXT_texture_mirror_clamp_to_edge */

#جے_بنا_تعریف GL_EXT_texture_norm16
#تعریف_کرو GL_EXT_texture_norm16 1
#تعریف_کرو GL_R16_EXT                        0x822A
#تعریف_کرو GL_RG16_EXT                       0x822C
#تعریف_کرو GL_RGBA16_EXT                     0x805B
#تعریف_کرو GL_RGB16_EXT                      0x8054
#تعریف_کرو GL_RGB16_SNORM_EXT                0x8F9A
#جے_انت /* GL_EXT_texture_norm16 */

#جے_بنا_تعریف GL_EXT_texture_query_lod
#تعریف_کرو GL_EXT_texture_query_lod 1
#جے_انت /* GL_EXT_texture_query_lod */

#جے_بنا_تعریف GL_EXT_texture_rg
#تعریف_کرو GL_EXT_texture_rg 1
#تعریف_کرو GL_RED_EXT                        0x1903
#تعریف_کرو GL_RG_EXT                         0x8227
#تعریف_کرو GL_R8_EXT                         0x8229
#تعریف_کرو GL_RG8_EXT                        0x822B
#جے_انت /* GL_EXT_texture_rg */

#جے_بنا_تعریف GL_EXT_texture_sRGB_R8
#تعریف_کرو GL_EXT_texture_sRGB_R8 1
#تعریف_کرو GL_SR8_EXT                        0x8FBD
#جے_انت /* GL_EXT_texture_sRGB_R8 */

#جے_بنا_تعریف GL_EXT_texture_sRGB_RG8
#تعریف_کرو GL_EXT_texture_sRGB_RG8 1
#تعریف_کرو GL_SRG8_EXT                       0x8FBE
#جے_انت /* GL_EXT_texture_sRGB_RG8 */

#جے_بنا_تعریف GL_EXT_texture_sRGB_decode
#تعریف_کرو GL_EXT_texture_sRGB_decode 1
#تعریف_کرو GL_TEXTURE_SRGB_DECODE_EXT        0x8A48
#تعریف_کرو GL_DECODE_EXT                     0x8A49
#تعریف_کرو GL_SKIP_DECODE_EXT                0x8A4A
#جے_انت /* GL_EXT_texture_sRGB_decode */

#جے_بنا_تعریف GL_EXT_texture_shadow_lod
#تعریف_کرو GL_EXT_texture_shadow_lod 1
#جے_انت /* GL_EXT_texture_shadow_lod */

#جے_بنا_تعریف GL_EXT_texture_storage
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
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE1DEXTPROC) (GLenum نشانہ, GLsizei پدھراں, GLenum internalformat, GLsizei چوڑائی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE2DEXTPROC) (GLenum نشانہ, GLsizei پدھراں, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE3DEXTPROC) (GLenum نشانہ, GLsizei پدھراں, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGE1DEXTPROC) (GLuint texture, GLenum نشانہ, GLsizei پدھراں, GLenum internalformat, GLsizei چوڑائی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGE2DEXTPROC) (GLuint texture, GLenum نشانہ, GLsizei پدھراں, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGE3DEXTPROC) (GLuint texture, GLenum نشانہ, GLsizei پدھراں, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTexStorage1DEXT (GLenum نشانہ, GLsizei پدھراں, GLenum internalformat, GLsizei چوڑائی);
GL_APICALL فراغ GL_APIENTRY glTexStorage2DEXT (GLenum نشانہ, GLsizei پدھراں, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی);
GL_APICALL فراغ GL_APIENTRY glTexStorage3DEXT (GLenum نشانہ, GLsizei پدھراں, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2);
GL_APICALL فراغ GL_APIENTRY glTextureStorage1DEXT (GLuint texture, GLenum نشانہ, GLsizei پدھراں, GLenum internalformat, GLsizei چوڑائی);
GL_APICALL فراغ GL_APIENTRY glTextureStorage2DEXT (GLuint texture, GLenum نشانہ, GLsizei پدھراں, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی);
GL_APICALL فراغ GL_APIENTRY glTextureStorage3DEXT (GLuint texture, GLenum نشانہ, GLsizei پدھراں, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2);
#جے_انت
#جے_انت /* GL_EXT_texture_storage */

#جے_بنا_تعریف GL_EXT_texture_storage_compression
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
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGEATTRIBS2DEXTPROC) (GLenum نشانہ, GLsizei پدھراں, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی, ثابت GLint* attrib_list);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGEATTRIBS3DEXTPROC) (GLenum نشانہ, GLsizei پدھراں, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2, ثابت GLint* attrib_list);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTexStorageAttribs2DEXT (GLenum نشانہ, GLsizei پدھراں, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی, ثابت GLint* attrib_list);
GL_APICALL فراغ GL_APIENTRY glTexStorageAttribs3DEXT (GLenum نشانہ, GLsizei پدھراں, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2, ثابت GLint* attrib_list);
#جے_انت
#جے_انت /* GL_EXT_texture_storage_compression */

#جے_بنا_تعریف GL_EXT_texture_type_2_10_10_10_REV
#تعریف_کرو GL_EXT_texture_type_2_10_10_10_REV 1
#تعریف_کرو GL_UNSIGNED_INT_2_10_10_10_REV_EXT 0x8368
#جے_انت /* GL_EXT_texture_type_2_10_10_10_REV */

#جے_بنا_تعریف GL_EXT_texture_view
#تعریف_کرو GL_EXT_texture_view 1
#تعریف_کرو GL_TEXTURE_VIEW_MIN_LEVEL_EXT     0x82DB
#تعریف_کرو GL_TEXTURE_VIEW_عدد_پدھراں_EXT    0x82DC
#تعریف_کرو GL_TEXTURE_VIEW_MIN_LAYER_EXT     0x82DD
#تعریف_کرو GL_TEXTURE_VIEW_عدد_LAYERS_EXT    0x82DE
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTUREVIEWEXTPROC) (GLuint texture, GLenum نشانہ, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTextureViewEXT (GLuint texture, GLenum نشانہ, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
#جے_انت
#جے_انت /* GL_EXT_texture_view */

#جے_بنا_تعریف GL_EXT_unpack_subimage
#تعریف_کرو GL_EXT_unpack_subimage 1
#تعریف_کرو GL_UNPACK_صف_لمائی_EXT          0x0CF2
#تعریف_کرو GL_UNPACK_SKIP_صفاں_EXT           0x0CF3
#تعریف_کرو GL_UNPACK_SKIP_PIXELS_EXT         0x0CF4
#جے_انت /* GL_EXT_unpack_subimage */

#جے_بنا_تعریف GL_EXT_win32_keyed_mutex
#تعریف_کرو GL_EXT_win32_keyed_mutex 1
تعريفنوع GLboolean (GL_APIENTRYP PFNGLACQUIREKEYEDMUTEXWIN32EXTPROC) (GLuint حافظہ, GLuint64 کلید, GLuint timeout);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLRELEASEKEYEDMUTEXWIN32EXTPROC) (GLuint حافظہ, GLuint64 کلید);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL GLboolean GL_APIENTRY glAcquireKeyedMutexWin32EXT (GLuint حافظہ, GLuint64 کلید, GLuint timeout);
GL_APICALL GLboolean GL_APIENTRY glReleaseKeyedMutexWin32EXT (GLuint حافظہ, GLuint64 کلید);
#جے_انت
#جے_انت /* GL_EXT_win32_keyed_mutex */

#جے_بنا_تعریف GL_EXT_کھڑکی_rectangles
#تعریف_کرو GL_EXT_کھڑکی_rectangles 1
#تعریف_کرو GL_INCLUSIVE_EXT                  0x8F10
#تعریف_کرو GL_EXCLUSIVE_EXT                  0x8F11
#تعریف_کرو GL_کھڑکی_RECTANGLE_EXT           0x8F12
#تعریف_کرو GL_کھڑکی_RECTANGLE_منوال_EXT      0x8F13
#تعریف_کرو GL_MAX_کھڑکی_RECTANGLES_EXT      0x8F14
#تعریف_کرو GL_عدد_کھڑکی_RECTANGLES_EXT      0x8F15
تعريفنوع فراغ (GL_APIENTRYP PFNGLWINDOWRECTANGLESEXTPROC) (GLenum منوال, GLsizei گنتی, ثابت GLint *box);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_کھڑکی_Rectangles_EXT (GLenum منوال, GLsizei گنتی, ثابت GLint *box);
#جے_انت
#جے_انت /* GL_EXT_window_rectangles */

#جے_بنا_تعریف GL_FJ_shader_ثنائی_GCCSO
#تعریف_کرو GL_FJ_shader_ثنائی_GCCSO 1
#تعریف_کرو GL_GCCSO_SHADER_ثنائی_FJ         0x9260
#جے_انت /* GL_FJ_shader_binary_GCCSO */

#جے_بنا_تعریف GL_HUAWEI_پروگرام_ثنائی
#تعریف_کرو GL_HUAWEI_پروگرام_ثنائی 1
#تعریف_کرو GL_پروگرام_ثنائی_HUAWEI          0x9771
#جے_انت /* GL_HUAWEI_program_binary */

#جے_بنا_تعریف GL_HUAWEI_shader_ثنائی
#تعریف_کرو GL_HUAWEI_shader_ثنائی 1
#تعریف_کرو GL_SHADER_ثنائی_HUAWEI           0x9770
#جے_انت /* GL_HUAWEI_shader_binary */

#جے_بنا_تعریف GL_IMG_bindless_texture
#تعریف_کرو GL_IMG_bindless_texture 1
تعريفنوع GLuint64 (GL_APIENTRYP PFNGLGETTEXTUREHANDLEIMGPROC) (GLuint texture);
تعريفنوع GLuint64 (GL_APIENTRYP PFNGLGETTEXTURESAMPLERHANDLEIMGPROC) (GLuint texture, GLuint sampler);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMHANDLEUI64IMGPROC) (GLint location, GLuint64 قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMHANDLEUI64VIMGPROC) (GLint location, GLsizei گنتی, ثابت GLuint64 *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64IMGPROC) (GLuint پروگرام, GLint location, GLuint64 قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64VIMGPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint64 *اقدار);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL GLuint64 GL_APIENTRY glGetTextureHandleIMG (GLuint texture);
GL_APICALL GLuint64 GL_APIENTRY glGetTextureSamplerHandleIMG (GLuint texture, GLuint sampler);
GL_APICALL فراغ GL_APIENTRY gl_اکسار_Handleui64_IMG (GLint location, GLuint64 قدر);
GL_APICALL فراغ GL_APIENTRY gl_اکسار_Handleui64v_IMG (GLint location, GLsizei گنتی, ثابت GLuint64 *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_اکسار_Handleui64_IMG (GLuint پروگرام, GLint location, GLuint64 قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_اکسار_Handleui64v_IMG (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint64 *اقدار);
#جے_انت
#جے_انت /* GL_IMG_bindless_texture */

#جے_بنا_تعریف GL_IMG_framebuffer_downsample
#تعریف_کرو GL_IMG_framebuffer_downsample 1
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_AND_DOWNSAMPLE_IMG 0x913C
#تعریف_کرو GL_عدد_DOWNSAMPLE_SCALES_IMG      0x913D
#تعریف_کرو GL_DOWNSAMPLE_SCALES_IMG          0x913E
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SCALE_IMG 0x913F
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DDOWNSAMPLEIMGPROC) (GLenum نشانہ, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint xscale, GLint yscale);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURELAYERDOWNSAMPLEIMGPROC) (GLenum نشانہ, GLenum attachment, GLuint texture, GLint level, GLint layer, GLint xscale, GLint yscale);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferTexture2DDownsampleIMG (GLenum نشانہ, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint xscale, GLint yscale);
GL_APICALL فراغ GL_APIENTRY glFramebufferTextureLayerDownsampleIMG (GLenum نشانہ, GLenum attachment, GLuint texture, GLint level, GLint layer, GLint xscale, GLint yscale);
#جے_انت
#جے_انت /* GL_IMG_framebuffer_downsample */

#جے_بنا_تعریف GL_IMG_multisampled_render_منزل_texture
#تعریف_کرو GL_IMG_multisampled_render_منزل_texture 1
#تعریف_کرو GL_RENDERBUFFER_SAMPLES_IMG       0x9133
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_IMG 0x9134
#تعریف_کرو GL_MAX_SAMPLES_IMG                0x9135
#تعریف_کرو GL_TEXTURE_SAMPLES_IMG            0x9136
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEIMGPROC) (GLenum نشانہ, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEIMGPROC) (GLenum نشانہ, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glRenderbufferStorageMultisampleIMG (GLenum نشانہ, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی);
GL_APICALL فراغ GL_APIENTRY glFramebufferTexture2DMultisampleIMG (GLenum نشانہ, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#جے_انت
#جے_انت /* GL_IMG_multisampled_render_to_texture */

#جے_بنا_تعریف GL_IMG_پروگرام_ثنائی
#تعریف_کرو GL_IMG_پروگرام_ثنائی 1
#تعریف_کرو GL_SGX_پروگرام_ثنائی_IMG         0x9130
#جے_انت /* GL_IMG_program_binary */

#جے_بنا_تعریف GL_IMG_read_format
#تعریف_کرو GL_IMG_read_format 1
#تعریف_کرو GL_BGRA_IMG                       0x80E1
#تعریف_کرو GL_UNSIGNED_SHORT_4_4_4_4_REV_IMG 0x8365
#جے_انت /* GL_IMG_read_format */

#جے_بنا_تعریف GL_IMG_shader_ثنائی
#تعریف_کرو GL_IMG_shader_ثنائی 1
#تعریف_کرو GL_SGX_ثنائی_IMG                 0x8C0A
#جے_انت /* GL_IMG_shader_binary */

#جے_بنا_تعریف GL_IMG_texture_compression_pvrtc
#تعریف_کرو GL_IMG_texture_compression_pvrtc 1
#تعریف_کرو GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG 0x8C00
#تعریف_کرو GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG 0x8C01
#تعریف_کرو GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG 0x8C02
#تعریف_کرو GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG 0x8C03
#جے_انت /* GL_IMG_texture_compression_pvrtc */

#جے_بنا_تعریف GL_IMG_texture_compression_pvrtc2
#تعریف_کرو GL_IMG_texture_compression_pvrtc2 1
#تعریف_کرو GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG 0x9137
#تعریف_کرو GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG 0x9138
#جے_انت /* GL_IMG_texture_compression_pvrtc2 */

#جے_بنا_تعریف GL_IMG_texture_filter_cubic
#تعریف_کرو GL_IMG_texture_filter_cubic 1
#تعریف_کرو GL_CUBIC_IMG                      0x9139
#تعریف_کرو GL_CUBIC_MIPMAP_سبھ_توں_نیڑے_IMG       0x913A
#تعریف_کرو GL_CUBIC_MIPMAP_خطی_IMG        0x913B
#جے_انت /* GL_IMG_texture_filter_cubic */

#جے_بنا_تعریف GL_INTEL_blackhole_render
#تعریف_کرو GL_INTEL_blackhole_render 1
#تعریف_کرو GL_BLACKHOLE_RENDER_INTEL         0x83FC
#جے_انت /* GL_INTEL_blackhole_render */

#جے_بنا_تعریف GL_INTEL_conservative_rasterization
#تعریف_کرو GL_INTEL_conservative_rasterization 1
#تعریف_کرو GL_CONSERVATIVE_RASTERIZATION_INTEL 0x83FE
#جے_انت /* GL_INTEL_conservative_rasterization */

#جے_بنا_تعریف GL_INTEL_framebuffer_CMAA
#تعریف_کرو GL_INTEL_framebuffer_CMAA 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLAPPLYFRAMEBUFFERATTACHMENTCMAAINTELPROC) (فراغ);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glApplyFramebufferAttachmentCMAAINTEL (فراغ);
#جے_انت
#جے_انت /* GL_INTEL_framebuffer_CMAA */

#جے_بنا_تعریف GL_INTEL_performance_query
#تعریف_کرو GL_INTEL_performance_query 1
#تعریف_کرو GL_PERFQUERY_SINGLE_CONTEXT_INTEL 0x00000000
#تعریف_کرو GL_PERFQUERY_GLOBAL_CONTEXT_INTEL 0x00000001
#تعریف_کرو GL_PERFQUERY_WAIT_INTEL           0x83FB
#تعریف_کرو GL_PERFQUERY_FLUSH_INTEL          0x83FA
#تعریف_کرو GL_PERFQUERY_DONOT_FLUSH_INTEL    0x83F9
#تعریف_کرو GL_PERFQUERY_COUNTER_EVENT_INTEL  0x94F0
#تعریف_کرو GL_PERFQUERY_COUNTER_DURATION_NORM_INTEL 0x94F1
#تعریف_کرو GL_PERFQUERY_COUNTER_DURATION_RAW_INTEL 0x94F2
#تعریف_کرو GL_PERFQUERY_COUNTER_THROUGHPUT_INTEL 0x94F3
#تعریف_کرو GL_PERFQUERY_COUNTER_RAW_INTEL    0x94F4
#تعریف_کرو GL_PERFQUERY_COUNTER_TIMESTAMP_INTEL 0x94F5
#تعریف_کرو GL_PERFQUERY_COUNTER_انکڑے_UINT32_INTEL 0x94F8
#تعریف_کرو GL_PERFQUERY_COUNTER_انکڑے_UINT64_INTEL 0x94F9
#تعریف_کرو GL_PERFQUERY_COUNTER_انکڑے_FLOAT_INTEL 0x94FA
#تعریف_کرو GL_PERFQUERY_COUNTER_انکڑے_DOUBLE_INTEL 0x94FB
#تعریف_کرو GL_PERFQUERY_COUNTER_انکڑے_BOOL32_INTEL 0x94FC
#تعریف_کرو GL_PERFQUERY_QUERY_NAME_لمائی_MAX_INTEL 0x94FD
#تعریف_کرو GL_PERFQUERY_COUNTER_NAME_لمائی_MAX_INTEL 0x94FE
#تعریف_کرو GL_PERFQUERY_COUNTER_DESC_لمائی_MAX_INTEL 0x94FF
#تعریف_کرو GL_PERFQUERY_GPA_EXTENDED_COUNTERS_INTEL 0x9500
تعريفنوع فراغ (GL_APIENTRYP PFNGLBEGINPERFQUERYINTELPROC) (GLuint queryHandle);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCREATEPERFQUERYINTELPROC) (GLuint queryId, GLuint *queryHandle);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEPERFQUERYINTELPROC) (GLuint queryHandle);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENDPERFQUERYINTELPROC) (GLuint queryHandle);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFIRSTPERFQUERYIDINTELPROC) (GLuint *queryId);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNEXTPERFQUERYIDINTELPROC) (GLuint queryId, GLuint *اگلا_Query_Id);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFCOUNTERINFOINTELPROC) (GLuint queryId, GLuint counterId, GLuint counter_Name_لمائی, GLchar *counterName, GLuint counter_Desc_لمائی, GLchar *counterDesc, GLuint *counter_وتھ, GLuint *counter_انکڑے_ناپ, GLuint *counterTypeEnum, GLuint *counter_انکڑے_Type_Enum, GLuint64 *raw_Counter_Max_قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFQUERYDATAINTELPROC) (GLuint queryHandle, GLuint flags, GLsizei انکڑے_ناپ_2, فراغ *انکڑے, GLuint *بائٹاں_Written);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFQUERYIDBYNAMEINTELPROC) (GLchar *queryName, GLuint *queryId);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPERFQUERYINFOINTELPROC) (GLuint queryId, GLuint query_Name_لمائی, GLchar *queryName, GLuint *انکڑے_ناپ_2, GLuint *noCounters, GLuint *noInstances, GLuint *caps_نقاب);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glBeginPerfQueryINTEL (GLuint queryHandle);
GL_APICALL فراغ GL_APIENTRY glCreatePerfQueryINTEL (GLuint queryId, GLuint *queryHandle);
GL_APICALL فراغ GL_APIENTRY glDeletePerfQueryINTEL (GLuint queryHandle);
GL_APICALL فراغ GL_APIENTRY gl_سرا_Perf_Query_INTEL (GLuint queryHandle);
GL_APICALL فراغ GL_APIENTRY gl_Get_پہلا_Perf_Query_Id_INTEL (GLuint *queryId);
GL_APICALL فراغ GL_APIENTRY gl_Get_اگلا_Perf_Query_Id_INTEL (GLuint queryId, GLuint *اگلا_Query_Id);
GL_APICALL فراغ GL_APIENTRY glGetPerfCounterInfoINTEL (GLuint queryId, GLuint counterId, GLuint counter_Name_لمائی, GLchar *counterName, GLuint counter_Desc_لمائی, GLchar *counterDesc, GLuint *counter_وتھ, GLuint *counter_انکڑے_ناپ, GLuint *counterTypeEnum, GLuint *counter_انکڑے_Type_Enum, GLuint64 *raw_Counter_Max_قدر);
GL_APICALL فراغ GL_APIENTRY gl_Get_Perf_Query_انکڑے_INTEL (GLuint queryHandle, GLuint flags, GLsizei انکڑے_ناپ_2, فراغ *انکڑے, GLuint *بائٹاں_Written);
GL_APICALL فراغ GL_APIENTRY glGetPerfQueryIdByNameINTEL (GLchar *queryName, GLuint *queryId);
GL_APICALL فراغ GL_APIENTRY glGetPerfQueryInfoINTEL (GLuint queryId, GLuint query_Name_لمائی, GLchar *queryName, GLuint *انکڑے_ناپ_2, GLuint *noCounters, GLuint *noInstances, GLuint *caps_نقاب);
#جے_انت
#جے_انت /* GL_INTEL_performance_query */

#جے_بنا_تعریف GL_MESA_bgra
#تعریف_کرو GL_MESA_bgra 1
#تعریف_کرو GL_BGR_EXT                        0x80E0
#جے_انت /* GL_MESA_bgra */

#جے_بنا_تعریف GL_MESA_framebuffer_flip_x
#تعریف_کرو GL_MESA_framebuffer_flip_x 1
#تعریف_کرو GL_FRAMEBUFFER_FLIP_X_MESA        0x8BBC
#جے_انت /* GL_MESA_framebuffer_flip_x */

#جے_بنا_تعریف GL_MESA_framebuffer_flip_y
#تعریف_کرو GL_MESA_framebuffer_flip_y 1
#تعریف_کرو GL_FRAMEBUFFER_FLIP_Y_MESA        0x8BBB
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERPARAMETERIMESAPROC) (GLenum نشانہ, GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFRAMEBUFFERPARAMETERIVMESAPROC) (GLenum نشانہ, GLenum pname, GLint *params);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferParameteriMESA (GLenum نشانہ, GLenum pname, GLint param);
GL_APICALL فراغ GL_APIENTRY glGetFramebufferParameterivMESA (GLenum نشانہ, GLenum pname, GLint *params);
#جے_انت
#جے_انت /* GL_MESA_framebuffer_flip_y */

#جے_بنا_تعریف GL_MESA_framebuffer_وٹاندرا_xy
#تعریف_کرو GL_MESA_framebuffer_وٹاندرا_xy 1
#تعریف_کرو GL_FRAMEBUFFER_وٹاندرا_XY_MESA       0x8BBD
#جے_انت /* GL_MESA_framebuffer_swap_xy */

#جے_بنا_تعریف GL_MESA_پروگرام_ثنائی_formats
#تعریف_کرو GL_MESA_پروگرام_ثنائی_formats 1
#تعریف_کرو GL_پروگرام_ثنائی_FORMAT_MESA     0x875F
#جے_انت /* GL_MESA_program_binary_formats */

#جے_بنا_تعریف GL_MESA_sampler_objects
#تعریف_کرو GL_MESA_sampler_objects 1
#تعریف_کرو GL_SAMPLER_BINDING                0x8919
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENSAMPLERSPROC) (GLsizei گنتی, GLuint *samplers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETESAMPLERSPROC) (GLsizei گنتی, ثابت GLuint *samplers);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISSAMPLERPROC) (GLuint sampler);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDSAMPLERPROC) (GLuint unit, GLuint sampler);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIPROC) (GLuint sampler, GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, ثابت GLint *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERFPROC) (GLuint sampler, GLenum pname, GLfloat param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, ثابت GLfloat *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, GLfloat *params);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glGenSamplers (GLsizei گنتی, GLuint *samplers);
GL_APICALL فراغ GL_APIENTRY glDeleteSamplers (GLsizei گنتی, ثابت GLuint *samplers);
GL_APICALL GLboolean GL_APIENTRY glIsSampler (GLuint sampler);
GL_APICALL فراغ GL_APIENTRY glBindSampler (GLuint unit, GLuint sampler);
GL_APICALL فراغ GL_APIENTRY glSamplerParameteri (GLuint sampler, GLenum pname, GLint param);
GL_APICALL فراغ GL_APIENTRY glSamplerParameteriv (GLuint sampler, GLenum pname, ثابت GLint *param);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterf (GLuint sampler, GLenum pname, GLfloat param);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterfv (GLuint sampler, GLenum pname, ثابت GLfloat *param);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameteriv (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameterfv (GLuint sampler, GLenum pname, GLfloat *params);
#جے_انت
#جے_انت /* GL_MESA_sampler_objects */

#جے_بنا_تعریف GL_MESA_shader_integer_functions
#تعریف_کرو GL_MESA_shader_integer_functions 1
#جے_انت /* GL_MESA_shader_integer_functions */

#جے_بنا_تعریف GL_MESA_texture_const_bandwidth
#تعریف_کرو GL_MESA_texture_const_bandwidth 1
#تعریف_کرو GL_CONST_BW_TILING_MESA           0x8BBE
#جے_انت /* GL_MESA_texture_const_bandwidth */

#جے_بنا_تعریف GL_NVX_blend_equation_advanced_multi_draw_buffers
#تعریف_کرو GL_NVX_blend_equation_advanced_multi_draw_buffers 1
#جے_انت /* GL_NVX_blend_equation_advanced_multi_draw_buffers */

#جے_بنا_تعریف GL_NV_bindless_texture
#تعریف_کرو GL_NV_bindless_texture 1
تعريفنوع GLuint64 (GL_APIENTRYP PFNGLGETTEXTUREHANDLENVPROC) (GLuint texture);
تعريفنوع GLuint64 (GL_APIENTRYP PFNGLGETTEXTURESAMPLERHANDLENVPROC) (GLuint texture, GLuint sampler);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMAKETEXTUREHANDLERESIDENTNVPROC) (GLuint64 handle);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMAKETEXTUREHANDLENONRESIDENTNVPROC) (GLuint64 handle);
تعريفنوع GLuint64 (GL_APIENTRYP PFNGLGETIMAGEHANDLENVPROC) (GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMAKEIMAGEHANDLERESIDENTNVPROC) (GLuint64 handle, GLenum access);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMAKEIMAGEHANDLENONRESIDENTNVPROC) (GLuint64 handle);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMHANDLEUI64NVPROC) (GLint location, GLuint64 قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMHANDLEUI64VNVPROC) (GLint location, GLsizei گنتی, ثابت GLuint64 *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64NVPROC) (GLuint پروگرام, GLint location, GLuint64 قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64VNVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint64 *اقدار);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISTEXTUREHANDLERESIDENTNVPROC) (GLuint64 handle);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISIMAGEHANDLERESIDENTNVPROC) (GLuint64 handle);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL GLuint64 GL_APIENTRY glGetTextureHandleNV (GLuint texture);
GL_APICALL GLuint64 GL_APIENTRY glGetTextureSamplerHandleNV (GLuint texture, GLuint sampler);
GL_APICALL فراغ GL_APIENTRY glMakeTextureHandleResidentNV (GLuint64 handle);
GL_APICALL فراغ GL_APIENTRY glMakeTextureHandleNonResidentNV (GLuint64 handle);
GL_APICALL GLuint64 GL_APIENTRY glGetImageHandleNV (GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format);
GL_APICALL فراغ GL_APIENTRY glMakeImageHandleResidentNV (GLuint64 handle, GLenum access);
GL_APICALL فراغ GL_APIENTRY glMakeImageHandleNonResidentNV (GLuint64 handle);
GL_APICALL فراغ GL_APIENTRY gl_اکسار_Handleui64_NV (GLint location, GLuint64 قدر);
GL_APICALL فراغ GL_APIENTRY gl_اکسار_Handleui64v_NV (GLint location, GLsizei گنتی, ثابت GLuint64 *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_اکسار_Handleui64_NV (GLuint پروگرام, GLint location, GLuint64 قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_اکسار_Handleui64v_NV (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint64 *اقدار);
GL_APICALL GLboolean GL_APIENTRY glIsTextureHandleResidentNV (GLuint64 handle);
GL_APICALL GLboolean GL_APIENTRY glIsImageHandleResidentNV (GLuint64 handle);
#جے_انت
#جے_انت /* GL_NV_bindless_texture */

#جے_بنا_تعریف GL_NV_blend_equation_advanced
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
#تعریف_کرو GL_DST_وچ_NV                      0x928B
#تعریف_کرو GL_DST_NV                         0x9287
#تعریف_کرو GL_DST_باہرلا_NV                     0x928D
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
#تعریف_کرو GL_SRC_وچ_NV                      0x928A
#تعریف_کرو GL_SRC_NV                         0x9286
#تعریف_کرو GL_SRC_باہرلا_NV                     0x928C
#تعریف_کرو GL_SRC_OVER_NV                    0x9288
#تعریف_کرو GL_UNCORRELATED_NV                0x9282
#تعریف_کرو GL_VIVIDLIGHT_NV                  0x92A6
#تعریف_کرو GL_XOR_NV                         0x1506
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDPARAMETERINVPROC) (GLenum pname, GLint قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDBARRIERNVPROC) (فراغ);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glBlendParameteriNV (GLenum pname, GLint قدر);
GL_APICALL فراغ GL_APIENTRY glBlendBarrierNV (فراغ);
#جے_انت
#جے_انت /* GL_NV_blend_equation_advanced */

#جے_بنا_تعریف GL_NV_blend_equation_advanced_coherent
#تعریف_کرو GL_NV_blend_equation_advanced_coherent 1
#تعریف_کرو GL_BLEND_ADVANCED_COHERENT_NV     0x9285
#جے_انت /* GL_NV_blend_equation_advanced_coherent */

#جے_بنا_تعریف GL_NV_blend_minmax_ضارب
#تعریف_کرو GL_NV_blend_minmax_ضارب 1
#تعریف_کرو GL_ضارب_MIN_AMD                 0x901C
#تعریف_کرو GL_ضارب_MAX_AMD                 0x901D
#جے_انت /* GL_NV_blend_minmax_factor */

#جے_بنا_تعریف GL_NV_clip_space_w_scaling
#تعریف_کرو GL_NV_clip_space_w_scaling 1
#تعریف_کرو GL_VIEWPORT_POSITION_W_SCALE_NV   0x937C
#تعریف_کرو GL_VIEWPORT_POSITION_W_SCALE_X_COEFF_NV 0x937D
#تعریف_کرو GL_VIEWPORT_POSITION_W_SCALE_Y_COEFF_NV 0x937E
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTPOSITIONWSCALENVPROC) (GLuint اشاریہ, GLfloat xcoeff, GLfloat ycoeff);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glViewportPositionWScaleNV (GLuint اشاریہ, GLfloat xcoeff, GLfloat ycoeff);
#جے_انت
#جے_انت /* GL_NV_clip_space_w_scaling */

#جے_بنا_تعریف GL_NV_compute_shader_derivatives
#تعریف_کرو GL_NV_compute_shader_derivatives 1
#جے_انت /* GL_NV_compute_shader_derivatives */

#جے_بنا_تعریف GL_NV_conditional_render
#تعریف_کرو GL_NV_conditional_render 1
#تعریف_کرو GL_QUERY_WAIT_NV                  0x8E13
#تعریف_کرو GL_QUERY_NO_WAIT_NV               0x8E14
#تعریف_کرو GL_QUERY_BY_REGION_WAIT_NV        0x8E15
#تعریف_کرو GL_QUERY_BY_REGION_NO_WAIT_NV     0x8E16
تعريفنوع فراغ (GL_APIENTRYP PFNGLBEGINCONDITIONALRENDERNVPROC) (GLuint id, GLenum منوال);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENDCONDITIONALRENDERNVPROC) (فراغ);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glBeginConditionalRenderNV (GLuint id, GLenum منوال);
GL_APICALL فراغ GL_APIENTRY gl_سرا_Conditional_Render_NV (فراغ);
#جے_انت
#جے_انت /* GL_NV_conditional_render */

#جے_بنا_تعریف GL_NV_conservative_raster
#تعریف_کرو GL_NV_conservative_raster 1
#تعریف_کرو GL_CONSERVATIVE_RASTERIZATION_NV  0x9346
#تعریف_کرو GL_SUBPIXEL_PRECISION_BIAS_X_بٹ_NV 0x9347
#تعریف_کرو GL_SUBPIXEL_PRECISION_BIAS_Y_بٹ_NV 0x9348
#تعریف_کرو GL_MAX_SUBPIXEL_PRECISION_BIAS_بٹ_NV 0x9349
تعريفنوع فراغ (GL_APIENTRYP PFNGLSUBPIXELPRECISIONBIASNVPROC) (GLuint xbits, GLuint ybits);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glSubpixelPrecisionBiasNV (GLuint xbits, GLuint ybits);
#جے_انت
#جے_انت /* GL_NV_conservative_raster */

#جے_بنا_تعریف GL_NV_conservative_raster_pre_snap
#تعریف_کرو GL_NV_conservative_raster_pre_snap 1
#تعریف_کرو GL_CONSERVATIVE_RASTER_منوال_PRE_SNAP_NV 0x9550
#جے_انت /* GL_NV_conservative_raster_pre_snap */

#جے_بنا_تعریف GL_NV_conservative_raster_pre_snap_triangles
#تعریف_کرو GL_NV_conservative_raster_pre_snap_triangles 1
#تعریف_کرو GL_CONSERVATIVE_RASTER_منوال_NV    0x954D
#تعریف_کرو GL_CONSERVATIVE_RASTER_منوال_POST_SNAP_NV 0x954E
#تعریف_کرو GL_CONSERVATIVE_RASTER_منوال_PRE_SNAP_TRIANGLES_NV 0x954F
تعريفنوع فراغ (GL_APIENTRYP PFNGLCONSERVATIVERASTERPARAMETERINVPROC) (GLenum pname, GLint param);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glConservativeRasterParameteriNV (GLenum pname, GLint param);
#جے_انت
#جے_انت /* GL_NV_conservative_raster_pre_snap_triangles */

#جے_بنا_تعریف GL_NV_copy_بفر
#تعریف_کرو GL_NV_copy_بفر 1
#تعریف_کرو GL_COPY_READ_بفر_NV            0x8F36
#تعریف_کرو GL_COPY_WRITE_بفر_NV           0x8F37
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYBUFFERSUBDATANVPROC) (GLenum read_نشانہ, GLenum write_نشانہ, GLintptr read_وتھ, GLintptr write_وتھ, GLsizeiptr ناپ);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Copy_بفر_Sub_انکڑے_NV (GLenum read_نشانہ, GLenum write_نشانہ, GLintptr read_وتھ, GLintptr write_وتھ, GLsizeiptr ناپ);
#جے_انت
#جے_انت /* GL_NV_copy_buffer */

#جے_بنا_تعریف GL_NV_coverage_sample
#تعریف_کرو GL_NV_coverage_sample 1
#تعریف_کرو GL_COVERAGE_COMPONENT_NV          0x8ED0
#تعریف_کرو GL_COVERAGE_COMPONENT4_NV         0x8ED1
#تعریف_کرو GL_COVERAGE_ATTACHMENT_NV         0x8ED2
#تعریف_کرو GL_COVERAGE_BUFFERS_NV            0x8ED3
#تعریف_کرو GL_COVERAGE_SAMPLES_NV            0x8ED4
#تعریف_کرو GL_COVERAGE_ALL_FRAGMENTS_NV      0x8ED5
#تعریف_کرو GL_COVERAGE_کنارا_FRAGMENTS_NV     0x8ED6
#تعریف_کرو GL_COVERAGE_AUTOMATIC_NV          0x8ED7
#تعریف_کرو GL_COVERAGE_بفر_ثنائی_ہندسہ_NV         0x00008000
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOVERAGEMASKNVPROC) (GLboolean نقاب);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOVERAGEOPERATIONNVPROC) (GLenum operation);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Coverage_نقاب_NV (GLboolean نقاب);
GL_APICALL فراغ GL_APIENTRY glCoverageOperationNV (GLenum operation);
#جے_انت
#جے_انت /* GL_NV_coverage_sample */

#جے_بنا_تعریف GL_NV_ڈونگھائی_nonlinear
#تعریف_کرو GL_NV_ڈونگھائی_nonlinear 1
#تعریف_کرو GL_ڈونگھائی_COMPONENT16_NONLINEAR_NV 0x8E2C
#جے_انت /* GL_NV_depth_nonlinear */

#جے_بنا_تعریف GL_NV_draw_buffers
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
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWBUFFERSNVPROC) (GLsizei n, ثابت GLenum *bufs);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawBuffersNV (GLsizei n, ثابت GLenum *bufs);
#جے_انت
#جے_انت /* GL_NV_draw_buffers */

#جے_بنا_تعریف GL_NV_draw_instanced
#تعریف_کرو GL_NV_draw_instanced 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDNVPROC) (GLenum منوال, GLint پہلا, GLsizei گنتی, GLsizei primcount);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDNVPROC) (GLenum منوال, GLsizei گنتی, GLenum type, ثابت فراغ *indices, GLsizei primcount);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawArraysInstancedNV (GLenum منوال, GLint پہلا, GLsizei گنتی, GLsizei primcount);
GL_APICALL فراغ GL_APIENTRY glDrawElementsInstancedNV (GLenum منوال, GLsizei گنتی, GLenum type, ثابت فراغ *indices, GLsizei primcount);
#جے_انت
#جے_انت /* GL_NV_draw_instanced */

#جے_بنا_تعریف GL_NV_draw_vulkan_image
#تعریف_کرو GL_NV_draw_vulkan_image 1
تعريفنوع فراغ (GL_APIENTRY  *GLVULKANPROCNV)(فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWVKIMAGENVPROC) (GLuint64 vkImage, GLuint sampler, GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat z, GLfloat s0, GLfloat t0, GLfloat s1, GLfloat t1);
تعريفنوع GLVULKANPROCNV (GL_APIENTRYP PFNGLGETVKPROCADDRNVPROC) (ثابت GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLWAITVKSEMAPHORENVPROC) (GLuint64 vkSemaphore);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSIGNALVKSEMAPHORENVPROC) (GLuint64 vkSemaphore);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSIGNALVKFENCENVPROC) (GLuint64 vkFence);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawVkImageNV (GLuint64 vkImage, GLuint sampler, GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat z, GLfloat s0, GLfloat t0, GLfloat s1, GLfloat t1);
GL_APICALL GLVULKANPROCNV GL_APIENTRY glGetVkProcAddrNV (ثابت GLchar *name);
GL_APICALL فراغ GL_APIENTRY glWaitVkSemaphoreNV (GLuint64 vkSemaphore);
GL_APICALL فراغ GL_APIENTRY glSignalVkSemaphoreNV (GLuint64 vkSemaphore);
GL_APICALL فراغ GL_APIENTRY glSignalVkFenceNV (GLuint64 vkFence);
#جے_انت
#جے_انت /* GL_NV_draw_vulkan_image */

#جے_بنا_تعریف GL_NV_explicit_attrib_location
#تعریف_کرو GL_NV_explicit_attrib_location 1
#جے_انت /* GL_NV_explicit_attrib_location */

#جے_بنا_تعریف GL_NV_fbo_color_attachments
#تعریف_کرو GL_NV_fbo_color_attachments 1
#تعریف_کرو GL_MAX_COLOR_ATTACHMENTS_NV       0x8CDF
#جے_انت /* GL_NV_fbo_color_attachments */

#جے_بنا_تعریف GL_NV_fence
#تعریف_کرو GL_NV_fence 1
#تعریف_کرو GL_ALL_COMPLETED_NV               0x84F2
#تعریف_کرو GL_FENCE_حالت_NV                0x84F3
#تعریف_کرو GL_FENCE_CONDITION_NV             0x84F4
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEFENCESNVPROC) (GLsizei n, ثابت GLuint *fences);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENFENCESNVPROC) (GLsizei n, GLuint *fences);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISFENCENVPROC) (GLuint fence);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLTESTFENCENVPROC) (GLuint fence);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFENCEIVNVPROC) (GLuint fence, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFINISHFENCENVPROC) (GLuint fence);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSETFENCENVPROC) (GLuint fence, GLenum condition);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDeleteFencesNV (GLsizei n, ثابت GLuint *fences);
GL_APICALL فراغ GL_APIENTRY glGenFencesNV (GLsizei n, GLuint *fences);
GL_APICALL GLboolean GL_APIENTRY glIsFenceNV (GLuint fence);
GL_APICALL GLboolean GL_APIENTRY glTestFenceNV (GLuint fence);
GL_APICALL فراغ GL_APIENTRY glGetFenceivNV (GLuint fence, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY gl_انت_Fence_NV (GLuint fence);
GL_APICALL فراغ GL_APIENTRY gl_سیٹ_Fence_NV (GLuint fence, GLenum condition);
#جے_انت
#جے_انت /* GL_NV_fence */

#جے_بنا_تعریف GL_NV_fill_rectangle
#تعریف_کرو GL_NV_fill_rectangle 1
#تعریف_کرو GL_FILL_RECTANGLE_NV              0x933C
#جے_انت /* GL_NV_fill_rectangle */

#جے_بنا_تعریف GL_NV_fragment_coverage_منزل_color
#تعریف_کرو GL_NV_fragment_coverage_منزل_color 1
#تعریف_کرو GL_FRAGMENT_COVERAGE_منزل_COLOR_NV  0x92DD
#تعریف_کرو GL_FRAGMENT_COVERAGE_COLOR_NV     0x92DE
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAGMENTCOVERAGECOLORNVPROC) (GLuint color);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFragmentCoverageColorNV (GLuint color);
#جے_انت
#جے_انت /* GL_NV_fragment_coverage_to_color */

#جے_بنا_تعریف GL_NV_fragment_shader_barycentric
#تعریف_کرو GL_NV_fragment_shader_barycentric 1
#جے_انت /* GL_NV_fragment_shader_barycentric */

#جے_بنا_تعریف GL_NV_fragment_shader_interlock
#تعریف_کرو GL_NV_fragment_shader_interlock 1
#جے_انت /* GL_NV_fragment_shader_interlock */

#جے_بنا_تعریف GL_NV_framebuffer_blit
#تعریف_کرو GL_NV_framebuffer_blit 1
#تعریف_کرو GL_READ_FRAMEBUFFER_NV            0x8CA8
#تعریف_کرو GL_DRAW_FRAMEBUFFER_NV            0x8CA9
#تعریف_کرو GL_DRAW_FRAMEBUFFER_BINDING_NV    0x8CA6
#تعریف_کرو GL_READ_FRAMEBUFFER_BINDING_NV    0x8CAA
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLITFRAMEBUFFERNVPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield نقاب, GLenum filter);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glBlitFramebufferNV (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield نقاب, GLenum filter);
#جے_انت
#جے_انت /* GL_NV_framebuffer_blit */

#جے_بنا_تعریف GL_NV_framebuffer_mixed_samples
#تعریف_کرو GL_NV_framebuffer_mixed_samples 1
#تعریف_کرو GL_COVERAGE_MODULATION_جدول_NV   0x9331
#تعریف_کرو GL_COLOR_SAMPLES_NV               0x8E20
#تعریف_کرو GL_ڈونگھائی_SAMPLES_NV               0x932D
#تعریف_کرو GL_STENCIL_SAMPLES_NV             0x932E
#تعریف_کرو GL_MIXED_ڈونگھائی_SAMPLES_SUPPORTED_NV 0x932F
#تعریف_کرو GL_MIXED_STENCIL_SAMPLES_SUPPORTED_NV 0x9330
#تعریف_کرو GL_COVERAGE_MODULATION_NV         0x9332
#تعریف_کرو GL_COVERAGE_MODULATION_جدول_ناپ_NV 0x9333
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOVERAGEMODULATIONTABLENVPROC) (GLsizei n, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETCOVERAGEMODULATIONTABLENVPROC) (GLsizei buf_ناپ, GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOVERAGEMODULATIONNVPROC) (GLenum components);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Coverage_Modulation_جدول_NV (GLsizei n, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY gl_Get_Coverage_Modulation_جدول_NV (GLsizei buf_ناپ, GLfloat *v);
GL_APICALL فراغ GL_APIENTRY glCoverageModulationNV (GLenum components);
#جے_انت
#جے_انت /* GL_NV_framebuffer_mixed_samples */

#جے_بنا_تعریف GL_NV_framebuffer_multisample
#تعریف_کرو GL_NV_framebuffer_multisample 1
#تعریف_کرو GL_RENDERBUFFER_SAMPLES_NV        0x8CAB
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_NV 0x8D56
#تعریف_کرو GL_MAX_SAMPLES_NV                 0x8D57
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLENVPROC) (GLenum نشانہ, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glRenderbufferStorageMultisampleNV (GLenum نشانہ, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی);
#جے_انت
#جے_انت /* GL_NV_framebuffer_multisample */

#جے_بنا_تعریف GL_NV_generate_mipmap_sRGB
#تعریف_کرو GL_NV_generate_mipmap_sRGB 1
#جے_انت /* GL_NV_generate_mipmap_sRGB */

#جے_بنا_تعریف GL_NV_geometry_shader_passthrough
#تعریف_کرو GL_NV_geometry_shader_passthrough 1
#جے_انت /* GL_NV_geometry_shader_passthrough */

#جے_بنا_تعریف GL_NV_gpu_shader5
#تعریف_کرو GL_NV_gpu_shader5 1
تعريفنوع khronos_int64_t GLint64EXT;
تعريفنوع khronos_uint64_t GLuint64EXT;
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
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1I64NVPROC) (GLint location, GLint64EXT x);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2I64NVPROC) (GLint location, GLint64EXT x, GLint64EXT y);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3I64NVPROC) (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4I64NVPROC) (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1I64VNVPROC) (GLint location, GLsizei گنتی, ثابت GLint64EXT *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2I64VNVPROC) (GLint location, GLsizei گنتی, ثابت GLint64EXT *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3I64VNVPROC) (GLint location, GLsizei گنتی, ثابت GLint64EXT *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4I64VNVPROC) (GLint location, GLsizei گنتی, ثابت GLint64EXT *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1UI64NVPROC) (GLint location, GLuint64EXT x);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2UI64NVPROC) (GLint location, GLuint64EXT x, GLuint64EXT y);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3UI64NVPROC) (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4UI64NVPROC) (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1UI64VNVPROC) (GLint location, GLsizei گنتی, ثابت GLuint64EXT *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2UI64VNVPROC) (GLint location, GLsizei گنتی, ثابت GLuint64EXT *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3UI64VNVPROC) (GLint location, GLsizei گنتی, ثابت GLuint64EXT *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4UI64VNVPROC) (GLint location, GLsizei گنتی, ثابت GLuint64EXT *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETUNIFORMI64VNVPROC) (GLuint پروگرام, GLint location, GLint64EXT *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1I64NVPROC) (GLuint پروگرام, GLint location, GLint64EXT x);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2I64NVPROC) (GLuint پروگرام, GLint location, GLint64EXT x, GLint64EXT y);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3I64NVPROC) (GLuint پروگرام, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4I64NVPROC) (GLuint پروگرام, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1I64VNVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint64EXT *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2I64VNVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint64EXT *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3I64VNVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint64EXT *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4I64VNVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint64EXT *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UI64NVPROC) (GLuint پروگرام, GLint location, GLuint64EXT x);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UI64NVPROC) (GLuint پروگرام, GLint location, GLuint64EXT x, GLuint64EXT y);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UI64NVPROC) (GLuint پروگرام, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UI64NVPROC) (GLuint پروگرام, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UI64VNVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint64EXT *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UI64VNVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint64EXT *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UI64VNVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint64EXT *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UI64VNVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint64EXT *قدر);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glUniform1i64NV (GLint location, GLint64EXT x);
GL_APICALL فراغ GL_APIENTRY glUniform2i64NV (GLint location, GLint64EXT x, GLint64EXT y);
GL_APICALL فراغ GL_APIENTRY glUniform3i64NV (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
GL_APICALL فراغ GL_APIENTRY glUniform4i64NV (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
GL_APICALL فراغ GL_APIENTRY glUniform1i64vNV (GLint location, GLsizei گنتی, ثابت GLint64EXT *قدر);
GL_APICALL فراغ GL_APIENTRY glUniform2i64vNV (GLint location, GLsizei گنتی, ثابت GLint64EXT *قدر);
GL_APICALL فراغ GL_APIENTRY glUniform3i64vNV (GLint location, GLsizei گنتی, ثابت GLint64EXT *قدر);
GL_APICALL فراغ GL_APIENTRY glUniform4i64vNV (GLint location, GLsizei گنتی, ثابت GLint64EXT *قدر);
GL_APICALL فراغ GL_APIENTRY glUniform1ui64NV (GLint location, GLuint64EXT x);
GL_APICALL فراغ GL_APIENTRY glUniform2ui64NV (GLint location, GLuint64EXT x, GLuint64EXT y);
GL_APICALL فراغ GL_APIENTRY glUniform3ui64NV (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
GL_APICALL فراغ GL_APIENTRY glUniform4ui64NV (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
GL_APICALL فراغ GL_APIENTRY glUniform1ui64vNV (GLint location, GLsizei گنتی, ثابت GLuint64EXT *قدر);
GL_APICALL فراغ GL_APIENTRY glUniform2ui64vNV (GLint location, GLsizei گنتی, ثابت GLuint64EXT *قدر);
GL_APICALL فراغ GL_APIENTRY glUniform3ui64vNV (GLint location, GLsizei گنتی, ثابت GLuint64EXT *قدر);
GL_APICALL فراغ GL_APIENTRY glUniform4ui64vNV (GLint location, GLsizei گنتی, ثابت GLuint64EXT *قدر);
GL_APICALL فراغ GL_APIENTRY glGetUniformi64vNV (GLuint پروگرام, GLint location, GLint64EXT *params);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform1i64_NV (GLuint پروگرام, GLint location, GLint64EXT x);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform2i64_NV (GLuint پروگرام, GLint location, GLint64EXT x, GLint64EXT y);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform3i64_NV (GLuint پروگرام, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform4i64_NV (GLuint پروگرام, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform1i64v_NV (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint64EXT *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform2i64v_NV (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint64EXT *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform3i64v_NV (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint64EXT *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform4i64v_NV (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint64EXT *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform1ui64_NV (GLuint پروگرام, GLint location, GLuint64EXT x);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform2ui64_NV (GLuint پروگرام, GLint location, GLuint64EXT x, GLuint64EXT y);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform3ui64_NV (GLuint پروگرام, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform4ui64_NV (GLuint پروگرام, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform1ui64v_NV (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint64EXT *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform2ui64v_NV (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint64EXT *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform3ui64v_NV (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint64EXT *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform4ui64v_NV (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint64EXT *قدر);
#جے_انت
#جے_انت /* GL_NV_gpu_shader5 */

#جے_بنا_تعریف GL_NV_image_formats
#تعریف_کرو GL_NV_image_formats 1
#جے_انت /* GL_NV_image_formats */

#جے_بنا_تعریف GL_NV_instanced_arrays
#تعریف_کرو GL_NV_instanced_arrays 1
#تعریف_کرو GL_راس_ATTRIB_ARRAY_مقسوم_علیہ_NV 0x88FE
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBDIVISORNVPROC) (GLuint اشاریہ, GLuint مقسوم_علیہ);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib_مقسوم_علیہ_NV (GLuint اشاریہ, GLuint مقسوم_علیہ);
#جے_انت
#جے_انت /* GL_NV_instanced_arrays */

#جے_بنا_تعریف GL_NV_internalformat_sample_query
#تعریف_کرو GL_NV_internalformat_sample_query 1
#تعریف_کرو GL_TEXTURE_2D_MULTISAMPLE         0x9100
#تعریف_کرو GL_TEXTURE_2D_MULTISAMPLE_ARRAY   0x9102
#تعریف_کرو GL_MULTISAMPLES_NV                0x9371
#تعریف_کرو GL_SUPERSAMPLE_SCALE_X_NV         0x9372
#تعریف_کرو GL_SUPERSAMPLE_SCALE_Y_NV         0x9373
#تعریف_کرو GL_CONFORMANT_NV                  0x9374
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTERNALFORMATSAMPLEIVNVPROC) (GLenum نشانہ, GLenum internalformat, GLsizei samples, GLenum pname, GLsizei گنتی, GLint *params);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glGetInternalformatSampleivNV (GLenum نشانہ, GLenum internalformat, GLsizei samples, GLenum pname, GLsizei گنتی, GLint *params);
#جے_انت
#جے_انت /* GL_NV_internalformat_sample_query */

#جے_بنا_تعریف GL_NV_حافظہ_attachment
#تعریف_کرو GL_NV_حافظہ_attachment 1
#تعریف_کرو GL_ATTACHED_حافظہ_OBJECT_NV      0x95A4
#تعریف_کرو GL_ATTACHED_حافظہ_وتھ_NV      0x95A5
#تعریف_کرو GL_حافظہ_ATTACHABLE_ALIGNMENT_NV 0x95A6
#تعریف_کرو GL_حافظہ_ATTACHABLE_ناپ_NV      0x95A7
#تعریف_کرو GL_حافظہ_ATTACHABLE_NV           0x95A8
#تعریف_کرو GL_DETACHED_حافظہ_INCARNATION_NV 0x95A9
#تعریف_کرو GL_DETACHED_TEXTURES_NV           0x95AA
#تعریف_کرو GL_DETACHED_BUFFERS_NV            0x95AB
#تعریف_کرو GL_MAX_DETACHED_TEXTURES_NV       0x95AC
#تعریف_کرو GL_MAX_DETACHED_BUFFERS_NV        0x95AD
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETMEMORYOBJECTDETACHEDRESOURCESUIVNVPROC) (GLuint حافظہ, GLenum pname, GLint پہلا, GLsizei گنتی, GLuint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRESETMEMORYOBJECTPARAMETERNVPROC) (GLuint حافظہ, GLenum pname);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXATTACHMEMORYNVPROC) (GLenum نشانہ, GLuint حافظہ, GLuint64 وتھ_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBUFFERATTACHMEMORYNVPROC) (GLenum نشانہ, GLuint حافظہ, GLuint64 وتھ_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTUREATTACHMEMORYNVPROC) (GLuint texture, GLuint حافظہ, GLuint64 وتھ_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLNAMEDBUFFERATTACHMEMORYNVPROC) (GLuint بفر_2, GLuint حافظہ, GLuint64 وتھ_2);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Get_حافظہ_Object_Detached_Resourcesuiv_NV (GLuint حافظہ, GLenum pname, GLint پہلا, GLsizei گنتی, GLuint *params);
GL_APICALL فراغ GL_APIENTRY gl_Reset_حافظہ_Object_Parameter_NV (GLuint حافظہ, GLenum pname);
GL_APICALL فراغ GL_APIENTRY gl_Tex_Attach_حافظہ_NV (GLenum نشانہ, GLuint حافظہ, GLuint64 وتھ_2);
GL_APICALL فراغ GL_APIENTRY gl_بفر_Attach_حافظہ_NV (GLenum نشانہ, GLuint حافظہ, GLuint64 وتھ_2);
GL_APICALL فراغ GL_APIENTRY gl_Texture_Attach_حافظہ_NV (GLuint texture, GLuint حافظہ, GLuint64 وتھ_2);
GL_APICALL فراغ GL_APIENTRY gl_Named_بفر_Attach_حافظہ_NV (GLuint بفر_2, GLuint حافظہ, GLuint64 وتھ_2);
#جے_انت
#جے_انت /* GL_NV_memory_attachment */

#جے_بنا_تعریف GL_NV_حافظہ_object_sparse
#تعریف_کرو GL_NV_حافظہ_object_sparse 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLBUFFERPAGECOMMITMENTMEMNVPROC) (GLenum نشانہ, GLintptr وتھ_2, GLsizeiptr ناپ, GLuint حافظہ, GLuint64 mem_وتھ, GLboolean commit);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPAGECOMMITMENTMEMNVPROC) (GLenum نشانہ, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2, GLuint حافظہ, GLuint64 وتھ_2, GLboolean commit);
تعريفنوع فراغ (GL_APIENTRYP PFNGLNAMEDBUFFERPAGECOMMITMENTMEMNVPROC) (GLuint بفر_2, GLintptr وتھ_2, GLsizeiptr ناپ, GLuint حافظہ, GLuint64 mem_وتھ, GLboolean commit);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTUREPAGECOMMITMENTMEMNVPROC) (GLuint texture, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2, GLuint حافظہ, GLuint64 وتھ_2, GLboolean commit);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_بفر_ورقہ_Commitment_Mem_NV (GLenum نشانہ, GLintptr وتھ_2, GLsizeiptr ناپ, GLuint حافظہ, GLuint64 mem_وتھ, GLboolean commit);
GL_APICALL فراغ GL_APIENTRY gl_Tex_ورقہ_Commitment_Mem_NV (GLenum نشانہ, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2, GLuint حافظہ, GLuint64 وتھ_2, GLboolean commit);
GL_APICALL فراغ GL_APIENTRY gl_Named_بفر_ورقہ_Commitment_Mem_NV (GLuint بفر_2, GLintptr وتھ_2, GLsizeiptr ناپ, GLuint حافظہ, GLuint64 mem_وتھ, GLboolean commit);
GL_APICALL فراغ GL_APIENTRY gl_Texture_ورقہ_Commitment_Mem_NV (GLuint texture, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2, GLuint حافظہ, GLuint64 وتھ_2, GLboolean commit);
#جے_انت
#جے_انت /* GL_NV_memory_object_sparse */

#جے_بنا_تعریف GL_NV_mesh_shader
#تعریف_کرو GL_NV_mesh_shader 1
#تعریف_کرو GL_MESH_SHADER_NV                 0x9559
#تعریف_کرو GL_TASK_SHADER_NV                 0x955A
#تعریف_کرو GL_MAX_MESH_اکسار_بلاکاں_NV     0x8E60
#تعریف_کرو GL_MAX_MESH_TEXTURE_IMAGE_UNITS_NV 0x8E61
#تعریف_کرو GL_MAX_MESH_IMAGE_UNIFORMS_NV     0x8E62
#تعریف_کرو GL_MAX_MESH_اکسار_COMPONENTS_NV 0x8E63
#تعریف_کرو GL_MAX_MESH_ATOMIC_COUNTER_BUFFERS_NV 0x8E64
#تعریف_کرو GL_MAX_MESH_ATOMIC_COUNTERS_NV    0x8E65
#تعریف_کرو GL_MAX_MESH_SHADER_STORAGE_بلاکاں_NV 0x8E66
#تعریف_کرو GL_MAX_COMBINED_MESH_اکسار_COMPONENTS_NV 0x8E67
#تعریف_کرو GL_MAX_TASK_اکسار_بلاکاں_NV     0x8E68
#تعریف_کرو GL_MAX_TASK_TEXTURE_IMAGE_UNITS_NV 0x8E69
#تعریف_کرو GL_MAX_TASK_IMAGE_UNIFORMS_NV     0x8E6A
#تعریف_کرو GL_MAX_TASK_اکسار_COMPONENTS_NV 0x8E6B
#تعریف_کرو GL_MAX_TASK_ATOMIC_COUNTER_BUFFERS_NV 0x8E6C
#تعریف_کرو GL_MAX_TASK_ATOMIC_COUNTERS_NV    0x8E6D
#تعریف_کرو GL_MAX_TASK_SHADER_STORAGE_بلاکاں_NV 0x8E6E
#تعریف_کرو GL_MAX_COMBINED_TASK_اکسار_COMPONENTS_NV 0x8E6F
#تعریف_کرو GL_MAX_MESH_WORK_گروہ_INVOCATIONS_NV 0x95A2
#تعریف_کرو GL_MAX_TASK_WORK_گروہ_INVOCATIONS_NV 0x95A3
#تعریف_کرو GL_MAX_MESH_کل_حافظہ_ناپ_NV  0x9536
#تعریف_کرو GL_MAX_TASK_کل_حافظہ_ناپ_NV  0x9537
#تعریف_کرو GL_MAX_MESH_OUTPUT_VERTICES_NV    0x9538
#تعریف_کرو GL_MAX_MESH_OUTPUT_PRIMITIVES_NV  0x9539
#تعریف_کرو GL_MAX_TASK_OUTPUT_گنتی_NV       0x953A
#تعریف_کرو GL_MAX_DRAW_MESH_TASKS_گنتی_NV   0x953D
#تعریف_کرو GL_MAX_MESH_VIEWS_NV              0x9557
#تعریف_کرو GL_MESH_OUTPUT_فی_راس_GRANULARITY_NV 0x92DF
#تعریف_کرو GL_MESH_OUTPUT_فی_PRIMITIVE_GRANULARITY_NV 0x9543
#تعریف_کرو GL_MAX_MESH_WORK_گروہ_ناپ_NV    0x953B
#تعریف_کرو GL_MAX_TASK_WORK_گروہ_ناپ_NV    0x953C
#تعریف_کرو GL_MESH_WORK_گروہ_ناپ_NV        0x953E
#تعریف_کرو GL_TASK_WORK_گروہ_ناپ_NV        0x953F
#تعریف_کرو GL_MESH_VERTICES_باہرلا_NV           0x9579
#تعریف_کرو GL_MESH_PRIMITIVES_باہرلا_NV         0x957A
#تعریف_کرو GL_MESH_OUTPUT_TYPE_NV            0x957B
#تعریف_کرو GL_اکسار_بلاک_REFERENCED_BY_MESH_SHADER_NV 0x959C
#تعریف_کرو GL_اکسار_بلاک_REFERENCED_BY_TASK_SHADER_NV 0x959D
#تعریف_کرو GL_REFERENCED_BY_MESH_SHADER_NV   0x95A0
#تعریف_کرو GL_REFERENCED_BY_TASK_SHADER_NV   0x95A1
#تعریف_کرو GL_MESH_SHADER_ثنائی_ہندسہ_NV             0x00000040
#تعریف_کرو GL_TASK_SHADER_ثنائی_ہندسہ_NV             0x00000080
#تعریف_کرو GL_MESH_SUBROUTINE_NV             0x957C
#تعریف_کرو GL_TASK_SUBROUTINE_NV             0x957D
#تعریف_کرو GL_MESH_SUBROUTINE_اکسار_NV     0x957E
#تعریف_کرو GL_TASK_SUBROUTINE_اکسار_NV     0x957F
#تعریف_کرو GL_ATOMIC_COUNTER_بفر_REFERENCED_BY_MESH_SHADER_NV 0x959E
#تعریف_کرو GL_ATOMIC_COUNTER_بفر_REFERENCED_BY_TASK_SHADER_NV 0x959F
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWMESHTASKSNVPROC) (GLuint پہلا, GLuint گنتی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWMESHTASKSINDIRECTNVPROC) (GLintptr اسدھا);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWMESHTASKSINDIRECTNVPROC) (GLintptr اسدھا, GLsizei drawcount, GLsizei stride);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTNVPROC) (GLintptr اسدھا, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDrawMeshTasksNV (GLuint پہلا, GLuint گنتی);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Mesh_Tasks_اسدھا_NV (GLintptr اسدھا);
GL_APICALL فراغ GL_APIENTRY gl_Multi_Draw_Mesh_Tasks_اسدھا_NV (GLintptr اسدھا, GLsizei drawcount, GLsizei stride);
GL_APICALL فراغ GL_APIENTRY gl_Multi_Draw_Mesh_Tasks_اسدھا_گنتی_NV (GLintptr اسدھا, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
#جے_انت
#جے_انت /* GL_NV_mesh_shader */

#جے_بنا_تعریف GL_NV_non_مربع_matrices
#تعریف_کرو GL_NV_non_مربع_matrices 1
#تعریف_کرو GL_FLOAT_MAT2x3_NV                0x8B65
#تعریف_کرو GL_FLOAT_MAT2x4_NV                0x8B66
#تعریف_کرو GL_FLOAT_MAT3x2_NV                0x8B67
#تعریف_کرو GL_FLOAT_MAT3x4_NV                0x8B68
#تعریف_کرو GL_FLOAT_MAT4x2_NV                0x8B69
#تعریف_کرو GL_FLOAT_MAT4x3_NV                0x8B6A
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX2X3FVNVPROC) (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX3X2FVNVPROC) (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX2X4FVNVPROC) (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX4X2FVNVPROC) (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX3X4FVNVPROC) (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX4X3FVNVPROC) (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_اکسار_Matrix2x3fv_NV (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_اکسار_Matrix3x2fv_NV (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_اکسار_Matrix2x4fv_NV (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_اکسار_Matrix4x2fv_NV (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_اکسار_Matrix3x4fv_NV (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_اکسار_Matrix4x3fv_NV (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
#جے_انت
#جے_انت /* GL_NV_non_square_matrices */

#جے_بنا_تعریف GL_NV_pack_subimage
#تعریف_کرو GL_NV_pack_subimage 1
#تعریف_کرو GL_PACK_صف_لمائی_NV             0x0D02
#تعریف_کرو GL_PACK_SKIP_صفاں_NV              0x0D03
#تعریف_کرو GL_PACK_SKIP_PIXELS_NV            0x0D04
#جے_انت /* GL_NV_pack_subimage */

#جے_بنا_تعریف GL_NV_رستہ_rendering
#تعریف_کرو GL_NV_رستہ_rendering 1
تعريفنوع مزدوج GLdouble;
#تعریف_کرو GL_رستہ_FORMAT_SVG_NV             0x9070
#تعریف_کرو GL_رستہ_FORMAT_PS_NV              0x9071
#تعریف_کرو GL_STANDARD_FONT_NAME_NV          0x9072
#تعریف_کرو GL_SYSTEM_FONT_NAME_NV            0x9073
#تعریف_کرو GL_FILE_NAME_NV                   0x9074
#تعریف_کرو GL_رستہ_STROKE_چوڑائی_NV           0x9075
#تعریف_کرو GL_رستہ_سرا_CAPS_NV               0x9076
#تعریف_کرو GL_رستہ_INITIAL_سرا_CAP_NV        0x9077
#تعریف_کرو GL_رستہ_TERMINAL_سرا_CAP_NV       0x9078
#تعریف_کرو GL_رستہ_JOIN_STYLE_NV             0x9079
#تعریف_کرو GL_رستہ_MITER_حد_بندی_NV            0x907A
#تعریف_کرو GL_رستہ_DASH_CAPS_NV              0x907B
#تعریف_کرو GL_رستہ_INITIAL_DASH_CAP_NV       0x907C
#تعریف_کرو GL_رستہ_TERMINAL_DASH_CAP_NV      0x907D
#تعریف_کرو GL_رستہ_DASH_وتھ_NV            0x907E
#تعریف_کرو GL_رستہ_CLIENT_لمائی_NV          0x907F
#تعریف_کرو GL_رستہ_FILL_منوال_NV              0x9080
#تعریف_کرو GL_رستہ_FILL_نقاب_NV              0x9081
#تعریف_کرو GL_رستہ_FILL_COVER_منوال_NV        0x9082
#تعریف_کرو GL_رستہ_STROKE_COVER_منوال_NV      0x9083
#تعریف_کرو GL_رستہ_STROKE_نقاب_NV            0x9084
#تعریف_کرو GL_گنتی_اتے_NV                    0x9088
#تعریف_کرو GL_گنتی_تھلے_NV                  0x9089
#تعریف_کرو GL_رستہ_OBJECT_BOUNDING_BOX_NV    0x908A
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
#تعریف_کرو GL_BOUNDING_BOX_دا_BOUNDING_BOXES_NV 0x909C
#تعریف_کرو GL_رستہ_COMMAND_گنتی_NV          0x909D
#تعریف_کرو GL_رستہ_COORD_گنتی_NV            0x909E
#تعریف_کرو GL_رستہ_DASH_ARRAY_گنتی_NV       0x909F
#تعریف_کرو GL_رستہ_COMPUTED_لمائی_NV        0x90A0
#تعریف_کرو GL_رستہ_FILL_BOUNDING_BOX_NV      0x90A1
#تعریف_کرو GL_رستہ_STROKE_BOUNDING_BOX_NV    0x90A2
#تعریف_کرو GL_مربع_NV                      0x90A3
#تعریف_کرو GL_گیڑا_NV                       0x90A4
#تعریف_کرو GL_TRIANGULAR_NV                  0x90A5
#تعریف_کرو GL_BEVEL_NV                       0x90A6
#تعریف_کرو GL_MITER_REVERT_NV                0x90A7
#تعریف_کرو GL_MITER_TRUNCATE_NV              0x90A8
#تعریف_کرو GL_SKIP_MISSING_GLYPH_NV          0x90A9
#تعریف_کرو GL_USE_MISSING_GLYPH_NV           0x90AA
#تعریف_کرو GL_رستہ_ERROR_POSITION_NV         0x90AB
#تعریف_کرو GL_ACCUM_ADJACENT_جوڑے_NV        0x90AD
#تعریف_کرو GL_ADJACENT_جوڑے_NV              0x90AE
#تعریف_کرو GL_پہلا_منزل_REST_NV               0x90AF
#تعریف_کرو GL_رستہ_GEN_منوال_NV               0x90B0
#تعریف_کرو GL_رستہ_GEN_COEFF_NV              0x90B1
#تعریف_کرو GL_رستہ_GEN_COMPONENTS_NV         0x90B3
#تعریف_کرو GL_رستہ_STENCIL_FUNC_NV           0x90B7
#تعریف_کرو GL_رستہ_STENCIL_REF_NV            0x90B8
#تعریف_کرو GL_رستہ_STENCIL_قدر_نقاب_NV     0x90B9
#تعریف_کرو GL_رستہ_STENCIL_ڈونگھائی_وتھ_ضارب_NV 0x90BD
#تعریف_کرو GL_رستہ_STENCIL_ڈونگھائی_وتھ_UNITS_NV 0x90BE
#تعریف_کرو GL_رستہ_COVER_ڈونگھائی_FUNC_NV       0x90BF
#تعریف_کرو GL_رستہ_DASH_وتھ_RESET_NV      0x90B4
#تعریف_کرو GL_MOVE_منزل_RESETS_NV              0x90B5
#تعریف_کرو GL_MOVE_منزل_CONTINUES_NV           0x90B6
#تعریف_کرو GL_CLOSE_رستہ_NV                  0x00
#تعریف_کرو GL_MOVE_منزل_NV                     0x02
#تعریف_کرو GL_RELATIVE_MOVE_منزل_NV            0x03
#تعریف_کرو GL_سطر_منزل_NV                     0x04
#تعریف_کرو GL_RELATIVE_سطر_منزل_NV            0x05
#تعریف_کرو GL_HORIZONTAL_سطر_منزل_NV          0x06
#تعریف_کرو GL_RELATIVE_HORIZONTAL_سطر_منزل_NV 0x07
#تعریف_کرو GL_VERTICAL_سطر_منزل_NV            0x08
#تعریف_کرو GL_RELATIVE_VERTICAL_سطر_منزل_NV   0x09
#تعریف_کرو GL_QUADRATIC_ونگ_منزل_NV          0x0A
#تعریف_کرو GL_RELATIVE_QUADRATIC_ونگ_منزل_NV 0x0B
#تعریف_کرو GL_CUBIC_ونگ_منزل_NV              0x0C
#تعریف_کرو GL_RELATIVE_CUBIC_ونگ_منزل_NV     0x0D
#تعریف_کرو GL_SMOOTH_QUADRATIC_ونگ_منزل_NV   0x0E
#تعریف_کرو GL_RELATIVE_SMOOTH_QUADRATIC_ونگ_منزل_NV 0x0F
#تعریف_کرو GL_SMOOTH_CUBIC_ونگ_منزل_NV       0x10
#تعریف_کرو GL_RELATIVE_SMOOTH_CUBIC_ونگ_منزل_NV 0x11
#تعریف_کرو GL_SMALL_CCW_ARC_منزل_NV            0x12
#تعریف_کرو GL_RELATIVE_SMALL_CCW_ARC_منزل_NV   0x13
#تعریف_کرو GL_SMALL_CW_ARC_منزل_NV             0x14
#تعریف_کرو GL_RELATIVE_SMALL_CW_ARC_منزل_NV    0x15
#تعریف_کرو GL_LARGE_CCW_ARC_منزل_NV            0x16
#تعریف_کرو GL_RELATIVE_LARGE_CCW_ARC_منزل_NV   0x17
#تعریف_کرو GL_LARGE_CW_ARC_منزل_NV             0x18
#تعریف_کرو GL_RELATIVE_LARGE_CW_ARC_منزل_NV    0x19
#تعریف_کرو GL_RESTART_رستہ_NV                0xF0
#تعریف_کرو GL_DUP_پہلا_CUBIC_ونگ_منزل_NV    0xF2
#تعریف_کرو GL_DUP_آخری_CUBIC_ونگ_منزل_NV     0xF4
#تعریف_کرو GL_RECT_NV                        0xF6
#تعریف_کرو GL_CIRCULAR_CCW_ARC_منزل_NV         0xF8
#تعریف_کرو GL_CIRCULAR_CW_ARC_منزل_NV          0xFA
#تعریف_کرو GL_CIRCULAR_TANGENT_ARC_منزل_NV     0xFC
#تعریف_کرو GL_ARC_منزل_NV                      0xFE
#تعریف_کرو GL_RELATIVE_ARC_منزل_NV             0xFF
#تعریف_کرو GL_BOLD_ثنائی_ہندسہ_NV                    0x01
#تعریف_کرو GL_ITALIC_ثنائی_ہندسہ_NV                  0x02
#تعریف_کرو GL_GLYPH_چوڑائی_ثنائی_ہندسہ_NV             0x01
#تعریف_کرو GL_GLYPH_اچائی_ثنائی_ہندسہ_NV            0x02
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
#تعریف_کرو GL_FONT_اچائی_ثنائی_ہندسہ_NV             0x00800000
#تعریف_کرو GL_FONT_MAX_ADVANCE_چوڑائی_ثنائی_ہندسہ_NV  0x01000000
#تعریف_کرو GL_FONT_MAX_ADVANCE_اچائی_ثنائی_ہندسہ_NV 0x02000000
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
#تعریف_کرو GL_FONT_نشانہ_UNAVAILABLE_NV     0x9369
#تعریف_کرو GL_FONT_UNAVAILABLE_NV            0x936A
#تعریف_کرو GL_FONT_UNINTELLIGIBLE_NV         0x936B
#تعریف_کرو GL_CONIC_ونگ_منزل_NV              0x1A
#تعریف_کرو GL_RELATIVE_CONIC_ونگ_منزل_NV     0x1B
#تعریف_کرو GL_FONT_عدد_GLYPH_INDICES_ثنائی_ہندسہ_NV  0x20000000
#تعریف_کرو GL_STANDARD_FONT_FORMAT_NV        0x936C
#تعریف_کرو GL_رستہ_PROJECTION_NV             0x1701
#تعریف_کرو GL_رستہ_MODELVIEW_NV              0x1700
#تعریف_کرو GL_رستہ_MODELVIEW_ڈھیر_ڈونگھائی_NV  0x0BA3
#تعریف_کرو GL_رستہ_MODELVIEW_میٹرکس_NV       0x0BA6
#تعریف_کرو GL_رستہ_MAX_MODELVIEW_ڈھیر_ڈونگھائی_NV 0x0D36
#تعریف_کرو GL_رستہ_TRANSPOSE_MODELVIEW_میٹرکس_NV 0x84E3
#تعریف_کرو GL_رستہ_PROJECTION_ڈھیر_ڈونگھائی_NV 0x0BA4
#تعریف_کرو GL_رستہ_PROJECTION_میٹرکس_NV      0x0BA7
#تعریف_کرو GL_رستہ_MAX_PROJECTION_ڈھیر_ڈونگھائی_NV 0x0D38
#تعریف_کرو GL_رستہ_TRANSPOSE_PROJECTION_میٹرکس_NV 0x84E4
#تعریف_کرو GL_FRAGMENT_داخلہ_NV              0x936D
تعريفنوع GLuint (GL_APIENTRYP PFNGLGENPATHSNVPROC) (GLsizei range);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEPATHSNVPROC) (GLuint رستہ, GLsizei range);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISPATHNVPROC) (GLuint رستہ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHCOMMANDSNVPROC) (GLuint رستہ, GLsizei عدد_Commands, ثابت GLubyte *commands, GLsizei عدد_Coords, GLenum coordType, ثابت فراغ *coords);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHCOORDSNVPROC) (GLuint رستہ, GLsizei عدد_Coords, GLenum coordType, ثابت فراغ *coords);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHSUBCOMMANDSNVPROC) (GLuint رستہ, GLsizei command_شروع, GLsizei commands_منزل_Delete, GLsizei عدد_Commands, ثابت GLubyte *commands, GLsizei عدد_Coords, GLenum coordType, ثابت فراغ *coords);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHSUBCOORDSNVPROC) (GLuint رستہ, GLsizei coord_شروع, GLsizei عدد_Coords, GLenum coordType, ثابت فراغ *coords);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHSTRINGNVPROC) (GLuint رستہ, GLenum format, GLsizei لمائی, ثابت فراغ *رستہ_String);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHGLYPHSNVPROC) (GLuint پہلا_رستہ_Name, GLenum font_نشانہ, ثابت فراغ *fontName, GLbitfield fontStyle, GLsizei عدد_Glyphs, GLenum type, ثابت فراغ *charcodes, GLenum handleMissingGlyphs, GLuint رستہ_Parameter_Template, GLfloat emScale);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHGLYPHRANGENVPROC) (GLuint پہلا_رستہ_Name, GLenum font_نشانہ, ثابت فراغ *fontName, GLbitfield fontStyle, GLuint پہلا_Glyph, GLsizei عدد_Glyphs, GLenum handleMissingGlyphs, GLuint رستہ_Parameter_Template, GLfloat emScale);
تعريفنوع فراغ (GL_APIENTRYP PFNGLWEIGHTPATHSNVPROC) (GLuint نتیجہ_رستہ, GLsizei عدد_Paths, ثابت GLuint *paths, ثابت GLfloat *weights);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYPATHNVPROC) (GLuint نتیجہ_رستہ, GLuint src_رستہ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLINTERPOLATEPATHSNVPROC) (GLuint نتیجہ_رستہ, GLuint رستہ_A, GLuint رستہ_B, GLfloat بھار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTRANSFORMPATHNVPROC) (GLuint نتیجہ_رستہ, GLuint src_رستہ, GLenum transformType, ثابت GLfloat *transform_اقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHPARAMETERIVNVPROC) (GLuint رستہ, GLenum pname, ثابت GLint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHPARAMETERINVPROC) (GLuint رستہ, GLenum pname, GLint قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHPARAMETERFVNVPROC) (GLuint رستہ, GLenum pname, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHPARAMETERFNVPROC) (GLuint رستہ, GLenum pname, GLfloat قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHDASHARRAYNVPROC) (GLuint رستہ, GLsizei dash_گنتی, ثابت GLfloat *dashArray);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHSTENCILFUNCNVPROC) (GLenum func, GLint ref, GLuint نقاب);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHSTENCILDEPTHOFFSETNVPROC) (GLfloat ضارب, GLfloat units);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILFILLPATHNVPROC) (GLuint رستہ, GLenum fill_منوال, GLuint نقاب);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILSTROKEPATHNVPROC) (GLuint رستہ, GLint reference, GLuint نقاب);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILFILLPATHINSTANCEDNVPROC) (GLsizei عدد_Paths, GLenum رستہ_Name_Type, ثابت فراغ *paths, GLuint رستہ_ادھار, GLenum fill_منوال, GLuint نقاب, GLenum transformType, ثابت GLfloat *transform_اقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILSTROKEPATHINSTANCEDNVPROC) (GLsizei عدد_Paths, GLenum رستہ_Name_Type, ثابت فراغ *paths, GLuint رستہ_ادھار, GLint reference, GLuint نقاب, GLenum transformType, ثابت GLfloat *transform_اقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATHCOVERDEPTHFUNCNVPROC) (GLenum func);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOVERFILLPATHNVPROC) (GLuint رستہ, GLenum cover_منوال);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOVERSTROKEPATHNVPROC) (GLuint رستہ, GLenum cover_منوال);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOVERFILLPATHINSTANCEDNVPROC) (GLsizei عدد_Paths, GLenum رستہ_Name_Type, ثابت فراغ *paths, GLuint رستہ_ادھار, GLenum cover_منوال, GLenum transformType, ثابت GLfloat *transform_اقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOVERSTROKEPATHINSTANCEDNVPROC) (GLsizei عدد_Paths, GLenum رستہ_Name_Type, ثابت فراغ *paths, GLuint رستہ_ادھار, GLenum cover_منوال, GLenum transformType, ثابت GLfloat *transform_اقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPATHPARAMETERIVNVPROC) (GLuint رستہ, GLenum pname, GLint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPATHPARAMETERFVNVPROC) (GLuint رستہ, GLenum pname, GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPATHCOMMANDSNVPROC) (GLuint رستہ, GLubyte *commands);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPATHCOORDSNVPROC) (GLuint رستہ, GLfloat *coords);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPATHDASHARRAYNVPROC) (GLuint رستہ, GLfloat *dashArray);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPATHMETRICSNVPROC) (GLbitfield metric_Query_نقاب, GLsizei عدد_Paths, GLenum رستہ_Name_Type, ثابت فراغ *paths, GLuint رستہ_ادھار, GLsizei stride, GLfloat *metrics);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPATHMETRICRANGENVPROC) (GLbitfield metric_Query_نقاب, GLuint پہلا_رستہ_Name, GLsizei عدد_Paths, GLsizei stride, GLfloat *metrics);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPATHSPACINGNVPROC) (GLenum رستہ_List_منوال, GLsizei عدد_Paths, GLenum رستہ_Name_Type, ثابت فراغ *paths, GLuint رستہ_ادھار, GLfloat advanceScale, GLfloat kerningScale, GLenum transformType, GLfloat *returnedSpacing);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISPOINTINFILLPATHNVPROC) (GLuint رستہ, GLuint نقاب, GLfloat x, GLfloat y);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISPOINTINSTROKEPATHNVPROC) (GLuint رستہ, GLfloat x, GLfloat y);
تعريفنوع GLfloat (GL_APIENTRYP PFNGLGETPATHLENGTHNVPROC) (GLuint رستہ, GLsizei شروع_Segment, GLsizei عدد_Segments);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLPOINTALONGPATHNVPROC) (GLuint رستہ, GLsizei شروع_Segment, GLsizei عدد_Segments, GLfloat فاصلہ, GLfloat *x, GLfloat *y, GLfloat *tangentX, GLfloat *tangentY);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXLOAD3X2FNVPROC) (GLenum میٹرکس_منوال, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXLOAD3X3FNVPROC) (GLenum میٹرکس_منوال, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXLOADTRANSPOSE3X3FNVPROC) (GLenum میٹرکس_منوال, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXMULT3X2FNVPROC) (GLenum میٹرکس_منوال, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXMULT3X3FNVPROC) (GLenum میٹرکس_منوال, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXMULTTRANSPOSE3X3FNVPROC) (GLenum میٹرکس_منوال, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILTHENCOVERFILLPATHNVPROC) (GLuint رستہ, GLenum fill_منوال, GLuint نقاب, GLenum cover_منوال);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILTHENCOVERSTROKEPATHNVPROC) (GLuint رستہ, GLint reference, GLuint نقاب, GLenum cover_منوال);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILTHENCOVERFILLPATHINSTANCEDNVPROC) (GLsizei عدد_Paths, GLenum رستہ_Name_Type, ثابت فراغ *paths, GLuint رستہ_ادھار, GLenum fill_منوال, GLuint نقاب, GLenum cover_منوال, GLenum transformType, ثابت GLfloat *transform_اقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILTHENCOVERSTROKEPATHINSTANCEDNVPROC) (GLsizei عدد_Paths, GLenum رستہ_Name_Type, ثابت فراغ *paths, GLuint رستہ_ادھار, GLint reference, GLuint نقاب, GLenum cover_منوال, GLenum transformType, ثابت GLfloat *transform_اقدار);
تعريفنوع GLenum (GL_APIENTRYP PFNGLPATHGLYPHINDEXRANGENVPROC) (GLenum font_نشانہ, ثابت فراغ *fontName, GLbitfield fontStyle, GLuint رستہ_Parameter_Template, GLfloat emScale, GLuint *ادھار_And_گنتی);
تعريفنوع GLenum (GL_APIENTRYP PFNGLPATHGLYPHINDEXARRAYNVPROC) (GLuint پہلا_رستہ_Name, GLenum font_نشانہ, ثابت فراغ *fontName, GLbitfield fontStyle, GLuint پہلا_Glyph_اشاریہ, GLsizei عدد_Glyphs, GLuint رستہ_Parameter_Template, GLfloat emScale);
تعريفنوع GLenum (GL_APIENTRYP PFNGLPATHMEMORYGLYPHINDEXARRAYNVPROC) (GLuint پہلا_رستہ_Name, GLenum font_نشانہ, GLsizeiptr font_ناپ, ثابت فراغ *font_انکڑے, GLsizei face_اشاریہ, GLuint پہلا_Glyph_اشاریہ, GLsizei عدد_Glyphs, GLuint رستہ_Parameter_Template, GLfloat emScale);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMPATHFRAGMENTINPUTGENNVPROC) (GLuint پروگرام, GLint location, GLenum gen_منوال, GLint components, ثابت GLfloat *coeffs);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMRESOURCEFVNVPROC) (GLuint پروگرام, GLenum پروگرام_Interface, GLuint اشاریہ, GLsizei prop_گنتی, ثابت GLenum *props, GLsizei گنتی, GLsizei *لمائی, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXFRUSTUMEXTPROC) (GLenum منوال, GLdouble بایاں, GLdouble دایاں, GLdouble bottom, GLdouble چوٹی, GLdouble zNear, GLdouble zFar);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXLOADIDENTITYEXTPROC) (GLenum منوال);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXLOADTRANSPOSEFEXTPROC) (GLenum منوال, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXLOADTRANSPOSEDEXTPROC) (GLenum منوال, ثابت GLdouble *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXLOADFEXTPROC) (GLenum منوال, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXLOADDEXTPROC) (GLenum منوال, ثابت GLdouble *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXMULTTRANSPOSEFEXTPROC) (GLenum منوال, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXMULTTRANSPOSEDEXTPROC) (GLenum منوال, ثابت GLdouble *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXMULTFEXTPROC) (GLenum منوال, ثابت GLfloat *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXMULTDEXTPROC) (GLenum منوال, ثابت GLdouble *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXORTHOEXTPROC) (GLenum منوال, GLdouble بایاں, GLdouble دایاں, GLdouble bottom, GLdouble چوٹی, GLdouble zNear, GLdouble zFar);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXPOPEXTPROC) (GLenum منوال);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXPUSHEXTPROC) (GLenum منوال);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXROTATEFEXTPROC) (GLenum منوال, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXROTATEDEXTPROC) (GLenum منوال, GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXSCALEFEXTPROC) (GLenum منوال, GLfloat x, GLfloat y, GLfloat z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXSCALEDEXTPROC) (GLenum منوال, GLdouble x, GLdouble y, GLdouble z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXTRANSLATEFEXTPROC) (GLenum منوال, GLfloat x, GLfloat y, GLfloat z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXTRANSLATEDEXTPROC) (GLenum منوال, GLdouble x, GLdouble y, GLdouble z);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL GLuint GL_APIENTRY glGenPathsNV (GLsizei range);
GL_APICALL فراغ GL_APIENTRY glDeletePathsNV (GLuint رستہ, GLsizei range);
GL_APICALL GLboolean GL_APIENTRY gl_Is_رستہ_NV (GLuint رستہ);
GL_APICALL فراغ GL_APIENTRY gl_رستہ_Commands_NV (GLuint رستہ, GLsizei عدد_Commands, ثابت GLubyte *commands, GLsizei عدد_Coords, GLenum coordType, ثابت فراغ *coords);
GL_APICALL فراغ GL_APIENTRY gl_رستہ_Coords_NV (GLuint رستہ, GLsizei عدد_Coords, GLenum coordType, ثابت فراغ *coords);
GL_APICALL فراغ GL_APIENTRY gl_رستہ_Sub_Commands_NV (GLuint رستہ, GLsizei command_شروع, GLsizei commands_منزل_Delete, GLsizei عدد_Commands, ثابت GLubyte *commands, GLsizei عدد_Coords, GLenum coordType, ثابت فراغ *coords);
GL_APICALL فراغ GL_APIENTRY gl_رستہ_Sub_Coords_NV (GLuint رستہ, GLsizei coord_شروع, GLsizei عدد_Coords, GLenum coordType, ثابت فراغ *coords);
GL_APICALL فراغ GL_APIENTRY gl_رستہ_String_NV (GLuint رستہ, GLenum format, GLsizei لمائی, ثابت فراغ *رستہ_String);
GL_APICALL فراغ GL_APIENTRY gl_رستہ_Glyphs_NV (GLuint پہلا_رستہ_Name, GLenum font_نشانہ, ثابت فراغ *fontName, GLbitfield fontStyle, GLsizei عدد_Glyphs, GLenum type, ثابت فراغ *charcodes, GLenum handleMissingGlyphs, GLuint رستہ_Parameter_Template, GLfloat emScale);
GL_APICALL فراغ GL_APIENTRY gl_رستہ_Glyph_Range_NV (GLuint پہلا_رستہ_Name, GLenum font_نشانہ, ثابت فراغ *fontName, GLbitfield fontStyle, GLuint پہلا_Glyph, GLsizei عدد_Glyphs, GLenum handleMissingGlyphs, GLuint رستہ_Parameter_Template, GLfloat emScale);
GL_APICALL فراغ GL_APIENTRY gl_بھار_Paths_NV (GLuint نتیجہ_رستہ, GLsizei عدد_Paths, ثابت GLuint *paths, ثابت GLfloat *weights);
GL_APICALL فراغ GL_APIENTRY gl_Copy_رستہ_NV (GLuint نتیجہ_رستہ, GLuint src_رستہ);
GL_APICALL فراغ GL_APIENTRY glInterpolatePathsNV (GLuint نتیجہ_رستہ, GLuint رستہ_A, GLuint رستہ_B, GLfloat بھار);
GL_APICALL فراغ GL_APIENTRY gl_Transform_رستہ_NV (GLuint نتیجہ_رستہ, GLuint src_رستہ, GLenum transformType, ثابت GLfloat *transform_اقدار);
GL_APICALL فراغ GL_APIENTRY gl_رستہ_Parameteriv_NV (GLuint رستہ, GLenum pname, ثابت GLint *قدر);
GL_APICALL فراغ GL_APIENTRY gl_رستہ_Parameteri_NV (GLuint رستہ, GLenum pname, GLint قدر);
GL_APICALL فراغ GL_APIENTRY gl_رستہ_Parameterfv_NV (GLuint رستہ, GLenum pname, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_رستہ_Parameterf_NV (GLuint رستہ, GLenum pname, GLfloat قدر);
GL_APICALL فراغ GL_APIENTRY gl_رستہ_Dash_Array_NV (GLuint رستہ, GLsizei dash_گنتی, ثابت GLfloat *dashArray);
GL_APICALL فراغ GL_APIENTRY gl_رستہ_Stencil_Func_NV (GLenum func, GLint ref, GLuint نقاب);
GL_APICALL فراغ GL_APIENTRY gl_رستہ_Stencil_ڈونگھائی_وتھ_NV (GLfloat ضارب, GLfloat units);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_Fill_رستہ_NV (GLuint رستہ, GLenum fill_منوال, GLuint نقاب);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_Stroke_رستہ_NV (GLuint رستہ, GLint reference, GLuint نقاب);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_Fill_رستہ_Instanced_NV (GLsizei عدد_Paths, GLenum رستہ_Name_Type, ثابت فراغ *paths, GLuint رستہ_ادھار, GLenum fill_منوال, GLuint نقاب, GLenum transformType, ثابت GLfloat *transform_اقدار);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_Stroke_رستہ_Instanced_NV (GLsizei عدد_Paths, GLenum رستہ_Name_Type, ثابت فراغ *paths, GLuint رستہ_ادھار, GLint reference, GLuint نقاب, GLenum transformType, ثابت GLfloat *transform_اقدار);
GL_APICALL فراغ GL_APIENTRY gl_رستہ_Cover_ڈونگھائی_Func_NV (GLenum func);
GL_APICALL فراغ GL_APIENTRY gl_Cover_Fill_رستہ_NV (GLuint رستہ, GLenum cover_منوال);
GL_APICALL فراغ GL_APIENTRY gl_Cover_Stroke_رستہ_NV (GLuint رستہ, GLenum cover_منوال);
GL_APICALL فراغ GL_APIENTRY gl_Cover_Fill_رستہ_Instanced_NV (GLsizei عدد_Paths, GLenum رستہ_Name_Type, ثابت فراغ *paths, GLuint رستہ_ادھار, GLenum cover_منوال, GLenum transformType, ثابت GLfloat *transform_اقدار);
GL_APICALL فراغ GL_APIENTRY gl_Cover_Stroke_رستہ_Instanced_NV (GLsizei عدد_Paths, GLenum رستہ_Name_Type, ثابت فراغ *paths, GLuint رستہ_ادھار, GLenum cover_منوال, GLenum transformType, ثابت GLfloat *transform_اقدار);
GL_APICALL فراغ GL_APIENTRY gl_Get_رستہ_Parameteriv_NV (GLuint رستہ, GLenum pname, GLint *قدر);
GL_APICALL فراغ GL_APIENTRY gl_Get_رستہ_Parameterfv_NV (GLuint رستہ, GLenum pname, GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_Get_رستہ_Commands_NV (GLuint رستہ, GLubyte *commands);
GL_APICALL فراغ GL_APIENTRY gl_Get_رستہ_Coords_NV (GLuint رستہ, GLfloat *coords);
GL_APICALL فراغ GL_APIENTRY gl_Get_رستہ_Dash_Array_NV (GLuint رستہ, GLfloat *dashArray);
GL_APICALL فراغ GL_APIENTRY gl_Get_رستہ_Metrics_NV (GLbitfield metric_Query_نقاب, GLsizei عدد_Paths, GLenum رستہ_Name_Type, ثابت فراغ *paths, GLuint رستہ_ادھار, GLsizei stride, GLfloat *metrics);
GL_APICALL فراغ GL_APIENTRY gl_Get_رستہ_Metric_Range_NV (GLbitfield metric_Query_نقاب, GLuint پہلا_رستہ_Name, GLsizei عدد_Paths, GLsizei stride, GLfloat *metrics);
GL_APICALL فراغ GL_APIENTRY gl_Get_رستہ_Spacing_NV (GLenum رستہ_List_منوال, GLsizei عدد_Paths, GLenum رستہ_Name_Type, ثابت فراغ *paths, GLuint رستہ_ادھار, GLfloat advanceScale, GLfloat kerningScale, GLenum transformType, GLfloat *returnedSpacing);
GL_APICALL GLboolean GL_APIENTRY gl_Is_نقطہ_وچ_Fill_رستہ_NV (GLuint رستہ, GLuint نقاب, GLfloat x, GLfloat y);
GL_APICALL GLboolean GL_APIENTRY gl_Is_نقطہ_وچ_Stroke_رستہ_NV (GLuint رستہ, GLfloat x, GLfloat y);
GL_APICALL GLfloat GL_APIENTRY gl_Get_رستہ_لمائی_NV (GLuint رستہ, GLsizei شروع_Segment, GLsizei عدد_Segments);
GL_APICALL GLboolean GL_APIENTRY gl_نقطہ_Along_رستہ_NV (GLuint رستہ, GLsizei شروع_Segment, GLsizei عدد_Segments, GLfloat فاصلہ, GLfloat *x, GLfloat *y, GLfloat *tangentX, GLfloat *tangentY);
GL_APICALL فراغ GL_APIENTRY gl_میٹرکس_Load3x2f_NV (GLenum میٹرکس_منوال, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_میٹرکس_Load3x3f_NV (GLenum میٹرکس_منوال, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_میٹرکس_لدو_Transpose3x3f_NV (GLenum میٹرکس_منوال, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_میٹرکس_Mult3x2f_NV (GLenum میٹرکس_منوال, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_میٹرکس_Mult3x3f_NV (GLenum میٹرکس_منوال, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_میٹرکس_Mult_Transpose3x3f_NV (GLenum میٹرکس_منوال, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_Then_Cover_Fill_رستہ_NV (GLuint رستہ, GLenum fill_منوال, GLuint نقاب, GLenum cover_منوال);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_Then_Cover_Stroke_رستہ_NV (GLuint رستہ, GLint reference, GLuint نقاب, GLenum cover_منوال);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_Then_Cover_Fill_رستہ_Instanced_NV (GLsizei عدد_Paths, GLenum رستہ_Name_Type, ثابت فراغ *paths, GLuint رستہ_ادھار, GLenum fill_منوال, GLuint نقاب, GLenum cover_منوال, GLenum transformType, ثابت GLfloat *transform_اقدار);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_Then_Cover_Stroke_رستہ_Instanced_NV (GLsizei عدد_Paths, GLenum رستہ_Name_Type, ثابت فراغ *paths, GLuint رستہ_ادھار, GLint reference, GLuint نقاب, GLenum cover_منوال, GLenum transformType, ثابت GLfloat *transform_اقدار);
GL_APICALL GLenum GL_APIENTRY gl_رستہ_Glyph_اشاریہ_Range_NV (GLenum font_نشانہ, ثابت فراغ *fontName, GLbitfield fontStyle, GLuint رستہ_Parameter_Template, GLfloat emScale, GLuint *ادھار_And_گنتی);
GL_APICALL GLenum GL_APIENTRY gl_رستہ_Glyph_اشاریہ_Array_NV (GLuint پہلا_رستہ_Name, GLenum font_نشانہ, ثابت فراغ *fontName, GLbitfield fontStyle, GLuint پہلا_Glyph_اشاریہ, GLsizei عدد_Glyphs, GLuint رستہ_Parameter_Template, GLfloat emScale);
GL_APICALL GLenum GL_APIENTRY gl_رستہ_حافظہ_Glyph_اشاریہ_Array_NV (GLuint پہلا_رستہ_Name, GLenum font_نشانہ, GLsizeiptr font_ناپ, ثابت فراغ *font_انکڑے, GLsizei face_اشاریہ, GLuint پہلا_Glyph_اشاریہ, GLsizei عدد_Glyphs, GLuint رستہ_Parameter_Template, GLfloat emScale);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_رستہ_Fragment_داخلہ_Gen_NV (GLuint پروگرام, GLint location, GLenum gen_منوال, GLint components, ثابت GLfloat *coeffs);
GL_APICALL فراغ GL_APIENTRY gl_Get_پروگرام_Resourcefv_NV (GLuint پروگرام, GLenum پروگرام_Interface, GLuint اشاریہ, GLsizei prop_گنتی, ثابت GLenum *props, GLsizei گنتی, GLsizei *لمائی, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY gl_میٹرکس_Frustum_EXT (GLenum منوال, GLdouble بایاں, GLdouble دایاں, GLdouble bottom, GLdouble چوٹی, GLdouble zNear, GLdouble zFar);
GL_APICALL فراغ GL_APIENTRY gl_میٹرکس_لدو_پچھان_تت_EXT (GLenum منوال);
GL_APICALL فراغ GL_APIENTRY gl_میٹرکس_لدو_Transposef_EXT (GLenum منوال, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_میٹرکس_لدو_Transposed_EXT (GLenum منوال, ثابت GLdouble *m);
GL_APICALL فراغ GL_APIENTRY gl_میٹرکس_Loadf_EXT (GLenum منوال, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_میٹرکس_Loadd_EXT (GLenum منوال, ثابت GLdouble *m);
GL_APICALL فراغ GL_APIENTRY gl_میٹرکس_Mult_Transposef_EXT (GLenum منوال, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_میٹرکس_Mult_Transposed_EXT (GLenum منوال, ثابت GLdouble *m);
GL_APICALL فراغ GL_APIENTRY gl_میٹرکس_Multf_EXT (GLenum منوال, ثابت GLfloat *m);
GL_APICALL فراغ GL_APIENTRY gl_میٹرکس_Multd_EXT (GLenum منوال, ثابت GLdouble *m);
GL_APICALL فراغ GL_APIENTRY gl_میٹرکس_Ortho_EXT (GLenum منوال, GLdouble بایاں, GLdouble دایاں, GLdouble bottom, GLdouble چوٹی, GLdouble zNear, GLdouble zFar);
GL_APICALL فراغ GL_APIENTRY gl_میٹرکس_نکالو_EXT (GLenum منوال);
GL_APICALL فراغ GL_APIENTRY gl_میٹرکس_ڈالو_EXT (GLenum منوال);
GL_APICALL فراغ GL_APIENTRY gl_میٹرکس_Rotatef_EXT (GLenum منوال, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL فراغ GL_APIENTRY gl_میٹرکس_Rotated_EXT (GLenum منوال, GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
GL_APICALL فراغ GL_APIENTRY gl_میٹرکس_Scalef_EXT (GLenum منوال, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL فراغ GL_APIENTRY gl_میٹرکس_Scaled_EXT (GLenum منوال, GLdouble x, GLdouble y, GLdouble z);
GL_APICALL فراغ GL_APIENTRY gl_میٹرکس_Translatef_EXT (GLenum منوال, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL فراغ GL_APIENTRY gl_میٹرکس_Translated_EXT (GLenum منوال, GLdouble x, GLdouble y, GLdouble z);
#جے_انت
#جے_انت /* GL_NV_path_rendering */

#جے_بنا_تعریف GL_NV_رستہ_rendering_shared_کنارا
#تعریف_کرو GL_NV_رستہ_rendering_shared_کنارا 1
#تعریف_کرو GL_SHARED_کنارا_NV                 0xC0
#جے_انت /* GL_NV_path_rendering_shared_edge */

#جے_بنا_تعریف GL_NV_pixel_بفر_object
#تعریف_کرو GL_NV_pixel_بفر_object 1
#تعریف_کرو GL_PIXEL_PACK_بفر_NV           0x88EB
#تعریف_کرو GL_PIXEL_UNPACK_بفر_NV         0x88EC
#تعریف_کرو GL_PIXEL_PACK_بفر_BINDING_NV   0x88ED
#تعریف_کرو GL_PIXEL_UNPACK_بفر_BINDING_NV 0x88EF
#جے_انت /* GL_NV_pixel_buffer_object */

#جے_بنا_تعریف GL_NV_polygon_منوال
#تعریف_کرو GL_NV_polygon_منوال 1
#تعریف_کرو GL_POLYGON_منوال_NV                0x0B40
#تعریف_کرو GL_POLYGON_وتھ_نقطہ_NV        0x2A01
#تعریف_کرو GL_POLYGON_وتھ_سطر_NV         0x2A02
#تعریف_کرو GL_نقطہ_NV                       0x1B00
#تعریف_کرو GL_سطر_NV                        0x1B01
#تعریف_کرو GL_FILL_NV                        0x1B02
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOLYGONMODENVPROC) (GLenum face, GLenum منوال);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Polygon_منوال_NV (GLenum face, GLenum منوال);
#جے_انت
#جے_انت /* GL_NV_polygon_mode */

#جے_بنا_تعریف GL_NV_primitive_shading_شرح
#تعریف_کرو GL_NV_primitive_shading_شرح 1
#تعریف_کرو GL_SHADING_شرح_IMAGE_فی_PRIMITIVE_NV 0x95B1
#تعریف_کرو GL_SHADING_شرح_IMAGE_PALETTE_گنتی_NV 0x95B2
#جے_انت /* GL_NV_primitive_shading_rate */

#جے_بنا_تعریف GL_NV_read_بفر
#تعریف_کرو GL_NV_read_بفر 1
#تعریف_کرو GL_READ_بفر_NV                 0x0C02
تعريفنوع فراغ (GL_APIENTRYP PFNGLREADBUFFERNVPROC) (GLenum منوال);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Read_بفر_NV (GLenum منوال);
#جے_انت
#جے_انت /* GL_NV_read_buffer */

#جے_بنا_تعریف GL_NV_read_بفر_front
#تعریف_کرو GL_NV_read_بفر_front 1
#جے_انت /* GL_NV_read_buffer_front */

#جے_بنا_تعریف GL_NV_read_ڈونگھائی
#تعریف_کرو GL_NV_read_ڈونگھائی 1
#جے_انت /* GL_NV_read_depth */

#جے_بنا_تعریف GL_NV_read_ڈونگھائی_stencil
#تعریف_کرو GL_NV_read_ڈونگھائی_stencil 1
#جے_انت /* GL_NV_read_depth_stencil */

#جے_بنا_تعریف GL_NV_read_stencil
#تعریف_کرو GL_NV_read_stencil 1
#جے_انت /* GL_NV_read_stencil */

#جے_بنا_تعریف GL_NV_representative_fragment_test
#تعریف_کرو GL_NV_representative_fragment_test 1
#تعریف_کرو GL_REPRESENTATIVE_FRAGMENT_TEST_NV 0x937F
#جے_انت /* GL_NV_representative_fragment_test */

#جے_بنا_تعریف GL_NV_sRGB_formats
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
#جے_انت /* GL_NV_sRGB_formats */

#جے_بنا_تعریف GL_NV_sample_locations
#تعریف_کرو GL_NV_sample_locations 1
#تعریف_کرو GL_SAMPLE_LOCATION_SUBPIXEL_بٹ_NV 0x933D
#تعریف_کرو GL_SAMPLE_LOCATION_PIXEL_GRID_چوڑائی_NV 0x933E
#تعریف_کرو GL_SAMPLE_LOCATION_PIXEL_GRID_اچائی_NV 0x933F
#تعریف_کرو GL_PROGRAMMABLE_SAMPLE_LOCATION_جدول_ناپ_NV 0x9340
#تعریف_کرو GL_SAMPLE_LOCATION_NV             0x8E50
#تعریف_کرو GL_PROGRAMMABLE_SAMPLE_LOCATION_NV 0x9341
#تعریف_کرو GL_FRAMEBUFFER_PROGRAMMABLE_SAMPLE_LOCATIONS_NV 0x9342
#تعریف_کرو GL_FRAMEBUFFER_SAMPLE_LOCATION_PIXEL_GRID_NV 0x9343
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERSAMPLELOCATIONSFVNVPROC) (GLenum نشانہ, GLuint شروع, GLsizei گنتی, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVNVPROC) (GLuint framebuffer, GLuint شروع, GLsizei گنتی, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRESOLVEDEPTHVALUESNVPROC) (فراغ);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferSampleLocationsfvNV (GLenum نشانہ, GLuint شروع, GLsizei گنتی, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY glNamedFramebufferSampleLocationsfvNV (GLuint framebuffer, GLuint شروع, GLsizei گنتی, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY gl_Resolve_ڈونگھائی_اقدار_NV (فراغ);
#جے_انت
#جے_انت /* GL_NV_sample_locations */

#جے_بنا_تعریف GL_NV_sample_نقاب_override_coverage
#تعریف_کرو GL_NV_sample_نقاب_override_coverage 1
#جے_انت /* GL_NV_sample_mask_override_coverage */

#جے_بنا_تعریف GL_NV_scissor_exclusive
#تعریف_کرو GL_NV_scissor_exclusive 1
#تعریف_کرو GL_SCISSOR_TEST_EXCLUSIVE_NV      0x9555
#تعریف_کرو GL_SCISSOR_BOX_EXCLUSIVE_NV       0x9556
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSOREXCLUSIVENVPROC) (GLint x, GLint y, GLsizei چوڑائی, GLsizei اچائی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSOREXCLUSIVEARRAYVNVPROC) (GLuint پہلا, GLsizei گنتی, ثابت GLint *v);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glScissorExclusiveNV (GLint x, GLint y, GLsizei چوڑائی, GLsizei اچائی);
GL_APICALL فراغ GL_APIENTRY glScissorExclusiveArrayvNV (GLuint پہلا, GLsizei گنتی, ثابت GLint *v);
#جے_انت
#جے_انت /* GL_NV_scissor_exclusive */

#جے_بنا_تعریف GL_NV_shader_atomic_fp16_سمتیہ
#تعریف_کرو GL_NV_shader_atomic_fp16_سمتیہ 1
#جے_انت /* GL_NV_shader_atomic_fp16_vector */

#جے_بنا_تعریف GL_NV_shader_noperspective_interpolation
#تعریف_کرو GL_NV_shader_noperspective_interpolation 1
#جے_انت /* GL_NV_shader_noperspective_interpolation */

#جے_بنا_تعریف GL_NV_shader_subgroup_partitioned
#تعریف_کرو GL_NV_shader_subgroup_partitioned 1
#تعریف_کرو GL_SUBGROUP_FEATURE_PARTITIONED_ثنائی_ہندسہ_NV 0x00000100
#جے_انت /* GL_NV_shader_subgroup_partitioned */

#جے_بنا_تعریف GL_NV_shader_texture_footprint
#تعریف_کرو GL_NV_shader_texture_footprint 1
#جے_انت /* GL_NV_shader_texture_footprint */

#جے_بنا_تعریف GL_NV_shading_شرح_image
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
#تعریف_کرو GL_SHADING_شرح_IMAGE_TEXEL_اچائی_NV 0x955D
#تعریف_کرو GL_SHADING_شرح_IMAGE_PALETTE_ناپ_NV 0x955E
#تعریف_کرو GL_MAX_COARSE_FRAGMENT_SAMPLES_NV 0x955F
#تعریف_کرو GL_SHADING_شرح_SAMPLE_ترتیب_DEFAULT_NV 0x95AE
#تعریف_کرو GL_SHADING_شرح_SAMPLE_ترتیب_PIXEL_MAJOR_NV 0x95AF
#تعریف_کرو GL_SHADING_شرح_SAMPLE_ترتیب_SAMPLE_MAJOR_NV 0x95B0
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDSHADINGRATEIMAGENVPROC) (GLuint texture);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSHADINGRATEIMAGEPALETTENVPROC) (GLuint viewport, GLuint اندراج, GLenum *شرح);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSHADINGRATESAMPLELOCATIONIVNVPROC) (GLenum شرح, GLuint samples, GLuint اشاریہ, GLint *location);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADINGRATEIMAGEBARRIERNVPROC) (GLboolean synchronize);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADINGRATEIMAGEPALETTENVPROC) (GLuint viewport, GLuint پہلا, GLsizei گنتی, ثابت GLenum *rates);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADINGRATESAMPLEORDERNVPROC) (GLenum ترتیب);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADINGRATESAMPLEORDERCUSTOMNVPROC) (GLenum شرح, GLuint samples, ثابت GLint *locations);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Bind_Shading_شرح_Image_NV (GLuint texture);
GL_APICALL فراغ GL_APIENTRY gl_Get_Shading_شرح_Image_Palette_NV (GLuint viewport, GLuint اندراج, GLenum *شرح);
GL_APICALL فراغ GL_APIENTRY gl_Get_Shading_شرح_Sample_Locationiv_NV (GLenum شرح, GLuint samples, GLuint اشاریہ, GLint *location);
GL_APICALL فراغ GL_APIENTRY gl_Shading_شرح_Image_Barrier_NV (GLboolean synchronize);
GL_APICALL فراغ GL_APIENTRY gl_Shading_شرح_Image_Palette_NV (GLuint viewport, GLuint پہلا, GLsizei گنتی, ثابت GLenum *rates);
GL_APICALL فراغ GL_APIENTRY gl_Shading_شرح_Sample_ترتیب_NV (GLenum ترتیب);
GL_APICALL فراغ GL_APIENTRY gl_Shading_شرح_Sample_ترتیب_Custom_NV (GLenum شرح, GLuint samples, ثابت GLint *locations);
#جے_انت
#جے_انت /* GL_NV_shading_rate_image */

#جے_بنا_تعریف GL_NV_shadow_samplers_array
#تعریف_کرو GL_NV_shadow_samplers_array 1
#تعریف_کرو GL_SAMPLER_2D_ARRAY_SHADOW_NV     0x8DC4
#جے_انت /* GL_NV_shadow_samplers_array */

#جے_بنا_تعریف GL_NV_shadow_samplers_cube
#تعریف_کرو GL_NV_shadow_samplers_cube 1
#تعریف_کرو GL_SAMPLER_CUBE_SHADOW_NV         0x8DC5
#جے_انت /* GL_NV_shadow_samplers_cube */

#جے_بنا_تعریف GL_NV_stereo_view_rendering
#تعریف_کرو GL_NV_stereo_view_rendering 1
#جے_انت /* GL_NV_stereo_view_rendering */

#جے_بنا_تعریف GL_NV_texture_barrier
#تعریف_کرو GL_NV_texture_barrier 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTUREBARRIERNVPROC) (فراغ);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTextureBarrierNV (فراغ);
#جے_انت
#جے_انت /* GL_NV_texture_barrier */

#جے_بنا_تعریف GL_NV_texture_border_clamp
#تعریف_کرو GL_NV_texture_border_clamp 1
#تعریف_کرو GL_TEXTURE_BORDER_COLOR_NV        0x1004
#تعریف_کرو GL_CLAMP_منزل_BORDER_NV             0x812D
#جے_انت /* GL_NV_texture_border_clamp */

#جے_بنا_تعریف GL_NV_texture_compression_s3tc_update
#تعریف_کرو GL_NV_texture_compression_s3tc_update 1
#جے_انت /* GL_NV_texture_compression_s3tc_update */

#جے_بنا_تعریف GL_NV_texture_npot_2D_mipmap
#تعریف_کرو GL_NV_texture_npot_2D_mipmap 1
#جے_انت /* GL_NV_texture_npot_2D_mipmap */

#جے_بنا_تعریف GL_NV_timeline_semaphore
#تعریف_کرو GL_NV_timeline_semaphore 1
#تعریف_کرو GL_TIMELINE_SEMAPHORE_قدر_NV    0x9595
#تعریف_کرو GL_SEMAPHORE_TYPE_NV              0x95B3
#تعریف_کرو GL_SEMAPHORE_TYPE_ثنائی_NV       0x95B4
#تعریف_کرو GL_SEMAPHORE_TYPE_TIMELINE_NV     0x95B5
#تعریف_کرو GL_MAX_TIMELINE_SEMAPHORE_قدر_DIFFERENCE_NV 0x95B6
تعريفنوع فراغ (GL_APIENTRYP PFNGLCREATESEMAPHORESNVPROC) (GLsizei n, GLuint *semaphores);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSEMAPHOREPARAMETERIVNVPROC) (GLuint semaphore, GLenum pname, ثابت GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSEMAPHOREPARAMETERIVNVPROC) (GLuint semaphore, GLenum pname, GLint *params);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glCreateSemaphoresNV (GLsizei n, GLuint *semaphores);
GL_APICALL فراغ GL_APIENTRY glSemaphoreParameterivNV (GLuint semaphore, GLenum pname, ثابت GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetSemaphoreParameterivNV (GLuint semaphore, GLenum pname, GLint *params);
#جے_انت
#جے_انت /* GL_NV_timeline_semaphore */

#جے_بنا_تعریف GL_NV_viewport_array
#تعریف_کرو GL_NV_viewport_array 1
#تعریف_کرو GL_MAX_VIEWPORTS_NV               0x825B
#تعریف_کرو GL_VIEWPORT_SUBPIXEL_بٹ_NV      0x825C
#تعریف_کرو GL_VIEWPORT_BOUNDS_RANGE_NV       0x825D
#تعریف_کرو GL_VIEWPORT_اشاریہ_PROVOKING_راس_NV 0x825F
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTARRAYVNVPROC) (GLuint پہلا, GLsizei گنتی, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTINDEXEDFNVPROC) (GLuint اشاریہ, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTINDEXEDFVNVPROC) (GLuint اشاریہ, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSORARRAYVNVPROC) (GLuint پہلا, GLsizei گنتی, ثابت GLint *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSORINDEXEDNVPROC) (GLuint اشاریہ, GLint بایاں, GLint bottom, GLsizei چوڑائی, GLsizei اچائی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSORINDEXEDVNVPROC) (GLuint اشاریہ, ثابت GLint *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHRANGEARRAYFVNVPROC) (GLuint پہلا, GLsizei گنتی, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHRANGEINDEXEDFNVPROC) (GLuint اشاریہ, GLfloat n, GLfloat f);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFLOATI_VNVPROC) (GLenum نشانہ, GLuint اشاریہ, GLfloat *انکڑے);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENABLEINVPROC) (GLenum نشانہ, GLuint اشاریہ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISABLEINVPROC) (GLenum نشانہ, GLuint اشاریہ);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISENABLEDINVPROC) (GLenum نشانہ, GLuint اشاریہ);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glViewportArrayvNV (GLuint پہلا, GLsizei گنتی, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY glViewportIndexedfNV (GLuint اشاریہ, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
GL_APICALL فراغ GL_APIENTRY glViewportIndexedfvNV (GLuint اشاریہ, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY glScissorArrayvNV (GLuint پہلا, GLsizei گنتی, ثابت GLint *v);
GL_APICALL فراغ GL_APIENTRY gl_Scissor_اشاریہ_دار_NV (GLuint اشاریہ, GLint بایاں, GLint bottom, GLsizei چوڑائی, GLsizei اچائی);
GL_APICALL فراغ GL_APIENTRY glScissorIndexedvNV (GLuint اشاریہ, ثابت GLint *v);
GL_APICALL فراغ GL_APIENTRY gl_ڈونگھائی_Range_Arrayfv_NV (GLuint پہلا, GLsizei گنتی, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY gl_ڈونگھائی_Range_Indexedf_NV (GLuint اشاریہ, GLfloat n, GLfloat f);
GL_APICALL فراغ GL_APIENTRY glGetFloati_vNV (GLenum نشانہ, GLuint اشاریہ, GLfloat *انکڑے);
GL_APICALL فراغ GL_APIENTRY glEnableiNV (GLenum نشانہ, GLuint اشاریہ);
GL_APICALL فراغ GL_APIENTRY glDisableiNV (GLenum نشانہ, GLuint اشاریہ);
GL_APICALL GLboolean GL_APIENTRY glIsEnablediNV (GLenum نشانہ, GLuint اشاریہ);
#جے_انت
#جے_انت /* GL_NV_viewport_array */

#جے_بنا_تعریف GL_NV_viewport_array2
#تعریف_کرو GL_NV_viewport_array2 1
#جے_انت /* GL_NV_viewport_array2 */

#جے_بنا_تعریف GL_NV_viewport_swizzle
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
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTSWIZZLENVPROC) (GLuint اشاریہ, GLenum swizzlex, GLenum swizzley, GLenum swizzlez, GLenum swizzlew);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glViewportSwizzleNV (GLuint اشاریہ, GLenum swizzlex, GLenum swizzley, GLenum swizzlez, GLenum swizzlew);
#جے_انت
#جے_انت /* GL_NV_viewport_swizzle */

#جے_بنا_تعریف GL_OVR_multiview
#تعریف_کرو GL_OVR_multiview 1
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_عدد_VIEWS_OVR 0x9630
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_ادھار_VIEW_اشاریہ_OVR 0x9632
#تعریف_کرو GL_MAX_VIEWS_OVR                  0x9631
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_VIEW_TARGETS_OVR 0x9633
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREMULTIVIEWOVRPROC) (GLenum نشانہ, GLenum attachment, GLuint texture, GLint level, GLint ادھار_View_اشاریہ, GLsizei عدد_Views_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLNAMEDFRAMEBUFFERTEXTUREMULTIVIEWOVRPROC) (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint ادھار_View_اشاریہ, GLsizei عدد_Views_2);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferTextureMultiviewOVR (GLenum نشانہ, GLenum attachment, GLuint texture, GLint level, GLint ادھار_View_اشاریہ, GLsizei عدد_Views_2);
GL_APICALL فراغ GL_APIENTRY glNamedFramebufferTextureMultiviewOVR (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint ادھار_View_اشاریہ, GLsizei عدد_Views_2);
#جے_انت
#جے_انت /* GL_OVR_multiview */

#جے_بنا_تعریف GL_OVR_multiview2
#تعریف_کرو GL_OVR_multiview2 1
#جے_انت /* GL_OVR_multiview2 */

#جے_بنا_تعریف GL_OVR_multiview_multisampled_render_منزل_texture
#تعریف_کرو GL_OVR_multiview_multisampled_render_منزل_texture 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREMULTISAMPLEMULTIVIEWOVRPROC) (GLenum نشانہ, GLenum attachment, GLuint texture, GLint level, GLsizei samples, GLint ادھار_View_اشاریہ, GLsizei عدد_Views_2);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferTextureMultisampleMultiviewOVR (GLenum نشانہ, GLenum attachment, GLuint texture, GLint level, GLsizei samples, GLint ادھار_View_اشاریہ, GLsizei عدد_Views_2);
#جے_انت
#جے_انت /* GL_OVR_multiview_multisampled_render_to_texture */

#جے_بنا_تعریف GL_QCOM_YUV_texture_gather
#تعریف_کرو GL_QCOM_YUV_texture_gather 1
#جے_انت /* GL_QCOM_YUV_texture_gather */

#جے_بنا_تعریف GL_QCOM_alpha_test
#تعریف_کرو GL_QCOM_alpha_test 1
#تعریف_کرو GL_ALPHA_TEST_QCOM                0x0BC0
#تعریف_کرو GL_ALPHA_TEST_FUNC_QCOM           0x0BC1
#تعریف_کرو GL_ALPHA_TEST_REF_QCOM            0x0BC2
تعريفنوع فراغ (GL_APIENTRYP PFNGLALPHAFUNCQCOMPROC) (GLenum func, GLclampf ref);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glAlphaFuncQCOM (GLenum func, GLclampf ref);
#جے_انت
#جے_انت /* GL_QCOM_alpha_test */

#جے_بنا_تعریف GL_QCOM_binning_control
#تعریف_کرو GL_QCOM_binning_control 1
#تعریف_کرو GL_BINNING_CONTROL_HINT_QCOM      0x8FB0
#تعریف_کرو GL_CPU_OPTIMIZED_QCOM             0x8FB1
#تعریف_کرو GL_GPU_OPTIMIZED_QCOM             0x8FB2
#تعریف_کرو GL_RENDER_سدھا_منزل_FRAMEBUFFER_QCOM 0x8FB3
#جے_انت /* GL_QCOM_binning_control */

#جے_بنا_تعریف GL_QCOM_driver_control
#تعریف_کرو GL_QCOM_driver_control 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETDRIVERCONTROLSQCOMPROC) (GLint *عدد, GLsizei ناپ, GLuint *driverControls);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETDRIVERCONTROLSTRINGQCOMPROC) (GLuint driverControl, GLsizei buf_ناپ, GLsizei *لمائی, GLchar *driverControlString);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glGetDriverControlsQCOM (GLint *عدد, GLsizei ناپ, GLuint *driverControls);
GL_APICALL فراغ GL_APIENTRY glGetDriverControlStringQCOM (GLuint driverControl, GLsizei buf_ناپ, GLsizei *لمائی, GLchar *driverControlString);
GL_APICALL فراغ GL_APIENTRY glEnableDriverControlQCOM (GLuint driverControl);
GL_APICALL فراغ GL_APIENTRY glDisableDriverControlQCOM (GLuint driverControl);
#جے_انت
#جے_انت /* GL_QCOM_driver_control */

#جے_بنا_تعریف GL_QCOM_extended_get
#تعریف_کرو GL_QCOM_extended_get 1
#تعریف_کرو GL_TEXTURE_چوڑائی_QCOM             0x8BD2
#تعریف_کرو GL_TEXTURE_اچائی_QCOM            0x8BD3
#تعریف_کرو GL_TEXTURE_ڈونگھائی_QCOM             0x8BD4
#تعریف_کرو GL_TEXTURE_اندرونی_FORMAT_QCOM   0x8BD5
#تعریف_کرو GL_TEXTURE_FORMAT_QCOM            0x8BD6
#تعریف_کرو GL_TEXTURE_TYPE_QCOM              0x8BD7
#تعریف_کرو GL_TEXTURE_IMAGE_VALID_QCOM       0x8BD8
#تعریف_کرو GL_TEXTURE_عدد_پدھراں_QCOM        0x8BD9
#تعریف_کرو GL_TEXTURE_نشانہ_QCOM            0x8BDA
#تعریف_کرو GL_TEXTURE_OBJECT_VALID_QCOM      0x8BDB
#تعریف_کرو GL_STATE_RESTORE                  0x8BDC
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETTEXTURESQCOMPROC) (GLuint *textures, GLint maxTextures, GLint *عدد_Textures);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETBUFFERSQCOMPROC) (GLuint *buffers, GLint maxBuffers, GLint *عدد_Buffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETRENDERBUFFERSQCOMPROC) (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *عدد_Renderbuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETFRAMEBUFFERSQCOMPROC) (GLuint *framebuffers, GLint maxFramebuffers, GLint *عدد_Framebuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETTEXLEVELPARAMETERIVQCOMPROC) (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTTEXOBJECTSTATEOVERRIDEIQCOMPROC) (GLenum نشانہ, GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETTEXSUBIMAGEQCOMPROC) (GLenum نشانہ, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2, GLenum format, GLenum type, فراغ *texels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETBUFFERPOINTERVQCOMPROC) (GLenum نشانہ, فراغ **params);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glExtGetTexturesQCOM (GLuint *textures, GLint maxTextures, GLint *عدد_Textures);
GL_APICALL فراغ GL_APIENTRY glExtGetBuffersQCOM (GLuint *buffers, GLint maxBuffers, GLint *عدد_Buffers);
GL_APICALL فراغ GL_APIENTRY glExtGetRenderbuffersQCOM (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *عدد_Renderbuffers);
GL_APICALL فراغ GL_APIENTRY glExtGetFramebuffersQCOM (GLuint *framebuffers, GLint maxFramebuffers, GLint *عدد_Framebuffers);
GL_APICALL فراغ GL_APIENTRY glExtGetTexLevelParameterivQCOM (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glExtTexObjectStateOverrideiQCOM (GLenum نشانہ, GLenum pname, GLint param);
GL_APICALL فراغ GL_APIENTRY glExtGetTexSubImageQCOM (GLenum نشانہ, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2, GLenum format, GLenum type, فراغ *texels);
GL_APICALL فراغ GL_APIENTRY gl_Ext_Get_بفر_Pointerv_QCOM (GLenum نشانہ, فراغ **params);
#جے_انت
#جے_انت /* GL_QCOM_extended_get */

#جے_بنا_تعریف GL_QCOM_extended_get2
#تعریف_کرو GL_QCOM_extended_get2 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETSHADERSQCOMPROC) (GLuint *shaders, GLint maxShaders, GLint *عدد_Shaders);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETPROGRAMSQCOMPROC) (GLuint *programs, GLint maxPrograms, GLint *عدد_Programs);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLEXTISPROGRAMBINARYQCOMPROC) (GLuint پروگرام);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETPROGRAMBINARYSOURCEQCOMPROC) (GLuint پروگرام, GLenum shadertype, GLchar *سروت, GLint *لمائی);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glExtGetShadersQCOM (GLuint *shaders, GLint maxShaders, GLint *عدد_Shaders);
GL_APICALL فراغ GL_APIENTRY glExtGetProgramsQCOM (GLuint *programs, GLint maxPrograms, GLint *عدد_Programs);
GL_APICALL GLboolean GL_APIENTRY gl_Ext_Is_پروگرام_ثنائی_QCOM (GLuint پروگرام);
GL_APICALL فراغ GL_APIENTRY gl_Ext_Get_پروگرام_ثنائی_سروت_QCOM (GLuint پروگرام, GLenum shadertype, GLchar *سروت, GLint *لمائی);
#جے_انت
#جے_انت /* GL_QCOM_extended_get2 */

#جے_بنا_تعریف GL_QCOM_چوکھٹا_extrapolation
#تعریف_کرو GL_QCOM_چوکھٹا_extrapolation 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTRAPOLATETEX2DQCOMPROC) (GLuint src1, GLuint src2, GLuint output, GLfloat scale_ضارب);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glExtrapolateTex2DQCOM (GLuint src1, GLuint src2, GLuint output, GLfloat scale_ضارب);
#جے_انت
#جے_انت /* GL_QCOM_frame_extrapolation */

#جے_بنا_تعریف GL_QCOM_framebuffer_foveated
#تعریف_کرو GL_QCOM_framebuffer_foveated 1
#تعریف_کرو GL_FOVEATION_ENABLE_ثنائی_ہندسہ_QCOM      0x00000001
#تعریف_کرو GL_FOVEATION_SCALED_BIN_طریقہ_ثنائی_ہندسہ_QCOM 0x00000002
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERFOVEATIONCONFIGQCOMPROC) (GLuint framebuffer, GLuint عدد_Layers, GLuint focal_Points_فی_Layer, GLuint requestedFeatures, GLuint *providedFeatures);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERFOVEATIONPARAMETERSQCOMPROC) (GLuint framebuffer, GLuint layer, GLuint focal_نقطہ, GLfloat focalX, GLfloat focalY, GLfloat gainX, GLfloat gainY, GLfloat foveaArea);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferFoveationConfigQCOM (GLuint framebuffer, GLuint عدد_Layers, GLuint focal_Points_فی_Layer, GLuint requestedFeatures, GLuint *providedFeatures);
GL_APICALL فراغ GL_APIENTRY glFramebufferFoveationParametersQCOM (GLuint framebuffer, GLuint layer, GLuint focal_نقطہ, GLfloat focalX, GLfloat focalY, GLfloat gainX, GLfloat gainY, GLfloat foveaArea);
#جے_انت
#جے_انت /* GL_QCOM_framebuffer_foveated */

#جے_بنا_تعریف GL_QCOM_motion_estimation
#تعریف_کرو GL_QCOM_motion_estimation 1
#تعریف_کرو GL_MOTION_ESTIMATION_تلاش_بلاک_X_QCOM 0x8C90
#تعریف_کرو GL_MOTION_ESTIMATION_تلاش_بلاک_Y_QCOM 0x8C91
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXESTIMATEMOTIONQCOMPROC) (GLuint ref, GLuint نشانہ, GLuint output);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXESTIMATEMOTIONREGIONSQCOMPROC) (GLuint ref, GLuint نشانہ, GLuint output, GLuint نقاب);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTexEstimateMotionQCOM (GLuint ref, GLuint نشانہ, GLuint output);
GL_APICALL فراغ GL_APIENTRY glTexEstimateMotionRegionsQCOM (GLuint ref, GLuint نشانہ, GLuint output, GLuint نقاب);
#جے_انت
#جے_انت /* GL_QCOM_motion_estimation */

#جے_بنا_تعریف GL_QCOM_perfmon_global_منوال
#تعریف_کرو GL_QCOM_perfmon_global_منوال 1
#تعریف_کرو GL_PERFMON_GLOBAL_منوال_QCOM       0x8FA0
#جے_انت /* GL_QCOM_perfmon_global_mode */

#جے_بنا_تعریف GL_QCOM_render_sRGB_R8_RG8
#تعریف_کرو GL_QCOM_render_sRGB_R8_RG8 1
#جے_انت /* GL_QCOM_render_sRGB_R8_RG8 */

#جے_بنا_تعریف GL_QCOM_render_shared_exponent
#تعریف_کرو GL_QCOM_render_shared_exponent 1
#جے_انت /* GL_QCOM_render_shared_exponent */

#جے_بنا_تعریف GL_QCOM_shader_framebuffer_fetch_noncoherent
#تعریف_کرو GL_QCOM_shader_framebuffer_fetch_noncoherent 1
#تعریف_کرو GL_FRAMEBUFFER_FETCH_NONCOHERENT_QCOM 0x96A2
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERFETCHBARRIERQCOMPROC) (فراغ);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glFramebufferFetchBarrierQCOM (فراغ);
#جے_انت
#جے_انت /* GL_QCOM_shader_framebuffer_fetch_noncoherent */

#جے_بنا_تعریف GL_QCOM_shader_framebuffer_fetch_شرح
#تعریف_کرو GL_QCOM_shader_framebuffer_fetch_شرح 1
#جے_انت /* GL_QCOM_shader_framebuffer_fetch_rate */

#جے_بنا_تعریف GL_QCOM_shading_شرح
#تعریف_کرو GL_QCOM_shading_شرح 1
#تعریف_کرو GL_SHADING_شرح_QCOM              0x96A4
#تعریف_کرو GL_SHADING_شرح_PRESERVE_ASPECT_تناسب_QCOM 0x96A5
#تعریف_کرو GL_SHADING_شرح_1_X1_PIXELS_QCOM   0x96A6
#تعریف_کرو GL_SHADING_شرح_1_X2_PIXELS_QCOM   0x96A7
#تعریف_کرو GL_SHADING_شرح_2_X1_PIXELS_QCOM   0x96A8
#تعریف_کرو GL_SHADING_شرح_2_X2_PIXELS_QCOM   0x96A9
#تعریف_کرو GL_SHADING_شرح_4_X2_PIXELS_QCOM   0x96AC
#تعریف_کرو GL_SHADING_شرح_4_X4_PIXELS_QCOM   0x96AE
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADINGRATEQCOMPROC) (GLenum شرح);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Shading_شرح_QCOM (GLenum شرح);
#جے_انت
#جے_انت /* GL_QCOM_shading_rate */

#جے_بنا_تعریف GL_QCOM_texture_foveated
#تعریف_کرو GL_QCOM_texture_foveated 1
#تعریف_کرو GL_TEXTURE_FOVEATED_FEATURE_بٹ_QCOM 0x8BFB
#تعریف_کرو GL_TEXTURE_FOVEATED_MIN_PIXEL_DENSITY_QCOM 0x8BFC
#تعریف_کرو GL_TEXTURE_FOVEATED_FEATURE_QUERY_QCOM 0x8BFD
#تعریف_کرو GL_TEXTURE_FOVEATED_عدد_FOCAL_POINTS_QUERY_QCOM 0x8BFE
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_FOVEATION_QCOM 0x8BFF
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTUREFOVEATIONPARAMETERSQCOMPROC) (GLuint texture, GLuint layer, GLuint focal_نقطہ, GLfloat focalX, GLfloat focalY, GLfloat gainX, GLfloat gainY, GLfloat foveaArea);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glTextureFoveationParametersQCOM (GLuint texture, GLuint layer, GLuint focal_نقطہ, GLfloat focalX, GLfloat focalY, GLfloat gainX, GLfloat gainY, GLfloat foveaArea);
#جے_انت
#جے_انت /* GL_QCOM_texture_foveated */

#جے_بنا_تعریف GL_QCOM_texture_foveated2
#تعریف_کرو GL_QCOM_texture_foveated2 1
#تعریف_کرو GL_TEXTURE_FOVEATED_CUTOFF_DENSITY_QCOM 0x96A0
#جے_انت /* GL_QCOM_texture_foveated2 */

#جے_بنا_تعریف GL_QCOM_texture_foveated_subsampled_layout
#تعریف_کرو GL_QCOM_texture_foveated_subsampled_layout 1
#تعریف_کرو GL_FOVEATION_SUBSAMPLED_LAYOUT_طریقہ_ثنائی_ہندسہ_QCOM 0x00000004
#تعریف_کرو GL_MAX_SHADER_SUBSAMPLED_IMAGE_UNITS_QCOM 0x8FA1
#جے_انت /* GL_QCOM_texture_foveated_subsampled_layout */

#جے_بنا_تعریف GL_QCOM_texture_lod_bias
#تعریف_کرو GL_QCOM_texture_lod_bias 1
#تعریف_کرو GL_TEXTURE_LOD_BIAS_QCOM          0x8C96
#جے_انت /* GL_QCOM_texture_lod_bias */

#جے_بنا_تعریف GL_QCOM_tiled_rendering
#تعریف_کرو GL_QCOM_tiled_rendering 1
#تعریف_کرو GL_COLOR_بفر_BIT0_QCOM         0x00000001
#تعریف_کرو GL_COLOR_بفر_BIT1_QCOM         0x00000002
#تعریف_کرو GL_COLOR_بفر_BIT2_QCOM         0x00000004
#تعریف_کرو GL_COLOR_بفر_BIT3_QCOM         0x00000008
#تعریف_کرو GL_COLOR_بفر_BIT4_QCOM         0x00000010
#تعریف_کرو GL_COLOR_بفر_BIT5_QCOM         0x00000020
#تعریف_کرو GL_COLOR_بفر_BIT6_QCOM         0x00000040
#تعریف_کرو GL_COLOR_بفر_BIT7_QCOM         0x00000080
#تعریف_کرو GL_ڈونگھائی_بفر_BIT0_QCOM         0x00000100
#تعریف_کرو GL_ڈونگھائی_بفر_BIT1_QCOM         0x00000200
#تعریف_کرو GL_ڈونگھائی_بفر_BIT2_QCOM         0x00000400
#تعریف_کرو GL_ڈونگھائی_بفر_BIT3_QCOM         0x00000800
#تعریف_کرو GL_ڈونگھائی_بفر_BIT4_QCOM         0x00001000
#تعریف_کرو GL_ڈونگھائی_بفر_BIT5_QCOM         0x00002000
#تعریف_کرو GL_ڈونگھائی_بفر_BIT6_QCOM         0x00004000
#تعریف_کرو GL_ڈونگھائی_بفر_BIT7_QCOM         0x00008000
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
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTARTTILINGQCOMPROC) (GLuint x, GLuint y, GLuint چوڑائی, GLuint اچائی, GLbitfield preserve_نقاب);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENDTILINGQCOMPROC) (GLbitfield preserve_نقاب);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_شروع_Tiling_QCOM (GLuint x, GLuint y, GLuint چوڑائی, GLuint اچائی, GLbitfield preserve_نقاب);
GL_APICALL فراغ GL_APIENTRY gl_سرا_Tiling_QCOM (GLbitfield preserve_نقاب);
#جے_انت
#جے_انت /* GL_QCOM_tiled_rendering */

#جے_بنا_تعریف GL_QCOM_writeonly_rendering
#تعریف_کرو GL_QCOM_writeonly_rendering 1
#تعریف_کرو GL_WRITEONLY_RENDERING_QCOM       0x8823
#جے_انت /* GL_QCOM_writeonly_rendering */

#جے_بنا_تعریف GL_QCOM_ycbcr_degamma
#تعریف_کرو GL_QCOM_ycbcr_degamma 1
#تعریف_کرو GL_TEXTURE_Y_DEGAMMA_QCOM         0x9710
#تعریف_کرو GL_TEXTURE_CBCR_DEGAMMA_QCOM      0x9711
#جے_انت /* GL_QCOM_ycbcr_degamma */

#جے_بنا_تعریف GL_VIV_shader_ثنائی
#تعریف_کرو GL_VIV_shader_ثنائی 1
#تعریف_کرو GL_SHADER_ثنائی_VIV              0x8FC4
#جے_انت /* GL_VIV_shader_binary */

#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت
