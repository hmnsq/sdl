#که_نه_تعریف_شوی __gles1_glext_h_
#تعریف_کړه __gles1_glext_h_ 1

#که_تعریف_شوی __cplusplus
خارجي "C" {
#د_که_پای

/*
** Copyright 2013-2026 The Khronos Group Inc.
** SPDX-License-Identifier: MIT
**
** This header is generated from the Khronos OpenGL / OpenGL ES XML
** API Registry. The current version of the Registry, generator scripts
** used to make the header, and the header can be found at
**   https://github.com/KhronosGroup/OpenGL-Registry
*/

#که_نه_تعریف_شوی GL_APIENTRYP
#تعریف_کړه GL_APIENTRYP GL_APIENTRY*
#د_که_پای

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

#که_نه_تعریف_شوی GL_KHR_debug
#تعریف_کړه GL_KHR_debug 1
#د_که_پای /* GL_KHR_debug */

#که_نه_تعریف_شوی GL_OES_EGL_image
#تعریف_کړه GL_OES_EGL_image 1
تعريفنوع فراغ *GLeglImageOES;
تعريفنوع فراغ (GL_APIENTRYP PFNGLEGLIMAGETARGETTEXTURE2DOESPROC) (GLenum موخه, GLeglImageOES image);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEGLIMAGETARGETRENDERBUFFERSTORAGEOESPROC) (GLenum موخه, GLeglImageOES image);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY gl_EGLImage_موخه_Texture2_DOES (GLenum موخه, GLeglImageOES image);
GL_API فراغ GL_APIENTRY gl_EGLImage_موخه_Renderbuffer_Storage_OES (GLenum موخه, GLeglImageOES image);
#د_که_پای
#د_که_پای /* GL_OES_EGL_image */

#که_نه_تعریف_شوی GL_OES_EGL_image_external
#تعریف_کړه GL_OES_EGL_image_external 1
#تعریف_کړه GL_TEXTURE_EXTERNAL_OES           0x8D65
#تعریف_کړه GL_TEXTURE_BINDING_EXTERNAL_OES   0x8D67
#تعریف_کړه GL_REQUIRED_TEXTURE_IMAGE_UNITS_OES 0x8D68
#د_که_پای /* GL_OES_EGL_image_external */

#که_نه_تعریف_شوی GL_OES_blend_equation_separate
#تعریف_کړه GL_OES_blend_equation_separate 1
#تعریف_کړه GL_BLEND_EQUATION_RGB_OES         0x8009
#تعریف_کړه GL_BLEND_EQUATION_ALPHA_OES       0x883D
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEOESPROC) (GLenum ډېرپېښ_RGB, GLenum ډېرپېښ_Alpha);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glBlendEquationSeparateOES (GLenum ډېرپېښ_RGB, GLenum ډېرپېښ_Alpha);
#د_که_پای
#د_که_پای /* GL_OES_blend_equation_separate */

#که_نه_تعریف_شوی GL_OES_blend_func_separate
#تعریف_کړه GL_OES_blend_func_separate 1
#تعریف_کړه GL_BLEND_DST_RGB_OES              0x80C8
#تعریف_کړه GL_BLEND_SRC_RGB_OES              0x80C9
#تعریف_کړه GL_BLEND_DST_ALPHA_OES            0x80CA
#تعریف_کړه GL_BLEND_SRC_ALPHA_OES            0x80CB
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEOESPROC) (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glBlendFuncSeparateOES (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
#د_که_پای
#د_که_پای /* GL_OES_blend_func_separate */

#که_نه_تعریف_شوی GL_OES_blend_کمول
#تعریف_کړه GL_OES_blend_کمول 1
#تعریف_کړه GL_BLEND_EQUATION_OES             0x8009
#تعریف_کړه GL_FUNC_جمع_کړه_OES                   0x8006
#تعریف_کړه GL_FUNC_کمول_OES              0x800A
#تعریف_کړه GL_FUNC_سرچپه_کمول_OES      0x800B
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONOESPROC) (GLenum ډېرپېښ);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glBlendEquationOES (GLenum ډېرپېښ);
#د_که_پای
#د_که_پای /* GL_OES_blend_subtract */

#که_نه_تعریف_شوی GL_OES_byte_coordinates
#تعریف_کړه GL_OES_byte_coordinates 1
#د_که_پای /* GL_OES_byte_coordinates */

#که_نه_تعریف_شوی GL_OES_compressed_ETC1_RGB8_sub_texture
#تعریف_کړه GL_OES_compressed_ETC1_RGB8_sub_texture 1
#د_که_پای /* GL_OES_compressed_ETC1_RGB8_sub_texture */

#که_نه_تعریف_شوی GL_OES_compressed_ETC1_RGB8_texture
#تعریف_کړه GL_OES_compressed_ETC1_RGB8_texture 1
#تعریف_کړه GL_ETC1_RGB8_OES                  0x8D64
#د_که_پای /* GL_OES_compressed_ETC1_RGB8_texture */

#که_نه_تعریف_شوی GL_OES_depth24
#تعریف_کړه GL_OES_depth24 1
#تعریف_کړه GL_ژوروالی_COMPONENT24_OES          0x81A6
#د_که_پای /* GL_OES_depth24 */

#که_نه_تعریف_شوی GL_OES_depth32
#تعریف_کړه GL_OES_depth32 1
#تعریف_کړه GL_ژوروالی_COMPONENT32_OES          0x81A7
#د_که_پای /* GL_OES_depth32 */

#که_نه_تعریف_شوی GL_OES_draw_texture
#تعریف_کړه GL_OES_draw_texture 1
#تعریف_کړه GL_TEXTURE_CROP_RECT_OES          0x8B9D
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXSOESPROC) (GLshort x, GLshort y, GLshort z, GLshort پلنوالی, GLshort لوړوالی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXIOESPROC) (GLint x, GLint y, GLint z, GLint پلنوالی, GLint لوړوالی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXXOESPROC) (GLfixed x, GLfixed y, GLfixed z, GLfixed پلنوالی, GLfixed لوړوالی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXSVOESPROC) (ثابت GLshort *coords);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXIVOESPROC) (ثابت GLint *coords);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXXVOESPROC) (ثابت GLfixed *coords);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXFOESPROC) (GLfloat x, GLfloat y, GLfloat z, GLfloat پلنوالی, GLfloat لوړوالی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXFVOESPROC) (ثابت GLfloat *coords);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glDrawTexsOES (GLshort x, GLshort y, GLshort z, GLshort پلنوالی, GLshort لوړوالی);
GL_API فراغ GL_APIENTRY glDrawTexiOES (GLint x, GLint y, GLint z, GLint پلنوالی, GLint لوړوالی);
GL_API فراغ GL_APIENTRY glDrawTexxOES (GLfixed x, GLfixed y, GLfixed z, GLfixed پلنوالی, GLfixed لوړوالی);
GL_API فراغ GL_APIENTRY glDrawTexsvOES (ثابت GLshort *coords);
GL_API فراغ GL_APIENTRY glDrawTexivOES (ثابت GLint *coords);
GL_API فراغ GL_APIENTRY glDrawTexxvOES (ثابت GLfixed *coords);
GL_API فراغ GL_APIENTRY glDrawTexfOES (GLfloat x, GLfloat y, GLfloat z, GLfloat پلنوالی, GLfloat لوړوالی);
GL_API فراغ GL_APIENTRY glDrawTexfvOES (ثابت GLfloat *coords);
#د_که_پای
#د_که_پای /* GL_OES_draw_texture */

#که_نه_تعریف_شوی GL_OES_element_شاخص_uint
#تعریف_کړه GL_OES_element_شاخص_uint 1
#تعریف_کړه GL_UNSIGNED_INT                   0x1405
#د_که_پای /* GL_OES_element_index_uint */

#که_نه_تعریف_شوی GL_OES_extended_ماتریکس_palette
#تعریف_کړه GL_OES_extended_ماتریکس_palette 1
#د_که_پای /* GL_OES_extended_matrix_palette */

#که_نه_تعریف_شوی GL_OES_fbo_render_mipmap
#تعریف_کړه GL_OES_fbo_render_mipmap 1
#د_که_پای /* GL_OES_fbo_render_mipmap */

#که_نه_تعریف_شوی GL_OES_fixed_ټکی
#تعریف_کړه GL_OES_fixed_ټکی 1
#تعریف_کړه GL_FIXED_OES                      0x140C
تعريفنوع فراغ (GL_APIENTRYP PFNGLALPHAFUNCXOESPROC) (GLenum func, GLfixed ref);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARCOLORXOESPROC) (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARDEPTHXOESPROC) (GLfixed ژوروالی_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLIPPLANEXOESPROC) (GLenum plane, ثابت GLfixed *equation);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOLOR4XOESPROC) (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHRANGEXOESPROC) (GLfixed n, GLfixed f);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFOGXOESPROC) (GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFOGXVOESPROC) (GLenum pname, ثابت GLfixed *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRUSTUMXOESPROC) (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETCLIPPLANEXOESPROC) (GLenum plane, GLfixed *equation);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFIXEDVOESPROC) (GLenum pname, GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXENVXVOESPROC) (GLenum موخه, GLenum pname, GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXPARAMETERXVOESPROC) (GLenum موخه, GLenum pname, GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLIGHTMODELXOESPROC) (GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLIGHTMODELXVOESPROC) (GLenum pname, ثابت GLfixed *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLIGHTXOESPROC) (GLenum light, GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLIGHTXVOESPROC) (GLenum light, GLenum pname, ثابت GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLINEWIDTHXOESPROC) (GLfixed پلنوالی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLOADMATRIXXOESPROC) (ثابت GLfixed *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATERIALXOESPROC) (GLenum face, GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATERIALXVOESPROC) (GLenum face, GLenum pname, ثابت GLfixed *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTMATRIXXOESPROC) (ثابت GLfixed *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTITEXCOORD4XOESPROC) (GLenum texture, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
تعريفنوع فراغ (GL_APIENTRYP PFNGLNORMAL3XOESPROC) (GLfixed nx, GLfixed ny, GLfixed nz);
تعريفنوع فراغ (GL_APIENTRYP PFNGLORTHOXOESPROC) (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOINTPARAMETERXVOESPROC) (GLenum pname, ثابت GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOINTSIZEXOESPROC) (GLfixed اندازه);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOLYGONOFFSETXOESPROC) (GLfixed ضریب, GLfixed units);
تعريفنوع فراغ (GL_APIENTRYP PFNGLROTATEXOESPROC) (GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCALEXOESPROC) (GLfixed x, GLfixed y, GLfixed z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXENVXOESPROC) (GLenum موخه, GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXENVXVOESPROC) (GLenum موخه, GLenum pname, ثابت GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERXOESPROC) (GLenum موخه, GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERXVOESPROC) (GLenum موخه, GLenum pname, ثابت GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTRANSLATEXOESPROC) (GLfixed x, GLfixed y, GLfixed z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETLIGHTXVOESPROC) (GLenum light, GLenum pname, GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETMATERIALXVOESPROC) (GLenum face, GLenum pname, GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOINTPARAMETERXOESPROC) (GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLECOVERAGEXOESPROC) (GLclampx ارزښت, GLboolean invert);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXGENXVOESPROC) (GLenum coord, GLenum pname, GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXGENXOESPROC) (GLenum coord, GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXGENXVOESPROC) (GLenum coord, GLenum pname, ثابت GLfixed *params);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glAlphaFuncxOES (GLenum func, GLfixed ref);
GL_API فراغ GL_APIENTRY glClearColorxOES (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GL_API فراغ GL_APIENTRY glClearDepthxOES (GLfixed ژوروالی_2);
GL_API فراغ GL_APIENTRY glClipPlanexOES (GLenum plane, ثابت GLfixed *equation);
GL_API فراغ GL_APIENTRY glColor4xOES (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GL_API فراغ GL_APIENTRY gl_ژوروالی_Rangex_OES (GLfixed n, GLfixed f);
GL_API فراغ GL_APIENTRY glFogxOES (GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glFogxvOES (GLenum pname, ثابت GLfixed *param);
GL_API فراغ GL_APIENTRY glFrustumxOES (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
GL_API فراغ GL_APIENTRY glGetClipPlanexOES (GLenum plane, GLfixed *equation);
GL_API فراغ GL_APIENTRY glGetFixedvOES (GLenum pname, GLfixed *params);
GL_API فراغ GL_APIENTRY glGetTexEnvxvOES (GLenum موخه, GLenum pname, GLfixed *params);
GL_API فراغ GL_APIENTRY glGetTexParameterxvOES (GLenum موخه, GLenum pname, GLfixed *params);
GL_API فراغ GL_APIENTRY glLightModelxOES (GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glLightModelxvOES (GLenum pname, ثابت GLfixed *param);
GL_API فراغ GL_APIENTRY glLightxOES (GLenum light, GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glLightxvOES (GLenum light, GLenum pname, ثابت GLfixed *params);
GL_API فراغ GL_APIENTRY gl_کرښه_Widthx_OES (GLfixed پلنوالی);
GL_API فراغ GL_APIENTRY gl_بارول_Matrixx_OES (ثابت GLfixed *m);
GL_API فراغ GL_APIENTRY glMaterialxOES (GLenum face, GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glMaterialxvOES (GLenum face, GLenum pname, ثابت GLfixed *param);
GL_API فراغ GL_APIENTRY glMultMatrixxOES (ثابت GLfixed *m);
GL_API فراغ GL_APIENTRY glMultiTexCoord4xOES (GLenum texture, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
GL_API فراغ GL_APIENTRY glNormal3xOES (GLfixed nx, GLfixed ny, GLfixed nz);
GL_API فراغ GL_APIENTRY glOrthoxOES (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
GL_API فراغ GL_APIENTRY gl_ټکی_Parameterxv_OES (GLenum pname, ثابت GLfixed *params);
GL_API فراغ GL_APIENTRY gl_ټکی_Sizex_OES (GLfixed اندازه);
GL_API فراغ GL_APIENTRY glPolygonOffsetxOES (GLfixed ضریب, GLfixed units);
GL_API فراغ GL_APIENTRY glRotatexOES (GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
GL_API فراغ GL_APIENTRY glScalexOES (GLfixed x, GLfixed y, GLfixed z);
GL_API فراغ GL_APIENTRY glTexEnvxOES (GLenum موخه, GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glTexEnvxvOES (GLenum موخه, GLenum pname, ثابت GLfixed *params);
GL_API فراغ GL_APIENTRY glTexParameterxOES (GLenum موخه, GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glTexParameterxvOES (GLenum موخه, GLenum pname, ثابت GLfixed *params);
GL_API فراغ GL_APIENTRY glTranslatexOES (GLfixed x, GLfixed y, GLfixed z);
GL_API فراغ GL_APIENTRY glGetLightxvOES (GLenum light, GLenum pname, GLfixed *params);
GL_API فراغ GL_APIENTRY glGetMaterialxvOES (GLenum face, GLenum pname, GLfixed *params);
GL_API فراغ GL_APIENTRY gl_ټکی_Parameterx_OES (GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glSampleCoveragexOES (GLclampx ارزښت, GLboolean invert);
GL_API فراغ GL_APIENTRY glGetTexGenxvOES (GLenum coord, GLenum pname, GLfixed *params);
GL_API فراغ GL_APIENTRY glTexGenxOES (GLenum coord, GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glTexGenxvOES (GLenum coord, GLenum pname, ثابت GLfixed *params);
#د_که_پای
#د_که_پای /* GL_OES_fixed_point */

#که_نه_تعریف_شوی GL_OES_framebuffer_object
#تعریف_کړه GL_OES_framebuffer_object 1
#تعریف_کړه GL_NONE_OES                       0
#تعریف_کړه GL_FRAMEBUFFER_OES                0x8D40
#تعریف_کړه GL_RENDERBUFFER_OES               0x8D41
#تعریف_کړه GL_RGBA4_OES                      0x8056
#تعریف_کړه GL_RGB5_A1_OES                    0x8057
#تعریف_کړه GL_RGB565_OES                     0x8D62
#تعریف_کړه GL_ژوروالی_COMPONENT16_OES          0x81A5
#تعریف_کړه GL_RENDERBUFFER_پلنوالی_OES         0x8D42
#تعریف_کړه GL_RENDERBUFFER_لوړوالی_OES        0x8D43
#تعریف_کړه GL_RENDERBUFFER_دننی_FORMAT_OES 0x8D44
#تعریف_کړه GL_RENDERBUFFER_RED_اندازه_OES      0x8D50
#تعریف_کړه GL_RENDERBUFFER_GREEN_اندازه_OES    0x8D51
#تعریف_کړه GL_RENDERBUFFER_BLUE_اندازه_OES     0x8D52
#تعریف_کړه GL_RENDERBUFFER_ALPHA_اندازه_OES    0x8D53
#تعریف_کړه GL_RENDERBUFFER_ژوروالی_اندازه_OES    0x8D54
#تعریف_کړه GL_RENDERBUFFER_STENCIL_اندازه_OES  0x8D55
#تعریف_کړه GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_OES 0x8CD0
#تعریف_کړه GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_OES 0x8CD1
#تعریف_کړه GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_OES 0x8CD2
#تعریف_کړه GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_OES 0x8CD3
#تعریف_کړه GL_COLOR_ATTACHMENT0_OES          0x8CE0
#تعریف_کړه GL_ژوروالی_ATTACHMENT_OES           0x8D00
#تعریف_کړه GL_STENCIL_ATTACHMENT_OES         0x8D20
#تعریف_کړه GL_FRAMEBUFFER_COMPLETE_OES       0x8CD5
#تعریف_کړه GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_OES 0x8CD6
#تعریف_کړه GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_OES 0x8CD7
#تعریف_کړه GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_OES 0x8CD9
#تعریف_کړه GL_FRAMEBUFFER_INCOMPLETE_FORMATS_OES 0x8CDA
#تعریف_کړه GL_FRAMEBUFFER_UNSUPPORTED_OES    0x8CDD
#تعریف_کړه GL_FRAMEBUFFER_BINDING_OES        0x8CA6
#تعریف_کړه GL_RENDERBUFFER_BINDING_OES       0x8CA7
#تعریف_کړه GL_MAX_RENDERBUFFER_اندازه_OES      0x84E8
#تعریف_کړه GL_INVALID_FRAMEBUFFER_OPERATION_OES 0x0506
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISRENDERBUFFEROESPROC) (GLuint renderbuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDRENDERBUFFEROESPROC) (GLenum موخه, GLuint renderbuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETERENDERBUFFERSOESPROC) (GLsizei n, ثابت GLuint *renderbuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENRENDERBUFFERSOESPROC) (GLsizei n, GLuint *renderbuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEOESPROC) (GLenum موخه, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVOESPROC) (GLenum موخه, GLenum pname, GLint *params);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISFRAMEBUFFEROESPROC) (GLuint framebuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDFRAMEBUFFEROESPROC) (GLenum موخه, GLuint framebuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEFRAMEBUFFERSOESPROC) (GLsizei n, ثابت GLuint *framebuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENFRAMEBUFFERSOESPROC) (GLsizei n, GLuint *framebuffers);
تعريفنوع GLenum (GL_APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSOESPROC) (GLenum موخه);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFEROESPROC) (GLenum موخه, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DOESPROC) (GLenum موخه, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVOESPROC) (GLenum موخه, GLenum attachment, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENERATEMIPMAPOESPROC) (GLenum موخه);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_API GLboolean GL_APIENTRY glIsRenderbufferOES (GLuint renderbuffer);
GL_API فراغ GL_APIENTRY glBindRenderbufferOES (GLenum موخه, GLuint renderbuffer);
GL_API فراغ GL_APIENTRY glDeleteRenderbuffersOES (GLsizei n, ثابت GLuint *renderbuffers);
GL_API فراغ GL_APIENTRY glGenRenderbuffersOES (GLsizei n, GLuint *renderbuffers);
GL_API فراغ GL_APIENTRY glRenderbufferStorageOES (GLenum موخه, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
GL_API فراغ GL_APIENTRY glGetRenderbufferParameterivOES (GLenum موخه, GLenum pname, GLint *params);
GL_API GLboolean GL_APIENTRY glIsFramebufferOES (GLuint framebuffer);
GL_API فراغ GL_APIENTRY glBindFramebufferOES (GLenum موخه, GLuint framebuffer);
GL_API فراغ GL_APIENTRY glDeleteFramebuffersOES (GLsizei n, ثابت GLuint *framebuffers);
GL_API فراغ GL_APIENTRY glGenFramebuffersOES (GLsizei n, GLuint *framebuffers);
GL_API GLenum GL_APIENTRY gl_Check_Framebuffer_حالت_OES (GLenum موخه);
GL_API فراغ GL_APIENTRY glFramebufferRenderbufferOES (GLenum موخه, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
GL_API فراغ GL_APIENTRY glFramebufferTexture2DOES (GLenum موخه, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GL_API فراغ GL_APIENTRY glGetFramebufferAttachmentParameterivOES (GLenum موخه, GLenum attachment, GLenum pname, GLint *params);
GL_API فراغ GL_APIENTRY glGenerateMipmapOES (GLenum موخه);
#د_که_پای
#د_که_پای /* GL_OES_framebuffer_object */

#که_نه_تعریف_شوی GL_OES_mapbuffer
#تعریف_کړه GL_OES_mapbuffer 1
#تعریف_کړه GL_WRITE_ONLY_OES                 0x88B9
#تعریف_کړه GL_بفر_ACCESS_OES              0x88BB
#تعریف_کړه GL_بفر_MAPPED_OES              0x88BC
#تعریف_کړه GL_بفر_MAP_اشاره_ګر_OES         0x88BD
تعريفنوع فراغ *(GL_APIENTRYP PFNGLMAPBUFFEROESPROC) (GLenum موخه, GLenum access);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLUNMAPBUFFEROESPROC) (GLenum موخه);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETBUFFERPOINTERVOESPROC) (GLenum موخه, GLenum pname, فراغ **params);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_API فراغ *GL_APIENTRY gl_Map_بفر_OES (GLenum موخه, GLenum access);
GL_API GLboolean GL_APIENTRY gl_Unmap_بفر_OES (GLenum موخه);
GL_API فراغ GL_APIENTRY gl_Get_بفر_Pointerv_OES (GLenum موخه, GLenum pname, فراغ **params);
#د_که_پای
#د_که_پای /* GL_OES_mapbuffer */

#که_نه_تعریف_شوی GL_OES_ماتریکس_get
#تعریف_کړه GL_OES_ماتریکس_get 1
#تعریف_کړه GL_MODELVIEW_ماتریکس_FLOAT_AS_INT_بټونه_OES 0x898D
#تعریف_کړه GL_PROJECTION_ماتریکس_FLOAT_AS_INT_بټونه_OES 0x898E
#تعریف_کړه GL_TEXTURE_ماتریکس_FLOAT_AS_INT_بټونه_OES 0x898F
#د_که_پای /* GL_OES_matrix_get */

#که_نه_تعریف_شوی GL_OES_ماتریکس_palette
#تعریف_کړه GL_OES_ماتریکس_palette 1
#تعریف_کړه GL_MAX_راس_UNITS_OES           0x86A4
#تعریف_کړه GL_MAX_PALETTE_MATRICES_OES       0x8842
#تعریف_کړه GL_ماتریکس_PALETTE_OES             0x8840
#تعریف_کړه GL_ماتریکس_شاخص_ARRAY_OES         0x8844
#تعریف_کړه GL_وزن_ARRAY_OES               0x86AD
#تعریف_کړه GL_CURRENT_PALETTE_ماتریکس_OES     0x8843
#تعریف_کړه GL_ماتریکس_شاخص_ARRAY_اندازه_OES    0x8846
#تعریف_کړه GL_ماتریکس_شاخص_ARRAY_TYPE_OES    0x8847
#تعریف_کړه GL_ماتریکس_شاخص_ARRAY_STRIDE_OES  0x8848
#تعریف_کړه GL_ماتریکس_شاخص_ARRAY_اشاره_ګر_OES 0x8849
#تعریف_کړه GL_ماتریکس_شاخص_ARRAY_بفر_BINDING_OES 0x8B9E
#تعریف_کړه GL_وزن_ARRAY_اندازه_OES          0x86AB
#تعریف_کړه GL_وزن_ARRAY_TYPE_OES          0x86A9
#تعریف_کړه GL_وزن_ARRAY_STRIDE_OES        0x86AA
#تعریف_کړه GL_وزن_ARRAY_اشاره_ګر_OES       0x86AC
#تعریف_کړه GL_وزن_ARRAY_بفر_BINDING_OES 0x889E
تعريفنوع فراغ (GL_APIENTRYP PFNGLCURRENTPALETTEMATRIXOESPROC) (GLuint matrixpaletteindex);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLOADPALETTEFROMMODELVIEWMATRIXOESPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXINDEXPOINTEROESPROC) (GLint اندازه, GLenum type, GLsizei stride, ثابت فراغ *اشاره_ګر_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLWEIGHTPOINTEROESPROC) (GLint اندازه, GLenum type, GLsizei stride, ثابت فراغ *اشاره_ګر_2);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY gl_Current_Palette_ماتریکس_OES (GLuint matrixpaletteindex);
GL_API فراغ GL_APIENTRY gl_بارول_Palette_From_Model_View_ماتریکس_OES (فراغ);
GL_API فراغ GL_APIENTRY gl_ماتریکس_شاخص_اشاره_ګر_OES (GLint اندازه, GLenum type, GLsizei stride, ثابت فراغ *اشاره_ګر_2);
GL_API فراغ GL_APIENTRY gl_وزن_اشاره_ګر_OES (GLint اندازه, GLenum type, GLsizei stride, ثابت فراغ *اشاره_ګر_2);
#د_که_پای
#د_که_پای /* GL_OES_matrix_palette */

#که_نه_تعریف_شوی GL_OES_packed_ژوروالی_stencil
#تعریف_کړه GL_OES_packed_ژوروالی_stencil 1
#تعریف_کړه GL_ژوروالی_STENCIL_OES              0x84F9
#تعریف_کړه GL_UNSIGNED_INT_24_8_OES          0x84FA
#تعریف_کړه GL_DEPTH24_STENCIL8_OES           0x88F0
#د_که_پای /* GL_OES_packed_depth_stencil */

#که_نه_تعریف_شوی GL_OES_query_ماتریکس
#تعریف_کړه GL_OES_query_ماتریکس 1
تعريفنوع GLbitfield (GL_APIENTRYP PFNGLQUERYMATRIXXOESPROC) (GLfixed *mantissa, GLint *exponent);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_API GLbitfield GL_APIENTRY glQueryMatrixxOES (GLfixed *mantissa, GLint *exponent);
#د_که_پای
#د_که_پای /* GL_OES_query_matrix */

#که_نه_تعریف_شوی GL_OES_required_internalformat
#تعریف_کړه GL_OES_required_internalformat 1
#تعریف_کړه GL_ALPHA8_OES                     0x803C
#تعریف_کړه GL_LUMINANCE4_ALPHA4_OES          0x8043
#تعریف_کړه GL_LUMINANCE8_ALPHA8_OES          0x8045
#تعریف_کړه GL_LUMINANCE8_OES                 0x8040
#تعریف_کړه GL_RGB8_OES                       0x8051
#تعریف_کړه GL_RGBA8_OES                      0x8058
#تعریف_کړه GL_RGB10_EXT                      0x8052
#تعریف_کړه GL_RGB10_A2_EXT                   0x8059
#د_که_پای /* GL_OES_required_internalformat */

#که_نه_تعریف_شوی GL_OES_rgb8_rgba8
#تعریف_کړه GL_OES_rgb8_rgba8 1
#د_که_پای /* GL_OES_rgb8_rgba8 */

#که_نه_تعریف_شوی GL_OES_single_precision
#تعریف_کړه GL_OES_single_precision 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARDEPTHFOESPROC) (GLclampf ژوروالی_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLIPPLANEFOESPROC) (GLenum plane, ثابت GLfloat *equation);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHRANGEFOESPROC) (GLclampf n, GLclampf f);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRUSTUMFOESPROC) (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETCLIPPLANEFOESPROC) (GLenum plane, GLfloat *equation);
تعريفنوع فراغ (GL_APIENTRYP PFNGLORTHOFOESPROC) (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glClearDepthfOES (GLclampf ژوروالی_2);
GL_API فراغ GL_APIENTRY glClipPlanefOES (GLenum plane, ثابت GLfloat *equation);
GL_API فراغ GL_APIENTRY gl_ژوروالی_Rangef_OES (GLclampf n, GLclampf f);
GL_API فراغ GL_APIENTRY glFrustumfOES (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
GL_API فراغ GL_APIENTRY glGetClipPlanefOES (GLenum plane, GLfloat *equation);
GL_API فراغ GL_APIENTRY glOrthofOES (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
#د_که_پای
#د_که_پای /* GL_OES_single_precision */

#که_نه_تعریف_شوی GL_OES_stencil1
#تعریف_کړه GL_OES_stencil1 1
#تعریف_کړه GL_STENCIL_INDEX1_OES             0x8D46
#د_که_پای /* GL_OES_stencil1 */

#که_نه_تعریف_شوی GL_OES_stencil4
#تعریف_کړه GL_OES_stencil4 1
#تعریف_کړه GL_STENCIL_INDEX4_OES             0x8D47
#د_که_پای /* GL_OES_stencil4 */

#که_نه_تعریف_شوی GL_OES_stencil8
#تعریف_کړه GL_OES_stencil8 1
#تعریف_کړه GL_STENCIL_INDEX8_OES             0x8D48
#د_که_پای /* GL_OES_stencil8 */

#که_نه_تعریف_شوی GL_OES_stencil_wrap
#تعریف_کړه GL_OES_stencil_wrap 1
#تعریف_کړه GL_INCR_WRAP_OES                  0x8507
#تعریف_کړه GL_DECR_WRAP_OES                  0x8508
#د_که_پای /* GL_OES_stencil_wrap */

#که_نه_تعریف_شوی GL_OES_surfaceless_context
#تعریف_کړه GL_OES_surfaceless_context 1
#تعریف_کړه GL_FRAMEBUFFER_UNDEFINED_OES      0x8219
#د_که_پای /* GL_OES_surfaceless_context */

#که_نه_تعریف_شوی GL_OES_texture_cube_map
#تعریف_کړه GL_OES_texture_cube_map 1
#تعریف_کړه GL_نورمال_MAP_OES                 0x8511
#تعریف_کړه GL_REFLECTION_MAP_OES             0x8512
#تعریف_کړه GL_TEXTURE_CUBE_MAP_OES           0x8513
#تعریف_کړه GL_TEXTURE_BINDING_CUBE_MAP_OES   0x8514
#تعریف_کړه GL_TEXTURE_CUBE_MAP_مثبت_X_OES 0x8515
#تعریف_کړه GL_TEXTURE_CUBE_MAP_NEGATIVE_X_OES 0x8516
#تعریف_کړه GL_TEXTURE_CUBE_MAP_مثبت_Y_OES 0x8517
#تعریف_کړه GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_OES 0x8518
#تعریف_کړه GL_TEXTURE_CUBE_MAP_مثبت_Z_OES 0x8519
#تعریف_کړه GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_OES 0x851A
#تعریف_کړه GL_MAX_CUBE_MAP_TEXTURE_اندازه_OES  0x851C
#تعریف_کړه GL_TEXTURE_GEN_ډېرپېښ_OES           0x2500
#تعریف_کړه GL_TEXTURE_GEN_STR_OES            0x8D60
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXGENFOESPROC) (GLenum coord, GLenum pname, GLfloat param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXGENFVOESPROC) (GLenum coord, GLenum pname, ثابت GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXGENIOESPROC) (GLenum coord, GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXGENIVOESPROC) (GLenum coord, GLenum pname, ثابت GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXGENFVOESPROC) (GLenum coord, GLenum pname, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXGENIVOESPROC) (GLenum coord, GLenum pname, GLint *params);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glTexGenfOES (GLenum coord, GLenum pname, GLfloat param);
GL_API فراغ GL_APIENTRY glTexGenfvOES (GLenum coord, GLenum pname, ثابت GLfloat *params);
GL_API فراغ GL_APIENTRY glTexGeniOES (GLenum coord, GLenum pname, GLint param);
GL_API فراغ GL_APIENTRY glTexGenivOES (GLenum coord, GLenum pname, ثابت GLint *params);
GL_API فراغ GL_APIENTRY glGetTexGenfvOES (GLenum coord, GLenum pname, GLfloat *params);
GL_API فراغ GL_APIENTRY glGetTexGenivOES (GLenum coord, GLenum pname, GLint *params);
#د_که_پای
#د_که_پای /* GL_OES_texture_cube_map */

#که_نه_تعریف_شوی GL_OES_texture_env_crossbar
#تعریف_کړه GL_OES_texture_env_crossbar 1
#د_که_پای /* GL_OES_texture_env_crossbar */

#که_نه_تعریف_شوی GL_OES_texture_mirrored_repeat
#تعریف_کړه GL_OES_texture_mirrored_repeat 1
#تعریف_کړه GL_MIRRORED_REPEAT_OES            0x8370
#د_که_پای /* GL_OES_texture_mirrored_repeat */

#که_نه_تعریف_شوی GL_OES_texture_npot
#تعریف_کړه GL_OES_texture_npot 1
#د_که_پای /* GL_OES_texture_npot */

#که_نه_تعریف_شوی GL_OES_راس_array_object
#تعریف_کړه GL_OES_راس_array_object 1
#تعریف_کړه GL_راس_ARRAY_BINDING_OES       0x85B5
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDVERTEXARRAYOESPROC) (GLuint array);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEVERTEXARRAYSOESPROC) (GLsizei n, ثابت GLuint *arrays);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENVERTEXARRAYSOESPROC) (GLsizei n, GLuint *arrays);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISVERTEXARRAYOESPROC) (GLuint array);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY gl_Bind_راس_Array_OES (GLuint array);
GL_API فراغ GL_APIENTRY gl_Delete_راس_Arrays_OES (GLsizei n, ثابت GLuint *arrays);
GL_API فراغ GL_APIENTRY gl_Gen_راس_Arrays_OES (GLsizei n, GLuint *arrays);
GL_API GLboolean GL_APIENTRY gl_Is_راس_Array_OES (GLuint array);
#د_که_پای
#د_که_پای /* GL_OES_vertex_array_object */

#که_نه_تعریف_شوی GL_AMD_compressed_3DC_texture
#تعریف_کړه GL_AMD_compressed_3DC_texture 1
#تعریف_کړه GL_3DC_X_AMD                      0x87F9
#تعریف_کړه GL_3DC_XY_AMD                     0x87FA
#د_که_پای /* GL_AMD_compressed_3DC_texture */

#که_نه_تعریف_شوی GL_AMD_compressed_ATC_texture
#تعریف_کړه GL_AMD_compressed_ATC_texture 1
#تعریف_کړه GL_ATC_RGB_AMD                    0x8C92
#تعریف_کړه GL_ATC_RGBA_EXPLICIT_ALPHA_AMD    0x8C93
#تعریف_کړه GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD 0x87EE
#د_که_پای /* GL_AMD_compressed_ATC_texture */

#که_نه_تعریف_شوی GL_APPLE_copy_texture_پوړونه
#تعریف_کړه GL_APPLE_copy_texture_پوړونه 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYTEXTURELEVELSAPPLEPROC) (GLuint destinationTexture, GLuint سرچینه_Texture, GLint سرچینه_بنسټ_Level, GLsizei سرچینه_Level_شمېر);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY gl_Copy_Texture_پوړونه_APPLE (GLuint destinationTexture, GLuint سرچینه_Texture, GLint سرچینه_بنسټ_Level, GLsizei سرچینه_Level_شمېر);
#د_که_پای
#د_که_پای /* GL_APPLE_copy_texture_levels */

#که_نه_تعریف_شوی GL_APPLE_framebuffer_multisample
#تعریف_کړه GL_APPLE_framebuffer_multisample 1
#تعریف_کړه GL_RENDERBUFFER_SAMPLES_APPLE     0x8CAB
#تعریف_کړه GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_APPLE 0x8D56
#تعریف_کړه GL_MAX_SAMPLES_APPLE              0x8D57
#تعریف_کړه GL_READ_FRAMEBUFFER_APPLE         0x8CA8
#تعریف_کړه GL_DRAW_FRAMEBUFFER_APPLE         0x8CA9
#تعریف_کړه GL_DRAW_FRAMEBUFFER_BINDING_APPLE 0x8CA6
#تعریف_کړه GL_READ_FRAMEBUFFER_BINDING_APPLE 0x8CAA
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEAPPLEPROC) (GLenum موخه, GLsizei samples, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRESOLVEMULTISAMPLEFRAMEBUFFERAPPLEPROC) (فراغ);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glRenderbufferStorageMultisampleAPPLE (GLenum موخه, GLsizei samples, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
GL_API فراغ GL_APIENTRY glResolveMultisampleFramebufferAPPLE (فراغ);
#د_که_پای
#د_که_پای /* GL_APPLE_framebuffer_multisample */

#که_نه_تعریف_شوی GL_APPLE_sync
#تعریف_کړه GL_APPLE_sync 1
تعريفنوع بنية __GLsync *GLsync;
تعريفنوع khronos_uint64_t GLuint64;
تعريفنوع khronos_int64_t GLint64;
#تعریف_کړه GL_SYNC_OBJECT_APPLE              0x8A53
#تعریف_کړه GL_MAX_SERVER_WAIT_TIMEOUT_APPLE  0x9111
#تعریف_کړه GL_OBJECT_TYPE_APPLE              0x9112
#تعریف_کړه GL_SYNC_CONDITION_APPLE           0x9113
#تعریف_کړه GL_SYNC_حالت_APPLE              0x9114
#تعریف_کړه GL_SYNC_FLAGS_APPLE               0x9115
#تعریف_کړه GL_SYNC_FENCE_APPLE               0x9116
#تعریف_کړه GL_SYNC_GPU_COMMANDS_COMPLETE_APPLE 0x9117
#تعریف_کړه GL_UNSIGNALED_APPLE               0x9118
#تعریف_کړه GL_SIGNALED_APPLE                 0x9119
#تعریف_کړه GL_ALREADY_SIGNALED_APPLE         0x911A
#تعریف_کړه GL_TIMEOUT_EXPIRED_APPLE          0x911B
#تعریف_کړه GL_CONDITION_SATISFIED_APPLE      0x911C
#تعریف_کړه GL_WAIT_FAILED_APPLE              0x911D
#تعریف_کړه GL_SYNC_FLUSH_COMMANDS_بټ_APPLE  0x00000001
#تعریف_کړه GL_TIMEOUT_IGNORED_APPLE          0xFFFFFFFFFFFFFFFFull
تعريفنوع GLsync (GL_APIENTRYP PFNGLFENCESYNCAPPLEPROC) (GLenum condition, GLbitfield flags);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISSYNCAPPLEPROC) (GLsync sync);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETESYNCAPPLEPROC) (GLsync sync);
تعريفنوع GLenum (GL_APIENTRYP PFNGLCLIENTWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
تعريفنوع فراغ (GL_APIENTRYP PFNGLWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTEGER64VAPPLEPROC) (GLenum pname, GLint64 *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSYNCIVAPPLEPROC) (GLsync sync, GLenum pname, GLsizei شمېر, GLsizei *اوږدتیا, GLint *ارزښتونه);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_API GLsync GL_APIENTRY glFenceSyncAPPLE (GLenum condition, GLbitfield flags);
GL_API GLboolean GL_APIENTRY glIsSyncAPPLE (GLsync sync);
GL_API فراغ GL_APIENTRY glDeleteSyncAPPLE (GLsync sync);
GL_API GLenum GL_APIENTRY glClientWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_API فراغ GL_APIENTRY glWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_API فراغ GL_APIENTRY glGetInteger64vAPPLE (GLenum pname, GLint64 *params);
GL_API فراغ GL_APIENTRY glGetSyncivAPPLE (GLsync sync, GLenum pname, GLsizei شمېر, GLsizei *اوږدتیا, GLint *ارزښتونه);
#د_که_پای
#د_که_پای /* GL_APPLE_sync */

#که_نه_تعریف_شوی GL_APPLE_texture_2D_limited_npot
#تعریف_کړه GL_APPLE_texture_2D_limited_npot 1
#د_که_پای /* GL_APPLE_texture_2D_limited_npot */

#که_نه_تعریف_شوی GL_APPLE_texture_format_BGRA8888
#تعریف_کړه GL_APPLE_texture_format_BGRA8888 1
#تعریف_کړه GL_BGRA_EXT                       0x80E1
#تعریف_کړه GL_BGRA8_EXT                      0x93A1
#د_که_پای /* GL_APPLE_texture_format_BGRA8888 */

#که_نه_تعریف_شوی GL_APPLE_texture_max_level
#تعریف_کړه GL_APPLE_texture_max_level 1
#تعریف_کړه GL_TEXTURE_MAX_LEVEL_APPLE        0x813D
#د_که_پای /* GL_APPLE_texture_max_level */

#که_نه_تعریف_شوی GL_ARM_rgba8
#تعریف_کړه GL_ARM_rgba8 1
#د_که_پای /* GL_ARM_rgba8 */

#که_نه_تعریف_شوی GL_EXT_blend_minmax
#تعریف_کړه GL_EXT_blend_minmax 1
#تعریف_کړه GL_MIN_EXT                        0x8007
#تعریف_کړه GL_MAX_EXT                        0x8008
#د_که_پای /* GL_EXT_blend_minmax */

#که_نه_تعریف_شوی GL_EXT_debug_marker
#تعریف_کړه GL_EXT_debug_marker 1
تعريفنوع حرف GLchar;
تعريفنوع فراغ (GL_APIENTRYP PFNGLINSERTEVENTMARKEREXTPROC) (GLsizei اوږدتیا, ثابت GLchar *marker);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPUSHGROUPMARKEREXTPROC) (GLsizei اوږدتیا, ثابت GLchar *marker);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOPGROUPMARKEREXTPROC) (فراغ);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY gl_ورننباسه_Event_Marker_EXT (GLsizei اوږدتیا, ثابت GLchar *marker);
GL_API فراغ GL_APIENTRY gl_ټېل_ډله_Marker_EXT (GLsizei اوږدتیا, ثابت GLchar *marker);
GL_API فراغ GL_APIENTRY gl_راوباسه_ډله_Marker_EXT (فراغ);
#د_که_پای
#د_که_پای /* GL_EXT_debug_marker */

#که_نه_تعریف_شوی GL_EXT_discard_framebuffer
#تعریف_کړه GL_EXT_discard_framebuffer 1
#تعریف_کړه GL_COLOR_EXT                      0x1800
#تعریف_کړه GL_ژوروالی_EXT                      0x1801
#تعریف_کړه GL_STENCIL_EXT                    0x1802
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISCARDFRAMEBUFFEREXTPROC) (GLenum موخه, GLsizei عدد_Attachments, ثابت GLenum *attachments);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glDiscardFramebufferEXT (GLenum موخه, GLsizei عدد_Attachments, ثابت GLenum *attachments);
#د_که_پای
#د_که_پای /* GL_EXT_discard_framebuffer */

#که_نه_تعریف_شوی GL_EXT_map_بفر_range
#تعریف_کړه GL_EXT_map_بفر_range 1
#تعریف_کړه GL_MAP_READ_بټ_EXT               0x0001
#تعریف_کړه GL_MAP_WRITE_بټ_EXT              0x0002
#تعریف_کړه GL_MAP_INVALIDATE_RANGE_بټ_EXT   0x0004
#تعریف_کړه GL_MAP_INVALIDATE_بفر_بټ_EXT  0x0008
#تعریف_کړه GL_MAP_FLUSH_EXPLICIT_بټ_EXT     0x0010
#تعریف_کړه GL_MAP_UNSYNCHRONIZED_بټ_EXT     0x0020
تعريفنوع فراغ *(GL_APIENTRYP PFNGLMAPBUFFERRANGEEXTPROC) (GLenum موخه, GLintptr دننه_واټن_2, GLsizeiptr اوږدتیا, GLbitfield access);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEEXTPROC) (GLenum موخه, GLintptr دننه_واټن_2, GLsizeiptr اوږدتیا);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_API فراغ *GL_APIENTRY gl_Map_بفر_Range_EXT (GLenum موخه, GLintptr دننه_واټن_2, GLsizeiptr اوږدتیا, GLbitfield access);
GL_API فراغ GL_APIENTRY gl_Flush_Mapped_بفر_Range_EXT (GLenum موخه, GLintptr دننه_واټن_2, GLsizeiptr اوږدتیا);
#د_که_پای
#د_که_پای /* GL_EXT_map_buffer_range */

#که_نه_تعریف_شوی GL_EXT_multi_draw_arrays
#تعریف_کړه GL_EXT_multi_draw_arrays 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWARRAYSEXTPROC) (GLenum ډېرپېښ, ثابت GLint *لومړی, ثابت GLsizei *شمېر, GLsizei primcount);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSEXTPROC) (GLenum ډېرپېښ, ثابت GLsizei *شمېر, GLenum type, ثابت فراغ *ثابت*indices, GLsizei primcount);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glMultiDrawArraysEXT (GLenum ډېرپېښ, ثابت GLint *لومړی, ثابت GLsizei *شمېر, GLsizei primcount);
GL_API فراغ GL_APIENTRY glMultiDrawElementsEXT (GLenum ډېرپېښ, ثابت GLsizei *شمېر, GLenum type, ثابت فراغ *ثابت*indices, GLsizei primcount);
#د_که_پای
#د_که_پای /* GL_EXT_multi_draw_arrays */

#که_نه_تعریف_شوی GL_EXT_multisampled_render_منزل_texture
#تعریف_کړه GL_EXT_multisampled_render_منزل_texture 1
#تعریف_کړه GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SAMPLES_EXT 0x8D6C
#تعریف_کړه GL_RENDERBUFFER_SAMPLES_EXT       0x8CAB
#تعریف_کړه GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT 0x8D56
#تعریف_کړه GL_MAX_SAMPLES_EXT                0x8D57
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) (GLenum موخه, GLsizei samples, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEEXTPROC) (GLenum موخه, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glRenderbufferStorageMultisampleEXT (GLenum موخه, GLsizei samples, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
GL_API فراغ GL_APIENTRY glFramebufferTexture2DMultisampleEXT (GLenum موخه, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#د_که_پای
#د_که_پای /* GL_EXT_multisampled_render_to_texture */

#که_نه_تعریف_شوی GL_EXT_read_format_bgra
#تعریف_کړه GL_EXT_read_format_bgra 1
#تعریف_کړه GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT 0x8365
#تعریف_کړه GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT 0x8366
#د_که_پای /* GL_EXT_read_format_bgra */

#که_نه_تعریف_شوی GL_EXT_robustness
#تعریف_کړه GL_EXT_robustness 1
#تعریف_کړه GL_GUILTY_CONTEXT_RESET_EXT       0x8253
#تعریف_کړه GL_INNOCENT_CONTEXT_RESET_EXT     0x8254
#تعریف_کړه GL_UNKNOWN_CONTEXT_RESET_EXT      0x8255
#تعریف_کړه GL_CONTEXT_ROBUST_ACCESS_EXT      0x90F3
#تعریف_کړه GL_RESET_NOTIFICATION_STRATEGY_EXT 0x8256
#تعریف_کړه GL_LOSE_CONTEXT_ON_RESET_EXT      0x8252
#تعریف_کړه GL_NO_RESET_NOTIFICATION_EXT      0x8261
تعريفنوع GLenum (GL_APIENTRYP PFNGLGETGRAPHICSRESETSTATUSEXTPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLREADNPIXELSEXTPROC) (GLint x, GLint y, GLsizei پلنوالی, GLsizei لوړوالی, GLenum format, GLenum type, GLsizei buf_اندازه, فراغ *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNUNIFORMFVEXTPROC) (GLuint پروګرام, GLint location, GLsizei buf_اندازه, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNUNIFORMIVEXTPROC) (GLuint پروګرام, GLint location, GLsizei buf_اندازه, GLint *params);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_API GLenum GL_APIENTRY gl_Get_Graphics_Reset_حالت_EXT (فراغ);
GL_API فراغ GL_APIENTRY glReadnPixelsEXT (GLint x, GLint y, GLsizei پلنوالی, GLsizei لوړوالی, GLenum format, GLenum type, GLsizei buf_اندازه, فراغ *معلومات);
GL_API فراغ GL_APIENTRY glGetnUniformfvEXT (GLuint پروګرام, GLint location, GLsizei buf_اندازه, GLfloat *params);
GL_API فراغ GL_APIENTRY glGetnUniformivEXT (GLuint پروګرام, GLint location, GLsizei buf_اندازه, GLint *params);
#د_که_پای
#د_که_پای /* GL_EXT_robustness */

#که_نه_تعریف_شوی GL_EXT_sRGB
#تعریف_کړه GL_EXT_sRGB 1
#تعریف_کړه GL_SRGB_EXT                       0x8C40
#تعریف_کړه GL_SRGB_ALPHA_EXT                 0x8C42
#تعریف_کړه GL_SRGB8_ALPHA8_EXT               0x8C43
#تعریف_کړه GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING_EXT 0x8210
#د_که_پای /* GL_EXT_sRGB */

#که_نه_تعریف_شوی GL_EXT_texture_compression_dxt1
#تعریف_کړه GL_EXT_texture_compression_dxt1 1
#تعریف_کړه GL_COMPRESSED_RGB_S3TC_DXT1_EXT   0x83F0
#تعریف_کړه GL_COMPRESSED_RGBA_S3TC_DXT1_EXT  0x83F1
#د_که_پای /* GL_EXT_texture_compression_dxt1 */

#که_نه_تعریف_شوی GL_EXT_texture_filter_anisotropic
#تعریف_کړه GL_EXT_texture_filter_anisotropic 1
#تعریف_کړه GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#تعریف_کړه GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#د_که_پای /* GL_EXT_texture_filter_anisotropic */

#که_نه_تعریف_شوی GL_EXT_texture_format_BGRA8888
#تعریف_کړه GL_EXT_texture_format_BGRA8888 1
#د_که_پای /* GL_EXT_texture_format_BGRA8888 */

#که_نه_تعریف_شوی GL_EXT_texture_lod_bias
#تعریف_کړه GL_EXT_texture_lod_bias 1
#تعریف_کړه GL_MAX_TEXTURE_LOD_BIAS_EXT       0x84FD
#تعریف_کړه GL_TEXTURE_FILTER_CONTROL_EXT     0x8500
#تعریف_کړه GL_TEXTURE_LOD_BIAS_EXT           0x8501
#د_که_پای /* GL_EXT_texture_lod_bias */

#که_نه_تعریف_شوی GL_EXT_texture_storage
#تعریف_کړه GL_EXT_texture_storage 1
#تعریف_کړه GL_TEXTURE_IMMUTABLE_FORMAT_EXT   0x912F
#تعریف_کړه GL_ALPHA8_EXT                     0x803C
#تعریف_کړه GL_LUMINANCE8_EXT                 0x8040
#تعریف_کړه GL_LUMINANCE8_ALPHA8_EXT          0x8045
#تعریف_کړه GL_RGBA32F_EXT                    0x8814
#تعریف_کړه GL_RGB32F_EXT                     0x8815
#تعریف_کړه GL_ALPHA32F_EXT                   0x8816
#تعریف_کړه GL_LUMINANCE32F_EXT               0x8818
#تعریف_کړه GL_LUMINANCE_ALPHA32F_EXT         0x8819
#تعریف_کړه GL_RGBA16F_EXT                    0x881A
#تعریف_کړه GL_RGB16F_EXT                     0x881B
#تعریف_کړه GL_ALPHA16F_EXT                   0x881C
#تعریف_کړه GL_LUMINANCE16F_EXT               0x881E
#تعریف_کړه GL_LUMINANCE_ALPHA16F_EXT         0x881F
#تعریف_کړه GL_R8_EXT                         0x8229
#تعریف_کړه GL_RG8_EXT                        0x822B
#تعریف_کړه GL_R32F_EXT                       0x822E
#تعریف_کړه GL_RG32F_EXT                      0x8230
#تعریف_کړه GL_R16F_EXT                       0x822D
#تعریف_کړه GL_RG16F_EXT                      0x822F
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE1DEXTPROC) (GLenum موخه, GLsizei پوړونه, GLenum internalformat, GLsizei پلنوالی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE2DEXTPROC) (GLenum موخه, GLsizei پوړونه, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE3DEXTPROC) (GLenum موخه, GLsizei پوړونه, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGE1DEXTPROC) (GLuint texture, GLenum موخه, GLsizei پوړونه, GLenum internalformat, GLsizei پلنوالی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGE2DEXTPROC) (GLuint texture, GLenum موخه, GLsizei پوړونه, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGE3DEXTPROC) (GLuint texture, GLenum موخه, GLsizei پوړونه, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glTexStorage1DEXT (GLenum موخه, GLsizei پوړونه, GLenum internalformat, GLsizei پلنوالی);
GL_API فراغ GL_APIENTRY glTexStorage2DEXT (GLenum موخه, GLsizei پوړونه, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
GL_API فراغ GL_APIENTRY glTexStorage3DEXT (GLenum موخه, GLsizei پوړونه, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2);
GL_API فراغ GL_APIENTRY glTextureStorage1DEXT (GLuint texture, GLenum موخه, GLsizei پوړونه, GLenum internalformat, GLsizei پلنوالی);
GL_API فراغ GL_APIENTRY glTextureStorage2DEXT (GLuint texture, GLenum موخه, GLsizei پوړونه, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
GL_API فراغ GL_APIENTRY glTextureStorage3DEXT (GLuint texture, GLenum موخه, GLsizei پوړونه, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2);
#د_که_پای
#د_که_پای /* GL_EXT_texture_storage */

#که_نه_تعریف_شوی GL_IMG_multisampled_render_منزل_texture
#تعریف_کړه GL_IMG_multisampled_render_منزل_texture 1
#تعریف_کړه GL_RENDERBUFFER_SAMPLES_IMG       0x9133
#تعریف_کړه GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_IMG 0x9134
#تعریف_کړه GL_MAX_SAMPLES_IMG                0x9135
#تعریف_کړه GL_TEXTURE_SAMPLES_IMG            0x9136
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEIMGPROC) (GLenum موخه, GLsizei samples, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEIMGPROC) (GLenum موخه, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glRenderbufferStorageMultisampleIMG (GLenum موخه, GLsizei samples, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
GL_API فراغ GL_APIENTRY glFramebufferTexture2DMultisampleIMG (GLenum موخه, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#د_که_پای
#د_که_پای /* GL_IMG_multisampled_render_to_texture */

#که_نه_تعریف_شوی GL_IMG_read_format
#تعریف_کړه GL_IMG_read_format 1
#تعریف_کړه GL_BGRA_IMG                       0x80E1
#تعریف_کړه GL_UNSIGNED_SHORT_4_4_4_4_REV_IMG 0x8365
#د_که_پای /* GL_IMG_read_format */

#که_نه_تعریف_شوی GL_IMG_texture_compression_pvrtc
#تعریف_کړه GL_IMG_texture_compression_pvrtc 1
#تعریف_کړه GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG 0x8C00
#تعریف_کړه GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG 0x8C01
#تعریف_کړه GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG 0x8C02
#تعریف_کړه GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG 0x8C03
#د_که_پای /* GL_IMG_texture_compression_pvrtc */

#که_نه_تعریف_شوی GL_IMG_texture_env_enhanced_fixed_function
#تعریف_کړه GL_IMG_texture_env_enhanced_fixed_function 1
#تعریف_کړه GL_MODULATE_COLOR_IMG             0x8C04
#تعریف_کړه GL_RECIP_جمع_کړه_SIGNED_ALPHA_IMG     0x8C05
#تعریف_کړه GL_TEXTURE_ALPHA_MODULATE_IMG     0x8C06
#تعریف_کړه GL_ضریب_ALPHA_MODULATE_IMG      0x8C07
#تعریف_کړه GL_FRAGMENT_ALPHA_MODULATE_IMG    0x8C08
#تعریف_کړه GL_جمع_کړه_BLEND_IMG                  0x8C09
#تعریف_کړه GL_DOT3_RGBA_IMG                  0x86AF
#د_که_پای /* GL_IMG_texture_env_enhanced_fixed_function */

#که_نه_تعریف_شوی GL_IMG_user_clip_plane
#تعریف_کړه GL_IMG_user_clip_plane 1
#تعریف_کړه GL_CLIP_PLANE0_IMG                0x3000
#تعریف_کړه GL_CLIP_PLANE1_IMG                0x3001
#تعریف_کړه GL_CLIP_PLANE2_IMG                0x3002
#تعریف_کړه GL_CLIP_PLANE3_IMG                0x3003
#تعریف_کړه GL_CLIP_PLANE4_IMG                0x3004
#تعریف_کړه GL_CLIP_PLANE5_IMG                0x3005
#تعریف_کړه GL_MAX_CLIP_PLANES_IMG            0x0D32
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLIPPLANEFIMGPROC) (GLenum p, ثابت GLfloat *eqn);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLIPPLANEXIMGPROC) (GLenum p, ثابت GLfixed *eqn);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glClipPlanefIMG (GLenum p, ثابت GLfloat *eqn);
GL_API فراغ GL_APIENTRY glClipPlanexIMG (GLenum p, ثابت GLfixed *eqn);
#د_که_پای
#د_که_پای /* GL_IMG_user_clip_plane */

#که_نه_تعریف_شوی GL_NV_fence
#تعریف_کړه GL_NV_fence 1
#تعریف_کړه GL_ALL_COMPLETED_NV               0x84F2
#تعریف_کړه GL_FENCE_حالت_NV                0x84F3
#تعریف_کړه GL_FENCE_CONDITION_NV             0x84F4
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEFENCESNVPROC) (GLsizei n, ثابت GLuint *fences);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENFENCESNVPROC) (GLsizei n, GLuint *fences);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISFENCENVPROC) (GLuint fence);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLTESTFENCENVPROC) (GLuint fence);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFENCEIVNVPROC) (GLuint fence, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFINISHFENCENVPROC) (GLuint fence);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSETFENCENVPROC) (GLuint fence, GLenum condition);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glDeleteFencesNV (GLsizei n, ثابت GLuint *fences);
GL_API فراغ GL_APIENTRY glGenFencesNV (GLsizei n, GLuint *fences);
GL_API GLboolean GL_APIENTRY glIsFenceNV (GLuint fence);
GL_API GLboolean GL_APIENTRY glTestFenceNV (GLuint fence);
GL_API فراغ GL_APIENTRY glGetFenceivNV (GLuint fence, GLenum pname, GLint *params);
GL_API فراغ GL_APIENTRY gl_پای_Fence_NV (GLuint fence);
GL_API فراغ GL_APIENTRY gl_سېټ_Fence_NV (GLuint fence, GLenum condition);
#د_که_پای
#د_که_پای /* GL_NV_fence */

#که_نه_تعریف_شوی GL_QCOM_driver_control
#تعریف_کړه GL_QCOM_driver_control 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETDRIVERCONTROLSQCOMPROC) (GLint *عدد, GLsizei اندازه, GLuint *driverControls);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETDRIVERCONTROLSTRINGQCOMPROC) (GLuint driverControl, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLchar *driverControlString);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glGetDriverControlsQCOM (GLint *عدد, GLsizei اندازه, GLuint *driverControls);
GL_API فراغ GL_APIENTRY glGetDriverControlStringQCOM (GLuint driverControl, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLchar *driverControlString);
GL_API فراغ GL_APIENTRY glEnableDriverControlQCOM (GLuint driverControl);
GL_API فراغ GL_APIENTRY glDisableDriverControlQCOM (GLuint driverControl);
#د_که_پای
#د_که_پای /* GL_QCOM_driver_control */

#که_نه_تعریف_شوی GL_QCOM_extended_get
#تعریف_کړه GL_QCOM_extended_get 1
#تعریف_کړه GL_TEXTURE_پلنوالی_QCOM             0x8BD2
#تعریف_کړه GL_TEXTURE_لوړوالی_QCOM            0x8BD3
#تعریف_کړه GL_TEXTURE_ژوروالی_QCOM             0x8BD4
#تعریف_کړه GL_TEXTURE_دننی_FORMAT_QCOM   0x8BD5
#تعریف_کړه GL_TEXTURE_FORMAT_QCOM            0x8BD6
#تعریف_کړه GL_TEXTURE_TYPE_QCOM              0x8BD7
#تعریف_کړه GL_TEXTURE_IMAGE_VALID_QCOM       0x8BD8
#تعریف_کړه GL_TEXTURE_عدد_پوړونه_QCOM        0x8BD9
#تعریف_کړه GL_TEXTURE_موخه_QCOM            0x8BDA
#تعریف_کړه GL_TEXTURE_OBJECT_VALID_QCOM      0x8BDB
#تعریف_کړه GL_STATE_RESTORE                  0x8BDC
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETTEXTURESQCOMPROC) (GLuint *textures, GLint maxTextures, GLint *عدد_Textures);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETBUFFERSQCOMPROC) (GLuint *buffers, GLint maxBuffers, GLint *عدد_Buffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETRENDERBUFFERSQCOMPROC) (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *عدد_Renderbuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETFRAMEBUFFERSQCOMPROC) (GLuint *framebuffers, GLint maxFramebuffers, GLint *عدد_Framebuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETTEXLEVELPARAMETERIVQCOMPROC) (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTTEXOBJECTSTATEOVERRIDEIQCOMPROC) (GLenum موخه, GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETTEXSUBIMAGEQCOMPROC) (GLenum موخه, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLenum format, GLenum type, فراغ *texels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETBUFFERPOINTERVQCOMPROC) (GLenum موخه, فراغ **params);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glExtGetTexturesQCOM (GLuint *textures, GLint maxTextures, GLint *عدد_Textures);
GL_API فراغ GL_APIENTRY glExtGetBuffersQCOM (GLuint *buffers, GLint maxBuffers, GLint *عدد_Buffers);
GL_API فراغ GL_APIENTRY glExtGetRenderbuffersQCOM (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *عدد_Renderbuffers);
GL_API فراغ GL_APIENTRY glExtGetFramebuffersQCOM (GLuint *framebuffers, GLint maxFramebuffers, GLint *عدد_Framebuffers);
GL_API فراغ GL_APIENTRY glExtGetTexLevelParameterivQCOM (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
GL_API فراغ GL_APIENTRY glExtTexObjectStateOverrideiQCOM (GLenum موخه, GLenum pname, GLint param);
GL_API فراغ GL_APIENTRY glExtGetTexSubImageQCOM (GLenum موخه, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLenum format, GLenum type, فراغ *texels);
GL_API فراغ GL_APIENTRY gl_Ext_Get_بفر_Pointerv_QCOM (GLenum موخه, فراغ **params);
#د_که_پای
#د_که_پای /* GL_QCOM_extended_get */

#که_نه_تعریف_شوی GL_QCOM_extended_get2
#تعریف_کړه GL_QCOM_extended_get2 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETSHADERSQCOMPROC) (GLuint *shaders, GLint maxShaders, GLint *عدد_Shaders);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETPROGRAMSQCOMPROC) (GLuint *programs, GLint maxPrograms, GLint *عدد_Programs);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLEXTISPROGRAMBINARYQCOMPROC) (GLuint پروګرام);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETPROGRAMBINARYSOURCEQCOMPROC) (GLuint پروګرام, GLenum shadertype, GLchar *سرچینه, GLint *اوږدتیا);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glExtGetShadersQCOM (GLuint *shaders, GLint maxShaders, GLint *عدد_Shaders);
GL_API فراغ GL_APIENTRY glExtGetProgramsQCOM (GLuint *programs, GLint maxPrograms, GLint *عدد_Programs);
GL_API GLboolean GL_APIENTRY gl_Ext_Is_پروګرام_دوګونی_QCOM (GLuint پروګرام);
GL_API فراغ GL_APIENTRY gl_Ext_Get_پروګرام_دوګونی_سرچینه_QCOM (GLuint پروګرام, GLenum shadertype, GLchar *سرچینه, GLint *اوږدتیا);
#د_که_پای
#د_که_پای /* GL_QCOM_extended_get2 */

#که_نه_تعریف_شوی GL_QCOM_perfmon_global_ډېرپېښ
#تعریف_کړه GL_QCOM_perfmon_global_ډېرپېښ 1
#تعریف_کړه GL_PERFMON_GLOBAL_ډېرپېښ_QCOM       0x8FA0
#د_که_پای /* GL_QCOM_perfmon_global_mode */

#که_نه_تعریف_شوی GL_QCOM_tiled_rendering
#تعریف_کړه GL_QCOM_tiled_rendering 1
#تعریف_کړه GL_COLOR_بفر_BIT0_QCOM         0x00000001
#تعریف_کړه GL_COLOR_بفر_BIT1_QCOM         0x00000002
#تعریف_کړه GL_COLOR_بفر_BIT2_QCOM         0x00000004
#تعریف_کړه GL_COLOR_بفر_BIT3_QCOM         0x00000008
#تعریف_کړه GL_COLOR_بفر_BIT4_QCOM         0x00000010
#تعریف_کړه GL_COLOR_بفر_BIT5_QCOM         0x00000020
#تعریف_کړه GL_COLOR_بفر_BIT6_QCOM         0x00000040
#تعریف_کړه GL_COLOR_بفر_BIT7_QCOM         0x00000080
#تعریف_کړه GL_ژوروالی_بفر_BIT0_QCOM         0x00000100
#تعریف_کړه GL_ژوروالی_بفر_BIT1_QCOM         0x00000200
#تعریف_کړه GL_ژوروالی_بفر_BIT2_QCOM         0x00000400
#تعریف_کړه GL_ژوروالی_بفر_BIT3_QCOM         0x00000800
#تعریف_کړه GL_ژوروالی_بفر_BIT4_QCOM         0x00001000
#تعریف_کړه GL_ژوروالی_بفر_BIT5_QCOM         0x00002000
#تعریف_کړه GL_ژوروالی_بفر_BIT6_QCOM         0x00004000
#تعریف_کړه GL_ژوروالی_بفر_BIT7_QCOM         0x00008000
#تعریف_کړه GL_STENCIL_بفر_BIT0_QCOM       0x00010000
#تعریف_کړه GL_STENCIL_بفر_BIT1_QCOM       0x00020000
#تعریف_کړه GL_STENCIL_بفر_BIT2_QCOM       0x00040000
#تعریف_کړه GL_STENCIL_بفر_BIT3_QCOM       0x00080000
#تعریف_کړه GL_STENCIL_بفر_BIT4_QCOM       0x00100000
#تعریف_کړه GL_STENCIL_بفر_BIT5_QCOM       0x00200000
#تعریف_کړه GL_STENCIL_بفر_BIT6_QCOM       0x00400000
#تعریف_کړه GL_STENCIL_بفر_BIT7_QCOM       0x00800000
#تعریف_کړه GL_MULTISAMPLE_بفر_BIT0_QCOM   0x01000000
#تعریف_کړه GL_MULTISAMPLE_بفر_BIT1_QCOM   0x02000000
#تعریف_کړه GL_MULTISAMPLE_بفر_BIT2_QCOM   0x04000000
#تعریف_کړه GL_MULTISAMPLE_بفر_BIT3_QCOM   0x08000000
#تعریف_کړه GL_MULTISAMPLE_بفر_BIT4_QCOM   0x10000000
#تعریف_کړه GL_MULTISAMPLE_بفر_BIT5_QCOM   0x20000000
#تعریف_کړه GL_MULTISAMPLE_بفر_BIT6_QCOM   0x40000000
#تعریف_کړه GL_MULTISAMPLE_بفر_BIT7_QCOM   0x80000000
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTARTTILINGQCOMPROC) (GLuint x, GLuint y, GLuint پلنوالی, GLuint لوړوالی, GLbitfield preserve_ماسک);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENDTILINGQCOMPROC) (GLbitfield preserve_ماسک);
#که_تعریف_شوی GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY gl_پیل_Tiling_QCOM (GLuint x, GLuint y, GLuint پلنوالی, GLuint لوړوالی, GLbitfield preserve_ماسک);
GL_API فراغ GL_APIENTRY gl_پای_ټکی_Tiling_QCOM (GLbitfield preserve_ماسک);
#د_که_پای
#د_که_پای /* GL_QCOM_tiled_rendering */

#که_نه_تعریف_شوی GL_QCOM_writeonly_rendering
#تعریف_کړه GL_QCOM_writeonly_rendering 1
#تعریف_کړه GL_WRITEONLY_RENDERING_QCOM       0x8823
#د_که_پای /* GL_QCOM_writeonly_rendering */

#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای
