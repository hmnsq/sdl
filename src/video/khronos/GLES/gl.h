#यदि_अपरिभाषितम् __gles1_gl_h_
#परिभाषय __gles1_gl_h_ 1

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

#अन्तर्भाव <GLES/glplatform.h>

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

#यदि_अपरिभाषितम् GL_संस्करणम्_ES_CM_1_0
#परिभाषय GL_संस्करणम्_ES_CM_1_0 1
#अन्तर्भाव <KHR/khrplatform.h>
प्रकारनिर्देश khronos_int8_t GLbyte;
प्रकारनिर्देश khronos_float_t GLclampf;
प्रकारनिर्देश khronos_int16_t GLshort;
प्रकारनिर्देश khronos_uint16_t GLushort;
प्रकारनिर्देश शून्य GLvoid;
प्रकारनिर्देश अचिह्नित पूर्णाङ्क GLenum;
प्रकारनिर्देश khronos_float_t GLfloat;
प्रकारनिर्देश khronos_int32_t GLfixed;
प्रकारनिर्देश अचिह्नित पूर्णाङ्क GLuint;
प्रकारनिर्देश khronos_ssize_t GLsizeiptr;
प्रकारनिर्देश khronos_intptr_t GLintptr;
प्रकारनिर्देश अचिह्नित पूर्णाङ्क GLbitfield;
प्रकारनिर्देश पूर्णाङ्क GLint;
प्रकारनिर्देश khronos_uint8_t GLubyte;
प्रकारनिर्देश अचिह्नित वर्ण GLboolean;
प्रकारनिर्देश पूर्णाङ्क GLsizei;
प्रकारनिर्देश khronos_int32_t GLclampx;
#परिभाषय GL_संस्करणम्_ES_CL_1_0              1
#परिभाषय GL_संस्करणम्_ES_CM_1_1              1
#परिभाषय GL_संस्करणम्_ES_CL_1_1              1
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
#परिभाषय GL_NEVER                          0x0200
#परिभाषय GL_LESS                           0x0201
#परिभाषय GL_EQUAL                          0x0202
#परिभाषय GL_LEQUAL                         0x0203
#परिभाषय GL_GREATER                        0x0204
#परिभाषय GL_NOTEQUAL                       0x0205
#परिभाषय GL_GEQUAL                         0x0206
#परिभाषय GL_ALWAYS                         0x0207
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
#परिभाषय GL_CLIP_PLANE0                    0x3000
#परिभाषय GL_CLIP_PLANE1                    0x3001
#परिभाषय GL_CLIP_PLANE2                    0x3002
#परिभाषय GL_CLIP_PLANE3                    0x3003
#परिभाषय GL_CLIP_PLANE4                    0x3004
#परिभाषय GL_CLIP_PLANE5                    0x3005
#परिभाषय GL_FRONT                          0x0404
#परिभाषय GL_पृष्ठभागः                           0x0405
#परिभाषय GL_FRONT_AND_पृष्ठभागः                 0x0408
#परिभाषय GL_FOG                            0x0B60
#परिभाषय GL_LIGHTING                       0x0B50
#परिभाषय GL_TEXTURE_2D                     0x0DE1
#परिभाषय GL_CULL_FACE                      0x0B44
#परिभाषय GL_ALPHA_TEST                     0x0BC0
#परिभाषय GL_BLEND                          0x0BE2
#परिभाषय GL_COLOR_LOGIC_OP                 0x0BF2
#परिभाषय GL_DITHER                         0x0BD0
#परिभाषय GL_STENCIL_TEST                   0x0B90
#परिभाषय GL_गभीरता_TEST                     0x0B71
#परिभाषय GL_POINT_SMOOTH                   0x0B10
#परिभाषय GL_पङ्क्तिः_SMOOTH                    0x0B20
#परिभाषय GL_SCISSOR_TEST                   0x0C11
#परिभाषय GL_COLOR_MATERIAL                 0x0B57
#परिभाषय GL_NORMALIZE                      0x0BA1
#परिभाषय GL_RESCALE_प्रसामान्यम्                 0x803A
#परिभाषय GL_VERTEX_ARRAY                   0x8074
#परिभाषय GL_प्रसामान्यम्_ARRAY                   0x8075
#परिभाषय GL_COLOR_ARRAY                    0x8076
#परिभाषय GL_TEXTURE_COORD_ARRAY            0x8078
#परिभाषय GL_MULTISAMPLE                    0x809D
#परिभाषय GL_SAMPLE_ALPHA_गन्तव्यम्_COVERAGE       0x809E
#परिभाषय GL_SAMPLE_ALPHA_गन्तव्यम्_ONE            0x809F
#परिभाषय GL_SAMPLE_COVERAGE                0x80A0
#परिभाषय GL_NO_ERROR                       0
#परिभाषय GL_INVALID_ENUM                   0x0500
#परिभाषय GL_INVALID_मानम्                  0x0501
#परिभाषय GL_INVALID_OPERATION              0x0502
#परिभाषय GL_राशिः_अतिप्रवाहः                 0x0503
#परिभाषय GL_राशिः_UNDERFLOW                0x0504
#परिभाषय GL_बहिर्गमनम्_सम्बन्धि_स्मृतिः                  0x0505
#परिभाषय GL_EXP                            0x0800
#परिभाषय GL_EXP2                           0x0801
#परिभाषय GL_FOG_DENSITY                    0x0B62
#परिभाषय GL_FOG_START                      0x0B63
#परिभाषय GL_FOG_अन्तः                        0x0B64
#परिभाषय GL_FOG_बहुलकम्                       0x0B65
#परिभाषय GL_FOG_COLOR                      0x0B66
#परिभाषय GL_CW                             0x0900
#परिभाषय GL_CCW                            0x0901
#परिभाषय GL_CURRENT_COLOR                  0x0B00
#परिभाषय GL_CURRENT_प्रसामान्यम्                 0x0B02
#परिभाषय GL_CURRENT_TEXTURE_COORDS         0x0B03
#परिभाषय GL_POINT_आकार                     0x0B11
#परिभाषय GL_POINT_आकार_MIN                 0x8126
#परिभाषय GL_POINT_आकार_MAX                 0x8127
#परिभाषय GL_POINT_FADE_देहली_आकार      0x8128
#परिभाषय GL_POINT_DISTANCE_ATTENUATION     0x8129
#परिभाषय GL_SMOOTH_POINT_आकार_RANGE        0x0B12
#परिभाषय GL_पङ्क्तिः_विस्तारः                     0x0B21
#परिभाषय GL_SMOOTH_पङ्क्तिः_विस्तारः_RANGE        0x0B22
#परिभाषय GL_ALIASED_POINT_आकार_RANGE       0x846D
#परिभाषय GL_ALIASED_पङ्क्तिः_विस्तारः_RANGE       0x846E
#परिभाषय GL_CULL_FACE_बहुलकम्                 0x0B45
#परिभाषय GL_FRONT_FACE                     0x0B46
#परिभाषय GL_SHADE_MODEL                    0x0B54
#परिभाषय GL_गभीरता_RANGE                    0x0B70
#परिभाषय GL_गभीरता_WRITEMASK                0x0B72
#परिभाषय GL_गभीरता_CLEAR_मानम्              0x0B73
#परिभाषय GL_गभीरता_FUNC                     0x0B74
#परिभाषय GL_STENCIL_CLEAR_मानम्            0x0B91
#परिभाषय GL_STENCIL_FUNC                   0x0B92
#परिभाषय GL_STENCIL_मानम्_आवरणम्             0x0B93
#परिभाषय GL_STENCIL_FAIL                   0x0B94
#परिभाषय GL_STENCIL_PASS_गभीरता_FAIL        0x0B95
#परिभाषय GL_STENCIL_PASS_गभीरता_PASS        0x0B96
#परिभाषय GL_STENCIL_REF                    0x0B97
#परिभाषय GL_STENCIL_WRITEMASK              0x0B98
#परिभाषय GL_MATRIX_बहुलकम्                    0x0BA0
#परिभाषय GL_VIEWPORT                       0x0BA2
#परिभाषय GL_MODELVIEW_राशिः_गभीरता          0x0BA3
#परिभाषय GL_PROJECTION_राशिः_गभीरता         0x0BA4
#परिभाषय GL_TEXTURE_राशिः_गभीरता            0x0BA5
#परिभाषय GL_MODELVIEW_MATRIX               0x0BA6
#परिभाषय GL_PROJECTION_MATRIX              0x0BA7
#परिभाषय GL_TEXTURE_MATRIX                 0x0BA8
#परिभाषय GL_ALPHA_TEST_FUNC                0x0BC1
#परिभाषय GL_ALPHA_TEST_REF                 0x0BC2
#परिभाषय GL_BLEND_DST                      0x0BE0
#परिभाषय GL_BLEND_SRC                      0x0BE1
#परिभाषय GL_LOGIC_OP_बहुलकम्                  0x0BF0
#परिभाषय GL_SCISSOR_BOX                    0x0C10
#परिभाषय GL_COLOR_CLEAR_मानम्              0x0C22
#परिभाषय GL_COLOR_WRITEMASK                0x0C23
#परिभाषय GL_MAX_LIGHTS                     0x0D31
#परिभाषय GL_MAX_CLIP_PLANES                0x0D32
#परिभाषय GL_MAX_TEXTURE_आकार               0x0D33
#परिभाषय GL_MAX_MODELVIEW_राशिः_गभीरता      0x0D36
#परिभाषय GL_MAX_PROJECTION_राशिः_गभीरता     0x0D38
#परिभाषय GL_MAX_TEXTURE_राशिः_गभीरता        0x0D39
#परिभाषय GL_MAX_VIEWPORT_DIMS              0x0D3A
#परिभाषय GL_MAX_TEXTURE_UNITS              0x84E2
#परिभाषय GL_SUBPIXEL_द्वयङ्काः                  0x0D50
#परिभाषय GL_RED_द्वयङ्काः                       0x0D52
#परिभाषय GL_GREEN_द्वयङ्काः                     0x0D53
#परिभाषय GL_BLUE_द्वयङ्काः                      0x0D54
#परिभाषय GL_ALPHA_द्वयङ्काः                     0x0D55
#परिभाषय GL_गभीरता_द्वयङ्काः                     0x0D56
#परिभाषय GL_STENCIL_द्वयङ्काः                   0x0D57
#परिभाषय GL_POLYGON_विस्थापनम्_UNITS           0x2A00
#परिभाषय GL_POLYGON_विस्थापनम्_FILL            0x8037
#परिभाषय GL_POLYGON_विस्थापनम्_गुणकः          0x8038
#परिभाषय GL_TEXTURE_BINDING_2D             0x8069
#परिभाषय GL_VERTEX_ARRAY_आकार              0x807A
#परिभाषय GL_VERTEX_ARRAY_TYPE              0x807B
#परिभाषय GL_VERTEX_ARRAY_STRIDE            0x807C
#परिभाषय GL_प्रसामान्यम्_ARRAY_TYPE              0x807E
#परिभाषय GL_प्रसामान्यम्_ARRAY_STRIDE            0x807F
#परिभाषय GL_COLOR_ARRAY_आकार               0x8081
#परिभाषय GL_COLOR_ARRAY_TYPE               0x8082
#परिभाषय GL_COLOR_ARRAY_STRIDE             0x8083
#परिभाषय GL_TEXTURE_COORD_ARRAY_आकार       0x8088
#परिभाषय GL_TEXTURE_COORD_ARRAY_TYPE       0x8089
#परिभाषय GL_TEXTURE_COORD_ARRAY_STRIDE     0x808A
#परिभाषय GL_VERTEX_ARRAY_POINTER           0x808E
#परिभाषय GL_प्रसामान्यम्_ARRAY_POINTER           0x808F
#परिभाषय GL_COLOR_ARRAY_POINTER            0x8090
#परिभाषय GL_TEXTURE_COORD_ARRAY_POINTER    0x8092
#परिभाषय GL_SAMPLE_BUFFERS                 0x80A8
#परिभाषय GL_SAMPLES                        0x80A9
#परिभाषय GL_SAMPLE_COVERAGE_मानम्          0x80AA
#परिभाषय GL_SAMPLE_COVERAGE_INVERT         0x80AB
#परिभाषय GL_अङ्कः_COMPRESSED_TEXTURE_FORMATS 0x86A2
#परिभाषय GL_COMPRESSED_TEXTURE_FORMATS     0x86A3
#परिभाषय GL_DONT_CARE                      0x1100
#परिभाषय GL_FASTEST                        0x1101
#परिभाषय GL_NICEST                         0x1102
#परिभाषय GL_PERSPECTIVE_CORRECTION_HINT    0x0C50
#परिभाषय GL_POINT_SMOOTH_HINT              0x0C51
#परिभाषय GL_पङ्क्तिः_SMOOTH_HINT               0x0C52
#परिभाषय GL_FOG_HINT                       0x0C54
#परिभाषय GL_GENERATE_MIPMAP_HINT           0x8192
#परिभाषय GL_LIGHT_MODEL_AMBIENT            0x0B53
#परिभाषय GL_LIGHT_MODEL_TWO_SIDE           0x0B52
#परिभाषय GL_AMBIENT                        0x1200
#परिभाषय GL_DIFFUSE                        0x1201
#परिभाषय GL_SPECULAR                       0x1202
#परिभाषय GL_POSITION                       0x1203
#परिभाषय GL_SPOT_DIRECTION                 0x1204
#परिभाषय GL_SPOT_EXPONENT                  0x1205
#परिभाषय GL_SPOT_CUTOFF                    0x1206
#परिभाषय GL_CONSTANT_ATTENUATION           0x1207
#परिभाषय GL_रैखिकम्_ATTENUATION             0x1208
#परिभाषय GL_QUADRATIC_ATTENUATION          0x1209
#परिभाषय GL_BYTE                           0x1400
#परिभाषय GL_UNSIGNED_BYTE                  0x1401
#परिभाषय GL_SHORT                          0x1402
#परिभाषय GL_UNSIGNED_SHORT                 0x1403
#परिभाषय GL_FLOAT                          0x1406
#परिभाषय GL_FIXED                          0x140C
#परिभाषय GL_CLEAR                          0x1500
#परिभाषय GL_AND                            0x1501
#परिभाषय GL_AND_REVERSE                    0x1502
#परिभाषय GL_COPY                           0x1503
#परिभाषय GL_AND_INVERTED                   0x1504
#परिभाषय GL_NOOP                           0x1505
#परिभाषय GL_XOR                            0x1506
#परिभाषय GL_OR                             0x1507
#परिभाषय GL_NOR                            0x1508
#परिभाषय GL_EQUIV                          0x1509
#परिभाषय GL_INVERT                         0x150A
#परिभाषय GL_OR_REVERSE                     0x150B
#परिभाषय GL_COPY_INVERTED                  0x150C
#परिभाषय GL_OR_INVERTED                    0x150D
#परिभाषय GL_NAND                           0x150E
#परिभाषय GL_समुच्चयः                            0x150F
#परिभाषय GL_EMISSION                       0x1600
#परिभाषय GL_SHININESS                      0x1601
#परिभाषय GL_AMBIENT_AND_DIFFUSE            0x1602
#परिभाषय GL_MODELVIEW                      0x1700
#परिभाषय GL_PROJECTION                     0x1701
#परिभाषय GL_TEXTURE                        0x1702
#परिभाषय GL_ALPHA                          0x1906
#परिभाषय GL_RGB                            0x1907
#परिभाषय GL_RGBA                           0x1908
#परिभाषय GL_LUMINANCE                      0x1909
#परिभाषय GL_LUMINANCE_ALPHA                0x190A
#परिभाषय GL_UNPACK_ALIGNMENT               0x0CF5
#परिभाषय GL_PACK_ALIGNMENT                 0x0D05
#परिभाषय GL_UNSIGNED_SHORT_4_4_4_4         0x8033
#परिभाषय GL_UNSIGNED_SHORT_5_5_5_1         0x8034
#परिभाषय GL_UNSIGNED_SHORT_5_6_5           0x8363
#परिभाषय GL_FLAT                           0x1D00
#परिभाषय GL_SMOOTH                         0x1D01
#परिभाषय GL_KEEP                           0x1E00
#परिभाषय GL_REPLACE                        0x1E01
#परिभाषय GL_INCR                           0x1E02
#परिभाषय GL_DECR                           0x1E03
#परिभाषय GL_VENDOR                         0x1F00
#परिभाषय GL_RENDERER                       0x1F01
#परिभाषय GL_संस्करणम्                        0x1F02
#परिभाषय GL_EXTENSIONS                     0x1F03
#परिभाषय GL_MODULATE                       0x2100
#परिभाषय GL_DECAL                          0x2101
#परिभाषय GL_सङ्कलय                            0x0104
#परिभाषय GL_TEXTURE_ENV_बहुलकम्               0x2200
#परिभाषय GL_TEXTURE_ENV_COLOR              0x2201
#परिभाषय GL_TEXTURE_ENV                    0x2300
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
#परिभाषय GL_GENERATE_MIPMAP                0x8191
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
#परिभाषय GL_CLIENT_सक्रिय_TEXTURE          0x84E1
#परिभाषय GL_REPEAT                         0x2901
#परिभाषय GL_CLAMP_गन्तव्यम्_EDGE                  0x812F
#परिभाषय GL_LIGHT0                         0x4000
#परिभाषय GL_LIGHT1                         0x4001
#परिभाषय GL_LIGHT2                         0x4002
#परिभाषय GL_LIGHT3                         0x4003
#परिभाषय GL_LIGHT4                         0x4004
#परिभाषय GL_LIGHT5                         0x4005
#परिभाषय GL_LIGHT6                         0x4006
#परिभाषय GL_LIGHT7                         0x4007
#परिभाषय GL_ARRAY_बफर                   0x8892
#परिभाषय GL_ELEMENT_ARRAY_बफर           0x8893
#परिभाषय GL_ARRAY_बफर_BINDING           0x8894
#परिभाषय GL_ELEMENT_ARRAY_बफर_BINDING   0x8895
#परिभाषय GL_VERTEX_ARRAY_बफर_BINDING    0x8896
#परिभाषय GL_प्रसामान्यम्_ARRAY_बफर_BINDING    0x8897
#परिभाषय GL_COLOR_ARRAY_बफर_BINDING     0x8898
#परिभाषय GL_TEXTURE_COORD_ARRAY_बफर_BINDING 0x889A
#परिभाषय GL_STATIC_DRAW                    0x88E4
#परिभाषय GL_DYNAMIC_DRAW                   0x88E8
#परिभाषय GL_बफर_आकार                    0x8764
#परिभाषय GL_बफर_USAGE                   0x8765
#परिभाषय GL_व्यवकलय                       0x84E7
#परिभाषय GL_COMBINE                        0x8570
#परिभाषय GL_COMBINE_RGB                    0x8571
#परिभाषय GL_COMBINE_ALPHA                  0x8572
#परिभाषय GL_RGB_SCALE                      0x8573
#परिभाषय GL_सङ्कलय_SIGNED                     0x8574
#परिभाषय GL_INTERPOLATE                    0x8575
#परिभाषय GL_CONSTANT                       0x8576
#परिभाषय GL_PRIMARY_COLOR                  0x8577
#परिभाषय GL_PREVIOUS                       0x8578
#परिभाषय GL_OPERAND0_RGB                   0x8590
#परिभाषय GL_OPERAND1_RGB                   0x8591
#परिभाषय GL_OPERAND2_RGB                   0x8592
#परिभाषय GL_OPERAND0_ALPHA                 0x8598
#परिभाषय GL_OPERAND1_ALPHA                 0x8599
#परिभाषय GL_OPERAND2_ALPHA                 0x859A
#परिभाषय GL_ALPHA_SCALE                    0x0D1C
#परिभाषय GL_SRC0_RGB                       0x8580
#परिभाषय GL_SRC1_RGB                       0x8581
#परिभाषय GL_SRC2_RGB                       0x8582
#परिभाषय GL_SRC0_ALPHA                     0x8588
#परिभाषय GL_SRC1_ALPHA                     0x8589
#परिभाषय GL_SRC2_ALPHA                     0x858A
#परिभाषय GL_DOT3_RGB                       0x86AE
#परिभाषय GL_DOT3_RGBA                      0x86AF
GL_API शून्य GL_APIENTRY glAlphaFunc (GLenum func, GLfloat ref);
GL_API शून्य GL_APIENTRY glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_API शून्य GL_APIENTRY glClearDepthf (GLfloat d);
GL_API शून्य GL_APIENTRY glClipPlanef (GLenum p, ध्रुव GLfloat *eqn);
GL_API शून्य GL_APIENTRY glColor4f (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_API शून्य GL_APIENTRY gl_गभीरता_Rangef (GLfloat n, GLfloat f);
GL_API शून्य GL_APIENTRY glFogf (GLenum pname, GLfloat param);
GL_API शून्य GL_APIENTRY glFogfv (GLenum pname, ध्रुव GLfloat *params);
GL_API शून्य GL_APIENTRY glFrustumf (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
GL_API शून्य GL_APIENTRY glGetClipPlanef (GLenum plane, GLfloat *equation);
GL_API शून्य GL_APIENTRY glGetFloatv (GLenum pname, GLfloat *दत्त);
GL_API शून्य GL_APIENTRY glGetLightfv (GLenum light, GLenum pname, GLfloat *params);
GL_API शून्य GL_APIENTRY glGetMaterialfv (GLenum face, GLenum pname, GLfloat *params);
GL_API शून्य GL_APIENTRY glGetTexEnvfv (GLenum target, GLenum pname, GLfloat *params);
GL_API शून्य GL_APIENTRY glGetTexParameterfv (GLenum target, GLenum pname, GLfloat *params);
GL_API शून्य GL_APIENTRY glLightModelf (GLenum pname, GLfloat param);
GL_API शून्य GL_APIENTRY glLightModelfv (GLenum pname, ध्रुव GLfloat *params);
GL_API शून्य GL_APIENTRY glLightf (GLenum light, GLenum pname, GLfloat param);
GL_API शून्य GL_APIENTRY glLightfv (GLenum light, GLenum pname, ध्रुव GLfloat *params);
GL_API शून्य GL_APIENTRY gl_पङ्क्तिः_विस्तारः (GLfloat विस्तारः);
GL_API शून्य GL_APIENTRY gl_आरोपय_Matrixf (ध्रुव GLfloat *m);
GL_API शून्य GL_APIENTRY glMaterialf (GLenum face, GLenum pname, GLfloat param);
GL_API शून्य GL_APIENTRY glMaterialfv (GLenum face, GLenum pname, ध्रुव GLfloat *params);
GL_API शून्य GL_APIENTRY glMultMatrixf (ध्रुव GLfloat *m);
GL_API शून्य GL_APIENTRY glMultiTexCoord4f (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
GL_API शून्य GL_APIENTRY glNormal3f (GLfloat nx, GLfloat ny, GLfloat nz);
GL_API शून्य GL_APIENTRY glOrthof (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
GL_API शून्य GL_APIENTRY glPointParameterf (GLenum pname, GLfloat param);
GL_API शून्य GL_APIENTRY glPointParameterfv (GLenum pname, ध्रुव GLfloat *params);
GL_API शून्य GL_APIENTRY gl_Point_आकार (GLfloat आकार);
GL_API शून्य GL_APIENTRY gl_Polygon_विस्थापनम् (GLfloat गुणकः, GLfloat units);
GL_API शून्य GL_APIENTRY glRotatef (GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
GL_API शून्य GL_APIENTRY glScalef (GLfloat x, GLfloat y, GLfloat z);
GL_API शून्य GL_APIENTRY glTexEnvf (GLenum target, GLenum pname, GLfloat param);
GL_API शून्य GL_APIENTRY glTexEnvfv (GLenum target, GLenum pname, ध्रुव GLfloat *params);
GL_API शून्य GL_APIENTRY glTexParameterf (GLenum target, GLenum pname, GLfloat param);
GL_API शून्य GL_APIENTRY glTexParameterfv (GLenum target, GLenum pname, ध्रुव GLfloat *params);
GL_API शून्य GL_APIENTRY glTranslatef (GLfloat x, GLfloat y, GLfloat z);
GL_API शून्य GL_APIENTRY gl_सक्रिय_Texture (GLenum texture);
GL_API शून्य GL_APIENTRY glAlphaFuncx (GLenum func, GLfixed ref);
GL_API शून्य GL_APIENTRY gl_Bind_बफर (GLenum target, GLuint बफर_2);
GL_API शून्य GL_APIENTRY glBindTexture (GLenum target, GLuint texture);
GL_API शून्य GL_APIENTRY glBlendFunc (GLenum sfactor, GLenum dfactor);
GL_API शून्य GL_APIENTRY gl_बफर_दत्त (GLenum target, GLsizeiptr आकार, ध्रुव शून्य *दत्त, GLenum usage);
GL_API शून्य GL_APIENTRY gl_बफर_Sub_दत्त (GLenum target, GLintptr विस्थापनम्_2, GLsizeiptr आकार, ध्रुव शून्य *दत्त);
GL_API शून्य GL_APIENTRY glClear (GLbitfield आवरणम्);
GL_API शून्य GL_APIENTRY glClearColorx (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GL_API शून्य GL_APIENTRY glClearDepthx (GLfixed गभीरता_2);
GL_API शून्य GL_APIENTRY glClearStencil (GLint s);
GL_API शून्य GL_APIENTRY gl_Client_सक्रिय_Texture (GLenum texture);
GL_API शून्य GL_APIENTRY glClipPlanex (GLenum plane, ध्रुव GLfixed *equation);
GL_API शून्य GL_APIENTRY glColor4ub (GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
GL_API शून्य GL_APIENTRY glColor4x (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GL_API शून्य GL_APIENTRY gl_Color_आवरणम् (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
GL_API शून्य GL_APIENTRY glColorPointer (GLint आकार, GLenum type, GLsizei stride, ध्रुव शून्य *pointer);
GL_API शून्य GL_APIENTRY glCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei विस्तारः, GLsizei height, GLint border, GLsizei image_आकार, ध्रुव शून्य *दत्त);
GL_API शून्य GL_APIENTRY glCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei विस्तारः, GLsizei height, GLenum format, GLsizei image_आकार, ध्रुव शून्य *दत्त);
GL_API शून्य GL_APIENTRY glCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei विस्तारः, GLsizei height, GLint border);
GL_API शून्य GL_APIENTRY glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei विस्तारः, GLsizei height);
GL_API शून्य GL_APIENTRY glCullFace (GLenum बहुलकम्);
GL_API शून्य GL_APIENTRY glDeleteBuffers (GLsizei n, ध्रुव GLuint *buffers);
GL_API शून्य GL_APIENTRY glDeleteTextures (GLsizei n, ध्रुव GLuint *textures);
GL_API शून्य GL_APIENTRY gl_गभीरता_Func (GLenum func);
GL_API शून्य GL_APIENTRY gl_गभीरता_आवरणम् (GLboolean flag);
GL_API शून्य GL_APIENTRY gl_गभीरता_Rangex (GLfixed n, GLfixed f);
GL_API शून्य GL_APIENTRY glDisable (GLenum cap);
GL_API शून्य GL_APIENTRY glDisableClientState (GLenum array);
GL_API शून्य GL_APIENTRY glDrawArrays (GLenum बहुलकम्, GLint first, GLsizei गणनम्);
GL_API शून्य GL_APIENTRY glDrawElements (GLenum बहुलकम्, GLsizei गणनम्, GLenum type, ध्रुव शून्य *indices);
GL_API शून्य GL_APIENTRY glEnable (GLenum cap);
GL_API शून्य GL_APIENTRY glEnableClientState (GLenum array);
GL_API शून्य GL_APIENTRY glFinish (शून्य);
GL_API शून्य GL_APIENTRY glFlush (शून्य);
GL_API शून्य GL_APIENTRY glFogx (GLenum pname, GLfixed param);
GL_API शून्य GL_APIENTRY glFogxv (GLenum pname, ध्रुव GLfixed *param);
GL_API शून्य GL_APIENTRY glFrontFace (GLenum बहुलकम्);
GL_API शून्य GL_APIENTRY glFrustumx (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
GL_API शून्य GL_APIENTRY glGetBooleanv (GLenum pname, GLboolean *दत्त);
GL_API शून्य GL_APIENTRY gl_Get_बफर_Parameteriv (GLenum target, GLenum pname, GLint *params);
GL_API शून्य GL_APIENTRY glGetClipPlanex (GLenum plane, GLfixed *equation);
GL_API शून्य GL_APIENTRY glGenBuffers (GLsizei n, GLuint *buffers);
GL_API शून्य GL_APIENTRY glGenTextures (GLsizei n, GLuint *textures);
GL_API GLenum GL_APIENTRY glGetError (शून्य);
GL_API शून्य GL_APIENTRY glGetFixedv (GLenum pname, GLfixed *दत्त);
GL_API शून्य GL_APIENTRY glGetIntegerv (GLenum pname, GLint *दत्त);
GL_API शून्य GL_APIENTRY glGetLightxv (GLenum light, GLenum pname, GLfixed *params);
GL_API शून्य GL_APIENTRY glGetMaterialxv (GLenum face, GLenum pname, GLfixed *params);
GL_API शून्य GL_APIENTRY glGetPointerv (GLenum pname, शून्य **params);
GL_API ध्रुव GLubyte *GL_APIENTRY glGetString (GLenum name);
GL_API शून्य GL_APIENTRY glGetTexEnviv (GLenum target, GLenum pname, GLint *params);
GL_API शून्य GL_APIENTRY glGetTexEnvxv (GLenum target, GLenum pname, GLfixed *params);
GL_API शून्य GL_APIENTRY glGetTexParameteriv (GLenum target, GLenum pname, GLint *params);
GL_API शून्य GL_APIENTRY glGetTexParameterxv (GLenum target, GLenum pname, GLfixed *params);
GL_API शून्य GL_APIENTRY glHint (GLenum target, GLenum बहुलकम्);
GL_API GLboolean GL_APIENTRY gl_Is_बफर (GLuint बफर_2);
GL_API GLboolean GL_APIENTRY glIsEnabled (GLenum cap);
GL_API GLboolean GL_APIENTRY glIsTexture (GLuint texture);
GL_API शून्य GL_APIENTRY glLightModelx (GLenum pname, GLfixed param);
GL_API शून्य GL_APIENTRY glLightModelxv (GLenum pname, ध्रुव GLfixed *param);
GL_API शून्य GL_APIENTRY glLightx (GLenum light, GLenum pname, GLfixed param);
GL_API शून्य GL_APIENTRY glLightxv (GLenum light, GLenum pname, ध्रुव GLfixed *params);
GL_API शून्य GL_APIENTRY gl_पङ्क्तिः_Widthx (GLfixed विस्तारः);
GL_API शून्य GL_APIENTRY gl_आरोपय_तटस्थः (शून्य);
GL_API शून्य GL_APIENTRY gl_आरोपय_Matrixx (ध्रुव GLfixed *m);
GL_API शून्य GL_APIENTRY glLogicOp (GLenum opcode);
GL_API शून्य GL_APIENTRY glMaterialx (GLenum face, GLenum pname, GLfixed param);
GL_API शून्य GL_APIENTRY glMaterialxv (GLenum face, GLenum pname, ध्रुव GLfixed *param);
GL_API शून्य GL_APIENTRY gl_Matrix_बहुलकम् (GLenum बहुलकम्);
GL_API शून्य GL_APIENTRY glMultMatrixx (ध्रुव GLfixed *m);
GL_API शून्य GL_APIENTRY glMultiTexCoord4x (GLenum texture, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
GL_API शून्य GL_APIENTRY glNormal3x (GLfixed nx, GLfixed ny, GLfixed nz);
GL_API शून्य GL_APIENTRY gl_प्रसामान्यम्_Pointer (GLenum type, GLsizei stride, ध्रुव शून्य *pointer);
GL_API शून्य GL_APIENTRY glOrthox (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
GL_API शून्य GL_APIENTRY glPixelStorei (GLenum pname, GLint param);
GL_API शून्य GL_APIENTRY glPointParameterx (GLenum pname, GLfixed param);
GL_API शून्य GL_APIENTRY glPointParameterxv (GLenum pname, ध्रुव GLfixed *params);
GL_API शून्य GL_APIENTRY glPointSizex (GLfixed आकार);
GL_API शून्य GL_APIENTRY glPolygonOffsetx (GLfixed गुणकः, GLfixed units);
GL_API शून्य GL_APIENTRY gl_निष्कासय_Matrix (शून्य);
GL_API शून्य GL_APIENTRY gl_प्रक्षिप_Matrix (शून्य);
GL_API शून्य GL_APIENTRY glReadPixels (GLint x, GLint y, GLsizei विस्तारः, GLsizei height, GLenum format, GLenum type, शून्य *pixels);
GL_API शून्य GL_APIENTRY glRotatex (GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
GL_API शून्य GL_APIENTRY glSampleCoverage (GLfloat मानम्, GLboolean invert);
GL_API शून्य GL_APIENTRY glSampleCoveragex (GLclampx मानम्, GLboolean invert);
GL_API शून्य GL_APIENTRY glScalex (GLfixed x, GLfixed y, GLfixed z);
GL_API शून्य GL_APIENTRY glScissor (GLint x, GLint y, GLsizei विस्तारः, GLsizei height);
GL_API शून्य GL_APIENTRY glShadeModel (GLenum बहुलकम्);
GL_API शून्य GL_APIENTRY glStencilFunc (GLenum func, GLint ref, GLuint आवरणम्);
GL_API शून्य GL_APIENTRY gl_Stencil_आवरणम् (GLuint आवरणम्);
GL_API शून्य GL_APIENTRY glStencilOp (GLenum fail, GLenum zfail, GLenum zpass);
GL_API शून्य GL_APIENTRY glTexCoordPointer (GLint आकार, GLenum type, GLsizei stride, ध्रुव शून्य *pointer);
GL_API शून्य GL_APIENTRY glTexEnvi (GLenum target, GLenum pname, GLint param);
GL_API शून्य GL_APIENTRY glTexEnvx (GLenum target, GLenum pname, GLfixed param);
GL_API शून्य GL_APIENTRY glTexEnviv (GLenum target, GLenum pname, ध्रुव GLint *params);
GL_API शून्य GL_APIENTRY glTexEnvxv (GLenum target, GLenum pname, ध्रुव GLfixed *params);
GL_API शून्य GL_APIENTRY glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei विस्तारः, GLsizei height, GLint border, GLenum format, GLenum type, ध्रुव शून्य *pixels);
GL_API शून्य GL_APIENTRY glTexParameteri (GLenum target, GLenum pname, GLint param);
GL_API शून्य GL_APIENTRY glTexParameterx (GLenum target, GLenum pname, GLfixed param);
GL_API शून्य GL_APIENTRY glTexParameteriv (GLenum target, GLenum pname, ध्रुव GLint *params);
GL_API शून्य GL_APIENTRY glTexParameterxv (GLenum target, GLenum pname, ध्रुव GLfixed *params);
GL_API शून्य GL_APIENTRY glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei विस्तारः, GLsizei height, GLenum format, GLenum type, ध्रुव शून्य *pixels);
GL_API शून्य GL_APIENTRY glTranslatex (GLfixed x, GLfixed y, GLfixed z);
GL_API शून्य GL_APIENTRY glVertexPointer (GLint आकार, GLenum type, GLsizei stride, ध्रुव शून्य *pointer);
GL_API शून्य GL_APIENTRY glViewport (GLint x, GLint y, GLsizei विस्तारः, GLsizei height);
#यदि_अन्तः /* GL_VERSION_ES_CM_1_0 */

#यदि_अपरिभाषितम् GL_OES_compressed_paletted_texture
#परिभाषय GL_OES_compressed_paletted_texture 1
#परिभाषय GL_PALETTE4_RGB8_OES              0x8B90
#परिभाषय GL_PALETTE4_RGBA8_OES             0x8B91
#परिभाषय GL_PALETTE4_R5_G6_B5_OES          0x8B92
#परिभाषय GL_PALETTE4_RGBA4_OES             0x8B93
#परिभाषय GL_PALETTE4_RGB5_A1_OES           0x8B94
#परिभाषय GL_PALETTE8_RGB8_OES              0x8B95
#परिभाषय GL_PALETTE8_RGBA8_OES             0x8B96
#परिभाषय GL_PALETTE8_R5_G6_B5_OES          0x8B97
#परिभाषय GL_PALETTE8_RGBA4_OES             0x8B98
#परिभाषय GL_PALETTE8_RGB5_A1_OES           0x8B99
#यदि_अन्तः /* GL_OES_compressed_paletted_texture */

#यदि_अपरिभाषितम् GL_OES_point_आकार_array
#परिभाषय GL_OES_point_आकार_array 1
#परिभाषय GL_POINT_आकार_ARRAY_OES           0x8B9C
#परिभाषय GL_POINT_आकार_ARRAY_TYPE_OES      0x898A
#परिभाषय GL_POINT_आकार_ARRAY_STRIDE_OES    0x898B
#परिभाषय GL_POINT_आकार_ARRAY_POINTER_OES   0x898C
#परिभाषय GL_POINT_आकार_ARRAY_बफर_BINDING_OES 0x8B9F
GL_API शून्य GL_APIENTRY gl_Point_आकार_Pointer_OES (GLenum type, GLsizei stride, ध्रुव शून्य *pointer);
#यदि_अन्तः /* GL_OES_point_size_array */

#यदि_अपरिभाषितम् GL_OES_point_sprite
#परिभाषय GL_OES_point_sprite 1
#परिभाषय GL_POINT_SPRITE_OES               0x8861
#परिभाषय GL_COORD_REPLACE_OES              0x8862
#यदि_अन्तः /* GL_OES_point_sprite */

#यदि_अपरिभाषितम् GL_OES_read_format
#परिभाषय GL_OES_read_format 1
#परिभाषय GL_IMPLEMENTATION_COLOR_READ_TYPE_OES 0x8B9A
#परिभाषय GL_IMPLEMENTATION_COLOR_READ_FORMAT_OES 0x8B9B
#यदि_अन्तः /* GL_OES_read_format */

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः
