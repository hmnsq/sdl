#جيڪڏهن_وصف_نه_ٿيل __gles2_gl2_h_
#وصف_ڪريو __gles2_gl2_h_ 1

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

#ضمن <GLES2/gl2platform.h>

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
 * Versions considered: 2\.[0-9]
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

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو
