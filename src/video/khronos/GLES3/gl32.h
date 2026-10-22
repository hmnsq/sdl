#ifndef __gles2_gl32_h_
#define __gles2_gl32_h_ 1

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

#ضمن <GLES3/gl3platform.h>

#ifndef GL_APIENTRYP
#define GL_APIENTRYP GL_APIENTRY*
#endif

#ifndef GL_GLES_PROTOTYPES
#define GL_GLES_PROTOTYPES 1
#endif

/* Generated on date 20260803 */

/* Generated C header for:
 * API: gles2
 * Profile: common
 * Versions considered: 2\.[0-9]|3\.[012]
 * Versions emitted: .*
 * Default extensions included: None
 * Additional extensions included: _nomatch_^
 * Extensions removed: _nomatch_^
 */

#ifndef GL_ES_VERSION_2_0
#define GL_ES_VERSION_2_0 1
#ضمن <KHR/khrplatform.h>
تعريفنوع khronos_int8_t GLbyte;
تعريفنوع khronos_float_t GLclampf;
تعريفنوع khronos_int32_t GLfixed;
تعريفنوع khronos_int16_t GLshort;
تعريفنوع khronos_uint16_t GLushort;
تعريفنوع فراغ GLvoid;
تعريفنوع بنية __GLsync *GLsync;
تعريفنوع khronos_int64_t GLint64;
تعريفنوع khronos_uint64_t GLuint64;
تعريفنوع unsigned صحيح GLenum;
تعريفنوع unsigned صحيح GLuint;
تعريفنوع حرف GLchar;
تعريفنوع khronos_float_t GLfloat;
تعريفنوع khronos_ssize_t GLsizeiptr;
تعريفنوع khronos_intptr_t GLintptr;
تعريفنوع unsigned صحيح GLbitfield;
تعريفنوع صحيح GLint;
تعريفنوع unsigned حرف GLboolean;
تعريفنوع صحيح GLsizei;
تعريفنوع khronos_uint8_t GLubyte;
#define GL_DEPTH_BUFFER_BIT               0x00000100
#define GL_STENCIL_BUFFER_BIT             0x00000400
#define GL_COLOR_BUFFER_BIT               0x00004000
#define GL_FALSE                          0
#define GL_TRUE                           1
#define GL_POINTS                         0x0000
#define GL_أسطر                          0x0001
#define GL_سطر_LOOP                      0x0002
#define GL_سطر_STRIP                     0x0003
#define GL_TRIANGLES                      0x0004
#define GL_TRIANGLE_STRIP                 0x0005
#define GL_TRIANGLE_FAN                   0x0006
#define GL_ZERO                           0
#define GL_ONE                            1
#define GL_SRC_COLOR                      0x0300
#define GL_ONE_MINUS_SRC_COLOR            0x0301
#define GL_SRC_ALPHA                      0x0302
#define GL_ONE_MINUS_SRC_ALPHA            0x0303
#define GL_DST_ALPHA                      0x0304
#define GL_ONE_MINUS_DST_ALPHA            0x0305
#define GL_DST_COLOR                      0x0306
#define GL_ONE_MINUS_DST_COLOR            0x0307
#define GL_SRC_ALPHA_SATURATE             0x0308
#define GL_FUNC_ADD                       0x8006
#define GL_BLEND_EQUATION                 0x8009
#define GL_BLEND_EQUATION_RGB             0x8009
#define GL_BLEND_EQUATION_ALPHA           0x883D
#define GL_FUNC_SUBTRACT                  0x800A
#define GL_FUNC_REVERSE_SUBTRACT          0x800B
#define GL_BLEND_DST_RGB                  0x80C8
#define GL_BLEND_SRC_RGB                  0x80C9
#define GL_BLEND_DST_ALPHA                0x80CA
#define GL_BLEND_SRC_ALPHA                0x80CB
#define GL_CONSTANT_COLOR                 0x8001
#define GL_ONE_MINUS_CONSTANT_COLOR       0x8002
#define GL_CONSTANT_ALPHA                 0x8003
#define GL_ONE_MINUS_CONSTANT_ALPHA       0x8004
#define GL_BLEND_COLOR                    0x8005
#define GL_ARRAY_BUFFER                   0x8892
#define GL_ELEMENT_ARRAY_BUFFER           0x8893
#define GL_ARRAY_BUFFER_BINDING           0x8894
#define GL_ELEMENT_ARRAY_BUFFER_BINDING   0x8895
#define GL_STREAM_DRAW                    0x88E0
#define GL_STATIC_DRAW                    0x88E4
#define GL_DYNAMIC_DRAW                   0x88E8
#define GL_BUFFER_SIZE                    0x8764
#define GL_BUFFER_USAGE                   0x8765
#define GL_CURRENT_VERTEX_ATTRIB          0x8626
#define GL_FRONT                          0x0404
#define GL_BACK                           0x0405
#define GL_FRONT_AND_BACK                 0x0408
#define GL_TEXTURE_2D                     0x0DE1
#define GL_CULL_FACE                      0x0B44
#define GL_BLEND                          0x0BE2
#define GL_DITHER                         0x0BD0
#define GL_STENCIL_TEST                   0x0B90
#define GL_DEPTH_TEST                     0x0B71
#define GL_SCISSOR_TEST                   0x0C11
#define GL_POLYGON_OFFSET_FILL            0x8037
#define GL_SAMPLE_ALPHA_TO_COVERAGE       0x809E
#define GL_SAMPLE_COVERAGE                0x80A0
#define GL_NO_ERROR                       0
#define GL_INVALID_ENUM                   0x0500
#define GL_INVALID_قيمة                  0x0501
#define GL_INVALID_OPERATION              0x0502
#define GL_OUT_OF_MEMORY                  0x0505
#define GL_CW                             0x0900
#define GL_CCW                            0x0901
#define GL_سطر_WIDTH                     0x0B21
#define GL_ALIASED_POINT_SIZE_RANGE       0x846D
#define GL_ALIASED_سطر_WIDTH_RANGE       0x846E
#define GL_CULL_FACE_MODE                 0x0B45
#define GL_FRONT_FACE                     0x0B46
#define GL_DEPTH_RANGE                    0x0B70
#define GL_DEPTH_WRITEMASK                0x0B72
#define GL_DEPTH_CLEAR_قيمة              0x0B73
#define GL_DEPTH_FUNC                     0x0B74
#define GL_STENCIL_CLEAR_قيمة            0x0B91
#define GL_STENCIL_FUNC                   0x0B92
#define GL_STENCIL_FAIL                   0x0B94
#define GL_STENCIL_PASS_DEPTH_FAIL        0x0B95
#define GL_STENCIL_PASS_DEPTH_PASS        0x0B96
#define GL_STENCIL_REF                    0x0B97
#define GL_STENCIL_قيمة_MASK             0x0B93
#define GL_STENCIL_WRITEMASK              0x0B98
#define GL_STENCIL_BACK_FUNC              0x8800
#define GL_STENCIL_BACK_FAIL              0x8801
#define GL_STENCIL_BACK_PASS_DEPTH_FAIL   0x8802
#define GL_STENCIL_BACK_PASS_DEPTH_PASS   0x8803
#define GL_STENCIL_BACK_REF               0x8CA3
#define GL_STENCIL_BACK_قيمة_MASK        0x8CA4
#define GL_STENCIL_BACK_WRITEMASK         0x8CA5
#define GL_VIEWPORT                       0x0BA2
#define GL_SCISSOR_BOX                    0x0C10
#define GL_COLOR_CLEAR_قيمة              0x0C22
#define GL_COLOR_WRITEMASK                0x0C23
#define GL_UNPACK_ALIGNMENT               0x0CF5
#define GL_PACK_ALIGNMENT                 0x0D05
#define GL_MAX_TEXTURE_SIZE               0x0D33
#define GL_MAX_VIEWPORT_DIMS              0x0D3A
#define GL_SUBPIXEL_BITS                  0x0D50
#define GL_RED_BITS                       0x0D52
#define GL_GREEN_BITS                     0x0D53
#define GL_BLUE_BITS                      0x0D54
#define GL_ALPHA_BITS                     0x0D55
#define GL_DEPTH_BITS                     0x0D56
#define GL_STENCIL_BITS                   0x0D57
#define GL_POLYGON_OFFSET_UNITS           0x2A00
#define GL_POLYGON_OFFSET_FACTOR          0x8038
#define GL_TEXTURE_BINDING_2D             0x8069
#define GL_SAMPLE_BUFFERS                 0x80A8
#define GL_SAMPLES                        0x80A9
#define GL_SAMPLE_COVERAGE_قيمة          0x80AA
#define GL_SAMPLE_COVERAGE_INVERT         0x80AB
#define GL_رقم_COMPRESSED_TEXTURE_FORMATS 0x86A2
#define GL_COMPRESSED_TEXTURE_FORMATS     0x86A3
#define GL_DONT_CARE                      0x1100
#define GL_FASTEST                        0x1101
#define GL_NICEST                         0x1102
#define GL_GENERATE_MIPMAP_HINT           0x8192
#define GL_BYTE                           0x1400
#define GL_UNSIGNED_BYTE                  0x1401
#define GL_SHORT                          0x1402
#define GL_UNSIGNED_SHORT                 0x1403
#define GL_INT                            0x1404
#define GL_UNSIGNED_INT                   0x1405
#define GL_FLOAT                          0x1406
#define GL_FIXED                          0x140C
#define GL_DEPTH_COMPONENT                0x1902
#define GL_ALPHA                          0x1906
#define GL_RGB                            0x1907
#define GL_RGBA                           0x1908
#define GL_LUMINANCE                      0x1909
#define GL_LUMINANCE_ALPHA                0x190A
#define GL_UNSIGNED_SHORT_4_4_4_4         0x8033
#define GL_UNSIGNED_SHORT_5_5_5_1         0x8034
#define GL_UNSIGNED_SHORT_5_6_5           0x8363
#define GL_FRAGMENT_SHADER                0x8B30
#define GL_VERTEX_SHADER                  0x8B31
#define GL_MAX_VERTEX_ATTRIBS             0x8869
#define GL_MAX_VERTEX_UNIFORM_VECTORS     0x8DFB
#define GL_MAX_VARYING_VECTORS            0x8DFC
#define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 0x8B4D
#define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS 0x8B4C
#define GL_MAX_TEXTURE_IMAGE_UNITS        0x8872
#define GL_MAX_FRAGMENT_UNIFORM_VECTORS   0x8DFD
#define GL_SHADER_TYPE                    0x8B4F
#define GL_DELETE_STATUS                  0x8B80
#define GL_LINK_STATUS                    0x8B82
#define GL_VALIDATE_STATUS                0x8B83
#define GL_ATTACHED_SHADERS               0x8B85
#define GL_ACTIVE_UNIFORMS                0x8B86
#define GL_ACTIVE_UNIFORM_MAX_LENGTH      0x8B87
#define GL_ACTIVE_ATTRIBUTES              0x8B89
#define GL_ACTIVE_ATTRIBUTE_MAX_LENGTH    0x8B8A
#define GL_SHADING_LANGUAGE_VERSION       0x8B8C
#define GL_CURRENT_PROGRAM                0x8B8D
#define GL_NEVER                          0x0200
#define GL_LESS                           0x0201
#define GL_EQUAL                          0x0202
#define GL_LEQUAL                         0x0203
#define GL_GREATER                        0x0204
#define GL_NOTEQUAL                       0x0205
#define GL_GEQUAL                         0x0206
#define GL_ALWAYS                         0x0207
#define GL_KEEP                           0x1E00
#define GL_REPLACE                        0x1E01
#define GL_INCR                           0x1E02
#define GL_DECR                           0x1E03
#define GL_INVERT                         0x150A
#define GL_INCR_WRAP                      0x8507
#define GL_DECR_WRAP                      0x8508
#define GL_VENDOR                         0x1F00
#define GL_RENDERER                       0x1F01
#define GL_VERSION                        0x1F02
#define GL_EXTENSIONS                     0x1F03
#define GL_NEAREST                        0x2600
#define GL_LINEAR                         0x2601
#define GL_NEAREST_MIPMAP_NEAREST         0x2700
#define GL_LINEAR_MIPMAP_NEAREST          0x2701
#define GL_NEAREST_MIPMAP_LINEAR          0x2702
#define GL_LINEAR_MIPMAP_LINEAR           0x2703
#define GL_TEXTURE_MAG_FILTER             0x2800
#define GL_TEXTURE_MIN_FILTER             0x2801
#define GL_TEXTURE_WRAP_S                 0x2802
#define GL_TEXTURE_WRAP_T                 0x2803
#define GL_TEXTURE                        0x1702
#define GL_TEXTURE_CUBE_MAP               0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP       0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X    0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X    0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y    0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y    0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z    0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z    0x851A
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE      0x851C
#define GL_TEXTURE0                       0x84C0
#define GL_TEXTURE1                       0x84C1
#define GL_TEXTURE2                       0x84C2
#define GL_TEXTURE3                       0x84C3
#define GL_TEXTURE4                       0x84C4
#define GL_TEXTURE5                       0x84C5
#define GL_TEXTURE6                       0x84C6
#define GL_TEXTURE7                       0x84C7
#define GL_TEXTURE8                       0x84C8
#define GL_TEXTURE9                       0x84C9
#define GL_TEXTURE10                      0x84CA
#define GL_TEXTURE11                      0x84CB
#define GL_TEXTURE12                      0x84CC
#define GL_TEXTURE13                      0x84CD
#define GL_TEXTURE14                      0x84CE
#define GL_TEXTURE15                      0x84CF
#define GL_TEXTURE16                      0x84D0
#define GL_TEXTURE17                      0x84D1
#define GL_TEXTURE18                      0x84D2
#define GL_TEXTURE19                      0x84D3
#define GL_TEXTURE20                      0x84D4
#define GL_TEXTURE21                      0x84D5
#define GL_TEXTURE22                      0x84D6
#define GL_TEXTURE23                      0x84D7
#define GL_TEXTURE24                      0x84D8
#define GL_TEXTURE25                      0x84D9
#define GL_TEXTURE26                      0x84DA
#define GL_TEXTURE27                      0x84DB
#define GL_TEXTURE28                      0x84DC
#define GL_TEXTURE29                      0x84DD
#define GL_TEXTURE30                      0x84DE
#define GL_TEXTURE31                      0x84DF
#define GL_ACTIVE_TEXTURE                 0x84E0
#define GL_REPEAT                         0x2901
#define GL_CLAMP_TO_EDGE                  0x812F
#define GL_MIRRORED_REPEAT                0x8370
#define GL_FLOAT_VEC2                     0x8B50
#define GL_FLOAT_VEC3                     0x8B51
#define GL_FLOAT_VEC4                     0x8B52
#define GL_INT_VEC2                       0x8B53
#define GL_INT_VEC3                       0x8B54
#define GL_INT_VEC4                       0x8B55
#define GL_BOOL                           0x8B56
#define GL_BOOL_VEC2                      0x8B57
#define GL_BOOL_VEC3                      0x8B58
#define GL_BOOL_VEC4                      0x8B59
#define GL_FLOAT_MAT2                     0x8B5A
#define GL_FLOAT_MAT3                     0x8B5B
#define GL_FLOAT_MAT4                     0x8B5C
#define GL_SAMPLER_2D                     0x8B5E
#define GL_SAMPLER_CUBE                   0x8B60
#define GL_VERTEX_ATTRIB_ARRAY_ENABLED    0x8622
#define GL_VERTEX_ATTRIB_ARRAY_SIZE       0x8623
#define GL_VERTEX_ATTRIB_ARRAY_STRIDE     0x8624
#define GL_VERTEX_ATTRIB_ARRAY_TYPE       0x8625
#define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED 0x886A
#define GL_VERTEX_ATTRIB_ARRAY_POINTER    0x8645
#define GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING 0x889F
#define GL_IMPLEMENTATION_COLOR_READ_TYPE 0x8B9A
#define GL_IMPLEMENTATION_COLOR_READ_FORMAT 0x8B9B
#define GL_COMPILE_STATUS                 0x8B81
#define GL_INFO_LOG_LENGTH                0x8B84
#define GL_SHADER_SOURCE_LENGTH           0x8B88
#define GL_SHADER_COMPILER                0x8DFA
#define GL_SHADER_ثنائي_FORMATS          0x8DF8
#define GL_رقم_SHADER_ثنائي_FORMATS      0x8DF9
#define GL_أدنى_FLOAT                      0x8DF0
#define GL_MEDIUM_FLOAT                   0x8DF1
#define GL_عالي_FLOAT                     0x8DF2
#define GL_أدنى_INT                        0x8DF3
#define GL_MEDIUM_INT                     0x8DF4
#define GL_عالي_INT                       0x8DF5
#define GL_FRAMEBUFFER                    0x8D40
#define GL_RENDERBUFFER                   0x8D41
#define GL_RGBA4                          0x8056
#define GL_RGB5_A1                        0x8057
#define GL_RGB565                         0x8D62
#define GL_DEPTH_COMPONENT16              0x81A5
#define GL_STENCIL_INDEX8                 0x8D48
#define GL_RENDERBUFFER_WIDTH             0x8D42
#define GL_RENDERBUFFER_HEIGHT            0x8D43
#define GL_RENDERBUFFER_INTERNAL_FORMAT   0x8D44
#define GL_RENDERBUFFER_RED_SIZE          0x8D50
#define GL_RENDERBUFFER_GREEN_SIZE        0x8D51
#define GL_RENDERBUFFER_BLUE_SIZE         0x8D52
#define GL_RENDERBUFFER_ALPHA_SIZE        0x8D53
#define GL_RENDERBUFFER_DEPTH_SIZE        0x8D54
#define GL_RENDERBUFFER_STENCIL_SIZE      0x8D55
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE 0x8CD0
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME 0x8CD1
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL 0x8CD2
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE 0x8CD3
#define GL_COLOR_ATTACHMENT0              0x8CE0
#define GL_DEPTH_ATTACHMENT               0x8D00
#define GL_STENCIL_ATTACHMENT             0x8D20
#define GL_NONE                           0
#define GL_FRAMEBUFFER_COMPLETE           0x8CD5
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT 0x8CD6
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 0x8CD7
#define GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS 0x8CD9
#define GL_FRAMEBUFFER_UNSUPPORTED        0x8CDD
#define GL_FRAMEBUFFER_BINDING            0x8CA6
#define GL_RENDERBUFFER_BINDING           0x8CA7
#define GL_MAX_RENDERBUFFER_SIZE          0x84E8
#define GL_INVALID_FRAMEBUFFER_OPERATION  0x0506
تعريفنوع فراغ (GL_APIENTRYP PFNGLACTIVETEXTUREPROC) (GLenum texture);
تعريفنوع فراغ (GL_APIENTRYP PFNGLATTACHSHADERPROC) (GLuint program, GLuint shader);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDATTRIBLOCATIONPROC) (GLuint program, GLuint index, ثابت GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDFRAMEBUFFERPROC) (GLenum target, GLuint framebuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDRENDERBUFFERPROC) (GLenum target, GLuint renderbuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDTEXTUREPROC) (GLenum target, GLuint texture);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONPROC) (GLenum mode);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEPROC) (GLenum modeRGB, GLenum modeAlpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDFUNCPROC) (GLenum sfactor, GLenum dfactor);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEPROC) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBUFFERDATAPROC) (GLenum target, GLsizeiptr size, ثابت فراغ *data, GLenum usage);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBUFFERSUBDATAPROC) (GLenum target, GLintptr offset, GLsizeiptr size, ثابت فراغ *data);
تعريفنوع GLenum (GL_APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSPROC) (GLenum target);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARPROC) (GLbitfield mask);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARDEPTHFPROC) (GLfloat d);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARSTENCILPROC) (GLint s);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOLORMASKPROC) (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOMPILESHADERPROC) (GLuint shader);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOMPRESSEDTEXIMAGE2DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, ثابت فراغ *data);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, ثابت فراغ *data);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYTEXIMAGE2DPROC) (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
تعريفنوع GLuint (GL_APIENTRYP PFNGLCREATEPROGRAMPROC) (فراغ);
تعريفنوع GLuint (GL_APIENTRYP PFNGLCREATESHADERPROC) (GLenum type);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCULLFACEPROC) (GLenum mode);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEBUFFERSPROC) (GLsizei n, ثابت GLuint *buffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEFRAMEBUFFERSPROC) (GLsizei n, ثابت GLuint *framebuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEPROGRAMPROC) (GLuint program);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETERENDERBUFFERSPROC) (GLsizei n, ثابت GLuint *renderbuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETESHADERPROC) (GLuint shader);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETETEXTURESPROC) (GLsizei n, ثابت GLuint *textures);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHFUNCPROC) (GLenum func);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHMASKPROC) (GLboolean flag);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHRANGEFPROC) (GLfloat n, GLfloat f);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDETACHSHADERPROC) (GLuint program, GLuint shader);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISABLEPROC) (GLenum cap);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint index);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWARRAYSPROC) (GLenum mode, GLint first, GLsizei عدد);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSPROC) (GLenum mode, GLsizei عدد, GLenum type, ثابت فراغ *indices);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENABLEPROC) (GLenum cap);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint index);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFINISHPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFLUSHPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFERPROC) (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRONTFACEPROC) (GLenum mode);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENBUFFERSPROC) (GLsizei n, GLuint *buffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENERATEMIPMAPPROC) (GLenum target);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENFRAMEBUFFERSPROC) (GLsizei n, GLuint *framebuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENRENDERBUFFERSPROC) (GLsizei n, GLuint *renderbuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENTEXTURESPROC) (GLsizei n, GLuint *textures);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETACTIVEATTRIBPROC) (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETACTIVEUNIFORMPROC) (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETATTACHEDSHADERSPROC) (GLuint program, GLsizei max_عدد, GLsizei *عدد, GLuint *shaders);
تعريفنوع GLint (GL_APIENTRYP PFNGLGETATTRIBLOCATIONPROC) (GLuint program, ثابت GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETBOOLEANVPROC) (GLenum pname, GLboolean *data);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETBUFFERPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
تعريفنوع GLenum (GL_APIENTRYP PFNGLGETERRORPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFLOATVPROC) (GLenum pname, GLfloat *data);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) (GLenum target, GLenum attachment, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTEGERVPROC) (GLenum pname, GLint *data);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMIVPROC) (GLuint program, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMINFOLOGPROC) (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSHADERPRECISIONFORMATPROC) (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSHADERSOURCEPROC) (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source);
تعريفنوع ثابت GLubyte *(GL_APIENTRYP PFNGLGETSTRINGPROC) (GLenum name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXPARAMETERFVPROC) (GLenum target, GLenum pname, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETUNIFORMFVPROC) (GLuint program, GLint location, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETUNIFORMIVPROC) (GLuint program, GLint location, GLint *params);
تعريفنوع GLint (GL_APIENTRYP PFNGLGETUNIFORMLOCATIONPROC) (GLuint program, ثابت GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETVERTEXATTRIBFVPROC) (GLuint index, GLenum pname, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETVERTEXATTRIBIVPROC) (GLuint index, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETVERTEXATTRIBPOINTERVPROC) (GLuint index, GLenum pname, فراغ **pointer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLHINTPROC) (GLenum target, GLenum mode);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISBUFFERPROC) (GLuint buffer);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISENABLEDPROC) (GLenum cap);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISFRAMEBUFFERPROC) (GLuint framebuffer);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISPROGRAMPROC) (GLuint program);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISRENDERBUFFERPROC) (GLuint renderbuffer);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISSHADERPROC) (GLuint shader);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISTEXTUREPROC) (GLuint texture);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLINEWIDTHPROC) (GLfloat width);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLINKPROGRAMPROC) (GLuint program);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPIXELSTOREIPROC) (GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOLYGONOFFSETPROC) (GLfloat factor, GLfloat units);
تعريفنوع فراغ (GL_APIENTRYP PFNGLREADPIXELSPROC) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, فراغ *pixels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRELEASESHADERCOMPILERPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEPROC) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLECOVERAGEPROC) (GLfloat قيمة, GLboolean invert);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSORPROC) (GLint x, GLint y, GLsizei width, GLsizei height);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADERBINARYPROC) (GLsizei عدد, ثابت GLuint *shaders, GLenum ثنائي_Format, ثابت فراغ *ثنائي, GLsizei length);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei عدد, ثابت GLchar *ثابت*string, ثابت GLint *length);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILFUNCPROC) (GLenum func, GLint ref, GLuint mask);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILFUNCSEPARATEPROC) (GLenum face, GLenum func, GLint ref, GLuint mask);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILMASKPROC) (GLuint mask);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILMASKSEPARATEPROC) (GLenum face, GLuint mask);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILOPPROC) (GLenum fail, GLenum zfail, GLenum zpass);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILOPSEPARATEPROC) (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXIMAGE2DPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, ثابت فراغ *pixels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERFPROC) (GLenum target, GLenum pname, GLfloat param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERFVPROC) (GLenum target, GLenum pname, ثابت GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERIPROC) (GLenum target, GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERIVPROC) (GLenum target, GLenum pname, ثابت GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, ثابت فراغ *pixels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1FPROC) (GLint location, GLfloat v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1FVPROC) (GLint location, GLsizei عدد, ثابت GLfloat *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1IPROC) (GLint location, GLint v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1IVPROC) (GLint location, GLsizei عدد, ثابت GLint *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2FPROC) (GLint location, GLfloat v0, GLfloat v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2FVPROC) (GLint location, GLsizei عدد, ثابت GLfloat *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2IPROC) (GLint location, GLint v0, GLint v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2IVPROC) (GLint location, GLsizei عدد, ثابت GLint *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3FVPROC) (GLint location, GLsizei عدد, ثابت GLfloat *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3IPROC) (GLint location, GLint v0, GLint v1, GLint v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3IVPROC) (GLint location, GLsizei عدد, ثابت GLint *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4FVPROC) (GLint location, GLsizei عدد, ثابت GLfloat *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4IPROC) (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4IVPROC) (GLint location, GLsizei عدد, ثابت GLint *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX2FVPROC) (GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX3FVPROC) (GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUSEPROGRAMPROC) (GLuint program);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVALIDATEPROGRAMPROC) (GLuint program);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB1FPROC) (GLuint index, GLfloat x);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB1FVPROC) (GLuint index, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB2FPROC) (GLuint index, GLfloat x, GLfloat y);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB2FVPROC) (GLuint index, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB3FPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB3FVPROC) (GLuint index, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB4FPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB4FVPROC) (GLuint index, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, ثابت فراغ *pointer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTPROC) (GLint x, GLint y, GLsizei width, GLsizei height);
#إذا GL_GLES_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glActiveTexture (GLenum texture);
GL_APICALL فراغ GL_APIENTRY glAttachShader (GLuint program, GLuint shader);
GL_APICALL فراغ GL_APIENTRY glBindAttribLocation (GLuint program, GLuint index, ثابت GLchar *name);
GL_APICALL فراغ GL_APIENTRY glBindBuffer (GLenum target, GLuint buffer);
GL_APICALL فراغ GL_APIENTRY glBindFramebuffer (GLenum target, GLuint framebuffer);
GL_APICALL فراغ GL_APIENTRY glBindRenderbuffer (GLenum target, GLuint renderbuffer);
GL_APICALL فراغ GL_APIENTRY glBindTexture (GLenum target, GLuint texture);
GL_APICALL فراغ GL_APIENTRY glBlendColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_APICALL فراغ GL_APIENTRY glBlendEquation (GLenum mode);
GL_APICALL فراغ GL_APIENTRY glBlendEquationSeparate (GLenum modeRGB, GLenum modeAlpha);
GL_APICALL فراغ GL_APIENTRY glBlendFunc (GLenum sfactor, GLenum dfactor);
GL_APICALL فراغ GL_APIENTRY glBlendFuncSeparate (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
GL_APICALL فراغ GL_APIENTRY glBufferData (GLenum target, GLsizeiptr size, ثابت فراغ *data, GLenum usage);
GL_APICALL فراغ GL_APIENTRY glBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, ثابت فراغ *data);
GL_APICALL GLenum GL_APIENTRY glCheckFramebufferStatus (GLenum target);
GL_APICALL فراغ GL_APIENTRY glClear (GLbitfield mask);
GL_APICALL فراغ GL_APIENTRY glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_APICALL فراغ GL_APIENTRY glClearDepthf (GLfloat d);
GL_APICALL فراغ GL_APIENTRY glClearStencil (GLint s);
GL_APICALL فراغ GL_APIENTRY glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
GL_APICALL فراغ GL_APIENTRY glCompileShader (GLuint shader);
GL_APICALL فراغ GL_APIENTRY glCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, ثابت فراغ *data);
GL_APICALL فراغ GL_APIENTRY glCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, ثابت فراغ *data);
GL_APICALL فراغ GL_APIENTRY glCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
GL_APICALL فراغ GL_APIENTRY glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
GL_APICALL GLuint GL_APIENTRY glCreateProgram (فراغ);
GL_APICALL GLuint GL_APIENTRY glCreateShader (GLenum type);
GL_APICALL فراغ GL_APIENTRY glCullFace (GLenum mode);
GL_APICALL فراغ GL_APIENTRY glDeleteBuffers (GLsizei n, ثابت GLuint *buffers);
GL_APICALL فراغ GL_APIENTRY glDeleteFramebuffers (GLsizei n, ثابت GLuint *framebuffers);
GL_APICALL فراغ GL_APIENTRY glDeleteProgram (GLuint program);
GL_APICALL فراغ GL_APIENTRY glDeleteRenderbuffers (GLsizei n, ثابت GLuint *renderbuffers);
GL_APICALL فراغ GL_APIENTRY glDeleteShader (GLuint shader);
GL_APICALL فراغ GL_APIENTRY glDeleteTextures (GLsizei n, ثابت GLuint *textures);
GL_APICALL فراغ GL_APIENTRY glDepthFunc (GLenum func);
GL_APICALL فراغ GL_APIENTRY glDepthMask (GLboolean flag);
GL_APICALL فراغ GL_APIENTRY glDepthRangef (GLfloat n, GLfloat f);
GL_APICALL فراغ GL_APIENTRY glDetachShader (GLuint program, GLuint shader);
GL_APICALL فراغ GL_APIENTRY glDisable (GLenum cap);
GL_APICALL فراغ GL_APIENTRY glDisableVertexAttribArray (GLuint index);
GL_APICALL فراغ GL_APIENTRY glDrawArrays (GLenum mode, GLint first, GLsizei عدد);
GL_APICALL فراغ GL_APIENTRY glDrawElements (GLenum mode, GLsizei عدد, GLenum type, ثابت فراغ *indices);
GL_APICALL فراغ GL_APIENTRY glEnable (GLenum cap);
GL_APICALL فراغ GL_APIENTRY glEnableVertexAttribArray (GLuint index);
GL_APICALL فراغ GL_APIENTRY glFinish (فراغ);
GL_APICALL فراغ GL_APIENTRY glFlush (فراغ);
GL_APICALL فراغ GL_APIENTRY glFramebufferRenderbuffer (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
GL_APICALL فراغ GL_APIENTRY glFramebufferTexture2D (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GL_APICALL فراغ GL_APIENTRY glFrontFace (GLenum mode);
GL_APICALL فراغ GL_APIENTRY glGenBuffers (GLsizei n, GLuint *buffers);
GL_APICALL فراغ GL_APIENTRY glGenerateMipmap (GLenum target);
GL_APICALL فراغ GL_APIENTRY glGenFramebuffers (GLsizei n, GLuint *framebuffers);
GL_APICALL فراغ GL_APIENTRY glGenRenderbuffers (GLsizei n, GLuint *renderbuffers);
GL_APICALL فراغ GL_APIENTRY glGenTextures (GLsizei n, GLuint *textures);
GL_APICALL فراغ GL_APIENTRY glGetActiveAttrib (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
GL_APICALL فراغ GL_APIENTRY glGetActiveUniform (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
GL_APICALL فراغ GL_APIENTRY glGetAttachedShaders (GLuint program, GLsizei max_عدد, GLsizei *عدد, GLuint *shaders);
GL_APICALL GLint GL_APIENTRY glGetAttribLocation (GLuint program, ثابت GLchar *name);
GL_APICALL فراغ GL_APIENTRY glGetBooleanv (GLenum pname, GLboolean *data);
GL_APICALL فراغ GL_APIENTRY glGetBufferParameteriv (GLenum target, GLenum pname, GLint *params);
GL_APICALL GLenum GL_APIENTRY glGetError (فراغ);
GL_APICALL فراغ GL_APIENTRY glGetFloatv (GLenum pname, GLfloat *data);
GL_APICALL فراغ GL_APIENTRY glGetFramebufferAttachmentParameteriv (GLenum target, GLenum attachment, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetIntegerv (GLenum pname, GLint *data);
GL_APICALL فراغ GL_APIENTRY glGetProgramiv (GLuint program, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetProgramInfoLog (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
GL_APICALL فراغ GL_APIENTRY glGetRenderbufferParameteriv (GLenum target, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetShaderiv (GLuint shader, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetShaderInfoLog (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
GL_APICALL فراغ GL_APIENTRY glGetShaderPrecisionFormat (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
GL_APICALL فراغ GL_APIENTRY glGetShaderSource (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source);
GL_APICALL ثابت GLubyte *GL_APIENTRY glGetString (GLenum name);
GL_APICALL فراغ GL_APIENTRY glGetTexParameterfv (GLenum target, GLenum pname, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY glGetTexParameteriv (GLenum target, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetUniformfv (GLuint program, GLint location, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY glGetUniformiv (GLuint program, GLint location, GLint *params);
GL_APICALL GLint GL_APIENTRY glGetUniformLocation (GLuint program, ثابت GLchar *name);
GL_APICALL فراغ GL_APIENTRY glGetVertexAttribfv (GLuint index, GLenum pname, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY glGetVertexAttribiv (GLuint index, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetVertexAttribPointerv (GLuint index, GLenum pname, فراغ **pointer);
GL_APICALL فراغ GL_APIENTRY glHint (GLenum target, GLenum mode);
GL_APICALL GLboolean GL_APIENTRY glIsBuffer (GLuint buffer);
GL_APICALL GLboolean GL_APIENTRY glIsEnabled (GLenum cap);
GL_APICALL GLboolean GL_APIENTRY glIsFramebuffer (GLuint framebuffer);
GL_APICALL GLboolean GL_APIENTRY glIsProgram (GLuint program);
GL_APICALL GLboolean GL_APIENTRY glIsRenderbuffer (GLuint renderbuffer);
GL_APICALL GLboolean GL_APIENTRY glIsShader (GLuint shader);
GL_APICALL GLboolean GL_APIENTRY glIsTexture (GLuint texture);
GL_APICALL فراغ GL_APIENTRY gl_سطر_Width (GLfloat width);
GL_APICALL فراغ GL_APIENTRY glLinkProgram (GLuint program);
GL_APICALL فراغ GL_APIENTRY glPixelStorei (GLenum pname, GLint param);
GL_APICALL فراغ GL_APIENTRY glPolygonOffset (GLfloat factor, GLfloat units);
GL_APICALL فراغ GL_APIENTRY glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, فراغ *pixels);
GL_APICALL فراغ GL_APIENTRY glReleaseShaderCompiler (فراغ);
GL_APICALL فراغ GL_APIENTRY glRenderbufferStorage (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
GL_APICALL فراغ GL_APIENTRY glSampleCoverage (GLfloat قيمة, GLboolean invert);
GL_APICALL فراغ GL_APIENTRY glScissor (GLint x, GLint y, GLsizei width, GLsizei height);
GL_APICALL فراغ GL_APIENTRY gl_Shader_ثنائي (GLsizei عدد, ثابت GLuint *shaders, GLenum ثنائي_Format, ثابت فراغ *ثنائي, GLsizei length);
GL_APICALL فراغ GL_APIENTRY glShaderSource (GLuint shader, GLsizei عدد, ثابت GLchar *ثابت*string, ثابت GLint *length);
GL_APICALL فراغ GL_APIENTRY glStencilFunc (GLenum func, GLint ref, GLuint mask);
GL_APICALL فراغ GL_APIENTRY glStencilFuncSeparate (GLenum face, GLenum func, GLint ref, GLuint mask);
GL_APICALL فراغ GL_APIENTRY glStencilMask (GLuint mask);
GL_APICALL فراغ GL_APIENTRY glStencilMaskSeparate (GLenum face, GLuint mask);
GL_APICALL فراغ GL_APIENTRY glStencilOp (GLenum fail, GLenum zfail, GLenum zpass);
GL_APICALL فراغ GL_APIENTRY glStencilOpSeparate (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
GL_APICALL فراغ GL_APIENTRY glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, ثابت فراغ *pixels);
GL_APICALL فراغ GL_APIENTRY glTexParameterf (GLenum target, GLenum pname, GLfloat param);
GL_APICALL فراغ GL_APIENTRY glTexParameterfv (GLenum target, GLenum pname, ثابت GLfloat *params);
GL_APICALL فراغ GL_APIENTRY glTexParameteri (GLenum target, GLenum pname, GLint param);
GL_APICALL فراغ GL_APIENTRY glTexParameteriv (GLenum target, GLenum pname, ثابت GLint *params);
GL_APICALL فراغ GL_APIENTRY glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, ثابت فراغ *pixels);
GL_APICALL فراغ GL_APIENTRY glUniform1f (GLint location, GLfloat v0);
GL_APICALL فراغ GL_APIENTRY glUniform1fv (GLint location, GLsizei عدد, ثابت GLfloat *قيمة);
GL_APICALL فراغ GL_APIENTRY glUniform1i (GLint location, GLint v0);
GL_APICALL فراغ GL_APIENTRY glUniform1iv (GLint location, GLsizei عدد, ثابت GLint *قيمة);
GL_APICALL فراغ GL_APIENTRY glUniform2f (GLint location, GLfloat v0, GLfloat v1);
GL_APICALL فراغ GL_APIENTRY glUniform2fv (GLint location, GLsizei عدد, ثابت GLfloat *قيمة);
GL_APICALL فراغ GL_APIENTRY glUniform2i (GLint location, GLint v0, GLint v1);
GL_APICALL فراغ GL_APIENTRY glUniform2iv (GLint location, GLsizei عدد, ثابت GLint *قيمة);
GL_APICALL فراغ GL_APIENTRY glUniform3f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
GL_APICALL فراغ GL_APIENTRY glUniform3fv (GLint location, GLsizei عدد, ثابت GLfloat *قيمة);
GL_APICALL فراغ GL_APIENTRY glUniform3i (GLint location, GLint v0, GLint v1, GLint v2);
GL_APICALL فراغ GL_APIENTRY glUniform3iv (GLint location, GLsizei عدد, ثابت GLint *قيمة);
GL_APICALL فراغ GL_APIENTRY glUniform4f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
GL_APICALL فراغ GL_APIENTRY glUniform4fv (GLint location, GLsizei عدد, ثابت GLfloat *قيمة);
GL_APICALL فراغ GL_APIENTRY glUniform4i (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
GL_APICALL فراغ GL_APIENTRY glUniform4iv (GLint location, GLsizei عدد, ثابت GLint *قيمة);
GL_APICALL فراغ GL_APIENTRY glUniformMatrix2fv (GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
GL_APICALL فراغ GL_APIENTRY glUniformMatrix3fv (GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
GL_APICALL فراغ GL_APIENTRY glUniformMatrix4fv (GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
GL_APICALL فراغ GL_APIENTRY glUseProgram (GLuint program);
GL_APICALL فراغ GL_APIENTRY glValidateProgram (GLuint program);
GL_APICALL فراغ GL_APIENTRY glVertexAttrib1f (GLuint index, GLfloat x);
GL_APICALL فراغ GL_APIENTRY glVertexAttrib1fv (GLuint index, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY glVertexAttrib2f (GLuint index, GLfloat x, GLfloat y);
GL_APICALL فراغ GL_APIENTRY glVertexAttrib2fv (GLuint index, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY glVertexAttrib3f (GLuint index, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL فراغ GL_APIENTRY glVertexAttrib3fv (GLuint index, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY glVertexAttrib4f (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
GL_APICALL فراغ GL_APIENTRY glVertexAttrib4fv (GLuint index, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY glVertexAttribPointer (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, ثابت فراغ *pointer);
GL_APICALL فراغ GL_APIENTRY glViewport (GLint x, GLint y, GLsizei width, GLsizei height);
#endif
#endif /* GL_ES_VERSION_2_0 */

#ifndef GL_ES_VERSION_3_0
#define GL_ES_VERSION_3_0 1
تعريفنوع khronos_uint16_t GLhalf;
#define GL_READ_BUFFER                    0x0C02
#define GL_UNPACK_ROW_LENGTH              0x0CF2
#define GL_UNPACK_SKIP_ROWS               0x0CF3
#define GL_UNPACK_SKIP_PIXELS             0x0CF4
#define GL_PACK_ROW_LENGTH                0x0D02
#define GL_PACK_SKIP_ROWS                 0x0D03
#define GL_PACK_SKIP_PIXELS               0x0D04
#define GL_COLOR                          0x1800
#define GL_DEPTH                          0x1801
#define GL_STENCIL                        0x1802
#define GL_RED                            0x1903
#define GL_RGB8                           0x8051
#define GL_RGBA8                          0x8058
#define GL_RGB10_A2                       0x8059
#define GL_TEXTURE_BINDING_3D             0x806A
#define GL_UNPACK_SKIP_IMAGES             0x806D
#define GL_UNPACK_IMAGE_HEIGHT            0x806E
#define GL_TEXTURE_3D                     0x806F
#define GL_TEXTURE_WRAP_R                 0x8072
#define GL_MAX_3D_TEXTURE_SIZE            0x8073
#define GL_UNSIGNED_INT_2_10_10_10_REV    0x8368
#define GL_MAX_ELEMENTS_VERTICES          0x80E8
#define GL_MAX_ELEMENTS_INDICES           0x80E9
#define GL_TEXTURE_MIN_LOD                0x813A
#define GL_TEXTURE_MAX_LOD                0x813B
#define GL_TEXTURE_BASE_LEVEL             0x813C
#define GL_TEXTURE_MAX_LEVEL              0x813D
#define GL_MIN                            0x8007
#define GL_MAX                            0x8008
#define GL_DEPTH_COMPONENT24              0x81A6
#define GL_MAX_TEXTURE_LOD_BIAS           0x84FD
#define GL_TEXTURE_COMPARE_MODE           0x884C
#define GL_TEXTURE_COMPARE_FUNC           0x884D
#define GL_CURRENT_QUERY                  0x8865
#define GL_QUERY_RESULT                   0x8866
#define GL_QUERY_RESULT_AVAILABLE         0x8867
#define GL_BUFFER_MAPPED                  0x88BC
#define GL_BUFFER_MAP_POINTER             0x88BD
#define GL_STREAM_READ                    0x88E1
#define GL_STREAM_COPY                    0x88E2
#define GL_STATIC_READ                    0x88E5
#define GL_STATIC_COPY                    0x88E6
#define GL_DYNAMIC_READ                   0x88E9
#define GL_DYNAMIC_COPY                   0x88EA
#define GL_MAX_DRAW_BUFFERS               0x8824
#define GL_DRAW_BUFFER0                   0x8825
#define GL_DRAW_BUFFER1                   0x8826
#define GL_DRAW_BUFFER2                   0x8827
#define GL_DRAW_BUFFER3                   0x8828
#define GL_DRAW_BUFFER4                   0x8829
#define GL_DRAW_BUFFER5                   0x882A
#define GL_DRAW_BUFFER6                   0x882B
#define GL_DRAW_BUFFER7                   0x882C
#define GL_DRAW_BUFFER8                   0x882D
#define GL_DRAW_BUFFER9                   0x882E
#define GL_DRAW_BUFFER10                  0x882F
#define GL_DRAW_BUFFER11                  0x8830
#define GL_DRAW_BUFFER12                  0x8831
#define GL_DRAW_BUFFER13                  0x8832
#define GL_DRAW_BUFFER14                  0x8833
#define GL_DRAW_BUFFER15                  0x8834
#define GL_MAX_FRAGMENT_UNIFORM_COMPONENTS 0x8B49
#define GL_MAX_VERTEX_UNIFORM_COMPONENTS  0x8B4A
#define GL_SAMPLER_3D                     0x8B5F
#define GL_SAMPLER_2D_SHADOW              0x8B62
#define GL_FRAGMENT_SHADER_DERIVATIVE_HINT 0x8B8B
#define GL_PIXEL_PACK_BUFFER              0x88EB
#define GL_PIXEL_UNPACK_BUFFER            0x88EC
#define GL_PIXEL_PACK_BUFFER_BINDING      0x88ED
#define GL_PIXEL_UNPACK_BUFFER_BINDING    0x88EF
#define GL_FLOAT_MAT2x3                   0x8B65
#define GL_FLOAT_MAT2x4                   0x8B66
#define GL_FLOAT_MAT3x2                   0x8B67
#define GL_FLOAT_MAT3x4                   0x8B68
#define GL_FLOAT_MAT4x2                   0x8B69
#define GL_FLOAT_MAT4x3                   0x8B6A
#define GL_SRGB                           0x8C40
#define GL_SRGB8                          0x8C41
#define GL_SRGB8_ALPHA8                   0x8C43
#define GL_COMPARE_REF_TO_TEXTURE         0x884E
#define GL_MAJOR_VERSION                  0x821B
#define GL_MINOR_VERSION                  0x821C
#define GL_رقم_EXTENSIONS                 0x821D
#define GL_RGBA32F                        0x8814
#define GL_RGB32F                         0x8815
#define GL_RGBA16F                        0x881A
#define GL_RGB16F                         0x881B
#define GL_VERTEX_ATTRIB_ARRAY_INTEGER    0x88FD
#define GL_MAX_ARRAY_TEXTURE_LAYERS       0x88FF
#define GL_MIN_PROGRAM_TEXEL_OFFSET       0x8904
#define GL_MAX_PROGRAM_TEXEL_OFFSET       0x8905
#define GL_MAX_VARYING_COMPONENTS         0x8B4B
#define GL_TEXTURE_2D_ARRAY               0x8C1A
#define GL_TEXTURE_BINDING_2D_ARRAY       0x8C1D
#define GL_R11F_G11F_B10F                 0x8C3A
#define GL_UNSIGNED_INT_10F_11F_11F_REV   0x8C3B
#define GL_RGB9_E5                        0x8C3D
#define GL_UNSIGNED_INT_5_9_9_9_REV       0x8C3E
#define GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH 0x8C76
#define GL_TRANSFORM_FEEDBACK_BUFFER_MODE 0x8C7F
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS 0x8C80
#define GL_TRANSFORM_FEEDBACK_VARYINGS    0x8C83
#define GL_TRANSFORM_FEEDBACK_BUFFER_START 0x8C84
#define GL_TRANSFORM_FEEDBACK_BUFFER_SIZE 0x8C85
#define GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN 0x8C88
#define GL_RASTERIZER_DISCARD             0x8C89
#define GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS 0x8C8A
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS 0x8C8B
#define GL_INTERLEAVED_ATTRIBS            0x8C8C
#define GL_SEPARATE_ATTRIBS               0x8C8D
#define GL_TRANSFORM_FEEDBACK_BUFFER      0x8C8E
#define GL_TRANSFORM_FEEDBACK_BUFFER_BINDING 0x8C8F
#define GL_RGBA32UI                       0x8D70
#define GL_RGB32UI                        0x8D71
#define GL_RGBA16UI                       0x8D76
#define GL_RGB16UI                        0x8D77
#define GL_RGBA8UI                        0x8D7C
#define GL_RGB8UI                         0x8D7D
#define GL_RGBA32I                        0x8D82
#define GL_RGB32I                         0x8D83
#define GL_RGBA16I                        0x8D88
#define GL_RGB16I                         0x8D89
#define GL_RGBA8I                         0x8D8E
#define GL_RGB8I                          0x8D8F
#define GL_RED_INTEGER                    0x8D94
#define GL_RGB_INTEGER                    0x8D98
#define GL_RGBA_INTEGER                   0x8D99
#define GL_SAMPLER_2D_ARRAY               0x8DC1
#define GL_SAMPLER_2D_ARRAY_SHADOW        0x8DC4
#define GL_SAMPLER_CUBE_SHADOW            0x8DC5
#define GL_UNSIGNED_INT_VEC2              0x8DC6
#define GL_UNSIGNED_INT_VEC3              0x8DC7
#define GL_UNSIGNED_INT_VEC4              0x8DC8
#define GL_INT_SAMPLER_2D                 0x8DCA
#define GL_INT_SAMPLER_3D                 0x8DCB
#define GL_INT_SAMPLER_CUBE               0x8DCC
#define GL_INT_SAMPLER_2D_ARRAY           0x8DCF
#define GL_UNSIGNED_INT_SAMPLER_2D        0x8DD2
#define GL_UNSIGNED_INT_SAMPLER_3D        0x8DD3
#define GL_UNSIGNED_INT_SAMPLER_CUBE      0x8DD4
#define GL_UNSIGNED_INT_SAMPLER_2D_ARRAY  0x8DD7
#define GL_BUFFER_ACCESS_FLAGS            0x911F
#define GL_BUFFER_MAP_LENGTH              0x9120
#define GL_BUFFER_MAP_OFFSET              0x9121
#define GL_DEPTH_COMPONENT32F             0x8CAC
#define GL_DEPTH32F_STENCIL8              0x8CAD
#define GL_FLOAT_32_UNSIGNED_INT_24_8_REV 0x8DAD
#define GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING 0x8210
#define GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE 0x8211
#define GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE 0x8212
#define GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE 0x8213
#define GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE 0x8214
#define GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE 0x8215
#define GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE 0x8216
#define GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE 0x8217
#define GL_FRAMEBUFFER_DEFAULT            0x8218
#define GL_FRAMEBUFFER_UNDEFINED          0x8219
#define GL_DEPTH_STENCIL_ATTACHMENT       0x821A
#define GL_DEPTH_STENCIL                  0x84F9
#define GL_UNSIGNED_INT_24_8              0x84FA
#define GL_DEPTH24_STENCIL8               0x88F0
#define GL_UNSIGNED_NORMALIZED            0x8C17
#define GL_DRAW_FRAMEBUFFER_BINDING       0x8CA6
#define GL_READ_FRAMEBUFFER               0x8CA8
#define GL_DRAW_FRAMEBUFFER               0x8CA9
#define GL_READ_FRAMEBUFFER_BINDING       0x8CAA
#define GL_RENDERBUFFER_SAMPLES           0x8CAB
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER 0x8CD4
#define GL_MAX_COLOR_ATTACHMENTS          0x8CDF
#define GL_COLOR_ATTACHMENT1              0x8CE1
#define GL_COLOR_ATTACHMENT2              0x8CE2
#define GL_COLOR_ATTACHMENT3              0x8CE3
#define GL_COLOR_ATTACHMENT4              0x8CE4
#define GL_COLOR_ATTACHMENT5              0x8CE5
#define GL_COLOR_ATTACHMENT6              0x8CE6
#define GL_COLOR_ATTACHMENT7              0x8CE7
#define GL_COLOR_ATTACHMENT8              0x8CE8
#define GL_COLOR_ATTACHMENT9              0x8CE9
#define GL_COLOR_ATTACHMENT10             0x8CEA
#define GL_COLOR_ATTACHMENT11             0x8CEB
#define GL_COLOR_ATTACHMENT12             0x8CEC
#define GL_COLOR_ATTACHMENT13             0x8CED
#define GL_COLOR_ATTACHMENT14             0x8CEE
#define GL_COLOR_ATTACHMENT15             0x8CEF
#define GL_COLOR_ATTACHMENT16             0x8CF0
#define GL_COLOR_ATTACHMENT17             0x8CF1
#define GL_COLOR_ATTACHMENT18             0x8CF2
#define GL_COLOR_ATTACHMENT19             0x8CF3
#define GL_COLOR_ATTACHMENT20             0x8CF4
#define GL_COLOR_ATTACHMENT21             0x8CF5
#define GL_COLOR_ATTACHMENT22             0x8CF6
#define GL_COLOR_ATTACHMENT23             0x8CF7
#define GL_COLOR_ATTACHMENT24             0x8CF8
#define GL_COLOR_ATTACHMENT25             0x8CF9
#define GL_COLOR_ATTACHMENT26             0x8CFA
#define GL_COLOR_ATTACHMENT27             0x8CFB
#define GL_COLOR_ATTACHMENT28             0x8CFC
#define GL_COLOR_ATTACHMENT29             0x8CFD
#define GL_COLOR_ATTACHMENT30             0x8CFE
#define GL_COLOR_ATTACHMENT31             0x8CFF
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE 0x8D56
#define GL_MAX_SAMPLES                    0x8D57
#define GL_HALF_FLOAT                     0x140B
#define GL_MAP_READ_BIT                   0x0001
#define GL_MAP_WRITE_BIT                  0x0002
#define GL_MAP_INVALIDATE_RANGE_BIT       0x0004
#define GL_MAP_INVALIDATE_BUFFER_BIT      0x0008
#define GL_MAP_FLUSH_EXPLICIT_BIT         0x0010
#define GL_MAP_UNSYNCHRONIZED_BIT         0x0020
#define GL_RG                             0x8227
#define GL_RG_INTEGER                     0x8228
#define GL_R8                             0x8229
#define GL_RG8                            0x822B
#define GL_R16F                           0x822D
#define GL_R32F                           0x822E
#define GL_RG16F                          0x822F
#define GL_RG32F                          0x8230
#define GL_R8I                            0x8231
#define GL_R8UI                           0x8232
#define GL_R16I                           0x8233
#define GL_R16UI                          0x8234
#define GL_R32I                           0x8235
#define GL_R32UI                          0x8236
#define GL_RG8I                           0x8237
#define GL_RG8UI                          0x8238
#define GL_RG16I                          0x8239
#define GL_RG16UI                         0x823A
#define GL_RG32I                          0x823B
#define GL_RG32UI                         0x823C
#define GL_VERTEX_ARRAY_BINDING           0x85B5
#define GL_R8_SNORM                       0x8F94
#define GL_RG8_SNORM                      0x8F95
#define GL_RGB8_SNORM                     0x8F96
#define GL_RGBA8_SNORM                    0x8F97
#define GL_SIGNED_NORMALIZED              0x8F9C
#define GL_PRIMITIVE_RESTART_FIXED_INDEX  0x8D69
#define GL_COPY_READ_BUFFER               0x8F36
#define GL_COPY_WRITE_BUFFER              0x8F37
#define GL_COPY_READ_BUFFER_BINDING       0x8F36
#define GL_COPY_WRITE_BUFFER_BINDING      0x8F37
#define GL_UNIFORM_BUFFER                 0x8A11
#define GL_UNIFORM_BUFFER_BINDING         0x8A28
#define GL_UNIFORM_BUFFER_START           0x8A29
#define GL_UNIFORM_BUFFER_SIZE            0x8A2A
#define GL_MAX_VERTEX_UNIFORM_BLOCKS      0x8A2B
#define GL_MAX_FRAGMENT_UNIFORM_BLOCKS    0x8A2D
#define GL_MAX_COMBINED_UNIFORM_BLOCKS    0x8A2E
#define GL_MAX_UNIFORM_BUFFER_BINDINGS    0x8A2F
#define GL_MAX_UNIFORM_BLOCK_SIZE         0x8A30
#define GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS 0x8A31
#define GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS 0x8A33
#define GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT 0x8A34
#define GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH 0x8A35
#define GL_ACTIVE_UNIFORM_BLOCKS          0x8A36
#define GL_UNIFORM_TYPE                   0x8A37
#define GL_UNIFORM_SIZE                   0x8A38
#define GL_UNIFORM_NAME_LENGTH            0x8A39
#define GL_UNIFORM_BLOCK_INDEX            0x8A3A
#define GL_UNIFORM_OFFSET                 0x8A3B
#define GL_UNIFORM_ARRAY_STRIDE           0x8A3C
#define GL_UNIFORM_MATRIX_STRIDE          0x8A3D
#define GL_UNIFORM_IS_ROW_MAJOR           0x8A3E
#define GL_UNIFORM_BLOCK_BINDING          0x8A3F
#define GL_UNIFORM_BLOCK_DATA_SIZE        0x8A40
#define GL_UNIFORM_BLOCK_NAME_LENGTH      0x8A41
#define GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS  0x8A42
#define GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES 0x8A43
#define GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER 0x8A44
#define GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER 0x8A46
#define GL_INVALID_INDEX                  0xFFFFFFFFu
#define GL_MAX_VERTEX_OUTPUT_COMPONENTS   0x9122
#define GL_MAX_FRAGMENT_مدخل_COMPONENTS  0x9125
#define GL_MAX_SERVER_WAIT_TIMEOUT        0x9111
#define GL_OBJECT_TYPE                    0x9112
#define GL_SYNC_CONDITION                 0x9113
#define GL_SYNC_STATUS                    0x9114
#define GL_SYNC_FLAGS                     0x9115
#define GL_SYNC_FENCE                     0x9116
#define GL_SYNC_GPU_COMMANDS_COMPLETE     0x9117
#define GL_UNSIGNALED                     0x9118
#define GL_SIGNALED                       0x9119
#define GL_ALREADY_SIGNALED               0x911A
#define GL_TIMEOUT_EXPIRED                0x911B
#define GL_CONDITION_SATISFIED            0x911C
#define GL_WAIT_FAILED                    0x911D
#define GL_SYNC_FLUSH_COMMANDS_BIT        0x00000001
#define GL_TIMEOUT_IGNORED                0xFFFFFFFFFFFFFFFFull
#define GL_VERTEX_ATTRIB_ARRAY_قاسم    0x88FE
#define GL_ANY_SAMPLES_PASSED             0x8C2F
#define GL_ANY_SAMPLES_PASSED_CONSERVATIVE 0x8D6A
#define GL_SAMPLER_BINDING                0x8919
#define GL_RGB10_A2UI                     0x906F
#define GL_TEXTURE_SWIZZLE_R              0x8E42
#define GL_TEXTURE_SWIZZLE_G              0x8E43
#define GL_TEXTURE_SWIZZLE_B              0x8E44
#define GL_TEXTURE_SWIZZLE_A              0x8E45
#define GL_GREEN                          0x1904
#define GL_BLUE                           0x1905
#define GL_INT_2_10_10_10_REV             0x8D9F
#define GL_TRANSFORM_FEEDBACK             0x8E22
#define GL_TRANSFORM_FEEDBACK_PAUSED      0x8E23
#define GL_TRANSFORM_FEEDBACK_ACTIVE      0x8E24
#define GL_TRANSFORM_FEEDBACK_BINDING     0x8E25
#define GL_PROGRAM_ثنائي_RETRIEVABLE_HINT 0x8257
#define GL_PROGRAM_ثنائي_LENGTH          0x8741
#define GL_رقم_PROGRAM_ثنائي_FORMATS     0x87FE
#define GL_PROGRAM_ثنائي_FORMATS         0x87FF
#define GL_COMPRESSED_R11_EAC             0x9270
#define GL_COMPRESSED_SIGNED_R11_EAC      0x9271
#define GL_COMPRESSED_RG11_EAC            0x9272
#define GL_COMPRESSED_SIGNED_RG11_EAC     0x9273
#define GL_COMPRESSED_RGB8_ETC2           0x9274
#define GL_COMPRESSED_SRGB8_ETC2          0x9275
#define GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9276
#define GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9277
#define GL_COMPRESSED_RGBA8_ETC2_EAC      0x9278
#define GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC 0x9279
#define GL_TEXTURE_IMMUTABLE_FORMAT       0x912F
#define GL_MAX_ELEMENT_INDEX              0x8D6B
#define GL_رقم_SAMPLE_COUNTS              0x9380
#define GL_TEXTURE_IMMUTABLE_LEVELS       0x82DF
تعريفنوع فراغ (GL_APIENTRYP PFNGLREADBUFFERPROC) (GLenum src);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWRANGEELEMENTSPROC) (GLenum mode, GLuint start, GLuint end, GLsizei عدد, GLenum type, ثابت فراغ *indices);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXIMAGE3DPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, ثابت فراغ *pixels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, ثابت فراغ *pixels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOMPRESSEDTEXIMAGE3DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, ثابت فراغ *data);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, ثابت فراغ *data);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENQUERIESPROC) (GLsizei n, GLuint *ids);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEQUERIESPROC) (GLsizei n, ثابت GLuint *ids);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISQUERYPROC) (GLuint id);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBEGINQUERYPROC) (GLenum target, GLuint id);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENDQUERYPROC) (GLenum target);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETQUERYIVPROC) (GLenum target, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETQUERYOBJECTUIVPROC) (GLuint id, GLenum pname, GLuint *params);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLUNMAPBUFFERPROC) (GLenum target);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETBUFFERPOINTERVPROC) (GLenum target, GLenum pname, فراغ **params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWBUFFERSPROC) (GLsizei n, ثابت GLenum *bufs);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX2X3FVPROC) (GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX3X2FVPROC) (GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX2X4FVPROC) (GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX4X2FVPROC) (GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX3X4FVPROC) (GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX4X3FVPROC) (GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLITFRAMEBUFFERPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURELAYERPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
تعريفنوع فراغ *(GL_APIENTRYP PFNGLMAPBUFFERRANGEPROC) (GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEPROC) (GLenum target, GLintptr offset, GLsizeiptr length);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDVERTEXARRAYPROC) (GLuint array);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEVERTEXARRAYSPROC) (GLsizei n, ثابت GLuint *arrays);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint *arrays);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISVERTEXARRAYPROC) (GLuint array);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTEGERI_VPROC) (GLenum target, GLuint index, GLint *data);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBEGINTRANSFORMFEEDBACKPROC) (GLenum primitiveMode);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENDTRANSFORMFEEDBACKPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDBUFFERRANGEPROC) (GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDBUFFERBASEPROC) (GLenum target, GLuint index, GLuint buffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTRANSFORMFEEDBACKVARYINGSPROC) (GLuint program, GLsizei عدد, ثابت GLchar *ثابت*varyings, GLenum bufferMode);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTRANSFORMFEEDBACKVARYINGPROC) (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBIPOINTERPROC) (GLuint index, GLint size, GLenum type, GLsizei stride, ثابت فراغ *pointer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETVERTEXATTRIBIIVPROC) (GLuint index, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETVERTEXATTRIBIUIVPROC) (GLuint index, GLenum pname, GLuint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBI4IPROC) (GLuint index, GLint x, GLint y, GLint z, GLint w);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBI4UIPROC) (GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBI4IVPROC) (GLuint index, ثابت GLint *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBI4UIVPROC) (GLuint index, ثابت GLuint *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETUNIFORMUIVPROC) (GLuint program, GLint location, GLuint *params);
تعريفنوع GLint (GL_APIENTRYP PFNGLGETFRAGDATALOCATIONPROC) (GLuint program, ثابت GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1UIPROC) (GLint location, GLuint v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2UIPROC) (GLint location, GLuint v0, GLuint v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3UIPROC) (GLint location, GLuint v0, GLuint v1, GLuint v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4UIPROC) (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1UIVPROC) (GLint location, GLsizei عدد, ثابت GLuint *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2UIVPROC) (GLint location, GLsizei عدد, ثابت GLuint *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3UIVPROC) (GLint location, GLsizei عدد, ثابت GLuint *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4UIVPROC) (GLint location, GLsizei عدد, ثابت GLuint *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARBUFFERIVPROC) (GLenum buffer, GLint drawbuffer, ثابت GLint *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARBUFFERUIVPROC) (GLenum buffer, GLint drawbuffer, ثابت GLuint *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARBUFFERFVPROC) (GLenum buffer, GLint drawbuffer, ثابت GLfloat *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARBUFFERFIPROC) (GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
تعريفنوع ثابت GLubyte *(GL_APIENTRYP PFNGLGETSTRINGIPROC) (GLenum name, GLuint index);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYBUFFERSUBDATAPROC) (GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETUNIFORMINDICESPROC) (GLuint program, GLsizei uniform_عدد, ثابت GLchar *ثابت*uniformNames, GLuint *uniformIndices);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETACTIVEUNIFORMSIVPROC) (GLuint program, GLsizei uniform_عدد, ثابت GLuint *uniformIndices, GLenum pname, GLint *params);
تعريفنوع GLuint (GL_APIENTRYP PFNGLGETUNIFORMBLOCKINDEXPROC) (GLuint program, ثابت GLchar *uniformBlockName);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKIVPROC) (GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC) (GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMBLOCKBINDINGPROC) (GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDPROC) (GLenum mode, GLint first, GLsizei عدد, GLsizei instancecount);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDPROC) (GLenum mode, GLsizei عدد, GLenum type, ثابت فراغ *indices, GLsizei instancecount);
تعريفنوع GLsync (GL_APIENTRYP PFNGLFENCESYNCPROC) (GLenum condition, GLbitfield flags);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISSYNCPROC) (GLsync sync);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETESYNCPROC) (GLsync sync);
تعريفنوع GLenum (GL_APIENTRYP PFNGLCLIENTWAITSYNCPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
تعريفنوع فراغ (GL_APIENTRYP PFNGLWAITSYNCPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTEGER64VPROC) (GLenum pname, GLint64 *data);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSYNCIVPROC) (GLsync sync, GLenum pname, GLsizei عدد, GLsizei *length, GLint *قيم);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTEGER64I_VPROC) (GLenum target, GLuint index, GLint64 *data);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETBUFFERPARAMETERI64VPROC) (GLenum target, GLenum pname, GLint64 *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENSAMPLERSPROC) (GLsizei عدد, GLuint *samplers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETESAMPLERSPROC) (GLsizei عدد, ثابت GLuint *samplers);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISSAMPLERPROC) (GLuint sampler);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDSAMPLERPROC) (GLuint unit, GLuint sampler);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIPROC) (GLuint sampler, GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, ثابت GLint *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERFPROC) (GLuint sampler, GLenum pname, GLfloat param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, ثابت GLfloat *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBDIVISORPROC) (GLuint index, GLuint قاسم);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDTRANSFORMFEEDBACKPROC) (GLenum target, GLuint id);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETETRANSFORMFEEDBACKSPROC) (GLsizei n, ثابت GLuint *ids);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENTRANSFORMFEEDBACKSPROC) (GLsizei n, GLuint *ids);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISTRANSFORMFEEDBACKPROC) (GLuint id);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPAUSETRANSFORMFEEDBACKPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRESUMETRANSFORMFEEDBACKPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMBINARYPROC) (GLuint program, GLsizei bufSize, GLsizei *length, GLenum *ثنائي_Format, فراغ *ثنائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMBINARYPROC) (GLuint program, GLenum ثنائي_Format, ثابت فراغ *ثنائي, GLsizei length);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMPARAMETERIPROC) (GLuint program, GLenum pname, GLint قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLINVALIDATEFRAMEBUFFERPROC) (GLenum target, GLsizei رقم_Attachments, ثابت GLenum *attachments);
تعريفنوع فراغ (GL_APIENTRYP PFNGLINVALIDATESUBFRAMEBUFFERPROC) (GLenum target, GLsizei رقم_Attachments, ثابت GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE2DPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE3DPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTERNALFORMATIVPROC) (GLenum target, GLenum internalformat, GLenum pname, GLsizei عدد, GLint *params);
#إذا GL_GLES_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glReadBuffer (GLenum src);
GL_APICALL فراغ GL_APIENTRY glDrawRangeElements (GLenum mode, GLuint start, GLuint end, GLsizei عدد, GLenum type, ثابت فراغ *indices);
GL_APICALL فراغ GL_APIENTRY glTexImage3D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, ثابت فراغ *pixels);
GL_APICALL فراغ GL_APIENTRY glTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, ثابت فراغ *pixels);
GL_APICALL فراغ GL_APIENTRY glCopyTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
GL_APICALL فراغ GL_APIENTRY glCompressedTexImage3D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, ثابت فراغ *data);
GL_APICALL فراغ GL_APIENTRY glCompressedTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, ثابت فراغ *data);
GL_APICALL فراغ GL_APIENTRY glGenQueries (GLsizei n, GLuint *ids);
GL_APICALL فراغ GL_APIENTRY glDeleteQueries (GLsizei n, ثابت GLuint *ids);
GL_APICALL GLboolean GL_APIENTRY glIsQuery (GLuint id);
GL_APICALL فراغ GL_APIENTRY glBeginQuery (GLenum target, GLuint id);
GL_APICALL فراغ GL_APIENTRY glEndQuery (GLenum target);
GL_APICALL فراغ GL_APIENTRY glGetQueryiv (GLenum target, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetQueryObjectuiv (GLuint id, GLenum pname, GLuint *params);
GL_APICALL GLboolean GL_APIENTRY glUnmapBuffer (GLenum target);
GL_APICALL فراغ GL_APIENTRY glGetBufferPointerv (GLenum target, GLenum pname, فراغ **params);
GL_APICALL فراغ GL_APIENTRY glDrawBuffers (GLsizei n, ثابت GLenum *bufs);
GL_APICALL فراغ GL_APIENTRY glUniformMatrix2x3fv (GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
GL_APICALL فراغ GL_APIENTRY glUniformMatrix3x2fv (GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
GL_APICALL فراغ GL_APIENTRY glUniformMatrix2x4fv (GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
GL_APICALL فراغ GL_APIENTRY glUniformMatrix4x2fv (GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
GL_APICALL فراغ GL_APIENTRY glUniformMatrix3x4fv (GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
GL_APICALL فراغ GL_APIENTRY glUniformMatrix4x3fv (GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
GL_APICALL فراغ GL_APIENTRY glBlitFramebuffer (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
GL_APICALL فراغ GL_APIENTRY glRenderbufferStorageMultisample (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
GL_APICALL فراغ GL_APIENTRY glFramebufferTextureLayer (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
GL_APICALL فراغ *GL_APIENTRY glMapBufferRange (GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
GL_APICALL فراغ GL_APIENTRY glFlushMappedBufferRange (GLenum target, GLintptr offset, GLsizeiptr length);
GL_APICALL فراغ GL_APIENTRY glBindVertexArray (GLuint array);
GL_APICALL فراغ GL_APIENTRY glDeleteVertexArrays (GLsizei n, ثابت GLuint *arrays);
GL_APICALL فراغ GL_APIENTRY glGenVertexArrays (GLsizei n, GLuint *arrays);
GL_APICALL GLboolean GL_APIENTRY glIsVertexArray (GLuint array);
GL_APICALL فراغ GL_APIENTRY glGetIntegeri_v (GLenum target, GLuint index, GLint *data);
GL_APICALL فراغ GL_APIENTRY glBeginTransformFeedback (GLenum primitiveMode);
GL_APICALL فراغ GL_APIENTRY glEndTransformFeedback (فراغ);
GL_APICALL فراغ GL_APIENTRY glBindBufferRange (GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
GL_APICALL فراغ GL_APIENTRY glBindBufferBase (GLenum target, GLuint index, GLuint buffer);
GL_APICALL فراغ GL_APIENTRY glTransformFeedbackVaryings (GLuint program, GLsizei عدد, ثابت GLchar *ثابت*varyings, GLenum bufferMode);
GL_APICALL فراغ GL_APIENTRY glGetTransformFeedbackVarying (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name);
GL_APICALL فراغ GL_APIENTRY glVertexAttribIPointer (GLuint index, GLint size, GLenum type, GLsizei stride, ثابت فراغ *pointer);
GL_APICALL فراغ GL_APIENTRY glGetVertexAttribIiv (GLuint index, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetVertexAttribIuiv (GLuint index, GLenum pname, GLuint *params);
GL_APICALL فراغ GL_APIENTRY glVertexAttribI4i (GLuint index, GLint x, GLint y, GLint z, GLint w);
GL_APICALL فراغ GL_APIENTRY glVertexAttribI4ui (GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
GL_APICALL فراغ GL_APIENTRY glVertexAttribI4iv (GLuint index, ثابت GLint *v);
GL_APICALL فراغ GL_APIENTRY glVertexAttribI4uiv (GLuint index, ثابت GLuint *v);
GL_APICALL فراغ GL_APIENTRY glGetUniformuiv (GLuint program, GLint location, GLuint *params);
GL_APICALL GLint GL_APIENTRY glGetFragDataLocation (GLuint program, ثابت GLchar *name);
GL_APICALL فراغ GL_APIENTRY glUniform1ui (GLint location, GLuint v0);
GL_APICALL فراغ GL_APIENTRY glUniform2ui (GLint location, GLuint v0, GLuint v1);
GL_APICALL فراغ GL_APIENTRY glUniform3ui (GLint location, GLuint v0, GLuint v1, GLuint v2);
GL_APICALL فراغ GL_APIENTRY glUniform4ui (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
GL_APICALL فراغ GL_APIENTRY glUniform1uiv (GLint location, GLsizei عدد, ثابت GLuint *قيمة);
GL_APICALL فراغ GL_APIENTRY glUniform2uiv (GLint location, GLsizei عدد, ثابت GLuint *قيمة);
GL_APICALL فراغ GL_APIENTRY glUniform3uiv (GLint location, GLsizei عدد, ثابت GLuint *قيمة);
GL_APICALL فراغ GL_APIENTRY glUniform4uiv (GLint location, GLsizei عدد, ثابت GLuint *قيمة);
GL_APICALL فراغ GL_APIENTRY glClearBufferiv (GLenum buffer, GLint drawbuffer, ثابت GLint *قيمة);
GL_APICALL فراغ GL_APIENTRY glClearBufferuiv (GLenum buffer, GLint drawbuffer, ثابت GLuint *قيمة);
GL_APICALL فراغ GL_APIENTRY glClearBufferfv (GLenum buffer, GLint drawbuffer, ثابت GLfloat *قيمة);
GL_APICALL فراغ GL_APIENTRY glClearBufferfi (GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
GL_APICALL ثابت GLubyte *GL_APIENTRY glGetStringi (GLenum name, GLuint index);
GL_APICALL فراغ GL_APIENTRY glCopyBufferSubData (GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
GL_APICALL فراغ GL_APIENTRY glGetUniformIndices (GLuint program, GLsizei uniform_عدد, ثابت GLchar *ثابت*uniformNames, GLuint *uniformIndices);
GL_APICALL فراغ GL_APIENTRY glGetActiveUniformsiv (GLuint program, GLsizei uniform_عدد, ثابت GLuint *uniformIndices, GLenum pname, GLint *params);
GL_APICALL GLuint GL_APIENTRY glGetUniformBlockIndex (GLuint program, ثابت GLchar *uniformBlockName);
GL_APICALL فراغ GL_APIENTRY glGetActiveUniformBlockiv (GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetActiveUniformBlockName (GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName);
GL_APICALL فراغ GL_APIENTRY glUniformBlockBinding (GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
GL_APICALL فراغ GL_APIENTRY glDrawArraysInstanced (GLenum mode, GLint first, GLsizei عدد, GLsizei instancecount);
GL_APICALL فراغ GL_APIENTRY glDrawElementsInstanced (GLenum mode, GLsizei عدد, GLenum type, ثابت فراغ *indices, GLsizei instancecount);
GL_APICALL GLsync GL_APIENTRY glFenceSync (GLenum condition, GLbitfield flags);
GL_APICALL GLboolean GL_APIENTRY glIsSync (GLsync sync);
GL_APICALL فراغ GL_APIENTRY glDeleteSync (GLsync sync);
GL_APICALL GLenum GL_APIENTRY glClientWaitSync (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_APICALL فراغ GL_APIENTRY glWaitSync (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_APICALL فراغ GL_APIENTRY glGetInteger64v (GLenum pname, GLint64 *data);
GL_APICALL فراغ GL_APIENTRY glGetSynciv (GLsync sync, GLenum pname, GLsizei عدد, GLsizei *length, GLint *قيم);
GL_APICALL فراغ GL_APIENTRY glGetInteger64i_v (GLenum target, GLuint index, GLint64 *data);
GL_APICALL فراغ GL_APIENTRY glGetBufferParameteri64v (GLenum target, GLenum pname, GLint64 *params);
GL_APICALL فراغ GL_APIENTRY glGenSamplers (GLsizei عدد, GLuint *samplers);
GL_APICALL فراغ GL_APIENTRY glDeleteSamplers (GLsizei عدد, ثابت GLuint *samplers);
GL_APICALL GLboolean GL_APIENTRY glIsSampler (GLuint sampler);
GL_APICALL فراغ GL_APIENTRY glBindSampler (GLuint unit, GLuint sampler);
GL_APICALL فراغ GL_APIENTRY glSamplerParameteri (GLuint sampler, GLenum pname, GLint param);
GL_APICALL فراغ GL_APIENTRY glSamplerParameteriv (GLuint sampler, GLenum pname, ثابت GLint *param);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterf (GLuint sampler, GLenum pname, GLfloat param);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterfv (GLuint sampler, GLenum pname, ثابت GLfloat *param);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameteriv (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameterfv (GLuint sampler, GLenum pname, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY gl_Vertex_Attrib_قاسم (GLuint index, GLuint قاسم);
GL_APICALL فراغ GL_APIENTRY glBindTransformFeedback (GLenum target, GLuint id);
GL_APICALL فراغ GL_APIENTRY glDeleteTransformFeedbacks (GLsizei n, ثابت GLuint *ids);
GL_APICALL فراغ GL_APIENTRY glGenTransformFeedbacks (GLsizei n, GLuint *ids);
GL_APICALL GLboolean GL_APIENTRY glIsTransformFeedback (GLuint id);
GL_APICALL فراغ GL_APIENTRY glPauseTransformFeedback (فراغ);
GL_APICALL فراغ GL_APIENTRY glResumeTransformFeedback (فراغ);
GL_APICALL فراغ GL_APIENTRY gl_Get_Program_ثنائي (GLuint program, GLsizei bufSize, GLsizei *length, GLenum *ثنائي_Format, فراغ *ثنائي);
GL_APICALL فراغ GL_APIENTRY gl_Program_ثنائي (GLuint program, GLenum ثنائي_Format, ثابت فراغ *ثنائي, GLsizei length);
GL_APICALL فراغ GL_APIENTRY glProgramParameteri (GLuint program, GLenum pname, GLint قيمة);
GL_APICALL فراغ GL_APIENTRY glInvalidateFramebuffer (GLenum target, GLsizei رقم_Attachments, ثابت GLenum *attachments);
GL_APICALL فراغ GL_APIENTRY glInvalidateSubFramebuffer (GLenum target, GLsizei رقم_Attachments, ثابت GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height);
GL_APICALL فراغ GL_APIENTRY glTexStorage2D (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
GL_APICALL فراغ GL_APIENTRY glTexStorage3D (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
GL_APICALL فراغ GL_APIENTRY glGetInternalformativ (GLenum target, GLenum internalformat, GLenum pname, GLsizei عدد, GLint *params);
#endif
#endif /* GL_ES_VERSION_3_0 */

#ifndef GL_ES_VERSION_3_1
#define GL_ES_VERSION_3_1 1
#define GL_COMPUTE_SHADER                 0x91B9
#define GL_MAX_COMPUTE_UNIFORM_BLOCKS     0x91BB
#define GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS 0x91BC
#define GL_MAX_COMPUTE_IMAGE_UNIFORMS     0x91BD
#define GL_MAX_COMPUTE_SHARED_MEMORY_SIZE 0x8262
#define GL_MAX_COMPUTE_UNIFORM_COMPONENTS 0x8263
#define GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS 0x8264
#define GL_MAX_COMPUTE_ATOMIC_COUNTERS    0x8265
#define GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS 0x8266
#define GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS 0x90EB
#define GL_MAX_COMPUTE_WORK_GROUP_عدد   0x91BE
#define GL_MAX_COMPUTE_WORK_GROUP_SIZE    0x91BF
#define GL_COMPUTE_WORK_GROUP_SIZE        0x8267
#define GL_DISPATCH_INDIRECT_BUFFER       0x90EE
#define GL_DISPATCH_INDIRECT_BUFFER_BINDING 0x90EF
#define GL_COMPUTE_SHADER_BIT             0x00000020
#define GL_DRAW_INDIRECT_BUFFER           0x8F3F
#define GL_DRAW_INDIRECT_BUFFER_BINDING   0x8F43
#define GL_MAX_UNIFORM_LOCATIONS          0x826E
#define GL_FRAMEBUFFER_DEFAULT_WIDTH      0x9310
#define GL_FRAMEBUFFER_DEFAULT_HEIGHT     0x9311
#define GL_FRAMEBUFFER_DEFAULT_SAMPLES    0x9313
#define GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS 0x9314
#define GL_MAX_FRAMEBUFFER_WIDTH          0x9315
#define GL_MAX_FRAMEBUFFER_HEIGHT         0x9316
#define GL_MAX_FRAMEBUFFER_SAMPLES        0x9318
#define GL_UNIFORM                        0x92E1
#define GL_UNIFORM_BLOCK                  0x92E2
#define GL_PROGRAM_مدخل                  0x92E3
#define GL_PROGRAM_OUTPUT                 0x92E4
#define GL_BUFFER_VARIABLE                0x92E5
#define GL_SHADER_STORAGE_BLOCK           0x92E6
#define GL_ATOMIC_COUNTER_BUFFER          0x92C0
#define GL_TRANSFORM_FEEDBACK_VARYING     0x92F4
#define GL_ACTIVE_RESOURCES               0x92F5
#define GL_MAX_NAME_LENGTH                0x92F6
#define GL_MAX_رقم_ACTIVE_VARIABLES       0x92F7
#define GL_NAME_LENGTH                    0x92F9
#define GL_TYPE                           0x92FA
#define GL_ARRAY_SIZE                     0x92FB
#define GL_OFFSET                         0x92FC
#define GL_BLOCK_INDEX                    0x92FD
#define GL_ARRAY_STRIDE                   0x92FE
#define GL_MATRIX_STRIDE                  0x92FF
#define GL_IS_ROW_MAJOR                   0x9300
#define GL_ATOMIC_COUNTER_BUFFER_INDEX    0x9301
#define GL_BUFFER_BINDING                 0x9302
#define GL_BUFFER_DATA_SIZE               0x9303
#define GL_رقم_ACTIVE_VARIABLES           0x9304
#define GL_ACTIVE_VARIABLES               0x9305
#define GL_REFERENCED_BY_VERTEX_SHADER    0x9306
#define GL_REFERENCED_BY_FRAGMENT_SHADER  0x930A
#define GL_REFERENCED_BY_COMPUTE_SHADER   0x930B
#define GL_قمة_LEVEL_ARRAY_SIZE           0x930C
#define GL_قمة_LEVEL_ARRAY_STRIDE         0x930D
#define GL_LOCATION                       0x930E
#define GL_VERTEX_SHADER_BIT              0x00000001
#define GL_FRAGMENT_SHADER_BIT            0x00000002
#define GL_ALL_SHADER_BITS                0xFFFFFFFF
#define GL_PROGRAM_SEPARABLE              0x8258
#define GL_ACTIVE_PROGRAM                 0x8259
#define GL_PROGRAM_PIPELINE_BINDING       0x825A
#define GL_ATOMIC_COUNTER_BUFFER_BINDING  0x92C1
#define GL_ATOMIC_COUNTER_BUFFER_START    0x92C2
#define GL_ATOMIC_COUNTER_BUFFER_SIZE     0x92C3
#define GL_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS 0x92CC
#define GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS 0x92D0
#define GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS 0x92D1
#define GL_MAX_VERTEX_ATOMIC_COUNTERS     0x92D2
#define GL_MAX_FRAGMENT_ATOMIC_COUNTERS   0x92D6
#define GL_MAX_COMBINED_ATOMIC_COUNTERS   0x92D7
#define GL_MAX_ATOMIC_COUNTER_BUFFER_SIZE 0x92D8
#define GL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS 0x92DC
#define GL_ACTIVE_ATOMIC_COUNTER_BUFFERS  0x92D9
#define GL_UNSIGNED_INT_ATOMIC_COUNTER    0x92DB
#define GL_MAX_IMAGE_UNITS                0x8F38
#define GL_MAX_VERTEX_IMAGE_UNIFORMS      0x90CA
#define GL_MAX_FRAGMENT_IMAGE_UNIFORMS    0x90CE
#define GL_MAX_COMBINED_IMAGE_UNIFORMS    0x90CF
#define GL_IMAGE_BINDING_NAME             0x8F3A
#define GL_IMAGE_BINDING_LEVEL            0x8F3B
#define GL_IMAGE_BINDING_LAYERED          0x8F3C
#define GL_IMAGE_BINDING_LAYER            0x8F3D
#define GL_IMAGE_BINDING_ACCESS           0x8F3E
#define GL_IMAGE_BINDING_FORMAT           0x906E
#define GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT 0x00000001
#define GL_ELEMENT_ARRAY_BARRIER_BIT      0x00000002
#define GL_UNIFORM_BARRIER_BIT            0x00000004
#define GL_TEXTURE_FETCH_BARRIER_BIT      0x00000008
#define GL_SHADER_IMAGE_ACCESS_BARRIER_BIT 0x00000020
#define GL_COMMAND_BARRIER_BIT            0x00000040
#define GL_PIXEL_BUFFER_BARRIER_BIT       0x00000080
#define GL_TEXTURE_UPDATE_BARRIER_BIT     0x00000100
#define GL_BUFFER_UPDATE_BARRIER_BIT      0x00000200
#define GL_FRAMEBUFFER_BARRIER_BIT        0x00000400
#define GL_TRANSFORM_FEEDBACK_BARRIER_BIT 0x00000800
#define GL_ATOMIC_COUNTER_BARRIER_BIT     0x00001000
#define GL_ALL_BARRIER_BITS               0xFFFFFFFF
#define GL_IMAGE_2D                       0x904D
#define GL_IMAGE_3D                       0x904E
#define GL_IMAGE_CUBE                     0x9050
#define GL_IMAGE_2D_ARRAY                 0x9053
#define GL_INT_IMAGE_2D                   0x9058
#define GL_INT_IMAGE_3D                   0x9059
#define GL_INT_IMAGE_CUBE                 0x905B
#define GL_INT_IMAGE_2D_ARRAY             0x905E
#define GL_UNSIGNED_INT_IMAGE_2D          0x9063
#define GL_UNSIGNED_INT_IMAGE_3D          0x9064
#define GL_UNSIGNED_INT_IMAGE_CUBE        0x9066
#define GL_UNSIGNED_INT_IMAGE_2D_ARRAY    0x9069
#define GL_IMAGE_FORMAT_COMPATIBILITY_TYPE 0x90C7
#define GL_IMAGE_FORMAT_COMPATIBILITY_BY_SIZE 0x90C8
#define GL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS 0x90C9
#define GL_READ_ONLY                      0x88B8
#define GL_WRITE_ONLY                     0x88B9
#define GL_READ_WRITE                     0x88BA
#define GL_SHADER_STORAGE_BUFFER          0x90D2
#define GL_SHADER_STORAGE_BUFFER_BINDING  0x90D3
#define GL_SHADER_STORAGE_BUFFER_START    0x90D4
#define GL_SHADER_STORAGE_BUFFER_SIZE     0x90D5
#define GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS 0x90D6
#define GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS 0x90DA
#define GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS 0x90DB
#define GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS 0x90DC
#define GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS 0x90DD
#define GL_MAX_SHADER_STORAGE_BLOCK_SIZE  0x90DE
#define GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT 0x90DF
#define GL_SHADER_STORAGE_BARRIER_BIT     0x00002000
#define GL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES 0x8F39
#define GL_DEPTH_STENCIL_TEXTURE_MODE     0x90EA
#define GL_STENCIL_INDEX                  0x1901
#define GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET 0x8E5E
#define GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET 0x8E5F
#define GL_SAMPLE_POSITION                0x8E50
#define GL_SAMPLE_MASK                    0x8E51
#define GL_SAMPLE_MASK_قيمة              0x8E52
#define GL_TEXTURE_2D_MULTISAMPLE         0x9100
#define GL_MAX_SAMPLE_MASK_كلمات          0x8E59
#define GL_MAX_COLOR_TEXTURE_SAMPLES      0x910E
#define GL_MAX_DEPTH_TEXTURE_SAMPLES      0x910F
#define GL_MAX_INTEGER_SAMPLES            0x9110
#define GL_TEXTURE_BINDING_2D_MULTISAMPLE 0x9104
#define GL_TEXTURE_SAMPLES                0x9106
#define GL_TEXTURE_FIXED_SAMPLE_LOCATIONS 0x9107
#define GL_TEXTURE_WIDTH                  0x1000
#define GL_TEXTURE_HEIGHT                 0x1001
#define GL_TEXTURE_DEPTH                  0x8071
#define GL_TEXTURE_INTERNAL_FORMAT        0x1003
#define GL_TEXTURE_RED_SIZE               0x805C
#define GL_TEXTURE_GREEN_SIZE             0x805D
#define GL_TEXTURE_BLUE_SIZE              0x805E
#define GL_TEXTURE_ALPHA_SIZE             0x805F
#define GL_TEXTURE_DEPTH_SIZE             0x884A
#define GL_TEXTURE_STENCIL_SIZE           0x88F1
#define GL_TEXTURE_SHARED_SIZE            0x8C3F
#define GL_TEXTURE_RED_TYPE               0x8C10
#define GL_TEXTURE_GREEN_TYPE             0x8C11
#define GL_TEXTURE_BLUE_TYPE              0x8C12
#define GL_TEXTURE_ALPHA_TYPE             0x8C13
#define GL_TEXTURE_DEPTH_TYPE             0x8C16
#define GL_TEXTURE_COMPRESSED             0x86A1
#define GL_SAMPLER_2D_MULTISAMPLE         0x9108
#define GL_INT_SAMPLER_2D_MULTISAMPLE     0x9109
#define GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE 0x910A
#define GL_VERTEX_ATTRIB_BINDING          0x82D4
#define GL_VERTEX_ATTRIB_RELATIVE_OFFSET  0x82D5
#define GL_VERTEX_BINDING_قاسم         0x82D6
#define GL_VERTEX_BINDING_OFFSET          0x82D7
#define GL_VERTEX_BINDING_STRIDE          0x82D8
#define GL_VERTEX_BINDING_BUFFER          0x8F4F
#define GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET 0x82D9
#define GL_MAX_VERTEX_ATTRIB_BINDINGS     0x82DA
#define GL_MAX_VERTEX_ATTRIB_STRIDE       0x82E5
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISPATCHCOMPUTEPROC) (GLuint رقم_groups_x, GLuint رقم_groups_y, GLuint رقم_groups_z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISPATCHCOMPUTEINDIRECTPROC) (GLintptr indirect);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWARRAYSINDIRECTPROC) (GLenum mode, ثابت فراغ *indirect);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINDIRECTPROC) (GLenum mode, GLenum type, ثابت فراغ *indirect);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERPARAMETERIPROC) (GLenum target, GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFRAMEBUFFERPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMINTERFACEIVPROC) (GLuint program, GLenum programInterface, GLenum pname, GLint *params);
تعريفنوع GLuint (GL_APIENTRYP PFNGLGETPROGRAMRESOURCEINDEXPROC) (GLuint program, GLenum programInterface, ثابت GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMRESOURCENAMEPROC) (GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMRESOURCEIVPROC) (GLuint program, GLenum programInterface, GLuint index, GLsizei prop_عدد, ثابت GLenum *props, GLsizei عدد, GLsizei *length, GLint *params);
تعريفنوع GLint (GL_APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONPROC) (GLuint program, GLenum programInterface, ثابت GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUSEPROGRAMSTAGESPROC) (GLuint pipeline, GLbitfield stages, GLuint program);
تعريفنوع فراغ (GL_APIENTRYP PFNGLACTIVESHADERPROGRAMPROC) (GLuint pipeline, GLuint program);
تعريفنوع GLuint (GL_APIENTRYP PFNGLCREATESHADERPROGRAMVPROC) (GLenum type, GLsizei عدد, ثابت GLchar *ثابت*strings);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDPROGRAMPIPELINEPROC) (GLuint pipeline);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEPROGRAMPIPELINESPROC) (GLsizei n, ثابت GLuint *pipelines);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENPROGRAMPIPELINESPROC) (GLsizei n, GLuint *pipelines);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISPROGRAMPIPELINEPROC) (GLuint pipeline);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMPIPELINEIVPROC) (GLuint pipeline, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1IPROC) (GLuint program, GLint location, GLint v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2IPROC) (GLuint program, GLint location, GLint v0, GLint v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3IPROC) (GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4IPROC) (GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UIPROC) (GLuint program, GLint location, GLuint v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UIPROC) (GLuint program, GLint location, GLuint v0, GLuint v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UIPROC) (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UIPROC) (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1FPROC) (GLuint program, GLint location, GLfloat v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2FPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3FPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4FPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1IVPROC) (GLuint program, GLint location, GLsizei عدد, ثابت GLint *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2IVPROC) (GLuint program, GLint location, GLsizei عدد, ثابت GLint *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3IVPROC) (GLuint program, GLint location, GLsizei عدد, ثابت GLint *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4IVPROC) (GLuint program, GLint location, GLsizei عدد, ثابت GLint *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UIVPROC) (GLuint program, GLint location, GLsizei عدد, ثابت GLuint *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UIVPROC) (GLuint program, GLint location, GLsizei عدد, ثابت GLuint *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UIVPROC) (GLuint program, GLint location, GLsizei عدد, ثابت GLuint *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UIVPROC) (GLuint program, GLint location, GLsizei عدد, ثابت GLuint *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1FVPROC) (GLuint program, GLint location, GLsizei عدد, ثابت GLfloat *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2FVPROC) (GLuint program, GLint location, GLsizei عدد, ثابت GLfloat *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3FVPROC) (GLuint program, GLint location, GLsizei عدد, ثابت GLfloat *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4FVPROC) (GLuint program, GLint location, GLsizei عدد, ثابت GLfloat *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2FVPROC) (GLuint program, GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3FVPROC) (GLuint program, GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4FVPROC) (GLuint program, GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC) (GLuint program, GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC) (GLuint program, GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC) (GLuint program, GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC) (GLuint program, GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC) (GLuint program, GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC) (GLuint program, GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVALIDATEPROGRAMPIPELINEPROC) (GLuint pipeline);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMPIPELINEINFOLOGPROC) (GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDIMAGETEXTUREPROC) (GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETBOOLEANI_VPROC) (GLenum target, GLuint index, GLboolean *data);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMEMORYBARRIERPROC) (GLbitfield barriers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMEMORYBARRIERBYREGIONPROC) (GLbitfield barriers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE2DMULTISAMPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETMULTISAMPLEFVPROC) (GLenum pname, GLuint index, GLfloat *val);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLEMASKIPROC) (GLuint mask_رقم, GLbitfield mask);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXLEVELPARAMETERIVPROC) (GLenum target, GLint level, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXLEVELPARAMETERFVPROC) (GLenum target, GLint level, GLenum pname, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDVERTEXBUFFERPROC) (GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBFORMATPROC) (GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBIFORMATPROC) (GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBBINDINGPROC) (GLuint attribindex, GLuint bindingindex);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXBINDINGDIVISORPROC) (GLuint bindingindex, GLuint قاسم);
#إذا GL_GLES_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDispatchCompute (GLuint رقم_groups_x, GLuint رقم_groups_y, GLuint رقم_groups_z);
GL_APICALL فراغ GL_APIENTRY glDispatchComputeIndirect (GLintptr indirect);
GL_APICALL فراغ GL_APIENTRY glDrawArraysIndirect (GLenum mode, ثابت فراغ *indirect);
GL_APICALL فراغ GL_APIENTRY glDrawElementsIndirect (GLenum mode, GLenum type, ثابت فراغ *indirect);
GL_APICALL فراغ GL_APIENTRY glFramebufferParameteri (GLenum target, GLenum pname, GLint param);
GL_APICALL فراغ GL_APIENTRY glGetFramebufferParameteriv (GLenum target, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetProgramInterfaceiv (GLuint program, GLenum programInterface, GLenum pname, GLint *params);
GL_APICALL GLuint GL_APIENTRY glGetProgramResourceIndex (GLuint program, GLenum programInterface, ثابت GLchar *name);
GL_APICALL فراغ GL_APIENTRY glGetProgramResourceName (GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name);
GL_APICALL فراغ GL_APIENTRY glGetProgramResourceiv (GLuint program, GLenum programInterface, GLuint index, GLsizei prop_عدد, ثابت GLenum *props, GLsizei عدد, GLsizei *length, GLint *params);
GL_APICALL GLint GL_APIENTRY glGetProgramResourceLocation (GLuint program, GLenum programInterface, ثابت GLchar *name);
GL_APICALL فراغ GL_APIENTRY glUseProgramStages (GLuint pipeline, GLbitfield stages, GLuint program);
GL_APICALL فراغ GL_APIENTRY glActiveShaderProgram (GLuint pipeline, GLuint program);
GL_APICALL GLuint GL_APIENTRY glCreateShaderProgramv (GLenum type, GLsizei عدد, ثابت GLchar *ثابت*strings);
GL_APICALL فراغ GL_APIENTRY glBindProgramPipeline (GLuint pipeline);
GL_APICALL فراغ GL_APIENTRY glDeleteProgramPipelines (GLsizei n, ثابت GLuint *pipelines);
GL_APICALL فراغ GL_APIENTRY glGenProgramPipelines (GLsizei n, GLuint *pipelines);
GL_APICALL GLboolean GL_APIENTRY glIsProgramPipeline (GLuint pipeline);
GL_APICALL فراغ GL_APIENTRY glGetProgramPipelineiv (GLuint pipeline, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glProgramUniform1i (GLuint program, GLint location, GLint v0);
GL_APICALL فراغ GL_APIENTRY glProgramUniform2i (GLuint program, GLint location, GLint v0, GLint v1);
GL_APICALL فراغ GL_APIENTRY glProgramUniform3i (GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
GL_APICALL فراغ GL_APIENTRY glProgramUniform4i (GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
GL_APICALL فراغ GL_APIENTRY glProgramUniform1ui (GLuint program, GLint location, GLuint v0);
GL_APICALL فراغ GL_APIENTRY glProgramUniform2ui (GLuint program, GLint location, GLuint v0, GLuint v1);
GL_APICALL فراغ GL_APIENTRY glProgramUniform3ui (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
GL_APICALL فراغ GL_APIENTRY glProgramUniform4ui (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
GL_APICALL فراغ GL_APIENTRY glProgramUniform1f (GLuint program, GLint location, GLfloat v0);
GL_APICALL فراغ GL_APIENTRY glProgramUniform2f (GLuint program, GLint location, GLfloat v0, GLfloat v1);
GL_APICALL فراغ GL_APIENTRY glProgramUniform3f (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
GL_APICALL فراغ GL_APIENTRY glProgramUniform4f (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
GL_APICALL فراغ GL_APIENTRY glProgramUniform1iv (GLuint program, GLint location, GLsizei عدد, ثابت GLint *قيمة);
GL_APICALL فراغ GL_APIENTRY glProgramUniform2iv (GLuint program, GLint location, GLsizei عدد, ثابت GLint *قيمة);
GL_APICALL فراغ GL_APIENTRY glProgramUniform3iv (GLuint program, GLint location, GLsizei عدد, ثابت GLint *قيمة);
GL_APICALL فراغ GL_APIENTRY glProgramUniform4iv (GLuint program, GLint location, GLsizei عدد, ثابت GLint *قيمة);
GL_APICALL فراغ GL_APIENTRY glProgramUniform1uiv (GLuint program, GLint location, GLsizei عدد, ثابت GLuint *قيمة);
GL_APICALL فراغ GL_APIENTRY glProgramUniform2uiv (GLuint program, GLint location, GLsizei عدد, ثابت GLuint *قيمة);
GL_APICALL فراغ GL_APIENTRY glProgramUniform3uiv (GLuint program, GLint location, GLsizei عدد, ثابت GLuint *قيمة);
GL_APICALL فراغ GL_APIENTRY glProgramUniform4uiv (GLuint program, GLint location, GLsizei عدد, ثابت GLuint *قيمة);
GL_APICALL فراغ GL_APIENTRY glProgramUniform1fv (GLuint program, GLint location, GLsizei عدد, ثابت GLfloat *قيمة);
GL_APICALL فراغ GL_APIENTRY glProgramUniform2fv (GLuint program, GLint location, GLsizei عدد, ثابت GLfloat *قيمة);
GL_APICALL فراغ GL_APIENTRY glProgramUniform3fv (GLuint program, GLint location, GLsizei عدد, ثابت GLfloat *قيمة);
GL_APICALL فراغ GL_APIENTRY glProgramUniform4fv (GLuint program, GLint location, GLsizei عدد, ثابت GLfloat *قيمة);
GL_APICALL فراغ GL_APIENTRY glProgramUniformMatrix2fv (GLuint program, GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
GL_APICALL فراغ GL_APIENTRY glProgramUniformMatrix3fv (GLuint program, GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
GL_APICALL فراغ GL_APIENTRY glProgramUniformMatrix4fv (GLuint program, GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
GL_APICALL فراغ GL_APIENTRY glProgramUniformMatrix2x3fv (GLuint program, GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
GL_APICALL فراغ GL_APIENTRY glProgramUniformMatrix3x2fv (GLuint program, GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
GL_APICALL فراغ GL_APIENTRY glProgramUniformMatrix2x4fv (GLuint program, GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
GL_APICALL فراغ GL_APIENTRY glProgramUniformMatrix4x2fv (GLuint program, GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
GL_APICALL فراغ GL_APIENTRY glProgramUniformMatrix3x4fv (GLuint program, GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
GL_APICALL فراغ GL_APIENTRY glProgramUniformMatrix4x3fv (GLuint program, GLint location, GLsizei عدد, GLboolean transpose, ثابت GLfloat *قيمة);
GL_APICALL فراغ GL_APIENTRY glValidateProgramPipeline (GLuint pipeline);
GL_APICALL فراغ GL_APIENTRY glGetProgramPipelineInfoLog (GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
GL_APICALL فراغ GL_APIENTRY glBindImageTexture (GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
GL_APICALL فراغ GL_APIENTRY glGetBooleani_v (GLenum target, GLuint index, GLboolean *data);
GL_APICALL فراغ GL_APIENTRY glMemoryBarrier (GLbitfield barriers);
GL_APICALL فراغ GL_APIENTRY glMemoryBarrierByRegion (GLbitfield barriers);
GL_APICALL فراغ GL_APIENTRY glTexStorage2DMultisample (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
GL_APICALL فراغ GL_APIENTRY glGetMultisamplefv (GLenum pname, GLuint index, GLfloat *val);
GL_APICALL فراغ GL_APIENTRY glSampleMaski (GLuint mask_رقم, GLbitfield mask);
GL_APICALL فراغ GL_APIENTRY glGetTexLevelParameteriv (GLenum target, GLint level, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetTexLevelParameterfv (GLenum target, GLint level, GLenum pname, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY glBindVertexBuffer (GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
GL_APICALL فراغ GL_APIENTRY glVertexAttribFormat (GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
GL_APICALL فراغ GL_APIENTRY glVertexAttribIFormat (GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
GL_APICALL فراغ GL_APIENTRY glVertexAttribBinding (GLuint attribindex, GLuint bindingindex);
GL_APICALL فراغ GL_APIENTRY gl_Vertex_Binding_قاسم (GLuint bindingindex, GLuint قاسم);
#endif
#endif /* GL_ES_VERSION_3_1 */

#ifndef GL_ES_VERSION_3_2
#define GL_ES_VERSION_3_2 1
تعريفنوع فراغ (GL_APIENTRY  *GLDEBUGPROC)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,ثابت GLchar *message,ثابت فراغ *userParam);
#define GL_MULTISAMPLE_سطر_WIDTH_RANGE   0x9381
#define GL_MULTISAMPLE_سطر_WIDTH_GRANULARITY 0x9382
#define GL_MULTIPLY                       0x9294
#define GL_SCREEN                         0x9295
#define GL_OVERLAY                        0x9296
#define GL_DARKEN                         0x9297
#define GL_LIGHTEN                        0x9298
#define GL_COLORDODGE                     0x9299
#define GL_COLORBURN                      0x929A
#define GL_HARDLIGHT                      0x929B
#define GL_SOFTLIGHT                      0x929C
#define GL_DIFFERENCE                     0x929E
#define GL_EXCLUSION                      0x92A0
#define GL_HSL_HUE                        0x92AD
#define GL_HSL_SATURATION                 0x92AE
#define GL_HSL_COLOR                      0x92AF
#define GL_HSL_LUMINOSITY                 0x92B0
#define GL_DEBUG_OUTPUT_SYNCHRONOUS       0x8242
#define GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH 0x8243
#define GL_DEBUG_CALLBACK_FUNCTION        0x8244
#define GL_DEBUG_CALLBACK_USER_PARAM      0x8245
#define GL_DEBUG_SOURCE_API               0x8246
#define GL_DEBUG_SOURCE_WINDOW_SYSTEM     0x8247
#define GL_DEBUG_SOURCE_SHADER_COMPILER   0x8248
#define GL_DEBUG_SOURCE_THIRD_PARTY       0x8249
#define GL_DEBUG_SOURCE_APPLICATION       0x824A
#define GL_DEBUG_SOURCE_OTHER             0x824B
#define GL_DEBUG_TYPE_ERROR               0x824C
#define GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR 0x824D
#define GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR  0x824E
#define GL_DEBUG_TYPE_PORTABILITY         0x824F
#define GL_DEBUG_TYPE_PERFORMANCE         0x8250
#define GL_DEBUG_TYPE_OTHER               0x8251
#define GL_DEBUG_TYPE_MARKER              0x8268
#define GL_DEBUG_TYPE_ادفع_GROUP          0x8269
#define GL_DEBUG_TYPE_اسحب_GROUP           0x826A
#define GL_DEBUG_SEVERITY_NOTIFICATION    0x826B
#define GL_MAX_DEBUG_GROUP_مكدس_DEPTH    0x826C
#define GL_DEBUG_GROUP_مكدس_DEPTH        0x826D
#define GL_BUFFER                         0x82E0
#define GL_SHADER                         0x82E1
#define GL_PROGRAM                        0x82E2
#define GL_VERTEX_ARRAY                   0x8074
#define GL_QUERY                          0x82E3
#define GL_PROGRAM_PIPELINE               0x82E4
#define GL_SAMPLER                        0x82E6
#define GL_MAX_LABEL_LENGTH               0x82E8
#define GL_MAX_DEBUG_MESSAGE_LENGTH       0x9143
#define GL_MAX_DEBUG_LOGGED_MESSAGES      0x9144
#define GL_DEBUG_LOGGED_MESSAGES          0x9145
#define GL_DEBUG_SEVERITY_عالي            0x9146
#define GL_DEBUG_SEVERITY_MEDIUM          0x9147
#define GL_DEBUG_SEVERITY_أدنى             0x9148
#define GL_DEBUG_OUTPUT                   0x92E0
#define GL_CONTEXT_FLAG_DEBUG_BIT         0x00000002
#define GL_مكدس_OVERFLOW                 0x0503
#define GL_مكدس_UNDERFLOW                0x0504
#define GL_GEOMETRY_SHADER                0x8DD9
#define GL_GEOMETRY_SHADER_BIT            0x00000004
#define GL_GEOMETRY_VERTICES_OUT          0x8916
#define GL_GEOMETRY_مدخل_TYPE            0x8917
#define GL_GEOMETRY_OUTPUT_TYPE           0x8918
#define GL_GEOMETRY_SHADER_INVOCATIONS    0x887F
#define GL_LAYER_PROVOKING_VERTEX         0x825E
#define GL_أسطر_ADJACENCY                0x000A
#define GL_سطر_STRIP_ADJACENCY           0x000B
#define GL_TRIANGLES_ADJACENCY            0x000C
#define GL_TRIANGLE_STRIP_ADJACENCY       0x000D
#define GL_MAX_GEOMETRY_UNIFORM_COMPONENTS 0x8DDF
#define GL_MAX_GEOMETRY_UNIFORM_BLOCKS    0x8A2C
#define GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS 0x8A32
#define GL_MAX_GEOMETRY_مدخل_COMPONENTS  0x9123
#define GL_MAX_GEOMETRY_OUTPUT_COMPONENTS 0x9124
#define GL_MAX_GEOMETRY_OUTPUT_VERTICES   0x8DE0
#define GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS 0x8DE1
#define GL_MAX_GEOMETRY_SHADER_INVOCATIONS 0x8E5A
#define GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS 0x8C29
#define GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS 0x92CF
#define GL_MAX_GEOMETRY_ATOMIC_COUNTERS   0x92D5
#define GL_MAX_GEOMETRY_IMAGE_UNIFORMS    0x90CD
#define GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS 0x90D7
#define GL_FIRST_VERTEX_CONVENTION        0x8E4D
#define GL_LAST_VERTEX_CONVENTION         0x8E4E
#define GL_UNDEFINED_VERTEX               0x8260
#define GL_PRIMITIVES_GENERATED           0x8C87
#define GL_FRAMEBUFFER_DEFAULT_LAYERS     0x9312
#define GL_MAX_FRAMEBUFFER_LAYERS         0x9317
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS 0x8DA8
#define GL_FRAMEBUFFER_ATTACHMENT_LAYERED 0x8DA7
#define GL_REFERENCED_BY_GEOMETRY_SHADER  0x9309
#define GL_PRIMITIVE_BOUNDING_BOX         0x92BE
#define GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT 0x00000004
#define GL_CONTEXT_FLAGS                  0x821E
#define GL_LOSE_CONTEXT_ON_RESET          0x8252
#define GL_GUILTY_CONTEXT_RESET           0x8253
#define GL_INNOCENT_CONTEXT_RESET         0x8254
#define GL_UNKNOWN_CONTEXT_RESET          0x8255
#define GL_RESET_NOTIFICATION_STRATEGY    0x8256
#define GL_NO_RESET_NOTIFICATION          0x8261
#define GL_CONTEXT_LOST                   0x0507
#define GL_SAMPLE_SHADING                 0x8C36
#define GL_MIN_SAMPLE_SHADING_قيمة       0x8C37
#define GL_MIN_FRAGMENT_INTERPOLATION_OFFSET 0x8E5B
#define GL_MAX_FRAGMENT_INTERPOLATION_OFFSET 0x8E5C
#define GL_FRAGMENT_INTERPOLATION_OFFSET_BITS 0x8E5D
#define GL_PATCHES                        0x000E
#define GL_PATCH_VERTICES                 0x8E72
#define GL_TESS_CONTROL_OUTPUT_VERTICES   0x8E75
#define GL_TESS_GEN_MODE                  0x8E76
#define GL_TESS_GEN_SPACING               0x8E77
#define GL_TESS_GEN_VERTEX_ORDER          0x8E78
#define GL_TESS_GEN_POINT_MODE            0x8E79
#define GL_ISOLINES                       0x8E7A
#define GL_QUADS                          0x0007
#define GL_FRACTIONAL_ODD                 0x8E7B
#define GL_FRACTIONAL_EVEN                0x8E7C
#define GL_MAX_PATCH_VERTICES             0x8E7D
#define GL_MAX_TESS_GEN_LEVEL             0x8E7E
#define GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS 0x8E7F
#define GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS 0x8E80
#define GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS 0x8E81
#define GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS 0x8E82
#define GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS 0x8E83
#define GL_MAX_TESS_PATCH_COMPONENTS      0x8E84
#define GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS 0x8E85
#define GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS 0x8E86
#define GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS 0x8E89
#define GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS 0x8E8A
#define GL_MAX_TESS_CONTROL_مدخل_COMPONENTS 0x886C
#define GL_MAX_TESS_EVALUATION_مدخل_COMPONENTS 0x886D
#define GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS 0x8E1E
#define GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS 0x8E1F
#define GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS 0x92CD
#define GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS 0x92CE
#define GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS 0x92D3
#define GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS 0x92D4
#define GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS 0x90CB
#define GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS 0x90CC
#define GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS 0x90D8
#define GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS 0x90D9
#define GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED 0x8221
#define GL_IS_PER_PATCH                   0x92E7
#define GL_REFERENCED_BY_TESS_CONTROL_SHADER 0x9307
#define GL_REFERENCED_BY_TESS_EVALUATION_SHADER 0x9308
#define GL_TESS_CONTROL_SHADER            0x8E88
#define GL_TESS_EVALUATION_SHADER         0x8E87
#define GL_TESS_CONTROL_SHADER_BIT        0x00000008
#define GL_TESS_EVALUATION_SHADER_BIT     0x00000010
#define GL_TEXTURE_BORDER_COLOR           0x1004
#define GL_CLAMP_TO_BORDER                0x812D
#define GL_TEXTURE_BUFFER                 0x8C2A
#define GL_TEXTURE_BUFFER_BINDING         0x8C2A
#define GL_MAX_TEXTURE_BUFFER_SIZE        0x8C2B
#define GL_TEXTURE_BINDING_BUFFER         0x8C2C
#define GL_TEXTURE_BUFFER_DATA_STORE_BINDING 0x8C2D
#define GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT 0x919F
#define GL_SAMPLER_BUFFER                 0x8DC2
#define GL_INT_SAMPLER_BUFFER             0x8DD0
#define GL_UNSIGNED_INT_SAMPLER_BUFFER    0x8DD8
#define GL_IMAGE_BUFFER                   0x9051
#define GL_INT_IMAGE_BUFFER               0x905C
#define GL_UNSIGNED_INT_IMAGE_BUFFER      0x9067
#define GL_TEXTURE_BUFFER_OFFSET          0x919D
#define GL_TEXTURE_BUFFER_SIZE            0x919E
#define GL_COMPRESSED_RGBA_ASTC_4x4       0x93B0
#define GL_COMPRESSED_RGBA_ASTC_5x4       0x93B1
#define GL_COMPRESSED_RGBA_ASTC_5x5       0x93B2
#define GL_COMPRESSED_RGBA_ASTC_6x5       0x93B3
#define GL_COMPRESSED_RGBA_ASTC_6x6       0x93B4
#define GL_COMPRESSED_RGBA_ASTC_8x5       0x93B5
#define GL_COMPRESSED_RGBA_ASTC_8x6       0x93B6
#define GL_COMPRESSED_RGBA_ASTC_8x8       0x93B7
#define GL_COMPRESSED_RGBA_ASTC_10x5      0x93B8
#define GL_COMPRESSED_RGBA_ASTC_10x6      0x93B9
#define GL_COMPRESSED_RGBA_ASTC_10x8      0x93BA
#define GL_COMPRESSED_RGBA_ASTC_10x10     0x93BB
#define GL_COMPRESSED_RGBA_ASTC_12x10     0x93BC
#define GL_COMPRESSED_RGBA_ASTC_12x12     0x93BD
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4 0x93D0
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4 0x93D1
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5 0x93D2
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5 0x93D3
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6 0x93D4
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5 0x93D5
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6 0x93D6
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8 0x93D7
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5 0x93D8
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6 0x93D9
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8 0x93DA
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10 0x93DB
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10 0x93DC
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12 0x93DD
#define GL_TEXTURE_CUBE_MAP_ARRAY         0x9009
#define GL_TEXTURE_BINDING_CUBE_MAP_ARRAY 0x900A
#define GL_SAMPLER_CUBE_MAP_ARRAY         0x900C
#define GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW  0x900D
#define GL_INT_SAMPLER_CUBE_MAP_ARRAY     0x900E
#define GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY 0x900F
#define GL_IMAGE_CUBE_MAP_ARRAY           0x9054
#define GL_INT_IMAGE_CUBE_MAP_ARRAY       0x905F
#define GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY 0x906A
#define GL_TEXTURE_2D_MULTISAMPLE_ARRAY   0x9102
#define GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY 0x9105
#define GL_SAMPLER_2D_MULTISAMPLE_ARRAY   0x910B
#define GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910C
#define GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910D
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDBARRIERPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYIMAGESUBDATAPROC) (GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEBUGMESSAGECONTROLPROC) (GLenum source, GLenum type, GLenum severity, GLsizei عدد, ثابت GLuint *ids, GLboolean enabled);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEBUGMESSAGEINSERTPROC) (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, ثابت GLchar *buf);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEBUGMESSAGECALLBACKPROC) (GLDEBUGPROC callback, ثابت فراغ *userParam);
تعريفنوع GLuint (GL_APIENTRYP PFNGLGETDEBUGMESSAGELOGPROC) (GLuint عدد, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPUSHDEBUGGROUPPROC) (GLenum source, GLuint id, GLsizei length, ثابت GLchar *message);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOPDEBUGGROUPPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLOBJECTLABELPROC) (GLenum identifier, GLuint name, GLsizei length, ثابت GLchar *label);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETOBJECTLABELPROC) (GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, GLchar *label);
تعريفنوع فراغ (GL_APIENTRYP PFNGLOBJECTPTRLABELPROC) (ثابت فراغ *ptr, GLsizei length, ثابت GLchar *label);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETOBJECTPTRLABELPROC) (ثابت فراغ *ptr, GLsizei bufSize, GLsizei *length, GLchar *label);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPOINTERVPROC) (GLenum pname, فراغ **params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENABLEIPROC) (GLenum target, GLuint index);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISABLEIPROC) (GLenum target, GLuint index);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONIPROC) (GLuint buf, GLenum mode);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEIPROC) (GLuint buf, GLenum modeRGB, GLenum modeAlpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDFUNCIPROC) (GLuint buf, GLenum src, GLenum dst);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEIPROC) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOLORMASKIPROC) (GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISENABLEDIPROC) (GLenum target, GLuint index);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSBASEVERTEXPROC) (GLenum mode, GLsizei عدد, GLenum type, ثابت فراغ *indices, GLint basevertex);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC) (GLenum mode, GLuint start, GLuint end, GLsizei عدد, GLenum type, ثابت فراغ *indices, GLint basevertex);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC) (GLenum mode, GLsizei عدد, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLint basevertex);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPRIMITIVEBOUNDINGBOXPROC) (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
تعريفنوع GLenum (GL_APIENTRYP PFNGLGETGRAPHICSRESETSTATUSPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLREADNPIXELSPROC) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, فراغ *data);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNUNIFORMFVPROC) (GLuint program, GLint location, GLsizei bufSize, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNUNIFORMIVPROC) (GLuint program, GLint location, GLsizei bufSize, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNUNIFORMUIVPROC) (GLuint program, GLint location, GLsizei bufSize, GLuint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMINSAMPLESHADINGPROC) (GLfloat قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATCHPARAMETERIPROC) (GLenum pname, GLint قيمة);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERIIVPROC) (GLenum target, GLenum pname, ثابت GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERIUIVPROC) (GLenum target, GLenum pname, ثابت GLuint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXPARAMETERIIVPROC) (GLenum target, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXPARAMETERIUIVPROC) (GLenum target, GLenum pname, GLuint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIIVPROC) (GLuint sampler, GLenum pname, ثابت GLint *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIUIVPROC) (GLuint sampler, GLenum pname, ثابت GLuint *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIIVPROC) (GLuint sampler, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIUIVPROC) (GLuint sampler, GLenum pname, GLuint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXBUFFERPROC) (GLenum target, GLenum internalformat, GLuint buffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXBUFFERRANGEPROC) (GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE3DMULTISAMPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
#إذا GL_GLES_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glBlendBarrier (فراغ);
GL_APICALL فراغ GL_APIENTRY glCopyImageSubData (GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
GL_APICALL فراغ GL_APIENTRY glDebugMessageControl (GLenum source, GLenum type, GLenum severity, GLsizei عدد, ثابت GLuint *ids, GLboolean enabled);
GL_APICALL فراغ GL_APIENTRY gl_Debug_Message_أدرج (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, ثابت GLchar *buf);
GL_APICALL فراغ GL_APIENTRY glDebugMessageCallback (GLDEBUGPROC callback, ثابت فراغ *userParam);
GL_APICALL GLuint GL_APIENTRY glGetDebugMessageLog (GLuint عدد, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog);
GL_APICALL فراغ GL_APIENTRY gl_ادفع_Debug_Group (GLenum source, GLuint id, GLsizei length, ثابت GLchar *message);
GL_APICALL فراغ GL_APIENTRY gl_اسحب_Debug_Group (فراغ);
GL_APICALL فراغ GL_APIENTRY glObjectLabel (GLenum identifier, GLuint name, GLsizei length, ثابت GLchar *label);
GL_APICALL فراغ GL_APIENTRY glGetObjectLabel (GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, GLchar *label);
GL_APICALL فراغ GL_APIENTRY glObjectPtrLabel (ثابت فراغ *ptr, GLsizei length, ثابت GLchar *label);
GL_APICALL فراغ GL_APIENTRY glGetObjectPtrLabel (ثابت فراغ *ptr, GLsizei bufSize, GLsizei *length, GLchar *label);
GL_APICALL فراغ GL_APIENTRY glGetPointerv (GLenum pname, فراغ **params);
GL_APICALL فراغ GL_APIENTRY glEnablei (GLenum target, GLuint index);
GL_APICALL فراغ GL_APIENTRY glDisablei (GLenum target, GLuint index);
GL_APICALL فراغ GL_APIENTRY glBlendEquationi (GLuint buf, GLenum mode);
GL_APICALL فراغ GL_APIENTRY glBlendEquationSeparatei (GLuint buf, GLenum modeRGB, GLenum modeAlpha);
GL_APICALL فراغ GL_APIENTRY glBlendFunci (GLuint buf, GLenum src, GLenum dst);
GL_APICALL فراغ GL_APIENTRY glBlendFuncSeparatei (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
GL_APICALL فراغ GL_APIENTRY glColorMaski (GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
GL_APICALL GLboolean GL_APIENTRY glIsEnabledi (GLenum target, GLuint index);
GL_APICALL فراغ GL_APIENTRY glDrawElementsBaseVertex (GLenum mode, GLsizei عدد, GLenum type, ثابت فراغ *indices, GLint basevertex);
GL_APICALL فراغ GL_APIENTRY glDrawRangeElementsBaseVertex (GLenum mode, GLuint start, GLuint end, GLsizei عدد, GLenum type, ثابت فراغ *indices, GLint basevertex);
GL_APICALL فراغ GL_APIENTRY glDrawElementsInstancedBaseVertex (GLenum mode, GLsizei عدد, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLint basevertex);
GL_APICALL فراغ GL_APIENTRY glFramebufferTexture (GLenum target, GLenum attachment, GLuint texture, GLint level);
GL_APICALL فراغ GL_APIENTRY glPrimitiveBoundingBox (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
GL_APICALL GLenum GL_APIENTRY glGetGraphicsResetStatus (فراغ);
GL_APICALL فراغ GL_APIENTRY glReadnPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, فراغ *data);
GL_APICALL فراغ GL_APIENTRY glGetnUniformfv (GLuint program, GLint location, GLsizei bufSize, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY glGetnUniformiv (GLuint program, GLint location, GLsizei bufSize, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetnUniformuiv (GLuint program, GLint location, GLsizei bufSize, GLuint *params);
GL_APICALL فراغ GL_APIENTRY glMinSampleShading (GLfloat قيمة);
GL_APICALL فراغ GL_APIENTRY glPatchParameteri (GLenum pname, GLint قيمة);
GL_APICALL فراغ GL_APIENTRY glTexParameterIiv (GLenum target, GLenum pname, ثابت GLint *params);
GL_APICALL فراغ GL_APIENTRY glTexParameterIuiv (GLenum target, GLenum pname, ثابت GLuint *params);
GL_APICALL فراغ GL_APIENTRY glGetTexParameterIiv (GLenum target, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetTexParameterIuiv (GLenum target, GLenum pname, GLuint *params);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterIiv (GLuint sampler, GLenum pname, ثابت GLint *param);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterIuiv (GLuint sampler, GLenum pname, ثابت GLuint *param);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameterIiv (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameterIuiv (GLuint sampler, GLenum pname, GLuint *params);
GL_APICALL فراغ GL_APIENTRY glTexBuffer (GLenum target, GLenum internalformat, GLuint buffer);
GL_APICALL فراغ GL_APIENTRY glTexBufferRange (GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
GL_APICALL فراغ GL_APIENTRY glTexStorage3DMultisample (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
#endif
#endif /* GL_ES_VERSION_3_2 */

#ifdef __cplusplus
}
#endif

#endif
