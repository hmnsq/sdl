#यदि_अपरिभाषितम् __gles2_gl2_h_
#परिभाषय __gles2_gl2_h_ 1

#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः

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

#यदि_अपरिभाषितम् GL_APIENTRYP
#परिभाषय GL_APIENTRYP GL_APIENTRY*
#यदि_अन्तः

#यदि_अपरिभाषितम् GL_GLES_PROTOTYPES
#परिभाषय GL_GLES_PROTOTYPES 1
#यदि_अन्तः

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

#यदि_अपरिभाषितम् GL_ES_संस्करणम्_2_0
#परिभाषय GL_ES_संस्करणम्_2_0 1
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
प्रकारनिर्देश अचिह्नित पूर्णाङ्क GLenum;
प्रकारनिर्देश अचिह्नित पूर्णाङ्क GLuint;
प्रकारनिर्देश वर्ण GLchar;
प्रकारनिर्देश khronos_float_t GLfloat;
प्रकारनिर्देश khronos_ssize_t GLsizeiptr;
प्रकारनिर्देश khronos_intptr_t GLintptr;
प्रकारनिर्देश अचिह्नित पूर्णाङ्क GLbitfield;
प्रकारनिर्देश पूर्णाङ्क GLint;
प्रकारनिर्देश अचिह्नित वर्ण GLboolean;
प्रकारनिर्देश पूर्णाङ्क GLsizei;
प्रकारनिर्देश khronos_uint8_t GLubyte;
#परिभाषय GL_गभीरता_बफर_BIT               0x00000100
#परिभाषय GL_STENCIL_बफर_BIT             0x00000400
#परिभाषय GL_COLOR_बफर_BIT               0x00004000
#परिभाषय GL_FALSE                          0
#परिभाषय GL_TRUE                           1
#परिभाषय GL_POINTS                         0x0000
#परिभाषय GL_पङ्क्तयः                          0x0001
#परिभाषय GL_पङ्क्तिः_LOOP                      0x0002
#परिभाषय GL_पङ्क्तिः_STRIP                     0x0003
#परिभाषय GL_TRIANGLES                      0x0004
#परिभाषय GL_TRIANGLE_STRIP                 0x0005
#परिभाषय GL_TRIANGLE_FAN                   0x0006
#परिभाषय GL_ZERO                           0
#परिभाषय GL_ONE                            1
#परिभाषय GL_SRC_COLOR                      0x0300
#परिभाषय GL_ONE_MINUS_SRC_COLOR            0x0301
#परिभाषय GL_SRC_ALPHA                      0x0302
#परिभाषय GL_ONE_MINUS_SRC_ALPHA            0x0303
#परिभाषय GL_DST_ALPHA                      0x0304
#परिभाषय GL_ONE_MINUS_DST_ALPHA            0x0305
#परिभाषय GL_DST_COLOR                      0x0306
#परिभाषय GL_ONE_MINUS_DST_COLOR            0x0307
#परिभाषय GL_SRC_ALPHA_SATURATE             0x0308
#परिभाषय GL_FUNC_सङ्कलय                       0x8006
#परिभाषय GL_BLEND_EQUATION                 0x8009
#परिभाषय GL_BLEND_EQUATION_RGB             0x8009
#परिभाषय GL_BLEND_EQUATION_ALPHA           0x883D
#परिभाषय GL_FUNC_व्यवकलय                  0x800A
#परिभाषय GL_FUNC_REVERSE_व्यवकलय          0x800B
#परिभाषय GL_BLEND_DST_RGB                  0x80C8
#परिभाषय GL_BLEND_SRC_RGB                  0x80C9
#परिभाषय GL_BLEND_DST_ALPHA                0x80CA
#परिभाषय GL_BLEND_SRC_ALPHA                0x80CB
#परिभाषय GL_CONSTANT_COLOR                 0x8001
#परिभाषय GL_ONE_MINUS_CONSTANT_COLOR       0x8002
#परिभाषय GL_CONSTANT_ALPHA                 0x8003
#परिभाषय GL_ONE_MINUS_CONSTANT_ALPHA       0x8004
#परिभाषय GL_BLEND_COLOR                    0x8005
#परिभाषय GL_ARRAY_बफर                   0x8892
#परिभाषय GL_ELEMENT_ARRAY_बफर           0x8893
#परिभाषय GL_ARRAY_बफर_BINDING           0x8894
#परिभाषय GL_ELEMENT_ARRAY_बफर_BINDING   0x8895
#परिभाषय GL_प्रवाहः_DRAW                    0x88E0
#परिभाषय GL_STATIC_DRAW                    0x88E4
#परिभाषय GL_DYNAMIC_DRAW                   0x88E8
#परिभाषय GL_बफर_आकार                    0x8764
#परिभाषय GL_बफर_USAGE                   0x8765
#परिभाषय GL_CURRENT_VERTEX_ATTRIB          0x8626
#परिभाषय GL_FRONT                          0x0404
#परिभाषय GL_पृष्ठभागः                           0x0405
#परिभाषय GL_FRONT_AND_पृष्ठभागः                 0x0408
#परिभाषय GL_TEXTURE_2D                     0x0DE1
#परिभाषय GL_CULL_FACE                      0x0B44
#परिभाषय GL_BLEND                          0x0BE2
#परिभाषय GL_DITHER                         0x0BD0
#परिभाषय GL_STENCIL_TEST                   0x0B90
#परिभाषय GL_गभीरता_TEST                     0x0B71
#परिभाषय GL_SCISSOR_TEST                   0x0C11
#परिभाषय GL_POLYGON_विस्थापनम्_FILL            0x8037
#परिभाषय GL_SAMPLE_ALPHA_गन्तव्यम्_COVERAGE       0x809E
#परिभाषय GL_SAMPLE_COVERAGE                0x80A0
#परिभाषय GL_NO_ERROR                       0
#परिभाषय GL_INVALID_ENUM                   0x0500
#परिभाषय GL_INVALID_मानम्                  0x0501
#परिभाषय GL_INVALID_OPERATION              0x0502
#परिभाषय GL_बहिर्गमनम्_सम्बन्धि_स्मृतिः                  0x0505
#परिभाषय GL_CW                             0x0900
#परिभाषय GL_CCW                            0x0901
#परिभाषय GL_पङ्क्तिः_विस्तारः                     0x0B21
#परिभाषय GL_ALIASED_POINT_आकार_RANGE       0x846D
#परिभाषय GL_ALIASED_पङ्क्तिः_विस्तारः_RANGE       0x846E
#परिभाषय GL_CULL_FACE_बहुलकम्                 0x0B45
#परिभाषय GL_FRONT_FACE                     0x0B46
#परिभाषय GL_गभीरता_RANGE                    0x0B70
#परिभाषय GL_गभीरता_WRITEMASK                0x0B72
#परिभाषय GL_गभीरता_CLEAR_मानम्              0x0B73
#परिभाषय GL_गभीरता_FUNC                     0x0B74
#परिभाषय GL_STENCIL_CLEAR_मानम्            0x0B91
#परिभाषय GL_STENCIL_FUNC                   0x0B92
#परिभाषय GL_STENCIL_FAIL                   0x0B94
#परिभाषय GL_STENCIL_PASS_गभीरता_FAIL        0x0B95
#परिभाषय GL_STENCIL_PASS_गभीरता_PASS        0x0B96
#परिभाषय GL_STENCIL_REF                    0x0B97
#परिभाषय GL_STENCIL_मानम्_आवरणम्             0x0B93
#परिभाषय GL_STENCIL_WRITEMASK              0x0B98
#परिभाषय GL_STENCIL_पृष्ठभागः_FUNC              0x8800
#परिभाषय GL_STENCIL_पृष्ठभागः_FAIL              0x8801
#परिभाषय GL_STENCIL_पृष्ठभागः_PASS_गभीरता_FAIL   0x8802
#परिभाषय GL_STENCIL_पृष्ठभागः_PASS_गभीरता_PASS   0x8803
#परिभाषय GL_STENCIL_पृष्ठभागः_REF               0x8CA3
#परिभाषय GL_STENCIL_पृष्ठभागः_मानम्_आवरणम्        0x8CA4
#परिभाषय GL_STENCIL_पृष्ठभागः_WRITEMASK         0x8CA5
#परिभाषय GL_VIEWPORT                       0x0BA2
#परिभाषय GL_SCISSOR_BOX                    0x0C10
#परिभाषय GL_COLOR_CLEAR_मानम्              0x0C22
#परिभाषय GL_COLOR_WRITEMASK                0x0C23
#परिभाषय GL_UNPACK_ALIGNMENT               0x0CF5
#परिभाषय GL_PACK_ALIGNMENT                 0x0D05
#परिभाषय GL_MAX_TEXTURE_आकार               0x0D33
#परिभाषय GL_MAX_VIEWPORT_DIMS              0x0D3A
#परिभाषय GL_SUBPIXEL_द्वयङ्काः                  0x0D50
#परिभाषय GL_RED_द्वयङ्काः                       0x0D52
#परिभाषय GL_GREEN_द्वयङ्काः                     0x0D53
#परिभाषय GL_BLUE_द्वयङ्काः                      0x0D54
#परिभाषय GL_ALPHA_द्वयङ्काः                     0x0D55
#परिभाषय GL_गभीरता_द्वयङ्काः                     0x0D56
#परिभाषय GL_STENCIL_द्वयङ्काः                   0x0D57
#परिभाषय GL_POLYGON_विस्थापनम्_UNITS           0x2A00
#परिभाषय GL_POLYGON_विस्थापनम्_गुणकः          0x8038
#परिभाषय GL_TEXTURE_BINDING_2D             0x8069
#परिभाषय GL_SAMPLE_BUFFERS                 0x80A8
#परिभाषय GL_SAMPLES                        0x80A9
#परिभाषय GL_SAMPLE_COVERAGE_मानम्          0x80AA
#परिभाषय GL_SAMPLE_COVERAGE_INVERT         0x80AB
#परिभाषय GL_अङ्कः_COMPRESSED_TEXTURE_FORMATS 0x86A2
#परिभाषय GL_COMPRESSED_TEXTURE_FORMATS     0x86A3
#परिभाषय GL_DONT_CARE                      0x1100
#परिभाषय GL_FASTEST                        0x1101
#परिभाषय GL_NICEST                         0x1102
#परिभाषय GL_GENERATE_MIPMAP_HINT           0x8192
#परिभाषय GL_BYTE                           0x1400
#परिभाषय GL_UNSIGNED_BYTE                  0x1401
#परिभाषय GL_SHORT                          0x1402
#परिभाषय GL_UNSIGNED_SHORT                 0x1403
#परिभाषय GL_INT                            0x1404
#परिभाषय GL_UNSIGNED_INT                   0x1405
#परिभाषय GL_FLOAT                          0x1406
#परिभाषय GL_FIXED                          0x140C
#परिभाषय GL_गभीरता_COMPONENT                0x1902
#परिभाषय GL_ALPHA                          0x1906
#परिभाषय GL_RGB                            0x1907
#परिभाषय GL_RGBA                           0x1908
#परिभाषय GL_LUMINANCE                      0x1909
#परिभाषय GL_LUMINANCE_ALPHA                0x190A
#परिभाषय GL_UNSIGNED_SHORT_4_4_4_4         0x8033
#परिभाषय GL_UNSIGNED_SHORT_5_5_5_1         0x8034
#परिभाषय GL_UNSIGNED_SHORT_5_6_5           0x8363
#परिभाषय GL_FRAGMENT_SHADER                0x8B30
#परिभाषय GL_VERTEX_SHADER                  0x8B31
#परिभाषय GL_MAX_VERTEX_ATTRIBS             0x8869
#परिभाषय GL_MAX_VERTEX_एकरूपम्_VECTORS     0x8DFB
#परिभाषय GL_MAX_VARYING_VECTORS            0x8DFC
#परिभाषय GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 0x8B4D
#परिभाषय GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS 0x8B4C
#परिभाषय GL_MAX_TEXTURE_IMAGE_UNITS        0x8872
#परिभाषय GL_MAX_FRAGMENT_एकरूपम्_VECTORS   0x8DFD
#परिभाषय GL_SHADER_TYPE                    0x8B4F
#परिभाषय GL_DELETE_स्थितिः                  0x8B80
#परिभाषय GL_LINK_स्थितिः                    0x8B82
#परिभाषय GL_VALIDATE_स्थितिः                0x8B83
#परिभाषय GL_ATTACHED_SHADERS               0x8B85
#परिभाषय GL_सक्रिय_UNIFORMS                0x8B86
#परिभाषय GL_सक्रिय_एकरूपम्_MAX_दीर्घता      0x8B87
#परिभाषय GL_सक्रिय_गुणाः              0x8B89
#परिभाषय GL_सक्रिय_ATTRIBUTE_MAX_दीर्घता    0x8B8A
#परिभाषय GL_SHADING_LANGUAGE_संस्करणम्       0x8B8C
#परिभाषय GL_CURRENT_क्रमादेशः                0x8B8D
#परिभाषय GL_NEVER                          0x0200
#परिभाषय GL_LESS                           0x0201
#परिभाषय GL_EQUAL                          0x0202
#परिभाषय GL_LEQUAL                         0x0203
#परिभाषय GL_GREATER                        0x0204
#परिभाषय GL_NOTEQUAL                       0x0205
#परिभाषय GL_GEQUAL                         0x0206
#परिभाषय GL_ALWAYS                         0x0207
#परिभाषय GL_KEEP                           0x1E00
#परिभाषय GL_REPLACE                        0x1E01
#परिभाषय GL_INCR                           0x1E02
#परिभाषय GL_DECR                           0x1E03
#परिभाषय GL_INVERT                         0x150A
#परिभाषय GL_INCR_WRAP                      0x8507
#परिभाषय GL_DECR_WRAP                      0x8508
#परिभाषय GL_VENDOR                         0x1F00
#परिभाषय GL_RENDERER                       0x1F01
#परिभाषय GL_संस्करणम्                        0x1F02
#परिभाषय GL_EXTENSIONS                     0x1F03
#परिभाषय GL_निकटतमः                        0x2600
#परिभाषय GL_रैखिकम्                         0x2601
#परिभाषय GL_निकटतमः_MIPMAP_निकटतमः         0x2700
#परिभाषय GL_रैखिकम्_MIPMAP_निकटतमः          0x2701
#परिभाषय GL_निकटतमः_MIPMAP_रैखिकम्          0x2702
#परिभाषय GL_रैखिकम्_MIPMAP_रैखिकम्           0x2703
#परिभाषय GL_TEXTURE_MAG_FILTER             0x2800
#परिभाषय GL_TEXTURE_MIN_FILTER             0x2801
#परिभाषय GL_TEXTURE_WRAP_S                 0x2802
#परिभाषय GL_TEXTURE_WRAP_T                 0x2803
#परिभाषय GL_TEXTURE                        0x1702
#परिभाषय GL_TEXTURE_CUBE_MAP               0x8513
#परिभाषय GL_TEXTURE_BINDING_CUBE_MAP       0x8514
#परिभाषय GL_TEXTURE_CUBE_MAP_धनात्मकम्_X    0x8515
#परिभाषय GL_TEXTURE_CUBE_MAP_NEGATIVE_X    0x8516
#परिभाषय GL_TEXTURE_CUBE_MAP_धनात्मकम्_Y    0x8517
#परिभाषय GL_TEXTURE_CUBE_MAP_NEGATIVE_Y    0x8518
#परिभाषय GL_TEXTURE_CUBE_MAP_धनात्मकम्_Z    0x8519
#परिभाषय GL_TEXTURE_CUBE_MAP_NEGATIVE_Z    0x851A
#परिभाषय GL_MAX_CUBE_MAP_TEXTURE_आकार      0x851C
#परिभाषय GL_TEXTURE0                       0x84C0
#परिभाषय GL_TEXTURE1                       0x84C1
#परिभाषय GL_TEXTURE2                       0x84C2
#परिभाषय GL_TEXTURE3                       0x84C3
#परिभाषय GL_TEXTURE4                       0x84C4
#परिभाषय GL_TEXTURE5                       0x84C5
#परिभाषय GL_TEXTURE6                       0x84C6
#परिभाषय GL_TEXTURE7                       0x84C7
#परिभाषय GL_TEXTURE8                       0x84C8
#परिभाषय GL_TEXTURE9                       0x84C9
#परिभाषय GL_TEXTURE10                      0x84CA
#परिभाषय GL_TEXTURE11                      0x84CB
#परिभाषय GL_TEXTURE12                      0x84CC
#परिभाषय GL_TEXTURE13                      0x84CD
#परिभाषय GL_TEXTURE14                      0x84CE
#परिभाषय GL_TEXTURE15                      0x84CF
#परिभाषय GL_TEXTURE16                      0x84D0
#परिभाषय GL_TEXTURE17                      0x84D1
#परिभाषय GL_TEXTURE18                      0x84D2
#परिभाषय GL_TEXTURE19                      0x84D3
#परिभाषय GL_TEXTURE20                      0x84D4
#परिभाषय GL_TEXTURE21                      0x84D5
#परिभाषय GL_TEXTURE22                      0x84D6
#परिभाषय GL_TEXTURE23                      0x84D7
#परिभाषय GL_TEXTURE24                      0x84D8
#परिभाषय GL_TEXTURE25                      0x84D9
#परिभाषय GL_TEXTURE26                      0x84DA
#परिभाषय GL_TEXTURE27                      0x84DB
#परिभाषय GL_TEXTURE28                      0x84DC
#परिभाषय GL_TEXTURE29                      0x84DD
#परिभाषय GL_TEXTURE30                      0x84DE
#परिभाषय GL_TEXTURE31                      0x84DF
#परिभाषय GL_सक्रिय_TEXTURE                 0x84E0
#परिभाषय GL_REPEAT                         0x2901
#परिभाषय GL_CLAMP_गन्तव्यम्_EDGE                  0x812F
#परिभाषय GL_MIRRORED_REPEAT                0x8370
#परिभाषय GL_FLOAT_VEC2                     0x8B50
#परिभाषय GL_FLOAT_VEC3                     0x8B51
#परिभाषय GL_FLOAT_VEC4                     0x8B52
#परिभाषय GL_INT_VEC2                       0x8B53
#परिभाषय GL_INT_VEC3                       0x8B54
#परिभाषय GL_INT_VEC4                       0x8B55
#परिभाषय GL_BOOL                           0x8B56
#परिभाषय GL_BOOL_VEC2                      0x8B57
#परिभाषय GL_BOOL_VEC3                      0x8B58
#परिभाषय GL_BOOL_VEC4                      0x8B59
#परिभाषय GL_FLOAT_MAT2                     0x8B5A
#परिभाषय GL_FLOAT_MAT3                     0x8B5B
#परिभाषय GL_FLOAT_MAT4                     0x8B5C
#परिभाषय GL_SAMPLER_2D                     0x8B5E
#परिभाषय GL_SAMPLER_CUBE                   0x8B60
#परिभाषय GL_VERTEX_ATTRIB_ARRAY_ENABLED    0x8622
#परिभाषय GL_VERTEX_ATTRIB_ARRAY_आकार       0x8623
#परिभाषय GL_VERTEX_ATTRIB_ARRAY_STRIDE     0x8624
#परिभाषय GL_VERTEX_ATTRIB_ARRAY_TYPE       0x8625
#परिभाषय GL_VERTEX_ATTRIB_ARRAY_NORMALIZED 0x886A
#परिभाषय GL_VERTEX_ATTRIB_ARRAY_POINTER    0x8645
#परिभाषय GL_VERTEX_ATTRIB_ARRAY_बफर_BINDING 0x889F
#परिभाषय GL_IMPLEMENTATION_COLOR_READ_TYPE 0x8B9A
#परिभाषय GL_IMPLEMENTATION_COLOR_READ_FORMAT 0x8B9B
#परिभाषय GL_COMPILE_स्थितिः                 0x8B81
#परिभाषय GL_INFO_LOG_दीर्घता                0x8B84
#परिभाषय GL_SHADER_SOURCE_दीर्घता           0x8B88
#परिभाषय GL_SHADER_COMPILER                0x8DFA
#परिभाषय GL_SHADER_द्विमान_FORMATS          0x8DF8
#परिभाषय GL_अङ्कः_SHADER_द्विमान_FORMATS      0x8DF9
#परिभाषय GL_नीचः_FLOAT                      0x8DF0
#परिभाषय GL_MEDIUM_FLOAT                   0x8DF1
#परिभाषय GL_उच्चः_FLOAT                     0x8DF2
#परिभाषय GL_नीचः_INT                        0x8DF3
#परिभाषय GL_MEDIUM_INT                     0x8DF4
#परिभाषय GL_उच्चः_INT                       0x8DF5
#परिभाषय GL_FRAMEBUFFER                    0x8D40
#परिभाषय GL_RENDERBUFFER                   0x8D41
#परिभाषय GL_RGBA4                          0x8056
#परिभाषय GL_RGB5_A1                        0x8057
#परिभाषय GL_RGB565                         0x8D62
#परिभाषय GL_गभीरता_COMPONENT16              0x81A5
#परिभाषय GL_STENCIL_INDEX8                 0x8D48
#परिभाषय GL_RENDERBUFFER_विस्तारः             0x8D42
#परिभाषय GL_RENDERBUFFER_HEIGHT            0x8D43
#परिभाषय GL_RENDERBUFFER_आन्तरिकम्_FORMAT   0x8D44
#परिभाषय GL_RENDERBUFFER_RED_आकार          0x8D50
#परिभाषय GL_RENDERBUFFER_GREEN_आकार        0x8D51
#परिभाषय GL_RENDERBUFFER_BLUE_आकार         0x8D52
#परिभाषय GL_RENDERBUFFER_ALPHA_आकार        0x8D53
#परिभाषय GL_RENDERBUFFER_गभीरता_आकार        0x8D54
#परिभाषय GL_RENDERBUFFER_STENCIL_आकार      0x8D55
#परिभाषय GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE 0x8CD0
#परिभाषय GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME 0x8CD1
#परिभाषय GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL 0x8CD2
#परिभाषय GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE 0x8CD3
#परिभाषय GL_COLOR_ATTACHMENT0              0x8CE0
#परिभाषय GL_गभीरता_ATTACHMENT               0x8D00
#परिभाषय GL_STENCIL_ATTACHMENT             0x8D20
#परिभाषय GL_NONE                           0
#परिभाषय GL_FRAMEBUFFER_COMPLETE           0x8CD5
#परिभाषय GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT 0x8CD6
#परिभाषय GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 0x8CD7
#परिभाषय GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS 0x8CD9
#परिभाषय GL_FRAMEBUFFER_UNSUPPORTED        0x8CDD
#परिभाषय GL_FRAMEBUFFER_BINDING            0x8CA6
#परिभाषय GL_RENDERBUFFER_BINDING           0x8CA7
#परिभाषय GL_MAX_RENDERBUFFER_आकार          0x84E8
#परिभाषय GL_INVALID_FRAMEBUFFER_OPERATION  0x0506
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLACTIVETEXTUREPROC) (GLenum texture);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLATTACHSHADERPROC) (GLuint क्रमादेशः, GLuint shader);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBINDATTRIBLOCATIONPROC) (GLuint क्रमादेशः, GLuint सूचकांक, ध्रुव GLchar *name);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBINDBUFFERPROC) (GLenum target, GLuint बफर_2);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBINDFRAMEBUFFERPROC) (GLenum target, GLuint framebuffer);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBINDRENDERBUFFERPROC) (GLenum target, GLuint renderbuffer);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBINDTEXTUREPROC) (GLenum target, GLuint texture);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBLENDCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBLENDEQUATIONPROC) (GLenum बहुलकम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEPROC) (GLenum बहुलकम्_RGB, GLenum बहुलकम्_Alpha);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBLENDFUNCPROC) (GLenum sfactor, GLenum dfactor);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEPROC) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBUFFERDATAPROC) (GLenum target, GLsizeiptr आकार, ध्रुव शून्य *दत्त, GLenum usage);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLBUFFERSUBDATAPROC) (GLenum target, GLintptr विस्थापनम्_2, GLsizeiptr आकार, ध्रुव शून्य *दत्त);
प्रकारनिर्देश GLenum (GL_APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSPROC) (GLenum target);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCLEARPROC) (GLbitfield आवरणम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCLEARCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCLEARDEPTHFPROC) (GLfloat d);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCLEARSTENCILPROC) (GLint s);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCOLORMASKPROC) (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCOMPILESHADERPROC) (GLuint shader);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCOMPRESSEDTEXIMAGE2DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei विस्तारः, GLsizei height, GLint border, GLsizei image_आकार, ध्रुव शून्य *दत्त);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei विस्तारः, GLsizei height, GLenum format, GLsizei image_आकार, ध्रुव शून्य *दत्त);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCOPYTEXIMAGE2DPROC) (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei विस्तारः, GLsizei height, GLint border);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCOPYTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei विस्तारः, GLsizei height);
प्रकारनिर्देश GLuint (GL_APIENTRYP PFNGLCREATEPROGRAMPROC) (शून्य);
प्रकारनिर्देश GLuint (GL_APIENTRYP PFNGLCREATESHADERPROC) (GLenum type);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLCULLFACEPROC) (GLenum बहुलकम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDELETEBUFFERSPROC) (GLsizei n, ध्रुव GLuint *buffers);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDELETEFRAMEBUFFERSPROC) (GLsizei n, ध्रुव GLuint *framebuffers);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDELETEPROGRAMPROC) (GLuint क्रमादेशः);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDELETERENDERBUFFERSPROC) (GLsizei n, ध्रुव GLuint *renderbuffers);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDELETESHADERPROC) (GLuint shader);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDELETETEXTURESPROC) (GLsizei n, ध्रुव GLuint *textures);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDEPTHFUNCPROC) (GLenum func);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDEPTHMASKPROC) (GLboolean flag);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDEPTHRANGEFPROC) (GLfloat n, GLfloat f);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDETACHSHADERPROC) (GLuint क्रमादेशः, GLuint shader);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDISABLEPROC) (GLenum cap);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint सूचकांक);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWARRAYSPROC) (GLenum बहुलकम्, GLint first, GLsizei गणनम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLDRAWELEMENTSPROC) (GLenum बहुलकम्, GLsizei गणनम्, GLenum type, ध्रुव शून्य *indices);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLENABLEPROC) (GLenum cap);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint सूचकांक);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFINISHPROC) (शून्य);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFLUSHPROC) (शून्य);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFERPROC) (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLFRONTFACEPROC) (GLenum बहुलकम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGENBUFFERSPROC) (GLsizei n, GLuint *buffers);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGENERATEMIPMAPPROC) (GLenum target);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGENFRAMEBUFFERSPROC) (GLsizei n, GLuint *framebuffers);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGENRENDERBUFFERSPROC) (GLsizei n, GLuint *renderbuffers);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGENTEXTURESPROC) (GLsizei n, GLuint *textures);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETACTIVEATTRIBPROC) (GLuint क्रमादेशः, GLuint सूचकांक, GLsizei buf_आकार, GLsizei *दीर्घता, GLint *आकार, GLenum *type, GLchar *name);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETACTIVEUNIFORMPROC) (GLuint क्रमादेशः, GLuint सूचकांक, GLsizei buf_आकार, GLsizei *दीर्घता, GLint *आकार, GLenum *type, GLchar *name);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETATTACHEDSHADERSPROC) (GLuint क्रमादेशः, GLsizei max_गणनम्, GLsizei *गणनम्, GLuint *shaders);
प्रकारनिर्देश GLint (GL_APIENTRYP PFNGLGETATTRIBLOCATIONPROC) (GLuint क्रमादेशः, ध्रुव GLchar *name);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETBOOLEANVPROC) (GLenum pname, GLboolean *दत्त);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETBUFFERPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
प्रकारनिर्देश GLenum (GL_APIENTRYP PFNGLGETERRORPROC) (शून्य);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETFLOATVPROC) (GLenum pname, GLfloat *दत्त);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) (GLenum target, GLenum attachment, GLenum pname, GLint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETINTEGERVPROC) (GLenum pname, GLint *दत्त);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETPROGRAMIVPROC) (GLuint क्रमादेशः, GLenum pname, GLint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETPROGRAMINFOLOGPROC) (GLuint क्रमादेशः, GLsizei buf_आकार, GLsizei *दीर्घता, GLchar *infoLog);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei buf_आकार, GLsizei *दीर्घता, GLchar *infoLog);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETSHADERPRECISIONFORMATPROC) (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETSHADERSOURCEPROC) (GLuint shader, GLsizei buf_आकार, GLsizei *दीर्घता, GLchar *source);
प्रकारनिर्देश ध्रुव GLubyte *(GL_APIENTRYP PFNGLGETSTRINGPROC) (GLenum name);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETTEXPARAMETERFVPROC) (GLenum target, GLenum pname, GLfloat *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETTEXPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETUNIFORMFVPROC) (GLuint क्रमादेशः, GLint location, GLfloat *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETUNIFORMIVPROC) (GLuint क्रमादेशः, GLint location, GLint *params);
प्रकारनिर्देश GLint (GL_APIENTRYP PFNGLGETUNIFORMLOCATIONPROC) (GLuint क्रमादेशः, ध्रुव GLchar *name);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETVERTEXATTRIBFVPROC) (GLuint सूचकांक, GLenum pname, GLfloat *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETVERTEXATTRIBIVPROC) (GLuint सूचकांक, GLenum pname, GLint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLGETVERTEXATTRIBPOINTERVPROC) (GLuint सूचकांक, GLenum pname, शून्य **pointer);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLHINTPROC) (GLenum target, GLenum बहुलकम्);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLISBUFFERPROC) (GLuint बफर_2);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLISENABLEDPROC) (GLenum cap);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLISFRAMEBUFFERPROC) (GLuint framebuffer);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLISPROGRAMPROC) (GLuint क्रमादेशः);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLISRENDERBUFFERPROC) (GLuint renderbuffer);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLISSHADERPROC) (GLuint shader);
प्रकारनिर्देश GLboolean (GL_APIENTRYP PFNGLISTEXTUREPROC) (GLuint texture);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLLINEWIDTHPROC) (GLfloat विस्तारः);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLLINKPROGRAMPROC) (GLuint क्रमादेशः);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPIXELSTOREIPROC) (GLenum pname, GLint param);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLPOLYGONOFFSETPROC) (GLfloat गुणकः, GLfloat units);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLREADPIXELSPROC) (GLint x, GLint y, GLsizei विस्तारः, GLsizei height, GLenum format, GLenum type, शून्य *pixels);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLRELEASESHADERCOMPILERPROC) (शून्य);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEPROC) (GLenum target, GLenum internalformat, GLsizei विस्तारः, GLsizei height);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSAMPLECOVERAGEPROC) (GLfloat मानम्, GLboolean invert);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSCISSORPROC) (GLint x, GLint y, GLsizei विस्तारः, GLsizei height);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSHADERBINARYPROC) (GLsizei गणनम्, ध्रुव GLuint *shaders, GLenum द्विमान_Format, ध्रुव शून्य *द्विमान, GLsizei दीर्घता);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei गणनम्, ध्रुव GLchar *ध्रुव*string, ध्रुव GLint *दीर्घता);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSTENCILFUNCPROC) (GLenum func, GLint ref, GLuint आवरणम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSTENCILFUNCSEPARATEPROC) (GLenum face, GLenum func, GLint ref, GLuint आवरणम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSTENCILMASKPROC) (GLuint आवरणम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSTENCILMASKSEPARATEPROC) (GLenum face, GLuint आवरणम्);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSTENCILOPPROC) (GLenum fail, GLenum zfail, GLenum zpass);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLSTENCILOPSEPARATEPROC) (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXIMAGE2DPROC) (GLenum target, GLint level, GLint internalformat, GLsizei विस्तारः, GLsizei height, GLint border, GLenum format, GLenum type, ध्रुव शून्य *pixels);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXPARAMETERFPROC) (GLenum target, GLenum pname, GLfloat param);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXPARAMETERFVPROC) (GLenum target, GLenum pname, ध्रुव GLfloat *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXPARAMETERIPROC) (GLenum target, GLenum pname, GLint param);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXPARAMETERIVPROC) (GLenum target, GLenum pname, ध्रुव GLint *params);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei विस्तारः, GLsizei height, GLenum format, GLenum type, ध्रुव शून्य *pixels);
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
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLUSEPROGRAMPROC) (GLuint क्रमादेशः);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLVALIDATEPROGRAMPROC) (GLuint क्रमादेशः);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLVERTEXATTRIB1FPROC) (GLuint सूचकांक, GLfloat x);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLVERTEXATTRIB1FVPROC) (GLuint सूचकांक, ध्रुव GLfloat *v);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLVERTEXATTRIB2FPROC) (GLuint सूचकांक, GLfloat x, GLfloat y);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLVERTEXATTRIB2FVPROC) (GLuint सूचकांक, ध्रुव GLfloat *v);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLVERTEXATTRIB3FPROC) (GLuint सूचकांक, GLfloat x, GLfloat y, GLfloat z);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLVERTEXATTRIB3FVPROC) (GLuint सूचकांक, ध्रुव GLfloat *v);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLVERTEXATTRIB4FPROC) (GLuint सूचकांक, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLVERTEXATTRIB4FVPROC) (GLuint सूचकांक, ध्रुव GLfloat *v);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC) (GLuint सूचकांक, GLint आकार, GLenum type, GLboolean normalized, GLsizei stride, ध्रुव शून्य *pointer);
प्रकारनिर्देश शून्य (GL_APIENTRYP PFNGLVIEWPORTPROC) (GLint x, GLint y, GLsizei विस्तारः, GLsizei height);
#यदि GL_GLES_PROTOTYPES
GL_APICALL शून्य GL_APIENTRY gl_सक्रिय_Texture (GLenum texture);
GL_APICALL शून्य GL_APIENTRY glAttachShader (GLuint क्रमादेशः, GLuint shader);
GL_APICALL शून्य GL_APIENTRY glBindAttribLocation (GLuint क्रमादेशः, GLuint सूचकांक, ध्रुव GLchar *name);
GL_APICALL शून्य GL_APIENTRY gl_Bind_बफर (GLenum target, GLuint बफर_2);
GL_APICALL शून्य GL_APIENTRY glBindFramebuffer (GLenum target, GLuint framebuffer);
GL_APICALL शून्य GL_APIENTRY glBindRenderbuffer (GLenum target, GLuint renderbuffer);
GL_APICALL शून्य GL_APIENTRY glBindTexture (GLenum target, GLuint texture);
GL_APICALL शून्य GL_APIENTRY glBlendColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_APICALL शून्य GL_APIENTRY glBlendEquation (GLenum बहुलकम्);
GL_APICALL शून्य GL_APIENTRY glBlendEquationSeparate (GLenum बहुलकम्_RGB, GLenum बहुलकम्_Alpha);
GL_APICALL शून्य GL_APIENTRY glBlendFunc (GLenum sfactor, GLenum dfactor);
GL_APICALL शून्य GL_APIENTRY glBlendFuncSeparate (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
GL_APICALL शून्य GL_APIENTRY gl_बफर_दत्त (GLenum target, GLsizeiptr आकार, ध्रुव शून्य *दत्त, GLenum usage);
GL_APICALL शून्य GL_APIENTRY gl_बफर_Sub_दत्त (GLenum target, GLintptr विस्थापनम्_2, GLsizeiptr आकार, ध्रुव शून्य *दत्त);
GL_APICALL GLenum GL_APIENTRY gl_Check_Framebuffer_स्थितिः (GLenum target);
GL_APICALL शून्य GL_APIENTRY glClear (GLbitfield आवरणम्);
GL_APICALL शून्य GL_APIENTRY glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_APICALL शून्य GL_APIENTRY glClearDepthf (GLfloat d);
GL_APICALL शून्य GL_APIENTRY glClearStencil (GLint s);
GL_APICALL शून्य GL_APIENTRY gl_Color_आवरणम् (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
GL_APICALL शून्य GL_APIENTRY glCompileShader (GLuint shader);
GL_APICALL शून्य GL_APIENTRY glCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei विस्तारः, GLsizei height, GLint border, GLsizei image_आकार, ध्रुव शून्य *दत्त);
GL_APICALL शून्य GL_APIENTRY glCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei विस्तारः, GLsizei height, GLenum format, GLsizei image_आकार, ध्रुव शून्य *दत्त);
GL_APICALL शून्य GL_APIENTRY glCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei विस्तारः, GLsizei height, GLint border);
GL_APICALL शून्य GL_APIENTRY glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei विस्तारः, GLsizei height);
GL_APICALL GLuint GL_APIENTRY gl_Create_क्रमादेशः (शून्य);
GL_APICALL GLuint GL_APIENTRY glCreateShader (GLenum type);
GL_APICALL शून्य GL_APIENTRY glCullFace (GLenum बहुलकम्);
GL_APICALL शून्य GL_APIENTRY glDeleteBuffers (GLsizei n, ध्रुव GLuint *buffers);
GL_APICALL शून्य GL_APIENTRY glDeleteFramebuffers (GLsizei n, ध्रुव GLuint *framebuffers);
GL_APICALL शून्य GL_APIENTRY gl_Delete_क्रमादेशः (GLuint क्रमादेशः);
GL_APICALL शून्य GL_APIENTRY glDeleteRenderbuffers (GLsizei n, ध्रुव GLuint *renderbuffers);
GL_APICALL शून्य GL_APIENTRY glDeleteShader (GLuint shader);
GL_APICALL शून्य GL_APIENTRY glDeleteTextures (GLsizei n, ध्रुव GLuint *textures);
GL_APICALL शून्य GL_APIENTRY gl_गभीरता_Func (GLenum func);
GL_APICALL शून्य GL_APIENTRY gl_गभीरता_आवरणम् (GLboolean flag);
GL_APICALL शून्य GL_APIENTRY gl_गभीरता_Rangef (GLfloat n, GLfloat f);
GL_APICALL शून्य GL_APIENTRY glDetachShader (GLuint क्रमादेशः, GLuint shader);
GL_APICALL शून्य GL_APIENTRY glDisable (GLenum cap);
GL_APICALL शून्य GL_APIENTRY glDisableVertexAttribArray (GLuint सूचकांक);
GL_APICALL शून्य GL_APIENTRY glDrawArrays (GLenum बहुलकम्, GLint first, GLsizei गणनम्);
GL_APICALL शून्य GL_APIENTRY glDrawElements (GLenum बहुलकम्, GLsizei गणनम्, GLenum type, ध्रुव शून्य *indices);
GL_APICALL शून्य GL_APIENTRY glEnable (GLenum cap);
GL_APICALL शून्य GL_APIENTRY glEnableVertexAttribArray (GLuint सूचकांक);
GL_APICALL शून्य GL_APIENTRY glFinish (शून्य);
GL_APICALL शून्य GL_APIENTRY glFlush (शून्य);
GL_APICALL शून्य GL_APIENTRY glFramebufferRenderbuffer (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
GL_APICALL शून्य GL_APIENTRY glFramebufferTexture2D (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GL_APICALL शून्य GL_APIENTRY glFrontFace (GLenum बहुलकम्);
GL_APICALL शून्य GL_APIENTRY glGenBuffers (GLsizei n, GLuint *buffers);
GL_APICALL शून्य GL_APIENTRY glGenerateMipmap (GLenum target);
GL_APICALL शून्य GL_APIENTRY glGenFramebuffers (GLsizei n, GLuint *framebuffers);
GL_APICALL शून्य GL_APIENTRY glGenRenderbuffers (GLsizei n, GLuint *renderbuffers);
GL_APICALL शून्य GL_APIENTRY glGenTextures (GLsizei n, GLuint *textures);
GL_APICALL शून्य GL_APIENTRY gl_Get_सक्रिय_Attrib (GLuint क्रमादेशः, GLuint सूचकांक, GLsizei buf_आकार, GLsizei *दीर्घता, GLint *आकार, GLenum *type, GLchar *name);
GL_APICALL शून्य GL_APIENTRY gl_Get_सक्रिय_एकरूपम् (GLuint क्रमादेशः, GLuint सूचकांक, GLsizei buf_आकार, GLsizei *दीर्घता, GLint *आकार, GLenum *type, GLchar *name);
GL_APICALL शून्य GL_APIENTRY glGetAttachedShaders (GLuint क्रमादेशः, GLsizei max_गणनम्, GLsizei *गणनम्, GLuint *shaders);
GL_APICALL GLint GL_APIENTRY glGetAttribLocation (GLuint क्रमादेशः, ध्रुव GLchar *name);
GL_APICALL शून्य GL_APIENTRY glGetBooleanv (GLenum pname, GLboolean *दत्त);
GL_APICALL शून्य GL_APIENTRY gl_Get_बफर_Parameteriv (GLenum target, GLenum pname, GLint *params);
GL_APICALL GLenum GL_APIENTRY glGetError (शून्य);
GL_APICALL शून्य GL_APIENTRY glGetFloatv (GLenum pname, GLfloat *दत्त);
GL_APICALL शून्य GL_APIENTRY glGetFramebufferAttachmentParameteriv (GLenum target, GLenum attachment, GLenum pname, GLint *params);
GL_APICALL शून्य GL_APIENTRY glGetIntegerv (GLenum pname, GLint *दत्त);
GL_APICALL शून्य GL_APIENTRY glGetProgramiv (GLuint क्रमादेशः, GLenum pname, GLint *params);
GL_APICALL शून्य GL_APIENTRY gl_Get_क्रमादेशः_Info_Log (GLuint क्रमादेशः, GLsizei buf_आकार, GLsizei *दीर्घता, GLchar *infoLog);
GL_APICALL शून्य GL_APIENTRY glGetRenderbufferParameteriv (GLenum target, GLenum pname, GLint *params);
GL_APICALL शून्य GL_APIENTRY glGetShaderiv (GLuint shader, GLenum pname, GLint *params);
GL_APICALL शून्य GL_APIENTRY glGetShaderInfoLog (GLuint shader, GLsizei buf_आकार, GLsizei *दीर्घता, GLchar *infoLog);
GL_APICALL शून्य GL_APIENTRY glGetShaderPrecisionFormat (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
GL_APICALL शून्य GL_APIENTRY glGetShaderSource (GLuint shader, GLsizei buf_आकार, GLsizei *दीर्घता, GLchar *source);
GL_APICALL ध्रुव GLubyte *GL_APIENTRY glGetString (GLenum name);
GL_APICALL शून्य GL_APIENTRY glGetTexParameterfv (GLenum target, GLenum pname, GLfloat *params);
GL_APICALL शून्य GL_APIENTRY glGetTexParameteriv (GLenum target, GLenum pname, GLint *params);
GL_APICALL शून्य GL_APIENTRY glGetUniformfv (GLuint क्रमादेशः, GLint location, GLfloat *params);
GL_APICALL शून्य GL_APIENTRY glGetUniformiv (GLuint क्रमादेशः, GLint location, GLint *params);
GL_APICALL GLint GL_APIENTRY gl_Get_एकरूपम्_Location (GLuint क्रमादेशः, ध्रुव GLchar *name);
GL_APICALL शून्य GL_APIENTRY glGetVertexAttribfv (GLuint सूचकांक, GLenum pname, GLfloat *params);
GL_APICALL शून्य GL_APIENTRY glGetVertexAttribiv (GLuint सूचकांक, GLenum pname, GLint *params);
GL_APICALL शून्य GL_APIENTRY glGetVertexAttribPointerv (GLuint सूचकांक, GLenum pname, शून्य **pointer);
GL_APICALL शून्य GL_APIENTRY glHint (GLenum target, GLenum बहुलकम्);
GL_APICALL GLboolean GL_APIENTRY gl_Is_बफर (GLuint बफर_2);
GL_APICALL GLboolean GL_APIENTRY glIsEnabled (GLenum cap);
GL_APICALL GLboolean GL_APIENTRY glIsFramebuffer (GLuint framebuffer);
GL_APICALL GLboolean GL_APIENTRY gl_Is_क्रमादेशः (GLuint क्रमादेशः);
GL_APICALL GLboolean GL_APIENTRY glIsRenderbuffer (GLuint renderbuffer);
GL_APICALL GLboolean GL_APIENTRY glIsShader (GLuint shader);
GL_APICALL GLboolean GL_APIENTRY glIsTexture (GLuint texture);
GL_APICALL शून्य GL_APIENTRY gl_पङ्क्तिः_विस्तारः (GLfloat विस्तारः);
GL_APICALL शून्य GL_APIENTRY gl_Link_क्रमादेशः (GLuint क्रमादेशः);
GL_APICALL शून्य GL_APIENTRY glPixelStorei (GLenum pname, GLint param);
GL_APICALL शून्य GL_APIENTRY gl_Polygon_विस्थापनम् (GLfloat गुणकः, GLfloat units);
GL_APICALL शून्य GL_APIENTRY glReadPixels (GLint x, GLint y, GLsizei विस्तारः, GLsizei height, GLenum format, GLenum type, शून्य *pixels);
GL_APICALL शून्य GL_APIENTRY glReleaseShaderCompiler (शून्य);
GL_APICALL शून्य GL_APIENTRY glRenderbufferStorage (GLenum target, GLenum internalformat, GLsizei विस्तारः, GLsizei height);
GL_APICALL शून्य GL_APIENTRY glSampleCoverage (GLfloat मानम्, GLboolean invert);
GL_APICALL शून्य GL_APIENTRY glScissor (GLint x, GLint y, GLsizei विस्तारः, GLsizei height);
GL_APICALL शून्य GL_APIENTRY gl_Shader_द्विमान (GLsizei गणनम्, ध्रुव GLuint *shaders, GLenum द्विमान_Format, ध्रुव शून्य *द्विमान, GLsizei दीर्घता);
GL_APICALL शून्य GL_APIENTRY glShaderSource (GLuint shader, GLsizei गणनम्, ध्रुव GLchar *ध्रुव*string, ध्रुव GLint *दीर्घता);
GL_APICALL शून्य GL_APIENTRY glStencilFunc (GLenum func, GLint ref, GLuint आवरणम्);
GL_APICALL शून्य GL_APIENTRY glStencilFuncSeparate (GLenum face, GLenum func, GLint ref, GLuint आवरणम्);
GL_APICALL शून्य GL_APIENTRY gl_Stencil_आवरणम् (GLuint आवरणम्);
GL_APICALL शून्य GL_APIENTRY gl_Stencil_आवरणम्_Separate (GLenum face, GLuint आवरणम्);
GL_APICALL शून्य GL_APIENTRY glStencilOp (GLenum fail, GLenum zfail, GLenum zpass);
GL_APICALL शून्य GL_APIENTRY glStencilOpSeparate (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
GL_APICALL शून्य GL_APIENTRY glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei विस्तारः, GLsizei height, GLint border, GLenum format, GLenum type, ध्रुव शून्य *pixels);
GL_APICALL शून्य GL_APIENTRY glTexParameterf (GLenum target, GLenum pname, GLfloat param);
GL_APICALL शून्य GL_APIENTRY glTexParameterfv (GLenum target, GLenum pname, ध्रुव GLfloat *params);
GL_APICALL शून्य GL_APIENTRY glTexParameteri (GLenum target, GLenum pname, GLint param);
GL_APICALL शून्य GL_APIENTRY glTexParameteriv (GLenum target, GLenum pname, ध्रुव GLint *params);
GL_APICALL शून्य GL_APIENTRY glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei विस्तारः, GLsizei height, GLenum format, GLenum type, ध्रुव शून्य *pixels);
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
GL_APICALL शून्य GL_APIENTRY gl_एकरूपम्_Matrix2fv (GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_एकरूपम्_Matrix3fv (GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_एकरूपम्_Matrix4fv (GLint location, GLsizei गणनम्, GLboolean transpose, ध्रुव GLfloat *मानम्);
GL_APICALL शून्य GL_APIENTRY gl_Use_क्रमादेशः (GLuint क्रमादेशः);
GL_APICALL शून्य GL_APIENTRY gl_Validate_क्रमादेशः (GLuint क्रमादेशः);
GL_APICALL शून्य GL_APIENTRY glVertexAttrib1f (GLuint सूचकांक, GLfloat x);
GL_APICALL शून्य GL_APIENTRY glVertexAttrib1fv (GLuint सूचकांक, ध्रुव GLfloat *v);
GL_APICALL शून्य GL_APIENTRY glVertexAttrib2f (GLuint सूचकांक, GLfloat x, GLfloat y);
GL_APICALL शून्य GL_APIENTRY glVertexAttrib2fv (GLuint सूचकांक, ध्रुव GLfloat *v);
GL_APICALL शून्य GL_APIENTRY glVertexAttrib3f (GLuint सूचकांक, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL शून्य GL_APIENTRY glVertexAttrib3fv (GLuint सूचकांक, ध्रुव GLfloat *v);
GL_APICALL शून्य GL_APIENTRY glVertexAttrib4f (GLuint सूचकांक, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
GL_APICALL शून्य GL_APIENTRY glVertexAttrib4fv (GLuint सूचकांक, ध्रुव GLfloat *v);
GL_APICALL शून्य GL_APIENTRY glVertexAttribPointer (GLuint सूचकांक, GLint आकार, GLenum type, GLboolean normalized, GLsizei stride, ध्रुव शून्य *pointer);
GL_APICALL शून्य GL_APIENTRY glViewport (GLint x, GLint y, GLsizei विस्तारः, GLsizei height);
#यदि_अन्तः
#यदि_अन्तः /* GL_ES_VERSION_2_0 */

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः
