#నిర్వచితం_కాకపోతే __gles1_glext_h_
#నిర్వచించు __gles1_glext_h_ 1

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

/* Generated on date 20260803 */

/* Generated C header for:
 * API: gles1
 * Profile: common
 * Versions considered: .*
 * Versions emitted: _nomatch_^
 * Default extensions included: gles1
 * Additional extensions included: _nomatch_^
 * Extensions removed: ^(GL_OES_read_format|GL_OES_compressed_paletted_texture|GL_OES_point_size_array|GL_OES_point_sprite)$
 */

#నిర్వచితం_కాకపోతే GL_KHR_debug
#నిర్వచించు GL_KHR_debug 1
#అయితే_ముగింపు /* GL_KHR_debug */

#నిర్వచితం_కాకపోతే GL_OES_EGL_image
#నిర్వచించు GL_OES_EGL_image 1
రకనిర్వచనం శూన్య *GLeglImageOES;
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLEGLIMAGETARGETTEXTURE2DOESPROC) (GLenum లక్ష్యం, GLeglImageOES image);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLEGLIMAGETARGETRENDERBUFFERSTORAGEOESPROC) (GLenum లక్ష్యం, GLeglImageOES image);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_API శూన్య GL_APIENTRY gl_EGLImage_లక్ష్యం_Texture2_DOES (GLenum లక్ష్యం, GLeglImageOES image);
GL_API శూన్య GL_APIENTRY gl_EGLImage_లక్ష్యం_Renderbuffer_Storage_OES (GLenum లక్ష్యం, GLeglImageOES image);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_OES_EGL_image */

#నిర్వచితం_కాకపోతే GL_OES_EGL_image_external
#నిర్వచించు GL_OES_EGL_image_external 1
#నిర్వచించు GL_TEXTURE_EXTERNAL_OES           0x8D65
#నిర్వచించు GL_TEXTURE_BINDING_EXTERNAL_OES   0x8D67
#నిర్వచించు GL_REQUIRED_TEXTURE_IMAGE_UNITS_OES 0x8D68
#అయితే_ముగింపు /* GL_OES_EGL_image_external */

#నిర్వచితం_కాకపోతే GL_OES_blend_equation_separate
#నిర్వచించు GL_OES_blend_equation_separate 1
#నిర్వచించు GL_BLEND_EQUATION_RGB_OES         0x8009
#నిర్వచించు GL_BLEND_EQUATION_ALPHA_OES       0x883D
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEOESPROC) (GLenum బహుళకం_RGB, GLenum బహుళకం_Alpha);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_API శూన్య GL_APIENTRY glBlendEquationSeparateOES (GLenum బహుళకం_RGB, GLenum బహుళకం_Alpha);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_OES_blend_equation_separate */

#నిర్వచితం_కాకపోతే GL_OES_blend_func_separate
#నిర్వచించు GL_OES_blend_func_separate 1
#నిర్వచించు GL_BLEND_DST_RGB_OES              0x80C8
#నిర్వచించు GL_BLEND_SRC_RGB_OES              0x80C9
#నిర్వచించు GL_BLEND_DST_ALPHA_OES            0x80CA
#నిర్వచించు GL_BLEND_SRC_ALPHA_OES            0x80CB
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEOESPROC) (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_API శూన్య GL_APIENTRY glBlendFuncSeparateOES (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_OES_blend_func_separate */

#నిర్వచితం_కాకపోతే GL_OES_blend_వ్యవకలనం
#నిర్వచించు GL_OES_blend_వ్యవకలనం 1
#నిర్వచించు GL_BLEND_EQUATION_OES             0x8009
#నిర్వచించు GL_FUNC_కూడు_OES                   0x8006
#నిర్వచించు GL_FUNC_వ్యవకలనం_OES              0x800A
#నిర్వచించు GL_FUNC_తిరగేయి_వ్యవకలనం_OES      0x800B
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBLENDEQUATIONOESPROC) (GLenum బహుళకం);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_API శూన్య GL_APIENTRY glBlendEquationOES (GLenum బహుళకం);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_OES_blend_subtract */

#నిర్వచితం_కాకపోతే GL_OES_byte_coordinates
#నిర్వచించు GL_OES_byte_coordinates 1
#అయితే_ముగింపు /* GL_OES_byte_coordinates */

#నిర్వచితం_కాకపోతే GL_OES_compressed_ETC1_RGB8_sub_texture
#నిర్వచించు GL_OES_compressed_ETC1_RGB8_sub_texture 1
#అయితే_ముగింపు /* GL_OES_compressed_ETC1_RGB8_sub_texture */

#నిర్వచితం_కాకపోతే GL_OES_compressed_ETC1_RGB8_texture
#నిర్వచించు GL_OES_compressed_ETC1_RGB8_texture 1
#నిర్వచించు GL_ETC1_RGB8_OES                  0x8D64
#అయితే_ముగింపు /* GL_OES_compressed_ETC1_RGB8_texture */

#నిర్వచితం_కాకపోతే GL_OES_depth24
#నిర్వచించు GL_OES_depth24 1
#నిర్వచించు GL_లోతు_COMPONENT24_OES          0x81A6
#అయితే_ముగింపు /* GL_OES_depth24 */

#నిర్వచితం_కాకపోతే GL_OES_depth32
#నిర్వచించు GL_OES_depth32 1
#నిర్వచించు GL_లోతు_COMPONENT32_OES          0x81A7
#అయితే_ముగింపు /* GL_OES_depth32 */

#నిర్వచితం_కాకపోతే GL_OES_draw_texture
#నిర్వచించు GL_OES_draw_texture 1
#నిర్వచించు GL_TEXTURE_CROP_RECT_OES          0x8B9D
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWTEXSOESPROC) (GLshort x, GLshort y, GLshort z, GLshort వెడల్పు, GLshort ఎత్తు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWTEXIOESPROC) (GLint x, GLint y, GLint z, GLint వెడల్పు, GLint ఎత్తు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWTEXXOESPROC) (GLfixed x, GLfixed y, GLfixed z, GLfixed వెడల్పు, GLfixed ఎత్తు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWTEXSVOESPROC) (స్థిరరాశి GLshort *coords);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWTEXIVOESPROC) (స్థిరరాశి GLint *coords);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWTEXXVOESPROC) (స్థిరరాశి GLfixed *coords);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWTEXFOESPROC) (GLfloat x, GLfloat y, GLfloat z, GLfloat వెడల్పు, GLfloat ఎత్తు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWTEXFVOESPROC) (స్థిరరాశి GLfloat *coords);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_API శూన్య GL_APIENTRY glDrawTexsOES (GLshort x, GLshort y, GLshort z, GLshort వెడల్పు, GLshort ఎత్తు);
GL_API శూన్య GL_APIENTRY glDrawTexiOES (GLint x, GLint y, GLint z, GLint వెడల్పు, GLint ఎత్తు);
GL_API శూన్య GL_APIENTRY glDrawTexxOES (GLfixed x, GLfixed y, GLfixed z, GLfixed వెడల్పు, GLfixed ఎత్తు);
GL_API శూన్య GL_APIENTRY glDrawTexsvOES (స్థిరరాశి GLshort *coords);
GL_API శూన్య GL_APIENTRY glDrawTexivOES (స్థిరరాశి GLint *coords);
GL_API శూన్య GL_APIENTRY glDrawTexxvOES (స్థిరరాశి GLfixed *coords);
GL_API శూన్య GL_APIENTRY glDrawTexfOES (GLfloat x, GLfloat y, GLfloat z, GLfloat వెడల్పు, GLfloat ఎత్తు);
GL_API శూన్య GL_APIENTRY glDrawTexfvOES (స్థిరరాశి GLfloat *coords);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_OES_draw_texture */

