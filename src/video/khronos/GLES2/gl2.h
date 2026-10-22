#جے_بنا_تعریف __gles2_gl2_h_
#تعریف_کرو __gles2_gl2_h_ 1

#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت

/*
** Copyright 2013-2026 The Khronos Group Inc.
** SPDX-License-Identifier: MIT
**
** This header is generated from the Khronos OpenGL / OpenGL ES XML
** API Registry. The current version of the Registry, generator scripts
** used to make the header, and the header can be found at
**   https://github.com/KhronosGroup/OpenGL-Registry
*/

#ضمن <GLES2/gl2platform.h>

#جے_بنا_تعریف GL_APIENTRYP
#تعریف_کرو GL_APIENTRYP GL_APIENTRY*
#جے_انت

#جے_بنا_تعریف GL_GLES_PROTOTYPES
#تعریف_کرو GL_GLES_PROTOTYPES 1
#جے_انت

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

#جے_بنا_تعریف GL_ES_نسخہ_2_0
#تعریف_کرو GL_ES_نسخہ_2_0 1
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
تعريفنوع بنانشانی صحيح GLenum;
تعريفنوع بنانشانی صحيح GLuint;
تعريفنوع حرف GLchar;
تعريفنوع khronos_float_t GLfloat;
تعريفنوع khronos_ssize_t GLsizeiptr;
تعريفنوع khronos_intptr_t GLintptr;
تعريفنوع بنانشانی صحيح GLbitfield;
تعريفنوع صحيح GLint;
تعريفنوع بنانشانی حرف GLboolean;
تعريفنوع صحيح GLsizei;
تعريفنوع khronos_uint8_t GLubyte;
#تعریف_کرو GL_ڈونگھائی_بفر_ثنائی_ہندسہ               0x00000100
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
#تعریف_کرو GL_FUNC_گھٹاؤ                  0x800A
#تعریف_کرو GL_FUNC_الٹ_گھٹاؤ          0x800B
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
#تعریف_کرو GL_بفر_ناپ                    0x8764
#تعریف_کرو GL_بفر_USAGE                   0x8765
#تعریف_کرو GL_CURRENT_راس_ATTRIB          0x8626
#تعریف_کرو GL_FRONT                          0x0404
#تعریف_کرو GL_پٹھ                           0x0405
#تعریف_کرو GL_FRONT_AND_پٹھ                 0x0408
#تعریف_کرو GL_TEXTURE_2D                     0x0DE1
#تعریف_کرو GL_CULL_FACE                      0x0B44
#تعریف_کرو GL_BLEND                          0x0BE2
#تعریف_کرو GL_DITHER                         0x0BD0
#تعریف_کرو GL_STENCIL_TEST                   0x0B90
#تعریف_کرو GL_ڈونگھائی_TEST                     0x0B71
#تعریف_کرو GL_SCISSOR_TEST                   0x0C11
#تعریف_کرو GL_POLYGON_وتھ_FILL            0x8037
#تعریف_کرو GL_SAMPLE_ALPHA_منزل_COVERAGE       0x809E
#تعریف_کرو GL_SAMPLE_COVERAGE                0x80A0
#تعریف_کرو GL_NO_ERROR                       0
#تعریف_کرو GL_INVALID_ENUM                   0x0500
#تعریف_کرو GL_INVALID_قدر                  0x0501
#تعریف_کرو GL_INVALID_OPERATION              0x0502
#تعریف_کرو GL_باہرلا_دا_حافظہ                  0x0505
#تعریف_کرو GL_CW                             0x0900
#تعریف_کرو GL_CCW                            0x0901
#تعریف_کرو GL_سطر_چوڑائی                     0x0B21
#تعریف_کرو GL_ALIASED_نقطہ_ناپ_RANGE       0x846D
#تعریف_کرو GL_ALIASED_سطر_چوڑائی_RANGE       0x846E
#تعریف_کرو GL_CULL_FACE_منوال                 0x0B45
#تعریف_کرو GL_FRONT_FACE                     0x0B46
#تعریف_کرو GL_ڈونگھائی_RANGE                    0x0B70
#تعریف_کرو GL_ڈونگھائی_WRITEMASK                0x0B72
#تعریف_کرو GL_ڈونگھائی_CLEAR_قدر              0x0B73
#تعریف_کرو GL_ڈونگھائی_FUNC                     0x0B74
#تعریف_کرو GL_STENCIL_CLEAR_قدر            0x0B91
#تعریف_کرو GL_STENCIL_FUNC                   0x0B92
#تعریف_کرو GL_STENCIL_FAIL                   0x0B94
#تعریف_کرو GL_STENCIL_PASS_ڈونگھائی_FAIL        0x0B95
#تعریف_کرو GL_STENCIL_PASS_ڈونگھائی_PASS        0x0B96
#تعریف_کرو GL_STENCIL_REF                    0x0B97
#تعریف_کرو GL_STENCIL_قدر_نقاب             0x0B93
#تعریف_کرو GL_STENCIL_WRITEMASK              0x0B98
#تعریف_کرو GL_STENCIL_پٹھ_FUNC              0x8800
#تعریف_کرو GL_STENCIL_پٹھ_FAIL              0x8801
#تعریف_کرو GL_STENCIL_پٹھ_PASS_ڈونگھائی_FAIL   0x8802
#تعریف_کرو GL_STENCIL_پٹھ_PASS_ڈونگھائی_PASS   0x8803
#تعریف_کرو GL_STENCIL_پٹھ_REF               0x8CA3
#تعریف_کرو GL_STENCIL_پٹھ_قدر_نقاب        0x8CA4
#تعریف_کرو GL_STENCIL_پٹھ_WRITEMASK         0x8CA5
#تعریف_کرو GL_VIEWPORT                       0x0BA2
#تعریف_کرو GL_SCISSOR_BOX                    0x0C10
#تعریف_کرو GL_COLOR_CLEAR_قدر              0x0C22
#تعریف_کرو GL_COLOR_WRITEMASK                0x0C23
#تعریف_کرو GL_UNPACK_ALIGNMENT               0x0CF5
#تعریف_کرو GL_PACK_ALIGNMENT                 0x0D05
#تعریف_کرو GL_MAX_TEXTURE_ناپ               0x0D33
#تعریف_کرو GL_MAX_VIEWPORT_DIMS              0x0D3A
#تعریف_کرو GL_SUBPIXEL_بٹ                  0x0D50
#تعریف_کرو GL_RED_بٹ                       0x0D52
#تعریف_کرو GL_GREEN_بٹ                     0x0D53
#تعریف_کرو GL_BLUE_بٹ                      0x0D54
#تعریف_کرو GL_ALPHA_بٹ                     0x0D55
#تعریف_کرو GL_ڈونگھائی_بٹ                     0x0D56
#تعریف_کرو GL_STENCIL_بٹ                   0x0D57
#تعریف_کرو GL_POLYGON_وتھ_UNITS           0x2A00
#تعریف_کرو GL_POLYGON_وتھ_ضارب          0x8038
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
#تعریف_کرو GL_ڈونگھائی_COMPONENT                0x1902
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
#تعریف_کرو GL_MAX_راس_اکسار_VECTORS     0x8DFB
#تعریف_کرو GL_MAX_VARYING_VECTORS            0x8DFC
#تعریف_کرو GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 0x8B4D
#تعریف_کرو GL_MAX_راس_TEXTURE_IMAGE_UNITS 0x8B4C
#تعریف_کرو GL_MAX_TEXTURE_IMAGE_UNITS        0x8872
#تعریف_کرو GL_MAX_FRAGMENT_اکسار_VECTORS   0x8DFD
#تعریف_کرو GL_SHADER_TYPE                    0x8B4F
#تعریف_کرو GL_DELETE_حالت                  0x8B80
#تعریف_کرو GL_LINK_حالت                    0x8B82
#تعریف_کرو GL_VALIDATE_حالت                0x8B83
#تعریف_کرو GL_ATTACHED_SHADERS               0x8B85
#تعریف_کرو GL_سرگرم_UNIFORMS                0x8B86
#تعریف_کرو GL_سرگرم_اکسار_MAX_لمائی      0x8B87
#تعریف_کرو GL_سرگرم_گن              0x8B89
#تعریف_کرو GL_سرگرم_ATTRIBUTE_MAX_لمائی    0x8B8A
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
#تعریف_کرو GL_سبھ_توں_نیڑے                        0x2600
#تعریف_کرو GL_خطی                         0x2601
#تعریف_کرو GL_سبھ_توں_نیڑے_MIPMAP_سبھ_توں_نیڑے         0x2700
#تعریف_کرو GL_خطی_MIPMAP_سبھ_توں_نیڑے          0x2701
#تعریف_کرو GL_سبھ_توں_نیڑے_MIPMAP_خطی          0x2702
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
#تعریف_کرو GL_MAX_CUBE_MAP_TEXTURE_ناپ      0x851C
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
#تعریف_کرو GL_سرگرم_TEXTURE                 0x84E0
#تعریف_کرو GL_REPEAT                         0x2901
#تعریف_کرو GL_CLAMP_منزل_کنارا                  0x812F
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
#تعریف_کرو GL_راس_ATTRIB_ARRAY_ناپ       0x8623
#تعریف_کرو GL_راس_ATTRIB_ARRAY_STRIDE     0x8624
#تعریف_کرو GL_راس_ATTRIB_ARRAY_TYPE       0x8625
#تعریف_کرو GL_راس_ATTRIB_ARRAY_NORMALIZED 0x886A
#تعریف_کرو GL_راس_ATTRIB_ARRAY_اشارہ_گر    0x8645
#تعریف_کرو GL_راس_ATTRIB_ARRAY_بفر_BINDING 0x889F
#تعریف_کرو GL_IMPLEMENTATION_COLOR_READ_TYPE 0x8B9A
#تعریف_کرو GL_IMPLEMENTATION_COLOR_READ_FORMAT 0x8B9B
#تعریف_کرو GL_COMPILE_حالت                 0x8B81
#تعریف_کرو GL_INFO_LOG_لمائی                0x8B84
#تعریف_کرو GL_SHADER_سروت_لمائی           0x8B88
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
#تعریف_کرو GL_ڈونگھائی_COMPONENT16              0x81A5
#تعریف_کرو GL_STENCIL_INDEX8                 0x8D48
#تعریف_کرو GL_RENDERBUFFER_چوڑائی             0x8D42
#تعریف_کرو GL_RENDERBUFFER_اچائی            0x8D43
#تعریف_کرو GL_RENDERBUFFER_اندرونی_FORMAT   0x8D44
#تعریف_کرو GL_RENDERBUFFER_RED_ناپ          0x8D50
#تعریف_کرو GL_RENDERBUFFER_GREEN_ناپ        0x8D51
#تعریف_کرو GL_RENDERBUFFER_BLUE_ناپ         0x8D52
#تعریف_کرو GL_RENDERBUFFER_ALPHA_ناپ        0x8D53
#تعریف_کرو GL_RENDERBUFFER_ڈونگھائی_ناپ        0x8D54
#تعریف_کرو GL_RENDERBUFFER_STENCIL_ناپ      0x8D55
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE 0x8CD0
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME 0x8CD1
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL 0x8CD2
#تعریف_کرو GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE 0x8CD3
#تعریف_کرو GL_COLOR_ATTACHMENT0              0x8CE0
#تعریف_کرو GL_ڈونگھائی_ATTACHMENT               0x8D00
#تعریف_کرو GL_STENCIL_ATTACHMENT             0x8D20
#تعریف_کرو GL_NONE                           0
#تعریف_کرو GL_FRAMEBUFFER_COMPLETE           0x8CD5
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT 0x8CD6
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 0x8CD7
#تعریف_کرو GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS 0x8CD9
#تعریف_کرو GL_FRAMEBUFFER_UNSUPPORTED        0x8CDD
#تعریف_کرو GL_FRAMEBUFFER_BINDING            0x8CA6
#تعریف_کرو GL_RENDERBUFFER_BINDING           0x8CA7
#تعریف_کرو GL_MAX_RENDERBUFFER_ناپ          0x84E8
#تعریف_کرو GL_INVALID_FRAMEBUFFER_OPERATION  0x0506
تعريفنوع فراغ (GL_APIENTRYP PFNGLACTIVETEXTUREPROC) (GLenum texture);
تعريفنوع فراغ (GL_APIENTRYP PFNGLATTACHSHADERPROC) (GLuint پروگرام, GLuint shader);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDATTRIBLOCATIONPROC) (GLuint پروگرام, GLuint اشاریہ, ثابت GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDBUFFERPROC) (GLenum نشانہ, GLuint بفر_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDFRAMEBUFFERPROC) (GLenum نشانہ, GLuint framebuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDRENDERBUFFERPROC) (GLenum نشانہ, GLuint renderbuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDTEXTUREPROC) (GLenum نشانہ, GLuint texture);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONPROC) (GLenum منوال);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEPROC) (GLenum منوال_RGB, GLenum منوال_Alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDFUNCPROC) (GLenum sfactor, GLenum dfactor);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEPROC) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBUFFERDATAPROC) (GLenum نشانہ, GLsizeiptr ناپ, ثابت فراغ *انکڑے, GLenum usage);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBUFFERSUBDATAPROC) (GLenum نشانہ, GLintptr وتھ_2, GLsizeiptr ناپ, ثابت فراغ *انکڑے);
تعريفنوع GLenum (GL_APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSPROC) (GLenum نشانہ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARPROC) (GLbitfield نقاب);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARDEPTHFPROC) (GLfloat d);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARSTENCILPROC) (GLint s);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOLORMASKPROC) (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOMPILESHADERPROC) (GLuint shader);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOMPRESSEDTEXIMAGE2DPROC) (GLenum نشانہ, GLint level, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی, GLint border, GLsizei image_ناپ, ثابت فراغ *انکڑے);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) (GLenum نشانہ, GLint level, GLint xoffset, GLint yoffset, GLsizei چوڑائی, GLsizei اچائی, GLenum format, GLsizei image_ناپ, ثابت فراغ *انکڑے);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYTEXIMAGE2DPROC) (GLenum نشانہ, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei چوڑائی, GLsizei اچائی, GLint border);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYTEXSUBIMAGE2DPROC) (GLenum نشانہ, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei چوڑائی, GLsizei اچائی);
تعريفنوع GLuint (GL_APIENTRYP PFNGLCREATEPROGRAMPROC) (فراغ);
تعريفنوع GLuint (GL_APIENTRYP PFNGLCREATESHADERPROC) (GLenum type);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCULLFACEPROC) (GLenum منوال);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEBUFFERSPROC) (GLsizei n, ثابت GLuint *buffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEFRAMEBUFFERSPROC) (GLsizei n, ثابت GLuint *framebuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEPROGRAMPROC) (GLuint پروگرام);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETERENDERBUFFERSPROC) (GLsizei n, ثابت GLuint *renderbuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETESHADERPROC) (GLuint shader);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETETEXTURESPROC) (GLsizei n, ثابت GLuint *textures);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHFUNCPROC) (GLenum func);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHMASKPROC) (GLboolean flag);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHRANGEFPROC) (GLfloat n, GLfloat f);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDETACHSHADERPROC) (GLuint پروگرام, GLuint shader);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISABLEPROC) (GLenum cap);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint اشاریہ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWARRAYSPROC) (GLenum منوال, GLint پہلا, GLsizei گنتی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSPROC) (GLenum منوال, GLsizei گنتی, GLenum type, ثابت فراغ *indices);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENABLEPROC) (GLenum cap);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint اشاریہ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFINISHPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFLUSHPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFERPROC) (GLenum نشانہ, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DPROC) (GLenum نشانہ, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRONTFACEPROC) (GLenum منوال);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENBUFFERSPROC) (GLsizei n, GLuint *buffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENERATEMIPMAPPROC) (GLenum نشانہ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENFRAMEBUFFERSPROC) (GLsizei n, GLuint *framebuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENRENDERBUFFERSPROC) (GLsizei n, GLuint *renderbuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENTEXTURESPROC) (GLsizei n, GLuint *textures);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETACTIVEATTRIBPROC) (GLuint پروگرام, GLuint اشاریہ, GLsizei buf_ناپ, GLsizei *لمائی, GLint *ناپ, GLenum *type, GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETACTIVEUNIFORMPROC) (GLuint پروگرام, GLuint اشاریہ, GLsizei buf_ناپ, GLsizei *لمائی, GLint *ناپ, GLenum *type, GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETATTACHEDSHADERSPROC) (GLuint پروگرام, GLsizei max_گنتی, GLsizei *گنتی, GLuint *shaders);
تعريفنوع GLint (GL_APIENTRYP PFNGLGETATTRIBLOCATIONPROC) (GLuint پروگرام, ثابت GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETBOOLEANVPROC) (GLenum pname, GLboolean *انکڑے);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETBUFFERPARAMETERIVPROC) (GLenum نشانہ, GLenum pname, GLint *params);
تعريفنوع GLenum (GL_APIENTRYP PFNGLGETERRORPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFLOATVPROC) (GLenum pname, GLfloat *انکڑے);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) (GLenum نشانہ, GLenum attachment, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTEGERVPROC) (GLenum pname, GLint *انکڑے);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMIVPROC) (GLuint پروگرام, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMINFOLOGPROC) (GLuint پروگرام, GLsizei buf_ناپ, GLsizei *لمائی, GLchar *infoLog);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVPROC) (GLenum نشانہ, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei buf_ناپ, GLsizei *لمائی, GLchar *infoLog);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSHADERPRECISIONFORMATPROC) (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSHADERSOURCEPROC) (GLuint shader, GLsizei buf_ناپ, GLsizei *لمائی, GLchar *سروت);
تعريفنوع ثابت GLubyte *(GL_APIENTRYP PFNGLGETSTRINGPROC) (GLenum name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXPARAMETERFVPROC) (GLenum نشانہ, GLenum pname, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXPARAMETERIVPROC) (GLenum نشانہ, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETUNIFORMFVPROC) (GLuint پروگرام, GLint location, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETUNIFORMIVPROC) (GLuint پروگرام, GLint location, GLint *params);
تعريفنوع GLint (GL_APIENTRYP PFNGLGETUNIFORMLOCATIONPROC) (GLuint پروگرام, ثابت GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETVERTEXATTRIBFVPROC) (GLuint اشاریہ, GLenum pname, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETVERTEXATTRIBIVPROC) (GLuint اشاریہ, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETVERTEXATTRIBPOINTERVPROC) (GLuint اشاریہ, GLenum pname, فراغ **اشارہ_گر_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLHINTPROC) (GLenum نشانہ, GLenum منوال);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISBUFFERPROC) (GLuint بفر_2);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISENABLEDPROC) (GLenum cap);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISFRAMEBUFFERPROC) (GLuint framebuffer);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISPROGRAMPROC) (GLuint پروگرام);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISRENDERBUFFERPROC) (GLuint renderbuffer);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISSHADERPROC) (GLuint shader);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISTEXTUREPROC) (GLuint texture);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLINEWIDTHPROC) (GLfloat چوڑائی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLINKPROGRAMPROC) (GLuint پروگرام);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPIXELSTOREIPROC) (GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOLYGONOFFSETPROC) (GLfloat ضارب, GLfloat units);
تعريفنوع فراغ (GL_APIENTRYP PFNGLREADPIXELSPROC) (GLint x, GLint y, GLsizei چوڑائی, GLsizei اچائی, GLenum format, GLenum type, فراغ *pixels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRELEASESHADERCOMPILERPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEPROC) (GLenum نشانہ, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLECOVERAGEPROC) (GLfloat قدر, GLboolean invert);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSORPROC) (GLint x, GLint y, GLsizei چوڑائی, GLsizei اچائی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADERBINARYPROC) (GLsizei گنتی, ثابت GLuint *shaders, GLenum ثنائی_Format, ثابت فراغ *ثنائی, GLsizei لمائی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei گنتی, ثابت GLchar *ثابت*string, ثابت GLint *لمائی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILFUNCPROC) (GLenum func, GLint ref, GLuint نقاب);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILFUNCSEPARATEPROC) (GLenum face, GLenum func, GLint ref, GLuint نقاب);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILMASKPROC) (GLuint نقاب);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILMASKSEPARATEPROC) (GLenum face, GLuint نقاب);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILOPPROC) (GLenum fail, GLenum zfail, GLenum zpass);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILOPSEPARATEPROC) (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXIMAGE2DPROC) (GLenum نشانہ, GLint level, GLint internalformat, GLsizei چوڑائی, GLsizei اچائی, GLint border, GLenum format, GLenum type, ثابت فراغ *pixels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERFPROC) (GLenum نشانہ, GLenum pname, GLfloat param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERFVPROC) (GLenum نشانہ, GLenum pname, ثابت GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERIPROC) (GLenum نشانہ, GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERIVPROC) (GLenum نشانہ, GLenum pname, ثابت GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSUBIMAGE2DPROC) (GLenum نشانہ, GLint level, GLint xoffset, GLint yoffset, GLsizei چوڑائی, GLsizei اچائی, GLenum format, GLenum type, ثابت فراغ *pixels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1FPROC) (GLint location, GLfloat v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1FVPROC) (GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1IPROC) (GLint location, GLint v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1IVPROC) (GLint location, GLsizei گنتی, ثابت GLint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2FPROC) (GLint location, GLfloat v0, GLfloat v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2FVPROC) (GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2IPROC) (GLint location, GLint v0, GLint v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2IVPROC) (GLint location, GLsizei گنتی, ثابت GLint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3FVPROC) (GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3IPROC) (GLint location, GLint v0, GLint v1, GLint v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3IVPROC) (GLint location, GLsizei گنتی, ثابت GLint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4FVPROC) (GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4IPROC) (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4IVPROC) (GLint location, GLsizei گنتی, ثابت GLint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX2FVPROC) (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX3FVPROC) (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUSEPROGRAMPROC) (GLuint پروگرام);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVALIDATEPROGRAMPROC) (GLuint پروگرام);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB1FPROC) (GLuint اشاریہ, GLfloat x);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB1FVPROC) (GLuint اشاریہ, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB2FPROC) (GLuint اشاریہ, GLfloat x, GLfloat y);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB2FVPROC) (GLuint اشاریہ, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB3FPROC) (GLuint اشاریہ, GLfloat x, GLfloat y, GLfloat z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB3FVPROC) (GLuint اشاریہ, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB4FPROC) (GLuint اشاریہ, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB4FVPROC) (GLuint اشاریہ, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC) (GLuint اشاریہ, GLint ناپ, GLenum type, GLboolean normalized, GLsizei stride, ثابت فراغ *اشارہ_گر_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTPROC) (GLint x, GLint y, GLsizei چوڑائی, GLsizei اچائی);
#إذا GL_GLES_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_سرگرم_Texture (GLenum texture);
GL_APICALL فراغ GL_APIENTRY glAttachShader (GLuint پروگرام, GLuint shader);
GL_APICALL فراغ GL_APIENTRY glBindAttribLocation (GLuint پروگرام, GLuint اشاریہ, ثابت GLchar *name);
GL_APICALL فراغ GL_APIENTRY gl_Bind_بفر (GLenum نشانہ, GLuint بفر_2);
GL_APICALL فراغ GL_APIENTRY glBindFramebuffer (GLenum نشانہ, GLuint framebuffer);
GL_APICALL فراغ GL_APIENTRY glBindRenderbuffer (GLenum نشانہ, GLuint renderbuffer);
GL_APICALL فراغ GL_APIENTRY glBindTexture (GLenum نشانہ, GLuint texture);
GL_APICALL فراغ GL_APIENTRY glBlendColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_APICALL فراغ GL_APIENTRY glBlendEquation (GLenum منوال);
GL_APICALL فراغ GL_APIENTRY glBlendEquationSeparate (GLenum منوال_RGB, GLenum منوال_Alpha);
GL_APICALL فراغ GL_APIENTRY glBlendFunc (GLenum sfactor, GLenum dfactor);
GL_APICALL فراغ GL_APIENTRY glBlendFuncSeparate (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
GL_APICALL فراغ GL_APIENTRY gl_بفر_انکڑے (GLenum نشانہ, GLsizeiptr ناپ, ثابت فراغ *انکڑے, GLenum usage);
GL_APICALL فراغ GL_APIENTRY gl_بفر_Sub_انکڑے (GLenum نشانہ, GLintptr وتھ_2, GLsizeiptr ناپ, ثابت فراغ *انکڑے);
GL_APICALL GLenum GL_APIENTRY gl_Check_Framebuffer_حالت (GLenum نشانہ);
GL_APICALL فراغ GL_APIENTRY glClear (GLbitfield نقاب);
GL_APICALL فراغ GL_APIENTRY glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_APICALL فراغ GL_APIENTRY glClearDepthf (GLfloat d);
GL_APICALL فراغ GL_APIENTRY glClearStencil (GLint s);
GL_APICALL فراغ GL_APIENTRY gl_Color_نقاب (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
GL_APICALL فراغ GL_APIENTRY glCompileShader (GLuint shader);
GL_APICALL فراغ GL_APIENTRY glCompressedTexImage2D (GLenum نشانہ, GLint level, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی, GLint border, GLsizei image_ناپ, ثابت فراغ *انکڑے);
GL_APICALL فراغ GL_APIENTRY glCompressedTexSubImage2D (GLenum نشانہ, GLint level, GLint xoffset, GLint yoffset, GLsizei چوڑائی, GLsizei اچائی, GLenum format, GLsizei image_ناپ, ثابت فراغ *انکڑے);
GL_APICALL فراغ GL_APIENTRY glCopyTexImage2D (GLenum نشانہ, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei چوڑائی, GLsizei اچائی, GLint border);
GL_APICALL فراغ GL_APIENTRY glCopyTexSubImage2D (GLenum نشانہ, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei چوڑائی, GLsizei اچائی);
GL_APICALL GLuint GL_APIENTRY gl_Create_پروگرام (فراغ);
GL_APICALL GLuint GL_APIENTRY glCreateShader (GLenum type);
GL_APICALL فراغ GL_APIENTRY glCullFace (GLenum منوال);
GL_APICALL فراغ GL_APIENTRY glDeleteBuffers (GLsizei n, ثابت GLuint *buffers);
GL_APICALL فراغ GL_APIENTRY glDeleteFramebuffers (GLsizei n, ثابت GLuint *framebuffers);
GL_APICALL فراغ GL_APIENTRY gl_Delete_پروگرام (GLuint پروگرام);
GL_APICALL فراغ GL_APIENTRY glDeleteRenderbuffers (GLsizei n, ثابت GLuint *renderbuffers);
GL_APICALL فراغ GL_APIENTRY glDeleteShader (GLuint shader);
GL_APICALL فراغ GL_APIENTRY glDeleteTextures (GLsizei n, ثابت GLuint *textures);
GL_APICALL فراغ GL_APIENTRY gl_ڈونگھائی_Func (GLenum func);
GL_APICALL فراغ GL_APIENTRY gl_ڈونگھائی_نقاب (GLboolean flag);
GL_APICALL فراغ GL_APIENTRY gl_ڈونگھائی_Rangef (GLfloat n, GLfloat f);
GL_APICALL فراغ GL_APIENTRY glDetachShader (GLuint پروگرام, GLuint shader);
GL_APICALL فراغ GL_APIENTRY glDisable (GLenum cap);
GL_APICALL فراغ GL_APIENTRY gl_Disable_راس_Attrib_Array (GLuint اشاریہ);
GL_APICALL فراغ GL_APIENTRY glDrawArrays (GLenum منوال, GLint پہلا, GLsizei گنتی);
GL_APICALL فراغ GL_APIENTRY glDrawElements (GLenum منوال, GLsizei گنتی, GLenum type, ثابت فراغ *indices);
GL_APICALL فراغ GL_APIENTRY glEnable (GLenum cap);
GL_APICALL فراغ GL_APIENTRY gl_Enable_راس_Attrib_Array (GLuint اشاریہ);
GL_APICALL فراغ GL_APIENTRY gl_انت (فراغ);
GL_APICALL فراغ GL_APIENTRY glFlush (فراغ);
GL_APICALL فراغ GL_APIENTRY glFramebufferRenderbuffer (GLenum نشانہ, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
GL_APICALL فراغ GL_APIENTRY glFramebufferTexture2D (GLenum نشانہ, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GL_APICALL فراغ GL_APIENTRY glFrontFace (GLenum منوال);
GL_APICALL فراغ GL_APIENTRY glGenBuffers (GLsizei n, GLuint *buffers);
GL_APICALL فراغ GL_APIENTRY glGenerateMipmap (GLenum نشانہ);
GL_APICALL فراغ GL_APIENTRY glGenFramebuffers (GLsizei n, GLuint *framebuffers);
GL_APICALL فراغ GL_APIENTRY glGenRenderbuffers (GLsizei n, GLuint *renderbuffers);
GL_APICALL فراغ GL_APIENTRY glGenTextures (GLsizei n, GLuint *textures);
GL_APICALL فراغ GL_APIENTRY gl_Get_سرگرم_Attrib (GLuint پروگرام, GLuint اشاریہ, GLsizei buf_ناپ, GLsizei *لمائی, GLint *ناپ, GLenum *type, GLchar *name);
GL_APICALL فراغ GL_APIENTRY gl_Get_سرگرم_اکسار (GLuint پروگرام, GLuint اشاریہ, GLsizei buf_ناپ, GLsizei *لمائی, GLint *ناپ, GLenum *type, GLchar *name);
GL_APICALL فراغ GL_APIENTRY glGetAttachedShaders (GLuint پروگرام, GLsizei max_گنتی, GLsizei *گنتی, GLuint *shaders);
GL_APICALL GLint GL_APIENTRY glGetAttribLocation (GLuint پروگرام, ثابت GLchar *name);
GL_APICALL فراغ GL_APIENTRY glGetBooleanv (GLenum pname, GLboolean *انکڑے);
GL_APICALL فراغ GL_APIENTRY gl_Get_بفر_Parameteriv (GLenum نشانہ, GLenum pname, GLint *params);
GL_APICALL GLenum GL_APIENTRY glGetError (فراغ);
GL_APICALL فراغ GL_APIENTRY glGetFloatv (GLenum pname, GLfloat *انکڑے);
GL_APICALL فراغ GL_APIENTRY glGetFramebufferAttachmentParameteriv (GLenum نشانہ, GLenum attachment, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetIntegerv (GLenum pname, GLint *انکڑے);
GL_APICALL فراغ GL_APIENTRY glGetProgramiv (GLuint پروگرام, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY gl_Get_پروگرام_Info_Log (GLuint پروگرام, GLsizei buf_ناپ, GLsizei *لمائی, GLchar *infoLog);
GL_APICALL فراغ GL_APIENTRY glGetRenderbufferParameteriv (GLenum نشانہ, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetShaderiv (GLuint shader, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetShaderInfoLog (GLuint shader, GLsizei buf_ناپ, GLsizei *لمائی, GLchar *infoLog);
GL_APICALL فراغ GL_APIENTRY glGetShaderPrecisionFormat (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
GL_APICALL فراغ GL_APIENTRY gl_Get_Shader_سروت (GLuint shader, GLsizei buf_ناپ, GLsizei *لمائی, GLchar *سروت);
GL_APICALL ثابت GLubyte *GL_APIENTRY glGetString (GLenum name);
GL_APICALL فراغ GL_APIENTRY glGetTexParameterfv (GLenum نشانہ, GLenum pname, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY glGetTexParameteriv (GLenum نشانہ, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetUniformfv (GLuint پروگرام, GLint location, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY glGetUniformiv (GLuint پروگرام, GLint location, GLint *params);
GL_APICALL GLint GL_APIENTRY gl_Get_اکسار_Location (GLuint پروگرام, ثابت GLchar *name);
GL_APICALL فراغ GL_APIENTRY gl_Get_راس_Attribfv (GLuint اشاریہ, GLenum pname, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY gl_Get_راس_Attribiv (GLuint اشاریہ, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY gl_Get_راس_Attrib_Pointerv (GLuint اشاریہ, GLenum pname, فراغ **اشارہ_گر_2);
GL_APICALL فراغ GL_APIENTRY glHint (GLenum نشانہ, GLenum منوال);
GL_APICALL GLboolean GL_APIENTRY gl_Is_بفر (GLuint بفر_2);
GL_APICALL GLboolean GL_APIENTRY glIsEnabled (GLenum cap);
GL_APICALL GLboolean GL_APIENTRY glIsFramebuffer (GLuint framebuffer);
GL_APICALL GLboolean GL_APIENTRY gl_Is_پروگرام (GLuint پروگرام);
GL_APICALL GLboolean GL_APIENTRY glIsRenderbuffer (GLuint renderbuffer);
GL_APICALL GLboolean GL_APIENTRY glIsShader (GLuint shader);
GL_APICALL GLboolean GL_APIENTRY glIsTexture (GLuint texture);
GL_APICALL فراغ GL_APIENTRY gl_سطر_چوڑائی (GLfloat چوڑائی);
GL_APICALL فراغ GL_APIENTRY gl_Link_پروگرام (GLuint پروگرام);
GL_APICALL فراغ GL_APIENTRY glPixelStorei (GLenum pname, GLint param);
GL_APICALL فراغ GL_APIENTRY gl_Polygon_وتھ (GLfloat ضارب, GLfloat units);
GL_APICALL فراغ GL_APIENTRY glReadPixels (GLint x, GLint y, GLsizei چوڑائی, GLsizei اچائی, GLenum format, GLenum type, فراغ *pixels);
GL_APICALL فراغ GL_APIENTRY glReleaseShaderCompiler (فراغ);
GL_APICALL فراغ GL_APIENTRY glRenderbufferStorage (GLenum نشانہ, GLenum internalformat, GLsizei چوڑائی, GLsizei اچائی);
GL_APICALL فراغ GL_APIENTRY glSampleCoverage (GLfloat قدر, GLboolean invert);
GL_APICALL فراغ GL_APIENTRY glScissor (GLint x, GLint y, GLsizei چوڑائی, GLsizei اچائی);
GL_APICALL فراغ GL_APIENTRY gl_Shader_ثنائی (GLsizei گنتی, ثابت GLuint *shaders, GLenum ثنائی_Format, ثابت فراغ *ثنائی, GLsizei لمائی);
GL_APICALL فراغ GL_APIENTRY gl_Shader_سروت (GLuint shader, GLsizei گنتی, ثابت GLchar *ثابت*string, ثابت GLint *لمائی);
GL_APICALL فراغ GL_APIENTRY glStencilFunc (GLenum func, GLint ref, GLuint نقاب);
GL_APICALL فراغ GL_APIENTRY glStencilFuncSeparate (GLenum face, GLenum func, GLint ref, GLuint نقاب);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_نقاب (GLuint نقاب);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_نقاب_Separate (GLenum face, GLuint نقاب);
GL_APICALL فراغ GL_APIENTRY glStencilOp (GLenum fail, GLenum zfail, GLenum zpass);
GL_APICALL فراغ GL_APIENTRY glStencilOpSeparate (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
GL_APICALL فراغ GL_APIENTRY glTexImage2D (GLenum نشانہ, GLint level, GLint internalformat, GLsizei چوڑائی, GLsizei اچائی, GLint border, GLenum format, GLenum type, ثابت فراغ *pixels);
GL_APICALL فراغ GL_APIENTRY glTexParameterf (GLenum نشانہ, GLenum pname, GLfloat param);
GL_APICALL فراغ GL_APIENTRY glTexParameterfv (GLenum نشانہ, GLenum pname, ثابت GLfloat *params);
GL_APICALL فراغ GL_APIENTRY glTexParameteri (GLenum نشانہ, GLenum pname, GLint param);
GL_APICALL فراغ GL_APIENTRY glTexParameteriv (GLenum نشانہ, GLenum pname, ثابت GLint *params);
GL_APICALL فراغ GL_APIENTRY glTexSubImage2D (GLenum نشانہ, GLint level, GLint xoffset, GLint yoffset, GLsizei چوڑائی, GLsizei اچائی, GLenum format, GLenum type, ثابت فراغ *pixels);
GL_APICALL فراغ GL_APIENTRY glUniform1f (GLint location, GLfloat v0);
GL_APICALL فراغ GL_APIENTRY glUniform1fv (GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY glUniform1i (GLint location, GLint v0);
GL_APICALL فراغ GL_APIENTRY glUniform1iv (GLint location, GLsizei گنتی, ثابت GLint *قدر);
GL_APICALL فراغ GL_APIENTRY glUniform2f (GLint location, GLfloat v0, GLfloat v1);
GL_APICALL فراغ GL_APIENTRY glUniform2fv (GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY glUniform2i (GLint location, GLint v0, GLint v1);
GL_APICALL فراغ GL_APIENTRY glUniform2iv (GLint location, GLsizei گنتی, ثابت GLint *قدر);
GL_APICALL فراغ GL_APIENTRY glUniform3f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
GL_APICALL فراغ GL_APIENTRY glUniform3fv (GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY glUniform3i (GLint location, GLint v0, GLint v1, GLint v2);
GL_APICALL فراغ GL_APIENTRY glUniform3iv (GLint location, GLsizei گنتی, ثابت GLint *قدر);
GL_APICALL فراغ GL_APIENTRY glUniform4f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
GL_APICALL فراغ GL_APIENTRY glUniform4fv (GLint location, GLsizei گنتی, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY glUniform4i (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
GL_APICALL فراغ GL_APIENTRY glUniform4iv (GLint location, GLsizei گنتی, ثابت GLint *قدر);
GL_APICALL فراغ GL_APIENTRY gl_اکسار_Matrix2fv (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_اکسار_Matrix3fv (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_اکسار_Matrix4fv (GLint location, GLsizei گنتی, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_Use_پروگرام (GLuint پروگرام);
GL_APICALL فراغ GL_APIENTRY gl_Validate_پروگرام (GLuint پروگرام);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib1f (GLuint اشاریہ, GLfloat x);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib1fv (GLuint اشاریہ, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib2f (GLuint اشاریہ, GLfloat x, GLfloat y);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib2fv (GLuint اشاریہ, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib3f (GLuint اشاریہ, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib3fv (GLuint اشاریہ, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib4f (GLuint اشاریہ, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib4fv (GLuint اشاریہ, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib_اشارہ_گر (GLuint اشاریہ, GLint ناپ, GLenum type, GLboolean normalized, GLsizei stride, ثابت فراغ *اشارہ_گر_2);
GL_APICALL فراغ GL_APIENTRY glViewport (GLint x, GLint y, GLsizei چوڑائی, GLsizei اچائی);
#جے_انت
#جے_انت /* GL_ES_VERSION_2_0 */

#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت
