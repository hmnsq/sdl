#अगर_अघोषित __gles2_gl32_h_
#घोषणा __gles2_gl32_h_ 1

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

#समावेश <GLES3/gl3platform.h>

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
 * Versions considered: 2\.[0-9]|3\.[012]
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

#अगर_अघोषित GL_ES_VERSION_3_0
#घोषणा GL_ES_VERSION_3_0 1
प्रकार khronos_uint16_t GLhalf;
#घोषणा GL_READ_बफर                    0x0C02
#घोषणा GL_UNPACK_ROW_लंबाई              0x0CF2
#घोषणा GL_UNPACK_SKIP_ROWS               0x0CF3
#घोषणा GL_UNPACK_SKIP_PIXELS             0x0CF4
#घोषणा GL_PACK_ROW_लंबाई                0x0D02
#घोषणा GL_PACK_SKIP_ROWS                 0x0D03
#घोषणा GL_PACK_SKIP_PIXELS               0x0D04
#घोषणा GL_COLOR                          0x1800
#घोषणा GL_DEPTH                          0x1801
#घोषणा GL_STENCIL                        0x1802
#घोषणा GL_RED                            0x1903
#घोषणा GL_RGB8                           0x8051
#घोषणा GL_RGBA8                          0x8058
#घोषणा GL_RGB10_A2                       0x8059
#घोषणा GL_TEXTURE_BINDING_3D             0x806A
#घोषणा GL_UNPACK_SKIP_IMAGES             0x806D
#घोषणा GL_UNPACK_IMAGE_HEIGHT            0x806E
#घोषणा GL_TEXTURE_3D                     0x806F
#घोषणा GL_TEXTURE_WRAP_R                 0x8072
#घोषणा GL_MAX_3_D_TEXTURE_आकार            0x8073
#घोषणा GL_UNSIGNED_INT_2_10_10_10_REV    0x8368
#घोषणा GL_MAX_ELEMENTS_VERTICES          0x80E8
#घोषणा GL_MAX_ELEMENTS_INDICES           0x80E9
#घोषणा GL_TEXTURE_MIN_LOD                0x813A
#घोषणा GL_TEXTURE_MAX_LOD                0x813B
#घोषणा GL_TEXTURE_BASE_LEVEL             0x813C
#घोषणा GL_TEXTURE_MAX_LEVEL              0x813D
#घोषणा GL_MIN                            0x8007
#घोषणा GL_MAX                            0x8008
#घोषणा GL_DEPTH_COMPONENT24              0x81A6
#घोषणा GL_MAX_TEXTURE_LOD_BIAS           0x84FD
#घोषणा GL_TEXTURE_COMPARE_MODE           0x884C
#घोषणा GL_TEXTURE_COMPARE_FUNC           0x884D
#घोषणा GL_CURRENT_QUERY                  0x8865
#घोषणा GL_QUERY_परिणाम                   0x8866
#घोषणा GL_QUERY_परिणाम_AVAILABLE         0x8867
#घोषणा GL_बफर_MAPPED                  0x88BC
#घोषणा GL_बफर_MAP_POINTER             0x88BD
#घोषणा GL_STREAM_READ                    0x88E1
#घोषणा GL_STREAM_COPY                    0x88E2
#घोषणा GL_STATIC_READ                    0x88E5
#घोषणा GL_STATIC_COPY                    0x88E6
#घोषणा GL_DYNAMIC_READ                   0x88E9
#घोषणा GL_DYNAMIC_COPY                   0x88EA
#घोषणा GL_MAX_DRAW_BUFFERS               0x8824
#घोषणा GL_DRAW_BUFFER0                   0x8825
#घोषणा GL_DRAW_BUFFER1                   0x8826
#घोषणा GL_DRAW_BUFFER2                   0x8827
#घोषणा GL_DRAW_BUFFER3                   0x8828
#घोषणा GL_DRAW_BUFFER4                   0x8829
#घोषणा GL_DRAW_BUFFER5                   0x882A
#घोषणा GL_DRAW_BUFFER6                   0x882B
#घोषणा GL_DRAW_BUFFER7                   0x882C
#घोषणा GL_DRAW_BUFFER8                   0x882D
#घोषणा GL_DRAW_BUFFER9                   0x882E
#घोषणा GL_DRAW_BUFFER10                  0x882F
#घोषणा GL_DRAW_BUFFER11                  0x8830
#घोषणा GL_DRAW_BUFFER12                  0x8831
#घोषणा GL_DRAW_BUFFER13                  0x8832
#घोषणा GL_DRAW_BUFFER14                  0x8833
#घोषणा GL_DRAW_BUFFER15                  0x8834
#घोषणा GL_MAX_FRAGMENT_UNIFORM_COMPONENTS 0x8B49
#घोषणा GL_MAX_VERTEX_UNIFORM_COMPONENTS  0x8B4A
#घोषणा GL_SAMPLER_3D                     0x8B5F
#घोषणा GL_SAMPLER_2D_SHADOW              0x8B62
#घोषणा GL_FRAGMENT_SHADER_DERIVATIVE_HINT 0x8B8B
#घोषणा GL_PIXEL_PACK_बफर              0x88EB
#घोषणा GL_PIXEL_UNPACK_बफर            0x88EC
#घोषणा GL_PIXEL_PACK_बफर_BINDING      0x88ED
#घोषणा GL_PIXEL_UNPACK_बफर_BINDING    0x88EF
#घोषणा GL_FLOAT_MAT2x3                   0x8B65
#घोषणा GL_FLOAT_MAT2x4                   0x8B66
#घोषणा GL_FLOAT_MAT3x2                   0x8B67
#घोषणा GL_FLOAT_MAT3x4                   0x8B68
#घोषणा GL_FLOAT_MAT4x2                   0x8B69
#घोषणा GL_FLOAT_MAT4x3                   0x8B6A
#घोषणा GL_SRGB                           0x8C40
#घोषणा GL_SRGB8                          0x8C41
#घोषणा GL_SRGB8_ALPHA8                   0x8C43
#घोषणा GL_COMPARE_REF_TO_TEXTURE         0x884E
#घोषणा GL_MAJOR_VERSION                  0x821B
#घोषणा GL_MINOR_VERSION                  0x821C
#घोषणा GL_अंक_EXTENSIONS                 0x821D
#घोषणा GL_RGBA32F                        0x8814
#घोषणा GL_RGB32F                         0x8815
#घोषणा GL_RGBA16F                        0x881A
#घोषणा GL_RGB16F                         0x881B
#घोषणा GL_VERTEX_ATTRIB_ARRAY_INTEGER    0x88FD
#घोषणा GL_MAX_ARRAY_TEXTURE_LAYERS       0x88FF
#घोषणा GL_MIN_PROGRAM_TEXEL_OFFSET       0x8904
#घोषणा GL_MAX_PROGRAM_TEXEL_OFFSET       0x8905
#घोषणा GL_MAX_VARYING_COMPONENTS         0x8B4B
#घोषणा GL_TEXTURE_2D_ARRAY               0x8C1A
#घोषणा GL_TEXTURE_BINDING_2D_ARRAY       0x8C1D
#घोषणा GL_R11F_G11F_B10F                 0x8C3A
#घोषणा GL_UNSIGNED_INT_10F_11F_11F_REV   0x8C3B
#घोषणा GL_RGB9_E5                        0x8C3D
#घोषणा GL_UNSIGNED_INT_5_9_9_9_REV       0x8C3E
#घोषणा GL_TRANSFORM_FEEDBACK_VARYING_MAX_लंबाई 0x8C76
#घोषणा GL_TRANSFORM_FEEDBACK_बफर_MODE 0x8C7F
#घोषणा GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS 0x8C80
#घोषणा GL_TRANSFORM_FEEDBACK_VARYINGS    0x8C83
#घोषणा GL_TRANSFORM_FEEDBACK_बफर_START 0x8C84
#घोषणा GL_TRANSFORM_FEEDBACK_बफर_आकार 0x8C85
#घोषणा GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN 0x8C88
#घोषणा GL_RASTERIZER_DISCARD             0x8C89
#घोषणा GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS 0x8C8A
#घोषणा GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS 0x8C8B
#घोषणा GL_INTERLEAVED_ATTRIBS            0x8C8C
#घोषणा GL_SEPARATE_ATTRIBS               0x8C8D
#घोषणा GL_TRANSFORM_FEEDBACK_बफर      0x8C8E
#घोषणा GL_TRANSFORM_FEEDBACK_बफर_BINDING 0x8C8F
#घोषणा GL_RGBA32UI                       0x8D70
#घोषणा GL_RGB32UI                        0x8D71
#घोषणा GL_RGBA16UI                       0x8D76
#घोषणा GL_RGB16UI                        0x8D77
#घोषणा GL_RGBA8UI                        0x8D7C
#घोषणा GL_RGB8UI                         0x8D7D
#घोषणा GL_RGBA32I                        0x8D82
#घोषणा GL_RGB32I                         0x8D83
#घोषणा GL_RGBA16I                        0x8D88
#घोषणा GL_RGB16I                         0x8D89
#घोषणा GL_RGBA8I                         0x8D8E
#घोषणा GL_RGB8I                          0x8D8F
#घोषणा GL_RED_INTEGER                    0x8D94
#घोषणा GL_RGB_INTEGER                    0x8D98
#घोषणा GL_RGBA_INTEGER                   0x8D99
#घोषणा GL_SAMPLER_2D_ARRAY               0x8DC1
#घोषणा GL_SAMPLER_2D_ARRAY_SHADOW        0x8DC4
#घोषणा GL_SAMPLER_CUBE_SHADOW            0x8DC5
#घोषणा GL_UNSIGNED_INT_VEC2              0x8DC6
#घोषणा GL_UNSIGNED_INT_VEC3              0x8DC7
#घोषणा GL_UNSIGNED_INT_VEC4              0x8DC8
#घोषणा GL_INT_SAMPLER_2D                 0x8DCA
#घोषणा GL_INT_SAMPLER_3D                 0x8DCB
#घोषणा GL_INT_SAMPLER_CUBE               0x8DCC
#घोषणा GL_INT_SAMPLER_2D_ARRAY           0x8DCF
#घोषणा GL_UNSIGNED_INT_SAMPLER_2D        0x8DD2
#घोषणा GL_UNSIGNED_INT_SAMPLER_3D        0x8DD3
#घोषणा GL_UNSIGNED_INT_SAMPLER_CUBE      0x8DD4
#घोषणा GL_UNSIGNED_INT_SAMPLER_2D_ARRAY  0x8DD7
#घोषणा GL_बफर_ACCESS_FLAGS            0x911F
#घोषणा GL_बफर_MAP_लंबाई              0x9120
#घोषणा GL_बफर_MAP_OFFSET              0x9121
#घोषणा GL_DEPTH_COMPONENT32F             0x8CAC
#घोषणा GL_DEPTH32F_STENCIL8              0x8CAD
#घोषणा GL_FLOAT_32_UNSIGNED_INT_24_8_REV 0x8DAD
#घोषणा GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING 0x8210
#घोषणा GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE 0x8211
#घोषणा GL_FRAMEBUFFER_ATTACHMENT_RED_आकार 0x8212
#घोषणा GL_FRAMEBUFFER_ATTACHMENT_GREEN_आकार 0x8213
#घोषणा GL_FRAMEBUFFER_ATTACHMENT_BLUE_आकार 0x8214
#घोषणा GL_FRAMEBUFFER_ATTACHMENT_ALPHA_आकार 0x8215
#घोषणा GL_FRAMEBUFFER_ATTACHMENT_DEPTH_आकार 0x8216
#घोषणा GL_FRAMEBUFFER_ATTACHMENT_STENCIL_आकार 0x8217
#घोषणा GL_FRAMEBUFFER_DEFAULT            0x8218
#घोषणा GL_FRAMEBUFFER_UNDEFINED          0x8219
#घोषणा GL_DEPTH_STENCIL_ATTACHMENT       0x821A
#घोषणा GL_DEPTH_STENCIL                  0x84F9
#घोषणा GL_UNSIGNED_INT_24_8              0x84FA
#घोषणा GL_DEPTH24_STENCIL8               0x88F0
#घोषणा GL_UNSIGNED_NORMALIZED            0x8C17
#घोषणा GL_DRAW_FRAMEBUFFER_BINDING       0x8CA6
#घोषणा GL_READ_FRAMEBUFFER               0x8CA8
#घोषणा GL_DRAW_FRAMEBUFFER               0x8CA9
#घोषणा GL_READ_FRAMEBUFFER_BINDING       0x8CAA
#घोषणा GL_RENDERBUFFER_SAMPLES           0x8CAB
#घोषणा GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER 0x8CD4
#घोषणा GL_MAX_COLOR_ATTACHMENTS          0x8CDF
#घोषणा GL_COLOR_ATTACHMENT1              0x8CE1
#घोषणा GL_COLOR_ATTACHMENT2              0x8CE2
#घोषणा GL_COLOR_ATTACHMENT3              0x8CE3
#घोषणा GL_COLOR_ATTACHMENT4              0x8CE4
#घोषणा GL_COLOR_ATTACHMENT5              0x8CE5
#घोषणा GL_COLOR_ATTACHMENT6              0x8CE6
#घोषणा GL_COLOR_ATTACHMENT7              0x8CE7
#घोषणा GL_COLOR_ATTACHMENT8              0x8CE8
#घोषणा GL_COLOR_ATTACHMENT9              0x8CE9
#घोषणा GL_COLOR_ATTACHMENT10             0x8CEA
#घोषणा GL_COLOR_ATTACHMENT11             0x8CEB
#घोषणा GL_COLOR_ATTACHMENT12             0x8CEC
#घोषणा GL_COLOR_ATTACHMENT13             0x8CED
#घोषणा GL_COLOR_ATTACHMENT14             0x8CEE
#घोषणा GL_COLOR_ATTACHMENT15             0x8CEF
#घोषणा GL_COLOR_ATTACHMENT16             0x8CF0
#घोषणा GL_COLOR_ATTACHMENT17             0x8CF1
#घोषणा GL_COLOR_ATTACHMENT18             0x8CF2
#घोषणा GL_COLOR_ATTACHMENT19             0x8CF3
#घोषणा GL_COLOR_ATTACHMENT20             0x8CF4
#घोषणा GL_COLOR_ATTACHMENT21             0x8CF5
#घोषणा GL_COLOR_ATTACHMENT22             0x8CF6
#घोषणा GL_COLOR_ATTACHMENT23             0x8CF7
#घोषणा GL_COLOR_ATTACHMENT24             0x8CF8
#घोषणा GL_COLOR_ATTACHMENT25             0x8CF9
#घोषणा GL_COLOR_ATTACHMENT26             0x8CFA
#घोषणा GL_COLOR_ATTACHMENT27             0x8CFB
#घोषणा GL_COLOR_ATTACHMENT28             0x8CFC
#घोषणा GL_COLOR_ATTACHMENT29             0x8CFD
#घोषणा GL_COLOR_ATTACHMENT30             0x8CFE
#घोषणा GL_COLOR_ATTACHMENT31             0x8CFF
#घोषणा GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE 0x8D56
#घोषणा GL_MAX_SAMPLES                    0x8D57
#घोषणा GL_HALF_FLOAT                     0x140B
#घोषणा GL_MAP_READ_BIT                   0x0001
#घोषणा GL_MAP_WRITE_BIT                  0x0002
#घोषणा GL_MAP_INVALIDATE_RANGE_BIT       0x0004
#घोषणा GL_MAP_INVALIDATE_बफर_BIT      0x0008
#घोषणा GL_MAP_FLUSH_EXPLICIT_BIT         0x0010
#घोषणा GL_MAP_UNSYNCHRONIZED_BIT         0x0020
#घोषणा GL_RG                             0x8227
#घोषणा GL_RG_INTEGER                     0x8228
#घोषणा GL_R8                             0x8229
#घोषणा GL_RG8                            0x822B
#घोषणा GL_R16F                           0x822D
#घोषणा GL_R32F                           0x822E
#घोषणा GL_RG16F                          0x822F
#घोषणा GL_RG32F                          0x8230
#घोषणा GL_R8I                            0x8231
#घोषणा GL_R8UI                           0x8232
#घोषणा GL_R16I                           0x8233
#घोषणा GL_R16UI                          0x8234
#घोषणा GL_R32I                           0x8235
#घोषणा GL_R32UI                          0x8236
#घोषणा GL_RG8I                           0x8237
#घोषणा GL_RG8UI                          0x8238
#घोषणा GL_RG16I                          0x8239
#घोषणा GL_RG16UI                         0x823A
#घोषणा GL_RG32I                          0x823B
#घोषणा GL_RG32UI                         0x823C
#घोषणा GL_VERTEX_ARRAY_BINDING           0x85B5
#घोषणा GL_R8_SNORM                       0x8F94
#घोषणा GL_RG8_SNORM                      0x8F95
#घोषणा GL_RGB8_SNORM                     0x8F96
#घोषणा GL_RGBA8_SNORM                    0x8F97
#घोषणा GL_SIGNED_NORMALIZED              0x8F9C
#घोषणा GL_PRIMITIVE_RESTART_FIXED_सूचकांक  0x8D69
#घोषणा GL_COPY_READ_बफर               0x8F36
#घोषणा GL_COPY_WRITE_बफर              0x8F37
#घोषणा GL_COPY_READ_बफर_BINDING       0x8F36
#घोषणा GL_COPY_WRITE_बफर_BINDING      0x8F37
#घोषणा GL_UNIFORM_बफर                 0x8A11
#घोषणा GL_UNIFORM_बफर_BINDING         0x8A28
#घोषणा GL_UNIFORM_बफर_START           0x8A29
#घोषणा GL_UNIFORM_बफर_आकार            0x8A2A
#घोषणा GL_MAX_VERTEX_UNIFORM_BLOCKS      0x8A2B
#घोषणा GL_MAX_FRAGMENT_UNIFORM_BLOCKS    0x8A2D
#घोषणा GL_MAX_COMBINED_UNIFORM_BLOCKS    0x8A2E
#घोषणा GL_MAX_UNIFORM_बफर_BINDINGS    0x8A2F
#घोषणा GL_MAX_UNIFORM_BLOCK_आकार         0x8A30
#घोषणा GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS 0x8A31
#घोषणा GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS 0x8A33
#घोषणा GL_UNIFORM_बफर_OFFSET_ALIGNMENT 0x8A34
#घोषणा GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_लंबाई 0x8A35
#घोषणा GL_ACTIVE_UNIFORM_BLOCKS          0x8A36
#घोषणा GL_UNIFORM_TYPE                   0x8A37
#घोषणा GL_UNIFORM_आकार                   0x8A38
#घोषणा GL_UNIFORM_NAME_लंबाई            0x8A39
#घोषणा GL_UNIFORM_BLOCK_सूचकांक            0x8A3A
#घोषणा GL_UNIFORM_OFFSET                 0x8A3B
#घोषणा GL_UNIFORM_ARRAY_STRIDE           0x8A3C
#घोषणा GL_UNIFORM_MATRIX_STRIDE          0x8A3D
#घोषणा GL_UNIFORM_IS_ROW_MAJOR           0x8A3E
#घोषणा GL_UNIFORM_BLOCK_BINDING          0x8A3F
#घोषणा GL_UNIFORM_BLOCK_तथ्य_आकार        0x8A40
#घोषणा GL_UNIFORM_BLOCK_NAME_लंबाई      0x8A41
#घोषणा GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS  0x8A42
#घोषणा GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES 0x8A43
#घोषणा GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER 0x8A44
#घोषणा GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER 0x8A46
#घोषणा GL_INVALID_सूचकांक                  0xFFFFFFFFu
#घोषणा GL_MAX_VERTEX_OUTPUT_COMPONENTS   0x9122
#घोषणा GL_MAX_FRAGMENT_निवेश_COMPONENTS  0x9125
#घोषणा GL_MAX_SERVER_WAIT_TIMEOUT        0x9111
#घोषणा GL_OBJECT_TYPE                    0x9112
#घोषणा GL_SYNC_CONDITION                 0x9113
#घोषणा GL_SYNC_STATUS                    0x9114
#घोषणा GL_SYNC_FLAGS                     0x9115
#घोषणा GL_SYNC_FENCE                     0x9116
#घोषणा GL_SYNC_GPU_COMMANDS_COMPLETE     0x9117
#घोषणा GL_UNSIGNALED                     0x9118
#घोषणा GL_SIGNALED                       0x9119
#घोषणा GL_ALREADY_SIGNALED               0x911A
#घोषणा GL_TIMEOUT_EXPIRED                0x911B
#घोषणा GL_CONDITION_SATISFIED            0x911C
#घोषणा GL_WAIT_FAILED                    0x911D
#घोषणा GL_SYNC_FLUSH_COMMANDS_BIT        0x00000001
#घोषणा GL_TIMEOUT_IGNORED                0xFFFFFFFFFFFFFFFFull
#घोषणा GL_VERTEX_ATTRIB_ARRAY_भाजक    0x88FE
#घोषणा GL_ANY_SAMPLES_PASSED             0x8C2F
#घोषणा GL_ANY_SAMPLES_PASSED_CONSERVATIVE 0x8D6A
#घोषणा GL_SAMPLER_BINDING                0x8919
#घोषणा GL_RGB10_A2UI                     0x906F
#घोषणा GL_TEXTURE_SWIZZLE_R              0x8E42
#घोषणा GL_TEXTURE_SWIZZLE_G              0x8E43
#घोषणा GL_TEXTURE_SWIZZLE_B              0x8E44
#घोषणा GL_TEXTURE_SWIZZLE_A              0x8E45
#घोषणा GL_GREEN                          0x1904
#घोषणा GL_BLUE                           0x1905
#घोषणा GL_INT_2_10_10_10_REV             0x8D9F
#घोषणा GL_TRANSFORM_FEEDBACK             0x8E22
#घोषणा GL_TRANSFORM_FEEDBACK_PAUSED      0x8E23
#घोषणा GL_TRANSFORM_FEEDBACK_ACTIVE      0x8E24
#घोषणा GL_TRANSFORM_FEEDBACK_BINDING     0x8E25
#घोषणा GL_PROGRAM_द्विआधारी_RETRIEVABLE_HINT 0x8257
#घोषणा GL_PROGRAM_द्विआधारी_लंबाई          0x8741
#घोषणा GL_अंक_PROGRAM_द्विआधारी_FORMATS     0x87FE
#घोषणा GL_PROGRAM_द्विआधारी_FORMATS         0x87FF
#घोषणा GL_COMPRESSED_R11_EAC             0x9270
#घोषणा GL_COMPRESSED_SIGNED_R11_EAC      0x9271
#घोषणा GL_COMPRESSED_RG11_EAC            0x9272
#घोषणा GL_COMPRESSED_SIGNED_RG11_EAC     0x9273
#घोषणा GL_COMPRESSED_RGB8_ETC2           0x9274
#घोषणा GL_COMPRESSED_SRGB8_ETC2          0x9275
#घोषणा GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9276
#घोषणा GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9277
#घोषणा GL_COMPRESSED_RGBA8_ETC2_EAC      0x9278
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC 0x9279
#घोषणा GL_TEXTURE_IMMUTABLE_FORMAT       0x912F
#घोषणा GL_MAX_ELEMENT_सूचकांक              0x8D6B
#घोषणा GL_अंक_SAMPLE_COUNTS              0x9380
#घोषणा GL_TEXTURE_IMMUTABLE_LEVELS       0x82DF
प्रकार व्योम (GL_APIENTRYP PFNGLREADBUFFERPROC) (GLenum src);
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWRANGEELEMENTSPROC) (GLenum mode, GLuint start, GLuint end, GLsizei गिनती, GLenum type, स्थिर व्योम *indices);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXIMAGE3DPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, स्थिर व्योम *pixels);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, स्थिर व्योम *pixels);
प्रकार व्योम (GL_APIENTRYP PFNGLCOPYTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
प्रकार व्योम (GL_APIENTRYP PFNGLCOMPRESSEDTEXIMAGE3DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei image_आकार, स्थिर व्योम *तथ्य);
प्रकार व्योम (GL_APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei image_आकार, स्थिर व्योम *तथ्य);
प्रकार व्योम (GL_APIENTRYP PFNGLGENQUERIESPROC) (GLsizei n, GLuint *ids);
प्रकार व्योम (GL_APIENTRYP PFNGLDELETEQUERIESPROC) (GLsizei n, स्थिर GLuint *ids);
प्रकार GLboolean (GL_APIENTRYP PFNGLISQUERYPROC) (GLuint id);
प्रकार व्योम (GL_APIENTRYP PFNGLBEGINQUERYPROC) (GLenum target, GLuint id);
प्रकार व्योम (GL_APIENTRYP PFNGLENDQUERYPROC) (GLenum target);
प्रकार व्योम (GL_APIENTRYP PFNGLGETQUERYIVPROC) (GLenum target, GLenum pname, GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETQUERYOBJECTUIVPROC) (GLuint id, GLenum pname, GLuint *params);
प्रकार GLboolean (GL_APIENTRYP PFNGLUNMAPBUFFERPROC) (GLenum target);
प्रकार व्योम (GL_APIENTRYP PFNGLGETBUFFERPOINTERVPROC) (GLenum target, GLenum pname, व्योम **params);
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWBUFFERSPROC) (GLsizei n, स्थिर GLenum *bufs);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORMMATRIX2X3FVPROC) (GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORMMATRIX3X2FVPROC) (GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORMMATRIX2X4FVPROC) (GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORMMATRIX4X2FVPROC) (GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORMMATRIX3X4FVPROC) (GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORMMATRIX4X3FVPROC) (GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLBLITFRAMEBUFFERPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
प्रकार व्योम (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
प्रकार व्योम (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURELAYERPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
प्रकार व्योम *(GL_APIENTRYP PFNGLMAPBUFFERRANGEPROC) (GLenum target, GLintptr offset, GLsizeiptr लंबाई, GLbitfield access);
प्रकार व्योम (GL_APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEPROC) (GLenum target, GLintptr offset, GLsizeiptr लंबाई);
प्रकार व्योम (GL_APIENTRYP PFNGLBINDVERTEXARRAYPROC) (GLuint array);
प्रकार व्योम (GL_APIENTRYP PFNGLDELETEVERTEXARRAYSPROC) (GLsizei n, स्थिर GLuint *arrays);
प्रकार व्योम (GL_APIENTRYP PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint *arrays);
प्रकार GLboolean (GL_APIENTRYP PFNGLISVERTEXARRAYPROC) (GLuint array);
प्रकार व्योम (GL_APIENTRYP PFNGLGETINTEGERI_VPROC) (GLenum target, GLuint सूचकांक, GLint *तथ्य);
प्रकार व्योम (GL_APIENTRYP PFNGLBEGINTRANSFORMFEEDBACKPROC) (GLenum primitiveMode);
प्रकार व्योम (GL_APIENTRYP PFNGLENDTRANSFORMFEEDBACKPROC) (व्योम);
प्रकार व्योम (GL_APIENTRYP PFNGLBINDBUFFERRANGEPROC) (GLenum target, GLuint सूचकांक, GLuint बफर_2, GLintptr offset, GLsizeiptr आकार);
प्रकार व्योम (GL_APIENTRYP PFNGLBINDBUFFERBASEPROC) (GLenum target, GLuint सूचकांक, GLuint बफर_2);
प्रकार व्योम (GL_APIENTRYP PFNGLTRANSFORMFEEDBACKVARYINGSPROC) (GLuint program, GLsizei गिनती, स्थिर GLchar *स्थिर*varyings, GLenum बफर_Mode);
प्रकार व्योम (GL_APIENTRYP PFNGLGETTRANSFORMFEEDBACKVARYINGPROC) (GLuint program, GLuint सूचकांक, GLsizei buf_आकार, GLsizei *लंबाई, GLsizei *आकार, GLenum *type, GLchar *name);
प्रकार व्योम (GL_APIENTRYP PFNGLVERTEXATTRIBIPOINTERPROC) (GLuint सूचकांक, GLint आकार, GLenum type, GLsizei stride, स्थिर व्योम *pointer);
प्रकार व्योम (GL_APIENTRYP PFNGLGETVERTEXATTRIBIIVPROC) (GLuint सूचकांक, GLenum pname, GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETVERTEXATTRIBIUIVPROC) (GLuint सूचकांक, GLenum pname, GLuint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLVERTEXATTRIBI4IPROC) (GLuint सूचकांक, GLint x, GLint y, GLint z, GLint w);
प्रकार व्योम (GL_APIENTRYP PFNGLVERTEXATTRIBI4UIPROC) (GLuint सूचकांक, GLuint x, GLuint y, GLuint z, GLuint w);
प्रकार व्योम (GL_APIENTRYP PFNGLVERTEXATTRIBI4IVPROC) (GLuint सूचकांक, स्थिर GLint *v);
प्रकार व्योम (GL_APIENTRYP PFNGLVERTEXATTRIBI4UIVPROC) (GLuint सूचकांक, स्थिर GLuint *v);
प्रकार व्योम (GL_APIENTRYP PFNGLGETUNIFORMUIVPROC) (GLuint program, GLint location, GLuint *params);
प्रकार GLint (GL_APIENTRYP PFNGLGETFRAGDATALOCATIONPROC) (GLuint program, स्थिर GLchar *name);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM1UIPROC) (GLint location, GLuint v0);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM2UIPROC) (GLint location, GLuint v0, GLuint v1);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM3UIPROC) (GLint location, GLuint v0, GLuint v1, GLuint v2);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM4UIPROC) (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM1UIVPROC) (GLint location, GLsizei गिनती, स्थिर GLuint *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM2UIVPROC) (GLint location, GLsizei गिनती, स्थिर GLuint *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM3UIVPROC) (GLint location, GLsizei गिनती, स्थिर GLuint *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORM4UIVPROC) (GLint location, GLsizei गिनती, स्थिर GLuint *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLCLEARBUFFERIVPROC) (GLenum बफर_2, GLint drawbuffer, स्थिर GLint *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLCLEARBUFFERUIVPROC) (GLenum बफर_2, GLint drawbuffer, स्थिर GLuint *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLCLEARBUFFERFVPROC) (GLenum बफर_2, GLint drawbuffer, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLCLEARBUFFERFIPROC) (GLenum बफर_2, GLint drawbuffer, GLfloat depth, GLint stencil);
प्रकार स्थिर GLubyte *(GL_APIENTRYP PFNGLGETSTRINGIPROC) (GLenum name, GLuint सूचकांक);
प्रकार व्योम (GL_APIENTRYP PFNGLCOPYBUFFERSUBDATAPROC) (GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr आकार);
प्रकार व्योम (GL_APIENTRYP PFNGLGETUNIFORMINDICESPROC) (GLuint program, GLsizei uniform_गिनती, स्थिर GLchar *स्थिर*uniformNames, GLuint *uniformIndices);
प्रकार व्योम (GL_APIENTRYP PFNGLGETACTIVEUNIFORMSIVPROC) (GLuint program, GLsizei uniform_गिनती, स्थिर GLuint *uniformIndices, GLenum pname, GLint *params);
प्रकार GLuint (GL_APIENTRYP PFNGLGETUNIFORMBLOCKINDEXPROC) (GLuint program, स्थिर GLchar *uniformBlockName);
प्रकार व्योम (GL_APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKIVPROC) (GLuint program, GLuint uniform_Block_सूचकांक, GLenum pname, GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC) (GLuint program, GLuint uniform_Block_सूचकांक, GLsizei buf_आकार, GLsizei *लंबाई, GLchar *uniformBlockName);
प्रकार व्योम (GL_APIENTRYP PFNGLUNIFORMBLOCKBINDINGPROC) (GLuint program, GLuint uniform_Block_सूचकांक, GLuint uniformBlockBinding);
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDPROC) (GLenum mode, GLint first, GLsizei गिनती, GLsizei instancecount);
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDPROC) (GLenum mode, GLsizei गिनती, GLenum type, स्थिर व्योम *indices, GLsizei instancecount);
प्रकार GLsync (GL_APIENTRYP PFNGLFENCESYNCPROC) (GLenum condition, GLbitfield flags);
प्रकार GLboolean (GL_APIENTRYP PFNGLISSYNCPROC) (GLsync sync);
प्रकार व्योम (GL_APIENTRYP PFNGLDELETESYNCPROC) (GLsync sync);
प्रकार GLenum (GL_APIENTRYP PFNGLCLIENTWAITSYNCPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
प्रकार व्योम (GL_APIENTRYP PFNGLWAITSYNCPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
प्रकार व्योम (GL_APIENTRYP PFNGLGETINTEGER64VPROC) (GLenum pname, GLint64 *तथ्य);
प्रकार व्योम (GL_APIENTRYP PFNGLGETSYNCIVPROC) (GLsync sync, GLenum pname, GLsizei गिनती, GLsizei *लंबाई, GLint *मूल्यावली);
प्रकार व्योम (GL_APIENTRYP PFNGLGETINTEGER64I_VPROC) (GLenum target, GLuint सूचकांक, GLint64 *तथ्य);
प्रकार व्योम (GL_APIENTRYP PFNGLGETBUFFERPARAMETERI64VPROC) (GLenum target, GLenum pname, GLint64 *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGENSAMPLERSPROC) (GLsizei गिनती, GLuint *samplers);
प्रकार व्योम (GL_APIENTRYP PFNGLDELETESAMPLERSPROC) (GLsizei गिनती, स्थिर GLuint *samplers);
प्रकार GLboolean (GL_APIENTRYP PFNGLISSAMPLERPROC) (GLuint sampler);
प्रकार व्योम (GL_APIENTRYP PFNGLBINDSAMPLERPROC) (GLuint unit, GLuint sampler);
प्रकार व्योम (GL_APIENTRYP PFNGLSAMPLERPARAMETERIPROC) (GLuint sampler, GLenum pname, GLint param);
प्रकार व्योम (GL_APIENTRYP PFNGLSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, स्थिर GLint *param);
प्रकार व्योम (GL_APIENTRYP PFNGLSAMPLERPARAMETERFPROC) (GLuint sampler, GLenum pname, GLfloat param);
प्रकार व्योम (GL_APIENTRYP PFNGLSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, स्थिर GLfloat *param);
प्रकार व्योम (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, GLfloat *params);
प्रकार व्योम (GL_APIENTRYP PFNGLVERTEXATTRIBDIVISORPROC) (GLuint सूचकांक, GLuint भाजक);
प्रकार व्योम (GL_APIENTRYP PFNGLBINDTRANSFORMFEEDBACKPROC) (GLenum target, GLuint id);
प्रकार व्योम (GL_APIENTRYP PFNGLDELETETRANSFORMFEEDBACKSPROC) (GLsizei n, स्थिर GLuint *ids);
प्रकार व्योम (GL_APIENTRYP PFNGLGENTRANSFORMFEEDBACKSPROC) (GLsizei n, GLuint *ids);
प्रकार GLboolean (GL_APIENTRYP PFNGLISTRANSFORMFEEDBACKPROC) (GLuint id);
प्रकार व्योम (GL_APIENTRYP PFNGLPAUSETRANSFORMFEEDBACKPROC) (व्योम);
प्रकार व्योम (GL_APIENTRYP PFNGLRESUMETRANSFORMFEEDBACKPROC) (व्योम);
प्रकार व्योम (GL_APIENTRYP PFNGLGETPROGRAMBINARYPROC) (GLuint program, GLsizei buf_आकार, GLsizei *लंबाई, GLenum *द्विआधारी_Format, व्योम *द्विआधारी);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMBINARYPROC) (GLuint program, GLenum द्विआधारी_Format, स्थिर व्योम *द्विआधारी, GLsizei लंबाई);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMPARAMETERIPROC) (GLuint program, GLenum pname, GLint मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLINVALIDATEFRAMEBUFFERPROC) (GLenum target, GLsizei अंक_Attachments, स्थिर GLenum *attachments);
प्रकार व्योम (GL_APIENTRYP PFNGLINVALIDATESUBFRAMEBUFFERPROC) (GLenum target, GLsizei अंक_Attachments, स्थिर GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXSTORAGE2DPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXSTORAGE3DPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
प्रकार व्योम (GL_APIENTRYP PFNGLGETINTERNALFORMATIVPROC) (GLenum target, GLenum internalformat, GLenum pname, GLsizei गिनती, GLint *params);
#अगर GL_GLES_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY gl_Read_बफर (GLenum src);
GL_APICALL व्योम GL_APIENTRY glDrawRangeElements (GLenum mode, GLuint start, GLuint end, GLsizei गिनती, GLenum type, स्थिर व्योम *indices);
GL_APICALL व्योम GL_APIENTRY glTexImage3D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, स्थिर व्योम *pixels);
GL_APICALL व्योम GL_APIENTRY glTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, स्थिर व्योम *pixels);
GL_APICALL व्योम GL_APIENTRY glCopyTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
GL_APICALL व्योम GL_APIENTRY glCompressedTexImage3D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei image_आकार, स्थिर व्योम *तथ्य);
GL_APICALL व्योम GL_APIENTRY glCompressedTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei image_आकार, स्थिर व्योम *तथ्य);
GL_APICALL व्योम GL_APIENTRY glGenQueries (GLsizei n, GLuint *ids);
GL_APICALL व्योम GL_APIENTRY glDeleteQueries (GLsizei n, स्थिर GLuint *ids);
GL_APICALL GLboolean GL_APIENTRY glIsQuery (GLuint id);
GL_APICALL व्योम GL_APIENTRY glBeginQuery (GLenum target, GLuint id);
GL_APICALL व्योम GL_APIENTRY glEndQuery (GLenum target);
GL_APICALL व्योम GL_APIENTRY glGetQueryiv (GLenum target, GLenum pname, GLint *params);
GL_APICALL व्योम GL_APIENTRY glGetQueryObjectuiv (GLuint id, GLenum pname, GLuint *params);
GL_APICALL GLboolean GL_APIENTRY gl_Unmap_बफर (GLenum target);
GL_APICALL व्योम GL_APIENTRY gl_Get_बफर_Pointerv (GLenum target, GLenum pname, व्योम **params);
GL_APICALL व्योम GL_APIENTRY glDrawBuffers (GLsizei n, स्थिर GLenum *bufs);
GL_APICALL व्योम GL_APIENTRY glUniformMatrix2x3fv (GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glUniformMatrix3x2fv (GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glUniformMatrix2x4fv (GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glUniformMatrix4x2fv (GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glUniformMatrix3x4fv (GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glUniformMatrix4x3fv (GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glBlitFramebuffer (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
GL_APICALL व्योम GL_APIENTRY glRenderbufferStorageMultisample (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
GL_APICALL व्योम GL_APIENTRY glFramebufferTextureLayer (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
GL_APICALL व्योम *GL_APIENTRY gl_Map_बफर_Range (GLenum target, GLintptr offset, GLsizeiptr लंबाई, GLbitfield access);
GL_APICALL व्योम GL_APIENTRY gl_Flush_Mapped_बफर_Range (GLenum target, GLintptr offset, GLsizeiptr लंबाई);
GL_APICALL व्योम GL_APIENTRY glBindVertexArray (GLuint array);
GL_APICALL व्योम GL_APIENTRY glDeleteVertexArrays (GLsizei n, स्थिर GLuint *arrays);
GL_APICALL व्योम GL_APIENTRY glGenVertexArrays (GLsizei n, GLuint *arrays);
GL_APICALL GLboolean GL_APIENTRY glIsVertexArray (GLuint array);
GL_APICALL व्योम GL_APIENTRY glGetIntegeri_v (GLenum target, GLuint सूचकांक, GLint *तथ्य);
GL_APICALL व्योम GL_APIENTRY glBeginTransformFeedback (GLenum primitiveMode);
GL_APICALL व्योम GL_APIENTRY glEndTransformFeedback (व्योम);
GL_APICALL व्योम GL_APIENTRY gl_Bind_बफर_Range (GLenum target, GLuint सूचकांक, GLuint बफर_2, GLintptr offset, GLsizeiptr आकार);
GL_APICALL व्योम GL_APIENTRY gl_Bind_बफर_Base (GLenum target, GLuint सूचकांक, GLuint बफर_2);
GL_APICALL व्योम GL_APIENTRY glTransformFeedbackVaryings (GLuint program, GLsizei गिनती, स्थिर GLchar *स्थिर*varyings, GLenum बफर_Mode);
GL_APICALL व्योम GL_APIENTRY glGetTransformFeedbackVarying (GLuint program, GLuint सूचकांक, GLsizei buf_आकार, GLsizei *लंबाई, GLsizei *आकार, GLenum *type, GLchar *name);
GL_APICALL व्योम GL_APIENTRY glVertexAttribIPointer (GLuint सूचकांक, GLint आकार, GLenum type, GLsizei stride, स्थिर व्योम *pointer);
GL_APICALL व्योम GL_APIENTRY glGetVertexAttribIiv (GLuint सूचकांक, GLenum pname, GLint *params);
GL_APICALL व्योम GL_APIENTRY glGetVertexAttribIuiv (GLuint सूचकांक, GLenum pname, GLuint *params);
GL_APICALL व्योम GL_APIENTRY glVertexAttribI4i (GLuint सूचकांक, GLint x, GLint y, GLint z, GLint w);
GL_APICALL व्योम GL_APIENTRY glVertexAttribI4ui (GLuint सूचकांक, GLuint x, GLuint y, GLuint z, GLuint w);
GL_APICALL व्योम GL_APIENTRY glVertexAttribI4iv (GLuint सूचकांक, स्थिर GLint *v);
GL_APICALL व्योम GL_APIENTRY glVertexAttribI4uiv (GLuint सूचकांक, स्थिर GLuint *v);
GL_APICALL व्योम GL_APIENTRY glGetUniformuiv (GLuint program, GLint location, GLuint *params);
GL_APICALL GLint GL_APIENTRY gl_Get_Frag_तथ्य_Location (GLuint program, स्थिर GLchar *name);
GL_APICALL व्योम GL_APIENTRY glUniform1ui (GLint location, GLuint v0);
GL_APICALL व्योम GL_APIENTRY glUniform2ui (GLint location, GLuint v0, GLuint v1);
GL_APICALL व्योम GL_APIENTRY glUniform3ui (GLint location, GLuint v0, GLuint v1, GLuint v2);
GL_APICALL व्योम GL_APIENTRY glUniform4ui (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
GL_APICALL व्योम GL_APIENTRY glUniform1uiv (GLint location, GLsizei गिनती, स्थिर GLuint *मूल्य);
GL_APICALL व्योम GL_APIENTRY glUniform2uiv (GLint location, GLsizei गिनती, स्थिर GLuint *मूल्य);
GL_APICALL व्योम GL_APIENTRY glUniform3uiv (GLint location, GLsizei गिनती, स्थिर GLuint *मूल्य);
GL_APICALL व्योम GL_APIENTRY glUniform4uiv (GLint location, GLsizei गिनती, स्थिर GLuint *मूल्य);
GL_APICALL व्योम GL_APIENTRY glClearBufferiv (GLenum बफर_2, GLint drawbuffer, स्थिर GLint *मूल्य);
GL_APICALL व्योम GL_APIENTRY glClearBufferuiv (GLenum बफर_2, GLint drawbuffer, स्थिर GLuint *मूल्य);
GL_APICALL व्योम GL_APIENTRY glClearBufferfv (GLenum बफर_2, GLint drawbuffer, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glClearBufferfi (GLenum बफर_2, GLint drawbuffer, GLfloat depth, GLint stencil);
GL_APICALL स्थिर GLubyte *GL_APIENTRY glGetStringi (GLenum name, GLuint सूचकांक);
GL_APICALL व्योम GL_APIENTRY gl_Copy_बफर_Sub_तथ्य (GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr आकार);
GL_APICALL व्योम GL_APIENTRY glGetUniformIndices (GLuint program, GLsizei uniform_गिनती, स्थिर GLchar *स्थिर*uniformNames, GLuint *uniformIndices);
GL_APICALL व्योम GL_APIENTRY glGetActiveUniformsiv (GLuint program, GLsizei uniform_गिनती, स्थिर GLuint *uniformIndices, GLenum pname, GLint *params);
GL_APICALL GLuint GL_APIENTRY gl_Get_Uniform_Block_सूचकांक (GLuint program, स्थिर GLchar *uniformBlockName);
GL_APICALL व्योम GL_APIENTRY glGetActiveUniformBlockiv (GLuint program, GLuint uniform_Block_सूचकांक, GLenum pname, GLint *params);
GL_APICALL व्योम GL_APIENTRY glGetActiveUniformBlockName (GLuint program, GLuint uniform_Block_सूचकांक, GLsizei buf_आकार, GLsizei *लंबाई, GLchar *uniformBlockName);
GL_APICALL व्योम GL_APIENTRY glUniformBlockBinding (GLuint program, GLuint uniform_Block_सूचकांक, GLuint uniformBlockBinding);
GL_APICALL व्योम GL_APIENTRY glDrawArraysInstanced (GLenum mode, GLint first, GLsizei गिनती, GLsizei instancecount);
GL_APICALL व्योम GL_APIENTRY glDrawElementsInstanced (GLenum mode, GLsizei गिनती, GLenum type, स्थिर व्योम *indices, GLsizei instancecount);
GL_APICALL GLsync GL_APIENTRY glFenceSync (GLenum condition, GLbitfield flags);
GL_APICALL GLboolean GL_APIENTRY glIsSync (GLsync sync);
GL_APICALL व्योम GL_APIENTRY glDeleteSync (GLsync sync);
GL_APICALL GLenum GL_APIENTRY glClientWaitSync (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_APICALL व्योम GL_APIENTRY glWaitSync (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_APICALL व्योम GL_APIENTRY glGetInteger64v (GLenum pname, GLint64 *तथ्य);
GL_APICALL व्योम GL_APIENTRY glGetSynciv (GLsync sync, GLenum pname, GLsizei गिनती, GLsizei *लंबाई, GLint *मूल्यावली);
GL_APICALL व्योम GL_APIENTRY glGetInteger64i_v (GLenum target, GLuint सूचकांक, GLint64 *तथ्य);
GL_APICALL व्योम GL_APIENTRY gl_Get_बफर_Parameteri64v (GLenum target, GLenum pname, GLint64 *params);
GL_APICALL व्योम GL_APIENTRY glGenSamplers (GLsizei गिनती, GLuint *samplers);
GL_APICALL व्योम GL_APIENTRY glDeleteSamplers (GLsizei गिनती, स्थिर GLuint *samplers);
GL_APICALL GLboolean GL_APIENTRY glIsSampler (GLuint sampler);
GL_APICALL व्योम GL_APIENTRY glBindSampler (GLuint unit, GLuint sampler);
GL_APICALL व्योम GL_APIENTRY glSamplerParameteri (GLuint sampler, GLenum pname, GLint param);
GL_APICALL व्योम GL_APIENTRY glSamplerParameteriv (GLuint sampler, GLenum pname, स्थिर GLint *param);
GL_APICALL व्योम GL_APIENTRY glSamplerParameterf (GLuint sampler, GLenum pname, GLfloat param);
GL_APICALL व्योम GL_APIENTRY glSamplerParameterfv (GLuint sampler, GLenum pname, स्थिर GLfloat *param);
GL_APICALL व्योम GL_APIENTRY glGetSamplerParameteriv (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL व्योम GL_APIENTRY glGetSamplerParameterfv (GLuint sampler, GLenum pname, GLfloat *params);
GL_APICALL व्योम GL_APIENTRY gl_Vertex_Attrib_भाजक (GLuint सूचकांक, GLuint भाजक);
GL_APICALL व्योम GL_APIENTRY glBindTransformFeedback (GLenum target, GLuint id);
GL_APICALL व्योम GL_APIENTRY glDeleteTransformFeedbacks (GLsizei n, स्थिर GLuint *ids);
GL_APICALL व्योम GL_APIENTRY glGenTransformFeedbacks (GLsizei n, GLuint *ids);
GL_APICALL GLboolean GL_APIENTRY glIsTransformFeedback (GLuint id);
GL_APICALL व्योम GL_APIENTRY glPauseTransformFeedback (व्योम);
GL_APICALL व्योम GL_APIENTRY glResumeTransformFeedback (व्योम);
GL_APICALL व्योम GL_APIENTRY gl_Get_Program_द्विआधारी (GLuint program, GLsizei buf_आकार, GLsizei *लंबाई, GLenum *द्विआधारी_Format, व्योम *द्विआधारी);
GL_APICALL व्योम GL_APIENTRY gl_Program_द्विआधारी (GLuint program, GLenum द्विआधारी_Format, स्थिर व्योम *द्विआधारी, GLsizei लंबाई);
GL_APICALL व्योम GL_APIENTRY glProgramParameteri (GLuint program, GLenum pname, GLint मूल्य);
GL_APICALL व्योम GL_APIENTRY glInvalidateFramebuffer (GLenum target, GLsizei अंक_Attachments, स्थिर GLenum *attachments);
GL_APICALL व्योम GL_APIENTRY glInvalidateSubFramebuffer (GLenum target, GLsizei अंक_Attachments, स्थिर GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height);
GL_APICALL व्योम GL_APIENTRY glTexStorage2D (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
GL_APICALL व्योम GL_APIENTRY glTexStorage3D (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
GL_APICALL व्योम GL_APIENTRY glGetInternalformativ (GLenum target, GLenum internalformat, GLenum pname, GLsizei गिनती, GLint *params);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_ES_VERSION_3_0 */

#अगर_अघोषित GL_ES_VERSION_3_1
#घोषणा GL_ES_VERSION_3_1 1
#घोषणा GL_COMPUTE_SHADER                 0x91B9
#घोषणा GL_MAX_COMPUTE_UNIFORM_BLOCKS     0x91BB
#घोषणा GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS 0x91BC
#घोषणा GL_MAX_COMPUTE_IMAGE_UNIFORMS     0x91BD
#घोषणा GL_MAX_COMPUTE_SHARED_MEMORY_आकार 0x8262
#घोषणा GL_MAX_COMPUTE_UNIFORM_COMPONENTS 0x8263
#घोषणा GL_MAX_COMPUTE_ATOMIC_गणक_BUFFERS 0x8264
#घोषणा GL_MAX_COMPUTE_ATOMIC_COUNTERS    0x8265
#घोषणा GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS 0x8266
#घोषणा GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS 0x90EB
#घोषणा GL_MAX_COMPUTE_WORK_GROUP_गिनती   0x91BE
#घोषणा GL_MAX_COMPUTE_WORK_GROUP_आकार    0x91BF
#घोषणा GL_COMPUTE_WORK_GROUP_आकार        0x8267
#घोषणा GL_DISPATCH_INDIRECT_बफर       0x90EE
#घोषणा GL_DISPATCH_INDIRECT_बफर_BINDING 0x90EF
#घोषणा GL_COMPUTE_SHADER_BIT             0x00000020
#घोषणा GL_DRAW_INDIRECT_बफर           0x8F3F
#घोषणा GL_DRAW_INDIRECT_बफर_BINDING   0x8F43
#घोषणा GL_MAX_UNIFORM_LOCATIONS          0x826E
#घोषणा GL_FRAMEBUFFER_DEFAULT_WIDTH      0x9310
#घोषणा GL_FRAMEBUFFER_DEFAULT_HEIGHT     0x9311
#घोषणा GL_FRAMEBUFFER_DEFAULT_SAMPLES    0x9313
#घोषणा GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS 0x9314
#घोषणा GL_MAX_FRAMEBUFFER_WIDTH          0x9315
#घोषणा GL_MAX_FRAMEBUFFER_HEIGHT         0x9316
#घोषणा GL_MAX_FRAMEBUFFER_SAMPLES        0x9318
#घोषणा GL_UNIFORM                        0x92E1
#घोषणा GL_UNIFORM_BLOCK                  0x92E2
#घोषणा GL_PROGRAM_निवेश                  0x92E3
#घोषणा GL_PROGRAM_OUTPUT                 0x92E4
#घोषणा GL_बफर_VARIABLE                0x92E5
#घोषणा GL_SHADER_STORAGE_BLOCK           0x92E6
#घोषणा GL_ATOMIC_गणक_बफर          0x92C0
#घोषणा GL_TRANSFORM_FEEDBACK_VARYING     0x92F4
#घोषणा GL_ACTIVE_RESOURCES               0x92F5
#घोषणा GL_MAX_NAME_लंबाई                0x92F6
#घोषणा GL_MAX_अंक_ACTIVE_VARIABLES       0x92F7
#घोषणा GL_NAME_लंबाई                    0x92F9
#घोषणा GL_TYPE                           0x92FA
#घोषणा GL_ARRAY_आकार                     0x92FB
#घोषणा GL_OFFSET                         0x92FC
#घोषणा GL_BLOCK_सूचकांक                    0x92FD
#घोषणा GL_ARRAY_STRIDE                   0x92FE
#घोषणा GL_MATRIX_STRIDE                  0x92FF
#घोषणा GL_IS_ROW_MAJOR                   0x9300
#घोषणा GL_ATOMIC_गणक_बफर_सूचकांक    0x9301
#घोषणा GL_बफर_BINDING                 0x9302
#घोषणा GL_बफर_तथ्य_आकार               0x9303
#घोषणा GL_अंक_ACTIVE_VARIABLES           0x9304
#घोषणा GL_ACTIVE_VARIABLES               0x9305
#घोषणा GL_REFERENCED_BY_VERTEX_SHADER    0x9306
#घोषणा GL_REFERENCED_BY_FRAGMENT_SHADER  0x930A
#घोषणा GL_REFERENCED_BY_COMPUTE_SHADER   0x930B
#घोषणा GL_शीर्ष_LEVEL_ARRAY_आकार           0x930C
#घोषणा GL_शीर्ष_LEVEL_ARRAY_STRIDE         0x930D
#घोषणा GL_LOCATION                       0x930E
#घोषणा GL_VERTEX_SHADER_BIT              0x00000001
#घोषणा GL_FRAGMENT_SHADER_BIT            0x00000002
#घोषणा GL_ALL_SHADER_BITS                0xFFFFFFFF
#घोषणा GL_PROGRAM_SEPARABLE              0x8258
#घोषणा GL_ACTIVE_PROGRAM                 0x8259
#घोषणा GL_PROGRAM_PIPELINE_BINDING       0x825A
#घोषणा GL_ATOMIC_गणक_बफर_BINDING  0x92C1
#घोषणा GL_ATOMIC_गणक_बफर_START    0x92C2
#घोषणा GL_ATOMIC_गणक_बफर_आकार     0x92C3
#घोषणा GL_MAX_VERTEX_ATOMIC_गणक_BUFFERS 0x92CC
#घोषणा GL_MAX_FRAGMENT_ATOMIC_गणक_BUFFERS 0x92D0
#घोषणा GL_MAX_COMBINED_ATOMIC_गणक_BUFFERS 0x92D1
#घोषणा GL_MAX_VERTEX_ATOMIC_COUNTERS     0x92D2
#घोषणा GL_MAX_FRAGMENT_ATOMIC_COUNTERS   0x92D6
#घोषणा GL_MAX_COMBINED_ATOMIC_COUNTERS   0x92D7
#घोषणा GL_MAX_ATOMIC_गणक_बफर_आकार 0x92D8
#घोषणा GL_MAX_ATOMIC_गणक_बफर_BINDINGS 0x92DC
#घोषणा GL_ACTIVE_ATOMIC_गणक_BUFFERS  0x92D9
#घोषणा GL_UNSIGNED_INT_ATOMIC_गणक    0x92DB
#घोषणा GL_MAX_IMAGE_UNITS                0x8F38
#घोषणा GL_MAX_VERTEX_IMAGE_UNIFORMS      0x90CA
#घोषणा GL_MAX_FRAGMENT_IMAGE_UNIFORMS    0x90CE
#घोषणा GL_MAX_COMBINED_IMAGE_UNIFORMS    0x90CF
#घोषणा GL_IMAGE_BINDING_NAME             0x8F3A
#घोषणा GL_IMAGE_BINDING_LEVEL            0x8F3B
#घोषणा GL_IMAGE_BINDING_LAYERED          0x8F3C
#घोषणा GL_IMAGE_BINDING_LAYER            0x8F3D
#घोषणा GL_IMAGE_BINDING_ACCESS           0x8F3E
#घोषणा GL_IMAGE_BINDING_FORMAT           0x906E
#घोषणा GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT 0x00000001
#घोषणा GL_ELEMENT_ARRAY_BARRIER_BIT      0x00000002
#घोषणा GL_UNIFORM_BARRIER_BIT            0x00000004
#घोषणा GL_TEXTURE_FETCH_BARRIER_BIT      0x00000008
#घोषणा GL_SHADER_IMAGE_ACCESS_BARRIER_BIT 0x00000020
#घोषणा GL_COMMAND_BARRIER_BIT            0x00000040
#घोषणा GL_PIXEL_बफर_BARRIER_BIT       0x00000080
#घोषणा GL_TEXTURE_UPDATE_BARRIER_BIT     0x00000100
#घोषणा GL_बफर_UPDATE_BARRIER_BIT      0x00000200
#घोषणा GL_FRAMEBUFFER_BARRIER_BIT        0x00000400
#घोषणा GL_TRANSFORM_FEEDBACK_BARRIER_BIT 0x00000800
#घोषणा GL_ATOMIC_गणक_BARRIER_BIT     0x00001000
#घोषणा GL_ALL_BARRIER_BITS               0xFFFFFFFF
#घोषणा GL_IMAGE_2D                       0x904D
#घोषणा GL_IMAGE_3D                       0x904E
#घोषणा GL_IMAGE_CUBE                     0x9050
#घोषणा GL_IMAGE_2D_ARRAY                 0x9053
#घोषणा GL_INT_IMAGE_2D                   0x9058
#घोषणा GL_INT_IMAGE_3D                   0x9059
#घोषणा GL_INT_IMAGE_CUBE                 0x905B
#घोषणा GL_INT_IMAGE_2D_ARRAY             0x905E
#घोषणा GL_UNSIGNED_INT_IMAGE_2D          0x9063
#घोषणा GL_UNSIGNED_INT_IMAGE_3D          0x9064
#घोषणा GL_UNSIGNED_INT_IMAGE_CUBE        0x9066
#घोषणा GL_UNSIGNED_INT_IMAGE_2D_ARRAY    0x9069
#घोषणा GL_IMAGE_FORMAT_COMPATIBILITY_TYPE 0x90C7
#घोषणा GL_IMAGE_FORMAT_COMPATIBILITY_BY_आकार 0x90C8
#घोषणा GL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS 0x90C9
#घोषणा GL_READ_ONLY                      0x88B8
#घोषणा GL_WRITE_ONLY                     0x88B9
#घोषणा GL_READ_WRITE                     0x88BA
#घोषणा GL_SHADER_STORAGE_बफर          0x90D2
#घोषणा GL_SHADER_STORAGE_बफर_BINDING  0x90D3
#घोषणा GL_SHADER_STORAGE_बफर_START    0x90D4
#घोषणा GL_SHADER_STORAGE_बफर_आकार     0x90D5
#घोषणा GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS 0x90D6
#घोषणा GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS 0x90DA
#घोषणा GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS 0x90DB
#घोषणा GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS 0x90DC
#घोषणा GL_MAX_SHADER_STORAGE_बफर_BINDINGS 0x90DD
#घोषणा GL_MAX_SHADER_STORAGE_BLOCK_आकार  0x90DE
#घोषणा GL_SHADER_STORAGE_बफर_OFFSET_ALIGNMENT 0x90DF
#घोषणा GL_SHADER_STORAGE_BARRIER_BIT     0x00002000
#घोषणा GL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES 0x8F39
#घोषणा GL_DEPTH_STENCIL_TEXTURE_MODE     0x90EA
#घोषणा GL_STENCIL_सूचकांक                  0x1901
#घोषणा GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET 0x8E5E
#घोषणा GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET 0x8E5F
#घोषणा GL_SAMPLE_POSITION                0x8E50
#घोषणा GL_SAMPLE_MASK                    0x8E51
#घोषणा GL_SAMPLE_MASK_मूल्य              0x8E52
#घोषणा GL_TEXTURE_2D_MULTISAMPLE         0x9100
#घोषणा GL_MAX_SAMPLE_MASK_शब्दगण          0x8E59
#घोषणा GL_MAX_COLOR_TEXTURE_SAMPLES      0x910E
#घोषणा GL_MAX_DEPTH_TEXTURE_SAMPLES      0x910F
#घोषणा GL_MAX_INTEGER_SAMPLES            0x9110
#घोषणा GL_TEXTURE_BINDING_2D_MULTISAMPLE 0x9104
#घोषणा GL_TEXTURE_SAMPLES                0x9106
#घोषणा GL_TEXTURE_FIXED_SAMPLE_LOCATIONS 0x9107
#घोषणा GL_TEXTURE_WIDTH                  0x1000
#घोषणा GL_TEXTURE_HEIGHT                 0x1001
#घोषणा GL_TEXTURE_DEPTH                  0x8071
#घोषणा GL_TEXTURE_INTERNAL_FORMAT        0x1003
#घोषणा GL_TEXTURE_RED_आकार               0x805C
#घोषणा GL_TEXTURE_GREEN_आकार             0x805D
#घोषणा GL_TEXTURE_BLUE_आकार              0x805E
#घोषणा GL_TEXTURE_ALPHA_आकार             0x805F
#घोषणा GL_TEXTURE_DEPTH_आकार             0x884A
#घोषणा GL_TEXTURE_STENCIL_आकार           0x88F1
#घोषणा GL_TEXTURE_SHARED_आकार            0x8C3F
#घोषणा GL_TEXTURE_RED_TYPE               0x8C10
#घोषणा GL_TEXTURE_GREEN_TYPE             0x8C11
#घोषणा GL_TEXTURE_BLUE_TYPE              0x8C12
#घोषणा GL_TEXTURE_ALPHA_TYPE             0x8C13
#घोषणा GL_TEXTURE_DEPTH_TYPE             0x8C16
#घोषणा GL_TEXTURE_COMPRESSED             0x86A1
#घोषणा GL_SAMPLER_2D_MULTISAMPLE         0x9108
#घोषणा GL_INT_SAMPLER_2D_MULTISAMPLE     0x9109
#घोषणा GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE 0x910A
#घोषणा GL_VERTEX_ATTRIB_BINDING          0x82D4
#घोषणा GL_VERTEX_ATTRIB_RELATIVE_OFFSET  0x82D5
#घोषणा GL_VERTEX_BINDING_भाजक         0x82D6
#घोषणा GL_VERTEX_BINDING_OFFSET          0x82D7
#घोषणा GL_VERTEX_BINDING_STRIDE          0x82D8
#घोषणा GL_VERTEX_BINDING_बफर          0x8F4F
#घोषणा GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET 0x82D9
#घोषणा GL_MAX_VERTEX_ATTRIB_BINDINGS     0x82DA
#घोषणा GL_MAX_VERTEX_ATTRIB_STRIDE       0x82E5
प्रकार व्योम (GL_APIENTRYP PFNGLDISPATCHCOMPUTEPROC) (GLuint अंक_groups_x, GLuint अंक_groups_y, GLuint अंक_groups_z);
प्रकार व्योम (GL_APIENTRYP PFNGLDISPATCHCOMPUTEINDIRECTPROC) (GLintptr indirect);
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWARRAYSINDIRECTPROC) (GLenum mode, स्थिर व्योम *indirect);
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWELEMENTSINDIRECTPROC) (GLenum mode, GLenum type, स्थिर व्योम *indirect);
प्रकार व्योम (GL_APIENTRYP PFNGLFRAMEBUFFERPARAMETERIPROC) (GLenum target, GLenum pname, GLint param);
प्रकार व्योम (GL_APIENTRYP PFNGLGETFRAMEBUFFERPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETPROGRAMINTERFACEIVPROC) (GLuint program, GLenum programInterface, GLenum pname, GLint *params);
प्रकार GLuint (GL_APIENTRYP PFNGLGETPROGRAMRESOURCEINDEXPROC) (GLuint program, GLenum programInterface, स्थिर GLchar *name);
प्रकार व्योम (GL_APIENTRYP PFNGLGETPROGRAMRESOURCENAMEPROC) (GLuint program, GLenum programInterface, GLuint सूचकांक, GLsizei buf_आकार, GLsizei *लंबाई, GLchar *name);
प्रकार व्योम (GL_APIENTRYP PFNGLGETPROGRAMRESOURCEIVPROC) (GLuint program, GLenum programInterface, GLuint सूचकांक, GLsizei prop_गिनती, स्थिर GLenum *props, GLsizei गिनती, GLsizei *लंबाई, GLint *params);
प्रकार GLint (GL_APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONPROC) (GLuint program, GLenum programInterface, स्थिर GLchar *name);
प्रकार व्योम (GL_APIENTRYP PFNGLUSEPROGRAMSTAGESPROC) (GLuint pipeline, GLbitfield stages, GLuint program);
प्रकार व्योम (GL_APIENTRYP PFNGLACTIVESHADERPROGRAMPROC) (GLuint pipeline, GLuint program);
प्रकार GLuint (GL_APIENTRYP PFNGLCREATESHADERPROGRAMVPROC) (GLenum type, GLsizei गिनती, स्थिर GLchar *स्थिर*strings);
प्रकार व्योम (GL_APIENTRYP PFNGLBINDPROGRAMPIPELINEPROC) (GLuint pipeline);
प्रकार व्योम (GL_APIENTRYP PFNGLDELETEPROGRAMPIPELINESPROC) (GLsizei n, स्थिर GLuint *pipelines);
प्रकार व्योम (GL_APIENTRYP PFNGLGENPROGRAMPIPELINESPROC) (GLsizei n, GLuint *pipelines);
प्रकार GLboolean (GL_APIENTRYP PFNGLISPROGRAMPIPELINEPROC) (GLuint pipeline);
प्रकार व्योम (GL_APIENTRYP PFNGLGETPROGRAMPIPELINEIVPROC) (GLuint pipeline, GLenum pname, GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM1IPROC) (GLuint program, GLint location, GLint v0);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM2IPROC) (GLuint program, GLint location, GLint v0, GLint v1);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM3IPROC) (GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM4IPROC) (GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UIPROC) (GLuint program, GLint location, GLuint v0);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UIPROC) (GLuint program, GLint location, GLuint v0, GLuint v1);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UIPROC) (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UIPROC) (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM1FPROC) (GLuint program, GLint location, GLfloat v0);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM2FPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM3FPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM4FPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM1IVPROC) (GLuint program, GLint location, GLsizei गिनती, स्थिर GLint *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM2IVPROC) (GLuint program, GLint location, GLsizei गिनती, स्थिर GLint *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM3IVPROC) (GLuint program, GLint location, GLsizei गिनती, स्थिर GLint *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM4IVPROC) (GLuint program, GLint location, GLsizei गिनती, स्थिर GLint *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UIVPROC) (GLuint program, GLint location, GLsizei गिनती, स्थिर GLuint *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UIVPROC) (GLuint program, GLint location, GLsizei गिनती, स्थिर GLuint *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UIVPROC) (GLuint program, GLint location, GLsizei गिनती, स्थिर GLuint *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UIVPROC) (GLuint program, GLint location, GLsizei गिनती, स्थिर GLuint *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM1FVPROC) (GLuint program, GLint location, GLsizei गिनती, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM2FVPROC) (GLuint program, GLint location, GLsizei गिनती, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM3FVPROC) (GLuint program, GLint location, GLsizei गिनती, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORM4FVPROC) (GLuint program, GLint location, GLsizei गिनती, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2FVPROC) (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3FVPROC) (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4FVPROC) (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC) (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC) (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC) (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC) (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC) (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC) (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLVALIDATEPROGRAMPIPELINEPROC) (GLuint pipeline);
प्रकार व्योम (GL_APIENTRYP PFNGLGETPROGRAMPIPELINEINFOLOGPROC) (GLuint pipeline, GLsizei buf_आकार, GLsizei *लंबाई, GLchar *infoLog);
प्रकार व्योम (GL_APIENTRYP PFNGLBINDIMAGETEXTUREPROC) (GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
प्रकार व्योम (GL_APIENTRYP PFNGLGETBOOLEANI_VPROC) (GLenum target, GLuint सूचकांक, GLboolean *तथ्य);
प्रकार व्योम (GL_APIENTRYP PFNGLMEMORYBARRIERPROC) (GLbitfield barriers);
प्रकार व्योम (GL_APIENTRYP PFNGLMEMORYBARRIERBYREGIONPROC) (GLbitfield barriers);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXSTORAGE2DMULTISAMPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
प्रकार व्योम (GL_APIENTRYP PFNGLGETMULTISAMPLEFVPROC) (GLenum pname, GLuint सूचकांक, GLfloat *val);
प्रकार व्योम (GL_APIENTRYP PFNGLSAMPLEMASKIPROC) (GLuint mask_संख्या, GLbitfield mask);
प्रकार व्योम (GL_APIENTRYP PFNGLGETTEXLEVELPARAMETERIVPROC) (GLenum target, GLint level, GLenum pname, GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETTEXLEVELPARAMETERFVPROC) (GLenum target, GLint level, GLenum pname, GLfloat *params);
प्रकार व्योम (GL_APIENTRYP PFNGLBINDVERTEXBUFFERPROC) (GLuint bindingindex, GLuint बफर_2, GLintptr offset, GLsizei stride);
प्रकार व्योम (GL_APIENTRYP PFNGLVERTEXATTRIBFORMATPROC) (GLuint attribindex, GLint आकार, GLenum type, GLboolean normalized, GLuint relativeoffset);
प्रकार व्योम (GL_APIENTRYP PFNGLVERTEXATTRIBIFORMATPROC) (GLuint attribindex, GLint आकार, GLenum type, GLuint relativeoffset);
प्रकार व्योम (GL_APIENTRYP PFNGLVERTEXATTRIBBINDINGPROC) (GLuint attribindex, GLuint bindingindex);
प्रकार व्योम (GL_APIENTRYP PFNGLVERTEXBINDINGDIVISORPROC) (GLuint bindingindex, GLuint भाजक);
#अगर GL_GLES_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glDispatchCompute (GLuint अंक_groups_x, GLuint अंक_groups_y, GLuint अंक_groups_z);
GL_APICALL व्योम GL_APIENTRY glDispatchComputeIndirect (GLintptr indirect);
GL_APICALL व्योम GL_APIENTRY glDrawArraysIndirect (GLenum mode, स्थिर व्योम *indirect);
GL_APICALL व्योम GL_APIENTRY glDrawElementsIndirect (GLenum mode, GLenum type, स्थिर व्योम *indirect);
GL_APICALL व्योम GL_APIENTRY glFramebufferParameteri (GLenum target, GLenum pname, GLint param);
GL_APICALL व्योम GL_APIENTRY glGetFramebufferParameteriv (GLenum target, GLenum pname, GLint *params);
GL_APICALL व्योम GL_APIENTRY glGetProgramInterfaceiv (GLuint program, GLenum programInterface, GLenum pname, GLint *params);
GL_APICALL GLuint GL_APIENTRY gl_Get_Program_Resource_सूचकांक (GLuint program, GLenum programInterface, स्थिर GLchar *name);
GL_APICALL व्योम GL_APIENTRY glGetProgramResourceName (GLuint program, GLenum programInterface, GLuint सूचकांक, GLsizei buf_आकार, GLsizei *लंबाई, GLchar *name);
GL_APICALL व्योम GL_APIENTRY glGetProgramResourceiv (GLuint program, GLenum programInterface, GLuint सूचकांक, GLsizei prop_गिनती, स्थिर GLenum *props, GLsizei गिनती, GLsizei *लंबाई, GLint *params);
GL_APICALL GLint GL_APIENTRY glGetProgramResourceLocation (GLuint program, GLenum programInterface, स्थिर GLchar *name);
GL_APICALL व्योम GL_APIENTRY glUseProgramStages (GLuint pipeline, GLbitfield stages, GLuint program);
GL_APICALL व्योम GL_APIENTRY glActiveShaderProgram (GLuint pipeline, GLuint program);
GL_APICALL GLuint GL_APIENTRY glCreateShaderProgramv (GLenum type, GLsizei गिनती, स्थिर GLchar *स्थिर*strings);
GL_APICALL व्योम GL_APIENTRY glBindProgramPipeline (GLuint pipeline);
GL_APICALL व्योम GL_APIENTRY glDeleteProgramPipelines (GLsizei n, स्थिर GLuint *pipelines);
GL_APICALL व्योम GL_APIENTRY glGenProgramPipelines (GLsizei n, GLuint *pipelines);
GL_APICALL GLboolean GL_APIENTRY glIsProgramPipeline (GLuint pipeline);
GL_APICALL व्योम GL_APIENTRY glGetProgramPipelineiv (GLuint pipeline, GLenum pname, GLint *params);
GL_APICALL व्योम GL_APIENTRY glProgramUniform1i (GLuint program, GLint location, GLint v0);
GL_APICALL व्योम GL_APIENTRY glProgramUniform2i (GLuint program, GLint location, GLint v0, GLint v1);
GL_APICALL व्योम GL_APIENTRY glProgramUniform3i (GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
GL_APICALL व्योम GL_APIENTRY glProgramUniform4i (GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
GL_APICALL व्योम GL_APIENTRY glProgramUniform1ui (GLuint program, GLint location, GLuint v0);
GL_APICALL व्योम GL_APIENTRY glProgramUniform2ui (GLuint program, GLint location, GLuint v0, GLuint v1);
GL_APICALL व्योम GL_APIENTRY glProgramUniform3ui (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
GL_APICALL व्योम GL_APIENTRY glProgramUniform4ui (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
GL_APICALL व्योम GL_APIENTRY glProgramUniform1f (GLuint program, GLint location, GLfloat v0);
GL_APICALL व्योम GL_APIENTRY glProgramUniform2f (GLuint program, GLint location, GLfloat v0, GLfloat v1);
GL_APICALL व्योम GL_APIENTRY glProgramUniform3f (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
GL_APICALL व्योम GL_APIENTRY glProgramUniform4f (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
GL_APICALL व्योम GL_APIENTRY glProgramUniform1iv (GLuint program, GLint location, GLsizei गिनती, स्थिर GLint *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniform2iv (GLuint program, GLint location, GLsizei गिनती, स्थिर GLint *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniform3iv (GLuint program, GLint location, GLsizei गिनती, स्थिर GLint *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniform4iv (GLuint program, GLint location, GLsizei गिनती, स्थिर GLint *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniform1uiv (GLuint program, GLint location, GLsizei गिनती, स्थिर GLuint *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniform2uiv (GLuint program, GLint location, GLsizei गिनती, स्थिर GLuint *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniform3uiv (GLuint program, GLint location, GLsizei गिनती, स्थिर GLuint *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniform4uiv (GLuint program, GLint location, GLsizei गिनती, स्थिर GLuint *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniform1fv (GLuint program, GLint location, GLsizei गिनती, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniform2fv (GLuint program, GLint location, GLsizei गिनती, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniform3fv (GLuint program, GLint location, GLsizei गिनती, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniform4fv (GLuint program, GLint location, GLsizei गिनती, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniformMatrix2fv (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniformMatrix3fv (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniformMatrix4fv (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniformMatrix2x3fv (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniformMatrix3x2fv (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniformMatrix2x4fv (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniformMatrix4x2fv (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniformMatrix3x4fv (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glProgramUniformMatrix4x3fv (GLuint program, GLint location, GLsizei गिनती, GLboolean transpose, स्थिर GLfloat *मूल्य);
GL_APICALL व्योम GL_APIENTRY glValidateProgramPipeline (GLuint pipeline);
GL_APICALL व्योम GL_APIENTRY glGetProgramPipelineInfoLog (GLuint pipeline, GLsizei buf_आकार, GLsizei *लंबाई, GLchar *infoLog);
GL_APICALL व्योम GL_APIENTRY glBindImageTexture (GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
GL_APICALL व्योम GL_APIENTRY glGetBooleani_v (GLenum target, GLuint सूचकांक, GLboolean *तथ्य);
GL_APICALL व्योम GL_APIENTRY glMemoryBarrier (GLbitfield barriers);
GL_APICALL व्योम GL_APIENTRY glMemoryBarrierByRegion (GLbitfield barriers);
GL_APICALL व्योम GL_APIENTRY glTexStorage2DMultisample (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
GL_APICALL व्योम GL_APIENTRY glGetMultisamplefv (GLenum pname, GLuint सूचकांक, GLfloat *val);
GL_APICALL व्योम GL_APIENTRY glSampleMaski (GLuint mask_संख्या, GLbitfield mask);
GL_APICALL व्योम GL_APIENTRY glGetTexLevelParameteriv (GLenum target, GLint level, GLenum pname, GLint *params);
GL_APICALL व्योम GL_APIENTRY glGetTexLevelParameterfv (GLenum target, GLint level, GLenum pname, GLfloat *params);
GL_APICALL व्योम GL_APIENTRY gl_Bind_Vertex_बफर (GLuint bindingindex, GLuint बफर_2, GLintptr offset, GLsizei stride);
GL_APICALL व्योम GL_APIENTRY glVertexAttribFormat (GLuint attribindex, GLint आकार, GLenum type, GLboolean normalized, GLuint relativeoffset);
GL_APICALL व्योम GL_APIENTRY glVertexAttribIFormat (GLuint attribindex, GLint आकार, GLenum type, GLuint relativeoffset);
GL_APICALL व्योम GL_APIENTRY glVertexAttribBinding (GLuint attribindex, GLuint bindingindex);
GL_APICALL व्योम GL_APIENTRY gl_Vertex_Binding_भाजक (GLuint bindingindex, GLuint भाजक);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_ES_VERSION_3_1 */

#अगर_अघोषित GL_ES_VERSION_3_2
#घोषणा GL_ES_VERSION_3_2 1
प्रकार व्योम (GL_APIENTRY  *GLDEBUGPROC)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei लंबाई,स्थिर GLchar *message,स्थिर व्योम *userParam);
#घोषणा GL_MULTISAMPLE_पंक्ति_WIDTH_RANGE   0x9381
#घोषणा GL_MULTISAMPLE_पंक्ति_WIDTH_GRANULARITY 0x9382
#घोषणा GL_MULTIPLY                       0x9294
#घोषणा GL_SCREEN                         0x9295
#घोषणा GL_OVERLAY                        0x9296
#घोषणा GL_DARKEN                         0x9297
#घोषणा GL_LIGHTEN                        0x9298
#घोषणा GL_COLORDODGE                     0x9299
#घोषणा GL_COLORBURN                      0x929A
#घोषणा GL_HARDLIGHT                      0x929B
#घोषणा GL_SOFTLIGHT                      0x929C
#घोषणा GL_DIFFERENCE                     0x929E
#घोषणा GL_EXCLUSION                      0x92A0
#घोषणा GL_HSL_HUE                        0x92AD
#घोषणा GL_HSL_SATURATION                 0x92AE
#घोषणा GL_HSL_COLOR                      0x92AF
#घोषणा GL_HSL_LUMINOSITY                 0x92B0
#घोषणा GL_DEBUG_OUTPUT_SYNCHRONOUS       0x8242
#घोषणा GL_DEBUG_अग्र_LOGGED_MESSAGE_लंबाई 0x8243
#घोषणा GL_DEBUG_CALLBACK_FUNCTION        0x8244
#घोषणा GL_DEBUG_CALLBACK_USER_PARAM      0x8245
#घोषणा GL_DEBUG_SOURCE_API               0x8246
#घोषणा GL_DEBUG_SOURCE_WINDOW_SYSTEM     0x8247
#घोषणा GL_DEBUG_SOURCE_SHADER_COMPILER   0x8248
#घोषणा GL_DEBUG_SOURCE_THIRD_PARTY       0x8249
#घोषणा GL_DEBUG_SOURCE_APPLICATION       0x824A
#घोषणा GL_DEBUG_SOURCE_OTHER             0x824B
#घोषणा GL_DEBUG_TYPE_ERROR               0x824C
#घोषणा GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR 0x824D
#घोषणा GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR  0x824E
#घोषणा GL_DEBUG_TYPE_PORTABILITY         0x824F
#घोषणा GL_DEBUG_TYPE_PERFORMANCE         0x8250
#घोषणा GL_DEBUG_TYPE_OTHER               0x8251
#घोषणा GL_DEBUG_TYPE_MARKER              0x8268
#घोषणा GL_DEBUG_TYPE_धकेलो_GROUP          0x8269
#घोषणा GL_DEBUG_TYPE_निकालो_GROUP           0x826A
#घोषणा GL_DEBUG_SEVERITY_NOTIFICATION    0x826B
#घोषणा GL_MAX_DEBUG_GROUP_ढेर_DEPTH    0x826C
#घोषणा GL_DEBUG_GROUP_ढेर_DEPTH        0x826D
#घोषणा GL_बफर                         0x82E0
#घोषणा GL_SHADER                         0x82E1
#घोषणा GL_PROGRAM                        0x82E2
#घोषणा GL_VERTEX_ARRAY                   0x8074
#घोषणा GL_QUERY                          0x82E3
#घोषणा GL_PROGRAM_PIPELINE               0x82E4
#घोषणा GL_SAMPLER                        0x82E6
#घोषणा GL_MAX_LABEL_लंबाई               0x82E8
#घोषणा GL_MAX_DEBUG_MESSAGE_लंबाई       0x9143
#घोषणा GL_MAX_DEBUG_LOGGED_MESSAGES      0x9144
#घोषणा GL_DEBUG_LOGGED_MESSAGES          0x9145
#घोषणा GL_DEBUG_SEVERITY_ऊपरी            0x9146
#घोषणा GL_DEBUG_SEVERITY_MEDIUM          0x9147
#घोषणा GL_DEBUG_SEVERITY_निचला             0x9148
#घोषणा GL_DEBUG_OUTPUT                   0x92E0
#घोषणा GL_CONTEXT_FLAG_DEBUG_BIT         0x00000002
#घोषणा GL_ढेर_OVERFLOW                 0x0503
#घोषणा GL_ढेर_UNDERFLOW                0x0504
#घोषणा GL_GEOMETRY_SHADER                0x8DD9
#घोषणा GL_GEOMETRY_SHADER_BIT            0x00000004
#घोषणा GL_GEOMETRY_VERTICES_OUT          0x8916
#घोषणा GL_GEOMETRY_निवेश_TYPE            0x8917
#घोषणा GL_GEOMETRY_OUTPUT_TYPE           0x8918
#घोषणा GL_GEOMETRY_SHADER_INVOCATIONS    0x887F
#घोषणा GL_LAYER_PROVOKING_VERTEX         0x825E
#घोषणा GL_पंक्तियाँ_ADJACENCY                0x000A
#घोषणा GL_पंक्ति_STRIP_ADJACENCY           0x000B
#घोषणा GL_TRIANGLES_ADJACENCY            0x000C
#घोषणा GL_TRIANGLE_STRIP_ADJACENCY       0x000D
#घोषणा GL_MAX_GEOMETRY_UNIFORM_COMPONENTS 0x8DDF
#घोषणा GL_MAX_GEOMETRY_UNIFORM_BLOCKS    0x8A2C
#घोषणा GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS 0x8A32
#घोषणा GL_MAX_GEOMETRY_निवेश_COMPONENTS  0x9123
#घोषणा GL_MAX_GEOMETRY_OUTPUT_COMPONENTS 0x9124
#घोषणा GL_MAX_GEOMETRY_OUTPUT_VERTICES   0x8DE0
#घोषणा GL_MAX_GEOMETRY_योग_OUTPUT_COMPONENTS 0x8DE1
#घोषणा GL_MAX_GEOMETRY_SHADER_INVOCATIONS 0x8E5A
#घोषणा GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS 0x8C29
#घोषणा GL_MAX_GEOMETRY_ATOMIC_गणक_BUFFERS 0x92CF
#घोषणा GL_MAX_GEOMETRY_ATOMIC_COUNTERS   0x92D5
#घोषणा GL_MAX_GEOMETRY_IMAGE_UNIFORMS    0x90CD
#घोषणा GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS 0x90D7
#घोषणा GL_FIRST_VERTEX_CONVENTION        0x8E4D
#घोषणा GL_LAST_VERTEX_CONVENTION         0x8E4E
#घोषणा GL_UNDEFINED_VERTEX               0x8260
#घोषणा GL_PRIMITIVES_GENERATED           0x8C87
#घोषणा GL_FRAMEBUFFER_DEFAULT_LAYERS     0x9312
#घोषणा GL_MAX_FRAMEBUFFER_LAYERS         0x9317
#घोषणा GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS 0x8DA8
#घोषणा GL_FRAMEBUFFER_ATTACHMENT_LAYERED 0x8DA7
#घोषणा GL_REFERENCED_BY_GEOMETRY_SHADER  0x9309
#घोषणा GL_PRIMITIVE_BOUNDING_BOX         0x92BE
#घोषणा GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT 0x00000004
#घोषणा GL_CONTEXT_FLAGS                  0x821E
#घोषणा GL_LOSE_CONTEXT_ON_RESET          0x8252
#घोषणा GL_GUILTY_CONTEXT_RESET           0x8253
#घोषणा GL_INNOCENT_CONTEXT_RESET         0x8254
#घोषणा GL_UNKNOWN_CONTEXT_RESET          0x8255
#घोषणा GL_RESET_NOTIFICATION_STRATEGY    0x8256
#घोषणा GL_NO_RESET_NOTIFICATION          0x8261
#घोषणा GL_CONTEXT_LOST                   0x0507
#घोषणा GL_SAMPLE_SHADING                 0x8C36
#घोषणा GL_MIN_SAMPLE_SHADING_मूल्य       0x8C37
#घोषणा GL_MIN_FRAGMENT_INTERPOLATION_OFFSET 0x8E5B
#घोषणा GL_MAX_FRAGMENT_INTERPOLATION_OFFSET 0x8E5C
#घोषणा GL_FRAGMENT_INTERPOLATION_OFFSET_BITS 0x8E5D
#घोषणा GL_PATCHES                        0x000E
#घोषणा GL_PATCH_VERTICES                 0x8E72
#घोषणा GL_TESS_CONTROL_OUTPUT_VERTICES   0x8E75
#घोषणा GL_TESS_GEN_MODE                  0x8E76
#घोषणा GL_TESS_GEN_SPACING               0x8E77
#घोषणा GL_TESS_GEN_VERTEX_ORDER          0x8E78
#घोषणा GL_TESS_GEN_POINT_MODE            0x8E79
#घोषणा GL_ISOLINES                       0x8E7A
#घोषणा GL_QUADS                          0x0007
#घोषणा GL_FRACTIONAL_ODD                 0x8E7B
#घोषणा GL_FRACTIONAL_EVEN                0x8E7C
#घोषणा GL_MAX_PATCH_VERTICES             0x8E7D
#घोषणा GL_MAX_TESS_GEN_LEVEL             0x8E7E
#घोषणा GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS 0x8E7F
#घोषणा GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS 0x8E80
#घोषणा GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS 0x8E81
#घोषणा GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS 0x8E82
#घोषणा GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS 0x8E83
#घोषणा GL_MAX_TESS_PATCH_COMPONENTS      0x8E84
#घोषणा GL_MAX_TESS_CONTROL_योग_OUTPUT_COMPONENTS 0x8E85
#घोषणा GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS 0x8E86
#घोषणा GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS 0x8E89
#घोषणा GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS 0x8E8A
#घोषणा GL_MAX_TESS_CONTROL_निवेश_COMPONENTS 0x886C
#घोषणा GL_MAX_TESS_EVALUATION_निवेश_COMPONENTS 0x886D
#घोषणा GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS 0x8E1E
#घोषणा GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS 0x8E1F
#घोषणा GL_MAX_TESS_CONTROL_ATOMIC_गणक_BUFFERS 0x92CD
#घोषणा GL_MAX_TESS_EVALUATION_ATOMIC_गणक_BUFFERS 0x92CE
#घोषणा GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS 0x92D3
#घोषणा GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS 0x92D4
#घोषणा GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS 0x90CB
#घोषणा GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS 0x90CC
#घोषणा GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS 0x90D8
#घोषणा GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS 0x90D9
#घोषणा GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED 0x8221
#घोषणा GL_IS_PER_PATCH                   0x92E7
#घोषणा GL_REFERENCED_BY_TESS_CONTROL_SHADER 0x9307
#घोषणा GL_REFERENCED_BY_TESS_EVALUATION_SHADER 0x9308
#घोषणा GL_TESS_CONTROL_SHADER            0x8E88
#घोषणा GL_TESS_EVALUATION_SHADER         0x8E87
#घोषणा GL_TESS_CONTROL_SHADER_BIT        0x00000008
#घोषणा GL_TESS_EVALUATION_SHADER_BIT     0x00000010
#घोषणा GL_TEXTURE_BORDER_COLOR           0x1004
#घोषणा GL_CLAMP_TO_BORDER                0x812D
#घोषणा GL_TEXTURE_बफर                 0x8C2A
#घोषणा GL_TEXTURE_बफर_BINDING         0x8C2A
#घोषणा GL_MAX_TEXTURE_बफर_आकार        0x8C2B
#घोषणा GL_TEXTURE_BINDING_बफर         0x8C2C
#घोषणा GL_TEXTURE_बफर_तथ्य_STORE_BINDING 0x8C2D
#घोषणा GL_TEXTURE_बफर_OFFSET_ALIGNMENT 0x919F
#घोषणा GL_SAMPLER_बफर                 0x8DC2
#घोषणा GL_INT_SAMPLER_बफर             0x8DD0
#घोषणा GL_UNSIGNED_INT_SAMPLER_बफर    0x8DD8
#घोषणा GL_IMAGE_बफर                   0x9051
#घोषणा GL_INT_IMAGE_बफर               0x905C
#घोषणा GL_UNSIGNED_INT_IMAGE_बफर      0x9067
#घोषणा GL_TEXTURE_बफर_OFFSET          0x919D
#घोषणा GL_TEXTURE_बफर_आकार            0x919E
#घोषणा GL_COMPRESSED_RGBA_ASTC_4x4       0x93B0
#घोषणा GL_COMPRESSED_RGBA_ASTC_5x4       0x93B1
#घोषणा GL_COMPRESSED_RGBA_ASTC_5x5       0x93B2
#घोषणा GL_COMPRESSED_RGBA_ASTC_6x5       0x93B3
#घोषणा GL_COMPRESSED_RGBA_ASTC_6x6       0x93B4
#घोषणा GL_COMPRESSED_RGBA_ASTC_8x5       0x93B5
#घोषणा GL_COMPRESSED_RGBA_ASTC_8x6       0x93B6
#घोषणा GL_COMPRESSED_RGBA_ASTC_8x8       0x93B7
#घोषणा GL_COMPRESSED_RGBA_ASTC_10x5      0x93B8
#घोषणा GL_COMPRESSED_RGBA_ASTC_10x6      0x93B9
#घोषणा GL_COMPRESSED_RGBA_ASTC_10x8      0x93BA
#घोषणा GL_COMPRESSED_RGBA_ASTC_10x10     0x93BB
#घोषणा GL_COMPRESSED_RGBA_ASTC_12x10     0x93BC
#घोषणा GL_COMPRESSED_RGBA_ASTC_12x12     0x93BD
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4 0x93D0
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4 0x93D1
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5 0x93D2
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5 0x93D3
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6 0x93D4
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5 0x93D5
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6 0x93D6
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8 0x93D7
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5 0x93D8
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6 0x93D9
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8 0x93DA
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10 0x93DB
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10 0x93DC
#घोषणा GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12 0x93DD
#घोषणा GL_TEXTURE_CUBE_MAP_ARRAY         0x9009
#घोषणा GL_TEXTURE_BINDING_CUBE_MAP_ARRAY 0x900A
#घोषणा GL_SAMPLER_CUBE_MAP_ARRAY         0x900C
#घोषणा GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW  0x900D
#घोषणा GL_INT_SAMPLER_CUBE_MAP_ARRAY     0x900E
#घोषणा GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY 0x900F
#घोषणा GL_IMAGE_CUBE_MAP_ARRAY           0x9054
#घोषणा GL_INT_IMAGE_CUBE_MAP_ARRAY       0x905F
#घोषणा GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY 0x906A
#घोषणा GL_TEXTURE_2D_MULTISAMPLE_ARRAY   0x9102
#घोषणा GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY 0x9105
#घोषणा GL_SAMPLER_2D_MULTISAMPLE_ARRAY   0x910B
#घोषणा GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910C
#घोषणा GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910D
प्रकार व्योम (GL_APIENTRYP PFNGLBLENDBARRIERPROC) (व्योम);
प्रकार व्योम (GL_APIENTRYP PFNGLCOPYIMAGESUBDATAPROC) (GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
प्रकार व्योम (GL_APIENTRYP PFNGLDEBUGMESSAGECONTROLPROC) (GLenum source, GLenum type, GLenum severity, GLsizei गिनती, स्थिर GLuint *ids, GLboolean enabled);
प्रकार व्योम (GL_APIENTRYP PFNGLDEBUGMESSAGEINSERTPROC) (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei लंबाई, स्थिर GLchar *buf);
प्रकार व्योम (GL_APIENTRYP PFNGLDEBUGMESSAGECALLBACKPROC) (GLDEBUGPROC callback, स्थिर व्योम *userParam);
प्रकार GLuint (GL_APIENTRYP PFNGLGETDEBUGMESSAGELOGPROC) (GLuint गिनती, GLsizei buf_आकार, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog);
प्रकार व्योम (GL_APIENTRYP PFNGLPUSHDEBUGGROUPPROC) (GLenum source, GLuint id, GLsizei लंबाई, स्थिर GLchar *message);
प्रकार व्योम (GL_APIENTRYP PFNGLPOPDEBUGGROUPPROC) (व्योम);
प्रकार व्योम (GL_APIENTRYP PFNGLOBJECTLABELPROC) (GLenum identifier, GLuint name, GLsizei लंबाई, स्थिर GLchar *label);
प्रकार व्योम (GL_APIENTRYP PFNGLGETOBJECTLABELPROC) (GLenum identifier, GLuint name, GLsizei buf_आकार, GLsizei *लंबाई, GLchar *label);
प्रकार व्योम (GL_APIENTRYP PFNGLOBJECTPTRLABELPROC) (स्थिर व्योम *ptr, GLsizei लंबाई, स्थिर GLchar *label);
प्रकार व्योम (GL_APIENTRYP PFNGLGETOBJECTPTRLABELPROC) (स्थिर व्योम *ptr, GLsizei buf_आकार, GLsizei *लंबाई, GLchar *label);
प्रकार व्योम (GL_APIENTRYP PFNGLGETPOINTERVPROC) (GLenum pname, व्योम **params);
प्रकार व्योम (GL_APIENTRYP PFNGLENABLEIPROC) (GLenum target, GLuint सूचकांक);
प्रकार व्योम (GL_APIENTRYP PFNGLDISABLEIPROC) (GLenum target, GLuint सूचकांक);
प्रकार व्योम (GL_APIENTRYP PFNGLBLENDEQUATIONIPROC) (GLuint buf, GLenum mode);
प्रकार व्योम (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEIPROC) (GLuint buf, GLenum modeRGB, GLenum modeAlpha);
प्रकार व्योम (GL_APIENTRYP PFNGLBLENDFUNCIPROC) (GLuint buf, GLenum src, GLenum dst);
प्रकार व्योम (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEIPROC) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
प्रकार व्योम (GL_APIENTRYP PFNGLCOLORMASKIPROC) (GLuint सूचकांक, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
प्रकार GLboolean (GL_APIENTRYP PFNGLISENABLEDIPROC) (GLenum target, GLuint सूचकांक);
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWELEMENTSBASEVERTEXPROC) (GLenum mode, GLsizei गिनती, GLenum type, स्थिर व्योम *indices, GLint basevertex);
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC) (GLenum mode, GLuint start, GLuint end, GLsizei गिनती, GLenum type, स्थिर व्योम *indices, GLint basevertex);
प्रकार व्योम (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC) (GLenum mode, GLsizei गिनती, GLenum type, स्थिर व्योम *indices, GLsizei instancecount, GLint basevertex);
प्रकार व्योम (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level);
प्रकार व्योम (GL_APIENTRYP PFNGLPRIMITIVEBOUNDINGBOXPROC) (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
प्रकार GLenum (GL_APIENTRYP PFNGLGETGRAPHICSRESETSTATUSPROC) (व्योम);
प्रकार व्योम (GL_APIENTRYP PFNGLREADNPIXELSPROC) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei buf_आकार, व्योम *तथ्य);
प्रकार व्योम (GL_APIENTRYP PFNGLGETNUNIFORMFVPROC) (GLuint program, GLint location, GLsizei buf_आकार, GLfloat *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETNUNIFORMIVPROC) (GLuint program, GLint location, GLsizei buf_आकार, GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETNUNIFORMUIVPROC) (GLuint program, GLint location, GLsizei buf_आकार, GLuint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLMINSAMPLESHADINGPROC) (GLfloat मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLPATCHPARAMETERIPROC) (GLenum pname, GLint मूल्य);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXPARAMETERIIVPROC) (GLenum target, GLenum pname, स्थिर GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXPARAMETERIUIVPROC) (GLenum target, GLenum pname, स्थिर GLuint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETTEXPARAMETERIIVPROC) (GLenum target, GLenum pname, GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETTEXPARAMETERIUIVPROC) (GLenum target, GLenum pname, GLuint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLSAMPLERPARAMETERIIVPROC) (GLuint sampler, GLenum pname, स्थिर GLint *param);
प्रकार व्योम (GL_APIENTRYP PFNGLSAMPLERPARAMETERIUIVPROC) (GLuint sampler, GLenum pname, स्थिर GLuint *param);
प्रकार व्योम (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIIVPROC) (GLuint sampler, GLenum pname, GLint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIUIVPROC) (GLuint sampler, GLenum pname, GLuint *params);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXBUFFERPROC) (GLenum target, GLenum internalformat, GLuint बफर_2);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXBUFFERRANGEPROC) (GLenum target, GLenum internalformat, GLuint बफर_2, GLintptr offset, GLsizeiptr आकार);
प्रकार व्योम (GL_APIENTRYP PFNGLTEXSTORAGE3DMULTISAMPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
#अगर GL_GLES_PROTOTYPES
GL_APICALL व्योम GL_APIENTRY glBlendBarrier (व्योम);
GL_APICALL व्योम GL_APIENTRY gl_Copy_Image_Sub_तथ्य (GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
GL_APICALL व्योम GL_APIENTRY glDebugMessageControl (GLenum source, GLenum type, GLenum severity, GLsizei गिनती, स्थिर GLuint *ids, GLboolean enabled);
GL_APICALL व्योम GL_APIENTRY gl_Debug_Message_जोड़ो (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei लंबाई, स्थिर GLchar *buf);
GL_APICALL व्योम GL_APIENTRY glDebugMessageCallback (GLDEBUGPROC callback, स्थिर व्योम *userParam);
GL_APICALL GLuint GL_APIENTRY glGetDebugMessageLog (GLuint गिनती, GLsizei buf_आकार, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog);
GL_APICALL व्योम GL_APIENTRY gl_धकेलो_Debug_Group (GLenum source, GLuint id, GLsizei लंबाई, स्थिर GLchar *message);
GL_APICALL व्योम GL_APIENTRY gl_निकालो_Debug_Group (व्योम);
GL_APICALL व्योम GL_APIENTRY glObjectLabel (GLenum identifier, GLuint name, GLsizei लंबाई, स्थिर GLchar *label);
GL_APICALL व्योम GL_APIENTRY glGetObjectLabel (GLenum identifier, GLuint name, GLsizei buf_आकार, GLsizei *लंबाई, GLchar *label);
GL_APICALL व्योम GL_APIENTRY glObjectPtrLabel (स्थिर व्योम *ptr, GLsizei लंबाई, स्थिर GLchar *label);
GL_APICALL व्योम GL_APIENTRY glGetObjectPtrLabel (स्थिर व्योम *ptr, GLsizei buf_आकार, GLsizei *लंबाई, GLchar *label);
GL_APICALL व्योम GL_APIENTRY glGetPointerv (GLenum pname, व्योम **params);
GL_APICALL व्योम GL_APIENTRY glEnablei (GLenum target, GLuint सूचकांक);
GL_APICALL व्योम GL_APIENTRY glDisablei (GLenum target, GLuint सूचकांक);
GL_APICALL व्योम GL_APIENTRY glBlendEquationi (GLuint buf, GLenum mode);
GL_APICALL व्योम GL_APIENTRY glBlendEquationSeparatei (GLuint buf, GLenum modeRGB, GLenum modeAlpha);
GL_APICALL व्योम GL_APIENTRY glBlendFunci (GLuint buf, GLenum src, GLenum dst);
GL_APICALL व्योम GL_APIENTRY glBlendFuncSeparatei (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
GL_APICALL व्योम GL_APIENTRY glColorMaski (GLuint सूचकांक, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
GL_APICALL GLboolean GL_APIENTRY glIsEnabledi (GLenum target, GLuint सूचकांक);
GL_APICALL व्योम GL_APIENTRY glDrawElementsBaseVertex (GLenum mode, GLsizei गिनती, GLenum type, स्थिर व्योम *indices, GLint basevertex);
GL_APICALL व्योम GL_APIENTRY glDrawRangeElementsBaseVertex (GLenum mode, GLuint start, GLuint end, GLsizei गिनती, GLenum type, स्थिर व्योम *indices, GLint basevertex);
GL_APICALL व्योम GL_APIENTRY glDrawElementsInstancedBaseVertex (GLenum mode, GLsizei गिनती, GLenum type, स्थिर व्योम *indices, GLsizei instancecount, GLint basevertex);
GL_APICALL व्योम GL_APIENTRY glFramebufferTexture (GLenum target, GLenum attachment, GLuint texture, GLint level);
GL_APICALL व्योम GL_APIENTRY glPrimitiveBoundingBox (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
GL_APICALL GLenum GL_APIENTRY glGetGraphicsResetStatus (व्योम);
GL_APICALL व्योम GL_APIENTRY glReadnPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei buf_आकार, व्योम *तथ्य);
GL_APICALL व्योम GL_APIENTRY glGetnUniformfv (GLuint program, GLint location, GLsizei buf_आकार, GLfloat *params);
GL_APICALL व्योम GL_APIENTRY glGetnUniformiv (GLuint program, GLint location, GLsizei buf_आकार, GLint *params);
GL_APICALL व्योम GL_APIENTRY glGetnUniformuiv (GLuint program, GLint location, GLsizei buf_आकार, GLuint *params);
GL_APICALL व्योम GL_APIENTRY glMinSampleShading (GLfloat मूल्य);
GL_APICALL व्योम GL_APIENTRY glPatchParameteri (GLenum pname, GLint मूल्य);
GL_APICALL व्योम GL_APIENTRY glTexParameterIiv (GLenum target, GLenum pname, स्थिर GLint *params);
GL_APICALL व्योम GL_APIENTRY glTexParameterIuiv (GLenum target, GLenum pname, स्थिर GLuint *params);
GL_APICALL व्योम GL_APIENTRY glGetTexParameterIiv (GLenum target, GLenum pname, GLint *params);
GL_APICALL व्योम GL_APIENTRY glGetTexParameterIuiv (GLenum target, GLenum pname, GLuint *params);
GL_APICALL व्योम GL_APIENTRY glSamplerParameterIiv (GLuint sampler, GLenum pname, स्थिर GLint *param);
GL_APICALL व्योम GL_APIENTRY glSamplerParameterIuiv (GLuint sampler, GLenum pname, स्थिर GLuint *param);
GL_APICALL व्योम GL_APIENTRY glGetSamplerParameterIiv (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL व्योम GL_APIENTRY glGetSamplerParameterIuiv (GLuint sampler, GLenum pname, GLuint *params);
GL_APICALL व्योम GL_APIENTRY gl_Tex_बफर (GLenum target, GLenum internalformat, GLuint बफर_2);
GL_APICALL व्योम GL_APIENTRY gl_Tex_बफर_Range (GLenum target, GLenum internalformat, GLuint बफर_2, GLintptr offset, GLsizeiptr आकार);
GL_APICALL व्योम GL_APIENTRY glTexStorage3DMultisample (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
#पूर्ण_अगर
#पूर्ण_अगर /* GL_ES_VERSION_3_2 */

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर
