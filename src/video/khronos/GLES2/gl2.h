#अगर_अघोषित __gles2_gl2_h_
#घोषणा __gles2_gl2_h_ 1

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

#समावेश <GLES2/gl2platform.h>

#अगर_अघोषित GL_APIENTRYP
#घोषणा GL_APIENTRYP GL_APIENTRY*
#पूर्ण_अगर

#अगर_अघोषित GL_GLES_PROTOTYPES
#घोषणा GL_GLES_PROTOTYPES 1
#पूर्ण_अगर

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

#अगर_अघोषित GL_ES_VERSION_2_0
#घोषणा GL_ES_VERSION_2_0 1
#समावेश <KHR/khrplatform.h>
प्रकार khronos_int8_t GLbyte;
प्रकार khronos_float_t GLclampf;
प्रकार khronos_int32_t GLfixed;
प्रकार khronos_int16_t GLshort;
प्रकार khronos_uint16_t GLushort;
प्रकार व्योम GLvoid;
प्रकार काष्ठा __GLsync *GLsync;
प्रकार khronos_int64_t GLint64;
प्रकार khronos_uint64_t GLuint64;
प्रकार अचिन्हित पूर्णांक GLenum;
प्रकार अचिन्हित पूर्णांक GLuint;
प्रकार अक्षर GLchar;
प्रकार khronos_float_t GLfloat;
प्रकार khronos_ssize_t GLsizeiptr;
प्रकार khronos_intptr_t GLintptr;
प्रकार अचिन्हित पूर्णांक GLbitfield;
प्रकार पूर्णांक GLint;
प्रकार अचिन्हित अक्षर GLboolean;
प्रकार पूर्णांक GLsizei;
प्रकार khronos_uint8_t GLubyte;
#घोषणा GL_DEPTH_बफर_BIT               0x00000100
#घोषणा GL_STENCIL_बफर_BIT             0x00000400
#घोषणा GL_COLOR_बफर_BIT               0x00004000
#घोषणा GL_FALSE                          0
#घोषणा GL_TRUE                           1
#घोषणा GL_POINTS                         0x0000
#घोषणा GL_पंक्तियाँ                          0x0001
#घोषणा GL_पंक्ति_LOOP                      0x0002
#घोषणा GL_पंक्ति_STRIP                     0x0003
#घोषणा GL_TRIANGLES                      0x0004
#घोषणा GL_TRIANGLE_STRIP                 0x0005
#घोषणा GL_TRIANGLE_FAN                   0x0006
#घोषणा GL_ZERO                           0
#घोषणा GL_ONE                            1
#घोषणा GL_SRC_COLOR                      0x0300
#घोषणा GL_ONE_MINUS_SRC_COLOR            0x0301
#घोषणा GL_SRC_ALPHA                      0x0302
#घोषणा GL_ONE_MINUS_SRC_ALPHA            0x0303
#घोषणा GL_DST_ALPHA                      0x0304
#घोषणा GL_ONE_MINUS_DST_ALPHA            0x0305
#घोषणा GL_DST_COLOR                      0x0306
#घोषणा GL_ONE_MINUS_DST_COLOR            0x0307
#घोषणा GL_SRC_ALPHA_SATURATE             0x0308
#घोषणा GL_FUNC_ADD                       0x8006
#घोषणा GL_BLEND_EQUATION                 0x8009
#घोषणा GL_BLEND_EQUATION_RGB             0x8009
#घोषणा GL_BLEND_EQUATION_ALPHA           0x883D
#घोषणा GL_FUNC_SUBTRACT                  0x800A
#घोषणा GL_FUNC_REVERSE_SUBTRACT          0x800B
#घोषणा GL_BLEND_DST_RGB                  0x80C8
#घोषणा GL_BLEND_SRC_RGB                  0x80C9
#घोषणा GL_BLEND_DST_ALPHA                0x80CA
#घोषणा GL_BLEND_SRC_ALPHA                0x80CB
#घोषणा GL_CONSTANT_COLOR                 0x8001
#घोषणा GL_ONE_MINUS_CONSTANT_COLOR       0x8002
#घोषणा GL_CONSTANT_ALPHA                 0x8003
#घोषणा GL_ONE_MINUS_CONSTANT_ALPHA       0x8004
#घोषणा GL_BLEND_COLOR                    0x8005
#घोषणा GL_ARRAY_बफर                   0x8892
#घोषणा GL_ELEMENT_ARRAY_बफर           0x8893
#घोषणा GL_ARRAY_बफर_BINDING           0x8894
#घोषणा GL_ELEMENT_ARRAY_बफर_BINDING   0x8895
#घोषणा GL_STREAM_DRAW                    0x88E0
#घोषणा GL_STATIC_DRAW                    0x88E4
#घोषणा GL_DYNAMIC_DRAW                   0x88E8
#घोषणा GL_बफर_आकार                    0x8764
#घोषणा GL_बफर_USAGE                   0x8765
#घोषणा GL_CURRENT_VERTEX_ATTRIB          0x8626
#घोषणा GL_FRONT                          0x0404
#घोषणा GL_BACK                           0x0405
#घोषणा GL_FRONT_AND_BACK                 0x0408
#घोषणा GL_TEXTURE_2D                     0x0DE1
#घोषणा GL_CULL_FACE                      0x0B44
#घोषणा GL_BLEND                          0x0BE2
#घोषणा GL_DITHER                         0x0BD0
#घोषणा GL_STENCIL_TEST                   0x0B90
#घोषणा GL_DEPTH_TEST                     0x0B71
#घोषणा GL_SCISSOR_TEST                   0x0C11
#घोषणा GL_POLYGON_OFFSET_FILL            0x8037
#घोषणा GL_SAMPLE_ALPHA_TO_COVERAGE       0x809E
#घोषणा GL_SAMPLE_COVERAGE                0x80A0
#घोषणा GL_NO_ERROR                       0
#घोषणा GL_INVALID_ENUM                   0x0500
#घोषणा GL_INVALID_मूल्य                  0x0501
#घोषणा GL_INVALID_OPERATION              0x0502
#घोषणा GL_OUT_OF_MEMORY                  0x0505
#घोषणा GL_CW                             0x0900
#घोषणा GL_CCW                            0x0901
#घोषणा GL_पंक्ति_WIDTH                     0x0B21
#घोषणा GL_ALIASED_POINT_आकार_RANGE       0x846D
#घोषणा GL_ALIASED_पंक्ति_WIDTH_RANGE       0x846E
#घोषणा GL_CULL_FACE_MODE                 0x0B45
#घोषणा GL_FRONT_FACE                     0x0B46
#घोषणा GL_DEPTH_RANGE                    0x0B70
#घोषणा GL_DEPTH_WRITEMASK                0x0B72
#घोषणा GL_DEPTH_CLEAR_मूल्य              0x0B73
#घोषणा GL_DEPTH_FUNC                     0x0B74
#घोषणा GL_STENCIL_CLEAR_मूल्य            0x0B91
#घोषणा GL_STENCIL_FUNC                   0x0B92
#घोषणा GL_STENCIL_FAIL                   0x0B94
#घोषणा GL_STENCIL_PASS_DEPTH_FAIL        0x0B95
#घोषणा GL_STENCIL_PASS_DEPTH_PASS        0x0B96
#घोषणा GL_STENCIL_REF                    0x0B97
#घोषणा GL_STENCIL_मूल्य_MASK             0x0B93
#घोषणा GL_STENCIL_WRITEMASK              0x0B98
#घोषणा GL_STENCIL_BACK_FUNC              0x8800
#घोषणा GL_STENCIL_BACK_FAIL              0x8801
#घोषणा GL_STENCIL_BACK_PASS_DEPTH_FAIL   0x8802
#घोषणा GL_STENCIL_BACK_PASS_DEPTH_PASS   0x8803
#घोषणा GL_STENCIL_BACK_REF               0x8CA3
#घोषणा GL_STENCIL_BACK_मूल्य_MASK        0x8CA4
#घोषणा GL_STENCIL_BACK_WRITEMASK         0x8CA5
#घोषणा GL_VIEWPORT                       0x0BA2
#घोषणा GL_SCISSOR_BOX                    0x0C10
#घोषणा GL_COLOR_CLEAR_मूल्य              0x0C22
#घोषणा GL_COLOR_WRITEMASK                0x0C23
#घोषणा GL_UNPACK_ALIGNMENT               0x0CF5
#घोषणा GL_PACK_ALIGNMENT                 0x0D05
#घोषणा GL_MAX_TEXTURE_आकार               0x0D33
#घोषणा GL_MAX_VIEWPORT_DIMS              0x0D3A
#घोषणा GL_SUBPIXEL_BITS                  0x0D50
#घोषणा GL_RED_BITS                       0x0D52
#घोषणा GL_GREEN_BITS                     0x0D53
#घोषणा GL_BLUE_BITS                      0x0D54
#घोषणा GL_ALPHA_BITS                     0x0D55
#घोषणा GL_DEPTH_BITS                     0x0D56
#घोषणा GL_STENCIL_BITS                   0x0D57
#घोषणा GL_POLYGON_OFFSET_UNITS           0x2A00
#घोषणा GL_POLYGON_OFFSET_FACTOR          0x8038
#घोषणा GL_TEXTURE_BINDING_2D             0x8069
#घोषणा GL_SAMPLE_BUFFERS                 0x80A8
#घोषणा GL_SAMPLES                        0x80A9
#घोषणा GL_SAMPLE_COVERAGE_मूल्य          0x80AA
#घोषणा GL_SAMPLE_COVERAGE_INVERT         0x80AB
#घोषणा GL_अंक_COMPRESSED_TEXTURE_FORMATS 0x86A2
#घोषणा GL_COMPRESSED_TEXTURE_FORMATS     0x86A3
#घोषणा GL_DONT_CARE                      0x1100
#घोषणा GL_FASTEST                        0x1101
#घोषणा GL_NICEST                         0x1102
#घोषणा GL_GENERATE_MIPMAP_HINT           0x8192
#घोषणा GL_BYTE                           0x1400
#घोषणा GL_UNSIGNED_BYTE                  0x1401
#घोषणा GL_SHORT                          0x1402
#घोषणा GL_UNSIGNED_SHORT                 0x1403
#घोषणा GL_INT                            0x1404
#घोषणा GL_UNSIGNED_INT                   0x1405
#घोषणा GL_FLOAT                          0x1406
#घोषणा GL_FIXED                          0x140C
#घोषणा GL_DEPTH_COMPONENT                0x1902
#घोषणा GL_ALPHA                          0x1906
#घोषणा GL_RGB                            0x1907
#घोषणा GL_RGBA                           0x1908
#घोषणा GL_LUMINANCE                      0x1909
#घोषणा GL_LUMINANCE_ALPHA                0x190A
#घोषणा GL_UNSIGNED_SHORT_4_4_4_4         0x8033
#घोषणा GL_UNSIGNED_SHORT_5_5_5_1         0x8034
#घोषणा GL_UNSIGNED_SHORT_5_6_5           0x8363
#घोषणा GL_FRAGMENT_SHADER                0x8B30
#घोषणा GL_VERTEX_SHADER                  0x8B31
#घोषणा GL_MAX_VERTEX_ATTRIBS             0x8869
#घोषणा GL_MAX_VERTEX_UNIFORM_VECTORS     0x8DFB
#घोषणा GL_MAX_VARYING_VECTORS            0x8DFC
#घोषणा GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 0x8B4D
#घोषणा GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS 0x8B4C
#घोषणा GL_MAX_TEXTURE_IMAGE_UNITS        0x8872
#घोषणा GL_MAX_FRAGMENT_UNIFORM_VECTORS   0x8DFD
#घोषणा GL_SHADER_TYPE                    0x8B4F
#घोषणा GL_DELETE_STATUS                  0x8B80
#घोषणा GL_LINK_STATUS                    0x8B82
#घोषणा GL_VALIDATE_STATUS                0x8B83
#घोषणा GL_ATTACHED_SHADERS               0x8B85
#घोषणा GL_ACTIVE_UNIFORMS                0x8B86
#घोषणा GL_ACTIVE_UNIFORM_MAX_लंबाई      0x8B87
#घोषणा GL_ACTIVE_ATTRIBUTES              0x8B89
#घोषणा GL_ACTIVE_ATTRIBUTE_MAX_लंबाई    0x8B8A
#घोषणा GL_SHADING_LANGUAGE_VERSION       0x8B8C
#घोषणा GL_CURRENT_PROGRAM                0x8B8D
#घोषणा GL_NEVER                          0x0200
#घोषणा GL_LESS                           0x0201
#घोषणा GL_EQUAL                          0x0202
#घोषणा GL_LEQUAL                         0x0203
#घोषणा GL_GREATER                        0x0204
#घोषणा GL_NOTEQUAL                       0x0205
#घोषणा GL_GEQUAL                         0x0206
#घोषणा GL_ALWAYS                         0x0207
#घोषणा GL_KEEP                           0x1E00
#घोषणा GL_REPLACE                        0x1E01
#घोषणा GL_INCR                           0x1E02
#घोषणा GL_DECR                           0x1E03
#घोषणा GL_INVERT                         0x150A
#घोषणा GL_INCR_WRAP                      0x8507
#घोषणा GL_DECR_WRAP                      0x8508
#घोषणा GL_VENDOR                         0x1F00
#घोषणा GL_RENDERER                       0x1F01
#घोषणा GL_VERSION                        0x1F02
#घोषणा GL_EXTENSIONS                     0x1F03
#घोषणा GL_NEAREST                        0x2600
#घोषणा GL_LINEAR                         0x2601
#घोषणा GL_NEAREST_MIPMAP_NEAREST         0x2700
#घोषणा GL_LINEAR_MIPMAP_NEAREST          0x2701
#घोषणा GL_NEAREST_MIPMAP_LINEAR          0x2702
#घोषणा GL_LINEAR_MIPMAP_LINEAR           0x2703
#घोषणा GL_TEXTURE_MAG_FILTER             0x2800
#घोषणा GL_TEXTURE_MIN_FILTER             0x2801
#घोषणा GL_TEXTURE_WRAP_S                 0x2802
#घोषणा GL_TEXTURE_WRAP_T                 0x2803
#घोषणा GL_TEXTURE                        0x1702
#घोषणा GL_TEXTURE_CUBE_MAP               0x8513
#घोषणा GL_TEXTURE_BINDING_CUBE_MAP       0x8514
#घोषणा GL_TEXTURE_CUBE_MAP_POSITIVE_X    0x8515
#घोषणा GL_TEXTURE_CUBE_MAP_NEGATIVE_X    0x8516
#घोषणा GL_TEXTURE_CUBE_MAP_POSITIVE_Y    0x8517
#घोषणा GL_TEXTURE_CUBE_MAP_NEGATIVE_Y    0x8518
#घोषणा GL_TEXTURE_CUBE_MAP_POSITIVE_Z    0x8519
#घोषणा GL_TEXTURE_CUBE_MAP_NEGATIVE_Z    0x851A
#घोषणा GL_MAX_CUBE_MAP_TEXTURE_आकार      0x851C
#घोषणा GL_TEXTURE0                       0x84C0
#घोषणा GL_TEXTURE1                       0x84C1
#घोषणा GL_TEXTURE2                       0x84C2
#घोषणा GL_TEXTURE3                       0x84C3
#घोषणा GL_TEXTURE4                       0x84C4
#घोषणा GL_TEXTURE5                       0x84C5
#घोषणा GL_TEXTURE6                       0x84C6
#घोषणा GL_TEXTURE7                       0x84C7
#घोषणा GL_TEXTURE8                       0x84C8
#घोषणा GL_TEXTURE9                       0x84C9
#घोषणा GL_TEXTURE10                      0x84CA
#घोषणा GL_TEXTURE11                      0x84CB
#घोषणा GL_TEXTURE12                      0x84CC
#घोषणा GL_TEXTURE13                      0x84CD
#घोषणा GL_TEXTURE14                      0x84CE
#घोषणा GL_TEXTURE15                      0x84CF
#घोषणा GL_TEXTURE16                      0x84D0
#घोषणा GL_TEXTURE17                      0x84D1
#घोषणा GL_TEXTURE18                      0x84D2
#घोषणा GL_TEXTURE19                      0x84D3
#घोषणा GL_TEXTURE20                      0x84D4
#घोषणा GL_TEXTURE21                      0x84D5
#घोषणा GL_TEXTURE22                      0x84D6
#घोषणा GL_TEXTURE23                      0x84D7
#घोषणा GL_TEXTURE24                      0x84D8
#घोषणा GL_TEXTURE25                      0x84D9
#घोषणा GL_TEXTURE26                      0x84DA
#घोषणा GL_TEXTURE27                      0x84DB
#घोषणा GL_TEXTURE28                      0x84DC
#घोषणा GL_TEXTURE29                      0x84DD
#घोषणा GL_TEXTURE30                      0x84DE
#घोषणा GL_TEXTURE31                      0x84DF
#घोषणा GL_ACTIVE_TEXTURE                 0x84E0
#घोषणा GL_REPEAT                         0x2901
#घोषणा GL_CLAMP_TO_EDGE                  0x812F
#घोषणा GL_MIRRORED_REPEAT                0x8370
#घोषणा GL_FLOAT_VEC2                     0x8B50
#घोषणा GL_FLOAT_VEC3                     0x8B51
#घोषणा GL_FLOAT_VEC4                     0x8B52
#घोषणा GL_INT_VEC2                       0x8B53
#घोषणा GL_INT_VEC3                       0x8B54
#घोषणा GL_INT_VEC4                       0x8B55
#घोषणा GL_BOOL                           0x8B56
#घोषणा GL_BOOL_VEC2                      0x8B57
#घोषणा GL_BOOL_VEC3                      0x8B58
#घोषणा GL_BOOL_VEC4                      0x8B59
#घोषणा GL_FLOAT_MAT2                     0x8B5A
#घोषणा GL_FLOAT_MAT3                     0x8B5B
#घोषणा GL_FLOAT_MAT4                     0x8B5C
#घोषणा GL_SAMPLER_2D                     0x8B5E
#घोषणा GL_SAMPLER_CUBE                   0x8B60
#घोषणा GL_VERTEX_ATTRIB_ARRAY_ENABLED    0x8622
#घोषणा GL_VERTEX_ATTRIB_ARRAY_आकार       0x8623
#घोषणा GL_VERTEX_ATTRIB_ARRAY_STRIDE     0x8624
#घोषणा GL_VERTEX_ATTRIB_ARRAY_TYPE       0x8625
#घोषणा GL_VERTEX_ATTRIB_ARRAY_NORMALIZED 0x886A
#घोषणा GL_VERTEX_ATTRIB_ARRAY_POINTER    0x8645
#घोषणा GL_VERTEX_ATTRIB_ARRAY_बफर_BINDING 0x889F
#घोषणा GL_IMPLEMENTATION_COLOR_READ_TYPE 0x8B9A
#घोषणा GL_IMPLEMENTATION_COLOR_READ_FORMAT 0x8B9B
#घोषणा GL_COMPILE_STATUS                 0x8B81
#घोषणा GL_INFO_LOG_लंबाई                0x8B84
#घोषणा GL_SHADER_SOURCE_लंबाई           0x8B88
#घोषणा GL_SHADER_COMPILER                0x8DFA
#घोषणा GL_SHADER_द्विआधारी_FORMATS          0x8DF8
#घोषणा GL_अंक_SHADER_द्विआधारी_FORMATS      0x8DF9
#घोषणा GL_निचला_FLOAT                      0x8DF0
#घोषणा GL_MEDIUM_FLOAT                   0x8DF1
#घोषणा GL_ऊपरी_FLOAT                     0x8DF2
#घोषणा GL_निचला_INT                        0x8DF3
#घोषणा GL_MEDIUM_INT                     0x8DF4
#घोषणा GL_ऊपरी_INT                       0x8DF5
#घोषणा GL_FRAMEBUFFER                    0x8D40
#घोषणा GL_RENDERBUFFER                   0x8D41
#घोषणा GL_RGBA4                          0x8056
#घोषणा GL_RGB5_A1                        0x8057
#घोषणा GL_RGB565                         0x8D62
#घोषणा GL_DEPTH_COMPONENT16              0x81A5
#घोषणा GL_STENCIL_INDEX8                 0x8D48
#घोषणा GL_RENDERBUFFER_WIDTH             0x8D42
#घोषणा GL_RENDERBUFFER_HEIGHT            0x8D43
#घोषणा GL_RENDERBUFFER_INTERNAL_FORMAT   0x8D44
#घोषणा GL_RENDERBUFFER_RED_आकार          0x8D50
#घोषणा GL_RENDERBUFFER_GREEN_आकार        0x8D51
#घोषणा GL_RENDERBUFFER_BLUE_आकार         0x8D52
#घोषणा GL_RENDERBUFFER_ALPHA_आकार        0x8D53
#घोषणा GL_RENDERBUFFER_DEPTH_आकार        0x8D54
#घोषणा GL_RENDERBUFFER_STENCIL_आकार      0x8D55
#घोषणा GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE 0x8CD0
#घोषणा GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME 0x8CD1
#घोषणा GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL 0x8CD2
#घोषणा GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE 0x8CD3
#घोषणा GL_COLOR_ATTACHMENT0              0x8CE0
#घोषणा GL_DEPTH_ATTACHMENT               0x8D00
#घोषणा GL_STENCIL_ATTACHMENT             0x8D20
#घोषणा GL_NONE                           0
#घोषणा GL_FRAMEBUFFER_COMPLETE           0x8CD5
#घोषणा GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT 0x8CD6
#घोषणा GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 0x8CD7
#घोषणा GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS 0x8CD9
#घोषणा GL_FRAMEBUFFER_UNSUPPORTED        0x8CDD
#घोषणा GL_FRAMEBUFFER_BINDING            0x8CA6
#घोषणा GL_RENDERBUFFER_BINDING           0x8CA7
#घोषणा GL_MAX_RENDERBUFFER_आकार          0x84E8
#घोषणा GL_INVALID_FRAMEBUFFER_OPERATION  0x0506
प्रकार व्योम (GL_APIENTRYP PFNGLACTIVETEXTUREPROC) (GLenum texture);
प्रकार व्योम (GL_APIENTRYP PFNGLATTACHSHADERPROC) (GLuint program, GLuint shader);
प्रकार व्योम (GL_APIENTRYP PFNGLBINDATTRIBLOCATIONPROC) (GLuint program, GLuint सूचकांक, स्थिर GLchar *name);
प्रकार व्योम (GL_APIENTRYP PFNGLBINDBUFFERPROC) (GLenum target, GLuint बफर_2);
प्रकार व्योम (GL_APIENTRYP PFNGLBINDFRAMEBUFFERPROC) (GLenum target, GLuint framebuffer);
प्रकार व्योम (GL_APIENTRYP PFNGLBINDRENDERBUFFERPROC) (GLenum target, GLuint renderbuffer);
प्रकार व्योम (GL_APIENTRYP PFNGLBINDTEXTUREPROC) (GLenum target, GLuint texture);
प्रकार व्योम (GL_APIENTRYP PFNGLBLENDCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
प्रकार व्योम (GL_APIENTRYP PFNGLBLENDEQUATIONPROC) (GLenum mode);
प्रकार व्योम (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEPROC) (GLenum modeRGB, GLenum modeAlpha);
प्रकार व्योम (GL_APIENTRYP PFNGLBLENDFUNCPROC) (GLenum sfactor, GLenum dfactor);
प्रकार व्योम (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEPROC) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
प्रकार व्योम (GL_APIENTRYP PFNGLBUFFERDATAPROC) (GLenum target, GLsizeiptr आकार, स्थिर व्योम *तथ्य, GLenum usage);
प्रकार व्योम (GL_APIENTRYP PFNGLBUFFERSUBDATAPROC) (GLenum target, GLintptr offset, GLsizeiptr आकार, स्थिर व्योम *तथ्य);
प्रकार GLenum (GL_APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSPROC) (GLenum target);
प्रकार व्योम (GL_APIENTRYP PFNGLCLEARPROC) (GLbitfield mask);
प्रकार व्योम (GL_APIENTRYP PFNGLCLEARCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
प्रकार व्योम (GL_APIENTRYP PFNGLCLEARDEPTHFPROC) (GLfloat d);
प्रकार व्योम (GL_APIENTRYP PFNGLCLEARSTENCILPROC) (GLint s);
प्रकार व्योम (GL_APIENTRYP PFNGLCOLORMASKPROC) (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
प्रकार व्योम (GL_APIENTRYP PFNGLCOMPILESHADERPROC) (GLuint shader);
प्रकार व्योम (GL_APIENTRYP PFNGLCOMPRESSEDTEXIMAGE2DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei image_आकार, स्थिर व्योम *तथ्य);
प्रकार व्योम (GL_APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei image_आकार, स्थिर व्योम *तथ्य);
प्रकार व्योम (GL_APIENTRYP PFNGLCOPYTEXIMAGE2DPROC) (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
प्रकार व्योम (GL_APIENTRYP PFNGLCOPYTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
प्रकार GLuint (GL_APIENTRYP PFNGLCREATEPROGRAMPROC) (व्योम);
प्रकार GLuint (GL_APIENTRYP PFNGLCREATESHADERPROC) (GLenum type);
प्रकार व्योम (GL_APIENTRYP PFNGLCULLFACEPROC) (GLenum mode);
प्रकार व्योम (GL_APIENTRYP PFNGLDELETEBUFFERSPROC) (GLsizei n, स्थिर GLuint *buffers);
प्रकार व्योम (GL_APIENTRYP PFNGLDELETEFRAMEBUFFERSPROC) (GLsizei n, स्थिर GLuint *framebuffers);
प्रकार व्योम (GL_APIENTRYP PFNGLDELETEPROGRAMPROC) (GLuint program);
प्रकार व्योम (GL_APIENTRYP PFNGLDELETERENDERBUFFERSPROC) (GLsizei n, स्थिर GLuint *renderbuffers);
प्रकार व्योम (GL_APIENTRYP PFNGLDELETESHADERPROC) (GLuint shader);
प्रकार व्योम (GL_APIENTRYP PFNGLDELETETEXTURESPROC) (GLsizei n, स्थिर GLuint *textures);
प्रकार व्योम (GL_APIENTRYP PFNGLDEPTHFUNCPROC) (GLenum func);
प्रकार व्योम (GL_APIENTRYP PFNGLDEPTHMASKPROC) (GLboolean flag);
प्रकार व्योम (GL_APIENTRYP PFNGLDEPTHRANGEFPROC) (GLfloat n, GLfloat f);
प्रकार व्योम (GL_APIENTRYP PFNGLDETACHSHADERPROC) (GLuint program, GLuint shader);
प्रकार व्योम (GL_APIENTRYP PFNGLDISABLEPROC) (GLenum cap);
प्रकार व्योम (GL_APIENTRYP PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint सूचकांक);
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWARRAYSPROC) (GLenum mode, GLint first, GLsizei गिनती);
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWELEMENTSPROC) (GLenum mode, GLsizei गिनती, GLenum type, स्थिर व्योम *indices);
प्रकार व्योम (GL_APIENTRYP PFNGLENABLEPROC) (GLenum cap);
प्रकार व्योम (GL_APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint सूचकांक);
प्रकार व्योम (GL_APIENTRYP PFNGLFINISHPROC) (व्योम);
प्रकार व्योम (GL_APIENTRYP PFNGLFLUSHPROC) (व्योम);
प्रकार व्योम (GL_APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFERPROC) (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
प्रकार व्योम (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
प्रकार व्योम (GL_APIENTRYP PFNGLFRONTFACEPROC) (GLenum mode);
प्रकार व्योम (GL_APIENTRYP PFNGLGENBUFFERSPROC) (GLsizei n, GLuint *buffers);
प्रकार व्योम (GL_APIENTRYP PFNGLGENERATEMIPMAPPROC) (GLenum target);
प्रकार व्योम (GL_APIENTRYP PFNGLGENFRAMEBUFFERSPROC) (GLsizei n, GLuint *framebuffers);
प्रकार व्योम (GL_APIENTRYP PFNGLGENRENDERBUFFERSPROC) (GLsizei n, GLuint *renderbuffers);
प्रकार व्योम (GL_APIENTRYP PFNGLGENTEXTURESPROC) (GLsizei n, GLuint *textures);
प्रकार व्योम (GL_APIENTRYP PFNGLGETACTIVEATTRIBPROC) (GLuint program, GLuint सूचकांक, GLsizei buf_आकार, GLsizei *लंबाई, GLint *आकार, GLenum *type, GLchar *name);
प्रकार व्योम (GL_APIENTRYP PFNGLGETACTIVEUNIFORMPROC) (GLuint program, GLuint सूचकांक, GLsizei buf_आकार, GLsizei *लंबाई, GLint *आकार, GLenum *type, GLchar *name);
प्रकार व्योम (GL_APIENTRYP PFNGLGETATTACHEDSHADERSPROC) (GLuint program, GLsizei max_गिनती, GLsizei *गिनती, GLuint *shaders);
प्रकार GLint (GL_APIENTRYP PFNGLGETATTRIBLOCATIONPROC) (GLuint program, स्थिर GLchar *name);
प्रकार व्योम (GL_APIENTRYP PFNGLGETBOOLEANVPROC) (GLenum pname, GLboolean *तथ्य);
प्रकार व्योम (GL_APIENTRYP PFNGLGETBUFFERPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
प्रकार GLenum (GL_APIENTRYP PFNGLGETERRORPROC) (व्योम);
प्रकार व्योम (GL_APIENTRYP PFNGLGETFLOATVPROC) (GLenum pname, GLfloat *तथ्य);
प्रकार व्योम (GL_APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) (GLenum target, GLenum attachment, GLenum pname, GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETINTEGERVPROC) (GLenum pname, GLint *तथ्य);
प्रकार व्योम (GL_APIENTRYP PFNGLGETPROGRAMIVPROC) (GLuint program, GLenum pname, GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETPROGRAMINFOLOGPROC) (GLuint program, GLsizei buf_आकार, GLsizei *लंबाई, GLchar *infoLog);
प्रकार व्योम (GL_APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei buf_आकार, GLsizei *लंबाई, GLchar *infoLog);
प्रकार व्योम (GL_APIENTRYP PFNGLGETSHADERPRECISIONFORMATPROC) (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
प्रकार व्योम (GL_APIENTRYP PFNGLGETSHADERSOURCEPROC) (GLuint shader, GLsizei buf_आकार, GLsizei *लंबाई, GLchar *source);
प्रकार स्थिर GLubyte *(GL_APIENTRYP PFNGLGETSTRINGPROC) (GLenum name);
प्रकार व्योम (GL_APIENTRYP PFNGLGETTEXPARAMETERFVPROC) (GLenum target, GLenum pname, GLfloat *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETTEXPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETUNIFORMFVPROC) (GLuint program, GLint location, GLfloat *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETUNIFORMIVPROC) (GLuint program, GLint location, GLint *params);
प्रकार GLint (GL_APIENTRYP PFNGLGETUNIFORMLOCATIONPROC) (GLuint program, स्थिर GLchar *name);
प्रकार व्योम (GL_APIENTRYP PFNGLGETVERTEXATTRIBFVPROC) (GLuint सूचकांक, GLenum pname, GLfloat *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETVERTEXATTRIBIVPROC) (GLuint सूचकांक, GLenum pname, GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETVERTEXATTRIBPOINTERVPROC) (GLuint सूचकांक, GLenum pname, व्योम **pointer);
प्रकार व्योम (GL_APIENTRYP PFNGLHINTPROC) (GLenum target, GLenum mode);
प्रकार GLboolean (GL_APIENTRYP PFNGLISBUFFERPROC) (GLuint बफर_2);
प्रकार GLboolean (GL_APIENTRYP PFNGLISENABLEDPROC) (GLenum cap);
प्रकार GLboolean (GL_APIENTRYP PFNGLISFRAMEBUFFERPROC) (GLuint framebuffer);
प्रकार GLboolean (GL_APIENTRYP PFNGLISPROGRAMPROC) (GLuint program);
प्रकार GLboolean (GL_APIENTRYP PFNGLISRENDERBUFFERPROC) (GLuint renderbuffer);
प्रकार GLboolean (GL_APIENTRYP PFNGLISSHADERPROC) (GLuint shader);
प्रकार GLboolean (GL_APIENTRYP PFNGLISTEXTUREPROC) (GLuint texture);
प्रकार व्योम (GL_APIENTRYP PFNGLLINEWIDTHPROC) (GLfloat width);
प्रकार व्योम (GL_APIENTRYP PFNGLLINKPROGRAMPROC) (GLuint program);
प्रकार व्योम (GL_APIENTRYP PFNGLPIXELSTOREIPROC) (GLenum pname, GLint param);
प्रकार व्योम (GL_APIENTRYP PFNGLPOLYGONOFFSETPROC) (GLfloat factor, GLfloat units);
प्रकार व्योम (GL_APIENTRYP PFNGLREADPIXELSPROC) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, व्योम *pixels);
प्रकार व्योम (GL_APIENTRYP PFNGLRELEASESHADERCOMPILERPROC) (व्योम);
प्रकार व्योम (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEPROC) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
प्रकार व्योम (GL_APIENTRYP PFNGLSAMPLECOVERAGEPROC) (GLfloat मूल्य, GLboolean invert);
प्रकार व्योम (GL_APIENTRYP PFNGLSCISSORPROC) (GLint x, GLint y, GLsizei width, GLsizei height);
प्रकार व्योम (GL_APIENTRYP PFNGLSHADERBINARYPROC) (GLsizei गिनती, स्थिर GLuint *shaders, GLenum द्विआधारी_Format, स्थिर व्योम *द्विआधारी, GLsizei लंबाई);
प्रकार व्योम (GL_APIENTRYP PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei गिनती, स्थिर GLchar *स्थिर*string, स्थिर GLint *लंबाई);
प्रकार व्योम (GL_APIENTRYP PFNGLSTENCILFUNCPROC) (GLenum func, GLint ref, GLuint mask);
प्रकार व्योम (GL_APIENTRYP PFNGLSTENCILFUNCSEPARATEPROC) (GLenum face, GLenum func, GLint ref, GLuint mask);
प्रकार व्योम (GL_APIENTRYP PFNGLSTENCILMASKPROC) (GLuint mask);
प्रकार व्योम (GL_APIENTRYP PFNGLSTENCILMASKSEPARATEPROC) (GLenum face, GLuint mask);
प्रकार व्योम (GL_APIENTRYP PFNGLSTENCILOPPROC) (GLenum fail, GLenum zfail, GLenum zpass);
प्रकार व्योम (GL_APIENTRYP PFNGLSTENCILOPSEPARATEPROC) (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXIMAGE2DPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, स्थिर व्योम *pixels);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXPARAMETERFPROC) (GLenum target, GLenum pname, GLfloat param);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXPARAMETERFVPROC) (GLenum target, GLenum pname, स्थिर GLfloat *params);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXPARAMETERIPROC) (GLenum target, GLenum pname, GLint param);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXPARAMETERIVPROC) (GLenum target, GLenum pname, स्थिर GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, स्थिर व्योम *pixels);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM1FPROC) (GLint location, GLfloat v0);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM1FVPROC) (GLint location, GLsizei गिनती, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM1IPROC) (GLint location, GLint v0);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM1IVPROC) (GLint location, GLsizei गिनती, स्थिर GLint *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM2FPROC) (GLint location, GLfloat v0, GLfloat v1);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM2FVPROC) (GLint location, GLsizei गिनती, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM2IPROC) (GLint location, GLint v0, GLint v1);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM2IVPROC) (GLint location, GLsizei गिनती, स्थिर GLint *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM3FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM3FVPROC) (GLint location, GLsizei गिनती, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM3IPROC) (GLint location, GLint v0, GLint v1, GLint v2);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM3IVPROC) (GLint location, GLsizei गिनती, स्थिर GLint *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM4FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM4FVPROC) (GLint location, GLsizei गिनती, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM4IPROC) (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM4IVPROC) (GLint location, GLsizei गिनती, स्थिर GLint *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORMMATRIX2FVPROC) (GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORMMATRIX3FVPROC) (GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLUSEPROGRAMPROC) (GLuint program);
प्रकार व्योम (GL_APIENTRYP PFNGLVALIDATEPROGRAMPROC) (GLuint program);
प्रकार व्योम (GL_APIENTRYP PFNGLVERTEXATTRIB1FPROC) (GLuint सूचकांक, GLfloat x);
प्रकार व्योम (GL_APIENTRYP PFNGLVERTEXATTRIB1FVPROC) (GLuint सूचकांक, स्थिर GLfloat *v);
प्रकार व्योम (GL_APIENTRYP PFNGLVERTEXATTRIB2FPROC) (GLuint सूचकांक, GLfloat x, GLfloat y);
प्रकार व्योम (GL_APIENTRYP PFNGLVERTEXATTRIB2FVPROC) (GLuint सूचकांक, स्थिर GLfloat *v);
प्रकार व्योम (GL_APIENTRYP PFNGLVERTEXATTRIB3FPROC) (GLuint सूचकांक, GLfloat x, GLfloat y, GLfloat z);
प्रकार व्योम (GL_APIENTRYP PFNGLVERTEXATTRIB3FVPROC) (GLuint सूचकांक, स्थिर GLfloat *v);
प्रकार व्योम (GL_APIENTRYP PFNGLVERTEXATTRIB4FPROC) (GLuint सूचकांक, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
प्रकार व्योम (GL_APIENTRYP PFNGLVERTEXATTRIB4FVPROC) (GLuint सूचकांक, स्थिर GLfloat *v);
प्रकार व्योम (GL_APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC) (GLuint सूचकांक, GLint आकार, GLenum type, GLboolean normalized, GLsizei stride, स्थिर व्योम *pointer);
प्रकार व्योम (GL_APIENTRYP PFNGLVIEWPORTPROC) (GLint x, GLint y, GLsizei width, GLsizei height);
#अगर GL_GLES_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glActiveTexture (GLenum texture);
GL_APICALL व्योम GL_APIENTRY glAttachShader (GLuint program, GLuint shader);
GL_APICALL व्योम GL_APIENTRY glBindAttribLocation (GLuint program, GLuint सूचकांक, स्थिर GLchar *name);
GL_APICALL व्योम GL_APIENTRY gl_Bind_बफर (GLenum target, GLuint बफर_2);
GL_APICALL व्योम GL_APIENTRY glBindFramebuffer (GLenum target, GLuint framebuffer);
GL_APICALL व्योम GL_APIENTRY glBindRenderbuffer (GLenum target, GLuint renderbuffer);
GL_APICALL व्योम GL_APIENTRY glBindTexture (GLenum target, GLuint texture);
GL_APICALL व्योम GL_APIENTRY glBlendColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_APICALL व्योम GL_APIENTRY glBlendEquation (GLenum mode);
GL_APICALL व्योम GL_APIENTRY glBlendEquationSeparate (GLenum modeRGB, GLenum modeAlpha);
GL_APICALL व्योम GL_APIENTRY glBlendFunc (GLenum sfactor, GLenum dfactor);
GL_APICALL व्योम GL_APIENTRY glBlendFuncSeparate (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
GL_APICALL व्योम GL_APIENTRY gl_बफर_तथ्य (GLenum target, GLsizeiptr आकार, स्थिर व्योम *तथ्य, GLenum usage);
GL_APICALL व्योम GL_APIENTRY gl_बफर_Sub_तथ्य (GLenum target, GLintptr offset, GLsizeiptr आकार, स्थिर व्योम *तथ्य);
GL_APICALL GLenum GL_APIENTRY glCheckFramebufferStatus (GLenum target);
GL_APICALL व्योम GL_APIENTRY glClear (GLbitfield mask);
GL_APICALL व्योम GL_APIENTRY glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_APICALL व्योम GL_APIENTRY glClearDepthf (GLfloat d);
GL_APICALL व्योम GL_APIENTRY glClearStencil (GLint s);
GL_APICALL व्योम GL_APIENTRY glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
GL_APICALL व्योम GL_APIENTRY glCompileShader (GLuint shader);
GL_APICALL व्योम GL_APIENTRY glCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei image_आकार, स्थिर व्योम *तथ्य);
GL_APICALL व्योम GL_APIENTRY glCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei image_आकार, स्थिर व्योम *तथ्य);
GL_APICALL व्योम GL_APIENTRY glCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
GL_APICALL व्योम GL_APIENTRY glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
GL_APICALL GLuint GL_APIENTRY glCreateProgram (व्योम);
GL_APICALL GLuint GL_APIENTRY glCreateShader (GLenum type);
GL_APICALL व्योम GL_APIENTRY glCullFace (GLenum mode);
GL_APICALL व्योम GL_APIENTRY glDeleteBuffers (GLsizei n, स्थिर GLuint *buffers);
GL_APICALL व्योम GL_APIENTRY glDeleteFramebuffers (GLsizei n, स्थिर GLuint *framebuffers);
GL_APICALL व्योम GL_APIENTRY glDeleteProgram (GLuint program);
GL_APICALL व्योम GL_APIENTRY glDeleteRenderbuffers (GLsizei n, स्थिर GLuint *renderbuffers);
GL_APICALL व्योम GL_APIENTRY glDeleteShader (GLuint shader);
GL_APICALL व्योम GL_APIENTRY glDeleteTextures (GLsizei n, स्थिर GLuint *textures);
GL_APICALL व्योम GL_APIENTRY glDepthFunc (GLenum func);
GL_APICALL व्योम GL_APIENTRY glDepthMask (GLboolean flag);
GL_APICALL व्योम GL_APIENTRY glDepthRangef (GLfloat n, GLfloat f);
GL_APICALL व्योम GL_APIENTRY glDetachShader (GLuint program, GLuint shader);
GL_APICALL व्योम GL_APIENTRY glDisable (GLenum cap);
GL_APICALL व्योम GL_APIENTRY glDisableVertexAttribArray (GLuint सूचकांक);
GL_APICALL व्योम GL_APIENTRY glDrawArrays (GLenum mode, GLint first, GLsizei गिनती);
GL_APICALL व्योम GL_APIENTRY glDrawElements (GLenum mode, GLsizei गिनती, GLenum type, स्थिर व्योम *indices);
GL_APICALL व्योम GL_APIENTRY glEnable (GLenum cap);
GL_APICALL व्योम GL_APIENTRY glEnableVertexAttribArray (GLuint सूचकांक);
GL_APICALL व्योम GL_APIENTRY glFinish (व्योम);
GL_APICALL व्योम GL_APIENTRY glFlush (व्योम);
GL_APICALL व्योम GL_APIENTRY glFramebufferRenderbuffer (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
GL_APICALL व्योम GL_APIENTRY glFramebufferTexture2D (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GL_APICALL व्योम GL_APIENTRY glFrontFace (GLenum mode);
GL_APICALL व्योम GL_APIENTRY glGenBuffers (GLsizei n, GLuint *buffers);
GL_APICALL व्योम GL_APIENTRY glGenerateMipmap (GLenum target);
GL_APICALL व्योम GL_APIENTRY glGenFramebuffers (GLsizei n, GLuint *framebuffers);
GL_APICALL व्योम GL_APIENTRY glGenRenderbuffers (GLsizei n, GLuint *renderbuffers);
GL_APICALL व्योम GL_APIENTRY glGenTextures (GLsizei n, GLuint *textures);
GL_APICALL व्योम GL_APIENTRY glGetActiveAttrib (GLuint program, GLuint सूचकांक, GLsizei buf_आकार, GLsizei *लंबाई, GLint *आकार, GLenum *type, GLchar *name);
GL_APICALL व्योम GL_APIENTRY glGetActiveUniform (GLuint program, GLuint सूचकांक, GLsizei buf_आकार, GLsizei *लंबाई, GLint *आकार, GLenum *type, GLchar *name);
GL_APICALL व्योम GL_APIENTRY glGetAttachedShaders (GLuint program, GLsizei max_गिनती, GLsizei *गिनती, GLuint *shaders);
GL_APICALL GLint GL_APIENTRY glGetAttribLocation (GLuint program, स्थिर GLchar *name);
GL_APICALL व्योम GL_APIENTRY glGetBooleanv (GLenum pname, GLboolean *तथ्य);
GL_APICALL व्योम GL_APIENTRY gl_Get_बफर_Parameteriv (GLenum target, GLenum pname, GLint *params);
GL_APICALL GLenum GL_APIENTRY glGetError (व्योम);
GL_APICALL व्योम GL_APIENTRY glGetFloatv (GLenum pname, GLfloat *तथ्य);
GL_APICALL व्योम GL_APIENTRY glGetFramebufferAttachmentParameteriv (GLenum target, GLenum attachment, GLenum pname, GLint *params);
GL_APICALL व्योम GL_APIENTRY glGetIntegerv (GLenum pname, GLint *तथ्य);
GL_APICALL व्योम GL_APIENTRY glGetProgramiv (GLuint program, GLenum pname, GLint *params);
GL_APICALL व्योम GL_APIENTRY glGetProgramInfoLog (GLuint program, GLsizei buf_आकार, GLsizei *लंबाई, GLchar *infoLog);
GL_APICALL व्योम GL_APIENTRY glGetRenderbufferParameteriv (GLenum target, GLenum pname, GLint *params);
GL_APICALL व्योम GL_APIENTRY glGetShaderiv (GLuint shader, GLenum pname, GLint *params);
GL_APICALL व्योम GL_APIENTRY glGetShaderInfoLog (GLuint shader, GLsizei buf_आकार, GLsizei *लंबाई, GLchar *infoLog);
GL_APICALL व्योम GL_APIENTRY glGetShaderPrecisionFormat (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
GL_APICALL व्योम GL_APIENTRY glGetShaderSource (GLuint shader, GLsizei buf_आकार, GLsizei *लंबाई, GLchar *source);
GL_APICALL स्थिर GLubyte *GL_APIENTRY glGetString (GLenum name);
GL_APICALL व्योम GL_APIENTRY glGetTexParameterfv (GLenum target, GLenum pname, GLfloat *params);
GL_APICALL व्योम GL_APIENTRY glGetTexParameteriv (GLenum target, GLenum pname, GLint *params);
GL_APICALL व्योम GL_APIENTRY glGetUniformfv (GLuint program, GLint location, GLfloat *params);
GL_APICALL व्योम GL_APIENTRY glGetUniformiv (GLuint program, GLint location, GLint *params);
GL_APICALL GLint GL_APIENTRY glGetUniformLocation (GLuint program, स्थिर GLchar *name);
GL_APICALL व्योम GL_APIENTRY glGetVertexAttribfv (GLuint सूचकांक, GLenum pname, GLfloat *params);
GL_APICALL व्योम GL_APIENTRY glGetVertexAttribiv (GLuint सूचकांक, GLenum pname, GLint *params);
GL_APICALL व्योम GL_APIENTRY glGetVertexAttribPointerv (GLuint सूचकांक, GLenum pname, व्योम **pointer);
GL_APICALL व्योम GL_APIENTRY glHint (GLenum target, GLenum mode);
GL_APICALL GLboolean GL_APIENTRY gl_Is_बफर (GLuint बफर_2);
GL_APICALL GLboolean GL_APIENTRY glIsEnabled (GLenum cap);
GL_APICALL GLboolean GL_APIENTRY glIsFramebuffer (GLuint framebuffer);
GL_APICALL GLboolean GL_APIENTRY glIsProgram (GLuint program);
GL_APICALL GLboolean GL_APIENTRY glIsRenderbuffer (GLuint renderbuffer);
GL_APICALL GLboolean GL_APIENTRY glIsShader (GLuint shader);
GL_APICALL GLboolean GL_APIENTRY glIsTexture (GLuint texture);
GL_APICALL व्योम GL_APIENTRY gl_पंक्ति_Width (GLfloat width);
GL_APICALL व्योम GL_APIENTRY glLinkProgram (GLuint program);
GL_APICALL व्योम GL_APIENTRY glPixelStorei (GLenum pname, GLint param);
GL_APICALL व्योम GL_APIENTRY glPolygonOffset (GLfloat factor, GLfloat units);
GL_APICALL व्योम GL_APIENTRY glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, व्योम *pixels);
GL_APICALL व्योम GL_APIENTRY glReleaseShaderCompiler (व्योम);
GL_APICALL व्योम GL_APIENTRY glRenderbufferStorage (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
GL_APICALL व्योम GL_APIENTRY glSampleCoverage (GLfloat मूल्य, GLboolean invert);
GL_APICALL व्योम GL_APIENTRY glScissor (GLint x, GLint y, GLsizei width, GLsizei height);
GL_APICALL व्योम GL_APIENTRY gl_Shader_द्विआधारी (GLsizei गिनती, स्थिर GLuint *shaders, GLenum द्विआधारी_Format, स्थिर व्योम *द्विआधारी, GLsizei लंबाई);
GL_APICALL व्योम GL_APIENTRY glShaderSource (GLuint shader, GLsizei गिनती, स्थिर GLchar *स्थिर*string, स्थिर GLint *लंबाई);
GL_APICALL व्योम GL_APIENTRY glStencilFunc (GLenum func, GLint ref, GLuint mask);
GL_APICALL व्योम GL_APIENTRY glStencilFuncSeparate (GLenum face, GLenum func, GLint ref, GLuint mask);
GL_APICALL व्योम GL_APIENTRY glStencilMask (GLuint mask);
GL_APICALL व्योम GL_APIENTRY glStencilMaskSeparate (GLenum face, GLuint mask);
GL_APICALL व्योम GL_APIENTRY glStencilOp (GLenum fail, GLenum zfail, GLenum zpass);
GL_APICALL व्योम GL_APIENTRY glStencilOpSeparate (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
GL_APICALL व्योम GL_APIENTRY glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, स्थिर व्योम *pixels);
GL_APICALL व्योम GL_APIENTRY glTexParameterf (GLenum target, GLenum pname, GLfloat param);
GL_APICALL व्योम GL_APIENTRY glTexParameterfv (GLenum target, GLenum pname, स्थिर GLfloat *params);
GL_APICALL व्योम GL_APIENTRY glTexParameteri (GLenum target, GLenum pname, GLint param);
GL_APICALL व्योम GL_APIENTRY glTexParameteriv (GLenum target, GLenum pname, स्थिर GLint *params);
GL_APICALL व्योम GL_APIENTRY glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, स्थिर व्योम *pixels);
GL_APICALL व्योम GL_APIENTRY glUniform1f (GLint location, GLfloat v0);
GL_APICALL व्योम GL_APIENTRY glUniform1fv (GLint location, GLsizei गिनती, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glUniform1i (GLint location, GLint v0);
GL_APICALL व्योम GL_APIENTRY glUniform1iv (GLint location, GLsizei गिनती, स्थिर GLint *मूल्य);
GL_APICALL व्योम GL_APIENTRY glUniform2f (GLint location, GLfloat v0, GLfloat v1);
GL_APICALL व्योम GL_APIENTRY glUniform2fv (GLint location, GLsizei गिनती, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glUniform2i (GLint location, GLint v0, GLint v1);
GL_APICALL व्योम GL_APIENTRY glUniform2iv (GLint location, GLsizei गिनती, स्थिर GLint *मूल्य);
GL_APICALL व्योम GL_APIENTRY glUniform3f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
GL_APICALL व्योम GL_APIENTRY glUniform3fv (GLint location, GLsizei गिनती, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glUniform3i (GLint location, GLint v0, GLint v1, GLint v2);
GL_APICALL व्योम GL_APIENTRY glUniform3iv (GLint location, GLsizei गिनती, स्थिर GLint *मूल्य);
GL_APICALL व्योम GL_APIENTRY glUniform4f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
GL_APICALL व्योम GL_APIENTRY glUniform4fv (GLint location, GLsizei गिनती, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glUniform4i (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
GL_APICALL व्योम GL_APIENTRY glUniform4iv (GLint location, GLsizei गिनती, स्थिर GLint *मूल्य);
GL_APICALL व्योम GL_APIENTRY glUniformMatrix2fv (GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glUniformMatrix3fv (GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glUniformMatrix4fv (GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glUseProgram (GLuint program);
GL_APICALL व्योम GL_APIENTRY glValidateProgram (GLuint program);
GL_APICALL व्योम GL_APIENTRY glVertexAttrib1f (GLuint सूचकांक, GLfloat x);
GL_APICALL व्योम GL_APIENTRY glVertexAttrib1fv (GLuint सूचकांक, स्थिर GLfloat *v);
GL_APICALL व्योम GL_APIENTRY glVertexAttrib2f (GLuint सूचकांक, GLfloat x, GLfloat y);
GL_APICALL व्योम GL_APIENTRY glVertexAttrib2fv (GLuint सूचकांक, स्थिर GLfloat *v);
GL_APICALL व्योम GL_APIENTRY glVertexAttrib3f (GLuint सूचकांक, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL व्योम GL_APIENTRY glVertexAttrib3fv (GLuint सूचकांक, स्थिर GLfloat *v);
GL_APICALL व्योम GL_APIENTRY glVertexAttrib4f (GLuint सूचकांक, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
GL_APICALL व्योम GL_APIENTRY glVertexAttrib4fv (GLuint सूचकांक, स्थिर GLfloat *v);
GL_APICALL व्योम GL_APIENTRY glVertexAttribPointer (GLuint सूचकांक, GLint आकार, GLenum type, GLboolean normalized, GLsizei stride, स्थिर व्योम *pointer);
GL_APICALL व्योम GL_APIENTRY glViewport (GLint x, GLint y, GLsizei width, GLsizei height);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_ES_VERSION_2_0 */

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर
