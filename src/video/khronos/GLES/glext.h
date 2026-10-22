#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __gles1_glext_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ __gles1_glext_h_ 1

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ

/*
** Copyright 2013-2026 The Khronos Group Inc.
** SPDX-License-Identifier: MIT
**
** This header is generated from the Khronos OpenGL / OpenGL ES XML
** API Registry. The current version of the Registry, generator scripts
** used to make the header, and the header can be found at
**   https://github.com/KhronosGroup/OpenGL-Registry
*/

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_APIENTRYP
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_APIENTRYP GL_APIENTRY*
#ਜੇ_ਅੰਤ

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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_KHR_debug
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_KHR_debug 1
#ਜੇ_ਅੰਤ /* GL_KHR_debug */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_OES_EGL_image
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OES_EGL_image 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ *GLeglImageOES;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLEGLIMAGETARGETTEXTURE2DOESPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLeglImageOES image);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLEGLIMAGETARGETRENDERBUFFERSTORAGEOESPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLeglImageOES image);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ GL_GLEXT_PROTOTYPES
GL_API ਖਾਲੀ GL_APIENTRY gl_EGLImage_ਨਿਸ਼ਾਨਾ_Texture2_DOES (GLenum ਨਿਸ਼ਾਨਾ, GLeglImageOES image);
GL_API ਖਾਲੀ GL_APIENTRY gl_EGLImage_ਨਿਸ਼ਾਨਾ_Renderbuffer_Storage_OES (GLenum ਨਿਸ਼ਾਨਾ, GLeglImageOES image);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* GL_OES_EGL_image */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_OES_EGL_image_external
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OES_EGL_image_external 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_EXTERNAL_OES           0x8D65
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_BINDING_EXTERNAL_OES   0x8D67
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_REQUIRED_TEXTURE_IMAGE_UNITS_OES 0x8D68
#ਜੇ_ਅੰਤ /* GL_OES_EGL_image_external */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_OES_blend_equation_separate
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OES_blend_equation_separate 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_BLEND_EQUATION_RGB_OES         0x8009
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_BLEND_EQUATION_ALPHA_OES       0x883D
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEOESPROC) (GLenum ਬਹੁਲਕ_RGB, GLenum ਬਹੁਲਕ_Alpha);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ GL_GLEXT_PROTOTYPES
GL_API ਖਾਲੀ GL_APIENTRY glBlendEquationSeparateOES (GLenum ਬਹੁਲਕ_RGB, GLenum ਬਹੁਲਕ_Alpha);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* GL_OES_blend_equation_separate */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_OES_blend_func_separate
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OES_blend_func_separate 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_BLEND_DST_RGB_OES              0x80C8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_BLEND_SRC_RGB_OES              0x80C9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_BLEND_DST_ALPHA_OES            0x80CA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_BLEND_SRC_ALPHA_OES            0x80CB
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEOESPROC) (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ GL_GLEXT_PROTOTYPES
GL_API ਖਾਲੀ GL_APIENTRY glBlendFuncSeparateOES (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* GL_OES_blend_func_separate */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_OES_blend_ਘਟਾਓ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OES_blend_ਘਟਾਓ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_BLEND_EQUATION_OES             0x8009
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FUNC_ਜੋੜੋ_OES                   0x8006
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FUNC_ਘਟਾਓ_OES              0x800A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FUNC_ਉਲਟ_ਘਟਾਓ_OES      0x800B
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLBLENDEQUATIONOESPROC) (GLenum ਬਹੁਲਕ);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ GL_GLEXT_PROTOTYPES
GL_API ਖਾਲੀ GL_APIENTRY glBlendEquationOES (GLenum ਬਹੁਲਕ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* GL_OES_blend_subtract */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_OES_byte_coordinates
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OES_byte_coordinates 1
#ਜੇ_ਅੰਤ /* GL_OES_byte_coordinates */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_OES_compressed_ETC1_RGB8_sub_texture
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OES_compressed_ETC1_RGB8_sub_texture 1
#ਜੇ_ਅੰਤ /* GL_OES_compressed_ETC1_RGB8_sub_texture */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_OES_compressed_ETC1_RGB8_texture
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OES_compressed_ETC1_RGB8_texture 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ETC1_RGB8_OES                  0x8D64
#ਜੇ_ਅੰਤ /* GL_OES_compressed_ETC1_RGB8_texture */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_OES_depth24
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OES_depth24 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਡੂੰਘਾਈ_COMPONENT24_OES          0x81A6
#ਜੇ_ਅੰਤ /* GL_OES_depth24 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_OES_depth32
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OES_depth32 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਡੂੰਘਾਈ_COMPONENT32_OES          0x81A7
#ਜੇ_ਅੰਤ /* GL_OES_depth32 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_OES_draw_texture
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OES_draw_texture 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_CROP_RECT_OES          0x8B9D
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDRAWTEXSOESPROC) (GLshort x, GLshort y, GLshort z, GLshort ਚੌੜਾਈ, GLshort ਉਚਾਈ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDRAWTEXIOESPROC) (GLint x, GLint y, GLint z, GLint ਚੌੜਾਈ, GLint ਉਚਾਈ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDRAWTEXXOESPROC) (GLfixed x, GLfixed y, GLfixed z, GLfixed ਚੌੜਾਈ, GLfixed ਉਚਾਈ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDRAWTEXSVOESPROC) (ਅਚਲ GLshort *coords);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDRAWTEXIVOESPROC) (ਅਚਲ GLint *coords);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDRAWTEXXVOESPROC) (ਅਚਲ GLfixed *coords);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDRAWTEXFOESPROC) (GLfloat x, GLfloat y, GLfloat z, GLfloat ਚੌੜਾਈ, GLfloat ਉਚਾਈ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDRAWTEXFVOESPROC) (ਅਚਲ GLfloat *coords);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ GL_GLEXT_PROTOTYPES
GL_API ਖਾਲੀ GL_APIENTRY glDrawTexsOES (GLshort x, GLshort y, GLshort z, GLshort ਚੌੜਾਈ, GLshort ਉਚਾਈ);
GL_API ਖਾਲੀ GL_APIENTRY glDrawTexiOES (GLint x, GLint y, GLint z, GLint ਚੌੜਾਈ, GLint ਉਚਾਈ);
GL_API ਖਾਲੀ GL_APIENTRY glDrawTexxOES (GLfixed x, GLfixed y, GLfixed z, GLfixed ਚੌੜਾਈ, GLfixed ਉਚਾਈ);
GL_API ਖਾਲੀ GL_APIENTRY glDrawTexsvOES (ਅਚਲ GLshort *coords);
GL_API ਖਾਲੀ GL_APIENTRY glDrawTexivOES (ਅਚਲ GLint *coords);
GL_API ਖਾਲੀ GL_APIENTRY glDrawTexxvOES (ਅਚਲ GLfixed *coords);
GL_API ਖਾਲੀ GL_APIENTRY glDrawTexfOES (GLfloat x, GLfloat y, GLfloat z, GLfloat ਚੌੜਾਈ, GLfloat ਉਚਾਈ);
GL_API ਖਾਲੀ GL_APIENTRY glDrawTexfvOES (ਅਚਲ GLfloat *coords);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* GL_OES_draw_texture */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_OES_element_ਸੂਚਕਾਂਕ_uint
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OES_element_ਸੂਚਕਾਂਕ_uint 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNED_INT                   0x1405
#ਜੇ_ਅੰਤ /* GL_OES_element_index_uint */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_OES_extended_ਮੈਟ੍ਰਿਕਸ_palette
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OES_extended_ਮੈਟ੍ਰਿਕਸ_palette 1
#ਜੇ_ਅੰਤ /* GL_OES_extended_matrix_palette */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_OES_fbo_render_mipmap
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OES_fbo_render_mipmap 1
#ਜੇ_ਅੰਤ /* GL_OES_fbo_render_mipmap */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_OES_fixed_ਬਿੰਦੂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OES_fixed_ਬਿੰਦੂ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FIXED_OES                      0x140C
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLALPHAFUNCXOESPROC) (GLenum func, GLfixed ref);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLCLEARCOLORXOESPROC) (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLCLEARDEPTHXOESPROC) (GLfixed ਡੂੰਘਾਈ_2);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLCLIPPLANEXOESPROC) (GLenum plane, ਅਚਲ GLfixed *equation);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLCOLOR4XOESPROC) (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDEPTHRANGEXOESPROC) (GLfixed n, GLfixed f);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLFOGXOESPROC) (GLenum pname, GLfixed param);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLFOGXVOESPROC) (GLenum pname, ਅਚਲ GLfixed *param);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLFRUSTUMXOESPROC) (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETCLIPPLANEXOESPROC) (GLenum plane, GLfixed *equation);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETFIXEDVOESPROC) (GLenum pname, GLfixed *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETTEXENVXVOESPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLfixed *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETTEXPARAMETERXVOESPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLfixed *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLLIGHTMODELXOESPROC) (GLenum pname, GLfixed param);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLLIGHTMODELXVOESPROC) (GLenum pname, ਅਚਲ GLfixed *param);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLLIGHTXOESPROC) (GLenum light, GLenum pname, GLfixed param);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLLIGHTXVOESPROC) (GLenum light, GLenum pname, ਅਚਲ GLfixed *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLLINEWIDTHXOESPROC) (GLfixed ਚੌੜਾਈ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLLOADMATRIXXOESPROC) (ਅਚਲ GLfixed *m);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLMATERIALXOESPROC) (GLenum face, GLenum pname, GLfixed param);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLMATERIALXVOESPROC) (GLenum face, GLenum pname, ਅਚਲ GLfixed *param);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLMULTMATRIXXOESPROC) (ਅਚਲ GLfixed *m);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLMULTITEXCOORD4XOESPROC) (GLenum texture, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLNORMAL3XOESPROC) (GLfixed nx, GLfixed ny, GLfixed nz);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLORTHOXOESPROC) (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPOINTPARAMETERXVOESPROC) (GLenum pname, ਅਚਲ GLfixed *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPOINTSIZEXOESPROC) (GLfixed ਮਾਪ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPOLYGONOFFSETXOESPROC) (GLfixed ਗੁਣਕ, GLfixed units);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLROTATEXOESPROC) (GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLSCALEXOESPROC) (GLfixed x, GLfixed y, GLfixed z);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLTEXENVXOESPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLfixed param);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLTEXENVXVOESPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, ਅਚਲ GLfixed *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLTEXPARAMETERXOESPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLfixed param);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLTEXPARAMETERXVOESPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, ਅਚਲ GLfixed *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLTRANSLATEXOESPROC) (GLfixed x, GLfixed y, GLfixed z);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETLIGHTXVOESPROC) (GLenum light, GLenum pname, GLfixed *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETMATERIALXVOESPROC) (GLenum face, GLenum pname, GLfixed *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPOINTPARAMETERXOESPROC) (GLenum pname, GLfixed param);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLSAMPLECOVERAGEXOESPROC) (GLclampx ਮੁੱਲ, GLboolean invert);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETTEXGENXVOESPROC) (GLenum coord, GLenum pname, GLfixed *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLTEXGENXOESPROC) (GLenum coord, GLenum pname, GLfixed param);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLTEXGENXVOESPROC) (GLenum coord, GLenum pname, ਅਚਲ GLfixed *params);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ GL_GLEXT_PROTOTYPES
GL_API ਖਾਲੀ GL_APIENTRY glAlphaFuncxOES (GLenum func, GLfixed ref);
GL_API ਖਾਲੀ GL_APIENTRY glClearColorxOES (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GL_API ਖਾਲੀ GL_APIENTRY glClearDepthxOES (GLfixed ਡੂੰਘਾਈ_2);
GL_API ਖਾਲੀ GL_APIENTRY glClipPlanexOES (GLenum plane, ਅਚਲ GLfixed *equation);
GL_API ਖਾਲੀ GL_APIENTRY glColor4xOES (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GL_API ਖਾਲੀ GL_APIENTRY gl_ਡੂੰਘਾਈ_Rangex_OES (GLfixed n, GLfixed f);
GL_API ਖਾਲੀ GL_APIENTRY glFogxOES (GLenum pname, GLfixed param);
GL_API ਖਾਲੀ GL_APIENTRY glFogxvOES (GLenum pname, ਅਚਲ GLfixed *param);
GL_API ਖਾਲੀ GL_APIENTRY glFrustumxOES (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
GL_API ਖਾਲੀ GL_APIENTRY glGetClipPlanexOES (GLenum plane, GLfixed *equation);
GL_API ਖਾਲੀ GL_APIENTRY glGetFixedvOES (GLenum pname, GLfixed *params);
GL_API ਖਾਲੀ GL_APIENTRY glGetTexEnvxvOES (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLfixed *params);
GL_API ਖਾਲੀ GL_APIENTRY glGetTexParameterxvOES (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLfixed *params);
GL_API ਖਾਲੀ GL_APIENTRY glLightModelxOES (GLenum pname, GLfixed param);
GL_API ਖਾਲੀ GL_APIENTRY glLightModelxvOES (GLenum pname, ਅਚਲ GLfixed *param);
GL_API ਖਾਲੀ GL_APIENTRY glLightxOES (GLenum light, GLenum pname, GLfixed param);
GL_API ਖਾਲੀ GL_APIENTRY glLightxvOES (GLenum light, GLenum pname, ਅਚਲ GLfixed *params);
GL_API ਖਾਲੀ GL_APIENTRY gl_ਸਤਰ_Widthx_OES (GLfixed ਚੌੜਾਈ);
GL_API ਖਾਲੀ GL_APIENTRY gl_ਲੱਦੋ_Matrixx_OES (ਅਚਲ GLfixed *m);
GL_API ਖਾਲੀ GL_APIENTRY glMaterialxOES (GLenum face, GLenum pname, GLfixed param);
GL_API ਖਾਲੀ GL_APIENTRY glMaterialxvOES (GLenum face, GLenum pname, ਅਚਲ GLfixed *param);
GL_API ਖਾਲੀ GL_APIENTRY glMultMatrixxOES (ਅਚਲ GLfixed *m);
GL_API ਖਾਲੀ GL_APIENTRY glMultiTexCoord4xOES (GLenum texture, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
GL_API ਖਾਲੀ GL_APIENTRY glNormal3xOES (GLfixed nx, GLfixed ny, GLfixed nz);
GL_API ਖਾਲੀ GL_APIENTRY glOrthoxOES (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
GL_API ਖਾਲੀ GL_APIENTRY gl_ਬਿੰਦੂ_Parameterxv_OES (GLenum pname, ਅਚਲ GLfixed *params);
GL_API ਖਾਲੀ GL_APIENTRY gl_ਬਿੰਦੂ_Sizex_OES (GLfixed ਮਾਪ);
GL_API ਖਾਲੀ GL_APIENTRY glPolygonOffsetxOES (GLfixed ਗੁਣਕ, GLfixed units);
GL_API ਖਾਲੀ GL_APIENTRY glRotatexOES (GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
GL_API ਖਾਲੀ GL_APIENTRY glScalexOES (GLfixed x, GLfixed y, GLfixed z);
GL_API ਖਾਲੀ GL_APIENTRY glTexEnvxOES (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLfixed param);
GL_API ਖਾਲੀ GL_APIENTRY glTexEnvxvOES (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, ਅਚਲ GLfixed *params);
GL_API ਖਾਲੀ GL_APIENTRY glTexParameterxOES (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLfixed param);
GL_API ਖਾਲੀ GL_APIENTRY glTexParameterxvOES (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, ਅਚਲ GLfixed *params);
GL_API ਖਾਲੀ GL_APIENTRY glTranslatexOES (GLfixed x, GLfixed y, GLfixed z);
GL_API ਖਾਲੀ GL_APIENTRY glGetLightxvOES (GLenum light, GLenum pname, GLfixed *params);
GL_API ਖਾਲੀ GL_APIENTRY glGetMaterialxvOES (GLenum face, GLenum pname, GLfixed *params);
GL_API ਖਾਲੀ GL_APIENTRY gl_ਬਿੰਦੂ_Parameterx_OES (GLenum pname, GLfixed param);
GL_API ਖਾਲੀ GL_APIENTRY glSampleCoveragexOES (GLclampx ਮੁੱਲ, GLboolean invert);
GL_API ਖਾਲੀ GL_APIENTRY glGetTexGenxvOES (GLenum coord, GLenum pname, GLfixed *params);
GL_API ਖਾਲੀ GL_APIENTRY glTexGenxOES (GLenum coord, GLenum pname, GLfixed param);
GL_API ਖਾਲੀ GL_APIENTRY glTexGenxvOES (GLenum coord, GLenum pname, ਅਚਲ GLfixed *params);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* GL_OES_fixed_point */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_OES_framebuffer_object
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OES_framebuffer_object 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_NONE_OES                       0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_OES                0x8D40
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RENDERBUFFER_OES               0x8D41
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGBA4_OES                      0x8056
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGB5_A1_OES                    0x8057
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGB565_OES                     0x8D62
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਡੂੰਘਾਈ_COMPONENT16_OES          0x81A5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RENDERBUFFER_ਚੌੜਾਈ_OES         0x8D42
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RENDERBUFFER_ਉਚਾਈ_OES        0x8D43
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RENDERBUFFER_ਅੰਦਰੂਨੀ_FORMAT_OES 0x8D44
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RENDERBUFFER_RED_ਮਾਪ_OES      0x8D50
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RENDERBUFFER_GREEN_ਮਾਪ_OES    0x8D51
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RENDERBUFFER_BLUE_ਮਾਪ_OES     0x8D52
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RENDERBUFFER_ALPHA_ਮਾਪ_OES    0x8D53
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RENDERBUFFER_ਡੂੰਘਾਈ_ਮਾਪ_OES    0x8D54
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RENDERBUFFER_STENCIL_ਮਾਪ_OES  0x8D55
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_OES 0x8CD0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_OES 0x8CD1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_OES 0x8CD2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_OES 0x8CD3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ATTACHMENT0_OES          0x8CE0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਡੂੰਘਾਈ_ATTACHMENT_OES           0x8D00
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STENCIL_ATTACHMENT_OES         0x8D20
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_COMPLETE_OES       0x8CD5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_OES 0x8CD6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_OES 0x8CD7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_OES 0x8CD9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_INCOMPLETE_FORMATS_OES 0x8CDA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_UNSUPPORTED_OES    0x8CDD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_BINDING_OES        0x8CA6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RENDERBUFFER_BINDING_OES       0x8CA7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_RENDERBUFFER_ਮਾਪ_OES      0x84E8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_INVALID_FRAMEBUFFER_OPERATION_OES 0x0506
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLboolean (GL_APIENTRYP PFNGLISRENDERBUFFEROESPROC) (GLuint renderbuffer);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLBINDRENDERBUFFEROESPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLuint renderbuffer);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDELETERENDERBUFFERSOESPROC) (GLsizei n, ਅਚਲ GLuint *renderbuffers);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGENRENDERBUFFERSOESPROC) (GLsizei n, GLuint *renderbuffers);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEOESPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVOESPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLboolean (GL_APIENTRYP PFNGLISFRAMEBUFFEROESPROC) (GLuint framebuffer);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLBINDFRAMEBUFFEROESPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLuint framebuffer);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDELETEFRAMEBUFFERSOESPROC) (GLsizei n, ਅਚਲ GLuint *framebuffers);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGENFRAMEBUFFERSOESPROC) (GLsizei n, GLuint *framebuffers);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLenum (GL_APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSOESPROC) (GLenum ਨਿਸ਼ਾਨਾ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFEROESPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DOESPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVOESPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum attachment, GLenum pname, GLint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGENERATEMIPMAPOESPROC) (GLenum ਨਿਸ਼ਾਨਾ);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ GL_GLEXT_PROTOTYPES
GL_API GLboolean GL_APIENTRY glIsRenderbufferOES (GLuint renderbuffer);
GL_API ਖਾਲੀ GL_APIENTRY glBindRenderbufferOES (GLenum ਨਿਸ਼ਾਨਾ, GLuint renderbuffer);
GL_API ਖਾਲੀ GL_APIENTRY glDeleteRenderbuffersOES (GLsizei n, ਅਚਲ GLuint *renderbuffers);
GL_API ਖਾਲੀ GL_APIENTRY glGenRenderbuffersOES (GLsizei n, GLuint *renderbuffers);
GL_API ਖਾਲੀ GL_APIENTRY glRenderbufferStorageOES (GLenum ਨਿਸ਼ਾਨਾ, GLenum internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ);
GL_API ਖਾਲੀ GL_APIENTRY glGetRenderbufferParameterivOES (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLint *params);
GL_API GLboolean GL_APIENTRY glIsFramebufferOES (GLuint framebuffer);
GL_API ਖਾਲੀ GL_APIENTRY glBindFramebufferOES (GLenum ਨਿਸ਼ਾਨਾ, GLuint framebuffer);
GL_API ਖਾਲੀ GL_APIENTRY glDeleteFramebuffersOES (GLsizei n, ਅਚਲ GLuint *framebuffers);
GL_API ਖਾਲੀ GL_APIENTRY glGenFramebuffersOES (GLsizei n, GLuint *framebuffers);
GL_API GLenum GL_APIENTRY gl_Check_Framebuffer_ਸਥਿਤੀ_OES (GLenum ਨਿਸ਼ਾਨਾ);
GL_API ਖਾਲੀ GL_APIENTRY glFramebufferRenderbufferOES (GLenum ਨਿਸ਼ਾਨਾ, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
GL_API ਖਾਲੀ GL_APIENTRY glFramebufferTexture2DOES (GLenum ਨਿਸ਼ਾਨਾ, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GL_API ਖਾਲੀ GL_APIENTRY glGetFramebufferAttachmentParameterivOES (GLenum ਨਿਸ਼ਾਨਾ, GLenum attachment, GLenum pname, GLint *params);
GL_API ਖਾਲੀ GL_APIENTRY glGenerateMipmapOES (GLenum ਨਿਸ਼ਾਨਾ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* GL_OES_framebuffer_object */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_OES_mapbuffer
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OES_mapbuffer 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_WRITE_ONLY_OES                 0x88B9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਬਫਰ_ACCESS_OES              0x88BB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਬਫਰ_MAPPED_OES              0x88BC
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਬਫਰ_MAP_ਸੂਚਕ_OES         0x88BD
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ *(GL_APIENTRYP PFNGLMAPBUFFEROESPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum access);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLboolean (GL_APIENTRYP PFNGLUNMAPBUFFEROESPROC) (GLenum ਨਿਸ਼ਾਨਾ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETBUFFERPOINTERVOESPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, ਖਾਲੀ **params);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ GL_GLEXT_PROTOTYPES
GL_API ਖਾਲੀ *GL_APIENTRY gl_Map_ਬਫਰ_OES (GLenum ਨਿਸ਼ਾਨਾ, GLenum access);
GL_API GLboolean GL_APIENTRY gl_Unmap_ਬਫਰ_OES (GLenum ਨਿਸ਼ਾਨਾ);
GL_API ਖਾਲੀ GL_APIENTRY gl_Get_ਬਫਰ_Pointerv_OES (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, ਖਾਲੀ **params);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* GL_OES_mapbuffer */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_OES_ਮੈਟ੍ਰਿਕਸ_get
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OES_ਮੈਟ੍ਰਿਕਸ_get 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MODELVIEW_ਮੈਟ੍ਰਿਕਸ_FLOAT_AS_INT_ਬਿੱਟ_OES 0x898D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_PROJECTION_ਮੈਟ੍ਰਿਕਸ_FLOAT_AS_INT_ਬਿੱਟ_OES 0x898E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_ਮੈਟ੍ਰਿਕਸ_FLOAT_AS_INT_ਬਿੱਟ_OES 0x898F
#ਜੇ_ਅੰਤ /* GL_OES_matrix_get */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_OES_ਮੈਟ੍ਰਿਕਸ_palette
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OES_ਮੈਟ੍ਰਿਕਸ_palette 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_ਸ਼ੀਰਸ਼_UNITS_OES           0x86A4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_PALETTE_MATRICES_OES       0x8842
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਮੈਟ੍ਰਿਕਸ_PALETTE_OES             0x8840
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਮੈਟ੍ਰਿਕਸ_ਸੂਚਕਾਂਕ_ARRAY_OES         0x8844
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਭਾਰ_ARRAY_OES               0x86AD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_CURRENT_PALETTE_ਮੈਟ੍ਰਿਕਸ_OES     0x8843
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਮੈਟ੍ਰਿਕਸ_ਸੂਚਕਾਂਕ_ARRAY_ਮਾਪ_OES    0x8846
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਮੈਟ੍ਰਿਕਸ_ਸੂਚਕਾਂਕ_ARRAY_TYPE_OES    0x8847
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਮੈਟ੍ਰਿਕਸ_ਸੂਚਕਾਂਕ_ARRAY_STRIDE_OES  0x8848
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਮੈਟ੍ਰਿਕਸ_ਸੂਚਕਾਂਕ_ARRAY_ਸੂਚਕ_OES 0x8849
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਮੈਟ੍ਰਿਕਸ_ਸੂਚਕਾਂਕ_ARRAY_ਬਫਰ_BINDING_OES 0x8B9E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਭਾਰ_ARRAY_ਮਾਪ_OES          0x86AB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਭਾਰ_ARRAY_TYPE_OES          0x86A9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਭਾਰ_ARRAY_STRIDE_OES        0x86AA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਭਾਰ_ARRAY_ਸੂਚਕ_OES       0x86AC
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਭਾਰ_ARRAY_ਬਫਰ_BINDING_OES 0x889E
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLCURRENTPALETTEMATRIXOESPROC) (GLuint matrixpaletteindex);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLLOADPALETTEFROMMODELVIEWMATRIXOESPROC) (ਖਾਲੀ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLMATRIXINDEXPOINTEROESPROC) (GLint ਮਾਪ, GLenum type, GLsizei stride, ਅਚਲ ਖਾਲੀ *ਸੂਚਕ_2);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLWEIGHTPOINTEROESPROC) (GLint ਮਾਪ, GLenum type, GLsizei stride, ਅਚਲ ਖਾਲੀ *ਸੂਚਕ_2);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ GL_GLEXT_PROTOTYPES
GL_API ਖਾਲੀ GL_APIENTRY gl_Current_Palette_ਮੈਟ੍ਰਿਕਸ_OES (GLuint matrixpaletteindex);
GL_API ਖਾਲੀ GL_APIENTRY gl_ਲੱਦੋ_Palette_From_Model_View_ਮੈਟ੍ਰਿਕਸ_OES (ਖਾਲੀ);
GL_API ਖਾਲੀ GL_APIENTRY gl_ਮੈਟ੍ਰਿਕਸ_ਸੂਚਕਾਂਕ_ਸੂਚਕ_OES (GLint ਮਾਪ, GLenum type, GLsizei stride, ਅਚਲ ਖਾਲੀ *ਸੂਚਕ_2);
GL_API ਖਾਲੀ GL_APIENTRY gl_ਭਾਰ_ਸੂਚਕ_OES (GLint ਮਾਪ, GLenum type, GLsizei stride, ਅਚਲ ਖਾਲੀ *ਸੂਚਕ_2);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* GL_OES_matrix_palette */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_OES_packed_ਡੂੰਘਾਈ_stencil
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OES_packed_ਡੂੰਘਾਈ_stencil 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਡੂੰਘਾਈ_STENCIL_OES              0x84F9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNED_INT_24_8_OES          0x84FA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DEPTH24_STENCIL8_OES           0x88F0
#ਜੇ_ਅੰਤ /* GL_OES_packed_depth_stencil */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_OES_query_ਮੈਟ੍ਰਿਕਸ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OES_query_ਮੈਟ੍ਰਿਕਸ 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLbitfield (GL_APIENTRYP PFNGLQUERYMATRIXXOESPROC) (GLfixed *mantissa, GLint *exponent);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ GL_GLEXT_PROTOTYPES
GL_API GLbitfield GL_APIENTRY glQueryMatrixxOES (GLfixed *mantissa, GLint *exponent);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* GL_OES_query_matrix */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_OES_required_internalformat
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OES_required_internalformat 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ALPHA8_OES                     0x803C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_LUMINANCE4_ALPHA4_OES          0x8043
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_LUMINANCE8_ALPHA8_OES          0x8045
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_LUMINANCE8_OES                 0x8040
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGB8_OES                       0x8051
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGBA8_OES                      0x8058
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGB10_EXT                      0x8052
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGB10_A2_EXT                   0x8059
#ਜੇ_ਅੰਤ /* GL_OES_required_internalformat */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_OES_rgb8_rgba8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OES_rgb8_rgba8 1
#ਜੇ_ਅੰਤ /* GL_OES_rgb8_rgba8 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_OES_single_precision
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OES_single_precision 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLCLEARDEPTHFOESPROC) (GLclampf ਡੂੰਘਾਈ_2);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLCLIPPLANEFOESPROC) (GLenum plane, ਅਚਲ GLfloat *equation);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDEPTHRANGEFOESPROC) (GLclampf n, GLclampf f);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLFRUSTUMFOESPROC) (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETCLIPPLANEFOESPROC) (GLenum plane, GLfloat *equation);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLORTHOFOESPROC) (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ GL_GLEXT_PROTOTYPES
GL_API ਖਾਲੀ GL_APIENTRY glClearDepthfOES (GLclampf ਡੂੰਘਾਈ_2);
GL_API ਖਾਲੀ GL_APIENTRY glClipPlanefOES (GLenum plane, ਅਚਲ GLfloat *equation);
GL_API ਖਾਲੀ GL_APIENTRY gl_ਡੂੰਘਾਈ_Rangef_OES (GLclampf n, GLclampf f);
GL_API ਖਾਲੀ GL_APIENTRY glFrustumfOES (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
GL_API ਖਾਲੀ GL_APIENTRY glGetClipPlanefOES (GLenum plane, GLfloat *equation);
GL_API ਖਾਲੀ GL_APIENTRY glOrthofOES (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* GL_OES_single_precision */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_OES_stencil1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OES_stencil1 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STENCIL_INDEX1_OES             0x8D46
#ਜੇ_ਅੰਤ /* GL_OES_stencil1 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_OES_stencil4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OES_stencil4 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STENCIL_INDEX4_OES             0x8D47
#ਜੇ_ਅੰਤ /* GL_OES_stencil4 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_OES_stencil8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OES_stencil8 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STENCIL_INDEX8_OES             0x8D48
#ਜੇ_ਅੰਤ /* GL_OES_stencil8 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_OES_stencil_wrap
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OES_stencil_wrap 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_INCR_WRAP_OES                  0x8507
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DECR_WRAP_OES                  0x8508
#ਜੇ_ਅੰਤ /* GL_OES_stencil_wrap */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_OES_surfaceless_context
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OES_surfaceless_context 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_UNDEFINED_OES      0x8219
#ਜੇ_ਅੰਤ /* GL_OES_surfaceless_context */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_OES_texture_cube_map
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OES_texture_cube_map 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸਾਧਾਰਨ_MAP_OES                 0x8511
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_REFLECTION_MAP_OES             0x8512
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_CUBE_MAP_OES           0x8513
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_BINDING_CUBE_MAP_OES   0x8514
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_CUBE_MAP_ਸਕਾਰਾਤਮਕ_X_OES 0x8515
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_CUBE_MAP_NEGATIVE_X_OES 0x8516
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_CUBE_MAP_ਸਕਾਰਾਤਮਕ_Y_OES 0x8517
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_OES 0x8518
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_CUBE_MAP_ਸਕਾਰਾਤਮਕ_Z_OES 0x8519
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_OES 0x851A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_CUBE_MAP_TEXTURE_ਮਾਪ_OES  0x851C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_GEN_ਬਹੁਲਕ_OES           0x2500
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_GEN_STR_OES            0x8D60
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLTEXGENFOESPROC) (GLenum coord, GLenum pname, GLfloat param);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLTEXGENFVOESPROC) (GLenum coord, GLenum pname, ਅਚਲ GLfloat *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLTEXGENIOESPROC) (GLenum coord, GLenum pname, GLint param);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLTEXGENIVOESPROC) (GLenum coord, GLenum pname, ਅਚਲ GLint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETTEXGENFVOESPROC) (GLenum coord, GLenum pname, GLfloat *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETTEXGENIVOESPROC) (GLenum coord, GLenum pname, GLint *params);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ GL_GLEXT_PROTOTYPES
GL_API ਖਾਲੀ GL_APIENTRY glTexGenfOES (GLenum coord, GLenum pname, GLfloat param);
GL_API ਖਾਲੀ GL_APIENTRY glTexGenfvOES (GLenum coord, GLenum pname, ਅਚਲ GLfloat *params);
GL_API ਖਾਲੀ GL_APIENTRY glTexGeniOES (GLenum coord, GLenum pname, GLint param);
GL_API ਖਾਲੀ GL_APIENTRY glTexGenivOES (GLenum coord, GLenum pname, ਅਚਲ GLint *params);
GL_API ਖਾਲੀ GL_APIENTRY glGetTexGenfvOES (GLenum coord, GLenum pname, GLfloat *params);
GL_API ਖਾਲੀ GL_APIENTRY glGetTexGenivOES (GLenum coord, GLenum pname, GLint *params);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* GL_OES_texture_cube_map */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_OES_texture_env_crossbar
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OES_texture_env_crossbar 1
#ਜੇ_ਅੰਤ /* GL_OES_texture_env_crossbar */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_OES_texture_mirrored_repeat
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OES_texture_mirrored_repeat 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MIRRORED_REPEAT_OES            0x8370
#ਜੇ_ਅੰਤ /* GL_OES_texture_mirrored_repeat */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_OES_texture_npot
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OES_texture_npot 1
#ਜੇ_ਅੰਤ /* GL_OES_texture_npot */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_OES_ਸ਼ੀਰਸ਼_array_object
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OES_ਸ਼ੀਰਸ਼_array_object 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸ਼ੀਰਸ਼_ARRAY_BINDING_OES       0x85B5
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLBINDVERTEXARRAYOESPROC) (GLuint array);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDELETEVERTEXARRAYSOESPROC) (GLsizei n, ਅਚਲ GLuint *arrays);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGENVERTEXARRAYSOESPROC) (GLsizei n, GLuint *arrays);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLboolean (GL_APIENTRYP PFNGLISVERTEXARRAYOESPROC) (GLuint array);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ GL_GLEXT_PROTOTYPES
GL_API ਖਾਲੀ GL_APIENTRY gl_Bind_ਸ਼ੀਰਸ਼_Array_OES (GLuint array);
GL_API ਖਾਲੀ GL_APIENTRY gl_Delete_ਸ਼ੀਰਸ਼_Arrays_OES (GLsizei n, ਅਚਲ GLuint *arrays);
GL_API ਖਾਲੀ GL_APIENTRY gl_Gen_ਸ਼ੀਰਸ਼_Arrays_OES (GLsizei n, GLuint *arrays);
GL_API GLboolean GL_APIENTRY gl_Is_ਸ਼ੀਰਸ਼_Array_OES (GLuint array);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* GL_OES_vertex_array_object */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_AMD_compressed_3DC_texture
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_AMD_compressed_3DC_texture 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_3DC_X_AMD                      0x87F9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_3DC_XY_AMD                     0x87FA
#ਜੇ_ਅੰਤ /* GL_AMD_compressed_3DC_texture */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_AMD_compressed_ATC_texture
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_AMD_compressed_ATC_texture 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ATC_RGB_AMD                    0x8C92
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ATC_RGBA_EXPLICIT_ALPHA_AMD    0x8C93
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD 0x87EE
#ਜੇ_ਅੰਤ /* GL_AMD_compressed_ATC_texture */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_APPLE_copy_texture_ਪੱਧਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_APPLE_copy_texture_ਪੱਧਰ 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLCOPYTEXTURELEVELSAPPLEPROC) (GLuint destinationTexture, GLuint ਸਰੋਤ_Texture, GLint ਸਰੋਤ_ਅਧਾਰ_Level, GLsizei ਸਰੋਤ_Level_ਗਿਣਤੀ);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ GL_GLEXT_PROTOTYPES
GL_API ਖਾਲੀ GL_APIENTRY gl_Copy_Texture_ਪੱਧਰ_APPLE (GLuint destinationTexture, GLuint ਸਰੋਤ_Texture, GLint ਸਰੋਤ_ਅਧਾਰ_Level, GLsizei ਸਰੋਤ_Level_ਗਿਣਤੀ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* GL_APPLE_copy_texture_levels */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_APPLE_framebuffer_multisample
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_APPLE_framebuffer_multisample 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RENDERBUFFER_SAMPLES_APPLE     0x8CAB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_APPLE 0x8D56
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_SAMPLES_APPLE              0x8D57
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_READ_FRAMEBUFFER_APPLE         0x8CA8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DRAW_FRAMEBUFFER_APPLE         0x8CA9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DRAW_FRAMEBUFFER_BINDING_APPLE 0x8CA6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_READ_FRAMEBUFFER_BINDING_APPLE 0x8CAA
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEAPPLEPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLsizei samples, GLenum internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLRESOLVEMULTISAMPLEFRAMEBUFFERAPPLEPROC) (ਖਾਲੀ);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ GL_GLEXT_PROTOTYPES
GL_API ਖਾਲੀ GL_APIENTRY glRenderbufferStorageMultisampleAPPLE (GLenum ਨਿਸ਼ਾਨਾ, GLsizei samples, GLenum internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ);
GL_API ਖਾਲੀ GL_APIENTRY glResolveMultisampleFramebufferAPPLE (ਖਾਲੀ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* GL_APPLE_framebuffer_multisample */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_APPLE_sync
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_APPLE_sync 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ __GLsync *GLsync;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ khronos_uint64_t GLuint64;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ khronos_int64_t GLint64;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SYNC_OBJECT_APPLE              0x8A53
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_SERVER_WAIT_TIMEOUT_APPLE  0x9111
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OBJECT_TYPE_APPLE              0x9112
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SYNC_CONDITION_APPLE           0x9113
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SYNC_ਸਥਿਤੀ_APPLE              0x9114
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SYNC_FLAGS_APPLE               0x9115
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SYNC_FENCE_APPLE               0x9116
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SYNC_GPU_COMMANDS_COMPLETE_APPLE 0x9117
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNALED_APPLE               0x9118
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SIGNALED_APPLE                 0x9119
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ALREADY_SIGNALED_APPLE         0x911A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TIMEOUT_EXPIRED_APPLE          0x911B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_CONDITION_SATISFIED_APPLE      0x911C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_WAIT_FAILED_APPLE              0x911D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SYNC_FLUSH_COMMANDS_ਦੋਆਧਾਰੀ_ਅੰਕ_APPLE  0x00000001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TIMEOUT_IGNORED_APPLE          0xFFFFFFFFFFFFFFFFull
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLsync (GL_APIENTRYP PFNGLFENCESYNCAPPLEPROC) (GLenum condition, GLbitfield flags);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLboolean (GL_APIENTRYP PFNGLISSYNCAPPLEPROC) (GLsync sync);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDELETESYNCAPPLEPROC) (GLsync sync);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLenum (GL_APIENTRYP PFNGLCLIENTWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETINTEGER64VAPPLEPROC) (GLenum pname, GLint64 *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETSYNCIVAPPLEPROC) (GLsync sync, GLenum pname, GLsizei ਗਿਣਤੀ_2, GLsizei *ਲੰਮਾਈ, GLint *ਮੁੱਲਾਂ);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ GL_GLEXT_PROTOTYPES
GL_API GLsync GL_APIENTRY glFenceSyncAPPLE (GLenum condition, GLbitfield flags);
GL_API GLboolean GL_APIENTRY glIsSyncAPPLE (GLsync sync);
GL_API ਖਾਲੀ GL_APIENTRY glDeleteSyncAPPLE (GLsync sync);
GL_API GLenum GL_APIENTRY glClientWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_API ਖਾਲੀ GL_APIENTRY glWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_API ਖਾਲੀ GL_APIENTRY glGetInteger64vAPPLE (GLenum pname, GLint64 *params);
GL_API ਖਾਲੀ GL_APIENTRY glGetSyncivAPPLE (GLsync sync, GLenum pname, GLsizei ਗਿਣਤੀ_2, GLsizei *ਲੰਮਾਈ, GLint *ਮੁੱਲਾਂ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* GL_APPLE_sync */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_APPLE_texture_2D_limited_npot
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_APPLE_texture_2D_limited_npot 1
#ਜੇ_ਅੰਤ /* GL_APPLE_texture_2D_limited_npot */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_APPLE_texture_format_BGRA8888
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_APPLE_texture_format_BGRA8888 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_BGRA_EXT                       0x80E1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_BGRA8_EXT                      0x93A1
#ਜੇ_ਅੰਤ /* GL_APPLE_texture_format_BGRA8888 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_APPLE_texture_max_level
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_APPLE_texture_max_level 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_MAX_LEVEL_APPLE        0x813D
#ਜੇ_ਅੰਤ /* GL_APPLE_texture_max_level */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_ARM_rgba8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ARM_rgba8 1
#ਜੇ_ਅੰਤ /* GL_ARM_rgba8 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_EXT_blend_minmax
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_EXT_blend_minmax 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MIN_EXT                        0x8007
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_EXT                        0x8008
#ਜੇ_ਅੰਤ /* GL_EXT_blend_minmax */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_EXT_debug_marker
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_EXT_debug_marker 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਅੱਖਰ GLchar;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLINSERTEVENTMARKEREXTPROC) (GLsizei ਲੰਮਾਈ, ਅਚਲ GLchar *marker);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPUSHGROUPMARKEREXTPROC) (GLsizei ਲੰਮਾਈ, ਅਚਲ GLchar *marker);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPOPGROUPMARKEREXTPROC) (ਖਾਲੀ);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ GL_GLEXT_PROTOTYPES
GL_API ਖਾਲੀ GL_APIENTRY gl_ਪਾਓ_Event_Marker_EXT (GLsizei ਲੰਮਾਈ, ਅਚਲ GLchar *marker);
GL_API ਖਾਲੀ GL_APIENTRY gl_ਧੱਕੋ_ਸਮੂਹ_Marker_EXT (GLsizei ਲੰਮਾਈ, ਅਚਲ GLchar *marker);
GL_API ਖਾਲੀ GL_APIENTRY gl_ਕੱਢੋ_ਸਮੂਹ_Marker_EXT (ਖਾਲੀ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* GL_EXT_debug_marker */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_EXT_discard_framebuffer
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_EXT_discard_framebuffer 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_EXT                      0x1800
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਡੂੰਘਾਈ_EXT                      0x1801
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STENCIL_EXT                    0x1802
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDISCARDFRAMEBUFFEREXTPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLsizei ਅੰਕ_Attachments, ਅਚਲ GLenum *attachments);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ GL_GLEXT_PROTOTYPES
GL_API ਖਾਲੀ GL_APIENTRY glDiscardFramebufferEXT (GLenum ਨਿਸ਼ਾਨਾ, GLsizei ਅੰਕ_Attachments, ਅਚਲ GLenum *attachments);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* GL_EXT_discard_framebuffer */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_EXT_map_ਬਫਰ_range
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_EXT_map_ਬਫਰ_range 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAP_READ_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT               0x0001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAP_WRITE_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT              0x0002
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAP_INVALIDATE_RANGE_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT   0x0004
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAP_INVALIDATE_ਬਫਰ_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT  0x0008
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAP_FLUSH_EXPLICIT_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT     0x0010
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAP_UNSYNCHRONIZED_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT     0x0020
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ *(GL_APIENTRYP PFNGLMAPBUFFERRANGEEXTPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLintptr ਵਿੱਥ_2, GLsizeiptr ਲੰਮਾਈ, GLbitfield access);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEEXTPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLintptr ਵਿੱਥ_2, GLsizeiptr ਲੰਮਾਈ);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ GL_GLEXT_PROTOTYPES
GL_API ਖਾਲੀ *GL_APIENTRY gl_Map_ਬਫਰ_Range_EXT (GLenum ਨਿਸ਼ਾਨਾ, GLintptr ਵਿੱਥ_2, GLsizeiptr ਲੰਮਾਈ, GLbitfield access);
GL_API ਖਾਲੀ GL_APIENTRY gl_Flush_Mapped_ਬਫਰ_Range_EXT (GLenum ਨਿਸ਼ਾਨਾ, GLintptr ਵਿੱਥ_2, GLsizeiptr ਲੰਮਾਈ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* GL_EXT_map_buffer_range */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_EXT_multi_draw_arrays
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_EXT_multi_draw_arrays 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLMULTIDRAWARRAYSEXTPROC) (GLenum ਬਹੁਲਕ, ਅਚਲ GLint *ਪਹਿਲਾ, ਅਚਲ GLsizei *ਗਿਣਤੀ_2, GLsizei primcount);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSEXTPROC) (GLenum ਬਹੁਲਕ, ਅਚਲ GLsizei *ਗਿਣਤੀ_2, GLenum type, ਅਚਲ ਖਾਲੀ *ਅਚਲ*indices, GLsizei primcount);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ GL_GLEXT_PROTOTYPES
GL_API ਖਾਲੀ GL_APIENTRY glMultiDrawArraysEXT (GLenum ਬਹੁਲਕ, ਅਚਲ GLint *ਪਹਿਲਾ, ਅਚਲ GLsizei *ਗਿਣਤੀ_2, GLsizei primcount);
GL_API ਖਾਲੀ GL_APIENTRY glMultiDrawElementsEXT (GLenum ਬਹੁਲਕ, ਅਚਲ GLsizei *ਗਿਣਤੀ_2, GLenum type, ਅਚਲ ਖਾਲੀ *ਅਚਲ*indices, GLsizei primcount);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* GL_EXT_multi_draw_arrays */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_EXT_multisampled_render_ਮੰਜ਼ਿਲ_texture
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_EXT_multisampled_render_ਮੰਜ਼ਿਲ_texture 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SAMPLES_EXT 0x8D6C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RENDERBUFFER_SAMPLES_EXT       0x8CAB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT 0x8D56
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_SAMPLES_EXT                0x8D57
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLsizei samples, GLenum internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEEXTPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ GL_GLEXT_PROTOTYPES
GL_API ਖਾਲੀ GL_APIENTRY glRenderbufferStorageMultisampleEXT (GLenum ਨਿਸ਼ਾਨਾ, GLsizei samples, GLenum internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ);
GL_API ਖਾਲੀ GL_APIENTRY glFramebufferTexture2DMultisampleEXT (GLenum ਨਿਸ਼ਾਨਾ, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* GL_EXT_multisampled_render_to_texture */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_EXT_read_format_bgra
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_EXT_read_format_bgra 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT 0x8365
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT 0x8366
#ਜੇ_ਅੰਤ /* GL_EXT_read_format_bgra */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_EXT_robustness
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_EXT_robustness 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_GUILTY_CONTEXT_RESET_EXT       0x8253
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_INNOCENT_CONTEXT_RESET_EXT     0x8254
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNKNOWN_CONTEXT_RESET_EXT      0x8255
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_CONTEXT_ROBUST_ACCESS_EXT      0x90F3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RESET_NOTIFICATION_STRATEGY_EXT 0x8256
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_LOSE_CONTEXT_ON_RESET_EXT      0x8252
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_NO_RESET_NOTIFICATION_EXT      0x8261
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLenum (GL_APIENTRYP PFNGLGETGRAPHICSRESETSTATUSEXTPROC) (ਖਾਲੀ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLREADNPIXELSEXTPROC) (GLint x, GLint y, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLenum format, GLenum type, GLsizei buf_ਮਾਪ, ਖਾਲੀ *ਅੰਕੜੇ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETNUNIFORMFVEXTPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei buf_ਮਾਪ, GLfloat *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETNUNIFORMIVEXTPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei buf_ਮਾਪ, GLint *params);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ GL_GLEXT_PROTOTYPES
GL_API GLenum GL_APIENTRY gl_Get_Graphics_Reset_ਸਥਿਤੀ_EXT (ਖਾਲੀ);
GL_API ਖਾਲੀ GL_APIENTRY glReadnPixelsEXT (GLint x, GLint y, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLenum format, GLenum type, GLsizei buf_ਮਾਪ, ਖਾਲੀ *ਅੰਕੜੇ);
GL_API ਖਾਲੀ GL_APIENTRY glGetnUniformfvEXT (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei buf_ਮਾਪ, GLfloat *params);
GL_API ਖਾਲੀ GL_APIENTRY glGetnUniformivEXT (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei buf_ਮਾਪ, GLint *params);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* GL_EXT_robustness */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_EXT_sRGB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_EXT_sRGB 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SRGB_EXT                       0x8C40
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SRGB_ALPHA_EXT                 0x8C42
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SRGB8_ALPHA8_EXT               0x8C43
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING_EXT 0x8210
#ਜੇ_ਅੰਤ /* GL_EXT_sRGB */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_EXT_texture_compression_dxt1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_EXT_texture_compression_dxt1 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_RGB_S3TC_DXT1_EXT   0x83F0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_RGBA_S3TC_DXT1_EXT  0x83F1
#ਜੇ_ਅੰਤ /* GL_EXT_texture_compression_dxt1 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_EXT_texture_filter_anisotropic
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_EXT_texture_filter_anisotropic 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#ਜੇ_ਅੰਤ /* GL_EXT_texture_filter_anisotropic */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_EXT_texture_format_BGRA8888
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_EXT_texture_format_BGRA8888 1
#ਜੇ_ਅੰਤ /* GL_EXT_texture_format_BGRA8888 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_EXT_texture_lod_bias
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_EXT_texture_lod_bias 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_TEXTURE_LOD_BIAS_EXT       0x84FD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_FILTER_CONTROL_EXT     0x8500
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_LOD_BIAS_EXT           0x8501
#ਜੇ_ਅੰਤ /* GL_EXT_texture_lod_bias */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_EXT_texture_storage
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_EXT_texture_storage 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_IMMUTABLE_FORMAT_EXT   0x912F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ALPHA8_EXT                     0x803C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_LUMINANCE8_EXT                 0x8040
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_LUMINANCE8_ALPHA8_EXT          0x8045
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGBA32F_EXT                    0x8814
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGB32F_EXT                     0x8815
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ALPHA32F_EXT                   0x8816
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_LUMINANCE32F_EXT               0x8818
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_LUMINANCE_ALPHA32F_EXT         0x8819
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGBA16F_EXT                    0x881A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGB16F_EXT                     0x881B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ALPHA16F_EXT                   0x881C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_LUMINANCE16F_EXT               0x881E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_LUMINANCE_ALPHA16F_EXT         0x881F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_R8_EXT                         0x8229
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RG8_EXT                        0x822B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_R32F_EXT                       0x822E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RG32F_EXT                      0x8230
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_R16F_EXT                       0x822D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RG16F_EXT                      0x822F
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLTEXSTORAGE1DEXTPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLsizei ਪੱਧਰ, GLenum internalformat, GLsizei ਚੌੜਾਈ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLTEXSTORAGE2DEXTPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLsizei ਪੱਧਰ, GLenum internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLTEXSTORAGE3DEXTPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLsizei ਪੱਧਰ, GLenum internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLsizei ਡੂੰਘਾਈ_2);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLTEXTURESTORAGE1DEXTPROC) (GLuint texture, GLenum ਨਿਸ਼ਾਨਾ, GLsizei ਪੱਧਰ, GLenum internalformat, GLsizei ਚੌੜਾਈ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLTEXTURESTORAGE2DEXTPROC) (GLuint texture, GLenum ਨਿਸ਼ਾਨਾ, GLsizei ਪੱਧਰ, GLenum internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLTEXTURESTORAGE3DEXTPROC) (GLuint texture, GLenum ਨਿਸ਼ਾਨਾ, GLsizei ਪੱਧਰ, GLenum internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLsizei ਡੂੰਘਾਈ_2);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ GL_GLEXT_PROTOTYPES
GL_API ਖਾਲੀ GL_APIENTRY glTexStorage1DEXT (GLenum ਨਿਸ਼ਾਨਾ, GLsizei ਪੱਧਰ, GLenum internalformat, GLsizei ਚੌੜਾਈ);
GL_API ਖਾਲੀ GL_APIENTRY glTexStorage2DEXT (GLenum ਨਿਸ਼ਾਨਾ, GLsizei ਪੱਧਰ, GLenum internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ);
GL_API ਖਾਲੀ GL_APIENTRY glTexStorage3DEXT (GLenum ਨਿਸ਼ਾਨਾ, GLsizei ਪੱਧਰ, GLenum internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLsizei ਡੂੰਘਾਈ_2);
GL_API ਖਾਲੀ GL_APIENTRY glTextureStorage1DEXT (GLuint texture, GLenum ਨਿਸ਼ਾਨਾ, GLsizei ਪੱਧਰ, GLenum internalformat, GLsizei ਚੌੜਾਈ);
GL_API ਖਾਲੀ GL_APIENTRY glTextureStorage2DEXT (GLuint texture, GLenum ਨਿਸ਼ਾਨਾ, GLsizei ਪੱਧਰ, GLenum internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ);
GL_API ਖਾਲੀ GL_APIENTRY glTextureStorage3DEXT (GLuint texture, GLenum ਨਿਸ਼ਾਨਾ, GLsizei ਪੱਧਰ, GLenum internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLsizei ਡੂੰਘਾਈ_2);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* GL_EXT_texture_storage */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_IMG_multisampled_render_ਮੰਜ਼ਿਲ_texture
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_IMG_multisampled_render_ਮੰਜ਼ਿਲ_texture 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RENDERBUFFER_SAMPLES_IMG       0x9133
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_IMG 0x9134
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_SAMPLES_IMG                0x9135
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_SAMPLES_IMG            0x9136
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEIMGPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLsizei samples, GLenum internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEIMGPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ GL_GLEXT_PROTOTYPES
GL_API ਖਾਲੀ GL_APIENTRY glRenderbufferStorageMultisampleIMG (GLenum ਨਿਸ਼ਾਨਾ, GLsizei samples, GLenum internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ);
GL_API ਖਾਲੀ GL_APIENTRY glFramebufferTexture2DMultisampleIMG (GLenum ਨਿਸ਼ਾਨਾ, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* GL_IMG_multisampled_render_to_texture */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_IMG_read_format
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_IMG_read_format 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_BGRA_IMG                       0x80E1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNED_SHORT_4_4_4_4_REV_IMG 0x8365
#ਜੇ_ਅੰਤ /* GL_IMG_read_format */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_IMG_texture_compression_pvrtc
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_IMG_texture_compression_pvrtc 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG 0x8C00
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG 0x8C01
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG 0x8C02
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG 0x8C03
#ਜੇ_ਅੰਤ /* GL_IMG_texture_compression_pvrtc */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_IMG_texture_env_enhanced_fixed_function
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_IMG_texture_env_enhanced_fixed_function 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MODULATE_COLOR_IMG             0x8C04
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RECIP_ਜੋੜੋ_SIGNED_ALPHA_IMG     0x8C05
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_ALPHA_MODULATE_IMG     0x8C06
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਗੁਣਕ_ALPHA_MODULATE_IMG      0x8C07
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAGMENT_ALPHA_MODULATE_IMG    0x8C08
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਜੋੜੋ_BLEND_IMG                  0x8C09
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DOT3_RGBA_IMG                  0x86AF
#ਜੇ_ਅੰਤ /* GL_IMG_texture_env_enhanced_fixed_function */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_IMG_user_clip_plane
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_IMG_user_clip_plane 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_CLIP_PLANE0_IMG                0x3000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_CLIP_PLANE1_IMG                0x3001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_CLIP_PLANE2_IMG                0x3002
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_CLIP_PLANE3_IMG                0x3003
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_CLIP_PLANE4_IMG                0x3004
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_CLIP_PLANE5_IMG                0x3005
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_CLIP_PLANES_IMG            0x0D32
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLCLIPPLANEFIMGPROC) (GLenum p, ਅਚਲ GLfloat *eqn);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLCLIPPLANEXIMGPROC) (GLenum p, ਅਚਲ GLfixed *eqn);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ GL_GLEXT_PROTOTYPES
GL_API ਖਾਲੀ GL_APIENTRY glClipPlanefIMG (GLenum p, ਅਚਲ GLfloat *eqn);
GL_API ਖਾਲੀ GL_APIENTRY glClipPlanexIMG (GLenum p, ਅਚਲ GLfixed *eqn);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* GL_IMG_user_clip_plane */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_NV_fence
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_NV_fence 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ALL_COMPLETED_NV               0x84F2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FENCE_ਸਥਿਤੀ_NV                0x84F3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FENCE_CONDITION_NV             0x84F4
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDELETEFENCESNVPROC) (GLsizei n, ਅਚਲ GLuint *fences);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGENFENCESNVPROC) (GLsizei n, GLuint *fences);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLboolean (GL_APIENTRYP PFNGLISFENCENVPROC) (GLuint fence);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLboolean (GL_APIENTRYP PFNGLTESTFENCENVPROC) (GLuint fence);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETFENCEIVNVPROC) (GLuint fence, GLenum pname, GLint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLFINISHFENCENVPROC) (GLuint fence);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLSETFENCENVPROC) (GLuint fence, GLenum condition);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ GL_GLEXT_PROTOTYPES
GL_API ਖਾਲੀ GL_APIENTRY glDeleteFencesNV (GLsizei n, ਅਚਲ GLuint *fences);
GL_API ਖਾਲੀ GL_APIENTRY glGenFencesNV (GLsizei n, GLuint *fences);
GL_API GLboolean GL_APIENTRY glIsFenceNV (GLuint fence);
GL_API GLboolean GL_APIENTRY glTestFenceNV (GLuint fence);
GL_API ਖਾਲੀ GL_APIENTRY glGetFenceivNV (GLuint fence, GLenum pname, GLint *params);
GL_API ਖਾਲੀ GL_APIENTRY gl_ਅੰਤ_Fence_NV (GLuint fence);
GL_API ਖਾਲੀ GL_APIENTRY gl_ਸੈੱਟ_Fence_NV (GLuint fence, GLenum condition);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* GL_NV_fence */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_QCOM_driver_control
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_QCOM_driver_control 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETDRIVERCONTROLSQCOMPROC) (GLint *ਅੰਕ, GLsizei ਮਾਪ, GLuint *driverControls);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETDRIVERCONTROLSTRINGQCOMPROC) (GLuint driverControl, GLsizei buf_ਮਾਪ, GLsizei *ਲੰਮਾਈ, GLchar *driverControlString);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLENABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDISABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ GL_GLEXT_PROTOTYPES
GL_API ਖਾਲੀ GL_APIENTRY glGetDriverControlsQCOM (GLint *ਅੰਕ, GLsizei ਮਾਪ, GLuint *driverControls);
GL_API ਖਾਲੀ GL_APIENTRY glGetDriverControlStringQCOM (GLuint driverControl, GLsizei buf_ਮਾਪ, GLsizei *ਲੰਮਾਈ, GLchar *driverControlString);
GL_API ਖਾਲੀ GL_APIENTRY glEnableDriverControlQCOM (GLuint driverControl);
GL_API ਖਾਲੀ GL_APIENTRY glDisableDriverControlQCOM (GLuint driverControl);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* GL_QCOM_driver_control */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_QCOM_extended_get
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_QCOM_extended_get 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_ਚੌੜਾਈ_QCOM             0x8BD2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_ਉਚਾਈ_QCOM            0x8BD3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_ਡੂੰਘਾਈ_QCOM             0x8BD4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_ਅੰਦਰੂਨੀ_FORMAT_QCOM   0x8BD5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_FORMAT_QCOM            0x8BD6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_TYPE_QCOM              0x8BD7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_IMAGE_VALID_QCOM       0x8BD8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_ਅੰਕ_ਪੱਧਰ_QCOM        0x8BD9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_ਨਿਸ਼ਾਨਾ_QCOM            0x8BDA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_OBJECT_VALID_QCOM      0x8BDB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STATE_RESTORE                  0x8BDC
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLEXTGETTEXTURESQCOMPROC) (GLuint *textures, GLint maxTextures, GLint *ਅੰਕ_Textures);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLEXTGETBUFFERSQCOMPROC) (GLuint *buffers, GLint maxBuffers, GLint *ਅੰਕ_Buffers);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLEXTGETRENDERBUFFERSQCOMPROC) (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *ਅੰਕ_Renderbuffers);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLEXTGETFRAMEBUFFERSQCOMPROC) (GLuint *framebuffers, GLint maxFramebuffers, GLint *ਅੰਕ_Framebuffers);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLEXTGETTEXLEVELPARAMETERIVQCOMPROC) (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLEXTTEXOBJECTSTATEOVERRIDEIQCOMPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLint param);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLEXTGETTEXSUBIMAGEQCOMPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLsizei ਡੂੰਘਾਈ_2, GLenum format, GLenum type, ਖਾਲੀ *texels);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLEXTGETBUFFERPOINTERVQCOMPROC) (GLenum ਨਿਸ਼ਾਨਾ, ਖਾਲੀ **params);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ GL_GLEXT_PROTOTYPES
GL_API ਖਾਲੀ GL_APIENTRY glExtGetTexturesQCOM (GLuint *textures, GLint maxTextures, GLint *ਅੰਕ_Textures);
GL_API ਖਾਲੀ GL_APIENTRY glExtGetBuffersQCOM (GLuint *buffers, GLint maxBuffers, GLint *ਅੰਕ_Buffers);
GL_API ਖਾਲੀ GL_APIENTRY glExtGetRenderbuffersQCOM (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *ਅੰਕ_Renderbuffers);
GL_API ਖਾਲੀ GL_APIENTRY glExtGetFramebuffersQCOM (GLuint *framebuffers, GLint maxFramebuffers, GLint *ਅੰਕ_Framebuffers);
GL_API ਖਾਲੀ GL_APIENTRY glExtGetTexLevelParameterivQCOM (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
GL_API ਖਾਲੀ GL_APIENTRY glExtTexObjectStateOverrideiQCOM (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLint param);
GL_API ਖਾਲੀ GL_APIENTRY glExtGetTexSubImageQCOM (GLenum ਨਿਸ਼ਾਨਾ, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLsizei ਡੂੰਘਾਈ_2, GLenum format, GLenum type, ਖਾਲੀ *texels);
GL_API ਖਾਲੀ GL_APIENTRY gl_Ext_Get_ਬਫਰ_Pointerv_QCOM (GLenum ਨਿਸ਼ਾਨਾ, ਖਾਲੀ **params);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* GL_QCOM_extended_get */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_QCOM_extended_get2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_QCOM_extended_get2 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLEXTGETSHADERSQCOMPROC) (GLuint *shaders, GLint maxShaders, GLint *ਅੰਕ_Shaders);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLEXTGETPROGRAMSQCOMPROC) (GLuint *programs, GLint maxPrograms, GLint *ਅੰਕ_Programs);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLboolean (GL_APIENTRYP PFNGLEXTISPROGRAMBINARYQCOMPROC) (GLuint ਪ੍ਰੋਗਰਾਮ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLEXTGETPROGRAMBINARYSOURCEQCOMPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLenum shadertype, GLchar *ਸਰੋਤ, GLint *ਲੰਮਾਈ);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ GL_GLEXT_PROTOTYPES
GL_API ਖਾਲੀ GL_APIENTRY glExtGetShadersQCOM (GLuint *shaders, GLint maxShaders, GLint *ਅੰਕ_Shaders);
GL_API ਖਾਲੀ GL_APIENTRY glExtGetProgramsQCOM (GLuint *programs, GLint maxPrograms, GLint *ਅੰਕ_Programs);
GL_API GLboolean GL_APIENTRY gl_Ext_Is_ਪ੍ਰੋਗਰਾਮ_ਦੁਆਧਾਰੀ_QCOM (GLuint ਪ੍ਰੋਗਰਾਮ);
GL_API ਖਾਲੀ GL_APIENTRY gl_Ext_Get_ਪ੍ਰੋਗਰਾਮ_ਦੁਆਧਾਰੀ_ਸਰੋਤ_QCOM (GLuint ਪ੍ਰੋਗਰਾਮ, GLenum shadertype, GLchar *ਸਰੋਤ, GLint *ਲੰਮਾਈ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* GL_QCOM_extended_get2 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_QCOM_perfmon_global_ਬਹੁਲਕ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_QCOM_perfmon_global_ਬਹੁਲਕ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_PERFMON_GLOBAL_ਬਹੁਲਕ_QCOM       0x8FA0
#ਜੇ_ਅੰਤ /* GL_QCOM_perfmon_global_mode */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_QCOM_tiled_rendering
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_QCOM_tiled_rendering 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ਬਫਰ_BIT0_QCOM         0x00000001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ਬਫਰ_BIT1_QCOM         0x00000002
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ਬਫਰ_BIT2_QCOM         0x00000004
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ਬਫਰ_BIT3_QCOM         0x00000008
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ਬਫਰ_BIT4_QCOM         0x00000010
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ਬਫਰ_BIT5_QCOM         0x00000020
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ਬਫਰ_BIT6_QCOM         0x00000040
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ਬਫਰ_BIT7_QCOM         0x00000080
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਡੂੰਘਾਈ_ਬਫਰ_BIT0_QCOM         0x00000100
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਡੂੰਘਾਈ_ਬਫਰ_BIT1_QCOM         0x00000200
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਡੂੰਘਾਈ_ਬਫਰ_BIT2_QCOM         0x00000400
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਡੂੰਘਾਈ_ਬਫਰ_BIT3_QCOM         0x00000800
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਡੂੰਘਾਈ_ਬਫਰ_BIT4_QCOM         0x00001000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਡੂੰਘਾਈ_ਬਫਰ_BIT5_QCOM         0x00002000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਡੂੰਘਾਈ_ਬਫਰ_BIT6_QCOM         0x00004000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਡੂੰਘਾਈ_ਬਫਰ_BIT7_QCOM         0x00008000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STENCIL_ਬਫਰ_BIT0_QCOM       0x00010000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STENCIL_ਬਫਰ_BIT1_QCOM       0x00020000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STENCIL_ਬਫਰ_BIT2_QCOM       0x00040000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STENCIL_ਬਫਰ_BIT3_QCOM       0x00080000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STENCIL_ਬਫਰ_BIT4_QCOM       0x00100000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STENCIL_ਬਫਰ_BIT5_QCOM       0x00200000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STENCIL_ਬਫਰ_BIT6_QCOM       0x00400000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STENCIL_ਬਫਰ_BIT7_QCOM       0x00800000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MULTISAMPLE_ਬਫਰ_BIT0_QCOM   0x01000000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MULTISAMPLE_ਬਫਰ_BIT1_QCOM   0x02000000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MULTISAMPLE_ਬਫਰ_BIT2_QCOM   0x04000000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MULTISAMPLE_ਬਫਰ_BIT3_QCOM   0x08000000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MULTISAMPLE_ਬਫਰ_BIT4_QCOM   0x10000000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MULTISAMPLE_ਬਫਰ_BIT5_QCOM   0x20000000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MULTISAMPLE_ਬਫਰ_BIT6_QCOM   0x40000000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MULTISAMPLE_ਬਫਰ_BIT7_QCOM   0x80000000
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLSTARTTILINGQCOMPROC) (GLuint x, GLuint y, GLuint ਚੌੜਾਈ, GLuint ਉਚਾਈ, GLbitfield preserve_ਨਕਾਬ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLENDTILINGQCOMPROC) (GLbitfield preserve_ਨਕਾਬ);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ GL_GLEXT_PROTOTYPES
GL_API ਖਾਲੀ GL_APIENTRY gl_ਸ਼ੁਰੂ_Tiling_QCOM (GLuint x, GLuint y, GLuint ਚੌੜਾਈ, GLuint ਉਚਾਈ, GLbitfield preserve_ਨਕਾਬ);
GL_API ਖਾਲੀ GL_APIENTRY gl_ਸਿਰਾ_Tiling_QCOM (GLbitfield preserve_ਨਕਾਬ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* GL_QCOM_tiled_rendering */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_QCOM_writeonly_rendering
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_QCOM_writeonly_rendering 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_WRITEONLY_RENDERING_QCOM       0x8823
#ਜੇ_ਅੰਤ /* GL_QCOM_writeonly_rendering */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ
