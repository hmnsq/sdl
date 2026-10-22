#اگر_غیر_تعریف_شدہ __gles1_glext_h_
#تعریف_کرو __gles1_glext_h_ 1

#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم

/*
** Copyright 2013-2026 The Khronos Group Inc.
** SPDX-License-Identifier: MIT
**
** This header is generated from the Khronos OpenGL / OpenGL ES XML
** API Registry. The current version of the Registry, generator scripts
** used to make the header, and the header can be found at
**   https://github.com/KhronosGroup/OpenGL-Registry
*/

#اگر_غیر_تعریف_شدہ GL_APIENTRYP
#تعریف_کرو GL_APIENTRYP GL_APIENTRY*
#اگر_ختم

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

#اگر_غیر_تعریف_شدہ GL_KHR_debug
#تعریف_کرو GL_KHR_debug 1
#اگر_ختم /* GL_KHR_debug */

#اگر_غیر_تعریف_شدہ GL_OES_EGL_image
#تعریف_کرو GL_OES_EGL_image 1
قسمتعریف خالی *GLeglImageOES;
قسمتعریف خالی (GL_APIENTRYP PFNGLEGLIMAGETARGETTEXTURE2DOESPROC) (GLenum ہدف, GLeglImageOES image);
قسمتعریف خالی (GL_APIENTRYP PFNGLEGLIMAGETARGETRENDERBUFFERSTORAGEOESPROC) (GLenum ہدف, GLeglImageOES image);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API خالی GL_APIENTRY gl_EGLImage_ہدف_Texture2_DOES (GLenum ہدف, GLeglImageOES image);
GL_API خالی GL_APIENTRY gl_EGLImage_ہدف_Renderbuffer_Storage_OES (GLenum ہدف, GLeglImageOES image);
#اگر_ختم
#اگر_ختم /* GL_OES_EGL_image */

#اگر_غیر_تعریف_شدہ GL_OES_EGL_image_external
#تعریف_کرو GL_OES_EGL_image_external 1
#تعریف_کرو GL_TEXTURE_EXTERNAL_OES           0x8D65
#تعریف_کرو GL_TEXTURE_BINDING_EXTERNAL_OES   0x8D67
#تعریف_کرو GL_REQUIRED_TEXTURE_IMAGE_UNITS_OES 0x8D68
#اگر_ختم /* GL_OES_EGL_image_external */

#اگر_غیر_تعریف_شدہ GL_OES_blend_equation_separate
#تعریف_کرو GL_OES_blend_equation_separate 1
#تعریف_کرو GL_BLEND_EQUATION_RGB_OES         0x8009
#تعریف_کرو GL_BLEND_EQUATION_ALPHA_OES       0x883D
قسمتعریف خالی (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEOESPROC) (GLenum منوال_RGB, GLenum منوال_Alpha);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API خالی GL_APIENTRY glBlendEquationSeparateOES (GLenum منوال_RGB, GLenum منوال_Alpha);
#اگر_ختم
#اگر_ختم /* GL_OES_blend_equation_separate */

#اگر_غیر_تعریف_شدہ GL_OES_blend_func_separate
#تعریف_کرو GL_OES_blend_func_separate 1
#تعریف_کرو GL_BLEND_DST_RGB_OES              0x80C8
#تعریف_کرو GL_BLEND_SRC_RGB_OES              0x80C9
#تعریف_کرو GL_BLEND_DST_ALPHA_OES            0x80CA
#تعریف_کرو GL_BLEND_SRC_ALPHA_OES            0x80CB
قسمتعریف خالی (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEOESPROC) (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API خالی GL_APIENTRY glBlendFuncSeparateOES (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
#اگر_ختم
#اگر_ختم /* GL_OES_blend_func_separate */

#اگر_غیر_تعریف_شدہ GL_OES_blend_تفریق
#تعریف_کرو GL_OES_blend_تفریق 1
#تعریف_کرو GL_BLEND_EQUATION_OES             0x8009
#تعریف_کرو GL_FUNC_جوڑو_OES                   0x8006
#تعریف_کرو GL_FUNC_تفریق_OES              0x800A
#تعریف_کرو GL_FUNC_الٹ_تفریق_OES      0x800B
قسمتعریف خالی (GL_APIENTRYP PFNGLBLENDEQUATIONOESPROC) (GLenum منوال);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API خالی GL_APIENTRY glBlendEquationOES (GLenum منوال);
#اگر_ختم
#اگر_ختم /* GL_OES_blend_subtract */

#اگر_غیر_تعریف_شدہ GL_OES_byte_coordinates
#تعریف_کرو GL_OES_byte_coordinates 1
#اگر_ختم /* GL_OES_byte_coordinates */

#اگر_غیر_تعریف_شدہ GL_OES_compressed_ETC1_RGB8_sub_texture
#تعریف_کرو GL_OES_compressed_ETC1_RGB8_sub_texture 1
#اگر_ختم /* GL_OES_compressed_ETC1_RGB8_sub_texture */

#اگر_غیر_تعریف_شدہ GL_OES_compressed_ETC1_RGB8_texture
#تعریف_کرو GL_OES_compressed_ETC1_RGB8_texture 1
#تعریف_کرو GL_ETC1_RGB8_OES                  0x8D64
#اگر_ختم /* GL_OES_compressed_ETC1_RGB8_texture */

#اگر_غیر_تعریف_شدہ GL_OES_depth24
#تعریف_کرو GL_OES_depth24 1
#تعریف_کرو GL_گہرائی_COMPONENT24_OES          0x81A6
#اگر_ختم /* GL_OES_depth24 */

#اگر_غیر_تعریف_شدہ GL_OES_depth32
#تعریف_کرو GL_OES_depth32 1
#تعریف_کرو GL_گہرائی_COMPONENT32_OES          0x81A7
#اگر_ختم /* GL_OES_depth32 */

#اگر_غیر_تعریف_شدہ GL_OES_draw_texture
#تعریف_کرو GL_OES_draw_texture 1
#تعریف_کرو GL_TEXTURE_CROP_RECT_OES          0x8B9D
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWTEXSOESPROC) (GLshort x, GLshort y, GLshort z, GLshort چوڑائی, GLshort اونچائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWTEXIOESPROC) (GLint x, GLint y, GLint z, GLint چوڑائی, GLint اونچائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWTEXXOESPROC) (GLfixed x, GLfixed y, GLfixed z, GLfixed چوڑائی, GLfixed اونچائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWTEXSVOESPROC) (ثابت GLshort *coords);
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWTEXIVOESPROC) (ثابت GLint *coords);
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWTEXXVOESPROC) (ثابت GLfixed *coords);
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWTEXFOESPROC) (GLfloat x, GLfloat y, GLfloat z, GLfloat چوڑائی, GLfloat اونچائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWTEXFVOESPROC) (ثابت GLfloat *coords);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API خالی GL_APIENTRY glDrawTexsOES (GLshort x, GLshort y, GLshort z, GLshort چوڑائی, GLshort اونچائی);
GL_API خالی GL_APIENTRY glDrawTexiOES (GLint x, GLint y, GLint z, GLint چوڑائی, GLint اونچائی);
GL_API خالی GL_APIENTRY glDrawTexxOES (GLfixed x, GLfixed y, GLfixed z, GLfixed چوڑائی, GLfixed اونچائی);
GL_API خالی GL_APIENTRY glDrawTexsvOES (ثابت GLshort *coords);
GL_API خالی GL_APIENTRY glDrawTexivOES (ثابت GLint *coords);
GL_API خالی GL_APIENTRY glDrawTexxvOES (ثابت GLfixed *coords);
GL_API خالی GL_APIENTRY glDrawTexfOES (GLfloat x, GLfloat y, GLfloat z, GLfloat چوڑائی, GLfloat اونچائی);
GL_API خالی GL_APIENTRY glDrawTexfvOES (ثابت GLfloat *coords);
#اگر_ختم
#اگر_ختم /* GL_OES_draw_texture */

#اگر_غیر_تعریف_شدہ GL_OES_element_اشاریہ_uint
#تعریف_کرو GL_OES_element_اشاریہ_uint 1
#تعریف_کرو GL_UNSIGNED_INT                   0x1405
#اگر_ختم /* GL_OES_element_index_uint */

#اگر_غیر_تعریف_شدہ GL_OES_extended_میٹرکس_palette
#تعریف_کرو GL_OES_extended_میٹرکس_palette 1
#اگر_ختم /* GL_OES_extended_matrix_palette */

#اگر_غیر_تعریف_شدہ GL_OES_fbo_render_mipmap
#تعریف_کرو GL_OES_fbo_render_mipmap 1
#اگر_ختم /* GL_OES_fbo_render_mipmap */

#اگر_غیر_تعریف_شدہ GL_OES_fixed_نقطہ
#تعریف_کرو GL_OES_fixed_نقطہ 1
#تعریف_کرو GL_FIXED_OES                      0x140C
قسمتعریف خالی (GL_APIENTRYP PFNGLALPHAFUNCXOESPROC) (GLenum func, GLfixed ref);
قسمتعریف خالی (GL_APIENTRYP PFNGLCLEARCOLORXOESPROC) (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
قسمتعریف خالی (GL_APIENTRYP PFNGLCLEARDEPTHXOESPROC) (GLfixed گہرائی_2);
قسمتعریف خالی (GL_APIENTRYP PFNGLCLIPPLANEXOESPROC) (GLenum plane, ثابت GLfixed *equation);
قسمتعریف خالی (GL_APIENTRYP PFNGLCOLOR4XOESPROC) (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
قسمتعریف خالی (GL_APIENTRYP PFNGLDEPTHRANGEXOESPROC) (GLfixed n, GLfixed f);
قسمتعریف خالی (GL_APIENTRYP PFNGLFOGXOESPROC) (GLenum pname, GLfixed param);
قسمتعریف خالی (GL_APIENTRYP PFNGLFOGXVOESPROC) (GLenum pname, ثابت GLfixed *param);
قسمتعریف خالی (GL_APIENTRYP PFNGLFRUSTUMXOESPROC) (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETCLIPPLANEXOESPROC) (GLenum plane, GLfixed *equation);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETFIXEDVOESPROC) (GLenum pname, GLfixed *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETTEXENVXVOESPROC) (GLenum ہدف, GLenum pname, GLfixed *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETTEXPARAMETERXVOESPROC) (GLenum ہدف, GLenum pname, GLfixed *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLLIGHTMODELXOESPROC) (GLenum pname, GLfixed param);
قسمتعریف خالی (GL_APIENTRYP PFNGLLIGHTMODELXVOESPROC) (GLenum pname, ثابت GLfixed *param);
قسمتعریف خالی (GL_APIENTRYP PFNGLLIGHTXOESPROC) (GLenum light, GLenum pname, GLfixed param);
قسمتعریف خالی (GL_APIENTRYP PFNGLLIGHTXVOESPROC) (GLenum light, GLenum pname, ثابت GLfixed *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLLINEWIDTHXOESPROC) (GLfixed چوڑائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLLOADMATRIXXOESPROC) (ثابت GLfixed *m);
قسمتعریف خالی (GL_APIENTRYP PFNGLMATERIALXOESPROC) (GLenum face, GLenum pname, GLfixed param);
قسمتعریف خالی (GL_APIENTRYP PFNGLMATERIALXVOESPROC) (GLenum face, GLenum pname, ثابت GLfixed *param);
قسمتعریف خالی (GL_APIENTRYP PFNGLMULTMATRIXXOESPROC) (ثابت GLfixed *m);
قسمتعریف خالی (GL_APIENTRYP PFNGLMULTITEXCOORD4XOESPROC) (GLenum texture, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
قسمتعریف خالی (GL_APIENTRYP PFNGLNORMAL3XOESPROC) (GLfixed nx, GLfixed ny, GLfixed nz);
قسمتعریف خالی (GL_APIENTRYP PFNGLORTHOXOESPROC) (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
قسمتعریف خالی (GL_APIENTRYP PFNGLPOINTPARAMETERXVOESPROC) (GLenum pname, ثابت GLfixed *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLPOINTSIZEXOESPROC) (GLfixed سائز);
قسمتعریف خالی (GL_APIENTRYP PFNGLPOLYGONOFFSETXOESPROC) (GLfixed ضربی_عدد, GLfixed units);
قسمتعریف خالی (GL_APIENTRYP PFNGLROTATEXOESPROC) (GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
قسمتعریف خالی (GL_APIENTRYP PFNGLSCALEXOESPROC) (GLfixed x, GLfixed y, GLfixed z);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXENVXOESPROC) (GLenum ہدف, GLenum pname, GLfixed param);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXENVXVOESPROC) (GLenum ہدف, GLenum pname, ثابت GLfixed *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXPARAMETERXOESPROC) (GLenum ہدف, GLenum pname, GLfixed param);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXPARAMETERXVOESPROC) (GLenum ہدف, GLenum pname, ثابت GLfixed *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLTRANSLATEXOESPROC) (GLfixed x, GLfixed y, GLfixed z);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETLIGHTXVOESPROC) (GLenum light, GLenum pname, GLfixed *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETMATERIALXVOESPROC) (GLenum face, GLenum pname, GLfixed *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLPOINTPARAMETERXOESPROC) (GLenum pname, GLfixed param);
قسمتعریف خالی (GL_APIENTRYP PFNGLSAMPLECOVERAGEXOESPROC) (GLclampx قدر, GLboolean invert);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETTEXGENXVOESPROC) (GLenum coord, GLenum pname, GLfixed *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXGENXOESPROC) (GLenum coord, GLenum pname, GLfixed param);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXGENXVOESPROC) (GLenum coord, GLenum pname, ثابت GLfixed *params);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API خالی GL_APIENTRY glAlphaFuncxOES (GLenum func, GLfixed ref);
GL_API خالی GL_APIENTRY glClearColorxOES (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GL_API خالی GL_APIENTRY glClearDepthxOES (GLfixed گہرائی_2);
GL_API خالی GL_APIENTRY glClipPlanexOES (GLenum plane, ثابت GLfixed *equation);
GL_API خالی GL_APIENTRY glColor4xOES (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GL_API خالی GL_APIENTRY gl_گہرائی_Rangex_OES (GLfixed n, GLfixed f);
GL_API خالی GL_APIENTRY glFogxOES (GLenum pname, GLfixed param);
GL_API خالی GL_APIENTRY glFogxvOES (GLenum pname, ثابت GLfixed *param);
GL_API خالی GL_APIENTRY glFrustumxOES (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
GL_API خالی GL_APIENTRY glGetClipPlanexOES (GLenum plane, GLfixed *equation);
GL_API خالی GL_APIENTRY glGetFixedvOES (GLenum pname, GLfixed *params);
GL_API خالی GL_APIENTRY glGetTexEnvxvOES (GLenum ہدف, GLenum pname, GLfixed *params);
GL_API خالی GL_APIENTRY glGetTexParameterxvOES (GLenum ہدف, GLenum pname, GLfixed *params);
GL_API خالی GL_APIENTRY glLightModelxOES (GLenum pname, GLfixed param);
GL_API خالی GL_APIENTRY glLightModelxvOES (GLenum pname, ثابت GLfixed *param);
GL_API خالی GL_APIENTRY glLightxOES (GLenum light, GLenum pname, GLfixed param);
GL_API خالی GL_APIENTRY glLightxvOES (GLenum light, GLenum pname, ثابت GLfixed *params);
GL_API خالی GL_APIENTRY gl_سطر_Widthx_OES (GLfixed چوڑائی);
GL_API خالی GL_APIENTRY gl_بھرو_Matrixx_OES (ثابت GLfixed *m);
GL_API خالی GL_APIENTRY glMaterialxOES (GLenum face, GLenum pname, GLfixed param);
GL_API خالی GL_APIENTRY glMaterialxvOES (GLenum face, GLenum pname, ثابت GLfixed *param);
GL_API خالی GL_APIENTRY glMultMatrixxOES (ثابت GLfixed *m);
GL_API خالی GL_APIENTRY glMultiTexCoord4xOES (GLenum texture, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
GL_API خالی GL_APIENTRY glNormal3xOES (GLfixed nx, GLfixed ny, GLfixed nz);
GL_API خالی GL_APIENTRY glOrthoxOES (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
GL_API خالی GL_APIENTRY gl_نقطہ_Parameterxv_OES (GLenum pname, ثابت GLfixed *params);
GL_API خالی GL_APIENTRY gl_نقطہ_Sizex_OES (GLfixed سائز);
GL_API خالی GL_APIENTRY glPolygonOffsetxOES (GLfixed ضربی_عدد, GLfixed units);
GL_API خالی GL_APIENTRY glRotatexOES (GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
GL_API خالی GL_APIENTRY glScalexOES (GLfixed x, GLfixed y, GLfixed z);
GL_API خالی GL_APIENTRY glTexEnvxOES (GLenum ہدف, GLenum pname, GLfixed param);
GL_API خالی GL_APIENTRY glTexEnvxvOES (GLenum ہدف, GLenum pname, ثابت GLfixed *params);
GL_API خالی GL_APIENTRY glTexParameterxOES (GLenum ہدف, GLenum pname, GLfixed param);
GL_API خالی GL_APIENTRY glTexParameterxvOES (GLenum ہدف, GLenum pname, ثابت GLfixed *params);
GL_API خالی GL_APIENTRY glTranslatexOES (GLfixed x, GLfixed y, GLfixed z);
GL_API خالی GL_APIENTRY glGetLightxvOES (GLenum light, GLenum pname, GLfixed *params);
GL_API خالی GL_APIENTRY glGetMaterialxvOES (GLenum face, GLenum pname, GLfixed *params);
GL_API خالی GL_APIENTRY gl_نقطہ_Parameterx_OES (GLenum pname, GLfixed param);
GL_API خالی GL_APIENTRY glSampleCoveragexOES (GLclampx قدر, GLboolean invert);
GL_API خالی GL_APIENTRY glGetTexGenxvOES (GLenum coord, GLenum pname, GLfixed *params);
GL_API خالی GL_APIENTRY glTexGenxOES (GLenum coord, GLenum pname, GLfixed param);
GL_API خالی GL_APIENTRY glTexGenxvOES (GLenum coord, GLenum pname, ثابت GLfixed *params);
#اگر_ختم
#اگر_ختم /* GL_OES_fixed_point */

#اگر_غیر_تعریف_شدہ GL_OES_framebuffer_object
#تعریف_کرو GL_OES_framebuffer_object 1
#تعریف_کرو GL_NONE_OES                       0
#تعریف_کرو GL_FRAMEBUFFER_OES                0x8D40
#تعریف_کرو GL_RENDERBUFFER_OES               0x8D41
#تعریف_کرو GL_RGBA4_OES                      0x8056
#تعریف_کرو GL_RGB5_A1_OES                    0x8057
#تعریف_کرو GL_RGB565_OES                     0x8D62
#تعریف_کرو GL_گہرائی_COMPONENT16_OES          0x81A5
#تعریف_کرو GL_RENDERBUFFER_چوڑائی_OES         0x8D42
#تعریف_کرو GL_RENDERBUFFER_اونچائی_OES        0x8D43
#تعریف_کرو GL_RENDERBUFFER_اندرونی_FORMAT_OES 0x8D44
#تعریف_کرو GL_RENDERBUFFER_RED_سائز_OES      0x8D50
#تعریف_کرو GL_RENDERBUFFER_GREEN_سائز_OES    0x8D51
#تعریف_کرو GL_RENDERBUFFER_BLUE_سائز_OES     0x8D52
#تعریف_کرو GL_RENDERBUFFER_ALPHA_سائز_OES    0x8D53
#تعریف_کرو GL_RENDERBUFFER_گہرائی_سائز_OES    0x8D54
#تعریف_کرو GL_RENDERBUFFER_STENCIL_سائز_OES  0x8D55
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_OES 0x8CD0
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_OES 0x8CD1
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_OES 0x8CD2
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_OES 0x8CD3
#تعریف_کرو GL_COLOR_ATTACHMENT0_OES          0x8CE0
#تعریف_کرو GL_گہرائی_ATTACHMENT_OES           0x8D00
#تعریف_کرو GL_STENCIL_ATTACHMENT_OES         0x8D20
#تعریف_کرو GL_FRAMEBUFFER_COMPLETE_OES       0x8CD5
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_OES 0x8CD6
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_OES 0x8CD7
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_OES 0x8CD9
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_FORMATS_OES 0x8CDA
#تعریف_کرو GL_FRAMEBUFFER_UNSUPPORTED_OES    0x8CDD
#تعریف_کرو GL_FRAMEBUFFER_BINDING_OES        0x8CA6
#تعریف_کرو GL_RENDERBUFFER_BINDING_OES       0x8CA7
#تعریف_کرو GL_MAX_RENDERBUFFER_سائز_OES      0x84E8
#تعریف_کرو GL_INVALID_FRAMEBUFFER_OPERATION_OES 0x0506
قسمتعریف GLboolean (GL_APIENTRYP PFNGLISRENDERBUFFEROESPROC) (GLuint renderbuffer);
قسمتعریف خالی (GL_APIENTRYP PFNGLBINDRENDERBUFFEROESPROC) (GLenum ہدف, GLuint renderbuffer);
قسمتعریف خالی (GL_APIENTRYP PFNGLDELETERENDERBUFFERSOESPROC) (GLsizei n, ثابت GLuint *renderbuffers);
قسمتعریف خالی (GL_APIENTRYP PFNGLGENRENDERBUFFERSOESPROC) (GLsizei n, GLuint *renderbuffers);
قسمتعریف خالی (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEOESPROC) (GLenum ہدف, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVOESPROC) (GLenum ہدف, GLenum pname, GLint *params);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLISFRAMEBUFFEROESPROC) (GLuint framebuffer);
قسمتعریف خالی (GL_APIENTRYP PFNGLBINDFRAMEBUFFEROESPROC) (GLenum ہدف, GLuint framebuffer);
قسمتعریف خالی (GL_APIENTRYP PFNGLDELETEFRAMEBUFFERSOESPROC) (GLsizei n, ثابت GLuint *framebuffers);
قسمتعریف خالی (GL_APIENTRYP PFNGLGENFRAMEBUFFERSOESPROC) (GLsizei n, GLuint *framebuffers);
قسمتعریف GLenum (GL_APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSOESPROC) (GLenum ہدف);
قسمتعریف خالی (GL_APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFEROESPROC) (GLenum ہدف, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
قسمتعریف خالی (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DOESPROC) (GLenum ہدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVOESPROC) (GLenum ہدف, GLenum attachment, GLenum pname, GLint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGENERATEMIPMAPOESPROC) (GLenum ہدف);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API GLboolean GL_APIENTRY glIsRenderbufferOES (GLuint renderbuffer);
GL_API خالی GL_APIENTRY glBindRenderbufferOES (GLenum ہدف, GLuint renderbuffer);
GL_API خالی GL_APIENTRY glDeleteRenderbuffersOES (GLsizei n, ثابت GLuint *renderbuffers);
GL_API خالی GL_APIENTRY glGenRenderbuffersOES (GLsizei n, GLuint *renderbuffers);
GL_API خالی GL_APIENTRY glRenderbufferStorageOES (GLenum ہدف, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
GL_API خالی GL_APIENTRY glGetRenderbufferParameterivOES (GLenum ہدف, GLenum pname, GLint *params);
GL_API GLboolean GL_APIENTRY glIsFramebufferOES (GLuint framebuffer);
GL_API خالی GL_APIENTRY glBindFramebufferOES (GLenum ہدف, GLuint framebuffer);
GL_API خالی GL_APIENTRY glDeleteFramebuffersOES (GLsizei n, ثابت GLuint *framebuffers);
GL_API خالی GL_APIENTRY glGenFramebuffersOES (GLsizei n, GLuint *framebuffers);
GL_API GLenum GL_APIENTRY gl_Check_Framebuffer_حالت_OES (GLenum ہدف);
GL_API خالی GL_APIENTRY glFramebufferRenderbufferOES (GLenum ہدف, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
GL_API خالی GL_APIENTRY glFramebufferTexture2DOES (GLenum ہدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GL_API خالی GL_APIENTRY glGetFramebufferAttachmentParameterivOES (GLenum ہدف, GLenum attachment, GLenum pname, GLint *params);
GL_API خالی GL_APIENTRY glGenerateMipmapOES (GLenum ہدف);
#اگر_ختم
#اگر_ختم /* GL_OES_framebuffer_object */

#اگر_غیر_تعریف_شدہ GL_OES_mapbuffer
#تعریف_کرو GL_OES_mapbuffer 1
#تعریف_کرو GL_WRITE_ONLY_OES                 0x88B9
#تعریف_کرو GL_بفر_ACCESS_OES              0x88BB
#تعریف_کرو GL_بفر_MAPPED_OES              0x88BC
#تعریف_کرو GL_بفر_MAP_اشارہ_گر_OES         0x88BD
قسمتعریف خالی *(GL_APIENTRYP PFNGLMAPBUFFEROESPROC) (GLenum ہدف, GLenum access);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLUNMAPBUFFEROESPROC) (GLenum ہدف);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETBUFFERPOINTERVOESPROC) (GLenum ہدف, GLenum pname, خالی **params);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API خالی *GL_APIENTRY gl_Map_بفر_OES (GLenum ہدف, GLenum access);
GL_API GLboolean GL_APIENTRY gl_Unmap_بفر_OES (GLenum ہدف);
GL_API خالی GL_APIENTRY gl_Get_بفر_Pointerv_OES (GLenum ہدف, GLenum pname, خالی **params);
#اگر_ختم
#اگر_ختم /* GL_OES_mapbuffer */

#اگر_غیر_تعریف_شدہ GL_OES_میٹرکس_get
#تعریف_کرو GL_OES_میٹرکس_get 1
#تعریف_کرو GL_MODELVIEW_میٹرکس_FLOAT_AS_INT_بٹ_OES 0x898D
#تعریف_کرو GL_PROJECTION_میٹرکس_FLOAT_AS_INT_بٹ_OES 0x898E
#تعریف_کرو GL_TEXTURE_میٹرکس_FLOAT_AS_INT_بٹ_OES 0x898F
#اگر_ختم /* GL_OES_matrix_get */

#اگر_غیر_تعریف_شدہ GL_OES_میٹرکس_palette
#تعریف_کرو GL_OES_میٹرکس_palette 1
#تعریف_کرو GL_MAX_راس_UNITS_OES           0x86A4
#تعریف_کرو GL_MAX_PALETTE_MATRICES_OES       0x8842
#تعریف_کرو GL_میٹرکس_PALETTE_OES             0x8840
#تعریف_کرو GL_میٹرکس_اشاریہ_ARRAY_OES         0x8844
#تعریف_کرو GL_وزن_ARRAY_OES               0x86AD
#تعریف_کرو GL_CURRENT_PALETTE_میٹرکس_OES     0x8843
#تعریف_کرو GL_میٹرکس_اشاریہ_ARRAY_سائز_OES    0x8846
#تعریف_کرو GL_میٹرکس_اشاریہ_ARRAY_TYPE_OES    0x8847
#تعریف_کرو GL_میٹرکس_اشاریہ_ARRAY_STRIDE_OES  0x8848
#تعریف_کرو GL_میٹرکس_اشاریہ_ARRAY_اشارہ_گر_OES 0x8849
#تعریف_کرو GL_میٹرکس_اشاریہ_ARRAY_بفر_BINDING_OES 0x8B9E
#تعریف_کرو GL_وزن_ARRAY_سائز_OES          0x86AB
#تعریف_کرو GL_وزن_ARRAY_TYPE_OES          0x86A9
#تعریف_کرو GL_وزن_ARRAY_STRIDE_OES        0x86AA
#تعریف_کرو GL_وزن_ARRAY_اشارہ_گر_OES       0x86AC
#تعریف_کرو GL_وزن_ARRAY_بفر_BINDING_OES 0x889E
قسمتعریف خالی (GL_APIENTRYP PFNGLCURRENTPALETTEMATRIXOESPROC) (GLuint matrixpaletteindex);
قسمتعریف خالی (GL_APIENTRYP PFNGLLOADPALETTEFROMMODELVIEWMATRIXOESPROC) (خالی);
قسمتعریف خالی (GL_APIENTRYP PFNGLMATRIXINDEXPOINTEROESPROC) (GLint سائز, GLenum type, GLsizei stride, ثابت خالی *اشارہ_گر_2);
قسمتعریف خالی (GL_APIENTRYP PFNGLWEIGHTPOINTEROESPROC) (GLint سائز, GLenum type, GLsizei stride, ثابت خالی *اشارہ_گر_2);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API خالی GL_APIENTRY gl_Current_Palette_میٹرکس_OES (GLuint matrixpaletteindex);
GL_API خالی GL_APIENTRY gl_بھرو_Palette_From_Model_View_میٹرکس_OES (خالی);
GL_API خالی GL_APIENTRY gl_میٹرکس_اشاریہ_اشارہ_گر_OES (GLint سائز, GLenum type, GLsizei stride, ثابت خالی *اشارہ_گر_2);
GL_API خالی GL_APIENTRY gl_وزن_اشارہ_گر_OES (GLint سائز, GLenum type, GLsizei stride, ثابت خالی *اشارہ_گر_2);
#اگر_ختم
#اگر_ختم /* GL_OES_matrix_palette */

#اگر_غیر_تعریف_شدہ GL_OES_packed_گہرائی_stencil
#تعریف_کرو GL_OES_packed_گہرائی_stencil 1
#تعریف_کرو GL_گہرائی_STENCIL_OES              0x84F9
#تعریف_کرو GL_UNSIGNED_INT_24_8_OES          0x84FA
#تعریف_کرو GL_DEPTH24_STENCIL8_OES           0x88F0
#اگر_ختم /* GL_OES_packed_depth_stencil */

#اگر_غیر_تعریف_شدہ GL_OES_query_میٹرکس
#تعریف_کرو GL_OES_query_میٹرکس 1
قسمتعریف GLbitfield (GL_APIENTRYP PFNGLQUERYMATRIXXOESPROC) (GLfixed *mantissa, GLint *exponent);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API GLbitfield GL_APIENTRY glQueryMatrixxOES (GLfixed *mantissa, GLint *exponent);
#اگر_ختم
#اگر_ختم /* GL_OES_query_matrix */

#اگر_غیر_تعریف_شدہ GL_OES_required_internalformat
#تعریف_کرو GL_OES_required_internalformat 1
#تعریف_کرو GL_ALPHA8_OES                     0x803C
#تعریف_کرو GL_LUMINANCE4_ALPHA4_OES          0x8043
#تعریف_کرو GL_LUMINANCE8_ALPHA8_OES          0x8045
#تعریف_کرو GL_LUMINANCE8_OES                 0x8040
#تعریف_کرو GL_RGB8_OES                       0x8051
#تعریف_کرو GL_RGBA8_OES                      0x8058
#تعریف_کرو GL_RGB10_EXT                      0x8052
#تعریف_کرو GL_RGB10_A2_EXT                   0x8059
#اگر_ختم /* GL_OES_required_internalformat */

#اگر_غیر_تعریف_شدہ GL_OES_rgb8_rgba8
#تعریف_کرو GL_OES_rgb8_rgba8 1
#اگر_ختم /* GL_OES_rgb8_rgba8 */

#اگر_غیر_تعریف_شدہ GL_OES_single_precision
#تعریف_کرو GL_OES_single_precision 1
قسمتعریف خالی (GL_APIENTRYP PFNGLCLEARDEPTHFOESPROC) (GLclampf گہرائی_2);
قسمتعریف خالی (GL_APIENTRYP PFNGLCLIPPLANEFOESPROC) (GLenum plane, ثابت GLfloat *equation);
قسمتعریف خالی (GL_APIENTRYP PFNGLDEPTHRANGEFOESPROC) (GLclampf n, GLclampf f);
قسمتعریف خالی (GL_APIENTRYP PFNGLFRUSTUMFOESPROC) (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETCLIPPLANEFOESPROC) (GLenum plane, GLfloat *equation);
قسمتعریف خالی (GL_APIENTRYP PFNGLORTHOFOESPROC) (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API خالی GL_APIENTRY glClearDepthfOES (GLclampf گہرائی_2);
GL_API خالی GL_APIENTRY glClipPlanefOES (GLenum plane, ثابت GLfloat *equation);
GL_API خالی GL_APIENTRY gl_گہرائی_Rangef_OES (GLclampf n, GLclampf f);
GL_API خالی GL_APIENTRY glFrustumfOES (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
GL_API خالی GL_APIENTRY glGetClipPlanefOES (GLenum plane, GLfloat *equation);
GL_API خالی GL_APIENTRY glOrthofOES (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
#اگر_ختم
#اگر_ختم /* GL_OES_single_precision */

#اگر_غیر_تعریف_شدہ GL_OES_stencil1
#تعریف_کرو GL_OES_stencil1 1
#تعریف_کرو GL_STENCIL_INDEX1_OES             0x8D46
#اگر_ختم /* GL_OES_stencil1 */

#اگر_غیر_تعریف_شدہ GL_OES_stencil4
#تعریف_کرو GL_OES_stencil4 1
#تعریف_کرو GL_STENCIL_INDEX4_OES             0x8D47
#اگر_ختم /* GL_OES_stencil4 */

#اگر_غیر_تعریف_شدہ GL_OES_stencil8
#تعریف_کرو GL_OES_stencil8 1
#تعریف_کرو GL_STENCIL_INDEX8_OES             0x8D48
#اگر_ختم /* GL_OES_stencil8 */

#اگر_غیر_تعریف_شدہ GL_OES_stencil_wrap
#تعریف_کرو GL_OES_stencil_wrap 1
#تعریف_کرو GL_INCR_WRAP_OES                  0x8507
#تعریف_کرو GL_DECR_WRAP_OES                  0x8508
#اگر_ختم /* GL_OES_stencil_wrap */

#اگر_غیر_تعریف_شدہ GL_OES_surfaceless_context
#تعریف_کرو GL_OES_surfaceless_context 1
#تعریف_کرو GL_FRAMEBUFFER_UNDEFINED_OES      0x8219
#اگر_ختم /* GL_OES_surfaceless_context */

#اگر_غیر_تعریف_شدہ GL_OES_texture_cube_map
#تعریف_کرو GL_OES_texture_cube_map 1
#تعریف_کرو GL_معمول_MAP_OES                 0x8511
#تعریف_کرو GL_REFLECTION_MAP_OES             0x8512
#تعریف_کرو GL_TEXTURE_CUBE_MAP_OES           0x8513
#تعریف_کرو GL_TEXTURE_BINDING_CUBE_MAP_OES   0x8514
#تعریف_کرو GL_TEXTURE_CUBE_MAP_مثبت_X_OES 0x8515
#تعریف_کرو GL_TEXTURE_CUBE_MAP_NEGATIVE_X_OES 0x8516
#تعریف_کرو GL_TEXTURE_CUBE_MAP_مثبت_Y_OES 0x8517
#تعریف_کرو GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_OES 0x8518
#تعریف_کرو GL_TEXTURE_CUBE_MAP_مثبت_Z_OES 0x8519
#تعریف_کرو GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_OES 0x851A
#تعریف_کرو GL_MAX_CUBE_MAP_TEXTURE_سائز_OES  0x851C
#تعریف_کرو GL_TEXTURE_GEN_منوال_OES           0x2500
#تعریف_کرو GL_TEXTURE_GEN_STR_OES            0x8D60
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXGENFOESPROC) (GLenum coord, GLenum pname, GLfloat param);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXGENFVOESPROC) (GLenum coord, GLenum pname, ثابت GLfloat *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXGENIOESPROC) (GLenum coord, GLenum pname, GLint param);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXGENIVOESPROC) (GLenum coord, GLenum pname, ثابت GLint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETTEXGENFVOESPROC) (GLenum coord, GLenum pname, GLfloat *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETTEXGENIVOESPROC) (GLenum coord, GLenum pname, GLint *params);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API خالی GL_APIENTRY glTexGenfOES (GLenum coord, GLenum pname, GLfloat param);
GL_API خالی GL_APIENTRY glTexGenfvOES (GLenum coord, GLenum pname, ثابت GLfloat *params);
GL_API خالی GL_APIENTRY glTexGeniOES (GLenum coord, GLenum pname, GLint param);
GL_API خالی GL_APIENTRY glTexGenivOES (GLenum coord, GLenum pname, ثابت GLint *params);
GL_API خالی GL_APIENTRY glGetTexGenfvOES (GLenum coord, GLenum pname, GLfloat *params);
GL_API خالی GL_APIENTRY glGetTexGenivOES (GLenum coord, GLenum pname, GLint *params);
#اگر_ختم
#اگر_ختم /* GL_OES_texture_cube_map */

#اگر_غیر_تعریف_شدہ GL_OES_texture_env_crossbar
#تعریف_کرو GL_OES_texture_env_crossbar 1
#اگر_ختم /* GL_OES_texture_env_crossbar */

#اگر_غیر_تعریف_شدہ GL_OES_texture_mirrored_repeat
#تعریف_کرو GL_OES_texture_mirrored_repeat 1
#تعریف_کرو GL_MIRRORED_REPEAT_OES            0x8370
#اگر_ختم /* GL_OES_texture_mirrored_repeat */

#اگر_غیر_تعریف_شدہ GL_OES_texture_npot
#تعریف_کرو GL_OES_texture_npot 1
#اگر_ختم /* GL_OES_texture_npot */

#اگر_غیر_تعریف_شدہ GL_OES_راس_array_object
#تعریف_کرو GL_OES_راس_array_object 1
#تعریف_کرو GL_راس_ARRAY_BINDING_OES       0x85B5
قسمتعریف خالی (GL_APIENTRYP PFNGLBINDVERTEXARRAYOESPROC) (GLuint array);
قسمتعریف خالی (GL_APIENTRYP PFNGLDELETEVERTEXARRAYSOESPROC) (GLsizei n, ثابت GLuint *arrays);
قسمتعریف خالی (GL_APIENTRYP PFNGLGENVERTEXARRAYSOESPROC) (GLsizei n, GLuint *arrays);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLISVERTEXARRAYOESPROC) (GLuint array);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API خالی GL_APIENTRY gl_Bind_راس_Array_OES (GLuint array);
GL_API خالی GL_APIENTRY gl_Delete_راس_Arrays_OES (GLsizei n, ثابت GLuint *arrays);
GL_API خالی GL_APIENTRY gl_Gen_راس_Arrays_OES (GLsizei n, GLuint *arrays);
GL_API GLboolean GL_APIENTRY gl_Is_راس_Array_OES (GLuint array);
#اگر_ختم
#اگر_ختم /* GL_OES_vertex_array_object */

#اگر_غیر_تعریف_شدہ GL_AMD_compressed_3DC_texture
#تعریف_کرو GL_AMD_compressed_3DC_texture 1
#تعریف_کرو GL_3DC_X_AMD                      0x87F9
#تعریف_کرو GL_3DC_XY_AMD                     0x87FA
#اگر_ختم /* GL_AMD_compressed_3DC_texture */

#اگر_غیر_تعریف_شدہ GL_AMD_compressed_ATC_texture
#تعریف_کرو GL_AMD_compressed_ATC_texture 1
#تعریف_کرو GL_ATC_RGB_AMD                    0x8C92
#تعریف_کرو GL_ATC_RGBA_EXPLICIT_ALPHA_AMD    0x8C93
#تعریف_کرو GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD 0x87EE
#اگر_ختم /* GL_AMD_compressed_ATC_texture */

#اگر_غیر_تعریف_شدہ GL_APPLE_copy_texture_سطحیں
#تعریف_کرو GL_APPLE_copy_texture_سطحیں 1
قسمتعریف خالی (GL_APIENTRYP PFNGLCOPYTEXTURELEVELSAPPLEPROC) (GLuint destinationTexture, GLuint ماخذ_Texture, GLint ماخذ_بنیاد_Level, GLsizei ماخذ_Level_گنتی);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API خالی GL_APIENTRY gl_Copy_Texture_سطحیں_APPLE (GLuint destinationTexture, GLuint ماخذ_Texture, GLint ماخذ_بنیاد_Level, GLsizei ماخذ_Level_گنتی);
#اگر_ختم
#اگر_ختم /* GL_APPLE_copy_texture_levels */

#اگر_غیر_تعریف_شدہ GL_APPLE_framebuffer_multisample
#تعریف_کرو GL_APPLE_framebuffer_multisample 1
#تعریف_کرو GL_RENDERBUFFER_SAMPLES_APPLE     0x8CAB
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_APPLE 0x8D56
#تعریف_کرو GL_MAX_SAMPLES_APPLE              0x8D57
#تعریف_کرو GL_READ_FRAMEBUFFER_APPLE         0x8CA8
#تعریف_کرو GL_DRAW_FRAMEBUFFER_APPLE         0x8CA9
#تعریف_کرو GL_DRAW_FRAMEBUFFER_BINDING_APPLE 0x8CA6
#تعریف_کرو GL_READ_FRAMEBUFFER_BINDING_APPLE 0x8CAA
قسمتعریف خالی (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEAPPLEPROC) (GLenum ہدف, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLRESOLVEMULTISAMPLEFRAMEBUFFERAPPLEPROC) (خالی);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API خالی GL_APIENTRY glRenderbufferStorageMultisampleAPPLE (GLenum ہدف, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
GL_API خالی GL_APIENTRY glResolveMultisampleFramebufferAPPLE (خالی);
#اگر_ختم
#اگر_ختم /* GL_APPLE_framebuffer_multisample */

#اگر_غیر_تعریف_شدہ GL_APPLE_sync
#تعریف_کرو GL_APPLE_sync 1
قسمتعریف ساخت __GLsync *GLsync;
قسمتعریف khronos_uint64_t GLuint64;
قسمتعریف khronos_int64_t GLint64;
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
قسمتعریف GLsync (GL_APIENTRYP PFNGLFENCESYNCAPPLEPROC) (GLenum condition, GLbitfield flags);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLISSYNCAPPLEPROC) (GLsync sync);
قسمتعریف خالی (GL_APIENTRYP PFNGLDELETESYNCAPPLEPROC) (GLsync sync);
قسمتعریف GLenum (GL_APIENTRYP PFNGLCLIENTWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
قسمتعریف خالی (GL_APIENTRYP PFNGLWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETINTEGER64VAPPLEPROC) (GLenum pname, GLint64 *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETSYNCIVAPPLEPROC) (GLsync sync, GLenum pname, GLsizei گنتی, GLsizei *لمبائی, GLint *اقدار);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API GLsync GL_APIENTRY glFenceSyncAPPLE (GLenum condition, GLbitfield flags);
GL_API GLboolean GL_APIENTRY glIsSyncAPPLE (GLsync sync);
GL_API خالی GL_APIENTRY glDeleteSyncAPPLE (GLsync sync);
GL_API GLenum GL_APIENTRY glClientWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_API خالی GL_APIENTRY glWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_API خالی GL_APIENTRY glGetInteger64vAPPLE (GLenum pname, GLint64 *params);
GL_API خالی GL_APIENTRY glGetSyncivAPPLE (GLsync sync, GLenum pname, GLsizei گنتی, GLsizei *لمبائی, GLint *اقدار);
#اگر_ختم
#اگر_ختم /* GL_APPLE_sync */

#اگر_غیر_تعریف_شدہ GL_APPLE_texture_2D_limited_npot
#تعریف_کرو GL_APPLE_texture_2D_limited_npot 1
#اگر_ختم /* GL_APPLE_texture_2D_limited_npot */

#اگر_غیر_تعریف_شدہ GL_APPLE_texture_format_BGRA8888
#تعریف_کرو GL_APPLE_texture_format_BGRA8888 1
#تعریف_کرو GL_BGRA_EXT                       0x80E1
#تعریف_کرو GL_BGRA8_EXT                      0x93A1
#اگر_ختم /* GL_APPLE_texture_format_BGRA8888 */

#اگر_غیر_تعریف_شدہ GL_APPLE_texture_max_level
#تعریف_کرو GL_APPLE_texture_max_level 1
#تعریف_کرو GL_TEXTURE_MAX_LEVEL_APPLE        0x813D
#اگر_ختم /* GL_APPLE_texture_max_level */

#اگر_غیر_تعریف_شدہ GL_ARM_rgba8
#تعریف_کرو GL_ARM_rgba8 1
#اگر_ختم /* GL_ARM_rgba8 */

#اگر_غیر_تعریف_شدہ GL_EXT_blend_minmax
#تعریف_کرو GL_EXT_blend_minmax 1
#تعریف_کرو GL_MIN_EXT                        0x8007
#تعریف_کرو GL_MAX_EXT                        0x8008
#اگر_ختم /* GL_EXT_blend_minmax */

#اگر_غیر_تعریف_شدہ GL_EXT_debug_marker
#تعریف_کرو GL_EXT_debug_marker 1
قسمتعریف حرف GLchar;
قسمتعریف خالی (GL_APIENTRYP PFNGLINSERTEVENTMARKEREXTPROC) (GLsizei لمبائی, ثابت GLchar *marker);
قسمتعریف خالی (GL_APIENTRYP PFNGLPUSHGROUPMARKEREXTPROC) (GLsizei لمبائی, ثابت GLchar *marker);
قسمتعریف خالی (GL_APIENTRYP PFNGLPOPGROUPMARKEREXTPROC) (خالی);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API خالی GL_APIENTRY gl_داخل_کرو_Event_Marker_EXT (GLsizei لمبائی, ثابت GLchar *marker);
GL_API خالی GL_APIENTRY gl_ڈالو_گروہ_Marker_EXT (GLsizei لمبائی, ثابت GLchar *marker);
GL_API خالی GL_APIENTRY gl_نکالو_گروہ_Marker_EXT (خالی);
#اگر_ختم
#اگر_ختم /* GL_EXT_debug_marker */

#اگر_غیر_تعریف_شدہ GL_EXT_discard_framebuffer
#تعریف_کرو GL_EXT_discard_framebuffer 1
#تعریف_کرو GL_COLOR_EXT                      0x1800
#تعریف_کرو GL_گہرائی_EXT                      0x1801
#تعریف_کرو GL_STENCIL_EXT                    0x1802
قسمتعریف خالی (GL_APIENTRYP PFNGLDISCARDFRAMEBUFFEREXTPROC) (GLenum ہدف, GLsizei عدد_Attachments, ثابت GLenum *attachments);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API خالی GL_APIENTRY glDiscardFramebufferEXT (GLenum ہدف, GLsizei عدد_Attachments, ثابت GLenum *attachments);
#اگر_ختم
#اگر_ختم /* GL_EXT_discard_framebuffer */

#اگر_غیر_تعریف_شدہ GL_EXT_map_بفر_range
#تعریف_کرو GL_EXT_map_بفر_range 1
#تعریف_کرو GL_MAP_READ_ثنائی_ہندسہ_EXT               0x0001
#تعریف_کرو GL_MAP_WRITE_ثنائی_ہندسہ_EXT              0x0002
#تعریف_کرو GL_MAP_INVALIDATE_RANGE_ثنائی_ہندسہ_EXT   0x0004
#تعریف_کرو GL_MAP_INVALIDATE_بفر_ثنائی_ہندسہ_EXT  0x0008
#تعریف_کرو GL_MAP_FLUSH_EXPLICIT_ثنائی_ہندسہ_EXT     0x0010
#تعریف_کرو GL_MAP_UNSYNCHRONIZED_ثنائی_ہندسہ_EXT     0x0020
قسمتعریف خالی *(GL_APIENTRYP PFNGLMAPBUFFERRANGEEXTPROC) (GLenum ہدف, GLintptr انحراف_2, GLsizeiptr لمبائی, GLbitfield access);
قسمتعریف خالی (GL_APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEEXTPROC) (GLenum ہدف, GLintptr انحراف_2, GLsizeiptr لمبائی);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API خالی *GL_APIENTRY gl_Map_بفر_Range_EXT (GLenum ہدف, GLintptr انحراف_2, GLsizeiptr لمبائی, GLbitfield access);
GL_API خالی GL_APIENTRY gl_Flush_Mapped_بفر_Range_EXT (GLenum ہدف, GLintptr انحراف_2, GLsizeiptr لمبائی);
#اگر_ختم
#اگر_ختم /* GL_EXT_map_buffer_range */

#اگر_غیر_تعریف_شدہ GL_EXT_multi_draw_arrays
#تعریف_کرو GL_EXT_multi_draw_arrays 1
قسمتعریف خالی (GL_APIENTRYP PFNGLMULTIDRAWARRAYSEXTPROC) (GLenum منوال, ثابت GLint *پہلا, ثابت GLsizei *گنتی, GLsizei primcount);
قسمتعریف خالی (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSEXTPROC) (GLenum منوال, ثابت GLsizei *گنتی, GLenum type, ثابت خالی *ثابت*indices, GLsizei primcount);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API خالی GL_APIENTRY glMultiDrawArraysEXT (GLenum منوال, ثابت GLint *پہلا, ثابت GLsizei *گنتی, GLsizei primcount);
GL_API خالی GL_APIENTRY glMultiDrawElementsEXT (GLenum منوال, ثابت GLsizei *گنتی, GLenum type, ثابت خالی *ثابت*indices, GLsizei primcount);
#اگر_ختم
#اگر_ختم /* GL_EXT_multi_draw_arrays */

#اگر_غیر_تعریف_شدہ GL_EXT_multisampled_render_مقصد_texture
#تعریف_کرو GL_EXT_multisampled_render_مقصد_texture 1
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SAMPLES_EXT 0x8D6C
#تعریف_کرو GL_RENDERBUFFER_SAMPLES_EXT       0x8CAB
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT 0x8D56
#تعریف_کرو GL_MAX_SAMPLES_EXT                0x8D57
قسمتعریف خالی (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) (GLenum ہدف, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEEXTPROC) (GLenum ہدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API خالی GL_APIENTRY glRenderbufferStorageMultisampleEXT (GLenum ہدف, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
GL_API خالی GL_APIENTRY glFramebufferTexture2DMultisampleEXT (GLenum ہدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#اگر_ختم
#اگر_ختم /* GL_EXT_multisampled_render_to_texture */

#اگر_غیر_تعریف_شدہ GL_EXT_read_format_bgra
#تعریف_کرو GL_EXT_read_format_bgra 1
#تعریف_کرو GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT 0x8365
#تعریف_کرو GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT 0x8366
#اگر_ختم /* GL_EXT_read_format_bgra */

#اگر_غیر_تعریف_شدہ GL_EXT_robustness
#تعریف_کرو GL_EXT_robustness 1
#تعریف_کرو GL_GUILTY_CONTEXT_RESET_EXT       0x8253
#تعریف_کرو GL_INNOCENT_CONTEXT_RESET_EXT     0x8254
#تعریف_کرو GL_UNKNOWN_CONTEXT_RESET_EXT      0x8255
#تعریف_کرو GL_CONTEXT_ROBUST_ACCESS_EXT      0x90F3
#تعریف_کرو GL_RESET_NOTIFICATION_STRATEGY_EXT 0x8256
#تعریف_کرو GL_LOSE_CONTEXT_ON_RESET_EXT      0x8252
#تعریف_کرو GL_NO_RESET_NOTIFICATION_EXT      0x8261
قسمتعریف GLenum (GL_APIENTRYP PFNGLGETGRAPHICSRESETSTATUSEXTPROC) (خالی);
قسمتعریف خالی (GL_APIENTRYP PFNGLREADNPIXELSEXTPROC) (GLint x, GLint y, GLsizei چوڑائی, GLsizei اونچائی, GLenum format, GLenum type, GLsizei buf_سائز, خالی *ڈیٹا);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETNUNIFORMFVEXTPROC) (GLuint پروگرام, GLint location, GLsizei buf_سائز, GLfloat *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETNUNIFORMIVEXTPROC) (GLuint پروگرام, GLint location, GLsizei buf_سائز, GLint *params);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API GLenum GL_APIENTRY gl_Get_Graphics_Reset_حالت_EXT (خالی);
GL_API خالی GL_APIENTRY glReadnPixelsEXT (GLint x, GLint y, GLsizei چوڑائی, GLsizei اونچائی, GLenum format, GLenum type, GLsizei buf_سائز, خالی *ڈیٹا);
GL_API خالی GL_APIENTRY glGetnUniformfvEXT (GLuint پروگرام, GLint location, GLsizei buf_سائز, GLfloat *params);
GL_API خالی GL_APIENTRY glGetnUniformivEXT (GLuint پروگرام, GLint location, GLsizei buf_سائز, GLint *params);
#اگر_ختم
#اگر_ختم /* GL_EXT_robustness */

#اگر_غیر_تعریف_شدہ GL_EXT_sRGB
#تعریف_کرو GL_EXT_sRGB 1
#تعریف_کرو GL_SRGB_EXT                       0x8C40
#تعریف_کرو GL_SRGB_ALPHA_EXT                 0x8C42
#تعریف_کرو GL_SRGB8_ALPHA8_EXT               0x8C43
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING_EXT 0x8210
#اگر_ختم /* GL_EXT_sRGB */

#اگر_غیر_تعریف_شدہ GL_EXT_texture_compression_dxt1
#تعریف_کرو GL_EXT_texture_compression_dxt1 1
#تعریف_کرو GL_COMPRESSED_RGB_S3TC_DXT1_EXT   0x83F0
#تعریف_کرو GL_COMPRESSED_RGBA_S3TC_DXT1_EXT  0x83F1
#اگر_ختم /* GL_EXT_texture_compression_dxt1 */

#اگر_غیر_تعریف_شدہ GL_EXT_texture_filter_anisotropic
#تعریف_کرو GL_EXT_texture_filter_anisotropic 1
#تعریف_کرو GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#تعریف_کرو GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#اگر_ختم /* GL_EXT_texture_filter_anisotropic */

#اگر_غیر_تعریف_شدہ GL_EXT_texture_format_BGRA8888
#تعریف_کرو GL_EXT_texture_format_BGRA8888 1
#اگر_ختم /* GL_EXT_texture_format_BGRA8888 */

#اگر_غیر_تعریف_شدہ GL_EXT_texture_lod_bias
#تعریف_کرو GL_EXT_texture_lod_bias 1
#تعریف_کرو GL_MAX_TEXTURE_LOD_BIAS_EXT       0x84FD
#تعریف_کرو GL_TEXTURE_FILTER_CONTROL_EXT     0x8500
#تعریف_کرو GL_TEXTURE_LOD_BIAS_EXT           0x8501
#اگر_ختم /* GL_EXT_texture_lod_bias */

#اگر_غیر_تعریف_شدہ GL_EXT_texture_storage
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
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXSTORAGE1DEXTPROC) (GLenum ہدف, GLsizei سطحیں, GLenum internalformat, GLsizei چوڑائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXSTORAGE2DEXTPROC) (GLenum ہدف, GLsizei سطحیں, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXSTORAGE3DEXTPROC) (GLenum ہدف, GLsizei سطحیں, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXTURESTORAGE1DEXTPROC) (GLuint texture, GLenum ہدف, GLsizei سطحیں, GLenum internalformat, GLsizei چوڑائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXTURESTORAGE2DEXTPROC) (GLuint texture, GLenum ہدف, GLsizei سطحیں, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXTURESTORAGE3DEXTPROC) (GLuint texture, GLenum ہدف, GLsizei سطحیں, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API خالی GL_APIENTRY glTexStorage1DEXT (GLenum ہدف, GLsizei سطحیں, GLenum internalformat, GLsizei چوڑائی);
GL_API خالی GL_APIENTRY glTexStorage2DEXT (GLenum ہدف, GLsizei سطحیں, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
GL_API خالی GL_APIENTRY glTexStorage3DEXT (GLenum ہدف, GLsizei سطحیں, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2);
GL_API خالی GL_APIENTRY glTextureStorage1DEXT (GLuint texture, GLenum ہدف, GLsizei سطحیں, GLenum internalformat, GLsizei چوڑائی);
GL_API خالی GL_APIENTRY glTextureStorage2DEXT (GLuint texture, GLenum ہدف, GLsizei سطحیں, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
GL_API خالی GL_APIENTRY glTextureStorage3DEXT (GLuint texture, GLenum ہدف, GLsizei سطحیں, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2);
#اگر_ختم
#اگر_ختم /* GL_EXT_texture_storage */

#اگر_غیر_تعریف_شدہ GL_IMG_multisampled_render_مقصد_texture
#تعریف_کرو GL_IMG_multisampled_render_مقصد_texture 1
#تعریف_کرو GL_RENDERBUFFER_SAMPLES_IMG       0x9133
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_IMG 0x9134
#تعریف_کرو GL_MAX_SAMPLES_IMG                0x9135
#تعریف_کرو GL_TEXTURE_SAMPLES_IMG            0x9136
قسمتعریف خالی (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEIMGPROC) (GLenum ہدف, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEIMGPROC) (GLenum ہدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API خالی GL_APIENTRY glRenderbufferStorageMultisampleIMG (GLenum ہدف, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
GL_API خالی GL_APIENTRY glFramebufferTexture2DMultisampleIMG (GLenum ہدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#اگر_ختم
#اگر_ختم /* GL_IMG_multisampled_render_to_texture */

#اگر_غیر_تعریف_شدہ GL_IMG_read_format
#تعریف_کرو GL_IMG_read_format 1
#تعریف_کرو GL_BGRA_IMG                       0x80E1
#تعریف_کرو GL_UNSIGNED_SHORT_4_4_4_4_REV_IMG 0x8365
#اگر_ختم /* GL_IMG_read_format */

#اگر_غیر_تعریف_شدہ GL_IMG_texture_compression_pvrtc
#تعریف_کرو GL_IMG_texture_compression_pvrtc 1
#تعریف_کرو GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG 0x8C00
#تعریف_کرو GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG 0x8C01
#تعریف_کرو GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG 0x8C02
#تعریف_کرو GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG 0x8C03
#اگر_ختم /* GL_IMG_texture_compression_pvrtc */

#اگر_غیر_تعریف_شدہ GL_IMG_texture_env_enhanced_fixed_function
#تعریف_کرو GL_IMG_texture_env_enhanced_fixed_function 1
#تعریف_کرو GL_MODULATE_COLOR_IMG             0x8C04
#تعریف_کرو GL_RECIP_جوڑو_SIGNED_ALPHA_IMG     0x8C05
#تعریف_کرو GL_TEXTURE_ALPHA_MODULATE_IMG     0x8C06
#تعریف_کرو GL_ضربی_عدد_ALPHA_MODULATE_IMG      0x8C07
#تعریف_کرو GL_FRAGMENT_ALPHA_MODULATE_IMG    0x8C08
#تعریف_کرو GL_جوڑو_BLEND_IMG                  0x8C09
#تعریف_کرو GL_DOT3_RGBA_IMG                  0x86AF
#اگر_ختم /* GL_IMG_texture_env_enhanced_fixed_function */

#اگر_غیر_تعریف_شدہ GL_IMG_user_clip_plane
#تعریف_کرو GL_IMG_user_clip_plane 1
#تعریف_کرو GL_CLIP_PLANE0_IMG                0x3000
#تعریف_کرو GL_CLIP_PLANE1_IMG                0x3001
#تعریف_کرو GL_CLIP_PLANE2_IMG                0x3002
#تعریف_کرو GL_CLIP_PLANE3_IMG                0x3003
#تعریف_کرو GL_CLIP_PLANE4_IMG                0x3004
#تعریف_کرو GL_CLIP_PLANE5_IMG                0x3005
#تعریف_کرو GL_MAX_CLIP_PLANES_IMG            0x0D32
قسمتعریف خالی (GL_APIENTRYP PFNGLCLIPPLANEFIMGPROC) (GLenum p, ثابت GLfloat *eqn);
قسمتعریف خالی (GL_APIENTRYP PFNGLCLIPPLANEXIMGPROC) (GLenum p, ثابت GLfixed *eqn);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API خالی GL_APIENTRY glClipPlanefIMG (GLenum p, ثابت GLfloat *eqn);
GL_API خالی GL_APIENTRY glClipPlanexIMG (GLenum p, ثابت GLfixed *eqn);
#اگر_ختم
#اگر_ختم /* GL_IMG_user_clip_plane */

#اگر_غیر_تعریف_شدہ GL_NV_fence
#تعریف_کرو GL_NV_fence 1
#تعریف_کرو GL_ALL_COMPLETED_NV               0x84F2
#تعریف_کرو GL_FENCE_حالت_NV                0x84F3
#تعریف_کرو GL_FENCE_CONDITION_NV             0x84F4
قسمتعریف خالی (GL_APIENTRYP PFNGLDELETEFENCESNVPROC) (GLsizei n, ثابت GLuint *fences);
قسمتعریف خالی (GL_APIENTRYP PFNGLGENFENCESNVPROC) (GLsizei n, GLuint *fences);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLISFENCENVPROC) (GLuint fence);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLTESTFENCENVPROC) (GLuint fence);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETFENCEIVNVPROC) (GLuint fence, GLenum pname, GLint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLFINISHFENCENVPROC) (GLuint fence);
قسمتعریف خالی (GL_APIENTRYP PFNGLSETFENCENVPROC) (GLuint fence, GLenum condition);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API خالی GL_APIENTRY glDeleteFencesNV (GLsizei n, ثابت GLuint *fences);
GL_API خالی GL_APIENTRY glGenFencesNV (GLsizei n, GLuint *fences);
GL_API GLboolean GL_APIENTRY glIsFenceNV (GLuint fence);
GL_API GLboolean GL_APIENTRY glTestFenceNV (GLuint fence);
GL_API خالی GL_APIENTRY glGetFenceivNV (GLuint fence, GLenum pname, GLint *params);
GL_API خالی GL_APIENTRY gl_اختتام_Fence_NV (GLuint fence);
GL_API خالی GL_APIENTRY gl_سیٹ_Fence_NV (GLuint fence, GLenum condition);
#اگر_ختم
#اگر_ختم /* GL_NV_fence */

#اگر_غیر_تعریف_شدہ GL_QCOM_driver_control
#تعریف_کرو GL_QCOM_driver_control 1
قسمتعریف خالی (GL_APIENTRYP PFNGLGETDRIVERCONTROLSQCOMPROC) (GLint *عدد, GLsizei سائز, GLuint *driverControls);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETDRIVERCONTROLSTRINGQCOMPROC) (GLuint driverControl, GLsizei buf_سائز, GLsizei *لمبائی, GLchar *driverControlString);
قسمتعریف خالی (GL_APIENTRYP PFNGLENABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
قسمتعریف خالی (GL_APIENTRYP PFNGLDISABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API خالی GL_APIENTRY glGetDriverControlsQCOM (GLint *عدد, GLsizei سائز, GLuint *driverControls);
GL_API خالی GL_APIENTRY glGetDriverControlStringQCOM (GLuint driverControl, GLsizei buf_سائز, GLsizei *لمبائی, GLchar *driverControlString);
GL_API خالی GL_APIENTRY glEnableDriverControlQCOM (GLuint driverControl);
GL_API خالی GL_APIENTRY glDisableDriverControlQCOM (GLuint driverControl);
#اگر_ختم
#اگر_ختم /* GL_QCOM_driver_control */

#اگر_غیر_تعریف_شدہ GL_QCOM_extended_get
#تعریف_کرو GL_QCOM_extended_get 1
#تعریف_کرو GL_TEXTURE_چوڑائی_QCOM             0x8BD2
#تعریف_کرو GL_TEXTURE_اونچائی_QCOM            0x8BD3
#تعریف_کرو GL_TEXTURE_گہرائی_QCOM             0x8BD4
#تعریف_کرو GL_TEXTURE_اندرونی_FORMAT_QCOM   0x8BD5
#تعریف_کرو GL_TEXTURE_FORMAT_QCOM            0x8BD6
#تعریف_کرو GL_TEXTURE_TYPE_QCOM              0x8BD7
#تعریف_کرو GL_TEXTURE_IMAGE_VALID_QCOM       0x8BD8
#تعریف_کرو GL_TEXTURE_عدد_سطحیں_QCOM        0x8BD9
#تعریف_کرو GL_TEXTURE_ہدف_QCOM            0x8BDA
#تعریف_کرو GL_TEXTURE_OBJECT_VALID_QCOM      0x8BDB
#تعریف_کرو GL_STATE_RESTORE                  0x8BDC
قسمتعریف خالی (GL_APIENTRYP PFNGLEXTGETTEXTURESQCOMPROC) (GLuint *textures, GLint maxTextures, GLint *عدد_Textures);
قسمتعریف خالی (GL_APIENTRYP PFNGLEXTGETBUFFERSQCOMPROC) (GLuint *buffers, GLint maxBuffers, GLint *عدد_Buffers);
قسمتعریف خالی (GL_APIENTRYP PFNGLEXTGETRENDERBUFFERSQCOMPROC) (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *عدد_Renderbuffers);
قسمتعریف خالی (GL_APIENTRYP PFNGLEXTGETFRAMEBUFFERSQCOMPROC) (GLuint *framebuffers, GLint maxFramebuffers, GLint *عدد_Framebuffers);
قسمتعریف خالی (GL_APIENTRYP PFNGLEXTGETTEXLEVELPARAMETERIVQCOMPROC) (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLEXTTEXOBJECTSTATEOVERRIDEIQCOMPROC) (GLenum ہدف, GLenum pname, GLint param);
قسمتعریف خالی (GL_APIENTRYP PFNGLEXTGETTEXSUBIMAGEQCOMPROC) (GLenum ہدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLenum format, GLenum type, خالی *texels);
قسمتعریف خالی (GL_APIENTRYP PFNGLEXTGETBUFFERPOINTERVQCOMPROC) (GLenum ہدف, خالی **params);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API خالی GL_APIENTRY glExtGetTexturesQCOM (GLuint *textures, GLint maxTextures, GLint *عدد_Textures);
GL_API خالی GL_APIENTRY glExtGetBuffersQCOM (GLuint *buffers, GLint maxBuffers, GLint *عدد_Buffers);
GL_API خالی GL_APIENTRY glExtGetRenderbuffersQCOM (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *عدد_Renderbuffers);
GL_API خالی GL_APIENTRY glExtGetFramebuffersQCOM (GLuint *framebuffers, GLint maxFramebuffers, GLint *عدد_Framebuffers);
GL_API خالی GL_APIENTRY glExtGetTexLevelParameterivQCOM (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
GL_API خالی GL_APIENTRY glExtTexObjectStateOverrideiQCOM (GLenum ہدف, GLenum pname, GLint param);
GL_API خالی GL_APIENTRY glExtGetTexSubImageQCOM (GLenum ہدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLenum format, GLenum type, خالی *texels);
GL_API خالی GL_APIENTRY gl_Ext_Get_بفر_Pointerv_QCOM (GLenum ہدف, خالی **params);
#اگر_ختم
#اگر_ختم /* GL_QCOM_extended_get */

#اگر_غیر_تعریف_شدہ GL_QCOM_extended_get2
#تعریف_کرو GL_QCOM_extended_get2 1
قسمتعریف خالی (GL_APIENTRYP PFNGLEXTGETSHADERSQCOMPROC) (GLuint *shaders, GLint maxShaders, GLint *عدد_Shaders);
قسمتعریف خالی (GL_APIENTRYP PFNGLEXTGETPROGRAMSQCOMPROC) (GLuint *programs, GLint maxPrograms, GLint *عدد_Programs);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLEXTISPROGRAMBINARYQCOMPROC) (GLuint پروگرام);
قسمتعریف خالی (GL_APIENTRYP PFNGLEXTGETPROGRAMBINARYSOURCEQCOMPROC) (GLuint پروگرام, GLenum shadertype, GLchar *ماخذ, GLint *لمبائی);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API خالی GL_APIENTRY glExtGetShadersQCOM (GLuint *shaders, GLint maxShaders, GLint *عدد_Shaders);
GL_API خالی GL_APIENTRY glExtGetProgramsQCOM (GLuint *programs, GLint maxPrograms, GLint *عدد_Programs);
GL_API GLboolean GL_APIENTRY gl_Ext_Is_پروگرام_ثنائی_QCOM (GLuint پروگرام);
GL_API خالی GL_APIENTRY gl_Ext_Get_پروگرام_ثنائی_ماخذ_QCOM (GLuint پروگرام, GLenum shadertype, GLchar *ماخذ, GLint *لمبائی);
#اگر_ختم
#اگر_ختم /* GL_QCOM_extended_get2 */

#اگر_غیر_تعریف_شدہ GL_QCOM_perfmon_global_منوال
#تعریف_کرو GL_QCOM_perfmon_global_منوال 1
#تعریف_کرو GL_PERFMON_GLOBAL_منوال_QCOM       0x8FA0
#اگر_ختم /* GL_QCOM_perfmon_global_mode */

#اگر_غیر_تعریف_شدہ GL_QCOM_tiled_rendering
#تعریف_کرو GL_QCOM_tiled_rendering 1
#تعریف_کرو GL_COLOR_بفر_BIT0_QCOM         0x00000001
#تعریف_کرو GL_COLOR_بفر_BIT1_QCOM         0x00000002
#تعریف_کرو GL_COLOR_بفر_BIT2_QCOM         0x00000004
#تعریف_کرو GL_COLOR_بفر_BIT3_QCOM         0x00000008
#تعریف_کرو GL_COLOR_بفر_BIT4_QCOM         0x00000010
#تعریف_کرو GL_COLOR_بفر_BIT5_QCOM         0x00000020
#تعریف_کرو GL_COLOR_بفر_BIT6_QCOM         0x00000040
#تعریف_کرو GL_COLOR_بفر_BIT7_QCOM         0x00000080
#تعریف_کرو GL_گہرائی_بفر_BIT0_QCOM         0x00000100
#تعریف_کرو GL_گہرائی_بفر_BIT1_QCOM         0x00000200
#تعریف_کرو GL_گہرائی_بفر_BIT2_QCOM         0x00000400
#تعریف_کرو GL_گہرائی_بفر_BIT3_QCOM         0x00000800
#تعریف_کرو GL_گہرائی_بفر_BIT4_QCOM         0x00001000
#تعریف_کرو GL_گہرائی_بفر_BIT5_QCOM         0x00002000
#تعریف_کرو GL_گہرائی_بفر_BIT6_QCOM         0x00004000
#تعریف_کرو GL_گہرائی_بفر_BIT7_QCOM         0x00008000
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
قسمتعریف خالی (GL_APIENTRYP PFNGLSTARTTILINGQCOMPROC) (GLuint x, GLuint y, GLuint چوڑائی, GLuint اونچائی, GLbitfield preserve_نقاب);
قسمتعریف خالی (GL_APIENTRYP PFNGLENDTILINGQCOMPROC) (GLbitfield preserve_نقاب);
#اگر_تعریف_شدہ GL_GLEXT_PROTOTYPES
GL_API خالی GL_APIENTRY gl_آغاز_Tiling_QCOM (GLuint x, GLuint y, GLuint چوڑائی, GLuint اونچائی, GLbitfield preserve_نقاب);
GL_API خالی GL_APIENTRY gl_انتہا_Tiling_QCOM (GLbitfield preserve_نقاب);
#اگر_ختم
#اگر_ختم /* GL_QCOM_tiled_rendering */

#اگر_غیر_تعریف_شدہ GL_QCOM_writeonly_rendering
#تعریف_کرو GL_QCOM_writeonly_rendering 1
#تعریف_کرو GL_WRITEONLY_RENDERING_QCOM       0x8823
#اگر_ختم /* GL_QCOM_writeonly_rendering */

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم
