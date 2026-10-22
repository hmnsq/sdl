#اگر_تعریف_نشده __gles1_glext_h_
#تعریف_کن __gles1_glext_h_ 1

#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر

/*
** Copyright 2013-2026 The Khronos Group Inc.
** SPDX-License-Identifier: MIT
**
** This header is generated from the Khronos OpenGL / OpenGL ES XML
** API Registry. The current version of the Registry, generator scripts
** used to make the header, and the header can be found at
**   https://github.com/KhronosGroup/OpenGL-Registry
*/

#اگر_تعریف_نشده GL_APIENTRYP
#تعریف_کن GL_APIENTRYP GL_APIENTRY*
#پایان_اگر

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

#اگر_تعریف_نشده GL_KHR_debug
#تعریف_کن GL_KHR_debug 1
#پایان_اگر /* GL_KHR_debug */

#اگر_تعریف_نشده GL_OES_EGL_image
#تعریف_کن GL_OES_EGL_image 1
تعريفنوع فراغ *GLeglImageOES;
تعريفنوع فراغ (GL_APIENTRYP PFNGLEGLIMAGETARGETTEXTURE2DOESPROC) (GLenum هدف, GLeglImageOES image);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEGLIMAGETARGETRENDERBUFFERSTORAGEOESPROC) (GLenum هدف, GLeglImageOES image);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY gl_EGLImage_هدف_Texture2_DOES (GLenum هدف, GLeglImageOES image);
GL_API فراغ GL_APIENTRY gl_EGLImage_هدف_Renderbuffer_Storage_OES (GLenum هدف, GLeglImageOES image);
#پایان_اگر
#پایان_اگر /* GL_OES_EGL_image */

#اگر_تعریف_نشده GL_OES_EGL_image_external
#تعریف_کن GL_OES_EGL_image_external 1
#تعریف_کن GL_TEXTURE_EXTERNAL_OES           0x8D65
#تعریف_کن GL_TEXTURE_BINDING_EXTERNAL_OES   0x8D67
#تعریف_کن GL_REQUIRED_TEXTURE_IMAGE_UNITS_OES 0x8D68
#پایان_اگر /* GL_OES_EGL_image_external */

#اگر_تعریف_نشده GL_OES_blend_equation_separate
#تعریف_کن GL_OES_blend_equation_separate 1
#تعریف_کن GL_BLEND_EQUATION_RGB_OES         0x8009
#تعریف_کن GL_BLEND_EQUATION_ALPHA_OES       0x883D
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEOESPROC) (GLenum نما_RGB, GLenum نما_Alpha);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glBlendEquationSeparateOES (GLenum نما_RGB, GLenum نما_Alpha);
#پایان_اگر
#پایان_اگر /* GL_OES_blend_equation_separate */

#اگر_تعریف_نشده GL_OES_blend_func_separate
#تعریف_کن GL_OES_blend_func_separate 1
#تعریف_کن GL_BLEND_DST_RGB_OES              0x80C8
#تعریف_کن GL_BLEND_SRC_RGB_OES              0x80C9
#تعریف_کن GL_BLEND_DST_ALPHA_OES            0x80CA
#تعریف_کن GL_BLEND_SRC_ALPHA_OES            0x80CB
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEOESPROC) (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glBlendFuncSeparateOES (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
#پایان_اگر
#پایان_اگر /* GL_OES_blend_func_separate */

#اگر_تعریف_نشده GL_OES_blend_تفریق
#تعریف_کن GL_OES_blend_تفریق 1
#تعریف_کن GL_BLEND_EQUATION_OES             0x8009
#تعریف_کن GL_FUNC_جمع_کن_OES                   0x8006
#تعریف_کن GL_FUNC_تفریق_OES              0x800A
#تعریف_کن GL_FUNC_معکوس_تفریق_OES      0x800B
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONOESPROC) (GLenum نما);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glBlendEquationOES (GLenum نما);
#پایان_اگر
#پایان_اگر /* GL_OES_blend_subtract */

#اگر_تعریف_نشده GL_OES_byte_coordinates
#تعریف_کن GL_OES_byte_coordinates 1
#پایان_اگر /* GL_OES_byte_coordinates */

#اگر_تعریف_نشده GL_OES_compressed_ETC1_RGB8_sub_texture
#تعریف_کن GL_OES_compressed_ETC1_RGB8_sub_texture 1
#پایان_اگر /* GL_OES_compressed_ETC1_RGB8_sub_texture */

#اگر_تعریف_نشده GL_OES_compressed_ETC1_RGB8_texture
#تعریف_کن GL_OES_compressed_ETC1_RGB8_texture 1
#تعریف_کن GL_ETC1_RGB8_OES                  0x8D64
#پایان_اگر /* GL_OES_compressed_ETC1_RGB8_texture */

#اگر_تعریف_نشده GL_OES_depth24
#تعریف_کن GL_OES_depth24 1
#تعریف_کن GL_عمق_COMPONENT24_OES          0x81A6
#پایان_اگر /* GL_OES_depth24 */

#اگر_تعریف_نشده GL_OES_depth32
#تعریف_کن GL_OES_depth32 1
#تعریف_کن GL_عمق_COMPONENT32_OES          0x81A7
#پایان_اگر /* GL_OES_depth32 */

#اگر_تعریف_نشده GL_OES_draw_texture
#تعریف_کن GL_OES_draw_texture 1
#تعریف_کن GL_TEXTURE_CROP_RECT_OES          0x8B9D
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXSOESPROC) (GLshort x, GLshort y, GLshort z, GLshort عرض, GLshort ارتفاع);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXIOESPROC) (GLint x, GLint y, GLint z, GLint عرض, GLint ارتفاع);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXXOESPROC) (GLfixed x, GLfixed y, GLfixed z, GLfixed عرض, GLfixed ارتفاع);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXSVOESPROC) (ثابت GLshort *coords);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXIVOESPROC) (ثابت GLint *coords);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXXVOESPROC) (ثابت GLfixed *coords);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXFOESPROC) (GLfloat x, GLfloat y, GLfloat z, GLfloat عرض, GLfloat ارتفاع);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWTEXFVOESPROC) (ثابت GLfloat *coords);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glDrawTexsOES (GLshort x, GLshort y, GLshort z, GLshort عرض, GLshort ارتفاع);
GL_API فراغ GL_APIENTRY glDrawTexiOES (GLint x, GLint y, GLint z, GLint عرض, GLint ارتفاع);
GL_API فراغ GL_APIENTRY glDrawTexxOES (GLfixed x, GLfixed y, GLfixed z, GLfixed عرض, GLfixed ارتفاع);
GL_API فراغ GL_APIENTRY glDrawTexsvOES (ثابت GLshort *coords);
GL_API فراغ GL_APIENTRY glDrawTexivOES (ثابت GLint *coords);
GL_API فراغ GL_APIENTRY glDrawTexxvOES (ثابت GLfixed *coords);
GL_API فراغ GL_APIENTRY glDrawTexfOES (GLfloat x, GLfloat y, GLfloat z, GLfloat عرض, GLfloat ارتفاع);
GL_API فراغ GL_APIENTRY glDrawTexfvOES (ثابت GLfloat *coords);
#پایان_اگر
#پایان_اگر /* GL_OES_draw_texture */

#اگر_تعریف_نشده GL_OES_element_شاخص_uint
#تعریف_کن GL_OES_element_شاخص_uint 1
#تعریف_کن GL_UNSIGNED_INT                   0x1405
#پایان_اگر /* GL_OES_element_index_uint */

#اگر_تعریف_نشده GL_OES_extended_ماتریس_palette
#تعریف_کن GL_OES_extended_ماتریس_palette 1
#پایان_اگر /* GL_OES_extended_matrix_palette */

#اگر_تعریف_نشده GL_OES_fbo_render_mipmap
#تعریف_کن GL_OES_fbo_render_mipmap 1
#پایان_اگر /* GL_OES_fbo_render_mipmap */

#اگر_تعریف_نشده GL_OES_fixed_نقطه
#تعریف_کن GL_OES_fixed_نقطه 1
#تعریف_کن GL_FIXED_OES                      0x140C
تعريفنوع فراغ (GL_APIENTRYP PFNGLALPHAFUNCXOESPROC) (GLenum func, GLfixed ref);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARCOLORXOESPROC) (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARDEPTHXOESPROC) (GLfixed عمق_2);
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
تعريفنوع فراغ (GL_APIENTRYP PFNGLLINEWIDTHXOESPROC) (GLfixed عرض);
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
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXENVXOESPROC) (GLenum هدف, GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXENVXVOESPROC) (GLenum هدف, GLenum pname, ثابت GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERXOESPROC) (GLenum هدف, GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERXVOESPROC) (GLenum هدف, GLenum pname, ثابت GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTRANSLATEXOESPROC) (GLfixed x, GLfixed y, GLfixed z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETLIGHTXVOESPROC) (GLenum light, GLenum pname, GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETMATERIALXVOESPROC) (GLenum face, GLenum pname, GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOINTPARAMETERXOESPROC) (GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLECOVERAGEXOESPROC) (GLclampx مقدار, GLboolean invert);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXGENXVOESPROC) (GLenum coord, GLenum pname, GLfixed *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXGENXOESPROC) (GLenum coord, GLenum pname, GLfixed param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXGENXVOESPROC) (GLenum coord, GLenum pname, ثابت GLfixed *params);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glAlphaFuncxOES (GLenum func, GLfixed ref);
GL_API فراغ GL_APIENTRY glClearColorxOES (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GL_API فراغ GL_APIENTRY glClearDepthxOES (GLfixed عمق_2);
GL_API فراغ GL_APIENTRY glClipPlanexOES (GLenum plane, ثابت GLfixed *equation);
GL_API فراغ GL_APIENTRY glColor4xOES (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GL_API فراغ GL_APIENTRY gl_عمق_Rangex_OES (GLfixed n, GLfixed f);
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
GL_API فراغ GL_APIENTRY gl_سطر_Widthx_OES (GLfixed عرض);
GL_API فراغ GL_APIENTRY gl_بارگیری_Matrixx_OES (ثابت GLfixed *m);
GL_API فراغ GL_APIENTRY glMaterialxOES (GLenum face, GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glMaterialxvOES (GLenum face, GLenum pname, ثابت GLfixed *param);
GL_API فراغ GL_APIENTRY glMultMatrixxOES (ثابت GLfixed *m);
GL_API فراغ GL_APIENTRY glMultiTexCoord4xOES (GLenum texture, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
GL_API فراغ GL_APIENTRY glNormal3xOES (GLfixed nx, GLfixed ny, GLfixed nz);
GL_API فراغ GL_APIENTRY glOrthoxOES (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
GL_API فراغ GL_APIENTRY gl_نقطه_Parameterxv_OES (GLenum pname, ثابت GLfixed *params);
GL_API فراغ GL_APIENTRY gl_نقطه_Sizex_OES (GLfixed اندازه);
GL_API فراغ GL_APIENTRY glPolygonOffsetxOES (GLfixed ضریب, GLfixed units);
GL_API فراغ GL_APIENTRY glRotatexOES (GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
GL_API فراغ GL_APIENTRY glScalexOES (GLfixed x, GLfixed y, GLfixed z);
GL_API فراغ GL_APIENTRY glTexEnvxOES (GLenum هدف, GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glTexEnvxvOES (GLenum هدف, GLenum pname, ثابت GLfixed *params);
GL_API فراغ GL_APIENTRY glTexParameterxOES (GLenum هدف, GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glTexParameterxvOES (GLenum هدف, GLenum pname, ثابت GLfixed *params);
GL_API فراغ GL_APIENTRY glTranslatexOES (GLfixed x, GLfixed y, GLfixed z);
GL_API فراغ GL_APIENTRY glGetLightxvOES (GLenum light, GLenum pname, GLfixed *params);
GL_API فراغ GL_APIENTRY glGetMaterialxvOES (GLenum face, GLenum pname, GLfixed *params);
GL_API فراغ GL_APIENTRY gl_نقطه_Parameterx_OES (GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glSampleCoveragexOES (GLclampx مقدار, GLboolean invert);
GL_API فراغ GL_APIENTRY glGetTexGenxvOES (GLenum coord, GLenum pname, GLfixed *params);
GL_API فراغ GL_APIENTRY glTexGenxOES (GLenum coord, GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glTexGenxvOES (GLenum coord, GLenum pname, ثابت GLfixed *params);
#پایان_اگر
#پایان_اگر /* GL_OES_fixed_point */

#اگر_تعریف_نشده GL_OES_framebuffer_object
#تعریف_کن GL_OES_framebuffer_object 1
#تعریف_کن GL_NONE_OES                       0
#تعریف_کن GL_FRAMEBUFFER_OES                0x8D40
#تعریف_کن GL_RENDERBUFFER_OES               0x8D41
#تعریف_کن GL_RGBA4_OES                      0x8056
#تعریف_کن GL_RGB5_A1_OES                    0x8057
#تعریف_کن GL_RGB565_OES                     0x8D62
#تعریف_کن GL_عمق_COMPONENT16_OES          0x81A5
#تعریف_کن GL_RENDERBUFFER_عرض_OES         0x8D42
#تعریف_کن GL_RENDERBUFFER_ارتفاع_OES        0x8D43
#تعریف_کن GL_RENDERBUFFER_داخلی_FORMAT_OES 0x8D44
#تعریف_کن GL_RENDERBUFFER_RED_اندازه_OES      0x8D50
#تعریف_کن GL_RENDERBUFFER_GREEN_اندازه_OES    0x8D51
#تعریف_کن GL_RENDERBUFFER_BLUE_اندازه_OES     0x8D52
#تعریف_کن GL_RENDERBUFFER_ALPHA_اندازه_OES    0x8D53
#تعریف_کن GL_RENDERBUFFER_عمق_اندازه_OES    0x8D54
#تعریف_کن GL_RENDERBUFFER_STENCIL_اندازه_OES  0x8D55
#تعریف_کن GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_OES 0x8CD0
#تعریف_کن GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_OES 0x8CD1
#تعریف_کن GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_OES 0x8CD2
#تعریف_کن GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_OES 0x8CD3
#تعریف_کن GL_COLOR_ATTACHMENT0_OES          0x8CE0
#تعریف_کن GL_عمق_ATTACHMENT_OES           0x8D00
#تعریف_کن GL_STENCIL_ATTACHMENT_OES         0x8D20
#تعریف_کن GL_FRAMEBUFFER_COMPLETE_OES       0x8CD5
#تعریف_کن GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_OES 0x8CD6
#تعریف_کن GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_OES 0x8CD7
#تعریف_کن GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_OES 0x8CD9
#تعریف_کن GL_FRAMEBUFFER_INCOMPLETE_FORMATS_OES 0x8CDA
#تعریف_کن GL_FRAMEBUFFER_UNSUPPORTED_OES    0x8CDD
#تعریف_کن GL_FRAMEBUFFER_BINDING_OES        0x8CA6
#تعریف_کن GL_RENDERBUFFER_BINDING_OES       0x8CA7
#تعریف_کن GL_MAX_RENDERBUFFER_اندازه_OES      0x84E8
#تعریف_کن GL_INVALID_FRAMEBUFFER_OPERATION_OES 0x0506
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISRENDERBUFFEROESPROC) (GLuint renderbuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDRENDERBUFFEROESPROC) (GLenum هدف, GLuint renderbuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETERENDERBUFFERSOESPROC) (GLsizei n, ثابت GLuint *renderbuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENRENDERBUFFERSOESPROC) (GLsizei n, GLuint *renderbuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEOESPROC) (GLenum هدف, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
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
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_API GLboolean GL_APIENTRY glIsRenderbufferOES (GLuint renderbuffer);
GL_API فراغ GL_APIENTRY glBindRenderbufferOES (GLenum هدف, GLuint renderbuffer);
GL_API فراغ GL_APIENTRY glDeleteRenderbuffersOES (GLsizei n, ثابت GLuint *renderbuffers);
GL_API فراغ GL_APIENTRY glGenRenderbuffersOES (GLsizei n, GLuint *renderbuffers);
GL_API فراغ GL_APIENTRY glRenderbufferStorageOES (GLenum هدف, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
GL_API فراغ GL_APIENTRY glGetRenderbufferParameterivOES (GLenum هدف, GLenum pname, GLint *params);
GL_API GLboolean GL_APIENTRY glIsFramebufferOES (GLuint framebuffer);
GL_API فراغ GL_APIENTRY glBindFramebufferOES (GLenum هدف, GLuint framebuffer);
GL_API فراغ GL_APIENTRY glDeleteFramebuffersOES (GLsizei n, ثابت GLuint *framebuffers);
GL_API فراغ GL_APIENTRY glGenFramebuffersOES (GLsizei n, GLuint *framebuffers);
GL_API GLenum GL_APIENTRY gl_Check_Framebuffer_وضعیت_OES (GLenum هدف);
GL_API فراغ GL_APIENTRY glFramebufferRenderbufferOES (GLenum هدف, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
GL_API فراغ GL_APIENTRY glFramebufferTexture2DOES (GLenum هدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GL_API فراغ GL_APIENTRY glGetFramebufferAttachmentParameterivOES (GLenum هدف, GLenum attachment, GLenum pname, GLint *params);
GL_API فراغ GL_APIENTRY glGenerateMipmapOES (GLenum هدف);
#پایان_اگر
#پایان_اگر /* GL_OES_framebuffer_object */

#اگر_تعریف_نشده GL_OES_mapbuffer
#تعریف_کن GL_OES_mapbuffer 1
#تعریف_کن GL_WRITE_ONLY_OES                 0x88B9
#تعریف_کن GL_میانگیر_ACCESS_OES              0x88BB
#تعریف_کن GL_میانگیر_MAPPED_OES              0x88BC
#تعریف_کن GL_میانگیر_MAP_اشاره_گر_OES         0x88BD
تعريفنوع فراغ *(GL_APIENTRYP PFNGLMAPBUFFEROESPROC) (GLenum هدف, GLenum access);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLUNMAPBUFFEROESPROC) (GLenum هدف);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETBUFFERPOINTERVOESPROC) (GLenum هدف, GLenum pname, فراغ **params);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_API فراغ *GL_APIENTRY gl_Map_میانگیر_OES (GLenum هدف, GLenum access);
GL_API GLboolean GL_APIENTRY gl_Unmap_میانگیر_OES (GLenum هدف);
GL_API فراغ GL_APIENTRY gl_Get_میانگیر_Pointerv_OES (GLenum هدف, GLenum pname, فراغ **params);
#پایان_اگر
#پایان_اگر /* GL_OES_mapbuffer */

#اگر_تعریف_نشده GL_OES_ماتریس_get
#تعریف_کن GL_OES_ماتریس_get 1
#تعریف_کن GL_MODELVIEW_ماتریس_FLOAT_AS_INT_بیتها_OES 0x898D
#تعریف_کن GL_PROJECTION_ماتریس_FLOAT_AS_INT_بیتها_OES 0x898E
#تعریف_کن GL_TEXTURE_ماتریس_FLOAT_AS_INT_بیتها_OES 0x898F
#پایان_اگر /* GL_OES_matrix_get */

#اگر_تعریف_نشده GL_OES_ماتریس_palette
#تعریف_کن GL_OES_ماتریس_palette 1
#تعریف_کن GL_MAX_رأس_UNITS_OES           0x86A4
#تعریف_کن GL_MAX_PALETTE_MATRICES_OES       0x8842
#تعریف_کن GL_ماتریس_PALETTE_OES             0x8840
#تعریف_کن GL_ماتریس_شاخص_ARRAY_OES         0x8844
#تعریف_کن GL_وزن_ARRAY_OES               0x86AD
#تعریف_کن GL_CURRENT_PALETTE_ماتریس_OES     0x8843
#تعریف_کن GL_ماتریس_شاخص_ARRAY_اندازه_OES    0x8846
#تعریف_کن GL_ماتریس_شاخص_ARRAY_TYPE_OES    0x8847
#تعریف_کن GL_ماتریس_شاخص_ARRAY_STRIDE_OES  0x8848
#تعریف_کن GL_ماتریس_شاخص_ARRAY_اشاره_گر_OES 0x8849
#تعریف_کن GL_ماتریس_شاخص_ARRAY_میانگیر_BINDING_OES 0x8B9E
#تعریف_کن GL_وزن_ARRAY_اندازه_OES          0x86AB
#تعریف_کن GL_وزن_ARRAY_TYPE_OES          0x86A9
#تعریف_کن GL_وزن_ARRAY_STRIDE_OES        0x86AA
#تعریف_کن GL_وزن_ARRAY_اشاره_گر_OES       0x86AC
#تعریف_کن GL_وزن_ARRAY_میانگیر_BINDING_OES 0x889E
تعريفنوع فراغ (GL_APIENTRYP PFNGLCURRENTPALETTEMATRIXOESPROC) (GLuint matrixpaletteindex);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLOADPALETTEFROMMODELVIEWMATRIXOESPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMATRIXINDEXPOINTEROESPROC) (GLint اندازه, GLenum type, GLsizei stride, ثابت فراغ *اشاره_گر_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLWEIGHTPOINTEROESPROC) (GLint اندازه, GLenum type, GLsizei stride, ثابت فراغ *اشاره_گر_2);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY gl_Current_Palette_ماتریس_OES (GLuint matrixpaletteindex);
GL_API فراغ GL_APIENTRY gl_بارگیری_Palette_From_Model_View_ماتریس_OES (فراغ);
GL_API فراغ GL_APIENTRY gl_ماتریس_شاخص_اشاره_گر_OES (GLint اندازه, GLenum type, GLsizei stride, ثابت فراغ *اشاره_گر_2);
GL_API فراغ GL_APIENTRY gl_وزن_اشاره_گر_OES (GLint اندازه, GLenum type, GLsizei stride, ثابت فراغ *اشاره_گر_2);
#پایان_اگر
#پایان_اگر /* GL_OES_matrix_palette */

#اگر_تعریف_نشده GL_OES_packed_عمق_stencil
#تعریف_کن GL_OES_packed_عمق_stencil 1
#تعریف_کن GL_عمق_STENCIL_OES              0x84F9
#تعریف_کن GL_UNSIGNED_INT_24_8_OES          0x84FA
#تعریف_کن GL_DEPTH24_STENCIL8_OES           0x88F0
#پایان_اگر /* GL_OES_packed_depth_stencil */

#اگر_تعریف_نشده GL_OES_query_ماتریس
#تعریف_کن GL_OES_query_ماتریس 1
تعريفنوع GLbitfield (GL_APIENTRYP PFNGLQUERYMATRIXXOESPROC) (GLfixed *mantissa, GLint *exponent);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_API GLbitfield GL_APIENTRY glQueryMatrixxOES (GLfixed *mantissa, GLint *exponent);
#پایان_اگر
#پایان_اگر /* GL_OES_query_matrix */

#اگر_تعریف_نشده GL_OES_required_internalformat
#تعریف_کن GL_OES_required_internalformat 1
#تعریف_کن GL_ALPHA8_OES                     0x803C
#تعریف_کن GL_LUMINANCE4_ALPHA4_OES          0x8043
#تعریف_کن GL_LUMINANCE8_ALPHA8_OES          0x8045
#تعریف_کن GL_LUMINANCE8_OES                 0x8040
#تعریف_کن GL_RGB8_OES                       0x8051
#تعریف_کن GL_RGBA8_OES                      0x8058
#تعریف_کن GL_RGB10_EXT                      0x8052
#تعریف_کن GL_RGB10_A2_EXT                   0x8059
#پایان_اگر /* GL_OES_required_internalformat */

#اگر_تعریف_نشده GL_OES_rgb8_rgba8
#تعریف_کن GL_OES_rgb8_rgba8 1
#پایان_اگر /* GL_OES_rgb8_rgba8 */

#اگر_تعریف_نشده GL_OES_single_precision
#تعریف_کن GL_OES_single_precision 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARDEPTHFOESPROC) (GLclampf عمق_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLIPPLANEFOESPROC) (GLenum plane, ثابت GLfloat *equation);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHRANGEFOESPROC) (GLclampf n, GLclampf f);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRUSTUMFOESPROC) (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETCLIPPLANEFOESPROC) (GLenum plane, GLfloat *equation);
تعريفنوع فراغ (GL_APIENTRYP PFNGLORTHOFOESPROC) (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glClearDepthfOES (GLclampf عمق_2);
GL_API فراغ GL_APIENTRY glClipPlanefOES (GLenum plane, ثابت GLfloat *equation);
GL_API فراغ GL_APIENTRY gl_عمق_Rangef_OES (GLclampf n, GLclampf f);
GL_API فراغ GL_APIENTRY glFrustumfOES (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
GL_API فراغ GL_APIENTRY glGetClipPlanefOES (GLenum plane, GLfloat *equation);
GL_API فراغ GL_APIENTRY glOrthofOES (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
#پایان_اگر
#پایان_اگر /* GL_OES_single_precision */

#اگر_تعریف_نشده GL_OES_stencil1
#تعریف_کن GL_OES_stencil1 1
#تعریف_کن GL_STENCIL_INDEX1_OES             0x8D46
#پایان_اگر /* GL_OES_stencil1 */

#اگر_تعریف_نشده GL_OES_stencil4
#تعریف_کن GL_OES_stencil4 1
#تعریف_کن GL_STENCIL_INDEX4_OES             0x8D47
#پایان_اگر /* GL_OES_stencil4 */

#اگر_تعریف_نشده GL_OES_stencil8
#تعریف_کن GL_OES_stencil8 1
#تعریف_کن GL_STENCIL_INDEX8_OES             0x8D48
#پایان_اگر /* GL_OES_stencil8 */

#اگر_تعریف_نشده GL_OES_stencil_wrap
#تعریف_کن GL_OES_stencil_wrap 1
#تعریف_کن GL_INCR_WRAP_OES                  0x8507
#تعریف_کن GL_DECR_WRAP_OES                  0x8508
#پایان_اگر /* GL_OES_stencil_wrap */

#اگر_تعریف_نشده GL_OES_surfaceless_context
#تعریف_کن GL_OES_surfaceless_context 1
#تعریف_کن GL_FRAMEBUFFER_UNDEFINED_OES      0x8219
#پایان_اگر /* GL_OES_surfaceless_context */

#اگر_تعریف_نشده GL_OES_texture_cube_map
#تعریف_کن GL_OES_texture_cube_map 1
#تعریف_کن GL_نرمال_MAP_OES                 0x8511
#تعریف_کن GL_REFLECTION_MAP_OES             0x8512
#تعریف_کن GL_TEXTURE_CUBE_MAP_OES           0x8513
#تعریف_کن GL_TEXTURE_BINDING_CUBE_MAP_OES   0x8514
#تعریف_کن GL_TEXTURE_CUBE_MAP_مثبت_X_OES 0x8515
#تعریف_کن GL_TEXTURE_CUBE_MAP_NEGATIVE_X_OES 0x8516
#تعریف_کن GL_TEXTURE_CUBE_MAP_مثبت_Y_OES 0x8517
#تعریف_کن GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_OES 0x8518
#تعریف_کن GL_TEXTURE_CUBE_MAP_مثبت_Z_OES 0x8519
#تعریف_کن GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_OES 0x851A
#تعریف_کن GL_MAX_CUBE_MAP_TEXTURE_اندازه_OES  0x851C
#تعریف_کن GL_TEXTURE_GEN_نما_OES           0x2500
#تعریف_کن GL_TEXTURE_GEN_STR_OES            0x8D60
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXGENFOESPROC) (GLenum coord, GLenum pname, GLfloat param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXGENFVOESPROC) (GLenum coord, GLenum pname, ثابت GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXGENIOESPROC) (GLenum coord, GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXGENIVOESPROC) (GLenum coord, GLenum pname, ثابت GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXGENFVOESPROC) (GLenum coord, GLenum pname, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXGENIVOESPROC) (GLenum coord, GLenum pname, GLint *params);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glTexGenfOES (GLenum coord, GLenum pname, GLfloat param);
GL_API فراغ GL_APIENTRY glTexGenfvOES (GLenum coord, GLenum pname, ثابت GLfloat *params);
GL_API فراغ GL_APIENTRY glTexGeniOES (GLenum coord, GLenum pname, GLint param);
GL_API فراغ GL_APIENTRY glTexGenivOES (GLenum coord, GLenum pname, ثابت GLint *params);
GL_API فراغ GL_APIENTRY glGetTexGenfvOES (GLenum coord, GLenum pname, GLfloat *params);
GL_API فراغ GL_APIENTRY glGetTexGenivOES (GLenum coord, GLenum pname, GLint *params);
#پایان_اگر
#پایان_اگر /* GL_OES_texture_cube_map */

#اگر_تعریف_نشده GL_OES_texture_env_crossbar
#تعریف_کن GL_OES_texture_env_crossbar 1
#پایان_اگر /* GL_OES_texture_env_crossbar */

#اگر_تعریف_نشده GL_OES_texture_mirrored_repeat
#تعریف_کن GL_OES_texture_mirrored_repeat 1
#تعریف_کن GL_MIRRORED_REPEAT_OES            0x8370
#پایان_اگر /* GL_OES_texture_mirrored_repeat */

#اگر_تعریف_نشده GL_OES_texture_npot
#تعریف_کن GL_OES_texture_npot 1
#پایان_اگر /* GL_OES_texture_npot */

#اگر_تعریف_نشده GL_OES_رأس_array_object
#تعریف_کن GL_OES_رأس_array_object 1
#تعریف_کن GL_رأس_ARRAY_BINDING_OES       0x85B5
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDVERTEXARRAYOESPROC) (GLuint array);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEVERTEXARRAYSOESPROC) (GLsizei n, ثابت GLuint *arrays);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENVERTEXARRAYSOESPROC) (GLsizei n, GLuint *arrays);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISVERTEXARRAYOESPROC) (GLuint array);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY gl_Bind_رأس_Array_OES (GLuint array);
GL_API فراغ GL_APIENTRY gl_Delete_رأس_Arrays_OES (GLsizei n, ثابت GLuint *arrays);
GL_API فراغ GL_APIENTRY gl_Gen_رأس_Arrays_OES (GLsizei n, GLuint *arrays);
GL_API GLboolean GL_APIENTRY gl_Is_رأس_Array_OES (GLuint array);
#پایان_اگر
#پایان_اگر /* GL_OES_vertex_array_object */

#اگر_تعریف_نشده GL_AMD_compressed_3DC_texture
#تعریف_کن GL_AMD_compressed_3DC_texture 1
#تعریف_کن GL_3DC_X_AMD                      0x87F9
#تعریف_کن GL_3DC_XY_AMD                     0x87FA
#پایان_اگر /* GL_AMD_compressed_3DC_texture */

#اگر_تعریف_نشده GL_AMD_compressed_ATC_texture
#تعریف_کن GL_AMD_compressed_ATC_texture 1
#تعریف_کن GL_ATC_RGB_AMD                    0x8C92
#تعریف_کن GL_ATC_RGBA_EXPLICIT_ALPHA_AMD    0x8C93
#تعریف_کن GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD 0x87EE
#پایان_اگر /* GL_AMD_compressed_ATC_texture */

#اگر_تعریف_نشده GL_APPLE_copy_texture_سطوح
#تعریف_کن GL_APPLE_copy_texture_سطوح 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYTEXTURELEVELSAPPLEPROC) (GLuint destinationTexture, GLuint منبع_Texture, GLint منبع_پایه_Level, GLsizei منبع_Level_شمار);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY gl_Copy_Texture_سطوح_APPLE (GLuint destinationTexture, GLuint منبع_Texture, GLint منبع_پایه_Level, GLsizei منبع_Level_شمار);
#پایان_اگر
#پایان_اگر /* GL_APPLE_copy_texture_levels */

#اگر_تعریف_نشده GL_APPLE_framebuffer_multisample
#تعریف_کن GL_APPLE_framebuffer_multisample 1
#تعریف_کن GL_RENDERBUFFER_SAMPLES_APPLE     0x8CAB
#تعریف_کن GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_APPLE 0x8D56
#تعریف_کن GL_MAX_SAMPLES_APPLE              0x8D57
#تعریف_کن GL_READ_FRAMEBUFFER_APPLE         0x8CA8
#تعریف_کن GL_DRAW_FRAMEBUFFER_APPLE         0x8CA9
#تعریف_کن GL_DRAW_FRAMEBUFFER_BINDING_APPLE 0x8CA6
#تعریف_کن GL_READ_FRAMEBUFFER_BINDING_APPLE 0x8CAA
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEAPPLEPROC) (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRESOLVEMULTISAMPLEFRAMEBUFFERAPPLEPROC) (فراغ);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glRenderbufferStorageMultisampleAPPLE (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
GL_API فراغ GL_APIENTRY glResolveMultisampleFramebufferAPPLE (فراغ);
#پایان_اگر
#پایان_اگر /* GL_APPLE_framebuffer_multisample */

#اگر_تعریف_نشده GL_APPLE_sync
#تعریف_کن GL_APPLE_sync 1
تعريفنوع بنية __GLsync *GLsync;
تعريفنوع khronos_uint64_t GLuint64;
تعريفنوع khronos_int64_t GLint64;
#تعریف_کن GL_SYNC_OBJECT_APPLE              0x8A53
#تعریف_کن GL_MAX_SERVER_WAIT_TIMEOUT_APPLE  0x9111
#تعریف_کن GL_OBJECT_TYPE_APPLE              0x9112
#تعریف_کن GL_SYNC_CONDITION_APPLE           0x9113
#تعریف_کن GL_SYNC_وضعیت_APPLE              0x9114
#تعریف_کن GL_SYNC_FLAGS_APPLE               0x9115
#تعریف_کن GL_SYNC_FENCE_APPLE               0x9116
#تعریف_کن GL_SYNC_GPU_COMMANDS_COMPLETE_APPLE 0x9117
#تعریف_کن GL_UNSIGNALED_APPLE               0x9118
#تعریف_کن GL_SIGNALED_APPLE                 0x9119
#تعریف_کن GL_ALREADY_SIGNALED_APPLE         0x911A
#تعریف_کن GL_TIMEOUT_EXPIRED_APPLE          0x911B
#تعریف_کن GL_CONDITION_SATISFIED_APPLE      0x911C
#تعریف_کن GL_WAIT_FAILED_APPLE              0x911D
#تعریف_کن GL_SYNC_FLUSH_COMMANDS_بیت_APPLE  0x00000001
#تعریف_کن GL_TIMEOUT_IGNORED_APPLE          0xFFFFFFFFFFFFFFFFull
تعريفنوع GLsync (GL_APIENTRYP PFNGLFENCESYNCAPPLEPROC) (GLenum condition, GLbitfield flags);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISSYNCAPPLEPROC) (GLsync sync);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETESYNCAPPLEPROC) (GLsync sync);
تعريفنوع GLenum (GL_APIENTRYP PFNGLCLIENTWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
تعريفنوع فراغ (GL_APIENTRYP PFNGLWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTEGER64VAPPLEPROC) (GLenum pname, GLint64 *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSYNCIVAPPLEPROC) (GLsync sync, GLenum pname, GLsizei شمار, GLsizei *درازی, GLint *مقادیر);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_API GLsync GL_APIENTRY glFenceSyncAPPLE (GLenum condition, GLbitfield flags);
GL_API GLboolean GL_APIENTRY glIsSyncAPPLE (GLsync sync);
GL_API فراغ GL_APIENTRY glDeleteSyncAPPLE (GLsync sync);
GL_API GLenum GL_APIENTRY glClientWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_API فراغ GL_APIENTRY glWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_API فراغ GL_APIENTRY glGetInteger64vAPPLE (GLenum pname, GLint64 *params);
GL_API فراغ GL_APIENTRY glGetSyncivAPPLE (GLsync sync, GLenum pname, GLsizei شمار, GLsizei *درازی, GLint *مقادیر);
#پایان_اگر
#پایان_اگر /* GL_APPLE_sync */

#اگر_تعریف_نشده GL_APPLE_texture_2D_limited_npot
#تعریف_کن GL_APPLE_texture_2D_limited_npot 1
#پایان_اگر /* GL_APPLE_texture_2D_limited_npot */

#اگر_تعریف_نشده GL_APPLE_texture_format_BGRA8888
#تعریف_کن GL_APPLE_texture_format_BGRA8888 1
#تعریف_کن GL_BGRA_EXT                       0x80E1
#تعریف_کن GL_BGRA8_EXT                      0x93A1
#پایان_اگر /* GL_APPLE_texture_format_BGRA8888 */

#اگر_تعریف_نشده GL_APPLE_texture_max_level
#تعریف_کن GL_APPLE_texture_max_level 1
#تعریف_کن GL_TEXTURE_MAX_LEVEL_APPLE        0x813D
#پایان_اگر /* GL_APPLE_texture_max_level */

#اگر_تعریف_نشده GL_ARM_rgba8
#تعریف_کن GL_ARM_rgba8 1
#پایان_اگر /* GL_ARM_rgba8 */

#اگر_تعریف_نشده GL_EXT_blend_minmax
#تعریف_کن GL_EXT_blend_minmax 1
#تعریف_کن GL_MIN_EXT                        0x8007
#تعریف_کن GL_MAX_EXT                        0x8008
#پایان_اگر /* GL_EXT_blend_minmax */

#اگر_تعریف_نشده GL_EXT_debug_marker
#تعریف_کن GL_EXT_debug_marker 1
تعريفنوع حرف GLchar;
تعريفنوع فراغ (GL_APIENTRYP PFNGLINSERTEVENTMARKEREXTPROC) (GLsizei درازی, ثابت GLchar *marker);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPUSHGROUPMARKEREXTPROC) (GLsizei درازی, ثابت GLchar *marker);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOPGROUPMARKEREXTPROC) (فراغ);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY gl_درج_Event_Marker_EXT (GLsizei درازی, ثابت GLchar *marker);
GL_API فراغ GL_APIENTRY gl_افزودن_گروه_Marker_EXT (GLsizei درازی, ثابت GLchar *marker);
GL_API فراغ GL_APIENTRY gl_برداشت_گروه_Marker_EXT (فراغ);
#پایان_اگر
#پایان_اگر /* GL_EXT_debug_marker */

#اگر_تعریف_نشده GL_EXT_discard_framebuffer
#تعریف_کن GL_EXT_discard_framebuffer 1
#تعریف_کن GL_COLOR_EXT                      0x1800
#تعریف_کن GL_عمق_EXT                      0x1801
#تعریف_کن GL_STENCIL_EXT                    0x1802
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISCARDFRAMEBUFFEREXTPROC) (GLenum هدف, GLsizei رقم_Attachments, ثابت GLenum *attachments);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glDiscardFramebufferEXT (GLenum هدف, GLsizei رقم_Attachments, ثابت GLenum *attachments);
#پایان_اگر
#پایان_اگر /* GL_EXT_discard_framebuffer */

#اگر_تعریف_نشده GL_EXT_map_میانگیر_range
#تعریف_کن GL_EXT_map_میانگیر_range 1
#تعریف_کن GL_MAP_READ_بیت_EXT               0x0001
#تعریف_کن GL_MAP_WRITE_بیت_EXT              0x0002
#تعریف_کن GL_MAP_INVALIDATE_RANGE_بیت_EXT   0x0004
#تعریف_کن GL_MAP_INVALIDATE_میانگیر_بیت_EXT  0x0008
#تعریف_کن GL_MAP_FLUSH_EXPLICIT_بیت_EXT     0x0010
#تعریف_کن GL_MAP_UNSYNCHRONIZED_بیت_EXT     0x0020
تعريفنوع فراغ *(GL_APIENTRYP PFNGLMAPBUFFERRANGEEXTPROC) (GLenum هدف, GLintptr جابه_جایی_2, GLsizeiptr درازی, GLbitfield access);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEEXTPROC) (GLenum هدف, GLintptr جابه_جایی_2, GLsizeiptr درازی);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_API فراغ *GL_APIENTRY gl_Map_میانگیر_Range_EXT (GLenum هدف, GLintptr جابه_جایی_2, GLsizeiptr درازی, GLbitfield access);
GL_API فراغ GL_APIENTRY gl_Flush_Mapped_میانگیر_Range_EXT (GLenum هدف, GLintptr جابه_جایی_2, GLsizeiptr درازی);
#پایان_اگر
#پایان_اگر /* GL_EXT_map_buffer_range */

#اگر_تعریف_نشده GL_EXT_multi_draw_arrays
#تعریف_کن GL_EXT_multi_draw_arrays 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWARRAYSEXTPROC) (GLenum نما, ثابت GLint *اولی, ثابت GLsizei *شمار, GLsizei primcount);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSEXTPROC) (GLenum نما, ثابت GLsizei *شمار, GLenum type, ثابت فراغ *ثابت*indices, GLsizei primcount);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glMultiDrawArraysEXT (GLenum نما, ثابت GLint *اولی, ثابت GLsizei *شمار, GLsizei primcount);
GL_API فراغ GL_APIENTRY glMultiDrawElementsEXT (GLenum نما, ثابت GLsizei *شمار, GLenum type, ثابت فراغ *ثابت*indices, GLsizei primcount);
#پایان_اگر
#پایان_اگر /* GL_EXT_multi_draw_arrays */

#اگر_تعریف_نشده GL_EXT_multisampled_render_مقصد_texture
#تعریف_کن GL_EXT_multisampled_render_مقصد_texture 1
#تعریف_کن GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SAMPLES_EXT 0x8D6C
#تعریف_کن GL_RENDERBUFFER_SAMPLES_EXT       0x8CAB
#تعریف_کن GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT 0x8D56
#تعریف_کن GL_MAX_SAMPLES_EXT                0x8D57
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEEXTPROC) (GLenum هدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glRenderbufferStorageMultisampleEXT (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
GL_API فراغ GL_APIENTRY glFramebufferTexture2DMultisampleEXT (GLenum هدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#پایان_اگر
#پایان_اگر /* GL_EXT_multisampled_render_to_texture */

#اگر_تعریف_نشده GL_EXT_read_format_bgra
#تعریف_کن GL_EXT_read_format_bgra 1
#تعریف_کن GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT 0x8365
#تعریف_کن GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT 0x8366
#پایان_اگر /* GL_EXT_read_format_bgra */

#اگر_تعریف_نشده GL_EXT_robustness
#تعریف_کن GL_EXT_robustness 1
#تعریف_کن GL_GUILTY_CONTEXT_RESET_EXT       0x8253
#تعریف_کن GL_INNOCENT_CONTEXT_RESET_EXT     0x8254
#تعریف_کن GL_UNKNOWN_CONTEXT_RESET_EXT      0x8255
#تعریف_کن GL_CONTEXT_ROBUST_ACCESS_EXT      0x90F3
#تعریف_کن GL_RESET_NOTIFICATION_STRATEGY_EXT 0x8256
#تعریف_کن GL_LOSE_CONTEXT_ON_RESET_EXT      0x8252
#تعریف_کن GL_NO_RESET_NOTIFICATION_EXT      0x8261
تعريفنوع GLenum (GL_APIENTRYP PFNGLGETGRAPHICSRESETSTATUSEXTPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLREADNPIXELSEXTPROC) (GLint x, GLint y, GLsizei عرض, GLsizei ارتفاع, GLenum format, GLenum type, GLsizei buf_اندازه, فراغ *داده);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNUNIFORMFVEXTPROC) (GLuint برنامه, GLint location, GLsizei buf_اندازه, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNUNIFORMIVEXTPROC) (GLuint برنامه, GLint location, GLsizei buf_اندازه, GLint *params);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_API GLenum GL_APIENTRY gl_Get_Graphics_Reset_وضعیت_EXT (فراغ);
GL_API فراغ GL_APIENTRY glReadnPixelsEXT (GLint x, GLint y, GLsizei عرض, GLsizei ارتفاع, GLenum format, GLenum type, GLsizei buf_اندازه, فراغ *داده);
GL_API فراغ GL_APIENTRY glGetnUniformfvEXT (GLuint برنامه, GLint location, GLsizei buf_اندازه, GLfloat *params);
GL_API فراغ GL_APIENTRY glGetnUniformivEXT (GLuint برنامه, GLint location, GLsizei buf_اندازه, GLint *params);
#پایان_اگر
#پایان_اگر /* GL_EXT_robustness */

#اگر_تعریف_نشده GL_EXT_sRGB
#تعریف_کن GL_EXT_sRGB 1
#تعریف_کن GL_SRGB_EXT                       0x8C40
#تعریف_کن GL_SRGB_ALPHA_EXT                 0x8C42
#تعریف_کن GL_SRGB8_ALPHA8_EXT               0x8C43
#تعریف_کن GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING_EXT 0x8210
#پایان_اگر /* GL_EXT_sRGB */

#اگر_تعریف_نشده GL_EXT_texture_compression_dxt1
#تعریف_کن GL_EXT_texture_compression_dxt1 1
#تعریف_کن GL_COMPRESSED_RGB_S3TC_DXT1_EXT   0x83F0
#تعریف_کن GL_COMPRESSED_RGBA_S3TC_DXT1_EXT  0x83F1
#پایان_اگر /* GL_EXT_texture_compression_dxt1 */

#اگر_تعریف_نشده GL_EXT_texture_filter_anisotropic
#تعریف_کن GL_EXT_texture_filter_anisotropic 1
#تعریف_کن GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#تعریف_کن GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#پایان_اگر /* GL_EXT_texture_filter_anisotropic */

#اگر_تعریف_نشده GL_EXT_texture_format_BGRA8888
#تعریف_کن GL_EXT_texture_format_BGRA8888 1
#پایان_اگر /* GL_EXT_texture_format_BGRA8888 */

#اگر_تعریف_نشده GL_EXT_texture_lod_bias
#تعریف_کن GL_EXT_texture_lod_bias 1
#تعریف_کن GL_MAX_TEXTURE_LOD_BIAS_EXT       0x84FD
#تعریف_کن GL_TEXTURE_FILTER_CONTROL_EXT     0x8500
#تعریف_کن GL_TEXTURE_LOD_BIAS_EXT           0x8501
#پایان_اگر /* GL_EXT_texture_lod_bias */

#اگر_تعریف_نشده GL_EXT_texture_storage
#تعریف_کن GL_EXT_texture_storage 1
#تعریف_کن GL_TEXTURE_IMMUTABLE_FORMAT_EXT   0x912F
#تعریف_کن GL_ALPHA8_EXT                     0x803C
#تعریف_کن GL_LUMINANCE8_EXT                 0x8040
#تعریف_کن GL_LUMINANCE8_ALPHA8_EXT          0x8045
#تعریف_کن GL_RGBA32F_EXT                    0x8814
#تعریف_کن GL_RGB32F_EXT                     0x8815
#تعریف_کن GL_ALPHA32F_EXT                   0x8816
#تعریف_کن GL_LUMINANCE32F_EXT               0x8818
#تعریف_کن GL_LUMINANCE_ALPHA32F_EXT         0x8819
#تعریف_کن GL_RGBA16F_EXT                    0x881A
#تعریف_کن GL_RGB16F_EXT                     0x881B
#تعریف_کن GL_ALPHA16F_EXT                   0x881C
#تعریف_کن GL_LUMINANCE16F_EXT               0x881E
#تعریف_کن GL_LUMINANCE_ALPHA16F_EXT         0x881F
#تعریف_کن GL_R8_EXT                         0x8229
#تعریف_کن GL_RG8_EXT                        0x822B
#تعریف_کن GL_R32F_EXT                       0x822E
#تعریف_کن GL_RG32F_EXT                      0x8230
#تعریف_کن GL_R16F_EXT                       0x822D
#تعریف_کن GL_RG16F_EXT                      0x822F
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE1DEXTPROC) (GLenum هدف, GLsizei سطوح, GLenum internalformat, GLsizei عرض);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE2DEXTPROC) (GLenum هدف, GLsizei سطوح, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE3DEXTPROC) (GLenum هدف, GLsizei سطوح, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGE1DEXTPROC) (GLuint texture, GLenum هدف, GLsizei سطوح, GLenum internalformat, GLsizei عرض);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGE2DEXTPROC) (GLuint texture, GLenum هدف, GLsizei سطوح, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXTURESTORAGE3DEXTPROC) (GLuint texture, GLenum هدف, GLsizei سطوح, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glTexStorage1DEXT (GLenum هدف, GLsizei سطوح, GLenum internalformat, GLsizei عرض);
GL_API فراغ GL_APIENTRY glTexStorage2DEXT (GLenum هدف, GLsizei سطوح, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
GL_API فراغ GL_APIENTRY glTexStorage3DEXT (GLenum هدف, GLsizei سطوح, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2);
GL_API فراغ GL_APIENTRY glTextureStorage1DEXT (GLuint texture, GLenum هدف, GLsizei سطوح, GLenum internalformat, GLsizei عرض);
GL_API فراغ GL_APIENTRY glTextureStorage2DEXT (GLuint texture, GLenum هدف, GLsizei سطوح, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
GL_API فراغ GL_APIENTRY glTextureStorage3DEXT (GLuint texture, GLenum هدف, GLsizei سطوح, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2);
#پایان_اگر
#پایان_اگر /* GL_EXT_texture_storage */

#اگر_تعریف_نشده GL_IMG_multisampled_render_مقصد_texture
#تعریف_کن GL_IMG_multisampled_render_مقصد_texture 1
#تعریف_کن GL_RENDERBUFFER_SAMPLES_IMG       0x9133
#تعریف_کن GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_IMG 0x9134
#تعریف_کن GL_MAX_SAMPLES_IMG                0x9135
#تعریف_کن GL_TEXTURE_SAMPLES_IMG            0x9136
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEIMGPROC) (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEIMGPROC) (GLenum هدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glRenderbufferStorageMultisampleIMG (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
GL_API فراغ GL_APIENTRY glFramebufferTexture2DMultisampleIMG (GLenum هدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#پایان_اگر
#پایان_اگر /* GL_IMG_multisampled_render_to_texture */

#اگر_تعریف_نشده GL_IMG_read_format
#تعریف_کن GL_IMG_read_format 1
#تعریف_کن GL_BGRA_IMG                       0x80E1
#تعریف_کن GL_UNSIGNED_SHORT_4_4_4_4_REV_IMG 0x8365
#پایان_اگر /* GL_IMG_read_format */

#اگر_تعریف_نشده GL_IMG_texture_compression_pvrtc
#تعریف_کن GL_IMG_texture_compression_pvrtc 1
#تعریف_کن GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG 0x8C00
#تعریف_کن GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG 0x8C01
#تعریف_کن GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG 0x8C02
#تعریف_کن GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG 0x8C03
#پایان_اگر /* GL_IMG_texture_compression_pvrtc */

#اگر_تعریف_نشده GL_IMG_texture_env_enhanced_fixed_function
#تعریف_کن GL_IMG_texture_env_enhanced_fixed_function 1
#تعریف_کن GL_MODULATE_COLOR_IMG             0x8C04
#تعریف_کن GL_RECIP_جمع_کن_SIGNED_ALPHA_IMG     0x8C05
#تعریف_کن GL_TEXTURE_ALPHA_MODULATE_IMG     0x8C06
#تعریف_کن GL_ضریب_ALPHA_MODULATE_IMG      0x8C07
#تعریف_کن GL_FRAGMENT_ALPHA_MODULATE_IMG    0x8C08
#تعریف_کن GL_جمع_کن_BLEND_IMG                  0x8C09
#تعریف_کن GL_DOT3_RGBA_IMG                  0x86AF
#پایان_اگر /* GL_IMG_texture_env_enhanced_fixed_function */

#اگر_تعریف_نشده GL_IMG_user_clip_plane
#تعریف_کن GL_IMG_user_clip_plane 1
#تعریف_کن GL_CLIP_PLANE0_IMG                0x3000
#تعریف_کن GL_CLIP_PLANE1_IMG                0x3001
#تعریف_کن GL_CLIP_PLANE2_IMG                0x3002
#تعریف_کن GL_CLIP_PLANE3_IMG                0x3003
#تعریف_کن GL_CLIP_PLANE4_IMG                0x3004
#تعریف_کن GL_CLIP_PLANE5_IMG                0x3005
#تعریف_کن GL_MAX_CLIP_PLANES_IMG            0x0D32
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLIPPLANEFIMGPROC) (GLenum p, ثابت GLfloat *eqn);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLIPPLANEXIMGPROC) (GLenum p, ثابت GLfixed *eqn);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glClipPlanefIMG (GLenum p, ثابت GLfloat *eqn);
GL_API فراغ GL_APIENTRY glClipPlanexIMG (GLenum p, ثابت GLfixed *eqn);
#پایان_اگر
#پایان_اگر /* GL_IMG_user_clip_plane */

#اگر_تعریف_نشده GL_NV_fence
#تعریف_کن GL_NV_fence 1
#تعریف_کن GL_ALL_COMPLETED_NV               0x84F2
#تعریف_کن GL_FENCE_وضعیت_NV                0x84F3
#تعریف_کن GL_FENCE_CONDITION_NV             0x84F4
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEFENCESNVPROC) (GLsizei n, ثابت GLuint *fences);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENFENCESNVPROC) (GLsizei n, GLuint *fences);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISFENCENVPROC) (GLuint fence);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLTESTFENCENVPROC) (GLuint fence);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFENCEIVNVPROC) (GLuint fence, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFINISHFENCENVPROC) (GLuint fence);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSETFENCENVPROC) (GLuint fence, GLenum condition);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glDeleteFencesNV (GLsizei n, ثابت GLuint *fences);
GL_API فراغ GL_APIENTRY glGenFencesNV (GLsizei n, GLuint *fences);
GL_API GLboolean GL_APIENTRY glIsFenceNV (GLuint fence);
GL_API GLboolean GL_APIENTRY glTestFenceNV (GLuint fence);
GL_API فراغ GL_APIENTRY glGetFenceivNV (GLuint fence, GLenum pname, GLint *params);
GL_API فراغ GL_APIENTRY gl_پایان_Fence_NV (GLuint fence);
GL_API فراغ GL_APIENTRY gl_مجموعه_Fence_NV (GLuint fence, GLenum condition);
#پایان_اگر
#پایان_اگر /* GL_NV_fence */

#اگر_تعریف_نشده GL_QCOM_driver_control
#تعریف_کن GL_QCOM_driver_control 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETDRIVERCONTROLSQCOMPROC) (GLint *رقم, GLsizei اندازه, GLuint *driverControls);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETDRIVERCONTROLSTRINGQCOMPROC) (GLuint driverControl, GLsizei buf_اندازه, GLsizei *درازی, GLchar *driverControlString);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glGetDriverControlsQCOM (GLint *رقم, GLsizei اندازه, GLuint *driverControls);
GL_API فراغ GL_APIENTRY glGetDriverControlStringQCOM (GLuint driverControl, GLsizei buf_اندازه, GLsizei *درازی, GLchar *driverControlString);
GL_API فراغ GL_APIENTRY glEnableDriverControlQCOM (GLuint driverControl);
GL_API فراغ GL_APIENTRY glDisableDriverControlQCOM (GLuint driverControl);
#پایان_اگر
#پایان_اگر /* GL_QCOM_driver_control */

#اگر_تعریف_نشده GL_QCOM_extended_get
#تعریف_کن GL_QCOM_extended_get 1
#تعریف_کن GL_TEXTURE_عرض_QCOM             0x8BD2
#تعریف_کن GL_TEXTURE_ارتفاع_QCOM            0x8BD3
#تعریف_کن GL_TEXTURE_عمق_QCOM             0x8BD4
#تعریف_کن GL_TEXTURE_داخلی_FORMAT_QCOM   0x8BD5
#تعریف_کن GL_TEXTURE_FORMAT_QCOM            0x8BD6
#تعریف_کن GL_TEXTURE_TYPE_QCOM              0x8BD7
#تعریف_کن GL_TEXTURE_IMAGE_VALID_QCOM       0x8BD8
#تعریف_کن GL_TEXTURE_رقم_سطوح_QCOM        0x8BD9
#تعریف_کن GL_TEXTURE_هدف_QCOM            0x8BDA
#تعریف_کن GL_TEXTURE_OBJECT_VALID_QCOM      0x8BDB
#تعریف_کن GL_STATE_RESTORE                  0x8BDC
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETTEXTURESQCOMPROC) (GLuint *textures, GLint maxTextures, GLint *رقم_Textures);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETBUFFERSQCOMPROC) (GLuint *buffers, GLint maxBuffers, GLint *رقم_Buffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETRENDERBUFFERSQCOMPROC) (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *رقم_Renderbuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETFRAMEBUFFERSQCOMPROC) (GLuint *framebuffers, GLint maxFramebuffers, GLint *رقم_Framebuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETTEXLEVELPARAMETERIVQCOMPROC) (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTTEXOBJECTSTATEOVERRIDEIQCOMPROC) (GLenum هدف, GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETTEXSUBIMAGEQCOMPROC) (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLenum format, GLenum type, فراغ *texels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETBUFFERPOINTERVQCOMPROC) (GLenum هدف, فراغ **params);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glExtGetTexturesQCOM (GLuint *textures, GLint maxTextures, GLint *رقم_Textures);
GL_API فراغ GL_APIENTRY glExtGetBuffersQCOM (GLuint *buffers, GLint maxBuffers, GLint *رقم_Buffers);
GL_API فراغ GL_APIENTRY glExtGetRenderbuffersQCOM (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *رقم_Renderbuffers);
GL_API فراغ GL_APIENTRY glExtGetFramebuffersQCOM (GLuint *framebuffers, GLint maxFramebuffers, GLint *رقم_Framebuffers);
GL_API فراغ GL_APIENTRY glExtGetTexLevelParameterivQCOM (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
GL_API فراغ GL_APIENTRY glExtTexObjectStateOverrideiQCOM (GLenum هدف, GLenum pname, GLint param);
GL_API فراغ GL_APIENTRY glExtGetTexSubImageQCOM (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLenum format, GLenum type, فراغ *texels);
GL_API فراغ GL_APIENTRY gl_Ext_Get_میانگیر_Pointerv_QCOM (GLenum هدف, فراغ **params);
#پایان_اگر
#پایان_اگر /* GL_QCOM_extended_get */

#اگر_تعریف_نشده GL_QCOM_extended_get2
#تعریف_کن GL_QCOM_extended_get2 1
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETSHADERSQCOMPROC) (GLuint *shaders, GLint maxShaders, GLint *رقم_Shaders);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETPROGRAMSQCOMPROC) (GLuint *programs, GLint maxPrograms, GLint *رقم_Programs);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLEXTISPROGRAMBINARYQCOMPROC) (GLuint برنامه);
تعريفنوع فراغ (GL_APIENTRYP PFNGLEXTGETPROGRAMBINARYSOURCEQCOMPROC) (GLuint برنامه, GLenum shadertype, GLchar *منبع, GLint *درازی);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY glExtGetShadersQCOM (GLuint *shaders, GLint maxShaders, GLint *رقم_Shaders);
GL_API فراغ GL_APIENTRY glExtGetProgramsQCOM (GLuint *programs, GLint maxPrograms, GLint *رقم_Programs);
GL_API GLboolean GL_APIENTRY gl_Ext_Is_برنامه_دودویی_QCOM (GLuint برنامه);
GL_API فراغ GL_APIENTRY gl_Ext_Get_برنامه_دودویی_منبع_QCOM (GLuint برنامه, GLenum shadertype, GLchar *منبع, GLint *درازی);
#پایان_اگر
#پایان_اگر /* GL_QCOM_extended_get2 */

#اگر_تعریف_نشده GL_QCOM_perfmon_global_نما
#تعریف_کن GL_QCOM_perfmon_global_نما 1
#تعریف_کن GL_PERFMON_GLOBAL_نما_QCOM       0x8FA0
#پایان_اگر /* GL_QCOM_perfmon_global_mode */

#اگر_تعریف_نشده GL_QCOM_tiled_rendering
#تعریف_کن GL_QCOM_tiled_rendering 1
#تعریف_کن GL_COLOR_میانگیر_BIT0_QCOM         0x00000001
#تعریف_کن GL_COLOR_میانگیر_BIT1_QCOM         0x00000002
#تعریف_کن GL_COLOR_میانگیر_BIT2_QCOM         0x00000004
#تعریف_کن GL_COLOR_میانگیر_BIT3_QCOM         0x00000008
#تعریف_کن GL_COLOR_میانگیر_BIT4_QCOM         0x00000010
#تعریف_کن GL_COLOR_میانگیر_BIT5_QCOM         0x00000020
#تعریف_کن GL_COLOR_میانگیر_BIT6_QCOM         0x00000040
#تعریف_کن GL_COLOR_میانگیر_BIT7_QCOM         0x00000080
#تعریف_کن GL_عمق_میانگیر_BIT0_QCOM         0x00000100
#تعریف_کن GL_عمق_میانگیر_BIT1_QCOM         0x00000200
#تعریف_کن GL_عمق_میانگیر_BIT2_QCOM         0x00000400
#تعریف_کن GL_عمق_میانگیر_BIT3_QCOM         0x00000800
#تعریف_کن GL_عمق_میانگیر_BIT4_QCOM         0x00001000
#تعریف_کن GL_عمق_میانگیر_BIT5_QCOM         0x00002000
#تعریف_کن GL_عمق_میانگیر_BIT6_QCOM         0x00004000
#تعریف_کن GL_عمق_میانگیر_BIT7_QCOM         0x00008000
#تعریف_کن GL_STENCIL_میانگیر_BIT0_QCOM       0x00010000
#تعریف_کن GL_STENCIL_میانگیر_BIT1_QCOM       0x00020000
#تعریف_کن GL_STENCIL_میانگیر_BIT2_QCOM       0x00040000
#تعریف_کن GL_STENCIL_میانگیر_BIT3_QCOM       0x00080000
#تعریف_کن GL_STENCIL_میانگیر_BIT4_QCOM       0x00100000
#تعریف_کن GL_STENCIL_میانگیر_BIT5_QCOM       0x00200000
#تعریف_کن GL_STENCIL_میانگیر_BIT6_QCOM       0x00400000
#تعریف_کن GL_STENCIL_میانگیر_BIT7_QCOM       0x00800000
#تعریف_کن GL_MULTISAMPLE_میانگیر_BIT0_QCOM   0x01000000
#تعریف_کن GL_MULTISAMPLE_میانگیر_BIT1_QCOM   0x02000000
#تعریف_کن GL_MULTISAMPLE_میانگیر_BIT2_QCOM   0x04000000
#تعریف_کن GL_MULTISAMPLE_میانگیر_BIT3_QCOM   0x08000000
#تعریف_کن GL_MULTISAMPLE_میانگیر_BIT4_QCOM   0x10000000
#تعریف_کن GL_MULTISAMPLE_میانگیر_BIT5_QCOM   0x20000000
#تعریف_کن GL_MULTISAMPLE_میانگیر_BIT6_QCOM   0x40000000
#تعریف_کن GL_MULTISAMPLE_میانگیر_BIT7_QCOM   0x80000000
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTARTTILINGQCOMPROC) (GLuint x, GLuint y, GLuint عرض, GLuint ارتفاع, GLbitfield preserve_ماسک);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENDTILINGQCOMPROC) (GLbitfield preserve_ماسک);
#اگر_تعریف_شده GL_GLEXT_PROTOTYPES
GL_API فراغ GL_APIENTRY gl_شروع_Tiling_QCOM (GLuint x, GLuint y, GLuint عرض, GLuint ارتفاع, GLbitfield preserve_ماسک);
GL_API فراغ GL_APIENTRY gl_انتها_Tiling_QCOM (GLbitfield preserve_ماسک);
#پایان_اگر
#پایان_اگر /* GL_QCOM_tiled_rendering */

#اگر_تعریف_نشده GL_QCOM_writeonly_rendering
#تعریف_کن GL_QCOM_writeonly_rendering 1
#تعریف_کن GL_WRITEONLY_RENDERING_QCOM       0x8823
#پایان_اگر /* GL_QCOM_writeonly_rendering */

#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر
