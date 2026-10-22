#اگر_غیر_تعریف_شدہ __gles1_gl_h_
#تعریف_کرو __gles1_gl_h_ 1

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

#شامل <GLES/glplatform.h>

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

#اگر_غیر_تعریف_شدہ GL_نسخہ_ES_CM_1_0
#تعریف_کرو GL_نسخہ_ES_CM_1_0 1
#شامل <KHR/khrplatform.h>
قسمتعریف khronos_int8_t GLbyte;
قسمتعریف khronos_float_t GLclampf;
قسمتعریف khronos_int16_t GLshort;
قسمتعریف khronos_uint16_t GLushort;
قسمتعریف خالی GLvoid;
قسمتعریف غیرعلامتی صحیح GLenum;
قسمتعریف khronos_float_t GLfloat;
قسمتعریف khronos_int32_t GLfixed;
قسمتعریف غیرعلامتی صحیح GLuint;
قسمتعریف khronos_ssize_t GLsizeiptr;
قسمتعریف khronos_intptr_t GLintptr;
قسمتعریف غیرعلامتی صحیح GLbitfield;
قسمتعریف صحیح GLint;
قسمتعریف khronos_uint8_t GLubyte;
قسمتعریف غیرعلامتی حرف GLboolean;
قسمتعریف صحیح GLsizei;
قسمتعریف khronos_int32_t GLclampx;
#تعریف_کرو GL_نسخہ_ES_CL_1_0              1
#تعریف_کرو GL_نسخہ_ES_CM_1_1              1
#تعریف_کرو GL_نسخہ_ES_CL_1_1              1
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
#تعریف_کرو GL_NEVER                          0x0200
#تعریف_کرو GL_LESS                           0x0201
#تعریف_کرو GL_EQUAL                          0x0202
#تعریف_کرو GL_LEQUAL                         0x0203
#تعریف_کرو GL_GREATER                        0x0204
#تعریف_کرو GL_NOTEQUAL                       0x0205
#تعریف_کرو GL_GEQUAL                         0x0206
#تعریف_کرو GL_ALWAYS                         0x0207
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
#تعریف_کرو GL_CLIP_PLANE0                    0x3000
#تعریف_کرو GL_CLIP_PLANE1                    0x3001
#تعریف_کرو GL_CLIP_PLANE2                    0x3002
#تعریف_کرو GL_CLIP_PLANE3                    0x3003
#تعریف_کرو GL_CLIP_PLANE4                    0x3004
#تعریف_کرو GL_CLIP_PLANE5                    0x3005
#تعریف_کرو GL_FRONT                          0x0404
#تعریف_کرو GL_عقب                           0x0405
#تعریف_کرو GL_FRONT_AND_عقب                 0x0408
#تعریف_کرو GL_FOG                            0x0B60
#تعریف_کرو GL_LIGHTING                       0x0B50
#تعریف_کرو GL_TEXTURE_2D                     0x0DE1
#تعریف_کرو GL_CULL_FACE                      0x0B44
#تعریف_کرو GL_ALPHA_TEST                     0x0BC0
#تعریف_کرو GL_BLEND                          0x0BE2
#تعریف_کرو GL_COLOR_LOGIC_OP                 0x0BF2
#تعریف_کرو GL_DITHER                         0x0BD0
#تعریف_کرو GL_STENCIL_TEST                   0x0B90
#تعریف_کرو GL_گہرائی_TEST                     0x0B71
#تعریف_کرو GL_نقطہ_SMOOTH                   0x0B10
#تعریف_کرو GL_سطر_SMOOTH                    0x0B20
#تعریف_کرو GL_SCISSOR_TEST                   0x0C11
#تعریف_کرو GL_COLOR_MATERIAL                 0x0B57
#تعریف_کرو GL_NORMALIZE                      0x0BA1
#تعریف_کرو GL_RESCALE_معمول                 0x803A
#تعریف_کرو GL_راس_ARRAY                   0x8074
#تعریف_کرو GL_معمول_ARRAY                   0x8075
#تعریف_کرو GL_COLOR_ARRAY                    0x8076
#تعریف_کرو GL_TEXTURE_COORD_ARRAY            0x8078
#تعریف_کرو GL_MULTISAMPLE                    0x809D
#تعریف_کرو GL_SAMPLE_ALPHA_مقصد_COVERAGE       0x809E
#تعریف_کرو GL_SAMPLE_ALPHA_مقصد_ONE            0x809F
#تعریف_کرو GL_SAMPLE_COVERAGE                0x80A0
#تعریف_کرو GL_NO_ERROR                       0
#تعریف_کرو GL_INVALID_ENUM                   0x0500
#تعریف_کرو GL_INVALID_قدر                  0x0501
#تعریف_کرو GL_INVALID_OPERATION              0x0502
#تعریف_کرو GL_ڈھیر_حد_سے_تجاوز                 0x0503
#تعریف_کرو GL_ڈھیر_UNDERFLOW                0x0504
#تعریف_کرو GL_برآمد_کا_حافظہ                  0x0505
#تعریف_کرو GL_EXP                            0x0800
#تعریف_کرو GL_EXP2                           0x0801
#تعریف_کرو GL_FOG_DENSITY                    0x0B62
#تعریف_کرو GL_FOG_آغاز                      0x0B63
#تعریف_کرو GL_FOG_انتہا                        0x0B64
#تعریف_کرو GL_FOG_منوال                       0x0B65
#تعریف_کرو GL_FOG_COLOR                      0x0B66
#تعریف_کرو GL_CW                             0x0900
#تعریف_کرو GL_CCW                            0x0901
#تعریف_کرو GL_CURRENT_COLOR                  0x0B00
#تعریف_کرو GL_CURRENT_معمول                 0x0B02
#تعریف_کرو GL_CURRENT_TEXTURE_COORDS         0x0B03
#تعریف_کرو GL_نقطہ_سائز                     0x0B11
#تعریف_کرو GL_نقطہ_سائز_MIN                 0x8126
#تعریف_کرو GL_نقطہ_سائز_MAX                 0x8127
#تعریف_کرو GL_نقطہ_FADE_حد_سائز      0x8128
#تعریف_کرو GL_نقطہ_فاصلہ_ATTENUATION     0x8129
#تعریف_کرو GL_SMOOTH_نقطہ_سائز_RANGE        0x0B12
#تعریف_کرو GL_سطر_چوڑائی                     0x0B21
#تعریف_کرو GL_SMOOTH_سطر_چوڑائی_RANGE        0x0B22
#تعریف_کرو GL_ALIASED_نقطہ_سائز_RANGE       0x846D
#تعریف_کرو GL_ALIASED_سطر_چوڑائی_RANGE       0x846E
#تعریف_کرو GL_CULL_FACE_منوال                 0x0B45
#تعریف_کرو GL_FRONT_FACE                     0x0B46
#تعریف_کرو GL_SHADE_MODEL                    0x0B54
#تعریف_کرو GL_گہرائی_RANGE                    0x0B70
#تعریف_کرو GL_گہرائی_WRITEMASK                0x0B72
#تعریف_کرو GL_گہرائی_CLEAR_قدر              0x0B73
#تعریف_کرو GL_گہرائی_FUNC                     0x0B74
#تعریف_کرو GL_STENCIL_CLEAR_قدر            0x0B91
#تعریف_کرو GL_STENCIL_FUNC                   0x0B92
#تعریف_کرو GL_STENCIL_قدر_نقاب             0x0B93
#تعریف_کرو GL_STENCIL_FAIL                   0x0B94
#تعریف_کرو GL_STENCIL_PASS_گہرائی_FAIL        0x0B95
#تعریف_کرو GL_STENCIL_PASS_گہرائی_PASS        0x0B96
#تعریف_کرو GL_STENCIL_REF                    0x0B97
#تعریف_کرو GL_STENCIL_WRITEMASK              0x0B98
#تعریف_کرو GL_میٹرکس_منوال                    0x0BA0
#تعریف_کرو GL_VIEWPORT                       0x0BA2
#تعریف_کرو GL_MODELVIEW_ڈھیر_گہرائی          0x0BA3
#تعریف_کرو GL_PROJECTION_ڈھیر_گہرائی         0x0BA4
#تعریف_کرو GL_TEXTURE_ڈھیر_گہرائی            0x0BA5
#تعریف_کرو GL_MODELVIEW_میٹرکس               0x0BA6
#تعریف_کرو GL_PROJECTION_میٹرکس              0x0BA7
#تعریف_کرو GL_TEXTURE_میٹرکس                 0x0BA8
#تعریف_کرو GL_ALPHA_TEST_FUNC                0x0BC1
#تعریف_کرو GL_ALPHA_TEST_REF                 0x0BC2
#تعریف_کرو GL_BLEND_DST                      0x0BE0
#تعریف_کرو GL_BLEND_SRC                      0x0BE1
#تعریف_کرو GL_LOGIC_OP_منوال                  0x0BF0
#تعریف_کرو GL_SCISSOR_BOX                    0x0C10
#تعریف_کرو GL_COLOR_CLEAR_قدر              0x0C22
#تعریف_کرو GL_COLOR_WRITEMASK                0x0C23
#تعریف_کرو GL_MAX_LIGHTS                     0x0D31
#تعریف_کرو GL_MAX_CLIP_PLANES                0x0D32
#تعریف_کرو GL_MAX_TEXTURE_سائز               0x0D33
#تعریف_کرو GL_MAX_MODELVIEW_ڈھیر_گہرائی      0x0D36
#تعریف_کرو GL_MAX_PROJECTION_ڈھیر_گہرائی     0x0D38
#تعریف_کرو GL_MAX_TEXTURE_ڈھیر_گہرائی        0x0D39
#تعریف_کرو GL_MAX_VIEWPORT_DIMS              0x0D3A
#تعریف_کرو GL_MAX_TEXTURE_UNITS              0x84E2
#تعریف_کرو GL_SUBPIXEL_بٹ                  0x0D50
#تعریف_کرو GL_RED_بٹ                       0x0D52
#تعریف_کرو GL_GREEN_بٹ                     0x0D53
#تعریف_کرو GL_BLUE_بٹ                      0x0D54
#تعریف_کرو GL_ALPHA_بٹ                     0x0D55
#تعریف_کرو GL_گہرائی_بٹ                     0x0D56
#تعریف_کرو GL_STENCIL_بٹ                   0x0D57
#تعریف_کرو GL_POLYGON_انحراف_UNITS           0x2A00
#تعریف_کرو GL_POLYGON_انحراف_FILL            0x8037
#تعریف_کرو GL_POLYGON_انحراف_ضربی_عدد          0x8038
#تعریف_کرو GL_TEXTURE_BINDING_2D             0x8069
#تعریف_کرو GL_راس_ARRAY_سائز              0x807A
#تعریف_کرو GL_راس_ARRAY_TYPE              0x807B
#تعریف_کرو GL_راس_ARRAY_STRIDE            0x807C
#تعریف_کرو GL_معمول_ARRAY_TYPE              0x807E
#تعریف_کرو GL_معمول_ARRAY_STRIDE            0x807F
#تعریف_کرو GL_COLOR_ARRAY_سائز               0x8081
#تعریف_کرو GL_COLOR_ARRAY_TYPE               0x8082
#تعریف_کرو GL_COLOR_ARRAY_STRIDE             0x8083
#تعریف_کرو GL_TEXTURE_COORD_ARRAY_سائز       0x8088
#تعریف_کرو GL_TEXTURE_COORD_ARRAY_TYPE       0x8089
#تعریف_کرو GL_TEXTURE_COORD_ARRAY_STRIDE     0x808A
#تعریف_کرو GL_راس_ARRAY_اشارہ_گر           0x808E
#تعریف_کرو GL_معمول_ARRAY_اشارہ_گر           0x808F
#تعریف_کرو GL_COLOR_ARRAY_اشارہ_گر            0x8090
#تعریف_کرو GL_TEXTURE_COORD_ARRAY_اشارہ_گر    0x8092
#تعریف_کرو GL_SAMPLE_BUFFERS                 0x80A8
#تعریف_کرو GL_SAMPLES                        0x80A9
#تعریف_کرو GL_SAMPLE_COVERAGE_قدر          0x80AA
#تعریف_کرو GL_SAMPLE_COVERAGE_INVERT         0x80AB
#تعریف_کرو GL_عدد_COMPRESSED_TEXTURE_FORMATS 0x86A2
#تعریف_کرو GL_COMPRESSED_TEXTURE_FORMATS     0x86A3
#تعریف_کرو GL_DONT_CARE                      0x1100
#تعریف_کرو GL_FASTEST                        0x1101
#تعریف_کرو GL_NICEST                         0x1102
#تعریف_کرو GL_PERSPECTIVE_CORRECTION_HINT    0x0C50
#تعریف_کرو GL_نقطہ_SMOOTH_HINT              0x0C51
#تعریف_کرو GL_سطر_SMOOTH_HINT               0x0C52
#تعریف_کرو GL_FOG_HINT                       0x0C54
#تعریف_کرو GL_GENERATE_MIPMAP_HINT           0x8192
#تعریف_کرو GL_LIGHT_MODEL_AMBIENT            0x0B53
#تعریف_کرو GL_LIGHT_MODEL_TWO_SIDE           0x0B52
#تعریف_کرو GL_AMBIENT                        0x1200
#تعریف_کرو GL_DIFFUSE                        0x1201
#تعریف_کرو GL_SPECULAR                       0x1202
#تعریف_کرو GL_POSITION                       0x1203
#تعریف_کرو GL_SPOT_DIRECTION                 0x1204
#تعریف_کرو GL_SPOT_EXPONENT                  0x1205
#تعریف_کرو GL_SPOT_CUTOFF                    0x1206
#تعریف_کرو GL_CONSTANT_ATTENUATION           0x1207
#تعریف_کرو GL_خطی_ATTENUATION             0x1208
#تعریف_کرو GL_QUADRATIC_ATTENUATION          0x1209
#تعریف_کرو GL_BYTE                           0x1400
#تعریف_کرو GL_UNSIGNED_BYTE                  0x1401
#تعریف_کرو GL_SHORT                          0x1402
#تعریف_کرو GL_UNSIGNED_SHORT                 0x1403
#تعریف_کرو GL_FLOAT                          0x1406
#تعریف_کرو GL_FIXED                          0x140C
#تعریف_کرو GL_CLEAR                          0x1500
#تعریف_کرو GL_AND                            0x1501
#تعریف_کرو GL_AND_الٹ                    0x1502
#تعریف_کرو GL_COPY                           0x1503
#تعریف_کرو GL_AND_INVERTED                   0x1504
#تعریف_کرو GL_NOOP                           0x1505
#تعریف_کرو GL_XOR                            0x1506
#تعریف_کرو GL_OR                             0x1507
#تعریف_کرو GL_NOR                            0x1508
#تعریف_کرو GL_EQUIV                          0x1509
#تعریف_کرو GL_INVERT                         0x150A
#تعریف_کرو GL_OR_الٹ                     0x150B
#تعریف_کرو GL_COPY_INVERTED                  0x150C
#تعریف_کرو GL_OR_INVERTED                    0x150D
#تعریف_کرو GL_NAND                           0x150E
#تعریف_کرو GL_سیٹ                            0x150F
#تعریف_کرو GL_EMISSION                       0x1600
#تعریف_کرو GL_SHININESS                      0x1601
#تعریف_کرو GL_AMBIENT_AND_DIFFUSE            0x1602
#تعریف_کرو GL_MODELVIEW                      0x1700
#تعریف_کرو GL_PROJECTION                     0x1701
#تعریف_کرو GL_TEXTURE                        0x1702
#تعریف_کرو GL_ALPHA                          0x1906
#تعریف_کرو GL_RGB                            0x1907
#تعریف_کرو GL_RGBA                           0x1908
#تعریف_کرو GL_LUMINANCE                      0x1909
#تعریف_کرو GL_LUMINANCE_ALPHA                0x190A
#تعریف_کرو GL_UNPACK_ALIGNMENT               0x0CF5
#تعریف_کرو GL_PACK_ALIGNMENT                 0x0D05
#تعریف_کرو GL_UNSIGNED_SHORT_4_4_4_4         0x8033
#تعریف_کرو GL_UNSIGNED_SHORT_5_5_5_1         0x8034
#تعریف_کرو GL_UNSIGNED_SHORT_5_6_5           0x8363
#تعریف_کرو GL_FLAT                           0x1D00
#تعریف_کرو GL_SMOOTH                         0x1D01
#تعریف_کرو GL_KEEP                           0x1E00
#تعریف_کرو GL_REPLACE                        0x1E01
#تعریف_کرو GL_INCR                           0x1E02
#تعریف_کرو GL_DECR                           0x1E03
#تعریف_کرو GL_VENDOR                         0x1F00
#تعریف_کرو GL_RENDERER                       0x1F01
#تعریف_کرو GL_نسخہ                        0x1F02
#تعریف_کرو GL_EXTENSIONS                     0x1F03
#تعریف_کرو GL_MODULATE                       0x2100
#تعریف_کرو GL_DECAL                          0x2101
#تعریف_کرو GL_جوڑو                            0x0104
#تعریف_کرو GL_TEXTURE_ENV_منوال               0x2200
#تعریف_کرو GL_TEXTURE_ENV_COLOR              0x2201
#تعریف_کرو GL_TEXTURE_ENV                    0x2300
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
#تعریف_کرو GL_GENERATE_MIPMAP                0x8191
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
#تعریف_کرو GL_CLIENT_فعال_TEXTURE          0x84E1
#تعریف_کرو GL_REPEAT                         0x2901
#تعریف_کرو GL_CLAMP_مقصد_کنارہ                  0x812F
#تعریف_کرو GL_LIGHT0                         0x4000
#تعریف_کرو GL_LIGHT1                         0x4001
#تعریف_کرو GL_LIGHT2                         0x4002
#تعریف_کرو GL_LIGHT3                         0x4003
#تعریف_کرو GL_LIGHT4                         0x4004
#تعریف_کرو GL_LIGHT5                         0x4005
#تعریف_کرو GL_LIGHT6                         0x4006
#تعریف_کرو GL_LIGHT7                         0x4007
#تعریف_کرو GL_ARRAY_بفر                   0x8892
#تعریف_کرو GL_ELEMENT_ARRAY_بفر           0x8893
#تعریف_کرو GL_ARRAY_بفر_BINDING           0x8894
#تعریف_کرو GL_ELEMENT_ARRAY_بفر_BINDING   0x8895
#تعریف_کرو GL_راس_ARRAY_بفر_BINDING    0x8896
#تعریف_کرو GL_معمول_ARRAY_بفر_BINDING    0x8897
#تعریف_کرو GL_COLOR_ARRAY_بفر_BINDING     0x8898
#تعریف_کرو GL_TEXTURE_COORD_ARRAY_بفر_BINDING 0x889A
#تعریف_کرو GL_STATIC_DRAW                    0x88E4
#تعریف_کرو GL_DYNAMIC_DRAW                   0x88E8
#تعریف_کرو GL_بفر_سائز                    0x8764
#تعریف_کرو GL_بفر_USAGE                   0x8765
#تعریف_کرو GL_تفریق                       0x84E7
#تعریف_کرو GL_COMBINE                        0x8570
#تعریف_کرو GL_COMBINE_RGB                    0x8571
#تعریف_کرو GL_COMBINE_ALPHA                  0x8572
#تعریف_کرو GL_RGB_SCALE                      0x8573
#تعریف_کرو GL_جوڑو_SIGNED                     0x8574
#تعریف_کرو GL_INTERPOLATE                    0x8575
#تعریف_کرو GL_CONSTANT                       0x8576
#تعریف_کرو GL_PRIMARY_COLOR                  0x8577
#تعریف_کرو GL_پچھلا                       0x8578
#تعریف_کرو GL_OPERAND0_RGB                   0x8590
#تعریف_کرو GL_OPERAND1_RGB                   0x8591
#تعریف_کرو GL_OPERAND2_RGB                   0x8592
#تعریف_کرو GL_OPERAND0_ALPHA                 0x8598
#تعریف_کرو GL_OPERAND1_ALPHA                 0x8599
#تعریف_کرو GL_OPERAND2_ALPHA                 0x859A
#تعریف_کرو GL_ALPHA_SCALE                    0x0D1C
#تعریف_کرو GL_SRC0_RGB                       0x8580
#تعریف_کرو GL_SRC1_RGB                       0x8581
#تعریف_کرو GL_SRC2_RGB                       0x8582
#تعریف_کرو GL_SRC0_ALPHA                     0x8588
#تعریف_کرو GL_SRC1_ALPHA                     0x8589
#تعریف_کرو GL_SRC2_ALPHA                     0x858A
#تعریف_کرو GL_DOT3_RGB                       0x86AE
#تعریف_کرو GL_DOT3_RGBA                      0x86AF
GL_API خالی GL_APIENTRY glAlphaFunc (GLenum func, GLfloat ref);
GL_API خالی GL_APIENTRY glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_API خالی GL_APIENTRY glClearDepthf (GLfloat d);
GL_API خالی GL_APIENTRY glClipPlanef (GLenum p, ثابت GLfloat *eqn);
GL_API خالی GL_APIENTRY glColor4f (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_API خالی GL_APIENTRY gl_گہرائی_Rangef (GLfloat n, GLfloat f);
GL_API خالی GL_APIENTRY glFogf (GLenum pname, GLfloat param);
GL_API خالی GL_APIENTRY glFogfv (GLenum pname, ثابت GLfloat *params);
GL_API خالی GL_APIENTRY glFrustumf (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
GL_API خالی GL_APIENTRY glGetClipPlanef (GLenum plane, GLfloat *equation);
GL_API خالی GL_APIENTRY glGetFloatv (GLenum pname, GLfloat *ڈیٹا);
GL_API خالی GL_APIENTRY glGetLightfv (GLenum light, GLenum pname, GLfloat *params);
GL_API خالی GL_APIENTRY glGetMaterialfv (GLenum face, GLenum pname, GLfloat *params);
GL_API خالی GL_APIENTRY glGetTexEnvfv (GLenum ہدف, GLenum pname, GLfloat *params);
GL_API خالی GL_APIENTRY glGetTexParameterfv (GLenum ہدف, GLenum pname, GLfloat *params);
GL_API خالی GL_APIENTRY glLightModelf (GLenum pname, GLfloat param);
GL_API خالی GL_APIENTRY glLightModelfv (GLenum pname, ثابت GLfloat *params);
GL_API خالی GL_APIENTRY glLightf (GLenum light, GLenum pname, GLfloat param);
GL_API خالی GL_APIENTRY glLightfv (GLenum light, GLenum pname, ثابت GLfloat *params);
GL_API خالی GL_APIENTRY gl_سطر_چوڑائی (GLfloat چوڑائی);
GL_API خالی GL_APIENTRY gl_بھرو_Matrixf (ثابت GLfloat *m);
GL_API خالی GL_APIENTRY glMaterialf (GLenum face, GLenum pname, GLfloat param);
GL_API خالی GL_APIENTRY glMaterialfv (GLenum face, GLenum pname, ثابت GLfloat *params);
GL_API خالی GL_APIENTRY glMultMatrixf (ثابت GLfloat *m);
GL_API خالی GL_APIENTRY glMultiTexCoord4f (GLenum ہدف, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
GL_API خالی GL_APIENTRY glNormal3f (GLfloat nx, GLfloat ny, GLfloat nz);
GL_API خالی GL_APIENTRY glOrthof (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
GL_API خالی GL_APIENTRY gl_نقطہ_Parameterf (GLenum pname, GLfloat param);
GL_API خالی GL_APIENTRY gl_نقطہ_Parameterfv (GLenum pname, ثابت GLfloat *params);
GL_API خالی GL_APIENTRY gl_نقطہ_سائز (GLfloat سائز);
GL_API خالی GL_APIENTRY gl_Polygon_انحراف (GLfloat ضربی_عدد, GLfloat units);
GL_API خالی GL_APIENTRY glRotatef (GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
GL_API خالی GL_APIENTRY glScalef (GLfloat x, GLfloat y, GLfloat z);
GL_API خالی GL_APIENTRY glTexEnvf (GLenum ہدف, GLenum pname, GLfloat param);
GL_API خالی GL_APIENTRY glTexEnvfv (GLenum ہدف, GLenum pname, ثابت GLfloat *params);
GL_API خالی GL_APIENTRY glTexParameterf (GLenum ہدف, GLenum pname, GLfloat param);
GL_API خالی GL_APIENTRY glTexParameterfv (GLenum ہدف, GLenum pname, ثابت GLfloat *params);
GL_API خالی GL_APIENTRY glTranslatef (GLfloat x, GLfloat y, GLfloat z);
GL_API خالی GL_APIENTRY gl_فعال_Texture (GLenum texture);
GL_API خالی GL_APIENTRY glAlphaFuncx (GLenum func, GLfixed ref);
GL_API خالی GL_APIENTRY gl_Bind_بفر (GLenum ہدف, GLuint بفر_2);
GL_API خالی GL_APIENTRY glBindTexture (GLenum ہدف, GLuint texture);
GL_API خالی GL_APIENTRY glBlendFunc (GLenum sfactor, GLenum dfactor);
GL_API خالی GL_APIENTRY gl_بفر_ڈیٹا (GLenum ہدف, GLsizeiptr سائز, ثابت خالی *ڈیٹا, GLenum usage);
GL_API خالی GL_APIENTRY gl_بفر_Sub_ڈیٹا (GLenum ہدف, GLintptr انحراف_2, GLsizeiptr سائز, ثابت خالی *ڈیٹا);
GL_API خالی GL_APIENTRY glClear (GLbitfield نقاب);
GL_API خالی GL_APIENTRY glClearColorx (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GL_API خالی GL_APIENTRY glClearDepthx (GLfixed گہرائی_2);
GL_API خالی GL_APIENTRY glClearStencil (GLint s);
GL_API خالی GL_APIENTRY gl_Client_فعال_Texture (GLenum texture);
GL_API خالی GL_APIENTRY glClipPlanex (GLenum plane, ثابت GLfixed *equation);
GL_API خالی GL_APIENTRY glColor4ub (GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
GL_API خالی GL_APIENTRY glColor4x (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GL_API خالی GL_APIENTRY gl_Color_نقاب (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
GL_API خالی GL_APIENTRY gl_Color_اشارہ_گر (GLint سائز, GLenum type, GLsizei stride, ثابت خالی *اشارہ_گر_2);
GL_API خالی GL_APIENTRY glCompressedTexImage2D (GLenum ہدف, GLint level, GLenum internalformat, GLsizei چوڑائی, GLsizei اونچائی, GLint border, GLsizei image_سائز, ثابت خالی *ڈیٹا);
GL_API خالی GL_APIENTRY glCompressedTexSubImage2D (GLenum ہدف, GLint level, GLint xoffset, GLint yoffset, GLsizei چوڑائی, GLsizei اونچائی, GLenum format, GLsizei image_سائز, ثابت خالی *ڈیٹا);
GL_API خالی GL_APIENTRY glCopyTexImage2D (GLenum ہدف, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei چوڑائی, GLsizei اونچائی, GLint border);
GL_API خالی GL_APIENTRY glCopyTexSubImage2D (GLenum ہدف, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei چوڑائی, GLsizei اونچائی);
GL_API خالی GL_APIENTRY glCullFace (GLenum منوال);
GL_API خالی GL_APIENTRY glDeleteBuffers (GLsizei n, ثابت GLuint *buffers);
GL_API خالی GL_APIENTRY glDeleteTextures (GLsizei n, ثابت GLuint *textures);
GL_API خالی GL_APIENTRY gl_گہرائی_Func (GLenum func);
GL_API خالی GL_APIENTRY gl_گہرائی_نقاب (GLboolean flag);
GL_API خالی GL_APIENTRY gl_گہرائی_Rangex (GLfixed n, GLfixed f);
GL_API خالی GL_APIENTRY glDisable (GLenum cap);
GL_API خالی GL_APIENTRY glDisableClientState (GLenum array);
GL_API خالی GL_APIENTRY glDrawArrays (GLenum منوال, GLint پہلا, GLsizei گنتی);
GL_API خالی GL_APIENTRY glDrawElements (GLenum منوال, GLsizei گنتی, GLenum type, ثابت خالی *indices);
GL_API خالی GL_APIENTRY glEnable (GLenum cap);
GL_API خالی GL_APIENTRY glEnableClientState (GLenum array);
GL_API خالی GL_APIENTRY gl_اختتام (خالی);
GL_API خالی GL_APIENTRY glFlush (خالی);
GL_API خالی GL_APIENTRY glFogx (GLenum pname, GLfixed param);
GL_API خالی GL_APIENTRY glFogxv (GLenum pname, ثابت GLfixed *param);
GL_API خالی GL_APIENTRY glFrontFace (GLenum منوال);
GL_API خالی GL_APIENTRY glFrustumx (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
GL_API خالی GL_APIENTRY glGetBooleanv (GLenum pname, GLboolean *ڈیٹا);
GL_API خالی GL_APIENTRY gl_Get_بفر_Parameteriv (GLenum ہدف, GLenum pname, GLint *params);
GL_API خالی GL_APIENTRY glGetClipPlanex (GLenum plane, GLfixed *equation);
GL_API خالی GL_APIENTRY glGenBuffers (GLsizei n, GLuint *buffers);
GL_API خالی GL_APIENTRY glGenTextures (GLsizei n, GLuint *textures);
GL_API GLenum GL_APIENTRY glGetError (خالی);
GL_API خالی GL_APIENTRY glGetFixedv (GLenum pname, GLfixed *ڈیٹا);
GL_API خالی GL_APIENTRY glGetIntegerv (GLenum pname, GLint *ڈیٹا);
GL_API خالی GL_APIENTRY glGetLightxv (GLenum light, GLenum pname, GLfixed *params);
GL_API خالی GL_APIENTRY glGetMaterialxv (GLenum face, GLenum pname, GLfixed *params);
GL_API خالی GL_APIENTRY glGetPointerv (GLenum pname, خالی **params);
GL_API ثابت GLubyte *GL_APIENTRY glGetString (GLenum name);
GL_API خالی GL_APIENTRY glGetTexEnviv (GLenum ہدف, GLenum pname, GLint *params);
GL_API خالی GL_APIENTRY glGetTexEnvxv (GLenum ہدف, GLenum pname, GLfixed *params);
GL_API خالی GL_APIENTRY glGetTexParameteriv (GLenum ہدف, GLenum pname, GLint *params);
GL_API خالی GL_APIENTRY glGetTexParameterxv (GLenum ہدف, GLenum pname, GLfixed *params);
GL_API خالی GL_APIENTRY glHint (GLenum ہدف, GLenum منوال);
GL_API GLboolean GL_APIENTRY gl_Is_بفر (GLuint بفر_2);
GL_API GLboolean GL_APIENTRY glIsEnabled (GLenum cap);
GL_API GLboolean GL_APIENTRY glIsTexture (GLuint texture);
GL_API خالی GL_APIENTRY glLightModelx (GLenum pname, GLfixed param);
GL_API خالی GL_APIENTRY glLightModelxv (GLenum pname, ثابت GLfixed *param);
GL_API خالی GL_APIENTRY glLightx (GLenum light, GLenum pname, GLfixed param);
GL_API خالی GL_APIENTRY glLightxv (GLenum light, GLenum pname, ثابت GLfixed *params);
GL_API خالی GL_APIENTRY gl_سطر_Widthx (GLfixed چوڑائی);
GL_API خالی GL_APIENTRY gl_بھرو_شناختی_عنصر (خالی);
GL_API خالی GL_APIENTRY gl_بھرو_Matrixx (ثابت GLfixed *m);
GL_API خالی GL_APIENTRY glLogicOp (GLenum opcode);
GL_API خالی GL_APIENTRY glMaterialx (GLenum face, GLenum pname, GLfixed param);
GL_API خالی GL_APIENTRY glMaterialxv (GLenum face, GLenum pname, ثابت GLfixed *param);
GL_API خالی GL_APIENTRY gl_میٹرکس_منوال (GLenum منوال);
GL_API خالی GL_APIENTRY glMultMatrixx (ثابت GLfixed *m);
GL_API خالی GL_APIENTRY glMultiTexCoord4x (GLenum texture, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
GL_API خالی GL_APIENTRY glNormal3x (GLfixed nx, GLfixed ny, GLfixed nz);
GL_API خالی GL_APIENTRY gl_معمول_اشارہ_گر (GLenum type, GLsizei stride, ثابت خالی *اشارہ_گر_2);
GL_API خالی GL_APIENTRY glOrthox (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
GL_API خالی GL_APIENTRY glPixelStorei (GLenum pname, GLint param);
GL_API خالی GL_APIENTRY gl_نقطہ_Parameterx (GLenum pname, GLfixed param);
GL_API خالی GL_APIENTRY gl_نقطہ_Parameterxv (GLenum pname, ثابت GLfixed *params);
GL_API خالی GL_APIENTRY gl_نقطہ_Sizex (GLfixed سائز);
GL_API خالی GL_APIENTRY glPolygonOffsetx (GLfixed ضربی_عدد, GLfixed units);
GL_API خالی GL_APIENTRY gl_نکالو_میٹرکس (خالی);
GL_API خالی GL_APIENTRY gl_ڈالو_میٹرکس (خالی);
GL_API خالی GL_APIENTRY glReadPixels (GLint x, GLint y, GLsizei چوڑائی, GLsizei اونچائی, GLenum format, GLenum type, خالی *pixels);
GL_API خالی GL_APIENTRY glRotatex (GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
GL_API خالی GL_APIENTRY glSampleCoverage (GLfloat قدر, GLboolean invert);
GL_API خالی GL_APIENTRY glSampleCoveragex (GLclampx قدر, GLboolean invert);
GL_API خالی GL_APIENTRY glScalex (GLfixed x, GLfixed y, GLfixed z);
GL_API خالی GL_APIENTRY glScissor (GLint x, GLint y, GLsizei چوڑائی, GLsizei اونچائی);
GL_API خالی GL_APIENTRY glShadeModel (GLenum منوال);
GL_API خالی GL_APIENTRY glStencilFunc (GLenum func, GLint ref, GLuint نقاب);
GL_API خالی GL_APIENTRY gl_Stencil_نقاب (GLuint نقاب);
GL_API خالی GL_APIENTRY glStencilOp (GLenum fail, GLenum zfail, GLenum zpass);
GL_API خالی GL_APIENTRY gl_Tex_Coord_اشارہ_گر (GLint سائز, GLenum type, GLsizei stride, ثابت خالی *اشارہ_گر_2);
GL_API خالی GL_APIENTRY glTexEnvi (GLenum ہدف, GLenum pname, GLint param);
GL_API خالی GL_APIENTRY glTexEnvx (GLenum ہدف, GLenum pname, GLfixed param);
GL_API خالی GL_APIENTRY glTexEnviv (GLenum ہدف, GLenum pname, ثابت GLint *params);
GL_API خالی GL_APIENTRY glTexEnvxv (GLenum ہدف, GLenum pname, ثابت GLfixed *params);
GL_API خالی GL_APIENTRY glTexImage2D (GLenum ہدف, GLint level, GLint internalformat, GLsizei چوڑائی, GLsizei اونچائی, GLint border, GLenum format, GLenum type, ثابت خالی *pixels);
GL_API خالی GL_APIENTRY glTexParameteri (GLenum ہدف, GLenum pname, GLint param);
GL_API خالی GL_APIENTRY glTexParameterx (GLenum ہدف, GLenum pname, GLfixed param);
GL_API خالی GL_APIENTRY glTexParameteriv (GLenum ہدف, GLenum pname, ثابت GLint *params);
GL_API خالی GL_APIENTRY glTexParameterxv (GLenum ہدف, GLenum pname, ثابت GLfixed *params);
GL_API خالی GL_APIENTRY glTexSubImage2D (GLenum ہدف, GLint level, GLint xoffset, GLint yoffset, GLsizei چوڑائی, GLsizei اونچائی, GLenum format, GLenum type, ثابت خالی *pixels);
GL_API خالی GL_APIENTRY glTranslatex (GLfixed x, GLfixed y, GLfixed z);
GL_API خالی GL_APIENTRY gl_راس_اشارہ_گر (GLint سائز, GLenum type, GLsizei stride, ثابت خالی *اشارہ_گر_2);
GL_API خالی GL_APIENTRY glViewport (GLint x, GLint y, GLsizei چوڑائی, GLsizei اونچائی);
#اگر_ختم /* GL_VERSION_ES_CM_1_0 */

#اگر_غیر_تعریف_شدہ GL_OES_compressed_paletted_texture
#تعریف_کرو GL_OES_compressed_paletted_texture 1
#تعریف_کرو GL_PALETTE4_RGB8_OES              0x8B90
#تعریف_کرو GL_PALETTE4_RGBA8_OES             0x8B91
#تعریف_کرو GL_PALETTE4_R5_G6_B5_OES          0x8B92
#تعریف_کرو GL_PALETTE4_RGBA4_OES             0x8B93
#تعریف_کرو GL_PALETTE4_RGB5_A1_OES           0x8B94
#تعریف_کرو GL_PALETTE8_RGB8_OES              0x8B95
#تعریف_کرو GL_PALETTE8_RGBA8_OES             0x8B96
#تعریف_کرو GL_PALETTE8_R5_G6_B5_OES          0x8B97
#تعریف_کرو GL_PALETTE8_RGBA4_OES             0x8B98
#تعریف_کرو GL_PALETTE8_RGB5_A1_OES           0x8B99
#اگر_ختم /* GL_OES_compressed_paletted_texture */

#اگر_غیر_تعریف_شدہ GL_OES_نقطہ_سائز_array
#تعریف_کرو GL_OES_نقطہ_سائز_array 1
#تعریف_کرو GL_نقطہ_سائز_ARRAY_OES           0x8B9C
#تعریف_کرو GL_نقطہ_سائز_ARRAY_TYPE_OES      0x898A
#تعریف_کرو GL_نقطہ_سائز_ARRAY_STRIDE_OES    0x898B
#تعریف_کرو GL_نقطہ_سائز_ARRAY_اشارہ_گر_OES   0x898C
#تعریف_کرو GL_نقطہ_سائز_ARRAY_بفر_BINDING_OES 0x8B9F
GL_API خالی GL_APIENTRY gl_نقطہ_سائز_اشارہ_گر_OES (GLenum type, GLsizei stride, ثابت خالی *اشارہ_گر_2);
#اگر_ختم /* GL_OES_point_size_array */

#اگر_غیر_تعریف_شدہ GL_OES_نقطہ_sprite
#تعریف_کرو GL_OES_نقطہ_sprite 1
#تعریف_کرو GL_نقطہ_SPRITE_OES               0x8861
#تعریف_کرو GL_COORD_REPLACE_OES              0x8862
#اگر_ختم /* GL_OES_point_sprite */

#اگر_غیر_تعریف_شدہ GL_OES_read_format
#تعریف_کرو GL_OES_read_format 1
#تعریف_کرو GL_IMPLEMENTATION_COLOR_READ_TYPE_OES 0x8B9A
#تعریف_کرو GL_IMPLEMENTATION_COLOR_READ_FORMAT_OES 0x8B9B
#اگر_ختم /* GL_OES_read_format */

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم
