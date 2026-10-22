#ifndef __gles2_gl2_h_
#define __gles2_gl2_h_ 1

#ifdef __cplusplus
बाह्य "C" {
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

#अन्तर्भाव <GLES2/gl2platform.h>

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
 * Versions considered: 2\.[0-9]
 * Versions emitted: .*
 * Default extensions included: None
 * Additional extensions included: _nomatch_^
 * Extensions removed: _nomatch_^
 */

#ifndef GL_ES_VERSION_2_0
#define GL_ES_VERSION_2_0 1
#अन्तर्भाव <KHR/khrplatform.h>
प्रकारनिर्देश khronos_int8_t GLbyte;
प्रकारनिर्देश khronos_float_t GLclampf;
प्रकारनिर्देश khronos_int32_t GLfixed;
प्रकारनिर्देश khronos_int16_t GLshort;
प्रकारनिर्देश khronos_uint16_t GLushort;
प्रकारनिर्देश शून्य GLvoid;
प्रकारनिर्देश संरचना __GLsync *GLsync;
प्रकारनिर्देश khronos_int64_t GLint64;
प्रकारनिर्देश khronos_uint64_t GLuint64;
प्रकारनिर्देश unsigned पूर्णाङ्क GLenum;
प्रकारनिर्देश unsigned पूर्णाङ्क GLuint;
प्रकारनिर्देश वर्ण GLchar;
प्रकारनिर्देश khronos_float_t GLfloat;
प्रकारनिर्देश khronos_ssize_t GLsizeiptr;
प्रकारनिर्देश khronos_intptr_t GLintptr;
प्रकारनिर्देश unsigned पूर्णाङ्क GLbitfield;
प्रकारनिर्देश पूर्णाङ्क GLint;
प्रकारनिर्देश unsigned वर्ण GLboolean;
प्रकारनिर्देश पूर्णाङ्क GLsizei;
प्रकारनिर्देश khronos_uint8_t GLubyte;
#define GL_DEPTH_BUFFER_BIT               0x00000100
#define GL_STENCIL_BUFFER_BIT             0x00000400
#define GL_COLOR_BUFFER_BIT               0x00004000
#define GL_FALSE                          0
#define GL_TRUE                           1
#define GL_POINTS                         0x0000
#define GL_पङ्क्तयः                          0x0001
#define GL_पङ्क्तिः_LOOP                      0x0002
#define GL_पङ्क्तिः_STRIP                     0x0003
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
#define GL_INVALID_मानम्                  0x0501
#define GL_INVALID_OPERATION              0x0502
#define GL_OUT_OF_MEMORY                  0x0505
#define GL_CW                             0x0900
#define GL_CCW                            0x0901
#define GL_पङ्क्तिः_WIDTH                     0x0B21
#define GL_ALIASED_POINT_SIZE_RANGE       0x846D
#define GL_ALIASED_पङ्क्तिः_WIDTH_RANGE       0x846E
#define GL_CULL_FACE_MODE                 0x0B45
#define GL_FRONT_FACE                     0x0B46
#define GL_DEPTH_RANGE                    0x0B70
#define GL_DEPTH_WRITEMASK                0x0B72
#define GL_DEPTH_CLEAR_मानम्              0x0B73
#define GL_DEPTH_FUNC                     0x0B74
#define GL_STENCIL_CLEAR_मानम्            0x0B91
#define GL_STENCIL_FUNC                   0x0B92
#define GL_STENCIL_FAIL                   0x0B94
#define GL_STENCIL_PASS_DEPTH_FAIL        0x0B95
#define GL_STENCIL_PASS_DEPTH_PASS        0x0B96
#define GL_STENCIL_REF                    0x0B97
#define GL_STENCIL_मानम्_MASK             0x0B93
#define GL_STENCIL_WRITEMASK              0x0B98
#define GL_STENCIL_BACK_FUNC              0x8800
#define GL_STENCIL_BACK_FAIL              0x8801
#define GL_STENCIL_BACK_PASS_DEPTH_FAIL   0x8802
#define GL_STENCIL_BACK_PASS_DEPTH_PASS   0x8803
#define GL_STENCIL_BACK_REF               0x8CA3
#define GL_STENCIL_BACK_मानम्_MASK        0x8CA4
#define GL_STENCIL_BACK_WRITEMASK         0x8CA5
#define GL_VIEWPORT                       0x0BA2
#define GL_SCISSOR_BOX                    0x0C10
#define GL_COLOR_CLEAR_मानम्              0x0C22
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
#define GL_SAMPLE_COVERAGE_मानम्          0x80AA
#define GL_SAMPLE_COVERAGE_INVERT         0x80AB
#define GL_अङ्कः_COMPRESSED_TEXTURE_FORMATS 0x86A2
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
#define GL_SHADER_द्विमान_FORMATS          0x8DF8
#define GL_अङ्कः_SHADER_द्विमान_FORMATS      0x8DF9
#define GL_नीचः_FLOAT                      0x8DF0
#define GL_MEDIUM_FLOAT                   0x8DF1
#define GL_उच्चः_FLOAT                     0x8DF2
#define GL_नीचः_INT                        0x8DF3
#define GL_MEDIUM_INT                     0x8DF4
#define GL_उच्चः_INT                       0x8DF5
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
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLACTIVETEXTUREPROC) (GLenum texture);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLATTACHSHADERPROC) (GLuint program, GLuint shader);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBINDATTRIBLOCATIONPROC) (GLuint program, GLuint index, ध्रुव GLchar *name);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBINDFRAMEBUFFERPROC) (GLenum target, GLuint framebuffer);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBINDRENDERBUFFERPROC) (GLenum target, GLuint renderbuffer);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBINDTEXTUREPROC) (GLenum target, GLuint texture);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBLENDCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBLENDEQUATIONPROC) (GLenum mode);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEPROC) (GLenum modeRGB, GLenum modeAlpha);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBLENDFUNCPROC) (GLenum sfactor, GLenum dfactor);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEPROC) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBUFFERDATAPROC) (GLenum target, GLsizeiptr size, ध्रुव शून्य *data, GLenum usage);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBUFFERSUBDATAPROC) (GLenum target, GLintptr offset, GLsizeiptr size, ध्रुव शून्य *data);
प्रकारनिर्देश GLenum (GL_APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSPROC) (GLenum target);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCLEARPROC) (GLbitfield mask);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCLEARCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCLEARDEPTHFPROC) (GLfloat d);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCLEARSTENCILPROC) (GLint s);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCOLORMASKPROC) (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCOMPILESHADERPROC) (GLuint shader);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCOMPRESSEDTEXIMAGE2DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, ध्रुव शून्य *data);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, ध्रुव शून्य *data);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCOPYTEXIMAGE2DPROC) (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCOPYTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
प्रकारनिर्देश GLuint (GL_APIENTRYP PFNGLCREATEPROGRAMPROC) (शून्य);
प्रकारनिर्देश GLuint (GL_APIENTRYP PFNGLCREATESHADERPROC) (GLenum type);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCULLFACEPROC) (GLenum mode);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDELETEBUFFERSPROC) (GLsizei n, ध्रुव GLuint *buffers);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDELETEFRAMEBUFFERSPROC) (GLsizei n, ध्रुव GLuint *framebuffers);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDELETEPROGRAMPROC) (GLuint program);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDELETERENDERBUFFERSPROC) (GLsizei n, ध्रुव GLuint *renderbuffers);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDELETESHADERPROC) (GLuint shader);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDELETETEXTURESPROC) (GLsizei n, ध्रुव GLuint *textures);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDEPTHFUNCPROC) (GLenum func);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDEPTHMASKPROC) (GLboolean flag);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDEPTHRANGEFPROC) (GLfloat n, GLfloat f);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDETACHSHADERPROC) (GLuint program, GLuint shader);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDISABLEPROC) (GLenum cap);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint index);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWARRAYSPROC) (GLenum mode, GLint first, GLsizei गणनम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWELEMENTSPROC) (GLenum mode, GLsizei गणनम्, GLenum type, ध्रुव शून्य *indices);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLENABLEPROC) (GLenum cap);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint index);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFINISHPROC) (शून्य);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFLUSHPROC) (शून्य);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFERPROC) (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFRONTFACEPROC) (GLenum mode);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGENBUFFERSPROC) (GLsizei n, GLuint *buffers);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGENERATEMIPMAPPROC) (GLenum target);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGENFRAMEBUFFERSPROC) (GLsizei n, GLuint *framebuffers);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGENRENDERBUFFERSPROC) (GLsizei n, GLuint *renderbuffers);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGENTEXTURESPROC) (GLsizei n, GLuint *textures);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETACTIVEATTRIBPROC) (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETACTIVEUNIFORMPROC) (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETATTACHEDSHADERSPROC) (GLuint program, GLsizei max_गणनम्, GLsizei *गणनम्, GLuint *shaders);
प्रकारनिर्देश GLint (GL_APIENTRYP PFNGLGETATTRIBLOCATIONPROC) (GLuint program, ध्रुव GLchar *name);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETBOOLEANVPROC) (GLenum pname, GLboolean *data);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETBUFFERPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
प्रकारनिर्देश GLenum (GL_APIENTRYP PFNGLGETERRORPROC) (शून्य);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETFLOATVPROC) (GLenum pname, GLfloat *data);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) (GLenum target, GLenum attachment, GLenum pname, GLint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETINTEGERVPROC) (GLenum pname, GLint *data);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETPROGRAMIVPROC) (GLuint program, GLenum pname, GLint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETPROGRAMINFOLOGPROC) (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETSHADERPRECISIONFORMATPROC) (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETSHADERSOURCEPROC) (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source);
प्रकारनिर्देश ध्रुव GLubyte *(GL_APIENTRYP PFNGLGETSTRINGPROC) (GLenum name);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETTEXPARAMETERFVPROC) (GLenum target, GLenum pname, GLfloat *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETTEXPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETUNIFORMFVPROC) (GLuint program, GLint location, GLfloat *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETUNIFORMIVPROC) (GLuint program, GLint location, GLint *params);
प्रकारनिर्देश GLint (GL_APIENTRYP PFNGLGETUNIFORMLOCATIONPROC) (GLuint program, ध्रुव GLchar *name);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETVERTEXATTRIBFVPROC) (GLuint index, GLenum pname, GLfloat *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETVERTEXATTRIBIVPROC) (GLuint index, GLenum pname, GLint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETVERTEXATTRIBPOINTERVPROC) (GLuint index, GLenum pname, शून्य **pointer);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLHINTPROC) (GLenum target, GLenum mode);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLISBUFFERPROC) (GLuint buffer);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLISENABLEDPROC) (GLenum cap);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLISFRAMEBUFFERPROC) (GLuint framebuffer);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLISPROGRAMPROC) (GLuint program);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLISRENDERBUFFERPROC) (GLuint renderbuffer);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLISSHADERPROC) (GLuint shader);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLISTEXTUREPROC) (GLuint texture);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLLINEWIDTHPROC) (GLfloat width);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLLINKPROGRAMPROC) (GLuint program);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPIXELSTOREIPROC) (GLenum pname, GLint param);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPOLYGONOFFSETPROC) (GLfloat factor, GLfloat units);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLREADPIXELSPROC) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, शून्य *pixels);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLRELEASESHADERCOMPILERPROC) (शून्य);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEPROC) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSAMPLECOVERAGEPROC) (GLfloat मानम्, GLboolean invert);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSCISSORPROC) (GLint x, GLint y, GLsizei width, GLsizei height);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSHADERBINARYPROC) (GLsizei गणनम्, ध्रुव GLuint *shaders, GLenum द्विमान_Format, ध्रुव शून्य *द्विमान, GLsizei length);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei गणनम्, ध्रुव GLchar *ध्रुव*string, ध्रुव GLint *length);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSTENCILFUNCPROC) (GLenum func, GLint ref, GLuint mask);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSTENCILFUNCSEPARATEPROC) (GLenum face, GLenum func, GLint ref, GLuint mask);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSTENCILMASKPROC) (GLuint mask);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSTENCILMASKSEPARATEPROC) (GLenum face, GLuint mask);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSTENCILOPPROC) (GLenum fail, GLenum zfail, GLenum zpass);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSTENCILOPSEPARATEPROC) (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXIMAGE2DPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, ध्रुव शून्य *pixels);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXPARAMETERFPROC) (GLenum target, GLenum pname, GLfloat param);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXPARAMETERFVPROC) (GLenum target, GLenum pname, ध्रुव GLfloat *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXPARAMETERIPROC) (GLenum target, GLenum pname, GLint param);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXPARAMETERIVPROC) (GLenum target, GLenum pname, ध्रुव GLint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, ध्रुव शून्य *pixels);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORM1FPROC) (GLint location, GLfloat v0);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORM1FVPROC) (GLint location, GLsizei गणनम्, ध्रुव GLfloat *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORM1IPROC) (GLint location, GLint v0);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORM1IVPROC) (GLint location, GLsizei गणनम्, ध्रुव GLint *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORM2FPROC) (GLint location, GLfloat v0, GLfloat v1);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORM2FVPROC) (GLint location, GLsizei गणनम्, ध्रुव GLfloat *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORM2IPROC) (GLint location, GLint v0, GLint v1);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORM2IVPROC) (GLint location, GLsizei गणनम्, ध्रुव GLint *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORM3FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORM3FVPROC) (GLint location, GLsizei गणनम्, ध्रुव GLfloat *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORM3IPROC) (GLint location, GLint v0, GLint v1, GLint v2);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORM3IVPROC) (GLint location, GLsizei गणनम्, ध्रुव GLint *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORM4FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORM4FVPROC) (GLint location, GLsizei गणनम्, ध्रुव GLfloat *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORM4IPROC) (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORM4IVPROC) (GLint location, GLsizei गणनम्, ध्रुव GLint *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORMMATRIX2FVPROC) (GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORMMATRIX3FVPROC) (GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUSEPROGRAMPROC) (GLuint program);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLVALIDATEPROGRAMPROC) (GLuint program);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLVERTEXATTRIB1FPROC) (GLuint index, GLfloat x);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLVERTEXATTRIB1FVPROC) (GLuint index, ध्रुव GLfloat *v);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLVERTEXATTRIB2FPROC) (GLuint index, GLfloat x, GLfloat y);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLVERTEXATTRIB2FVPROC) (GLuint index, ध्रुव GLfloat *v);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLVERTEXATTRIB3FPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat z);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLVERTEXATTRIB3FVPROC) (GLuint index, ध्रुव GLfloat *v);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLVERTEXATTRIB4FPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLVERTEXATTRIB4FVPROC) (GLuint index, ध्रुव GLfloat *v);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, ध्रुव शून्य *pointer);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLVIEWPORTPROC) (GLint x, GLint y, GLsizei width, GLsizei height);
#जइ GL_GLES_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY glActiveTexture (GLenum texture);
GL_APICALL शून्य GL_APIENTRY glAttachShader (GLuint program, GLuint shader);
GL_APICALL शून्य GL_APIENTRY glBindAttribLocation (GLuint program, GLuint index, ध्रुव GLchar *name);
GL_APICALL शून्य GL_APIENTRY glBindBuffer (GLenum target, GLuint buffer);
GL_APICALL शून्य GL_APIENTRY glBindFramebuffer (GLenum target, GLuint framebuffer);
GL_APICALL शून्य GL_APIENTRY glBindRenderbuffer (GLenum target, GLuint renderbuffer);
GL_APICALL शून्य GL_APIENTRY glBindTexture (GLenum target, GLuint texture);
GL_APICALL शून्य GL_APIENTRY glBlendColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_APICALL शून्य GL_APIENTRY glBlendEquation (GLenum mode);
GL_APICALL शून्य GL_APIENTRY glBlendEquationSeparate (GLenum modeRGB, GLenum modeAlpha);
GL_APICALL शून्य GL_APIENTRY glBlendFunc (GLenum sfactor, GLenum dfactor);
GL_APICALL शून्य GL_APIENTRY glBlendFuncSeparate (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
GL_APICALL शून्य GL_APIENTRY glBufferData (GLenum target, GLsizeiptr size, ध्रुव शून्य *data, GLenum usage);
GL_APICALL शून्य GL_APIENTRY glBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, ध्रुव शून्य *data);
GL_APICALL GLenum GL_APIENTRY glCheckFramebufferStatus (GLenum target);
GL_APICALL शून्य GL_APIENTRY glClear (GLbitfield mask);
GL_APICALL शून्य GL_APIENTRY glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_APICALL शून्य GL_APIENTRY glClearDepthf (GLfloat d);
GL_APICALL शून्य GL_APIENTRY glClearStencil (GLint s);
GL_APICALL शून्य GL_APIENTRY glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
GL_APICALL शून्य GL_APIENTRY glCompileShader (GLuint shader);
GL_APICALL शून्य GL_APIENTRY glCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, ध्रुव शून्य *data);
GL_APICALL शून्य GL_APIENTRY glCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, ध्रुव शून्य *data);
GL_APICALL शून्य GL_APIENTRY glCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
GL_APICALL शून्य GL_APIENTRY glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
GL_APICALL GLuint GL_APIENTRY glCreateProgram (शून्य);
GL_APICALL GLuint GL_APIENTRY glCreateShader (GLenum type);
GL_APICALL शून्य GL_APIENTRY glCullFace (GLenum mode);
GL_APICALL शून्य GL_APIENTRY glDeleteBuffers (GLsizei n, ध्रुव GLuint *buffers);
GL_APICALL शून्य GL_APIENTRY glDeleteFramebuffers (GLsizei n, ध्रुव GLuint *framebuffers);
GL_APICALL शून्य GL_APIENTRY glDeleteProgram (GLuint program);
GL_APICALL शून्य GL_APIENTRY glDeleteRenderbuffers (GLsizei n, ध्रुव GLuint *renderbuffers);
GL_APICALL शून्य GL_APIENTRY glDeleteShader (GLuint shader);
GL_APICALL शून्य GL_APIENTRY glDeleteTextures (GLsizei n, ध्रुव GLuint *textures);
GL_APICALL शून्य GL_APIENTRY glDepthFunc (GLenum func);
GL_APICALL शून्य GL_APIENTRY glDepthMask (GLboolean flag);
GL_APICALL शून्य GL_APIENTRY glDepthRangef (GLfloat n, GLfloat f);
GL_APICALL शून्य GL_APIENTRY glDetachShader (GLuint program, GLuint shader);
GL_APICALL शून्य GL_APIENTRY glDisable (GLenum cap);
GL_APICALL शून्य GL_APIENTRY glDisableVertexAttribArray (GLuint index);
GL_APICALL शून्य GL_APIENTRY glDrawArrays (GLenum mode, GLint first, GLsizei गणनम्);
GL_APICALL शून्य GL_APIENTRY glDrawElements (GLenum mode, GLsizei गणनम्, GLenum type, ध्रुव शून्य *indices);
GL_APICALL शून्य GL_APIENTRY glEnable (GLenum cap);
GL_APICALL शून्य GL_APIENTRY glEnableVertexAttribArray (GLuint index);
GL_APICALL शून्य GL_APIENTRY glFinish (शून्य);
GL_APICALL शून्य GL_APIENTRY glFlush (शून्य);
GL_APICALL शून्य GL_APIENTRY glFramebufferRenderbuffer (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
GL_APICALL शून्य GL_APIENTRY glFramebufferTexture2D (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GL_APICALL शून्य GL_APIENTRY glFrontFace (GLenum mode);
GL_APICALL शून्य GL_APIENTRY glGenBuffers (GLsizei n, GLuint *buffers);
GL_APICALL शून्य GL_APIENTRY glGenerateMipmap (GLenum target);
GL_APICALL शून्य GL_APIENTRY glGenFramebuffers (GLsizei n, GLuint *framebuffers);
GL_APICALL शून्य GL_APIENTRY glGenRenderbuffers (GLsizei n, GLuint *renderbuffers);
GL_APICALL शून्य GL_APIENTRY glGenTextures (GLsizei n, GLuint *textures);
GL_APICALL शून्य GL_APIENTRY glGetActiveAttrib (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
GL_APICALL शून्य GL_APIENTRY glGetActiveUniform (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
GL_APICALL शून्य GL_APIENTRY glGetAttachedShaders (GLuint program, GLsizei max_गणनम्, GLsizei *गणनम्, GLuint *shaders);
GL_APICALL GLint GL_APIENTRY glGetAttribLocation (GLuint program, ध्रुव GLchar *name);
GL_APICALL शून्य GL_APIENTRY glGetBooleanv (GLenum pname, GLboolean *data);
GL_APICALL शून्य GL_APIENTRY glGetBufferParameteriv (GLenum target, GLenum pname, GLint *params);
GL_APICALL GLenum GL_APIENTRY glGetError (शून्य);
GL_APICALL शून्य GL_APIENTRY glGetFloatv (GLenum pname, GLfloat *data);
GL_APICALL शून्य GL_APIENTRY glGetFramebufferAttachmentParameteriv (GLenum target, GLenum attachment, GLenum pname, GLint *params);
GL_APICALL शून्य GL_APIENTRY glGetIntegerv (GLenum pname, GLint *data);
GL_APICALL शून्य GL_APIENTRY glGetProgramiv (GLuint program, GLenum pname, GLint *params);
GL_APICALL शून्य GL_APIENTRY glGetProgramInfoLog (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
GL_APICALL शून्य GL_APIENTRY glGetRenderbufferParameteriv (GLenum target, GLenum pname, GLint *params);
GL_APICALL शून्य GL_APIENTRY glGetShaderiv (GLuint shader, GLenum pname, GLint *params);
GL_APICALL शून्य GL_APIENTRY glGetShaderInfoLog (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
GL_APICALL शून्य GL_APIENTRY glGetShaderPrecisionFormat (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
GL_APICALL शून्य GL_APIENTRY glGetShaderSource (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source);
GL_APICALL ध्रुव GLubyte *GL_APIENTRY glGetString (GLenum name);
GL_APICALL शून्य GL_APIENTRY glGetTexParameterfv (GLenum target, GLenum pname, GLfloat *params);
GL_APICALL शून्य GL_APIENTRY glGetTexParameteriv (GLenum target, GLenum pname, GLint *params);
GL_APICALL शून्य GL_APIENTRY glGetUniformfv (GLuint program, GLint location, GLfloat *params);
GL_APICALL शून्य GL_APIENTRY glGetUniformiv (GLuint program, GLint location, GLint *params);
GL_APICALL GLint GL_APIENTRY glGetUniformLocation (GLuint program, ध्रुव GLchar *name);
GL_APICALL शून्य GL_APIENTRY glGetVertexAttribfv (GLuint index, GLenum pname, GLfloat *params);
GL_APICALL शून्य GL_APIENTRY glGetVertexAttribiv (GLuint index, GLenum pname, GLint *params);
GL_APICALL शून्य GL_APIENTRY glGetVertexAttribPointerv (GLuint index, GLenum pname, शून्य **pointer);
GL_APICALL शून्य GL_APIENTRY glHint (GLenum target, GLenum mode);
GL_APICALL GLboolean GL_APIENTRY glIsBuffer (GLuint buffer);
GL_APICALL GLboolean GL_APIENTRY glIsEnabled (GLenum cap);
GL_APICALL GLboolean GL_APIENTRY glIsFramebuffer (GLuint framebuffer);
GL_APICALL GLboolean GL_APIENTRY glIsProgram (GLuint program);
GL_APICALL GLboolean GL_APIENTRY glIsRenderbuffer (GLuint renderbuffer);
GL_APICALL GLboolean GL_APIENTRY glIsShader (GLuint shader);
GL_APICALL GLboolean GL_APIENTRY glIsTexture (GLuint texture);
GL_APICALL शून्य GL_APIENTRY gl_पङ्क्तिः_Width (GLfloat width);
GL_APICALL शून्य GL_APIENTRY glLinkProgram (GLuint program);
GL_APICALL शून्य GL_APIENTRY glPixelStorei (GLenum pname, GLint param);
GL_APICALL शून्य GL_APIENTRY glPolygonOffset (GLfloat factor, GLfloat units);
GL_APICALL शून्य GL_APIENTRY glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, शून्य *pixels);
GL_APICALL शून्य GL_APIENTRY glReleaseShaderCompiler (शून्य);
GL_APICALL शून्य GL_APIENTRY glRenderbufferStorage (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
GL_APICALL शून्य GL_APIENTRY glSampleCoverage (GLfloat मानम्, GLboolean invert);
GL_APICALL शून्य GL_APIENTRY glScissor (GLint x, GLint y, GLsizei width, GLsizei height);
GL_APICALL शून्य GL_APIENTRY gl_Shader_द्विमान (GLsizei गणनम्, ध्रुव GLuint *shaders, GLenum द्विमान_Format, ध्रुव शून्य *द्विमान, GLsizei length);
GL_APICALL शून्य GL_APIENTRY glShaderSource (GLuint shader, GLsizei गणनम्, ध्रुव GLchar *ध्रुव*string, ध्रुव GLint *length);
GL_APICALL शून्य GL_APIENTRY glStencilFunc (GLenum func, GLint ref, GLuint mask);
GL_APICALL शून्य GL_APIENTRY glStencilFuncSeparate (GLenum face, GLenum func, GLint ref, GLuint mask);
GL_APICALL शून्य GL_APIENTRY glStencilMask (GLuint mask);
GL_APICALL शून्य GL_APIENTRY glStencilMaskSeparate (GLenum face, GLuint mask);
GL_APICALL शून्य GL_APIENTRY glStencilOp (GLenum fail, GLenum zfail, GLenum zpass);
GL_APICALL शून्य GL_APIENTRY glStencilOpSeparate (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
GL_APICALL शून्य GL_APIENTRY glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, ध्रुव शून्य *pixels);
GL_APICALL शून्य GL_APIENTRY glTexParameterf (GLenum target, GLenum pname, GLfloat param);
GL_APICALL शून्य GL_APIENTRY glTexParameterfv (GLenum target, GLenum pname, ध्रुव GLfloat *params);
GL_APICALL शून्य GL_APIENTRY glTexParameteri (GLenum target, GLenum pname, GLint param);
GL_APICALL शून्य GL_APIENTRY glTexParameteriv (GLenum target, GLenum pname, ध्रुव GLint *params);
GL_APICALL शून्य GL_APIENTRY glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, ध्रुव शून्य *pixels);
GL_APICALL शून्य GL_APIENTRY glUniform1f (GLint location, GLfloat v0);
GL_APICALL शून्य GL_APIENTRY glUniform1fv (GLint location, GLsizei गणनम्, ध्रुव GLfloat *मानम्);
GL_APICALL शून्य GL_APIENTRY glUniform1i (GLint location, GLint v0);
GL_APICALL शून्य GL_APIENTRY glUniform1iv (GLint location, GLsizei गणनम्, ध्रुव GLint *मानम्);
GL_APICALL शून्य GL_APIENTRY glUniform2f (GLint location, GLfloat v0, GLfloat v1);
GL_APICALL शून्य GL_APIENTRY glUniform2fv (GLint location, GLsizei गणनम्, ध्रुव GLfloat *मानम्);
GL_APICALL शून्य GL_APIENTRY glUniform2i (GLint location, GLint v0, GLint v1);
GL_APICALL शून्य GL_APIENTRY glUniform2iv (GLint location, GLsizei गणनम्, ध्रुव GLint *मानम्);
GL_APICALL शून्य GL_APIENTRY glUniform3f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
GL_APICALL शून्य GL_APIENTRY glUniform3fv (GLint location, GLsizei गणनम्, ध्रुव GLfloat *मानम्);
GL_APICALL शून्य GL_APIENTRY glUniform3i (GLint location, GLint v0, GLint v1, GLint v2);
GL_APICALL शून्य GL_APIENTRY glUniform3iv (GLint location, GLsizei गणनम्, ध्रुव GLint *मानम्);
GL_APICALL शून्य GL_APIENTRY glUniform4f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
GL_APICALL शून्य GL_APIENTRY glUniform4fv (GLint location, GLsizei गणनम्, ध्रुव GLfloat *मानम्);
GL_APICALL शून्य GL_APIENTRY glUniform4i (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
GL_APICALL शून्य GL_APIENTRY glUniform4iv (GLint location, GLsizei गणनम्, ध्रुव GLint *मानम्);
GL_APICALL शून्य GL_APIENTRY glUniformMatrix2fv (GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
GL_APICALL शून्य GL_APIENTRY glUniformMatrix3fv (GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
GL_APICALL शून्य GL_APIENTRY glUniformMatrix4fv (GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
GL_APICALL शून्य GL_APIENTRY glUseProgram (GLuint program);
GL_APICALL शून्य GL_APIENTRY glValidateProgram (GLuint program);
GL_APICALL शून्य GL_APIENTRY glVertexAttrib1f (GLuint index, GLfloat x);
GL_APICALL शून्य GL_APIENTRY glVertexAttrib1fv (GLuint index, ध्रुव GLfloat *v);
GL_APICALL शून्य GL_APIENTRY glVertexAttrib2f (GLuint index, GLfloat x, GLfloat y);
GL_APICALL शून्य GL_APIENTRY glVertexAttrib2fv (GLuint index, ध्रुव GLfloat *v);
GL_APICALL शून्य GL_APIENTRY glVertexAttrib3f (GLuint index, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL शून्य GL_APIENTRY glVertexAttrib3fv (GLuint index, ध्रुव GLfloat *v);
GL_APICALL शून्य GL_APIENTRY glVertexAttrib4f (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
GL_APICALL शून्य GL_APIENTRY glVertexAttrib4fv (GLuint index, ध्रुव GLfloat *v);
GL_APICALL शून्य GL_APIENTRY glVertexAttribPointer (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, ध्रुव शून्य *pointer);
GL_APICALL शून्य GL_APIENTRY glViewport (GLint x, GLint y, GLsizei width, GLsizei height);
#endif
#endif /* GL_ES_VERSION_2_0 */

#ifdef __cplusplus
}
#endif

#endif
