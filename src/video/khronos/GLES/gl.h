#अगर_अघोषित __gles1_gl_h_
#घोषणा __gles1_gl_h_ 1

#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर

/*
** Copyright 2013-2026 The Khronos Group Inc.
** SPDX-License-Identifier: MIT
**
** This header is generated from the Khronos OpenGL / OpenGL ES XML
** API Registry. The current version of the Registry, generator scripts
** used to make the header, and the header can be found at
**   https://github.com/KhronosGroup/OpenGL-Registry
*/

#समावेश <GLES/glplatform.h>

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

#अगर_अघोषित GL_VERSION_ES_CM_1_0
#घोषणा GL_VERSION_ES_CM_1_0 1
#समावेश <KHR/khrplatform.h>
प्रकार khronos_int8_t GLbyte;
प्रकार khronos_float_t GLclampf;
प्रकार khronos_int16_t GLshort;
प्रकार khronos_uint16_t GLushort;
प्रकार व्योम GLvoid;
प्रकार अचिन्हित पूर्णांक GLenum;
प्रकार khronos_float_t GLfloat;
प्रकार khronos_int32_t GLfixed;
प्रकार अचिन्हित पूर्णांक GLuint;
प्रकार khronos_ssize_t GLsizeiptr;
प्रकार khronos_intptr_t GLintptr;
प्रकार अचिन्हित पूर्णांक GLbitfield;
प्रकार पूर्णांक GLint;
प्रकार khronos_uint8_t GLubyte;
प्रकार अचिन्हित अक्षर GLboolean;
प्रकार पूर्णांक GLsizei;
प्रकार khronos_int32_t GLclampx;
#घोषणा GL_VERSION_ES_CL_1_0              1
#घोषणा GL_VERSION_ES_CM_1_1              1
#घोषणा GL_VERSION_ES_CL_1_1              1
#घोषणा GL_DEPTH_बफर_BIT               0x00000100
#घोषणा GL_STENCIL_बफर_BIT             0x00000400
#घोषणा GL_COLOR_बफर_BIT               0x00004000
#घोषणा GL_FALSE                          0
#घोषणा GL_TRUE                           1
#घोषणा GL_POINTS                         0x0000
#घोषणा GL_पंक्तियाँ                          0x0001
#घोषणा GL_पंक्ति_LOOP                      0x0002
#घोषणा GL_पंक्ति_STRIP                     0x0003
#घोषणा GL_TRIANGLES                      0x0004
#घोषणा GL_TRIANGLE_STRIP                 0x0005
#घोषणा GL_TRIANGLE_FAN                   0x0006
#घोषणा GL_NEVER                          0x0200
#घोषणा GL_LESS                           0x0201
#घोषणा GL_EQUAL                          0x0202
#घोषणा GL_LEQUAL                         0x0203
#घोषणा GL_GREATER                        0x0204
#घोषणा GL_NOTEQUAL                       0x0205
#घोषणा GL_GEQUAL                         0x0206
#घोषणा GL_ALWAYS                         0x0207
#घोषणा GL_ZERO                           0
#घोषणा GL_ONE                            1
#घोषणा GL_SRC_COLOR                      0x0300
#घोषणा GL_ONE_MINUS_SRC_COLOR            0x0301
#घोषणा GL_SRC_ALPHA                      0x0302
#घोषणा GL_ONE_MINUS_SRC_ALPHA            0x0303
#घोषणा GL_DST_ALPHA                      0x0304
#घोषणा GL_ONE_MINUS_DST_ALPHA            0x0305
#घोषणा GL_DST_COLOR                      0x0306
#घोषणा GL_ONE_MINUS_DST_COLOR            0x0307
#घोषणा GL_SRC_ALPHA_SATURATE             0x0308
#घोषणा GL_CLIP_PLANE0                    0x3000
#घोषणा GL_CLIP_PLANE1                    0x3001
#घोषणा GL_CLIP_PLANE2                    0x3002
#घोषणा GL_CLIP_PLANE3                    0x3003
#घोषणा GL_CLIP_PLANE4                    0x3004
#घोषणा GL_CLIP_PLANE5                    0x3005
#घोषणा GL_FRONT                          0x0404
#घोषणा GL_BACK                           0x0405
#घोषणा GL_FRONT_AND_BACK                 0x0408
#घोषणा GL_FOG                            0x0B60
#घोषणा GL_LIGHTING                       0x0B50
#घोषणा GL_TEXTURE_2D                     0x0DE1
#घोषणा GL_CULL_FACE                      0x0B44
#घोषणा GL_ALPHA_TEST                     0x0BC0
#घोषणा GL_BLEND                          0x0BE2
#घोषणा GL_COLOR_LOGIC_OP                 0x0BF2
#घोषणा GL_DITHER                         0x0BD0
#घोषणा GL_STENCIL_TEST                   0x0B90
#घोषणा GL_DEPTH_TEST                     0x0B71
#घोषणा GL_POINT_SMOOTH                   0x0B10
#घोषणा GL_पंक्ति_SMOOTH                    0x0B20
#घोषणा GL_SCISSOR_TEST                   0x0C11
#घोषणा GL_COLOR_MATERIAL                 0x0B57
#घोषणा GL_NORMALIZE                      0x0BA1
#घोषणा GL_RESCALE_NORMAL                 0x803A
#घोषणा GL_VERTEX_ARRAY                   0x8074
#घोषणा GL_NORMAL_ARRAY                   0x8075
#घोषणा GL_COLOR_ARRAY                    0x8076
#घोषणा GL_TEXTURE_COORD_ARRAY            0x8078
#घोषणा GL_MULTISAMPLE                    0x809D
#घोषणा GL_SAMPLE_ALPHA_TO_COVERAGE       0x809E
#घोषणा GL_SAMPLE_ALPHA_TO_ONE            0x809F
#घोषणा GL_SAMPLE_COVERAGE                0x80A0
#घोषणा GL_NO_ERROR                       0
#घोषणा GL_INVALID_ENUM                   0x0500
#घोषणा GL_INVALID_मूल्य                  0x0501
#घोषणा GL_INVALID_OPERATION              0x0502
#घोषणा GL_ढेर_OVERFLOW                 0x0503
#घोषणा GL_ढेर_UNDERFLOW                0x0504
#घोषणा GL_OUT_OF_MEMORY                  0x0505
#घोषणा GL_EXP                            0x0800
#घोषणा GL_EXP2                           0x0801
#घोषणा GL_FOG_DENSITY                    0x0B62
#घोषणा GL_FOG_START                      0x0B63
#घोषणा GL_FOG_END                        0x0B64
#घोषणा GL_FOG_MODE                       0x0B65
#घोषणा GL_FOG_COLOR                      0x0B66
#घोषणा GL_CW                             0x0900
#घोषणा GL_CCW                            0x0901
#घोषणा GL_CURRENT_COLOR                  0x0B00
#घोषणा GL_CURRENT_NORMAL                 0x0B02
#घोषणा GL_CURRENT_TEXTURE_COORDS         0x0B03
#घोषणा GL_POINT_आकार                     0x0B11
#घोषणा GL_POINT_आकार_MIN                 0x8126
#घोषणा GL_POINT_आकार_MAX                 0x8127
#घोषणा GL_POINT_FADE_THRESHOLD_आकार      0x8128
#घोषणा GL_POINT_DISTANCE_ATTENUATION     0x8129
#घोषणा GL_SMOOTH_POINT_आकार_RANGE        0x0B12
#घोषणा GL_पंक्ति_WIDTH                     0x0B21
#घोषणा GL_SMOOTH_पंक्ति_WIDTH_RANGE        0x0B22
#घोषणा GL_ALIASED_POINT_आकार_RANGE       0x846D
#घोषणा GL_ALIASED_पंक्ति_WIDTH_RANGE       0x846E
#घोषणा GL_CULL_FACE_MODE                 0x0B45
#घोषणा GL_FRONT_FACE                     0x0B46
#घोषणा GL_SHADE_MODEL                    0x0B54
#घोषणा GL_DEPTH_RANGE                    0x0B70
#घोषणा GL_DEPTH_WRITEMASK                0x0B72
#घोषणा GL_DEPTH_CLEAR_मूल्य              0x0B73
#घोषणा GL_DEPTH_FUNC                     0x0B74
#घोषणा GL_STENCIL_CLEAR_मूल्य            0x0B91
#घोषणा GL_STENCIL_FUNC                   0x0B92
#घोषणा GL_STENCIL_मूल्य_MASK             0x0B93
#घोषणा GL_STENCIL_FAIL                   0x0B94
#घोषणा GL_STENCIL_PASS_DEPTH_FAIL        0x0B95
#घोषणा GL_STENCIL_PASS_DEPTH_PASS        0x0B96
#घोषणा GL_STENCIL_REF                    0x0B97
#घोषणा GL_STENCIL_WRITEMASK              0x0B98
#घोषणा GL_MATRIX_MODE                    0x0BA0
#घोषणा GL_VIEWPORT                       0x0BA2
#घोषणा GL_MODELVIEW_ढेर_DEPTH          0x0BA3
#घोषणा GL_PROJECTION_ढेर_DEPTH         0x0BA4
#घोषणा GL_TEXTURE_ढेर_DEPTH            0x0BA5
#घोषणा GL_MODELVIEW_MATRIX               0x0BA6
#घोषणा GL_PROJECTION_MATRIX              0x0BA7
#घोषणा GL_TEXTURE_MATRIX                 0x0BA8
#घोषणा GL_ALPHA_TEST_FUNC                0x0BC1
#घोषणा GL_ALPHA_TEST_REF                 0x0BC2
#घोषणा GL_BLEND_DST                      0x0BE0
#घोषणा GL_BLEND_SRC                      0x0BE1
#घोषणा GL_LOGIC_OP_MODE                  0x0BF0
#घोषणा GL_SCISSOR_BOX                    0x0C10
#घोषणा GL_COLOR_CLEAR_मूल्य              0x0C22
#घोषणा GL_COLOR_WRITEMASK                0x0C23
#घोषणा GL_MAX_LIGHTS                     0x0D31
#घोषणा GL_MAX_CLIP_PLANES                0x0D32
#घोषणा GL_MAX_TEXTURE_आकार               0x0D33
#घोषणा GL_MAX_MODELVIEW_ढेर_DEPTH      0x0D36
#घोषणा GL_MAX_PROJECTION_ढेर_DEPTH     0x0D38
#घोषणा GL_MAX_TEXTURE_ढेर_DEPTH        0x0D39
#घोषणा GL_MAX_VIEWPORT_DIMS              0x0D3A
#घोषणा GL_MAX_TEXTURE_UNITS              0x84E2
#घोषणा GL_SUBPIXEL_BITS                  0x0D50
#घोषणा GL_RED_BITS                       0x0D52
#घोषणा GL_GREEN_BITS                     0x0D53
#घोषणा GL_BLUE_BITS                      0x0D54
#घोषणा GL_ALPHA_BITS                     0x0D55
#घोषणा GL_DEPTH_BITS                     0x0D56
#घोषणा GL_STENCIL_BITS                   0x0D57
#घोषणा GL_POLYGON_OFFSET_UNITS           0x2A00
#घोषणा GL_POLYGON_OFFSET_FILL            0x8037
#घोषणा GL_POLYGON_OFFSET_FACTOR          0x8038
#घोषणा GL_TEXTURE_BINDING_2D             0x8069
#घोषणा GL_VERTEX_ARRAY_आकार              0x807A
#घोषणा GL_VERTEX_ARRAY_TYPE              0x807B
#घोषणा GL_VERTEX_ARRAY_STRIDE            0x807C
#घोषणा GL_NORMAL_ARRAY_TYPE              0x807E
#घोषणा GL_NORMAL_ARRAY_STRIDE            0x807F
#घोषणा GL_COLOR_ARRAY_आकार               0x8081
#घोषणा GL_COLOR_ARRAY_TYPE               0x8082
#घोषणा GL_COLOR_ARRAY_STRIDE             0x8083
#घोषणा GL_TEXTURE_COORD_ARRAY_आकार       0x8088
#घोषणा GL_TEXTURE_COORD_ARRAY_TYPE       0x8089
#घोषणा GL_TEXTURE_COORD_ARRAY_STRIDE     0x808A
#घोषणा GL_VERTEX_ARRAY_POINTER           0x808E
#घोषणा GL_NORMAL_ARRAY_POINTER           0x808F
#घोषणा GL_COLOR_ARRAY_POINTER            0x8090
#घोषणा GL_TEXTURE_COORD_ARRAY_POINTER    0x8092
#घोषणा GL_SAMPLE_BUFFERS                 0x80A8
#घोषणा GL_SAMPLES                        0x80A9
#घोषणा GL_SAMPLE_COVERAGE_मूल्य          0x80AA
#घोषणा GL_SAMPLE_COVERAGE_INVERT         0x80AB
#घोषणा GL_अंक_COMPRESSED_TEXTURE_FORMATS 0x86A2
#घोषणा GL_COMPRESSED_TEXTURE_FORMATS     0x86A3
#घोषणा GL_DONT_CARE                      0x1100
#घोषणा GL_FASTEST                        0x1101
#घोषणा GL_NICEST                         0x1102
#घोषणा GL_PERSPECTIVE_CORRECTION_HINT    0x0C50
#घोषणा GL_POINT_SMOOTH_HINT              0x0C51
#घोषणा GL_पंक्ति_SMOOTH_HINT               0x0C52
#घोषणा GL_FOG_HINT                       0x0C54
#घोषणा GL_GENERATE_MIPMAP_HINT           0x8192
#घोषणा GL_LIGHT_MODEL_AMBIENT            0x0B53
#घोषणा GL_LIGHT_MODEL_TWO_SIDE           0x0B52
#घोषणा GL_AMBIENT                        0x1200
#घोषणा GL_DIFFUSE                        0x1201
#घोषणा GL_SPECULAR                       0x1202
#घोषणा GL_POSITION                       0x1203
#घोषणा GL_SPOT_DIRECTION                 0x1204
#घोषणा GL_SPOT_EXPONENT                  0x1205
#घोषणा GL_SPOT_CUTOFF                    0x1206
#घोषणा GL_CONSTANT_ATTENUATION           0x1207
#घोषणा GL_LINEAR_ATTENUATION             0x1208
#घोषणा GL_QUADRATIC_ATTENUATION          0x1209
#घोषणा GL_BYTE                           0x1400
#घोषणा GL_UNSIGNED_BYTE                  0x1401
#घोषणा GL_SHORT                          0x1402
#घोषणा GL_UNSIGNED_SHORT                 0x1403
#घोषणा GL_FLOAT                          0x1406
#घोषणा GL_FIXED                          0x140C
#घोषणा GL_CLEAR                          0x1500
#घोषणा GL_AND                            0x1501
#घोषणा GL_AND_REVERSE                    0x1502
#घोषणा GL_COPY                           0x1503
#घोषणा GL_AND_INVERTED                   0x1504
#घोषणा GL_NOOP                           0x1505
#घोषणा GL_XOR                            0x1506
#घोषणा GL_OR                             0x1507
#घोषणा GL_NOR                            0x1508
#घोषणा GL_EQUIV                          0x1509
#घोषणा GL_INVERT                         0x150A
#घोषणा GL_OR_REVERSE                     0x150B
#घोषणा GL_COPY_INVERTED                  0x150C
#घोषणा GL_OR_INVERTED                    0x150D
#घोषणा GL_NAND                           0x150E
#घोषणा GL_SET                            0x150F
#घोषणा GL_EMISSION                       0x1600
#घोषणा GL_SHININESS                      0x1601
#घोषणा GL_AMBIENT_AND_DIFFUSE            0x1602
#घोषणा GL_MODELVIEW                      0x1700
#घोषणा GL_PROJECTION                     0x1701
#घोषणा GL_TEXTURE                        0x1702
#घोषणा GL_ALPHA                          0x1906
#घोषणा GL_RGB                            0x1907
#घोषणा GL_RGBA                           0x1908
#घोषणा GL_LUMINANCE                      0x1909
#घोषणा GL_LUMINANCE_ALPHA                0x190A
#घोषणा GL_UNPACK_ALIGNMENT               0x0CF5
#घोषणा GL_PACK_ALIGNMENT                 0x0D05
#घोषणा GL_UNSIGNED_SHORT_4_4_4_4         0x8033
#घोषणा GL_UNSIGNED_SHORT_5_5_5_1         0x8034
#घोषणा GL_UNSIGNED_SHORT_5_6_5           0x8363
#घोषणा GL_FLAT                           0x1D00
#घोषणा GL_SMOOTH                         0x1D01
#घोषणा GL_KEEP                           0x1E00
#घोषणा GL_REPLACE                        0x1E01
#घोषणा GL_INCR                           0x1E02
#घोषणा GL_DECR                           0x1E03
#घोषणा GL_VENDOR                         0x1F00
#घोषणा GL_RENDERER                       0x1F01
#घोषणा GL_VERSION                        0x1F02
#घोषणा GL_EXTENSIONS                     0x1F03
#घोषणा GL_MODULATE                       0x2100
#घोषणा GL_DECAL                          0x2101
#घोषणा GL_ADD                            0x0104
#घोषणा GL_TEXTURE_ENV_MODE               0x2200
#घोषणा GL_TEXTURE_ENV_COLOR              0x2201
#घोषणा GL_TEXTURE_ENV                    0x2300
#घोषणा GL_NEAREST                        0x2600
#घोषणा GL_LINEAR                         0x2601
#घोषणा GL_NEAREST_MIPMAP_NEAREST         0x2700
#घोषणा GL_LINEAR_MIPMAP_NEAREST          0x2701
#घोषणा GL_NEAREST_MIPMAP_LINEAR          0x2702
#घोषणा GL_LINEAR_MIPMAP_LINEAR           0x2703
#घोषणा GL_TEXTURE_MAG_FILTER             0x2800
#घोषणा GL_TEXTURE_MIN_FILTER             0x2801
#घोषणा GL_TEXTURE_WRAP_S                 0x2802
#घोषणा GL_TEXTURE_WRAP_T                 0x2803
#घोषणा GL_GENERATE_MIPMAP                0x8191
#घोषणा GL_TEXTURE0                       0x84C0
#घोषणा GL_TEXTURE1                       0x84C1
#घोषणा GL_TEXTURE2                       0x84C2
#घोषणा GL_TEXTURE3                       0x84C3
#घोषणा GL_TEXTURE4                       0x84C4
#घोषणा GL_TEXTURE5                       0x84C5
#घोषणा GL_TEXTURE6                       0x84C6
#घोषणा GL_TEXTURE7                       0x84C7
#घोषणा GL_TEXTURE8                       0x84C8
#घोषणा GL_TEXTURE9                       0x84C9
#घोषणा GL_TEXTURE10                      0x84CA
#घोषणा GL_TEXTURE11                      0x84CB
#घोषणा GL_TEXTURE12                      0x84CC
#घोषणा GL_TEXTURE13                      0x84CD
#घोषणा GL_TEXTURE14                      0x84CE
#घोषणा GL_TEXTURE15                      0x84CF
#घोषणा GL_TEXTURE16                      0x84D0
#घोषणा GL_TEXTURE17                      0x84D1
#घोषणा GL_TEXTURE18                      0x84D2
#घोषणा GL_TEXTURE19                      0x84D3
#घोषणा GL_TEXTURE20                      0x84D4
#घोषणा GL_TEXTURE21                      0x84D5
#घोषणा GL_TEXTURE22                      0x84D6
#घोषणा GL_TEXTURE23                      0x84D7
#घोषणा GL_TEXTURE24                      0x84D8
#घोषणा GL_TEXTURE25                      0x84D9
#घोषणा GL_TEXTURE26                      0x84DA
#घोषणा GL_TEXTURE27                      0x84DB
#घोषणा GL_TEXTURE28                      0x84DC
#घोषणा GL_TEXTURE29                      0x84DD
#घोषणा GL_TEXTURE30                      0x84DE
#घोषणा GL_TEXTURE31                      0x84DF
#घोषणा GL_ACTIVE_TEXTURE                 0x84E0
#घोषणा GL_CLIENT_ACTIVE_TEXTURE          0x84E1
#घोषणा GL_REPEAT                         0x2901
#घोषणा GL_CLAMP_TO_EDGE                  0x812F
#घोषणा GL_LIGHT0                         0x4000
#घोषणा GL_LIGHT1                         0x4001
#घोषणा GL_LIGHT2                         0x4002
#घोषणा GL_LIGHT3                         0x4003
#घोषणा GL_LIGHT4                         0x4004
#घोषणा GL_LIGHT5                         0x4005
#घोषणा GL_LIGHT6                         0x4006
#घोषणा GL_LIGHT7                         0x4007
#घोषणा GL_ARRAY_बफर                   0x8892
#घोषणा GL_ELEMENT_ARRAY_बफर           0x8893
#घोषणा GL_ARRAY_बफर_BINDING           0x8894
#घोषणा GL_ELEMENT_ARRAY_बफर_BINDING   0x8895
#घोषणा GL_VERTEX_ARRAY_बफर_BINDING    0x8896
#घोषणा GL_NORMAL_ARRAY_बफर_BINDING    0x8897
#घोषणा GL_COLOR_ARRAY_बफर_BINDING     0x8898
#घोषणा GL_TEXTURE_COORD_ARRAY_बफर_BINDING 0x889A
#घोषणा GL_STATIC_DRAW                    0x88E4
#घोषणा GL_DYNAMIC_DRAW                   0x88E8
#घोषणा GL_बफर_आकार                    0x8764
#घोषणा GL_बफर_USAGE                   0x8765
#घोषणा GL_SUBTRACT                       0x84E7
#घोषणा GL_COMBINE                        0x8570
#घोषणा GL_COMBINE_RGB                    0x8571
#घोषणा GL_COMBINE_ALPHA                  0x8572
#घोषणा GL_RGB_SCALE                      0x8573
#घोषणा GL_ADD_SIGNED                     0x8574
#घोषणा GL_INTERPOLATE                    0x8575
#घोषणा GL_CONSTANT                       0x8576
#घोषणा GL_PRIMARY_COLOR                  0x8577
#घोषणा GL_PREVIOUS                       0x8578
#घोषणा GL_OPERAND0_RGB                   0x8590
#घोषणा GL_OPERAND1_RGB                   0x8591
#घोषणा GL_OPERAND2_RGB                   0x8592
#घोषणा GL_OPERAND0_ALPHA                 0x8598
#घोषणा GL_OPERAND1_ALPHA                 0x8599
#घोषणा GL_OPERAND2_ALPHA                 0x859A
#घोषणा GL_ALPHA_SCALE                    0x0D1C
#घोषणा GL_SRC0_RGB                       0x8580
#घोषणा GL_SRC1_RGB                       0x8581
#घोषणा GL_SRC2_RGB                       0x8582
#घोषणा GL_SRC0_ALPHA                     0x8588
#घोषणा GL_SRC1_ALPHA                     0x8589
#घोषणा GL_SRC2_ALPHA                     0x858A
#घोषणा GL_DOT3_RGB                       0x86AE
#घोषणा GL_DOT3_RGBA                      0x86AF
GL_API व्योम GL_APIENTRY glAlphaFunc (GLenum func, GLfloat ref);
GL_API व्योम GL_APIENTRY glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_API व्योम GL_APIENTRY glClearDepthf (GLfloat d);
GL_API व्योम GL_APIENTRY glClipPlanef (GLenum p, स्थिर GLfloat *eqn);
GL_API व्योम GL_APIENTRY glColor4f (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_API व्योम GL_APIENTRY glDepthRangef (GLfloat n, GLfloat f);
GL_API व्योम GL_APIENTRY glFogf (GLenum pname, GLfloat param);
GL_API व्योम GL_APIENTRY glFogfv (GLenum pname, स्थिर GLfloat *params);
GL_API व्योम GL_APIENTRY glFrustumf (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
GL_API व्योम GL_APIENTRY glGetClipPlanef (GLenum plane, GLfloat *equation);
GL_API व्योम GL_APIENTRY glGetFloatv (GLenum pname, GLfloat *तथ्य);
GL_API व्योम GL_APIENTRY glGetLightfv (GLenum light, GLenum pname, GLfloat *params);
GL_API व्योम GL_APIENTRY glGetMaterialfv (GLenum face, GLenum pname, GLfloat *params);
GL_API व्योम GL_APIENTRY glGetTexEnvfv (GLenum target, GLenum pname, GLfloat *params);
GL_API व्योम GL_APIENTRY glGetTexParameterfv (GLenum target, GLenum pname, GLfloat *params);
GL_API व्योम GL_APIENTRY glLightModelf (GLenum pname, GLfloat param);
GL_API व्योम GL_APIENTRY glLightModelfv (GLenum pname, स्थिर GLfloat *params);
GL_API व्योम GL_APIENTRY glLightf (GLenum light, GLenum pname, GLfloat param);
GL_API व्योम GL_APIENTRY glLightfv (GLenum light, GLenum pname, स्थिर GLfloat *params);
GL_API व्योम GL_APIENTRY gl_पंक्ति_Width (GLfloat width);
GL_API व्योम GL_APIENTRY glLoadMatrixf (स्थिर GLfloat *m);
GL_API व्योम GL_APIENTRY glMaterialf (GLenum face, GLenum pname, GLfloat param);
GL_API व्योम GL_APIENTRY glMaterialfv (GLenum face, GLenum pname, स्थिर GLfloat *params);
GL_API व्योम GL_APIENTRY glMultMatrixf (स्थिर GLfloat *m);
GL_API व्योम GL_APIENTRY glMultiTexCoord4f (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
GL_API व्योम GL_APIENTRY glNormal3f (GLfloat nx, GLfloat ny, GLfloat nz);
GL_API व्योम GL_APIENTRY glOrthof (GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
GL_API व्योम GL_APIENTRY glPointParameterf (GLenum pname, GLfloat param);
GL_API व्योम GL_APIENTRY glPointParameterfv (GLenum pname, स्थिर GLfloat *params);
GL_API व्योम GL_APIENTRY gl_Point_आकार (GLfloat आकार);
GL_API व्योम GL_APIENTRY glPolygonOffset (GLfloat factor, GLfloat units);
GL_API व्योम GL_APIENTRY glRotatef (GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
GL_API व्योम GL_APIENTRY glScalef (GLfloat x, GLfloat y, GLfloat z);
GL_API व्योम GL_APIENTRY glTexEnvf (GLenum target, GLenum pname, GLfloat param);
GL_API व्योम GL_APIENTRY glTexEnvfv (GLenum target, GLenum pname, स्थिर GLfloat *params);
GL_API व्योम GL_APIENTRY glTexParameterf (GLenum target, GLenum pname, GLfloat param);
GL_API व्योम GL_APIENTRY glTexParameterfv (GLenum target, GLenum pname, स्थिर GLfloat *params);
GL_API व्योम GL_APIENTRY glTranslatef (GLfloat x, GLfloat y, GLfloat z);
GL_API व्योम GL_APIENTRY glActiveTexture (GLenum texture);
GL_API व्योम GL_APIENTRY glAlphaFuncx (GLenum func, GLfixed ref);
GL_API व्योम GL_APIENTRY gl_Bind_बफर (GLenum target, GLuint बफर_2);
GL_API व्योम GL_APIENTRY glBindTexture (GLenum target, GLuint texture);
GL_API व्योम GL_APIENTRY glBlendFunc (GLenum sfactor, GLenum dfactor);
GL_API व्योम GL_APIENTRY gl_बफर_तथ्य (GLenum target, GLsizeiptr आकार, स्थिर व्योम *तथ्य, GLenum usage);
GL_API व्योम GL_APIENTRY gl_बफर_Sub_तथ्य (GLenum target, GLintptr offset, GLsizeiptr आकार, स्थिर व्योम *तथ्य);
GL_API व्योम GL_APIENTRY glClear (GLbitfield mask);
GL_API व्योम GL_APIENTRY glClearColorx (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GL_API व्योम GL_APIENTRY glClearDepthx (GLfixed depth);
GL_API व्योम GL_APIENTRY glClearStencil (GLint s);
GL_API व्योम GL_APIENTRY glClientActiveTexture (GLenum texture);
GL_API व्योम GL_APIENTRY glClipPlanex (GLenum plane, स्थिर GLfixed *equation);
GL_API व्योम GL_APIENTRY glColor4ub (GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
GL_API व्योम GL_APIENTRY glColor4x (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
GL_API व्योम GL_APIENTRY glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
GL_API व्योम GL_APIENTRY glColorPointer (GLint आकार, GLenum type, GLsizei stride, स्थिर व्योम *pointer);
GL_API व्योम GL_APIENTRY glCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei image_आकार, स्थिर व्योम *तथ्य);
GL_API व्योम GL_APIENTRY glCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei image_आकार, स्थिर व्योम *तथ्य);
GL_API व्योम GL_APIENTRY glCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
GL_API व्योम GL_APIENTRY glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
GL_API व्योम GL_APIENTRY glCullFace (GLenum mode);
GL_API व्योम GL_APIENTRY glDeleteBuffers (GLsizei n, स्थिर GLuint *buffers);
GL_API व्योम GL_APIENTRY glDeleteTextures (GLsizei n, स्थिर GLuint *textures);
GL_API व्योम GL_APIENTRY glDepthFunc (GLenum func);
GL_API व्योम GL_APIENTRY glDepthMask (GLboolean flag);
GL_API व्योम GL_APIENTRY glDepthRangex (GLfixed n, GLfixed f);
GL_API व्योम GL_APIENTRY glDisable (GLenum cap);
GL_API व्योम GL_APIENTRY glDisableClientState (GLenum array);
GL_API व्योम GL_APIENTRY glDrawArrays (GLenum mode, GLint first, GLsizei गिनती);
GL_API व्योम GL_APIENTRY glDrawElements (GLenum mode, GLsizei गिनती, GLenum type, स्थिर व्योम *indices);
GL_API व्योम GL_APIENTRY glEnable (GLenum cap);
GL_API व्योम GL_APIENTRY glEnableClientState (GLenum array);
GL_API व्योम GL_APIENTRY glFinish (व्योम);
GL_API व्योम GL_APIENTRY glFlush (व्योम);
GL_API व्योम GL_APIENTRY glFogx (GLenum pname, GLfixed param);
GL_API व्योम GL_APIENTRY glFogxv (GLenum pname, स्थिर GLfixed *param);
GL_API व्योम GL_APIENTRY glFrontFace (GLenum mode);
GL_API व्योम GL_APIENTRY glFrustumx (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
GL_API व्योम GL_APIENTRY glGetBooleanv (GLenum pname, GLboolean *तथ्य);
GL_API व्योम GL_APIENTRY gl_Get_बफर_Parameteriv (GLenum target, GLenum pname, GLint *params);
GL_API व्योम GL_APIENTRY glGetClipPlanex (GLenum plane, GLfixed *equation);
GL_API व्योम GL_APIENTRY glGenBuffers (GLsizei n, GLuint *buffers);
GL_API व्योम GL_APIENTRY glGenTextures (GLsizei n, GLuint *textures);
GL_API GLenum GL_APIENTRY glGetError (व्योम);
GL_API व्योम GL_APIENTRY glGetFixedv (GLenum pname, GLfixed *तथ्य);
GL_API व्योम GL_APIENTRY glGetIntegerv (GLenum pname, GLint *तथ्य);
GL_API व्योम GL_APIENTRY glGetLightxv (GLenum light, GLenum pname, GLfixed *params);
GL_API व्योम GL_APIENTRY glGetMaterialxv (GLenum face, GLenum pname, GLfixed *params);
GL_API व्योम GL_APIENTRY glGetPointerv (GLenum pname, व्योम **params);
GL_API स्थिर GLubyte *GL_APIENTRY glGetString (GLenum name);
GL_API व्योम GL_APIENTRY glGetTexEnviv (GLenum target, GLenum pname, GLint *params);
GL_API व्योम GL_APIENTRY glGetTexEnvxv (GLenum target, GLenum pname, GLfixed *params);
GL_API व्योम GL_APIENTRY glGetTexParameteriv (GLenum target, GLenum pname, GLint *params);
GL_API व्योम GL_APIENTRY glGetTexParameterxv (GLenum target, GLenum pname, GLfixed *params);
GL_API व्योम GL_APIENTRY glHint (GLenum target, GLenum mode);
GL_API GLboolean GL_APIENTRY gl_Is_बफर (GLuint बफर_2);
GL_API GLboolean GL_APIENTRY glIsEnabled (GLenum cap);
GL_API GLboolean GL_APIENTRY glIsTexture (GLuint texture);
GL_API व्योम GL_APIENTRY glLightModelx (GLenum pname, GLfixed param);
GL_API व्योम GL_APIENTRY glLightModelxv (GLenum pname, स्थिर GLfixed *param);
GL_API व्योम GL_APIENTRY glLightx (GLenum light, GLenum pname, GLfixed param);
GL_API व्योम GL_APIENTRY glLightxv (GLenum light, GLenum pname, स्थिर GLfixed *params);
GL_API व्योम GL_APIENTRY gl_पंक्ति_Widthx (GLfixed width);
GL_API व्योम GL_APIENTRY glLoadIdentity (व्योम);
GL_API व्योम GL_APIENTRY glLoadMatrixx (स्थिर GLfixed *m);
GL_API व्योम GL_APIENTRY glLogicOp (GLenum opcode);
GL_API व्योम GL_APIENTRY glMaterialx (GLenum face, GLenum pname, GLfixed param);
GL_API व्योम GL_APIENTRY glMaterialxv (GLenum face, GLenum pname, स्थिर GLfixed *param);
GL_API व्योम GL_APIENTRY glMatrixMode (GLenum mode);
GL_API व्योम GL_APIENTRY glMultMatrixx (स्थिर GLfixed *m);
GL_API व्योम GL_APIENTRY glMultiTexCoord4x (GLenum texture, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
GL_API व्योम GL_APIENTRY glNormal3x (GLfixed nx, GLfixed ny, GLfixed nz);
GL_API व्योम GL_APIENTRY glNormalPointer (GLenum type, GLsizei stride, स्थिर व्योम *pointer);
GL_API व्योम GL_APIENTRY glOrthox (GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);
GL_API व्योम GL_APIENTRY glPixelStorei (GLenum pname, GLint param);
GL_API व्योम GL_APIENTRY glPointParameterx (GLenum pname, GLfixed param);
GL_API व्योम GL_APIENTRY glPointParameterxv (GLenum pname, स्थिर GLfixed *params);
GL_API व्योम GL_APIENTRY glPointSizex (GLfixed आकार);
GL_API व्योम GL_APIENTRY glPolygonOffsetx (GLfixed factor, GLfixed units);
GL_API व्योम GL_APIENTRY gl_निकालो_Matrix (व्योम);
GL_API व्योम GL_APIENTRY gl_धकेलो_Matrix (व्योम);
GL_API व्योम GL_APIENTRY glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, व्योम *pixels);
GL_API व्योम GL_APIENTRY glRotatex (GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
GL_API व्योम GL_APIENTRY glSampleCoverage (GLfloat मूल्य, GLboolean invert);
GL_API व्योम GL_APIENTRY glSampleCoveragex (GLclampx मूल्य, GLboolean invert);
GL_API व्योम GL_APIENTRY glScalex (GLfixed x, GLfixed y, GLfixed z);
GL_API व्योम GL_APIENTRY glScissor (GLint x, GLint y, GLsizei width, GLsizei height);
GL_API व्योम GL_APIENTRY glShadeModel (GLenum mode);
GL_API व्योम GL_APIENTRY glStencilFunc (GLenum func, GLint ref, GLuint mask);
GL_API व्योम GL_APIENTRY glStencilMask (GLuint mask);
GL_API व्योम GL_APIENTRY glStencilOp (GLenum fail, GLenum zfail, GLenum zpass);
GL_API व्योम GL_APIENTRY glTexCoordPointer (GLint आकार, GLenum type, GLsizei stride, स्थिर व्योम *pointer);
GL_API व्योम GL_APIENTRY glTexEnvi (GLenum target, GLenum pname, GLint param);
GL_API व्योम GL_APIENTRY glTexEnvx (GLenum target, GLenum pname, GLfixed param);
GL_API व्योम GL_APIENTRY glTexEnviv (GLenum target, GLenum pname, स्थिर GLint *params);
GL_API व्योम GL_APIENTRY glTexEnvxv (GLenum target, GLenum pname, स्थिर GLfixed *params);
GL_API व्योम GL_APIENTRY glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, स्थिर व्योम *pixels);
GL_API व्योम GL_APIENTRY glTexParameteri (GLenum target, GLenum pname, GLint param);
GL_API व्योम GL_APIENTRY glTexParameterx (GLenum target, GLenum pname, GLfixed param);
GL_API व्योम GL_APIENTRY glTexParameteriv (GLenum target, GLenum pname, स्थिर GLint *params);
GL_API व्योम GL_APIENTRY glTexParameterxv (GLenum target, GLenum pname, स्थिर GLfixed *params);
GL_API व्योम GL_APIENTRY glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, स्थिर व्योम *pixels);
GL_API व्योम GL_APIENTRY glTranslatex (GLfixed x, GLfixed y, GLfixed z);
GL_API व्योम GL_APIENTRY glVertexPointer (GLint आकार, GLenum type, GLsizei stride, स्थिर व्योम *pointer);
GL_API व्योम GL_APIENTRY glViewport (GLint x, GLint y, GLsizei width, GLsizei height);
#पूर्ण_अगर /* GL_VERSION_ES_CM_1_0 */

#अगर_अघोषित GL_OES_compressed_paletted_texture
#घोषणा GL_OES_compressed_paletted_texture 1
#घोषणा GL_PALETTE4_RGB8_OES              0x8B90
#घोषणा GL_PALETTE4_RGBA8_OES             0x8B91
#घोषणा GL_PALETTE4_R5_G6_B5_OES          0x8B92
#घोषणा GL_PALETTE4_RGBA4_OES             0x8B93
#घोषणा GL_PALETTE4_RGB5_A1_OES           0x8B94
#घोषणा GL_PALETTE8_RGB8_OES              0x8B95
#घोषणा GL_PALETTE8_RGBA8_OES             0x8B96
#घोषणा GL_PALETTE8_R5_G6_B5_OES          0x8B97
#घोषणा GL_PALETTE8_RGBA4_OES             0x8B98
#घोषणा GL_PALETTE8_RGB5_A1_OES           0x8B99
#पूर्ण_अगर /* GL_OES_compressed_paletted_texture */

#अगर_अघोषित GL_OES_point_आकार_array
#घोषणा GL_OES_point_आकार_array 1
#घोषणा GL_POINT_आकार_ARRAY_OES           0x8B9C
#घोषणा GL_POINT_आकार_ARRAY_TYPE_OES      0x898A
#घोषणा GL_POINT_आकार_ARRAY_STRIDE_OES    0x898B
#घोषणा GL_POINT_आकार_ARRAY_POINTER_OES   0x898C
#घोषणा GL_POINT_आकार_ARRAY_बफर_BINDING_OES 0x8B9F
GL_API व्योम GL_APIENTRY gl_Point_आकार_Pointer_OES (GLenum type, GLsizei stride, स्थिर व्योम *pointer);
#पूर्ण_अगर /* GL_OES_point_size_array */

#अगर_अघोषित GL_OES_point_sprite
#घोषणा GL_OES_point_sprite 1
#घोषणा GL_POINT_SPRITE_OES               0x8861
#घोषणा GL_COORD_REPLACE_OES              0x8862
#पूर्ण_अगर /* GL_OES_point_sprite */

#अगर_अघोषित GL_OES_read_format
#घोषणा GL_OES_read_format 1
#घोषणा GL_IMPLEMENTATION_COLOR_READ_TYPE_OES 0x8B9A
#घोषणा GL_IMPLEMENTATION_COLOR_READ_FORMAT_OES 0x8B9B
#पूर्ण_अगर /* GL_OES_read_format */

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर
