#که_نه_تعریف_شوی __gles1_gl_h_
#تعریف_کړه __gles1_gl_h_ 1

#که_تعریف_شوی __cplusplus
خارجي "C" {
#د_که_پای

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

#که_نه_تعریف_شوی GL_نسخه_ES_CM_1_0
#تعریف_کړه GL_نسخه_ES_CM_1_0 1
#ضمن <KHR/khrplatform.h>
تعريفنوع khronos_int8_t GLbyte;
تعريفنوع khronos_float_t GLclampf;
تعريفنوع khronos_int16_t GLshort;
تعريفنوع khronos_uint16_t GLushort;
تعريفنوع فراغ GLvoid;
تعريفنوع بینښه صحيح GLenum;
تعريفنوع khronos_float_t GLfloat;
تعريفنوع khronos_int32_t GLfixed;
تعريفنوع بینښه صحيح GLuint;
تعريفنوع khronos_ssize_t GLsizeiptr;
تعريفنوع khronos_intptr_t GLintptr;
تعريفنوع بینښه صحيح GLbitfield;
تعريفنوع صحيح GLint;
تعريفنوع khronos_uint8_t GLubyte;
تعريفنوع بینښه حرف GLboolean;
تعريفنوع صحيح GLsizei;
تعريفنوع khronos_int32_t GLclampx;
#تعریف_کړه GL_نسخه_ES_CL_1_0              1
#تعریف_کړه GL_نسخه_ES_CM_1_1              1
#تعریف_کړه GL_نسخه_ES_CL_1_1              1
#تعریف_کړه GL_ژوروالی_بفر_بټ               0x00000100
#تعریف_کړه GL_STENCIL_بفر_بټ             0x00000400
#تعریف_کړه GL_COLOR_بفر_بټ               0x00004000
#تعریف_کړه GL_FALSE                          0
#تعریف_کړه GL_TRUE                           1
#تعریف_کړه GL_POINTS                         0x0000
#تعریف_کړه GL_کرښې                          0x0001
#تعریف_کړه GL_کرښه_LOOP                      0x0002
#تعریف_کړه GL_کرښه_STRIP                     0x0003
#تعریف_کړه GL_TRIANGLES                      0x0004
#تعریف_کړه GL_TRIANGLE_STRIP                 0x0005
#تعریف_کړه GL_TRIANGLE_FAN                   0x0006
#تعریف_کړه GL_NEVER                          0x0200
#تعریف_کړه GL_LESS                           0x0201
#تعریف_کړه GL_EQUAL                          0x0202
#تعریف_کړه GL_LEQUAL                         0x0203
#تعریف_کړه GL_GREATER                        0x0204
#تعریف_کړه GL_NOTEQUAL                       0x0205
#تعریف_کړه GL_GEQUAL                         0x0206
#تعریف_کړه GL_ALWAYS                         0x0207
#تعریف_کړه GL_ZERO                           0
#تعریف_کړه GL_ONE                            1
#تعریف_کړه GL_SRC_COLOR                      0x0300
#تعریف_کړه GL_ONE_MINUS_SRC_COLOR            0x0301
#تعریف_کړه GL_SRC_ALPHA                      0x0302
#تعریف_کړه GL_ONE_MINUS_SRC_ALPHA            0x0303
#تعریف_کړه GL_DST_ALPHA                      0x0304
#تعریف_کړه GL_ONE_MINUS_DST_ALPHA            0x0305
#تعریف_کړه GL_DST_COLOR                      0x0306
#تعریف_کړه GL_ONE_MINUS_DST_COLOR            0x0307
#تعریف_کړه GL_SRC_ALPHA_SATURATE             0x0308
#تعریف_کړه GL_CLIP_PLANE0                    0x3000
#تعریف_کړه GL_CLIP_PLANE1                    0x3001
#تعریف_کړه GL_CLIP_PLANE2                    0x3002
#تعریف_کړه GL_CLIP_PLANE3                    0x3003
#تعریف_کړه GL_CLIP_PLANE4                    0x3004
#تعریف_کړه GL_CLIP_PLANE5                    0x3005
#تعریف_کړه GL_FRONT                          0x0404
#تعریف_کړه GL_شا                           0x0405
#تعریف_کړه GL_FRONT_AND_شا                 0x0408
#تعریف_کړه GL_FOG                            0x0B60
#تعریف_کړه GL_LIGHTING                       0x0B50
#تعریف_کړه GL_TEXTURE_2D                     0x0DE1
#تعریف_کړه GL_CULL_FACE                      0x0B44
#تعریف_کړه GL_ALPHA_TEST                     0x0BC0
#تعریف_کړه GL_BLEND                          0x0BE2
#تعریف_کړه GL_COLOR_LOGIC_OP                 0x0BF2
#تعریف_کړه GL_DITHER                         0x0BD0
#تعریف_کړه GL_STENCIL_TEST                   0x0B90
#تعریف_کړه GL_ژوروالی_TEST                     0x0B71
#تعریف_کړه GL_ټکی_SMOOTH                   0x0B10
#تعریف_کړه GL_کرښه_SMOOTH                    0x0B20
#تعریف_کړه GL_SCISSOR_TEST                   0x0C11
#تعریف_کړه GL_COLOR_MATERIAL                 0x0B57
#تعریف_کړه GL_NORMALIZE                      0x0BA1
#تعریف_کړه GL_RESCALE_نورمال                 0x803A
#تعریف_کړه GL_راس_ARRAY                   0x8074
#تعریف_کړه GL_نورمال_ARRAY                   0x8075
#تعریف_کړه GL_COLOR_ARRAY                    0x8076
#تعریف_کړه GL_TEXTURE_COORD_ARRAY            0x8078
#تعریف_کړه GL_MULTISAMPLE                    0x809D
#تعریف_کړه GL_SAMPLE_ALPHA_منزل_COVERAGE       0x809E
#تعریف_کړه GL_SAMPLE_ALPHA_منزل_ONE            0x809F
#تعریف_کړه GL_SAMPLE_COVERAGE                0x80A0
#تعریف_کړه GL_NO_ERROR                       0
#تعریف_کړه GL_INVALID_ENUM                   0x0500
#تعریف_کړه GL_INVALID_ارزښت                  0x0501
#تعریف_کړه GL_INVALID_OPERATION              0x0502
#تعریف_کړه GL_ډېری_ډکېدنه                 0x0503
#تعریف_کړه GL_ډېری_UNDERFLOW                0x0504
#تعریف_کړه GL_بهر_د_حافظه                  0x0505
#تعریف_کړه GL_EXP                            0x0800
#تعریف_کړه GL_EXP2                           0x0801
#تعریف_کړه GL_FOG_DENSITY                    0x0B62
#تعریف_کړه GL_FOG_پیل                      0x0B63
#تعریف_کړه GL_FOG_پای_ټکی                        0x0B64
#تعریف_کړه GL_FOG_ډېرپېښ                       0x0B65
#تعریف_کړه GL_FOG_COLOR                      0x0B66
#تعریف_کړه GL_CW                             0x0900
#تعریف_کړه GL_CCW                            0x0901
#تعریف_کړه GL_CURRENT_COLOR                  0x0B00
#تعریف_کړه GL_CURRENT_نورمال                 0x0B02
#تعریف_کړه GL_CURRENT_TEXTURE_COORDS         0x0B03
#تعریف_کړه GL_ټکی_اندازه                     0x0B11
#تعریف_کړه GL_ټکی_اندازه_MIN                 0x8126
#تعریف_کړه GL_ټکی_اندازه_MAX                 0x8127
#تعریف_کړه GL_ټکی_FADE_پوله_اندازه      0x8128
#تعریف_کړه GL_ټکی_واټن_ATTENUATION     0x8129
#تعریف_کړه GL_SMOOTH_ټکی_اندازه_RANGE        0x0B12
#تعریف_کړه GL_کرښه_پلنوالی                     0x0B21
#تعریف_کړه GL_SMOOTH_کرښه_پلنوالی_RANGE        0x0B22
#تعریف_کړه GL_ALIASED_ټکی_اندازه_RANGE       0x846D
#تعریف_کړه GL_ALIASED_کرښه_پلنوالی_RANGE       0x846E
#تعریف_کړه GL_CULL_FACE_ډېرپېښ                 0x0B45
#تعریف_کړه GL_FRONT_FACE                     0x0B46
#تعریف_کړه GL_SHADE_MODEL                    0x0B54
#تعریف_کړه GL_ژوروالی_RANGE                    0x0B70
#تعریف_کړه GL_ژوروالی_WRITEMASK                0x0B72
#تعریف_کړه GL_ژوروالی_CLEAR_ارزښت              0x0B73
#تعریف_کړه GL_ژوروالی_FUNC                     0x0B74
#تعریف_کړه GL_STENCIL_CLEAR_ارزښت            0x0B91
#تعریف_کړه GL_STENCIL_FUNC                   0x0B92
#تعریف_کړه GL_STENCIL_ارزښت_ماسک             0x0B93
#تعریف_کړه GL_STENCIL_FAIL                   0x0B94
#تعریف_کړه GL_STENCIL_PASS_ژوروالی_FAIL        0x0B95
#تعریف_کړه GL_STENCIL_PASS_ژوروالی_PASS        0x0B96
#تعریف_کړه GL_STENCIL_REF                    0x0B97
#تعریف_کړه GL_STENCIL_WRITEMASK              0x0B98
#تعریف_کړه GL_ماتریکس_ډېرپېښ                    0x0BA0
#تعریف_کړه GL_VIEWPORT                       0x0BA2
#تعریف_کړه GL_MODELVIEW_ډېری_ژوروالی          0x0BA3
#تعریف_کړه GL_PROJECTION_ډېری_ژوروالی         0x0BA4
#تعریف_کړه GL_TEXTURE_ډېری_ژوروالی            0x0BA5
#تعریف_کړه GL_MODELVIEW_ماتریکس               0x0BA6
#تعریف_کړه GL_PROJECTION_ماتریکس              0x0BA7
#تعریف_کړه GL_TEXTURE_ماتریکس                 0x0BA8
#تعریف_کړه GL_ALPHA_TEST_FUNC                0x0BC1
#تعریف_کړه GL_ALPHA_TEST_REF                 0x0BC2
#تعریف_کړه GL_BLEND_DST                      0x0BE0
#تعریف_کړه GL_BLEND_SRC                      0x0BE1
#تعریف_کړه GL_LOGIC_OP_ډېرپېښ                  0x0BF0
#تعریف_کړه GL_SCISSOR_BOX                    0x0C10
#تعریف_کړه GL_COLOR_CLEAR_ارزښت              0x0C22
#تعریف_کړه GL_COLOR_WRITEMASK                0x0C23
#تعریف_کړه GL_MAX_LIGHTS                     0x0D31
#تعریف_کړه GL_MAX_CLIP_PLANES                0x0D32
#تعریف_کړه GL_MAX_TEXTURE_اندازه               0x0D33
#تعریف_کړه GL_MAX_MODELVIEW_ډېری_ژوروالی      0x0D36
#تعریف_کړه GL_MAX_PROJECTION_ډېری_ژوروالی     0x0D38
#تعریف_کړه GL_MAX_TEXTURE_ډېری_ژوروالی        0x0D39
#تعریف_کړه GL_MAX_VIEWPORT_DIMS              0x0D3A
#تعریف_کړه GL_MAX_TEXTURE_UNITS              0x84E2
#تعریف_کړه GL_SUBPIXEL_بټونه                  0x0D50
#تعریف_کړه GL_RED_بټونه                       0x0D52
#تعریف_کړه GL_GREEN_بټونه                     0x0D53
#تعریف_کړه GL_BLUE_بټونه                      0x0D54
#تعریف_کړه GL_ALPHA_بټونه                     0x0D55
#تعریف_کړه GL_ژوروالی_بټونه                     0x0D56
#تعریف_کړه GL_STENCIL_بټونه                   0x0D57
#تعریف_کړه GL_POLYGON_دننه_واټن_UNITS           0x2A00
#تعریف_کړه GL_POLYGON_دننه_واټن_FILL            0x8037
#تعریف_کړه GL_POLYGON_دننه_واټن_ضریب          0x8038
#تعریف_کړه GL_TEXTURE_BINDING_2D             0x8069
#تعریف_کړه GL_راس_ARRAY_اندازه              0x807A
#تعریف_کړه GL_راس_ARRAY_TYPE              0x807B
#تعریف_کړه GL_راس_ARRAY_STRIDE            0x807C
#تعریف_کړه GL_نورمال_ARRAY_TYPE              0x807E
#تعریف_کړه GL_نورمال_ARRAY_STRIDE            0x807F
#تعریف_کړه GL_COLOR_ARRAY_اندازه               0x8081
#تعریف_کړه GL_COLOR_ARRAY_TYPE               0x8082
#تعریف_کړه GL_COLOR_ARRAY_STRIDE             0x8083
#تعریف_کړه GL_TEXTURE_COORD_ARRAY_اندازه       0x8088
#تعریف_کړه GL_TEXTURE_COORD_ARRAY_TYPE       0x8089
#تعریف_کړه GL_TEXTURE_COORD_ARRAY_STRIDE     0x808A
#تعریف_کړه GL_راس_ARRAY_اشاره_ګر           0x808E
#تعریف_کړه GL_نورمال_ARRAY_اشاره_ګر           0x808F
#تعریف_کړه GL_COLOR_ARRAY_اشاره_ګر            0x8090
#تعریف_کړه GL_TEXTURE_COORD_ARRAY_اشاره_ګر    0x8092
#تعریف_کړه GL_SAMPLE_BUFFERS                 0x80A8
#تعریف_کړه GL_SAMPLES                        0x80A9
#تعریف_کړه GL_SAMPLE_COVERAGE_ارزښت          0x80AA
#تعریف_کړه GL_SAMPLE_COVERAGE_INVERT         0x80AB
#تعریف_کړه GL_عدد_COMPRESSED_TEXTURE_FORMATS 0x86A2
#تعریف_کړه GL_COMPRESSED_TEXTURE_FORMATS     0x86A3
#تعریف_کړه GL_DONT_CARE                      0x1100
#تعریف_کړه GL_FASTEST                        0x1101
#تعریف_کړه GL_NICEST                         0x1102
#تعریف_کړه GL_PERSPECTIVE_CORRECTION_HINT    0x0C50
#تعریف_کړه GL_ټکی_SMOOTH_HINT              0x0C51
#تعریف_کړه GL_کرښه_SMOOTH_HINT               0x0C52
#تعریف_کړه GL_FOG_HINT                       0x0C54
#تعریف_کړه GL_GENERATE_MIPMAP_HINT           0x8192
#تعریف_کړه GL_LIGHT_MODEL_AMBIENT            0x0B53
#تعریف_کړه GL_LIGHT_MODEL_TWO_SIDE           0x0B52
#تعریف_کړه GL_AMBIENT                        0x1200
#تعریف_کړه GL_DIFFUSE                        0x1201
#تعریف_کړه GL_SPECULAR                       0x1202
#تعریف_کړه GL_POSITION                       0x1203
#تعریف_کړه GL_SPOT_DIRECTION                 0x1204
#تعریف_کړه GL_SPOT_EXPONENT                  0x1205
#تعریف_کړه GL_SPOT_CUTOFF                    0x1206
#تعریف_کړه GL_CONSTANT_ATTENUATION           0x1207
#تعریف_کړه GL_خطي_ATTENUATION             0x1208
#تعریف_کړه GL_QUADRATIC_ATTENUATION          0x1209
#تعریف_کړه GL_BYTE                           0x1400
#تعریف_کړه GL_UNSIGNED_BYTE                  0x1401
#تعریف_کړه GL_SHORT                          0x1402
#تعریف_کړه GL_UNSIGNED_SHORT                 0x1403
#تعریف_کړه GL_FLOAT                          0x1406
#تعریف_کړه GL_FIXED                          0x140C
#تعریف_کړه GL_CLEAR                          0x1500
#تعریف_کړه GL_AND                            0x1501
#تعریف_کړه GL_AND_سرچپه                    0x1502
#تعریف_کړه GL_COPY                           0x1503
#تعریف_کړه GL_AND_INVERTED                   0x1504
#تعریف_کړه GL_NOOP                           0x1505
#تعریف_کړه GL_XOR                            0x1506
#تعریف_کړه GL_OR                             0x1507
#تعریف_کړه GL_NOR                            0x1508
#تعریف_کړه GL_EQUIV                          0x1509
#تعریف_کړه GL_INVERT                         0x150A
#تعریف_کړه GL_OR_سرچپه                     0x150B
#تعریف_کړه GL_COPY_INVERTED                  0x150C
#تعریف_کړه GL_OR_INVERTED                    0x150D
#تعریف_کړه GL_NAND                           0x150E
#تعریف_کړه GL_سېټ                            0x150F
#تعریف_کړه GL_EMISSION                       0x1600
#تعریف_کړه GL_SHININESS                      0x1601
#تعریف_کړه GL_AMBIENT_AND_DIFFUSE            0x1602
#تعریف_کړه GL_MODELVIEW                      0x1700
#تعریف_کړه GL_PROJECTION                     0x1701
#تعریف_کړه GL_TEXTURE                        0x1702
#تعریف_کړه GL_ALPHA                          0x1906
#تعریف_کړه GL_RGB                            0x1907
#تعریف_کړه GL_RGBA                           0x1908
#تعریف_کړه GL_LUMINANCE                      0x1909
#تعریف_کړه GL_LUMINANCE_ALPHA                0x190A
#تعریف_کړه GL_UNPACK_ALIGNMENT               0x0CF5
#تعریف_کړه GL_PACK_ALIGNMENT                 0x0D05
#تعریف_کړه GL_UNSIGNED_SHORT_4_4_4_4         0x8033
#تعریف_کړه GL_UNSIGNED_SHORT_5_5_5_1         0x8034
#تعریف_کړه GL_UNSIGNED_SHORT_5_6_5           0x8363
#تعریف_کړه GL_FLAT                           0x1D00
#تعریف_کړه GL_SMOOTH                         0x1D01
#تعریف_کړه GL_KEEP                           0x1E00
#تعریف_کړه GL_REPLACE                        0x1E01
#تعریف_کړه GL_INCR                           0x1E02
#تعریف_کړه GL_DECR                           0x1E03
#تعریف_کړه GL_VENDOR                         0x1F00
#تعریف_کړه GL_RENDERER                       0x1F01
#تعریف_کړه GL_نسخه                        0x1F02
#تعریف_کړه GL_EXTENSIONS                     0x1F03
#تعریف_کړه GL_MODULATE                       0x2100
#تعریف_کړه GL_DECAL                          0x2101
#تعریف_کړه GL_جمع_کړه                            0x0104
#تعریف_کړه GL_TEXTURE_ENV_ډېرپېښ               0x2200
#تعریف_کړه GL_TEXTURE_ENV_COLOR              0x2201
#تعریف_کړه GL_TEXTURE_ENV                    0x2300
#تعریف_کړه GL_تر_ټولو_نږدې                        0x2600
#تعریف_کړه GL_خطي                         0x2601
#تعریف_کړه GL_تر_ټولو_نږدې_MIPMAP_تر_ټولو_نږدې         0x2700
#تعریف_کړه GL_خطي_MIPMAP_تر_ټولو_نږدې          0x2701
#تعریف_کړه GL_تر_ټولو_نږدې_MIPMAP_خطي          0x2702
#تعریف_کړه GL_خطي_MIPMAP_خطي           0x2703
#تعریف_کړه GL_TEXTURE_MAG_FILTER             0x2800
#تعریف_کړه GL_TEXTURE_MIN_FILTER             0x2801
#تعریف_کړه GL_TEXTURE_WRAP_S                 0x2802
#تعریف_کړه GL_TEXTURE_WRAP_T                 0x2803
#تعریف_کړه GL_GENERATE_MIPMAP                0x8191
#تعریف_کړه GL_TEXTURE0                       0x84C0
#تعریف_کړه GL_TEXTURE1                       0x84C1
#تعریف_کړه GL_TEXTURE2                       0x84C2
#تعریف_کړه GL_TEXTURE3                       0x84C3
#تعریف_کړه GL_TEXTURE4                       0x84C4
#تعریف_کړه GL_TEXTURE5                       0x84C5
#تعریف_کړه GL_TEXTURE6                       0x84C6
#تعریف_کړه GL_TEXTURE7                       0x84C7
#تعریف_کړه GL_TEXTURE8                       0x84C8
#تعریف_کړه GL_TEXTURE9                       0x84C9
#تعریف_کړه GL_TEXTURE10                      0x84CA
#تعریف_کړه GL_TEXTURE11                      0x84CB
#تعریف_کړه GL_TEXTURE12                      0x84CC
#تعریف_کړه GL_TEXTURE13                      0x84CD
#تعریف_کړه GL_TEXTURE14                      0x84CE
#تعریف_کړه GL_TEXTURE15                      0x84CF
#تعریف_کړه GL_TEXTURE16                      0x84D0
#تعریف_کړه GL_TEXTURE17                      0x84D1
#تعریف_کړه GL_TEXTURE18                      0x84D2
#تعریف_کړه GL_TEXTURE19                      0x84D3
#تعریف_کړه GL_TEXTURE20                      0x84D4
#تعریف_کړه GL_TEXTURE21                      0x84D5
#تعریف_کړه GL_TEXTURE22                      0x84D6
#تعریف_کړه GL_TEXTURE23                      0x84D7
#تعریف_کړه GL_TEXTURE24                      0x84D8
#تعریف_کړه GL_TEXTURE25                      0x84D9
#تعریف_کړه GL_TEXTURE26                      0x84DA
#تعریف_کړه GL_TEXTURE27                      0x84DB
#تعریف_کړه GL_TEXTURE28                      0x84DC
#تعریف_کړه GL_TEXTURE29                      0x84DD
#تعریف_کړه GL_TEXTURE30                      0x84DE
#تعریف_کړه GL_TEXTURE31                      0x84DF
#تعریف_کړه GL_فعال_TEXTURE                 0x84E0
#تعریف_کړه GL_CLIENT_فعال_TEXTURE          0x84E1
#تعریف_کړه GL_REPEAT                         0x2901
#تعریف_کړه GL_CLAMP_منزل_څنډه                  0x812F
#تعریف_کړه GL_LIGHT0                         0x4000
#تعریف_کړه GL_LIGHT1                         0x4001
#تعریف_کړه GL_LIGHT2                         0x4002
#تعریف_کړه GL_LIGHT3                         0x4003
#تعریف_کړه GL_LIGHT4                         0x4004
#تعریف_کړه GL_LIGHT5                         0x4005
#تعریف_کړه GL_LIGHT6                         0x4006
#تعریف_کړه GL_LIGHT7                         0x4007
#تعریف_کړه GL_ARRAY_بفر                   0x8892
#تعریف_کړه GL_ELEMENT_ARRAY_بفر           0x8893
#تعریف_کړه GL_ARRAY_بفر_BINDING           0x8894
#تعریف_کړه GL_ELEMENT_ARRAY_بفر_BINDING   0x8895
#تعریف_کړه GL_راس_ARRAY_بفر_BINDING    0x8896
#تعریف_کړه GL_نورمال_ARRAY_بفر_BINDING    0x8897
#تعریف_کړه GL_COLOR_ARRAY_بفر_BINDING     0x8898
#تعریف_کړه GL_TEXTURE_COORD_ARRAY_بفر_BINDING 0x889A
#تعریف_کړه GL_STATIC_DRAW                    0x88E4
#تعریف_کړه GL_DYNAMIC_DRAW                   0x88E8
#تعریف_کړه GL_بفر_اندازه                    0x8764
#تعریف_کړه GL_بفر_USAGE                   0x8765
#تعریف_کړه GL_کمول                       0x84E7
#تعریف_کړه GL_COMBINE                        0x8570
#تعریف_کړه GL_COMBINE_RGB                    0x8571
#تعریف_کړه GL_COMBINE_ALPHA                  0x8572
#تعریف_کړه GL_RGB_SCALE                      0x8573
#تعریف_کړه GL_جمع_کړه_SIGNED                     0x8574
#تعریف_کړه GL_INTERPOLATE                    0x8575
#تعریف_کړه GL_CONSTANT                       0x8576
#تعریف_کړه GL_PRIMARY_COLOR                  0x8577
#تعریف_کړه GL_پخوانی                       0x8578
#تعریف_کړه GL_OPERAND0_RGB                   0x8590
#تعریف_کړه GL_OPERAND1_RGB                   0x8591
#تعریف_کړه GL_OPERAND2_RGB                   0x8592
#تعریف_کړه GL_OPERAND0_ALPHA                 0x8598
#تعریف_کړه GL_OPERAND1_ALPHA                 0x8599
#تعریف_کړه GL_OPERAND2_ALPHA                 0x859A
#تعریف_کړه GL_ALPHA_SCALE                    0x0D1C
#تعریف_کړه GL_SRC0_RGB                       0x8580
#تعریف_کړه GL_SRC1_RGB                       0x8581
#تعریف_کړه GL_SRC2_RGB                       0x8582
#تعریف_کړه GL_SRC0_ALPHA                     0x8588
#تعریف_کړه GL_SRC1_ALPHA                     0x8589
#تعریف_کړه GL_SRC2_ALPHA                     0x858A
#تعریف_کړه GL_DOT3_RGB                       0x86AE
#تعریف_کړه GL_DOT3_RGBA                      0x86AF
GL_API فراغ GL_APIENTRY glAlphaFunc (GLenum func, GLfloat ref);
GL_API فراغ GL_APIENTRY glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_API فراغ GL_APIENTRY glClearDepthf (GLfloat d);
GL_API فراغ GL_APIENTRY glClipPlanef (GLenum p, ثابت GLfloat *eqn);
GL_API فراغ GL_APIENTRY glColor4f (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_API فراغ GL_APIENTRY gl_ژوروالی_Rangef (GLfloat n, GLfloat f);
GL_API فراغ GL_APIENTRY glFogf (GLenum pname, GLfloat param);
GL_API فراغ GL_APIENTRY glFogfv (GLenum pname, ثابت GLfloat *params);
GL_API فراغ GL_APIENTRY glFrustumf (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
GL_API فراغ GL_APIENTRY glGetClipPlanef (GLenum plane, GLfloat *equation);
GL_API فراغ GL_APIENTRY glGetFloatv (GLenum pname, GLfloat *معلومات);
GL_API فراغ GL_APIENTRY glGetLightfv (GLenum light, GLenum pname, GLfloat *params);
GL_API فراغ GL_APIENTRY glGetMaterialfv (GLenum face, GLenum pname, GLfloat *params);
GL_API فراغ GL_APIENTRY glGetTexEnvfv (GLenum موخه, GLenum pname, GLfloat *params);
GL_API فراغ GL_APIENTRY glGetTexParameterfv (GLenum موخه, GLenum pname, GLfloat *params);
GL_API فراغ GL_APIENTRY glLightModelf (GLenum pname, GLfloat param);
GL_API فراغ GL_APIENTRY glLightModelfv (GLenum pname, ثابت GLfloat *params);
GL_API فراغ GL_APIENTRY glLightf (GLenum light, GLenum pname, GLfloat param);
GL_API فراغ GL_APIENTRY glLightfv (GLenum light, GLenum pname, ثابت GLfloat *params);
GL_API فراغ GL_APIENTRY gl_کرښه_پلنوالی (GLfloat پلنوالی);
GL_API فراغ GL_APIENTRY gl_بارول_Matrixf (ثابت GLfloat *m);
GL_API فراغ GL_APIENTRY glMaterialf (GLenum face, GLenum pname, GLfloat param);
GL_API فراغ GL_APIENTRY glMaterialfv (GLenum face, GLenum pname, ثابت GLfloat *params);
GL_API فراغ GL_APIENTRY glMultMatrixf (ثابت GLfloat *m);
GL_API فراغ GL_APIENTRY glMultiTexCoord4f (GLenum موخه, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
GL_API فراغ GL_APIENTRY glNormal3f (GLfloat nx, GLfloat ny, GLfloat nz);
GL_API فراغ GL_APIENTRY glOrthof (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
GL_API فراغ GL_APIENTRY gl_ټکی_Parameterf (GLenum pname, GLfloat param);
GL_API فراغ GL_APIENTRY gl_ټکی_Parameterfv (GLenum pname, ثابت GLfloat *params);
GL_API فراغ GL_APIENTRY gl_ټکی_اندازه (GLfloat اندازه);
GL_API فراغ GL_APIENTRY gl_Polygon_دننه_واټن (GLfloat ضریب, GLfloat units);
GL_API فراغ GL_APIENTRY glRotatef (GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
GL_API فراغ GL_APIENTRY glScalef (GLfloat x, GLfloat y, GLfloat z);
GL_API فراغ GL_APIENTRY glTexEnvf (GLenum موخه, GLenum pname, GLfloat param);
GL_API فراغ GL_APIENTRY glTexEnvfv (GLenum موخه, GLenum pname, ثابت GLfloat *params);
GL_API فراغ GL_APIENTRY glTexParameterf (GLenum موخه, GLenum pname, GLfloat param);
GL_API فراغ GL_APIENTRY glTexParameterfv (GLenum موخه, GLenum pname, ثابت GLfloat *params);
GL_API فراغ GL_APIENTRY glTranslatef (GLfloat x, GLfloat y, GLfloat z);
GL_API فراغ GL_APIENTRY gl_فعال_Texture (GLenum texture);
GL_API فراغ GL_APIENTRY glAlphaFuncx (GLenum func, GLfixed ref);
GL_API فراغ GL_APIENTRY gl_Bind_بفر (GLenum موخه, GLuint بفر_2);
GL_API فراغ GL_APIENTRY glBindTexture (GLenum موخه, GLuint texture);
GL_API فراغ GL_APIENTRY glBlendFunc (GLenum sfactor, GLenum dfactor);
GL_API فراغ GL_APIENTRY gl_بفر_معلومات (GLenum موخه, GLsizeiptr اندازه, ثابت فراغ *معلومات, GLenum usage);
GL_API فراغ GL_APIENTRY gl_بفر_Sub_معلومات (GLenum موخه, GLintptr دننه_واټن_2, GLsizeiptr اندازه, ثابت فراغ *معلومات);
GL_API فراغ GL_APIENTRY glClear (GLbitfield ماسک);
GL_API فراغ GL_APIENTRY glClearColorx (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GL_API فراغ GL_APIENTRY glClearDepthx (GLfixed ژوروالی_2);
GL_API فراغ GL_APIENTRY glClearStencil (GLint s);
GL_API فراغ GL_APIENTRY gl_Client_فعال_Texture (GLenum texture);
GL_API فراغ GL_APIENTRY glClipPlanex (GLenum plane, ثابت GLfixed *equation);
GL_API فراغ GL_APIENTRY glColor4ub (GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
GL_API فراغ GL_APIENTRY glColor4x (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GL_API فراغ GL_APIENTRY gl_Color_ماسک (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
GL_API فراغ GL_APIENTRY gl_Color_اشاره_ګر (GLint اندازه, GLenum type, GLsizei stride, ثابت فراغ *اشاره_ګر_2);
GL_API فراغ GL_APIENTRY glCompressedTexImage2D (GLenum موخه, GLint level, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی, GLint border, GLsizei image_اندازه, ثابت فراغ *معلومات);
GL_API فراغ GL_APIENTRY glCompressedTexSubImage2D (GLenum موخه, GLint level, GLint xoffset, GLint yoffset, GLsizei پلنوالی, GLsizei لوړوالی, GLenum format, GLsizei image_اندازه, ثابت فراغ *معلومات);
GL_API فراغ GL_APIENTRY glCopyTexImage2D (GLenum موخه, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei پلنوالی, GLsizei لوړوالی, GLint border);
GL_API فراغ GL_APIENTRY glCopyTexSubImage2D (GLenum موخه, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei پلنوالی, GLsizei لوړوالی);
GL_API فراغ GL_APIENTRY glCullFace (GLenum ډېرپېښ);
GL_API فراغ GL_APIENTRY glDeleteBuffers (GLsizei n, ثابت GLuint *buffers);
GL_API فراغ GL_APIENTRY glDeleteTextures (GLsizei n, ثابت GLuint *textures);
GL_API فراغ GL_APIENTRY gl_ژوروالی_Func (GLenum func);
GL_API فراغ GL_APIENTRY gl_ژوروالی_ماسک (GLboolean flag);
GL_API فراغ GL_APIENTRY gl_ژوروالی_Rangex (GLfixed n, GLfixed f);
GL_API فراغ GL_APIENTRY glDisable (GLenum cap);
GL_API فراغ GL_APIENTRY glDisableClientState (GLenum array);
GL_API فراغ GL_APIENTRY glDrawArrays (GLenum ډېرپېښ, GLint لومړی, GLsizei شمېر);
GL_API فراغ GL_APIENTRY glDrawElements (GLenum ډېرپېښ, GLsizei شمېر, GLenum type, ثابت فراغ *indices);
GL_API فراغ GL_APIENTRY glEnable (GLenum cap);
GL_API فراغ GL_APIENTRY glEnableClientState (GLenum array);
GL_API فراغ GL_APIENTRY gl_پای (فراغ);
GL_API فراغ GL_APIENTRY glFlush (فراغ);
GL_API فراغ GL_APIENTRY glFogx (GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glFogxv (GLenum pname, ثابت GLfixed *param);
GL_API فراغ GL_APIENTRY glFrontFace (GLenum ډېرپېښ);
GL_API فراغ GL_APIENTRY glFrustumx (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
GL_API فراغ GL_APIENTRY glGetBooleanv (GLenum pname, GLboolean *معلومات);
GL_API فراغ GL_APIENTRY gl_Get_بفر_Parameteriv (GLenum موخه, GLenum pname, GLint *params);
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
GL_API فراغ GL_APIENTRY glGetTexEnviv (GLenum موخه, GLenum pname, GLint *params);
GL_API فراغ GL_APIENTRY glGetTexEnvxv (GLenum موخه, GLenum pname, GLfixed *params);
GL_API فراغ GL_APIENTRY glGetTexParameteriv (GLenum موخه, GLenum pname, GLint *params);
GL_API فراغ GL_APIENTRY glGetTexParameterxv (GLenum موخه, GLenum pname, GLfixed *params);
GL_API فراغ GL_APIENTRY glHint (GLenum موخه, GLenum ډېرپېښ);
GL_API GLboolean GL_APIENTRY gl_Is_بفر (GLuint بفر_2);
GL_API GLboolean GL_APIENTRY glIsEnabled (GLenum cap);
GL_API GLboolean GL_APIENTRY glIsTexture (GLuint texture);
GL_API فراغ GL_APIENTRY glLightModelx (GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glLightModelxv (GLenum pname, ثابت GLfixed *param);
GL_API فراغ GL_APIENTRY glLightx (GLenum light, GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glLightxv (GLenum light, GLenum pname, ثابت GLfixed *params);
GL_API فراغ GL_APIENTRY gl_کرښه_Widthx (GLfixed پلنوالی);
GL_API فراغ GL_APIENTRY gl_بارول_بې_اغېزه_عنصر (فراغ);
GL_API فراغ GL_APIENTRY gl_بارول_Matrixx (ثابت GLfixed *m);
GL_API فراغ GL_APIENTRY glLogicOp (GLenum opcode);
GL_API فراغ GL_APIENTRY glMaterialx (GLenum face, GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glMaterialxv (GLenum face, GLenum pname, ثابت GLfixed *param);
GL_API فراغ GL_APIENTRY gl_ماتریکس_ډېرپېښ (GLenum ډېرپېښ);
GL_API فراغ GL_APIENTRY glMultMatrixx (ثابت GLfixed *m);
GL_API فراغ GL_APIENTRY glMultiTexCoord4x (GLenum texture, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
GL_API فراغ GL_APIENTRY glNormal3x (GLfixed nx, GLfixed ny, GLfixed nz);
GL_API فراغ GL_APIENTRY gl_نورمال_اشاره_ګر (GLenum type, GLsizei stride, ثابت فراغ *اشاره_ګر_2);
GL_API فراغ GL_APIENTRY glOrthox (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
GL_API فراغ GL_APIENTRY glPixelStorei (GLenum pname, GLint param);
GL_API فراغ GL_APIENTRY gl_ټکی_Parameterx (GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY gl_ټکی_Parameterxv (GLenum pname, ثابت GLfixed *params);
GL_API فراغ GL_APIENTRY gl_ټکی_Sizex (GLfixed اندازه);
GL_API فراغ GL_APIENTRY glPolygonOffsetx (GLfixed ضریب, GLfixed units);
GL_API فراغ GL_APIENTRY gl_راوباسه_ماتریکس (فراغ);
GL_API فراغ GL_APIENTRY gl_ټېل_ماتریکس (فراغ);
GL_API فراغ GL_APIENTRY glReadPixels (GLint x, GLint y, GLsizei پلنوالی, GLsizei لوړوالی, GLenum format, GLenum type, فراغ *pixels);
GL_API فراغ GL_APIENTRY glRotatex (GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
GL_API فراغ GL_APIENTRY glSampleCoverage (GLfloat ارزښت, GLboolean invert);
GL_API فراغ GL_APIENTRY glSampleCoveragex (GLclampx ارزښت, GLboolean invert);
GL_API فراغ GL_APIENTRY glScalex (GLfixed x, GLfixed y, GLfixed z);
GL_API فراغ GL_APIENTRY glScissor (GLint x, GLint y, GLsizei پلنوالی, GLsizei لوړوالی);
GL_API فراغ GL_APIENTRY glShadeModel (GLenum ډېرپېښ);
GL_API فراغ GL_APIENTRY glStencilFunc (GLenum func, GLint ref, GLuint ماسک);
GL_API فراغ GL_APIENTRY gl_Stencil_ماسک (GLuint ماسک);
GL_API فراغ GL_APIENTRY glStencilOp (GLenum fail, GLenum zfail, GLenum zpass);
GL_API فراغ GL_APIENTRY gl_Tex_Coord_اشاره_ګر (GLint اندازه, GLenum type, GLsizei stride, ثابت فراغ *اشاره_ګر_2);
GL_API فراغ GL_APIENTRY glTexEnvi (GLenum موخه, GLenum pname, GLint param);
GL_API فراغ GL_APIENTRY glTexEnvx (GLenum موخه, GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glTexEnviv (GLenum موخه, GLenum pname, ثابت GLint *params);
GL_API فراغ GL_APIENTRY glTexEnvxv (GLenum موخه, GLenum pname, ثابت GLfixed *params);
GL_API فراغ GL_APIENTRY glTexImage2D (GLenum موخه, GLint level, GLint internalformat, GLsizei پلنوالی, GLsizei لوړوالی, GLint border, GLenum format, GLenum type, ثابت فراغ *pixels);
GL_API فراغ GL_APIENTRY glTexParameteri (GLenum موخه, GLenum pname, GLint param);
GL_API فراغ GL_APIENTRY glTexParameterx (GLenum موخه, GLenum pname, GLfixed param);
GL_API فراغ GL_APIENTRY glTexParameteriv (GLenum موخه, GLenum pname, ثابت GLint *params);
GL_API فراغ GL_APIENTRY glTexParameterxv (GLenum موخه, GLenum pname, ثابت GLfixed *params);
GL_API فراغ GL_APIENTRY glTexSubImage2D (GLenum موخه, GLint level, GLint xoffset, GLint yoffset, GLsizei پلنوالی, GLsizei لوړوالی, GLenum format, GLenum type, ثابت فراغ *pixels);
GL_API فراغ GL_APIENTRY glTranslatex (GLfixed x, GLfixed y, GLfixed z);
GL_API فراغ GL_APIENTRY gl_راس_اشاره_ګر (GLint اندازه, GLenum type, GLsizei stride, ثابت فراغ *اشاره_ګر_2);
GL_API فراغ GL_APIENTRY glViewport (GLint x, GLint y, GLsizei پلنوالی, GLsizei لوړوالی);
#د_که_پای /* GL_VERSION_ES_CM_1_0 */

#که_نه_تعریف_شوی GL_OES_compressed_paletted_texture
#تعریف_کړه GL_OES_compressed_paletted_texture 1
#تعریف_کړه GL_PALETTE4_RGB8_OES              0x8B90
#تعریف_کړه GL_PALETTE4_RGBA8_OES             0x8B91
#تعریف_کړه GL_PALETTE4_R5_G6_B5_OES          0x8B92
#تعریف_کړه GL_PALETTE4_RGBA4_OES             0x8B93
#تعریف_کړه GL_PALETTE4_RGB5_A1_OES           0x8B94
#تعریف_کړه GL_PALETTE8_RGB8_OES              0x8B95
#تعریف_کړه GL_PALETTE8_RGBA8_OES             0x8B96
#تعریف_کړه GL_PALETTE8_R5_G6_B5_OES          0x8B97
#تعریف_کړه GL_PALETTE8_RGBA4_OES             0x8B98
#تعریف_کړه GL_PALETTE8_RGB5_A1_OES           0x8B99
#د_که_پای /* GL_OES_compressed_paletted_texture */

#که_نه_تعریف_شوی GL_OES_ټکی_اندازه_array
#تعریف_کړه GL_OES_ټکی_اندازه_array 1
#تعریف_کړه GL_ټکی_اندازه_ARRAY_OES           0x8B9C
#تعریف_کړه GL_ټکی_اندازه_ARRAY_TYPE_OES      0x898A
#تعریف_کړه GL_ټکی_اندازه_ARRAY_STRIDE_OES    0x898B
#تعریف_کړه GL_ټکی_اندازه_ARRAY_اشاره_ګر_OES   0x898C
#تعریف_کړه GL_ټکی_اندازه_ARRAY_بفر_BINDING_OES 0x8B9F
GL_API فراغ GL_APIENTRY gl_ټکی_اندازه_اشاره_ګر_OES (GLenum type, GLsizei stride, ثابت فراغ *اشاره_ګر_2);
#د_که_پای /* GL_OES_point_size_array */

#که_نه_تعریف_شوی GL_OES_ټکی_sprite
#تعریف_کړه GL_OES_ټکی_sprite 1
#تعریف_کړه GL_ټکی_SPRITE_OES               0x8861
#تعریف_کړه GL_COORD_REPLACE_OES              0x8862
#د_که_پای /* GL_OES_point_sprite */

#که_نه_تعریف_شوی GL_OES_read_format
#تعریف_کړه GL_OES_read_format 1
#تعریف_کړه GL_IMPLEMENTATION_COLOR_READ_TYPE_OES 0x8B9A
#تعریف_کړه GL_IMPLEMENTATION_COLOR_READ_FORMAT_OES 0x8B9B
#د_که_پای /* GL_OES_read_format */

#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای
