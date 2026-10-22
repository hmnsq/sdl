#ifndef __gles1_glext_h_
#define __gles1_glext_h_ 1

#ifdef __cplusplus
خارجي "C" {
#endif

/*
** Copyright 2013-2026 The Khronos Group Inc.
** SPDX-License-Identifier: MIT
**
** This header is generated from the Khronos OpenGL / OpenGL ES XML
** API Registry. The current version of the Registry, generator scripts
** used to make the header, and the header can be found at
**   https://github.com/KhronosGroup/OpenGL-Registry
*/

#ifndef GL_APIENTRYP
#define GL_APIENTRYP GL_APIENTRY*
#endif

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

#ifndef GL_KHR_debug
#define GL_KHR_debug 1
#endif /* GL_KHR_debug */

#ifndef GL_OES_EGL_image
#define GL_OES_EGL_image 1
تعريفنوع فراغ *GLeglImageOES;
تعريفنوع فراغ (GL_APIENTRYP PFNGLEGLIMAGETARGETTEXTURE2DOESPROC) (GLenum target, GLeglImageOES image);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEGLIMAGETARGETRENDERBUFFERSTORAGEOESPROC) (GLenum target, GLeglImageOES image);
#ifdef GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glEGLImageTargetTexture2DOES (GLenum target, GLeglImageOES image);
GL_API فراغ GL_APIENTRY glEGLImageTargetRenderbufferStorageOES (GLenum target, GLeglImageOES image);
#endif
#endif /* GL_OES_EGL_image */

#ifndef GL_OES_EGL_image_external
#define GL_OES_EGL_image_external 1
#define GL_TEXTURE_EXTERNAL_OES           0x8D65
#define GL_TEXTURE_BINDING_EXTERNAL_OES   0x8D67
#define GL_REQUIRED_TEXTURE_IMAGE_UNITS_OES 0x8D68
#endif /* GL_OES_EGL_image_external */

#ifndef GL_OES_blend_equation_separate
#define GL_OES_blend_equation_separate 1
#define GL_BLEND_EQUATION_RGB_OES         0x8009
#define GL_BLEND_EQUATION_ALPHA_OES       0x883D
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEOESPROC) (GLenum modeRGB, GLenum modeAlpha);
#ifdef GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glBlendEquationSeparateOES (GLenum modeRGB, GLenum modeAlpha);
#endif
#endif /* GL_OES_blend_equation_separate */

#ifndef GL_OES_blend_func_separate
#define GL_OES_blend_func_separate 1
#define GL_BLEND_DST_RGB_OES              0x80C8
#define GL_BLEND_SRC_RGB_OES              0x80C9
#define GL_BLEND_DST_ALPHA_OES            0x80CA
#define GL_BLEND_SRC_ALPHA_OES            0x80CB
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEOESPROC) (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
#ifdef GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glBlendFuncSeparateOES (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
#endif
#endif /* GL_OES_blend_func_separate */

#ifndef GL_OES_blend_subtract
#define GL_OES_blend_subtract 1
#define GL_BLEND_EQUATION_OES             0x8009
#define GL_FUNC_ADD_OES                   0x8006
#define GL_FUNC_SUBTRACT_OES              0x800A
#define GL_FUNC_REVERSE_SUBTRACT_OES      0x800B
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONOESPROC) (GLenum mode);
#ifdef GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glBlendEquationOES (GLenum mode);
#endif
#endif /* GL_OES_blend_subtract */

#ifndef GL_OES_byte_coordinates
#define GL_OES_byte_coordinates 1
#endif /* GL_OES_byte_coordinates */

#ifndef GL_OES_compressed_ETC1_RGB8_sub_texture
#define GL_OES_compressed_ETC1_RGB8_sub_texture 1
#endif /* GL_OES_compressed_ETC1_RGB8_sub_texture */

#ifndef GL_OES_compressed_ETC1_RGB8_texture
#define GL_OES_compressed_ETC1_RGB8_texture 1
#define GL_ETC1_RGB8_OES                  0x8D64
#endif /* GL_OES_compressed_ETC1_RGB8_texture */

#ifndef GL_OES_depth24
#define GL_OES_depth24 1
#define GL_DEPTH_COMPONENT24_OES          0x81A6
#endif /* GL_OES_depth24 */

#ifndef GL_OES_depth32
#define GL_OES_depth32 1
#define GL_DEPTH_COMPONENT32_OES          0x81A7
#endif /* GL_OES_depth32 */

#ifndef GL_OES_draw_texture
#define GL_OES_draw_texture 1
#define GL_TEXTURE_CROP_RECT_OES          0x8B9D
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXSOESPROC) (GLshort x, GLshort y, GLshort z, GLshort width, GLshort height);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXIOESPROC) (GLint x, GLint y, GLint z, GLint width, GLint height);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXXOESPROC) (GLfixed x, GLfixed y, GLfixed z, GLfixed width, GLfixed height);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXSVOESPROC) (ثابت GLshort *coords);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXIVOESPROC) (ثابت GLint *coords);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXXVOESPROC) (ثابت GLfixed *coords);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXFOESPROC) (GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXFVOESPROC) (ثابت GLfloat *coords);
#ifdef GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glDrawTexsOES (GLshort x, GLshort y, GLshort z, GLshort width, GLshort height);
GL_API فراغ GL_APIENTRY glDrawTexiOES (GLint x, GLint y, GLint z, GLint width, GLint height);
GL_API فراغ GL_APIENTRY glDrawTexxOES (GLfixed x, GLfixed y, GLfixed z, GLfixed width, GLfixed height);
GL_API فراغ GL_APIENTRY glDrawTexsvOES (ثابت GLshort *coords);
GL_API فراغ GL_APIENTRY glDrawTexivOES (ثابت GLint *coords);
GL_API فراغ GL_APIENTRY glDrawTexxvOES (ثابت GLfixed *coords);
GL_API فراغ GL_APIENTRY glDrawTexfOES (GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height);
GL_API فراغ GL_APIENTRY glDrawTexfvOES (ثابت GLfloat *coords);
#endif
#endif /* GL_OES_draw_texture */

#ifndef GL_OES_element_index_uint
#define GL_OES_element_index_uint 1
#define GL_UNSIGNED_INT                   0x1405
#endif /* GL_OES_element_index_uint */

#ifndef GL_OES_extended_matrix_palette
#define GL_OES_extended_matrix_palette 1
#endif /* GL_OES_extended_matrix_palette */

#ifndef GL_OES_fbo_render_mipmap
#define GL_OES_fbo_render_mipmap 1
#endif /* GL_OES_fbo_render_mipmap */

#ifndef GL_OES_fixed_point
#define GL_OES_fixed_point 1
#define GL_FIXED_OES                      0x140C
تعريفنوع فراغ (GL_APIENTRYP PFNGLALPHAFUNCXOESPROC) (GLenum func, GLfixed ref);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARCOLORXOESPROC) (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARDEPTHXOESPROC) (GLfixed depth);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLIPPLANEXOESPROC) (GLenum plane, ثابت GLfixed *equation);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOLOR4XOESPROC) (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHRANGEXOESPROC) (GLfixed n, GLfixed f);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFOGXOESPROC) (GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFOGXVOESPROC) (GLenum pname, ثابت GLfixed *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRUSTUMXOESPROC) (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETCLIPPLANEXOESPROC) (GLenum plane, GLfixed *equation);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFIXEDVOESPROC) (GLenum pname, GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXENVXVOESPROC) (GLenum target, GLenum pname, GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXPARAMETERXVOESPROC) (GLenum target, GLenum pname, GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLIGHTMODELXOESPROC) (GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLIGHTMODELXVOESPROC) (GLenum pname, ثابت GLfixed *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLIGHTXOESPROC) (GLenum light, GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLIGHTXVOESPROC) (GLenum light, GLenum pname, ثابت GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLINEWIDTHXOESPROC) (GLfixed width);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLOADMATRIXXOESPROC) (ثابت GLfixed *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATERIALXOESPROC) (GLenum face, GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATERIALXVOESPROC) (GLenum face, GLenum pname, ثابت GLfixed *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTMATRIXXOESPROC) (ثابت GLfixed *m);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTITEXCOORD4XOESPROC) (GLenum texture, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
تعريفنوع فراغ (GL_APIENTRYP PFNGLNORMAL3XOESPROC) (GLfixed nx, GLfixed ny, GLfixed nz);
تعريفنوع فراغ (GL_APIENTRYP PFNGLORTHOXOESPROC) (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOINTPARAMETERXVOESPROC) (GLenum pname, ثابت GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOINTSIZEXOESPROC) (GLfixed size);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOLYGONOFFSETXOESPROC) (GLfixed factor, GLfixed units);
تعريفنوع فراغ (GL_APIENTRYP PFNGLROTATEXOESPROC) (GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCALEXOESPROC) (GLfixed x, GLfixed y, GLfixed z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXENVXOESPROC) (GLenum target, GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXENVXVOESPROC) (GLenum target, GLenum pname, ثابت GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERXOESPROC) (GLenum target, GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERXVOESPROC) (GLenum target, GLenum pname, ثابت GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTRANSLATEXOESPROC) (GLfixed x, GLfixed y, GLfixed z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETLIGHTXVOESPROC) (GLenum light, GLenum pname, GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETMATERIALXVOESPROC) (GLenum face, GLenum pname, GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOINTPARAMETERXOESPROC) (GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLECOVERAGEXOESPROC) (GLclampx نيلاي, GLboolean invert);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXGENXVOESPROC) (GLenum coord, GLenum pname, GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXGENXOESPROC) (GLenum coord, GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXGENXVOESPROC) (GLenum coord, GLenum pname, ثابت GLfixed *params);
#ifdef GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glAlphaFuncxOES (GLenum func, GLfixed ref);
GL_API فراغ GL_APIENTRY glClearColorxOES (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GL_API فراغ GL_APIENTRY glClearDepthxOES (GLfixed depth);
GL_API فراغ GL_APIENTRY glClipPlanexOES (GLenum plane, ثابت GLfixed *equation);
GL_API فراغ GL_APIENTRY glColor4xOES (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GL_API فراغ GL_APIENTRY glDepthRangexOES (GLfixed n, GLfixed f);
GL_API فراغ GL_APIENTRY glFogxOES (GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glFogxvOES (GLenum pname, ثابت GLfixed *param);
GL_API فراغ GL_APIENTRY glFrustumxOES (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
GL_API فراغ GL_APIENTRY glGetClipPlanexOES (GLenum plane, GLfixed *equation);
GL_API فراغ GL_APIENTRY glGetFixedvOES (GLenum pname, GLfixed *params);
GL_API فراغ GL_APIENTRY glGetTexEnvxvOES (GLenum target, GLenum pname, GLfixed *params);
GL_API فراغ GL_APIENTRY glGetTexParameterxvOES (GLenum target, GLenum pname, GLfixed *params);
GL_API فراغ GL_APIENTRY glLightModelxOES (GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glLightModelxvOES (GLenum pname, ثابت GLfixed *param);
GL_API فراغ GL_APIENTRY glLightxOES (GLenum light, GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glLightxvOES (GLenum light, GLenum pname, ثابت GLfixed *params);
GL_API فراغ GL_APIENTRY gl_باريس_Widthx_OES (GLfixed width);
GL_API فراغ GL_APIENTRY glLoadMatrixxOES (ثابت GLfixed *m);
GL_API فراغ GL_APIENTRY glMaterialxOES (GLenum face, GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glMaterialxvOES (GLenum face, GLenum pname, ثابت GLfixed *param);
GL_API فراغ GL_APIENTRY glMultMatrixxOES (ثابت GLfixed *m);
GL_API فراغ GL_APIENTRY glMultiTexCoord4xOES (GLenum texture, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
GL_API فراغ GL_APIENTRY glNormal3xOES (GLfixed nx, GLfixed ny, GLfixed nz);
GL_API فراغ GL_APIENTRY glOrthoxOES (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
GL_API فراغ GL_APIENTRY glPointParameterxvOES (GLenum pname, ثابت GLfixed *params);
GL_API فراغ GL_APIENTRY glPointSizexOES (GLfixed size);
GL_API فراغ GL_APIENTRY glPolygonOffsetxOES (GLfixed factor, GLfixed units);
GL_API فراغ GL_APIENTRY glRotatexOES (GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
GL_API فراغ GL_APIENTRY glScalexOES (GLfixed x, GLfixed y, GLfixed z);
GL_API فراغ GL_APIENTRY glTexEnvxOES (GLenum target, GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glTexEnvxvOES (GLenum target, GLenum pname, ثابت GLfixed *params);
GL_API فراغ GL_APIENTRY glTexParameterxOES (GLenum target, GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glTexParameterxvOES (GLenum target, GLenum pname, ثابت GLfixed *params);
GL_API فراغ GL_APIENTRY glTranslatexOES (GLfixed x, GLfixed y, GLfixed z);
GL_API فراغ GL_APIENTRY glGetLightxvOES (GLenum light, GLenum pname, GLfixed *params);
GL_API فراغ GL_APIENTRY glGetMaterialxvOES (GLenum face, GLenum pname, GLfixed *params);
GL_API فراغ GL_APIENTRY glPointParameterxOES (GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glSampleCoveragexOES (GLclampx نيلاي, GLboolean invert);
GL_API فراغ GL_APIENTRY glGetTexGenxvOES (GLenum coord, GLenum pname, GLfixed *params);
GL_API فراغ GL_APIENTRY glTexGenxOES (GLenum coord, GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glTexGenxvOES (GLenum coord, GLenum pname, ثابت GLfixed *params);
#endif
#endif /* GL_OES_fixed_point */

#ifndef GL_OES_framebuffer_object
#define GL_OES_framebuffer_object 1
#define GL_NONE_OES                       0
#define GL_FRAMEBUFFER_OES                0x8D40
#define GL_RENDERBUFFER_OES               0x8D41
#define GL_RGBA4_OES                      0x8056
#define GL_RGB5_A1_OES                    0x8057
#define GL_RGB565_OES                     0x8D62
#define GL_DEPTH_COMPONENT16_OES          0x81A5
#define GL_RENDERBUFFER_WIDTH_OES         0x8D42
#define GL_RENDERBUFFER_HEIGHT_OES        0x8D43
#define GL_RENDERBUFFER_INTERNAL_FORMAT_OES 0x8D44
#define GL_RENDERBUFFER_RED_SIZE_OES      0x8D50
#define GL_RENDERBUFFER_GREEN_SIZE_OES    0x8D51
#define GL_RENDERBUFFER_BLUE_SIZE_OES     0x8D52
#define GL_RENDERBUFFER_ALPHA_SIZE_OES    0x8D53
#define GL_RENDERBUFFER_DEPTH_SIZE_OES    0x8D54
#define GL_RENDERBUFFER_STENCIL_SIZE_OES  0x8D55
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_OES 0x8CD0
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_OES 0x8CD1
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_OES 0x8CD2
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_OES 0x8CD3
#define GL_COLOR_ATTACHMENT0_OES          0x8CE0
#define GL_DEPTH_ATTACHMENT_OES           0x8D00
#define GL_STENCIL_ATTACHMENT_OES         0x8D20
#define GL_FRAMEBUFFER_COMPLETE_OES       0x8CD5
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_OES 0x8CD6
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_OES 0x8CD7
#define GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_OES 0x8CD9
#define GL_FRAMEBUFFER_INCOMPLETE_FORMATS_OES 0x8CDA
#define GL_FRAMEBUFFER_UNSUPPORTED_OES    0x8CDD
#define GL_FRAMEBUFFER_BINDING_OES        0x8CA6
#define GL_RENDERBUFFER_BINDING_OES       0x8CA7
#define GL_MAX_RENDERBUFFER_SIZE_OES      0x84E8
#define GL_INVALID_FRAMEBUFFER_OPERATION_OES 0x0506
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISRENDERBUFFEROESPROC) (GLuint renderbuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDRENDERBUFFEROESPROC) (GLenum target, GLuint renderbuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETERENDERBUFFERSOESPROC) (GLsizei n, ثابت GLuint *renderbuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENRENDERBUFFERSOESPROC) (GLsizei n, GLuint *renderbuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEOESPROC) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVOESPROC) (GLenum target, GLenum pname, GLint *params);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISFRAMEBUFFEROESPROC) (GLuint framebuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDFRAMEBUFFEROESPROC) (GLenum target, GLuint framebuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEFRAMEBUFFERSOESPROC) (GLsizei n, ثابت GLuint *framebuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENFRAMEBUFFERSOESPROC) (GLsizei n, GLuint *framebuffers);
تعريفنوع GLenum (GL_APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSOESPROC) (GLenum target);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFEROESPROC) (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DOESPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVOESPROC) (GLenum target, GLenum attachment, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENERATEMIPMAPOESPROC) (GLenum target);
#ifdef GL_GLEXT_PROTOTYPES
GL_API GLboolean GL_APIENTRY glIsRenderbufferOES (GLuint renderbuffer);
GL_API فراغ GL_APIENTRY glBindRenderbufferOES (GLenum target, GLuint renderbuffer);
GL_API فراغ GL_APIENTRY glDeleteRenderbuffersOES (GLsizei n, ثابت GLuint *renderbuffers);
GL_API فراغ GL_APIENTRY glGenRenderbuffersOES (GLsizei n, GLuint *renderbuffers);
GL_API فراغ GL_APIENTRY glRenderbufferStorageOES (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
GL_API فراغ GL_APIENTRY glGetRenderbufferParameterivOES (GLenum target, GLenum pname, GLint *params);
GL_API GLboolean GL_APIENTRY glIsFramebufferOES (GLuint framebuffer);
GL_API فراغ GL_APIENTRY glBindFramebufferOES (GLenum target, GLuint framebuffer);
GL_API فراغ GL_APIENTRY glDeleteFramebuffersOES (GLsizei n, ثابت GLuint *framebuffers);
GL_API فراغ GL_APIENTRY glGenFramebuffersOES (GLsizei n, GLuint *framebuffers);
GL_API GLenum GL_APIENTRY glCheckFramebufferStatusOES (GLenum target);
GL_API فراغ GL_APIENTRY glFramebufferRenderbufferOES (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
GL_API فراغ GL_APIENTRY glFramebufferTexture2DOES (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GL_API فراغ GL_APIENTRY glGetFramebufferAttachmentParameterivOES (GLenum target, GLenum attachment, GLenum pname, GLint *params);
GL_API فراغ GL_APIENTRY glGenerateMipmapOES (GLenum target);
#endif
#endif /* GL_OES_framebuffer_object */

#ifndef GL_OES_mapbuffer
#define GL_OES_mapbuffer 1
#define GL_WRITE_ONLY_OES                 0x88B9
#define GL_BUFFER_ACCESS_OES              0x88BB
#define GL_BUFFER_MAPPED_OES              0x88BC
#define GL_BUFFER_MAP_POINTER_OES         0x88BD
تعريفنوع فراغ *(GL_APIENTRYP PFNGLMAPBUFFEROESPROC) (GLenum target, GLenum access);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLUNMAPBUFFEROESPROC) (GLenum target);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETBUFFERPOINTERVOESPROC) (GLenum target, GLenum pname, فراغ **params);
#ifdef GL_GLEXT_PROTOTYPES
GL_API فراغ *GL_APIENTRY glMapBufferOES (GLenum target, GLenum access);
GL_API GLboolean GL_APIENTRY glUnmapBufferOES (GLenum target);
GL_API فراغ GL_APIENTRY glGetBufferPointervOES (GLenum target, GLenum pname, فراغ **params);
#endif
#endif /* GL_OES_mapbuffer */

#ifndef GL_OES_matrix_get
#define GL_OES_matrix_get 1
#define GL_MODELVIEW_MATRIX_FLOAT_AS_INT_BITS_OES 0x898D
#define GL_PROJECTION_MATRIX_FLOAT_AS_INT_BITS_OES 0x898E
#define GL_TEXTURE_MATRIX_FLOAT_AS_INT_BITS_OES 0x898F
#endif /* GL_OES_matrix_get */

#ifndef GL_OES_matrix_palette
#define GL_OES_matrix_palette 1
#define GL_MAX_VERTEX_UNITS_OES           0x86A4
#define GL_MAX_PALETTE_MATRICES_OES       0x8842
#define GL_MATRIX_PALETTE_OES             0x8840
#define GL_MATRIX_INDEX_ARRAY_OES         0x8844
#define GL_WEIGHT_ARRAY_OES               0x86AD
#define GL_CURRENT_PALETTE_MATRIX_OES     0x8843
#define GL_MATRIX_INDEX_ARRAY_SIZE_OES    0x8846
#define GL_MATRIX_INDEX_ARRAY_TYPE_OES    0x8847
#define GL_MATRIX_INDEX_ARRAY_STRIDE_OES  0x8848
#define GL_MATRIX_INDEX_ARRAY_POINTER_OES 0x8849
#define GL_MATRIX_INDEX_ARRAY_BUFFER_BINDING_OES 0x8B9E
#define GL_WEIGHT_ARRAY_SIZE_OES          0x86AB
#define GL_WEIGHT_ARRAY_TYPE_OES          0x86A9
#define GL_WEIGHT_ARRAY_STRIDE_OES        0x86AA
#define GL_WEIGHT_ARRAY_POINTER_OES       0x86AC
#define GL_WEIGHT_ARRAY_BUFFER_BINDING_OES 0x889E
تعريفنوع فراغ (GL_APIENTRYP PFNGLCURRENTPALETTEMATRIXOESPROC) (GLuint matrixpaletteindex);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLOADPALETTEFROMMODELVIEWMATRIXOESPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXINDEXPOINTEROESPROC) (GLint size, GLenum type, GLsizei stride, ثابت فراغ *pointer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLWEIGHTPOINTEROESPROC) (GLint size, GLenum type, GLsizei stride, ثابت فراغ *pointer);
#ifdef GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glCurrentPaletteMatrixOES (GLuint matrixpaletteindex);
GL_API فراغ GL_APIENTRY glLoadPaletteFromModelViewMatrixOES (فراغ);
GL_API فراغ GL_APIENTRY glMatrixIndexPointerOES (GLint size, GLenum type, GLsizei stride, ثابت فراغ *pointer);
GL_API فراغ GL_APIENTRY glWeightPointerOES (GLint size, GLenum type, GLsizei stride, ثابت فراغ *pointer);
#endif
#endif /* GL_OES_matrix_palette */

#ifndef GL_OES_packed_depth_stencil
#define GL_OES_packed_depth_stencil 1
#define GL_DEPTH_STENCIL_OES              0x84F9
#define GL_UNSIGNED_INT_24_8_OES          0x84FA
#define GL_DEPTH24_STENCIL8_OES           0x88F0
#endif /* GL_OES_packed_depth_stencil */

#ifndef GL_OES_query_matrix
#define GL_OES_query_matrix 1
تعريفنوع GLbitfield (GL_APIENTRYP PFNGLQUERYMATRIXXOESPROC) (GLfixed *mantissa, GLint *exponent);
#ifdef GL_GLEXT_PROTOTYPES
GL_API GLbitfield GL_APIENTRY glQueryMatrixxOES (GLfixed *mantissa, GLint *exponent);
#endif
#endif /* GL_OES_query_matrix */

#ifndef GL_OES_required_internalformat
#define GL_OES_required_internalformat 1
#define GL_ALPHA8_OES                     0x803C
#define GL_LUMINANCE4_ALPHA4_OES          0x8043
#define GL_LUMINANCE8_ALPHA8_OES          0x8045
#define GL_LUMINANCE8_OES                 0x8040
#define GL_RGB8_OES                       0x8051
#define GL_RGBA8_OES                      0x8058
#define GL_RGB10_EXT                      0x8052
#define GL_RGB10_A2_EXT                   0x8059
#endif /* GL_OES_required_internalformat */

#ifndef GL_OES_rgb8_rgba8
#define GL_OES_rgb8_rgba8 1
#endif /* GL_OES_rgb8_rgba8 */

#ifndef GL_OES_single_precision
#define GL_OES_single_precision 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARDEPTHFOESPROC) (GLclampf depth);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLIPPLANEFOESPROC) (GLenum plane, ثابت GLfloat *equation);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHRANGEFOESPROC) (GLclampf n, GLclampf f);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRUSTUMFOESPROC) (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETCLIPPLANEFOESPROC) (GLenum plane, GLfloat *equation);
تعريفنوع فراغ (GL_APIENTRYP PFNGLORTHOFOESPROC) (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
#ifdef GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glClearDepthfOES (GLclampf depth);
GL_API فراغ GL_APIENTRY glClipPlanefOES (GLenum plane, ثابت GLfloat *equation);
GL_API فراغ GL_APIENTRY glDepthRangefOES (GLclampf n, GLclampf f);
GL_API فراغ GL_APIENTRY glFrustumfOES (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
GL_API فراغ GL_APIENTRY glGetClipPlanefOES (GLenum plane, GLfloat *equation);
GL_API فراغ GL_APIENTRY glOrthofOES (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
#endif
#endif /* GL_OES_single_precision */

#ifndef GL_OES_stencil1
#define GL_OES_stencil1 1
#define GL_STENCIL_INDEX1_OES             0x8D46
#endif /* GL_OES_stencil1 */

#ifndef GL_OES_stencil4
#define GL_OES_stencil4 1
#define GL_STENCIL_INDEX4_OES             0x8D47
#endif /* GL_OES_stencil4 */

#ifndef GL_OES_stencil8
#define GL_OES_stencil8 1
#define GL_STENCIL_INDEX8_OES             0x8D48
#endif /* GL_OES_stencil8 */

#ifndef GL_OES_stencil_wrap
#define GL_OES_stencil_wrap 1
#define GL_INCR_WRAP_OES                  0x8507
#define GL_DECR_WRAP_OES                  0x8508
#endif /* GL_OES_stencil_wrap */

#ifndef GL_OES_surfaceless_context
#define GL_OES_surfaceless_context 1
#define GL_FRAMEBUFFER_UNDEFINED_OES      0x8219
#endif /* GL_OES_surfaceless_context */

#ifndef GL_OES_texture_cube_map
#define GL_OES_texture_cube_map 1
#define GL_NORMAL_MAP_OES                 0x8511
#define GL_REFLECTION_MAP_OES             0x8512
#define GL_TEXTURE_CUBE_MAP_OES           0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP_OES   0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X_OES 0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X_OES 0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y_OES 0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_OES 0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z_OES 0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_OES 0x851A
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE_OES  0x851C
#define GL_TEXTURE_GEN_MODE_OES           0x2500
#define GL_TEXTURE_GEN_STR_OES            0x8D60
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXGENFOESPROC) (GLenum coord, GLenum pname, GLfloat param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXGENFVOESPROC) (GLenum coord, GLenum pname, ثابت GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXGENIOESPROC) (GLenum coord, GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXGENIVOESPROC) (GLenum coord, GLenum pname, ثابت GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXGENFVOESPROC) (GLenum coord, GLenum pname, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXGENIVOESPROC) (GLenum coord, GLenum pname, GLint *params);
#ifdef GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glTexGenfOES (GLenum coord, GLenum pname, GLfloat param);
GL_API فراغ GL_APIENTRY glTexGenfvOES (GLenum coord, GLenum pname, ثابت GLfloat *params);
GL_API فراغ GL_APIENTRY glTexGeniOES (GLenum coord, GLenum pname, GLint param);
GL_API فراغ GL_APIENTRY glTexGenivOES (GLenum coord, GLenum pname, ثابت GLint *params);
GL_API فراغ GL_APIENTRY glGetTexGenfvOES (GLenum coord, GLenum pname, GLfloat *params);
GL_API فراغ GL_APIENTRY glGetTexGenivOES (GLenum coord, GLenum pname, GLint *params);
#endif
#endif /* GL_OES_texture_cube_map */

#ifndef GL_OES_texture_env_crossbar
#define GL_OES_texture_env_crossbar 1
#endif /* GL_OES_texture_env_crossbar */

#ifndef GL_OES_texture_mirrored_repeat
#define GL_OES_texture_mirrored_repeat 1
#define GL_MIRRORED_REPEAT_OES            0x8370
#endif /* GL_OES_texture_mirrored_repeat */

#ifndef GL_OES_texture_npot
#define GL_OES_texture_npot 1
#endif /* GL_OES_texture_npot */

#ifndef GL_OES_vertex_array_object
#define GL_OES_vertex_array_object 1
#define GL_VERTEX_ARRAY_BINDING_OES       0x85B5
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDVERTEXARRAYOESPROC) (GLuint array);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEVERTEXARRAYSOESPROC) (GLsizei n, ثابت GLuint *arrays);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENVERTEXARRAYSOESPROC) (GLsizei n, GLuint *arrays);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISVERTEXARRAYOESPROC) (GLuint array);
#ifdef GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glBindVertexArrayOES (GLuint array);
GL_API فراغ GL_APIENTRY glDeleteVertexArraysOES (GLsizei n, ثابت GLuint *arrays);
GL_API فراغ GL_APIENTRY glGenVertexArraysOES (GLsizei n, GLuint *arrays);
GL_API GLboolean GL_APIENTRY glIsVertexArrayOES (GLuint array);
#endif
#endif /* GL_OES_vertex_array_object */

#ifndef GL_AMD_compressed_3DC_texture
#define GL_AMD_compressed_3DC_texture 1
#define GL_3DC_X_AMD                      0x87F9
#define GL_3DC_XY_AMD                     0x87FA
#endif /* GL_AMD_compressed_3DC_texture */

#ifndef GL_AMD_compressed_ATC_texture
#define GL_AMD_compressed_ATC_texture 1
#define GL_ATC_RGB_AMD                    0x8C92
#define GL_ATC_RGBA_EXPLICIT_ALPHA_AMD    0x8C93
#define GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD 0x87EE
#endif /* GL_AMD_compressed_ATC_texture */

#ifndef GL_APPLE_copy_texture_levels
#define GL_APPLE_copy_texture_levels 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYTEXTURELEVELSAPPLEPROC) (GLuint destinationTexture, GLuint sourceTexture, GLint sourceBaseLevel, GLsizei source_Level_کيراءن);
#ifdef GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glCopyTextureLevelsAPPLE (GLuint destinationTexture, GLuint sourceTexture, GLint sourceBaseLevel, GLsizei source_Level_کيراءن);
#endif
#endif /* GL_APPLE_copy_texture_levels */

#ifndef GL_APPLE_framebuffer_multisample
#define GL_APPLE_framebuffer_multisample 1
#define GL_RENDERBUFFER_SAMPLES_APPLE     0x8CAB
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_APPLE 0x8D56
#define GL_MAX_SAMPLES_APPLE              0x8D57
#define GL_READ_FRAMEBUFFER_APPLE         0x8CA8
#define GL_DRAW_FRAMEBUFFER_APPLE         0x8CA9
#define GL_DRAW_FRAMEBUFFER_BINDING_APPLE 0x8CA6
#define GL_READ_FRAMEBUFFER_BINDING_APPLE 0x8CAA
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEAPPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRESOLVEMULTISAMPLEFRAMEBUFFERAPPLEPROC) (فراغ);
#ifdef GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glRenderbufferStorageMultisampleAPPLE (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
GL_API فراغ GL_APIENTRY glResolveMultisampleFramebufferAPPLE (فراغ);
#endif
#endif /* GL_APPLE_framebuffer_multisample */

#ifndef GL_APPLE_sync
#define GL_APPLE_sync 1
تعريفنوع بنية __GLsync *GLsync;
تعريفنوع khronos_uint64_t GLuint64;
تعريفنوع khronos_int64_t GLint64;
#define GL_SYNC_OBJECT_APPLE              0x8A53
#define GL_MAX_SERVER_WAIT_TIMEOUT_APPLE  0x9111
#define GL_OBJECT_TYPE_APPLE              0x9112
#define GL_SYNC_CONDITION_APPLE           0x9113
#define GL_SYNC_STATUS_APPLE              0x9114
#define GL_SYNC_FLAGS_APPLE               0x9115
#define GL_SYNC_FENCE_APPLE               0x9116
#define GL_SYNC_GPU_COMMANDS_COMPLETE_APPLE 0x9117
#define GL_UNSIGNALED_APPLE               0x9118
#define GL_SIGNALED_APPLE                 0x9119
#define GL_ALREADY_SIGNALED_APPLE         0x911A
#define GL_TIMEOUT_EXPIRED_APPLE          0x911B
#define GL_CONDITION_SATISFIED_APPLE      0x911C
#define GL_WAIT_FAILED_APPLE              0x911D
#define GL_SYNC_FLUSH_COMMANDS_BIT_APPLE  0x00000001
#define GL_TIMEOUT_IGNORED_APPLE          0xFFFFFFFFFFFFFFFFull
تعريفنوع GLsync (GL_APIENTRYP PFNGLFENCESYNCAPPLEPROC) (GLenum condition, GLbitfield flags);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISSYNCAPPLEPROC) (GLsync sync);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETESYNCAPPLEPROC) (GLsync sync);
تعريفنوع GLenum (GL_APIENTRYP PFNGLCLIENTWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
تعريفنوع فراغ (GL_APIENTRYP PFNGLWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTEGER64VAPPLEPROC) (GLenum pname, GLint64 *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSYNCIVAPPLEPROC) (GLsync sync, GLenum pname, GLsizei کيراءن, GLsizei *length, GLint *نيلاي_سموا);
#ifdef GL_GLEXT_PROTOTYPES
GL_API GLsync GL_APIENTRY glFenceSyncAPPLE (GLenum condition, GLbitfield flags);
GL_API GLboolean GL_APIENTRY glIsSyncAPPLE (GLsync sync);
GL_API فراغ GL_APIENTRY glDeleteSyncAPPLE (GLsync sync);
GL_API GLenum GL_APIENTRY glClientWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_API فراغ GL_APIENTRY glWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_API فراغ GL_APIENTRY glGetInteger64vAPPLE (GLenum pname, GLint64 *params);
GL_API فراغ GL_APIENTRY glGetSyncivAPPLE (GLsync sync, GLenum pname, GLsizei کيراءن, GLsizei *length, GLint *نيلاي_سموا);
#endif
#endif /* GL_APPLE_sync */

#ifndef GL_APPLE_texture_2D_limited_npot
#define GL_APPLE_texture_2D_limited_npot 1
#endif /* GL_APPLE_texture_2D_limited_npot */

#ifndef GL_APPLE_texture_format_BGRA8888
#define GL_APPLE_texture_format_BGRA8888 1
#define GL_BGRA_EXT                       0x80E1
#define GL_BGRA8_EXT                      0x93A1
#endif /* GL_APPLE_texture_format_BGRA8888 */

#ifndef GL_APPLE_texture_max_level
#define GL_APPLE_texture_max_level 1
#define GL_TEXTURE_MAX_LEVEL_APPLE        0x813D
#endif /* GL_APPLE_texture_max_level */

#ifndef GL_ARM_rgba8
#define GL_ARM_rgba8 1
#endif /* GL_ARM_rgba8 */

#ifndef GL_EXT_blend_minmax
#define GL_EXT_blend_minmax 1
#define GL_MIN_EXT                        0x8007
#define GL_MAX_EXT                        0x8008
#endif /* GL_EXT_blend_minmax */

#ifndef GL_EXT_debug_marker
#define GL_EXT_debug_marker 1
تعريفنوع حرف GLchar;
تعريفنوع فراغ (GL_APIENTRYP PFNGLINSERTEVENTMARKEREXTPROC) (GLsizei length, ثابت GLchar *marker);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPUSHGROUPMARKEREXTPROC) (GLsizei length, ثابت GLchar *marker);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOPGROUPMARKEREXTPROC) (فراغ);
#ifdef GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY gl_سيسيڤ_Event_Marker_EXT (GLsizei length, ثابت GLchar *marker);
GL_API فراغ GL_APIENTRY gl_تولق_Group_Marker_EXT (GLsizei length, ثابت GLchar *marker);
GL_API فراغ GL_APIENTRY gl_کلوار_Group_Marker_EXT (فراغ);
#endif
#endif /* GL_EXT_debug_marker */

#ifndef GL_EXT_discard_framebuffer
#define GL_EXT_discard_framebuffer 1
#define GL_COLOR_EXT                      0x1800
#define GL_DEPTH_EXT                      0x1801
#define GL_STENCIL_EXT                    0x1802
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISCARDFRAMEBUFFEREXTPROC) (GLenum target, GLsizei اڠک_Attachments, ثابت GLenum *attachments);
#ifdef GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glDiscardFramebufferEXT (GLenum target, GLsizei اڠک_Attachments, ثابت GLenum *attachments);
#endif
#endif /* GL_EXT_discard_framebuffer */

#ifndef GL_EXT_map_buffer_range
#define GL_EXT_map_buffer_range 1
#define GL_MAP_READ_BIT_EXT               0x0001
#define GL_MAP_WRITE_BIT_EXT              0x0002
#define GL_MAP_INVALIDATE_RANGE_BIT_EXT   0x0004
#define GL_MAP_INVALIDATE_BUFFER_BIT_EXT  0x0008
#define GL_MAP_FLUSH_EXPLICIT_BIT_EXT     0x0010
#define GL_MAP_UNSYNCHRONIZED_BIT_EXT     0x0020
تعريفنوع فراغ *(GL_APIENTRYP PFNGLMAPBUFFERRANGEEXTPROC) (GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEEXTPROC) (GLenum target, GLintptr offset, GLsizeiptr length);
#ifdef GL_GLEXT_PROTOTYPES
GL_API فراغ *GL_APIENTRY glMapBufferRangeEXT (GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
GL_API فراغ GL_APIENTRY glFlushMappedBufferRangeEXT (GLenum target, GLintptr offset, GLsizeiptr length);
#endif
#endif /* GL_EXT_map_buffer_range */

#ifndef GL_EXT_multi_draw_arrays
#define GL_EXT_multi_draw_arrays 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWARRAYSEXTPROC) (GLenum mode, ثابت GLint *first, ثابت GLsizei *کيراءن, GLsizei primcount);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSEXTPROC) (GLenum mode, ثابت GLsizei *کيراءن, GLenum type, ثابت فراغ *ثابت*indices, GLsizei primcount);
#ifdef GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glMultiDrawArraysEXT (GLenum mode, ثابت GLint *first, ثابت GLsizei *کيراءن, GLsizei primcount);
GL_API فراغ GL_APIENTRY glMultiDrawElementsEXT (GLenum mode, ثابت GLsizei *کيراءن, GLenum type, ثابت فراغ *ثابت*indices, GLsizei primcount);
#endif
#endif /* GL_EXT_multi_draw_arrays */

#ifndef GL_EXT_multisampled_render_to_texture
#define GL_EXT_multisampled_render_to_texture 1
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SAMPLES_EXT 0x8D6C
#define GL_RENDERBUFFER_SAMPLES_EXT       0x8CAB
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT 0x8D56
#define GL_MAX_SAMPLES_EXT                0x8D57
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEEXTPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#ifdef GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glRenderbufferStorageMultisampleEXT (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
GL_API فراغ GL_APIENTRY glFramebufferTexture2DMultisampleEXT (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#endif
#endif /* GL_EXT_multisampled_render_to_texture */

#ifndef GL_EXT_read_format_bgra
#define GL_EXT_read_format_bgra 1
#define GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT 0x8365
#define GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT 0x8366
#endif /* GL_EXT_read_format_bgra */

#ifndef GL_EXT_robustness
#define GL_EXT_robustness 1
#define GL_GUILTY_CONTEXT_RESET_EXT       0x8253
#define GL_INNOCENT_CONTEXT_RESET_EXT     0x8254
#define GL_UNKNOWN_CONTEXT_RESET_EXT      0x8255
#define GL_CONTEXT_ROBUST_ACCESS_EXT      0x90F3
#define GL_RESET_NOTIFICATION_STRATEGY_EXT 0x8256
#define GL_LOSE_CONTEXT_ON_RESET_EXT      0x8252
#define GL_NO_RESET_NOTIFICATION_EXT      0x8261
تعريفنوع GLenum (GL_APIENTRYP PFNGLGETGRAPHICSRESETSTATUSEXTPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLREADNPIXELSEXTPROC) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, فراغ *data);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNUNIFORMFVEXTPROC) (GLuint program, GLint location, GLsizei bufSize, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNUNIFORMIVEXTPROC) (GLuint program, GLint location, GLsizei bufSize, GLint *params);
#ifdef GL_GLEXT_PROTOTYPES
GL_API GLenum GL_APIENTRY glGetGraphicsResetStatusEXT (فراغ);
GL_API فراغ GL_APIENTRY glReadnPixelsEXT (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, فراغ *data);
GL_API فراغ GL_APIENTRY glGetnUniformfvEXT (GLuint program, GLint location, GLsizei bufSize, GLfloat *params);
GL_API فراغ GL_APIENTRY glGetnUniformivEXT (GLuint program, GLint location, GLsizei bufSize, GLint *params);
#endif
#endif /* GL_EXT_robustness */

#ifndef GL_EXT_sRGB
#define GL_EXT_sRGB 1
#define GL_SRGB_EXT                       0x8C40
#define GL_SRGB_ALPHA_EXT                 0x8C42
#define GL_SRGB8_ALPHA8_EXT               0x8C43
#define GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING_EXT 0x8210
#endif /* GL_EXT_sRGB */

#ifndef GL_EXT_texture_compression_dxt1
#define GL_EXT_texture_compression_dxt1 1
#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT   0x83F0
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT  0x83F1
#endif /* GL_EXT_texture_compression_dxt1 */

#ifndef GL_EXT_texture_filter_anisotropic
#define GL_EXT_texture_filter_anisotropic 1
#define GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#endif /* GL_EXT_texture_filter_anisotropic */

#ifndef GL_EXT_texture_format_BGRA8888
#define GL_EXT_texture_format_BGRA8888 1
#endif /* GL_EXT_texture_format_BGRA8888 */

#ifndef GL_EXT_texture_lod_bias
#define GL_EXT_texture_lod_bias 1
#define GL_MAX_TEXTURE_LOD_BIAS_EXT       0x84FD
#define GL_TEXTURE_FILTER_CONTROL_EXT     0x8500
#define GL_TEXTURE_LOD_BIAS_EXT           0x8501
#endif /* GL_EXT_texture_lod_bias */

#ifndef GL_EXT_texture_storage
#define GL_EXT_texture_storage 1
#define GL_TEXTURE_IMMUTABLE_FORMAT_EXT   0x912F
#define GL_ALPHA8_EXT                     0x803C
#define GL_LUMINANCE8_EXT                 0x8040
#define GL_LUMINANCE8_ALPHA8_EXT          0x8045
#define GL_RGBA32F_EXT                    0x8814
#define GL_RGB32F_EXT                     0x8815
#define GL_ALPHA32F_EXT                   0x8816
#define GL_LUMINANCE32F_EXT               0x8818
#define GL_LUMINANCE_ALPHA32F_EXT         0x8819
#define GL_RGBA16F_EXT                    0x881A
#define GL_RGB16F_EXT                     0x881B
#define GL_ALPHA16F_EXT                   0x881C
#define GL_LUMINANCE16F_EXT               0x881E
#define GL_LUMINANCE_ALPHA16F_EXT         0x881F
#define GL_R8_EXT                         0x8229
#define GL_RG8_EXT                        0x822B
#define GL_R32F_EXT                       0x822E
#define GL_RG32F_EXT                      0x8230
#define GL_R16F_EXT                       0x822D
#define GL_RG16F_EXT                      0x822F
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE1DEXTPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE2DEXTPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE3DEXTPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGE1DEXTPROC) (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGE2DEXTPROC) (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGE3DEXTPROC) (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
#ifdef GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glTexStorage1DEXT (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
GL_API فراغ GL_APIENTRY glTexStorage2DEXT (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
GL_API فراغ GL_APIENTRY glTexStorage3DEXT (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
GL_API فراغ GL_APIENTRY glTextureStorage1DEXT (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
GL_API فراغ GL_APIENTRY glTextureStorage2DEXT (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
GL_API فراغ GL_APIENTRY glTextureStorage3DEXT (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
#endif
#endif /* GL_EXT_texture_storage */

#ifndef GL_IMG_multisampled_render_to_texture
#define GL_IMG_multisampled_render_to_texture 1
#define GL_RENDERBUFFER_SAMPLES_IMG       0x9133
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_IMG 0x9134
#define GL_MAX_SAMPLES_IMG                0x9135
#define GL_TEXTURE_SAMPLES_IMG            0x9136
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEIMGPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEIMGPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#ifdef GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glRenderbufferStorageMultisampleIMG (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
GL_API فراغ GL_APIENTRY glFramebufferTexture2DMultisampleIMG (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#endif
#endif /* GL_IMG_multisampled_render_to_texture */

#ifndef GL_IMG_read_format
#define GL_IMG_read_format 1
#define GL_BGRA_IMG                       0x80E1
#define GL_UNSIGNED_SHORT_4_4_4_4_REV_IMG 0x8365
#endif /* GL_IMG_read_format */

#ifndef GL_IMG_texture_compression_pvrtc
#define GL_IMG_texture_compression_pvrtc 1
#define GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG 0x8C00
#define GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG 0x8C01
#define GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG 0x8C02
#define GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG 0x8C03
#endif /* GL_IMG_texture_compression_pvrtc */

#ifndef GL_IMG_texture_env_enhanced_fixed_function
#define GL_IMG_texture_env_enhanced_fixed_function 1
#define GL_MODULATE_COLOR_IMG             0x8C04
#define GL_RECIP_ADD_SIGNED_ALPHA_IMG     0x8C05
#define GL_TEXTURE_ALPHA_MODULATE_IMG     0x8C06
#define GL_FACTOR_ALPHA_MODULATE_IMG      0x8C07
#define GL_FRAGMENT_ALPHA_MODULATE_IMG    0x8C08
#define GL_ADD_BLEND_IMG                  0x8C09
#define GL_DOT3_RGBA_IMG                  0x86AF
#endif /* GL_IMG_texture_env_enhanced_fixed_function */

#ifndef GL_IMG_user_clip_plane
#define GL_IMG_user_clip_plane 1
#define GL_CLIP_PLANE0_IMG                0x3000
#define GL_CLIP_PLANE1_IMG                0x3001
#define GL_CLIP_PLANE2_IMG                0x3002
#define GL_CLIP_PLANE3_IMG                0x3003
#define GL_CLIP_PLANE4_IMG                0x3004
#define GL_CLIP_PLANE5_IMG                0x3005
#define GL_MAX_CLIP_PLANES_IMG            0x0D32
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLIPPLANEFIMGPROC) (GLenum p, ثابت GLfloat *eqn);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLIPPLANEXIMGPROC) (GLenum p, ثابت GLfixed *eqn);
#ifdef GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glClipPlanefIMG (GLenum p, ثابت GLfloat *eqn);
GL_API فراغ GL_APIENTRY glClipPlanexIMG (GLenum p, ثابت GLfixed *eqn);
#endif
#endif /* GL_IMG_user_clip_plane */

#ifndef GL_NV_fence
#define GL_NV_fence 1
#define GL_ALL_COMPLETED_NV               0x84F2
#define GL_FENCE_STATUS_NV                0x84F3
#define GL_FENCE_CONDITION_NV             0x84F4
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEFENCESNVPROC) (GLsizei n, ثابت GLuint *fences);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENFENCESNVPROC) (GLsizei n, GLuint *fences);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISFENCENVPROC) (GLuint fence);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLTESTFENCENVPROC) (GLuint fence);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFENCEIVNVPROC) (GLuint fence, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFINISHFENCENVPROC) (GLuint fence);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSETFENCENVPROC) (GLuint fence, GLenum condition);
#ifdef GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glDeleteFencesNV (GLsizei n, ثابت GLuint *fences);
GL_API فراغ GL_APIENTRY glGenFencesNV (GLsizei n, GLuint *fences);
GL_API GLboolean GL_APIENTRY glIsFenceNV (GLuint fence);
GL_API GLboolean GL_APIENTRY glTestFenceNV (GLuint fence);
GL_API فراغ GL_APIENTRY glGetFenceivNV (GLuint fence, GLenum pname, GLint *params);
GL_API فراغ GL_APIENTRY glFinishFenceNV (GLuint fence);
GL_API فراغ GL_APIENTRY glSetFenceNV (GLuint fence, GLenum condition);
#endif
#endif /* GL_NV_fence */

#ifndef GL_QCOM_driver_control
#define GL_QCOM_driver_control 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETDRIVERCONTROLSQCOMPROC) (GLint *اڠک, GLsizei size, GLuint *driverControls);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETDRIVERCONTROLSTRINGQCOMPROC) (GLuint driverControl, GLsizei bufSize, GLsizei *length, GLchar *driverControlString);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
#ifdef GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glGetDriverControlsQCOM (GLint *اڠک, GLsizei size, GLuint *driverControls);
GL_API فراغ GL_APIENTRY glGetDriverControlStringQCOM (GLuint driverControl, GLsizei bufSize, GLsizei *length, GLchar *driverControlString);
GL_API فراغ GL_APIENTRY glEnableDriverControlQCOM (GLuint driverControl);
GL_API فراغ GL_APIENTRY glDisableDriverControlQCOM (GLuint driverControl);
#endif
#endif /* GL_QCOM_driver_control */

#ifndef GL_QCOM_extended_get
#define GL_QCOM_extended_get 1
#define GL_TEXTURE_WIDTH_QCOM             0x8BD2
#define GL_TEXTURE_HEIGHT_QCOM            0x8BD3
#define GL_TEXTURE_DEPTH_QCOM             0x8BD4
#define GL_TEXTURE_INTERNAL_FORMAT_QCOM   0x8BD5
#define GL_TEXTURE_FORMAT_QCOM            0x8BD6
#define GL_TEXTURE_TYPE_QCOM              0x8BD7
#define GL_TEXTURE_IMAGE_VALID_QCOM       0x8BD8
#define GL_TEXTURE_اڠک_LEVELS_QCOM        0x8BD9
#define GL_TEXTURE_TARGET_QCOM            0x8BDA
#define GL_TEXTURE_OBJECT_VALID_QCOM      0x8BDB
#define GL_STATE_RESTORE                  0x8BDC
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETTEXTURESQCOMPROC) (GLuint *textures, GLint maxTextures, GLint *اڠک_Textures);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETBUFFERSQCOMPROC) (GLuint *buffers, GLint maxBuffers, GLint *اڠک_Buffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETRENDERBUFFERSQCOMPROC) (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *اڠک_Renderbuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETFRAMEBUFFERSQCOMPROC) (GLuint *framebuffers, GLint maxFramebuffers, GLint *اڠک_Framebuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETTEXLEVELPARAMETERIVQCOMPROC) (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTTEXOBJECTSTATEOVERRIDEIQCOMPROC) (GLenum target, GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETTEXSUBIMAGEQCOMPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, فراغ *texels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETBUFFERPOINTERVQCOMPROC) (GLenum target, فراغ **params);
#ifdef GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glExtGetTexturesQCOM (GLuint *textures, GLint maxTextures, GLint *اڠک_Textures);
GL_API فراغ GL_APIENTRY glExtGetBuffersQCOM (GLuint *buffers, GLint maxBuffers, GLint *اڠک_Buffers);
GL_API فراغ GL_APIENTRY glExtGetRenderbuffersQCOM (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *اڠک_Renderbuffers);
GL_API فراغ GL_APIENTRY glExtGetFramebuffersQCOM (GLuint *framebuffers, GLint maxFramebuffers, GLint *اڠک_Framebuffers);
GL_API فراغ GL_APIENTRY glExtGetTexLevelParameterivQCOM (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
GL_API فراغ GL_APIENTRY glExtTexObjectStateOverrideiQCOM (GLenum target, GLenum pname, GLint param);
GL_API فراغ GL_APIENTRY glExtGetTexSubImageQCOM (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, فراغ *texels);
GL_API فراغ GL_APIENTRY glExtGetBufferPointervQCOM (GLenum target, فراغ **params);
#endif
#endif /* GL_QCOM_extended_get */

#ifndef GL_QCOM_extended_get2
#define GL_QCOM_extended_get2 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETSHADERSQCOMPROC) (GLuint *shaders, GLint maxShaders, GLint *اڠک_Shaders);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETPROGRAMSQCOMPROC) (GLuint *programs, GLint maxPrograms, GLint *اڠک_Programs);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLEXTISPROGRAMBINARYQCOMPROC) (GLuint program);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETPROGRAMBINARYSOURCEQCOMPROC) (GLuint program, GLenum shadertype, GLchar *source, GLint *length);
#ifdef GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glExtGetShadersQCOM (GLuint *shaders, GLint maxShaders, GLint *اڠک_Shaders);
GL_API فراغ GL_APIENTRY glExtGetProgramsQCOM (GLuint *programs, GLint maxPrograms, GLint *اڠک_Programs);
GL_API GLboolean GL_APIENTRY gl_Ext_Is_Program_بيناري_QCOM (GLuint program);
GL_API فراغ GL_APIENTRY gl_Ext_Get_Program_بيناري_Source_QCOM (GLuint program, GLenum shadertype, GLchar *source, GLint *length);
#endif
#endif /* GL_QCOM_extended_get2 */

#ifndef GL_QCOM_perfmon_global_mode
#define GL_QCOM_perfmon_global_mode 1
#define GL_PERFMON_GLOBAL_MODE_QCOM       0x8FA0
#endif /* GL_QCOM_perfmon_global_mode */

#ifndef GL_QCOM_tiled_rendering
#define GL_QCOM_tiled_rendering 1
#define GL_COLOR_BUFFER_BIT0_QCOM         0x00000001
#define GL_COLOR_BUFFER_BIT1_QCOM         0x00000002
#define GL_COLOR_BUFFER_BIT2_QCOM         0x00000004
#define GL_COLOR_BUFFER_BIT3_QCOM         0x00000008
#define GL_COLOR_BUFFER_BIT4_QCOM         0x00000010
#define GL_COLOR_BUFFER_BIT5_QCOM         0x00000020
#define GL_COLOR_BUFFER_BIT6_QCOM         0x00000040
#define GL_COLOR_BUFFER_BIT7_QCOM         0x00000080
#define GL_DEPTH_BUFFER_BIT0_QCOM         0x00000100
#define GL_DEPTH_BUFFER_BIT1_QCOM         0x00000200
#define GL_DEPTH_BUFFER_BIT2_QCOM         0x00000400
#define GL_DEPTH_BUFFER_BIT3_QCOM         0x00000800
#define GL_DEPTH_BUFFER_BIT4_QCOM         0x00001000
#define GL_DEPTH_BUFFER_BIT5_QCOM         0x00002000
#define GL_DEPTH_BUFFER_BIT6_QCOM         0x00004000
#define GL_DEPTH_BUFFER_BIT7_QCOM         0x00008000
#define GL_STENCIL_BUFFER_BIT0_QCOM       0x00010000
#define GL_STENCIL_BUFFER_BIT1_QCOM       0x00020000
#define GL_STENCIL_BUFFER_BIT2_QCOM       0x00040000
#define GL_STENCIL_BUFFER_BIT3_QCOM       0x00080000
#define GL_STENCIL_BUFFER_BIT4_QCOM       0x00100000
#define GL_STENCIL_BUFFER_BIT5_QCOM       0x00200000
#define GL_STENCIL_BUFFER_BIT6_QCOM       0x00400000
#define GL_STENCIL_BUFFER_BIT7_QCOM       0x00800000
#define GL_MULTISAMPLE_BUFFER_BIT0_QCOM   0x01000000
#define GL_MULTISAMPLE_BUFFER_BIT1_QCOM   0x02000000
#define GL_MULTISAMPLE_BUFFER_BIT2_QCOM   0x04000000
#define GL_MULTISAMPLE_BUFFER_BIT3_QCOM   0x08000000
#define GL_MULTISAMPLE_BUFFER_BIT4_QCOM   0x10000000
#define GL_MULTISAMPLE_BUFFER_BIT5_QCOM   0x20000000
#define GL_MULTISAMPLE_BUFFER_BIT6_QCOM   0x40000000
#define GL_MULTISAMPLE_BUFFER_BIT7_QCOM   0x80000000
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTARTTILINGQCOMPROC) (GLuint x, GLuint y, GLuint width, GLuint height, GLbitfield preserveMask);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENDTILINGQCOMPROC) (GLbitfield preserveMask);
#ifdef GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glStartTilingQCOM (GLuint x, GLuint y, GLuint width, GLuint height, GLbitfield preserveMask);
GL_API فراغ GL_APIENTRY glEndTilingQCOM (GLbitfield preserveMask);
#endif
#endif /* GL_QCOM_tiled_rendering */

#ifndef GL_QCOM_writeonly_rendering
#define GL_QCOM_writeonly_rendering 1
#define GL_WRITEONLY_RENDERING_QCOM       0x8823
#endif /* GL_QCOM_writeonly_rendering */

#ifdef __cplusplus
}
#endif

#endif
