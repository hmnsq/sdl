#अगर_अघोषित __gles1_glext_h_
#घोषणा __gles1_glext_h_ 1

#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर

/*
** Copyright 2013-2026 The Khronos Group Inc.
** SPDX-License-Identifier: MIT
**
** This header is generated from the Khronos OpenGL / OpenGL ES XML
** API Registry. The current version of the Registry, generator scripts
** used to make the header, and the header can be found at
**   https://github.com/KhronosGroup/OpenGL-Registry
*/

#अगर_अघोषित GL_APIENTRYP
#घोषणा GL_APIENTRYP GL_APIENTRY*
#पूर्ण_अगर

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

#अगर_अघोषित GL_KHR_debug
#घोषणा GL_KHR_debug 1
#पूर्ण_अगर /* GL_KHR_debug */

#अगर_अघोषित GL_OES_EGL_image
#घोषणा GL_OES_EGL_image 1
प्रकार व्योम *GLeglImageOES;
प्रकार व्योम (GL_APIENTRYP PFNGLEGLIMAGETARGETTEXTURE2DOESPROC) (GLenum target, GLeglImageOES image);
प्रकार व्योम (GL_APIENTRYP PFNGLEGLIMAGETARGETRENDERBUFFERSTORAGEOESPROC) (GLenum target, GLeglImageOES image);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_API व्योम GL_APIENTRY glEGLImageTargetTexture2DOES (GLenum target, GLeglImageOES image);
GL_API व्योम GL_APIENTRY glEGLImageTargetRenderbufferStorageOES (GLenum target, GLeglImageOES image);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_OES_EGL_image */

#अगर_अघोषित GL_OES_EGL_image_external
#घोषणा GL_OES_EGL_image_external 1
#घोषणा GL_TEXTURE_EXTERNAL_OES           0x8D65
#घोषणा GL_TEXTURE_BINDING_EXTERNAL_OES   0x8D67
#घोषणा GL_REQUIRED_TEXTURE_IMAGE_UNITS_OES 0x8D68
#पूर्ण_अगर /* GL_OES_EGL_image_external */

#अगर_अघोषित GL_OES_blend_equation_separate
#घोषणा GL_OES_blend_equation_separate 1
#घोषणा GL_BLEND_EQUATION_RGB_OES         0x8009
#घोषणा GL_BLEND_EQUATION_ALPHA_OES       0x883D
प्रकार व्योम (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEOESPROC) (GLenum modeRGB, GLenum modeAlpha);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_API व्योम GL_APIENTRY glBlendEquationSeparateOES (GLenum modeRGB, GLenum modeAlpha);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_OES_blend_equation_separate */

#अगर_अघोषित GL_OES_blend_func_separate
#घोषणा GL_OES_blend_func_separate 1
#घोषणा GL_BLEND_DST_RGB_OES              0x80C8
#घोषणा GL_BLEND_SRC_RGB_OES              0x80C9
#घोषणा GL_BLEND_DST_ALPHA_OES            0x80CA
#घोषणा GL_BLEND_SRC_ALPHA_OES            0x80CB
प्रकार व्योम (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEOESPROC) (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_API व्योम GL_APIENTRY glBlendFuncSeparateOES (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_OES_blend_func_separate */

#अगर_अघोषित GL_OES_blend_subtract
#घोषणा GL_OES_blend_subtract 1
#घोषणा GL_BLEND_EQUATION_OES             0x8009
#घोषणा GL_FUNC_ADD_OES                   0x8006
#घोषणा GL_FUNC_SUBTRACT_OES              0x800A
#घोषणा GL_FUNC_REVERSE_SUBTRACT_OES      0x800B
प्रकार व्योम (GL_APIENTRYP PFNGLBLENDEQUATIONOESPROC) (GLenum mode);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_API व्योम GL_APIENTRY glBlendEquationOES (GLenum mode);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_OES_blend_subtract */

#अगर_अघोषित GL_OES_byte_coordinates
#घोषणा GL_OES_byte_coordinates 1
#पूर्ण_अगर /* GL_OES_byte_coordinates */

#अगर_अघोषित GL_OES_compressed_ETC1_RGB8_sub_texture
#घोषणा GL_OES_compressed_ETC1_RGB8_sub_texture 1
#पूर्ण_अगर /* GL_OES_compressed_ETC1_RGB8_sub_texture */

#अगर_अघोषित GL_OES_compressed_ETC1_RGB8_texture
#घोषणा GL_OES_compressed_ETC1_RGB8_texture 1
#घोषणा GL_ETC1_RGB8_OES                  0x8D64
#पूर्ण_अगर /* GL_OES_compressed_ETC1_RGB8_texture */

#अगर_अघोषित GL_OES_depth24
#घोषणा GL_OES_depth24 1
#घोषणा GL_DEPTH_COMPONENT24_OES          0x81A6
#पूर्ण_अगर /* GL_OES_depth24 */

#अगर_अघोषित GL_OES_depth32
#घोषणा GL_OES_depth32 1
#घोषणा GL_DEPTH_COMPONENT32_OES          0x81A7
#पूर्ण_अगर /* GL_OES_depth32 */

#अगर_अघोषित GL_OES_draw_texture
#घोषणा GL_OES_draw_texture 1
#घोषणा GL_TEXTURE_CROP_RECT_OES          0x8B9D
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWTEXSOESPROC) (GLshort x, GLshort y, GLshort z, GLshort width, GLshort height);
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWTEXIOESPROC) (GLint x, GLint y, GLint z, GLint width, GLint height);
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWTEXXOESPROC) (GLfixed x, GLfixed y, GLfixed z, GLfixed width, GLfixed height);
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWTEXSVOESPROC) (स्थिर GLshort *coords);
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWTEXIVOESPROC) (स्थिर GLint *coords);
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWTEXXVOESPROC) (स्थिर GLfixed *coords);
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWTEXFOESPROC) (GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height);
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWTEXFVOESPROC) (स्थिर GLfloat *coords);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_API व्योम GL_APIENTRY glDrawTexsOES (GLshort x, GLshort y, GLshort z, GLshort width, GLshort height);
GL_API व्योम GL_APIENTRY glDrawTexiOES (GLint x, GLint y, GLint z, GLint width, GLint height);
GL_API व्योम GL_APIENTRY glDrawTexxOES (GLfixed x, GLfixed y, GLfixed z, GLfixed width, GLfixed height);
GL_API व्योम GL_APIENTRY glDrawTexsvOES (स्थिर GLshort *coords);
GL_API व्योम GL_APIENTRY glDrawTexivOES (स्थिर GLint *coords);
GL_API व्योम GL_APIENTRY glDrawTexxvOES (स्थिर GLfixed *coords);
GL_API व्योम GL_APIENTRY glDrawTexfOES (GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height);
GL_API व्योम GL_APIENTRY glDrawTexfvOES (स्थिर GLfloat *coords);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_OES_draw_texture */

#अगर_अघोषित GL_OES_element_सूचकांक_uint
#घोषणा GL_OES_element_सूचकांक_uint 1
#घोषणा GL_UNSIGNED_INT                   0x1405
#पूर्ण_अगर /* GL_OES_element_index_uint */

#अगर_अघोषित GL_OES_extended_matrix_palette
#घोषणा GL_OES_extended_matrix_palette 1
#पूर्ण_अगर /* GL_OES_extended_matrix_palette */

#अगर_अघोषित GL_OES_fbo_render_mipmap
#घोषणा GL_OES_fbo_render_mipmap 1
#पूर्ण_अगर /* GL_OES_fbo_render_mipmap */

#अगर_अघोषित GL_OES_fixed_point
#घोषणा GL_OES_fixed_point 1
#घोषणा GL_FIXED_OES                      0x140C
प्रकार व्योम (GL_APIENTRYP PFNGLALPHAFUNCXOESPROC) (GLenum func, GLfixed ref);
प्रकार व्योम (GL_APIENTRYP PFNGLCLEARCOLORXOESPROC) (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
प्रकार व्योम (GL_APIENTRYP PFNGLCLEARDEPTHXOESPROC) (GLfixed depth);
प्रकार व्योम (GL_APIENTRYP PFNGLCLIPPLANEXOESPROC) (GLenum plane, स्थिर GLfixed *equation);
प्रकार व्योम (GL_APIENTRYP PFNGLCOLOR4XOESPROC) (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
प्रकार व्योम (GL_APIENTRYP PFNGLDEPTHRANGEXOESPROC) (GLfixed n, GLfixed f);
प्रकार व्योम (GL_APIENTRYP PFNGLFOGXOESPROC) (GLenum pname, GLfixed param);
प्रकार व्योम (GL_APIENTRYP PFNGLFOGXVOESPROC) (GLenum pname, स्थिर GLfixed *param);
प्रकार व्योम (GL_APIENTRYP PFNGLFRUSTUMXOESPROC) (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
प्रकार व्योम (GL_APIENTRYP PFNGLGETCLIPPLANEXOESPROC) (GLenum plane, GLfixed *equation);
प्रकार व्योम (GL_APIENTRYP PFNGLGETFIXEDVOESPROC) (GLenum pname, GLfixed *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETTEXENVXVOESPROC) (GLenum target, GLenum pname, GLfixed *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETTEXPARAMETERXVOESPROC) (GLenum target, GLenum pname, GLfixed *params);
प्रकार व्योम (GL_APIENTRYP PFNGLLIGHTMODELXOESPROC) (GLenum pname, GLfixed param);
प्रकार व्योम (GL_APIENTRYP PFNGLLIGHTMODELXVOESPROC) (GLenum pname, स्थिर GLfixed *param);
प्रकार व्योम (GL_APIENTRYP PFNGLLIGHTXOESPROC) (GLenum light, GLenum pname, GLfixed param);
प्रकार व्योम (GL_APIENTRYP PFNGLLIGHTXVOESPROC) (GLenum light, GLenum pname, स्थिर GLfixed *params);
प्रकार व्योम (GL_APIENTRYP PFNGLLINEWIDTHXOESPROC) (GLfixed width);
प्रकार व्योम (GL_APIENTRYP PFNGLLOADMATRIXXOESPROC) (स्थिर GLfixed *m);
प्रकार व्योम (GL_APIENTRYP PFNGLMATERIALXOESPROC) (GLenum face, GLenum pname, GLfixed param);
प्रकार व्योम (GL_APIENTRYP PFNGLMATERIALXVOESPROC) (GLenum face, GLenum pname, स्थिर GLfixed *param);
प्रकार व्योम (GL_APIENTRYP PFNGLMULTMATRIXXOESPROC) (स्थिर GLfixed *m);
प्रकार व्योम (GL_APIENTRYP PFNGLMULTITEXCOORD4XOESPROC) (GLenum texture, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
प्रकार व्योम (GL_APIENTRYP PFNGLNORMAL3XOESPROC) (GLfixed nx, GLfixed ny, GLfixed nz);
प्रकार व्योम (GL_APIENTRYP PFNGLORTHOXOESPROC) (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
प्रकार व्योम (GL_APIENTRYP PFNGLPOINTPARAMETERXVOESPROC) (GLenum pname, स्थिर GLfixed *params);
प्रकार व्योम (GL_APIENTRYP PFNGLPOINTSIZEXOESPROC) (GLfixed आकार);
प्रकार व्योम (GL_APIENTRYP PFNGLPOLYGONOFFSETXOESPROC) (GLfixed factor, GLfixed units);
प्रकार व्योम (GL_APIENTRYP PFNGLROTATEXOESPROC) (GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
प्रकार व्योम (GL_APIENTRYP PFNGLSCALEXOESPROC) (GLfixed x, GLfixed y, GLfixed z);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXENVXOESPROC) (GLenum target, GLenum pname, GLfixed param);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXENVXVOESPROC) (GLenum target, GLenum pname, स्थिर GLfixed *params);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXPARAMETERXOESPROC) (GLenum target, GLenum pname, GLfixed param);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXPARAMETERXVOESPROC) (GLenum target, GLenum pname, स्थिर GLfixed *params);
प्रकार व्योम (GL_APIENTRYP PFNGLTRANSLATEXOESPROC) (GLfixed x, GLfixed y, GLfixed z);
प्रकार व्योम (GL_APIENTRYP PFNGLGETLIGHTXVOESPROC) (GLenum light, GLenum pname, GLfixed *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETMATERIALXVOESPROC) (GLenum face, GLenum pname, GLfixed *params);
प्रकार व्योम (GL_APIENTRYP PFNGLPOINTPARAMETERXOESPROC) (GLenum pname, GLfixed param);
प्रकार व्योम (GL_APIENTRYP PFNGLSAMPLECOVERAGEXOESPROC) (GLclampx मूल्य, GLboolean invert);
प्रकार व्योम (GL_APIENTRYP PFNGLGETTEXGENXVOESPROC) (GLenum coord, GLenum pname, GLfixed *params);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXGENXOESPROC) (GLenum coord, GLenum pname, GLfixed param);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXGENXVOESPROC) (GLenum coord, GLenum pname, स्थिर GLfixed *params);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_API व्योम GL_APIENTRY glAlphaFuncxOES (GLenum func, GLfixed ref);
GL_API व्योम GL_APIENTRY glClearColorxOES (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GL_API व्योम GL_APIENTRY glClearDepthxOES (GLfixed depth);
GL_API व्योम GL_APIENTRY glClipPlanexOES (GLenum plane, स्थिर GLfixed *equation);
GL_API व्योम GL_APIENTRY glColor4xOES (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GL_API व्योम GL_APIENTRY glDepthRangexOES (GLfixed n, GLfixed f);
GL_API व्योम GL_APIENTRY glFogxOES (GLenum pname, GLfixed param);
GL_API व्योम GL_APIENTRY glFogxvOES (GLenum pname, स्थिर GLfixed *param);
GL_API व्योम GL_APIENTRY glFrustumxOES (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
GL_API व्योम GL_APIENTRY glGetClipPlanexOES (GLenum plane, GLfixed *equation);
GL_API व्योम GL_APIENTRY glGetFixedvOES (GLenum pname, GLfixed *params);
GL_API व्योम GL_APIENTRY glGetTexEnvxvOES (GLenum target, GLenum pname, GLfixed *params);
GL_API व्योम GL_APIENTRY glGetTexParameterxvOES (GLenum target, GLenum pname, GLfixed *params);
GL_API व्योम GL_APIENTRY glLightModelxOES (GLenum pname, GLfixed param);
GL_API व्योम GL_APIENTRY glLightModelxvOES (GLenum pname, स्थिर GLfixed *param);
GL_API व्योम GL_APIENTRY glLightxOES (GLenum light, GLenum pname, GLfixed param);
GL_API व्योम GL_APIENTRY glLightxvOES (GLenum light, GLenum pname, स्थिर GLfixed *params);
GL_API व्योम GL_APIENTRY gl_पंक्ति_Widthx_OES (GLfixed width);
GL_API व्योम GL_APIENTRY glLoadMatrixxOES (स्थिर GLfixed *m);
GL_API व्योम GL_APIENTRY glMaterialxOES (GLenum face, GLenum pname, GLfixed param);
GL_API व्योम GL_APIENTRY glMaterialxvOES (GLenum face, GLenum pname, स्थिर GLfixed *param);
GL_API व्योम GL_APIENTRY glMultMatrixxOES (स्थिर GLfixed *m);
GL_API व्योम GL_APIENTRY glMultiTexCoord4xOES (GLenum texture, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
GL_API व्योम GL_APIENTRY glNormal3xOES (GLfixed nx, GLfixed ny, GLfixed nz);
GL_API व्योम GL_APIENTRY glOrthoxOES (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
GL_API व्योम GL_APIENTRY glPointParameterxvOES (GLenum pname, स्थिर GLfixed *params);
GL_API व्योम GL_APIENTRY glPointSizexOES (GLfixed आकार);
GL_API व्योम GL_APIENTRY glPolygonOffsetxOES (GLfixed factor, GLfixed units);
GL_API व्योम GL_APIENTRY glRotatexOES (GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
GL_API व्योम GL_APIENTRY glScalexOES (GLfixed x, GLfixed y, GLfixed z);
GL_API व्योम GL_APIENTRY glTexEnvxOES (GLenum target, GLenum pname, GLfixed param);
GL_API व्योम GL_APIENTRY glTexEnvxvOES (GLenum target, GLenum pname, स्थिर GLfixed *params);
GL_API व्योम GL_APIENTRY glTexParameterxOES (GLenum target, GLenum pname, GLfixed param);
GL_API व्योम GL_APIENTRY glTexParameterxvOES (GLenum target, GLenum pname, स्थिर GLfixed *params);
GL_API व्योम GL_APIENTRY glTranslatexOES (GLfixed x, GLfixed y, GLfixed z);
GL_API व्योम GL_APIENTRY glGetLightxvOES (GLenum light, GLenum pname, GLfixed *params);
GL_API व्योम GL_APIENTRY glGetMaterialxvOES (GLenum face, GLenum pname, GLfixed *params);
GL_API व्योम GL_APIENTRY glPointParameterxOES (GLenum pname, GLfixed param);
GL_API व्योम GL_APIENTRY glSampleCoveragexOES (GLclampx मूल्य, GLboolean invert);
GL_API व्योम GL_APIENTRY glGetTexGenxvOES (GLenum coord, GLenum pname, GLfixed *params);
GL_API व्योम GL_APIENTRY glTexGenxOES (GLenum coord, GLenum pname, GLfixed param);
GL_API व्योम GL_APIENTRY glTexGenxvOES (GLenum coord, GLenum pname, स्थिर GLfixed *params);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_OES_fixed_point */

#अगर_अघोषित GL_OES_framebuffer_object
#घोषणा GL_OES_framebuffer_object 1
#घोषणा GL_NONE_OES                       0
#घोषणा GL_FRAMEBUFFER_OES                0x8D40
#घोषणा GL_RENDERBUFFER_OES               0x8D41
#घोषणा GL_RGBA4_OES                      0x8056
#घोषणा GL_RGB5_A1_OES                    0x8057
#घोषणा GL_RGB565_OES                     0x8D62
#घोषणा GL_DEPTH_COMPONENT16_OES          0x81A5
#घोषणा GL_RENDERBUFFER_WIDTH_OES         0x8D42
#घोषणा GL_RENDERBUFFER_HEIGHT_OES        0x8D43
#घोषणा GL_RENDERBUFFER_INTERNAL_FORMAT_OES 0x8D44
#घोषणा GL_RENDERBUFFER_RED_आकार_OES      0x8D50
#घोषणा GL_RENDERBUFFER_GREEN_आकार_OES    0x8D51
#घोषणा GL_RENDERBUFFER_BLUE_आकार_OES     0x8D52
#घोषणा GL_RENDERBUFFER_ALPHA_आकार_OES    0x8D53
#घोषणा GL_RENDERBUFFER_DEPTH_आकार_OES    0x8D54
#घोषणा GL_RENDERBUFFER_STENCIL_आकार_OES  0x8D55
#घोषणा GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_OES 0x8CD0
#घोषणा GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_OES 0x8CD1
#घोषणा GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_OES 0x8CD2
#घोषणा GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_OES 0x8CD3
#घोषणा GL_COLOR_ATTACHMENT0_OES          0x8CE0
#घोषणा GL_DEPTH_ATTACHMENT_OES           0x8D00
#घोषणा GL_STENCIL_ATTACHMENT_OES         0x8D20
#घोषणा GL_FRAMEBUFFER_COMPLETE_OES       0x8CD5
#घोषणा GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_OES 0x8CD6
#घोषणा GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_OES 0x8CD7
#घोषणा GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_OES 0x8CD9
#घोषणा GL_FRAMEBUFFER_INCOMPLETE_FORMATS_OES 0x8CDA
#घोषणा GL_FRAMEBUFFER_UNSUPPORTED_OES    0x8CDD
#घोषणा GL_FRAMEBUFFER_BINDING_OES        0x8CA6
#घोषणा GL_RENDERBUFFER_BINDING_OES       0x8CA7
#घोषणा GL_MAX_RENDERBUFFER_आकार_OES      0x84E8
#घोषणा GL_INVALID_FRAMEBUFFER_OPERATION_OES 0x0506
प्रकार GLboolean (GL_APIENTRYP PFNGLISRENDERBUFFEROESPROC) (GLuint renderbuffer);
प्रकार व्योम (GL_APIENTRYP PFNGLBINDRENDERBUFFEROESPROC) (GLenum target, GLuint renderbuffer);
प्रकार व्योम (GL_APIENTRYP PFNGLDELETERENDERBUFFERSOESPROC) (GLsizei n, स्थिर GLuint *renderbuffers);
प्रकार व्योम (GL_APIENTRYP PFNGLGENRENDERBUFFERSOESPROC) (GLsizei n, GLuint *renderbuffers);
प्रकार व्योम (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEOESPROC) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
प्रकार व्योम (GL_APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVOESPROC) (GLenum target, GLenum pname, GLint *params);
प्रकार GLboolean (GL_APIENTRYP PFNGLISFRAMEBUFFEROESPROC) (GLuint framebuffer);
प्रकार व्योम (GL_APIENTRYP PFNGLBINDFRAMEBUFFEROESPROC) (GLenum target, GLuint framebuffer);
प्रकार व्योम (GL_APIENTRYP PFNGLDELETEFRAMEBUFFERSOESPROC) (GLsizei n, स्थिर GLuint *framebuffers);
प्रकार व्योम (GL_APIENTRYP PFNGLGENFRAMEBUFFERSOESPROC) (GLsizei n, GLuint *framebuffers);
प्रकार GLenum (GL_APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSOESPROC) (GLenum target);
प्रकार व्योम (GL_APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFEROESPROC) (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
प्रकार व्योम (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DOESPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
प्रकार व्योम (GL_APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVOESPROC) (GLenum target, GLenum attachment, GLenum pname, GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGENERATEMIPMAPOESPROC) (GLenum target);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_API GLboolean GL_APIENTRY glIsRenderbufferOES (GLuint renderbuffer);
GL_API व्योम GL_APIENTRY glBindRenderbufferOES (GLenum target, GLuint renderbuffer);
GL_API व्योम GL_APIENTRY glDeleteRenderbuffersOES (GLsizei n, स्थिर GLuint *renderbuffers);
GL_API व्योम GL_APIENTRY glGenRenderbuffersOES (GLsizei n, GLuint *renderbuffers);
GL_API व्योम GL_APIENTRY glRenderbufferStorageOES (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
GL_API व्योम GL_APIENTRY glGetRenderbufferParameterivOES (GLenum target, GLenum pname, GLint *params);
GL_API GLboolean GL_APIENTRY glIsFramebufferOES (GLuint framebuffer);
GL_API व्योम GL_APIENTRY glBindFramebufferOES (GLenum target, GLuint framebuffer);
GL_API व्योम GL_APIENTRY glDeleteFramebuffersOES (GLsizei n, स्थिर GLuint *framebuffers);
GL_API व्योम GL_APIENTRY glGenFramebuffersOES (GLsizei n, GLuint *framebuffers);
GL_API GLenum GL_APIENTRY glCheckFramebufferStatusOES (GLenum target);
GL_API व्योम GL_APIENTRY glFramebufferRenderbufferOES (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
GL_API व्योम GL_APIENTRY glFramebufferTexture2DOES (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GL_API व्योम GL_APIENTRY glGetFramebufferAttachmentParameterivOES (GLenum target, GLenum attachment, GLenum pname, GLint *params);
GL_API व्योम GL_APIENTRY glGenerateMipmapOES (GLenum target);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_OES_framebuffer_object */

#अगर_अघोषित GL_OES_mapbuffer
#घोषणा GL_OES_mapbuffer 1
#घोषणा GL_WRITE_ONLY_OES                 0x88B9
#घोषणा GL_बफर_ACCESS_OES              0x88BB
#घोषणा GL_बफर_MAPPED_OES              0x88BC
#घोषणा GL_बफर_MAP_POINTER_OES         0x88BD
प्रकार व्योम *(GL_APIENTRYP PFNGLMAPBUFFEROESPROC) (GLenum target, GLenum access);
प्रकार GLboolean (GL_APIENTRYP PFNGLUNMAPBUFFEROESPROC) (GLenum target);
प्रकार व्योम (GL_APIENTRYP PFNGLGETBUFFERPOINTERVOESPROC) (GLenum target, GLenum pname, व्योम **params);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_API व्योम *GL_APIENTRY gl_Map_बफर_OES (GLenum target, GLenum access);
GL_API GLboolean GL_APIENTRY gl_Unmap_बफर_OES (GLenum target);
GL_API व्योम GL_APIENTRY gl_Get_बफर_Pointerv_OES (GLenum target, GLenum pname, व्योम **params);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_OES_mapbuffer */

#अगर_अघोषित GL_OES_matrix_get
#घोषणा GL_OES_matrix_get 1
#घोषणा GL_MODELVIEW_MATRIX_FLOAT_AS_INT_BITS_OES 0x898D
#घोषणा GL_PROJECTION_MATRIX_FLOAT_AS_INT_BITS_OES 0x898E
#घोषणा GL_TEXTURE_MATRIX_FLOAT_AS_INT_BITS_OES 0x898F
#पूर्ण_अगर /* GL_OES_matrix_get */

#अगर_अघोषित GL_OES_matrix_palette
#घोषणा GL_OES_matrix_palette 1
#घोषणा GL_MAX_VERTEX_UNITS_OES           0x86A4
#घोषणा GL_MAX_PALETTE_MATRICES_OES       0x8842
#घोषणा GL_MATRIX_PALETTE_OES             0x8840
#घोषणा GL_MATRIX_सूचकांक_ARRAY_OES         0x8844
#घोषणा GL_WEIGHT_ARRAY_OES               0x86AD
#घोषणा GL_CURRENT_PALETTE_MATRIX_OES     0x8843
#घोषणा GL_MATRIX_सूचकांक_ARRAY_आकार_OES    0x8846
#घोषणा GL_MATRIX_सूचकांक_ARRAY_TYPE_OES    0x8847
#घोषणा GL_MATRIX_सूचकांक_ARRAY_STRIDE_OES  0x8848
#घोषणा GL_MATRIX_सूचकांक_ARRAY_POINTER_OES 0x8849
#घोषणा GL_MATRIX_सूचकांक_ARRAY_बफर_BINDING_OES 0x8B9E
#घोषणा GL_WEIGHT_ARRAY_आकार_OES          0x86AB
#घोषणा GL_WEIGHT_ARRAY_TYPE_OES          0x86A9
#घोषणा GL_WEIGHT_ARRAY_STRIDE_OES        0x86AA
#घोषणा GL_WEIGHT_ARRAY_POINTER_OES       0x86AC
#घोषणा GL_WEIGHT_ARRAY_बफर_BINDING_OES 0x889E
प्रकार व्योम (GL_APIENTRYP PFNGLCURRENTPALETTEMATRIXOESPROC) (GLuint matrixpaletteindex);
प्रकार व्योम (GL_APIENTRYP PFNGLLOADPALETTEFROMMODELVIEWMATRIXOESPROC) (व्योम);
प्रकार व्योम (GL_APIENTRYP PFNGLMATRIXINDEXPOINTEROESPROC) (GLint आकार, GLenum type, GLsizei stride, स्थिर व्योम *pointer);
प्रकार व्योम (GL_APIENTRYP PFNGLWEIGHTPOINTEROESPROC) (GLint आकार, GLenum type, GLsizei stride, स्थिर व्योम *pointer);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_API व्योम GL_APIENTRY glCurrentPaletteMatrixOES (GLuint matrixpaletteindex);
GL_API व्योम GL_APIENTRY glLoadPaletteFromModelViewMatrixOES (व्योम);
GL_API व्योम GL_APIENTRY gl_Matrix_सूचकांक_Pointer_OES (GLint आकार, GLenum type, GLsizei stride, स्थिर व्योम *pointer);
GL_API व्योम GL_APIENTRY glWeightPointerOES (GLint आकार, GLenum type, GLsizei stride, स्थिर व्योम *pointer);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_OES_matrix_palette */

#अगर_अघोषित GL_OES_packed_depth_stencil
#घोषणा GL_OES_packed_depth_stencil 1
#घोषणा GL_DEPTH_STENCIL_OES              0x84F9
#घोषणा GL_UNSIGNED_INT_24_8_OES          0x84FA
#घोषणा GL_DEPTH24_STENCIL8_OES           0x88F0
#पूर्ण_अगर /* GL_OES_packed_depth_stencil */

#अगर_अघोषित GL_OES_query_matrix
#घोषणा GL_OES_query_matrix 1
प्रकार GLbitfield (GL_APIENTRYP PFNGLQUERYMATRIXXOESPROC) (GLfixed *mantissa, GLint *exponent);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_API GLbitfield GL_APIENTRY glQueryMatrixxOES (GLfixed *mantissa, GLint *exponent);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_OES_query_matrix */

#अगर_अघोषित GL_OES_required_internalformat
#घोषणा GL_OES_required_internalformat 1
#घोषणा GL_ALPHA8_OES                     0x803C
#घोषणा GL_LUMINANCE4_ALPHA4_OES          0x8043
#घोषणा GL_LUMINANCE8_ALPHA8_OES          0x8045
#घोषणा GL_LUMINANCE8_OES                 0x8040
#घोषणा GL_RGB8_OES                       0x8051
#घोषणा GL_RGBA8_OES                      0x8058
#घोषणा GL_RGB10_EXT                      0x8052
#घोषणा GL_RGB10_A2_EXT                   0x8059
#पूर्ण_अगर /* GL_OES_required_internalformat */

#अगर_अघोषित GL_OES_rgb8_rgba8
#घोषणा GL_OES_rgb8_rgba8 1
#पूर्ण_अगर /* GL_OES_rgb8_rgba8 */

#अगर_अघोषित GL_OES_single_precision
#घोषणा GL_OES_single_precision 1
प्रकार व्योम (GL_APIENTRYP PFNGLCLEARDEPTHFOESPROC) (GLclampf depth);
प्रकार व्योम (GL_APIENTRYP PFNGLCLIPPLANEFOESPROC) (GLenum plane, स्थिर GLfloat *equation);
प्रकार व्योम (GL_APIENTRYP PFNGLDEPTHRANGEFOESPROC) (GLclampf n, GLclampf f);
प्रकार व्योम (GL_APIENTRYP PFNGLFRUSTUMFOESPROC) (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
प्रकार व्योम (GL_APIENTRYP PFNGLGETCLIPPLANEFOESPROC) (GLenum plane, GLfloat *equation);
प्रकार व्योम (GL_APIENTRYP PFNGLORTHOFOESPROC) (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_API व्योम GL_APIENTRY glClearDepthfOES (GLclampf depth);
GL_API व्योम GL_APIENTRY glClipPlanefOES (GLenum plane, स्थिर GLfloat *equation);
GL_API व्योम GL_APIENTRY glDepthRangefOES (GLclampf n, GLclampf f);
GL_API व्योम GL_APIENTRY glFrustumfOES (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
GL_API व्योम GL_APIENTRY glGetClipPlanefOES (GLenum plane, GLfloat *equation);
GL_API व्योम GL_APIENTRY glOrthofOES (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_OES_single_precision */

#अगर_अघोषित GL_OES_stencil1
#घोषणा GL_OES_stencil1 1
#घोषणा GL_STENCIL_INDEX1_OES             0x8D46
#पूर्ण_अगर /* GL_OES_stencil1 */

#अगर_अघोषित GL_OES_stencil4
#घोषणा GL_OES_stencil4 1
#घोषणा GL_STENCIL_INDEX4_OES             0x8D47
#पूर्ण_अगर /* GL_OES_stencil4 */

#अगर_अघोषित GL_OES_stencil8
#घोषणा GL_OES_stencil8 1
#घोषणा GL_STENCIL_INDEX8_OES             0x8D48
#पूर्ण_अगर /* GL_OES_stencil8 */

#अगर_अघोषित GL_OES_stencil_wrap
#घोषणा GL_OES_stencil_wrap 1
#घोषणा GL_INCR_WRAP_OES                  0x8507
#घोषणा GL_DECR_WRAP_OES                  0x8508
#पूर्ण_अगर /* GL_OES_stencil_wrap */

#अगर_अघोषित GL_OES_surfaceless_context
#घोषणा GL_OES_surfaceless_context 1
#घोषणा GL_FRAMEBUFFER_UNDEFINED_OES      0x8219
#पूर्ण_अगर /* GL_OES_surfaceless_context */

#अगर_अघोषित GL_OES_texture_cube_map
#घोषणा GL_OES_texture_cube_map 1
#घोषणा GL_NORMAL_MAP_OES                 0x8511
#घोषणा GL_REFLECTION_MAP_OES             0x8512
#घोषणा GL_TEXTURE_CUBE_MAP_OES           0x8513
#घोषणा GL_TEXTURE_BINDING_CUBE_MAP_OES   0x8514
#घोषणा GL_TEXTURE_CUBE_MAP_POSITIVE_X_OES 0x8515
#घोषणा GL_TEXTURE_CUBE_MAP_NEGATIVE_X_OES 0x8516
#घोषणा GL_TEXTURE_CUBE_MAP_POSITIVE_Y_OES 0x8517
#घोषणा GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_OES 0x8518
#घोषणा GL_TEXTURE_CUBE_MAP_POSITIVE_Z_OES 0x8519
#घोषणा GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_OES 0x851A
#घोषणा GL_MAX_CUBE_MAP_TEXTURE_आकार_OES  0x851C
#घोषणा GL_TEXTURE_GEN_MODE_OES           0x2500
#घोषणा GL_TEXTURE_GEN_STR_OES            0x8D60
प्रकार व्योम (GL_APIENTRYP PFNGLTEXGENFOESPROC) (GLenum coord, GLenum pname, GLfloat param);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXGENFVOESPROC) (GLenum coord, GLenum pname, स्थिर GLfloat *params);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXGENIOESPROC) (GLenum coord, GLenum pname, GLint param);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXGENIVOESPROC) (GLenum coord, GLenum pname, स्थिर GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETTEXGENFVOESPROC) (GLenum coord, GLenum pname, GLfloat *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETTEXGENIVOESPROC) (GLenum coord, GLenum pname, GLint *params);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_API व्योम GL_APIENTRY glTexGenfOES (GLenum coord, GLenum pname, GLfloat param);
GL_API व्योम GL_APIENTRY glTexGenfvOES (GLenum coord, GLenum pname, स्थिर GLfloat *params);
GL_API व्योम GL_APIENTRY glTexGeniOES (GLenum coord, GLenum pname, GLint param);
GL_API व्योम GL_APIENTRY glTexGenivOES (GLenum coord, GLenum pname, स्थिर GLint *params);
GL_API व्योम GL_APIENTRY glGetTexGenfvOES (GLenum coord, GLenum pname, GLfloat *params);
GL_API व्योम GL_APIENTRY glGetTexGenivOES (GLenum coord, GLenum pname, GLint *params);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_OES_texture_cube_map */

#अगर_अघोषित GL_OES_texture_env_crossbar
#घोषणा GL_OES_texture_env_crossbar 1
#पूर्ण_अगर /* GL_OES_texture_env_crossbar */

#अगर_अघोषित GL_OES_texture_mirrored_repeat
#घोषणा GL_OES_texture_mirrored_repeat 1
#घोषणा GL_MIRRORED_REPEAT_OES            0x8370
#पूर्ण_अगर /* GL_OES_texture_mirrored_repeat */

#अगर_अघोषित GL_OES_texture_npot
#घोषणा GL_OES_texture_npot 1
#पूर्ण_अगर /* GL_OES_texture_npot */

#अगर_अघोषित GL_OES_vertex_array_object
#घोषणा GL_OES_vertex_array_object 1
#घोषणा GL_VERTEX_ARRAY_BINDING_OES       0x85B5
प्रकार व्योम (GL_APIENTRYP PFNGLBINDVERTEXARRAYOESPROC) (GLuint array);
प्रकार व्योम (GL_APIENTRYP PFNGLDELETEVERTEXARRAYSOESPROC) (GLsizei n, स्थिर GLuint *arrays);
प्रकार व्योम (GL_APIENTRYP PFNGLGENVERTEXARRAYSOESPROC) (GLsizei n, GLuint *arrays);
प्रकार GLboolean (GL_APIENTRYP PFNGLISVERTEXARRAYOESPROC) (GLuint array);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_API व्योम GL_APIENTRY glBindVertexArrayOES (GLuint array);
GL_API व्योम GL_APIENTRY glDeleteVertexArraysOES (GLsizei n, स्थिर GLuint *arrays);
GL_API व्योम GL_APIENTRY glGenVertexArraysOES (GLsizei n, GLuint *arrays);
GL_API GLboolean GL_APIENTRY glIsVertexArrayOES (GLuint array);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_OES_vertex_array_object */

#अगर_अघोषित GL_AMD_compressed_3DC_texture
#घोषणा GL_AMD_compressed_3DC_texture 1
#घोषणा GL_3DC_X_AMD                      0x87F9
#घोषणा GL_3DC_XY_AMD                     0x87FA
#पूर्ण_अगर /* GL_AMD_compressed_3DC_texture */

#अगर_अघोषित GL_AMD_compressed_ATC_texture
#घोषणा GL_AMD_compressed_ATC_texture 1
#घोषणा GL_ATC_RGB_AMD                    0x8C92
#घोषणा GL_ATC_RGBA_EXPLICIT_ALPHA_AMD    0x8C93
#घोषणा GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD 0x87EE
#पूर्ण_अगर /* GL_AMD_compressed_ATC_texture */

#अगर_अघोषित GL_APPLE_copy_texture_levels
#घोषणा GL_APPLE_copy_texture_levels 1
प्रकार व्योम (GL_APIENTRYP PFNGLCOPYTEXTURELEVELSAPPLEPROC) (GLuint destinationTexture, GLuint sourceTexture, GLint sourceBaseLevel, GLsizei source_Level_गिनती);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_API व्योम GL_APIENTRY glCopyTextureLevelsAPPLE (GLuint destinationTexture, GLuint sourceTexture, GLint sourceBaseLevel, GLsizei source_Level_गिनती);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_APPLE_copy_texture_levels */

#अगर_अघोषित GL_APPLE_framebuffer_multisample
#घोषणा GL_APPLE_framebuffer_multisample 1
#घोषणा GL_RENDERBUFFER_SAMPLES_APPLE     0x8CAB
#घोषणा GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_APPLE 0x8D56
#घोषणा GL_MAX_SAMPLES_APPLE              0x8D57
#घोषणा GL_READ_FRAMEBUFFER_APPLE         0x8CA8
#घोषणा GL_DRAW_FRAMEBUFFER_APPLE         0x8CA9
#घोषणा GL_DRAW_FRAMEBUFFER_BINDING_APPLE 0x8CA6
#घोषणा GL_READ_FRAMEBUFFER_BINDING_APPLE 0x8CAA
प्रकार व्योम (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEAPPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
प्रकार व्योम (GL_APIENTRYP PFNGLRESOLVEMULTISAMPLEFRAMEBUFFERAPPLEPROC) (व्योम);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_API व्योम GL_APIENTRY glRenderbufferStorageMultisampleAPPLE (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
GL_API व्योम GL_APIENTRY glResolveMultisampleFramebufferAPPLE (व्योम);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_APPLE_framebuffer_multisample */

#अगर_अघोषित GL_APPLE_sync
#घोषणा GL_APPLE_sync 1
प्रकार काष्ठा __GLsync *GLsync;
प्रकार khronos_uint64_t GLuint64;
प्रकार khronos_int64_t GLint64;
#घोषणा GL_SYNC_OBJECT_APPLE              0x8A53
#घोषणा GL_MAX_SERVER_WAIT_TIMEOUT_APPLE  0x9111
#घोषणा GL_OBJECT_TYPE_APPLE              0x9112
#घोषणा GL_SYNC_CONDITION_APPLE           0x9113
#घोषणा GL_SYNC_STATUS_APPLE              0x9114
#घोषणा GL_SYNC_FLAGS_APPLE               0x9115
#घोषणा GL_SYNC_FENCE_APPLE               0x9116
#घोषणा GL_SYNC_GPU_COMMANDS_COMPLETE_APPLE 0x9117
#घोषणा GL_UNSIGNALED_APPLE               0x9118
#घोषणा GL_SIGNALED_APPLE                 0x9119
#घोषणा GL_ALREADY_SIGNALED_APPLE         0x911A
#घोषणा GL_TIMEOUT_EXPIRED_APPLE          0x911B
#घोषणा GL_CONDITION_SATISFIED_APPLE      0x911C
#घोषणा GL_WAIT_FAILED_APPLE              0x911D
#घोषणा GL_SYNC_FLUSH_COMMANDS_BIT_APPLE  0x00000001
#घोषणा GL_TIMEOUT_IGNORED_APPLE          0xFFFFFFFFFFFFFFFFull
प्रकार GLsync (GL_APIENTRYP PFNGLFENCESYNCAPPLEPROC) (GLenum condition, GLbitfield flags);
प्रकार GLboolean (GL_APIENTRYP PFNGLISSYNCAPPLEPROC) (GLsync sync);
प्रकार व्योम (GL_APIENTRYP PFNGLDELETESYNCAPPLEPROC) (GLsync sync);
प्रकार GLenum (GL_APIENTRYP PFNGLCLIENTWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
प्रकार व्योम (GL_APIENTRYP PFNGLWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
प्रकार व्योम (GL_APIENTRYP PFNGLGETINTEGER64VAPPLEPROC) (GLenum pname, GLint64 *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETSYNCIVAPPLEPROC) (GLsync sync, GLenum pname, GLsizei गिनती, GLsizei *लंबाई, GLint *मूल्यावली);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_API GLsync GL_APIENTRY glFenceSyncAPPLE (GLenum condition, GLbitfield flags);
GL_API GLboolean GL_APIENTRY glIsSyncAPPLE (GLsync sync);
GL_API व्योम GL_APIENTRY glDeleteSyncAPPLE (GLsync sync);
GL_API GLenum GL_APIENTRY glClientWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_API व्योम GL_APIENTRY glWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_API व्योम GL_APIENTRY glGetInteger64vAPPLE (GLenum pname, GLint64 *params);
GL_API व्योम GL_APIENTRY glGetSyncivAPPLE (GLsync sync, GLenum pname, GLsizei गिनती, GLsizei *लंबाई, GLint *मूल्यावली);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_APPLE_sync */

#अगर_अघोषित GL_APPLE_texture_2D_limited_npot
#घोषणा GL_APPLE_texture_2D_limited_npot 1
#पूर्ण_अगर /* GL_APPLE_texture_2D_limited_npot */

#अगर_अघोषित GL_APPLE_texture_format_BGRA8888
#घोषणा GL_APPLE_texture_format_BGRA8888 1
#घोषणा GL_BGRA_EXT                       0x80E1
#घोषणा GL_BGRA8_EXT                      0x93A1
#पूर्ण_अगर /* GL_APPLE_texture_format_BGRA8888 */

#अगर_अघोषित GL_APPLE_texture_max_level
#घोषणा GL_APPLE_texture_max_level 1
#घोषणा GL_TEXTURE_MAX_LEVEL_APPLE        0x813D
#पूर्ण_अगर /* GL_APPLE_texture_max_level */

#अगर_अघोषित GL_ARM_rgba8
#घोषणा GL_ARM_rgba8 1
#पूर्ण_अगर /* GL_ARM_rgba8 */

#अगर_अघोषित GL_EXT_blend_minmax
#घोषणा GL_EXT_blend_minmax 1
#घोषणा GL_MIN_EXT                        0x8007
#घोषणा GL_MAX_EXT                        0x8008
#पूर्ण_अगर /* GL_EXT_blend_minmax */

#अगर_अघोषित GL_EXT_debug_marker
#घोषणा GL_EXT_debug_marker 1
प्रकार अक्षर GLchar;
प्रकार व्योम (GL_APIENTRYP PFNGLINSERTEVENTMARKEREXTPROC) (GLsizei लंबाई, स्थिर GLchar *marker);
प्रकार व्योम (GL_APIENTRYP PFNGLPUSHGROUPMARKEREXTPROC) (GLsizei लंबाई, स्थिर GLchar *marker);
प्रकार व्योम (GL_APIENTRYP PFNGLPOPGROUPMARKEREXTPROC) (व्योम);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_API व्योम GL_APIENTRY gl_जोड़ो_Event_Marker_EXT (GLsizei लंबाई, स्थिर GLchar *marker);
GL_API व्योम GL_APIENTRY gl_धकेलो_Group_Marker_EXT (GLsizei लंबाई, स्थिर GLchar *marker);
GL_API व्योम GL_APIENTRY gl_निकालो_Group_Marker_EXT (व्योम);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_debug_marker */

#अगर_अघोषित GL_EXT_discard_framebuffer
#घोषणा GL_EXT_discard_framebuffer 1
#घोषणा GL_COLOR_EXT                      0x1800
#घोषणा GL_DEPTH_EXT                      0x1801
#घोषणा GL_STENCIL_EXT                    0x1802
प्रकार व्योम (GL_APIENTRYP PFNGLDISCARDFRAMEBUFFEREXTPROC) (GLenum target, GLsizei अंक_Attachments, स्थिर GLenum *attachments);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_API व्योम GL_APIENTRY glDiscardFramebufferEXT (GLenum target, GLsizei अंक_Attachments, स्थिर GLenum *attachments);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_discard_framebuffer */

#अगर_अघोषित GL_EXT_map_बफर_range
#घोषणा GL_EXT_map_बफर_range 1
#घोषणा GL_MAP_READ_BIT_EXT               0x0001
#घोषणा GL_MAP_WRITE_BIT_EXT              0x0002
#घोषणा GL_MAP_INVALIDATE_RANGE_BIT_EXT   0x0004
#घोषणा GL_MAP_INVALIDATE_बफर_BIT_EXT  0x0008
#घोषणा GL_MAP_FLUSH_EXPLICIT_BIT_EXT     0x0010
#घोषणा GL_MAP_UNSYNCHRONIZED_BIT_EXT     0x0020
प्रकार व्योम *(GL_APIENTRYP PFNGLMAPBUFFERRANGEEXTPROC) (GLenum target, GLintptr offset, GLsizeiptr लंबाई, GLbitfield access);
प्रकार व्योम (GL_APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEEXTPROC) (GLenum target, GLintptr offset, GLsizeiptr लंबाई);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_API व्योम *GL_APIENTRY gl_Map_बफर_Range_EXT (GLenum target, GLintptr offset, GLsizeiptr लंबाई, GLbitfield access);
GL_API व्योम GL_APIENTRY gl_Flush_Mapped_बफर_Range_EXT (GLenum target, GLintptr offset, GLsizeiptr लंबाई);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_map_buffer_range */

#अगर_अघोषित GL_EXT_multi_draw_arrays
#घोषणा GL_EXT_multi_draw_arrays 1
प्रकार व्योम (GL_APIENTRYP PFNGLMULTIDRAWARRAYSEXTPROC) (GLenum mode, स्थिर GLint *first, स्थिर GLsizei *गिनती, GLsizei primcount);
प्रकार व्योम (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSEXTPROC) (GLenum mode, स्थिर GLsizei *गिनती, GLenum type, स्थिर व्योम *स्थिर*indices, GLsizei primcount);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_API व्योम GL_APIENTRY glMultiDrawArraysEXT (GLenum mode, स्थिर GLint *first, स्थिर GLsizei *गिनती, GLsizei primcount);
GL_API व्योम GL_APIENTRY glMultiDrawElementsEXT (GLenum mode, स्थिर GLsizei *गिनती, GLenum type, स्थिर व्योम *स्थिर*indices, GLsizei primcount);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_multi_draw_arrays */

#अगर_अघोषित GL_EXT_multisampled_render_to_texture
#घोषणा GL_EXT_multisampled_render_to_texture 1
#घोषणा GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SAMPLES_EXT 0x8D6C
#घोषणा GL_RENDERBUFFER_SAMPLES_EXT       0x8CAB
#घोषणा GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT 0x8D56
#घोषणा GL_MAX_SAMPLES_EXT                0x8D57
प्रकार व्योम (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
प्रकार व्योम (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEEXTPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_API व्योम GL_APIENTRY glRenderbufferStorageMultisampleEXT (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
GL_API व्योम GL_APIENTRY glFramebufferTexture2DMultisampleEXT (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_multisampled_render_to_texture */

#अगर_अघोषित GL_EXT_read_format_bgra
#घोषणा GL_EXT_read_format_bgra 1
#घोषणा GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT 0x8365
#घोषणा GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT 0x8366
#पूर्ण_अगर /* GL_EXT_read_format_bgra */

#अगर_अघोषित GL_EXT_robustness
#घोषणा GL_EXT_robustness 1
#घोषणा GL_GUILTY_CONTEXT_RESET_EXT       0x8253
#घोषणा GL_INNOCENT_CONTEXT_RESET_EXT     0x8254
#घोषणा GL_UNKNOWN_CONTEXT_RESET_EXT      0x8255
#घोषणा GL_CONTEXT_ROBUST_ACCESS_EXT      0x90F3
#घोषणा GL_RESET_NOTIFICATION_STRATEGY_EXT 0x8256
#घोषणा GL_LOSE_CONTEXT_ON_RESET_EXT      0x8252
#घोषणा GL_NO_RESET_NOTIFICATION_EXT      0x8261
प्रकार GLenum (GL_APIENTRYP PFNGLGETGRAPHICSRESETSTATUSEXTPROC) (व्योम);
प्रकार व्योम (GL_APIENTRYP PFNGLREADNPIXELSEXTPROC) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei buf_आकार, व्योम *तथ्य);
प्रकार व्योम (GL_APIENTRYP PFNGLGETNUNIFORMFVEXTPROC) (GLuint program, GLint location, GLsizei buf_आकार, GLfloat *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETNUNIFORMIVEXTPROC) (GLuint program, GLint location, GLsizei buf_आकार, GLint *params);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_API GLenum GL_APIENTRY glGetGraphicsResetStatusEXT (व्योम);
GL_API व्योम GL_APIENTRY glReadnPixelsEXT (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei buf_आकार, व्योम *तथ्य);
GL_API व्योम GL_APIENTRY glGetnUniformfvEXT (GLuint program, GLint location, GLsizei buf_आकार, GLfloat *params);
GL_API व्योम GL_APIENTRY glGetnUniformivEXT (GLuint program, GLint location, GLsizei buf_आकार, GLint *params);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_robustness */

#अगर_अघोषित GL_EXT_sRGB
#घोषणा GL_EXT_sRGB 1
#घोषणा GL_SRGB_EXT                       0x8C40
#घोषणा GL_SRGB_ALPHA_EXT                 0x8C42
#घोषणा GL_SRGB8_ALPHA8_EXT               0x8C43
#घोषणा GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING_EXT 0x8210
#पूर्ण_अगर /* GL_EXT_sRGB */

#अगर_अघोषित GL_EXT_texture_compression_dxt1
#घोषणा GL_EXT_texture_compression_dxt1 1
#घोषणा GL_COMPRESSED_RGB_S3TC_DXT1_EXT   0x83F0
#घोषणा GL_COMPRESSED_RGBA_S3TC_DXT1_EXT  0x83F1
#पूर्ण_अगर /* GL_EXT_texture_compression_dxt1 */

#अगर_अघोषित GL_EXT_texture_filter_anisotropic
#घोषणा GL_EXT_texture_filter_anisotropic 1
#घोषणा GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#घोषणा GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#पूर्ण_अगर /* GL_EXT_texture_filter_anisotropic */

#अगर_अघोषित GL_EXT_texture_format_BGRA8888
#घोषणा GL_EXT_texture_format_BGRA8888 1
#पूर्ण_अगर /* GL_EXT_texture_format_BGRA8888 */

#अगर_अघोषित GL_EXT_texture_lod_bias
#घोषणा GL_EXT_texture_lod_bias 1
#घोषणा GL_MAX_TEXTURE_LOD_BIAS_EXT       0x84FD
#घोषणा GL_TEXTURE_FILTER_CONTROL_EXT     0x8500
#घोषणा GL_TEXTURE_LOD_BIAS_EXT           0x8501
#पूर्ण_अगर /* GL_EXT_texture_lod_bias */

#अगर_अघोषित GL_EXT_texture_storage
#घोषणा GL_EXT_texture_storage 1
#घोषणा GL_TEXTURE_IMMUTABLE_FORMAT_EXT   0x912F
#घोषणा GL_ALPHA8_EXT                     0x803C
#घोषणा GL_LUMINANCE8_EXT                 0x8040
#घोषणा GL_LUMINANCE8_ALPHA8_EXT          0x8045
#घोषणा GL_RGBA32F_EXT                    0x8814
#घोषणा GL_RGB32F_EXT                     0x8815
#घोषणा GL_ALPHA32F_EXT                   0x8816
#घोषणा GL_LUMINANCE32F_EXT               0x8818
#घोषणा GL_LUMINANCE_ALPHA32F_EXT         0x8819
#घोषणा GL_RGBA16F_EXT                    0x881A
#घोषणा GL_RGB16F_EXT                     0x881B
#घोषणा GL_ALPHA16F_EXT                   0x881C
#घोषणा GL_LUMINANCE16F_EXT               0x881E
#घोषणा GL_LUMINANCE_ALPHA16F_EXT         0x881F
#घोषणा GL_R8_EXT                         0x8229
#घोषणा GL_RG8_EXT                        0x822B
#घोषणा GL_R32F_EXT                       0x822E
#घोषणा GL_RG32F_EXT                      0x8230
#घोषणा GL_R16F_EXT                       0x822D
#घोषणा GL_RG16F_EXT                      0x822F
प्रकार व्योम (GL_APIENTRYP PFNGLTEXSTORAGE1DEXTPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXSTORAGE2DEXTPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXSTORAGE3DEXTPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXTURESTORAGE1DEXTPROC) (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXTURESTORAGE2DEXTPROC) (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXTURESTORAGE3DEXTPROC) (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_API व्योम GL_APIENTRY glTexStorage1DEXT (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
GL_API व्योम GL_APIENTRY glTexStorage2DEXT (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
GL_API व्योम GL_APIENTRY glTexStorage3DEXT (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
GL_API व्योम GL_APIENTRY glTextureStorage1DEXT (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
GL_API व्योम GL_APIENTRY glTextureStorage2DEXT (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
GL_API व्योम GL_APIENTRY glTextureStorage3DEXT (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_EXT_texture_storage */

#अगर_अघोषित GL_IMG_multisampled_render_to_texture
#घोषणा GL_IMG_multisampled_render_to_texture 1
#घोषणा GL_RENDERBUFFER_SAMPLES_IMG       0x9133
#घोषणा GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_IMG 0x9134
#घोषणा GL_MAX_SAMPLES_IMG                0x9135
#घोषणा GL_TEXTURE_SAMPLES_IMG            0x9136
प्रकार व्योम (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEIMGPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
प्रकार व्योम (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEIMGPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_API व्योम GL_APIENTRY glRenderbufferStorageMultisampleIMG (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
GL_API व्योम GL_APIENTRY glFramebufferTexture2DMultisampleIMG (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_IMG_multisampled_render_to_texture */

#अगर_अघोषित GL_IMG_read_format
#घोषणा GL_IMG_read_format 1
#घोषणा GL_BGRA_IMG                       0x80E1
#घोषणा GL_UNSIGNED_SHORT_4_4_4_4_REV_IMG 0x8365
#पूर्ण_अगर /* GL_IMG_read_format */

#अगर_अघोषित GL_IMG_texture_compression_pvrtc
#घोषणा GL_IMG_texture_compression_pvrtc 1
#घोषणा GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG 0x8C00
#घोषणा GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG 0x8C01
#घोषणा GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG 0x8C02
#घोषणा GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG 0x8C03
#पूर्ण_अगर /* GL_IMG_texture_compression_pvrtc */

#अगर_अघोषित GL_IMG_texture_env_enhanced_fixed_function
#घोषणा GL_IMG_texture_env_enhanced_fixed_function 1
#घोषणा GL_MODULATE_COLOR_IMG             0x8C04
#घोषणा GL_RECIP_ADD_SIGNED_ALPHA_IMG     0x8C05
#घोषणा GL_TEXTURE_ALPHA_MODULATE_IMG     0x8C06
#घोषणा GL_FACTOR_ALPHA_MODULATE_IMG      0x8C07
#घोषणा GL_FRAGMENT_ALPHA_MODULATE_IMG    0x8C08
#घोषणा GL_ADD_BLEND_IMG                  0x8C09
#घोषणा GL_DOT3_RGBA_IMG                  0x86AF
#पूर्ण_अगर /* GL_IMG_texture_env_enhanced_fixed_function */

#अगर_अघोषित GL_IMG_user_clip_plane
#घोषणा GL_IMG_user_clip_plane 1
#घोषणा GL_CLIP_PLANE0_IMG                0x3000
#घोषणा GL_CLIP_PLANE1_IMG                0x3001
#घोषणा GL_CLIP_PLANE2_IMG                0x3002
#घोषणा GL_CLIP_PLANE3_IMG                0x3003
#घोषणा GL_CLIP_PLANE4_IMG                0x3004
#घोषणा GL_CLIP_PLANE5_IMG                0x3005
#घोषणा GL_MAX_CLIP_PLANES_IMG            0x0D32
प्रकार व्योम (GL_APIENTRYP PFNGLCLIPPLANEFIMGPROC) (GLenum p, स्थिर GLfloat *eqn);
प्रकार व्योम (GL_APIENTRYP PFNGLCLIPPLANEXIMGPROC) (GLenum p, स्थिर GLfixed *eqn);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_API व्योम GL_APIENTRY glClipPlanefIMG (GLenum p, स्थिर GLfloat *eqn);
GL_API व्योम GL_APIENTRY glClipPlanexIMG (GLenum p, स्थिर GLfixed *eqn);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_IMG_user_clip_plane */

#अगर_अघोषित GL_NV_fence
#घोषणा GL_NV_fence 1
#घोषणा GL_ALL_COMPLETED_NV               0x84F2
#घोषणा GL_FENCE_STATUS_NV                0x84F3
#घोषणा GL_FENCE_CONDITION_NV             0x84F4
प्रकार व्योम (GL_APIENTRYP PFNGLDELETEFENCESNVPROC) (GLsizei n, स्थिर GLuint *fences);
प्रकार व्योम (GL_APIENTRYP PFNGLGENFENCESNVPROC) (GLsizei n, GLuint *fences);
प्रकार GLboolean (GL_APIENTRYP PFNGLISFENCENVPROC) (GLuint fence);
प्रकार GLboolean (GL_APIENTRYP PFNGLTESTFENCENVPROC) (GLuint fence);
प्रकार व्योम (GL_APIENTRYP PFNGLGETFENCEIVNVPROC) (GLuint fence, GLenum pname, GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLFINISHFENCENVPROC) (GLuint fence);
प्रकार व्योम (GL_APIENTRYP PFNGLSETFENCENVPROC) (GLuint fence, GLenum condition);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_API व्योम GL_APIENTRY glDeleteFencesNV (GLsizei n, स्थिर GLuint *fences);
GL_API व्योम GL_APIENTRY glGenFencesNV (GLsizei n, GLuint *fences);
GL_API GLboolean GL_APIENTRY glIsFenceNV (GLuint fence);
GL_API GLboolean GL_APIENTRY glTestFenceNV (GLuint fence);
GL_API व्योम GL_APIENTRY glGetFenceivNV (GLuint fence, GLenum pname, GLint *params);
GL_API व्योम GL_APIENTRY glFinishFenceNV (GLuint fence);
GL_API व्योम GL_APIENTRY glSetFenceNV (GLuint fence, GLenum condition);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_NV_fence */

#अगर_अघोषित GL_QCOM_driver_control
#घोषणा GL_QCOM_driver_control 1
प्रकार व्योम (GL_APIENTRYP PFNGLGETDRIVERCONTROLSQCOMPROC) (GLint *अंक, GLsizei आकार, GLuint *driverControls);
प्रकार व्योम (GL_APIENTRYP PFNGLGETDRIVERCONTROLSTRINGQCOMPROC) (GLuint driverControl, GLsizei buf_आकार, GLsizei *लंबाई, GLchar *driverControlString);
प्रकार व्योम (GL_APIENTRYP PFNGLENABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
प्रकार व्योम (GL_APIENTRYP PFNGLDISABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_API व्योम GL_APIENTRY glGetDriverControlsQCOM (GLint *अंक, GLsizei आकार, GLuint *driverControls);
GL_API व्योम GL_APIENTRY glGetDriverControlStringQCOM (GLuint driverControl, GLsizei buf_आकार, GLsizei *लंबाई, GLchar *driverControlString);
GL_API व्योम GL_APIENTRY glEnableDriverControlQCOM (GLuint driverControl);
GL_API व्योम GL_APIENTRY glDisableDriverControlQCOM (GLuint driverControl);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_QCOM_driver_control */

#अगर_अघोषित GL_QCOM_extended_get
#घोषणा GL_QCOM_extended_get 1
#घोषणा GL_TEXTURE_WIDTH_QCOM             0x8BD2
#घोषणा GL_TEXTURE_HEIGHT_QCOM            0x8BD3
#घोषणा GL_TEXTURE_DEPTH_QCOM             0x8BD4
#घोषणा GL_TEXTURE_INTERNAL_FORMAT_QCOM   0x8BD5
#घोषणा GL_TEXTURE_FORMAT_QCOM            0x8BD6
#घोषणा GL_TEXTURE_TYPE_QCOM              0x8BD7
#घोषणा GL_TEXTURE_IMAGE_VALID_QCOM       0x8BD8
#घोषणा GL_TEXTURE_अंक_LEVELS_QCOM        0x8BD9
#घोषणा GL_TEXTURE_TARGET_QCOM            0x8BDA
#घोषणा GL_TEXTURE_OBJECT_VALID_QCOM      0x8BDB
#घोषणा GL_STATE_RESTORE                  0x8BDC
प्रकार व्योम (GL_APIENTRYP PFNGLEXTGETTEXTURESQCOMPROC) (GLuint *textures, GLint maxTextures, GLint *अंक_Textures);
प्रकार व्योम (GL_APIENTRYP PFNGLEXTGETBUFFERSQCOMPROC) (GLuint *buffers, GLint maxBuffers, GLint *अंक_Buffers);
प्रकार व्योम (GL_APIENTRYP PFNGLEXTGETRENDERBUFFERSQCOMPROC) (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *अंक_Renderbuffers);
प्रकार व्योम (GL_APIENTRYP PFNGLEXTGETFRAMEBUFFERSQCOMPROC) (GLuint *framebuffers, GLint maxFramebuffers, GLint *अंक_Framebuffers);
प्रकार व्योम (GL_APIENTRYP PFNGLEXTGETTEXLEVELPARAMETERIVQCOMPROC) (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLEXTTEXOBJECTSTATEOVERRIDEIQCOMPROC) (GLenum target, GLenum pname, GLint param);
प्रकार व्योम (GL_APIENTRYP PFNGLEXTGETTEXSUBIMAGEQCOMPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, व्योम *texels);
प्रकार व्योम (GL_APIENTRYP PFNGLEXTGETBUFFERPOINTERVQCOMPROC) (GLenum target, व्योम **params);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_API व्योम GL_APIENTRY glExtGetTexturesQCOM (GLuint *textures, GLint maxTextures, GLint *अंक_Textures);
GL_API व्योम GL_APIENTRY glExtGetBuffersQCOM (GLuint *buffers, GLint maxBuffers, GLint *अंक_Buffers);
GL_API व्योम GL_APIENTRY glExtGetRenderbuffersQCOM (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *अंक_Renderbuffers);
GL_API व्योम GL_APIENTRY glExtGetFramebuffersQCOM (GLuint *framebuffers, GLint maxFramebuffers, GLint *अंक_Framebuffers);
GL_API व्योम GL_APIENTRY glExtGetTexLevelParameterivQCOM (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
GL_API व्योम GL_APIENTRY glExtTexObjectStateOverrideiQCOM (GLenum target, GLenum pname, GLint param);
GL_API व्योम GL_APIENTRY glExtGetTexSubImageQCOM (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, व्योम *texels);
GL_API व्योम GL_APIENTRY gl_Ext_Get_बफर_Pointerv_QCOM (GLenum target, व्योम **params);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_QCOM_extended_get */

#अगर_अघोषित GL_QCOM_extended_get2
#घोषणा GL_QCOM_extended_get2 1
प्रकार व्योम (GL_APIENTRYP PFNGLEXTGETSHADERSQCOMPROC) (GLuint *shaders, GLint maxShaders, GLint *अंक_Shaders);
प्रकार व्योम (GL_APIENTRYP PFNGLEXTGETPROGRAMSQCOMPROC) (GLuint *programs, GLint maxPrograms, GLint *अंक_Programs);
प्रकार GLboolean (GL_APIENTRYP PFNGLEXTISPROGRAMBINARYQCOMPROC) (GLuint program);
प्रकार व्योम (GL_APIENTRYP PFNGLEXTGETPROGRAMBINARYSOURCEQCOMPROC) (GLuint program, GLenum shadertype, GLchar *source, GLint *लंबाई);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_API व्योम GL_APIENTRY glExtGetShadersQCOM (GLuint *shaders, GLint maxShaders, GLint *अंक_Shaders);
GL_API व्योम GL_APIENTRY glExtGetProgramsQCOM (GLuint *programs, GLint maxPrograms, GLint *अंक_Programs);
GL_API GLboolean GL_APIENTRY gl_Ext_Is_Program_द्विआधारी_QCOM (GLuint program);
GL_API व्योम GL_APIENTRY gl_Ext_Get_Program_द्विआधारी_Source_QCOM (GLuint program, GLenum shadertype, GLchar *source, GLint *लंबाई);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_QCOM_extended_get2 */

#अगर_अघोषित GL_QCOM_perfmon_global_mode
#घोषणा GL_QCOM_perfmon_global_mode 1
#घोषणा GL_PERFMON_GLOBAL_MODE_QCOM       0x8FA0
#पूर्ण_अगर /* GL_QCOM_perfmon_global_mode */

#अगर_अघोषित GL_QCOM_tiled_rendering
#घोषणा GL_QCOM_tiled_rendering 1
#घोषणा GL_COLOR_बफर_BIT0_QCOM         0x00000001
#घोषणा GL_COLOR_बफर_BIT1_QCOM         0x00000002
#घोषणा GL_COLOR_बफर_BIT2_QCOM         0x00000004
#घोषणा GL_COLOR_बफर_BIT3_QCOM         0x00000008
#घोषणा GL_COLOR_बफर_BIT4_QCOM         0x00000010
#घोषणा GL_COLOR_बफर_BIT5_QCOM         0x00000020
#घोषणा GL_COLOR_बफर_BIT6_QCOM         0x00000040
#घोषणा GL_COLOR_बफर_BIT7_QCOM         0x00000080
#घोषणा GL_DEPTH_बफर_BIT0_QCOM         0x00000100
#घोषणा GL_DEPTH_बफर_BIT1_QCOM         0x00000200
#घोषणा GL_DEPTH_बफर_BIT2_QCOM         0x00000400
#घोषणा GL_DEPTH_बफर_BIT3_QCOM         0x00000800
#घोषणा GL_DEPTH_बफर_BIT4_QCOM         0x00001000
#घोषणा GL_DEPTH_बफर_BIT5_QCOM         0x00002000
#घोषणा GL_DEPTH_बफर_BIT6_QCOM         0x00004000
#घोषणा GL_DEPTH_बफर_BIT7_QCOM         0x00008000
#घोषणा GL_STENCIL_बफर_BIT0_QCOM       0x00010000
#घोषणा GL_STENCIL_बफर_BIT1_QCOM       0x00020000
#घोषणा GL_STENCIL_बफर_BIT2_QCOM       0x00040000
#घोषणा GL_STENCIL_बफर_BIT3_QCOM       0x00080000
#घोषणा GL_STENCIL_बफर_BIT4_QCOM       0x00100000
#घोषणा GL_STENCIL_बफर_BIT5_QCOM       0x00200000
#घोषणा GL_STENCIL_बफर_BIT6_QCOM       0x00400000
#घोषणा GL_STENCIL_बफर_BIT7_QCOM       0x00800000
#घोषणा GL_MULTISAMPLE_बफर_BIT0_QCOM   0x01000000
#घोषणा GL_MULTISAMPLE_बफर_BIT1_QCOM   0x02000000
#घोषणा GL_MULTISAMPLE_बफर_BIT2_QCOM   0x04000000
#घोषणा GL_MULTISAMPLE_बफर_BIT3_QCOM   0x08000000
#घोषणा GL_MULTISAMPLE_बफर_BIT4_QCOM   0x10000000
#घोषणा GL_MULTISAMPLE_बफर_BIT5_QCOM   0x20000000
#घोषणा GL_MULTISAMPLE_बफर_BIT6_QCOM   0x40000000
#घोषणा GL_MULTISAMPLE_बफर_BIT7_QCOM   0x80000000
प्रकार व्योम (GL_APIENTRYP PFNGLSTARTTILINGQCOMPROC) (GLuint x, GLuint y, GLuint width, GLuint height, GLbitfield preserveMask);
प्रकार व्योम (GL_APIENTRYP PFNGLENDTILINGQCOMPROC) (GLbitfield preserveMask);
#अगर_घोषित GL_GLEXT_PROTOTYPES
GL_API व्योम GL_APIENTRY glStartTilingQCOM (GLuint x, GLuint y, GLuint width, GLuint height, GLbitfield preserveMask);
GL_API व्योम GL_APIENTRY glEndTilingQCOM (GLbitfield preserveMask);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_QCOM_tiled_rendering */

#अगर_अघोषित GL_QCOM_writeonly_rendering
#घोषणा GL_QCOM_writeonly_rendering 1
#घोषणा GL_WRITEONLY_RENDERING_QCOM       0x8823
#पूर्ण_अगर /* GL_QCOM_writeonly_rendering */

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर
