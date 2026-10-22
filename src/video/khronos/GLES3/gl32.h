#جيڪڏهن_وصف_نه_ٿيل __gles2_gl32_h_
#وصف_ڪريو __gles2_gl32_h_ 1

#جيڪڏهن_وصف_ٿيل __cplusplus
خارجي "C" {
#جيڪڏهن_پورو

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

#جيڪڏهن_وصف_نه_ٿيل GL_APIENTRYP
#وصف_ڪريو GL_APIENTRYP GL_APIENTRY*
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل GL_GLES_PROTOTYPES
#وصف_ڪريو GL_GLES_PROTOTYPES 1
#جيڪڏهن_پورو

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

#جيڪڏهن_وصف_نه_ٿيل GL_ES_نسخو_2_0
#وصف_ڪريو GL_ES_نسخو_2_0 1
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
تعريفنوع بنانشان صحيح GLenum;
تعريفنوع بنانشان صحيح GLuint;
تعريفنوع حرف GLchar;
تعريفنوع khronos_float_t GLfloat;
تعريفنوع khronos_ssize_t GLsizeiptr;
تعريفنوع khronos_intptr_t GLintptr;
تعريفنوع بنانشان صحيح GLbitfield;
تعريفنوع صحيح GLint;
تعريفنوع بنانشان حرف GLboolean;
تعريفنوع صحيح GLsizei;
تعريفنوع khronos_uint8_t GLubyte;
#وصف_ڪريو GL_اونهائي_بفر_ٻٽو_انگ               0x00000100
#وصف_ڪريو GL_STENCIL_بفر_ٻٽو_انگ             0x00000400
#وصف_ڪريو GL_COLOR_بفر_ٻٽو_انگ               0x00004000
#وصف_ڪريو GL_FALSE                          0
#وصف_ڪريو GL_TRUE                           1
#وصف_ڪريو GL_POINTS                         0x0000
#وصف_ڪريو GL_سٽون                          0x0001
#وصف_ڪريو GL_سٽ_LOOP                      0x0002
#وصف_ڪريو GL_سٽ_STRIP                     0x0003
#وصف_ڪريو GL_TRIANGLES                      0x0004
#وصف_ڪريو GL_TRIANGLE_STRIP                 0x0005
#وصف_ڪريو GL_TRIANGLE_FAN                   0x0006
#وصف_ڪريو GL_ZERO                           0
#وصف_ڪريو GL_ONE                            1
#وصف_ڪريو GL_SRC_COLOR                      0x0300
#وصف_ڪريو GL_ONE_MINUS_SRC_COLOR            0x0301
#وصف_ڪريو GL_SRC_ALPHA                      0x0302
#وصف_ڪريو GL_ONE_MINUS_SRC_ALPHA            0x0303
#وصف_ڪريو GL_DST_ALPHA                      0x0304
#وصف_ڪريو GL_ONE_MINUS_DST_ALPHA            0x0305
#وصف_ڪريو GL_DST_COLOR                      0x0306
#وصف_ڪريو GL_ONE_MINUS_DST_COLOR            0x0307
#وصف_ڪريو GL_SRC_ALPHA_SATURATE             0x0308
#وصف_ڪريو GL_FUNC_جوڙيو                       0x8006
#وصف_ڪريو GL_BLEND_EQUATION                 0x8009
#وصف_ڪريو GL_BLEND_EQUATION_RGB             0x8009
#وصف_ڪريو GL_BLEND_EQUATION_ALPHA           0x883D
#وصف_ڪريو GL_FUNC_ڪٽيو                  0x800A
#وصف_ڪريو GL_FUNC_ابتو_ڪٽيو          0x800B
#وصف_ڪريو GL_BLEND_DST_RGB                  0x80C8
#وصف_ڪريو GL_BLEND_SRC_RGB                  0x80C9
#وصف_ڪريو GL_BLEND_DST_ALPHA                0x80CA
#وصف_ڪريو GL_BLEND_SRC_ALPHA                0x80CB
#وصف_ڪريو GL_CONSTANT_COLOR                 0x8001
#وصف_ڪريو GL_ONE_MINUS_CONSTANT_COLOR       0x8002
#وصف_ڪريو GL_CONSTANT_ALPHA                 0x8003
#وصف_ڪريو GL_ONE_MINUS_CONSTANT_ALPHA       0x8004
#وصف_ڪريو GL_BLEND_COLOR                    0x8005
#وصف_ڪريو GL_ARRAY_بفر                   0x8892
#وصف_ڪريو GL_ELEMENT_ARRAY_بفر           0x8893
#وصف_ڪريو GL_ARRAY_بفر_BINDING           0x8894
#وصف_ڪريو GL_ELEMENT_ARRAY_بفر_BINDING   0x8895
#وصف_ڪريو GL_وهڪرو_DRAW                    0x88E0
#وصف_ڪريو GL_STATIC_DRAW                    0x88E4
#وصف_ڪريو GL_DYNAMIC_DRAW                   0x88E8
#وصف_ڪريو GL_بفر_سائيز                    0x8764
#وصف_ڪريو GL_بفر_USAGE                   0x8765
#وصف_ڪريو GL_CURRENT_راس_ATTRIB          0x8626
#وصف_ڪريو GL_FRONT                          0x0404
#وصف_ڪريو GL_پٺ                           0x0405
#وصف_ڪريو GL_FRONT_AND_پٺ                 0x0408
#وصف_ڪريو GL_TEXTURE_2D                     0x0DE1
#وصف_ڪريو GL_CULL_FACE                      0x0B44
#وصف_ڪريو GL_BLEND                          0x0BE2
#وصف_ڪريو GL_DITHER                         0x0BD0
#وصف_ڪريو GL_STENCIL_TEST                   0x0B90
#وصف_ڪريو GL_اونهائي_TEST                     0x0B71
#وصف_ڪريو GL_SCISSOR_TEST                   0x0C11
#وصف_ڪريو GL_POLYGON_وٿي_FILL            0x8037
#وصف_ڪريو GL_SAMPLE_ALPHA_منزل_COVERAGE       0x809E
#وصف_ڪريو GL_SAMPLE_COVERAGE                0x80A0
#وصف_ڪريو GL_NO_ERROR                       0
#وصف_ڪريو GL_INVALID_ENUM                   0x0500
#وصف_ڪريو GL_INVALID_قدر                  0x0501
#وصف_ڪريو GL_INVALID_OPERATION              0x0502
#وصف_ڪريو GL_ٻاهريون_جو_يادگيري                  0x0505
#وصف_ڪريو GL_CW                             0x0900
#وصف_ڪريو GL_CCW                            0x0901
#وصف_ڪريو GL_سٽ_ويڪر                     0x0B21
#وصف_ڪريو GL_ALIASED_نقطو_سائيز_RANGE       0x846D
#وصف_ڪريو GL_ALIASED_سٽ_ويڪر_RANGE       0x846E
#وصف_ڪريو GL_CULL_FACE_گهڻائي                 0x0B45
#وصف_ڪريو GL_FRONT_FACE                     0x0B46
#وصف_ڪريو GL_اونهائي_RANGE                    0x0B70
#وصف_ڪريو GL_اونهائي_WRITEMASK                0x0B72
#وصف_ڪريو GL_اونهائي_CLEAR_قدر              0x0B73
#وصف_ڪريو GL_اونهائي_FUNC                     0x0B74
#وصف_ڪريو GL_STENCIL_CLEAR_قدر            0x0B91
#وصف_ڪريو GL_STENCIL_FUNC                   0x0B92
#وصف_ڪريو GL_STENCIL_FAIL                   0x0B94
#وصف_ڪريو GL_STENCIL_PASS_اونهائي_FAIL        0x0B95
#وصف_ڪريو GL_STENCIL_PASS_اونهائي_PASS        0x0B96
#وصف_ڪريو GL_STENCIL_REF                    0x0B97
#وصف_ڪريو GL_STENCIL_قدر_نقاب             0x0B93
#وصف_ڪريو GL_STENCIL_WRITEMASK              0x0B98
#وصف_ڪريو GL_STENCIL_پٺ_FUNC              0x8800
#وصف_ڪريو GL_STENCIL_پٺ_FAIL              0x8801
#وصف_ڪريو GL_STENCIL_پٺ_PASS_اونهائي_FAIL   0x8802
#وصف_ڪريو GL_STENCIL_پٺ_PASS_اونهائي_PASS   0x8803
#وصف_ڪريو GL_STENCIL_پٺ_REF               0x8CA3
#وصف_ڪريو GL_STENCIL_پٺ_قدر_نقاب        0x8CA4
#وصف_ڪريو GL_STENCIL_پٺ_WRITEMASK         0x8CA5
#وصف_ڪريو GL_VIEWPORT                       0x0BA2
#وصف_ڪريو GL_SCISSOR_BOX                    0x0C10
#وصف_ڪريو GL_COLOR_CLEAR_قدر              0x0C22
#وصف_ڪريو GL_COLOR_WRITEMASK                0x0C23
#وصف_ڪريو GL_UNPACK_ALIGNMENT               0x0CF5
#وصف_ڪريو GL_PACK_ALIGNMENT                 0x0D05
#وصف_ڪريو GL_MAX_TEXTURE_سائيز               0x0D33
#وصف_ڪريو GL_MAX_VIEWPORT_DIMS              0x0D3A
#وصف_ڪريو GL_SUBPIXEL_بٽ                  0x0D50
#وصف_ڪريو GL_RED_بٽ                       0x0D52
#وصف_ڪريو GL_GREEN_بٽ                     0x0D53
#وصف_ڪريو GL_BLUE_بٽ                      0x0D54
#وصف_ڪريو GL_ALPHA_بٽ                     0x0D55
#وصف_ڪريو GL_اونهائي_بٽ                     0x0D56
#وصف_ڪريو GL_STENCIL_بٽ                   0x0D57
#وصف_ڪريو GL_POLYGON_وٿي_UNITS           0x2A00
#وصف_ڪريو GL_POLYGON_وٿي_ضرب_ڪندڙ          0x8038
#وصف_ڪريو GL_TEXTURE_BINDING_2D             0x8069
#وصف_ڪريو GL_SAMPLE_BUFFERS                 0x80A8
#وصف_ڪريو GL_SAMPLES                        0x80A9
#وصف_ڪريو GL_SAMPLE_COVERAGE_قدر          0x80AA
#وصف_ڪريو GL_SAMPLE_COVERAGE_INVERT         0x80AB
#وصف_ڪريو GL_انگ_COMPRESSED_TEXTURE_FORMATS 0x86A2
#وصف_ڪريو GL_COMPRESSED_TEXTURE_FORMATS     0x86A3
#وصف_ڪريو GL_DONT_CARE                      0x1100
#وصف_ڪريو GL_FASTEST                        0x1101
#وصف_ڪريو GL_NICEST                         0x1102
#وصف_ڪريو GL_GENERATE_MIPMAP_HINT           0x8192
#وصف_ڪريو GL_BYTE                           0x1400
#وصف_ڪريو GL_UNSIGNED_BYTE                  0x1401
#وصف_ڪريو GL_SHORT                          0x1402
#وصف_ڪريو GL_UNSIGNED_SHORT                 0x1403
#وصف_ڪريو GL_INT                            0x1404
#وصف_ڪريو GL_UNSIGNED_INT                   0x1405
#وصف_ڪريو GL_FLOAT                          0x1406
#وصف_ڪريو GL_FIXED                          0x140C
#وصف_ڪريو GL_اونهائي_COMPONENT                0x1902
#وصف_ڪريو GL_ALPHA                          0x1906
#وصف_ڪريو GL_RGB                            0x1907
#وصف_ڪريو GL_RGBA                           0x1908
#وصف_ڪريو GL_LUMINANCE                      0x1909
#وصف_ڪريو GL_LUMINANCE_ALPHA                0x190A
#وصف_ڪريو GL_UNSIGNED_SHORT_4_4_4_4         0x8033
#وصف_ڪريو GL_UNSIGNED_SHORT_5_5_5_1         0x8034
#وصف_ڪريو GL_UNSIGNED_SHORT_5_6_5           0x8363
#وصف_ڪريو GL_FRAGMENT_SHADER                0x8B30
#وصف_ڪريو GL_راس_SHADER                  0x8B31
#وصف_ڪريو GL_MAX_راس_ATTRIBS             0x8869
#وصف_ڪريو GL_MAX_راس_هڪجهڙو_VECTORS     0x8DFB
#وصف_ڪريو GL_MAX_VARYING_VECTORS            0x8DFC
#وصف_ڪريو GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 0x8B4D
#وصف_ڪريو GL_MAX_راس_TEXTURE_IMAGE_UNITS 0x8B4C
#وصف_ڪريو GL_MAX_TEXTURE_IMAGE_UNITS        0x8872
#وصف_ڪريو GL_MAX_FRAGMENT_هڪجهڙو_VECTORS   0x8DFD
#وصف_ڪريو GL_SHADER_TYPE                    0x8B4F
#وصف_ڪريو GL_DELETE_حالت                  0x8B80
#وصف_ڪريو GL_LINK_حالت                    0x8B82
#وصف_ڪريو GL_VALIDATE_حالت                0x8B83
#وصف_ڪريو GL_ATTACHED_SHADERS               0x8B85
#وصف_ڪريو GL_سرگرم_UNIFORMS                0x8B86
#وصف_ڪريو GL_سرگرم_هڪجهڙو_MAX_ڊيگهائي      0x8B87
#وصف_ڪريو GL_سرگرم_خاصيتون              0x8B89
#وصف_ڪريو GL_سرگرم_ATTRIBUTE_MAX_ڊيگهائي    0x8B8A
#وصف_ڪريو GL_SHADING_LANGUAGE_نسخو       0x8B8C
#وصف_ڪريو GL_CURRENT_پروگرام                0x8B8D
#وصف_ڪريو GL_NEVER                          0x0200
#وصف_ڪريو GL_LESS                           0x0201
#وصف_ڪريو GL_EQUAL                          0x0202
#وصف_ڪريو GL_LEQUAL                         0x0203
#وصف_ڪريو GL_GREATER                        0x0204
#وصف_ڪريو GL_NOTEQUAL                       0x0205
#وصف_ڪريو GL_GEQUAL                         0x0206
#وصف_ڪريو GL_ALWAYS                         0x0207
#وصف_ڪريو GL_KEEP                           0x1E00
#وصف_ڪريو GL_REPLACE                        0x1E01
#وصف_ڪريو GL_INCR                           0x1E02
#وصف_ڪريو GL_DECR                           0x1E03
#وصف_ڪريو GL_INVERT                         0x150A
#وصف_ڪريو GL_INCR_WRAP                      0x8507
#وصف_ڪريو GL_DECR_WRAP                      0x8508
#وصف_ڪريو GL_VENDOR                         0x1F00
#وصف_ڪريو GL_RENDERER                       0x1F01
#وصف_ڪريو GL_نسخو                        0x1F02
#وصف_ڪريو GL_EXTENSIONS                     0x1F03
#وصف_ڪريو GL_سڀ_کان_ويجهو                        0x2600
#وصف_ڪريو GL_لڪيري                         0x2601
#وصف_ڪريو GL_سڀ_کان_ويجهو_MIPMAP_سڀ_کان_ويجهو         0x2700
#وصف_ڪريو GL_لڪيري_MIPMAP_سڀ_کان_ويجهو          0x2701
#وصف_ڪريو GL_سڀ_کان_ويجهو_MIPMAP_لڪيري          0x2702
#وصف_ڪريو GL_لڪيري_MIPMAP_لڪيري           0x2703
#وصف_ڪريو GL_TEXTURE_MAG_FILTER             0x2800
#وصف_ڪريو GL_TEXTURE_MIN_FILTER             0x2801
#وصف_ڪريو GL_TEXTURE_WRAP_S                 0x2802
#وصف_ڪريو GL_TEXTURE_WRAP_T                 0x2803
#وصف_ڪريو GL_TEXTURE                        0x1702
#وصف_ڪريو GL_TEXTURE_CUBE_MAP               0x8513
#وصف_ڪريو GL_TEXTURE_BINDING_CUBE_MAP       0x8514
#وصف_ڪريو GL_TEXTURE_CUBE_MAP_مثبت_X    0x8515
#وصف_ڪريو GL_TEXTURE_CUBE_MAP_NEGATIVE_X    0x8516
#وصف_ڪريو GL_TEXTURE_CUBE_MAP_مثبت_Y    0x8517
#وصف_ڪريو GL_TEXTURE_CUBE_MAP_NEGATIVE_Y    0x8518
#وصف_ڪريو GL_TEXTURE_CUBE_MAP_مثبت_Z    0x8519
#وصف_ڪريو GL_TEXTURE_CUBE_MAP_NEGATIVE_Z    0x851A
#وصف_ڪريو GL_MAX_CUBE_MAP_TEXTURE_سائيز      0x851C
#وصف_ڪريو GL_TEXTURE0                       0x84C0
#وصف_ڪريو GL_TEXTURE1                       0x84C1
#وصف_ڪريو GL_TEXTURE2                       0x84C2
#وصف_ڪريو GL_TEXTURE3                       0x84C3
#وصف_ڪريو GL_TEXTURE4                       0x84C4
#وصف_ڪريو GL_TEXTURE5                       0x84C5
#وصف_ڪريو GL_TEXTURE6                       0x84C6
#وصف_ڪريو GL_TEXTURE7                       0x84C7
#وصف_ڪريو GL_TEXTURE8                       0x84C8
#وصف_ڪريو GL_TEXTURE9                       0x84C9
#وصف_ڪريو GL_TEXTURE10                      0x84CA
#وصف_ڪريو GL_TEXTURE11                      0x84CB
#وصف_ڪريو GL_TEXTURE12                      0x84CC
#وصف_ڪريو GL_TEXTURE13                      0x84CD
#وصف_ڪريو GL_TEXTURE14                      0x84CE
#وصف_ڪريو GL_TEXTURE15                      0x84CF
#وصف_ڪريو GL_TEXTURE16                      0x84D0
#وصف_ڪريو GL_TEXTURE17                      0x84D1
#وصف_ڪريو GL_TEXTURE18                      0x84D2
#وصف_ڪريو GL_TEXTURE19                      0x84D3
#وصف_ڪريو GL_TEXTURE20                      0x84D4
#وصف_ڪريو GL_TEXTURE21                      0x84D5
#وصف_ڪريو GL_TEXTURE22                      0x84D6
#وصف_ڪريو GL_TEXTURE23                      0x84D7
#وصف_ڪريو GL_TEXTURE24                      0x84D8
#وصف_ڪريو GL_TEXTURE25                      0x84D9
#وصف_ڪريو GL_TEXTURE26                      0x84DA
#وصف_ڪريو GL_TEXTURE27                      0x84DB
#وصف_ڪريو GL_TEXTURE28                      0x84DC
#وصف_ڪريو GL_TEXTURE29                      0x84DD
#وصف_ڪريو GL_TEXTURE30                      0x84DE
#وصف_ڪريو GL_TEXTURE31                      0x84DF
#وصف_ڪريو GL_سرگرم_TEXTURE                 0x84E0
#وصف_ڪريو GL_REPEAT                         0x2901
#وصف_ڪريو GL_CLAMP_منزل_ڪنارو                  0x812F
#وصف_ڪريو GL_MIRRORED_REPEAT                0x8370
#وصف_ڪريو GL_FLOAT_VEC2                     0x8B50
#وصف_ڪريو GL_FLOAT_VEC3                     0x8B51
#وصف_ڪريو GL_FLOAT_VEC4                     0x8B52
#وصف_ڪريو GL_INT_VEC2                       0x8B53
#وصف_ڪريو GL_INT_VEC3                       0x8B54
#وصف_ڪريو GL_INT_VEC4                       0x8B55
#وصف_ڪريو GL_BOOL                           0x8B56
#وصف_ڪريو GL_BOOL_VEC2                      0x8B57
#وصف_ڪريو GL_BOOL_VEC3                      0x8B58
#وصف_ڪريو GL_BOOL_VEC4                      0x8B59
#وصف_ڪريو GL_FLOAT_MAT2                     0x8B5A
#وصف_ڪريو GL_FLOAT_MAT3                     0x8B5B
#وصف_ڪريو GL_FLOAT_MAT4                     0x8B5C
#وصف_ڪريو GL_SAMPLER_2D                     0x8B5E
#وصف_ڪريو GL_SAMPLER_CUBE                   0x8B60
#وصف_ڪريو GL_راس_ATTRIB_ARRAY_ENABLED    0x8622
#وصف_ڪريو GL_راس_ATTRIB_ARRAY_سائيز       0x8623
#وصف_ڪريو GL_راس_ATTRIB_ARRAY_STRIDE     0x8624
#وصف_ڪريو GL_راس_ATTRIB_ARRAY_TYPE       0x8625
#وصف_ڪريو GL_راس_ATTRIB_ARRAY_NORMALIZED 0x886A
#وصف_ڪريو GL_راس_ATTRIB_ARRAY_اشارو    0x8645
#وصف_ڪريو GL_راس_ATTRIB_ARRAY_بفر_BINDING 0x889F
#وصف_ڪريو GL_IMPLEMENTATION_COLOR_READ_TYPE 0x8B9A
#وصف_ڪريو GL_IMPLEMENTATION_COLOR_READ_FORMAT 0x8B9B
#وصف_ڪريو GL_COMPILE_حالت                 0x8B81
#وصف_ڪريو GL_INFO_LOG_ڊيگهائي                0x8B84
#وصف_ڪريو GL_SHADER_ذريعو_ڊيگهائي           0x8B88
#وصف_ڪريو GL_SHADER_COMPILER                0x8DFA
#وصف_ڪريو GL_SHADER_ٻٽو_FORMATS          0x8DF8
#وصف_ڪريو GL_انگ_SHADER_ٻٽو_FORMATS      0x8DF9
#وصف_ڪريو GL_هيٺيون_FLOAT                      0x8DF0
#وصف_ڪريو GL_MEDIUM_FLOAT                   0x8DF1
#وصف_ڪريو GL_مٿاهون_FLOAT                     0x8DF2
#وصف_ڪريو GL_هيٺيون_INT                        0x8DF3
#وصف_ڪريو GL_MEDIUM_INT                     0x8DF4
#وصف_ڪريو GL_مٿاهون_INT                       0x8DF5
#وصف_ڪريو GL_FRAMEBUFFER                    0x8D40
#وصف_ڪريو GL_RENDERBUFFER                   0x8D41
#وصف_ڪريو GL_RGBA4                          0x8056
#وصف_ڪريو GL_RGB5_A1                        0x8057
#وصف_ڪريو GL_RGB565                         0x8D62
#وصف_ڪريو GL_اونهائي_COMPONENT16              0x81A5
#وصف_ڪريو GL_STENCIL_INDEX8                 0x8D48
#وصف_ڪريو GL_RENDERBUFFER_ويڪر             0x8D42
#وصف_ڪريو GL_RENDERBUFFER_اوچائي            0x8D43
#وصف_ڪريو GL_RENDERBUFFER_اندروني_FORMAT   0x8D44
#وصف_ڪريو GL_RENDERBUFFER_RED_سائيز          0x8D50
#وصف_ڪريو GL_RENDERBUFFER_GREEN_سائيز        0x8D51
#وصف_ڪريو GL_RENDERBUFFER_BLUE_سائيز         0x8D52
#وصف_ڪريو GL_RENDERBUFFER_ALPHA_سائيز        0x8D53
#وصف_ڪريو GL_RENDERBUFFER_اونهائي_سائيز        0x8D54
#وصف_ڪريو GL_RENDERBUFFER_STENCIL_سائيز      0x8D55
#وصف_ڪريو GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE 0x8CD0
#وصف_ڪريو GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME 0x8CD1
#وصف_ڪريو GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL 0x8CD2
#وصف_ڪريو GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE 0x8CD3
#وصف_ڪريو GL_COLOR_ATTACHMENT0              0x8CE0
#وصف_ڪريو GL_اونهائي_ATTACHMENT               0x8D00
#وصف_ڪريو GL_STENCIL_ATTACHMENT             0x8D20
#وصف_ڪريو GL_NONE                           0
#وصف_ڪريو GL_FRAMEBUFFER_COMPLETE           0x8CD5
#وصف_ڪريو GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT 0x8CD6
#وصف_ڪريو GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 0x8CD7
#وصف_ڪريو GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS 0x8CD9
#وصف_ڪريو GL_FRAMEBUFFER_UNSUPPORTED        0x8CDD
#وصف_ڪريو GL_FRAMEBUFFER_BINDING            0x8CA6
#وصف_ڪريو GL_RENDERBUFFER_BINDING           0x8CA7
#وصف_ڪريو GL_MAX_RENDERBUFFER_سائيز          0x84E8
#وصف_ڪريو GL_INVALID_FRAMEBUFFER_OPERATION  0x0506
تعريفنوع فراغ (GL_APIENTRYP PFNGLACTIVETEXTUREPROC) (GLenum texture);
تعريفنوع فراغ (GL_APIENTRYP PFNGLATTACHSHADERPROC) (GLuint پروگرام, GLuint shader);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDATTRIBLOCATIONPROC) (GLuint پروگرام, GLuint اشاريو, ثابت GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDBUFFERPROC) (GLenum هدف, GLuint بفر_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDFRAMEBUFFERPROC) (GLenum هدف, GLuint framebuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDRENDERBUFFERPROC) (GLenum هدف, GLuint renderbuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDTEXTUREPROC) (GLenum هدف, GLuint texture);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONPROC) (GLenum گهڻائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEPROC) (GLenum گهڻائي_RGB, GLenum گهڻائي_Alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDFUNCPROC) (GLenum sfactor, GLenum dfactor);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEPROC) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBUFFERDATAPROC) (GLenum هدف, GLsizeiptr سائيز, ثابت فراغ *معلومات, GLenum usage);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBUFFERSUBDATAPROC) (GLenum هدف, GLintptr وٿي_2, GLsizeiptr سائيز, ثابت فراغ *معلومات);
تعريفنوع GLenum (GL_APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSPROC) (GLenum هدف);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARPROC) (GLbitfield نقاب);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARDEPTHFPROC) (GLfloat d);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARSTENCILPROC) (GLint s);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOLORMASKPROC) (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOMPILESHADERPROC) (GLuint shader);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOMPRESSEDTEXIMAGE2DPROC) (GLenum هدف, GLint level, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي, GLint border, GLsizei image_سائيز, ثابت فراغ *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLsizei ويڪر, GLsizei اوچائي, GLenum format, GLsizei image_سائيز, ثابت فراغ *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYTEXIMAGE2DPROC) (GLenum هدف, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei ويڪر, GLsizei اوچائي, GLint border);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYTEXSUBIMAGE2DPROC) (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei ويڪر, GLsizei اوچائي);
تعريفنوع GLuint (GL_APIENTRYP PFNGLCREATEPROGRAMPROC) (فراغ);
تعريفنوع GLuint (GL_APIENTRYP PFNGLCREATESHADERPROC) (GLenum type);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCULLFACEPROC) (GLenum گهڻائي);
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
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint اشاريو);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWARRAYSPROC) (GLenum گهڻائي, GLint پهريون, GLsizei ڳڻپ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSPROC) (GLenum گهڻائي, GLsizei ڳڻپ, GLenum type, ثابت فراغ *indices);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENABLEPROC) (GLenum cap);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint اشاريو);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFINISHPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFLUSHPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFERPROC) (GLenum هدف, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DPROC) (GLenum هدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRONTFACEPROC) (GLenum گهڻائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENBUFFERSPROC) (GLsizei n, GLuint *buffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENERATEMIPMAPPROC) (GLenum هدف);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENFRAMEBUFFERSPROC) (GLsizei n, GLuint *framebuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENRENDERBUFFERSPROC) (GLsizei n, GLuint *renderbuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENTEXTURESPROC) (GLsizei n, GLuint *textures);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETACTIVEATTRIBPROC) (GLuint پروگرام, GLuint اشاريو, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLint *سائيز, GLenum *type, GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETACTIVEUNIFORMPROC) (GLuint پروگرام, GLuint اشاريو, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLint *سائيز, GLenum *type, GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETATTACHEDSHADERSPROC) (GLuint پروگرام, GLsizei max_ڳڻپ, GLsizei *ڳڻپ, GLuint *shaders);
تعريفنوع GLint (GL_APIENTRYP PFNGLGETATTRIBLOCATIONPROC) (GLuint پروگرام, ثابت GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETBOOLEANVPROC) (GLenum pname, GLboolean *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETBUFFERPARAMETERIVPROC) (GLenum هدف, GLenum pname, GLint *params);
تعريفنوع GLenum (GL_APIENTRYP PFNGLGETERRORPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFLOATVPROC) (GLenum pname, GLfloat *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) (GLenum هدف, GLenum attachment, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTEGERVPROC) (GLenum pname, GLint *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMIVPROC) (GLuint پروگرام, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMINFOLOGPROC) (GLuint پروگرام, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLchar *infoLog);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVPROC) (GLenum هدف, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLchar *infoLog);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSHADERPRECISIONFORMATPROC) (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSHADERSOURCEPROC) (GLuint shader, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLchar *ذريعو);
تعريفنوع ثابت GLubyte *(GL_APIENTRYP PFNGLGETSTRINGPROC) (GLenum name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXPARAMETERFVPROC) (GLenum هدف, GLenum pname, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXPARAMETERIVPROC) (GLenum هدف, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETUNIFORMFVPROC) (GLuint پروگرام, GLint location, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETUNIFORMIVPROC) (GLuint پروگرام, GLint location, GLint *params);
تعريفنوع GLint (GL_APIENTRYP PFNGLGETUNIFORMLOCATIONPROC) (GLuint پروگرام, ثابت GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETVERTEXATTRIBFVPROC) (GLuint اشاريو, GLenum pname, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETVERTEXATTRIBIVPROC) (GLuint اشاريو, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETVERTEXATTRIBPOINTERVPROC) (GLuint اشاريو, GLenum pname, فراغ **اشارو_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLHINTPROC) (GLenum هدف, GLenum گهڻائي);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISBUFFERPROC) (GLuint بفر_2);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISENABLEDPROC) (GLenum cap);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISFRAMEBUFFERPROC) (GLuint framebuffer);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISPROGRAMPROC) (GLuint پروگرام);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISRENDERBUFFERPROC) (GLuint renderbuffer);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISSHADERPROC) (GLuint shader);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISTEXTUREPROC) (GLuint texture);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLINEWIDTHPROC) (GLfloat ويڪر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLINKPROGRAMPROC) (GLuint پروگرام);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPIXELSTOREIPROC) (GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOLYGONOFFSETPROC) (GLfloat ضرب_ڪندڙ, GLfloat units);
تعريفنوع فراغ (GL_APIENTRYP PFNGLREADPIXELSPROC) (GLint x, GLint y, GLsizei ويڪر, GLsizei اوچائي, GLenum format, GLenum type, فراغ *pixels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRELEASESHADERCOMPILERPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEPROC) (GLenum هدف, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLECOVERAGEPROC) (GLfloat قدر, GLboolean invert);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSORPROC) (GLint x, GLint y, GLsizei ويڪر, GLsizei اوچائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADERBINARYPROC) (GLsizei ڳڻپ, ثابت GLuint *shaders, GLenum ٻٽو_Format, ثابت فراغ *ٻٽو, GLsizei ڊيگهائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei ڳڻپ, ثابت GLchar *ثابت*string, ثابت GLint *ڊيگهائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILFUNCPROC) (GLenum func, GLint ref, GLuint نقاب);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILFUNCSEPARATEPROC) (GLenum face, GLenum func, GLint ref, GLuint نقاب);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILMASKPROC) (GLuint نقاب);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILMASKSEPARATEPROC) (GLenum face, GLuint نقاب);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILOPPROC) (GLenum fail, GLenum zfail, GLenum zpass);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILOPSEPARATEPROC) (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXIMAGE2DPROC) (GLenum هدف, GLint level, GLint internalformat, GLsizei ويڪر, GLsizei اوچائي, GLint border, GLenum format, GLenum type, ثابت فراغ *pixels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERFPROC) (GLenum هدف, GLenum pname, GLfloat param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERFVPROC) (GLenum هدف, GLenum pname, ثابت GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERIPROC) (GLenum هدف, GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERIVPROC) (GLenum هدف, GLenum pname, ثابت GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSUBIMAGE2DPROC) (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLsizei ويڪر, GLsizei اوچائي, GLenum format, GLenum type, ثابت فراغ *pixels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1FPROC) (GLint location, GLfloat v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1FVPROC) (GLint location, GLsizei ڳڻپ, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1IPROC) (GLint location, GLint v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1IVPROC) (GLint location, GLsizei ڳڻپ, ثابت GLint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2FPROC) (GLint location, GLfloat v0, GLfloat v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2FVPROC) (GLint location, GLsizei ڳڻپ, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2IPROC) (GLint location, GLint v0, GLint v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2IVPROC) (GLint location, GLsizei ڳڻپ, ثابت GLint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3FVPROC) (GLint location, GLsizei ڳڻپ, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3IPROC) (GLint location, GLint v0, GLint v1, GLint v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3IVPROC) (GLint location, GLsizei ڳڻپ, ثابت GLint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4FVPROC) (GLint location, GLsizei ڳڻپ, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4IPROC) (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4IVPROC) (GLint location, GLsizei ڳڻپ, ثابت GLint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX2FVPROC) (GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX3FVPROC) (GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUSEPROGRAMPROC) (GLuint پروگرام);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVALIDATEPROGRAMPROC) (GLuint پروگرام);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB1FPROC) (GLuint اشاريو, GLfloat x);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB1FVPROC) (GLuint اشاريو, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB2FPROC) (GLuint اشاريو, GLfloat x, GLfloat y);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB2FVPROC) (GLuint اشاريو, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB3FPROC) (GLuint اشاريو, GLfloat x, GLfloat y, GLfloat z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB3FVPROC) (GLuint اشاريو, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB4FPROC) (GLuint اشاريو, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB4FVPROC) (GLuint اشاريو, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC) (GLuint اشاريو, GLint سائيز, GLenum type, GLboolean normalized, GLsizei stride, ثابت فراغ *اشارو_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTPROC) (GLint x, GLint y, GLsizei ويڪر, GLsizei اوچائي);
#إذا GL_GLES_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_سرگرم_Texture (GLenum texture);
GL_APICALL فراغ GL_APIENTRY glAttachShader (GLuint پروگرام, GLuint shader);
GL_APICALL فراغ GL_APIENTRY glBindAttribLocation (GLuint پروگرام, GLuint اشاريو, ثابت GLchar *name);
GL_APICALL فراغ GL_APIENTRY gl_Bind_بفر (GLenum هدف, GLuint بفر_2);
GL_APICALL فراغ GL_APIENTRY glBindFramebuffer (GLenum هدف, GLuint framebuffer);
GL_APICALL فراغ GL_APIENTRY glBindRenderbuffer (GLenum هدف, GLuint renderbuffer);
GL_APICALL فراغ GL_APIENTRY glBindTexture (GLenum هدف, GLuint texture);
GL_APICALL فراغ GL_APIENTRY glBlendColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_APICALL فراغ GL_APIENTRY glBlendEquation (GLenum گهڻائي);
GL_APICALL فراغ GL_APIENTRY glBlendEquationSeparate (GLenum گهڻائي_RGB, GLenum گهڻائي_Alpha);
GL_APICALL فراغ GL_APIENTRY glBlendFunc (GLenum sfactor, GLenum dfactor);
GL_APICALL فراغ GL_APIENTRY glBlendFuncSeparate (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
GL_APICALL فراغ GL_APIENTRY gl_بفر_معلومات (GLenum هدف, GLsizeiptr سائيز, ثابت فراغ *معلومات, GLenum usage);
GL_APICALL فراغ GL_APIENTRY gl_بفر_Sub_معلومات (GLenum هدف, GLintptr وٿي_2, GLsizeiptr سائيز, ثابت فراغ *معلومات);
GL_APICALL GLenum GL_APIENTRY gl_Check_Framebuffer_حالت (GLenum هدف);
GL_APICALL فراغ GL_APIENTRY glClear (GLbitfield نقاب);
GL_APICALL فراغ GL_APIENTRY glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_APICALL فراغ GL_APIENTRY glClearDepthf (GLfloat d);
GL_APICALL فراغ GL_APIENTRY glClearStencil (GLint s);
GL_APICALL فراغ GL_APIENTRY gl_Color_نقاب (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
GL_APICALL فراغ GL_APIENTRY glCompileShader (GLuint shader);
GL_APICALL فراغ GL_APIENTRY glCompressedTexImage2D (GLenum هدف, GLint level, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي, GLint border, GLsizei image_سائيز, ثابت فراغ *معلومات);
GL_APICALL فراغ GL_APIENTRY glCompressedTexSubImage2D (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLsizei ويڪر, GLsizei اوچائي, GLenum format, GLsizei image_سائيز, ثابت فراغ *معلومات);
GL_APICALL فراغ GL_APIENTRY glCopyTexImage2D (GLenum هدف, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei ويڪر, GLsizei اوچائي, GLint border);
GL_APICALL فراغ GL_APIENTRY glCopyTexSubImage2D (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei ويڪر, GLsizei اوچائي);
GL_APICALL GLuint GL_APIENTRY gl_Create_پروگرام (فراغ);
GL_APICALL GLuint GL_APIENTRY glCreateShader (GLenum type);
GL_APICALL فراغ GL_APIENTRY glCullFace (GLenum گهڻائي);
GL_APICALL فراغ GL_APIENTRY glDeleteBuffers (GLsizei n, ثابت GLuint *buffers);
GL_APICALL فراغ GL_APIENTRY glDeleteFramebuffers (GLsizei n, ثابت GLuint *framebuffers);
GL_APICALL فراغ GL_APIENTRY gl_Delete_پروگرام (GLuint پروگرام);
GL_APICALL فراغ GL_APIENTRY glDeleteRenderbuffers (GLsizei n, ثابت GLuint *renderbuffers);
GL_APICALL فراغ GL_APIENTRY glDeleteShader (GLuint shader);
GL_APICALL فراغ GL_APIENTRY glDeleteTextures (GLsizei n, ثابت GLuint *textures);
GL_APICALL فراغ GL_APIENTRY gl_اونهائي_Func (GLenum func);
GL_APICALL فراغ GL_APIENTRY gl_اونهائي_نقاب (GLboolean flag);
GL_APICALL فراغ GL_APIENTRY gl_اونهائي_Rangef (GLfloat n, GLfloat f);
GL_APICALL فراغ GL_APIENTRY glDetachShader (GLuint پروگرام, GLuint shader);
GL_APICALL فراغ GL_APIENTRY glDisable (GLenum cap);
GL_APICALL فراغ GL_APIENTRY gl_Disable_راس_Attrib_Array (GLuint اشاريو);
GL_APICALL فراغ GL_APIENTRY glDrawArrays (GLenum گهڻائي, GLint پهريون, GLsizei ڳڻپ);
GL_APICALL فراغ GL_APIENTRY glDrawElements (GLenum گهڻائي, GLsizei ڳڻپ, GLenum type, ثابت فراغ *indices);
GL_APICALL فراغ GL_APIENTRY glEnable (GLenum cap);
GL_APICALL فراغ GL_APIENTRY gl_Enable_راس_Attrib_Array (GLuint اشاريو);
GL_APICALL فراغ GL_APIENTRY gl_پڄاڻي (فراغ);
GL_APICALL فراغ GL_APIENTRY glFlush (فراغ);
GL_APICALL فراغ GL_APIENTRY glFramebufferRenderbuffer (GLenum هدف, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
GL_APICALL فراغ GL_APIENTRY glFramebufferTexture2D (GLenum هدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GL_APICALL فراغ GL_APIENTRY glFrontFace (GLenum گهڻائي);
GL_APICALL فراغ GL_APIENTRY glGenBuffers (GLsizei n, GLuint *buffers);
GL_APICALL فراغ GL_APIENTRY glGenerateMipmap (GLenum هدف);
GL_APICALL فراغ GL_APIENTRY glGenFramebuffers (GLsizei n, GLuint *framebuffers);
GL_APICALL فراغ GL_APIENTRY glGenRenderbuffers (GLsizei n, GLuint *renderbuffers);
GL_APICALL فراغ GL_APIENTRY glGenTextures (GLsizei n, GLuint *textures);
GL_APICALL فراغ GL_APIENTRY gl_Get_سرگرم_Attrib (GLuint پروگرام, GLuint اشاريو, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLint *سائيز, GLenum *type, GLchar *name);
GL_APICALL فراغ GL_APIENTRY gl_Get_سرگرم_هڪجهڙو (GLuint پروگرام, GLuint اشاريو, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLint *سائيز, GLenum *type, GLchar *name);
GL_APICALL فراغ GL_APIENTRY glGetAttachedShaders (GLuint پروگرام, GLsizei max_ڳڻپ, GLsizei *ڳڻپ, GLuint *shaders);
GL_APICALL GLint GL_APIENTRY glGetAttribLocation (GLuint پروگرام, ثابت GLchar *name);
GL_APICALL فراغ GL_APIENTRY glGetBooleanv (GLenum pname, GLboolean *معلومات);
GL_APICALL فراغ GL_APIENTRY gl_Get_بفر_Parameteriv (GLenum هدف, GLenum pname, GLint *params);
GL_APICALL GLenum GL_APIENTRY glGetError (فراغ);
GL_APICALL فراغ GL_APIENTRY glGetFloatv (GLenum pname, GLfloat *معلومات);
GL_APICALL فراغ GL_APIENTRY glGetFramebufferAttachmentParameteriv (GLenum هدف, GLenum attachment, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetIntegerv (GLenum pname, GLint *معلومات);
GL_APICALL فراغ GL_APIENTRY glGetProgramiv (GLuint پروگرام, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY gl_Get_پروگرام_Info_Log (GLuint پروگرام, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLchar *infoLog);
GL_APICALL فراغ GL_APIENTRY glGetRenderbufferParameteriv (GLenum هدف, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetShaderiv (GLuint shader, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetShaderInfoLog (GLuint shader, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLchar *infoLog);
GL_APICALL فراغ GL_APIENTRY glGetShaderPrecisionFormat (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
GL_APICALL فراغ GL_APIENTRY gl_Get_Shader_ذريعو (GLuint shader, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLchar *ذريعو);
GL_APICALL ثابت GLubyte *GL_APIENTRY glGetString (GLenum name);
GL_APICALL فراغ GL_APIENTRY glGetTexParameterfv (GLenum هدف, GLenum pname, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY glGetTexParameteriv (GLenum هدف, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetUniformfv (GLuint پروگرام, GLint location, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY glGetUniformiv (GLuint پروگرام, GLint location, GLint *params);
GL_APICALL GLint GL_APIENTRY gl_Get_هڪجهڙو_Location (GLuint پروگرام, ثابت GLchar *name);
GL_APICALL فراغ GL_APIENTRY gl_Get_راس_Attribfv (GLuint اشاريو, GLenum pname, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY gl_Get_راس_Attribiv (GLuint اشاريو, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY gl_Get_راس_Attrib_Pointerv (GLuint اشاريو, GLenum pname, فراغ **اشارو_2);
GL_APICALL فراغ GL_APIENTRY glHint (GLenum هدف, GLenum گهڻائي);
GL_APICALL GLboolean GL_APIENTRY gl_Is_بفر (GLuint بفر_2);
GL_APICALL GLboolean GL_APIENTRY glIsEnabled (GLenum cap);
GL_APICALL GLboolean GL_APIENTRY glIsFramebuffer (GLuint framebuffer);
GL_APICALL GLboolean GL_APIENTRY gl_Is_پروگرام (GLuint پروگرام);
GL_APICALL GLboolean GL_APIENTRY glIsRenderbuffer (GLuint renderbuffer);
GL_APICALL GLboolean GL_APIENTRY glIsShader (GLuint shader);
GL_APICALL GLboolean GL_APIENTRY glIsTexture (GLuint texture);
GL_APICALL فراغ GL_APIENTRY gl_سٽ_ويڪر (GLfloat ويڪر);
GL_APICALL فراغ GL_APIENTRY gl_Link_پروگرام (GLuint پروگرام);
GL_APICALL فراغ GL_APIENTRY glPixelStorei (GLenum pname, GLint param);
GL_APICALL فراغ GL_APIENTRY gl_Polygon_وٿي (GLfloat ضرب_ڪندڙ, GLfloat units);
GL_APICALL فراغ GL_APIENTRY glReadPixels (GLint x, GLint y, GLsizei ويڪر, GLsizei اوچائي, GLenum format, GLenum type, فراغ *pixels);
GL_APICALL فراغ GL_APIENTRY glReleaseShaderCompiler (فراغ);
GL_APICALL فراغ GL_APIENTRY glRenderbufferStorage (GLenum هدف, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
GL_APICALL فراغ GL_APIENTRY glSampleCoverage (GLfloat قدر, GLboolean invert);
GL_APICALL فراغ GL_APIENTRY glScissor (GLint x, GLint y, GLsizei ويڪر, GLsizei اوچائي);
GL_APICALL فراغ GL_APIENTRY gl_Shader_ٻٽو (GLsizei ڳڻپ, ثابت GLuint *shaders, GLenum ٻٽو_Format, ثابت فراغ *ٻٽو, GLsizei ڊيگهائي);
GL_APICALL فراغ GL_APIENTRY gl_Shader_ذريعو (GLuint shader, GLsizei ڳڻپ, ثابت GLchar *ثابت*string, ثابت GLint *ڊيگهائي);
GL_APICALL فراغ GL_APIENTRY glStencilFunc (GLenum func, GLint ref, GLuint نقاب);
GL_APICALL فراغ GL_APIENTRY glStencilFuncSeparate (GLenum face, GLenum func, GLint ref, GLuint نقاب);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_نقاب (GLuint نقاب);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_نقاب_Separate (GLenum face, GLuint نقاب);
GL_APICALL فراغ GL_APIENTRY glStencilOp (GLenum fail, GLenum zfail, GLenum zpass);
GL_APICALL فراغ GL_APIENTRY glStencilOpSeparate (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
GL_APICALL فراغ GL_APIENTRY glTexImage2D (GLenum هدف, GLint level, GLint internalformat, GLsizei ويڪر, GLsizei اوچائي, GLint border, GLenum format, GLenum type, ثابت فراغ *pixels);
GL_APICALL فراغ GL_APIENTRY glTexParameterf (GLenum هدف, GLenum pname, GLfloat param);
GL_APICALL فراغ GL_APIENTRY glTexParameterfv (GLenum هدف, GLenum pname, ثابت GLfloat *params);
GL_APICALL فراغ GL_APIENTRY glTexParameteri (GLenum هدف, GLenum pname, GLint param);
GL_APICALL فراغ GL_APIENTRY glTexParameteriv (GLenum هدف, GLenum pname, ثابت GLint *params);
GL_APICALL فراغ GL_APIENTRY glTexSubImage2D (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLsizei ويڪر, GLsizei اوچائي, GLenum format, GLenum type, ثابت فراغ *pixels);
GL_APICALL فراغ GL_APIENTRY glUniform1f (GLint location, GLfloat v0);
GL_APICALL فراغ GL_APIENTRY glUniform1fv (GLint location, GLsizei ڳڻپ, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY glUniform1i (GLint location, GLint v0);
GL_APICALL فراغ GL_APIENTRY glUniform1iv (GLint location, GLsizei ڳڻپ, ثابت GLint *قدر);
GL_APICALL فراغ GL_APIENTRY glUniform2f (GLint location, GLfloat v0, GLfloat v1);
GL_APICALL فراغ GL_APIENTRY glUniform2fv (GLint location, GLsizei ڳڻپ, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY glUniform2i (GLint location, GLint v0, GLint v1);
GL_APICALL فراغ GL_APIENTRY glUniform2iv (GLint location, GLsizei ڳڻپ, ثابت GLint *قدر);
GL_APICALL فراغ GL_APIENTRY glUniform3f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
GL_APICALL فراغ GL_APIENTRY glUniform3fv (GLint location, GLsizei ڳڻپ, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY glUniform3i (GLint location, GLint v0, GLint v1, GLint v2);
GL_APICALL فراغ GL_APIENTRY glUniform3iv (GLint location, GLsizei ڳڻپ, ثابت GLint *قدر);
GL_APICALL فراغ GL_APIENTRY glUniform4f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
GL_APICALL فراغ GL_APIENTRY glUniform4fv (GLint location, GLsizei ڳڻپ, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY glUniform4i (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
GL_APICALL فراغ GL_APIENTRY glUniform4iv (GLint location, GLsizei ڳڻپ, ثابت GLint *قدر);
GL_APICALL فراغ GL_APIENTRY gl_هڪجهڙو_Matrix2fv (GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_هڪجهڙو_Matrix3fv (GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_هڪجهڙو_Matrix4fv (GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_Use_پروگرام (GLuint پروگرام);
GL_APICALL فراغ GL_APIENTRY gl_Validate_پروگرام (GLuint پروگرام);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib1f (GLuint اشاريو, GLfloat x);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib1fv (GLuint اشاريو, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib2f (GLuint اشاريو, GLfloat x, GLfloat y);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib2fv (GLuint اشاريو, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib3f (GLuint اشاريو, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib3fv (GLuint اشاريو, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib4f (GLuint اشاريو, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib4fv (GLuint اشاريو, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib_اشارو (GLuint اشاريو, GLint سائيز, GLenum type, GLboolean normalized, GLsizei stride, ثابت فراغ *اشارو_2);
GL_APICALL فراغ GL_APIENTRY glViewport (GLint x, GLint y, GLsizei ويڪر, GLsizei اوچائي);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_ES_VERSION_2_0 */

#جيڪڏهن_وصف_نه_ٿيل GL_ES_نسخو_3_0
#وصف_ڪريو GL_ES_نسخو_3_0 1
تعريفنوع khronos_uint16_t GLhalf;
#وصف_ڪريو GL_READ_بفر                    0x0C02
#وصف_ڪريو GL_UNPACK_صف_ڊيگهائي              0x0CF2
#وصف_ڪريو GL_UNPACK_SKIP_صفون               0x0CF3
#وصف_ڪريو GL_UNPACK_SKIP_PIXELS             0x0CF4
#وصف_ڪريو GL_PACK_صف_ڊيگهائي                0x0D02
#وصف_ڪريو GL_PACK_SKIP_صفون                 0x0D03
#وصف_ڪريو GL_PACK_SKIP_PIXELS               0x0D04
#وصف_ڪريو GL_COLOR                          0x1800
#وصف_ڪريو GL_اونهائي                          0x1801
#وصف_ڪريو GL_STENCIL                        0x1802
#وصف_ڪريو GL_RED                            0x1903
#وصف_ڪريو GL_RGB8                           0x8051
#وصف_ڪريو GL_RGBA8                          0x8058
#وصف_ڪريو GL_RGB10_A2                       0x8059
#وصف_ڪريو GL_TEXTURE_BINDING_3D             0x806A
#وصف_ڪريو GL_UNPACK_SKIP_IMAGES             0x806D
#وصف_ڪريو GL_UNPACK_IMAGE_اوچائي            0x806E
#وصف_ڪريو GL_TEXTURE_3D                     0x806F
#وصف_ڪريو GL_TEXTURE_WRAP_R                 0x8072
#وصف_ڪريو GL_MAX_3_D_TEXTURE_سائيز            0x8073
#وصف_ڪريو GL_UNSIGNED_INT_2_10_10_10_REV    0x8368
#وصف_ڪريو GL_MAX_ELEMENTS_VERTICES          0x80E8
#وصف_ڪريو GL_MAX_ELEMENTS_INDICES           0x80E9
#وصف_ڪريو GL_TEXTURE_MIN_LOD                0x813A
#وصف_ڪريو GL_TEXTURE_MAX_LOD                0x813B
#وصف_ڪريو GL_TEXTURE_بنياد_LEVEL             0x813C
#وصف_ڪريو GL_TEXTURE_MAX_LEVEL              0x813D
#وصف_ڪريو GL_MIN                            0x8007
#وصف_ڪريو GL_MAX                            0x8008
#وصف_ڪريو GL_اونهائي_COMPONENT24              0x81A6
#وصف_ڪريو GL_MAX_TEXTURE_LOD_BIAS           0x84FD
#وصف_ڪريو GL_TEXTURE_COMPARE_گهڻائي           0x884C
#وصف_ڪريو GL_TEXTURE_COMPARE_FUNC           0x884D
#وصف_ڪريو GL_CURRENT_QUERY                  0x8865
#وصف_ڪريو GL_QUERY_نتيجو                   0x8866
#وصف_ڪريو GL_QUERY_نتيجو_موجود         0x8867
#وصف_ڪريو GL_بفر_MAPPED                  0x88BC
#وصف_ڪريو GL_بفر_MAP_اشارو             0x88BD
#وصف_ڪريو GL_وهڪرو_READ                    0x88E1
#وصف_ڪريو GL_وهڪرو_COPY                    0x88E2
#وصف_ڪريو GL_STATIC_READ                    0x88E5
#وصف_ڪريو GL_STATIC_COPY                    0x88E6
#وصف_ڪريو GL_DYNAMIC_READ                   0x88E9
#وصف_ڪريو GL_DYNAMIC_COPY                   0x88EA
#وصف_ڪريو GL_MAX_DRAW_BUFFERS               0x8824
#وصف_ڪريو GL_DRAW_BUFFER0                   0x8825
#وصف_ڪريو GL_DRAW_BUFFER1                   0x8826
#وصف_ڪريو GL_DRAW_BUFFER2                   0x8827
#وصف_ڪريو GL_DRAW_BUFFER3                   0x8828
#وصف_ڪريو GL_DRAW_BUFFER4                   0x8829
#وصف_ڪريو GL_DRAW_BUFFER5                   0x882A
#وصف_ڪريو GL_DRAW_BUFFER6                   0x882B
#وصف_ڪريو GL_DRAW_BUFFER7                   0x882C
#وصف_ڪريو GL_DRAW_BUFFER8                   0x882D
#وصف_ڪريو GL_DRAW_BUFFER9                   0x882E
#وصف_ڪريو GL_DRAW_BUFFER10                  0x882F
#وصف_ڪريو GL_DRAW_BUFFER11                  0x8830
#وصف_ڪريو GL_DRAW_BUFFER12                  0x8831
#وصف_ڪريو GL_DRAW_BUFFER13                  0x8832
#وصف_ڪريو GL_DRAW_BUFFER14                  0x8833
#وصف_ڪريو GL_DRAW_BUFFER15                  0x8834
#وصف_ڪريو GL_MAX_FRAGMENT_هڪجهڙو_COMPONENTS 0x8B49
#وصف_ڪريو GL_MAX_راس_هڪجهڙو_COMPONENTS  0x8B4A
#وصف_ڪريو GL_SAMPLER_3D                     0x8B5F
#وصف_ڪريو GL_SAMPLER_2D_SHADOW              0x8B62
#وصف_ڪريو GL_FRAGMENT_SHADER_DERIVATIVE_HINT 0x8B8B
#وصف_ڪريو GL_PIXEL_PACK_بفر              0x88EB
#وصف_ڪريو GL_PIXEL_UNPACK_بفر            0x88EC
#وصف_ڪريو GL_PIXEL_PACK_بفر_BINDING      0x88ED
#وصف_ڪريو GL_PIXEL_UNPACK_بفر_BINDING    0x88EF
#وصف_ڪريو GL_FLOAT_MAT2x3                   0x8B65
#وصف_ڪريو GL_FLOAT_MAT2x4                   0x8B66
#وصف_ڪريو GL_FLOAT_MAT3x2                   0x8B67
#وصف_ڪريو GL_FLOAT_MAT3x4                   0x8B68
#وصف_ڪريو GL_FLOAT_MAT4x2                   0x8B69
#وصف_ڪريو GL_FLOAT_MAT4x3                   0x8B6A
#وصف_ڪريو GL_SRGB                           0x8C40
#وصف_ڪريو GL_SRGB8                          0x8C41
#وصف_ڪريو GL_SRGB8_ALPHA8                   0x8C43
#وصف_ڪريو GL_COMPARE_REF_منزل_TEXTURE         0x884E
#وصف_ڪريو GL_MAJOR_نسخو                  0x821B
#وصف_ڪريو GL_MINOR_نسخو                  0x821C
#وصف_ڪريو GL_انگ_EXTENSIONS                 0x821D
#وصف_ڪريو GL_RGBA32F                        0x8814
#وصف_ڪريو GL_RGB32F                         0x8815
#وصف_ڪريو GL_RGBA16F                        0x881A
#وصف_ڪريو GL_RGB16F                         0x881B
#وصف_ڪريو GL_راس_ATTRIB_ARRAY_INTEGER    0x88FD
#وصف_ڪريو GL_MAX_ARRAY_TEXTURE_LAYERS       0x88FF
#وصف_ڪريو GL_MIN_پروگرام_TEXEL_وٿي       0x8904
#وصف_ڪريو GL_MAX_پروگرام_TEXEL_وٿي       0x8905
#وصف_ڪريو GL_MAX_VARYING_COMPONENTS         0x8B4B
#وصف_ڪريو GL_TEXTURE_2D_ARRAY               0x8C1A
#وصف_ڪريو GL_TEXTURE_BINDING_2D_ARRAY       0x8C1D
#وصف_ڪريو GL_R11F_G11F_B10F                 0x8C3A
#وصف_ڪريو GL_UNSIGNED_INT_10F_11F_11F_REV   0x8C3B
#وصف_ڪريو GL_RGB9_E5                        0x8C3D
#وصف_ڪريو GL_UNSIGNED_INT_5_9_9_9_REV       0x8C3E
#وصف_ڪريو GL_TRANSFORM_FEEDBACK_VARYING_MAX_ڊيگهائي 0x8C76
#وصف_ڪريو GL_TRANSFORM_FEEDBACK_بفر_گهڻائي 0x8C7F
#وصف_ڪريو GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS 0x8C80
#وصف_ڪريو GL_TRANSFORM_FEEDBACK_VARYINGS    0x8C83
#وصف_ڪريو GL_TRANSFORM_FEEDBACK_بفر_شروعات 0x8C84
#وصف_ڪريو GL_TRANSFORM_FEEDBACK_بفر_سائيز 0x8C85
#وصف_ڪريو GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN 0x8C88
#وصف_ڪريو GL_RASTERIZER_DISCARD             0x8C89
#وصف_ڪريو GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS 0x8C8A
#وصف_ڪريو GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS 0x8C8B
#وصف_ڪريو GL_INTERLEAVED_ATTRIBS            0x8C8C
#وصف_ڪريو GL_SEPARATE_ATTRIBS               0x8C8D
#وصف_ڪريو GL_TRANSFORM_FEEDBACK_بفر      0x8C8E
#وصف_ڪريو GL_TRANSFORM_FEEDBACK_بفر_BINDING 0x8C8F
#وصف_ڪريو GL_RGBA32UI                       0x8D70
#وصف_ڪريو GL_RGB32UI                        0x8D71
#وصف_ڪريو GL_RGBA16UI                       0x8D76
#وصف_ڪريو GL_RGB16UI                        0x8D77
#وصف_ڪريو GL_RGBA8UI                        0x8D7C
#وصف_ڪريو GL_RGB8UI                         0x8D7D
#وصف_ڪريو GL_RGBA32I                        0x8D82
#وصف_ڪريو GL_RGB32I                         0x8D83
#وصف_ڪريو GL_RGBA16I                        0x8D88
#وصف_ڪريو GL_RGB16I                         0x8D89
#وصف_ڪريو GL_RGBA8I                         0x8D8E
#وصف_ڪريو GL_RGB8I                          0x8D8F
#وصف_ڪريو GL_RED_INTEGER                    0x8D94
#وصف_ڪريو GL_RGB_INTEGER                    0x8D98
#وصف_ڪريو GL_RGBA_INTEGER                   0x8D99
#وصف_ڪريو GL_SAMPLER_2D_ARRAY               0x8DC1
#وصف_ڪريو GL_SAMPLER_2D_ARRAY_SHADOW        0x8DC4
#وصف_ڪريو GL_SAMPLER_CUBE_SHADOW            0x8DC5
#وصف_ڪريو GL_UNSIGNED_INT_VEC2              0x8DC6
#وصف_ڪريو GL_UNSIGNED_INT_VEC3              0x8DC7
#وصف_ڪريو GL_UNSIGNED_INT_VEC4              0x8DC8
#وصف_ڪريو GL_INT_SAMPLER_2D                 0x8DCA
#وصف_ڪريو GL_INT_SAMPLER_3D                 0x8DCB
#وصف_ڪريو GL_INT_SAMPLER_CUBE               0x8DCC
#وصف_ڪريو GL_INT_SAMPLER_2D_ARRAY           0x8DCF
#وصف_ڪريو GL_UNSIGNED_INT_SAMPLER_2D        0x8DD2
#وصف_ڪريو GL_UNSIGNED_INT_SAMPLER_3D        0x8DD3
#وصف_ڪريو GL_UNSIGNED_INT_SAMPLER_CUBE      0x8DD4
#وصف_ڪريو GL_UNSIGNED_INT_SAMPLER_2D_ARRAY  0x8DD7
#وصف_ڪريو GL_بفر_ACCESS_FLAGS            0x911F
#وصف_ڪريو GL_بفر_MAP_ڊيگهائي              0x9120
#وصف_ڪريو GL_بفر_MAP_وٿي              0x9121
#وصف_ڪريو GL_اونهائي_COMPONENT32_F             0x8CAC
#وصف_ڪريو GL_DEPTH32F_STENCIL8              0x8CAD
#وصف_ڪريو GL_FLOAT_32_UNSIGNED_INT_24_8_REV 0x8DAD
#وصف_ڪريو GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING 0x8210
#وصف_ڪريو GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE 0x8211
#وصف_ڪريو GL_FRAMEBUFFER_ATTACHMENT_RED_سائيز 0x8212
#وصف_ڪريو GL_FRAMEBUFFER_ATTACHMENT_GREEN_سائيز 0x8213
#وصف_ڪريو GL_FRAMEBUFFER_ATTACHMENT_BLUE_سائيز 0x8214
#وصف_ڪريو GL_FRAMEBUFFER_ATTACHMENT_ALPHA_سائيز 0x8215
#وصف_ڪريو GL_FRAMEBUFFER_ATTACHMENT_اونهائي_سائيز 0x8216
#وصف_ڪريو GL_FRAMEBUFFER_ATTACHMENT_STENCIL_سائيز 0x8217
#وصف_ڪريو GL_FRAMEBUFFER_DEFAULT            0x8218
#وصف_ڪريو GL_FRAMEBUFFER_UNDEFINED          0x8219
#وصف_ڪريو GL_اونهائي_STENCIL_ATTACHMENT       0x821A
#وصف_ڪريو GL_اونهائي_STENCIL                  0x84F9
#وصف_ڪريو GL_UNSIGNED_INT_24_8              0x84FA
#وصف_ڪريو GL_DEPTH24_STENCIL8               0x88F0
#وصف_ڪريو GL_UNSIGNED_NORMALIZED            0x8C17
#وصف_ڪريو GL_DRAW_FRAMEBUFFER_BINDING       0x8CA6
#وصف_ڪريو GL_READ_FRAMEBUFFER               0x8CA8
#وصف_ڪريو GL_DRAW_FRAMEBUFFER               0x8CA9
#وصف_ڪريو GL_READ_FRAMEBUFFER_BINDING       0x8CAA
#وصف_ڪريو GL_RENDERBUFFER_SAMPLES           0x8CAB
#وصف_ڪريو GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER 0x8CD4
#وصف_ڪريو GL_MAX_COLOR_ATTACHMENTS          0x8CDF
#وصف_ڪريو GL_COLOR_ATTACHMENT1              0x8CE1
#وصف_ڪريو GL_COLOR_ATTACHMENT2              0x8CE2
#وصف_ڪريو GL_COLOR_ATTACHMENT3              0x8CE3
#وصف_ڪريو GL_COLOR_ATTACHMENT4              0x8CE4
#وصف_ڪريو GL_COLOR_ATTACHMENT5              0x8CE5
#وصف_ڪريو GL_COLOR_ATTACHMENT6              0x8CE6
#وصف_ڪريو GL_COLOR_ATTACHMENT7              0x8CE7
#وصف_ڪريو GL_COLOR_ATTACHMENT8              0x8CE8
#وصف_ڪريو GL_COLOR_ATTACHMENT9              0x8CE9
#وصف_ڪريو GL_COLOR_ATTACHMENT10             0x8CEA
#وصف_ڪريو GL_COLOR_ATTACHMENT11             0x8CEB
#وصف_ڪريو GL_COLOR_ATTACHMENT12             0x8CEC
#وصف_ڪريو GL_COLOR_ATTACHMENT13             0x8CED
#وصف_ڪريو GL_COLOR_ATTACHMENT14             0x8CEE
#وصف_ڪريو GL_COLOR_ATTACHMENT15             0x8CEF
#وصف_ڪريو GL_COLOR_ATTACHMENT16             0x8CF0
#وصف_ڪريو GL_COLOR_ATTACHMENT17             0x8CF1
#وصف_ڪريو GL_COLOR_ATTACHMENT18             0x8CF2
#وصف_ڪريو GL_COLOR_ATTACHMENT19             0x8CF3
#وصف_ڪريو GL_COLOR_ATTACHMENT20             0x8CF4
#وصف_ڪريو GL_COLOR_ATTACHMENT21             0x8CF5
#وصف_ڪريو GL_COLOR_ATTACHMENT22             0x8CF6
#وصف_ڪريو GL_COLOR_ATTACHMENT23             0x8CF7
#وصف_ڪريو GL_COLOR_ATTACHMENT24             0x8CF8
#وصف_ڪريو GL_COLOR_ATTACHMENT25             0x8CF9
#وصف_ڪريو GL_COLOR_ATTACHMENT26             0x8CFA
#وصف_ڪريو GL_COLOR_ATTACHMENT27             0x8CFB
#وصف_ڪريو GL_COLOR_ATTACHMENT28             0x8CFC
#وصف_ڪريو GL_COLOR_ATTACHMENT29             0x8CFD
#وصف_ڪريو GL_COLOR_ATTACHMENT30             0x8CFE
#وصف_ڪريو GL_COLOR_ATTACHMENT31             0x8CFF
#وصف_ڪريو GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE 0x8D56
#وصف_ڪريو GL_MAX_SAMPLES                    0x8D57
#وصف_ڪريو GL_HALF_FLOAT                     0x140B
#وصف_ڪريو GL_MAP_READ_ٻٽو_انگ                   0x0001
#وصف_ڪريو GL_MAP_WRITE_ٻٽو_انگ                  0x0002
#وصف_ڪريو GL_MAP_INVALIDATE_RANGE_ٻٽو_انگ       0x0004
#وصف_ڪريو GL_MAP_INVALIDATE_بفر_ٻٽو_انگ      0x0008
#وصف_ڪريو GL_MAP_FLUSH_EXPLICIT_ٻٽو_انگ         0x0010
#وصف_ڪريو GL_MAP_UNSYNCHRONIZED_ٻٽو_انگ         0x0020
#وصف_ڪريو GL_RG                             0x8227
#وصف_ڪريو GL_RG_INTEGER                     0x8228
#وصف_ڪريو GL_R8                             0x8229
#وصف_ڪريو GL_RG8                            0x822B
#وصف_ڪريو GL_R16F                           0x822D
#وصف_ڪريو GL_R32F                           0x822E
#وصف_ڪريو GL_RG16F                          0x822F
#وصف_ڪريو GL_RG32F                          0x8230
#وصف_ڪريو GL_R8I                            0x8231
#وصف_ڪريو GL_R8UI                           0x8232
#وصف_ڪريو GL_R16I                           0x8233
#وصف_ڪريو GL_R16UI                          0x8234
#وصف_ڪريو GL_R32I                           0x8235
#وصف_ڪريو GL_R32UI                          0x8236
#وصف_ڪريو GL_RG8I                           0x8237
#وصف_ڪريو GL_RG8UI                          0x8238
#وصف_ڪريو GL_RG16I                          0x8239
#وصف_ڪريو GL_RG16UI                         0x823A
#وصف_ڪريو GL_RG32I                          0x823B
#وصف_ڪريو GL_RG32UI                         0x823C
#وصف_ڪريو GL_راس_ARRAY_BINDING           0x85B5
#وصف_ڪريو GL_R8_SNORM                       0x8F94
#وصف_ڪريو GL_RG8_SNORM                      0x8F95
#وصف_ڪريو GL_RGB8_SNORM                     0x8F96
#وصف_ڪريو GL_RGBA8_SNORM                    0x8F97
#وصف_ڪريو GL_SIGNED_NORMALIZED              0x8F9C
#وصف_ڪريو GL_PRIMITIVE_RESTART_FIXED_اشاريو  0x8D69
#وصف_ڪريو GL_COPY_READ_بفر               0x8F36
#وصف_ڪريو GL_COPY_WRITE_بفر              0x8F37
#وصف_ڪريو GL_COPY_READ_بفر_BINDING       0x8F36
#وصف_ڪريو GL_COPY_WRITE_بفر_BINDING      0x8F37
#وصف_ڪريو GL_هڪجهڙو_بفر                 0x8A11
#وصف_ڪريو GL_هڪجهڙو_بفر_BINDING         0x8A28
#وصف_ڪريو GL_هڪجهڙو_بفر_شروعات           0x8A29
#وصف_ڪريو GL_هڪجهڙو_بفر_سائيز            0x8A2A
#وصف_ڪريو GL_MAX_راس_هڪجهڙو_بلاڪون      0x8A2B
#وصف_ڪريو GL_MAX_FRAGMENT_هڪجهڙو_بلاڪون    0x8A2D
#وصف_ڪريو GL_MAX_COMBINED_هڪجهڙو_بلاڪون    0x8A2E
#وصف_ڪريو GL_MAX_هڪجهڙو_بفر_BINDINGS    0x8A2F
#وصف_ڪريو GL_MAX_هڪجهڙو_بلاڪ_سائيز         0x8A30
#وصف_ڪريو GL_MAX_COMBINED_راس_هڪجهڙو_COMPONENTS 0x8A31
#وصف_ڪريو GL_MAX_COMBINED_FRAGMENT_هڪجهڙو_COMPONENTS 0x8A33
#وصف_ڪريو GL_هڪجهڙو_بفر_وٿي_ALIGNMENT 0x8A34
#وصف_ڪريو GL_سرگرم_هڪجهڙو_بلاڪ_MAX_NAME_ڊيگهائي 0x8A35
#وصف_ڪريو GL_سرگرم_هڪجهڙو_بلاڪون          0x8A36
#وصف_ڪريو GL_هڪجهڙو_TYPE                   0x8A37
#وصف_ڪريو GL_هڪجهڙو_سائيز                   0x8A38
#وصف_ڪريو GL_هڪجهڙو_NAME_ڊيگهائي            0x8A39
#وصف_ڪريو GL_هڪجهڙو_بلاڪ_اشاريو            0x8A3A
#وصف_ڪريو GL_هڪجهڙو_وٿي                 0x8A3B
#وصف_ڪريو GL_هڪجهڙو_ARRAY_STRIDE           0x8A3C
#وصف_ڪريو GL_هڪجهڙو_ميٽرڪس_STRIDE          0x8A3D
#وصف_ڪريو GL_هڪجهڙو_IS_صف_MAJOR           0x8A3E
#وصف_ڪريو GL_هڪجهڙو_بلاڪ_BINDING          0x8A3F
#وصف_ڪريو GL_هڪجهڙو_بلاڪ_معلومات_سائيز        0x8A40
#وصف_ڪريو GL_هڪجهڙو_بلاڪ_NAME_ڊيگهائي      0x8A41
#وصف_ڪريو GL_هڪجهڙو_بلاڪ_سرگرم_UNIFORMS  0x8A42
#وصف_ڪريو GL_هڪجهڙو_بلاڪ_سرگرم_هڪجهڙو_INDICES 0x8A43
#وصف_ڪريو GL_هڪجهڙو_بلاڪ_REFERENCED_BY_راس_SHADER 0x8A44
#وصف_ڪريو GL_هڪجهڙو_بلاڪ_REFERENCED_BY_FRAGMENT_SHADER 0x8A46
#وصف_ڪريو GL_INVALID_اشاريو                  0xFFFFFFFFu
#وصف_ڪريو GL_MAX_راس_OUTPUT_COMPONENTS   0x9122
#وصف_ڪريو GL_MAX_FRAGMENT_داخلا_COMPONENTS  0x9125
#وصف_ڪريو GL_MAX_SERVER_WAIT_TIMEOUT        0x9111
#وصف_ڪريو GL_OBJECT_TYPE                    0x9112
#وصف_ڪريو GL_SYNC_CONDITION                 0x9113
#وصف_ڪريو GL_SYNC_حالت                    0x9114
#وصف_ڪريو GL_SYNC_FLAGS                     0x9115
#وصف_ڪريو GL_SYNC_FENCE                     0x9116
#وصف_ڪريو GL_SYNC_GPU_COMMANDS_COMPLETE     0x9117
#وصف_ڪريو GL_UNSIGNALED                     0x9118
#وصف_ڪريو GL_SIGNALED                       0x9119
#وصف_ڪريو GL_ALREADY_SIGNALED               0x911A
#وصف_ڪريو GL_TIMEOUT_EXPIRED                0x911B
#وصف_ڪريو GL_CONDITION_SATISFIED            0x911C
#وصف_ڪريو GL_WAIT_FAILED                    0x911D
#وصف_ڪريو GL_SYNC_FLUSH_COMMANDS_ٻٽو_انگ        0x00000001
#وصف_ڪريو GL_TIMEOUT_IGNORED                0xFFFFFFFFFFFFFFFFull
#وصف_ڪريو GL_راس_ATTRIB_ARRAY_ورهائيندڙ    0x88FE
#وصف_ڪريو GL_ANY_SAMPLES_PASSED             0x8C2F
#وصف_ڪريو GL_ANY_SAMPLES_PASSED_CONSERVATIVE 0x8D6A
#وصف_ڪريو GL_SAMPLER_BINDING                0x8919
#وصف_ڪريو GL_RGB10_A2UI                     0x906F
#وصف_ڪريو GL_TEXTURE_SWIZZLE_R              0x8E42
#وصف_ڪريو GL_TEXTURE_SWIZZLE_G              0x8E43
#وصف_ڪريو GL_TEXTURE_SWIZZLE_B              0x8E44
#وصف_ڪريو GL_TEXTURE_SWIZZLE_A              0x8E45
#وصف_ڪريو GL_GREEN                          0x1904
#وصف_ڪريو GL_BLUE                           0x1905
#وصف_ڪريو GL_INT_2_10_10_10_REV             0x8D9F
#وصف_ڪريو GL_TRANSFORM_FEEDBACK             0x8E22
#وصف_ڪريو GL_TRANSFORM_FEEDBACK_PAUSED      0x8E23
#وصف_ڪريو GL_TRANSFORM_FEEDBACK_سرگرم      0x8E24
#وصف_ڪريو GL_TRANSFORM_FEEDBACK_BINDING     0x8E25
#وصف_ڪريو GL_پروگرام_ٻٽو_RETRIEVABLE_HINT 0x8257
#وصف_ڪريو GL_پروگرام_ٻٽو_ڊيگهائي          0x8741
#وصف_ڪريو GL_انگ_پروگرام_ٻٽو_FORMATS     0x87FE
#وصف_ڪريو GL_پروگرام_ٻٽو_FORMATS         0x87FF
#وصف_ڪريو GL_COMPRESSED_R11_EAC             0x9270
#وصف_ڪريو GL_COMPRESSED_SIGNED_R11_EAC      0x9271
#وصف_ڪريو GL_COMPRESSED_RG11_EAC            0x9272
#وصف_ڪريو GL_COMPRESSED_SIGNED_RG11_EAC     0x9273
#وصف_ڪريو GL_COMPRESSED_RGB8_ETC2           0x9274
#وصف_ڪريو GL_COMPRESSED_SRGB8_ETC2          0x9275
#وصف_ڪريو GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9276
#وصف_ڪريو GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9277
#وصف_ڪريو GL_COMPRESSED_RGBA8_ETC2_EAC      0x9278
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC 0x9279
#وصف_ڪريو GL_TEXTURE_IMMUTABLE_FORMAT       0x912F
#وصف_ڪريو GL_MAX_ELEMENT_اشاريو              0x8D6B
#وصف_ڪريو GL_انگ_SAMPLE_COUNTS              0x9380
#وصف_ڪريو GL_TEXTURE_IMMUTABLE_سطحون       0x82DF
تعريفنوع فراغ (GL_APIENTRYP PFNGLREADBUFFERPROC) (GLenum src);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWRANGEELEMENTSPROC) (GLenum گهڻائي, GLuint شروعات, GLuint پڇاڙي, GLsizei ڳڻپ, GLenum type, ثابت فراغ *indices);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXIMAGE3DPROC) (GLenum هدف, GLint level, GLint internalformat, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLint border, GLenum format, GLenum type, ثابت فراغ *pixels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSUBIMAGE3DPROC) (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLenum format, GLenum type, ثابت فراغ *pixels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYTEXSUBIMAGE3DPROC) (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei ويڪر, GLsizei اوچائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOMPRESSEDTEXIMAGE3DPROC) (GLenum هدف, GLint level, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLint border, GLsizei image_سائيز, ثابت فراغ *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC) (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLenum format, GLsizei image_سائيز, ثابت فراغ *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENQUERIESPROC) (GLsizei n, GLuint *ids);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEQUERIESPROC) (GLsizei n, ثابت GLuint *ids);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISQUERYPROC) (GLuint id);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBEGINQUERYPROC) (GLenum هدف, GLuint id);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENDQUERYPROC) (GLenum هدف);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETQUERYIVPROC) (GLenum هدف, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETQUERYOBJECTUIVPROC) (GLuint id, GLenum pname, GLuint *params);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLUNMAPBUFFERPROC) (GLenum هدف);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETBUFFERPOINTERVPROC) (GLenum هدف, GLenum pname, فراغ **params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWBUFFERSPROC) (GLsizei n, ثابت GLenum *bufs);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX2X3FVPROC) (GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX3X2FVPROC) (GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX2X4FVPROC) (GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX4X2FVPROC) (GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX3X4FVPROC) (GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX4X3FVPROC) (GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLITFRAMEBUFFERPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield نقاب, GLenum filter);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC) (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURELAYERPROC) (GLenum هدف, GLenum attachment, GLuint texture, GLint level, GLint layer);
تعريفنوع فراغ *(GL_APIENTRYP PFNGLMAPBUFFERRANGEPROC) (GLenum هدف, GLintptr وٿي_2, GLsizeiptr ڊيگهائي, GLbitfield access);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEPROC) (GLenum هدف, GLintptr وٿي_2, GLsizeiptr ڊيگهائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDVERTEXARRAYPROC) (GLuint array);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEVERTEXARRAYSPROC) (GLsizei n, ثابت GLuint *arrays);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint *arrays);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISVERTEXARRAYPROC) (GLuint array);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTEGERI_VPROC) (GLenum هدف, GLuint اشاريو, GLint *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBEGINTRANSFORMFEEDBACKPROC) (GLenum primitive_گهڻائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENDTRANSFORMFEEDBACKPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDBUFFERRANGEPROC) (GLenum هدف, GLuint اشاريو, GLuint بفر_2, GLintptr وٿي_2, GLsizeiptr سائيز);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDBUFFERBASEPROC) (GLenum هدف, GLuint اشاريو, GLuint بفر_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTRANSFORMFEEDBACKVARYINGSPROC) (GLuint پروگرام, GLsizei ڳڻپ, ثابت GLchar *ثابت*varyings, GLenum بفر_گهڻائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTRANSFORMFEEDBACKVARYINGPROC) (GLuint پروگرام, GLuint اشاريو, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLsizei *سائيز, GLenum *type, GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBIPOINTERPROC) (GLuint اشاريو, GLint سائيز, GLenum type, GLsizei stride, ثابت فراغ *اشارو_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETVERTEXATTRIBIIVPROC) (GLuint اشاريو, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETVERTEXATTRIBIUIVPROC) (GLuint اشاريو, GLenum pname, GLuint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBI4IPROC) (GLuint اشاريو, GLint x, GLint y, GLint z, GLint w);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBI4UIPROC) (GLuint اشاريو, GLuint x, GLuint y, GLuint z, GLuint w);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBI4IVPROC) (GLuint اشاريو, ثابت GLint *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBI4UIVPROC) (GLuint اشاريو, ثابت GLuint *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETUNIFORMUIVPROC) (GLuint پروگرام, GLint location, GLuint *params);
تعريفنوع GLint (GL_APIENTRYP PFNGLGETFRAGDATALOCATIONPROC) (GLuint پروگرام, ثابت GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1UIPROC) (GLint location, GLuint v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2UIPROC) (GLint location, GLuint v0, GLuint v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3UIPROC) (GLint location, GLuint v0, GLuint v1, GLuint v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4UIPROC) (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1UIVPROC) (GLint location, GLsizei ڳڻپ, ثابت GLuint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2UIVPROC) (GLint location, GLsizei ڳڻپ, ثابت GLuint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3UIVPROC) (GLint location, GLsizei ڳڻپ, ثابت GLuint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4UIVPROC) (GLint location, GLsizei ڳڻپ, ثابت GLuint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARBUFFERIVPROC) (GLenum بفر_2, GLint drawbuffer, ثابت GLint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARBUFFERUIVPROC) (GLenum بفر_2, GLint drawbuffer, ثابت GLuint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARBUFFERFVPROC) (GLenum بفر_2, GLint drawbuffer, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARBUFFERFIPROC) (GLenum بفر_2, GLint drawbuffer, GLfloat اونهائي_2, GLint stencil);
تعريفنوع ثابت GLubyte *(GL_APIENTRYP PFNGLGETSTRINGIPROC) (GLenum name, GLuint اشاريو);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYBUFFERSUBDATAPROC) (GLenum read_هدف, GLenum write_هدف, GLintptr read_وٿي, GLintptr write_وٿي, GLsizeiptr سائيز);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETUNIFORMINDICESPROC) (GLuint پروگرام, GLsizei هڪجهڙو_ڳڻپ, ثابت GLchar *ثابت*هڪجهڙو_نالا, GLuint *هڪجهڙو_Indices);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETACTIVEUNIFORMSIVPROC) (GLuint پروگرام, GLsizei هڪجهڙو_ڳڻپ, ثابت GLuint *هڪجهڙو_Indices, GLenum pname, GLint *params);
تعريفنوع GLuint (GL_APIENTRYP PFNGLGETUNIFORMBLOCKINDEXPROC) (GLuint پروگرام, ثابت GLchar *هڪجهڙو_بلاڪ_Name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKIVPROC) (GLuint پروگرام, GLuint هڪجهڙو_بلاڪ_اشاريو, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC) (GLuint پروگرام, GLuint هڪجهڙو_بلاڪ_اشاريو, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLchar *هڪجهڙو_بلاڪ_Name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMBLOCKBINDINGPROC) (GLuint پروگرام, GLuint هڪجهڙو_بلاڪ_اشاريو, GLuint هڪجهڙو_بلاڪ_Binding);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDPROC) (GLenum گهڻائي, GLint پهريون, GLsizei ڳڻپ, GLsizei instancecount);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDPROC) (GLenum گهڻائي, GLsizei ڳڻپ, GLenum type, ثابت فراغ *indices, GLsizei instancecount);
تعريفنوع GLsync (GL_APIENTRYP PFNGLFENCESYNCPROC) (GLenum condition, GLbitfield flags);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISSYNCPROC) (GLsync sync);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETESYNCPROC) (GLsync sync);
تعريفنوع GLenum (GL_APIENTRYP PFNGLCLIENTWAITSYNCPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
تعريفنوع فراغ (GL_APIENTRYP PFNGLWAITSYNCPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTEGER64VPROC) (GLenum pname, GLint64 *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSYNCIVPROC) (GLsync sync, GLenum pname, GLsizei ڳڻپ, GLsizei *ڊيگهائي, GLint *قدرون);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTEGER64I_VPROC) (GLenum هدف, GLuint اشاريو, GLint64 *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETBUFFERPARAMETERI64VPROC) (GLenum هدف, GLenum pname, GLint64 *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENSAMPLERSPROC) (GLsizei ڳڻپ, GLuint *samplers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETESAMPLERSPROC) (GLsizei ڳڻپ, ثابت GLuint *samplers);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISSAMPLERPROC) (GLuint sampler);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDSAMPLERPROC) (GLuint unit, GLuint sampler);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIPROC) (GLuint sampler, GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, ثابت GLint *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERFPROC) (GLuint sampler, GLenum pname, GLfloat param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, ثابت GLfloat *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBDIVISORPROC) (GLuint اشاريو, GLuint ورهائيندڙ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDTRANSFORMFEEDBACKPROC) (GLenum هدف, GLuint id);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETETRANSFORMFEEDBACKSPROC) (GLsizei n, ثابت GLuint *ids);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENTRANSFORMFEEDBACKSPROC) (GLsizei n, GLuint *ids);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISTRANSFORMFEEDBACKPROC) (GLuint id);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPAUSETRANSFORMFEEDBACKPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRESUMETRANSFORMFEEDBACKPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMBINARYPROC) (GLuint پروگرام, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLenum *ٻٽو_Format, فراغ *ٻٽو);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMBINARYPROC) (GLuint پروگرام, GLenum ٻٽو_Format, ثابت فراغ *ٻٽو, GLsizei ڊيگهائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMPARAMETERIPROC) (GLuint پروگرام, GLenum pname, GLint قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLINVALIDATEFRAMEBUFFERPROC) (GLenum هدف, GLsizei انگ_Attachments, ثابت GLenum *attachments);
تعريفنوع فراغ (GL_APIENTRYP PFNGLINVALIDATESUBFRAMEBUFFERPROC) (GLenum هدف, GLsizei انگ_Attachments, ثابت GLenum *attachments, GLint x, GLint y, GLsizei ويڪر, GLsizei اوچائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE2DPROC) (GLenum هدف, GLsizei سطحون, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE3DPROC) (GLenum هدف, GLsizei سطحون, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTERNALFORMATIVPROC) (GLenum هدف, GLenum internalformat, GLenum pname, GLsizei ڳڻپ, GLint *params);
#إذا GL_GLES_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Read_بفر (GLenum src);
GL_APICALL فراغ GL_APIENTRY glDrawRangeElements (GLenum گهڻائي, GLuint شروعات, GLuint پڇاڙي, GLsizei ڳڻپ, GLenum type, ثابت فراغ *indices);
GL_APICALL فراغ GL_APIENTRY glTexImage3D (GLenum هدف, GLint level, GLint internalformat, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLint border, GLenum format, GLenum type, ثابت فراغ *pixels);
GL_APICALL فراغ GL_APIENTRY glTexSubImage3D (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLenum format, GLenum type, ثابت فراغ *pixels);
GL_APICALL فراغ GL_APIENTRY glCopyTexSubImage3D (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei ويڪر, GLsizei اوچائي);
GL_APICALL فراغ GL_APIENTRY glCompressedTexImage3D (GLenum هدف, GLint level, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLint border, GLsizei image_سائيز, ثابت فراغ *معلومات);
GL_APICALL فراغ GL_APIENTRY glCompressedTexSubImage3D (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLenum format, GLsizei image_سائيز, ثابت فراغ *معلومات);
GL_APICALL فراغ GL_APIENTRY glGenQueries (GLsizei n, GLuint *ids);
GL_APICALL فراغ GL_APIENTRY glDeleteQueries (GLsizei n, ثابت GLuint *ids);
GL_APICALL GLboolean GL_APIENTRY glIsQuery (GLuint id);
GL_APICALL فراغ GL_APIENTRY glBeginQuery (GLenum هدف, GLuint id);
GL_APICALL فراغ GL_APIENTRY gl_پڇاڙي_Query (GLenum هدف);
GL_APICALL فراغ GL_APIENTRY glGetQueryiv (GLenum هدف, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetQueryObjectuiv (GLuint id, GLenum pname, GLuint *params);
GL_APICALL GLboolean GL_APIENTRY gl_Unmap_بفر (GLenum هدف);
GL_APICALL فراغ GL_APIENTRY gl_Get_بفر_Pointerv (GLenum هدف, GLenum pname, فراغ **params);
GL_APICALL فراغ GL_APIENTRY glDrawBuffers (GLsizei n, ثابت GLenum *bufs);
GL_APICALL فراغ GL_APIENTRY gl_هڪجهڙو_Matrix2x3fv (GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_هڪجهڙو_Matrix3x2fv (GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_هڪجهڙو_Matrix2x4fv (GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_هڪجهڙو_Matrix4x2fv (GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_هڪجهڙو_Matrix3x4fv (GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_هڪجهڙو_Matrix4x3fv (GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY glBlitFramebuffer (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield نقاب, GLenum filter);
GL_APICALL فراغ GL_APIENTRY glRenderbufferStorageMultisample (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
GL_APICALL فراغ GL_APIENTRY glFramebufferTextureLayer (GLenum هدف, GLenum attachment, GLuint texture, GLint level, GLint layer);
GL_APICALL فراغ *GL_APIENTRY gl_Map_بفر_Range (GLenum هدف, GLintptr وٿي_2, GLsizeiptr ڊيگهائي, GLbitfield access);
GL_APICALL فراغ GL_APIENTRY gl_Flush_Mapped_بفر_Range (GLenum هدف, GLintptr وٿي_2, GLsizeiptr ڊيگهائي);
GL_APICALL فراغ GL_APIENTRY gl_Bind_راس_Array (GLuint array);
GL_APICALL فراغ GL_APIENTRY gl_Delete_راس_Arrays (GLsizei n, ثابت GLuint *arrays);
GL_APICALL فراغ GL_APIENTRY gl_Gen_راس_Arrays (GLsizei n, GLuint *arrays);
GL_APICALL GLboolean GL_APIENTRY gl_Is_راس_Array (GLuint array);
GL_APICALL فراغ GL_APIENTRY glGetIntegeri_v (GLenum هدف, GLuint اشاريو, GLint *معلومات);
GL_APICALL فراغ GL_APIENTRY glBeginTransformFeedback (GLenum primitive_گهڻائي);
GL_APICALL فراغ GL_APIENTRY gl_پڇاڙي_Transform_Feedback (فراغ);
GL_APICALL فراغ GL_APIENTRY gl_Bind_بفر_Range (GLenum هدف, GLuint اشاريو, GLuint بفر_2, GLintptr وٿي_2, GLsizeiptr سائيز);
GL_APICALL فراغ GL_APIENTRY gl_Bind_بفر_بنياد (GLenum هدف, GLuint اشاريو, GLuint بفر_2);
GL_APICALL فراغ GL_APIENTRY glTransformFeedbackVaryings (GLuint پروگرام, GLsizei ڳڻپ, ثابت GLchar *ثابت*varyings, GLenum بفر_گهڻائي);
GL_APICALL فراغ GL_APIENTRY glGetTransformFeedbackVarying (GLuint پروگرام, GLuint اشاريو, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLsizei *سائيز, GLenum *type, GLchar *name);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib_IPointer (GLuint اشاريو, GLint سائيز, GLenum type, GLsizei stride, ثابت فراغ *اشارو_2);
GL_APICALL فراغ GL_APIENTRY gl_Get_راس_Attrib_Iiv (GLuint اشاريو, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY gl_Get_راس_Attrib_Iuiv (GLuint اشاريو, GLenum pname, GLuint *params);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib_I4i (GLuint اشاريو, GLint x, GLint y, GLint z, GLint w);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib_I4ui (GLuint اشاريو, GLuint x, GLuint y, GLuint z, GLuint w);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib_I4iv (GLuint اشاريو, ثابت GLint *v);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib_I4uiv (GLuint اشاريو, ثابت GLuint *v);
GL_APICALL فراغ GL_APIENTRY glGetUniformuiv (GLuint پروگرام, GLint location, GLuint *params);
GL_APICALL GLint GL_APIENTRY gl_Get_Frag_معلومات_Location (GLuint پروگرام, ثابت GLchar *name);
GL_APICALL فراغ GL_APIENTRY glUniform1ui (GLint location, GLuint v0);
GL_APICALL فراغ GL_APIENTRY glUniform2ui (GLint location, GLuint v0, GLuint v1);
GL_APICALL فراغ GL_APIENTRY glUniform3ui (GLint location, GLuint v0, GLuint v1, GLuint v2);
GL_APICALL فراغ GL_APIENTRY glUniform4ui (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
GL_APICALL فراغ GL_APIENTRY glUniform1uiv (GLint location, GLsizei ڳڻپ, ثابت GLuint *قدر);
GL_APICALL فراغ GL_APIENTRY glUniform2uiv (GLint location, GLsizei ڳڻپ, ثابت GLuint *قدر);
GL_APICALL فراغ GL_APIENTRY glUniform3uiv (GLint location, GLsizei ڳڻپ, ثابت GLuint *قدر);
GL_APICALL فراغ GL_APIENTRY glUniform4uiv (GLint location, GLsizei ڳڻپ, ثابت GLuint *قدر);
GL_APICALL فراغ GL_APIENTRY glClearBufferiv (GLenum بفر_2, GLint drawbuffer, ثابت GLint *قدر);
GL_APICALL فراغ GL_APIENTRY glClearBufferuiv (GLenum بفر_2, GLint drawbuffer, ثابت GLuint *قدر);
GL_APICALL فراغ GL_APIENTRY glClearBufferfv (GLenum بفر_2, GLint drawbuffer, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY glClearBufferfi (GLenum بفر_2, GLint drawbuffer, GLfloat اونهائي_2, GLint stencil);
GL_APICALL ثابت GLubyte *GL_APIENTRY glGetStringi (GLenum name, GLuint اشاريو);
GL_APICALL فراغ GL_APIENTRY gl_Copy_بفر_Sub_معلومات (GLenum read_هدف, GLenum write_هدف, GLintptr read_وٿي, GLintptr write_وٿي, GLsizeiptr سائيز);
GL_APICALL فراغ GL_APIENTRY gl_Get_هڪجهڙو_Indices (GLuint پروگرام, GLsizei هڪجهڙو_ڳڻپ, ثابت GLchar *ثابت*هڪجهڙو_نالا, GLuint *هڪجهڙو_Indices);
GL_APICALL فراغ GL_APIENTRY gl_Get_سرگرم_Uniformsiv (GLuint پروگرام, GLsizei هڪجهڙو_ڳڻپ, ثابت GLuint *هڪجهڙو_Indices, GLenum pname, GLint *params);
GL_APICALL GLuint GL_APIENTRY gl_Get_هڪجهڙو_بلاڪ_اشاريو (GLuint پروگرام, ثابت GLchar *هڪجهڙو_بلاڪ_Name);
GL_APICALL فراغ GL_APIENTRY gl_Get_سرگرم_هڪجهڙو_Blockiv (GLuint پروگرام, GLuint هڪجهڙو_بلاڪ_اشاريو, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY gl_Get_سرگرم_هڪجهڙو_بلاڪ_Name (GLuint پروگرام, GLuint هڪجهڙو_بلاڪ_اشاريو, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLchar *هڪجهڙو_بلاڪ_Name);
GL_APICALL فراغ GL_APIENTRY gl_هڪجهڙو_بلاڪ_Binding (GLuint پروگرام, GLuint هڪجهڙو_بلاڪ_اشاريو, GLuint هڪجهڙو_بلاڪ_Binding);
GL_APICALL فراغ GL_APIENTRY glDrawArraysInstanced (GLenum گهڻائي, GLint پهريون, GLsizei ڳڻپ, GLsizei instancecount);
GL_APICALL فراغ GL_APIENTRY glDrawElementsInstanced (GLenum گهڻائي, GLsizei ڳڻپ, GLenum type, ثابت فراغ *indices, GLsizei instancecount);
GL_APICALL GLsync GL_APIENTRY glFenceSync (GLenum condition, GLbitfield flags);
GL_APICALL GLboolean GL_APIENTRY glIsSync (GLsync sync);
GL_APICALL فراغ GL_APIENTRY glDeleteSync (GLsync sync);
GL_APICALL GLenum GL_APIENTRY glClientWaitSync (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_APICALL فراغ GL_APIENTRY glWaitSync (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_APICALL فراغ GL_APIENTRY glGetInteger64v (GLenum pname, GLint64 *معلومات);
GL_APICALL فراغ GL_APIENTRY glGetSynciv (GLsync sync, GLenum pname, GLsizei ڳڻپ, GLsizei *ڊيگهائي, GLint *قدرون);
GL_APICALL فراغ GL_APIENTRY glGetInteger64i_v (GLenum هدف, GLuint اشاريو, GLint64 *معلومات);
GL_APICALL فراغ GL_APIENTRY gl_Get_بفر_Parameteri64v (GLenum هدف, GLenum pname, GLint64 *params);
GL_APICALL فراغ GL_APIENTRY glGenSamplers (GLsizei ڳڻپ, GLuint *samplers);
GL_APICALL فراغ GL_APIENTRY glDeleteSamplers (GLsizei ڳڻپ, ثابت GLuint *samplers);
GL_APICALL GLboolean GL_APIENTRY glIsSampler (GLuint sampler);
GL_APICALL فراغ GL_APIENTRY glBindSampler (GLuint unit, GLuint sampler);
GL_APICALL فراغ GL_APIENTRY glSamplerParameteri (GLuint sampler, GLenum pname, GLint param);
GL_APICALL فراغ GL_APIENTRY glSamplerParameteriv (GLuint sampler, GLenum pname, ثابت GLint *param);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterf (GLuint sampler, GLenum pname, GLfloat param);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterfv (GLuint sampler, GLenum pname, ثابت GLfloat *param);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameteriv (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameterfv (GLuint sampler, GLenum pname, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib_ورهائيندڙ (GLuint اشاريو, GLuint ورهائيندڙ);
GL_APICALL فراغ GL_APIENTRY glBindTransformFeedback (GLenum هدف, GLuint id);
GL_APICALL فراغ GL_APIENTRY glDeleteTransformFeedbacks (GLsizei n, ثابت GLuint *ids);
GL_APICALL فراغ GL_APIENTRY glGenTransformFeedbacks (GLsizei n, GLuint *ids);
GL_APICALL GLboolean GL_APIENTRY glIsTransformFeedback (GLuint id);
GL_APICALL فراغ GL_APIENTRY glPauseTransformFeedback (فراغ);
GL_APICALL فراغ GL_APIENTRY glResumeTransformFeedback (فراغ);
GL_APICALL فراغ GL_APIENTRY gl_Get_پروگرام_ٻٽو (GLuint پروگرام, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLenum *ٻٽو_Format, فراغ *ٻٽو);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_ٻٽو (GLuint پروگرام, GLenum ٻٽو_Format, ثابت فراغ *ٻٽو, GLsizei ڊيگهائي);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Parameteri (GLuint پروگرام, GLenum pname, GLint قدر);
GL_APICALL فراغ GL_APIENTRY glInvalidateFramebuffer (GLenum هدف, GLsizei انگ_Attachments, ثابت GLenum *attachments);
GL_APICALL فراغ GL_APIENTRY glInvalidateSubFramebuffer (GLenum هدف, GLsizei انگ_Attachments, ثابت GLenum *attachments, GLint x, GLint y, GLsizei ويڪر, GLsizei اوچائي);
GL_APICALL فراغ GL_APIENTRY glTexStorage2D (GLenum هدف, GLsizei سطحون, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي);
GL_APICALL فراغ GL_APIENTRY glTexStorage3D (GLenum هدف, GLsizei سطحون, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2);
GL_APICALL فراغ GL_APIENTRY glGetInternalformativ (GLenum هدف, GLenum internalformat, GLenum pname, GLsizei ڳڻپ, GLint *params);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_ES_VERSION_3_0 */

#جيڪڏهن_وصف_نه_ٿيل GL_ES_نسخو_3_1
#وصف_ڪريو GL_ES_نسخو_3_1 1
#وصف_ڪريو GL_COMPUTE_SHADER                 0x91B9
#وصف_ڪريو GL_MAX_COMPUTE_هڪجهڙو_بلاڪون     0x91BB
#وصف_ڪريو GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS 0x91BC
#وصف_ڪريو GL_MAX_COMPUTE_IMAGE_UNIFORMS     0x91BD
#وصف_ڪريو GL_MAX_COMPUTE_SHARED_يادگيري_سائيز 0x8262
#وصف_ڪريو GL_MAX_COMPUTE_هڪجهڙو_COMPONENTS 0x8263
#وصف_ڪريو GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS 0x8264
#وصف_ڪريو GL_MAX_COMPUTE_ATOMIC_COUNTERS    0x8265
#وصف_ڪريو GL_MAX_COMBINED_COMPUTE_هڪجهڙو_COMPONENTS 0x8266
#وصف_ڪريو GL_MAX_COMPUTE_WORK_گروهه_INVOCATIONS 0x90EB
#وصف_ڪريو GL_MAX_COMPUTE_WORK_گروهه_ڳڻپ   0x91BE
#وصف_ڪريو GL_MAX_COMPUTE_WORK_گروهه_سائيز    0x91BF
#وصف_ڪريو GL_COMPUTE_WORK_گروهه_سائيز        0x8267
#وصف_ڪريو GL_DISPATCH_اڻسڌو_بفر       0x90EE
#وصف_ڪريو GL_DISPATCH_اڻسڌو_بفر_BINDING 0x90EF
#وصف_ڪريو GL_COMPUTE_SHADER_ٻٽو_انگ             0x00000020
#وصف_ڪريو GL_DRAW_اڻسڌو_بفر           0x8F3F
#وصف_ڪريو GL_DRAW_اڻسڌو_بفر_BINDING   0x8F43
#وصف_ڪريو GL_MAX_هڪجهڙو_LOCATIONS          0x826E
#وصف_ڪريو GL_FRAMEBUFFER_DEFAULT_ويڪر      0x9310
#وصف_ڪريو GL_FRAMEBUFFER_DEFAULT_اوچائي     0x9311
#وصف_ڪريو GL_FRAMEBUFFER_DEFAULT_SAMPLES    0x9313
#وصف_ڪريو GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS 0x9314
#وصف_ڪريو GL_MAX_FRAMEBUFFER_ويڪر          0x9315
#وصف_ڪريو GL_MAX_FRAMEBUFFER_اوچائي         0x9316
#وصف_ڪريو GL_MAX_FRAMEBUFFER_SAMPLES        0x9318
#وصف_ڪريو GL_هڪجهڙو                        0x92E1
#وصف_ڪريو GL_هڪجهڙو_بلاڪ                  0x92E2
#وصف_ڪريو GL_پروگرام_داخلا                  0x92E3
#وصف_ڪريو GL_پروگرام_OUTPUT                 0x92E4
#وصف_ڪريو GL_بفر_VARIABLE                0x92E5
#وصف_ڪريو GL_SHADER_STORAGE_بلاڪ           0x92E6
#وصف_ڪريو GL_ATOMIC_COUNTER_بفر          0x92C0
#وصف_ڪريو GL_TRANSFORM_FEEDBACK_VARYING     0x92F4
#وصف_ڪريو GL_سرگرم_RESOURCES               0x92F5
#وصف_ڪريو GL_MAX_NAME_ڊيگهائي                0x92F6
#وصف_ڪريو GL_MAX_انگ_سرگرم_VARIABLES       0x92F7
#وصف_ڪريو GL_NAME_ڊيگهائي                    0x92F9
#وصف_ڪريو GL_TYPE                           0x92FA
#وصف_ڪريو GL_ARRAY_سائيز                     0x92FB
#وصف_ڪريو GL_وٿي                         0x92FC
#وصف_ڪريو GL_بلاڪ_اشاريو                    0x92FD
#وصف_ڪريو GL_ARRAY_STRIDE                   0x92FE
#وصف_ڪريو GL_ميٽرڪس_STRIDE                  0x92FF
#وصف_ڪريو GL_IS_صف_MAJOR                   0x9300
#وصف_ڪريو GL_ATOMIC_COUNTER_بفر_اشاريو    0x9301
#وصف_ڪريو GL_بفر_BINDING                 0x9302
#وصف_ڪريو GL_بفر_معلومات_سائيز               0x9303
#وصف_ڪريو GL_انگ_سرگرم_VARIABLES           0x9304
#وصف_ڪريو GL_سرگرم_VARIABLES               0x9305
#وصف_ڪريو GL_REFERENCED_BY_راس_SHADER    0x9306
#وصف_ڪريو GL_REFERENCED_BY_FRAGMENT_SHADER  0x930A
#وصف_ڪريو GL_REFERENCED_BY_COMPUTE_SHADER   0x930B
#وصف_ڪريو GL_چوٽي_LEVEL_ARRAY_سائيز           0x930C
#وصف_ڪريو GL_چوٽي_LEVEL_ARRAY_STRIDE         0x930D
#وصف_ڪريو GL_LOCATION                       0x930E
#وصف_ڪريو GL_راس_SHADER_ٻٽو_انگ              0x00000001
#وصف_ڪريو GL_FRAGMENT_SHADER_ٻٽو_انگ            0x00000002
#وصف_ڪريو GL_ALL_SHADER_بٽ                0xFFFFFFFF
#وصف_ڪريو GL_پروگرام_SEPARABLE              0x8258
#وصف_ڪريو GL_سرگرم_پروگرام                 0x8259
#وصف_ڪريو GL_پروگرام_PIPELINE_BINDING       0x825A
#وصف_ڪريو GL_ATOMIC_COUNTER_بفر_BINDING  0x92C1
#وصف_ڪريو GL_ATOMIC_COUNTER_بفر_شروعات    0x92C2
#وصف_ڪريو GL_ATOMIC_COUNTER_بفر_سائيز     0x92C3
#وصف_ڪريو GL_MAX_راس_ATOMIC_COUNTER_BUFFERS 0x92CC
#وصف_ڪريو GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS 0x92D0
#وصف_ڪريو GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS 0x92D1
#وصف_ڪريو GL_MAX_راس_ATOMIC_COUNTERS     0x92D2
#وصف_ڪريو GL_MAX_FRAGMENT_ATOMIC_COUNTERS   0x92D6
#وصف_ڪريو GL_MAX_COMBINED_ATOMIC_COUNTERS   0x92D7
#وصف_ڪريو GL_MAX_ATOMIC_COUNTER_بفر_سائيز 0x92D8
#وصف_ڪريو GL_MAX_ATOMIC_COUNTER_بفر_BINDINGS 0x92DC
#وصف_ڪريو GL_سرگرم_ATOMIC_COUNTER_BUFFERS  0x92D9
#وصف_ڪريو GL_UNSIGNED_INT_ATOMIC_COUNTER    0x92DB
#وصف_ڪريو GL_MAX_IMAGE_UNITS                0x8F38
#وصف_ڪريو GL_MAX_راس_IMAGE_UNIFORMS      0x90CA
#وصف_ڪريو GL_MAX_FRAGMENT_IMAGE_UNIFORMS    0x90CE
#وصف_ڪريو GL_MAX_COMBINED_IMAGE_UNIFORMS    0x90CF
#وصف_ڪريو GL_IMAGE_BINDING_NAME             0x8F3A
#وصف_ڪريو GL_IMAGE_BINDING_LEVEL            0x8F3B
#وصف_ڪريو GL_IMAGE_BINDING_LAYERED          0x8F3C
#وصف_ڪريو GL_IMAGE_BINDING_LAYER            0x8F3D
#وصف_ڪريو GL_IMAGE_BINDING_ACCESS           0x8F3E
#وصف_ڪريو GL_IMAGE_BINDING_FORMAT           0x906E
#وصف_ڪريو GL_راس_ATTRIB_ARRAY_BARRIER_ٻٽو_انگ 0x00000001
#وصف_ڪريو GL_ELEMENT_ARRAY_BARRIER_ٻٽو_انگ      0x00000002
#وصف_ڪريو GL_هڪجهڙو_BARRIER_ٻٽو_انگ            0x00000004
#وصف_ڪريو GL_TEXTURE_FETCH_BARRIER_ٻٽو_انگ      0x00000008
#وصف_ڪريو GL_SHADER_IMAGE_ACCESS_BARRIER_ٻٽو_انگ 0x00000020
#وصف_ڪريو GL_COMMAND_BARRIER_ٻٽو_انگ            0x00000040
#وصف_ڪريو GL_PIXEL_بفر_BARRIER_ٻٽو_انگ       0x00000080
#وصف_ڪريو GL_TEXTURE_UPDATE_BARRIER_ٻٽو_انگ     0x00000100
#وصف_ڪريو GL_بفر_UPDATE_BARRIER_ٻٽو_انگ      0x00000200
#وصف_ڪريو GL_FRAMEBUFFER_BARRIER_ٻٽو_انگ        0x00000400
#وصف_ڪريو GL_TRANSFORM_FEEDBACK_BARRIER_ٻٽو_انگ 0x00000800
#وصف_ڪريو GL_ATOMIC_COUNTER_BARRIER_ٻٽو_انگ     0x00001000
#وصف_ڪريو GL_ALL_BARRIER_بٽ               0xFFFFFFFF
#وصف_ڪريو GL_IMAGE_2D                       0x904D
#وصف_ڪريو GL_IMAGE_3D                       0x904E
#وصف_ڪريو GL_IMAGE_CUBE                     0x9050
#وصف_ڪريو GL_IMAGE_2D_ARRAY                 0x9053
#وصف_ڪريو GL_INT_IMAGE_2D                   0x9058
#وصف_ڪريو GL_INT_IMAGE_3D                   0x9059
#وصف_ڪريو GL_INT_IMAGE_CUBE                 0x905B
#وصف_ڪريو GL_INT_IMAGE_2D_ARRAY             0x905E
#وصف_ڪريو GL_UNSIGNED_INT_IMAGE_2D          0x9063
#وصف_ڪريو GL_UNSIGNED_INT_IMAGE_3D          0x9064
#وصف_ڪريو GL_UNSIGNED_INT_IMAGE_CUBE        0x9066
#وصف_ڪريو GL_UNSIGNED_INT_IMAGE_2D_ARRAY    0x9069
#وصف_ڪريو GL_IMAGE_FORMAT_COMPATIBILITY_TYPE 0x90C7
#وصف_ڪريو GL_IMAGE_FORMAT_COMPATIBILITY_BY_سائيز 0x90C8
#وصف_ڪريو GL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS 0x90C9
#وصف_ڪريو GL_READ_ONLY                      0x88B8
#وصف_ڪريو GL_WRITE_ONLY                     0x88B9
#وصف_ڪريو GL_READ_WRITE                     0x88BA
#وصف_ڪريو GL_SHADER_STORAGE_بفر          0x90D2
#وصف_ڪريو GL_SHADER_STORAGE_بفر_BINDING  0x90D3
#وصف_ڪريو GL_SHADER_STORAGE_بفر_شروعات    0x90D4
#وصف_ڪريو GL_SHADER_STORAGE_بفر_سائيز     0x90D5
#وصف_ڪريو GL_MAX_راس_SHADER_STORAGE_بلاڪون 0x90D6
#وصف_ڪريو GL_MAX_FRAGMENT_SHADER_STORAGE_بلاڪون 0x90DA
#وصف_ڪريو GL_MAX_COMPUTE_SHADER_STORAGE_بلاڪون 0x90DB
#وصف_ڪريو GL_MAX_COMBINED_SHADER_STORAGE_بلاڪون 0x90DC
#وصف_ڪريو GL_MAX_SHADER_STORAGE_بفر_BINDINGS 0x90DD
#وصف_ڪريو GL_MAX_SHADER_STORAGE_بلاڪ_سائيز  0x90DE
#وصف_ڪريو GL_SHADER_STORAGE_بفر_وٿي_ALIGNMENT 0x90DF
#وصف_ڪريو GL_SHADER_STORAGE_BARRIER_ٻٽو_انگ     0x00002000
#وصف_ڪريو GL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES 0x8F39
#وصف_ڪريو GL_اونهائي_STENCIL_TEXTURE_گهڻائي     0x90EA
#وصف_ڪريو GL_STENCIL_اشاريو                  0x1901
#وصف_ڪريو GL_MIN_پروگرام_TEXTURE_GATHER_وٿي 0x8E5E
#وصف_ڪريو GL_MAX_پروگرام_TEXTURE_GATHER_وٿي 0x8E5F
#وصف_ڪريو GL_SAMPLE_POSITION                0x8E50
#وصف_ڪريو GL_SAMPLE_نقاب                    0x8E51
#وصف_ڪريو GL_SAMPLE_نقاب_قدر              0x8E52
#وصف_ڪريو GL_TEXTURE_2D_MULTISAMPLE         0x9100
#وصف_ڪريو GL_MAX_SAMPLE_نقاب_لفظ          0x8E59
#وصف_ڪريو GL_MAX_COLOR_TEXTURE_SAMPLES      0x910E
#وصف_ڪريو GL_MAX_اونهائي_TEXTURE_SAMPLES      0x910F
#وصف_ڪريو GL_MAX_INTEGER_SAMPLES            0x9110
#وصف_ڪريو GL_TEXTURE_BINDING_2D_MULTISAMPLE 0x9104
#وصف_ڪريو GL_TEXTURE_SAMPLES                0x9106
#وصف_ڪريو GL_TEXTURE_FIXED_SAMPLE_LOCATIONS 0x9107
#وصف_ڪريو GL_TEXTURE_ويڪر                  0x1000
#وصف_ڪريو GL_TEXTURE_اوچائي                 0x1001
#وصف_ڪريو GL_TEXTURE_اونهائي                  0x8071
#وصف_ڪريو GL_TEXTURE_اندروني_FORMAT        0x1003
#وصف_ڪريو GL_TEXTURE_RED_سائيز               0x805C
#وصف_ڪريو GL_TEXTURE_GREEN_سائيز             0x805D
#وصف_ڪريو GL_TEXTURE_BLUE_سائيز              0x805E
#وصف_ڪريو GL_TEXTURE_ALPHA_سائيز             0x805F
#وصف_ڪريو GL_TEXTURE_اونهائي_سائيز             0x884A
#وصف_ڪريو GL_TEXTURE_STENCIL_سائيز           0x88F1
#وصف_ڪريو GL_TEXTURE_SHARED_سائيز            0x8C3F
#وصف_ڪريو GL_TEXTURE_RED_TYPE               0x8C10
#وصف_ڪريو GL_TEXTURE_GREEN_TYPE             0x8C11
#وصف_ڪريو GL_TEXTURE_BLUE_TYPE              0x8C12
#وصف_ڪريو GL_TEXTURE_ALPHA_TYPE             0x8C13
#وصف_ڪريو GL_TEXTURE_اونهائي_TYPE             0x8C16
#وصف_ڪريو GL_TEXTURE_COMPRESSED             0x86A1
#وصف_ڪريو GL_SAMPLER_2D_MULTISAMPLE         0x9108
#وصف_ڪريو GL_INT_SAMPLER_2D_MULTISAMPLE     0x9109
#وصف_ڪريو GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE 0x910A
#وصف_ڪريو GL_راس_ATTRIB_BINDING          0x82D4
#وصف_ڪريو GL_راس_ATTRIB_RELATIVE_وٿي  0x82D5
#وصف_ڪريو GL_راس_BINDING_ورهائيندڙ         0x82D6
#وصف_ڪريو GL_راس_BINDING_وٿي          0x82D7
#وصف_ڪريو GL_راس_BINDING_STRIDE          0x82D8
#وصف_ڪريو GL_راس_BINDING_بفر          0x8F4F
#وصف_ڪريو GL_MAX_راس_ATTRIB_RELATIVE_وٿي 0x82D9
#وصف_ڪريو GL_MAX_راس_ATTRIB_BINDINGS     0x82DA
#وصف_ڪريو GL_MAX_راس_ATTRIB_STRIDE       0x82E5
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISPATCHCOMPUTEPROC) (GLuint انگ_groups_x, GLuint انگ_groups_y, GLuint انگ_groups_z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISPATCHCOMPUTEINDIRECTPROC) (GLintptr اڻسڌو);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWARRAYSINDIRECTPROC) (GLenum گهڻائي, ثابت فراغ *اڻسڌو);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINDIRECTPROC) (GLenum گهڻائي, GLenum type, ثابت فراغ *اڻسڌو);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERPARAMETERIPROC) (GLenum هدف, GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFRAMEBUFFERPARAMETERIVPROC) (GLenum هدف, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMINTERFACEIVPROC) (GLuint پروگرام, GLenum پروگرام_Interface, GLenum pname, GLint *params);
تعريفنوع GLuint (GL_APIENTRYP PFNGLGETPROGRAMRESOURCEINDEXPROC) (GLuint پروگرام, GLenum پروگرام_Interface, ثابت GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMRESOURCENAMEPROC) (GLuint پروگرام, GLenum پروگرام_Interface, GLuint اشاريو, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMRESOURCEIVPROC) (GLuint پروگرام, GLenum پروگرام_Interface, GLuint اشاريو, GLsizei prop_ڳڻپ, ثابت GLenum *props, GLsizei ڳڻپ, GLsizei *ڊيگهائي, GLint *params);
تعريفنوع GLint (GL_APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONPROC) (GLuint پروگرام, GLenum پروگرام_Interface, ثابت GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUSEPROGRAMSTAGESPROC) (GLuint pipeline, GLbitfield stages, GLuint پروگرام);
تعريفنوع فراغ (GL_APIENTRYP PFNGLACTIVESHADERPROGRAMPROC) (GLuint pipeline, GLuint پروگرام);
تعريفنوع GLuint (GL_APIENTRYP PFNGLCREATESHADERPROGRAMVPROC) (GLenum type, GLsizei ڳڻپ, ثابت GLchar *ثابت*لڙيون);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDPROGRAMPIPELINEPROC) (GLuint pipeline);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEPROGRAMPIPELINESPROC) (GLsizei n, ثابت GLuint *pipelines);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENPROGRAMPIPELINESPROC) (GLsizei n, GLuint *pipelines);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISPROGRAMPIPELINEPROC) (GLuint pipeline);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMPIPELINEIVPROC) (GLuint pipeline, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1IPROC) (GLuint پروگرام, GLint location, GLint v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2IPROC) (GLuint پروگرام, GLint location, GLint v0, GLint v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3IPROC) (GLuint پروگرام, GLint location, GLint v0, GLint v1, GLint v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4IPROC) (GLuint پروگرام, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UIPROC) (GLuint پروگرام, GLint location, GLuint v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UIPROC) (GLuint پروگرام, GLint location, GLuint v0, GLuint v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UIPROC) (GLuint پروگرام, GLint location, GLuint v0, GLuint v1, GLuint v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UIPROC) (GLuint پروگرام, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1FPROC) (GLuint پروگرام, GLint location, GLfloat v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2FPROC) (GLuint پروگرام, GLint location, GLfloat v0, GLfloat v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3FPROC) (GLuint پروگرام, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4FPROC) (GLuint پروگرام, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1IVPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2IVPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3IVPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4IVPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UIVPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLuint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UIVPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLuint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UIVPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLuint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UIVPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLuint *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1FVPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2FVPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3FVPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4FVPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2FVPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3FVPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4FVPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC) (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVALIDATEPROGRAMPIPELINEPROC) (GLuint pipeline);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMPIPELINEINFOLOGPROC) (GLuint pipeline, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLchar *infoLog);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDIMAGETEXTUREPROC) (GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETBOOLEANI_VPROC) (GLenum هدف, GLuint اشاريو, GLboolean *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMEMORYBARRIERPROC) (GLbitfield barriers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMEMORYBARRIERBYREGIONPROC) (GLbitfield barriers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE2DMULTISAMPLEPROC) (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي, GLboolean fixedsamplelocations);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETMULTISAMPLEFVPROC) (GLenum pname, GLuint اشاريو, GLfloat *val);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLEMASKIPROC) (GLuint نقاب_عدد, GLbitfield نقاب);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXLEVELPARAMETERIVPROC) (GLenum هدف, GLint level, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXLEVELPARAMETERFVPROC) (GLenum هدف, GLint level, GLenum pname, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDVERTEXBUFFERPROC) (GLuint bindingindex, GLuint بفر_2, GLintptr وٿي_2, GLsizei stride);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBFORMATPROC) (GLuint attribindex, GLint سائيز, GLenum type, GLboolean normalized, GLuint relativeoffset);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBIFORMATPROC) (GLuint attribindex, GLint سائيز, GLenum type, GLuint relativeoffset);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBBINDINGPROC) (GLuint attribindex, GLuint bindingindex);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXBINDINGDIVISORPROC) (GLuint bindingindex, GLuint ورهائيندڙ);
#إذا GL_GLES_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDispatchCompute (GLuint انگ_groups_x, GLuint انگ_groups_y, GLuint انگ_groups_z);
GL_APICALL فراغ GL_APIENTRY gl_Dispatch_Compute_اڻسڌو (GLintptr اڻسڌو);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Arrays_اڻسڌو (GLenum گهڻائي, ثابت فراغ *اڻسڌو);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Elements_اڻسڌو (GLenum گهڻائي, GLenum type, ثابت فراغ *اڻسڌو);
GL_APICALL فراغ GL_APIENTRY glFramebufferParameteri (GLenum هدف, GLenum pname, GLint param);
GL_APICALL فراغ GL_APIENTRY glGetFramebufferParameteriv (GLenum هدف, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY gl_Get_پروگرام_Interfaceiv (GLuint پروگرام, GLenum پروگرام_Interface, GLenum pname, GLint *params);
GL_APICALL GLuint GL_APIENTRY gl_Get_پروگرام_Resource_اشاريو (GLuint پروگرام, GLenum پروگرام_Interface, ثابت GLchar *name);
GL_APICALL فراغ GL_APIENTRY gl_Get_پروگرام_Resource_Name (GLuint پروگرام, GLenum پروگرام_Interface, GLuint اشاريو, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLchar *name);
GL_APICALL فراغ GL_APIENTRY gl_Get_پروگرام_Resourceiv (GLuint پروگرام, GLenum پروگرام_Interface, GLuint اشاريو, GLsizei prop_ڳڻپ, ثابت GLenum *props, GLsizei ڳڻپ, GLsizei *ڊيگهائي, GLint *params);
GL_APICALL GLint GL_APIENTRY gl_Get_پروگرام_Resource_Location (GLuint پروگرام, GLenum پروگرام_Interface, ثابت GLchar *name);
GL_APICALL فراغ GL_APIENTRY gl_Use_پروگرام_Stages (GLuint pipeline, GLbitfield stages, GLuint پروگرام);
GL_APICALL فراغ GL_APIENTRY gl_سرگرم_Shader_پروگرام (GLuint pipeline, GLuint پروگرام);
GL_APICALL GLuint GL_APIENTRY glCreateShaderProgramv (GLenum type, GLsizei ڳڻپ, ثابت GLchar *ثابت*لڙيون);
GL_APICALL فراغ GL_APIENTRY gl_Bind_پروگرام_Pipeline (GLuint pipeline);
GL_APICALL فراغ GL_APIENTRY gl_Delete_پروگرام_Pipelines (GLsizei n, ثابت GLuint *pipelines);
GL_APICALL فراغ GL_APIENTRY gl_Gen_پروگرام_Pipelines (GLsizei n, GLuint *pipelines);
GL_APICALL GLboolean GL_APIENTRY gl_Is_پروگرام_Pipeline (GLuint pipeline);
GL_APICALL فراغ GL_APIENTRY gl_Get_پروگرام_Pipelineiv (GLuint pipeline, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform1i (GLuint پروگرام, GLint location, GLint v0);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform2i (GLuint پروگرام, GLint location, GLint v0, GLint v1);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform3i (GLuint پروگرام, GLint location, GLint v0, GLint v1, GLint v2);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform4i (GLuint پروگرام, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform1ui (GLuint پروگرام, GLint location, GLuint v0);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform2ui (GLuint پروگرام, GLint location, GLuint v0, GLuint v1);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform3ui (GLuint پروگرام, GLint location, GLuint v0, GLuint v1, GLuint v2);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform4ui (GLuint پروگرام, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform1f (GLuint پروگرام, GLint location, GLfloat v0);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform2f (GLuint پروگرام, GLint location, GLfloat v0, GLfloat v1);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform3f (GLuint پروگرام, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform4f (GLuint پروگرام, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform1iv (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLint *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform2iv (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLint *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform3iv (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLint *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform4iv (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLint *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform1uiv (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLuint *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform2uiv (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLuint *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform3uiv (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLuint *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform4uiv (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLuint *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform1fv (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform2fv (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform3fv (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_Uniform4fv (GLuint پروگرام, GLint location, GLsizei ڳڻپ, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_هڪجهڙو_Matrix2fv (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_هڪجهڙو_Matrix3fv (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_هڪجهڙو_Matrix4fv (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_هڪجهڙو_Matrix2x3fv (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_هڪجهڙو_Matrix3x2fv (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_هڪجهڙو_Matrix2x4fv (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_هڪجهڙو_Matrix4x2fv (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_هڪجهڙو_Matrix3x4fv (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_پروگرام_هڪجهڙو_Matrix4x3fv (GLuint پروگرام, GLint location, GLsizei ڳڻپ, GLboolean transpose, ثابت GLfloat *قدر);
GL_APICALL فراغ GL_APIENTRY gl_Validate_پروگرام_Pipeline (GLuint pipeline);
GL_APICALL فراغ GL_APIENTRY gl_Get_پروگرام_Pipeline_Info_Log (GLuint pipeline, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLchar *infoLog);
GL_APICALL فراغ GL_APIENTRY glBindImageTexture (GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
GL_APICALL فراغ GL_APIENTRY glGetBooleani_v (GLenum هدف, GLuint اشاريو, GLboolean *معلومات);
GL_APICALL فراغ GL_APIENTRY gl_يادگيري_Barrier (GLbitfield barriers);
GL_APICALL فراغ GL_APIENTRY gl_يادگيري_Barrier_By_Region (GLbitfield barriers);
GL_APICALL فراغ GL_APIENTRY glTexStorage2DMultisample (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي, GLboolean fixedsamplelocations);
GL_APICALL فراغ GL_APIENTRY glGetMultisamplefv (GLenum pname, GLuint اشاريو, GLfloat *val);
GL_APICALL فراغ GL_APIENTRY glSampleMaski (GLuint نقاب_عدد, GLbitfield نقاب);
GL_APICALL فراغ GL_APIENTRY glGetTexLevelParameteriv (GLenum هدف, GLint level, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetTexLevelParameterfv (GLenum هدف, GLint level, GLenum pname, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY gl_Bind_راس_بفر (GLuint bindingindex, GLuint بفر_2, GLintptr وٿي_2, GLsizei stride);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib_Format (GLuint attribindex, GLint سائيز, GLenum type, GLboolean normalized, GLuint relativeoffset);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib_IFormat (GLuint attribindex, GLint سائيز, GLenum type, GLuint relativeoffset);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib_Binding (GLuint attribindex, GLuint bindingindex);
GL_APICALL فراغ GL_APIENTRY gl_راس_Binding_ورهائيندڙ (GLuint bindingindex, GLuint ورهائيندڙ);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_ES_VERSION_3_1 */

#جيڪڏهن_وصف_نه_ٿيل GL_ES_نسخو_3_2
#وصف_ڪريو GL_ES_نسخو_3_2 1
تعريفنوع فراغ (GL_APIENTRY  *GLDEBUGPROC)(GLenum ذريعو,GLenum type,GLuint id,GLenum severity,GLsizei ڊيگهائي,ثابت GLchar *پيغام,ثابت فراغ *userParam);
#وصف_ڪريو GL_MULTISAMPLE_سٽ_ويڪر_RANGE   0x9381
#وصف_ڪريو GL_MULTISAMPLE_سٽ_ويڪر_GRANULARITY 0x9382
#وصف_ڪريو GL_MULTIPLY                       0x9294
#وصف_ڪريو GL_SCREEN                         0x9295
#وصف_ڪريو GL_OVERLAY                        0x9296
#وصف_ڪريو GL_DARKEN                         0x9297
#وصف_ڪريو GL_LIGHTEN                        0x9298
#وصف_ڪريو GL_COLORDODGE                     0x9299
#وصف_ڪريو GL_COLORBURN                      0x929A
#وصف_ڪريو GL_HARDLIGHT                      0x929B
#وصف_ڪريو GL_SOFTLIGHT                      0x929C
#وصف_ڪريو GL_DIFFERENCE                     0x929E
#وصف_ڪريو GL_EXCLUSION                      0x92A0
#وصف_ڪريو GL_HSL_HUE                        0x92AD
#وصف_ڪريو GL_HSL_SATURATION                 0x92AE
#وصف_ڪريو GL_HSL_COLOR                      0x92AF
#وصف_ڪريو GL_HSL_LUMINOSITY                 0x92B0
#وصف_ڪريو GL_DEBUG_OUTPUT_SYNCHRONOUS       0x8242
#وصف_ڪريو GL_DEBUG_ايندڙ_LOGGED_پيغام_ڊيگهائي 0x8243
#وصف_ڪريو GL_DEBUG_CALLBACK_FUNCTION        0x8244
#وصف_ڪريو GL_DEBUG_CALLBACK_USER_PARAM      0x8245
#وصف_ڪريو GL_DEBUG_ذريعو_API               0x8246
#وصف_ڪريو GL_DEBUG_ذريعو_دري_SYSTEM     0x8247
#وصف_ڪريو GL_DEBUG_ذريعو_SHADER_COMPILER   0x8248
#وصف_ڪريو GL_DEBUG_ذريعو_ٽيون_PARTY       0x8249
#وصف_ڪريو GL_DEBUG_ذريعو_APPLICATION       0x824A
#وصف_ڪريو GL_DEBUG_ذريعو_OTHER             0x824B
#وصف_ڪريو GL_DEBUG_TYPE_ERROR               0x824C
#وصف_ڪريو GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR 0x824D
#وصف_ڪريو GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR  0x824E
#وصف_ڪريو GL_DEBUG_TYPE_PORTABILITY         0x824F
#وصف_ڪريو GL_DEBUG_TYPE_PERFORMANCE         0x8250
#وصف_ڪريو GL_DEBUG_TYPE_OTHER               0x8251
#وصف_ڪريو GL_DEBUG_TYPE_MARKER              0x8268
#وصف_ڪريو GL_DEBUG_TYPE_ڌڪو_گروهه          0x8269
#وصف_ڪريو GL_DEBUG_TYPE_ڪڍو_گروهه           0x826A
#وصف_ڪريو GL_DEBUG_SEVERITY_NOTIFICATION    0x826B
#وصف_ڪريو GL_MAX_DEBUG_گروهه_ڍير_اونهائي    0x826C
#وصف_ڪريو GL_DEBUG_گروهه_ڍير_اونهائي        0x826D
#وصف_ڪريو GL_بفر                         0x82E0
#وصف_ڪريو GL_SHADER                         0x82E1
#وصف_ڪريو GL_پروگرام                        0x82E2
#وصف_ڪريو GL_راس_ARRAY                   0x8074
#وصف_ڪريو GL_QUERY                          0x82E3
#وصف_ڪريو GL_پروگرام_PIPELINE               0x82E4
#وصف_ڪريو GL_SAMPLER                        0x82E6
#وصف_ڪريو GL_MAX_LABEL_ڊيگهائي               0x82E8
#وصف_ڪريو GL_MAX_DEBUG_پيغام_ڊيگهائي       0x9143
#وصف_ڪريو GL_MAX_DEBUG_LOGGED_MESSAGES      0x9144
#وصف_ڪريو GL_DEBUG_LOGGED_MESSAGES          0x9145
#وصف_ڪريو GL_DEBUG_SEVERITY_مٿاهون            0x9146
#وصف_ڪريو GL_DEBUG_SEVERITY_MEDIUM          0x9147
#وصف_ڪريو GL_DEBUG_SEVERITY_هيٺيون             0x9148
#وصف_ڪريو GL_DEBUG_OUTPUT                   0x92E0
#وصف_ڪريو GL_CONTEXT_FLAG_DEBUG_ٻٽو_انگ         0x00000002
#وصف_ڪريو GL_ڍير_حد_کان_مٿي                 0x0503
#وصف_ڪريو GL_ڍير_UNDERFLOW                0x0504
#وصف_ڪريو GL_GEOMETRY_SHADER                0x8DD9
#وصف_ڪريو GL_GEOMETRY_SHADER_ٻٽو_انگ            0x00000004
#وصف_ڪريو GL_GEOMETRY_VERTICES_ٻاهريون          0x8916
#وصف_ڪريو GL_GEOMETRY_داخلا_TYPE            0x8917
#وصف_ڪريو GL_GEOMETRY_OUTPUT_TYPE           0x8918
#وصف_ڪريو GL_GEOMETRY_SHADER_INVOCATIONS    0x887F
#وصف_ڪريو GL_LAYER_PROVOKING_راس         0x825E
#وصف_ڪريو GL_سٽون_ADJACENCY                0x000A
#وصف_ڪريو GL_سٽ_STRIP_ADJACENCY           0x000B
#وصف_ڪريو GL_TRIANGLES_ADJACENCY            0x000C
#وصف_ڪريو GL_TRIANGLE_STRIP_ADJACENCY       0x000D
#وصف_ڪريو GL_MAX_GEOMETRY_هڪجهڙو_COMPONENTS 0x8DDF
#وصف_ڪريو GL_MAX_GEOMETRY_هڪجهڙو_بلاڪون    0x8A2C
#وصف_ڪريو GL_MAX_COMBINED_GEOMETRY_هڪجهڙو_COMPONENTS 0x8A32
#وصف_ڪريو GL_MAX_GEOMETRY_داخلا_COMPONENTS  0x9123
#وصف_ڪريو GL_MAX_GEOMETRY_OUTPUT_COMPONENTS 0x9124
#وصف_ڪريو GL_MAX_GEOMETRY_OUTPUT_VERTICES   0x8DE0
#وصف_ڪريو GL_MAX_GEOMETRY_ڪل_OUTPUT_COMPONENTS 0x8DE1
#وصف_ڪريو GL_MAX_GEOMETRY_SHADER_INVOCATIONS 0x8E5A
#وصف_ڪريو GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS 0x8C29
#وصف_ڪريو GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS 0x92CF
#وصف_ڪريو GL_MAX_GEOMETRY_ATOMIC_COUNTERS   0x92D5
#وصف_ڪريو GL_MAX_GEOMETRY_IMAGE_UNIFORMS    0x90CD
#وصف_ڪريو GL_MAX_GEOMETRY_SHADER_STORAGE_بلاڪون 0x90D7
#وصف_ڪريو GL_پهريون_راس_CONVENTION        0x8E4D
#وصف_ڪريو GL_آخري_راس_CONVENTION         0x8E4E
#وصف_ڪريو GL_UNDEFINED_راس               0x8260
#وصف_ڪريو GL_PRIMITIVES_GENERATED           0x8C87
#وصف_ڪريو GL_FRAMEBUFFER_DEFAULT_LAYERS     0x9312
#وصف_ڪريو GL_MAX_FRAMEBUFFER_LAYERS         0x9317
#وصف_ڪريو GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS 0x8DA8
#وصف_ڪريو GL_FRAMEBUFFER_ATTACHMENT_LAYERED 0x8DA7
#وصف_ڪريو GL_REFERENCED_BY_GEOMETRY_SHADER  0x9309
#وصف_ڪريو GL_PRIMITIVE_BOUNDING_BOX         0x92BE
#وصف_ڪريو GL_CONTEXT_FLAG_ROBUST_ACCESS_ٻٽو_انگ 0x00000004
#وصف_ڪريو GL_CONTEXT_FLAGS                  0x821E
#وصف_ڪريو GL_LOSE_CONTEXT_ON_RESET          0x8252
#وصف_ڪريو GL_GUILTY_CONTEXT_RESET           0x8253
#وصف_ڪريو GL_INNOCENT_CONTEXT_RESET         0x8254
#وصف_ڪريو GL_UNKNOWN_CONTEXT_RESET          0x8255
#وصف_ڪريو GL_RESET_NOTIFICATION_STRATEGY    0x8256
#وصف_ڪريو GL_NO_RESET_NOTIFICATION          0x8261
#وصف_ڪريو GL_CONTEXT_گم                   0x0507
#وصف_ڪريو GL_SAMPLE_SHADING                 0x8C36
#وصف_ڪريو GL_MIN_SAMPLE_SHADING_قدر       0x8C37
#وصف_ڪريو GL_MIN_FRAGMENT_INTERPOLATION_وٿي 0x8E5B
#وصف_ڪريو GL_MAX_FRAGMENT_INTERPOLATION_وٿي 0x8E5C
#وصف_ڪريو GL_FRAGMENT_INTERPOLATION_وٿي_بٽ 0x8E5D
#وصف_ڪريو GL_PATCHES                        0x000E
#وصف_ڪريو GL_PATCH_VERTICES                 0x8E72
#وصف_ڪريو GL_TESS_CONTROL_OUTPUT_VERTICES   0x8E75
#وصف_ڪريو GL_TESS_GEN_گهڻائي                  0x8E76
#وصف_ڪريو GL_TESS_GEN_SPACING               0x8E77
#وصف_ڪريو GL_TESS_GEN_راس_ترتيب          0x8E78
#وصف_ڪريو GL_TESS_GEN_نقطو_گهڻائي            0x8E79
#وصف_ڪريو GL_ISOLINES                       0x8E7A
#وصف_ڪريو GL_QUADS                          0x0007
#وصف_ڪريو GL_FRACTIONAL_ODD                 0x8E7B
#وصف_ڪريو GL_FRACTIONAL_EVEN                0x8E7C
#وصف_ڪريو GL_MAX_PATCH_VERTICES             0x8E7D
#وصف_ڪريو GL_MAX_TESS_GEN_LEVEL             0x8E7E
#وصف_ڪريو GL_MAX_TESS_CONTROL_هڪجهڙو_COMPONENTS 0x8E7F
#وصف_ڪريو GL_MAX_TESS_EVALUATION_هڪجهڙو_COMPONENTS 0x8E80
#وصف_ڪريو GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS 0x8E81
#وصف_ڪريو GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS 0x8E82
#وصف_ڪريو GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS 0x8E83
#وصف_ڪريو GL_MAX_TESS_PATCH_COMPONENTS      0x8E84
#وصف_ڪريو GL_MAX_TESS_CONTROL_ڪل_OUTPUT_COMPONENTS 0x8E85
#وصف_ڪريو GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS 0x8E86
#وصف_ڪريو GL_MAX_TESS_CONTROL_هڪجهڙو_بلاڪون 0x8E89
#وصف_ڪريو GL_MAX_TESS_EVALUATION_هڪجهڙو_بلاڪون 0x8E8A
#وصف_ڪريو GL_MAX_TESS_CONTROL_داخلا_COMPONENTS 0x886C
#وصف_ڪريو GL_MAX_TESS_EVALUATION_داخلا_COMPONENTS 0x886D
#وصف_ڪريو GL_MAX_COMBINED_TESS_CONTROL_هڪجهڙو_COMPONENTS 0x8E1E
#وصف_ڪريو GL_MAX_COMBINED_TESS_EVALUATION_هڪجهڙو_COMPONENTS 0x8E1F
#وصف_ڪريو GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS 0x92CD
#وصف_ڪريو GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS 0x92CE
#وصف_ڪريو GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS 0x92D3
#وصف_ڪريو GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS 0x92D4
#وصف_ڪريو GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS 0x90CB
#وصف_ڪريو GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS 0x90CC
#وصف_ڪريو GL_MAX_TESS_CONTROL_SHADER_STORAGE_بلاڪون 0x90D8
#وصف_ڪريو GL_MAX_TESS_EVALUATION_SHADER_STORAGE_بلاڪون 0x90D9
#وصف_ڪريو GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED 0x8221
#وصف_ڪريو GL_IS_في_PATCH                   0x92E7
#وصف_ڪريو GL_REFERENCED_BY_TESS_CONTROL_SHADER 0x9307
#وصف_ڪريو GL_REFERENCED_BY_TESS_EVALUATION_SHADER 0x9308
#وصف_ڪريو GL_TESS_CONTROL_SHADER            0x8E88
#وصف_ڪريو GL_TESS_EVALUATION_SHADER         0x8E87
#وصف_ڪريو GL_TESS_CONTROL_SHADER_ٻٽو_انگ        0x00000008
#وصف_ڪريو GL_TESS_EVALUATION_SHADER_ٻٽو_انگ     0x00000010
#وصف_ڪريو GL_TEXTURE_BORDER_COLOR           0x1004
#وصف_ڪريو GL_CLAMP_منزل_BORDER                0x812D
#وصف_ڪريو GL_TEXTURE_بفر                 0x8C2A
#وصف_ڪريو GL_TEXTURE_بفر_BINDING         0x8C2A
#وصف_ڪريو GL_MAX_TEXTURE_بفر_سائيز        0x8C2B
#وصف_ڪريو GL_TEXTURE_BINDING_بفر         0x8C2C
#وصف_ڪريو GL_TEXTURE_بفر_معلومات_STORE_BINDING 0x8C2D
#وصف_ڪريو GL_TEXTURE_بفر_وٿي_ALIGNMENT 0x919F
#وصف_ڪريو GL_SAMPLER_بفر                 0x8DC2
#وصف_ڪريو GL_INT_SAMPLER_بفر             0x8DD0
#وصف_ڪريو GL_UNSIGNED_INT_SAMPLER_بفر    0x8DD8
#وصف_ڪريو GL_IMAGE_بفر                   0x9051
#وصف_ڪريو GL_INT_IMAGE_بفر               0x905C
#وصف_ڪريو GL_UNSIGNED_INT_IMAGE_بفر      0x9067
#وصف_ڪريو GL_TEXTURE_بفر_وٿي          0x919D
#وصف_ڪريو GL_TEXTURE_بفر_سائيز            0x919E
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_4x4       0x93B0
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_5x4       0x93B1
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_5x5       0x93B2
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_6x5       0x93B3
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_6x6       0x93B4
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_8x5       0x93B5
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_8x6       0x93B6
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_8x8       0x93B7
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_10x5      0x93B8
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_10x6      0x93B9
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_10x8      0x93BA
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_10x10     0x93BB
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_12x10     0x93BC
#وصف_ڪريو GL_COMPRESSED_RGBA_ASTC_12x12     0x93BD
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4 0x93D0
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4 0x93D1
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5 0x93D2
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5 0x93D3
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6 0x93D4
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5 0x93D5
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6 0x93D6
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8 0x93D7
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5 0x93D8
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6 0x93D9
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8 0x93DA
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10 0x93DB
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10 0x93DC
#وصف_ڪريو GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12 0x93DD
#وصف_ڪريو GL_TEXTURE_CUBE_MAP_ARRAY         0x9009
#وصف_ڪريو GL_TEXTURE_BINDING_CUBE_MAP_ARRAY 0x900A
#وصف_ڪريو GL_SAMPLER_CUBE_MAP_ARRAY         0x900C
#وصف_ڪريو GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW  0x900D
#وصف_ڪريو GL_INT_SAMPLER_CUBE_MAP_ARRAY     0x900E
#وصف_ڪريو GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY 0x900F
#وصف_ڪريو GL_IMAGE_CUBE_MAP_ARRAY           0x9054
#وصف_ڪريو GL_INT_IMAGE_CUBE_MAP_ARRAY       0x905F
#وصف_ڪريو GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY 0x906A
#وصف_ڪريو GL_TEXTURE_2D_MULTISAMPLE_ARRAY   0x9102
#وصف_ڪريو GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY 0x9105
#وصف_ڪريو GL_SAMPLER_2D_MULTISAMPLE_ARRAY   0x910B
#وصف_ڪريو GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910C
#وصف_ڪريو GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910D
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDBARRIERPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYIMAGESUBDATAPROC) (GLuint srcName, GLenum src_هدف, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dst_هدف, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei src_ويڪر, GLsizei src_اوچائي, GLsizei src_اونهائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEBUGMESSAGECONTROLPROC) (GLenum ذريعو, GLenum type, GLenum severity, GLsizei ڳڻپ, ثابت GLuint *ids, GLboolean enabled);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEBUGMESSAGEINSERTPROC) (GLenum ذريعو, GLenum type, GLuint id, GLenum severity, GLsizei ڊيگهائي, ثابت GLchar *buf);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEBUGMESSAGECALLBACKPROC) (GLDEBUGPROC callback, ثابت فراغ *userParam);
تعريفنوع GLuint (GL_APIENTRYP PFNGLGETDEBUGMESSAGELOGPROC) (GLuint ڳڻپ, GLsizei buf_سائيز, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *پيغام_Log);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPUSHDEBUGGROUPPROC) (GLenum ذريعو, GLuint id, GLsizei ڊيگهائي, ثابت GLchar *پيغام);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOPDEBUGGROUPPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLOBJECTLABELPROC) (GLenum identifier, GLuint name, GLsizei ڊيگهائي, ثابت GLchar *label);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETOBJECTLABELPROC) (GLenum identifier, GLuint name, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLchar *label);
تعريفنوع فراغ (GL_APIENTRYP PFNGLOBJECTPTRLABELPROC) (ثابت فراغ *ptr, GLsizei ڊيگهائي, ثابت GLchar *label);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETOBJECTPTRLABELPROC) (ثابت فراغ *ptr, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLchar *label);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPOINTERVPROC) (GLenum pname, فراغ **params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENABLEIPROC) (GLenum هدف, GLuint اشاريو);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISABLEIPROC) (GLenum هدف, GLuint اشاريو);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONIPROC) (GLuint buf, GLenum گهڻائي);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEIPROC) (GLuint buf, GLenum گهڻائي_RGB, GLenum گهڻائي_Alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDFUNCIPROC) (GLuint buf, GLenum src, GLenum dst);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEIPROC) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOLORMASKIPROC) (GLuint اشاريو, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISENABLEDIPROC) (GLenum هدف, GLuint اشاريو);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSBASEVERTEXPROC) (GLenum گهڻائي, GLsizei ڳڻپ, GLenum type, ثابت فراغ *indices, GLint basevertex);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC) (GLenum گهڻائي, GLuint شروعات, GLuint پڇاڙي, GLsizei ڳڻپ, GLenum type, ثابت فراغ *indices, GLint basevertex);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC) (GLenum گهڻائي, GLsizei ڳڻپ, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLint basevertex);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREPROC) (GLenum هدف, GLenum attachment, GLuint texture, GLint level);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPRIMITIVEBOUNDINGBOXPROC) (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
تعريفنوع GLenum (GL_APIENTRYP PFNGLGETGRAPHICSRESETSTATUSPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLREADNPIXELSPROC) (GLint x, GLint y, GLsizei ويڪر, GLsizei اوچائي, GLenum format, GLenum type, GLsizei buf_سائيز, فراغ *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNUNIFORMFVPROC) (GLuint پروگرام, GLint location, GLsizei buf_سائيز, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNUNIFORMIVPROC) (GLuint پروگرام, GLint location, GLsizei buf_سائيز, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETNUNIFORMUIVPROC) (GLuint پروگرام, GLint location, GLsizei buf_سائيز, GLuint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMINSAMPLESHADINGPROC) (GLfloat قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPATCHPARAMETERIPROC) (GLenum pname, GLint قدر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERIIVPROC) (GLenum هدف, GLenum pname, ثابت GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERIUIVPROC) (GLenum هدف, GLenum pname, ثابت GLuint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXPARAMETERIIVPROC) (GLenum هدف, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXPARAMETERIUIVPROC) (GLenum هدف, GLenum pname, GLuint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIIVPROC) (GLuint sampler, GLenum pname, ثابت GLint *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIUIVPROC) (GLuint sampler, GLenum pname, ثابت GLuint *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIIVPROC) (GLuint sampler, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIUIVPROC) (GLuint sampler, GLenum pname, GLuint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXBUFFERPROC) (GLenum هدف, GLenum internalformat, GLuint بفر_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXBUFFERRANGEPROC) (GLenum هدف, GLenum internalformat, GLuint بفر_2, GLintptr وٿي_2, GLsizeiptr سائيز);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE3DMULTISAMPLEPROC) (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLboolean fixedsamplelocations);
#إذا GL_GLES_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glBlendBarrier (فراغ);
GL_APICALL فراغ GL_APIENTRY gl_Copy_Image_Sub_معلومات (GLuint srcName, GLenum src_هدف, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dst_هدف, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei src_ويڪر, GLsizei src_اوچائي, GLsizei src_اونهائي);
GL_APICALL فراغ GL_APIENTRY gl_Debug_پيغام_Control (GLenum ذريعو, GLenum type, GLenum severity, GLsizei ڳڻپ, ثابت GLuint *ids, GLboolean enabled);
GL_APICALL فراغ GL_APIENTRY gl_Debug_پيغام_وجهو (GLenum ذريعو, GLenum type, GLuint id, GLenum severity, GLsizei ڊيگهائي, ثابت GLchar *buf);
GL_APICALL فراغ GL_APIENTRY gl_Debug_پيغام_Callback (GLDEBUGPROC callback, ثابت فراغ *userParam);
GL_APICALL GLuint GL_APIENTRY gl_Get_Debug_پيغام_Log (GLuint ڳڻپ, GLsizei buf_سائيز, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *پيغام_Log);
GL_APICALL فراغ GL_APIENTRY gl_ڌڪو_Debug_گروهه (GLenum ذريعو, GLuint id, GLsizei ڊيگهائي, ثابت GLchar *پيغام);
GL_APICALL فراغ GL_APIENTRY gl_ڪڍو_Debug_گروهه (فراغ);
GL_APICALL فراغ GL_APIENTRY glObjectLabel (GLenum identifier, GLuint name, GLsizei ڊيگهائي, ثابت GLchar *label);
GL_APICALL فراغ GL_APIENTRY glGetObjectLabel (GLenum identifier, GLuint name, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLchar *label);
GL_APICALL فراغ GL_APIENTRY glObjectPtrLabel (ثابت فراغ *ptr, GLsizei ڊيگهائي, ثابت GLchar *label);
GL_APICALL فراغ GL_APIENTRY glGetObjectPtrLabel (ثابت فراغ *ptr, GLsizei buf_سائيز, GLsizei *ڊيگهائي, GLchar *label);
GL_APICALL فراغ GL_APIENTRY glGetPointerv (GLenum pname, فراغ **params);
GL_APICALL فراغ GL_APIENTRY glEnablei (GLenum هدف, GLuint اشاريو);
GL_APICALL فراغ GL_APIENTRY glDisablei (GLenum هدف, GLuint اشاريو);
GL_APICALL فراغ GL_APIENTRY glBlendEquationi (GLuint buf, GLenum گهڻائي);
GL_APICALL فراغ GL_APIENTRY glBlendEquationSeparatei (GLuint buf, GLenum گهڻائي_RGB, GLenum گهڻائي_Alpha);
GL_APICALL فراغ GL_APIENTRY glBlendFunci (GLuint buf, GLenum src, GLenum dst);
GL_APICALL فراغ GL_APIENTRY glBlendFuncSeparatei (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
GL_APICALL فراغ GL_APIENTRY glColorMaski (GLuint اشاريو, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
GL_APICALL GLboolean GL_APIENTRY glIsEnabledi (GLenum هدف, GLuint اشاريو);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Elements_بنياد_راس (GLenum گهڻائي, GLsizei ڳڻپ, GLenum type, ثابت فراغ *indices, GLint basevertex);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Range_Elements_بنياد_راس (GLenum گهڻائي, GLuint شروعات, GLuint پڇاڙي, GLsizei ڳڻپ, GLenum type, ثابت فراغ *indices, GLint basevertex);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Elements_Instanced_بنياد_راس (GLenum گهڻائي, GLsizei ڳڻپ, GLenum type, ثابت فراغ *indices, GLsizei instancecount, GLint basevertex);
GL_APICALL فراغ GL_APIENTRY glFramebufferTexture (GLenum هدف, GLenum attachment, GLuint texture, GLint level);
GL_APICALL فراغ GL_APIENTRY glPrimitiveBoundingBox (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
GL_APICALL GLenum GL_APIENTRY gl_Get_Graphics_Reset_حالت (فراغ);
GL_APICALL فراغ GL_APIENTRY glReadnPixels (GLint x, GLint y, GLsizei ويڪر, GLsizei اوچائي, GLenum format, GLenum type, GLsizei buf_سائيز, فراغ *معلومات);
GL_APICALL فراغ GL_APIENTRY glGetnUniformfv (GLuint پروگرام, GLint location, GLsizei buf_سائيز, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY glGetnUniformiv (GLuint پروگرام, GLint location, GLsizei buf_سائيز, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetnUniformuiv (GLuint پروگرام, GLint location, GLsizei buf_سائيز, GLuint *params);
GL_APICALL فراغ GL_APIENTRY glMinSampleShading (GLfloat قدر);
GL_APICALL فراغ GL_APIENTRY glPatchParameteri (GLenum pname, GLint قدر);
GL_APICALL فراغ GL_APIENTRY glTexParameterIiv (GLenum هدف, GLenum pname, ثابت GLint *params);
GL_APICALL فراغ GL_APIENTRY glTexParameterIuiv (GLenum هدف, GLenum pname, ثابت GLuint *params);
GL_APICALL فراغ GL_APIENTRY glGetTexParameterIiv (GLenum هدف, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetTexParameterIuiv (GLenum هدف, GLenum pname, GLuint *params);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterIiv (GLuint sampler, GLenum pname, ثابت GLint *param);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterIuiv (GLuint sampler, GLenum pname, ثابت GLuint *param);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameterIiv (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameterIuiv (GLuint sampler, GLenum pname, GLuint *params);
GL_APICALL فراغ GL_APIENTRY gl_Tex_بفر (GLenum هدف, GLenum internalformat, GLuint بفر_2);
GL_APICALL فراغ GL_APIENTRY gl_Tex_بفر_Range (GLenum هدف, GLenum internalformat, GLuint بفر_2, GLintptr وٿي_2, GLsizeiptr سائيز);
GL_APICALL فراغ GL_APIENTRY glTexStorage3DMultisample (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي, GLsizei اونهائي_2, GLboolean fixedsamplelocations);
#جيڪڏهن_پورو
#جيڪڏهن_پورو /* GL_ES_VERSION_3_2 */

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو
