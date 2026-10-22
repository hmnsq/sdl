#यदि_अपरिभाषितम् __gles2_gl2ext_h_
#परिभाषय __gles2_gl2ext_h_ 1

#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः

/*
** Copyright 2013-2026 The Khronos Group Inc.
** SPDX-License-Identifier: MIT
**
** This header is generated from the Khronos OpenGL / OpenGL ES XML
** API Registry. The current version of the Registry, generator scripts
** used to make the header, and the header can be found at
**   https://github.com/KhronosGroup/OpenGL-Registry
*/

#यदि_अपरिभाषितम् GL_APIENTRYP
#परिभाषय GL_APIENTRYP GL_APIENTRY*
#यदि_अन्तः

#परिभाषय GL_GLEXT_संस्करणम् 20260803

/* Generated C header for:
 * API: gles2
 * Profile: common
 * Versions considered: 2\.[0-9]
 * Versions emitted: _nomatch_^
 * Default extensions included: gles2
 * Additional extensions included: _nomatch_^
 * Extensions removed: _nomatch_^
 */

#यदि_अपरिभाषितम् GL_KHR_blend_equation_advanced
#परिभाषय GL_KHR_blend_equation_advanced 1
#परिभाषय GL_MULTIPLY_KHR                   0x9294
#परिभाषय GL_SCREEN_KHR                     0x9295
#परिभाषय GL_OVERLAY_KHR                    0x9296
#परिभाषय GL_DARKEN_KHR                     0x9297
#परिभाषय GL_LIGHTEN_KHR                    0x9298
#परिभाषय GL_COLORDODGE_KHR                 0x9299
#परिभाषय GL_COLORBURN_KHR                  0x929A
#परिभाषय GL_HARDLIGHT_KHR                  0x929B
#परिभाषय GL_SOFTLIGHT_KHR                  0x929C
#परिभाषय GL_DIFFERENCE_KHR                 0x929E
#परिभाषय GL_EXCLUSION_KHR                  0x92A0
#परिभाषय GL_HSL_HUE_KHR                    0x92AD
#परिभाषय GL_HSL_SATURATION_KHR             0x92AE
#परिभाषय GL_HSL_COLOR_KHR                  0x92AF
#परिभाषय GL_HSL_LUMINOSITY_KHR             0x92B0
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBLENDBARRIERKHRPROC) (शून्य);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glBlendBarrierKHR (शून्य);
#यदि_अन्तः
#यदि_अन्तः /* GL_KHR_blend_equation_advanced */

#यदि_अपरिभाषितम् GL_KHR_blend_equation_advanced_coherent
#परिभाषय GL_KHR_blend_equation_advanced_coherent 1
#परिभाषय GL_BLEND_ADVANCED_COHERENT_KHR    0x9285
#यदि_अन्तः /* GL_KHR_blend_equation_advanced_coherent */

#यदि_अपरिभाषितम् GL_KHR_context_flush_control
#परिभाषय GL_KHR_context_flush_control 1
#परिभाषय GL_CONTEXT_RELEASE_BEHAVIOR_KHR   0x82FB
#परिभाषय GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_KHR 0x82FC
#यदि_अन्तः /* GL_KHR_context_flush_control */

#यदि_अपरिभाषितम् GL_KHR_debug
#परिभाषय GL_KHR_debug 1
प्रकारनिर्देश शून्य (GL_APIENTRY  *GLDEBUGPROCKHR)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei दीर्घता,ध्रुव GLchar *सन्देशः,ध्रुव शून्य *userParam);
#परिभाषय GL_SAMPLER                        0x82E6
#परिभाषय GL_DEBUG_OUTPUT_SYNCHRONOUS_KHR   0x8242
#परिभाषय GL_DEBUG_अग्र_LOGGED_सन्देशः_दीर्घता_KHR 0x8243
#परिभाषय GL_DEBUG_CALLBACK_FUNCTION_KHR    0x8244
#परिभाषय GL_DEBUG_CALLBACK_USER_PARAM_KHR  0x8245
#परिभाषय GL_DEBUG_SOURCE_API_KHR           0x8246
#परिभाषय GL_DEBUG_SOURCE_गवाक्षः_SYSTEM_KHR 0x8247
#परिभाषय GL_DEBUG_SOURCE_SHADER_COMPILER_KHR 0x8248
#परिभाषय GL_DEBUG_SOURCE_THIRD_PARTY_KHR   0x8249
#परिभाषय GL_DEBUG_SOURCE_APPLICATION_KHR   0x824A
#परिभाषय GL_DEBUG_SOURCE_OTHER_KHR         0x824B
#परिभाषय GL_DEBUG_TYPE_ERROR_KHR           0x824C
#परिभाषय GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_KHR 0x824D
#परिभाषय GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_KHR 0x824E
#परिभाषय GL_DEBUG_TYPE_PORTABILITY_KHR     0x824F
#परिभाषय GL_DEBUG_TYPE_PERFORMANCE_KHR     0x8250
#परिभाषय GL_DEBUG_TYPE_OTHER_KHR           0x8251
#परिभाषय GL_DEBUG_TYPE_MARKER_KHR          0x8268
#परिभाषय GL_DEBUG_TYPE_प्रक्षिप_गणः_KHR      0x8269
#परिभाषय GL_DEBUG_TYPE_निष्कासय_गणः_KHR       0x826A
#परिभाषय GL_DEBUG_SEVERITY_NOTIFICATION_KHR 0x826B
#परिभाषय GL_MAX_DEBUG_गणः_राशिः_गभीरता_KHR 0x826C
#परिभाषय GL_DEBUG_गणः_राशिः_गभीरता_KHR    0x826D
#परिभाषय GL_बफर_KHR                     0x82E0
#परिभाषय GL_SHADER_KHR                     0x82E1
#परिभाषय GL_क्रमादेशः_KHR                    0x82E2
#परिभाषय GL_VERTEX_ARRAY_KHR               0x8074
#परिभाषय GL_QUERY_KHR                      0x82E3
#परिभाषय GL_क्रमादेशः_PIPELINE_KHR           0x82E4
#परिभाषय GL_SAMPLER_KHR                    0x82E6
#परिभाषय GL_MAX_LABEL_दीर्घता_KHR           0x82E8
#परिभाषय GL_MAX_DEBUG_सन्देशः_दीर्घता_KHR   0x9143
#परिभाषय GL_MAX_DEBUG_LOGGED_MESSAGES_KHR  0x9144
#परिभाषय GL_DEBUG_LOGGED_MESSAGES_KHR      0x9145
#परिभाषय GL_DEBUG_SEVERITY_उच्चः_KHR        0x9146
#परिभाषय GL_DEBUG_SEVERITY_MEDIUM_KHR      0x9147
#परिभाषय GL_DEBUG_SEVERITY_नीचः_KHR         0x9148
#परिभाषय GL_DEBUG_OUTPUT_KHR               0x92E0
#परिभाषय GL_CONTEXT_FLAG_DEBUG_BIT_KHR     0x00000002
#परिभाषय GL_राशिः_अतिप्रवाहः_KHR             0x0503
#परिभाषय GL_राशिः_UNDERFLOW_KHR            0x0504
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDEBUGMESSAGECONTROLKHRPROC) (GLenum source, GLenum type, GLenum severity, GLsizei गणनम्, ध्रुव GLuint *ids, GLboolean enabled);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDEBUGMESSAGEINSERTKHRPROC) (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei दीर्घता, ध्रुव GLchar *buf);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDEBUGMESSAGECALLBACKKHRPROC) (GLDEBUGPROCKHR callback, ध्रुव शून्य *userParam);
प्रकारनिर्देश GLuint (GL_APIENTRYP PFNGLGETDEBUGMESSAGELOGKHRPROC) (GLuint गणनम्, GLsizei buf_आकार, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *सन्देशः_Log);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPUSHDEBUGGROUPKHRPROC) (GLenum source, GLuint id, GLsizei दीर्घता, ध्रुव GLchar *सन्देशः);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPOPDEBUGGROUPKHRPROC) (शून्य);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLOBJECTLABELKHRPROC) (GLenum identifier, GLuint name, GLsizei दीर्घता, ध्रुव GLchar *label);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETOBJECTLABELKHRPROC) (GLenum identifier, GLuint name, GLsizei buf_आकार, GLsizei *दीर्घता, GLchar *label);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLOBJECTPTRLABELKHRPROC) (ध्रुव शून्य *ptr, GLsizei दीर्घता, ध्रुव GLchar *label);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETOBJECTPTRLABELKHRPROC) (ध्रुव शून्य *ptr, GLsizei buf_आकार, GLsizei *दीर्घता, GLchar *label);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETPOINTERVKHRPROC) (GLenum pname, शून्य **params);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_Debug_सन्देशः_Control_KHR (GLenum source, GLenum type, GLenum severity, GLsizei गणनम्, ध्रुव GLuint *ids, GLboolean enabled);
GL_APICALL शून्य GL_APIENTRY gl_Debug_सन्देशः_निवेशय_KHR (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei दीर्घता, ध्रुव GLchar *buf);
GL_APICALL शून्य GL_APIENTRY gl_Debug_सन्देशः_Callback_KHR (GLDEBUGPROCKHR callback, ध्रुव शून्य *userParam);
GL_APICALL GLuint GL_APIENTRY gl_Get_Debug_सन्देशः_Log_KHR (GLuint गणनम्, GLsizei buf_आकार, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *सन्देशः_Log);
GL_APICALL शून्य GL_APIENTRY gl_प्रक्षिप_Debug_गणः_KHR (GLenum source, GLuint id, GLsizei दीर्घता, ध्रुव GLchar *सन्देशः);
GL_APICALL शून्य GL_APIENTRY gl_निष्कासय_Debug_गणः_KHR (शून्य);
GL_APICALL शून्य GL_APIENTRY glObjectLabelKHR (GLenum identifier, GLuint name, GLsizei दीर्घता, ध्रुव GLchar *label);
GL_APICALL शून्य GL_APIENTRY glGetObjectLabelKHR (GLenum identifier, GLuint name, GLsizei buf_आकार, GLsizei *दीर्घता, GLchar *label);
GL_APICALL शून्य GL_APIENTRY glObjectPtrLabelKHR (ध्रुव शून्य *ptr, GLsizei दीर्घता, ध्रुव GLchar *label);
GL_APICALL शून्य GL_APIENTRY glGetObjectPtrLabelKHR (ध्रुव शून्य *ptr, GLsizei buf_आकार, GLsizei *दीर्घता, GLchar *label);
GL_APICALL शून्य GL_APIENTRY glGetPointervKHR (GLenum pname, शून्य **params);
#यदि_अन्तः
#यदि_अन्तः /* GL_KHR_debug */

#यदि_अपरिभाषितम् GL_KHR_no_error
#परिभाषय GL_KHR_no_error 1
#परिभाषय GL_CONTEXT_FLAG_NO_ERROR_BIT_KHR  0x00000008
#यदि_अन्तः /* GL_KHR_no_error */

#यदि_अपरिभाषितम् GL_KHR_parallel_shader_compile
#परिभाषय GL_KHR_parallel_shader_compile 1
#परिभाषय GL_MAX_SHADER_COMPILER_तन्तवः_KHR 0x91B0
#परिभाषय GL_COMPLETION_स्थितिः_KHR          0x91B1
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMAXSHADERCOMPILERTHREADSKHRPROC) (GLuint गणनम्);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_Max_Shader_Compiler_तन्तवः_KHR (GLuint गणनम्);
#यदि_अन्तः
#यदि_अन्तः /* GL_KHR_parallel_shader_compile */

#यदि_अपरिभाषितम् GL_KHR_robust_बफर_access_behavior
#परिभाषय GL_KHR_robust_बफर_access_behavior 1
#यदि_अन्तः /* GL_KHR_robust_buffer_access_behavior */

#यदि_अपरिभाषितम् GL_KHR_robustness
#परिभाषय GL_KHR_robustness 1
#परिभाषय GL_CONTEXT_ROBUST_ACCESS_KHR      0x90F3
#परिभाषय GL_LOSE_CONTEXT_ON_RESET_KHR      0x8252
#परिभाषय GL_GUILTY_CONTEXT_RESET_KHR       0x8253
#परिभाषय GL_INNOCENT_CONTEXT_RESET_KHR     0x8254
#परिभाषय GL_UNKNOWN_CONTEXT_RESET_KHR      0x8255
#परिभाषय GL_RESET_NOTIFICATION_STRATEGY_KHR 0x8256
#परिभाषय GL_NO_RESET_NOTIFICATION_KHR      0x8261
#परिभाषय GL_CONTEXT_नष्टम्_KHR               0x0507
प्रकारनिर्देश GLenum (GL_APIENTRYP PFNGLGETGRAPHICSRESETSTATUSKHRPROC) (शून्य);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLREADNPIXELSKHRPROC) (GLint x, GLint y, GLsizei विस्तारः, GLsizei height, GLenum format, GLenum type, GLsizei buf_आकार, शून्य *दत्त);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETNUNIFORMFVKHRPROC) (GLuint क्रमादेशः, GLint location, GLsizei buf_आकार, GLfloat *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETNUNIFORMIVKHRPROC) (GLuint क्रमादेशः, GLint location, GLsizei buf_आकार, GLint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETNUNIFORMUIVKHRPROC) (GLuint क्रमादेशः, GLint location, GLsizei buf_आकार, GLuint *params);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL GLenum GL_APIENTRY gl_Get_Graphics_Reset_स्थितिः_KHR (शून्य);
GL_APICALL शून्य GL_APIENTRY glReadnPixelsKHR (GLint x, GLint y, GLsizei विस्तारः, GLsizei height, GLenum format, GLenum type, GLsizei buf_आकार, शून्य *दत्त);
GL_APICALL शून्य GL_APIENTRY glGetnUniformfvKHR (GLuint क्रमादेशः, GLint location, GLsizei buf_आकार, GLfloat *params);
GL_APICALL शून्य GL_APIENTRY glGetnUniformivKHR (GLuint क्रमादेशः, GLint location, GLsizei buf_आकार, GLint *params);
GL_APICALL शून्य GL_APIENTRY glGetnUniformuivKHR (GLuint क्रमादेशः, GLint location, GLsizei buf_आकार, GLuint *params);
#यदि_अन्तः
#यदि_अन्तः /* GL_KHR_robustness */

#यदि_अपरिभाषितम् GL_KHR_shader_subgroup
#परिभाषय GL_KHR_shader_subgroup 1
#परिभाषय GL_SUBGROUP_आकार_KHR              0x9532
#परिभाषय GL_SUBGROUP_SUPPORTED_STAGES_KHR  0x9533
#परिभाषय GL_SUBGROUP_SUPPORTED_FEATURES_KHR 0x9534
#परिभाषय GL_SUBGROUP_QUAD_ALL_STAGES_KHR   0x9535
#परिभाषय GL_SUBGROUP_FEATURE_BASIC_BIT_KHR 0x00000001
#परिभाषय GL_SUBGROUP_FEATURE_VOTE_BIT_KHR  0x00000002
#परिभाषय GL_SUBGROUP_FEATURE_ARITHMETIC_BIT_KHR 0x00000004
#परिभाषय GL_SUBGROUP_FEATURE_BALLOT_BIT_KHR 0x00000008
#परिभाषय GL_SUBGROUP_FEATURE_SHUFFLE_BIT_KHR 0x00000010
#परिभाषय GL_SUBGROUP_FEATURE_SHUFFLE_RELATIVE_BIT_KHR 0x00000020
#परिभाषय GL_SUBGROUP_FEATURE_CLUSTERED_BIT_KHR 0x00000040
#परिभाषय GL_SUBGROUP_FEATURE_QUAD_BIT_KHR  0x00000080
#यदि_अन्तः /* GL_KHR_shader_subgroup */

#यदि_अपरिभाषितम् GL_KHR_texture_compression_astc_hdr
#परिभाषय GL_KHR_texture_compression_astc_hdr 1
#परिभाषय GL_COMPRESSED_RGBA_ASTC_4x4_KHR   0x93B0
#परिभाषय GL_COMPRESSED_RGBA_ASTC_5x4_KHR   0x93B1
#परिभाषय GL_COMPRESSED_RGBA_ASTC_5x5_KHR   0x93B2
#परिभाषय GL_COMPRESSED_RGBA_ASTC_6x5_KHR   0x93B3
#परिभाषय GL_COMPRESSED_RGBA_ASTC_6x6_KHR   0x93B4
#परिभाषय GL_COMPRESSED_RGBA_ASTC_8x5_KHR   0x93B5
#परिभाषय GL_COMPRESSED_RGBA_ASTC_8x6_KHR   0x93B6
#परिभाषय GL_COMPRESSED_RGBA_ASTC_8x8_KHR   0x93B7
#परिभाषय GL_COMPRESSED_RGBA_ASTC_10x5_KHR  0x93B8
#परिभाषय GL_COMPRESSED_RGBA_ASTC_10x6_KHR  0x93B9
#परिभाषय GL_COMPRESSED_RGBA_ASTC_10x8_KHR  0x93BA
#परिभाषय GL_COMPRESSED_RGBA_ASTC_10x10_KHR 0x93BB
#परिभाषय GL_COMPRESSED_RGBA_ASTC_12x10_KHR 0x93BC
#परिभाषय GL_COMPRESSED_RGBA_ASTC_12x12_KHR 0x93BD
#परिभाषय GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR 0x93D0
#परिभाषय GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR 0x93D1
#परिभाषय GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR 0x93D2
#परिभाषय GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR 0x93D3
#परिभाषय GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR 0x93D4
#परिभाषय GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR 0x93D5
#परिभाषय GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR 0x93D6
#परिभाषय GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR 0x93D7
#परिभाषय GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR 0x93D8
#परिभाषय GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR 0x93D9
#परिभाषय GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR 0x93DA
#परिभाषय GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR 0x93DB
#परिभाषय GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR 0x93DC
#परिभाषय GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR 0x93DD
#यदि_अन्तः /* GL_KHR_texture_compression_astc_hdr */

#यदि_अपरिभाषितम् GL_KHR_texture_compression_astc_ldr
#परिभाषय GL_KHR_texture_compression_astc_ldr 1
#यदि_अन्तः /* GL_KHR_texture_compression_astc_ldr */

#यदि_अपरिभाषितम् GL_KHR_texture_compression_astc_sliced_3d
#परिभाषय GL_KHR_texture_compression_astc_sliced_3d 1
#यदि_अन्तः /* GL_KHR_texture_compression_astc_sliced_3d */

#यदि_अपरिभाषितम् GL_OES_EGL_image
#परिभाषय GL_OES_EGL_image 1
प्रकारनिर्देश शून्य *GLeglImageOES;
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLEGLIMAGETARGETTEXTURE2DOESPROC) (GLenum target, GLeglImageOES image);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLEGLIMAGETARGETRENDERBUFFERSTORAGEOESPROC) (GLenum target, GLeglImageOES image);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glEGLImageTargetTexture2DOES (GLenum target, GLeglImageOES image);
GL_APICALL शून्य GL_APIENTRY glEGLImageTargetRenderbufferStorageOES (GLenum target, GLeglImageOES image);
#यदि_अन्तः
#यदि_अन्तः /* GL_OES_EGL_image */

#यदि_अपरिभाषितम् GL_OES_EGL_image_external
#परिभाषय GL_OES_EGL_image_external 1
#परिभाषय GL_TEXTURE_EXTERNAL_OES           0x8D65
#परिभाषय GL_TEXTURE_BINDING_EXTERNAL_OES   0x8D67
#परिभाषय GL_REQUIRED_TEXTURE_IMAGE_UNITS_OES 0x8D68
#परिभाषय GL_SAMPLER_EXTERNAL_OES           0x8D66
#यदि_अन्तः /* GL_OES_EGL_image_external */

#यदि_अपरिभाषितम् GL_OES_EGL_image_external_essl3
#परिभाषय GL_OES_EGL_image_external_essl3 1
#यदि_अन्तः /* GL_OES_EGL_image_external_essl3 */

#यदि_अपरिभाषितम् GL_OES_compressed_ETC1_RGB8_sub_texture
#परिभाषय GL_OES_compressed_ETC1_RGB8_sub_texture 1
#यदि_अन्तः /* GL_OES_compressed_ETC1_RGB8_sub_texture */

#यदि_अपरिभाषितम् GL_OES_compressed_ETC1_RGB8_texture
#परिभाषय GL_OES_compressed_ETC1_RGB8_texture 1
#परिभाषय GL_ETC1_RGB8_OES                  0x8D64
#यदि_अन्तः /* GL_OES_compressed_ETC1_RGB8_texture */

#यदि_अपरिभाषितम् GL_OES_compressed_paletted_texture
#परिभाषय GL_OES_compressed_paletted_texture 1
#परिभाषय GL_PALETTE4_RGB8_OES              0x8B90
#परिभाषय GL_PALETTE4_RGBA8_OES             0x8B91
#परिभाषय GL_PALETTE4_R5_G6_B5_OES          0x8B92
#परिभाषय GL_PALETTE4_RGBA4_OES             0x8B93
#परिभाषय GL_PALETTE4_RGB5_A1_OES           0x8B94
#परिभाषय GL_PALETTE8_RGB8_OES              0x8B95
#परिभाषय GL_PALETTE8_RGBA8_OES             0x8B96
#परिभाषय GL_PALETTE8_R5_G6_B5_OES          0x8B97
#परिभाषय GL_PALETTE8_RGBA4_OES             0x8B98
#परिभाषय GL_PALETTE8_RGB5_A1_OES           0x8B99
#यदि_अन्तः /* GL_OES_compressed_paletted_texture */

#यदि_अपरिभाषितम् GL_OES_copy_image
#परिभाषय GL_OES_copy_image 1
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCOPYIMAGESUBDATAOESPROC) (GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei src_विस्तारः, GLsizei srcHeight, GLsizei src_गभीरता);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_Copy_Image_Sub_दत्त_OES (GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei src_विस्तारः, GLsizei srcHeight, GLsizei src_गभीरता);
#यदि_अन्तः
#यदि_अन्तः /* GL_OES_copy_image */

#यदि_अपरिभाषितम् GL_OES_depth24
#परिभाषय GL_OES_depth24 1
#परिभाषय GL_गभीरता_COMPONENT24_OES          0x81A6
#यदि_अन्तः /* GL_OES_depth24 */

#यदि_अपरिभाषितम् GL_OES_depth32
#परिभाषय GL_OES_depth32 1
#परिभाषय GL_गभीरता_COMPONENT32_OES          0x81A7
#यदि_अन्तः /* GL_OES_depth32 */

#यदि_अपरिभाषितम् GL_OES_गभीरता_texture
#परिभाषय GL_OES_गभीरता_texture 1
#यदि_अन्तः /* GL_OES_depth_texture */

#यदि_अपरिभाषितम् GL_OES_draw_buffers_अनुक्रमितम्
#परिभाषय GL_OES_draw_buffers_अनुक्रमितम् 1
#परिभाषय GL_MIN                            0x8007
#परिभाषय GL_MAX                            0x8008
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLENABLEIOESPROC) (GLenum target, GLuint सूचकांक);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDISABLEIOESPROC) (GLenum target, GLuint सूचकांक);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBLENDEQUATIONIOESPROC) (GLuint buf, GLenum बहुलकम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEIOESPROC) (GLuint buf, GLenum बहुलकम्_RGB, GLenum बहुलकम्_Alpha);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBLENDFUNCIOESPROC) (GLuint buf, GLenum src, GLenum dst);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEIOESPROC) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCOLORMASKIOESPROC) (GLuint सूचकांक, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLISENABLEDIOESPROC) (GLenum target, GLuint सूचकांक);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glEnableiOES (GLenum target, GLuint सूचकांक);
GL_APICALL शून्य GL_APIENTRY glDisableiOES (GLenum target, GLuint सूचकांक);
GL_APICALL शून्य GL_APIENTRY glBlendEquationiOES (GLuint buf, GLenum बहुलकम्);
GL_APICALL शून्य GL_APIENTRY glBlendEquationSeparateiOES (GLuint buf, GLenum बहुलकम्_RGB, GLenum बहुलकम्_Alpha);
GL_APICALL शून्य GL_APIENTRY glBlendFunciOES (GLuint buf, GLenum src, GLenum dst);
GL_APICALL शून्य GL_APIENTRY glBlendFuncSeparateiOES (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
GL_APICALL शून्य GL_APIENTRY glColorMaskiOES (GLuint सूचकांक, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
GL_APICALL GLboolean GL_APIENTRY glIsEnablediOES (GLenum target, GLuint सूचकांक);
#यदि_अन्तः
#यदि_अन्तः /* GL_OES_draw_buffers_indexed */

#यदि_अपरिभाषितम् GL_OES_draw_elements_आधारः_vertex
#परिभाषय GL_OES_draw_elements_आधारः_vertex 1
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWELEMENTSBASEVERTEXOESPROC) (GLenum बहुलकम्, GLsizei गणनम्, GLenum type, ध्रुव शून्य *indices, GLint basevertex);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWRANGEELEMENTSBASEVERTEXOESPROC) (GLenum बहुलकम्, GLuint start, GLuint अन्तः, GLsizei गणनम्, GLenum type, ध्रुव शून्य *indices, GLint basevertex);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXOESPROC) (GLenum बहुलकम्, GLsizei गणनम्, GLenum type, ध्रुव शून्य *indices, GLsizei instancecount, GLint basevertex);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSBASEVERTEXEXTPROC) (GLenum बहुलकम्, ध्रुव GLsizei *गणनम्, GLenum type, ध्रुव शून्य *ध्रुव*indices, GLsizei drawcount, ध्रुव GLint *basevertex);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_Draw_Elements_आधारः_Vertex_OES (GLenum बहुलकम्, GLsizei गणनम्, GLenum type, ध्रुव शून्य *indices, GLint basevertex);
GL_APICALL शून्य GL_APIENTRY gl_Draw_Range_Elements_आधारः_Vertex_OES (GLenum बहुलकम्, GLuint start, GLuint अन्तः, GLsizei गणनम्, GLenum type, ध्रुव शून्य *indices, GLint basevertex);
GL_APICALL शून्य GL_APIENTRY gl_Draw_Elements_Instanced_आधारः_Vertex_OES (GLenum बहुलकम्, GLsizei गणनम्, GLenum type, ध्रुव शून्य *indices, GLsizei instancecount, GLint basevertex);
GL_APICALL शून्य GL_APIENTRY gl_Multi_Draw_Elements_आधारः_Vertex_EXT (GLenum बहुलकम्, ध्रुव GLsizei *गणनम्, GLenum type, ध्रुव शून्य *ध्रुव*indices, GLsizei drawcount, ध्रुव GLint *basevertex);
#यदि_अन्तः
#यदि_अन्तः /* GL_OES_draw_elements_base_vertex */

#यदि_अपरिभाषितम् GL_OES_element_सूचकांक_uint
#परिभाषय GL_OES_element_सूचकांक_uint 1
#यदि_अन्तः /* GL_OES_element_index_uint */

#यदि_अपरिभाषितम् GL_OES_fbo_render_mipmap
#परिभाषय GL_OES_fbo_render_mipmap 1
#यदि_अन्तः /* GL_OES_fbo_render_mipmap */

#यदि_अपरिभाषितम् GL_OES_fragment_precision_उच्चः
#परिभाषय GL_OES_fragment_precision_उच्चः 1
#यदि_अन्तः /* GL_OES_fragment_precision_high */

#यदि_अपरिभाषितम् GL_OES_geometry_point_आकार
#परिभाषय GL_OES_geometry_point_आकार 1
#यदि_अन्तः /* GL_OES_geometry_point_size */

#यदि_अपरिभाषितम् GL_OES_geometry_shader
#परिभाषय GL_OES_geometry_shader 1
#परिभाषय GL_GEOMETRY_SHADER_OES            0x8DD9
#परिभाषय GL_GEOMETRY_SHADER_BIT_OES        0x00000004
#परिभाषय GL_GEOMETRY_LINKED_VERTICES_बहिर्गमनम्_OES 0x8916
#परिभाषय GL_GEOMETRY_LINKED_निवेशः_TYPE_OES 0x8917
#परिभाषय GL_GEOMETRY_LINKED_OUTPUT_TYPE_OES 0x8918
#परिभाषय GL_GEOMETRY_SHADER_INVOCATIONS_OES 0x887F
#परिभाषय GL_LAYER_PROVOKING_VERTEX_OES     0x825E
#परिभाषय GL_पङ्क्तयः_ADJACENCY_OES            0x000A
#परिभाषय GL_पङ्क्तिः_STRIP_ADJACENCY_OES       0x000B
#परिभाषय GL_TRIANGLES_ADJACENCY_OES        0x000C
#परिभाषय GL_TRIANGLE_STRIP_ADJACENCY_OES   0x000D
#परिभाषय GL_MAX_GEOMETRY_एकरूपम्_COMPONENTS_OES 0x8DDF
#परिभाषय GL_MAX_GEOMETRY_एकरूपम्_खण्डानि_OES 0x8A2C
#परिभाषय GL_MAX_COMBINED_GEOMETRY_एकरूपम्_COMPONENTS_OES 0x8A32
#परिभाषय GL_MAX_GEOMETRY_निवेशः_COMPONENTS_OES 0x9123
#परिभाषय GL_MAX_GEOMETRY_OUTPUT_COMPONENTS_OES 0x9124
#परिभाषय GL_MAX_GEOMETRY_OUTPUT_VERTICES_OES 0x8DE0
#परिभाषय GL_MAX_GEOMETRY_योग_OUTPUT_COMPONENTS_OES 0x8DE1
#परिभाषय GL_MAX_GEOMETRY_SHADER_INVOCATIONS_OES 0x8E5A
#परिभाषय GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_OES 0x8C29
#परिभाषय GL_MAX_GEOMETRY_ATOMIC_गणक_BUFFERS_OES 0x92CF
#परिभाषय GL_MAX_GEOMETRY_ATOMIC_COUNTERS_OES 0x92D5
#परिभाषय GL_MAX_GEOMETRY_IMAGE_UNIFORMS_OES 0x90CD
#परिभाषय GL_MAX_GEOMETRY_SHADER_STORAGE_खण्डानि_OES 0x90D7
#परिभाषय GL_FIRST_VERTEX_CONVENTION_OES    0x8E4D
#परिभाषय GL_चरमः_VERTEX_CONVENTION_OES     0x8E4E
#परिभाषय GL_UNDEFINED_VERTEX_OES           0x8260
#परिभाषय GL_PRIMITIVES_GENERATED_OES       0x8C87
#परिभाषय GL_FRAMEBUFFER_DEFAULT_LAYERS_OES 0x9312
#परिभाषय GL_MAX_FRAMEBUFFER_LAYERS_OES     0x9317
#परिभाषय GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_OES 0x8DA8
#परिभाषय GL_FRAMEBUFFER_ATTACHMENT_LAYERED_OES 0x8DA7
#परिभाषय GL_REFERENCED_BY_GEOMETRY_SHADER_OES 0x9309
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREOESPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glFramebufferTextureOES (GLenum target, GLenum attachment, GLuint texture, GLint level);
#यदि_अन्तः
#यदि_अन्तः /* GL_OES_geometry_shader */

#यदि_अपरिभाषितम् GL_OES_get_क्रमादेशः_द्विमान
#परिभाषय GL_OES_get_क्रमादेशः_द्विमान 1
#परिभाषय GL_क्रमादेशः_द्विमान_दीर्घता_OES      0x8741
#परिभाषय GL_अङ्कः_क्रमादेशः_द्विमान_FORMATS_OES 0x87FE
#परिभाषय GL_क्रमादेशः_द्विमान_FORMATS_OES     0x87FF
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETPROGRAMBINARYOESPROC) (GLuint क्रमादेशः, GLsizei buf_आकार, GLsizei *दीर्घता, GLenum *द्विमान_Format, शून्य *द्विमान);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMBINARYOESPROC) (GLuint क्रमादेशः, GLenum द्विमान_Format, ध्रुव शून्य *द्विमान, GLint दीर्घता);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_Get_क्रमादेशः_द्विमान_OES (GLuint क्रमादेशः, GLsizei buf_आकार, GLsizei *दीर्घता, GLenum *द्विमान_Format, शून्य *द्विमान);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_द्विमान_OES (GLuint क्रमादेशः, GLenum द्विमान_Format, ध्रुव शून्य *द्विमान, GLint दीर्घता);
#यदि_अन्तः
#यदि_अन्तः /* GL_OES_get_program_binary */

#यदि_अपरिभाषितम् GL_OES_gpu_shader5
#परिभाषय GL_OES_gpu_shader5 1
#यदि_अन्तः /* GL_OES_gpu_shader5 */

#यदि_अपरिभाषितम् GL_OES_mapbuffer
#परिभाषय GL_OES_mapbuffer 1
#परिभाषय GL_WRITE_ONLY_OES                 0x88B9
#परिभाषय GL_बफर_ACCESS_OES              0x88BB
#परिभाषय GL_बफर_MAPPED_OES              0x88BC
#परिभाषय GL_बफर_MAP_POINTER_OES         0x88BD
प्रकारनिर्देश शून्य *(GL_APIENTRYP PFNGLMAPBUFFEROESPROC) (GLenum target, GLenum access);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLUNMAPBUFFEROESPROC) (GLenum target);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETBUFFERPOINTERVOESPROC) (GLenum target, GLenum pname, शून्य **params);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य *GL_APIENTRY gl_Map_बफर_OES (GLenum target, GLenum access);
GL_APICALL GLboolean GL_APIENTRY gl_Unmap_बफर_OES (GLenum target);
GL_APICALL शून्य GL_APIENTRY gl_Get_बफर_Pointerv_OES (GLenum target, GLenum pname, शून्य **params);
#यदि_अन्तः
#यदि_अन्तः /* GL_OES_mapbuffer */

#यदि_अपरिभाषितम् GL_OES_packed_गभीरता_stencil
#परिभाषय GL_OES_packed_गभीरता_stencil 1
#परिभाषय GL_गभीरता_STENCIL_OES              0x84F9
#परिभाषय GL_UNSIGNED_INT_24_8_OES          0x84FA
#परिभाषय GL_DEPTH24_STENCIL8_OES           0x88F0
#यदि_अन्तः /* GL_OES_packed_depth_stencil */

#यदि_अपरिभाषितम् GL_OES_primitive_bounding_box
#परिभाषय GL_OES_primitive_bounding_box 1
#परिभाषय GL_PRIMITIVE_BOUNDING_BOX_OES     0x92BE
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPRIMITIVEBOUNDINGBOXOESPROC) (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glPrimitiveBoundingBoxOES (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
#यदि_अन्तः
#यदि_अन्तः /* GL_OES_primitive_bounding_box */

#यदि_अपरिभाषितम् GL_OES_required_internalformat
#परिभाषय GL_OES_required_internalformat 1
#परिभाषय GL_ALPHA8_OES                     0x803C
#परिभाषय GL_गभीरता_COMPONENT16_OES          0x81A5
#परिभाषय GL_LUMINANCE4_ALPHA4_OES          0x8043
#परिभाषय GL_LUMINANCE8_ALPHA8_OES          0x8045
#परिभाषय GL_LUMINANCE8_OES                 0x8040
#परिभाषय GL_RGBA4_OES                      0x8056
#परिभाषय GL_RGB5_A1_OES                    0x8057
#परिभाषय GL_RGB565_OES                     0x8D62
#परिभाषय GL_RGB8_OES                       0x8051
#परिभाषय GL_RGBA8_OES                      0x8058
#परिभाषय GL_RGB10_EXT                      0x8052
#परिभाषय GL_RGB10_A2_EXT                   0x8059
#यदि_अन्तः /* GL_OES_required_internalformat */

#यदि_अपरिभाषितम् GL_OES_rgb8_rgba8
#परिभाषय GL_OES_rgb8_rgba8 1
#यदि_अन्तः /* GL_OES_rgb8_rgba8 */

#यदि_अपरिभाषितम् GL_OES_sample_shading
#परिभाषय GL_OES_sample_shading 1
#परिभाषय GL_SAMPLE_SHADING_OES             0x8C36
#परिभाषय GL_MIN_SAMPLE_SHADING_मानम्_OES   0x8C37
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMINSAMPLESHADINGOESPROC) (GLfloat मानम्);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glMinSampleShadingOES (GLfloat मानम्);
#यदि_अन्तः
#यदि_अन्तः /* GL_OES_sample_shading */

#यदि_अपरिभाषितम् GL_OES_sample_variables
#परिभाषय GL_OES_sample_variables 1
#यदि_अन्तः /* GL_OES_sample_variables */

#यदि_अपरिभाषितम् GL_OES_shader_image_atomic
#परिभाषय GL_OES_shader_image_atomic 1
#यदि_अन्तः /* GL_OES_shader_image_atomic */

#यदि_अपरिभाषितम् GL_OES_shader_io_खण्डानि
#परिभाषय GL_OES_shader_io_खण्डानि 1
#यदि_अन्तः /* GL_OES_shader_io_blocks */

#यदि_अपरिभाषितम् GL_OES_shader_multisample_interpolation
#परिभाषय GL_OES_shader_multisample_interpolation 1
#परिभाषय GL_MIN_FRAGMENT_INTERPOLATION_विस्थापनम्_OES 0x8E5B
#परिभाषय GL_MAX_FRAGMENT_INTERPOLATION_विस्थापनम्_OES 0x8E5C
#परिभाषय GL_FRAGMENT_INTERPOLATION_विस्थापनम्_द्वयङ्काः_OES 0x8E5D
#यदि_अन्तः /* GL_OES_shader_multisample_interpolation */

#यदि_अपरिभाषितम् GL_OES_standard_derivatives
#परिभाषय GL_OES_standard_derivatives 1
#परिभाषय GL_FRAGMENT_SHADER_DERIVATIVE_HINT_OES 0x8B8B
#यदि_अन्तः /* GL_OES_standard_derivatives */

#यदि_अपरिभाषितम् GL_OES_stencil1
#परिभाषय GL_OES_stencil1 1
#परिभाषय GL_STENCIL_INDEX1_OES             0x8D46
#यदि_अन्तः /* GL_OES_stencil1 */

#यदि_अपरिभाषितम् GL_OES_stencil4
#परिभाषय GL_OES_stencil4 1
#परिभाषय GL_STENCIL_INDEX4_OES             0x8D47
#यदि_अन्तः /* GL_OES_stencil4 */

#यदि_अपरिभाषितम् GL_OES_surfaceless_context
#परिभाषय GL_OES_surfaceless_context 1
#परिभाषय GL_FRAMEBUFFER_UNDEFINED_OES      0x8219
#यदि_अन्तः /* GL_OES_surfaceless_context */

#यदि_अपरिभाषितम् GL_OES_tessellation_point_आकार
#परिभाषय GL_OES_tessellation_point_आकार 1
#यदि_अन्तः /* GL_OES_tessellation_point_size */

#यदि_अपरिभाषितम् GL_OES_tessellation_shader
#परिभाषय GL_OES_tessellation_shader 1
#परिभाषय GL_PATCHES_OES                    0x000E
#परिभाषय GL_PATCH_VERTICES_OES             0x8E72
#परिभाषय GL_TESS_CONTROL_OUTPUT_VERTICES_OES 0x8E75
#परिभाषय GL_TESS_GEN_बहुलकम्_OES              0x8E76
#परिभाषय GL_TESS_GEN_SPACING_OES           0x8E77
#परिभाषय GL_TESS_GEN_VERTEX_क्रमः_OES      0x8E78
#परिभाषय GL_TESS_GEN_POINT_बहुलकम्_OES        0x8E79
#परिभाषय GL_ISOLINES_OES                   0x8E7A
#परिभाषय GL_QUADS_OES                      0x0007
#परिभाषय GL_FRACTIONAL_ODD_OES             0x8E7B
#परिभाषय GL_FRACTIONAL_EVEN_OES            0x8E7C
#परिभाषय GL_MAX_PATCH_VERTICES_OES         0x8E7D
#परिभाषय GL_MAX_TESS_GEN_LEVEL_OES         0x8E7E
#परिभाषय GL_MAX_TESS_CONTROL_एकरूपम्_COMPONENTS_OES 0x8E7F
#परिभाषय GL_MAX_TESS_EVALUATION_एकरूपम्_COMPONENTS_OES 0x8E80
#परिभाषय GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS_OES 0x8E81
#परिभाषय GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS_OES 0x8E82
#परिभाषय GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS_OES 0x8E83
#परिभाषय GL_MAX_TESS_PATCH_COMPONENTS_OES  0x8E84
#परिभाषय GL_MAX_TESS_CONTROL_योग_OUTPUT_COMPONENTS_OES 0x8E85
#परिभाषय GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS_OES 0x8E86
#परिभाषय GL_MAX_TESS_CONTROL_एकरूपम्_खण्डानि_OES 0x8E89
#परिभाषय GL_MAX_TESS_EVALUATION_एकरूपम्_खण्डानि_OES 0x8E8A
#परिभाषय GL_MAX_TESS_CONTROL_निवेशः_COMPONENTS_OES 0x886C
#परिभाषय GL_MAX_TESS_EVALUATION_निवेशः_COMPONENTS_OES 0x886D
#परिभाषय GL_MAX_COMBINED_TESS_CONTROL_एकरूपम्_COMPONENTS_OES 0x8E1E
#परिभाषय GL_MAX_COMBINED_TESS_EVALUATION_एकरूपम्_COMPONENTS_OES 0x8E1F
#परिभाषय GL_MAX_TESS_CONTROL_ATOMIC_गणक_BUFFERS_OES 0x92CD
#परिभाषय GL_MAX_TESS_EVALUATION_ATOMIC_गणक_BUFFERS_OES 0x92CE
#परिभाषय GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS_OES 0x92D3
#परिभाषय GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS_OES 0x92D4
#परिभाषय GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS_OES 0x90CB
#परिभाषय GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS_OES 0x90CC
#परिभाषय GL_MAX_TESS_CONTROL_SHADER_STORAGE_खण्डानि_OES 0x90D8
#परिभाषय GL_MAX_TESS_EVALUATION_SHADER_STORAGE_खण्डानि_OES 0x90D9
#परिभाषय GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED_OES 0x8221
#परिभाषय GL_IS_प्रत्येकम्_PATCH_OES               0x92E7
#परिभाषय GL_REFERENCED_BY_TESS_CONTROL_SHADER_OES 0x9307
#परिभाषय GL_REFERENCED_BY_TESS_EVALUATION_SHADER_OES 0x9308
#परिभाषय GL_TESS_CONTROL_SHADER_OES        0x8E88
#परिभाषय GL_TESS_EVALUATION_SHADER_OES     0x8E87
#परिभाषय GL_TESS_CONTROL_SHADER_BIT_OES    0x00000008
#परिभाषय GL_TESS_EVALUATION_SHADER_BIT_OES 0x00000010
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPATCHPARAMETERIOESPROC) (GLenum pname, GLint मानम्);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glPatchParameteriOES (GLenum pname, GLint मानम्);
#यदि_अन्तः
#यदि_अन्तः /* GL_OES_tessellation_shader */

#यदि_अपरिभाषितम् GL_OES_texture_3D
#परिभाषय GL_OES_texture_3D 1
#परिभाषय GL_TEXTURE_WRAP_R_OES             0x8072
#परिभाषय GL_TEXTURE_3D_OES                 0x806F
#परिभाषय GL_TEXTURE_BINDING_3D_OES         0x806A
#परिभाषय GL_MAX_3_D_TEXTURE_आकार_OES        0x8073
#परिभाषय GL_SAMPLER_3D_OES                 0x8B5F
#परिभाषय GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_3D_ZOFFSET_OES 0x8CD4
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXIMAGE3DOESPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2, GLint border, GLenum format, GLenum type, ध्रुव शून्य *pixels);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXSUBIMAGE3DOESPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2, GLenum format, GLenum type, ध्रुव शून्य *pixels);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCOPYTEXSUBIMAGE3DOESPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei विस्तारः, GLsizei height);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCOMPRESSEDTEXIMAGE3DOESPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2, GLint border, GLsizei image_आकार, ध्रुव शून्य *दत्त);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE3DOESPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2, GLenum format, GLsizei image_आकार, ध्रुव शून्य *दत्त);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE3DOESPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glTexImage3DOES (GLenum target, GLint level, GLenum internalformat, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2, GLint border, GLenum format, GLenum type, ध्रुव शून्य *pixels);
GL_APICALL शून्य GL_APIENTRY glTexSubImage3DOES (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2, GLenum format, GLenum type, ध्रुव शून्य *pixels);
GL_APICALL शून्य GL_APIENTRY glCopyTexSubImage3DOES (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei विस्तारः, GLsizei height);
GL_APICALL शून्य GL_APIENTRY glCompressedTexImage3DOES (GLenum target, GLint level, GLenum internalformat, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2, GLint border, GLsizei image_आकार, ध्रुव शून्य *दत्त);
GL_APICALL शून्य GL_APIENTRY glCompressedTexSubImage3DOES (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2, GLenum format, GLsizei image_आकार, ध्रुव शून्य *दत्त);
GL_APICALL शून्य GL_APIENTRY glFramebufferTexture3DOES (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
#यदि_अन्तः
#यदि_अन्तः /* GL_OES_texture_3D */

#यदि_अपरिभाषितम् GL_OES_texture_border_clamp
#परिभाषय GL_OES_texture_border_clamp 1
#परिभाषय GL_TEXTURE_BORDER_COLOR_OES       0x1004
#परिभाषय GL_CLAMP_गन्तव्यम्_BORDER_OES            0x812D
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXPARAMETERIIVOESPROC) (GLenum target, GLenum pname, ध्रुव GLint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXPARAMETERIUIVOESPROC) (GLenum target, GLenum pname, ध्रुव GLuint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETTEXPARAMETERIIVOESPROC) (GLenum target, GLenum pname, GLint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETTEXPARAMETERIUIVOESPROC) (GLenum target, GLenum pname, GLuint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSAMPLERPARAMETERIIVOESPROC) (GLuint sampler, GLenum pname, ध्रुव GLint *param);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSAMPLERPARAMETERIUIVOESPROC) (GLuint sampler, GLenum pname, ध्रुव GLuint *param);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIIVOESPROC) (GLuint sampler, GLenum pname, GLint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIUIVOESPROC) (GLuint sampler, GLenum pname, GLuint *params);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glTexParameterIivOES (GLenum target, GLenum pname, ध्रुव GLint *params);
GL_APICALL शून्य GL_APIENTRY glTexParameterIuivOES (GLenum target, GLenum pname, ध्रुव GLuint *params);
GL_APICALL शून्य GL_APIENTRY glGetTexParameterIivOES (GLenum target, GLenum pname, GLint *params);
GL_APICALL शून्य GL_APIENTRY glGetTexParameterIuivOES (GLenum target, GLenum pname, GLuint *params);
GL_APICALL शून्य GL_APIENTRY glSamplerParameterIivOES (GLuint sampler, GLenum pname, ध्रुव GLint *param);
GL_APICALL शून्य GL_APIENTRY glSamplerParameterIuivOES (GLuint sampler, GLenum pname, ध्रुव GLuint *param);
GL_APICALL शून्य GL_APIENTRY glGetSamplerParameterIivOES (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL शून्य GL_APIENTRY glGetSamplerParameterIuivOES (GLuint sampler, GLenum pname, GLuint *params);
#यदि_अन्तः
#यदि_अन्तः /* GL_OES_texture_border_clamp */

#यदि_अपरिभाषितम् GL_OES_texture_बफर
#परिभाषय GL_OES_texture_बफर 1
#परिभाषय GL_TEXTURE_बफर_OES             0x8C2A
#परिभाषय GL_TEXTURE_बफर_BINDING_OES     0x8C2A
#परिभाषय GL_MAX_TEXTURE_बफर_आकार_OES    0x8C2B
#परिभाषय GL_TEXTURE_BINDING_बफर_OES     0x8C2C
#परिभाषय GL_TEXTURE_बफर_दत्त_STORE_BINDING_OES 0x8C2D
#परिभाषय GL_TEXTURE_बफर_विस्थापनम्_ALIGNMENT_OES 0x919F
#परिभाषय GL_SAMPLER_बफर_OES             0x8DC2
#परिभाषय GL_INT_SAMPLER_बफर_OES         0x8DD0
#परिभाषय GL_UNSIGNED_INT_SAMPLER_बफर_OES 0x8DD8
#परिभाषय GL_IMAGE_बफर_OES               0x9051
#परिभाषय GL_INT_IMAGE_बफर_OES           0x905C
#परिभाषय GL_UNSIGNED_INT_IMAGE_बफर_OES  0x9067
#परिभाषय GL_TEXTURE_बफर_विस्थापनम्_OES      0x919D
#परिभाषय GL_TEXTURE_बफर_आकार_OES        0x919E
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXBUFFEROESPROC) (GLenum target, GLenum internalformat, GLuint बफर_2);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXBUFFERRANGEOESPROC) (GLenum target, GLenum internalformat, GLuint बफर_2, GLintptr विस्थापनम्_2, GLsizeiptr आकार);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_Tex_बफर_OES (GLenum target, GLenum internalformat, GLuint बफर_2);
GL_APICALL शून्य GL_APIENTRY gl_Tex_बफर_Range_OES (GLenum target, GLenum internalformat, GLuint बफर_2, GLintptr विस्थापनम्_2, GLsizeiptr आकार);
#यदि_अन्तः
#यदि_अन्तः /* GL_OES_texture_buffer */

#यदि_अपरिभाषितम् GL_OES_texture_compression_astc
#परिभाषय GL_OES_texture_compression_astc 1
#परिभाषय GL_COMPRESSED_RGBA_ASTC_3x3x3_OES 0x93C0
#परिभाषय GL_COMPRESSED_RGBA_ASTC_4x3x3_OES 0x93C1
#परिभाषय GL_COMPRESSED_RGBA_ASTC_4x4x3_OES 0x93C2
#परिभाषय GL_COMPRESSED_RGBA_ASTC_4x4x4_OES 0x93C3
#परिभाषय GL_COMPRESSED_RGBA_ASTC_5x4x4_OES 0x93C4
#परिभाषय GL_COMPRESSED_RGBA_ASTC_5x5x4_OES 0x93C5
#परिभाषय GL_COMPRESSED_RGBA_ASTC_5x5x5_OES 0x93C6
#परिभाषय GL_COMPRESSED_RGBA_ASTC_6x5x5_OES 0x93C7
#परिभाषय GL_COMPRESSED_RGBA_ASTC_6x6x5_OES 0x93C8
#परिभाषय GL_COMPRESSED_RGBA_ASTC_6x6x6_OES 0x93C9
#परिभाषय GL_COMPRESSED_SRGB8_ALPHA8_ASTC_3x3x3_OES 0x93E0
#परिभाषय GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x3x3_OES 0x93E1
#परिभाषय GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4x3_OES 0x93E2
#परिभाषय GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4x4_OES 0x93E3
#परिभाषय GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4x4_OES 0x93E4
#परिभाषय GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5x4_OES 0x93E5
#परिभाषय GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5x5_OES 0x93E6
#परिभाषय GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5x5_OES 0x93E7
#परिभाषय GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6x5_OES 0x93E8
#परिभाषय GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6x6_OES 0x93E9
#यदि_अन्तः /* GL_OES_texture_compression_astc */

#यदि_अपरिभाषितम् GL_OES_texture_cube_map_array
#परिभाषय GL_OES_texture_cube_map_array 1
#परिभाषय GL_TEXTURE_CUBE_MAP_ARRAY_OES     0x9009
#परिभाषय GL_TEXTURE_BINDING_CUBE_MAP_ARRAY_OES 0x900A
#परिभाषय GL_SAMPLER_CUBE_MAP_ARRAY_OES     0x900C
#परिभाषय GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW_OES 0x900D
#परिभाषय GL_INT_SAMPLER_CUBE_MAP_ARRAY_OES 0x900E
#परिभाषय GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY_OES 0x900F
#परिभाषय GL_IMAGE_CUBE_MAP_ARRAY_OES       0x9054
#परिभाषय GL_INT_IMAGE_CUBE_MAP_ARRAY_OES   0x905F
#परिभाषय GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY_OES 0x906A
#यदि_अन्तः /* GL_OES_texture_cube_map_array */

#यदि_अपरिभाषितम् GL_OES_texture_float
#परिभाषय GL_OES_texture_float 1
#यदि_अन्तः /* GL_OES_texture_float */

#यदि_अपरिभाषितम् GL_OES_texture_float_रैखिकम्
#परिभाषय GL_OES_texture_float_रैखिकम् 1
#यदि_अन्तः /* GL_OES_texture_float_linear */

#यदि_अपरिभाषितम् GL_OES_texture_half_float
#परिभाषय GL_OES_texture_half_float 1
#परिभाषय GL_HALF_FLOAT_OES                 0x8D61
#यदि_अन्तः /* GL_OES_texture_half_float */

#यदि_अपरिभाषितम् GL_OES_texture_half_float_रैखिकम्
#परिभाषय GL_OES_texture_half_float_रैखिकम् 1
#यदि_अन्तः /* GL_OES_texture_half_float_linear */

#यदि_अपरिभाषितम् GL_OES_texture_npot
#परिभाषय GL_OES_texture_npot 1
#यदि_अन्तः /* GL_OES_texture_npot */

#यदि_अपरिभाषितम् GL_OES_texture_stencil8
#परिभाषय GL_OES_texture_stencil8 1
#परिभाषय GL_STENCIL_सूचकांक_OES              0x1901
#परिभाषय GL_STENCIL_INDEX8_OES             0x8D48
#यदि_अन्तः /* GL_OES_texture_stencil8 */

#यदि_अपरिभाषितम् GL_OES_texture_storage_multisample_2d_array
#परिभाषय GL_OES_texture_storage_multisample_2d_array 1
#परिभाषय GL_TEXTURE_2D_MULTISAMPLE_ARRAY_OES 0x9102
#परिभाषय GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY_OES 0x9105
#परिभाषय GL_SAMPLER_2D_MULTISAMPLE_ARRAY_OES 0x910B
#परिभाषय GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY_OES 0x910C
#परिभाषय GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY_OES 0x910D
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXSTORAGE3DMULTISAMPLEOESPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2, GLboolean fixedsamplelocations);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glTexStorage3DMultisampleOES (GLenum target, GLsizei samples, GLenum internalformat, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2, GLboolean fixedsamplelocations);
#यदि_अन्तः
#यदि_अन्तः /* GL_OES_texture_storage_multisample_2d_array */

#यदि_अपरिभाषितम् GL_OES_texture_view
#परिभाषय GL_OES_texture_view 1
#परिभाषय GL_TEXTURE_VIEW_MIN_LEVEL_OES     0x82DB
#परिभाषय GL_TEXTURE_VIEW_अङ्कः_स्तराः_OES    0x82DC
#परिभाषय GL_TEXTURE_VIEW_MIN_LAYER_OES     0x82DD
#परिभाषय GL_TEXTURE_VIEW_अङ्कः_LAYERS_OES    0x82DE
#परिभाषय GL_TEXTURE_IMMUTABLE_स्तराः       0x82DF
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXTUREVIEWOESPROC) (GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glTextureViewOES (GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
#यदि_अन्तः
#यदि_अन्तः /* GL_OES_texture_view */

#यदि_अपरिभाषितम् GL_OES_vertex_array_object
#परिभाषय GL_OES_vertex_array_object 1
#परिभाषय GL_VERTEX_ARRAY_BINDING_OES       0x85B5
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBINDVERTEXARRAYOESPROC) (GLuint array);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDELETEVERTEXARRAYSOESPROC) (GLsizei n, ध्रुव GLuint *arrays);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGENVERTEXARRAYSOESPROC) (GLsizei n, GLuint *arrays);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLISVERTEXARRAYOESPROC) (GLuint array);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glBindVertexArrayOES (GLuint array);
GL_APICALL शून्य GL_APIENTRY glDeleteVertexArraysOES (GLsizei n, ध्रुव GLuint *arrays);
GL_APICALL शून्य GL_APIENTRY glGenVertexArraysOES (GLsizei n, GLuint *arrays);
GL_APICALL GLboolean GL_APIENTRY glIsVertexArrayOES (GLuint array);
#यदि_अन्तः
#यदि_अन्तः /* GL_OES_vertex_array_object */

#यदि_अपरिभाषितम् GL_OES_vertex_half_float
#परिभाषय GL_OES_vertex_half_float 1
#यदि_अन्तः /* GL_OES_vertex_half_float */

#यदि_अपरिभाषितम् GL_OES_vertex_type_10_10_10_2
#परिभाषय GL_OES_vertex_type_10_10_10_2 1
#परिभाषय GL_UNSIGNED_INT_10_10_10_2_OES    0x8DF6
#परिभाषय GL_INT_10_10_10_2_OES             0x8DF7
#यदि_अन्तः /* GL_OES_vertex_type_10_10_10_2 */

#यदि_अपरिभाषितम् GL_OES_viewport_array
#परिभाषय GL_OES_viewport_array 1
#परिभाषय GL_MAX_VIEWPORTS_OES              0x825B
#परिभाषय GL_VIEWPORT_SUBPIXEL_द्वयङ्काः_OES     0x825C
#परिभाषय GL_VIEWPORT_BOUNDS_RANGE_OES      0x825D
#परिभाषय GL_VIEWPORT_सूचकांक_PROVOKING_VERTEX_OES 0x825F
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLVIEWPORTARRAYVOESPROC) (GLuint first, GLsizei गणनम्, ध्रुव GLfloat *v);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLVIEWPORTINDEXEDFOESPROC) (GLuint सूचकांक, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLVIEWPORTINDEXEDFVOESPROC) (GLuint सूचकांक, ध्रुव GLfloat *v);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSCISSORARRAYVOESPROC) (GLuint first, GLsizei गणनम्, ध्रुव GLint *v);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSCISSORINDEXEDOESPROC) (GLuint सूचकांक, GLint वामः, GLint bottom, GLsizei विस्तारः, GLsizei height);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSCISSORINDEXEDVOESPROC) (GLuint सूचकांक, ध्रुव GLint *v);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDEPTHRANGEARRAYFVOESPROC) (GLuint first, GLsizei गणनम्, ध्रुव GLfloat *v);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDEPTHRANGEINDEXEDFOESPROC) (GLuint सूचकांक, GLfloat n, GLfloat f);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETFLOATI_VOESPROC) (GLenum target, GLuint सूचकांक, GLfloat *दत्त);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glViewportArrayvOES (GLuint first, GLsizei गणनम्, ध्रुव GLfloat *v);
GL_APICALL शून्य GL_APIENTRY glViewportIndexedfOES (GLuint सूचकांक, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
GL_APICALL शून्य GL_APIENTRY glViewportIndexedfvOES (GLuint सूचकांक, ध्रुव GLfloat *v);
GL_APICALL शून्य GL_APIENTRY glScissorArrayvOES (GLuint first, GLsizei गणनम्, ध्रुव GLint *v);
GL_APICALL शून्य GL_APIENTRY gl_Scissor_अनुक्रमितम्_OES (GLuint सूचकांक, GLint वामः, GLint bottom, GLsizei विस्तारः, GLsizei height);
GL_APICALL शून्य GL_APIENTRY glScissorIndexedvOES (GLuint सूचकांक, ध्रुव GLint *v);
GL_APICALL शून्य GL_APIENTRY gl_गभीरता_Range_Arrayfv_OES (GLuint first, GLsizei गणनम्, ध्रुव GLfloat *v);
GL_APICALL शून्य GL_APIENTRY gl_गभीरता_Range_Indexedf_OES (GLuint सूचकांक, GLfloat n, GLfloat f);
GL_APICALL शून्य GL_APIENTRY glGetFloati_vOES (GLenum target, GLuint सूचकांक, GLfloat *दत्त);
#यदि_अन्तः
#यदि_अन्तः /* GL_OES_viewport_array */

#यदि_अपरिभाषितम् GL_AMD_compressed_3DC_texture
#परिभाषय GL_AMD_compressed_3DC_texture 1
#परिभाषय GL_3DC_X_AMD                      0x87F9
#परिभाषय GL_3DC_XY_AMD                     0x87FA
#यदि_अन्तः /* GL_AMD_compressed_3DC_texture */

#यदि_अपरिभाषितम् GL_AMD_compressed_ATC_texture
#परिभाषय GL_AMD_compressed_ATC_texture 1
#परिभाषय GL_ATC_RGB_AMD                    0x8C92
#परिभाषय GL_ATC_RGBA_EXPLICIT_ALPHA_AMD    0x8C93
#परिभाषय GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD 0x87EE
#यदि_अन्तः /* GL_AMD_compressed_ATC_texture */

#यदि_अपरिभाषितम् GL_AMD_framebuffer_multisample_advanced
#परिभाषय GL_AMD_framebuffer_multisample_advanced 1
#परिभाषय GL_RENDERBUFFER_STORAGE_SAMPLES_AMD 0x91B2
#परिभाषय GL_MAX_COLOR_FRAMEBUFFER_SAMPLES_AMD 0x91B3
#परिभाषय GL_MAX_COLOR_FRAMEBUFFER_STORAGE_SAMPLES_AMD 0x91B4
#परिभाषय GL_MAX_गभीरता_STENCIL_FRAMEBUFFER_SAMPLES_AMD 0x91B5
#परिभाषय GL_अङ्कः_SUPPORTED_MULTISAMPLE_MODES_AMD 0x91B6
#परिभाषय GL_SUPPORTED_MULTISAMPLE_MODES_AMD 0x91B7
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC) (GLenum target, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei विस्तारः, GLsizei height);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC) (GLuint renderbuffer, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei विस्तारः, GLsizei height);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glRenderbufferStorageMultisampleAdvancedAMD (GLenum target, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei विस्तारः, GLsizei height);
GL_APICALL शून्य GL_APIENTRY glNamedRenderbufferStorageMultisampleAdvancedAMD (GLuint renderbuffer, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei विस्तारः, GLsizei height);
#यदि_अन्तः
#यदि_अन्तः /* GL_AMD_framebuffer_multisample_advanced */

#यदि_अपरिभाषितम् GL_AMD_performance_monitor
#परिभाषय GL_AMD_performance_monitor 1
#परिभाषय GL_गणक_TYPE_AMD               0x8BC0
#परिभाषय GL_गणक_RANGE_AMD              0x8BC1
#परिभाषय GL_UNSIGNED_INT64_AMD             0x8BC2
#परिभाषय GL_PERCENTAGE_AMD                 0x8BC3
#परिभाषय GL_PERFMON_परिणाम_उपलब्धम्_AMD   0x8BC4
#परिभाषय GL_PERFMON_परिणाम_आकार_AMD        0x8BC5
#परिभाषय GL_PERFMON_परिणाम_AMD             0x8BC6
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETPERFMONITORGROUPSAMDPROC) (GLint *अङ्कः_Groups, GLsizei groups_आकार, GLuint *groups);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETPERFMONITORCOUNTERSAMDPROC) (GLuint गणः, GLint *अङ्कः_Counters, GLint *max_सक्रिय_Counters, GLsizei गणक_आकार, GLuint *counters);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETPERFMONITORGROUPSTRINGAMDPROC) (GLuint गणः, GLsizei buf_आकार, GLsizei *दीर्घता, GLchar *गणः_String);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC) (GLuint गणः, GLuint गणक, GLsizei buf_आकार, GLsizei *दीर्घता, GLchar *गणक_String);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETPERFMONITORCOUNTERINFOAMDPROC) (GLuint गणः, GLuint गणक, GLenum pname, शून्य *दत्त);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGENPERFMONITORSAMDPROC) (GLsizei n, GLuint *monitors);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDELETEPERFMONITORSAMDPROC) (GLsizei n, GLuint *monitors);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSELECTPERFMONITORCOUNTERSAMDPROC) (GLuint monitor, GLboolean enable, GLuint गणः, GLint अङ्कः_Counters, GLuint *गणक_List);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBEGINPERFMONITORAMDPROC) (GLuint monitor);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLENDPERFMONITORAMDPROC) (GLuint monitor);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETPERFMONITORCOUNTERDATAAMDPROC) (GLuint monitor, GLenum pname, GLsizei दत्त_आकार_2, GLuint *दत्त, GLint *अष्टकानि_Written);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glGetPerfMonitorGroupsAMD (GLint *अङ्कः_Groups, GLsizei groups_आकार, GLuint *groups);
GL_APICALL शून्य GL_APIENTRY glGetPerfMonitorCountersAMD (GLuint गणः, GLint *अङ्कः_Counters, GLint *max_सक्रिय_Counters, GLsizei गणक_आकार, GLuint *counters);
GL_APICALL शून्य GL_APIENTRY gl_Get_Perf_Monitor_गणः_String_AMD (GLuint गणः, GLsizei buf_आकार, GLsizei *दीर्घता, GLchar *गणः_String);
GL_APICALL शून्य GL_APIENTRY gl_Get_Perf_Monitor_गणक_String_AMD (GLuint गणः, GLuint गणक, GLsizei buf_आकार, GLsizei *दीर्घता, GLchar *गणक_String);
GL_APICALL शून्य GL_APIENTRY gl_Get_Perf_Monitor_गणक_Info_AMD (GLuint गणः, GLuint गणक, GLenum pname, शून्य *दत्त);
GL_APICALL शून्य GL_APIENTRY glGenPerfMonitorsAMD (GLsizei n, GLuint *monitors);
GL_APICALL शून्य GL_APIENTRY glDeletePerfMonitorsAMD (GLsizei n, GLuint *monitors);
GL_APICALL शून्य GL_APIENTRY glSelectPerfMonitorCountersAMD (GLuint monitor, GLboolean enable, GLuint गणः, GLint अङ्कः_Counters, GLuint *गणक_List);
GL_APICALL शून्य GL_APIENTRY glBeginPerfMonitorAMD (GLuint monitor);
GL_APICALL शून्य GL_APIENTRY gl_अन्तः_Perf_Monitor_AMD (GLuint monitor);
GL_APICALL शून्य GL_APIENTRY gl_Get_Perf_Monitor_गणक_दत्त_AMD (GLuint monitor, GLenum pname, GLsizei दत्त_आकार_2, GLuint *दत्त, GLint *अष्टकानि_Written);
#यदि_अन्तः
#यदि_अन्तः /* GL_AMD_performance_monitor */

#यदि_अपरिभाषितम् GL_AMD_क्रमादेशः_द्विमान_Z400
#परिभाषय GL_AMD_क्रमादेशः_द्विमान_Z400 1
#परिभाषय GL_Z400_द्विमान_AMD                0x8740
#यदि_अन्तः /* GL_AMD_program_binary_Z400 */

#यदि_अपरिभाषितम् GL_ANDROID_extension_pack_es31a
#परिभाषय GL_ANDROID_extension_pack_es31a 1
#यदि_अन्तः /* GL_ANDROID_extension_pack_es31a */

#यदि_अपरिभाषितम् GL_ANGLE_गभीरता_texture
#परिभाषय GL_ANGLE_गभीरता_texture 1
#यदि_अन्तः /* GL_ANGLE_depth_texture */

#यदि_अपरिभाषितम् GL_ANGLE_framebuffer_blit
#परिभाषय GL_ANGLE_framebuffer_blit 1
#परिभाषय GL_READ_FRAMEBUFFER_ANGLE         0x8CA8
#परिभाषय GL_DRAW_FRAMEBUFFER_ANGLE         0x8CA9
#परिभाषय GL_DRAW_FRAMEBUFFER_BINDING_ANGLE 0x8CA6
#परिभाषय GL_READ_FRAMEBUFFER_BINDING_ANGLE 0x8CAA
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBLITFRAMEBUFFERANGLEPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield आवरणम्, GLenum filter);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glBlitFramebufferANGLE (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield आवरणम्, GLenum filter);
#यदि_अन्तः
#यदि_अन्तः /* GL_ANGLE_framebuffer_blit */

#यदि_अपरिभाषितम् GL_ANGLE_framebuffer_multisample
#परिभाषय GL_ANGLE_framebuffer_multisample 1
#परिभाषय GL_RENDERBUFFER_SAMPLES_ANGLE     0x8CAB
#परिभाषय GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_ANGLE 0x8D56
#परिभाषय GL_MAX_SAMPLES_ANGLE              0x8D57
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEANGLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei विस्तारः, GLsizei height);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glRenderbufferStorageMultisampleANGLE (GLenum target, GLsizei samples, GLenum internalformat, GLsizei विस्तारः, GLsizei height);
#यदि_अन्तः
#यदि_अन्तः /* GL_ANGLE_framebuffer_multisample */

#यदि_अपरिभाषितम् GL_ANGLE_instanced_arrays
#परिभाषय GL_ANGLE_instanced_arrays 1
#परिभाषय GL_VERTEX_ATTRIB_ARRAY_भाजकः_ANGLE 0x88FE
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDANGLEPROC) (GLenum बहुलकम्, GLint first, GLsizei गणनम्, GLsizei primcount);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDANGLEPROC) (GLenum बहुलकम्, GLsizei गणनम्, GLenum type, ध्रुव शून्य *indices, GLsizei primcount);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLVERTEXATTRIBDIVISORANGLEPROC) (GLuint सूचकांक, GLuint भाजकः);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glDrawArraysInstancedANGLE (GLenum बहुलकम्, GLint first, GLsizei गणनम्, GLsizei primcount);
GL_APICALL शून्य GL_APIENTRY glDrawElementsInstancedANGLE (GLenum बहुलकम्, GLsizei गणनम्, GLenum type, ध्रुव शून्य *indices, GLsizei primcount);
GL_APICALL शून्य GL_APIENTRY gl_Vertex_Attrib_भाजकः_ANGLE (GLuint सूचकांक, GLuint भाजकः);
#यदि_अन्तः
#यदि_अन्तः /* GL_ANGLE_instanced_arrays */

#यदि_अपरिभाषितम् GL_ANGLE_pack_reverse_row_क्रमः
#परिभाषय GL_ANGLE_pack_reverse_row_क्रमः 1
#परिभाषय GL_PACK_REVERSE_ROW_क्रमः_ANGLE   0x93A4
#यदि_अन्तः /* GL_ANGLE_pack_reverse_row_order */

#यदि_अपरिभाषितम् GL_ANGLE_क्रमादेशः_द्विमान
#परिभाषय GL_ANGLE_क्रमादेशः_द्विमान 1
#परिभाषय GL_क्रमादेशः_द्विमान_ANGLE           0x93A6
#यदि_अन्तः /* GL_ANGLE_program_binary */

#यदि_अपरिभाषितम् GL_ANGLE_texture_compression_dxt3
#परिभाषय GL_ANGLE_texture_compression_dxt3 1
#परिभाषय GL_COMPRESSED_RGBA_S3TC_DXT3_ANGLE 0x83F2
#यदि_अन्तः /* GL_ANGLE_texture_compression_dxt3 */

#यदि_अपरिभाषितम् GL_ANGLE_texture_compression_dxt5
#परिभाषय GL_ANGLE_texture_compression_dxt5 1
#परिभाषय GL_COMPRESSED_RGBA_S3TC_DXT5_ANGLE 0x83F3
#यदि_अन्तः /* GL_ANGLE_texture_compression_dxt5 */

#यदि_अपरिभाषितम् GL_ANGLE_texture_usage
#परिभाषय GL_ANGLE_texture_usage 1
#परिभाषय GL_TEXTURE_USAGE_ANGLE            0x93A2
#परिभाषय GL_FRAMEBUFFER_ATTACHMENT_ANGLE   0x93A3
#यदि_अन्तः /* GL_ANGLE_texture_usage */

#यदि_अपरिभाषितम् GL_ANGLE_translated_shader_source
#परिभाषय GL_ANGLE_translated_shader_source 1
#परिभाषय GL_TRANSLATED_SHADER_SOURCE_दीर्घता_ANGLE 0x93A0
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETTRANSLATEDSHADERSOURCEANGLEPROC) (GLuint shader, GLsizei buf_आकार, GLsizei *दीर्घता, GLchar *source);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glGetTranslatedShaderSourceANGLE (GLuint shader, GLsizei buf_आकार, GLsizei *दीर्घता, GLchar *source);
#यदि_अन्तः
#यदि_अन्तः /* GL_ANGLE_translated_shader_source */

#यदि_अपरिभाषितम् GL_APPLE_clip_distance
#परिभाषय GL_APPLE_clip_distance 1
#परिभाषय GL_MAX_CLIP_DISTANCES_APPLE       0x0D32
#परिभाषय GL_CLIP_DISTANCE0_APPLE           0x3000
#परिभाषय GL_CLIP_DISTANCE1_APPLE           0x3001
#परिभाषय GL_CLIP_DISTANCE2_APPLE           0x3002
#परिभाषय GL_CLIP_DISTANCE3_APPLE           0x3003
#परिभाषय GL_CLIP_DISTANCE4_APPLE           0x3004
#परिभाषय GL_CLIP_DISTANCE5_APPLE           0x3005
#परिभाषय GL_CLIP_DISTANCE6_APPLE           0x3006
#परिभाषय GL_CLIP_DISTANCE7_APPLE           0x3007
#यदि_अन्तः /* GL_APPLE_clip_distance */

#यदि_अपरिभाषितम् GL_APPLE_color_बफर_packed_float
#परिभाषय GL_APPLE_color_बफर_packed_float 1
#यदि_अन्तः /* GL_APPLE_color_buffer_packed_float */

#यदि_अपरिभाषितम् GL_APPLE_copy_texture_स्तराः
#परिभाषय GL_APPLE_copy_texture_स्तराः 1
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCOPYTEXTURELEVELSAPPLEPROC) (GLuint destinationTexture, GLuint sourceTexture, GLint source_आधारः_Level, GLsizei source_Level_गणनम्);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_Copy_Texture_स्तराः_APPLE (GLuint destinationTexture, GLuint sourceTexture, GLint source_आधारः_Level, GLsizei source_Level_गणनम्);
#यदि_अन्तः
#यदि_अन्तः /* GL_APPLE_copy_texture_levels */

#यदि_अपरिभाषितम् GL_APPLE_framebuffer_multisample
#परिभाषय GL_APPLE_framebuffer_multisample 1
#परिभाषय GL_RENDERBUFFER_SAMPLES_APPLE     0x8CAB
#परिभाषय GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_APPLE 0x8D56
#परिभाषय GL_MAX_SAMPLES_APPLE              0x8D57
#परिभाषय GL_READ_FRAMEBUFFER_APPLE         0x8CA8
#परिभाषय GL_DRAW_FRAMEBUFFER_APPLE         0x8CA9
#परिभाषय GL_DRAW_FRAMEBUFFER_BINDING_APPLE 0x8CA6
#परिभाषय GL_READ_FRAMEBUFFER_BINDING_APPLE 0x8CAA
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEAPPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei विस्तारः, GLsizei height);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLRESOLVEMULTISAMPLEFRAMEBUFFERAPPLEPROC) (शून्य);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glRenderbufferStorageMultisampleAPPLE (GLenum target, GLsizei samples, GLenum internalformat, GLsizei विस्तारः, GLsizei height);
GL_APICALL शून्य GL_APIENTRY glResolveMultisampleFramebufferAPPLE (शून्य);
#यदि_अन्तः
#यदि_अन्तः /* GL_APPLE_framebuffer_multisample */

#यदि_अपरिभाषितम् GL_APPLE_rgb_422
#परिभाषय GL_APPLE_rgb_422 1
#परिभाषय GL_RGB_422_APPLE                  0x8A1F
#परिभाषय GL_UNSIGNED_SHORT_8_8_APPLE       0x85BA
#परिभाषय GL_UNSIGNED_SHORT_8_8_REV_APPLE   0x85BB
#परिभाषय GL_RGB_RAW_422_APPLE              0x8A51
#यदि_अन्तः /* GL_APPLE_rgb_422 */

#यदि_अपरिभाषितम् GL_APPLE_sync
#परिभाषय GL_APPLE_sync 1
#परिभाषय GL_SYNC_OBJECT_APPLE              0x8A53
#परिभाषय GL_MAX_SERVER_WAIT_TIMEOUT_APPLE  0x9111
#परिभाषय GL_OBJECT_TYPE_APPLE              0x9112
#परिभाषय GL_SYNC_CONDITION_APPLE           0x9113
#परिभाषय GL_SYNC_स्थितिः_APPLE              0x9114
#परिभाषय GL_SYNC_FLAGS_APPLE               0x9115
#परिभाषय GL_SYNC_FENCE_APPLE               0x9116
#परिभाषय GL_SYNC_GPU_COMMANDS_COMPLETE_APPLE 0x9117
#परिभाषय GL_UNSIGNALED_APPLE               0x9118
#परिभाषय GL_SIGNALED_APPLE                 0x9119
#परिभाषय GL_ALREADY_SIGNALED_APPLE         0x911A
#परिभाषय GL_TIMEOUT_EXPIRED_APPLE          0x911B
#परिभाषय GL_CONDITION_SATISFIED_APPLE      0x911C
#परिभाषय GL_WAIT_FAILED_APPLE              0x911D
#परिभाषय GL_SYNC_FLUSH_COMMANDS_BIT_APPLE  0x00000001
#परिभाषय GL_TIMEOUT_IGNORED_APPLE          0xFFFFFFFFFFFFFFFFull
प्रकारनिर्देश GLsync (GL_APIENTRYP PFNGLFENCESYNCAPPLEPROC) (GLenum condition, GLbitfield flags);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLISSYNCAPPLEPROC) (GLsync sync);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDELETESYNCAPPLEPROC) (GLsync sync);
प्रकारनिर्देश GLenum (GL_APIENTRYP PFNGLCLIENTWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETINTEGER64VAPPLEPROC) (GLenum pname, GLint64 *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETSYNCIVAPPLEPROC) (GLsync sync, GLenum pname, GLsizei गणनम्, GLsizei *दीर्घता, GLint *मानानि);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL GLsync GL_APIENTRY glFenceSyncAPPLE (GLenum condition, GLbitfield flags);
GL_APICALL GLboolean GL_APIENTRY glIsSyncAPPLE (GLsync sync);
GL_APICALL शून्य GL_APIENTRY glDeleteSyncAPPLE (GLsync sync);
GL_APICALL GLenum GL_APIENTRY glClientWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_APICALL शून्य GL_APIENTRY glWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_APICALL शून्य GL_APIENTRY glGetInteger64vAPPLE (GLenum pname, GLint64 *params);
GL_APICALL शून्य GL_APIENTRY glGetSyncivAPPLE (GLsync sync, GLenum pname, GLsizei गणनम्, GLsizei *दीर्घता, GLint *मानानि);
#यदि_अन्तः
#यदि_अन्तः /* GL_APPLE_sync */

#यदि_अपरिभाषितम् GL_APPLE_texture_format_BGRA8888
#परिभाषय GL_APPLE_texture_format_BGRA8888 1
#परिभाषय GL_BGRA_EXT                       0x80E1
#परिभाषय GL_BGRA8_EXT                      0x93A1
#यदि_अन्तः /* GL_APPLE_texture_format_BGRA8888 */

#यदि_अपरिभाषितम् GL_APPLE_texture_max_level
#परिभाषय GL_APPLE_texture_max_level 1
#परिभाषय GL_TEXTURE_MAX_LEVEL_APPLE        0x813D
#यदि_अन्तः /* GL_APPLE_texture_max_level */

#यदि_अपरिभाषितम् GL_APPLE_texture_packed_float
#परिभाषय GL_APPLE_texture_packed_float 1
#परिभाषय GL_UNSIGNED_INT_10F_11F_11F_REV_APPLE 0x8C3B
#परिभाषय GL_UNSIGNED_INT_5_9_9_9_REV_APPLE 0x8C3E
#परिभाषय GL_R11F_G11F_B10F_APPLE           0x8C3A
#परिभाषय GL_RGB9_E5_APPLE                  0x8C3D
#यदि_अन्तः /* GL_APPLE_texture_packed_float */

#यदि_अपरिभाषितम् GL_ARM_mali_क्रमादेशः_द्विमान
#परिभाषय GL_ARM_mali_क्रमादेशः_द्विमान 1
#परिभाषय GL_MALI_क्रमादेशः_द्विमान_ARM        0x8F61
#यदि_अन्तः /* GL_ARM_mali_program_binary */

#यदि_अपरिभाषितम् GL_ARM_mali_shader_द्विमान
#परिभाषय GL_ARM_mali_shader_द्विमान 1
#परिभाषय GL_MALI_SHADER_द्विमान_ARM         0x8F60
#यदि_अन्तः /* GL_ARM_mali_shader_binary */

#यदि_अपरिभाषितम् GL_ARM_rgba8
#परिभाषय GL_ARM_rgba8 1
#यदि_अन्तः /* GL_ARM_rgba8 */

#यदि_अपरिभाषितम् GL_ARM_shader_core_properties
#परिभाषय GL_ARM_shader_core_properties 1
#परिभाषय GL_SHADER_CORE_गणनम्_ARM          0x96F0
#परिभाषय GL_SHADER_CORE_सक्रिय_गणनम्_ARM   0x96F1
#परिभाषय GL_SHADER_CORE_PRESENT_आवरणम्_ARM   0x96F2
#परिभाषय GL_SHADER_CORE_MAX_WARP_गणनम्_ARM 0x96F3
#परिभाषय GL_SHADER_CORE_PIXEL_दरः_ARM     0x96F4
#परिभाषय GL_SHADER_CORE_TEXEL_दरः_ARM     0x96F5
#परिभाषय GL_SHADER_CORE_FMA_दरः_ARM       0x96F6
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMAXACTIVESHADERCORESARMPROC) (GLuint गणनम्);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_Max_सक्रिय_Shader_Cores_ARM (GLuint गणनम्);
#यदि_अन्तः
#यदि_अन्तः /* GL_ARM_shader_core_properties */

#यदि_अपरिभाषितम् GL_ARM_shader_framebuffer_fetch
#परिभाषय GL_ARM_shader_framebuffer_fetch 1
#परिभाषय GL_FETCH_प्रत्येकम्_SAMPLE_ARM           0x8F65
#परिभाषय GL_FRAGMENT_SHADER_FRAMEBUFFER_FETCH_MRT_ARM 0x8F66
#यदि_अन्तः /* GL_ARM_shader_framebuffer_fetch */

#यदि_अपरिभाषितम् GL_ARM_shader_framebuffer_fetch_गभीरता_stencil
#परिभाषय GL_ARM_shader_framebuffer_fetch_गभीरता_stencil 1
#यदि_अन्तः /* GL_ARM_shader_framebuffer_fetch_depth_stencil */

#यदि_अपरिभाषितम् GL_ARM_texture_unnormalized_coordinates
#परिभाषय GL_ARM_texture_unnormalized_coordinates 1
#परिभाषय GL_TEXTURE_UNNORMALIZED_COORDINATES_ARM 0x8F6A
#यदि_अन्तः /* GL_ARM_texture_unnormalized_coordinates */

#यदि_अपरिभाषितम् GL_DMP_क्रमादेशः_द्विमान
#परिभाषय GL_DMP_क्रमादेशः_द्विमान 1
#परिभाषय GL_SMAPHS30_क्रमादेशः_द्विमान_DMP    0x9251
#परिभाषय GL_SMAPHS_क्रमादेशः_द्विमान_DMP      0x9252
#परिभाषय GL_DMP_क्रमादेशः_द्विमान_DMP         0x9253
#यदि_अन्तः /* GL_DMP_program_binary */

#यदि_अपरिभाषितम् GL_DMP_shader_द्विमान
#परिभाषय GL_DMP_shader_द्विमान 1
#परिभाषय GL_SHADER_द्विमान_DMP              0x9250
#यदि_अन्तः /* GL_DMP_shader_binary */

#यदि_अपरिभाषितम् GL_EXT_EGL_image_array
#परिभाषय GL_EXT_EGL_image_array 1
#यदि_अन्तः /* GL_EXT_EGL_image_array */

#यदि_अपरिभाषितम् GL_EXT_EGL_image_storage
#परिभाषय GL_EXT_EGL_image_storage 1
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLEGLIMAGETARGETTEXSTORAGEEXTPROC) (GLenum target, GLeglImageOES image, ध्रुव GLint* attrib_list);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLEGLIMAGETARGETTEXTURESTORAGEEXTPROC) (GLuint texture, GLeglImageOES image, ध्रुव GLint* attrib_list);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glEGLImageTargetTexStorageEXT (GLenum target, GLeglImageOES image, ध्रुव GLint* attrib_list);
GL_APICALL शून्य GL_APIENTRY glEGLImageTargetTextureStorageEXT (GLuint texture, GLeglImageOES image, ध्रुव GLint* attrib_list);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_EGL_image_storage */

#यदि_अपरिभाषितम् GL_EXT_EGL_image_storage_compression
#परिभाषय GL_EXT_EGL_image_storage_compression 1
#परिभाषय GL_SURFACE_COMPRESSION_EXT        0x96C0
#परिभाषय GL_SURFACE_COMPRESSION_FIXED_दरः_NONE_EXT 0x96C1
#परिभाषय GL_SURFACE_COMPRESSION_FIXED_दरः_DEFAULT_EXT 0x96C2
#यदि_अन्तः /* GL_EXT_EGL_image_storage_compression */

#यदि_अपरिभाषितम् GL_EXT_YUV_target
#परिभाषय GL_EXT_YUV_target 1
#परिभाषय GL_SAMPLER_EXTERNAL_2D_Y2Y_EXT    0x8BE7
#यदि_अन्तः /* GL_EXT_YUV_target */

#यदि_अपरिभाषितम् GL_EXT_आधारः_instance
#परिभाषय GL_EXT_आधारः_instance 1
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEEXTPROC) (GLenum बहुलकम्, GLint first, GLsizei गणनम्, GLsizei instancecount, GLuint baseinstance);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEEXTPROC) (GLenum बहुलकम्, GLsizei गणनम्, GLenum type, ध्रुव शून्य *indices, GLsizei instancecount, GLuint baseinstance);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEEXTPROC) (GLenum बहुलकम्, GLsizei गणनम्, GLenum type, ध्रुव शून्य *indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_Draw_Arrays_Instanced_आधारः_Instance_EXT (GLenum बहुलकम्, GLint first, GLsizei गणनम्, GLsizei instancecount, GLuint baseinstance);
GL_APICALL शून्य GL_APIENTRY gl_Draw_Elements_Instanced_आधारः_Instance_EXT (GLenum बहुलकम्, GLsizei गणनम्, GLenum type, ध्रुव शून्य *indices, GLsizei instancecount, GLuint baseinstance);
GL_APICALL शून्य GL_APIENTRY gl_Draw_Elements_Instanced_आधारः_Vertex_आधारः_Instance_EXT (GLenum बहुलकम्, GLsizei गणनम्, GLenum type, ध्रुव शून्य *indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_base_instance */

#यदि_अपरिभाषितम् GL_EXT_blend_func_extended
#परिभाषय GL_EXT_blend_func_extended 1
#परिभाषय GL_SRC1_COLOR_EXT                 0x88F9
#परिभाषय GL_SRC1_ALPHA_EXT                 0x8589
#परिभाषय GL_ONE_MINUS_SRC1_COLOR_EXT       0x88FA
#परिभाषय GL_ONE_MINUS_SRC1_ALPHA_EXT       0x88FB
#परिभाषय GL_SRC_ALPHA_SATURATE_EXT         0x0308
#परिभाषय GL_LOCATION_सूचकांक_EXT             0x930F
#परिभाषय GL_MAX_DUAL_SOURCE_DRAW_BUFFERS_EXT 0x88FC
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBINDFRAGDATALOCATIONINDEXEDEXTPROC) (GLuint क्रमादेशः, GLuint color_सङ्ख्या, GLuint सूचकांक, ध्रुव GLchar *name);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBINDFRAGDATALOCATIONEXTPROC) (GLuint क्रमादेशः, GLuint color, ध्रुव GLchar *name);
प्रकारनिर्देश GLint (GL_APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONINDEXEXTPROC) (GLuint क्रमादेशः, GLenum क्रमादेशः_Interface, ध्रुव GLchar *name);
प्रकारनिर्देश GLint (GL_APIENTRYP PFNGLGETFRAGDATAINDEXEXTPROC) (GLuint क्रमादेशः, ध्रुव GLchar *name);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_Bind_Frag_दत्त_Location_अनुक्रमितम्_EXT (GLuint क्रमादेशः, GLuint color_सङ्ख्या, GLuint सूचकांक, ध्रुव GLchar *name);
GL_APICALL शून्य GL_APIENTRY gl_Bind_Frag_दत्त_Location_EXT (GLuint क्रमादेशः, GLuint color, ध्रुव GLchar *name);
GL_APICALL GLint GL_APIENTRY gl_Get_क्रमादेशः_Resource_Location_सूचकांक_EXT (GLuint क्रमादेशः, GLenum क्रमादेशः_Interface, ध्रुव GLchar *name);
GL_APICALL GLint GL_APIENTRY gl_Get_Frag_दत्त_सूचकांक_EXT (GLuint क्रमादेशः, ध्रुव GLchar *name);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_blend_func_extended */

#यदि_अपरिभाषितम् GL_EXT_blend_minmax
#परिभाषय GL_EXT_blend_minmax 1
#परिभाषय GL_MIN_EXT                        0x8007
#परिभाषय GL_MAX_EXT                        0x8008
#यदि_अन्तः /* GL_EXT_blend_minmax */

#यदि_अपरिभाषितम् GL_EXT_बफर_storage
#परिभाषय GL_EXT_बफर_storage 1
#परिभाषय GL_MAP_READ_BIT                   0x0001
#परिभाषय GL_MAP_WRITE_BIT                  0x0002
#परिभाषय GL_MAP_PERSISTENT_BIT_EXT         0x0040
#परिभाषय GL_MAP_COHERENT_BIT_EXT           0x0080
#परिभाषय GL_DYNAMIC_STORAGE_BIT_EXT        0x0100
#परिभाषय GL_CLIENT_STORAGE_BIT_EXT         0x0200
#परिभाषय GL_CLIENT_MAPPED_बफर_BARRIER_BIT_EXT 0x00004000
#परिभाषय GL_बफर_IMMUTABLE_STORAGE_EXT   0x821F
#परिभाषय GL_बफर_STORAGE_FLAGS_EXT       0x8220
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBUFFERSTORAGEEXTPROC) (GLenum target, GLsizeiptr आकार, ध्रुव शून्य *दत्त, GLbitfield flags);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_बफर_Storage_EXT (GLenum target, GLsizeiptr आकार, ध्रुव शून्य *दत्त, GLbitfield flags);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_buffer_storage */

#यदि_अपरिभाषितम् GL_EXT_clear_texture
#परिभाषय GL_EXT_clear_texture 1
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCLEARTEXIMAGEEXTPROC) (GLuint texture, GLint level, GLenum format, GLenum type, ध्रुव शून्य *दत्त);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCLEARTEXSUBIMAGEEXTPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2, GLenum format, GLenum type, ध्रुव शून्य *दत्त);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glClearTexImageEXT (GLuint texture, GLint level, GLenum format, GLenum type, ध्रुव शून्य *दत्त);
GL_APICALL शून्य GL_APIENTRY glClearTexSubImageEXT (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2, GLenum format, GLenum type, ध्रुव शून्य *दत्त);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_clear_texture */

#यदि_अपरिभाषितम् GL_EXT_clip_control
#परिभाषय GL_EXT_clip_control 1
#परिभाषय GL_अधस्तनम्_वामः_EXT                 0x8CA1
#परिभाषय GL_ऊर्ध्वस्थम्_वामः_EXT                 0x8CA2
#परिभाषय GL_NEGATIVE_ONE_गन्तव्यम्_ONE_EXT        0x935E
#परिभाषय GL_ZERO_गन्तव्यम्_ONE_EXT                0x935F
#परिभाषय GL_CLIP_ORIGIN_EXT                0x935C
#परिभाषय GL_CLIP_गभीरता_बहुलकम्_EXT            0x935D
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCLIPCONTROLEXTPROC) (GLenum origin, GLenum गभीरता_2);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glClipControlEXT (GLenum origin, GLenum गभीरता_2);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_clip_control */

#यदि_अपरिभाषितम् GL_EXT_clip_cull_distance
#परिभाषय GL_EXT_clip_cull_distance 1
#परिभाषय GL_MAX_CLIP_DISTANCES_EXT         0x0D32
#परिभाषय GL_MAX_CULL_DISTANCES_EXT         0x82F9
#परिभाषय GL_MAX_COMBINED_CLIP_AND_CULL_DISTANCES_EXT 0x82FA
#परिभाषय GL_CLIP_DISTANCE0_EXT             0x3000
#परिभाषय GL_CLIP_DISTANCE1_EXT             0x3001
#परिभाषय GL_CLIP_DISTANCE2_EXT             0x3002
#परिभाषय GL_CLIP_DISTANCE3_EXT             0x3003
#परिभाषय GL_CLIP_DISTANCE4_EXT             0x3004
#परिभाषय GL_CLIP_DISTANCE5_EXT             0x3005
#परिभाषय GL_CLIP_DISTANCE6_EXT             0x3006
#परिभाषय GL_CLIP_DISTANCE7_EXT             0x3007
#यदि_अन्तः /* GL_EXT_clip_cull_distance */

#यदि_अपरिभाषितम् GL_EXT_color_बफर_float
#परिभाषय GL_EXT_color_बफर_float 1
#यदि_अन्तः /* GL_EXT_color_buffer_float */

#यदि_अपरिभाषितम् GL_EXT_color_बफर_half_float
#परिभाषय GL_EXT_color_बफर_half_float 1
#परिभाषय GL_RGBA16F_EXT                    0x881A
#परिभाषय GL_RGB16F_EXT                     0x881B
#परिभाषय GL_RG16F_EXT                      0x822F
#परिभाषय GL_R16F_EXT                       0x822D
#परिभाषय GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE_EXT 0x8211
#परिभाषय GL_UNSIGNED_NORMALIZED_EXT        0x8C17
#यदि_अन्तः /* GL_EXT_color_buffer_half_float */

#यदि_अपरिभाषितम् GL_EXT_conservative_गभीरता
#परिभाषय GL_EXT_conservative_गभीरता 1
#यदि_अन्तः /* GL_EXT_conservative_depth */

#यदि_अपरिभाषितम् GL_EXT_copy_image
#परिभाषय GL_EXT_copy_image 1
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCOPYIMAGESUBDATAEXTPROC) (GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei src_विस्तारः, GLsizei srcHeight, GLsizei src_गभीरता);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_Copy_Image_Sub_दत्त_EXT (GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei src_विस्तारः, GLsizei srcHeight, GLsizei src_गभीरता);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_copy_image */

#यदि_अपरिभाषितम् GL_EXT_debug_label
#परिभाषय GL_EXT_debug_label 1
#परिभाषय GL_क्रमादेशः_PIPELINE_OBJECT_EXT    0x8A4F
#परिभाषय GL_क्रमादेशः_OBJECT_EXT             0x8B40
#परिभाषय GL_SHADER_OBJECT_EXT              0x8B48
#परिभाषय GL_बफर_OBJECT_EXT              0x9151
#परिभाषय GL_QUERY_OBJECT_EXT               0x9153
#परिभाषय GL_VERTEX_ARRAY_OBJECT_EXT        0x9154
#परिभाषय GL_TRANSFORM_FEEDBACK             0x8E22
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLLABELOBJECTEXTPROC) (GLenum type, GLuint object, GLsizei दीर्घता, ध्रुव GLchar *label);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETOBJECTLABELEXTPROC) (GLenum type, GLuint object, GLsizei buf_आकार, GLsizei *दीर्घता, GLchar *label);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glLabelObjectEXT (GLenum type, GLuint object, GLsizei दीर्घता, ध्रुव GLchar *label);
GL_APICALL शून्य GL_APIENTRY glGetObjectLabelEXT (GLenum type, GLuint object, GLsizei buf_आकार, GLsizei *दीर्घता, GLchar *label);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_debug_label */

#यदि_अपरिभाषितम् GL_EXT_debug_marker
#परिभाषय GL_EXT_debug_marker 1
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLINSERTEVENTMARKEREXTPROC) (GLsizei दीर्घता, ध्रुव GLchar *marker);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPUSHGROUPMARKEREXTPROC) (GLsizei दीर्घता, ध्रुव GLchar *marker);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPOPGROUPMARKEREXTPROC) (शून्य);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_निवेशय_Event_Marker_EXT (GLsizei दीर्घता, ध्रुव GLchar *marker);
GL_APICALL शून्य GL_APIENTRY gl_प्रक्षिप_गणः_Marker_EXT (GLsizei दीर्घता, ध्रुव GLchar *marker);
GL_APICALL शून्य GL_APIENTRY gl_निष्कासय_गणः_Marker_EXT (शून्य);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_debug_marker */

#यदि_अपरिभाषितम् GL_EXT_गभीरता_clamp
#परिभाषय GL_EXT_गभीरता_clamp 1
#परिभाषय GL_गभीरता_CLAMP_EXT                0x864F
#यदि_अन्तः /* GL_EXT_depth_clamp */

#यदि_अपरिभाषितम् GL_EXT_discard_framebuffer
#परिभाषय GL_EXT_discard_framebuffer 1
#परिभाषय GL_COLOR_EXT                      0x1800
#परिभाषय GL_गभीरता_EXT                      0x1801
#परिभाषय GL_STENCIL_EXT                    0x1802
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDISCARDFRAMEBUFFEREXTPROC) (GLenum target, GLsizei अङ्कः_Attachments, ध्रुव GLenum *attachments);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glDiscardFramebufferEXT (GLenum target, GLsizei अङ्कः_Attachments, ध्रुव GLenum *attachments);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_discard_framebuffer */

#यदि_अपरिभाषितम् GL_EXT_disjoint_timer_query
#परिभाषय GL_EXT_disjoint_timer_query 1
#परिभाषय GL_QUERY_गणक_द्वयङ्काः_EXT         0x8864
#परिभाषय GL_CURRENT_QUERY_EXT              0x8865
#परिभाषय GL_QUERY_परिणाम_EXT               0x8866
#परिभाषय GL_QUERY_परिणाम_उपलब्धम्_EXT     0x8867
#परिभाषय GL_TIME_ELAPSED_EXT               0x88BF
#परिभाषय GL_TIMESTAMP_EXT                  0x8E28
#परिभाषय GL_GPU_DISJOINT_EXT               0x8FBB
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGENQUERIESEXTPROC) (GLsizei n, GLuint *ids);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDELETEQUERIESEXTPROC) (GLsizei n, ध्रुव GLuint *ids);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLISQUERYEXTPROC) (GLuint id);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBEGINQUERYEXTPROC) (GLenum target, GLuint id);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLENDQUERYEXTPROC) (GLenum target);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLQUERYCOUNTEREXTPROC) (GLuint id, GLenum target);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETQUERYIVEXTPROC) (GLenum target, GLenum pname, GLint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETQUERYOBJECTIVEXTPROC) (GLuint id, GLenum pname, GLint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETQUERYOBJECTUIVEXTPROC) (GLuint id, GLenum pname, GLuint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETQUERYOBJECTI64VEXTPROC) (GLuint id, GLenum pname, GLint64 *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETQUERYOBJECTUI64VEXTPROC) (GLuint id, GLenum pname, GLuint64 *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETINTEGER64VEXTPROC) (GLenum pname, GLint64 *दत्त);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glGenQueriesEXT (GLsizei n, GLuint *ids);
GL_APICALL शून्य GL_APIENTRY glDeleteQueriesEXT (GLsizei n, ध्रुव GLuint *ids);
GL_APICALL GLboolean GL_APIENTRY glIsQueryEXT (GLuint id);
GL_APICALL शून्य GL_APIENTRY glBeginQueryEXT (GLenum target, GLuint id);
GL_APICALL शून्य GL_APIENTRY gl_अन्तः_Query_EXT (GLenum target);
GL_APICALL शून्य GL_APIENTRY gl_Query_गणक_EXT (GLuint id, GLenum target);
GL_APICALL शून्य GL_APIENTRY glGetQueryivEXT (GLenum target, GLenum pname, GLint *params);
GL_APICALL शून्य GL_APIENTRY glGetQueryObjectivEXT (GLuint id, GLenum pname, GLint *params);
GL_APICALL शून्य GL_APIENTRY glGetQueryObjectuivEXT (GLuint id, GLenum pname, GLuint *params);
GL_APICALL शून्य GL_APIENTRY glGetQueryObjecti64vEXT (GLuint id, GLenum pname, GLint64 *params);
GL_APICALL शून्य GL_APIENTRY glGetQueryObjectui64vEXT (GLuint id, GLenum pname, GLuint64 *params);
GL_APICALL शून्य GL_APIENTRY glGetInteger64vEXT (GLenum pname, GLint64 *दत्त);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_disjoint_timer_query */

#यदि_अपरिभाषितम् GL_EXT_draw_buffers
#परिभाषय GL_EXT_draw_buffers 1
#परिभाषय GL_MAX_COLOR_ATTACHMENTS_EXT      0x8CDF
#परिभाषय GL_MAX_DRAW_BUFFERS_EXT           0x8824
#परिभाषय GL_DRAW_BUFFER0_EXT               0x8825
#परिभाषय GL_DRAW_BUFFER1_EXT               0x8826
#परिभाषय GL_DRAW_BUFFER2_EXT               0x8827
#परिभाषय GL_DRAW_BUFFER3_EXT               0x8828
#परिभाषय GL_DRAW_BUFFER4_EXT               0x8829
#परिभाषय GL_DRAW_BUFFER5_EXT               0x882A
#परिभाषय GL_DRAW_BUFFER6_EXT               0x882B
#परिभाषय GL_DRAW_BUFFER7_EXT               0x882C
#परिभाषय GL_DRAW_BUFFER8_EXT               0x882D
#परिभाषय GL_DRAW_BUFFER9_EXT               0x882E
#परिभाषय GL_DRAW_BUFFER10_EXT              0x882F
#परिभाषय GL_DRAW_BUFFER11_EXT              0x8830
#परिभाषय GL_DRAW_BUFFER12_EXT              0x8831
#परिभाषय GL_DRAW_BUFFER13_EXT              0x8832
#परिभाषय GL_DRAW_BUFFER14_EXT              0x8833
#परिभाषय GL_DRAW_BUFFER15_EXT              0x8834
#परिभाषय GL_COLOR_ATTACHMENT0_EXT          0x8CE0
#परिभाषय GL_COLOR_ATTACHMENT1_EXT          0x8CE1
#परिभाषय GL_COLOR_ATTACHMENT2_EXT          0x8CE2
#परिभाषय GL_COLOR_ATTACHMENT3_EXT          0x8CE3
#परिभाषय GL_COLOR_ATTACHMENT4_EXT          0x8CE4
#परिभाषय GL_COLOR_ATTACHMENT5_EXT          0x8CE5
#परिभाषय GL_COLOR_ATTACHMENT6_EXT          0x8CE6
#परिभाषय GL_COLOR_ATTACHMENT7_EXT          0x8CE7
#परिभाषय GL_COLOR_ATTACHMENT8_EXT          0x8CE8
#परिभाषय GL_COLOR_ATTACHMENT9_EXT          0x8CE9
#परिभाषय GL_COLOR_ATTACHMENT10_EXT         0x8CEA
#परिभाषय GL_COLOR_ATTACHMENT11_EXT         0x8CEB
#परिभाषय GL_COLOR_ATTACHMENT12_EXT         0x8CEC
#परिभाषय GL_COLOR_ATTACHMENT13_EXT         0x8CED
#परिभाषय GL_COLOR_ATTACHMENT14_EXT         0x8CEE
#परिभाषय GL_COLOR_ATTACHMENT15_EXT         0x8CEF
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWBUFFERSEXTPROC) (GLsizei n, ध्रुव GLenum *bufs);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glDrawBuffersEXT (GLsizei n, ध्रुव GLenum *bufs);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_draw_buffers */

#यदि_अपरिभाषितम् GL_EXT_draw_buffers_अनुक्रमितम्
#परिभाषय GL_EXT_draw_buffers_अनुक्रमितम् 1
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLENABLEIEXTPROC) (GLenum target, GLuint सूचकांक);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDISABLEIEXTPROC) (GLenum target, GLuint सूचकांक);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBLENDEQUATIONIEXTPROC) (GLuint buf, GLenum बहुलकम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEIEXTPROC) (GLuint buf, GLenum बहुलकम्_RGB, GLenum बहुलकम्_Alpha);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBLENDFUNCIEXTPROC) (GLuint buf, GLenum src, GLenum dst);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEIEXTPROC) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCOLORMASKIEXTPROC) (GLuint सूचकांक, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLISENABLEDIEXTPROC) (GLenum target, GLuint सूचकांक);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glEnableiEXT (GLenum target, GLuint सूचकांक);
GL_APICALL शून्य GL_APIENTRY glDisableiEXT (GLenum target, GLuint सूचकांक);
GL_APICALL शून्य GL_APIENTRY glBlendEquationiEXT (GLuint buf, GLenum बहुलकम्);
GL_APICALL शून्य GL_APIENTRY glBlendEquationSeparateiEXT (GLuint buf, GLenum बहुलकम्_RGB, GLenum बहुलकम्_Alpha);
GL_APICALL शून्य GL_APIENTRY glBlendFunciEXT (GLuint buf, GLenum src, GLenum dst);
GL_APICALL शून्य GL_APIENTRY glBlendFuncSeparateiEXT (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
GL_APICALL शून्य GL_APIENTRY glColorMaskiEXT (GLuint सूचकांक, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
GL_APICALL GLboolean GL_APIENTRY glIsEnablediEXT (GLenum target, GLuint सूचकांक);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_draw_buffers_indexed */

#यदि_अपरिभाषितम् GL_EXT_draw_elements_आधारः_vertex
#परिभाषय GL_EXT_draw_elements_आधारः_vertex 1
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWELEMENTSBASEVERTEXEXTPROC) (GLenum बहुलकम्, GLsizei गणनम्, GLenum type, ध्रुव शून्य *indices, GLint basevertex);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWRANGEELEMENTSBASEVERTEXEXTPROC) (GLenum बहुलकम्, GLuint start, GLuint अन्तः, GLsizei गणनम्, GLenum type, ध्रुव शून्य *indices, GLint basevertex);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXEXTPROC) (GLenum बहुलकम्, GLsizei गणनम्, GLenum type, ध्रुव शून्य *indices, GLsizei instancecount, GLint basevertex);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_Draw_Elements_आधारः_Vertex_EXT (GLenum बहुलकम्, GLsizei गणनम्, GLenum type, ध्रुव शून्य *indices, GLint basevertex);
GL_APICALL शून्य GL_APIENTRY gl_Draw_Range_Elements_आधारः_Vertex_EXT (GLenum बहुलकम्, GLuint start, GLuint अन्तः, GLsizei गणनम्, GLenum type, ध्रुव शून्य *indices, GLint basevertex);
GL_APICALL शून्य GL_APIENTRY gl_Draw_Elements_Instanced_आधारः_Vertex_EXT (GLenum बहुलकम्, GLsizei गणनम्, GLenum type, ध्रुव शून्य *indices, GLsizei instancecount, GLint basevertex);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_draw_elements_base_vertex */

#यदि_अपरिभाषितम् GL_EXT_draw_instanced
#परिभाषय GL_EXT_draw_instanced 1
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDEXTPROC) (GLenum बहुलकम्, GLint start, GLsizei गणनम्, GLsizei primcount);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDEXTPROC) (GLenum बहुलकम्, GLsizei गणनम्, GLenum type, ध्रुव शून्य *indices, GLsizei primcount);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glDrawArraysInstancedEXT (GLenum बहुलकम्, GLint start, GLsizei गणनम्, GLsizei primcount);
GL_APICALL शून्य GL_APIENTRY glDrawElementsInstancedEXT (GLenum बहुलकम्, GLsizei गणनम्, GLenum type, ध्रुव शून्य *indices, GLsizei primcount);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_draw_instanced */

#यदि_अपरिभाषितम् GL_EXT_draw_transform_feedback
#परिभाषय GL_EXT_draw_transform_feedback 1
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKEXTPROC) (GLenum बहुलकम्, GLuint id);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDEXTPROC) (GLenum बहुलकम्, GLuint id, GLsizei instancecount);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glDrawTransformFeedbackEXT (GLenum बहुलकम्, GLuint id);
GL_APICALL शून्य GL_APIENTRY glDrawTransformFeedbackInstancedEXT (GLenum बहुलकम्, GLuint id, GLsizei instancecount);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_draw_transform_feedback */

#यदि_अपरिभाषितम् GL_EXT_external_बफर
#परिभाषय GL_EXT_external_बफर 1
प्रकारनिर्देश शून्य *GLegl_Client_बफर_EXT;
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBUFFERSTORAGEEXTERNALEXTPROC) (GLenum target, GLintptr विस्थापनम्_2, GLsizeiptr आकार, GLegl_Client_बफर_EXT client_बफर, GLbitfield flags);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLNAMEDBUFFERSTORAGEEXTERNALEXTPROC) (GLuint बफर_2, GLintptr विस्थापनम्_2, GLsizeiptr आकार, GLegl_Client_बफर_EXT client_बफर, GLbitfield flags);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_बफर_Storage_External_EXT (GLenum target, GLintptr विस्थापनम्_2, GLsizeiptr आकार, GLegl_Client_बफर_EXT client_बफर, GLbitfield flags);
GL_APICALL शून्य GL_APIENTRY gl_Named_बफर_Storage_External_EXT (GLuint बफर_2, GLintptr विस्थापनम्_2, GLsizeiptr आकार, GLegl_Client_बफर_EXT client_बफर, GLbitfield flags);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_external_buffer */

#यदि_अपरिभाषितम् GL_EXT_float_blend
#परिभाषय GL_EXT_float_blend 1
#यदि_अन्तः /* GL_EXT_float_blend */

#यदि_अपरिभाषितम् GL_EXT_fragment_shading_दरः
#परिभाषय GL_EXT_fragment_shading_दरः 1
#परिभाषय GL_SHADING_दरः_1_X1_PIXELS_EXT    0x96A6
#परिभाषय GL_SHADING_दरः_1_X2_PIXELS_EXT    0x96A7
#परिभाषय GL_SHADING_दरः_2_X1_PIXELS_EXT    0x96A8
#परिभाषय GL_SHADING_दरः_2_X2_PIXELS_EXT    0x96A9
#परिभाषय GL_SHADING_दरः_1_X4_PIXELS_EXT    0x96AA
#परिभाषय GL_SHADING_दरः_4_X1_PIXELS_EXT    0x96AB
#परिभाषय GL_SHADING_दरः_4_X2_PIXELS_EXT    0x96AC
#परिभाषय GL_SHADING_दरः_2_X4_PIXELS_EXT    0x96AD
#परिभाषय GL_SHADING_दरः_4_X4_PIXELS_EXT    0x96AE
#परिभाषय GL_SHADING_दरः_EXT               0x96D0
#परिभाषय GL_SHADING_दरः_ATTACHMENT_EXT    0x96D1
#परिभाषय GL_FRAGMENT_SHADING_दरः_COMBINER_OP_KEEP_EXT 0x96D2
#परिभाषय GL_FRAGMENT_SHADING_दरः_COMBINER_OP_REPLACE_EXT 0x96D3
#परिभाषय GL_FRAGMENT_SHADING_दरः_COMBINER_OP_MIN_EXT 0x96D4
#परिभाषय GL_FRAGMENT_SHADING_दरः_COMBINER_OP_MAX_EXT 0x96D5
#परिभाषय GL_FRAGMENT_SHADING_दरः_COMBINER_OP_MUL_EXT 0x96D6
#परिभाषय GL_MIN_FRAGMENT_SHADING_दरः_ATTACHMENT_TEXEL_विस्तारः_EXT 0x96D7
#परिभाषय GL_MAX_FRAGMENT_SHADING_दरः_ATTACHMENT_TEXEL_विस्तारः_EXT 0x96D8
#परिभाषय GL_MIN_FRAGMENT_SHADING_दरः_ATTACHMENT_TEXEL_HEIGHT_EXT 0x96D9
#परिभाषय GL_MAX_FRAGMENT_SHADING_दरः_ATTACHMENT_TEXEL_HEIGHT_EXT 0x96DA
#परिभाषय GL_MAX_FRAGMENT_SHADING_दरः_ATTACHMENT_TEXEL_ASPECT_अनुपातः_EXT 0x96DB
#परिभाषय GL_MAX_FRAGMENT_SHADING_दरः_ATTACHMENT_LAYERS_EXT 0x96DC
#परिभाषय GL_FRAGMENT_SHADING_दरः_WITH_SHADER_गभीरता_STENCIL_WRITES_SUPPORTED_EXT 0x96DD
#परिभाषय GL_FRAGMENT_SHADING_दरः_WITH_SAMPLE_आवरणम्_SUPPORTED_EXT 0x96DE
#परिभाषय GL_FRAGMENT_SHADING_दरः_ATTACHMENT_WITH_DEFAULT_FRAMEBUFFER_SUPPORTED_EXT 0x96DF
#परिभाषय GL_FRAGMENT_SHADING_दरः_NON_TRIVIAL_COMBINERS_SUPPORTED_EXT 0x8F6F
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETFRAGMENTSHADINGRATESEXTPROC) (GLsizei samples, GLsizei max_गणनम्, GLsizei *गणनम्, GLenum *shadingRates);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSHADINGRATEEXTPROC) (GLenum दरः);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSHADINGRATECOMBINEROPSEXTPROC) (GLenum combinerOp0, GLenum combinerOp1);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFRAMEBUFFERSHADINGRATEEXTPROC) (GLenum target, GLenum attachment, GLuint texture, GLint आधारः_Layer, GLsizei अङ्कः_Layers, GLsizei texel_विस्तारः, GLsizei texelHeight);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glGetFragmentShadingRatesEXT (GLsizei samples, GLsizei max_गणनम्, GLsizei *गणनम्, GLenum *shadingRates);
GL_APICALL शून्य GL_APIENTRY gl_Shading_दरः_EXT (GLenum दरः);
GL_APICALL शून्य GL_APIENTRY gl_Shading_दरः_Combiner_Ops_EXT (GLenum combinerOp0, GLenum combinerOp1);
GL_APICALL शून्य GL_APIENTRY gl_Framebuffer_Shading_दरः_EXT (GLenum target, GLenum attachment, GLuint texture, GLint आधारः_Layer, GLsizei अङ्कः_Layers, GLsizei texel_विस्तारः, GLsizei texelHeight);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_fragment_shading_rate */

#यदि_अपरिभाषितम् GL_EXT_framebuffer_blit_layers
#परिभाषय GL_EXT_framebuffer_blit_layers 1
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBLITFRAMEBUFFERLAYERSEXTPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield आवरणम्, GLenum filter);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBLITFRAMEBUFFERLAYEREXTPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint srcLayer, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLint dstLayer, GLbitfield आवरणम्, GLenum filter);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glBlitFramebufferLayersEXT (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield आवरणम्, GLenum filter);
GL_APICALL शून्य GL_APIENTRY glBlitFramebufferLayerEXT (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint srcLayer, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLint dstLayer, GLbitfield आवरणम्, GLenum filter);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_framebuffer_blit_layers */

#यदि_अपरिभाषितम् GL_EXT_geometry_point_आकार
#परिभाषय GL_EXT_geometry_point_आकार 1
#यदि_अन्तः /* GL_EXT_geometry_point_size */

#यदि_अपरिभाषितम् GL_EXT_geometry_shader
#परिभाषय GL_EXT_geometry_shader 1
#परिभाषय GL_GEOMETRY_SHADER_EXT            0x8DD9
#परिभाषय GL_GEOMETRY_SHADER_BIT_EXT        0x00000004
#परिभाषय GL_GEOMETRY_LINKED_VERTICES_बहिर्गमनम्_EXT 0x8916
#परिभाषय GL_GEOMETRY_LINKED_निवेशः_TYPE_EXT 0x8917
#परिभाषय GL_GEOMETRY_LINKED_OUTPUT_TYPE_EXT 0x8918
#परिभाषय GL_GEOMETRY_SHADER_INVOCATIONS_EXT 0x887F
#परिभाषय GL_LAYER_PROVOKING_VERTEX_EXT     0x825E
#परिभाषय GL_पङ्क्तयः_ADJACENCY_EXT            0x000A
#परिभाषय GL_पङ्क्तिः_STRIP_ADJACENCY_EXT       0x000B
#परिभाषय GL_TRIANGLES_ADJACENCY_EXT        0x000C
#परिभाषय GL_TRIANGLE_STRIP_ADJACENCY_EXT   0x000D
#परिभाषय GL_MAX_GEOMETRY_एकरूपम्_COMPONENTS_EXT 0x8DDF
#परिभाषय GL_MAX_GEOMETRY_एकरूपम्_खण्डानि_EXT 0x8A2C
#परिभाषय GL_MAX_COMBINED_GEOMETRY_एकरूपम्_COMPONENTS_EXT 0x8A32
#परिभाषय GL_MAX_GEOMETRY_निवेशः_COMPONENTS_EXT 0x9123
#परिभाषय GL_MAX_GEOMETRY_OUTPUT_COMPONENTS_EXT 0x9124
#परिभाषय GL_MAX_GEOMETRY_OUTPUT_VERTICES_EXT 0x8DE0
#परिभाषय GL_MAX_GEOMETRY_योग_OUTPUT_COMPONENTS_EXT 0x8DE1
#परिभाषय GL_MAX_GEOMETRY_SHADER_INVOCATIONS_EXT 0x8E5A
#परिभाषय GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_EXT 0x8C29
#परिभाषय GL_MAX_GEOMETRY_ATOMIC_गणक_BUFFERS_EXT 0x92CF
#परिभाषय GL_MAX_GEOMETRY_ATOMIC_COUNTERS_EXT 0x92D5
#परिभाषय GL_MAX_GEOMETRY_IMAGE_UNIFORMS_EXT 0x90CD
#परिभाषय GL_MAX_GEOMETRY_SHADER_STORAGE_खण्डानि_EXT 0x90D7
#परिभाषय GL_FIRST_VERTEX_CONVENTION_EXT    0x8E4D
#परिभाषय GL_चरमः_VERTEX_CONVENTION_EXT     0x8E4E
#परिभाषय GL_UNDEFINED_VERTEX_EXT           0x8260
#परिभाषय GL_PRIMITIVES_GENERATED_EXT       0x8C87
#परिभाषय GL_FRAMEBUFFER_DEFAULT_LAYERS_EXT 0x9312
#परिभाषय GL_MAX_FRAMEBUFFER_LAYERS_EXT     0x9317
#परिभाषय GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_EXT 0x8DA8
#परिभाषय GL_FRAMEBUFFER_ATTACHMENT_LAYERED_EXT 0x8DA7
#परिभाषय GL_REFERENCED_BY_GEOMETRY_SHADER_EXT 0x9309
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREEXTPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glFramebufferTextureEXT (GLenum target, GLenum attachment, GLuint texture, GLint level);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_geometry_shader */

#यदि_अपरिभाषितम् GL_EXT_gpu_shader5
#परिभाषय GL_EXT_gpu_shader5 1
#यदि_अन्तः /* GL_EXT_gpu_shader5 */

#यदि_अपरिभाषितम् GL_EXT_instanced_arrays
#परिभाषय GL_EXT_instanced_arrays 1
#परिभाषय GL_VERTEX_ATTRIB_ARRAY_भाजकः_EXT 0x88FE
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLVERTEXATTRIBDIVISOREXTPROC) (GLuint सूचकांक, GLuint भाजकः);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_Vertex_Attrib_भाजकः_EXT (GLuint सूचकांक, GLuint भाजकः);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_instanced_arrays */

#यदि_अपरिभाषितम् GL_EXT_map_बफर_range
#परिभाषय GL_EXT_map_बफर_range 1
#परिभाषय GL_MAP_READ_BIT_EXT               0x0001
#परिभाषय GL_MAP_WRITE_BIT_EXT              0x0002
#परिभाषय GL_MAP_INVALIDATE_RANGE_BIT_EXT   0x0004
#परिभाषय GL_MAP_INVALIDATE_बफर_BIT_EXT  0x0008
#परिभाषय GL_MAP_FLUSH_EXPLICIT_BIT_EXT     0x0010
#परिभाषय GL_MAP_UNSYNCHRONIZED_BIT_EXT     0x0020
प्रकारनिर्देश शून्य *(GL_APIENTRYP PFNGLMAPBUFFERRANGEEXTPROC) (GLenum target, GLintptr विस्थापनम्_2, GLsizeiptr दीर्घता, GLbitfield access);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEEXTPROC) (GLenum target, GLintptr विस्थापनम्_2, GLsizeiptr दीर्घता);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य *GL_APIENTRY gl_Map_बफर_Range_EXT (GLenum target, GLintptr विस्थापनम्_2, GLsizeiptr दीर्घता, GLbitfield access);
GL_APICALL शून्य GL_APIENTRY gl_Flush_Mapped_बफर_Range_EXT (GLenum target, GLintptr विस्थापनम्_2, GLsizeiptr दीर्घता);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_map_buffer_range */

#यदि_अपरिभाषितम् GL_EXT_स्मृतिः_object
#परिभाषय GL_EXT_स्मृतिः_object 1
#परिभाषय GL_TEXTURE_TILING_EXT             0x9580
#परिभाषय GL_DEDICATED_स्मृतिः_OBJECT_EXT    0x9581
#परिभाषय GL_PROTECTED_स्मृतिः_OBJECT_EXT    0x959B
#परिभाषय GL_अङ्कः_TILING_TYPES_EXT           0x9582
#परिभाषय GL_TILING_TYPES_EXT               0x9583
#परिभाषय GL_OPTIMAL_TILING_EXT             0x9584
#परिभाषय GL_रैखिकम्_TILING_EXT              0x9585
#परिभाषय GL_अङ्कः_DEVICE_UUIDS_EXT           0x9596
#परिभाषय GL_DEVICE_UUID_EXT                0x9597
#परिभाषय GL_DRIVER_UUID_EXT                0x9598
#परिभाषय GL_UUID_आकार_EXT                  16
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETUNSIGNEDBYTEVEXTPROC) (GLenum pname, GLubyte *दत्त);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETUNSIGNEDBYTEI_VEXTPROC) (GLenum target, GLuint सूचकांक, GLubyte *दत्त);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDELETEMEMORYOBJECTSEXTPROC) (GLsizei n, ध्रुव GLuint *स्मृतिः_Objects);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLISMEMORYOBJECTEXTPROC) (GLuint स्मृतिः_Object);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCREATEMEMORYOBJECTSEXTPROC) (GLsizei n, GLuint *स्मृतिः_Objects);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMEMORYOBJECTPARAMETERIVEXTPROC) (GLuint स्मृतिः_Object, GLenum pname, ध्रुव GLint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETMEMORYOBJECTPARAMETERIVEXTPROC) (GLuint स्मृतिः_Object, GLenum pname, GLint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXSTORAGEMEM2DEXTPROC) (GLenum target, GLsizei स्तराः, GLenum आन्तरिकम्_Format, GLsizei विस्तारः, GLsizei height, GLuint स्मृतिः, GLuint64 विस्थापनम्_2);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXSTORAGEMEM2DMULTISAMPLEEXTPROC) (GLenum target, GLsizei samples, GLenum आन्तरिकम्_Format, GLsizei विस्तारः, GLsizei height, GLboolean fixedSampleLocations, GLuint स्मृतिः, GLuint64 विस्थापनम्_2);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXSTORAGEMEM3DEXTPROC) (GLenum target, GLsizei स्तराः, GLenum आन्तरिकम्_Format, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2, GLuint स्मृतिः, GLuint64 विस्थापनम्_2);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXSTORAGEMEM3DMULTISAMPLEEXTPROC) (GLenum target, GLsizei samples, GLenum आन्तरिकम्_Format, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2, GLboolean fixedSampleLocations, GLuint स्मृतिः, GLuint64 विस्थापनम्_2);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBUFFERSTORAGEMEMEXTPROC) (GLenum target, GLsizeiptr आकार, GLuint स्मृतिः, GLuint64 विस्थापनम्_2);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXTURESTORAGEMEM2DEXTPROC) (GLuint texture, GLsizei स्तराः, GLenum आन्तरिकम्_Format, GLsizei विस्तारः, GLsizei height, GLuint स्मृतिः, GLuint64 विस्थापनम्_2);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXTURESTORAGEMEM2DMULTISAMPLEEXTPROC) (GLuint texture, GLsizei samples, GLenum आन्तरिकम्_Format, GLsizei विस्तारः, GLsizei height, GLboolean fixedSampleLocations, GLuint स्मृतिः, GLuint64 विस्थापनम्_2);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXTURESTORAGEMEM3DEXTPROC) (GLuint texture, GLsizei स्तराः, GLenum आन्तरिकम्_Format, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2, GLuint स्मृतिः, GLuint64 विस्थापनम्_2);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXTURESTORAGEMEM3DMULTISAMPLEEXTPROC) (GLuint texture, GLsizei samples, GLenum आन्तरिकम्_Format, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2, GLboolean fixedSampleLocations, GLuint स्मृतिः, GLuint64 विस्थापनम्_2);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLNAMEDBUFFERSTORAGEMEMEXTPROC) (GLuint बफर_2, GLsizeiptr आकार, GLuint स्मृतिः, GLuint64 विस्थापनम्_2);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glGetUnsignedBytevEXT (GLenum pname, GLubyte *दत्त);
GL_APICALL शून्य GL_APIENTRY glGetUnsignedBytei_vEXT (GLenum target, GLuint सूचकांक, GLubyte *दत्त);
GL_APICALL शून्य GL_APIENTRY gl_Delete_स्मृतिः_Objects_EXT (GLsizei n, ध्रुव GLuint *स्मृतिः_Objects);
GL_APICALL GLboolean GL_APIENTRY gl_Is_स्मृतिः_Object_EXT (GLuint स्मृतिः_Object);
GL_APICALL शून्य GL_APIENTRY gl_Create_स्मृतिः_Objects_EXT (GLsizei n, GLuint *स्मृतिः_Objects);
GL_APICALL शून्य GL_APIENTRY gl_स्मृतिः_Object_Parameteriv_EXT (GLuint स्मृतिः_Object, GLenum pname, ध्रुव GLint *params);
GL_APICALL शून्य GL_APIENTRY gl_Get_स्मृतिः_Object_Parameteriv_EXT (GLuint स्मृतिः_Object, GLenum pname, GLint *params);
GL_APICALL शून्य GL_APIENTRY glTexStorageMem2DEXT (GLenum target, GLsizei स्तराः, GLenum आन्तरिकम्_Format, GLsizei विस्तारः, GLsizei height, GLuint स्मृतिः, GLuint64 विस्थापनम्_2);
GL_APICALL शून्य GL_APIENTRY glTexStorageMem2DMultisampleEXT (GLenum target, GLsizei samples, GLenum आन्तरिकम्_Format, GLsizei विस्तारः, GLsizei height, GLboolean fixedSampleLocations, GLuint स्मृतिः, GLuint64 विस्थापनम्_2);
GL_APICALL शून्य GL_APIENTRY glTexStorageMem3DEXT (GLenum target, GLsizei स्तराः, GLenum आन्तरिकम्_Format, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2, GLuint स्मृतिः, GLuint64 विस्थापनम्_2);
GL_APICALL शून्य GL_APIENTRY glTexStorageMem3DMultisampleEXT (GLenum target, GLsizei samples, GLenum आन्तरिकम्_Format, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2, GLboolean fixedSampleLocations, GLuint स्मृतिः, GLuint64 विस्थापनम्_2);
GL_APICALL शून्य GL_APIENTRY gl_बफर_Storage_Mem_EXT (GLenum target, GLsizeiptr आकार, GLuint स्मृतिः, GLuint64 विस्थापनम्_2);
GL_APICALL शून्य GL_APIENTRY glTextureStorageMem2DEXT (GLuint texture, GLsizei स्तराः, GLenum आन्तरिकम्_Format, GLsizei विस्तारः, GLsizei height, GLuint स्मृतिः, GLuint64 विस्थापनम्_2);
GL_APICALL शून्य GL_APIENTRY glTextureStorageMem2DMultisampleEXT (GLuint texture, GLsizei samples, GLenum आन्तरिकम्_Format, GLsizei विस्तारः, GLsizei height, GLboolean fixedSampleLocations, GLuint स्मृतिः, GLuint64 विस्थापनम्_2);
GL_APICALL शून्य GL_APIENTRY glTextureStorageMem3DEXT (GLuint texture, GLsizei स्तराः, GLenum आन्तरिकम्_Format, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2, GLuint स्मृतिः, GLuint64 विस्थापनम्_2);
GL_APICALL शून्य GL_APIENTRY glTextureStorageMem3DMultisampleEXT (GLuint texture, GLsizei samples, GLenum आन्तरिकम्_Format, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2, GLboolean fixedSampleLocations, GLuint स्मृतिः, GLuint64 विस्थापनम्_2);
GL_APICALL शून्य GL_APIENTRY gl_Named_बफर_Storage_Mem_EXT (GLuint बफर_2, GLsizeiptr आकार, GLuint स्मृतिः, GLuint64 विस्थापनम्_2);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_memory_object */

#यदि_अपरिभाषितम् GL_EXT_स्मृतिः_object_fd
#परिभाषय GL_EXT_स्मृतिः_object_fd 1
#परिभाषय GL_HANDLE_TYPE_OPAQUE_FD_EXT      0x9586
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLIMPORTMEMORYFDEXTPROC) (GLuint स्मृतिः, GLuint64 आकार, GLenum handleType, GLint fd);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_Import_स्मृतिः_Fd_EXT (GLuint स्मृतिः, GLuint64 आकार, GLenum handleType, GLint fd);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_memory_object_fd */

#यदि_अपरिभाषितम् GL_EXT_स्मृतिः_object_win32
#परिभाषय GL_EXT_स्मृतिः_object_win32 1
#परिभाषय GL_HANDLE_TYPE_OPAQUE_WIN32_EXT   0x9587
#परिभाषय GL_HANDLE_TYPE_OPAQUE_WIN32_KMT_EXT 0x9588
#परिभाषय GL_DEVICE_LUID_EXT                0x9599
#परिभाषय GL_DEVICE_ग्रन्थिः_आवरणम्_EXT           0x959A
#परिभाषय GL_LUID_आकार_EXT                  8
#परिभाषय GL_HANDLE_TYPE_D3D12_TILEPOOL_EXT 0x9589
#परिभाषय GL_HANDLE_TYPE_D3D12_RESOURCE_EXT 0x958A
#परिभाषय GL_HANDLE_TYPE_D3D11_IMAGE_EXT    0x958B
#परिभाषय GL_HANDLE_TYPE_D3D11_IMAGE_KMT_EXT 0x958C
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLIMPORTMEMORYWIN32HANDLEEXTPROC) (GLuint स्मृतिः, GLuint64 आकार, GLenum handleType, शून्य *handle);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLIMPORTMEMORYWIN32NAMEEXTPROC) (GLuint स्मृतिः, GLuint64 आकार, GLenum handleType, ध्रुव शून्य *name);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_Import_स्मृतिः_Win32_Handle_EXT (GLuint स्मृतिः, GLuint64 आकार, GLenum handleType, शून्य *handle);
GL_APICALL शून्य GL_APIENTRY gl_Import_स्मृतिः_Win32_Name_EXT (GLuint स्मृतिः, GLuint64 आकार, GLenum handleType, ध्रुव शून्य *name);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_memory_object_win32 */

#यदि_अपरिभाषितम् GL_EXT_mesh_shader
#परिभाषय GL_EXT_mesh_shader 1
#परिभाषय GL_MESH_SHADER_EXT                0x9559
#परिभाषय GL_TASK_SHADER_EXT                0x955A
#परिभाषय GL_MAX_MESH_एकरूपम्_खण्डानि_EXT    0x8E60
#परिभाषय GL_MAX_MESH_TEXTURE_IMAGE_UNITS_EXT 0x8E61
#परिभाषय GL_MAX_MESH_IMAGE_UNIFORMS_EXT    0x8E62
#परिभाषय GL_MAX_MESH_एकरूपम्_COMPONENTS_EXT 0x8E63
#परिभाषय GL_MAX_MESH_ATOMIC_गणक_BUFFERS_EXT 0x8E64
#परिभाषय GL_MAX_MESH_ATOMIC_COUNTERS_EXT   0x8E65
#परिभाषय GL_MAX_MESH_SHADER_STORAGE_खण्डानि_EXT 0x8E66
#परिभाषय GL_MAX_COMBINED_MESH_एकरूपम्_COMPONENTS_EXT 0x8E67
#परिभाषय GL_MAX_TASK_एकरूपम्_खण्डानि_EXT    0x8E68
#परिभाषय GL_MAX_TASK_TEXTURE_IMAGE_UNITS_EXT 0x8E69
#परिभाषय GL_MAX_TASK_IMAGE_UNIFORMS_EXT    0x8E6A
#परिभाषय GL_MAX_TASK_एकरूपम्_COMPONENTS_EXT 0x8E6B
#परिभाषय GL_MAX_TASK_ATOMIC_गणक_BUFFERS_EXT 0x8E6C
#परिभाषय GL_MAX_TASK_ATOMIC_COUNTERS_EXT   0x8E6D
#परिभाषय GL_MAX_TASK_SHADER_STORAGE_खण्डानि_EXT 0x8E6E
#परिभाषय GL_MAX_COMBINED_TASK_एकरूपम्_COMPONENTS_EXT 0x8E6F
#परिभाषय GL_MAX_TASK_WORK_गणः_योग_गणनम्_EXT 0x9740
#परिभाषय GL_MAX_MESH_WORK_गणः_योग_गणनम्_EXT 0x9741
#परिभाषय GL_MAX_MESH_WORK_गणः_INVOCATIONS_EXT 0x9757
#परिभाषय GL_MAX_TASK_WORK_गणः_INVOCATIONS_EXT 0x9759
#परिभाषय GL_MAX_TASK_PAYLOAD_आकार_EXT      0x9742
#परिभाषय GL_MAX_TASK_SHARED_स्मृतिः_आकार_EXT 0x9743
#परिभाषय GL_MAX_MESH_SHARED_स्मृतिः_आकार_EXT 0x9744
#परिभाषय GL_MAX_TASK_PAYLOAD_AND_SHARED_स्मृतिः_आकार_EXT 0x9745
#परिभाषय GL_MAX_MESH_PAYLOAD_AND_SHARED_स्मृतिः_आकार_EXT 0x9746
#परिभाषय GL_MAX_MESH_OUTPUT_स्मृतिः_आकार_EXT 0x9747
#परिभाषय GL_MAX_MESH_PAYLOAD_AND_OUTPUT_स्मृतिः_आकार_EXT 0x9748
#परिभाषय GL_MAX_MESH_OUTPUT_VERTICES_EXT   0x9538
#परिभाषय GL_MAX_MESH_OUTPUT_PRIMITIVES_EXT 0x9756
#परिभाषय GL_MAX_MESH_OUTPUT_COMPONENTS_EXT 0x9749
#परिभाषय GL_MAX_MESH_OUTPUT_LAYERS_EXT     0x974A
#परिभाषय GL_MAX_MESH_MULTIVIEW_VIEW_गणनम्_EXT 0x9557
#परिभाषय GL_MESH_OUTPUT_प्रत्येकम्_VERTEX_GRANULARITY_EXT 0x92DF
#परिभाषय GL_MESH_OUTPUT_प्रत्येकम्_PRIMITIVE_GRANULARITY_EXT 0x9543
#परिभाषय GL_MAX_PREFERRED_TASK_WORK_गणः_INVOCATIONS_EXT 0x974B
#परिभाषय GL_MAX_PREFERRED_MESH_WORK_गणः_INVOCATIONS_EXT 0x974C
#परिभाषय GL_MESH_PREFERS_LOCAL_INVOCATION_VERTEX_OUTPUT_EXT 0x974D
#परिभाषय GL_MESH_PREFERS_LOCAL_INVOCATION_PRIMITIVE_OUTPUT_EXT 0x974E
#परिभाषय GL_MESH_PREFERS_COMPACT_VERTEX_OUTPUT_EXT 0x974F
#परिभाषय GL_MESH_PREFERS_COMPACT_PRIMITIVE_OUTPUT_EXT 0x9750
#परिभाषय GL_MAX_TASK_WORK_गणः_गणनम्_EXT  0x9751
#परिभाषय GL_MAX_MESH_WORK_गणः_गणनम्_EXT  0x9752
#परिभाषय GL_MAX_MESH_WORK_गणः_आकार_EXT   0x9758
#परिभाषय GL_MAX_TASK_WORK_गणः_आकार_EXT   0x975A
#परिभाषय GL_MESH_WORK_गणः_आकार_EXT       0x953E
#परिभाषय GL_TASK_WORK_गणः_आकार_EXT       0x953F
#परिभाषय GL_MESH_VERTICES_बहिर्गमनम्_EXT          0x9579
#परिभाषय GL_MESH_PRIMITIVES_बहिर्गमनम्_EXT        0x957A
#परिभाषय GL_MESH_OUTPUT_TYPE_EXT           0x957B
#परिभाषय GL_एकरूपम्_खण्डम्_REFERENCED_BY_MESH_SHADER_EXT 0x959C
#परिभाषय GL_एकरूपम्_खण्डम्_REFERENCED_BY_TASK_SHADER_EXT 0x959D
#परिभाषय GL_REFERENCED_BY_MESH_SHADER_EXT  0x95A0
#परिभाषय GL_REFERENCED_BY_TASK_SHADER_EXT  0x95A1
#परिभाषय GL_TASK_SHADER_INVOCATIONS_EXT    0x9753
#परिभाषय GL_MESH_SHADER_INVOCATIONS_EXT    0x9754
#परिभाषय GL_MESH_PRIMITIVES_GENERATED_EXT  0x9755
#परिभाषय GL_MESH_SHADER_BIT_EXT            0x00000040
#परिभाषय GL_TASK_SHADER_BIT_EXT            0x00000080
#परिभाषय GL_MESH_SUBROUTINE_EXT            0x957C
#परिभाषय GL_TASK_SUBROUTINE_EXT            0x957D
#परिभाषय GL_MESH_SUBROUTINE_एकरूपम्_EXT    0x957E
#परिभाषय GL_TASK_SUBROUTINE_एकरूपम्_EXT    0x957F
#परिभाषय GL_ATOMIC_गणक_बफर_REFERENCED_BY_MESH_SHADER_EXT 0x959E
#परिभाषय GL_ATOMIC_गणक_बफर_REFERENCED_BY_TASK_SHADER_EXT 0x959F
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWMESHTASKSEXTPROC) (GLuint अङ्कः_groups_x, GLuint अङ्कः_groups_y, GLuint अङ्कः_groups_z);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWMESHTASKSINDIRECTEXTPROC) (GLintptr परोक्षम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMULTIDRAWMESHTASKSINDIRECTEXTPROC) (GLintptr परोक्षम्, GLsizei drawcount, GLsizei stride);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTEXTPROC) (GLintptr परोक्षम्, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glDrawMeshTasksEXT (GLuint अङ्कः_groups_x, GLuint अङ्कः_groups_y, GLuint अङ्कः_groups_z);
GL_APICALL शून्य GL_APIENTRY gl_Draw_Mesh_Tasks_परोक्षम्_EXT (GLintptr परोक्षम्);
GL_APICALL शून्य GL_APIENTRY gl_Multi_Draw_Mesh_Tasks_परोक्षम्_EXT (GLintptr परोक्षम्, GLsizei drawcount, GLsizei stride);
GL_APICALL शून्य GL_APIENTRY gl_Multi_Draw_Mesh_Tasks_परोक्षम्_गणनम्_EXT (GLintptr परोक्षम्, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_mesh_shader */

#यदि_अपरिभाषितम् GL_EXT_multi_draw_arrays
#परिभाषय GL_EXT_multi_draw_arrays 1
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMULTIDRAWARRAYSEXTPROC) (GLenum बहुलकम्, ध्रुव GLint *first, ध्रुव GLsizei *गणनम्, GLsizei primcount);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSEXTPROC) (GLenum बहुलकम्, ध्रुव GLsizei *गणनम्, GLenum type, ध्रुव शून्य *ध्रुव*indices, GLsizei primcount);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glMultiDrawArraysEXT (GLenum बहुलकम्, ध्रुव GLint *first, ध्रुव GLsizei *गणनम्, GLsizei primcount);
GL_APICALL शून्य GL_APIENTRY glMultiDrawElementsEXT (GLenum बहुलकम्, ध्रुव GLsizei *गणनम्, GLenum type, ध्रुव शून्य *ध्रुव*indices, GLsizei primcount);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_multi_draw_arrays */

#यदि_अपरिभाषितम् GL_EXT_multi_draw_परोक्षम्
#परिभाषय GL_EXT_multi_draw_परोक्षम् 1
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMULTIDRAWARRAYSINDIRECTEXTPROC) (GLenum बहुलकम्, ध्रुव शून्य *परोक्षम्, GLsizei drawcount, GLsizei stride);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSINDIRECTEXTPROC) (GLenum बहुलकम्, GLenum type, ध्रुव शून्य *परोक्षम्, GLsizei drawcount, GLsizei stride);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_Multi_Draw_Arrays_परोक्षम्_EXT (GLenum बहुलकम्, ध्रुव शून्य *परोक्षम्, GLsizei drawcount, GLsizei stride);
GL_APICALL शून्य GL_APIENTRY gl_Multi_Draw_Elements_परोक्षम्_EXT (GLenum बहुलकम्, GLenum type, ध्रुव शून्य *परोक्षम्, GLsizei drawcount, GLsizei stride);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_multi_draw_indirect */

#यदि_अपरिभाषितम् GL_EXT_multisampled_compatibility
#परिभाषय GL_EXT_multisampled_compatibility 1
#परिभाषय GL_MULTISAMPLE_EXT                0x809D
#परिभाषय GL_SAMPLE_ALPHA_गन्तव्यम्_ONE_EXT        0x809F
#यदि_अन्तः /* GL_EXT_multisampled_compatibility */

#यदि_अपरिभाषितम् GL_EXT_multisampled_render_गन्तव्यम्_texture
#परिभाषय GL_EXT_multisampled_render_गन्तव्यम्_texture 1
#परिभाषय GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SAMPLES_EXT 0x8D6C
#परिभाषय GL_RENDERBUFFER_SAMPLES_EXT       0x8CAB
#परिभाषय GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT 0x8D56
#परिभाषय GL_MAX_SAMPLES_EXT                0x8D57
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei विस्तारः, GLsizei height);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEEXTPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glRenderbufferStorageMultisampleEXT (GLenum target, GLsizei samples, GLenum internalformat, GLsizei विस्तारः, GLsizei height);
GL_APICALL शून्य GL_APIENTRY glFramebufferTexture2DMultisampleEXT (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_multisampled_render_to_texture */

#यदि_अपरिभाषितम् GL_EXT_multisampled_render_गन्तव्यम्_texture2
#परिभाषय GL_EXT_multisampled_render_गन्तव्यम्_texture2 1
#यदि_अन्तः /* GL_EXT_multisampled_render_to_texture2 */

#यदि_अपरिभाषितम् GL_EXT_multiview_draw_buffers
#परिभाषय GL_EXT_multiview_draw_buffers 1
#परिभाषय GL_COLOR_ATTACHMENT_EXT           0x90F0
#परिभाषय GL_MULTIVIEW_EXT                  0x90F1
#परिभाषय GL_DRAW_बफर_EXT                0x0C01
#परिभाषय GL_READ_बफर_EXT                0x0C02
#परिभाषय GL_MAX_MULTIVIEW_BUFFERS_EXT      0x90F2
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLREADBUFFERINDEXEDEXTPROC) (GLenum src, GLint सूचकांक);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWBUFFERSINDEXEDEXTPROC) (GLint n, ध्रुव GLenum *location, ध्रुव GLint *indices);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETINTEGERI_VEXTPROC) (GLenum target, GLuint सूचकांक, GLint *दत्त);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_Read_बफर_अनुक्रमितम्_EXT (GLenum src, GLint सूचकांक);
GL_APICALL शून्य GL_APIENTRY gl_Draw_Buffers_अनुक्रमितम्_EXT (GLint n, ध्रुव GLenum *location, ध्रुव GLint *indices);
GL_APICALL शून्य GL_APIENTRY glGetIntegeri_vEXT (GLenum target, GLuint सूचकांक, GLint *दत्त);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_multiview_draw_buffers */

#यदि_अपरिभाषितम् GL_EXT_multiview_tessellation_geometry_shader
#परिभाषय GL_EXT_multiview_tessellation_geometry_shader 1
#यदि_अन्तः /* GL_EXT_multiview_tessellation_geometry_shader */

#यदि_अपरिभाषितम् GL_EXT_multiview_texture_multisample
#परिभाषय GL_EXT_multiview_texture_multisample 1
#यदि_अन्तः /* GL_EXT_multiview_texture_multisample */

#यदि_अपरिभाषितम् GL_EXT_multiview_timer_query
#परिभाषय GL_EXT_multiview_timer_query 1
#यदि_अन्तः /* GL_EXT_multiview_timer_query */

#यदि_अपरिभाषितम् GL_EXT_occlusion_query_boolean
#परिभाषय GL_EXT_occlusion_query_boolean 1
#परिभाषय GL_ANY_SAMPLES_PASSED_EXT         0x8C2F
#परिभाषय GL_ANY_SAMPLES_PASSED_CONSERVATIVE_EXT 0x8D6A
#यदि_अन्तः /* GL_EXT_occlusion_query_boolean */

#यदि_अपरिभाषितम् GL_EXT_polygon_विस्थापनम्_clamp
#परिभाषय GL_EXT_polygon_विस्थापनम्_clamp 1
#परिभाषय GL_POLYGON_विस्थापनम्_CLAMP_EXT       0x8E1B
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPOLYGONOFFSETCLAMPEXTPROC) (GLfloat गुणकः, GLfloat units, GLfloat clamp);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_Polygon_विस्थापनम्_Clamp_EXT (GLfloat गुणकः, GLfloat units, GLfloat clamp);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_polygon_offset_clamp */

#यदि_अपरिभाषितम् GL_EXT_post_गभीरता_coverage
#परिभाषय GL_EXT_post_गभीरता_coverage 1
#यदि_अन्तः /* GL_EXT_post_depth_coverage */

#यदि_अपरिभाषितम् GL_EXT_primitive_bounding_box
#परिभाषय GL_EXT_primitive_bounding_box 1
#परिभाषय GL_PRIMITIVE_BOUNDING_BOX_EXT     0x92BE
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPRIMITIVEBOUNDINGBOXEXTPROC) (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glPrimitiveBoundingBoxEXT (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_primitive_bounding_box */

#यदि_अपरिभाषितम् GL_EXT_protected_textures
#परिभाषय GL_EXT_protected_textures 1
#परिभाषय GL_CONTEXT_FLAG_PROTECTED_CONTENT_BIT_EXT 0x00000010
#परिभाषय GL_TEXTURE_PROTECTED_EXT          0x8BFA
#यदि_अन्तः /* GL_EXT_protected_textures */

#यदि_अपरिभाषितम् GL_EXT_pvrtc_sRGB
#परिभाषय GL_EXT_pvrtc_sRGB 1
#परिभाषय GL_COMPRESSED_SRGB_PVRTC_2BPPV1_EXT 0x8A54
#परिभाषय GL_COMPRESSED_SRGB_PVRTC_4BPPV1_EXT 0x8A55
#परिभाषय GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV1_EXT 0x8A56
#परिभाषय GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV1_EXT 0x8A57
#परिभाषय GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV2_IMG 0x93F0
#परिभाषय GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV2_IMG 0x93F1
#यदि_अन्तः /* GL_EXT_pvrtc_sRGB */

#यदि_अपरिभाषितम् GL_EXT_raster_multisample
#परिभाषय GL_EXT_raster_multisample 1
#परिभाषय GL_RASTER_MULTISAMPLE_EXT         0x9327
#परिभाषय GL_RASTER_SAMPLES_EXT             0x9328
#परिभाषय GL_MAX_RASTER_SAMPLES_EXT         0x9329
#परिभाषय GL_RASTER_FIXED_SAMPLE_LOCATIONS_EXT 0x932A
#परिभाषय GL_MULTISAMPLE_RASTERIZATION_ALLOWED_EXT 0x932B
#परिभाषय GL_EFFECTIVE_RASTER_SAMPLES_EXT   0x932C
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLRASTERSAMPLESEXTPROC) (GLuint samples, GLboolean fixedsamplelocations);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glRasterSamplesEXT (GLuint samples, GLboolean fixedsamplelocations);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_raster_multisample */

#यदि_अपरिभाषितम् GL_EXT_read_format_bgra
#परिभाषय GL_EXT_read_format_bgra 1
#परिभाषय GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT 0x8365
#परिभाषय GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT 0x8366
#यदि_अन्तः /* GL_EXT_read_format_bgra */

#यदि_अपरिभाषितम् GL_EXT_render_snorm
#परिभाषय GL_EXT_render_snorm 1
#परिभाषय GL_R8_SNORM                       0x8F94
#परिभाषय GL_RG8_SNORM                      0x8F95
#परिभाषय GL_RGBA8_SNORM                    0x8F97
#परिभाषय GL_R16_SNORM_EXT                  0x8F98
#परिभाषय GL_RG16_SNORM_EXT                 0x8F99
#परिभाषय GL_RGBA16_SNORM_EXT               0x8F9B
#यदि_अन्तः /* GL_EXT_render_snorm */

#यदि_अपरिभाषितम् GL_EXT_robustness
#परिभाषय GL_EXT_robustness 1
#परिभाषय GL_GUILTY_CONTEXT_RESET_EXT       0x8253
#परिभाषय GL_INNOCENT_CONTEXT_RESET_EXT     0x8254
#परिभाषय GL_UNKNOWN_CONTEXT_RESET_EXT      0x8255
#परिभाषय GL_CONTEXT_ROBUST_ACCESS_EXT      0x90F3
#परिभाषय GL_RESET_NOTIFICATION_STRATEGY_EXT 0x8256
#परिभाषय GL_LOSE_CONTEXT_ON_RESET_EXT      0x8252
#परिभाषय GL_NO_RESET_NOTIFICATION_EXT      0x8261
प्रकारनिर्देश GLenum (GL_APIENTRYP PFNGLGETGRAPHICSRESETSTATUSEXTPROC) (शून्य);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLREADNPIXELSEXTPROC) (GLint x, GLint y, GLsizei विस्तारः, GLsizei height, GLenum format, GLenum type, GLsizei buf_आकार, शून्य *दत्त);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETNUNIFORMFVEXTPROC) (GLuint क्रमादेशः, GLint location, GLsizei buf_आकार, GLfloat *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETNUNIFORMIVEXTPROC) (GLuint क्रमादेशः, GLint location, GLsizei buf_आकार, GLint *params);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL GLenum GL_APIENTRY gl_Get_Graphics_Reset_स्थितिः_EXT (शून्य);
GL_APICALL शून्य GL_APIENTRY glReadnPixelsEXT (GLint x, GLint y, GLsizei विस्तारः, GLsizei height, GLenum format, GLenum type, GLsizei buf_आकार, शून्य *दत्त);
GL_APICALL शून्य GL_APIENTRY glGetnUniformfvEXT (GLuint क्रमादेशः, GLint location, GLsizei buf_आकार, GLfloat *params);
GL_APICALL शून्य GL_APIENTRY glGetnUniformivEXT (GLuint क्रमादेशः, GLint location, GLsizei buf_आकार, GLint *params);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_robustness */

#यदि_अपरिभाषितम् GL_EXT_sRGB
#परिभाषय GL_EXT_sRGB 1
#परिभाषय GL_SRGB_EXT                       0x8C40
#परिभाषय GL_SRGB_ALPHA_EXT                 0x8C42
#परिभाषय GL_SRGB8_ALPHA8_EXT               0x8C43
#परिभाषय GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING_EXT 0x8210
#यदि_अन्तः /* GL_EXT_sRGB */

#यदि_अपरिभाषितम् GL_EXT_sRGB_write_control
#परिभाषय GL_EXT_sRGB_write_control 1
#परिभाषय GL_FRAMEBUFFER_SRGB_EXT           0x8DB9
#यदि_अन्तः /* GL_EXT_sRGB_write_control */

#यदि_अपरिभाषितम् GL_EXT_semaphore
#परिभाषय GL_EXT_semaphore 1
#परिभाषय GL_LAYOUT_GENERAL_EXT             0x958D
#परिभाषय GL_LAYOUT_COLOR_ATTACHMENT_EXT    0x958E
#परिभाषय GL_LAYOUT_गभीरता_STENCIL_ATTACHMENT_EXT 0x958F
#परिभाषय GL_LAYOUT_गभीरता_STENCIL_READ_ONLY_EXT 0x9590
#परिभाषय GL_LAYOUT_SHADER_READ_ONLY_EXT    0x9591
#परिभाषय GL_LAYOUT_TRANSFER_SRC_EXT        0x9592
#परिभाषय GL_LAYOUT_TRANSFER_DST_EXT        0x9593
#परिभाषय GL_LAYOUT_गभीरता_READ_ONLY_STENCIL_ATTACHMENT_EXT 0x9530
#परिभाषय GL_LAYOUT_गभीरता_ATTACHMENT_STENCIL_READ_ONLY_EXT 0x9531
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGENSEMAPHORESEXTPROC) (GLsizei n, GLuint *semaphores);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDELETESEMAPHORESEXTPROC) (GLsizei n, ध्रुव GLuint *semaphores);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLISSEMAPHOREEXTPROC) (GLuint semaphore);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSEMAPHOREPARAMETERUI64VEXTPROC) (GLuint semaphore, GLenum pname, ध्रुव GLuint64 *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETSEMAPHOREPARAMETERUI64VEXTPROC) (GLuint semaphore, GLenum pname, GLuint64 *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLWAITSEMAPHOREEXTPROC) (GLuint semaphore, GLuint अङ्कः_बफर_Barriers, ध्रुव GLuint *buffers, GLuint अङ्कः_Texture_Barriers, ध्रुव GLuint *textures, ध्रुव GLenum *srcLayouts);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSIGNALSEMAPHOREEXTPROC) (GLuint semaphore, GLuint अङ्कः_बफर_Barriers, ध्रुव GLuint *buffers, GLuint अङ्कः_Texture_Barriers, ध्रुव GLuint *textures, ध्रुव GLenum *dstLayouts);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glGenSemaphoresEXT (GLsizei n, GLuint *semaphores);
GL_APICALL शून्य GL_APIENTRY glDeleteSemaphoresEXT (GLsizei n, ध्रुव GLuint *semaphores);
GL_APICALL GLboolean GL_APIENTRY glIsSemaphoreEXT (GLuint semaphore);
GL_APICALL शून्य GL_APIENTRY glSemaphoreParameterui64vEXT (GLuint semaphore, GLenum pname, ध्रुव GLuint64 *params);
GL_APICALL शून्य GL_APIENTRY glGetSemaphoreParameterui64vEXT (GLuint semaphore, GLenum pname, GLuint64 *params);
GL_APICALL शून्य GL_APIENTRY glWaitSemaphoreEXT (GLuint semaphore, GLuint अङ्कः_बफर_Barriers, ध्रुव GLuint *buffers, GLuint अङ्कः_Texture_Barriers, ध्रुव GLuint *textures, ध्रुव GLenum *srcLayouts);
GL_APICALL शून्य GL_APIENTRY glSignalSemaphoreEXT (GLuint semaphore, GLuint अङ्कः_बफर_Barriers, ध्रुव GLuint *buffers, GLuint अङ्कः_Texture_Barriers, ध्रुव GLuint *textures, ध्रुव GLenum *dstLayouts);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_semaphore */

#यदि_अपरिभाषितम् GL_EXT_semaphore_fd
#परिभाषय GL_EXT_semaphore_fd 1
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLIMPORTSEMAPHOREFDEXTPROC) (GLuint semaphore, GLenum handleType, GLint fd);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glImportSemaphoreFdEXT (GLuint semaphore, GLenum handleType, GLint fd);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_semaphore_fd */

#यदि_अपरिभाषितम् GL_EXT_semaphore_win32
#परिभाषय GL_EXT_semaphore_win32 1
#परिभाषय GL_HANDLE_TYPE_D3D12_FENCE_EXT    0x9594
#परिभाषय GL_D3_D12_FENCE_मानम्_EXT          0x9595
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLIMPORTSEMAPHOREWIN32HANDLEEXTPROC) (GLuint semaphore, GLenum handleType, शून्य *handle);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLIMPORTSEMAPHOREWIN32NAMEEXTPROC) (GLuint semaphore, GLenum handleType, ध्रुव शून्य *name);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glImportSemaphoreWin32HandleEXT (GLuint semaphore, GLenum handleType, शून्य *handle);
GL_APICALL शून्य GL_APIENTRY glImportSemaphoreWin32NameEXT (GLuint semaphore, GLenum handleType, ध्रुव शून्य *name);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_semaphore_win32 */

#यदि_अपरिभाषितम् GL_EXT_separate_गभीरता_stencil
#परिभाषय GL_EXT_separate_गभीरता_stencil 1
#यदि_अन्तः /* GL_EXT_separate_depth_stencil */

#यदि_अपरिभाषितम् GL_EXT_separate_shader_objects
#परिभाषय GL_EXT_separate_shader_objects 1
#परिभाषय GL_सक्रिय_क्रमादेशः_EXT             0x8259
#परिभाषय GL_VERTEX_SHADER_BIT_EXT          0x00000001
#परिभाषय GL_FRAGMENT_SHADER_BIT_EXT        0x00000002
#परिभाषय GL_ALL_SHADER_द्वयङ्काः_EXT            0xFFFFFFFF
#परिभाषय GL_क्रमादेशः_SEPARABLE_EXT          0x8258
#परिभाषय GL_क्रमादेशः_PIPELINE_BINDING_EXT   0x825A
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLACTIVESHADERPROGRAMEXTPROC) (GLuint pipeline, GLuint क्रमादेशः);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBINDPROGRAMPIPELINEEXTPROC) (GLuint pipeline);
प्रकारनिर्देश GLuint (GL_APIENTRYP PFNGLCREATESHADERPROGRAMVEXTPROC) (GLenum type, GLsizei गणनम्, ध्रुव GLchar *ध्रुव*वाक्यानि);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDELETEPROGRAMPIPELINESEXTPROC) (GLsizei n, ध्रुव GLuint *pipelines);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGENPROGRAMPIPELINESEXTPROC) (GLsizei n, GLuint *pipelines);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETPROGRAMPIPELINEINFOLOGEXTPROC) (GLuint pipeline, GLsizei buf_आकार, GLsizei *दीर्घता, GLchar *infoLog);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETPROGRAMPIPELINEIVEXTPROC) (GLuint pipeline, GLenum pname, GLint *params);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLISPROGRAMPIPELINEEXTPROC) (GLuint pipeline);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMPARAMETERIEXTPROC) (GLuint क्रमादेशः, GLenum pname, GLint मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM1FEXTPROC) (GLuint क्रमादेशः, GLint location, GLfloat v0);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM1FVEXTPROC) (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLfloat *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM1IEXTPROC) (GLuint क्रमादेशः, GLint location, GLint v0);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM1IVEXTPROC) (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLint *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM2FEXTPROC) (GLuint क्रमादेशः, GLint location, GLfloat v0, GLfloat v1);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM2FVEXTPROC) (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLfloat *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM2IEXTPROC) (GLuint क्रमादेशः, GLint location, GLint v0, GLint v1);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM2IVEXTPROC) (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLint *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM3FEXTPROC) (GLuint क्रमादेशः, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM3FVEXTPROC) (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLfloat *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM3IEXTPROC) (GLuint क्रमादेशः, GLint location, GLint v0, GLint v1, GLint v2);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM3IVEXTPROC) (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLint *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM4FEXTPROC) (GLuint क्रमादेशः, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM4FVEXTPROC) (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLfloat *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM4IEXTPROC) (GLuint क्रमादेशः, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM4IVEXTPROC) (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLint *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC) (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC) (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC) (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUSEPROGRAMSTAGESEXTPROC) (GLuint pipeline, GLbitfield stages, GLuint क्रमादेशः);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLVALIDATEPROGRAMPIPELINEEXTPROC) (GLuint pipeline);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UIEXTPROC) (GLuint क्रमादेशः, GLint location, GLuint v0);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UIEXTPROC) (GLuint क्रमादेशः, GLint location, GLuint v0, GLuint v1);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UIEXTPROC) (GLuint क्रमादेशः, GLint location, GLuint v0, GLuint v1, GLuint v2);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UIEXTPROC) (GLuint क्रमादेशः, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UIVEXTPROC) (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLuint *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UIVEXTPROC) (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLuint *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UIVEXTPROC) (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLuint *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UIVEXTPROC) (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLuint *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC) (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC) (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC) (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC) (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC) (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC) (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_सक्रिय_Shader_क्रमादेशः_EXT (GLuint pipeline, GLuint क्रमादेशः);
GL_APICALL शून्य GL_APIENTRY gl_Bind_क्रमादेशः_Pipeline_EXT (GLuint pipeline);
GL_APICALL GLuint GL_APIENTRY glCreateShaderProgramvEXT (GLenum type, GLsizei गणनम्, ध्रुव GLchar *ध्रुव*वाक्यानि);
GL_APICALL शून्य GL_APIENTRY gl_Delete_क्रमादेशः_Pipelines_EXT (GLsizei n, ध्रुव GLuint *pipelines);
GL_APICALL शून्य GL_APIENTRY gl_Gen_क्रमादेशः_Pipelines_EXT (GLsizei n, GLuint *pipelines);
GL_APICALL शून्य GL_APIENTRY gl_Get_क्रमादेशः_Pipeline_Info_Log_EXT (GLuint pipeline, GLsizei buf_आकार, GLsizei *दीर्घता, GLchar *infoLog);
GL_APICALL शून्य GL_APIENTRY gl_Get_क्रमादेशः_Pipelineiv_EXT (GLuint pipeline, GLenum pname, GLint *params);
GL_APICALL GLboolean GL_APIENTRY gl_Is_क्रमादेशः_Pipeline_EXT (GLuint pipeline);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Parameteri_EXT (GLuint क्रमादेशः, GLenum pname, GLint मानम्);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform1f_EXT (GLuint क्रमादेशः, GLint location, GLfloat v0);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform1fv_EXT (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLfloat *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform1i_EXT (GLuint क्रमादेशः, GLint location, GLint v0);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform1iv_EXT (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLint *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform2f_EXT (GLuint क्रमादेशः, GLint location, GLfloat v0, GLfloat v1);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform2fv_EXT (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLfloat *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform2i_EXT (GLuint क्रमादेशः, GLint location, GLint v0, GLint v1);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform2iv_EXT (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLint *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform3f_EXT (GLuint क्रमादेशः, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform3fv_EXT (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLfloat *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform3i_EXT (GLuint क्रमादेशः, GLint location, GLint v0, GLint v1, GLint v2);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform3iv_EXT (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLint *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform4f_EXT (GLuint क्रमादेशः, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform4fv_EXT (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLfloat *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform4i_EXT (GLuint क्रमादेशः, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform4iv_EXT (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLint *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_एकरूपम्_Matrix2fv_EXT (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_एकरूपम्_Matrix3fv_EXT (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_एकरूपम्_Matrix4fv_EXT (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_Use_क्रमादेशः_Stages_EXT (GLuint pipeline, GLbitfield stages, GLuint क्रमादेशः);
GL_APICALL शून्य GL_APIENTRY gl_Validate_क्रमादेशः_Pipeline_EXT (GLuint pipeline);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform1ui_EXT (GLuint क्रमादेशः, GLint location, GLuint v0);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform2ui_EXT (GLuint क्रमादेशः, GLint location, GLuint v0, GLuint v1);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform3ui_EXT (GLuint क्रमादेशः, GLint location, GLuint v0, GLuint v1, GLuint v2);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform4ui_EXT (GLuint क्रमादेशः, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform1uiv_EXT (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLuint *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform2uiv_EXT (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLuint *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform3uiv_EXT (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLuint *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform4uiv_EXT (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLuint *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_एकरूपम्_Matrix2x3fv_EXT (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_एकरूपम्_Matrix3x2fv_EXT (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_एकरूपम्_Matrix2x4fv_EXT (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_एकरूपम्_Matrix4x2fv_EXT (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_एकरूपम्_Matrix3x4fv_EXT (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_एकरूपम्_Matrix4x3fv_EXT (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_separate_shader_objects */

#यदि_अपरिभाषितम् GL_EXT_shader_framebuffer_fetch
#परिभाषय GL_EXT_shader_framebuffer_fetch 1
#परिभाषय GL_FRAGMENT_SHADER_DISCARDS_SAMPLES_EXT 0x8A52
#यदि_अन्तः /* GL_EXT_shader_framebuffer_fetch */

#यदि_अपरिभाषितम् GL_EXT_shader_framebuffer_fetch_non_coherent
#परिभाषय GL_EXT_shader_framebuffer_fetch_non_coherent 1
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFRAMEBUFFERFETCHBARRIEREXTPROC) (शून्य);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glFramebufferFetchBarrierEXT (शून्य);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_shader_framebuffer_fetch_non_coherent */

#यदि_अपरिभाषितम् GL_EXT_shader_गणः_vote
#परिभाषय GL_EXT_shader_गणः_vote 1
#यदि_अन्तः /* GL_EXT_shader_group_vote */

#यदि_अपरिभाषितम् GL_EXT_shader_implicit_conversions
#परिभाषय GL_EXT_shader_implicit_conversions 1
#यदि_अन्तः /* GL_EXT_shader_implicit_conversions */

#यदि_अपरिभाषितम् GL_EXT_shader_integer_mix
#परिभाषय GL_EXT_shader_integer_mix 1
#यदि_अन्तः /* GL_EXT_shader_integer_mix */

#यदि_अपरिभाषितम् GL_EXT_shader_io_खण्डानि
#परिभाषय GL_EXT_shader_io_खण्डानि 1
#यदि_अन्तः /* GL_EXT_shader_io_blocks */

#यदि_अपरिभाषितम् GL_EXT_shader_non_constant_global_initializers
#परिभाषय GL_EXT_shader_non_constant_global_initializers 1
#यदि_अन्तः /* GL_EXT_shader_non_constant_global_initializers */

#यदि_अपरिभाषितम् GL_EXT_shader_pixel_local_storage
#परिभाषय GL_EXT_shader_pixel_local_storage 1
#परिभाषय GL_MAX_SHADER_PIXEL_LOCAL_STORAGE_FAST_आकार_EXT 0x8F63
#परिभाषय GL_MAX_SHADER_PIXEL_LOCAL_STORAGE_आकार_EXT 0x8F67
#परिभाषय GL_SHADER_PIXEL_LOCAL_STORAGE_EXT 0x8F64
#यदि_अन्तः /* GL_EXT_shader_pixel_local_storage */

#यदि_अपरिभाषितम् GL_EXT_shader_pixel_local_storage2
#परिभाषय GL_EXT_shader_pixel_local_storage2 1
#परिभाषय GL_MAX_SHADER_COMBINED_LOCAL_STORAGE_FAST_आकार_EXT 0x9650
#परिभाषय GL_MAX_SHADER_COMBINED_LOCAL_STORAGE_आकार_EXT 0x9651
#परिभाषय GL_FRAMEBUFFER_INCOMPLETE_INSUFFICIENT_SHADER_COMBINED_LOCAL_STORAGE_EXT 0x9652
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFRAMEBUFFERPIXELLOCALSTORAGESIZEEXTPROC) (GLuint target, GLsizei आकार);
प्रकारनिर्देश GLsizei (GL_APIENTRYP PFNGLGETFRAMEBUFFERPIXELLOCALSTORAGESIZEEXTPROC) (GLuint target);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCLEARPIXELLOCALSTORAGEUIEXTPROC) (GLsizei विस्थापनम्_2, GLsizei n, ध्रुव GLuint *मानानि);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_Framebuffer_Pixel_Local_Storage_आकार_EXT (GLuint target, GLsizei आकार);
GL_APICALL GLsizei GL_APIENTRY gl_Get_Framebuffer_Pixel_Local_Storage_आकार_EXT (GLuint target);
GL_APICALL शून्य GL_APIENTRY glClearPixelLocalStorageuiEXT (GLsizei विस्थापनम्_2, GLsizei n, ध्रुव GLuint *मानानि);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_shader_pixel_local_storage2 */

#यदि_अपरिभाषितम् GL_EXT_shader_samples_identical
#परिभाषय GL_EXT_shader_samples_identical 1
#यदि_अन्तः /* GL_EXT_shader_samples_identical */

#यदि_अपरिभाषितम् GL_EXT_shader_texture_lod
#परिभाषय GL_EXT_shader_texture_lod 1
#यदि_अन्तः /* GL_EXT_shader_texture_lod */

#यदि_अपरिभाषितम् GL_EXT_shader_texture_samples
#परिभाषय GL_EXT_shader_texture_samples 1
#यदि_अन्तः /* GL_EXT_shader_texture_samples */

#यदि_अपरिभाषितम् GL_EXT_shadow_samplers
#परिभाषय GL_EXT_shadow_samplers 1
#परिभाषय GL_TEXTURE_COMPARE_बहुलकम्_EXT       0x884C
#परिभाषय GL_TEXTURE_COMPARE_FUNC_EXT       0x884D
#परिभाषय GL_COMPARE_REF_गन्तव्यम्_TEXTURE_EXT     0x884E
#परिभाषय GL_SAMPLER_2D_SHADOW_EXT          0x8B62
#यदि_अन्तः /* GL_EXT_shadow_samplers */

#यदि_अपरिभाषितम् GL_EXT_sparse_texture
#परिभाषय GL_EXT_sparse_texture 1
#परिभाषय GL_TEXTURE_SPARSE_EXT             0x91A6
#परिभाषय GL_VIRTUAL_PAGE_आकार_सूचकांक_EXT    0x91A7
#परिभाषय GL_अङ्कः_SPARSE_स्तराः_EXT          0x91AA
#परिभाषय GL_अङ्कः_VIRTUAL_PAGE_SIZES_EXT     0x91A8
#परिभाषय GL_VIRTUAL_PAGE_आकार_X_EXT        0x9195
#परिभाषय GL_VIRTUAL_PAGE_आकार_Y_EXT        0x9196
#परिभाषय GL_VIRTUAL_PAGE_आकार_Z_EXT        0x9197
#परिभाषय GL_TEXTURE_2D_ARRAY               0x8C1A
#परिभाषय GL_TEXTURE_3D                     0x806F
#परिभाषय GL_MAX_SPARSE_TEXTURE_आकार_EXT    0x9198
#परिभाषय GL_MAX_SPARSE_3_D_TEXTURE_आकार_EXT 0x9199
#परिभाषय GL_MAX_SPARSE_ARRAY_TEXTURE_LAYERS_EXT 0x919A
#परिभाषय GL_SPARSE_TEXTURE_पूर्णम्_ARRAY_CUBE_MIPMAPS_EXT 0x91A9
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXPAGECOMMITMENTEXTPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2, GLboolean commit);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glTexPageCommitmentEXT (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2, GLboolean commit);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_sparse_texture */

#यदि_अपरिभाषितम् GL_EXT_sparse_texture2
#परिभाषय GL_EXT_sparse_texture2 1
#यदि_अन्तः /* GL_EXT_sparse_texture2 */

#यदि_अपरिभाषितम् GL_EXT_tessellation_point_आकार
#परिभाषय GL_EXT_tessellation_point_आकार 1
#यदि_अन्तः /* GL_EXT_tessellation_point_size */

#यदि_अपरिभाषितम् GL_EXT_tessellation_shader
#परिभाषय GL_EXT_tessellation_shader 1
#परिभाषय GL_PATCHES_EXT                    0x000E
#परिभाषय GL_PATCH_VERTICES_EXT             0x8E72
#परिभाषय GL_TESS_CONTROL_OUTPUT_VERTICES_EXT 0x8E75
#परिभाषय GL_TESS_GEN_बहुलकम्_EXT              0x8E76
#परिभाषय GL_TESS_GEN_SPACING_EXT           0x8E77
#परिभाषय GL_TESS_GEN_VERTEX_क्रमः_EXT      0x8E78
#परिभाषय GL_TESS_GEN_POINT_बहुलकम्_EXT        0x8E79
#परिभाषय GL_ISOLINES_EXT                   0x8E7A
#परिभाषय GL_QUADS_EXT                      0x0007
#परिभाषय GL_FRACTIONAL_ODD_EXT             0x8E7B
#परिभाषय GL_FRACTIONAL_EVEN_EXT            0x8E7C
#परिभाषय GL_MAX_PATCH_VERTICES_EXT         0x8E7D
#परिभाषय GL_MAX_TESS_GEN_LEVEL_EXT         0x8E7E
#परिभाषय GL_MAX_TESS_CONTROL_एकरूपम्_COMPONENTS_EXT 0x8E7F
#परिभाषय GL_MAX_TESS_EVALUATION_एकरूपम्_COMPONENTS_EXT 0x8E80
#परिभाषय GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS_EXT 0x8E81
#परिभाषय GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS_EXT 0x8E82
#परिभाषय GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS_EXT 0x8E83
#परिभाषय GL_MAX_TESS_PATCH_COMPONENTS_EXT  0x8E84
#परिभाषय GL_MAX_TESS_CONTROL_योग_OUTPUT_COMPONENTS_EXT 0x8E85
#परिभाषय GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS_EXT 0x8E86
#परिभाषय GL_MAX_TESS_CONTROL_एकरूपम्_खण्डानि_EXT 0x8E89
#परिभाषय GL_MAX_TESS_EVALUATION_एकरूपम्_खण्डानि_EXT 0x8E8A
#परिभाषय GL_MAX_TESS_CONTROL_निवेशः_COMPONENTS_EXT 0x886C
#परिभाषय GL_MAX_TESS_EVALUATION_निवेशः_COMPONENTS_EXT 0x886D
#परिभाषय GL_MAX_COMBINED_TESS_CONTROL_एकरूपम्_COMPONENTS_EXT 0x8E1E
#परिभाषय GL_MAX_COMBINED_TESS_EVALUATION_एकरूपम्_COMPONENTS_EXT 0x8E1F
#परिभाषय GL_MAX_TESS_CONTROL_ATOMIC_गणक_BUFFERS_EXT 0x92CD
#परिभाषय GL_MAX_TESS_EVALUATION_ATOMIC_गणक_BUFFERS_EXT 0x92CE
#परिभाषय GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS_EXT 0x92D3
#परिभाषय GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS_EXT 0x92D4
#परिभाषय GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS_EXT 0x90CB
#परिभाषय GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS_EXT 0x90CC
#परिभाषय GL_MAX_TESS_CONTROL_SHADER_STORAGE_खण्डानि_EXT 0x90D8
#परिभाषय GL_MAX_TESS_EVALUATION_SHADER_STORAGE_खण्डानि_EXT 0x90D9
#परिभाषय GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED 0x8221
#परिभाषय GL_IS_प्रत्येकम्_PATCH_EXT               0x92E7
#परिभाषय GL_REFERENCED_BY_TESS_CONTROL_SHADER_EXT 0x9307
#परिभाषय GL_REFERENCED_BY_TESS_EVALUATION_SHADER_EXT 0x9308
#परिभाषय GL_TESS_CONTROL_SHADER_EXT        0x8E88
#परिभाषय GL_TESS_EVALUATION_SHADER_EXT     0x8E87
#परिभाषय GL_TESS_CONTROL_SHADER_BIT_EXT    0x00000008
#परिभाषय GL_TESS_EVALUATION_SHADER_BIT_EXT 0x00000010
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPATCHPARAMETERIEXTPROC) (GLenum pname, GLint मानम्);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glPatchParameteriEXT (GLenum pname, GLint मानम्);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_tessellation_shader */

#यदि_अपरिभाषितम् GL_EXT_texture_border_clamp
#परिभाषय GL_EXT_texture_border_clamp 1
#परिभाषय GL_TEXTURE_BORDER_COLOR_EXT       0x1004
#परिभाषय GL_CLAMP_गन्तव्यम्_BORDER_EXT            0x812D
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXPARAMETERIIVEXTPROC) (GLenum target, GLenum pname, ध्रुव GLint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXPARAMETERIUIVEXTPROC) (GLenum target, GLenum pname, ध्रुव GLuint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETTEXPARAMETERIIVEXTPROC) (GLenum target, GLenum pname, GLint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETTEXPARAMETERIUIVEXTPROC) (GLenum target, GLenum pname, GLuint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSAMPLERPARAMETERIIVEXTPROC) (GLuint sampler, GLenum pname, ध्रुव GLint *param);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSAMPLERPARAMETERIUIVEXTPROC) (GLuint sampler, GLenum pname, ध्रुव GLuint *param);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIIVEXTPROC) (GLuint sampler, GLenum pname, GLint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIUIVEXTPROC) (GLuint sampler, GLenum pname, GLuint *params);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glTexParameterIivEXT (GLenum target, GLenum pname, ध्रुव GLint *params);
GL_APICALL शून्य GL_APIENTRY glTexParameterIuivEXT (GLenum target, GLenum pname, ध्रुव GLuint *params);
GL_APICALL शून्य GL_APIENTRY glGetTexParameterIivEXT (GLenum target, GLenum pname, GLint *params);
GL_APICALL शून्य GL_APIENTRY glGetTexParameterIuivEXT (GLenum target, GLenum pname, GLuint *params);
GL_APICALL शून्य GL_APIENTRY glSamplerParameterIivEXT (GLuint sampler, GLenum pname, ध्रुव GLint *param);
GL_APICALL शून्य GL_APIENTRY glSamplerParameterIuivEXT (GLuint sampler, GLenum pname, ध्रुव GLuint *param);
GL_APICALL शून्य GL_APIENTRY glGetSamplerParameterIivEXT (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL शून्य GL_APIENTRY glGetSamplerParameterIuivEXT (GLuint sampler, GLenum pname, GLuint *params);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_texture_border_clamp */

#यदि_अपरिभाषितम् GL_EXT_texture_बफर
#परिभाषय GL_EXT_texture_बफर 1
#परिभाषय GL_TEXTURE_बफर_EXT             0x8C2A
#परिभाषय GL_TEXTURE_बफर_BINDING_EXT     0x8C2A
#परिभाषय GL_MAX_TEXTURE_बफर_आकार_EXT    0x8C2B
#परिभाषय GL_TEXTURE_BINDING_बफर_EXT     0x8C2C
#परिभाषय GL_TEXTURE_बफर_दत्त_STORE_BINDING_EXT 0x8C2D
#परिभाषय GL_TEXTURE_बफर_विस्थापनम्_ALIGNMENT_EXT 0x919F
#परिभाषय GL_SAMPLER_बफर_EXT             0x8DC2
#परिभाषय GL_INT_SAMPLER_बफर_EXT         0x8DD0
#परिभाषय GL_UNSIGNED_INT_SAMPLER_बफर_EXT 0x8DD8
#परिभाषय GL_IMAGE_बफर_EXT               0x9051
#परिभाषय GL_INT_IMAGE_बफर_EXT           0x905C
#परिभाषय GL_UNSIGNED_INT_IMAGE_बफर_EXT  0x9067
#परिभाषय GL_TEXTURE_बफर_विस्थापनम्_EXT      0x919D
#परिभाषय GL_TEXTURE_बफर_आकार_EXT        0x919E
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXBUFFEREXTPROC) (GLenum target, GLenum internalformat, GLuint बफर_2);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXBUFFERRANGEEXTPROC) (GLenum target, GLenum internalformat, GLuint बफर_2, GLintptr विस्थापनम्_2, GLsizeiptr आकार);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_Tex_बफर_EXT (GLenum target, GLenum internalformat, GLuint बफर_2);
GL_APICALL शून्य GL_APIENTRY gl_Tex_बफर_Range_EXT (GLenum target, GLenum internalformat, GLuint बफर_2, GLintptr विस्थापनम्_2, GLsizeiptr आकार);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_texture_buffer */

#यदि_अपरिभाषितम् GL_EXT_texture_compression_astc_decode_बहुलकम्
#परिभाषय GL_EXT_texture_compression_astc_decode_बहुलकम् 1
#परिभाषय GL_TEXTURE_ASTC_DECODE_PRECISION_EXT 0x8F69
#यदि_अन्तः /* GL_EXT_texture_compression_astc_decode_mode */

#यदि_अपरिभाषितम् GL_EXT_texture_compression_bptc
#परिभाषय GL_EXT_texture_compression_bptc 1
#परिभाषय GL_COMPRESSED_RGBA_BPTC_UNORM_EXT 0x8E8C
#परिभाषय GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_EXT 0x8E8D
#परिभाषय GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_EXT 0x8E8E
#परिभाषय GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_EXT 0x8E8F
#यदि_अन्तः /* GL_EXT_texture_compression_bptc */

#यदि_अपरिभाषितम् GL_EXT_texture_compression_dxt1
#परिभाषय GL_EXT_texture_compression_dxt1 1
#परिभाषय GL_COMPRESSED_RGB_S3TC_DXT1_EXT   0x83F0
#परिभाषय GL_COMPRESSED_RGBA_S3TC_DXT1_EXT  0x83F1
#यदि_अन्तः /* GL_EXT_texture_compression_dxt1 */

#यदि_अपरिभाषितम् GL_EXT_texture_compression_rgtc
#परिभाषय GL_EXT_texture_compression_rgtc 1
#परिभाषय GL_COMPRESSED_RED_RGTC1_EXT       0x8DBB
#परिभाषय GL_COMPRESSED_SIGNED_RED_RGTC1_EXT 0x8DBC
#परिभाषय GL_COMPRESSED_RED_GREEN_RGTC2_EXT 0x8DBD
#परिभाषय GL_COMPRESSED_SIGNED_RED_GREEN_RGTC2_EXT 0x8DBE
#यदि_अन्तः /* GL_EXT_texture_compression_rgtc */

#यदि_अपरिभाषितम् GL_EXT_texture_compression_s3tc
#परिभाषय GL_EXT_texture_compression_s3tc 1
#परिभाषय GL_COMPRESSED_RGBA_S3TC_DXT3_EXT  0x83F2
#परिभाषय GL_COMPRESSED_RGBA_S3TC_DXT5_EXT  0x83F3
#यदि_अन्तः /* GL_EXT_texture_compression_s3tc */

#यदि_अपरिभाषितम् GL_EXT_texture_compression_s3tc_srgb
#परिभाषय GL_EXT_texture_compression_s3tc_srgb 1
#परिभाषय GL_COMPRESSED_SRGB_S3TC_DXT1_EXT  0x8C4C
#परिभाषय GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT 0x8C4D
#परिभाषय GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT 0x8C4E
#परिभाषय GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT 0x8C4F
#यदि_अन्तः /* GL_EXT_texture_compression_s3tc_srgb */

#यदि_अपरिभाषितम् GL_EXT_texture_cube_map_array
#परिभाषय GL_EXT_texture_cube_map_array 1
#परिभाषय GL_TEXTURE_CUBE_MAP_ARRAY_EXT     0x9009
#परिभाषय GL_TEXTURE_BINDING_CUBE_MAP_ARRAY_EXT 0x900A
#परिभाषय GL_SAMPLER_CUBE_MAP_ARRAY_EXT     0x900C
#परिभाषय GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW_EXT 0x900D
#परिभाषय GL_INT_SAMPLER_CUBE_MAP_ARRAY_EXT 0x900E
#परिभाषय GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY_EXT 0x900F
#परिभाषय GL_IMAGE_CUBE_MAP_ARRAY_EXT       0x9054
#परिभाषय GL_INT_IMAGE_CUBE_MAP_ARRAY_EXT   0x905F
#परिभाषय GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY_EXT 0x906A
#यदि_अन्तः /* GL_EXT_texture_cube_map_array */

#यदि_अपरिभाषितम् GL_EXT_texture_filter_anisotropic
#परिभाषय GL_EXT_texture_filter_anisotropic 1
#परिभाषय GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#परिभाषय GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#यदि_अन्तः /* GL_EXT_texture_filter_anisotropic */

#यदि_अपरिभाषितम् GL_EXT_texture_filter_minmax
#परिभाषय GL_EXT_texture_filter_minmax 1
#परिभाषय GL_TEXTURE_REDUCTION_बहुलकम्_EXT     0x9366
#परिभाषय GL_WEIGHTED_मध्यमानम्_EXT           0x9367
#यदि_अन्तः /* GL_EXT_texture_filter_minmax */

#यदि_अपरिभाषितम् GL_EXT_texture_format_BGRA8888
#परिभाषय GL_EXT_texture_format_BGRA8888 1
#यदि_अन्तः /* GL_EXT_texture_format_BGRA8888 */

#यदि_अपरिभाषितम् GL_EXT_texture_format_sRGB_override
#परिभाषय GL_EXT_texture_format_sRGB_override 1
#परिभाषय GL_TEXTURE_FORMAT_SRGB_OVERRIDE_EXT 0x8FBF
#यदि_अन्तः /* GL_EXT_texture_format_sRGB_override */

#यदि_अपरिभाषितम् GL_EXT_texture_mirror_clamp_गन्तव्यम्_edge
#परिभाषय GL_EXT_texture_mirror_clamp_गन्तव्यम्_edge 1
#परिभाषय GL_MIRROR_CLAMP_गन्तव्यम्_EDGE_EXT       0x8743
#यदि_अन्तः /* GL_EXT_texture_mirror_clamp_to_edge */

#यदि_अपरिभाषितम् GL_EXT_texture_norm16
#परिभाषय GL_EXT_texture_norm16 1
#परिभाषय GL_R16_EXT                        0x822A
#परिभाषय GL_RG16_EXT                       0x822C
#परिभाषय GL_RGBA16_EXT                     0x805B
#परिभाषय GL_RGB16_EXT                      0x8054
#परिभाषय GL_RGB16_SNORM_EXT                0x8F9A
#यदि_अन्तः /* GL_EXT_texture_norm16 */

#यदि_अपरिभाषितम् GL_EXT_texture_query_lod
#परिभाषय GL_EXT_texture_query_lod 1
#यदि_अन्तः /* GL_EXT_texture_query_lod */

#यदि_अपरिभाषितम् GL_EXT_texture_rg
#परिभाषय GL_EXT_texture_rg 1
#परिभाषय GL_RED_EXT                        0x1903
#परिभाषय GL_RG_EXT                         0x8227
#परिभाषय GL_R8_EXT                         0x8229
#परिभाषय GL_RG8_EXT                        0x822B
#यदि_अन्तः /* GL_EXT_texture_rg */

#यदि_अपरिभाषितम् GL_EXT_texture_sRGB_R8
#परिभाषय GL_EXT_texture_sRGB_R8 1
#परिभाषय GL_SR8_EXT                        0x8FBD
#यदि_अन्तः /* GL_EXT_texture_sRGB_R8 */

#यदि_अपरिभाषितम् GL_EXT_texture_sRGB_RG8
#परिभाषय GL_EXT_texture_sRGB_RG8 1
#परिभाषय GL_SRG8_EXT                       0x8FBE
#यदि_अन्तः /* GL_EXT_texture_sRGB_RG8 */

#यदि_अपरिभाषितम् GL_EXT_texture_sRGB_decode
#परिभाषय GL_EXT_texture_sRGB_decode 1
#परिभाषय GL_TEXTURE_SRGB_DECODE_EXT        0x8A48
#परिभाषय GL_DECODE_EXT                     0x8A49
#परिभाषय GL_SKIP_DECODE_EXT                0x8A4A
#यदि_अन्तः /* GL_EXT_texture_sRGB_decode */

#यदि_अपरिभाषितम् GL_EXT_texture_shadow_lod
#परिभाषय GL_EXT_texture_shadow_lod 1
#यदि_अन्तः /* GL_EXT_texture_shadow_lod */

#यदि_अपरिभाषितम् GL_EXT_texture_storage
#परिभाषय GL_EXT_texture_storage 1
#परिभाषय GL_TEXTURE_IMMUTABLE_FORMAT_EXT   0x912F
#परिभाषय GL_ALPHA8_EXT                     0x803C
#परिभाषय GL_LUMINANCE8_EXT                 0x8040
#परिभाषय GL_LUMINANCE8_ALPHA8_EXT          0x8045
#परिभाषय GL_RGBA32F_EXT                    0x8814
#परिभाषय GL_RGB32F_EXT                     0x8815
#परिभाषय GL_ALPHA32F_EXT                   0x8816
#परिभाषय GL_LUMINANCE32F_EXT               0x8818
#परिभाषय GL_LUMINANCE_ALPHA32F_EXT         0x8819
#परिभाषय GL_ALPHA16F_EXT                   0x881C
#परिभाषय GL_LUMINANCE16F_EXT               0x881E
#परिभाषय GL_LUMINANCE_ALPHA16F_EXT         0x881F
#परिभाषय GL_R32F_EXT                       0x822E
#परिभाषय GL_RG32F_EXT                      0x8230
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXSTORAGE1DEXTPROC) (GLenum target, GLsizei स्तराः, GLenum internalformat, GLsizei विस्तारः);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXSTORAGE2DEXTPROC) (GLenum target, GLsizei स्तराः, GLenum internalformat, GLsizei विस्तारः, GLsizei height);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXSTORAGE3DEXTPROC) (GLenum target, GLsizei स्तराः, GLenum internalformat, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXTURESTORAGE1DEXTPROC) (GLuint texture, GLenum target, GLsizei स्तराः, GLenum internalformat, GLsizei विस्तारः);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXTURESTORAGE2DEXTPROC) (GLuint texture, GLenum target, GLsizei स्तराः, GLenum internalformat, GLsizei विस्तारः, GLsizei height);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXTURESTORAGE3DEXTPROC) (GLuint texture, GLenum target, GLsizei स्तराः, GLenum internalformat, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glTexStorage1DEXT (GLenum target, GLsizei स्तराः, GLenum internalformat, GLsizei विस्तारः);
GL_APICALL शून्य GL_APIENTRY glTexStorage2DEXT (GLenum target, GLsizei स्तराः, GLenum internalformat, GLsizei विस्तारः, GLsizei height);
GL_APICALL शून्य GL_APIENTRY glTexStorage3DEXT (GLenum target, GLsizei स्तराः, GLenum internalformat, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2);
GL_APICALL शून्य GL_APIENTRY glTextureStorage1DEXT (GLuint texture, GLenum target, GLsizei स्तराः, GLenum internalformat, GLsizei विस्तारः);
GL_APICALL शून्य GL_APIENTRY glTextureStorage2DEXT (GLuint texture, GLenum target, GLsizei स्तराः, GLenum internalformat, GLsizei विस्तारः, GLsizei height);
GL_APICALL शून्य GL_APIENTRY glTextureStorage3DEXT (GLuint texture, GLenum target, GLsizei स्तराः, GLenum internalformat, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_texture_storage */

#यदि_अपरिभाषितम् GL_EXT_texture_storage_compression
#परिभाषय GL_EXT_texture_storage_compression 1
#परिभाषय GL_अङ्कः_SURFACE_COMPRESSION_FIXED_RATES_EXT 0x8F6E
#परिभाषय GL_SURFACE_COMPRESSION_FIXED_दरः_1_BPC_EXT 0x96C4
#परिभाषय GL_SURFACE_COMPRESSION_FIXED_दरः_2_BPC_EXT 0x96C5
#परिभाषय GL_SURFACE_COMPRESSION_FIXED_दरः_3_BPC_EXT 0x96C6
#परिभाषय GL_SURFACE_COMPRESSION_FIXED_दरः_4_BPC_EXT 0x96C7
#परिभाषय GL_SURFACE_COMPRESSION_FIXED_दरः_5_BPC_EXT 0x96C8
#परिभाषय GL_SURFACE_COMPRESSION_FIXED_दरः_6_BPC_EXT 0x96C9
#परिभाषय GL_SURFACE_COMPRESSION_FIXED_दरः_7_BPC_EXT 0x96CA
#परिभाषय GL_SURFACE_COMPRESSION_FIXED_दरः_8_BPC_EXT 0x96CB
#परिभाषय GL_SURFACE_COMPRESSION_FIXED_दरः_9_BPC_EXT 0x96CC
#परिभाषय GL_SURFACE_COMPRESSION_FIXED_दरः_10_BPC_EXT 0x96CD
#परिभाषय GL_SURFACE_COMPRESSION_FIXED_दरः_11_BPC_EXT 0x96CE
#परिभाषय GL_SURFACE_COMPRESSION_FIXED_दरः_12_BPC_EXT 0x96CF
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXSTORAGEATTRIBS2DEXTPROC) (GLenum target, GLsizei स्तराः, GLenum internalformat, GLsizei विस्तारः, GLsizei height, ध्रुव GLint* attrib_list);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXSTORAGEATTRIBS3DEXTPROC) (GLenum target, GLsizei स्तराः, GLenum internalformat, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2, ध्रुव GLint* attrib_list);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glTexStorageAttribs2DEXT (GLenum target, GLsizei स्तराः, GLenum internalformat, GLsizei विस्तारः, GLsizei height, ध्रुव GLint* attrib_list);
GL_APICALL शून्य GL_APIENTRY glTexStorageAttribs3DEXT (GLenum target, GLsizei स्तराः, GLenum internalformat, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2, ध्रुव GLint* attrib_list);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_texture_storage_compression */

#यदि_अपरिभाषितम् GL_EXT_texture_type_2_10_10_10_REV
#परिभाषय GL_EXT_texture_type_2_10_10_10_REV 1
#परिभाषय GL_UNSIGNED_INT_2_10_10_10_REV_EXT 0x8368
#यदि_अन्तः /* GL_EXT_texture_type_2_10_10_10_REV */

#यदि_अपरिभाषितम् GL_EXT_texture_view
#परिभाषय GL_EXT_texture_view 1
#परिभाषय GL_TEXTURE_VIEW_MIN_LEVEL_EXT     0x82DB
#परिभाषय GL_TEXTURE_VIEW_अङ्कः_स्तराः_EXT    0x82DC
#परिभाषय GL_TEXTURE_VIEW_MIN_LAYER_EXT     0x82DD
#परिभाषय GL_TEXTURE_VIEW_अङ्कः_LAYERS_EXT    0x82DE
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXTUREVIEWEXTPROC) (GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glTextureViewEXT (GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_texture_view */

#यदि_अपरिभाषितम् GL_EXT_unpack_subimage
#परिभाषय GL_EXT_unpack_subimage 1
#परिभाषय GL_UNPACK_ROW_दीर्घता_EXT          0x0CF2
#परिभाषय GL_UNPACK_SKIP_पङ्क्तिकाः_EXT           0x0CF3
#परिभाषय GL_UNPACK_SKIP_PIXELS_EXT         0x0CF4
#यदि_अन्तः /* GL_EXT_unpack_subimage */

#यदि_अपरिभाषितम् GL_EXT_win32_keyed_mutex
#परिभाषय GL_EXT_win32_keyed_mutex 1
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLACQUIREKEYEDMUTEXWIN32EXTPROC) (GLuint स्मृतिः, GLuint64 कुञ्चिका, GLuint timeout);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLRELEASEKEYEDMUTEXWIN32EXTPROC) (GLuint स्मृतिः, GLuint64 कुञ्चिका);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL GLboolean GL_APIENTRY glAcquireKeyedMutexWin32EXT (GLuint स्मृतिः, GLuint64 कुञ्चिका, GLuint timeout);
GL_APICALL GLboolean GL_APIENTRY glReleaseKeyedMutexWin32EXT (GLuint स्मृतिः, GLuint64 कुञ्चिका);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_win32_keyed_mutex */

#यदि_अपरिभाषितम् GL_EXT_गवाक्षः_rectangles
#परिभाषय GL_EXT_गवाक्षः_rectangles 1
#परिभाषय GL_INCLUSIVE_EXT                  0x8F10
#परिभाषय GL_EXCLUSIVE_EXT                  0x8F11
#परिभाषय GL_गवाक्षः_RECTANGLE_EXT           0x8F12
#परिभाषय GL_गवाक्षः_RECTANGLE_बहुलकम्_EXT      0x8F13
#परिभाषय GL_MAX_गवाक्षः_RECTANGLES_EXT      0x8F14
#परिभाषय GL_अङ्कः_गवाक्षः_RECTANGLES_EXT      0x8F15
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLWINDOWRECTANGLESEXTPROC) (GLenum बहुलकम्, GLsizei गणनम्, ध्रुव GLint *box);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_गवाक्षः_Rectangles_EXT (GLenum बहुलकम्, GLsizei गणनम्, ध्रुव GLint *box);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_window_rectangles */

#यदि_अपरिभाषितम् GL_FJ_shader_द्विमान_GCCSO
#परिभाषय GL_FJ_shader_द्विमान_GCCSO 1
#परिभाषय GL_GCCSO_SHADER_द्विमान_FJ         0x9260
#यदि_अन्तः /* GL_FJ_shader_binary_GCCSO */

#यदि_अपरिभाषितम् GL_HUAWEI_क्रमादेशः_द्विमान
#परिभाषय GL_HUAWEI_क्रमादेशः_द्विमान 1
#परिभाषय GL_क्रमादेशः_द्विमान_HUAWEI          0x9771
#यदि_अन्तः /* GL_HUAWEI_program_binary */

#यदि_अपरिभाषितम् GL_HUAWEI_shader_द्विमान
#परिभाषय GL_HUAWEI_shader_द्विमान 1
#परिभाषय GL_SHADER_द्विमान_HUAWEI           0x9770
#यदि_अन्तः /* GL_HUAWEI_shader_binary */

#यदि_अपरिभाषितम् GL_IMG_bindless_texture
#परिभाषय GL_IMG_bindless_texture 1
प्रकारनिर्देश GLuint64 (GL_APIENTRYP PFNGLGETTEXTUREHANDLEIMGPROC) (GLuint texture);
प्रकारनिर्देश GLuint64 (GL_APIENTRYP PFNGLGETTEXTURESAMPLERHANDLEIMGPROC) (GLuint texture, GLuint sampler);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORMHANDLEUI64IMGPROC) (GLint location, GLuint64 मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORMHANDLEUI64VIMGPROC) (GLint location, GLsizei गणनम्, ध्रुव GLuint64 *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64IMGPROC) (GLuint क्रमादेशः, GLint location, GLuint64 मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64VIMGPROC) (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLuint64 *मानानि);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL GLuint64 GL_APIENTRY glGetTextureHandleIMG (GLuint texture);
GL_APICALL GLuint64 GL_APIENTRY glGetTextureSamplerHandleIMG (GLuint texture, GLuint sampler);
GL_APICALL शून्य GL_APIENTRY gl_एकरूपम्_Handleui64_IMG (GLint location, GLuint64 मानम्);
GL_APICALL शून्य GL_APIENTRY gl_एकरूपम्_Handleui64v_IMG (GLint location, GLsizei गणनम्, ध्रुव GLuint64 *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_एकरूपम्_Handleui64_IMG (GLuint क्रमादेशः, GLint location, GLuint64 मानम्);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_एकरूपम्_Handleui64v_IMG (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLuint64 *मानानि);
#यदि_अन्तः
#यदि_अन्तः /* GL_IMG_bindless_texture */

#यदि_अपरिभाषितम् GL_IMG_framebuffer_downsample
#परिभाषय GL_IMG_framebuffer_downsample 1
#परिभाषय GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_AND_DOWNSAMPLE_IMG 0x913C
#परिभाषय GL_अङ्कः_DOWNSAMPLE_SCALES_IMG      0x913D
#परिभाषय GL_DOWNSAMPLE_SCALES_IMG          0x913E
#परिभाषय GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SCALE_IMG 0x913F
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DDOWNSAMPLEIMGPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint xscale, GLint yscale);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURELAYERDOWNSAMPLEIMGPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer, GLint xscale, GLint yscale);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glFramebufferTexture2DDownsampleIMG (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint xscale, GLint yscale);
GL_APICALL शून्य GL_APIENTRY glFramebufferTextureLayerDownsampleIMG (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer, GLint xscale, GLint yscale);
#यदि_अन्तः
#यदि_अन्तः /* GL_IMG_framebuffer_downsample */

#यदि_अपरिभाषितम् GL_IMG_multisampled_render_गन्तव्यम्_texture
#परिभाषय GL_IMG_multisampled_render_गन्तव्यम्_texture 1
#परिभाषय GL_RENDERBUFFER_SAMPLES_IMG       0x9133
#परिभाषय GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_IMG 0x9134
#परिभाषय GL_MAX_SAMPLES_IMG                0x9135
#परिभाषय GL_TEXTURE_SAMPLES_IMG            0x9136
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEIMGPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei विस्तारः, GLsizei height);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEIMGPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glRenderbufferStorageMultisampleIMG (GLenum target, GLsizei samples, GLenum internalformat, GLsizei विस्तारः, GLsizei height);
GL_APICALL शून्य GL_APIENTRY glFramebufferTexture2DMultisampleIMG (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#यदि_अन्तः
#यदि_अन्तः /* GL_IMG_multisampled_render_to_texture */

#यदि_अपरिभाषितम् GL_IMG_क्रमादेशः_द्विमान
#परिभाषय GL_IMG_क्रमादेशः_द्विमान 1
#परिभाषय GL_SGX_क्रमादेशः_द्विमान_IMG         0x9130
#यदि_अन्तः /* GL_IMG_program_binary */

#यदि_अपरिभाषितम् GL_IMG_read_format
#परिभाषय GL_IMG_read_format 1
#परिभाषय GL_BGRA_IMG                       0x80E1
#परिभाषय GL_UNSIGNED_SHORT_4_4_4_4_REV_IMG 0x8365
#यदि_अन्तः /* GL_IMG_read_format */

#यदि_अपरिभाषितम् GL_IMG_shader_द्विमान
#परिभाषय GL_IMG_shader_द्विमान 1
#परिभाषय GL_SGX_द्विमान_IMG                 0x8C0A
#यदि_अन्तः /* GL_IMG_shader_binary */

#यदि_अपरिभाषितम् GL_IMG_texture_compression_pvrtc
#परिभाषय GL_IMG_texture_compression_pvrtc 1
#परिभाषय GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG 0x8C00
#परिभाषय GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG 0x8C01
#परिभाषय GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG 0x8C02
#परिभाषय GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG 0x8C03
#यदि_अन्तः /* GL_IMG_texture_compression_pvrtc */

#यदि_अपरिभाषितम् GL_IMG_texture_compression_pvrtc2
#परिभाषय GL_IMG_texture_compression_pvrtc2 1
#परिभाषय GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG 0x9137
#परिभाषय GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG 0x9138
#यदि_अन्तः /* GL_IMG_texture_compression_pvrtc2 */

#यदि_अपरिभाषितम् GL_IMG_texture_filter_cubic
#परिभाषय GL_IMG_texture_filter_cubic 1
#परिभाषय GL_CUBIC_IMG                      0x9139
#परिभाषय GL_CUBIC_MIPMAP_निकटतमः_IMG       0x913A
#परिभाषय GL_CUBIC_MIPMAP_रैखिकम्_IMG        0x913B
#यदि_अन्तः /* GL_IMG_texture_filter_cubic */

#यदि_अपरिभाषितम् GL_INTEL_blackhole_render
#परिभाषय GL_INTEL_blackhole_render 1
#परिभाषय GL_BLACKHOLE_RENDER_INTEL         0x83FC
#यदि_अन्तः /* GL_INTEL_blackhole_render */

#यदि_अपरिभाषितम् GL_INTEL_conservative_rasterization
#परिभाषय GL_INTEL_conservative_rasterization 1
#परिभाषय GL_CONSERVATIVE_RASTERIZATION_INTEL 0x83FE
#यदि_अन्तः /* GL_INTEL_conservative_rasterization */

#यदि_अपरिभाषितम् GL_INTEL_framebuffer_CMAA
#परिभाषय GL_INTEL_framebuffer_CMAA 1
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLAPPLYFRAMEBUFFERATTACHMENTCMAAINTELPROC) (शून्य);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glApplyFramebufferAttachmentCMAAINTEL (शून्य);
#यदि_अन्तः
#यदि_अन्तः /* GL_INTEL_framebuffer_CMAA */

#यदि_अपरिभाषितम् GL_INTEL_performance_query
#परिभाषय GL_INTEL_performance_query 1
#परिभाषय GL_PERFQUERY_SINGLE_CONTEXT_INTEL 0x00000000
#परिभाषय GL_PERFQUERY_GLOBAL_CONTEXT_INTEL 0x00000001
#परिभाषय GL_PERFQUERY_WAIT_INTEL           0x83FB
#परिभाषय GL_PERFQUERY_FLUSH_INTEL          0x83FA
#परिभाषय GL_PERFQUERY_DONOT_FLUSH_INTEL    0x83F9
#परिभाषय GL_PERFQUERY_गणक_EVENT_INTEL  0x94F0
#परिभाषय GL_PERFQUERY_गणक_DURATION_NORM_INTEL 0x94F1
#परिभाषय GL_PERFQUERY_गणक_DURATION_RAW_INTEL 0x94F2
#परिभाषय GL_PERFQUERY_गणक_THROUGHPUT_INTEL 0x94F3
#परिभाषय GL_PERFQUERY_गणक_RAW_INTEL    0x94F4
#परिभाषय GL_PERFQUERY_गणक_TIMESTAMP_INTEL 0x94F5
#परिभाषय GL_PERFQUERY_गणक_दत्त_UINT32_INTEL 0x94F8
#परिभाषय GL_PERFQUERY_गणक_दत्त_UINT64_INTEL 0x94F9
#परिभाषय GL_PERFQUERY_गणक_दत्त_FLOAT_INTEL 0x94FA
#परिभाषय GL_PERFQUERY_गणक_दत्त_DOUBLE_INTEL 0x94FB
#परिभाषय GL_PERFQUERY_गणक_दत्त_BOOL32_INTEL 0x94FC
#परिभाषय GL_PERFQUERY_QUERY_NAME_दीर्घता_MAX_INTEL 0x94FD
#परिभाषय GL_PERFQUERY_गणक_NAME_दीर्घता_MAX_INTEL 0x94FE
#परिभाषय GL_PERFQUERY_गणक_DESC_दीर्घता_MAX_INTEL 0x94FF
#परिभाषय GL_PERFQUERY_GPA_EXTENDED_COUNTERS_INTEL 0x9500
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBEGINPERFQUERYINTELPROC) (GLuint queryHandle);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCREATEPERFQUERYINTELPROC) (GLuint queryId, GLuint *queryHandle);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDELETEPERFQUERYINTELPROC) (GLuint queryHandle);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLENDPERFQUERYINTELPROC) (GLuint queryHandle);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETFIRSTPERFQUERYIDINTELPROC) (GLuint *queryId);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETNEXTPERFQUERYIDINTELPROC) (GLuint queryId, GLuint *अग्र_Query_Id);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETPERFCOUNTERINFOINTELPROC) (GLuint queryId, GLuint गणक_Id, GLuint गणक_Name_दीर्घता, GLchar *गणक_Name, GLuint गणक_Desc_दीर्घता, GLchar *गणक_Desc, GLuint *गणक_विस्थापनम्, GLuint *गणक_दत्त_आकार, GLuint *गणक_Type_Enum, GLuint *गणक_दत्त_Type_Enum, GLuint64 *raw_गणक_Max_मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETPERFQUERYDATAINTELPROC) (GLuint queryHandle, GLuint flags, GLsizei दत्त_आकार_2, शून्य *दत्त, GLuint *अष्टकानि_Written);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETPERFQUERYIDBYNAMEINTELPROC) (GLchar *queryName, GLuint *queryId);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETPERFQUERYINFOINTELPROC) (GLuint queryId, GLuint query_Name_दीर्घता, GLchar *queryName, GLuint *दत्त_आकार_2, GLuint *noCounters, GLuint *noInstances, GLuint *caps_आवरणम्);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glBeginPerfQueryINTEL (GLuint queryHandle);
GL_APICALL शून्य GL_APIENTRY glCreatePerfQueryINTEL (GLuint queryId, GLuint *queryHandle);
GL_APICALL शून्य GL_APIENTRY glDeletePerfQueryINTEL (GLuint queryHandle);
GL_APICALL शून्य GL_APIENTRY gl_अन्तः_Perf_Query_INTEL (GLuint queryHandle);
GL_APICALL शून्य GL_APIENTRY glGetFirstPerfQueryIdINTEL (GLuint *queryId);
GL_APICALL शून्य GL_APIENTRY gl_Get_अग्र_Perf_Query_Id_INTEL (GLuint queryId, GLuint *अग्र_Query_Id);
GL_APICALL शून्य GL_APIENTRY gl_Get_Perf_गणक_Info_INTEL (GLuint queryId, GLuint गणक_Id, GLuint गणक_Name_दीर्घता, GLchar *गणक_Name, GLuint गणक_Desc_दीर्घता, GLchar *गणक_Desc, GLuint *गणक_विस्थापनम्, GLuint *गणक_दत्त_आकार, GLuint *गणक_Type_Enum, GLuint *गणक_दत्त_Type_Enum, GLuint64 *raw_गणक_Max_मानम्);
GL_APICALL शून्य GL_APIENTRY gl_Get_Perf_Query_दत्त_INTEL (GLuint queryHandle, GLuint flags, GLsizei दत्त_आकार_2, शून्य *दत्त, GLuint *अष्टकानि_Written);
GL_APICALL शून्य GL_APIENTRY glGetPerfQueryIdByNameINTEL (GLchar *queryName, GLuint *queryId);
GL_APICALL शून्य GL_APIENTRY glGetPerfQueryInfoINTEL (GLuint queryId, GLuint query_Name_दीर्घता, GLchar *queryName, GLuint *दत्त_आकार_2, GLuint *noCounters, GLuint *noInstances, GLuint *caps_आवरणम्);
#यदि_अन्तः
#यदि_अन्तः /* GL_INTEL_performance_query */

#यदि_अपरिभाषितम् GL_MESA_bgra
#परिभाषय GL_MESA_bgra 1
#परिभाषय GL_BGR_EXT                        0x80E0
#यदि_अन्तः /* GL_MESA_bgra */

#यदि_अपरिभाषितम् GL_MESA_framebuffer_flip_x
#परिभाषय GL_MESA_framebuffer_flip_x 1
#परिभाषय GL_FRAMEBUFFER_FLIP_X_MESA        0x8BBC
#यदि_अन्तः /* GL_MESA_framebuffer_flip_x */

#यदि_अपरिभाषितम् GL_MESA_framebuffer_flip_y
#परिभाषय GL_MESA_framebuffer_flip_y 1
#परिभाषय GL_FRAMEBUFFER_FLIP_Y_MESA        0x8BBB
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFRAMEBUFFERPARAMETERIMESAPROC) (GLenum target, GLenum pname, GLint param);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETFRAMEBUFFERPARAMETERIVMESAPROC) (GLenum target, GLenum pname, GLint *params);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glFramebufferParameteriMESA (GLenum target, GLenum pname, GLint param);
GL_APICALL शून्य GL_APIENTRY glGetFramebufferParameterivMESA (GLenum target, GLenum pname, GLint *params);
#यदि_अन्तः
#यदि_अन्तः /* GL_MESA_framebuffer_flip_y */

#यदि_अपरिभाषितम् GL_MESA_framebuffer_swap_xy
#परिभाषय GL_MESA_framebuffer_swap_xy 1
#परिभाषय GL_FRAMEBUFFER_SWAP_XY_MESA       0x8BBD
#यदि_अन्तः /* GL_MESA_framebuffer_swap_xy */

#यदि_अपरिभाषितम् GL_MESA_क्रमादेशः_द्विमान_formats
#परिभाषय GL_MESA_क्रमादेशः_द्विमान_formats 1
#परिभाषय GL_क्रमादेशः_द्विमान_FORMAT_MESA     0x875F
#यदि_अन्तः /* GL_MESA_program_binary_formats */

#यदि_अपरिभाषितम् GL_MESA_sampler_objects
#परिभाषय GL_MESA_sampler_objects 1
#परिभाषय GL_SAMPLER_BINDING                0x8919
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGENSAMPLERSPROC) (GLsizei गणनम्, GLuint *samplers);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDELETESAMPLERSPROC) (GLsizei गणनम्, ध्रुव GLuint *samplers);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLISSAMPLERPROC) (GLuint sampler);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBINDSAMPLERPROC) (GLuint unit, GLuint sampler);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSAMPLERPARAMETERIPROC) (GLuint sampler, GLenum pname, GLint param);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, ध्रुव GLint *param);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSAMPLERPARAMETERFPROC) (GLuint sampler, GLenum pname, GLfloat param);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, ध्रुव GLfloat *param);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, GLint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, GLfloat *params);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glGenSamplers (GLsizei गणनम्, GLuint *samplers);
GL_APICALL शून्य GL_APIENTRY glDeleteSamplers (GLsizei गणनम्, ध्रुव GLuint *samplers);
GL_APICALL GLboolean GL_APIENTRY glIsSampler (GLuint sampler);
GL_APICALL शून्य GL_APIENTRY glBindSampler (GLuint unit, GLuint sampler);
GL_APICALL शून्य GL_APIENTRY glSamplerParameteri (GLuint sampler, GLenum pname, GLint param);
GL_APICALL शून्य GL_APIENTRY glSamplerParameteriv (GLuint sampler, GLenum pname, ध्रुव GLint *param);
GL_APICALL शून्य GL_APIENTRY glSamplerParameterf (GLuint sampler, GLenum pname, GLfloat param);
GL_APICALL शून्य GL_APIENTRY glSamplerParameterfv (GLuint sampler, GLenum pname, ध्रुव GLfloat *param);
GL_APICALL शून्य GL_APIENTRY glGetSamplerParameteriv (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL शून्य GL_APIENTRY glGetSamplerParameterfv (GLuint sampler, GLenum pname, GLfloat *params);
#यदि_अन्तः
#यदि_अन्तः /* GL_MESA_sampler_objects */

#यदि_अपरिभाषितम् GL_MESA_shader_integer_functions
#परिभाषय GL_MESA_shader_integer_functions 1
#यदि_अन्तः /* GL_MESA_shader_integer_functions */

#यदि_अपरिभाषितम् GL_MESA_texture_const_bandwidth
#परिभाषय GL_MESA_texture_const_bandwidth 1
#परिभाषय GL_CONST_BW_TILING_MESA           0x8BBE
#यदि_अन्तः /* GL_MESA_texture_const_bandwidth */

#यदि_अपरिभाषितम् GL_NVX_blend_equation_advanced_multi_draw_buffers
#परिभाषय GL_NVX_blend_equation_advanced_multi_draw_buffers 1
#यदि_अन्तः /* GL_NVX_blend_equation_advanced_multi_draw_buffers */

#यदि_अपरिभाषितम् GL_NV_bindless_texture
#परिभाषय GL_NV_bindless_texture 1
प्रकारनिर्देश GLuint64 (GL_APIENTRYP PFNGLGETTEXTUREHANDLENVPROC) (GLuint texture);
प्रकारनिर्देश GLuint64 (GL_APIENTRYP PFNGLGETTEXTURESAMPLERHANDLENVPROC) (GLuint texture, GLuint sampler);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMAKETEXTUREHANDLERESIDENTNVPROC) (GLuint64 handle);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMAKETEXTUREHANDLENONRESIDENTNVPROC) (GLuint64 handle);
प्रकारनिर्देश GLuint64 (GL_APIENTRYP PFNGLGETIMAGEHANDLENVPROC) (GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMAKEIMAGEHANDLERESIDENTNVPROC) (GLuint64 handle, GLenum access);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMAKEIMAGEHANDLENONRESIDENTNVPROC) (GLuint64 handle);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORMHANDLEUI64NVPROC) (GLint location, GLuint64 मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORMHANDLEUI64VNVPROC) (GLint location, GLsizei गणनम्, ध्रुव GLuint64 *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64NVPROC) (GLuint क्रमादेशः, GLint location, GLuint64 मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64VNVPROC) (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLuint64 *मानानि);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLISTEXTUREHANDLERESIDENTNVPROC) (GLuint64 handle);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLISIMAGEHANDLERESIDENTNVPROC) (GLuint64 handle);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL GLuint64 GL_APIENTRY glGetTextureHandleNV (GLuint texture);
GL_APICALL GLuint64 GL_APIENTRY glGetTextureSamplerHandleNV (GLuint texture, GLuint sampler);
GL_APICALL शून्य GL_APIENTRY glMakeTextureHandleResidentNV (GLuint64 handle);
GL_APICALL शून्य GL_APIENTRY glMakeTextureHandleNonResidentNV (GLuint64 handle);
GL_APICALL GLuint64 GL_APIENTRY glGetImageHandleNV (GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format);
GL_APICALL शून्य GL_APIENTRY glMakeImageHandleResidentNV (GLuint64 handle, GLenum access);
GL_APICALL शून्य GL_APIENTRY glMakeImageHandleNonResidentNV (GLuint64 handle);
GL_APICALL शून्य GL_APIENTRY gl_एकरूपम्_Handleui64_NV (GLint location, GLuint64 मानम्);
GL_APICALL शून्य GL_APIENTRY gl_एकरूपम्_Handleui64v_NV (GLint location, GLsizei गणनम्, ध्रुव GLuint64 *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_एकरूपम्_Handleui64_NV (GLuint क्रमादेशः, GLint location, GLuint64 मानम्);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_एकरूपम्_Handleui64v_NV (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLuint64 *मानानि);
GL_APICALL GLboolean GL_APIENTRY glIsTextureHandleResidentNV (GLuint64 handle);
GL_APICALL GLboolean GL_APIENTRY glIsImageHandleResidentNV (GLuint64 handle);
#यदि_अन्तः
#यदि_अन्तः /* GL_NV_bindless_texture */

#यदि_अपरिभाषितम् GL_NV_blend_equation_advanced
#परिभाषय GL_NV_blend_equation_advanced 1
#परिभाषय GL_BLEND_OVERLAP_NV               0x9281
#परिभाषय GL_BLEND_PREMULTIPLIED_SRC_NV     0x9280
#परिभाषय GL_BLUE_NV                        0x1905
#परिभाषय GL_COLORBURN_NV                   0x929A
#परिभाषय GL_COLORDODGE_NV                  0x9299
#परिभाषय GL_CONJOINT_NV                    0x9284
#परिभाषय GL_CONTRAST_NV                    0x92A1
#परिभाषय GL_DARKEN_NV                      0x9297
#परिभाषय GL_DIFFERENCE_NV                  0x929E
#परिभाषय GL_DISJOINT_NV                    0x9283
#परिभाषय GL_DST_ATOP_NV                    0x928F
#परिभाषय GL_DST_अन्तर्_NV                      0x928B
#परिभाषय GL_DST_NV                         0x9287
#परिभाषय GL_DST_बहिर्गमनम्_NV                     0x928D
#परिभाषय GL_DST_OVER_NV                    0x9289
#परिभाषय GL_EXCLUSION_NV                   0x92A0
#परिभाषय GL_GREEN_NV                       0x1904
#परिभाषय GL_HARDLIGHT_NV                   0x929B
#परिभाषय GL_HARDMIX_NV                     0x92A9
#परिभाषय GL_HSL_COLOR_NV                   0x92AF
#परिभाषय GL_HSL_HUE_NV                     0x92AD
#परिभाषय GL_HSL_LUMINOSITY_NV              0x92B0
#परिभाषय GL_HSL_SATURATION_NV              0x92AE
#परिभाषय GL_INVERT_OVG_NV                  0x92B4
#परिभाषय GL_INVERT_RGB_NV                  0x92A3
#परिभाषय GL_LIGHTEN_NV                     0x9298
#परिभाषय GL_LINEARBURN_NV                  0x92A5
#परिभाषय GL_LINEARDODGE_NV                 0x92A4
#परिभाषय GL_LINEARLIGHT_NV                 0x92A7
#परिभाषय GL_MINUS_CLAMPED_NV               0x92B3
#परिभाषय GL_MINUS_NV                       0x929F
#परिभाषय GL_MULTIPLY_NV                    0x9294
#परिभाषय GL_OVERLAY_NV                     0x9296
#परिभाषय GL_PINLIGHT_NV                    0x92A8
#परिभाषय GL_PLUS_CLAMPED_ALPHA_NV          0x92B2
#परिभाषय GL_PLUS_CLAMPED_NV                0x92B1
#परिभाषय GL_PLUS_DARKER_NV                 0x9292
#परिभाषय GL_PLUS_NV                        0x9291
#परिभाषय GL_RED_NV                         0x1903
#परिभाषय GL_SCREEN_NV                      0x9295
#परिभाषय GL_SOFTLIGHT_NV                   0x929C
#परिभाषय GL_SRC_ATOP_NV                    0x928E
#परिभाषय GL_SRC_अन्तर्_NV                      0x928A
#परिभाषय GL_SRC_NV                         0x9286
#परिभाषय GL_SRC_बहिर्गमनम्_NV                     0x928C
#परिभाषय GL_SRC_OVER_NV                    0x9288
#परिभाषय GL_UNCORRELATED_NV                0x9282
#परिभाषय GL_VIVIDLIGHT_NV                  0x92A6
#परिभाषय GL_XOR_NV                         0x1506
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBLENDPARAMETERINVPROC) (GLenum pname, GLint मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBLENDBARRIERNVPROC) (शून्य);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glBlendParameteriNV (GLenum pname, GLint मानम्);
GL_APICALL शून्य GL_APIENTRY glBlendBarrierNV (शून्य);
#यदि_अन्तः
#यदि_अन्तः /* GL_NV_blend_equation_advanced */

#यदि_अपरिभाषितम् GL_NV_blend_equation_advanced_coherent
#परिभाषय GL_NV_blend_equation_advanced_coherent 1
#परिभाषय GL_BLEND_ADVANCED_COHERENT_NV     0x9285
#यदि_अन्तः /* GL_NV_blend_equation_advanced_coherent */

#यदि_अपरिभाषितम् GL_NV_blend_minmax_गुणकः
#परिभाषय GL_NV_blend_minmax_गुणकः 1
#परिभाषय GL_गुणकः_MIN_AMD                 0x901C
#परिभाषय GL_गुणकः_MAX_AMD                 0x901D
#यदि_अन्तः /* GL_NV_blend_minmax_factor */

#यदि_अपरिभाषितम् GL_NV_clip_space_w_scaling
#परिभाषय GL_NV_clip_space_w_scaling 1
#परिभाषय GL_VIEWPORT_POSITION_W_SCALE_NV   0x937C
#परिभाषय GL_VIEWPORT_POSITION_W_SCALE_X_COEFF_NV 0x937D
#परिभाषय GL_VIEWPORT_POSITION_W_SCALE_Y_COEFF_NV 0x937E
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLVIEWPORTPOSITIONWSCALENVPROC) (GLuint सूचकांक, GLfloat xcoeff, GLfloat ycoeff);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glViewportPositionWScaleNV (GLuint सूचकांक, GLfloat xcoeff, GLfloat ycoeff);
#यदि_अन्तः
#यदि_अन्तः /* GL_NV_clip_space_w_scaling */

#यदि_अपरिभाषितम् GL_NV_compute_shader_derivatives
#परिभाषय GL_NV_compute_shader_derivatives 1
#यदि_अन्तः /* GL_NV_compute_shader_derivatives */

#यदि_अपरिभाषितम् GL_NV_conditional_render
#परिभाषय GL_NV_conditional_render 1
#परिभाषय GL_QUERY_WAIT_NV                  0x8E13
#परिभाषय GL_QUERY_NO_WAIT_NV               0x8E14
#परिभाषय GL_QUERY_BY_REGION_WAIT_NV        0x8E15
#परिभाषय GL_QUERY_BY_REGION_NO_WAIT_NV     0x8E16
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBEGINCONDITIONALRENDERNVPROC) (GLuint id, GLenum बहुलकम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLENDCONDITIONALRENDERNVPROC) (शून्य);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glBeginConditionalRenderNV (GLuint id, GLenum बहुलकम्);
GL_APICALL शून्य GL_APIENTRY gl_अन्तः_Conditional_Render_NV (शून्य);
#यदि_अन्तः
#यदि_अन्तः /* GL_NV_conditional_render */

#यदि_अपरिभाषितम् GL_NV_conservative_raster
#परिभाषय GL_NV_conservative_raster 1
#परिभाषय GL_CONSERVATIVE_RASTERIZATION_NV  0x9346
#परिभाषय GL_SUBPIXEL_PRECISION_BIAS_X_द्वयङ्काः_NV 0x9347
#परिभाषय GL_SUBPIXEL_PRECISION_BIAS_Y_द्वयङ्काः_NV 0x9348
#परिभाषय GL_MAX_SUBPIXEL_PRECISION_BIAS_द्वयङ्काः_NV 0x9349
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSUBPIXELPRECISIONBIASNVPROC) (GLuint xbits, GLuint ybits);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glSubpixelPrecisionBiasNV (GLuint xbits, GLuint ybits);
#यदि_अन्तः
#यदि_अन्तः /* GL_NV_conservative_raster */

#यदि_अपरिभाषितम् GL_NV_conservative_raster_pre_snap
#परिभाषय GL_NV_conservative_raster_pre_snap 1
#परिभाषय GL_CONSERVATIVE_RASTER_बहुलकम्_PRE_SNAP_NV 0x9550
#यदि_अन्तः /* GL_NV_conservative_raster_pre_snap */

#यदि_अपरिभाषितम् GL_NV_conservative_raster_pre_snap_triangles
#परिभाषय GL_NV_conservative_raster_pre_snap_triangles 1
#परिभाषय GL_CONSERVATIVE_RASTER_बहुलकम्_NV    0x954D
#परिभाषय GL_CONSERVATIVE_RASTER_बहुलकम्_POST_SNAP_NV 0x954E
#परिभाषय GL_CONSERVATIVE_RASTER_बहुलकम्_PRE_SNAP_TRIANGLES_NV 0x954F
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCONSERVATIVERASTERPARAMETERINVPROC) (GLenum pname, GLint param);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glConservativeRasterParameteriNV (GLenum pname, GLint param);
#यदि_अन्तः
#यदि_अन्तः /* GL_NV_conservative_raster_pre_snap_triangles */

#यदि_अपरिभाषितम् GL_NV_copy_बफर
#परिभाषय GL_NV_copy_बफर 1
#परिभाषय GL_COPY_READ_बफर_NV            0x8F36
#परिभाषय GL_COPY_WRITE_बफर_NV           0x8F37
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCOPYBUFFERSUBDATANVPROC) (GLenum readTarget, GLenum writeTarget, GLintptr read_विस्थापनम्, GLintptr write_विस्थापनम्, GLsizeiptr आकार);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_Copy_बफर_Sub_दत्त_NV (GLenum readTarget, GLenum writeTarget, GLintptr read_विस्थापनम्, GLintptr write_विस्थापनम्, GLsizeiptr आकार);
#यदि_अन्तः
#यदि_अन्तः /* GL_NV_copy_buffer */

#यदि_अपरिभाषितम् GL_NV_coverage_sample
#परिभाषय GL_NV_coverage_sample 1
#परिभाषय GL_COVERAGE_COMPONENT_NV          0x8ED0
#परिभाषय GL_COVERAGE_COMPONENT4_NV         0x8ED1
#परिभाषय GL_COVERAGE_ATTACHMENT_NV         0x8ED2
#परिभाषय GL_COVERAGE_BUFFERS_NV            0x8ED3
#परिभाषय GL_COVERAGE_SAMPLES_NV            0x8ED4
#परिभाषय GL_COVERAGE_ALL_FRAGMENTS_NV      0x8ED5
#परिभाषय GL_COVERAGE_EDGE_FRAGMENTS_NV     0x8ED6
#परिभाषय GL_COVERAGE_AUTOMATIC_NV          0x8ED7
#परिभाषय GL_COVERAGE_बफर_BIT_NV         0x00008000
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCOVERAGEMASKNVPROC) (GLboolean आवरणम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCOVERAGEOPERATIONNVPROC) (GLenum operation);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_Coverage_आवरणम्_NV (GLboolean आवरणम्);
GL_APICALL शून्य GL_APIENTRY glCoverageOperationNV (GLenum operation);
#यदि_अन्तः
#यदि_अन्तः /* GL_NV_coverage_sample */

#यदि_अपरिभाषितम् GL_NV_गभीरता_nonlinear
#परिभाषय GL_NV_गभीरता_nonlinear 1
#परिभाषय GL_गभीरता_COMPONENT16_NONLINEAR_NV 0x8E2C
#यदि_अन्तः /* GL_NV_depth_nonlinear */

#यदि_अपरिभाषितम् GL_NV_draw_buffers
#परिभाषय GL_NV_draw_buffers 1
#परिभाषय GL_MAX_DRAW_BUFFERS_NV            0x8824
#परिभाषय GL_DRAW_BUFFER0_NV                0x8825
#परिभाषय GL_DRAW_BUFFER1_NV                0x8826
#परिभाषय GL_DRAW_BUFFER2_NV                0x8827
#परिभाषय GL_DRAW_BUFFER3_NV                0x8828
#परिभाषय GL_DRAW_BUFFER4_NV                0x8829
#परिभाषय GL_DRAW_BUFFER5_NV                0x882A
#परिभाषय GL_DRAW_BUFFER6_NV                0x882B
#परिभाषय GL_DRAW_BUFFER7_NV                0x882C
#परिभाषय GL_DRAW_BUFFER8_NV                0x882D
#परिभाषय GL_DRAW_BUFFER9_NV                0x882E
#परिभाषय GL_DRAW_BUFFER10_NV               0x882F
#परिभाषय GL_DRAW_BUFFER11_NV               0x8830
#परिभाषय GL_DRAW_BUFFER12_NV               0x8831
#परिभाषय GL_DRAW_BUFFER13_NV               0x8832
#परिभाषय GL_DRAW_BUFFER14_NV               0x8833
#परिभाषय GL_DRAW_BUFFER15_NV               0x8834
#परिभाषय GL_COLOR_ATTACHMENT0_NV           0x8CE0
#परिभाषय GL_COLOR_ATTACHMENT1_NV           0x8CE1
#परिभाषय GL_COLOR_ATTACHMENT2_NV           0x8CE2
#परिभाषय GL_COLOR_ATTACHMENT3_NV           0x8CE3
#परिभाषय GL_COLOR_ATTACHMENT4_NV           0x8CE4
#परिभाषय GL_COLOR_ATTACHMENT5_NV           0x8CE5
#परिभाषय GL_COLOR_ATTACHMENT6_NV           0x8CE6
#परिभाषय GL_COLOR_ATTACHMENT7_NV           0x8CE7
#परिभाषय GL_COLOR_ATTACHMENT8_NV           0x8CE8
#परिभाषय GL_COLOR_ATTACHMENT9_NV           0x8CE9
#परिभाषय GL_COLOR_ATTACHMENT10_NV          0x8CEA
#परिभाषय GL_COLOR_ATTACHMENT11_NV          0x8CEB
#परिभाषय GL_COLOR_ATTACHMENT12_NV          0x8CEC
#परिभाषय GL_COLOR_ATTACHMENT13_NV          0x8CED
#परिभाषय GL_COLOR_ATTACHMENT14_NV          0x8CEE
#परिभाषय GL_COLOR_ATTACHMENT15_NV          0x8CEF
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWBUFFERSNVPROC) (GLsizei n, ध्रुव GLenum *bufs);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glDrawBuffersNV (GLsizei n, ध्रुव GLenum *bufs);
#यदि_अन्तः
#यदि_अन्तः /* GL_NV_draw_buffers */

#यदि_अपरिभाषितम् GL_NV_draw_instanced
#परिभाषय GL_NV_draw_instanced 1
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDNVPROC) (GLenum बहुलकम्, GLint first, GLsizei गणनम्, GLsizei primcount);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDNVPROC) (GLenum बहुलकम्, GLsizei गणनम्, GLenum type, ध्रुव शून्य *indices, GLsizei primcount);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glDrawArraysInstancedNV (GLenum बहुलकम्, GLint first, GLsizei गणनम्, GLsizei primcount);
GL_APICALL शून्य GL_APIENTRY glDrawElementsInstancedNV (GLenum बहुलकम्, GLsizei गणनम्, GLenum type, ध्रुव शून्य *indices, GLsizei primcount);
#यदि_अन्तः
#यदि_अन्तः /* GL_NV_draw_instanced */

#यदि_अपरिभाषितम् GL_NV_draw_vulkan_image
#परिभाषय GL_NV_draw_vulkan_image 1
प्रकारनिर्देश शून्य (GL_APIENTRY  *GLVULKANPROCNV)(शून्य);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWVKIMAGENVPROC) (GLuint64 vkImage, GLuint sampler, GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat z, GLfloat s0, GLfloat t0, GLfloat s1, GLfloat t1);
प्रकारनिर्देश GLVULKANPROCNV (GL_APIENTRYP PFNGLGETVKPROCADDRNVPROC) (ध्रुव GLchar *name);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLWAITVKSEMAPHORENVPROC) (GLuint64 vkSemaphore);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSIGNALVKSEMAPHORENVPROC) (GLuint64 vkSemaphore);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSIGNALVKFENCENVPROC) (GLuint64 vkFence);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glDrawVkImageNV (GLuint64 vkImage, GLuint sampler, GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat z, GLfloat s0, GLfloat t0, GLfloat s1, GLfloat t1);
GL_APICALL GLVULKANPROCNV GL_APIENTRY glGetVkProcAddrNV (ध्रुव GLchar *name);
GL_APICALL शून्य GL_APIENTRY glWaitVkSemaphoreNV (GLuint64 vkSemaphore);
GL_APICALL शून्य GL_APIENTRY glSignalVkSemaphoreNV (GLuint64 vkSemaphore);
GL_APICALL शून्य GL_APIENTRY glSignalVkFenceNV (GLuint64 vkFence);
#यदि_अन्तः
#यदि_अन्तः /* GL_NV_draw_vulkan_image */

#यदि_अपरिभाषितम् GL_NV_explicit_attrib_location
#परिभाषय GL_NV_explicit_attrib_location 1
#यदि_अन्तः /* GL_NV_explicit_attrib_location */

#यदि_अपरिभाषितम् GL_NV_fbo_color_attachments
#परिभाषय GL_NV_fbo_color_attachments 1
#परिभाषय GL_MAX_COLOR_ATTACHMENTS_NV       0x8CDF
#यदि_अन्तः /* GL_NV_fbo_color_attachments */

#यदि_अपरिभाषितम् GL_NV_fence
#परिभाषय GL_NV_fence 1
#परिभाषय GL_ALL_COMPLETED_NV               0x84F2
#परिभाषय GL_FENCE_स्थितिः_NV                0x84F3
#परिभाषय GL_FENCE_CONDITION_NV             0x84F4
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDELETEFENCESNVPROC) (GLsizei n, ध्रुव GLuint *fences);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGENFENCESNVPROC) (GLsizei n, GLuint *fences);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLISFENCENVPROC) (GLuint fence);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLTESTFENCENVPROC) (GLuint fence);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETFENCEIVNVPROC) (GLuint fence, GLenum pname, GLint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFINISHFENCENVPROC) (GLuint fence);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSETFENCENVPROC) (GLuint fence, GLenum condition);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glDeleteFencesNV (GLsizei n, ध्रुव GLuint *fences);
GL_APICALL शून्य GL_APIENTRY glGenFencesNV (GLsizei n, GLuint *fences);
GL_APICALL GLboolean GL_APIENTRY glIsFenceNV (GLuint fence);
GL_APICALL GLboolean GL_APIENTRY glTestFenceNV (GLuint fence);
GL_APICALL शून्य GL_APIENTRY glGetFenceivNV (GLuint fence, GLenum pname, GLint *params);
GL_APICALL शून्य GL_APIENTRY glFinishFenceNV (GLuint fence);
GL_APICALL शून्य GL_APIENTRY gl_समुच्चयः_Fence_NV (GLuint fence, GLenum condition);
#यदि_अन्तः
#यदि_अन्तः /* GL_NV_fence */

#यदि_अपरिभाषितम् GL_NV_fill_rectangle
#परिभाषय GL_NV_fill_rectangle 1
#परिभाषय GL_FILL_RECTANGLE_NV              0x933C
#यदि_अन्तः /* GL_NV_fill_rectangle */

#यदि_अपरिभाषितम् GL_NV_fragment_coverage_गन्तव्यम्_color
#परिभाषय GL_NV_fragment_coverage_गन्तव्यम्_color 1
#परिभाषय GL_FRAGMENT_COVERAGE_गन्तव्यम्_COLOR_NV  0x92DD
#परिभाषय GL_FRAGMENT_COVERAGE_COLOR_NV     0x92DE
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFRAGMENTCOVERAGECOLORNVPROC) (GLuint color);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glFragmentCoverageColorNV (GLuint color);
#यदि_अन्तः
#यदि_अन्तः /* GL_NV_fragment_coverage_to_color */

#यदि_अपरिभाषितम् GL_NV_fragment_shader_barycentric
#परिभाषय GL_NV_fragment_shader_barycentric 1
#यदि_अन्तः /* GL_NV_fragment_shader_barycentric */

#यदि_अपरिभाषितम् GL_NV_fragment_shader_interlock
#परिभाषय GL_NV_fragment_shader_interlock 1
#यदि_अन्तः /* GL_NV_fragment_shader_interlock */

#यदि_अपरिभाषितम् GL_NV_framebuffer_blit
#परिभाषय GL_NV_framebuffer_blit 1
#परिभाषय GL_READ_FRAMEBUFFER_NV            0x8CA8
#परिभाषय GL_DRAW_FRAMEBUFFER_NV            0x8CA9
#परिभाषय GL_DRAW_FRAMEBUFFER_BINDING_NV    0x8CA6
#परिभाषय GL_READ_FRAMEBUFFER_BINDING_NV    0x8CAA
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBLITFRAMEBUFFERNVPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield आवरणम्, GLenum filter);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glBlitFramebufferNV (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield आवरणम्, GLenum filter);
#यदि_अन्तः
#यदि_अन्तः /* GL_NV_framebuffer_blit */

#यदि_अपरिभाषितम् GL_NV_framebuffer_mixed_samples
#परिभाषय GL_NV_framebuffer_mixed_samples 1
#परिभाषय GL_COVERAGE_MODULATION_सारणी_NV   0x9331
#परिभाषय GL_COLOR_SAMPLES_NV               0x8E20
#परिभाषय GL_गभीरता_SAMPLES_NV               0x932D
#परिभाषय GL_STENCIL_SAMPLES_NV             0x932E
#परिभाषय GL_MIXED_गभीरता_SAMPLES_SUPPORTED_NV 0x932F
#परिभाषय GL_MIXED_STENCIL_SAMPLES_SUPPORTED_NV 0x9330
#परिभाषय GL_COVERAGE_MODULATION_NV         0x9332
#परिभाषय GL_COVERAGE_MODULATION_सारणी_आकार_NV 0x9333
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCOVERAGEMODULATIONTABLENVPROC) (GLsizei n, ध्रुव GLfloat *v);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETCOVERAGEMODULATIONTABLENVPROC) (GLsizei buf_आकार, GLfloat *v);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCOVERAGEMODULATIONNVPROC) (GLenum components);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_Coverage_Modulation_सारणी_NV (GLsizei n, ध्रुव GLfloat *v);
GL_APICALL शून्य GL_APIENTRY gl_Get_Coverage_Modulation_सारणी_NV (GLsizei buf_आकार, GLfloat *v);
GL_APICALL शून्य GL_APIENTRY glCoverageModulationNV (GLenum components);
#यदि_अन्तः
#यदि_अन्तः /* GL_NV_framebuffer_mixed_samples */

#यदि_अपरिभाषितम् GL_NV_framebuffer_multisample
#परिभाषय GL_NV_framebuffer_multisample 1
#परिभाषय GL_RENDERBUFFER_SAMPLES_NV        0x8CAB
#परिभाषय GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_NV 0x8D56
#परिभाषय GL_MAX_SAMPLES_NV                 0x8D57
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLENVPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei विस्तारः, GLsizei height);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glRenderbufferStorageMultisampleNV (GLenum target, GLsizei samples, GLenum internalformat, GLsizei विस्तारः, GLsizei height);
#यदि_अन्तः
#यदि_अन्तः /* GL_NV_framebuffer_multisample */

#यदि_अपरिभाषितम् GL_NV_generate_mipmap_sRGB
#परिभाषय GL_NV_generate_mipmap_sRGB 1
#यदि_अन्तः /* GL_NV_generate_mipmap_sRGB */

#यदि_अपरिभाषितम् GL_NV_geometry_shader_passthrough
#परिभाषय GL_NV_geometry_shader_passthrough 1
#यदि_अन्तः /* GL_NV_geometry_shader_passthrough */

#यदि_अपरिभाषितम् GL_NV_gpu_shader5
#परिभाषय GL_NV_gpu_shader5 1
प्रकारनिर्देश khronos_int64_t GLint64EXT;
प्रकारनिर्देश khronos_uint64_t GLuint64EXT;
#परिभाषय GL_INT64_NV                       0x140E
#परिभाषय GL_UNSIGNED_INT64_NV              0x140F
#परिभाषय GL_INT8_NV                        0x8FE0
#परिभाषय GL_INT8_VEC2_NV                   0x8FE1
#परिभाषय GL_INT8_VEC3_NV                   0x8FE2
#परिभाषय GL_INT8_VEC4_NV                   0x8FE3
#परिभाषय GL_INT16_NV                       0x8FE4
#परिभाषय GL_INT16_VEC2_NV                  0x8FE5
#परिभाषय GL_INT16_VEC3_NV                  0x8FE6
#परिभाषय GL_INT16_VEC4_NV                  0x8FE7
#परिभाषय GL_INT64_VEC2_NV                  0x8FE9
#परिभाषय GL_INT64_VEC3_NV                  0x8FEA
#परिभाषय GL_INT64_VEC4_NV                  0x8FEB
#परिभाषय GL_UNSIGNED_INT8_NV               0x8FEC
#परिभाषय GL_UNSIGNED_INT8_VEC2_NV          0x8FED
#परिभाषय GL_UNSIGNED_INT8_VEC3_NV          0x8FEE
#परिभाषय GL_UNSIGNED_INT8_VEC4_NV          0x8FEF
#परिभाषय GL_UNSIGNED_INT16_NV              0x8FF0
#परिभाषय GL_UNSIGNED_INT16_VEC2_NV         0x8FF1
#परिभाषय GL_UNSIGNED_INT16_VEC3_NV         0x8FF2
#परिभाषय GL_UNSIGNED_INT16_VEC4_NV         0x8FF3
#परिभाषय GL_UNSIGNED_INT64_VEC2_NV         0x8FF5
#परिभाषय GL_UNSIGNED_INT64_VEC3_NV         0x8FF6
#परिभाषय GL_UNSIGNED_INT64_VEC4_NV         0x8FF7
#परिभाषय GL_FLOAT16_NV                     0x8FF8
#परिभाषय GL_FLOAT16_VEC2_NV                0x8FF9
#परिभाषय GL_FLOAT16_VEC3_NV                0x8FFA
#परिभाषय GL_FLOAT16_VEC4_NV                0x8FFB
#परिभाषय GL_PATCHES                        0x000E
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORM1I64NVPROC) (GLint location, GLint64EXT x);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORM2I64NVPROC) (GLint location, GLint64EXT x, GLint64EXT y);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORM3I64NVPROC) (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORM4I64NVPROC) (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORM1I64VNVPROC) (GLint location, GLsizei गणनम्, ध्रुव GLint64EXT *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORM2I64VNVPROC) (GLint location, GLsizei गणनम्, ध्रुव GLint64EXT *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORM3I64VNVPROC) (GLint location, GLsizei गणनम्, ध्रुव GLint64EXT *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORM4I64VNVPROC) (GLint location, GLsizei गणनम्, ध्रुव GLint64EXT *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORM1UI64NVPROC) (GLint location, GLuint64EXT x);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORM2UI64NVPROC) (GLint location, GLuint64EXT x, GLuint64EXT y);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORM3UI64NVPROC) (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORM4UI64NVPROC) (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORM1UI64VNVPROC) (GLint location, GLsizei गणनम्, ध्रुव GLuint64EXT *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORM2UI64VNVPROC) (GLint location, GLsizei गणनम्, ध्रुव GLuint64EXT *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORM3UI64VNVPROC) (GLint location, GLsizei गणनम्, ध्रुव GLuint64EXT *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORM4UI64VNVPROC) (GLint location, GLsizei गणनम्, ध्रुव GLuint64EXT *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETUNIFORMI64VNVPROC) (GLuint क्रमादेशः, GLint location, GLint64EXT *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM1I64NVPROC) (GLuint क्रमादेशः, GLint location, GLint64EXT x);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM2I64NVPROC) (GLuint क्रमादेशः, GLint location, GLint64EXT x, GLint64EXT y);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM3I64NVPROC) (GLuint क्रमादेशः, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM4I64NVPROC) (GLuint क्रमादेशः, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM1I64VNVPROC) (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLint64EXT *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM2I64VNVPROC) (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLint64EXT *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM3I64VNVPROC) (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLint64EXT *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM4I64VNVPROC) (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLint64EXT *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UI64NVPROC) (GLuint क्रमादेशः, GLint location, GLuint64EXT x);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UI64NVPROC) (GLuint क्रमादेशः, GLint location, GLuint64EXT x, GLuint64EXT y);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UI64NVPROC) (GLuint क्रमादेशः, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UI64NVPROC) (GLuint क्रमादेशः, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UI64VNVPROC) (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLuint64EXT *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UI64VNVPROC) (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLuint64EXT *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UI64VNVPROC) (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLuint64EXT *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UI64VNVPROC) (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLuint64EXT *मानम्);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glUniform1i64NV (GLint location, GLint64EXT x);
GL_APICALL शून्य GL_APIENTRY glUniform2i64NV (GLint location, GLint64EXT x, GLint64EXT y);
GL_APICALL शून्य GL_APIENTRY glUniform3i64NV (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
GL_APICALL शून्य GL_APIENTRY glUniform4i64NV (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
GL_APICALL शून्य GL_APIENTRY glUniform1i64vNV (GLint location, GLsizei गणनम्, ध्रुव GLint64EXT *मानम्);
GL_APICALL शून्य GL_APIENTRY glUniform2i64vNV (GLint location, GLsizei गणनम्, ध्रुव GLint64EXT *मानम्);
GL_APICALL शून्य GL_APIENTRY glUniform3i64vNV (GLint location, GLsizei गणनम्, ध्रुव GLint64EXT *मानम्);
GL_APICALL शून्य GL_APIENTRY glUniform4i64vNV (GLint location, GLsizei गणनम्, ध्रुव GLint64EXT *मानम्);
GL_APICALL शून्य GL_APIENTRY glUniform1ui64NV (GLint location, GLuint64EXT x);
GL_APICALL शून्य GL_APIENTRY glUniform2ui64NV (GLint location, GLuint64EXT x, GLuint64EXT y);
GL_APICALL शून्य GL_APIENTRY glUniform3ui64NV (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
GL_APICALL शून्य GL_APIENTRY glUniform4ui64NV (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
GL_APICALL शून्य GL_APIENTRY glUniform1ui64vNV (GLint location, GLsizei गणनम्, ध्रुव GLuint64EXT *मानम्);
GL_APICALL शून्य GL_APIENTRY glUniform2ui64vNV (GLint location, GLsizei गणनम्, ध्रुव GLuint64EXT *मानम्);
GL_APICALL शून्य GL_APIENTRY glUniform3ui64vNV (GLint location, GLsizei गणनम्, ध्रुव GLuint64EXT *मानम्);
GL_APICALL शून्य GL_APIENTRY glUniform4ui64vNV (GLint location, GLsizei गणनम्, ध्रुव GLuint64EXT *मानम्);
GL_APICALL शून्य GL_APIENTRY glGetUniformi64vNV (GLuint क्रमादेशः, GLint location, GLint64EXT *params);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform1i64_NV (GLuint क्रमादेशः, GLint location, GLint64EXT x);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform2i64_NV (GLuint क्रमादेशः, GLint location, GLint64EXT x, GLint64EXT y);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform3i64_NV (GLuint क्रमादेशः, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform4i64_NV (GLuint क्रमादेशः, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform1i64v_NV (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLint64EXT *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform2i64v_NV (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLint64EXT *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform3i64v_NV (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLint64EXT *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform4i64v_NV (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLint64EXT *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform1ui64_NV (GLuint क्रमादेशः, GLint location, GLuint64EXT x);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform2ui64_NV (GLuint क्रमादेशः, GLint location, GLuint64EXT x, GLuint64EXT y);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform3ui64_NV (GLuint क्रमादेशः, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform4ui64_NV (GLuint क्रमादेशः, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform1ui64v_NV (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLuint64EXT *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform2ui64v_NV (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLuint64EXT *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform3ui64v_NV (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLuint64EXT *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_Uniform4ui64v_NV (GLuint क्रमादेशः, GLint location, GLsizei गणनम्, ध्रुव GLuint64EXT *मानम्);
#यदि_अन्तः
#यदि_अन्तः /* GL_NV_gpu_shader5 */

#यदि_अपरिभाषितम् GL_NV_image_formats
#परिभाषय GL_NV_image_formats 1
#यदि_अन्तः /* GL_NV_image_formats */

#यदि_अपरिभाषितम् GL_NV_instanced_arrays
#परिभाषय GL_NV_instanced_arrays 1
#परिभाषय GL_VERTEX_ATTRIB_ARRAY_भाजकः_NV 0x88FE
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLVERTEXATTRIBDIVISORNVPROC) (GLuint सूचकांक, GLuint भाजकः);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_Vertex_Attrib_भाजकः_NV (GLuint सूचकांक, GLuint भाजकः);
#यदि_अन्तः
#यदि_अन्तः /* GL_NV_instanced_arrays */

#यदि_अपरिभाषितम् GL_NV_internalformat_sample_query
#परिभाषय GL_NV_internalformat_sample_query 1
#परिभाषय GL_TEXTURE_2D_MULTISAMPLE         0x9100
#परिभाषय GL_TEXTURE_2D_MULTISAMPLE_ARRAY   0x9102
#परिभाषय GL_MULTISAMPLES_NV                0x9371
#परिभाषय GL_SUPERSAMPLE_SCALE_X_NV         0x9372
#परिभाषय GL_SUPERSAMPLE_SCALE_Y_NV         0x9373
#परिभाषय GL_CONFORMANT_NV                  0x9374
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETINTERNALFORMATSAMPLEIVNVPROC) (GLenum target, GLenum internalformat, GLsizei samples, GLenum pname, GLsizei गणनम्, GLint *params);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glGetInternalformatSampleivNV (GLenum target, GLenum internalformat, GLsizei samples, GLenum pname, GLsizei गणनम्, GLint *params);
#यदि_अन्तः
#यदि_अन्तः /* GL_NV_internalformat_sample_query */

#यदि_अपरिभाषितम् GL_NV_स्मृतिः_attachment
#परिभाषय GL_NV_स्मृतिः_attachment 1
#परिभाषय GL_ATTACHED_स्मृतिः_OBJECT_NV      0x95A4
#परिभाषय GL_ATTACHED_स्मृतिः_विस्थापनम्_NV      0x95A5
#परिभाषय GL_स्मृतिः_ATTACHABLE_ALIGNMENT_NV 0x95A6
#परिभाषय GL_स्मृतिः_ATTACHABLE_आकार_NV      0x95A7
#परिभाषय GL_स्मृतिः_ATTACHABLE_NV           0x95A8
#परिभाषय GL_DETACHED_स्मृतिः_INCARNATION_NV 0x95A9
#परिभाषय GL_DETACHED_TEXTURES_NV           0x95AA
#परिभाषय GL_DETACHED_BUFFERS_NV            0x95AB
#परिभाषय GL_MAX_DETACHED_TEXTURES_NV       0x95AC
#परिभाषय GL_MAX_DETACHED_BUFFERS_NV        0x95AD
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETMEMORYOBJECTDETACHEDRESOURCESUIVNVPROC) (GLuint स्मृतिः, GLenum pname, GLint first, GLsizei गणनम्, GLuint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLRESETMEMORYOBJECTPARAMETERNVPROC) (GLuint स्मृतिः, GLenum pname);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXATTACHMEMORYNVPROC) (GLenum target, GLuint स्मृतिः, GLuint64 विस्थापनम्_2);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBUFFERATTACHMEMORYNVPROC) (GLenum target, GLuint स्मृतिः, GLuint64 विस्थापनम्_2);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXTUREATTACHMEMORYNVPROC) (GLuint texture, GLuint स्मृतिः, GLuint64 विस्थापनम्_2);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLNAMEDBUFFERATTACHMEMORYNVPROC) (GLuint बफर_2, GLuint स्मृतिः, GLuint64 विस्थापनम्_2);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_Get_स्मृतिः_Object_Detached_Resourcesuiv_NV (GLuint स्मृतिः, GLenum pname, GLint first, GLsizei गणनम्, GLuint *params);
GL_APICALL शून्य GL_APIENTRY gl_Reset_स्मृतिः_Object_Parameter_NV (GLuint स्मृतिः, GLenum pname);
GL_APICALL शून्य GL_APIENTRY gl_Tex_Attach_स्मृतिः_NV (GLenum target, GLuint स्मृतिः, GLuint64 विस्थापनम्_2);
GL_APICALL शून्य GL_APIENTRY gl_बफर_Attach_स्मृतिः_NV (GLenum target, GLuint स्मृतिः, GLuint64 विस्थापनम्_2);
GL_APICALL शून्य GL_APIENTRY gl_Texture_Attach_स्मृतिः_NV (GLuint texture, GLuint स्मृतिः, GLuint64 विस्थापनम्_2);
GL_APICALL शून्य GL_APIENTRY gl_Named_बफर_Attach_स्मृतिः_NV (GLuint बफर_2, GLuint स्मृतिः, GLuint64 विस्थापनम्_2);
#यदि_अन्तः
#यदि_अन्तः /* GL_NV_memory_attachment */

#यदि_अपरिभाषितम् GL_NV_स्मृतिः_object_sparse
#परिभाषय GL_NV_स्मृतिः_object_sparse 1
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBUFFERPAGECOMMITMENTMEMNVPROC) (GLenum target, GLintptr विस्थापनम्_2, GLsizeiptr आकार, GLuint स्मृतिः, GLuint64 mem_विस्थापनम्, GLboolean commit);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXPAGECOMMITMENTMEMNVPROC) (GLenum target, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2, GLuint स्मृतिः, GLuint64 विस्थापनम्_2, GLboolean commit);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLNAMEDBUFFERPAGECOMMITMENTMEMNVPROC) (GLuint बफर_2, GLintptr विस्थापनम्_2, GLsizeiptr आकार, GLuint स्मृतिः, GLuint64 mem_विस्थापनम्, GLboolean commit);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXTUREPAGECOMMITMENTMEMNVPROC) (GLuint texture, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2, GLuint स्मृतिः, GLuint64 विस्थापनम्_2, GLboolean commit);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_बफर_Page_Commitment_Mem_NV (GLenum target, GLintptr विस्थापनम्_2, GLsizeiptr आकार, GLuint स्मृतिः, GLuint64 mem_विस्थापनम्, GLboolean commit);
GL_APICALL शून्य GL_APIENTRY glTexPageCommitmentMemNV (GLenum target, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2, GLuint स्मृतिः, GLuint64 विस्थापनम्_2, GLboolean commit);
GL_APICALL शून्य GL_APIENTRY gl_Named_बफर_Page_Commitment_Mem_NV (GLuint बफर_2, GLintptr विस्थापनम्_2, GLsizeiptr आकार, GLuint स्मृतिः, GLuint64 mem_विस्थापनम्, GLboolean commit);
GL_APICALL शून्य GL_APIENTRY glTexturePageCommitmentMemNV (GLuint texture, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2, GLuint स्मृतिः, GLuint64 विस्थापनम्_2, GLboolean commit);
#यदि_अन्तः
#यदि_अन्तः /* GL_NV_memory_object_sparse */

#यदि_अपरिभाषितम् GL_NV_mesh_shader
#परिभाषय GL_NV_mesh_shader 1
#परिभाषय GL_MESH_SHADER_NV                 0x9559
#परिभाषय GL_TASK_SHADER_NV                 0x955A
#परिभाषय GL_MAX_MESH_एकरूपम्_खण्डानि_NV     0x8E60
#परिभाषय GL_MAX_MESH_TEXTURE_IMAGE_UNITS_NV 0x8E61
#परिभाषय GL_MAX_MESH_IMAGE_UNIFORMS_NV     0x8E62
#परिभाषय GL_MAX_MESH_एकरूपम्_COMPONENTS_NV 0x8E63
#परिभाषय GL_MAX_MESH_ATOMIC_गणक_BUFFERS_NV 0x8E64
#परिभाषय GL_MAX_MESH_ATOMIC_COUNTERS_NV    0x8E65
#परिभाषय GL_MAX_MESH_SHADER_STORAGE_खण्डानि_NV 0x8E66
#परिभाषय GL_MAX_COMBINED_MESH_एकरूपम्_COMPONENTS_NV 0x8E67
#परिभाषय GL_MAX_TASK_एकरूपम्_खण्डानि_NV     0x8E68
#परिभाषय GL_MAX_TASK_TEXTURE_IMAGE_UNITS_NV 0x8E69
#परिभाषय GL_MAX_TASK_IMAGE_UNIFORMS_NV     0x8E6A
#परिभाषय GL_MAX_TASK_एकरूपम्_COMPONENTS_NV 0x8E6B
#परिभाषय GL_MAX_TASK_ATOMIC_गणक_BUFFERS_NV 0x8E6C
#परिभाषय GL_MAX_TASK_ATOMIC_COUNTERS_NV    0x8E6D
#परिभाषय GL_MAX_TASK_SHADER_STORAGE_खण्डानि_NV 0x8E6E
#परिभाषय GL_MAX_COMBINED_TASK_एकरूपम्_COMPONENTS_NV 0x8E6F
#परिभाषय GL_MAX_MESH_WORK_गणः_INVOCATIONS_NV 0x95A2
#परिभाषय GL_MAX_TASK_WORK_गणः_INVOCATIONS_NV 0x95A3
#परिभाषय GL_MAX_MESH_योग_स्मृतिः_आकार_NV  0x9536
#परिभाषय GL_MAX_TASK_योग_स्मृतिः_आकार_NV  0x9537
#परिभाषय GL_MAX_MESH_OUTPUT_VERTICES_NV    0x9538
#परिभाषय GL_MAX_MESH_OUTPUT_PRIMITIVES_NV  0x9539
#परिभाषय GL_MAX_TASK_OUTPUT_गणनम्_NV       0x953A
#परिभाषय GL_MAX_DRAW_MESH_TASKS_गणनम्_NV   0x953D
#परिभाषय GL_MAX_MESH_VIEWS_NV              0x9557
#परिभाषय GL_MESH_OUTPUT_प्रत्येकम्_VERTEX_GRANULARITY_NV 0x92DF
#परिभाषय GL_MESH_OUTPUT_प्रत्येकम्_PRIMITIVE_GRANULARITY_NV 0x9543
#परिभाषय GL_MAX_MESH_WORK_गणः_आकार_NV    0x953B
#परिभाषय GL_MAX_TASK_WORK_गणः_आकार_NV    0x953C
#परिभाषय GL_MESH_WORK_गणः_आकार_NV        0x953E
#परिभाषय GL_TASK_WORK_गणः_आकार_NV        0x953F
#परिभाषय GL_MESH_VERTICES_बहिर्गमनम्_NV           0x9579
#परिभाषय GL_MESH_PRIMITIVES_बहिर्गमनम्_NV         0x957A
#परिभाषय GL_MESH_OUTPUT_TYPE_NV            0x957B
#परिभाषय GL_एकरूपम्_खण्डम्_REFERENCED_BY_MESH_SHADER_NV 0x959C
#परिभाषय GL_एकरूपम्_खण्डम्_REFERENCED_BY_TASK_SHADER_NV 0x959D
#परिभाषय GL_REFERENCED_BY_MESH_SHADER_NV   0x95A0
#परिभाषय GL_REFERENCED_BY_TASK_SHADER_NV   0x95A1
#परिभाषय GL_MESH_SHADER_BIT_NV             0x00000040
#परिभाषय GL_TASK_SHADER_BIT_NV             0x00000080
#परिभाषय GL_MESH_SUBROUTINE_NV             0x957C
#परिभाषय GL_TASK_SUBROUTINE_NV             0x957D
#परिभाषय GL_MESH_SUBROUTINE_एकरूपम्_NV     0x957E
#परिभाषय GL_TASK_SUBROUTINE_एकरूपम्_NV     0x957F
#परिभाषय GL_ATOMIC_गणक_बफर_REFERENCED_BY_MESH_SHADER_NV 0x959E
#परिभाषय GL_ATOMIC_गणक_बफर_REFERENCED_BY_TASK_SHADER_NV 0x959F
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWMESHTASKSNVPROC) (GLuint first, GLuint गणनम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWMESHTASKSINDIRECTNVPROC) (GLintptr परोक्षम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMULTIDRAWMESHTASKSINDIRECTNVPROC) (GLintptr परोक्षम्, GLsizei drawcount, GLsizei stride);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTNVPROC) (GLintptr परोक्षम्, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glDrawMeshTasksNV (GLuint first, GLuint गणनम्);
GL_APICALL शून्य GL_APIENTRY gl_Draw_Mesh_Tasks_परोक्षम्_NV (GLintptr परोक्षम्);
GL_APICALL शून्य GL_APIENTRY gl_Multi_Draw_Mesh_Tasks_परोक्षम्_NV (GLintptr परोक्षम्, GLsizei drawcount, GLsizei stride);
GL_APICALL शून्य GL_APIENTRY gl_Multi_Draw_Mesh_Tasks_परोक्षम्_गणनम्_NV (GLintptr परोक्षम्, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
#यदि_अन्तः
#यदि_अन्तः /* GL_NV_mesh_shader */

#यदि_अपरिभाषितम् GL_NV_non_वर्गफलम्_matrices
#परिभाषय GL_NV_non_वर्गफलम्_matrices 1
#परिभाषय GL_FLOAT_MAT2x3_NV                0x8B65
#परिभाषय GL_FLOAT_MAT2x4_NV                0x8B66
#परिभाषय GL_FLOAT_MAT3x2_NV                0x8B67
#परिभाषय GL_FLOAT_MAT3x4_NV                0x8B68
#परिभाषय GL_FLOAT_MAT4x2_NV                0x8B69
#परिभाषय GL_FLOAT_MAT4x3_NV                0x8B6A
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORMMATRIX2X3FVNVPROC) (GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORMMATRIX3X2FVNVPROC) (GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORMMATRIX2X4FVNVPROC) (GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORMMATRIX4X2FVNVPROC) (GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORMMATRIX3X4FVNVPROC) (GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORMMATRIX4X3FVNVPROC) (GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_एकरूपम्_Matrix2x3fv_NV (GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_एकरूपम्_Matrix3x2fv_NV (GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_एकरूपम्_Matrix2x4fv_NV (GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_एकरूपम्_Matrix4x2fv_NV (GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_एकरूपम्_Matrix3x4fv_NV (GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_एकरूपम्_Matrix4x3fv_NV (GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
#यदि_अन्तः
#यदि_अन्तः /* GL_NV_non_square_matrices */

#यदि_अपरिभाषितम् GL_NV_pack_subimage
#परिभाषय GL_NV_pack_subimage 1
#परिभाषय GL_PACK_ROW_दीर्घता_NV             0x0D02
#परिभाषय GL_PACK_SKIP_पङ्क्तिकाः_NV              0x0D03
#परिभाषय GL_PACK_SKIP_PIXELS_NV            0x0D04
#यदि_अन्तः /* GL_NV_pack_subimage */

#यदि_अपरिभाषितम् GL_NV_मार्गः_rendering
#परिभाषय GL_NV_मार्गः_rendering 1
प्रकारनिर्देश द्विगुण GLdouble;
#परिभाषय GL_मार्गः_FORMAT_SVG_NV             0x9070
#परिभाषय GL_मार्गः_FORMAT_PS_NV              0x9071
#परिभाषय GL_STANDARD_FONT_NAME_NV          0x9072
#परिभाषय GL_SYSTEM_FONT_NAME_NV            0x9073
#परिभाषय GL_FILE_NAME_NV                   0x9074
#परिभाषय GL_मार्गः_STROKE_विस्तारः_NV           0x9075
#परिभाषय GL_मार्गः_अन्तः_CAPS_NV               0x9076
#परिभाषय GL_मार्गः_INITIAL_अन्तः_CAP_NV        0x9077
#परिभाषय GL_मार्गः_TERMINAL_अन्तः_CAP_NV       0x9078
#परिभाषय GL_मार्गः_JOIN_STYLE_NV             0x9079
#परिभाषय GL_मार्गः_MITER_सीमा_NV            0x907A
#परिभाषय GL_मार्गः_DASH_CAPS_NV              0x907B
#परिभाषय GL_मार्गः_INITIAL_DASH_CAP_NV       0x907C
#परिभाषय GL_मार्गः_TERMINAL_DASH_CAP_NV      0x907D
#परिभाषय GL_मार्गः_DASH_विस्थापनम्_NV            0x907E
#परिभाषय GL_मार्गः_CLIENT_दीर्घता_NV          0x907F
#परिभाषय GL_मार्गः_FILL_बहुलकम्_NV              0x9080
#परिभाषय GL_मार्गः_FILL_आवरणम्_NV              0x9081
#परिभाषय GL_मार्गः_FILL_COVER_बहुलकम्_NV        0x9082
#परिभाषय GL_मार्गः_STROKE_COVER_बहुलकम्_NV      0x9083
#परिभाषय GL_मार्गः_STROKE_आवरणम्_NV            0x9084
#परिभाषय GL_गणनम्_ऊर्ध्वम्_NV                    0x9088
#परिभाषय GL_गणनम्_अधस्तात्_NV                  0x9089
#परिभाषय GL_मार्गः_OBJECT_BOUNDING_BOX_NV    0x908A
#परिभाषय GL_CONVEX_HULL_NV                 0x908B
#परिभाषय GL_BOUNDING_BOX_NV                0x908D
#परिभाषय GL_TRANSLATE_X_NV                 0x908E
#परिभाषय GL_TRANSLATE_Y_NV                 0x908F
#परिभाषय GL_TRANSLATE_2D_NV                0x9090
#परिभाषय GL_TRANSLATE_3D_NV                0x9091
#परिभाषय GL_AFFINE_2D_NV                   0x9092
#परिभाषय GL_AFFINE_3D_NV                   0x9094
#परिभाषय GL_TRANSPOSE_AFFINE_2D_NV         0x9096
#परिभाषय GL_TRANSPOSE_AFFINE_3D_NV         0x9098
#परिभाषय GL_UTF8_NV                        0x909A
#परिभाषय GL_UTF16_NV                       0x909B
#परिभाषय GL_BOUNDING_BOX_सम्बन्धि_BOUNDING_BOXES_NV 0x909C
#परिभाषय GL_मार्गः_COMMAND_गणनम्_NV          0x909D
#परिभाषय GL_मार्गः_COORD_गणनम्_NV            0x909E
#परिभाषय GL_मार्गः_DASH_ARRAY_गणनम्_NV       0x909F
#परिभाषय GL_मार्गः_COMPUTED_दीर्घता_NV        0x90A0
#परिभाषय GL_मार्गः_FILL_BOUNDING_BOX_NV      0x90A1
#परिभाषय GL_मार्गः_STROKE_BOUNDING_BOX_NV    0x90A2
#परिभाषय GL_वर्गफलम्_NV                      0x90A3
#परिभाषय GL_आवर्तनम्_NV                       0x90A4
#परिभाषय GL_TRIANGULAR_NV                  0x90A5
#परिभाषय GL_BEVEL_NV                       0x90A6
#परिभाषय GL_MITER_REVERT_NV                0x90A7
#परिभाषय GL_MITER_TRUNCATE_NV              0x90A8
#परिभाषय GL_SKIP_MISSING_GLYPH_NV          0x90A9
#परिभाषय GL_USE_MISSING_GLYPH_NV           0x90AA
#परिभाषय GL_मार्गः_ERROR_POSITION_NV         0x90AB
#परिभाषय GL_ACCUM_ADJACENT_युग्मानि_NV        0x90AD
#परिभाषय GL_ADJACENT_युग्मानि_NV              0x90AE
#परिभाषय GL_FIRST_गन्तव्यम्_REST_NV               0x90AF
#परिभाषय GL_मार्गः_GEN_बहुलकम्_NV               0x90B0
#परिभाषय GL_मार्गः_GEN_COEFF_NV              0x90B1
#परिभाषय GL_मार्गः_GEN_COMPONENTS_NV         0x90B3
#परिभाषय GL_मार्गः_STENCIL_FUNC_NV           0x90B7
#परिभाषय GL_मार्गः_STENCIL_REF_NV            0x90B8
#परिभाषय GL_मार्गः_STENCIL_मानम्_आवरणम्_NV     0x90B9
#परिभाषय GL_मार्गः_STENCIL_गभीरता_विस्थापनम्_गुणकः_NV 0x90BD
#परिभाषय GL_मार्गः_STENCIL_गभीरता_विस्थापनम्_UNITS_NV 0x90BE
#परिभाषय GL_मार्गः_COVER_गभीरता_FUNC_NV       0x90BF
#परिभाषय GL_मार्गः_DASH_विस्थापनम्_RESET_NV      0x90B4
#परिभाषय GL_MOVE_गन्तव्यम्_RESETS_NV              0x90B5
#परिभाषय GL_MOVE_गन्तव्यम्_CONTINUES_NV           0x90B6
#परिभाषय GL_CLOSE_मार्गः_NV                  0x00
#परिभाषय GL_MOVE_गन्तव्यम्_NV                     0x02
#परिभाषय GL_RELATIVE_MOVE_गन्तव्यम्_NV            0x03
#परिभाषय GL_पङ्क्तिः_गन्तव्यम्_NV                     0x04
#परिभाषय GL_RELATIVE_पङ्क्तिः_गन्तव्यम्_NV            0x05
#परिभाषय GL_HORIZONTAL_पङ्क्तिः_गन्तव्यम्_NV          0x06
#परिभाषय GL_RELATIVE_HORIZONTAL_पङ्क्तिः_गन्तव्यम्_NV 0x07
#परिभाषय GL_VERTICAL_पङ्क्तिः_गन्तव्यम्_NV            0x08
#परिभाषय GL_RELATIVE_VERTICAL_पङ्क्तिः_गन्तव्यम्_NV   0x09
#परिभाषय GL_QUADRATIC_वक्रम्_गन्तव्यम्_NV          0x0A
#परिभाषय GL_RELATIVE_QUADRATIC_वक्रम्_गन्तव्यम्_NV 0x0B
#परिभाषय GL_CUBIC_वक्रम्_गन्तव्यम्_NV              0x0C
#परिभाषय GL_RELATIVE_CUBIC_वक्रम्_गन्तव्यम्_NV     0x0D
#परिभाषय GL_SMOOTH_QUADRATIC_वक्रम्_गन्तव्यम्_NV   0x0E
#परिभाषय GL_RELATIVE_SMOOTH_QUADRATIC_वक्रम्_गन्तव्यम्_NV 0x0F
#परिभाषय GL_SMOOTH_CUBIC_वक्रम्_गन्तव्यम्_NV       0x10
#परिभाषय GL_RELATIVE_SMOOTH_CUBIC_वक्रम्_गन्तव्यम्_NV 0x11
#परिभाषय GL_SMALL_CCW_ARC_गन्तव्यम्_NV            0x12
#परिभाषय GL_RELATIVE_SMALL_CCW_ARC_गन्तव्यम्_NV   0x13
#परिभाषय GL_SMALL_CW_ARC_गन्तव्यम्_NV             0x14
#परिभाषय GL_RELATIVE_SMALL_CW_ARC_गन्तव्यम्_NV    0x15
#परिभाषय GL_LARGE_CCW_ARC_गन्तव्यम्_NV            0x16
#परिभाषय GL_RELATIVE_LARGE_CCW_ARC_गन्तव्यम्_NV   0x17
#परिभाषय GL_LARGE_CW_ARC_गन्तव्यम्_NV             0x18
#परिभाषय GL_RELATIVE_LARGE_CW_ARC_गन्तव्यम्_NV    0x19
#परिभाषय GL_RESTART_मार्गः_NV                0xF0
#परिभाषय GL_DUP_FIRST_CUBIC_वक्रम्_गन्तव्यम्_NV    0xF2
#परिभाषय GL_DUP_चरमः_CUBIC_वक्रम्_गन्तव्यम्_NV     0xF4
#परिभाषय GL_RECT_NV                        0xF6
#परिभाषय GL_CIRCULAR_CCW_ARC_गन्तव्यम्_NV         0xF8
#परिभाषय GL_CIRCULAR_CW_ARC_गन्तव्यम्_NV          0xFA
#परिभाषय GL_CIRCULAR_TANGENT_ARC_गन्तव्यम्_NV     0xFC
#परिभाषय GL_ARC_गन्तव्यम्_NV                      0xFE
#परिभाषय GL_RELATIVE_ARC_गन्तव्यम्_NV             0xFF
#परिभाषय GL_BOLD_BIT_NV                    0x01
#परिभाषय GL_ITALIC_BIT_NV                  0x02
#परिभाषय GL_GLYPH_विस्तारः_BIT_NV             0x01
#परिभाषय GL_GLYPH_HEIGHT_BIT_NV            0x02
#परिभाषय GL_GLYPH_HORIZONTAL_BEARING_X_BIT_NV 0x04
#परिभाषय GL_GLYPH_HORIZONTAL_BEARING_Y_BIT_NV 0x08
#परिभाषय GL_GLYPH_HORIZONTAL_BEARING_ADVANCE_BIT_NV 0x10
#परिभाषय GL_GLYPH_VERTICAL_BEARING_X_BIT_NV 0x20
#परिभाषय GL_GLYPH_VERTICAL_BEARING_Y_BIT_NV 0x40
#परिभाषय GL_GLYPH_VERTICAL_BEARING_ADVANCE_BIT_NV 0x80
#परिभाषय GL_GLYPH_HAS_KERNING_BIT_NV       0x100
#परिभाषय GL_FONT_X_MIN_BOUNDS_BIT_NV       0x00010000
#परिभाषय GL_FONT_Y_MIN_BOUNDS_BIT_NV       0x00020000
#परिभाषय GL_FONT_X_MAX_BOUNDS_BIT_NV       0x00040000
#परिभाषय GL_FONT_Y_MAX_BOUNDS_BIT_NV       0x00080000
#परिभाषय GL_FONT_UNITS_प्रत्येकम्_EM_BIT_NV       0x00100000
#परिभाषय GL_FONT_ASCENDER_BIT_NV           0x00200000
#परिभाषय GL_FONT_DESCENDER_BIT_NV          0x00400000
#परिभाषय GL_FONT_HEIGHT_BIT_NV             0x00800000
#परिभाषय GL_FONT_MAX_ADVANCE_विस्तारः_BIT_NV  0x01000000
#परिभाषय GL_FONT_MAX_ADVANCE_HEIGHT_BIT_NV 0x02000000
#परिभाषय GL_FONT_UNDERLINE_POSITION_BIT_NV 0x04000000
#परिभाषय GL_FONT_UNDERLINE_THICKNESS_BIT_NV 0x08000000
#परिभाषय GL_FONT_HAS_KERNING_BIT_NV        0x10000000
#परिभाषय GL_ROUNDED_RECT_NV                0xE8
#परिभाषय GL_RELATIVE_ROUNDED_RECT_NV       0xE9
#परिभाषय GL_ROUNDED_RECT2_NV               0xEA
#परिभाषय GL_RELATIVE_ROUNDED_RECT2_NV      0xEB
#परिभाषय GL_ROUNDED_RECT4_NV               0xEC
#परिभाषय GL_RELATIVE_ROUNDED_RECT4_NV      0xED
#परिभाषय GL_ROUNDED_RECT8_NV               0xEE
#परिभाषय GL_RELATIVE_ROUNDED_RECT8_NV      0xEF
#परिभाषय GL_RELATIVE_RECT_NV               0xF7
#परिभाषय GL_FONT_GLYPHS_उपलब्धम्_NV       0x9368
#परिभाषय GL_FONT_TARGET_UNAVAILABLE_NV     0x9369
#परिभाषय GL_FONT_UNAVAILABLE_NV            0x936A
#परिभाषय GL_FONT_UNINTELLIGIBLE_NV         0x936B
#परिभाषय GL_CONIC_वक्रम्_गन्तव्यम्_NV              0x1A
#परिभाषय GL_RELATIVE_CONIC_वक्रम्_गन्तव्यम्_NV     0x1B
#परिभाषय GL_FONT_अङ्कः_GLYPH_INDICES_BIT_NV  0x20000000
#परिभाषय GL_STANDARD_FONT_FORMAT_NV        0x936C
#परिभाषय GL_मार्गः_PROJECTION_NV             0x1701
#परिभाषय GL_मार्गः_MODELVIEW_NV              0x1700
#परिभाषय GL_मार्गः_MODELVIEW_राशिः_गभीरता_NV  0x0BA3
#परिभाषय GL_मार्गः_MODELVIEW_MATRIX_NV       0x0BA6
#परिभाषय GL_मार्गः_MAX_MODELVIEW_राशिः_गभीरता_NV 0x0D36
#परिभाषय GL_मार्गः_TRANSPOSE_MODELVIEW_MATRIX_NV 0x84E3
#परिभाषय GL_मार्गः_PROJECTION_राशिः_गभीरता_NV 0x0BA4
#परिभाषय GL_मार्गः_PROJECTION_MATRIX_NV      0x0BA7
#परिभाषय GL_मार्गः_MAX_PROJECTION_राशिः_गभीरता_NV 0x0D38
#परिभाषय GL_मार्गः_TRANSPOSE_PROJECTION_MATRIX_NV 0x84E4
#परिभाषय GL_FRAGMENT_निवेशः_NV              0x936D
प्रकारनिर्देश GLuint (GL_APIENTRYP PFNGLGENPATHSNVPROC) (GLsizei range);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDELETEPATHSNVPROC) (GLuint मार्गः, GLsizei range);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLISPATHNVPROC) (GLuint मार्गः);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPATHCOMMANDSNVPROC) (GLuint मार्गः, GLsizei अङ्कः_Commands, ध्रुव GLubyte *commands, GLsizei अङ्कः_Coords, GLenum coordType, ध्रुव शून्य *coords);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPATHCOORDSNVPROC) (GLuint मार्गः, GLsizei अङ्कः_Coords, GLenum coordType, ध्रुव शून्य *coords);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPATHSUBCOMMANDSNVPROC) (GLuint मार्गः, GLsizei commandStart, GLsizei commands_गन्तव्यम्_Delete, GLsizei अङ्कः_Commands, ध्रुव GLubyte *commands, GLsizei अङ्कः_Coords, GLenum coordType, ध्रुव शून्य *coords);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPATHSUBCOORDSNVPROC) (GLuint मार्गः, GLsizei coordStart, GLsizei अङ्कः_Coords, GLenum coordType, ध्रुव शून्य *coords);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPATHSTRINGNVPROC) (GLuint मार्गः, GLenum format, GLsizei दीर्घता, ध्रुव शून्य *मार्गः_String);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPATHGLYPHSNVPROC) (GLuint first_मार्गः_Name, GLenum fontTarget, ध्रुव शून्य *fontName, GLbitfield fontStyle, GLsizei अङ्कः_Glyphs, GLenum type, ध्रुव शून्य *charcodes, GLenum handleMissingGlyphs, GLuint मार्गः_Parameter_Template, GLfloat emScale);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPATHGLYPHRANGENVPROC) (GLuint first_मार्गः_Name, GLenum fontTarget, ध्रुव शून्य *fontName, GLbitfield fontStyle, GLuint firstGlyph, GLsizei अङ्कः_Glyphs, GLenum handleMissingGlyphs, GLuint मार्गः_Parameter_Template, GLfloat emScale);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLWEIGHTPATHSNVPROC) (GLuint परिणाम_मार्गः, GLsizei अङ्कः_Paths, ध्रुव GLuint *paths, ध्रुव GLfloat *weights);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCOPYPATHNVPROC) (GLuint परिणाम_मार्गः, GLuint src_मार्गः);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLINTERPOLATEPATHSNVPROC) (GLuint परिणाम_मार्गः, GLuint मार्गः_A, GLuint मार्गः_B, GLfloat weight);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTRANSFORMPATHNVPROC) (GLuint परिणाम_मार्गः, GLuint src_मार्गः, GLenum transformType, ध्रुव GLfloat *transform_मानानि);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPATHPARAMETERIVNVPROC) (GLuint मार्गः, GLenum pname, ध्रुव GLint *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPATHPARAMETERINVPROC) (GLuint मार्गः, GLenum pname, GLint मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPATHPARAMETERFVNVPROC) (GLuint मार्गः, GLenum pname, ध्रुव GLfloat *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPATHPARAMETERFNVPROC) (GLuint मार्गः, GLenum pname, GLfloat मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPATHDASHARRAYNVPROC) (GLuint मार्गः, GLsizei dash_गणनम्, ध्रुव GLfloat *dashArray);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPATHSTENCILFUNCNVPROC) (GLenum func, GLint ref, GLuint आवरणम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPATHSTENCILDEPTHOFFSETNVPROC) (GLfloat गुणकः, GLfloat units);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSTENCILFILLPATHNVPROC) (GLuint मार्गः, GLenum fill_बहुलकम्, GLuint आवरणम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSTENCILSTROKEPATHNVPROC) (GLuint मार्गः, GLint reference, GLuint आवरणम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSTENCILFILLPATHINSTANCEDNVPROC) (GLsizei अङ्कः_Paths, GLenum मार्गः_Name_Type, ध्रुव शून्य *paths, GLuint मार्गः_आधारः, GLenum fill_बहुलकम्, GLuint आवरणम्, GLenum transformType, ध्रुव GLfloat *transform_मानानि);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSTENCILSTROKEPATHINSTANCEDNVPROC) (GLsizei अङ्कः_Paths, GLenum मार्गः_Name_Type, ध्रुव शून्य *paths, GLuint मार्गः_आधारः, GLint reference, GLuint आवरणम्, GLenum transformType, ध्रुव GLfloat *transform_मानानि);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPATHCOVERDEPTHFUNCNVPROC) (GLenum func);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCOVERFILLPATHNVPROC) (GLuint मार्गः, GLenum cover_बहुलकम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCOVERSTROKEPATHNVPROC) (GLuint मार्गः, GLenum cover_बहुलकम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCOVERFILLPATHINSTANCEDNVPROC) (GLsizei अङ्कः_Paths, GLenum मार्गः_Name_Type, ध्रुव शून्य *paths, GLuint मार्गः_आधारः, GLenum cover_बहुलकम्, GLenum transformType, ध्रुव GLfloat *transform_मानानि);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCOVERSTROKEPATHINSTANCEDNVPROC) (GLsizei अङ्कः_Paths, GLenum मार्गः_Name_Type, ध्रुव शून्य *paths, GLuint मार्गः_आधारः, GLenum cover_बहुलकम्, GLenum transformType, ध्रुव GLfloat *transform_मानानि);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETPATHPARAMETERIVNVPROC) (GLuint मार्गः, GLenum pname, GLint *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETPATHPARAMETERFVNVPROC) (GLuint मार्गः, GLenum pname, GLfloat *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETPATHCOMMANDSNVPROC) (GLuint मार्गः, GLubyte *commands);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETPATHCOORDSNVPROC) (GLuint मार्गः, GLfloat *coords);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETPATHDASHARRAYNVPROC) (GLuint मार्गः, GLfloat *dashArray);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETPATHMETRICSNVPROC) (GLbitfield metric_Query_आवरणम्, GLsizei अङ्कः_Paths, GLenum मार्गः_Name_Type, ध्रुव शून्य *paths, GLuint मार्गः_आधारः, GLsizei stride, GLfloat *metrics);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETPATHMETRICRANGENVPROC) (GLbitfield metric_Query_आवरणम्, GLuint first_मार्गः_Name, GLsizei अङ्कः_Paths, GLsizei stride, GLfloat *metrics);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETPATHSPACINGNVPROC) (GLenum मार्गः_List_बहुलकम्, GLsizei अङ्कः_Paths, GLenum मार्गः_Name_Type, ध्रुव शून्य *paths, GLuint मार्गः_आधारः, GLfloat advanceScale, GLfloat kerningScale, GLenum transformType, GLfloat *returnedSpacing);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLISPOINTINFILLPATHNVPROC) (GLuint मार्गः, GLuint आवरणम्, GLfloat x, GLfloat y);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLISPOINTINSTROKEPATHNVPROC) (GLuint मार्गः, GLfloat x, GLfloat y);
प्रकारनिर्देश GLfloat (GL_APIENTRYP PFNGLGETPATHLENGTHNVPROC) (GLuint मार्गः, GLsizei startSegment, GLsizei अङ्कः_Segments);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLPOINTALONGPATHNVPROC) (GLuint मार्गः, GLsizei startSegment, GLsizei अङ्कः_Segments, GLfloat distance, GLfloat *x, GLfloat *y, GLfloat *tangentX, GLfloat *tangentY);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMATRIXLOAD3X2FNVPROC) (GLenum matrix_बहुलकम्, ध्रुव GLfloat *m);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMATRIXLOAD3X3FNVPROC) (GLenum matrix_बहुलकम्, ध्रुव GLfloat *m);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMATRIXLOADTRANSPOSE3X3FNVPROC) (GLenum matrix_बहुलकम्, ध्रुव GLfloat *m);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMATRIXMULT3X2FNVPROC) (GLenum matrix_बहुलकम्, ध्रुव GLfloat *m);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMATRIXMULT3X3FNVPROC) (GLenum matrix_बहुलकम्, ध्रुव GLfloat *m);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMATRIXMULTTRANSPOSE3X3FNVPROC) (GLenum matrix_बहुलकम्, ध्रुव GLfloat *m);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSTENCILTHENCOVERFILLPATHNVPROC) (GLuint मार्गः, GLenum fill_बहुलकम्, GLuint आवरणम्, GLenum cover_बहुलकम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSTENCILTHENCOVERSTROKEPATHNVPROC) (GLuint मार्गः, GLint reference, GLuint आवरणम्, GLenum cover_बहुलकम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSTENCILTHENCOVERFILLPATHINSTANCEDNVPROC) (GLsizei अङ्कः_Paths, GLenum मार्गः_Name_Type, ध्रुव शून्य *paths, GLuint मार्गः_आधारः, GLenum fill_बहुलकम्, GLuint आवरणम्, GLenum cover_बहुलकम्, GLenum transformType, ध्रुव GLfloat *transform_मानानि);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSTENCILTHENCOVERSTROKEPATHINSTANCEDNVPROC) (GLsizei अङ्कः_Paths, GLenum मार्गः_Name_Type, ध्रुव शून्य *paths, GLuint मार्गः_आधारः, GLint reference, GLuint आवरणम्, GLenum cover_बहुलकम्, GLenum transformType, ध्रुव GLfloat *transform_मानानि);
प्रकारनिर्देश GLenum (GL_APIENTRYP PFNGLPATHGLYPHINDEXRANGENVPROC) (GLenum fontTarget, ध्रुव शून्य *fontName, GLbitfield fontStyle, GLuint मार्गः_Parameter_Template, GLfloat emScale, GLuint *आधारः_And_गणनम्);
प्रकारनिर्देश GLenum (GL_APIENTRYP PFNGLPATHGLYPHINDEXARRAYNVPROC) (GLuint first_मार्गः_Name, GLenum fontTarget, ध्रुव शून्य *fontName, GLbitfield fontStyle, GLuint first_Glyph_सूचकांक, GLsizei अङ्कः_Glyphs, GLuint मार्गः_Parameter_Template, GLfloat emScale);
प्रकारनिर्देश GLenum (GL_APIENTRYP PFNGLPATHMEMORYGLYPHINDEXARRAYNVPROC) (GLuint first_मार्गः_Name, GLenum fontTarget, GLsizeiptr font_आकार, ध्रुव शून्य *font_दत्त, GLsizei face_सूचकांक, GLuint first_Glyph_सूचकांक, GLsizei अङ्कः_Glyphs, GLuint मार्गः_Parameter_Template, GLfloat emScale);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPROGRAMPATHFRAGMENTINPUTGENNVPROC) (GLuint क्रमादेशः, GLint location, GLenum gen_बहुलकम्, GLint components, ध्रुव GLfloat *coeffs);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETPROGRAMRESOURCEFVNVPROC) (GLuint क्रमादेशः, GLenum क्रमादेशः_Interface, GLuint सूचकांक, GLsizei prop_गणनम्, ध्रुव GLenum *props, GLsizei गणनम्, GLsizei *दीर्घता, GLfloat *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMATRIXFRUSTUMEXTPROC) (GLenum बहुलकम्, GLdouble वामः, GLdouble दक्षिणः, GLdouble bottom, GLdouble शिखरम्, GLdouble zNear, GLdouble zFar);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMATRIXLOADIDENTITYEXTPROC) (GLenum बहुलकम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMATRIXLOADTRANSPOSEFEXTPROC) (GLenum बहुलकम्, ध्रुव GLfloat *m);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMATRIXLOADTRANSPOSEDEXTPROC) (GLenum बहुलकम्, ध्रुव GLdouble *m);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMATRIXLOADFEXTPROC) (GLenum बहुलकम्, ध्रुव GLfloat *m);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMATRIXLOADDEXTPROC) (GLenum बहुलकम्, ध्रुव GLdouble *m);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMATRIXMULTTRANSPOSEFEXTPROC) (GLenum बहुलकम्, ध्रुव GLfloat *m);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMATRIXMULTTRANSPOSEDEXTPROC) (GLenum बहुलकम्, ध्रुव GLdouble *m);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMATRIXMULTFEXTPROC) (GLenum बहुलकम्, ध्रुव GLfloat *m);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMATRIXMULTDEXTPROC) (GLenum बहुलकम्, ध्रुव GLdouble *m);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMATRIXORTHOEXTPROC) (GLenum बहुलकम्, GLdouble वामः, GLdouble दक्षिणः, GLdouble bottom, GLdouble शिखरम्, GLdouble zNear, GLdouble zFar);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMATRIXPOPEXTPROC) (GLenum बहुलकम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMATRIXPUSHEXTPROC) (GLenum बहुलकम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMATRIXROTATEFEXTPROC) (GLenum बहुलकम्, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMATRIXROTATEDEXTPROC) (GLenum बहुलकम्, GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMATRIXSCALEFEXTPROC) (GLenum बहुलकम्, GLfloat x, GLfloat y, GLfloat z);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMATRIXSCALEDEXTPROC) (GLenum बहुलकम्, GLdouble x, GLdouble y, GLdouble z);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMATRIXTRANSLATEFEXTPROC) (GLenum बहुलकम्, GLfloat x, GLfloat y, GLfloat z);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMATRIXTRANSLATEDEXTPROC) (GLenum बहुलकम्, GLdouble x, GLdouble y, GLdouble z);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL GLuint GL_APIENTRY glGenPathsNV (GLsizei range);
GL_APICALL शून्य GL_APIENTRY glDeletePathsNV (GLuint मार्गः, GLsizei range);
GL_APICALL GLboolean GL_APIENTRY gl_Is_मार्गः_NV (GLuint मार्गः);
GL_APICALL शून्य GL_APIENTRY gl_मार्गः_Commands_NV (GLuint मार्गः, GLsizei अङ्कः_Commands, ध्रुव GLubyte *commands, GLsizei अङ्कः_Coords, GLenum coordType, ध्रुव शून्य *coords);
GL_APICALL शून्य GL_APIENTRY gl_मार्गः_Coords_NV (GLuint मार्गः, GLsizei अङ्कः_Coords, GLenum coordType, ध्रुव शून्य *coords);
GL_APICALL शून्य GL_APIENTRY gl_मार्गः_Sub_Commands_NV (GLuint मार्गः, GLsizei commandStart, GLsizei commands_गन्तव्यम्_Delete, GLsizei अङ्कः_Commands, ध्रुव GLubyte *commands, GLsizei अङ्कः_Coords, GLenum coordType, ध्रुव शून्य *coords);
GL_APICALL शून्य GL_APIENTRY gl_मार्गः_Sub_Coords_NV (GLuint मार्गः, GLsizei coordStart, GLsizei अङ्कः_Coords, GLenum coordType, ध्रुव शून्य *coords);
GL_APICALL शून्य GL_APIENTRY gl_मार्गः_String_NV (GLuint मार्गः, GLenum format, GLsizei दीर्घता, ध्रुव शून्य *मार्गः_String);
GL_APICALL शून्य GL_APIENTRY gl_मार्गः_Glyphs_NV (GLuint first_मार्गः_Name, GLenum fontTarget, ध्रुव शून्य *fontName, GLbitfield fontStyle, GLsizei अङ्कः_Glyphs, GLenum type, ध्रुव शून्य *charcodes, GLenum handleMissingGlyphs, GLuint मार्गः_Parameter_Template, GLfloat emScale);
GL_APICALL शून्य GL_APIENTRY gl_मार्गः_Glyph_Range_NV (GLuint first_मार्गः_Name, GLenum fontTarget, ध्रुव शून्य *fontName, GLbitfield fontStyle, GLuint firstGlyph, GLsizei अङ्कः_Glyphs, GLenum handleMissingGlyphs, GLuint मार्गः_Parameter_Template, GLfloat emScale);
GL_APICALL शून्य GL_APIENTRY glWeightPathsNV (GLuint परिणाम_मार्गः, GLsizei अङ्कः_Paths, ध्रुव GLuint *paths, ध्रुव GLfloat *weights);
GL_APICALL शून्य GL_APIENTRY gl_Copy_मार्गः_NV (GLuint परिणाम_मार्गः, GLuint src_मार्गः);
GL_APICALL शून्य GL_APIENTRY glInterpolatePathsNV (GLuint परिणाम_मार्गः, GLuint मार्गः_A, GLuint मार्गः_B, GLfloat weight);
GL_APICALL शून्य GL_APIENTRY gl_Transform_मार्गः_NV (GLuint परिणाम_मार्गः, GLuint src_मार्गः, GLenum transformType, ध्रुव GLfloat *transform_मानानि);
GL_APICALL शून्य GL_APIENTRY gl_मार्गः_Parameteriv_NV (GLuint मार्गः, GLenum pname, ध्रुव GLint *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_मार्गः_Parameteri_NV (GLuint मार्गः, GLenum pname, GLint मानम्);
GL_APICALL शून्य GL_APIENTRY gl_मार्गः_Parameterfv_NV (GLuint मार्गः, GLenum pname, ध्रुव GLfloat *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_मार्गः_Parameterf_NV (GLuint मार्गः, GLenum pname, GLfloat मानम्);
GL_APICALL शून्य GL_APIENTRY gl_मार्गः_Dash_Array_NV (GLuint मार्गः, GLsizei dash_गणनम्, ध्रुव GLfloat *dashArray);
GL_APICALL शून्य GL_APIENTRY gl_मार्गः_Stencil_Func_NV (GLenum func, GLint ref, GLuint आवरणम्);
GL_APICALL शून्य GL_APIENTRY gl_मार्गः_Stencil_गभीरता_विस्थापनम्_NV (GLfloat गुणकः, GLfloat units);
GL_APICALL शून्य GL_APIENTRY gl_Stencil_Fill_मार्गः_NV (GLuint मार्गः, GLenum fill_बहुलकम्, GLuint आवरणम्);
GL_APICALL शून्य GL_APIENTRY gl_Stencil_Stroke_मार्गः_NV (GLuint मार्गः, GLint reference, GLuint आवरणम्);
GL_APICALL शून्य GL_APIENTRY gl_Stencil_Fill_मार्गः_Instanced_NV (GLsizei अङ्कः_Paths, GLenum मार्गः_Name_Type, ध्रुव शून्य *paths, GLuint मार्गः_आधारः, GLenum fill_बहुलकम्, GLuint आवरणम्, GLenum transformType, ध्रुव GLfloat *transform_मानानि);
GL_APICALL शून्य GL_APIENTRY gl_Stencil_Stroke_मार्गः_Instanced_NV (GLsizei अङ्कः_Paths, GLenum मार्गः_Name_Type, ध्रुव शून्य *paths, GLuint मार्गः_आधारः, GLint reference, GLuint आवरणम्, GLenum transformType, ध्रुव GLfloat *transform_मानानि);
GL_APICALL शून्य GL_APIENTRY gl_मार्गः_Cover_गभीरता_Func_NV (GLenum func);
GL_APICALL शून्य GL_APIENTRY gl_Cover_Fill_मार्गः_NV (GLuint मार्गः, GLenum cover_बहुलकम्);
GL_APICALL शून्य GL_APIENTRY gl_Cover_Stroke_मार्गः_NV (GLuint मार्गः, GLenum cover_बहुलकम्);
GL_APICALL शून्य GL_APIENTRY gl_Cover_Fill_मार्गः_Instanced_NV (GLsizei अङ्कः_Paths, GLenum मार्गः_Name_Type, ध्रुव शून्य *paths, GLuint मार्गः_आधारः, GLenum cover_बहुलकम्, GLenum transformType, ध्रुव GLfloat *transform_मानानि);
GL_APICALL शून्य GL_APIENTRY gl_Cover_Stroke_मार्गः_Instanced_NV (GLsizei अङ्कः_Paths, GLenum मार्गः_Name_Type, ध्रुव शून्य *paths, GLuint मार्गः_आधारः, GLenum cover_बहुलकम्, GLenum transformType, ध्रुव GLfloat *transform_मानानि);
GL_APICALL शून्य GL_APIENTRY gl_Get_मार्गः_Parameteriv_NV (GLuint मार्गः, GLenum pname, GLint *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_Get_मार्गः_Parameterfv_NV (GLuint मार्गः, GLenum pname, GLfloat *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_Get_मार्गः_Commands_NV (GLuint मार्गः, GLubyte *commands);
GL_APICALL शून्य GL_APIENTRY gl_Get_मार्गः_Coords_NV (GLuint मार्गः, GLfloat *coords);
GL_APICALL शून्य GL_APIENTRY gl_Get_मार्गः_Dash_Array_NV (GLuint मार्गः, GLfloat *dashArray);
GL_APICALL शून्य GL_APIENTRY gl_Get_मार्गः_Metrics_NV (GLbitfield metric_Query_आवरणम्, GLsizei अङ्कः_Paths, GLenum मार्गः_Name_Type, ध्रुव शून्य *paths, GLuint मार्गः_आधारः, GLsizei stride, GLfloat *metrics);
GL_APICALL शून्य GL_APIENTRY gl_Get_मार्गः_Metric_Range_NV (GLbitfield metric_Query_आवरणम्, GLuint first_मार्गः_Name, GLsizei अङ्कः_Paths, GLsizei stride, GLfloat *metrics);
GL_APICALL शून्य GL_APIENTRY gl_Get_मार्गः_Spacing_NV (GLenum मार्गः_List_बहुलकम्, GLsizei अङ्कः_Paths, GLenum मार्गः_Name_Type, ध्रुव शून्य *paths, GLuint मार्गः_आधारः, GLfloat advanceScale, GLfloat kerningScale, GLenum transformType, GLfloat *returnedSpacing);
GL_APICALL GLboolean GL_APIENTRY gl_Is_Point_अन्तर्_Fill_मार्गः_NV (GLuint मार्गः, GLuint आवरणम्, GLfloat x, GLfloat y);
GL_APICALL GLboolean GL_APIENTRY gl_Is_Point_अन्तर्_Stroke_मार्गः_NV (GLuint मार्गः, GLfloat x, GLfloat y);
GL_APICALL GLfloat GL_APIENTRY gl_Get_मार्गः_दीर्घता_NV (GLuint मार्गः, GLsizei startSegment, GLsizei अङ्कः_Segments);
GL_APICALL GLboolean GL_APIENTRY gl_Point_Along_मार्गः_NV (GLuint मार्गः, GLsizei startSegment, GLsizei अङ्कः_Segments, GLfloat distance, GLfloat *x, GLfloat *y, GLfloat *tangentX, GLfloat *tangentY);
GL_APICALL शून्य GL_APIENTRY glMatrixLoad3x2fNV (GLenum matrix_बहुलकम्, ध्रुव GLfloat *m);
GL_APICALL शून्य GL_APIENTRY glMatrixLoad3x3fNV (GLenum matrix_बहुलकम्, ध्रुव GLfloat *m);
GL_APICALL शून्य GL_APIENTRY gl_Matrix_आरोपय_Transpose3x3f_NV (GLenum matrix_बहुलकम्, ध्रुव GLfloat *m);
GL_APICALL शून्य GL_APIENTRY glMatrixMult3x2fNV (GLenum matrix_बहुलकम्, ध्रुव GLfloat *m);
GL_APICALL शून्य GL_APIENTRY glMatrixMult3x3fNV (GLenum matrix_बहुलकम्, ध्रुव GLfloat *m);
GL_APICALL शून्य GL_APIENTRY glMatrixMultTranspose3x3fNV (GLenum matrix_बहुलकम्, ध्रुव GLfloat *m);
GL_APICALL शून्य GL_APIENTRY gl_Stencil_Then_Cover_Fill_मार्गः_NV (GLuint मार्गः, GLenum fill_बहुलकम्, GLuint आवरणम्, GLenum cover_बहुलकम्);
GL_APICALL शून्य GL_APIENTRY gl_Stencil_Then_Cover_Stroke_मार्गः_NV (GLuint मार्गः, GLint reference, GLuint आवरणम्, GLenum cover_बहुलकम्);
GL_APICALL शून्य GL_APIENTRY gl_Stencil_Then_Cover_Fill_मार्गः_Instanced_NV (GLsizei अङ्कः_Paths, GLenum मार्गः_Name_Type, ध्रुव शून्य *paths, GLuint मार्गः_आधारः, GLenum fill_बहुलकम्, GLuint आवरणम्, GLenum cover_बहुलकम्, GLenum transformType, ध्रुव GLfloat *transform_मानानि);
GL_APICALL शून्य GL_APIENTRY gl_Stencil_Then_Cover_Stroke_मार्गः_Instanced_NV (GLsizei अङ्कः_Paths, GLenum मार्गः_Name_Type, ध्रुव शून्य *paths, GLuint मार्गः_आधारः, GLint reference, GLuint आवरणम्, GLenum cover_बहुलकम्, GLenum transformType, ध्रुव GLfloat *transform_मानानि);
GL_APICALL GLenum GL_APIENTRY gl_मार्गः_Glyph_सूचकांक_Range_NV (GLenum fontTarget, ध्रुव शून्य *fontName, GLbitfield fontStyle, GLuint मार्गः_Parameter_Template, GLfloat emScale, GLuint *आधारः_And_गणनम्);
GL_APICALL GLenum GL_APIENTRY gl_मार्गः_Glyph_सूचकांक_Array_NV (GLuint first_मार्गः_Name, GLenum fontTarget, ध्रुव शून्य *fontName, GLbitfield fontStyle, GLuint first_Glyph_सूचकांक, GLsizei अङ्कः_Glyphs, GLuint मार्गः_Parameter_Template, GLfloat emScale);
GL_APICALL GLenum GL_APIENTRY gl_मार्गः_स्मृतिः_Glyph_सूचकांक_Array_NV (GLuint first_मार्गः_Name, GLenum fontTarget, GLsizeiptr font_आकार, ध्रुव शून्य *font_दत्त, GLsizei face_सूचकांक, GLuint first_Glyph_सूचकांक, GLsizei अङ्कः_Glyphs, GLuint मार्गः_Parameter_Template, GLfloat emScale);
GL_APICALL शून्य GL_APIENTRY gl_क्रमादेशः_मार्गः_Fragment_निवेशः_Gen_NV (GLuint क्रमादेशः, GLint location, GLenum gen_बहुलकम्, GLint components, ध्रुव GLfloat *coeffs);
GL_APICALL शून्य GL_APIENTRY gl_Get_क्रमादेशः_Resourcefv_NV (GLuint क्रमादेशः, GLenum क्रमादेशः_Interface, GLuint सूचकांक, GLsizei prop_गणनम्, ध्रुव GLenum *props, GLsizei गणनम्, GLsizei *दीर्घता, GLfloat *params);
GL_APICALL शून्य GL_APIENTRY glMatrixFrustumEXT (GLenum बहुलकम्, GLdouble वामः, GLdouble दक्षिणः, GLdouble bottom, GLdouble शिखरम्, GLdouble zNear, GLdouble zFar);
GL_APICALL शून्य GL_APIENTRY gl_Matrix_आरोपय_तटस्थः_EXT (GLenum बहुलकम्);
GL_APICALL शून्य GL_APIENTRY gl_Matrix_आरोपय_Transposef_EXT (GLenum बहुलकम्, ध्रुव GLfloat *m);
GL_APICALL शून्य GL_APIENTRY gl_Matrix_आरोपय_Transposed_EXT (GLenum बहुलकम्, ध्रुव GLdouble *m);
GL_APICALL शून्य GL_APIENTRY glMatrixLoadfEXT (GLenum बहुलकम्, ध्रुव GLfloat *m);
GL_APICALL शून्य GL_APIENTRY glMatrixLoaddEXT (GLenum बहुलकम्, ध्रुव GLdouble *m);
GL_APICALL शून्य GL_APIENTRY glMatrixMultTransposefEXT (GLenum बहुलकम्, ध्रुव GLfloat *m);
GL_APICALL शून्य GL_APIENTRY glMatrixMultTransposedEXT (GLenum बहुलकम्, ध्रुव GLdouble *m);
GL_APICALL शून्य GL_APIENTRY glMatrixMultfEXT (GLenum बहुलकम्, ध्रुव GLfloat *m);
GL_APICALL शून्य GL_APIENTRY glMatrixMultdEXT (GLenum बहुलकम्, ध्रुव GLdouble *m);
GL_APICALL शून्य GL_APIENTRY glMatrixOrthoEXT (GLenum बहुलकम्, GLdouble वामः, GLdouble दक्षिणः, GLdouble bottom, GLdouble शिखरम्, GLdouble zNear, GLdouble zFar);
GL_APICALL शून्य GL_APIENTRY gl_Matrix_निष्कासय_EXT (GLenum बहुलकम्);
GL_APICALL शून्य GL_APIENTRY gl_Matrix_प्रक्षिप_EXT (GLenum बहुलकम्);
GL_APICALL शून्य GL_APIENTRY glMatrixRotatefEXT (GLenum बहुलकम्, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL शून्य GL_APIENTRY glMatrixRotatedEXT (GLenum बहुलकम्, GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
GL_APICALL शून्य GL_APIENTRY glMatrixScalefEXT (GLenum बहुलकम्, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL शून्य GL_APIENTRY glMatrixScaledEXT (GLenum बहुलकम्, GLdouble x, GLdouble y, GLdouble z);
GL_APICALL शून्य GL_APIENTRY glMatrixTranslatefEXT (GLenum बहुलकम्, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL शून्य GL_APIENTRY glMatrixTranslatedEXT (GLenum बहुलकम्, GLdouble x, GLdouble y, GLdouble z);
#यदि_अन्तः
#यदि_अन्तः /* GL_NV_path_rendering */

#यदि_अपरिभाषितम् GL_NV_मार्गः_rendering_shared_edge
#परिभाषय GL_NV_मार्गः_rendering_shared_edge 1
#परिभाषय GL_SHARED_EDGE_NV                 0xC0
#यदि_अन्तः /* GL_NV_path_rendering_shared_edge */

#यदि_अपरिभाषितम् GL_NV_pixel_बफर_object
#परिभाषय GL_NV_pixel_बफर_object 1
#परिभाषय GL_PIXEL_PACK_बफर_NV           0x88EB
#परिभाषय GL_PIXEL_UNPACK_बफर_NV         0x88EC
#परिभाषय GL_PIXEL_PACK_बफर_BINDING_NV   0x88ED
#परिभाषय GL_PIXEL_UNPACK_बफर_BINDING_NV 0x88EF
#यदि_अन्तः /* GL_NV_pixel_buffer_object */

#यदि_अपरिभाषितम् GL_NV_polygon_बहुलकम्
#परिभाषय GL_NV_polygon_बहुलकम् 1
#परिभाषय GL_POLYGON_बहुलकम्_NV                0x0B40
#परिभाषय GL_POLYGON_विस्थापनम्_POINT_NV        0x2A01
#परिभाषय GL_POLYGON_विस्थापनम्_पङ्क्तिः_NV         0x2A02
#परिभाषय GL_POINT_NV                       0x1B00
#परिभाषय GL_पङ्क्तिः_NV                        0x1B01
#परिभाषय GL_FILL_NV                        0x1B02
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPOLYGONMODENVPROC) (GLenum face, GLenum बहुलकम्);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_Polygon_बहुलकम्_NV (GLenum face, GLenum बहुलकम्);
#यदि_अन्तः
#यदि_अन्तः /* GL_NV_polygon_mode */

#यदि_अपरिभाषितम् GL_NV_primitive_shading_दरः
#परिभाषय GL_NV_primitive_shading_दरः 1
#परिभाषय GL_SHADING_दरः_IMAGE_प्रत्येकम्_PRIMITIVE_NV 0x95B1
#परिभाषय GL_SHADING_दरः_IMAGE_PALETTE_गणनम्_NV 0x95B2
#यदि_अन्तः /* GL_NV_primitive_shading_rate */

#यदि_अपरिभाषितम् GL_NV_read_बफर
#परिभाषय GL_NV_read_बफर 1
#परिभाषय GL_READ_बफर_NV                 0x0C02
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLREADBUFFERNVPROC) (GLenum बहुलकम्);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_Read_बफर_NV (GLenum बहुलकम्);
#यदि_अन्तः
#यदि_अन्तः /* GL_NV_read_buffer */

#यदि_अपरिभाषितम् GL_NV_read_बफर_front
#परिभाषय GL_NV_read_बफर_front 1
#यदि_अन्तः /* GL_NV_read_buffer_front */

#यदि_अपरिभाषितम् GL_NV_read_गभीरता
#परिभाषय GL_NV_read_गभीरता 1
#यदि_अन्तः /* GL_NV_read_depth */

#यदि_अपरिभाषितम् GL_NV_read_गभीरता_stencil
#परिभाषय GL_NV_read_गभीरता_stencil 1
#यदि_अन्तः /* GL_NV_read_depth_stencil */

#यदि_अपरिभाषितम् GL_NV_read_stencil
#परिभाषय GL_NV_read_stencil 1
#यदि_अन्तः /* GL_NV_read_stencil */

#यदि_अपरिभाषितम् GL_NV_representative_fragment_test
#परिभाषय GL_NV_representative_fragment_test 1
#परिभाषय GL_REPRESENTATIVE_FRAGMENT_TEST_NV 0x937F
#यदि_अन्तः /* GL_NV_representative_fragment_test */

#यदि_अपरिभाषितम् GL_NV_sRGB_formats
#परिभाषय GL_NV_sRGB_formats 1
#परिभाषय GL_SLUMINANCE_NV                  0x8C46
#परिभाषय GL_SLUMINANCE_ALPHA_NV            0x8C44
#परिभाषय GL_SRGB8_NV                       0x8C41
#परिभाषय GL_SLUMINANCE8_NV                 0x8C47
#परिभाषय GL_SLUMINANCE8_ALPHA8_NV          0x8C45
#परिभाषय GL_COMPRESSED_SRGB_S3TC_DXT1_NV   0x8C4C
#परिभाषय GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_NV 0x8C4D
#परिभाषय GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_NV 0x8C4E
#परिभाषय GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_NV 0x8C4F
#परिभाषय GL_ETC1_SRGB8_NV                  0x88EE
#यदि_अन्तः /* GL_NV_sRGB_formats */

#यदि_अपरिभाषितम् GL_NV_sample_locations
#परिभाषय GL_NV_sample_locations 1
#परिभाषय GL_SAMPLE_LOCATION_SUBPIXEL_द्वयङ्काः_NV 0x933D
#परिभाषय GL_SAMPLE_LOCATION_PIXEL_GRID_विस्तारः_NV 0x933E
#परिभाषय GL_SAMPLE_LOCATION_PIXEL_GRID_HEIGHT_NV 0x933F
#परिभाषय GL_PROGRAMMABLE_SAMPLE_LOCATION_सारणी_आकार_NV 0x9340
#परिभाषय GL_SAMPLE_LOCATION_NV             0x8E50
#परिभाषय GL_PROGRAMMABLE_SAMPLE_LOCATION_NV 0x9341
#परिभाषय GL_FRAMEBUFFER_PROGRAMMABLE_SAMPLE_LOCATIONS_NV 0x9342
#परिभाषय GL_FRAMEBUFFER_SAMPLE_LOCATION_PIXEL_GRID_NV 0x9343
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFRAMEBUFFERSAMPLELOCATIONSFVNVPROC) (GLenum target, GLuint start, GLsizei गणनम्, ध्रुव GLfloat *v);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVNVPROC) (GLuint framebuffer, GLuint start, GLsizei गणनम्, ध्रुव GLfloat *v);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLRESOLVEDEPTHVALUESNVPROC) (शून्य);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glFramebufferSampleLocationsfvNV (GLenum target, GLuint start, GLsizei गणनम्, ध्रुव GLfloat *v);
GL_APICALL शून्य GL_APIENTRY glNamedFramebufferSampleLocationsfvNV (GLuint framebuffer, GLuint start, GLsizei गणनम्, ध्रुव GLfloat *v);
GL_APICALL शून्य GL_APIENTRY gl_Resolve_गभीरता_मानानि_NV (शून्य);
#यदि_अन्तः
#यदि_अन्तः /* GL_NV_sample_locations */

#यदि_अपरिभाषितम् GL_NV_sample_आवरणम्_override_coverage
#परिभाषय GL_NV_sample_आवरणम्_override_coverage 1
#यदि_अन्तः /* GL_NV_sample_mask_override_coverage */

#यदि_अपरिभाषितम् GL_NV_scissor_exclusive
#परिभाषय GL_NV_scissor_exclusive 1
#परिभाषय GL_SCISSOR_TEST_EXCLUSIVE_NV      0x9555
#परिभाषय GL_SCISSOR_BOX_EXCLUSIVE_NV       0x9556
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSCISSOREXCLUSIVENVPROC) (GLint x, GLint y, GLsizei विस्तारः, GLsizei height);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSCISSOREXCLUSIVEARRAYVNVPROC) (GLuint first, GLsizei गणनम्, ध्रुव GLint *v);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glScissorExclusiveNV (GLint x, GLint y, GLsizei विस्तारः, GLsizei height);
GL_APICALL शून्य GL_APIENTRY glScissorExclusiveArrayvNV (GLuint first, GLsizei गणनम्, ध्रुव GLint *v);
#यदि_अन्तः
#यदि_अन्तः /* GL_NV_scissor_exclusive */

#यदि_अपरिभाषितम् GL_NV_shader_atomic_fp16_सदिशम्
#परिभाषय GL_NV_shader_atomic_fp16_सदिशम् 1
#यदि_अन्तः /* GL_NV_shader_atomic_fp16_vector */

#यदि_अपरिभाषितम् GL_NV_shader_noperspective_interpolation
#परिभाषय GL_NV_shader_noperspective_interpolation 1
#यदि_अन्तः /* GL_NV_shader_noperspective_interpolation */

#यदि_अपरिभाषितम् GL_NV_shader_subgroup_partitioned
#परिभाषय GL_NV_shader_subgroup_partitioned 1
#परिभाषय GL_SUBGROUP_FEATURE_PARTITIONED_BIT_NV 0x00000100
#यदि_अन्तः /* GL_NV_shader_subgroup_partitioned */

#यदि_अपरिभाषितम् GL_NV_shader_texture_footprint
#परिभाषय GL_NV_shader_texture_footprint 1
#यदि_अन्तः /* GL_NV_shader_texture_footprint */

#यदि_अपरिभाषितम् GL_NV_shading_दरः_image
#परिभाषय GL_NV_shading_दरः_image 1
#परिभाषय GL_SHADING_दरः_IMAGE_NV          0x9563
#परिभाषय GL_SHADING_दरः_NO_INVOCATIONS_NV 0x9564
#परिभाषय GL_SHADING_दरः_1_INVOCATION_प्रत्येकम्_PIXEL_NV 0x9565
#परिभाषय GL_SHADING_दरः_1_INVOCATION_प्रत्येकम्_1_X2_PIXELS_NV 0x9566
#परिभाषय GL_SHADING_दरः_1_INVOCATION_प्रत्येकम्_2_X1_PIXELS_NV 0x9567
#परिभाषय GL_SHADING_दरः_1_INVOCATION_प्रत्येकम्_2_X2_PIXELS_NV 0x9568
#परिभाषय GL_SHADING_दरः_1_INVOCATION_प्रत्येकम्_2_X4_PIXELS_NV 0x9569
#परिभाषय GL_SHADING_दरः_1_INVOCATION_प्रत्येकम्_4_X2_PIXELS_NV 0x956A
#परिभाषय GL_SHADING_दरः_1_INVOCATION_प्रत्येकम्_4_X4_PIXELS_NV 0x956B
#परिभाषय GL_SHADING_दरः_2_INVOCATIONS_प्रत्येकम्_PIXEL_NV 0x956C
#परिभाषय GL_SHADING_दरः_4_INVOCATIONS_प्रत्येकम्_PIXEL_NV 0x956D
#परिभाषय GL_SHADING_दरः_8_INVOCATIONS_प्रत्येकम्_PIXEL_NV 0x956E
#परिभाषय GL_SHADING_दरः_16_INVOCATIONS_प्रत्येकम्_PIXEL_NV 0x956F
#परिभाषय GL_SHADING_दरः_IMAGE_BINDING_NV  0x955B
#परिभाषय GL_SHADING_दरः_IMAGE_TEXEL_विस्तारः_NV 0x955C
#परिभाषय GL_SHADING_दरः_IMAGE_TEXEL_HEIGHT_NV 0x955D
#परिभाषय GL_SHADING_दरः_IMAGE_PALETTE_आकार_NV 0x955E
#परिभाषय GL_MAX_COARSE_FRAGMENT_SAMPLES_NV 0x955F
#परिभाषय GL_SHADING_दरः_SAMPLE_क्रमः_DEFAULT_NV 0x95AE
#परिभाषय GL_SHADING_दरः_SAMPLE_क्रमः_PIXEL_MAJOR_NV 0x95AF
#परिभाषय GL_SHADING_दरः_SAMPLE_क्रमः_SAMPLE_MAJOR_NV 0x95B0
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBINDSHADINGRATEIMAGENVPROC) (GLuint texture);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETSHADINGRATEIMAGEPALETTENVPROC) (GLuint viewport, GLuint प्रविष्टिः, GLenum *दरः);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETSHADINGRATESAMPLELOCATIONIVNVPROC) (GLenum दरः, GLuint samples, GLuint सूचकांक, GLint *location);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSHADINGRATEIMAGEBARRIERNVPROC) (GLboolean synchronize);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSHADINGRATEIMAGEPALETTENVPROC) (GLuint viewport, GLuint first, GLsizei गणनम्, ध्रुव GLenum *rates);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSHADINGRATESAMPLEORDERNVPROC) (GLenum क्रमः);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSHADINGRATESAMPLEORDERCUSTOMNVPROC) (GLenum दरः, GLuint samples, ध्रुव GLint *locations);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_Bind_Shading_दरः_Image_NV (GLuint texture);
GL_APICALL शून्य GL_APIENTRY gl_Get_Shading_दरः_Image_Palette_NV (GLuint viewport, GLuint प्रविष्टिः, GLenum *दरः);
GL_APICALL शून्य GL_APIENTRY gl_Get_Shading_दरः_Sample_Locationiv_NV (GLenum दरः, GLuint samples, GLuint सूचकांक, GLint *location);
GL_APICALL शून्य GL_APIENTRY gl_Shading_दरः_Image_Barrier_NV (GLboolean synchronize);
GL_APICALL शून्य GL_APIENTRY gl_Shading_दरः_Image_Palette_NV (GLuint viewport, GLuint first, GLsizei गणनम्, ध्रुव GLenum *rates);
GL_APICALL शून्य GL_APIENTRY gl_Shading_दरः_Sample_क्रमः_NV (GLenum क्रमः);
GL_APICALL शून्य GL_APIENTRY gl_Shading_दरः_Sample_क्रमः_Custom_NV (GLenum दरः, GLuint samples, ध्रुव GLint *locations);
#यदि_अन्तः
#यदि_अन्तः /* GL_NV_shading_rate_image */

#यदि_अपरिभाषितम् GL_NV_shadow_samplers_array
#परिभाषय GL_NV_shadow_samplers_array 1
#परिभाषय GL_SAMPLER_2D_ARRAY_SHADOW_NV     0x8DC4
#यदि_अन्तः /* GL_NV_shadow_samplers_array */

#यदि_अपरिभाषितम् GL_NV_shadow_samplers_cube
#परिभाषय GL_NV_shadow_samplers_cube 1
#परिभाषय GL_SAMPLER_CUBE_SHADOW_NV         0x8DC5
#यदि_अन्तः /* GL_NV_shadow_samplers_cube */

#यदि_अपरिभाषितम् GL_NV_stereo_view_rendering
#परिभाषय GL_NV_stereo_view_rendering 1
#यदि_अन्तः /* GL_NV_stereo_view_rendering */

#यदि_अपरिभाषितम् GL_NV_texture_barrier
#परिभाषय GL_NV_texture_barrier 1
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXTUREBARRIERNVPROC) (शून्य);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glTextureBarrierNV (शून्य);
#यदि_अन्तः
#यदि_अन्तः /* GL_NV_texture_barrier */

#यदि_अपरिभाषितम् GL_NV_texture_border_clamp
#परिभाषय GL_NV_texture_border_clamp 1
#परिभाषय GL_TEXTURE_BORDER_COLOR_NV        0x1004
#परिभाषय GL_CLAMP_गन्तव्यम्_BORDER_NV             0x812D
#यदि_अन्तः /* GL_NV_texture_border_clamp */

#यदि_अपरिभाषितम् GL_NV_texture_compression_s3tc_update
#परिभाषय GL_NV_texture_compression_s3tc_update 1
#यदि_अन्तः /* GL_NV_texture_compression_s3tc_update */

#यदि_अपरिभाषितम् GL_NV_texture_npot_2D_mipmap
#परिभाषय GL_NV_texture_npot_2D_mipmap 1
#यदि_अन्तः /* GL_NV_texture_npot_2D_mipmap */

#यदि_अपरिभाषितम् GL_NV_timeline_semaphore
#परिभाषय GL_NV_timeline_semaphore 1
#परिभाषय GL_TIMELINE_SEMAPHORE_मानम्_NV    0x9595
#परिभाषय GL_SEMAPHORE_TYPE_NV              0x95B3
#परिभाषय GL_SEMAPHORE_TYPE_द्विमान_NV       0x95B4
#परिभाषय GL_SEMAPHORE_TYPE_TIMELINE_NV     0x95B5
#परिभाषय GL_MAX_TIMELINE_SEMAPHORE_मानम्_DIFFERENCE_NV 0x95B6
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCREATESEMAPHORESNVPROC) (GLsizei n, GLuint *semaphores);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSEMAPHOREPARAMETERIVNVPROC) (GLuint semaphore, GLenum pname, ध्रुव GLint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETSEMAPHOREPARAMETERIVNVPROC) (GLuint semaphore, GLenum pname, GLint *params);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glCreateSemaphoresNV (GLsizei n, GLuint *semaphores);
GL_APICALL शून्य GL_APIENTRY glSemaphoreParameterivNV (GLuint semaphore, GLenum pname, ध्रुव GLint *params);
GL_APICALL शून्य GL_APIENTRY glGetSemaphoreParameterivNV (GLuint semaphore, GLenum pname, GLint *params);
#यदि_अन्तः
#यदि_अन्तः /* GL_NV_timeline_semaphore */

#यदि_अपरिभाषितम् GL_NV_viewport_array
#परिभाषय GL_NV_viewport_array 1
#परिभाषय GL_MAX_VIEWPORTS_NV               0x825B
#परिभाषय GL_VIEWPORT_SUBPIXEL_द्वयङ्काः_NV      0x825C
#परिभाषय GL_VIEWPORT_BOUNDS_RANGE_NV       0x825D
#परिभाषय GL_VIEWPORT_सूचकांक_PROVOKING_VERTEX_NV 0x825F
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLVIEWPORTARRAYVNVPROC) (GLuint first, GLsizei गणनम्, ध्रुव GLfloat *v);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLVIEWPORTINDEXEDFNVPROC) (GLuint सूचकांक, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLVIEWPORTINDEXEDFVNVPROC) (GLuint सूचकांक, ध्रुव GLfloat *v);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSCISSORARRAYVNVPROC) (GLuint first, GLsizei गणनम्, ध्रुव GLint *v);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSCISSORINDEXEDNVPROC) (GLuint सूचकांक, GLint वामः, GLint bottom, GLsizei विस्तारः, GLsizei height);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSCISSORINDEXEDVNVPROC) (GLuint सूचकांक, ध्रुव GLint *v);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDEPTHRANGEARRAYFVNVPROC) (GLuint first, GLsizei गणनम्, ध्रुव GLfloat *v);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDEPTHRANGEINDEXEDFNVPROC) (GLuint सूचकांक, GLfloat n, GLfloat f);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETFLOATI_VNVPROC) (GLenum target, GLuint सूचकांक, GLfloat *दत्त);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLENABLEINVPROC) (GLenum target, GLuint सूचकांक);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDISABLEINVPROC) (GLenum target, GLuint सूचकांक);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLISENABLEDINVPROC) (GLenum target, GLuint सूचकांक);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glViewportArrayvNV (GLuint first, GLsizei गणनम्, ध्रुव GLfloat *v);
GL_APICALL शून्य GL_APIENTRY glViewportIndexedfNV (GLuint सूचकांक, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
GL_APICALL शून्य GL_APIENTRY glViewportIndexedfvNV (GLuint सूचकांक, ध्रुव GLfloat *v);
GL_APICALL शून्य GL_APIENTRY glScissorArrayvNV (GLuint first, GLsizei गणनम्, ध्रुव GLint *v);
GL_APICALL शून्य GL_APIENTRY gl_Scissor_अनुक्रमितम्_NV (GLuint सूचकांक, GLint वामः, GLint bottom, GLsizei विस्तारः, GLsizei height);
GL_APICALL शून्य GL_APIENTRY glScissorIndexedvNV (GLuint सूचकांक, ध्रुव GLint *v);
GL_APICALL शून्य GL_APIENTRY gl_गभीरता_Range_Arrayfv_NV (GLuint first, GLsizei गणनम्, ध्रुव GLfloat *v);
GL_APICALL शून्य GL_APIENTRY gl_गभीरता_Range_Indexedf_NV (GLuint सूचकांक, GLfloat n, GLfloat f);
GL_APICALL शून्य GL_APIENTRY glGetFloati_vNV (GLenum target, GLuint सूचकांक, GLfloat *दत्त);
GL_APICALL शून्य GL_APIENTRY glEnableiNV (GLenum target, GLuint सूचकांक);
GL_APICALL शून्य GL_APIENTRY glDisableiNV (GLenum target, GLuint सूचकांक);
GL_APICALL GLboolean GL_APIENTRY glIsEnablediNV (GLenum target, GLuint सूचकांक);
#यदि_अन्तः
#यदि_अन्तः /* GL_NV_viewport_array */

#यदि_अपरिभाषितम् GL_NV_viewport_array2
#परिभाषय GL_NV_viewport_array2 1
#यदि_अन्तः /* GL_NV_viewport_array2 */

#यदि_अपरिभाषितम् GL_NV_viewport_swizzle
#परिभाषय GL_NV_viewport_swizzle 1
#परिभाषय GL_VIEWPORT_SWIZZLE_धनात्मकम्_X_NV 0x9350
#परिभाषय GL_VIEWPORT_SWIZZLE_NEGATIVE_X_NV 0x9351
#परिभाषय GL_VIEWPORT_SWIZZLE_धनात्मकम्_Y_NV 0x9352
#परिभाषय GL_VIEWPORT_SWIZZLE_NEGATIVE_Y_NV 0x9353
#परिभाषय GL_VIEWPORT_SWIZZLE_धनात्मकम्_Z_NV 0x9354
#परिभाषय GL_VIEWPORT_SWIZZLE_NEGATIVE_Z_NV 0x9355
#परिभाषय GL_VIEWPORT_SWIZZLE_धनात्मकम्_W_NV 0x9356
#परिभाषय GL_VIEWPORT_SWIZZLE_NEGATIVE_W_NV 0x9357
#परिभाषय GL_VIEWPORT_SWIZZLE_X_NV          0x9358
#परिभाषय GL_VIEWPORT_SWIZZLE_Y_NV          0x9359
#परिभाषय GL_VIEWPORT_SWIZZLE_Z_NV          0x935A
#परिभाषय GL_VIEWPORT_SWIZZLE_W_NV          0x935B
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLVIEWPORTSWIZZLENVPROC) (GLuint सूचकांक, GLenum swizzlex, GLenum swizzley, GLenum swizzlez, GLenum swizzlew);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glViewportSwizzleNV (GLuint सूचकांक, GLenum swizzlex, GLenum swizzley, GLenum swizzlez, GLenum swizzlew);
#यदि_अन्तः
#यदि_अन्तः /* GL_NV_viewport_swizzle */

#यदि_अपरिभाषितम् GL_OVR_multiview
#परिभाषय GL_OVR_multiview 1
#परिभाषय GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_अङ्कः_VIEWS_OVR 0x9630
#परिभाषय GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_आधारः_VIEW_सूचकांक_OVR 0x9632
#परिभाषय GL_MAX_VIEWS_OVR                  0x9631
#परिभाषय GL_FRAMEBUFFER_INCOMPLETE_VIEW_TARGETS_OVR 0x9633
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREMULTIVIEWOVRPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint आधारः_View_सूचकांक, GLsizei अङ्कः_Views_2);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLNAMEDFRAMEBUFFERTEXTUREMULTIVIEWOVRPROC) (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint आधारः_View_सूचकांक, GLsizei अङ्कः_Views_2);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glFramebufferTextureMultiviewOVR (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint आधारः_View_सूचकांक, GLsizei अङ्कः_Views_2);
GL_APICALL शून्य GL_APIENTRY glNamedFramebufferTextureMultiviewOVR (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint आधारः_View_सूचकांक, GLsizei अङ्कः_Views_2);
#यदि_अन्तः
#यदि_अन्तः /* GL_OVR_multiview */

#यदि_अपरिभाषितम् GL_OVR_multiview2
#परिभाषय GL_OVR_multiview2 1
#यदि_अन्तः /* GL_OVR_multiview2 */

#यदि_अपरिभाषितम् GL_OVR_multiview_multisampled_render_गन्तव्यम्_texture
#परिभाषय GL_OVR_multiview_multisampled_render_गन्तव्यम्_texture 1
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREMULTISAMPLEMULTIVIEWOVRPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLsizei samples, GLint आधारः_View_सूचकांक, GLsizei अङ्कः_Views_2);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glFramebufferTextureMultisampleMultiviewOVR (GLenum target, GLenum attachment, GLuint texture, GLint level, GLsizei samples, GLint आधारः_View_सूचकांक, GLsizei अङ्कः_Views_2);
#यदि_अन्तः
#यदि_अन्तः /* GL_OVR_multiview_multisampled_render_to_texture */

#यदि_अपरिभाषितम् GL_QCOM_YUV_texture_gather
#परिभाषय GL_QCOM_YUV_texture_gather 1
#यदि_अन्तः /* GL_QCOM_YUV_texture_gather */

#यदि_अपरिभाषितम् GL_QCOM_alpha_test
#परिभाषय GL_QCOM_alpha_test 1
#परिभाषय GL_ALPHA_TEST_QCOM                0x0BC0
#परिभाषय GL_ALPHA_TEST_FUNC_QCOM           0x0BC1
#परिभाषय GL_ALPHA_TEST_REF_QCOM            0x0BC2
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLALPHAFUNCQCOMPROC) (GLenum func, GLclampf ref);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glAlphaFuncQCOM (GLenum func, GLclampf ref);
#यदि_अन्तः
#यदि_अन्तः /* GL_QCOM_alpha_test */

#यदि_अपरिभाषितम् GL_QCOM_binning_control
#परिभाषय GL_QCOM_binning_control 1
#परिभाषय GL_BINNING_CONTROL_HINT_QCOM      0x8FB0
#परिभाषय GL_CPU_OPTIMIZED_QCOM             0x8FB1
#परिभाषय GL_GPU_OPTIMIZED_QCOM             0x8FB2
#परिभाषय GL_RENDER_प्रत्यक्षम्_गन्तव्यम्_FRAMEBUFFER_QCOM 0x8FB3
#यदि_अन्तः /* GL_QCOM_binning_control */

#यदि_अपरिभाषितम् GL_QCOM_driver_control
#परिभाषय GL_QCOM_driver_control 1
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETDRIVERCONTROLSQCOMPROC) (GLint *अङ्कः, GLsizei आकार, GLuint *driverControls);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETDRIVERCONTROLSTRINGQCOMPROC) (GLuint driverControl, GLsizei buf_आकार, GLsizei *दीर्घता, GLchar *driverControlString);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLENABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDISABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glGetDriverControlsQCOM (GLint *अङ्कः, GLsizei आकार, GLuint *driverControls);
GL_APICALL शून्य GL_APIENTRY glGetDriverControlStringQCOM (GLuint driverControl, GLsizei buf_आकार, GLsizei *दीर्घता, GLchar *driverControlString);
GL_APICALL शून्य GL_APIENTRY glEnableDriverControlQCOM (GLuint driverControl);
GL_APICALL शून्य GL_APIENTRY glDisableDriverControlQCOM (GLuint driverControl);
#यदि_अन्तः
#यदि_अन्तः /* GL_QCOM_driver_control */

#यदि_अपरिभाषितम् GL_QCOM_extended_get
#परिभाषय GL_QCOM_extended_get 1
#परिभाषय GL_TEXTURE_विस्तारः_QCOM             0x8BD2
#परिभाषय GL_TEXTURE_HEIGHT_QCOM            0x8BD3
#परिभाषय GL_TEXTURE_गभीरता_QCOM             0x8BD4
#परिभाषय GL_TEXTURE_आन्तरिकम्_FORMAT_QCOM   0x8BD5
#परिभाषय GL_TEXTURE_FORMAT_QCOM            0x8BD6
#परिभाषय GL_TEXTURE_TYPE_QCOM              0x8BD7
#परिभाषय GL_TEXTURE_IMAGE_VALID_QCOM       0x8BD8
#परिभाषय GL_TEXTURE_अङ्कः_स्तराः_QCOM        0x8BD9
#परिभाषय GL_TEXTURE_TARGET_QCOM            0x8BDA
#परिभाषय GL_TEXTURE_OBJECT_VALID_QCOM      0x8BDB
#परिभाषय GL_STATE_RESTORE                  0x8BDC
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLEXTGETTEXTURESQCOMPROC) (GLuint *textures, GLint maxTextures, GLint *अङ्कः_Textures);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLEXTGETBUFFERSQCOMPROC) (GLuint *buffers, GLint maxBuffers, GLint *अङ्कः_Buffers);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLEXTGETRENDERBUFFERSQCOMPROC) (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *अङ्कः_Renderbuffers);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLEXTGETFRAMEBUFFERSQCOMPROC) (GLuint *framebuffers, GLint maxFramebuffers, GLint *अङ्कः_Framebuffers);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLEXTGETTEXLEVELPARAMETERIVQCOMPROC) (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLEXTTEXOBJECTSTATEOVERRIDEIQCOMPROC) (GLenum target, GLenum pname, GLint param);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLEXTGETTEXSUBIMAGEQCOMPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2, GLenum format, GLenum type, शून्य *texels);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLEXTGETBUFFERPOINTERVQCOMPROC) (GLenum target, शून्य **params);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glExtGetTexturesQCOM (GLuint *textures, GLint maxTextures, GLint *अङ्कः_Textures);
GL_APICALL शून्य GL_APIENTRY glExtGetBuffersQCOM (GLuint *buffers, GLint maxBuffers, GLint *अङ्कः_Buffers);
GL_APICALL शून्य GL_APIENTRY glExtGetRenderbuffersQCOM (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *अङ्कः_Renderbuffers);
GL_APICALL शून्य GL_APIENTRY glExtGetFramebuffersQCOM (GLuint *framebuffers, GLint maxFramebuffers, GLint *अङ्कः_Framebuffers);
GL_APICALL शून्य GL_APIENTRY glExtGetTexLevelParameterivQCOM (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
GL_APICALL शून्य GL_APIENTRY glExtTexObjectStateOverrideiQCOM (GLenum target, GLenum pname, GLint param);
GL_APICALL शून्य GL_APIENTRY glExtGetTexSubImageQCOM (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2, GLenum format, GLenum type, शून्य *texels);
GL_APICALL शून्य GL_APIENTRY gl_Ext_Get_बफर_Pointerv_QCOM (GLenum target, शून्य **params);
#यदि_अन्तः
#यदि_अन्तः /* GL_QCOM_extended_get */

#यदि_अपरिभाषितम् GL_QCOM_extended_get2
#परिभाषय GL_QCOM_extended_get2 1
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLEXTGETSHADERSQCOMPROC) (GLuint *shaders, GLint maxShaders, GLint *अङ्कः_Shaders);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLEXTGETPROGRAMSQCOMPROC) (GLuint *programs, GLint maxPrograms, GLint *अङ्कः_Programs);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLEXTISPROGRAMBINARYQCOMPROC) (GLuint क्रमादेशः);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLEXTGETPROGRAMBINARYSOURCEQCOMPROC) (GLuint क्रमादेशः, GLenum shadertype, GLchar *source, GLint *दीर्घता);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glExtGetShadersQCOM (GLuint *shaders, GLint maxShaders, GLint *अङ्कः_Shaders);
GL_APICALL शून्य GL_APIENTRY glExtGetProgramsQCOM (GLuint *programs, GLint maxPrograms, GLint *अङ्कः_Programs);
GL_APICALL GLboolean GL_APIENTRY gl_Ext_Is_क्रमादेशः_द्विमान_QCOM (GLuint क्रमादेशः);
GL_APICALL शून्य GL_APIENTRY gl_Ext_Get_क्रमादेशः_द्विमान_Source_QCOM (GLuint क्रमादेशः, GLenum shadertype, GLchar *source, GLint *दीर्घता);
#यदि_अन्तः
#यदि_अन्तः /* GL_QCOM_extended_get2 */

#यदि_अपरिभाषितम् GL_QCOM_frame_extrapolation
#परिभाषय GL_QCOM_frame_extrapolation 1
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLEXTRAPOLATETEX2DQCOMPROC) (GLuint src1, GLuint src2, GLuint output, GLfloat scale_गुणकः);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glExtrapolateTex2DQCOM (GLuint src1, GLuint src2, GLuint output, GLfloat scale_गुणकः);
#यदि_अन्तः
#यदि_अन्तः /* GL_QCOM_frame_extrapolation */

#यदि_अपरिभाषितम् GL_QCOM_framebuffer_foveated
#परिभाषय GL_QCOM_framebuffer_foveated 1
#परिभाषय GL_FOVEATION_ENABLE_BIT_QCOM      0x00000001
#परिभाषय GL_FOVEATION_SCALED_BIN_विधानम्_BIT_QCOM 0x00000002
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFRAMEBUFFERFOVEATIONCONFIGQCOMPROC) (GLuint framebuffer, GLuint अङ्कः_Layers, GLuint focal_Points_प्रत्येकम्_Layer, GLuint requestedFeatures, GLuint *providedFeatures);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFRAMEBUFFERFOVEATIONPARAMETERSQCOMPROC) (GLuint framebuffer, GLuint layer, GLuint focalPoint, GLfloat focalX, GLfloat focalY, GLfloat gainX, GLfloat gainY, GLfloat foveaArea);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glFramebufferFoveationConfigQCOM (GLuint framebuffer, GLuint अङ्कः_Layers, GLuint focal_Points_प्रत्येकम्_Layer, GLuint requestedFeatures, GLuint *providedFeatures);
GL_APICALL शून्य GL_APIENTRY glFramebufferFoveationParametersQCOM (GLuint framebuffer, GLuint layer, GLuint focalPoint, GLfloat focalX, GLfloat focalY, GLfloat gainX, GLfloat gainY, GLfloat foveaArea);
#यदि_अन्तः
#यदि_अन्तः /* GL_QCOM_framebuffer_foveated */

#यदि_अपरिभाषितम् GL_QCOM_motion_estimation
#परिभाषय GL_QCOM_motion_estimation 1
#परिभाषय GL_MOTION_ESTIMATION_अन्वेषणम्_खण्डम्_X_QCOM 0x8C90
#परिभाषय GL_MOTION_ESTIMATION_अन्वेषणम्_खण्डम्_Y_QCOM 0x8C91
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXESTIMATEMOTIONQCOMPROC) (GLuint ref, GLuint target, GLuint output);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXESTIMATEMOTIONREGIONSQCOMPROC) (GLuint ref, GLuint target, GLuint output, GLuint आवरणम्);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glTexEstimateMotionQCOM (GLuint ref, GLuint target, GLuint output);
GL_APICALL शून्य GL_APIENTRY glTexEstimateMotionRegionsQCOM (GLuint ref, GLuint target, GLuint output, GLuint आवरणम्);
#यदि_अन्तः
#यदि_अन्तः /* GL_QCOM_motion_estimation */

#यदि_अपरिभाषितम् GL_QCOM_perfmon_global_बहुलकम्
#परिभाषय GL_QCOM_perfmon_global_बहुलकम् 1
#परिभाषय GL_PERFMON_GLOBAL_बहुलकम्_QCOM       0x8FA0
#यदि_अन्तः /* GL_QCOM_perfmon_global_mode */

#यदि_अपरिभाषितम् GL_QCOM_render_sRGB_R8_RG8
#परिभाषय GL_QCOM_render_sRGB_R8_RG8 1
#यदि_अन्तः /* GL_QCOM_render_sRGB_R8_RG8 */

#यदि_अपरिभाषितम् GL_QCOM_render_shared_exponent
#परिभाषय GL_QCOM_render_shared_exponent 1
#यदि_अन्तः /* GL_QCOM_render_shared_exponent */

#यदि_अपरिभाषितम् GL_QCOM_shader_framebuffer_fetch_noncoherent
#परिभाषय GL_QCOM_shader_framebuffer_fetch_noncoherent 1
#परिभाषय GL_FRAMEBUFFER_FETCH_NONCOHERENT_QCOM 0x96A2
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFRAMEBUFFERFETCHBARRIERQCOMPROC) (शून्य);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glFramebufferFetchBarrierQCOM (शून्य);
#यदि_अन्तः
#यदि_अन्तः /* GL_QCOM_shader_framebuffer_fetch_noncoherent */

#यदि_अपरिभाषितम् GL_QCOM_shader_framebuffer_fetch_दरः
#परिभाषय GL_QCOM_shader_framebuffer_fetch_दरः 1
#यदि_अन्तः /* GL_QCOM_shader_framebuffer_fetch_rate */

#यदि_अपरिभाषितम् GL_QCOM_shading_दरः
#परिभाषय GL_QCOM_shading_दरः 1
#परिभाषय GL_SHADING_दरः_QCOM              0x96A4
#परिभाषय GL_SHADING_दरः_PRESERVE_ASPECT_अनुपातः_QCOM 0x96A5
#परिभाषय GL_SHADING_दरः_1_X1_PIXELS_QCOM   0x96A6
#परिभाषय GL_SHADING_दरः_1_X2_PIXELS_QCOM   0x96A7
#परिभाषय GL_SHADING_दरः_2_X1_PIXELS_QCOM   0x96A8
#परिभाषय GL_SHADING_दरः_2_X2_PIXELS_QCOM   0x96A9
#परिभाषय GL_SHADING_दरः_4_X2_PIXELS_QCOM   0x96AC
#परिभाषय GL_SHADING_दरः_4_X4_PIXELS_QCOM   0x96AE
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSHADINGRATEQCOMPROC) (GLenum दरः);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_Shading_दरः_QCOM (GLenum दरः);
#यदि_अन्तः
#यदि_अन्तः /* GL_QCOM_shading_rate */

#यदि_अपरिभाषितम् GL_QCOM_texture_foveated
#परिभाषय GL_QCOM_texture_foveated 1
#परिभाषय GL_TEXTURE_FOVEATED_FEATURE_द्वयङ्काः_QCOM 0x8BFB
#परिभाषय GL_TEXTURE_FOVEATED_MIN_PIXEL_DENSITY_QCOM 0x8BFC
#परिभाषय GL_TEXTURE_FOVEATED_FEATURE_QUERY_QCOM 0x8BFD
#परिभाषय GL_TEXTURE_FOVEATED_अङ्कः_FOCAL_POINTS_QUERY_QCOM 0x8BFE
#परिभाषय GL_FRAMEBUFFER_INCOMPLETE_FOVEATION_QCOM 0x8BFF
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXTUREFOVEATIONPARAMETERSQCOMPROC) (GLuint texture, GLuint layer, GLuint focalPoint, GLfloat focalX, GLfloat focalY, GLfloat gainX, GLfloat gainY, GLfloat foveaArea);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glTextureFoveationParametersQCOM (GLuint texture, GLuint layer, GLuint focalPoint, GLfloat focalX, GLfloat focalY, GLfloat gainX, GLfloat gainY, GLfloat foveaArea);
#यदि_अन्तः
#यदि_अन्तः /* GL_QCOM_texture_foveated */

#यदि_अपरिभाषितम् GL_QCOM_texture_foveated2
#परिभाषय GL_QCOM_texture_foveated2 1
#परिभाषय GL_TEXTURE_FOVEATED_CUTOFF_DENSITY_QCOM 0x96A0
#यदि_अन्तः /* GL_QCOM_texture_foveated2 */

#यदि_अपरिभाषितम् GL_QCOM_texture_foveated_subsampled_layout
#परिभाषय GL_QCOM_texture_foveated_subsampled_layout 1
#परिभाषय GL_FOVEATION_SUBSAMPLED_LAYOUT_विधानम्_BIT_QCOM 0x00000004
#परिभाषय GL_MAX_SHADER_SUBSAMPLED_IMAGE_UNITS_QCOM 0x8FA1
#यदि_अन्तः /* GL_QCOM_texture_foveated_subsampled_layout */

#यदि_अपरिभाषितम् GL_QCOM_texture_lod_bias
#परिभाषय GL_QCOM_texture_lod_bias 1
#परिभाषय GL_TEXTURE_LOD_BIAS_QCOM          0x8C96
#यदि_अन्तः /* GL_QCOM_texture_lod_bias */

#यदि_अपरिभाषितम् GL_QCOM_tiled_rendering
#परिभाषय GL_QCOM_tiled_rendering 1
#परिभाषय GL_COLOR_बफर_BIT0_QCOM         0x00000001
#परिभाषय GL_COLOR_बफर_BIT1_QCOM         0x00000002
#परिभाषय GL_COLOR_बफर_BIT2_QCOM         0x00000004
#परिभाषय GL_COLOR_बफर_BIT3_QCOM         0x00000008
#परिभाषय GL_COLOR_बफर_BIT4_QCOM         0x00000010
#परिभाषय GL_COLOR_बफर_BIT5_QCOM         0x00000020
#परिभाषय GL_COLOR_बफर_BIT6_QCOM         0x00000040
#परिभाषय GL_COLOR_बफर_BIT7_QCOM         0x00000080
#परिभाषय GL_गभीरता_बफर_BIT0_QCOM         0x00000100
#परिभाषय GL_गभीरता_बफर_BIT1_QCOM         0x00000200
#परिभाषय GL_गभीरता_बफर_BIT2_QCOM         0x00000400
#परिभाषय GL_गभीरता_बफर_BIT3_QCOM         0x00000800
#परिभाषय GL_गभीरता_बफर_BIT4_QCOM         0x00001000
#परिभाषय GL_गभीरता_बफर_BIT5_QCOM         0x00002000
#परिभाषय GL_गभीरता_बफर_BIT6_QCOM         0x00004000
#परिभाषय GL_गभीरता_बफर_BIT7_QCOM         0x00008000
#परिभाषय GL_STENCIL_बफर_BIT0_QCOM       0x00010000
#परिभाषय GL_STENCIL_बफर_BIT1_QCOM       0x00020000
#परिभाषय GL_STENCIL_बफर_BIT2_QCOM       0x00040000
#परिभाषय GL_STENCIL_बफर_BIT3_QCOM       0x00080000
#परिभाषय GL_STENCIL_बफर_BIT4_QCOM       0x00100000
#परिभाषय GL_STENCIL_बफर_BIT5_QCOM       0x00200000
#परिभाषय GL_STENCIL_बफर_BIT6_QCOM       0x00400000
#परिभाषय GL_STENCIL_बफर_BIT7_QCOM       0x00800000
#परिभाषय GL_MULTISAMPLE_बफर_BIT0_QCOM   0x01000000
#परिभाषय GL_MULTISAMPLE_बफर_BIT1_QCOM   0x02000000
#परिभाषय GL_MULTISAMPLE_बफर_BIT2_QCOM   0x04000000
#परिभाषय GL_MULTISAMPLE_बफर_BIT3_QCOM   0x08000000
#परिभाषय GL_MULTISAMPLE_बफर_BIT4_QCOM   0x10000000
#परिभाषय GL_MULTISAMPLE_बफर_BIT5_QCOM   0x20000000
#परिभाषय GL_MULTISAMPLE_बफर_BIT6_QCOM   0x40000000
#परिभाषय GL_MULTISAMPLE_बफर_BIT7_QCOM   0x80000000
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSTARTTILINGQCOMPROC) (GLuint x, GLuint y, GLuint विस्तारः, GLuint height, GLbitfield preserve_आवरणम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLENDTILINGQCOMPROC) (GLbitfield preserve_आवरणम्);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glStartTilingQCOM (GLuint x, GLuint y, GLuint विस्तारः, GLuint height, GLbitfield preserve_आवरणम्);
GL_APICALL शून्य GL_APIENTRY gl_अन्तः_Tiling_QCOM (GLbitfield preserve_आवरणम्);
#यदि_अन्तः
#यदि_अन्तः /* GL_QCOM_tiled_rendering */

#यदि_अपरिभाषितम् GL_QCOM_writeonly_rendering
#परिभाषय GL_QCOM_writeonly_rendering 1
#परिभाषय GL_WRITEONLY_RENDERING_QCOM       0x8823
#यदि_अन्तः /* GL_QCOM_writeonly_rendering */

#यदि_अपरिभाषितम् GL_QCOM_ycbcr_degamma
#परिभाषय GL_QCOM_ycbcr_degamma 1
#परिभाषय GL_TEXTURE_Y_DEGAMMA_QCOM         0x9710
#परिभाषय GL_TEXTURE_CBCR_DEGAMMA_QCOM      0x9711
#यदि_अन्तः /* GL_QCOM_ycbcr_degamma */

#यदि_अपरिभाषितम् GL_VIV_shader_द्विमान
#परिभाषय GL_VIV_shader_द्विमान 1
#परिभाषय GL_SHADER_द्विमान_VIV              0x8FC4
#यदि_अन्तः /* GL_VIV_shader_binary */

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः
