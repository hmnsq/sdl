#अगर_अघोषित __gles2_gl2ext_h_
#घोषणा __gles2_gl2ext_h_ 1

#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर

/*
** Copyright 2013-2026 The Khronos Group Inc.
** SPDX-License-Identifier: MIT
**
** This header is generated from the Khronos OpenGL / OpenGL ES XML
** API Registry. The current version of the Registry, generator scripts
** used to make the header, and the header can be found at
**   https://github.com/KhronosGroup/OpenGL-Registry
*/

#अगर_अघोषित GL_APIENTRYP
#घोषणा GL_APIENTRYP GL_APIENTRY*
#पूर्ण_अगर

#घोषणा GL_GLEXT_VERSION 20260803

/* Generated C header for:
 * API: gles2
 * Profile: common
 * Versions considered: 2\.[0-9]
 * Versions emitted: _nomatch_^
 * Default extensions included: gles2
 * Additional extensions included: _nomatch_^
 * Extensions removed: _nomatch_^
 */

#अगर_अघोषित GL_KHR_blend_equation_advanced
#घोषणा GL_KHR_blend_equation_advanced 1
#घोषणा GL_MULTIPLY_KHR                   0x9294
#घोषणा GL_SCREEN_KHR                     0x9295
#घोषणा GL_OVERLAY_KHR                    0x9296
#घोषणा GL_DARKEN_KHR                     0x9297
#घोषणा GL_LIGHTEN_KHR                    0x9298
#घोषणा GL_COLORDODGE_KHR                 0x9299
#घोषणा GL_COLORBURN_KHR                  0x929A
#घोषणा GL_HARDLIGHT_KHR                  0x929B
#घोषणा GL_SOFTLIGHT_KHR                  0x929C
#घोषणा GL_DIFFERENCE_KHR                 0x929E
#घोषणा GL_EXCLUSION_KHR                  0x92A0
#घोषणा GL_HSL_HUE_KHR                    0x92AD
#घोषणा GL_HSL_SATURATION_KHR             0x92AE
#घोषणा GL_HSL_COLOR_KHR                  0x92AF
#घोषणा GL_HSL_LUMINOSITY_KHR             0x92B0
प्रकार व्योम (GL_APIENTRYP PFNGLBLENDBARRIERKHRPROC) (व्योम);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glBlendBarrierKHR (व्योम);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_KHR_blend_equation_advanced */

#अगर_अघोषित GL_KHR_blend_equation_advanced_coherent
#घोषणा GL_KHR_blend_equation_advanced_coherent 1
#घोषणा GL_BLEND_ADVANCED_COHERENT_KHR    0x9285
#पूर्ण_अगर /* GL_KHR_blend_equation_advanced_coherent */

#अगर_अघोषित GL_KHR_context_flush_control
#घोषणा GL_KHR_context_flush_control 1
#घोषणा GL_CONTEXT_RELEASE_BEHAVIOR_KHR   0x82FB
#घोषणा GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_KHR 0x82FC
#पूर्ण_अगर /* GL_KHR_context_flush_control */

#अगर_अघोषित GL_KHR_debug
#घोषणा GL_KHR_debug 1
प्रकार व्योम (GL_APIENTRY  *GLDEBUGPROCKHR)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei लंबाई,स्थिर GLchar *message,स्थिर व्योम *userParam);
#घोषणा GL_SAMPLER                        0x82E6
#घोषणा GL_DEBUG_OUTPUT_SYNCHRONOUS_KHR   0x8242
#घोषणा GL_DEBUG_अग्र_LOGGED_MESSAGE_लंबाई_KHR 0x8243
#घोषणा GL_DEBUG_CALLBACK_FUNCTION_KHR    0x8244
#घोषणा GL_DEBUG_CALLBACK_USER_PARAM_KHR  0x8245
#घोषणा GL_DEBUG_SOURCE_API_KHR           0x8246
#घोषणा GL_DEBUG_SOURCE_WINDOW_SYSTEM_KHR 0x8247
#घोषणा GL_DEBUG_SOURCE_SHADER_COMPILER_KHR 0x8248
#घोषणा GL_DEBUG_SOURCE_THIRD_PARTY_KHR   0x8249
#घोषणा GL_DEBUG_SOURCE_APPLICATION_KHR   0x824A
#घोषणा GL_DEBUG_SOURCE_OTHER_KHR         0x824B
#घोषणा GL_DEBUG_TYPE_ERROR_KHR           0x824C
#घोषणा GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_KHR 0x824D
#घोषणा GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_KHR 0x824E
#घोषणा GL_DEBUG_TYPE_PORTABILITY_KHR     0x824F
#घोषणा GL_DEBUG_TYPE_PERFORMANCE_KHR     0x8250
#घोषणा GL_DEBUG_TYPE_OTHER_KHR           0x8251
#घोषणा GL_DEBUG_TYPE_MARKER_KHR          0x8268
#घोषणा GL_DEBUG_TYPE_धकेलो_GROUP_KHR      0x8269
#घोषणा GL_DEBUG_TYPE_निकालो_GROUP_KHR       0x826A
#घोषणा GL_DEBUG_SEVERITY_NOTIFICATION_KHR 0x826B
#घोषणा GL_MAX_DEBUG_GROUP_ढेर_DEPTH_KHR 0x826C
#घोषणा GL_DEBUG_GROUP_ढेर_DEPTH_KHR    0x826D
#घोषणा GL_बफर_KHR                     0x82E0
#घोषणा GL_SHADER_KHR                     0x82E1
#घोषणा GL_PROGRAM_KHR                    0x82E2
#घोषणा GL_VERTEX_ARRAY_KHR               0x8074
#घोषणा GL_QUERY_KHR                      0x82E3
#घोषणा GL_PROGRAM_PIPELINE_KHR           0x82E4
#घोषणा GL_SAMPLER_KHR                    0x82E6
#घोषणा GL_MAX_LABEL_लंबाई_KHR           0x82E8
#घोषणा GL_MAX_DEBUG_MESSAGE_लंबाई_KHR   0x9143
#घोषणा GL_MAX_DEBUG_LOGGED_MESSAGES_KHR  0x9144
#घोषणा GL_DEBUG_LOGGED_MESSAGES_KHR      0x9145
#घोषणा GL_DEBUG_SEVERITY_ऊपरी_KHR        0x9146
#घोषणा GL_DEBUG_SEVERITY_MEDIUM_KHR      0x9147
#घोषणा GL_DEBUG_SEVERITY_निचला_KHR         0x9148
#घोषणा GL_DEBUG_OUTPUT_KHR               0x92E0
#घोषणा GL_CONTEXT_FLAG_DEBUG_BIT_KHR     0x00000002
#घोषणा GL_ढेर_OVERFLOW_KHR             0x0503
#घोषणा GL_ढेर_UNDERFLOW_KHR            0x0504
प्रकार व्योम (GL_APIENTRYP PFNGLDEBUGMESSAGECONTROLKHRPROC) (GLenum source, GLenum type, GLenum severity, GLsizei गिनती, स्थिर GLuint *ids, GLboolean enabled);
प्रकार व्योम (GL_APIENTRYP PFNGLDEBUGMESSAGEINSERTKHRPROC) (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei लंबाई, स्थिर GLchar *buf);
प्रकार व्योम (GL_APIENTRYP PFNGLDEBUGMESSAGECALLBACKKHRPROC) (GLDEBUGPROCKHR callback, स्थिर व्योम *userParam);
प्रकार GLuint (GL_APIENTRYP PFNGLGETDEBUGMESSAGELOGKHRPROC) (GLuint गिनती, GLsizei buf_आकार, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog);
प्रकार व्योम (GL_APIENTRYP PFNGLPUSHDEBUGGROUPKHRPROC) (GLenum source, GLuint id, GLsizei लंबाई, स्थिर GLchar *message);
प्रकार व्योम (GL_APIENTRYP PFNGLPOPDEBUGGROUPKHRPROC) (व्योम);
प्रकार व्योम (GL_APIENTRYP PFNGLOBJECTLABELKHRPROC) (GLenum identifier, GLuint name, GLsizei लंबाई, स्थिर GLchar *label);
प्रकार व्योम (GL_APIENTRYP PFNGLGETOBJECTLABELKHRPROC) (GLenum identifier, GLuint name, GLsizei buf_आकार, GLsizei *लंबाई, GLchar *label);
प्रकार व्योम (GL_APIENTRYP PFNGLOBJECTPTRLABELKHRPROC) (स्थिर व्योम *ptr, GLsizei लंबाई, स्थिर GLchar *label);
प्रकार व्योम (GL_APIENTRYP PFNGLGETOBJECTPTRLABELKHRPROC) (स्थिर व्योम *ptr, GLsizei buf_आकार, GLsizei *लंबाई, GLchar *label);
प्रकार व्योम (GL_APIENTRYP PFNGLGETPOINTERVKHRPROC) (GLenum pname, व्योम **params);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glDebugMessageControlKHR (GLenum source, GLenum type, GLenum severity, GLsizei गिनती, स्थिर GLuint *ids, GLboolean enabled);
GL_APICALL व्योम GL_APIENTRY gl_Debug_Message_जोड़ो_KHR (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei लंबाई, स्थिर GLchar *buf);
GL_APICALL व्योम GL_APIENTRY glDebugMessageCallbackKHR (GLDEBUGPROCKHR callback, स्थिर व्योम *userParam);
GL_APICALL GLuint GL_APIENTRY glGetDebugMessageLogKHR (GLuint गिनती, GLsizei buf_आकार, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog);
GL_APICALL व्योम GL_APIENTRY gl_धकेलो_Debug_Group_KHR (GLenum source, GLuint id, GLsizei लंबाई, स्थिर GLchar *message);
GL_APICALL व्योम GL_APIENTRY gl_निकालो_Debug_Group_KHR (व्योम);
GL_APICALL व्योम GL_APIENTRY glObjectLabelKHR (GLenum identifier, GLuint name, GLsizei लंबाई, स्थिर GLchar *label);
GL_APICALL व्योम GL_APIENTRY glGetObjectLabelKHR (GLenum identifier, GLuint name, GLsizei buf_आकार, GLsizei *लंबाई, GLchar *label);
GL_APICALL व्योम GL_APIENTRY glObjectPtrLabelKHR (स्थिर व्योम *ptr, GLsizei लंबाई, स्थिर GLchar *label);
GL_APICALL व्योम GL_APIENTRY glGetObjectPtrLabelKHR (स्थिर व्योम *ptr, GLsizei buf_आकार, GLsizei *लंबाई, GLchar *label);
GL_APICALL व्योम GL_APIENTRY glGetPointervKHR (GLenum pname, व्योम **params);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_KHR_debug */

#अगर_अघोषित GL_KHR_no_error
#घोषणा GL_KHR_no_error 1
#घोषणा GL_CONTEXT_FLAG_NO_ERROR_BIT_KHR  0x00000008
#पूर्ण_अगर /* GL_KHR_no_error */

#अगर_अघोषित GL_KHR_parallel_shader_compile
#घोषणा GL_KHR_parallel_shader_compile 1
#घोषणा GL_MAX_SHADER_COMPILER_THREADS_KHR 0x91B0
#घोषणा GL_COMPLETION_STATUS_KHR          0x91B1
प्रकार व्योम (GL_APIENTRYP PFNGLMAXSHADERCOMPILERTHREADSKHRPROC) (GLuint गिनती);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glMaxShaderCompilerThreadsKHR (GLuint गिनती);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_KHR_parallel_shader_compile */

#अगर_अघोषित GL_KHR_robust_बफर_access_behavior
#घोषणा GL_KHR_robust_बफर_access_behavior 1
#पूर्ण_अगर /* GL_KHR_robust_buffer_access_behavior */

#अगर_अघोषित GL_KHR_robustness
#घोषणा GL_KHR_robustness 1
#घोषणा GL_CONTEXT_ROBUST_ACCESS_KHR      0x90F3
#घोषणा GL_LOSE_CONTEXT_ON_RESET_KHR      0x8252
#घोषणा GL_GUILTY_CONTEXT_RESET_KHR       0x8253
#घोषणा GL_INNOCENT_CONTEXT_RESET_KHR     0x8254
#घोषणा GL_UNKNOWN_CONTEXT_RESET_KHR      0x8255
#घोषणा GL_RESET_NOTIFICATION_STRATEGY_KHR 0x8256
#घोषणा GL_NO_RESET_NOTIFICATION_KHR      0x8261
#घोषणा GL_CONTEXT_LOST_KHR               0x0507
प्रकार GLenum (GL_APIENTRYP PFNGLGETGRAPHICSRESETSTATUSKHRPROC) (व्योम);
प्रकार व्योम (GL_APIENTRYP PFNGLREADNPIXELSKHRPROC) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei buf_आकार, व्योम *तथ्य);
प्रकार व्योम (GL_APIENTRYP PFNGLGETNUNIFORMFVKHRPROC) (GLuint program, GLint location, GLsizei buf_आकार, GLfloat *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETNUNIFORMIVKHRPROC) (GLuint program, GLint location, GLsizei buf_आकार, GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETNUNIFORMUIVKHRPROC) (GLuint program, GLint location, GLsizei buf_आकार, GLuint *params);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL GLenum GL_APIENTRY glGetGraphicsResetStatusKHR (व्योम);
GL_APICALL व्योम GL_APIENTRY glReadnPixelsKHR (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei buf_आकार, व्योम *तथ्य);
GL_APICALL व्योम GL_APIENTRY glGetnUniformfvKHR (GLuint program, GLint location, GLsizei buf_आकार, GLfloat *params);
GL_APICALL व्योम GL_APIENTRY glGetnUniformivKHR (GLuint program, GLint location, GLsizei buf_आकार, GLint *params);
GL_APICALL व्योम GL_APIENTRY glGetnUniformuivKHR (GLuint program, GLint location, GLsizei buf_आकार, GLuint *params);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_KHR_robustness */

#अगर_अघोषित GL_KHR_shader_subgroup
#घोषणा GL_KHR_shader_subgroup 1
#घोषणा GL_SUBGROUP_आकार_KHR              0x9532
#घोषणा GL_SUBGROUP_SUPPORTED_STAGES_KHR  0x9533
#घोषणा GL_SUBGROUP_SUPPORTED_FEATURES_KHR 0x9534
#घोषणा GL_SUBGROUP_QUAD_ALL_STAGES_KHR   0x9535
#घोषणा GL_SUBGROUP_FEATURE_BASIC_BIT_KHR 0x00000001
#घोषणा GL_SUBGROUP_FEATURE_VOTE_BIT_KHR  0x00000002
#घोषणा GL_SUBGROUP_FEATURE_ARITHMETIC_BIT_KHR 0x00000004
#घोषणा GL_SUBGROUP_FEATURE_BALLOT_BIT_KHR 0x00000008
#घोषणा GL_SUBGROUP_FEATURE_SHUFFLE_BIT_KHR 0x00000010
#घोषणा GL_SUBGROUP_FEATURE_SHUFFLE_RELATIVE_BIT_KHR 0x00000020
#घोषणा GL_SUBGROUP_FEATURE_CLUSTERED_BIT_KHR 0x00000040
#घोषणा GL_SUBGROUP_FEATURE_QUAD_BIT_KHR  0x00000080
#पूर्ण_अगर /* GL_KHR_shader_subgroup */

#अगर_अघोषित GL_KHR_texture_compression_astc_hdr
#घोषणा GL_KHR_texture_compression_astc_hdr 1
#घोषणा GL_COMPRESSED_RGBA_ASTC_4x4_KHR   0x93B0
#घोषणा GL_COMPRESSED_RGBA_ASTC_5x4_KHR   0x93B1
#घोषणा GL_COMPRESSED_RGBA_ASTC_5x5_KHR   0x93B2
#घोषणा GL_COMPRESSED_RGBA_ASTC_6x5_KHR   0x93B3
#घोषणा GL_COMPRESSED_RGBA_ASTC_6x6_KHR   0x93B4
#घोषणा GL_COMPRESSED_RGBA_ASTC_8x5_KHR   0x93B5
#घोषणा GL_COMPRESSED_RGBA_ASTC_8x6_KHR   0x93B6
#घोषणा GL_COMPRESSED_RGBA_ASTC_8x8_KHR   0x93B7
#घोषणा GL_COMPRESSED_RGBA_ASTC_10x5_KHR  0x93B8
#घोषणा GL_COMPRESSED_RGBA_ASTC_10x6_KHR  0x93B9
#घोषणा GL_COMPRESSED_RGBA_ASTC_10x8_KHR  0x93BA
#घोषणा GL_COMPRESSED_RGBA_ASTC_10x10_KHR 0x93BB
#घोषणा GL_COMPRESSED_RGBA_ASTC_12x10_KHR 0x93BC
#घोषणा GL_COMPRESSED_RGBA_ASTC_12x12_KHR 0x93BD
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR 0x93D0
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR 0x93D1
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR 0x93D2
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR 0x93D3
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR 0x93D4
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR 0x93D5
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR 0x93D6
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR 0x93D7
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR 0x93D8
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR 0x93D9
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR 0x93DA
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR 0x93DB
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR 0x93DC
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR 0x93DD
#पूर्ण_अगर /* GL_KHR_texture_compression_astc_hdr */

#अगर_अघोषित GL_KHR_texture_compression_astc_ldr
#घोषणा GL_KHR_texture_compression_astc_ldr 1
#पूर्ण_अगर /* GL_KHR_texture_compression_astc_ldr */

#अगर_अघोषित GL_KHR_texture_compression_astc_sliced_3d
#घोषणा GL_KHR_texture_compression_astc_sliced_3d 1
#पूर्ण_अगर /* GL_KHR_texture_compression_astc_sliced_3d */

#अगर_अघोषित GL_OES_EGL_image
#घोषणा GL_OES_EGL_image 1
प्रकार व्योम *GLeglImageOES;
प्रकार व्योम (GL_APIENTRYP PFNGLEGLIMAGETARGETTEXTURE2DOESPROC) (GLenum target, GLeglImageOES image);
प्रकार व्योम (GL_APIENTRYP PFNGLEGLIMAGETARGETRENDERBUFFERSTORAGEOESPROC) (GLenum target, GLeglImageOES image);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glEGLImageTargetTexture2DOES (GLenum target, GLeglImageOES image);
GL_APICALL व्योम GL_APIENTRY glEGLImageTargetRenderbufferStorageOES (GLenum target, GLeglImageOES image);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_OES_EGL_image */

#अगर_अघोषित GL_OES_EGL_image_external
#घोषणा GL_OES_EGL_image_external 1
#घोषणा GL_TEXTURE_EXTERNAL_OES           0x8D65
#घोषणा GL_TEXTURE_BINDING_EXTERNAL_OES   0x8D67
#घोषणा GL_REQUIRED_TEXTURE_IMAGE_UNITS_OES 0x8D68
#घोषणा GL_SAMPLER_EXTERNAL_OES           0x8D66
#पूर्ण_अगर /* GL_OES_EGL_image_external */

#अगर_अघोषित GL_OES_EGL_image_external_essl3
#घोषणा GL_OES_EGL_image_external_essl3 1
#पूर्ण_अगर /* GL_OES_EGL_image_external_essl3 */

#अगर_अघोषित GL_OES_compressed_ETC1_RGB8_sub_texture
#घोषणा GL_OES_compressed_ETC1_RGB8_sub_texture 1
#पूर्ण_अगर /* GL_OES_compressed_ETC1_RGB8_sub_texture */

#अगर_अघोषित GL_OES_compressed_ETC1_RGB8_texture
#घोषणा GL_OES_compressed_ETC1_RGB8_texture 1
#घोषणा GL_ETC1_RGB8_OES                  0x8D64
#पूर्ण_अगर /* GL_OES_compressed_ETC1_RGB8_texture */

#अगर_अघोषित GL_OES_compressed_paletted_texture
#घोषणा GL_OES_compressed_paletted_texture 1
#घोषणा GL_PALETTE4_RGB8_OES              0x8B90
#घोषणा GL_PALETTE4_RGBA8_OES             0x8B91
#घोषणा GL_PALETTE4_R5_G6_B5_OES          0x8B92
#घोषणा GL_PALETTE4_RGBA4_OES             0x8B93
#घोषणा GL_PALETTE4_RGB5_A1_OES           0x8B94
#घोषणा GL_PALETTE8_RGB8_OES              0x8B95
#घोषणा GL_PALETTE8_RGBA8_OES             0x8B96
#घोषणा GL_PALETTE8_R5_G6_B5_OES          0x8B97
#घोषणा GL_PALETTE8_RGBA4_OES             0x8B98
#घोषणा GL_PALETTE8_RGB5_A1_OES           0x8B99
#पूर्ण_अगर /* GL_OES_compressed_paletted_texture */

#अगर_अघोषित GL_OES_copy_image
#घोषणा GL_OES_copy_image 1
प्रकार व्योम (GL_APIENTRYP PFNGLCOPYIMAGESUBDATAOESPROC) (GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY gl_Copy_Image_Sub_तथ्य_OES (GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_OES_copy_image */

#अगर_अघोषित GL_OES_depth24
#घोषणा GL_OES_depth24 1
#घोषणा GL_DEPTH_COMPONENT24_OES          0x81A6
#पूर्ण_अगर /* GL_OES_depth24 */

#अगर_अघोषित GL_OES_depth32
#घोषणा GL_OES_depth32 1
#घोषणा GL_DEPTH_COMPONENT32_OES          0x81A7
#पूर्ण_अगर /* GL_OES_depth32 */

#अगर_अघोषित GL_OES_depth_texture
#घोषणा GL_OES_depth_texture 1
#पूर्ण_अगर /* GL_OES_depth_texture */

#अगर_अघोषित GL_OES_draw_buffers_indexed
#घोषणा GL_OES_draw_buffers_indexed 1
#घोषणा GL_MIN                            0x8007
#घोषणा GL_MAX                            0x8008
प्रकार व्योम (GL_APIENTRYP PFNGLENABLEIOESPROC) (GLenum target, GLuint सूचकांक);
प्रकार व्योम (GL_APIENTRYP PFNGLDISABLEIOESPROC) (GLenum target, GLuint सूचकांक);
प्रकार व्योम (GL_APIENTRYP PFNGLBLENDEQUATIONIOESPROC) (GLuint buf, GLenum mode);
प्रकार व्योम (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEIOESPROC) (GLuint buf, GLenum modeRGB, GLenum modeAlpha);
प्रकार व्योम (GL_APIENTRYP PFNGLBLENDFUNCIOESPROC) (GLuint buf, GLenum src, GLenum dst);
प्रकार व्योम (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEIOESPROC) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
प्रकार व्योम (GL_APIENTRYP PFNGLCOLORMASKIOESPROC) (GLuint सूचकांक, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
प्रकार GLboolean (GL_APIENTRYP PFNGLISENABLEDIOESPROC) (GLenum target, GLuint सूचकांक);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glEnableiOES (GLenum target, GLuint सूचकांक);
GL_APICALL व्योम GL_APIENTRY glDisableiOES (GLenum target, GLuint सूचकांक);
GL_APICALL व्योम GL_APIENTRY glBlendEquationiOES (GLuint buf, GLenum mode);
GL_APICALL व्योम GL_APIENTRY glBlendEquationSeparateiOES (GLuint buf, GLenum modeRGB, GLenum modeAlpha);
GL_APICALL व्योम GL_APIENTRY glBlendFunciOES (GLuint buf, GLenum src, GLenum dst);
GL_APICALL व्योम GL_APIENTRY glBlendFuncSeparateiOES (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
GL_APICALL व्योम GL_APIENTRY glColorMaskiOES (GLuint सूचकांक, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
GL_APICALL GLboolean GL_APIENTRY glIsEnablediOES (GLenum target, GLuint सूचकांक);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_OES_draw_buffers_indexed */

#अगर_अघोषित GL_OES_draw_elements_base_vertex
#घोषणा GL_OES_draw_elements_base_vertex 1
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWELEMENTSBASEVERTEXOESPROC) (GLenum mode, GLsizei गिनती, GLenum type, स्थिर व्योम *indices, GLint basevertex);
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWRANGEELEMENTSBASEVERTEXOESPROC) (GLenum mode, GLuint start, GLuint end, GLsizei गिनती, GLenum type, स्थिर व्योम *indices, GLint basevertex);
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXOESPROC) (GLenum mode, GLsizei गिनती, GLenum type, स्थिर व्योम *indices, GLsizei instancecount, GLint basevertex);
प्रकार व्योम (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSBASEVERTEXEXTPROC) (GLenum mode, स्थिर GLsizei *गिनती, GLenum type, स्थिर व्योम *स्थिर*indices, GLsizei drawcount, स्थिर GLint *basevertex);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glDrawElementsBaseVertexOES (GLenum mode, GLsizei गिनती, GLenum type, स्थिर व्योम *indices, GLint basevertex);
GL_APICALL व्योम GL_APIENTRY glDrawRangeElementsBaseVertexOES (GLenum mode, GLuint start, GLuint end, GLsizei गिनती, GLenum type, स्थिर व्योम *indices, GLint basevertex);
GL_APICALL व्योम GL_APIENTRY glDrawElementsInstancedBaseVertexOES (GLenum mode, GLsizei गिनती, GLenum type, स्थिर व्योम *indices, GLsizei instancecount, GLint basevertex);
GL_APICALL व्योम GL_APIENTRY glMultiDrawElementsBaseVertexEXT (GLenum mode, स्थिर GLsizei *गिनती, GLenum type, स्थिर व्योम *स्थिर*indices, GLsizei drawcount, स्थिर GLint *basevertex);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_OES_draw_elements_base_vertex */

#अगर_अघोषित GL_OES_element_सूचकांक_uint
#घोषणा GL_OES_element_सूचकांक_uint 1
#पूर्ण_अगर /* GL_OES_element_index_uint */

#अगर_अघोषित GL_OES_fbo_render_mipmap
#घोषणा GL_OES_fbo_render_mipmap 1
#पूर्ण_अगर /* GL_OES_fbo_render_mipmap */

#अगर_अघोषित GL_OES_fragment_precision_ऊपरी
#घोषणा GL_OES_fragment_precision_ऊपरी 1
#पूर्ण_अगर /* GL_OES_fragment_precision_high */

#अगर_अघोषित GL_OES_geometry_point_आकार
#घोषणा GL_OES_geometry_point_आकार 1
#पूर्ण_अगर /* GL_OES_geometry_point_size */

#अगर_अघोषित GL_OES_geometry_shader
#घोषणा GL_OES_geometry_shader 1
#घोषणा GL_GEOMETRY_SHADER_OES            0x8DD9
#घोषणा GL_GEOMETRY_SHADER_BIT_OES        0x00000004
#घोषणा GL_GEOMETRY_LINKED_VERTICES_OUT_OES 0x8916
#घोषणा GL_GEOMETRY_LINKED_निवेश_TYPE_OES 0x8917
#घोषणा GL_GEOMETRY_LINKED_OUTPUT_TYPE_OES 0x8918
#घोषणा GL_GEOMETRY_SHADER_INVOCATIONS_OES 0x887F
#घोषणा GL_LAYER_PROVOKING_VERTEX_OES     0x825E
#घोषणा GL_पंक्तियाँ_ADJACENCY_OES            0x000A
#घोषणा GL_पंक्ति_STRIP_ADJACENCY_OES       0x000B
#घोषणा GL_TRIANGLES_ADJACENCY_OES        0x000C
#घोषणा GL_TRIANGLE_STRIP_ADJACENCY_OES   0x000D
#घोषणा GL_MAX_GEOMETRY_UNIFORM_COMPONENTS_OES 0x8DDF
#घोषणा GL_MAX_GEOMETRY_UNIFORM_BLOCKS_OES 0x8A2C
#घोषणा GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS_OES 0x8A32
#घोषणा GL_MAX_GEOMETRY_निवेश_COMPONENTS_OES 0x9123
#घोषणा GL_MAX_GEOMETRY_OUTPUT_COMPONENTS_OES 0x9124
#घोषणा GL_MAX_GEOMETRY_OUTPUT_VERTICES_OES 0x8DE0
#घोषणा GL_MAX_GEOMETRY_योग_OUTPUT_COMPONENTS_OES 0x8DE1
#घोषणा GL_MAX_GEOMETRY_SHADER_INVOCATIONS_OES 0x8E5A
#घोषणा GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_OES 0x8C29
#घोषणा GL_MAX_GEOMETRY_ATOMIC_गणक_BUFFERS_OES 0x92CF
#घोषणा GL_MAX_GEOMETRY_ATOMIC_COUNTERS_OES 0x92D5
#घोषणा GL_MAX_GEOMETRY_IMAGE_UNIFORMS_OES 0x90CD
#घोषणा GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS_OES 0x90D7
#घोषणा GL_FIRST_VERTEX_CONVENTION_OES    0x8E4D
#घोषणा GL_LAST_VERTEX_CONVENTION_OES     0x8E4E
#घोषणा GL_UNDEFINED_VERTEX_OES           0x8260
#घोषणा GL_PRIMITIVES_GENERATED_OES       0x8C87
#घोषणा GL_FRAMEBUFFER_DEFAULT_LAYERS_OES 0x9312
#घोषणा GL_MAX_FRAMEBUFFER_LAYERS_OES     0x9317
#घोषणा GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_OES 0x8DA8
#घोषणा GL_FRAMEBUFFER_ATTACHMENT_LAYERED_OES 0x8DA7
#घोषणा GL_REFERENCED_BY_GEOMETRY_SHADER_OES 0x9309
प्रकार व्योम (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREOESPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glFramebufferTextureOES (GLenum target, GLenum attachment, GLuint texture, GLint level);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_OES_geometry_shader */

#अगर_अघोषित GL_OES_get_program_द्विआधारी
#घोषणा GL_OES_get_program_द्विआधारी 1
#घोषणा GL_PROGRAM_द्विआधारी_लंबाई_OES      0x8741
#घोषणा GL_अंक_PROGRAM_द्विआधारी_FORMATS_OES 0x87FE
#घोषणा GL_PROGRAM_द्विआधारी_FORMATS_OES     0x87FF
प्रकार व्योम (GL_APIENTRYP PFNGLGETPROGRAMBINARYOESPROC) (GLuint program, GLsizei buf_आकार, GLsizei *लंबाई, GLenum *द्विआधारी_Format, व्योम *द्विआधारी);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMBINARYOESPROC) (GLuint program, GLenum द्विआधारी_Format, स्थिर व्योम *द्विआधारी, GLint लंबाई);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY gl_Get_Program_द्विआधारी_OES (GLuint program, GLsizei buf_आकार, GLsizei *लंबाई, GLenum *द्विआधारी_Format, व्योम *द्विआधारी);
GL_APICALL व्योम GL_APIENTRY gl_Program_द्विआधारी_OES (GLuint program, GLenum द्विआधारी_Format, स्थिर व्योम *द्विआधारी, GLint लंबाई);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_OES_get_program_binary */

#अगर_अघोषित GL_OES_gpu_shader5
#घोषणा GL_OES_gpu_shader5 1
#पूर्ण_अगर /* GL_OES_gpu_shader5 */

#अगर_अघोषित GL_OES_mapbuffer
#घोषणा GL_OES_mapbuffer 1
#घोषणा GL_WRITE_ONLY_OES                 0x88B9
#घोषणा GL_बफर_ACCESS_OES              0x88BB
#घोषणा GL_बफर_MAPPED_OES              0x88BC
#घोषणा GL_बफर_MAP_POINTER_OES         0x88BD
प्रकार व्योम *(GL_APIENTRYP PFNGLMAPBUFFEROESPROC) (GLenum target, GLenum access);
प्रकार GLboolean (GL_APIENTRYP PFNGLUNMAPBUFFEROESPROC) (GLenum target);
प्रकार व्योम (GL_APIENTRYP PFNGLGETBUFFERPOINTERVOESPROC) (GLenum target, GLenum pname, व्योम **params);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम *GL_APIENTRY gl_Map_बफर_OES (GLenum target, GLenum access);
GL_APICALL GLboolean GL_APIENTRY gl_Unmap_बफर_OES (GLenum target);
GL_APICALL व्योम GL_APIENTRY gl_Get_बफर_Pointerv_OES (GLenum target, GLenum pname, व्योम **params);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_OES_mapbuffer */

#अगर_अघोषित GL_OES_packed_depth_stencil
#घोषणा GL_OES_packed_depth_stencil 1
#घोषणा GL_DEPTH_STENCIL_OES              0x84F9
#घोषणा GL_UNSIGNED_INT_24_8_OES          0x84FA
#घोषणा GL_DEPTH24_STENCIL8_OES           0x88F0
#पूर्ण_अगर /* GL_OES_packed_depth_stencil */

#अगर_अघोषित GL_OES_primitive_bounding_box
#घोषणा GL_OES_primitive_bounding_box 1
#घोषणा GL_PRIMITIVE_BOUNDING_BOX_OES     0x92BE
प्रकार व्योम (GL_APIENTRYP PFNGLPRIMITIVEBOUNDINGBOXOESPROC) (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glPrimitiveBoundingBoxOES (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_OES_primitive_bounding_box */

#अगर_अघोषित GL_OES_required_internalformat
#घोषणा GL_OES_required_internalformat 1
#घोषणा GL_ALPHA8_OES                     0x803C
#घोषणा GL_DEPTH_COMPONENT16_OES          0x81A5
#घोषणा GL_LUMINANCE4_ALPHA4_OES          0x8043
#घोषणा GL_LUMINANCE8_ALPHA8_OES          0x8045
#घोषणा GL_LUMINANCE8_OES                 0x8040
#घोषणा GL_RGBA4_OES                      0x8056
#घोषणा GL_RGB5_A1_OES                    0x8057
#घोषणा GL_RGB565_OES                     0x8D62
#घोषणा GL_RGB8_OES                       0x8051
#घोषणा GL_RGBA8_OES                      0x8058
#घोषणा GL_RGB10_EXT                      0x8052
#घोषणा GL_RGB10_A2_EXT                   0x8059
#पूर्ण_अगर /* GL_OES_required_internalformat */

#अगर_अघोषित GL_OES_rgb8_rgba8
#घोषणा GL_OES_rgb8_rgba8 1
#पूर्ण_अगर /* GL_OES_rgb8_rgba8 */

#अगर_अघोषित GL_OES_sample_shading
#घोषणा GL_OES_sample_shading 1
#घोषणा GL_SAMPLE_SHADING_OES             0x8C36
#घोषणा GL_MIN_SAMPLE_SHADING_मूल्य_OES   0x8C37
प्रकार व्योम (GL_APIENTRYP PFNGLMINSAMPLESHADINGOESPROC) (GLfloat मूल्य);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glMinSampleShadingOES (GLfloat मूल्य);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_OES_sample_shading */

#अगर_अघोषित GL_OES_sample_variables
#घोषणा GL_OES_sample_variables 1
#पूर्ण_अगर /* GL_OES_sample_variables */

#अगर_अघोषित GL_OES_shader_image_atomic
#घोषणा GL_OES_shader_image_atomic 1
#पूर्ण_अगर /* GL_OES_shader_image_atomic */

#अगर_अघोषित GL_OES_shader_io_blocks
#घोषणा GL_OES_shader_io_blocks 1
#पूर्ण_अगर /* GL_OES_shader_io_blocks */

#अगर_अघोषित GL_OES_shader_multisample_interpolation
#घोषणा GL_OES_shader_multisample_interpolation 1
#घोषणा GL_MIN_FRAGMENT_INTERPOLATION_OFFSET_OES 0x8E5B
#घोषणा GL_MAX_FRAGMENT_INTERPOLATION_OFFSET_OES 0x8E5C
#घोषणा GL_FRAGMENT_INTERPOLATION_OFFSET_BITS_OES 0x8E5D
#पूर्ण_अगर /* GL_OES_shader_multisample_interpolation */

#अगर_अघोषित GL_OES_standard_derivatives
#घोषणा GL_OES_standard_derivatives 1
#घोषणा GL_FRAGMENT_SHADER_DERIVATIVE_HINT_OES 0x8B8B
#पूर्ण_अगर /* GL_OES_standard_derivatives */

#अगर_अघोषित GL_OES_stencil1
#घोषणा GL_OES_stencil1 1
#घोषणा GL_STENCIL_INDEX1_OES             0x8D46
#पूर्ण_अगर /* GL_OES_stencil1 */

#अगर_अघोषित GL_OES_stencil4
#घोषणा GL_OES_stencil4 1
#घोषणा GL_STENCIL_INDEX4_OES             0x8D47
#पूर्ण_अगर /* GL_OES_stencil4 */

#अगर_अघोषित GL_OES_surfaceless_context
#घोषणा GL_OES_surfaceless_context 1
#घोषणा GL_FRAMEBUFFER_UNDEFINED_OES      0x8219
#पूर्ण_अगर /* GL_OES_surfaceless_context */

#अगर_अघोषित GL_OES_tessellation_point_आकार
#घोषणा GL_OES_tessellation_point_आकार 1
#पूर्ण_अगर /* GL_OES_tessellation_point_size */

#अगर_अघोषित GL_OES_tessellation_shader
#घोषणा GL_OES_tessellation_shader 1
#घोषणा GL_PATCHES_OES                    0x000E
#घोषणा GL_PATCH_VERTICES_OES             0x8E72
#घोषणा GL_TESS_CONTROL_OUTPUT_VERTICES_OES 0x8E75
#घोषणा GL_TESS_GEN_MODE_OES              0x8E76
#घोषणा GL_TESS_GEN_SPACING_OES           0x8E77
#घोषणा GL_TESS_GEN_VERTEX_ORDER_OES      0x8E78
#घोषणा GL_TESS_GEN_POINT_MODE_OES        0x8E79
#घोषणा GL_ISOLINES_OES                   0x8E7A
#घोषणा GL_QUADS_OES                      0x0007
#घोषणा GL_FRACTIONAL_ODD_OES             0x8E7B
#घोषणा GL_FRACTIONAL_EVEN_OES            0x8E7C
#घोषणा GL_MAX_PATCH_VERTICES_OES         0x8E7D
#घोषणा GL_MAX_TESS_GEN_LEVEL_OES         0x8E7E
#घोषणा GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS_OES 0x8E7F
#घोषणा GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS_OES 0x8E80
#घोषणा GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS_OES 0x8E81
#घोषणा GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS_OES 0x8E82
#घोषणा GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS_OES 0x8E83
#घोषणा GL_MAX_TESS_PATCH_COMPONENTS_OES  0x8E84
#घोषणा GL_MAX_TESS_CONTROL_योग_OUTPUT_COMPONENTS_OES 0x8E85
#घोषणा GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS_OES 0x8E86
#घोषणा GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS_OES 0x8E89
#घोषणा GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS_OES 0x8E8A
#घोषणा GL_MAX_TESS_CONTROL_निवेश_COMPONENTS_OES 0x886C
#घोषणा GL_MAX_TESS_EVALUATION_निवेश_COMPONENTS_OES 0x886D
#घोषणा GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS_OES 0x8E1E
#घोषणा GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS_OES 0x8E1F
#घोषणा GL_MAX_TESS_CONTROL_ATOMIC_गणक_BUFFERS_OES 0x92CD
#घोषणा GL_MAX_TESS_EVALUATION_ATOMIC_गणक_BUFFERS_OES 0x92CE
#घोषणा GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS_OES 0x92D3
#घोषणा GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS_OES 0x92D4
#घोषणा GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS_OES 0x90CB
#घोषणा GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS_OES 0x90CC
#घोषणा GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS_OES 0x90D8
#घोषणा GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS_OES 0x90D9
#घोषणा GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED_OES 0x8221
#घोषणा GL_IS_PER_PATCH_OES               0x92E7
#घोषणा GL_REFERENCED_BY_TESS_CONTROL_SHADER_OES 0x9307
#घोषणा GL_REFERENCED_BY_TESS_EVALUATION_SHADER_OES 0x9308
#घोषणा GL_TESS_CONTROL_SHADER_OES        0x8E88
#घोषणा GL_TESS_EVALUATION_SHADER_OES     0x8E87
#घोषणा GL_TESS_CONTROL_SHADER_BIT_OES    0x00000008
#घोषणा GL_TESS_EVALUATION_SHADER_BIT_OES 0x00000010
प्रकार व्योम (GL_APIENTRYP PFNGLPATCHPARAMETERIOESPROC) (GLenum pname, GLint मूल्य);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glPatchParameteriOES (GLenum pname, GLint मूल्य);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_OES_tessellation_shader */

#अगर_अघोषित GL_OES_texture_3D
#घोषणा GL_OES_texture_3D 1
#घोषणा GL_TEXTURE_WRAP_R_OES             0x8072
#घोषणा GL_TEXTURE_3D_OES                 0x806F
#घोषणा GL_TEXTURE_BINDING_3D_OES         0x806A
#घोषणा GL_MAX_3_D_TEXTURE_आकार_OES        0x8073
#घोषणा GL_SAMPLER_3D_OES                 0x8B5F
#घोषणा GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_3D_ZOFFSET_OES 0x8CD4
प्रकार व्योम (GL_APIENTRYP PFNGLTEXIMAGE3DOESPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, स्थिर व्योम *pixels);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXSUBIMAGE3DOESPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, स्थिर व्योम *pixels);
प्रकार व्योम (GL_APIENTRYP PFNGLCOPYTEXSUBIMAGE3DOESPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
प्रकार व्योम (GL_APIENTRYP PFNGLCOMPRESSEDTEXIMAGE3DOESPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei image_आकार, स्थिर व्योम *तथ्य);
प्रकार व्योम (GL_APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE3DOESPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei image_आकार, स्थिर व्योम *तथ्य);
प्रकार व्योम (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE3DOESPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glTexImage3DOES (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, स्थिर व्योम *pixels);
GL_APICALL व्योम GL_APIENTRY glTexSubImage3DOES (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, स्थिर व्योम *pixels);
GL_APICALL व्योम GL_APIENTRY glCopyTexSubImage3DOES (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
GL_APICALL व्योम GL_APIENTRY glCompressedTexImage3DOES (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei image_आकार, स्थिर व्योम *तथ्य);
GL_APICALL व्योम GL_APIENTRY glCompressedTexSubImage3DOES (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei image_आकार, स्थिर व्योम *तथ्य);
GL_APICALL व्योम GL_APIENTRY glFramebufferTexture3DOES (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_OES_texture_3D */

#अगर_अघोषित GL_OES_texture_border_clamp
#घोषणा GL_OES_texture_border_clamp 1
#घोषणा GL_TEXTURE_BORDER_COLOR_OES       0x1004
#घोषणा GL_CLAMP_TO_BORDER_OES            0x812D
प्रकार व्योम (GL_APIENTRYP PFNGLTEXPARAMETERIIVOESPROC) (GLenum target, GLenum pname, स्थिर GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXPARAMETERIUIVOESPROC) (GLenum target, GLenum pname, स्थिर GLuint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETTEXPARAMETERIIVOESPROC) (GLenum target, GLenum pname, GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETTEXPARAMETERIUIVOESPROC) (GLenum target, GLenum pname, GLuint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLSAMPLERPARAMETERIIVOESPROC) (GLuint sampler, GLenum pname, स्थिर GLint *param);
प्रकार व्योम (GL_APIENTRYP PFNGLSAMPLERPARAMETERIUIVOESPROC) (GLuint sampler, GLenum pname, स्थिर GLuint *param);
प्रकार व्योम (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIIVOESPROC) (GLuint sampler, GLenum pname, GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIUIVOESPROC) (GLuint sampler, GLenum pname, GLuint *params);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glTexParameterIivOES (GLenum target, GLenum pname, स्थिर GLint *params);
GL_APICALL व्योम GL_APIENTRY glTexParameterIuivOES (GLenum target, GLenum pname, स्थिर GLuint *params);
GL_APICALL व्योम GL_APIENTRY glGetTexParameterIivOES (GLenum target, GLenum pname, GLint *params);
GL_APICALL व्योम GL_APIENTRY glGetTexParameterIuivOES (GLenum target, GLenum pname, GLuint *params);
GL_APICALL व्योम GL_APIENTRY glSamplerParameterIivOES (GLuint sampler, GLenum pname, स्थिर GLint *param);
GL_APICALL व्योम GL_APIENTRY glSamplerParameterIuivOES (GLuint sampler, GLenum pname, स्थिर GLuint *param);
GL_APICALL व्योम GL_APIENTRY glGetSamplerParameterIivOES (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL व्योम GL_APIENTRY glGetSamplerParameterIuivOES (GLuint sampler, GLenum pname, GLuint *params);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_OES_texture_border_clamp */

#अगर_अघोषित GL_OES_texture_बफर
#घोषणा GL_OES_texture_बफर 1
#घोषणा GL_TEXTURE_बफर_OES             0x8C2A
#घोषणा GL_TEXTURE_बफर_BINDING_OES     0x8C2A
#घोषणा GL_MAX_TEXTURE_बफर_आकार_OES    0x8C2B
#घोषणा GL_TEXTURE_BINDING_बफर_OES     0x8C2C
#घोषणा GL_TEXTURE_बफर_तथ्य_STORE_BINDING_OES 0x8C2D
#घोषणा GL_TEXTURE_बफर_OFFSET_ALIGNMENT_OES 0x919F
#घोषणा GL_SAMPLER_बफर_OES             0x8DC2
#घोषणा GL_INT_SAMPLER_बफर_OES         0x8DD0
#घोषणा GL_UNSIGNED_INT_SAMPLER_बफर_OES 0x8DD8
#घोषणा GL_IMAGE_बफर_OES               0x9051
#घोषणा GL_INT_IMAGE_बफर_OES           0x905C
#घोषणा GL_UNSIGNED_INT_IMAGE_बफर_OES  0x9067
#घोषणा GL_TEXTURE_बफर_OFFSET_OES      0x919D
#घोषणा GL_TEXTURE_बफर_आकार_OES        0x919E
प्रकार व्योम (GL_APIENTRYP PFNGLTEXBUFFEROESPROC) (GLenum target, GLenum internalformat, GLuint बफर_2);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXBUFFERRANGEOESPROC) (GLenum target, GLenum internalformat, GLuint बफर_2, GLintptr offset, GLsizeiptr आकार);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY gl_Tex_बफर_OES (GLenum target, GLenum internalformat, GLuint बफर_2);
GL_APICALL व्योम GL_APIENTRY gl_Tex_बफर_Range_OES (GLenum target, GLenum internalformat, GLuint बफर_2, GLintptr offset, GLsizeiptr आकार);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_OES_texture_buffer */

#अगर_अघोषित GL_OES_texture_compression_astc
#घोषणा GL_OES_texture_compression_astc 1
#घोषणा GL_COMPRESSED_RGBA_ASTC_3x3x3_OES 0x93C0
#घोषणा GL_COMPRESSED_RGBA_ASTC_4x3x3_OES 0x93C1
#घोषणा GL_COMPRESSED_RGBA_ASTC_4x4x3_OES 0x93C2
#घोषणा GL_COMPRESSED_RGBA_ASTC_4x4x4_OES 0x93C3
#घोषणा GL_COMPRESSED_RGBA_ASTC_5x4x4_OES 0x93C4
#घोषणा GL_COMPRESSED_RGBA_ASTC_5x5x4_OES 0x93C5
#घोषणा GL_COMPRESSED_RGBA_ASTC_5x5x5_OES 0x93C6
#घोषणा GL_COMPRESSED_RGBA_ASTC_6x5x5_OES 0x93C7
#घोषणा GL_COMPRESSED_RGBA_ASTC_6x6x5_OES 0x93C8
#घोषणा GL_COMPRESSED_RGBA_ASTC_6x6x6_OES 0x93C9
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_3x3x3_OES 0x93E0
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x3x3_OES 0x93E1
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4x3_OES 0x93E2
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4x4_OES 0x93E3
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4x4_OES 0x93E4
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5x4_OES 0x93E5
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5x5_OES 0x93E6
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5x5_OES 0x93E7
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6x5_OES 0x93E8
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6x6_OES 0x93E9
#पूर्ण_अगर /* GL_OES_texture_compression_astc */

#अगर_अघोषित GL_OES_texture_cube_map_array
#घोषणा GL_OES_texture_cube_map_array 1
#घोषणा GL_TEXTURE_CUBE_MAP_ARRAY_OES     0x9009
#घोषणा GL_TEXTURE_BINDING_CUBE_MAP_ARRAY_OES 0x900A
#घोषणा GL_SAMPLER_CUBE_MAP_ARRAY_OES     0x900C
#घोषणा GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW_OES 0x900D
#घोषणा GL_INT_SAMPLER_CUBE_MAP_ARRAY_OES 0x900E
#घोषणा GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY_OES 0x900F
#घोषणा GL_IMAGE_CUBE_MAP_ARRAY_OES       0x9054
#घोषणा GL_INT_IMAGE_CUBE_MAP_ARRAY_OES   0x905F
#घोषणा GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY_OES 0x906A
#पूर्ण_अगर /* GL_OES_texture_cube_map_array */

#अगर_अघोषित GL_OES_texture_float
#घोषणा GL_OES_texture_float 1
#पूर्ण_अगर /* GL_OES_texture_float */

#अगर_अघोषित GL_OES_texture_float_linear
#घोषणा GL_OES_texture_float_linear 1
#पूर्ण_अगर /* GL_OES_texture_float_linear */

#अगर_अघोषित GL_OES_texture_half_float
#घोषणा GL_OES_texture_half_float 1
#घोषणा GL_HALF_FLOAT_OES                 0x8D61
#पूर्ण_अगर /* GL_OES_texture_half_float */

#अगर_अघोषित GL_OES_texture_half_float_linear
#घोषणा GL_OES_texture_half_float_linear 1
#पूर्ण_अगर /* GL_OES_texture_half_float_linear */

#अगर_अघोषित GL_OES_texture_npot
#घोषणा GL_OES_texture_npot 1
#पूर्ण_अगर /* GL_OES_texture_npot */

#अगर_अघोषित GL_OES_texture_stencil8
#घोषणा GL_OES_texture_stencil8 1
#घोषणा GL_STENCIL_सूचकांक_OES              0x1901
#घोषणा GL_STENCIL_INDEX8_OES             0x8D48
#पूर्ण_अगर /* GL_OES_texture_stencil8 */

#अगर_अघोषित GL_OES_texture_storage_multisample_2d_array
#घोषणा GL_OES_texture_storage_multisample_2d_array 1
#घोषणा GL_TEXTURE_2D_MULTISAMPLE_ARRAY_OES 0x9102
#घोषणा GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY_OES 0x9105
#घोषणा GL_SAMPLER_2D_MULTISAMPLE_ARRAY_OES 0x910B
#घोषणा GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY_OES 0x910C
#घोषणा GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY_OES 0x910D
प्रकार व्योम (GL_APIENTRYP PFNGLTEXSTORAGE3DMULTISAMPLEOESPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glTexStorage3DMultisampleOES (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_OES_texture_storage_multisample_2d_array */

#अगर_अघोषित GL_OES_texture_view
#घोषणा GL_OES_texture_view 1
#घोषणा GL_TEXTURE_VIEW_MIN_LEVEL_OES     0x82DB
#घोषणा GL_TEXTURE_VIEW_अंक_LEVELS_OES    0x82DC
#घोषणा GL_TEXTURE_VIEW_MIN_LAYER_OES     0x82DD
#घोषणा GL_TEXTURE_VIEW_अंक_LAYERS_OES    0x82DE
#घोषणा GL_TEXTURE_IMMUTABLE_LEVELS       0x82DF
प्रकार व्योम (GL_APIENTRYP PFNGLTEXTUREVIEWOESPROC) (GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glTextureViewOES (GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_OES_texture_view */

#अगर_अघोषित GL_OES_vertex_array_object
#घोषणा GL_OES_vertex_array_object 1
#घोषणा GL_VERTEX_ARRAY_BINDING_OES       0x85B5
प्रकार व्योम (GL_APIENTRYP PFNGLBINDVERTEXARRAYOESPROC) (GLuint array);
प्रकार व्योम (GL_APIENTRYP PFNGLDELETEVERTEXARRAYSOESPROC) (GLsizei n, स्थिर GLuint *arrays);
प्रकार व्योम (GL_APIENTRYP PFNGLGENVERTEXARRAYSOESPROC) (GLsizei n, GLuint *arrays);
प्रकार GLboolean (GL_APIENTRYP PFNGLISVERTEXARRAYOESPROC) (GLuint array);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glBindVertexArrayOES (GLuint array);
GL_APICALL व्योम GL_APIENTRY glDeleteVertexArraysOES (GLsizei n, स्थिर GLuint *arrays);
GL_APICALL व्योम GL_APIENTRY glGenVertexArraysOES (GLsizei n, GLuint *arrays);
GL_APICALL GLboolean GL_APIENTRY glIsVertexArrayOES (GLuint array);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_OES_vertex_array_object */

#अगर_अघोषित GL_OES_vertex_half_float
#घोषणा GL_OES_vertex_half_float 1
#पूर्ण_अगर /* GL_OES_vertex_half_float */

#अगर_अघोषित GL_OES_vertex_type_10_10_10_2
#घोषणा GL_OES_vertex_type_10_10_10_2 1
#घोषणा GL_UNSIGNED_INT_10_10_10_2_OES    0x8DF6
#घोषणा GL_INT_10_10_10_2_OES             0x8DF7
#पूर्ण_अगर /* GL_OES_vertex_type_10_10_10_2 */

#अगर_अघोषित GL_OES_viewport_array
#घोषणा GL_OES_viewport_array 1
#घोषणा GL_MAX_VIEWPORTS_OES              0x825B
#घोषणा GL_VIEWPORT_SUBPIXEL_BITS_OES     0x825C
#घोषणा GL_VIEWPORT_BOUNDS_RANGE_OES      0x825D
#घोषणा GL_VIEWPORT_सूचकांक_PROVOKING_VERTEX_OES 0x825F
प्रकार व्योम (GL_APIENTRYP PFNGLVIEWPORTARRAYVOESPROC) (GLuint first, GLsizei गिनती, स्थिर GLfloat *v);
प्रकार व्योम (GL_APIENTRYP PFNGLVIEWPORTINDEXEDFOESPROC) (GLuint सूचकांक, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
प्रकार व्योम (GL_APIENTRYP PFNGLVIEWPORTINDEXEDFVOESPROC) (GLuint सूचकांक, स्थिर GLfloat *v);
प्रकार व्योम (GL_APIENTRYP PFNGLSCISSORARRAYVOESPROC) (GLuint first, GLsizei गिनती, स्थिर GLint *v);
प्रकार व्योम (GL_APIENTRYP PFNGLSCISSORINDEXEDOESPROC) (GLuint सूचकांक, GLint बायाँ, GLint bottom, GLsizei width, GLsizei height);
प्रकार व्योम (GL_APIENTRYP PFNGLSCISSORINDEXEDVOESPROC) (GLuint सूचकांक, स्थिर GLint *v);
प्रकार व्योम (GL_APIENTRYP PFNGLDEPTHRANGEARRAYFVOESPROC) (GLuint first, GLsizei गिनती, स्थिर GLfloat *v);
प्रकार व्योम (GL_APIENTRYP PFNGLDEPTHRANGEINDEXEDFOESPROC) (GLuint सूचकांक, GLfloat n, GLfloat f);
प्रकार व्योम (GL_APIENTRYP PFNGLGETFLOATI_VOESPROC) (GLenum target, GLuint सूचकांक, GLfloat *तथ्य);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glViewportArrayvOES (GLuint first, GLsizei गिनती, स्थिर GLfloat *v);
GL_APICALL व्योम GL_APIENTRY glViewportIndexedfOES (GLuint सूचकांक, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
GL_APICALL व्योम GL_APIENTRY glViewportIndexedfvOES (GLuint सूचकांक, स्थिर GLfloat *v);
GL_APICALL व्योम GL_APIENTRY glScissorArrayvOES (GLuint first, GLsizei गिनती, स्थिर GLint *v);
GL_APICALL व्योम GL_APIENTRY glScissorIndexedOES (GLuint सूचकांक, GLint बायाँ, GLint bottom, GLsizei width, GLsizei height);
GL_APICALL व्योम GL_APIENTRY glScissorIndexedvOES (GLuint सूचकांक, स्थिर GLint *v);
GL_APICALL व्योम GL_APIENTRY glDepthRangeArrayfvOES (GLuint first, GLsizei गिनती, स्थिर GLfloat *v);
GL_APICALL व्योम GL_APIENTRY glDepthRangeIndexedfOES (GLuint सूचकांक, GLfloat n, GLfloat f);
GL_APICALL व्योम GL_APIENTRY glGetFloati_vOES (GLenum target, GLuint सूचकांक, GLfloat *तथ्य);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_OES_viewport_array */

#अगर_अघोषित GL_AMD_compressed_3DC_texture
#घोषणा GL_AMD_compressed_3DC_texture 1
#घोषणा GL_3DC_X_AMD                      0x87F9
#घोषणा GL_3DC_XY_AMD                     0x87FA
#पूर्ण_अगर /* GL_AMD_compressed_3DC_texture */

#अगर_अघोषित GL_AMD_compressed_ATC_texture
#घोषणा GL_AMD_compressed_ATC_texture 1
#घोषणा GL_ATC_RGB_AMD                    0x8C92
#घोषणा GL_ATC_RGBA_EXPLICIT_ALPHA_AMD    0x8C93
#घोषणा GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD 0x87EE
#पूर्ण_अगर /* GL_AMD_compressed_ATC_texture */

#अगर_अघोषित GL_AMD_framebuffer_multisample_advanced
#घोषणा GL_AMD_framebuffer_multisample_advanced 1
#घोषणा GL_RENDERBUFFER_STORAGE_SAMPLES_AMD 0x91B2
#घोषणा GL_MAX_COLOR_FRAMEBUFFER_SAMPLES_AMD 0x91B3
#घोषणा GL_MAX_COLOR_FRAMEBUFFER_STORAGE_SAMPLES_AMD 0x91B4
#घोषणा GL_MAX_DEPTH_STENCIL_FRAMEBUFFER_SAMPLES_AMD 0x91B5
#घोषणा GL_अंक_SUPPORTED_MULTISAMPLE_MODES_AMD 0x91B6
#घोषणा GL_SUPPORTED_MULTISAMPLE_MODES_AMD 0x91B7
प्रकार व्योम (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC) (GLenum target, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei width, GLsizei height);
प्रकार व्योम (GL_APIENTRYP PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC) (GLuint renderbuffer, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei width, GLsizei height);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glRenderbufferStorageMultisampleAdvancedAMD (GLenum target, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei width, GLsizei height);
GL_APICALL व्योम GL_APIENTRY glNamedRenderbufferStorageMultisampleAdvancedAMD (GLuint renderbuffer, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei width, GLsizei height);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_AMD_framebuffer_multisample_advanced */

#अगर_अघोषित GL_AMD_performance_monitor
#घोषणा GL_AMD_performance_monitor 1
#घोषणा GL_गणक_TYPE_AMD               0x8BC0
#घोषणा GL_गणक_RANGE_AMD              0x8BC1
#घोषणा GL_UNSIGNED_INT64_AMD             0x8BC2
#घोषणा GL_PERCENTAGE_AMD                 0x8BC3
#घोषणा GL_PERFMON_परिणाम_AVAILABLE_AMD   0x8BC4
#घोषणा GL_PERFMON_परिणाम_आकार_AMD        0x8BC5
#घोषणा GL_PERFMON_परिणाम_AMD             0x8BC6
प्रकार व्योम (GL_APIENTRYP PFNGLGETPERFMONITORGROUPSAMDPROC) (GLint *अंक_Groups, GLsizei groups_आकार, GLuint *groups);
प्रकार व्योम (GL_APIENTRYP PFNGLGETPERFMONITORCOUNTERSAMDPROC) (GLuint group, GLint *अंक_Counters, GLint *maxActiveCounters, GLsizei गणक_आकार, GLuint *counters);
प्रकार व्योम (GL_APIENTRYP PFNGLGETPERFMONITORGROUPSTRINGAMDPROC) (GLuint group, GLsizei buf_आकार, GLsizei *लंबाई, GLchar *groupString);
प्रकार व्योम (GL_APIENTRYP PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC) (GLuint group, GLuint गणक, GLsizei buf_आकार, GLsizei *लंबाई, GLchar *गणक_String);
प्रकार व्योम (GL_APIENTRYP PFNGLGETPERFMONITORCOUNTERINFOAMDPROC) (GLuint group, GLuint गणक, GLenum pname, व्योम *तथ्य);
प्रकार व्योम (GL_APIENTRYP PFNGLGENPERFMONITORSAMDPROC) (GLsizei n, GLuint *monitors);
प्रकार व्योम (GL_APIENTRYP PFNGLDELETEPERFMONITORSAMDPROC) (GLsizei n, GLuint *monitors);
प्रकार व्योम (GL_APIENTRYP PFNGLSELECTPERFMONITORCOUNTERSAMDPROC) (GLuint monitor, GLboolean enable, GLuint group, GLint अंक_Counters, GLuint *गणक_List);
प्रकार व्योम (GL_APIENTRYP PFNGLBEGINPERFMONITORAMDPROC) (GLuint monitor);
प्रकार व्योम (GL_APIENTRYP PFNGLENDPERFMONITORAMDPROC) (GLuint monitor);
प्रकार व्योम (GL_APIENTRYP PFNGLGETPERFMONITORCOUNTERDATAAMDPROC) (GLuint monitor, GLenum pname, GLsizei तथ्य_आकार_2, GLuint *तथ्य, GLint *bytesWritten);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glGetPerfMonitorGroupsAMD (GLint *अंक_Groups, GLsizei groups_आकार, GLuint *groups);
GL_APICALL व्योम GL_APIENTRY glGetPerfMonitorCountersAMD (GLuint group, GLint *अंक_Counters, GLint *maxActiveCounters, GLsizei गणक_आकार, GLuint *counters);
GL_APICALL व्योम GL_APIENTRY glGetPerfMonitorGroupStringAMD (GLuint group, GLsizei buf_आकार, GLsizei *लंबाई, GLchar *groupString);
GL_APICALL व्योम GL_APIENTRY gl_Get_Perf_Monitor_गणक_String_AMD (GLuint group, GLuint गणक, GLsizei buf_आकार, GLsizei *लंबाई, GLchar *गणक_String);
GL_APICALL व्योम GL_APIENTRY gl_Get_Perf_Monitor_गणक_Info_AMD (GLuint group, GLuint गणक, GLenum pname, व्योम *तथ्य);
GL_APICALL व्योम GL_APIENTRY glGenPerfMonitorsAMD (GLsizei n, GLuint *monitors);
GL_APICALL व्योम GL_APIENTRY glDeletePerfMonitorsAMD (GLsizei n, GLuint *monitors);
GL_APICALL व्योम GL_APIENTRY glSelectPerfMonitorCountersAMD (GLuint monitor, GLboolean enable, GLuint group, GLint अंक_Counters, GLuint *गणक_List);
GL_APICALL व्योम GL_APIENTRY glBeginPerfMonitorAMD (GLuint monitor);
GL_APICALL व्योम GL_APIENTRY glEndPerfMonitorAMD (GLuint monitor);
GL_APICALL व्योम GL_APIENTRY gl_Get_Perf_Monitor_गणक_तथ्य_AMD (GLuint monitor, GLenum pname, GLsizei तथ्य_आकार_2, GLuint *तथ्य, GLint *bytesWritten);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_AMD_performance_monitor */

#अगर_अघोषित GL_AMD_program_द्विआधारी_Z400
#घोषणा GL_AMD_program_द्विआधारी_Z400 1
#घोषणा GL_Z400_द्विआधारी_AMD                0x8740
#पूर्ण_अगर /* GL_AMD_program_binary_Z400 */

#अगर_अघोषित GL_ANDROID_extension_pack_es31a
#घोषणा GL_ANDROID_extension_pack_es31a 1
#पूर्ण_अगर /* GL_ANDROID_extension_pack_es31a */

#अगर_अघोषित GL_ANGLE_depth_texture
#घोषणा GL_ANGLE_depth_texture 1
#पूर्ण_अगर /* GL_ANGLE_depth_texture */

#अगर_अघोषित GL_ANGLE_framebuffer_blit
#घोषणा GL_ANGLE_framebuffer_blit 1
#घोषणा GL_READ_FRAMEBUFFER_ANGLE         0x8CA8
#घोषणा GL_DRAW_FRAMEBUFFER_ANGLE         0x8CA9
#घोषणा GL_DRAW_FRAMEBUFFER_BINDING_ANGLE 0x8CA6
#घोषणा GL_READ_FRAMEBUFFER_BINDING_ANGLE 0x8CAA
प्रकार व्योम (GL_APIENTRYP PFNGLBLITFRAMEBUFFERANGLEPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glBlitFramebufferANGLE (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_ANGLE_framebuffer_blit */

#अगर_अघोषित GL_ANGLE_framebuffer_multisample
#घोषणा GL_ANGLE_framebuffer_multisample 1
#घोषणा GL_RENDERBUFFER_SAMPLES_ANGLE     0x8CAB
#घोषणा GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_ANGLE 0x8D56
#घोषणा GL_MAX_SAMPLES_ANGLE              0x8D57
प्रकार व्योम (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEANGLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glRenderbufferStorageMultisampleANGLE (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_ANGLE_framebuffer_multisample */

#अगर_अघोषित GL_ANGLE_instanced_arrays
#घोषणा GL_ANGLE_instanced_arrays 1
#घोषणा GL_VERTEX_ATTRIB_ARRAY_भाजक_ANGLE 0x88FE
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDANGLEPROC) (GLenum mode, GLint first, GLsizei गिनती, GLsizei primcount);
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDANGLEPROC) (GLenum mode, GLsizei गिनती, GLenum type, स्थिर व्योम *indices, GLsizei primcount);
प्रकार व्योम (GL_APIENTRYP PFNGLVERTEXATTRIBDIVISORANGLEPROC) (GLuint सूचकांक, GLuint भाजक);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glDrawArraysInstancedANGLE (GLenum mode, GLint first, GLsizei गिनती, GLsizei primcount);
GL_APICALL व्योम GL_APIENTRY glDrawElementsInstancedANGLE (GLenum mode, GLsizei गिनती, GLenum type, स्थिर व्योम *indices, GLsizei primcount);
GL_APICALL व्योम GL_APIENTRY gl_Vertex_Attrib_भाजक_ANGLE (GLuint सूचकांक, GLuint भाजक);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_ANGLE_instanced_arrays */

#अगर_अघोषित GL_ANGLE_pack_reverse_row_order
#घोषणा GL_ANGLE_pack_reverse_row_order 1
#घोषणा GL_PACK_REVERSE_ROW_ORDER_ANGLE   0x93A4
#पूर्ण_अगर /* GL_ANGLE_pack_reverse_row_order */

#अगर_अघोषित GL_ANGLE_program_द्विआधारी
#घोषणा GL_ANGLE_program_द्विआधारी 1
#घोषणा GL_PROGRAM_द्विआधारी_ANGLE           0x93A6
#पूर्ण_अगर /* GL_ANGLE_program_binary */

#अगर_अघोषित GL_ANGLE_texture_compression_dxt3
#घोषणा GL_ANGLE_texture_compression_dxt3 1
#घोषणा GL_COMPRESSED_RGBA_S3TC_DXT3_ANGLE 0x83F2
#पूर्ण_अगर /* GL_ANGLE_texture_compression_dxt3 */

#अगर_अघोषित GL_ANGLE_texture_compression_dxt5
#घोषणा GL_ANGLE_texture_compression_dxt5 1
#घोषणा GL_COMPRESSED_RGBA_S3TC_DXT5_ANGLE 0x83F3
#पूर्ण_अगर /* GL_ANGLE_texture_compression_dxt5 */

#अगर_अघोषित GL_ANGLE_texture_usage
#घोषणा GL_ANGLE_texture_usage 1
#घोषणा GL_TEXTURE_USAGE_ANGLE            0x93A2
#घोषणा GL_FRAMEBUFFER_ATTACHMENT_ANGLE   0x93A3
#पूर्ण_अगर /* GL_ANGLE_texture_usage */

#अगर_अघोषित GL_ANGLE_translated_shader_source
#घोषणा GL_ANGLE_translated_shader_source 1
#घोषणा GL_TRANSLATED_SHADER_SOURCE_लंबाई_ANGLE 0x93A0
प्रकार व्योम (GL_APIENTRYP PFNGLGETTRANSLATEDSHADERSOURCEANGLEPROC) (GLuint shader, GLsizei buf_आकार, GLsizei *लंबाई, GLchar *source);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glGetTranslatedShaderSourceANGLE (GLuint shader, GLsizei buf_आकार, GLsizei *लंबाई, GLchar *source);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_ANGLE_translated_shader_source */

#अगर_अघोषित GL_APPLE_clip_distance
#घोषणा GL_APPLE_clip_distance 1
#घोषणा GL_MAX_CLIP_DISTANCES_APPLE       0x0D32
#घोषणा GL_CLIP_DISTANCE0_APPLE           0x3000
#घोषणा GL_CLIP_DISTANCE1_APPLE           0x3001
#घोषणा GL_CLIP_DISTANCE2_APPLE           0x3002
#घोषणा GL_CLIP_DISTANCE3_APPLE           0x3003
#घोषणा GL_CLIP_DISTANCE4_APPLE           0x3004
#घोषणा GL_CLIP_DISTANCE5_APPLE           0x3005
#घोषणा GL_CLIP_DISTANCE6_APPLE           0x3006
#घोषणा GL_CLIP_DISTANCE7_APPLE           0x3007
#पूर्ण_अगर /* GL_APPLE_clip_distance */

#अगर_अघोषित GL_APPLE_color_बफर_packed_float
#घोषणा GL_APPLE_color_बफर_packed_float 1
#पूर्ण_अगर /* GL_APPLE_color_buffer_packed_float */

#अगर_अघोषित GL_APPLE_copy_texture_levels
#घोषणा GL_APPLE_copy_texture_levels 1
प्रकार व्योम (GL_APIENTRYP PFNGLCOPYTEXTURELEVELSAPPLEPROC) (GLuint destinationTexture, GLuint sourceTexture, GLint sourceBaseLevel, GLsizei source_Level_गिनती);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glCopyTextureLevelsAPPLE (GLuint destinationTexture, GLuint sourceTexture, GLint sourceBaseLevel, GLsizei source_Level_गिनती);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_APPLE_copy_texture_levels */

#अगर_अघोषित GL_APPLE_framebuffer_multisample
#घोषणा GL_APPLE_framebuffer_multisample 1
#घोषणा GL_RENDERBUFFER_SAMPLES_APPLE     0x8CAB
#घोषणा GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_APPLE 0x8D56
#घोषणा GL_MAX_SAMPLES_APPLE              0x8D57
#घोषणा GL_READ_FRAMEBUFFER_APPLE         0x8CA8
#घोषणा GL_DRAW_FRAMEBUFFER_APPLE         0x8CA9
#घोषणा GL_DRAW_FRAMEBUFFER_BINDING_APPLE 0x8CA6
#घोषणा GL_READ_FRAMEBUFFER_BINDING_APPLE 0x8CAA
प्रकार व्योम (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEAPPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
प्रकार व्योम (GL_APIENTRYP PFNGLRESOLVEMULTISAMPLEFRAMEBUFFERAPPLEPROC) (व्योम);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glRenderbufferStorageMultisampleAPPLE (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
GL_APICALL व्योम GL_APIENTRY glResolveMultisampleFramebufferAPPLE (व्योम);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_APPLE_framebuffer_multisample */

#अगर_अघोषित GL_APPLE_rgb_422
#घोषणा GL_APPLE_rgb_422 1
#घोषणा GL_RGB_422_APPLE                  0x8A1F
#घोषणा GL_UNSIGNED_SHORT_8_8_APPLE       0x85BA
#घोषणा GL_UNSIGNED_SHORT_8_8_REV_APPLE   0x85BB
#घोषणा GL_RGB_RAW_422_APPLE              0x8A51
#पूर्ण_अगर /* GL_APPLE_rgb_422 */

#अगर_अघोषित GL_APPLE_sync
#घोषणा GL_APPLE_sync 1
#घोषणा GL_SYNC_OBJECT_APPLE              0x8A53
#घोषणा GL_MAX_SERVER_WAIT_TIMEOUT_APPLE  0x9111
#घोषणा GL_OBJECT_TYPE_APPLE              0x9112
#घोषणा GL_SYNC_CONDITION_APPLE           0x9113
#घोषणा GL_SYNC_STATUS_APPLE              0x9114
#घोषणा GL_SYNC_FLAGS_APPLE               0x9115
#घोषणा GL_SYNC_FENCE_APPLE               0x9116
#घोषणा GL_SYNC_GPU_COMMANDS_COMPLETE_APPLE 0x9117
#घोषणा GL_UNSIGNALED_APPLE               0x9118
#घोषणा GL_SIGNALED_APPLE                 0x9119
#घोषणा GL_ALREADY_SIGNALED_APPLE         0x911A
#घोषणा GL_TIMEOUT_EXPIRED_APPLE          0x911B
#घोषणा GL_CONDITION_SATISFIED_APPLE      0x911C
#घोषणा GL_WAIT_FAILED_APPLE              0x911D
#घोषणा GL_SYNC_FLUSH_COMMANDS_BIT_APPLE  0x00000001
#घोषणा GL_TIMEOUT_IGNORED_APPLE          0xFFFFFFFFFFFFFFFFull
प्रकार GLsync (GL_APIENTRYP PFNGLFENCESYNCAPPLEPROC) (GLenum condition, GLbitfield flags);
प्रकार GLboolean (GL_APIENTRYP PFNGLISSYNCAPPLEPROC) (GLsync sync);
प्रकार व्योम (GL_APIENTRYP PFNGLDELETESYNCAPPLEPROC) (GLsync sync);
प्रकार GLenum (GL_APIENTRYP PFNGLCLIENTWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
प्रकार व्योम (GL_APIENTRYP PFNGLWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
प्रकार व्योम (GL_APIENTRYP PFNGLGETINTEGER64VAPPLEPROC) (GLenum pname, GLint64 *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETSYNCIVAPPLEPROC) (GLsync sync, GLenum pname, GLsizei गिनती, GLsizei *लंबाई, GLint *मूल्यावली);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL GLsync GL_APIENTRY glFenceSyncAPPLE (GLenum condition, GLbitfield flags);
GL_APICALL GLboolean GL_APIENTRY glIsSyncAPPLE (GLsync sync);
GL_APICALL व्योम GL_APIENTRY glDeleteSyncAPPLE (GLsync sync);
GL_APICALL GLenum GL_APIENTRY glClientWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_APICALL व्योम GL_APIENTRY glWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_APICALL व्योम GL_APIENTRY glGetInteger64vAPPLE (GLenum pname, GLint64 *params);
GL_APICALL व्योम GL_APIENTRY glGetSyncivAPPLE (GLsync sync, GLenum pname, GLsizei गिनती, GLsizei *लंबाई, GLint *मूल्यावली);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_APPLE_sync */

#अगर_अघोषित GL_APPLE_texture_format_BGRA8888
#घोषणा GL_APPLE_texture_format_BGRA8888 1
#घोषणा GL_BGRA_EXT                       0x80E1
#घोषणा GL_BGRA8_EXT                      0x93A1
#पूर्ण_अगर /* GL_APPLE_texture_format_BGRA8888 */

#अगर_अघोषित GL_APPLE_texture_max_level
#घोषणा GL_APPLE_texture_max_level 1
#घोषणा GL_TEXTURE_MAX_LEVEL_APPLE        0x813D
#पूर्ण_अगर /* GL_APPLE_texture_max_level */

#अगर_अघोषित GL_APPLE_texture_packed_float
#घोषणा GL_APPLE_texture_packed_float 1
#घोषणा GL_UNSIGNED_INT_10F_11F_11F_REV_APPLE 0x8C3B
#घोषणा GL_UNSIGNED_INT_5_9_9_9_REV_APPLE 0x8C3E
#घोषणा GL_R11F_G11F_B10F_APPLE           0x8C3A
#घोषणा GL_RGB9_E5_APPLE                  0x8C3D
#पूर्ण_अगर /* GL_APPLE_texture_packed_float */

#अगर_अघोषित GL_ARM_mali_program_द्विआधारी
#घोषणा GL_ARM_mali_program_द्विआधारी 1
#घोषणा GL_MALI_PROGRAM_द्विआधारी_ARM        0x8F61
#पूर्ण_अगर /* GL_ARM_mali_program_binary */

#अगर_अघोषित GL_ARM_mali_shader_द्विआधारी
#घोषणा GL_ARM_mali_shader_द्विआधारी 1
#घोषणा GL_MALI_SHADER_द्विआधारी_ARM         0x8F60
#पूर्ण_अगर /* GL_ARM_mali_shader_binary */

#अगर_अघोषित GL_ARM_rgba8
#घोषणा GL_ARM_rgba8 1
#पूर्ण_अगर /* GL_ARM_rgba8 */

#अगर_अघोषित GL_ARM_shader_core_properties
#घोषणा GL_ARM_shader_core_properties 1
#घोषणा GL_SHADER_CORE_गिनती_ARM          0x96F0
#घोषणा GL_SHADER_CORE_ACTIVE_गिनती_ARM   0x96F1
#घोषणा GL_SHADER_CORE_PRESENT_MASK_ARM   0x96F2
#घोषणा GL_SHADER_CORE_MAX_WARP_गिनती_ARM 0x96F3
#घोषणा GL_SHADER_CORE_PIXEL_RATE_ARM     0x96F4
#घोषणा GL_SHADER_CORE_TEXEL_RATE_ARM     0x96F5
#घोषणा GL_SHADER_CORE_FMA_RATE_ARM       0x96F6
प्रकार व्योम (GL_APIENTRYP PFNGLMAXACTIVESHADERCORESARMPROC) (GLuint गिनती);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glMaxActiveShaderCoresARM (GLuint गिनती);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_ARM_shader_core_properties */

#अगर_अघोषित GL_ARM_shader_framebuffer_fetch
#घोषणा GL_ARM_shader_framebuffer_fetch 1
#घोषणा GL_FETCH_PER_SAMPLE_ARM           0x8F65
#घोषणा GL_FRAGMENT_SHADER_FRAMEBUFFER_FETCH_MRT_ARM 0x8F66
#पूर्ण_अगर /* GL_ARM_shader_framebuffer_fetch */

#अगर_अघोषित GL_ARM_shader_framebuffer_fetch_depth_stencil
#घोषणा GL_ARM_shader_framebuffer_fetch_depth_stencil 1
#पूर्ण_अगर /* GL_ARM_shader_framebuffer_fetch_depth_stencil */

#अगर_अघोषित GL_ARM_texture_unnormalized_coordinates
#घोषणा GL_ARM_texture_unnormalized_coordinates 1
#घोषणा GL_TEXTURE_UNNORMALIZED_COORDINATES_ARM 0x8F6A
#पूर्ण_अगर /* GL_ARM_texture_unnormalized_coordinates */

#अगर_अघोषित GL_DMP_program_द्विआधारी
#घोषणा GL_DMP_program_द्विआधारी 1
#घोषणा GL_SMAPHS30_PROGRAM_द्विआधारी_DMP    0x9251
#घोषणा GL_SMAPHS_PROGRAM_द्विआधारी_DMP      0x9252
#घोषणा GL_DMP_PROGRAM_द्विआधारी_DMP         0x9253
#पूर्ण_अगर /* GL_DMP_program_binary */

#अगर_अघोषित GL_DMP_shader_द्विआधारी
#घोषणा GL_DMP_shader_द्विआधारी 1
#घोषणा GL_SHADER_द्विआधारी_DMP              0x9250
#पूर्ण_अगर /* GL_DMP_shader_binary */

#अगर_अघोषित GL_EXT_EGL_image_array
#घोषणा GL_EXT_EGL_image_array 1
#पूर्ण_अगर /* GL_EXT_EGL_image_array */

#अगर_अघोषित GL_EXT_EGL_image_storage
#घोषणा GL_EXT_EGL_image_storage 1
प्रकार व्योम (GL_APIENTRYP PFNGLEGLIMAGETARGETTEXSTORAGEEXTPROC) (GLenum target, GLeglImageOES image, स्थिर GLint* attrib_list);
प्रकार व्योम (GL_APIENTRYP PFNGLEGLIMAGETARGETTEXTURESTORAGEEXTPROC) (GLuint texture, GLeglImageOES image, स्थिर GLint* attrib_list);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glEGLImageTargetTexStorageEXT (GLenum target, GLeglImageOES image, स्थिर GLint* attrib_list);
GL_APICALL व्योम GL_APIENTRY glEGLImageTargetTextureStorageEXT (GLuint texture, GLeglImageOES image, स्थिर GLint* attrib_list);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_EGL_image_storage */

#अगर_अघोषित GL_EXT_EGL_image_storage_compression
#घोषणा GL_EXT_EGL_image_storage_compression 1
#घोषणा GL_SURFACE_COMPRESSION_EXT        0x96C0
#घोषणा GL_SURFACE_COMPRESSION_FIXED_RATE_NONE_EXT 0x96C1
#घोषणा GL_SURFACE_COMPRESSION_FIXED_RATE_DEFAULT_EXT 0x96C2
#पूर्ण_अगर /* GL_EXT_EGL_image_storage_compression */

#अगर_अघोषित GL_EXT_YUV_target
#घोषणा GL_EXT_YUV_target 1
#घोषणा GL_SAMPLER_EXTERNAL_2D_Y2Y_EXT    0x8BE7
#पूर्ण_अगर /* GL_EXT_YUV_target */

#अगर_अघोषित GL_EXT_base_instance
#घोषणा GL_EXT_base_instance 1
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEEXTPROC) (GLenum mode, GLint first, GLsizei गिनती, GLsizei instancecount, GLuint baseinstance);
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEEXTPROC) (GLenum mode, GLsizei गिनती, GLenum type, स्थिर व्योम *indices, GLsizei instancecount, GLuint baseinstance);
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEEXTPROC) (GLenum mode, GLsizei गिनती, GLenum type, स्थिर व्योम *indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glDrawArraysInstancedBaseInstanceEXT (GLenum mode, GLint first, GLsizei गिनती, GLsizei instancecount, GLuint baseinstance);
GL_APICALL व्योम GL_APIENTRY glDrawElementsInstancedBaseInstanceEXT (GLenum mode, GLsizei गिनती, GLenum type, स्थिर व्योम *indices, GLsizei instancecount, GLuint baseinstance);
GL_APICALL व्योम GL_APIENTRY glDrawElementsInstancedBaseVertexBaseInstanceEXT (GLenum mode, GLsizei गिनती, GLenum type, स्थिर व्योम *indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_base_instance */

#अगर_अघोषित GL_EXT_blend_func_extended
#घोषणा GL_EXT_blend_func_extended 1
#घोषणा GL_SRC1_COLOR_EXT                 0x88F9
#घोषणा GL_SRC1_ALPHA_EXT                 0x8589
#घोषणा GL_ONE_MINUS_SRC1_COLOR_EXT       0x88FA
#घोषणा GL_ONE_MINUS_SRC1_ALPHA_EXT       0x88FB
#घोषणा GL_SRC_ALPHA_SATURATE_EXT         0x0308
#घोषणा GL_LOCATION_सूचकांक_EXT             0x930F
#घोषणा GL_MAX_DUAL_SOURCE_DRAW_BUFFERS_EXT 0x88FC
प्रकार व्योम (GL_APIENTRYP PFNGLBINDFRAGDATALOCATIONINDEXEDEXTPROC) (GLuint program, GLuint color_संख्या, GLuint सूचकांक, स्थिर GLchar *name);
प्रकार व्योम (GL_APIENTRYP PFNGLBINDFRAGDATALOCATIONEXTPROC) (GLuint program, GLuint color, स्थिर GLchar *name);
प्रकार GLint (GL_APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONINDEXEXTPROC) (GLuint program, GLenum programInterface, स्थिर GLchar *name);
प्रकार GLint (GL_APIENTRYP PFNGLGETFRAGDATAINDEXEXTPROC) (GLuint program, स्थिर GLchar *name);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY gl_Bind_Frag_तथ्य_Location_Indexed_EXT (GLuint program, GLuint color_संख्या, GLuint सूचकांक, स्थिर GLchar *name);
GL_APICALL व्योम GL_APIENTRY gl_Bind_Frag_तथ्य_Location_EXT (GLuint program, GLuint color, स्थिर GLchar *name);
GL_APICALL GLint GL_APIENTRY gl_Get_Program_Resource_Location_सूचकांक_EXT (GLuint program, GLenum programInterface, स्थिर GLchar *name);
GL_APICALL GLint GL_APIENTRY gl_Get_Frag_तथ्य_सूचकांक_EXT (GLuint program, स्थिर GLchar *name);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_blend_func_extended */

#अगर_अघोषित GL_EXT_blend_minmax
#घोषणा GL_EXT_blend_minmax 1
#घोषणा GL_MIN_EXT                        0x8007
#घोषणा GL_MAX_EXT                        0x8008
#पूर्ण_अगर /* GL_EXT_blend_minmax */

#अगर_अघोषित GL_EXT_बफर_storage
#घोषणा GL_EXT_बफर_storage 1
#घोषणा GL_MAP_READ_BIT                   0x0001
#घोषणा GL_MAP_WRITE_BIT                  0x0002
#घोषणा GL_MAP_PERSISTENT_BIT_EXT         0x0040
#घोषणा GL_MAP_COHERENT_BIT_EXT           0x0080
#घोषणा GL_DYNAMIC_STORAGE_BIT_EXT        0x0100
#घोषणा GL_CLIENT_STORAGE_BIT_EXT         0x0200
#घोषणा GL_CLIENT_MAPPED_बफर_BARRIER_BIT_EXT 0x00004000
#घोषणा GL_बफर_IMMUTABLE_STORAGE_EXT   0x821F
#घोषणा GL_बफर_STORAGE_FLAGS_EXT       0x8220
प्रकार व्योम (GL_APIENTRYP PFNGLBUFFERSTORAGEEXTPROC) (GLenum target, GLsizeiptr आकार, स्थिर व्योम *तथ्य, GLbitfield flags);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY gl_बफर_Storage_EXT (GLenum target, GLsizeiptr आकार, स्थिर व्योम *तथ्य, GLbitfield flags);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_buffer_storage */

#अगर_अघोषित GL_EXT_clear_texture
#घोषणा GL_EXT_clear_texture 1
प्रकार व्योम (GL_APIENTRYP PFNGLCLEARTEXIMAGEEXTPROC) (GLuint texture, GLint level, GLenum format, GLenum type, स्थिर व्योम *तथ्य);
प्रकार व्योम (GL_APIENTRYP PFNGLCLEARTEXSUBIMAGEEXTPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, स्थिर व्योम *तथ्य);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glClearTexImageEXT (GLuint texture, GLint level, GLenum format, GLenum type, स्थिर व्योम *तथ्य);
GL_APICALL व्योम GL_APIENTRY glClearTexSubImageEXT (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, स्थिर व्योम *तथ्य);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_clear_texture */

#अगर_अघोषित GL_EXT_clip_control
#घोषणा GL_EXT_clip_control 1
#घोषणा GL_LOWER_बायाँ_EXT                 0x8CA1
#घोषणा GL_UPPER_बायाँ_EXT                 0x8CA2
#घोषणा GL_NEGATIVE_ONE_TO_ONE_EXT        0x935E
#घोषणा GL_ZERO_TO_ONE_EXT                0x935F
#घोषणा GL_CLIP_ORIGIN_EXT                0x935C
#घोषणा GL_CLIP_DEPTH_MODE_EXT            0x935D
प्रकार व्योम (GL_APIENTRYP PFNGLCLIPCONTROLEXTPROC) (GLenum origin, GLenum depth);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glClipControlEXT (GLenum origin, GLenum depth);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_clip_control */

#अगर_अघोषित GL_EXT_clip_cull_distance
#घोषणा GL_EXT_clip_cull_distance 1
#घोषणा GL_MAX_CLIP_DISTANCES_EXT         0x0D32
#घोषणा GL_MAX_CULL_DISTANCES_EXT         0x82F9
#घोषणा GL_MAX_COMBINED_CLIP_AND_CULL_DISTANCES_EXT 0x82FA
#घोषणा GL_CLIP_DISTANCE0_EXT             0x3000
#घोषणा GL_CLIP_DISTANCE1_EXT             0x3001
#घोषणा GL_CLIP_DISTANCE2_EXT             0x3002
#घोषणा GL_CLIP_DISTANCE3_EXT             0x3003
#घोषणा GL_CLIP_DISTANCE4_EXT             0x3004
#घोषणा GL_CLIP_DISTANCE5_EXT             0x3005
#घोषणा GL_CLIP_DISTANCE6_EXT             0x3006
#घोषणा GL_CLIP_DISTANCE7_EXT             0x3007
#पूर्ण_अगर /* GL_EXT_clip_cull_distance */

#अगर_अघोषित GL_EXT_color_बफर_float
#घोषणा GL_EXT_color_बफर_float 1
#पूर्ण_अगर /* GL_EXT_color_buffer_float */

#अगर_अघोषित GL_EXT_color_बफर_half_float
#घोषणा GL_EXT_color_बफर_half_float 1
#घोषणा GL_RGBA16F_EXT                    0x881A
#घोषणा GL_RGB16F_EXT                     0x881B
#घोषणा GL_RG16F_EXT                      0x822F
#घोषणा GL_R16F_EXT                       0x822D
#घोषणा GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE_EXT 0x8211
#घोषणा GL_UNSIGNED_NORMALIZED_EXT        0x8C17
#पूर्ण_अगर /* GL_EXT_color_buffer_half_float */

#अगर_अघोषित GL_EXT_conservative_depth
#घोषणा GL_EXT_conservative_depth 1
#पूर्ण_अगर /* GL_EXT_conservative_depth */

#अगर_अघोषित GL_EXT_copy_image
#घोषणा GL_EXT_copy_image 1
प्रकार व्योम (GL_APIENTRYP PFNGLCOPYIMAGESUBDATAEXTPROC) (GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY gl_Copy_Image_Sub_तथ्य_EXT (GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_copy_image */

#अगर_अघोषित GL_EXT_debug_label
#घोषणा GL_EXT_debug_label 1
#घोषणा GL_PROGRAM_PIPELINE_OBJECT_EXT    0x8A4F
#घोषणा GL_PROGRAM_OBJECT_EXT             0x8B40
#घोषणा GL_SHADER_OBJECT_EXT              0x8B48
#घोषणा GL_बफर_OBJECT_EXT              0x9151
#घोषणा GL_QUERY_OBJECT_EXT               0x9153
#घोषणा GL_VERTEX_ARRAY_OBJECT_EXT        0x9154
#घोषणा GL_TRANSFORM_FEEDBACK             0x8E22
प्रकार व्योम (GL_APIENTRYP PFNGLLABELOBJECTEXTPROC) (GLenum type, GLuint object, GLsizei लंबाई, स्थिर GLchar *label);
प्रकार व्योम (GL_APIENTRYP PFNGLGETOBJECTLABELEXTPROC) (GLenum type, GLuint object, GLsizei buf_आकार, GLsizei *लंबाई, GLchar *label);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glLabelObjectEXT (GLenum type, GLuint object, GLsizei लंबाई, स्थिर GLchar *label);
GL_APICALL व्योम GL_APIENTRY glGetObjectLabelEXT (GLenum type, GLuint object, GLsizei buf_आकार, GLsizei *लंबाई, GLchar *label);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_debug_label */

#अगर_अघोषित GL_EXT_debug_marker
#घोषणा GL_EXT_debug_marker 1
प्रकार व्योम (GL_APIENTRYP PFNGLINSERTEVENTMARKEREXTPROC) (GLsizei लंबाई, स्थिर GLchar *marker);
प्रकार व्योम (GL_APIENTRYP PFNGLPUSHGROUPMARKEREXTPROC) (GLsizei लंबाई, स्थिर GLchar *marker);
प्रकार व्योम (GL_APIENTRYP PFNGLPOPGROUPMARKEREXTPROC) (व्योम);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY gl_जोड़ो_Event_Marker_EXT (GLsizei लंबाई, स्थिर GLchar *marker);
GL_APICALL व्योम GL_APIENTRY gl_धकेलो_Group_Marker_EXT (GLsizei लंबाई, स्थिर GLchar *marker);
GL_APICALL व्योम GL_APIENTRY gl_निकालो_Group_Marker_EXT (व्योम);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_debug_marker */

#अगर_अघोषित GL_EXT_depth_clamp
#घोषणा GL_EXT_depth_clamp 1
#घोषणा GL_DEPTH_CLAMP_EXT                0x864F
#पूर्ण_अगर /* GL_EXT_depth_clamp */

#अगर_अघोषित GL_EXT_discard_framebuffer
#घोषणा GL_EXT_discard_framebuffer 1
#घोषणा GL_COLOR_EXT                      0x1800
#घोषणा GL_DEPTH_EXT                      0x1801
#घोषणा GL_STENCIL_EXT                    0x1802
प्रकार व्योम (GL_APIENTRYP PFNGLDISCARDFRAMEBUFFEREXTPROC) (GLenum target, GLsizei अंक_Attachments, स्थिर GLenum *attachments);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glDiscardFramebufferEXT (GLenum target, GLsizei अंक_Attachments, स्थिर GLenum *attachments);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_discard_framebuffer */

#अगर_अघोषित GL_EXT_disjoint_timer_query
#घोषणा GL_EXT_disjoint_timer_query 1
#घोषणा GL_QUERY_गणक_BITS_EXT         0x8864
#घोषणा GL_CURRENT_QUERY_EXT              0x8865
#घोषणा GL_QUERY_परिणाम_EXT               0x8866
#घोषणा GL_QUERY_परिणाम_AVAILABLE_EXT     0x8867
#घोषणा GL_TIME_ELAPSED_EXT               0x88BF
#घोषणा GL_TIMESTAMP_EXT                  0x8E28
#घोषणा GL_GPU_DISJOINT_EXT               0x8FBB
प्रकार व्योम (GL_APIENTRYP PFNGLGENQUERIESEXTPROC) (GLsizei n, GLuint *ids);
प्रकार व्योम (GL_APIENTRYP PFNGLDELETEQUERIESEXTPROC) (GLsizei n, स्थिर GLuint *ids);
प्रकार GLboolean (GL_APIENTRYP PFNGLISQUERYEXTPROC) (GLuint id);
प्रकार व्योम (GL_APIENTRYP PFNGLBEGINQUERYEXTPROC) (GLenum target, GLuint id);
प्रकार व्योम (GL_APIENTRYP PFNGLENDQUERYEXTPROC) (GLenum target);
प्रकार व्योम (GL_APIENTRYP PFNGLQUERYCOUNTEREXTPROC) (GLuint id, GLenum target);
प्रकार व्योम (GL_APIENTRYP PFNGLGETQUERYIVEXTPROC) (GLenum target, GLenum pname, GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETQUERYOBJECTIVEXTPROC) (GLuint id, GLenum pname, GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETQUERYOBJECTUIVEXTPROC) (GLuint id, GLenum pname, GLuint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETQUERYOBJECTI64VEXTPROC) (GLuint id, GLenum pname, GLint64 *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETQUERYOBJECTUI64VEXTPROC) (GLuint id, GLenum pname, GLuint64 *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETINTEGER64VEXTPROC) (GLenum pname, GLint64 *तथ्य);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glGenQueriesEXT (GLsizei n, GLuint *ids);
GL_APICALL व्योम GL_APIENTRY glDeleteQueriesEXT (GLsizei n, स्थिर GLuint *ids);
GL_APICALL GLboolean GL_APIENTRY glIsQueryEXT (GLuint id);
GL_APICALL व्योम GL_APIENTRY glBeginQueryEXT (GLenum target, GLuint id);
GL_APICALL व्योम GL_APIENTRY glEndQueryEXT (GLenum target);
GL_APICALL व्योम GL_APIENTRY gl_Query_गणक_EXT (GLuint id, GLenum target);
GL_APICALL व्योम GL_APIENTRY glGetQueryivEXT (GLenum target, GLenum pname, GLint *params);
GL_APICALL व्योम GL_APIENTRY glGetQueryObjectivEXT (GLuint id, GLenum pname, GLint *params);
GL_APICALL व्योम GL_APIENTRY glGetQueryObjectuivEXT (GLuint id, GLenum pname, GLuint *params);
GL_APICALL व्योम GL_APIENTRY glGetQueryObjecti64vEXT (GLuint id, GLenum pname, GLint64 *params);
GL_APICALL व्योम GL_APIENTRY glGetQueryObjectui64vEXT (GLuint id, GLenum pname, GLuint64 *params);
GL_APICALL व्योम GL_APIENTRY glGetInteger64vEXT (GLenum pname, GLint64 *तथ्य);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_disjoint_timer_query */

#अगर_अघोषित GL_EXT_draw_buffers
#घोषणा GL_EXT_draw_buffers 1
#घोषणा GL_MAX_COLOR_ATTACHMENTS_EXT      0x8CDF
#घोषणा GL_MAX_DRAW_BUFFERS_EXT           0x8824
#घोषणा GL_DRAW_BUFFER0_EXT               0x8825
#घोषणा GL_DRAW_BUFFER1_EXT               0x8826
#घोषणा GL_DRAW_BUFFER2_EXT               0x8827
#घोषणा GL_DRAW_BUFFER3_EXT               0x8828
#घोषणा GL_DRAW_BUFFER4_EXT               0x8829
#घोषणा GL_DRAW_BUFFER5_EXT               0x882A
#घोषणा GL_DRAW_BUFFER6_EXT               0x882B
#घोषणा GL_DRAW_BUFFER7_EXT               0x882C
#घोषणा GL_DRAW_BUFFER8_EXT               0x882D
#घोषणा GL_DRAW_BUFFER9_EXT               0x882E
#घोषणा GL_DRAW_BUFFER10_EXT              0x882F
#घोषणा GL_DRAW_BUFFER11_EXT              0x8830
#घोषणा GL_DRAW_BUFFER12_EXT              0x8831
#घोषणा GL_DRAW_BUFFER13_EXT              0x8832
#घोषणा GL_DRAW_BUFFER14_EXT              0x8833
#घोषणा GL_DRAW_BUFFER15_EXT              0x8834
#घोषणा GL_COLOR_ATTACHMENT0_EXT          0x8CE0
#घोषणा GL_COLOR_ATTACHMENT1_EXT          0x8CE1
#घोषणा GL_COLOR_ATTACHMENT2_EXT          0x8CE2
#घोषणा GL_COLOR_ATTACHMENT3_EXT          0x8CE3
#घोषणा GL_COLOR_ATTACHMENT4_EXT          0x8CE4
#घोषणा GL_COLOR_ATTACHMENT5_EXT          0x8CE5
#घोषणा GL_COLOR_ATTACHMENT6_EXT          0x8CE6
#घोषणा GL_COLOR_ATTACHMENT7_EXT          0x8CE7
#घोषणा GL_COLOR_ATTACHMENT8_EXT          0x8CE8
#घोषणा GL_COLOR_ATTACHMENT9_EXT          0x8CE9
#घोषणा GL_COLOR_ATTACHMENT10_EXT         0x8CEA
#घोषणा GL_COLOR_ATTACHMENT11_EXT         0x8CEB
#घोषणा GL_COLOR_ATTACHMENT12_EXT         0x8CEC
#घोषणा GL_COLOR_ATTACHMENT13_EXT         0x8CED
#घोषणा GL_COLOR_ATTACHMENT14_EXT         0x8CEE
#घोषणा GL_COLOR_ATTACHMENT15_EXT         0x8CEF
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWBUFFERSEXTPROC) (GLsizei n, स्थिर GLenum *bufs);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glDrawBuffersEXT (GLsizei n, स्थिर GLenum *bufs);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_draw_buffers */

#अगर_अघोषित GL_EXT_draw_buffers_indexed
#घोषणा GL_EXT_draw_buffers_indexed 1
प्रकार व्योम (GL_APIENTRYP PFNGLENABLEIEXTPROC) (GLenum target, GLuint सूचकांक);
प्रकार व्योम (GL_APIENTRYP PFNGLDISABLEIEXTPROC) (GLenum target, GLuint सूचकांक);
प्रकार व्योम (GL_APIENTRYP PFNGLBLENDEQUATIONIEXTPROC) (GLuint buf, GLenum mode);
प्रकार व्योम (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEIEXTPROC) (GLuint buf, GLenum modeRGB, GLenum modeAlpha);
प्रकार व्योम (GL_APIENTRYP PFNGLBLENDFUNCIEXTPROC) (GLuint buf, GLenum src, GLenum dst);
प्रकार व्योम (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEIEXTPROC) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
प्रकार व्योम (GL_APIENTRYP PFNGLCOLORMASKIEXTPROC) (GLuint सूचकांक, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
प्रकार GLboolean (GL_APIENTRYP PFNGLISENABLEDIEXTPROC) (GLenum target, GLuint सूचकांक);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glEnableiEXT (GLenum target, GLuint सूचकांक);
GL_APICALL व्योम GL_APIENTRY glDisableiEXT (GLenum target, GLuint सूचकांक);
GL_APICALL व्योम GL_APIENTRY glBlendEquationiEXT (GLuint buf, GLenum mode);
GL_APICALL व्योम GL_APIENTRY glBlendEquationSeparateiEXT (GLuint buf, GLenum modeRGB, GLenum modeAlpha);
GL_APICALL व्योम GL_APIENTRY glBlendFunciEXT (GLuint buf, GLenum src, GLenum dst);
GL_APICALL व्योम GL_APIENTRY glBlendFuncSeparateiEXT (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
GL_APICALL व्योम GL_APIENTRY glColorMaskiEXT (GLuint सूचकांक, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
GL_APICALL GLboolean GL_APIENTRY glIsEnablediEXT (GLenum target, GLuint सूचकांक);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_draw_buffers_indexed */

#अगर_अघोषित GL_EXT_draw_elements_base_vertex
#घोषणा GL_EXT_draw_elements_base_vertex 1
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWELEMENTSBASEVERTEXEXTPROC) (GLenum mode, GLsizei गिनती, GLenum type, स्थिर व्योम *indices, GLint basevertex);
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWRANGEELEMENTSBASEVERTEXEXTPROC) (GLenum mode, GLuint start, GLuint end, GLsizei गिनती, GLenum type, स्थिर व्योम *indices, GLint basevertex);
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXEXTPROC) (GLenum mode, GLsizei गिनती, GLenum type, स्थिर व्योम *indices, GLsizei instancecount, GLint basevertex);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glDrawElementsBaseVertexEXT (GLenum mode, GLsizei गिनती, GLenum type, स्थिर व्योम *indices, GLint basevertex);
GL_APICALL व्योम GL_APIENTRY glDrawRangeElementsBaseVertexEXT (GLenum mode, GLuint start, GLuint end, GLsizei गिनती, GLenum type, स्थिर व्योम *indices, GLint basevertex);
GL_APICALL व्योम GL_APIENTRY glDrawElementsInstancedBaseVertexEXT (GLenum mode, GLsizei गिनती, GLenum type, स्थिर व्योम *indices, GLsizei instancecount, GLint basevertex);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_draw_elements_base_vertex */

#अगर_अघोषित GL_EXT_draw_instanced
#घोषणा GL_EXT_draw_instanced 1
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDEXTPROC) (GLenum mode, GLint start, GLsizei गिनती, GLsizei primcount);
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDEXTPROC) (GLenum mode, GLsizei गिनती, GLenum type, स्थिर व्योम *indices, GLsizei primcount);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glDrawArraysInstancedEXT (GLenum mode, GLint start, GLsizei गिनती, GLsizei primcount);
GL_APICALL व्योम GL_APIENTRY glDrawElementsInstancedEXT (GLenum mode, GLsizei गिनती, GLenum type, स्थिर व्योम *indices, GLsizei primcount);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_draw_instanced */

#अगर_अघोषित GL_EXT_draw_transform_feedback
#घोषणा GL_EXT_draw_transform_feedback 1
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKEXTPROC) (GLenum mode, GLuint id);
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDEXTPROC) (GLenum mode, GLuint id, GLsizei instancecount);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glDrawTransformFeedbackEXT (GLenum mode, GLuint id);
GL_APICALL व्योम GL_APIENTRY glDrawTransformFeedbackInstancedEXT (GLenum mode, GLuint id, GLsizei instancecount);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_draw_transform_feedback */

#अगर_अघोषित GL_EXT_external_बफर
#घोषणा GL_EXT_external_बफर 1
प्रकार व्योम *GLegl_Client_बफर_EXT;
प्रकार व्योम (GL_APIENTRYP PFNGLBUFFERSTORAGEEXTERNALEXTPROC) (GLenum target, GLintptr offset, GLsizeiptr आकार, GLegl_Client_बफर_EXT client_बफर, GLbitfield flags);
प्रकार व्योम (GL_APIENTRYP PFNGLNAMEDBUFFERSTORAGEEXTERNALEXTPROC) (GLuint बफर_2, GLintptr offset, GLsizeiptr आकार, GLegl_Client_बफर_EXT client_बफर, GLbitfield flags);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY gl_बफर_Storage_External_EXT (GLenum target, GLintptr offset, GLsizeiptr आकार, GLegl_Client_बफर_EXT client_बफर, GLbitfield flags);
GL_APICALL व्योम GL_APIENTRY gl_Named_बफर_Storage_External_EXT (GLuint बफर_2, GLintptr offset, GLsizeiptr आकार, GLegl_Client_बफर_EXT client_बफर, GLbitfield flags);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_external_buffer */

#अगर_अघोषित GL_EXT_float_blend
#घोषणा GL_EXT_float_blend 1
#पूर्ण_अगर /* GL_EXT_float_blend */

#अगर_अघोषित GL_EXT_fragment_shading_rate
#घोषणा GL_EXT_fragment_shading_rate 1
#घोषणा GL_SHADING_RATE_1X1_PIXELS_EXT    0x96A6
#घोषणा GL_SHADING_RATE_1X2_PIXELS_EXT    0x96A7
#घोषणा GL_SHADING_RATE_2X1_PIXELS_EXT    0x96A8
#घोषणा GL_SHADING_RATE_2X2_PIXELS_EXT    0x96A9
#घोषणा GL_SHADING_RATE_1X4_PIXELS_EXT    0x96AA
#घोषणा GL_SHADING_RATE_4X1_PIXELS_EXT    0x96AB
#घोषणा GL_SHADING_RATE_4X2_PIXELS_EXT    0x96AC
#घोषणा GL_SHADING_RATE_2X4_PIXELS_EXT    0x96AD
#घोषणा GL_SHADING_RATE_4X4_PIXELS_EXT    0x96AE
#घोषणा GL_SHADING_RATE_EXT               0x96D0
#घोषणा GL_SHADING_RATE_ATTACHMENT_EXT    0x96D1
#घोषणा GL_FRAGMENT_SHADING_RATE_COMBINER_OP_KEEP_EXT 0x96D2
#घोषणा GL_FRAGMENT_SHADING_RATE_COMBINER_OP_REPLACE_EXT 0x96D3
#घोषणा GL_FRAGMENT_SHADING_RATE_COMBINER_OP_MIN_EXT 0x96D4
#घोषणा GL_FRAGMENT_SHADING_RATE_COMBINER_OP_MAX_EXT 0x96D5
#घोषणा GL_FRAGMENT_SHADING_RATE_COMBINER_OP_MUL_EXT 0x96D6
#घोषणा GL_MIN_FRAGMENT_SHADING_RATE_ATTACHMENT_TEXEL_WIDTH_EXT 0x96D7
#घोषणा GL_MAX_FRAGMENT_SHADING_RATE_ATTACHMENT_TEXEL_WIDTH_EXT 0x96D8
#घोषणा GL_MIN_FRAGMENT_SHADING_RATE_ATTACHMENT_TEXEL_HEIGHT_EXT 0x96D9
#घोषणा GL_MAX_FRAGMENT_SHADING_RATE_ATTACHMENT_TEXEL_HEIGHT_EXT 0x96DA
#घोषणा GL_MAX_FRAGMENT_SHADING_RATE_ATTACHMENT_TEXEL_ASPECT_RATIO_EXT 0x96DB
#घोषणा GL_MAX_FRAGMENT_SHADING_RATE_ATTACHMENT_LAYERS_EXT 0x96DC
#घोषणा GL_FRAGMENT_SHADING_RATE_WITH_SHADER_DEPTH_STENCIL_WRITES_SUPPORTED_EXT 0x96DD
#घोषणा GL_FRAGMENT_SHADING_RATE_WITH_SAMPLE_MASK_SUPPORTED_EXT 0x96DE
#घोषणा GL_FRAGMENT_SHADING_RATE_ATTACHMENT_WITH_DEFAULT_FRAMEBUFFER_SUPPORTED_EXT 0x96DF
#घोषणा GL_FRAGMENT_SHADING_RATE_NON_TRIVIAL_COMBINERS_SUPPORTED_EXT 0x8F6F
प्रकार व्योम (GL_APIENTRYP PFNGLGETFRAGMENTSHADINGRATESEXTPROC) (GLsizei samples, GLsizei max_गिनती, GLsizei *गिनती, GLenum *shadingRates);
प्रकार व्योम (GL_APIENTRYP PFNGLSHADINGRATEEXTPROC) (GLenum rate);
प्रकार व्योम (GL_APIENTRYP PFNGLSHADINGRATECOMBINEROPSEXTPROC) (GLenum combinerOp0, GLenum combinerOp1);
प्रकार व्योम (GL_APIENTRYP PFNGLFRAMEBUFFERSHADINGRATEEXTPROC) (GLenum target, GLenum attachment, GLuint texture, GLint baseLayer, GLsizei अंक_Layers, GLsizei texelWidth, GLsizei texelHeight);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glGetFragmentShadingRatesEXT (GLsizei samples, GLsizei max_गिनती, GLsizei *गिनती, GLenum *shadingRates);
GL_APICALL व्योम GL_APIENTRY glShadingRateEXT (GLenum rate);
GL_APICALL व्योम GL_APIENTRY glShadingRateCombinerOpsEXT (GLenum combinerOp0, GLenum combinerOp1);
GL_APICALL व्योम GL_APIENTRY glFramebufferShadingRateEXT (GLenum target, GLenum attachment, GLuint texture, GLint baseLayer, GLsizei अंक_Layers, GLsizei texelWidth, GLsizei texelHeight);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_fragment_shading_rate */

#अगर_अघोषित GL_EXT_framebuffer_blit_layers
#घोषणा GL_EXT_framebuffer_blit_layers 1
प्रकार व्योम (GL_APIENTRYP PFNGLBLITFRAMEBUFFERLAYERSEXTPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
प्रकार व्योम (GL_APIENTRYP PFNGLBLITFRAMEBUFFERLAYEREXTPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint srcLayer, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLint dstLayer, GLbitfield mask, GLenum filter);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glBlitFramebufferLayersEXT (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
GL_APICALL व्योम GL_APIENTRY glBlitFramebufferLayerEXT (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint srcLayer, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLint dstLayer, GLbitfield mask, GLenum filter);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_framebuffer_blit_layers */

#अगर_अघोषित GL_EXT_geometry_point_आकार
#घोषणा GL_EXT_geometry_point_आकार 1
#पूर्ण_अगर /* GL_EXT_geometry_point_size */

#अगर_अघोषित GL_EXT_geometry_shader
#घोषणा GL_EXT_geometry_shader 1
#घोषणा GL_GEOMETRY_SHADER_EXT            0x8DD9
#घोषणा GL_GEOMETRY_SHADER_BIT_EXT        0x00000004
#घोषणा GL_GEOMETRY_LINKED_VERTICES_OUT_EXT 0x8916
#घोषणा GL_GEOMETRY_LINKED_निवेश_TYPE_EXT 0x8917
#घोषणा GL_GEOMETRY_LINKED_OUTPUT_TYPE_EXT 0x8918
#घोषणा GL_GEOMETRY_SHADER_INVOCATIONS_EXT 0x887F
#घोषणा GL_LAYER_PROVOKING_VERTEX_EXT     0x825E
#घोषणा GL_पंक्तियाँ_ADJACENCY_EXT            0x000A
#घोषणा GL_पंक्ति_STRIP_ADJACENCY_EXT       0x000B
#घोषणा GL_TRIANGLES_ADJACENCY_EXT        0x000C
#घोषणा GL_TRIANGLE_STRIP_ADJACENCY_EXT   0x000D
#घोषणा GL_MAX_GEOMETRY_UNIFORM_COMPONENTS_EXT 0x8DDF
#घोषणा GL_MAX_GEOMETRY_UNIFORM_BLOCKS_EXT 0x8A2C
#घोषणा GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS_EXT 0x8A32
#घोषणा GL_MAX_GEOMETRY_निवेश_COMPONENTS_EXT 0x9123
#घोषणा GL_MAX_GEOMETRY_OUTPUT_COMPONENTS_EXT 0x9124
#घोषणा GL_MAX_GEOMETRY_OUTPUT_VERTICES_EXT 0x8DE0
#घोषणा GL_MAX_GEOMETRY_योग_OUTPUT_COMPONENTS_EXT 0x8DE1
#घोषणा GL_MAX_GEOMETRY_SHADER_INVOCATIONS_EXT 0x8E5A
#घोषणा GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_EXT 0x8C29
#घोषणा GL_MAX_GEOMETRY_ATOMIC_गणक_BUFFERS_EXT 0x92CF
#घोषणा GL_MAX_GEOMETRY_ATOMIC_COUNTERS_EXT 0x92D5
#घोषणा GL_MAX_GEOMETRY_IMAGE_UNIFORMS_EXT 0x90CD
#घोषणा GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS_EXT 0x90D7
#घोषणा GL_FIRST_VERTEX_CONVENTION_EXT    0x8E4D
#घोषणा GL_LAST_VERTEX_CONVENTION_EXT     0x8E4E
#घोषणा GL_UNDEFINED_VERTEX_EXT           0x8260
#घोषणा GL_PRIMITIVES_GENERATED_EXT       0x8C87
#घोषणा GL_FRAMEBUFFER_DEFAULT_LAYERS_EXT 0x9312
#घोषणा GL_MAX_FRAMEBUFFER_LAYERS_EXT     0x9317
#घोषणा GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_EXT 0x8DA8
#घोषणा GL_FRAMEBUFFER_ATTACHMENT_LAYERED_EXT 0x8DA7
#घोषणा GL_REFERENCED_BY_GEOMETRY_SHADER_EXT 0x9309
प्रकार व्योम (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREEXTPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glFramebufferTextureEXT (GLenum target, GLenum attachment, GLuint texture, GLint level);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_geometry_shader */

#अगर_अघोषित GL_EXT_gpu_shader5
#घोषणा GL_EXT_gpu_shader5 1
#पूर्ण_अगर /* GL_EXT_gpu_shader5 */

#अगर_अघोषित GL_EXT_instanced_arrays
#घोषणा GL_EXT_instanced_arrays 1
#घोषणा GL_VERTEX_ATTRIB_ARRAY_भाजक_EXT 0x88FE
प्रकार व्योम (GL_APIENTRYP PFNGLVERTEXATTRIBDIVISOREXTPROC) (GLuint सूचकांक, GLuint भाजक);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY gl_Vertex_Attrib_भाजक_EXT (GLuint सूचकांक, GLuint भाजक);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_instanced_arrays */

#अगर_अघोषित GL_EXT_map_बफर_range
#घोषणा GL_EXT_map_बफर_range 1
#घोषणा GL_MAP_READ_BIT_EXT               0x0001
#घोषणा GL_MAP_WRITE_BIT_EXT              0x0002
#घोषणा GL_MAP_INVALIDATE_RANGE_BIT_EXT   0x0004
#घोषणा GL_MAP_INVALIDATE_बफर_BIT_EXT  0x0008
#घोषणा GL_MAP_FLUSH_EXPLICIT_BIT_EXT     0x0010
#घोषणा GL_MAP_UNSYNCHRONIZED_BIT_EXT     0x0020
प्रकार व्योम *(GL_APIENTRYP PFNGLMAPBUFFERRANGEEXTPROC) (GLenum target, GLintptr offset, GLsizeiptr लंबाई, GLbitfield access);
प्रकार व्योम (GL_APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEEXTPROC) (GLenum target, GLintptr offset, GLsizeiptr लंबाई);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम *GL_APIENTRY gl_Map_बफर_Range_EXT (GLenum target, GLintptr offset, GLsizeiptr लंबाई, GLbitfield access);
GL_APICALL व्योम GL_APIENTRY gl_Flush_Mapped_बफर_Range_EXT (GLenum target, GLintptr offset, GLsizeiptr लंबाई);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_map_buffer_range */

#अगर_अघोषित GL_EXT_memory_object
#घोषणा GL_EXT_memory_object 1
#घोषणा GL_TEXTURE_TILING_EXT             0x9580
#घोषणा GL_DEDICATED_MEMORY_OBJECT_EXT    0x9581
#घोषणा GL_PROTECTED_MEMORY_OBJECT_EXT    0x959B
#घोषणा GL_अंक_TILING_TYPES_EXT           0x9582
#घोषणा GL_TILING_TYPES_EXT               0x9583
#घोषणा GL_OPTIMAL_TILING_EXT             0x9584
#घोषणा GL_LINEAR_TILING_EXT              0x9585
#घोषणा GL_अंक_DEVICE_UUIDS_EXT           0x9596
#घोषणा GL_DEVICE_UUID_EXT                0x9597
#घोषणा GL_DRIVER_UUID_EXT                0x9598
#घोषणा GL_UUID_आकार_EXT                  16
प्रकार व्योम (GL_APIENTRYP PFNGLGETUNSIGNEDBYTEVEXTPROC) (GLenum pname, GLubyte *तथ्य);
प्रकार व्योम (GL_APIENTRYP PFNGLGETUNSIGNEDBYTEI_VEXTPROC) (GLenum target, GLuint सूचकांक, GLubyte *तथ्य);
प्रकार व्योम (GL_APIENTRYP PFNGLDELETEMEMORYOBJECTSEXTPROC) (GLsizei n, स्थिर GLuint *memoryObjects);
प्रकार GLboolean (GL_APIENTRYP PFNGLISMEMORYOBJECTEXTPROC) (GLuint memoryObject);
प्रकार व्योम (GL_APIENTRYP PFNGLCREATEMEMORYOBJECTSEXTPROC) (GLsizei n, GLuint *memoryObjects);
प्रकार व्योम (GL_APIENTRYP PFNGLMEMORYOBJECTPARAMETERIVEXTPROC) (GLuint memoryObject, GLenum pname, स्थिर GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETMEMORYOBJECTPARAMETERIVEXTPROC) (GLuint memoryObject, GLenum pname, GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXSTORAGEMEM2DEXTPROC) (GLenum target, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLuint memory, GLuint64 offset);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXSTORAGEMEM2DMULTISAMPLEEXTPROC) (GLenum target, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations, GLuint memory, GLuint64 offset);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXSTORAGEMEM3DEXTPROC) (GLenum target, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLuint memory, GLuint64 offset);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXSTORAGEMEM3DMULTISAMPLEEXTPROC) (GLenum target, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations, GLuint memory, GLuint64 offset);
प्रकार व्योम (GL_APIENTRYP PFNGLBUFFERSTORAGEMEMEXTPROC) (GLenum target, GLsizeiptr आकार, GLuint memory, GLuint64 offset);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXTURESTORAGEMEM2DEXTPROC) (GLuint texture, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLuint memory, GLuint64 offset);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXTURESTORAGEMEM2DMULTISAMPLEEXTPROC) (GLuint texture, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations, GLuint memory, GLuint64 offset);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXTURESTORAGEMEM3DEXTPROC) (GLuint texture, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLuint memory, GLuint64 offset);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXTURESTORAGEMEM3DMULTISAMPLEEXTPROC) (GLuint texture, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations, GLuint memory, GLuint64 offset);
प्रकार व्योम (GL_APIENTRYP PFNGLNAMEDBUFFERSTORAGEMEMEXTPROC) (GLuint बफर_2, GLsizeiptr आकार, GLuint memory, GLuint64 offset);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glGetUnsignedBytevEXT (GLenum pname, GLubyte *तथ्य);
GL_APICALL व्योम GL_APIENTRY glGetUnsignedBytei_vEXT (GLenum target, GLuint सूचकांक, GLubyte *तथ्य);
GL_APICALL व्योम GL_APIENTRY glDeleteMemoryObjectsEXT (GLsizei n, स्थिर GLuint *memoryObjects);
GL_APICALL GLboolean GL_APIENTRY glIsMemoryObjectEXT (GLuint memoryObject);
GL_APICALL व्योम GL_APIENTRY glCreateMemoryObjectsEXT (GLsizei n, GLuint *memoryObjects);
GL_APICALL व्योम GL_APIENTRY glMemoryObjectParameterivEXT (GLuint memoryObject, GLenum pname, स्थिर GLint *params);
GL_APICALL व्योम GL_APIENTRY glGetMemoryObjectParameterivEXT (GLuint memoryObject, GLenum pname, GLint *params);
GL_APICALL व्योम GL_APIENTRY glTexStorageMem2DEXT (GLenum target, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLuint memory, GLuint64 offset);
GL_APICALL व्योम GL_APIENTRY glTexStorageMem2DMultisampleEXT (GLenum target, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations, GLuint memory, GLuint64 offset);
GL_APICALL व्योम GL_APIENTRY glTexStorageMem3DEXT (GLenum target, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLuint memory, GLuint64 offset);
GL_APICALL व्योम GL_APIENTRY glTexStorageMem3DMultisampleEXT (GLenum target, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations, GLuint memory, GLuint64 offset);
GL_APICALL व्योम GL_APIENTRY gl_बफर_Storage_Mem_EXT (GLenum target, GLsizeiptr आकार, GLuint memory, GLuint64 offset);
GL_APICALL व्योम GL_APIENTRY glTextureStorageMem2DEXT (GLuint texture, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLuint memory, GLuint64 offset);
GL_APICALL व्योम GL_APIENTRY glTextureStorageMem2DMultisampleEXT (GLuint texture, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations, GLuint memory, GLuint64 offset);
GL_APICALL व्योम GL_APIENTRY glTextureStorageMem3DEXT (GLuint texture, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLuint memory, GLuint64 offset);
GL_APICALL व्योम GL_APIENTRY glTextureStorageMem3DMultisampleEXT (GLuint texture, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations, GLuint memory, GLuint64 offset);
GL_APICALL व्योम GL_APIENTRY gl_Named_बफर_Storage_Mem_EXT (GLuint बफर_2, GLsizeiptr आकार, GLuint memory, GLuint64 offset);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_memory_object */

#अगर_अघोषित GL_EXT_memory_object_fd
#घोषणा GL_EXT_memory_object_fd 1
#घोषणा GL_HANDLE_TYPE_OPAQUE_FD_EXT      0x9586
प्रकार व्योम (GL_APIENTRYP PFNGLIMPORTMEMORYFDEXTPROC) (GLuint memory, GLuint64 आकार, GLenum handleType, GLint fd);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glImportMemoryFdEXT (GLuint memory, GLuint64 आकार, GLenum handleType, GLint fd);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_memory_object_fd */

#अगर_अघोषित GL_EXT_memory_object_win32
#घोषणा GL_EXT_memory_object_win32 1
#घोषणा GL_HANDLE_TYPE_OPAQUE_WIN32_EXT   0x9587
#घोषणा GL_HANDLE_TYPE_OPAQUE_WIN32_KMT_EXT 0x9588
#घोषणा GL_DEVICE_LUID_EXT                0x9599
#घोषणा GL_DEVICE_गाँठ_MASK_EXT           0x959A
#घोषणा GL_LUID_आकार_EXT                  8
#घोषणा GL_HANDLE_TYPE_D3D12_TILEPOOL_EXT 0x9589
#घोषणा GL_HANDLE_TYPE_D3D12_RESOURCE_EXT 0x958A
#घोषणा GL_HANDLE_TYPE_D3D11_IMAGE_EXT    0x958B
#घोषणा GL_HANDLE_TYPE_D3D11_IMAGE_KMT_EXT 0x958C
प्रकार व्योम (GL_APIENTRYP PFNGLIMPORTMEMORYWIN32HANDLEEXTPROC) (GLuint memory, GLuint64 आकार, GLenum handleType, व्योम *handle);
प्रकार व्योम (GL_APIENTRYP PFNGLIMPORTMEMORYWIN32NAMEEXTPROC) (GLuint memory, GLuint64 आकार, GLenum handleType, स्थिर व्योम *name);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glImportMemoryWin32HandleEXT (GLuint memory, GLuint64 आकार, GLenum handleType, व्योम *handle);
GL_APICALL व्योम GL_APIENTRY glImportMemoryWin32NameEXT (GLuint memory, GLuint64 आकार, GLenum handleType, स्थिर व्योम *name);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_memory_object_win32 */

#अगर_अघोषित GL_EXT_mesh_shader
#घोषणा GL_EXT_mesh_shader 1
#घोषणा GL_MESH_SHADER_EXT                0x9559
#घोषणा GL_TASK_SHADER_EXT                0x955A
#घोषणा GL_MAX_MESH_UNIFORM_BLOCKS_EXT    0x8E60
#घोषणा GL_MAX_MESH_TEXTURE_IMAGE_UNITS_EXT 0x8E61
#घोषणा GL_MAX_MESH_IMAGE_UNIFORMS_EXT    0x8E62
#घोषणा GL_MAX_MESH_UNIFORM_COMPONENTS_EXT 0x8E63
#घोषणा GL_MAX_MESH_ATOMIC_गणक_BUFFERS_EXT 0x8E64
#घोषणा GL_MAX_MESH_ATOMIC_COUNTERS_EXT   0x8E65
#घोषणा GL_MAX_MESH_SHADER_STORAGE_BLOCKS_EXT 0x8E66
#घोषणा GL_MAX_COMBINED_MESH_UNIFORM_COMPONENTS_EXT 0x8E67
#घोषणा GL_MAX_TASK_UNIFORM_BLOCKS_EXT    0x8E68
#घोषणा GL_MAX_TASK_TEXTURE_IMAGE_UNITS_EXT 0x8E69
#घोषणा GL_MAX_TASK_IMAGE_UNIFORMS_EXT    0x8E6A
#घोषणा GL_MAX_TASK_UNIFORM_COMPONENTS_EXT 0x8E6B
#घोषणा GL_MAX_TASK_ATOMIC_गणक_BUFFERS_EXT 0x8E6C
#घोषणा GL_MAX_TASK_ATOMIC_COUNTERS_EXT   0x8E6D
#घोषणा GL_MAX_TASK_SHADER_STORAGE_BLOCKS_EXT 0x8E6E
#घोषणा GL_MAX_COMBINED_TASK_UNIFORM_COMPONENTS_EXT 0x8E6F
#घोषणा GL_MAX_TASK_WORK_GROUP_योग_गिनती_EXT 0x9740
#घोषणा GL_MAX_MESH_WORK_GROUP_योग_गिनती_EXT 0x9741
#घोषणा GL_MAX_MESH_WORK_GROUP_INVOCATIONS_EXT 0x9757
#घोषणा GL_MAX_TASK_WORK_GROUP_INVOCATIONS_EXT 0x9759
#घोषणा GL_MAX_TASK_PAYLOAD_आकार_EXT      0x9742
#घोषणा GL_MAX_TASK_SHARED_MEMORY_आकार_EXT 0x9743
#घोषणा GL_MAX_MESH_SHARED_MEMORY_आकार_EXT 0x9744
#घोषणा GL_MAX_TASK_PAYLOAD_AND_SHARED_MEMORY_आकार_EXT 0x9745
#घोषणा GL_MAX_MESH_PAYLOAD_AND_SHARED_MEMORY_आकार_EXT 0x9746
#घोषणा GL_MAX_MESH_OUTPUT_MEMORY_आकार_EXT 0x9747
#घोषणा GL_MAX_MESH_PAYLOAD_AND_OUTPUT_MEMORY_आकार_EXT 0x9748
#घोषणा GL_MAX_MESH_OUTPUT_VERTICES_EXT   0x9538
#घोषणा GL_MAX_MESH_OUTPUT_PRIMITIVES_EXT 0x9756
#घोषणा GL_MAX_MESH_OUTPUT_COMPONENTS_EXT 0x9749
#घोषणा GL_MAX_MESH_OUTPUT_LAYERS_EXT     0x974A
#घोषणा GL_MAX_MESH_MULTIVIEW_VIEW_गिनती_EXT 0x9557
#घोषणा GL_MESH_OUTPUT_PER_VERTEX_GRANULARITY_EXT 0x92DF
#घोषणा GL_MESH_OUTPUT_PER_PRIMITIVE_GRANULARITY_EXT 0x9543
#घोषणा GL_MAX_PREFERRED_TASK_WORK_GROUP_INVOCATIONS_EXT 0x974B
#घोषणा GL_MAX_PREFERRED_MESH_WORK_GROUP_INVOCATIONS_EXT 0x974C
#घोषणा GL_MESH_PREFERS_LOCAL_INVOCATION_VERTEX_OUTPUT_EXT 0x974D
#घोषणा GL_MESH_PREFERS_LOCAL_INVOCATION_PRIMITIVE_OUTPUT_EXT 0x974E
#घोषणा GL_MESH_PREFERS_COMPACT_VERTEX_OUTPUT_EXT 0x974F
#घोषणा GL_MESH_PREFERS_COMPACT_PRIMITIVE_OUTPUT_EXT 0x9750
#घोषणा GL_MAX_TASK_WORK_GROUP_गिनती_EXT  0x9751
#घोषणा GL_MAX_MESH_WORK_GROUP_गिनती_EXT  0x9752
#घोषणा GL_MAX_MESH_WORK_GROUP_आकार_EXT   0x9758
#घोषणा GL_MAX_TASK_WORK_GROUP_आकार_EXT   0x975A
#घोषणा GL_MESH_WORK_GROUP_आकार_EXT       0x953E
#घोषणा GL_TASK_WORK_GROUP_आकार_EXT       0x953F
#घोषणा GL_MESH_VERTICES_OUT_EXT          0x9579
#घोषणा GL_MESH_PRIMITIVES_OUT_EXT        0x957A
#घोषणा GL_MESH_OUTPUT_TYPE_EXT           0x957B
#घोषणा GL_UNIFORM_BLOCK_REFERENCED_BY_MESH_SHADER_EXT 0x959C
#घोषणा GL_UNIFORM_BLOCK_REFERENCED_BY_TASK_SHADER_EXT 0x959D
#घोषणा GL_REFERENCED_BY_MESH_SHADER_EXT  0x95A0
#घोषणा GL_REFERENCED_BY_TASK_SHADER_EXT  0x95A1
#घोषणा GL_TASK_SHADER_INVOCATIONS_EXT    0x9753
#घोषणा GL_MESH_SHADER_INVOCATIONS_EXT    0x9754
#घोषणा GL_MESH_PRIMITIVES_GENERATED_EXT  0x9755
#घोषणा GL_MESH_SHADER_BIT_EXT            0x00000040
#घोषणा GL_TASK_SHADER_BIT_EXT            0x00000080
#घोषणा GL_MESH_SUBROUTINE_EXT            0x957C
#घोषणा GL_TASK_SUBROUTINE_EXT            0x957D
#घोषणा GL_MESH_SUBROUTINE_UNIFORM_EXT    0x957E
#घोषणा GL_TASK_SUBROUTINE_UNIFORM_EXT    0x957F
#घोषणा GL_ATOMIC_गणक_बफर_REFERENCED_BY_MESH_SHADER_EXT 0x959E
#घोषणा GL_ATOMIC_गणक_बफर_REFERENCED_BY_TASK_SHADER_EXT 0x959F
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWMESHTASKSEXTPROC) (GLuint अंक_groups_x, GLuint अंक_groups_y, GLuint अंक_groups_z);
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWMESHTASKSINDIRECTEXTPROC) (GLintptr indirect);
प्रकार व्योम (GL_APIENTRYP PFNGLMULTIDRAWMESHTASKSINDIRECTEXTPROC) (GLintptr indirect, GLsizei drawcount, GLsizei stride);
प्रकार व्योम (GL_APIENTRYP PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTEXTPROC) (GLintptr indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glDrawMeshTasksEXT (GLuint अंक_groups_x, GLuint अंक_groups_y, GLuint अंक_groups_z);
GL_APICALL व्योम GL_APIENTRY glDrawMeshTasksIndirectEXT (GLintptr indirect);
GL_APICALL व्योम GL_APIENTRY glMultiDrawMeshTasksIndirectEXT (GLintptr indirect, GLsizei drawcount, GLsizei stride);
GL_APICALL व्योम GL_APIENTRY gl_Multi_Draw_Mesh_Tasks_Indirect_गिनती_EXT (GLintptr indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_mesh_shader */

#अगर_अघोषित GL_EXT_multi_draw_arrays
#घोषणा GL_EXT_multi_draw_arrays 1
प्रकार व्योम (GL_APIENTRYP PFNGLMULTIDRAWARRAYSEXTPROC) (GLenum mode, स्थिर GLint *first, स्थिर GLsizei *गिनती, GLsizei primcount);
प्रकार व्योम (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSEXTPROC) (GLenum mode, स्थिर GLsizei *गिनती, GLenum type, स्थिर व्योम *स्थिर*indices, GLsizei primcount);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glMultiDrawArraysEXT (GLenum mode, स्थिर GLint *first, स्थिर GLsizei *गिनती, GLsizei primcount);
GL_APICALL व्योम GL_APIENTRY glMultiDrawElementsEXT (GLenum mode, स्थिर GLsizei *गिनती, GLenum type, स्थिर व्योम *स्थिर*indices, GLsizei primcount);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_multi_draw_arrays */

#अगर_अघोषित GL_EXT_multi_draw_indirect
#घोषणा GL_EXT_multi_draw_indirect 1
प्रकार व्योम (GL_APIENTRYP PFNGLMULTIDRAWARRAYSINDIRECTEXTPROC) (GLenum mode, स्थिर व्योम *indirect, GLsizei drawcount, GLsizei stride);
प्रकार व्योम (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSINDIRECTEXTPROC) (GLenum mode, GLenum type, स्थिर व्योम *indirect, GLsizei drawcount, GLsizei stride);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glMultiDrawArraysIndirectEXT (GLenum mode, स्थिर व्योम *indirect, GLsizei drawcount, GLsizei stride);
GL_APICALL व्योम GL_APIENTRY glMultiDrawElementsIndirectEXT (GLenum mode, GLenum type, स्थिर व्योम *indirect, GLsizei drawcount, GLsizei stride);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_multi_draw_indirect */

#अगर_अघोषित GL_EXT_multisampled_compatibility
#घोषणा GL_EXT_multisampled_compatibility 1
#घोषणा GL_MULTISAMPLE_EXT                0x809D
#घोषणा GL_SAMPLE_ALPHA_TO_ONE_EXT        0x809F
#पूर्ण_अगर /* GL_EXT_multisampled_compatibility */

#अगर_अघोषित GL_EXT_multisampled_render_to_texture
#घोषणा GL_EXT_multisampled_render_to_texture 1
#घोषणा GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SAMPLES_EXT 0x8D6C
#घोषणा GL_RENDERBUFFER_SAMPLES_EXT       0x8CAB
#घोषणा GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT 0x8D56
#घोषणा GL_MAX_SAMPLES_EXT                0x8D57
प्रकार व्योम (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
प्रकार व्योम (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEEXTPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glRenderbufferStorageMultisampleEXT (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
GL_APICALL व्योम GL_APIENTRY glFramebufferTexture2DMultisampleEXT (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_multisampled_render_to_texture */

#अगर_अघोषित GL_EXT_multisampled_render_to_texture2
#घोषणा GL_EXT_multisampled_render_to_texture2 1
#पूर्ण_अगर /* GL_EXT_multisampled_render_to_texture2 */

#अगर_अघोषित GL_EXT_multiview_draw_buffers
#घोषणा GL_EXT_multiview_draw_buffers 1
#घोषणा GL_COLOR_ATTACHMENT_EXT           0x90F0
#घोषणा GL_MULTIVIEW_EXT                  0x90F1
#घोषणा GL_DRAW_बफर_EXT                0x0C01
#घोषणा GL_READ_बफर_EXT                0x0C02
#घोषणा GL_MAX_MULTIVIEW_BUFFERS_EXT      0x90F2
प्रकार व्योम (GL_APIENTRYP PFNGLREADBUFFERINDEXEDEXTPROC) (GLenum src, GLint सूचकांक);
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWBUFFERSINDEXEDEXTPROC) (GLint n, स्थिर GLenum *location, स्थिर GLint *indices);
प्रकार व्योम (GL_APIENTRYP PFNGLGETINTEGERI_VEXTPROC) (GLenum target, GLuint सूचकांक, GLint *तथ्य);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY gl_Read_बफर_Indexed_EXT (GLenum src, GLint सूचकांक);
GL_APICALL व्योम GL_APIENTRY glDrawBuffersIndexedEXT (GLint n, स्थिर GLenum *location, स्थिर GLint *indices);
GL_APICALL व्योम GL_APIENTRY glGetIntegeri_vEXT (GLenum target, GLuint सूचकांक, GLint *तथ्य);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_multiview_draw_buffers */

#अगर_अघोषित GL_EXT_multiview_tessellation_geometry_shader
#घोषणा GL_EXT_multiview_tessellation_geometry_shader 1
#पूर्ण_अगर /* GL_EXT_multiview_tessellation_geometry_shader */

#अगर_अघोषित GL_EXT_multiview_texture_multisample
#घोषणा GL_EXT_multiview_texture_multisample 1
#पूर्ण_अगर /* GL_EXT_multiview_texture_multisample */

#अगर_अघोषित GL_EXT_multiview_timer_query
#घोषणा GL_EXT_multiview_timer_query 1
#पूर्ण_अगर /* GL_EXT_multiview_timer_query */

#अगर_अघोषित GL_EXT_occlusion_query_boolean
#घोषणा GL_EXT_occlusion_query_boolean 1
#घोषणा GL_ANY_SAMPLES_PASSED_EXT         0x8C2F
#घोषणा GL_ANY_SAMPLES_PASSED_CONSERVATIVE_EXT 0x8D6A
#पूर्ण_अगर /* GL_EXT_occlusion_query_boolean */

#अगर_अघोषित GL_EXT_polygon_offset_clamp
#घोषणा GL_EXT_polygon_offset_clamp 1
#घोषणा GL_POLYGON_OFFSET_CLAMP_EXT       0x8E1B
प्रकार व्योम (GL_APIENTRYP PFNGLPOLYGONOFFSETCLAMPEXTPROC) (GLfloat factor, GLfloat units, GLfloat clamp);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glPolygonOffsetClampEXT (GLfloat factor, GLfloat units, GLfloat clamp);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_polygon_offset_clamp */

#अगर_अघोषित GL_EXT_post_depth_coverage
#घोषणा GL_EXT_post_depth_coverage 1
#पूर्ण_अगर /* GL_EXT_post_depth_coverage */

#अगर_अघोषित GL_EXT_primitive_bounding_box
#घोषणा GL_EXT_primitive_bounding_box 1
#घोषणा GL_PRIMITIVE_BOUNDING_BOX_EXT     0x92BE
प्रकार व्योम (GL_APIENTRYP PFNGLPRIMITIVEBOUNDINGBOXEXTPROC) (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glPrimitiveBoundingBoxEXT (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_primitive_bounding_box */

#अगर_अघोषित GL_EXT_protected_textures
#घोषणा GL_EXT_protected_textures 1
#घोषणा GL_CONTEXT_FLAG_PROTECTED_CONTENT_BIT_EXT 0x00000010
#घोषणा GL_TEXTURE_PROTECTED_EXT          0x8BFA
#पूर्ण_अगर /* GL_EXT_protected_textures */

#अगर_अघोषित GL_EXT_pvrtc_sRGB
#घोषणा GL_EXT_pvrtc_sRGB 1
#घोषणा GL_COMPRESSED_SRGB_PVRTC_2BPPV1_EXT 0x8A54
#घोषणा GL_COMPRESSED_SRGB_PVRTC_4BPPV1_EXT 0x8A55
#घोषणा GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV1_EXT 0x8A56
#घोषणा GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV1_EXT 0x8A57
#घोषणा GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV2_IMG 0x93F0
#घोषणा GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV2_IMG 0x93F1
#पूर्ण_अगर /* GL_EXT_pvrtc_sRGB */

#अगर_अघोषित GL_EXT_raster_multisample
#घोषणा GL_EXT_raster_multisample 1
#घोषणा GL_RASTER_MULTISAMPLE_EXT         0x9327
#घोषणा GL_RASTER_SAMPLES_EXT             0x9328
#घोषणा GL_MAX_RASTER_SAMPLES_EXT         0x9329
#घोषणा GL_RASTER_FIXED_SAMPLE_LOCATIONS_EXT 0x932A
#घोषणा GL_MULTISAMPLE_RASTERIZATION_ALLOWED_EXT 0x932B
#घोषणा GL_EFFECTIVE_RASTER_SAMPLES_EXT   0x932C
प्रकार व्योम (GL_APIENTRYP PFNGLRASTERSAMPLESEXTPROC) (GLuint samples, GLboolean fixedsamplelocations);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glRasterSamplesEXT (GLuint samples, GLboolean fixedsamplelocations);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_raster_multisample */

#अगर_अघोषित GL_EXT_read_format_bgra
#घोषणा GL_EXT_read_format_bgra 1
#घोषणा GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT 0x8365
#घोषणा GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT 0x8366
#पूर्ण_अगर /* GL_EXT_read_format_bgra */

#अगर_अघोषित GL_EXT_render_snorm
#घोषणा GL_EXT_render_snorm 1
#घोषणा GL_R8_SNORM                       0x8F94
#घोषणा GL_RG8_SNORM                      0x8F95
#घोषणा GL_RGBA8_SNORM                    0x8F97
#घोषणा GL_R16_SNORM_EXT                  0x8F98
#घोषणा GL_RG16_SNORM_EXT                 0x8F99
#घोषणा GL_RGBA16_SNORM_EXT               0x8F9B
#पूर्ण_अगर /* GL_EXT_render_snorm */

#अगर_अघोषित GL_EXT_robustness
#घोषणा GL_EXT_robustness 1
#घोषणा GL_GUILTY_CONTEXT_RESET_EXT       0x8253
#घोषणा GL_INNOCENT_CONTEXT_RESET_EXT     0x8254
#घोषणा GL_UNKNOWN_CONTEXT_RESET_EXT      0x8255
#घोषणा GL_CONTEXT_ROBUST_ACCESS_EXT      0x90F3
#घोषणा GL_RESET_NOTIFICATION_STRATEGY_EXT 0x8256
#घोषणा GL_LOSE_CONTEXT_ON_RESET_EXT      0x8252
#घोषणा GL_NO_RESET_NOTIFICATION_EXT      0x8261
प्रकार GLenum (GL_APIENTRYP PFNGLGETGRAPHICSRESETSTATUSEXTPROC) (व्योम);
प्रकार व्योम (GL_APIENTRYP PFNGLREADNPIXELSEXTPROC) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei buf_आकार, व्योम *तथ्य);
प्रकार व्योम (GL_APIENTRYP PFNGLGETNUNIFORMFVEXTPROC) (GLuint program, GLint location, GLsizei buf_आकार, GLfloat *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETNUNIFORMIVEXTPROC) (GLuint program, GLint location, GLsizei buf_आकार, GLint *params);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL GLenum GL_APIENTRY glGetGraphicsResetStatusEXT (व्योम);
GL_APICALL व्योम GL_APIENTRY glReadnPixelsEXT (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei buf_आकार, व्योम *तथ्य);
GL_APICALL व्योम GL_APIENTRY glGetnUniformfvEXT (GLuint program, GLint location, GLsizei buf_आकार, GLfloat *params);
GL_APICALL व्योम GL_APIENTRY glGetnUniformivEXT (GLuint program, GLint location, GLsizei buf_आकार, GLint *params);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_robustness */

#अगर_अघोषित GL_EXT_sRGB
#घोषणा GL_EXT_sRGB 1
#घोषणा GL_SRGB_EXT                       0x8C40
#घोषणा GL_SRGB_ALPHA_EXT                 0x8C42
#घोषणा GL_SRGB8_ALPHA8_EXT               0x8C43
#घोषणा GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING_EXT 0x8210
#पूर्ण_अगर /* GL_EXT_sRGB */

#अगर_अघोषित GL_EXT_sRGB_write_control
#घोषणा GL_EXT_sRGB_write_control 1
#घोषणा GL_FRAMEBUFFER_SRGB_EXT           0x8DB9
#पूर्ण_अगर /* GL_EXT_sRGB_write_control */

#अगर_अघोषित GL_EXT_semaphore
#घोषणा GL_EXT_semaphore 1
#घोषणा GL_LAYOUT_GENERAL_EXT             0x958D
#घोषणा GL_LAYOUT_COLOR_ATTACHMENT_EXT    0x958E
#घोषणा GL_LAYOUT_DEPTH_STENCIL_ATTACHMENT_EXT 0x958F
#घोषणा GL_LAYOUT_DEPTH_STENCIL_READ_ONLY_EXT 0x9590
#घोषणा GL_LAYOUT_SHADER_READ_ONLY_EXT    0x9591
#घोषणा GL_LAYOUT_TRANSFER_SRC_EXT        0x9592
#घोषणा GL_LAYOUT_TRANSFER_DST_EXT        0x9593
#घोषणा GL_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_EXT 0x9530
#घोषणा GL_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_EXT 0x9531
प्रकार व्योम (GL_APIENTRYP PFNGLGENSEMAPHORESEXTPROC) (GLsizei n, GLuint *semaphores);
प्रकार व्योम (GL_APIENTRYP PFNGLDELETESEMAPHORESEXTPROC) (GLsizei n, स्थिर GLuint *semaphores);
प्रकार GLboolean (GL_APIENTRYP PFNGLISSEMAPHOREEXTPROC) (GLuint semaphore);
प्रकार व्योम (GL_APIENTRYP PFNGLSEMAPHOREPARAMETERUI64VEXTPROC) (GLuint semaphore, GLenum pname, स्थिर GLuint64 *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETSEMAPHOREPARAMETERUI64VEXTPROC) (GLuint semaphore, GLenum pname, GLuint64 *params);
प्रकार व्योम (GL_APIENTRYP PFNGLWAITSEMAPHOREEXTPROC) (GLuint semaphore, GLuint अंक_बफर_Barriers, स्थिर GLuint *buffers, GLuint अंक_Texture_Barriers, स्थिर GLuint *textures, स्थिर GLenum *srcLayouts);
प्रकार व्योम (GL_APIENTRYP PFNGLSIGNALSEMAPHOREEXTPROC) (GLuint semaphore, GLuint अंक_बफर_Barriers, स्थिर GLuint *buffers, GLuint अंक_Texture_Barriers, स्थिर GLuint *textures, स्थिर GLenum *dstLayouts);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glGenSemaphoresEXT (GLsizei n, GLuint *semaphores);
GL_APICALL व्योम GL_APIENTRY glDeleteSemaphoresEXT (GLsizei n, स्थिर GLuint *semaphores);
GL_APICALL GLboolean GL_APIENTRY glIsSemaphoreEXT (GLuint semaphore);
GL_APICALL व्योम GL_APIENTRY glSemaphoreParameterui64vEXT (GLuint semaphore, GLenum pname, स्थिर GLuint64 *params);
GL_APICALL व्योम GL_APIENTRY glGetSemaphoreParameterui64vEXT (GLuint semaphore, GLenum pname, GLuint64 *params);
GL_APICALL व्योम GL_APIENTRY glWaitSemaphoreEXT (GLuint semaphore, GLuint अंक_बफर_Barriers, स्थिर GLuint *buffers, GLuint अंक_Texture_Barriers, स्थिर GLuint *textures, स्थिर GLenum *srcLayouts);
GL_APICALL व्योम GL_APIENTRY glSignalSemaphoreEXT (GLuint semaphore, GLuint अंक_बफर_Barriers, स्थिर GLuint *buffers, GLuint अंक_Texture_Barriers, स्थिर GLuint *textures, स्थिर GLenum *dstLayouts);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_semaphore */

#अगर_अघोषित GL_EXT_semaphore_fd
#घोषणा GL_EXT_semaphore_fd 1
प्रकार व्योम (GL_APIENTRYP PFNGLIMPORTSEMAPHOREFDEXTPROC) (GLuint semaphore, GLenum handleType, GLint fd);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glImportSemaphoreFdEXT (GLuint semaphore, GLenum handleType, GLint fd);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_semaphore_fd */

#अगर_अघोषित GL_EXT_semaphore_win32
#घोषणा GL_EXT_semaphore_win32 1
#घोषणा GL_HANDLE_TYPE_D3D12_FENCE_EXT    0x9594
#घोषणा GL_D3_D12_FENCE_मूल्य_EXT          0x9595
प्रकार व्योम (GL_APIENTRYP PFNGLIMPORTSEMAPHOREWIN32HANDLEEXTPROC) (GLuint semaphore, GLenum handleType, व्योम *handle);
प्रकार व्योम (GL_APIENTRYP PFNGLIMPORTSEMAPHOREWIN32NAMEEXTPROC) (GLuint semaphore, GLenum handleType, स्थिर व्योम *name);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glImportSemaphoreWin32HandleEXT (GLuint semaphore, GLenum handleType, व्योम *handle);
GL_APICALL व्योम GL_APIENTRY glImportSemaphoreWin32NameEXT (GLuint semaphore, GLenum handleType, स्थिर व्योम *name);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_semaphore_win32 */

#अगर_अघोषित GL_EXT_separate_depth_stencil
#घोषणा GL_EXT_separate_depth_stencil 1
#पूर्ण_अगर /* GL_EXT_separate_depth_stencil */

#अगर_अघोषित GL_EXT_separate_shader_objects
#घोषणा GL_EXT_separate_shader_objects 1
#घोषणा GL_ACTIVE_PROGRAM_EXT             0x8259
#घोषणा GL_VERTEX_SHADER_BIT_EXT          0x00000001
#घोषणा GL_FRAGMENT_SHADER_BIT_EXT        0x00000002
#घोषणा GL_ALL_SHADER_BITS_EXT            0xFFFFFFFF
#घोषणा GL_PROGRAM_SEPARABLE_EXT          0x8258
#घोषणा GL_PROGRAM_PIPELINE_BINDING_EXT   0x825A
प्रकार व्योम (GL_APIENTRYP PFNGLACTIVESHADERPROGRAMEXTPROC) (GLuint pipeline, GLuint program);
प्रकार व्योम (GL_APIENTRYP PFNGLBINDPROGRAMPIPELINEEXTPROC) (GLuint pipeline);
प्रकार GLuint (GL_APIENTRYP PFNGLCREATESHADERPROGRAMVEXTPROC) (GLenum type, GLsizei गिनती, स्थिर GLchar *स्थिर*strings);
प्रकार व्योम (GL_APIENTRYP PFNGLDELETEPROGRAMPIPELINESEXTPROC) (GLsizei n, स्थिर GLuint *pipelines);
प्रकार व्योम (GL_APIENTRYP PFNGLGENPROGRAMPIPELINESEXTPROC) (GLsizei n, GLuint *pipelines);
प्रकार व्योम (GL_APIENTRYP PFNGLGETPROGRAMPIPELINEINFOLOGEXTPROC) (GLuint pipeline, GLsizei buf_आकार, GLsizei *लंबाई, GLchar *infoLog);
प्रकार व्योम (GL_APIENTRYP PFNGLGETPROGRAMPIPELINEIVEXTPROC) (GLuint pipeline, GLenum pname, GLint *params);
प्रकार GLboolean (GL_APIENTRYP PFNGLISPROGRAMPIPELINEEXTPROC) (GLuint pipeline);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMPARAMETERIEXTPROC) (GLuint program, GLenum pname, GLint मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM1FEXTPROC) (GLuint program, GLint location, GLfloat v0);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM1FVEXTPROC) (GLuint program, GLint location, GLsizei गिनती, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM1IEXTPROC) (GLuint program, GLint location, GLint v0);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM1IVEXTPROC) (GLuint program, GLint location, GLsizei गिनती, स्थिर GLint *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM2FEXTPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM2FVEXTPROC) (GLuint program, GLint location, GLsizei गिनती, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM2IEXTPROC) (GLuint program, GLint location, GLint v0, GLint v1);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM2IVEXTPROC) (GLuint program, GLint location, GLsizei गिनती, स्थिर GLint *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM3FEXTPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM3FVEXTPROC) (GLuint program, GLint location, GLsizei गिनती, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM3IEXTPROC) (GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM3IVEXTPROC) (GLuint program, GLint location, GLsizei गिनती, स्थिर GLint *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM4FEXTPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM4FVEXTPROC) (GLuint program, GLint location, GLsizei गिनती, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM4IEXTPROC) (GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM4IVEXTPROC) (GLuint program, GLint location, GLsizei गिनती, स्थिर GLint *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC) (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC) (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC) (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLUSEPROGRAMSTAGESEXTPROC) (GLuint pipeline, GLbitfield stages, GLuint program);
प्रकार व्योम (GL_APIENTRYP PFNGLVALIDATEPROGRAMPIPELINEEXTPROC) (GLuint pipeline);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UIEXTPROC) (GLuint program, GLint location, GLuint v0);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UIEXTPROC) (GLuint program, GLint location, GLuint v0, GLuint v1);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UIEXTPROC) (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UIEXTPROC) (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UIVEXTPROC) (GLuint program, GLint location, GLsizei गिनती, स्थिर GLuint *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UIVEXTPROC) (GLuint program, GLint location, GLsizei गिनती, स्थिर GLuint *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UIVEXTPROC) (GLuint program, GLint location, GLsizei गिनती, स्थिर GLuint *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UIVEXTPROC) (GLuint program, GLint location, GLsizei गिनती, स्थिर GLuint *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC) (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC) (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC) (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC) (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC) (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC) (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glActiveShaderProgramEXT (GLuint pipeline, GLuint program);
GL_APICALL व्योम GL_APIENTRY glBindProgramPipelineEXT (GLuint pipeline);
GL_APICALL GLuint GL_APIENTRY glCreateShaderProgramvEXT (GLenum type, GLsizei गिनती, स्थिर GLchar *स्थिर*strings);
GL_APICALL व्योम GL_APIENTRY glDeleteProgramPipelinesEXT (GLsizei n, स्थिर GLuint *pipelines);
GL_APICALL व्योम GL_APIENTRY glGenProgramPipelinesEXT (GLsizei n, GLuint *pipelines);
GL_APICALL व्योम GL_APIENTRY glGetProgramPipelineInfoLogEXT (GLuint pipeline, GLsizei buf_आकार, GLsizei *लंबाई, GLchar *infoLog);
GL_APICALL व्योम GL_APIENTRY glGetProgramPipelineivEXT (GLuint pipeline, GLenum pname, GLint *params);
GL_APICALL GLboolean GL_APIENTRY glIsProgramPipelineEXT (GLuint pipeline);
GL_APICALL व्योम GL_APIENTRY glProgramParameteriEXT (GLuint program, GLenum pname, GLint मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniform1fEXT (GLuint program, GLint location, GLfloat v0);
GL_APICALL व्योम GL_APIENTRY glProgramUniform1fvEXT (GLuint program, GLint location, GLsizei गिनती, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniform1iEXT (GLuint program, GLint location, GLint v0);
GL_APICALL व्योम GL_APIENTRY glProgramUniform1ivEXT (GLuint program, GLint location, GLsizei गिनती, स्थिर GLint *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniform2fEXT (GLuint program, GLint location, GLfloat v0, GLfloat v1);
GL_APICALL व्योम GL_APIENTRY glProgramUniform2fvEXT (GLuint program, GLint location, GLsizei गिनती, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniform2iEXT (GLuint program, GLint location, GLint v0, GLint v1);
GL_APICALL व्योम GL_APIENTRY glProgramUniform2ivEXT (GLuint program, GLint location, GLsizei गिनती, स्थिर GLint *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniform3fEXT (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
GL_APICALL व्योम GL_APIENTRY glProgramUniform3fvEXT (GLuint program, GLint location, GLsizei गिनती, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniform3iEXT (GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
GL_APICALL व्योम GL_APIENTRY glProgramUniform3ivEXT (GLuint program, GLint location, GLsizei गिनती, स्थिर GLint *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniform4fEXT (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
GL_APICALL व्योम GL_APIENTRY glProgramUniform4fvEXT (GLuint program, GLint location, GLsizei गिनती, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniform4iEXT (GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
GL_APICALL व्योम GL_APIENTRY glProgramUniform4ivEXT (GLuint program, GLint location, GLsizei गिनती, स्थिर GLint *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniformMatrix2fvEXT (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniformMatrix3fvEXT (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniformMatrix4fvEXT (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glUseProgramStagesEXT (GLuint pipeline, GLbitfield stages, GLuint program);
GL_APICALL व्योम GL_APIENTRY glValidateProgramPipelineEXT (GLuint pipeline);
GL_APICALL व्योम GL_APIENTRY glProgramUniform1uiEXT (GLuint program, GLint location, GLuint v0);
GL_APICALL व्योम GL_APIENTRY glProgramUniform2uiEXT (GLuint program, GLint location, GLuint v0, GLuint v1);
GL_APICALL व्योम GL_APIENTRY glProgramUniform3uiEXT (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
GL_APICALL व्योम GL_APIENTRY glProgramUniform4uiEXT (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
GL_APICALL व्योम GL_APIENTRY glProgramUniform1uivEXT (GLuint program, GLint location, GLsizei गिनती, स्थिर GLuint *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniform2uivEXT (GLuint program, GLint location, GLsizei गिनती, स्थिर GLuint *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniform3uivEXT (GLuint program, GLint location, GLsizei गिनती, स्थिर GLuint *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniform4uivEXT (GLuint program, GLint location, GLsizei गिनती, स्थिर GLuint *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniformMatrix2x3fvEXT (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniformMatrix3x2fvEXT (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniformMatrix2x4fvEXT (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniformMatrix4x2fvEXT (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniformMatrix3x4fvEXT (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniformMatrix4x3fvEXT (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_separate_shader_objects */

#अगर_अघोषित GL_EXT_shader_framebuffer_fetch
#घोषणा GL_EXT_shader_framebuffer_fetch 1
#घोषणा GL_FRAGMENT_SHADER_DISCARDS_SAMPLES_EXT 0x8A52
#पूर्ण_अगर /* GL_EXT_shader_framebuffer_fetch */

#अगर_अघोषित GL_EXT_shader_framebuffer_fetch_non_coherent
#घोषणा GL_EXT_shader_framebuffer_fetch_non_coherent 1
प्रकार व्योम (GL_APIENTRYP PFNGLFRAMEBUFFERFETCHBARRIEREXTPROC) (व्योम);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glFramebufferFetchBarrierEXT (व्योम);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_shader_framebuffer_fetch_non_coherent */

#अगर_अघोषित GL_EXT_shader_group_vote
#घोषणा GL_EXT_shader_group_vote 1
#पूर्ण_अगर /* GL_EXT_shader_group_vote */

#अगर_अघोषित GL_EXT_shader_implicit_conversions
#घोषणा GL_EXT_shader_implicit_conversions 1
#पूर्ण_अगर /* GL_EXT_shader_implicit_conversions */

#अगर_अघोषित GL_EXT_shader_integer_mix
#घोषणा GL_EXT_shader_integer_mix 1
#पूर्ण_अगर /* GL_EXT_shader_integer_mix */

#अगर_अघोषित GL_EXT_shader_io_blocks
#घोषणा GL_EXT_shader_io_blocks 1
#पूर्ण_अगर /* GL_EXT_shader_io_blocks */

#अगर_अघोषित GL_EXT_shader_non_constant_global_initializers
#घोषणा GL_EXT_shader_non_constant_global_initializers 1
#पूर्ण_अगर /* GL_EXT_shader_non_constant_global_initializers */

#अगर_अघोषित GL_EXT_shader_pixel_local_storage
#घोषणा GL_EXT_shader_pixel_local_storage 1
#घोषणा GL_MAX_SHADER_PIXEL_LOCAL_STORAGE_FAST_आकार_EXT 0x8F63
#घोषणा GL_MAX_SHADER_PIXEL_LOCAL_STORAGE_आकार_EXT 0x8F67
#घोषणा GL_SHADER_PIXEL_LOCAL_STORAGE_EXT 0x8F64
#पूर्ण_अगर /* GL_EXT_shader_pixel_local_storage */

#अगर_अघोषित GL_EXT_shader_pixel_local_storage2
#घोषणा GL_EXT_shader_pixel_local_storage2 1
#घोषणा GL_MAX_SHADER_COMBINED_LOCAL_STORAGE_FAST_आकार_EXT 0x9650
#घोषणा GL_MAX_SHADER_COMBINED_LOCAL_STORAGE_आकार_EXT 0x9651
#घोषणा GL_FRAMEBUFFER_INCOMPLETE_INSUFFICIENT_SHADER_COMBINED_LOCAL_STORAGE_EXT 0x9652
प्रकार व्योम (GL_APIENTRYP PFNGLFRAMEBUFFERPIXELLOCALSTORAGESIZEEXTPROC) (GLuint target, GLsizei आकार);
प्रकार GLsizei (GL_APIENTRYP PFNGLGETFRAMEBUFFERPIXELLOCALSTORAGESIZEEXTPROC) (GLuint target);
प्रकार व्योम (GL_APIENTRYP PFNGLCLEARPIXELLOCALSTORAGEUIEXTPROC) (GLsizei offset, GLsizei n, स्थिर GLuint *मूल्यावली);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY gl_Framebuffer_Pixel_Local_Storage_आकार_EXT (GLuint target, GLsizei आकार);
GL_APICALL GLsizei GL_APIENTRY gl_Get_Framebuffer_Pixel_Local_Storage_आकार_EXT (GLuint target);
GL_APICALL व्योम GL_APIENTRY glClearPixelLocalStorageuiEXT (GLsizei offset, GLsizei n, स्थिर GLuint *मूल्यावली);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_shader_pixel_local_storage2 */

#अगर_अघोषित GL_EXT_shader_samples_identical
#घोषणा GL_EXT_shader_samples_identical 1
#पूर्ण_अगर /* GL_EXT_shader_samples_identical */

#अगर_अघोषित GL_EXT_shader_texture_lod
#घोषणा GL_EXT_shader_texture_lod 1
#पूर्ण_अगर /* GL_EXT_shader_texture_lod */

#अगर_अघोषित GL_EXT_shader_texture_samples
#घोषणा GL_EXT_shader_texture_samples 1
#पूर्ण_अगर /* GL_EXT_shader_texture_samples */

#अगर_अघोषित GL_EXT_shadow_samplers
#घोषणा GL_EXT_shadow_samplers 1
#घोषणा GL_TEXTURE_COMPARE_MODE_EXT       0x884C
#घोषणा GL_TEXTURE_COMPARE_FUNC_EXT       0x884D
#घोषणा GL_COMPARE_REF_TO_TEXTURE_EXT     0x884E
#घोषणा GL_SAMPLER_2D_SHADOW_EXT          0x8B62
#पूर्ण_अगर /* GL_EXT_shadow_samplers */

#अगर_अघोषित GL_EXT_sparse_texture
#घोषणा GL_EXT_sparse_texture 1
#घोषणा GL_TEXTURE_SPARSE_EXT             0x91A6
#घोषणा GL_VIRTUAL_PAGE_आकार_सूचकांक_EXT    0x91A7
#घोषणा GL_अंक_SPARSE_LEVELS_EXT          0x91AA
#घोषणा GL_अंक_VIRTUAL_PAGE_SIZES_EXT     0x91A8
#घोषणा GL_VIRTUAL_PAGE_आकार_X_EXT        0x9195
#घोषणा GL_VIRTUAL_PAGE_आकार_Y_EXT        0x9196
#घोषणा GL_VIRTUAL_PAGE_आकार_Z_EXT        0x9197
#घोषणा GL_TEXTURE_2D_ARRAY               0x8C1A
#घोषणा GL_TEXTURE_3D                     0x806F
#घोषणा GL_MAX_SPARSE_TEXTURE_आकार_EXT    0x9198
#घोषणा GL_MAX_SPARSE_3_D_TEXTURE_आकार_EXT 0x9199
#घोषणा GL_MAX_SPARSE_ARRAY_TEXTURE_LAYERS_EXT 0x919A
#घोषणा GL_SPARSE_TEXTURE_FULL_ARRAY_CUBE_MIPMAPS_EXT 0x91A9
प्रकार व्योम (GL_APIENTRYP PFNGLTEXPAGECOMMITMENTEXTPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLboolean commit);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glTexPageCommitmentEXT (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLboolean commit);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_sparse_texture */

#अगर_अघोषित GL_EXT_sparse_texture2
#घोषणा GL_EXT_sparse_texture2 1
#पूर्ण_अगर /* GL_EXT_sparse_texture2 */

#अगर_अघोषित GL_EXT_tessellation_point_आकार
#घोषणा GL_EXT_tessellation_point_आकार 1
#पूर्ण_अगर /* GL_EXT_tessellation_point_size */

#अगर_अघोषित GL_EXT_tessellation_shader
#घोषणा GL_EXT_tessellation_shader 1
#घोषणा GL_PATCHES_EXT                    0x000E
#घोषणा GL_PATCH_VERTICES_EXT             0x8E72
#घोषणा GL_TESS_CONTROL_OUTPUT_VERTICES_EXT 0x8E75
#घोषणा GL_TESS_GEN_MODE_EXT              0x8E76
#घोषणा GL_TESS_GEN_SPACING_EXT           0x8E77
#घोषणा GL_TESS_GEN_VERTEX_ORDER_EXT      0x8E78
#घोषणा GL_TESS_GEN_POINT_MODE_EXT        0x8E79
#घोषणा GL_ISOLINES_EXT                   0x8E7A
#घोषणा GL_QUADS_EXT                      0x0007
#घोषणा GL_FRACTIONAL_ODD_EXT             0x8E7B
#घोषणा GL_FRACTIONAL_EVEN_EXT            0x8E7C
#घोषणा GL_MAX_PATCH_VERTICES_EXT         0x8E7D
#घोषणा GL_MAX_TESS_GEN_LEVEL_EXT         0x8E7E
#घोषणा GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS_EXT 0x8E7F
#घोषणा GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS_EXT 0x8E80
#घोषणा GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS_EXT 0x8E81
#घोषणा GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS_EXT 0x8E82
#घोषणा GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS_EXT 0x8E83
#घोषणा GL_MAX_TESS_PATCH_COMPONENTS_EXT  0x8E84
#घोषणा GL_MAX_TESS_CONTROL_योग_OUTPUT_COMPONENTS_EXT 0x8E85
#घोषणा GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS_EXT 0x8E86
#घोषणा GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS_EXT 0x8E89
#घोषणा GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS_EXT 0x8E8A
#घोषणा GL_MAX_TESS_CONTROL_निवेश_COMPONENTS_EXT 0x886C
#घोषणा GL_MAX_TESS_EVALUATION_निवेश_COMPONENTS_EXT 0x886D
#घोषणा GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS_EXT 0x8E1E
#घोषणा GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS_EXT 0x8E1F
#घोषणा GL_MAX_TESS_CONTROL_ATOMIC_गणक_BUFFERS_EXT 0x92CD
#घोषणा GL_MAX_TESS_EVALUATION_ATOMIC_गणक_BUFFERS_EXT 0x92CE
#घोषणा GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS_EXT 0x92D3
#घोषणा GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS_EXT 0x92D4
#घोषणा GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS_EXT 0x90CB
#घोषणा GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS_EXT 0x90CC
#घोषणा GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS_EXT 0x90D8
#घोषणा GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS_EXT 0x90D9
#घोषणा GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED 0x8221
#घोषणा GL_IS_PER_PATCH_EXT               0x92E7
#घोषणा GL_REFERENCED_BY_TESS_CONTROL_SHADER_EXT 0x9307
#घोषणा GL_REFERENCED_BY_TESS_EVALUATION_SHADER_EXT 0x9308
#घोषणा GL_TESS_CONTROL_SHADER_EXT        0x8E88
#घोषणा GL_TESS_EVALUATION_SHADER_EXT     0x8E87
#घोषणा GL_TESS_CONTROL_SHADER_BIT_EXT    0x00000008
#घोषणा GL_TESS_EVALUATION_SHADER_BIT_EXT 0x00000010
प्रकार व्योम (GL_APIENTRYP PFNGLPATCHPARAMETERIEXTPROC) (GLenum pname, GLint मूल्य);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glPatchParameteriEXT (GLenum pname, GLint मूल्य);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_tessellation_shader */

#अगर_अघोषित GL_EXT_texture_border_clamp
#घोषणा GL_EXT_texture_border_clamp 1
#घोषणा GL_TEXTURE_BORDER_COLOR_EXT       0x1004
#घोषणा GL_CLAMP_TO_BORDER_EXT            0x812D
प्रकार व्योम (GL_APIENTRYP PFNGLTEXPARAMETERIIVEXTPROC) (GLenum target, GLenum pname, स्थिर GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXPARAMETERIUIVEXTPROC) (GLenum target, GLenum pname, स्थिर GLuint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETTEXPARAMETERIIVEXTPROC) (GLenum target, GLenum pname, GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETTEXPARAMETERIUIVEXTPROC) (GLenum target, GLenum pname, GLuint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLSAMPLERPARAMETERIIVEXTPROC) (GLuint sampler, GLenum pname, स्थिर GLint *param);
प्रकार व्योम (GL_APIENTRYP PFNGLSAMPLERPARAMETERIUIVEXTPROC) (GLuint sampler, GLenum pname, स्थिर GLuint *param);
प्रकार व्योम (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIIVEXTPROC) (GLuint sampler, GLenum pname, GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIUIVEXTPROC) (GLuint sampler, GLenum pname, GLuint *params);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glTexParameterIivEXT (GLenum target, GLenum pname, स्थिर GLint *params);
GL_APICALL व्योम GL_APIENTRY glTexParameterIuivEXT (GLenum target, GLenum pname, स्थिर GLuint *params);
GL_APICALL व्योम GL_APIENTRY glGetTexParameterIivEXT (GLenum target, GLenum pname, GLint *params);
GL_APICALL व्योम GL_APIENTRY glGetTexParameterIuivEXT (GLenum target, GLenum pname, GLuint *params);
GL_APICALL व्योम GL_APIENTRY glSamplerParameterIivEXT (GLuint sampler, GLenum pname, स्थिर GLint *param);
GL_APICALL व्योम GL_APIENTRY glSamplerParameterIuivEXT (GLuint sampler, GLenum pname, स्थिर GLuint *param);
GL_APICALL व्योम GL_APIENTRY glGetSamplerParameterIivEXT (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL व्योम GL_APIENTRY glGetSamplerParameterIuivEXT (GLuint sampler, GLenum pname, GLuint *params);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_texture_border_clamp */

#अगर_अघोषित GL_EXT_texture_बफर
#घोषणा GL_EXT_texture_बफर 1
#घोषणा GL_TEXTURE_बफर_EXT             0x8C2A
#घोषणा GL_TEXTURE_बफर_BINDING_EXT     0x8C2A
#घोषणा GL_MAX_TEXTURE_बफर_आकार_EXT    0x8C2B
#घोषणा GL_TEXTURE_BINDING_बफर_EXT     0x8C2C
#घोषणा GL_TEXTURE_बफर_तथ्य_STORE_BINDING_EXT 0x8C2D
#घोषणा GL_TEXTURE_बफर_OFFSET_ALIGNMENT_EXT 0x919F
#घोषणा GL_SAMPLER_बफर_EXT             0x8DC2
#घोषणा GL_INT_SAMPLER_बफर_EXT         0x8DD0
#घोषणा GL_UNSIGNED_INT_SAMPLER_बफर_EXT 0x8DD8
#घोषणा GL_IMAGE_बफर_EXT               0x9051
#घोषणा GL_INT_IMAGE_बफर_EXT           0x905C
#घोषणा GL_UNSIGNED_INT_IMAGE_बफर_EXT  0x9067
#घोषणा GL_TEXTURE_बफर_OFFSET_EXT      0x919D
#घोषणा GL_TEXTURE_बफर_आकार_EXT        0x919E
प्रकार व्योम (GL_APIENTRYP PFNGLTEXBUFFEREXTPROC) (GLenum target, GLenum internalformat, GLuint बफर_2);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXBUFFERRANGEEXTPROC) (GLenum target, GLenum internalformat, GLuint बफर_2, GLintptr offset, GLsizeiptr आकार);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY gl_Tex_बफर_EXT (GLenum target, GLenum internalformat, GLuint बफर_2);
GL_APICALL व्योम GL_APIENTRY gl_Tex_बफर_Range_EXT (GLenum target, GLenum internalformat, GLuint बफर_2, GLintptr offset, GLsizeiptr आकार);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_texture_buffer */

#अगर_अघोषित GL_EXT_texture_compression_astc_decode_mode
#घोषणा GL_EXT_texture_compression_astc_decode_mode 1
#घोषणा GL_TEXTURE_ASTC_DECODE_PRECISION_EXT 0x8F69
#पूर्ण_अगर /* GL_EXT_texture_compression_astc_decode_mode */

#अगर_अघोषित GL_EXT_texture_compression_bptc
#घोषणा GL_EXT_texture_compression_bptc 1
#घोषणा GL_COMPRESSED_RGBA_BPTC_UNORM_EXT 0x8E8C
#घोषणा GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_EXT 0x8E8D
#घोषणा GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_EXT 0x8E8E
#घोषणा GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_EXT 0x8E8F
#पूर्ण_अगर /* GL_EXT_texture_compression_bptc */

#अगर_अघोषित GL_EXT_texture_compression_dxt1
#घोषणा GL_EXT_texture_compression_dxt1 1
#घोषणा GL_COMPRESSED_RGB_S3TC_DXT1_EXT   0x83F0
#घोषणा GL_COMPRESSED_RGBA_S3TC_DXT1_EXT  0x83F1
#पूर्ण_अगर /* GL_EXT_texture_compression_dxt1 */

#अगर_अघोषित GL_EXT_texture_compression_rgtc
#घोषणा GL_EXT_texture_compression_rgtc 1
#घोषणा GL_COMPRESSED_RED_RGTC1_EXT       0x8DBB
#घोषणा GL_COMPRESSED_SIGNED_RED_RGTC1_EXT 0x8DBC
#घोषणा GL_COMPRESSED_RED_GREEN_RGTC2_EXT 0x8DBD
#घोषणा GL_COMPRESSED_SIGNED_RED_GREEN_RGTC2_EXT 0x8DBE
#पूर्ण_अगर /* GL_EXT_texture_compression_rgtc */

#अगर_अघोषित GL_EXT_texture_compression_s3tc
#घोषणा GL_EXT_texture_compression_s3tc 1
#घोषणा GL_COMPRESSED_RGBA_S3TC_DXT3_EXT  0x83F2
#घोषणा GL_COMPRESSED_RGBA_S3TC_DXT5_EXT  0x83F3
#पूर्ण_अगर /* GL_EXT_texture_compression_s3tc */

#अगर_अघोषित GL_EXT_texture_compression_s3tc_srgb
#घोषणा GL_EXT_texture_compression_s3tc_srgb 1
#घोषणा GL_COMPRESSED_SRGB_S3TC_DXT1_EXT  0x8C4C
#घोषणा GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT 0x8C4D
#घोषणा GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT 0x8C4E
#घोषणा GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT 0x8C4F
#पूर्ण_अगर /* GL_EXT_texture_compression_s3tc_srgb */

#अगर_अघोषित GL_EXT_texture_cube_map_array
#घोषणा GL_EXT_texture_cube_map_array 1
#घोषणा GL_TEXTURE_CUBE_MAP_ARRAY_EXT     0x9009
#घोषणा GL_TEXTURE_BINDING_CUBE_MAP_ARRAY_EXT 0x900A
#घोषणा GL_SAMPLER_CUBE_MAP_ARRAY_EXT     0x900C
#घोषणा GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW_EXT 0x900D
#घोषणा GL_INT_SAMPLER_CUBE_MAP_ARRAY_EXT 0x900E
#घोषणा GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY_EXT 0x900F
#घोषणा GL_IMAGE_CUBE_MAP_ARRAY_EXT       0x9054
#घोषणा GL_INT_IMAGE_CUBE_MAP_ARRAY_EXT   0x905F
#घोषणा GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY_EXT 0x906A
#पूर्ण_अगर /* GL_EXT_texture_cube_map_array */

#अगर_अघोषित GL_EXT_texture_filter_anisotropic
#घोषणा GL_EXT_texture_filter_anisotropic 1
#घोषणा GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#घोषणा GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#पूर्ण_अगर /* GL_EXT_texture_filter_anisotropic */

#अगर_अघोषित GL_EXT_texture_filter_minmax
#घोषणा GL_EXT_texture_filter_minmax 1
#घोषणा GL_TEXTURE_REDUCTION_MODE_EXT     0x9366
#घोषणा GL_WEIGHTED_AVERAGE_EXT           0x9367
#पूर्ण_अगर /* GL_EXT_texture_filter_minmax */

#अगर_अघोषित GL_EXT_texture_format_BGRA8888
#घोषणा GL_EXT_texture_format_BGRA8888 1
#पूर्ण_अगर /* GL_EXT_texture_format_BGRA8888 */

#अगर_अघोषित GL_EXT_texture_format_sRGB_override
#घोषणा GL_EXT_texture_format_sRGB_override 1
#घोषणा GL_TEXTURE_FORMAT_SRGB_OVERRIDE_EXT 0x8FBF
#पूर्ण_अगर /* GL_EXT_texture_format_sRGB_override */

#अगर_अघोषित GL_EXT_texture_mirror_clamp_to_edge
#घोषणा GL_EXT_texture_mirror_clamp_to_edge 1
#घोषणा GL_MIRROR_CLAMP_TO_EDGE_EXT       0x8743
#पूर्ण_अगर /* GL_EXT_texture_mirror_clamp_to_edge */

#अगर_अघोषित GL_EXT_texture_norm16
#घोषणा GL_EXT_texture_norm16 1
#घोषणा GL_R16_EXT                        0x822A
#घोषणा GL_RG16_EXT                       0x822C
#घोषणा GL_RGBA16_EXT                     0x805B
#घोषणा GL_RGB16_EXT                      0x8054
#घोषणा GL_RGB16_SNORM_EXT                0x8F9A
#पूर्ण_अगर /* GL_EXT_texture_norm16 */

#अगर_अघोषित GL_EXT_texture_query_lod
#घोषणा GL_EXT_texture_query_lod 1
#पूर्ण_अगर /* GL_EXT_texture_query_lod */

#अगर_अघोषित GL_EXT_texture_rg
#घोषणा GL_EXT_texture_rg 1
#घोषणा GL_RED_EXT                        0x1903
#घोषणा GL_RG_EXT                         0x8227
#घोषणा GL_R8_EXT                         0x8229
#घोषणा GL_RG8_EXT                        0x822B
#पूर्ण_अगर /* GL_EXT_texture_rg */

#अगर_अघोषित GL_EXT_texture_sRGB_R8
#घोषणा GL_EXT_texture_sRGB_R8 1
#घोषणा GL_SR8_EXT                        0x8FBD
#पूर्ण_अगर /* GL_EXT_texture_sRGB_R8 */

#अगर_अघोषित GL_EXT_texture_sRGB_RG8
#घोषणा GL_EXT_texture_sRGB_RG8 1
#घोषणा GL_SRG8_EXT                       0x8FBE
#पूर्ण_अगर /* GL_EXT_texture_sRGB_RG8 */

#अगर_अघोषित GL_EXT_texture_sRGB_decode
#घोषणा GL_EXT_texture_sRGB_decode 1
#घोषणा GL_TEXTURE_SRGB_DECODE_EXT        0x8A48
#घोषणा GL_DECODE_EXT                     0x8A49
#घोषणा GL_SKIP_DECODE_EXT                0x8A4A
#पूर्ण_अगर /* GL_EXT_texture_sRGB_decode */

#अगर_अघोषित GL_EXT_texture_shadow_lod
#घोषणा GL_EXT_texture_shadow_lod 1
#पूर्ण_अगर /* GL_EXT_texture_shadow_lod */

#अगर_अघोषित GL_EXT_texture_storage
#घोषणा GL_EXT_texture_storage 1
#घोषणा GL_TEXTURE_IMMUTABLE_FORMAT_EXT   0x912F
#घोषणा GL_ALPHA8_EXT                     0x803C
#घोषणा GL_LUMINANCE8_EXT                 0x8040
#घोषणा GL_LUMINANCE8_ALPHA8_EXT          0x8045
#घोषणा GL_RGBA32F_EXT                    0x8814
#घोषणा GL_RGB32F_EXT                     0x8815
#घोषणा GL_ALPHA32F_EXT                   0x8816
#घोषणा GL_LUMINANCE32F_EXT               0x8818
#घोषणा GL_LUMINANCE_ALPHA32F_EXT         0x8819
#घोषणा GL_ALPHA16F_EXT                   0x881C
#घोषणा GL_LUMINANCE16F_EXT               0x881E
#घोषणा GL_LUMINANCE_ALPHA16F_EXT         0x881F
#घोषणा GL_R32F_EXT                       0x822E
#घोषणा GL_RG32F_EXT                      0x8230
प्रकार व्योम (GL_APIENTRYP PFNGLTEXSTORAGE1DEXTPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXSTORAGE2DEXTPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXSTORAGE3DEXTPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXTURESTORAGE1DEXTPROC) (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXTURESTORAGE2DEXTPROC) (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXTURESTORAGE3DEXTPROC) (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glTexStorage1DEXT (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
GL_APICALL व्योम GL_APIENTRY glTexStorage2DEXT (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
GL_APICALL व्योम GL_APIENTRY glTexStorage3DEXT (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
GL_APICALL व्योम GL_APIENTRY glTextureStorage1DEXT (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
GL_APICALL व्योम GL_APIENTRY glTextureStorage2DEXT (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
GL_APICALL व्योम GL_APIENTRY glTextureStorage3DEXT (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_texture_storage */

#अगर_अघोषित GL_EXT_texture_storage_compression
#घोषणा GL_EXT_texture_storage_compression 1
#घोषणा GL_अंक_SURFACE_COMPRESSION_FIXED_RATES_EXT 0x8F6E
#घोषणा GL_SURFACE_COMPRESSION_FIXED_RATE_1BPC_EXT 0x96C4
#घोषणा GL_SURFACE_COMPRESSION_FIXED_RATE_2BPC_EXT 0x96C5
#घोषणा GL_SURFACE_COMPRESSION_FIXED_RATE_3BPC_EXT 0x96C6
#घोषणा GL_SURFACE_COMPRESSION_FIXED_RATE_4BPC_EXT 0x96C7
#घोषणा GL_SURFACE_COMPRESSION_FIXED_RATE_5BPC_EXT 0x96C8
#घोषणा GL_SURFACE_COMPRESSION_FIXED_RATE_6BPC_EXT 0x96C9
#घोषणा GL_SURFACE_COMPRESSION_FIXED_RATE_7BPC_EXT 0x96CA
#घोषणा GL_SURFACE_COMPRESSION_FIXED_RATE_8BPC_EXT 0x96CB
#घोषणा GL_SURFACE_COMPRESSION_FIXED_RATE_9BPC_EXT 0x96CC
#घोषणा GL_SURFACE_COMPRESSION_FIXED_RATE_10BPC_EXT 0x96CD
#घोषणा GL_SURFACE_COMPRESSION_FIXED_RATE_11BPC_EXT 0x96CE
#घोषणा GL_SURFACE_COMPRESSION_FIXED_RATE_12BPC_EXT 0x96CF
प्रकार व्योम (GL_APIENTRYP PFNGLTEXSTORAGEATTRIBS2DEXTPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, स्थिर GLint* attrib_list);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXSTORAGEATTRIBS3DEXTPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, स्थिर GLint* attrib_list);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glTexStorageAttribs2DEXT (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, स्थिर GLint* attrib_list);
GL_APICALL व्योम GL_APIENTRY glTexStorageAttribs3DEXT (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, स्थिर GLint* attrib_list);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_texture_storage_compression */

#अगर_अघोषित GL_EXT_texture_type_2_10_10_10_REV
#घोषणा GL_EXT_texture_type_2_10_10_10_REV 1
#घोषणा GL_UNSIGNED_INT_2_10_10_10_REV_EXT 0x8368
#पूर्ण_अगर /* GL_EXT_texture_type_2_10_10_10_REV */

#अगर_अघोषित GL_EXT_texture_view
#घोषणा GL_EXT_texture_view 1
#घोषणा GL_TEXTURE_VIEW_MIN_LEVEL_EXT     0x82DB
#घोषणा GL_TEXTURE_VIEW_अंक_LEVELS_EXT    0x82DC
#घोषणा GL_TEXTURE_VIEW_MIN_LAYER_EXT     0x82DD
#घोषणा GL_TEXTURE_VIEW_अंक_LAYERS_EXT    0x82DE
प्रकार व्योम (GL_APIENTRYP PFNGLTEXTUREVIEWEXTPROC) (GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glTextureViewEXT (GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_texture_view */

#अगर_अघोषित GL_EXT_unpack_subimage
#घोषणा GL_EXT_unpack_subimage 1
#घोषणा GL_UNPACK_ROW_लंबाई_EXT          0x0CF2
#घोषणा GL_UNPACK_SKIP_ROWS_EXT           0x0CF3
#घोषणा GL_UNPACK_SKIP_PIXELS_EXT         0x0CF4
#पूर्ण_अगर /* GL_EXT_unpack_subimage */

#अगर_अघोषित GL_EXT_win32_keyed_mutex
#घोषणा GL_EXT_win32_keyed_mutex 1
प्रकार GLboolean (GL_APIENTRYP PFNGLACQUIREKEYEDMUTEXWIN32EXTPROC) (GLuint memory, GLuint64 कुंजी, GLuint timeout);
प्रकार GLboolean (GL_APIENTRYP PFNGLRELEASEKEYEDMUTEXWIN32EXTPROC) (GLuint memory, GLuint64 कुंजी);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL GLboolean GL_APIENTRY glAcquireKeyedMutexWin32EXT (GLuint memory, GLuint64 कुंजी, GLuint timeout);
GL_APICALL GLboolean GL_APIENTRY glReleaseKeyedMutexWin32EXT (GLuint memory, GLuint64 कुंजी);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_win32_keyed_mutex */

#अगर_अघोषित GL_EXT_window_rectangles
#घोषणा GL_EXT_window_rectangles 1
#घोषणा GL_INCLUSIVE_EXT                  0x8F10
#घोषणा GL_EXCLUSIVE_EXT                  0x8F11
#घोषणा GL_WINDOW_RECTANGLE_EXT           0x8F12
#घोषणा GL_WINDOW_RECTANGLE_MODE_EXT      0x8F13
#घोषणा GL_MAX_WINDOW_RECTANGLES_EXT      0x8F14
#घोषणा GL_अंक_WINDOW_RECTANGLES_EXT      0x8F15
प्रकार व्योम (GL_APIENTRYP PFNGLWINDOWRECTANGLESEXTPROC) (GLenum mode, GLsizei गिनती, स्थिर GLint *box);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glWindowRectanglesEXT (GLenum mode, GLsizei गिनती, स्थिर GLint *box);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_window_rectangles */

#अगर_अघोषित GL_FJ_shader_द्विआधारी_GCCSO
#घोषणा GL_FJ_shader_द्विआधारी_GCCSO 1
#घोषणा GL_GCCSO_SHADER_द्विआधारी_FJ         0x9260
#पूर्ण_अगर /* GL_FJ_shader_binary_GCCSO */

#अगर_अघोषित GL_HUAWEI_program_द्विआधारी
#घोषणा GL_HUAWEI_program_द्विआधारी 1
#घोषणा GL_PROGRAM_द्विआधारी_HUAWEI          0x9771
#पूर्ण_अगर /* GL_HUAWEI_program_binary */

#अगर_अघोषित GL_HUAWEI_shader_द्विआधारी
#घोषणा GL_HUAWEI_shader_द्विआधारी 1
#घोषणा GL_SHADER_द्विआधारी_HUAWEI           0x9770
#पूर्ण_अगर /* GL_HUAWEI_shader_binary */

#अगर_अघोषित GL_IMG_bindless_texture
#घोषणा GL_IMG_bindless_texture 1
प्रकार GLuint64 (GL_APIENTRYP PFNGLGETTEXTUREHANDLEIMGPROC) (GLuint texture);
प्रकार GLuint64 (GL_APIENTRYP PFNGLGETTEXTURESAMPLERHANDLEIMGPROC) (GLuint texture, GLuint sampler);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORMHANDLEUI64IMGPROC) (GLint location, GLuint64 मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORMHANDLEUI64VIMGPROC) (GLint location, GLsizei गिनती, स्थिर GLuint64 *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64IMGPROC) (GLuint program, GLint location, GLuint64 मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64VIMGPROC) (GLuint program, GLint location, GLsizei गिनती, स्थिर GLuint64 *मूल्यावली);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL GLuint64 GL_APIENTRY glGetTextureHandleIMG (GLuint texture);
GL_APICALL GLuint64 GL_APIENTRY glGetTextureSamplerHandleIMG (GLuint texture, GLuint sampler);
GL_APICALL व्योम GL_APIENTRY glUniformHandleui64IMG (GLint location, GLuint64 मूल्य);
GL_APICALL व्योम GL_APIENTRY glUniformHandleui64vIMG (GLint location, GLsizei गिनती, स्थिर GLuint64 *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniformHandleui64IMG (GLuint program, GLint location, GLuint64 मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniformHandleui64vIMG (GLuint program, GLint location, GLsizei गिनती, स्थिर GLuint64 *मूल्यावली);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_IMG_bindless_texture */

#अगर_अघोषित GL_IMG_framebuffer_downsample
#घोषणा GL_IMG_framebuffer_downsample 1
#घोषणा GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_AND_DOWNSAMPLE_IMG 0x913C
#घोषणा GL_अंक_DOWNSAMPLE_SCALES_IMG      0x913D
#घोषणा GL_DOWNSAMPLE_SCALES_IMG          0x913E
#घोषणा GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SCALE_IMG 0x913F
प्रकार व्योम (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DDOWNSAMPLEIMGPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint xscale, GLint yscale);
प्रकार व्योम (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURELAYERDOWNSAMPLEIMGPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer, GLint xscale, GLint yscale);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glFramebufferTexture2DDownsampleIMG (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint xscale, GLint yscale);
GL_APICALL व्योम GL_APIENTRY glFramebufferTextureLayerDownsampleIMG (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer, GLint xscale, GLint yscale);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_IMG_framebuffer_downsample */

#अगर_अघोषित GL_IMG_multisampled_render_to_texture
#घोषणा GL_IMG_multisampled_render_to_texture 1
#घोषणा GL_RENDERBUFFER_SAMPLES_IMG       0x9133
#घोषणा GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_IMG 0x9134
#घोषणा GL_MAX_SAMPLES_IMG                0x9135
#घोषणा GL_TEXTURE_SAMPLES_IMG            0x9136
प्रकार व्योम (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEIMGPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
प्रकार व्योम (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEIMGPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glRenderbufferStorageMultisampleIMG (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
GL_APICALL व्योम GL_APIENTRY glFramebufferTexture2DMultisampleIMG (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_IMG_multisampled_render_to_texture */

#अगर_अघोषित GL_IMG_program_द्विआधारी
#घोषणा GL_IMG_program_द्विआधारी 1
#घोषणा GL_SGX_PROGRAM_द्विआधारी_IMG         0x9130
#पूर्ण_अगर /* GL_IMG_program_binary */

#अगर_अघोषित GL_IMG_read_format
#घोषणा GL_IMG_read_format 1
#घोषणा GL_BGRA_IMG                       0x80E1
#घोषणा GL_UNSIGNED_SHORT_4_4_4_4_REV_IMG 0x8365
#पूर्ण_अगर /* GL_IMG_read_format */

#अगर_अघोषित GL_IMG_shader_द्विआधारी
#घोषणा GL_IMG_shader_द्विआधारी 1
#घोषणा GL_SGX_द्विआधारी_IMG                 0x8C0A
#पूर्ण_अगर /* GL_IMG_shader_binary */

#अगर_अघोषित GL_IMG_texture_compression_pvrtc
#घोषणा GL_IMG_texture_compression_pvrtc 1
#घोषणा GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG 0x8C00
#घोषणा GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG 0x8C01
#घोषणा GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG 0x8C02
#घोषणा GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG 0x8C03
#पूर्ण_अगर /* GL_IMG_texture_compression_pvrtc */

#अगर_अघोषित GL_IMG_texture_compression_pvrtc2
#घोषणा GL_IMG_texture_compression_pvrtc2 1
#घोषणा GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG 0x9137
#घोषणा GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG 0x9138
#पूर्ण_अगर /* GL_IMG_texture_compression_pvrtc2 */

#अगर_अघोषित GL_IMG_texture_filter_cubic
#घोषणा GL_IMG_texture_filter_cubic 1
#घोषणा GL_CUBIC_IMG                      0x9139
#घोषणा GL_CUBIC_MIPMAP_NEAREST_IMG       0x913A
#घोषणा GL_CUBIC_MIPMAP_LINEAR_IMG        0x913B
#पूर्ण_अगर /* GL_IMG_texture_filter_cubic */

#अगर_अघोषित GL_INTEL_blackhole_render
#घोषणा GL_INTEL_blackhole_render 1
#घोषणा GL_BLACKHOLE_RENDER_INTEL         0x83FC
#पूर्ण_अगर /* GL_INTEL_blackhole_render */

#अगर_अघोषित GL_INTEL_conservative_rasterization
#घोषणा GL_INTEL_conservative_rasterization 1
#घोषणा GL_CONSERVATIVE_RASTERIZATION_INTEL 0x83FE
#पूर्ण_अगर /* GL_INTEL_conservative_rasterization */

#अगर_अघोषित GL_INTEL_framebuffer_CMAA
#घोषणा GL_INTEL_framebuffer_CMAA 1
प्रकार व्योम (GL_APIENTRYP PFNGLAPPLYFRAMEBUFFERATTACHMENTCMAAINTELPROC) (व्योम);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glApplyFramebufferAttachmentCMAAINTEL (व्योम);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_INTEL_framebuffer_CMAA */

#अगर_अघोषित GL_INTEL_performance_query
#घोषणा GL_INTEL_performance_query 1
#घोषणा GL_PERFQUERY_SINGLE_CONTEXT_INTEL 0x00000000
#घोषणा GL_PERFQUERY_GLOBAL_CONTEXT_INTEL 0x00000001
#घोषणा GL_PERFQUERY_WAIT_INTEL           0x83FB
#घोषणा GL_PERFQUERY_FLUSH_INTEL          0x83FA
#घोषणा GL_PERFQUERY_DONOT_FLUSH_INTEL    0x83F9
#घोषणा GL_PERFQUERY_गणक_EVENT_INTEL  0x94F0
#घोषणा GL_PERFQUERY_गणक_DURATION_NORM_INTEL 0x94F1
#घोषणा GL_PERFQUERY_गणक_DURATION_RAW_INTEL 0x94F2
#घोषणा GL_PERFQUERY_गणक_THROUGHPUT_INTEL 0x94F3
#घोषणा GL_PERFQUERY_गणक_RAW_INTEL    0x94F4
#घोषणा GL_PERFQUERY_गणक_TIMESTAMP_INTEL 0x94F5
#घोषणा GL_PERFQUERY_गणक_तथ्य_UINT32_INTEL 0x94F8
#घोषणा GL_PERFQUERY_गणक_तथ्य_UINT64_INTEL 0x94F9
#घोषणा GL_PERFQUERY_गणक_तथ्य_FLOAT_INTEL 0x94FA
#घोषणा GL_PERFQUERY_गणक_तथ्य_DOUBLE_INTEL 0x94FB
#घोषणा GL_PERFQUERY_गणक_तथ्य_BOOL32_INTEL 0x94FC
#घोषणा GL_PERFQUERY_QUERY_NAME_लंबाई_MAX_INTEL 0x94FD
#घोषणा GL_PERFQUERY_गणक_NAME_लंबाई_MAX_INTEL 0x94FE
#घोषणा GL_PERFQUERY_गणक_DESC_लंबाई_MAX_INTEL 0x94FF
#घोषणा GL_PERFQUERY_GPA_EXTENDED_COUNTERS_INTEL 0x9500
प्रकार व्योम (GL_APIENTRYP PFNGLBEGINPERFQUERYINTELPROC) (GLuint queryHandle);
प्रकार व्योम (GL_APIENTRYP PFNGLCREATEPERFQUERYINTELPROC) (GLuint queryId, GLuint *queryHandle);
प्रकार व्योम (GL_APIENTRYP PFNGLDELETEPERFQUERYINTELPROC) (GLuint queryHandle);
प्रकार व्योम (GL_APIENTRYP PFNGLENDPERFQUERYINTELPROC) (GLuint queryHandle);
प्रकार व्योम (GL_APIENTRYP PFNGLGETFIRSTPERFQUERYIDINTELPROC) (GLuint *queryId);
प्रकार व्योम (GL_APIENTRYP PFNGLGETNEXTPERFQUERYIDINTELPROC) (GLuint queryId, GLuint *अग्र_Query_Id);
प्रकार व्योम (GL_APIENTRYP PFNGLGETPERFCOUNTERINFOINTELPROC) (GLuint queryId, GLuint गणक_Id, GLuint गणक_Name_लंबाई, GLchar *गणक_Name, GLuint गणक_Desc_लंबाई, GLchar *गणक_Desc, GLuint *गणक_Offset, GLuint *गणक_तथ्य_आकार, GLuint *गणक_Type_Enum, GLuint *गणक_तथ्य_Type_Enum, GLuint64 *raw_गणक_Max_मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLGETPERFQUERYDATAINTELPROC) (GLuint queryHandle, GLuint flags, GLsizei तथ्य_आकार_2, व्योम *तथ्य, GLuint *bytesWritten);
प्रकार व्योम (GL_APIENTRYP PFNGLGETPERFQUERYIDBYNAMEINTELPROC) (GLchar *queryName, GLuint *queryId);
प्रकार व्योम (GL_APIENTRYP PFNGLGETPERFQUERYINFOINTELPROC) (GLuint queryId, GLuint query_Name_लंबाई, GLchar *queryName, GLuint *तथ्य_आकार_2, GLuint *noCounters, GLuint *noInstances, GLuint *capsMask);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glBeginPerfQueryINTEL (GLuint queryHandle);
GL_APICALL व्योम GL_APIENTRY glCreatePerfQueryINTEL (GLuint queryId, GLuint *queryHandle);
GL_APICALL व्योम GL_APIENTRY glDeletePerfQueryINTEL (GLuint queryHandle);
GL_APICALL व्योम GL_APIENTRY glEndPerfQueryINTEL (GLuint queryHandle);
GL_APICALL व्योम GL_APIENTRY glGetFirstPerfQueryIdINTEL (GLuint *queryId);
GL_APICALL व्योम GL_APIENTRY gl_Get_अग्र_Perf_Query_Id_INTEL (GLuint queryId, GLuint *अग्र_Query_Id);
GL_APICALL व्योम GL_APIENTRY gl_Get_Perf_गणक_Info_INTEL (GLuint queryId, GLuint गणक_Id, GLuint गणक_Name_लंबाई, GLchar *गणक_Name, GLuint गणक_Desc_लंबाई, GLchar *गणक_Desc, GLuint *गणक_Offset, GLuint *गणक_तथ्य_आकार, GLuint *गणक_Type_Enum, GLuint *गणक_तथ्य_Type_Enum, GLuint64 *raw_गणक_Max_मूल्य);
GL_APICALL व्योम GL_APIENTRY gl_Get_Perf_Query_तथ्य_INTEL (GLuint queryHandle, GLuint flags, GLsizei तथ्य_आकार_2, व्योम *तथ्य, GLuint *bytesWritten);
GL_APICALL व्योम GL_APIENTRY glGetPerfQueryIdByNameINTEL (GLchar *queryName, GLuint *queryId);
GL_APICALL व्योम GL_APIENTRY glGetPerfQueryInfoINTEL (GLuint queryId, GLuint query_Name_लंबाई, GLchar *queryName, GLuint *तथ्य_आकार_2, GLuint *noCounters, GLuint *noInstances, GLuint *capsMask);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_INTEL_performance_query */

#अगर_अघोषित GL_MESA_bgra
#घोषणा GL_MESA_bgra 1
#घोषणा GL_BGR_EXT                        0x80E0
#पूर्ण_अगर /* GL_MESA_bgra */

#अगर_अघोषित GL_MESA_framebuffer_flip_x
#घोषणा GL_MESA_framebuffer_flip_x 1
#घोषणा GL_FRAMEBUFFER_FLIP_X_MESA        0x8BBC
#पूर्ण_अगर /* GL_MESA_framebuffer_flip_x */

#अगर_अघोषित GL_MESA_framebuffer_flip_y
#घोषणा GL_MESA_framebuffer_flip_y 1
#घोषणा GL_FRAMEBUFFER_FLIP_Y_MESA        0x8BBB
प्रकार व्योम (GL_APIENTRYP PFNGLFRAMEBUFFERPARAMETERIMESAPROC) (GLenum target, GLenum pname, GLint param);
प्रकार व्योम (GL_APIENTRYP PFNGLGETFRAMEBUFFERPARAMETERIVMESAPROC) (GLenum target, GLenum pname, GLint *params);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glFramebufferParameteriMESA (GLenum target, GLenum pname, GLint param);
GL_APICALL व्योम GL_APIENTRY glGetFramebufferParameterivMESA (GLenum target, GLenum pname, GLint *params);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_MESA_framebuffer_flip_y */

#अगर_अघोषित GL_MESA_framebuffer_swap_xy
#घोषणा GL_MESA_framebuffer_swap_xy 1
#घोषणा GL_FRAMEBUFFER_SWAP_XY_MESA       0x8BBD
#पूर्ण_अगर /* GL_MESA_framebuffer_swap_xy */

#अगर_अघोषित GL_MESA_program_द्विआधारी_formats
#घोषणा GL_MESA_program_द्विआधारी_formats 1
#घोषणा GL_PROGRAM_द्विआधारी_FORMAT_MESA     0x875F
#पूर्ण_अगर /* GL_MESA_program_binary_formats */

#अगर_अघोषित GL_MESA_sampler_objects
#घोषणा GL_MESA_sampler_objects 1
#घोषणा GL_SAMPLER_BINDING                0x8919
प्रकार व्योम (GL_APIENTRYP PFNGLGENSAMPLERSPROC) (GLsizei गिनती, GLuint *samplers);
प्रकार व्योम (GL_APIENTRYP PFNGLDELETESAMPLERSPROC) (GLsizei गिनती, स्थिर GLuint *samplers);
प्रकार GLboolean (GL_APIENTRYP PFNGLISSAMPLERPROC) (GLuint sampler);
प्रकार व्योम (GL_APIENTRYP PFNGLBINDSAMPLERPROC) (GLuint unit, GLuint sampler);
प्रकार व्योम (GL_APIENTRYP PFNGLSAMPLERPARAMETERIPROC) (GLuint sampler, GLenum pname, GLint param);
प्रकार व्योम (GL_APIENTRYP PFNGLSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, स्थिर GLint *param);
प्रकार व्योम (GL_APIENTRYP PFNGLSAMPLERPARAMETERFPROC) (GLuint sampler, GLenum pname, GLfloat param);
प्रकार व्योम (GL_APIENTRYP PFNGLSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, स्थिर GLfloat *param);
प्रकार व्योम (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, GLfloat *params);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glGenSamplers (GLsizei गिनती, GLuint *samplers);
GL_APICALL व्योम GL_APIENTRY glDeleteSamplers (GLsizei गिनती, स्थिर GLuint *samplers);
GL_APICALL GLboolean GL_APIENTRY glIsSampler (GLuint sampler);
GL_APICALL व्योम GL_APIENTRY glBindSampler (GLuint unit, GLuint sampler);
GL_APICALL व्योम GL_APIENTRY glSamplerParameteri (GLuint sampler, GLenum pname, GLint param);
GL_APICALL व्योम GL_APIENTRY glSamplerParameteriv (GLuint sampler, GLenum pname, स्थिर GLint *param);
GL_APICALL व्योम GL_APIENTRY glSamplerParameterf (GLuint sampler, GLenum pname, GLfloat param);
GL_APICALL व्योम GL_APIENTRY glSamplerParameterfv (GLuint sampler, GLenum pname, स्थिर GLfloat *param);
GL_APICALL व्योम GL_APIENTRY glGetSamplerParameteriv (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL व्योम GL_APIENTRY glGetSamplerParameterfv (GLuint sampler, GLenum pname, GLfloat *params);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_MESA_sampler_objects */

#अगर_अघोषित GL_MESA_shader_integer_functions
#घोषणा GL_MESA_shader_integer_functions 1
#पूर्ण_अगर /* GL_MESA_shader_integer_functions */

#अगर_अघोषित GL_MESA_texture_const_bandwidth
#घोषणा GL_MESA_texture_const_bandwidth 1
#घोषणा GL_CONST_BW_TILING_MESA           0x8BBE
#पूर्ण_अगर /* GL_MESA_texture_const_bandwidth */

#अगर_अघोषित GL_NVX_blend_equation_advanced_multi_draw_buffers
#घोषणा GL_NVX_blend_equation_advanced_multi_draw_buffers 1
#पूर्ण_अगर /* GL_NVX_blend_equation_advanced_multi_draw_buffers */

#अगर_अघोषित GL_NV_bindless_texture
#घोषणा GL_NV_bindless_texture 1
प्रकार GLuint64 (GL_APIENTRYP PFNGLGETTEXTUREHANDLENVPROC) (GLuint texture);
प्रकार GLuint64 (GL_APIENTRYP PFNGLGETTEXTURESAMPLERHANDLENVPROC) (GLuint texture, GLuint sampler);
प्रकार व्योम (GL_APIENTRYP PFNGLMAKETEXTUREHANDLERESIDENTNVPROC) (GLuint64 handle);
प्रकार व्योम (GL_APIENTRYP PFNGLMAKETEXTUREHANDLENONRESIDENTNVPROC) (GLuint64 handle);
प्रकार GLuint64 (GL_APIENTRYP PFNGLGETIMAGEHANDLENVPROC) (GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format);
प्रकार व्योम (GL_APIENTRYP PFNGLMAKEIMAGEHANDLERESIDENTNVPROC) (GLuint64 handle, GLenum access);
प्रकार व्योम (GL_APIENTRYP PFNGLMAKEIMAGEHANDLENONRESIDENTNVPROC) (GLuint64 handle);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORMHANDLEUI64NVPROC) (GLint location, GLuint64 मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORMHANDLEUI64VNVPROC) (GLint location, GLsizei गिनती, स्थिर GLuint64 *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64NVPROC) (GLuint program, GLint location, GLuint64 मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64VNVPROC) (GLuint program, GLint location, GLsizei गिनती, स्थिर GLuint64 *मूल्यावली);
प्रकार GLboolean (GL_APIENTRYP PFNGLISTEXTUREHANDLERESIDENTNVPROC) (GLuint64 handle);
प्रकार GLboolean (GL_APIENTRYP PFNGLISIMAGEHANDLERESIDENTNVPROC) (GLuint64 handle);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL GLuint64 GL_APIENTRY glGetTextureHandleNV (GLuint texture);
GL_APICALL GLuint64 GL_APIENTRY glGetTextureSamplerHandleNV (GLuint texture, GLuint sampler);
GL_APICALL व्योम GL_APIENTRY glMakeTextureHandleResidentNV (GLuint64 handle);
GL_APICALL व्योम GL_APIENTRY glMakeTextureHandleNonResidentNV (GLuint64 handle);
GL_APICALL GLuint64 GL_APIENTRY glGetImageHandleNV (GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format);
GL_APICALL व्योम GL_APIENTRY glMakeImageHandleResidentNV (GLuint64 handle, GLenum access);
GL_APICALL व्योम GL_APIENTRY glMakeImageHandleNonResidentNV (GLuint64 handle);
GL_APICALL व्योम GL_APIENTRY glUniformHandleui64NV (GLint location, GLuint64 मूल्य);
GL_APICALL व्योम GL_APIENTRY glUniformHandleui64vNV (GLint location, GLsizei गिनती, स्थिर GLuint64 *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniformHandleui64NV (GLuint program, GLint location, GLuint64 मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniformHandleui64vNV (GLuint program, GLint location, GLsizei गिनती, स्थिर GLuint64 *मूल्यावली);
GL_APICALL GLboolean GL_APIENTRY glIsTextureHandleResidentNV (GLuint64 handle);
GL_APICALL GLboolean GL_APIENTRY glIsImageHandleResidentNV (GLuint64 handle);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_NV_bindless_texture */

#अगर_अघोषित GL_NV_blend_equation_advanced
#घोषणा GL_NV_blend_equation_advanced 1
#घोषणा GL_BLEND_OVERLAP_NV               0x9281
#घोषणा GL_BLEND_PREMULTIPLIED_SRC_NV     0x9280
#घोषणा GL_BLUE_NV                        0x1905
#घोषणा GL_COLORBURN_NV                   0x929A
#घोषणा GL_COLORDODGE_NV                  0x9299
#घोषणा GL_CONJOINT_NV                    0x9284
#घोषणा GL_CONTRAST_NV                    0x92A1
#घोषणा GL_DARKEN_NV                      0x9297
#घोषणा GL_DIFFERENCE_NV                  0x929E
#घोषणा GL_DISJOINT_NV                    0x9283
#घोषणा GL_DST_ATOP_NV                    0x928F
#घोषणा GL_DST_IN_NV                      0x928B
#घोषणा GL_DST_NV                         0x9287
#घोषणा GL_DST_OUT_NV                     0x928D
#घोषणा GL_DST_OVER_NV                    0x9289
#घोषणा GL_EXCLUSION_NV                   0x92A0
#घोषणा GL_GREEN_NV                       0x1904
#घोषणा GL_HARDLIGHT_NV                   0x929B
#घोषणा GL_HARDMIX_NV                     0x92A9
#घोषणा GL_HSL_COLOR_NV                   0x92AF
#घोषणा GL_HSL_HUE_NV                     0x92AD
#घोषणा GL_HSL_LUMINOSITY_NV              0x92B0
#घोषणा GL_HSL_SATURATION_NV              0x92AE
#घोषणा GL_INVERT_OVG_NV                  0x92B4
#घोषणा GL_INVERT_RGB_NV                  0x92A3
#घोषणा GL_LIGHTEN_NV                     0x9298
#घोषणा GL_LINEARBURN_NV                  0x92A5
#घोषणा GL_LINEARDODGE_NV                 0x92A4
#घोषणा GL_LINEARLIGHT_NV                 0x92A7
#घोषणा GL_MINUS_CLAMPED_NV               0x92B3
#घोषणा GL_MINUS_NV                       0x929F
#घोषणा GL_MULTIPLY_NV                    0x9294
#घोषणा GL_OVERLAY_NV                     0x9296
#घोषणा GL_PINLIGHT_NV                    0x92A8
#घोषणा GL_PLUS_CLAMPED_ALPHA_NV          0x92B2
#घोषणा GL_PLUS_CLAMPED_NV                0x92B1
#घोषणा GL_PLUS_DARKER_NV                 0x9292
#घोषणा GL_PLUS_NV                        0x9291
#घोषणा GL_RED_NV                         0x1903
#घोषणा GL_SCREEN_NV                      0x9295
#घोषणा GL_SOFTLIGHT_NV                   0x929C
#घोषणा GL_SRC_ATOP_NV                    0x928E
#घोषणा GL_SRC_IN_NV                      0x928A
#घोषणा GL_SRC_NV                         0x9286
#घोषणा GL_SRC_OUT_NV                     0x928C
#घोषणा GL_SRC_OVER_NV                    0x9288
#घोषणा GL_UNCORRELATED_NV                0x9282
#घोषणा GL_VIVIDLIGHT_NV                  0x92A6
#घोषणा GL_XOR_NV                         0x1506
प्रकार व्योम (GL_APIENTRYP PFNGLBLENDPARAMETERINVPROC) (GLenum pname, GLint मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLBLENDBARRIERNVPROC) (व्योम);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glBlendParameteriNV (GLenum pname, GLint मूल्य);
GL_APICALL व्योम GL_APIENTRY glBlendBarrierNV (व्योम);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_NV_blend_equation_advanced */

#अगर_अघोषित GL_NV_blend_equation_advanced_coherent
#घोषणा GL_NV_blend_equation_advanced_coherent 1
#घोषणा GL_BLEND_ADVANCED_COHERENT_NV     0x9285
#पूर्ण_अगर /* GL_NV_blend_equation_advanced_coherent */

#अगर_अघोषित GL_NV_blend_minmax_factor
#घोषणा GL_NV_blend_minmax_factor 1
#घोषणा GL_FACTOR_MIN_AMD                 0x901C
#घोषणा GL_FACTOR_MAX_AMD                 0x901D
#पूर्ण_अगर /* GL_NV_blend_minmax_factor */

#अगर_अघोषित GL_NV_clip_space_w_scaling
#घोषणा GL_NV_clip_space_w_scaling 1
#घोषणा GL_VIEWPORT_POSITION_W_SCALE_NV   0x937C
#घोषणा GL_VIEWPORT_POSITION_W_SCALE_X_COEFF_NV 0x937D
#घोषणा GL_VIEWPORT_POSITION_W_SCALE_Y_COEFF_NV 0x937E
प्रकार व्योम (GL_APIENTRYP PFNGLVIEWPORTPOSITIONWSCALENVPROC) (GLuint सूचकांक, GLfloat xcoeff, GLfloat ycoeff);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glViewportPositionWScaleNV (GLuint सूचकांक, GLfloat xcoeff, GLfloat ycoeff);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_NV_clip_space_w_scaling */

#अगर_अघोषित GL_NV_compute_shader_derivatives
#घोषणा GL_NV_compute_shader_derivatives 1
#पूर्ण_अगर /* GL_NV_compute_shader_derivatives */

#अगर_अघोषित GL_NV_conditional_render
#घोषणा GL_NV_conditional_render 1
#घोषणा GL_QUERY_WAIT_NV                  0x8E13
#घोषणा GL_QUERY_NO_WAIT_NV               0x8E14
#घोषणा GL_QUERY_BY_REGION_WAIT_NV        0x8E15
#घोषणा GL_QUERY_BY_REGION_NO_WAIT_NV     0x8E16
प्रकार व्योम (GL_APIENTRYP PFNGLBEGINCONDITIONALRENDERNVPROC) (GLuint id, GLenum mode);
प्रकार व्योम (GL_APIENTRYP PFNGLENDCONDITIONALRENDERNVPROC) (व्योम);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glBeginConditionalRenderNV (GLuint id, GLenum mode);
GL_APICALL व्योम GL_APIENTRY glEndConditionalRenderNV (व्योम);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_NV_conditional_render */

#अगर_अघोषित GL_NV_conservative_raster
#घोषणा GL_NV_conservative_raster 1
#घोषणा GL_CONSERVATIVE_RASTERIZATION_NV  0x9346
#घोषणा GL_SUBPIXEL_PRECISION_BIAS_X_BITS_NV 0x9347
#घोषणा GL_SUBPIXEL_PRECISION_BIAS_Y_BITS_NV 0x9348
#घोषणा GL_MAX_SUBPIXEL_PRECISION_BIAS_BITS_NV 0x9349
प्रकार व्योम (GL_APIENTRYP PFNGLSUBPIXELPRECISIONBIASNVPROC) (GLuint xbits, GLuint ybits);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glSubpixelPrecisionBiasNV (GLuint xbits, GLuint ybits);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_NV_conservative_raster */

#अगर_अघोषित GL_NV_conservative_raster_pre_snap
#घोषणा GL_NV_conservative_raster_pre_snap 1
#घोषणा GL_CONSERVATIVE_RASTER_MODE_PRE_SNAP_NV 0x9550
#पूर्ण_अगर /* GL_NV_conservative_raster_pre_snap */

#अगर_अघोषित GL_NV_conservative_raster_pre_snap_triangles
#घोषणा GL_NV_conservative_raster_pre_snap_triangles 1
#घोषणा GL_CONSERVATIVE_RASTER_MODE_NV    0x954D
#घोषणा GL_CONSERVATIVE_RASTER_MODE_POST_SNAP_NV 0x954E
#घोषणा GL_CONSERVATIVE_RASTER_MODE_PRE_SNAP_TRIANGLES_NV 0x954F
प्रकार व्योम (GL_APIENTRYP PFNGLCONSERVATIVERASTERPARAMETERINVPROC) (GLenum pname, GLint param);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glConservativeRasterParameteriNV (GLenum pname, GLint param);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_NV_conservative_raster_pre_snap_triangles */

#अगर_अघोषित GL_NV_copy_बफर
#घोषणा GL_NV_copy_बफर 1
#घोषणा GL_COPY_READ_बफर_NV            0x8F36
#घोषणा GL_COPY_WRITE_बफर_NV           0x8F37
प्रकार व्योम (GL_APIENTRYP PFNGLCOPYBUFFERSUBDATANVPROC) (GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr आकार);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY gl_Copy_बफर_Sub_तथ्य_NV (GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr आकार);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_NV_copy_buffer */

#अगर_अघोषित GL_NV_coverage_sample
#घोषणा GL_NV_coverage_sample 1
#घोषणा GL_COVERAGE_COMPONENT_NV          0x8ED0
#घोषणा GL_COVERAGE_COMPONENT4_NV         0x8ED1
#घोषणा GL_COVERAGE_ATTACHMENT_NV         0x8ED2
#घोषणा GL_COVERAGE_BUFFERS_NV            0x8ED3
#घोषणा GL_COVERAGE_SAMPLES_NV            0x8ED4
#घोषणा GL_COVERAGE_ALL_FRAGMENTS_NV      0x8ED5
#घोषणा GL_COVERAGE_EDGE_FRAGMENTS_NV     0x8ED6
#घोषणा GL_COVERAGE_AUTOMATIC_NV          0x8ED7
#घोषणा GL_COVERAGE_बफर_BIT_NV         0x00008000
प्रकार व्योम (GL_APIENTRYP PFNGLCOVERAGEMASKNVPROC) (GLboolean mask);
प्रकार व्योम (GL_APIENTRYP PFNGLCOVERAGEOPERATIONNVPROC) (GLenum operation);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glCoverageMaskNV (GLboolean mask);
GL_APICALL व्योम GL_APIENTRY glCoverageOperationNV (GLenum operation);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_NV_coverage_sample */

#अगर_अघोषित GL_NV_depth_nonlinear
#घोषणा GL_NV_depth_nonlinear 1
#घोषणा GL_DEPTH_COMPONENT16_NONLINEAR_NV 0x8E2C
#पूर्ण_अगर /* GL_NV_depth_nonlinear */

#अगर_अघोषित GL_NV_draw_buffers
#घोषणा GL_NV_draw_buffers 1
#घोषणा GL_MAX_DRAW_BUFFERS_NV            0x8824
#घोषणा GL_DRAW_BUFFER0_NV                0x8825
#घोषणा GL_DRAW_BUFFER1_NV                0x8826
#घोषणा GL_DRAW_BUFFER2_NV                0x8827
#घोषणा GL_DRAW_BUFFER3_NV                0x8828
#घोषणा GL_DRAW_BUFFER4_NV                0x8829
#घोषणा GL_DRAW_BUFFER5_NV                0x882A
#घोषणा GL_DRAW_BUFFER6_NV                0x882B
#घोषणा GL_DRAW_BUFFER7_NV                0x882C
#घोषणा GL_DRAW_BUFFER8_NV                0x882D
#घोषणा GL_DRAW_BUFFER9_NV                0x882E
#घोषणा GL_DRAW_BUFFER10_NV               0x882F
#घोषणा GL_DRAW_BUFFER11_NV               0x8830
#घोषणा GL_DRAW_BUFFER12_NV               0x8831
#घोषणा GL_DRAW_BUFFER13_NV               0x8832
#घोषणा GL_DRAW_BUFFER14_NV               0x8833
#घोषणा GL_DRAW_BUFFER15_NV               0x8834
#घोषणा GL_COLOR_ATTACHMENT0_NV           0x8CE0
#घोषणा GL_COLOR_ATTACHMENT1_NV           0x8CE1
#घोषणा GL_COLOR_ATTACHMENT2_NV           0x8CE2
#घोषणा GL_COLOR_ATTACHMENT3_NV           0x8CE3
#घोषणा GL_COLOR_ATTACHMENT4_NV           0x8CE4
#घोषणा GL_COLOR_ATTACHMENT5_NV           0x8CE5
#घोषणा GL_COLOR_ATTACHMENT6_NV           0x8CE6
#घोषणा GL_COLOR_ATTACHMENT7_NV           0x8CE7
#घोषणा GL_COLOR_ATTACHMENT8_NV           0x8CE8
#घोषणा GL_COLOR_ATTACHMENT9_NV           0x8CE9
#घोषणा GL_COLOR_ATTACHMENT10_NV          0x8CEA
#घोषणा GL_COLOR_ATTACHMENT11_NV          0x8CEB
#घोषणा GL_COLOR_ATTACHMENT12_NV          0x8CEC
#घोषणा GL_COLOR_ATTACHMENT13_NV          0x8CED
#घोषणा GL_COLOR_ATTACHMENT14_NV          0x8CEE
#घोषणा GL_COLOR_ATTACHMENT15_NV          0x8CEF
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWBUFFERSNVPROC) (GLsizei n, स्थिर GLenum *bufs);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glDrawBuffersNV (GLsizei n, स्थिर GLenum *bufs);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_NV_draw_buffers */

#अगर_अघोषित GL_NV_draw_instanced
#घोषणा GL_NV_draw_instanced 1
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDNVPROC) (GLenum mode, GLint first, GLsizei गिनती, GLsizei primcount);
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDNVPROC) (GLenum mode, GLsizei गिनती, GLenum type, स्थिर व्योम *indices, GLsizei primcount);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glDrawArraysInstancedNV (GLenum mode, GLint first, GLsizei गिनती, GLsizei primcount);
GL_APICALL व्योम GL_APIENTRY glDrawElementsInstancedNV (GLenum mode, GLsizei गिनती, GLenum type, स्थिर व्योम *indices, GLsizei primcount);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_NV_draw_instanced */

#अगर_अघोषित GL_NV_draw_vulkan_image
#घोषणा GL_NV_draw_vulkan_image 1
प्रकार व्योम (GL_APIENTRY  *GLVULKANPROCNV)(व्योम);
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWVKIMAGENVPROC) (GLuint64 vkImage, GLuint sampler, GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat z, GLfloat s0, GLfloat t0, GLfloat s1, GLfloat t1);
प्रकार GLVULKANPROCNV (GL_APIENTRYP PFNGLGETVKPROCADDRNVPROC) (स्थिर GLchar *name);
प्रकार व्योम (GL_APIENTRYP PFNGLWAITVKSEMAPHORENVPROC) (GLuint64 vkSemaphore);
प्रकार व्योम (GL_APIENTRYP PFNGLSIGNALVKSEMAPHORENVPROC) (GLuint64 vkSemaphore);
प्रकार व्योम (GL_APIENTRYP PFNGLSIGNALVKFENCENVPROC) (GLuint64 vkFence);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glDrawVkImageNV (GLuint64 vkImage, GLuint sampler, GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat z, GLfloat s0, GLfloat t0, GLfloat s1, GLfloat t1);
GL_APICALL GLVULKANPROCNV GL_APIENTRY glGetVkProcAddrNV (स्थिर GLchar *name);
GL_APICALL व्योम GL_APIENTRY glWaitVkSemaphoreNV (GLuint64 vkSemaphore);
GL_APICALL व्योम GL_APIENTRY glSignalVkSemaphoreNV (GLuint64 vkSemaphore);
GL_APICALL व्योम GL_APIENTRY glSignalVkFenceNV (GLuint64 vkFence);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_NV_draw_vulkan_image */

#अगर_अघोषित GL_NV_explicit_attrib_location
#घोषणा GL_NV_explicit_attrib_location 1
#पूर्ण_अगर /* GL_NV_explicit_attrib_location */

#अगर_अघोषित GL_NV_fbo_color_attachments
#घोषणा GL_NV_fbo_color_attachments 1
#घोषणा GL_MAX_COLOR_ATTACHMENTS_NV       0x8CDF
#पूर्ण_अगर /* GL_NV_fbo_color_attachments */

#अगर_अघोषित GL_NV_fence
#घोषणा GL_NV_fence 1
#घोषणा GL_ALL_COMPLETED_NV               0x84F2
#घोषणा GL_FENCE_STATUS_NV                0x84F3
#घोषणा GL_FENCE_CONDITION_NV             0x84F4
प्रकार व्योम (GL_APIENTRYP PFNGLDELETEFENCESNVPROC) (GLsizei n, स्थिर GLuint *fences);
प्रकार व्योम (GL_APIENTRYP PFNGLGENFENCESNVPROC) (GLsizei n, GLuint *fences);
प्रकार GLboolean (GL_APIENTRYP PFNGLISFENCENVPROC) (GLuint fence);
प्रकार GLboolean (GL_APIENTRYP PFNGLTESTFENCENVPROC) (GLuint fence);
प्रकार व्योम (GL_APIENTRYP PFNGLGETFENCEIVNVPROC) (GLuint fence, GLenum pname, GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLFINISHFENCENVPROC) (GLuint fence);
प्रकार व्योम (GL_APIENTRYP PFNGLSETFENCENVPROC) (GLuint fence, GLenum condition);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glDeleteFencesNV (GLsizei n, स्थिर GLuint *fences);
GL_APICALL व्योम GL_APIENTRY glGenFencesNV (GLsizei n, GLuint *fences);
GL_APICALL GLboolean GL_APIENTRY glIsFenceNV (GLuint fence);
GL_APICALL GLboolean GL_APIENTRY glTestFenceNV (GLuint fence);
GL_APICALL व्योम GL_APIENTRY glGetFenceivNV (GLuint fence, GLenum pname, GLint *params);
GL_APICALL व्योम GL_APIENTRY glFinishFenceNV (GLuint fence);
GL_APICALL व्योम GL_APIENTRY glSetFenceNV (GLuint fence, GLenum condition);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_NV_fence */

#अगर_अघोषित GL_NV_fill_rectangle
#घोषणा GL_NV_fill_rectangle 1
#घोषणा GL_FILL_RECTANGLE_NV              0x933C
#पूर्ण_अगर /* GL_NV_fill_rectangle */

#अगर_अघोषित GL_NV_fragment_coverage_to_color
#घोषणा GL_NV_fragment_coverage_to_color 1
#घोषणा GL_FRAGMENT_COVERAGE_TO_COLOR_NV  0x92DD
#घोषणा GL_FRAGMENT_COVERAGE_COLOR_NV     0x92DE
प्रकार व्योम (GL_APIENTRYP PFNGLFRAGMENTCOVERAGECOLORNVPROC) (GLuint color);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glFragmentCoverageColorNV (GLuint color);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_NV_fragment_coverage_to_color */

#अगर_अघोषित GL_NV_fragment_shader_barycentric
#घोषणा GL_NV_fragment_shader_barycentric 1
#पूर्ण_अगर /* GL_NV_fragment_shader_barycentric */

#अगर_अघोषित GL_NV_fragment_shader_interlock
#घोषणा GL_NV_fragment_shader_interlock 1
#पूर्ण_अगर /* GL_NV_fragment_shader_interlock */

#अगर_अघोषित GL_NV_framebuffer_blit
#घोषणा GL_NV_framebuffer_blit 1
#घोषणा GL_READ_FRAMEBUFFER_NV            0x8CA8
#घोषणा GL_DRAW_FRAMEBUFFER_NV            0x8CA9
#घोषणा GL_DRAW_FRAMEBUFFER_BINDING_NV    0x8CA6
#घोषणा GL_READ_FRAMEBUFFER_BINDING_NV    0x8CAA
प्रकार व्योम (GL_APIENTRYP PFNGLBLITFRAMEBUFFERNVPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glBlitFramebufferNV (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_NV_framebuffer_blit */

#अगर_अघोषित GL_NV_framebuffer_mixed_samples
#घोषणा GL_NV_framebuffer_mixed_samples 1
#घोषणा GL_COVERAGE_MODULATION_TABLE_NV   0x9331
#घोषणा GL_COLOR_SAMPLES_NV               0x8E20
#घोषणा GL_DEPTH_SAMPLES_NV               0x932D
#घोषणा GL_STENCIL_SAMPLES_NV             0x932E
#घोषणा GL_MIXED_DEPTH_SAMPLES_SUPPORTED_NV 0x932F
#घोषणा GL_MIXED_STENCIL_SAMPLES_SUPPORTED_NV 0x9330
#घोषणा GL_COVERAGE_MODULATION_NV         0x9332
#घोषणा GL_COVERAGE_MODULATION_TABLE_आकार_NV 0x9333
प्रकार व्योम (GL_APIENTRYP PFNGLCOVERAGEMODULATIONTABLENVPROC) (GLsizei n, स्थिर GLfloat *v);
प्रकार व्योम (GL_APIENTRYP PFNGLGETCOVERAGEMODULATIONTABLENVPROC) (GLsizei buf_आकार, GLfloat *v);
प्रकार व्योम (GL_APIENTRYP PFNGLCOVERAGEMODULATIONNVPROC) (GLenum components);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glCoverageModulationTableNV (GLsizei n, स्थिर GLfloat *v);
GL_APICALL व्योम GL_APIENTRY glGetCoverageModulationTableNV (GLsizei buf_आकार, GLfloat *v);
GL_APICALL व्योम GL_APIENTRY glCoverageModulationNV (GLenum components);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_NV_framebuffer_mixed_samples */

#अगर_अघोषित GL_NV_framebuffer_multisample
#घोषणा GL_NV_framebuffer_multisample 1
#घोषणा GL_RENDERBUFFER_SAMPLES_NV        0x8CAB
#घोषणा GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_NV 0x8D56
#घोषणा GL_MAX_SAMPLES_NV                 0x8D57
प्रकार व्योम (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLENVPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glRenderbufferStorageMultisampleNV (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_NV_framebuffer_multisample */

#अगर_अघोषित GL_NV_generate_mipmap_sRGB
#घोषणा GL_NV_generate_mipmap_sRGB 1
#पूर्ण_अगर /* GL_NV_generate_mipmap_sRGB */

#अगर_अघोषित GL_NV_geometry_shader_passthrough
#घोषणा GL_NV_geometry_shader_passthrough 1
#पूर्ण_अगर /* GL_NV_geometry_shader_passthrough */

#अगर_अघोषित GL_NV_gpu_shader5
#घोषणा GL_NV_gpu_shader5 1
प्रकार khronos_int64_t GLint64EXT;
प्रकार khronos_uint64_t GLuint64EXT;
#घोषणा GL_INT64_NV                       0x140E
#घोषणा GL_UNSIGNED_INT64_NV              0x140F
#घोषणा GL_INT8_NV                        0x8FE0
#घोषणा GL_INT8_VEC2_NV                   0x8FE1
#घोषणा GL_INT8_VEC3_NV                   0x8FE2
#घोषणा GL_INT8_VEC4_NV                   0x8FE3
#घोषणा GL_INT16_NV                       0x8FE4
#घोषणा GL_INT16_VEC2_NV                  0x8FE5
#घोषणा GL_INT16_VEC3_NV                  0x8FE6
#घोषणा GL_INT16_VEC4_NV                  0x8FE7
#घोषणा GL_INT64_VEC2_NV                  0x8FE9
#घोषणा GL_INT64_VEC3_NV                  0x8FEA
#घोषणा GL_INT64_VEC4_NV                  0x8FEB
#घोषणा GL_UNSIGNED_INT8_NV               0x8FEC
#घोषणा GL_UNSIGNED_INT8_VEC2_NV          0x8FED
#घोषणा GL_UNSIGNED_INT8_VEC3_NV          0x8FEE
#घोषणा GL_UNSIGNED_INT8_VEC4_NV          0x8FEF
#घोषणा GL_UNSIGNED_INT16_NV              0x8FF0
#घोषणा GL_UNSIGNED_INT16_VEC2_NV         0x8FF1
#घोषणा GL_UNSIGNED_INT16_VEC3_NV         0x8FF2
#घोषणा GL_UNSIGNED_INT16_VEC4_NV         0x8FF3
#घोषणा GL_UNSIGNED_INT64_VEC2_NV         0x8FF5
#घोषणा GL_UNSIGNED_INT64_VEC3_NV         0x8FF6
#घोषणा GL_UNSIGNED_INT64_VEC4_NV         0x8FF7
#घोषणा GL_FLOAT16_NV                     0x8FF8
#घोषणा GL_FLOAT16_VEC2_NV                0x8FF9
#घोषणा GL_FLOAT16_VEC3_NV                0x8FFA
#घोषणा GL_FLOAT16_VEC4_NV                0x8FFB
#घोषणा GL_PATCHES                        0x000E
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM1I64NVPROC) (GLint location, GLint64EXT x);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM2I64NVPROC) (GLint location, GLint64EXT x, GLint64EXT y);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM3I64NVPROC) (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM4I64NVPROC) (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM1I64VNVPROC) (GLint location, GLsizei गिनती, स्थिर GLint64EXT *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM2I64VNVPROC) (GLint location, GLsizei गिनती, स्थिर GLint64EXT *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM3I64VNVPROC) (GLint location, GLsizei गिनती, स्थिर GLint64EXT *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM4I64VNVPROC) (GLint location, GLsizei गिनती, स्थिर GLint64EXT *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM1UI64NVPROC) (GLint location, GLuint64EXT x);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM2UI64NVPROC) (GLint location, GLuint64EXT x, GLuint64EXT y);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM3UI64NVPROC) (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM4UI64NVPROC) (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM1UI64VNVPROC) (GLint location, GLsizei गिनती, स्थिर GLuint64EXT *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM2UI64VNVPROC) (GLint location, GLsizei गिनती, स्थिर GLuint64EXT *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM3UI64VNVPROC) (GLint location, GLsizei गिनती, स्थिर GLuint64EXT *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM4UI64VNVPROC) (GLint location, GLsizei गिनती, स्थिर GLuint64EXT *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLGETUNIFORMI64VNVPROC) (GLuint program, GLint location, GLint64EXT *params);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM1I64NVPROC) (GLuint program, GLint location, GLint64EXT x);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM2I64NVPROC) (GLuint program, GLint location, GLint64EXT x, GLint64EXT y);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM3I64NVPROC) (GLuint program, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM4I64NVPROC) (GLuint program, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM1I64VNVPROC) (GLuint program, GLint location, GLsizei गिनती, स्थिर GLint64EXT *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM2I64VNVPROC) (GLuint program, GLint location, GLsizei गिनती, स्थिर GLint64EXT *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM3I64VNVPROC) (GLuint program, GLint location, GLsizei गिनती, स्थिर GLint64EXT *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM4I64VNVPROC) (GLuint program, GLint location, GLsizei गिनती, स्थिर GLint64EXT *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UI64NVPROC) (GLuint program, GLint location, GLuint64EXT x);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UI64NVPROC) (GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UI64NVPROC) (GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UI64NVPROC) (GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UI64VNVPROC) (GLuint program, GLint location, GLsizei गिनती, स्थिर GLuint64EXT *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UI64VNVPROC) (GLuint program, GLint location, GLsizei गिनती, स्थिर GLuint64EXT *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UI64VNVPROC) (GLuint program, GLint location, GLsizei गिनती, स्थिर GLuint64EXT *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UI64VNVPROC) (GLuint program, GLint location, GLsizei गिनती, स्थिर GLuint64EXT *मूल्य);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glUniform1i64NV (GLint location, GLint64EXT x);
GL_APICALL व्योम GL_APIENTRY glUniform2i64NV (GLint location, GLint64EXT x, GLint64EXT y);
GL_APICALL व्योम GL_APIENTRY glUniform3i64NV (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
GL_APICALL व्योम GL_APIENTRY glUniform4i64NV (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
GL_APICALL व्योम GL_APIENTRY glUniform1i64vNV (GLint location, GLsizei गिनती, स्थिर GLint64EXT *मूल्य);
GL_APICALL व्योम GL_APIENTRY glUniform2i64vNV (GLint location, GLsizei गिनती, स्थिर GLint64EXT *मूल्य);
GL_APICALL व्योम GL_APIENTRY glUniform3i64vNV (GLint location, GLsizei गिनती, स्थिर GLint64EXT *मूल्य);
GL_APICALL व्योम GL_APIENTRY glUniform4i64vNV (GLint location, GLsizei गिनती, स्थिर GLint64EXT *मूल्य);
GL_APICALL व्योम GL_APIENTRY glUniform1ui64NV (GLint location, GLuint64EXT x);
GL_APICALL व्योम GL_APIENTRY glUniform2ui64NV (GLint location, GLuint64EXT x, GLuint64EXT y);
GL_APICALL व्योम GL_APIENTRY glUniform3ui64NV (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
GL_APICALL व्योम GL_APIENTRY glUniform4ui64NV (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
GL_APICALL व्योम GL_APIENTRY glUniform1ui64vNV (GLint location, GLsizei गिनती, स्थिर GLuint64EXT *मूल्य);
GL_APICALL व्योम GL_APIENTRY glUniform2ui64vNV (GLint location, GLsizei गिनती, स्थिर GLuint64EXT *मूल्य);
GL_APICALL व्योम GL_APIENTRY glUniform3ui64vNV (GLint location, GLsizei गिनती, स्थिर GLuint64EXT *मूल्य);
GL_APICALL व्योम GL_APIENTRY glUniform4ui64vNV (GLint location, GLsizei गिनती, स्थिर GLuint64EXT *मूल्य);
GL_APICALL व्योम GL_APIENTRY glGetUniformi64vNV (GLuint program, GLint location, GLint64EXT *params);
GL_APICALL व्योम GL_APIENTRY glProgramUniform1i64NV (GLuint program, GLint location, GLint64EXT x);
GL_APICALL व्योम GL_APIENTRY glProgramUniform2i64NV (GLuint program, GLint location, GLint64EXT x, GLint64EXT y);
GL_APICALL व्योम GL_APIENTRY glProgramUniform3i64NV (GLuint program, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
GL_APICALL व्योम GL_APIENTRY glProgramUniform4i64NV (GLuint program, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
GL_APICALL व्योम GL_APIENTRY glProgramUniform1i64vNV (GLuint program, GLint location, GLsizei गिनती, स्थिर GLint64EXT *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniform2i64vNV (GLuint program, GLint location, GLsizei गिनती, स्थिर GLint64EXT *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniform3i64vNV (GLuint program, GLint location, GLsizei गिनती, स्थिर GLint64EXT *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniform4i64vNV (GLuint program, GLint location, GLsizei गिनती, स्थिर GLint64EXT *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniform1ui64NV (GLuint program, GLint location, GLuint64EXT x);
GL_APICALL व्योम GL_APIENTRY glProgramUniform2ui64NV (GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y);
GL_APICALL व्योम GL_APIENTRY glProgramUniform3ui64NV (GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
GL_APICALL व्योम GL_APIENTRY glProgramUniform4ui64NV (GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
GL_APICALL व्योम GL_APIENTRY glProgramUniform1ui64vNV (GLuint program, GLint location, GLsizei गिनती, स्थिर GLuint64EXT *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniform2ui64vNV (GLuint program, GLint location, GLsizei गिनती, स्थिर GLuint64EXT *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniform3ui64vNV (GLuint program, GLint location, GLsizei गिनती, स्थिर GLuint64EXT *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniform4ui64vNV (GLuint program, GLint location, GLsizei गिनती, स्थिर GLuint64EXT *मूल्य);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_NV_gpu_shader5 */

#अगर_अघोषित GL_NV_image_formats
#घोषणा GL_NV_image_formats 1
#पूर्ण_अगर /* GL_NV_image_formats */

#अगर_अघोषित GL_NV_instanced_arrays
#घोषणा GL_NV_instanced_arrays 1
#घोषणा GL_VERTEX_ATTRIB_ARRAY_भाजक_NV 0x88FE
प्रकार व्योम (GL_APIENTRYP PFNGLVERTEXATTRIBDIVISORNVPROC) (GLuint सूचकांक, GLuint भाजक);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY gl_Vertex_Attrib_भाजक_NV (GLuint सूचकांक, GLuint भाजक);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_NV_instanced_arrays */

#अगर_अघोषित GL_NV_internalformat_sample_query
#घोषणा GL_NV_internalformat_sample_query 1
#घोषणा GL_TEXTURE_2D_MULTISAMPLE         0x9100
#घोषणा GL_TEXTURE_2D_MULTISAMPLE_ARRAY   0x9102
#घोषणा GL_MULTISAMPLES_NV                0x9371
#घोषणा GL_SUPERSAMPLE_SCALE_X_NV         0x9372
#घोषणा GL_SUPERSAMPLE_SCALE_Y_NV         0x9373
#घोषणा GL_CONFORMANT_NV                  0x9374
प्रकार व्योम (GL_APIENTRYP PFNGLGETINTERNALFORMATSAMPLEIVNVPROC) (GLenum target, GLenum internalformat, GLsizei samples, GLenum pname, GLsizei गिनती, GLint *params);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glGetInternalformatSampleivNV (GLenum target, GLenum internalformat, GLsizei samples, GLenum pname, GLsizei गिनती, GLint *params);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_NV_internalformat_sample_query */

#अगर_अघोषित GL_NV_memory_attachment
#घोषणा GL_NV_memory_attachment 1
#घोषणा GL_ATTACHED_MEMORY_OBJECT_NV      0x95A4
#घोषणा GL_ATTACHED_MEMORY_OFFSET_NV      0x95A5
#घोषणा GL_MEMORY_ATTACHABLE_ALIGNMENT_NV 0x95A6
#घोषणा GL_MEMORY_ATTACHABLE_आकार_NV      0x95A7
#घोषणा GL_MEMORY_ATTACHABLE_NV           0x95A8
#घोषणा GL_DETACHED_MEMORY_INCARNATION_NV 0x95A9
#घोषणा GL_DETACHED_TEXTURES_NV           0x95AA
#घोषणा GL_DETACHED_BUFFERS_NV            0x95AB
#घोषणा GL_MAX_DETACHED_TEXTURES_NV       0x95AC
#घोषणा GL_MAX_DETACHED_BUFFERS_NV        0x95AD
प्रकार व्योम (GL_APIENTRYP PFNGLGETMEMORYOBJECTDETACHEDRESOURCESUIVNVPROC) (GLuint memory, GLenum pname, GLint first, GLsizei गिनती, GLuint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLRESETMEMORYOBJECTPARAMETERNVPROC) (GLuint memory, GLenum pname);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXATTACHMEMORYNVPROC) (GLenum target, GLuint memory, GLuint64 offset);
प्रकार व्योम (GL_APIENTRYP PFNGLBUFFERATTACHMEMORYNVPROC) (GLenum target, GLuint memory, GLuint64 offset);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXTUREATTACHMEMORYNVPROC) (GLuint texture, GLuint memory, GLuint64 offset);
प्रकार व्योम (GL_APIENTRYP PFNGLNAMEDBUFFERATTACHMEMORYNVPROC) (GLuint बफर_2, GLuint memory, GLuint64 offset);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glGetMemoryObjectDetachedResourcesuivNV (GLuint memory, GLenum pname, GLint first, GLsizei गिनती, GLuint *params);
GL_APICALL व्योम GL_APIENTRY glResetMemoryObjectParameterNV (GLuint memory, GLenum pname);
GL_APICALL व्योम GL_APIENTRY glTexAttachMemoryNV (GLenum target, GLuint memory, GLuint64 offset);
GL_APICALL व्योम GL_APIENTRY gl_बफर_Attach_Memory_NV (GLenum target, GLuint memory, GLuint64 offset);
GL_APICALL व्योम GL_APIENTRY glTextureAttachMemoryNV (GLuint texture, GLuint memory, GLuint64 offset);
GL_APICALL व्योम GL_APIENTRY gl_Named_बफर_Attach_Memory_NV (GLuint बफर_2, GLuint memory, GLuint64 offset);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_NV_memory_attachment */

#अगर_अघोषित GL_NV_memory_object_sparse
#घोषणा GL_NV_memory_object_sparse 1
प्रकार व्योम (GL_APIENTRYP PFNGLBUFFERPAGECOMMITMENTMEMNVPROC) (GLenum target, GLintptr offset, GLsizeiptr आकार, GLuint memory, GLuint64 memOffset, GLboolean commit);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXPAGECOMMITMENTMEMNVPROC) (GLenum target, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLuint memory, GLuint64 offset, GLboolean commit);
प्रकार व्योम (GL_APIENTRYP PFNGLNAMEDBUFFERPAGECOMMITMENTMEMNVPROC) (GLuint बफर_2, GLintptr offset, GLsizeiptr आकार, GLuint memory, GLuint64 memOffset, GLboolean commit);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXTUREPAGECOMMITMENTMEMNVPROC) (GLuint texture, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLuint memory, GLuint64 offset, GLboolean commit);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY gl_बफर_Page_Commitment_Mem_NV (GLenum target, GLintptr offset, GLsizeiptr आकार, GLuint memory, GLuint64 memOffset, GLboolean commit);
GL_APICALL व्योम GL_APIENTRY glTexPageCommitmentMemNV (GLenum target, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLuint memory, GLuint64 offset, GLboolean commit);
GL_APICALL व्योम GL_APIENTRY gl_Named_बफर_Page_Commitment_Mem_NV (GLuint बफर_2, GLintptr offset, GLsizeiptr आकार, GLuint memory, GLuint64 memOffset, GLboolean commit);
GL_APICALL व्योम GL_APIENTRY glTexturePageCommitmentMemNV (GLuint texture, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLuint memory, GLuint64 offset, GLboolean commit);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_NV_memory_object_sparse */

#अगर_अघोषित GL_NV_mesh_shader
#घोषणा GL_NV_mesh_shader 1
#घोषणा GL_MESH_SHADER_NV                 0x9559
#घोषणा GL_TASK_SHADER_NV                 0x955A
#घोषणा GL_MAX_MESH_UNIFORM_BLOCKS_NV     0x8E60
#घोषणा GL_MAX_MESH_TEXTURE_IMAGE_UNITS_NV 0x8E61
#घोषणा GL_MAX_MESH_IMAGE_UNIFORMS_NV     0x8E62
#घोषणा GL_MAX_MESH_UNIFORM_COMPONENTS_NV 0x8E63
#घोषणा GL_MAX_MESH_ATOMIC_गणक_BUFFERS_NV 0x8E64
#घोषणा GL_MAX_MESH_ATOMIC_COUNTERS_NV    0x8E65
#घोषणा GL_MAX_MESH_SHADER_STORAGE_BLOCKS_NV 0x8E66
#घोषणा GL_MAX_COMBINED_MESH_UNIFORM_COMPONENTS_NV 0x8E67
#घोषणा GL_MAX_TASK_UNIFORM_BLOCKS_NV     0x8E68
#घोषणा GL_MAX_TASK_TEXTURE_IMAGE_UNITS_NV 0x8E69
#घोषणा GL_MAX_TASK_IMAGE_UNIFORMS_NV     0x8E6A
#घोषणा GL_MAX_TASK_UNIFORM_COMPONENTS_NV 0x8E6B
#घोषणा GL_MAX_TASK_ATOMIC_गणक_BUFFERS_NV 0x8E6C
#घोषणा GL_MAX_TASK_ATOMIC_COUNTERS_NV    0x8E6D
#घोषणा GL_MAX_TASK_SHADER_STORAGE_BLOCKS_NV 0x8E6E
#घोषणा GL_MAX_COMBINED_TASK_UNIFORM_COMPONENTS_NV 0x8E6F
#घोषणा GL_MAX_MESH_WORK_GROUP_INVOCATIONS_NV 0x95A2
#घोषणा GL_MAX_TASK_WORK_GROUP_INVOCATIONS_NV 0x95A3
#घोषणा GL_MAX_MESH_योग_MEMORY_आकार_NV  0x9536
#घोषणा GL_MAX_TASK_योग_MEMORY_आकार_NV  0x9537
#घोषणा GL_MAX_MESH_OUTPUT_VERTICES_NV    0x9538
#घोषणा GL_MAX_MESH_OUTPUT_PRIMITIVES_NV  0x9539
#घोषणा GL_MAX_TASK_OUTPUT_गिनती_NV       0x953A
#घोषणा GL_MAX_DRAW_MESH_TASKS_गिनती_NV   0x953D
#घोषणा GL_MAX_MESH_VIEWS_NV              0x9557
#घोषणा GL_MESH_OUTPUT_PER_VERTEX_GRANULARITY_NV 0x92DF
#घोषणा GL_MESH_OUTPUT_PER_PRIMITIVE_GRANULARITY_NV 0x9543
#घोषणा GL_MAX_MESH_WORK_GROUP_आकार_NV    0x953B
#घोषणा GL_MAX_TASK_WORK_GROUP_आकार_NV    0x953C
#घोषणा GL_MESH_WORK_GROUP_आकार_NV        0x953E
#घोषणा GL_TASK_WORK_GROUP_आकार_NV        0x953F
#घोषणा GL_MESH_VERTICES_OUT_NV           0x9579
#घोषणा GL_MESH_PRIMITIVES_OUT_NV         0x957A
#घोषणा GL_MESH_OUTPUT_TYPE_NV            0x957B
#घोषणा GL_UNIFORM_BLOCK_REFERENCED_BY_MESH_SHADER_NV 0x959C
#घोषणा GL_UNIFORM_BLOCK_REFERENCED_BY_TASK_SHADER_NV 0x959D
#घोषणा GL_REFERENCED_BY_MESH_SHADER_NV   0x95A0
#घोषणा GL_REFERENCED_BY_TASK_SHADER_NV   0x95A1
#घोषणा GL_MESH_SHADER_BIT_NV             0x00000040
#घोषणा GL_TASK_SHADER_BIT_NV             0x00000080
#घोषणा GL_MESH_SUBROUTINE_NV             0x957C
#घोषणा GL_TASK_SUBROUTINE_NV             0x957D
#घोषणा GL_MESH_SUBROUTINE_UNIFORM_NV     0x957E
#घोषणा GL_TASK_SUBROUTINE_UNIFORM_NV     0x957F
#घोषणा GL_ATOMIC_गणक_बफर_REFERENCED_BY_MESH_SHADER_NV 0x959E
#घोषणा GL_ATOMIC_गणक_बफर_REFERENCED_BY_TASK_SHADER_NV 0x959F
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWMESHTASKSNVPROC) (GLuint first, GLuint गिनती);
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWMESHTASKSINDIRECTNVPROC) (GLintptr indirect);
प्रकार व्योम (GL_APIENTRYP PFNGLMULTIDRAWMESHTASKSINDIRECTNVPROC) (GLintptr indirect, GLsizei drawcount, GLsizei stride);
प्रकार व्योम (GL_APIENTRYP PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTNVPROC) (GLintptr indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glDrawMeshTasksNV (GLuint first, GLuint गिनती);
GL_APICALL व्योम GL_APIENTRY glDrawMeshTasksIndirectNV (GLintptr indirect);
GL_APICALL व्योम GL_APIENTRY glMultiDrawMeshTasksIndirectNV (GLintptr indirect, GLsizei drawcount, GLsizei stride);
GL_APICALL व्योम GL_APIENTRY gl_Multi_Draw_Mesh_Tasks_Indirect_गिनती_NV (GLintptr indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_NV_mesh_shader */

#अगर_अघोषित GL_NV_non_square_matrices
#घोषणा GL_NV_non_square_matrices 1
#घोषणा GL_FLOAT_MAT2x3_NV                0x8B65
#घोषणा GL_FLOAT_MAT2x4_NV                0x8B66
#घोषणा GL_FLOAT_MAT3x2_NV                0x8B67
#घोषणा GL_FLOAT_MAT3x4_NV                0x8B68
#घोषणा GL_FLOAT_MAT4x2_NV                0x8B69
#घोषणा GL_FLOAT_MAT4x3_NV                0x8B6A
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORMMATRIX2X3FVNVPROC) (GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORMMATRIX3X2FVNVPROC) (GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORMMATRIX2X4FVNVPROC) (GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORMMATRIX4X2FVNVPROC) (GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORMMATRIX3X4FVNVPROC) (GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORMMATRIX4X3FVNVPROC) (GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glUniformMatrix2x3fvNV (GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glUniformMatrix3x2fvNV (GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glUniformMatrix2x4fvNV (GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glUniformMatrix4x2fvNV (GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glUniformMatrix3x4fvNV (GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glUniformMatrix4x3fvNV (GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_NV_non_square_matrices */

#अगर_अघोषित GL_NV_pack_subimage
#घोषणा GL_NV_pack_subimage 1
#घोषणा GL_PACK_ROW_लंबाई_NV             0x0D02
#घोषणा GL_PACK_SKIP_ROWS_NV              0x0D03
#घोषणा GL_PACK_SKIP_PIXELS_NV            0x0D04
#पूर्ण_अगर /* GL_NV_pack_subimage */

#अगर_अघोषित GL_NV_path_rendering
#घोषणा GL_NV_path_rendering 1
प्रकार द्विगुन GLdouble;
#घोषणा GL_PATH_FORMAT_SVG_NV             0x9070
#घोषणा GL_PATH_FORMAT_PS_NV              0x9071
#घोषणा GL_STANDARD_FONT_NAME_NV          0x9072
#घोषणा GL_SYSTEM_FONT_NAME_NV            0x9073
#घोषणा GL_FILE_NAME_NV                   0x9074
#घोषणा GL_PATH_STROKE_WIDTH_NV           0x9075
#घोषणा GL_PATH_END_CAPS_NV               0x9076
#घोषणा GL_PATH_INITIAL_END_CAP_NV        0x9077
#घोषणा GL_PATH_TERMINAL_END_CAP_NV       0x9078
#घोषणा GL_PATH_JOIN_STYLE_NV             0x9079
#घोषणा GL_PATH_MITER_LIMIT_NV            0x907A
#घोषणा GL_PATH_DASH_CAPS_NV              0x907B
#घोषणा GL_PATH_INITIAL_DASH_CAP_NV       0x907C
#घोषणा GL_PATH_TERMINAL_DASH_CAP_NV      0x907D
#घोषणा GL_PATH_DASH_OFFSET_NV            0x907E
#घोषणा GL_PATH_CLIENT_लंबाई_NV          0x907F
#घोषणा GL_PATH_FILL_MODE_NV              0x9080
#घोषणा GL_PATH_FILL_MASK_NV              0x9081
#घोषणा GL_PATH_FILL_COVER_MODE_NV        0x9082
#घोषणा GL_PATH_STROKE_COVER_MODE_NV      0x9083
#घोषणा GL_PATH_STROKE_MASK_NV            0x9084
#घोषणा GL_गिनती_UP_NV                    0x9088
#घोषणा GL_गिनती_DOWN_NV                  0x9089
#घोषणा GL_PATH_OBJECT_BOUNDING_BOX_NV    0x908A
#घोषणा GL_CONVEX_HULL_NV                 0x908B
#घोषणा GL_BOUNDING_BOX_NV                0x908D
#घोषणा GL_TRANSLATE_X_NV                 0x908E
#घोषणा GL_TRANSLATE_Y_NV                 0x908F
#घोषणा GL_TRANSLATE_2D_NV                0x9090
#घोषणा GL_TRANSLATE_3D_NV                0x9091
#घोषणा GL_AFFINE_2D_NV                   0x9092
#घोषणा GL_AFFINE_3D_NV                   0x9094
#घोषणा GL_TRANSPOSE_AFFINE_2D_NV         0x9096
#घोषणा GL_TRANSPOSE_AFFINE_3D_NV         0x9098
#घोषणा GL_UTF8_NV                        0x909A
#घोषणा GL_UTF16_NV                       0x909B
#घोषणा GL_BOUNDING_BOX_OF_BOUNDING_BOXES_NV 0x909C
#घोषणा GL_PATH_COMMAND_गिनती_NV          0x909D
#घोषणा GL_PATH_COORD_गिनती_NV            0x909E
#घोषणा GL_PATH_DASH_ARRAY_गिनती_NV       0x909F
#घोषणा GL_PATH_COMPUTED_लंबाई_NV        0x90A0
#घोषणा GL_PATH_FILL_BOUNDING_BOX_NV      0x90A1
#घोषणा GL_PATH_STROKE_BOUNDING_BOX_NV    0x90A2
#घोषणा GL_SQUARE_NV                      0x90A3
#घोषणा GL_ROUND_NV                       0x90A4
#घोषणा GL_TRIANGULAR_NV                  0x90A5
#घोषणा GL_BEVEL_NV                       0x90A6
#घोषणा GL_MITER_REVERT_NV                0x90A7
#घोषणा GL_MITER_TRUNCATE_NV              0x90A8
#घोषणा GL_SKIP_MISSING_GLYPH_NV          0x90A9
#घोषणा GL_USE_MISSING_GLYPH_NV           0x90AA
#घोषणा GL_PATH_ERROR_POSITION_NV         0x90AB
#घोषणा GL_ACCUM_ADJACENT_PAIRS_NV        0x90AD
#घोषणा GL_ADJACENT_PAIRS_NV              0x90AE
#घोषणा GL_FIRST_TO_REST_NV               0x90AF
#घोषणा GL_PATH_GEN_MODE_NV               0x90B0
#घोषणा GL_PATH_GEN_COEFF_NV              0x90B1
#घोषणा GL_PATH_GEN_COMPONENTS_NV         0x90B3
#घोषणा GL_PATH_STENCIL_FUNC_NV           0x90B7
#घोषणा GL_PATH_STENCIL_REF_NV            0x90B8
#घोषणा GL_PATH_STENCIL_मूल्य_MASK_NV     0x90B9
#घोषणा GL_PATH_STENCIL_DEPTH_OFFSET_FACTOR_NV 0x90BD
#घोषणा GL_PATH_STENCIL_DEPTH_OFFSET_UNITS_NV 0x90BE
#घोषणा GL_PATH_COVER_DEPTH_FUNC_NV       0x90BF
#घोषणा GL_PATH_DASH_OFFSET_RESET_NV      0x90B4
#घोषणा GL_MOVE_TO_RESETS_NV              0x90B5
#घोषणा GL_MOVE_TO_CONTINUES_NV           0x90B6
#घोषणा GL_CLOSE_PATH_NV                  0x00
#घोषणा GL_MOVE_TO_NV                     0x02
#घोषणा GL_RELATIVE_MOVE_TO_NV            0x03
#घोषणा GL_पंक्ति_TO_NV                     0x04
#घोषणा GL_RELATIVE_पंक्ति_TO_NV            0x05
#घोषणा GL_HORIZONTAL_पंक्ति_TO_NV          0x06
#घोषणा GL_RELATIVE_HORIZONTAL_पंक्ति_TO_NV 0x07
#घोषणा GL_VERTICAL_पंक्ति_TO_NV            0x08
#घोषणा GL_RELATIVE_VERTICAL_पंक्ति_TO_NV   0x09
#घोषणा GL_QUADRATIC_CURVE_TO_NV          0x0A
#घोषणा GL_RELATIVE_QUADRATIC_CURVE_TO_NV 0x0B
#घोषणा GL_CUBIC_CURVE_TO_NV              0x0C
#घोषणा GL_RELATIVE_CUBIC_CURVE_TO_NV     0x0D
#घोषणा GL_SMOOTH_QUADRATIC_CURVE_TO_NV   0x0E
#घोषणा GL_RELATIVE_SMOOTH_QUADRATIC_CURVE_TO_NV 0x0F
#घोषणा GL_SMOOTH_CUBIC_CURVE_TO_NV       0x10
#घोषणा GL_RELATIVE_SMOOTH_CUBIC_CURVE_TO_NV 0x11
#घोषणा GL_SMALL_CCW_ARC_TO_NV            0x12
#घोषणा GL_RELATIVE_SMALL_CCW_ARC_TO_NV   0x13
#घोषणा GL_SMALL_CW_ARC_TO_NV             0x14
#घोषणा GL_RELATIVE_SMALL_CW_ARC_TO_NV    0x15
#घोषणा GL_LARGE_CCW_ARC_TO_NV            0x16
#घोषणा GL_RELATIVE_LARGE_CCW_ARC_TO_NV   0x17
#घोषणा GL_LARGE_CW_ARC_TO_NV             0x18
#घोषणा GL_RELATIVE_LARGE_CW_ARC_TO_NV    0x19
#घोषणा GL_RESTART_PATH_NV                0xF0
#घोषणा GL_DUP_FIRST_CUBIC_CURVE_TO_NV    0xF2
#घोषणा GL_DUP_LAST_CUBIC_CURVE_TO_NV     0xF4
#घोषणा GL_RECT_NV                        0xF6
#घोषणा GL_CIRCULAR_CCW_ARC_TO_NV         0xF8
#घोषणा GL_CIRCULAR_CW_ARC_TO_NV          0xFA
#घोषणा GL_CIRCULAR_TANGENT_ARC_TO_NV     0xFC
#घोषणा GL_ARC_TO_NV                      0xFE
#घोषणा GL_RELATIVE_ARC_TO_NV             0xFF
#घोषणा GL_BOLD_BIT_NV                    0x01
#घोषणा GL_ITALIC_BIT_NV                  0x02
#घोषणा GL_GLYPH_WIDTH_BIT_NV             0x01
#घोषणा GL_GLYPH_HEIGHT_BIT_NV            0x02
#घोषणा GL_GLYPH_HORIZONTAL_BEARING_X_BIT_NV 0x04
#घोषणा GL_GLYPH_HORIZONTAL_BEARING_Y_BIT_NV 0x08
#घोषणा GL_GLYPH_HORIZONTAL_BEARING_ADVANCE_BIT_NV 0x10
#घोषणा GL_GLYPH_VERTICAL_BEARING_X_BIT_NV 0x20
#घोषणा GL_GLYPH_VERTICAL_BEARING_Y_BIT_NV 0x40
#घोषणा GL_GLYPH_VERTICAL_BEARING_ADVANCE_BIT_NV 0x80
#घोषणा GL_GLYPH_HAS_KERNING_BIT_NV       0x100
#घोषणा GL_FONT_X_MIN_BOUNDS_BIT_NV       0x00010000
#घोषणा GL_FONT_Y_MIN_BOUNDS_BIT_NV       0x00020000
#घोषणा GL_FONT_X_MAX_BOUNDS_BIT_NV       0x00040000
#घोषणा GL_FONT_Y_MAX_BOUNDS_BIT_NV       0x00080000
#घोषणा GL_FONT_UNITS_PER_EM_BIT_NV       0x00100000
#घोषणा GL_FONT_ASCENDER_BIT_NV           0x00200000
#घोषणा GL_FONT_DESCENDER_BIT_NV          0x00400000
#घोषणा GL_FONT_HEIGHT_BIT_NV             0x00800000
#घोषणा GL_FONT_MAX_ADVANCE_WIDTH_BIT_NV  0x01000000
#घोषणा GL_FONT_MAX_ADVANCE_HEIGHT_BIT_NV 0x02000000
#घोषणा GL_FONT_UNDERLINE_POSITION_BIT_NV 0x04000000
#घोषणा GL_FONT_UNDERLINE_THICKNESS_BIT_NV 0x08000000
#घोषणा GL_FONT_HAS_KERNING_BIT_NV        0x10000000
#घोषणा GL_ROUNDED_RECT_NV                0xE8
#घोषणा GL_RELATIVE_ROUNDED_RECT_NV       0xE9
#घोषणा GL_ROUNDED_RECT2_NV               0xEA
#घोषणा GL_RELATIVE_ROUNDED_RECT2_NV      0xEB
#घोषणा GL_ROUNDED_RECT4_NV               0xEC
#घोषणा GL_RELATIVE_ROUNDED_RECT4_NV      0xED
#घोषणा GL_ROUNDED_RECT8_NV               0xEE
#घोषणा GL_RELATIVE_ROUNDED_RECT8_NV      0xEF
#घोषणा GL_RELATIVE_RECT_NV               0xF7
#घोषणा GL_FONT_GLYPHS_AVAILABLE_NV       0x9368
#घोषणा GL_FONT_TARGET_UNAVAILABLE_NV     0x9369
#घोषणा GL_FONT_UNAVAILABLE_NV            0x936A
#घोषणा GL_FONT_UNINTELLIGIBLE_NV         0x936B
#घोषणा GL_CONIC_CURVE_TO_NV              0x1A
#घोषणा GL_RELATIVE_CONIC_CURVE_TO_NV     0x1B
#घोषणा GL_FONT_अंक_GLYPH_INDICES_BIT_NV  0x20000000
#घोषणा GL_STANDARD_FONT_FORMAT_NV        0x936C
#घोषणा GL_PATH_PROJECTION_NV             0x1701
#घोषणा GL_PATH_MODELVIEW_NV              0x1700
#घोषणा GL_PATH_MODELVIEW_ढेर_DEPTH_NV  0x0BA3
#घोषणा GL_PATH_MODELVIEW_MATRIX_NV       0x0BA6
#घोषणा GL_PATH_MAX_MODELVIEW_ढेर_DEPTH_NV 0x0D36
#घोषणा GL_PATH_TRANSPOSE_MODELVIEW_MATRIX_NV 0x84E3
#घोषणा GL_PATH_PROJECTION_ढेर_DEPTH_NV 0x0BA4
#घोषणा GL_PATH_PROJECTION_MATRIX_NV      0x0BA7
#घोषणा GL_PATH_MAX_PROJECTION_ढेर_DEPTH_NV 0x0D38
#घोषणा GL_PATH_TRANSPOSE_PROJECTION_MATRIX_NV 0x84E4
#घोषणा GL_FRAGMENT_निवेश_NV              0x936D
प्रकार GLuint (GL_APIENTRYP PFNGLGENPATHSNVPROC) (GLsizei range);
प्रकार व्योम (GL_APIENTRYP PFNGLDELETEPATHSNVPROC) (GLuint path, GLsizei range);
प्रकार GLboolean (GL_APIENTRYP PFNGLISPATHNVPROC) (GLuint path);
प्रकार व्योम (GL_APIENTRYP PFNGLPATHCOMMANDSNVPROC) (GLuint path, GLsizei अंक_Commands, स्थिर GLubyte *commands, GLsizei अंक_Coords, GLenum coordType, स्थिर व्योम *coords);
प्रकार व्योम (GL_APIENTRYP PFNGLPATHCOORDSNVPROC) (GLuint path, GLsizei अंक_Coords, GLenum coordType, स्थिर व्योम *coords);
प्रकार व्योम (GL_APIENTRYP PFNGLPATHSUBCOMMANDSNVPROC) (GLuint path, GLsizei commandStart, GLsizei commandsToDelete, GLsizei अंक_Commands, स्थिर GLubyte *commands, GLsizei अंक_Coords, GLenum coordType, स्थिर व्योम *coords);
प्रकार व्योम (GL_APIENTRYP PFNGLPATHSUBCOORDSNVPROC) (GLuint path, GLsizei coordStart, GLsizei अंक_Coords, GLenum coordType, स्थिर व्योम *coords);
प्रकार व्योम (GL_APIENTRYP PFNGLPATHSTRINGNVPROC) (GLuint path, GLenum format, GLsizei लंबाई, स्थिर व्योम *pathString);
प्रकार व्योम (GL_APIENTRYP PFNGLPATHGLYPHSNVPROC) (GLuint firstPathName, GLenum fontTarget, स्थिर व्योम *fontName, GLbitfield fontStyle, GLsizei अंक_Glyphs, GLenum type, स्थिर व्योम *charcodes, GLenum handleMissingGlyphs, GLuint pathParameterTemplate, GLfloat emScale);
प्रकार व्योम (GL_APIENTRYP PFNGLPATHGLYPHRANGENVPROC) (GLuint firstPathName, GLenum fontTarget, स्थिर व्योम *fontName, GLbitfield fontStyle, GLuint firstGlyph, GLsizei अंक_Glyphs, GLenum handleMissingGlyphs, GLuint pathParameterTemplate, GLfloat emScale);
प्रकार व्योम (GL_APIENTRYP PFNGLWEIGHTPATHSNVPROC) (GLuint परिणाम_Path, GLsizei अंक_Paths, स्थिर GLuint *paths, स्थिर GLfloat *weights);
प्रकार व्योम (GL_APIENTRYP PFNGLCOPYPATHNVPROC) (GLuint परिणाम_Path, GLuint srcPath);
प्रकार व्योम (GL_APIENTRYP PFNGLINTERPOLATEPATHSNVPROC) (GLuint परिणाम_Path, GLuint pathA, GLuint pathB, GLfloat weight);
प्रकार व्योम (GL_APIENTRYP PFNGLTRANSFORMPATHNVPROC) (GLuint परिणाम_Path, GLuint srcPath, GLenum transformType, स्थिर GLfloat *transform_मूल्यावली);
प्रकार व्योम (GL_APIENTRYP PFNGLPATHPARAMETERIVNVPROC) (GLuint path, GLenum pname, स्थिर GLint *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPATHPARAMETERINVPROC) (GLuint path, GLenum pname, GLint मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPATHPARAMETERFVNVPROC) (GLuint path, GLenum pname, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPATHPARAMETERFNVPROC) (GLuint path, GLenum pname, GLfloat मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPATHDASHARRAYNVPROC) (GLuint path, GLsizei dash_गिनती, स्थिर GLfloat *dashArray);
प्रकार व्योम (GL_APIENTRYP PFNGLPATHSTENCILFUNCNVPROC) (GLenum func, GLint ref, GLuint mask);
प्रकार व्योम (GL_APIENTRYP PFNGLPATHSTENCILDEPTHOFFSETNVPROC) (GLfloat factor, GLfloat units);
प्रकार व्योम (GL_APIENTRYP PFNGLSTENCILFILLPATHNVPROC) (GLuint path, GLenum fillMode, GLuint mask);
प्रकार व्योम (GL_APIENTRYP PFNGLSTENCILSTROKEPATHNVPROC) (GLuint path, GLint reference, GLuint mask);
प्रकार व्योम (GL_APIENTRYP PFNGLSTENCILFILLPATHINSTANCEDNVPROC) (GLsizei अंक_Paths, GLenum pathNameType, स्थिर व्योम *paths, GLuint pathBase, GLenum fillMode, GLuint mask, GLenum transformType, स्थिर GLfloat *transform_मूल्यावली);
प्रकार व्योम (GL_APIENTRYP PFNGLSTENCILSTROKEPATHINSTANCEDNVPROC) (GLsizei अंक_Paths, GLenum pathNameType, स्थिर व्योम *paths, GLuint pathBase, GLint reference, GLuint mask, GLenum transformType, स्थिर GLfloat *transform_मूल्यावली);
प्रकार व्योम (GL_APIENTRYP PFNGLPATHCOVERDEPTHFUNCNVPROC) (GLenum func);
प्रकार व्योम (GL_APIENTRYP PFNGLCOVERFILLPATHNVPROC) (GLuint path, GLenum coverMode);
प्रकार व्योम (GL_APIENTRYP PFNGLCOVERSTROKEPATHNVPROC) (GLuint path, GLenum coverMode);
प्रकार व्योम (GL_APIENTRYP PFNGLCOVERFILLPATHINSTANCEDNVPROC) (GLsizei अंक_Paths, GLenum pathNameType, स्थिर व्योम *paths, GLuint pathBase, GLenum coverMode, GLenum transformType, स्थिर GLfloat *transform_मूल्यावली);
प्रकार व्योम (GL_APIENTRYP PFNGLCOVERSTROKEPATHINSTANCEDNVPROC) (GLsizei अंक_Paths, GLenum pathNameType, स्थिर व्योम *paths, GLuint pathBase, GLenum coverMode, GLenum transformType, स्थिर GLfloat *transform_मूल्यावली);
प्रकार व्योम (GL_APIENTRYP PFNGLGETPATHPARAMETERIVNVPROC) (GLuint path, GLenum pname, GLint *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLGETPATHPARAMETERFVNVPROC) (GLuint path, GLenum pname, GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLGETPATHCOMMANDSNVPROC) (GLuint path, GLubyte *commands);
प्रकार व्योम (GL_APIENTRYP PFNGLGETPATHCOORDSNVPROC) (GLuint path, GLfloat *coords);
प्रकार व्योम (GL_APIENTRYP PFNGLGETPATHDASHARRAYNVPROC) (GLuint path, GLfloat *dashArray);
प्रकार व्योम (GL_APIENTRYP PFNGLGETPATHMETRICSNVPROC) (GLbitfield metricQueryMask, GLsizei अंक_Paths, GLenum pathNameType, स्थिर व्योम *paths, GLuint pathBase, GLsizei stride, GLfloat *metrics);
प्रकार व्योम (GL_APIENTRYP PFNGLGETPATHMETRICRANGENVPROC) (GLbitfield metricQueryMask, GLuint firstPathName, GLsizei अंक_Paths, GLsizei stride, GLfloat *metrics);
प्रकार व्योम (GL_APIENTRYP PFNGLGETPATHSPACINGNVPROC) (GLenum pathListMode, GLsizei अंक_Paths, GLenum pathNameType, स्थिर व्योम *paths, GLuint pathBase, GLfloat advanceScale, GLfloat kerningScale, GLenum transformType, GLfloat *returnedSpacing);
प्रकार GLboolean (GL_APIENTRYP PFNGLISPOINTINFILLPATHNVPROC) (GLuint path, GLuint mask, GLfloat x, GLfloat y);
प्रकार GLboolean (GL_APIENTRYP PFNGLISPOINTINSTROKEPATHNVPROC) (GLuint path, GLfloat x, GLfloat y);
प्रकार GLfloat (GL_APIENTRYP PFNGLGETPATHLENGTHNVPROC) (GLuint path, GLsizei startSegment, GLsizei अंक_Segments);
प्रकार GLboolean (GL_APIENTRYP PFNGLPOINTALONGPATHNVPROC) (GLuint path, GLsizei startSegment, GLsizei अंक_Segments, GLfloat distance, GLfloat *x, GLfloat *y, GLfloat *tangentX, GLfloat *tangentY);
प्रकार व्योम (GL_APIENTRYP PFNGLMATRIXLOAD3X2FNVPROC) (GLenum matrixMode, स्थिर GLfloat *m);
प्रकार व्योम (GL_APIENTRYP PFNGLMATRIXLOAD3X3FNVPROC) (GLenum matrixMode, स्थिर GLfloat *m);
प्रकार व्योम (GL_APIENTRYP PFNGLMATRIXLOADTRANSPOSE3X3FNVPROC) (GLenum matrixMode, स्थिर GLfloat *m);
प्रकार व्योम (GL_APIENTRYP PFNGLMATRIXMULT3X2FNVPROC) (GLenum matrixMode, स्थिर GLfloat *m);
प्रकार व्योम (GL_APIENTRYP PFNGLMATRIXMULT3X3FNVPROC) (GLenum matrixMode, स्थिर GLfloat *m);
प्रकार व्योम (GL_APIENTRYP PFNGLMATRIXMULTTRANSPOSE3X3FNVPROC) (GLenum matrixMode, स्थिर GLfloat *m);
प्रकार व्योम (GL_APIENTRYP PFNGLSTENCILTHENCOVERFILLPATHNVPROC) (GLuint path, GLenum fillMode, GLuint mask, GLenum coverMode);
प्रकार व्योम (GL_APIENTRYP PFNGLSTENCILTHENCOVERSTROKEPATHNVPROC) (GLuint path, GLint reference, GLuint mask, GLenum coverMode);
प्रकार व्योम (GL_APIENTRYP PFNGLSTENCILTHENCOVERFILLPATHINSTANCEDNVPROC) (GLsizei अंक_Paths, GLenum pathNameType, स्थिर व्योम *paths, GLuint pathBase, GLenum fillMode, GLuint mask, GLenum coverMode, GLenum transformType, स्थिर GLfloat *transform_मूल्यावली);
प्रकार व्योम (GL_APIENTRYP PFNGLSTENCILTHENCOVERSTROKEPATHINSTANCEDNVPROC) (GLsizei अंक_Paths, GLenum pathNameType, स्थिर व्योम *paths, GLuint pathBase, GLint reference, GLuint mask, GLenum coverMode, GLenum transformType, स्थिर GLfloat *transform_मूल्यावली);
प्रकार GLenum (GL_APIENTRYP PFNGLPATHGLYPHINDEXRANGENVPROC) (GLenum fontTarget, स्थिर व्योम *fontName, GLbitfield fontStyle, GLuint pathParameterTemplate, GLfloat emScale, GLuint *base_And_गिनती);
प्रकार GLenum (GL_APIENTRYP PFNGLPATHGLYPHINDEXARRAYNVPROC) (GLuint firstPathName, GLenum fontTarget, स्थिर व्योम *fontName, GLbitfield fontStyle, GLuint first_Glyph_सूचकांक, GLsizei अंक_Glyphs, GLuint pathParameterTemplate, GLfloat emScale);
प्रकार GLenum (GL_APIENTRYP PFNGLPATHMEMORYGLYPHINDEXARRAYNVPROC) (GLuint firstPathName, GLenum fontTarget, GLsizeiptr font_आकार, स्थिर व्योम *font_तथ्य, GLsizei face_सूचकांक, GLuint first_Glyph_सूचकांक, GLsizei अंक_Glyphs, GLuint pathParameterTemplate, GLfloat emScale);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMPATHFRAGMENTINPUTGENNVPROC) (GLuint program, GLint location, GLenum genMode, GLint components, स्थिर GLfloat *coeffs);
प्रकार व्योम (GL_APIENTRYP PFNGLGETPROGRAMRESOURCEFVNVPROC) (GLuint program, GLenum programInterface, GLuint सूचकांक, GLsizei prop_गिनती, स्थिर GLenum *props, GLsizei गिनती, GLsizei *लंबाई, GLfloat *params);
प्रकार व्योम (GL_APIENTRYP PFNGLMATRIXFRUSTUMEXTPROC) (GLenum mode, GLdouble बायाँ, GLdouble दायाँ, GLdouble bottom, GLdouble शीर्ष, GLdouble zNear, GLdouble zFar);
प्रकार व्योम (GL_APIENTRYP PFNGLMATRIXLOADIDENTITYEXTPROC) (GLenum mode);
प्रकार व्योम (GL_APIENTRYP PFNGLMATRIXLOADTRANSPOSEFEXTPROC) (GLenum mode, स्थिर GLfloat *m);
प्रकार व्योम (GL_APIENTRYP PFNGLMATRIXLOADTRANSPOSEDEXTPROC) (GLenum mode, स्थिर GLdouble *m);
प्रकार व्योम (GL_APIENTRYP PFNGLMATRIXLOADFEXTPROC) (GLenum mode, स्थिर GLfloat *m);
प्रकार व्योम (GL_APIENTRYP PFNGLMATRIXLOADDEXTPROC) (GLenum mode, स्थिर GLdouble *m);
प्रकार व्योम (GL_APIENTRYP PFNGLMATRIXMULTTRANSPOSEFEXTPROC) (GLenum mode, स्थिर GLfloat *m);
प्रकार व्योम (GL_APIENTRYP PFNGLMATRIXMULTTRANSPOSEDEXTPROC) (GLenum mode, स्थिर GLdouble *m);
प्रकार व्योम (GL_APIENTRYP PFNGLMATRIXMULTFEXTPROC) (GLenum mode, स्थिर GLfloat *m);
प्रकार व्योम (GL_APIENTRYP PFNGLMATRIXMULTDEXTPROC) (GLenum mode, स्थिर GLdouble *m);
प्रकार व्योम (GL_APIENTRYP PFNGLMATRIXORTHOEXTPROC) (GLenum mode, GLdouble बायाँ, GLdouble दायाँ, GLdouble bottom, GLdouble शीर्ष, GLdouble zNear, GLdouble zFar);
प्रकार व्योम (GL_APIENTRYP PFNGLMATRIXPOPEXTPROC) (GLenum mode);
प्रकार व्योम (GL_APIENTRYP PFNGLMATRIXPUSHEXTPROC) (GLenum mode);
प्रकार व्योम (GL_APIENTRYP PFNGLMATRIXROTATEFEXTPROC) (GLenum mode, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
प्रकार व्योम (GL_APIENTRYP PFNGLMATRIXROTATEDEXTPROC) (GLenum mode, GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
प्रकार व्योम (GL_APIENTRYP PFNGLMATRIXSCALEFEXTPROC) (GLenum mode, GLfloat x, GLfloat y, GLfloat z);
प्रकार व्योम (GL_APIENTRYP PFNGLMATRIXSCALEDEXTPROC) (GLenum mode, GLdouble x, GLdouble y, GLdouble z);
प्रकार व्योम (GL_APIENTRYP PFNGLMATRIXTRANSLATEFEXTPROC) (GLenum mode, GLfloat x, GLfloat y, GLfloat z);
प्रकार व्योम (GL_APIENTRYP PFNGLMATRIXTRANSLATEDEXTPROC) (GLenum mode, GLdouble x, GLdouble y, GLdouble z);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL GLuint GL_APIENTRY glGenPathsNV (GLsizei range);
GL_APICALL व्योम GL_APIENTRY glDeletePathsNV (GLuint path, GLsizei range);
GL_APICALL GLboolean GL_APIENTRY glIsPathNV (GLuint path);
GL_APICALL व्योम GL_APIENTRY glPathCommandsNV (GLuint path, GLsizei अंक_Commands, स्थिर GLubyte *commands, GLsizei अंक_Coords, GLenum coordType, स्थिर व्योम *coords);
GL_APICALL व्योम GL_APIENTRY glPathCoordsNV (GLuint path, GLsizei अंक_Coords, GLenum coordType, स्थिर व्योम *coords);
GL_APICALL व्योम GL_APIENTRY glPathSubCommandsNV (GLuint path, GLsizei commandStart, GLsizei commandsToDelete, GLsizei अंक_Commands, स्थिर GLubyte *commands, GLsizei अंक_Coords, GLenum coordType, स्थिर व्योम *coords);
GL_APICALL व्योम GL_APIENTRY glPathSubCoordsNV (GLuint path, GLsizei coordStart, GLsizei अंक_Coords, GLenum coordType, स्थिर व्योम *coords);
GL_APICALL व्योम GL_APIENTRY glPathStringNV (GLuint path, GLenum format, GLsizei लंबाई, स्थिर व्योम *pathString);
GL_APICALL व्योम GL_APIENTRY glPathGlyphsNV (GLuint firstPathName, GLenum fontTarget, स्थिर व्योम *fontName, GLbitfield fontStyle, GLsizei अंक_Glyphs, GLenum type, स्थिर व्योम *charcodes, GLenum handleMissingGlyphs, GLuint pathParameterTemplate, GLfloat emScale);
GL_APICALL व्योम GL_APIENTRY glPathGlyphRangeNV (GLuint firstPathName, GLenum fontTarget, स्थिर व्योम *fontName, GLbitfield fontStyle, GLuint firstGlyph, GLsizei अंक_Glyphs, GLenum handleMissingGlyphs, GLuint pathParameterTemplate, GLfloat emScale);
GL_APICALL व्योम GL_APIENTRY glWeightPathsNV (GLuint परिणाम_Path, GLsizei अंक_Paths, स्थिर GLuint *paths, स्थिर GLfloat *weights);
GL_APICALL व्योम GL_APIENTRY glCopyPathNV (GLuint परिणाम_Path, GLuint srcPath);
GL_APICALL व्योम GL_APIENTRY glInterpolatePathsNV (GLuint परिणाम_Path, GLuint pathA, GLuint pathB, GLfloat weight);
GL_APICALL व्योम GL_APIENTRY glTransformPathNV (GLuint परिणाम_Path, GLuint srcPath, GLenum transformType, स्थिर GLfloat *transform_मूल्यावली);
GL_APICALL व्योम GL_APIENTRY glPathParameterivNV (GLuint path, GLenum pname, स्थिर GLint *मूल्य);
GL_APICALL व्योम GL_APIENTRY glPathParameteriNV (GLuint path, GLenum pname, GLint मूल्य);
GL_APICALL व्योम GL_APIENTRY glPathParameterfvNV (GLuint path, GLenum pname, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glPathParameterfNV (GLuint path, GLenum pname, GLfloat मूल्य);
GL_APICALL व्योम GL_APIENTRY glPathDashArrayNV (GLuint path, GLsizei dash_गिनती, स्थिर GLfloat *dashArray);
GL_APICALL व्योम GL_APIENTRY glPathStencilFuncNV (GLenum func, GLint ref, GLuint mask);
GL_APICALL व्योम GL_APIENTRY glPathStencilDepthOffsetNV (GLfloat factor, GLfloat units);
GL_APICALL व्योम GL_APIENTRY glStencilFillPathNV (GLuint path, GLenum fillMode, GLuint mask);
GL_APICALL व्योम GL_APIENTRY glStencilStrokePathNV (GLuint path, GLint reference, GLuint mask);
GL_APICALL व्योम GL_APIENTRY glStencilFillPathInstancedNV (GLsizei अंक_Paths, GLenum pathNameType, स्थिर व्योम *paths, GLuint pathBase, GLenum fillMode, GLuint mask, GLenum transformType, स्थिर GLfloat *transform_मूल्यावली);
GL_APICALL व्योम GL_APIENTRY glStencilStrokePathInstancedNV (GLsizei अंक_Paths, GLenum pathNameType, स्थिर व्योम *paths, GLuint pathBase, GLint reference, GLuint mask, GLenum transformType, स्थिर GLfloat *transform_मूल्यावली);
GL_APICALL व्योम GL_APIENTRY glPathCoverDepthFuncNV (GLenum func);
GL_APICALL व्योम GL_APIENTRY glCoverFillPathNV (GLuint path, GLenum coverMode);
GL_APICALL व्योम GL_APIENTRY glCoverStrokePathNV (GLuint path, GLenum coverMode);
GL_APICALL व्योम GL_APIENTRY glCoverFillPathInstancedNV (GLsizei अंक_Paths, GLenum pathNameType, स्थिर व्योम *paths, GLuint pathBase, GLenum coverMode, GLenum transformType, स्थिर GLfloat *transform_मूल्यावली);
GL_APICALL व्योम GL_APIENTRY glCoverStrokePathInstancedNV (GLsizei अंक_Paths, GLenum pathNameType, स्थिर व्योम *paths, GLuint pathBase, GLenum coverMode, GLenum transformType, स्थिर GLfloat *transform_मूल्यावली);
GL_APICALL व्योम GL_APIENTRY glGetPathParameterivNV (GLuint path, GLenum pname, GLint *मूल्य);
GL_APICALL व्योम GL_APIENTRY glGetPathParameterfvNV (GLuint path, GLenum pname, GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glGetPathCommandsNV (GLuint path, GLubyte *commands);
GL_APICALL व्योम GL_APIENTRY glGetPathCoordsNV (GLuint path, GLfloat *coords);
GL_APICALL व्योम GL_APIENTRY glGetPathDashArrayNV (GLuint path, GLfloat *dashArray);
GL_APICALL व्योम GL_APIENTRY glGetPathMetricsNV (GLbitfield metricQueryMask, GLsizei अंक_Paths, GLenum pathNameType, स्थिर व्योम *paths, GLuint pathBase, GLsizei stride, GLfloat *metrics);
GL_APICALL व्योम GL_APIENTRY glGetPathMetricRangeNV (GLbitfield metricQueryMask, GLuint firstPathName, GLsizei अंक_Paths, GLsizei stride, GLfloat *metrics);
GL_APICALL व्योम GL_APIENTRY glGetPathSpacingNV (GLenum pathListMode, GLsizei अंक_Paths, GLenum pathNameType, स्थिर व्योम *paths, GLuint pathBase, GLfloat advanceScale, GLfloat kerningScale, GLenum transformType, GLfloat *returnedSpacing);
GL_APICALL GLboolean GL_APIENTRY glIsPointInFillPathNV (GLuint path, GLuint mask, GLfloat x, GLfloat y);
GL_APICALL GLboolean GL_APIENTRY glIsPointInStrokePathNV (GLuint path, GLfloat x, GLfloat y);
GL_APICALL GLfloat GL_APIENTRY gl_Get_Path_लंबाई_NV (GLuint path, GLsizei startSegment, GLsizei अंक_Segments);
GL_APICALL GLboolean GL_APIENTRY glPointAlongPathNV (GLuint path, GLsizei startSegment, GLsizei अंक_Segments, GLfloat distance, GLfloat *x, GLfloat *y, GLfloat *tangentX, GLfloat *tangentY);
GL_APICALL व्योम GL_APIENTRY glMatrixLoad3x2fNV (GLenum matrixMode, स्थिर GLfloat *m);
GL_APICALL व्योम GL_APIENTRY glMatrixLoad3x3fNV (GLenum matrixMode, स्थिर GLfloat *m);
GL_APICALL व्योम GL_APIENTRY glMatrixLoadTranspose3x3fNV (GLenum matrixMode, स्थिर GLfloat *m);
GL_APICALL व्योम GL_APIENTRY glMatrixMult3x2fNV (GLenum matrixMode, स्थिर GLfloat *m);
GL_APICALL व्योम GL_APIENTRY glMatrixMult3x3fNV (GLenum matrixMode, स्थिर GLfloat *m);
GL_APICALL व्योम GL_APIENTRY glMatrixMultTranspose3x3fNV (GLenum matrixMode, स्थिर GLfloat *m);
GL_APICALL व्योम GL_APIENTRY glStencilThenCoverFillPathNV (GLuint path, GLenum fillMode, GLuint mask, GLenum coverMode);
GL_APICALL व्योम GL_APIENTRY glStencilThenCoverStrokePathNV (GLuint path, GLint reference, GLuint mask, GLenum coverMode);
GL_APICALL व्योम GL_APIENTRY glStencilThenCoverFillPathInstancedNV (GLsizei अंक_Paths, GLenum pathNameType, स्थिर व्योम *paths, GLuint pathBase, GLenum fillMode, GLuint mask, GLenum coverMode, GLenum transformType, स्थिर GLfloat *transform_मूल्यावली);
GL_APICALL व्योम GL_APIENTRY glStencilThenCoverStrokePathInstancedNV (GLsizei अंक_Paths, GLenum pathNameType, स्थिर व्योम *paths, GLuint pathBase, GLint reference, GLuint mask, GLenum coverMode, GLenum transformType, स्थिर GLfloat *transform_मूल्यावली);
GL_APICALL GLenum GL_APIENTRY gl_Path_Glyph_सूचकांक_Range_NV (GLenum fontTarget, स्थिर व्योम *fontName, GLbitfield fontStyle, GLuint pathParameterTemplate, GLfloat emScale, GLuint *base_And_गिनती);
GL_APICALL GLenum GL_APIENTRY gl_Path_Glyph_सूचकांक_Array_NV (GLuint firstPathName, GLenum fontTarget, स्थिर व्योम *fontName, GLbitfield fontStyle, GLuint first_Glyph_सूचकांक, GLsizei अंक_Glyphs, GLuint pathParameterTemplate, GLfloat emScale);
GL_APICALL GLenum GL_APIENTRY gl_Path_Memory_Glyph_सूचकांक_Array_NV (GLuint firstPathName, GLenum fontTarget, GLsizeiptr font_आकार, स्थिर व्योम *font_तथ्य, GLsizei face_सूचकांक, GLuint first_Glyph_सूचकांक, GLsizei अंक_Glyphs, GLuint pathParameterTemplate, GLfloat emScale);
GL_APICALL व्योम GL_APIENTRY gl_Program_Path_Fragment_निवेश_Gen_NV (GLuint program, GLint location, GLenum genMode, GLint components, स्थिर GLfloat *coeffs);
GL_APICALL व्योम GL_APIENTRY glGetProgramResourcefvNV (GLuint program, GLenum programInterface, GLuint सूचकांक, GLsizei prop_गिनती, स्थिर GLenum *props, GLsizei गिनती, GLsizei *लंबाई, GLfloat *params);
GL_APICALL व्योम GL_APIENTRY glMatrixFrustumEXT (GLenum mode, GLdouble बायाँ, GLdouble दायाँ, GLdouble bottom, GLdouble शीर्ष, GLdouble zNear, GLdouble zFar);
GL_APICALL व्योम GL_APIENTRY glMatrixLoadIdentityEXT (GLenum mode);
GL_APICALL व्योम GL_APIENTRY glMatrixLoadTransposefEXT (GLenum mode, स्थिर GLfloat *m);
GL_APICALL व्योम GL_APIENTRY glMatrixLoadTransposedEXT (GLenum mode, स्थिर GLdouble *m);
GL_APICALL व्योम GL_APIENTRY glMatrixLoadfEXT (GLenum mode, स्थिर GLfloat *m);
GL_APICALL व्योम GL_APIENTRY glMatrixLoaddEXT (GLenum mode, स्थिर GLdouble *m);
GL_APICALL व्योम GL_APIENTRY glMatrixMultTransposefEXT (GLenum mode, स्थिर GLfloat *m);
GL_APICALL व्योम GL_APIENTRY glMatrixMultTransposedEXT (GLenum mode, स्थिर GLdouble *m);
GL_APICALL व्योम GL_APIENTRY glMatrixMultfEXT (GLenum mode, स्थिर GLfloat *m);
GL_APICALL व्योम GL_APIENTRY glMatrixMultdEXT (GLenum mode, स्थिर GLdouble *m);
GL_APICALL व्योम GL_APIENTRY glMatrixOrthoEXT (GLenum mode, GLdouble बायाँ, GLdouble दायाँ, GLdouble bottom, GLdouble शीर्ष, GLdouble zNear, GLdouble zFar);
GL_APICALL व्योम GL_APIENTRY gl_Matrix_निकालो_EXT (GLenum mode);
GL_APICALL व्योम GL_APIENTRY gl_Matrix_धकेलो_EXT (GLenum mode);
GL_APICALL व्योम GL_APIENTRY glMatrixRotatefEXT (GLenum mode, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL व्योम GL_APIENTRY glMatrixRotatedEXT (GLenum mode, GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
GL_APICALL व्योम GL_APIENTRY glMatrixScalefEXT (GLenum mode, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL व्योम GL_APIENTRY glMatrixScaledEXT (GLenum mode, GLdouble x, GLdouble y, GLdouble z);
GL_APICALL व्योम GL_APIENTRY glMatrixTranslatefEXT (GLenum mode, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL व्योम GL_APIENTRY glMatrixTranslatedEXT (GLenum mode, GLdouble x, GLdouble y, GLdouble z);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_NV_path_rendering */

#अगर_अघोषित GL_NV_path_rendering_shared_edge
#घोषणा GL_NV_path_rendering_shared_edge 1
#घोषणा GL_SHARED_EDGE_NV                 0xC0
#पूर्ण_अगर /* GL_NV_path_rendering_shared_edge */

#अगर_अघोषित GL_NV_pixel_बफर_object
#घोषणा GL_NV_pixel_बफर_object 1
#घोषणा GL_PIXEL_PACK_बफर_NV           0x88EB
#घोषणा GL_PIXEL_UNPACK_बफर_NV         0x88EC
#घोषणा GL_PIXEL_PACK_बफर_BINDING_NV   0x88ED
#घोषणा GL_PIXEL_UNPACK_बफर_BINDING_NV 0x88EF
#पूर्ण_अगर /* GL_NV_pixel_buffer_object */

#अगर_अघोषित GL_NV_polygon_mode
#घोषणा GL_NV_polygon_mode 1
#घोषणा GL_POLYGON_MODE_NV                0x0B40
#घोषणा GL_POLYGON_OFFSET_POINT_NV        0x2A01
#घोषणा GL_POLYGON_OFFSET_पंक्ति_NV         0x2A02
#घोषणा GL_POINT_NV                       0x1B00
#घोषणा GL_पंक्ति_NV                        0x1B01
#घोषणा GL_FILL_NV                        0x1B02
प्रकार व्योम (GL_APIENTRYP PFNGLPOLYGONMODENVPROC) (GLenum face, GLenum mode);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glPolygonModeNV (GLenum face, GLenum mode);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_NV_polygon_mode */

#अगर_अघोषित GL_NV_primitive_shading_rate
#घोषणा GL_NV_primitive_shading_rate 1
#घोषणा GL_SHADING_RATE_IMAGE_PER_PRIMITIVE_NV 0x95B1
#घोषणा GL_SHADING_RATE_IMAGE_PALETTE_गिनती_NV 0x95B2
#पूर्ण_अगर /* GL_NV_primitive_shading_rate */

#अगर_अघोषित GL_NV_read_बफर
#घोषणा GL_NV_read_बफर 1
#घोषणा GL_READ_बफर_NV                 0x0C02
प्रकार व्योम (GL_APIENTRYP PFNGLREADBUFFERNVPROC) (GLenum mode);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY gl_Read_बफर_NV (GLenum mode);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_NV_read_buffer */

#अगर_अघोषित GL_NV_read_बफर_front
#घोषणा GL_NV_read_बफर_front 1
#पूर्ण_अगर /* GL_NV_read_buffer_front */

#अगर_अघोषित GL_NV_read_depth
#घोषणा GL_NV_read_depth 1
#पूर्ण_अगर /* GL_NV_read_depth */

#अगर_अघोषित GL_NV_read_depth_stencil
#घोषणा GL_NV_read_depth_stencil 1
#पूर्ण_अगर /* GL_NV_read_depth_stencil */

#अगर_अघोषित GL_NV_read_stencil
#घोषणा GL_NV_read_stencil 1
#पूर्ण_अगर /* GL_NV_read_stencil */

#अगर_अघोषित GL_NV_representative_fragment_test
#घोषणा GL_NV_representative_fragment_test 1
#घोषणा GL_REPRESENTATIVE_FRAGMENT_TEST_NV 0x937F
#पूर्ण_अगर /* GL_NV_representative_fragment_test */

#अगर_अघोषित GL_NV_sRGB_formats
#घोषणा GL_NV_sRGB_formats 1
#घोषणा GL_SLUMINANCE_NV                  0x8C46
#घोषणा GL_SLUMINANCE_ALPHA_NV            0x8C44
#घोषणा GL_SRGB8_NV                       0x8C41
#घोषणा GL_SLUMINANCE8_NV                 0x8C47
#घोषणा GL_SLUMINANCE8_ALPHA8_NV          0x8C45
#घोषणा GL_COMPRESSED_SRGB_S3TC_DXT1_NV   0x8C4C
#घोषणा GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_NV 0x8C4D
#घोषणा GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_NV 0x8C4E
#घोषणा GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_NV 0x8C4F
#घोषणा GL_ETC1_SRGB8_NV                  0x88EE
#पूर्ण_अगर /* GL_NV_sRGB_formats */

#अगर_अघोषित GL_NV_sample_locations
#घोषणा GL_NV_sample_locations 1
#घोषणा GL_SAMPLE_LOCATION_SUBPIXEL_BITS_NV 0x933D
#घोषणा GL_SAMPLE_LOCATION_PIXEL_GRID_WIDTH_NV 0x933E
#घोषणा GL_SAMPLE_LOCATION_PIXEL_GRID_HEIGHT_NV 0x933F
#घोषणा GL_PROGRAMMABLE_SAMPLE_LOCATION_TABLE_आकार_NV 0x9340
#घोषणा GL_SAMPLE_LOCATION_NV             0x8E50
#घोषणा GL_PROGRAMMABLE_SAMPLE_LOCATION_NV 0x9341
#घोषणा GL_FRAMEBUFFER_PROGRAMMABLE_SAMPLE_LOCATIONS_NV 0x9342
#घोषणा GL_FRAMEBUFFER_SAMPLE_LOCATION_PIXEL_GRID_NV 0x9343
प्रकार व्योम (GL_APIENTRYP PFNGLFRAMEBUFFERSAMPLELOCATIONSFVNVPROC) (GLenum target, GLuint start, GLsizei गिनती, स्थिर GLfloat *v);
प्रकार व्योम (GL_APIENTRYP PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVNVPROC) (GLuint framebuffer, GLuint start, GLsizei गिनती, स्थिर GLfloat *v);
प्रकार व्योम (GL_APIENTRYP PFNGLRESOLVEDEPTHVALUESNVPROC) (व्योम);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glFramebufferSampleLocationsfvNV (GLenum target, GLuint start, GLsizei गिनती, स्थिर GLfloat *v);
GL_APICALL व्योम GL_APIENTRY glNamedFramebufferSampleLocationsfvNV (GLuint framebuffer, GLuint start, GLsizei गिनती, स्थिर GLfloat *v);
GL_APICALL व्योम GL_APIENTRY gl_Resolve_Depth_मूल्यावली_NV (व्योम);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_NV_sample_locations */

#अगर_अघोषित GL_NV_sample_mask_override_coverage
#घोषणा GL_NV_sample_mask_override_coverage 1
#पूर्ण_अगर /* GL_NV_sample_mask_override_coverage */

#अगर_अघोषित GL_NV_scissor_exclusive
#घोषणा GL_NV_scissor_exclusive 1
#घोषणा GL_SCISSOR_TEST_EXCLUSIVE_NV      0x9555
#घोषणा GL_SCISSOR_BOX_EXCLUSIVE_NV       0x9556
प्रकार व्योम (GL_APIENTRYP PFNGLSCISSOREXCLUSIVENVPROC) (GLint x, GLint y, GLsizei width, GLsizei height);
प्रकार व्योम (GL_APIENTRYP PFNGLSCISSOREXCLUSIVEARRAYVNVPROC) (GLuint first, GLsizei गिनती, स्थिर GLint *v);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glScissorExclusiveNV (GLint x, GLint y, GLsizei width, GLsizei height);
GL_APICALL व्योम GL_APIENTRY glScissorExclusiveArrayvNV (GLuint first, GLsizei गिनती, स्थिर GLint *v);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_NV_scissor_exclusive */

#अगर_अघोषित GL_NV_shader_atomic_fp16_vector
#घोषणा GL_NV_shader_atomic_fp16_vector 1
#पूर्ण_अगर /* GL_NV_shader_atomic_fp16_vector */

#अगर_अघोषित GL_NV_shader_noperspective_interpolation
#घोषणा GL_NV_shader_noperspective_interpolation 1
#पूर्ण_अगर /* GL_NV_shader_noperspective_interpolation */

#अगर_अघोषित GL_NV_shader_subgroup_partitioned
#घोषणा GL_NV_shader_subgroup_partitioned 1
#घोषणा GL_SUBGROUP_FEATURE_PARTITIONED_BIT_NV 0x00000100
#पूर्ण_अगर /* GL_NV_shader_subgroup_partitioned */

#अगर_अघोषित GL_NV_shader_texture_footprint
#घोषणा GL_NV_shader_texture_footprint 1
#पूर्ण_अगर /* GL_NV_shader_texture_footprint */

#अगर_अघोषित GL_NV_shading_rate_image
#घोषणा GL_NV_shading_rate_image 1
#घोषणा GL_SHADING_RATE_IMAGE_NV          0x9563
#घोषणा GL_SHADING_RATE_NO_INVOCATIONS_NV 0x9564
#घोषणा GL_SHADING_RATE_1_INVOCATION_PER_PIXEL_NV 0x9565
#घोषणा GL_SHADING_RATE_1_INVOCATION_PER_1X2_PIXELS_NV 0x9566
#घोषणा GL_SHADING_RATE_1_INVOCATION_PER_2X1_PIXELS_NV 0x9567
#घोषणा GL_SHADING_RATE_1_INVOCATION_PER_2X2_PIXELS_NV 0x9568
#घोषणा GL_SHADING_RATE_1_INVOCATION_PER_2X4_PIXELS_NV 0x9569
#घोषणा GL_SHADING_RATE_1_INVOCATION_PER_4X2_PIXELS_NV 0x956A
#घोषणा GL_SHADING_RATE_1_INVOCATION_PER_4X4_PIXELS_NV 0x956B
#घोषणा GL_SHADING_RATE_2_INVOCATIONS_PER_PIXEL_NV 0x956C
#घोषणा GL_SHADING_RATE_4_INVOCATIONS_PER_PIXEL_NV 0x956D
#घोषणा GL_SHADING_RATE_8_INVOCATIONS_PER_PIXEL_NV 0x956E
#घोषणा GL_SHADING_RATE_16_INVOCATIONS_PER_PIXEL_NV 0x956F
#घोषणा GL_SHADING_RATE_IMAGE_BINDING_NV  0x955B
#घोषणा GL_SHADING_RATE_IMAGE_TEXEL_WIDTH_NV 0x955C
#घोषणा GL_SHADING_RATE_IMAGE_TEXEL_HEIGHT_NV 0x955D
#घोषणा GL_SHADING_RATE_IMAGE_PALETTE_आकार_NV 0x955E
#घोषणा GL_MAX_COARSE_FRAGMENT_SAMPLES_NV 0x955F
#घोषणा GL_SHADING_RATE_SAMPLE_ORDER_DEFAULT_NV 0x95AE
#घोषणा GL_SHADING_RATE_SAMPLE_ORDER_PIXEL_MAJOR_NV 0x95AF
#घोषणा GL_SHADING_RATE_SAMPLE_ORDER_SAMPLE_MAJOR_NV 0x95B0
प्रकार व्योम (GL_APIENTRYP PFNGLBINDSHADINGRATEIMAGENVPROC) (GLuint texture);
प्रकार व्योम (GL_APIENTRYP PFNGLGETSHADINGRATEIMAGEPALETTENVPROC) (GLuint viewport, GLuint entry, GLenum *rate);
प्रकार व्योम (GL_APIENTRYP PFNGLGETSHADINGRATESAMPLELOCATIONIVNVPROC) (GLenum rate, GLuint samples, GLuint सूचकांक, GLint *location);
प्रकार व्योम (GL_APIENTRYP PFNGLSHADINGRATEIMAGEBARRIERNVPROC) (GLboolean synchronize);
प्रकार व्योम (GL_APIENTRYP PFNGLSHADINGRATEIMAGEPALETTENVPROC) (GLuint viewport, GLuint first, GLsizei गिनती, स्थिर GLenum *rates);
प्रकार व्योम (GL_APIENTRYP PFNGLSHADINGRATESAMPLEORDERNVPROC) (GLenum order);
प्रकार व्योम (GL_APIENTRYP PFNGLSHADINGRATESAMPLEORDERCUSTOMNVPROC) (GLenum rate, GLuint samples, स्थिर GLint *locations);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glBindShadingRateImageNV (GLuint texture);
GL_APICALL व्योम GL_APIENTRY glGetShadingRateImagePaletteNV (GLuint viewport, GLuint entry, GLenum *rate);
GL_APICALL व्योम GL_APIENTRY glGetShadingRateSampleLocationivNV (GLenum rate, GLuint samples, GLuint सूचकांक, GLint *location);
GL_APICALL व्योम GL_APIENTRY glShadingRateImageBarrierNV (GLboolean synchronize);
GL_APICALL व्योम GL_APIENTRY glShadingRateImagePaletteNV (GLuint viewport, GLuint first, GLsizei गिनती, स्थिर GLenum *rates);
GL_APICALL व्योम GL_APIENTRY glShadingRateSampleOrderNV (GLenum order);
GL_APICALL व्योम GL_APIENTRY glShadingRateSampleOrderCustomNV (GLenum rate, GLuint samples, स्थिर GLint *locations);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_NV_shading_rate_image */

#अगर_अघोषित GL_NV_shadow_samplers_array
#घोषणा GL_NV_shadow_samplers_array 1
#घोषणा GL_SAMPLER_2D_ARRAY_SHADOW_NV     0x8DC4
#पूर्ण_अगर /* GL_NV_shadow_samplers_array */

#अगर_अघोषित GL_NV_shadow_samplers_cube
#घोषणा GL_NV_shadow_samplers_cube 1
#घोषणा GL_SAMPLER_CUBE_SHADOW_NV         0x8DC5
#पूर्ण_अगर /* GL_NV_shadow_samplers_cube */

#अगर_अघोषित GL_NV_stereo_view_rendering
#घोषणा GL_NV_stereo_view_rendering 1
#पूर्ण_अगर /* GL_NV_stereo_view_rendering */

#अगर_अघोषित GL_NV_texture_barrier
#घोषणा GL_NV_texture_barrier 1
प्रकार व्योम (GL_APIENTRYP PFNGLTEXTUREBARRIERNVPROC) (व्योम);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glTextureBarrierNV (व्योम);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_NV_texture_barrier */

#अगर_अघोषित GL_NV_texture_border_clamp
#घोषणा GL_NV_texture_border_clamp 1
#घोषणा GL_TEXTURE_BORDER_COLOR_NV        0x1004
#घोषणा GL_CLAMP_TO_BORDER_NV             0x812D
#पूर्ण_अगर /* GL_NV_texture_border_clamp */

#अगर_अघोषित GL_NV_texture_compression_s3tc_update
#घोषणा GL_NV_texture_compression_s3tc_update 1
#पूर्ण_अगर /* GL_NV_texture_compression_s3tc_update */

#अगर_अघोषित GL_NV_texture_npot_2D_mipmap
#घोषणा GL_NV_texture_npot_2D_mipmap 1
#पूर्ण_अगर /* GL_NV_texture_npot_2D_mipmap */

#अगर_अघोषित GL_NV_timeline_semaphore
#घोषणा GL_NV_timeline_semaphore 1
#घोषणा GL_TIMELINE_SEMAPHORE_मूल्य_NV    0x9595
#घोषणा GL_SEMAPHORE_TYPE_NV              0x95B3
#घोषणा GL_SEMAPHORE_TYPE_द्विआधारी_NV       0x95B4
#घोषणा GL_SEMAPHORE_TYPE_TIMELINE_NV     0x95B5
#घोषणा GL_MAX_TIMELINE_SEMAPHORE_मूल्य_DIFFERENCE_NV 0x95B6
प्रकार व्योम (GL_APIENTRYP PFNGLCREATESEMAPHORESNVPROC) (GLsizei n, GLuint *semaphores);
प्रकार व्योम (GL_APIENTRYP PFNGLSEMAPHOREPARAMETERIVNVPROC) (GLuint semaphore, GLenum pname, स्थिर GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETSEMAPHOREPARAMETERIVNVPROC) (GLuint semaphore, GLenum pname, GLint *params);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glCreateSemaphoresNV (GLsizei n, GLuint *semaphores);
GL_APICALL व्योम GL_APIENTRY glSemaphoreParameterivNV (GLuint semaphore, GLenum pname, स्थिर GLint *params);
GL_APICALL व्योम GL_APIENTRY glGetSemaphoreParameterivNV (GLuint semaphore, GLenum pname, GLint *params);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_NV_timeline_semaphore */

#अगर_अघोषित GL_NV_viewport_array
#घोषणा GL_NV_viewport_array 1
#घोषणा GL_MAX_VIEWPORTS_NV               0x825B
#घोषणा GL_VIEWPORT_SUBPIXEL_BITS_NV      0x825C
#घोषणा GL_VIEWPORT_BOUNDS_RANGE_NV       0x825D
#घोषणा GL_VIEWPORT_सूचकांक_PROVOKING_VERTEX_NV 0x825F
प्रकार व्योम (GL_APIENTRYP PFNGLVIEWPORTARRAYVNVPROC) (GLuint first, GLsizei गिनती, स्थिर GLfloat *v);
प्रकार व्योम (GL_APIENTRYP PFNGLVIEWPORTINDEXEDFNVPROC) (GLuint सूचकांक, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
प्रकार व्योम (GL_APIENTRYP PFNGLVIEWPORTINDEXEDFVNVPROC) (GLuint सूचकांक, स्थिर GLfloat *v);
प्रकार व्योम (GL_APIENTRYP PFNGLSCISSORARRAYVNVPROC) (GLuint first, GLsizei गिनती, स्थिर GLint *v);
प्रकार व्योम (GL_APIENTRYP PFNGLSCISSORINDEXEDNVPROC) (GLuint सूचकांक, GLint बायाँ, GLint bottom, GLsizei width, GLsizei height);
प्रकार व्योम (GL_APIENTRYP PFNGLSCISSORINDEXEDVNVPROC) (GLuint सूचकांक, स्थिर GLint *v);
प्रकार व्योम (GL_APIENTRYP PFNGLDEPTHRANGEARRAYFVNVPROC) (GLuint first, GLsizei गिनती, स्थिर GLfloat *v);
प्रकार व्योम (GL_APIENTRYP PFNGLDEPTHRANGEINDEXEDFNVPROC) (GLuint सूचकांक, GLfloat n, GLfloat f);
प्रकार व्योम (GL_APIENTRYP PFNGLGETFLOATI_VNVPROC) (GLenum target, GLuint सूचकांक, GLfloat *तथ्य);
प्रकार व्योम (GL_APIENTRYP PFNGLENABLEINVPROC) (GLenum target, GLuint सूचकांक);
प्रकार व्योम (GL_APIENTRYP PFNGLDISABLEINVPROC) (GLenum target, GLuint सूचकांक);
प्रकार GLboolean (GL_APIENTRYP PFNGLISENABLEDINVPROC) (GLenum target, GLuint सूचकांक);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glViewportArrayvNV (GLuint first, GLsizei गिनती, स्थिर GLfloat *v);
GL_APICALL व्योम GL_APIENTRY glViewportIndexedfNV (GLuint सूचकांक, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
GL_APICALL व्योम GL_APIENTRY glViewportIndexedfvNV (GLuint सूचकांक, स्थिर GLfloat *v);
GL_APICALL व्योम GL_APIENTRY glScissorArrayvNV (GLuint first, GLsizei गिनती, स्थिर GLint *v);
GL_APICALL व्योम GL_APIENTRY glScissorIndexedNV (GLuint सूचकांक, GLint बायाँ, GLint bottom, GLsizei width, GLsizei height);
GL_APICALL व्योम GL_APIENTRY glScissorIndexedvNV (GLuint सूचकांक, स्थिर GLint *v);
GL_APICALL व्योम GL_APIENTRY glDepthRangeArrayfvNV (GLuint first, GLsizei गिनती, स्थिर GLfloat *v);
GL_APICALL व्योम GL_APIENTRY glDepthRangeIndexedfNV (GLuint सूचकांक, GLfloat n, GLfloat f);
GL_APICALL व्योम GL_APIENTRY glGetFloati_vNV (GLenum target, GLuint सूचकांक, GLfloat *तथ्य);
GL_APICALL व्योम GL_APIENTRY glEnableiNV (GLenum target, GLuint सूचकांक);
GL_APICALL व्योम GL_APIENTRY glDisableiNV (GLenum target, GLuint सूचकांक);
GL_APICALL GLboolean GL_APIENTRY glIsEnablediNV (GLenum target, GLuint सूचकांक);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_NV_viewport_array */

#अगर_अघोषित GL_NV_viewport_array2
#घोषणा GL_NV_viewport_array2 1
#पूर्ण_अगर /* GL_NV_viewport_array2 */

#अगर_अघोषित GL_NV_viewport_swizzle
#घोषणा GL_NV_viewport_swizzle 1
#घोषणा GL_VIEWPORT_SWIZZLE_POSITIVE_X_NV 0x9350
#घोषणा GL_VIEWPORT_SWIZZLE_NEGATIVE_X_NV 0x9351
#घोषणा GL_VIEWPORT_SWIZZLE_POSITIVE_Y_NV 0x9352
#घोषणा GL_VIEWPORT_SWIZZLE_NEGATIVE_Y_NV 0x9353
#घोषणा GL_VIEWPORT_SWIZZLE_POSITIVE_Z_NV 0x9354
#घोषणा GL_VIEWPORT_SWIZZLE_NEGATIVE_Z_NV 0x9355
#घोषणा GL_VIEWPORT_SWIZZLE_POSITIVE_W_NV 0x9356
#घोषणा GL_VIEWPORT_SWIZZLE_NEGATIVE_W_NV 0x9357
#घोषणा GL_VIEWPORT_SWIZZLE_X_NV          0x9358
#घोषणा GL_VIEWPORT_SWIZZLE_Y_NV          0x9359
#घोषणा GL_VIEWPORT_SWIZZLE_Z_NV          0x935A
#घोषणा GL_VIEWPORT_SWIZZLE_W_NV          0x935B
प्रकार व्योम (GL_APIENTRYP PFNGLVIEWPORTSWIZZLENVPROC) (GLuint सूचकांक, GLenum swizzlex, GLenum swizzley, GLenum swizzlez, GLenum swizzlew);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glViewportSwizzleNV (GLuint सूचकांक, GLenum swizzlex, GLenum swizzley, GLenum swizzlez, GLenum swizzlew);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_NV_viewport_swizzle */

#अगर_अघोषित GL_OVR_multiview
#घोषणा GL_OVR_multiview 1
#घोषणा GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_अंक_VIEWS_OVR 0x9630
#घोषणा GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_BASE_VIEW_सूचकांक_OVR 0x9632
#घोषणा GL_MAX_VIEWS_OVR                  0x9631
#घोषणा GL_FRAMEBUFFER_INCOMPLETE_VIEW_TARGETS_OVR 0x9633
प्रकार व्योम (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREMULTIVIEWOVRPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint base_View_सूचकांक, GLsizei अंक_Views_2);
प्रकार व्योम (GL_APIENTRYP PFNGLNAMEDFRAMEBUFFERTEXTUREMULTIVIEWOVRPROC) (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint base_View_सूचकांक, GLsizei अंक_Views_2);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glFramebufferTextureMultiviewOVR (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint base_View_सूचकांक, GLsizei अंक_Views_2);
GL_APICALL व्योम GL_APIENTRY glNamedFramebufferTextureMultiviewOVR (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint base_View_सूचकांक, GLsizei अंक_Views_2);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_OVR_multiview */

#अगर_अघोषित GL_OVR_multiview2
#घोषणा GL_OVR_multiview2 1
#पूर्ण_अगर /* GL_OVR_multiview2 */

#अगर_अघोषित GL_OVR_multiview_multisampled_render_to_texture
#घोषणा GL_OVR_multiview_multisampled_render_to_texture 1
प्रकार व्योम (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREMULTISAMPLEMULTIVIEWOVRPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLsizei samples, GLint base_View_सूचकांक, GLsizei अंक_Views_2);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glFramebufferTextureMultisampleMultiviewOVR (GLenum target, GLenum attachment, GLuint texture, GLint level, GLsizei samples, GLint base_View_सूचकांक, GLsizei अंक_Views_2);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_OVR_multiview_multisampled_render_to_texture */

#अगर_अघोषित GL_QCOM_YUV_texture_gather
#घोषणा GL_QCOM_YUV_texture_gather 1
#पूर्ण_अगर /* GL_QCOM_YUV_texture_gather */

#अगर_अघोषित GL_QCOM_alpha_test
#घोषणा GL_QCOM_alpha_test 1
#घोषणा GL_ALPHA_TEST_QCOM                0x0BC0
#घोषणा GL_ALPHA_TEST_FUNC_QCOM           0x0BC1
#घोषणा GL_ALPHA_TEST_REF_QCOM            0x0BC2
प्रकार व्योम (GL_APIENTRYP PFNGLALPHAFUNCQCOMPROC) (GLenum func, GLclampf ref);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glAlphaFuncQCOM (GLenum func, GLclampf ref);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_QCOM_alpha_test */

#अगर_अघोषित GL_QCOM_binning_control
#घोषणा GL_QCOM_binning_control 1
#घोषणा GL_BINNING_CONTROL_HINT_QCOM      0x8FB0
#घोषणा GL_CPU_OPTIMIZED_QCOM             0x8FB1
#घोषणा GL_GPU_OPTIMIZED_QCOM             0x8FB2
#घोषणा GL_RENDER_DIRECT_TO_FRAMEBUFFER_QCOM 0x8FB3
#पूर्ण_अगर /* GL_QCOM_binning_control */

#अगर_अघोषित GL_QCOM_driver_control
#घोषणा GL_QCOM_driver_control 1
प्रकार व्योम (GL_APIENTRYP PFNGLGETDRIVERCONTROLSQCOMPROC) (GLint *अंक, GLsizei आकार, GLuint *driverControls);
प्रकार व्योम (GL_APIENTRYP PFNGLGETDRIVERCONTROLSTRINGQCOMPROC) (GLuint driverControl, GLsizei buf_आकार, GLsizei *लंबाई, GLchar *driverControlString);
प्रकार व्योम (GL_APIENTRYP PFNGLENABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
प्रकार व्योम (GL_APIENTRYP PFNGLDISABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glGetDriverControlsQCOM (GLint *अंक, GLsizei आकार, GLuint *driverControls);
GL_APICALL व्योम GL_APIENTRY glGetDriverControlStringQCOM (GLuint driverControl, GLsizei buf_आकार, GLsizei *लंबाई, GLchar *driverControlString);
GL_APICALL व्योम GL_APIENTRY glEnableDriverControlQCOM (GLuint driverControl);
GL_APICALL व्योम GL_APIENTRY glDisableDriverControlQCOM (GLuint driverControl);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_QCOM_driver_control */

#अगर_अघोषित GL_QCOM_extended_get
#घोषणा GL_QCOM_extended_get 1
#घोषणा GL_TEXTURE_WIDTH_QCOM             0x8BD2
#घोषणा GL_TEXTURE_HEIGHT_QCOM            0x8BD3
#घोषणा GL_TEXTURE_DEPTH_QCOM             0x8BD4
#घोषणा GL_TEXTURE_INTERNAL_FORMAT_QCOM   0x8BD5
#घोषणा GL_TEXTURE_FORMAT_QCOM            0x8BD6
#घोषणा GL_TEXTURE_TYPE_QCOM              0x8BD7
#घोषणा GL_TEXTURE_IMAGE_VALID_QCOM       0x8BD8
#घोषणा GL_TEXTURE_अंक_LEVELS_QCOM        0x8BD9
#घोषणा GL_TEXTURE_TARGET_QCOM            0x8BDA
#घोषणा GL_TEXTURE_OBJECT_VALID_QCOM      0x8BDB
#घोषणा GL_STATE_RESTORE                  0x8BDC
प्रकार व्योम (GL_APIENTRYP PFNGLEXTGETTEXTURESQCOMPROC) (GLuint *textures, GLint maxTextures, GLint *अंक_Textures);
प्रकार व्योम (GL_APIENTRYP PFNGLEXTGETBUFFERSQCOMPROC) (GLuint *buffers, GLint maxBuffers, GLint *अंक_Buffers);
प्रकार व्योम (GL_APIENTRYP PFNGLEXTGETRENDERBUFFERSQCOMPROC) (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *अंक_Renderbuffers);
प्रकार व्योम (GL_APIENTRYP PFNGLEXTGETFRAMEBUFFERSQCOMPROC) (GLuint *framebuffers, GLint maxFramebuffers, GLint *अंक_Framebuffers);
प्रकार व्योम (GL_APIENTRYP PFNGLEXTGETTEXLEVELPARAMETERIVQCOMPROC) (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLEXTTEXOBJECTSTATEOVERRIDEIQCOMPROC) (GLenum target, GLenum pname, GLint param);
प्रकार व्योम (GL_APIENTRYP PFNGLEXTGETTEXSUBIMAGEQCOMPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, व्योम *texels);
प्रकार व्योम (GL_APIENTRYP PFNGLEXTGETBUFFERPOINTERVQCOMPROC) (GLenum target, व्योम **params);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glExtGetTexturesQCOM (GLuint *textures, GLint maxTextures, GLint *अंक_Textures);
GL_APICALL व्योम GL_APIENTRY glExtGetBuffersQCOM (GLuint *buffers, GLint maxBuffers, GLint *अंक_Buffers);
GL_APICALL व्योम GL_APIENTRY glExtGetRenderbuffersQCOM (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *अंक_Renderbuffers);
GL_APICALL व्योम GL_APIENTRY glExtGetFramebuffersQCOM (GLuint *framebuffers, GLint maxFramebuffers, GLint *अंक_Framebuffers);
GL_APICALL व्योम GL_APIENTRY glExtGetTexLevelParameterivQCOM (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
GL_APICALL व्योम GL_APIENTRY glExtTexObjectStateOverrideiQCOM (GLenum target, GLenum pname, GLint param);
GL_APICALL व्योम GL_APIENTRY glExtGetTexSubImageQCOM (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, व्योम *texels);
GL_APICALL व्योम GL_APIENTRY gl_Ext_Get_बफर_Pointerv_QCOM (GLenum target, व्योम **params);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_QCOM_extended_get */

#अगर_अघोषित GL_QCOM_extended_get2
#घोषणा GL_QCOM_extended_get2 1
प्रकार व्योम (GL_APIENTRYP PFNGLEXTGETSHADERSQCOMPROC) (GLuint *shaders, GLint maxShaders, GLint *अंक_Shaders);
प्रकार व्योम (GL_APIENTRYP PFNGLEXTGETPROGRAMSQCOMPROC) (GLuint *programs, GLint maxPrograms, GLint *अंक_Programs);
प्रकार GLboolean (GL_APIENTRYP PFNGLEXTISPROGRAMBINARYQCOMPROC) (GLuint program);
प्रकार व्योम (GL_APIENTRYP PFNGLEXTGETPROGRAMBINARYSOURCEQCOMPROC) (GLuint program, GLenum shadertype, GLchar *source, GLint *लंबाई);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glExtGetShadersQCOM (GLuint *shaders, GLint maxShaders, GLint *अंक_Shaders);
GL_APICALL व्योम GL_APIENTRY glExtGetProgramsQCOM (GLuint *programs, GLint maxPrograms, GLint *अंक_Programs);
GL_APICALL GLboolean GL_APIENTRY gl_Ext_Is_Program_द्विआधारी_QCOM (GLuint program);
GL_APICALL व्योम GL_APIENTRY gl_Ext_Get_Program_द्विआधारी_Source_QCOM (GLuint program, GLenum shadertype, GLchar *source, GLint *लंबाई);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_QCOM_extended_get2 */

#अगर_अघोषित GL_QCOM_frame_extrapolation
#घोषणा GL_QCOM_frame_extrapolation 1
प्रकार व्योम (GL_APIENTRYP PFNGLEXTRAPOLATETEX2DQCOMPROC) (GLuint src1, GLuint src2, GLuint output, GLfloat scaleFactor);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glExtrapolateTex2DQCOM (GLuint src1, GLuint src2, GLuint output, GLfloat scaleFactor);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_QCOM_frame_extrapolation */

#अगर_अघोषित GL_QCOM_framebuffer_foveated
#घोषणा GL_QCOM_framebuffer_foveated 1
#घोषणा GL_FOVEATION_ENABLE_BIT_QCOM      0x00000001
#घोषणा GL_FOVEATION_SCALED_BIN_METHOD_BIT_QCOM 0x00000002
प्रकार व्योम (GL_APIENTRYP PFNGLFRAMEBUFFERFOVEATIONCONFIGQCOMPROC) (GLuint framebuffer, GLuint अंक_Layers, GLuint focalPointsPerLayer, GLuint requestedFeatures, GLuint *providedFeatures);
प्रकार व्योम (GL_APIENTRYP PFNGLFRAMEBUFFERFOVEATIONPARAMETERSQCOMPROC) (GLuint framebuffer, GLuint layer, GLuint focalPoint, GLfloat focalX, GLfloat focalY, GLfloat gainX, GLfloat gainY, GLfloat foveaArea);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glFramebufferFoveationConfigQCOM (GLuint framebuffer, GLuint अंक_Layers, GLuint focalPointsPerLayer, GLuint requestedFeatures, GLuint *providedFeatures);
GL_APICALL व्योम GL_APIENTRY glFramebufferFoveationParametersQCOM (GLuint framebuffer, GLuint layer, GLuint focalPoint, GLfloat focalX, GLfloat focalY, GLfloat gainX, GLfloat gainY, GLfloat foveaArea);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_QCOM_framebuffer_foveated */

#अगर_अघोषित GL_QCOM_motion_estimation
#घोषणा GL_QCOM_motion_estimation 1
#घोषणा GL_MOTION_ESTIMATION_खोज_BLOCK_X_QCOM 0x8C90
#घोषणा GL_MOTION_ESTIMATION_खोज_BLOCK_Y_QCOM 0x8C91
प्रकार व्योम (GL_APIENTRYP PFNGLTEXESTIMATEMOTIONQCOMPROC) (GLuint ref, GLuint target, GLuint output);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXESTIMATEMOTIONREGIONSQCOMPROC) (GLuint ref, GLuint target, GLuint output, GLuint mask);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glTexEstimateMotionQCOM (GLuint ref, GLuint target, GLuint output);
GL_APICALL व्योम GL_APIENTRY glTexEstimateMotionRegionsQCOM (GLuint ref, GLuint target, GLuint output, GLuint mask);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_QCOM_motion_estimation */

#अगर_अघोषित GL_QCOM_perfmon_global_mode
#घोषणा GL_QCOM_perfmon_global_mode 1
#घोषणा GL_PERFMON_GLOBAL_MODE_QCOM       0x8FA0
#पूर्ण_अगर /* GL_QCOM_perfmon_global_mode */

#अगर_अघोषित GL_QCOM_render_sRGB_R8_RG8
#घोषणा GL_QCOM_render_sRGB_R8_RG8 1
#पूर्ण_अगर /* GL_QCOM_render_sRGB_R8_RG8 */

#अगर_अघोषित GL_QCOM_render_shared_exponent
#घोषणा GL_QCOM_render_shared_exponent 1
#पूर्ण_अगर /* GL_QCOM_render_shared_exponent */

#अगर_अघोषित GL_QCOM_shader_framebuffer_fetch_noncoherent
#घोषणा GL_QCOM_shader_framebuffer_fetch_noncoherent 1
#घोषणा GL_FRAMEBUFFER_FETCH_NONCOHERENT_QCOM 0x96A2
प्रकार व्योम (GL_APIENTRYP PFNGLFRAMEBUFFERFETCHBARRIERQCOMPROC) (व्योम);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glFramebufferFetchBarrierQCOM (व्योम);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_QCOM_shader_framebuffer_fetch_noncoherent */

#अगर_अघोषित GL_QCOM_shader_framebuffer_fetch_rate
#घोषणा GL_QCOM_shader_framebuffer_fetch_rate 1
#पूर्ण_अगर /* GL_QCOM_shader_framebuffer_fetch_rate */

#अगर_अघोषित GL_QCOM_shading_rate
#घोषणा GL_QCOM_shading_rate 1
#घोषणा GL_SHADING_RATE_QCOM              0x96A4
#घोषणा GL_SHADING_RATE_PRESERVE_ASPECT_RATIO_QCOM 0x96A5
#घोषणा GL_SHADING_RATE_1X1_PIXELS_QCOM   0x96A6
#घोषणा GL_SHADING_RATE_1X2_PIXELS_QCOM   0x96A7
#घोषणा GL_SHADING_RATE_2X1_PIXELS_QCOM   0x96A8
#घोषणा GL_SHADING_RATE_2X2_PIXELS_QCOM   0x96A9
#घोषणा GL_SHADING_RATE_4X2_PIXELS_QCOM   0x96AC
#घोषणा GL_SHADING_RATE_4X4_PIXELS_QCOM   0x96AE
प्रकार व्योम (GL_APIENTRYP PFNGLSHADINGRATEQCOMPROC) (GLenum rate);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glShadingRateQCOM (GLenum rate);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_QCOM_shading_rate */

#अगर_अघोषित GL_QCOM_texture_foveated
#घोषणा GL_QCOM_texture_foveated 1
#घोषणा GL_TEXTURE_FOVEATED_FEATURE_BITS_QCOM 0x8BFB
#घोषणा GL_TEXTURE_FOVEATED_MIN_PIXEL_DENSITY_QCOM 0x8BFC
#घोषणा GL_TEXTURE_FOVEATED_FEATURE_QUERY_QCOM 0x8BFD
#घोषणा GL_TEXTURE_FOVEATED_अंक_FOCAL_POINTS_QUERY_QCOM 0x8BFE
#घोषणा GL_FRAMEBUFFER_INCOMPLETE_FOVEATION_QCOM 0x8BFF
प्रकार व्योम (GL_APIENTRYP PFNGLTEXTUREFOVEATIONPARAMETERSQCOMPROC) (GLuint texture, GLuint layer, GLuint focalPoint, GLfloat focalX, GLfloat focalY, GLfloat gainX, GLfloat gainY, GLfloat foveaArea);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glTextureFoveationParametersQCOM (GLuint texture, GLuint layer, GLuint focalPoint, GLfloat focalX, GLfloat focalY, GLfloat gainX, GLfloat gainY, GLfloat foveaArea);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_QCOM_texture_foveated */

#अगर_अघोषित GL_QCOM_texture_foveated2
#घोषणा GL_QCOM_texture_foveated2 1
#घोषणा GL_TEXTURE_FOVEATED_CUTOFF_DENSITY_QCOM 0x96A0
#पूर्ण_अगर /* GL_QCOM_texture_foveated2 */

#अगर_अघोषित GL_QCOM_texture_foveated_subsampled_layout
#घोषणा GL_QCOM_texture_foveated_subsampled_layout 1
#घोषणा GL_FOVEATION_SUBSAMPLED_LAYOUT_METHOD_BIT_QCOM 0x00000004
#घोषणा GL_MAX_SHADER_SUBSAMPLED_IMAGE_UNITS_QCOM 0x8FA1
#पूर्ण_अगर /* GL_QCOM_texture_foveated_subsampled_layout */

#अगर_अघोषित GL_QCOM_texture_lod_bias
#घोषणा GL_QCOM_texture_lod_bias 1
#घोषणा GL_TEXTURE_LOD_BIAS_QCOM          0x8C96
#पूर्ण_अगर /* GL_QCOM_texture_lod_bias */

#अगर_अघोषित GL_QCOM_tiled_rendering
#घोषणा GL_QCOM_tiled_rendering 1
#घोषणा GL_COLOR_बफर_BIT0_QCOM         0x00000001
#घोषणा GL_COLOR_बफर_BIT1_QCOM         0x00000002
#घोषणा GL_COLOR_बफर_BIT2_QCOM         0x00000004
#घोषणा GL_COLOR_बफर_BIT3_QCOM         0x00000008
#घोषणा GL_COLOR_बफर_BIT4_QCOM         0x00000010
#घोषणा GL_COLOR_बफर_BIT5_QCOM         0x00000020
#घोषणा GL_COLOR_बफर_BIT6_QCOM         0x00000040
#घोषणा GL_COLOR_बफर_BIT7_QCOM         0x00000080
#घोषणा GL_DEPTH_बफर_BIT0_QCOM         0x00000100
#घोषणा GL_DEPTH_बफर_BIT1_QCOM         0x00000200
#घोषणा GL_DEPTH_बफर_BIT2_QCOM         0x00000400
#घोषणा GL_DEPTH_बफर_BIT3_QCOM         0x00000800
#घोषणा GL_DEPTH_बफर_BIT4_QCOM         0x00001000
#घोषणा GL_DEPTH_बफर_BIT5_QCOM         0x00002000
#घोषणा GL_DEPTH_बफर_BIT6_QCOM         0x00004000
#घोषणा GL_DEPTH_बफर_BIT7_QCOM         0x00008000
#घोषणा GL_STENCIL_बफर_BIT0_QCOM       0x00010000
#घोषणा GL_STENCIL_बफर_BIT1_QCOM       0x00020000
#घोषणा GL_STENCIL_बफर_BIT2_QCOM       0x00040000
#घोषणा GL_STENCIL_बफर_BIT3_QCOM       0x00080000
#घोषणा GL_STENCIL_बफर_BIT4_QCOM       0x00100000
#घोषणा GL_STENCIL_बफर_BIT5_QCOM       0x00200000
#घोषणा GL_STENCIL_बफर_BIT6_QCOM       0x00400000
#घोषणा GL_STENCIL_बफर_BIT7_QCOM       0x00800000
#घोषणा GL_MULTISAMPLE_बफर_BIT0_QCOM   0x01000000
#घोषणा GL_MULTISAMPLE_बफर_BIT1_QCOM   0x02000000
#घोषणा GL_MULTISAMPLE_बफर_BIT2_QCOM   0x04000000
#घोषणा GL_MULTISAMPLE_बफर_BIT3_QCOM   0x08000000
#घोषणा GL_MULTISAMPLE_बफर_BIT4_QCOM   0x10000000
#घोषणा GL_MULTISAMPLE_बफर_BIT5_QCOM   0x20000000
#घोषणा GL_MULTISAMPLE_बफर_BIT6_QCOM   0x40000000
#घोषणा GL_MULTISAMPLE_बफर_BIT7_QCOM   0x80000000
प्रकार व्योम (GL_APIENTRYP PFNGLSTARTTILINGQCOMPROC) (GLuint x, GLuint y, GLuint width, GLuint height, GLbitfield preserveMask);
प्रकार व्योम (GL_APIENTRYP PFNGLENDTILINGQCOMPROC) (GLbitfield preserveMask);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glStartTilingQCOM (GLuint x, GLuint y, GLuint width, GLuint height, GLbitfield preserveMask);
GL_APICALL व्योम GL_APIENTRY glEndTilingQCOM (GLbitfield preserveMask);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_QCOM_tiled_rendering */

#अगर_अघोषित GL_QCOM_writeonly_rendering
#घोषणा GL_QCOM_writeonly_rendering 1
#घोषणा GL_WRITEONLY_RENDERING_QCOM       0x8823
#पूर्ण_अगर /* GL_QCOM_writeonly_rendering */

#अगर_अघोषित GL_QCOM_ycbcr_degamma
#घोषणा GL_QCOM_ycbcr_degamma 1
#घोषणा GL_TEXTURE_Y_DEGAMMA_QCOM         0x9710
#घोषणा GL_TEXTURE_CBCR_DEGAMMA_QCOM      0x9711
#पूर्ण_अगर /* GL_QCOM_ycbcr_degamma */

#अगर_अघोषित GL_VIV_shader_द्विआधारी
#घोषणा GL_VIV_shader_द्विआधारी 1
#घोषणा GL_SHADER_द्विआधारी_VIV              0x8FC4
#पूर्ण_अगर /* GL_VIV_shader_binary */

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर
