#నిర్వచితం_కాకపోతే __gles1_gl_h_
#నిర్వచించు __gles1_gl_h_ 1

#నిర్వచితమైతే __cplusplus
బాహ్య "C" {
#అయితే_ముగింపు

/*
** Copyright 2013-2026 The Khronos Group Inc.
** SPDX-License-Identifier: MIT
**
** This header is generated from the Khronos OpenGL / OpenGL ES XML
** API Registry. The current version of the Registry, generator scripts
** used to make the header, and the header can be found at
**   https://github.com/KhronosGroup/OpenGL-Registry
*/

#అన్తర్భావ <GLES/glplatform.h>

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

#నిర్వచితం_కాకపోతే GL_సంస్కరణ_ES_CM_1_0
#నిర్వచించు GL_సంస్కరణ_ES_CM_1_0 1
#అన్తర్భావ <KHR/khrplatform.h>
రకనిర్వచనం khronos_int8_t GLbyte;
రకనిర్వచనం khronos_float_t GLclampf;
రకనిర్వచనం khronos_int16_t GLshort;
రకనిర్వచనం khronos_uint16_t GLushort;
రకనిర్వచనం శూన్య GLvoid;
రకనిర్వచనం గుర్తులేని పూర్ణాంకం GLenum;
రకనిర్వచనం khronos_float_t GLfloat;
రకనిర్వచనం khronos_int32_t GLfixed;
రకనిర్వచనం గుర్తులేని పూర్ణాంకం GLuint;
రకనిర్వచనం khronos_ssize_t GLsizeiptr;
రకనిర్వచనం khronos_intptr_t GLintptr;
రకనిర్వచనం గుర్తులేని పూర్ణాంకం GLbitfield;
రకనిర్వచనం పూర్ణాంకం GLint;
రకనిర్వచనం khronos_uint8_t GLubyte;
రకనిర్వచనం గుర్తులేని అక్షరం GLboolean;
రకనిర్వచనం పూర్ణాంకం GLsizei;
రకనిర్వచనం khronos_int32_t GLclampx;
#నిర్వచించు GL_సంస్కరణ_ES_CL_1_0              1
#నిర్వచించు GL_సంస్కరణ_ES_CM_1_1              1
#నిర్వచించు GL_సంస్కరణ_ES_CL_1_1              1
#నిర్వచించు GL_లోతు_బఫరు_బిట్టు               0x00000100
#నిర్వచించు GL_STENCIL_బఫరు_బిట్టు             0x00000400
#నిర్వచించు GL_COLOR_బఫరు_బిట్టు               0x00004000
#నిర్వచించు GL_FALSE                          0
#నిర్వచించు GL_TRUE                           1
#నిర్వచించు GL_POINTS                         0x0000
#నిర్వచించు GL_పంక్తులు                          0x0001
#నిర్వచించు GL_పంక్తి_LOOP                      0x0002
#నిర్వచించు GL_పంక్తి_STRIP                     0x0003
#నిర్వచించు GL_TRIANGLES                      0x0004
#నిర్వచించు GL_TRIANGLE_STRIP                 0x0005
#నిర్వచించు GL_TRIANGLE_FAN                   0x0006
#నిర్వచించు GL_NEVER                          0x0200
#నిర్వచించు GL_LESS                           0x0201
#నిర్వచించు GL_EQUAL                          0x0202
#నిర్వచించు GL_LEQUAL                         0x0203
#నిర్వచించు GL_GREATER                        0x0204
#నిర్వచించు GL_NOTEQUAL                       0x0205
#నిర్వచించు GL_GEQUAL                         0x0206
#నిర్వచించు GL_ALWAYS                         0x0207
#నిర్వచించు GL_ZERO                           0
#నిర్వచించు GL_ONE                            1
#నిర్వచించు GL_SRC_COLOR                      0x0300
#నిర్వచించు GL_ONE_MINUS_SRC_COLOR            0x0301
#నిర్వచించు GL_SRC_ALPHA                      0x0302
#నిర్వచించు GL_ONE_MINUS_SRC_ALPHA            0x0303
#నిర్వచించు GL_DST_ALPHA                      0x0304
#నిర్వచించు GL_ONE_MINUS_DST_ALPHA            0x0305
#నిర్వచించు GL_DST_COLOR                      0x0306
#నిర్వచించు GL_ONE_MINUS_DST_COLOR            0x0307
#నిర్వచించు GL_SRC_ALPHA_SATURATE             0x0308
#నిర్వచించు GL_CLIP_PLANE0                    0x3000
#నిర్వచించు GL_CLIP_PLANE1                    0x3001
#నిర్వచించు GL_CLIP_PLANE2                    0x3002
#నిర్వచించు GL_CLIP_PLANE3                    0x3003
#నిర్వచించు GL_CLIP_PLANE4                    0x3004
#నిర్వచించు GL_CLIP_PLANE5                    0x3005
#నిర్వచించు GL_FRONT                          0x0404
#నిర్వచించు GL_వెనుక                           0x0405
#నిర్వచించు GL_FRONT_AND_వెనుక                 0x0408
#నిర్వచించు GL_FOG                            0x0B60
#నిర్వచించు GL_LIGHTING                       0x0B50
#నిర్వచించు GL_TEXTURE_2D                     0x0DE1
#నిర్వచించు GL_CULL_FACE                      0x0B44
#నిర్వచించు GL_ALPHA_TEST                     0x0BC0
#నిర్వచించు GL_BLEND                          0x0BE2
#నిర్వచించు GL_COLOR_LOGIC_OP                 0x0BF2
#నిర్వచించు GL_DITHER                         0x0BD0
#నిర్వచించు GL_STENCIL_TEST                   0x0B90
#నిర్వచించు GL_లోతు_TEST                     0x0B71
#నిర్వచించు GL_బిందువు_SMOOTH                   0x0B10
#నిర్వచించు GL_పంక్తి_SMOOTH                    0x0B20
#నిర్వచించు GL_SCISSOR_TEST                   0x0C11
#నిర్వచించు GL_COLOR_MATERIAL                 0x0B57
#నిర్వచించు GL_NORMALIZE                      0x0BA1
#నిర్వచించు GL_RESCALE_సాధారణ                 0x803A
#నిర్వచించు GL_శీర్షం_ARRAY                   0x8074
#నిర్వచించు GL_సాధారణ_ARRAY                   0x8075
#నిర్వచించు GL_COLOR_ARRAY                    0x8076
#నిర్వచించు GL_TEXTURE_COORD_ARRAY            0x8078
#నిర్వచించు GL_MULTISAMPLE                    0x809D
#నిర్వచించు GL_SAMPLE_ALPHA_గమ్యం_COVERAGE       0x809E
#నిర్వచించు GL_SAMPLE_ALPHA_గమ్యం_ONE            0x809F
#నిర్వచించు GL_SAMPLE_COVERAGE                0x80A0
#నిర్వచించు GL_NO_ERROR                       0
#నిర్వచించు GL_INVALID_ENUM                   0x0500
#నిర్వచించు GL_INVALID_విలువ                  0x0501
#నిర్వచించు GL_INVALID_OPERATION              0x0502
#నిర్వచించు GL_దొంతర_అధికప్రవాహం                 0x0503
#నిర్వచించు GL_దొంతర_UNDERFLOW                0x0504
#నిర్వచించు GL_బహిర్గతం_యొక్క_జ్ఞాపకం                  0x0505
#నిర్వచించు GL_EXP                            0x0800
#నిర్వచించు GL_EXP2                           0x0801
#నిర్వచించు GL_FOG_DENSITY                    0x0B62
#నిర్వచించు GL_FOG_ప్రారంభం                      0x0B63
#నిర్వచించు GL_FOG_చివర                        0x0B64
#నిర్వచించు GL_FOG_బహుళకం                       0x0B65
#నిర్వచించు GL_FOG_COLOR                      0x0B66
#నిర్వచించు GL_CW                             0x0900
#నిర్వచించు GL_CCW                            0x0901
#నిర్వచించు GL_CURRENT_COLOR                  0x0B00
#నిర్వచించు GL_CURRENT_సాధారణ                 0x0B02
#నిర్వచించు GL_CURRENT_TEXTURE_COORDS         0x0B03
#నిర్వచించు GL_బిందువు_కొలత                     0x0B11
#నిర్వచించు GL_బిందువు_కొలత_MIN                 0x8126
#నిర్వచించు GL_బిందువు_కొలత_MAX                 0x8127
#నిర్వచించు GL_బిందువు_FADE_పరిమితి_కొలత      0x8128
#నిర్వచించు GL_బిందువు_దూరం_ATTENUATION     0x8129
#నిర్వచించు GL_SMOOTH_బిందువు_కొలత_RANGE        0x0B12
#నిర్వచించు GL_పంక్తి_వెడల్పు                     0x0B21
#నిర్వచించు GL_SMOOTH_పంక్తి_వెడల్పు_RANGE        0x0B22
#నిర్వచించు GL_ALIASED_బిందువు_కొలత_RANGE       0x846D
#నిర్వచించు GL_ALIASED_పంక్తి_వెడల్పు_RANGE       0x846E
#నిర్వచించు GL_CULL_FACE_బహుళకం                 0x0B45
#నిర్వచించు GL_FRONT_FACE                     0x0B46
#నిర్వచించు GL_SHADE_MODEL                    0x0B54
#నిర్వచించు GL_లోతు_RANGE                    0x0B70
#నిర్వచించు GL_లోతు_WRITEMASK                0x0B72
#నిర్వచించు GL_లోతు_CLEAR_విలువ              0x0B73
#నిర్వచించు GL_లోతు_FUNC                     0x0B74
#నిర్వచించు GL_STENCIL_CLEAR_విలువ            0x0B91
#నిర్వచించు GL_STENCIL_FUNC                   0x0B92
#నిర్వచించు GL_STENCIL_విలువ_ముసుగు             0x0B93
#నిర్వచించు GL_STENCIL_FAIL                   0x0B94
#నిర్వచించు GL_STENCIL_PASS_లోతు_FAIL        0x0B95
#నిర్వచించు GL_STENCIL_PASS_లోతు_PASS        0x0B96
#నిర్వచించు GL_STENCIL_REF                    0x0B97
#నిర్వచించు GL_STENCIL_WRITEMASK              0x0B98
#నిర్వచించు GL_మాతృక_బహుళకం                    0x0BA0
#నిర్వచించు GL_VIEWPORT                       0x0BA2
#నిర్వచించు GL_MODELVIEW_దొంతర_లోతు          0x0BA3
#నిర్వచించు GL_PROJECTION_దొంతర_లోతు         0x0BA4
#నిర్వచించు GL_TEXTURE_దొంతర_లోతు            0x0BA5
#నిర్వచించు GL_MODELVIEW_మాతృక               0x0BA6
#నిర్వచించు GL_PROJECTION_మాతృక              0x0BA7
#నిర్వచించు GL_TEXTURE_మాతృక                 0x0BA8
#నిర్వచించు GL_ALPHA_TEST_FUNC                0x0BC1
#నిర్వచించు GL_ALPHA_TEST_REF                 0x0BC2
#నిర్వచించు GL_BLEND_DST                      0x0BE0
#నిర్వచించు GL_BLEND_SRC                      0x0BE1
#నిర్వచించు GL_LOGIC_OP_బహుళకం                  0x0BF0
#నిర్వచించు GL_SCISSOR_BOX                    0x0C10
#నిర్వచించు GL_COLOR_CLEAR_విలువ              0x0C22
#నిర్వచించు GL_COLOR_WRITEMASK                0x0C23
#నిర్వచించు GL_MAX_LIGHTS                     0x0D31
#నిర్వచించు GL_MAX_CLIP_PLANES                0x0D32
#నిర్వచించు GL_MAX_TEXTURE_కొలత               0x0D33
#నిర్వచించు GL_MAX_MODELVIEW_దొంతర_లోతు      0x0D36
#నిర్వచించు GL_MAX_PROJECTION_దొంతర_లోతు     0x0D38
#నిర్వచించు GL_MAX_TEXTURE_దొంతర_లోతు        0x0D39
#నిర్వచించు GL_MAX_VIEWPORT_DIMS              0x0D3A
#నిర్వచించు GL_MAX_TEXTURE_UNITS              0x84E2
#నిర్వచించు GL_SUBPIXEL_బిట్లు                  0x0D50
#నిర్వచించు GL_RED_బిట్లు                       0x0D52
#నిర్వచించు GL_GREEN_బిట్లు                     0x0D53
#నిర్వచించు GL_BLUE_బిట్లు                      0x0D54
#నిర్వచించు GL_ALPHA_బిట్లు                     0x0D55
#నిర్వచించు GL_లోతు_బిట్లు                     0x0D56
#నిర్వచించు GL_STENCIL_బిట్లు                   0x0D57
#నిర్వచించు GL_POLYGON_స్థానభ్రంశం_UNITS           0x2A00
#నిర్వచించు GL_POLYGON_స్థానభ్రంశం_FILL            0x8037
#నిర్వచించు GL_POLYGON_స్థానభ్రంశం_గుణకం          0x8038
#నిర్వచించు GL_TEXTURE_BINDING_2D             0x8069
#నిర్వచించు GL_శీర్షం_ARRAY_కొలత              0x807A
#నిర్వచించు GL_శీర్షం_ARRAY_TYPE              0x807B
#నిర్వచించు GL_శీర్షం_ARRAY_STRIDE            0x807C
#నిర్వచించు GL_సాధారణ_ARRAY_TYPE              0x807E
#నిర్వచించు GL_సాధారణ_ARRAY_STRIDE            0x807F
#నిర్వచించు GL_COLOR_ARRAY_కొలత               0x8081
#నిర్వచించు GL_COLOR_ARRAY_TYPE               0x8082
#నిర్వచించు GL_COLOR_ARRAY_STRIDE             0x8083
#నిర్వచించు GL_TEXTURE_COORD_ARRAY_కొలత       0x8088
#నిర్వచించు GL_TEXTURE_COORD_ARRAY_TYPE       0x8089
#నిర్వచించు GL_TEXTURE_COORD_ARRAY_STRIDE     0x808A
#నిర్వచించు GL_శీర్షం_ARRAY_సూచిక           0x808E
#నిర్వచించు GL_సాధారణ_ARRAY_సూచిక           0x808F
#నిర్వచించు GL_COLOR_ARRAY_సూచిక            0x8090
#నిర్వచించు GL_TEXTURE_COORD_ARRAY_సూచిక    0x8092
#నిర్వచించు GL_SAMPLE_BUFFERS                 0x80A8
#నిర్వచించు GL_SAMPLES                        0x80A9
#నిర్వచించు GL_SAMPLE_COVERAGE_విలువ          0x80AA
#నిర్వచించు GL_SAMPLE_COVERAGE_INVERT         0x80AB
#నిర్వచించు GL_అంకె_COMPRESSED_TEXTURE_FORMATS 0x86A2
#నిర్వచించు GL_COMPRESSED_TEXTURE_FORMATS     0x86A3
#నిర్వచించు GL_DONT_CARE                      0x1100
#నిర్వచించు GL_FASTEST                        0x1101
#నిర్వచించు GL_NICEST                         0x1102
#నిర్వచించు GL_PERSPECTIVE_CORRECTION_HINT    0x0C50
#నిర్వచించు GL_బిందువు_SMOOTH_HINT              0x0C51
#నిర్వచించు GL_పంక్తి_SMOOTH_HINT               0x0C52
#నిర్వచించు GL_FOG_HINT                       0x0C54
#నిర్వచించు GL_GENERATE_MIPMAP_HINT           0x8192
#నిర్వచించు GL_LIGHT_MODEL_AMBIENT            0x0B53
#నిర్వచించు GL_LIGHT_MODEL_TWO_SIDE           0x0B52
#నిర్వచించు GL_AMBIENT                        0x1200
#నిర్వచించు GL_DIFFUSE                        0x1201
#నిర్వచించు GL_SPECULAR                       0x1202
#నిర్వచించు GL_POSITION                       0x1203
#నిర్వచించు GL_SPOT_DIRECTION                 0x1204
#నిర్వచించు GL_SPOT_EXPONENT                  0x1205
#నిర్వచించు GL_SPOT_CUTOFF                    0x1206
#నిర్వచించు GL_CONSTANT_ATTENUATION           0x1207
#నిర్వచించు GL_రేఖీయ_ATTENUATION             0x1208
#నిర్వచించు GL_QUADRATIC_ATTENUATION          0x1209
#నిర్వచించు GL_BYTE                           0x1400
#నిర్వచించు GL_UNSIGNED_BYTE                  0x1401
#నిర్వచించు GL_SHORT                          0x1402
#నిర్వచించు GL_UNSIGNED_SHORT                 0x1403
#నిర్వచించు GL_FLOAT                          0x1406
#నిర్వచించు GL_FIXED                          0x140C
#నిర్వచించు GL_CLEAR                          0x1500
#నిర్వచించు GL_AND                            0x1501
#నిర్వచించు GL_AND_తిరగేయి                    0x1502
#నిర్వచించు GL_COPY                           0x1503
#నిర్వచించు GL_AND_INVERTED                   0x1504
#నిర్వచించు GL_NOOP                           0x1505
#నిర్వచించు GL_XOR                            0x1506
#నిర్వచించు GL_OR                             0x1507
#నిర్వచించు GL_NOR                            0x1508
#నిర్వచించు GL_EQUIV                          0x1509
#నిర్వచించు GL_INVERT                         0x150A
#నిర్వచించు GL_OR_తిరగేయి                     0x150B
#నిర్వచించు GL_COPY_INVERTED                  0x150C
#నిర్వచించు GL_OR_INVERTED                    0x150D
#నిర్వచించు GL_NAND                           0x150E
#నిర్వచించు GL_సమితి                            0x150F
#నిర్వచించు GL_EMISSION                       0x1600
#నిర్వచించు GL_SHININESS                      0x1601
#నిర్వచించు GL_AMBIENT_AND_DIFFUSE            0x1602
#నిర్వచించు GL_MODELVIEW                      0x1700
#నిర్వచించు GL_PROJECTION                     0x1701
#నిర్వచించు GL_TEXTURE                        0x1702
#నిర్వచించు GL_ALPHA                          0x1906
#నిర్వచించు GL_RGB                            0x1907
#నిర్వచించు GL_RGBA                           0x1908
#నిర్వచించు GL_LUMINANCE                      0x1909
#నిర్వచించు GL_LUMINANCE_ALPHA                0x190A
#నిర్వచించు GL_UNPACK_ALIGNMENT               0x0CF5
#నిర్వచించు GL_PACK_ALIGNMENT                 0x0D05
#నిర్వచించు GL_UNSIGNED_SHORT_4_4_4_4         0x8033
#నిర్వచించు GL_UNSIGNED_SHORT_5_5_5_1         0x8034
#నిర్వచించు GL_UNSIGNED_SHORT_5_6_5           0x8363
#నిర్వచించు GL_FLAT                           0x1D00
#నిర్వచించు GL_SMOOTH                         0x1D01
#నిర్వచించు GL_KEEP                           0x1E00
#నిర్వచించు GL_REPLACE                        0x1E01
#నిర్వచించు GL_INCR                           0x1E02
#నిర్వచించు GL_DECR                           0x1E03
#నిర్వచించు GL_VENDOR                         0x1F00
#నిర్వచించు GL_RENDERER                       0x1F01
#నిర్వచించు GL_సంస్కరణ                        0x1F02
#నిర్వచించు GL_EXTENSIONS                     0x1F03
#నిర్వచించు GL_MODULATE                       0x2100
#నిర్వచించు GL_DECAL                          0x2101
#నిర్వచించు GL_కూడు                            0x0104
#నిర్వచించు GL_TEXTURE_ENV_బహుళకం               0x2200
#నిర్వచించు GL_TEXTURE_ENV_COLOR              0x2201
#నిర్వచించు GL_TEXTURE_ENV                    0x2300
#నిర్వచించు GL_సమీప                        0x2600
#నిర్వచించు GL_రేఖీయ                         0x2601
#నిర్వచించు GL_సమీప_MIPMAP_సమీప         0x2700
#నిర్వచించు GL_రేఖీయ_MIPMAP_సమీప          0x2701
#నిర్వచించు GL_సమీప_MIPMAP_రేఖీయ          0x2702
#నిర్వచించు GL_రేఖీయ_MIPMAP_రేఖీయ           0x2703
#నిర్వచించు GL_TEXTURE_MAG_FILTER             0x2800
#నిర్వచించు GL_TEXTURE_MIN_FILTER             0x2801
#నిర్వచించు GL_TEXTURE_WRAP_S                 0x2802
#నిర్వచించు GL_TEXTURE_WRAP_T                 0x2803
#నిర్వచించు GL_GENERATE_MIPMAP                0x8191
#నిర్వచించు GL_TEXTURE0                       0x84C0
#నిర్వచించు GL_TEXTURE1                       0x84C1
#నిర్వచించు GL_TEXTURE2                       0x84C2
#నిర్వచించు GL_TEXTURE3                       0x84C3
#నిర్వచించు GL_TEXTURE4                       0x84C4
#నిర్వచించు GL_TEXTURE5                       0x84C5
#నిర్వచించు GL_TEXTURE6                       0x84C6
#నిర్వచించు GL_TEXTURE7                       0x84C7
#నిర్వచించు GL_TEXTURE8                       0x84C8
#నిర్వచించు GL_TEXTURE9                       0x84C9
#నిర్వచించు GL_TEXTURE10                      0x84CA
#నిర్వచించు GL_TEXTURE11                      0x84CB
#నిర్వచించు GL_TEXTURE12                      0x84CC
#నిర్వచించు GL_TEXTURE13                      0x84CD
#నిర్వచించు GL_TEXTURE14                      0x84CE
#నిర్వచించు GL_TEXTURE15                      0x84CF
#నిర్వచించు GL_TEXTURE16                      0x84D0
#నిర్వచించు GL_TEXTURE17                      0x84D1
#నిర్వచించు GL_TEXTURE18                      0x84D2
#నిర్వచించు GL_TEXTURE19                      0x84D3
#నిర్వచించు GL_TEXTURE20                      0x84D4
#నిర్వచించు GL_TEXTURE21                      0x84D5
#నిర్వచించు GL_TEXTURE22                      0x84D6
#నిర్వచించు GL_TEXTURE23                      0x84D7
#నిర్వచించు GL_TEXTURE24                      0x84D8
#నిర్వచించు GL_TEXTURE25                      0x84D9
#నిర్వచించు GL_TEXTURE26                      0x84DA
#నిర్వచించు GL_TEXTURE27                      0x84DB
#నిర్వచించు GL_TEXTURE28                      0x84DC
#నిర్వచించు GL_TEXTURE29                      0x84DD
#నిర్వచించు GL_TEXTURE30                      0x84DE
#నిర్వచించు GL_TEXTURE31                      0x84DF
#నిర్వచించు GL_చురుకైన_TEXTURE                 0x84E0
#నిర్వచించు GL_CLIENT_చురుకైన_TEXTURE          0x84E1
#నిర్వచించు GL_REPEAT                         0x2901
#నిర్వచించు GL_CLAMP_గమ్యం_అంచు                  0x812F
#నిర్వచించు GL_LIGHT0                         0x4000
#నిర్వచించు GL_LIGHT1                         0x4001
#నిర్వచించు GL_LIGHT2                         0x4002
#నిర్వచించు GL_LIGHT3                         0x4003
#నిర్వచించు GL_LIGHT4                         0x4004
#నిర్వచించు GL_LIGHT5                         0x4005
#నిర్వచించు GL_LIGHT6                         0x4006
#నిర్వచించు GL_LIGHT7                         0x4007
#నిర్వచించు GL_ARRAY_బఫరు                   0x8892
#నిర్వచించు GL_ELEMENT_ARRAY_బఫరు           0x8893
#నిర్వచించు GL_ARRAY_బఫరు_BINDING           0x8894
#నిర్వచించు GL_ELEMENT_ARRAY_బఫరు_BINDING   0x8895
#నిర్వచించు GL_శీర్షం_ARRAY_బఫరు_BINDING    0x8896
#నిర్వచించు GL_సాధారణ_ARRAY_బఫరు_BINDING    0x8897
#నిర్వచించు GL_COLOR_ARRAY_బఫరు_BINDING     0x8898
#నిర్వచించు GL_TEXTURE_COORD_ARRAY_బఫరు_BINDING 0x889A
#నిర్వచించు GL_STATIC_DRAW                    0x88E4
#నిర్వచించు GL_DYNAMIC_DRAW                   0x88E8
#నిర్వచించు GL_బఫరు_కొలత                    0x8764
#నిర్వచించు GL_బఫరు_USAGE                   0x8765
#నిర్వచించు GL_వ్యవకలనం                       0x84E7
#నిర్వచించు GL_COMBINE                        0x8570
#నిర్వచించు GL_COMBINE_RGB                    0x8571
#నిర్వచించు GL_COMBINE_ALPHA                  0x8572
#నిర్వచించు GL_RGB_SCALE                      0x8573
#నిర్వచించు GL_కూడు_SIGNED                     0x8574
#నిర్వచించు GL_INTERPOLATE                    0x8575
#నిర్వచించు GL_CONSTANT                       0x8576
#నిర్వచించు GL_PRIMARY_COLOR                  0x8577
#నిర్వచించు GL_మునుపటి                       0x8578
#నిర్వచించు GL_OPERAND0_RGB                   0x8590
#నిర్వచించు GL_OPERAND1_RGB                   0x8591
#నిర్వచించు GL_OPERAND2_RGB                   0x8592
#నిర్వచించు GL_OPERAND0_ALPHA                 0x8598
#నిర్వచించు GL_OPERAND1_ALPHA                 0x8599
#నిర్వచించు GL_OPERAND2_ALPHA                 0x859A
#నిర్వచించు GL_ALPHA_SCALE                    0x0D1C
#నిర్వచించు GL_SRC0_RGB                       0x8580
#నిర్వచించు GL_SRC1_RGB                       0x8581
#నిర్వచించు GL_SRC2_RGB                       0x8582
#నిర్వచించు GL_SRC0_ALPHA                     0x8588
#నిర్వచించు GL_SRC1_ALPHA                     0x8589
#నిర్వచించు GL_SRC2_ALPHA                     0x858A
#నిర్వచించు GL_DOT3_RGB                       0x86AE
#నిర్వచించు GL_DOT3_RGBA                      0x86AF
GL_API శూన్య GL_APIENTRY glAlphaFunc (GLenum func, GLfloat ref);
GL_API శూన్య GL_APIENTRY glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_API శూన్య GL_APIENTRY glClearDepthf (GLfloat d);
GL_API శూన్య GL_APIENTRY glClipPlanef (GLenum p, స్థిరరాశి GLfloat *eqn);
GL_API శూన్య GL_APIENTRY glColor4f (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_API శూన్య GL_APIENTRY gl_లోతు_Rangef (GLfloat n, GLfloat f);
GL_API శూన్య GL_APIENTRY glFogf (GLenum pname, GLfloat param);
GL_API శూన్య GL_APIENTRY glFogfv (GLenum pname, స్థిరరాశి GLfloat *params);
GL_API శూన్య GL_APIENTRY glFrustumf (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
GL_API శూన్య GL_APIENTRY glGetClipPlanef (GLenum plane, GLfloat *equation);
GL_API శూన్య GL_APIENTRY glGetFloatv (GLenum pname, GLfloat *దత్తాంశం);
GL_API శూన్య GL_APIENTRY glGetLightfv (GLenum light, GLenum pname, GLfloat *params);
GL_API శూన్య GL_APIENTRY glGetMaterialfv (GLenum face, GLenum pname, GLfloat *params);
GL_API శూన్య GL_APIENTRY glGetTexEnvfv (GLenum లక్ష్యం, GLenum pname, GLfloat *params);
GL_API శూన్య GL_APIENTRY glGetTexParameterfv (GLenum లక్ష్యం, GLenum pname, GLfloat *params);
GL_API శూన్య GL_APIENTRY glLightModelf (GLenum pname, GLfloat param);
GL_API శూన్య GL_APIENTRY glLightModelfv (GLenum pname, స్థిరరాశి GLfloat *params);
GL_API శూన్య GL_APIENTRY glLightf (GLenum light, GLenum pname, GLfloat param);
GL_API శూన్య GL_APIENTRY glLightfv (GLenum light, GLenum pname, స్థిరరాశి GLfloat *params);
GL_API శూన్య GL_APIENTRY gl_పంక్తి_వెడల్పు (GLfloat వెడల్పు);
GL_API శూన్య GL_APIENTRY gl_ఎక్కించు_Matrixf (స్థిరరాశి GLfloat *m);
GL_API శూన్య GL_APIENTRY glMaterialf (GLenum face, GLenum pname, GLfloat param);
GL_API శూన్య GL_APIENTRY glMaterialfv (GLenum face, GLenum pname, స్థిరరాశి GLfloat *params);
GL_API శూన్య GL_APIENTRY glMultMatrixf (స్థిరరాశి GLfloat *m);
GL_API శూన్య GL_APIENTRY glMultiTexCoord4f (GLenum లక్ష్యం, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
GL_API శూన్య GL_APIENTRY glNormal3f (GLfloat nx, GLfloat ny, GLfloat nz);
GL_API శూన్య GL_APIENTRY glOrthof (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
GL_API శూన్య GL_APIENTRY gl_బిందువు_Parameterf (GLenum pname, GLfloat param);
GL_API శూన్య GL_APIENTRY gl_బిందువు_Parameterfv (GLenum pname, స్థిరరాశి GLfloat *params);
GL_API శూన్య GL_APIENTRY gl_బిందువు_కొలత (GLfloat కొలత);
GL_API శూన్య GL_APIENTRY gl_Polygon_స్థానభ్రంశం (GLfloat గుణకం, GLfloat units);
GL_API శూన్య GL_APIENTRY glRotatef (GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
GL_API శూన్య GL_APIENTRY glScalef (GLfloat x, GLfloat y, GLfloat z);
GL_API శూన్య GL_APIENTRY glTexEnvf (GLenum లక్ష్యం, GLenum pname, GLfloat param);
GL_API శూన్య GL_APIENTRY glTexEnvfv (GLenum లక్ష్యం, GLenum pname, స్థిరరాశి GLfloat *params);
GL_API శూన్య GL_APIENTRY glTexParameterf (GLenum లక్ష్యం, GLenum pname, GLfloat param);
GL_API శూన్య GL_APIENTRY glTexParameterfv (GLenum లక్ష్యం, GLenum pname, స్థిరరాశి GLfloat *params);
GL_API శూన్య GL_APIENTRY glTranslatef (GLfloat x, GLfloat y, GLfloat z);
GL_API శూన్య GL_APIENTRY gl_చురుకైన_Texture (GLenum texture);
GL_API శూన్య GL_APIENTRY glAlphaFuncx (GLenum func, GLfixed ref);
GL_API శూన్య GL_APIENTRY gl_Bind_బఫరు (GLenum లక్ష్యం, GLuint బఫరు_2);
GL_API శూన్య GL_APIENTRY glBindTexture (GLenum లక్ష్యం, GLuint texture);
GL_API శూన్య GL_APIENTRY glBlendFunc (GLenum sfactor, GLenum dfactor);
GL_API శూన్య GL_APIENTRY gl_బఫరు_దత్తాంశం (GLenum లక్ష్యం, GLsizeiptr కొలత, స్థిరరాశి శూన్య *దత్తాంశం, GLenum usage);
GL_API శూన్య GL_APIENTRY gl_బఫరు_Sub_దత్తాంశం (GLenum లక్ష్యం, GLintptr స్థానభ్రంశం_2, GLsizeiptr కొలత, స్థిరరాశి శూన్య *దత్తాంశం);
GL_API శూన్య GL_APIENTRY glClear (GLbitfield ముసుగు);
GL_API శూన్య GL_APIENTRY glClearColorx (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GL_API శూన్య GL_APIENTRY glClearDepthx (GLfixed లోతు_2);
GL_API శూన్య GL_APIENTRY glClearStencil (GLint s);
GL_API శూన్య GL_APIENTRY gl_Client_చురుకైన_Texture (GLenum texture);
GL_API శూన్య GL_APIENTRY glClipPlanex (GLenum plane, స్థిరరాశి GLfixed *equation);
GL_API శూన్య GL_APIENTRY glColor4ub (GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
GL_API శూన్య GL_APIENTRY glColor4x (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GL_API శూన్య GL_APIENTRY gl_Color_ముసుగు (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
GL_API శూన్య GL_APIENTRY gl_Color_సూచిక (GLint కొలత, GLenum type, GLsizei stride, స్థిరరాశి శూన్య *సూచిక_2);
GL_API శూన్య GL_APIENTRY glCompressedTexImage2D (GLenum లక్ష్యం, GLint level, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు, GLint border, GLsizei image_కొలత, స్థిరరాశి శూన్య *దత్తాంశం);
GL_API శూన్య GL_APIENTRY glCompressedTexSubImage2D (GLenum లక్ష్యం, GLint level, GLint xoffset, GLint yoffset, GLsizei వెడల్పు, GLsizei ఎత్తు, GLenum format, GLsizei image_కొలత, స్థిరరాశి శూన్య *దత్తాంశం);
GL_API శూన్య GL_APIENTRY glCopyTexImage2D (GLenum లక్ష్యం, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei వెడల్పు, GLsizei ఎత్తు, GLint border);
GL_API శూన్య GL_APIENTRY glCopyTexSubImage2D (GLenum లక్ష్యం, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei వెడల్పు, GLsizei ఎత్తు);
GL_API శూన్య GL_APIENTRY glCullFace (GLenum బహుళకం);
GL_API శూన్య GL_APIENTRY glDeleteBuffers (GLsizei n, స్థిరరాశి GLuint *buffers);
GL_API శూన్య GL_APIENTRY glDeleteTextures (GLsizei n, స్థిరరాశి GLuint *textures);
GL_API శూన్య GL_APIENTRY gl_లోతు_Func (GLenum func);
GL_API శూన్య GL_APIENTRY gl_లోతు_ముసుగు (GLboolean flag);
GL_API శూన్య GL_APIENTRY gl_లోతు_Rangex (GLfixed n, GLfixed f);
GL_API శూన్య GL_APIENTRY glDisable (GLenum cap);
GL_API శూన్య GL_APIENTRY glDisableClientState (GLenum array);
GL_API శూన్య GL_APIENTRY glDrawArrays (GLenum బహుళకం, GLint మొదటి, GLsizei లెక్క);
GL_API శూన్య GL_APIENTRY glDrawElements (GLenum బహుళకం, GLsizei లెక్క, GLenum type, స్థిరరాశి శూన్య *indices);
GL_API శూన్య GL_APIENTRY glEnable (GLenum cap);
GL_API శూన్య GL_APIENTRY glEnableClientState (GLenum array);
GL_API శూన్య GL_APIENTRY gl_ముగింపు (శూన్య);
GL_API శూన్య GL_APIENTRY glFlush (శూన్య);
GL_API శూన్య GL_APIENTRY glFogx (GLenum pname, GLfixed param);
GL_API శూన్య GL_APIENTRY glFogxv (GLenum pname, స్థిరరాశి GLfixed *param);
GL_API శూన్య GL_APIENTRY glFrontFace (GLenum బహుళకం);
GL_API శూన్య GL_APIENTRY glFrustumx (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
GL_API శూన్య GL_APIENTRY glGetBooleanv (GLenum pname, GLboolean *దత్తాంశం);
GL_API శూన్య GL_APIENTRY gl_Get_బఫరు_Parameteriv (GLenum లక్ష్యం, GLenum pname, GLint *params);
GL_API శూన్య GL_APIENTRY glGetClipPlanex (GLenum plane, GLfixed *equation);
GL_API శూన్య GL_APIENTRY glGenBuffers (GLsizei n, GLuint *buffers);
GL_API శూన్య GL_APIENTRY glGenTextures (GLsizei n, GLuint *textures);
GL_API GLenum GL_APIENTRY glGetError (శూన్య);
GL_API శూన్య GL_APIENTRY glGetFixedv (GLenum pname, GLfixed *దత్తాంశం);
GL_API శూన్య GL_APIENTRY glGetIntegerv (GLenum pname, GLint *దత్తాంశం);
GL_API శూన్య GL_APIENTRY glGetLightxv (GLenum light, GLenum pname, GLfixed *params);
GL_API శూన్య GL_APIENTRY glGetMaterialxv (GLenum face, GLenum pname, GLfixed *params);
GL_API శూన్య GL_APIENTRY glGetPointerv (GLenum pname, శూన్య **params);
GL_API స్థిరరాశి GLubyte *GL_APIENTRY glGetString (GLenum name);
GL_API శూన్య GL_APIENTRY glGetTexEnviv (GLenum లక్ష్యం, GLenum pname, GLint *params);
GL_API శూన్య GL_APIENTRY glGetTexEnvxv (GLenum లక్ష్యం, GLenum pname, GLfixed *params);
GL_API శూన్య GL_APIENTRY glGetTexParameteriv (GLenum లక్ష్యం, GLenum pname, GLint *params);
GL_API శూన్య GL_APIENTRY glGetTexParameterxv (GLenum లక్ష్యం, GLenum pname, GLfixed *params);
GL_API శూన్య GL_APIENTRY glHint (GLenum లక్ష్యం, GLenum బహుళకం);
GL_API GLboolean GL_APIENTRY gl_Is_బఫరు (GLuint బఫరు_2);
GL_API GLboolean GL_APIENTRY glIsEnabled (GLenum cap);
GL_API GLboolean GL_APIENTRY glIsTexture (GLuint texture);
GL_API శూన్య GL_APIENTRY glLightModelx (GLenum pname, GLfixed param);
GL_API శూన్య GL_APIENTRY glLightModelxv (GLenum pname, స్థిరరాశి GLfixed *param);
GL_API శూన్య GL_APIENTRY glLightx (GLenum light, GLenum pname, GLfixed param);
GL_API శూన్య GL_APIENTRY glLightxv (GLenum light, GLenum pname, స్థిరరాశి GLfixed *params);
GL_API శూన్య GL_APIENTRY gl_పంక్తి_Widthx (GLfixed వెడల్పు);
GL_API శూన్య GL_APIENTRY gl_ఎక్కించు_తటస్థం (శూన్య);
GL_API శూన్య GL_APIENTRY gl_ఎక్కించు_Matrixx (స్థిరరాశి GLfixed *m);
GL_API శూన్య GL_APIENTRY glLogicOp (GLenum opcode);
GL_API శూన్య GL_APIENTRY glMaterialx (GLenum face, GLenum pname, GLfixed param);
GL_API శూన్య GL_APIENTRY glMaterialxv (GLenum face, GLenum pname, స్థిరరాశి GLfixed *param);
GL_API శూన్య GL_APIENTRY gl_మాతృక_బహుళకం (GLenum బహుళకం);
GL_API శూన్య GL_APIENTRY glMultMatrixx (స్థిరరాశి GLfixed *m);
GL_API శూన్య GL_APIENTRY glMultiTexCoord4x (GLenum texture, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
GL_API శూన్య GL_APIENTRY glNormal3x (GLfixed nx, GLfixed ny, GLfixed nz);
GL_API శూన్య GL_APIENTRY gl_సాధారణ_సూచిక (GLenum type, GLsizei stride, స్థిరరాశి శూన్య *సూచిక_2);
GL_API శూన్య GL_APIENTRY glOrthox (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
GL_API శూన్య GL_APIENTRY glPixelStorei (GLenum pname, GLint param);
GL_API శూన్య GL_APIENTRY gl_బిందువు_Parameterx (GLenum pname, GLfixed param);
GL_API శూన్య GL_APIENTRY gl_బిందువు_Parameterxv (GLenum pname, స్థిరరాశి GLfixed *params);
GL_API శూన్య GL_APIENTRY gl_బిందువు_Sizex (GLfixed కొలత);
GL_API శూన్య GL_APIENTRY glPolygonOffsetx (GLfixed గుణకం, GLfixed units);
GL_API శూన్య GL_APIENTRY gl_తీయి_మాతృక (శూన్య);
GL_API శూన్య GL_APIENTRY gl_నెట్టు_మాతృక (శూన్య);
GL_API శూన్య GL_APIENTRY glReadPixels (GLint x, GLint y, GLsizei వెడల్పు, GLsizei ఎత్తు, GLenum format, GLenum type, శూన్య *pixels);
GL_API శూన్య GL_APIENTRY glRotatex (GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
GL_API శూన్య GL_APIENTRY glSampleCoverage (GLfloat విలువ, GLboolean invert);
GL_API శూన్య GL_APIENTRY glSampleCoveragex (GLclampx విలువ, GLboolean invert);
GL_API శూన్య GL_APIENTRY glScalex (GLfixed x, GLfixed y, GLfixed z);
GL_API శూన్య GL_APIENTRY glScissor (GLint x, GLint y, GLsizei వెడల్పు, GLsizei ఎత్తు);
GL_API శూన్య GL_APIENTRY glShadeModel (GLenum బహుళకం);
GL_API శూన్య GL_APIENTRY glStencilFunc (GLenum func, GLint ref, GLuint ముసుగు);
GL_API శూన్య GL_APIENTRY gl_Stencil_ముసుగు (GLuint ముసుగు);
GL_API శూన్య GL_APIENTRY glStencilOp (GLenum fail, GLenum zfail, GLenum zpass);
GL_API శూన్య GL_APIENTRY gl_Tex_Coord_సూచిక (GLint కొలత, GLenum type, GLsizei stride, స్థిరరాశి శూన్య *సూచిక_2);
GL_API శూన్య GL_APIENTRY glTexEnvi (GLenum లక్ష్యం, GLenum pname, GLint param);
GL_API శూన్య GL_APIENTRY glTexEnvx (GLenum లక్ష్యం, GLenum pname, GLfixed param);
GL_API శూన్య GL_APIENTRY glTexEnviv (GLenum లక్ష్యం, GLenum pname, స్థిరరాశి GLint *params);
GL_API శూన్య GL_APIENTRY glTexEnvxv (GLenum లక్ష్యం, GLenum pname, స్థిరరాశి GLfixed *params);
GL_API శూన్య GL_APIENTRY glTexImage2D (GLenum లక్ష్యం, GLint level, GLint internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు, GLint border, GLenum format, GLenum type, స్థిరరాశి శూన్య *pixels);
GL_API శూన్య GL_APIENTRY glTexParameteri (GLenum లక్ష్యం, GLenum pname, GLint param);
GL_API శూన్య GL_APIENTRY glTexParameterx (GLenum లక్ష్యం, GLenum pname, GLfixed param);
GL_API శూన్య GL_APIENTRY glTexParameteriv (GLenum లక్ష్యం, GLenum pname, స్థిరరాశి GLint *params);
GL_API శూన్య GL_APIENTRY glTexParameterxv (GLenum లక్ష్యం, GLenum pname, స్థిరరాశి GLfixed *params);
GL_API శూన్య GL_APIENTRY glTexSubImage2D (GLenum లక్ష్యం, GLint level, GLint xoffset, GLint yoffset, GLsizei వెడల్పు, GLsizei ఎత్తు, GLenum format, GLenum type, స్థిరరాశి శూన్య *pixels);
GL_API శూన్య GL_APIENTRY glTranslatex (GLfixed x, GLfixed y, GLfixed z);
GL_API శూన్య GL_APIENTRY gl_శీర్షం_సూచిక (GLint కొలత, GLenum type, GLsizei stride, స్థిరరాశి శూన్య *సూచిక_2);
GL_API శూన్య GL_APIENTRY glViewport (GLint x, GLint y, GLsizei వెడల్పు, GLsizei ఎత్తు);
#అయితే_ముగింపు /* GL_VERSION_ES_CM_1_0 */

#నిర్వచితం_కాకపోతే GL_OES_compressed_paletted_texture
#నిర్వచించు GL_OES_compressed_paletted_texture 1
#నిర్వచించు GL_PALETTE4_RGB8_OES              0x8B90
#నిర్వచించు GL_PALETTE4_RGBA8_OES             0x8B91
#నిర్వచించు GL_PALETTE4_R5_G6_B5_OES          0x8B92
#నిర్వచించు GL_PALETTE4_RGBA4_OES             0x8B93
#నిర్వచించు GL_PALETTE4_RGB5_A1_OES           0x8B94
#నిర్వచించు GL_PALETTE8_RGB8_OES              0x8B95
#నిర్వచించు GL_PALETTE8_RGBA8_OES             0x8B96
#నిర్వచించు GL_PALETTE8_R5_G6_B5_OES          0x8B97
#నిర్వచించు GL_PALETTE8_RGBA4_OES             0x8B98
#నిర్వచించు GL_PALETTE8_RGB5_A1_OES           0x8B99
#అయితే_ముగింపు /* GL_OES_compressed_paletted_texture */

#నిర్వచితం_కాకపోతే GL_OES_బిందువు_కొలత_array
#నిర్వచించు GL_OES_బిందువు_కొలత_array 1
#నిర్వచించు GL_బిందువు_కొలత_ARRAY_OES           0x8B9C
#నిర్వచించు GL_బిందువు_కొలత_ARRAY_TYPE_OES      0x898A
#నిర్వచించు GL_బిందువు_కొలత_ARRAY_STRIDE_OES    0x898B
#నిర్వచించు GL_బిందువు_కొలత_ARRAY_సూచిక_OES   0x898C
#నిర్వచించు GL_బిందువు_కొలత_ARRAY_బఫరు_BINDING_OES 0x8B9F
GL_API శూన్య GL_APIENTRY gl_బిందువు_కొలత_సూచిక_OES (GLenum type, GLsizei stride, స్థిరరాశి శూన్య *సూచిక_2);
#అయితే_ముగింపు /* GL_OES_point_size_array */

#నిర్వచితం_కాకపోతే GL_OES_బిందువు_sprite
#నిర్వచించు GL_OES_బిందువు_sprite 1
#నిర్వచించు GL_బిందువు_SPRITE_OES               0x8861
#నిర్వచించు GL_COORD_REPLACE_OES              0x8862
#అయితే_ముగింపు /* GL_OES_point_sprite */

#నిర్వచితం_కాకపోతే GL_OES_read_format
#నిర్వచించు GL_OES_read_format 1
#నిర్వచించు GL_IMPLEMENTATION_COLOR_READ_TYPE_OES 0x8B9A
#నిర్వచించు GL_IMPLEMENTATION_COLOR_READ_FORMAT_OES 0x8B9B
#అయితే_ముగింపు /* GL_OES_read_format */

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు
