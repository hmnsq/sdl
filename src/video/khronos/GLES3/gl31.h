#ifndef __gles2_gl31_h_
#define __gles2_gl31_h_ 1

#ifdef __cplusplus
ବାହ୍ୟ "C" {
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

#ଅନ୍ତର୍ଭାଵ <GLES3/gl3platform.h>

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
 * Versions considered: 2\.[0-9]|3\.[01]
 * Versions emitted: .*
 * Default extensions included: None
 * Additional extensions included: _nomatch_^
 * Extensions removed: _nomatch_^
 */

#ifndef GL_ES_VERSION_2_0
#define GL_ES_VERSION_2_0 1
#ଅନ୍ତର୍ଭାଵ <KHR/khrplatform.h>
ପ୍ରକାରବ୍ୟାଖ୍ୟା khronos_int8_t GLbyte;
ପ୍ରକାରବ୍ୟାଖ୍ୟା khronos_float_t GLclampf;
ପ୍ରକାରବ୍ୟାଖ୍ୟା khronos_int32_t GLfixed;
ପ୍ରକାରବ୍ୟାଖ୍ୟା khronos_int16_t GLshort;
ପ୍ରକାରବ୍ୟାଖ୍ୟା khronos_uint16_t GLushort;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ GLvoid;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା __GLsync *GLsync;
ପ୍ରକାରବ୍ୟାଖ୍ୟା khronos_int64_t GLint64;
ପ୍ରକାରବ୍ୟାଖ୍ୟା khronos_uint64_t GLuint64;
ପ୍ରକାରବ୍ୟାଖ୍ୟା unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା GLenum;
ପ୍ରକାରବ୍ୟାଖ୍ୟା unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା GLuint;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଅକ୍ଷର GLchar;
ପ୍ରକାରବ୍ୟାଖ୍ୟା khronos_float_t GLfloat;
ପ୍ରକାରବ୍ୟାଖ୍ୟା khronos_ssize_t GLsizeiptr;
ପ୍ରକାରବ୍ୟାଖ୍ୟା khronos_intptr_t GLintptr;
ପ୍ରକାରବ୍ୟାଖ୍ୟା unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା GLbitfield;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ପୂର୍ଣ୍ଣସଂଖ୍ୟା GLint;
ପ୍ରକାରବ୍ୟାଖ୍ୟା unsigned ଅକ୍ଷର GLboolean;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ପୂର୍ଣ୍ଣସଂଖ୍ୟା GLsizei;
ପ୍ରକାରବ୍ୟାଖ୍ୟା khronos_uint8_t GLubyte;
#define GL_DEPTH_BUFFER_BIT               0x00000100
#define GL_STENCIL_BUFFER_BIT             0x00000400
#define GL_COLOR_BUFFER_BIT               0x00004000
#define GL_FALSE                          0
#define GL_TRUE                           1
#define GL_POINTS                         0x0000
#define GL_ଧାଡ଼ିଗୁଡ଼ିକ                          0x0001
#define GL_ଧାଡ଼ି_LOOP                      0x0002
#define GL_ଧାଡ଼ି_STRIP                     0x0003
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
#define GL_INVALID_ମୂଲ୍ୟ                  0x0501
#define GL_INVALID_OPERATION              0x0502
#define GL_OUT_OF_MEMORY                  0x0505
#define GL_CW                             0x0900
#define GL_CCW                            0x0901
#define GL_ଧାଡ଼ି_WIDTH                     0x0B21
#define GL_ALIASED_POINT_SIZE_RANGE       0x846D
#define GL_ALIASED_ଧାଡ଼ି_WIDTH_RANGE       0x846E
#define GL_CULL_FACE_MODE                 0x0B45
#define GL_FRONT_FACE                     0x0B46
#define GL_DEPTH_RANGE                    0x0B70
#define GL_DEPTH_WRITEMASK                0x0B72
#define GL_DEPTH_CLEAR_ମୂଲ୍ୟ              0x0B73
#define GL_DEPTH_FUNC                     0x0B74
#define GL_STENCIL_CLEAR_ମୂଲ୍ୟ            0x0B91
#define GL_STENCIL_FUNC                   0x0B92
#define GL_STENCIL_FAIL                   0x0B94
#define GL_STENCIL_PASS_DEPTH_FAIL        0x0B95
#define GL_STENCIL_PASS_DEPTH_PASS        0x0B96
#define GL_STENCIL_REF                    0x0B97
#define GL_STENCIL_ମୂଲ୍ୟ_MASK             0x0B93
#define GL_STENCIL_WRITEMASK              0x0B98
#define GL_STENCIL_BACK_FUNC              0x8800
#define GL_STENCIL_BACK_FAIL              0x8801
#define GL_STENCIL_BACK_PASS_DEPTH_FAIL   0x8802
#define GL_STENCIL_BACK_PASS_DEPTH_PASS   0x8803
#define GL_STENCIL_BACK_REF               0x8CA3
#define GL_STENCIL_BACK_ମୂଲ୍ୟ_MASK        0x8CA4
#define GL_STENCIL_BACK_WRITEMASK         0x8CA5
#define GL_VIEWPORT                       0x0BA2
#define GL_SCISSOR_BOX                    0x0C10
#define GL_COLOR_CLEAR_ମୂଲ୍ୟ              0x0C22
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
#define GL_SAMPLE_COVERAGE_ମୂଲ୍ୟ          0x80AA
#define GL_SAMPLE_COVERAGE_INVERT         0x80AB
#define GL_ଅଙ୍କ_COMPRESSED_TEXTURE_FORMATS 0x86A2
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
#define GL_SHADER_ଦ୍ୱିମିକ_FORMATS          0x8DF8
#define GL_ଅଙ୍କ_SHADER_ଦ୍ୱିମିକ_FORMATS      0x8DF9
#define GL_ତଳ_FLOAT                      0x8DF0
#define GL_MEDIUM_FLOAT                   0x8DF1
#define GL_ଉପର_FLOAT                     0x8DF2
#define GL_ତଳ_INT                        0x8DF3
#define GL_MEDIUM_INT                     0x8DF4
#define GL_ଉପର_INT                       0x8DF5
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
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLACTIVETEXTUREPROC) (GLenum texture);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLATTACHSHADERPROC) (GLuint program, GLuint shader);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLBINDATTRIBLOCATIONPROC) (GLuint program, GLuint index, ଅଚଳ GLchar *name);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLBINDFRAMEBUFFERPROC) (GLenum target, GLuint framebuffer);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLBINDRENDERBUFFERPROC) (GLenum target, GLuint renderbuffer);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLBINDTEXTUREPROC) (GLenum target, GLuint texture);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLBLENDCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLBLENDEQUATIONPROC) (GLenum mode);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEPROC) (GLenum modeRGB, GLenum modeAlpha);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLBLENDFUNCPROC) (GLenum sfactor, GLenum dfactor);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEPROC) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLBUFFERDATAPROC) (GLenum target, GLsizeiptr size, ଅଚଳ ଶୂନ୍ୟ *data, GLenum usage);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLBUFFERSUBDATAPROC) (GLenum target, GLintptr offset, GLsizeiptr size, ଅଚଳ ଶୂନ୍ୟ *data);
ପ୍ରକାରବ୍ୟାଖ୍ୟା GLenum (GL_APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSPROC) (GLenum target);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLCLEARPROC) (GLbitfield mask);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLCLEARCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLCLEARDEPTHFPROC) (GLfloat d);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLCLEARSTENCILPROC) (GLint s);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLCOLORMASKPROC) (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLCOMPILESHADERPROC) (GLuint shader);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLCOMPRESSEDTEXIMAGE2DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, ଅଚଳ ଶୂନ୍ୟ *data);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, ଅଚଳ ଶୂନ୍ୟ *data);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLCOPYTEXIMAGE2DPROC) (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLCOPYTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
ପ୍ରକାରବ୍ୟାଖ୍ୟା GLuint (GL_APIENTRYP PFNGLCREATEPROGRAMPROC) (ଶୂନ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା GLuint (GL_APIENTRYP PFNGLCREATESHADERPROC) (GLenum type);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLCULLFACEPROC) (GLenum mode);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLDELETEBUFFERSPROC) (GLsizei n, ଅଚଳ GLuint *buffers);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLDELETEFRAMEBUFFERSPROC) (GLsizei n, ଅଚଳ GLuint *framebuffers);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLDELETEPROGRAMPROC) (GLuint program);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLDELETERENDERBUFFERSPROC) (GLsizei n, ଅଚଳ GLuint *renderbuffers);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLDELETESHADERPROC) (GLuint shader);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLDELETETEXTURESPROC) (GLsizei n, ଅଚଳ GLuint *textures);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLDEPTHFUNCPROC) (GLenum func);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLDEPTHMASKPROC) (GLboolean flag);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLDEPTHRANGEFPROC) (GLfloat n, GLfloat f);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLDETACHSHADERPROC) (GLuint program, GLuint shader);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLDISABLEPROC) (GLenum cap);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint index);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLDRAWARRAYSPROC) (GLenum mode, GLint first, GLsizei ଗଣନା_2);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLDRAWELEMENTSPROC) (GLenum mode, GLsizei ଗଣନା_2, GLenum type, ଅଚଳ ଶୂନ୍ୟ *indices);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLENABLEPROC) (GLenum cap);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint index);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLFINISHPROC) (ଶୂନ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLFLUSHPROC) (ଶୂନ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFERPROC) (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLFRONTFACEPROC) (GLenum mode);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGENBUFFERSPROC) (GLsizei n, GLuint *buffers);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGENERATEMIPMAPPROC) (GLenum target);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGENFRAMEBUFFERSPROC) (GLsizei n, GLuint *framebuffers);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGENRENDERBUFFERSPROC) (GLsizei n, GLuint *renderbuffers);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGENTEXTURESPROC) (GLsizei n, GLuint *textures);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETACTIVEATTRIBPROC) (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETACTIVEUNIFORMPROC) (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETATTACHEDSHADERSPROC) (GLuint program, GLsizei max_ଗଣନା, GLsizei *ଗଣନା_2, GLuint *shaders);
ପ୍ରକାରବ୍ୟାଖ୍ୟା GLint (GL_APIENTRYP PFNGLGETATTRIBLOCATIONPROC) (GLuint program, ଅଚଳ GLchar *name);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETBOOLEANVPROC) (GLenum pname, GLboolean *data);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETBUFFERPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
ପ୍ରକାରବ୍ୟାଖ୍ୟା GLenum (GL_APIENTRYP PFNGLGETERRORPROC) (ଶୂନ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETFLOATVPROC) (GLenum pname, GLfloat *data);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) (GLenum target, GLenum attachment, GLenum pname, GLint *params);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETINTEGERVPROC) (GLenum pname, GLint *data);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETPROGRAMIVPROC) (GLuint program, GLenum pname, GLint *params);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETPROGRAMINFOLOGPROC) (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint *params);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETSHADERPRECISIONFORMATPROC) (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETSHADERSOURCEPROC) (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଅଚଳ GLubyte *(GL_APIENTRYP PFNGLGETSTRINGPROC) (GLenum name);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETTEXPARAMETERFVPROC) (GLenum target, GLenum pname, GLfloat *params);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETTEXPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETUNIFORMFVPROC) (GLuint program, GLint location, GLfloat *params);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETUNIFORMIVPROC) (GLuint program, GLint location, GLint *params);
ପ୍ରକାରବ୍ୟାଖ୍ୟା GLint (GL_APIENTRYP PFNGLGETUNIFORMLOCATIONPROC) (GLuint program, ଅଚଳ GLchar *name);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETVERTEXATTRIBFVPROC) (GLuint index, GLenum pname, GLfloat *params);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETVERTEXATTRIBIVPROC) (GLuint index, GLenum pname, GLint *params);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETVERTEXATTRIBPOINTERVPROC) (GLuint index, GLenum pname, ଶୂନ୍ୟ **pointer);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLHINTPROC) (GLenum target, GLenum mode);
ପ୍ରକାରବ୍ୟାଖ୍ୟା GLboolean (GL_APIENTRYP PFNGLISBUFFERPROC) (GLuint buffer);
ପ୍ରକାରବ୍ୟାଖ୍ୟା GLboolean (GL_APIENTRYP PFNGLISENABLEDPROC) (GLenum cap);
ପ୍ରକାରବ୍ୟାଖ୍ୟା GLboolean (GL_APIENTRYP PFNGLISFRAMEBUFFERPROC) (GLuint framebuffer);
ପ୍ରକାରବ୍ୟାଖ୍ୟା GLboolean (GL_APIENTRYP PFNGLISPROGRAMPROC) (GLuint program);
ପ୍ରକାରବ୍ୟାଖ୍ୟା GLboolean (GL_APIENTRYP PFNGLISRENDERBUFFERPROC) (GLuint renderbuffer);
ପ୍ରକାରବ୍ୟାଖ୍ୟା GLboolean (GL_APIENTRYP PFNGLISSHADERPROC) (GLuint shader);
ପ୍ରକାରବ୍ୟାଖ୍ୟା GLboolean (GL_APIENTRYP PFNGLISTEXTUREPROC) (GLuint texture);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLLINEWIDTHPROC) (GLfloat width);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLLINKPROGRAMPROC) (GLuint program);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPIXELSTOREIPROC) (GLenum pname, GLint param);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPOLYGONOFFSETPROC) (GLfloat factor, GLfloat units);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLREADPIXELSPROC) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, ଶୂନ୍ୟ *pixels);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLRELEASESHADERCOMPILERPROC) (ଶୂନ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEPROC) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLSAMPLECOVERAGEPROC) (GLfloat ମୂଲ୍ୟ, GLboolean invert);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLSCISSORPROC) (GLint x, GLint y, GLsizei width, GLsizei height);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLSHADERBINARYPROC) (GLsizei ଗଣନା_2, ଅଚଳ GLuint *shaders, GLenum ଦ୍ୱିମିକ_Format, ଅଚଳ ଶୂନ୍ୟ *ଦ୍ୱିମିକ, GLsizei length);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei ଗଣନା_2, ଅଚଳ GLchar *ଅଚଳ*string, ଅଚଳ GLint *length);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLSTENCILFUNCPROC) (GLenum func, GLint ref, GLuint mask);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLSTENCILFUNCSEPARATEPROC) (GLenum face, GLenum func, GLint ref, GLuint mask);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLSTENCILMASKPROC) (GLuint mask);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLSTENCILMASKSEPARATEPROC) (GLenum face, GLuint mask);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLSTENCILOPPROC) (GLenum fail, GLenum zfail, GLenum zpass);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLSTENCILOPSEPARATEPROC) (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLTEXIMAGE2DPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, ଅଚଳ ଶୂନ୍ୟ *pixels);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLTEXPARAMETERFPROC) (GLenum target, GLenum pname, GLfloat param);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLTEXPARAMETERFVPROC) (GLenum target, GLenum pname, ଅଚଳ GLfloat *params);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLTEXPARAMETERIPROC) (GLenum target, GLenum pname, GLint param);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLTEXPARAMETERIVPROC) (GLenum target, GLenum pname, ଅଚଳ GLint *params);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, ଅଚଳ ଶୂନ୍ୟ *pixels);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUNIFORM1FPROC) (GLint location, GLfloat v0);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUNIFORM1FVPROC) (GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUNIFORM1IPROC) (GLint location, GLint v0);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUNIFORM1IVPROC) (GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLint *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUNIFORM2FPROC) (GLint location, GLfloat v0, GLfloat v1);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUNIFORM2FVPROC) (GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUNIFORM2IPROC) (GLint location, GLint v0, GLint v1);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUNIFORM2IVPROC) (GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLint *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUNIFORM3FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUNIFORM3FVPROC) (GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUNIFORM3IPROC) (GLint location, GLint v0, GLint v1, GLint v2);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUNIFORM3IVPROC) (GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLint *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUNIFORM4FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUNIFORM4FVPROC) (GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUNIFORM4IPROC) (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUNIFORM4IVPROC) (GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLint *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUNIFORMMATRIX2FVPROC) (GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUNIFORMMATRIX3FVPROC) (GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUSEPROGRAMPROC) (GLuint program);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLVALIDATEPROGRAMPROC) (GLuint program);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLVERTEXATTRIB1FPROC) (GLuint index, GLfloat x);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLVERTEXATTRIB1FVPROC) (GLuint index, ଅଚଳ GLfloat *v);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLVERTEXATTRIB2FPROC) (GLuint index, GLfloat x, GLfloat y);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLVERTEXATTRIB2FVPROC) (GLuint index, ଅଚଳ GLfloat *v);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLVERTEXATTRIB3FPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat z);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLVERTEXATTRIB3FVPROC) (GLuint index, ଅଚଳ GLfloat *v);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLVERTEXATTRIB4FPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLVERTEXATTRIB4FVPROC) (GLuint index, ଅଚଳ GLfloat *v);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, ଅଚଳ ଶୂନ୍ୟ *pointer);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLVIEWPORTPROC) (GLint x, GLint y, GLsizei width, GLsizei height);
#ଯଦି GL_GLES_PROTOTYPES
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glActiveTexture (GLenum texture);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glAttachShader (GLuint program, GLuint shader);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glBindAttribLocation (GLuint program, GLuint index, ଅଚଳ GLchar *name);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glBindBuffer (GLenum target, GLuint buffer);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glBindFramebuffer (GLenum target, GLuint framebuffer);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glBindRenderbuffer (GLenum target, GLuint renderbuffer);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glBindTexture (GLenum target, GLuint texture);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glBlendColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glBlendEquation (GLenum mode);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glBlendEquationSeparate (GLenum modeRGB, GLenum modeAlpha);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glBlendFunc (GLenum sfactor, GLenum dfactor);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glBlendFuncSeparate (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glBufferData (GLenum target, GLsizeiptr size, ଅଚଳ ଶୂନ୍ୟ *data, GLenum usage);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, ଅଚଳ ଶୂନ୍ୟ *data);
GL_APICALL GLenum GL_APIENTRY glCheckFramebufferStatus (GLenum target);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glClear (GLbitfield mask);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glClearDepthf (GLfloat d);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glClearStencil (GLint s);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glCompileShader (GLuint shader);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, ଅଚଳ ଶୂନ୍ୟ *data);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, ଅଚଳ ଶୂନ୍ୟ *data);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
GL_APICALL GLuint GL_APIENTRY glCreateProgram (ଶୂନ୍ୟ);
GL_APICALL GLuint GL_APIENTRY glCreateShader (GLenum type);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glCullFace (GLenum mode);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glDeleteBuffers (GLsizei n, ଅଚଳ GLuint *buffers);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glDeleteFramebuffers (GLsizei n, ଅଚଳ GLuint *framebuffers);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glDeleteProgram (GLuint program);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glDeleteRenderbuffers (GLsizei n, ଅଚଳ GLuint *renderbuffers);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glDeleteShader (GLuint shader);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glDeleteTextures (GLsizei n, ଅଚଳ GLuint *textures);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glDepthFunc (GLenum func);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glDepthMask (GLboolean flag);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glDepthRangef (GLfloat n, GLfloat f);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glDetachShader (GLuint program, GLuint shader);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glDisable (GLenum cap);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glDisableVertexAttribArray (GLuint index);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glDrawArrays (GLenum mode, GLint first, GLsizei ଗଣନା_2);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glDrawElements (GLenum mode, GLsizei ଗଣନା_2, GLenum type, ଅଚଳ ଶୂନ୍ୟ *indices);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glEnable (GLenum cap);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glEnableVertexAttribArray (GLuint index);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glFinish (ଶୂନ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glFlush (ଶୂନ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glFramebufferRenderbuffer (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glFramebufferTexture2D (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glFrontFace (GLenum mode);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGenBuffers (GLsizei n, GLuint *buffers);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGenerateMipmap (GLenum target);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGenFramebuffers (GLsizei n, GLuint *framebuffers);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGenRenderbuffers (GLsizei n, GLuint *renderbuffers);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGenTextures (GLsizei n, GLuint *textures);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetActiveAttrib (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetActiveUniform (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetAttachedShaders (GLuint program, GLsizei max_ଗଣନା, GLsizei *ଗଣନା_2, GLuint *shaders);
GL_APICALL GLint GL_APIENTRY glGetAttribLocation (GLuint program, ଅଚଳ GLchar *name);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetBooleanv (GLenum pname, GLboolean *data);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetBufferParameteriv (GLenum target, GLenum pname, GLint *params);
GL_APICALL GLenum GL_APIENTRY glGetError (ଶୂନ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetFloatv (GLenum pname, GLfloat *data);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetFramebufferAttachmentParameteriv (GLenum target, GLenum attachment, GLenum pname, GLint *params);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetIntegerv (GLenum pname, GLint *data);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetProgramiv (GLuint program, GLenum pname, GLint *params);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetProgramInfoLog (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetRenderbufferParameteriv (GLenum target, GLenum pname, GLint *params);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetShaderiv (GLuint shader, GLenum pname, GLint *params);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetShaderInfoLog (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetShaderPrecisionFormat (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetShaderSource (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source);
GL_APICALL ଅଚଳ GLubyte *GL_APIENTRY glGetString (GLenum name);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetTexParameterfv (GLenum target, GLenum pname, GLfloat *params);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetTexParameteriv (GLenum target, GLenum pname, GLint *params);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetUniformfv (GLuint program, GLint location, GLfloat *params);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetUniformiv (GLuint program, GLint location, GLint *params);
GL_APICALL GLint GL_APIENTRY glGetUniformLocation (GLuint program, ଅଚଳ GLchar *name);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetVertexAttribfv (GLuint index, GLenum pname, GLfloat *params);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetVertexAttribiv (GLuint index, GLenum pname, GLint *params);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetVertexAttribPointerv (GLuint index, GLenum pname, ଶୂନ୍ୟ **pointer);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glHint (GLenum target, GLenum mode);
GL_APICALL GLboolean GL_APIENTRY glIsBuffer (GLuint buffer);
GL_APICALL GLboolean GL_APIENTRY glIsEnabled (GLenum cap);
GL_APICALL GLboolean GL_APIENTRY glIsFramebuffer (GLuint framebuffer);
GL_APICALL GLboolean GL_APIENTRY glIsProgram (GLuint program);
GL_APICALL GLboolean GL_APIENTRY glIsRenderbuffer (GLuint renderbuffer);
GL_APICALL GLboolean GL_APIENTRY glIsShader (GLuint shader);
GL_APICALL GLboolean GL_APIENTRY glIsTexture (GLuint texture);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY gl_ଧାଡ଼ି_Width (GLfloat width);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glLinkProgram (GLuint program);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glPixelStorei (GLenum pname, GLint param);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glPolygonOffset (GLfloat factor, GLfloat units);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, ଶୂନ୍ୟ *pixels);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glReleaseShaderCompiler (ଶୂନ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glRenderbufferStorage (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glSampleCoverage (GLfloat ମୂଲ୍ୟ, GLboolean invert);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glScissor (GLint x, GLint y, GLsizei width, GLsizei height);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY gl_Shader_ଦ୍ୱିମିକ (GLsizei ଗଣନା_2, ଅଚଳ GLuint *shaders, GLenum ଦ୍ୱିମିକ_Format, ଅଚଳ ଶୂନ୍ୟ *ଦ୍ୱିମିକ, GLsizei length);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glShaderSource (GLuint shader, GLsizei ଗଣନା_2, ଅଚଳ GLchar *ଅଚଳ*string, ଅଚଳ GLint *length);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glStencilFunc (GLenum func, GLint ref, GLuint mask);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glStencilFuncSeparate (GLenum face, GLenum func, GLint ref, GLuint mask);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glStencilMask (GLuint mask);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glStencilMaskSeparate (GLenum face, GLuint mask);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glStencilOp (GLenum fail, GLenum zfail, GLenum zpass);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glStencilOpSeparate (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, ଅଚଳ ଶୂନ୍ୟ *pixels);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glTexParameterf (GLenum target, GLenum pname, GLfloat param);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glTexParameterfv (GLenum target, GLenum pname, ଅଚଳ GLfloat *params);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glTexParameteri (GLenum target, GLenum pname, GLint param);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glTexParameteriv (GLenum target, GLenum pname, ଅଚଳ GLint *params);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, ଅଚଳ ଶୂନ୍ୟ *pixels);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUniform1f (GLint location, GLfloat v0);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUniform1fv (GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUniform1i (GLint location, GLint v0);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUniform1iv (GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLint *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUniform2f (GLint location, GLfloat v0, GLfloat v1);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUniform2fv (GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUniform2i (GLint location, GLint v0, GLint v1);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUniform2iv (GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLint *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUniform3f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUniform3fv (GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUniform3i (GLint location, GLint v0, GLint v1, GLint v2);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUniform3iv (GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLint *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUniform4f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUniform4fv (GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUniform4i (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUniform4iv (GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLint *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUniformMatrix2fv (GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUniformMatrix3fv (GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUniformMatrix4fv (GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUseProgram (GLuint program);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glValidateProgram (GLuint program);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glVertexAttrib1f (GLuint index, GLfloat x);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glVertexAttrib1fv (GLuint index, ଅଚଳ GLfloat *v);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glVertexAttrib2f (GLuint index, GLfloat x, GLfloat y);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glVertexAttrib2fv (GLuint index, ଅଚଳ GLfloat *v);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glVertexAttrib3f (GLuint index, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glVertexAttrib3fv (GLuint index, ଅଚଳ GLfloat *v);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glVertexAttrib4f (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glVertexAttrib4fv (GLuint index, ଅଚଳ GLfloat *v);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glVertexAttribPointer (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, ଅଚଳ ଶୂନ୍ୟ *pointer);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glViewport (GLint x, GLint y, GLsizei width, GLsizei height);
#endif
#endif /* GL_ES_VERSION_2_0 */

#ifndef GL_ES_VERSION_3_0
#define GL_ES_VERSION_3_0 1
ପ୍ରକାରବ୍ୟାଖ୍ୟା khronos_uint16_t GLhalf;
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
#define GL_ଅଙ୍କ_EXTENSIONS                 0x821D
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
#define GL_MAX_FRAGMENT_ନିବେଶ_COMPONENTS  0x9125
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
#define GL_VERTEX_ATTRIB_ARRAY_ଭାଜକ    0x88FE
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
#define GL_PROGRAM_ଦ୍ୱିମିକ_RETRIEVABLE_HINT 0x8257
#define GL_PROGRAM_ଦ୍ୱିମିକ_LENGTH          0x8741
#define GL_ଅଙ୍କ_PROGRAM_ଦ୍ୱିମିକ_FORMATS     0x87FE
#define GL_PROGRAM_ଦ୍ୱିମିକ_FORMATS         0x87FF
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
#define GL_ଅଙ୍କ_SAMPLE_COUNTS              0x9380
#define GL_TEXTURE_IMMUTABLE_LEVELS       0x82DF
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLREADBUFFERPROC) (GLenum src);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLDRAWRANGEELEMENTSPROC) (GLenum mode, GLuint start, GLuint end, GLsizei ଗଣନା_2, GLenum type, ଅଚଳ ଶୂନ୍ୟ *indices);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLTEXIMAGE3DPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, ଅଚଳ ଶୂନ୍ୟ *pixels);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, ଅଚଳ ଶୂନ୍ୟ *pixels);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLCOPYTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLCOMPRESSEDTEXIMAGE3DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, ଅଚଳ ଶୂନ୍ୟ *data);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, ଅଚଳ ଶୂନ୍ୟ *data);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGENQUERIESPROC) (GLsizei n, GLuint *ids);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLDELETEQUERIESPROC) (GLsizei n, ଅଚଳ GLuint *ids);
ପ୍ରକାରବ୍ୟାଖ୍ୟା GLboolean (GL_APIENTRYP PFNGLISQUERYPROC) (GLuint id);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLBEGINQUERYPROC) (GLenum target, GLuint id);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLENDQUERYPROC) (GLenum target);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETQUERYIVPROC) (GLenum target, GLenum pname, GLint *params);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETQUERYOBJECTUIVPROC) (GLuint id, GLenum pname, GLuint *params);
ପ୍ରକାରବ୍ୟାଖ୍ୟା GLboolean (GL_APIENTRYP PFNGLUNMAPBUFFERPROC) (GLenum target);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETBUFFERPOINTERVPROC) (GLenum target, GLenum pname, ଶୂନ୍ୟ **params);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLDRAWBUFFERSPROC) (GLsizei n, ଅଚଳ GLenum *bufs);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUNIFORMMATRIX2X3FVPROC) (GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUNIFORMMATRIX3X2FVPROC) (GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUNIFORMMATRIX2X4FVPROC) (GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUNIFORMMATRIX4X2FVPROC) (GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUNIFORMMATRIX3X4FVPROC) (GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUNIFORMMATRIX4X3FVPROC) (GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLBLITFRAMEBUFFERPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURELAYERPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ *(GL_APIENTRYP PFNGLMAPBUFFERRANGEPROC) (GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEPROC) (GLenum target, GLintptr offset, GLsizeiptr length);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLBINDVERTEXARRAYPROC) (GLuint array);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLDELETEVERTEXARRAYSPROC) (GLsizei n, ଅଚଳ GLuint *arrays);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint *arrays);
ପ୍ରକାରବ୍ୟାଖ୍ୟା GLboolean (GL_APIENTRYP PFNGLISVERTEXARRAYPROC) (GLuint array);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETINTEGERI_VPROC) (GLenum target, GLuint index, GLint *data);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLBEGINTRANSFORMFEEDBACKPROC) (GLenum primitiveMode);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLENDTRANSFORMFEEDBACKPROC) (ଶୂନ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLBINDBUFFERRANGEPROC) (GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLBINDBUFFERBASEPROC) (GLenum target, GLuint index, GLuint buffer);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLTRANSFORMFEEDBACKVARYINGSPROC) (GLuint program, GLsizei ଗଣନା_2, ଅଚଳ GLchar *ଅଚଳ*varyings, GLenum bufferMode);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETTRANSFORMFEEDBACKVARYINGPROC) (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLVERTEXATTRIBIPOINTERPROC) (GLuint index, GLint size, GLenum type, GLsizei stride, ଅଚଳ ଶୂନ୍ୟ *pointer);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETVERTEXATTRIBIIVPROC) (GLuint index, GLenum pname, GLint *params);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETVERTEXATTRIBIUIVPROC) (GLuint index, GLenum pname, GLuint *params);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLVERTEXATTRIBI4IPROC) (GLuint index, GLint x, GLint y, GLint z, GLint w);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLVERTEXATTRIBI4UIPROC) (GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLVERTEXATTRIBI4IVPROC) (GLuint index, ଅଚଳ GLint *v);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLVERTEXATTRIBI4UIVPROC) (GLuint index, ଅଚଳ GLuint *v);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETUNIFORMUIVPROC) (GLuint program, GLint location, GLuint *params);
ପ୍ରକାରବ୍ୟାଖ୍ୟା GLint (GL_APIENTRYP PFNGLGETFRAGDATALOCATIONPROC) (GLuint program, ଅଚଳ GLchar *name);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUNIFORM1UIPROC) (GLint location, GLuint v0);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUNIFORM2UIPROC) (GLint location, GLuint v0, GLuint v1);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUNIFORM3UIPROC) (GLint location, GLuint v0, GLuint v1, GLuint v2);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUNIFORM4UIPROC) (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUNIFORM1UIVPROC) (GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLuint *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUNIFORM2UIVPROC) (GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLuint *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUNIFORM3UIVPROC) (GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLuint *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUNIFORM4UIVPROC) (GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLuint *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLCLEARBUFFERIVPROC) (GLenum buffer, GLint drawbuffer, ଅଚଳ GLint *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLCLEARBUFFERUIVPROC) (GLenum buffer, GLint drawbuffer, ଅଚଳ GLuint *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLCLEARBUFFERFVPROC) (GLenum buffer, GLint drawbuffer, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLCLEARBUFFERFIPROC) (GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଅଚଳ GLubyte *(GL_APIENTRYP PFNGLGETSTRINGIPROC) (GLenum name, GLuint index);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLCOPYBUFFERSUBDATAPROC) (GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETUNIFORMINDICESPROC) (GLuint program, GLsizei uniform_ଗଣନା, ଅଚଳ GLchar *ଅଚଳ*uniformNames, GLuint *uniformIndices);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETACTIVEUNIFORMSIVPROC) (GLuint program, GLsizei uniform_ଗଣନା, ଅଚଳ GLuint *uniformIndices, GLenum pname, GLint *params);
ପ୍ରକାରବ୍ୟାଖ୍ୟା GLuint (GL_APIENTRYP PFNGLGETUNIFORMBLOCKINDEXPROC) (GLuint program, ଅଚଳ GLchar *uniformBlockName);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKIVPROC) (GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC) (GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUNIFORMBLOCKBINDINGPROC) (GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDPROC) (GLenum mode, GLint first, GLsizei ଗଣନା_2, GLsizei instancecount);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDPROC) (GLenum mode, GLsizei ଗଣନା_2, GLenum type, ଅଚଳ ଶୂନ୍ୟ *indices, GLsizei instancecount);
ପ୍ରକାରବ୍ୟାଖ୍ୟା GLsync (GL_APIENTRYP PFNGLFENCESYNCPROC) (GLenum condition, GLbitfield flags);
ପ୍ରକାରବ୍ୟାଖ୍ୟା GLboolean (GL_APIENTRYP PFNGLISSYNCPROC) (GLsync sync);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLDELETESYNCPROC) (GLsync sync);
ପ୍ରକାରବ୍ୟାଖ୍ୟା GLenum (GL_APIENTRYP PFNGLCLIENTWAITSYNCPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLWAITSYNCPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETINTEGER64VPROC) (GLenum pname, GLint64 *data);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETSYNCIVPROC) (GLsync sync, GLenum pname, GLsizei ଗଣନା_2, GLsizei *length, GLint *ମୂଲ୍ୟଗୁଡ଼ିକ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETINTEGER64I_VPROC) (GLenum target, GLuint index, GLint64 *data);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETBUFFERPARAMETERI64VPROC) (GLenum target, GLenum pname, GLint64 *params);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGENSAMPLERSPROC) (GLsizei ଗଣନା_2, GLuint *samplers);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLDELETESAMPLERSPROC) (GLsizei ଗଣନା_2, ଅଚଳ GLuint *samplers);
ପ୍ରକାରବ୍ୟାଖ୍ୟା GLboolean (GL_APIENTRYP PFNGLISSAMPLERPROC) (GLuint sampler);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLBINDSAMPLERPROC) (GLuint unit, GLuint sampler);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIPROC) (GLuint sampler, GLenum pname, GLint param);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, ଅଚଳ GLint *param);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLSAMPLERPARAMETERFPROC) (GLuint sampler, GLenum pname, GLfloat param);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, ଅଚଳ GLfloat *param);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, GLint *params);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, GLfloat *params);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLVERTEXATTRIBDIVISORPROC) (GLuint index, GLuint ଭାଜକ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLBINDTRANSFORMFEEDBACKPROC) (GLenum target, GLuint id);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLDELETETRANSFORMFEEDBACKSPROC) (GLsizei n, ଅଚଳ GLuint *ids);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGENTRANSFORMFEEDBACKSPROC) (GLsizei n, GLuint *ids);
ପ୍ରକାରବ୍ୟାଖ୍ୟା GLboolean (GL_APIENTRYP PFNGLISTRANSFORMFEEDBACKPROC) (GLuint id);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPAUSETRANSFORMFEEDBACKPROC) (ଶୂନ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLRESUMETRANSFORMFEEDBACKPROC) (ଶୂନ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETPROGRAMBINARYPROC) (GLuint program, GLsizei bufSize, GLsizei *length, GLenum *ଦ୍ୱିମିକ_Format, ଶୂନ୍ୟ *ଦ୍ୱିମିକ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPROGRAMBINARYPROC) (GLuint program, GLenum ଦ୍ୱିମିକ_Format, ଅଚଳ ଶୂନ୍ୟ *ଦ୍ୱିମିକ, GLsizei length);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPROGRAMPARAMETERIPROC) (GLuint program, GLenum pname, GLint ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLINVALIDATEFRAMEBUFFERPROC) (GLenum target, GLsizei ଅଙ୍କ_Attachments, ଅଚଳ GLenum *attachments);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLINVALIDATESUBFRAMEBUFFERPROC) (GLenum target, GLsizei ଅଙ୍କ_Attachments, ଅଚଳ GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLTEXSTORAGE2DPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLTEXSTORAGE3DPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETINTERNALFORMATIVPROC) (GLenum target, GLenum internalformat, GLenum pname, GLsizei ଗଣନା_2, GLint *params);
#ଯଦି GL_GLES_PROTOTYPES
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glReadBuffer (GLenum src);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glDrawRangeElements (GLenum mode, GLuint start, GLuint end, GLsizei ଗଣନା_2, GLenum type, ଅଚଳ ଶୂନ୍ୟ *indices);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glTexImage3D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, ଅଚଳ ଶୂନ୍ୟ *pixels);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, ଅଚଳ ଶୂନ୍ୟ *pixels);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glCopyTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glCompressedTexImage3D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, ଅଚଳ ଶୂନ୍ୟ *data);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glCompressedTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, ଅଚଳ ଶୂନ୍ୟ *data);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGenQueries (GLsizei n, GLuint *ids);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glDeleteQueries (GLsizei n, ଅଚଳ GLuint *ids);
GL_APICALL GLboolean GL_APIENTRY glIsQuery (GLuint id);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glBeginQuery (GLenum target, GLuint id);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glEndQuery (GLenum target);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetQueryiv (GLenum target, GLenum pname, GLint *params);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetQueryObjectuiv (GLuint id, GLenum pname, GLuint *params);
GL_APICALL GLboolean GL_APIENTRY glUnmapBuffer (GLenum target);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetBufferPointerv (GLenum target, GLenum pname, ଶୂନ୍ୟ **params);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glDrawBuffers (GLsizei n, ଅଚଳ GLenum *bufs);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUniformMatrix2x3fv (GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUniformMatrix3x2fv (GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUniformMatrix2x4fv (GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUniformMatrix4x2fv (GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUniformMatrix3x4fv (GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUniformMatrix4x3fv (GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glBlitFramebuffer (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glRenderbufferStorageMultisample (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glFramebufferTextureLayer (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
GL_APICALL ଶୂନ୍ୟ *GL_APIENTRY glMapBufferRange (GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glFlushMappedBufferRange (GLenum target, GLintptr offset, GLsizeiptr length);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glBindVertexArray (GLuint array);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glDeleteVertexArrays (GLsizei n, ଅଚଳ GLuint *arrays);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGenVertexArrays (GLsizei n, GLuint *arrays);
GL_APICALL GLboolean GL_APIENTRY glIsVertexArray (GLuint array);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetIntegeri_v (GLenum target, GLuint index, GLint *data);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glBeginTransformFeedback (GLenum primitiveMode);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glEndTransformFeedback (ଶୂନ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glBindBufferRange (GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glBindBufferBase (GLenum target, GLuint index, GLuint buffer);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glTransformFeedbackVaryings (GLuint program, GLsizei ଗଣନା_2, ଅଚଳ GLchar *ଅଚଳ*varyings, GLenum bufferMode);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetTransformFeedbackVarying (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glVertexAttribIPointer (GLuint index, GLint size, GLenum type, GLsizei stride, ଅଚଳ ଶୂନ୍ୟ *pointer);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetVertexAttribIiv (GLuint index, GLenum pname, GLint *params);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetVertexAttribIuiv (GLuint index, GLenum pname, GLuint *params);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glVertexAttribI4i (GLuint index, GLint x, GLint y, GLint z, GLint w);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glVertexAttribI4ui (GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glVertexAttribI4iv (GLuint index, ଅଚଳ GLint *v);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glVertexAttribI4uiv (GLuint index, ଅଚଳ GLuint *v);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetUniformuiv (GLuint program, GLint location, GLuint *params);
GL_APICALL GLint GL_APIENTRY glGetFragDataLocation (GLuint program, ଅଚଳ GLchar *name);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUniform1ui (GLint location, GLuint v0);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUniform2ui (GLint location, GLuint v0, GLuint v1);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUniform3ui (GLint location, GLuint v0, GLuint v1, GLuint v2);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUniform4ui (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUniform1uiv (GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLuint *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUniform2uiv (GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLuint *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUniform3uiv (GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLuint *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUniform4uiv (GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLuint *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glClearBufferiv (GLenum buffer, GLint drawbuffer, ଅଚଳ GLint *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glClearBufferuiv (GLenum buffer, GLint drawbuffer, ଅଚଳ GLuint *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glClearBufferfv (GLenum buffer, GLint drawbuffer, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glClearBufferfi (GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
GL_APICALL ଅଚଳ GLubyte *GL_APIENTRY glGetStringi (GLenum name, GLuint index);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glCopyBufferSubData (GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetUniformIndices (GLuint program, GLsizei uniform_ଗଣନା, ଅଚଳ GLchar *ଅଚଳ*uniformNames, GLuint *uniformIndices);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetActiveUniformsiv (GLuint program, GLsizei uniform_ଗଣନା, ଅଚଳ GLuint *uniformIndices, GLenum pname, GLint *params);
GL_APICALL GLuint GL_APIENTRY glGetUniformBlockIndex (GLuint program, ଅଚଳ GLchar *uniformBlockName);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetActiveUniformBlockiv (GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetActiveUniformBlockName (GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUniformBlockBinding (GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glDrawArraysInstanced (GLenum mode, GLint first, GLsizei ଗଣନା_2, GLsizei instancecount);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glDrawElementsInstanced (GLenum mode, GLsizei ଗଣନା_2, GLenum type, ଅଚଳ ଶୂନ୍ୟ *indices, GLsizei instancecount);
GL_APICALL GLsync GL_APIENTRY glFenceSync (GLenum condition, GLbitfield flags);
GL_APICALL GLboolean GL_APIENTRY glIsSync (GLsync sync);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glDeleteSync (GLsync sync);
GL_APICALL GLenum GL_APIENTRY glClientWaitSync (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glWaitSync (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetInteger64v (GLenum pname, GLint64 *data);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetSynciv (GLsync sync, GLenum pname, GLsizei ଗଣନା_2, GLsizei *length, GLint *ମୂଲ୍ୟଗୁଡ଼ିକ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetInteger64i_v (GLenum target, GLuint index, GLint64 *data);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetBufferParameteri64v (GLenum target, GLenum pname, GLint64 *params);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGenSamplers (GLsizei ଗଣନା_2, GLuint *samplers);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glDeleteSamplers (GLsizei ଗଣନା_2, ଅଚଳ GLuint *samplers);
GL_APICALL GLboolean GL_APIENTRY glIsSampler (GLuint sampler);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glBindSampler (GLuint unit, GLuint sampler);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glSamplerParameteri (GLuint sampler, GLenum pname, GLint param);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glSamplerParameteriv (GLuint sampler, GLenum pname, ଅଚଳ GLint *param);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glSamplerParameterf (GLuint sampler, GLenum pname, GLfloat param);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glSamplerParameterfv (GLuint sampler, GLenum pname, ଅଚଳ GLfloat *param);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetSamplerParameteriv (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetSamplerParameterfv (GLuint sampler, GLenum pname, GLfloat *params);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY gl_Vertex_Attrib_ଭାଜକ (GLuint index, GLuint ଭାଜକ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glBindTransformFeedback (GLenum target, GLuint id);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glDeleteTransformFeedbacks (GLsizei n, ଅଚଳ GLuint *ids);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGenTransformFeedbacks (GLsizei n, GLuint *ids);
GL_APICALL GLboolean GL_APIENTRY glIsTransformFeedback (GLuint id);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glPauseTransformFeedback (ଶୂନ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glResumeTransformFeedback (ଶୂନ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY gl_Get_Program_ଦ୍ୱିମିକ (GLuint program, GLsizei bufSize, GLsizei *length, GLenum *ଦ୍ୱିମିକ_Format, ଶୂନ୍ୟ *ଦ୍ୱିମିକ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY gl_Program_ଦ୍ୱିମିକ (GLuint program, GLenum ଦ୍ୱିମିକ_Format, ଅଚଳ ଶୂନ୍ୟ *ଦ୍ୱିମିକ, GLsizei length);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glProgramParameteri (GLuint program, GLenum pname, GLint ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glInvalidateFramebuffer (GLenum target, GLsizei ଅଙ୍କ_Attachments, ଅଚଳ GLenum *attachments);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glInvalidateSubFramebuffer (GLenum target, GLsizei ଅଙ୍କ_Attachments, ଅଚଳ GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glTexStorage2D (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glTexStorage3D (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetInternalformativ (GLenum target, GLenum internalformat, GLenum pname, GLsizei ଗଣନା_2, GLint *params);
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
#define GL_MAX_COMPUTE_WORK_GROUP_ଗଣନା   0x91BE
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
#define GL_PROGRAM_ନିବେଶ                  0x92E3
#define GL_PROGRAM_OUTPUT                 0x92E4
#define GL_BUFFER_VARIABLE                0x92E5
#define GL_SHADER_STORAGE_BLOCK           0x92E6
#define GL_ATOMIC_COUNTER_BUFFER          0x92C0
#define GL_TRANSFORM_FEEDBACK_VARYING     0x92F4
#define GL_ACTIVE_RESOURCES               0x92F5
#define GL_MAX_NAME_LENGTH                0x92F6
#define GL_MAX_ଅଙ୍କ_ACTIVE_VARIABLES       0x92F7
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
#define GL_ଅଙ୍କ_ACTIVE_VARIABLES           0x9304
#define GL_ACTIVE_VARIABLES               0x9305
#define GL_REFERENCED_BY_VERTEX_SHADER    0x9306
#define GL_REFERENCED_BY_FRAGMENT_SHADER  0x930A
#define GL_REFERENCED_BY_COMPUTE_SHADER   0x930B
#define GL_ଶୀର୍ଷ_LEVEL_ARRAY_SIZE           0x930C
#define GL_ଶୀର୍ଷ_LEVEL_ARRAY_STRIDE         0x930D
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
#define GL_SAMPLE_MASK_ମୂଲ୍ୟ              0x8E52
#define GL_TEXTURE_2D_MULTISAMPLE         0x9100
#define GL_MAX_SAMPLE_MASK_ଶବ୍ଦଗୁଡ଼ିକ          0x8E59
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
#define GL_VERTEX_BINDING_ଭାଜକ         0x82D6
#define GL_VERTEX_BINDING_OFFSET          0x82D7
#define GL_VERTEX_BINDING_STRIDE          0x82D8
#define GL_VERTEX_BINDING_BUFFER          0x8F4F
#define GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET 0x82D9
#define GL_MAX_VERTEX_ATTRIB_BINDINGS     0x82DA
#define GL_MAX_VERTEX_ATTRIB_STRIDE       0x82E5
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLDISPATCHCOMPUTEPROC) (GLuint ଅଙ୍କ_groups_x, GLuint ଅଙ୍କ_groups_y, GLuint ଅଙ୍କ_groups_z);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLDISPATCHCOMPUTEINDIRECTPROC) (GLintptr indirect);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLDRAWARRAYSINDIRECTPROC) (GLenum mode, ଅଚଳ ଶୂନ୍ୟ *indirect);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLDRAWELEMENTSINDIRECTPROC) (GLenum mode, GLenum type, ଅଚଳ ଶୂନ୍ୟ *indirect);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLFRAMEBUFFERPARAMETERIPROC) (GLenum target, GLenum pname, GLint param);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETFRAMEBUFFERPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETPROGRAMINTERFACEIVPROC) (GLuint program, GLenum programInterface, GLenum pname, GLint *params);
ପ୍ରକାରବ୍ୟାଖ୍ୟା GLuint (GL_APIENTRYP PFNGLGETPROGRAMRESOURCEINDEXPROC) (GLuint program, GLenum programInterface, ଅଚଳ GLchar *name);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETPROGRAMRESOURCENAMEPROC) (GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETPROGRAMRESOURCEIVPROC) (GLuint program, GLenum programInterface, GLuint index, GLsizei prop_ଗଣନା, ଅଚଳ GLenum *props, GLsizei ଗଣନା_2, GLsizei *length, GLint *params);
ପ୍ରକାରବ୍ୟାଖ୍ୟା GLint (GL_APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONPROC) (GLuint program, GLenum programInterface, ଅଚଳ GLchar *name);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLUSEPROGRAMSTAGESPROC) (GLuint pipeline, GLbitfield stages, GLuint program);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLACTIVESHADERPROGRAMPROC) (GLuint pipeline, GLuint program);
ପ୍ରକାରବ୍ୟାଖ୍ୟା GLuint (GL_APIENTRYP PFNGLCREATESHADERPROGRAMVPROC) (GLenum type, GLsizei ଗଣନା_2, ଅଚଳ GLchar *ଅଚଳ*strings);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLBINDPROGRAMPIPELINEPROC) (GLuint pipeline);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLDELETEPROGRAMPIPELINESPROC) (GLsizei n, ଅଚଳ GLuint *pipelines);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGENPROGRAMPIPELINESPROC) (GLsizei n, GLuint *pipelines);
ପ୍ରକାରବ୍ୟାଖ୍ୟା GLboolean (GL_APIENTRYP PFNGLISPROGRAMPIPELINEPROC) (GLuint pipeline);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETPROGRAMPIPELINEIVPROC) (GLuint pipeline, GLenum pname, GLint *params);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1IPROC) (GLuint program, GLint location, GLint v0);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2IPROC) (GLuint program, GLint location, GLint v0, GLint v1);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3IPROC) (GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4IPROC) (GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UIPROC) (GLuint program, GLint location, GLuint v0);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UIPROC) (GLuint program, GLint location, GLuint v0, GLuint v1);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UIPROC) (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UIPROC) (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1FPROC) (GLuint program, GLint location, GLfloat v0);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2FPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3FPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4FPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1IVPROC) (GLuint program, GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLint *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2IVPROC) (GLuint program, GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLint *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3IVPROC) (GLuint program, GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLint *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4IVPROC) (GLuint program, GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLint *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UIVPROC) (GLuint program, GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLuint *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UIVPROC) (GLuint program, GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLuint *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UIVPROC) (GLuint program, GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLuint *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UIVPROC) (GLuint program, GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLuint *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1FVPROC) (GLuint program, GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2FVPROC) (GLuint program, GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3FVPROC) (GLuint program, GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4FVPROC) (GLuint program, GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2FVPROC) (GLuint program, GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3FVPROC) (GLuint program, GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4FVPROC) (GLuint program, GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC) (GLuint program, GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC) (GLuint program, GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC) (GLuint program, GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC) (GLuint program, GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC) (GLuint program, GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC) (GLuint program, GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLVALIDATEPROGRAMPIPELINEPROC) (GLuint pipeline);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETPROGRAMPIPELINEINFOLOGPROC) (GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLBINDIMAGETEXTUREPROC) (GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETBOOLEANI_VPROC) (GLenum target, GLuint index, GLboolean *data);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLMEMORYBARRIERPROC) (GLbitfield barriers);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLMEMORYBARRIERBYREGIONPROC) (GLbitfield barriers);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLTEXSTORAGE2DMULTISAMPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETMULTISAMPLEFVPROC) (GLenum pname, GLuint index, GLfloat *val);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLSAMPLEMASKIPROC) (GLuint mask_ସଂଖ୍ୟା, GLbitfield mask);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETTEXLEVELPARAMETERIVPROC) (GLenum target, GLint level, GLenum pname, GLint *params);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLGETTEXLEVELPARAMETERFVPROC) (GLenum target, GLint level, GLenum pname, GLfloat *params);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLBINDVERTEXBUFFERPROC) (GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLVERTEXATTRIBFORMATPROC) (GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLVERTEXATTRIBIFORMATPROC) (GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLVERTEXATTRIBBINDINGPROC) (GLuint attribindex, GLuint bindingindex);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (GL_APIENTRYP PFNGLVERTEXBINDINGDIVISORPROC) (GLuint bindingindex, GLuint ଭାଜକ);
#ଯଦି GL_GLES_PROTOTYPES
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glDispatchCompute (GLuint ଅଙ୍କ_groups_x, GLuint ଅଙ୍କ_groups_y, GLuint ଅଙ୍କ_groups_z);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glDispatchComputeIndirect (GLintptr indirect);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glDrawArraysIndirect (GLenum mode, ଅଚଳ ଶୂନ୍ୟ *indirect);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glDrawElementsIndirect (GLenum mode, GLenum type, ଅଚଳ ଶୂନ୍ୟ *indirect);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glFramebufferParameteri (GLenum target, GLenum pname, GLint param);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetFramebufferParameteriv (GLenum target, GLenum pname, GLint *params);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetProgramInterfaceiv (GLuint program, GLenum programInterface, GLenum pname, GLint *params);
GL_APICALL GLuint GL_APIENTRY glGetProgramResourceIndex (GLuint program, GLenum programInterface, ଅଚଳ GLchar *name);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetProgramResourceName (GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetProgramResourceiv (GLuint program, GLenum programInterface, GLuint index, GLsizei prop_ଗଣନା, ଅଚଳ GLenum *props, GLsizei ଗଣନା_2, GLsizei *length, GLint *params);
GL_APICALL GLint GL_APIENTRY glGetProgramResourceLocation (GLuint program, GLenum programInterface, ଅଚଳ GLchar *name);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glUseProgramStages (GLuint pipeline, GLbitfield stages, GLuint program);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glActiveShaderProgram (GLuint pipeline, GLuint program);
GL_APICALL GLuint GL_APIENTRY glCreateShaderProgramv (GLenum type, GLsizei ଗଣନା_2, ଅଚଳ GLchar *ଅଚଳ*strings);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glBindProgramPipeline (GLuint pipeline);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glDeleteProgramPipelines (GLsizei n, ଅଚଳ GLuint *pipelines);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGenProgramPipelines (GLsizei n, GLuint *pipelines);
GL_APICALL GLboolean GL_APIENTRY glIsProgramPipeline (GLuint pipeline);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetProgramPipelineiv (GLuint pipeline, GLenum pname, GLint *params);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glProgramUniform1i (GLuint program, GLint location, GLint v0);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glProgramUniform2i (GLuint program, GLint location, GLint v0, GLint v1);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glProgramUniform3i (GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glProgramUniform4i (GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glProgramUniform1ui (GLuint program, GLint location, GLuint v0);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glProgramUniform2ui (GLuint program, GLint location, GLuint v0, GLuint v1);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glProgramUniform3ui (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glProgramUniform4ui (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glProgramUniform1f (GLuint program, GLint location, GLfloat v0);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glProgramUniform2f (GLuint program, GLint location, GLfloat v0, GLfloat v1);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glProgramUniform3f (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glProgramUniform4f (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glProgramUniform1iv (GLuint program, GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLint *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glProgramUniform2iv (GLuint program, GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLint *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glProgramUniform3iv (GLuint program, GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLint *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glProgramUniform4iv (GLuint program, GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLint *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glProgramUniform1uiv (GLuint program, GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLuint *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glProgramUniform2uiv (GLuint program, GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLuint *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glProgramUniform3uiv (GLuint program, GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLuint *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glProgramUniform4uiv (GLuint program, GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLuint *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glProgramUniform1fv (GLuint program, GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glProgramUniform2fv (GLuint program, GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glProgramUniform3fv (GLuint program, GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glProgramUniform4fv (GLuint program, GLint location, GLsizei ଗଣନା_2, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glProgramUniformMatrix2fv (GLuint program, GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glProgramUniformMatrix3fv (GLuint program, GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glProgramUniformMatrix4fv (GLuint program, GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glProgramUniformMatrix2x3fv (GLuint program, GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glProgramUniformMatrix3x2fv (GLuint program, GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glProgramUniformMatrix2x4fv (GLuint program, GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glProgramUniformMatrix4x2fv (GLuint program, GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glProgramUniformMatrix3x4fv (GLuint program, GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glProgramUniformMatrix4x3fv (GLuint program, GLint location, GLsizei ଗଣନା_2, GLboolean transpose, ଅଚଳ GLfloat *ମୂଲ୍ୟ);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glValidateProgramPipeline (GLuint pipeline);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetProgramPipelineInfoLog (GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glBindImageTexture (GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetBooleani_v (GLenum target, GLuint index, GLboolean *data);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glMemoryBarrier (GLbitfield barriers);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glMemoryBarrierByRegion (GLbitfield barriers);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glTexStorage2DMultisample (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetMultisamplefv (GLenum pname, GLuint index, GLfloat *val);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glSampleMaski (GLuint mask_ସଂଖ୍ୟା, GLbitfield mask);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetTexLevelParameteriv (GLenum target, GLint level, GLenum pname, GLint *params);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glGetTexLevelParameterfv (GLenum target, GLint level, GLenum pname, GLfloat *params);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glBindVertexBuffer (GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glVertexAttribFormat (GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glVertexAttribIFormat (GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY glVertexAttribBinding (GLuint attribindex, GLuint bindingindex);
GL_APICALL ଶୂନ୍ୟ GL_APIENTRY gl_Vertex_Binding_ଭାଜକ (GLuint bindingindex, GLuint ଭାଜକ);
#endif
#endif /* GL_ES_VERSION_3_1 */

#ifdef __cplusplus
}
#endif

#endif