#నిర్వచితం_కాకపోతే GL_OES_element_సూచీ_uint
#నిర్వచించు GL_OES_element_సూచీ_uint 1
#నిర్వచించు GL_UNSIGNED_INT                   0x1405
#అయితే_ముగింపు /* GL_OES_element_index_uint */

#నిర్వచితం_కాకపోతే GL_OES_extended_మాతృక_palette
#నిర్వచించు GL_OES_extended_మాతృక_palette 1
#అయితే_ముగింపు /* GL_OES_extended_matrix_palette */

#నిర్వచితం_కాకపోతే GL_OES_fbo_render_mipmap
#నిర్వచించు GL_OES_fbo_render_mipmap 1
#అయితే_ముగింపు /* GL_OES_fbo_render_mipmap */

#నిర్వచితం_కాకపోతే GL_OES_fixed_బిందువు
#నిర్వచించు GL_OES_fixed_బిందువు 1
#నిర్వచించు GL_FIXED_OES                      0x140C
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLALPHAFUNCXOESPROC) (GLenum func, GLfixed ref);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCLEARCOLORXOESPROC) (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCLEARDEPTHXOESPROC) (GLfixed లోతు_2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCLIPPLANEXOESPROC) (GLenum plane, స్థిరరాశి GLfixed *equation);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCOLOR4XOESPROC) (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDEPTHRANGEXOESPROC) (GLfixed n, GLfixed f);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFOGXOESPROC) (GLenum pname, GLfixed param);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFOGXVOESPROC) (GLenum pname, స్థిరరాశి GLfixed *param);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFRUSTUMXOESPROC) (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETCLIPPLANEXOESPROC) (GLenum plane, GLfixed *equation);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETFIXEDVOESPROC) (GLenum pname, GLfixed *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETTEXENVXVOESPROC) (GLenum లక్ష్యం, GLenum pname, GLfixed *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETTEXPARAMETERXVOESPROC) (GLenum లక్ష్యం, GLenum pname, GLfixed *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLLIGHTMODELXOESPROC) (GLenum pname, GLfixed param);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLLIGHTMODELXVOESPROC) (GLenum pname, స్థిరరాశి GLfixed *param);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLLIGHTXOESPROC) (GLenum light, GLenum pname, GLfixed param);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLLIGHTXVOESPROC) (GLenum light, GLenum pname, స్థిరరాశి GLfixed *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLLINEWIDTHXOESPROC) (GLfixed వెడల్పు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLLOADMATRIXXOESPROC) (స్థిరరాశి GLfixed *m);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMATERIALXOESPROC) (GLenum face, GLenum pname, GLfixed param);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMATERIALXVOESPROC) (GLenum face, GLenum pname, స్థిరరాశి GLfixed *param);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMULTMATRIXXOESPROC) (స్థిరరాశి GLfixed *m);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMULTITEXCOORD4XOESPROC) (GLenum texture, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLNORMAL3XOESPROC) (GLfixed nx, GLfixed ny, GLfixed nz);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLORTHOXOESPROC) (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPOINTPARAMETERXVOESPROC) (GLenum pname, స్థిరరాశి GLfixed *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPOINTSIZEXOESPROC) (GLfixed కొలత);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPOLYGONOFFSETXOESPROC) (GLfixed గుణకం, GLfixed units);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLROTATEXOESPROC) (GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSCALEXOESPROC) (GLfixed x, GLfixed y, GLfixed z);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXENVXOESPROC) (GLenum లక్ష్యం, GLenum pname, GLfixed param);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXENVXVOESPROC) (GLenum లక్ష్యం, GLenum pname, స్థిరరాశి GLfixed *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXPARAMETERXOESPROC) (GLenum లక్ష్యం, GLenum pname, GLfixed param);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXPARAMETERXVOESPROC) (GLenum లక్ష్యం, GLenum pname, స్థిరరాశి GLfixed *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTRANSLATEXOESPROC) (GLfixed x, GLfixed y, GLfixed z);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETLIGHTXVOESPROC) (GLenum light, GLenum pname, GLfixed *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETMATERIALXVOESPROC) (GLenum face, GLenum pname, GLfixed *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPOINTPARAMETERXOESPROC) (GLenum pname, GLfixed param);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSAMPLECOVERAGEXOESPROC) (GLclampx విలువ, GLboolean invert);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETTEXGENXVOESPROC) (GLenum coord, GLenum pname, GLfixed *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXGENXOESPROC) (GLenum coord, GLenum pname, GLfixed param);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXGENXVOESPROC) (GLenum coord, GLenum pname, స్థిరరాశి GLfixed *params);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_API శూన్య GL_APIENTRY glAlphaFuncxOES (GLenum func, GLfixed ref);
GL_API శూన్య GL_APIENTRY glClearColorxOES (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GL_API శూన్య GL_APIENTRY glClearDepthxOES (GLfixed లోతు_2);
GL_API శూన్య GL_APIENTRY glClipPlanexOES (GLenum plane, స్థిరరాశి GLfixed *equation);
GL_API శూన్య GL_APIENTRY glColor4xOES (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GL_API శూన్య GL_APIENTRY gl_లోతు_Rangex_OES (GLfixed n, GLfixed f);
GL_API శూన్య GL_APIENTRY glFogxOES (GLenum pname, GLfixed param);
GL_API శూన్య GL_APIENTRY glFogxvOES (GLenum pname, స్థిరరాశి GLfixed *param);
GL_API శూన్య GL_APIENTRY glFrustumxOES (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
GL_API శూన్య GL_APIENTRY glGetClipPlanexOES (GLenum plane, GLfixed *equation);
GL_API శూన్య GL_APIENTRY glGetFixedvOES (GLenum pname, GLfixed *params);
GL_API శూన్య GL_APIENTRY glGetTexEnvxvOES (GLenum లక్ష్యం, GLenum pname, GLfixed *params);
GL_API శూన్య GL_APIENTRY glGetTexParameterxvOES (GLenum లక్ష్యం, GLenum pname, GLfixed *params);
GL_API శూన్య GL_APIENTRY glLightModelxOES (GLenum pname, GLfixed param);
GL_API శూన్య GL_APIENTRY glLightModelxvOES (GLenum pname, స్థిరరాశి GLfixed *param);
GL_API శూన్య GL_APIENTRY glLightxOES (GLenum light, GLenum pname, GLfixed param);
GL_API శూన్య GL_APIENTRY glLightxvOES (GLenum light, GLenum pname, స్థిరరాశి GLfixed *params);
GL_API శూన్య GL_APIENTRY gl_పంక్తి_Widthx_OES (GLfixed వెడల్పు);
GL_API శూన్య GL_APIENTRY gl_ఎక్కించు_Matrixx_OES (స్థిరరాశి GLfixed *m);
GL_API శూన్య GL_APIENTRY glMaterialxOES (GLenum face, GLenum pname, GLfixed param);
GL_API శూన్య GL_APIENTRY glMaterialxvOES (GLenum face, GLenum pname, స్థిరరాశి GLfixed *param);
GL_API శూన్య GL_APIENTRY glMultMatrixxOES (స్థిరరాశి GLfixed *m);
GL_API శూన్య GL_APIENTRY glMultiTexCoord4xOES (GLenum texture, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
GL_API శూన్య GL_APIENTRY glNormal3xOES (GLfixed nx, GLfixed ny, GLfixed nz);
GL_API శూన్య GL_APIENTRY glOrthoxOES (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
GL_API శూన్య GL_APIENTRY gl_బిందువు_Parameterxv_OES (GLenum pname, స్థిరరాశి GLfixed *params);
GL_API శూన్య GL_APIENTRY gl_బిందువు_Sizex_OES (GLfixed కొలత);
GL_API శూన్య GL_APIENTRY glPolygonOffsetxOES (GLfixed గుణకం, GLfixed units);
GL_API శూన్య GL_APIENTRY glRotatexOES (GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
GL_API శూన్య GL_APIENTRY glScalexOES (GLfixed x, GLfixed y, GLfixed z);
GL_API శూన్య GL_APIENTRY glTexEnvxOES (GLenum లక్ష్యం, GLenum pname, GLfixed param);
GL_API శూన్య GL_APIENTRY glTexEnvxvOES (GLenum లక్ష్యం, GLenum pname, స్థిరరాశి GLfixed *params);
GL_API శూన్య GL_APIENTRY glTexParameterxOES (GLenum లక్ష్యం, GLenum pname, GLfixed param);
GL_API శూన్య GL_APIENTRY glTexParameterxvOES (GLenum లక్ష్యం, GLenum pname, స్థిరరాశి GLfixed *params);
GL_API శూన్య GL_APIENTRY glTranslatexOES (GLfixed x, GLfixed y, GLfixed z);
GL_API శూన్య GL_APIENTRY glGetLightxvOES (GLenum light, GLenum pname, GLfixed *params);
GL_API శూన్య GL_APIENTRY glGetMaterialxvOES (GLenum face, GLenum pname, GLfixed *params);
GL_API శూన్య GL_APIENTRY gl_బిందువు_Parameterx_OES (GLenum pname, GLfixed param);
GL_API శూన్య GL_APIENTRY glSampleCoveragexOES (GLclampx విలువ, GLboolean invert);
GL_API శూన్య GL_APIENTRY glGetTexGenxvOES (GLenum coord, GLenum pname, GLfixed *params);
GL_API శూన్య GL_APIENTRY glTexGenxOES (GLenum coord, GLenum pname, GLfixed param);
GL_API శూన్య GL_APIENTRY glTexGenxvOES (GLenum coord, GLenum pname, స్థిరరాశి GLfixed *params);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_OES_fixed_point */

#నిర్వచితం_కాకపోతే GL_OES_framebuffer_object
#నిర్వచించు GL_OES_framebuffer_object 1
#నిర్వచించు GL_NONE_OES                       0
#నిర్వచించు GL_FRAMEBUFFER_OES                0x8D40
#నిర్వచించు GL_RENDERBUFFER_OES               0x8D41
#నిర్వచించు GL_RGBA4_OES                      0x8056
#నిర్వచించు GL_RGB5_A1_OES                    0x8057
#నిర్వచించు GL_RGB565_OES                     0x8D62
#నిర్వచించు GL_లోతు_COMPONENT16_OES          0x81A5
#నిర్వచించు GL_RENDERBUFFER_వెడల్పు_OES         0x8D42
#నిర్వచించు GL_RENDERBUFFER_ఎత్తు_OES        0x8D43
#నిర్వచించు GL_RENDERBUFFER_అంతర్గత_FORMAT_OES 0x8D44
#నిర్వచించు GL_RENDERBUFFER_RED_కొలత_OES      0x8D50
#నిర్వచించు GL_RENDERBUFFER_GREEN_కొలత_OES    0x8D51
#నిర్వచించు GL_RENDERBUFFER_BLUE_కొలత_OES     0x8D52
#నిర్వచించు GL_RENDERBUFFER_ALPHA_కొలత_OES    0x8D53
#నిర్వచించు GL_RENDERBUFFER_లోతు_కొలత_OES    0x8D54
#నిర్వచించు GL_RENDERBUFFER_STENCIL_కొలత_OES  0x8D55
#నిర్వచించు GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_OES 0x8CD0
#నిర్వచించు GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_OES 0x8CD1
#నిర్వచించు GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_OES 0x8CD2
#నిర్వచించు GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_OES 0x8CD3
#నిర్వచించు GL_COLOR_ATTACHMENT0_OES          0x8CE0
#నిర్వచించు GL_లోతు_ATTACHMENT_OES           0x8D00
#నిర్వచించు GL_STENCIL_ATTACHMENT_OES         0x8D20
#నిర్వచించు GL_FRAMEBUFFER_COMPLETE_OES       0x8CD5
#నిర్వచించు GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_OES 0x8CD6
#నిర్వచించు GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_OES 0x8CD7
#నిర్వచించు GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_OES 0x8CD9
#నిర్వచించు GL_FRAMEBUFFER_INCOMPLETE_FORMATS_OES 0x8CDA
#నిర్వచించు GL_FRAMEBUFFER_UNSUPPORTED_OES    0x8CDD
#నిర్వచించు GL_FRAMEBUFFER_BINDING_OES        0x8CA6
#నిర్వచించు GL_RENDERBUFFER_BINDING_OES       0x8CA7
#నిర్వచించు GL_MAX_RENDERBUFFER_కొలత_OES      0x84E8
#నిర్వచించు GL_INVALID_FRAMEBUFFER_OPERATION_OES 0x0506
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLISRENDERBUFFEROESPROC) (GLuint renderbuffer);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBINDRENDERBUFFEROESPROC) (GLenum లక్ష్యం, GLuint renderbuffer);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDELETERENDERBUFFERSOESPROC) (GLsizei n, స్థిరరాశి GLuint *renderbuffers);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGENRENDERBUFFERSOESPROC) (GLsizei n, GLuint *renderbuffers);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEOESPROC) (GLenum లక్ష్యం, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVOESPROC) (GLenum లక్ష్యం, GLenum pname, GLint *params);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLISFRAMEBUFFEROESPROC) (GLuint framebuffer);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBINDFRAMEBUFFEROESPROC) (GLenum లక్ష్యం, GLuint framebuffer);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDELETEFRAMEBUFFERSOESPROC) (GLsizei n, స్థిరరాశి GLuint *framebuffers);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGENFRAMEBUFFERSOESPROC) (GLsizei n, GLuint *framebuffers);
రకనిర్వచనం GLenum (GL_APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSOESPROC) (GLenum లక్ష్యం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFEROESPROC) (GLenum లక్ష్యం, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DOESPROC) (GLenum లక్ష్యం, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVOESPROC) (GLenum లక్ష్యం, GLenum attachment, GLenum pname, GLint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGENERATEMIPMAPOESPROC) (GLenum లక్ష్యం);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_API GLboolean GL_APIENTRY glIsRenderbufferOES (GLuint renderbuffer);
GL_API శూన్య GL_APIENTRY glBindRenderbufferOES (GLenum లక్ష్యం, GLuint renderbuffer);
GL_API శూన్య GL_APIENTRY glDeleteRenderbuffersOES (GLsizei n, స్థిరరాశి GLuint *renderbuffers);
GL_API శూన్య GL_APIENTRY glGenRenderbuffersOES (GLsizei n, GLuint *renderbuffers);
GL_API శూన్య GL_APIENTRY glRenderbufferStorageOES (GLenum లక్ష్యం, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
GL_API శూన్య GL_APIENTRY glGetRenderbufferParameterivOES (GLenum లక్ష్యం, GLenum pname, GLint *params);
GL_API GLboolean GL_APIENTRY glIsFramebufferOES (GLuint framebuffer);
GL_API శూన్య GL_APIENTRY glBindFramebufferOES (GLenum లక్ష్యం, GLuint framebuffer);
GL_API శూన్య GL_APIENTRY glDeleteFramebuffersOES (GLsizei n, స్థిరరాశి GLuint *framebuffers);
GL_API శూన్య GL_APIENTRY glGenFramebuffersOES (GLsizei n, GLuint *framebuffers);
GL_API GLenum GL_APIENTRY gl_Check_Framebuffer_స్థితి_OES (GLenum లక్ష్యం);
GL_API శూన్య GL_APIENTRY glFramebufferRenderbufferOES (GLenum లక్ష్యం, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
GL_API శూన్య GL_APIENTRY glFramebufferTexture2DOES (GLenum లక్ష్యం, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GL_API శూన్య GL_APIENTRY glGetFramebufferAttachmentParameterivOES (GLenum లక్ష్యం, GLenum attachment, GLenum pname, GLint *params);
GL_API శూన్య GL_APIENTRY glGenerateMipmapOES (GLenum లక్ష్యం);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_OES_framebuffer_object */

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
GL_API శూన్య *GL_APIENTRY gl_Map_బఫరు_OES (GLenum లక్ష్యం, GLenum access);
GL_API GLboolean GL_APIENTRY gl_Unmap_బఫరు_OES (GLenum లక్ష్యం);
GL_API శూన్య GL_APIENTRY gl_Get_బఫరు_Pointerv_OES (GLenum లక్ష్యం, GLenum pname, శూన్య **params);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_OES_mapbuffer */

#నిర్వచితం_కాకపోతే GL_OES_మాతృక_get
#నిర్వచించు GL_OES_మాతృక_get 1
#నిర్వచించు GL_MODELVIEW_మాతృక_FLOAT_AS_INT_బిట్లు_OES 0x898D
#నిర్వచించు GL_PROJECTION_మాతృక_FLOAT_AS_INT_బిట్లు_OES 0x898E
#నిర్వచించు GL_TEXTURE_మాతృక_FLOAT_AS_INT_బిట్లు_OES 0x898F
#అయితే_ముగింపు /* GL_OES_matrix_get */

#నిర్వచితం_కాకపోతే GL_OES_మాతృక_palette
#నిర్వచించు GL_OES_మాతృక_palette 1
#నిర్వచించు GL_MAX_శీర్షం_UNITS_OES           0x86A4
#నిర్వచించు GL_MAX_PALETTE_MATRICES_OES       0x8842
#నిర్వచించు GL_మాతృక_PALETTE_OES             0x8840
#నిర్వచించు GL_మాతృక_సూచీ_ARRAY_OES         0x8844
#నిర్వచించు GL_బరువు_ARRAY_OES               0x86AD
#నిర్వచించు GL_CURRENT_PALETTE_మాతృక_OES     0x8843
#నిర్వచించు GL_మాతృక_సూచీ_ARRAY_కొలత_OES    0x8846
#నిర్వచించు GL_మాతృక_సూచీ_ARRAY_TYPE_OES    0x8847
#నిర్వచించు GL_మాతృక_సూచీ_ARRAY_STRIDE_OES  0x8848
#నిర్వచించు GL_మాతృక_సూచీ_ARRAY_సూచిక_OES 0x8849
#నిర్వచించు GL_మాతృక_సూచీ_ARRAY_బఫరు_BINDING_OES 0x8B9E
#నిర్వచించు GL_బరువు_ARRAY_కొలత_OES          0x86AB
#నిర్వచించు GL_బరువు_ARRAY_TYPE_OES          0x86A9
#నిర్వచించు GL_బరువు_ARRAY_STRIDE_OES        0x86AA
#నిర్వచించు GL_బరువు_ARRAY_సూచిక_OES       0x86AC
#నిర్వచించు GL_బరువు_ARRAY_బఫరు_BINDING_OES 0x889E
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCURRENTPALETTEMATRIXOESPROC) (GLuint matrixpaletteindex);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLLOADPALETTEFROMMODELVIEWMATRIXOESPROC) (శూన్య);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMATRIXINDEXPOINTEROESPROC) (GLint కొలత, GLenum type, GLsizei stride, స్థిరరాశి శూన్య *సూచిక_2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLWEIGHTPOINTEROESPROC) (GLint కొలత, GLenum type, GLsizei stride, స్థిరరాశి శూన్య *సూచిక_2);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_API శూన్య GL_APIENTRY gl_Current_Palette_మాతృక_OES (GLuint matrixpaletteindex);
GL_API శూన్య GL_APIENTRY gl_ఎక్కించు_Palette_From_Model_View_మాతృక_OES (శూన్య);
GL_API శూన్య GL_APIENTRY gl_మాతృక_సూచీ_సూచిక_OES (GLint కొలత, GLenum type, GLsizei stride, స్థిరరాశి శూన్య *సూచిక_2);
GL_API శూన్య GL_APIENTRY gl_బరువు_సూచిక_OES (GLint కొలత, GLenum type, GLsizei stride, స్థిరరాశి శూన్య *సూచిక_2);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_OES_matrix_palette */

#నిర్వచితం_కాకపోతే GL_OES_packed_లోతు_stencil
#నిర్వచించు GL_OES_packed_లోతు_stencil 1
#నిర్వచించు GL_లోతు_STENCIL_OES              0x84F9
#నిర్వచించు GL_UNSIGNED_INT_24_8_OES          0x84FA
#నిర్వచించు GL_DEPTH24_STENCIL8_OES           0x88F0
#అయితే_ముగింపు /* GL_OES_packed_depth_stencil */

#నిర్వచితం_కాకపోతే GL_OES_query_మాతృక
#నిర్వచించు GL_OES_query_మాతృక 1
రకనిర్వచనం GLbitfield (GL_APIENTRYP PFNGLQUERYMATRIXXOESPROC) (GLfixed *mantissa, GLint *exponent);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_API GLbitfield GL_APIENTRY glQueryMatrixxOES (GLfixed *mantissa, GLint *exponent);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_OES_query_matrix */

#నిర్వచితం_కాకపోతే GL_OES_required_internalformat
#నిర్వచించు GL_OES_required_internalformat 1
#నిర్వచించు GL_ALPHA8_OES                     0x803C
#నిర్వచించు GL_LUMINANCE4_ALPHA4_OES          0x8043
#నిర్వచించు GL_LUMINANCE8_ALPHA8_OES          0x8045
#నిర్వచించు GL_LUMINANCE8_OES                 0x8040
#నిర్వచించు GL_RGB8_OES                       0x8051
#నిర్వచించు GL_RGBA8_OES                      0x8058
#నిర్వచించు GL_RGB10_EXT                      0x8052
#నిర్వచించు GL_RGB10_A2_EXT                   0x8059
#అయితే_ముగింపు /* GL_OES_required_internalformat */

#నిర్వచితం_కాకపోతే GL_OES_rgb8_rgba8
#నిర్వచించు GL_OES_rgb8_rgba8 1
#అయితే_ముగింపు /* GL_OES_rgb8_rgba8 */

#నిర్వచితం_కాకపోతే GL_OES_single_precision
#నిర్వచించు GL_OES_single_precision 1
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCLEARDEPTHFOESPROC) (GLclampf లోతు_2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCLIPPLANEFOESPROC) (GLenum plane, స్థిరరాశి GLfloat *equation);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDEPTHRANGEFOESPROC) (GLclampf n, GLclampf f);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFRUSTUMFOESPROC) (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETCLIPPLANEFOESPROC) (GLenum plane, GLfloat *equation);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLORTHOFOESPROC) (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_API శూన్య GL_APIENTRY glClearDepthfOES (GLclampf లోతు_2);
GL_API శూన్య GL_APIENTRY glClipPlanefOES (GLenum plane, స్థిరరాశి GLfloat *equation);
GL_API శూన్య GL_APIENTRY gl_లోతు_Rangef_OES (GLclampf n, GLclampf f);
GL_API శూన్య GL_APIENTRY glFrustumfOES (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
GL_API శూన్య GL_APIENTRY glGetClipPlanefOES (GLenum plane, GLfloat *equation);
GL_API శూన్య GL_APIENTRY glOrthofOES (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_OES_single_precision */

#నిర్వచితం_కాకపోతే GL_OES_stencil1
#నిర్వచించు GL_OES_stencil1 1
#నిర్వచించు GL_STENCIL_INDEX1_OES             0x8D46
#అయితే_ముగింపు /* GL_OES_stencil1 */

#నిర్వచితం_కాకపోతే GL_OES_stencil4
#నిర్వచించు GL_OES_stencil4 1
#నిర్వచించు GL_STENCIL_INDEX4_OES             0x8D47
#అయితే_ముగింపు /* GL_OES_stencil4 */

#నిర్వచితం_కాకపోతే GL_OES_stencil8
#నిర్వచించు GL_OES_stencil8 1
#నిర్వచించు GL_STENCIL_INDEX8_OES             0x8D48
#అయితే_ముగింపు /* GL_OES_stencil8 */

#నిర్వచితం_కాకపోతే GL_OES_stencil_wrap
#నిర్వచించు GL_OES_stencil_wrap 1
#నిర్వచించు GL_INCR_WRAP_OES                  0x8507
#నిర్వచించు GL_DECR_WRAP_OES                  0x8508
#అయితే_ముగింపు /* GL_OES_stencil_wrap */

#నిర్వచితం_కాకపోతే GL_OES_surfaceless_context
#నిర్వచించు GL_OES_surfaceless_context 1
#నిర్వచించు GL_FRAMEBUFFER_UNDEFINED_OES      0x8219
#అయితే_ముగింపు /* GL_OES_surfaceless_context */

#నిర్వచితం_కాకపోతే GL_OES_texture_cube_map
#నిర్వచించు GL_OES_texture_cube_map 1
#నిర్వచించు GL_సాధారణ_MAP_OES                 0x8511
#నిర్వచించు GL_REFLECTION_MAP_OES             0x8512
#నిర్వచించు GL_TEXTURE_CUBE_MAP_OES           0x8513
#నిర్వచించు GL_TEXTURE_BINDING_CUBE_MAP_OES   0x8514
#నిర్వచించు GL_TEXTURE_CUBE_MAP_ధనాత్మక_X_OES 0x8515
#నిర్వచించు GL_TEXTURE_CUBE_MAP_NEGATIVE_X_OES 0x8516
#నిర్వచించు GL_TEXTURE_CUBE_MAP_ధనాత్మక_Y_OES 0x8517
#నిర్వచించు GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_OES 0x8518
#నిర్వచించు GL_TEXTURE_CUBE_MAP_ధనాత్మక_Z_OES 0x8519
#నిర్వచించు GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_OES 0x851A
#నిర్వచించు GL_MAX_CUBE_MAP_TEXTURE_కొలత_OES  0x851C
#నిర్వచించు GL_TEXTURE_GEN_బహుళకం_OES           0x2500
#నిర్వచించు GL_TEXTURE_GEN_STR_OES            0x8D60
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXGENFOESPROC) (GLenum coord, GLenum pname, GLfloat param);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXGENFVOESPROC) (GLenum coord, GLenum pname, స్థిరరాశి GLfloat *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXGENIOESPROC) (GLenum coord, GLenum pname, GLint param);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXGENIVOESPROC) (GLenum coord, GLenum pname, స్థిరరాశి GLint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETTEXGENFVOESPROC) (GLenum coord, GLenum pname, GLfloat *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETTEXGENIVOESPROC) (GLenum coord, GLenum pname, GLint *params);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_API శూన్య GL_APIENTRY glTexGenfOES (GLenum coord, GLenum pname, GLfloat param);
GL_API శూన్య GL_APIENTRY glTexGenfvOES (GLenum coord, GLenum pname, స్థిరరాశి GLfloat *params);
GL_API శూన్య GL_APIENTRY glTexGeniOES (GLenum coord, GLenum pname, GLint param);
GL_API శూన్య GL_APIENTRY glTexGenivOES (GLenum coord, GLenum pname, స్థిరరాశి GLint *params);
GL_API శూన్య GL_APIENTRY glGetTexGenfvOES (GLenum coord, GLenum pname, GLfloat *params);
GL_API శూన్య GL_APIENTRY glGetTexGenivOES (GLenum coord, GLenum pname, GLint *params);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_OES_texture_cube_map */

#నిర్వచితం_కాకపోతే GL_OES_texture_env_crossbar
#నిర్వచించు GL_OES_texture_env_crossbar 1
#అయితే_ముగింపు /* GL_OES_texture_env_crossbar */

#నిర్వచితం_కాకపోతే GL_OES_texture_mirrored_repeat
#నిర్వచించు GL_OES_texture_mirrored_repeat 1
#నిర్వచించు GL_MIRRORED_REPEAT_OES            0x8370
#అయితే_ముగింపు /* GL_OES_texture_mirrored_repeat */

#నిర్వచితం_కాకపోతే GL_OES_texture_npot
#నిర్వచించు GL_OES_texture_npot 1
#అయితే_ముగింపు /* GL_OES_texture_npot */

#నిర్వచితం_కాకపోతే GL_OES_శీర్షం_array_object
#నిర్వచించు GL_OES_శీర్షం_array_object 1
#నిర్వచించు GL_శీర్షం_ARRAY_BINDING_OES       0x85B5
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBINDVERTEXARRAYOESPROC) (GLuint array);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDELETEVERTEXARRAYSOESPROC) (GLsizei n, స్థిరరాశి GLuint *arrays);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGENVERTEXARRAYSOESPROC) (GLsizei n, GLuint *arrays);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLISVERTEXARRAYOESPROC) (GLuint array);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_API శూన్య GL_APIENTRY gl_Bind_శీర్షం_Array_OES (GLuint array);
GL_API శూన్య GL_APIENTRY gl_Delete_శీర్షం_Arrays_OES (GLsizei n, స్థిరరాశి GLuint *arrays);
GL_API శూన్య GL_APIENTRY gl_Gen_శీర్షం_Arrays_OES (GLsizei n, GLuint *arrays);
GL_API GLboolean GL_APIENTRY gl_Is_శీర్షం_Array_OES (GLuint array);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_OES_vertex_array_object */

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

#నిర్వచితం_కాకపోతే GL_APPLE_copy_texture_స్థాయిలు
#నిర్వచించు GL_APPLE_copy_texture_స్థాయిలు 1
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCOPYTEXTURELEVELSAPPLEPROC) (GLuint destinationTexture, GLuint ఆధారం_Texture, GLint ఆధారం_పునాది_Level, GLsizei ఆధారం_Level_లెక్క);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_API శూన్య GL_APIENTRY gl_Copy_Texture_స్థాయిలు_APPLE (GLuint destinationTexture, GLuint ఆధారం_Texture, GLint ఆధారం_పునాది_Level, GLsizei ఆధారం_Level_లెక్క);
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
GL_API శూన్య GL_APIENTRY glRenderbufferStorageMultisampleAPPLE (GLenum లక్ష్యం, GLsizei samples, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
GL_API శూన్య GL_APIENTRY glResolveMultisampleFramebufferAPPLE (శూన్య);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_APPLE_framebuffer_multisample */

#నిర్వచితం_కాకపోతే GL_APPLE_sync
#నిర్వచించు GL_APPLE_sync 1
రకనిర్వచనం నిర్మాణం __GLsync *GLsync;
రకనిర్వచనం khronos_uint64_t GLuint64;
రకనిర్వచనం khronos_int64_t GLint64;
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
GL_API GLsync GL_APIENTRY glFenceSyncAPPLE (GLenum condition, GLbitfield flags);
GL_API GLboolean GL_APIENTRY glIsSyncAPPLE (GLsync sync);
GL_API శూన్య GL_APIENTRY glDeleteSyncAPPLE (GLsync sync);
GL_API GLenum GL_APIENTRY glClientWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_API శూన్య GL_APIENTRY glWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_API శూన్య GL_APIENTRY glGetInteger64vAPPLE (GLenum pname, GLint64 *params);
GL_API శూన్య GL_APIENTRY glGetSyncivAPPLE (GLsync sync, GLenum pname, GLsizei లెక్క, GLsizei *నిడివి, GLint *విలువలు);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_APPLE_sync */

#నిర్వచితం_కాకపోతే GL_APPLE_texture_2D_limited_npot
#నిర్వచించు GL_APPLE_texture_2D_limited_npot 1
#అయితే_ముగింపు /* GL_APPLE_texture_2D_limited_npot */

#నిర్వచితం_కాకపోతే GL_APPLE_texture_format_BGRA8888
#నిర్వచించు GL_APPLE_texture_format_BGRA8888 1
#నిర్వచించు GL_BGRA_EXT                       0x80E1
#నిర్వచించు GL_BGRA8_EXT                      0x93A1
#అయితే_ముగింపు /* GL_APPLE_texture_format_BGRA8888 */

#నిర్వచితం_కాకపోతే GL_APPLE_texture_max_level
#నిర్వచించు GL_APPLE_texture_max_level 1
#నిర్వచించు GL_TEXTURE_MAX_LEVEL_APPLE        0x813D
#అయితే_ముగింపు /* GL_APPLE_texture_max_level */

#నిర్వచితం_కాకపోతే GL_ARM_rgba8
#నిర్వచించు GL_ARM_rgba8 1
#అయితే_ముగింపు /* GL_ARM_rgba8 */

#నిర్వచితం_కాకపోతే GL_EXT_blend_minmax
#నిర్వచించు GL_EXT_blend_minmax 1
#నిర్వచించు GL_MIN_EXT                        0x8007
#నిర్వచించు GL_MAX_EXT                        0x8008
#అయితే_ముగింపు /* GL_EXT_blend_minmax */

#నిర్వచితం_కాకపోతే GL_EXT_debug_marker
#నిర్వచించు GL_EXT_debug_marker 1
రకనిర్వచనం అక్షరం GLchar;
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLINSERTEVENTMARKEREXTPROC) (GLsizei నిడివి, స్థిరరాశి GLchar *marker);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPUSHGROUPMARKEREXTPROC) (GLsizei నిడివి, స్థిరరాశి GLchar *marker);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPOPGROUPMARKEREXTPROC) (శూన్య);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_API శూన్య GL_APIENTRY gl_చొప్పించు_Event_Marker_EXT (GLsizei నిడివి, స్థిరరాశి GLchar *marker);
GL_API శూన్య GL_APIENTRY gl_నెట్టు_సమూహం_Marker_EXT (GLsizei నిడివి, స్థిరరాశి GLchar *marker);
GL_API శూన్య GL_APIENTRY gl_తీయి_సమూహం_Marker_EXT (శూన్య);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_debug_marker */

#నిర్వచితం_కాకపోతే GL_EXT_discard_framebuffer
#నిర్వచించు GL_EXT_discard_framebuffer 1
#నిర్వచించు GL_COLOR_EXT                      0x1800
#నిర్వచించు GL_లోతు_EXT                      0x1801
#నిర్వచించు GL_STENCIL_EXT                    0x1802
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDISCARDFRAMEBUFFEREXTPROC) (GLenum లక్ష్యం, GLsizei అంకె_Attachments, స్థిరరాశి GLenum *attachments);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_API శూన్య GL_APIENTRY glDiscardFramebufferEXT (GLenum లక్ష్యం, GLsizei అంకె_Attachments, స్థిరరాశి GLenum *attachments);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_discard_framebuffer */

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
GL_API శూన్య *GL_APIENTRY gl_Map_బఫరు_Range_EXT (GLenum లక్ష్యం, GLintptr స్థానభ్రంశం_2, GLsizeiptr నిడివి, GLbitfield access);
GL_API శూన్య GL_APIENTRY gl_Flush_Mapped_బఫరు_Range_EXT (GLenum లక్ష్యం, GLintptr స్థానభ్రంశం_2, GLsizeiptr నిడివి);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_map_buffer_range */

#నిర్వచితం_కాకపోతే GL_EXT_multi_draw_arrays
#నిర్వచించు GL_EXT_multi_draw_arrays 1
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMULTIDRAWARRAYSEXTPROC) (GLenum బహుళకం, స్థిరరాశి GLint *మొదటి, స్థిరరాశి GLsizei *లెక్క, GLsizei primcount);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSEXTPROC) (GLenum బహుళకం, స్థిరరాశి GLsizei *లెక్క, GLenum type, స్థిరరాశి శూన్య *స్థిరరాశి*indices, GLsizei primcount);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_API శూన్య GL_APIENTRY glMultiDrawArraysEXT (GLenum బహుళకం, స్థిరరాశి GLint *మొదటి, స్థిరరాశి GLsizei *లెక్క, GLsizei primcount);
GL_API శూన్య GL_APIENTRY glMultiDrawElementsEXT (GLenum బహుళకం, స్థిరరాశి GLsizei *లెక్క, GLenum type, స్థిరరాశి శూన్య *స్థిరరాశి*indices, GLsizei primcount);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_multi_draw_arrays */

#నిర్వచితం_కాకపోతే GL_EXT_multisampled_render_గమ్యం_texture
#నిర్వచించు GL_EXT_multisampled_render_గమ్యం_texture 1
#నిర్వచించు GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SAMPLES_EXT 0x8D6C
#నిర్వచించు GL_RENDERBUFFER_SAMPLES_EXT       0x8CAB
#నిర్వచించు GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT 0x8D56
#నిర్వచించు GL_MAX_SAMPLES_EXT                0x8D57
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) (GLenum లక్ష్యం, GLsizei samples, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEEXTPROC) (GLenum లక్ష్యం, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_API శూన్య GL_APIENTRY glRenderbufferStorageMultisampleEXT (GLenum లక్ష్యం, GLsizei samples, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
GL_API శూన్య GL_APIENTRY glFramebufferTexture2DMultisampleEXT (GLenum లక్ష్యం, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_multisampled_render_to_texture */

#నిర్వచితం_కాకపోతే GL_EXT_read_format_bgra
#నిర్వచించు GL_EXT_read_format_bgra 1
#నిర్వచించు GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT 0x8365
#నిర్వచించు GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT 0x8366
#అయితే_ముగింపు /* GL_EXT_read_format_bgra */

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
GL_API GLenum GL_APIENTRY gl_Get_Graphics_Reset_స్థితి_EXT (శూన్య);
GL_API శూన్య GL_APIENTRY glReadnPixelsEXT (GLint x, GLint y, GLsizei వెడల్పు, GLsizei ఎత్తు, GLenum format, GLenum type, GLsizei buf_కొలత, శూన్య *దత్తాంశం);
GL_API శూన్య GL_APIENTRY glGetnUniformfvEXT (GLuint కార్యక్రమం, GLint location, GLsizei buf_కొలత, GLfloat *params);
GL_API శూన్య GL_APIENTRY glGetnUniformivEXT (GLuint కార్యక్రమం, GLint location, GLsizei buf_కొలత, GLint *params);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_robustness */

#నిర్వచితం_కాకపోతే GL_EXT_sRGB
#నిర్వచించు GL_EXT_sRGB 1
#నిర్వచించు GL_SRGB_EXT                       0x8C40
#నిర్వచించు GL_SRGB_ALPHA_EXT                 0x8C42
#నిర్వచించు GL_SRGB8_ALPHA8_EXT               0x8C43
#నిర్వచించు GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING_EXT 0x8210
#అయితే_ముగింపు /* GL_EXT_sRGB */

#నిర్వచితం_కాకపోతే GL_EXT_texture_compression_dxt1
#నిర్వచించు GL_EXT_texture_compression_dxt1 1
#నిర్వచించు GL_COMPRESSED_RGB_S3TC_DXT1_EXT   0x83F0
#నిర్వచించు GL_COMPRESSED_RGBA_S3TC_DXT1_EXT  0x83F1
#అయితే_ముగింపు /* GL_EXT_texture_compression_dxt1 */

#నిర్వచితం_కాకపోతే GL_EXT_texture_filter_anisotropic
#నిర్వచించు GL_EXT_texture_filter_anisotropic 1
#నిర్వచించు GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#నిర్వచించు GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#అయితే_ముగింపు /* GL_EXT_texture_filter_anisotropic */

#నిర్వచితం_కాకపోతే GL_EXT_texture_format_BGRA8888
#నిర్వచించు GL_EXT_texture_format_BGRA8888 1
#అయితే_ముగింపు /* GL_EXT_texture_format_BGRA8888 */

#నిర్వచితం_కాకపోతే GL_EXT_texture_lod_bias
#నిర్వచించు GL_EXT_texture_lod_bias 1
#నిర్వచించు GL_MAX_TEXTURE_LOD_BIAS_EXT       0x84FD
#నిర్వచించు GL_TEXTURE_FILTER_CONTROL_EXT     0x8500
#నిర్వచించు GL_TEXTURE_LOD_BIAS_EXT           0x8501
#అయితే_ముగింపు /* GL_EXT_texture_lod_bias */

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
#నిర్వచించు GL_RGBA16F_EXT                    0x881A
#నిర్వచించు GL_RGB16F_EXT                     0x881B
#నిర్వచించు GL_ALPHA16F_EXT                   0x881C
#నిర్వచించు GL_LUMINANCE16F_EXT               0x881E
#నిర్వచించు GL_LUMINANCE_ALPHA16F_EXT         0x881F
#నిర్వచించు GL_R8_EXT                         0x8229
#నిర్వచించు GL_RG8_EXT                        0x822B
#నిర్వచించు GL_R32F_EXT                       0x822E
#నిర్వచించు GL_RG32F_EXT                      0x8230
#నిర్వచించు GL_R16F_EXT                       0x822D
#నిర్వచించు GL_RG16F_EXT                      0x822F
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXSTORAGE1DEXTPROC) (GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum internalformat, GLsizei వెడల్పు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXSTORAGE2DEXTPROC) (GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXSTORAGE3DEXTPROC) (GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXTURESTORAGE1DEXTPROC) (GLuint texture, GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum internalformat, GLsizei వెడల్పు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXTURESTORAGE2DEXTPROC) (GLuint texture, GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXTURESTORAGE3DEXTPROC) (GLuint texture, GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_API శూన్య GL_APIENTRY glTexStorage1DEXT (GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum internalformat, GLsizei వెడల్పు);
GL_API శూన్య GL_APIENTRY glTexStorage2DEXT (GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
GL_API శూన్య GL_APIENTRY glTexStorage3DEXT (GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2);
GL_API శూన్య GL_APIENTRY glTextureStorage1DEXT (GLuint texture, GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum internalformat, GLsizei వెడల్పు);
GL_API శూన్య GL_APIENTRY glTextureStorage2DEXT (GLuint texture, GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
GL_API శూన్య GL_APIENTRY glTextureStorage3DEXT (GLuint texture, GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_EXT_texture_storage */

#నిర్వచితం_కాకపోతే GL_IMG_multisampled_render_గమ్యం_texture
#నిర్వచించు GL_IMG_multisampled_render_గమ్యం_texture 1
#నిర్వచించు GL_RENDERBUFFER_SAMPLES_IMG       0x9133
#నిర్వచించు GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_IMG 0x9134
#నిర్వచించు GL_MAX_SAMPLES_IMG                0x9135
#నిర్వచించు GL_TEXTURE_SAMPLES_IMG            0x9136
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEIMGPROC) (GLenum లక్ష్యం, GLsizei samples, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEIMGPROC) (GLenum లక్ష్యం, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_API శూన్య GL_APIENTRY glRenderbufferStorageMultisampleIMG (GLenum లక్ష్యం, GLsizei samples, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
GL_API శూన్య GL_APIENTRY glFramebufferTexture2DMultisampleIMG (GLenum లక్ష్యం, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_IMG_multisampled_render_to_texture */

#నిర్వచితం_కాకపోతే GL_IMG_read_format
#నిర్వచించు GL_IMG_read_format 1
#నిర్వచించు GL_BGRA_IMG                       0x80E1
#నిర్వచించు GL_UNSIGNED_SHORT_4_4_4_4_REV_IMG 0x8365
#అయితే_ముగింపు /* GL_IMG_read_format */

#నిర్వచితం_కాకపోతే GL_IMG_texture_compression_pvrtc
#నిర్వచించు GL_IMG_texture_compression_pvrtc 1
#నిర్వచించు GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG 0x8C00
#నిర్వచించు GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG 0x8C01
#నిర్వచించు GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG 0x8C02
#నిర్వచించు GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG 0x8C03
#అయితే_ముగింపు /* GL_IMG_texture_compression_pvrtc */

#నిర్వచితం_కాకపోతే GL_IMG_texture_env_enhanced_fixed_function
#నిర్వచించు GL_IMG_texture_env_enhanced_fixed_function 1
#నిర్వచించు GL_MODULATE_COLOR_IMG             0x8C04
#నిర్వచించు GL_RECIP_కూడు_SIGNED_ALPHA_IMG     0x8C05
#నిర్వచించు GL_TEXTURE_ALPHA_MODULATE_IMG     0x8C06
#నిర్వచించు GL_గుణకం_ALPHA_MODULATE_IMG      0x8C07
#నిర్వచించు GL_FRAGMENT_ALPHA_MODULATE_IMG    0x8C08
#నిర్వచించు GL_కూడు_BLEND_IMG                  0x8C09
#నిర్వచించు GL_DOT3_RGBA_IMG                  0x86AF
#అయితే_ముగింపు /* GL_IMG_texture_env_enhanced_fixed_function */

#నిర్వచితం_కాకపోతే GL_IMG_user_clip_plane
#నిర్వచించు GL_IMG_user_clip_plane 1
#నిర్వచించు GL_CLIP_PLANE0_IMG                0x3000
#నిర్వచించు GL_CLIP_PLANE1_IMG                0x3001
#నిర్వచించు GL_CLIP_PLANE2_IMG                0x3002
#నిర్వచించు GL_CLIP_PLANE3_IMG                0x3003
#నిర్వచించు GL_CLIP_PLANE4_IMG                0x3004
#నిర్వచించు GL_CLIP_PLANE5_IMG                0x3005
#నిర్వచించు GL_MAX_CLIP_PLANES_IMG            0x0D32
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCLIPPLANEFIMGPROC) (GLenum p, స్థిరరాశి GLfloat *eqn);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCLIPPLANEXIMGPROC) (GLenum p, స్థిరరాశి GLfixed *eqn);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_API శూన్య GL_APIENTRY glClipPlanefIMG (GLenum p, స్థిరరాశి GLfloat *eqn);
GL_API శూన్య GL_APIENTRY glClipPlanexIMG (GLenum p, స్థిరరాశి GLfixed *eqn);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_IMG_user_clip_plane */

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
GL_API శూన్య GL_APIENTRY glDeleteFencesNV (GLsizei n, స్థిరరాశి GLuint *fences);
GL_API శూన్య GL_APIENTRY glGenFencesNV (GLsizei n, GLuint *fences);
GL_API GLboolean GL_APIENTRY glIsFenceNV (GLuint fence);
GL_API GLboolean GL_APIENTRY glTestFenceNV (GLuint fence);
GL_API శూన్య GL_APIENTRY glGetFenceivNV (GLuint fence, GLenum pname, GLint *params);
GL_API శూన్య GL_APIENTRY gl_ముగింపు_Fence_NV (GLuint fence);
GL_API శూన్య GL_APIENTRY gl_సమితి_Fence_NV (GLuint fence, GLenum condition);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_NV_fence */

#నిర్వచితం_కాకపోతే GL_QCOM_driver_control
#నిర్వచించు GL_QCOM_driver_control 1
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETDRIVERCONTROLSQCOMPROC) (GLint *అంకె, GLsizei కొలత, GLuint *driverControls);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETDRIVERCONTROLSTRINGQCOMPROC) (GLuint driverControl, GLsizei buf_కొలత, GLsizei *నిడివి, GLchar *driverControlString);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLENABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDISABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_API శూన్య GL_APIENTRY glGetDriverControlsQCOM (GLint *అంకె, GLsizei కొలత, GLuint *driverControls);
GL_API శూన్య GL_APIENTRY glGetDriverControlStringQCOM (GLuint driverControl, GLsizei buf_కొలత, GLsizei *నిడివి, GLchar *driverControlString);
GL_API శూన్య GL_APIENTRY glEnableDriverControlQCOM (GLuint driverControl);
GL_API శూన్య GL_APIENTRY glDisableDriverControlQCOM (GLuint driverControl);
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
GL_API శూన్య GL_APIENTRY glExtGetTexturesQCOM (GLuint *textures, GLint maxTextures, GLint *అంకె_Textures);
GL_API శూన్య GL_APIENTRY glExtGetBuffersQCOM (GLuint *buffers, GLint maxBuffers, GLint *అంకె_Buffers);
GL_API శూన్య GL_APIENTRY glExtGetRenderbuffersQCOM (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *అంకె_Renderbuffers);
GL_API శూన్య GL_APIENTRY glExtGetFramebuffersQCOM (GLuint *framebuffers, GLint maxFramebuffers, GLint *అంకె_Framebuffers);
GL_API శూన్య GL_APIENTRY glExtGetTexLevelParameterivQCOM (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
GL_API శూన్య GL_APIENTRY glExtTexObjectStateOverrideiQCOM (GLenum లక్ష్యం, GLenum pname, GLint param);
GL_API శూన్య GL_APIENTRY glExtGetTexSubImageQCOM (GLenum లక్ష్యం, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLenum format, GLenum type, శూన్య *texels);
GL_API శూన్య GL_APIENTRY gl_Ext_Get_బఫరు_Pointerv_QCOM (GLenum లక్ష్యం, శూన్య **params);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_QCOM_extended_get */

#నిర్వచితం_కాకపోతే GL_QCOM_extended_get2
#నిర్వచించు GL_QCOM_extended_get2 1
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLEXTGETSHADERSQCOMPROC) (GLuint *shaders, GLint maxShaders, GLint *అంకె_Shaders);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLEXTGETPROGRAMSQCOMPROC) (GLuint *programs, GLint maxPrograms, GLint *అంకె_Programs);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLEXTISPROGRAMBINARYQCOMPROC) (GLuint కార్యక్రమం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLEXTGETPROGRAMBINARYSOURCEQCOMPROC) (GLuint కార్యక్రమం, GLenum shadertype, GLchar *ఆధారం, GLint *నిడివి);
#నిర్వచితమైతే GL_GLEXT_PROTOTYPES
GL_API శూన్య GL_APIENTRY glExtGetShadersQCOM (GLuint *shaders, GLint maxShaders, GLint *అంకె_Shaders);
GL_API శూన్య GL_APIENTRY glExtGetProgramsQCOM (GLuint *programs, GLint maxPrograms, GLint *అంకె_Programs);
GL_API GLboolean GL_APIENTRY gl_Ext_Is_కార్యక్రమం_ద్విమాన_QCOM (GLuint కార్యక్రమం);
GL_API శూన్య GL_APIENTRY gl_Ext_Get_కార్యక్రమం_ద్విమాన_ఆధారం_QCOM (GLuint కార్యక్రమం, GLenum shadertype, GLchar *ఆధారం, GLint *నిడివి);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_QCOM_extended_get2 */

#నిర్వచితం_కాకపోతే GL_QCOM_perfmon_global_బహుళకం
#నిర్వచించు GL_QCOM_perfmon_global_బహుళకం 1
#నిర్వచించు GL_PERFMON_GLOBAL_బహుళకం_QCOM       0x8FA0
#అయితే_ముగింపు /* GL_QCOM_perfmon_global_mode */

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
GL_API శూన్య GL_APIENTRY gl_ప్రారంభం_Tiling_QCOM (GLuint x, GLuint y, GLuint వెడల్పు, GLuint ఎత్తు, GLbitfield preserve_ముసుగు);
GL_API శూన్య GL_APIENTRY gl_చివర_Tiling_QCOM (GLbitfield preserve_ముసుగు);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_QCOM_tiled_rendering */

#నిర్వచితం_కాకపోతే GL_QCOM_writeonly_rendering
#నిర్వచించు GL_QCOM_writeonly_rendering 1
#నిర్వచించు GL_WRITEONLY_RENDERING_QCOM       0x8823
#అయితే_ముగింపు /* GL_QCOM_writeonly_rendering */

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు
