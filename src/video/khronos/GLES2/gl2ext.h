#నిర్వచితం_కాకపోతే __gles2_gl2ext_h_
#నిర్వచించు __gles2_gl2ext_h_ 1

#నిర్వచితమైతే __cplusplus
బాహ్య "C" {
#అయితే_ముగింపు

/*
** Copyright 2013-2026 The Khronos Group Inc.
** SPDX-License-Identifier: MIT
**
** This header is generated from the Khronos OpenGL / OpenGL ES XML
** API Registry. The current version of the Registry, generator scripts
** used to make the header, and the header can be found at
**   https://github.com/KhronosGroup/OpenGL-Registry
*/

#నిర్వచితం_కాకపోతే GL_APIENTRYP
#నిర్వచించు GL_APIENTRYP GL_APIENTRY*
#అయితే_ముగింపు

#నిర్వచించు GL_GLEXT_సంస్కరణ 20260803

/* Generated C header for:
 * API: gles2
 * Profile: common
 * Versions considered: 2\.[0-9]
 * Versions emitted: _nomatch_^
 * Default extensions included: gles2
 * Additional extensions included: _nomatch_^
 * Extensions removed: _nomatch_^
 */

#నిర్వచితం_కాకపోతే GL_KHR_blend_equation_advanced
#నిర్వచించు GL_KHR_blend_equation_advanced 1
#నిర్వచించు GL_MULTIPLY_KHR                   0x9294
#నిర్వచించు GL_SCREEN_KHR                     0x9295
#నిర్వచించు GL_OVERLAY_KHR                    0x9296
#నిర్వచించు GL_DARKEN_KHR                     0x9297
#నిర్వచించు GL_LIGHTEN_KHR                    0x9298
#నిర్వచించు GL_COLORDODGE_KHR                 0x9299
#నిర్వచించు GL_COLORBURN_KHR                  0x929A
#నిర్వచించు GL_HARDLIGHT_KHR                  0x929B
#నిర్వచించు GL_SOFTLIGHT_KHR                  0x929C
#నిర్వచించు GL_DIFFERENCE_KHR                 0x929E
#నిర్వచించు GL_EXCLUSION_KHR                  0x92A0
#నిర్వచించు GL_HSL_HUE_KHR                    0x92AD
#నిర్వచించు GL_HSL_SATURATION_KHR             0x92AE
#నిర్వచించు GL_HSL_COLOR_KHR                  0x92AF
#నిర్వచించు GL_HSL_LUMINOSITY_KHR             0x92B0
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBLENDBARRIERKHRPROC) (శూన్య);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glBlendBarrierKHR (శూన్య);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_KHR_blend_equation_advanced */

#నిర్వచితం_కాకపోతే GL_KHR_blend_equation_advanced_coherent
#నిర్వచించు GL_KHR_blend_equation_advanced_coherent 1
#నిర్వచించు GL_BLEND_ADVANCED_COHERENT_KHR    0x9285
#అయితే_ముగింపు /* GL_KHR_blend_equation_advanced_coherent */

#నిర్వచితం_కాకపోతే GL_KHR_context_flush_control
#నిర్వచించు GL_KHR_context_flush_control 1
#నిర్వచించు GL_CONTEXT_RELEASE_BEHAVIOR_KHR   0x82FB
#నిర్వచించు GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_KHR 0x82FC
#అయితే_ముగింపు /* GL_KHR_context_flush_control */

#నిర్వచితం_కాకపోతే GL_KHR_debug
#నిర్వచించు GL_KHR_debug 1
రకనిర్వచనం శూన్య (GL_APIENTRY  *GLDEBUGPROCKHR)(GLenum ఆధారం,GLenum type,GLuint id,GLenum severity,GLsizei నిడివి,స్థిరరాశి GLchar *సందేశం,స్థిరరాశి శూన్య *userParam);
#నిర్వచించు GL_SAMPLER                        0x82E6
#నిర్వచించు GL_DEBUG_OUTPUT_SYNCHRONOUS_KHR   0x8242
#నిర్వచించు GL_DEBUG_తదుపరి_LOGGED_సందేశం_నిడివి_KHR 0x8243
#నిర్వచించు GL_DEBUG_CALLBACK_FUNCTION_KHR    0x8244
#నిర్వచించు GL_DEBUG_CALLBACK_USER_PARAM_KHR  0x8245
#నిర్వచించు GL_DEBUG_ఆధారం_API_KHR           0x8246
#నిర్వచించు GL_DEBUG_ఆధారం_కిటికీ_SYSTEM_KHR 0x8247
#నిర్వచించు GL_DEBUG_ఆధారం_SHADER_COMPILER_KHR 0x8248
#నిర్వచించు GL_DEBUG_ఆధారం_మూడవ_PARTY_KHR   0x8249
#నిర్వచించు GL_DEBUG_ఆధారం_APPLICATION_KHR   0x824A
#నిర్వచించు GL_DEBUG_ఆధారం_OTHER_KHR         0x824B
#నిర్వచించు GL_DEBUG_TYPE_ERROR_KHR           0x824C
#నిర్వచించు GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_KHR 0x824D
#నిర్వచించు GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_KHR 0x824E
#నిర్వచించు GL_DEBUG_TYPE_PORTABILITY_KHR     0x824F
#నిర్వచించు GL_DEBUG_TYPE_PERFORMANCE_KHR     0x8250
#నిర్వచించు GL_DEBUG_TYPE_OTHER_KHR           0x8251
#నిర్వచించు GL_DEBUG_TYPE_MARKER_KHR          0x8268
#నిర్వచించు GL_DEBUG_TYPE_నెట్టు_సమూహం_KHR      0x8269
#నిర్వచించు GL_DEBUG_TYPE_తీయి_సమూహం_KHR       0x826A
#నిర్వచించు GL_DEBUG_SEVERITY_NOTIFICATION_KHR 0x826B
#నిర్వచించు GL_MAX_DEBUG_సమూహం_దొంతర_లోతు_KHR 0x826C
#నిర్వచించు GL_DEBUG_సమూహం_దొంతర_లోతు_KHR    0x826D
#నిర్వచించు GL_బఫరు_KHR                     0x82E0
#నిర్వచించు GL_SHADER_KHR                     0x82E1
#నిర్వచించు GL_కార్యక్రమం_KHR                    0x82E2
#నిర్వచించు GL_శీర్షం_ARRAY_KHR               0x8074
#నిర్వచించు GL_QUERY_KHR                      0x82E3
#నిర్వచించు GL_కార్యక్రమం_PIPELINE_KHR           0x82E4
#నిర్వచించు GL_SAMPLER_KHR                    0x82E6
#నిర్వచించు GL_MAX_LABEL_నిడివి_KHR           0x82E8
#నిర్వచించు GL_MAX_DEBUG_సందేశం_నిడివి_KHR   0x9143
#నిర్వచించు GL_MAX_DEBUG_LOGGED_MESSAGES_KHR  0x9144
#నిర్వచించు GL_DEBUG_LOGGED_MESSAGES_KHR      0x9145
#నిర్వచించు GL_DEBUG_SEVERITY_ఎగువ_KHR        0x9146
#నిర్వచించు GL_DEBUG_SEVERITY_MEDIUM_KHR      0x9147
#నిర్వచించు GL_DEBUG_SEVERITY_దిగువ_KHR         0x9148
#నిర్వచించు GL_DEBUG_OUTPUT_KHR               0x92E0
#నిర్వచించు GL_CONTEXT_FLAG_DEBUG_బిట్టు_KHR     0x00000002
#నిర్వచించు GL_దొంతర_అధికప్రవాహం_KHR             0x0503
#నిర్వచించు GL_దొంతర_UNDERFLOW_KHR            0x0504
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDEBUGMESSAGECONTROLKHRPROC) (GLenum ఆధారం, GLenum type, GLenum severity, GLsizei లెక్క, స్థిరరాశి GLuint *ids, GLboolean enabled);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDEBUGMESSAGEINSERTKHRPROC) (GLenum ఆధారం, GLenum type, GLuint id, GLenum severity, GLsizei నిడివి, స్థిరరాశి GLchar *buf);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDEBUGMESSAGECALLBACKKHRPROC) (GLDEBUGPROCKHR callback, స్థిరరాశి శూన్య *userParam);
రకనిర్వచనం GLuint (GL_APIENTRYP PFNGLGETDEBUGMESSAGELOGKHRPROC) (GLuint లెక్క, GLsizei buf_కొలత, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *సందేశం_Log);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPUSHDEBUGGROUPKHRPROC) (GLenum ఆధారం, GLuint id, GLsizei నిడివి, స్థిరరాశి GLchar *సందేశం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPOPDEBUGGROUPKHRPROC) (శూన్య);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLOBJECTLABELKHRPROC) (GLenum identifier, GLuint name, GLsizei నిడివి, స్థిరరాశి GLchar *label);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETOBJECTLABELKHRPROC) (GLenum identifier, GLuint name, GLsizei buf_కొలత, GLsizei *నిడివి, GLchar *label);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLOBJECTPTRLABELKHRPROC) (స్థిరరాశి శూన్య *ptr, GLsizei నిడివి, స్థిరరాశి GLchar *label);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETOBJECTPTRLABELKHRPROC) (స్థిరరాశి శూన్య *ptr, GLsizei buf_కొలత, GLsizei *నిడివి, GLchar *label);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETPOINTERVKHRPROC) (GLenum pname, శూన్య **params);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_Debug_సందేశం_Control_KHR (GLenum ఆధారం, GLenum type, GLenum severity, GLsizei లెక్క, స్థిరరాశి GLuint *ids, GLboolean enabled);
GL_APICALL శూన్య GL_APIENTRY gl_Debug_సందేశం_చొప్పించు_KHR (GLenum ఆధారం, GLenum type, GLuint id, GLenum severity, GLsizei నిడివి, స్థిరరాశి GLchar *buf);
GL_APICALL శూన్య GL_APIENTRY gl_Debug_సందేశం_Callback_KHR (GLDEBUGPROCKHR callback, స్థిరరాశి శూన్య *userParam);
GL_APICALL GLuint GL_APIENTRY gl_Get_Debug_సందేశం_Log_KHR (GLuint లెక్క, GLsizei buf_కొలత, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *సందేశం_Log);
GL_APICALL శూన్య GL_APIENTRY gl_నెట్టు_Debug_సమూహం_KHR (GLenum ఆధారం, GLuint id, GLsizei నిడివి, స్థిరరాశి GLchar *సందేశం);
GL_APICALL శూన్య GL_APIENTRY gl_తీయి_Debug_సమూహం_KHR (శూన్య);
GL_APICALL శూన్య GL_APIENTRY glObjectLabelKHR (GLenum identifier, GLuint name, GLsizei నిడివి, స్థిరరాశి GLchar *label);
GL_APICALL శూన్య GL_APIENTRY glGetObjectLabelKHR (GLenum identifier, GLuint name, GLsizei buf_కొలత, GLsizei *నిడివి, GLchar *label);
GL_APICALL శూన్య GL_APIENTRY glObjectPtrLabelKHR (స్థిరరాశి శూన్య *ptr, GLsizei నిడివి, స్థిరరాశి GLchar *label);
GL_APICALL శూన్య GL_APIENTRY glGetObjectPtrLabelKHR (స్థిరరాశి శూన్య *ptr, GLsizei buf_కొలత, GLsizei *నిడివి, GLchar *label);
GL_APICALL శూన్య GL_APIENTRY glGetPointervKHR (GLenum pname, శూన్య **params);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_KHR_debug */

#నిర్వచితం_కాకపోతే GL_KHR_no_error
#నిర్వచించు GL_KHR_no_error 1
#నిర్వచించు GL_CONTEXT_FLAG_NO_ERROR_బిట్టు_KHR  0x00000008
#అయితే_ముగింపు /* GL_KHR_no_error */

#నిర్వచితం_కాకపోతే GL_KHR_parallel_shader_compile
#నిర్వచించు GL_KHR_parallel_shader_compile 1
#నిర్వచించు GL_MAX_SHADER_COMPILER_దారాలు_KHR 0x91B0
#నిర్వచించు GL_COMPLETION_స్థితి_KHR          0x91B1
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMAXSHADERCOMPILERTHREADSKHRPROC) (GLuint లెక్క);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_Max_Shader_Compiler_దారాలు_KHR (GLuint లెక్క);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_KHR_parallel_shader_compile */

#నిర్వచితం_కాకపోతే GL_KHR_robust_బఫరు_access_behavior
#నిర్వచించు GL_KHR_robust_బఫరు_access_behavior 1
#అయితే_ముగింపు /* GL_KHR_robust_buffer_access_behavior */

#నిర్వచితం_కాకపోతే GL_KHR_robustness
#నిర్వచించు GL_KHR_robustness 1
#నిర్వచించు GL_CONTEXT_ROBUST_ACCESS_KHR      0x90F3
#నిర్వచించు GL_LOSE_CONTEXT_ON_RESET_KHR      0x8252
#నిర్వచించు GL_GUILTY_CONTEXT_RESET_KHR       0x8253
#నిర్వచించు GL_INNOCENT_CONTEXT_RESET_KHR     0x8254
#నిర్వచించు GL_UNKNOWN_CONTEXT_RESET_KHR      0x8255
#నిర్వచించు GL_RESET_NOTIFICATION_STRATEGY_KHR 0x8256
#నిర్వచించు GL_NO_RESET_NOTIFICATION_KHR      0x8261
#నిర్వచించు GL_CONTEXT_కోల్పోయిన_KHR               0x0507
రకనిర్వచనం GLenum (GL_APIENTRYP PFNGLGETGRAPHICSRESETSTATUSKHRPROC) (శూన్య);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLREADNPIXELSKHRPROC) (GLint x, GLint y, GLsizei వెడల్పు, GLsizei ఎత్తు, GLenum format, GLenum type, GLsizei buf_కొలత, శూన్య *దత్తాంశం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETNUNIFORMFVKHRPROC) (GLuint కార్యక్రమం, GLint location, GLsizei buf_కొలత, GLfloat *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETNUNIFORMIVKHRPROC) (GLuint కార్యక్రమం, GLint location, GLsizei buf_కొలత, GLint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETNUNIFORMUIVKHRPROC) (GLuint కార్యక్రమం, GLint location, GLsizei buf_కొలత, GLuint *params);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL GLenum GL_APIENTRY gl_Get_Graphics_Reset_స్థితి_KHR (శూన్య);
GL_APICALL శూన్య GL_APIENTRY glReadnPixelsKHR (GLint x, GLint y, GLsizei వెడల్పు, GLsizei ఎత్తు, GLenum format, GLenum type, GLsizei buf_కొలత, శూన్య *దత్తాంశం);
GL_APICALL శూన్య GL_APIENTRY glGetnUniformfvKHR (GLuint కార్యక్రమం, GLint location, GLsizei buf_కొలత, GLfloat *params);
GL_APICALL శూన్య GL_APIENTRY glGetnUniformivKHR (GLuint కార్యక్రమం, GLint location, GLsizei buf_కొలత, GLint *params);
GL_APICALL శూన్య GL_APIENTRY glGetnUniformuivKHR (GLuint కార్యక్రమం, GLint location, GLsizei buf_కొలత, GLuint *params);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_KHR_robustness */

#నిర్వచితం_కాకపోతే GL_KHR_shader_subgroup
#నిర్వచించు GL_KHR_shader_subgroup 1
#నిర్వచించు GL_SUBGROUP_కొలత_KHR              0x9532
#నిర్వచించు GL_SUBGROUP_SUPPORTED_STAGES_KHR  0x9533
#నిర్వచించు GL_SUBGROUP_SUPPORTED_FEATURES_KHR 0x9534
#నిర్వచించు GL_SUBGROUP_QUAD_ALL_STAGES_KHR   0x9535
#నిర్వచించు GL_SUBGROUP_FEATURE_BASIC_బిట్టు_KHR 0x00000001
#నిర్వచించు GL_SUBGROUP_FEATURE_VOTE_బిట్టు_KHR  0x00000002
#నిర్వచించు GL_SUBGROUP_FEATURE_ARITHMETIC_బిట్టు_KHR 0x00000004
#నిర్వచించు GL_SUBGROUP_FEATURE_BALLOT_బిట్టు_KHR 0x00000008
#నిర్వచించు GL_SUBGROUP_FEATURE_SHUFFLE_బిట్టు_KHR 0x00000010
#నిర్వచించు GL_SUBGROUP_FEATURE_SHUFFLE_RELATIVE_బిట్టు_KHR 0x00000020
#నిర్వచించు GL_SUBGROUP_FEATURE_CLUSTERED_బిట్టు_KHR 0x00000040
#నిర్వచించు GL_SUBGROUP_FEATURE_QUAD_బిట్టు_KHR  0x00000080
#అయితే_ముగింపు /* GL_KHR_shader_subgroup */

#నిర్వచితం_కాకపోతే GL_KHR_texture_compression_astc_hdr
#నిర్వచించు GL_KHR_texture_compression_astc_hdr 1
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_4x4_KHR   0x93B0
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_5x4_KHR   0x93B1
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_5x5_KHR   0x93B2
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_6x5_KHR   0x93B3
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_6x6_KHR   0x93B4
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_8x5_KHR   0x93B5
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_8x6_KHR   0x93B6
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_8x8_KHR   0x93B7
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_10x5_KHR  0x93B8
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_10x6_KHR  0x93B9
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_10x8_KHR  0x93BA
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_10x10_KHR 0x93BB
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_12x10_KHR 0x93BC
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_12x12_KHR 0x93BD
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR 0x93D0
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR 0x93D1
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR 0x93D2
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR 0x93D3
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR 0x93D4
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR 0x93D5
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR 0x93D6
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR 0x93D7
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR 0x93D8
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR 0x93D9
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR 0x93DA
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR 0x93DB
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR 0x93DC
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR 0x93DD
#అయితే_ముగింపు /* GL_KHR_texture_compression_astc_hdr */

#నిర్వచితం_కాకపోతే GL_KHR_texture_compression_astc_ldr
#నిర్వచించు GL_KHR_texture_compression_astc_ldr 1
#అయితే_ముగింపు /* GL_KHR_texture_compression_astc_ldr */

#నిర్వచితం_కాకపోతే GL_KHR_texture_compression_astc_sliced_3d
#నిర్వచించు GL_KHR_texture_compression_astc_sliced_3d 1
#అయితే_ముగింపు /* GL_KHR_texture_compression_astc_sliced_3d */

#నిర్వచితం_కాకపోతే GL_OES_EGL_image
#నిర్వచించు GL_OES_EGL_image 1
రకనిర్వచనం శూన్య *GLeglImageOES;
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLEGLIMAGETARGETTEXTURE2DOESPROC) (GLenum లక్ష్యం, GLeglImageOES image);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLEGLIMAGETARGETRENDERBUFFERSTORAGEOESPROC) (GLenum లక్ష్యం, GLeglImageOES image);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_EGLImage_లక్ష్యం_Texture2_DOES (GLenum లక్ష్యం, GLeglImageOES image);
GL_APICALL శూన్య GL_APIENTRY gl_EGLImage_లక్ష్యం_Renderbuffer_Storage_OES (GLenum లక్ష్యం, GLeglImageOES image);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_OES_EGL_image */

#నిర్వచితం_కాకపోతే GL_OES_EGL_image_external
#నిర్వచించు GL_OES_EGL_image_external 1
#నిర్వచించు GL_TEXTURE_EXTERNAL_OES           0x8D65
#నిర్వచించు GL_TEXTURE_BINDING_EXTERNAL_OES   0x8D67
#నిర్వచించు GL_REQUIRED_TEXTURE_IMAGE_UNITS_OES 0x8D68
#నిర్వచించు GL_SAMPLER_EXTERNAL_OES           0x8D66
#అయితే_ముగింపు /* GL_OES_EGL_image_external */

#నిర్వచితం_కాకపోతే GL_OES_EGL_image_external_essl3
#నిర్వచించు GL_OES_EGL_image_external_essl3 1
#అయితే_ముగింపు /* GL_OES_EGL_image_external_essl3 */

#నిర్వచితం_కాకపోతే GL_OES_compressed_ETC1_RGB8_sub_texture
#నిర్వచించు GL_OES_compressed_ETC1_RGB8_sub_texture 1
#అయితే_ముగింపు /* GL_OES_compressed_ETC1_RGB8_sub_texture */

#నిర్వచితం_కాకపోతే GL_OES_compressed_ETC1_RGB8_texture
#నిర్వచించు GL_OES_compressed_ETC1_RGB8_texture 1
#నిర్వచించు GL_ETC1_RGB8_OES                  0x8D64
#అయితే_ముగింపు /* GL_OES_compressed_ETC1_RGB8_texture */

#నిర్వచితం_కాకపోతే GL_OES_compressed_paletted_texture
#నిర్వచించు GL_OES_compressed_paletted_texture 1
#నిర్వచించు GL_PALETTE4_RGB8_OES              0x8B90
#నిర్వచించు GL_PALETTE4_RGBA8_OES             0x8B91
#నిర్వచించు GL_PALETTE4_R5_G6_B5_OES          0x8B92
#నిర్వచించు GL_PALETTE4_RGBA4_OES             0x8B93
#నిర్వచించు GL_PALETTE4_RGB5_A1_OES           0x8B94
#నిర్వచించు GL_PALETTE8_RGB8_OES              0x8B95
#నిర్వచించు GL_PALETTE8_RGBA8_OES             0x8B96
#నిర్వచించు GL_PALETTE8_R5_G6_B5_OES          0x8B97
#నిర్వచించు GL_PALETTE8_RGBA4_OES             0x8B98
#నిర్వచించు GL_PALETTE8_RGB5_A1_OES           0x8B99
#అయితే_ముగింపు /* GL_OES_compressed_paletted_texture */

#నిర్వచితం_కాకపోతే GL_OES_copy_image
#నిర్వచించు GL_OES_copy_image 1
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCOPYIMAGESUBDATAOESPROC) (GLuint srcName, GLenum src_లక్ష్యం, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dst_లక్ష్యం, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei src_వెడల్పు, GLsizei src_ఎత్తు, GLsizei src_లోతు);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_Copy_Image_Sub_దత్తాంశం_OES (GLuint srcName, GLenum src_లక్ష్యం, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dst_లక్ష్యం, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei src_వెడల్పు, GLsizei src_ఎత్తు, GLsizei src_లోతు);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_OES_copy_image */

#నిర్వచితం_కాకపోతే GL_OES_depth24
#నిర్వచించు GL_OES_depth24 1
#నిర్వచించు GL_లోతు_COMPONENT24_OES          0x81A6
#అయితే_ముగింపు /* GL_OES_depth24 */

#నిర్వచితం_కాకపోతే GL_OES_depth32
#నిర్వచించు GL_OES_depth32 1
#నిర్వచించు GL_లోతు_COMPONENT32_OES          0x81A7
#అయితే_ముగింపు /* GL_OES_depth32 */

#నిర్వచితం_కాకపోతే GL_OES_లోతు_texture
#నిర్వచించు GL_OES_లోతు_texture 1
#అయితే_ముగింపు /* GL_OES_depth_texture */

#నిర్వచితం_కాకపోతే GL_OES_draw_buffers_సూచీకృత
#నిర్వచించు GL_OES_draw_buffers_సూచీకృత 1
#నిర్వచించు GL_MIN                            0x8007
#నిర్వచించు GL_MAX                            0x8008
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLENABLEIOESPROC) (GLenum లక్ష్యం, GLuint సూచీ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDISABLEIOESPROC) (GLenum లక్ష్యం, GLuint సూచీ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBLENDEQUATIONIOESPROC) (GLuint buf, GLenum బహుళకం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEIOESPROC) (GLuint buf, GLenum బహుళకం_RGB, GLenum బహుళకం_Alpha);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBLENDFUNCIOESPROC) (GLuint buf, GLenum src, GLenum dst);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEIOESPROC) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCOLORMASKIOESPROC) (GLuint సూచీ, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLISENABLEDIOESPROC) (GLenum లక్ష్యం, GLuint సూచీ);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glEnableiOES (GLenum లక్ష్యం, GLuint సూచీ);
GL_APICALL శూన్య GL_APIENTRY glDisableiOES (GLenum లక్ష్యం, GLuint సూచీ);
GL_APICALL శూన్య GL_APIENTRY glBlendEquationiOES (GLuint buf, GLenum బహుళకం);
GL_APICALL శూన్య GL_APIENTRY glBlendEquationSeparateiOES (GLuint buf, GLenum బహుళకం_RGB, GLenum బహుళకం_Alpha);
GL_APICALL శూన్య GL_APIENTRY glBlendFunciOES (GLuint buf, GLenum src, GLenum dst);
GL_APICALL శూన్య GL_APIENTRY glBlendFuncSeparateiOES (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
GL_APICALL శూన్య GL_APIENTRY glColorMaskiOES (GLuint సూచీ, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
GL_APICALL GLboolean GL_APIENTRY glIsEnablediOES (GLenum లక్ష్యం, GLuint సూచీ);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_OES_draw_buffers_indexed */

#నిర్వచితం_కాకపోతే GL_OES_draw_elements_పునాది_శీర్షం
#నిర్వచించు GL_OES_draw_elements_పునాది_శీర్షం 1
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWELEMENTSBASEVERTEXOESPROC) (GLenum బహుళకం, GLsizei లెక్క, GLenum type, స్థిరరాశి శూన్య *indices, GLint basevertex);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWRANGEELEMENTSBASEVERTEXOESPROC) (GLenum బహుళకం, GLuint ప్రారంభం, GLuint చివర, GLsizei లెక్క, GLenum type, స్థిరరాశి శూన్య *indices, GLint basevertex);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXOESPROC) (GLenum బహుళకం, GLsizei లెక్క, GLenum type, స్థిరరాశి శూన్య *indices, GLsizei instancecount, GLint basevertex);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSBASEVERTEXEXTPROC) (GLenum బహుళకం, స్థిరరాశి GLsizei *లెక్క, GLenum type, స్థిరరాశి శూన్య *స్థిరరాశి*indices, GLsizei drawcount, స్థిరరాశి GLint *basevertex);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_Draw_Elements_పునాది_శీర్షం_OES (GLenum బహుళకం, GLsizei లెక్క, GLenum type, స్థిరరాశి శూన్య *indices, GLint basevertex);
GL_APICALL శూన్య GL_APIENTRY gl_Draw_Range_Elements_పునాది_శీర్షం_OES (GLenum బహుళకం, GLuint ప్రారంభం, GLuint చివర, GLsizei లెక్క, GLenum type, స్థిరరాశి శూన్య *indices, GLint basevertex);
GL_APICALL శూన్య GL_APIENTRY gl_Draw_Elements_Instanced_పునాది_శీర్షం_OES (GLenum బహుళకం, GLsizei లెక్క, GLenum type, స్థిరరాశి శూన్య *indices, GLsizei instancecount, GLint basevertex);
GL_APICALL శూన్య GL_APIENTRY gl_Multi_Draw_Elements_పునాది_శీర్షం_EXT (GLenum బహుళకం, స్థిరరాశి GLsizei *లెక్క, GLenum type, స్థిరరాశి శూన్య *స్థిరరాశి*indices, GLsizei drawcount, స్థిరరాశి GLint *basevertex);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_OES_draw_elements_base_vertex */

#నిర్వచితం_కాకపోతే GL_OES_element_సూచీ_uint
#నిర్వచించు GL_OES_element_సూచీ_uint 1
#అయితే_ముగింపు /* GL_OES_element_index_uint */

#నిర్వచితం_కాకపోతే GL_OES_fbo_render_mipmap
#నిర్వచించు GL_OES_fbo_render_mipmap 1
#అయితే_ముగింపు /* GL_OES_fbo_render_mipmap */

#నిర్వచితం_కాకపోతే GL_OES_fragment_precision_ఎగువ
#నిర్వచించు GL_OES_fragment_precision_ఎగువ 1
#అయితే_ముగింపు /* GL_OES_fragment_precision_high */

#నిర్వచితం_కాకపోతే GL_OES_geometry_బిందువు_కొలత
#నిర్వచించు GL_OES_geometry_బిందువు_కొలత 1
#అయితే_ముగింపు /* GL_OES_geometry_point_size */

#నిర్వచితం_కాకపోతే GL_OES_geometry_shader
#నిర్వచించు GL_OES_geometry_shader 1
#నిర్వచించు GL_GEOMETRY_SHADER_OES            0x8DD9
#నిర్వచించు GL_GEOMETRY_SHADER_బిట్టు_OES        0x00000004
#నిర్వచించు GL_GEOMETRY_LINKED_VERTICES_బహిర్గతం_OES 0x8916
#నిర్వచించు GL_GEOMETRY_LINKED_ఆదానం_TYPE_OES 0x8917
#నిర్వచించు GL_GEOMETRY_LINKED_OUTPUT_TYPE_OES 0x8918
#నిర్వచించు GL_GEOMETRY_SHADER_INVOCATIONS_OES 0x887F
#నిర్వచించు GL_LAYER_PROVOKING_శీర్షం_OES     0x825E
#నిర్వచించు GL_పంక్తులు_ADJACENCY_OES            0x000A
#నిర్వచించు GL_పంక్తి_STRIP_ADJACENCY_OES       0x000B
#నిర్వచించు GL_TRIANGLES_ADJACENCY_OES        0x000C
#నిర్వచించు GL_TRIANGLE_STRIP_ADJACENCY_OES   0x000D
#నిర్వచించు GL_MAX_GEOMETRY_ఏకరీతి_COMPONENTS_OES 0x8DDF
#నిర్వచించు GL_MAX_GEOMETRY_ఏకరీతి_ఖండాలు_OES 0x8A2C
#నిర్వచించు GL_MAX_COMBINED_GEOMETRY_ఏకరీతి_COMPONENTS_OES 0x8A32
#నిర్వచించు GL_MAX_GEOMETRY_ఆదానం_COMPONENTS_OES 0x9123
#నిర్వచించు GL_MAX_GEOMETRY_OUTPUT_COMPONENTS_OES 0x9124
#నిర్వచించు GL_MAX_GEOMETRY_OUTPUT_VERTICES_OES 0x8DE0
#నిర్వచించు GL_MAX_GEOMETRY_మొత్తం_OUTPUT_COMPONENTS_OES 0x8DE1
#నిర్వచించు GL_MAX_GEOMETRY_SHADER_INVOCATIONS_OES 0x8E5A
#నిర్వచించు GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_OES 0x8C29
#నిర్వచించు GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS_OES 0x92CF
#నిర్వచించు GL_MAX_GEOMETRY_ATOMIC_COUNTERS_OES 0x92D5
#నిర్వచించు GL_MAX_GEOMETRY_IMAGE_UNIFORMS_OES 0x90CD
#నిర్వచించు GL_MAX_GEOMETRY_SHADER_STORAGE_ఖండాలు_OES 0x90D7
#నిర్వచించు GL_మొదటి_శీర్షం_CONVENTION_OES    0x8E4D
#నిర్వచించు GL_చివరి_శీర్షం_CONVENTION_OES     0x8E4E
#నిర్వచించు GL_UNDEFINED_శీర్షం_OES           0x8260
#నిర్వచించు GL_PRIMITIVES_GENERATED_OES       0x8C87
#నిర్వచించు GL_FRAMEBUFFER_DEFAULT_LAYERS_OES 0x9312
#నిర్వచించు GL_MAX_FRAMEBUFFER_LAYERS_OES     0x9317
#నిర్వచించు GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_OES 0x8DA8
#నిర్వచించు GL_FRAMEBUFFER_ATTACHMENT_LAYERED_OES 0x8DA7
#నిర్వచించు GL_REFERENCED_BY_GEOMETRY_SHADER_OES 0x9309
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREOESPROC) (GLenum లక్ష్యం, GLenum attachment, GLuint texture, GLint level);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glFramebufferTextureOES (GLenum లక్ష్యం, GLenum attachment, GLuint texture, GLint level);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_OES_geometry_shader */

#నిర్వచితం_కాకపోతే GL_OES_get_కార్యక్రమం_ద్విమాన
#నిర్వచించు GL_OES_get_కార్యక్రమం_ద్విమాన 1
#నిర్వచించు GL_కార్యక్రమం_ద్విమాన_నిడివి_OES      0x8741
#నిర్వచించు GL_అంకె_కార్యక్రమం_ద్విమాన_FORMATS_OES 0x87FE
#నిర్వచించు GL_కార్యక్రమం_ద్విమాన_FORMATS_OES     0x87FF
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETPROGRAMBINARYOESPROC) (GLuint కార్యక్రమం, GLsizei buf_కొలత, GLsizei *నిడివి, GLenum *ద్విమాన_Format, శూన్య *ద్విమాన);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMBINARYOESPROC) (GLuint కార్యక్రమం, GLenum ద్విమాన_Format, స్థిరరాశి శూన్య *ద్విమాన, GLint నిడివి);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_Get_కార్యక్రమం_ద్విమాన_OES (GLuint కార్యక్రమం, GLsizei buf_కొలత, GLsizei *నిడివి, GLenum *ద్విమాన_Format, శూన్య *ద్విమాన);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_ద్విమాన_OES (GLuint కార్యక్రమం, GLenum ద్విమాన_Format, స్థిరరాశి శూన్య *ద్విమాన, GLint నిడివి);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_OES_get_program_binary */

#నిర్వచితం_కాకపోతే GL_OES_gpu_shader5
#నిర్వచించు GL_OES_gpu_shader5 1
#అయితే_ముగింపు /* GL_OES_gpu_shader5 */

#నిర్వచితం_కాకపోతే GL_OES_mapbuffer
#నిర్వచించు GL_OES_mapbuffer 1
#నిర్వచించు GL_WRITE_ONLY_OES                 0x88B9
#నిర్వచించు GL_బఫరు_ACCESS_OES              0x88BB
#నిర్వచించు GL_బఫరు_MAPPED_OES              0x88BC
#నిర్వచించు GL_బఫరు_MAP_సూచిక_OES         0x88BD
రకనిర్వచనం శూన్య *(GL_APIENTRYP PFNGLMAPBUFFEROESPROC) (GLenum లక్ష్యం, GLenum access);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLUNMAPBUFFEROESPROC) (GLenum లక్ష్యం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETBUFFERPOINTERVOESPROC) (GLenum లక్ష్యం, GLenum pname, శూన్య **params);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య *GL_APIENTRY gl_Map_బఫరు_OES (GLenum లక్ష్యం, GLenum access);
GL_APICALL GLboolean GL_APIENTRY gl_Unmap_బఫరు_OES (GLenum లక్ష్యం);
GL_APICALL శూన్య GL_APIENTRY gl_Get_బఫరు_Pointerv_OES (GLenum లక్ష్యం, GLenum pname, శూన్య **params);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_OES_mapbuffer */

#నిర్వచితం_కాకపోతే GL_OES_packed_లోతు_stencil
#నిర్వచించు GL_OES_packed_లోతు_stencil 1
#నిర్వచించు GL_లోతు_STENCIL_OES              0x84F9
#నిర్వచించు GL_UNSIGNED_INT_24_8_OES          0x84FA
#నిర్వచించు GL_DEPTH24_STENCIL8_OES           0x88F0
#అయితే_ముగింపు /* GL_OES_packed_depth_stencil */

#నిర్వచితం_కాకపోతే GL_OES_primitive_bounding_box
#నిర్వచించు GL_OES_primitive_bounding_box 1
#నిర్వచించు GL_PRIMITIVE_BOUNDING_BOX_OES     0x92BE
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPRIMITIVEBOUNDINGBOXOESPROC) (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glPrimitiveBoundingBoxOES (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_OES_primitive_bounding_box */

#నిర్వచితం_కాకపోతే GL_OES_required_internalformat
#నిర్వచించు GL_OES_required_internalformat 1
#నిర్వచించు GL_ALPHA8_OES                     0x803C
#నిర్వచించు GL_లోతు_COMPONENT16_OES          0x81A5
#నిర్వచించు GL_LUMINANCE4_ALPHA4_OES          0x8043
#నిర్వచించు GL_LUMINANCE8_ALPHA8_OES          0x8045
#నిర్వచించు GL_LUMINANCE8_OES                 0x8040
#నిర్వచించు GL_RGBA4_OES                      0x8056
#నిర్వచించు GL_RGB5_A1_OES                    0x8057
#నిర్వచించు GL_RGB565_OES                     0x8D62
#నిర్వచించు GL_RGB8_OES                       0x8051
#నిర్వచించు GL_RGBA8_OES                      0x8058
#నిర్వచించు GL_RGB10_EXT                      0x8052
#నిర్వచించు GL_RGB10_A2_EXT                   0x8059
#అయితే_ముగింపు /* GL_OES_required_internalformat */

#నిర్వచితం_కాకపోతే GL_OES_rgb8_rgba8
#నిర్వచించు GL_OES_rgb8_rgba8 1
#అయితే_ముగింపు /* GL_OES_rgb8_rgba8 */

#నిర్వచితం_కాకపోతే GL_OES_sample_shading
#నిర్వచించు GL_OES_sample_shading 1
#నిర్వచించు GL_SAMPLE_SHADING_OES             0x8C36
#నిర్వచించు GL_MIN_SAMPLE_SHADING_విలువ_OES   0x8C37
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMINSAMPLESHADINGOESPROC) (GLfloat విలువ);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glMinSampleShadingOES (GLfloat విలువ);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_OES_sample_shading */

#నిర్వచితం_కాకపోతే GL_OES_sample_variables
#నిర్వచించు GL_OES_sample_variables 1
#అయితే_ముగింపు /* GL_OES_sample_variables */

#నిర్వచితం_కాకపోతే GL_OES_shader_image_atomic
#నిర్వచించు GL_OES_shader_image_atomic 1
#అయితే_ముగింపు /* GL_OES_shader_image_atomic */

#నిర్వచితం_కాకపోతే GL_OES_shader_io_ఖండాలు
#నిర్వచించు GL_OES_shader_io_ఖండాలు 1
#అయితే_ముగింపు /* GL_OES_shader_io_blocks */

#నిర్వచితం_కాకపోతే GL_OES_shader_multisample_interpolation
#నిర్వచించు GL_OES_shader_multisample_interpolation 1
#నిర్వచించు GL_MIN_FRAGMENT_INTERPOLATION_స్థానభ్రంశం_OES 0x8E5B
#నిర్వచించు GL_MAX_FRAGMENT_INTERPOLATION_స్థానభ్రంశం_OES 0x8E5C
#నిర్వచించు GL_FRAGMENT_INTERPOLATION_స్థానభ్రంశం_బిట్లు_OES 0x8E5D
#అయితే_ముగింపు /* GL_OES_shader_multisample_interpolation */

#నిర్వచితం_కాకపోతే GL_OES_standard_derivatives
#నిర్వచించు GL_OES_standard_derivatives 1
#నిర్వచించు GL_FRAGMENT_SHADER_DERIVATIVE_HINT_OES 0x8B8B
#అయితే_ముగింపు /* GL_OES_standard_derivatives */

#నిర్వచితం_కాకపోతే GL_OES_stencil1
#నిర్వచించు GL_OES_stencil1 1
#నిర్వచించు GL_STENCIL_INDEX1_OES             0x8D46
#అయితే_ముగింపు /* GL_OES_stencil1 */

#నిర్వచితం_కాకపోతే GL_OES_stencil4
#నిర్వచించు GL_OES_stencil4 1
#నిర్వచించు GL_STENCIL_INDEX4_OES             0x8D47
#అయితే_ముగింపు /* GL_OES_stencil4 */

#నిర్వచితం_కాకపోతే GL_OES_surfaceless_context
#నిర్వచించు GL_OES_surfaceless_context 1
#నిర్వచించు GL_FRAMEBUFFER_UNDEFINED_OES      0x8219
#అయితే_ముగింపు /* GL_OES_surfaceless_context */

#నిర్వచితం_కాకపోతే GL_OES_tessellation_బిందువు_కొలత
#నిర్వచించు GL_OES_tessellation_బిందువు_కొలత 1
#అయితే_ముగింపు /* GL_OES_tessellation_point_size */

#నిర్వచితం_కాకపోతే GL_OES_tessellation_shader
#నిర్వచించు GL_OES_tessellation_shader 1
#నిర్వచించు GL_PATCHES_OES                    0x000E
#నిర్వచించు GL_PATCH_VERTICES_OES             0x8E72
#నిర్వచించు GL_TESS_CONTROL_OUTPUT_VERTICES_OES 0x8E75
#నిర్వచించు GL_TESS_GEN_బహుళకం_OES              0x8E76
#నిర్వచించు GL_TESS_GEN_SPACING_OES           0x8E77
#నిర్వచించు GL_TESS_GEN_శీర్షం_క్రమం_OES      0x8E78
#నిర్వచించు GL_TESS_GEN_బిందువు_బహుళకం_OES        0x8E79
#నిర్వచించు GL_ISOLINES_OES                   0x8E7A
#నిర్వచించు GL_QUADS_OES                      0x0007
#నిర్వచించు GL_FRACTIONAL_ODD_OES             0x8E7B
#నిర్వచించు GL_FRACTIONAL_EVEN_OES            0x8E7C
#నిర్వచించు GL_MAX_PATCH_VERTICES_OES         0x8E7D
#నిర్వచించు GL_MAX_TESS_GEN_LEVEL_OES         0x8E7E
#నిర్వచించు GL_MAX_TESS_CONTROL_ఏకరీతి_COMPONENTS_OES 0x8E7F
#నిర్వచించు GL_MAX_TESS_EVALUATION_ఏకరీతి_COMPONENTS_OES 0x8E80
#నిర్వచించు GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS_OES 0x8E81
#నిర్వచించు GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS_OES 0x8E82
#నిర్వచించు GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS_OES 0x8E83
#నిర్వచించు GL_MAX_TESS_PATCH_COMPONENTS_OES  0x8E84
#నిర్వచించు GL_MAX_TESS_CONTROL_మొత్తం_OUTPUT_COMPONENTS_OES 0x8E85
#నిర్వచించు GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS_OES 0x8E86
#నిర్వచించు GL_MAX_TESS_CONTROL_ఏకరీతి_ఖండాలు_OES 0x8E89
#నిర్వచించు GL_MAX_TESS_EVALUATION_ఏకరీతి_ఖండాలు_OES 0x8E8A
#నిర్వచించు GL_MAX_TESS_CONTROL_ఆదానం_COMPONENTS_OES 0x886C
#నిర్వచించు GL_MAX_TESS_EVALUATION_ఆదానం_COMPONENTS_OES 0x886D
#నిర్వచించు GL_MAX_COMBINED_TESS_CONTROL_ఏకరీతి_COMPONENTS_OES 0x8E1E
#నిర్వచించు GL_MAX_COMBINED_TESS_EVALUATION_ఏకరీతి_COMPONENTS_OES 0x8E1F
#నిర్వచించు GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS_OES 0x92CD
#నిర్వచించు GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS_OES 0x92CE
#నిర్వచించు GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS_OES 0x92D3
#నిర్వచించు GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS_OES 0x92D4
#నిర్వచించు GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS_OES 0x90CB
#నిర్వచించు GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS_OES 0x90CC
#నిర్వచించు GL_MAX_TESS_CONTROL_SHADER_STORAGE_ఖండాలు_OES 0x90D8
#నిర్వచించు GL_MAX_TESS_EVALUATION_SHADER_STORAGE_ఖండాలు_OES 0x90D9
#నిర్వచించు GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED_OES 0x8221
#నిర్వచించు GL_IS_చొప్పున_PATCH_OES               0x92E7
#నిర్వచించు GL_REFERENCED_BY_TESS_CONTROL_SHADER_OES 0x9307
#నిర్వచించు GL_REFERENCED_BY_TESS_EVALUATION_SHADER_OES 0x9308
#నిర్వచించు GL_TESS_CONTROL_SHADER_OES        0x8E88
#నిర్వచించు GL_TESS_EVALUATION_SHADER_OES     0x8E87
#నిర్వచించు GL_TESS_CONTROL_SHADER_బిట్టు_OES    0x00000008
#నిర్వచించు GL_TESS_EVALUATION_SHADER_బిట్టు_OES 0x00000010
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPATCHPARAMETERIOESPROC) (GLenum pname, GLint విలువ);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glPatchParameteriOES (GLenum pname, GLint విలువ);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_OES_tessellation_shader */

#నిర్వచితం_కాకపోతే GL_OES_texture_3D
#నిర్వచించు GL_OES_texture_3D 1
#నిర్వచించు GL_TEXTURE_WRAP_R_OES             0x8072
#నిర్వచించు GL_TEXTURE_3D_OES                 0x806F
#నిర్వచించు GL_TEXTURE_BINDING_3D_OES         0x806A
#నిర్వచించు GL_MAX_3_D_TEXTURE_కొలత_OES        0x8073
#నిర్వచించు GL_SAMPLER_3D_OES                 0x8B5F
#నిర్వచించు GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_3D_ZOFFSET_OES 0x8CD4
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXIMAGE3DOESPROC) (GLenum లక్ష్యం, GLint level, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLint border, GLenum format, GLenum type, స్థిరరాశి శూన్య *pixels);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXSUBIMAGE3DOESPROC) (GLenum లక్ష్యం, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLenum format, GLenum type, స్థిరరాశి శూన్య *pixels);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCOPYTEXSUBIMAGE3DOESPROC) (GLenum లక్ష్యం, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei వెడల్పు, GLsizei ఎత్తు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCOMPRESSEDTEXIMAGE3DOESPROC) (GLenum లక్ష్యం, GLint level, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLint border, GLsizei image_కొలత, స్థిరరాశి శూన్య *దత్తాంశం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE3DOESPROC) (GLenum లక్ష్యం, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLenum format, GLsizei image_కొలత, స్థిరరాశి శూన్య *దత్తాంశం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE3DOESPROC) (GLenum లక్ష్యం, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glTexImage3DOES (GLenum లక్ష్యం, GLint level, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLint border, GLenum format, GLenum type, స్థిరరాశి శూన్య *pixels);
GL_APICALL శూన్య GL_APIENTRY glTexSubImage3DOES (GLenum లక్ష్యం, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLenum format, GLenum type, స్థిరరాశి శూన్య *pixels);
GL_APICALL శూన్య GL_APIENTRY glCopyTexSubImage3DOES (GLenum లక్ష్యం, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei వెడల్పు, GLsizei ఎత్తు);
GL_APICALL శూన్య GL_APIENTRY glCompressedTexImage3DOES (GLenum లక్ష్యం, GLint level, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLint border, GLsizei image_కొలత, స్థిరరాశి శూన్య *దత్తాంశం);
GL_APICALL శూన్య GL_APIENTRY glCompressedTexSubImage3DOES (GLenum లక్ష్యం, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLenum format, GLsizei image_కొలత, స్థిరరాశి శూన్య *దత్తాంశం);
GL_APICALL శూన్య GL_APIENTRY glFramebufferTexture3DOES (GLenum లక్ష్యం, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_OES_texture_3D */

#నిర్వచితం_కాకపోతే GL_OES_texture_border_clamp
#నిర్వచించు GL_OES_texture_border_clamp 1
#నిర్వచించు GL_TEXTURE_BORDER_COLOR_OES       0x1004
#నిర్వచించు GL_CLAMP_గమ్యం_BORDER_OES            0x812D
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXPARAMETERIIVOESPROC) (GLenum లక్ష్యం, GLenum pname, స్థిరరాశి GLint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXPARAMETERIUIVOESPROC) (GLenum లక్ష్యం, GLenum pname, స్థిరరాశి GLuint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETTEXPARAMETERIIVOESPROC) (GLenum లక్ష్యం, GLenum pname, GLint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETTEXPARAMETERIUIVOESPROC) (GLenum లక్ష్యం, GLenum pname, GLuint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSAMPLERPARAMETERIIVOESPROC) (GLuint sampler, GLenum pname, స్థిరరాశి GLint *param);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSAMPLERPARAMETERIUIVOESPROC) (GLuint sampler, GLenum pname, స్థిరరాశి GLuint *param);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIIVOESPROC) (GLuint sampler, GLenum pname, GLint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIUIVOESPROC) (GLuint sampler, GLenum pname, GLuint *params);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glTexParameterIivOES (GLenum లక్ష్యం, GLenum pname, స్థిరరాశి GLint *params);
GL_APICALL శూన్య GL_APIENTRY glTexParameterIuivOES (GLenum లక్ష్యం, GLenum pname, స్థిరరాశి GLuint *params);
GL_APICALL శూన్య GL_APIENTRY glGetTexParameterIivOES (GLenum లక్ష్యం, GLenum pname, GLint *params);
GL_APICALL శూన్య GL_APIENTRY glGetTexParameterIuivOES (GLenum లక్ష్యం, GLenum pname, GLuint *params);
GL_APICALL శూన్య GL_APIENTRY glSamplerParameterIivOES (GLuint sampler, GLenum pname, స్థిరరాశి GLint *param);
GL_APICALL శూన్య GL_APIENTRY glSamplerParameterIuivOES (GLuint sampler, GLenum pname, స్థిరరాశి GLuint *param);
GL_APICALL శూన్య GL_APIENTRY glGetSamplerParameterIivOES (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL శూన్య GL_APIENTRY glGetSamplerParameterIuivOES (GLuint sampler, GLenum pname, GLuint *params);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_OES_texture_border_clamp */

#నిర్వచితం_కాకపోతే GL_OES_texture_బఫరు
#నిర్వచించు GL_OES_texture_బఫరు 1
#నిర్వచించు GL_TEXTURE_బఫరు_OES             0x8C2A
#నిర్వచించు GL_TEXTURE_బఫరు_BINDING_OES     0x8C2A
#నిర్వచించు GL_MAX_TEXTURE_బఫరు_కొలత_OES    0x8C2B
#నిర్వచించు GL_TEXTURE_BINDING_బఫరు_OES     0x8C2C
#నిర్వచించు GL_TEXTURE_బఫరు_దత్తాంశం_STORE_BINDING_OES 0x8C2D
#నిర్వచించు GL_TEXTURE_బఫరు_స్థానభ్రంశం_ALIGNMENT_OES 0x919F
#నిర్వచించు GL_SAMPLER_బఫరు_OES             0x8DC2
#నిర్వచించు GL_INT_SAMPLER_బఫరు_OES         0x8DD0
#నిర్వచించు GL_UNSIGNED_INT_SAMPLER_బఫరు_OES 0x8DD8
#నిర్వచించు GL_IMAGE_బఫరు_OES               0x9051
#నిర్వచించు GL_INT_IMAGE_బఫరు_OES           0x905C
#నిర్వచించు GL_UNSIGNED_INT_IMAGE_బఫరు_OES  0x9067
#నిర్వచించు GL_TEXTURE_బఫరు_స్థానభ్రంశం_OES      0x919D
#నిర్వచించు GL_TEXTURE_బఫరు_కొలత_OES        0x919E
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXBUFFEROESPROC) (GLenum లక్ష్యం, GLenum internalformat, GLuint బఫరు_2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXBUFFERRANGEOESPROC) (GLenum లక్ష్యం, GLenum internalformat, GLuint బఫరు_2, GLintptr స్థానభ్రంశం_2, GLsizeiptr కొలత);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_Tex_బఫరు_OES (GLenum లక్ష్యం, GLenum internalformat, GLuint బఫరు_2);
GL_APICALL శూన్య GL_APIENTRY gl_Tex_బఫరు_Range_OES (GLenum లక్ష్యం, GLenum internalformat, GLuint బఫరు_2, GLintptr స్థానభ్రంశం_2, GLsizeiptr కొలత);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_OES_texture_buffer */

#నిర్వచితం_కాకపోతే GL_OES_texture_compression_astc
#నిర్వచించు GL_OES_texture_compression_astc 1
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_3x3x3_OES 0x93C0
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_4x3x3_OES 0x93C1
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_4x4x3_OES 0x93C2
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_4x4x4_OES 0x93C3
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_5x4x4_OES 0x93C4
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_5x5x4_OES 0x93C5
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_5x5x5_OES 0x93C6
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_6x5x5_OES 0x93C7
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_6x6x5_OES 0x93C8
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_6x6x6_OES 0x93C9
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_3x3x3_OES 0x93E0
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x3x3_OES 0x93E1
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4x3_OES 0x93E2
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4x4_OES 0x93E3
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4x4_OES 0x93E4
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5x4_OES 0x93E5
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5x5_OES 0x93E6
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5x5_OES 0x93E7
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6x5_OES 0x93E8
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6x6_OES 0x93E9
#అయితే_ముగింపు /* GL_OES_texture_compression_astc */

#నిర్వచితం_కాకపోతే GL_OES_texture_cube_map_array
#నిర్వచించు GL_OES_texture_cube_map_array 1
#నిర్వచించు GL_TEXTURE_CUBE_MAP_ARRAY_OES     0x9009
#నిర్వచించు GL_TEXTURE_BINDING_CUBE_MAP_ARRAY_OES 0x900A
#నిర్వచించు GL_SAMPLER_CUBE_MAP_ARRAY_OES     0x900C
#నిర్వచించు GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW_OES 0x900D
#నిర్వచించు GL_INT_SAMPLER_CUBE_MAP_ARRAY_OES 0x900E
#నిర్వచించు GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY_OES 0x900F
#నిర్వచించు GL_IMAGE_CUBE_MAP_ARRAY_OES       0x9054
#నిర్వచించు GL_INT_IMAGE_CUBE_MAP_ARRAY_OES   0x905F
#నిర్వచించు GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY_OES 0x906A
#అయితే_ముగింపు /* GL_OES_texture_cube_map_array */

#నిర్వచితం_కాకపోతే GL_OES_texture_float
#నిర్వచించు GL_OES_texture_float 1
#అయితే_ముగింపు /* GL_OES_texture_float */

#నిర్వచితం_కాకపోతే GL_OES_texture_float_రేఖీయ
#నిర్వచించు GL_OES_texture_float_రేఖీయ 1
#అయితే_ముగింపు /* GL_OES_texture_float_linear */

#నిర్వచితం_కాకపోతే GL_OES_texture_half_float
#నిర్వచించు GL_OES_texture_half_float 1
#నిర్వచించు GL_HALF_FLOAT_OES                 0x8D61
#అయితే_ముగింపు /* GL_OES_texture_half_float */

#నిర్వచితం_కాకపోతే GL_OES_texture_half_float_రేఖీయ
#నిర్వచించు GL_OES_texture_half_float_రేఖీయ 1
#అయితే_ముగింపు /* GL_OES_texture_half_float_linear */

#నిర్వచితం_కాకపోతే GL_OES_texture_npot
#నిర్వచించు GL_OES_texture_npot 1
#అయితే_ముగింపు /* GL_OES_texture_npot */

#నిర్వచితం_కాకపోతే GL_OES_texture_stencil8
#నిర్వచించు GL_OES_texture_stencil8 1
#నిర్వచించు GL_STENCIL_సూచీ_OES              0x1901
#నిర్వచించు GL_STENCIL_INDEX8_OES             0x8D48
#అయితే_ముగింపు /* GL_OES_texture_stencil8 */

#నిర్వచితం_కాకపోతే GL_OES_texture_storage_multisample_2d_array
#నిర్వచించు GL_OES_texture_storage_multisample_2d_array 1
#నిర్వచించు GL_TEXTURE_2D_MULTISAMPLE_ARRAY_OES 0x9102
#నిర్వచించు GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY_OES 0x9105
#నిర్వచించు GL_SAMPLER_2D_MULTISAMPLE_ARRAY_OES 0x910B
#నిర్వచించు GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY_OES 0x910C
#నిర్వచించు GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY_OES 0x910D
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXSTORAGE3DMULTISAMPLEOESPROC) (GLenum లక్ష్యం, GLsizei samples, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLboolean fixedsamplelocations);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glTexStorage3DMultisampleOES (GLenum లక్ష్యం, GLsizei samples, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLboolean fixedsamplelocations);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_OES_texture_storage_multisample_2d_array */

#నిర్వచితం_కాకపోతే GL_OES_texture_view
#నిర్వచించు GL_OES_texture_view 1
#నిర్వచించు GL_TEXTURE_VIEW_MIN_LEVEL_OES     0x82DB
#నిర్వచించు GL_TEXTURE_VIEW_అంకె_స్థాయిలు_OES    0x82DC
#నిర్వచించు GL_TEXTURE_VIEW_MIN_LAYER_OES     0x82DD
#నిర్వచించు GL_TEXTURE_VIEW_అంకె_LAYERS_OES    0x82DE
#నిర్వచించు GL_TEXTURE_IMMUTABLE_స్థాయిలు       0x82DF
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXTUREVIEWOESPROC) (GLuint texture, GLenum లక్ష్యం, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glTextureViewOES (GLuint texture, GLenum లక్ష్యం, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_OES_texture_view */

#నిర్వచితం_కాకపోతే GL_OES_శీర్షం_array_object
#నిర్వచించు GL_OES_శీర్షం_array_object 1
#నిర్వచించు GL_శీర్షం_ARRAY_BINDING_OES       0x85B5
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBINDVERTEXARRAYOESPROC) (GLuint array);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDELETEVERTEXARRAYSOESPROC) (GLsizei n, స్థిరరాశి GLuint *arrays);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGENVERTEXARRAYSOESPROC) (GLsizei n, GLuint *arrays);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLISVERTEXARRAYOESPROC) (GLuint array);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_Bind_శీర్షం_Array_OES (GLuint array);
GL_APICALL శూన్య GL_APIENTRY gl_Delete_శీర్షం_Arrays_OES (GLsizei n, స్థిరరాశి GLuint *arrays);
GL_APICALL శూన్య GL_APIENTRY gl_Gen_శీర్షం_Arrays_OES (GLsizei n, GLuint *arrays);
GL_APICALL GLboolean GL_APIENTRY gl_Is_శీర్షం_Array_OES (GLuint array);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_OES_vertex_array_object */

#నిర్వచితం_కాకపోతే GL_OES_శీర్షం_half_float
#నిర్వచించు GL_OES_శీర్షం_half_float 1
#అయితే_ముగింపు /* GL_OES_vertex_half_float */

#నిర్వచితం_కాకపోతే GL_OES_శీర్షం_type_10_10_10_2
#నిర్వచించు GL_OES_శీర్షం_type_10_10_10_2 1
#నిర్వచించు GL_UNSIGNED_INT_10_10_10_2_OES    0x8DF6
#నిర్వచించు GL_INT_10_10_10_2_OES             0x8DF7
#అయితే_ముగింపు /* GL_OES_vertex_type_10_10_10_2 */

#నిర్వచితం_కాకపోతే GL_OES_viewport_array
#నిర్వచించు GL_OES_viewport_array 1
#నిర్వచించు GL_MAX_VIEWPORTS_OES              0x825B
#నిర్వచించు GL_VIEWPORT_SUBPIXEL_బిట్లు_OES     0x825C
#నిర్వచించు GL_VIEWPORT_BOUNDS_RANGE_OES      0x825D
#నిర్వచించు GL_VIEWPORT_సూచీ_PROVOKING_శీర్షం_OES 0x825F
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLVIEWPORTARRAYVOESPROC) (GLuint మొదటి, GLsizei లెక్క, స్థిరరాశి GLfloat *v);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLVIEWPORTINDEXEDFOESPROC) (GLuint సూచీ, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLVIEWPORTINDEXEDFVOESPROC) (GLuint సూచీ, స్థిరరాశి GLfloat *v);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSCISSORARRAYVOESPROC) (GLuint మొదటి, GLsizei లెక్క, స్థిరరాశి GLint *v);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSCISSORINDEXEDOESPROC) (GLuint సూచీ, GLint ఎడమ, GLint bottom, GLsizei వెడల్పు, GLsizei ఎత్తు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSCISSORINDEXEDVOESPROC) (GLuint సూచీ, స్థిరరాశి GLint *v);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDEPTHRANGEARRAYFVOESPROC) (GLuint మొదటి, GLsizei లెక్క, స్థిరరాశి GLfloat *v);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDEPTHRANGEINDEXEDFOESPROC) (GLuint సూచీ, GLfloat n, GLfloat f);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETFLOATI_VOESPROC) (GLenum లక్ష్యం, GLuint సూచీ, GLfloat *దత్తాంశం);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glViewportArrayvOES (GLuint మొదటి, GLsizei లెక్క, స్థిరరాశి GLfloat *v);
GL_APICALL శూన్య GL_APIENTRY glViewportIndexedfOES (GLuint సూచీ, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
GL_APICALL శూన్య GL_APIENTRY glViewportIndexedfvOES (GLuint సూచీ, స్థిరరాశి GLfloat *v);
GL_APICALL శూన్య GL_APIENTRY glScissorArrayvOES (GLuint మొదటి, GLsizei లెక్క, స్థిరరాశి GLint *v);
GL_APICALL శూన్య GL_APIENTRY gl_Scissor_సూచీకృత_OES (GLuint సూచీ, GLint ఎడమ, GLint bottom, GLsizei వెడల్పు, GLsizei ఎత్తు);
GL_APICALL శూన్య GL_APIENTRY glScissorIndexedvOES (GLuint సూచీ, స్థిరరాశి GLint *v);
GL_APICALL శూన్య GL_APIENTRY gl_లోతు_Range_Arrayfv_OES (GLuint మొదటి, GLsizei లెక్క, స్థిరరాశి GLfloat *v);
GL_APICALL శూన్య GL_APIENTRY gl_లోతు_Range_Indexedf_OES (GLuint సూచీ, GLfloat n, GLfloat f);
GL_APICALL శూన్య GL_APIENTRY glGetFloati_vOES (GLenum లక్ష్యం, GLuint సూచీ, GLfloat *దత్తాంశం);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_OES_viewport_array */

#నిర్వచితం_కాకపోతే GL_AMD_compressed_3DC_texture
#నిర్వచించు GL_AMD_compressed_3DC_texture 1
#నిర్వచించు GL_3DC_X_AMD                      0x87F9
#నిర్వచించు GL_3DC_XY_AMD                     0x87FA
#అయితే_ముగింపు /* GL_AMD_compressed_3DC_texture */

#నిర్వచితం_కాకపోతే GL_AMD_compressed_ATC_texture
#నిర్వచించు GL_AMD_compressed_ATC_texture 1
#నిర్వచించు GL_ATC_RGB_AMD                    0x8C92
#నిర్వచించు GL_ATC_RGBA_EXPLICIT_ALPHA_AMD    0x8C93
#నిర్వచించు GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD 0x87EE
#అయితే_ముగింపు /* GL_AMD_compressed_ATC_texture */

#నిర్వచితం_కాకపోతే GL_AMD_framebuffer_multisample_advanced
#నిర్వచించు GL_AMD_framebuffer_multisample_advanced 1
#నిర్వచించు GL_RENDERBUFFER_STORAGE_SAMPLES_AMD 0x91B2
#నిర్వచించు GL_MAX_COLOR_FRAMEBUFFER_SAMPLES_AMD 0x91B3
#నిర్వచించు GL_MAX_COLOR_FRAMEBUFFER_STORAGE_SAMPLES_AMD 0x91B4
#నిర్వచించు GL_MAX_లోతు_STENCIL_FRAMEBUFFER_SAMPLES_AMD 0x91B5
#నిర్వచించు GL_అంకె_SUPPORTED_MULTISAMPLE_MODES_AMD 0x91B6
#నిర్వచించు GL_SUPPORTED_MULTISAMPLE_MODES_AMD 0x91B7
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC) (GLenum లక్ష్యం, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC) (GLuint renderbuffer, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glRenderbufferStorageMultisampleAdvancedAMD (GLenum లక్ష్యం, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
GL_APICALL శూన్య GL_APIENTRY glNamedRenderbufferStorageMultisampleAdvancedAMD (GLuint renderbuffer, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_AMD_framebuffer_multisample_advanced */

#నిర్వచితం_కాకపోతే GL_AMD_performance_monitor
#నిర్వచించు GL_AMD_performance_monitor 1
#నిర్వచించు GL_COUNTER_TYPE_AMD               0x8BC0
#నిర్వచించు GL_COUNTER_RANGE_AMD              0x8BC1
#నిర్వచించు GL_UNSIGNED_INT64_AMD             0x8BC2
#నిర్వచించు GL_PERCENTAGE_AMD                 0x8BC3
#నిర్వచించు GL_PERFMON_ఫలితం_అందుబాటు_AMD   0x8BC4
#నిర్వచించు GL_PERFMON_ఫలితం_కొలత_AMD        0x8BC5
#నిర్వచించు GL_PERFMON_ఫలితం_AMD             0x8BC6
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETPERFMONITORGROUPSAMDPROC) (GLint *అంకె_Groups, GLsizei groups_కొలత, GLuint *groups);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETPERFMONITORCOUNTERSAMDPROC) (GLuint సమూహం, GLint *అంకె_Counters, GLint *max_చురుకైన_Counters, GLsizei counter_కొలత, GLuint *counters);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETPERFMONITORGROUPSTRINGAMDPROC) (GLuint సమూహం, GLsizei buf_కొలత, GLsizei *నిడివి, GLchar *సమూహం_String);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC) (GLuint సమూహం, GLuint counter, GLsizei buf_కొలత, GLsizei *నిడివి, GLchar *counterString);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETPERFMONITORCOUNTERINFOAMDPROC) (GLuint సమూహం, GLuint counter, GLenum pname, శూన్య *దత్తాంశం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGENPERFMONITORSAMDPROC) (GLsizei n, GLuint *monitors);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDELETEPERFMONITORSAMDPROC) (GLsizei n, GLuint *monitors);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSELECTPERFMONITORCOUNTERSAMDPROC) (GLuint monitor, GLboolean enable, GLuint సమూహం, GLint అంకె_Counters, GLuint *counterList);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBEGINPERFMONITORAMDPROC) (GLuint monitor);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLENDPERFMONITORAMDPROC) (GLuint monitor);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETPERFMONITORCOUNTERDATAAMDPROC) (GLuint monitor, GLenum pname, GLsizei దత్తాంశం_కొలత_2, GLuint *దత్తాంశం, GLint *బైట్లు_Written);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glGetPerfMonitorGroupsAMD (GLint *అంకె_Groups, GLsizei groups_కొలత, GLuint *groups);
GL_APICALL శూన్య GL_APIENTRY glGetPerfMonitorCountersAMD (GLuint సమూహం, GLint *అంకె_Counters, GLint *max_చురుకైన_Counters, GLsizei counter_కొలత, GLuint *counters);
GL_APICALL శూన్య GL_APIENTRY gl_Get_Perf_Monitor_సమూహం_String_AMD (GLuint సమూహం, GLsizei buf_కొలత, GLsizei *నిడివి, GLchar *సమూహం_String);
GL_APICALL శూన్య GL_APIENTRY glGetPerfMonitorCounterStringAMD (GLuint సమూహం, GLuint counter, GLsizei buf_కొలత, GLsizei *నిడివి, GLchar *counterString);
GL_APICALL శూన్య GL_APIENTRY glGetPerfMonitorCounterInfoAMD (GLuint సమూహం, GLuint counter, GLenum pname, శూన్య *దత్తాంశం);
GL_APICALL శూన్య GL_APIENTRY glGenPerfMonitorsAMD (GLsizei n, GLuint *monitors);
GL_APICALL శూన్య GL_APIENTRY glDeletePerfMonitorsAMD (GLsizei n, GLuint *monitors);
GL_APICALL శూన్య GL_APIENTRY glSelectPerfMonitorCountersAMD (GLuint monitor, GLboolean enable, GLuint సమూహం, GLint అంకె_Counters, GLuint *counterList);
GL_APICALL శూన్య GL_APIENTRY glBeginPerfMonitorAMD (GLuint monitor);
GL_APICALL శూన్య GL_APIENTRY gl_చివర_Perf_Monitor_AMD (GLuint monitor);
GL_APICALL శూన్య GL_APIENTRY gl_Get_Perf_Monitor_Counter_దత్తాంశం_AMD (GLuint monitor, GLenum pname, GLsizei దత్తాంశం_కొలత_2, GLuint *దత్తాంశం, GLint *బైట్లు_Written);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_AMD_performance_monitor */

#నిర్వచితం_కాకపోతే GL_AMD_కార్యక్రమం_ద్విమాన_Z400
#నిర్వచించు GL_AMD_కార్యక్రమం_ద్విమాన_Z400 1
#నిర్వచించు GL_Z400_ద్విమాన_AMD                0x8740
#అయితే_ముగింపు /* GL_AMD_program_binary_Z400 */

#నిర్వచితం_కాకపోతే GL_ANDROID_extension_pack_es31a
#నిర్వచించు GL_ANDROID_extension_pack_es31a 1
#అయితే_ముగింపు /* GL_ANDROID_extension_pack_es31a */

#నిర్వచితం_కాకపోతే GL_ANGLE_లోతు_texture
#నిర్వచించు GL_ANGLE_లోతు_texture 1
#అయితే_ముగింపు /* GL_ANGLE_depth_texture */

#నిర్వచితం_కాకపోతే GL_ANGLE_framebuffer_blit
#నిర్వచించు GL_ANGLE_framebuffer_blit 1
#నిర్వచించు GL_READ_FRAMEBUFFER_ANGLE         0x8CA8
#నిర్వచించు GL_DRAW_FRAMEBUFFER_ANGLE         0x8CA9
#నిర్వచించు GL_DRAW_FRAMEBUFFER_BINDING_ANGLE 0x8CA6
#నిర్వచించు GL_READ_FRAMEBUFFER_BINDING_ANGLE 0x8CAA
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBLITFRAMEBUFFERANGLEPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield ముసుగు, GLenum filter);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glBlitFramebufferANGLE (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield ముసుగు, GLenum filter);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_ANGLE_framebuffer_blit */

#నిర్వచితం_కాకపోతే GL_ANGLE_framebuffer_multisample
#నిర్వచించు GL_ANGLE_framebuffer_multisample 1
#నిర్వచించు GL_RENDERBUFFER_SAMPLES_ANGLE     0x8CAB
#నిర్వచించు GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_ANGLE 0x8D56
#నిర్వచించు GL_MAX_SAMPLES_ANGLE              0x8D57
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEANGLEPROC) (GLenum లక్ష్యం, GLsizei samples, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glRenderbufferStorageMultisampleANGLE (GLenum లక్ష్యం, GLsizei samples, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_ANGLE_framebuffer_multisample */

#నిర్వచితం_కాకపోతే GL_ANGLE_instanced_arrays
#నిర్వచించు GL_ANGLE_instanced_arrays 1
#నిర్వచించు GL_శీర్షం_ATTRIB_ARRAY_భాజకం_ANGLE 0x88FE
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDANGLEPROC) (GLenum బహుళకం, GLint మొదటి, GLsizei లెక్క, GLsizei primcount);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDANGLEPROC) (GLenum బహుళకం, GLsizei లెక్క, GLenum type, స్థిరరాశి శూన్య *indices, GLsizei primcount);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLVERTEXATTRIBDIVISORANGLEPROC) (GLuint సూచీ, GLuint భాజకం);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glDrawArraysInstancedANGLE (GLenum బహుళకం, GLint మొదటి, GLsizei లెక్క, GLsizei primcount);
GL_APICALL శూన్య GL_APIENTRY glDrawElementsInstancedANGLE (GLenum బహుళకం, GLsizei లెక్క, GLenum type, స్థిరరాశి శూన్య *indices, GLsizei primcount);
GL_APICALL శూన్య GL_APIENTRY gl_శీర్షం_Attrib_భాజకం_ANGLE (GLuint సూచీ, GLuint భాజకం);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_ANGLE_instanced_arrays */

#నిర్వచితం_కాకపోతే GL_ANGLE_pack_తిరగేయి_అడ్డువరుస_క్రమం
#నిర్వచించు GL_ANGLE_pack_తిరగేయి_అడ్డువరుస_క్రమం 1
#నిర్వచించు GL_PACK_తిరగేయి_అడ్డువరుస_క్రమం_ANGLE   0x93A4
#అయితే_ముగింపు /* GL_ANGLE_pack_reverse_row_order */

#నిర్వచితం_కాకపోతే GL_ANGLE_కార్యక్రమం_ద్విమాన
#నిర్వచించు GL_ANGLE_కార్యక్రమం_ద్విమాన 1
#నిర్వచించు GL_కార్యక్రమం_ద్విమాన_ANGLE           0x93A6
#అయితే_ముగింపు /* GL_ANGLE_program_binary */

#నిర్వచితం_కాకపోతే GL_ANGLE_texture_compression_dxt3
#నిర్వచించు GL_ANGLE_texture_compression_dxt3 1
#నిర్వచించు GL_COMPRESSED_RGBA_S3TC_DXT3_ANGLE 0x83F2
#అయితే_ముగింపు /* GL_ANGLE_texture_compression_dxt3 */

#నిర్వచితం_కాకపోతే GL_ANGLE_texture_compression_dxt5
#నిర్వచించు GL_ANGLE_texture_compression_dxt5 1
#నిర్వచించు GL_COMPRESSED_RGBA_S3TC_DXT5_ANGLE 0x83F3
#అయితే_ముగింపు /* GL_ANGLE_texture_compression_dxt5 */

#నిర్వచితం_కాకపోతే GL_ANGLE_texture_usage
#నిర్వచించు GL_ANGLE_texture_usage 1
#నిర్వచించు GL_TEXTURE_USAGE_ANGLE            0x93A2
#నిర్వచించు GL_FRAMEBUFFER_ATTACHMENT_ANGLE   0x93A3
#అయితే_ముగింపు /* GL_ANGLE_texture_usage */

#నిర్వచితం_కాకపోతే GL_ANGLE_translated_shader_ఆధారం
#నిర్వచించు GL_ANGLE_translated_shader_ఆధారం 1
#నిర్వచించు GL_TRANSLATED_SHADER_ఆధారం_నిడివి_ANGLE 0x93A0
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETTRANSLATEDSHADERSOURCEANGLEPROC) (GLuint shader, GLsizei buf_కొలత, GLsizei *నిడివి, GLchar *ఆధారం);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_Get_Translated_Shader_ఆధారం_ANGLE (GLuint shader, GLsizei buf_కొలత, GLsizei *నిడివి, GLchar *ఆధారం);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_ANGLE_translated_shader_source */

#నిర్వచితం_కాకపోతే GL_APPLE_clip_దూరం
#నిర్వచించు GL_APPLE_clip_దూరం 1
#నిర్వచించు GL_MAX_CLIP_DISTANCES_APPLE       0x0D32
#నిర్వచించు GL_CLIP_DISTANCE0_APPLE           0x3000
#నిర్వచించు GL_CLIP_DISTANCE1_APPLE           0x3001
#నిర్వచించు GL_CLIP_DISTANCE2_APPLE           0x3002
#నిర్వచించు GL_CLIP_DISTANCE3_APPLE           0x3003
#నిర్వచించు GL_CLIP_DISTANCE4_APPLE           0x3004
#నిర్వచించు GL_CLIP_DISTANCE5_APPLE           0x3005
#నిర్వచించు GL_CLIP_DISTANCE6_APPLE           0x3006
#నిర్వచించు GL_CLIP_DISTANCE7_APPLE           0x3007
#అయితే_ముగింపు /* GL_APPLE_clip_distance */

#నిర్వచితం_కాకపోతే GL_APPLE_color_బఫరు_packed_float
#నిర్వచించు GL_APPLE_color_బఫరు_packed_float 1
#అయితే_ముగింపు /* GL_APPLE_color_buffer_packed_float */

#నిర్వచితం_కాకపోతే GL_APPLE_copy_texture_స్థాయిలు
#నిర్వచించు GL_APPLE_copy_texture_స్థాయిలు 1
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCOPYTEXTURELEVELSAPPLEPROC) (GLuint destinationTexture, GLuint ఆధారం_Texture, GLint ఆధారం_పునాది_Level, GLsizei ఆధారం_Level_లెక్క);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_Copy_Texture_స్థాయిలు_APPLE (GLuint destinationTexture, GLuint ఆధారం_Texture, GLint ఆధారం_పునాది_Level, GLsizei ఆధారం_Level_లెక్క);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_APPLE_copy_texture_levels */

#నిర్వచితం_కాకపోతే GL_APPLE_framebuffer_multisample
#నిర్వచించు GL_APPLE_framebuffer_multisample 1
#నిర్వచించు GL_RENDERBUFFER_SAMPLES_APPLE     0x8CAB
#నిర్వచించు GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_APPLE 0x8D56
#నిర్వచించు GL_MAX_SAMPLES_APPLE              0x8D57
#నిర్వచించు GL_READ_FRAMEBUFFER_APPLE         0x8CA8
#నిర్వచించు GL_DRAW_FRAMEBUFFER_APPLE         0x8CA9
#నిర్వచించు GL_DRAW_FRAMEBUFFER_BINDING_APPLE 0x8CA6
#నిర్వచించు GL_READ_FRAMEBUFFER_BINDING_APPLE 0x8CAA
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEAPPLEPROC) (GLenum లక్ష్యం, GLsizei samples, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLRESOLVEMULTISAMPLEFRAMEBUFFERAPPLEPROC) (శూన్య);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glRenderbufferStorageMultisampleAPPLE (GLenum లక్ష్యం, GLsizei samples, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
GL_APICALL శూన్య GL_APIENTRY glResolveMultisampleFramebufferAPPLE (శూన్య);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_APPLE_framebuffer_multisample */

#నిర్వచితం_కాకపోతే GL_APPLE_rgb_422
#నిర్వచించు GL_APPLE_rgb_422 1
#నిర్వచించు GL_RGB_422_APPLE                  0x8A1F
#నిర్వచించు GL_UNSIGNED_SHORT_8_8_APPLE       0x85BA
#నిర్వచించు GL_UNSIGNED_SHORT_8_8_REV_APPLE   0x85BB
#నిర్వచించు GL_RGB_RAW_422_APPLE              0x8A51
#అయితే_ముగింపు /* GL_APPLE_rgb_422 */

#నిర్వచితం_కాకపోతే GL_APPLE_sync
#నిర్వచించు GL_APPLE_sync 1
#నిర్వచించు GL_SYNC_OBJECT_APPLE              0x8A53
#నిర్వచించు GL_MAX_SERVER_WAIT_TIMEOUT_APPLE  0x9111
#నిర్వచించు GL_OBJECT_TYPE_APPLE              0x9112
#నిర్వచించు GL_SYNC_CONDITION_APPLE           0x9113
#నిర్వచించు GL_SYNC_స్థితి_APPLE              0x9114
#నిర్వచించు GL_SYNC_FLAGS_APPLE               0x9115
#నిర్వచించు GL_SYNC_FENCE_APPLE               0x9116
#నిర్వచించు GL_SYNC_GPU_COMMANDS_COMPLETE_APPLE 0x9117
#నిర్వచించు GL_UNSIGNALED_APPLE               0x9118
#నిర్వచించు GL_SIGNALED_APPLE                 0x9119
#నిర్వచించు GL_ALREADY_SIGNALED_APPLE         0x911A
#నిర్వచించు GL_TIMEOUT_EXPIRED_APPLE          0x911B
#నిర్వచించు GL_CONDITION_SATISFIED_APPLE      0x911C
#నిర్వచించు GL_WAIT_FAILED_APPLE              0x911D
#నిర్వచించు GL_SYNC_FLUSH_COMMANDS_బిట్టు_APPLE  0x00000001
#నిర్వచించు GL_TIMEOUT_IGNORED_APPLE          0xFFFFFFFFFFFFFFFFull
రకనిర్వచనం GLsync (GL_APIENTRYP PFNGLFENCESYNCAPPLEPROC) (GLenum condition, GLbitfield flags);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLISSYNCAPPLEPROC) (GLsync sync);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDELETESYNCAPPLEPROC) (GLsync sync);
రకనిర్వచనం GLenum (GL_APIENTRYP PFNGLCLIENTWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETINTEGER64VAPPLEPROC) (GLenum pname, GLint64 *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETSYNCIVAPPLEPROC) (GLsync sync, GLenum pname, GLsizei లెక్క, GLsizei *నిడివి, GLint *విలువలు);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL GLsync GL_APIENTRY glFenceSyncAPPLE (GLenum condition, GLbitfield flags);
GL_APICALL GLboolean GL_APIENTRY glIsSyncAPPLE (GLsync sync);
GL_APICALL శూన్య GL_APIENTRY glDeleteSyncAPPLE (GLsync sync);
GL_APICALL GLenum GL_APIENTRY glClientWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_APICALL శూన్య GL_APIENTRY glWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_APICALL శూన్య GL_APIENTRY glGetInteger64vAPPLE (GLenum pname, GLint64 *params);
GL_APICALL శూన్య GL_APIENTRY glGetSyncivAPPLE (GLsync sync, GLenum pname, GLsizei లెక్క, GLsizei *నిడివి, GLint *విలువలు);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_APPLE_sync */

#నిర్వచితం_కాకపోతే GL_APPLE_texture_format_BGRA8888
#నిర్వచించు GL_APPLE_texture_format_BGRA8888 1
#నిర్వచించు GL_BGRA_EXT                       0x80E1
#నిర్వచించు GL_BGRA8_EXT                      0x93A1
#అయితే_ముగింపు /* GL_APPLE_texture_format_BGRA8888 */

#నిర్వచితం_కాకపోతే GL_APPLE_texture_max_level
#నిర్వచించు GL_APPLE_texture_max_level 1
#నిర్వచించు GL_TEXTURE_MAX_LEVEL_APPLE        0x813D
#అయితే_ముగింపు /* GL_APPLE_texture_max_level */

#నిర్వచితం_కాకపోతే GL_APPLE_texture_packed_float
#నిర్వచించు GL_APPLE_texture_packed_float 1
#నిర్వచించు GL_UNSIGNED_INT_10F_11F_11F_REV_APPLE 0x8C3B
#నిర్వచించు GL_UNSIGNED_INT_5_9_9_9_REV_APPLE 0x8C3E
#నిర్వచించు GL_R11F_G11F_B10F_APPLE           0x8C3A
#నిర్వచించు GL_RGB9_E5_APPLE                  0x8C3D
#అయితే_ముగింపు /* GL_APPLE_texture_packed_float */

#నిర్వచితం_కాకపోతే GL_ARM_mali_కార్యక్రమం_ద్విమాన
#నిర్వచించు GL_ARM_mali_కార్యక్రమం_ద్విమాన 1
#నిర్వచించు GL_MALI_కార్యక్రమం_ద్విమాన_ARM        0x8F61
#అయితే_ముగింపు /* GL_ARM_mali_program_binary */

#నిర్వచితం_కాకపోతే GL_ARM_mali_shader_ద్విమాన
#నిర్వచించు GL_ARM_mali_shader_ద్విమాన 1
#నిర్వచించు GL_MALI_SHADER_ద్విమాన_ARM         0x8F60
#అయితే_ముగింపు /* GL_ARM_mali_shader_binary */

#నిర్వచితం_కాకపోతే GL_ARM_rgba8
#నిర్వచించు GL_ARM_rgba8 1
#అయితే_ముగింపు /* GL_ARM_rgba8 */

#నిర్వచితం_కాకపోతే GL_ARM_shader_core_properties
#నిర్వచించు GL_ARM_shader_core_properties 1
#నిర్వచించు GL_SHADER_CORE_లెక్క_ARM          0x96F0
#నిర్వచించు GL_SHADER_CORE_చురుకైన_లెక్క_ARM   0x96F1
#నిర్వచించు GL_SHADER_CORE_PRESENT_ముసుగు_ARM   0x96F2
#నిర్వచించు GL_SHADER_CORE_MAX_WARP_లెక్క_ARM 0x96F3
#నిర్వచించు GL_SHADER_CORE_PIXEL_రేటు_ARM     0x96F4
#నిర్వచించు GL_SHADER_CORE_TEXEL_రేటు_ARM     0x96F5
#నిర్వచించు GL_SHADER_CORE_FMA_రేటు_ARM       0x96F6
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMAXACTIVESHADERCORESARMPROC) (GLuint లెక్క);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_Max_చురుకైన_Shader_Cores_ARM (GLuint లెక్క);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_ARM_shader_core_properties */

#నిర్వచితం_కాకపోతే GL_ARM_shader_framebuffer_fetch
#నిర్వచించు GL_ARM_shader_framebuffer_fetch 1
#నిర్వచించు GL_FETCH_చొప్పున_SAMPLE_ARM           0x8F65
#నిర్వచించు GL_FRAGMENT_SHADER_FRAMEBUFFER_FETCH_MRT_ARM 0x8F66
#అయితే_ముగింపు /* GL_ARM_shader_framebuffer_fetch */

#నిర్వచితం_కాకపోతే GL_ARM_shader_framebuffer_fetch_లోతు_stencil
#నిర్వచించు GL_ARM_shader_framebuffer_fetch_లోతు_stencil 1
#అయితే_ముగింపు /* GL_ARM_shader_framebuffer_fetch_depth_stencil */

#నిర్వచితం_కాకపోతే GL_ARM_texture_unnormalized_coordinates
#నిర్వచించు GL_ARM_texture_unnormalized_coordinates 1
#నిర్వచించు GL_TEXTURE_UNNORMALIZED_COORDINATES_ARM 0x8F6A
#అయితే_ముగింపు /* GL_ARM_texture_unnormalized_coordinates */

#నిర్వచితం_కాకపోతే GL_DMP_కార్యక్రమం_ద్విమాన
#నిర్వచించు GL_DMP_కార్యక్రమం_ద్విమాన 1
#నిర్వచించు GL_SMAPHS30_కార్యక్రమం_ద్విమాన_DMP    0x9251
#నిర్వచించు GL_SMAPHS_కార్యక్రమం_ద్విమాన_DMP      0x9252
#నిర్వచించు GL_DMP_కార్యక్రమం_ద్విమాన_DMP         0x9253
#అయితే_ముగింపు /* GL_DMP_program_binary */

#నిర్వచితం_కాకపోతే GL_DMP_shader_ద్విమాన
#నిర్వచించు GL_DMP_shader_ద్విమాన 1
#నిర్వచించు GL_SHADER_ద్విమాన_DMP              0x9250
#అయితే_ముగింపు /* GL_DMP_shader_binary */

#నిర్వచితం_కాకపోతే GL_EXT_EGL_image_array
#నిర్వచించు GL_EXT_EGL_image_array 1
#అయితే_ముగింపు /* GL_EXT_EGL_image_array */

#నిర్వచితం_కాకపోతే GL_EXT_EGL_image_storage
#నిర్వచించు GL_EXT_EGL_image_storage 1
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLEGLIMAGETARGETTEXSTORAGEEXTPROC) (GLenum లక్ష్యం, GLeglImageOES image, స్థిరరాశి GLint* attrib_list);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLEGLIMAGETARGETTEXTURESTORAGEEXTPROC) (GLuint texture, GLeglImageOES image, స్థిరరాశి GLint* attrib_list);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_EGLImage_లక్ష్యం_Tex_Storage_EXT (GLenum లక్ష్యం, GLeglImageOES image, స్థిరరాశి GLint* attrib_list);
GL_APICALL శూన్య GL_APIENTRY gl_EGLImage_లక్ష్యం_Texture_Storage_EXT (GLuint texture, GLeglImageOES image, స్థిరరాశి GLint* attrib_list);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_EGL_image_storage */

#నిర్వచితం_కాకపోతే GL_EXT_EGL_image_storage_compression
#నిర్వచించు GL_EXT_EGL_image_storage_compression 1
#నిర్వచించు GL_SURFACE_COMPRESSION_EXT        0x96C0
#నిర్వచించు GL_SURFACE_COMPRESSION_FIXED_రేటు_NONE_EXT 0x96C1
#నిర్వచించు GL_SURFACE_COMPRESSION_FIXED_రేటు_DEFAULT_EXT 0x96C2
#అయితే_ముగింపు /* GL_EXT_EGL_image_storage_compression */

#నిర్వచితం_కాకపోతే GL_EXT_YUV_లక్ష్యం
#నిర్వచించు GL_EXT_YUV_లక్ష్యం 1
#నిర్వచించు GL_SAMPLER_EXTERNAL_2D_Y2Y_EXT    0x8BE7
#అయితే_ముగింపు /* GL_EXT_YUV_target */

#నిర్వచితం_కాకపోతే GL_EXT_పునాది_instance
#నిర్వచించు GL_EXT_పునాది_instance 1
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEEXTPROC) (GLenum బహుళకం, GLint మొదటి, GLsizei లెక్క, GLsizei instancecount, GLuint baseinstance);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEEXTPROC) (GLenum బహుళకం, GLsizei లెక్క, GLenum type, స్థిరరాశి శూన్య *indices, GLsizei instancecount, GLuint baseinstance);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEEXTPROC) (GLenum బహుళకం, GLsizei లెక్క, GLenum type, స్థిరరాశి శూన్య *indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_Draw_Arrays_Instanced_పునాది_Instance_EXT (GLenum బహుళకం, GLint మొదటి, GLsizei లెక్క, GLsizei instancecount, GLuint baseinstance);
GL_APICALL శూన్య GL_APIENTRY gl_Draw_Elements_Instanced_పునాది_Instance_EXT (GLenum బహుళకం, GLsizei లెక్క, GLenum type, స్థిరరాశి శూన్య *indices, GLsizei instancecount, GLuint baseinstance);
GL_APICALL శూన్య GL_APIENTRY gl_Draw_Elements_Instanced_పునాది_శీర్షం_పునాది_Instance_EXT (GLenum బహుళకం, GLsizei లెక్క, GLenum type, స్థిరరాశి శూన్య *indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_base_instance */

#నిర్వచితం_కాకపోతే GL_EXT_blend_func_extended
#నిర్వచించు GL_EXT_blend_func_extended 1
#నిర్వచించు GL_SRC1_COLOR_EXT                 0x88F9
#నిర్వచించు GL_SRC1_ALPHA_EXT                 0x8589
#నిర్వచించు GL_ONE_MINUS_SRC1_COLOR_EXT       0x88FA
#నిర్వచించు GL_ONE_MINUS_SRC1_ALPHA_EXT       0x88FB
#నిర్వచించు GL_SRC_ALPHA_SATURATE_EXT         0x0308
#నిర్వచించు GL_LOCATION_సూచీ_EXT             0x930F
#నిర్వచించు GL_MAX_DUAL_ఆధారం_DRAW_BUFFERS_EXT 0x88FC
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBINDFRAGDATALOCATIONINDEXEDEXTPROC) (GLuint కార్యక్రమం, GLuint color_సంఖ్య, GLuint సూచీ, స్థిరరాశి GLchar *name);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBINDFRAGDATALOCATIONEXTPROC) (GLuint కార్యక్రమం, GLuint color, స్థిరరాశి GLchar *name);
రకనిర్వచనం GLint (GL_APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONINDEXEXTPROC) (GLuint కార్యక్రమం, GLenum కార్యక్రమం_Interface, స్థిరరాశి GLchar *name);
రకనిర్వచనం GLint (GL_APIENTRYP PFNGLGETFRAGDATAINDEXEXTPROC) (GLuint కార్యక్రమం, స్థిరరాశి GLchar *name);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_Bind_Frag_దత్తాంశం_Location_సూచీకృత_EXT (GLuint కార్యక్రమం, GLuint color_సంఖ్య, GLuint సూచీ, స్థిరరాశి GLchar *name);
GL_APICALL శూన్య GL_APIENTRY gl_Bind_Frag_దత్తాంశం_Location_EXT (GLuint కార్యక్రమం, GLuint color, స్థిరరాశి GLchar *name);
GL_APICALL GLint GL_APIENTRY gl_Get_కార్యక్రమం_Resource_Location_సూచీ_EXT (GLuint కార్యక్రమం, GLenum కార్యక్రమం_Interface, స్థిరరాశి GLchar *name);
GL_APICALL GLint GL_APIENTRY gl_Get_Frag_దత్తాంశం_సూచీ_EXT (GLuint కార్యక్రమం, స్థిరరాశి GLchar *name);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_blend_func_extended */

#నిర్వచితం_కాకపోతే GL_EXT_blend_minmax
#నిర్వచించు GL_EXT_blend_minmax 1
#నిర్వచించు GL_MIN_EXT                        0x8007
#నిర్వచించు GL_MAX_EXT                        0x8008
#అయితే_ముగింపు /* GL_EXT_blend_minmax */

#నిర్వచితం_కాకపోతే GL_EXT_బఫరు_storage
#నిర్వచించు GL_EXT_బఫరు_storage 1
#నిర్వచించు GL_MAP_READ_బిట్టు                   0x0001
#నిర్వచించు GL_MAP_WRITE_బిట్టు                  0x0002
#నిర్వచించు GL_MAP_PERSISTENT_బిట్టు_EXT         0x0040
#నిర్వచించు GL_MAP_COHERENT_బిట్టు_EXT           0x0080
#నిర్వచించు GL_DYNAMIC_STORAGE_బిట్టు_EXT        0x0100
#నిర్వచించు GL_CLIENT_STORAGE_బిట్టు_EXT         0x0200
#నిర్వచించు GL_CLIENT_MAPPED_బఫరు_BARRIER_బిట్టు_EXT 0x00004000
#నిర్వచించు GL_బఫరు_IMMUTABLE_STORAGE_EXT   0x821F
#నిర్వచించు GL_బఫరు_STORAGE_FLAGS_EXT       0x8220
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBUFFERSTORAGEEXTPROC) (GLenum లక్ష్యం, GLsizeiptr కొలత, స్థిరరాశి శూన్య *దత్తాంశం, GLbitfield flags);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_బఫరు_Storage_EXT (GLenum లక్ష్యం, GLsizeiptr కొలత, స్థిరరాశి శూన్య *దత్తాంశం, GLbitfield flags);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_buffer_storage */

#నిర్వచితం_కాకపోతే GL_EXT_clear_texture
#నిర్వచించు GL_EXT_clear_texture 1
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCLEARTEXIMAGEEXTPROC) (GLuint texture, GLint level, GLenum format, GLenum type, స్థిరరాశి శూన్య *దత్తాంశం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCLEARTEXSUBIMAGEEXTPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLenum format, GLenum type, స్థిరరాశి శూన్య *దత్తాంశం);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glClearTexImageEXT (GLuint texture, GLint level, GLenum format, GLenum type, స్థిరరాశి శూన్య *దత్తాంశం);
GL_APICALL శూన్య GL_APIENTRY glClearTexSubImageEXT (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLenum format, GLenum type, స్థిరరాశి శూన్య *దత్తాంశం);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_clear_texture */

#నిర్వచితం_కాకపోతే GL_EXT_clip_control
#నిర్వచించు GL_EXT_clip_control 1
#నిర్వచించు GL_క్రింది_ఎడమ_EXT                 0x8CA1
#నిర్వచించు GL_పై_ఎడమ_EXT                 0x8CA2
#నిర్వచించు GL_NEGATIVE_ONE_గమ్యం_ONE_EXT        0x935E
#నిర్వచించు GL_ZERO_గమ్యం_ONE_EXT                0x935F
#నిర్వచించు GL_CLIP_ORIGIN_EXT                0x935C
#నిర్వచించు GL_CLIP_లోతు_బహుళకం_EXT            0x935D
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCLIPCONTROLEXTPROC) (GLenum origin, GLenum లోతు_2);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glClipControlEXT (GLenum origin, GLenum లోతు_2);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_clip_control */

#నిర్వచితం_కాకపోతే GL_EXT_clip_cull_దూరం
#నిర్వచించు GL_EXT_clip_cull_దూరం 1
#నిర్వచించు GL_MAX_CLIP_DISTANCES_EXT         0x0D32
#నిర్వచించు GL_MAX_CULL_DISTANCES_EXT         0x82F9
#నిర్వచించు GL_MAX_COMBINED_CLIP_AND_CULL_DISTANCES_EXT 0x82FA
#నిర్వచించు GL_CLIP_DISTANCE0_EXT             0x3000
#నిర్వచించు GL_CLIP_DISTANCE1_EXT             0x3001
#నిర్వచించు GL_CLIP_DISTANCE2_EXT             0x3002
#నిర్వచించు GL_CLIP_DISTANCE3_EXT             0x3003
#నిర్వచించు GL_CLIP_DISTANCE4_EXT             0x3004
#నిర్వచించు GL_CLIP_DISTANCE5_EXT             0x3005
#నిర్వచించు GL_CLIP_DISTANCE6_EXT             0x3006
#నిర్వచించు GL_CLIP_DISTANCE7_EXT             0x3007
#అయితే_ముగింపు /* GL_EXT_clip_cull_distance */

#నిర్వచితం_కాకపోతే GL_EXT_color_బఫరు_float
#నిర్వచించు GL_EXT_color_బఫరు_float 1
#అయితే_ముగింపు /* GL_EXT_color_buffer_float */

#నిర్వచితం_కాకపోతే GL_EXT_color_బఫరు_half_float
#నిర్వచించు GL_EXT_color_బఫరు_half_float 1
#నిర్వచించు GL_RGBA16F_EXT                    0x881A
#నిర్వచించు GL_RGB16F_EXT                     0x881B
#నిర్వచించు GL_RG16F_EXT                      0x822F
#నిర్వచించు GL_R16F_EXT                       0x822D
#నిర్వచించు GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE_EXT 0x8211
#నిర్వచించు GL_UNSIGNED_NORMALIZED_EXT        0x8C17
#అయితే_ముగింపు /* GL_EXT_color_buffer_half_float */

#నిర్వచితం_కాకపోతే GL_EXT_conservative_లోతు
#నిర్వచించు GL_EXT_conservative_లోతు 1
#అయితే_ముగింపు /* GL_EXT_conservative_depth */

#నిర్వచితం_కాకపోతే GL_EXT_copy_image
#నిర్వచించు GL_EXT_copy_image 1
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCOPYIMAGESUBDATAEXTPROC) (GLuint srcName, GLenum src_లక్ష్యం, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dst_లక్ష్యం, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei src_వెడల్పు, GLsizei src_ఎత్తు, GLsizei src_లోతు);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_Copy_Image_Sub_దత్తాంశం_EXT (GLuint srcName, GLenum src_లక్ష్యం, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dst_లక్ష్యం, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei src_వెడల్పు, GLsizei src_ఎత్తు, GLsizei src_లోతు);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_copy_image */

#నిర్వచితం_కాకపోతే GL_EXT_debug_label
#నిర్వచించు GL_EXT_debug_label 1
#నిర్వచించు GL_కార్యక్రమం_PIPELINE_OBJECT_EXT    0x8A4F
#నిర్వచించు GL_కార్యక్రమం_OBJECT_EXT             0x8B40
#నిర్వచించు GL_SHADER_OBJECT_EXT              0x8B48
#నిర్వచించు GL_బఫరు_OBJECT_EXT              0x9151
#నిర్వచించు GL_QUERY_OBJECT_EXT               0x9153
#నిర్వచించు GL_శీర్షం_ARRAY_OBJECT_EXT        0x9154
#నిర్వచించు GL_TRANSFORM_FEEDBACK             0x8E22
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLLABELOBJECTEXTPROC) (GLenum type, GLuint object, GLsizei నిడివి, స్థిరరాశి GLchar *label);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETOBJECTLABELEXTPROC) (GLenum type, GLuint object, GLsizei buf_కొలత, GLsizei *నిడివి, GLchar *label);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glLabelObjectEXT (GLenum type, GLuint object, GLsizei నిడివి, స్థిరరాశి GLchar *label);
GL_APICALL శూన్య GL_APIENTRY glGetObjectLabelEXT (GLenum type, GLuint object, GLsizei buf_కొలత, GLsizei *నిడివి, GLchar *label);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_debug_label */

#నిర్వచితం_కాకపోతే GL_EXT_debug_marker
#నిర్వచించు GL_EXT_debug_marker 1
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLINSERTEVENTMARKEREXTPROC) (GLsizei నిడివి, స్థిరరాశి GLchar *marker);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPUSHGROUPMARKEREXTPROC) (GLsizei నిడివి, స్థిరరాశి GLchar *marker);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPOPGROUPMARKEREXTPROC) (శూన్య);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_చొప్పించు_Event_Marker_EXT (GLsizei నిడివి, స్థిరరాశి GLchar *marker);
GL_APICALL శూన్య GL_APIENTRY gl_నెట్టు_సమూహం_Marker_EXT (GLsizei నిడివి, స్థిరరాశి GLchar *marker);
GL_APICALL శూన్య GL_APIENTRY gl_తీయి_సమూహం_Marker_EXT (శూన్య);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_debug_marker */

#నిర్వచితం_కాకపోతే GL_EXT_లోతు_clamp
#నిర్వచించు GL_EXT_లోతు_clamp 1
#నిర్వచించు GL_లోతు_CLAMP_EXT                0x864F
#అయితే_ముగింపు /* GL_EXT_depth_clamp */

#నిర్వచితం_కాకపోతే GL_EXT_discard_framebuffer
#నిర్వచించు GL_EXT_discard_framebuffer 1
#నిర్వచించు GL_COLOR_EXT                      0x1800
#నిర్వచించు GL_లోతు_EXT                      0x1801
#నిర్వచించు GL_STENCIL_EXT                    0x1802
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDISCARDFRAMEBUFFEREXTPROC) (GLenum లక్ష్యం, GLsizei అంకె_Attachments, స్థిరరాశి GLenum *attachments);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glDiscardFramebufferEXT (GLenum లక్ష్యం, GLsizei అంకె_Attachments, స్థిరరాశి GLenum *attachments);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_discard_framebuffer */

#నిర్వచితం_కాకపోతే GL_EXT_disjoint_timer_query
#నిర్వచించు GL_EXT_disjoint_timer_query 1
#నిర్వచించు GL_QUERY_COUNTER_బిట్లు_EXT         0x8864
#నిర్వచించు GL_CURRENT_QUERY_EXT              0x8865
#నిర్వచించు GL_QUERY_ఫలితం_EXT               0x8866
#నిర్వచించు GL_QUERY_ఫలితం_అందుబాటు_EXT     0x8867
#నిర్వచించు GL_సమయం_ELAPSED_EXT               0x88BF
#నిర్వచించు GL_TIMESTAMP_EXT                  0x8E28
#నిర్వచించు GL_GPU_DISJOINT_EXT               0x8FBB
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGENQUERIESEXTPROC) (GLsizei n, GLuint *ids);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDELETEQUERIESEXTPROC) (GLsizei n, స్థిరరాశి GLuint *ids);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLISQUERYEXTPROC) (GLuint id);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBEGINQUERYEXTPROC) (GLenum లక్ష్యం, GLuint id);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLENDQUERYEXTPROC) (GLenum లక్ష్యం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLQUERYCOUNTEREXTPROC) (GLuint id, GLenum లక్ష్యం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETQUERYIVEXTPROC) (GLenum లక్ష్యం, GLenum pname, GLint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETQUERYOBJECTIVEXTPROC) (GLuint id, GLenum pname, GLint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETQUERYOBJECTUIVEXTPROC) (GLuint id, GLenum pname, GLuint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETQUERYOBJECTI64VEXTPROC) (GLuint id, GLenum pname, GLint64 *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETQUERYOBJECTUI64VEXTPROC) (GLuint id, GLenum pname, GLuint64 *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETINTEGER64VEXTPROC) (GLenum pname, GLint64 *దత్తాంశం);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glGenQueriesEXT (GLsizei n, GLuint *ids);
GL_APICALL శూన్య GL_APIENTRY glDeleteQueriesEXT (GLsizei n, స్థిరరాశి GLuint *ids);
GL_APICALL GLboolean GL_APIENTRY glIsQueryEXT (GLuint id);
GL_APICALL శూన్య GL_APIENTRY glBeginQueryEXT (GLenum లక్ష్యం, GLuint id);
GL_APICALL శూన్య GL_APIENTRY gl_చివర_Query_EXT (GLenum లక్ష్యం);
GL_APICALL శూన్య GL_APIENTRY glQueryCounterEXT (GLuint id, GLenum లక్ష్యం);
GL_APICALL శూన్య GL_APIENTRY glGetQueryivEXT (GLenum లక్ష్యం, GLenum pname, GLint *params);
GL_APICALL శూన్య GL_APIENTRY glGetQueryObjectivEXT (GLuint id, GLenum pname, GLint *params);
GL_APICALL శూన్య GL_APIENTRY glGetQueryObjectuivEXT (GLuint id, GLenum pname, GLuint *params);
GL_APICALL శూన్య GL_APIENTRY glGetQueryObjecti64vEXT (GLuint id, GLenum pname, GLint64 *params);
GL_APICALL శూన్య GL_APIENTRY glGetQueryObjectui64vEXT (GLuint id, GLenum pname, GLuint64 *params);
GL_APICALL శూన్య GL_APIENTRY glGetInteger64vEXT (GLenum pname, GLint64 *దత్తాంశం);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_disjoint_timer_query */

#నిర్వచితం_కాకపోతే GL_EXT_draw_buffers
#నిర్వచించు GL_EXT_draw_buffers 1
#నిర్వచించు GL_MAX_COLOR_ATTACHMENTS_EXT      0x8CDF
#నిర్వచించు GL_MAX_DRAW_BUFFERS_EXT           0x8824
#నిర్వచించు GL_DRAW_BUFFER0_EXT               0x8825
#నిర్వచించు GL_DRAW_BUFFER1_EXT               0x8826
#నిర్వచించు GL_DRAW_BUFFER2_EXT               0x8827
#నిర్వచించు GL_DRAW_BUFFER3_EXT               0x8828
#నిర్వచించు GL_DRAW_BUFFER4_EXT               0x8829
#నిర్వచించు GL_DRAW_BUFFER5_EXT               0x882A
#నిర్వచించు GL_DRAW_BUFFER6_EXT               0x882B
#నిర్వచించు GL_DRAW_BUFFER7_EXT               0x882C
#నిర్వచించు GL_DRAW_BUFFER8_EXT               0x882D
#నిర్వచించు GL_DRAW_BUFFER9_EXT               0x882E
#నిర్వచించు GL_DRAW_BUFFER10_EXT              0x882F
#నిర్వచించు GL_DRAW_BUFFER11_EXT              0x8830
#నిర్వచించు GL_DRAW_BUFFER12_EXT              0x8831
#నిర్వచించు GL_DRAW_BUFFER13_EXT              0x8832
#నిర్వచించు GL_DRAW_BUFFER14_EXT              0x8833
#నిర్వచించు GL_DRAW_BUFFER15_EXT              0x8834
#నిర్వచించు GL_COLOR_ATTACHMENT0_EXT          0x8CE0
#నిర్వచించు GL_COLOR_ATTACHMENT1_EXT          0x8CE1
#నిర్వచించు GL_COLOR_ATTACHMENT2_EXT          0x8CE2
#నిర్వచించు GL_COLOR_ATTACHMENT3_EXT          0x8CE3
#నిర్వచించు GL_COLOR_ATTACHMENT4_EXT          0x8CE4
#నిర్వచించు GL_COLOR_ATTACHMENT5_EXT          0x8CE5
#నిర్వచించు GL_COLOR_ATTACHMENT6_EXT          0x8CE6
#నిర్వచించు GL_COLOR_ATTACHMENT7_EXT          0x8CE7
#నిర్వచించు GL_COLOR_ATTACHMENT8_EXT          0x8CE8
#నిర్వచించు GL_COLOR_ATTACHMENT9_EXT          0x8CE9
#నిర్వచించు GL_COLOR_ATTACHMENT10_EXT         0x8CEA
#నిర్వచించు GL_COLOR_ATTACHMENT11_EXT         0x8CEB
#నిర్వచించు GL_COLOR_ATTACHMENT12_EXT         0x8CEC
#నిర్వచించు GL_COLOR_ATTACHMENT13_EXT         0x8CED
#నిర్వచించు GL_COLOR_ATTACHMENT14_EXT         0x8CEE
#నిర్వచించు GL_COLOR_ATTACHMENT15_EXT         0x8CEF
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWBUFFERSEXTPROC) (GLsizei n, స్థిరరాశి GLenum *bufs);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glDrawBuffersEXT (GLsizei n, స్థిరరాశి GLenum *bufs);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_draw_buffers */

#నిర్వచితం_కాకపోతే GL_EXT_draw_buffers_సూచీకృత
#నిర్వచించు GL_EXT_draw_buffers_సూచీకృత 1
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLENABLEIEXTPROC) (GLenum లక్ష్యం, GLuint సూచీ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDISABLEIEXTPROC) (GLenum లక్ష్యం, GLuint సూచీ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBLENDEQUATIONIEXTPROC) (GLuint buf, GLenum బహుళకం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEIEXTPROC) (GLuint buf, GLenum బహుళకం_RGB, GLenum బహుళకం_Alpha);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBLENDFUNCIEXTPROC) (GLuint buf, GLenum src, GLenum dst);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEIEXTPROC) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCOLORMASKIEXTPROC) (GLuint సూచీ, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLISENABLEDIEXTPROC) (GLenum లక్ష్యం, GLuint సూచీ);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glEnableiEXT (GLenum లక్ష్యం, GLuint సూచీ);
GL_APICALL శూన్య GL_APIENTRY glDisableiEXT (GLenum లక్ష్యం, GLuint సూచీ);
GL_APICALL శూన్య GL_APIENTRY glBlendEquationiEXT (GLuint buf, GLenum బహుళకం);
GL_APICALL శూన్య GL_APIENTRY glBlendEquationSeparateiEXT (GLuint buf, GLenum బహుళకం_RGB, GLenum బహుళకం_Alpha);
GL_APICALL శూన్య GL_APIENTRY glBlendFunciEXT (GLuint buf, GLenum src, GLenum dst);
GL_APICALL శూన్య GL_APIENTRY glBlendFuncSeparateiEXT (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
GL_APICALL శూన్య GL_APIENTRY glColorMaskiEXT (GLuint సూచీ, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
GL_APICALL GLboolean GL_APIENTRY glIsEnablediEXT (GLenum లక్ష్యం, GLuint సూచీ);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_draw_buffers_indexed */

#నిర్వచితం_కాకపోతే GL_EXT_draw_elements_పునాది_శీర్షం
#నిర్వచించు GL_EXT_draw_elements_పునాది_శీర్షం 1
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWELEMENTSBASEVERTEXEXTPROC) (GLenum బహుళకం, GLsizei లెక్క, GLenum type, స్థిరరాశి శూన్య *indices, GLint basevertex);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWRANGEELEMENTSBASEVERTEXEXTPROC) (GLenum బహుళకం, GLuint ప్రారంభం, GLuint చివర, GLsizei లెక్క, GLenum type, స్థిరరాశి శూన్య *indices, GLint basevertex);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXEXTPROC) (GLenum బహుళకం, GLsizei లెక్క, GLenum type, స్థిరరాశి శూన్య *indices, GLsizei instancecount, GLint basevertex);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_Draw_Elements_పునాది_శీర్షం_EXT (GLenum బహుళకం, GLsizei లెక్క, GLenum type, స్థిరరాశి శూన్య *indices, GLint basevertex);
GL_APICALL శూన్య GL_APIENTRY gl_Draw_Range_Elements_పునాది_శీర్షం_EXT (GLenum బహుళకం, GLuint ప్రారంభం, GLuint చివర, GLsizei లెక్క, GLenum type, స్థిరరాశి శూన్య *indices, GLint basevertex);
GL_APICALL శూన్య GL_APIENTRY gl_Draw_Elements_Instanced_పునాది_శీర్షం_EXT (GLenum బహుళకం, GLsizei లెక్క, GLenum type, స్థిరరాశి శూన్య *indices, GLsizei instancecount, GLint basevertex);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_draw_elements_base_vertex */

#నిర్వచితం_కాకపోతే GL_EXT_draw_instanced
#నిర్వచించు GL_EXT_draw_instanced 1
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDEXTPROC) (GLenum బహుళకం, GLint ప్రారంభం, GLsizei లెక్క, GLsizei primcount);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDEXTPROC) (GLenum బహుళకం, GLsizei లెక్క, GLenum type, స్థిరరాశి శూన్య *indices, GLsizei primcount);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glDrawArraysInstancedEXT (GLenum బహుళకం, GLint ప్రారంభం, GLsizei లెక్క, GLsizei primcount);
GL_APICALL శూన్య GL_APIENTRY glDrawElementsInstancedEXT (GLenum బహుళకం, GLsizei లెక్క, GLenum type, స్థిరరాశి శూన్య *indices, GLsizei primcount);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_draw_instanced */

#నిర్వచితం_కాకపోతే GL_EXT_draw_transform_feedback
#నిర్వచించు GL_EXT_draw_transform_feedback 1
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKEXTPROC) (GLenum బహుళకం, GLuint id);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDEXTPROC) (GLenum బహుళకం, GLuint id, GLsizei instancecount);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glDrawTransformFeedbackEXT (GLenum బహుళకం, GLuint id);
GL_APICALL శూన్య GL_APIENTRY glDrawTransformFeedbackInstancedEXT (GLenum బహుళకం, GLuint id, GLsizei instancecount);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_draw_transform_feedback */

#నిర్వచితం_కాకపోతే GL_EXT_external_బఫరు
#నిర్వచించు GL_EXT_external_బఫరు 1
రకనిర్వచనం శూన్య *GLegl_Client_బఫరు_EXT;
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBUFFERSTORAGEEXTERNALEXTPROC) (GLenum లక్ష్యం, GLintptr స్థానభ్రంశం_2, GLsizeiptr కొలత, GLegl_Client_బఫరు_EXT client_బఫరు, GLbitfield flags);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLNAMEDBUFFERSTORAGEEXTERNALEXTPROC) (GLuint బఫరు_2, GLintptr స్థానభ్రంశం_2, GLsizeiptr కొలత, GLegl_Client_బఫరు_EXT client_బఫరు, GLbitfield flags);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_బఫరు_Storage_External_EXT (GLenum లక్ష్యం, GLintptr స్థానభ్రంశం_2, GLsizeiptr కొలత, GLegl_Client_బఫరు_EXT client_బఫరు, GLbitfield flags);
GL_APICALL శూన్య GL_APIENTRY gl_Named_బఫరు_Storage_External_EXT (GLuint బఫరు_2, GLintptr స్థానభ్రంశం_2, GLsizeiptr కొలత, GLegl_Client_బఫరు_EXT client_బఫరు, GLbitfield flags);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_external_buffer */

#నిర్వచితం_కాకపోతే GL_EXT_float_blend
#నిర్వచించు GL_EXT_float_blend 1
#అయితే_ముగింపు /* GL_EXT_float_blend */

#నిర్వచితం_కాకపోతే GL_EXT_fragment_shading_రేటు
#నిర్వచించు GL_EXT_fragment_shading_రేటు 1
#నిర్వచించు GL_SHADING_రేటు_1_X1_PIXELS_EXT    0x96A6
#నిర్వచించు GL_SHADING_రేటు_1_X2_PIXELS_EXT    0x96A7
#నిర్వచించు GL_SHADING_రేటు_2_X1_PIXELS_EXT    0x96A8
#నిర్వచించు GL_SHADING_రేటు_2_X2_PIXELS_EXT    0x96A9
#నిర్వచించు GL_SHADING_రేటు_1_X4_PIXELS_EXT    0x96AA
#నిర్వచించు GL_SHADING_రేటు_4_X1_PIXELS_EXT    0x96AB
#నిర్వచించు GL_SHADING_రేటు_4_X2_PIXELS_EXT    0x96AC
#నిర్వచించు GL_SHADING_రేటు_2_X4_PIXELS_EXT    0x96AD
#నిర్వచించు GL_SHADING_రేటు_4_X4_PIXELS_EXT    0x96AE
#నిర్వచించు GL_SHADING_రేటు_EXT               0x96D0
#నిర్వచించు GL_SHADING_రేటు_ATTACHMENT_EXT    0x96D1
#నిర్వచించు GL_FRAGMENT_SHADING_రేటు_COMBINER_OP_KEEP_EXT 0x96D2
#నిర్వచించు GL_FRAGMENT_SHADING_రేటు_COMBINER_OP_REPLACE_EXT 0x96D3
#నిర్వచించు GL_FRAGMENT_SHADING_రేటు_COMBINER_OP_MIN_EXT 0x96D4
#నిర్వచించు GL_FRAGMENT_SHADING_రేటు_COMBINER_OP_MAX_EXT 0x96D5
#నిర్వచించు GL_FRAGMENT_SHADING_రేటు_COMBINER_OP_MUL_EXT 0x96D6
#నిర్వచించు GL_MIN_FRAGMENT_SHADING_రేటు_ATTACHMENT_TEXEL_వెడల్పు_EXT 0x96D7
#నిర్వచించు GL_MAX_FRAGMENT_SHADING_రేటు_ATTACHMENT_TEXEL_వెడల్పు_EXT 0x96D8
#నిర్వచించు GL_MIN_FRAGMENT_SHADING_రేటు_ATTACHMENT_TEXEL_ఎత్తు_EXT 0x96D9
#నిర్వచించు GL_MAX_FRAGMENT_SHADING_రేటు_ATTACHMENT_TEXEL_ఎత్తు_EXT 0x96DA
#నిర్వచించు GL_MAX_FRAGMENT_SHADING_రేటు_ATTACHMENT_TEXEL_ASPECT_నిష్పత్తి_EXT 0x96DB
#నిర్వచించు GL_MAX_FRAGMENT_SHADING_రేటు_ATTACHMENT_LAYERS_EXT 0x96DC
#నిర్వచించు GL_FRAGMENT_SHADING_రేటు_WITH_SHADER_లోతు_STENCIL_WRITES_SUPPORTED_EXT 0x96DD
#నిర్వచించు GL_FRAGMENT_SHADING_రేటు_WITH_SAMPLE_ముసుగు_SUPPORTED_EXT 0x96DE
#నిర్వచించు GL_FRAGMENT_SHADING_రేటు_ATTACHMENT_WITH_DEFAULT_FRAMEBUFFER_SUPPORTED_EXT 0x96DF
#నిర్వచించు GL_FRAGMENT_SHADING_రేటు_NON_TRIVIAL_COMBINERS_SUPPORTED_EXT 0x8F6F
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETFRAGMENTSHADINGRATESEXTPROC) (GLsizei samples, GLsizei max_లెక్క, GLsizei *లెక్క, GLenum *shadingRates);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSHADINGRATEEXTPROC) (GLenum రేటు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSHADINGRATECOMBINEROPSEXTPROC) (GLenum combinerOp0, GLenum combinerOp1);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFRAMEBUFFERSHADINGRATEEXTPROC) (GLenum లక్ష్యం, GLenum attachment, GLuint texture, GLint పునాది_Layer, GLsizei అంకె_Layers, GLsizei texel_వెడల్పు, GLsizei texel_ఎత్తు);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glGetFragmentShadingRatesEXT (GLsizei samples, GLsizei max_లెక్క, GLsizei *లెక్క, GLenum *shadingRates);
GL_APICALL శూన్య GL_APIENTRY gl_Shading_రేటు_EXT (GLenum రేటు);
GL_APICALL శూన్య GL_APIENTRY gl_Shading_రేటు_Combiner_Ops_EXT (GLenum combinerOp0, GLenum combinerOp1);
GL_APICALL శూన్య GL_APIENTRY gl_Framebuffer_Shading_రేటు_EXT (GLenum లక్ష్యం, GLenum attachment, GLuint texture, GLint పునాది_Layer, GLsizei అంకె_Layers, GLsizei texel_వెడల్పు, GLsizei texel_ఎత్తు);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_fragment_shading_rate */

#నిర్వచితం_కాకపోతే GL_EXT_framebuffer_blit_layers
#నిర్వచించు GL_EXT_framebuffer_blit_layers 1
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBLITFRAMEBUFFERLAYERSEXTPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield ముసుగు, GLenum filter);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBLITFRAMEBUFFERLAYEREXTPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint srcLayer, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLint dstLayer, GLbitfield ముసుగు, GLenum filter);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glBlitFramebufferLayersEXT (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield ముసుగు, GLenum filter);
GL_APICALL శూన్య GL_APIENTRY glBlitFramebufferLayerEXT (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint srcLayer, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLint dstLayer, GLbitfield ముసుగు, GLenum filter);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_framebuffer_blit_layers */

#నిర్వచితం_కాకపోతే GL_EXT_geometry_బిందువు_కొలత
#నిర్వచించు GL_EXT_geometry_బిందువు_కొలత 1
#అయితే_ముగింపు /* GL_EXT_geometry_point_size */

#నిర్వచితం_కాకపోతే GL_EXT_geometry_shader
#నిర్వచించు GL_EXT_geometry_shader 1
#నిర్వచించు GL_GEOMETRY_SHADER_EXT            0x8DD9
#నిర్వచించు GL_GEOMETRY_SHADER_బిట్టు_EXT        0x00000004
#నిర్వచించు GL_GEOMETRY_LINKED_VERTICES_బహిర్గతం_EXT 0x8916
#నిర్వచించు GL_GEOMETRY_LINKED_ఆదానం_TYPE_EXT 0x8917
#నిర్వచించు GL_GEOMETRY_LINKED_OUTPUT_TYPE_EXT 0x8918
#నిర్వచించు GL_GEOMETRY_SHADER_INVOCATIONS_EXT 0x887F
#నిర్వచించు GL_LAYER_PROVOKING_శీర్షం_EXT     0x825E
#నిర్వచించు GL_పంక్తులు_ADJACENCY_EXT            0x000A
#నిర్వచించు GL_పంక్తి_STRIP_ADJACENCY_EXT       0x000B
#నిర్వచించు GL_TRIANGLES_ADJACENCY_EXT        0x000C
#నిర్వచించు GL_TRIANGLE_STRIP_ADJACENCY_EXT   0x000D
#నిర్వచించు GL_MAX_GEOMETRY_ఏకరీతి_COMPONENTS_EXT 0x8DDF
#నిర్వచించు GL_MAX_GEOMETRY_ఏకరీతి_ఖండాలు_EXT 0x8A2C
#నిర్వచించు GL_MAX_COMBINED_GEOMETRY_ఏకరీతి_COMPONENTS_EXT 0x8A32
#నిర్వచించు GL_MAX_GEOMETRY_ఆదానం_COMPONENTS_EXT 0x9123
#నిర్వచించు GL_MAX_GEOMETRY_OUTPUT_COMPONENTS_EXT 0x9124
#నిర్వచించు GL_MAX_GEOMETRY_OUTPUT_VERTICES_EXT 0x8DE0
#నిర్వచించు GL_MAX_GEOMETRY_మొత్తం_OUTPUT_COMPONENTS_EXT 0x8DE1
#నిర్వచించు GL_MAX_GEOMETRY_SHADER_INVOCATIONS_EXT 0x8E5A
#నిర్వచించు GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_EXT 0x8C29
#నిర్వచించు GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS_EXT 0x92CF
#నిర్వచించు GL_MAX_GEOMETRY_ATOMIC_COUNTERS_EXT 0x92D5
#నిర్వచించు GL_MAX_GEOMETRY_IMAGE_UNIFORMS_EXT 0x90CD
#నిర్వచించు GL_MAX_GEOMETRY_SHADER_STORAGE_ఖండాలు_EXT 0x90D7
#నిర్వచించు GL_మొదటి_శీర్షం_CONVENTION_EXT    0x8E4D
#నిర్వచించు GL_చివరి_శీర్షం_CONVENTION_EXT     0x8E4E
#నిర్వచించు GL_UNDEFINED_శీర్షం_EXT           0x8260
#నిర్వచించు GL_PRIMITIVES_GENERATED_EXT       0x8C87
#నిర్వచించు GL_FRAMEBUFFER_DEFAULT_LAYERS_EXT 0x9312
#నిర్వచించు GL_MAX_FRAMEBUFFER_LAYERS_EXT     0x9317
#నిర్వచించు GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_EXT 0x8DA8
#నిర్వచించు GL_FRAMEBUFFER_ATTACHMENT_LAYERED_EXT 0x8DA7
#నిర్వచించు GL_REFERENCED_BY_GEOMETRY_SHADER_EXT 0x9309
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREEXTPROC) (GLenum లక్ష్యం, GLenum attachment, GLuint texture, GLint level);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glFramebufferTextureEXT (GLenum లక్ష్యం, GLenum attachment, GLuint texture, GLint level);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_geometry_shader */

#నిర్వచితం_కాకపోతే GL_EXT_gpu_shader5
#నిర్వచించు GL_EXT_gpu_shader5 1
#అయితే_ముగింపు /* GL_EXT_gpu_shader5 */

#నిర్వచితం_కాకపోతే GL_EXT_instanced_arrays
#నిర్వచించు GL_EXT_instanced_arrays 1
#నిర్వచించు GL_శీర్షం_ATTRIB_ARRAY_భాజకం_EXT 0x88FE
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLVERTEXATTRIBDIVISOREXTPROC) (GLuint సూచీ, GLuint భాజకం);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_శీర్షం_Attrib_భాజకం_EXT (GLuint సూచీ, GLuint భాజకం);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_instanced_arrays */

#నిర్వచితం_కాకపోతే GL_EXT_map_బఫరు_range
#నిర్వచించు GL_EXT_map_బఫరు_range 1
#నిర్వచించు GL_MAP_READ_బిట్టు_EXT               0x0001
#నిర్వచించు GL_MAP_WRITE_బిట్టు_EXT              0x0002
#నిర్వచించు GL_MAP_INVALIDATE_RANGE_బిట్టు_EXT   0x0004
#నిర్వచించు GL_MAP_INVALIDATE_బఫరు_బిట్టు_EXT  0x0008
#నిర్వచించు GL_MAP_FLUSH_EXPLICIT_బిట్టు_EXT     0x0010
#నిర్వచించు GL_MAP_UNSYNCHRONIZED_బిట్టు_EXT     0x0020
రకనిర్వచనం శూన్య *(GL_APIENTRYP PFNGLMAPBUFFERRANGEEXTPROC) (GLenum లక్ష్యం, GLintptr స్థానభ్రంశం_2, GLsizeiptr నిడివి, GLbitfield access);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEEXTPROC) (GLenum లక్ష్యం, GLintptr స్థానభ్రంశం_2, GLsizeiptr నిడివి);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య *GL_APIENTRY gl_Map_బఫరు_Range_EXT (GLenum లక్ష్యం, GLintptr స్థానభ్రంశం_2, GLsizeiptr నిడివి, GLbitfield access);
GL_APICALL శూన్య GL_APIENTRY gl_Flush_Mapped_బఫరు_Range_EXT (GLenum లక్ష్యం, GLintptr స్థానభ్రంశం_2, GLsizeiptr నిడివి);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_map_buffer_range */

#నిర్వచితం_కాకపోతే GL_EXT_జ్ఞాపకం_object
#నిర్వచించు GL_EXT_జ్ఞాపకం_object 1
#నిర్వచించు GL_TEXTURE_TILING_EXT             0x9580
#నిర్వచించు GL_DEDICATED_జ్ఞాపకం_OBJECT_EXT    0x9581
#నిర్వచించు GL_PROTECTED_జ్ఞాపకం_OBJECT_EXT    0x959B
#నిర్వచించు GL_అంకె_TILING_TYPES_EXT           0x9582
#నిర్వచించు GL_TILING_TYPES_EXT               0x9583
#నిర్వచించు GL_OPTIMAL_TILING_EXT             0x9584
#నిర్వచించు GL_రేఖీయ_TILING_EXT              0x9585
#నిర్వచించు GL_అంకె_DEVICE_UUIDS_EXT           0x9596
#నిర్వచించు GL_DEVICE_UUID_EXT                0x9597
#నిర్వచించు GL_DRIVER_UUID_EXT                0x9598
#నిర్వచించు GL_UUID_కొలత_EXT                  16
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETUNSIGNEDBYTEVEXTPROC) (GLenum pname, GLubyte *దత్తాంశం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETUNSIGNEDBYTEI_VEXTPROC) (GLenum లక్ష్యం, GLuint సూచీ, GLubyte *దత్తాంశం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDELETEMEMORYOBJECTSEXTPROC) (GLsizei n, స్థిరరాశి GLuint *జ్ఞాపకం_Objects);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLISMEMORYOBJECTEXTPROC) (GLuint జ్ఞాపకం_Object);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCREATEMEMORYOBJECTSEXTPROC) (GLsizei n, GLuint *జ్ఞాపకం_Objects);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMEMORYOBJECTPARAMETERIVEXTPROC) (GLuint జ్ఞాపకం_Object, GLenum pname, స్థిరరాశి GLint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETMEMORYOBJECTPARAMETERIVEXTPROC) (GLuint జ్ఞాపకం_Object, GLenum pname, GLint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXSTORAGEMEM2DEXTPROC) (GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum అంతర్గత_Format, GLsizei వెడల్పు, GLsizei ఎత్తు, GLuint జ్ఞాపకం, GLuint64 స్థానభ్రంశం_2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXSTORAGEMEM2DMULTISAMPLEEXTPROC) (GLenum లక్ష్యం, GLsizei samples, GLenum అంతర్గత_Format, GLsizei వెడల్పు, GLsizei ఎత్తు, GLboolean fixedSampleLocations, GLuint జ్ఞాపకం, GLuint64 స్థానభ్రంశం_2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXSTORAGEMEM3DEXTPROC) (GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum అంతర్గత_Format, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLuint జ్ఞాపకం, GLuint64 స్థానభ్రంశం_2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXSTORAGEMEM3DMULTISAMPLEEXTPROC) (GLenum లక్ష్యం, GLsizei samples, GLenum అంతర్గత_Format, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLboolean fixedSampleLocations, GLuint జ్ఞాపకం, GLuint64 స్థానభ్రంశం_2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBUFFERSTORAGEMEMEXTPROC) (GLenum లక్ష్యం, GLsizeiptr కొలత, GLuint జ్ఞాపకం, GLuint64 స్థానభ్రంశం_2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXTURESTORAGEMEM2DEXTPROC) (GLuint texture, GLsizei స్థాయిలు, GLenum అంతర్గత_Format, GLsizei వెడల్పు, GLsizei ఎత్తు, GLuint జ్ఞాపకం, GLuint64 స్థానభ్రంశం_2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXTURESTORAGEMEM2DMULTISAMPLEEXTPROC) (GLuint texture, GLsizei samples, GLenum అంతర్గత_Format, GLsizei వెడల్పు, GLsizei ఎత్తు, GLboolean fixedSampleLocations, GLuint జ్ఞాపకం, GLuint64 స్థానభ్రంశం_2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXTURESTORAGEMEM3DEXTPROC) (GLuint texture, GLsizei స్థాయిలు, GLenum అంతర్గత_Format, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLuint జ్ఞాపకం, GLuint64 స్థానభ్రంశం_2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXTURESTORAGEMEM3DMULTISAMPLEEXTPROC) (GLuint texture, GLsizei samples, GLenum అంతర్గత_Format, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLboolean fixedSampleLocations, GLuint జ్ఞాపకం, GLuint64 స్థానభ్రంశం_2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLNAMEDBUFFERSTORAGEMEMEXTPROC) (GLuint బఫరు_2, GLsizeiptr కొలత, GLuint జ్ఞాపకం, GLuint64 స్థానభ్రంశం_2);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glGetUnsignedBytevEXT (GLenum pname, GLubyte *దత్తాంశం);
GL_APICALL శూన్య GL_APIENTRY glGetUnsignedBytei_vEXT (GLenum లక్ష్యం, GLuint సూచీ, GLubyte *దత్తాంశం);
GL_APICALL శూన్య GL_APIENTRY gl_Delete_జ్ఞాపకం_Objects_EXT (GLsizei n, స్థిరరాశి GLuint *జ్ఞాపకం_Objects);
GL_APICALL GLboolean GL_APIENTRY gl_Is_జ్ఞాపకం_Object_EXT (GLuint జ్ఞాపకం_Object);
GL_APICALL శూన్య GL_APIENTRY gl_Create_జ్ఞాపకం_Objects_EXT (GLsizei n, GLuint *జ్ఞాపకం_Objects);
GL_APICALL శూన్య GL_APIENTRY gl_జ్ఞాపకం_Object_Parameteriv_EXT (GLuint జ్ఞాపకం_Object, GLenum pname, స్థిరరాశి GLint *params);
GL_APICALL శూన్య GL_APIENTRY gl_Get_జ్ఞాపకం_Object_Parameteriv_EXT (GLuint జ్ఞాపకం_Object, GLenum pname, GLint *params);
GL_APICALL శూన్య GL_APIENTRY glTexStorageMem2DEXT (GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum అంతర్గత_Format, GLsizei వెడల్పు, GLsizei ఎత్తు, GLuint జ్ఞాపకం, GLuint64 స్థానభ్రంశం_2);
GL_APICALL శూన్య GL_APIENTRY glTexStorageMem2DMultisampleEXT (GLenum లక్ష్యం, GLsizei samples, GLenum అంతర్గత_Format, GLsizei వెడల్పు, GLsizei ఎత్తు, GLboolean fixedSampleLocations, GLuint జ్ఞాపకం, GLuint64 స్థానభ్రంశం_2);
GL_APICALL శూన్య GL_APIENTRY glTexStorageMem3DEXT (GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum అంతర్గత_Format, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLuint జ్ఞాపకం, GLuint64 స్థానభ్రంశం_2);
GL_APICALL శూన్య GL_APIENTRY glTexStorageMem3DMultisampleEXT (GLenum లక్ష్యం, GLsizei samples, GLenum అంతర్గత_Format, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLboolean fixedSampleLocations, GLuint జ్ఞాపకం, GLuint64 స్థానభ్రంశం_2);
GL_APICALL శూన్య GL_APIENTRY gl_బఫరు_Storage_Mem_EXT (GLenum లక్ష్యం, GLsizeiptr కొలత, GLuint జ్ఞాపకం, GLuint64 స్థానభ్రంశం_2);
GL_APICALL శూన్య GL_APIENTRY glTextureStorageMem2DEXT (GLuint texture, GLsizei స్థాయిలు, GLenum అంతర్గత_Format, GLsizei వెడల్పు, GLsizei ఎత్తు, GLuint జ్ఞాపకం, GLuint64 స్థానభ్రంశం_2);
GL_APICALL శూన్య GL_APIENTRY glTextureStorageMem2DMultisampleEXT (GLuint texture, GLsizei samples, GLenum అంతర్గత_Format, GLsizei వెడల్పు, GLsizei ఎత్తు, GLboolean fixedSampleLocations, GLuint జ్ఞాపకం, GLuint64 స్థానభ్రంశం_2);
GL_APICALL శూన్య GL_APIENTRY glTextureStorageMem3DEXT (GLuint texture, GLsizei స్థాయిలు, GLenum అంతర్గత_Format, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLuint జ్ఞాపకం, GLuint64 స్థానభ్రంశం_2);
GL_APICALL శూన్య GL_APIENTRY glTextureStorageMem3DMultisampleEXT (GLuint texture, GLsizei samples, GLenum అంతర్గత_Format, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLboolean fixedSampleLocations, GLuint జ్ఞాపకం, GLuint64 స్థానభ్రంశం_2);
GL_APICALL శూన్య GL_APIENTRY gl_Named_బఫరు_Storage_Mem_EXT (GLuint బఫరు_2, GLsizeiptr కొలత, GLuint జ్ఞాపకం, GLuint64 స్థానభ్రంశం_2);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_memory_object */

#నిర్వచితం_కాకపోతే GL_EXT_జ్ఞాపకం_object_fd
#నిర్వచించు GL_EXT_జ్ఞాపకం_object_fd 1
#నిర్వచించు GL_HANDLE_TYPE_OPAQUE_FD_EXT      0x9586
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLIMPORTMEMORYFDEXTPROC) (GLuint జ్ఞాపకం, GLuint64 కొలత, GLenum handleType, GLint fd);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_Import_జ్ఞాపకం_Fd_EXT (GLuint జ్ఞాపకం, GLuint64 కొలత, GLenum handleType, GLint fd);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_memory_object_fd */

#నిర్వచితం_కాకపోతే GL_EXT_జ్ఞాపకం_object_win32
#నిర్వచించు GL_EXT_జ్ఞాపకం_object_win32 1
#నిర్వచించు GL_HANDLE_TYPE_OPAQUE_WIN32_EXT   0x9587
#నిర్వచించు GL_HANDLE_TYPE_OPAQUE_WIN32_KMT_EXT 0x9588
#నిర్వచించు GL_DEVICE_LUID_EXT                0x9599
#నిర్వచించు GL_DEVICE_కణుపు_ముసుగు_EXT           0x959A
#నిర్వచించు GL_LUID_కొలత_EXT                  8
#నిర్వచించు GL_HANDLE_TYPE_D3D12_TILEPOOL_EXT 0x9589
#నిర్వచించు GL_HANDLE_TYPE_D3D12_RESOURCE_EXT 0x958A
#నిర్వచించు GL_HANDLE_TYPE_D3D11_IMAGE_EXT    0x958B
#నిర్వచించు GL_HANDLE_TYPE_D3D11_IMAGE_KMT_EXT 0x958C
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLIMPORTMEMORYWIN32HANDLEEXTPROC) (GLuint జ్ఞాపకం, GLuint64 కొలత, GLenum handleType, శూన్య *handle);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLIMPORTMEMORYWIN32NAMEEXTPROC) (GLuint జ్ఞాపకం, GLuint64 కొలత, GLenum handleType, స్థిరరాశి శూన్య *name);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_Import_జ్ఞాపకం_Win32_Handle_EXT (GLuint జ్ఞాపకం, GLuint64 కొలత, GLenum handleType, శూన్య *handle);
GL_APICALL శూన్య GL_APIENTRY gl_Import_జ్ఞాపకం_Win32_Name_EXT (GLuint జ్ఞాపకం, GLuint64 కొలత, GLenum handleType, స్థిరరాశి శూన్య *name);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_memory_object_win32 */

#నిర్వచితం_కాకపోతే GL_EXT_mesh_shader
#నిర్వచించు GL_EXT_mesh_shader 1
#నిర్వచించు GL_MESH_SHADER_EXT                0x9559
#నిర్వచించు GL_TASK_SHADER_EXT                0x955A
#నిర్వచించు GL_MAX_MESH_ఏకరీతి_ఖండాలు_EXT    0x8E60
#నిర్వచించు GL_MAX_MESH_TEXTURE_IMAGE_UNITS_EXT 0x8E61
#నిర్వచించు GL_MAX_MESH_IMAGE_UNIFORMS_EXT    0x8E62
#నిర్వచించు GL_MAX_MESH_ఏకరీతి_COMPONENTS_EXT 0x8E63
#నిర్వచించు GL_MAX_MESH_ATOMIC_COUNTER_BUFFERS_EXT 0x8E64
#నిర్వచించు GL_MAX_MESH_ATOMIC_COUNTERS_EXT   0x8E65
#నిర్వచించు GL_MAX_MESH_SHADER_STORAGE_ఖండాలు_EXT 0x8E66
#నిర్వచించు GL_MAX_COMBINED_MESH_ఏకరీతి_COMPONENTS_EXT 0x8E67
#నిర్వచించు GL_MAX_TASK_ఏకరీతి_ఖండాలు_EXT    0x8E68
#నిర్వచించు GL_MAX_TASK_TEXTURE_IMAGE_UNITS_EXT 0x8E69
#నిర్వచించు GL_MAX_TASK_IMAGE_UNIFORMS_EXT    0x8E6A
#నిర్వచించు GL_MAX_TASK_ఏకరీతి_COMPONENTS_EXT 0x8E6B
#నిర్వచించు GL_MAX_TASK_ATOMIC_COUNTER_BUFFERS_EXT 0x8E6C
#నిర్వచించు GL_MAX_TASK_ATOMIC_COUNTERS_EXT   0x8E6D
#నిర్వచించు GL_MAX_TASK_SHADER_STORAGE_ఖండాలు_EXT 0x8E6E
#నిర్వచించు GL_MAX_COMBINED_TASK_ఏకరీతి_COMPONENTS_EXT 0x8E6F
#నిర్వచించు GL_MAX_TASK_WORK_సమూహం_మొత్తం_లెక్క_EXT 0x9740
#నిర్వచించు GL_MAX_MESH_WORK_సమూహం_మొత్తం_లెక్క_EXT 0x9741
#నిర్వచించు GL_MAX_MESH_WORK_సమూహం_INVOCATIONS_EXT 0x9757
#నిర్వచించు GL_MAX_TASK_WORK_సమూహం_INVOCATIONS_EXT 0x9759
#నిర్వచించు GL_MAX_TASK_PAYLOAD_కొలత_EXT      0x9742
#నిర్వచించు GL_MAX_TASK_SHARED_జ్ఞాపకం_కొలత_EXT 0x9743
#నిర్వచించు GL_MAX_MESH_SHARED_జ్ఞాపకం_కొలత_EXT 0x9744
#నిర్వచించు GL_MAX_TASK_PAYLOAD_AND_SHARED_జ్ఞాపకం_కొలత_EXT 0x9745
#నిర్వచించు GL_MAX_MESH_PAYLOAD_AND_SHARED_జ్ఞాపకం_కొలత_EXT 0x9746
#నిర్వచించు GL_MAX_MESH_OUTPUT_జ్ఞాపకం_కొలత_EXT 0x9747
#నిర్వచించు GL_MAX_MESH_PAYLOAD_AND_OUTPUT_జ్ఞాపకం_కొలత_EXT 0x9748
#నిర్వచించు GL_MAX_MESH_OUTPUT_VERTICES_EXT   0x9538
#నిర్వచించు GL_MAX_MESH_OUTPUT_PRIMITIVES_EXT 0x9756
#నిర్వచించు GL_MAX_MESH_OUTPUT_COMPONENTS_EXT 0x9749
#నిర్వచించు GL_MAX_MESH_OUTPUT_LAYERS_EXT     0x974A
#నిర్వచించు GL_MAX_MESH_MULTIVIEW_VIEW_లెక్క_EXT 0x9557
#నిర్వచించు GL_MESH_OUTPUT_చొప్పున_శీర్షం_GRANULARITY_EXT 0x92DF
#నిర్వచించు GL_MESH_OUTPUT_చొప్పున_PRIMITIVE_GRANULARITY_EXT 0x9543
#నిర్వచించు GL_MAX_PREFERRED_TASK_WORK_సమూహం_INVOCATIONS_EXT 0x974B
#నిర్వచించు GL_MAX_PREFERRED_MESH_WORK_సమూహం_INVOCATIONS_EXT 0x974C
#నిర్వచించు GL_MESH_PREFERS_LOCAL_INVOCATION_శీర్షం_OUTPUT_EXT 0x974D
#నిర్వచించు GL_MESH_PREFERS_LOCAL_INVOCATION_PRIMITIVE_OUTPUT_EXT 0x974E
#నిర్వచించు GL_MESH_PREFERS_COMPACT_శీర్షం_OUTPUT_EXT 0x974F
#నిర్వచించు GL_MESH_PREFERS_COMPACT_PRIMITIVE_OUTPUT_EXT 0x9750
#నిర్వచించు GL_MAX_TASK_WORK_సమూహం_లెక్క_EXT  0x9751
#నిర్వచించు GL_MAX_MESH_WORK_సమూహం_లెక్క_EXT  0x9752
#నిర్వచించు GL_MAX_MESH_WORK_సమూహం_కొలత_EXT   0x9758
#నిర్వచించు GL_MAX_TASK_WORK_సమూహం_కొలత_EXT   0x975A
#నిర్వచించు GL_MESH_WORK_సమూహం_కొలత_EXT       0x953E
#నిర్వచించు GL_TASK_WORK_సమూహం_కొలత_EXT       0x953F
#నిర్వచించు GL_MESH_VERTICES_బహిర్గతం_EXT          0x9579
#నిర్వచించు GL_MESH_PRIMITIVES_బహిర్గతం_EXT        0x957A
#నిర్వచించు GL_MESH_OUTPUT_TYPE_EXT           0x957B
#నిర్వచించు GL_ఏకరీతి_ఖండం_REFERENCED_BY_MESH_SHADER_EXT 0x959C
#నిర్వచించు GL_ఏకరీతి_ఖండం_REFERENCED_BY_TASK_SHADER_EXT 0x959D
#నిర్వచించు GL_REFERENCED_BY_MESH_SHADER_EXT  0x95A0
#నిర్వచించు GL_REFERENCED_BY_TASK_SHADER_EXT  0x95A1
#నిర్వచించు GL_TASK_SHADER_INVOCATIONS_EXT    0x9753
#నిర్వచించు GL_MESH_SHADER_INVOCATIONS_EXT    0x9754
#నిర్వచించు GL_MESH_PRIMITIVES_GENERATED_EXT  0x9755
#నిర్వచించు GL_MESH_SHADER_బిట్టు_EXT            0x00000040
#నిర్వచించు GL_TASK_SHADER_బిట్టు_EXT            0x00000080
#నిర్వచించు GL_MESH_SUBROUTINE_EXT            0x957C
#నిర్వచించు GL_TASK_SUBROUTINE_EXT            0x957D
#నిర్వచించు GL_MESH_SUBROUTINE_ఏకరీతి_EXT    0x957E
#నిర్వచించు GL_TASK_SUBROUTINE_ఏకరీతి_EXT    0x957F
#నిర్వచించు GL_ATOMIC_COUNTER_బఫరు_REFERENCED_BY_MESH_SHADER_EXT 0x959E
#నిర్వచించు GL_ATOMIC_COUNTER_బఫరు_REFERENCED_BY_TASK_SHADER_EXT 0x959F
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWMESHTASKSEXTPROC) (GLuint అంకె_groups_x, GLuint అంకె_groups_y, GLuint అంకె_groups_z);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWMESHTASKSINDIRECTEXTPROC) (GLintptr పరోక్ష);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMULTIDRAWMESHTASKSINDIRECTEXTPROC) (GLintptr పరోక్ష, GLsizei drawcount, GLsizei stride);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTEXTPROC) (GLintptr పరోక్ష, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glDrawMeshTasksEXT (GLuint అంకె_groups_x, GLuint అంకె_groups_y, GLuint అంకె_groups_z);
GL_APICALL శూన్య GL_APIENTRY gl_Draw_Mesh_Tasks_పరోక్ష_EXT (GLintptr పరోక్ష);
GL_APICALL శూన్య GL_APIENTRY gl_Multi_Draw_Mesh_Tasks_పరోక్ష_EXT (GLintptr పరోక్ష, GLsizei drawcount, GLsizei stride);
GL_APICALL శూన్య GL_APIENTRY gl_Multi_Draw_Mesh_Tasks_పరోక్ష_లెక్క_EXT (GLintptr పరోక్ష, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_mesh_shader */

#నిర్వచితం_కాకపోతే GL_EXT_multi_draw_arrays
#నిర్వచించు GL_EXT_multi_draw_arrays 1
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMULTIDRAWARRAYSEXTPROC) (GLenum బహుళకం, స్థిరరాశి GLint *మొదటి, స్థిరరాశి GLsizei *లెక్క, GLsizei primcount);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSEXTPROC) (GLenum బహుళకం, స్థిరరాశి GLsizei *లెక్క, GLenum type, స్థిరరాశి శూన్య *స్థిరరాశి*indices, GLsizei primcount);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glMultiDrawArraysEXT (GLenum బహుళకం, స్థిరరాశి GLint *మొదటి, స్థిరరాశి GLsizei *లెక్క, GLsizei primcount);
GL_APICALL శూన్య GL_APIENTRY glMultiDrawElementsEXT (GLenum బహుళకం, స్థిరరాశి GLsizei *లెక్క, GLenum type, స్థిరరాశి శూన్య *స్థిరరాశి*indices, GLsizei primcount);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_multi_draw_arrays */

#నిర్వచితం_కాకపోతే GL_EXT_multi_draw_పరోక్ష
#నిర్వచించు GL_EXT_multi_draw_పరోక్ష 1
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMULTIDRAWARRAYSINDIRECTEXTPROC) (GLenum బహుళకం, స్థిరరాశి శూన్య *పరోక్ష, GLsizei drawcount, GLsizei stride);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSINDIRECTEXTPROC) (GLenum బహుళకం, GLenum type, స్థిరరాశి శూన్య *పరోక్ష, GLsizei drawcount, GLsizei stride);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_Multi_Draw_Arrays_పరోక్ష_EXT (GLenum బహుళకం, స్థిరరాశి శూన్య *పరోక్ష, GLsizei drawcount, GLsizei stride);
GL_APICALL శూన్య GL_APIENTRY gl_Multi_Draw_Elements_పరోక్ష_EXT (GLenum బహుళకం, GLenum type, స్థిరరాశి శూన్య *పరోక్ష, GLsizei drawcount, GLsizei stride);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_multi_draw_indirect */

#నిర్వచితం_కాకపోతే GL_EXT_multisampled_compatibility
#నిర్వచించు GL_EXT_multisampled_compatibility 1
#నిర్వచించు GL_MULTISAMPLE_EXT                0x809D
#నిర్వచించు GL_SAMPLE_ALPHA_గమ్యం_ONE_EXT        0x809F
#అయితే_ముగింపు /* GL_EXT_multisampled_compatibility */

#నిర్వచితం_కాకపోతే GL_EXT_multisampled_render_గమ్యం_texture
#నిర్వచించు GL_EXT_multisampled_render_గమ్యం_texture 1
#నిర్వచించు GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SAMPLES_EXT 0x8D6C
#నిర్వచించు GL_RENDERBUFFER_SAMPLES_EXT       0x8CAB
#నిర్వచించు GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT 0x8D56
#నిర్వచించు GL_MAX_SAMPLES_EXT                0x8D57
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) (GLenum లక్ష్యం, GLsizei samples, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEEXTPROC) (GLenum లక్ష్యం, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glRenderbufferStorageMultisampleEXT (GLenum లక్ష్యం, GLsizei samples, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
GL_APICALL శూన్య GL_APIENTRY glFramebufferTexture2DMultisampleEXT (GLenum లక్ష్యం, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_multisampled_render_to_texture */

#నిర్వచితం_కాకపోతే GL_EXT_multisampled_render_గమ్యం_texture2
#నిర్వచించు GL_EXT_multisampled_render_గమ్యం_texture2 1
#అయితే_ముగింపు /* GL_EXT_multisampled_render_to_texture2 */

#నిర్వచితం_కాకపోతే GL_EXT_multiview_draw_buffers
#నిర్వచించు GL_EXT_multiview_draw_buffers 1
#నిర్వచించు GL_COLOR_ATTACHMENT_EXT           0x90F0
#నిర్వచించు GL_MULTIVIEW_EXT                  0x90F1
#నిర్వచించు GL_DRAW_బఫరు_EXT                0x0C01
#నిర్వచించు GL_READ_బఫరు_EXT                0x0C02
#నిర్వచించు GL_MAX_MULTIVIEW_BUFFERS_EXT      0x90F2
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLREADBUFFERINDEXEDEXTPROC) (GLenum src, GLint సూచీ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWBUFFERSINDEXEDEXTPROC) (GLint n, స్థిరరాశి GLenum *location, స్థిరరాశి GLint *indices);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETINTEGERI_VEXTPROC) (GLenum లక్ష్యం, GLuint సూచీ, GLint *దత్తాంశం);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_Read_బఫరు_సూచీకృత_EXT (GLenum src, GLint సూచీ);
GL_APICALL శూన్య GL_APIENTRY gl_Draw_Buffers_సూచీకృత_EXT (GLint n, స్థిరరాశి GLenum *location, స్థిరరాశి GLint *indices);
GL_APICALL శూన్య GL_APIENTRY glGetIntegeri_vEXT (GLenum లక్ష్యం, GLuint సూచీ, GLint *దత్తాంశం);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_multiview_draw_buffers */

#నిర్వచితం_కాకపోతే GL_EXT_multiview_tessellation_geometry_shader
#నిర్వచించు GL_EXT_multiview_tessellation_geometry_shader 1
#అయితే_ముగింపు /* GL_EXT_multiview_tessellation_geometry_shader */

#నిర్వచితం_కాకపోతే GL_EXT_multiview_texture_multisample
#నిర్వచించు GL_EXT_multiview_texture_multisample 1
#అయితే_ముగింపు /* GL_EXT_multiview_texture_multisample */

#నిర్వచితం_కాకపోతే GL_EXT_multiview_timer_query
#నిర్వచించు GL_EXT_multiview_timer_query 1
#అయితే_ముగింపు /* GL_EXT_multiview_timer_query */

#నిర్వచితం_కాకపోతే GL_EXT_occlusion_query_boolean
#నిర్వచించు GL_EXT_occlusion_query_boolean 1
#నిర్వచించు GL_ANY_SAMPLES_PASSED_EXT         0x8C2F
#నిర్వచించు GL_ANY_SAMPLES_PASSED_CONSERVATIVE_EXT 0x8D6A
#అయితే_ముగింపు /* GL_EXT_occlusion_query_boolean */

#నిర్వచితం_కాకపోతే GL_EXT_polygon_స్థానభ్రంశం_clamp
#నిర్వచించు GL_EXT_polygon_స్థానభ్రంశం_clamp 1
#నిర్వచించు GL_POLYGON_స్థానభ్రంశం_CLAMP_EXT       0x8E1B
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPOLYGONOFFSETCLAMPEXTPROC) (GLfloat గుణకం, GLfloat units, GLfloat clamp);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_Polygon_స్థానభ్రంశం_Clamp_EXT (GLfloat గుణకం, GLfloat units, GLfloat clamp);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_polygon_offset_clamp */

#నిర్వచితం_కాకపోతే GL_EXT_post_లోతు_coverage
#నిర్వచించు GL_EXT_post_లోతు_coverage 1
#అయితే_ముగింపు /* GL_EXT_post_depth_coverage */

#నిర్వచితం_కాకపోతే GL_EXT_primitive_bounding_box
#నిర్వచించు GL_EXT_primitive_bounding_box 1
#నిర్వచించు GL_PRIMITIVE_BOUNDING_BOX_EXT     0x92BE
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPRIMITIVEBOUNDINGBOXEXTPROC) (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glPrimitiveBoundingBoxEXT (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_primitive_bounding_box */

#నిర్వచితం_కాకపోతే GL_EXT_protected_textures
#నిర్వచించు GL_EXT_protected_textures 1
#నిర్వచించు GL_CONTEXT_FLAG_PROTECTED_CONTENT_బిట్టు_EXT 0x00000010
#నిర్వచించు GL_TEXTURE_PROTECTED_EXT          0x8BFA
#అయితే_ముగింపు /* GL_EXT_protected_textures */

#నిర్వచితం_కాకపోతే GL_EXT_pvrtc_sRGB
#నిర్వచించు GL_EXT_pvrtc_sRGB 1
#నిర్వచించు GL_COMPRESSED_SRGB_PVRTC_2BPPV1_EXT 0x8A54
#నిర్వచించు GL_COMPRESSED_SRGB_PVRTC_4BPPV1_EXT 0x8A55
#నిర్వచించు GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV1_EXT 0x8A56
#నిర్వచించు GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV1_EXT 0x8A57
#నిర్వచించు GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV2_IMG 0x93F0
#నిర్వచించు GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV2_IMG 0x93F1
#అయితే_ముగింపు /* GL_EXT_pvrtc_sRGB */

#నిర్వచితం_కాకపోతే GL_EXT_raster_multisample
#నిర్వచించు GL_EXT_raster_multisample 1
#నిర్వచించు GL_RASTER_MULTISAMPLE_EXT         0x9327
#నిర్వచించు GL_RASTER_SAMPLES_EXT             0x9328
#నిర్వచించు GL_MAX_RASTER_SAMPLES_EXT         0x9329
#నిర్వచించు GL_RASTER_FIXED_SAMPLE_LOCATIONS_EXT 0x932A
#నిర్వచించు GL_MULTISAMPLE_RASTERIZATION_ALLOWED_EXT 0x932B
#నిర్వచించు GL_EFFECTIVE_RASTER_SAMPLES_EXT   0x932C
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLRASTERSAMPLESEXTPROC) (GLuint samples, GLboolean fixedsamplelocations);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glRasterSamplesEXT (GLuint samples, GLboolean fixedsamplelocations);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_raster_multisample */

#నిర్వచితం_కాకపోతే GL_EXT_read_format_bgra
#నిర్వచించు GL_EXT_read_format_bgra 1
#నిర్వచించు GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT 0x8365
#నిర్వచించు GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT 0x8366
#అయితే_ముగింపు /* GL_EXT_read_format_bgra */

#నిర్వచితం_కాకపోతే GL_EXT_render_snorm
#నిర్వచించు GL_EXT_render_snorm 1
#నిర్వచించు GL_R8_SNORM                       0x8F94
#నిర్వచించు GL_RG8_SNORM                      0x8F95
#నిర్వచించు GL_RGBA8_SNORM                    0x8F97
#నిర్వచించు GL_R16_SNORM_EXT                  0x8F98
#నిర్వచించు GL_RG16_SNORM_EXT                 0x8F99
#నిర్వచించు GL_RGBA16_SNORM_EXT               0x8F9B
#అయితే_ముగింపు /* GL_EXT_render_snorm */

#నిర్వచితం_కాకపోతే GL_EXT_robustness
#నిర్వచించు GL_EXT_robustness 1
#నిర్వచించు GL_GUILTY_CONTEXT_RESET_EXT       0x8253
#నిర్వచించు GL_INNOCENT_CONTEXT_RESET_EXT     0x8254
#నిర్వచించు GL_UNKNOWN_CONTEXT_RESET_EXT      0x8255
#నిర్వచించు GL_CONTEXT_ROBUST_ACCESS_EXT      0x90F3
#నిర్వచించు GL_RESET_NOTIFICATION_STRATEGY_EXT 0x8256
#నిర్వచించు GL_LOSE_CONTEXT_ON_RESET_EXT      0x8252
#నిర్వచించు GL_NO_RESET_NOTIFICATION_EXT      0x8261
రకనిర్వచనం GLenum (GL_APIENTRYP PFNGLGETGRAPHICSRESETSTATUSEXTPROC) (శూన్య);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLREADNPIXELSEXTPROC) (GLint x, GLint y, GLsizei వెడల్పు, GLsizei ఎత్తు, GLenum format, GLenum type, GLsizei buf_కొలత, శూన్య *దత్తాంశం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETNUNIFORMFVEXTPROC) (GLuint కార్యక్రమం, GLint location, GLsizei buf_కొలత, GLfloat *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETNUNIFORMIVEXTPROC) (GLuint కార్యక్రమం, GLint location, GLsizei buf_కొలత, GLint *params);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL GLenum GL_APIENTRY gl_Get_Graphics_Reset_స్థితి_EXT (శూన్య);
GL_APICALL శూన్య GL_APIENTRY glReadnPixelsEXT (GLint x, GLint y, GLsizei వెడల్పు, GLsizei ఎత్తు, GLenum format, GLenum type, GLsizei buf_కొలత, శూన్య *దత్తాంశం);
GL_APICALL శూన్య GL_APIENTRY glGetnUniformfvEXT (GLuint కార్యక్రమం, GLint location, GLsizei buf_కొలత, GLfloat *params);
GL_APICALL శూన్య GL_APIENTRY glGetnUniformivEXT (GLuint కార్యక్రమం, GLint location, GLsizei buf_కొలత, GLint *params);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_robustness */

#నిర్వచితం_కాకపోతే GL_EXT_sRGB
#నిర్వచించు GL_EXT_sRGB 1
#నిర్వచించు GL_SRGB_EXT                       0x8C40
#నిర్వచించు GL_SRGB_ALPHA_EXT                 0x8C42
#నిర్వచించు GL_SRGB8_ALPHA8_EXT               0x8C43
#నిర్వచించు GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING_EXT 0x8210
#అయితే_ముగింపు /* GL_EXT_sRGB */

#నిర్వచితం_కాకపోతే GL_EXT_sRGB_write_control
#నిర్వచించు GL_EXT_sRGB_write_control 1
#నిర్వచించు GL_FRAMEBUFFER_SRGB_EXT           0x8DB9
#అయితే_ముగింపు /* GL_EXT_sRGB_write_control */

#నిర్వచితం_కాకపోతే GL_EXT_semaphore
#నిర్వచించు GL_EXT_semaphore 1
#నిర్వచించు GL_LAYOUT_GENERAL_EXT             0x958D
#నిర్వచించు GL_LAYOUT_COLOR_ATTACHMENT_EXT    0x958E
#నిర్వచించు GL_LAYOUT_లోతు_STENCIL_ATTACHMENT_EXT 0x958F
#నిర్వచించు GL_LAYOUT_లోతు_STENCIL_READ_ONLY_EXT 0x9590
#నిర్వచించు GL_LAYOUT_SHADER_READ_ONLY_EXT    0x9591
#నిర్వచించు GL_LAYOUT_TRANSFER_SRC_EXT        0x9592
#నిర్వచించు GL_LAYOUT_TRANSFER_DST_EXT        0x9593
#నిర్వచించు GL_LAYOUT_లోతు_READ_ONLY_STENCIL_ATTACHMENT_EXT 0x9530
#నిర్వచించు GL_LAYOUT_లోతు_ATTACHMENT_STENCIL_READ_ONLY_EXT 0x9531
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGENSEMAPHORESEXTPROC) (GLsizei n, GLuint *semaphores);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDELETESEMAPHORESEXTPROC) (GLsizei n, స్థిరరాశి GLuint *semaphores);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLISSEMAPHOREEXTPROC) (GLuint semaphore);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSEMAPHOREPARAMETERUI64VEXTPROC) (GLuint semaphore, GLenum pname, స్థిరరాశి GLuint64 *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETSEMAPHOREPARAMETERUI64VEXTPROC) (GLuint semaphore, GLenum pname, GLuint64 *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLWAITSEMAPHOREEXTPROC) (GLuint semaphore, GLuint అంకె_బఫరు_Barriers, స్థిరరాశి GLuint *buffers, GLuint అంకె_Texture_Barriers, స్థిరరాశి GLuint *textures, స్థిరరాశి GLenum *srcLayouts);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSIGNALSEMAPHOREEXTPROC) (GLuint semaphore, GLuint అంకె_బఫరు_Barriers, స్థిరరాశి GLuint *buffers, GLuint అంకె_Texture_Barriers, స్థిరరాశి GLuint *textures, స్థిరరాశి GLenum *dstLayouts);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glGenSemaphoresEXT (GLsizei n, GLuint *semaphores);
GL_APICALL శూన్య GL_APIENTRY glDeleteSemaphoresEXT (GLsizei n, స్థిరరాశి GLuint *semaphores);
GL_APICALL GLboolean GL_APIENTRY glIsSemaphoreEXT (GLuint semaphore);
GL_APICALL శూన్య GL_APIENTRY glSemaphoreParameterui64vEXT (GLuint semaphore, GLenum pname, స్థిరరాశి GLuint64 *params);
GL_APICALL శూన్య GL_APIENTRY glGetSemaphoreParameterui64vEXT (GLuint semaphore, GLenum pname, GLuint64 *params);
GL_APICALL శూన్య GL_APIENTRY glWaitSemaphoreEXT (GLuint semaphore, GLuint అంకె_బఫరు_Barriers, స్థిరరాశి GLuint *buffers, GLuint అంకె_Texture_Barriers, స్థిరరాశి GLuint *textures, స్థిరరాశి GLenum *srcLayouts);
GL_APICALL శూన్య GL_APIENTRY glSignalSemaphoreEXT (GLuint semaphore, GLuint అంకె_బఫరు_Barriers, స్థిరరాశి GLuint *buffers, GLuint అంకె_Texture_Barriers, స్థిరరాశి GLuint *textures, స్థిరరాశి GLenum *dstLayouts);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_semaphore */

#నిర్వచితం_కాకపోతే GL_EXT_semaphore_fd
#నిర్వచించు GL_EXT_semaphore_fd 1
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLIMPORTSEMAPHOREFDEXTPROC) (GLuint semaphore, GLenum handleType, GLint fd);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glImportSemaphoreFdEXT (GLuint semaphore, GLenum handleType, GLint fd);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_semaphore_fd */

#నిర్వచితం_కాకపోతే GL_EXT_semaphore_win32
#నిర్వచించు GL_EXT_semaphore_win32 1
#నిర్వచించు GL_HANDLE_TYPE_D3D12_FENCE_EXT    0x9594
#నిర్వచించు GL_D3_D12_FENCE_విలువ_EXT          0x9595
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLIMPORTSEMAPHOREWIN32HANDLEEXTPROC) (GLuint semaphore, GLenum handleType, శూన్య *handle);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLIMPORTSEMAPHOREWIN32NAMEEXTPROC) (GLuint semaphore, GLenum handleType, స్థిరరాశి శూన్య *name);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glImportSemaphoreWin32HandleEXT (GLuint semaphore, GLenum handleType, శూన్య *handle);
GL_APICALL శూన్య GL_APIENTRY glImportSemaphoreWin32NameEXT (GLuint semaphore, GLenum handleType, స్థిరరాశి శూన్య *name);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_semaphore_win32 */

#నిర్వచితం_కాకపోతే GL_EXT_separate_లోతు_stencil
#నిర్వచించు GL_EXT_separate_లోతు_stencil 1
#అయితే_ముగింపు /* GL_EXT_separate_depth_stencil */

#నిర్వచితం_కాకపోతే GL_EXT_separate_shader_objects
#నిర్వచించు GL_EXT_separate_shader_objects 1
#నిర్వచించు GL_చురుకైన_కార్యక్రమం_EXT             0x8259
#నిర్వచించు GL_శీర్షం_SHADER_బిట్టు_EXT          0x00000001
#నిర్వచించు GL_FRAGMENT_SHADER_బిట్టు_EXT        0x00000002
#నిర్వచించు GL_ALL_SHADER_బిట్లు_EXT            0xFFFFFFFF
#నిర్వచించు GL_కార్యక్రమం_SEPARABLE_EXT          0x8258
#నిర్వచించు GL_కార్యక్రమం_PIPELINE_BINDING_EXT   0x825A
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLACTIVESHADERPROGRAMEXTPROC) (GLuint pipeline, GLuint కార్యక్రమం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBINDPROGRAMPIPELINEEXTPROC) (GLuint pipeline);
రకనిర్వచనం GLuint (GL_APIENTRYP PFNGLCREATESHADERPROGRAMVEXTPROC) (GLenum type, GLsizei లెక్క, స్థిరరాశి GLchar *స్థిరరాశి*అక్షరశ్రేణులు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDELETEPROGRAMPIPELINESEXTPROC) (GLsizei n, స్థిరరాశి GLuint *pipelines);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGENPROGRAMPIPELINESEXTPROC) (GLsizei n, GLuint *pipelines);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETPROGRAMPIPELINEINFOLOGEXTPROC) (GLuint pipeline, GLsizei buf_కొలత, GLsizei *నిడివి, GLchar *infoLog);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETPROGRAMPIPELINEIVEXTPROC) (GLuint pipeline, GLenum pname, GLint *params);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLISPROGRAMPIPELINEEXTPROC) (GLuint pipeline);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMPARAMETERIEXTPROC) (GLuint కార్యక్రమం, GLenum pname, GLint విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM1FEXTPROC) (GLuint కార్యక్రమం, GLint location, GLfloat v0);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM1FVEXTPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM1IEXTPROC) (GLuint కార్యక్రమం, GLint location, GLint v0);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM1IVEXTPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLint *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM2FEXTPROC) (GLuint కార్యక్రమం, GLint location, GLfloat v0, GLfloat v1);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM2FVEXTPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM2IEXTPROC) (GLuint కార్యక్రమం, GLint location, GLint v0, GLint v1);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM2IVEXTPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLint *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM3FEXTPROC) (GLuint కార్యక్రమం, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM3FVEXTPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM3IEXTPROC) (GLuint కార్యక్రమం, GLint location, GLint v0, GLint v1, GLint v2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM3IVEXTPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLint *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM4FEXTPROC) (GLuint కార్యక్రమం, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM4FVEXTPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM4IEXTPROC) (GLuint కార్యక్రమం, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM4IVEXTPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLint *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUSEPROGRAMSTAGESEXTPROC) (GLuint pipeline, GLbitfield stages, GLuint కార్యక్రమం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLVALIDATEPROGRAMPIPELINEEXTPROC) (GLuint pipeline);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UIEXTPROC) (GLuint కార్యక్రమం, GLint location, GLuint v0);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UIEXTPROC) (GLuint కార్యక్రమం, GLint location, GLuint v0, GLuint v1);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UIEXTPROC) (GLuint కార్యక్రమం, GLint location, GLuint v0, GLuint v1, GLuint v2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UIEXTPROC) (GLuint కార్యక్రమం, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UIVEXTPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLuint *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UIVEXTPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLuint *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UIVEXTPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLuint *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UIVEXTPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLuint *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_చురుకైన_Shader_కార్యక్రమం_EXT (GLuint pipeline, GLuint కార్యక్రమం);
GL_APICALL శూన్య GL_APIENTRY gl_Bind_కార్యక్రమం_Pipeline_EXT (GLuint pipeline);
GL_APICALL GLuint GL_APIENTRY glCreateShaderProgramvEXT (GLenum type, GLsizei లెక్క, స్థిరరాశి GLchar *స్థిరరాశి*అక్షరశ్రేణులు);
GL_APICALL శూన్య GL_APIENTRY gl_Delete_కార్యక్రమం_Pipelines_EXT (GLsizei n, స్థిరరాశి GLuint *pipelines);
GL_APICALL శూన్య GL_APIENTRY gl_Gen_కార్యక్రమం_Pipelines_EXT (GLsizei n, GLuint *pipelines);
GL_APICALL శూన్య GL_APIENTRY gl_Get_కార్యక్రమం_Pipeline_Info_Log_EXT (GLuint pipeline, GLsizei buf_కొలత, GLsizei *నిడివి, GLchar *infoLog);
GL_APICALL శూన్య GL_APIENTRY gl_Get_కార్యక్రమం_Pipelineiv_EXT (GLuint pipeline, GLenum pname, GLint *params);
GL_APICALL GLboolean GL_APIENTRY gl_Is_కార్యక్రమం_Pipeline_EXT (GLuint pipeline);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Parameteri_EXT (GLuint కార్యక్రమం, GLenum pname, GLint విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform1f_EXT (GLuint కార్యక్రమం, GLint location, GLfloat v0);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform1fv_EXT (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform1i_EXT (GLuint కార్యక్రమం, GLint location, GLint v0);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform1iv_EXT (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLint *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform2f_EXT (GLuint కార్యక్రమం, GLint location, GLfloat v0, GLfloat v1);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform2fv_EXT (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform2i_EXT (GLuint కార్యక్రమం, GLint location, GLint v0, GLint v1);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform2iv_EXT (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLint *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform3f_EXT (GLuint కార్యక్రమం, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform3fv_EXT (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform3i_EXT (GLuint కార్యక్రమం, GLint location, GLint v0, GLint v1, GLint v2);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform3iv_EXT (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLint *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform4f_EXT (GLuint కార్యక్రమం, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform4fv_EXT (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform4i_EXT (GLuint కార్యక్రమం, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform4iv_EXT (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLint *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_ఏకరీతి_Matrix2fv_EXT (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_ఏకరీతి_Matrix3fv_EXT (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_ఏకరీతి_Matrix4fv_EXT (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_Use_కార్యక్రమం_Stages_EXT (GLuint pipeline, GLbitfield stages, GLuint కార్యక్రమం);
GL_APICALL శూన్య GL_APIENTRY gl_Validate_కార్యక్రమం_Pipeline_EXT (GLuint pipeline);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform1ui_EXT (GLuint కార్యక్రమం, GLint location, GLuint v0);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform2ui_EXT (GLuint కార్యక్రమం, GLint location, GLuint v0, GLuint v1);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform3ui_EXT (GLuint కార్యక్రమం, GLint location, GLuint v0, GLuint v1, GLuint v2);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform4ui_EXT (GLuint కార్యక్రమం, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform1uiv_EXT (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLuint *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform2uiv_EXT (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLuint *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform3uiv_EXT (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLuint *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform4uiv_EXT (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLuint *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_ఏకరీతి_Matrix2x3fv_EXT (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_ఏకరీతి_Matrix3x2fv_EXT (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_ఏకరీతి_Matrix2x4fv_EXT (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_ఏకరీతి_Matrix4x2fv_EXT (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_ఏకరీతి_Matrix3x4fv_EXT (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_ఏకరీతి_Matrix4x3fv_EXT (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_separate_shader_objects */

#నిర్వచితం_కాకపోతే GL_EXT_shader_framebuffer_fetch
#నిర్వచించు GL_EXT_shader_framebuffer_fetch 1
#నిర్వచించు GL_FRAGMENT_SHADER_DISCARDS_SAMPLES_EXT 0x8A52
#అయితే_ముగింపు /* GL_EXT_shader_framebuffer_fetch */

#నిర్వచితం_కాకపోతే GL_EXT_shader_framebuffer_fetch_non_coherent
#నిర్వచించు GL_EXT_shader_framebuffer_fetch_non_coherent 1
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFRAMEBUFFERFETCHBARRIEREXTPROC) (శూన్య);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glFramebufferFetchBarrierEXT (శూన్య);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_shader_framebuffer_fetch_non_coherent */

#నిర్వచితం_కాకపోతే GL_EXT_shader_సమూహం_vote
#నిర్వచించు GL_EXT_shader_సమూహం_vote 1
#అయితే_ముగింపు /* GL_EXT_shader_group_vote */

#నిర్వచితం_కాకపోతే GL_EXT_shader_implicit_conversions
#నిర్వచించు GL_EXT_shader_implicit_conversions 1
#అయితే_ముగింపు /* GL_EXT_shader_implicit_conversions */

#నిర్వచితం_కాకపోతే GL_EXT_shader_integer_mix
#నిర్వచించు GL_EXT_shader_integer_mix 1
#అయితే_ముగింపు /* GL_EXT_shader_integer_mix */

#నిర్వచితం_కాకపోతే GL_EXT_shader_io_ఖండాలు
#నిర్వచించు GL_EXT_shader_io_ఖండాలు 1
#అయితే_ముగింపు /* GL_EXT_shader_io_blocks */

#నిర్వచితం_కాకపోతే GL_EXT_shader_non_constant_global_initializers
#నిర్వచించు GL_EXT_shader_non_constant_global_initializers 1
#అయితే_ముగింపు /* GL_EXT_shader_non_constant_global_initializers */

#నిర్వచితం_కాకపోతే GL_EXT_shader_pixel_local_storage
#నిర్వచించు GL_EXT_shader_pixel_local_storage 1
#నిర్వచించు GL_MAX_SHADER_PIXEL_LOCAL_STORAGE_FAST_కొలత_EXT 0x8F63
#నిర్వచించు GL_MAX_SHADER_PIXEL_LOCAL_STORAGE_కొలత_EXT 0x8F67
#నిర్వచించు GL_SHADER_PIXEL_LOCAL_STORAGE_EXT 0x8F64
#అయితే_ముగింపు /* GL_EXT_shader_pixel_local_storage */

#నిర్వచితం_కాకపోతే GL_EXT_shader_pixel_local_storage2
#నిర్వచించు GL_EXT_shader_pixel_local_storage2 1
#నిర్వచించు GL_MAX_SHADER_COMBINED_LOCAL_STORAGE_FAST_కొలత_EXT 0x9650
#నిర్వచించు GL_MAX_SHADER_COMBINED_LOCAL_STORAGE_కొలత_EXT 0x9651
#నిర్వచించు GL_FRAMEBUFFER_INCOMPLETE_INSUFFICIENT_SHADER_COMBINED_LOCAL_STORAGE_EXT 0x9652
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFRAMEBUFFERPIXELLOCALSTORAGESIZEEXTPROC) (GLuint లక్ష్యం, GLsizei కొలత);
రకనిర్వచనం GLsizei (GL_APIENTRYP PFNGLGETFRAMEBUFFERPIXELLOCALSTORAGESIZEEXTPROC) (GLuint లక్ష్యం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCLEARPIXELLOCALSTORAGEUIEXTPROC) (GLsizei స్థానభ్రంశం_2, GLsizei n, స్థిరరాశి GLuint *విలువలు);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_Framebuffer_Pixel_Local_Storage_కొలత_EXT (GLuint లక్ష్యం, GLsizei కొలత);
GL_APICALL GLsizei GL_APIENTRY gl_Get_Framebuffer_Pixel_Local_Storage_కొలత_EXT (GLuint లక్ష్యం);
GL_APICALL శూన్య GL_APIENTRY glClearPixelLocalStorageuiEXT (GLsizei స్థానభ్రంశం_2, GLsizei n, స్థిరరాశి GLuint *విలువలు);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_shader_pixel_local_storage2 */

#నిర్వచితం_కాకపోతే GL_EXT_shader_samples_identical
#నిర్వచించు GL_EXT_shader_samples_identical 1
#అయితే_ముగింపు /* GL_EXT_shader_samples_identical */

#నిర్వచితం_కాకపోతే GL_EXT_shader_texture_lod
#నిర్వచించు GL_EXT_shader_texture_lod 1
#అయితే_ముగింపు /* GL_EXT_shader_texture_lod */

#నిర్వచితం_కాకపోతే GL_EXT_shader_texture_samples
#నిర్వచించు GL_EXT_shader_texture_samples 1
#అయితే_ముగింపు /* GL_EXT_shader_texture_samples */

#నిర్వచితం_కాకపోతే GL_EXT_shadow_samplers
#నిర్వచించు GL_EXT_shadow_samplers 1
#నిర్వచించు GL_TEXTURE_COMPARE_బహుళకం_EXT       0x884C
#నిర్వచించు GL_TEXTURE_COMPARE_FUNC_EXT       0x884D
#నిర్వచించు GL_COMPARE_REF_గమ్యం_TEXTURE_EXT     0x884E
#నిర్వచించు GL_SAMPLER_2D_SHADOW_EXT          0x8B62
#అయితే_ముగింపు /* GL_EXT_shadow_samplers */

#నిర్వచితం_కాకపోతే GL_EXT_sparse_texture
#నిర్వచించు GL_EXT_sparse_texture 1
#నిర్వచించు GL_TEXTURE_SPARSE_EXT             0x91A6
#నిర్వచించు GL_VIRTUAL_పుట_కొలత_సూచీ_EXT    0x91A7
#నిర్వచించు GL_అంకె_SPARSE_స్థాయిలు_EXT          0x91AA
#నిర్వచించు GL_అంకె_VIRTUAL_పుట_SIZES_EXT     0x91A8
#నిర్వచించు GL_VIRTUAL_పుట_కొలత_X_EXT        0x9195
#నిర్వచించు GL_VIRTUAL_పుట_కొలత_Y_EXT        0x9196
#నిర్వచించు GL_VIRTUAL_పుట_కొలత_Z_EXT        0x9197
#నిర్వచించు GL_TEXTURE_2D_ARRAY               0x8C1A
#నిర్వచించు GL_TEXTURE_3D                     0x806F
#నిర్వచించు GL_MAX_SPARSE_TEXTURE_కొలత_EXT    0x9198
#నిర్వచించు GL_MAX_SPARSE_3_D_TEXTURE_కొలత_EXT 0x9199
#నిర్వచించు GL_MAX_SPARSE_ARRAY_TEXTURE_LAYERS_EXT 0x919A
#నిర్వచించు GL_SPARSE_TEXTURE_నిండిన_ARRAY_CUBE_MIPMAPS_EXT 0x91A9
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXPAGECOMMITMENTEXTPROC) (GLenum లక్ష్యం, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLboolean commit);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_Tex_పుట_Commitment_EXT (GLenum లక్ష్యం, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLboolean commit);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_sparse_texture */

#నిర్వచితం_కాకపోతే GL_EXT_sparse_texture2
#నిర్వచించు GL_EXT_sparse_texture2 1
#అయితే_ముగింపు /* GL_EXT_sparse_texture2 */

#నిర్వచితం_కాకపోతే GL_EXT_tessellation_బిందువు_కొలత
#నిర్వచించు GL_EXT_tessellation_బిందువు_కొలత 1
#అయితే_ముగింపు /* GL_EXT_tessellation_point_size */

#నిర్వచితం_కాకపోతే GL_EXT_tessellation_shader
#నిర్వచించు GL_EXT_tessellation_shader 1
#నిర్వచించు GL_PATCHES_EXT                    0x000E
#నిర్వచించు GL_PATCH_VERTICES_EXT             0x8E72
#నిర్వచించు GL_TESS_CONTROL_OUTPUT_VERTICES_EXT 0x8E75
#నిర్వచించు GL_TESS_GEN_బహుళకం_EXT              0x8E76
#నిర్వచించు GL_TESS_GEN_SPACING_EXT           0x8E77
#నిర్వచించు GL_TESS_GEN_శీర్షం_క్రమం_EXT      0x8E78
#నిర్వచించు GL_TESS_GEN_బిందువు_బహుళకం_EXT        0x8E79
#నిర్వచించు GL_ISOLINES_EXT                   0x8E7A
#నిర్వచించు GL_QUADS_EXT                      0x0007
#నిర్వచించు GL_FRACTIONAL_ODD_EXT             0x8E7B
#నిర్వచించు GL_FRACTIONAL_EVEN_EXT            0x8E7C
#నిర్వచించు GL_MAX_PATCH_VERTICES_EXT         0x8E7D
#నిర్వచించు GL_MAX_TESS_GEN_LEVEL_EXT         0x8E7E
#నిర్వచించు GL_MAX_TESS_CONTROL_ఏకరీతి_COMPONENTS_EXT 0x8E7F
#నిర్వచించు GL_MAX_TESS_EVALUATION_ఏకరీతి_COMPONENTS_EXT 0x8E80
#నిర్వచించు GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS_EXT 0x8E81
#నిర్వచించు GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS_EXT 0x8E82
#నిర్వచించు GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS_EXT 0x8E83
#నిర్వచించు GL_MAX_TESS_PATCH_COMPONENTS_EXT  0x8E84
#నిర్వచించు GL_MAX_TESS_CONTROL_మొత్తం_OUTPUT_COMPONENTS_EXT 0x8E85
#నిర్వచించు GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS_EXT 0x8E86
#నిర్వచించు GL_MAX_TESS_CONTROL_ఏకరీతి_ఖండాలు_EXT 0x8E89
#నిర్వచించు GL_MAX_TESS_EVALUATION_ఏకరీతి_ఖండాలు_EXT 0x8E8A
#నిర్వచించు GL_MAX_TESS_CONTROL_ఆదానం_COMPONENTS_EXT 0x886C
#నిర్వచించు GL_MAX_TESS_EVALUATION_ఆదానం_COMPONENTS_EXT 0x886D
#నిర్వచించు GL_MAX_COMBINED_TESS_CONTROL_ఏకరీతి_COMPONENTS_EXT 0x8E1E
#నిర్వచించు GL_MAX_COMBINED_TESS_EVALUATION_ఏకరీతి_COMPONENTS_EXT 0x8E1F
#నిర్వచించు GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS_EXT 0x92CD
#నిర్వచించు GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS_EXT 0x92CE
#నిర్వచించు GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS_EXT 0x92D3
#నిర్వచించు GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS_EXT 0x92D4
#నిర్వచించు GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS_EXT 0x90CB
#నిర్వచించు GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS_EXT 0x90CC
#నిర్వచించు GL_MAX_TESS_CONTROL_SHADER_STORAGE_ఖండాలు_EXT 0x90D8
#నిర్వచించు GL_MAX_TESS_EVALUATION_SHADER_STORAGE_ఖండాలు_EXT 0x90D9
#నిర్వచించు GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED 0x8221
#నిర్వచించు GL_IS_చొప్పున_PATCH_EXT               0x92E7
#నిర్వచించు GL_REFERENCED_BY_TESS_CONTROL_SHADER_EXT 0x9307
#నిర్వచించు GL_REFERENCED_BY_TESS_EVALUATION_SHADER_EXT 0x9308
#నిర్వచించు GL_TESS_CONTROL_SHADER_EXT        0x8E88
#నిర్వచించు GL_TESS_EVALUATION_SHADER_EXT     0x8E87
#నిర్వచించు GL_TESS_CONTROL_SHADER_బిట్టు_EXT    0x00000008
#నిర్వచించు GL_TESS_EVALUATION_SHADER_బిట్టు_EXT 0x00000010
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPATCHPARAMETERIEXTPROC) (GLenum pname, GLint విలువ);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glPatchParameteriEXT (GLenum pname, GLint విలువ);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_tessellation_shader */

#నిర్వచితం_కాకపోతే GL_EXT_texture_border_clamp
#నిర్వచించు GL_EXT_texture_border_clamp 1
#నిర్వచించు GL_TEXTURE_BORDER_COLOR_EXT       0x1004
#నిర్వచించు GL_CLAMP_గమ్యం_BORDER_EXT            0x812D
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXPARAMETERIIVEXTPROC) (GLenum లక్ష్యం, GLenum pname, స్థిరరాశి GLint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXPARAMETERIUIVEXTPROC) (GLenum లక్ష్యం, GLenum pname, స్థిరరాశి GLuint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETTEXPARAMETERIIVEXTPROC) (GLenum లక్ష్యం, GLenum pname, GLint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETTEXPARAMETERIUIVEXTPROC) (GLenum లక్ష్యం, GLenum pname, GLuint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSAMPLERPARAMETERIIVEXTPROC) (GLuint sampler, GLenum pname, స్థిరరాశి GLint *param);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSAMPLERPARAMETERIUIVEXTPROC) (GLuint sampler, GLenum pname, స్థిరరాశి GLuint *param);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIIVEXTPROC) (GLuint sampler, GLenum pname, GLint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIUIVEXTPROC) (GLuint sampler, GLenum pname, GLuint *params);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glTexParameterIivEXT (GLenum లక్ష్యం, GLenum pname, స్థిరరాశి GLint *params);
GL_APICALL శూన్య GL_APIENTRY glTexParameterIuivEXT (GLenum లక్ష్యం, GLenum pname, స్థిరరాశి GLuint *params);
GL_APICALL శూన్య GL_APIENTRY glGetTexParameterIivEXT (GLenum లక్ష్యం, GLenum pname, GLint *params);
GL_APICALL శూన్య GL_APIENTRY glGetTexParameterIuivEXT (GLenum లక్ష్యం, GLenum pname, GLuint *params);
GL_APICALL శూన్య GL_APIENTRY glSamplerParameterIivEXT (GLuint sampler, GLenum pname, స్థిరరాశి GLint *param);
GL_APICALL శూన్య GL_APIENTRY glSamplerParameterIuivEXT (GLuint sampler, GLenum pname, స్థిరరాశి GLuint *param);
GL_APICALL శూన్య GL_APIENTRY glGetSamplerParameterIivEXT (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL శూన్య GL_APIENTRY glGetSamplerParameterIuivEXT (GLuint sampler, GLenum pname, GLuint *params);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_texture_border_clamp */

#నిర్వచితం_కాకపోతే GL_EXT_texture_బఫరు
#నిర్వచించు GL_EXT_texture_బఫరు 1
#నిర్వచించు GL_TEXTURE_బఫరు_EXT             0x8C2A
#నిర్వచించు GL_TEXTURE_బఫరు_BINDING_EXT     0x8C2A
#నిర్వచించు GL_MAX_TEXTURE_బఫరు_కొలత_EXT    0x8C2B
#నిర్వచించు GL_TEXTURE_BINDING_బఫరు_EXT     0x8C2C
#నిర్వచించు GL_TEXTURE_బఫరు_దత్తాంశం_STORE_BINDING_EXT 0x8C2D
#నిర్వచించు GL_TEXTURE_బఫరు_స్థానభ్రంశం_ALIGNMENT_EXT 0x919F
#నిర్వచించు GL_SAMPLER_బఫరు_EXT             0x8DC2
#నిర్వచించు GL_INT_SAMPLER_బఫరు_EXT         0x8DD0
#నిర్వచించు GL_UNSIGNED_INT_SAMPLER_బఫరు_EXT 0x8DD8
#నిర్వచించు GL_IMAGE_బఫరు_EXT               0x9051
#నిర్వచించు GL_INT_IMAGE_బఫరు_EXT           0x905C
#నిర్వచించు GL_UNSIGNED_INT_IMAGE_బఫరు_EXT  0x9067
#నిర్వచించు GL_TEXTURE_బఫరు_స్థానభ్రంశం_EXT      0x919D
#నిర్వచించు GL_TEXTURE_బఫరు_కొలత_EXT        0x919E
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXBUFFEREXTPROC) (GLenum లక్ష్యం, GLenum internalformat, GLuint బఫరు_2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXBUFFERRANGEEXTPROC) (GLenum లక్ష్యం, GLenum internalformat, GLuint బఫరు_2, GLintptr స్థానభ్రంశం_2, GLsizeiptr కొలత);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_Tex_బఫరు_EXT (GLenum లక్ష్యం, GLenum internalformat, GLuint బఫరు_2);
GL_APICALL శూన్య GL_APIENTRY gl_Tex_బఫరు_Range_EXT (GLenum లక్ష్యం, GLenum internalformat, GLuint బఫరు_2, GLintptr స్థానభ్రంశం_2, GLsizeiptr కొలత);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_texture_buffer */

#నిర్వచితం_కాకపోతే GL_EXT_texture_compression_astc_decode_బహుళకం
#నిర్వచించు GL_EXT_texture_compression_astc_decode_బహుళకం 1
#నిర్వచించు GL_TEXTURE_ASTC_DECODE_PRECISION_EXT 0x8F69
#అయితే_ముగింపు /* GL_EXT_texture_compression_astc_decode_mode */

#నిర్వచితం_కాకపోతే GL_EXT_texture_compression_bptc
#నిర్వచించు GL_EXT_texture_compression_bptc 1
#నిర్వచించు GL_COMPRESSED_RGBA_BPTC_UNORM_EXT 0x8E8C
#నిర్వచించు GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_EXT 0x8E8D
#నిర్వచించు GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_EXT 0x8E8E
#నిర్వచించు GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_EXT 0x8E8F
#అయితే_ముగింపు /* GL_EXT_texture_compression_bptc */

#నిర్వచితం_కాకపోతే GL_EXT_texture_compression_dxt1
#నిర్వచించు GL_EXT_texture_compression_dxt1 1
#నిర్వచించు GL_COMPRESSED_RGB_S3TC_DXT1_EXT   0x83F0
#నిర్వచించు GL_COMPRESSED_RGBA_S3TC_DXT1_EXT  0x83F1
#అయితే_ముగింపు /* GL_EXT_texture_compression_dxt1 */

#నిర్వచితం_కాకపోతే GL_EXT_texture_compression_rgtc
#నిర్వచించు GL_EXT_texture_compression_rgtc 1
#నిర్వచించు GL_COMPRESSED_RED_RGTC1_EXT       0x8DBB
#నిర్వచించు GL_COMPRESSED_SIGNED_RED_RGTC1_EXT 0x8DBC
#నిర్వచించు GL_COMPRESSED_RED_GREEN_RGTC2_EXT 0x8DBD
#నిర్వచించు GL_COMPRESSED_SIGNED_RED_GREEN_RGTC2_EXT 0x8DBE
#అయితే_ముగింపు /* GL_EXT_texture_compression_rgtc */

#నిర్వచితం_కాకపోతే GL_EXT_texture_compression_s3tc
#నిర్వచించు GL_EXT_texture_compression_s3tc 1
#నిర్వచించు GL_COMPRESSED_RGBA_S3TC_DXT3_EXT  0x83F2
#నిర్వచించు GL_COMPRESSED_RGBA_S3TC_DXT5_EXT  0x83F3
#అయితే_ముగింపు /* GL_EXT_texture_compression_s3tc */

#నిర్వచితం_కాకపోతే GL_EXT_texture_compression_s3tc_srgb
#నిర్వచించు GL_EXT_texture_compression_s3tc_srgb 1
#నిర్వచించు GL_COMPRESSED_SRGB_S3TC_DXT1_EXT  0x8C4C
#నిర్వచించు GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT 0x8C4D
#నిర్వచించు GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT 0x8C4E
#నిర్వచించు GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT 0x8C4F
#అయితే_ముగింపు /* GL_EXT_texture_compression_s3tc_srgb */

#నిర్వచితం_కాకపోతే GL_EXT_texture_cube_map_array
#నిర్వచించు GL_EXT_texture_cube_map_array 1
#నిర్వచించు GL_TEXTURE_CUBE_MAP_ARRAY_EXT     0x9009
#నిర్వచించు GL_TEXTURE_BINDING_CUBE_MAP_ARRAY_EXT 0x900A
#నిర్వచించు GL_SAMPLER_CUBE_MAP_ARRAY_EXT     0x900C
#నిర్వచించు GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW_EXT 0x900D
#నిర్వచించు GL_INT_SAMPLER_CUBE_MAP_ARRAY_EXT 0x900E
#నిర్వచించు GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY_EXT 0x900F
#నిర్వచించు GL_IMAGE_CUBE_MAP_ARRAY_EXT       0x9054
#నిర్వచించు GL_INT_IMAGE_CUBE_MAP_ARRAY_EXT   0x905F
#నిర్వచించు GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY_EXT 0x906A
#అయితే_ముగింపు /* GL_EXT_texture_cube_map_array */

#నిర్వచితం_కాకపోతే GL_EXT_texture_filter_anisotropic
#నిర్వచించు GL_EXT_texture_filter_anisotropic 1
#నిర్వచించు GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#నిర్వచించు GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#అయితే_ముగింపు /* GL_EXT_texture_filter_anisotropic */

#నిర్వచితం_కాకపోతే GL_EXT_texture_filter_minmax
#నిర్వచించు GL_EXT_texture_filter_minmax 1
#నిర్వచించు GL_TEXTURE_REDUCTION_బహుళకం_EXT     0x9366
#నిర్వచించు GL_WEIGHTED_సరాసరి_EXT           0x9367
#అయితే_ముగింపు /* GL_EXT_texture_filter_minmax */

#నిర్వచితం_కాకపోతే GL_EXT_texture_format_BGRA8888
#నిర్వచించు GL_EXT_texture_format_BGRA8888 1
#అయితే_ముగింపు /* GL_EXT_texture_format_BGRA8888 */

#నిర్వచితం_కాకపోతే GL_EXT_texture_format_sRGB_override
#నిర్వచించు GL_EXT_texture_format_sRGB_override 1
#నిర్వచించు GL_TEXTURE_FORMAT_SRGB_OVERRIDE_EXT 0x8FBF
#అయితే_ముగింపు /* GL_EXT_texture_format_sRGB_override */

#నిర్వచితం_కాకపోతే GL_EXT_texture_mirror_clamp_గమ్యం_అంచు
#నిర్వచించు GL_EXT_texture_mirror_clamp_గమ్యం_అంచు 1
#నిర్వచించు GL_MIRROR_CLAMP_గమ్యం_అంచు_EXT       0x8743
#అయితే_ముగింపు /* GL_EXT_texture_mirror_clamp_to_edge */

#నిర్వచితం_కాకపోతే GL_EXT_texture_norm16
#నిర్వచించు GL_EXT_texture_norm16 1
#నిర్వచించు GL_R16_EXT                        0x822A
#నిర్వచించు GL_RG16_EXT                       0x822C
#నిర్వచించు GL_RGBA16_EXT                     0x805B
#నిర్వచించు GL_RGB16_EXT                      0x8054
#నిర్వచించు GL_RGB16_SNORM_EXT                0x8F9A
#అయితే_ముగింపు /* GL_EXT_texture_norm16 */

#నిర్వచితం_కాకపోతే GL_EXT_texture_query_lod
#నిర్వచించు GL_EXT_texture_query_lod 1
#అయితే_ముగింపు /* GL_EXT_texture_query_lod */

#నిర్వచితం_కాకపోతే GL_EXT_texture_rg
#నిర్వచించు GL_EXT_texture_rg 1
#నిర్వచించు GL_RED_EXT                        0x1903
#నిర్వచించు GL_RG_EXT                         0x8227
#నిర్వచించు GL_R8_EXT                         0x8229
#నిర్వచించు GL_RG8_EXT                        0x822B
#అయితే_ముగింపు /* GL_EXT_texture_rg */

#నిర్వచితం_కాకపోతే GL_EXT_texture_sRGB_R8
#నిర్వచించు GL_EXT_texture_sRGB_R8 1
#నిర్వచించు GL_SR8_EXT                        0x8FBD
#అయితే_ముగింపు /* GL_EXT_texture_sRGB_R8 */

#నిర్వచితం_కాకపోతే GL_EXT_texture_sRGB_RG8
#నిర్వచించు GL_EXT_texture_sRGB_RG8 1
#నిర్వచించు GL_SRG8_EXT                       0x8FBE
#అయితే_ముగింపు /* GL_EXT_texture_sRGB_RG8 */

#నిర్వచితం_కాకపోతే GL_EXT_texture_sRGB_decode
#నిర్వచించు GL_EXT_texture_sRGB_decode 1
#నిర్వచించు GL_TEXTURE_SRGB_DECODE_EXT        0x8A48
#నిర్వచించు GL_DECODE_EXT                     0x8A49
#నిర్వచించు GL_SKIP_DECODE_EXT                0x8A4A
#అయితే_ముగింపు /* GL_EXT_texture_sRGB_decode */

#నిర్వచితం_కాకపోతే GL_EXT_texture_shadow_lod
#నిర్వచించు GL_EXT_texture_shadow_lod 1
#అయితే_ముగింపు /* GL_EXT_texture_shadow_lod */

#నిర్వచితం_కాకపోతే GL_EXT_texture_storage
#నిర్వచించు GL_EXT_texture_storage 1
#నిర్వచించు GL_TEXTURE_IMMUTABLE_FORMAT_EXT   0x912F
#నిర్వచించు GL_ALPHA8_EXT                     0x803C
#నిర్వచించు GL_LUMINANCE8_EXT                 0x8040
#నిర్వచించు GL_LUMINANCE8_ALPHA8_EXT          0x8045
#నిర్వచించు GL_RGBA32F_EXT                    0x8814
#నిర్వచించు GL_RGB32F_EXT                     0x8815
#నిర్వచించు GL_ALPHA32F_EXT                   0x8816
#నిర్వచించు GL_LUMINANCE32F_EXT               0x8818
#నిర్వచించు GL_LUMINANCE_ALPHA32F_EXT         0x8819
#నిర్వచించు GL_ALPHA16F_EXT                   0x881C
#నిర్వచించు GL_LUMINANCE16F_EXT               0x881E
#నిర్వచించు GL_LUMINANCE_ALPHA16F_EXT         0x881F
#నిర్వచించు GL_R32F_EXT                       0x822E
#నిర్వచించు GL_RG32F_EXT                      0x8230
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXSTORAGE1DEXTPROC) (GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum internalformat, GLsizei వెడల్పు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXSTORAGE2DEXTPROC) (GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXSTORAGE3DEXTPROC) (GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXTURESTORAGE1DEXTPROC) (GLuint texture, GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum internalformat, GLsizei వెడల్పు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXTURESTORAGE2DEXTPROC) (GLuint texture, GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXTURESTORAGE3DEXTPROC) (GLuint texture, GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glTexStorage1DEXT (GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum internalformat, GLsizei వెడల్పు);
GL_APICALL శూన్య GL_APIENTRY glTexStorage2DEXT (GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
GL_APICALL శూన్య GL_APIENTRY glTexStorage3DEXT (GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2);
GL_APICALL శూన్య GL_APIENTRY glTextureStorage1DEXT (GLuint texture, GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum internalformat, GLsizei వెడల్పు);
GL_APICALL శూన్య GL_APIENTRY glTextureStorage2DEXT (GLuint texture, GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
GL_APICALL శూన్య GL_APIENTRY glTextureStorage3DEXT (GLuint texture, GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_texture_storage */

#నిర్వచితం_కాకపోతే GL_EXT_texture_storage_compression
#నిర్వచించు GL_EXT_texture_storage_compression 1
#నిర్వచించు GL_అంకె_SURFACE_COMPRESSION_FIXED_RATES_EXT 0x8F6E
#నిర్వచించు GL_SURFACE_COMPRESSION_FIXED_రేటు_1_BPC_EXT 0x96C4
#నిర్వచించు GL_SURFACE_COMPRESSION_FIXED_రేటు_2_BPC_EXT 0x96C5
#నిర్వచించు GL_SURFACE_COMPRESSION_FIXED_రేటు_3_BPC_EXT 0x96C6
#నిర్వచించు GL_SURFACE_COMPRESSION_FIXED_రేటు_4_BPC_EXT 0x96C7
#నిర్వచించు GL_SURFACE_COMPRESSION_FIXED_రేటు_5_BPC_EXT 0x96C8
#నిర్వచించు GL_SURFACE_COMPRESSION_FIXED_రేటు_6_BPC_EXT 0x96C9
#నిర్వచించు GL_SURFACE_COMPRESSION_FIXED_రేటు_7_BPC_EXT 0x96CA
#నిర్వచించు GL_SURFACE_COMPRESSION_FIXED_రేటు_8_BPC_EXT 0x96CB
#నిర్వచించు GL_SURFACE_COMPRESSION_FIXED_రేటు_9_BPC_EXT 0x96CC
#నిర్వచించు GL_SURFACE_COMPRESSION_FIXED_రేటు_10_BPC_EXT 0x96CD
#నిర్వచించు GL_SURFACE_COMPRESSION_FIXED_రేటు_11_BPC_EXT 0x96CE
#నిర్వచించు GL_SURFACE_COMPRESSION_FIXED_రేటు_12_BPC_EXT 0x96CF
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXSTORAGEATTRIBS2DEXTPROC) (GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు, స్థిరరాశి GLint* attrib_list);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXSTORAGEATTRIBS3DEXTPROC) (GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, స్థిరరాశి GLint* attrib_list);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glTexStorageAttribs2DEXT (GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు, స్థిరరాశి GLint* attrib_list);
GL_APICALL శూన్య GL_APIENTRY glTexStorageAttribs3DEXT (GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, స్థిరరాశి GLint* attrib_list);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_texture_storage_compression */

#నిర్వచితం_కాకపోతే GL_EXT_texture_type_2_10_10_10_REV
#నిర్వచించు GL_EXT_texture_type_2_10_10_10_REV 1
#నిర్వచించు GL_UNSIGNED_INT_2_10_10_10_REV_EXT 0x8368
#అయితే_ముగింపు /* GL_EXT_texture_type_2_10_10_10_REV */

#నిర్వచితం_కాకపోతే GL_EXT_texture_view
#నిర్వచించు GL_EXT_texture_view 1
#నిర్వచించు GL_TEXTURE_VIEW_MIN_LEVEL_EXT     0x82DB
#నిర్వచించు GL_TEXTURE_VIEW_అంకె_స్థాయిలు_EXT    0x82DC
#నిర్వచించు GL_TEXTURE_VIEW_MIN_LAYER_EXT     0x82DD
#నిర్వచించు GL_TEXTURE_VIEW_అంకె_LAYERS_EXT    0x82DE
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXTUREVIEWEXTPROC) (GLuint texture, GLenum లక్ష్యం, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glTextureViewEXT (GLuint texture, GLenum లక్ష్యం, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_texture_view */

#నిర్వచితం_కాకపోతే GL_EXT_unpack_subimage
#నిర్వచించు GL_EXT_unpack_subimage 1
#నిర్వచించు GL_UNPACK_అడ్డువరుస_నిడివి_EXT          0x0CF2
#నిర్వచించు GL_UNPACK_SKIP_అడ్డువరుసలు_EXT           0x0CF3
#నిర్వచించు GL_UNPACK_SKIP_PIXELS_EXT         0x0CF4
#అయితే_ముగింపు /* GL_EXT_unpack_subimage */

#నిర్వచితం_కాకపోతే GL_EXT_win32_keyed_mutex
#నిర్వచించు GL_EXT_win32_keyed_mutex 1
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLACQUIREKEYEDMUTEXWIN32EXTPROC) (GLuint జ్ఞాపకం, GLuint64 కీలకం, GLuint timeout);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLRELEASEKEYEDMUTEXWIN32EXTPROC) (GLuint జ్ఞాపకం, GLuint64 కీలకం);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL GLboolean GL_APIENTRY glAcquireKeyedMutexWin32EXT (GLuint జ్ఞాపకం, GLuint64 కీలకం, GLuint timeout);
GL_APICALL GLboolean GL_APIENTRY glReleaseKeyedMutexWin32EXT (GLuint జ్ఞాపకం, GLuint64 కీలకం);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_win32_keyed_mutex */

#నిర్వచితం_కాకపోతే GL_EXT_కిటికీ_rectangles
#నిర్వచించు GL_EXT_కిటికీ_rectangles 1
#నిర్వచించు GL_INCLUSIVE_EXT                  0x8F10
#నిర్వచించు GL_EXCLUSIVE_EXT                  0x8F11
#నిర్వచించు GL_కిటికీ_RECTANGLE_EXT           0x8F12
#నిర్వచించు GL_కిటికీ_RECTANGLE_బహుళకం_EXT      0x8F13
#నిర్వచించు GL_MAX_కిటికీ_RECTANGLES_EXT      0x8F14
#నిర్వచించు GL_అంకె_కిటికీ_RECTANGLES_EXT      0x8F15
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLWINDOWRECTANGLESEXTPROC) (GLenum బహుళకం, GLsizei లెక్క, స్థిరరాశి GLint *box);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_కిటికీ_Rectangles_EXT (GLenum బహుళకం, GLsizei లెక్క, స్థిరరాశి GLint *box);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_window_rectangles */

#నిర్వచితం_కాకపోతే GL_FJ_shader_ద్విమాన_GCCSO
#నిర్వచించు GL_FJ_shader_ద్విమాన_GCCSO 1
#నిర్వచించు GL_GCCSO_SHADER_ద్విమాన_FJ         0x9260
#అయితే_ముగింపు /* GL_FJ_shader_binary_GCCSO */

#నిర్వచితం_కాకపోతే GL_HUAWEI_కార్యక్రమం_ద్విమాన
#నిర్వచించు GL_HUAWEI_కార్యక్రమం_ద్విమాన 1
#నిర్వచించు GL_కార్యక్రమం_ద్విమాన_HUAWEI          0x9771
#అయితే_ముగింపు /* GL_HUAWEI_program_binary */

#నిర్వచితం_కాకపోతే GL_HUAWEI_shader_ద్విమాన
#నిర్వచించు GL_HUAWEI_shader_ద్విమాన 1
#నిర్వచించు GL_SHADER_ద్విమాన_HUAWEI           0x9770
#అయితే_ముగింపు /* GL_HUAWEI_shader_binary */

#నిర్వచితం_కాకపోతే GL_IMG_bindless_texture
#నిర్వచించు GL_IMG_bindless_texture 1
రకనిర్వచనం GLuint64 (GL_APIENTRYP PFNGLGETTEXTUREHANDLEIMGPROC) (GLuint texture);
రకనిర్వచనం GLuint64 (GL_APIENTRYP PFNGLGETTEXTURESAMPLERHANDLEIMGPROC) (GLuint texture, GLuint sampler);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORMHANDLEUI64IMGPROC) (GLint location, GLuint64 విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORMHANDLEUI64VIMGPROC) (GLint location, GLsizei లెక్క, స్థిరరాశి GLuint64 *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64IMGPROC) (GLuint కార్యక్రమం, GLint location, GLuint64 విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64VIMGPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLuint64 *విలువలు);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL GLuint64 GL_APIENTRY glGetTextureHandleIMG (GLuint texture);
GL_APICALL GLuint64 GL_APIENTRY glGetTextureSamplerHandleIMG (GLuint texture, GLuint sampler);
GL_APICALL శూన్య GL_APIENTRY gl_ఏకరీతి_Handleui64_IMG (GLint location, GLuint64 విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_ఏకరీతి_Handleui64v_IMG (GLint location, GLsizei లెక్క, స్థిరరాశి GLuint64 *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_ఏకరీతి_Handleui64_IMG (GLuint కార్యక్రమం, GLint location, GLuint64 విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_ఏకరీతి_Handleui64v_IMG (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLuint64 *విలువలు);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_IMG_bindless_texture */

#నిర్వచితం_కాకపోతే GL_IMG_framebuffer_downsample
#నిర్వచించు GL_IMG_framebuffer_downsample 1
#నిర్వచించు GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_AND_DOWNSAMPLE_IMG 0x913C
#నిర్వచించు GL_అంకె_DOWNSAMPLE_SCALES_IMG      0x913D
#నిర్వచించు GL_DOWNSAMPLE_SCALES_IMG          0x913E
#నిర్వచించు GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SCALE_IMG 0x913F
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DDOWNSAMPLEIMGPROC) (GLenum లక్ష్యం, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint xscale, GLint yscale);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURELAYERDOWNSAMPLEIMGPROC) (GLenum లక్ష్యం, GLenum attachment, GLuint texture, GLint level, GLint layer, GLint xscale, GLint yscale);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glFramebufferTexture2DDownsampleIMG (GLenum లక్ష్యం, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint xscale, GLint yscale);
GL_APICALL శూన్య GL_APIENTRY glFramebufferTextureLayerDownsampleIMG (GLenum లక్ష్యం, GLenum attachment, GLuint texture, GLint level, GLint layer, GLint xscale, GLint yscale);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_IMG_framebuffer_downsample */

#నిర్వచితం_కాకపోతే GL_IMG_multisampled_render_గమ్యం_texture
#నిర్వచించు GL_IMG_multisampled_render_గమ్యం_texture 1
#నిర్వచించు GL_RENDERBUFFER_SAMPLES_IMG       0x9133
#నిర్వచించు GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_IMG 0x9134
#నిర్వచించు GL_MAX_SAMPLES_IMG                0x9135
#నిర్వచించు GL_TEXTURE_SAMPLES_IMG            0x9136
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEIMGPROC) (GLenum లక్ష్యం, GLsizei samples, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEIMGPROC) (GLenum లక్ష్యం, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glRenderbufferStorageMultisampleIMG (GLenum లక్ష్యం, GLsizei samples, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
GL_APICALL శూన్య GL_APIENTRY glFramebufferTexture2DMultisampleIMG (GLenum లక్ష్యం, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_IMG_multisampled_render_to_texture */

#నిర్వచితం_కాకపోతే GL_IMG_కార్యక్రమం_ద్విమాన
#నిర్వచించు GL_IMG_కార్యక్రమం_ద్విమాన 1
#నిర్వచించు GL_SGX_కార్యక్రమం_ద్విమాన_IMG         0x9130
#అయితే_ముగింపు /* GL_IMG_program_binary */

#నిర్వచితం_కాకపోతే GL_IMG_read_format
#నిర్వచించు GL_IMG_read_format 1
#నిర్వచించు GL_BGRA_IMG                       0x80E1
#నిర్వచించు GL_UNSIGNED_SHORT_4_4_4_4_REV_IMG 0x8365
#అయితే_ముగింపు /* GL_IMG_read_format */

#నిర్వచితం_కాకపోతే GL_IMG_shader_ద్విమాన
#నిర్వచించు GL_IMG_shader_ద్విమాన 1
#నిర్వచించు GL_SGX_ద్విమాన_IMG                 0x8C0A
#అయితే_ముగింపు /* GL_IMG_shader_binary */

#నిర్వచితం_కాకపోతే GL_IMG_texture_compression_pvrtc
#నిర్వచించు GL_IMG_texture_compression_pvrtc 1
#నిర్వచించు GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG 0x8C00
#నిర్వచించు GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG 0x8C01
#నిర్వచించు GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG 0x8C02
#నిర్వచించు GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG 0x8C03
#అయితే_ముగింపు /* GL_IMG_texture_compression_pvrtc */

#నిర్వచితం_కాకపోతే GL_IMG_texture_compression_pvrtc2
#నిర్వచించు GL_IMG_texture_compression_pvrtc2 1
#నిర్వచించు GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG 0x9137
#నిర్వచించు GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG 0x9138
#అయితే_ముగింపు /* GL_IMG_texture_compression_pvrtc2 */

#నిర్వచితం_కాకపోతే GL_IMG_texture_filter_cubic
#నిర్వచించు GL_IMG_texture_filter_cubic 1
#నిర్వచించు GL_CUBIC_IMG                      0x9139
#నిర్వచించు GL_CUBIC_MIPMAP_సమీప_IMG       0x913A
#నిర్వచించు GL_CUBIC_MIPMAP_రేఖీయ_IMG        0x913B
#అయితే_ముగింపు /* GL_IMG_texture_filter_cubic */

#నిర్వచితం_కాకపోతే GL_INTEL_blackhole_render
#నిర్వచించు GL_INTEL_blackhole_render 1
#నిర్వచించు GL_BLACKHOLE_RENDER_INTEL         0x83FC
#అయితే_ముగింపు /* GL_INTEL_blackhole_render */

#నిర్వచితం_కాకపోతే GL_INTEL_conservative_rasterization
#నిర్వచించు GL_INTEL_conservative_rasterization 1
#నిర్వచించు GL_CONSERVATIVE_RASTERIZATION_INTEL 0x83FE
#అయితే_ముగింపు /* GL_INTEL_conservative_rasterization */

#నిర్వచితం_కాకపోతే GL_INTEL_framebuffer_CMAA
#నిర్వచించు GL_INTEL_framebuffer_CMAA 1
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLAPPLYFRAMEBUFFERATTACHMENTCMAAINTELPROC) (శూన్య);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glApplyFramebufferAttachmentCMAAINTEL (శూన్య);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_INTEL_framebuffer_CMAA */

#నిర్వచితం_కాకపోతే GL_INTEL_performance_query
#నిర్వచించు GL_INTEL_performance_query 1
#నిర్వచించు GL_PERFQUERY_SINGLE_CONTEXT_INTEL 0x00000000
#నిర్వచించు GL_PERFQUERY_GLOBAL_CONTEXT_INTEL 0x00000001
#నిర్వచించు GL_PERFQUERY_WAIT_INTEL           0x83FB
#నిర్వచించు GL_PERFQUERY_FLUSH_INTEL          0x83FA
#నిర్వచించు GL_PERFQUERY_DONOT_FLUSH_INTEL    0x83F9
#నిర్వచించు GL_PERFQUERY_COUNTER_EVENT_INTEL  0x94F0
#నిర్వచించు GL_PERFQUERY_COUNTER_DURATION_NORM_INTEL 0x94F1
#నిర్వచించు GL_PERFQUERY_COUNTER_DURATION_RAW_INTEL 0x94F2
#నిర్వచించు GL_PERFQUERY_COUNTER_THROUGHPUT_INTEL 0x94F3
#నిర్వచించు GL_PERFQUERY_COUNTER_RAW_INTEL    0x94F4
#నిర్వచించు GL_PERFQUERY_COUNTER_TIMESTAMP_INTEL 0x94F5
#నిర్వచించు GL_PERFQUERY_COUNTER_దత్తాంశం_UINT32_INTEL 0x94F8
#నిర్వచించు GL_PERFQUERY_COUNTER_దత్తాంశం_UINT64_INTEL 0x94F9
#నిర్వచించు GL_PERFQUERY_COUNTER_దత్తాంశం_FLOAT_INTEL 0x94FA
#నిర్వచించు GL_PERFQUERY_COUNTER_దత్తాంశం_DOUBLE_INTEL 0x94FB
#నిర్వచించు GL_PERFQUERY_COUNTER_దత్తాంశం_BOOL32_INTEL 0x94FC
#నిర్వచించు GL_PERFQUERY_QUERY_NAME_నిడివి_MAX_INTEL 0x94FD
#నిర్వచించు GL_PERFQUERY_COUNTER_NAME_నిడివి_MAX_INTEL 0x94FE
#నిర్వచించు GL_PERFQUERY_COUNTER_DESC_నిడివి_MAX_INTEL 0x94FF
#నిర్వచించు GL_PERFQUERY_GPA_EXTENDED_COUNTERS_INTEL 0x9500
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBEGINPERFQUERYINTELPROC) (GLuint queryHandle);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCREATEPERFQUERYINTELPROC) (GLuint queryId, GLuint *queryHandle);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDELETEPERFQUERYINTELPROC) (GLuint queryHandle);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLENDPERFQUERYINTELPROC) (GLuint queryHandle);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETFIRSTPERFQUERYIDINTELPROC) (GLuint *queryId);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETNEXTPERFQUERYIDINTELPROC) (GLuint queryId, GLuint *తదుపరి_Query_Id);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETPERFCOUNTERINFOINTELPROC) (GLuint queryId, GLuint counterId, GLuint counter_Name_నిడివి, GLchar *counterName, GLuint counter_Desc_నిడివి, GLchar *counterDesc, GLuint *counter_స్థానభ్రంశం, GLuint *counter_దత్తాంశం_కొలత, GLuint *counterTypeEnum, GLuint *counter_దత్తాంశం_Type_Enum, GLuint64 *raw_Counter_Max_విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETPERFQUERYDATAINTELPROC) (GLuint queryHandle, GLuint flags, GLsizei దత్తాంశం_కొలత_2, శూన్య *దత్తాంశం, GLuint *బైట్లు_Written);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETPERFQUERYIDBYNAMEINTELPROC) (GLchar *queryName, GLuint *queryId);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETPERFQUERYINFOINTELPROC) (GLuint queryId, GLuint query_Name_నిడివి, GLchar *queryName, GLuint *దత్తాంశం_కొలత_2, GLuint *noCounters, GLuint *noInstances, GLuint *caps_ముసుగు);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glBeginPerfQueryINTEL (GLuint queryHandle);
GL_APICALL శూన్య GL_APIENTRY glCreatePerfQueryINTEL (GLuint queryId, GLuint *queryHandle);
GL_APICALL శూన్య GL_APIENTRY glDeletePerfQueryINTEL (GLuint queryHandle);
GL_APICALL శూన్య GL_APIENTRY gl_చివర_Perf_Query_INTEL (GLuint queryHandle);
GL_APICALL శూన్య GL_APIENTRY gl_Get_మొదటి_Perf_Query_Id_INTEL (GLuint *queryId);
GL_APICALL శూన్య GL_APIENTRY gl_Get_తదుపరి_Perf_Query_Id_INTEL (GLuint queryId, GLuint *తదుపరి_Query_Id);
GL_APICALL శూన్య GL_APIENTRY glGetPerfCounterInfoINTEL (GLuint queryId, GLuint counterId, GLuint counter_Name_నిడివి, GLchar *counterName, GLuint counter_Desc_నిడివి, GLchar *counterDesc, GLuint *counter_స్థానభ్రంశం, GLuint *counter_దత్తాంశం_కొలత, GLuint *counterTypeEnum, GLuint *counter_దత్తాంశం_Type_Enum, GLuint64 *raw_Counter_Max_విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_Get_Perf_Query_దత్తాంశం_INTEL (GLuint queryHandle, GLuint flags, GLsizei దత్తాంశం_కొలత_2, శూన్య *దత్తాంశం, GLuint *బైట్లు_Written);
GL_APICALL శూన్య GL_APIENTRY glGetPerfQueryIdByNameINTEL (GLchar *queryName, GLuint *queryId);
GL_APICALL శూన్య GL_APIENTRY glGetPerfQueryInfoINTEL (GLuint queryId, GLuint query_Name_నిడివి, GLchar *queryName, GLuint *దత్తాంశం_కొలత_2, GLuint *noCounters, GLuint *noInstances, GLuint *caps_ముసుగు);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_INTEL_performance_query */

#నిర్వచితం_కాకపోతే GL_MESA_bgra
#నిర్వచించు GL_MESA_bgra 1
#నిర్వచించు GL_BGR_EXT                        0x80E0
#అయితే_ముగింపు /* GL_MESA_bgra */

#నిర్వచితం_కాకపోతే GL_MESA_framebuffer_flip_x
#నిర్వచించు GL_MESA_framebuffer_flip_x 1
#నిర్వచించు GL_FRAMEBUFFER_FLIP_X_MESA        0x8BBC
#అయితే_ముగింపు /* GL_MESA_framebuffer_flip_x */

#నిర్వచితం_కాకపోతే GL_MESA_framebuffer_flip_y
#నిర్వచించు GL_MESA_framebuffer_flip_y 1
#నిర్వచించు GL_FRAMEBUFFER_FLIP_Y_MESA        0x8BBB
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFRAMEBUFFERPARAMETERIMESAPROC) (GLenum లక్ష్యం, GLenum pname, GLint param);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETFRAMEBUFFERPARAMETERIVMESAPROC) (GLenum లక్ష్యం, GLenum pname, GLint *params);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glFramebufferParameteriMESA (GLenum లక్ష్యం, GLenum pname, GLint param);
GL_APICALL శూన్య GL_APIENTRY glGetFramebufferParameterivMESA (GLenum లక్ష్యం, GLenum pname, GLint *params);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_MESA_framebuffer_flip_y */

#నిర్వచితం_కాకపోతే GL_MESA_framebuffer_మార్పిడి_xy
#నిర్వచించు GL_MESA_framebuffer_మార్పిడి_xy 1
#నిర్వచించు GL_FRAMEBUFFER_మార్పిడి_XY_MESA       0x8BBD
#అయితే_ముగింపు /* GL_MESA_framebuffer_swap_xy */

#నిర్వచితం_కాకపోతే GL_MESA_కార్యక్రమం_ద్విమాన_formats
#నిర్వచించు GL_MESA_కార్యక్రమం_ద్విమాన_formats 1
#నిర్వచించు GL_కార్యక్రమం_ద్విమాన_FORMAT_MESA     0x875F
#అయితే_ముగింపు /* GL_MESA_program_binary_formats */

#నిర్వచితం_కాకపోతే GL_MESA_sampler_objects
#నిర్వచించు GL_MESA_sampler_objects 1
#నిర్వచించు GL_SAMPLER_BINDING                0x8919
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGENSAMPLERSPROC) (GLsizei లెక్క, GLuint *samplers);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDELETESAMPLERSPROC) (GLsizei లెక్క, స్థిరరాశి GLuint *samplers);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLISSAMPLERPROC) (GLuint sampler);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBINDSAMPLERPROC) (GLuint unit, GLuint sampler);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSAMPLERPARAMETERIPROC) (GLuint sampler, GLenum pname, GLint param);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, స్థిరరాశి GLint *param);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSAMPLERPARAMETERFPROC) (GLuint sampler, GLenum pname, GLfloat param);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, స్థిరరాశి GLfloat *param);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, GLint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, GLfloat *params);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glGenSamplers (GLsizei లెక్క, GLuint *samplers);
GL_APICALL శూన్య GL_APIENTRY glDeleteSamplers (GLsizei లెక్క, స్థిరరాశి GLuint *samplers);
GL_APICALL GLboolean GL_APIENTRY glIsSampler (GLuint sampler);
GL_APICALL శూన్య GL_APIENTRY glBindSampler (GLuint unit, GLuint sampler);
GL_APICALL శూన్య GL_APIENTRY glSamplerParameteri (GLuint sampler, GLenum pname, GLint param);
GL_APICALL శూన్య GL_APIENTRY glSamplerParameteriv (GLuint sampler, GLenum pname, స్థిరరాశి GLint *param);
GL_APICALL శూన్య GL_APIENTRY glSamplerParameterf (GLuint sampler, GLenum pname, GLfloat param);
GL_APICALL శూన్య GL_APIENTRY glSamplerParameterfv (GLuint sampler, GLenum pname, స్థిరరాశి GLfloat *param);
GL_APICALL శూన్య GL_APIENTRY glGetSamplerParameteriv (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL శూన్య GL_APIENTRY glGetSamplerParameterfv (GLuint sampler, GLenum pname, GLfloat *params);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_MESA_sampler_objects */

#నిర్వచితం_కాకపోతే GL_MESA_shader_integer_functions
#నిర్వచించు GL_MESA_shader_integer_functions 1
#అయితే_ముగింపు /* GL_MESA_shader_integer_functions */

#నిర్వచితం_కాకపోతే GL_MESA_texture_const_bandwidth
#నిర్వచించు GL_MESA_texture_const_bandwidth 1
#నిర్వచించు GL_CONST_BW_TILING_MESA           0x8BBE
#అయితే_ముగింపు /* GL_MESA_texture_const_bandwidth */

#నిర్వచితం_కాకపోతే GL_NVX_blend_equation_advanced_multi_draw_buffers
#నిర్వచించు GL_NVX_blend_equation_advanced_multi_draw_buffers 1
#అయితే_ముగింపు /* GL_NVX_blend_equation_advanced_multi_draw_buffers */

#నిర్వచితం_కాకపోతే GL_NV_bindless_texture
#నిర్వచించు GL_NV_bindless_texture 1
రకనిర్వచనం GLuint64 (GL_APIENTRYP PFNGLGETTEXTUREHANDLENVPROC) (GLuint texture);
రకనిర్వచనం GLuint64 (GL_APIENTRYP PFNGLGETTEXTURESAMPLERHANDLENVPROC) (GLuint texture, GLuint sampler);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMAKETEXTUREHANDLERESIDENTNVPROC) (GLuint64 handle);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMAKETEXTUREHANDLENONRESIDENTNVPROC) (GLuint64 handle);
రకనిర్వచనం GLuint64 (GL_APIENTRYP PFNGLGETIMAGEHANDLENVPROC) (GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMAKEIMAGEHANDLERESIDENTNVPROC) (GLuint64 handle, GLenum access);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMAKEIMAGEHANDLENONRESIDENTNVPROC) (GLuint64 handle);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORMHANDLEUI64NVPROC) (GLint location, GLuint64 విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORMHANDLEUI64VNVPROC) (GLint location, GLsizei లెక్క, స్థిరరాశి GLuint64 *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64NVPROC) (GLuint కార్యక్రమం, GLint location, GLuint64 విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64VNVPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLuint64 *విలువలు);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLISTEXTUREHANDLERESIDENTNVPROC) (GLuint64 handle);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLISIMAGEHANDLERESIDENTNVPROC) (GLuint64 handle);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL GLuint64 GL_APIENTRY glGetTextureHandleNV (GLuint texture);
GL_APICALL GLuint64 GL_APIENTRY glGetTextureSamplerHandleNV (GLuint texture, GLuint sampler);
GL_APICALL శూన్య GL_APIENTRY glMakeTextureHandleResidentNV (GLuint64 handle);
GL_APICALL శూన్య GL_APIENTRY glMakeTextureHandleNonResidentNV (GLuint64 handle);
GL_APICALL GLuint64 GL_APIENTRY glGetImageHandleNV (GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format);
GL_APICALL శూన్య GL_APIENTRY glMakeImageHandleResidentNV (GLuint64 handle, GLenum access);
GL_APICALL శూన్య GL_APIENTRY glMakeImageHandleNonResidentNV (GLuint64 handle);
GL_APICALL శూన్య GL_APIENTRY gl_ఏకరీతి_Handleui64_NV (GLint location, GLuint64 విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_ఏకరీతి_Handleui64v_NV (GLint location, GLsizei లెక్క, స్థిరరాశి GLuint64 *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_ఏకరీతి_Handleui64_NV (GLuint కార్యక్రమం, GLint location, GLuint64 విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_ఏకరీతి_Handleui64v_NV (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLuint64 *విలువలు);
GL_APICALL GLboolean GL_APIENTRY glIsTextureHandleResidentNV (GLuint64 handle);
GL_APICALL GLboolean GL_APIENTRY glIsImageHandleResidentNV (GLuint64 handle);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_NV_bindless_texture */

#నిర్వచితం_కాకపోతే GL_NV_blend_equation_advanced
#నిర్వచించు GL_NV_blend_equation_advanced 1
#నిర్వచించు GL_BLEND_OVERLAP_NV               0x9281
#నిర్వచించు GL_BLEND_PREMULTIPLIED_SRC_NV     0x9280
#నిర్వచించు GL_BLUE_NV                        0x1905
#నిర్వచించు GL_COLORBURN_NV                   0x929A
#నిర్వచించు GL_COLORDODGE_NV                  0x9299
#నిర్వచించు GL_CONJOINT_NV                    0x9284
#నిర్వచించు GL_CONTRAST_NV                    0x92A1
#నిర్వచించు GL_DARKEN_NV                      0x9297
#నిర్వచించు GL_DIFFERENCE_NV                  0x929E
#నిర్వచించు GL_DISJOINT_NV                    0x9283
#నిర్వచించు GL_DST_ATOP_NV                    0x928F
#నిర్వచించు GL_DST_లోపల_NV                      0x928B
#నిర్వచించు GL_DST_NV                         0x9287
#నిర్వచించు GL_DST_బహిర్గతం_NV                     0x928D
#నిర్వచించు GL_DST_OVER_NV                    0x9289
#నిర్వచించు GL_EXCLUSION_NV                   0x92A0
#నిర్వచించు GL_GREEN_NV                       0x1904
#నిర్వచించు GL_HARDLIGHT_NV                   0x929B
#నిర్వచించు GL_HARDMIX_NV                     0x92A9
#నిర్వచించు GL_HSL_COLOR_NV                   0x92AF
#నిర్వచించు GL_HSL_HUE_NV                     0x92AD
#నిర్వచించు GL_HSL_LUMINOSITY_NV              0x92B0
#నిర్వచించు GL_HSL_SATURATION_NV              0x92AE
#నిర్వచించు GL_INVERT_OVG_NV                  0x92B4
#నిర్వచించు GL_INVERT_RGB_NV                  0x92A3
#నిర్వచించు GL_LIGHTEN_NV                     0x9298
#నిర్వచించు GL_LINEARBURN_NV                  0x92A5
#నిర్వచించు GL_LINEARDODGE_NV                 0x92A4
#నిర్వచించు GL_LINEARLIGHT_NV                 0x92A7
#నిర్వచించు GL_MINUS_CLAMPED_NV               0x92B3
#నిర్వచించు GL_MINUS_NV                       0x929F
#నిర్వచించు GL_MULTIPLY_NV                    0x9294
#నిర్వచించు GL_OVERLAY_NV                     0x9296
#నిర్వచించు GL_PINLIGHT_NV                    0x92A8
#నిర్వచించు GL_PLUS_CLAMPED_ALPHA_NV          0x92B2
#నిర్వచించు GL_PLUS_CLAMPED_NV                0x92B1
#నిర్వచించు GL_PLUS_DARKER_NV                 0x9292
#నిర్వచించు GL_PLUS_NV                        0x9291
#నిర్వచించు GL_RED_NV                         0x1903
#నిర్వచించు GL_SCREEN_NV                      0x9295
#నిర్వచించు GL_SOFTLIGHT_NV                   0x929C
#నిర్వచించు GL_SRC_ATOP_NV                    0x928E
#నిర్వచించు GL_SRC_లోపల_NV                      0x928A
#నిర్వచించు GL_SRC_NV                         0x9286
#నిర్వచించు GL_SRC_బహిర్గతం_NV                     0x928C
#నిర్వచించు GL_SRC_OVER_NV                    0x9288
#నిర్వచించు GL_UNCORRELATED_NV                0x9282
#నిర్వచించు GL_VIVIDLIGHT_NV                  0x92A6
#నిర్వచించు GL_XOR_NV                         0x1506
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBLENDPARAMETERINVPROC) (GLenum pname, GLint విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBLENDBARRIERNVPROC) (శూన్య);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glBlendParameteriNV (GLenum pname, GLint విలువ);
GL_APICALL శూన్య GL_APIENTRY glBlendBarrierNV (శూన్య);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_NV_blend_equation_advanced */

#నిర్వచితం_కాకపోతే GL_NV_blend_equation_advanced_coherent
#నిర్వచించు GL_NV_blend_equation_advanced_coherent 1
#నిర్వచించు GL_BLEND_ADVANCED_COHERENT_NV     0x9285
#అయితే_ముగింపు /* GL_NV_blend_equation_advanced_coherent */

#నిర్వచితం_కాకపోతే GL_NV_blend_minmax_గుణకం
#నిర్వచించు GL_NV_blend_minmax_గుణకం 1
#నిర్వచించు GL_గుణకం_MIN_AMD                 0x901C
#నిర్వచించు GL_గుణకం_MAX_AMD                 0x901D
#అయితే_ముగింపు /* GL_NV_blend_minmax_factor */

#నిర్వచితం_కాకపోతే GL_NV_clip_space_w_scaling
#నిర్వచించు GL_NV_clip_space_w_scaling 1
#నిర్వచించు GL_VIEWPORT_POSITION_W_SCALE_NV   0x937C
#నిర్వచించు GL_VIEWPORT_POSITION_W_SCALE_X_COEFF_NV 0x937D
#నిర్వచించు GL_VIEWPORT_POSITION_W_SCALE_Y_COEFF_NV 0x937E
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLVIEWPORTPOSITIONWSCALENVPROC) (GLuint సూచీ, GLfloat xcoeff, GLfloat ycoeff);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glViewportPositionWScaleNV (GLuint సూచీ, GLfloat xcoeff, GLfloat ycoeff);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_NV_clip_space_w_scaling */

#నిర్వచితం_కాకపోతే GL_NV_compute_shader_derivatives
#నిర్వచించు GL_NV_compute_shader_derivatives 1
#అయితే_ముగింపు /* GL_NV_compute_shader_derivatives */

#నిర్వచితం_కాకపోతే GL_NV_conditional_render
#నిర్వచించు GL_NV_conditional_render 1
#నిర్వచించు GL_QUERY_WAIT_NV                  0x8E13
#నిర్వచించు GL_QUERY_NO_WAIT_NV               0x8E14
#నిర్వచించు GL_QUERY_BY_REGION_WAIT_NV        0x8E15
#నిర్వచించు GL_QUERY_BY_REGION_NO_WAIT_NV     0x8E16
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBEGINCONDITIONALRENDERNVPROC) (GLuint id, GLenum బహుళకం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLENDCONDITIONALRENDERNVPROC) (శూన్య);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glBeginConditionalRenderNV (GLuint id, GLenum బహుళకం);
GL_APICALL శూన్య GL_APIENTRY gl_చివర_Conditional_Render_NV (శూన్య);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_NV_conditional_render */

#నిర్వచితం_కాకపోతే GL_NV_conservative_raster
#నిర్వచించు GL_NV_conservative_raster 1
#నిర్వచించు GL_CONSERVATIVE_RASTERIZATION_NV  0x9346
#నిర్వచించు GL_SUBPIXEL_PRECISION_BIAS_X_బిట్లు_NV 0x9347
#నిర్వచించు GL_SUBPIXEL_PRECISION_BIAS_Y_బిట్లు_NV 0x9348
#నిర్వచించు GL_MAX_SUBPIXEL_PRECISION_BIAS_బిట్లు_NV 0x9349
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSUBPIXELPRECISIONBIASNVPROC) (GLuint xbits, GLuint ybits);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glSubpixelPrecisionBiasNV (GLuint xbits, GLuint ybits);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_NV_conservative_raster */

#నిర్వచితం_కాకపోతే GL_NV_conservative_raster_pre_snap
#నిర్వచించు GL_NV_conservative_raster_pre_snap 1
#నిర్వచించు GL_CONSERVATIVE_RASTER_బహుళకం_PRE_SNAP_NV 0x9550
#అయితే_ముగింపు /* GL_NV_conservative_raster_pre_snap */

#నిర్వచితం_కాకపోతే GL_NV_conservative_raster_pre_snap_triangles
#నిర్వచించు GL_NV_conservative_raster_pre_snap_triangles 1
#నిర్వచించు GL_CONSERVATIVE_RASTER_బహుళకం_NV    0x954D
#నిర్వచించు GL_CONSERVATIVE_RASTER_బహుళకం_POST_SNAP_NV 0x954E
#నిర్వచించు GL_CONSERVATIVE_RASTER_బహుళకం_PRE_SNAP_TRIANGLES_NV 0x954F
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCONSERVATIVERASTERPARAMETERINVPROC) (GLenum pname, GLint param);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glConservativeRasterParameteriNV (GLenum pname, GLint param);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_NV_conservative_raster_pre_snap_triangles */

#నిర్వచితం_కాకపోతే GL_NV_copy_బఫరు
#నిర్వచించు GL_NV_copy_బఫరు 1
#నిర్వచించు GL_COPY_READ_బఫరు_NV            0x8F36
#నిర్వచించు GL_COPY_WRITE_బఫరు_NV           0x8F37
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCOPYBUFFERSUBDATANVPROC) (GLenum read_లక్ష్యం, GLenum write_లక్ష్యం, GLintptr read_స్థానభ్రంశం, GLintptr write_స్థానభ్రంశం, GLsizeiptr కొలత);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_Copy_బఫరు_Sub_దత్తాంశం_NV (GLenum read_లక్ష్యం, GLenum write_లక్ష్యం, GLintptr read_స్థానభ్రంశం, GLintptr write_స్థానభ్రంశం, GLsizeiptr కొలత);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_NV_copy_buffer */

#నిర్వచితం_కాకపోతే GL_NV_coverage_sample
#నిర్వచించు GL_NV_coverage_sample 1
#నిర్వచించు GL_COVERAGE_COMPONENT_NV          0x8ED0
#నిర్వచించు GL_COVERAGE_COMPONENT4_NV         0x8ED1
#నిర్వచించు GL_COVERAGE_ATTACHMENT_NV         0x8ED2
#నిర్వచించు GL_COVERAGE_BUFFERS_NV            0x8ED3
#నిర్వచించు GL_COVERAGE_SAMPLES_NV            0x8ED4
#నిర్వచించు GL_COVERAGE_ALL_FRAGMENTS_NV      0x8ED5
#నిర్వచించు GL_COVERAGE_అంచు_FRAGMENTS_NV     0x8ED6
#నిర్వచించు GL_COVERAGE_AUTOMATIC_NV          0x8ED7
#నిర్వచించు GL_COVERAGE_బఫరు_బిట్టు_NV         0x00008000
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCOVERAGEMASKNVPROC) (GLboolean ముసుగు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCOVERAGEOPERATIONNVPROC) (GLenum operation);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_Coverage_ముసుగు_NV (GLboolean ముసుగు);
GL_APICALL శూన్య GL_APIENTRY glCoverageOperationNV (GLenum operation);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_NV_coverage_sample */

#నిర్వచితం_కాకపోతే GL_NV_లోతు_nonlinear
#నిర్వచించు GL_NV_లోతు_nonlinear 1
#నిర్వచించు GL_లోతు_COMPONENT16_NONLINEAR_NV 0x8E2C
#అయితే_ముగింపు /* GL_NV_depth_nonlinear */

#నిర్వచితం_కాకపోతే GL_NV_draw_buffers
#నిర్వచించు GL_NV_draw_buffers 1
#నిర్వచించు GL_MAX_DRAW_BUFFERS_NV            0x8824
#నిర్వచించు GL_DRAW_BUFFER0_NV                0x8825
#నిర్వచించు GL_DRAW_BUFFER1_NV                0x8826
#నిర్వచించు GL_DRAW_BUFFER2_NV                0x8827
#నిర్వచించు GL_DRAW_BUFFER3_NV                0x8828
#నిర్వచించు GL_DRAW_BUFFER4_NV                0x8829
#నిర్వచించు GL_DRAW_BUFFER5_NV                0x882A
#నిర్వచించు GL_DRAW_BUFFER6_NV                0x882B
#నిర్వచించు GL_DRAW_BUFFER7_NV                0x882C
#నిర్వచించు GL_DRAW_BUFFER8_NV                0x882D
#నిర్వచించు GL_DRAW_BUFFER9_NV                0x882E
#నిర్వచించు GL_DRAW_BUFFER10_NV               0x882F
#నిర్వచించు GL_DRAW_BUFFER11_NV               0x8830
#నిర్వచించు GL_DRAW_BUFFER12_NV               0x8831
#నిర్వచించు GL_DRAW_BUFFER13_NV               0x8832
#నిర్వచించు GL_DRAW_BUFFER14_NV               0x8833
#నిర్వచించు GL_DRAW_BUFFER15_NV               0x8834
#నిర్వచించు GL_COLOR_ATTACHMENT0_NV           0x8CE0
#నిర్వచించు GL_COLOR_ATTACHMENT1_NV           0x8CE1
#నిర్వచించు GL_COLOR_ATTACHMENT2_NV           0x8CE2
#నిర్వచించు GL_COLOR_ATTACHMENT3_NV           0x8CE3
#నిర్వచించు GL_COLOR_ATTACHMENT4_NV           0x8CE4
#నిర్వచించు GL_COLOR_ATTACHMENT5_NV           0x8CE5
#నిర్వచించు GL_COLOR_ATTACHMENT6_NV           0x8CE6
#నిర్వచించు GL_COLOR_ATTACHMENT7_NV           0x8CE7
#నిర్వచించు GL_COLOR_ATTACHMENT8_NV           0x8CE8
#నిర్వచించు GL_COLOR_ATTACHMENT9_NV           0x8CE9
#నిర్వచించు GL_COLOR_ATTACHMENT10_NV          0x8CEA
#నిర్వచించు GL_COLOR_ATTACHMENT11_NV          0x8CEB
#నిర్వచించు GL_COLOR_ATTACHMENT12_NV          0x8CEC
#నిర్వచించు GL_COLOR_ATTACHMENT13_NV          0x8CED
#నిర్వచించు GL_COLOR_ATTACHMENT14_NV          0x8CEE
#నిర్వచించు GL_COLOR_ATTACHMENT15_NV          0x8CEF
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWBUFFERSNVPROC) (GLsizei n, స్థిరరాశి GLenum *bufs);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glDrawBuffersNV (GLsizei n, స్థిరరాశి GLenum *bufs);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_NV_draw_buffers */

#నిర్వచితం_కాకపోతే GL_NV_draw_instanced
#నిర్వచించు GL_NV_draw_instanced 1
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDNVPROC) (GLenum బహుళకం, GLint మొదటి, GLsizei లెక్క, GLsizei primcount);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDNVPROC) (GLenum బహుళకం, GLsizei లెక్క, GLenum type, స్థిరరాశి శూన్య *indices, GLsizei primcount);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glDrawArraysInstancedNV (GLenum బహుళకం, GLint మొదటి, GLsizei లెక్క, GLsizei primcount);
GL_APICALL శూన్య GL_APIENTRY glDrawElementsInstancedNV (GLenum బహుళకం, GLsizei లెక్క, GLenum type, స్థిరరాశి శూన్య *indices, GLsizei primcount);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_NV_draw_instanced */

#నిర్వచితం_కాకపోతే GL_NV_draw_vulkan_image
#నిర్వచించు GL_NV_draw_vulkan_image 1
రకనిర్వచనం శూన్య (GL_APIENTRY  *GLVULKANPROCNV)(శూన్య);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWVKIMAGENVPROC) (GLuint64 vkImage, GLuint sampler, GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat z, GLfloat s0, GLfloat t0, GLfloat s1, GLfloat t1);
రకనిర్వచనం GLVULKANPROCNV (GL_APIENTRYP PFNGLGETVKPROCADDRNVPROC) (స్థిరరాశి GLchar *name);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLWAITVKSEMAPHORENVPROC) (GLuint64 vkSemaphore);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSIGNALVKSEMAPHORENVPROC) (GLuint64 vkSemaphore);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSIGNALVKFENCENVPROC) (GLuint64 vkFence);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glDrawVkImageNV (GLuint64 vkImage, GLuint sampler, GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat z, GLfloat s0, GLfloat t0, GLfloat s1, GLfloat t1);
GL_APICALL GLVULKANPROCNV GL_APIENTRY glGetVkProcAddrNV (స్థిరరాశి GLchar *name);
GL_APICALL శూన్య GL_APIENTRY glWaitVkSemaphoreNV (GLuint64 vkSemaphore);
GL_APICALL శూన్య GL_APIENTRY glSignalVkSemaphoreNV (GLuint64 vkSemaphore);
GL_APICALL శూన్య GL_APIENTRY glSignalVkFenceNV (GLuint64 vkFence);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_NV_draw_vulkan_image */

#నిర్వచితం_కాకపోతే GL_NV_explicit_attrib_location
#నిర్వచించు GL_NV_explicit_attrib_location 1
#అయితే_ముగింపు /* GL_NV_explicit_attrib_location */

#నిర్వచితం_కాకపోతే GL_NV_fbo_color_attachments
#నిర్వచించు GL_NV_fbo_color_attachments 1
#నిర్వచించు GL_MAX_COLOR_ATTACHMENTS_NV       0x8CDF
#అయితే_ముగింపు /* GL_NV_fbo_color_attachments */

#నిర్వచితం_కాకపోతే GL_NV_fence
#నిర్వచించు GL_NV_fence 1
#నిర్వచించు GL_ALL_COMPLETED_NV               0x84F2
#నిర్వచించు GL_FENCE_స్థితి_NV                0x84F3
#నిర్వచించు GL_FENCE_CONDITION_NV             0x84F4
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDELETEFENCESNVPROC) (GLsizei n, స్థిరరాశి GLuint *fences);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGENFENCESNVPROC) (GLsizei n, GLuint *fences);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLISFENCENVPROC) (GLuint fence);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLTESTFENCENVPROC) (GLuint fence);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETFENCEIVNVPROC) (GLuint fence, GLenum pname, GLint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFINISHFENCENVPROC) (GLuint fence);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSETFENCENVPROC) (GLuint fence, GLenum condition);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glDeleteFencesNV (GLsizei n, స్థిరరాశి GLuint *fences);
GL_APICALL శూన్య GL_APIENTRY glGenFencesNV (GLsizei n, GLuint *fences);
GL_APICALL GLboolean GL_APIENTRY glIsFenceNV (GLuint fence);
GL_APICALL GLboolean GL_APIENTRY glTestFenceNV (GLuint fence);
GL_APICALL శూన్య GL_APIENTRY glGetFenceivNV (GLuint fence, GLenum pname, GLint *params);
GL_APICALL శూన్య GL_APIENTRY gl_ముగింపు_Fence_NV (GLuint fence);
GL_APICALL శూన్య GL_APIENTRY gl_సమితి_Fence_NV (GLuint fence, GLenum condition);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_NV_fence */

#నిర్వచితం_కాకపోతే GL_NV_fill_rectangle
#నిర్వచించు GL_NV_fill_rectangle 1
#నిర్వచించు GL_FILL_RECTANGLE_NV              0x933C
#అయితే_ముగింపు /* GL_NV_fill_rectangle */

#నిర్వచితం_కాకపోతే GL_NV_fragment_coverage_గమ్యం_color
#నిర్వచించు GL_NV_fragment_coverage_గమ్యం_color 1
#నిర్వచించు GL_FRAGMENT_COVERAGE_గమ్యం_COLOR_NV  0x92DD
#నిర్వచించు GL_FRAGMENT_COVERAGE_COLOR_NV     0x92DE
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFRAGMENTCOVERAGECOLORNVPROC) (GLuint color);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glFragmentCoverageColorNV (GLuint color);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_NV_fragment_coverage_to_color */

#నిర్వచితం_కాకపోతే GL_NV_fragment_shader_barycentric
#నిర్వచించు GL_NV_fragment_shader_barycentric 1
#అయితే_ముగింపు /* GL_NV_fragment_shader_barycentric */

#నిర్వచితం_కాకపోతే GL_NV_fragment_shader_interlock
#నిర్వచించు GL_NV_fragment_shader_interlock 1
#అయితే_ముగింపు /* GL_NV_fragment_shader_interlock */

#నిర్వచితం_కాకపోతే GL_NV_framebuffer_blit
#నిర్వచించు GL_NV_framebuffer_blit 1
#నిర్వచించు GL_READ_FRAMEBUFFER_NV            0x8CA8
#నిర్వచించు GL_DRAW_FRAMEBUFFER_NV            0x8CA9
#నిర్వచించు GL_DRAW_FRAMEBUFFER_BINDING_NV    0x8CA6
#నిర్వచించు GL_READ_FRAMEBUFFER_BINDING_NV    0x8CAA
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBLITFRAMEBUFFERNVPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield ముసుగు, GLenum filter);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glBlitFramebufferNV (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield ముసుగు, GLenum filter);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_NV_framebuffer_blit */

#నిర్వచితం_కాకపోతే GL_NV_framebuffer_mixed_samples
#నిర్వచించు GL_NV_framebuffer_mixed_samples 1
#నిర్వచించు GL_COVERAGE_MODULATION_పట్టిక_NV   0x9331
#నిర్వచించు GL_COLOR_SAMPLES_NV               0x8E20
#నిర్వచించు GL_లోతు_SAMPLES_NV               0x932D
#నిర్వచించు GL_STENCIL_SAMPLES_NV             0x932E
#నిర్వచించు GL_MIXED_లోతు_SAMPLES_SUPPORTED_NV 0x932F
#నిర్వచించు GL_MIXED_STENCIL_SAMPLES_SUPPORTED_NV 0x9330
#నిర్వచించు GL_COVERAGE_MODULATION_NV         0x9332
#నిర్వచించు GL_COVERAGE_MODULATION_పట్టిక_కొలత_NV 0x9333
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCOVERAGEMODULATIONTABLENVPROC) (GLsizei n, స్థిరరాశి GLfloat *v);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETCOVERAGEMODULATIONTABLENVPROC) (GLsizei buf_కొలత, GLfloat *v);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCOVERAGEMODULATIONNVPROC) (GLenum components);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_Coverage_Modulation_పట్టిక_NV (GLsizei n, స్థిరరాశి GLfloat *v);
GL_APICALL శూన్య GL_APIENTRY gl_Get_Coverage_Modulation_పట్టిక_NV (GLsizei buf_కొలత, GLfloat *v);
GL_APICALL శూన్య GL_APIENTRY glCoverageModulationNV (GLenum components);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_NV_framebuffer_mixed_samples */

#నిర్వచితం_కాకపోతే GL_NV_framebuffer_multisample
#నిర్వచించు GL_NV_framebuffer_multisample 1
#నిర్వచించు GL_RENDERBUFFER_SAMPLES_NV        0x8CAB
#నిర్వచించు GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_NV 0x8D56
#నిర్వచించు GL_MAX_SAMPLES_NV                 0x8D57
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLENVPROC) (GLenum లక్ష్యం, GLsizei samples, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glRenderbufferStorageMultisampleNV (GLenum లక్ష్యం, GLsizei samples, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_NV_framebuffer_multisample */

#నిర్వచితం_కాకపోతే GL_NV_generate_mipmap_sRGB
#నిర్వచించు GL_NV_generate_mipmap_sRGB 1
#అయితే_ముగింపు /* GL_NV_generate_mipmap_sRGB */

#నిర్వచితం_కాకపోతే GL_NV_geometry_shader_passthrough
#నిర్వచించు GL_NV_geometry_shader_passthrough 1
#అయితే_ముగింపు /* GL_NV_geometry_shader_passthrough */

#నిర్వచితం_కాకపోతే GL_NV_gpu_shader5
#నిర్వచించు GL_NV_gpu_shader5 1
రకనిర్వచనం khronos_int64_t GLint64EXT;
రకనిర్వచనం khronos_uint64_t GLuint64EXT;
#నిర్వచించు GL_INT64_NV                       0x140E
#నిర్వచించు GL_UNSIGNED_INT64_NV              0x140F
#నిర్వచించు GL_INT8_NV                        0x8FE0
#నిర్వచించు GL_INT8_VEC2_NV                   0x8FE1
#నిర్వచించు GL_INT8_VEC3_NV                   0x8FE2
#నిర్వచించు GL_INT8_VEC4_NV                   0x8FE3
#నిర్వచించు GL_INT16_NV                       0x8FE4
#నిర్వచించు GL_INT16_VEC2_NV                  0x8FE5
#నిర్వచించు GL_INT16_VEC3_NV                  0x8FE6
#నిర్వచించు GL_INT16_VEC4_NV                  0x8FE7
#నిర్వచించు GL_INT64_VEC2_NV                  0x8FE9
#నిర్వచించు GL_INT64_VEC3_NV                  0x8FEA
#నిర్వచించు GL_INT64_VEC4_NV                  0x8FEB
#నిర్వచించు GL_UNSIGNED_INT8_NV               0x8FEC
#నిర్వచించు GL_UNSIGNED_INT8_VEC2_NV          0x8FED
#నిర్వచించు GL_UNSIGNED_INT8_VEC3_NV          0x8FEE
#నిర్వచించు GL_UNSIGNED_INT8_VEC4_NV          0x8FEF
#నిర్వచించు GL_UNSIGNED_INT16_NV              0x8FF0
#నిర్వచించు GL_UNSIGNED_INT16_VEC2_NV         0x8FF1
#నిర్వచించు GL_UNSIGNED_INT16_VEC3_NV         0x8FF2
#నిర్వచించు GL_UNSIGNED_INT16_VEC4_NV         0x8FF3
#నిర్వచించు GL_UNSIGNED_INT64_VEC2_NV         0x8FF5
#నిర్వచించు GL_UNSIGNED_INT64_VEC3_NV         0x8FF6
#నిర్వచించు GL_UNSIGNED_INT64_VEC4_NV         0x8FF7
#నిర్వచించు GL_FLOAT16_NV                     0x8FF8
#నిర్వచించు GL_FLOAT16_VEC2_NV                0x8FF9
#నిర్వచించు GL_FLOAT16_VEC3_NV                0x8FFA
#నిర్వచించు GL_FLOAT16_VEC4_NV                0x8FFB
#నిర్వచించు GL_PATCHES                        0x000E
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM1I64NVPROC) (GLint location, GLint64EXT x);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM2I64NVPROC) (GLint location, GLint64EXT x, GLint64EXT y);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM3I64NVPROC) (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM4I64NVPROC) (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM1I64VNVPROC) (GLint location, GLsizei లెక్క, స్థిరరాశి GLint64EXT *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM2I64VNVPROC) (GLint location, GLsizei లెక్క, స్థిరరాశి GLint64EXT *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM3I64VNVPROC) (GLint location, GLsizei లెక్క, స్థిరరాశి GLint64EXT *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM4I64VNVPROC) (GLint location, GLsizei లెక్క, స్థిరరాశి GLint64EXT *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM1UI64NVPROC) (GLint location, GLuint64EXT x);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM2UI64NVPROC) (GLint location, GLuint64EXT x, GLuint64EXT y);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM3UI64NVPROC) (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM4UI64NVPROC) (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM1UI64VNVPROC) (GLint location, GLsizei లెక్క, స్థిరరాశి GLuint64EXT *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM2UI64VNVPROC) (GLint location, GLsizei లెక్క, స్థిరరాశి GLuint64EXT *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM3UI64VNVPROC) (GLint location, GLsizei లెక్క, స్థిరరాశి GLuint64EXT *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM4UI64VNVPROC) (GLint location, GLsizei లెక్క, స్థిరరాశి GLuint64EXT *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETUNIFORMI64VNVPROC) (GLuint కార్యక్రమం, GLint location, GLint64EXT *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM1I64NVPROC) (GLuint కార్యక్రమం, GLint location, GLint64EXT x);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM2I64NVPROC) (GLuint కార్యక్రమం, GLint location, GLint64EXT x, GLint64EXT y);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM3I64NVPROC) (GLuint కార్యక్రమం, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM4I64NVPROC) (GLuint కార్యక్రమం, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM1I64VNVPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLint64EXT *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM2I64VNVPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLint64EXT *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM3I64VNVPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLint64EXT *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM4I64VNVPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLint64EXT *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UI64NVPROC) (GLuint కార్యక్రమం, GLint location, GLuint64EXT x);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UI64NVPROC) (GLuint కార్యక్రమం, GLint location, GLuint64EXT x, GLuint64EXT y);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UI64NVPROC) (GLuint కార్యక్రమం, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UI64NVPROC) (GLuint కార్యక్రమం, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UI64VNVPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLuint64EXT *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UI64VNVPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLuint64EXT *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UI64VNVPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLuint64EXT *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UI64VNVPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLuint64EXT *విలువ);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glUniform1i64NV (GLint location, GLint64EXT x);
GL_APICALL శూన్య GL_APIENTRY glUniform2i64NV (GLint location, GLint64EXT x, GLint64EXT y);
GL_APICALL శూన్య GL_APIENTRY glUniform3i64NV (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
GL_APICALL శూన్య GL_APIENTRY glUniform4i64NV (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
GL_APICALL శూన్య GL_APIENTRY glUniform1i64vNV (GLint location, GLsizei లెక్క, స్థిరరాశి GLint64EXT *విలువ);
GL_APICALL శూన్య GL_APIENTRY glUniform2i64vNV (GLint location, GLsizei లెక్క, స్థిరరాశి GLint64EXT *విలువ);
GL_APICALL శూన్య GL_APIENTRY glUniform3i64vNV (GLint location, GLsizei లెక్క, స్థిరరాశి GLint64EXT *విలువ);
GL_APICALL శూన్య GL_APIENTRY glUniform4i64vNV (GLint location, GLsizei లెక్క, స్థిరరాశి GLint64EXT *విలువ);
GL_APICALL శూన్య GL_APIENTRY glUniform1ui64NV (GLint location, GLuint64EXT x);
GL_APICALL శూన్య GL_APIENTRY glUniform2ui64NV (GLint location, GLuint64EXT x, GLuint64EXT y);
GL_APICALL శూన్య GL_APIENTRY glUniform3ui64NV (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
GL_APICALL శూన్య GL_APIENTRY glUniform4ui64NV (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
GL_APICALL శూన్య GL_APIENTRY glUniform1ui64vNV (GLint location, GLsizei లెక్క, స్థిరరాశి GLuint64EXT *విలువ);
GL_APICALL శూన్య GL_APIENTRY glUniform2ui64vNV (GLint location, GLsizei లెక్క, స్థిరరాశి GLuint64EXT *విలువ);
GL_APICALL శూన్య GL_APIENTRY glUniform3ui64vNV (GLint location, GLsizei లెక్క, స్థిరరాశి GLuint64EXT *విలువ);
GL_APICALL శూన్య GL_APIENTRY glUniform4ui64vNV (GLint location, GLsizei లెక్క, స్థిరరాశి GLuint64EXT *విలువ);
GL_APICALL శూన్య GL_APIENTRY glGetUniformi64vNV (GLuint కార్యక్రమం, GLint location, GLint64EXT *params);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform1i64_NV (GLuint కార్యక్రమం, GLint location, GLint64EXT x);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform2i64_NV (GLuint కార్యక్రమం, GLint location, GLint64EXT x, GLint64EXT y);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform3i64_NV (GLuint కార్యక్రమం, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform4i64_NV (GLuint కార్యక్రమం, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform1i64v_NV (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLint64EXT *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform2i64v_NV (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLint64EXT *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform3i64v_NV (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLint64EXT *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform4i64v_NV (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLint64EXT *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform1ui64_NV (GLuint కార్యక్రమం, GLint location, GLuint64EXT x);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform2ui64_NV (GLuint కార్యక్రమం, GLint location, GLuint64EXT x, GLuint64EXT y);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform3ui64_NV (GLuint కార్యక్రమం, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform4ui64_NV (GLuint కార్యక్రమం, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform1ui64v_NV (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLuint64EXT *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform2ui64v_NV (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLuint64EXT *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform3ui64v_NV (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLuint64EXT *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform4ui64v_NV (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLuint64EXT *విలువ);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_NV_gpu_shader5 */

#నిర్వచితం_కాకపోతే GL_NV_image_formats
#నిర్వచించు GL_NV_image_formats 1
#అయితే_ముగింపు /* GL_NV_image_formats */

#నిర్వచితం_కాకపోతే GL_NV_instanced_arrays
#నిర్వచించు GL_NV_instanced_arrays 1
#నిర్వచించు GL_శీర్షం_ATTRIB_ARRAY_భాజకం_NV 0x88FE
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLVERTEXATTRIBDIVISORNVPROC) (GLuint సూచీ, GLuint భాజకం);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_శీర్షం_Attrib_భాజకం_NV (GLuint సూచీ, GLuint భాజకం);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_NV_instanced_arrays */

#నిర్వచితం_కాకపోతే GL_NV_internalformat_sample_query
#నిర్వచించు GL_NV_internalformat_sample_query 1
#నిర్వచించు GL_TEXTURE_2D_MULTISAMPLE         0x9100
#నిర్వచించు GL_TEXTURE_2D_MULTISAMPLE_ARRAY   0x9102
#నిర్వచించు GL_MULTISAMPLES_NV                0x9371
#నిర్వచించు GL_SUPERSAMPLE_SCALE_X_NV         0x9372
#నిర్వచించు GL_SUPERSAMPLE_SCALE_Y_NV         0x9373
#నిర్వచించు GL_CONFORMANT_NV                  0x9374
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETINTERNALFORMATSAMPLEIVNVPROC) (GLenum లక్ష్యం, GLenum internalformat, GLsizei samples, GLenum pname, GLsizei లెక్క, GLint *params);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glGetInternalformatSampleivNV (GLenum లక్ష్యం, GLenum internalformat, GLsizei samples, GLenum pname, GLsizei లెక్క, GLint *params);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_NV_internalformat_sample_query */

#నిర్వచితం_కాకపోతే GL_NV_జ్ఞాపకం_attachment
#నిర్వచించు GL_NV_జ్ఞాపకం_attachment 1
#నిర్వచించు GL_ATTACHED_జ్ఞాపకం_OBJECT_NV      0x95A4
#నిర్వచించు GL_ATTACHED_జ్ఞాపకం_స్థానభ్రంశం_NV      0x95A5
#నిర్వచించు GL_జ్ఞాపకం_ATTACHABLE_ALIGNMENT_NV 0x95A6
#నిర్వచించు GL_జ్ఞాపకం_ATTACHABLE_కొలత_NV      0x95A7
#నిర్వచించు GL_జ్ఞాపకం_ATTACHABLE_NV           0x95A8
#నిర్వచించు GL_DETACHED_జ్ఞాపకం_INCARNATION_NV 0x95A9
#నిర్వచించు GL_DETACHED_TEXTURES_NV           0x95AA
#నిర్వచించు GL_DETACHED_BUFFERS_NV            0x95AB
#నిర్వచించు GL_MAX_DETACHED_TEXTURES_NV       0x95AC
#నిర్వచించు GL_MAX_DETACHED_BUFFERS_NV        0x95AD
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETMEMORYOBJECTDETACHEDRESOURCESUIVNVPROC) (GLuint జ్ఞాపకం, GLenum pname, GLint మొదటి, GLsizei లెక్క, GLuint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLRESETMEMORYOBJECTPARAMETERNVPROC) (GLuint జ్ఞాపకం, GLenum pname);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXATTACHMEMORYNVPROC) (GLenum లక్ష్యం, GLuint జ్ఞాపకం, GLuint64 స్థానభ్రంశం_2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBUFFERATTACHMEMORYNVPROC) (GLenum లక్ష్యం, GLuint జ్ఞాపకం, GLuint64 స్థానభ్రంశం_2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXTUREATTACHMEMORYNVPROC) (GLuint texture, GLuint జ్ఞాపకం, GLuint64 స్థానభ్రంశం_2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLNAMEDBUFFERATTACHMEMORYNVPROC) (GLuint బఫరు_2, GLuint జ్ఞాపకం, GLuint64 స్థానభ్రంశం_2);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_Get_జ్ఞాపకం_Object_Detached_Resourcesuiv_NV (GLuint జ్ఞాపకం, GLenum pname, GLint మొదటి, GLsizei లెక్క, GLuint *params);
GL_APICALL శూన్య GL_APIENTRY gl_Reset_జ్ఞాపకం_Object_Parameter_NV (GLuint జ్ఞాపకం, GLenum pname);
GL_APICALL శూన్య GL_APIENTRY gl_Tex_Attach_జ్ఞాపకం_NV (GLenum లక్ష్యం, GLuint జ్ఞాపకం, GLuint64 స్థానభ్రంశం_2);
GL_APICALL శూన్య GL_APIENTRY gl_బఫరు_Attach_జ్ఞాపకం_NV (GLenum లక్ష్యం, GLuint జ్ఞాపకం, GLuint64 స్థానభ్రంశం_2);
GL_APICALL శూన్య GL_APIENTRY gl_Texture_Attach_జ్ఞాపకం_NV (GLuint texture, GLuint జ్ఞాపకం, GLuint64 స్థానభ్రంశం_2);
GL_APICALL శూన్య GL_APIENTRY gl_Named_బఫరు_Attach_జ్ఞాపకం_NV (GLuint బఫరు_2, GLuint జ్ఞాపకం, GLuint64 స్థానభ్రంశం_2);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_NV_memory_attachment */

#నిర్వచితం_కాకపోతే GL_NV_జ్ఞాపకం_object_sparse
#నిర్వచించు GL_NV_జ్ఞాపకం_object_sparse 1
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBUFFERPAGECOMMITMENTMEMNVPROC) (GLenum లక్ష్యం, GLintptr స్థానభ్రంశం_2, GLsizeiptr కొలత, GLuint జ్ఞాపకం, GLuint64 mem_స్థానభ్రంశం, GLboolean commit);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXPAGECOMMITMENTMEMNVPROC) (GLenum లక్ష్యం, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLuint జ్ఞాపకం, GLuint64 స్థానభ్రంశం_2, GLboolean commit);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLNAMEDBUFFERPAGECOMMITMENTMEMNVPROC) (GLuint బఫరు_2, GLintptr స్థానభ్రంశం_2, GLsizeiptr కొలత, GLuint జ్ఞాపకం, GLuint64 mem_స్థానభ్రంశం, GLboolean commit);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXTUREPAGECOMMITMENTMEMNVPROC) (GLuint texture, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLuint జ్ఞాపకం, GLuint64 స్థానభ్రంశం_2, GLboolean commit);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_బఫరు_పుట_Commitment_Mem_NV (GLenum లక్ష్యం, GLintptr స్థానభ్రంశం_2, GLsizeiptr కొలత, GLuint జ్ఞాపకం, GLuint64 mem_స్థానభ్రంశం, GLboolean commit);
GL_APICALL శూన్య GL_APIENTRY gl_Tex_పుట_Commitment_Mem_NV (GLenum లక్ష్యం, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLuint జ్ఞాపకం, GLuint64 స్థానభ్రంశం_2, GLboolean commit);
GL_APICALL శూన్య GL_APIENTRY gl_Named_బఫరు_పుట_Commitment_Mem_NV (GLuint బఫరు_2, GLintptr స్థానభ్రంశం_2, GLsizeiptr కొలత, GLuint జ్ఞాపకం, GLuint64 mem_స్థానభ్రంశం, GLboolean commit);
GL_APICALL శూన్య GL_APIENTRY gl_Texture_పుట_Commitment_Mem_NV (GLuint texture, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLuint జ్ఞాపకం, GLuint64 స్థానభ్రంశం_2, GLboolean commit);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_NV_memory_object_sparse */

#నిర్వచితం_కాకపోతే GL_NV_mesh_shader
#నిర్వచించు GL_NV_mesh_shader 1
#నిర్వచించు GL_MESH_SHADER_NV                 0x9559
#నిర్వచించు GL_TASK_SHADER_NV                 0x955A
#నిర్వచించు GL_MAX_MESH_ఏకరీతి_ఖండాలు_NV     0x8E60
#నిర్వచించు GL_MAX_MESH_TEXTURE_IMAGE_UNITS_NV 0x8E61
#నిర్వచించు GL_MAX_MESH_IMAGE_UNIFORMS_NV     0x8E62
#నిర్వచించు GL_MAX_MESH_ఏకరీతి_COMPONENTS_NV 0x8E63
#నిర్వచించు GL_MAX_MESH_ATOMIC_COUNTER_BUFFERS_NV 0x8E64
#నిర్వచించు GL_MAX_MESH_ATOMIC_COUNTERS_NV    0x8E65
#నిర్వచించు GL_MAX_MESH_SHADER_STORAGE_ఖండాలు_NV 0x8E66
#నిర్వచించు GL_MAX_COMBINED_MESH_ఏకరీతి_COMPONENTS_NV 0x8E67
#నిర్వచించు GL_MAX_TASK_ఏకరీతి_ఖండాలు_NV     0x8E68
#నిర్వచించు GL_MAX_TASK_TEXTURE_IMAGE_UNITS_NV 0x8E69
#నిర్వచించు GL_MAX_TASK_IMAGE_UNIFORMS_NV     0x8E6A
#నిర్వచించు GL_MAX_TASK_ఏకరీతి_COMPONENTS_NV 0x8E6B
#నిర్వచించు GL_MAX_TASK_ATOMIC_COUNTER_BUFFERS_NV 0x8E6C
#నిర్వచించు GL_MAX_TASK_ATOMIC_COUNTERS_NV    0x8E6D
#నిర్వచించు GL_MAX_TASK_SHADER_STORAGE_ఖండాలు_NV 0x8E6E
#నిర్వచించు GL_MAX_COMBINED_TASK_ఏకరీతి_COMPONENTS_NV 0x8E6F
#నిర్వచించు GL_MAX_MESH_WORK_సమూహం_INVOCATIONS_NV 0x95A2
#నిర్వచించు GL_MAX_TASK_WORK_సమూహం_INVOCATIONS_NV 0x95A3
#నిర్వచించు GL_MAX_MESH_మొత్తం_జ్ఞాపకం_కొలత_NV  0x9536
#నిర్వచించు GL_MAX_TASK_మొత్తం_జ్ఞాపకం_కొలత_NV  0x9537
#నిర్వచించు GL_MAX_MESH_OUTPUT_VERTICES_NV    0x9538
#నిర్వచించు GL_MAX_MESH_OUTPUT_PRIMITIVES_NV  0x9539
#నిర్వచించు GL_MAX_TASK_OUTPUT_లెక్క_NV       0x953A
#నిర్వచించు GL_MAX_DRAW_MESH_TASKS_లెక్క_NV   0x953D
#నిర్వచించు GL_MAX_MESH_VIEWS_NV              0x9557
#నిర్వచించు GL_MESH_OUTPUT_చొప్పున_శీర్షం_GRANULARITY_NV 0x92DF
#నిర్వచించు GL_MESH_OUTPUT_చొప్పున_PRIMITIVE_GRANULARITY_NV 0x9543
#నిర్వచించు GL_MAX_MESH_WORK_సమూహం_కొలత_NV    0x953B
#నిర్వచించు GL_MAX_TASK_WORK_సమూహం_కొలత_NV    0x953C
#నిర్వచించు GL_MESH_WORK_సమూహం_కొలత_NV        0x953E
#నిర్వచించు GL_TASK_WORK_సమూహం_కొలత_NV        0x953F
#నిర్వచించు GL_MESH_VERTICES_బహిర్గతం_NV           0x9579
#నిర్వచించు GL_MESH_PRIMITIVES_బహిర్గతం_NV         0x957A
#నిర్వచించు GL_MESH_OUTPUT_TYPE_NV            0x957B
#నిర్వచించు GL_ఏకరీతి_ఖండం_REFERENCED_BY_MESH_SHADER_NV 0x959C
#నిర్వచించు GL_ఏకరీతి_ఖండం_REFERENCED_BY_TASK_SHADER_NV 0x959D
#నిర్వచించు GL_REFERENCED_BY_MESH_SHADER_NV   0x95A0
#నిర్వచించు GL_REFERENCED_BY_TASK_SHADER_NV   0x95A1
#నిర్వచించు GL_MESH_SHADER_బిట్టు_NV             0x00000040
#నిర్వచించు GL_TASK_SHADER_బిట్టు_NV             0x00000080
#నిర్వచించు GL_MESH_SUBROUTINE_NV             0x957C
#నిర్వచించు GL_TASK_SUBROUTINE_NV             0x957D
#నిర్వచించు GL_MESH_SUBROUTINE_ఏకరీతి_NV     0x957E
#నిర్వచించు GL_TASK_SUBROUTINE_ఏకరీతి_NV     0x957F
#నిర్వచించు GL_ATOMIC_COUNTER_బఫరు_REFERENCED_BY_MESH_SHADER_NV 0x959E
#నిర్వచించు GL_ATOMIC_COUNTER_బఫరు_REFERENCED_BY_TASK_SHADER_NV 0x959F
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWMESHTASKSNVPROC) (GLuint మొదటి, GLuint లెక్క);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWMESHTASKSINDIRECTNVPROC) (GLintptr పరోక్ష);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMULTIDRAWMESHTASKSINDIRECTNVPROC) (GLintptr పరోక్ష, GLsizei drawcount, GLsizei stride);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTNVPROC) (GLintptr పరోక్ష, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glDrawMeshTasksNV (GLuint మొదటి, GLuint లెక్క);
GL_APICALL శూన్య GL_APIENTRY gl_Draw_Mesh_Tasks_పరోక్ష_NV (GLintptr పరోక్ష);
GL_APICALL శూన్య GL_APIENTRY gl_Multi_Draw_Mesh_Tasks_పరోక్ష_NV (GLintptr పరోక్ష, GLsizei drawcount, GLsizei stride);
GL_APICALL శూన్య GL_APIENTRY gl_Multi_Draw_Mesh_Tasks_పరోక్ష_లెక్క_NV (GLintptr పరోక్ష, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_NV_mesh_shader */

#నిర్వచితం_కాకపోతే GL_NV_non_వర్గం_matrices
#నిర్వచించు GL_NV_non_వర్గం_matrices 1
#నిర్వచించు GL_FLOAT_MAT2x3_NV                0x8B65
#నిర్వచించు GL_FLOAT_MAT2x4_NV                0x8B66
#నిర్వచించు GL_FLOAT_MAT3x2_NV                0x8B67
#నిర్వచించు GL_FLOAT_MAT3x4_NV                0x8B68
#నిర్వచించు GL_FLOAT_MAT4x2_NV                0x8B69
#నిర్వచించు GL_FLOAT_MAT4x3_NV                0x8B6A
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORMMATRIX2X3FVNVPROC) (GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORMMATRIX3X2FVNVPROC) (GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORMMATRIX2X4FVNVPROC) (GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORMMATRIX4X2FVNVPROC) (GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORMMATRIX3X4FVNVPROC) (GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORMMATRIX4X3FVNVPROC) (GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_ఏకరీతి_Matrix2x3fv_NV (GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_ఏకరీతి_Matrix3x2fv_NV (GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_ఏకరీతి_Matrix2x4fv_NV (GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_ఏకరీతి_Matrix4x2fv_NV (GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_ఏకరీతి_Matrix3x4fv_NV (GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_ఏకరీతి_Matrix4x3fv_NV (GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_NV_non_square_matrices */

#నిర్వచితం_కాకపోతే GL_NV_pack_subimage
#నిర్వచించు GL_NV_pack_subimage 1
#నిర్వచించు GL_PACK_అడ్డువరుస_నిడివి_NV             0x0D02
#నిర్వచించు GL_PACK_SKIP_అడ్డువరుసలు_NV              0x0D03
#నిర్వచించు GL_PACK_SKIP_PIXELS_NV            0x0D04
#అయితే_ముగింపు /* GL_NV_pack_subimage */

#నిర్వచితం_కాకపోతే GL_NV_మార్గం_rendering
#నిర్వచించు GL_NV_మార్గం_rendering 1
రకనిర్వచనం ద్విగుణ GLdouble;
#నిర్వచించు GL_మార్గం_FORMAT_SVG_NV             0x9070
#నిర్వచించు GL_మార్గం_FORMAT_PS_NV              0x9071
#నిర్వచించు GL_STANDARD_FONT_NAME_NV          0x9072
#నిర్వచించు GL_SYSTEM_FONT_NAME_NV            0x9073
#నిర్వచించు GL_FILE_NAME_NV                   0x9074
#నిర్వచించు GL_మార్గం_STROKE_వెడల్పు_NV           0x9075
#నిర్వచించు GL_మార్గం_చివర_CAPS_NV               0x9076
#నిర్వచించు GL_మార్గం_INITIAL_చివర_CAP_NV        0x9077
#నిర్వచించు GL_మార్గం_TERMINAL_చివర_CAP_NV       0x9078
#నిర్వచించు GL_మార్గం_JOIN_STYLE_NV             0x9079
#నిర్వచించు GL_మార్గం_MITER_హద్దు_NV            0x907A
#నిర్వచించు GL_మార్గం_DASH_CAPS_NV              0x907B
#నిర్వచించు GL_మార్గం_INITIAL_DASH_CAP_NV       0x907C
#నిర్వచించు GL_మార్గం_TERMINAL_DASH_CAP_NV      0x907D
#నిర్వచించు GL_మార్గం_DASH_స్థానభ్రంశం_NV            0x907E
#నిర్వచించు GL_మార్గం_CLIENT_నిడివి_NV          0x907F
#నిర్వచించు GL_మార్గం_FILL_బహుళకం_NV              0x9080
#నిర్వచించు GL_మార్గం_FILL_ముసుగు_NV              0x9081
#నిర్వచించు GL_మార్గం_FILL_COVER_బహుళకం_NV        0x9082
#నిర్వచించు GL_మార్గం_STROKE_COVER_బహుళకం_NV      0x9083
#నిర్వచించు GL_మార్గం_STROKE_ముసుగు_NV            0x9084
#నిర్వచించు GL_లెక్క_పైకి_NV                    0x9088
#నిర్వచించు GL_లెక్క_కిందికి_NV                  0x9089
#నిర్వచించు GL_మార్గం_OBJECT_BOUNDING_BOX_NV    0x908A
#నిర్వచించు GL_CONVEX_HULL_NV                 0x908B
#నిర్వచించు GL_BOUNDING_BOX_NV                0x908D
#నిర్వచించు GL_TRANSLATE_X_NV                 0x908E
#నిర్వచించు GL_TRANSLATE_Y_NV                 0x908F
#నిర్వచించు GL_TRANSLATE_2D_NV                0x9090
#నిర్వచించు GL_TRANSLATE_3D_NV                0x9091
#నిర్వచించు GL_AFFINE_2D_NV                   0x9092
#నిర్వచించు GL_AFFINE_3D_NV                   0x9094
#నిర్వచించు GL_TRANSPOSE_AFFINE_2D_NV         0x9096
#నిర్వచించు GL_TRANSPOSE_AFFINE_3D_NV         0x9098
#నిర్వచించు GL_UTF8_NV                        0x909A
#నిర్వచించు GL_UTF16_NV                       0x909B
#నిర్వచించు GL_BOUNDING_BOX_యొక్క_BOUNDING_BOXES_NV 0x909C
#నిర్వచించు GL_మార్గం_COMMAND_లెక్క_NV          0x909D
#నిర్వచించు GL_మార్గం_COORD_లెక్క_NV            0x909E
#నిర్వచించు GL_మార్గం_DASH_ARRAY_లెక్క_NV       0x909F
#నిర్వచించు GL_మార్గం_COMPUTED_నిడివి_NV        0x90A0
#నిర్వచించు GL_మార్గం_FILL_BOUNDING_BOX_NV      0x90A1
#నిర్వచించు GL_మార్గం_STROKE_BOUNDING_BOX_NV    0x90A2
#నిర్వచించు GL_వర్గం_NV                      0x90A3
#నిర్వచించు GL_విడత_NV                       0x90A4
#నిర్వచించు GL_TRIANGULAR_NV                  0x90A5
#నిర్వచించు GL_BEVEL_NV                       0x90A6
#నిర్వచించు GL_MITER_REVERT_NV                0x90A7
#నిర్వచించు GL_MITER_TRUNCATE_NV              0x90A8
#నిర్వచించు GL_SKIP_MISSING_GLYPH_NV          0x90A9
#నిర్వచించు GL_USE_MISSING_GLYPH_NV           0x90AA
#నిర్వచించు GL_మార్గం_ERROR_POSITION_NV         0x90AB
#నిర్వచించు GL_ACCUM_ADJACENT_జతలు_NV        0x90AD
#నిర్వచించు GL_ADJACENT_జతలు_NV              0x90AE
#నిర్వచించు GL_మొదటి_గమ్యం_REST_NV               0x90AF
#నిర్వచించు GL_మార్గం_GEN_బహుళకం_NV               0x90B0
#నిర్వచించు GL_మార్గం_GEN_COEFF_NV              0x90B1
#నిర్వచించు GL_మార్గం_GEN_COMPONENTS_NV         0x90B3
#నిర్వచించు GL_మార్గం_STENCIL_FUNC_NV           0x90B7
#నిర్వచించు GL_మార్గం_STENCIL_REF_NV            0x90B8
#నిర్వచించు GL_మార్గం_STENCIL_విలువ_ముసుగు_NV     0x90B9
#నిర్వచించు GL_మార్గం_STENCIL_లోతు_స్థానభ్రంశం_గుణకం_NV 0x90BD
#నిర్వచించు GL_మార్గం_STENCIL_లోతు_స్థానభ్రంశం_UNITS_NV 0x90BE
#నిర్వచించు GL_మార్గం_COVER_లోతు_FUNC_NV       0x90BF
#నిర్వచించు GL_మార్గం_DASH_స్థానభ్రంశం_RESET_NV      0x90B4
#నిర్వచించు GL_MOVE_గమ్యం_RESETS_NV              0x90B5
#నిర్వచించు GL_MOVE_గమ్యం_CONTINUES_NV           0x90B6
#నిర్వచించు GL_CLOSE_మార్గం_NV                  0x00
#నిర్వచించు GL_MOVE_గమ్యం_NV                     0x02
#నిర్వచించు GL_RELATIVE_MOVE_గమ్యం_NV            0x03
#నిర్వచించు GL_పంక్తి_గమ్యం_NV                     0x04
#నిర్వచించు GL_RELATIVE_పంక్తి_గమ్యం_NV            0x05
#నిర్వచించు GL_HORIZONTAL_పంక్తి_గమ్యం_NV          0x06
#నిర్వచించు GL_RELATIVE_HORIZONTAL_పంక్తి_గమ్యం_NV 0x07
#నిర్వచించు GL_VERTICAL_పంక్తి_గమ్యం_NV            0x08
#నిర్వచించు GL_RELATIVE_VERTICAL_పంక్తి_గమ్యం_NV   0x09
#నిర్వచించు GL_QUADRATIC_వక్రం_గమ్యం_NV          0x0A
#నిర్వచించు GL_RELATIVE_QUADRATIC_వక్రం_గమ్యం_NV 0x0B
#నిర్వచించు GL_CUBIC_వక్రం_గమ్యం_NV              0x0C
#నిర్వచించు GL_RELATIVE_CUBIC_వక్రం_గమ్యం_NV     0x0D
#నిర్వచించు GL_SMOOTH_QUADRATIC_వక్రం_గమ్యం_NV   0x0E
#నిర్వచించు GL_RELATIVE_SMOOTH_QUADRATIC_వక్రం_గమ్యం_NV 0x0F
#నిర్వచించు GL_SMOOTH_CUBIC_వక్రం_గమ్యం_NV       0x10
#నిర్వచించు GL_RELATIVE_SMOOTH_CUBIC_వక్రం_గమ్యం_NV 0x11
#నిర్వచించు GL_SMALL_CCW_ARC_గమ్యం_NV            0x12
#నిర్వచించు GL_RELATIVE_SMALL_CCW_ARC_గమ్యం_NV   0x13
#నిర్వచించు GL_SMALL_CW_ARC_గమ్యం_NV             0x14
#నిర్వచించు GL_RELATIVE_SMALL_CW_ARC_గమ్యం_NV    0x15
#నిర్వచించు GL_LARGE_CCW_ARC_గమ్యం_NV            0x16
#నిర్వచించు GL_RELATIVE_LARGE_CCW_ARC_గమ్యం_NV   0x17
#నిర్వచించు GL_LARGE_CW_ARC_గమ్యం_NV             0x18
#నిర్వచించు GL_RELATIVE_LARGE_CW_ARC_గమ్యం_NV    0x19
#నిర్వచించు GL_RESTART_మార్గం_NV                0xF0
#నిర్వచించు GL_DUP_మొదటి_CUBIC_వక్రం_గమ్యం_NV    0xF2
#నిర్వచించు GL_DUP_చివరి_CUBIC_వక్రం_గమ్యం_NV     0xF4
#నిర్వచించు GL_RECT_NV                        0xF6
#నిర్వచించు GL_CIRCULAR_CCW_ARC_గమ్యం_NV         0xF8
#నిర్వచించు GL_CIRCULAR_CW_ARC_గమ్యం_NV          0xFA
#నిర్వచించు GL_CIRCULAR_TANGENT_ARC_గమ్యం_NV     0xFC
#నిర్వచించు GL_ARC_గమ్యం_NV                      0xFE
#నిర్వచించు GL_RELATIVE_ARC_గమ్యం_NV             0xFF
#నిర్వచించు GL_BOLD_బిట్టు_NV                    0x01
#నిర్వచించు GL_ITALIC_బిట్టు_NV                  0x02
#నిర్వచించు GL_GLYPH_వెడల్పు_బిట్టు_NV             0x01
#నిర్వచించు GL_GLYPH_ఎత్తు_బిట్టు_NV            0x02
#నిర్వచించు GL_GLYPH_HORIZONTAL_BEARING_X_బిట్టు_NV 0x04
#నిర్వచించు GL_GLYPH_HORIZONTAL_BEARING_Y_బిట్టు_NV 0x08
#నిర్వచించు GL_GLYPH_HORIZONTAL_BEARING_ADVANCE_బిట్టు_NV 0x10
#నిర్వచించు GL_GLYPH_VERTICAL_BEARING_X_బిట్టు_NV 0x20
#నిర్వచించు GL_GLYPH_VERTICAL_BEARING_Y_బిట్టు_NV 0x40
#నిర్వచించు GL_GLYPH_VERTICAL_BEARING_ADVANCE_బిట్టు_NV 0x80
#నిర్వచించు GL_GLYPH_HAS_KERNING_బిట్టు_NV       0x100
#నిర్వచించు GL_FONT_X_MIN_BOUNDS_బిట్టు_NV       0x00010000
#నిర్వచించు GL_FONT_Y_MIN_BOUNDS_బిట్టు_NV       0x00020000
#నిర్వచించు GL_FONT_X_MAX_BOUNDS_బిట్టు_NV       0x00040000
#నిర్వచించు GL_FONT_Y_MAX_BOUNDS_బిట్టు_NV       0x00080000
#నిర్వచించు GL_FONT_UNITS_చొప్పున_EM_బిట్టు_NV       0x00100000
#నిర్వచించు GL_FONT_ASCENDER_బిట్టు_NV           0x00200000
#నిర్వచించు GL_FONT_DESCENDER_బిట్టు_NV          0x00400000
#నిర్వచించు GL_FONT_ఎత్తు_బిట్టు_NV             0x00800000
#నిర్వచించు GL_FONT_MAX_ADVANCE_వెడల్పు_బిట్టు_NV  0x01000000
#నిర్వచించు GL_FONT_MAX_ADVANCE_ఎత్తు_బిట్టు_NV 0x02000000
#నిర్వచించు GL_FONT_UNDERLINE_POSITION_బిట్టు_NV 0x04000000
#నిర్వచించు GL_FONT_UNDERLINE_THICKNESS_బిట్టు_NV 0x08000000
#నిర్వచించు GL_FONT_HAS_KERNING_బిట్టు_NV        0x10000000
#నిర్వచించు GL_ROUNDED_RECT_NV                0xE8
#నిర్వచించు GL_RELATIVE_ROUNDED_RECT_NV       0xE9
#నిర్వచించు GL_ROUNDED_RECT2_NV               0xEA
#నిర్వచించు GL_RELATIVE_ROUNDED_RECT2_NV      0xEB
#నిర్వచించు GL_ROUNDED_RECT4_NV               0xEC
#నిర్వచించు GL_RELATIVE_ROUNDED_RECT4_NV      0xED
#నిర్వచించు GL_ROUNDED_RECT8_NV               0xEE
#నిర్వచించు GL_RELATIVE_ROUNDED_RECT8_NV      0xEF
#నిర్వచించు GL_RELATIVE_RECT_NV               0xF7
#నిర్వచించు GL_FONT_GLYPHS_అందుబాటు_NV       0x9368
#నిర్వచించు GL_FONT_లక్ష్యం_UNAVAILABLE_NV     0x9369
#నిర్వచించు GL_FONT_UNAVAILABLE_NV            0x936A
#నిర్వచించు GL_FONT_UNINTELLIGIBLE_NV         0x936B
#నిర్వచించు GL_CONIC_వక్రం_గమ్యం_NV              0x1A
#నిర్వచించు GL_RELATIVE_CONIC_వక్రం_గమ్యం_NV     0x1B
#నిర్వచించు GL_FONT_అంకె_GLYPH_INDICES_బిట్టు_NV  0x20000000
#నిర్వచించు GL_STANDARD_FONT_FORMAT_NV        0x936C
#నిర్వచించు GL_మార్గం_PROJECTION_NV             0x1701
#నిర్వచించు GL_మార్గం_MODELVIEW_NV              0x1700
#నిర్వచించు GL_మార్గం_MODELVIEW_దొంతర_లోతు_NV  0x0BA3
#నిర్వచించు GL_మార్గం_MODELVIEW_మాతృక_NV       0x0BA6
#నిర్వచించు GL_మార్గం_MAX_MODELVIEW_దొంతర_లోతు_NV 0x0D36
#నిర్వచించు GL_మార్గం_TRANSPOSE_MODELVIEW_మాతృక_NV 0x84E3
#నిర్వచించు GL_మార్గం_PROJECTION_దొంతర_లోతు_NV 0x0BA4
#నిర్వచించు GL_మార్గం_PROJECTION_మాతృక_NV      0x0BA7
#నిర్వచించు GL_మార్గం_MAX_PROJECTION_దొంతర_లోతు_NV 0x0D38
#నిర్వచించు GL_మార్గం_TRANSPOSE_PROJECTION_మాతృక_NV 0x84E4
#నిర్వచించు GL_FRAGMENT_ఆదానం_NV              0x936D
రకనిర్వచనం GLuint (GL_APIENTRYP PFNGLGENPATHSNVPROC) (GLsizei range);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDELETEPATHSNVPROC) (GLuint మార్గం, GLsizei range);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLISPATHNVPROC) (GLuint మార్గం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPATHCOMMANDSNVPROC) (GLuint మార్గం, GLsizei అంకె_Commands, స్థిరరాశి GLubyte *commands, GLsizei అంకె_Coords, GLenum coordType, స్థిరరాశి శూన్య *coords);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPATHCOORDSNVPROC) (GLuint మార్గం, GLsizei అంకె_Coords, GLenum coordType, స్థిరరాశి శూన్య *coords);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPATHSUBCOMMANDSNVPROC) (GLuint మార్గం, GLsizei command_ప్రారంభం, GLsizei commands_గమ్యం_Delete, GLsizei అంకె_Commands, స్థిరరాశి GLubyte *commands, GLsizei అంకె_Coords, GLenum coordType, స్థిరరాశి శూన్య *coords);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPATHSUBCOORDSNVPROC) (GLuint మార్గం, GLsizei coord_ప్రారంభం, GLsizei అంకె_Coords, GLenum coordType, స్థిరరాశి శూన్య *coords);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPATHSTRINGNVPROC) (GLuint మార్గం, GLenum format, GLsizei నిడివి, స్థిరరాశి శూన్య *మార్గం_String);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPATHGLYPHSNVPROC) (GLuint మొదటి_మార్గం_Name, GLenum font_లక్ష్యం, స్థిరరాశి శూన్య *fontName, GLbitfield fontStyle, GLsizei అంకె_Glyphs, GLenum type, స్థిరరాశి శూన్య *charcodes, GLenum handleMissingGlyphs, GLuint మార్గం_Parameter_Template, GLfloat emScale);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPATHGLYPHRANGENVPROC) (GLuint మొదటి_మార్గం_Name, GLenum font_లక్ష్యం, స్థిరరాశి శూన్య *fontName, GLbitfield fontStyle, GLuint మొదటి_Glyph, GLsizei అంకె_Glyphs, GLenum handleMissingGlyphs, GLuint మార్గం_Parameter_Template, GLfloat emScale);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLWEIGHTPATHSNVPROC) (GLuint ఫలితం_మార్గం, GLsizei అంకె_Paths, స్థిరరాశి GLuint *paths, స్థిరరాశి GLfloat *weights);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCOPYPATHNVPROC) (GLuint ఫలితం_మార్గం, GLuint src_మార్గం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLINTERPOLATEPATHSNVPROC) (GLuint ఫలితం_మార్గం, GLuint మార్గం_A, GLuint మార్గం_B, GLfloat బరువు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTRANSFORMPATHNVPROC) (GLuint ఫలితం_మార్గం, GLuint src_మార్గం, GLenum transformType, స్థిరరాశి GLfloat *transform_విలువలు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPATHPARAMETERIVNVPROC) (GLuint మార్గం, GLenum pname, స్థిరరాశి GLint *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPATHPARAMETERINVPROC) (GLuint మార్గం, GLenum pname, GLint విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPATHPARAMETERFVNVPROC) (GLuint మార్గం, GLenum pname, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPATHPARAMETERFNVPROC) (GLuint మార్గం, GLenum pname, GLfloat విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPATHDASHARRAYNVPROC) (GLuint మార్గం, GLsizei dash_లెక్క, స్థిరరాశి GLfloat *dashArray);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPATHSTENCILFUNCNVPROC) (GLenum func, GLint ref, GLuint ముసుగు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPATHSTENCILDEPTHOFFSETNVPROC) (GLfloat గుణకం, GLfloat units);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSTENCILFILLPATHNVPROC) (GLuint మార్గం, GLenum fill_బహుళకం, GLuint ముసుగు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSTENCILSTROKEPATHNVPROC) (GLuint మార్గం, GLint reference, GLuint ముసుగు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSTENCILFILLPATHINSTANCEDNVPROC) (GLsizei అంకె_Paths, GLenum మార్గం_Name_Type, స్థిరరాశి శూన్య *paths, GLuint మార్గం_పునాది, GLenum fill_బహుళకం, GLuint ముసుగు, GLenum transformType, స్థిరరాశి GLfloat *transform_విలువలు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSTENCILSTROKEPATHINSTANCEDNVPROC) (GLsizei అంకె_Paths, GLenum మార్గం_Name_Type, స్థిరరాశి శూన్య *paths, GLuint మార్గం_పునాది, GLint reference, GLuint ముసుగు, GLenum transformType, స్థిరరాశి GLfloat *transform_విలువలు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPATHCOVERDEPTHFUNCNVPROC) (GLenum func);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCOVERFILLPATHNVPROC) (GLuint మార్గం, GLenum cover_బహుళకం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCOVERSTROKEPATHNVPROC) (GLuint మార్గం, GLenum cover_బహుళకం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCOVERFILLPATHINSTANCEDNVPROC) (GLsizei అంకె_Paths, GLenum మార్గం_Name_Type, స్థిరరాశి శూన్య *paths, GLuint మార్గం_పునాది, GLenum cover_బహుళకం, GLenum transformType, స్థిరరాశి GLfloat *transform_విలువలు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCOVERSTROKEPATHINSTANCEDNVPROC) (GLsizei అంకె_Paths, GLenum మార్గం_Name_Type, స్థిరరాశి శూన్య *paths, GLuint మార్గం_పునాది, GLenum cover_బహుళకం, GLenum transformType, స్థిరరాశి GLfloat *transform_విలువలు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETPATHPARAMETERIVNVPROC) (GLuint మార్గం, GLenum pname, GLint *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETPATHPARAMETERFVNVPROC) (GLuint మార్గం, GLenum pname, GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETPATHCOMMANDSNVPROC) (GLuint మార్గం, GLubyte *commands);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETPATHCOORDSNVPROC) (GLuint మార్గం, GLfloat *coords);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETPATHDASHARRAYNVPROC) (GLuint మార్గం, GLfloat *dashArray);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETPATHMETRICSNVPROC) (GLbitfield metric_Query_ముసుగు, GLsizei అంకె_Paths, GLenum మార్గం_Name_Type, స్థిరరాశి శూన్య *paths, GLuint మార్గం_పునాది, GLsizei stride, GLfloat *metrics);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETPATHMETRICRANGENVPROC) (GLbitfield metric_Query_ముసుగు, GLuint మొదటి_మార్గం_Name, GLsizei అంకె_Paths, GLsizei stride, GLfloat *metrics);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETPATHSPACINGNVPROC) (GLenum మార్గం_List_బహుళకం, GLsizei అంకె_Paths, GLenum మార్గం_Name_Type, స్థిరరాశి శూన్య *paths, GLuint మార్గం_పునాది, GLfloat advanceScale, GLfloat kerningScale, GLenum transformType, GLfloat *returnedSpacing);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLISPOINTINFILLPATHNVPROC) (GLuint మార్గం, GLuint ముసుగు, GLfloat x, GLfloat y);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLISPOINTINSTROKEPATHNVPROC) (GLuint మార్గం, GLfloat x, GLfloat y);
రకనిర్వచనం GLfloat (GL_APIENTRYP PFNGLGETPATHLENGTHNVPROC) (GLuint మార్గం, GLsizei ప్రారంభం_Segment, GLsizei అంకె_Segments);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLPOINTALONGPATHNVPROC) (GLuint మార్గం, GLsizei ప్రారంభం_Segment, GLsizei అంకె_Segments, GLfloat దూరం, GLfloat *x, GLfloat *y, GLfloat *tangentX, GLfloat *tangentY);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMATRIXLOAD3X2FNVPROC) (GLenum మాతృక_బహుళకం, స్థిరరాశి GLfloat *m);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMATRIXLOAD3X3FNVPROC) (GLenum మాతృక_బహుళకం, స్థిరరాశి GLfloat *m);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMATRIXLOADTRANSPOSE3X3FNVPROC) (GLenum మాతృక_బహుళకం, స్థిరరాశి GLfloat *m);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMATRIXMULT3X2FNVPROC) (GLenum మాతృక_బహుళకం, స్థిరరాశి GLfloat *m);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMATRIXMULT3X3FNVPROC) (GLenum మాతృక_బహుళకం, స్థిరరాశి GLfloat *m);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMATRIXMULTTRANSPOSE3X3FNVPROC) (GLenum మాతృక_బహుళకం, స్థిరరాశి GLfloat *m);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSTENCILTHENCOVERFILLPATHNVPROC) (GLuint మార్గం, GLenum fill_బహుళకం, GLuint ముసుగు, GLenum cover_బహుళకం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSTENCILTHENCOVERSTROKEPATHNVPROC) (GLuint మార్గం, GLint reference, GLuint ముసుగు, GLenum cover_బహుళకం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSTENCILTHENCOVERFILLPATHINSTANCEDNVPROC) (GLsizei అంకె_Paths, GLenum మార్గం_Name_Type, స్థిరరాశి శూన్య *paths, GLuint మార్గం_పునాది, GLenum fill_బహుళకం, GLuint ముసుగు, GLenum cover_బహుళకం, GLenum transformType, స్థిరరాశి GLfloat *transform_విలువలు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSTENCILTHENCOVERSTROKEPATHINSTANCEDNVPROC) (GLsizei అంకె_Paths, GLenum మార్గం_Name_Type, స్థిరరాశి శూన్య *paths, GLuint మార్గం_పునాది, GLint reference, GLuint ముసుగు, GLenum cover_బహుళకం, GLenum transformType, స్థిరరాశి GLfloat *transform_విలువలు);
రకనిర్వచనం GLenum (GL_APIENTRYP PFNGLPATHGLYPHINDEXRANGENVPROC) (GLenum font_లక్ష్యం, స్థిరరాశి శూన్య *fontName, GLbitfield fontStyle, GLuint మార్గం_Parameter_Template, GLfloat emScale, GLuint *పునాది_And_లెక్క);
రకనిర్వచనం GLenum (GL_APIENTRYP PFNGLPATHGLYPHINDEXARRAYNVPROC) (GLuint మొదటి_మార్గం_Name, GLenum font_లక్ష్యం, స్థిరరాశి శూన్య *fontName, GLbitfield fontStyle, GLuint మొదటి_Glyph_సూచీ, GLsizei అంకె_Glyphs, GLuint మార్గం_Parameter_Template, GLfloat emScale);
రకనిర్వచనం GLenum (GL_APIENTRYP PFNGLPATHMEMORYGLYPHINDEXARRAYNVPROC) (GLuint మొదటి_మార్గం_Name, GLenum font_లక్ష్యం, GLsizeiptr font_కొలత, స్థిరరాశి శూన్య *font_దత్తాంశం, GLsizei face_సూచీ, GLuint మొదటి_Glyph_సూచీ, GLsizei అంకె_Glyphs, GLuint మార్గం_Parameter_Template, GLfloat emScale);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMPATHFRAGMENTINPUTGENNVPROC) (GLuint కార్యక్రమం, GLint location, GLenum gen_బహుళకం, GLint components, స్థిరరాశి GLfloat *coeffs);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETPROGRAMRESOURCEFVNVPROC) (GLuint కార్యక్రమం, GLenum కార్యక్రమం_Interface, GLuint సూచీ, GLsizei prop_లెక్క, స్థిరరాశి GLenum *props, GLsizei లెక్క, GLsizei *నిడివి, GLfloat *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMATRIXFRUSTUMEXTPROC) (GLenum బహుళకం, GLdouble ఎడమ, GLdouble కుడి, GLdouble bottom, GLdouble శిఖరం, GLdouble zNear, GLdouble zFar);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMATRIXLOADIDENTITYEXTPROC) (GLenum బహుళకం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMATRIXLOADTRANSPOSEFEXTPROC) (GLenum బహుళకం, స్థిరరాశి GLfloat *m);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMATRIXLOADTRANSPOSEDEXTPROC) (GLenum బహుళకం, స్థిరరాశి GLdouble *m);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMATRIXLOADFEXTPROC) (GLenum బహుళకం, స్థిరరాశి GLfloat *m);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMATRIXLOADDEXTPROC) (GLenum బహుళకం, స్థిరరాశి GLdouble *m);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMATRIXMULTTRANSPOSEFEXTPROC) (GLenum బహుళకం, స్థిరరాశి GLfloat *m);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMATRIXMULTTRANSPOSEDEXTPROC) (GLenum బహుళకం, స్థిరరాశి GLdouble *m);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMATRIXMULTFEXTPROC) (GLenum బహుళకం, స్థిరరాశి GLfloat *m);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMATRIXMULTDEXTPROC) (GLenum బహుళకం, స్థిరరాశి GLdouble *m);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMATRIXORTHOEXTPROC) (GLenum బహుళకం, GLdouble ఎడమ, GLdouble కుడి, GLdouble bottom, GLdouble శిఖరం, GLdouble zNear, GLdouble zFar);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMATRIXPOPEXTPROC) (GLenum బహుళకం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMATRIXPUSHEXTPROC) (GLenum బహుళకం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMATRIXROTATEFEXTPROC) (GLenum బహుళకం, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMATRIXROTATEDEXTPROC) (GLenum బహుళకం, GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMATRIXSCALEFEXTPROC) (GLenum బహుళకం, GLfloat x, GLfloat y, GLfloat z);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMATRIXSCALEDEXTPROC) (GLenum బహుళకం, GLdouble x, GLdouble y, GLdouble z);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMATRIXTRANSLATEFEXTPROC) (GLenum బహుళకం, GLfloat x, GLfloat y, GLfloat z);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMATRIXTRANSLATEDEXTPROC) (GLenum బహుళకం, GLdouble x, GLdouble y, GLdouble z);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL GLuint GL_APIENTRY glGenPathsNV (GLsizei range);
GL_APICALL శూన్య GL_APIENTRY glDeletePathsNV (GLuint మార్గం, GLsizei range);
GL_APICALL GLboolean GL_APIENTRY gl_Is_మార్గం_NV (GLuint మార్గం);
GL_APICALL శూన్య GL_APIENTRY gl_మార్గం_Commands_NV (GLuint మార్గం, GLsizei అంకె_Commands, స్థిరరాశి GLubyte *commands, GLsizei అంకె_Coords, GLenum coordType, స్థిరరాశి శూన్య *coords);
GL_APICALL శూన్య GL_APIENTRY gl_మార్గం_Coords_NV (GLuint మార్గం, GLsizei అంకె_Coords, GLenum coordType, స్థిరరాశి శూన్య *coords);
GL_APICALL శూన్య GL_APIENTRY gl_మార్గం_Sub_Commands_NV (GLuint మార్గం, GLsizei command_ప్రారంభం, GLsizei commands_గమ్యం_Delete, GLsizei అంకె_Commands, స్థిరరాశి GLubyte *commands, GLsizei అంకె_Coords, GLenum coordType, స్థిరరాశి శూన్య *coords);
GL_APICALL శూన్య GL_APIENTRY gl_మార్గం_Sub_Coords_NV (GLuint మార్గం, GLsizei coord_ప్రారంభం, GLsizei అంకె_Coords, GLenum coordType, స్థిరరాశి శూన్య *coords);
GL_APICALL శూన్య GL_APIENTRY gl_మార్గం_String_NV (GLuint మార్గం, GLenum format, GLsizei నిడివి, స్థిరరాశి శూన్య *మార్గం_String);
GL_APICALL శూన్య GL_APIENTRY gl_మార్గం_Glyphs_NV (GLuint మొదటి_మార్గం_Name, GLenum font_లక్ష్యం, స్థిరరాశి శూన్య *fontName, GLbitfield fontStyle, GLsizei అంకె_Glyphs, GLenum type, స్థిరరాశి శూన్య *charcodes, GLenum handleMissingGlyphs, GLuint మార్గం_Parameter_Template, GLfloat emScale);
GL_APICALL శూన్య GL_APIENTRY gl_మార్గం_Glyph_Range_NV (GLuint మొదటి_మార్గం_Name, GLenum font_లక్ష్యం, స్థిరరాశి శూన్య *fontName, GLbitfield fontStyle, GLuint మొదటి_Glyph, GLsizei అంకె_Glyphs, GLenum handleMissingGlyphs, GLuint మార్గం_Parameter_Template, GLfloat emScale);
GL_APICALL శూన్య GL_APIENTRY gl_బరువు_Paths_NV (GLuint ఫలితం_మార్గం, GLsizei అంకె_Paths, స్థిరరాశి GLuint *paths, స్థిరరాశి GLfloat *weights);
GL_APICALL శూన్య GL_APIENTRY gl_Copy_మార్గం_NV (GLuint ఫలితం_మార్గం, GLuint src_మార్గం);
GL_APICALL శూన్య GL_APIENTRY glInterpolatePathsNV (GLuint ఫలితం_మార్గం, GLuint మార్గం_A, GLuint మార్గం_B, GLfloat బరువు);
GL_APICALL శూన్య GL_APIENTRY gl_Transform_మార్గం_NV (GLuint ఫలితం_మార్గం, GLuint src_మార్గం, GLenum transformType, స్థిరరాశి GLfloat *transform_విలువలు);
GL_APICALL శూన్య GL_APIENTRY gl_మార్గం_Parameteriv_NV (GLuint మార్గం, GLenum pname, స్థిరరాశి GLint *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_మార్గం_Parameteri_NV (GLuint మార్గం, GLenum pname, GLint విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_మార్గం_Parameterfv_NV (GLuint మార్గం, GLenum pname, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_మార్గం_Parameterf_NV (GLuint మార్గం, GLenum pname, GLfloat విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_మార్గం_Dash_Array_NV (GLuint మార్గం, GLsizei dash_లెక్క, స్థిరరాశి GLfloat *dashArray);
GL_APICALL శూన్య GL_APIENTRY gl_మార్గం_Stencil_Func_NV (GLenum func, GLint ref, GLuint ముసుగు);
GL_APICALL శూన్య GL_APIENTRY gl_మార్గం_Stencil_లోతు_స్థానభ్రంశం_NV (GLfloat గుణకం, GLfloat units);
GL_APICALL శూన్య GL_APIENTRY gl_Stencil_Fill_మార్గం_NV (GLuint మార్గం, GLenum fill_బహుళకం, GLuint ముసుగు);
GL_APICALL శూన్య GL_APIENTRY gl_Stencil_Stroke_మార్గం_NV (GLuint మార్గం, GLint reference, GLuint ముసుగు);
GL_APICALL శూన్య GL_APIENTRY gl_Stencil_Fill_మార్గం_Instanced_NV (GLsizei అంకె_Paths, GLenum మార్గం_Name_Type, స్థిరరాశి శూన్య *paths, GLuint మార్గం_పునాది, GLenum fill_బహుళకం, GLuint ముసుగు, GLenum transformType, స్థిరరాశి GLfloat *transform_విలువలు);
GL_APICALL శూన్య GL_APIENTRY gl_Stencil_Stroke_మార్గం_Instanced_NV (GLsizei అంకె_Paths, GLenum మార్గం_Name_Type, స్థిరరాశి శూన్య *paths, GLuint మార్గం_పునాది, GLint reference, GLuint ముసుగు, GLenum transformType, స్థిరరాశి GLfloat *transform_విలువలు);
GL_APICALL శూన్య GL_APIENTRY gl_మార్గం_Cover_లోతు_Func_NV (GLenum func);
GL_APICALL శూన్య GL_APIENTRY gl_Cover_Fill_మార్గం_NV (GLuint మార్గం, GLenum cover_బహుళకం);
GL_APICALL శూన్య GL_APIENTRY gl_Cover_Stroke_మార్గం_NV (GLuint మార్గం, GLenum cover_బహుళకం);
GL_APICALL శూన్య GL_APIENTRY gl_Cover_Fill_మార్గం_Instanced_NV (GLsizei అంకె_Paths, GLenum మార్గం_Name_Type, స్థిరరాశి శూన్య *paths, GLuint మార్గం_పునాది, GLenum cover_బహుళకం, GLenum transformType, స్థిరరాశి GLfloat *transform_విలువలు);
GL_APICALL శూన్య GL_APIENTRY gl_Cover_Stroke_మార్గం_Instanced_NV (GLsizei అంకె_Paths, GLenum మార్గం_Name_Type, స్థిరరాశి శూన్య *paths, GLuint మార్గం_పునాది, GLenum cover_బహుళకం, GLenum transformType, స్థిరరాశి GLfloat *transform_విలువలు);
GL_APICALL శూన్య GL_APIENTRY gl_Get_మార్గం_Parameteriv_NV (GLuint మార్గం, GLenum pname, GLint *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_Get_మార్గం_Parameterfv_NV (GLuint మార్గం, GLenum pname, GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_Get_మార్గం_Commands_NV (GLuint మార్గం, GLubyte *commands);
GL_APICALL శూన్య GL_APIENTRY gl_Get_మార్గం_Coords_NV (GLuint మార్గం, GLfloat *coords);
GL_APICALL శూన్య GL_APIENTRY gl_Get_మార్గం_Dash_Array_NV (GLuint మార్గం, GLfloat *dashArray);
GL_APICALL శూన్య GL_APIENTRY gl_Get_మార్గం_Metrics_NV (GLbitfield metric_Query_ముసుగు, GLsizei అంకె_Paths, GLenum మార్గం_Name_Type, స్థిరరాశి శూన్య *paths, GLuint మార్గం_పునాది, GLsizei stride, GLfloat *metrics);
GL_APICALL శూన్య GL_APIENTRY gl_Get_మార్గం_Metric_Range_NV (GLbitfield metric_Query_ముసుగు, GLuint మొదటి_మార్గం_Name, GLsizei అంకె_Paths, GLsizei stride, GLfloat *metrics);
GL_APICALL శూన్య GL_APIENTRY gl_Get_మార్గం_Spacing_NV (GLenum మార్గం_List_బహుళకం, GLsizei అంకె_Paths, GLenum మార్గం_Name_Type, స్థిరరాశి శూన్య *paths, GLuint మార్గం_పునాది, GLfloat advanceScale, GLfloat kerningScale, GLenum transformType, GLfloat *returnedSpacing);
GL_APICALL GLboolean GL_APIENTRY gl_Is_బిందువు_లోపల_Fill_మార్గం_NV (GLuint మార్గం, GLuint ముసుగు, GLfloat x, GLfloat y);
GL_APICALL GLboolean GL_APIENTRY gl_Is_బిందువు_లోపల_Stroke_మార్గం_NV (GLuint మార్గం, GLfloat x, GLfloat y);
GL_APICALL GLfloat GL_APIENTRY gl_Get_మార్గం_నిడివి_NV (GLuint మార్గం, GLsizei ప్రారంభం_Segment, GLsizei అంకె_Segments);
GL_APICALL GLboolean GL_APIENTRY gl_బిందువు_Along_మార్గం_NV (GLuint మార్గం, GLsizei ప్రారంభం_Segment, GLsizei అంకె_Segments, GLfloat దూరం, GLfloat *x, GLfloat *y, GLfloat *tangentX, GLfloat *tangentY);
GL_APICALL శూన్య GL_APIENTRY gl_మాతృక_Load3x2f_NV (GLenum మాతృక_బహుళకం, స్థిరరాశి GLfloat *m);
GL_APICALL శూన్య GL_APIENTRY gl_మాతృక_Load3x3f_NV (GLenum మాతృక_బహుళకం, స్థిరరాశి GLfloat *m);
GL_APICALL శూన్య GL_APIENTRY gl_మాతృక_ఎక్కించు_Transpose3x3f_NV (GLenum మాతృక_బహుళకం, స్థిరరాశి GLfloat *m);
GL_APICALL శూన్య GL_APIENTRY gl_మాతృక_Mult3x2f_NV (GLenum మాతృక_బహుళకం, స్థిరరాశి GLfloat *m);
GL_APICALL శూన్య GL_APIENTRY gl_మాతృక_Mult3x3f_NV (GLenum మాతృక_బహుళకం, స్థిరరాశి GLfloat *m);
GL_APICALL శూన్య GL_APIENTRY gl_మాతృక_Mult_Transpose3x3f_NV (GLenum మాతృక_బహుళకం, స్థిరరాశి GLfloat *m);
GL_APICALL శూన్య GL_APIENTRY gl_Stencil_Then_Cover_Fill_మార్గం_NV (GLuint మార్గం, GLenum fill_బహుళకం, GLuint ముసుగు, GLenum cover_బహుళకం);
GL_APICALL శూన్య GL_APIENTRY gl_Stencil_Then_Cover_Stroke_మార్గం_NV (GLuint మార్గం, GLint reference, GLuint ముసుగు, GLenum cover_బహుళకం);
GL_APICALL శూన్య GL_APIENTRY gl_Stencil_Then_Cover_Fill_మార్గం_Instanced_NV (GLsizei అంకె_Paths, GLenum మార్గం_Name_Type, స్థిరరాశి శూన్య *paths, GLuint మార్గం_పునాది, GLenum fill_బహుళకం, GLuint ముసుగు, GLenum cover_బహుళకం, GLenum transformType, స్థిరరాశి GLfloat *transform_విలువలు);
GL_APICALL శూన్య GL_APIENTRY gl_Stencil_Then_Cover_Stroke_మార్గం_Instanced_NV (GLsizei అంకె_Paths, GLenum మార్గం_Name_Type, స్థిరరాశి శూన్య *paths, GLuint మార్గం_పునాది, GLint reference, GLuint ముసుగు, GLenum cover_బహుళకం, GLenum transformType, స్థిరరాశి GLfloat *transform_విలువలు);
GL_APICALL GLenum GL_APIENTRY gl_మార్గం_Glyph_సూచీ_Range_NV (GLenum font_లక్ష్యం, స్థిరరాశి శూన్య *fontName, GLbitfield fontStyle, GLuint మార్గం_Parameter_Template, GLfloat emScale, GLuint *పునాది_And_లెక్క);
GL_APICALL GLenum GL_APIENTRY gl_మార్గం_Glyph_సూచీ_Array_NV (GLuint మొదటి_మార్గం_Name, GLenum font_లక్ష్యం, స్థిరరాశి శూన్య *fontName, GLbitfield fontStyle, GLuint మొదటి_Glyph_సూచీ, GLsizei అంకె_Glyphs, GLuint మార్గం_Parameter_Template, GLfloat emScale);
GL_APICALL GLenum GL_APIENTRY gl_మార్గం_జ్ఞాపకం_Glyph_సూచీ_Array_NV (GLuint మొదటి_మార్గం_Name, GLenum font_లక్ష్యం, GLsizeiptr font_కొలత, స్థిరరాశి శూన్య *font_దత్తాంశం, GLsizei face_సూచీ, GLuint మొదటి_Glyph_సూచీ, GLsizei అంకె_Glyphs, GLuint మార్గం_Parameter_Template, GLfloat emScale);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_మార్గం_Fragment_ఆదానం_Gen_NV (GLuint కార్యక్రమం, GLint location, GLenum gen_బహుళకం, GLint components, స్థిరరాశి GLfloat *coeffs);
GL_APICALL శూన్య GL_APIENTRY gl_Get_కార్యక్రమం_Resourcefv_NV (GLuint కార్యక్రమం, GLenum కార్యక్రమం_Interface, GLuint సూచీ, GLsizei prop_లెక్క, స్థిరరాశి GLenum *props, GLsizei లెక్క, GLsizei *నిడివి, GLfloat *params);
GL_APICALL శూన్య GL_APIENTRY gl_మాతృక_Frustum_EXT (GLenum బహుళకం, GLdouble ఎడమ, GLdouble కుడి, GLdouble bottom, GLdouble శిఖరం, GLdouble zNear, GLdouble zFar);
GL_APICALL శూన్య GL_APIENTRY gl_మాతృక_ఎక్కించు_తటస్థం_EXT (GLenum బహుళకం);
GL_APICALL శూన్య GL_APIENTRY gl_మాతృక_ఎక్కించు_Transposef_EXT (GLenum బహుళకం, స్థిరరాశి GLfloat *m);
GL_APICALL శూన్య GL_APIENTRY gl_మాతృక_ఎక్కించు_Transposed_EXT (GLenum బహుళకం, స్థిరరాశి GLdouble *m);
GL_APICALL శూన్య GL_APIENTRY gl_మాతృక_Loadf_EXT (GLenum బహుళకం, స్థిరరాశి GLfloat *m);
GL_APICALL శూన్య GL_APIENTRY gl_మాతృక_Loadd_EXT (GLenum బహుళకం, స్థిరరాశి GLdouble *m);
GL_APICALL శూన్య GL_APIENTRY gl_మాతృక_Mult_Transposef_EXT (GLenum బహుళకం, స్థిరరాశి GLfloat *m);
GL_APICALL శూన్య GL_APIENTRY gl_మాతృక_Mult_Transposed_EXT (GLenum బహుళకం, స్థిరరాశి GLdouble *m);
GL_APICALL శూన్య GL_APIENTRY gl_మాతృక_Multf_EXT (GLenum బహుళకం, స్థిరరాశి GLfloat *m);
GL_APICALL శూన్య GL_APIENTRY gl_మాతృక_Multd_EXT (GLenum బహుళకం, స్థిరరాశి GLdouble *m);
GL_APICALL శూన్య GL_APIENTRY gl_మాతృక_Ortho_EXT (GLenum బహుళకం, GLdouble ఎడమ, GLdouble కుడి, GLdouble bottom, GLdouble శిఖరం, GLdouble zNear, GLdouble zFar);
GL_APICALL శూన్య GL_APIENTRY gl_మాతృక_తీయి_EXT (GLenum బహుళకం);
GL_APICALL శూన్య GL_APIENTRY gl_మాతృక_నెట్టు_EXT (GLenum బహుళకం);
GL_APICALL శూన్య GL_APIENTRY gl_మాతృక_Rotatef_EXT (GLenum బహుళకం, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL శూన్య GL_APIENTRY gl_మాతృక_Rotated_EXT (GLenum బహుళకం, GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
GL_APICALL శూన్య GL_APIENTRY gl_మాతృక_Scalef_EXT (GLenum బహుళకం, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL శూన్య GL_APIENTRY gl_మాతృక_Scaled_EXT (GLenum బహుళకం, GLdouble x, GLdouble y, GLdouble z);
GL_APICALL శూన్య GL_APIENTRY gl_మాతృక_Translatef_EXT (GLenum బహుళకం, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL శూన్య GL_APIENTRY gl_మాతృక_Translated_EXT (GLenum బహుళకం, GLdouble x, GLdouble y, GLdouble z);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_NV_path_rendering */

#నిర్వచితం_కాకపోతే GL_NV_మార్గం_rendering_shared_అంచు
#నిర్వచించు GL_NV_మార్గం_rendering_shared_అంచు 1
#నిర్వచించు GL_SHARED_అంచు_NV                 0xC0
#అయితే_ముగింపు /* GL_NV_path_rendering_shared_edge */

#నిర్వచితం_కాకపోతే GL_NV_pixel_బఫరు_object
#నిర్వచించు GL_NV_pixel_బఫరు_object 1
#నిర్వచించు GL_PIXEL_PACK_బఫరు_NV           0x88EB
#నిర్వచించు GL_PIXEL_UNPACK_బఫరు_NV         0x88EC
#నిర్వచించు GL_PIXEL_PACK_బఫరు_BINDING_NV   0x88ED
#నిర్వచించు GL_PIXEL_UNPACK_బఫరు_BINDING_NV 0x88EF
#అయితే_ముగింపు /* GL_NV_pixel_buffer_object */

#నిర్వచితం_కాకపోతే GL_NV_polygon_బహుళకం
#నిర్వచించు GL_NV_polygon_బహుళకం 1
#నిర్వచించు GL_POLYGON_బహుళకం_NV                0x0B40
#నిర్వచించు GL_POLYGON_స్థానభ్రంశం_బిందువు_NV        0x2A01
#నిర్వచించు GL_POLYGON_స్థానభ్రంశం_పంక్తి_NV         0x2A02
#నిర్వచించు GL_బిందువు_NV                       0x1B00
#నిర్వచించు GL_పంక్తి_NV                        0x1B01
#నిర్వచించు GL_FILL_NV                        0x1B02
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPOLYGONMODENVPROC) (GLenum face, GLenum బహుళకం);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_Polygon_బహుళకం_NV (GLenum face, GLenum బహుళకం);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_NV_polygon_mode */

#నిర్వచితం_కాకపోతే GL_NV_primitive_shading_రేటు
#నిర్వచించు GL_NV_primitive_shading_రేటు 1
#నిర్వచించు GL_SHADING_రేటు_IMAGE_చొప్పున_PRIMITIVE_NV 0x95B1
#నిర్వచించు GL_SHADING_రేటు_IMAGE_PALETTE_లెక్క_NV 0x95B2
#అయితే_ముగింపు /* GL_NV_primitive_shading_rate */

#నిర్వచితం_కాకపోతే GL_NV_read_బఫరు
#నిర్వచించు GL_NV_read_బఫరు 1
#నిర్వచించు GL_READ_బఫరు_NV                 0x0C02
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLREADBUFFERNVPROC) (GLenum బహుళకం);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_Read_బఫరు_NV (GLenum బహుళకం);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_NV_read_buffer */

#నిర్వచితం_కాకపోతే GL_NV_read_బఫరు_front
#నిర్వచించు GL_NV_read_బఫరు_front 1
#అయితే_ముగింపు /* GL_NV_read_buffer_front */

#నిర్వచితం_కాకపోతే GL_NV_read_లోతు
#నిర్వచించు GL_NV_read_లోతు 1
#అయితే_ముగింపు /* GL_NV_read_depth */

#నిర్వచితం_కాకపోతే GL_NV_read_లోతు_stencil
#నిర్వచించు GL_NV_read_లోతు_stencil 1
#అయితే_ముగింపు /* GL_NV_read_depth_stencil */

#నిర్వచితం_కాకపోతే GL_NV_read_stencil
#నిర్వచించు GL_NV_read_stencil 1
#అయితే_ముగింపు /* GL_NV_read_stencil */

#నిర్వచితం_కాకపోతే GL_NV_representative_fragment_test
#నిర్వచించు GL_NV_representative_fragment_test 1
#నిర్వచించు GL_REPRESENTATIVE_FRAGMENT_TEST_NV 0x937F
#అయితే_ముగింపు /* GL_NV_representative_fragment_test */

#నిర్వచితం_కాకపోతే GL_NV_sRGB_formats
#నిర్వచించు GL_NV_sRGB_formats 1
#నిర్వచించు GL_SLUMINANCE_NV                  0x8C46
#నిర్వచించు GL_SLUMINANCE_ALPHA_NV            0x8C44
#నిర్వచించు GL_SRGB8_NV                       0x8C41
#నిర్వచించు GL_SLUMINANCE8_NV                 0x8C47
#నిర్వచించు GL_SLUMINANCE8_ALPHA8_NV          0x8C45
#నిర్వచించు GL_COMPRESSED_SRGB_S3TC_DXT1_NV   0x8C4C
#నిర్వచించు GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_NV 0x8C4D
#నిర్వచించు GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_NV 0x8C4E
#నిర్వచించు GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_NV 0x8C4F
#నిర్వచించు GL_ETC1_SRGB8_NV                  0x88EE
#అయితే_ముగింపు /* GL_NV_sRGB_formats */

#నిర్వచితం_కాకపోతే GL_NV_sample_locations
#నిర్వచించు GL_NV_sample_locations 1
#నిర్వచించు GL_SAMPLE_LOCATION_SUBPIXEL_బిట్లు_NV 0x933D
#నిర్వచించు GL_SAMPLE_LOCATION_PIXEL_GRID_వెడల్పు_NV 0x933E
#నిర్వచించు GL_SAMPLE_LOCATION_PIXEL_GRID_ఎత్తు_NV 0x933F
#నిర్వచించు GL_PROGRAMMABLE_SAMPLE_LOCATION_పట్టిక_కొలత_NV 0x9340
#నిర్వచించు GL_SAMPLE_LOCATION_NV             0x8E50
#నిర్వచించు GL_PROGRAMMABLE_SAMPLE_LOCATION_NV 0x9341
#నిర్వచించు GL_FRAMEBUFFER_PROGRAMMABLE_SAMPLE_LOCATIONS_NV 0x9342
#నిర్వచించు GL_FRAMEBUFFER_SAMPLE_LOCATION_PIXEL_GRID_NV 0x9343
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFRAMEBUFFERSAMPLELOCATIONSFVNVPROC) (GLenum లక్ష్యం, GLuint ప్రారంభం, GLsizei లెక్క, స్థిరరాశి GLfloat *v);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVNVPROC) (GLuint framebuffer, GLuint ప్రారంభం, GLsizei లెక్క, స్థిరరాశి GLfloat *v);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLRESOLVEDEPTHVALUESNVPROC) (శూన్య);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glFramebufferSampleLocationsfvNV (GLenum లక్ష్యం, GLuint ప్రారంభం, GLsizei లెక్క, స్థిరరాశి GLfloat *v);
GL_APICALL శూన్య GL_APIENTRY glNamedFramebufferSampleLocationsfvNV (GLuint framebuffer, GLuint ప్రారంభం, GLsizei లెక్క, స్థిరరాశి GLfloat *v);
GL_APICALL శూన్య GL_APIENTRY gl_Resolve_లోతు_విలువలు_NV (శూన్య);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_NV_sample_locations */

#నిర్వచితం_కాకపోతే GL_NV_sample_ముసుగు_override_coverage
#నిర్వచించు GL_NV_sample_ముసుగు_override_coverage 1
#అయితే_ముగింపు /* GL_NV_sample_mask_override_coverage */

#నిర్వచితం_కాకపోతే GL_NV_scissor_exclusive
#నిర్వచించు GL_NV_scissor_exclusive 1
#నిర్వచించు GL_SCISSOR_TEST_EXCLUSIVE_NV      0x9555
#నిర్వచించు GL_SCISSOR_BOX_EXCLUSIVE_NV       0x9556
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSCISSOREXCLUSIVENVPROC) (GLint x, GLint y, GLsizei వెడల్పు, GLsizei ఎత్తు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSCISSOREXCLUSIVEARRAYVNVPROC) (GLuint మొదటి, GLsizei లెక్క, స్థిరరాశి GLint *v);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glScissorExclusiveNV (GLint x, GLint y, GLsizei వెడల్పు, GLsizei ఎత్తు);
GL_APICALL శూన్య GL_APIENTRY glScissorExclusiveArrayvNV (GLuint మొదటి, GLsizei లెక్క, స్థిరరాశి GLint *v);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_NV_scissor_exclusive */

#నిర్వచితం_కాకపోతే GL_NV_shader_atomic_fp16_సదిశ
#నిర్వచించు GL_NV_shader_atomic_fp16_సదిశ 1
#అయితే_ముగింపు /* GL_NV_shader_atomic_fp16_vector */

#నిర్వచితం_కాకపోతే GL_NV_shader_noperspective_interpolation
#నిర్వచించు GL_NV_shader_noperspective_interpolation 1
#అయితే_ముగింపు /* GL_NV_shader_noperspective_interpolation */

#నిర్వచితం_కాకపోతే GL_NV_shader_subgroup_partitioned
#నిర్వచించు GL_NV_shader_subgroup_partitioned 1
#నిర్వచించు GL_SUBGROUP_FEATURE_PARTITIONED_బిట్టు_NV 0x00000100
#అయితే_ముగింపు /* GL_NV_shader_subgroup_partitioned */

#నిర్వచితం_కాకపోతే GL_NV_shader_texture_footprint
#నిర్వచించు GL_NV_shader_texture_footprint 1
#అయితే_ముగింపు /* GL_NV_shader_texture_footprint */

#నిర్వచితం_కాకపోతే GL_NV_shading_రేటు_image
#నిర్వచించు GL_NV_shading_రేటు_image 1
#నిర్వచించు GL_SHADING_రేటు_IMAGE_NV          0x9563
#నిర్వచించు GL_SHADING_రేటు_NO_INVOCATIONS_NV 0x9564
#నిర్వచించు GL_SHADING_రేటు_1_INVOCATION_చొప్పున_PIXEL_NV 0x9565
#నిర్వచించు GL_SHADING_రేటు_1_INVOCATION_చొప్పున_1_X2_PIXELS_NV 0x9566
#నిర్వచించు GL_SHADING_రేటు_1_INVOCATION_చొప్పున_2_X1_PIXELS_NV 0x9567
#నిర్వచించు GL_SHADING_రేటు_1_INVOCATION_చొప్పున_2_X2_PIXELS_NV 0x9568
#నిర్వచించు GL_SHADING_రేటు_1_INVOCATION_చొప్పున_2_X4_PIXELS_NV 0x9569
#నిర్వచించు GL_SHADING_రేటు_1_INVOCATION_చొప్పున_4_X2_PIXELS_NV 0x956A
#నిర్వచించు GL_SHADING_రేటు_1_INVOCATION_చొప్పున_4_X4_PIXELS_NV 0x956B
#నిర్వచించు GL_SHADING_రేటు_2_INVOCATIONS_చొప్పున_PIXEL_NV 0x956C
#నిర్వచించు GL_SHADING_రేటు_4_INVOCATIONS_చొప్పున_PIXEL_NV 0x956D
#నిర్వచించు GL_SHADING_రేటు_8_INVOCATIONS_చొప్పున_PIXEL_NV 0x956E
#నిర్వచించు GL_SHADING_రేటు_16_INVOCATIONS_చొప్పున_PIXEL_NV 0x956F
#నిర్వచించు GL_SHADING_రేటు_IMAGE_BINDING_NV  0x955B
#నిర్వచించు GL_SHADING_రేటు_IMAGE_TEXEL_వెడల్పు_NV 0x955C
#నిర్వచించు GL_SHADING_రేటు_IMAGE_TEXEL_ఎత్తు_NV 0x955D
#నిర్వచించు GL_SHADING_రేటు_IMAGE_PALETTE_కొలత_NV 0x955E
#నిర్వచించు GL_MAX_COARSE_FRAGMENT_SAMPLES_NV 0x955F
#నిర్వచించు GL_SHADING_రేటు_SAMPLE_క్రమం_DEFAULT_NV 0x95AE
#నిర్వచించు GL_SHADING_రేటు_SAMPLE_క్రమం_PIXEL_MAJOR_NV 0x95AF
#నిర్వచించు GL_SHADING_రేటు_SAMPLE_క్రమం_SAMPLE_MAJOR_NV 0x95B0
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBINDSHADINGRATEIMAGENVPROC) (GLuint texture);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETSHADINGRATEIMAGEPALETTENVPROC) (GLuint viewport, GLuint నమోదు_2, GLenum *రేటు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETSHADINGRATESAMPLELOCATIONIVNVPROC) (GLenum రేటు, GLuint samples, GLuint సూచీ, GLint *location);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSHADINGRATEIMAGEBARRIERNVPROC) (GLboolean synchronize);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSHADINGRATEIMAGEPALETTENVPROC) (GLuint viewport, GLuint మొదటి, GLsizei లెక్క, స్థిరరాశి GLenum *rates);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSHADINGRATESAMPLEORDERNVPROC) (GLenum క్రమం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSHADINGRATESAMPLEORDERCUSTOMNVPROC) (GLenum రేటు, GLuint samples, స్థిరరాశి GLint *locations);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_Bind_Shading_రేటు_Image_NV (GLuint texture);
GL_APICALL శూన్య GL_APIENTRY gl_Get_Shading_రేటు_Image_Palette_NV (GLuint viewport, GLuint నమోదు_2, GLenum *రేటు);
GL_APICALL శూన్య GL_APIENTRY gl_Get_Shading_రేటు_Sample_Locationiv_NV (GLenum రేటు, GLuint samples, GLuint సూచీ, GLint *location);
GL_APICALL శూన్య GL_APIENTRY gl_Shading_రేటు_Image_Barrier_NV (GLboolean synchronize);
GL_APICALL శూన్య GL_APIENTRY gl_Shading_రేటు_Image_Palette_NV (GLuint viewport, GLuint మొదటి, GLsizei లెక్క, స్థిరరాశి GLenum *rates);
GL_APICALL శూన్య GL_APIENTRY gl_Shading_రేటు_Sample_క్రమం_NV (GLenum క్రమం);
GL_APICALL శూన్య GL_APIENTRY gl_Shading_రేటు_Sample_క్రమం_Custom_NV (GLenum రేటు, GLuint samples, స్థిరరాశి GLint *locations);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_NV_shading_rate_image */

#నిర్వచితం_కాకపోతే GL_NV_shadow_samplers_array
#నిర్వచించు GL_NV_shadow_samplers_array 1
#నిర్వచించు GL_SAMPLER_2D_ARRAY_SHADOW_NV     0x8DC4
#అయితే_ముగింపు /* GL_NV_shadow_samplers_array */

#నిర్వచితం_కాకపోతే GL_NV_shadow_samplers_cube
#నిర్వచించు GL_NV_shadow_samplers_cube 1
#నిర్వచించు GL_SAMPLER_CUBE_SHADOW_NV         0x8DC5
#అయితే_ముగింపు /* GL_NV_shadow_samplers_cube */

#నిర్వచితం_కాకపోతే GL_NV_stereo_view_rendering
#నిర్వచించు GL_NV_stereo_view_rendering 1
#అయితే_ముగింపు /* GL_NV_stereo_view_rendering */

#నిర్వచితం_కాకపోతే GL_NV_texture_barrier
#నిర్వచించు GL_NV_texture_barrier 1
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXTUREBARRIERNVPROC) (శూన్య);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glTextureBarrierNV (శూన్య);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_NV_texture_barrier */

#నిర్వచితం_కాకపోతే GL_NV_texture_border_clamp
#నిర్వచించు GL_NV_texture_border_clamp 1
#నిర్వచించు GL_TEXTURE_BORDER_COLOR_NV        0x1004
#నిర్వచించు GL_CLAMP_గమ్యం_BORDER_NV             0x812D
#అయితే_ముగింపు /* GL_NV_texture_border_clamp */

#నిర్వచితం_కాకపోతే GL_NV_texture_compression_s3tc_update
#నిర్వచించు GL_NV_texture_compression_s3tc_update 1
#అయితే_ముగింపు /* GL_NV_texture_compression_s3tc_update */

#నిర్వచితం_కాకపోతే GL_NV_texture_npot_2D_mipmap
#నిర్వచించు GL_NV_texture_npot_2D_mipmap 1
#అయితే_ముగింపు /* GL_NV_texture_npot_2D_mipmap */

#నిర్వచితం_కాకపోతే GL_NV_timeline_semaphore
#నిర్వచించు GL_NV_timeline_semaphore 1
#నిర్వచించు GL_TIMELINE_SEMAPHORE_విలువ_NV    0x9595
#నిర్వచించు GL_SEMAPHORE_TYPE_NV              0x95B3
#నిర్వచించు GL_SEMAPHORE_TYPE_ద్విమాన_NV       0x95B4
#నిర్వచించు GL_SEMAPHORE_TYPE_TIMELINE_NV     0x95B5
#నిర్వచించు GL_MAX_TIMELINE_SEMAPHORE_విలువ_DIFFERENCE_NV 0x95B6
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCREATESEMAPHORESNVPROC) (GLsizei n, GLuint *semaphores);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSEMAPHOREPARAMETERIVNVPROC) (GLuint semaphore, GLenum pname, స్థిరరాశి GLint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETSEMAPHOREPARAMETERIVNVPROC) (GLuint semaphore, GLenum pname, GLint *params);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glCreateSemaphoresNV (GLsizei n, GLuint *semaphores);
GL_APICALL శూన్య GL_APIENTRY glSemaphoreParameterivNV (GLuint semaphore, GLenum pname, స్థిరరాశి GLint *params);
GL_APICALL శూన్య GL_APIENTRY glGetSemaphoreParameterivNV (GLuint semaphore, GLenum pname, GLint *params);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_NV_timeline_semaphore */

#నిర్వచితం_కాకపోతే GL_NV_viewport_array
#నిర్వచించు GL_NV_viewport_array 1
#నిర్వచించు GL_MAX_VIEWPORTS_NV               0x825B
#నిర్వచించు GL_VIEWPORT_SUBPIXEL_బిట్లు_NV      0x825C
#నిర్వచించు GL_VIEWPORT_BOUNDS_RANGE_NV       0x825D
#నిర్వచించు GL_VIEWPORT_సూచీ_PROVOKING_శీర్షం_NV 0x825F
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLVIEWPORTARRAYVNVPROC) (GLuint మొదటి, GLsizei లెక్క, స్థిరరాశి GLfloat *v);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLVIEWPORTINDEXEDFNVPROC) (GLuint సూచీ, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLVIEWPORTINDEXEDFVNVPROC) (GLuint సూచీ, స్థిరరాశి GLfloat *v);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSCISSORARRAYVNVPROC) (GLuint మొదటి, GLsizei లెక్క, స్థిరరాశి GLint *v);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSCISSORINDEXEDNVPROC) (GLuint సూచీ, GLint ఎడమ, GLint bottom, GLsizei వెడల్పు, GLsizei ఎత్తు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSCISSORINDEXEDVNVPROC) (GLuint సూచీ, స్థిరరాశి GLint *v);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDEPTHRANGEARRAYFVNVPROC) (GLuint మొదటి, GLsizei లెక్క, స్థిరరాశి GLfloat *v);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDEPTHRANGEINDEXEDFNVPROC) (GLuint సూచీ, GLfloat n, GLfloat f);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETFLOATI_VNVPROC) (GLenum లక్ష్యం, GLuint సూచీ, GLfloat *దత్తాంశం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLENABLEINVPROC) (GLenum లక్ష్యం, GLuint సూచీ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDISABLEINVPROC) (GLenum లక్ష్యం, GLuint సూచీ);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLISENABLEDINVPROC) (GLenum లక్ష్యం, GLuint సూచీ);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glViewportArrayvNV (GLuint మొదటి, GLsizei లెక్క, స్థిరరాశి GLfloat *v);
GL_APICALL శూన్య GL_APIENTRY glViewportIndexedfNV (GLuint సూచీ, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
GL_APICALL శూన్య GL_APIENTRY glViewportIndexedfvNV (GLuint సూచీ, స్థిరరాశి GLfloat *v);
GL_APICALL శూన్య GL_APIENTRY glScissorArrayvNV (GLuint మొదటి, GLsizei లెక్క, స్థిరరాశి GLint *v);
GL_APICALL శూన్య GL_APIENTRY gl_Scissor_సూచీకృత_NV (GLuint సూచీ, GLint ఎడమ, GLint bottom, GLsizei వెడల్పు, GLsizei ఎత్తు);
GL_APICALL శూన్య GL_APIENTRY glScissorIndexedvNV (GLuint సూచీ, స్థిరరాశి GLint *v);
GL_APICALL శూన్య GL_APIENTRY gl_లోతు_Range_Arrayfv_NV (GLuint మొదటి, GLsizei లెక్క, స్థిరరాశి GLfloat *v);
GL_APICALL శూన్య GL_APIENTRY gl_లోతు_Range_Indexedf_NV (GLuint సూచీ, GLfloat n, GLfloat f);
GL_APICALL శూన్య GL_APIENTRY glGetFloati_vNV (GLenum లక్ష్యం, GLuint సూచీ, GLfloat *దత్తాంశం);
GL_APICALL శూన్య GL_APIENTRY glEnableiNV (GLenum లక్ష్యం, GLuint సూచీ);
GL_APICALL శూన్య GL_APIENTRY glDisableiNV (GLenum లక్ష్యం, GLuint సూచీ);
GL_APICALL GLboolean GL_APIENTRY glIsEnablediNV (GLenum లక్ష్యం, GLuint సూచీ);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_NV_viewport_array */

#నిర్వచితం_కాకపోతే GL_NV_viewport_array2
#నిర్వచించు GL_NV_viewport_array2 1
#అయితే_ముగింపు /* GL_NV_viewport_array2 */

#నిర్వచితం_కాకపోతే GL_NV_viewport_swizzle
#నిర్వచించు GL_NV_viewport_swizzle 1
#నిర్వచించు GL_VIEWPORT_SWIZZLE_ధనాత్మక_X_NV 0x9350
#నిర్వచించు GL_VIEWPORT_SWIZZLE_NEGATIVE_X_NV 0x9351
#నిర్వచించు GL_VIEWPORT_SWIZZLE_ధనాత్మక_Y_NV 0x9352
#నిర్వచించు GL_VIEWPORT_SWIZZLE_NEGATIVE_Y_NV 0x9353
#నిర్వచించు GL_VIEWPORT_SWIZZLE_ధనాత్మక_Z_NV 0x9354
#నిర్వచించు GL_VIEWPORT_SWIZZLE_NEGATIVE_Z_NV 0x9355
#నిర్వచించు GL_VIEWPORT_SWIZZLE_ధనాత్మక_W_NV 0x9356
#నిర్వచించు GL_VIEWPORT_SWIZZLE_NEGATIVE_W_NV 0x9357
#నిర్వచించు GL_VIEWPORT_SWIZZLE_X_NV          0x9358
#నిర్వచించు GL_VIEWPORT_SWIZZLE_Y_NV          0x9359
#నిర్వచించు GL_VIEWPORT_SWIZZLE_Z_NV          0x935A
#నిర్వచించు GL_VIEWPORT_SWIZZLE_W_NV          0x935B
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLVIEWPORTSWIZZLENVPROC) (GLuint సూచీ, GLenum swizzlex, GLenum swizzley, GLenum swizzlez, GLenum swizzlew);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glViewportSwizzleNV (GLuint సూచీ, GLenum swizzlex, GLenum swizzley, GLenum swizzlez, GLenum swizzlew);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_NV_viewport_swizzle */

#నిర్వచితం_కాకపోతే GL_OVR_multiview
#నిర్వచించు GL_OVR_multiview 1
#నిర్వచించు GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_అంకె_VIEWS_OVR 0x9630
#నిర్వచించు GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_పునాది_VIEW_సూచీ_OVR 0x9632
#నిర్వచించు GL_MAX_VIEWS_OVR                  0x9631
#నిర్వచించు GL_FRAMEBUFFER_INCOMPLETE_VIEW_TARGETS_OVR 0x9633
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREMULTIVIEWOVRPROC) (GLenum లక్ష్యం, GLenum attachment, GLuint texture, GLint level, GLint పునాది_View_సూచీ, GLsizei అంకె_Views_2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLNAMEDFRAMEBUFFERTEXTUREMULTIVIEWOVRPROC) (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint పునాది_View_సూచీ, GLsizei అంకె_Views_2);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glFramebufferTextureMultiviewOVR (GLenum లక్ష్యం, GLenum attachment, GLuint texture, GLint level, GLint పునాది_View_సూచీ, GLsizei అంకె_Views_2);
GL_APICALL శూన్య GL_APIENTRY glNamedFramebufferTextureMultiviewOVR (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint పునాది_View_సూచీ, GLsizei అంకె_Views_2);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_OVR_multiview */

#నిర్వచితం_కాకపోతే GL_OVR_multiview2
#నిర్వచించు GL_OVR_multiview2 1
#అయితే_ముగింపు /* GL_OVR_multiview2 */

#నిర్వచితం_కాకపోతే GL_OVR_multiview_multisampled_render_గమ్యం_texture
#నిర్వచించు GL_OVR_multiview_multisampled_render_గమ్యం_texture 1
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREMULTISAMPLEMULTIVIEWOVRPROC) (GLenum లక్ష్యం, GLenum attachment, GLuint texture, GLint level, GLsizei samples, GLint పునాది_View_సూచీ, GLsizei అంకె_Views_2);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glFramebufferTextureMultisampleMultiviewOVR (GLenum లక్ష్యం, GLenum attachment, GLuint texture, GLint level, GLsizei samples, GLint పునాది_View_సూచీ, GLsizei అంకె_Views_2);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_OVR_multiview_multisampled_render_to_texture */

#నిర్వచితం_కాకపోతే GL_QCOM_YUV_texture_gather
#నిర్వచించు GL_QCOM_YUV_texture_gather 1
#అయితే_ముగింపు /* GL_QCOM_YUV_texture_gather */

#నిర్వచితం_కాకపోతే GL_QCOM_alpha_test
#నిర్వచించు GL_QCOM_alpha_test 1
#నిర్వచించు GL_ALPHA_TEST_QCOM                0x0BC0
#నిర్వచించు GL_ALPHA_TEST_FUNC_QCOM           0x0BC1
#నిర్వచించు GL_ALPHA_TEST_REF_QCOM            0x0BC2
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLALPHAFUNCQCOMPROC) (GLenum func, GLclampf ref);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glAlphaFuncQCOM (GLenum func, GLclampf ref);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_QCOM_alpha_test */

#నిర్వచితం_కాకపోతే GL_QCOM_binning_control
#నిర్వచించు GL_QCOM_binning_control 1
#నిర్వచించు GL_BINNING_CONTROL_HINT_QCOM      0x8FB0
#నిర్వచించు GL_CPU_OPTIMIZED_QCOM             0x8FB1
#నిర్వచించు GL_GPU_OPTIMIZED_QCOM             0x8FB2
#నిర్వచించు GL_RENDER_ప్రత్యక్ష_గమ్యం_FRAMEBUFFER_QCOM 0x8FB3
#అయితే_ముగింపు /* GL_QCOM_binning_control */

#నిర్వచితం_కాకపోతే GL_QCOM_driver_control
#నిర్వచించు GL_QCOM_driver_control 1
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETDRIVERCONTROLSQCOMPROC) (GLint *అంకె, GLsizei కొలత, GLuint *driverControls);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETDRIVERCONTROLSTRINGQCOMPROC) (GLuint driverControl, GLsizei buf_కొలత, GLsizei *నిడివి, GLchar *driverControlString);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLENABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDISABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glGetDriverControlsQCOM (GLint *అంకె, GLsizei కొలత, GLuint *driverControls);
GL_APICALL శూన్య GL_APIENTRY glGetDriverControlStringQCOM (GLuint driverControl, GLsizei buf_కొలత, GLsizei *నిడివి, GLchar *driverControlString);
GL_APICALL శూన్య GL_APIENTRY glEnableDriverControlQCOM (GLuint driverControl);
GL_APICALL శూన్య GL_APIENTRY glDisableDriverControlQCOM (GLuint driverControl);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_QCOM_driver_control */

#నిర్వచితం_కాకపోతే GL_QCOM_extended_get
#నిర్వచించు GL_QCOM_extended_get 1
#నిర్వచించు GL_TEXTURE_వెడల్పు_QCOM             0x8BD2
#నిర్వచించు GL_TEXTURE_ఎత్తు_QCOM            0x8BD3
#నిర్వచించు GL_TEXTURE_లోతు_QCOM             0x8BD4
#నిర్వచించు GL_TEXTURE_అంతర్గత_FORMAT_QCOM   0x8BD5
#నిర్వచించు GL_TEXTURE_FORMAT_QCOM            0x8BD6
#నిర్వచించు GL_TEXTURE_TYPE_QCOM              0x8BD7
#నిర్వచించు GL_TEXTURE_IMAGE_VALID_QCOM       0x8BD8
#నిర్వచించు GL_TEXTURE_అంకె_స్థాయిలు_QCOM        0x8BD9
#నిర్వచించు GL_TEXTURE_లక్ష్యం_QCOM            0x8BDA
#నిర్వచించు GL_TEXTURE_OBJECT_VALID_QCOM      0x8BDB
#నిర్వచించు GL_STATE_RESTORE                  0x8BDC
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLEXTGETTEXTURESQCOMPROC) (GLuint *textures, GLint maxTextures, GLint *అంకె_Textures);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLEXTGETBUFFERSQCOMPROC) (GLuint *buffers, GLint maxBuffers, GLint *అంకె_Buffers);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLEXTGETRENDERBUFFERSQCOMPROC) (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *అంకె_Renderbuffers);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLEXTGETFRAMEBUFFERSQCOMPROC) (GLuint *framebuffers, GLint maxFramebuffers, GLint *అంకె_Framebuffers);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLEXTGETTEXLEVELPARAMETERIVQCOMPROC) (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLEXTTEXOBJECTSTATEOVERRIDEIQCOMPROC) (GLenum లక్ష్యం, GLenum pname, GLint param);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLEXTGETTEXSUBIMAGEQCOMPROC) (GLenum లక్ష్యం, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLenum format, GLenum type, శూన్య *texels);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLEXTGETBUFFERPOINTERVQCOMPROC) (GLenum లక్ష్యం, శూన్య **params);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glExtGetTexturesQCOM (GLuint *textures, GLint maxTextures, GLint *అంకె_Textures);
GL_APICALL శూన్య GL_APIENTRY glExtGetBuffersQCOM (GLuint *buffers, GLint maxBuffers, GLint *అంకె_Buffers);
GL_APICALL శూన్య GL_APIENTRY glExtGetRenderbuffersQCOM (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *అంకె_Renderbuffers);
GL_APICALL శూన్య GL_APIENTRY glExtGetFramebuffersQCOM (GLuint *framebuffers, GLint maxFramebuffers, GLint *అంకె_Framebuffers);
GL_APICALL శూన్య GL_APIENTRY glExtGetTexLevelParameterivQCOM (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
GL_APICALL శూన్య GL_APIENTRY glExtTexObjectStateOverrideiQCOM (GLenum లక్ష్యం, GLenum pname, GLint param);
GL_APICALL శూన్య GL_APIENTRY glExtGetTexSubImageQCOM (GLenum లక్ష్యం, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLenum format, GLenum type, శూన్య *texels);
GL_APICALL శూన్య GL_APIENTRY gl_Ext_Get_బఫరు_Pointerv_QCOM (GLenum లక్ష్యం, శూన్య **params);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_QCOM_extended_get */

#నిర్వచితం_కాకపోతే GL_QCOM_extended_get2
#నిర్వచించు GL_QCOM_extended_get2 1
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLEXTGETSHADERSQCOMPROC) (GLuint *shaders, GLint maxShaders, GLint *అంకె_Shaders);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLEXTGETPROGRAMSQCOMPROC) (GLuint *programs, GLint maxPrograms, GLint *అంకె_Programs);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLEXTISPROGRAMBINARYQCOMPROC) (GLuint కార్యక్రమం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLEXTGETPROGRAMBINARYSOURCEQCOMPROC) (GLuint కార్యక్రమం, GLenum shadertype, GLchar *ఆధారం, GLint *నిడివి);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glExtGetShadersQCOM (GLuint *shaders, GLint maxShaders, GLint *అంకె_Shaders);
GL_APICALL శూన్య GL_APIENTRY glExtGetProgramsQCOM (GLuint *programs, GLint maxPrograms, GLint *అంకె_Programs);
GL_APICALL GLboolean GL_APIENTRY gl_Ext_Is_కార్యక్రమం_ద్విమాన_QCOM (GLuint కార్యక్రమం);
GL_APICALL శూన్య GL_APIENTRY gl_Ext_Get_కార్యక్రమం_ద్విమాన_ఆధారం_QCOM (GLuint కార్యక్రమం, GLenum shadertype, GLchar *ఆధారం, GLint *నిడివి);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_QCOM_extended_get2 */

#నిర్వచితం_కాకపోతే GL_QCOM_చట్రం_extrapolation
#నిర్వచించు GL_QCOM_చట్రం_extrapolation 1
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLEXTRAPOLATETEX2DQCOMPROC) (GLuint src1, GLuint src2, GLuint output, GLfloat scale_గుణకం);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glExtrapolateTex2DQCOM (GLuint src1, GLuint src2, GLuint output, GLfloat scale_గుణకం);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_QCOM_frame_extrapolation */

#నిర్వచితం_కాకపోతే GL_QCOM_framebuffer_foveated
#నిర్వచించు GL_QCOM_framebuffer_foveated 1
#నిర్వచించు GL_FOVEATION_ENABLE_బిట్టు_QCOM      0x00000001
#నిర్వచించు GL_FOVEATION_SCALED_BIN_పద్ధతి_బిట్టు_QCOM 0x00000002
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFRAMEBUFFERFOVEATIONCONFIGQCOMPROC) (GLuint framebuffer, GLuint అంకె_Layers, GLuint focal_Points_చొప్పున_Layer, GLuint requestedFeatures, GLuint *providedFeatures);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFRAMEBUFFERFOVEATIONPARAMETERSQCOMPROC) (GLuint framebuffer, GLuint layer, GLuint focal_బిందువు, GLfloat focalX, GLfloat focalY, GLfloat gainX, GLfloat gainY, GLfloat foveaArea);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glFramebufferFoveationConfigQCOM (GLuint framebuffer, GLuint అంకె_Layers, GLuint focal_Points_చొప్పున_Layer, GLuint requestedFeatures, GLuint *providedFeatures);
GL_APICALL శూన్య GL_APIENTRY glFramebufferFoveationParametersQCOM (GLuint framebuffer, GLuint layer, GLuint focal_బిందువు, GLfloat focalX, GLfloat focalY, GLfloat gainX, GLfloat gainY, GLfloat foveaArea);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_QCOM_framebuffer_foveated */

#నిర్వచితం_కాకపోతే GL_QCOM_motion_estimation
#నిర్వచించు GL_QCOM_motion_estimation 1
#నిర్వచించు GL_MOTION_ESTIMATION_శోధన_ఖండం_X_QCOM 0x8C90
#నిర్వచించు GL_MOTION_ESTIMATION_శోధన_ఖండం_Y_QCOM 0x8C91
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXESTIMATEMOTIONQCOMPROC) (GLuint ref, GLuint లక్ష్యం, GLuint output);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXESTIMATEMOTIONREGIONSQCOMPROC) (GLuint ref, GLuint లక్ష్యం, GLuint output, GLuint ముసుగు);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glTexEstimateMotionQCOM (GLuint ref, GLuint లక్ష్యం, GLuint output);
GL_APICALL శూన్య GL_APIENTRY glTexEstimateMotionRegionsQCOM (GLuint ref, GLuint లక్ష్యం, GLuint output, GLuint ముసుగు);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_QCOM_motion_estimation */

#నిర్వచితం_కాకపోతే GL_QCOM_perfmon_global_బహుళకం
#నిర్వచించు GL_QCOM_perfmon_global_బహుళకం 1
#నిర్వచించు GL_PERFMON_GLOBAL_బహుళకం_QCOM       0x8FA0
#అయితే_ముగింపు /* GL_QCOM_perfmon_global_mode */

#నిర్వచితం_కాకపోతే GL_QCOM_render_sRGB_R8_RG8
#నిర్వచించు GL_QCOM_render_sRGB_R8_RG8 1
#అయితే_ముగింపు /* GL_QCOM_render_sRGB_R8_RG8 */

#నిర్వచితం_కాకపోతే GL_QCOM_render_shared_exponent
#నిర్వచించు GL_QCOM_render_shared_exponent 1
#అయితే_ముగింపు /* GL_QCOM_render_shared_exponent */

#నిర్వచితం_కాకపోతే GL_QCOM_shader_framebuffer_fetch_noncoherent
#నిర్వచించు GL_QCOM_shader_framebuffer_fetch_noncoherent 1
#నిర్వచించు GL_FRAMEBUFFER_FETCH_NONCOHERENT_QCOM 0x96A2
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFRAMEBUFFERFETCHBARRIERQCOMPROC) (శూన్య);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glFramebufferFetchBarrierQCOM (శూన్య);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_QCOM_shader_framebuffer_fetch_noncoherent */

#నిర్వచితం_కాకపోతే GL_QCOM_shader_framebuffer_fetch_రేటు
#నిర్వచించు GL_QCOM_shader_framebuffer_fetch_రేటు 1
#అయితే_ముగింపు /* GL_QCOM_shader_framebuffer_fetch_rate */

#నిర్వచితం_కాకపోతే GL_QCOM_shading_రేటు
#నిర్వచించు GL_QCOM_shading_రేటు 1
#నిర్వచించు GL_SHADING_రేటు_QCOM              0x96A4
#నిర్వచించు GL_SHADING_రేటు_PRESERVE_ASPECT_నిష్పత్తి_QCOM 0x96A5
#నిర్వచించు GL_SHADING_రేటు_1_X1_PIXELS_QCOM   0x96A6
#నిర్వచించు GL_SHADING_రేటు_1_X2_PIXELS_QCOM   0x96A7
#నిర్వచించు GL_SHADING_రేటు_2_X1_PIXELS_QCOM   0x96A8
#నిర్వచించు GL_SHADING_రేటు_2_X2_PIXELS_QCOM   0x96A9
#నిర్వచించు GL_SHADING_రేటు_4_X2_PIXELS_QCOM   0x96AC
#నిర్వచించు GL_SHADING_రేటు_4_X4_PIXELS_QCOM   0x96AE
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSHADINGRATEQCOMPROC) (GLenum రేటు);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_Shading_రేటు_QCOM (GLenum రేటు);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_QCOM_shading_rate */

#నిర్వచితం_కాకపోతే GL_QCOM_texture_foveated
#నిర్వచించు GL_QCOM_texture_foveated 1
#నిర్వచించు GL_TEXTURE_FOVEATED_FEATURE_బిట్లు_QCOM 0x8BFB
#నిర్వచించు GL_TEXTURE_FOVEATED_MIN_PIXEL_DENSITY_QCOM 0x8BFC
#నిర్వచించు GL_TEXTURE_FOVEATED_FEATURE_QUERY_QCOM 0x8BFD
#నిర్వచించు GL_TEXTURE_FOVEATED_అంకె_FOCAL_POINTS_QUERY_QCOM 0x8BFE
#నిర్వచించు GL_FRAMEBUFFER_INCOMPLETE_FOVEATION_QCOM 0x8BFF
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXTUREFOVEATIONPARAMETERSQCOMPROC) (GLuint texture, GLuint layer, GLuint focal_బిందువు, GLfloat focalX, GLfloat focalY, GLfloat gainX, GLfloat gainY, GLfloat foveaArea);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glTextureFoveationParametersQCOM (GLuint texture, GLuint layer, GLuint focal_బిందువు, GLfloat focalX, GLfloat focalY, GLfloat gainX, GLfloat gainY, GLfloat foveaArea);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_QCOM_texture_foveated */

#నిర్వచితం_కాకపోతే GL_QCOM_texture_foveated2
#నిర్వచించు GL_QCOM_texture_foveated2 1
#నిర్వచించు GL_TEXTURE_FOVEATED_CUTOFF_DENSITY_QCOM 0x96A0
#అయితే_ముగింపు /* GL_QCOM_texture_foveated2 */

#నిర్వచితం_కాకపోతే GL_QCOM_texture_foveated_subsampled_layout
#నిర్వచించు GL_QCOM_texture_foveated_subsampled_layout 1
#నిర్వచించు GL_FOVEATION_SUBSAMPLED_LAYOUT_పద్ధతి_బిట్టు_QCOM 0x00000004
#నిర్వచించు GL_MAX_SHADER_SUBSAMPLED_IMAGE_UNITS_QCOM 0x8FA1
#అయితే_ముగింపు /* GL_QCOM_texture_foveated_subsampled_layout */

#నిర్వచితం_కాకపోతే GL_QCOM_texture_lod_bias
#నిర్వచించు GL_QCOM_texture_lod_bias 1
#నిర్వచించు GL_TEXTURE_LOD_BIAS_QCOM          0x8C96
#అయితే_ముగింపు /* GL_QCOM_texture_lod_bias */

#నిర్వచితం_కాకపోతే GL_QCOM_tiled_rendering
#నిర్వచించు GL_QCOM_tiled_rendering 1
#నిర్వచించు GL_COLOR_బఫరు_BIT0_QCOM         0x00000001
#నిర్వచించు GL_COLOR_బఫరు_BIT1_QCOM         0x00000002
#నిర్వచించు GL_COLOR_బఫరు_BIT2_QCOM         0x00000004
#నిర్వచించు GL_COLOR_బఫరు_BIT3_QCOM         0x00000008
#నిర్వచించు GL_COLOR_బఫరు_BIT4_QCOM         0x00000010
#నిర్వచించు GL_COLOR_బఫరు_BIT5_QCOM         0x00000020
#నిర్వచించు GL_COLOR_బఫరు_BIT6_QCOM         0x00000040
#నిర్వచించు GL_COLOR_బఫరు_BIT7_QCOM         0x00000080
#నిర్వచించు GL_లోతు_బఫరు_BIT0_QCOM         0x00000100
#నిర్వచించు GL_లోతు_బఫరు_BIT1_QCOM         0x00000200
#నిర్వచించు GL_లోతు_బఫరు_BIT2_QCOM         0x00000400
#నిర్వచించు GL_లోతు_బఫరు_BIT3_QCOM         0x00000800
#నిర్వచించు GL_లోతు_బఫరు_BIT4_QCOM         0x00001000
#నిర్వచించు GL_లోతు_బఫరు_BIT5_QCOM         0x00002000
#నిర్వచించు GL_లోతు_బఫరు_BIT6_QCOM         0x00004000
#నిర్వచించు GL_లోతు_బఫరు_BIT7_QCOM         0x00008000
#నిర్వచించు GL_STENCIL_బఫరు_BIT0_QCOM       0x00010000
#నిర్వచించు GL_STENCIL_బఫరు_BIT1_QCOM       0x00020000
#నిర్వచించు GL_STENCIL_బఫరు_BIT2_QCOM       0x00040000
#నిర్వచించు GL_STENCIL_బఫరు_BIT3_QCOM       0x00080000
#నిర్వచించు GL_STENCIL_బఫరు_BIT4_QCOM       0x00100000
#నిర్వచించు GL_STENCIL_బఫరు_BIT5_QCOM       0x00200000
#నిర్వచించు GL_STENCIL_బఫరు_BIT6_QCOM       0x00400000
#నిర్వచించు GL_STENCIL_బఫరు_BIT7_QCOM       0x00800000
#నిర్వచించు GL_MULTISAMPLE_బఫరు_BIT0_QCOM   0x01000000
#నిర్వచించు GL_MULTISAMPLE_బఫరు_BIT1_QCOM   0x02000000
#నిర్వచించు GL_MULTISAMPLE_బఫరు_BIT2_QCOM   0x04000000
#నిర్వచించు GL_MULTISAMPLE_బఫరు_BIT3_QCOM   0x08000000
#నిర్వచించు GL_MULTISAMPLE_బఫరు_BIT4_QCOM   0x10000000
#నిర్వచించు GL_MULTISAMPLE_బఫరు_BIT5_QCOM   0x20000000
#నిర్వచించు GL_MULTISAMPLE_బఫరు_BIT6_QCOM   0x40000000
#నిర్వచించు GL_MULTISAMPLE_బఫరు_BIT7_QCOM   0x80000000
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSTARTTILINGQCOMPROC) (GLuint x, GLuint y, GLuint వెడల్పు, GLuint ఎత్తు, GLbitfield preserve_ముసుగు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLENDTILINGQCOMPROC) (GLbitfield preserve_ముసుగు);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_ప్రారంభం_Tiling_QCOM (GLuint x, GLuint y, GLuint వెడల్పు, GLuint ఎత్తు, GLbitfield preserve_ముసుగు);
GL_APICALL శూన్య GL_APIENTRY gl_చివర_Tiling_QCOM (GLbitfield preserve_ముసుగు);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_QCOM_tiled_rendering */

#నిర్వచితం_కాకపోతే GL_QCOM_writeonly_rendering
#నిర్వచించు GL_QCOM_writeonly_rendering 1
#నిర్వచించు GL_WRITEONLY_RENDERING_QCOM       0x8823
#అయితే_ముగింపు /* GL_QCOM_writeonly_rendering */

#నిర్వచితం_కాకపోతే GL_QCOM_ycbcr_degamma
#నిర్వచించు GL_QCOM_ycbcr_degamma 1
#నిర్వచించు GL_TEXTURE_Y_DEGAMMA_QCOM         0x9710
#నిర్వచించు GL_TEXTURE_CBCR_DEGAMMA_QCOM      0x9711
#అయితే_ముగింపు /* GL_QCOM_ycbcr_degamma */

#నిర్వచితం_కాకపోతే GL_VIV_shader_ద్విమాన
#నిర్వచించు GL_VIV_shader_ద్విమాన 1
#నిర్వచించు GL_SHADER_ద్విమాన_VIV              0x8FC4
#అయితే_ముగింపు /* GL_VIV_shader_binary */

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు
