#اگر_غیر_تعریف_شدہ __gles2_gl31_h_
#تعریف_کرو __gles2_gl31_h_ 1

#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم

/*
** Copyright 2013-2026 The Khronos Group Inc.
** SPDX-License-Identifier: MIT
**
** This header is generated from the Khronos OpenGL / OpenGL ES XML
** API Registry. The current version of the Registry, generator scripts
** used to make the header, and the header can be found at
**   https://github.com/KhronosGroup/OpenGL-Registry
*/

#شامل <GLES3/gl3platform.h>

#اگر_غیر_تعریف_شدہ GL_APIENTRYP
#تعریف_کرو GL_APIENTRYP GL_APIENTRY*
#اگر_ختم

#اگر_غیر_تعریف_شدہ GL_GLES_PROTOTYPES
#تعریف_کرو GL_GLES_PROTOTYPES 1
#اگر_ختم

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

#اگر_غیر_تعریف_شدہ GL_ES_نسخہ_2_0
#تعریف_کرو GL_ES_نسخہ_2_0 1
#شامل <KHR/khrplatform.h>
قسمتعریف khronos_int8_t GLbyte;
قسمتعریف khronos_float_t GLclampf;
قسمتعریف khronos_int32_t GLfixed;
قسمتعریف khronos_int16_t GLshort;
قسمتعریف khronos_uint16_t GLushort;
قسمتعریف خالی GLvoid;
قسمتعریف ساخت __GLsync *GLsync;
قسمتعریف khronos_int64_t GLint64;
قسمتعریف khronos_uint64_t GLuint64;
قسمتعریف غیرعلامتی صحیح GLenum;
قسمتعریف غیرعلامتی صحیح GLuint;
قسمتعریف حرف GLchar;
قسمتعریف khronos_float_t GLfloat;
قسمتعریف khronos_ssize_t GLsizeiptr;
قسمتعریف khronos_intptr_t GLintptr;
قسمتعریف غیرعلامتی صحیح GLbitfield;
قسمتعریف صحیح GLint;
قسمتعریف غیرعلامتی حرف GLboolean;
قسمتعریف صحیح GLsizei;
قسمتعریف khronos_uint8_t GLubyte;
#تعریف_کرو GL_گہرائی_بفر_ثنائی_ہندسہ               0x00000100
#تعریف_کرو GL_STENCIL_بفر_ثنائی_ہندسہ             0x00000400
#تعریف_کرو GL_COLOR_بفر_ثنائی_ہندسہ               0x00004000
#تعریف_کرو GL_FALSE                          0
#تعریف_کرو GL_TRUE                           1
#تعریف_کرو GL_POINTS                         0x0000
#تعریف_کرو GL_سطریں                          0x0001
#تعریف_کرو GL_سطر_LOOP                      0x0002
#تعریف_کرو GL_سطر_STRIP                     0x0003
#تعریف_کرو GL_TRIANGLES                      0x0004
#تعریف_کرو GL_TRIANGLE_STRIP                 0x0005
#تعریف_کرو GL_TRIANGLE_FAN                   0x0006
#تعریف_کرو GL_ZERO                           0
#تعریف_کرو GL_ONE                            1
#تعریف_کرو GL_SRC_COLOR                      0x0300
#تعریف_کرو GL_ONE_MINUS_SRC_COLOR            0x0301
#تعریف_کرو GL_SRC_ALPHA                      0x0302
#تعریف_کرو GL_ONE_MINUS_SRC_ALPHA            0x0303
#تعریف_کرو GL_DST_ALPHA                      0x0304
#تعریف_کرو GL_ONE_MINUS_DST_ALPHA            0x0305
#تعریف_کرو GL_DST_COLOR                      0x0306
#تعریف_کرو GL_ONE_MINUS_DST_COLOR            0x0307
#تعریف_کرو GL_SRC_ALPHA_SATURATE             0x0308
#تعریف_کرو GL_FUNC_جوڑو                       0x8006
#تعریف_کرو GL_BLEND_EQUATION                 0x8009
#تعریف_کرو GL_BLEND_EQUATION_RGB             0x8009
#تعریف_کرو GL_BLEND_EQUATION_ALPHA           0x883D
#تعریف_کرو GL_FUNC_تفریق                  0x800A
#تعریف_کرو GL_FUNC_الٹ_تفریق          0x800B
#تعریف_کرو GL_BLEND_DST_RGB                  0x80C8
#تعریف_کرو GL_BLEND_SRC_RGB                  0x80C9
#تعریف_کرو GL_BLEND_DST_ALPHA                0x80CA
#تعریف_کرو GL_BLEND_SRC_ALPHA                0x80CB
#تعریف_کرو GL_CONSTANT_COLOR                 0x8001
#تعریف_کرو GL_ONE_MINUS_CONSTANT_COLOR       0x8002
#تعریف_کرو GL_CONSTANT_ALPHA                 0x8003
#تعریف_کرو GL_ONE_MINUS_CONSTANT_ALPHA       0x8004
#تعریف_کرو GL_BLEND_COLOR                    0x8005
#تعریف_کرو GL_ARRAY_بفر                   0x8892
#تعریف_کرو GL_ELEMENT_ARRAY_بفر           0x8893
#تعریف_کرو GL_ARRAY_بفر_BINDING           0x8894
#تعریف_کرو GL_ELEMENT_ARRAY_بفر_BINDING   0x8895
#تعریف_کرو GL_دھارا_DRAW                    0x88E0
#تعریف_کرو GL_STATIC_DRAW                    0x88E4
#تعریف_کرو GL_DYNAMIC_DRAW                   0x88E8
#تعریف_کرو GL_بفر_سائز                    0x8764
#تعریف_کرو GL_بفر_USAGE                   0x8765
#تعریف_کرو GL_CURRENT_راس_ATTRIB          0x8626
#تعریف_کرو GL_FRONT                          0x0404
#تعریف_کرو GL_عقب                           0x0405
#تعریف_کرو GL_FRONT_AND_عقب                 0x0408
#تعریف_کرو GL_TEXTURE_2D                     0x0DE1
#تعریف_کرو GL_CULL_FACE                      0x0B44
#تعریف_کرو GL_BLEND                          0x0BE2
#تعریف_کرو GL_DITHER                         0x0BD0
#تعریف_کرو GL_STENCIL_TEST                   0x0B90
#تعریف_کرو GL_گہرائی_TEST                     0x0B71
#تعریف_کرو GL_SCISSOR_TEST                   0x0C11
#تعریف_کرو GL_POLYGON_انحراف_FILL            0x8037
#تعریف_کرو GL_SAMPLE_ALPHA_مقصد_COVERAGE       0x809E
#تعریف_کرو GL_SAMPLE_COVERAGE                0x80A0
#تعریف_کرو GL_NO_ERROR                       0
#تعریف_کرو GL_INVALID_ENUM                   0x0500
#تعریف_کرو GL_INVALID_قدر                  0x0501
#تعریف_کرو GL_INVALID_OPERATION              0x0502
#تعریف_کرو GL_برآمد_کا_حافظہ                  0x0505
#تعریف_کرو GL_CW                             0x0900
#تعریف_کرو GL_CCW                            0x0901
#تعریف_کرو GL_سطر_چوڑائی                     0x0B21
#تعریف_کرو GL_ALIASED_نقطہ_سائز_RANGE       0x846D
#تعریف_کرو GL_ALIASED_سطر_چوڑائی_RANGE       0x846E
#تعریف_کرو GL_CULL_FACE_منوال                 0x0B45
#تعریف_کرو GL_FRONT_FACE                     0x0B46
#تعریف_کرو GL_گہرائی_RANGE                    0x0B70
#تعریف_کرو GL_گہرائی_WRITEMASK                0x0B72
#تعریف_کرو GL_گہرائی_CLEAR_قدر              0x0B73
#تعریف_کرو GL_گہرائی_FUNC                     0x0B74
#تعریف_کرو GL_STENCIL_CLEAR_قدر            0x0B91
#تعریف_کرو GL_STENCIL_FUNC                   0x0B92
#تعریف_کرو GL_STENCIL_FAIL                   0x0B94
#تعریف_کرو GL_STENCIL_PASS_گہرائی_FAIL        0x0B95
#تعریف_کرو GL_STENCIL_PASS_گہرائی_PASS        0x0B96
#تعریف_کرو GL_STENCIL_REF                    0x0B97
#تعریف_کرو GL_STENCIL_قدر_نقاب             0x0B93
#تعریف_کرو GL_STENCIL_WRITEMASK              0x0B98
#تعریف_کرو GL_STENCIL_عقب_FUNC              0x8800
#تعریف_کرو GL_STENCIL_عقب_FAIL              0x8801
#تعریف_کرو GL_STENCIL_عقب_PASS_گہرائی_FAIL   0x8802
#تعریف_کرو GL_STENCIL_عقب_PASS_گہرائی_PASS   0x8803
#تعریف_کرو GL_STENCIL_عقب_REF               0x8CA3
#تعریف_کرو GL_STENCIL_عقب_قدر_نقاب        0x8CA4
#تعریف_کرو GL_STENCIL_عقب_WRITEMASK         0x8CA5
#تعریف_کرو GL_VIEWPORT                       0x0BA2
#تعریف_کرو GL_SCISSOR_BOX                    0x0C10
#تعریف_کرو GL_COLOR_CLEAR_قدر              0x0C22
#تعریف_کرو GL_COLOR_WRITEMASK                0x0C23
#تعریف_کرو GL_UNPACK_ALIGNMENT               0x0CF5
#تعریف_کرو GL_PACK_ALIGNMENT                 0x0D05
#تعریف_کرو GL_MAX_TEXTURE_سائز               0x0D33
#تعریف_کرو GL_MAX_VIEWPORT_DIMS              0x0D3A
#تعریف_کرو GL_SUBPIXEL_بٹ                  0x0D50
#تعریف_کرو GL_RED_بٹ                       0x0D52
#تعریف_کرو GL_GREEN_بٹ                     0x0D53
#تعریف_کرو GL_BLUE_بٹ                      0x0D54
#تعریف_کرو GL_ALPHA_بٹ                     0x0D55
#تعریف_کرو GL_گہرائی_بٹ                     0x0D56
#تعریف_کرو GL_STENCIL_بٹ                   0x0D57
#تعریف_کرو GL_POLYGON_انحراف_UNITS           0x2A00
#تعریف_کرو GL_POLYGON_انحراف_ضربی_عدد          0x8038
#تعریف_کرو GL_TEXTURE_BINDING_2D             0x8069
#تعریف_کرو GL_SAMPLE_BUFFERS                 0x80A8
#تعریف_کرو GL_SAMPLES                        0x80A9
#تعریف_کرو GL_SAMPLE_COVERAGE_قدر          0x80AA
#تعریف_کرو GL_SAMPLE_COVERAGE_INVERT         0x80AB
#تعریف_کرو GL_عدد_COMPRESSED_TEXTURE_FORMATS 0x86A2
#تعریف_کرو GL_COMPRESSED_TEXTURE_FORMATS     0x86A3
#تعریف_کرو GL_DONT_CARE                      0x1100
#تعریف_کرو GL_FASTEST                        0x1101
#تعریف_کرو GL_NICEST                         0x1102
#تعریف_کرو GL_GENERATE_MIPMAP_HINT           0x8192
#تعریف_کرو GL_BYTE                           0x1400
#تعریف_کرو GL_UNSIGNED_BYTE                  0x1401
#تعریف_کرو GL_SHORT                          0x1402
#تعریف_کرو GL_UNSIGNED_SHORT                 0x1403
#تعریف_کرو GL_INT                            0x1404
#تعریف_کرو GL_UNSIGNED_INT                   0x1405
#تعریف_کرو GL_FLOAT                          0x1406
#تعریف_کرو GL_FIXED                          0x140C
#تعریف_کرو GL_گہرائی_COMPONENT                0x1902
#تعریف_کرو GL_ALPHA                          0x1906
#تعریف_کرو GL_RGB                            0x1907
#تعریف_کرو GL_RGBA                           0x1908
#تعریف_کرو GL_LUMINANCE                      0x1909
#تعریف_کرو GL_LUMINANCE_ALPHA                0x190A
#تعریف_کرو GL_UNSIGNED_SHORT_4_4_4_4         0x8033
#تعریف_کرو GL_UNSIGNED_SHORT_5_5_5_1         0x8034
#تعریف_کرو GL_UNSIGNED_SHORT_5_6_5           0x8363
#تعریف_کرو GL_FRAGMENT_SHADER                0x8B30
#تعریف_کرو GL_راس_SHADER                  0x8B31
#تعریف_کرو GL_MAX_راس_ATTRIBS             0x8869
#تعریف_کرو GL_MAX_راس_یکساں_VECTORS     0x8DFB
#تعریف_کرو GL_MAX_VARYING_VECTORS            0x8DFC
#تعریف_کرو GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 0x8B4D
#تعریف_کرو GL_MAX_راس_TEXTURE_IMAGE_UNITS 0x8B4C
#تعریف_کرو GL_MAX_TEXTURE_IMAGE_UNITS        0x8872
#تعریف_کرو GL_MAX_FRAGMENT_یکساں_VECTORS   0x8DFD
#تعریف_کرو GL_SHADER_TYPE                    0x8B4F
#تعریف_کرو GL_DELETE_حالت                  0x8B80
#تعریف_کرو GL_LINK_حالت                    0x8B82
#تعریف_کرو GL_VALIDATE_حالت                0x8B83
#تعریف_کرو GL_ATTACHED_SHADERS               0x8B85
#تعریف_کرو GL_فعال_UNIFORMS                0x8B86
#تعریف_کرو GL_فعال_یکساں_MAX_لمبائی      0x8B87
#تعریف_کرو GL_فعال_اوصاف              0x8B89
#تعریف_کرو GL_فعال_ATTRIBUTE_MAX_لمبائی    0x8B8A
#تعریف_کرو GL_SHADING_LANGUAGE_نسخہ       0x8B8C
#تعریف_کرو GL_CURRENT_پروگرام                0x8B8D
#تعریف_کرو GL_NEVER                          0x0200
#تعریف_کرو GL_LESS                           0x0201
#تعریف_کرو GL_EQUAL                          0x0202
#تعریف_کرو GL_LEQUAL                         0x0203
#تعریف_کرو GL_GREATER                        0x0204
#تعریف_کرو GL_NOTEQUAL                       0x0205
#تعریف_کرو GL_GEQUAL                         0x0206
#تعریف_کرو GL_ALWAYS                         0x0207
#تعریف_کرو GL_KEEP                           0x1E00
#تعریف_کرو GL_REPLACE                        0x1E01
#تعریف_کرو GL_INCR                           0x1E02
#تعریف_کرو GL_DECR                           0x1E03
#تعریف_کرو GL_INVERT                         0x150A
#تعریف_کرو GL_INCR_WRAP                      0x8507
#تعریف_کرو GL_DECR_WRAP                      0x8508
#تعریف_کرو GL_VENDOR                         0x1F00
#تعریف_کرو GL_RENDERER                       0x1F01
#تعریف_کرو GL_نسخہ                        0x1F02
#تعریف_کرو GL_EXTENSIONS                     0x1F03
#تعریف_کرو GL_قریب_ترین                        0x2600
#تعریف_کرو GL_خطی                         0x2601
#تعریف_کرو GL_قریب_ترین_MIPMAP_قریب_ترین         0x2700
#تعریف_کرو GL_خطی_MIPMAP_قریب_ترین          0x2701
#تعریف_کرو GL_قریب_ترین_MIPMAP_خطی          0x2702
#تعریف_کرو GL_خطی_MIPMAP_خطی           0x2703
#تعریف_کرو GL_TEXTURE_MAG_FILTER             0x2800
#تعریف_کرو GL_TEXTURE_MIN_FILTER             0x2801
#تعریف_کرو GL_TEXTURE_WRAP_S                 0x2802
#تعریف_کرو GL_TEXTURE_WRAP_T                 0x2803
#تعریف_کرو GL_TEXTURE                        0x1702
#تعریف_کرو GL_TEXTURE_CUBE_MAP               0x8513
#تعریف_کرو GL_TEXTURE_BINDING_CUBE_MAP       0x8514
#تعریف_کرو GL_TEXTURE_CUBE_MAP_مثبت_X    0x8515
#تعریف_کرو GL_TEXTURE_CUBE_MAP_NEGATIVE_X    0x8516
#تعریف_کرو GL_TEXTURE_CUBE_MAP_مثبت_Y    0x8517
#تعریف_کرو GL_TEXTURE_CUBE_MAP_NEGATIVE_Y    0x8518
#تعریف_کرو GL_TEXTURE_CUBE_MAP_مثبت_Z    0x8519
#تعریف_کرو GL_TEXTURE_CUBE_MAP_NEGATIVE_Z    0x851A
#تعریف_کرو GL_MAX_CUBE_MAP_TEXTURE_سائز      0x851C
#تعریف_کرو GL_TEXTURE0                       0x84C0
#تعریف_کرو GL_TEXTURE1                       0x84C1
#تعریف_کرو GL_TEXTURE2                       0x84C2
#تعریف_کرو GL_TEXTURE3                       0x84C3
#تعریف_کرو GL_TEXTURE4                       0x84C4
#تعریف_کرو GL_TEXTURE5                       0x84C5
#تعریف_کرو GL_TEXTURE6                       0x84C6
#تعریف_کرو GL_TEXTURE7                       0x84C7
#تعریف_کرو GL_TEXTURE8                       0x84C8
#تعریف_کرو GL_TEXTURE9                       0x84C9
#تعریف_کرو GL_TEXTURE10                      0x84CA
#تعریف_کرو GL_TEXTURE11                      0x84CB
#تعریف_کرو GL_TEXTURE12                      0x84CC
#تعریف_کرو GL_TEXTURE13                      0x84CD
#تعریف_کرو GL_TEXTURE14                      0x84CE
#تعریف_کرو GL_TEXTURE15                      0x84CF
#تعریف_کرو GL_TEXTURE16                      0x84D0
#تعریف_کرو GL_TEXTURE17                      0x84D1
#تعریف_کرو GL_TEXTURE18                      0x84D2
#تعریف_کرو GL_TEXTURE19                      0x84D3
#تعریف_کرو GL_TEXTURE20                      0x84D4
#تعریف_کرو GL_TEXTURE21                      0x84D5
#تعریف_کرو GL_TEXTURE22                      0x84D6
#تعریف_کرو GL_TEXTURE23                      0x84D7
#تعریف_کرو GL_TEXTURE24                      0x84D8
#تعریف_کرو GL_TEXTURE25                      0x84D9
#تعریف_کرو GL_TEXTURE26                      0x84DA
#تعریف_کرو GL_TEXTURE27                      0x84DB
#تعریف_کرو GL_TEXTURE28                      0x84DC
#تعریف_کرو GL_TEXTURE29                      0x84DD
#تعریف_کرو GL_TEXTURE30                      0x84DE
#تعریف_کرو GL_TEXTURE31                      0x84DF
#تعریف_کرو GL_فعال_TEXTURE                 0x84E0
#تعریف_کرو GL_REPEAT                         0x2901
#تعریف_کرو GL_CLAMP_مقصد_کنارہ                  0x812F
#تعریف_کرو GL_MIRRORED_REPEAT                0x8370
#تعریف_کرو GL_FLOAT_VEC2                     0x8B50
#تعریف_کرو GL_FLOAT_VEC3                     0x8B51
#تعریف_کرو GL_FLOAT_VEC4                     0x8B52
#تعریف_کرو GL_INT_VEC2                       0x8B53
#تعریف_کرو GL_INT_VEC3                       0x8B54
#تعریف_کرو GL_INT_VEC4                       0x8B55
#تعریف_کرو GL_BOOL                           0x8B56
#تعریف_کرو GL_BOOL_VEC2                      0x8B57
#تعریف_کرو GL_BOOL_VEC3                      0x8B58
#تعریف_کرو GL_BOOL_VEC4                      0x8B59
#تعریف_کرو GL_FLOAT_MAT2                     0x8B5A
#تعریف_کرو GL_FLOAT_MAT3                     0x8B5B
#تعریف_کرو GL_FLOAT_MAT4                     0x8B5C
#تعریف_کرو GL_SAMPLER_2D                     0x8B5E
#تعریف_کرو GL_SAMPLER_CUBE                   0x8B60
#تعریف_کرو GL_راس_ATTRIB_ARRAY_ENABLED    0x8622
#تعریف_کرو GL_راس_ATTRIB_ARRAY_سائز       0x8623
#تعریف_کرو GL_راس_ATTRIB_ARRAY_STRIDE     0x8624
#تعریف_کرو GL_راس_ATTRIB_ARRAY_TYPE       0x8625
#تعریف_کرو GL_راس_ATTRIB_ARRAY_NORMALIZED 0x886A
#تعریف_کرو GL_راس_ATTRIB_ARRAY_اشارہ_گر    0x8645
#تعریف_کرو GL_راس_ATTRIB_ARRAY_بفر_BINDING 0x889F
#تعریف_کرو GL_IMPLEMENTATION_COLOR_READ_TYPE 0x8B9A
#تعریف_کرو GL_IMPLEMENTATION_COLOR_READ_FORMAT 0x8B9B
#تعریف_کرو GL_COMPILE_حالت                 0x8B81
#تعریف_کرو GL_INFO_LOG_لمبائی                0x8B84
#تعریف_کرو GL_SHADER_ماخذ_لمبائی           0x8B88
#تعریف_کرو GL_SHADER_COMPILER                0x8DFA
#تعریف_کرو GL_SHADER_ثنائی_FORMATS          0x8DF8
#تعریف_کرو GL_عدد_SHADER_ثنائی_FORMATS      0x8DF9
#تعریف_کرو GL_کم_FLOAT                      0x8DF0
#تعریف_کرو GL_MEDIUM_FLOAT                   0x8DF1
#تعریف_کرو GL_بلند_FLOAT                     0x8DF2
#تعریف_کرو GL_کم_INT                        0x8DF3
#تعریف_کرو GL_MEDIUM_INT                     0x8DF4
#تعریف_کرو GL_بلند_INT                       0x8DF5
#تعریف_کرو GL_FRAMEBUFFER                    0x8D40
#تعریف_کرو GL_RENDERBUFFER                   0x8D41
#تعریف_کرو GL_RGBA4                          0x8056
#تعریف_کرو GL_RGB5_A1                        0x8057
#تعریف_کرو GL_RGB565                         0x8D62
#تعریف_کرو GL_گہرائی_COMPONENT16              0x81A5
#تعریف_کرو GL_STENCIL_INDEX8                 0x8D48
#تعریف_کرو GL_RENDERBUFFER_چوڑائی             0x8D42
#تعریف_کرو GL_RENDERBUFFER_اونچائی            0x8D43
#تعریف_کرو GL_RENDERBUFFER_اندرونی_FORMAT   0x8D44
#تعریف_کرو GL_RENDERBUFFER_RED_سائز          0x8D50
#تعریف_کرو GL_RENDERBUFFER_GREEN_سائز        0x8D51
#تعریف_کرو GL_RENDERBUFFER_BLUE_سائز         0x8D52
#تعریف_کرو GL_RENDERBUFFER_ALPHA_سائز        0x8D53
#تعریف_کرو GL_RENDERBUFFER_گہرائی_سائز        0x8D54
#تعریف_کرو GL_RENDERBUFFER_STENCIL_سائز      0x8D55
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE 0x8CD0
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME 0x8CD1
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL 0x8CD2
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE 0x8CD3
#تعریف_کرو GL_COLOR_ATTACHMENT0              0x8CE0
#تعریف_کرو GL_گہرائی_ATTACHMENT               0x8D00
#تعریف_کرو GL_STENCIL_ATTACHMENT             0x8D20
#تعریف_کرو GL_NONE                           0
#تعریف_کرو GL_FRAMEBUFFER_COMPLETE           0x8CD5
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT 0x8CD6
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 0x8CD7
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS 0x8CD9
#تعریف_کرو GL_FRAMEBUFFER_UNSUPPORTED        0x8CDD
#تعریف_کرو GL_FRAMEBUFFER_BINDING            0x8CA6
#تعریف_کرو GL_RENDERBUFFER_BINDING           0x8CA7
#تعریف_کرو GL_MAX_RENDERBUFFER_سائز          0x84E8
#تعریف_کرو GL_INVALID_FRAMEBUFFER_OPERATION  0x0506
قسمتعریف خالی (GL_APIENTRYP PFNGLACTIVETEXTUREPROC) (GLenum texture);
قسمتعریف خالی (GL_APIENTRYP PFNGLATTACHSHADERPROC) (GLuint پروگرام, GLuint shader);
قسمتعریف خالی (GL_APIENTRYP PFNGLBINDATTRIBLOCATIONPROC) (GLuint پروگرام, GLuint اشاریہ, ثابت GLchar *name);
قسمتعریف خالی (GL_APIENTRYP PFNGLBINDBUFFERPROC) (GLenum ہدف, GLuint بفر_2);
قسمتعریف خالی (GL_APIENTRYP PFNGLBINDFRAMEBUFFERPROC) (GLenum ہدف, GLuint framebuffer);
قسمتعریف خالی (GL_APIENTRYP PFNGLBINDRENDERBUFFERPROC) (GLenum ہدف, GLuint renderbuffer);
قسمتعریف خالی (GL_APIENTRYP PFNGLBINDTEXTUREPROC) (GLenum ہدف, GLuint texture);
قسمتعریف خالی (GL_APIENTRYP PFNGLBLENDCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
قسمتعریف خالی (GL_APIENTRYP PFNGLBLENDEQUATIONPROC) (GLenum منوال);
قسمتعریف خالی (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEPROC) (GLenum منوال_RGB, GLenum منوال_Alpha);
قسمتعریف خالی (GL_APIENTRYP PFNGLBLENDFUNCPROC) (GLenum sfactor, GLenum dfactor);
قسمتعریف خالی (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEPROC) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
قسمتعریف خالی (GL_APIENTRYP PFNGLBUFFERDATAPROC) (GLenum ہدف, GLsizeiptr سائز, ثابت خالی *ڈیٹا, GLenum usage);
قسمتعریف خالی (GL_APIENTRYP PFNGLBUFFERSUBDATAPROC) (GLenum ہدف, GLintptr انحراف_2, GLsizeiptr سائز, ثابت خالی *ڈیٹا);
قسمتعریف GLenum (GL_APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSPROC) (GLenum ہدف);
قسمتعریف خالی (GL_APIENTRYP PFNGLCLEARPROC) (GLbitfield نقاب);
قسمتعریف خالی (GL_APIENTRYP PFNGLCLEARCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
قسمتعریف خالی (GL_APIENTRYP PFNGLCLEARDEPTHFPROC) (GLfloat d);
قسمتعریف خالی (GL_APIENTRYP PFNGLCLEARSTENCILPROC) (GLint s);
قسمتعریف خالی (GL_APIENTRYP PFNGLCOLORMASKPROC) (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
قسمتعریف خالی (GL_APIENTRYP PFNGLCOMPILESHADERPROC) (GLuint shader);
قسمتعریف خالی (GL_APIENTRYP PFNGLCOMPRESSEDTEXIMAGE2DPROC) (GLenum ہدف, GLint level, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی, GLint border, GLsizei image_سائز, ثابت خالی *ڈیٹا);
قسمتعریف خالی (GL_APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) (GLenum ہدف, GLint level, GLint xoffset, GLint yoffset, GLsizei چوڑائی, GLsizei اونچائی, GLenum format, GLsizei image_سائز, ثابت خالی *ڈیٹا);
قسمتعریف خالی (GL_APIENTRYP PFNGLCOPYTEXIMAGE2DPROC) (GLenum ہدف, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei چوڑائی, GLsizei اونچائی, GLint border);
قسمتعریف خالی (GL_APIENTRYP PFNGLCOPYTEXSUBIMAGE2DPROC) (GLenum ہدف, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei چوڑائی, GLsizei اونچائی);
قسمتعریف GLuint (GL_APIENTRYP PFNGLCREATEPROGRAMPROC) (خالی);
قسمتعریف GLuint (GL_APIENTRYP PFNGLCREATESHADERPROC) (GLenum type);
قسمتعریف خالی (GL_APIENTRYP PFNGLCULLFACEPROC) (GLenum منوال);
قسمتعریف خالی (GL_APIENTRYP PFNGLDELETEBUFFERSPROC) (GLsizei n, ثابت GLuint *buffers);
قسمتعریف خالی (GL_APIENTRYP PFNGLDELETEFRAMEBUFFERSPROC) (GLsizei n, ثابت GLuint *framebuffers);
قسمتعریف خالی (GL_APIENTRYP PFNGLDELETEPROGRAMPROC) (GLuint پروگرام);
قسمتعریف خالی (GL_APIENTRYP PFNGLDELETERENDERBUFFERSPROC) (GLsizei n, ثابت GLuint *renderbuffers);
قسمتعریف خالی (GL_APIENTRYP PFNGLDELETESHADERPROC) (GLuint shader);
قسمتعریف خالی (GL_APIENTRYP PFNGLDELETETEXTURESPROC) (GLsizei n, ثابت GLuint *textures);
قسمتعریف خالی (GL_APIENTRYP PFNGLDEPTHFUNCPROC) (GLenum func);
قسمتعریف خالی (GL_APIENTRYP PFNGLDEPTHMASKPROC) (GLboolean flag);
قسمتعریف خالی (GL_APIENTRYP PFNGLDEPTHRANGEFPROC) (GLfloat n, GLfloat f);
قسمتعریف خالی (GL_APIENTRYP PFNGLDETACHSHADERPROC) (GLuint پروگرام, GLuint shader);
قسمتعریف خالی (GL_APIENTRYP PFNGLDISABLEPROC) (GLenum cap);
قسمتعریف خالی (GL_APIENTRYP PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint اشاریہ);
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWARRAYSPROC) (GLenum منوال, GLint پہلا, GLsizei گنتی);
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWELEMENTSPROC) (GLenum منوال, GLsizei گنتی, GLenum type, ثابت خالی *indices);
قسمتعریف خالی (GL_APIENTRYP PFNGLENABLEPROC) (GLenum cap);
قسمتعریف خالی (GL_APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint اشاریہ);
قسمتعریف خالی (GL_APIENTRYP PFNGLFINISHPROC) (خالی);
قسمتعریف خالی (GL_APIENTRYP PFNGLFLUSHPROC) (خالی);
قسمتعریف خالی (GL_APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFERPROC) (GLenum ہدف, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
قسمتعریف خالی (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DPROC) (GLenum ہدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
قسمتعریف خالی (GL_APIENTRYP PFNGLFRONTFACEPROC) (GLenum منوال);
قسمتعریف خالی (GL_APIENTRYP PFNGLGENBUFFERSPROC) (GLsizei n, GLuint *buffers);
قسمتعریف خالی (GL_APIENTRYP PFNGLGENERATEMIPMAPPROC) (GLenum ہدف);
قسمتعریف خالی (GL_APIENTRYP PFNGLGENFRAMEBUFFERSPROC) (GLsizei n, GLuint *framebuffers);
قسمتعریف خالی (GL_APIENTRYP PFNGLGENRENDERBUFFERSPROC) (GLsizei n, GLuint *renderbuffers);
قسمتعریف خالی (GL_APIENTRYP PFNGLGENTEXTURESPROC) (GLsizei n, GLuint *textures);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETACTIVEATTRIBPROC) (GLuint پروگرام, GLuint اشاریہ, GLsizei buf_سائز, GLsizei *لمبائی, GLint *سائز, GLenum *type, GLchar *name);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETACTIVEUNIFORMPROC) (GLuint پروگرام, GLuint اشاریہ, GLsizei buf_سائز, GLsizei *لمبائی, GLint *سائز, GLenum *type, GLchar *name);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETATTACHEDSHADERSPROC) (GLuint پروگرام, GLsizei max_گنتی, GLsizei *گنتی, GLuint *shaders);
قسمتعریف GLint (GL_APIENTRYP PFNGLGETATTRIBLOCATIONPROC) (GLuint پروگرام, ثابت GLchar *name);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETBOOLEANVPROC) (GLenum pname, GLboolean *ڈیٹا);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETBUFFERPARAMETERIVPROC) (GLenum ہدف, GLenum pname, GLint *params);
قسمتعریف GLenum (GL_APIENTRYP PFNGLGETERRORPROC) (خالی);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETFLOATVPROC) (GLenum pname, GLfloat *ڈیٹا);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) (GLenum ہدف, GLenum attachment, GLenum pname, GLint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETINTEGERVPROC) (GLenum pname, GLint *ڈیٹا);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETPROGRAMIVPROC) (GLuint پروگرام, GLenum pname, GLint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETPROGRAMINFOLOGPROC) (GLuint پروگرام, GLsizei buf_سائز, GLsizei *لمبائی, GLchar *infoLog);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVPROC) (GLenum ہدف, GLenum pname, GLint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei buf_سائز, GLsizei *لمبائی, GLchar *infoLog);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETSHADERPRECISIONFORMATPROC) (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETSHADERSOURCEPROC) (GLuint shader, GLsizei buf_سائز, GLsizei *لمبائی, GLchar *ماخذ);
قسمتعریف ثابت GLubyte *(GL_APIENTRYP PFNGLGETSTRINGPROC) (GLenum name);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETTEXPARAMETERFVPROC) (GLenum ہدف, GLenum pname, GLfloat *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETTEXPARAMETERIVPROC) (GLenum ہدف, GLenum pname, GLint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETUNIFORMFVPROC) (GLuint پروگرام, GLint location, GLfloat *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETUNIFORMIVPROC) (GLuint پروگرام, GLint location, GLint *params);
قسمتعریف GLint (GL_APIENTRYP PFNGLGETUNIFORMLOCATIONPROC) (GLuint پروگرام, ثابت GLchar *name);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETVERTEXATTRIBFVPROC) (GLuint اشاریہ, GLenum pname, GLfloat *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETVERTEXATTRIBIVPROC) (GLuint اشاریہ, GLenum pname, GLint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETVERTEXATTRIBPOINTERVPROC) (GLuint اشاریہ, GLenum pname, خالی **اشارہ_گر_2);
قسمتعریف خالی (GL_APIENTRYP PFNGLHINTPROC) (GLenum ہدف, GLenum منوال);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLISBUFFERPROC) (GLuint بفر_2);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLISENABLEDPROC) (GLenum cap);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLISFRAMEBUFFERPROC) (GLuint framebuffer);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLISPROGRAMPROC) (GLuint پروگرام);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLISRENDERBUFFERPROC) (GLuint renderbuffer);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLISSHADERPROC) (GLuint shader);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLISTEXTUREPROC) (GLuint texture);
قسمتعریف خالی (GL_APIENTRYP PFNGLLINEWIDTHPROC) (GLfloat چوڑائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLLINKPROGRAMPROC) (GLuint پروگرام);
قسمتعریف خالی (GL_APIENTRYP PFNGLPIXELSTOREIPROC) (GLenum pname, GLint param);
قسمتعریف خالی (GL_APIENTRYP PFNGLPOLYGONOFFSETPROC) (GLfloat ضربی_عدد, GLfloat units);
قسمتعریف خالی (GL_APIENTRYP PFNGLREADPIXELSPROC) (GLint x, GLint y, GLsizei چوڑائی, GLsizei اونچائی, GLenum format, GLenum type, خالی *pixels);
قسمتعریف خالی (GL_APIENTRYP PFNGLRELEASESHADERCOMPILERPROC) (خالی);
قسمتعریف خالی (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEPROC) (GLenum ہدف, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLSAMPLECOVERAGEPROC) (GLfloat قدر, GLboolean invert);
قسمتعریف خالی (GL_APIENTRYP PFNGLSCISSORPROC) (GLint x, GLint y, GLsizei چوڑائی, GLsizei اونچائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLSHADERBINARYPROC) (GLsizei گنتی, ثابت GLuint *shaders, GLenum ثنائی_Format, ثابت خالی *ثنائی, GLsizei لمبائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei گنتی, ثابت GLchar *ثابت*string, ثابت GLint *لمبائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLSTENCILFUNCPROC) (GLenum func, GLint ref, GLuint نقاب);
قسمتعریف خالی (GL_APIENTRYP PFNGLSTENCILFUNCSEPARATEPROC) (GLenum face, GLenum func, GLint ref, GLuint نقاب);
قسمتعریف خالی (GL_APIENTRYP PFNGLSTENCILMASKPROC) (GLuint نقاب);
قسمتعریف خالی (GL_APIENTRYP PFNGLSTENCILMASKSEPARATEPROC) (GLenum face, GLuint نقاب);
قسمتعریف خالی (GL_APIENTRYP PFNGLSTENCILOPPROC) (GLenum fail, GLenum zfail, GLenum zpass);
قسمتعریف خالی (GL_APIENTRYP PFNGLSTENCILOPSEPARATEPROC) (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXIMAGE2DPROC) (GLenum ہدف, GLint level, GLint internalformat, GLsizei چوڑائی, GLsizei اونچائی, GLint border, GLenum format, GLenum type, ثابت خالی *pixels);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXPARAMETERFPROC) (GLenum ہدف, GLenum pname, GLfloat param);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXPARAMETERFVPROC) (GLenum ہدف, GLenum pname, ثابت GLfloat *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXPARAMETERIPROC) (GLenum ہدف, GLenum pname, GLint param);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXPARAMETERIVPROC) (GLenum ہدف, GLenum pname, ثابت GLint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXSUBIMAGE2DPROC) (GLenum ہدف, GLint level, GLint xoffset, GLint yoffset, GLsizei چوڑائی, GLsizei اونچائی, GLenum format, GLenum type, ثابت خالی *pixels);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM1FPROC) (GLint location, GLfloat v0);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM1FVPROC) (GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM1IPROC) (GLint location, GLint v0);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM1IVPROC) (GLint location, GLsizei گنتی, ثابت GLint *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM2FPROC) (GLint location, GLfloat v0, GLfloat v1);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM2FVPROC) (GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM2IPROC) (GLint location, GLint v0, GLint v1);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM2IVPROC) (GLint location, GLsizei گنتی, ثابت GLint *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM3FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM3FVPROC) (GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM3IPROC) (GLint location, GLint v0, GLint v1, GLint v2);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM3IVPROC) (GLint location, GLsizei گنتی, ثابت GLint *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM4FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM4FVPROC) (GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM4IPROC) (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM4IVPROC) (GLint location, GLsizei گنتی, ثابت GLint *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORMMATRIX2FVPROC) (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORMMATRIX3FVPROC) (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLUSEPROGRAMPROC) (GLuint پروگرام);
قسمتعریف خالی (GL_APIENTRYP PFNGLVALIDATEPROGRAMPROC) (GLuint پروگرام);
قسمتعریف خالی (GL_APIENTRYP PFNGLVERTEXATTRIB1FPROC) (GLuint اشاریہ, GLfloat x);
قسمتعریف خالی (GL_APIENTRYP PFNGLVERTEXATTRIB1FVPROC) (GLuint اشاریہ, ثابت GLfloat *v);
قسمتعریف خالی (GL_APIENTRYP PFNGLVERTEXATTRIB2FPROC) (GLuint اشاریہ, GLfloat x, GLfloat y);
قسمتعریف خالی (GL_APIENTRYP PFNGLVERTEXATTRIB2FVPROC) (GLuint اشاریہ, ثابت GLfloat *v);
قسمتعریف خالی (GL_APIENTRYP PFNGLVERTEXATTRIB3FPROC) (GLuint اشاریہ, GLfloat x, GLfloat y, GLfloat z);
قسمتعریف خالی (GL_APIENTRYP PFNGLVERTEXATTRIB3FVPROC) (GLuint اشاریہ, ثابت GLfloat *v);
قسمتعریف خالی (GL_APIENTRYP PFNGLVERTEXATTRIB4FPROC) (GLuint اشاریہ, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
قسمتعریف خالی (GL_APIENTRYP PFNGLVERTEXATTRIB4FVPROC) (GLuint اشاریہ, ثابت GLfloat *v);
قسمتعریف خالی (GL_APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC) (GLuint اشاریہ, GLint سائز, GLenum type, GLboolean normalized, GLsizei stride, ثابت خالی *اشارہ_گر_2);
قسمتعریف خالی (GL_APIENTRYP PFNGLVIEWPORTPROC) (GLint x, GLint y, GLsizei چوڑائی, GLsizei اونچائی);
#اگر GL_GLES_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_فعال_Texture (GLenum texture);
GL_APICALL خالی GL_APIENTRY glAttachShader (GLuint پروگرام, GLuint shader);
GL_APICALL خالی GL_APIENTRY glBindAttribLocation (GLuint پروگرام, GLuint اشاریہ, ثابت GLchar *name);
GL_APICALL خالی GL_APIENTRY gl_Bind_بفر (GLenum ہدف, GLuint بفر_2);
GL_APICALL خالی GL_APIENTRY glBindFramebuffer (GLenum ہدف, GLuint framebuffer);
GL_APICALL خالی GL_APIENTRY glBindRenderbuffer (GLenum ہدف, GLuint renderbuffer);
GL_APICALL خالی GL_APIENTRY glBindTexture (GLenum ہدف, GLuint texture);
GL_APICALL خالی GL_APIENTRY glBlendColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_APICALL خالی GL_APIENTRY glBlendEquation (GLenum منوال);
GL_APICALL خالی GL_APIENTRY glBlendEquationSeparate (GLenum منوال_RGB, GLenum منوال_Alpha);
GL_APICALL خالی GL_APIENTRY glBlendFunc (GLenum sfactor, GLenum dfactor);
GL_APICALL خالی GL_APIENTRY glBlendFuncSeparate (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
GL_APICALL خالی GL_APIENTRY gl_بفر_ڈیٹا (GLenum ہدف, GLsizeiptr سائز, ثابت خالی *ڈیٹا, GLenum usage);
GL_APICALL خالی GL_APIENTRY gl_بفر_Sub_ڈیٹا (GLenum ہدف, GLintptr انحراف_2, GLsizeiptr سائز, ثابت خالی *ڈیٹا);
GL_APICALL GLenum GL_APIENTRY gl_Check_Framebuffer_حالت (GLenum ہدف);
GL_APICALL خالی GL_APIENTRY glClear (GLbitfield نقاب);
GL_APICALL خالی GL_APIENTRY glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_APICALL خالی GL_APIENTRY glClearDepthf (GLfloat d);
GL_APICALL خالی GL_APIENTRY glClearStencil (GLint s);
GL_APICALL خالی GL_APIENTRY gl_Color_نقاب (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
GL_APICALL خالی GL_APIENTRY glCompileShader (GLuint shader);
GL_APICALL خالی GL_APIENTRY glCompressedTexImage2D (GLenum ہدف, GLint level, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی, GLint border, GLsizei image_سائز, ثابت خالی *ڈیٹا);
GL_APICALL خالی GL_APIENTRY glCompressedTexSubImage2D (GLenum ہدف, GLint level, GLint xoffset, GLint yoffset, GLsizei چوڑائی, GLsizei اونچائی, GLenum format, GLsizei image_سائز, ثابت خالی *ڈیٹا);
GL_APICALL خالی GL_APIENTRY glCopyTexImage2D (GLenum ہدف, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei چوڑائی, GLsizei اونچائی, GLint border);
GL_APICALL خالی GL_APIENTRY glCopyTexSubImage2D (GLenum ہدف, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei چوڑائی, GLsizei اونچائی);
GL_APICALL GLuint GL_APIENTRY gl_Create_پروگرام (خالی);
GL_APICALL GLuint GL_APIENTRY glCreateShader (GLenum type);
GL_APICALL خالی GL_APIENTRY glCullFace (GLenum منوال);
GL_APICALL خالی GL_APIENTRY glDeleteBuffers (GLsizei n, ثابت GLuint *buffers);
GL_APICALL خالی GL_APIENTRY glDeleteFramebuffers (GLsizei n, ثابت GLuint *framebuffers);
GL_APICALL خالی GL_APIENTRY gl_Delete_پروگرام (GLuint پروگرام);
GL_APICALL خالی GL_APIENTRY glDeleteRenderbuffers (GLsizei n, ثابت GLuint *renderbuffers);
GL_APICALL خالی GL_APIENTRY glDeleteShader (GLuint shader);
GL_APICALL خالی GL_APIENTRY glDeleteTextures (GLsizei n, ثابت GLuint *textures);
GL_APICALL خالی GL_APIENTRY gl_گہرائی_Func (GLenum func);
GL_APICALL خالی GL_APIENTRY gl_گہرائی_نقاب (GLboolean flag);
GL_APICALL خالی GL_APIENTRY gl_گہرائی_Rangef (GLfloat n, GLfloat f);
GL_APICALL خالی GL_APIENTRY glDetachShader (GLuint پروگرام, GLuint shader);
GL_APICALL خالی GL_APIENTRY glDisable (GLenum cap);
GL_APICALL خالی GL_APIENTRY gl_Disable_راس_Attrib_Array (GLuint اشاریہ);
GL_APICALL خالی GL_APIENTRY glDrawArrays (GLenum منوال, GLint پہلا, GLsizei گنتی);
GL_APICALL خالی GL_APIENTRY glDrawElements (GLenum منوال, GLsizei گنتی, GLenum type, ثابت خالی *indices);
GL_APICALL خالی GL_APIENTRY glEnable (GLenum cap);
GL_APICALL خالی GL_APIENTRY gl_Enable_راس_Attrib_Array (GLuint اشاریہ);
GL_APICALL خالی GL_APIENTRY gl_اختتام (خالی);
GL_APICALL خالی GL_APIENTRY glFlush (خالی);
GL_APICALL خالی GL_APIENTRY glFramebufferRenderbuffer (GLenum ہدف, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
GL_APICALL خالی GL_APIENTRY glFramebufferTexture2D (GLenum ہدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GL_APICALL خالی GL_APIENTRY glFrontFace (GLenum منوال);
GL_APICALL خالی GL_APIENTRY glGenBuffers (GLsizei n, GLuint *buffers);
GL_APICALL خالی GL_APIENTRY glGenerateMipmap (GLenum ہدف);
GL_APICALL خالی GL_APIENTRY glGenFramebuffers (GLsizei n, GLuint *framebuffers);
GL_APICALL خالی GL_APIENTRY glGenRenderbuffers (GLsizei n, GLuint *renderbuffers);
GL_APICALL خالی GL_APIENTRY glGenTextures (GLsizei n, GLuint *textures);
GL_APICALL خالی GL_APIENTRY gl_Get_فعال_Attrib (GLuint پروگرام, GLuint اشاریہ, GLsizei buf_سائز, GLsizei *لمبائی, GLint *سائز, GLenum *type, GLchar *name);
GL_APICALL خالی GL_APIENTRY gl_Get_فعال_یکساں (GLuint پروگرام, GLuint اشاریہ, GLsizei buf_سائز, GLsizei *لمبائی, GLint *سائز, GLenum *type, GLchar *name);
GL_APICALL خالی GL_APIENTRY glGetAttachedShaders (GLuint پروگرام, GLsizei max_گنتی, GLsizei *گنتی, GLuint *shaders);
GL_APICALL GLint GL_APIENTRY glGetAttribLocation (GLuint پروگرام, ثابت GLchar *name);
GL_APICALL خالی GL_APIENTRY glGetBooleanv (GLenum pname, GLboolean *ڈیٹا);
GL_APICALL خالی GL_APIENTRY gl_Get_بفر_Parameteriv (GLenum ہدف, GLenum pname, GLint *params);
GL_APICALL GLenum GL_APIENTRY glGetError (خالی);
GL_APICALL خالی GL_APIENTRY glGetFloatv (GLenum pname, GLfloat *ڈیٹا);
GL_APICALL خالی GL_APIENTRY glGetFramebufferAttachmentParameteriv (GLenum ہدف, GLenum attachment, GLenum pname, GLint *params);
GL_APICALL خالی GL_APIENTRY glGetIntegerv (GLenum pname, GLint *ڈیٹا);
GL_APICALL خالی GL_APIENTRY glGetProgramiv (GLuint پروگرام, GLenum pname, GLint *params);
GL_APICALL خالی GL_APIENTRY gl_Get_پروگرام_Info_Log (GLuint پروگرام, GLsizei buf_سائز, GLsizei *لمبائی, GLchar *infoLog);
GL_APICALL خالی GL_APIENTRY glGetRenderbufferParameteriv (GLenum ہدف, GLenum pname, GLint *params);
GL_APICALL خالی GL_APIENTRY glGetShaderiv (GLuint shader, GLenum pname, GLint *params);
GL_APICALL خالی GL_APIENTRY glGetShaderInfoLog (GLuint shader, GLsizei buf_سائز, GLsizei *لمبائی, GLchar *infoLog);
GL_APICALL خالی GL_APIENTRY glGetShaderPrecisionFormat (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
GL_APICALL خالی GL_APIENTRY gl_Get_Shader_ماخذ (GLuint shader, GLsizei buf_سائز, GLsizei *لمبائی, GLchar *ماخذ);
GL_APICALL ثابت GLubyte *GL_APIENTRY glGetString (GLenum name);
GL_APICALL خالی GL_APIENTRY glGetTexParameterfv (GLenum ہدف, GLenum pname, GLfloat *params);
GL_APICALL خالی GL_APIENTRY glGetTexParameteriv (GLenum ہدف, GLenum pname, GLint *params);
GL_APICALL خالی GL_APIENTRY glGetUniformfv (GLuint پروگرام, GLint location, GLfloat *params);
GL_APICALL خالی GL_APIENTRY glGetUniformiv (GLuint پروگرام, GLint location, GLint *params);
GL_APICALL GLint GL_APIENTRY gl_Get_یکساں_Location (GLuint پروگرام, ثابت GLchar *name);
GL_APICALL خالی GL_APIENTRY gl_Get_راس_Attribfv (GLuint اشاریہ, GLenum pname, GLfloat *params);
GL_APICALL خالی GL_APIENTRY gl_Get_راس_Attribiv (GLuint اشاریہ, GLenum pname, GLint *params);
GL_APICALL خالی GL_APIENTRY gl_Get_راس_Attrib_Pointerv (GLuint اشاریہ, GLenum pname, خالی **اشارہ_گر_2);
GL_APICALL خالی GL_APIENTRY glHint (GLenum ہدف, GLenum منوال);
GL_APICALL GLboolean GL_APIENTRY gl_Is_بفر (GLuint بفر_2);
GL_APICALL GLboolean GL_APIENTRY glIsEnabled (GLenum cap);
GL_APICALL GLboolean GL_APIENTRY glIsFramebuffer (GLuint framebuffer);
GL_APICALL GLboolean GL_APIENTRY gl_Is_پروگرام (GLuint پروگرام);
GL_APICALL GLboolean GL_APIENTRY glIsRenderbuffer (GLuint renderbuffer);
GL_APICALL GLboolean GL_APIENTRY glIsShader (GLuint shader);
GL_APICALL GLboolean GL_APIENTRY glIsTexture (GLuint texture);
GL_APICALL خالی GL_APIENTRY gl_سطر_چوڑائی (GLfloat چوڑائی);
GL_APICALL خالی GL_APIENTRY gl_Link_پروگرام (GLuint پروگرام);
GL_APICALL خالی GL_APIENTRY glPixelStorei (GLenum pname, GLint param);
GL_APICALL خالی GL_APIENTRY gl_Polygon_انحراف (GLfloat ضربی_عدد, GLfloat units);
GL_APICALL خالی GL_APIENTRY glReadPixels (GLint x, GLint y, GLsizei چوڑائی, GLsizei اونچائی, GLenum format, GLenum type, خالی *pixels);
GL_APICALL خالی GL_APIENTRY glReleaseShaderCompiler (خالی);
GL_APICALL خالی GL_APIENTRY glRenderbufferStorage (GLenum ہدف, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
GL_APICALL خالی GL_APIENTRY glSampleCoverage (GLfloat قدر, GLboolean invert);
GL_APICALL خالی GL_APIENTRY glScissor (GLint x, GLint y, GLsizei چوڑائی, GLsizei اونچائی);
GL_APICALL خالی GL_APIENTRY gl_Shader_ثنائی (GLsizei گنتی, ثابت GLuint *shaders, GLenum ثنائی_Format, ثابت خالی *ثنائی, GLsizei لمبائی);
GL_APICALL خالی GL_APIENTRY gl_Shader_ماخذ (GLuint shader, GLsizei گنتی, ثابت GLchar *ثابت*string, ثابت GLint *لمبائی);
GL_APICALL خالی GL_APIENTRY glStencilFunc (GLenum func, GLint ref, GLuint نقاب);
GL_APICALL خالی GL_APIENTRY glStencilFuncSeparate (GLenum face, GLenum func, GLint ref, GLuint نقاب);
GL_APICALL خالی GL_APIENTRY gl_Stencil_نقاب (GLuint نقاب);
GL_APICALL خالی GL_APIENTRY gl_Stencil_نقاب_Separate (GLenum face, GLuint نقاب);
GL_APICALL خالی GL_APIENTRY glStencilOp (GLenum fail, GLenum zfail, GLenum zpass);
GL_APICALL خالی GL_APIENTRY glStencilOpSeparate (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
GL_APICALL خالی GL_APIENTRY glTexImage2D (GLenum ہدف, GLint level, GLint internalformat, GLsizei چوڑائی, GLsizei اونچائی, GLint border, GLenum format, GLenum type, ثابت خالی *pixels);
GL_APICALL خالی GL_APIENTRY glTexParameterf (GLenum ہدف, GLenum pname, GLfloat param);
GL_APICALL خالی GL_APIENTRY glTexParameterfv (GLenum ہدف, GLenum pname, ثابت GLfloat *params);
GL_APICALL خالی GL_APIENTRY glTexParameteri (GLenum ہدف, GLenum pname, GLint param);
GL_APICALL خالی GL_APIENTRY glTexParameteriv (GLenum ہدف, GLenum pname, ثابت GLint *params);
GL_APICALL خالی GL_APIENTRY glTexSubImage2D (GLenum ہدف, GLint level, GLint xoffset, GLint yoffset, GLsizei چوڑائی, GLsizei اونچائی, GLenum format, GLenum type, ثابت خالی *pixels);
GL_APICALL خالی GL_APIENTRY glUniform1f (GLint location, GLfloat v0);
GL_APICALL خالی GL_APIENTRY glUniform1fv (GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY glUniform1i (GLint location, GLint v0);
GL_APICALL خالی GL_APIENTRY glUniform1iv (GLint location, GLsizei گنتی, ثابت GLint *قدر);
GL_APICALL خالی GL_APIENTRY glUniform2f (GLint location, GLfloat v0, GLfloat v1);
GL_APICALL خالی GL_APIENTRY glUniform2fv (GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY glUniform2i (GLint location, GLint v0, GLint v1);
GL_APICALL خالی GL_APIENTRY glUniform2iv (GLint location, GLsizei گنتی, ثابت GLint *قدر);
GL_APICALL خالی GL_APIENTRY glUniform3f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
GL_APICALL خالی GL_APIENTRY glUniform3fv (GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY glUniform3i (GLint location, GLint v0, GLint v1, GLint v2);
GL_APICALL خالی GL_APIENTRY glUniform3iv (GLint location, GLsizei گنتی, ثابت GLint *قدر);
GL_APICALL خالی GL_APIENTRY glUniform4f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
GL_APICALL خالی GL_APIENTRY glUniform4fv (GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY glUniform4i (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
GL_APICALL خالی GL_APIENTRY glUniform4iv (GLint location, GLsizei گنتی, ثابت GLint *قدر);
GL_APICALL خالی GL_APIENTRY gl_یکساں_Matrix2fv (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_یکساں_Matrix3fv (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_یکساں_Matrix4fv (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_Use_پروگرام (GLuint پروگرام);
GL_APICALL خالی GL_APIENTRY gl_Validate_پروگرام (GLuint پروگرام);
GL_APICALL خالی GL_APIENTRY gl_راس_Attrib1f (GLuint اشاریہ, GLfloat x);
GL_APICALL خالی GL_APIENTRY gl_راس_Attrib1fv (GLuint اشاریہ, ثابت GLfloat *v);
GL_APICALL خالی GL_APIENTRY gl_راس_Attrib2f (GLuint اشاریہ, GLfloat x, GLfloat y);
GL_APICALL خالی GL_APIENTRY gl_راس_Attrib2fv (GLuint اشاریہ, ثابت GLfloat *v);
GL_APICALL خالی GL_APIENTRY gl_راس_Attrib3f (GLuint اشاریہ, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL خالی GL_APIENTRY gl_راس_Attrib3fv (GLuint اشاریہ, ثابت GLfloat *v);
GL_APICALL خالی GL_APIENTRY gl_راس_Attrib4f (GLuint اشاریہ, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
GL_APICALL خالی GL_APIENTRY gl_راس_Attrib4fv (GLuint اشاریہ, ثابت GLfloat *v);
GL_APICALL خالی GL_APIENTRY gl_راس_Attrib_اشارہ_گر (GLuint اشاریہ, GLint سائز, GLenum type, GLboolean normalized, GLsizei stride, ثابت خالی *اشارہ_گر_2);
GL_APICALL خالی GL_APIENTRY glViewport (GLint x, GLint y, GLsizei چوڑائی, GLsizei اونچائی);
#اگر_ختم
#اگر_ختم /* GL_ES_VERSION_2_0 */

#اگر_غیر_تعریف_شدہ GL_ES_نسخہ_3_0
#تعریف_کرو GL_ES_نسخہ_3_0 1
قسمتعریف khronos_uint16_t GLhalf;
#تعریف_کرو GL_READ_بفر                    0x0C02
#تعریف_کرو GL_UNPACK_صف_لمبائی              0x0CF2
#تعریف_کرو GL_UNPACK_SKIP_صفیں               0x0CF3
#تعریف_کرو GL_UNPACK_SKIP_PIXELS             0x0CF4
#تعریف_کرو GL_PACK_صف_لمبائی                0x0D02
#تعریف_کرو GL_PACK_SKIP_صفیں                 0x0D03
#تعریف_کرو GL_PACK_SKIP_PIXELS               0x0D04
#تعریف_کرو GL_COLOR                          0x1800
#تعریف_کرو GL_گہرائی                          0x1801
#تعریف_کرو GL_STENCIL                        0x1802
#تعریف_کرو GL_RED                            0x1903
#تعریف_کرو GL_RGB8                           0x8051
#تعریف_کرو GL_RGBA8                          0x8058
#تعریف_کرو GL_RGB10_A2                       0x8059
#تعریف_کرو GL_TEXTURE_BINDING_3D             0x806A
#تعریف_کرو GL_UNPACK_SKIP_IMAGES             0x806D
#تعریف_کرو GL_UNPACK_IMAGE_اونچائی            0x806E
#تعریف_کرو GL_TEXTURE_3D                     0x806F
#تعریف_کرو GL_TEXTURE_WRAP_R                 0x8072
#تعریف_کرو GL_MAX_3_D_TEXTURE_سائز            0x8073
#تعریف_کرو GL_UNSIGNED_INT_2_10_10_10_REV    0x8368
#تعریف_کرو GL_MAX_ELEMENTS_VERTICES          0x80E8
#تعریف_کرو GL_MAX_ELEMENTS_INDICES           0x80E9
#تعریف_کرو GL_TEXTURE_MIN_LOD                0x813A
#تعریف_کرو GL_TEXTURE_MAX_LOD                0x813B
#تعریف_کرو GL_TEXTURE_بنیاد_LEVEL             0x813C
#تعریف_کرو GL_TEXTURE_MAX_LEVEL              0x813D
#تعریف_کرو GL_MIN                            0x8007
#تعریف_کرو GL_MAX                            0x8008
#تعریف_کرو GL_گہرائی_COMPONENT24              0x81A6
#تعریف_کرو GL_MAX_TEXTURE_LOD_BIAS           0x84FD
#تعریف_کرو GL_TEXTURE_COMPARE_منوال           0x884C
#تعریف_کرو GL_TEXTURE_COMPARE_FUNC           0x884D
#تعریف_کرو GL_CURRENT_QUERY                  0x8865
#تعریف_کرو GL_QUERY_نتیجہ                   0x8866
#تعریف_کرو GL_QUERY_نتیجہ_دستیاب         0x8867
#تعریف_کرو GL_بفر_MAPPED                  0x88BC
#تعریف_کرو GL_بفر_MAP_اشارہ_گر             0x88BD
#تعریف_کرو GL_دھارا_READ                    0x88E1
#تعریف_کرو GL_دھارا_COPY                    0x88E2
#تعریف_کرو GL_STATIC_READ                    0x88E5
#تعریف_کرو GL_STATIC_COPY                    0x88E6
#تعریف_کرو GL_DYNAMIC_READ                   0x88E9
#تعریف_کرو GL_DYNAMIC_COPY                   0x88EA
#تعریف_کرو GL_MAX_DRAW_BUFFERS               0x8824
#تعریف_کرو GL_DRAW_BUFFER0                   0x8825
#تعریف_کرو GL_DRAW_BUFFER1                   0x8826
#تعریف_کرو GL_DRAW_BUFFER2                   0x8827
#تعریف_کرو GL_DRAW_BUFFER3                   0x8828
#تعریف_کرو GL_DRAW_BUFFER4                   0x8829
#تعریف_کرو GL_DRAW_BUFFER5                   0x882A
#تعریف_کرو GL_DRAW_BUFFER6                   0x882B
#تعریف_کرو GL_DRAW_BUFFER7                   0x882C
#تعریف_کرو GL_DRAW_BUFFER8                   0x882D
#تعریف_کرو GL_DRAW_BUFFER9                   0x882E
#تعریف_کرو GL_DRAW_BUFFER10                  0x882F
#تعریف_کرو GL_DRAW_BUFFER11                  0x8830
#تعریف_کرو GL_DRAW_BUFFER12                  0x8831
#تعریف_کرو GL_DRAW_BUFFER13                  0x8832
#تعریف_کرو GL_DRAW_BUFFER14                  0x8833
#تعریف_کرو GL_DRAW_BUFFER15                  0x8834
#تعریف_کرو GL_MAX_FRAGMENT_یکساں_COMPONENTS 0x8B49
#تعریف_کرو GL_MAX_راس_یکساں_COMPONENTS  0x8B4A
#تعریف_کرو GL_SAMPLER_3D                     0x8B5F
#تعریف_کرو GL_SAMPLER_2D_SHADOW              0x8B62
#تعریف_کرو GL_FRAGMENT_SHADER_DERIVATIVE_HINT 0x8B8B
#تعریف_کرو GL_PIXEL_PACK_بفر              0x88EB
#تعریف_کرو GL_PIXEL_UNPACK_بفر            0x88EC
#تعریف_کرو GL_PIXEL_PACK_بفر_BINDING      0x88ED
#تعریف_کرو GL_PIXEL_UNPACK_بفر_BINDING    0x88EF
#تعریف_کرو GL_FLOAT_MAT2x3                   0x8B65
#تعریف_کرو GL_FLOAT_MAT2x4                   0x8B66
#تعریف_کرو GL_FLOAT_MAT3x2                   0x8B67
#تعریف_کرو GL_FLOAT_MAT3x4                   0x8B68
#تعریف_کرو GL_FLOAT_MAT4x2                   0x8B69
#تعریف_کرو GL_FLOAT_MAT4x3                   0x8B6A
#تعریف_کرو GL_SRGB                           0x8C40
#تعریف_کرو GL_SRGB8                          0x8C41
#تعریف_کرو GL_SRGB8_ALPHA8                   0x8C43
#تعریف_کرو GL_COMPARE_REF_مقصد_TEXTURE         0x884E
#تعریف_کرو GL_MAJOR_نسخہ                  0x821B
#تعریف_کرو GL_MINOR_نسخہ                  0x821C
#تعریف_کرو GL_عدد_EXTENSIONS                 0x821D
#تعریف_کرو GL_RGBA32F                        0x8814
#تعریف_کرو GL_RGB32F                         0x8815
#تعریف_کرو GL_RGBA16F                        0x881A
#تعریف_کرو GL_RGB16F                         0x881B
#تعریف_کرو GL_راس_ATTRIB_ARRAY_INTEGER    0x88FD
#تعریف_کرو GL_MAX_ARRAY_TEXTURE_LAYERS       0x88FF
#تعریف_کرو GL_MIN_پروگرام_TEXEL_انحراف       0x8904
#تعریف_کرو GL_MAX_پروگرام_TEXEL_انحراف       0x8905
#تعریف_کرو GL_MAX_VARYING_COMPONENTS         0x8B4B
#تعریف_کرو GL_TEXTURE_2D_ARRAY               0x8C1A
#تعریف_کرو GL_TEXTURE_BINDING_2D_ARRAY       0x8C1D
#تعریف_کرو GL_R11F_G11F_B10F                 0x8C3A
#تعریف_کرو GL_UNSIGNED_INT_10F_11F_11F_REV   0x8C3B
#تعریف_کرو GL_RGB9_E5                        0x8C3D
#تعریف_کرو GL_UNSIGNED_INT_5_9_9_9_REV       0x8C3E
#تعریف_کرو GL_TRANSFORM_FEEDBACK_VARYING_MAX_لمبائی 0x8C76
#تعریف_کرو GL_TRANSFORM_FEEDBACK_بفر_منوال 0x8C7F
#تعریف_کرو GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS 0x8C80
#تعریف_کرو GL_TRANSFORM_FEEDBACK_VARYINGS    0x8C83
#تعریف_کرو GL_TRANSFORM_FEEDBACK_بفر_آغاز 0x8C84
#تعریف_کرو GL_TRANSFORM_FEEDBACK_بفر_سائز 0x8C85
#تعریف_کرو GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN 0x8C88
#تعریف_کرو GL_RASTERIZER_DISCARD             0x8C89
#تعریف_کرو GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS 0x8C8A
#تعریف_کرو GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS 0x8C8B
#تعریف_کرو GL_INTERLEAVED_ATTRIBS            0x8C8C
#تعریف_کرو GL_SEPARATE_ATTRIBS               0x8C8D
#تعریف_کرو GL_TRANSFORM_FEEDBACK_بفر      0x8C8E
#تعریف_کرو GL_TRANSFORM_FEEDBACK_بفر_BINDING 0x8C8F
#تعریف_کرو GL_RGBA32UI                       0x8D70
#تعریف_کرو GL_RGB32UI                        0x8D71
#تعریف_کرو GL_RGBA16UI                       0x8D76
#تعریف_کرو GL_RGB16UI                        0x8D77
#تعریف_کرو GL_RGBA8UI                        0x8D7C
#تعریف_کرو GL_RGB8UI                         0x8D7D
#تعریف_کرو GL_RGBA32I                        0x8D82
#تعریف_کرو GL_RGB32I                         0x8D83
#تعریف_کرو GL_RGBA16I                        0x8D88
#تعریف_کرو GL_RGB16I                         0x8D89
#تعریف_کرو GL_RGBA8I                         0x8D8E
#تعریف_کرو GL_RGB8I                          0x8D8F
#تعریف_کرو GL_RED_INTEGER                    0x8D94
#تعریف_کرو GL_RGB_INTEGER                    0x8D98
#تعریف_کرو GL_RGBA_INTEGER                   0x8D99
#تعریف_کرو GL_SAMPLER_2D_ARRAY               0x8DC1
#تعریف_کرو GL_SAMPLER_2D_ARRAY_SHADOW        0x8DC4
#تعریف_کرو GL_SAMPLER_CUBE_SHADOW            0x8DC5
#تعریف_کرو GL_UNSIGNED_INT_VEC2              0x8DC6
#تعریف_کرو GL_UNSIGNED_INT_VEC3              0x8DC7
#تعریف_کرو GL_UNSIGNED_INT_VEC4              0x8DC8
#تعریف_کرو GL_INT_SAMPLER_2D                 0x8DCA
#تعریف_کرو GL_INT_SAMPLER_3D                 0x8DCB
#تعریف_کرو GL_INT_SAMPLER_CUBE               0x8DCC
#تعریف_کرو GL_INT_SAMPLER_2D_ARRAY           0x8DCF
#تعریف_کرو GL_UNSIGNED_INT_SAMPLER_2D        0x8DD2
#تعریف_کرو GL_UNSIGNED_INT_SAMPLER_3D        0x8DD3
#تعریف_کرو GL_UNSIGNED_INT_SAMPLER_CUBE      0x8DD4
#تعریف_کرو GL_UNSIGNED_INT_SAMPLER_2D_ARRAY  0x8DD7
#تعریف_کرو GL_بفر_ACCESS_FLAGS            0x911F
#تعریف_کرو GL_بفر_MAP_لمبائی              0x9120
#تعریف_کرو GL_بفر_MAP_انحراف              0x9121
#تعریف_کرو GL_گہرائی_COMPONENT32_F             0x8CAC
#تعریف_کرو GL_DEPTH32F_STENCIL8              0x8CAD
#تعریف_کرو GL_FLOAT_32_UNSIGNED_INT_24_8_REV 0x8DAD
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING 0x8210
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE 0x8211
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_RED_سائز 0x8212
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_GREEN_سائز 0x8213
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_BLUE_سائز 0x8214
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_ALPHA_سائز 0x8215
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_گہرائی_سائز 0x8216
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_STENCIL_سائز 0x8217
#تعریف_کرو GL_FRAMEBUFFER_DEFAULT            0x8218
#تعریف_کرو GL_FRAMEBUFFER_UNDEFINED          0x8219
#تعریف_کرو GL_گہرائی_STENCIL_ATTACHMENT       0x821A
#تعریف_کرو GL_گہرائی_STENCIL                  0x84F9
#تعریف_کرو GL_UNSIGNED_INT_24_8              0x84FA
#تعریف_کرو GL_DEPTH24_STENCIL8               0x88F0
#تعریف_کرو GL_UNSIGNED_NORMALIZED            0x8C17
#تعریف_کرو GL_DRAW_FRAMEBUFFER_BINDING       0x8CA6
#تعریف_کرو GL_READ_FRAMEBUFFER               0x8CA8
#تعریف_کرو GL_DRAW_FRAMEBUFFER               0x8CA9
#تعریف_کرو GL_READ_FRAMEBUFFER_BINDING       0x8CAA
#تعریف_کرو GL_RENDERBUFFER_SAMPLES           0x8CAB
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER 0x8CD4
#تعریف_کرو GL_MAX_COLOR_ATTACHMENTS          0x8CDF
#تعریف_کرو GL_COLOR_ATTACHMENT1              0x8CE1
#تعریف_کرو GL_COLOR_ATTACHMENT2              0x8CE2
#تعریف_کرو GL_COLOR_ATTACHMENT3              0x8CE3
#تعریف_کرو GL_COLOR_ATTACHMENT4              0x8CE4
#تعریف_کرو GL_COLOR_ATTACHMENT5              0x8CE5
#تعریف_کرو GL_COLOR_ATTACHMENT6              0x8CE6
#تعریف_کرو GL_COLOR_ATTACHMENT7              0x8CE7
#تعریف_کرو GL_COLOR_ATTACHMENT8              0x8CE8
#تعریف_کرو GL_COLOR_ATTACHMENT9              0x8CE9
#تعریف_کرو GL_COLOR_ATTACHMENT10             0x8CEA
#تعریف_کرو GL_COLOR_ATTACHMENT11             0x8CEB
#تعریف_کرو GL_COLOR_ATTACHMENT12             0x8CEC
#تعریف_کرو GL_COLOR_ATTACHMENT13             0x8CED
#تعریف_کرو GL_COLOR_ATTACHMENT14             0x8CEE
#تعریف_کرو GL_COLOR_ATTACHMENT15             0x8CEF
#تعریف_کرو GL_COLOR_ATTACHMENT16             0x8CF0
#تعریف_کرو GL_COLOR_ATTACHMENT17             0x8CF1
#تعریف_کرو GL_COLOR_ATTACHMENT18             0x8CF2
#تعریف_کرو GL_COLOR_ATTACHMENT19             0x8CF3
#تعریف_کرو GL_COLOR_ATTACHMENT20             0x8CF4
#تعریف_کرو GL_COLOR_ATTACHMENT21             0x8CF5
#تعریف_کرو GL_COLOR_ATTACHMENT22             0x8CF6
#تعریف_کرو GL_COLOR_ATTACHMENT23             0x8CF7
#تعریف_کرو GL_COLOR_ATTACHMENT24             0x8CF8
#تعریف_کرو GL_COLOR_ATTACHMENT25             0x8CF9
#تعریف_کرو GL_COLOR_ATTACHMENT26             0x8CFA
#تعریف_کرو GL_COLOR_ATTACHMENT27             0x8CFB
#تعریف_کرو GL_COLOR_ATTACHMENT28             0x8CFC
#تعریف_کرو GL_COLOR_ATTACHMENT29             0x8CFD
#تعریف_کرو GL_COLOR_ATTACHMENT30             0x8CFE
#تعریف_کرو GL_COLOR_ATTACHMENT31             0x8CFF
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE 0x8D56
#تعریف_کرو GL_MAX_SAMPLES                    0x8D57
#تعریف_کرو GL_HALF_FLOAT                     0x140B
#تعریف_کرو GL_MAP_READ_ثنائی_ہندسہ                   0x0001
#تعریف_کرو GL_MAP_WRITE_ثنائی_ہندسہ                  0x0002
#تعریف_کرو GL_MAP_INVALIDATE_RANGE_ثنائی_ہندسہ       0x0004
#تعریف_کرو GL_MAP_INVALIDATE_بفر_ثنائی_ہندسہ      0x0008
#تعریف_کرو GL_MAP_FLUSH_EXPLICIT_ثنائی_ہندسہ         0x0010
#تعریف_کرو GL_MAP_UNSYNCHRONIZED_ثنائی_ہندسہ         0x0020
#تعریف_کرو GL_RG                             0x8227
#تعریف_کرو GL_RG_INTEGER                     0x8228
#تعریف_کرو GL_R8                             0x8229
#تعریف_کرو GL_RG8                            0x822B
#تعریف_کرو GL_R16F                           0x822D
#تعریف_کرو GL_R32F                           0x822E
#تعریف_کرو GL_RG16F                          0x822F
#تعریف_کرو GL_RG32F                          0x8230
#تعریف_کرو GL_R8I                            0x8231
#تعریف_کرو GL_R8UI                           0x8232
#تعریف_کرو GL_R16I                           0x8233
#تعریف_کرو GL_R16UI                          0x8234
#تعریف_کرو GL_R32I                           0x8235
#تعریف_کرو GL_R32UI                          0x8236
#تعریف_کرو GL_RG8I                           0x8237
#تعریف_کرو GL_RG8UI                          0x8238
#تعریف_کرو GL_RG16I                          0x8239
#تعریف_کرو GL_RG16UI                         0x823A
#تعریف_کرو GL_RG32I                          0x823B
#تعریف_کرو GL_RG32UI                         0x823C
#تعریف_کرو GL_راس_ARRAY_BINDING           0x85B5
#تعریف_کرو GL_R8_SNORM                       0x8F94
#تعریف_کرو GL_RG8_SNORM                      0x8F95
#تعریف_کرو GL_RGB8_SNORM                     0x8F96
#تعریف_کرو GL_RGBA8_SNORM                    0x8F97
#تعریف_کرو GL_SIGNED_NORMALIZED              0x8F9C
#تعریف_کرو GL_PRIMITIVE_RESTART_FIXED_اشاریہ  0x8D69
#تعریف_کرو GL_COPY_READ_بفر               0x8F36
#تعریف_کرو GL_COPY_WRITE_بفر              0x8F37
#تعریف_کرو GL_COPY_READ_بفر_BINDING       0x8F36
#تعریف_کرو GL_COPY_WRITE_بفر_BINDING      0x8F37
#تعریف_کرو GL_یکساں_بفر                 0x8A11
#تعریف_کرو GL_یکساں_بفر_BINDING         0x8A28
#تعریف_کرو GL_یکساں_بفر_آغاز           0x8A29
#تعریف_کرو GL_یکساں_بفر_سائز            0x8A2A
#تعریف_کرو GL_MAX_راس_یکساں_بلاکیں      0x8A2B
#تعریف_کرو GL_MAX_FRAGMENT_یکساں_بلاکیں    0x8A2D
#تعریف_کرو GL_MAX_COMBINED_یکساں_بلاکیں    0x8A2E
#تعریف_کرو GL_MAX_یکساں_بفر_BINDINGS    0x8A2F
#تعریف_کرو GL_MAX_یکساں_بلاک_سائز         0x8A30
#تعریف_کرو GL_MAX_COMBINED_راس_یکساں_COMPONENTS 0x8A31
#تعریف_کرو GL_MAX_COMBINED_FRAGMENT_یکساں_COMPONENTS 0x8A33
#تعریف_کرو GL_یکساں_بفر_انحراف_ALIGNMENT 0x8A34
#تعریف_کرو GL_فعال_یکساں_بلاک_MAX_NAME_لمبائی 0x8A35
#تعریف_کرو GL_فعال_یکساں_بلاکیں          0x8A36
#تعریف_کرو GL_یکساں_TYPE                   0x8A37
#تعریف_کرو GL_یکساں_سائز                   0x8A38
#تعریف_کرو GL_یکساں_NAME_لمبائی            0x8A39
#تعریف_کرو GL_یکساں_بلاک_اشاریہ            0x8A3A
#تعریف_کرو GL_یکساں_انحراف                 0x8A3B
#تعریف_کرو GL_یکساں_ARRAY_STRIDE           0x8A3C
#تعریف_کرو GL_یکساں_میٹرکس_STRIDE          0x8A3D
#تعریف_کرو GL_یکساں_IS_صف_MAJOR           0x8A3E
#تعریف_کرو GL_یکساں_بلاک_BINDING          0x8A3F
#تعریف_کرو GL_یکساں_بلاک_ڈیٹا_سائز        0x8A40
#تعریف_کرو GL_یکساں_بلاک_NAME_لمبائی      0x8A41
#تعریف_کرو GL_یکساں_بلاک_فعال_UNIFORMS  0x8A42
#تعریف_کرو GL_یکساں_بلاک_فعال_یکساں_INDICES 0x8A43
#تعریف_کرو GL_یکساں_بلاک_REFERENCED_BY_راس_SHADER 0x8A44
#تعریف_کرو GL_یکساں_بلاک_REFERENCED_BY_FRAGMENT_SHADER 0x8A46
#تعریف_کرو GL_INVALID_اشاریہ                  0xFFFFFFFFu
#تعریف_کرو GL_MAX_راس_OUTPUT_COMPONENTS   0x9122
#تعریف_کرو GL_MAX_FRAGMENT_داخلہ_COMPONENTS  0x9125
#تعریف_کرو GL_MAX_SERVER_WAIT_TIMEOUT        0x9111
#تعریف_کرو GL_OBJECT_TYPE                    0x9112
#تعریف_کرو GL_SYNC_CONDITION                 0x9113
#تعریف_کرو GL_SYNC_حالت                    0x9114
#تعریف_کرو GL_SYNC_FLAGS                     0x9115
#تعریف_کرو GL_SYNC_FENCE                     0x9116
#تعریف_کرو GL_SYNC_GPU_COMMANDS_COMPLETE     0x9117
#تعریف_کرو GL_UNSIGNALED                     0x9118
#تعریف_کرو GL_SIGNALED                       0x9119
#تعریف_کرو GL_ALREADY_SIGNALED               0x911A
#تعریف_کرو GL_TIMEOUT_EXPIRED                0x911B
#تعریف_کرو GL_CONDITION_SATISFIED            0x911C
#تعریف_کرو GL_WAIT_FAILED                    0x911D
#تعریف_کرو GL_SYNC_FLUSH_COMMANDS_ثنائی_ہندسہ        0x00000001
#تعریف_کرو GL_TIMEOUT_IGNORED                0xFFFFFFFFFFFFFFFFull
#تعریف_کرو GL_راس_ATTRIB_ARRAY_مقسوم_علیہ    0x88FE
#تعریف_کرو GL_ANY_SAMPLES_PASSED             0x8C2F
#تعریف_کرو GL_ANY_SAMPLES_PASSED_CONSERVATIVE 0x8D6A
#تعریف_کرو GL_SAMPLER_BINDING                0x8919
#تعریف_کرو GL_RGB10_A2UI                     0x906F
#تعریف_کرو GL_TEXTURE_SWIZZLE_R              0x8E42
#تعریف_کرو GL_TEXTURE_SWIZZLE_G              0x8E43
#تعریف_کرو GL_TEXTURE_SWIZZLE_B              0x8E44
#تعریف_کرو GL_TEXTURE_SWIZZLE_A              0x8E45
#تعریف_کرو GL_GREEN                          0x1904
#تعریف_کرو GL_BLUE                           0x1905
#تعریف_کرو GL_INT_2_10_10_10_REV             0x8D9F
#تعریف_کرو GL_TRANSFORM_FEEDBACK             0x8E22
#تعریف_کرو GL_TRANSFORM_FEEDBACK_PAUSED      0x8E23
#تعریف_کرو GL_TRANSFORM_FEEDBACK_فعال      0x8E24
#تعریف_کرو GL_TRANSFORM_FEEDBACK_BINDING     0x8E25
#تعریف_کرو GL_پروگرام_ثنائی_RETRIEVABLE_HINT 0x8257
#تعریف_کرو GL_پروگرام_ثنائی_لمبائی          0x8741
#تعریف_کرو GL_عدد_پروگرام_ثنائی_FORMATS     0x87FE
#تعریف_کرو GL_پروگرام_ثنائی_FORMATS         0x87FF
#تعریف_کرو GL_COMPRESSED_R11_EAC             0x9270
#تعریف_کرو GL_COMPRESSED_SIGNED_R11_EAC      0x9271
#تعریف_کرو GL_COMPRESSED_RG11_EAC            0x9272
#تعریف_کرو GL_COMPRESSED_SIGNED_RG11_EAC     0x9273
#تعریف_کرو GL_COMPRESSED_RGB8_ETC2           0x9274
#تعریف_کرو GL_COMPRESSED_SRGB8_ETC2          0x9275
#تعریف_کرو GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9276
#تعریف_کرو GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9277
#تعریف_کرو GL_COMPRESSED_RGBA8_ETC2_EAC      0x9278
#تعریف_کرو GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC 0x9279
#تعریف_کرو GL_TEXTURE_IMMUTABLE_FORMAT       0x912F
#تعریف_کرو GL_MAX_ELEMENT_اشاریہ              0x8D6B
#تعریف_کرو GL_عدد_SAMPLE_COUNTS              0x9380
#تعریف_کرو GL_TEXTURE_IMMUTABLE_سطحیں       0x82DF
قسمتعریف خالی (GL_APIENTRYP PFNGLREADBUFFERPROC) (GLenum src);
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWRANGEELEMENTSPROC) (GLenum منوال, GLuint آغاز, GLuint انتہا, GLsizei گنتی, GLenum type, ثابت خالی *indices);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXIMAGE3DPROC) (GLenum ہدف, GLint level, GLint internalformat, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLint border, GLenum format, GLenum type, ثابت خالی *pixels);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXSUBIMAGE3DPROC) (GLenum ہدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLenum format, GLenum type, ثابت خالی *pixels);
قسمتعریف خالی (GL_APIENTRYP PFNGLCOPYTEXSUBIMAGE3DPROC) (GLenum ہدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei چوڑائی, GLsizei اونچائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLCOMPRESSEDTEXIMAGE3DPROC) (GLenum ہدف, GLint level, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLint border, GLsizei image_سائز, ثابت خالی *ڈیٹا);
قسمتعریف خالی (GL_APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC) (GLenum ہدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLenum format, GLsizei image_سائز, ثابت خالی *ڈیٹا);
قسمتعریف خالی (GL_APIENTRYP PFNGLGENQUERIESPROC) (GLsizei n, GLuint *ids);
قسمتعریف خالی (GL_APIENTRYP PFNGLDELETEQUERIESPROC) (GLsizei n, ثابت GLuint *ids);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLISQUERYPROC) (GLuint id);
قسمتعریف خالی (GL_APIENTRYP PFNGLBEGINQUERYPROC) (GLenum ہدف, GLuint id);
قسمتعریف خالی (GL_APIENTRYP PFNGLENDQUERYPROC) (GLenum ہدف);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETQUERYIVPROC) (GLenum ہدف, GLenum pname, GLint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETQUERYOBJECTUIVPROC) (GLuint id, GLenum pname, GLuint *params);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLUNMAPBUFFERPROC) (GLenum ہدف);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETBUFFERPOINTERVPROC) (GLenum ہدف, GLenum pname, خالی **params);
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWBUFFERSPROC) (GLsizei n, ثابت GLenum *bufs);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORMMATRIX2X3FVPROC) (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORMMATRIX3X2FVPROC) (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORMMATRIX2X4FVPROC) (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORMMATRIX4X2FVPROC) (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORMMATRIX3X4FVPROC) (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORMMATRIX4X3FVPROC) (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLBLITFRAMEBUFFERPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield نقاب, GLenum filter);
قسمتعریف خالی (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC) (GLenum ہدف, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURELAYERPROC) (GLenum ہدف, GLenum attachment, GLuint texture, GLint level, GLint layer);
قسمتعریف خالی *(GL_APIENTRYP PFNGLMAPBUFFERRANGEPROC) (GLenum ہدف, GLintptr انحراف_2, GLsizeiptr لمبائی, GLbitfield access);
قسمتعریف خالی (GL_APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEPROC) (GLenum ہدف, GLintptr انحراف_2, GLsizeiptr لمبائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLBINDVERTEXARRAYPROC) (GLuint array);
قسمتعریف خالی (GL_APIENTRYP PFNGLDELETEVERTEXARRAYSPROC) (GLsizei n, ثابت GLuint *arrays);
قسمتعریف خالی (GL_APIENTRYP PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint *arrays);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLISVERTEXARRAYPROC) (GLuint array);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETINTEGERI_VPROC) (GLenum ہدف, GLuint اشاریہ, GLint *ڈیٹا);
قسمتعریف خالی (GL_APIENTRYP PFNGLBEGINTRANSFORMFEEDBACKPROC) (GLenum primitive_منوال);
قسمتعریف خالی (GL_APIENTRYP PFNGLENDTRANSFORMFEEDBACKPROC) (خالی);
قسمتعریف خالی (GL_APIENTRYP PFNGLBINDBUFFERRANGEPROC) (GLenum ہدف, GLuint اشاریہ, GLuint بفر_2, GLintptr انحراف_2, GLsizeiptr سائز);
قسمتعریف خالی (GL_APIENTRYP PFNGLBINDBUFFERBASEPROC) (GLenum ہدف, GLuint اشاریہ, GLuint بفر_2);
قسمتعریف خالی (GL_APIENTRYP PFNGLTRANSFORMFEEDBACKVARYINGSPROC) (GLuint پروگرام, GLsizei گنتی, ثابت GLchar *ثابت*varyings, GLenum بفر_منوال);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETTRANSFORMFEEDBACKVARYINGPROC) (GLuint پروگرام, GLuint اشاریہ, GLsizei buf_سائز, GLsizei *لمبائی, GLsizei *سائز, GLenum *type, GLchar *name);
قسمتعریف خالی (GL_APIENTRYP PFNGLVERTEXATTRIBIPOINTERPROC) (GLuint اشاریہ, GLint سائز, GLenum type, GLsizei stride, ثابت خالی *اشارہ_گر_2);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETVERTEXATTRIBIIVPROC) (GLuint اشاریہ, GLenum pname, GLint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETVERTEXATTRIBIUIVPROC) (GLuint اشاریہ, GLenum pname, GLuint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLVERTEXATTRIBI4IPROC) (GLuint اشاریہ, GLint x, GLint y, GLint z, GLint w);
قسمتعریف خالی (GL_APIENTRYP PFNGLVERTEXATTRIBI4UIPROC) (GLuint اشاریہ, GLuint x, GLuint y, GLuint z, GLuint w);
قسمتعریف خالی (GL_APIENTRYP PFNGLVERTEXATTRIBI4IVPROC) (GLuint اشاریہ, ثابت GLint *v);
قسمتعریف خالی (GL_APIENTRYP PFNGLVERTEXATTRIBI4UIVPROC) (GLuint اشاریہ, ثابت GLuint *v);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETUNIFORMUIVPROC) (GLuint پروگرام, GLint location, GLuint *params);
قسمتعریف GLint (GL_APIENTRYP PFNGLGETFRAGDATALOCATIONPROC) (GLuint پروگرام, ثابت GLchar *name);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM1UIPROC) (GLint location, GLuint v0);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM2UIPROC) (GLint location, GLuint v0, GLuint v1);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM3UIPROC) (GLint location, GLuint v0, GLuint v1, GLuint v2);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM4UIPROC) (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM1UIVPROC) (GLint location, GLsizei گنتی, ثابت GLuint *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM2UIVPROC) (GLint location, GLsizei گنتی, ثابت GLuint *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM3UIVPROC) (GLint location, GLsizei گنتی, ثابت GLuint *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORM4UIVPROC) (GLint location, GLsizei گنتی, ثابت GLuint *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLCLEARBUFFERIVPROC) (GLenum بفر_2, GLint drawbuffer, ثابت GLint *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLCLEARBUFFERUIVPROC) (GLenum بفر_2, GLint drawbuffer, ثابت GLuint *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLCLEARBUFFERFVPROC) (GLenum بفر_2, GLint drawbuffer, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLCLEARBUFFERFIPROC) (GLenum بفر_2, GLint drawbuffer, GLfloat گہرائی_2, GLint stencil);
قسمتعریف ثابت GLubyte *(GL_APIENTRYP PFNGLGETSTRINGIPROC) (GLenum name, GLuint اشاریہ);
قسمتعریف خالی (GL_APIENTRYP PFNGLCOPYBUFFERSUBDATAPROC) (GLenum read_ہدف, GLenum write_ہدف, GLintptr read_انحراف, GLintptr write_انحراف, GLsizeiptr سائز);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETUNIFORMINDICESPROC) (GLuint پروگرام, GLsizei یکساں_گنتی, ثابت GLchar *ثابت*یکساں_نام, GLuint *یکساں_Indices);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETACTIVEUNIFORMSIVPROC) (GLuint پروگرام, GLsizei یکساں_گنتی, ثابت GLuint *یکساں_Indices, GLenum pname, GLint *params);
قسمتعریف GLuint (GL_APIENTRYP PFNGLGETUNIFORMBLOCKINDEXPROC) (GLuint پروگرام, ثابت GLchar *یکساں_بلاک_Name);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKIVPROC) (GLuint پروگرام, GLuint یکساں_بلاک_اشاریہ, GLenum pname, GLint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC) (GLuint پروگرام, GLuint یکساں_بلاک_اشاریہ, GLsizei buf_سائز, GLsizei *لمبائی, GLchar *یکساں_بلاک_Name);
قسمتعریف خالی (GL_APIENTRYP PFNGLUNIFORMBLOCKBINDINGPROC) (GLuint پروگرام, GLuint یکساں_بلاک_اشاریہ, GLuint یکساں_بلاک_Binding);
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDPROC) (GLenum منوال, GLint پہلا, GLsizei گنتی, GLsizei instancecount);
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDPROC) (GLenum منوال, GLsizei گنتی, GLenum type, ثابت خالی *indices, GLsizei instancecount);
قسمتعریف GLsync (GL_APIENTRYP PFNGLFENCESYNCPROC) (GLenum condition, GLbitfield flags);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLISSYNCPROC) (GLsync sync);
قسمتعریف خالی (GL_APIENTRYP PFNGLDELETESYNCPROC) (GLsync sync);
قسمتعریف GLenum (GL_APIENTRYP PFNGLCLIENTWAITSYNCPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
قسمتعریف خالی (GL_APIENTRYP PFNGLWAITSYNCPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETINTEGER64VPROC) (GLenum pname, GLint64 *ڈیٹا);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETSYNCIVPROC) (GLsync sync, GLenum pname, GLsizei گنتی, GLsizei *لمبائی, GLint *اقدار);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETINTEGER64I_VPROC) (GLenum ہدف, GLuint اشاریہ, GLint64 *ڈیٹا);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETBUFFERPARAMETERI64VPROC) (GLenum ہدف, GLenum pname, GLint64 *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGENSAMPLERSPROC) (GLsizei گنتی, GLuint *samplers);
قسمتعریف خالی (GL_APIENTRYP PFNGLDELETESAMPLERSPROC) (GLsizei گنتی, ثابت GLuint *samplers);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLISSAMPLERPROC) (GLuint sampler);
قسمتعریف خالی (GL_APIENTRYP PFNGLBINDSAMPLERPROC) (GLuint unit, GLuint sampler);
قسمتعریف خالی (GL_APIENTRYP PFNGLSAMPLERPARAMETERIPROC) (GLuint sampler, GLenum pname, GLint param);
قسمتعریف خالی (GL_APIENTRYP PFNGLSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, ثابت GLint *param);
قسمتعریف خالی (GL_APIENTRYP PFNGLSAMPLERPARAMETERFPROC) (GLuint sampler, GLenum pname, GLfloat param);
قسمتعریف خالی (GL_APIENTRYP PFNGLSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, ثابت GLfloat *param);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, GLint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, GLfloat *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLVERTEXATTRIBDIVISORPROC) (GLuint اشاریہ, GLuint مقسوم_علیہ);
قسمتعریف خالی (GL_APIENTRYP PFNGLBINDTRANSFORMFEEDBACKPROC) (GLenum ہدف, GLuint id);
قسمتعریف خالی (GL_APIENTRYP PFNGLDELETETRANSFORMFEEDBACKSPROC) (GLsizei n, ثابت GLuint *ids);
قسمتعریف خالی (GL_APIENTRYP PFNGLGENTRANSFORMFEEDBACKSPROC) (GLsizei n, GLuint *ids);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLISTRANSFORMFEEDBACKPROC) (GLuint id);
قسمتعریف خالی (GL_APIENTRYP PFNGLPAUSETRANSFORMFEEDBACKPROC) (خالی);
قسمتعریف خالی (GL_APIENTRYP PFNGLRESUMETRANSFORMFEEDBACKPROC) (خالی);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETPROGRAMBINARYPROC) (GLuint پروگرام, GLsizei buf_سائز, GLsizei *لمبائی, GLenum *ثنائی_Format, خالی *ثنائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMBINARYPROC) (GLuint پروگرام, GLenum ثنائی_Format, ثابت خالی *ثنائی, GLsizei لمبائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMPARAMETERIPROC) (GLuint پروگرام, GLenum pname, GLint قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLINVALIDATEFRAMEBUFFERPROC) (GLenum ہدف, GLsizei عدد_Attachments, ثابت GLenum *attachments);
قسمتعریف خالی (GL_APIENTRYP PFNGLINVALIDATESUBFRAMEBUFFERPROC) (GLenum ہدف, GLsizei عدد_Attachments, ثابت GLenum *attachments, GLint x, GLint y, GLsizei چوڑائی, GLsizei اونچائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXSTORAGE2DPROC) (GLenum ہدف, GLsizei سطحیں, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXSTORAGE3DPROC) (GLenum ہدف, GLsizei سطحیں, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETINTERNALFORMATIVPROC) (GLenum ہدف, GLenum internalformat, GLenum pname, GLsizei گنتی, GLint *params);
#اگر GL_GLES_PROTOTYPES
GL_APICALL خالی GL_APIENTRY gl_Read_بفر (GLenum src);
GL_APICALL خالی GL_APIENTRY glDrawRangeElements (GLenum منوال, GLuint آغاز, GLuint انتہا, GLsizei گنتی, GLenum type, ثابت خالی *indices);
GL_APICALL خالی GL_APIENTRY glTexImage3D (GLenum ہدف, GLint level, GLint internalformat, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLint border, GLenum format, GLenum type, ثابت خالی *pixels);
GL_APICALL خالی GL_APIENTRY glTexSubImage3D (GLenum ہدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLenum format, GLenum type, ثابت خالی *pixels);
GL_APICALL خالی GL_APIENTRY glCopyTexSubImage3D (GLenum ہدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei چوڑائی, GLsizei اونچائی);
GL_APICALL خالی GL_APIENTRY glCompressedTexImage3D (GLenum ہدف, GLint level, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLint border, GLsizei image_سائز, ثابت خالی *ڈیٹا);
GL_APICALL خالی GL_APIENTRY glCompressedTexSubImage3D (GLenum ہدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2, GLenum format, GLsizei image_سائز, ثابت خالی *ڈیٹا);
GL_APICALL خالی GL_APIENTRY glGenQueries (GLsizei n, GLuint *ids);
GL_APICALL خالی GL_APIENTRY glDeleteQueries (GLsizei n, ثابت GLuint *ids);
GL_APICALL GLboolean GL_APIENTRY glIsQuery (GLuint id);
GL_APICALL خالی GL_APIENTRY glBeginQuery (GLenum ہدف, GLuint id);
GL_APICALL خالی GL_APIENTRY gl_انتہا_Query (GLenum ہدف);
GL_APICALL خالی GL_APIENTRY glGetQueryiv (GLenum ہدف, GLenum pname, GLint *params);
GL_APICALL خالی GL_APIENTRY glGetQueryObjectuiv (GLuint id, GLenum pname, GLuint *params);
GL_APICALL GLboolean GL_APIENTRY gl_Unmap_بفر (GLenum ہدف);
GL_APICALL خالی GL_APIENTRY gl_Get_بفر_Pointerv (GLenum ہدف, GLenum pname, خالی **params);
GL_APICALL خالی GL_APIENTRY glDrawBuffers (GLsizei n, ثابت GLenum *bufs);
GL_APICALL خالی GL_APIENTRY gl_یکساں_Matrix2x3fv (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_یکساں_Matrix3x2fv (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_یکساں_Matrix2x4fv (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_یکساں_Matrix4x2fv (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_یکساں_Matrix3x4fv (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_یکساں_Matrix4x3fv (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY glBlitFramebuffer (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield نقاب, GLenum filter);
GL_APICALL خالی GL_APIENTRY glRenderbufferStorageMultisample (GLenum ہدف, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
GL_APICALL خالی GL_APIENTRY glFramebufferTextureLayer (GLenum ہدف, GLenum attachment, GLuint texture, GLint level, GLint layer);
GL_APICALL خالی *GL_APIENTRY gl_Map_بفر_Range (GLenum ہدف, GLintptr انحراف_2, GLsizeiptr لمبائی, GLbitfield access);
GL_APICALL خالی GL_APIENTRY gl_Flush_Mapped_بفر_Range (GLenum ہدف, GLintptr انحراف_2, GLsizeiptr لمبائی);
GL_APICALL خالی GL_APIENTRY gl_Bind_راس_Array (GLuint array);
GL_APICALL خالی GL_APIENTRY gl_Delete_راس_Arrays (GLsizei n, ثابت GLuint *arrays);
GL_APICALL خالی GL_APIENTRY gl_Gen_راس_Arrays (GLsizei n, GLuint *arrays);
GL_APICALL GLboolean GL_APIENTRY gl_Is_راس_Array (GLuint array);
GL_APICALL خالی GL_APIENTRY glGetIntegeri_v (GLenum ہدف, GLuint اشاریہ, GLint *ڈیٹا);
GL_APICALL خالی GL_APIENTRY glBeginTransformFeedback (GLenum primitive_منوال);
GL_APICALL خالی GL_APIENTRY gl_انتہا_Transform_Feedback (خالی);
GL_APICALL خالی GL_APIENTRY gl_Bind_بفر_Range (GLenum ہدف, GLuint اشاریہ, GLuint بفر_2, GLintptr انحراف_2, GLsizeiptr سائز);
GL_APICALL خالی GL_APIENTRY gl_Bind_بفر_بنیاد (GLenum ہدف, GLuint اشاریہ, GLuint بفر_2);
GL_APICALL خالی GL_APIENTRY glTransformFeedbackVaryings (GLuint پروگرام, GLsizei گنتی, ثابت GLchar *ثابت*varyings, GLenum بفر_منوال);
GL_APICALL خالی GL_APIENTRY glGetTransformFeedbackVarying (GLuint پروگرام, GLuint اشاریہ, GLsizei buf_سائز, GLsizei *لمبائی, GLsizei *سائز, GLenum *type, GLchar *name);
GL_APICALL خالی GL_APIENTRY gl_راس_Attrib_IPointer (GLuint اشاریہ, GLint سائز, GLenum type, GLsizei stride, ثابت خالی *اشارہ_گر_2);
GL_APICALL خالی GL_APIENTRY gl_Get_راس_Attrib_Iiv (GLuint اشاریہ, GLenum pname, GLint *params);
GL_APICALL خالی GL_APIENTRY gl_Get_راس_Attrib_Iuiv (GLuint اشاریہ, GLenum pname, GLuint *params);
GL_APICALL خالی GL_APIENTRY gl_راس_Attrib_I4i (GLuint اشاریہ, GLint x, GLint y, GLint z, GLint w);
GL_APICALL خالی GL_APIENTRY gl_راس_Attrib_I4ui (GLuint اشاریہ, GLuint x, GLuint y, GLuint z, GLuint w);
GL_APICALL خالی GL_APIENTRY gl_راس_Attrib_I4iv (GLuint اشاریہ, ثابت GLint *v);
GL_APICALL خالی GL_APIENTRY gl_راس_Attrib_I4uiv (GLuint اشاریہ, ثابت GLuint *v);
GL_APICALL خالی GL_APIENTRY glGetUniformuiv (GLuint پروگرام, GLint location, GLuint *params);
GL_APICALL GLint GL_APIENTRY gl_Get_Frag_ڈیٹا_Location (GLuint پروگرام, ثابت GLchar *name);
GL_APICALL خالی GL_APIENTRY glUniform1ui (GLint location, GLuint v0);
GL_APICALL خالی GL_APIENTRY glUniform2ui (GLint location, GLuint v0, GLuint v1);
GL_APICALL خالی GL_APIENTRY glUniform3ui (GLint location, GLuint v0, GLuint v1, GLuint v2);
GL_APICALL خالی GL_APIENTRY glUniform4ui (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
GL_APICALL خالی GL_APIENTRY glUniform1uiv (GLint location, GLsizei گنتی, ثابت GLuint *قدر);
GL_APICALL خالی GL_APIENTRY glUniform2uiv (GLint location, GLsizei گنتی, ثابت GLuint *قدر);
GL_APICALL خالی GL_APIENTRY glUniform3uiv (GLint location, GLsizei گنتی, ثابت GLuint *قدر);
GL_APICALL خالی GL_APIENTRY glUniform4uiv (GLint location, GLsizei گنتی, ثابت GLuint *قدر);
GL_APICALL خالی GL_APIENTRY glClearBufferiv (GLenum بفر_2, GLint drawbuffer, ثابت GLint *قدر);
GL_APICALL خالی GL_APIENTRY glClearBufferuiv (GLenum بفر_2, GLint drawbuffer, ثابت GLuint *قدر);
GL_APICALL خالی GL_APIENTRY glClearBufferfv (GLenum بفر_2, GLint drawbuffer, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY glClearBufferfi (GLenum بفر_2, GLint drawbuffer, GLfloat گہرائی_2, GLint stencil);
GL_APICALL ثابت GLubyte *GL_APIENTRY glGetStringi (GLenum name, GLuint اشاریہ);
GL_APICALL خالی GL_APIENTRY gl_Copy_بفر_Sub_ڈیٹا (GLenum read_ہدف, GLenum write_ہدف, GLintptr read_انحراف, GLintptr write_انحراف, GLsizeiptr سائز);
GL_APICALL خالی GL_APIENTRY gl_Get_یکساں_Indices (GLuint پروگرام, GLsizei یکساں_گنتی, ثابت GLchar *ثابت*یکساں_نام, GLuint *یکساں_Indices);
GL_APICALL خالی GL_APIENTRY gl_Get_فعال_Uniformsiv (GLuint پروگرام, GLsizei یکساں_گنتی, ثابت GLuint *یکساں_Indices, GLenum pname, GLint *params);
GL_APICALL GLuint GL_APIENTRY gl_Get_یکساں_بلاک_اشاریہ (GLuint پروگرام, ثابت GLchar *یکساں_بلاک_Name);
GL_APICALL خالی GL_APIENTRY gl_Get_فعال_یکساں_Blockiv (GLuint پروگرام, GLuint یکساں_بلاک_اشاریہ, GLenum pname, GLint *params);
GL_APICALL خالی GL_APIENTRY gl_Get_فعال_یکساں_بلاک_Name (GLuint پروگرام, GLuint یکساں_بلاک_اشاریہ, GLsizei buf_سائز, GLsizei *لمبائی, GLchar *یکساں_بلاک_Name);
GL_APICALL خالی GL_APIENTRY gl_یکساں_بلاک_Binding (GLuint پروگرام, GLuint یکساں_بلاک_اشاریہ, GLuint یکساں_بلاک_Binding);
GL_APICALL خالی GL_APIENTRY glDrawArraysInstanced (GLenum منوال, GLint پہلا, GLsizei گنتی, GLsizei instancecount);
GL_APICALL خالی GL_APIENTRY glDrawElementsInstanced (GLenum منوال, GLsizei گنتی, GLenum type, ثابت خالی *indices, GLsizei instancecount);
GL_APICALL GLsync GL_APIENTRY glFenceSync (GLenum condition, GLbitfield flags);
GL_APICALL GLboolean GL_APIENTRY glIsSync (GLsync sync);
GL_APICALL خالی GL_APIENTRY glDeleteSync (GLsync sync);
GL_APICALL GLenum GL_APIENTRY glClientWaitSync (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_APICALL خالی GL_APIENTRY glWaitSync (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_APICALL خالی GL_APIENTRY glGetInteger64v (GLenum pname, GLint64 *ڈیٹا);
GL_APICALL خالی GL_APIENTRY glGetSynciv (GLsync sync, GLenum pname, GLsizei گنتی, GLsizei *لمبائی, GLint *اقدار);
GL_APICALL خالی GL_APIENTRY glGetInteger64i_v (GLenum ہدف, GLuint اشاریہ, GLint64 *ڈیٹا);
GL_APICALL خالی GL_APIENTRY gl_Get_بفر_Parameteri64v (GLenum ہدف, GLenum pname, GLint64 *params);
GL_APICALL خالی GL_APIENTRY glGenSamplers (GLsizei گنتی, GLuint *samplers);
GL_APICALL خالی GL_APIENTRY glDeleteSamplers (GLsizei گنتی, ثابت GLuint *samplers);
GL_APICALL GLboolean GL_APIENTRY glIsSampler (GLuint sampler);
GL_APICALL خالی GL_APIENTRY glBindSampler (GLuint unit, GLuint sampler);
GL_APICALL خالی GL_APIENTRY glSamplerParameteri (GLuint sampler, GLenum pname, GLint param);
GL_APICALL خالی GL_APIENTRY glSamplerParameteriv (GLuint sampler, GLenum pname, ثابت GLint *param);
GL_APICALL خالی GL_APIENTRY glSamplerParameterf (GLuint sampler, GLenum pname, GLfloat param);
GL_APICALL خالی GL_APIENTRY glSamplerParameterfv (GLuint sampler, GLenum pname, ثابت GLfloat *param);
GL_APICALL خالی GL_APIENTRY glGetSamplerParameteriv (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL خالی GL_APIENTRY glGetSamplerParameterfv (GLuint sampler, GLenum pname, GLfloat *params);
GL_APICALL خالی GL_APIENTRY gl_راس_Attrib_مقسوم_علیہ (GLuint اشاریہ, GLuint مقسوم_علیہ);
GL_APICALL خالی GL_APIENTRY glBindTransformFeedback (GLenum ہدف, GLuint id);
GL_APICALL خالی GL_APIENTRY glDeleteTransformFeedbacks (GLsizei n, ثابت GLuint *ids);
GL_APICALL خالی GL_APIENTRY glGenTransformFeedbacks (GLsizei n, GLuint *ids);
GL_APICALL GLboolean GL_APIENTRY glIsTransformFeedback (GLuint id);
GL_APICALL خالی GL_APIENTRY glPauseTransformFeedback (خالی);
GL_APICALL خالی GL_APIENTRY glResumeTransformFeedback (خالی);
GL_APICALL خالی GL_APIENTRY gl_Get_پروگرام_ثنائی (GLuint پروگرام, GLsizei buf_سائز, GLsizei *لمبائی, GLenum *ثنائی_Format, خالی *ثنائی);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_ثنائی (GLuint پروگرام, GLenum ثنائی_Format, ثابت خالی *ثنائی, GLsizei لمبائی);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Parameteri (GLuint پروگرام, GLenum pname, GLint قدر);
GL_APICALL خالی GL_APIENTRY glInvalidateFramebuffer (GLenum ہدف, GLsizei عدد_Attachments, ثابت GLenum *attachments);
GL_APICALL خالی GL_APIENTRY glInvalidateSubFramebuffer (GLenum ہدف, GLsizei عدد_Attachments, ثابت GLenum *attachments, GLint x, GLint y, GLsizei چوڑائی, GLsizei اونچائی);
GL_APICALL خالی GL_APIENTRY glTexStorage2D (GLenum ہدف, GLsizei سطحیں, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی);
GL_APICALL خالی GL_APIENTRY glTexStorage3D (GLenum ہدف, GLsizei سطحیں, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی, GLsizei گہرائی_2);
GL_APICALL خالی GL_APIENTRY glGetInternalformativ (GLenum ہدف, GLenum internalformat, GLenum pname, GLsizei گنتی, GLint *params);
#اگر_ختم
#اگر_ختم /* GL_ES_VERSION_3_0 */

#اگر_غیر_تعریف_شدہ GL_ES_نسخہ_3_1
#تعریف_کرو GL_ES_نسخہ_3_1 1
#تعریف_کرو GL_COMPUTE_SHADER                 0x91B9
#تعریف_کرو GL_MAX_COMPUTE_یکساں_بلاکیں     0x91BB
#تعریف_کرو GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS 0x91BC
#تعریف_کرو GL_MAX_COMPUTE_IMAGE_UNIFORMS     0x91BD
#تعریف_کرو GL_MAX_COMPUTE_SHARED_حافظہ_سائز 0x8262
#تعریف_کرو GL_MAX_COMPUTE_یکساں_COMPONENTS 0x8263
#تعریف_کرو GL_MAX_COMPUTE_ATOMIC_شمار_BUFFERS 0x8264
#تعریف_کرو GL_MAX_COMPUTE_ATOMIC_COUNTERS    0x8265
#تعریف_کرو GL_MAX_COMBINED_COMPUTE_یکساں_COMPONENTS 0x8266
#تعریف_کرو GL_MAX_COMPUTE_WORK_گروہ_INVOCATIONS 0x90EB
#تعریف_کرو GL_MAX_COMPUTE_WORK_گروہ_گنتی   0x91BE
#تعریف_کرو GL_MAX_COMPUTE_WORK_گروہ_سائز    0x91BF
#تعریف_کرو GL_COMPUTE_WORK_گروہ_سائز        0x8267
#تعریف_کرو GL_DISPATCH_بالواسطہ_بفر       0x90EE
#تعریف_کرو GL_DISPATCH_بالواسطہ_بفر_BINDING 0x90EF
#تعریف_کرو GL_COMPUTE_SHADER_ثنائی_ہندسہ             0x00000020
#تعریف_کرو GL_DRAW_بالواسطہ_بفر           0x8F3F
#تعریف_کرو GL_DRAW_بالواسطہ_بفر_BINDING   0x8F43
#تعریف_کرو GL_MAX_یکساں_LOCATIONS          0x826E
#تعریف_کرو GL_FRAMEBUFFER_DEFAULT_چوڑائی      0x9310
#تعریف_کرو GL_FRAMEBUFFER_DEFAULT_اونچائی     0x9311
#تعریف_کرو GL_FRAMEBUFFER_DEFAULT_SAMPLES    0x9313
#تعریف_کرو GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS 0x9314
#تعریف_کرو GL_MAX_FRAMEBUFFER_چوڑائی          0x9315
#تعریف_کرو GL_MAX_FRAMEBUFFER_اونچائی         0x9316
#تعریف_کرو GL_MAX_FRAMEBUFFER_SAMPLES        0x9318
#تعریف_کرو GL_یکساں                        0x92E1
#تعریف_کرو GL_یکساں_بلاک                  0x92E2
#تعریف_کرو GL_پروگرام_داخلہ                  0x92E3
#تعریف_کرو GL_پروگرام_OUTPUT                 0x92E4
#تعریف_کرو GL_بفر_VARIABLE                0x92E5
#تعریف_کرو GL_SHADER_STORAGE_بلاک           0x92E6
#تعریف_کرو GL_ATOMIC_شمار_بفر          0x92C0
#تعریف_کرو GL_TRANSFORM_FEEDBACK_VARYING     0x92F4
#تعریف_کرو GL_فعال_RESOURCES               0x92F5
#تعریف_کرو GL_MAX_NAME_لمبائی                0x92F6
#تعریف_کرو GL_MAX_عدد_فعال_VARIABLES       0x92F7
#تعریف_کرو GL_NAME_لمبائی                    0x92F9
#تعریف_کرو GL_TYPE                           0x92FA
#تعریف_کرو GL_ARRAY_سائز                     0x92FB
#تعریف_کرو GL_انحراف                         0x92FC
#تعریف_کرو GL_بلاک_اشاریہ                    0x92FD
#تعریف_کرو GL_ARRAY_STRIDE                   0x92FE
#تعریف_کرو GL_میٹرکس_STRIDE                  0x92FF
#تعریف_کرو GL_IS_صف_MAJOR                   0x9300
#تعریف_کرو GL_ATOMIC_شمار_بفر_اشاریہ    0x9301
#تعریف_کرو GL_بفر_BINDING                 0x9302
#تعریف_کرو GL_بفر_ڈیٹا_سائز               0x9303
#تعریف_کرو GL_عدد_فعال_VARIABLES           0x9304
#تعریف_کرو GL_فعال_VARIABLES               0x9305
#تعریف_کرو GL_REFERENCED_BY_راس_SHADER    0x9306
#تعریف_کرو GL_REFERENCED_BY_FRAGMENT_SHADER  0x930A
#تعریف_کرو GL_REFERENCED_BY_COMPUTE_SHADER   0x930B
#تعریف_کرو GL_چوٹی_LEVEL_ARRAY_سائز           0x930C
#تعریف_کرو GL_چوٹی_LEVEL_ARRAY_STRIDE         0x930D
#تعریف_کرو GL_LOCATION                       0x930E
#تعریف_کرو GL_راس_SHADER_ثنائی_ہندسہ              0x00000001
#تعریف_کرو GL_FRAGMENT_SHADER_ثنائی_ہندسہ            0x00000002
#تعریف_کرو GL_ALL_SHADER_بٹ                0xFFFFFFFF
#تعریف_کرو GL_پروگرام_SEPARABLE              0x8258
#تعریف_کرو GL_فعال_پروگرام                 0x8259
#تعریف_کرو GL_پروگرام_PIPELINE_BINDING       0x825A
#تعریف_کرو GL_ATOMIC_شمار_بفر_BINDING  0x92C1
#تعریف_کرو GL_ATOMIC_شمار_بفر_آغاز    0x92C2
#تعریف_کرو GL_ATOMIC_شمار_بفر_سائز     0x92C3
#تعریف_کرو GL_MAX_راس_ATOMIC_شمار_BUFFERS 0x92CC
#تعریف_کرو GL_MAX_FRAGMENT_ATOMIC_شمار_BUFFERS 0x92D0
#تعریف_کرو GL_MAX_COMBINED_ATOMIC_شمار_BUFFERS 0x92D1
#تعریف_کرو GL_MAX_راس_ATOMIC_COUNTERS     0x92D2
#تعریف_کرو GL_MAX_FRAGMENT_ATOMIC_COUNTERS   0x92D6
#تعریف_کرو GL_MAX_COMBINED_ATOMIC_COUNTERS   0x92D7
#تعریف_کرو GL_MAX_ATOMIC_شمار_بفر_سائز 0x92D8
#تعریف_کرو GL_MAX_ATOMIC_شمار_بفر_BINDINGS 0x92DC
#تعریف_کرو GL_فعال_ATOMIC_شمار_BUFFERS  0x92D9
#تعریف_کرو GL_UNSIGNED_INT_ATOMIC_شمار    0x92DB
#تعریف_کرو GL_MAX_IMAGE_UNITS                0x8F38
#تعریف_کرو GL_MAX_راس_IMAGE_UNIFORMS      0x90CA
#تعریف_کرو GL_MAX_FRAGMENT_IMAGE_UNIFORMS    0x90CE
#تعریف_کرو GL_MAX_COMBINED_IMAGE_UNIFORMS    0x90CF
#تعریف_کرو GL_IMAGE_BINDING_NAME             0x8F3A
#تعریف_کرو GL_IMAGE_BINDING_LEVEL            0x8F3B
#تعریف_کرو GL_IMAGE_BINDING_LAYERED          0x8F3C
#تعریف_کرو GL_IMAGE_BINDING_LAYER            0x8F3D
#تعریف_کرو GL_IMAGE_BINDING_ACCESS           0x8F3E
#تعریف_کرو GL_IMAGE_BINDING_FORMAT           0x906E
#تعریف_کرو GL_راس_ATTRIB_ARRAY_BARRIER_ثنائی_ہندسہ 0x00000001
#تعریف_کرو GL_ELEMENT_ARRAY_BARRIER_ثنائی_ہندسہ      0x00000002
#تعریف_کرو GL_یکساں_BARRIER_ثنائی_ہندسہ            0x00000004
#تعریف_کرو GL_TEXTURE_FETCH_BARRIER_ثنائی_ہندسہ      0x00000008
#تعریف_کرو GL_SHADER_IMAGE_ACCESS_BARRIER_ثنائی_ہندسہ 0x00000020
#تعریف_کرو GL_COMMAND_BARRIER_ثنائی_ہندسہ            0x00000040
#تعریف_کرو GL_PIXEL_بفر_BARRIER_ثنائی_ہندسہ       0x00000080
#تعریف_کرو GL_TEXTURE_UPDATE_BARRIER_ثنائی_ہندسہ     0x00000100
#تعریف_کرو GL_بفر_UPDATE_BARRIER_ثنائی_ہندسہ      0x00000200
#تعریف_کرو GL_FRAMEBUFFER_BARRIER_ثنائی_ہندسہ        0x00000400
#تعریف_کرو GL_TRANSFORM_FEEDBACK_BARRIER_ثنائی_ہندسہ 0x00000800
#تعریف_کرو GL_ATOMIC_شمار_BARRIER_ثنائی_ہندسہ     0x00001000
#تعریف_کرو GL_ALL_BARRIER_بٹ               0xFFFFFFFF
#تعریف_کرو GL_IMAGE_2D                       0x904D
#تعریف_کرو GL_IMAGE_3D                       0x904E
#تعریف_کرو GL_IMAGE_CUBE                     0x9050
#تعریف_کرو GL_IMAGE_2D_ARRAY                 0x9053
#تعریف_کرو GL_INT_IMAGE_2D                   0x9058
#تعریف_کرو GL_INT_IMAGE_3D                   0x9059
#تعریف_کرو GL_INT_IMAGE_CUBE                 0x905B
#تعریف_کرو GL_INT_IMAGE_2D_ARRAY             0x905E
#تعریف_کرو GL_UNSIGNED_INT_IMAGE_2D          0x9063
#تعریف_کرو GL_UNSIGNED_INT_IMAGE_3D          0x9064
#تعریف_کرو GL_UNSIGNED_INT_IMAGE_CUBE        0x9066
#تعریف_کرو GL_UNSIGNED_INT_IMAGE_2D_ARRAY    0x9069
#تعریف_کرو GL_IMAGE_FORMAT_COMPATIBILITY_TYPE 0x90C7
#تعریف_کرو GL_IMAGE_FORMAT_COMPATIBILITY_BY_سائز 0x90C8
#تعریف_کرو GL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS 0x90C9
#تعریف_کرو GL_READ_ONLY                      0x88B8
#تعریف_کرو GL_WRITE_ONLY                     0x88B9
#تعریف_کرو GL_READ_WRITE                     0x88BA
#تعریف_کرو GL_SHADER_STORAGE_بفر          0x90D2
#تعریف_کرو GL_SHADER_STORAGE_بفر_BINDING  0x90D3
#تعریف_کرو GL_SHADER_STORAGE_بفر_آغاز    0x90D4
#تعریف_کرو GL_SHADER_STORAGE_بفر_سائز     0x90D5
#تعریف_کرو GL_MAX_راس_SHADER_STORAGE_بلاکیں 0x90D6
#تعریف_کرو GL_MAX_FRAGMENT_SHADER_STORAGE_بلاکیں 0x90DA
#تعریف_کرو GL_MAX_COMPUTE_SHADER_STORAGE_بلاکیں 0x90DB
#تعریف_کرو GL_MAX_COMBINED_SHADER_STORAGE_بلاکیں 0x90DC
#تعریف_کرو GL_MAX_SHADER_STORAGE_بفر_BINDINGS 0x90DD
#تعریف_کرو GL_MAX_SHADER_STORAGE_بلاک_سائز  0x90DE
#تعریف_کرو GL_SHADER_STORAGE_بفر_انحراف_ALIGNMENT 0x90DF
#تعریف_کرو GL_SHADER_STORAGE_BARRIER_ثنائی_ہندسہ     0x00002000
#تعریف_کرو GL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES 0x8F39
#تعریف_کرو GL_گہرائی_STENCIL_TEXTURE_منوال     0x90EA
#تعریف_کرو GL_STENCIL_اشاریہ                  0x1901
#تعریف_کرو GL_MIN_پروگرام_TEXTURE_GATHER_انحراف 0x8E5E
#تعریف_کرو GL_MAX_پروگرام_TEXTURE_GATHER_انحراف 0x8E5F
#تعریف_کرو GL_SAMPLE_POSITION                0x8E50
#تعریف_کرو GL_SAMPLE_نقاب                    0x8E51
#تعریف_کرو GL_SAMPLE_نقاب_قدر              0x8E52
#تعریف_کرو GL_TEXTURE_2D_MULTISAMPLE         0x9100
#تعریف_کرو GL_MAX_SAMPLE_نقاب_الفاظ          0x8E59
#تعریف_کرو GL_MAX_COLOR_TEXTURE_SAMPLES      0x910E
#تعریف_کرو GL_MAX_گہرائی_TEXTURE_SAMPLES      0x910F
#تعریف_کرو GL_MAX_INTEGER_SAMPLES            0x9110
#تعریف_کرو GL_TEXTURE_BINDING_2D_MULTISAMPLE 0x9104
#تعریف_کرو GL_TEXTURE_SAMPLES                0x9106
#تعریف_کرو GL_TEXTURE_FIXED_SAMPLE_LOCATIONS 0x9107
#تعریف_کرو GL_TEXTURE_چوڑائی                  0x1000
#تعریف_کرو GL_TEXTURE_اونچائی                 0x1001
#تعریف_کرو GL_TEXTURE_گہرائی                  0x8071
#تعریف_کرو GL_TEXTURE_اندرونی_FORMAT        0x1003
#تعریف_کرو GL_TEXTURE_RED_سائز               0x805C
#تعریف_کرو GL_TEXTURE_GREEN_سائز             0x805D
#تعریف_کرو GL_TEXTURE_BLUE_سائز              0x805E
#تعریف_کرو GL_TEXTURE_ALPHA_سائز             0x805F
#تعریف_کرو GL_TEXTURE_گہرائی_سائز             0x884A
#تعریف_کرو GL_TEXTURE_STENCIL_سائز           0x88F1
#تعریف_کرو GL_TEXTURE_SHARED_سائز            0x8C3F
#تعریف_کرو GL_TEXTURE_RED_TYPE               0x8C10
#تعریف_کرو GL_TEXTURE_GREEN_TYPE             0x8C11
#تعریف_کرو GL_TEXTURE_BLUE_TYPE              0x8C12
#تعریف_کرو GL_TEXTURE_ALPHA_TYPE             0x8C13
#تعریف_کرو GL_TEXTURE_گہرائی_TYPE             0x8C16
#تعریف_کرو GL_TEXTURE_COMPRESSED             0x86A1
#تعریف_کرو GL_SAMPLER_2D_MULTISAMPLE         0x9108
#تعریف_کرو GL_INT_SAMPLER_2D_MULTISAMPLE     0x9109
#تعریف_کرو GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE 0x910A
#تعریف_کرو GL_راس_ATTRIB_BINDING          0x82D4
#تعریف_کرو GL_راس_ATTRIB_RELATIVE_انحراف  0x82D5
#تعریف_کرو GL_راس_BINDING_مقسوم_علیہ         0x82D6
#تعریف_کرو GL_راس_BINDING_انحراف          0x82D7
#تعریف_کرو GL_راس_BINDING_STRIDE          0x82D8
#تعریف_کرو GL_راس_BINDING_بفر          0x8F4F
#تعریف_کرو GL_MAX_راس_ATTRIB_RELATIVE_انحراف 0x82D9
#تعریف_کرو GL_MAX_راس_ATTRIB_BINDINGS     0x82DA
#تعریف_کرو GL_MAX_راس_ATTRIB_STRIDE       0x82E5
قسمتعریف خالی (GL_APIENTRYP PFNGLDISPATCHCOMPUTEPROC) (GLuint عدد_groups_x, GLuint عدد_groups_y, GLuint عدد_groups_z);
قسمتعریف خالی (GL_APIENTRYP PFNGLDISPATCHCOMPUTEINDIRECTPROC) (GLintptr بالواسطہ);
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWARRAYSINDIRECTPROC) (GLenum منوال, ثابت خالی *بالواسطہ);
قسمتعریف خالی (GL_APIENTRYP PFNGLDRAWELEMENTSINDIRECTPROC) (GLenum منوال, GLenum type, ثابت خالی *بالواسطہ);
قسمتعریف خالی (GL_APIENTRYP PFNGLFRAMEBUFFERPARAMETERIPROC) (GLenum ہدف, GLenum pname, GLint param);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETFRAMEBUFFERPARAMETERIVPROC) (GLenum ہدف, GLenum pname, GLint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETPROGRAMINTERFACEIVPROC) (GLuint پروگرام, GLenum پروگرام_Interface, GLenum pname, GLint *params);
قسمتعریف GLuint (GL_APIENTRYP PFNGLGETPROGRAMRESOURCEINDEXPROC) (GLuint پروگرام, GLenum پروگرام_Interface, ثابت GLchar *name);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETPROGRAMRESOURCENAMEPROC) (GLuint پروگرام, GLenum پروگرام_Interface, GLuint اشاریہ, GLsizei buf_سائز, GLsizei *لمبائی, GLchar *name);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETPROGRAMRESOURCEIVPROC) (GLuint پروگرام, GLenum پروگرام_Interface, GLuint اشاریہ, GLsizei prop_گنتی, ثابت GLenum *props, GLsizei گنتی, GLsizei *لمبائی, GLint *params);
قسمتعریف GLint (GL_APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONPROC) (GLuint پروگرام, GLenum پروگرام_Interface, ثابت GLchar *name);
قسمتعریف خالی (GL_APIENTRYP PFNGLUSEPROGRAMSTAGESPROC) (GLuint pipeline, GLbitfield stages, GLuint پروگرام);
قسمتعریف خالی (GL_APIENTRYP PFNGLACTIVESHADERPROGRAMPROC) (GLuint pipeline, GLuint پروگرام);
قسمتعریف GLuint (GL_APIENTRYP PFNGLCREATESHADERPROGRAMVPROC) (GLenum type, GLsizei گنتی, ثابت GLchar *ثابت*لڑیاں);
قسمتعریف خالی (GL_APIENTRYP PFNGLBINDPROGRAMPIPELINEPROC) (GLuint pipeline);
قسمتعریف خالی (GL_APIENTRYP PFNGLDELETEPROGRAMPIPELINESPROC) (GLsizei n, ثابت GLuint *pipelines);
قسمتعریف خالی (GL_APIENTRYP PFNGLGENPROGRAMPIPELINESPROC) (GLsizei n, GLuint *pipelines);
قسمتعریف GLboolean (GL_APIENTRYP PFNGLISPROGRAMPIPELINEPROC) (GLuint pipeline);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETPROGRAMPIPELINEIVPROC) (GLuint pipeline, GLenum pname, GLint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM1IPROC) (GLuint پروگرام, GLint location, GLint v0);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM2IPROC) (GLuint پروگرام, GLint location, GLint v0, GLint v1);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM3IPROC) (GLuint پروگرام, GLint location, GLint v0, GLint v1, GLint v2);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM4IPROC) (GLuint پروگرام, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UIPROC) (GLuint پروگرام, GLint location, GLuint v0);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UIPROC) (GLuint پروگرام, GLint location, GLuint v0, GLuint v1);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UIPROC) (GLuint پروگرام, GLint location, GLuint v0, GLuint v1, GLuint v2);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UIPROC) (GLuint پروگرام, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM1FPROC) (GLuint پروگرام, GLint location, GLfloat v0);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM2FPROC) (GLuint پروگرام, GLint location, GLfloat v0, GLfloat v1);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM3FPROC) (GLuint پروگرام, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM4FPROC) (GLuint پروگرام, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM1IVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM2IVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM3IVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM4IVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UIVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UIVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UIVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UIVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM1FVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM2FVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM3FVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORM4FVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2FVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3FVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4FVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC) (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
قسمتعریف خالی (GL_APIENTRYP PFNGLVALIDATEPROGRAMPIPELINEPROC) (GLuint pipeline);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETPROGRAMPIPELINEINFOLOGPROC) (GLuint pipeline, GLsizei buf_سائز, GLsizei *لمبائی, GLchar *infoLog);
قسمتعریف خالی (GL_APIENTRYP PFNGLBINDIMAGETEXTUREPROC) (GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETBOOLEANI_VPROC) (GLenum ہدف, GLuint اشاریہ, GLboolean *ڈیٹا);
قسمتعریف خالی (GL_APIENTRYP PFNGLMEMORYBARRIERPROC) (GLbitfield barriers);
قسمتعریف خالی (GL_APIENTRYP PFNGLMEMORYBARRIERBYREGIONPROC) (GLbitfield barriers);
قسمتعریف خالی (GL_APIENTRYP PFNGLTEXSTORAGE2DMULTISAMPLEPROC) (GLenum ہدف, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی, GLboolean fixedsamplelocations);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETMULTISAMPLEFVPROC) (GLenum pname, GLuint اشاریہ, GLfloat *val);
قسمتعریف خالی (GL_APIENTRYP PFNGLSAMPLEMASKIPROC) (GLuint نقاب_نمبر, GLbitfield نقاب);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETTEXLEVELPARAMETERIVPROC) (GLenum ہدف, GLint level, GLenum pname, GLint *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLGETTEXLEVELPARAMETERFVPROC) (GLenum ہدف, GLint level, GLenum pname, GLfloat *params);
قسمتعریف خالی (GL_APIENTRYP PFNGLBINDVERTEXBUFFERPROC) (GLuint bindingindex, GLuint بفر_2, GLintptr انحراف_2, GLsizei stride);
قسمتعریف خالی (GL_APIENTRYP PFNGLVERTEXATTRIBFORMATPROC) (GLuint attribindex, GLint سائز, GLenum type, GLboolean normalized, GLuint relativeoffset);
قسمتعریف خالی (GL_APIENTRYP PFNGLVERTEXATTRIBIFORMATPROC) (GLuint attribindex, GLint سائز, GLenum type, GLuint relativeoffset);
قسمتعریف خالی (GL_APIENTRYP PFNGLVERTEXATTRIBBINDINGPROC) (GLuint attribindex, GLuint bindingindex);
قسمتعریف خالی (GL_APIENTRYP PFNGLVERTEXBINDINGDIVISORPROC) (GLuint bindingindex, GLuint مقسوم_علیہ);
#اگر GL_GLES_PROTOTYPES
GL_APICALL خالی GL_APIENTRY glDispatchCompute (GLuint عدد_groups_x, GLuint عدد_groups_y, GLuint عدد_groups_z);
GL_APICALL خالی GL_APIENTRY gl_Dispatch_Compute_بالواسطہ (GLintptr بالواسطہ);
GL_APICALL خالی GL_APIENTRY gl_Draw_Arrays_بالواسطہ (GLenum منوال, ثابت خالی *بالواسطہ);
GL_APICALL خالی GL_APIENTRY gl_Draw_Elements_بالواسطہ (GLenum منوال, GLenum type, ثابت خالی *بالواسطہ);
GL_APICALL خالی GL_APIENTRY glFramebufferParameteri (GLenum ہدف, GLenum pname, GLint param);
GL_APICALL خالی GL_APIENTRY glGetFramebufferParameteriv (GLenum ہدف, GLenum pname, GLint *params);
GL_APICALL خالی GL_APIENTRY gl_Get_پروگرام_Interfaceiv (GLuint پروگرام, GLenum پروگرام_Interface, GLenum pname, GLint *params);
GL_APICALL GLuint GL_APIENTRY gl_Get_پروگرام_Resource_اشاریہ (GLuint پروگرام, GLenum پروگرام_Interface, ثابت GLchar *name);
GL_APICALL خالی GL_APIENTRY gl_Get_پروگرام_Resource_Name (GLuint پروگرام, GLenum پروگرام_Interface, GLuint اشاریہ, GLsizei buf_سائز, GLsizei *لمبائی, GLchar *name);
GL_APICALL خالی GL_APIENTRY gl_Get_پروگرام_Resourceiv (GLuint پروگرام, GLenum پروگرام_Interface, GLuint اشاریہ, GLsizei prop_گنتی, ثابت GLenum *props, GLsizei گنتی, GLsizei *لمبائی, GLint *params);
GL_APICALL GLint GL_APIENTRY gl_Get_پروگرام_Resource_Location (GLuint پروگرام, GLenum پروگرام_Interface, ثابت GLchar *name);
GL_APICALL خالی GL_APIENTRY gl_Use_پروگرام_Stages (GLuint pipeline, GLbitfield stages, GLuint پروگرام);
GL_APICALL خالی GL_APIENTRY gl_فعال_Shader_پروگرام (GLuint pipeline, GLuint پروگرام);
GL_APICALL GLuint GL_APIENTRY glCreateShaderProgramv (GLenum type, GLsizei گنتی, ثابت GLchar *ثابت*لڑیاں);
GL_APICALL خالی GL_APIENTRY gl_Bind_پروگرام_Pipeline (GLuint pipeline);
GL_APICALL خالی GL_APIENTRY gl_Delete_پروگرام_Pipelines (GLsizei n, ثابت GLuint *pipelines);
GL_APICALL خالی GL_APIENTRY gl_Gen_پروگرام_Pipelines (GLsizei n, GLuint *pipelines);
GL_APICALL GLboolean GL_APIENTRY gl_Is_پروگرام_Pipeline (GLuint pipeline);
GL_APICALL خالی GL_APIENTRY gl_Get_پروگرام_Pipelineiv (GLuint pipeline, GLenum pname, GLint *params);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform1i (GLuint پروگرام, GLint location, GLint v0);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform2i (GLuint پروگرام, GLint location, GLint v0, GLint v1);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform3i (GLuint پروگرام, GLint location, GLint v0, GLint v1, GLint v2);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform4i (GLuint پروگرام, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform1ui (GLuint پروگرام, GLint location, GLuint v0);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform2ui (GLuint پروگرام, GLint location, GLuint v0, GLuint v1);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform3ui (GLuint پروگرام, GLint location, GLuint v0, GLuint v1, GLuint v2);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform4ui (GLuint پروگرام, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform1f (GLuint پروگرام, GLint location, GLfloat v0);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform2f (GLuint پروگرام, GLint location, GLfloat v0, GLfloat v1);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform3f (GLuint پروگرام, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform4f (GLuint پروگرام, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform1iv (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform2iv (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform3iv (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform4iv (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLint *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform1uiv (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform2uiv (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform3uiv (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform4uiv (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLuint *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform1fv (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform2fv (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform3fv (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_Uniform4fv (GLuint پروگرام, GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_یکساں_Matrix2fv (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_یکساں_Matrix3fv (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_یکساں_Matrix4fv (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_یکساں_Matrix2x3fv (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_یکساں_Matrix3x2fv (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_یکساں_Matrix2x4fv (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_یکساں_Matrix4x2fv (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_یکساں_Matrix3x4fv (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_پروگرام_یکساں_Matrix4x3fv (GLuint پروگرام, GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL خالی GL_APIENTRY gl_Validate_پروگرام_Pipeline (GLuint pipeline);
GL_APICALL خالی GL_APIENTRY gl_Get_پروگرام_Pipeline_Info_Log (GLuint pipeline, GLsizei buf_سائز, GLsizei *لمبائی, GLchar *infoLog);
GL_APICALL خالی GL_APIENTRY glBindImageTexture (GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
GL_APICALL خالی GL_APIENTRY glGetBooleani_v (GLenum ہدف, GLuint اشاریہ, GLboolean *ڈیٹا);
GL_APICALL خالی GL_APIENTRY gl_حافظہ_Barrier (GLbitfield barriers);
GL_APICALL خالی GL_APIENTRY gl_حافظہ_Barrier_By_Region (GLbitfield barriers);
GL_APICALL خالی GL_APIENTRY glTexStorage2DMultisample (GLenum ہدف, GLsizei samples, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی, GLboolean fixedsamplelocations);
GL_APICALL خالی GL_APIENTRY glGetMultisamplefv (GLenum pname, GLuint اشاریہ, GLfloat *val);
GL_APICALL خالی GL_APIENTRY glSampleMaski (GLuint نقاب_نمبر, GLbitfield نقاب);
GL_APICALL خالی GL_APIENTRY glGetTexLevelParameteriv (GLenum ہدف, GLint level, GLenum pname, GLint *params);
GL_APICALL خالی GL_APIENTRY glGetTexLevelParameterfv (GLenum ہدف, GLint level, GLenum pname, GLfloat *params);
GL_APICALL خالی GL_APIENTRY gl_Bind_راس_بفر (GLuint bindingindex, GLuint بفر_2, GLintptr انحراف_2, GLsizei stride);
GL_APICALL خالی GL_APIENTRY gl_راس_Attrib_Format (GLuint attribindex, GLint سائز, GLenum type, GLboolean normalized, GLuint relativeoffset);
GL_APICALL خالی GL_APIENTRY gl_راس_Attrib_IFormat (GLuint attribindex, GLint سائز, GLenum type, GLuint relativeoffset);
GL_APICALL خالی GL_APIENTRY gl_راس_Attrib_Binding (GLuint attribindex, GLuint bindingindex);
GL_APICALL خالی GL_APIENTRY gl_راس_Binding_مقسوم_علیہ (GLuint bindingindex, GLuint مقسوم_علیہ);
#اگر_ختم
#اگر_ختم /* GL_ES_VERSION_3_1 */

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم
