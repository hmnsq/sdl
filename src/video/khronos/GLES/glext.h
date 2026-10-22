#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ __gles1_glext_h_
#ವ್ಯಾಖ್ಯಾನಿಸು __gles1_glext_h_ 1

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ

/*
** Copyright 2013-2026 The Khronos Group Inc.
** SPDX-License-Identifier: MIT
**
** This header is generated from the Khronos OpenGL / OpenGL ES XML
** API Registry. The current version of the Registry, generator scripts
** used to make the header, and the header can be found at
**   https://github.com/KhronosGroup/OpenGL-Registry
*/

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_APIENTRYP
#ವ್ಯಾಖ್ಯಾನಿಸು GL_APIENTRYP GL_APIENTRY*
#ಆದರೆ_ಅಂತ್ಯ

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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_KHR_debug
#ವ್ಯಾಖ್ಯಾನಿಸು GL_KHR_debug 1
#ಆದರೆ_ಅಂತ್ಯ /* GL_KHR_debug */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_OES_EGL_image
#ವ್ಯಾಖ್ಯಾನಿಸು GL_OES_EGL_image 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ *GLeglImageOES;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLEGLIMAGETARGETTEXTURE2DOESPROC) (GLenum ಗುರಿ, GLeglImageOES image);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLEGLIMAGETARGETRENDERBUFFERSTORAGEOESPROC) (GLenum ಗುರಿ, GLeglImageOES image);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ GL_GLEXT_PROTOTYPES
GL_API ಶೂನ್ಯ GL_APIENTRY gl_EGLImage_ಗುರಿ_Texture2_DOES (GLenum ಗುರಿ, GLeglImageOES image);
GL_API ಶೂನ್ಯ GL_APIENTRY gl_EGLImage_ಗುರಿ_Renderbuffer_Storage_OES (GLenum ಗುರಿ, GLeglImageOES image);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* GL_OES_EGL_image */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_OES_EGL_image_external
#ವ್ಯಾಖ್ಯಾನಿಸು GL_OES_EGL_image_external 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_TEXTURE_EXTERNAL_OES           0x8D65
#ವ್ಯಾಖ್ಯಾನಿಸು GL_TEXTURE_BINDING_EXTERNAL_OES   0x8D67
#ವ್ಯಾಖ್ಯಾನಿಸು GL_REQUIRED_TEXTURE_IMAGE_UNITS_OES 0x8D68
#ಆದರೆ_ಅಂತ್ಯ /* GL_OES_EGL_image_external */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_OES_blend_equation_separate
#ವ್ಯಾಖ್ಯಾನಿಸು GL_OES_blend_equation_separate 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_BLEND_EQUATION_RGB_OES         0x8009
#ವ್ಯಾಖ್ಯಾನಿಸು GL_BLEND_EQUATION_ALPHA_OES       0x883D
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEOESPROC) (GLenum ಬಹುಲಕ_RGB, GLenum ಬಹುಲಕ_Alpha);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ GL_GLEXT_PROTOTYPES
GL_API ಶೂನ್ಯ GL_APIENTRY glBlendEquationSeparateOES (GLenum ಬಹುಲಕ_RGB, GLenum ಬಹುಲಕ_Alpha);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* GL_OES_blend_equation_separate */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_OES_blend_func_separate
#ವ್ಯಾಖ್ಯಾನಿಸು GL_OES_blend_func_separate 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_BLEND_DST_RGB_OES              0x80C8
#ವ್ಯಾಖ್ಯಾನಿಸು GL_BLEND_SRC_RGB_OES              0x80C9
#ವ್ಯಾಖ್ಯಾನಿಸು GL_BLEND_DST_ALPHA_OES            0x80CA
#ವ್ಯಾಖ್ಯಾನಿಸು GL_BLEND_SRC_ALPHA_OES            0x80CB
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEOESPROC) (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ GL_GLEXT_PROTOTYPES
GL_API ಶೂನ್ಯ GL_APIENTRY glBlendFuncSeparateOES (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* GL_OES_blend_func_separate */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_OES_blend_ಕಳೆ
#ವ್ಯಾಖ್ಯಾನಿಸು GL_OES_blend_ಕಳೆ 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_BLEND_EQUATION_OES             0x8009
#ವ್ಯಾಖ್ಯಾನಿಸು GL_FUNC_ಕೂಡಿಸು_OES                   0x8006
#ವ್ಯಾಖ್ಯಾನಿಸು GL_FUNC_ಕಳೆ_OES              0x800A
#ವ್ಯಾಖ್ಯಾನಿಸು GL_FUNC_ಹಿಮ್ಮುಖ_ಕಳೆ_OES      0x800B
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLBLENDEQUATIONOESPROC) (GLenum ಬಹುಲಕ);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ GL_GLEXT_PROTOTYPES
GL_API ಶೂನ್ಯ GL_APIENTRY glBlendEquationOES (GLenum ಬಹುಲಕ);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* GL_OES_blend_subtract */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_OES_byte_coordinates
#ವ್ಯಾಖ್ಯಾನಿಸು GL_OES_byte_coordinates 1
#ಆದರೆ_ಅಂತ್ಯ /* GL_OES_byte_coordinates */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_OES_compressed_ETC1_RGB8_sub_texture
#ವ್ಯಾಖ್ಯಾನಿಸು GL_OES_compressed_ETC1_RGB8_sub_texture 1
#ಆದರೆ_ಅಂತ್ಯ /* GL_OES_compressed_ETC1_RGB8_sub_texture */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_OES_compressed_ETC1_RGB8_texture
#ವ್ಯಾಖ್ಯಾನಿಸು GL_OES_compressed_ETC1_RGB8_texture 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ETC1_RGB8_OES                  0x8D64
#ಆದರೆ_ಅಂತ್ಯ /* GL_OES_compressed_ETC1_RGB8_texture */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_OES_depth24
#ವ್ಯಾಖ್ಯಾನಿಸು GL_OES_depth24 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ಆಳ_COMPONENT24_OES          0x81A6
#ಆದರೆ_ಅಂತ್ಯ /* GL_OES_depth24 */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_OES_depth32
#ವ್ಯಾಖ್ಯಾನಿಸು GL_OES_depth32 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ಆಳ_COMPONENT32_OES          0x81A7
#ಆದರೆ_ಅಂತ್ಯ /* GL_OES_depth32 */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_OES_draw_texture
#ವ್ಯಾಖ್ಯಾನಿಸು GL_OES_draw_texture 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_TEXTURE_CROP_RECT_OES          0x8B9D
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLDRAWTEXSOESPROC) (GLshort x, GLshort y, GLshort z, GLshort ಅಗಲ, GLshort ಎತ್ತರ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLDRAWTEXIOESPROC) (GLint x, GLint y, GLint z, GLint ಅಗಲ, GLint ಎತ್ತರ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLDRAWTEXXOESPROC) (GLfixed x, GLfixed y, GLfixed z, GLfixed ಅಗಲ, GLfixed ಎತ್ತರ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLDRAWTEXSVOESPROC) (ಸ್ಥಿರಾಂಕ GLshort *coords);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLDRAWTEXIVOESPROC) (ಸ್ಥಿರಾಂಕ GLint *coords);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLDRAWTEXXVOESPROC) (ಸ್ಥಿರಾಂಕ GLfixed *coords);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLDRAWTEXFOESPROC) (GLfloat x, GLfloat y, GLfloat z, GLfloat ಅಗಲ, GLfloat ಎತ್ತರ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLDRAWTEXFVOESPROC) (ಸ್ಥಿರಾಂಕ GLfloat *coords);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ GL_GLEXT_PROTOTYPES
GL_API ಶೂನ್ಯ GL_APIENTRY glDrawTexsOES (GLshort x, GLshort y, GLshort z, GLshort ಅಗಲ, GLshort ಎತ್ತರ);
GL_API ಶೂನ್ಯ GL_APIENTRY glDrawTexiOES (GLint x, GLint y, GLint z, GLint ಅಗಲ, GLint ಎತ್ತರ);
GL_API ಶೂನ್ಯ GL_APIENTRY glDrawTexxOES (GLfixed x, GLfixed y, GLfixed z, GLfixed ಅಗಲ, GLfixed ಎತ್ತರ);
GL_API ಶೂನ್ಯ GL_APIENTRY glDrawTexsvOES (ಸ್ಥಿರಾಂಕ GLshort *coords);
GL_API ಶೂನ್ಯ GL_APIENTRY glDrawTexivOES (ಸ್ಥಿರಾಂಕ GLint *coords);
GL_API ಶೂನ್ಯ GL_APIENTRY glDrawTexxvOES (ಸ್ಥಿರಾಂಕ GLfixed *coords);
GL_API ಶೂನ್ಯ GL_APIENTRY glDrawTexfOES (GLfloat x, GLfloat y, GLfloat z, GLfloat ಅಗಲ, GLfloat ಎತ್ತರ);
GL_API ಶೂನ್ಯ GL_APIENTRY glDrawTexfvOES (ಸ್ಥಿರಾಂಕ GLfloat *coords);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* GL_OES_draw_texture */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_OES_element_ಸೂಚ್ಯಂಕ_uint
#ವ್ಯಾಖ್ಯಾನಿಸು GL_OES_element_ಸೂಚ್ಯಂಕ_uint 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_UNSIGNED_INT                   0x1405
#ಆದರೆ_ಅಂತ್ಯ /* GL_OES_element_index_uint */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_OES_extended_ಮಾತೃಕೆ_palette
#ವ್ಯಾಖ್ಯಾನಿಸು GL_OES_extended_ಮಾತೃಕೆ_palette 1
#ಆದರೆ_ಅಂತ್ಯ /* GL_OES_extended_matrix_palette */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_OES_fbo_render_mipmap
#ವ್ಯಾಖ್ಯಾನಿಸು GL_OES_fbo_render_mipmap 1
#ಆದರೆ_ಅಂತ್ಯ /* GL_OES_fbo_render_mipmap */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_OES_fixed_ಬಿಂದು
#ವ್ಯಾಖ್ಯಾನಿಸು GL_OES_fixed_ಬಿಂದು 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_FIXED_OES                      0x140C
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLALPHAFUNCXOESPROC) (GLenum func, GLfixed ref);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLCLEARCOLORXOESPROC) (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLCLEARDEPTHXOESPROC) (GLfixed ಆಳ_2);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLCLIPPLANEXOESPROC) (GLenum plane, ಸ್ಥಿರಾಂಕ GLfixed *equation);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLCOLOR4XOESPROC) (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLDEPTHRANGEXOESPROC) (GLfixed n, GLfixed f);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLFOGXOESPROC) (GLenum pname, GLfixed param);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLFOGXVOESPROC) (GLenum pname, ಸ್ಥಿರಾಂಕ GLfixed *param);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLFRUSTUMXOESPROC) (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLGETCLIPPLANEXOESPROC) (GLenum plane, GLfixed *equation);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLGETFIXEDVOESPROC) (GLenum pname, GLfixed *params);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLGETTEXENVXVOESPROC) (GLenum ಗುರಿ, GLenum pname, GLfixed *params);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLGETTEXPARAMETERXVOESPROC) (GLenum ಗುರಿ, GLenum pname, GLfixed *params);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLLIGHTMODELXOESPROC) (GLenum pname, GLfixed param);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLLIGHTMODELXVOESPROC) (GLenum pname, ಸ್ಥಿರಾಂಕ GLfixed *param);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLLIGHTXOESPROC) (GLenum light, GLenum pname, GLfixed param);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLLIGHTXVOESPROC) (GLenum light, GLenum pname, ಸ್ಥಿರಾಂಕ GLfixed *params);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLLINEWIDTHXOESPROC) (GLfixed ಅಗಲ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLLOADMATRIXXOESPROC) (ಸ್ಥಿರಾಂಕ GLfixed *m);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLMATERIALXOESPROC) (GLenum face, GLenum pname, GLfixed param);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLMATERIALXVOESPROC) (GLenum face, GLenum pname, ಸ್ಥಿರಾಂಕ GLfixed *param);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLMULTMATRIXXOESPROC) (ಸ್ಥಿರಾಂಕ GLfixed *m);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLMULTITEXCOORD4XOESPROC) (GLenum texture, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLNORMAL3XOESPROC) (GLfixed nx, GLfixed ny, GLfixed nz);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLORTHOXOESPROC) (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLPOINTPARAMETERXVOESPROC) (GLenum pname, ಸ್ಥಿರಾಂಕ GLfixed *params);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLPOINTSIZEXOESPROC) (GLfixed ಗಾತ್ರ_2);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLPOLYGONOFFSETXOESPROC) (GLfixed ಗುಣಕ, GLfixed units);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLROTATEXOESPROC) (GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLSCALEXOESPROC) (GLfixed x, GLfixed y, GLfixed z);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLTEXENVXOESPROC) (GLenum ಗುರಿ, GLenum pname, GLfixed param);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLTEXENVXVOESPROC) (GLenum ಗುರಿ, GLenum pname, ಸ್ಥಿರಾಂಕ GLfixed *params);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLTEXPARAMETERXOESPROC) (GLenum ಗುರಿ, GLenum pname, GLfixed param);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLTEXPARAMETERXVOESPROC) (GLenum ಗುರಿ, GLenum pname, ಸ್ಥಿರಾಂಕ GLfixed *params);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLTRANSLATEXOESPROC) (GLfixed x, GLfixed y, GLfixed z);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLGETLIGHTXVOESPROC) (GLenum light, GLenum pname, GLfixed *params);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLGETMATERIALXVOESPROC) (GLenum face, GLenum pname, GLfixed *params);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLPOINTPARAMETERXOESPROC) (GLenum pname, GLfixed param);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLSAMPLECOVERAGEXOESPROC) (GLclampx ಮೌಲ್ಯ, GLboolean invert);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLGETTEXGENXVOESPROC) (GLenum coord, GLenum pname, GLfixed *params);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLTEXGENXOESPROC) (GLenum coord, GLenum pname, GLfixed param);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLTEXGENXVOESPROC) (GLenum coord, GLenum pname, ಸ್ಥಿರಾಂಕ GLfixed *params);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ GL_GLEXT_PROTOTYPES
GL_API ಶೂನ್ಯ GL_APIENTRY glAlphaFuncxOES (GLenum func, GLfixed ref);
GL_API ಶೂನ್ಯ GL_APIENTRY glClearColorxOES (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GL_API ಶೂನ್ಯ GL_APIENTRY glClearDepthxOES (GLfixed ಆಳ_2);
GL_API ಶೂನ್ಯ GL_APIENTRY glClipPlanexOES (GLenum plane, ಸ್ಥಿರಾಂಕ GLfixed *equation);
GL_API ಶೂನ್ಯ GL_APIENTRY glColor4xOES (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GL_API ಶೂನ್ಯ GL_APIENTRY gl_ಆಳ_Rangex_OES (GLfixed n, GLfixed f);
GL_API ಶೂನ್ಯ GL_APIENTRY glFogxOES (GLenum pname, GLfixed param);
GL_API ಶೂನ್ಯ GL_APIENTRY glFogxvOES (GLenum pname, ಸ್ಥಿರಾಂಕ GLfixed *param);
GL_API ಶೂನ್ಯ GL_APIENTRY glFrustumxOES (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
GL_API ಶೂನ್ಯ GL_APIENTRY glGetClipPlanexOES (GLenum plane, GLfixed *equation);
GL_API ಶೂನ್ಯ GL_APIENTRY glGetFixedvOES (GLenum pname, GLfixed *params);
GL_API ಶೂನ್ಯ GL_APIENTRY glGetTexEnvxvOES (GLenum ಗುರಿ, GLenum pname, GLfixed *params);
GL_API ಶೂನ್ಯ GL_APIENTRY glGetTexParameterxvOES (GLenum ಗುರಿ, GLenum pname, GLfixed *params);
GL_API ಶೂನ್ಯ GL_APIENTRY glLightModelxOES (GLenum pname, GLfixed param);
GL_API ಶೂನ್ಯ GL_APIENTRY glLightModelxvOES (GLenum pname, ಸ್ಥಿರಾಂಕ GLfixed *param);
GL_API ಶೂನ್ಯ GL_APIENTRY glLightxOES (GLenum light, GLenum pname, GLfixed param);
GL_API ಶೂನ್ಯ GL_APIENTRY glLightxvOES (GLenum light, GLenum pname, ಸ್ಥಿರಾಂಕ GLfixed *params);
GL_API ಶೂನ್ಯ GL_APIENTRY gl_ಸಾಲು_Widthx_OES (GLfixed ಅಗಲ);
GL_API ಶೂನ್ಯ GL_APIENTRY gl_ತುಂಬು_Matrixx_OES (ಸ್ಥಿರಾಂಕ GLfixed *m);
GL_API ಶೂನ್ಯ GL_APIENTRY glMaterialxOES (GLenum face, GLenum pname, GLfixed param);
GL_API ಶೂನ್ಯ GL_APIENTRY glMaterialxvOES (GLenum face, GLenum pname, ಸ್ಥಿರಾಂಕ GLfixed *param);
GL_API ಶೂನ್ಯ GL_APIENTRY glMultMatrixxOES (ಸ್ಥಿರಾಂಕ GLfixed *m);
GL_API ಶೂನ್ಯ GL_APIENTRY glMultiTexCoord4xOES (GLenum texture, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
GL_API ಶೂನ್ಯ GL_APIENTRY glNormal3xOES (GLfixed nx, GLfixed ny, GLfixed nz);
GL_API ಶೂನ್ಯ GL_APIENTRY glOrthoxOES (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
GL_API ಶೂನ್ಯ GL_APIENTRY gl_ಬಿಂದು_Parameterxv_OES (GLenum pname, ಸ್ಥಿರಾಂಕ GLfixed *params);
GL_API ಶೂನ್ಯ GL_APIENTRY gl_ಬಿಂದು_Sizex_OES (GLfixed ಗಾತ್ರ_2);
GL_API ಶೂನ್ಯ GL_APIENTRY glPolygonOffsetxOES (GLfixed ಗುಣಕ, GLfixed units);
GL_API ಶೂನ್ಯ GL_APIENTRY glRotatexOES (GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
GL_API ಶೂನ್ಯ GL_APIENTRY glScalexOES (GLfixed x, GLfixed y, GLfixed z);
GL_API ಶೂನ್ಯ GL_APIENTRY glTexEnvxOES (GLenum ಗುರಿ, GLenum pname, GLfixed param);
GL_API ಶೂನ್ಯ GL_APIENTRY glTexEnvxvOES (GLenum ಗುರಿ, GLenum pname, ಸ್ಥಿರಾಂಕ GLfixed *params);
GL_API ಶೂನ್ಯ GL_APIENTRY glTexParameterxOES (GLenum ಗುರಿ, GLenum pname, GLfixed param);
GL_API ಶೂನ್ಯ GL_APIENTRY glTexParameterxvOES (GLenum ಗುರಿ, GLenum pname, ಸ್ಥಿರಾಂಕ GLfixed *params);
GL_API ಶೂನ್ಯ GL_APIENTRY glTranslatexOES (GLfixed x, GLfixed y, GLfixed z);
GL_API ಶೂನ್ಯ GL_APIENTRY glGetLightxvOES (GLenum light, GLenum pname, GLfixed *params);
GL_API ಶೂನ್ಯ GL_APIENTRY glGetMaterialxvOES (GLenum face, GLenum pname, GLfixed *params);
GL_API ಶೂನ್ಯ GL_APIENTRY gl_ಬಿಂದು_Parameterx_OES (GLenum pname, GLfixed param);
GL_API ಶೂನ್ಯ GL_APIENTRY glSampleCoveragexOES (GLclampx ಮೌಲ್ಯ, GLboolean invert);
GL_API ಶೂನ್ಯ GL_APIENTRY glGetTexGenxvOES (GLenum coord, GLenum pname, GLfixed *params);
GL_API ಶೂನ್ಯ GL_APIENTRY glTexGenxOES (GLenum coord, GLenum pname, GLfixed param);
GL_API ಶೂನ್ಯ GL_APIENTRY glTexGenxvOES (GLenum coord, GLenum pname, ಸ್ಥಿರಾಂಕ GLfixed *params);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* GL_OES_fixed_point */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_OES_framebuffer_object
#ವ್ಯಾಖ್ಯಾನಿಸು GL_OES_framebuffer_object 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_NONE_OES                       0
#ವ್ಯಾಖ್ಯಾನಿಸು GL_FRAMEBUFFER_OES                0x8D40
#ವ್ಯಾಖ್ಯಾನಿಸು GL_RENDERBUFFER_OES               0x8D41
#ವ್ಯಾಖ್ಯಾನಿಸು GL_RGBA4_OES                      0x8056
#ವ್ಯಾಖ್ಯಾನಿಸು GL_RGB5_A1_OES                    0x8057
#ವ್ಯಾಖ್ಯಾನಿಸು GL_RGB565_OES                     0x8D62
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ಆಳ_COMPONENT16_OES          0x81A5
#ವ್ಯಾಖ್ಯಾನಿಸು GL_RENDERBUFFER_ಅಗಲ_OES         0x8D42
#ವ್ಯಾಖ್ಯಾನಿಸು GL_RENDERBUFFER_ಎತ್ತರ_OES        0x8D43
#ವ್ಯಾಖ್ಯಾನಿಸು GL_RENDERBUFFER_ಆಂತರಿಕ_FORMAT_OES 0x8D44
#ವ್ಯಾಖ್ಯಾನಿಸು GL_RENDERBUFFER_RED_ಗಾತ್ರ_OES      0x8D50
#ವ್ಯಾಖ್ಯಾನಿಸು GL_RENDERBUFFER_GREEN_ಗಾತ್ರ_OES    0x8D51
#ವ್ಯಾಖ್ಯಾನಿಸು GL_RENDERBUFFER_BLUE_ಗಾತ್ರ_OES     0x8D52
#ವ್ಯಾಖ್ಯಾನಿಸು GL_RENDERBUFFER_ALPHA_ಗಾತ್ರ_OES    0x8D53
#ವ್ಯಾಖ್ಯಾನಿಸು GL_RENDERBUFFER_ಆಳ_ಗಾತ್ರ_OES    0x8D54
#ವ್ಯಾಖ್ಯಾನಿಸು GL_RENDERBUFFER_STENCIL_ಗಾತ್ರ_OES  0x8D55
#ವ್ಯಾಖ್ಯಾನಿಸು GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_OES 0x8CD0
#ವ್ಯಾಖ್ಯಾನಿಸು GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_OES 0x8CD1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_OES 0x8CD2
#ವ್ಯಾಖ್ಯಾನಿಸು GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_OES 0x8CD3
#ವ್ಯಾಖ್ಯಾನಿಸು GL_COLOR_ATTACHMENT0_OES          0x8CE0
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ಆಳ_ATTACHMENT_OES           0x8D00
#ವ್ಯಾಖ್ಯಾನಿಸು GL_STENCIL_ATTACHMENT_OES         0x8D20
#ವ್ಯಾಖ್ಯಾನಿಸು GL_FRAMEBUFFER_COMPLETE_OES       0x8CD5
#ವ್ಯಾಖ್ಯಾನಿಸು GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_OES 0x8CD6
#ವ್ಯಾಖ್ಯಾನಿಸು GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_OES 0x8CD7
#ವ್ಯಾಖ್ಯಾನಿಸು GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_OES 0x8CD9
#ವ್ಯಾಖ್ಯಾನಿಸು GL_FRAMEBUFFER_INCOMPLETE_FORMATS_OES 0x8CDA
#ವ್ಯಾಖ್ಯಾನಿಸು GL_FRAMEBUFFER_UNSUPPORTED_OES    0x8CDD
#ವ್ಯಾಖ್ಯಾನಿಸು GL_FRAMEBUFFER_BINDING_OES        0x8CA6
#ವ್ಯಾಖ್ಯಾನಿಸು GL_RENDERBUFFER_BINDING_OES       0x8CA7
#ವ್ಯಾಖ್ಯಾನಿಸು GL_MAX_RENDERBUFFER_ಗಾತ್ರ_OES      0x84E8
#ವ್ಯಾಖ್ಯಾನಿಸು GL_INVALID_FRAMEBUFFER_OPERATION_OES 0x0506
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ GLboolean (GL_APIENTRYP PFNGLISRENDERBUFFEROESPROC) (GLuint renderbuffer);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLBINDRENDERBUFFEROESPROC) (GLenum ಗುರಿ, GLuint renderbuffer);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLDELETERENDERBUFFERSOESPROC) (GLsizei n, ಸ್ಥಿರಾಂಕ GLuint *renderbuffers);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLGENRENDERBUFFERSOESPROC) (GLsizei n, GLuint *renderbuffers);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEOESPROC) (GLenum ಗುರಿ, GLenum internalformat, GLsizei ಅಗಲ, GLsizei ಎತ್ತರ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVOESPROC) (GLenum ಗುರಿ, GLenum pname, GLint *params);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ GLboolean (GL_APIENTRYP PFNGLISFRAMEBUFFEROESPROC) (GLuint framebuffer);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLBINDFRAMEBUFFEROESPROC) (GLenum ಗುರಿ, GLuint framebuffer);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLDELETEFRAMEBUFFERSOESPROC) (GLsizei n, ಸ್ಥಿರಾಂಕ GLuint *framebuffers);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLGENFRAMEBUFFERSOESPROC) (GLsizei n, GLuint *framebuffers);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ GLenum (GL_APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSOESPROC) (GLenum ಗುರಿ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFEROESPROC) (GLenum ಗುರಿ, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DOESPROC) (GLenum ಗುರಿ, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVOESPROC) (GLenum ಗುರಿ, GLenum attachment, GLenum pname, GLint *params);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLGENERATEMIPMAPOESPROC) (GLenum ಗುರಿ);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ GL_GLEXT_PROTOTYPES
GL_API GLboolean GL_APIENTRY glIsRenderbufferOES (GLuint renderbuffer);
GL_API ಶೂನ್ಯ GL_APIENTRY glBindRenderbufferOES (GLenum ಗುರಿ, GLuint renderbuffer);
GL_API ಶೂನ್ಯ GL_APIENTRY glDeleteRenderbuffersOES (GLsizei n, ಸ್ಥಿರಾಂಕ GLuint *renderbuffers);
GL_API ಶೂನ್ಯ GL_APIENTRY glGenRenderbuffersOES (GLsizei n, GLuint *renderbuffers);
GL_API ಶೂನ್ಯ GL_APIENTRY glRenderbufferStorageOES (GLenum ಗುರಿ, GLenum internalformat, GLsizei ಅಗಲ, GLsizei ಎತ್ತರ);
GL_API ಶೂನ್ಯ GL_APIENTRY glGetRenderbufferParameterivOES (GLenum ಗುರಿ, GLenum pname, GLint *params);
GL_API GLboolean GL_APIENTRY glIsFramebufferOES (GLuint framebuffer);
GL_API ಶೂನ್ಯ GL_APIENTRY glBindFramebufferOES (GLenum ಗುರಿ, GLuint framebuffer);
GL_API ಶೂನ್ಯ GL_APIENTRY glDeleteFramebuffersOES (GLsizei n, ಸ್ಥಿರಾಂಕ GLuint *framebuffers);
GL_API ಶೂನ್ಯ GL_APIENTRY glGenFramebuffersOES (GLsizei n, GLuint *framebuffers);
GL_API GLenum GL_APIENTRY gl_Check_Framebuffer_ಸ್ಥಿತಿ_OES (GLenum ಗುರಿ);
GL_API ಶೂನ್ಯ GL_APIENTRY glFramebufferRenderbufferOES (GLenum ಗುರಿ, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
GL_API ಶೂನ್ಯ GL_APIENTRY glFramebufferTexture2DOES (GLenum ಗುರಿ, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GL_API ಶೂನ್ಯ GL_APIENTRY glGetFramebufferAttachmentParameterivOES (GLenum ಗುರಿ, GLenum attachment, GLenum pname, GLint *params);
GL_API ಶೂನ್ಯ GL_APIENTRY glGenerateMipmapOES (GLenum ಗುರಿ);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* GL_OES_framebuffer_object */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_OES_mapbuffer
#ವ್ಯಾಖ್ಯಾನಿಸು GL_OES_mapbuffer 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_WRITE_ONLY_OES                 0x88B9
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ಬಫರ್_ACCESS_OES              0x88BB
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ಬಫರ್_MAPPED_OES              0x88BC
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ಬಫರ್_MAP_ಸೂಚಕ_OES         0x88BD
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ *(GL_APIENTRYP PFNGLMAPBUFFEROESPROC) (GLenum ಗುರಿ, GLenum access);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ GLboolean (GL_APIENTRYP PFNGLUNMAPBUFFEROESPROC) (GLenum ಗುರಿ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLGETBUFFERPOINTERVOESPROC) (GLenum ಗುರಿ, GLenum pname, ಶೂನ್ಯ **params);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ GL_GLEXT_PROTOTYPES
GL_API ಶೂನ್ಯ *GL_APIENTRY gl_Map_ಬಫರ್_OES (GLenum ಗುರಿ, GLenum access);
GL_API GLboolean GL_APIENTRY gl_Unmap_ಬಫರ್_OES (GLenum ಗುರಿ);
GL_API ಶೂನ್ಯ GL_APIENTRY gl_Get_ಬಫರ್_Pointerv_OES (GLenum ಗುರಿ, GLenum pname, ಶೂನ್ಯ **params);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* GL_OES_mapbuffer */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_OES_ಮಾತೃಕೆ_get
#ವ್ಯಾಖ್ಯಾನಿಸು GL_OES_ಮಾತೃಕೆ_get 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_MODELVIEW_ಮಾತೃಕೆ_FLOAT_AS_INT_ಬಿಟ್ಟುಗಳು_OES 0x898D
#ವ್ಯಾಖ್ಯಾನಿಸು GL_PROJECTION_ಮಾತೃಕೆ_FLOAT_AS_INT_ಬಿಟ್ಟುಗಳು_OES 0x898E
#ವ್ಯಾಖ್ಯಾನಿಸು GL_TEXTURE_ಮಾತೃಕೆ_FLOAT_AS_INT_ಬಿಟ್ಟುಗಳು_OES 0x898F
#ಆದರೆ_ಅಂತ್ಯ /* GL_OES_matrix_get */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_OES_ಮಾತೃಕೆ_palette
#ವ್ಯಾಖ್ಯಾನಿಸು GL_OES_ಮಾತೃಕೆ_palette 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_MAX_ಶೃಂಗ_UNITS_OES           0x86A4
#ವ್ಯಾಖ್ಯಾನಿಸು GL_MAX_PALETTE_MATRICES_OES       0x8842
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ಮಾತೃಕೆ_PALETTE_OES             0x8840
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ಮಾತೃಕೆ_ಸೂಚ್ಯಂಕ_ARRAY_OES         0x8844
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ತೂಕ_ARRAY_OES               0x86AD
#ವ್ಯಾಖ್ಯಾನಿಸು GL_CURRENT_PALETTE_ಮಾತೃಕೆ_OES     0x8843
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ಮಾತೃಕೆ_ಸೂಚ್ಯಂಕ_ARRAY_ಗಾತ್ರ_OES    0x8846
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ಮಾತೃಕೆ_ಸೂಚ್ಯಂಕ_ARRAY_TYPE_OES    0x8847
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ಮಾತೃಕೆ_ಸೂಚ್ಯಂಕ_ARRAY_STRIDE_OES  0x8848
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ಮಾತೃಕೆ_ಸೂಚ್ಯಂಕ_ARRAY_ಸೂಚಕ_OES 0x8849
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ಮಾತೃಕೆ_ಸೂಚ್ಯಂಕ_ARRAY_ಬಫರ್_BINDING_OES 0x8B9E
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ತೂಕ_ARRAY_ಗಾತ್ರ_OES          0x86AB
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ತೂಕ_ARRAY_TYPE_OES          0x86A9
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ತೂಕ_ARRAY_STRIDE_OES        0x86AA
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ತೂಕ_ARRAY_ಸೂಚಕ_OES       0x86AC
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ತೂಕ_ARRAY_ಬಫರ್_BINDING_OES 0x889E
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLCURRENTPALETTEMATRIXOESPROC) (GLuint matrixpaletteindex);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLLOADPALETTEFROMMODELVIEWMATRIXOESPROC) (ಶೂನ್ಯ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLMATRIXINDEXPOINTEROESPROC) (GLint ಗಾತ್ರ_2, GLenum type, GLsizei stride, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ಸೂಚಕ_2);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLWEIGHTPOINTEROESPROC) (GLint ಗಾತ್ರ_2, GLenum type, GLsizei stride, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ಸೂಚಕ_2);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ GL_GLEXT_PROTOTYPES
GL_API ಶೂನ್ಯ GL_APIENTRY gl_Current_Palette_ಮಾತೃಕೆ_OES (GLuint matrixpaletteindex);
GL_API ಶೂನ್ಯ GL_APIENTRY gl_ತುಂಬು_Palette_From_Model_View_ಮಾತೃಕೆ_OES (ಶೂನ್ಯ);
GL_API ಶೂನ್ಯ GL_APIENTRY gl_ಮಾತೃಕೆ_ಸೂಚ್ಯಂಕ_ಸೂಚಕ_OES (GLint ಗಾತ್ರ_2, GLenum type, GLsizei stride, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ಸೂಚಕ_2);
GL_API ಶೂನ್ಯ GL_APIENTRY gl_ತೂಕ_ಸೂಚಕ_OES (GLint ಗಾತ್ರ_2, GLenum type, GLsizei stride, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ಸೂಚಕ_2);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* GL_OES_matrix_palette */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_OES_packed_ಆಳ_stencil
#ವ್ಯಾಖ್ಯಾನಿಸು GL_OES_packed_ಆಳ_stencil 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ಆಳ_STENCIL_OES              0x84F9
#ವ್ಯಾಖ್ಯಾನಿಸು GL_UNSIGNED_INT_24_8_OES          0x84FA
#ವ್ಯಾಖ್ಯಾನಿಸು GL_DEPTH24_STENCIL8_OES           0x88F0
#ಆದರೆ_ಅಂತ್ಯ /* GL_OES_packed_depth_stencil */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_OES_query_ಮಾತೃಕೆ
#ವ್ಯಾಖ್ಯಾನಿಸು GL_OES_query_ಮಾತೃಕೆ 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ GLbitfield (GL_APIENTRYP PFNGLQUERYMATRIXXOESPROC) (GLfixed *mantissa, GLint *exponent);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ GL_GLEXT_PROTOTYPES
GL_API GLbitfield GL_APIENTRY glQueryMatrixxOES (GLfixed *mantissa, GLint *exponent);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* GL_OES_query_matrix */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_OES_required_internalformat
#ವ್ಯಾಖ್ಯಾನಿಸು GL_OES_required_internalformat 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ALPHA8_OES                     0x803C
#ವ್ಯಾಖ್ಯಾನಿಸು GL_LUMINANCE4_ALPHA4_OES          0x8043
#ವ್ಯಾಖ್ಯಾನಿಸು GL_LUMINANCE8_ALPHA8_OES          0x8045
#ವ್ಯಾಖ್ಯಾನಿಸು GL_LUMINANCE8_OES                 0x8040
#ವ್ಯಾಖ್ಯಾನಿಸು GL_RGB8_OES                       0x8051
#ವ್ಯಾಖ್ಯಾನಿಸು GL_RGBA8_OES                      0x8058
#ವ್ಯಾಖ್ಯಾನಿಸು GL_RGB10_EXT                      0x8052
#ವ್ಯಾಖ್ಯಾನಿಸು GL_RGB10_A2_EXT                   0x8059
#ಆದರೆ_ಅಂತ್ಯ /* GL_OES_required_internalformat */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_OES_rgb8_rgba8
#ವ್ಯಾಖ್ಯಾನಿಸು GL_OES_rgb8_rgba8 1
#ಆದರೆ_ಅಂತ್ಯ /* GL_OES_rgb8_rgba8 */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_OES_single_precision
#ವ್ಯಾಖ್ಯಾನಿಸು GL_OES_single_precision 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLCLEARDEPTHFOESPROC) (GLclampf ಆಳ_2);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLCLIPPLANEFOESPROC) (GLenum plane, ಸ್ಥಿರಾಂಕ GLfloat *equation);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLDEPTHRANGEFOESPROC) (GLclampf n, GLclampf f);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLFRUSTUMFOESPROC) (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLGETCLIPPLANEFOESPROC) (GLenum plane, GLfloat *equation);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLORTHOFOESPROC) (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ GL_GLEXT_PROTOTYPES
GL_API ಶೂನ್ಯ GL_APIENTRY glClearDepthfOES (GLclampf ಆಳ_2);
GL_API ಶೂನ್ಯ GL_APIENTRY glClipPlanefOES (GLenum plane, ಸ್ಥಿರಾಂಕ GLfloat *equation);
GL_API ಶೂನ್ಯ GL_APIENTRY gl_ಆಳ_Rangef_OES (GLclampf n, GLclampf f);
GL_API ಶೂನ್ಯ GL_APIENTRY glFrustumfOES (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
GL_API ಶೂನ್ಯ GL_APIENTRY glGetClipPlanefOES (GLenum plane, GLfloat *equation);
GL_API ಶೂನ್ಯ GL_APIENTRY glOrthofOES (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* GL_OES_single_precision */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_OES_stencil1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_OES_stencil1 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_STENCIL_INDEX1_OES             0x8D46
#ಆದರೆ_ಅಂತ್ಯ /* GL_OES_stencil1 */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_OES_stencil4
#ವ್ಯಾಖ್ಯಾನಿಸು GL_OES_stencil4 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_STENCIL_INDEX4_OES             0x8D47
#ಆದರೆ_ಅಂತ್ಯ /* GL_OES_stencil4 */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_OES_stencil8
#ವ್ಯಾಖ್ಯಾನಿಸು GL_OES_stencil8 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_STENCIL_INDEX8_OES             0x8D48
#ಆದರೆ_ಅಂತ್ಯ /* GL_OES_stencil8 */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_OES_stencil_wrap
#ವ್ಯಾಖ್ಯಾನಿಸು GL_OES_stencil_wrap 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_INCR_WRAP_OES                  0x8507
#ವ್ಯಾಖ್ಯಾನಿಸು GL_DECR_WRAP_OES                  0x8508
#ಆದರೆ_ಅಂತ್ಯ /* GL_OES_stencil_wrap */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_OES_surfaceless_context
#ವ್ಯಾಖ್ಯಾನಿಸು GL_OES_surfaceless_context 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_FRAMEBUFFER_UNDEFINED_OES      0x8219
#ಆದರೆ_ಅಂತ್ಯ /* GL_OES_surfaceless_context */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_OES_texture_cube_map
#ವ್ಯಾಖ್ಯಾನಿಸು GL_OES_texture_cube_map 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ಸಾಮಾನ್ಯ_MAP_OES                 0x8511
#ವ್ಯಾಖ್ಯಾನಿಸು GL_REFLECTION_MAP_OES             0x8512
#ವ್ಯಾಖ್ಯಾನಿಸು GL_TEXTURE_CUBE_MAP_OES           0x8513
#ವ್ಯಾಖ್ಯಾನಿಸು GL_TEXTURE_BINDING_CUBE_MAP_OES   0x8514
#ವ್ಯಾಖ್ಯಾನಿಸು GL_TEXTURE_CUBE_MAP_ಧನಾತ್ಮಕ_X_OES 0x8515
#ವ್ಯಾಖ್ಯಾನಿಸು GL_TEXTURE_CUBE_MAP_NEGATIVE_X_OES 0x8516
#ವ್ಯಾಖ್ಯಾನಿಸು GL_TEXTURE_CUBE_MAP_ಧನಾತ್ಮಕ_Y_OES 0x8517
#ವ್ಯಾಖ್ಯಾನಿಸು GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_OES 0x8518
#ವ್ಯಾಖ್ಯಾನಿಸು GL_TEXTURE_CUBE_MAP_ಧನಾತ್ಮಕ_Z_OES 0x8519
#ವ್ಯಾಖ್ಯಾನಿಸು GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_OES 0x851A
#ವ್ಯಾಖ್ಯಾನಿಸು GL_MAX_CUBE_MAP_TEXTURE_ಗಾತ್ರ_OES  0x851C
#ವ್ಯಾಖ್ಯಾನಿಸು GL_TEXTURE_GEN_ಬಹುಲಕ_OES           0x2500
#ವ್ಯಾಖ್ಯಾನಿಸು GL_TEXTURE_GEN_STR_OES            0x8D60
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLTEXGENFOESPROC) (GLenum coord, GLenum pname, GLfloat param);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLTEXGENFVOESPROC) (GLenum coord, GLenum pname, ಸ್ಥಿರಾಂಕ GLfloat *params);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLTEXGENIOESPROC) (GLenum coord, GLenum pname, GLint param);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLTEXGENIVOESPROC) (GLenum coord, GLenum pname, ಸ್ಥಿರಾಂಕ GLint *params);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLGETTEXGENFVOESPROC) (GLenum coord, GLenum pname, GLfloat *params);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLGETTEXGENIVOESPROC) (GLenum coord, GLenum pname, GLint *params);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ GL_GLEXT_PROTOTYPES
GL_API ಶೂನ್ಯ GL_APIENTRY glTexGenfOES (GLenum coord, GLenum pname, GLfloat param);
GL_API ಶೂನ್ಯ GL_APIENTRY glTexGenfvOES (GLenum coord, GLenum pname, ಸ್ಥಿರಾಂಕ GLfloat *params);
GL_API ಶೂನ್ಯ GL_APIENTRY glTexGeniOES (GLenum coord, GLenum pname, GLint param);
GL_API ಶೂನ್ಯ GL_APIENTRY glTexGenivOES (GLenum coord, GLenum pname, ಸ್ಥಿರಾಂಕ GLint *params);
GL_API ಶೂನ್ಯ GL_APIENTRY glGetTexGenfvOES (GLenum coord, GLenum pname, GLfloat *params);
GL_API ಶೂನ್ಯ GL_APIENTRY glGetTexGenivOES (GLenum coord, GLenum pname, GLint *params);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* GL_OES_texture_cube_map */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_OES_texture_env_crossbar
#ವ್ಯಾಖ್ಯಾನಿಸು GL_OES_texture_env_crossbar 1
#ಆದರೆ_ಅಂತ್ಯ /* GL_OES_texture_env_crossbar */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_OES_texture_mirrored_repeat
#ವ್ಯಾಖ್ಯಾನಿಸು GL_OES_texture_mirrored_repeat 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_MIRRORED_REPEAT_OES            0x8370
#ಆದರೆ_ಅಂತ್ಯ /* GL_OES_texture_mirrored_repeat */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_OES_texture_npot
#ವ್ಯಾಖ್ಯಾನಿಸು GL_OES_texture_npot 1
#ಆದರೆ_ಅಂತ್ಯ /* GL_OES_texture_npot */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_OES_ಶೃಂಗ_array_object
#ವ್ಯಾಖ್ಯಾನಿಸು GL_OES_ಶೃಂಗ_array_object 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ಶೃಂಗ_ARRAY_BINDING_OES       0x85B5
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLBINDVERTEXARRAYOESPROC) (GLuint array);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLDELETEVERTEXARRAYSOESPROC) (GLsizei n, ಸ್ಥಿರಾಂಕ GLuint *arrays);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLGENVERTEXARRAYSOESPROC) (GLsizei n, GLuint *arrays);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ GLboolean (GL_APIENTRYP PFNGLISVERTEXARRAYOESPROC) (GLuint array);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ GL_GLEXT_PROTOTYPES
GL_API ಶೂನ್ಯ GL_APIENTRY gl_Bind_ಶೃಂಗ_Array_OES (GLuint array);
GL_API ಶೂನ್ಯ GL_APIENTRY gl_Delete_ಶೃಂಗ_Arrays_OES (GLsizei n, ಸ್ಥಿರಾಂಕ GLuint *arrays);
GL_API ಶೂನ್ಯ GL_APIENTRY gl_Gen_ಶೃಂಗ_Arrays_OES (GLsizei n, GLuint *arrays);
GL_API GLboolean GL_APIENTRY gl_Is_ಶೃಂಗ_Array_OES (GLuint array);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* GL_OES_vertex_array_object */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_AMD_compressed_3DC_texture
#ವ್ಯಾಖ್ಯಾನಿಸು GL_AMD_compressed_3DC_texture 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_3DC_X_AMD                      0x87F9
#ವ್ಯಾಖ್ಯಾನಿಸು GL_3DC_XY_AMD                     0x87FA
#ಆದರೆ_ಅಂತ್ಯ /* GL_AMD_compressed_3DC_texture */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_AMD_compressed_ATC_texture
#ವ್ಯಾಖ್ಯಾನಿಸು GL_AMD_compressed_ATC_texture 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ATC_RGB_AMD                    0x8C92
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ATC_RGBA_EXPLICIT_ALPHA_AMD    0x8C93
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD 0x87EE
#ಆದರೆ_ಅಂತ್ಯ /* GL_AMD_compressed_ATC_texture */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_APPLE_copy_texture_ಮಟ್ಟಗಳು
#ವ್ಯಾಖ್ಯಾನಿಸು GL_APPLE_copy_texture_ಮಟ್ಟಗಳು 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLCOPYTEXTURELEVELSAPPLEPROC) (GLuint destinationTexture, GLuint ಮೂಲ_Texture, GLint ಮೂಲ_ತಳ_Level, GLsizei ಮೂಲ_Level_ಎಣಿಕೆ);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ GL_GLEXT_PROTOTYPES
GL_API ಶೂನ್ಯ GL_APIENTRY gl_Copy_Texture_ಮಟ್ಟಗಳು_APPLE (GLuint destinationTexture, GLuint ಮೂಲ_Texture, GLint ಮೂಲ_ತಳ_Level, GLsizei ಮೂಲ_Level_ಎಣಿಕೆ);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* GL_APPLE_copy_texture_levels */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_APPLE_framebuffer_multisample
#ವ್ಯಾಖ್ಯಾನಿಸು GL_APPLE_framebuffer_multisample 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_RENDERBUFFER_SAMPLES_APPLE     0x8CAB
#ವ್ಯಾಖ್ಯಾನಿಸು GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_APPLE 0x8D56
#ವ್ಯಾಖ್ಯಾನಿಸು GL_MAX_SAMPLES_APPLE              0x8D57
#ವ್ಯಾಖ್ಯಾನಿಸು GL_READ_FRAMEBUFFER_APPLE         0x8CA8
#ವ್ಯಾಖ್ಯಾನಿಸು GL_DRAW_FRAMEBUFFER_APPLE         0x8CA9
#ವ್ಯಾಖ್ಯಾನಿಸು GL_DRAW_FRAMEBUFFER_BINDING_APPLE 0x8CA6
#ವ್ಯಾಖ್ಯಾನಿಸು GL_READ_FRAMEBUFFER_BINDING_APPLE 0x8CAA
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEAPPLEPROC) (GLenum ಗುರಿ, GLsizei samples, GLenum internalformat, GLsizei ಅಗಲ, GLsizei ಎತ್ತರ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLRESOLVEMULTISAMPLEFRAMEBUFFERAPPLEPROC) (ಶೂನ್ಯ);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ GL_GLEXT_PROTOTYPES
GL_API ಶೂನ್ಯ GL_APIENTRY glRenderbufferStorageMultisampleAPPLE (GLenum ಗುರಿ, GLsizei samples, GLenum internalformat, GLsizei ಅಗಲ, GLsizei ಎತ್ತರ);
GL_API ಶೂನ್ಯ GL_APIENTRY glResolveMultisampleFramebufferAPPLE (ಶೂನ್ಯ);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* GL_APPLE_framebuffer_multisample */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_APPLE_sync
#ವ್ಯಾಖ್ಯಾನಿಸು GL_APPLE_sync 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ __GLsync *GLsync;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ khronos_uint64_t GLuint64;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ khronos_int64_t GLint64;
#ವ್ಯಾಖ್ಯಾನಿಸು GL_SYNC_OBJECT_APPLE              0x8A53
#ವ್ಯಾಖ್ಯಾನಿಸು GL_MAX_SERVER_WAIT_TIMEOUT_APPLE  0x9111
#ವ್ಯಾಖ್ಯಾನಿಸು GL_OBJECT_TYPE_APPLE              0x9112
#ವ್ಯಾಖ್ಯಾನಿಸು GL_SYNC_CONDITION_APPLE           0x9113
#ವ್ಯಾಖ್ಯಾನಿಸು GL_SYNC_ಸ್ಥಿತಿ_APPLE              0x9114
#ವ್ಯಾಖ್ಯಾನಿಸು GL_SYNC_FLAGS_APPLE               0x9115
#ವ್ಯಾಖ್ಯಾನಿಸು GL_SYNC_FENCE_APPLE               0x9116
#ವ್ಯಾಖ್ಯಾನಿಸು GL_SYNC_GPU_COMMANDS_COMPLETE_APPLE 0x9117
#ವ್ಯಾಖ್ಯಾನಿಸು GL_UNSIGNALED_APPLE               0x9118
#ವ್ಯಾಖ್ಯಾನಿಸು GL_SIGNALED_APPLE                 0x9119
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ALREADY_SIGNALED_APPLE         0x911A
#ವ್ಯಾಖ್ಯಾನಿಸು GL_TIMEOUT_EXPIRED_APPLE          0x911B
#ವ್ಯಾಖ್ಯಾನಿಸು GL_CONDITION_SATISFIED_APPLE      0x911C
#ವ್ಯಾಖ್ಯಾನಿಸು GL_WAIT_FAILED_APPLE              0x911D
#ವ್ಯಾಖ್ಯಾನಿಸು GL_SYNC_FLUSH_COMMANDS_ಬಿಟ್_APPLE  0x00000001
#ವ್ಯಾಖ್ಯಾನಿಸು GL_TIMEOUT_IGNORED_APPLE          0xFFFFFFFFFFFFFFFFull
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ GLsync (GL_APIENTRYP PFNGLFENCESYNCAPPLEPROC) (GLenum condition, GLbitfield flags);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ GLboolean (GL_APIENTRYP PFNGLISSYNCAPPLEPROC) (GLsync sync);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLDELETESYNCAPPLEPROC) (GLsync sync);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ GLenum (GL_APIENTRYP PFNGLCLIENTWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLGETINTEGER64VAPPLEPROC) (GLenum pname, GLint64 *params);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLGETSYNCIVAPPLEPROC) (GLsync sync, GLenum pname, GLsizei ಎಣಿಕೆ_2, GLsizei *ಉದ್ದಳತೆ, GLint *ಮೌಲ್ಯಗಳು);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ GL_GLEXT_PROTOTYPES
GL_API GLsync GL_APIENTRY glFenceSyncAPPLE (GLenum condition, GLbitfield flags);
GL_API GLboolean GL_APIENTRY glIsSyncAPPLE (GLsync sync);
GL_API ಶೂನ್ಯ GL_APIENTRY glDeleteSyncAPPLE (GLsync sync);
GL_API GLenum GL_APIENTRY glClientWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_API ಶೂನ್ಯ GL_APIENTRY glWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_API ಶೂನ್ಯ GL_APIENTRY glGetInteger64vAPPLE (GLenum pname, GLint64 *params);
GL_API ಶೂನ್ಯ GL_APIENTRY glGetSyncivAPPLE (GLsync sync, GLenum pname, GLsizei ಎಣಿಕೆ_2, GLsizei *ಉದ್ದಳತೆ, GLint *ಮೌಲ್ಯಗಳು);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* GL_APPLE_sync */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_APPLE_texture_2D_limited_npot
#ವ್ಯಾಖ್ಯಾನಿಸು GL_APPLE_texture_2D_limited_npot 1
#ಆದರೆ_ಅಂತ್ಯ /* GL_APPLE_texture_2D_limited_npot */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_APPLE_texture_format_BGRA8888
#ವ್ಯಾಖ್ಯಾನಿಸು GL_APPLE_texture_format_BGRA8888 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_BGRA_EXT                       0x80E1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_BGRA8_EXT                      0x93A1
#ಆದರೆ_ಅಂತ್ಯ /* GL_APPLE_texture_format_BGRA8888 */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_APPLE_texture_max_level
#ವ್ಯಾಖ್ಯಾನಿಸು GL_APPLE_texture_max_level 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_TEXTURE_MAX_LEVEL_APPLE        0x813D
#ಆದರೆ_ಅಂತ್ಯ /* GL_APPLE_texture_max_level */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_ARM_rgba8
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ARM_rgba8 1
#ಆದರೆ_ಅಂತ್ಯ /* GL_ARM_rgba8 */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_EXT_blend_minmax
#ವ್ಯಾಖ್ಯಾನಿಸು GL_EXT_blend_minmax 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_MIN_EXT                        0x8007
#ವ್ಯಾಖ್ಯಾನಿಸು GL_MAX_EXT                        0x8008
#ಆದರೆ_ಅಂತ್ಯ /* GL_EXT_blend_minmax */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_EXT_debug_marker
#ವ್ಯಾಖ್ಯಾನಿಸು GL_EXT_debug_marker 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಅಕ್ಷರ GLchar;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLINSERTEVENTMARKEREXTPROC) (GLsizei ಉದ್ದಳತೆ, ಸ್ಥಿರಾಂಕ GLchar *marker);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLPUSHGROUPMARKEREXTPROC) (GLsizei ಉದ್ದಳತೆ, ಸ್ಥಿರಾಂಕ GLchar *marker);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLPOPGROUPMARKEREXTPROC) (ಶೂನ್ಯ);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ GL_GLEXT_PROTOTYPES
GL_API ಶೂನ್ಯ GL_APIENTRY gl_ಸೇರಿಸು_Event_Marker_EXT (GLsizei ಉದ್ದಳತೆ, ಸ್ಥಿರಾಂಕ GLchar *marker);
GL_API ಶೂನ್ಯ GL_APIENTRY gl_ತಳ್ಳು_ಗುಂಪು_Marker_EXT (GLsizei ಉದ್ದಳತೆ, ಸ್ಥಿರಾಂಕ GLchar *marker);
GL_API ಶೂನ್ಯ GL_APIENTRY gl_ತೆಗೆ_ಗುಂಪು_Marker_EXT (ಶೂನ್ಯ);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* GL_EXT_debug_marker */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_EXT_discard_framebuffer
#ವ್ಯಾಖ್ಯಾನಿಸು GL_EXT_discard_framebuffer 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_COLOR_EXT                      0x1800
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ಆಳ_EXT                      0x1801
#ವ್ಯಾಖ್ಯಾನಿಸು GL_STENCIL_EXT                    0x1802
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLDISCARDFRAMEBUFFEREXTPROC) (GLenum ಗುರಿ, GLsizei ಅಂಕೆ_Attachments, ಸ್ಥಿರಾಂಕ GLenum *attachments);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ GL_GLEXT_PROTOTYPES
GL_API ಶೂನ್ಯ GL_APIENTRY glDiscardFramebufferEXT (GLenum ಗುರಿ, GLsizei ಅಂಕೆ_Attachments, ಸ್ಥಿರಾಂಕ GLenum *attachments);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* GL_EXT_discard_framebuffer */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_EXT_map_ಬಫರ್_range
#ವ್ಯಾಖ್ಯಾನಿಸು GL_EXT_map_ಬಫರ್_range 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_MAP_READ_ಬಿಟ್_EXT               0x0001
#ವ್ಯಾಖ್ಯಾನಿಸು GL_MAP_WRITE_ಬಿಟ್_EXT              0x0002
#ವ್ಯಾಖ್ಯಾನಿಸು GL_MAP_INVALIDATE_RANGE_ಬಿಟ್_EXT   0x0004
#ವ್ಯಾಖ್ಯಾನಿಸು GL_MAP_INVALIDATE_ಬಫರ್_ಬಿಟ್_EXT  0x0008
#ವ್ಯಾಖ್ಯಾನಿಸು GL_MAP_FLUSH_EXPLICIT_ಬಿಟ್_EXT     0x0010
#ವ್ಯಾಖ್ಯಾನಿಸು GL_MAP_UNSYNCHRONIZED_ಬಿಟ್_EXT     0x0020
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ *(GL_APIENTRYP PFNGLMAPBUFFERRANGEEXTPROC) (GLenum ಗುರಿ, GLintptr ಸ್ಥಾನಾಂತರ_2, GLsizeiptr ಉದ್ದಳತೆ, GLbitfield access);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEEXTPROC) (GLenum ಗುರಿ, GLintptr ಸ್ಥಾನಾಂತರ_2, GLsizeiptr ಉದ್ದಳತೆ);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ GL_GLEXT_PROTOTYPES
GL_API ಶೂನ್ಯ *GL_APIENTRY gl_Map_ಬಫರ್_Range_EXT (GLenum ಗುರಿ, GLintptr ಸ್ಥಾನಾಂತರ_2, GLsizeiptr ಉದ್ದಳತೆ, GLbitfield access);
GL_API ಶೂನ್ಯ GL_APIENTRY gl_Flush_Mapped_ಬಫರ್_Range_EXT (GLenum ಗುರಿ, GLintptr ಸ್ಥಾನಾಂತರ_2, GLsizeiptr ಉದ್ದಳತೆ);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* GL_EXT_map_buffer_range */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_EXT_multi_draw_arrays
#ವ್ಯಾಖ್ಯಾನಿಸು GL_EXT_multi_draw_arrays 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLMULTIDRAWARRAYSEXTPROC) (GLenum ಬಹುಲಕ, ಸ್ಥಿರಾಂಕ GLint *ಮೊದಲ, ಸ್ಥಿರಾಂಕ GLsizei *ಎಣಿಕೆ_2, GLsizei primcount);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSEXTPROC) (GLenum ಬಹುಲಕ, ಸ್ಥಿರಾಂಕ GLsizei *ಎಣಿಕೆ_2, GLenum type, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ಸ್ಥಿರಾಂಕ*indices, GLsizei primcount);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ GL_GLEXT_PROTOTYPES
GL_API ಶೂನ್ಯ GL_APIENTRY glMultiDrawArraysEXT (GLenum ಬಹುಲಕ, ಸ್ಥಿರಾಂಕ GLint *ಮೊದಲ, ಸ್ಥಿರಾಂಕ GLsizei *ಎಣಿಕೆ_2, GLsizei primcount);
GL_API ಶೂನ್ಯ GL_APIENTRY glMultiDrawElementsEXT (GLenum ಬಹುಲಕ, ಸ್ಥಿರಾಂಕ GLsizei *ಎಣಿಕೆ_2, GLenum type, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ಸ್ಥಿರಾಂಕ*indices, GLsizei primcount);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* GL_EXT_multi_draw_arrays */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_EXT_multisampled_render_ಗಮ್ಯ_texture
#ವ್ಯಾಖ್ಯಾನಿಸು GL_EXT_multisampled_render_ಗಮ್ಯ_texture 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SAMPLES_EXT 0x8D6C
#ವ್ಯಾಖ್ಯಾನಿಸು GL_RENDERBUFFER_SAMPLES_EXT       0x8CAB
#ವ್ಯಾಖ್ಯಾನಿಸು GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT 0x8D56
#ವ್ಯಾಖ್ಯಾನಿಸು GL_MAX_SAMPLES_EXT                0x8D57
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) (GLenum ಗುರಿ, GLsizei samples, GLenum internalformat, GLsizei ಅಗಲ, GLsizei ಎತ್ತರ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEEXTPROC) (GLenum ಗುರಿ, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ GL_GLEXT_PROTOTYPES
GL_API ಶೂನ್ಯ GL_APIENTRY glRenderbufferStorageMultisampleEXT (GLenum ಗುರಿ, GLsizei samples, GLenum internalformat, GLsizei ಅಗಲ, GLsizei ಎತ್ತರ);
GL_API ಶೂನ್ಯ GL_APIENTRY glFramebufferTexture2DMultisampleEXT (GLenum ಗುರಿ, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* GL_EXT_multisampled_render_to_texture */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_EXT_read_format_bgra
#ವ್ಯಾಖ್ಯಾನಿಸು GL_EXT_read_format_bgra 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT 0x8365
#ವ್ಯಾಖ್ಯಾನಿಸು GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT 0x8366
#ಆದರೆ_ಅಂತ್ಯ /* GL_EXT_read_format_bgra */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_EXT_robustness
#ವ್ಯಾಖ್ಯಾನಿಸು GL_EXT_robustness 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_GUILTY_CONTEXT_RESET_EXT       0x8253
#ವ್ಯಾಖ್ಯಾನಿಸು GL_INNOCENT_CONTEXT_RESET_EXT     0x8254
#ವ್ಯಾಖ್ಯಾನಿಸು GL_UNKNOWN_CONTEXT_RESET_EXT      0x8255
#ವ್ಯಾಖ್ಯಾನಿಸು GL_CONTEXT_ROBUST_ACCESS_EXT      0x90F3
#ವ್ಯಾಖ್ಯಾನಿಸು GL_RESET_NOTIFICATION_STRATEGY_EXT 0x8256
#ವ್ಯಾಖ್ಯಾನಿಸು GL_LOSE_CONTEXT_ON_RESET_EXT      0x8252
#ವ್ಯಾಖ್ಯಾನಿಸು GL_NO_RESET_NOTIFICATION_EXT      0x8261
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ GLenum (GL_APIENTRYP PFNGLGETGRAPHICSRESETSTATUSEXTPROC) (ಶೂನ್ಯ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLREADNPIXELSEXTPROC) (GLint x, GLint y, GLsizei ಅಗಲ, GLsizei ಎತ್ತರ, GLenum format, GLenum type, GLsizei buf_ಗಾತ್ರ, ಶೂನ್ಯ *ದತ್ತಾಂಶ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLGETNUNIFORMFVEXTPROC) (GLuint ಕಾರ್ಯಕ್ರಮ, GLint location, GLsizei buf_ಗಾತ್ರ, GLfloat *params);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLGETNUNIFORMIVEXTPROC) (GLuint ಕಾರ್ಯಕ್ರಮ, GLint location, GLsizei buf_ಗಾತ್ರ, GLint *params);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ GL_GLEXT_PROTOTYPES
GL_API GLenum GL_APIENTRY gl_Get_Graphics_Reset_ಸ್ಥಿತಿ_EXT (ಶೂನ್ಯ);
GL_API ಶೂನ್ಯ GL_APIENTRY glReadnPixelsEXT (GLint x, GLint y, GLsizei ಅಗಲ, GLsizei ಎತ್ತರ, GLenum format, GLenum type, GLsizei buf_ಗಾತ್ರ, ಶೂನ್ಯ *ದತ್ತಾಂಶ);
GL_API ಶೂನ್ಯ GL_APIENTRY glGetnUniformfvEXT (GLuint ಕಾರ್ಯಕ್ರಮ, GLint location, GLsizei buf_ಗಾತ್ರ, GLfloat *params);
GL_API ಶೂನ್ಯ GL_APIENTRY glGetnUniformivEXT (GLuint ಕಾರ್ಯಕ್ರಮ, GLint location, GLsizei buf_ಗಾತ್ರ, GLint *params);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* GL_EXT_robustness */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_EXT_sRGB
#ವ್ಯಾಖ್ಯಾನಿಸು GL_EXT_sRGB 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_SRGB_EXT                       0x8C40
#ವ್ಯಾಖ್ಯಾನಿಸು GL_SRGB_ALPHA_EXT                 0x8C42
#ವ್ಯಾಖ್ಯಾನಿಸು GL_SRGB8_ALPHA8_EXT               0x8C43
#ವ್ಯಾಖ್ಯಾನಿಸು GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING_EXT 0x8210
#ಆದರೆ_ಅಂತ್ಯ /* GL_EXT_sRGB */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_EXT_texture_compression_dxt1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_EXT_texture_compression_dxt1 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_COMPRESSED_RGB_S3TC_DXT1_EXT   0x83F0
#ವ್ಯಾಖ್ಯಾನಿಸು GL_COMPRESSED_RGBA_S3TC_DXT1_EXT  0x83F1
#ಆದರೆ_ಅಂತ್ಯ /* GL_EXT_texture_compression_dxt1 */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_EXT_texture_filter_anisotropic
#ವ್ಯಾಖ್ಯಾನಿಸು GL_EXT_texture_filter_anisotropic 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#ವ್ಯಾಖ್ಯಾನಿಸು GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#ಆದರೆ_ಅಂತ್ಯ /* GL_EXT_texture_filter_anisotropic */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_EXT_texture_format_BGRA8888
#ವ್ಯಾಖ್ಯಾನಿಸು GL_EXT_texture_format_BGRA8888 1
#ಆದರೆ_ಅಂತ್ಯ /* GL_EXT_texture_format_BGRA8888 */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_EXT_texture_lod_bias
#ವ್ಯಾಖ್ಯಾನಿಸು GL_EXT_texture_lod_bias 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_MAX_TEXTURE_LOD_BIAS_EXT       0x84FD
#ವ್ಯಾಖ್ಯಾನಿಸು GL_TEXTURE_FILTER_CONTROL_EXT     0x8500
#ವ್ಯಾಖ್ಯಾನಿಸು GL_TEXTURE_LOD_BIAS_EXT           0x8501
#ಆದರೆ_ಅಂತ್ಯ /* GL_EXT_texture_lod_bias */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_EXT_texture_storage
#ವ್ಯಾಖ್ಯಾನಿಸು GL_EXT_texture_storage 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_TEXTURE_IMMUTABLE_FORMAT_EXT   0x912F
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ALPHA8_EXT                     0x803C
#ವ್ಯಾಖ್ಯಾನಿಸು GL_LUMINANCE8_EXT                 0x8040
#ವ್ಯಾಖ್ಯಾನಿಸು GL_LUMINANCE8_ALPHA8_EXT          0x8045
#ವ್ಯಾಖ್ಯಾನಿಸು GL_RGBA32F_EXT                    0x8814
#ವ್ಯಾಖ್ಯಾನಿಸು GL_RGB32F_EXT                     0x8815
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ALPHA32F_EXT                   0x8816
#ವ್ಯಾಖ್ಯಾನಿಸು GL_LUMINANCE32F_EXT               0x8818
#ವ್ಯಾಖ್ಯಾನಿಸು GL_LUMINANCE_ALPHA32F_EXT         0x8819
#ವ್ಯಾಖ್ಯಾನಿಸು GL_RGBA16F_EXT                    0x881A
#ವ್ಯಾಖ್ಯಾನಿಸು GL_RGB16F_EXT                     0x881B
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ALPHA16F_EXT                   0x881C
#ವ್ಯಾಖ್ಯಾನಿಸು GL_LUMINANCE16F_EXT               0x881E
#ವ್ಯಾಖ್ಯಾನಿಸು GL_LUMINANCE_ALPHA16F_EXT         0x881F
#ವ್ಯಾಖ್ಯಾನಿಸು GL_R8_EXT                         0x8229
#ವ್ಯಾಖ್ಯಾನಿಸು GL_RG8_EXT                        0x822B
#ವ್ಯಾಖ್ಯಾನಿಸು GL_R32F_EXT                       0x822E
#ವ್ಯಾಖ್ಯಾನಿಸು GL_RG32F_EXT                      0x8230
#ವ್ಯಾಖ್ಯಾನಿಸು GL_R16F_EXT                       0x822D
#ವ್ಯಾಖ್ಯಾನಿಸು GL_RG16F_EXT                      0x822F
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLTEXSTORAGE1DEXTPROC) (GLenum ಗುರಿ, GLsizei ಮಟ್ಟಗಳು, GLenum internalformat, GLsizei ಅಗಲ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLTEXSTORAGE2DEXTPROC) (GLenum ಗುರಿ, GLsizei ಮಟ್ಟಗಳು, GLenum internalformat, GLsizei ಅಗಲ, GLsizei ಎತ್ತರ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLTEXSTORAGE3DEXTPROC) (GLenum ಗುರಿ, GLsizei ಮಟ್ಟಗಳು, GLenum internalformat, GLsizei ಅಗಲ, GLsizei ಎತ್ತರ, GLsizei ಆಳ_2);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLTEXTURESTORAGE1DEXTPROC) (GLuint texture, GLenum ಗುರಿ, GLsizei ಮಟ್ಟಗಳು, GLenum internalformat, GLsizei ಅಗಲ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLTEXTURESTORAGE2DEXTPROC) (GLuint texture, GLenum ಗುರಿ, GLsizei ಮಟ್ಟಗಳು, GLenum internalformat, GLsizei ಅಗಲ, GLsizei ಎತ್ತರ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLTEXTURESTORAGE3DEXTPROC) (GLuint texture, GLenum ಗುರಿ, GLsizei ಮಟ್ಟಗಳು, GLenum internalformat, GLsizei ಅಗಲ, GLsizei ಎತ್ತರ, GLsizei ಆಳ_2);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ GL_GLEXT_PROTOTYPES
GL_API ಶೂನ್ಯ GL_APIENTRY glTexStorage1DEXT (GLenum ಗುರಿ, GLsizei ಮಟ್ಟಗಳು, GLenum internalformat, GLsizei ಅಗಲ);
GL_API ಶೂನ್ಯ GL_APIENTRY glTexStorage2DEXT (GLenum ಗುರಿ, GLsizei ಮಟ್ಟಗಳು, GLenum internalformat, GLsizei ಅಗಲ, GLsizei ಎತ್ತರ);
GL_API ಶೂನ್ಯ GL_APIENTRY glTexStorage3DEXT (GLenum ಗುರಿ, GLsizei ಮಟ್ಟಗಳು, GLenum internalformat, GLsizei ಅಗಲ, GLsizei ಎತ್ತರ, GLsizei ಆಳ_2);
GL_API ಶೂನ್ಯ GL_APIENTRY glTextureStorage1DEXT (GLuint texture, GLenum ಗುರಿ, GLsizei ಮಟ್ಟಗಳು, GLenum internalformat, GLsizei ಅಗಲ);
GL_API ಶೂನ್ಯ GL_APIENTRY glTextureStorage2DEXT (GLuint texture, GLenum ಗುರಿ, GLsizei ಮಟ್ಟಗಳು, GLenum internalformat, GLsizei ಅಗಲ, GLsizei ಎತ್ತರ);
GL_API ಶೂನ್ಯ GL_APIENTRY glTextureStorage3DEXT (GLuint texture, GLenum ಗುರಿ, GLsizei ಮಟ್ಟಗಳು, GLenum internalformat, GLsizei ಅಗಲ, GLsizei ಎತ್ತರ, GLsizei ಆಳ_2);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* GL_EXT_texture_storage */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_IMG_multisampled_render_ಗಮ್ಯ_texture
#ವ್ಯಾಖ್ಯಾನಿಸು GL_IMG_multisampled_render_ಗಮ್ಯ_texture 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_RENDERBUFFER_SAMPLES_IMG       0x9133
#ವ್ಯಾಖ್ಯಾನಿಸು GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_IMG 0x9134
#ವ್ಯಾಖ್ಯಾನಿಸು GL_MAX_SAMPLES_IMG                0x9135
#ವ್ಯಾಖ್ಯಾನಿಸು GL_TEXTURE_SAMPLES_IMG            0x9136
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEIMGPROC) (GLenum ಗುರಿ, GLsizei samples, GLenum internalformat, GLsizei ಅಗಲ, GLsizei ಎತ್ತರ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEIMGPROC) (GLenum ಗುರಿ, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ GL_GLEXT_PROTOTYPES
GL_API ಶೂನ್ಯ GL_APIENTRY glRenderbufferStorageMultisampleIMG (GLenum ಗುರಿ, GLsizei samples, GLenum internalformat, GLsizei ಅಗಲ, GLsizei ಎತ್ತರ);
GL_API ಶೂನ್ಯ GL_APIENTRY glFramebufferTexture2DMultisampleIMG (GLenum ಗುರಿ, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* GL_IMG_multisampled_render_to_texture */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_IMG_read_format
#ವ್ಯಾಖ್ಯಾನಿಸು GL_IMG_read_format 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_BGRA_IMG                       0x80E1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_UNSIGNED_SHORT_4_4_4_4_REV_IMG 0x8365
#ಆದರೆ_ಅಂತ್ಯ /* GL_IMG_read_format */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_IMG_texture_compression_pvrtc
#ವ್ಯಾಖ್ಯಾನಿಸು GL_IMG_texture_compression_pvrtc 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG 0x8C00
#ವ್ಯಾಖ್ಯಾನಿಸು GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG 0x8C01
#ವ್ಯಾಖ್ಯಾನಿಸು GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG 0x8C02
#ವ್ಯಾಖ್ಯಾನಿಸು GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG 0x8C03
#ಆದರೆ_ಅಂತ್ಯ /* GL_IMG_texture_compression_pvrtc */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_IMG_texture_env_enhanced_fixed_function
#ವ್ಯಾಖ್ಯಾನಿಸು GL_IMG_texture_env_enhanced_fixed_function 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_MODULATE_COLOR_IMG             0x8C04
#ವ್ಯಾಖ್ಯಾನಿಸು GL_RECIP_ಕೂಡಿಸು_SIGNED_ALPHA_IMG     0x8C05
#ವ್ಯಾಖ್ಯಾನಿಸು GL_TEXTURE_ALPHA_MODULATE_IMG     0x8C06
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ಗುಣಕ_ALPHA_MODULATE_IMG      0x8C07
#ವ್ಯಾಖ್ಯಾನಿಸು GL_FRAGMENT_ALPHA_MODULATE_IMG    0x8C08
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ಕೂಡಿಸು_BLEND_IMG                  0x8C09
#ವ್ಯಾಖ್ಯಾನಿಸು GL_DOT3_RGBA_IMG                  0x86AF
#ಆದರೆ_ಅಂತ್ಯ /* GL_IMG_texture_env_enhanced_fixed_function */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_IMG_user_clip_plane
#ವ್ಯಾಖ್ಯಾನಿಸು GL_IMG_user_clip_plane 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_CLIP_PLANE0_IMG                0x3000
#ವ್ಯಾಖ್ಯಾನಿಸು GL_CLIP_PLANE1_IMG                0x3001
#ವ್ಯಾಖ್ಯಾನಿಸು GL_CLIP_PLANE2_IMG                0x3002
#ವ್ಯಾಖ್ಯಾನಿಸು GL_CLIP_PLANE3_IMG                0x3003
#ವ್ಯಾಖ್ಯಾನಿಸು GL_CLIP_PLANE4_IMG                0x3004
#ವ್ಯಾಖ್ಯಾನಿಸು GL_CLIP_PLANE5_IMG                0x3005
#ವ್ಯಾಖ್ಯಾನಿಸು GL_MAX_CLIP_PLANES_IMG            0x0D32
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLCLIPPLANEFIMGPROC) (GLenum p, ಸ್ಥಿರಾಂಕ GLfloat *eqn);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLCLIPPLANEXIMGPROC) (GLenum p, ಸ್ಥಿರಾಂಕ GLfixed *eqn);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ GL_GLEXT_PROTOTYPES
GL_API ಶೂನ್ಯ GL_APIENTRY glClipPlanefIMG (GLenum p, ಸ್ಥಿರಾಂಕ GLfloat *eqn);
GL_API ಶೂನ್ಯ GL_APIENTRY glClipPlanexIMG (GLenum p, ಸ್ಥಿರಾಂಕ GLfixed *eqn);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* GL_IMG_user_clip_plane */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_NV_fence
#ವ್ಯಾಖ್ಯಾನಿಸು GL_NV_fence 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ALL_COMPLETED_NV               0x84F2
#ವ್ಯಾಖ್ಯಾನಿಸು GL_FENCE_ಸ್ಥಿತಿ_NV                0x84F3
#ವ್ಯಾಖ್ಯಾನಿಸು GL_FENCE_CONDITION_NV             0x84F4
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLDELETEFENCESNVPROC) (GLsizei n, ಸ್ಥಿರಾಂಕ GLuint *fences);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLGENFENCESNVPROC) (GLsizei n, GLuint *fences);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ GLboolean (GL_APIENTRYP PFNGLISFENCENVPROC) (GLuint fence);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ GLboolean (GL_APIENTRYP PFNGLTESTFENCENVPROC) (GLuint fence);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLGETFENCEIVNVPROC) (GLuint fence, GLenum pname, GLint *params);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLFINISHFENCENVPROC) (GLuint fence);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLSETFENCENVPROC) (GLuint fence, GLenum condition);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ GL_GLEXT_PROTOTYPES
GL_API ಶೂನ್ಯ GL_APIENTRY glDeleteFencesNV (GLsizei n, ಸ್ಥಿರಾಂಕ GLuint *fences);
GL_API ಶೂನ್ಯ GL_APIENTRY glGenFencesNV (GLsizei n, GLuint *fences);
GL_API GLboolean GL_APIENTRY glIsFenceNV (GLuint fence);
GL_API GLboolean GL_APIENTRY glTestFenceNV (GLuint fence);
GL_API ಶೂನ್ಯ GL_APIENTRY glGetFenceivNV (GLuint fence, GLenum pname, GLint *params);
GL_API ಶೂನ್ಯ GL_APIENTRY gl_ಮುಕ್ತಾಯ_Fence_NV (GLuint fence);
GL_API ಶೂನ್ಯ GL_APIENTRY gl_ಗಣ_Fence_NV (GLuint fence, GLenum condition);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* GL_NV_fence */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_QCOM_driver_control
#ವ್ಯಾಖ್ಯಾನಿಸು GL_QCOM_driver_control 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLGETDRIVERCONTROLSQCOMPROC) (GLint *ಅಂಕೆ, GLsizei ಗಾತ್ರ_2, GLuint *driverControls);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLGETDRIVERCONTROLSTRINGQCOMPROC) (GLuint driverControl, GLsizei buf_ಗಾತ್ರ, GLsizei *ಉದ್ದಳತೆ, GLchar *driverControlString);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLENABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLDISABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ GL_GLEXT_PROTOTYPES
GL_API ಶೂನ್ಯ GL_APIENTRY glGetDriverControlsQCOM (GLint *ಅಂಕೆ, GLsizei ಗಾತ್ರ_2, GLuint *driverControls);
GL_API ಶೂನ್ಯ GL_APIENTRY glGetDriverControlStringQCOM (GLuint driverControl, GLsizei buf_ಗಾತ್ರ, GLsizei *ಉದ್ದಳತೆ, GLchar *driverControlString);
GL_API ಶೂನ್ಯ GL_APIENTRY glEnableDriverControlQCOM (GLuint driverControl);
GL_API ಶೂನ್ಯ GL_APIENTRY glDisableDriverControlQCOM (GLuint driverControl);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* GL_QCOM_driver_control */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_QCOM_extended_get
#ವ್ಯಾಖ್ಯಾನಿಸು GL_QCOM_extended_get 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_TEXTURE_ಅಗಲ_QCOM             0x8BD2
#ವ್ಯಾಖ್ಯಾನಿಸು GL_TEXTURE_ಎತ್ತರ_QCOM            0x8BD3
#ವ್ಯಾಖ್ಯಾನಿಸು GL_TEXTURE_ಆಳ_QCOM             0x8BD4
#ವ್ಯಾಖ್ಯಾನಿಸು GL_TEXTURE_ಆಂತರಿಕ_FORMAT_QCOM   0x8BD5
#ವ್ಯಾಖ್ಯಾನಿಸು GL_TEXTURE_FORMAT_QCOM            0x8BD6
#ವ್ಯಾಖ್ಯಾನಿಸು GL_TEXTURE_TYPE_QCOM              0x8BD7
#ವ್ಯಾಖ್ಯಾನಿಸು GL_TEXTURE_IMAGE_VALID_QCOM       0x8BD8
#ವ್ಯಾಖ್ಯಾನಿಸು GL_TEXTURE_ಅಂಕೆ_ಮಟ್ಟಗಳು_QCOM        0x8BD9
#ವ್ಯಾಖ್ಯಾನಿಸು GL_TEXTURE_ಗುರಿ_QCOM            0x8BDA
#ವ್ಯಾಖ್ಯಾನಿಸು GL_TEXTURE_OBJECT_VALID_QCOM      0x8BDB
#ವ್ಯಾಖ್ಯಾನಿಸು GL_STATE_RESTORE                  0x8BDC
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLEXTGETTEXTURESQCOMPROC) (GLuint *textures, GLint maxTextures, GLint *ಅಂಕೆ_Textures);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLEXTGETBUFFERSQCOMPROC) (GLuint *buffers, GLint maxBuffers, GLint *ಅಂಕೆ_Buffers);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLEXTGETRENDERBUFFERSQCOMPROC) (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *ಅಂಕೆ_Renderbuffers);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLEXTGETFRAMEBUFFERSQCOMPROC) (GLuint *framebuffers, GLint maxFramebuffers, GLint *ಅಂಕೆ_Framebuffers);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLEXTGETTEXLEVELPARAMETERIVQCOMPROC) (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLEXTTEXOBJECTSTATEOVERRIDEIQCOMPROC) (GLenum ಗುರಿ, GLenum pname, GLint param);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLEXTGETTEXSUBIMAGEQCOMPROC) (GLenum ಗುರಿ, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei ಅಗಲ, GLsizei ಎತ್ತರ, GLsizei ಆಳ_2, GLenum format, GLenum type, ಶೂನ್ಯ *texels);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLEXTGETBUFFERPOINTERVQCOMPROC) (GLenum ಗುರಿ, ಶೂನ್ಯ **params);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ GL_GLEXT_PROTOTYPES
GL_API ಶೂನ್ಯ GL_APIENTRY glExtGetTexturesQCOM (GLuint *textures, GLint maxTextures, GLint *ಅಂಕೆ_Textures);
GL_API ಶೂನ್ಯ GL_APIENTRY glExtGetBuffersQCOM (GLuint *buffers, GLint maxBuffers, GLint *ಅಂಕೆ_Buffers);
GL_API ಶೂನ್ಯ GL_APIENTRY glExtGetRenderbuffersQCOM (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *ಅಂಕೆ_Renderbuffers);
GL_API ಶೂನ್ಯ GL_APIENTRY glExtGetFramebuffersQCOM (GLuint *framebuffers, GLint maxFramebuffers, GLint *ಅಂಕೆ_Framebuffers);
GL_API ಶೂನ್ಯ GL_APIENTRY glExtGetTexLevelParameterivQCOM (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
GL_API ಶೂನ್ಯ GL_APIENTRY glExtTexObjectStateOverrideiQCOM (GLenum ಗುರಿ, GLenum pname, GLint param);
GL_API ಶೂನ್ಯ GL_APIENTRY glExtGetTexSubImageQCOM (GLenum ಗುರಿ, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei ಅಗಲ, GLsizei ಎತ್ತರ, GLsizei ಆಳ_2, GLenum format, GLenum type, ಶೂನ್ಯ *texels);
GL_API ಶೂನ್ಯ GL_APIENTRY gl_Ext_Get_ಬಫರ್_Pointerv_QCOM (GLenum ಗುರಿ, ಶೂನ್ಯ **params);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* GL_QCOM_extended_get */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_QCOM_extended_get2
#ವ್ಯಾಖ್ಯಾನಿಸು GL_QCOM_extended_get2 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLEXTGETSHADERSQCOMPROC) (GLuint *shaders, GLint maxShaders, GLint *ಅಂಕೆ_Shaders);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLEXTGETPROGRAMSQCOMPROC) (GLuint *programs, GLint maxPrograms, GLint *ಅಂಕೆ_Programs);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ GLboolean (GL_APIENTRYP PFNGLEXTISPROGRAMBINARYQCOMPROC) (GLuint ಕಾರ್ಯಕ್ರಮ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLEXTGETPROGRAMBINARYSOURCEQCOMPROC) (GLuint ಕಾರ್ಯಕ್ರಮ, GLenum shadertype, GLchar *ಮೂಲ, GLint *ಉದ್ದಳತೆ);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ GL_GLEXT_PROTOTYPES
GL_API ಶೂನ್ಯ GL_APIENTRY glExtGetShadersQCOM (GLuint *shaders, GLint maxShaders, GLint *ಅಂಕೆ_Shaders);
GL_API ಶೂನ್ಯ GL_APIENTRY glExtGetProgramsQCOM (GLuint *programs, GLint maxPrograms, GLint *ಅಂಕೆ_Programs);
GL_API GLboolean GL_APIENTRY gl_Ext_Is_ಕಾರ್ಯಕ್ರಮ_ದ್ವಿಮಾನ_QCOM (GLuint ಕಾರ್ಯಕ್ರಮ);
GL_API ಶೂನ್ಯ GL_APIENTRY gl_Ext_Get_ಕಾರ್ಯಕ್ರಮ_ದ್ವಿಮಾನ_ಮೂಲ_QCOM (GLuint ಕಾರ್ಯಕ್ರಮ, GLenum shadertype, GLchar *ಮೂಲ, GLint *ಉದ್ದಳತೆ);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* GL_QCOM_extended_get2 */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_QCOM_perfmon_global_ಬಹುಲಕ
#ವ್ಯಾಖ್ಯಾನಿಸು GL_QCOM_perfmon_global_ಬಹುಲಕ 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_PERFMON_GLOBAL_ಬಹುಲಕ_QCOM       0x8FA0
#ಆದರೆ_ಅಂತ್ಯ /* GL_QCOM_perfmon_global_mode */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_QCOM_tiled_rendering
#ವ್ಯಾಖ್ಯಾನಿಸು GL_QCOM_tiled_rendering 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_COLOR_ಬಫರ್_BIT0_QCOM         0x00000001
#ವ್ಯಾಖ್ಯಾನಿಸು GL_COLOR_ಬಫರ್_BIT1_QCOM         0x00000002
#ವ್ಯಾಖ್ಯಾನಿಸು GL_COLOR_ಬಫರ್_BIT2_QCOM         0x00000004
#ವ್ಯಾಖ್ಯಾನಿಸು GL_COLOR_ಬಫರ್_BIT3_QCOM         0x00000008
#ವ್ಯಾಖ್ಯಾನಿಸು GL_COLOR_ಬಫರ್_BIT4_QCOM         0x00000010
#ವ್ಯಾಖ್ಯಾನಿಸು GL_COLOR_ಬಫರ್_BIT5_QCOM         0x00000020
#ವ್ಯಾಖ್ಯಾನಿಸು GL_COLOR_ಬಫರ್_BIT6_QCOM         0x00000040
#ವ್ಯಾಖ್ಯಾನಿಸು GL_COLOR_ಬಫರ್_BIT7_QCOM         0x00000080
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ಆಳ_ಬಫರ್_BIT0_QCOM         0x00000100
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ಆಳ_ಬಫರ್_BIT1_QCOM         0x00000200
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ಆಳ_ಬಫರ್_BIT2_QCOM         0x00000400
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ಆಳ_ಬಫರ್_BIT3_QCOM         0x00000800
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ಆಳ_ಬಫರ್_BIT4_QCOM         0x00001000
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ಆಳ_ಬಫರ್_BIT5_QCOM         0x00002000
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ಆಳ_ಬಫರ್_BIT6_QCOM         0x00004000
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ಆಳ_ಬಫರ್_BIT7_QCOM         0x00008000
#ವ್ಯಾಖ್ಯಾನಿಸು GL_STENCIL_ಬಫರ್_BIT0_QCOM       0x00010000
#ವ್ಯಾಖ್ಯಾನಿಸು GL_STENCIL_ಬಫರ್_BIT1_QCOM       0x00020000
#ವ್ಯಾಖ್ಯಾನಿಸು GL_STENCIL_ಬಫರ್_BIT2_QCOM       0x00040000
#ವ್ಯಾಖ್ಯಾನಿಸು GL_STENCIL_ಬಫರ್_BIT3_QCOM       0x00080000
#ವ್ಯಾಖ್ಯಾನಿಸು GL_STENCIL_ಬಫರ್_BIT4_QCOM       0x00100000
#ವ್ಯಾಖ್ಯಾನಿಸು GL_STENCIL_ಬಫರ್_BIT5_QCOM       0x00200000
#ವ್ಯಾಖ್ಯಾನಿಸು GL_STENCIL_ಬಫರ್_BIT6_QCOM       0x00400000
#ವ್ಯಾಖ್ಯಾನಿಸು GL_STENCIL_ಬಫರ್_BIT7_QCOM       0x00800000
#ವ್ಯಾಖ್ಯಾನಿಸು GL_MULTISAMPLE_ಬಫರ್_BIT0_QCOM   0x01000000
#ವ್ಯಾಖ್ಯಾನಿಸು GL_MULTISAMPLE_ಬಫರ್_BIT1_QCOM   0x02000000
#ವ್ಯಾಖ್ಯಾನಿಸು GL_MULTISAMPLE_ಬಫರ್_BIT2_QCOM   0x04000000
#ವ್ಯಾಖ್ಯಾನಿಸು GL_MULTISAMPLE_ಬಫರ್_BIT3_QCOM   0x08000000
#ವ್ಯಾಖ್ಯಾನಿಸು GL_MULTISAMPLE_ಬಫರ್_BIT4_QCOM   0x10000000
#ವ್ಯಾಖ್ಯಾನಿಸು GL_MULTISAMPLE_ಬಫರ್_BIT5_QCOM   0x20000000
#ವ್ಯಾಖ್ಯಾನಿಸು GL_MULTISAMPLE_ಬಫರ್_BIT6_QCOM   0x40000000
#ವ್ಯಾಖ್ಯಾನಿಸು GL_MULTISAMPLE_ಬಫರ್_BIT7_QCOM   0x80000000
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLSTARTTILINGQCOMPROC) (GLuint x, GLuint y, GLuint ಅಗಲ, GLuint ಎತ್ತರ, GLbitfield preserve_ಮುಖವಾಡ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (GL_APIENTRYP PFNGLENDTILINGQCOMPROC) (GLbitfield preserve_ಮುಖವಾಡ);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ GL_GLEXT_PROTOTYPES
GL_API ಶೂನ್ಯ GL_APIENTRY gl_ಆರಂಭ_Tiling_QCOM (GLuint x, GLuint y, GLuint ಅಗಲ, GLuint ಎತ್ತರ, GLbitfield preserve_ಮುಖವಾಡ);
GL_API ಶೂನ್ಯ GL_APIENTRY gl_ಕೊನೆ_Tiling_QCOM (GLbitfield preserve_ಮುಖವಾಡ);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* GL_QCOM_tiled_rendering */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_QCOM_writeonly_rendering
#ವ್ಯಾಖ್ಯಾನಿಸು GL_QCOM_writeonly_rendering 1
#ವ್ಯಾಖ್ಯಾನಿಸು GL_WRITEONLY_RENDERING_QCOM       0x8823
#ಆದರೆ_ಅಂತ್ಯ /* GL_QCOM_writeonly_rendering */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ
