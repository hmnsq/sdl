#यदि_अपरिभाषितम् __gles1_glext_h_
#परिभाषय __gles1_glext_h_ 1

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

#यदि_अपरिभाषितम् GL_KHR_debug
#परिभाषय GL_KHR_debug 1
#यदि_अन्तः /* GL_KHR_debug */

#यदि_अपरिभाषितम् GL_OES_EGL_image
#परिभाषय GL_OES_EGL_image 1
प्रकारनिर्देश शून्य *GLeglImageOES;
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLEGLIMAGETARGETTEXTURE2DOESPROC) (GLenum target, GLeglImageOES image);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLEGLIMAGETARGETRENDERBUFFERSTORAGEOESPROC) (GLenum target, GLeglImageOES image);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_API शून्य GL_APIENTRY glEGLImageTargetTexture2DOES (GLenum target, GLeglImageOES image);
GL_API शून्य GL_APIENTRY glEGLImageTargetRenderbufferStorageOES (GLenum target, GLeglImageOES image);
#यदि_अन्तः
#यदि_अन्तः /* GL_OES_EGL_image */

#यदि_अपरिभाषितम् GL_OES_EGL_image_external
#परिभाषय GL_OES_EGL_image_external 1
#परिभाषय GL_TEXTURE_EXTERNAL_OES           0x8D65
#परिभाषय GL_TEXTURE_BINDING_EXTERNAL_OES   0x8D67
#परिभाषय GL_REQUIRED_TEXTURE_IMAGE_UNITS_OES 0x8D68
#यदि_अन्तः /* GL_OES_EGL_image_external */

#यदि_अपरिभाषितम् GL_OES_blend_equation_separate
#परिभाषय GL_OES_blend_equation_separate 1
#परिभाषय GL_BLEND_EQUATION_RGB_OES         0x8009
#परिभाषय GL_BLEND_EQUATION_ALPHA_OES       0x883D
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEOESPROC) (GLenum बहुलकम्_RGB, GLenum बहुलकम्_Alpha);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_API शून्य GL_APIENTRY glBlendEquationSeparateOES (GLenum बहुलकम्_RGB, GLenum बहुलकम्_Alpha);
#यदि_अन्तः
#यदि_अन्तः /* GL_OES_blend_equation_separate */

#यदि_अपरिभाषितम् GL_OES_blend_func_separate
#परिभाषय GL_OES_blend_func_separate 1
#परिभाषय GL_BLEND_DST_RGB_OES              0x80C8
#परिभाषय GL_BLEND_SRC_RGB_OES              0x80C9
#परिभाषय GL_BLEND_DST_ALPHA_OES            0x80CA
#परिभाषय GL_BLEND_SRC_ALPHA_OES            0x80CB
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEOESPROC) (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_API शून्य GL_APIENTRY glBlendFuncSeparateOES (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
#यदि_अन्तः
#यदि_अन्तः /* GL_OES_blend_func_separate */

#यदि_अपरिभाषितम् GL_OES_blend_व्यवकलय
#परिभाषय GL_OES_blend_व्यवकलय 1
#परिभाषय GL_BLEND_EQUATION_OES             0x8009
#परिभाषय GL_FUNC_सङ्कलय_OES                   0x8006
#परिभाषय GL_FUNC_व्यवकलय_OES              0x800A
#परिभाषय GL_FUNC_REVERSE_व्यवकलय_OES      0x800B
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBLENDEQUATIONOESPROC) (GLenum बहुलकम्);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_API शून्य GL_APIENTRY glBlendEquationOES (GLenum बहुलकम्);
#यदि_अन्तः
#यदि_अन्तः /* GL_OES_blend_subtract */

#यदि_अपरिभाषितम् GL_OES_byte_coordinates
#परिभाषय GL_OES_byte_coordinates 1
#यदि_अन्तः /* GL_OES_byte_coordinates */

#यदि_अपरिभाषितम् GL_OES_compressed_ETC1_RGB8_sub_texture
#परिभाषय GL_OES_compressed_ETC1_RGB8_sub_texture 1
#यदि_अन्तः /* GL_OES_compressed_ETC1_RGB8_sub_texture */

#यदि_अपरिभाषितम् GL_OES_compressed_ETC1_RGB8_texture
#परिभाषय GL_OES_compressed_ETC1_RGB8_texture 1
#परिभाषय GL_ETC1_RGB8_OES                  0x8D64
#यदि_अन्तः /* GL_OES_compressed_ETC1_RGB8_texture */

#यदि_अपरिभाषितम् GL_OES_depth24
#परिभाषय GL_OES_depth24 1
#परिभाषय GL_गभीरता_COMPONENT24_OES          0x81A6
#यदि_अन्तः /* GL_OES_depth24 */

#यदि_अपरिभाषितम् GL_OES_depth32
#परिभाषय GL_OES_depth32 1
#परिभाषय GL_गभीरता_COMPONENT32_OES          0x81A7
#यदि_अन्तः /* GL_OES_depth32 */

#यदि_अपरिभाषितम् GL_OES_draw_texture
#परिभाषय GL_OES_draw_texture 1
#परिभाषय GL_TEXTURE_CROP_RECT_OES          0x8B9D
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWTEXSOESPROC) (GLshort x, GLshort y, GLshort z, GLshort विस्तारः, GLshort height);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWTEXIOESPROC) (GLint x, GLint y, GLint z, GLint विस्तारः, GLint height);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWTEXXOESPROC) (GLfixed x, GLfixed y, GLfixed z, GLfixed विस्तारः, GLfixed height);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWTEXSVOESPROC) (ध्रुव GLshort *coords);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWTEXIVOESPROC) (ध्रुव GLint *coords);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWTEXXVOESPROC) (ध्रुव GLfixed *coords);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWTEXFOESPROC) (GLfloat x, GLfloat y, GLfloat z, GLfloat विस्तारः, GLfloat height);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWTEXFVOESPROC) (ध्रुव GLfloat *coords);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_API शून्य GL_APIENTRY glDrawTexsOES (GLshort x, GLshort y, GLshort z, GLshort विस्तारः, GLshort height);
GL_API शून्य GL_APIENTRY glDrawTexiOES (GLint x, GLint y, GLint z, GLint विस्तारः, GLint height);
GL_API शून्य GL_APIENTRY glDrawTexxOES (GLfixed x, GLfixed y, GLfixed z, GLfixed विस्तारः, GLfixed height);
GL_API शून्य GL_APIENTRY glDrawTexsvOES (ध्रुव GLshort *coords);
GL_API शून्य GL_APIENTRY glDrawTexivOES (ध्रुव GLint *coords);
GL_API शून्य GL_APIENTRY glDrawTexxvOES (ध्रुव GLfixed *coords);
GL_API शून्य GL_APIENTRY glDrawTexfOES (GLfloat x, GLfloat y, GLfloat z, GLfloat विस्तारः, GLfloat height);
GL_API शून्य GL_APIENTRY glDrawTexfvOES (ध्रुव GLfloat *coords);
#यदि_अन्तः
#यदि_अन्तः /* GL_OES_draw_texture */

#यदि_अपरिभाषितम् GL_OES_element_सूचकांक_uint
#परिभाषय GL_OES_element_सूचकांक_uint 1
#परिभाषय GL_UNSIGNED_INT                   0x1405
#यदि_अन्तः /* GL_OES_element_index_uint */

#यदि_अपरिभाषितम् GL_OES_extended_matrix_palette
#परिभाषय GL_OES_extended_matrix_palette 1
#यदि_अन्तः /* GL_OES_extended_matrix_palette */

#यदि_अपरिभाषितम् GL_OES_fbo_render_mipmap
#परिभाषय GL_OES_fbo_render_mipmap 1
#यदि_अन्तः /* GL_OES_fbo_render_mipmap */

#यदि_अपरिभाषितम् GL_OES_fixed_point
#परिभाषय GL_OES_fixed_point 1
#परिभाषय GL_FIXED_OES                      0x140C
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLALPHAFUNCXOESPROC) (GLenum func, GLfixed ref);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCLEARCOLORXOESPROC) (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCLEARDEPTHXOESPROC) (GLfixed गभीरता_2);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCLIPPLANEXOESPROC) (GLenum plane, ध्रुव GLfixed *equation);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCOLOR4XOESPROC) (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDEPTHRANGEXOESPROC) (GLfixed n, GLfixed f);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFOGXOESPROC) (GLenum pname, GLfixed param);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFOGXVOESPROC) (GLenum pname, ध्रुव GLfixed *param);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFRUSTUMXOESPROC) (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETCLIPPLANEXOESPROC) (GLenum plane, GLfixed *equation);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETFIXEDVOESPROC) (GLenum pname, GLfixed *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETTEXENVXVOESPROC) (GLenum target, GLenum pname, GLfixed *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETTEXPARAMETERXVOESPROC) (GLenum target, GLenum pname, GLfixed *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLLIGHTMODELXOESPROC) (GLenum pname, GLfixed param);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLLIGHTMODELXVOESPROC) (GLenum pname, ध्रुव GLfixed *param);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLLIGHTXOESPROC) (GLenum light, GLenum pname, GLfixed param);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLLIGHTXVOESPROC) (GLenum light, GLenum pname, ध्रुव GLfixed *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLLINEWIDTHXOESPROC) (GLfixed विस्तारः);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLLOADMATRIXXOESPROC) (ध्रुव GLfixed *m);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMATERIALXOESPROC) (GLenum face, GLenum pname, GLfixed param);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMATERIALXVOESPROC) (GLenum face, GLenum pname, ध्रुव GLfixed *param);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMULTMATRIXXOESPROC) (ध्रुव GLfixed *m);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMULTITEXCOORD4XOESPROC) (GLenum texture, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLNORMAL3XOESPROC) (GLfixed nx, GLfixed ny, GLfixed nz);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLORTHOXOESPROC) (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPOINTPARAMETERXVOESPROC) (GLenum pname, ध्रुव GLfixed *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPOINTSIZEXOESPROC) (GLfixed आकार);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPOLYGONOFFSETXOESPROC) (GLfixed गुणकः, GLfixed units);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLROTATEXOESPROC) (GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSCALEXOESPROC) (GLfixed x, GLfixed y, GLfixed z);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXENVXOESPROC) (GLenum target, GLenum pname, GLfixed param);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXENVXVOESPROC) (GLenum target, GLenum pname, ध्रुव GLfixed *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXPARAMETERXOESPROC) (GLenum target, GLenum pname, GLfixed param);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXPARAMETERXVOESPROC) (GLenum target, GLenum pname, ध्रुव GLfixed *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTRANSLATEXOESPROC) (GLfixed x, GLfixed y, GLfixed z);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETLIGHTXVOESPROC) (GLenum light, GLenum pname, GLfixed *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETMATERIALXVOESPROC) (GLenum face, GLenum pname, GLfixed *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPOINTPARAMETERXOESPROC) (GLenum pname, GLfixed param);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSAMPLECOVERAGEXOESPROC) (GLclampx मानम्, GLboolean invert);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETTEXGENXVOESPROC) (GLenum coord, GLenum pname, GLfixed *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXGENXOESPROC) (GLenum coord, GLenum pname, GLfixed param);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXGENXVOESPROC) (GLenum coord, GLenum pname, ध्रुव GLfixed *params);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_API शून्य GL_APIENTRY glAlphaFuncxOES (GLenum func, GLfixed ref);
GL_API शून्य GL_APIENTRY glClearColorxOES (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GL_API शून्य GL_APIENTRY glClearDepthxOES (GLfixed गभीरता_2);
GL_API शून्य GL_APIENTRY glClipPlanexOES (GLenum plane, ध्रुव GLfixed *equation);
GL_API शून्य GL_APIENTRY glColor4xOES (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GL_API शून्य GL_APIENTRY gl_गभीरता_Rangex_OES (GLfixed n, GLfixed f);
GL_API शून्य GL_APIENTRY glFogxOES (GLenum pname, GLfixed param);
GL_API शून्य GL_APIENTRY glFogxvOES (GLenum pname, ध्रुव GLfixed *param);
GL_API शून्य GL_APIENTRY glFrustumxOES (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
GL_API शून्य GL_APIENTRY glGetClipPlanexOES (GLenum plane, GLfixed *equation);
GL_API शून्य GL_APIENTRY glGetFixedvOES (GLenum pname, GLfixed *params);
GL_API शून्य GL_APIENTRY glGetTexEnvxvOES (GLenum target, GLenum pname, GLfixed *params);
GL_API शून्य GL_APIENTRY glGetTexParameterxvOES (GLenum target, GLenum pname, GLfixed *params);
GL_API शून्य GL_APIENTRY glLightModelxOES (GLenum pname, GLfixed param);
GL_API शून्य GL_APIENTRY glLightModelxvOES (GLenum pname, ध्रुव GLfixed *param);
GL_API शून्य GL_APIENTRY glLightxOES (GLenum light, GLenum pname, GLfixed param);
GL_API शून्य GL_APIENTRY glLightxvOES (GLenum light, GLenum pname, ध्रुव GLfixed *params);
GL_API शून्य GL_APIENTRY gl_पङ्क्तिः_Widthx_OES (GLfixed विस्तारः);
GL_API शून्य GL_APIENTRY gl_आरोपय_Matrixx_OES (ध्रुव GLfixed *m);
GL_API शून्य GL_APIENTRY glMaterialxOES (GLenum face, GLenum pname, GLfixed param);
GL_API शून्य GL_APIENTRY glMaterialxvOES (GLenum face, GLenum pname, ध्रुव GLfixed *param);
GL_API शून्य GL_APIENTRY glMultMatrixxOES (ध्रुव GLfixed *m);
GL_API शून्य GL_APIENTRY glMultiTexCoord4xOES (GLenum texture, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
GL_API शून्य GL_APIENTRY glNormal3xOES (GLfixed nx, GLfixed ny, GLfixed nz);
GL_API शून्य GL_APIENTRY glOrthoxOES (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
GL_API शून्य GL_APIENTRY glPointParameterxvOES (GLenum pname, ध्रुव GLfixed *params);
GL_API शून्य GL_APIENTRY glPointSizexOES (GLfixed आकार);
GL_API शून्य GL_APIENTRY glPolygonOffsetxOES (GLfixed गुणकः, GLfixed units);
GL_API शून्य GL_APIENTRY glRotatexOES (GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
GL_API शून्य GL_APIENTRY glScalexOES (GLfixed x, GLfixed y, GLfixed z);
GL_API शून्य GL_APIENTRY glTexEnvxOES (GLenum target, GLenum pname, GLfixed param);
GL_API शून्य GL_APIENTRY glTexEnvxvOES (GLenum target, GLenum pname, ध्रुव GLfixed *params);
GL_API शून्य GL_APIENTRY glTexParameterxOES (GLenum target, GLenum pname, GLfixed param);
GL_API शून्य GL_APIENTRY glTexParameterxvOES (GLenum target, GLenum pname, ध्रुव GLfixed *params);
GL_API शून्य GL_APIENTRY glTranslatexOES (GLfixed x, GLfixed y, GLfixed z);
GL_API शून्य GL_APIENTRY glGetLightxvOES (GLenum light, GLenum pname, GLfixed *params);
GL_API शून्य GL_APIENTRY glGetMaterialxvOES (GLenum face, GLenum pname, GLfixed *params);
GL_API शून्य GL_APIENTRY glPointParameterxOES (GLenum pname, GLfixed param);
GL_API शून्य GL_APIENTRY glSampleCoveragexOES (GLclampx मानम्, GLboolean invert);
GL_API शून्य GL_APIENTRY glGetTexGenxvOES (GLenum coord, GLenum pname, GLfixed *params);
GL_API शून्य GL_APIENTRY glTexGenxOES (GLenum coord, GLenum pname, GLfixed param);
GL_API शून्य GL_APIENTRY glTexGenxvOES (GLenum coord, GLenum pname, ध्रुव GLfixed *params);
#यदि_अन्तः
#यदि_अन्तः /* GL_OES_fixed_point */

#यदि_अपरिभाषितम् GL_OES_framebuffer_object
#परिभाषय GL_OES_framebuffer_object 1
#परिभाषय GL_NONE_OES                       0
#परिभाषय GL_FRAMEBUFFER_OES                0x8D40
#परिभाषय GL_RENDERBUFFER_OES               0x8D41
#परिभाषय GL_RGBA4_OES                      0x8056
#परिभाषय GL_RGB5_A1_OES                    0x8057
#परिभाषय GL_RGB565_OES                     0x8D62
#परिभाषय GL_गभीरता_COMPONENT16_OES          0x81A5
#परिभाषय GL_RENDERBUFFER_विस्तारः_OES         0x8D42
#परिभाषय GL_RENDERBUFFER_HEIGHT_OES        0x8D43
#परिभाषय GL_RENDERBUFFER_आन्तरिकम्_FORMAT_OES 0x8D44
#परिभाषय GL_RENDERBUFFER_RED_आकार_OES      0x8D50
#परिभाषय GL_RENDERBUFFER_GREEN_आकार_OES    0x8D51
#परिभाषय GL_RENDERBUFFER_BLUE_आकार_OES     0x8D52
#परिभाषय GL_RENDERBUFFER_ALPHA_आकार_OES    0x8D53
#परिभाषय GL_RENDERBUFFER_गभीरता_आकार_OES    0x8D54
#परिभाषय GL_RENDERBUFFER_STENCIL_आकार_OES  0x8D55
#परिभाषय GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_OES 0x8CD0
#परिभाषय GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_OES 0x8CD1
#परिभाषय GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_OES 0x8CD2
#परिभाषय GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_OES 0x8CD3
#परिभाषय GL_COLOR_ATTACHMENT0_OES          0x8CE0
#परिभाषय GL_गभीरता_ATTACHMENT_OES           0x8D00
#परिभाषय GL_STENCIL_ATTACHMENT_OES         0x8D20
#परिभाषय GL_FRAMEBUFFER_COMPLETE_OES       0x8CD5
#परिभाषय GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_OES 0x8CD6
#परिभाषय GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_OES 0x8CD7
#परिभाषय GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_OES 0x8CD9
#परिभाषय GL_FRAMEBUFFER_INCOMPLETE_FORMATS_OES 0x8CDA
#परिभाषय GL_FRAMEBUFFER_UNSUPPORTED_OES    0x8CDD
#परिभाषय GL_FRAMEBUFFER_BINDING_OES        0x8CA6
#परिभाषय GL_RENDERBUFFER_BINDING_OES       0x8CA7
#परिभाषय GL_MAX_RENDERBUFFER_आकार_OES      0x84E8
#परिभाषय GL_INVALID_FRAMEBUFFER_OPERATION_OES 0x0506
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLISRENDERBUFFEROESPROC) (GLuint renderbuffer);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBINDRENDERBUFFEROESPROC) (GLenum target, GLuint renderbuffer);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDELETERENDERBUFFERSOESPROC) (GLsizei n, ध्रुव GLuint *renderbuffers);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGENRENDERBUFFERSOESPROC) (GLsizei n, GLuint *renderbuffers);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEOESPROC) (GLenum target, GLenum internalformat, GLsizei विस्तारः, GLsizei height);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVOESPROC) (GLenum target, GLenum pname, GLint *params);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLISFRAMEBUFFEROESPROC) (GLuint framebuffer);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBINDFRAMEBUFFEROESPROC) (GLenum target, GLuint framebuffer);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDELETEFRAMEBUFFERSOESPROC) (GLsizei n, ध्रुव GLuint *framebuffers);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGENFRAMEBUFFERSOESPROC) (GLsizei n, GLuint *framebuffers);
प्रकारनिर्देश GLenum (GL_APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSOESPROC) (GLenum target);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFEROESPROC) (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DOESPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVOESPROC) (GLenum target, GLenum attachment, GLenum pname, GLint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGENERATEMIPMAPOESPROC) (GLenum target);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_API GLboolean GL_APIENTRY glIsRenderbufferOES (GLuint renderbuffer);
GL_API शून्य GL_APIENTRY glBindRenderbufferOES (GLenum target, GLuint renderbuffer);
GL_API शून्य GL_APIENTRY glDeleteRenderbuffersOES (GLsizei n, ध्रुव GLuint *renderbuffers);
GL_API शून्य GL_APIENTRY glGenRenderbuffersOES (GLsizei n, GLuint *renderbuffers);
GL_API शून्य GL_APIENTRY glRenderbufferStorageOES (GLenum target, GLenum internalformat, GLsizei विस्तारः, GLsizei height);
GL_API शून्य GL_APIENTRY glGetRenderbufferParameterivOES (GLenum target, GLenum pname, GLint *params);
GL_API GLboolean GL_APIENTRY glIsFramebufferOES (GLuint framebuffer);
GL_API शून्य GL_APIENTRY glBindFramebufferOES (GLenum target, GLuint framebuffer);
GL_API शून्य GL_APIENTRY glDeleteFramebuffersOES (GLsizei n, ध्रुव GLuint *framebuffers);
GL_API शून्य GL_APIENTRY glGenFramebuffersOES (GLsizei n, GLuint *framebuffers);
GL_API GLenum GL_APIENTRY gl_Check_Framebuffer_स्थितिः_OES (GLenum target);
GL_API शून्य GL_APIENTRY glFramebufferRenderbufferOES (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
GL_API शून्य GL_APIENTRY glFramebufferTexture2DOES (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GL_API शून्य GL_APIENTRY glGetFramebufferAttachmentParameterivOES (GLenum target, GLenum attachment, GLenum pname, GLint *params);
GL_API शून्य GL_APIENTRY glGenerateMipmapOES (GLenum target);
#यदि_अन्तः
#यदि_अन्तः /* GL_OES_framebuffer_object */

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
GL_API शून्य *GL_APIENTRY gl_Map_बफर_OES (GLenum target, GLenum access);
GL_API GLboolean GL_APIENTRY gl_Unmap_बफर_OES (GLenum target);
GL_API शून्य GL_APIENTRY gl_Get_बफर_Pointerv_OES (GLenum target, GLenum pname, शून्य **params);
#यदि_अन्तः
#यदि_अन्तः /* GL_OES_mapbuffer */

#यदि_अपरिभाषितम् GL_OES_matrix_get
#परिभाषय GL_OES_matrix_get 1
#परिभाषय GL_MODELVIEW_MATRIX_FLOAT_AS_INT_द्वयङ्काः_OES 0x898D
#परिभाषय GL_PROJECTION_MATRIX_FLOAT_AS_INT_द्वयङ्काः_OES 0x898E
#परिभाषय GL_TEXTURE_MATRIX_FLOAT_AS_INT_द्वयङ्काः_OES 0x898F
#यदि_अन्तः /* GL_OES_matrix_get */

#यदि_अपरिभाषितम् GL_OES_matrix_palette
#परिभाषय GL_OES_matrix_palette 1
#परिभाषय GL_MAX_VERTEX_UNITS_OES           0x86A4
#परिभाषय GL_MAX_PALETTE_MATRICES_OES       0x8842
#परिभाषय GL_MATRIX_PALETTE_OES             0x8840
#परिभाषय GL_MATRIX_सूचकांक_ARRAY_OES         0x8844
#परिभाषय GL_WEIGHT_ARRAY_OES               0x86AD
#परिभाषय GL_CURRENT_PALETTE_MATRIX_OES     0x8843
#परिभाषय GL_MATRIX_सूचकांक_ARRAY_आकार_OES    0x8846
#परिभाषय GL_MATRIX_सूचकांक_ARRAY_TYPE_OES    0x8847
#परिभाषय GL_MATRIX_सूचकांक_ARRAY_STRIDE_OES  0x8848
#परिभाषय GL_MATRIX_सूचकांक_ARRAY_POINTER_OES 0x8849
#परिभाषय GL_MATRIX_सूचकांक_ARRAY_बफर_BINDING_OES 0x8B9E
#परिभाषय GL_WEIGHT_ARRAY_आकार_OES          0x86AB
#परिभाषय GL_WEIGHT_ARRAY_TYPE_OES          0x86A9
#परिभाषय GL_WEIGHT_ARRAY_STRIDE_OES        0x86AA
#परिभाषय GL_WEIGHT_ARRAY_POINTER_OES       0x86AC
#परिभाषय GL_WEIGHT_ARRAY_बफर_BINDING_OES 0x889E
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCURRENTPALETTEMATRIXOESPROC) (GLuint matrixpaletteindex);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLLOADPALETTEFROMMODELVIEWMATRIXOESPROC) (शून्य);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMATRIXINDEXPOINTEROESPROC) (GLint आकार, GLenum type, GLsizei stride, ध्रुव शून्य *pointer);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLWEIGHTPOINTEROESPROC) (GLint आकार, GLenum type, GLsizei stride, ध्रुव शून्य *pointer);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_API शून्य GL_APIENTRY glCurrentPaletteMatrixOES (GLuint matrixpaletteindex);
GL_API शून्य GL_APIENTRY gl_आरोपय_Palette_From_Model_View_Matrix_OES (शून्य);
GL_API शून्य GL_APIENTRY gl_Matrix_सूचकांक_Pointer_OES (GLint आकार, GLenum type, GLsizei stride, ध्रुव शून्य *pointer);
GL_API शून्य GL_APIENTRY glWeightPointerOES (GLint आकार, GLenum type, GLsizei stride, ध्रुव शून्य *pointer);
#यदि_अन्तः
#यदि_अन्तः /* GL_OES_matrix_palette */

#यदि_अपरिभाषितम् GL_OES_packed_गभीरता_stencil
#परिभाषय GL_OES_packed_गभीरता_stencil 1
#परिभाषय GL_गभीरता_STENCIL_OES              0x84F9
#परिभाषय GL_UNSIGNED_INT_24_8_OES          0x84FA
#परिभाषय GL_DEPTH24_STENCIL8_OES           0x88F0
#यदि_अन्तः /* GL_OES_packed_depth_stencil */

#यदि_अपरिभाषितम् GL_OES_query_matrix
#परिभाषय GL_OES_query_matrix 1
प्रकारनिर्देश GLbitfield (GL_APIENTRYP PFNGLQUERYMATRIXXOESPROC) (GLfixed *mantissa, GLint *exponent);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_API GLbitfield GL_APIENTRY glQueryMatrixxOES (GLfixed *mantissa, GLint *exponent);
#यदि_अन्तः
#यदि_अन्तः /* GL_OES_query_matrix */

#यदि_अपरिभाषितम् GL_OES_required_internalformat
#परिभाषय GL_OES_required_internalformat 1
#परिभाषय GL_ALPHA8_OES                     0x803C
#परिभाषय GL_LUMINANCE4_ALPHA4_OES          0x8043
#परिभाषय GL_LUMINANCE8_ALPHA8_OES          0x8045
#परिभाषय GL_LUMINANCE8_OES                 0x8040
#परिभाषय GL_RGB8_OES                       0x8051
#परिभाषय GL_RGBA8_OES                      0x8058
#परिभाषय GL_RGB10_EXT                      0x8052
#परिभाषय GL_RGB10_A2_EXT                   0x8059
#यदि_अन्तः /* GL_OES_required_internalformat */

#यदि_अपरिभाषितम् GL_OES_rgb8_rgba8
#परिभाषय GL_OES_rgb8_rgba8 1
#यदि_अन्तः /* GL_OES_rgb8_rgba8 */

#यदि_अपरिभाषितम् GL_OES_single_precision
#परिभाषय GL_OES_single_precision 1
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCLEARDEPTHFOESPROC) (GLclampf गभीरता_2);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCLIPPLANEFOESPROC) (GLenum plane, ध्रुव GLfloat *equation);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDEPTHRANGEFOESPROC) (GLclampf n, GLclampf f);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFRUSTUMFOESPROC) (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETCLIPPLANEFOESPROC) (GLenum plane, GLfloat *equation);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLORTHOFOESPROC) (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_API शून्य GL_APIENTRY glClearDepthfOES (GLclampf गभीरता_2);
GL_API शून्य GL_APIENTRY glClipPlanefOES (GLenum plane, ध्रुव GLfloat *equation);
GL_API शून्य GL_APIENTRY gl_गभीरता_Rangef_OES (GLclampf n, GLclampf f);
GL_API शून्य GL_APIENTRY glFrustumfOES (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
GL_API शून्य GL_APIENTRY glGetClipPlanefOES (GLenum plane, GLfloat *equation);
GL_API शून्य GL_APIENTRY glOrthofOES (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
#यदि_अन्तः
#यदि_अन्तः /* GL_OES_single_precision */

#यदि_अपरिभाषितम् GL_OES_stencil1
#परिभाषय GL_OES_stencil1 1
#परिभाषय GL_STENCIL_INDEX1_OES             0x8D46
#यदि_अन्तः /* GL_OES_stencil1 */

#यदि_अपरिभाषितम् GL_OES_stencil4
#परिभाषय GL_OES_stencil4 1
#परिभाषय GL_STENCIL_INDEX4_OES             0x8D47
#यदि_अन्तः /* GL_OES_stencil4 */

#यदि_अपरिभाषितम् GL_OES_stencil8
#परिभाषय GL_OES_stencil8 1
#परिभाषय GL_STENCIL_INDEX8_OES             0x8D48
#यदि_अन्तः /* GL_OES_stencil8 */

#यदि_अपरिभाषितम् GL_OES_stencil_wrap
#परिभाषय GL_OES_stencil_wrap 1
#परिभाषय GL_INCR_WRAP_OES                  0x8507
#परिभाषय GL_DECR_WRAP_OES                  0x8508
#यदि_अन्तः /* GL_OES_stencil_wrap */

#यदि_अपरिभाषितम् GL_OES_surfaceless_context
#परिभाषय GL_OES_surfaceless_context 1
#परिभाषय GL_FRAMEBUFFER_UNDEFINED_OES      0x8219
#यदि_अन्तः /* GL_OES_surfaceless_context */

#यदि_अपरिभाषितम् GL_OES_texture_cube_map
#परिभाषय GL_OES_texture_cube_map 1
#परिभाषय GL_प्रसामान्यम्_MAP_OES                 0x8511
#परिभाषय GL_REFLECTION_MAP_OES             0x8512
#परिभाषय GL_TEXTURE_CUBE_MAP_OES           0x8513
#परिभाषय GL_TEXTURE_BINDING_CUBE_MAP_OES   0x8514
#परिभाषय GL_TEXTURE_CUBE_MAP_धनात्मकम्_X_OES 0x8515
#परिभाषय GL_TEXTURE_CUBE_MAP_NEGATIVE_X_OES 0x8516
#परिभाषय GL_TEXTURE_CUBE_MAP_धनात्मकम्_Y_OES 0x8517
#परिभाषय GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_OES 0x8518
#परिभाषय GL_TEXTURE_CUBE_MAP_धनात्मकम्_Z_OES 0x8519
#परिभाषय GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_OES 0x851A
#परिभाषय GL_MAX_CUBE_MAP_TEXTURE_आकार_OES  0x851C
#परिभाषय GL_TEXTURE_GEN_बहुलकम्_OES           0x2500
#परिभाषय GL_TEXTURE_GEN_STR_OES            0x8D60
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXGENFOESPROC) (GLenum coord, GLenum pname, GLfloat param);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXGENFVOESPROC) (GLenum coord, GLenum pname, ध्रुव GLfloat *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXGENIOESPROC) (GLenum coord, GLenum pname, GLint param);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXGENIVOESPROC) (GLenum coord, GLenum pname, ध्रुव GLint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETTEXGENFVOESPROC) (GLenum coord, GLenum pname, GLfloat *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETTEXGENIVOESPROC) (GLenum coord, GLenum pname, GLint *params);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_API शून्य GL_APIENTRY glTexGenfOES (GLenum coord, GLenum pname, GLfloat param);
GL_API शून्य GL_APIENTRY glTexGenfvOES (GLenum coord, GLenum pname, ध्रुव GLfloat *params);
GL_API शून्य GL_APIENTRY glTexGeniOES (GLenum coord, GLenum pname, GLint param);
GL_API शून्य GL_APIENTRY glTexGenivOES (GLenum coord, GLenum pname, ध्रुव GLint *params);
GL_API शून्य GL_APIENTRY glGetTexGenfvOES (GLenum coord, GLenum pname, GLfloat *params);
GL_API शून्य GL_APIENTRY glGetTexGenivOES (GLenum coord, GLenum pname, GLint *params);
#यदि_अन्तः
#यदि_अन्तः /* GL_OES_texture_cube_map */

#यदि_अपरिभाषितम् GL_OES_texture_env_crossbar
#परिभाषय GL_OES_texture_env_crossbar 1
#यदि_अन्तः /* GL_OES_texture_env_crossbar */

#यदि_अपरिभाषितम् GL_OES_texture_mirrored_repeat
#परिभाषय GL_OES_texture_mirrored_repeat 1
#परिभाषय GL_MIRRORED_REPEAT_OES            0x8370
#यदि_अन्तः /* GL_OES_texture_mirrored_repeat */

#यदि_अपरिभाषितम् GL_OES_texture_npot
#परिभाषय GL_OES_texture_npot 1
#यदि_अन्तः /* GL_OES_texture_npot */

#यदि_अपरिभाषितम् GL_OES_vertex_array_object
#परिभाषय GL_OES_vertex_array_object 1
#परिभाषय GL_VERTEX_ARRAY_BINDING_OES       0x85B5
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBINDVERTEXARRAYOESPROC) (GLuint array);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDELETEVERTEXARRAYSOESPROC) (GLsizei n, ध्रुव GLuint *arrays);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGENVERTEXARRAYSOESPROC) (GLsizei n, GLuint *arrays);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLISVERTEXARRAYOESPROC) (GLuint array);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_API शून्य GL_APIENTRY glBindVertexArrayOES (GLuint array);
GL_API शून्य GL_APIENTRY glDeleteVertexArraysOES (GLsizei n, ध्रुव GLuint *arrays);
GL_API शून्य GL_APIENTRY glGenVertexArraysOES (GLsizei n, GLuint *arrays);
GL_API GLboolean GL_APIENTRY glIsVertexArrayOES (GLuint array);
#यदि_अन्तः
#यदि_अन्तः /* GL_OES_vertex_array_object */

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

#यदि_अपरिभाषितम् GL_APPLE_copy_texture_स्तराः
#परिभाषय GL_APPLE_copy_texture_स्तराः 1
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCOPYTEXTURELEVELSAPPLEPROC) (GLuint destinationTexture, GLuint sourceTexture, GLint source_आधारः_Level, GLsizei source_Level_गणनम्);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_API शून्य GL_APIENTRY gl_Copy_Texture_स्तराः_APPLE (GLuint destinationTexture, GLuint sourceTexture, GLint source_आधारः_Level, GLsizei source_Level_गणनम्);
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
GL_API शून्य GL_APIENTRY glRenderbufferStorageMultisampleAPPLE (GLenum target, GLsizei samples, GLenum internalformat, GLsizei विस्तारः, GLsizei height);
GL_API शून्य GL_APIENTRY glResolveMultisampleFramebufferAPPLE (शून्य);
#यदि_अन्तः
#यदि_अन्तः /* GL_APPLE_framebuffer_multisample */

#यदि_अपरिभाषितम् GL_APPLE_sync
#परिभाषय GL_APPLE_sync 1
प्रकारनिर्देश संरचना __GLsync *GLsync;
प्रकारनिर्देश khronos_uint64_t GLuint64;
प्रकारनिर्देश khronos_int64_t GLint64;
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
GL_API GLsync GL_APIENTRY glFenceSyncAPPLE (GLenum condition, GLbitfield flags);
GL_API GLboolean GL_APIENTRY glIsSyncAPPLE (GLsync sync);
GL_API शून्य GL_APIENTRY glDeleteSyncAPPLE (GLsync sync);
GL_API GLenum GL_APIENTRY glClientWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_API शून्य GL_APIENTRY glWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_API शून्य GL_APIENTRY glGetInteger64vAPPLE (GLenum pname, GLint64 *params);
GL_API शून्य GL_APIENTRY glGetSyncivAPPLE (GLsync sync, GLenum pname, GLsizei गणनम्, GLsizei *दीर्घता, GLint *मानानि);
#यदि_अन्तः
#यदि_अन्तः /* GL_APPLE_sync */

#यदि_अपरिभाषितम् GL_APPLE_texture_2D_limited_npot
#परिभाषय GL_APPLE_texture_2D_limited_npot 1
#यदि_अन्तः /* GL_APPLE_texture_2D_limited_npot */

#यदि_अपरिभाषितम् GL_APPLE_texture_format_BGRA8888
#परिभाषय GL_APPLE_texture_format_BGRA8888 1
#परिभाषय GL_BGRA_EXT                       0x80E1
#परिभाषय GL_BGRA8_EXT                      0x93A1
#यदि_अन्तः /* GL_APPLE_texture_format_BGRA8888 */

#यदि_अपरिभाषितम् GL_APPLE_texture_max_level
#परिभाषय GL_APPLE_texture_max_level 1
#परिभाषय GL_TEXTURE_MAX_LEVEL_APPLE        0x813D
#यदि_अन्तः /* GL_APPLE_texture_max_level */

#यदि_अपरिभाषितम् GL_ARM_rgba8
#परिभाषय GL_ARM_rgba8 1
#यदि_अन्तः /* GL_ARM_rgba8 */

#यदि_अपरिभाषितम् GL_EXT_blend_minmax
#परिभाषय GL_EXT_blend_minmax 1
#परिभाषय GL_MIN_EXT                        0x8007
#परिभाषय GL_MAX_EXT                        0x8008
#यदि_अन्तः /* GL_EXT_blend_minmax */

#यदि_अपरिभाषितम् GL_EXT_debug_marker
#परिभाषय GL_EXT_debug_marker 1
प्रकारनिर्देश वर्ण GLchar;
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLINSERTEVENTMARKEREXTPROC) (GLsizei दीर्घता, ध्रुव GLchar *marker);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPUSHGROUPMARKEREXTPROC) (GLsizei दीर्घता, ध्रुव GLchar *marker);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPOPGROUPMARKEREXTPROC) (शून्य);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_API शून्य GL_APIENTRY gl_निवेशय_Event_Marker_EXT (GLsizei दीर्घता, ध्रुव GLchar *marker);
GL_API शून्य GL_APIENTRY gl_प्रक्षिप_गणः_Marker_EXT (GLsizei दीर्घता, ध्रुव GLchar *marker);
GL_API शून्य GL_APIENTRY gl_निष्कासय_गणः_Marker_EXT (शून्य);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_debug_marker */

#यदि_अपरिभाषितम् GL_EXT_discard_framebuffer
#परिभाषय GL_EXT_discard_framebuffer 1
#परिभाषय GL_COLOR_EXT                      0x1800
#परिभाषय GL_गभीरता_EXT                      0x1801
#परिभाषय GL_STENCIL_EXT                    0x1802
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDISCARDFRAMEBUFFEREXTPROC) (GLenum target, GLsizei अङ्कः_Attachments, ध्रुव GLenum *attachments);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_API शून्य GL_APIENTRY glDiscardFramebufferEXT (GLenum target, GLsizei अङ्कः_Attachments, ध्रुव GLenum *attachments);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_discard_framebuffer */

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
GL_API शून्य *GL_APIENTRY gl_Map_बफर_Range_EXT (GLenum target, GLintptr विस्थापनम्_2, GLsizeiptr दीर्घता, GLbitfield access);
GL_API शून्य GL_APIENTRY gl_Flush_Mapped_बफर_Range_EXT (GLenum target, GLintptr विस्थापनम्_2, GLsizeiptr दीर्घता);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_map_buffer_range */

#यदि_अपरिभाषितम् GL_EXT_multi_draw_arrays
#परिभाषय GL_EXT_multi_draw_arrays 1
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMULTIDRAWARRAYSEXTPROC) (GLenum बहुलकम्, ध्रुव GLint *first, ध्रुव GLsizei *गणनम्, GLsizei primcount);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSEXTPROC) (GLenum बहुलकम्, ध्रुव GLsizei *गणनम्, GLenum type, ध्रुव शून्य *ध्रुव*indices, GLsizei primcount);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_API शून्य GL_APIENTRY glMultiDrawArraysEXT (GLenum बहुलकम्, ध्रुव GLint *first, ध्रुव GLsizei *गणनम्, GLsizei primcount);
GL_API शून्य GL_APIENTRY glMultiDrawElementsEXT (GLenum बहुलकम्, ध्रुव GLsizei *गणनम्, GLenum type, ध्रुव शून्य *ध्रुव*indices, GLsizei primcount);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_multi_draw_arrays */

#यदि_अपरिभाषितम् GL_EXT_multisampled_render_गन्तव्यम्_texture
#परिभाषय GL_EXT_multisampled_render_गन्तव्यम्_texture 1
#परिभाषय GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SAMPLES_EXT 0x8D6C
#परिभाषय GL_RENDERBUFFER_SAMPLES_EXT       0x8CAB
#परिभाषय GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT 0x8D56
#परिभाषय GL_MAX_SAMPLES_EXT                0x8D57
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei विस्तारः, GLsizei height);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEEXTPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_API शून्य GL_APIENTRY glRenderbufferStorageMultisampleEXT (GLenum target, GLsizei samples, GLenum internalformat, GLsizei विस्तारः, GLsizei height);
GL_API शून्य GL_APIENTRY glFramebufferTexture2DMultisampleEXT (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_multisampled_render_to_texture */

#यदि_अपरिभाषितम् GL_EXT_read_format_bgra
#परिभाषय GL_EXT_read_format_bgra 1
#परिभाषय GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT 0x8365
#परिभाषय GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT 0x8366
#यदि_अन्तः /* GL_EXT_read_format_bgra */

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
GL_API GLenum GL_APIENTRY gl_Get_Graphics_Reset_स्थितिः_EXT (शून्य);
GL_API शून्य GL_APIENTRY glReadnPixelsEXT (GLint x, GLint y, GLsizei विस्तारः, GLsizei height, GLenum format, GLenum type, GLsizei buf_आकार, शून्य *दत्त);
GL_API शून्य GL_APIENTRY glGetnUniformfvEXT (GLuint क्रमादेशः, GLint location, GLsizei buf_आकार, GLfloat *params);
GL_API शून्य GL_APIENTRY glGetnUniformivEXT (GLuint क्रमादेशः, GLint location, GLsizei buf_आकार, GLint *params);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_robustness */

#यदि_अपरिभाषितम् GL_EXT_sRGB
#परिभाषय GL_EXT_sRGB 1
#परिभाषय GL_SRGB_EXT                       0x8C40
#परिभाषय GL_SRGB_ALPHA_EXT                 0x8C42
#परिभाषय GL_SRGB8_ALPHA8_EXT               0x8C43
#परिभाषय GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING_EXT 0x8210
#यदि_अन्तः /* GL_EXT_sRGB */

#यदि_अपरिभाषितम् GL_EXT_texture_compression_dxt1
#परिभाषय GL_EXT_texture_compression_dxt1 1
#परिभाषय GL_COMPRESSED_RGB_S3TC_DXT1_EXT   0x83F0
#परिभाषय GL_COMPRESSED_RGBA_S3TC_DXT1_EXT  0x83F1
#यदि_अन्तः /* GL_EXT_texture_compression_dxt1 */

#यदि_अपरिभाषितम् GL_EXT_texture_filter_anisotropic
#परिभाषय GL_EXT_texture_filter_anisotropic 1
#परिभाषय GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#परिभाषय GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#यदि_अन्तः /* GL_EXT_texture_filter_anisotropic */

#यदि_अपरिभाषितम् GL_EXT_texture_format_BGRA8888
#परिभाषय GL_EXT_texture_format_BGRA8888 1
#यदि_अन्तः /* GL_EXT_texture_format_BGRA8888 */

#यदि_अपरिभाषितम् GL_EXT_texture_lod_bias
#परिभाषय GL_EXT_texture_lod_bias 1
#परिभाषय GL_MAX_TEXTURE_LOD_BIAS_EXT       0x84FD
#परिभाषय GL_TEXTURE_FILTER_CONTROL_EXT     0x8500
#परिभाषय GL_TEXTURE_LOD_BIAS_EXT           0x8501
#यदि_अन्तः /* GL_EXT_texture_lod_bias */

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
#परिभाषय GL_RGBA16F_EXT                    0x881A
#परिभाषय GL_RGB16F_EXT                     0x881B
#परिभाषय GL_ALPHA16F_EXT                   0x881C
#परिभाषय GL_LUMINANCE16F_EXT               0x881E
#परिभाषय GL_LUMINANCE_ALPHA16F_EXT         0x881F
#परिभाषय GL_R8_EXT                         0x8229
#परिभाषय GL_RG8_EXT                        0x822B
#परिभाषय GL_R32F_EXT                       0x822E
#परिभाषय GL_RG32F_EXT                      0x8230
#परिभाषय GL_R16F_EXT                       0x822D
#परिभाषय GL_RG16F_EXT                      0x822F
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXSTORAGE1DEXTPROC) (GLenum target, GLsizei स्तराः, GLenum internalformat, GLsizei विस्तारः);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXSTORAGE2DEXTPROC) (GLenum target, GLsizei स्तराः, GLenum internalformat, GLsizei विस्तारः, GLsizei height);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXSTORAGE3DEXTPROC) (GLenum target, GLsizei स्तराः, GLenum internalformat, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXTURESTORAGE1DEXTPROC) (GLuint texture, GLenum target, GLsizei स्तराः, GLenum internalformat, GLsizei विस्तारः);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXTURESTORAGE2DEXTPROC) (GLuint texture, GLenum target, GLsizei स्तराः, GLenum internalformat, GLsizei विस्तारः, GLsizei height);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXTURESTORAGE3DEXTPROC) (GLuint texture, GLenum target, GLsizei स्तराः, GLenum internalformat, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_API शून्य GL_APIENTRY glTexStorage1DEXT (GLenum target, GLsizei स्तराः, GLenum internalformat, GLsizei विस्तारः);
GL_API शून्य GL_APIENTRY glTexStorage2DEXT (GLenum target, GLsizei स्तराः, GLenum internalformat, GLsizei विस्तारः, GLsizei height);
GL_API शून्य GL_APIENTRY glTexStorage3DEXT (GLenum target, GLsizei स्तराः, GLenum internalformat, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2);
GL_API शून्य GL_APIENTRY glTextureStorage1DEXT (GLuint texture, GLenum target, GLsizei स्तराः, GLenum internalformat, GLsizei विस्तारः);
GL_API शून्य GL_APIENTRY glTextureStorage2DEXT (GLuint texture, GLenum target, GLsizei स्तराः, GLenum internalformat, GLsizei विस्तारः, GLsizei height);
GL_API शून्य GL_APIENTRY glTextureStorage3DEXT (GLuint texture, GLenum target, GLsizei स्तराः, GLenum internalformat, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2);
#यदि_अन्तः
#यदि_अन्तः /* GL_EXT_texture_storage */

#यदि_अपरिभाषितम् GL_IMG_multisampled_render_गन्तव्यम्_texture
#परिभाषय GL_IMG_multisampled_render_गन्तव्यम्_texture 1
#परिभाषय GL_RENDERBUFFER_SAMPLES_IMG       0x9133
#परिभाषय GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_IMG 0x9134
#परिभाषय GL_MAX_SAMPLES_IMG                0x9135
#परिभाषय GL_TEXTURE_SAMPLES_IMG            0x9136
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEIMGPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei विस्तारः, GLsizei height);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEIMGPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_API शून्य GL_APIENTRY glRenderbufferStorageMultisampleIMG (GLenum target, GLsizei samples, GLenum internalformat, GLsizei विस्तारः, GLsizei height);
GL_API शून्य GL_APIENTRY glFramebufferTexture2DMultisampleIMG (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#यदि_अन्तः
#यदि_अन्तः /* GL_IMG_multisampled_render_to_texture */

#यदि_अपरिभाषितम् GL_IMG_read_format
#परिभाषय GL_IMG_read_format 1
#परिभाषय GL_BGRA_IMG                       0x80E1
#परिभाषय GL_UNSIGNED_SHORT_4_4_4_4_REV_IMG 0x8365
#यदि_अन्तः /* GL_IMG_read_format */

#यदि_अपरिभाषितम् GL_IMG_texture_compression_pvrtc
#परिभाषय GL_IMG_texture_compression_pvrtc 1
#परिभाषय GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG 0x8C00
#परिभाषय GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG 0x8C01
#परिभाषय GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG 0x8C02
#परिभाषय GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG 0x8C03
#यदि_अन्तः /* GL_IMG_texture_compression_pvrtc */

#यदि_अपरिभाषितम् GL_IMG_texture_env_enhanced_fixed_function
#परिभाषय GL_IMG_texture_env_enhanced_fixed_function 1
#परिभाषय GL_MODULATE_COLOR_IMG             0x8C04
#परिभाषय GL_RECIP_सङ्कलय_SIGNED_ALPHA_IMG     0x8C05
#परिभाषय GL_TEXTURE_ALPHA_MODULATE_IMG     0x8C06
#परिभाषय GL_गुणकः_ALPHA_MODULATE_IMG      0x8C07
#परिभाषय GL_FRAGMENT_ALPHA_MODULATE_IMG    0x8C08
#परिभाषय GL_सङ्कलय_BLEND_IMG                  0x8C09
#परिभाषय GL_DOT3_RGBA_IMG                  0x86AF
#यदि_अन्तः /* GL_IMG_texture_env_enhanced_fixed_function */

#यदि_अपरिभाषितम् GL_IMG_user_clip_plane
#परिभाषय GL_IMG_user_clip_plane 1
#परिभाषय GL_CLIP_PLANE0_IMG                0x3000
#परिभाषय GL_CLIP_PLANE1_IMG                0x3001
#परिभाषय GL_CLIP_PLANE2_IMG                0x3002
#परिभाषय GL_CLIP_PLANE3_IMG                0x3003
#परिभाषय GL_CLIP_PLANE4_IMG                0x3004
#परिभाषय GL_CLIP_PLANE5_IMG                0x3005
#परिभाषय GL_MAX_CLIP_PLANES_IMG            0x0D32
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCLIPPLANEFIMGPROC) (GLenum p, ध्रुव GLfloat *eqn);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCLIPPLANEXIMGPROC) (GLenum p, ध्रुव GLfixed *eqn);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_API शून्य GL_APIENTRY glClipPlanefIMG (GLenum p, ध्रुव GLfloat *eqn);
GL_API शून्य GL_APIENTRY glClipPlanexIMG (GLenum p, ध्रुव GLfixed *eqn);
#यदि_अन्तः
#यदि_अन्तः /* GL_IMG_user_clip_plane */

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
GL_API शून्य GL_APIENTRY glDeleteFencesNV (GLsizei n, ध्रुव GLuint *fences);
GL_API शून्य GL_APIENTRY glGenFencesNV (GLsizei n, GLuint *fences);
GL_API GLboolean GL_APIENTRY glIsFenceNV (GLuint fence);
GL_API GLboolean GL_APIENTRY glTestFenceNV (GLuint fence);
GL_API शून्य GL_APIENTRY glGetFenceivNV (GLuint fence, GLenum pname, GLint *params);
GL_API शून्य GL_APIENTRY glFinishFenceNV (GLuint fence);
GL_API शून्य GL_APIENTRY gl_समुच्चयः_Fence_NV (GLuint fence, GLenum condition);
#यदि_अन्तः
#यदि_अन्तः /* GL_NV_fence */

#यदि_अपरिभाषितम् GL_QCOM_driver_control
#परिभाषय GL_QCOM_driver_control 1
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETDRIVERCONTROLSQCOMPROC) (GLint *अङ्कः, GLsizei आकार, GLuint *driverControls);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETDRIVERCONTROLSTRINGQCOMPROC) (GLuint driverControl, GLsizei buf_आकार, GLsizei *दीर्घता, GLchar *driverControlString);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLENABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDISABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_API शून्य GL_APIENTRY glGetDriverControlsQCOM (GLint *अङ्कः, GLsizei आकार, GLuint *driverControls);
GL_API शून्य GL_APIENTRY glGetDriverControlStringQCOM (GLuint driverControl, GLsizei buf_आकार, GLsizei *दीर्घता, GLchar *driverControlString);
GL_API शून्य GL_APIENTRY glEnableDriverControlQCOM (GLuint driverControl);
GL_API शून्य GL_APIENTRY glDisableDriverControlQCOM (GLuint driverControl);
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
GL_API शून्य GL_APIENTRY glExtGetTexturesQCOM (GLuint *textures, GLint maxTextures, GLint *अङ्कः_Textures);
GL_API शून्य GL_APIENTRY glExtGetBuffersQCOM (GLuint *buffers, GLint maxBuffers, GLint *अङ्कः_Buffers);
GL_API शून्य GL_APIENTRY glExtGetRenderbuffersQCOM (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *अङ्कः_Renderbuffers);
GL_API शून्य GL_APIENTRY glExtGetFramebuffersQCOM (GLuint *framebuffers, GLint maxFramebuffers, GLint *अङ्कः_Framebuffers);
GL_API शून्य GL_APIENTRY glExtGetTexLevelParameterivQCOM (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
GL_API शून्य GL_APIENTRY glExtTexObjectStateOverrideiQCOM (GLenum target, GLenum pname, GLint param);
GL_API शून्य GL_APIENTRY glExtGetTexSubImageQCOM (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei विस्तारः, GLsizei height, GLsizei गभीरता_2, GLenum format, GLenum type, शून्य *texels);
GL_API शून्य GL_APIENTRY gl_Ext_Get_बफर_Pointerv_QCOM (GLenum target, शून्य **params);
#यदि_अन्तः
#यदि_अन्तः /* GL_QCOM_extended_get */

#यदि_अपरिभाषितम् GL_QCOM_extended_get2
#परिभाषय GL_QCOM_extended_get2 1
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLEXTGETSHADERSQCOMPROC) (GLuint *shaders, GLint maxShaders, GLint *अङ्कः_Shaders);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLEXTGETPROGRAMSQCOMPROC) (GLuint *programs, GLint maxPrograms, GLint *अङ्कः_Programs);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLEXTISPROGRAMBINARYQCOMPROC) (GLuint क्रमादेशः);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLEXTGETPROGRAMBINARYSOURCEQCOMPROC) (GLuint क्रमादेशः, GLenum shadertype, GLchar *source, GLint *दीर्घता);
#यदि_परिभाषितम् GL_GLEXT_PROTOTYPES
GL_API शून्य GL_APIENTRY glExtGetShadersQCOM (GLuint *shaders, GLint maxShaders, GLint *अङ्कः_Shaders);
GL_API शून्य GL_APIENTRY glExtGetProgramsQCOM (GLuint *programs, GLint maxPrograms, GLint *अङ्कः_Programs);
GL_API GLboolean GL_APIENTRY gl_Ext_Is_क्रमादेशः_द्विमान_QCOM (GLuint क्रमादेशः);
GL_API शून्य GL_APIENTRY gl_Ext_Get_क्रमादेशः_द्विमान_Source_QCOM (GLuint क्रमादेशः, GLenum shadertype, GLchar *source, GLint *दीर्घता);
#यदि_अन्तः
#यदि_अन्तः /* GL_QCOM_extended_get2 */

#यदि_अपरिभाषितम् GL_QCOM_perfmon_global_बहुलकम्
#परिभाषय GL_QCOM_perfmon_global_बहुलकम् 1
#परिभाषय GL_PERFMON_GLOBAL_बहुलकम्_QCOM       0x8FA0
#यदि_अन्तः /* GL_QCOM_perfmon_global_mode */

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
GL_API शून्य GL_APIENTRY glStartTilingQCOM (GLuint x, GLuint y, GLuint विस्तारः, GLuint height, GLbitfield preserve_आवरणम्);
GL_API शून्य GL_APIENTRY gl_अन्तः_Tiling_QCOM (GLbitfield preserve_आवरणम्);
#यदि_अन्तः
#यदि_अन्तः /* GL_QCOM_tiled_rendering */

#यदि_अपरिभाषितम् GL_QCOM_writeonly_rendering
#परिभाषय GL_QCOM_writeonly_rendering 1
#परिभाषय GL_WRITEONLY_RENDERING_QCOM       0x8823
#यदि_अन्तः /* GL_QCOM_writeonly_rendering */

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः
