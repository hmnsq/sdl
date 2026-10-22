#جيڪڏهن_وصف_نه_ٿيل __gles1_gl_h_
#وصف_ڪريو __gles1_gl_h_ 1

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

#ضمن <GLES/glplatform.h>

/* Generated on date 20260803 */

/* Generated C header for:
 * API: gles1
 * Profile: common
 * Versions considered: .*
 * Versions emitted: .*
 * Default extensions included: None
 * Additional extensions included: ^(GL_OES_read_format|GL_OES_compressed_paletted_texture|GL_OES_point_size_array|GL_OES_point_sprite)$
 * Extensions removed: _nomatch_^
 */

#جيڪڏهن_وصف_نه_ٿيل GL_نسخو_ES_CM_1_0
#وصف_ڪريو GL_نسخو_ES_CM_1_0 1
#ضمن <KHR/khrplatform.h>
تعريفنوع khronos_int8_t GLbyte;
تعريفنوع khronos_float_t GLclampf;
تعريفنوع khronos_int16_t GLshort;
تعريفنوع khronos_uint16_t GLushort;
تعريفنوع فراغ GLvoid;
تعريفنوع بنانشان صحيح GLenum;
تعريفنوع khronos_float_t GLfloat;
تعريفنوع khronos_int32_t GLfixed;
تعريفنوع بنانشان صحيح GLuint;
تعريفنوع khronos_ssize_t GLsizeiptr;
تعريفنوع khronos_intptr_t GLintptr;
تعريفنوع بنانشان صحيح GLbitfield;
تعريفنوع صحيح GLint;
تعريفنوع khronos_uint8_t GLubyte;
تعريفنوع بنانشان حرف GLboolean;
تعريفنوع صحيح GLsizei;
تعريفنوع khronos_int32_t GLclampx;
#وصف_ڪريو GL_نسخو_ES_CL_1_0              1
#وصف_ڪريو GL_نسخو_ES_CM_1_1              1
#وصف_ڪريو GL_نسخو_ES_CL_1_1              1
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
#وصف_ڪريو GL_NEVER                          0x0200
#وصف_ڪريو GL_LESS                           0x0201
#وصف_ڪريو GL_EQUAL                          0x0202
#وصف_ڪريو GL_LEQUAL                         0x0203
#وصف_ڪريو GL_GREATER                        0x0204
#وصف_ڪريو GL_NOTEQUAL                       0x0205
#وصف_ڪريو GL_GEQUAL                         0x0206
#وصف_ڪريو GL_ALWAYS                         0x0207
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
#وصف_ڪريو GL_CLIP_PLANE0                    0x3000
#وصف_ڪريو GL_CLIP_PLANE1                    0x3001
#وصف_ڪريو GL_CLIP_PLANE2                    0x3002
#وصف_ڪريو GL_CLIP_PLANE3                    0x3003
#وصف_ڪريو GL_CLIP_PLANE4                    0x3004
#وصف_ڪريو GL_CLIP_PLANE5                    0x3005
#وصف_ڪريو GL_FRONT                          0x0404
#وصف_ڪريو GL_پٺ                           0x0405
#وصف_ڪريو GL_FRONT_AND_پٺ                 0x0408
#وصف_ڪريو GL_FOG                            0x0B60
#وصف_ڪريو GL_LIGHTING                       0x0B50
#وصف_ڪريو GL_TEXTURE_2D                     0x0DE1
#وصف_ڪريو GL_CULL_FACE                      0x0B44
#وصف_ڪريو GL_ALPHA_TEST                     0x0BC0
#وصف_ڪريو GL_BLEND                          0x0BE2
#وصف_ڪريو GL_COLOR_LOGIC_OP                 0x0BF2
#وصف_ڪريو GL_DITHER                         0x0BD0
#وصف_ڪريو GL_STENCIL_TEST                   0x0B90
#وصف_ڪريو GL_اونهائي_TEST                     0x0B71
#وصف_ڪريو GL_نقطو_SMOOTH                   0x0B10
#وصف_ڪريو GL_سٽ_SMOOTH                    0x0B20
#وصف_ڪريو GL_SCISSOR_TEST                   0x0C11
#وصف_ڪريو GL_COLOR_MATERIAL                 0x0B57
#وصف_ڪريو GL_NORMALIZE                      0x0BA1
#وصف_ڪريو GL_RESCALE_عام                 0x803A
#وصف_ڪريو GL_راس_ARRAY                   0x8074
#وصف_ڪريو GL_عام_ARRAY                   0x8075
#وصف_ڪريو GL_COLOR_ARRAY                    0x8076
#وصف_ڪريو GL_TEXTURE_COORD_ARRAY            0x8078
#وصف_ڪريو GL_MULTISAMPLE                    0x809D
#وصف_ڪريو GL_SAMPLE_ALPHA_منزل_COVERAGE       0x809E
#وصف_ڪريو GL_SAMPLE_ALPHA_منزل_ONE            0x809F
#وصف_ڪريو GL_SAMPLE_COVERAGE                0x80A0
#وصف_ڪريو GL_NO_ERROR                       0
#وصف_ڪريو GL_INVALID_ENUM                   0x0500
#وصف_ڪريو GL_INVALID_قدر                  0x0501
#وصف_ڪريو GL_INVALID_OPERATION              0x0502
#وصف_ڪريو GL_ڍير_حد_کان_مٿي                 0x0503
#وصف_ڪريو GL_ڍير_UNDERFLOW                0x0504
#وصف_ڪريو GL_ٻاهريون_جو_يادگيري                  0x0505
#وصف_ڪريو GL_EXP                            0x0800
#وصف_ڪريو GL_EXP2                           0x0801
#وصف_ڪريو GL_FOG_DENSITY                    0x0B62
#وصف_ڪريو GL_FOG_شروعات                      0x0B63
#وصف_ڪريو GL_FOG_پڇاڙي                        0x0B64
#وصف_ڪريو GL_FOG_گهڻائي                       0x0B65
#وصف_ڪريو GL_FOG_COLOR                      0x0B66
#وصف_ڪريو GL_CW                             0x0900
#وصف_ڪريو GL_CCW                            0x0901
#وصف_ڪريو GL_CURRENT_COLOR                  0x0B00
#وصف_ڪريو GL_CURRENT_عام                 0x0B02
#وصف_ڪريو GL_CURRENT_TEXTURE_COORDS         0x0B03
#وصف_ڪريو GL_نقطو_سائيز                     0x0B11
#وصف_ڪريو GL_نقطو_سائيز_MIN                 0x8126
#وصف_ڪريو GL_نقطو_سائيز_MAX                 0x8127
#وصف_ڪريو GL_نقطو_FADE_حد_سائيز      0x8128
#وصف_ڪريو GL_نقطو_مفاصلو_ATTENUATION     0x8129
#وصف_ڪريو GL_SMOOTH_نقطو_سائيز_RANGE        0x0B12
#وصف_ڪريو GL_سٽ_ويڪر                     0x0B21
#وصف_ڪريو GL_SMOOTH_سٽ_ويڪر_RANGE        0x0B22
#وصف_ڪريو GL_ALIASED_نقطو_سائيز_RANGE       0x846D
#وصف_ڪريو GL_ALIASED_سٽ_ويڪر_RANGE       0x846E
#وصف_ڪريو GL_CULL_FACE_گهڻائي                 0x0B45
#وصف_ڪريو GL_FRONT_FACE                     0x0B46
#وصف_ڪريو GL_SHADE_MODEL                    0x0B54
#وصف_ڪريو GL_اونهائي_RANGE                    0x0B70
#وصف_ڪريو GL_اونهائي_WRITEMASK                0x0B72
#وصف_ڪريو GL_اونهائي_CLEAR_قدر              0x0B73
#وصف_ڪريو GL_اونهائي_FUNC                     0x0B74
#وصف_ڪريو GL_STENCIL_CLEAR_قدر            0x0B91
#وصف_ڪريو GL_STENCIL_FUNC                   0x0B92
#وصف_ڪريو GL_STENCIL_قدر_نقاب             0x0B93
#وصف_ڪريو GL_STENCIL_FAIL                   0x0B94
#وصف_ڪريو GL_STENCIL_PASS_اونهائي_FAIL        0x0B95
#وصف_ڪريو GL_STENCIL_PASS_اونهائي_PASS        0x0B96
#وصف_ڪريو GL_STENCIL_REF                    0x0B97
#وصف_ڪريو GL_STENCIL_WRITEMASK              0x0B98
#وصف_ڪريو GL_ميٽرڪس_گهڻائي                    0x0BA0
#وصف_ڪريو GL_VIEWPORT                       0x0BA2
#وصف_ڪريو GL_MODELVIEW_ڍير_اونهائي          0x0BA3
#وصف_ڪريو GL_PROJECTION_ڍير_اونهائي         0x0BA4
#وصف_ڪريو GL_TEXTURE_ڍير_اونهائي            0x0BA5
#وصف_ڪريو GL_MODELVIEW_ميٽرڪس               0x0BA6
#وصف_ڪريو GL_PROJECTION_ميٽرڪس              0x0BA7
#وصف_ڪريو GL_TEXTURE_ميٽرڪس                 0x0BA8
#وصف_ڪريو GL_ALPHA_TEST_FUNC                0x0BC1
#وصف_ڪريو GL_ALPHA_TEST_REF                 0x0BC2
#وصف_ڪريو GL_BLEND_DST                      0x0BE0
#وصف_ڪريو GL_BLEND_SRC                      0x0BE1
#وصف_ڪريو GL_LOGIC_OP_گهڻائي                  0x0BF0
#وصف_ڪريو GL_SCISSOR_BOX                    0x0C10
#وصف_ڪريو GL_COLOR_CLEAR_قدر              0x0C22
#وصف_ڪريو GL_COLOR_WRITEMASK                0x0C23
#وصف_ڪريو GL_MAX_LIGHTS                     0x0D31
#وصف_ڪريو GL_MAX_CLIP_PLANES                0x0D32
#وصف_ڪريو GL_MAX_TEXTURE_سائيز               0x0D33
#وصف_ڪريو GL_MAX_MODELVIEW_ڍير_اونهائي      0x0D36
#وصف_ڪريو GL_MAX_PROJECTION_ڍير_اونهائي     0x0D38
#وصف_ڪريو GL_MAX_TEXTURE_ڍير_اونهائي        0x0D39
#وصف_ڪريو GL_MAX_VIEWPORT_DIMS              0x0D3A
#وصف_ڪريو GL_MAX_TEXTURE_UNITS              0x84E2
#وصف_ڪريو GL_SUBPIXEL_بٽ                  0x0D50
#وصف_ڪريو GL_RED_بٽ                       0x0D52
#وصف_ڪريو GL_GREEN_بٽ                     0x0D53
#وصف_ڪريو GL_BLUE_بٽ                      0x0D54
#وصف_ڪريو GL_ALPHA_بٽ                     0x0D55
#وصف_ڪريو GL_اونهائي_بٽ                     0x0D56
#وصف_ڪريو GL_STENCIL_بٽ                   0x0D57
#وصف_ڪريو GL_POLYGON_وٿي_UNITS           0x2A00
#وصف_ڪريو GL_POLYGON_وٿي_FILL            0x8037
#وصف_ڪريو GL_POLYGON_وٿي_ضرب_ڪندڙ          0x8038
#وصف_ڪريو GL_TEXTURE_BINDING_2D             0x8069
#وصف_ڪريو GL_راس_ARRAY_سائيز              0x807A
#وصف_ڪريو GL_راس_ARRAY_TYPE              0x807B
#وصف_ڪريو GL_راس_ARRAY_STRIDE            0x807C
#وصف_ڪريو GL_عام_ARRAY_TYPE              0x807E
#وصف_ڪريو GL_عام_ARRAY_STRIDE            0x807F
#وصف_ڪريو GL_COLOR_ARRAY_سائيز               0x8081
#وصف_ڪريو GL_COLOR_ARRAY_TYPE               0x8082
#وصف_ڪريو GL_COLOR_ARRAY_STRIDE             0x8083
#وصف_ڪريو GL_TEXTURE_COORD_ARRAY_سائيز       0x8088
#وصف_ڪريو GL_TEXTURE_COORD_ARRAY_TYPE       0x8089
#وصف_ڪريو GL_TEXTURE_COORD_ARRAY_STRIDE     0x808A
#وصف_ڪريو GL_راس_ARRAY_اشارو           0x808E
#وصف_ڪريو GL_عام_ARRAY_اشارو           0x808F
#وصف_ڪريو GL_COLOR_ARRAY_اشارو            0x8090
#وصف_ڪريو GL_TEXTURE_COORD_ARRAY_اشارو    0x8092
#وصف_ڪريو GL_SAMPLE_BUFFERS                 0x80A8
#وصف_ڪريو GL_SAMPLES                        0x80A9
#وصف_ڪريو GL_SAMPLE_COVERAGE_قدر          0x80AA
#وصف_ڪريو GL_SAMPLE_COVERAGE_INVERT         0x80AB
#وصف_ڪريو GL_انگ_COMPRESSED_TEXTURE_FORMATS 0x86A2
#وصف_ڪريو GL_COMPRESSED_TEXTURE_FORMATS     0x86A3
#وصف_ڪريو GL_DONT_CARE                      0x1100
#وصف_ڪريو GL_FASTEST                        0x1101
#وصف_ڪريو GL_NICEST                         0x1102
#وصف_ڪريو GL_PERSPECTIVE_CORRECTION_HINT    0x0C50
#وصف_ڪريو GL_نقطو_SMOOTH_HINT              0x0C51
#وصف_ڪريو GL_سٽ_SMOOTH_HINT               0x0C52
#وصف_ڪريو GL_FOG_HINT                       0x0C54
#وصف_ڪريو GL_GENERATE_MIPMAP_HINT           0x8192
#وصف_ڪريو GL_LIGHT_MODEL_AMBIENT            0x0B53
#وصف_ڪريو GL_LIGHT_MODEL_TWO_SIDE           0x0B52
#وصف_ڪريو GL_AMBIENT                        0x1200
#وصف_ڪريو GL_DIFFUSE                        0x1201
#وصف_ڪريو GL_SPECULAR                       0x1202
#وصف_ڪريو GL_POSITION                       0x1203
#وصف_ڪريو GL_SPOT_DIRECTION                 0x1204
#وصف_ڪريو GL_SPOT_EXPONENT                  0x1205
#وصف_ڪريو GL_SPOT_CUTOFF                    0x1206
#وصف_ڪريو GL_CONSTANT_ATTENUATION           0x1207
#وصف_ڪريو GL_لڪيري_ATTENUATION             0x1208
#وصف_ڪريو GL_QUADRATIC_ATTENUATION          0x1209
#وصف_ڪريو GL_BYTE                           0x1400
#وصف_ڪريو GL_UNSIGNED_BYTE                  0x1401
#وصف_ڪريو GL_SHORT                          0x1402
#وصف_ڪريو GL_UNSIGNED_SHORT                 0x1403
#وصف_ڪريو GL_FLOAT                          0x1406
#وصف_ڪريو GL_FIXED                          0x140C
#وصف_ڪريو GL_CLEAR                          0x1500
#وصف_ڪريو GL_AND                            0x1501
#وصف_ڪريو GL_AND_ابتو                    0x1502
#وصف_ڪريو GL_COPY                           0x1503
#وصف_ڪريو GL_AND_INVERTED                   0x1504
#وصف_ڪريو GL_NOOP                           0x1505
#وصف_ڪريو GL_XOR                            0x1506
#وصف_ڪريو GL_OR                             0x1507
#وصف_ڪريو GL_NOR                            0x1508
#وصف_ڪريو GL_EQUIV                          0x1509
#وصف_ڪريو GL_INVERT                         0x150A
#وصف_ڪريو GL_OR_ابتو                     0x150B
#وصف_ڪريو GL_COPY_INVERTED                  0x150C
#وصف_ڪريو GL_OR_INVERTED                    0x150D
#وصف_ڪريو GL_NAND                           0x150E
#وصف_ڪريو GL_سيٽ                            0x150F
#وصف_ڪريو GL_EMISSION                       0x1600
#وصف_ڪريو GL_SHININESS                      0x1601
#وصف_ڪريو GL_AMBIENT_AND_DIFFUSE            0x1602
#وصف_ڪريو GL_MODELVIEW                      0x1700
#وصف_ڪريو GL_PROJECTION                     0x1701
#وصف_ڪريو GL_TEXTURE                        0x1702
#وصف_ڪريو GL_ALPHA                          0x1906
#وصف_ڪريو GL_RGB                            0x1907
#وصف_ڪريو GL_RGBA                           0x1908
#وصف_ڪريو GL_LUMINANCE                      0x1909
#وصف_ڪريو GL_LUMINANCE_ALPHA                0x190A
#وصف_ڪريو GL_UNPACK_ALIGNMENT               0x0CF5
#وصف_ڪريو GL_PACK_ALIGNMENT                 0x0D05
#وصف_ڪريو GL_UNSIGNED_SHORT_4_4_4_4         0x8033
#وصف_ڪريو GL_UNSIGNED_SHORT_5_5_5_1         0x8034
#وصف_ڪريو GL_UNSIGNED_SHORT_5_6_5           0x8363
#وصف_ڪريو GL_FLAT                           0x1D00
#وصف_ڪريو GL_SMOOTH                         0x1D01
#وصف_ڪريو GL_KEEP                           0x1E00
#وصف_ڪريو GL_REPLACE                        0x1E01
#وصف_ڪريو GL_INCR                           0x1E02
#وصف_ڪريو GL_DECR                           0x1E03
#وصف_ڪريو GL_VENDOR                         0x1F00
#وصف_ڪريو GL_RENDERER                       0x1F01
#وصف_ڪريو GL_نسخو                        0x1F02
#وصف_ڪريو GL_EXTENSIONS                     0x1F03
#وصف_ڪريو GL_MODULATE                       0x2100
#وصف_ڪريو GL_DECAL                          0x2101
#وصف_ڪريو GL_جوڙيو                            0x0104
#وصف_ڪريو GL_TEXTURE_ENV_گهڻائي               0x2200
#وصف_ڪريو GL_TEXTURE_ENV_COLOR              0x2201
#وصف_ڪريو GL_TEXTURE_ENV                    0x2300
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
#وصف_ڪريو GL_GENERATE_MIPMAP                0x8191
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
#وصف_ڪريو GL_CLIENT_سرگرم_TEXTURE          0x84E1
#وصف_ڪريو GL_REPEAT                         0x2901
#وصف_ڪريو GL_CLAMP_منزل_ڪنارو                  0x812F
#وصف_ڪريو GL_LIGHT0                         0x4000
#وصف_ڪريو GL_LIGHT1                         0x4001
#وصف_ڪريو GL_LIGHT2                         0x4002
#وصف_ڪريو GL_LIGHT3                         0x4003
#وصف_ڪريو GL_LIGHT4                         0x4004
#وصف_ڪريو GL_LIGHT5                         0x4005
#وصف_ڪريو GL_LIGHT6                         0x4006
#وصف_ڪريو GL_LIGHT7                         0x4007
#وصف_ڪريو GL_ARRAY_بفر                   0x8892
#وصف_ڪريو GL_ELEMENT_ARRAY_بفر           0x8893
#وصف_ڪريو GL_ARRAY_بفر_BINDING           0x8894
#وصف_ڪريو GL_ELEMENT_ARRAY_بفر_BINDING   0x8895
#وصف_ڪريو GL_راس_ARRAY_بفر_BINDING    0x8896
#وصف_ڪريو GL_عام_ARRAY_بفر_BINDING    0x8897
#وصف_ڪريو GL_COLOR_ARRAY_بفر_BINDING     0x8898
#وصف_ڪريو GL_TEXTURE_COORD_ARRAY_بفر_BINDING 0x889A
#وصف_ڪريو GL_STATIC_DRAW                    0x88E4
#وصف_ڪريو GL_DYNAMIC_DRAW                   0x88E8
#وصف_ڪريو GL_بفر_سائيز                    0x8764
#وصف_ڪريو GL_بفر_USAGE                   0x8765
#وصف_ڪريو GL_ڪٽيو                       0x84E7
#وصف_ڪريو GL_COMBINE                        0x8570
#وصف_ڪريو GL_COMBINE_RGB                    0x8571
#وصف_ڪريو GL_COMBINE_ALPHA                  0x8572
#وصف_ڪريو GL_RGB_SCALE                      0x8573
#وصف_ڪريو GL_جوڙيو_SIGNED                     0x8574
#وصف_ڪريو GL_INTERPOLATE                    0x8575
#وصف_ڪريو GL_CONSTANT                       0x8576
#وصف_ڪريو GL_PRIMARY_COLOR                  0x8577
#وصف_ڪريو GL_اڳيون                       0x8578
#وصف_ڪريو GL_OPERAND0_RGB                   0x8590
#وصف_ڪريو GL_OPERAND1_RGB                   0x8591
#وصف_ڪريو GL_OPERAND2_RGB                   0x8592
#وصف_ڪريو GL_OPERAND0_ALPHA                 0x8598
#وصف_ڪريو GL_OPERAND1_ALPHA                 0x8599
#وصف_ڪريو GL_OPERAND2_ALPHA                 0x859A
#وصف_ڪريو GL_ALPHA_SCALE                    0x0D1C
#وصف_ڪريو GL_SRC0_RGB                       0x8580
#وصف_ڪريو GL_SRC1_RGB                       0x8581
#وصف_ڪريو GL_SRC2_RGB                       0x8582
#وصف_ڪريو GL_SRC0_ALPHA                     0x8588
#وصف_ڪريو GL_SRC1_ALPHA                     0x8589
#وصف_ڪريو GL_SRC2_ALPHA                     0x858A
#وصف_ڪريو GL_DOT3_RGB                       0x86AE
#وصف_ڪريو GL_DOT3_RGBA                      0x86AF
GL_API فراغ GL_APIENTRY glAlphaFunc (GLenum func, GLfloat ref);
GL_API فراغ GL_APIENTRY glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_API فراغ GL_APIENTRY glClearDepthf (GLfloat d);
GL_API فراغ GL_APIENTRY glClipPlanef (GLenum p, ثابت GLfloat *eqn);
GL_API فراغ GL_APIENTRY glColor4f (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_API فراغ GL_APIENTRY gl_اونهائي_Rangef (GLfloat n, GLfloat f);
GL_API فراغ GL_APIENTRY glFogf (GLenum pname, GLfloat param);
GL_API فراغ GL_APIENTRY glFogfv (GLenum pname, ثابت GLfloat *params);
GL_API فراغ GL_APIENTRY glFrustumf (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
GL_API فراغ GL_APIENTRY glGetClipPlanef (GLenum plane, GLfloat *equation);
GL_API فراغ GL_APIENTRY glGetFloatv (GLenum pname, GLfloat *معلومات);
GL_API فراغ GL_APIENTRY glGetLightfv (GLenum light, GLenum pname, GLfloat *params);
GL_API فراغ GL_APIENTRY glGetMaterialfv (GLenum face, GLenum pname, GLfloat *params);
GL_API فراغ GL_APIENTRY glGetTexEnvfv (GLenum هدف, GLenum pname, GLfloat *params);
GL_API فراغ GL_APIENTRY glGetTexParameterfv (GLenum هدف, GLenum pname, GLfloat *params);
GL_API فراغ GL_APIENTRY glLightModelf (GLenum pname, GLfloat param);
GL_API فراغ GL_APIENTRY glLightModelfv (GLenum pname, ثابت GLfloat *params);
GL_API فراغ GL_APIENTRY glLightf (GLenum light, GLenum pname, GLfloat param);
GL_API فراغ GL_APIENTRY glLightfv (GLenum light, GLenum pname, ثابت GLfloat *params);
GL_API فراغ GL_APIENTRY gl_سٽ_ويڪر (GLfloat ويڪر);
GL_API فراغ GL_APIENTRY gl_ڀريو_Matrixf (ثابت GLfloat *m);
GL_API فراغ GL_APIENTRY glMaterialf (GLenum face, GLenum pname, GLfloat param);
GL_API فراغ GL_APIENTRY glMaterialfv (GLenum face, GLenum pname, ثابت GLfloat *params);
GL_API فراغ GL_APIENTRY glMultMatrixf (ثابت GLfloat *m);
GL_API فراغ GL_APIENTRY glMultiTexCoord4f (GLenum هدف, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
GL_API فراغ GL_APIENTRY glNormal3f (GLfloat nx, GLfloat ny, GLfloat nz);
GL_API فراغ GL_APIENTRY glOrthof (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
GL_API فراغ GL_APIENTRY gl_نقطو_Parameterf (GLenum pname, GLfloat param);
GL_API فراغ GL_APIENTRY gl_نقطو_Parameterfv (GLenum pname, ثابت GLfloat *params);
GL_API فراغ GL_APIENTRY gl_نقطو_سائيز (GLfloat سائيز);
GL_API فراغ GL_APIENTRY gl_Polygon_وٿي (GLfloat ضرب_ڪندڙ, GLfloat units);
GL_API فراغ GL_APIENTRY glRotatef (GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
GL_API فراغ GL_APIENTRY glScalef (GLfloat x, GLfloat y, GLfloat z);
GL_API فراغ GL_APIENTRY glTexEnvf (GLenum هدف, GLenum pname, GLfloat param);
GL_API فراغ GL_APIENTRY glTexEnvfv (GLenum هدف, GLenum pname, ثابت GLfloat *params);
GL_API فراغ GL_APIENTRY glTexParameterf (GLenum هدف, GLenum pname, GLfloat param);
GL_API فراغ GL_APIENTRY glTexParameterfv (GLenum هدف, GLenum pname, ثابت GLfloat *params);
GL_API فراغ GL_APIENTRY glTranslatef (GLfloat x, GLfloat y, GLfloat z);
GL_API فراغ GL_APIENTRY gl_سرگرم_Texture (GLenum texture);
GL_API فراغ GL_APIENTRY glAlphaFuncx (GLenum func, GLfixed ref);
GL_API فراغ GL_APIENTRY gl_Bind_بفر (GLenum هدف, GLuint بفر_2);
GL_API فراغ GL_APIENTRY glBindTexture (GLenum هدف, GLuint texture);
GL_API فراغ GL_APIENTRY glBlendFunc (GLenum sfactor, GLenum dfactor);
GL_API فراغ GL_APIENTRY gl_بفر_معلومات (GLenum هدف, GLsizeiptr سائيز, ثابت فراغ *معلومات, GLenum usage);
GL_API فراغ GL_APIENTRY gl_بفر_Sub_معلومات (GLenum هدف, GLintptr وٿي_2, GLsizeiptr سائيز, ثابت فراغ *معلومات);
GL_API فراغ GL_APIENTRY glClear (GLbitfield نقاب);
GL_API فراغ GL_APIENTRY glClearColorx (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GL_API فراغ GL_APIENTRY glClearDepthx (GLfixed اونهائي_2);
GL_API فراغ GL_APIENTRY glClearStencil (GLint s);
GL_API فراغ GL_APIENTRY gl_Client_سرگرم_Texture (GLenum texture);
GL_API فراغ GL_APIENTRY glClipPlanex (GLenum plane, ثابت GLfixed *equation);
GL_API فراغ GL_APIENTRY glColor4ub (GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
GL_API فراغ GL_APIENTRY glColor4x (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GL_API فراغ GL_APIENTRY gl_Color_نقاب (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
GL_API فراغ GL_APIENTRY gl_Color_اشارو (GLint سائيز, GLenum type, GLsizei stride, ثابت فراغ *اشارو_2);
GL_API فراغ GL_APIENTRY glCompressedTexImage2D (GLenum هدف, GLint level, GLenum internalformat, GLsizei ويڪر, GLsizei اوچائي, GLint border, GLsizei image_سائيز, ثابت فراغ *معلومات);
GL_API فراغ GL_APIENTRY glCompressedTexSubImage2D (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLsizei ويڪر, GLsizei اوچائي, GLenum format, GLsizei image_سائيز, ثابت فراغ *معلومات);
GL_API فراغ GL_APIENTRY glCopyTexImage2D (GLenum هدف, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei ويڪر, GLsizei اوچائي, GLint border);
GL_API فراغ GL_APIENTRY glCopyTexSubImage2D (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei ويڪر, GLsizei اوچائي);
GL_API فراغ GL_APIENTRY glCullFace (GLenum گهڻائي);
GL_API فراغ GL_APIENTRY glDeleteBuffers (GLsizei n, ثابت GLuint *buffers);
GL_API فراغ GL_APIENTRY glDeleteTextures (GLsizei n, ثابت GLuint *textures);
GL_API فراغ GL_APIENTRY gl_اونهائي_Func (GLenum func);
GL_API فراغ GL_APIENTRY gl_اونهائي_نقاب (GLboolean flag);
GL_API فراغ GL_APIENTRY gl_اونهائي_Rangex (GLfixed n, GLfixed f);
GL_API فراغ GL_APIENTRY glDisable (GLenum cap);
GL_API فراغ GL_APIENTRY glDisableClientState (GLenum array);
GL_API فراغ GL_APIENTRY glDrawArrays (GLenum گهڻائي, GLint پهريون, GLsizei ڳڻپ);
GL_API فراغ GL_APIENTRY glDrawElements (GLenum گهڻائي, GLsizei ڳڻپ, GLenum type, ثابت فراغ *indices);
GL_API فراغ GL_APIENTRY glEnable (GLenum cap);
GL_API فراغ GL_APIENTRY glEnableClientState (GLenum array);
GL_API فراغ GL_APIENTRY gl_پڄاڻي (فراغ);
GL_API فراغ GL_APIENTRY glFlush (فراغ);
GL_API فراغ GL_APIENTRY glFogx (GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glFogxv (GLenum pname, ثابت GLfixed *param);
GL_API فراغ GL_APIENTRY glFrontFace (GLenum گهڻائي);
GL_API فراغ GL_APIENTRY glFrustumx (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
GL_API فراغ GL_APIENTRY glGetBooleanv (GLenum pname, GLboolean *معلومات);
GL_API فراغ GL_APIENTRY gl_Get_بفر_Parameteriv (GLenum هدف, GLenum pname, GLint *params);
GL_API فراغ GL_APIENTRY glGetClipPlanex (GLenum plane, GLfixed *equation);
GL_API فراغ GL_APIENTRY glGenBuffers (GLsizei n, GLuint *buffers);
GL_API فراغ GL_APIENTRY glGenTextures (GLsizei n, GLuint *textures);
GL_API GLenum GL_APIENTRY glGetError (فراغ);
GL_API فراغ GL_APIENTRY glGetFixedv (GLenum pname, GLfixed *معلومات);
GL_API فراغ GL_APIENTRY glGetIntegerv (GLenum pname, GLint *معلومات);
GL_API فراغ GL_APIENTRY glGetLightxv (GLenum light, GLenum pname, GLfixed *params);
GL_API فراغ GL_APIENTRY glGetMaterialxv (GLenum face, GLenum pname, GLfixed *params);
GL_API فراغ GL_APIENTRY glGetPointerv (GLenum pname, فراغ **params);
GL_API ثابت GLubyte *GL_APIENTRY glGetString (GLenum name);
GL_API فراغ GL_APIENTRY glGetTexEnviv (GLenum هدف, GLenum pname, GLint *params);
GL_API فراغ GL_APIENTRY glGetTexEnvxv (GLenum هدف, GLenum pname, GLfixed *params);
GL_API فراغ GL_APIENTRY glGetTexParameteriv (GLenum هدف, GLenum pname, GLint *params);
GL_API فراغ GL_APIENTRY glGetTexParameterxv (GLenum هدف, GLenum pname, GLfixed *params);
GL_API فراغ GL_APIENTRY glHint (GLenum هدف, GLenum گهڻائي);
GL_API GLboolean GL_APIENTRY gl_Is_بفر (GLuint بفر_2);
GL_API GLboolean GL_APIENTRY glIsEnabled (GLenum cap);
GL_API GLboolean GL_APIENTRY glIsTexture (GLuint texture);
GL_API فراغ GL_APIENTRY glLightModelx (GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glLightModelxv (GLenum pname, ثابت GLfixed *param);
GL_API فراغ GL_APIENTRY glLightx (GLenum light, GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glLightxv (GLenum light, GLenum pname, ثابت GLfixed *params);
GL_API فراغ GL_APIENTRY gl_سٽ_Widthx (GLfixed ويڪر);
GL_API فراغ GL_APIENTRY gl_ڀريو_سڃاڻپ_عنصر (فراغ);
GL_API فراغ GL_APIENTRY gl_ڀريو_Matrixx (ثابت GLfixed *m);
GL_API فراغ GL_APIENTRY glLogicOp (GLenum opcode);
GL_API فراغ GL_APIENTRY glMaterialx (GLenum face, GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glMaterialxv (GLenum face, GLenum pname, ثابت GLfixed *param);
GL_API فراغ GL_APIENTRY gl_ميٽرڪس_گهڻائي (GLenum گهڻائي);
GL_API فراغ GL_APIENTRY glMultMatrixx (ثابت GLfixed *m);
GL_API فراغ GL_APIENTRY glMultiTexCoord4x (GLenum texture, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
GL_API فراغ GL_APIENTRY glNormal3x (GLfixed nx, GLfixed ny, GLfixed nz);
GL_API فراغ GL_APIENTRY gl_عام_اشارو (GLenum type, GLsizei stride, ثابت فراغ *اشارو_2);
GL_API فراغ GL_APIENTRY glOrthox (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
GL_API فراغ GL_APIENTRY glPixelStorei (GLenum pname, GLint param);
GL_API فراغ GL_APIENTRY gl_نقطو_Parameterx (GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY gl_نقطو_Parameterxv (GLenum pname, ثابت GLfixed *params);
GL_API فراغ GL_APIENTRY gl_نقطو_Sizex (GLfixed سائيز);
GL_API فراغ GL_APIENTRY glPolygonOffsetx (GLfixed ضرب_ڪندڙ, GLfixed units);
GL_API فراغ GL_APIENTRY gl_ڪڍو_ميٽرڪس (فراغ);
GL_API فراغ GL_APIENTRY gl_ڌڪو_ميٽرڪس (فراغ);
GL_API فراغ GL_APIENTRY glReadPixels (GLint x, GLint y, GLsizei ويڪر, GLsizei اوچائي, GLenum format, GLenum type, فراغ *pixels);
GL_API فراغ GL_APIENTRY glRotatex (GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
GL_API فراغ GL_APIENTRY glSampleCoverage (GLfloat قدر, GLboolean invert);
GL_API فراغ GL_APIENTRY glSampleCoveragex (GLclampx قدر, GLboolean invert);
GL_API فراغ GL_APIENTRY glScalex (GLfixed x, GLfixed y, GLfixed z);
GL_API فراغ GL_APIENTRY glScissor (GLint x, GLint y, GLsizei ويڪر, GLsizei اوچائي);
GL_API فراغ GL_APIENTRY glShadeModel (GLenum گهڻائي);
GL_API فراغ GL_APIENTRY glStencilFunc (GLenum func, GLint ref, GLuint نقاب);
GL_API فراغ GL_APIENTRY gl_Stencil_نقاب (GLuint نقاب);
GL_API فراغ GL_APIENTRY glStencilOp (GLenum fail, GLenum zfail, GLenum zpass);
GL_API فراغ GL_APIENTRY gl_Tex_Coord_اشارو (GLint سائيز, GLenum type, GLsizei stride, ثابت فراغ *اشارو_2);
GL_API فراغ GL_APIENTRY glTexEnvi (GLenum هدف, GLenum pname, GLint param);
GL_API فراغ GL_APIENTRY glTexEnvx (GLenum هدف, GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glTexEnviv (GLenum هدف, GLenum pname, ثابت GLint *params);
GL_API فراغ GL_APIENTRY glTexEnvxv (GLenum هدف, GLenum pname, ثابت GLfixed *params);
GL_API فراغ GL_APIENTRY glTexImage2D (GLenum هدف, GLint level, GLint internalformat, GLsizei ويڪر, GLsizei اوچائي, GLint border, GLenum format, GLenum type, ثابت فراغ *pixels);
GL_API فراغ GL_APIENTRY glTexParameteri (GLenum هدف, GLenum pname, GLint param);
GL_API فراغ GL_APIENTRY glTexParameterx (GLenum هدف, GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glTexParameteriv (GLenum هدف, GLenum pname, ثابت GLint *params);
GL_API فراغ GL_APIENTRY glTexParameterxv (GLenum هدف, GLenum pname, ثابت GLfixed *params);
GL_API فراغ GL_APIENTRY glTexSubImage2D (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLsizei ويڪر, GLsizei اوچائي, GLenum format, GLenum type, ثابت فراغ *pixels);
GL_API فراغ GL_APIENTRY glTranslatex (GLfixed x, GLfixed y, GLfixed z);
GL_API فراغ GL_APIENTRY gl_راس_اشارو (GLint سائيز, GLenum type, GLsizei stride, ثابت فراغ *اشارو_2);
GL_API فراغ GL_APIENTRY glViewport (GLint x, GLint y, GLsizei ويڪر, GLsizei اوچائي);
#جيڪڏهن_پورو /* GL_VERSION_ES_CM_1_0 */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_compressed_paletted_texture
#وصف_ڪريو GL_OES_compressed_paletted_texture 1
#وصف_ڪريو GL_PALETTE4_RGB8_OES              0x8B90
#وصف_ڪريو GL_PALETTE4_RGBA8_OES             0x8B91
#وصف_ڪريو GL_PALETTE4_R5_G6_B5_OES          0x8B92
#وصف_ڪريو GL_PALETTE4_RGBA4_OES             0x8B93
#وصف_ڪريو GL_PALETTE4_RGB5_A1_OES           0x8B94
#وصف_ڪريو GL_PALETTE8_RGB8_OES              0x8B95
#وصف_ڪريو GL_PALETTE8_RGBA8_OES             0x8B96
#وصف_ڪريو GL_PALETTE8_R5_G6_B5_OES          0x8B97
#وصف_ڪريو GL_PALETTE8_RGBA4_OES             0x8B98
#وصف_ڪريو GL_PALETTE8_RGB5_A1_OES           0x8B99
#جيڪڏهن_پورو /* GL_OES_compressed_paletted_texture */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_نقطو_سائيز_array
#وصف_ڪريو GL_OES_نقطو_سائيز_array 1
#وصف_ڪريو GL_نقطو_سائيز_ARRAY_OES           0x8B9C
#وصف_ڪريو GL_نقطو_سائيز_ARRAY_TYPE_OES      0x898A
#وصف_ڪريو GL_نقطو_سائيز_ARRAY_STRIDE_OES    0x898B
#وصف_ڪريو GL_نقطو_سائيز_ARRAY_اشارو_OES   0x898C
#وصف_ڪريو GL_نقطو_سائيز_ARRAY_بفر_BINDING_OES 0x8B9F
GL_API فراغ GL_APIENTRY gl_نقطو_سائيز_اشارو_OES (GLenum type, GLsizei stride, ثابت فراغ *اشارو_2);
#جيڪڏهن_پورو /* GL_OES_point_size_array */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_نقطو_sprite
#وصف_ڪريو GL_OES_نقطو_sprite 1
#وصف_ڪريو GL_نقطو_SPRITE_OES               0x8861
#وصف_ڪريو GL_COORD_REPLACE_OES              0x8862
#جيڪڏهن_پورو /* GL_OES_point_sprite */

#جيڪڏهن_وصف_نه_ٿيل GL_OES_read_format
#وصف_ڪريو GL_OES_read_format 1
#وصف_ڪريو GL_IMPLEMENTATION_COLOR_READ_TYPE_OES 0x8B9A
#وصف_ڪريو GL_IMPLEMENTATION_COLOR_READ_FORMAT_OES 0x8B9B
#جيڪڏهن_پورو /* GL_OES_read_format */

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو
