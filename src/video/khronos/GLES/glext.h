#جيڪڏهن_وصف_نه_ٿيل __gles1_glext_h_
#وصف_ڪريو __gles1_glext_h_ 1

#جيڪڏهن_وصف_ٿيل __cplusplus
خارجي "C" {
#جيڪڏهن_پورو

/*
** Copyright 2013-2026 The Khronos Group Inc.
** SPDX-License-Identifier: MIT
**
** This header is generated from the Khronos OpenGL / OpenGL ES XML
** API Registry. The current version of the Registry, generator scripts
** used to make the header, and the header can be found at
**   https://github.com/KhronosGroup/OpenGL-Registry
*/

#جيڪڏهن_وصف_نه_ٿيل GL_APIENTRYP
#وصف_ڪريو GL_APIENTRYP GL_APIENTRY*
#جيڪڏهن_پورو

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

#جيڪڏهن_وصف_نه_ٿيل GL_KHR_debug
#وصف_ڪريو GL_KHR_debug 1
#جيڪڏهن_پورو /* GL_KHR_debug */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_EGL_image
#وصف_ڪريو GL_OES_EGL_image 1
تعريفنوع فراغ *GLeglImageOES;
تعريفنوع فراغ (GL_APIENTRYP PFNGLEGLIMAGETARGETTEXTURE2DOESPROC) (GLenum هدف, GLeglImageOES image);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEGLIMAGETARGETRENDERBUFFERSTORAGEOESPROC) (GLenum هدف, GLeglImageOES image);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY gl_EGLImage_هدف_Texture2_DOES (GLenum هدف, GLeglImageOES image);
GL_API فراغ GL_APIENTRY gl_EGLImage_هدف_Renderbuffer_Storage_OES (GLenum هدف, GLeglImageOES image);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_OES_EGL_image */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_EGL_image_external
#وصف_ڪريو GL_OES_EGL_image_external 1
#وصف_ڪريو GL_TEXTURE_EXTERNAL_OES           0x8D65
#وصف_ڪريو GL_TEXTURE_BINDING_EXTERNAL_OES   0x8D67
#وصف_ڪريو GL_REQUIRED_TEXTURE_IMAGE_UNITS_OES 0x8D68
#جيڪڏهن_پورو /* GL_OES_EGL_image_external */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_blend_equation_separate
#وصف_ڪريو GL_OES_blend_equation_separate 1
#وصف_ڪريو GL_BLEND_EQUATION_RGB_OES         0x8009
#وصف_ڪريو GL_BLEND_EQUATION_ALPHA_OES       0x883D
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEOESPROC) (GLenum گهڻائي_RGB, GLenum گهڻائي_Alpha);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glBlendEquationSeparateOES (GLenum گهڻائي_RGB, GLenum گهڻائي_Alpha);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_OES_blend_equation_separate */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_blend_func_separate
#وصف_ڪريو GL_OES_blend_func_separate 1
#وصف_ڪريو GL_BLEND_DST_RGB_OES              0x80C8
#وصف_ڪريو GL_BLEND_SRC_RGB_OES              0x80C9
#وصف_ڪريو GL_BLEND_DST_ALPHA_OES            0x80CA
#وصف_ڪريو GL_BLEND_SRC_ALPHA_OES            0x80CB
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEOESPROC) (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glBlendFuncSeparateOES (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_OES_blend_func_separate */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_blend_ڪٽيو
#وصف_ڪريو GL_OES_blend_ڪٽيو 1
#وصف_ڪريو GL_BLEND_EQUATION_OES             0x8009
#وصف_ڪريو GL_FUNC_جوڙيو_OES                   0x8006
#وصف_ڪريو GL_FUNC_ڪٽيو_OES              0x800A
#وصف_ڪريو GL_FUNC_ابتو_ڪٽيو_OES      0x800B
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONOESPROC) (GLenum گهڻائي);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glBlendEquationOES (GLenum گهڻائي);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_OES_blend_subtract */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_byte_coordinates
#وصف_ڪريو GL_OES_byte_coordinates 1
#جيڪڏهن_پورو /* GL_OES_byte_coordinates */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_compressed_ETC1_RGB8_sub_texture
#وصف_ڪريو GL_OES_compressed_ETC1_RGB8_sub_texture 1
#جيڪڏهن_پورو /* GL_OES_compressed_ETC1_RGB8_sub_texture */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_compressed_ETC1_RGB8_texture
#وصف_ڪريو GL_OES_compressed_ETC1_RGB8_texture 1
#وصف_ڪريو GL_ETC1_RGB8_OES                  0x8D64
#جيڪڏهن_پورو /* GL_OES_compressed_ETC1_RGB8_texture */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_depth24
#وصف_ڪريو GL_OES_depth24 1
#وصف_ڪريو GL_اونهائي_COMPONENT24_OES          0x81A6
#جيڪڏهن_پورو /* GL_OES_depth24 */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_depth32
#وصف_ڪريو GL_OES_depth32 1
#وصف_ڪريو GL_اونهائي_COMPONENT32_OES          0x81A7
#جيڪڏهن_پورو /* GL_OES_depth32 */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_draw_texture
#وصف_ڪريو GL_OES_draw_texture 1
#وصف_ڪريو GL_TEXTURE_CROP_RECT_OES          0x8B9D
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXSOESPROC) (GLshort x, GLshort y, GLshort z, GLshort ويڪر, GLshort اوچائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXIOESPROC) (GLint x, GLint y, GLint z, GLint ويڪر, GLint اوچائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXXOESPROC) (GLfixed x, GLfixed y, GLfixed z, GLfixed ويڪر, GLfixed اوچائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXSVOESPROC) (ثابت GLshort *coords);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXIVOESPROC) (ثابت GLint *coords);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXXVOESPROC) (ثابت GLfixed *coords);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXFOESPROC) (GLfloat x, GLfloat y, GLfloat z, GLfloat ويڪر, GLfloat اوچائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXFVOESPROC) (ثابت GLfloat *coords);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glDrawTexsOES (GLshort x, GLshort y, GLshort z, GLshort ويڪر, GLshort اوچائي);
GL_API فراغ GL_APIENTRY glDrawTexiOES (GLint x, GLint y, GLint z, GLint ويڪر, GLint اوچائي);
GL_API فراغ GL_APIENTRY glDrawTexxOES (GLfixed x, GLfixed y, GLfixed z, GLfixed ويڪر, GLfixed اوچائي);
GL_API فراغ GL_APIENTRY glDrawTexsvOES (ثابت GLshort *coords);
GL_API فراغ GL_APIENTRY glDrawTexivOES (ثابت GLint *coords);
GL_API فراغ GL_APIENTRY glDrawTexxvOES (ثابت GLfixed *coords);
GL_API فراغ GL_APIENTRY glDrawTexfOES (GLfloat x, GLfloat y, GLfloat z, GLfloat ويڪر, GLfloat اوچائي);
GL_API فراغ GL_APIENTRY glDrawTexfvOES (ثابت GLfloat *coords);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_OES_draw_texture */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_element_اشاريو_uint
#وصف_ڪريو GL_OES_element_اشاريو_uint 1
#وصف_ڪريو GL_UNSIGNED_INT                   0x1405
#جيڪڏهن_پورو /* GL_OES_element_index_uint */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_extended_ميٽرڪس_palette
#وصف_ڪريو GL_OES_extended_ميٽرڪس_palette 1
#جيڪڏهن_پورو /* GL_OES_extended_matrix_palette */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_fbo_render_mipmap
#وصف_ڪريو GL_OES_fbo_render_mipmap 1
#جيڪڏهن_پورو /* GL_OES_fbo_render_mipmap */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_fixed_نقطو
#وصف_ڪريو GL_OES_fixed_نقطو 1
#وصف_ڪريو GL_FIXED_OES                      0x140C
تعريفنوع فراغ (GL_APIENTRYP PFNGLALPHAFUNCXOESPROC) (GLenum func, GLfixed ref);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARCOLORXOESPROC) (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARDEPTHXOESPROC) (GLfixed اونهائي_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLIPPLANEXOESPROC) (GLenum plane, ثابت GLfixed *equation);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOLOR4XOESPROC) (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHRANGEXOESPROC) (GLfixed n, GLfixed f);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFOGXOESPROC) (GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFOGXVOESPROC) (GLenum pname, ثابت GLfixed *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRUSTUMXOESPROC) (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETCLIPPLANEXOESPROC) (GLenum plane, GLfixed *equation);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFIXEDVOESPROC) (GLenum pname, GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXENVXVOESPROC) (GLenum هدف, GLenum pname, GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXPARAMETERXVOESPROC) (GLenum هدف, GLenum pname, GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLIGHTMODELXOESPROC) (GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLIGHTMODELXVOESPROC) (GLenum pname, ثابت GLfixed *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLIGHTXOESPROC) (GLenum light, GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLIGHTXVOESPROC) (GLenum light, GLenum pname, ثابت GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLINEWIDTHXOESPROC) (GLfixed ويڪر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLOADMATRIXXOESPROC) (ثابت GLfixed *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATERIALXOESPROC) (GLenum face, GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATERIALXVOESPROC) (GLenum face, GLenum pname, ثابت GLfixed *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTMATRIXXOESPROC) (ثابت GLfixed *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTITEXCOORD4XOESPROC) (GLenum texture, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
تعريفنوع فراغ (GL_APIENTRYP PFNGLNORMAL3XOESPROC) (GLfixed nx, GLfixed ny, GLfixed nz);
تعريفنوع فراغ (GL_APIENTRYP PFNGLORTHOXOESPROC) (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOINTPARAMETERXVOESPROC) (GLenum pname, ثابت GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOINTSIZEXOESPROC) (GLfixed سائيز);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOLYGONOFFSETXOESPROC) (GLfixed ضرب_ڪندڙ, GLfixed units);
تعريفنوع فراغ (GL_APIENTRYP PFNGLROTATEXOESPROC) (GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCALEXOESPROC) (GLfixed x, GLfixed y, GLfixed z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXENVXOESPROC) (GLenum هدف, GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXENVXVOESPROC) (GLenum هدف, GLenum pname, ثابت GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERXOESPROC) (GLenum هدف, GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERXVOESPROC) (GLenum هدف, GLenum pname, ثابت GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTRANSLATEXOESPROC) (GLfixed x, GLfixed y, GLfixed z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETLIGHTXVOESPROC) (GLenum light, GLenum pname, GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETMATERIALXVOESPROC) (GLenum face, GLenum pname, GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOINTPARAMETERXOESPROC) (GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLECOVERAGEXOESPROC) (GLclampx قدر, GLboolean invert);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXGENXVOESPROC) (GLenum coord, GLenum pname, GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXGENXOESPROC) (GLenum coord, GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXGENXVOESPROC) (GLenum coord, GLenum pname, ثابت GLfixed *params);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glAlphaFuncxOES (GLenum func, GLfixed ref);
GL_API فراغ GL_APIENTRY glClearColorxOES (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GL_API فراغ GL_APIENTRY glClearDepthxOES (GLfixed اونهائي_2);
GL_API فراغ GL_APIENTRY glClipPlanexOES (GLenum plane, ثابت GLfixed *equation);
GL_API فراغ GL_APIENTRY glColor4xOES (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GL_API فراغ GL_APIENTRY gl_اونهائي_Rangex_OES (GLfixed n, GLfixed f);
GL_API فراغ GL_APIENTRY glFogxOES (GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glFogxvOES (GLenum pname, ثابت GLfixed *param);
GL_API فراغ GL_APIENTRY glFrustumxOES (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
GL_API فراغ GL_APIENTRY glGetClipPlanexOES (GLenum plane, GLfixed *equation);
GL_API فراغ GL_APIENTRY glGetFixedvOES (GLenum pname, GLfixed *params);
GL_API فراغ GL_APIENTRY glGetTexEnvxvOES (GLenum هدف, GLenum pname, GLfixed *params);
GL_API فراغ GL_APIENTRY glGetTexParameterxvOES (GLenum هدف, GLenum pname, GLfixed *params);
GL_API فراغ GL_APIENTRY glLightModelxOES (GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glLightModelxvOES (GLenum pname, ثابت GLfixed *param);
GL_API فراغ GL_APIENTRY glLightxOES (GLenum light, GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glLightxvOES (GLenum light, GLenum pname, ثابت GLfixed *params);
GL_API فراغ GL_APIENTRY gl_سٽ_Widthx_OES (GLfixed ويڪر);
GL_API فراغ GL_APIENTRY gl_ڀريو_Matrixx_OES (ثابت GLfixed *m);
GL_API فراغ GL_APIENTRY glMaterialxOES (GLenum face, GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glMaterialxvOES (GLenum face, GLenum pname, ثابت GLfixed *param);
GL_API فراغ GL_APIENTRY glMultMatrixxOES (ثابت GLfixed *m);
GL_API فراغ GL_APIENTRY glMultiTexCoord4xOES (GLenum texture, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
GL_API فراغ GL_APIENTRY glNormal3xOES (GLfixed nx, GLfixed ny, GLfixed nz);
GL_API فراغ GL_APIENTRY glOrthoxOES (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
GL_API فراغ GL_APIENTRY gl_نقطو_Parameterxv_OES (GLenum pname, ثابت GLfixed *params);
GL_API فراغ GL_APIENTRY gl_نقطو_Sizex_OES (GLfixed سائيز);
GL_API فراغ GL_APIENTRY glPolygonOffsetxOES (GLfixed ضرب_ڪندڙ, GLfixed units);
GL_API فراغ GL_APIENTRY glRotatexOES (GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
GL_API فراغ GL_APIENTRY glScalexOES (GLfixed x, GLfixed y, GLfixed z);
GL_API فراغ GL_APIENTRY glTexEnvxOES (GLenum هدف, GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glTexEnvxvOES (GLenum هدف, GLenum pname, ثابت GLfixed *params);
GL_API فراغ GL_APIENTRY glTexParameterxOES (GLenum هدف, GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glTexParameterxvOES (GLenum هدف, GLenum pname, ثابت GLfixed *params);
GL_API فراغ GL_APIENTRY glTranslatexOES (GLfixed x, GLfixed y, GLfixed z);
GL_API فراغ GL_APIENTRY glGetLightxvOES (GLenum light, GLenum pname, GLfixed *params);
GL_API فراغ GL_APIENTRY glGetMaterialxvOES (GLenum face, GLenum pname, GLfixed *params);
GL_API فراغ GL_APIENTRY gl_نقطو_Parameterx_OES (GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glSampleCoveragexOES (GLclampx قدر, GLboolean invert);
GL_API فراغ GL_APIENTRY glGetTexGenxvOES (GLenum coord, GLenum pname, GLfixed *params);
GL_API فراغ GL_APIENTRY glTexGenxOES (GLenum coord, GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glTexGenxvOES (GLenum coord, GLenum pname, ثابت GLfixed *params);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_OES_fixed_point */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_framebuffer_object
#وصف_ڪريو GL_OES_framebuffer_object 1
#وصف_ڪريو GL_NONE_OES                       0
#وصف_ڪريو GL_FRAMEBUFFER_OES                0x8D40
#وصف_ڪريو GL_RENDERBUFFER_OES               0x8D41
#وصف_ڪريو GL_RGBA4_OES                      0x8056
#وصف_ڪريو GL_RGB5_A1_OES                    0x8057
#وصف_ڪريو GL_RGB565_OES                     0x8D62
#وصف_ڪريو GL_اونهائي_COMPONENT16_OES          0x81A5
#وصف_ڪريو GL_RENDERBUFFER_ويڪر_OES         0x8D42
#وصف_ڪريو GL_RENDERBUFFER_اوچائي_OES        0x8D43
#وصف_ڪريو GL_RENDERBUFFER_اندروني_FORMAT_OES 0x8D44
#وصف_ڪريو GL_RENDERBUFFER_RED_سائيز_OES      0x8D50
#وصف_ڪريو GL_RENDERBUFFER_GREEN_سائيز_OES    0x8D51
#وصف_ڪريو GL_RENDERBUFFER_BLUE_سائيز_OES     0x8D52
#وصف_ڪريو GL_RENDERBUFFER_ALPHA_سائيز_OES    0x8D53
#وصف_ڪريو GL_RENDERBUFFER_اونهائي_سائيز_OES    0x8D54
#وصف_ڪريو GL_RENDERBUFFER_STENCIL_سائيز_OES  0x8D55
#وصف_ڪريو GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_OES 0x8CD0
#وصف_ڪريو GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_OES 0x8CD1
#وصف_ڪريو GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_OES 0x8CD2
#وصف_ڪريو GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_OES 0x8CD3
#وصف_ڪريو GL_COLOR_ATTACHMENT0_OES          0x8CE0
#وصف_ڪريو GL_اونهائي_ATTACHMENT_OES           0x8D00
#وصف_ڪريو GL_STENCIL_ATTACHMENT_OES         0x8D20
#وصف_ڪريو GL_FRAMEBUFFER_COMPLETE_OES       0x8CD5
#وصف_ڪريو GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_OES 0x8CD6
#وصف_ڪريو GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_OES 0x8CD7
#وصف_ڪريو GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_OES 0x8CD9
#وصف_ڪريو GL_FRAMEBUFFER_INCOMPLETE_FORMATS_OES 0x8CDA
#وصف_ڪريو GL_FRAMEBUFFER_UNSUPPORTED_OES    0x8CDD
#وصف_ڪريو GL_FRAMEBUFFER_BINDING_OES        0x8CA6
#وصف_ڪريو GL_RENDERBUFFER_BINDING_OES       0x8CA7
#وصف_ڪريو GL_MAX_RENDERBUFFER_سائيز_OES      0x84E8
#وصف_ڪريو GL_INVALID_FRAMEBUFFER_OPERATION_OES 0x0506
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISRENDERBUFFEROESPROC) (GLuint renderbuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDRENDERBUFFEROESPROC) (GLenum هدف, GLuint renderbuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETERENDERBUFFERSOESPROC) (GLsizei n, ثابت GLuint *renderbuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENRENDERBUFFERSOESPROC) (GLsizei n, GLuint *renderbuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEOESPROC) (GLenum هدف, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVOESPROC) (GLenum هدف, GLenum pname, GLint *params);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISFRAMEBUFFEROESPROC) (GLuint framebuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDFRAMEBUFFEROESPROC) (GLenum هدف, GLuint framebuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEFRAMEBUFFERSOESPROC) (GLsizei n, ثابت GLuint *framebuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENFRAMEBUFFERSOESPROC) (GLsizei n, GLuint *framebuffers);
تعريفنوع GLenum (GL_APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSOESPROC) (GLenum هدف);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFEROESPROC) (GLenum هدف, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DOESPROC) (GLenum هدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVOESPROC) (GLenum هدف, GLenum attachment, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENERATEMIPMAPOESPROC) (GLenum هدف);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_API GLboolean GL_APIENTRY glIsRenderbufferOES (GLuint renderbuffer);
GL_API فراغ GL_APIENTRY glBindRenderbufferOES (GLenum هدف, GLuint renderbuffer);
GL_API فراغ GL_APIENTRY glDeleteRenderbuffersOES (GLsizei n, ثابت GLuint *renderbuffers);
GL_API فراغ GL_APIENTRY glGenRenderbuffersOES (GLsizei n, GLuint *renderbuffers);
GL_API فراغ GL_APIENTRY glRenderbufferStorageOES (GLenum هدف, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
GL_API فراغ GL_APIENTRY glGetRenderbufferParameterivOES (GLenum هدف, GLenum pname, GLint *params);
GL_API GLboolean GL_APIENTRY glIsFramebufferOES (GLuint framebuffer);
GL_API فراغ GL_APIENTRY glBindFramebufferOES (GLenum هدف, GLuint framebuffer);
GL_API فراغ GL_APIENTRY glDeleteFramebuffersOES (GLsizei n, ثابت GLuint *framebuffers);
GL_API فراغ GL_APIENTRY glGenFramebuffersOES (GLsizei n, GLuint *framebuffers);
GL_API GLenum GL_APIENTRY gl_Check_Framebuffer_حالت_OES (GLenum هدف);
GL_API فراغ GL_APIENTRY glFramebufferRenderbufferOES (GLenum هدف, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
GL_API فراغ GL_APIENTRY glFramebufferTexture2DOES (GLenum هدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GL_API فراغ GL_APIENTRY glGetFramebufferAttachmentParameterivOES (GLenum هدف, GLenum attachment, GLenum pname, GLint *params);
GL_API فراغ GL_APIENTRY glGenerateMipmapOES (GLenum هدف);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_OES_framebuffer_object */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_mapbuffer
#وصف_ڪريو GL_OES_mapbuffer 1
#وصف_ڪريو GL_WRITE_ONLY_OES                 0x88B9
#وصف_ڪريو GL_بفر_ACCESS_OES              0x88BB
#وصف_ڪريو GL_بفر_MAPPED_OES              0x88BC
#وصف_ڪريو GL_بفر_MAP_اشارو_OES         0x88BD
تعريفنوع فراغ *(GL_APIENTRYP PFNGLMAPBUFFEROESPROC) (GLenum هدف, GLenum access);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLUNMAPBUFFEROESPROC) (GLenum هدف);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETBUFFERPOINTERVOESPROC) (GLenum هدف, GLenum pname, فراغ **params);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_API فراغ *GL_APIENTRY gl_Map_بفر_OES (GLenum هدف, GLenum access);
GL_API GLboolean GL_APIENTRY gl_Unmap_بفر_OES (GLenum هدف);
GL_API فراغ GL_APIENTRY gl_Get_بفر_Pointerv_OES (GLenum هدف, GLenum pname, فراغ **params);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_OES_mapbuffer */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_ميٽرڪس_get
#وصف_ڪريو GL_OES_ميٽرڪس_get 1
#وصف_ڪريو GL_MODELVIEW_ميٽرڪس_FLOAT_AS_INT_بٽ_OES 0x898D
#وصف_ڪريو GL_PROJECTION_ميٽرڪس_FLOAT_AS_INT_بٽ_OES 0x898E
#وصف_ڪريو GL_TEXTURE_ميٽرڪس_FLOAT_AS_INT_بٽ_OES 0x898F
#جيڪڏهن_پورو /* GL_OES_matrix_get */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_ميٽرڪس_palette
#وصف_ڪريو GL_OES_ميٽرڪس_palette 1
#وصف_ڪريو GL_MAX_راس_UNITS_OES           0x86A4
#وصف_ڪريو GL_MAX_PALETTE_MATRICES_OES       0x8842
#وصف_ڪريو GL_ميٽرڪس_PALETTE_OES             0x8840
#وصف_ڪريو GL_ميٽرڪس_اشاريو_ARRAY_OES         0x8844
#وصف_ڪريو GL_وزن_ARRAY_OES               0x86AD
#وصف_ڪريو GL_CURRENT_PALETTE_ميٽرڪس_OES     0x8843
#وصف_ڪريو GL_ميٽرڪس_اشاريو_ARRAY_سائيز_OES    0x8846
#وصف_ڪريو GL_ميٽرڪس_اشاريو_ARRAY_TYPE_OES    0x8847
#وصف_ڪريو GL_ميٽرڪس_اشاريو_ARRAY_STRIDE_OES  0x8848
#وصف_ڪريو GL_ميٽرڪس_اشاريو_ARRAY_اشارو_OES 0x8849
#وصف_ڪريو GL_ميٽرڪس_اشاريو_ARRAY_بفر_BINDING_OES 0x8B9E
#وصف_ڪريو GL_وزن_ARRAY_سائيز_OES          0x86AB
#وصف_ڪريو GL_وزن_ARRAY_TYPE_OES          0x86A9
#وصف_ڪريو GL_وزن_ARRAY_STRIDE_OES        0x86AA
#وصف_ڪريو GL_وزن_ARRAY_اشارو_OES       0x86AC
#وصف_ڪريو GL_وزن_ARRAY_بفر_BINDING_OES 0x889E
تعريفنوع فراغ (GL_APIENTRYP PFNGLCURRENTPALETTEMATRIXOESPROC) (GLuint matrixpaletteindex);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLOADPALETTEFROMMODELVIEWMATRIXOESPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXINDEXPOINTEROESPROC) (GLint سائيز, GLenum type, GLsizei stride, ثابت فراغ *اشارو_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLWEIGHTPOINTEROESPROC) (GLint سائيز, GLenum type, GLsizei stride, ثابت فراغ *اشارو_2);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY gl_Current_Palette_ميٽرڪس_OES (GLuint matrixpaletteindex);
GL_API فراغ GL_APIENTRY gl_ڀريو_Palette_From_Model_View_ميٽرڪس_OES (فراغ);
GL_API فراغ GL_APIENTRY gl_ميٽرڪس_اشاريو_اشارو_OES (GLint سائيز, GLenum type, GLsizei stride, ثابت فراغ *اشارو_2);
GL_API فراغ GL_APIENTRY gl_وزن_اشارو_OES (GLint سائيز, GLenum type, GLsizei stride, ثابت فراغ *اشارو_2);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_OES_matrix_palette */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_packed_اونهائي_stencil
#وصف_ڪريو GL_OES_packed_اونهائي_stencil 1
#وصف_ڪريو GL_اونهائي_STENCIL_OES              0x84F9
#وصف_ڪريو GL_UNSIGNED_INT_24_8_OES          0x84FA
#وصف_ڪريو GL_DEPTH24_STENCIL8_OES           0x88F0
#جيڪڏهن_پورو /* GL_OES_packed_depth_stencil */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_query_ميٽرڪس
#وصف_ڪريو GL_OES_query_ميٽرڪس 1
تعريفنوع GLbitfield (GL_APIENTRYP PFNGLQUERYMATRIXXOESPROC) (GLfixed *mantissa, GLint *exponent);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_API GLbitfield GL_APIENTRY glQueryMatrixxOES (GLfixed *mantissa, GLint *exponent);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_OES_query_matrix */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_required_internalformat
#وصف_ڪريو GL_OES_required_internalformat 1
#وصف_ڪريو GL_ALPHA8_OES                     0x803C
#وصف_ڪريو GL_LUMINANCE4_ALPHA4_OES          0x8043
#وصف_ڪريو GL_LUMINANCE8_ALPHA8_OES          0x8045
#وصف_ڪريو GL_LUMINANCE8_OES                 0x8040
#وصف_ڪريو GL_RGB8_OES                       0x8051
#وصف_ڪريو GL_RGBA8_OES                      0x8058
#وصف_ڪريو GL_RGB10_EXT                      0x8052
#وصف_ڪريو GL_RGB10_A2_EXT                   0x8059
#جيڪڏهن_پورو /* GL_OES_required_internalformat */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_rgb8_rgba8
#وصف_ڪريو GL_OES_rgb8_rgba8 1
#جيڪڏهن_پورو /* GL_OES_rgb8_rgba8 */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_single_precision
#وصف_ڪريو GL_OES_single_precision 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARDEPTHFOESPROC) (GLclampf اونهائي_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLIPPLANEFOESPROC) (GLenum plane, ثابت GLfloat *equation);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHRANGEFOESPROC) (GLclampf n, GLclampf f);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRUSTUMFOESPROC) (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETCLIPPLANEFOESPROC) (GLenum plane, GLfloat *equation);
تعريفنوع فراغ (GL_APIENTRYP PFNGLORTHOFOESPROC) (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glClearDepthfOES (GLclampf اونهائي_2);
GL_API فراغ GL_APIENTRY glClipPlanefOES (GLenum plane, ثابت GLfloat *equation);
GL_API فراغ GL_APIENTRY gl_اونهائي_Rangef_OES (GLclampf n, GLclampf f);
GL_API فراغ GL_APIENTRY glFrustumfOES (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
GL_API فراغ GL_APIENTRY glGetClipPlanefOES (GLenum plane, GLfloat *equation);
GL_API فراغ GL_APIENTRY glOrthofOES (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_OES_single_precision */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_stencil1
#وصف_ڪريو GL_OES_stencil1 1
#وصف_ڪريو GL_STENCIL_INDEX1_OES             0x8D46
#جيڪڏهن_پورو /* GL_OES_stencil1 */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_stencil4
#وصف_ڪريو GL_OES_stencil4 1
#وصف_ڪريو GL_STENCIL_INDEX4_OES             0x8D47
#جيڪڏهن_پورو /* GL_OES_stencil4 */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_stencil8
#وصف_ڪريو GL_OES_stencil8 1
#وصف_ڪريو GL_STENCIL_INDEX8_OES             0x8D48
#جيڪڏهن_پورو /* GL_OES_stencil8 */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_stencil_wrap
#وصف_ڪريو GL_OES_stencil_wrap 1
#وصف_ڪريو GL_INCR_WRAP_OES                  0x8507
#وصف_ڪريو GL_DECR_WRAP_OES                  0x8508
#جيڪڏهن_پورو /* GL_OES_stencil_wrap */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_surfaceless_context
#وصف_ڪريو GL_OES_surfaceless_context 1
#وصف_ڪريو GL_FRAMEBUFFER_UNDEFINED_OES      0x8219
#جيڪڏهن_پورو /* GL_OES_surfaceless_context */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_texture_cube_map
#وصف_ڪريو GL_OES_texture_cube_map 1
#وصف_ڪريو GL_عام_MAP_OES                 0x8511
#وصف_ڪريو GL_REFLECTION_MAP_OES             0x8512
#وصف_ڪريو GL_TEXTURE_CUBE_MAP_OES           0x8513
#وصف_ڪريو GL_TEXTURE_BINDING_CUBE_MAP_OES   0x8514
#وصف_ڪريو GL_TEXTURE_CUBE_MAP_مثبت_X_OES 0x8515
#وصف_ڪريو GL_TEXTURE_CUBE_MAP_NEGATIVE_X_OES 0x8516
#وصف_ڪريو GL_TEXTURE_CUBE_MAP_مثبت_Y_OES 0x8517
#وصف_ڪريو GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_OES 0x8518
#وصف_ڪريو GL_TEXTURE_CUBE_MAP_مثبت_Z_OES 0x8519
#وصف_ڪريو GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_OES 0x851A
#وصف_ڪريو GL_MAX_CUBE_MAP_TEXTURE_سائيز_OES  0x851C
#وصف_ڪريو GL_TEXTURE_GEN_گهڻائي_OES           0x2500
#وصف_ڪريو GL_TEXTURE_GEN_STR_OES            0x8D60
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXGENFOESPROC) (GLenum coord, GLenum pname, GLfloat param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXGENFVOESPROC) (GLenum coord, GLenum pname, ثابت GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXGENIOESPROC) (GLenum coord, GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXGENIVOESPROC) (GLenum coord, GLenum pname, ثابت GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXGENFVOESPROC) (GLenum coord, GLenum pname, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXGENIVOESPROC) (GLenum coord, GLenum pname, GLint *params);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glTexGenfOES (GLenum coord, GLenum pname, GLfloat param);
GL_API فراغ GL_APIENTRY glTexGenfvOES (GLenum coord, GLenum pname, ثابت GLfloat *params);
GL_API فراغ GL_APIENTRY glTexGeniOES (GLenum coord, GLenum pname, GLint param);
GL_API فراغ GL_APIENTRY glTexGenivOES (GLenum coord, GLenum pname, ثابت GLint *params);
GL_API فراغ GL_APIENTRY glGetTexGenfvOES (GLenum coord, GLenum pname, GLfloat *params);
GL_API فراغ GL_APIENTRY glGetTexGenivOES (GLenum coord, GLenum pname, GLint *params);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_OES_texture_cube_map */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_texture_env_crossbar
#وصف_ڪريو GL_OES_texture_env_crossbar 1
#جيڪڏهن_پورو /* GL_OES_texture_env_crossbar */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_texture_mirrored_repeat
#وصف_ڪريو GL_OES_texture_mirrored_repeat 1
#وصف_ڪريو GL_MIRRORED_REPEAT_OES            0x8370
#جيڪڏهن_پورو /* GL_OES_texture_mirrored_repeat */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_texture_npot
#وصف_ڪريو GL_OES_texture_npot 1
#جيڪڏهن_پورو /* GL_OES_texture_npot */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_راس_array_object
#وصف_ڪريو GL_OES_راس_array_object 1
#وصف_ڪريو GL_راس_ARRAY_BINDING_OES       0x85B5
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDVERTEXARRAYOESPROC) (GLuint array);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEVERTEXARRAYSOESPROC) (GLsizei n, ثابت GLuint *arrays);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENVERTEXARRAYSOESPROC) (GLsizei n, GLuint *arrays);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISVERTEXARRAYOESPROC) (GLuint array);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY gl_Bind_راس_Array_OES (GLuint array);
GL_API فراغ GL_APIENTRY gl_Delete_راس_Arrays_OES (GLsizei n, ثابت GLuint *arrays);
GL_API فراغ GL_APIENTRY gl_Gen_راس_Arrays_OES (GLsizei n, GLuint *arrays);
GL_API GLboolean GL_APIENTRY gl_Is_راس_Array_OES (GLuint array);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_OES_vertex_array_object */

#جيڪڏهن_وصف_نه_ٿيل GL_AMD_compressed_3DC_texture
#وصف_ڪريو GL_AMD_compressed_3DC_texture 1
#وصف_ڪريو GL_3DC_X_AMD                      0x87F9
#وصف_ڪريو GL_3DC_XY_AMD                     0x87FA
#جيڪڏهن_پورو /* GL_AMD_compressed_3DC_texture */

#جيڪڏهن_وصف_نه_ٿيل GL_AMD_compressed_ATC_texture
#وصف_ڪريو GL_AMD_compressed_ATC_texture 1
#وصف_ڪريو GL_ATC_RGB_AMD                    0x8C92
#وصف_ڪريو GL_ATC_RGBA_EXPLICIT_ALPHA_AMD    0x8C93
#وصف_ڪريو GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD 0x87EE
#جيڪڏهن_پورو /* GL_AMD_compressed_ATC_texture */

#جيڪڏهن_وصف_نه_ٿيل GL_APPLE_copy_texture_سطحون
#وصف_ڪريو GL_APPLE_copy_texture_سطحون 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYTEXTURELEVELSAPPLEPROC) (GLuint destinationTexture, GLuint ذريعو_Texture, GLint ذريعو_بنياد_Level, GLsizei ذريعو_Level_ڳڻپ);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY gl_Copy_Texture_سطحون_APPLE (GLuint destinationTexture, GLuint ذريعو_Texture, GLint ذريعو_بنياد_Level, GLsizei ذريعو_Level_ڳڻپ);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_APPLE_copy_texture_levels */

#جيڪڏهن_وصف_نه_ٿيل GL_APPLE_framebuffer_multisample
#وصف_ڪريو GL_APPLE_framebuffer_multisample 1
#وصف_ڪريو GL_RENDERBUFFER_SAMPLES_APPLE     0x8CAB
#وصف_ڪريو GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_APPLE 0x8D56
#وصف_ڪريو GL_MAX_SAMPLES_APPLE              0x8D57
#وصف_ڪريو GL_READ_FRAMEBUFFER_APPLE         0x8CA8
#وصف_ڪريو GL_DRAW_FRAMEBUFFER_APPLE         0x8CA9
#وصف_ڪريو GL_DRAW_FRAMEBUFFER_BINDING_APPLE 0x8CA6
#وصف_ڪريو GL_READ_FRAMEBUFFER_BINDING_APPLE 0x8CAA
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEAPPLEPROC) (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRESOLVEMULTISAMPLEFRAMEBUFFERAPPLEPROC) (فراغ);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glRenderbufferStorageMultisampleAPPLE (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
GL_API فراغ GL_APIENTRY glResolveMultisampleFramebufferAPPLE (فراغ);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_APPLE_framebuffer_multisample */

#جيڪڏهن_وصف_نه_ٿيل GL_APPLE_sync
#وصف_ڪريو GL_APPLE_sync 1
تعريفنوع بنية __GLsync *GLsync;
تعريفنوع khronos_uint64_t GLuint64;
تعريفنوع khronos_int64_t GLint64;
#وصف_ڪريو GL_SYNC_OBJECT_APPLE              0x8A53
#وصف_ڪريو GL_MAX_SERVER_WAIT_TIMEOUT_APPLE  0x9111
#وصف_ڪريو GL_OBJECT_TYPE_APPLE              0x9112
#وصف_ڪريو GL_SYNC_CONDITION_APPLE           0x9113
#وصف_ڪريو GL_SYNC_حالت_APPLE              0x9114
#وصف_ڪريو GL_SYNC_FLAGS_APPLE               0x9115
#وصف_ڪريو GL_SYNC_FENCE_APPLE               0x9116
#وصف_ڪريو GL_SYNC_GPU_COMMANDS_COMPLETE_APPLE 0x9117
#وصف_ڪريو GL_UNSIGNALED_APPLE               0x9118
#وصف_ڪريو GL_SIGNALED_APPLE                 0x9119
#وصف_ڪريو GL_ALREADY_SIGNALED_APPLE         0x911A
#وصف_ڪريو GL_TIMEOUT_EXPIRED_APPLE          0x911B
#وصف_ڪريو GL_CONDITION_SATISFIED_APPLE      0x911C
#وصف_ڪريو GL_WAIT_FAILED_APPLE              0x911D
#وصف_ڪريو GL_SYNC_FLUSH_COMMANDS_ٻٽو_انگ_APPLE  0x00000001
#وصف_ڪريو GL_TIMEOUT_IGNORED_APPLE          0xFFFFFFFFFFFFFFFFull
تعريفنوع GLsync (GL_APIENTRYP PFNGLFENCESYNCAPPLEPROC) (GLenum condition, GLbitfield flags);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISSYNCAPPLEPROC) (GLsync sync);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETESYNCAPPLEPROC) (GLsync sync);
تعريفنوع GLenum (GL_APIENTRYP PFNGLCLIENTWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
تعريفنوع فراغ (GL_APIENTRYP PFNGLWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTEGER64VAPPLEPROC) (GLenum pname, GLint64 *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSYNCIVAPPLEPROC) (GLsync sync, GLenum pname, GLsizei ڳڻپ, GLsizei *ڊيگهائي, GLint *قدرون);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_API GLsync GL_APIENTRY glFenceSyncAPPLE (GLenum condition, GLbitfield flags);
GL_API GLboolean GL_APIENTRY glIsSyncAPPLE (GLsync sync);
GL_API فراغ GL_APIENTRY glDeleteSyncAPPLE (GLsync sync);
GL_API GLenum GL_APIENTRY glClientWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_API فراغ GL_APIENTRY glWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_API فراغ GL_APIENTRY glGetInteger64vAPPLE (GLenum pname, GLint64 *params);
GL_API فراغ GL_APIENTRY glGetSyncivAPPLE (GLsync sync, GLenum pname, GLsizei ڳڻپ, GLsizei *ڊيگهائي, GLint *قدرون);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_APPLE_sync */

#جيڪڏهن_وصف_نه_ٿيل GL_APPLE_texture_2D_limited_npot
#وصف_ڪريو GL_APPLE_texture_2D_limited_npot 1
#جيڪڏهن_پورو /* GL_APPLE_texture_2D_limited_npot */

#جيڪڏهن_وصف_نه_ٿيل GL_APPLE_texture_format_BGRA8888
#وصف_ڪريو GL_APPLE_texture_format_BGRA8888 1
#وصف_ڪريو GL_BGRA_EXT                       0x80E1
#وصف_ڪريو GL_BGRA8_EXT                      0x93A1
#جيڪڏهن_پورو /* GL_APPLE_texture_format_BGRA8888 */

#جيڪڏهن_وصف_نه_ٿيل GL_APPLE_texture_max_level
#وصف_ڪريو GL_APPLE_texture_max_level 1
#وصف_ڪريو GL_TEXTURE_MAX_LEVEL_APPLE        0x813D
#جيڪڏهن_پورو /* GL_APPLE_texture_max_level */

#جيڪڏهن_وصف_نه_ٿيل GL_ARM_rgba8
#وصف_ڪريو GL_ARM_rgba8 1
#جيڪڏهن_پورو /* GL_ARM_rgba8 */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_blend_minmax
#وصف_ڪريو GL_EXT_blend_minmax 1
#وصف_ڪريو GL_MIN_EXT                        0x8007
#وصف_ڪريو GL_MAX_EXT                        0x8008
#جيڪڏهن_پورو /* GL_EXT_blend_minmax */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_debug_marker
#وصف_ڪريو GL_EXT_debug_marker 1
تعريفنوع حرف GLchar;
تعريفنوع فراغ (GL_APIENTRYP PFNGLINSERTEVENTMARKEREXTPROC) (GLsizei ڊيگهائي, ثابت GLchar *marker);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPUSHGROUPMARKEREXTPROC) (GLsizei ڊيگهائي, ثابت GLchar *marker);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOPGROUPMARKEREXTPROC) (فراغ);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY gl_وجهو_Event_Marker_EXT (GLsizei ڊيگهائي, ثابت GLchar *marker);
GL_API فراغ GL_APIENTRY gl_ڌڪو_گروهه_Marker_EXT (GLsizei ڊيگهائي, ثابت GLchar *marker);
GL_API فراغ GL_APIENTRY gl_ڪڍو_گروهه_Marker_EXT (فراغ);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_debug_marker */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_discard_framebuffer
#وصف_ڪريو GL_EXT_discard_framebuffer 1
#وصف_ڪريو GL_COLOR_EXT                      0x1800
#وصف_ڪريو GL_اونهائي_EXT                      0x1801
#وصف_ڪريو GL_STENCIL_EXT                    0x1802
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISCARDFRAMEBUFFEREXTPROC) (GLenum هدف, GLsizei انگ_Attachments, ثابت GLenum *attachments);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glDiscardFramebufferEXT (GLenum هدف, GLsizei انگ_Attachments, ثابت GLenum *attachments);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_discard_framebuffer */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_map_بفر_range
#وصف_ڪريو GL_EXT_map_بفر_range 1
#وصف_ڪريو GL_MAP_READ_ٻٽو_انگ_EXT               0x0001
#وصف_ڪريو GL_MAP_WRITE_ٻٽو_انگ_EXT              0x0002
#وصف_ڪريو GL_MAP_INVALIDATE_RANGE_ٻٽو_انگ_EXT   0x0004
#وصف_ڪريو GL_MAP_INVALIDATE_بفر_ٻٽو_انگ_EXT  0x0008
#وصف_ڪريو GL_MAP_FLUSH_EXPLICIT_ٻٽو_انگ_EXT     0x0010
#وصف_ڪريو GL_MAP_UNSYNCHRONIZED_ٻٽو_انگ_EXT     0x0020
تعريفنوع فراغ *(GL_APIENTRYP PFNGLMAPBUFFERRANGEEXTPROC) (GLenum هدف, GLintptr وٿي_2, GLsizeiptr ڊيگهائي, GLbitfield access);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEEXTPROC) (GLenum هدف, GLintptr وٿي_2, GLsizeiptr ڊيگهائي);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_API فراغ *GL_APIENTRY gl_Map_بفر_Range_EXT (GLenum هدف, GLintptr وٿي_2, GLsizeiptr ڊيگهائي, GLbitfield access);
GL_API فراغ GL_APIENTRY gl_Flush_Mapped_بفر_Range_EXT (GLenum هدف, GLintptr وٿي_2, GLsizeiptr ڊيگهائي);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_map_buffer_range */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_multi_draw_arrays
#وصف_ڪريو GL_EXT_multi_draw_arrays 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWARRAYSEXTPROC) (GLenum گهڻائي, ثابت GLint *پهريون, ثابت GLsizei *ڳڻپ, GLsizei primcount);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSEXTPROC) (GLenum گهڻائي, ثابت GLsizei *ڳڻپ, GLenum type, ثابت فراغ *ثابت*indices, GLsizei primcount);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glMultiDrawArraysEXT (GLenum گهڻائي, ثابت GLint *پهريون, ثابت GLsizei *ڳڻپ, GLsizei primcount);
GL_API فراغ GL_APIENTRY glMultiDrawElementsEXT (GLenum گهڻائي, ثابت GLsizei *ڳڻپ, GLenum type, ثابت فراغ *ثابت*indices, GLsizei primcount);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_multi_draw_arrays */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_multisampled_render_منزل_texture
#وصف_ڪريو GL_EXT_multisampled_render_منزل_texture 1
#وصف_ڪريو GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SAMPLES_EXT 0x8D6C
#وصف_ڪريو GL_RENDERBUFFER_SAMPLES_EXT       0x8CAB
#وصف_ڪريو GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT 0x8D56
#وصف_ڪريو GL_MAX_SAMPLES_EXT                0x8D57
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEEXTPROC) (GLenum هدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glRenderbufferStorageMultisampleEXT (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
GL_API فراغ GL_APIENTRY glFramebufferTexture2DMultisampleEXT (GLenum هدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_multisampled_render_to_texture */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_read_format_bgra
#وصف_ڪريو GL_EXT_read_format_bgra 1
#وصف_ڪريو GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT 0x8365
#وصف_ڪريو GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT 0x8366
#جيڪڏهن_پورو /* GL_EXT_read_format_bgra */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_robustness
#وصف_ڪريو GL_EXT_robustness 1
#وصف_ڪريو GL_GUILTY_CONTEXT_RESET_EXT       0x8253
#وصف_ڪريو GL_INNOCENT_CONTEXT_RESET_EXT     0x8254
#وصف_ڪريو GL_UNKNOWN_CONTEXT_RESET_EXT      0x8255
#وصف_ڪريو GL_CONTEXT_ROBUST_ACCESS_EXT      0x90F3
#وصف_ڪريو GL_RESET_NOTIFICATION_STRATEGY_EXT 0x8256
#وصف_ڪريو GL_LOSE_CONTEXT_ON_RESET_EXT      0x8252
#وصف_ڪريو GL_NO_RESET_NOTIFICATION_EXT      0x8261
تعريفنوع GLenum (GL_APIENTRYP PFNGLGETGRAPHICSRESETSTATUSEXTPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLREADNPIXELSEXTPROC) (GLint x, GLint y, GLsizei ويڪر, GLsizei اوچائي, GLenum format, GLenum type, GLsizei buf_سائيز, فراغ *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNUNIFORMFVEXTPROC) (GLuint پروگرام, GLint location, GLsizei buf_سائيز, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNUNIFORMIVEXTPROC) (GLuint پروگرام, GLint location, GLsizei buf_سائيز, GLint *params);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_API GLenum GL_APIENTRY gl_Get_Graphics_Reset_حالت_EXT (فراغ);
GL_API فراغ GL_APIENTRY glReadnPixelsEXT (GLint x, GLint y, GLsizei ويڪر, GLsizei اوچائي, GLenum format, GLenum type, GLsizei buf_سائيز, فراغ *معلومات);
GL_API فراغ GL_APIENTRY glGetnUniformfvEXT (GLuint پروگرام, GLint location, GLsizei buf_سائيز, GLfloat *params);
GL_API فراغ GL_APIENTRY glGetnUniformivEXT (GLuint پروگرام, GLint location, GLsizei buf_سائيز, GLint *params);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_robustness */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_sRGB
#وصف_ڪريو GL_EXT_sRGB 1
#وصف_ڪريو GL_SRGB_EXT                       0x8C40
#وصف_ڪريو GL_SRGB_ALPHA_EXT                 0x8C42
#وصف_ڪريو GL_SRGB8_ALPHA8_EXT               0x8C43
#وصف_ڪريو GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING_EXT 0x8210
#جيڪڏهن_پورو /* GL_EXT_sRGB */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_texture_compression_dxt1
#وصف_ڪريو GL_EXT_texture_compression_dxt1 1
#وصف_ڪريو GL_COMPRESSED_RGB_S3TC_DXT1_EXT   0x83F0
#وصف_ڪريو GL_COMPRESSED_RGBA_S3TC_DXT1_EXT  0x83F1
#جيڪڏهن_پورو /* GL_EXT_texture_compression_dxt1 */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_texture_filter_anisotropic
#وصف_ڪريو GL_EXT_texture_filter_anisotropic 1
#وصف_ڪريو GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#وصف_ڪريو GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#جيڪڏهن_پورو /* GL_EXT_texture_filter_anisotropic */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_texture_format_BGRA8888
#وصف_ڪريو GL_EXT_texture_format_BGRA8888 1
#جيڪڏهن_پورو /* GL_EXT_texture_format_BGRA8888 */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_texture_lod_bias
#وصف_ڪريو GL_EXT_texture_lod_bias 1
#وصف_ڪريو GL_MAX_TEXTURE_LOD_BIAS_EXT       0x84FD
#وصف_ڪريو GL_TEXTURE_FILTER_CONTROL_EXT     0x8500
#وصف_ڪريو GL_TEXTURE_LOD_BIAS_EXT           0x8501
#جيڪڏهن_پورو /* GL_EXT_texture_lod_bias */

#جيڪڏهن_وصف_نه_ٿيل GL_EXT_texture_storage
#وصف_ڪريو GL_EXT_texture_storage 1
#وصف_ڪريو GL_TEXTURE_IMMUTABLE_FORMAT_EXT   0x912F
#وصف_ڪريو GL_ALPHA8_EXT                     0x803C
#وصف_ڪريو GL_LUMINANCE8_EXT                 0x8040
#وصف_ڪريو GL_LUMINANCE8_ALPHA8_EXT          0x8045
#وصف_ڪريو GL_RGBA32F_EXT                    0x8814
#وصف_ڪريو GL_RGB32F_EXT                     0x8815
#وصف_ڪريو GL_ALPHA32F_EXT                   0x8816
#وصف_ڪريو GL_LUMINANCE32F_EXT               0x8818
#وصف_ڪريو GL_LUMINANCE_ALPHA32F_EXT         0x8819
#وصف_ڪريو GL_RGBA16F_EXT                    0x881A
#وصف_ڪريو GL_RGB16F_EXT                     0x881B
#وصف_ڪريو GL_ALPHA16F_EXT                   0x881C
#وصف_ڪريو GL_LUMINANCE16F_EXT               0x881E
#وصف_ڪريو GL_LUMINANCE_ALPHA16F_EXT         0x881F
#وصف_ڪريو GL_R8_EXT                         0x8229
#وصف_ڪريو GL_RG8_EXT                        0x822B
#وصف_ڪريو GL_R32F_EXT                       0x822E
#وصف_ڪريو GL_RG32F_EXT                      0x8230
#وصف_ڪريو GL_R16F_EXT                       0x822D
#وصف_ڪريو GL_RG16F_EXT                      0x822F
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE1DEXTPROC) (GLenum هدف, GLsizei سطحون, GLenum internalformat, GLsizei ويڪر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE2DEXTPROC) (GLenum هدف, GLsizei سطحون, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE3DEXTPROC) (GLenum هدف, GLsizei سطحون, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGE1DEXTPROC) (GLuint texture, GLenum هدف, GLsizei سطحون, GLenum internalformat, GLsizei ويڪر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGE2DEXTPROC) (GLuint texture, GLenum هدف, GLsizei سطحون, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGE3DEXTPROC) (GLuint texture, GLenum هدف, GLsizei سطحون, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glTexStorage1DEXT (GLenum هدف, GLsizei سطحون, GLenum internalformat, GLsizei ويڪر);
GL_API فراغ GL_APIENTRY glTexStorage2DEXT (GLenum هدف, GLsizei سطحون, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
GL_API فراغ GL_APIENTRY glTexStorage3DEXT (GLenum هدف, GLsizei سطحون, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2);
GL_API فراغ GL_APIENTRY glTextureStorage1DEXT (GLuint texture, GLenum هدف, GLsizei سطحون, GLenum internalformat, GLsizei ويڪر);
GL_API فراغ GL_APIENTRY glTextureStorage2DEXT (GLuint texture, GLenum هدف, GLsizei سطحون, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
GL_API فراغ GL_APIENTRY glTextureStorage3DEXT (GLuint texture, GLenum هدف, GLsizei سطحون, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_EXT_texture_storage */

#جيڪڏهن_وصف_نه_ٿيل GL_IMG_multisampled_render_منزل_texture
#وصف_ڪريو GL_IMG_multisampled_render_منزل_texture 1
#وصف_ڪريو GL_RENDERBUFFER_SAMPLES_IMG       0x9133
#وصف_ڪريو GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_IMG 0x9134
#وصف_ڪريو GL_MAX_SAMPLES_IMG                0x9135
#وصف_ڪريو GL_TEXTURE_SAMPLES_IMG            0x9136
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEIMGPROC) (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEIMGPROC) (GLenum هدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glRenderbufferStorageMultisampleIMG (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
GL_API فراغ GL_APIENTRY glFramebufferTexture2DMultisampleIMG (GLenum هدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_IMG_multisampled_render_to_texture */

#جيڪڏهن_وصف_نه_ٿيل GL_IMG_read_format
#وصف_ڪريو GL_IMG_read_format 1
#وصف_ڪريو GL_BGRA_IMG                       0x80E1
#وصف_ڪريو GL_UNSIGNED_SHORT_4_4_4_4_REV_IMG 0x8365
#جيڪڏهن_پورو /* GL_IMG_read_format */

#جيڪڏهن_وصف_نه_ٿيل GL_IMG_texture_compression_pvrtc
#وصف_ڪريو GL_IMG_texture_compression_pvrtc 1
#وصف_ڪريو GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG 0x8C00
#وصف_ڪريو GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG 0x8C01
#وصف_ڪريو GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG 0x8C02
#وصف_ڪريو GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG 0x8C03
#جيڪڏهن_پورو /* GL_IMG_texture_compression_pvrtc */

#جيڪڏهن_وصف_نه_ٿيل GL_IMG_texture_env_enhanced_fixed_function
#وصف_ڪريو GL_IMG_texture_env_enhanced_fixed_function 1
#وصف_ڪريو GL_MODULATE_COLOR_IMG             0x8C04
#وصف_ڪريو GL_RECIP_جوڙيو_SIGNED_ALPHA_IMG     0x8C05
#وصف_ڪريو GL_TEXTURE_ALPHA_MODULATE_IMG     0x8C06
#وصف_ڪريو GL_ضرب_ڪندڙ_ALPHA_MODULATE_IMG      0x8C07
#وصف_ڪريو GL_FRAGMENT_ALPHA_MODULATE_IMG    0x8C08
#وصف_ڪريو GL_جوڙيو_BLEND_IMG                  0x8C09
#وصف_ڪريو GL_DOT3_RGBA_IMG                  0x86AF
#جيڪڏهن_پورو /* GL_IMG_texture_env_enhanced_fixed_function */

#جيڪڏهن_وصف_نه_ٿيل GL_IMG_user_clip_plane
#وصف_ڪريو GL_IMG_user_clip_plane 1
#وصف_ڪريو GL_CLIP_PLANE0_IMG                0x3000
#وصف_ڪريو GL_CLIP_PLANE1_IMG                0x3001
#وصف_ڪريو GL_CLIP_PLANE2_IMG                0x3002
#وصف_ڪريو GL_CLIP_PLANE3_IMG                0x3003
#وصف_ڪريو GL_CLIP_PLANE4_IMG                0x3004
#وصف_ڪريو GL_CLIP_PLANE5_IMG                0x3005
#وصف_ڪريو GL_MAX_CLIP_PLANES_IMG            0x0D32
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLIPPLANEFIMGPROC) (GLenum p, ثابت GLfloat *eqn);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLIPPLANEXIMGPROC) (GLenum p, ثابت GLfixed *eqn);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glClipPlanefIMG (GLenum p, ثابت GLfloat *eqn);
GL_API فراغ GL_APIENTRY glClipPlanexIMG (GLenum p, ثابت GLfixed *eqn);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_IMG_user_clip_plane */

#جيڪڏهن_وصف_نه_ٿيل GL_NV_fence
#وصف_ڪريو GL_NV_fence 1
#وصف_ڪريو GL_ALL_COMPLETED_NV               0x84F2
#وصف_ڪريو GL_FENCE_حالت_NV                0x84F3
#وصف_ڪريو GL_FENCE_CONDITION_NV             0x84F4
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEFENCESNVPROC) (GLsizei n, ثابت GLuint *fences);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENFENCESNVPROC) (GLsizei n, GLuint *fences);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISFENCENVPROC) (GLuint fence);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLTESTFENCENVPROC) (GLuint fence);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFENCEIVNVPROC) (GLuint fence, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFINISHFENCENVPROC) (GLuint fence);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSETFENCENVPROC) (GLuint fence, GLenum condition);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glDeleteFencesNV (GLsizei n, ثابت GLuint *fences);
GL_API فراغ GL_APIENTRY glGenFencesNV (GLsizei n, GLuint *fences);
GL_API GLboolean GL_APIENTRY glIsFenceNV (GLuint fence);
GL_API GLboolean GL_APIENTRY glTestFenceNV (GLuint fence);
GL_API فراغ GL_APIENTRY glGetFenceivNV (GLuint fence, GLenum pname, GLint *params);
GL_API فراغ GL_APIENTRY gl_پڄاڻي_Fence_NV (GLuint fence);
GL_API فراغ GL_APIENTRY gl_سيٽ_Fence_NV (GLuint fence, GLenum condition);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_NV_fence */

#جيڪڏهن_وصف_نه_ٿيل GL_QCOM_driver_control
#وصف_ڪريو GL_QCOM_driver_control 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETDRIVERCONTROLSQCOMPROC) (GLint *انگ, GLsizei سائيز, GLuint *driverControls);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETDRIVERCONTROLSTRINGQCOMPROC) (GLuint driverControl, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLchar *driverControlString);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glGetDriverControlsQCOM (GLint *انگ, GLsizei سائيز, GLuint *driverControls);
GL_API فراغ GL_APIENTRY glGetDriverControlStringQCOM (GLuint driverControl, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLchar *driverControlString);
GL_API فراغ GL_APIENTRY glEnableDriverControlQCOM (GLuint driverControl);
GL_API فراغ GL_APIENTRY glDisableDriverControlQCOM (GLuint driverControl);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_QCOM_driver_control */

#جيڪڏهن_وصف_نه_ٿيل GL_QCOM_extended_get
#وصف_ڪريو GL_QCOM_extended_get 1
#وصف_ڪريو GL_TEXTURE_ويڪر_QCOM             0x8BD2
#وصف_ڪريو GL_TEXTURE_اوچائي_QCOM            0x8BD3
#وصف_ڪريو GL_TEXTURE_اونهائي_QCOM             0x8BD4
#وصف_ڪريو GL_TEXTURE_اندروني_FORMAT_QCOM   0x8BD5
#وصف_ڪريو GL_TEXTURE_FORMAT_QCOM            0x8BD6
#وصف_ڪريو GL_TEXTURE_TYPE_QCOM              0x8BD7
#وصف_ڪريو GL_TEXTURE_IMAGE_VALID_QCOM       0x8BD8
#وصف_ڪريو GL_TEXTURE_انگ_سطحون_QCOM        0x8BD9
#وصف_ڪريو GL_TEXTURE_هدف_QCOM            0x8BDA
#وصف_ڪريو GL_TEXTURE_OBJECT_VALID_QCOM      0x8BDB
#وصف_ڪريو GL_STATE_RESTORE                  0x8BDC
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETTEXTURESQCOMPROC) (GLuint *textures, GLint maxTextures, GLint *انگ_Textures);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETBUFFERSQCOMPROC) (GLuint *buffers, GLint maxBuffers, GLint *انگ_Buffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETRENDERBUFFERSQCOMPROC) (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *انگ_Renderbuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETFRAMEBUFFERSQCOMPROC) (GLuint *framebuffers, GLint maxFramebuffers, GLint *انگ_Framebuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETTEXLEVELPARAMETERIVQCOMPROC) (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTTEXOBJECTSTATEOVERRIDEIQCOMPROC) (GLenum هدف, GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETTEXSUBIMAGEQCOMPROC) (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLenum format, GLenum type, فراغ *texels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETBUFFERPOINTERVQCOMPROC) (GLenum هدف, فراغ **params);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glExtGetTexturesQCOM (GLuint *textures, GLint maxTextures, GLint *انگ_Textures);
GL_API فراغ GL_APIENTRY glExtGetBuffersQCOM (GLuint *buffers, GLint maxBuffers, GLint *انگ_Buffers);
GL_API فراغ GL_APIENTRY glExtGetRenderbuffersQCOM (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *انگ_Renderbuffers);
GL_API فراغ GL_APIENTRY glExtGetFramebuffersQCOM (GLuint *framebuffers, GLint maxFramebuffers, GLint *انگ_Framebuffers);
GL_API فراغ GL_APIENTRY glExtGetTexLevelParameterivQCOM (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
GL_API فراغ GL_APIENTRY glExtTexObjectStateOverrideiQCOM (GLenum هدف, GLenum pname, GLint param);
GL_API فراغ GL_APIENTRY glExtGetTexSubImageQCOM (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLenum format, GLenum type, فراغ *texels);
GL_API فراغ GL_APIENTRY gl_Ext_Get_بفر_Pointerv_QCOM (GLenum هدف, فراغ **params);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_QCOM_extended_get */

#جيڪڏهن_وصف_نه_ٿيل GL_QCOM_extended_get2
#وصف_ڪريو GL_QCOM_extended_get2 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETSHADERSQCOMPROC) (GLuint *shaders, GLint maxShaders, GLint *انگ_Shaders);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETPROGRAMSQCOMPROC) (GLuint *programs, GLint maxPrograms, GLint *انگ_Programs);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLEXTISPROGRAMBINARYQCOMPROC) (GLuint پروگرام);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETPROGRAMBINARYSOURCEQCOMPROC) (GLuint پروگرام, GLenum shadertype, GLchar *ذريعو, GLint *ڊيگهائي);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glExtGetShadersQCOM (GLuint *shaders, GLint maxShaders, GLint *انگ_Shaders);
GL_API فراغ GL_APIENTRY glExtGetProgramsQCOM (GLuint *programs, GLint maxPrograms, GLint *انگ_Programs);
GL_API GLboolean GL_APIENTRY gl_Ext_Is_پروگرام_ٻٽو_QCOM (GLuint پروگرام);
GL_API فراغ GL_APIENTRY gl_Ext_Get_پروگرام_ٻٽو_ذريعو_QCOM (GLuint پروگرام, GLenum shadertype, GLchar *ذريعو, GLint *ڊيگهائي);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_QCOM_extended_get2 */

#جيڪڏهن_وصف_نه_ٿيل GL_QCOM_perfmon_global_گهڻائي
#وصف_ڪريو GL_QCOM_perfmon_global_گهڻائي 1
#وصف_ڪريو GL_PERFMON_GLOBAL_گهڻائي_QCOM       0x8FA0
#جيڪڏهن_پورو /* GL_QCOM_perfmon_global_mode */

#جيڪڏهن_وصف_نه_ٿيل GL_QCOM_tiled_rendering
#وصف_ڪريو GL_QCOM_tiled_rendering 1
#وصف_ڪريو GL_COLOR_بفر_BIT0_QCOM         0x00000001
#وصف_ڪريو GL_COLOR_بفر_BIT1_QCOM         0x00000002
#وصف_ڪريو GL_COLOR_بفر_BIT2_QCOM         0x00000004
#وصف_ڪريو GL_COLOR_بفر_BIT3_QCOM         0x00000008
#وصف_ڪريو GL_COLOR_بفر_BIT4_QCOM         0x00000010
#وصف_ڪريو GL_COLOR_بفر_BIT5_QCOM         0x00000020
#وصف_ڪريو GL_COLOR_بفر_BIT6_QCOM         0x00000040
#وصف_ڪريو GL_COLOR_بفر_BIT7_QCOM         0x00000080
#وصف_ڪريو GL_اونهائي_بفر_BIT0_QCOM         0x00000100
#وصف_ڪريو GL_اونهائي_بفر_BIT1_QCOM         0x00000200
#وصف_ڪريو GL_اونهائي_بفر_BIT2_QCOM         0x00000400
#وصف_ڪريو GL_اونهائي_بفر_BIT3_QCOM         0x00000800
#وصف_ڪريو GL_اونهائي_بفر_BIT4_QCOM         0x00001000
#وصف_ڪريو GL_اونهائي_بفر_BIT5_QCOM         0x00002000
#وصف_ڪريو GL_اونهائي_بفر_BIT6_QCOM         0x00004000
#وصف_ڪريو GL_اونهائي_بفر_BIT7_QCOM         0x00008000
#وصف_ڪريو GL_STENCIL_بفر_BIT0_QCOM       0x00010000
#وصف_ڪريو GL_STENCIL_بفر_BIT1_QCOM       0x00020000
#وصف_ڪريو GL_STENCIL_بفر_BIT2_QCOM       0x00040000
#وصف_ڪريو GL_STENCIL_بفر_BIT3_QCOM       0x00080000
#وصف_ڪريو GL_STENCIL_بفر_BIT4_QCOM       0x00100000
#وصف_ڪريو GL_STENCIL_بفر_BIT5_QCOM       0x00200000
#وصف_ڪريو GL_STENCIL_بفر_BIT6_QCOM       0x00400000
#وصف_ڪريو GL_STENCIL_بفر_BIT7_QCOM       0x00800000
#وصف_ڪريو GL_MULTISAMPLE_بفر_BIT0_QCOM   0x01000000
#وصف_ڪريو GL_MULTISAMPLE_بفر_BIT1_QCOM   0x02000000
#وصف_ڪريو GL_MULTISAMPLE_بفر_BIT2_QCOM   0x04000000
#وصف_ڪريو GL_MULTISAMPLE_بفر_BIT3_QCOM   0x08000000
#وصف_ڪريو GL_MULTISAMPLE_بفر_BIT4_QCOM   0x10000000
#وصف_ڪريو GL_MULTISAMPLE_بفر_BIT5_QCOM   0x20000000
#وصف_ڪريو GL_MULTISAMPLE_بفر_BIT6_QCOM   0x40000000
#وصف_ڪريو GL_MULTISAMPLE_بفر_BIT7_QCOM   0x80000000
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTARTTILINGQCOMPROC) (GLuint x, GLuint y, GLuint ويڪر, GLuint اوچائي, GLbitfield preserve_نقاب);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENDTILINGQCOMPROC) (GLbitfield preserve_نقاب);
#جيڪڏهن_وصف_ٿيل GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY gl_شروعات_Tiling_QCOM (GLuint x, GLuint y, GLuint ويڪر, GLuint اوچائي, GLbitfield preserve_نقاب);
GL_API فراغ GL_APIENTRY gl_پڇاڙي_Tiling_QCOM (GLbitfield preserve_نقاب);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_QCOM_tiled_rendering */

#جيڪڏهن_وصف_نه_ٿيل GL_QCOM_writeonly_rendering
#وصف_ڪريو GL_QCOM_writeonly_rendering 1
#وصف_ڪريو GL_WRITEONLY_RENDERING_QCOM       0x8823
#جيڪڏهن_پورو /* GL_QCOM_writeonly_rendering */

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو
