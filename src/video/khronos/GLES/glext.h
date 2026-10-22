#جے_بنا_تعریف __gles1_glext_h_
#تعریف_کرو __gles1_glext_h_ 1

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

#جے_بنا_تعریف GL_KHR_debug
#تعریف_کرو GL_KHR_debug 1
#جے_انت /* GL_KHR_debug */

#جے_بنا_تعریف GL_OES_EGL_image
#تعریف_کرو GL_OES_EGL_image 1
تعريفنوع فراغ *GLeglImageOES;
تعريفنوع فراغ (GL_APIENTRYP PFNGLEGLIMAGETARGETTEXTURE2DOESPROC) (GLenum نشانہ, GLeglImageOES image);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEGLIMAGETARGETRENDERBUFFERSTORAGEOESPROC) (GLenum نشانہ, GLeglImageOES image);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY gl_EGLImage_نشانہ_Texture2_DOES (GLenum نشانہ, GLeglImageOES image);
GL_API فراغ GL_APIENTRY gl_EGLImage_نشانہ_Renderbuffer_Storage_OES (GLenum نشانہ, GLeglImageOES image);
#جے_انت
#جے_انت /* GL_OES_EGL_image */

#جے_بنا_تعریف GL_OES_EGL_image_external
#تعریف_کرو GL_OES_EGL_image_external 1
#تعریف_کرو GL_TEXTURE_EXTERNAL_OES           0x8D65
#تعریف_کرو GL_TEXTURE_BINDING_EXTERNAL_OES   0x8D67
#تعریف_کرو GL_REQUIRED_TEXTURE_IMAGE_UNITS_OES 0x8D68
#جے_انت /* GL_OES_EGL_image_external */

#جے_بنا_تعریف GL_OES_blend_equation_separate
#تعریف_کرو GL_OES_blend_equation_separate 1
#تعریف_کرو GL_BLEND_EQUATION_RGB_OES         0x8009
#تعریف_کرو GL_BLEND_EQUATION_ALPHA_OES       0x883D
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEOESPROC) (GLenum منوال_RGB, GLenum منوال_Alpha);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glBlendEquationSeparateOES (GLenum منوال_RGB, GLenum منوال_Alpha);
#جے_انت
#جے_انت /* GL_OES_blend_equation_separate */

#جے_بنا_تعریف GL_OES_blend_func_separate
#تعریف_کرو GL_OES_blend_func_separate 1
#تعریف_کرو GL_BLEND_DST_RGB_OES              0x80C8
#تعریف_کرو GL_BLEND_SRC_RGB_OES              0x80C9
#تعریف_کرو GL_BLEND_DST_ALPHA_OES            0x80CA
#تعریف_کرو GL_BLEND_SRC_ALPHA_OES            0x80CB
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEOESPROC) (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glBlendFuncSeparateOES (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
#جے_انت
#جے_انت /* GL_OES_blend_func_separate */

#جے_بنا_تعریف GL_OES_blend_گھٹاؤ
#تعریف_کرو GL_OES_blend_گھٹاؤ 1
#تعریف_کرو GL_BLEND_EQUATION_OES             0x8009
#تعریف_کرو GL_FUNC_جوڑو_OES                   0x8006
#تعریف_کرو GL_FUNC_گھٹاؤ_OES              0x800A
#تعریف_کرو GL_FUNC_الٹ_گھٹاؤ_OES      0x800B
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONOESPROC) (GLenum منوال);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glBlendEquationOES (GLenum منوال);
#جے_انت
#جے_انت /* GL_OES_blend_subtract */

#جے_بنا_تعریف GL_OES_byte_coordinates
#تعریف_کرو GL_OES_byte_coordinates 1
#جے_انت /* GL_OES_byte_coordinates */

#جے_بنا_تعریف GL_OES_compressed_ETC1_RGB8_sub_texture
#تعریف_کرو GL_OES_compressed_ETC1_RGB8_sub_texture 1
#جے_انت /* GL_OES_compressed_ETC1_RGB8_sub_texture */

#جے_بنا_تعریف GL_OES_compressed_ETC1_RGB8_texture
#تعریف_کرو GL_OES_compressed_ETC1_RGB8_texture 1
#تعریف_کرو GL_ETC1_RGB8_OES                  0x8D64
#جے_انت /* GL_OES_compressed_ETC1_RGB8_texture */

#جے_بنا_تعریف GL_OES_depth24
#تعریف_کرو GL_OES_depth24 1
#تعریف_کرو GL_ڈونگھائی_COMPONENT24_OES          0x81A6
#جے_انت /* GL_OES_depth24 */

#جے_بنا_تعریف GL_OES_depth32
#تعریف_کرو GL_OES_depth32 1
#تعریف_کرو GL_ڈونگھائی_COMPONENT32_OES          0x81A7
#جے_انت /* GL_OES_depth32 */

#جے_بنا_تعریف GL_OES_draw_texture
#تعریف_کرو GL_OES_draw_texture 1
#تعریف_کرو GL_TEXTURE_CROP_RECT_OES          0x8B9D
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXSOESPROC) (GLshort x, GLshort y, GLshort z, GLshort چوڑائی, GLshort اچائی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXIOESPROC) (GLint x, GLint y, GLint z, GLint چوڑائی, GLint اچائی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXXOESPROC) (GLfixed x, GLfixed y, GLfixed z, GLfixed چوڑائی, GLfixed اچائی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXSVOESPROC) (ثابت GLshort *coords);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXIVOESPROC) (ثابت GLint *coords);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXXVOESPROC) (ثابت GLfixed *coords);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXFOESPROC) (GLfloat x, GLfloat y, GLfloat z, GLfloat چوڑائی, GLfloat اچائی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXFVOESPROC) (ثابت GLfloat *coords);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glDrawTexsOES (GLshort x, GLshort y, GLshort z, GLshort چوڑائی, GLshort اچائی);
GL_API فراغ GL_APIENTRY glDrawTexiOES (GLint x, GLint y, GLint z, GLint چوڑائی, GLint اچائی);
GL_API فراغ GL_APIENTRY glDrawTexxOES (GLfixed x, GLfixed y, GLfixed z, GLfixed چوڑائی, GLfixed اچائی);
GL_API فراغ GL_APIENTRY glDrawTexsvOES (ثابت GLshort *coords);
GL_API فراغ GL_APIENTRY glDrawTexivOES (ثابت GLint *coords);
GL_API فراغ GL_APIENTRY glDrawTexxvOES (ثابت GLfixed *coords);
GL_API فراغ GL_APIENTRY glDrawTexfOES (GLfloat x, GLfloat y, GLfloat z, GLfloat چوڑائی, GLfloat اچائی);
GL_API فراغ GL_APIENTRY glDrawTexfvOES (ثابت GLfloat *coords);
#جے_انت
#جے_انت /* GL_OES_draw_texture */

#جے_بنا_تعریف GL_OES_element_اشاریہ_uint
#تعریف_کرو GL_OES_element_اشاریہ_uint 1
#تعریف_کرو GL_UNSIGNED_INT                   0x1405
#جے_انت /* GL_OES_element_index_uint */

#جے_بنا_تعریف GL_OES_extended_میٹرکس_palette
#تعریف_کرو GL_OES_extended_میٹرکس_palette 1
#جے_انت /* GL_OES_extended_matrix_palette */

#جے_بنا_تعریف GL_OES_fbo_render_mipmap
#تعریف_کرو GL_OES_fbo_render_mipmap 1
#جے_انت /* GL_OES_fbo_render_mipmap */

#جے_بنا_تعریف GL_OES_fixed_نقطہ
#تعریف_کرو GL_OES_fixed_نقطہ 1
#تعریف_کرو GL_FIXED_OES                      0x140C
تعريفنوع فراغ (GL_APIENTRYP PFNGLALPHAFUNCXOESPROC) (GLenum func, GLfixed ref);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARCOLORXOESPROC) (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARDEPTHXOESPROC) (GLfixed ڈونگھائی_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLIPPLANEXOESPROC) (GLenum plane, ثابت GLfixed *equation);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOLOR4XOESPROC) (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHRANGEXOESPROC) (GLfixed n, GLfixed f);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFOGXOESPROC) (GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFOGXVOESPROC) (GLenum pname, ثابت GLfixed *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRUSTUMXOESPROC) (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETCLIPPLANEXOESPROC) (GLenum plane, GLfixed *equation);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFIXEDVOESPROC) (GLenum pname, GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXENVXVOESPROC) (GLenum نشانہ, GLenum pname, GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXPARAMETERXVOESPROC) (GLenum نشانہ, GLenum pname, GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLIGHTMODELXOESPROC) (GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLIGHTMODELXVOESPROC) (GLenum pname, ثابت GLfixed *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLIGHTXOESPROC) (GLenum light, GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLIGHTXVOESPROC) (GLenum light, GLenum pname, ثابت GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLINEWIDTHXOESPROC) (GLfixed چوڑائی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLOADMATRIXXOESPROC) (ثابت GLfixed *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATERIALXOESPROC) (GLenum face, GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATERIALXVOESPROC) (GLenum face, GLenum pname, ثابت GLfixed *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTMATRIXXOESPROC) (ثابت GLfixed *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTITEXCOORD4XOESPROC) (GLenum texture, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
تعريفنوع فراغ (GL_APIENTRYP PFNGLNORMAL3XOESPROC) (GLfixed nx, GLfixed ny, GLfixed nz);
تعريفنوع فراغ (GL_APIENTRYP PFNGLORTHOXOESPROC) (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOINTPARAMETERXVOESPROC) (GLenum pname, ثابت GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOINTSIZEXOESPROC) (GLfixed ناپ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOLYGONOFFSETXOESPROC) (GLfixed ضارب, GLfixed units);
تعريفنوع فراغ (GL_APIENTRYP PFNGLROTATEXOESPROC) (GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCALEXOESPROC) (GLfixed x, GLfixed y, GLfixed z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXENVXOESPROC) (GLenum نشانہ, GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXENVXVOESPROC) (GLenum نشانہ, GLenum pname, ثابت GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERXOESPROC) (GLenum نشانہ, GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERXVOESPROC) (GLenum نشانہ, GLenum pname, ثابت GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTRANSLATEXOESPROC) (GLfixed x, GLfixed y, GLfixed z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETLIGHTXVOESPROC) (GLenum light, GLenum pname, GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETMATERIALXVOESPROC) (GLenum face, GLenum pname, GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOINTPARAMETERXOESPROC) (GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLECOVERAGEXOESPROC) (GLclampx قدر, GLboolean invert);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXGENXVOESPROC) (GLenum coord, GLenum pname, GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXGENXOESPROC) (GLenum coord, GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXGENXVOESPROC) (GLenum coord, GLenum pname, ثابت GLfixed *params);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glAlphaFuncxOES (GLenum func, GLfixed ref);
GL_API فراغ GL_APIENTRY glClearColorxOES (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GL_API فراغ GL_APIENTRY glClearDepthxOES (GLfixed ڈونگھائی_2);
GL_API فراغ GL_APIENTRY glClipPlanexOES (GLenum plane, ثابت GLfixed *equation);
GL_API فراغ GL_APIENTRY glColor4xOES (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GL_API فراغ GL_APIENTRY gl_ڈونگھائی_Rangex_OES (GLfixed n, GLfixed f);
GL_API فراغ GL_APIENTRY glFogxOES (GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glFogxvOES (GLenum pname, ثابت GLfixed *param);
GL_API فراغ GL_APIENTRY glFrustumxOES (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
GL_API فراغ GL_APIENTRY glGetClipPlanexOES (GLenum plane, GLfixed *equation);
GL_API فراغ GL_APIENTRY glGetFixedvOES (GLenum pname, GLfixed *params);
GL_API فراغ GL_APIENTRY glGetTexEnvxvOES (GLenum نشانہ, GLenum pname, GLfixed *params);
GL_API فراغ GL_APIENTRY glGetTexParameterxvOES (GLenum نشانہ, GLenum pname, GLfixed *params);
GL_API فراغ GL_APIENTRY glLightModelxOES (GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glLightModelxvOES (GLenum pname, ثابت GLfixed *param);
GL_API فراغ GL_APIENTRY glLightxOES (GLenum light, GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glLightxvOES (GLenum light, GLenum pname, ثابت GLfixed *params);
GL_API فراغ GL_APIENTRY gl_سطر_Widthx_OES (GLfixed چوڑائی);
GL_API فراغ GL_APIENTRY gl_لدو_Matrixx_OES (ثابت GLfixed *m);
GL_API فراغ GL_APIENTRY glMaterialxOES (GLenum face, GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glMaterialxvOES (GLenum face, GLenum pname, ثابت GLfixed *param);
GL_API فراغ GL_APIENTRY glMultMatrixxOES (ثابت GLfixed *m);
GL_API فراغ GL_APIENTRY glMultiTexCoord4xOES (GLenum texture, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
GL_API فراغ GL_APIENTRY glNormal3xOES (GLfixed nx, GLfixed ny, GLfixed nz);
GL_API فراغ GL_APIENTRY glOrthoxOES (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
GL_API فراغ GL_APIENTRY gl_نقطہ_Parameterxv_OES (GLenum pname, ثابت GLfixed *params);
GL_API فراغ GL_APIENTRY gl_نقطہ_Sizex_OES (GLfixed ناپ);
GL_API فراغ GL_APIENTRY glPolygonOffsetxOES (GLfixed ضارب, GLfixed units);
GL_API فراغ GL_APIENTRY glRotatexOES (GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
GL_API فراغ GL_APIENTRY glScalexOES (GLfixed x, GLfixed y, GLfixed z);
GL_API فراغ GL_APIENTRY glTexEnvxOES (GLenum نشانہ, GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glTexEnvxvOES (GLenum نشانہ, GLenum pname, ثابت GLfixed *params);
GL_API فراغ GL_APIENTRY glTexParameterxOES (GLenum نشانہ, GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glTexParameterxvOES (GLenum نشانہ, GLenum pname, ثابت GLfixed *params);
GL_API فراغ GL_APIENTRY glTranslatexOES (GLfixed x, GLfixed y, GLfixed z);
GL_API فراغ GL_APIENTRY glGetLightxvOES (GLenum light, GLenum pname, GLfixed *params);
GL_API فراغ GL_APIENTRY glGetMaterialxvOES (GLenum face, GLenum pname, GLfixed *params);
GL_API فراغ GL_APIENTRY gl_نقطہ_Parameterx_OES (GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glSampleCoveragexOES (GLclampx قدر, GLboolean invert);
GL_API فراغ GL_APIENTRY glGetTexGenxvOES (GLenum coord, GLenum pname, GLfixed *params);
GL_API فراغ GL_APIENTRY glTexGenxOES (GLenum coord, GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glTexGenxvOES (GLenum coord, GLenum pname, ثابت GLfixed *params);
#جے_انت
#جے_انت /* GL_OES_fixed_point */

#جے_بنا_تعریف GL_OES_framebuffer_object
#تعریف_کرو GL_OES_framebuffer_object 1
#تعریف_کرو GL_NONE_OES                       0
#تعریف_کرو GL_FRAMEBUFFER_OES                0x8D40
#تعریف_کرو GL_RENDERBUFFER_OES               0x8D41
#تعریف_کرو GL_RGBA4_OES                      0x8056
#تعریف_کرو GL_RGB5_A1_OES                    0x8057
#تعریف_کرو GL_RGB565_OES                     0x8D62
#تعریف_کرو GL_ڈونگھائی_COMPONENT16_OES          0x81A5
#تعریف_کرو GL_RENDERBUFFER_چوڑائی_OES         0x8D42
#تعریف_کرو GL_RENDERBUFFER_اچائی_OES        0x8D43
#تعریف_کرو GL_RENDERBUFFER_اندرونی_FORMAT_OES 0x8D44
#تعریف_کرو GL_RENDERBUFFER_RED_ناپ_OES      0x8D50
#تعریف_کرو GL_RENDERBUFFER_GREEN_ناپ_OES    0x8D51
#تعریف_کرو GL_RENDERBUFFER_BLUE_ناپ_OES     0x8D52
#تعریف_کرو GL_RENDERBUFFER_ALPHA_ناپ_OES    0x8D53
#تعریف_کرو GL_RENDERBUFFER_ڈونگھائی_ناپ_OES    0x8D54
#تعریف_کرو GL_RENDERBUFFER_STENCIL_ناپ_OES  0x8D55
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_OES 0x8CD0
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_OES 0x8CD1
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_OES 0x8CD2
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_OES 0x8CD3
#تعریف_کرو GL_COLOR_ATTACHMENT0_OES          0x8CE0
#تعریف_کرو GL_ڈونگھائی_ATTACHMENT_OES           0x8D00
#تعریف_کرو GL_STENCIL_ATTACHMENT_OES         0x8D20
#تعریف_کرو GL_FRAMEBUFFER_COMPLETE_OES       0x8CD5
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_OES 0x8CD6
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_OES 0x8CD7
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_OES 0x8CD9
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_FORMATS_OES 0x8CDA
#تعریف_کرو GL_FRAMEBUFFER_UNSUPPORTED_OES    0x8CDD
#تعریف_کرو GL_FRAMEBUFFER_BINDING_OES        0x8CA6
#تعریف_کرو GL_RENDERBUFFER_BINDING_OES       0x8CA7
#تعریف_کرو GL_MAX_RENDERBUFFER_ناپ_OES      0x84E8
#تعریف_کرو GL_INVALID_FRAMEBUFFER_OPERATION_OES 0x0506
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISRENDERBUFFEROESPROC) (GLuint renderbuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDRENDERBUFFEROESPROC) (GLenum نشانہ, GLuint renderbuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETERENDERBUFFERSOESPROC) (GLsizei n, ثابت GLuint *renderbuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENRENDERBUFFERSOESPROC) (GLsizei n, GLuint *renderbuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEOESPROC) (GLenum نشانہ, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVOESPROC) (GLenum نشانہ, GLenum pname, GLint *params);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISFRAMEBUFFEROESPROC) (GLuint framebuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDFRAMEBUFFEROESPROC) (GLenum نشانہ, GLuint framebuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEFRAMEBUFFERSOESPROC) (GLsizei n, ثابت GLuint *framebuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENFRAMEBUFFERSOESPROC) (GLsizei n, GLuint *framebuffers);
تعريفنوع GLenum (GL_APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSOESPROC) (GLenum نشانہ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFEROESPROC) (GLenum نشانہ, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DOESPROC) (GLenum نشانہ, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVOESPROC) (GLenum نشانہ, GLenum attachment, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENERATEMIPMAPOESPROC) (GLenum نشانہ);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API GLboolean GL_APIENTRY glIsRenderbufferOES (GLuint renderbuffer);
GL_API فراغ GL_APIENTRY glBindRenderbufferOES (GLenum نشانہ, GLuint renderbuffer);
GL_API فراغ GL_APIENTRY glDeleteRenderbuffersOES (GLsizei n, ثابت GLuint *renderbuffers);
GL_API فراغ GL_APIENTRY glGenRenderbuffersOES (GLsizei n, GLuint *renderbuffers);
GL_API فراغ GL_APIENTRY glRenderbufferStorageOES (GLenum نشانہ, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی);
GL_API فراغ GL_APIENTRY glGetRenderbufferParameterivOES (GLenum نشانہ, GLenum pname, GLint *params);
GL_API GLboolean GL_APIENTRY glIsFramebufferOES (GLuint framebuffer);
GL_API فراغ GL_APIENTRY glBindFramebufferOES (GLenum نشانہ, GLuint framebuffer);
GL_API فراغ GL_APIENTRY glDeleteFramebuffersOES (GLsizei n, ثابت GLuint *framebuffers);
GL_API فراغ GL_APIENTRY glGenFramebuffersOES (GLsizei n, GLuint *framebuffers);
GL_API GLenum GL_APIENTRY gl_Check_Framebuffer_حالت_OES (GLenum نشانہ);
GL_API فراغ GL_APIENTRY glFramebufferRenderbufferOES (GLenum نشانہ, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
GL_API فراغ GL_APIENTRY glFramebufferTexture2DOES (GLenum نشانہ, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GL_API فراغ GL_APIENTRY glGetFramebufferAttachmentParameterivOES (GLenum نشانہ, GLenum attachment, GLenum pname, GLint *params);
GL_API فراغ GL_APIENTRY glGenerateMipmapOES (GLenum نشانہ);
#جے_انت
#جے_انت /* GL_OES_framebuffer_object */

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
GL_API فراغ *GL_APIENTRY gl_Map_بفر_OES (GLenum نشانہ, GLenum access);
GL_API GLboolean GL_APIENTRY gl_Unmap_بفر_OES (GLenum نشانہ);
GL_API فراغ GL_APIENTRY gl_Get_بفر_Pointerv_OES (GLenum نشانہ, GLenum pname, فراغ **params);
#جے_انت
#جے_انت /* GL_OES_mapbuffer */

#جے_بنا_تعریف GL_OES_میٹرکس_get
#تعریف_کرو GL_OES_میٹرکس_get 1
#تعریف_کرو GL_MODELVIEW_میٹرکس_FLOAT_AS_INT_بٹ_OES 0x898D
#تعریف_کرو GL_PROJECTION_میٹرکس_FLOAT_AS_INT_بٹ_OES 0x898E
#تعریف_کرو GL_TEXTURE_میٹرکس_FLOAT_AS_INT_بٹ_OES 0x898F
#جے_انت /* GL_OES_matrix_get */

#جے_بنا_تعریف GL_OES_میٹرکس_palette
#تعریف_کرو GL_OES_میٹرکس_palette 1
#تعریف_کرو GL_MAX_راس_UNITS_OES           0x86A4
#تعریف_کرو GL_MAX_PALETTE_MATRICES_OES       0x8842
#تعریف_کرو GL_میٹرکس_PALETTE_OES             0x8840
#تعریف_کرو GL_میٹرکس_اشاریہ_ARRAY_OES         0x8844
#تعریف_کرو GL_بھار_ARRAY_OES               0x86AD
#تعریف_کرو GL_CURRENT_PALETTE_میٹرکس_OES     0x8843
#تعریف_کرو GL_میٹرکس_اشاریہ_ARRAY_ناپ_OES    0x8846
#تعریف_کرو GL_میٹرکس_اشاریہ_ARRAY_TYPE_OES    0x8847
#تعریف_کرو GL_میٹرکس_اشاریہ_ARRAY_STRIDE_OES  0x8848
#تعریف_کرو GL_میٹرکس_اشاریہ_ARRAY_اشارہ_گر_OES 0x8849
#تعریف_کرو GL_میٹرکس_اشاریہ_ARRAY_بفر_BINDING_OES 0x8B9E
#تعریف_کرو GL_بھار_ARRAY_ناپ_OES          0x86AB
#تعریف_کرو GL_بھار_ARRAY_TYPE_OES          0x86A9
#تعریف_کرو GL_بھار_ARRAY_STRIDE_OES        0x86AA
#تعریف_کرو GL_بھار_ARRAY_اشارہ_گر_OES       0x86AC
#تعریف_کرو GL_بھار_ARRAY_بفر_BINDING_OES 0x889E
تعريفنوع فراغ (GL_APIENTRYP PFNGLCURRENTPALETTEMATRIXOESPROC) (GLuint matrixpaletteindex);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLOADPALETTEFROMMODELVIEWMATRIXOESPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXINDEXPOINTEROESPROC) (GLint ناپ, GLenum type, GLsizei stride, ثابت فراغ *اشارہ_گر_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLWEIGHTPOINTEROESPROC) (GLint ناپ, GLenum type, GLsizei stride, ثابت فراغ *اشارہ_گر_2);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY gl_Current_Palette_میٹرکس_OES (GLuint matrixpaletteindex);
GL_API فراغ GL_APIENTRY gl_لدو_Palette_From_Model_View_میٹرکس_OES (فراغ);
GL_API فراغ GL_APIENTRY gl_میٹرکس_اشاریہ_اشارہ_گر_OES (GLint ناپ, GLenum type, GLsizei stride, ثابت فراغ *اشارہ_گر_2);
GL_API فراغ GL_APIENTRY gl_بھار_اشارہ_گر_OES (GLint ناپ, GLenum type, GLsizei stride, ثابت فراغ *اشارہ_گر_2);
#جے_انت
#جے_انت /* GL_OES_matrix_palette */

#جے_بنا_تعریف GL_OES_packed_ڈونگھائی_stencil
#تعریف_کرو GL_OES_packed_ڈونگھائی_stencil 1
#تعریف_کرو GL_ڈونگھائی_STENCIL_OES              0x84F9
#تعریف_کرو GL_UNSIGNED_INT_24_8_OES          0x84FA
#تعریف_کرو GL_DEPTH24_STENCIL8_OES           0x88F0
#جے_انت /* GL_OES_packed_depth_stencil */

#جے_بنا_تعریف GL_OES_query_میٹرکس
#تعریف_کرو GL_OES_query_میٹرکس 1
تعريفنوع GLbitfield (GL_APIENTRYP PFNGLQUERYMATRIXXOESPROC) (GLfixed *mantissa, GLint *exponent);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API GLbitfield GL_APIENTRY glQueryMatrixxOES (GLfixed *mantissa, GLint *exponent);
#جے_انت
#جے_انت /* GL_OES_query_matrix */

#جے_بنا_تعریف GL_OES_required_internalformat
#تعریف_کرو GL_OES_required_internalformat 1
#تعریف_کرو GL_ALPHA8_OES                     0x803C
#تعریف_کرو GL_LUMINANCE4_ALPHA4_OES          0x8043
#تعریف_کرو GL_LUMINANCE8_ALPHA8_OES          0x8045
#تعریف_کرو GL_LUMINANCE8_OES                 0x8040
#تعریف_کرو GL_RGB8_OES                       0x8051
#تعریف_کرو GL_RGBA8_OES                      0x8058
#تعریف_کرو GL_RGB10_EXT                      0x8052
#تعریف_کرو GL_RGB10_A2_EXT                   0x8059
#جے_انت /* GL_OES_required_internalformat */

#جے_بنا_تعریف GL_OES_rgb8_rgba8
#تعریف_کرو GL_OES_rgb8_rgba8 1
#جے_انت /* GL_OES_rgb8_rgba8 */

#جے_بنا_تعریف GL_OES_single_precision
#تعریف_کرو GL_OES_single_precision 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARDEPTHFOESPROC) (GLclampf ڈونگھائی_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLIPPLANEFOESPROC) (GLenum plane, ثابت GLfloat *equation);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHRANGEFOESPROC) (GLclampf n, GLclampf f);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRUSTUMFOESPROC) (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETCLIPPLANEFOESPROC) (GLenum plane, GLfloat *equation);
تعريفنوع فراغ (GL_APIENTRYP PFNGLORTHOFOESPROC) (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glClearDepthfOES (GLclampf ڈونگھائی_2);
GL_API فراغ GL_APIENTRY glClipPlanefOES (GLenum plane, ثابت GLfloat *equation);
GL_API فراغ GL_APIENTRY gl_ڈونگھائی_Rangef_OES (GLclampf n, GLclampf f);
GL_API فراغ GL_APIENTRY glFrustumfOES (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
GL_API فراغ GL_APIENTRY glGetClipPlanefOES (GLenum plane, GLfloat *equation);
GL_API فراغ GL_APIENTRY glOrthofOES (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
#جے_انت
#جے_انت /* GL_OES_single_precision */

#جے_بنا_تعریف GL_OES_stencil1
#تعریف_کرو GL_OES_stencil1 1
#تعریف_کرو GL_STENCIL_INDEX1_OES             0x8D46
#جے_انت /* GL_OES_stencil1 */

#جے_بنا_تعریف GL_OES_stencil4
#تعریف_کرو GL_OES_stencil4 1
#تعریف_کرو GL_STENCIL_INDEX4_OES             0x8D47
#جے_انت /* GL_OES_stencil4 */

#جے_بنا_تعریف GL_OES_stencil8
#تعریف_کرو GL_OES_stencil8 1
#تعریف_کرو GL_STENCIL_INDEX8_OES             0x8D48
#جے_انت /* GL_OES_stencil8 */

#جے_بنا_تعریف GL_OES_stencil_wrap
#تعریف_کرو GL_OES_stencil_wrap 1
#تعریف_کرو GL_INCR_WRAP_OES                  0x8507
#تعریف_کرو GL_DECR_WRAP_OES                  0x8508
#جے_انت /* GL_OES_stencil_wrap */

#جے_بنا_تعریف GL_OES_surfaceless_context
#تعریف_کرو GL_OES_surfaceless_context 1
#تعریف_کرو GL_FRAMEBUFFER_UNDEFINED_OES      0x8219
#جے_انت /* GL_OES_surfaceless_context */

#جے_بنا_تعریف GL_OES_texture_cube_map
#تعریف_کرو GL_OES_texture_cube_map 1
#تعریف_کرو GL_عام_MAP_OES                 0x8511
#تعریف_کرو GL_REFLECTION_MAP_OES             0x8512
#تعریف_کرو GL_TEXTURE_CUBE_MAP_OES           0x8513
#تعریف_کرو GL_TEXTURE_BINDING_CUBE_MAP_OES   0x8514
#تعریف_کرو GL_TEXTURE_CUBE_MAP_مثبت_X_OES 0x8515
#تعریف_کرو GL_TEXTURE_CUBE_MAP_NEGATIVE_X_OES 0x8516
#تعریف_کرو GL_TEXTURE_CUBE_MAP_مثبت_Y_OES 0x8517
#تعریف_کرو GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_OES 0x8518
#تعریف_کرو GL_TEXTURE_CUBE_MAP_مثبت_Z_OES 0x8519
#تعریف_کرو GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_OES 0x851A
#تعریف_کرو GL_MAX_CUBE_MAP_TEXTURE_ناپ_OES  0x851C
#تعریف_کرو GL_TEXTURE_GEN_منوال_OES           0x2500
#تعریف_کرو GL_TEXTURE_GEN_STR_OES            0x8D60
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXGENFOESPROC) (GLenum coord, GLenum pname, GLfloat param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXGENFVOESPROC) (GLenum coord, GLenum pname, ثابت GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXGENIOESPROC) (GLenum coord, GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXGENIVOESPROC) (GLenum coord, GLenum pname, ثابت GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXGENFVOESPROC) (GLenum coord, GLenum pname, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXGENIVOESPROC) (GLenum coord, GLenum pname, GLint *params);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glTexGenfOES (GLenum coord, GLenum pname, GLfloat param);
GL_API فراغ GL_APIENTRY glTexGenfvOES (GLenum coord, GLenum pname, ثابت GLfloat *params);
GL_API فراغ GL_APIENTRY glTexGeniOES (GLenum coord, GLenum pname, GLint param);
GL_API فراغ GL_APIENTRY glTexGenivOES (GLenum coord, GLenum pname, ثابت GLint *params);
GL_API فراغ GL_APIENTRY glGetTexGenfvOES (GLenum coord, GLenum pname, GLfloat *params);
GL_API فراغ GL_APIENTRY glGetTexGenivOES (GLenum coord, GLenum pname, GLint *params);
#جے_انت
#جے_انت /* GL_OES_texture_cube_map */

#جے_بنا_تعریف GL_OES_texture_env_crossbar
#تعریف_کرو GL_OES_texture_env_crossbar 1
#جے_انت /* GL_OES_texture_env_crossbar */

#جے_بنا_تعریف GL_OES_texture_mirrored_repeat
#تعریف_کرو GL_OES_texture_mirrored_repeat 1
#تعریف_کرو GL_MIRRORED_REPEAT_OES            0x8370
#جے_انت /* GL_OES_texture_mirrored_repeat */

#جے_بنا_تعریف GL_OES_texture_npot
#تعریف_کرو GL_OES_texture_npot 1
#جے_انت /* GL_OES_texture_npot */

#جے_بنا_تعریف GL_OES_راس_array_object
#تعریف_کرو GL_OES_راس_array_object 1
#تعریف_کرو GL_راس_ARRAY_BINDING_OES       0x85B5
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDVERTEXARRAYOESPROC) (GLuint array);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEVERTEXARRAYSOESPROC) (GLsizei n, ثابت GLuint *arrays);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENVERTEXARRAYSOESPROC) (GLsizei n, GLuint *arrays);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISVERTEXARRAYOESPROC) (GLuint array);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY gl_Bind_راس_Array_OES (GLuint array);
GL_API فراغ GL_APIENTRY gl_Delete_راس_Arrays_OES (GLsizei n, ثابت GLuint *arrays);
GL_API فراغ GL_APIENTRY gl_Gen_راس_Arrays_OES (GLsizei n, GLuint *arrays);
GL_API GLboolean GL_APIENTRY gl_Is_راس_Array_OES (GLuint array);
#جے_انت
#جے_انت /* GL_OES_vertex_array_object */

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

#جے_بنا_تعریف GL_APPLE_copy_texture_پدھراں
#تعریف_کرو GL_APPLE_copy_texture_پدھراں 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYTEXTURELEVELSAPPLEPROC) (GLuint destinationTexture, GLuint سروت_Texture, GLint سروت_ادھار_Level, GLsizei سروت_Level_گنتی);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY gl_Copy_Texture_پدھراں_APPLE (GLuint destinationTexture, GLuint سروت_Texture, GLint سروت_ادھار_Level, GLsizei سروت_Level_گنتی);
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
GL_API فراغ GL_APIENTRY glRenderbufferStorageMultisampleAPPLE (GLenum نشانہ, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی);
GL_API فراغ GL_APIENTRY glResolveMultisampleFramebufferAPPLE (فراغ);
#جے_انت
#جے_انت /* GL_APPLE_framebuffer_multisample */

#جے_بنا_تعریف GL_APPLE_sync
#تعریف_کرو GL_APPLE_sync 1
تعريفنوع بنية __GLsync *GLsync;
تعريفنوع khronos_uint64_t GLuint64;
تعريفنوع khronos_int64_t GLint64;
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
GL_API GLsync GL_APIENTRY glFenceSyncAPPLE (GLenum condition, GLbitfield flags);
GL_API GLboolean GL_APIENTRY glIsSyncAPPLE (GLsync sync);
GL_API فراغ GL_APIENTRY glDeleteSyncAPPLE (GLsync sync);
GL_API GLenum GL_APIENTRY glClientWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_API فراغ GL_APIENTRY glWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_API فراغ GL_APIENTRY glGetInteger64vAPPLE (GLenum pname, GLint64 *params);
GL_API فراغ GL_APIENTRY glGetSyncivAPPLE (GLsync sync, GLenum pname, GLsizei گنتی, GLsizei *لمائی, GLint *اقدار);
#جے_انت
#جے_انت /* GL_APPLE_sync */

#جے_بنا_تعریف GL_APPLE_texture_2D_limited_npot
#تعریف_کرو GL_APPLE_texture_2D_limited_npot 1
#جے_انت /* GL_APPLE_texture_2D_limited_npot */

#جے_بنا_تعریف GL_APPLE_texture_format_BGRA8888
#تعریف_کرو GL_APPLE_texture_format_BGRA8888 1
#تعریف_کرو GL_BGRA_EXT                       0x80E1
#تعریف_کرو GL_BGRA8_EXT                      0x93A1
#جے_انت /* GL_APPLE_texture_format_BGRA8888 */

#جے_بنا_تعریف GL_APPLE_texture_max_level
#تعریف_کرو GL_APPLE_texture_max_level 1
#تعریف_کرو GL_TEXTURE_MAX_LEVEL_APPLE        0x813D
#جے_انت /* GL_APPLE_texture_max_level */

#جے_بنا_تعریف GL_ARM_rgba8
#تعریف_کرو GL_ARM_rgba8 1
#جے_انت /* GL_ARM_rgba8 */

#جے_بنا_تعریف GL_EXT_blend_minmax
#تعریف_کرو GL_EXT_blend_minmax 1
#تعریف_کرو GL_MIN_EXT                        0x8007
#تعریف_کرو GL_MAX_EXT                        0x8008
#جے_انت /* GL_EXT_blend_minmax */

#جے_بنا_تعریف GL_EXT_debug_marker
#تعریف_کرو GL_EXT_debug_marker 1
تعريفنوع حرف GLchar;
تعريفنوع فراغ (GL_APIENTRYP PFNGLINSERTEVENTMARKEREXTPROC) (GLsizei لمائی, ثابت GLchar *marker);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPUSHGROUPMARKEREXTPROC) (GLsizei لمائی, ثابت GLchar *marker);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOPGROUPMARKEREXTPROC) (فراغ);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY gl_داخل_کرو_Event_Marker_EXT (GLsizei لمائی, ثابت GLchar *marker);
GL_API فراغ GL_APIENTRY gl_ڈالو_گروہ_Marker_EXT (GLsizei لمائی, ثابت GLchar *marker);
GL_API فراغ GL_APIENTRY gl_نکالو_گروہ_Marker_EXT (فراغ);
#جے_انت
#جے_انت /* GL_EXT_debug_marker */

#جے_بنا_تعریف GL_EXT_discard_framebuffer
#تعریف_کرو GL_EXT_discard_framebuffer 1
#تعریف_کرو GL_COLOR_EXT                      0x1800
#تعریف_کرو GL_ڈونگھائی_EXT                      0x1801
#تعریف_کرو GL_STENCIL_EXT                    0x1802
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISCARDFRAMEBUFFEREXTPROC) (GLenum نشانہ, GLsizei عدد_Attachments, ثابت GLenum *attachments);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glDiscardFramebufferEXT (GLenum نشانہ, GLsizei عدد_Attachments, ثابت GLenum *attachments);
#جے_انت
#جے_انت /* GL_EXT_discard_framebuffer */

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
GL_API فراغ *GL_APIENTRY gl_Map_بفر_Range_EXT (GLenum نشانہ, GLintptr وتھ_2, GLsizeiptr لمائی, GLbitfield access);
GL_API فراغ GL_APIENTRY gl_Flush_Mapped_بفر_Range_EXT (GLenum نشانہ, GLintptr وتھ_2, GLsizeiptr لمائی);
#جے_انت
#جے_انت /* GL_EXT_map_buffer_range */

#جے_بنا_تعریف GL_EXT_multi_draw_arrays
#تعریف_کرو GL_EXT_multi_draw_arrays 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWARRAYSEXTPROC) (GLenum منوال, ثابت GLint *پہلا, ثابت GLsizei *گنتی, GLsizei primcount);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSEXTPROC) (GLenum منوال, ثابت GLsizei *گنتی, GLenum type, ثابت فراغ *ثابت*indices, GLsizei primcount);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glMultiDrawArraysEXT (GLenum منوال, ثابت GLint *پہلا, ثابت GLsizei *گنتی, GLsizei primcount);
GL_API فراغ GL_APIENTRY glMultiDrawElementsEXT (GLenum منوال, ثابت GLsizei *گنتی, GLenum type, ثابت فراغ *ثابت*indices, GLsizei primcount);
#جے_انت
#جے_انت /* GL_EXT_multi_draw_arrays */

#جے_بنا_تعریف GL_EXT_multisampled_render_منزل_texture
#تعریف_کرو GL_EXT_multisampled_render_منزل_texture 1
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SAMPLES_EXT 0x8D6C
#تعریف_کرو GL_RENDERBUFFER_SAMPLES_EXT       0x8CAB
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT 0x8D56
#تعریف_کرو GL_MAX_SAMPLES_EXT                0x8D57
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) (GLenum نشانہ, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEEXTPROC) (GLenum نشانہ, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glRenderbufferStorageMultisampleEXT (GLenum نشانہ, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی);
GL_API فراغ GL_APIENTRY glFramebufferTexture2DMultisampleEXT (GLenum نشانہ, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#جے_انت
#جے_انت /* GL_EXT_multisampled_render_to_texture */

#جے_بنا_تعریف GL_EXT_read_format_bgra
#تعریف_کرو GL_EXT_read_format_bgra 1
#تعریف_کرو GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT 0x8365
#تعریف_کرو GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT 0x8366
#جے_انت /* GL_EXT_read_format_bgra */

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
GL_API GLenum GL_APIENTRY gl_Get_Graphics_Reset_حالت_EXT (فراغ);
GL_API فراغ GL_APIENTRY glReadnPixelsEXT (GLint x, GLint y, GLsizei چوڑائی, GLsizei اچائی, GLenum format, GLenum type, GLsizei buf_ناپ, فراغ *انکڑے);
GL_API فراغ GL_APIENTRY glGetnUniformfvEXT (GLuint پروگرام, GLint location, GLsizei buf_ناپ, GLfloat *params);
GL_API فراغ GL_APIENTRY glGetnUniformivEXT (GLuint پروگرام, GLint location, GLsizei buf_ناپ, GLint *params);
#جے_انت
#جے_انت /* GL_EXT_robustness */

#جے_بنا_تعریف GL_EXT_sRGB
#تعریف_کرو GL_EXT_sRGB 1
#تعریف_کرو GL_SRGB_EXT                       0x8C40
#تعریف_کرو GL_SRGB_ALPHA_EXT                 0x8C42
#تعریف_کرو GL_SRGB8_ALPHA8_EXT               0x8C43
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING_EXT 0x8210
#جے_انت /* GL_EXT_sRGB */

#جے_بنا_تعریف GL_EXT_texture_compression_dxt1
#تعریف_کرو GL_EXT_texture_compression_dxt1 1
#تعریف_کرو GL_COMPRESSED_RGB_S3TC_DXT1_EXT   0x83F0
#تعریف_کرو GL_COMPRESSED_RGBA_S3TC_DXT1_EXT  0x83F1
#جے_انت /* GL_EXT_texture_compression_dxt1 */

#جے_بنا_تعریف GL_EXT_texture_filter_anisotropic
#تعریف_کرو GL_EXT_texture_filter_anisotropic 1
#تعریف_کرو GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#تعریف_کرو GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#جے_انت /* GL_EXT_texture_filter_anisotropic */

#جے_بنا_تعریف GL_EXT_texture_format_BGRA8888
#تعریف_کرو GL_EXT_texture_format_BGRA8888 1
#جے_انت /* GL_EXT_texture_format_BGRA8888 */

#جے_بنا_تعریف GL_EXT_texture_lod_bias
#تعریف_کرو GL_EXT_texture_lod_bias 1
#تعریف_کرو GL_MAX_TEXTURE_LOD_BIAS_EXT       0x84FD
#تعریف_کرو GL_TEXTURE_FILTER_CONTROL_EXT     0x8500
#تعریف_کرو GL_TEXTURE_LOD_BIAS_EXT           0x8501
#جے_انت /* GL_EXT_texture_lod_bias */

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
#تعریف_کرو GL_RGBA16F_EXT                    0x881A
#تعریف_کرو GL_RGB16F_EXT                     0x881B
#تعریف_کرو GL_ALPHA16F_EXT                   0x881C
#تعریف_کرو GL_LUMINANCE16F_EXT               0x881E
#تعریف_کرو GL_LUMINANCE_ALPHA16F_EXT         0x881F
#تعریف_کرو GL_R8_EXT                         0x8229
#تعریف_کرو GL_RG8_EXT                        0x822B
#تعریف_کرو GL_R32F_EXT                       0x822E
#تعریف_کرو GL_RG32F_EXT                      0x8230
#تعریف_کرو GL_R16F_EXT                       0x822D
#تعریف_کرو GL_RG16F_EXT                      0x822F
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE1DEXTPROC) (GLenum نشانہ, GLsizei پدھراں, GLenum internalformat, GLsizei چوڑائی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE2DEXTPROC) (GLenum نشانہ, GLsizei پدھراں, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE3DEXTPROC) (GLenum نشانہ, GLsizei پدھراں, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGE1DEXTPROC) (GLuint texture, GLenum نشانہ, GLsizei پدھراں, GLenum internalformat, GLsizei چوڑائی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGE2DEXTPROC) (GLuint texture, GLenum نشانہ, GLsizei پدھراں, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGE3DEXTPROC) (GLuint texture, GLenum نشانہ, GLsizei پدھراں, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glTexStorage1DEXT (GLenum نشانہ, GLsizei پدھراں, GLenum internalformat, GLsizei چوڑائی);
GL_API فراغ GL_APIENTRY glTexStorage2DEXT (GLenum نشانہ, GLsizei پدھراں, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی);
GL_API فراغ GL_APIENTRY glTexStorage3DEXT (GLenum نشانہ, GLsizei پدھراں, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2);
GL_API فراغ GL_APIENTRY glTextureStorage1DEXT (GLuint texture, GLenum نشانہ, GLsizei پدھراں, GLenum internalformat, GLsizei چوڑائی);
GL_API فراغ GL_APIENTRY glTextureStorage2DEXT (GLuint texture, GLenum نشانہ, GLsizei پدھراں, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی);
GL_API فراغ GL_APIENTRY glTextureStorage3DEXT (GLuint texture, GLenum نشانہ, GLsizei پدھراں, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2);
#جے_انت
#جے_انت /* GL_EXT_texture_storage */

#جے_بنا_تعریف GL_IMG_multisampled_render_منزل_texture
#تعریف_کرو GL_IMG_multisampled_render_منزل_texture 1
#تعریف_کرو GL_RENDERBUFFER_SAMPLES_IMG       0x9133
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_IMG 0x9134
#تعریف_کرو GL_MAX_SAMPLES_IMG                0x9135
#تعریف_کرو GL_TEXTURE_SAMPLES_IMG            0x9136
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEIMGPROC) (GLenum نشانہ, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEIMGPROC) (GLenum نشانہ, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glRenderbufferStorageMultisampleIMG (GLenum نشانہ, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی);
GL_API فراغ GL_APIENTRY glFramebufferTexture2DMultisampleIMG (GLenum نشانہ, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#جے_انت
#جے_انت /* GL_IMG_multisampled_render_to_texture */

#جے_بنا_تعریف GL_IMG_read_format
#تعریف_کرو GL_IMG_read_format 1
#تعریف_کرو GL_BGRA_IMG                       0x80E1
#تعریف_کرو GL_UNSIGNED_SHORT_4_4_4_4_REV_IMG 0x8365
#جے_انت /* GL_IMG_read_format */

#جے_بنا_تعریف GL_IMG_texture_compression_pvrtc
#تعریف_کرو GL_IMG_texture_compression_pvrtc 1
#تعریف_کرو GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG 0x8C00
#تعریف_کرو GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG 0x8C01
#تعریف_کرو GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG 0x8C02
#تعریف_کرو GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG 0x8C03
#جے_انت /* GL_IMG_texture_compression_pvrtc */

#جے_بنا_تعریف GL_IMG_texture_env_enhanced_fixed_function
#تعریف_کرو GL_IMG_texture_env_enhanced_fixed_function 1
#تعریف_کرو GL_MODULATE_COLOR_IMG             0x8C04
#تعریف_کرو GL_RECIP_جوڑو_SIGNED_ALPHA_IMG     0x8C05
#تعریف_کرو GL_TEXTURE_ALPHA_MODULATE_IMG     0x8C06
#تعریف_کرو GL_ضارب_ALPHA_MODULATE_IMG      0x8C07
#تعریف_کرو GL_FRAGMENT_ALPHA_MODULATE_IMG    0x8C08
#تعریف_کرو GL_جوڑو_BLEND_IMG                  0x8C09
#تعریف_کرو GL_DOT3_RGBA_IMG                  0x86AF
#جے_انت /* GL_IMG_texture_env_enhanced_fixed_function */

#جے_بنا_تعریف GL_IMG_user_clip_plane
#تعریف_کرو GL_IMG_user_clip_plane 1
#تعریف_کرو GL_CLIP_PLANE0_IMG                0x3000
#تعریف_کرو GL_CLIP_PLANE1_IMG                0x3001
#تعریف_کرو GL_CLIP_PLANE2_IMG                0x3002
#تعریف_کرو GL_CLIP_PLANE3_IMG                0x3003
#تعریف_کرو GL_CLIP_PLANE4_IMG                0x3004
#تعریف_کرو GL_CLIP_PLANE5_IMG                0x3005
#تعریف_کرو GL_MAX_CLIP_PLANES_IMG            0x0D32
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLIPPLANEFIMGPROC) (GLenum p, ثابت GLfloat *eqn);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLIPPLANEXIMGPROC) (GLenum p, ثابت GLfixed *eqn);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glClipPlanefIMG (GLenum p, ثابت GLfloat *eqn);
GL_API فراغ GL_APIENTRY glClipPlanexIMG (GLenum p, ثابت GLfixed *eqn);
#جے_انت
#جے_انت /* GL_IMG_user_clip_plane */

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
GL_API فراغ GL_APIENTRY glDeleteFencesNV (GLsizei n, ثابت GLuint *fences);
GL_API فراغ GL_APIENTRY glGenFencesNV (GLsizei n, GLuint *fences);
GL_API GLboolean GL_APIENTRY glIsFenceNV (GLuint fence);
GL_API GLboolean GL_APIENTRY glTestFenceNV (GLuint fence);
GL_API فراغ GL_APIENTRY glGetFenceivNV (GLuint fence, GLenum pname, GLint *params);
GL_API فراغ GL_APIENTRY gl_انت_Fence_NV (GLuint fence);
GL_API فراغ GL_APIENTRY gl_سیٹ_Fence_NV (GLuint fence, GLenum condition);
#جے_انت
#جے_انت /* GL_NV_fence */

#جے_بنا_تعریف GL_QCOM_driver_control
#تعریف_کرو GL_QCOM_driver_control 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETDRIVERCONTROLSQCOMPROC) (GLint *عدد, GLsizei ناپ, GLuint *driverControls);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETDRIVERCONTROLSTRINGQCOMPROC) (GLuint driverControl, GLsizei buf_ناپ, GLsizei *لمائی, GLchar *driverControlString);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glGetDriverControlsQCOM (GLint *عدد, GLsizei ناپ, GLuint *driverControls);
GL_API فراغ GL_APIENTRY glGetDriverControlStringQCOM (GLuint driverControl, GLsizei buf_ناپ, GLsizei *لمائی, GLchar *driverControlString);
GL_API فراغ GL_APIENTRY glEnableDriverControlQCOM (GLuint driverControl);
GL_API فراغ GL_APIENTRY glDisableDriverControlQCOM (GLuint driverControl);
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
GL_API فراغ GL_APIENTRY glExtGetTexturesQCOM (GLuint *textures, GLint maxTextures, GLint *عدد_Textures);
GL_API فراغ GL_APIENTRY glExtGetBuffersQCOM (GLuint *buffers, GLint maxBuffers, GLint *عدد_Buffers);
GL_API فراغ GL_APIENTRY glExtGetRenderbuffersQCOM (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *عدد_Renderbuffers);
GL_API فراغ GL_APIENTRY glExtGetFramebuffersQCOM (GLuint *framebuffers, GLint maxFramebuffers, GLint *عدد_Framebuffers);
GL_API فراغ GL_APIENTRY glExtGetTexLevelParameterivQCOM (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
GL_API فراغ GL_APIENTRY glExtTexObjectStateOverrideiQCOM (GLenum نشانہ, GLenum pname, GLint param);
GL_API فراغ GL_APIENTRY glExtGetTexSubImageQCOM (GLenum نشانہ, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei چوڑائی, GLsizei اچائی, GLsizei ڈونگھائی_2, GLenum format, GLenum type, فراغ *texels);
GL_API فراغ GL_APIENTRY gl_Ext_Get_بفر_Pointerv_QCOM (GLenum نشانہ, فراغ **params);
#جے_انت
#جے_انت /* GL_QCOM_extended_get */

#جے_بنا_تعریف GL_QCOM_extended_get2
#تعریف_کرو GL_QCOM_extended_get2 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETSHADERSQCOMPROC) (GLuint *shaders, GLint maxShaders, GLint *عدد_Shaders);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETPROGRAMSQCOMPROC) (GLuint *programs, GLint maxPrograms, GLint *عدد_Programs);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLEXTISPROGRAMBINARYQCOMPROC) (GLuint پروگرام);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETPROGRAMBINARYSOURCEQCOMPROC) (GLuint پروگرام, GLenum shadertype, GLchar *سروت, GLint *لمائی);
#جے_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glExtGetShadersQCOM (GLuint *shaders, GLint maxShaders, GLint *عدد_Shaders);
GL_API فراغ GL_APIENTRY glExtGetProgramsQCOM (GLuint *programs, GLint maxPrograms, GLint *عدد_Programs);
GL_API GLboolean GL_APIENTRY gl_Ext_Is_پروگرام_ثنائی_QCOM (GLuint پروگرام);
GL_API فراغ GL_APIENTRY gl_Ext_Get_پروگرام_ثنائی_سروت_QCOM (GLuint پروگرام, GLenum shadertype, GLchar *سروت, GLint *لمائی);
#جے_انت
#جے_انت /* GL_QCOM_extended_get2 */

#جے_بنا_تعریف GL_QCOM_perfmon_global_منوال
#تعریف_کرو GL_QCOM_perfmon_global_منوال 1
#تعریف_کرو GL_PERFMON_GLOBAL_منوال_QCOM       0x8FA0
#جے_انت /* GL_QCOM_perfmon_global_mode */

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
GL_API فراغ GL_APIENTRY gl_شروع_Tiling_QCOM (GLuint x, GLuint y, GLuint چوڑائی, GLuint اچائی, GLbitfield preserve_نقاب);
GL_API فراغ GL_APIENTRY gl_سرا_Tiling_QCOM (GLbitfield preserve_نقاب);
#جے_انت
#جے_انت /* GL_QCOM_tiled_rendering */

#جے_بنا_تعریف GL_QCOM_writeonly_rendering
#تعریف_کرو GL_QCOM_writeonly_rendering 1
#تعریف_کرو GL_WRITEONLY_RENDERING_QCOM       0x8823
#جے_انت /* GL_QCOM_writeonly_rendering */

#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت
