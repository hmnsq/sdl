#నిర్వచితం_కాకపోతే __gles2_gl32_h_
#నిర్వచించు __gles2_gl32_h_ 1

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

#అన్తర్భావ <GLES3/gl3platform.h>

#నిర్వచితం_కాకపోతే GL_APIENTRYP
#నిర్వచించు GL_APIENTRYP GL_APIENTRY*
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే GL_GLES_PROTOTYPES
#నిర్వచించు GL_GLES_PROTOTYPES 1
#అయితే_ముగింపు

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

#నిర్వచితం_కాకపోతే GL_ES_సంస్కరణ_2_0
#నిర్వచించు GL_ES_సంస్కరణ_2_0 1
#అన్తర్భావ <KHR/khrplatform.h>
రకనిర్వచనం khronos_int8_t GLbyte;
రకనిర్వచనం khronos_float_t GLclampf;
రకనిర్వచనం khronos_int32_t GLfixed;
రకనిర్వచనం khronos_int16_t GLshort;
రకనిర్వచనం khronos_uint16_t GLushort;
రకనిర్వచనం శూన్య GLvoid;
రకనిర్వచనం నిర్మాణం __GLsync *GLsync;
రకనిర్వచనం khronos_int64_t GLint64;
రకనిర్వచనం khronos_uint64_t GLuint64;
రకనిర్వచనం గుర్తులేని పూర్ణాంకం GLenum;
రకనిర్వచనం గుర్తులేని పూర్ణాంకం GLuint;
రకనిర్వచనం అక్షరం GLchar;
రకనిర్వచనం khronos_float_t GLfloat;
రకనిర్వచనం khronos_ssize_t GLsizeiptr;
రకనిర్వచనం khronos_intptr_t GLintptr;
రకనిర్వచనం గుర్తులేని పూర్ణాంకం GLbitfield;
రకనిర్వచనం పూర్ణాంకం GLint;
రకనిర్వచనం గుర్తులేని అక్షరం GLboolean;
రకనిర్వచనం పూర్ణాంకం GLsizei;
రకనిర్వచనం khronos_uint8_t GLubyte;
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
#నిర్వచించు GL_FUNC_కూడు                       0x8006
#నిర్వచించు GL_BLEND_EQUATION                 0x8009
#నిర్వచించు GL_BLEND_EQUATION_RGB             0x8009
#నిర్వచించు GL_BLEND_EQUATION_ALPHA           0x883D
#నిర్వచించు GL_FUNC_వ్యవకలనం                  0x800A
#నిర్వచించు GL_FUNC_తిరగేయి_వ్యవకలనం          0x800B
#నిర్వచించు GL_BLEND_DST_RGB                  0x80C8
#నిర్వచించు GL_BLEND_SRC_RGB                  0x80C9
#నిర్వచించు GL_BLEND_DST_ALPHA                0x80CA
#నిర్వచించు GL_BLEND_SRC_ALPHA                0x80CB
#నిర్వచించు GL_CONSTANT_COLOR                 0x8001
#నిర్వచించు GL_ONE_MINUS_CONSTANT_COLOR       0x8002
#నిర్వచించు GL_CONSTANT_ALPHA                 0x8003
#నిర్వచించు GL_ONE_MINUS_CONSTANT_ALPHA       0x8004
#నిర్వచించు GL_BLEND_COLOR                    0x8005
#నిర్వచించు GL_ARRAY_బఫరు                   0x8892
#నిర్వచించు GL_ELEMENT_ARRAY_బఫరు           0x8893
#నిర్వచించు GL_ARRAY_బఫరు_BINDING           0x8894
#నిర్వచించు GL_ELEMENT_ARRAY_బఫరు_BINDING   0x8895
#నిర్వచించు GL_ప్రవాహం_DRAW                    0x88E0
#నిర్వచించు GL_STATIC_DRAW                    0x88E4
#నిర్వచించు GL_DYNAMIC_DRAW                   0x88E8
#నిర్వచించు GL_బఫరు_కొలత                    0x8764
#నిర్వచించు GL_బఫరు_USAGE                   0x8765
#నిర్వచించు GL_CURRENT_శీర్షం_ATTRIB          0x8626
#నిర్వచించు GL_FRONT                          0x0404
#నిర్వచించు GL_వెనుక                           0x0405
#నిర్వచించు GL_FRONT_AND_వెనుక                 0x0408
#నిర్వచించు GL_TEXTURE_2D                     0x0DE1
#నిర్వచించు GL_CULL_FACE                      0x0B44
#నిర్వచించు GL_BLEND                          0x0BE2
#నిర్వచించు GL_DITHER                         0x0BD0
#నిర్వచించు GL_STENCIL_TEST                   0x0B90
#నిర్వచించు GL_లోతు_TEST                     0x0B71
#నిర్వచించు GL_SCISSOR_TEST                   0x0C11
#నిర్వచించు GL_POLYGON_స్థానభ్రంశం_FILL            0x8037
#నిర్వచించు GL_SAMPLE_ALPHA_గమ్యం_COVERAGE       0x809E
#నిర్వచించు GL_SAMPLE_COVERAGE                0x80A0
#నిర్వచించు GL_NO_ERROR                       0
#నిర్వచించు GL_INVALID_ENUM                   0x0500
#నిర్వచించు GL_INVALID_విలువ                  0x0501
#నిర్వచించు GL_INVALID_OPERATION              0x0502
#నిర్వచించు GL_బహిర్గతం_యొక్క_జ్ఞాపకం                  0x0505
#నిర్వచించు GL_CW                             0x0900
#నిర్వచించు GL_CCW                            0x0901
#నిర్వచించు GL_పంక్తి_వెడల్పు                     0x0B21
#నిర్వచించు GL_ALIASED_బిందువు_కొలత_RANGE       0x846D
#నిర్వచించు GL_ALIASED_పంక్తి_వెడల్పు_RANGE       0x846E
#నిర్వచించు GL_CULL_FACE_బహుళకం                 0x0B45
#నిర్వచించు GL_FRONT_FACE                     0x0B46
#నిర్వచించు GL_లోతు_RANGE                    0x0B70
#నిర్వచించు GL_లోతు_WRITEMASK                0x0B72
#నిర్వచించు GL_లోతు_CLEAR_విలువ              0x0B73
#నిర్వచించు GL_లోతు_FUNC                     0x0B74
#నిర్వచించు GL_STENCIL_CLEAR_విలువ            0x0B91
#నిర్వచించు GL_STENCIL_FUNC                   0x0B92
#నిర్వచించు GL_STENCIL_FAIL                   0x0B94
#నిర్వచించు GL_STENCIL_PASS_లోతు_FAIL        0x0B95
#నిర్వచించు GL_STENCIL_PASS_లోతు_PASS        0x0B96
#నిర్వచించు GL_STENCIL_REF                    0x0B97
#నిర్వచించు GL_STENCIL_విలువ_ముసుగు             0x0B93
#నిర్వచించు GL_STENCIL_WRITEMASK              0x0B98
#నిర్వచించు GL_STENCIL_వెనుక_FUNC              0x8800
#నిర్వచించు GL_STENCIL_వెనుక_FAIL              0x8801
#నిర్వచించు GL_STENCIL_వెనుక_PASS_లోతు_FAIL   0x8802
#నిర్వచించు GL_STENCIL_వెనుక_PASS_లోతు_PASS   0x8803
#నిర్వచించు GL_STENCIL_వెనుక_REF               0x8CA3
#నిర్వచించు GL_STENCIL_వెనుక_విలువ_ముసుగు        0x8CA4
#నిర్వచించు GL_STENCIL_వెనుక_WRITEMASK         0x8CA5
#నిర్వచించు GL_VIEWPORT                       0x0BA2
#నిర్వచించు GL_SCISSOR_BOX                    0x0C10
#నిర్వచించు GL_COLOR_CLEAR_విలువ              0x0C22
#నిర్వచించు GL_COLOR_WRITEMASK                0x0C23
#నిర్వచించు GL_UNPACK_ALIGNMENT               0x0CF5
#నిర్వచించు GL_PACK_ALIGNMENT                 0x0D05
#నిర్వచించు GL_MAX_TEXTURE_కొలత               0x0D33
#నిర్వచించు GL_MAX_VIEWPORT_DIMS              0x0D3A
#నిర్వచించు GL_SUBPIXEL_బిట్లు                  0x0D50
#నిర్వచించు GL_RED_బిట్లు                       0x0D52
#నిర్వచించు GL_GREEN_బిట్లు                     0x0D53
#నిర్వచించు GL_BLUE_బిట్లు                      0x0D54
#నిర్వచించు GL_ALPHA_బిట్లు                     0x0D55
#నిర్వచించు GL_లోతు_బిట్లు                     0x0D56
#నిర్వచించు GL_STENCIL_బిట్లు                   0x0D57
#నిర్వచించు GL_POLYGON_స్థానభ్రంశం_UNITS           0x2A00
#నిర్వచించు GL_POLYGON_స్థానభ్రంశం_గుణకం          0x8038
#నిర్వచించు GL_TEXTURE_BINDING_2D             0x8069
#నిర్వచించు GL_SAMPLE_BUFFERS                 0x80A8
#నిర్వచించు GL_SAMPLES                        0x80A9
#నిర్వచించు GL_SAMPLE_COVERAGE_విలువ          0x80AA
#నిర్వచించు GL_SAMPLE_COVERAGE_INVERT         0x80AB
#నిర్వచించు GL_అంకె_COMPRESSED_TEXTURE_FORMATS 0x86A2
#నిర్వచించు GL_COMPRESSED_TEXTURE_FORMATS     0x86A3
#నిర్వచించు GL_DONT_CARE                      0x1100
#నిర్వచించు GL_FASTEST                        0x1101
#నిర్వచించు GL_NICEST                         0x1102
#నిర్వచించు GL_GENERATE_MIPMAP_HINT           0x8192
#నిర్వచించు GL_BYTE                           0x1400
#నిర్వచించు GL_UNSIGNED_BYTE                  0x1401
#నిర్వచించు GL_SHORT                          0x1402
#నిర్వచించు GL_UNSIGNED_SHORT                 0x1403
#నిర్వచించు GL_INT                            0x1404
#నిర్వచించు GL_UNSIGNED_INT                   0x1405
#నిర్వచించు GL_FLOAT                          0x1406
#నిర్వచించు GL_FIXED                          0x140C
#నిర్వచించు GL_లోతు_COMPONENT                0x1902
#నిర్వచించు GL_ALPHA                          0x1906
#నిర్వచించు GL_RGB                            0x1907
#నిర్వచించు GL_RGBA                           0x1908
#నిర్వచించు GL_LUMINANCE                      0x1909
#నిర్వచించు GL_LUMINANCE_ALPHA                0x190A
#నిర్వచించు GL_UNSIGNED_SHORT_4_4_4_4         0x8033
#నిర్వచించు GL_UNSIGNED_SHORT_5_5_5_1         0x8034
#నిర్వచించు GL_UNSIGNED_SHORT_5_6_5           0x8363
#నిర్వచించు GL_FRAGMENT_SHADER                0x8B30
#నిర్వచించు GL_శీర్షం_SHADER                  0x8B31
#నిర్వచించు GL_MAX_శీర్షం_ATTRIBS             0x8869
#నిర్వచించు GL_MAX_శీర్షం_ఏకరీతి_VECTORS     0x8DFB
#నిర్వచించు GL_MAX_VARYING_VECTORS            0x8DFC
#నిర్వచించు GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 0x8B4D
#నిర్వచించు GL_MAX_శీర్షం_TEXTURE_IMAGE_UNITS 0x8B4C
#నిర్వచించు GL_MAX_TEXTURE_IMAGE_UNITS        0x8872
#నిర్వచించు GL_MAX_FRAGMENT_ఏకరీతి_VECTORS   0x8DFD
#నిర్వచించు GL_SHADER_TYPE                    0x8B4F
#నిర్వచించు GL_DELETE_స్థితి                  0x8B80
#నిర్వచించు GL_LINK_స్థితి                    0x8B82
#నిర్వచించు GL_VALIDATE_స్థితి                0x8B83
#నిర్వచించు GL_ATTACHED_SHADERS               0x8B85
#నిర్వచించు GL_చురుకైన_UNIFORMS                0x8B86
#నిర్వచించు GL_చురుకైన_ఏకరీతి_MAX_నిడివి      0x8B87
#నిర్వచించు GL_చురుకైన_లక్షణాలు              0x8B89
#నిర్వచించు GL_చురుకైన_ATTRIBUTE_MAX_నిడివి    0x8B8A
#నిర్వచించు GL_SHADING_LANGUAGE_సంస్కరణ       0x8B8C
#నిర్వచించు GL_CURRENT_కార్యక్రమం                0x8B8D
#నిర్వచించు GL_NEVER                          0x0200
#నిర్వచించు GL_LESS                           0x0201
#నిర్వచించు GL_EQUAL                          0x0202
#నిర్వచించు GL_LEQUAL                         0x0203
#నిర్వచించు GL_GREATER                        0x0204
#నిర్వచించు GL_NOTEQUAL                       0x0205
#నిర్వచించు GL_GEQUAL                         0x0206
#నిర్వచించు GL_ALWAYS                         0x0207
#నిర్వచించు GL_KEEP                           0x1E00
#నిర్వచించు GL_REPLACE                        0x1E01
#నిర్వచించు GL_INCR                           0x1E02
#నిర్వచించు GL_DECR                           0x1E03
#నిర్వచించు GL_INVERT                         0x150A
#నిర్వచించు GL_INCR_WRAP                      0x8507
#నిర్వచించు GL_DECR_WRAP                      0x8508
#నిర్వచించు GL_VENDOR                         0x1F00
#నిర్వచించు GL_RENDERER                       0x1F01
#నిర్వచించు GL_సంస్కరణ                        0x1F02
#నిర్వచించు GL_EXTENSIONS                     0x1F03
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
#నిర్వచించు GL_TEXTURE                        0x1702
#నిర్వచించు GL_TEXTURE_CUBE_MAP               0x8513
#నిర్వచించు GL_TEXTURE_BINDING_CUBE_MAP       0x8514
#నిర్వచించు GL_TEXTURE_CUBE_MAP_ధనాత్మక_X    0x8515
#నిర్వచించు GL_TEXTURE_CUBE_MAP_NEGATIVE_X    0x8516
#నిర్వచించు GL_TEXTURE_CUBE_MAP_ధనాత్మక_Y    0x8517
#నిర్వచించు GL_TEXTURE_CUBE_MAP_NEGATIVE_Y    0x8518
#నిర్వచించు GL_TEXTURE_CUBE_MAP_ధనాత్మక_Z    0x8519
#నిర్వచించు GL_TEXTURE_CUBE_MAP_NEGATIVE_Z    0x851A
#నిర్వచించు GL_MAX_CUBE_MAP_TEXTURE_కొలత      0x851C
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
#నిర్వచించు GL_REPEAT                         0x2901
#నిర్వచించు GL_CLAMP_గమ్యం_అంచు                  0x812F
#నిర్వచించు GL_MIRRORED_REPEAT                0x8370
#నిర్వచించు GL_FLOAT_VEC2                     0x8B50
#నిర్వచించు GL_FLOAT_VEC3                     0x8B51
#నిర్వచించు GL_FLOAT_VEC4                     0x8B52
#నిర్వచించు GL_INT_VEC2                       0x8B53
#నిర్వచించు GL_INT_VEC3                       0x8B54
#నిర్వచించు GL_INT_VEC4                       0x8B55
#నిర్వచించు GL_BOOL                           0x8B56
#నిర్వచించు GL_BOOL_VEC2                      0x8B57
#నిర్వచించు GL_BOOL_VEC3                      0x8B58
#నిర్వచించు GL_BOOL_VEC4                      0x8B59
#నిర్వచించు GL_FLOAT_MAT2                     0x8B5A
#నిర్వచించు GL_FLOAT_MAT3                     0x8B5B
#నిర్వచించు GL_FLOAT_MAT4                     0x8B5C
#నిర్వచించు GL_SAMPLER_2D                     0x8B5E
#నిర్వచించు GL_SAMPLER_CUBE                   0x8B60
#నిర్వచించు GL_శీర్షం_ATTRIB_ARRAY_ENABLED    0x8622
#నిర్వచించు GL_శీర్షం_ATTRIB_ARRAY_కొలత       0x8623
#నిర్వచించు GL_శీర్షం_ATTRIB_ARRAY_STRIDE     0x8624
#నిర్వచించు GL_శీర్షం_ATTRIB_ARRAY_TYPE       0x8625
#నిర్వచించు GL_శీర్షం_ATTRIB_ARRAY_NORMALIZED 0x886A
#నిర్వచించు GL_శీర్షం_ATTRIB_ARRAY_సూచిక    0x8645
#నిర్వచించు GL_శీర్షం_ATTRIB_ARRAY_బఫరు_BINDING 0x889F
#నిర్వచించు GL_IMPLEMENTATION_COLOR_READ_TYPE 0x8B9A
#నిర్వచించు GL_IMPLEMENTATION_COLOR_READ_FORMAT 0x8B9B
#నిర్వచించు GL_COMPILE_స్థితి                 0x8B81
#నిర్వచించు GL_INFO_LOG_నిడివి                0x8B84
#నిర్వచించు GL_SHADER_ఆధారం_నిడివి           0x8B88
#నిర్వచించు GL_SHADER_COMPILER                0x8DFA
#నిర్వచించు GL_SHADER_ద్విమాన_FORMATS          0x8DF8
#నిర్వచించు GL_అంకె_SHADER_ద్విమాన_FORMATS      0x8DF9
#నిర్వచించు GL_దిగువ_FLOAT                      0x8DF0
#నిర్వచించు GL_MEDIUM_FLOAT                   0x8DF1
#నిర్వచించు GL_ఎగువ_FLOAT                     0x8DF2
#నిర్వచించు GL_దిగువ_INT                        0x8DF3
#నిర్వచించు GL_MEDIUM_INT                     0x8DF4
#నిర్వచించు GL_ఎగువ_INT                       0x8DF5
#నిర్వచించు GL_FRAMEBUFFER                    0x8D40
#నిర్వచించు GL_RENDERBUFFER                   0x8D41
#నిర్వచించు GL_RGBA4                          0x8056
#నిర్వచించు GL_RGB5_A1                        0x8057
#నిర్వచించు GL_RGB565                         0x8D62
#నిర్వచించు GL_లోతు_COMPONENT16              0x81A5
#నిర్వచించు GL_STENCIL_INDEX8                 0x8D48
#నిర్వచించు GL_RENDERBUFFER_వెడల్పు             0x8D42
#నిర్వచించు GL_RENDERBUFFER_ఎత్తు            0x8D43
#నిర్వచించు GL_RENDERBUFFER_అంతర్గత_FORMAT   0x8D44
#నిర్వచించు GL_RENDERBUFFER_RED_కొలత          0x8D50
#నిర్వచించు GL_RENDERBUFFER_GREEN_కొలత        0x8D51
#నిర్వచించు GL_RENDERBUFFER_BLUE_కొలత         0x8D52
#నిర్వచించు GL_RENDERBUFFER_ALPHA_కొలత        0x8D53
#నిర్వచించు GL_RENDERBUFFER_లోతు_కొలత        0x8D54
#నిర్వచించు GL_RENDERBUFFER_STENCIL_కొలత      0x8D55
#నిర్వచించు GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE 0x8CD0
#నిర్వచించు GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME 0x8CD1
#నిర్వచించు GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL 0x8CD2
#నిర్వచించు GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE 0x8CD3
#నిర్వచించు GL_COLOR_ATTACHMENT0              0x8CE0
#నిర్వచించు GL_లోతు_ATTACHMENT               0x8D00
#నిర్వచించు GL_STENCIL_ATTACHMENT             0x8D20
#నిర్వచించు GL_NONE                           0
#నిర్వచించు GL_FRAMEBUFFER_COMPLETE           0x8CD5
#నిర్వచించు GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT 0x8CD6
#నిర్వచించు GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 0x8CD7
#నిర్వచించు GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS 0x8CD9
#నిర్వచించు GL_FRAMEBUFFER_UNSUPPORTED        0x8CDD
#నిర్వచించు GL_FRAMEBUFFER_BINDING            0x8CA6
#నిర్వచించు GL_RENDERBUFFER_BINDING           0x8CA7
#నిర్వచించు GL_MAX_RENDERBUFFER_కొలత          0x84E8
#నిర్వచించు GL_INVALID_FRAMEBUFFER_OPERATION  0x0506
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLACTIVETEXTUREPROC) (GLenum texture);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLATTACHSHADERPROC) (GLuint కార్యక్రమం, GLuint shader);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBINDATTRIBLOCATIONPROC) (GLuint కార్యక్రమం, GLuint సూచీ, స్థిరరాశి GLchar *name);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBINDBUFFERPROC) (GLenum లక్ష్యం, GLuint బఫరు_2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBINDFRAMEBUFFERPROC) (GLenum లక్ష్యం, GLuint framebuffer);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBINDRENDERBUFFERPROC) (GLenum లక్ష్యం, GLuint renderbuffer);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBINDTEXTUREPROC) (GLenum లక్ష్యం, GLuint texture);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBLENDCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBLENDEQUATIONPROC) (GLenum బహుళకం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEPROC) (GLenum బహుళకం_RGB, GLenum బహుళకం_Alpha);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBLENDFUNCPROC) (GLenum sfactor, GLenum dfactor);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEPROC) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBUFFERDATAPROC) (GLenum లక్ష్యం, GLsizeiptr కొలత, స్థిరరాశి శూన్య *దత్తాంశం, GLenum usage);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBUFFERSUBDATAPROC) (GLenum లక్ష్యం, GLintptr స్థానభ్రంశం_2, GLsizeiptr కొలత, స్థిరరాశి శూన్య *దత్తాంశం);
రకనిర్వచనం GLenum (GL_APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSPROC) (GLenum లక్ష్యం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCLEARPROC) (GLbitfield ముసుగు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCLEARCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCLEARDEPTHFPROC) (GLfloat d);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCLEARSTENCILPROC) (GLint s);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCOLORMASKPROC) (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCOMPILESHADERPROC) (GLuint shader);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCOMPRESSEDTEXIMAGE2DPROC) (GLenum లక్ష్యం, GLint level, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు, GLint border, GLsizei image_కొలత, స్థిరరాశి శూన్య *దత్తాంశం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) (GLenum లక్ష్యం, GLint level, GLint xoffset, GLint yoffset, GLsizei వెడల్పు, GLsizei ఎత్తు, GLenum format, GLsizei image_కొలత, స్థిరరాశి శూన్య *దత్తాంశం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCOPYTEXIMAGE2DPROC) (GLenum లక్ష్యం, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei వెడల్పు, GLsizei ఎత్తు, GLint border);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCOPYTEXSUBIMAGE2DPROC) (GLenum లక్ష్యం, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei వెడల్పు, GLsizei ఎత్తు);
రకనిర్వచనం GLuint (GL_APIENTRYP PFNGLCREATEPROGRAMPROC) (శూన్య);
రకనిర్వచనం GLuint (GL_APIENTRYP PFNGLCREATESHADERPROC) (GLenum type);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCULLFACEPROC) (GLenum బహుళకం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDELETEBUFFERSPROC) (GLsizei n, స్థిరరాశి GLuint *buffers);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDELETEFRAMEBUFFERSPROC) (GLsizei n, స్థిరరాశి GLuint *framebuffers);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDELETEPROGRAMPROC) (GLuint కార్యక్రమం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDELETERENDERBUFFERSPROC) (GLsizei n, స్థిరరాశి GLuint *renderbuffers);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDELETESHADERPROC) (GLuint shader);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDELETETEXTURESPROC) (GLsizei n, స్థిరరాశి GLuint *textures);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDEPTHFUNCPROC) (GLenum func);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDEPTHMASKPROC) (GLboolean flag);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDEPTHRANGEFPROC) (GLfloat n, GLfloat f);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDETACHSHADERPROC) (GLuint కార్యక్రమం, GLuint shader);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDISABLEPROC) (GLenum cap);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint సూచీ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWARRAYSPROC) (GLenum బహుళకం, GLint మొదటి, GLsizei లెక్క);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWELEMENTSPROC) (GLenum బహుళకం, GLsizei లెక్క, GLenum type, స్థిరరాశి శూన్య *indices);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLENABLEPROC) (GLenum cap);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint సూచీ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFINISHPROC) (శూన్య);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFLUSHPROC) (శూన్య);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFERPROC) (GLenum లక్ష్యం, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DPROC) (GLenum లక్ష్యం, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFRONTFACEPROC) (GLenum బహుళకం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGENBUFFERSPROC) (GLsizei n, GLuint *buffers);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGENERATEMIPMAPPROC) (GLenum లక్ష్యం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGENFRAMEBUFFERSPROC) (GLsizei n, GLuint *framebuffers);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGENRENDERBUFFERSPROC) (GLsizei n, GLuint *renderbuffers);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGENTEXTURESPROC) (GLsizei n, GLuint *textures);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETACTIVEATTRIBPROC) (GLuint కార్యక్రమం, GLuint సూచీ, GLsizei buf_కొలత, GLsizei *నిడివి, GLint *కొలత, GLenum *type, GLchar *name);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETACTIVEUNIFORMPROC) (GLuint కార్యక్రమం, GLuint సూచీ, GLsizei buf_కొలత, GLsizei *నిడివి, GLint *కొలత, GLenum *type, GLchar *name);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETATTACHEDSHADERSPROC) (GLuint కార్యక్రమం, GLsizei max_లెక్క, GLsizei *లెక్క, GLuint *shaders);
రకనిర్వచనం GLint (GL_APIENTRYP PFNGLGETATTRIBLOCATIONPROC) (GLuint కార్యక్రమం, స్థిరరాశి GLchar *name);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETBOOLEANVPROC) (GLenum pname, GLboolean *దత్తాంశం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETBUFFERPARAMETERIVPROC) (GLenum లక్ష్యం, GLenum pname, GLint *params);
రకనిర్వచనం GLenum (GL_APIENTRYP PFNGLGETERRORPROC) (శూన్య);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETFLOATVPROC) (GLenum pname, GLfloat *దత్తాంశం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) (GLenum లక్ష్యం, GLenum attachment, GLenum pname, GLint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETINTEGERVPROC) (GLenum pname, GLint *దత్తాంశం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETPROGRAMIVPROC) (GLuint కార్యక్రమం, GLenum pname, GLint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETPROGRAMINFOLOGPROC) (GLuint కార్యక్రమం, GLsizei buf_కొలత, GLsizei *నిడివి, GLchar *infoLog);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVPROC) (GLenum లక్ష్యం, GLenum pname, GLint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei buf_కొలత, GLsizei *నిడివి, GLchar *infoLog);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETSHADERPRECISIONFORMATPROC) (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETSHADERSOURCEPROC) (GLuint shader, GLsizei buf_కొలత, GLsizei *నిడివి, GLchar *ఆధారం);
రకనిర్వచనం స్థిరరాశి GLubyte *(GL_APIENTRYP PFNGLGETSTRINGPROC) (GLenum name);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETTEXPARAMETERFVPROC) (GLenum లక్ష్యం, GLenum pname, GLfloat *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETTEXPARAMETERIVPROC) (GLenum లక్ష్యం, GLenum pname, GLint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETUNIFORMFVPROC) (GLuint కార్యక్రమం, GLint location, GLfloat *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETUNIFORMIVPROC) (GLuint కార్యక్రమం, GLint location, GLint *params);
రకనిర్వచనం GLint (GL_APIENTRYP PFNGLGETUNIFORMLOCATIONPROC) (GLuint కార్యక్రమం, స్థిరరాశి GLchar *name);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETVERTEXATTRIBFVPROC) (GLuint సూచీ, GLenum pname, GLfloat *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETVERTEXATTRIBIVPROC) (GLuint సూచీ, GLenum pname, GLint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETVERTEXATTRIBPOINTERVPROC) (GLuint సూచీ, GLenum pname, శూన్య **సూచిక_2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLHINTPROC) (GLenum లక్ష్యం, GLenum బహుళకం);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLISBUFFERPROC) (GLuint బఫరు_2);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLISENABLEDPROC) (GLenum cap);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLISFRAMEBUFFERPROC) (GLuint framebuffer);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLISPROGRAMPROC) (GLuint కార్యక్రమం);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLISRENDERBUFFERPROC) (GLuint renderbuffer);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLISSHADERPROC) (GLuint shader);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLISTEXTUREPROC) (GLuint texture);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLLINEWIDTHPROC) (GLfloat వెడల్పు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLLINKPROGRAMPROC) (GLuint కార్యక్రమం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPIXELSTOREIPROC) (GLenum pname, GLint param);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPOLYGONOFFSETPROC) (GLfloat గుణకం, GLfloat units);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLREADPIXELSPROC) (GLint x, GLint y, GLsizei వెడల్పు, GLsizei ఎత్తు, GLenum format, GLenum type, శూన్య *pixels);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLRELEASESHADERCOMPILERPROC) (శూన్య);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEPROC) (GLenum లక్ష్యం, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSAMPLECOVERAGEPROC) (GLfloat విలువ, GLboolean invert);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSCISSORPROC) (GLint x, GLint y, GLsizei వెడల్పు, GLsizei ఎత్తు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSHADERBINARYPROC) (GLsizei లెక్క, స్థిరరాశి GLuint *shaders, GLenum ద్విమాన_Format, స్థిరరాశి శూన్య *ద్విమాన, GLsizei నిడివి);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei లెక్క, స్థిరరాశి GLchar *స్థిరరాశి*string, స్థిరరాశి GLint *నిడివి);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSTENCILFUNCPROC) (GLenum func, GLint ref, GLuint ముసుగు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSTENCILFUNCSEPARATEPROC) (GLenum face, GLenum func, GLint ref, GLuint ముసుగు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSTENCILMASKPROC) (GLuint ముసుగు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSTENCILMASKSEPARATEPROC) (GLenum face, GLuint ముసుగు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSTENCILOPPROC) (GLenum fail, GLenum zfail, GLenum zpass);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSTENCILOPSEPARATEPROC) (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXIMAGE2DPROC) (GLenum లక్ష్యం, GLint level, GLint internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు, GLint border, GLenum format, GLenum type, స్థిరరాశి శూన్య *pixels);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXPARAMETERFPROC) (GLenum లక్ష్యం, GLenum pname, GLfloat param);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXPARAMETERFVPROC) (GLenum లక్ష్యం, GLenum pname, స్థిరరాశి GLfloat *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXPARAMETERIPROC) (GLenum లక్ష్యం, GLenum pname, GLint param);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXPARAMETERIVPROC) (GLenum లక్ష్యం, GLenum pname, స్థిరరాశి GLint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXSUBIMAGE2DPROC) (GLenum లక్ష్యం, GLint level, GLint xoffset, GLint yoffset, GLsizei వెడల్పు, GLsizei ఎత్తు, GLenum format, GLenum type, స్థిరరాశి శూన్య *pixels);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM1FPROC) (GLint location, GLfloat v0);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM1FVPROC) (GLint location, GLsizei లెక్క, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM1IPROC) (GLint location, GLint v0);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM1IVPROC) (GLint location, GLsizei లెక్క, స్థిరరాశి GLint *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM2FPROC) (GLint location, GLfloat v0, GLfloat v1);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM2FVPROC) (GLint location, GLsizei లెక్క, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM2IPROC) (GLint location, GLint v0, GLint v1);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM2IVPROC) (GLint location, GLsizei లెక్క, స్థిరరాశి GLint *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM3FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM3FVPROC) (GLint location, GLsizei లెక్క, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM3IPROC) (GLint location, GLint v0, GLint v1, GLint v2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM3IVPROC) (GLint location, GLsizei లెక్క, స్థిరరాశి GLint *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM4FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM4FVPROC) (GLint location, GLsizei లెక్క, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM4IPROC) (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM4IVPROC) (GLint location, GLsizei లెక్క, స్థిరరాశి GLint *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORMMATRIX2FVPROC) (GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORMMATRIX3FVPROC) (GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUSEPROGRAMPROC) (GLuint కార్యక్రమం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLVALIDATEPROGRAMPROC) (GLuint కార్యక్రమం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLVERTEXATTRIB1FPROC) (GLuint సూచీ, GLfloat x);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLVERTEXATTRIB1FVPROC) (GLuint సూచీ, స్థిరరాశి GLfloat *v);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLVERTEXATTRIB2FPROC) (GLuint సూచీ, GLfloat x, GLfloat y);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLVERTEXATTRIB2FVPROC) (GLuint సూచీ, స్థిరరాశి GLfloat *v);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLVERTEXATTRIB3FPROC) (GLuint సూచీ, GLfloat x, GLfloat y, GLfloat z);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLVERTEXATTRIB3FVPROC) (GLuint సూచీ, స్థిరరాశి GLfloat *v);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLVERTEXATTRIB4FPROC) (GLuint సూచీ, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLVERTEXATTRIB4FVPROC) (GLuint సూచీ, స్థిరరాశి GLfloat *v);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC) (GLuint సూచీ, GLint కొలత, GLenum type, GLboolean normalized, GLsizei stride, స్థిరరాశి శూన్య *సూచిక_2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLVIEWPORTPROC) (GLint x, GLint y, GLsizei వెడల్పు, GLsizei ఎత్తు);
#ఒకవేళ GL_GLES_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_చురుకైన_Texture (GLenum texture);
GL_APICALL శూన్య GL_APIENTRY glAttachShader (GLuint కార్యక్రమం, GLuint shader);
GL_APICALL శూన్య GL_APIENTRY glBindAttribLocation (GLuint కార్యక్రమం, GLuint సూచీ, స్థిరరాశి GLchar *name);
GL_APICALL శూన్య GL_APIENTRY gl_Bind_బఫరు (GLenum లక్ష్యం, GLuint బఫరు_2);
GL_APICALL శూన్య GL_APIENTRY glBindFramebuffer (GLenum లక్ష్యం, GLuint framebuffer);
GL_APICALL శూన్య GL_APIENTRY glBindRenderbuffer (GLenum లక్ష్యం, GLuint renderbuffer);
GL_APICALL శూన్య GL_APIENTRY glBindTexture (GLenum లక్ష్యం, GLuint texture);
GL_APICALL శూన్య GL_APIENTRY glBlendColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_APICALL శూన్య GL_APIENTRY glBlendEquation (GLenum బహుళకం);
GL_APICALL శూన్య GL_APIENTRY glBlendEquationSeparate (GLenum బహుళకం_RGB, GLenum బహుళకం_Alpha);
GL_APICALL శూన్య GL_APIENTRY glBlendFunc (GLenum sfactor, GLenum dfactor);
GL_APICALL శూన్య GL_APIENTRY glBlendFuncSeparate (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
GL_APICALL శూన్య GL_APIENTRY gl_బఫరు_దత్తాంశం (GLenum లక్ష్యం, GLsizeiptr కొలత, స్థిరరాశి శూన్య *దత్తాంశం, GLenum usage);
GL_APICALL శూన్య GL_APIENTRY gl_బఫరు_Sub_దత్తాంశం (GLenum లక్ష్యం, GLintptr స్థానభ్రంశం_2, GLsizeiptr కొలత, స్థిరరాశి శూన్య *దత్తాంశం);
GL_APICALL GLenum GL_APIENTRY gl_Check_Framebuffer_స్థితి (GLenum లక్ష్యం);
GL_APICALL శూన్య GL_APIENTRY glClear (GLbitfield ముసుగు);
GL_APICALL శూన్య GL_APIENTRY glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_APICALL శూన్య GL_APIENTRY glClearDepthf (GLfloat d);
GL_APICALL శూన్య GL_APIENTRY glClearStencil (GLint s);
GL_APICALL శూన్య GL_APIENTRY gl_Color_ముసుగు (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
GL_APICALL శూన్య GL_APIENTRY glCompileShader (GLuint shader);
GL_APICALL శూన్య GL_APIENTRY glCompressedTexImage2D (GLenum లక్ష్యం, GLint level, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు, GLint border, GLsizei image_కొలత, స్థిరరాశి శూన్య *దత్తాంశం);
GL_APICALL శూన్య GL_APIENTRY glCompressedTexSubImage2D (GLenum లక్ష్యం, GLint level, GLint xoffset, GLint yoffset, GLsizei వెడల్పు, GLsizei ఎత్తు, GLenum format, GLsizei image_కొలత, స్థిరరాశి శూన్య *దత్తాంశం);
GL_APICALL శూన్య GL_APIENTRY glCopyTexImage2D (GLenum లక్ష్యం, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei వెడల్పు, GLsizei ఎత్తు, GLint border);
GL_APICALL శూన్య GL_APIENTRY glCopyTexSubImage2D (GLenum లక్ష్యం, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei వెడల్పు, GLsizei ఎత్తు);
GL_APICALL GLuint GL_APIENTRY gl_Create_కార్యక్రమం (శూన్య);
GL_APICALL GLuint GL_APIENTRY glCreateShader (GLenum type);
GL_APICALL శూన్య GL_APIENTRY glCullFace (GLenum బహుళకం);
GL_APICALL శూన్య GL_APIENTRY glDeleteBuffers (GLsizei n, స్థిరరాశి GLuint *buffers);
GL_APICALL శూన్య GL_APIENTRY glDeleteFramebuffers (GLsizei n, స్థిరరాశి GLuint *framebuffers);
GL_APICALL శూన్య GL_APIENTRY gl_Delete_కార్యక్రమం (GLuint కార్యక్రమం);
GL_APICALL శూన్య GL_APIENTRY glDeleteRenderbuffers (GLsizei n, స్థిరరాశి GLuint *renderbuffers);
GL_APICALL శూన్య GL_APIENTRY glDeleteShader (GLuint shader);
GL_APICALL శూన్య GL_APIENTRY glDeleteTextures (GLsizei n, స్థిరరాశి GLuint *textures);
GL_APICALL శూన్య GL_APIENTRY gl_లోతు_Func (GLenum func);
GL_APICALL శూన్య GL_APIENTRY gl_లోతు_ముసుగు (GLboolean flag);
GL_APICALL శూన్య GL_APIENTRY gl_లోతు_Rangef (GLfloat n, GLfloat f);
GL_APICALL శూన్య GL_APIENTRY glDetachShader (GLuint కార్యక్రమం, GLuint shader);
GL_APICALL శూన్య GL_APIENTRY glDisable (GLenum cap);
GL_APICALL శూన్య GL_APIENTRY gl_Disable_శీర్షం_Attrib_Array (GLuint సూచీ);
GL_APICALL శూన్య GL_APIENTRY glDrawArrays (GLenum బహుళకం, GLint మొదటి, GLsizei లెక్క);
GL_APICALL శూన్య GL_APIENTRY glDrawElements (GLenum బహుళకం, GLsizei లెక్క, GLenum type, స్థిరరాశి శూన్య *indices);
GL_APICALL శూన్య GL_APIENTRY glEnable (GLenum cap);
GL_APICALL శూన్య GL_APIENTRY gl_Enable_శీర్షం_Attrib_Array (GLuint సూచీ);
GL_APICALL శూన్య GL_APIENTRY gl_ముగింపు (శూన్య);
GL_APICALL శూన్య GL_APIENTRY glFlush (శూన్య);
GL_APICALL శూన్య GL_APIENTRY glFramebufferRenderbuffer (GLenum లక్ష్యం, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
GL_APICALL శూన్య GL_APIENTRY glFramebufferTexture2D (GLenum లక్ష్యం, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GL_APICALL శూన్య GL_APIENTRY glFrontFace (GLenum బహుళకం);
GL_APICALL శూన్య GL_APIENTRY glGenBuffers (GLsizei n, GLuint *buffers);
GL_APICALL శూన్య GL_APIENTRY glGenerateMipmap (GLenum లక్ష్యం);
GL_APICALL శూన్య GL_APIENTRY glGenFramebuffers (GLsizei n, GLuint *framebuffers);
GL_APICALL శూన్య GL_APIENTRY glGenRenderbuffers (GLsizei n, GLuint *renderbuffers);
GL_APICALL శూన్య GL_APIENTRY glGenTextures (GLsizei n, GLuint *textures);
GL_APICALL శూన్య GL_APIENTRY gl_Get_చురుకైన_Attrib (GLuint కార్యక్రమం, GLuint సూచీ, GLsizei buf_కొలత, GLsizei *నిడివి, GLint *కొలత, GLenum *type, GLchar *name);
GL_APICALL శూన్య GL_APIENTRY gl_Get_చురుకైన_ఏకరీతి (GLuint కార్యక్రమం, GLuint సూచీ, GLsizei buf_కొలత, GLsizei *నిడివి, GLint *కొలత, GLenum *type, GLchar *name);
GL_APICALL శూన్య GL_APIENTRY glGetAttachedShaders (GLuint కార్యక్రమం, GLsizei max_లెక్క, GLsizei *లెక్క, GLuint *shaders);
GL_APICALL GLint GL_APIENTRY glGetAttribLocation (GLuint కార్యక్రమం, స్థిరరాశి GLchar *name);
GL_APICALL శూన్య GL_APIENTRY glGetBooleanv (GLenum pname, GLboolean *దత్తాంశం);
GL_APICALL శూన్య GL_APIENTRY gl_Get_బఫరు_Parameteriv (GLenum లక్ష్యం, GLenum pname, GLint *params);
GL_APICALL GLenum GL_APIENTRY glGetError (శూన్య);
GL_APICALL శూన్య GL_APIENTRY glGetFloatv (GLenum pname, GLfloat *దత్తాంశం);
GL_APICALL శూన్య GL_APIENTRY glGetFramebufferAttachmentParameteriv (GLenum లక్ష్యం, GLenum attachment, GLenum pname, GLint *params);
GL_APICALL శూన్య GL_APIENTRY glGetIntegerv (GLenum pname, GLint *దత్తాంశం);
GL_APICALL శూన్య GL_APIENTRY glGetProgramiv (GLuint కార్యక్రమం, GLenum pname, GLint *params);
GL_APICALL శూన్య GL_APIENTRY gl_Get_కార్యక్రమం_Info_Log (GLuint కార్యక్రమం, GLsizei buf_కొలత, GLsizei *నిడివి, GLchar *infoLog);
GL_APICALL శూన్య GL_APIENTRY glGetRenderbufferParameteriv (GLenum లక్ష్యం, GLenum pname, GLint *params);
GL_APICALL శూన్య GL_APIENTRY glGetShaderiv (GLuint shader, GLenum pname, GLint *params);
GL_APICALL శూన్య GL_APIENTRY glGetShaderInfoLog (GLuint shader, GLsizei buf_కొలత, GLsizei *నిడివి, GLchar *infoLog);
GL_APICALL శూన్య GL_APIENTRY glGetShaderPrecisionFormat (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
GL_APICALL శూన్య GL_APIENTRY gl_Get_Shader_ఆధారం (GLuint shader, GLsizei buf_కొలత, GLsizei *నిడివి, GLchar *ఆధారం);
GL_APICALL స్థిరరాశి GLubyte *GL_APIENTRY glGetString (GLenum name);
GL_APICALL శూన్య GL_APIENTRY glGetTexParameterfv (GLenum లక్ష్యం, GLenum pname, GLfloat *params);
GL_APICALL శూన్య GL_APIENTRY glGetTexParameteriv (GLenum లక్ష్యం, GLenum pname, GLint *params);
GL_APICALL శూన్య GL_APIENTRY glGetUniformfv (GLuint కార్యక్రమం, GLint location, GLfloat *params);
GL_APICALL శూన్య GL_APIENTRY glGetUniformiv (GLuint కార్యక్రమం, GLint location, GLint *params);
GL_APICALL GLint GL_APIENTRY gl_Get_ఏకరీతి_Location (GLuint కార్యక్రమం, స్థిరరాశి GLchar *name);
GL_APICALL శూన్య GL_APIENTRY gl_Get_శీర్షం_Attribfv (GLuint సూచీ, GLenum pname, GLfloat *params);
GL_APICALL శూన్య GL_APIENTRY gl_Get_శీర్షం_Attribiv (GLuint సూచీ, GLenum pname, GLint *params);
GL_APICALL శూన్య GL_APIENTRY gl_Get_శీర్షం_Attrib_Pointerv (GLuint సూచీ, GLenum pname, శూన్య **సూచిక_2);
GL_APICALL శూన్య GL_APIENTRY glHint (GLenum లక్ష్యం, GLenum బహుళకం);
GL_APICALL GLboolean GL_APIENTRY gl_Is_బఫరు (GLuint బఫరు_2);
GL_APICALL GLboolean GL_APIENTRY glIsEnabled (GLenum cap);
GL_APICALL GLboolean GL_APIENTRY glIsFramebuffer (GLuint framebuffer);
GL_APICALL GLboolean GL_APIENTRY gl_Is_కార్యక్రమం (GLuint కార్యక్రమం);
GL_APICALL GLboolean GL_APIENTRY glIsRenderbuffer (GLuint renderbuffer);
GL_APICALL GLboolean GL_APIENTRY glIsShader (GLuint shader);
GL_APICALL GLboolean GL_APIENTRY glIsTexture (GLuint texture);
GL_APICALL శూన్య GL_APIENTRY gl_పంక్తి_వెడల్పు (GLfloat వెడల్పు);
GL_APICALL శూన్య GL_APIENTRY gl_Link_కార్యక్రమం (GLuint కార్యక్రమం);
GL_APICALL శూన్య GL_APIENTRY glPixelStorei (GLenum pname, GLint param);
GL_APICALL శూన్య GL_APIENTRY gl_Polygon_స్థానభ్రంశం (GLfloat గుణకం, GLfloat units);
GL_APICALL శూన్య GL_APIENTRY glReadPixels (GLint x, GLint y, GLsizei వెడల్పు, GLsizei ఎత్తు, GLenum format, GLenum type, శూన్య *pixels);
GL_APICALL శూన్య GL_APIENTRY glReleaseShaderCompiler (శూన్య);
GL_APICALL శూన్య GL_APIENTRY glRenderbufferStorage (GLenum లక్ష్యం, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
GL_APICALL శూన్య GL_APIENTRY glSampleCoverage (GLfloat విలువ, GLboolean invert);
GL_APICALL శూన్య GL_APIENTRY glScissor (GLint x, GLint y, GLsizei వెడల్పు, GLsizei ఎత్తు);
GL_APICALL శూన్య GL_APIENTRY gl_Shader_ద్విమాన (GLsizei లెక్క, స్థిరరాశి GLuint *shaders, GLenum ద్విమాన_Format, స్థిరరాశి శూన్య *ద్విమాన, GLsizei నిడివి);
GL_APICALL శూన్య GL_APIENTRY gl_Shader_ఆధారం (GLuint shader, GLsizei లెక్క, స్థిరరాశి GLchar *స్థిరరాశి*string, స్థిరరాశి GLint *నిడివి);
GL_APICALL శూన్య GL_APIENTRY glStencilFunc (GLenum func, GLint ref, GLuint ముసుగు);
GL_APICALL శూన్య GL_APIENTRY glStencilFuncSeparate (GLenum face, GLenum func, GLint ref, GLuint ముసుగు);
GL_APICALL శూన్య GL_APIENTRY gl_Stencil_ముసుగు (GLuint ముసుగు);
GL_APICALL శూన్య GL_APIENTRY gl_Stencil_ముసుగు_Separate (GLenum face, GLuint ముసుగు);
GL_APICALL శూన్య GL_APIENTRY glStencilOp (GLenum fail, GLenum zfail, GLenum zpass);
GL_APICALL శూన్య GL_APIENTRY glStencilOpSeparate (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
GL_APICALL శూన్య GL_APIENTRY glTexImage2D (GLenum లక్ష్యం, GLint level, GLint internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు, GLint border, GLenum format, GLenum type, స్థిరరాశి శూన్య *pixels);
GL_APICALL శూన్య GL_APIENTRY glTexParameterf (GLenum లక్ష్యం, GLenum pname, GLfloat param);
GL_APICALL శూన్య GL_APIENTRY glTexParameterfv (GLenum లక్ష్యం, GLenum pname, స్థిరరాశి GLfloat *params);
GL_APICALL శూన్య GL_APIENTRY glTexParameteri (GLenum లక్ష్యం, GLenum pname, GLint param);
GL_APICALL శూన్య GL_APIENTRY glTexParameteriv (GLenum లక్ష్యం, GLenum pname, స్థిరరాశి GLint *params);
GL_APICALL శూన్య GL_APIENTRY glTexSubImage2D (GLenum లక్ష్యం, GLint level, GLint xoffset, GLint yoffset, GLsizei వెడల్పు, GLsizei ఎత్తు, GLenum format, GLenum type, స్థిరరాశి శూన్య *pixels);
GL_APICALL శూన్య GL_APIENTRY glUniform1f (GLint location, GLfloat v0);
GL_APICALL శూన్య GL_APIENTRY glUniform1fv (GLint location, GLsizei లెక్క, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY glUniform1i (GLint location, GLint v0);
GL_APICALL శూన్య GL_APIENTRY glUniform1iv (GLint location, GLsizei లెక్క, స్థిరరాశి GLint *విలువ);
GL_APICALL శూన్య GL_APIENTRY glUniform2f (GLint location, GLfloat v0, GLfloat v1);
GL_APICALL శూన్య GL_APIENTRY glUniform2fv (GLint location, GLsizei లెక్క, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY glUniform2i (GLint location, GLint v0, GLint v1);
GL_APICALL శూన్య GL_APIENTRY glUniform2iv (GLint location, GLsizei లెక్క, స్థిరరాశి GLint *విలువ);
GL_APICALL శూన్య GL_APIENTRY glUniform3f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
GL_APICALL శూన్య GL_APIENTRY glUniform3fv (GLint location, GLsizei లెక్క, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY glUniform3i (GLint location, GLint v0, GLint v1, GLint v2);
GL_APICALL శూన్య GL_APIENTRY glUniform3iv (GLint location, GLsizei లెక్క, స్థిరరాశి GLint *విలువ);
GL_APICALL శూన్య GL_APIENTRY glUniform4f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
GL_APICALL శూన్య GL_APIENTRY glUniform4fv (GLint location, GLsizei లెక్క, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY glUniform4i (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
GL_APICALL శూన్య GL_APIENTRY glUniform4iv (GLint location, GLsizei లెక్క, స్థిరరాశి GLint *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_ఏకరీతి_Matrix2fv (GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_ఏకరీతి_Matrix3fv (GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_ఏకరీతి_Matrix4fv (GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_Use_కార్యక్రమం (GLuint కార్యక్రమం);
GL_APICALL శూన్య GL_APIENTRY gl_Validate_కార్యక్రమం (GLuint కార్యక్రమం);
GL_APICALL శూన్య GL_APIENTRY gl_శీర్షం_Attrib1f (GLuint సూచీ, GLfloat x);
GL_APICALL శూన్య GL_APIENTRY gl_శీర్షం_Attrib1fv (GLuint సూచీ, స్థిరరాశి GLfloat *v);
GL_APICALL శూన్య GL_APIENTRY gl_శీర్షం_Attrib2f (GLuint సూచీ, GLfloat x, GLfloat y);
GL_APICALL శూన్య GL_APIENTRY gl_శీర్షం_Attrib2fv (GLuint సూచీ, స్థిరరాశి GLfloat *v);
GL_APICALL శూన్య GL_APIENTRY gl_శీర్షం_Attrib3f (GLuint సూచీ, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL శూన్య GL_APIENTRY gl_శీర్షం_Attrib3fv (GLuint సూచీ, స్థిరరాశి GLfloat *v);
GL_APICALL శూన్య GL_APIENTRY gl_శీర్షం_Attrib4f (GLuint సూచీ, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
GL_APICALL శూన్య GL_APIENTRY gl_శీర్షం_Attrib4fv (GLuint సూచీ, స్థిరరాశి GLfloat *v);
GL_APICALL శూన్య GL_APIENTRY gl_శీర్షం_Attrib_సూచిక (GLuint సూచీ, GLint కొలత, GLenum type, GLboolean normalized, GLsizei stride, స్థిరరాశి శూన్య *సూచిక_2);
GL_APICALL శూన్య GL_APIENTRY glViewport (GLint x, GLint y, GLsizei వెడల్పు, GLsizei ఎత్తు);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_ES_VERSION_2_0 */

#నిర్వచితం_కాకపోతే GL_ES_సంస్కరణ_3_0
#నిర్వచించు GL_ES_సంస్కరణ_3_0 1
రకనిర్వచనం khronos_uint16_t GLhalf;
#నిర్వచించు GL_READ_బఫరు                    0x0C02
#నిర్వచించు GL_UNPACK_అడ్డువరుస_నిడివి              0x0CF2
#నిర్వచించు GL_UNPACK_SKIP_అడ్డువరుసలు               0x0CF3
#నిర్వచించు GL_UNPACK_SKIP_PIXELS             0x0CF4
#నిర్వచించు GL_PACK_అడ్డువరుస_నిడివి                0x0D02
#నిర్వచించు GL_PACK_SKIP_అడ్డువరుసలు                 0x0D03
#నిర్వచించు GL_PACK_SKIP_PIXELS               0x0D04
#నిర్వచించు GL_COLOR                          0x1800
#నిర్వచించు GL_లోతు                          0x1801
#నిర్వచించు GL_STENCIL                        0x1802
#నిర్వచించు GL_RED                            0x1903
#నిర్వచించు GL_RGB8                           0x8051
#నిర్వచించు GL_RGBA8                          0x8058
#నిర్వచించు GL_RGB10_A2                       0x8059
#నిర్వచించు GL_TEXTURE_BINDING_3D             0x806A
#నిర్వచించు GL_UNPACK_SKIP_IMAGES             0x806D
#నిర్వచించు GL_UNPACK_IMAGE_ఎత్తు            0x806E
#నిర్వచించు GL_TEXTURE_3D                     0x806F
#నిర్వచించు GL_TEXTURE_WRAP_R                 0x8072
#నిర్వచించు GL_MAX_3_D_TEXTURE_కొలత            0x8073
#నిర్వచించు GL_UNSIGNED_INT_2_10_10_10_REV    0x8368
#నిర్వచించు GL_MAX_ELEMENTS_VERTICES          0x80E8
#నిర్వచించు GL_MAX_ELEMENTS_INDICES           0x80E9
#నిర్వచించు GL_TEXTURE_MIN_LOD                0x813A
#నిర్వచించు GL_TEXTURE_MAX_LOD                0x813B
#నిర్వచించు GL_TEXTURE_పునాది_LEVEL             0x813C
#నిర్వచించు GL_TEXTURE_MAX_LEVEL              0x813D
#నిర్వచించు GL_MIN                            0x8007
#నిర్వచించు GL_MAX                            0x8008
#నిర్వచించు GL_లోతు_COMPONENT24              0x81A6
#నిర్వచించు GL_MAX_TEXTURE_LOD_BIAS           0x84FD
#నిర్వచించు GL_TEXTURE_COMPARE_బహుళకం           0x884C
#నిర్వచించు GL_TEXTURE_COMPARE_FUNC           0x884D
#నిర్వచించు GL_CURRENT_QUERY                  0x8865
#నిర్వచించు GL_QUERY_ఫలితం                   0x8866
#నిర్వచించు GL_QUERY_ఫలితం_అందుబాటు         0x8867
#నిర్వచించు GL_బఫరు_MAPPED                  0x88BC
#నిర్వచించు GL_బఫరు_MAP_సూచిక             0x88BD
#నిర్వచించు GL_ప్రవాహం_READ                    0x88E1
#నిర్వచించు GL_ప్రవాహం_COPY                    0x88E2
#నిర్వచించు GL_STATIC_READ                    0x88E5
#నిర్వచించు GL_STATIC_COPY                    0x88E6
#నిర్వచించు GL_DYNAMIC_READ                   0x88E9
#నిర్వచించు GL_DYNAMIC_COPY                   0x88EA
#నిర్వచించు GL_MAX_DRAW_BUFFERS               0x8824
#నిర్వచించు GL_DRAW_BUFFER0                   0x8825
#నిర్వచించు GL_DRAW_BUFFER1                   0x8826
#నిర్వచించు GL_DRAW_BUFFER2                   0x8827
#నిర్వచించు GL_DRAW_BUFFER3                   0x8828
#నిర్వచించు GL_DRAW_BUFFER4                   0x8829
#నిర్వచించు GL_DRAW_BUFFER5                   0x882A
#నిర్వచించు GL_DRAW_BUFFER6                   0x882B
#నిర్వచించు GL_DRAW_BUFFER7                   0x882C
#నిర్వచించు GL_DRAW_BUFFER8                   0x882D
#నిర్వచించు GL_DRAW_BUFFER9                   0x882E
#నిర్వచించు GL_DRAW_BUFFER10                  0x882F
#నిర్వచించు GL_DRAW_BUFFER11                  0x8830
#నిర్వచించు GL_DRAW_BUFFER12                  0x8831
#నిర్వచించు GL_DRAW_BUFFER13                  0x8832
#నిర్వచించు GL_DRAW_BUFFER14                  0x8833
#నిర్వచించు GL_DRAW_BUFFER15                  0x8834
#నిర్వచించు GL_MAX_FRAGMENT_ఏకరీతి_COMPONENTS 0x8B49
#నిర్వచించు GL_MAX_శీర్షం_ఏకరీతి_COMPONENTS  0x8B4A
#నిర్వచించు GL_SAMPLER_3D                     0x8B5F
#నిర్వచించు GL_SAMPLER_2D_SHADOW              0x8B62
#నిర్వచించు GL_FRAGMENT_SHADER_DERIVATIVE_HINT 0x8B8B
#నిర్వచించు GL_PIXEL_PACK_బఫరు              0x88EB
#నిర్వచించు GL_PIXEL_UNPACK_బఫరు            0x88EC
#నిర్వచించు GL_PIXEL_PACK_బఫరు_BINDING      0x88ED
#నిర్వచించు GL_PIXEL_UNPACK_బఫరు_BINDING    0x88EF
#నిర్వచించు GL_FLOAT_MAT2x3                   0x8B65
#నిర్వచించు GL_FLOAT_MAT2x4                   0x8B66
#నిర్వచించు GL_FLOAT_MAT3x2                   0x8B67
#నిర్వచించు GL_FLOAT_MAT3x4                   0x8B68
#నిర్వచించు GL_FLOAT_MAT4x2                   0x8B69
#నిర్వచించు GL_FLOAT_MAT4x3                   0x8B6A
#నిర్వచించు GL_SRGB                           0x8C40
#నిర్వచించు GL_SRGB8                          0x8C41
#నిర్వచించు GL_SRGB8_ALPHA8                   0x8C43
#నిర్వచించు GL_COMPARE_REF_గమ్యం_TEXTURE         0x884E
#నిర్వచించు GL_MAJOR_సంస్కరణ                  0x821B
#నిర్వచించు GL_MINOR_సంస్కరణ                  0x821C
#నిర్వచించు GL_అంకె_EXTENSIONS                 0x821D
#నిర్వచించు GL_RGBA32F                        0x8814
#నిర్వచించు GL_RGB32F                         0x8815
#నిర్వచించు GL_RGBA16F                        0x881A
#నిర్వచించు GL_RGB16F                         0x881B
#నిర్వచించు GL_శీర్షం_ATTRIB_ARRAY_INTEGER    0x88FD
#నిర్వచించు GL_MAX_ARRAY_TEXTURE_LAYERS       0x88FF
#నిర్వచించు GL_MIN_కార్యక్రమం_TEXEL_స్థానభ్రంశం       0x8904
#నిర్వచించు GL_MAX_కార్యక్రమం_TEXEL_స్థానభ్రంశం       0x8905
#నిర్వచించు GL_MAX_VARYING_COMPONENTS         0x8B4B
#నిర్వచించు GL_TEXTURE_2D_ARRAY               0x8C1A
#నిర్వచించు GL_TEXTURE_BINDING_2D_ARRAY       0x8C1D
#నిర్వచించు GL_R11F_G11F_B10F                 0x8C3A
#నిర్వచించు GL_UNSIGNED_INT_10F_11F_11F_REV   0x8C3B
#నిర్వచించు GL_RGB9_E5                        0x8C3D
#నిర్వచించు GL_UNSIGNED_INT_5_9_9_9_REV       0x8C3E
#నిర్వచించు GL_TRANSFORM_FEEDBACK_VARYING_MAX_నిడివి 0x8C76
#నిర్వచించు GL_TRANSFORM_FEEDBACK_బఫరు_బహుళకం 0x8C7F
#నిర్వచించు GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS 0x8C80
#నిర్వచించు GL_TRANSFORM_FEEDBACK_VARYINGS    0x8C83
#నిర్వచించు GL_TRANSFORM_FEEDBACK_బఫరు_ప్రారంభం 0x8C84
#నిర్వచించు GL_TRANSFORM_FEEDBACK_బఫరు_కొలత 0x8C85
#నిర్వచించు GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN 0x8C88
#నిర్వచించు GL_RASTERIZER_DISCARD             0x8C89
#నిర్వచించు GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS 0x8C8A
#నిర్వచించు GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS 0x8C8B
#నిర్వచించు GL_INTERLEAVED_ATTRIBS            0x8C8C
#నిర్వచించు GL_SEPARATE_ATTRIBS               0x8C8D
#నిర్వచించు GL_TRANSFORM_FEEDBACK_బఫరు      0x8C8E
#నిర్వచించు GL_TRANSFORM_FEEDBACK_బఫరు_BINDING 0x8C8F
#నిర్వచించు GL_RGBA32UI                       0x8D70
#నిర్వచించు GL_RGB32UI                        0x8D71
#నిర్వచించు GL_RGBA16UI                       0x8D76
#నిర్వచించు GL_RGB16UI                        0x8D77
#నిర్వచించు GL_RGBA8UI                        0x8D7C
#నిర్వచించు GL_RGB8UI                         0x8D7D
#నిర్వచించు GL_RGBA32I                        0x8D82
#నిర్వచించు GL_RGB32I                         0x8D83
#నిర్వచించు GL_RGBA16I                        0x8D88
#నిర్వచించు GL_RGB16I                         0x8D89
#నిర్వచించు GL_RGBA8I                         0x8D8E
#నిర్వచించు GL_RGB8I                          0x8D8F
#నిర్వచించు GL_RED_INTEGER                    0x8D94
#నిర్వచించు GL_RGB_INTEGER                    0x8D98
#నిర్వచించు GL_RGBA_INTEGER                   0x8D99
#నిర్వచించు GL_SAMPLER_2D_ARRAY               0x8DC1
#నిర్వచించు GL_SAMPLER_2D_ARRAY_SHADOW        0x8DC4
#నిర్వచించు GL_SAMPLER_CUBE_SHADOW            0x8DC5
#నిర్వచించు GL_UNSIGNED_INT_VEC2              0x8DC6
#నిర్వచించు GL_UNSIGNED_INT_VEC3              0x8DC7
#నిర్వచించు GL_UNSIGNED_INT_VEC4              0x8DC8
#నిర్వచించు GL_INT_SAMPLER_2D                 0x8DCA
#నిర్వచించు GL_INT_SAMPLER_3D                 0x8DCB
#నిర్వచించు GL_INT_SAMPLER_CUBE               0x8DCC
#నిర్వచించు GL_INT_SAMPLER_2D_ARRAY           0x8DCF
#నిర్వచించు GL_UNSIGNED_INT_SAMPLER_2D        0x8DD2
#నిర్వచించు GL_UNSIGNED_INT_SAMPLER_3D        0x8DD3
#నిర్వచించు GL_UNSIGNED_INT_SAMPLER_CUBE      0x8DD4
#నిర్వచించు GL_UNSIGNED_INT_SAMPLER_2D_ARRAY  0x8DD7
#నిర్వచించు GL_బఫరు_ACCESS_FLAGS            0x911F
#నిర్వచించు GL_బఫరు_MAP_నిడివి              0x9120
#నిర్వచించు GL_బఫరు_MAP_స్థానభ్రంశం              0x9121
#నిర్వచించు GL_లోతు_COMPONENT32_F             0x8CAC
#నిర్వచించు GL_DEPTH32F_STENCIL8              0x8CAD
#నిర్వచించు GL_FLOAT_32_UNSIGNED_INT_24_8_REV 0x8DAD
#నిర్వచించు GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING 0x8210
#నిర్వచించు GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE 0x8211
#నిర్వచించు GL_FRAMEBUFFER_ATTACHMENT_RED_కొలత 0x8212
#నిర్వచించు GL_FRAMEBUFFER_ATTACHMENT_GREEN_కొలత 0x8213
#నిర్వచించు GL_FRAMEBUFFER_ATTACHMENT_BLUE_కొలత 0x8214
#నిర్వచించు GL_FRAMEBUFFER_ATTACHMENT_ALPHA_కొలత 0x8215
#నిర్వచించు GL_FRAMEBUFFER_ATTACHMENT_లోతు_కొలత 0x8216
#నిర్వచించు GL_FRAMEBUFFER_ATTACHMENT_STENCIL_కొలత 0x8217
#నిర్వచించు GL_FRAMEBUFFER_DEFAULT            0x8218
#నిర్వచించు GL_FRAMEBUFFER_UNDEFINED          0x8219
#నిర్వచించు GL_లోతు_STENCIL_ATTACHMENT       0x821A
#నిర్వచించు GL_లోతు_STENCIL                  0x84F9
#నిర్వచించు GL_UNSIGNED_INT_24_8              0x84FA
#నిర్వచించు GL_DEPTH24_STENCIL8               0x88F0
#నిర్వచించు GL_UNSIGNED_NORMALIZED            0x8C17
#నిర్వచించు GL_DRAW_FRAMEBUFFER_BINDING       0x8CA6
#నిర్వచించు GL_READ_FRAMEBUFFER               0x8CA8
#నిర్వచించు GL_DRAW_FRAMEBUFFER               0x8CA9
#నిర్వచించు GL_READ_FRAMEBUFFER_BINDING       0x8CAA
#నిర్వచించు GL_RENDERBUFFER_SAMPLES           0x8CAB
#నిర్వచించు GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER 0x8CD4
#నిర్వచించు GL_MAX_COLOR_ATTACHMENTS          0x8CDF
#నిర్వచించు GL_COLOR_ATTACHMENT1              0x8CE1
#నిర్వచించు GL_COLOR_ATTACHMENT2              0x8CE2
#నిర్వచించు GL_COLOR_ATTACHMENT3              0x8CE3
#నిర్వచించు GL_COLOR_ATTACHMENT4              0x8CE4
#నిర్వచించు GL_COLOR_ATTACHMENT5              0x8CE5
#నిర్వచించు GL_COLOR_ATTACHMENT6              0x8CE6
#నిర్వచించు GL_COLOR_ATTACHMENT7              0x8CE7
#నిర్వచించు GL_COLOR_ATTACHMENT8              0x8CE8
#నిర్వచించు GL_COLOR_ATTACHMENT9              0x8CE9
#నిర్వచించు GL_COLOR_ATTACHMENT10             0x8CEA
#నిర్వచించు GL_COLOR_ATTACHMENT11             0x8CEB
#నిర్వచించు GL_COLOR_ATTACHMENT12             0x8CEC
#నిర్వచించు GL_COLOR_ATTACHMENT13             0x8CED
#నిర్వచించు GL_COLOR_ATTACHMENT14             0x8CEE
#నిర్వచించు GL_COLOR_ATTACHMENT15             0x8CEF
#నిర్వచించు GL_COLOR_ATTACHMENT16             0x8CF0
#నిర్వచించు GL_COLOR_ATTACHMENT17             0x8CF1
#నిర్వచించు GL_COLOR_ATTACHMENT18             0x8CF2
#నిర్వచించు GL_COLOR_ATTACHMENT19             0x8CF3
#నిర్వచించు GL_COLOR_ATTACHMENT20             0x8CF4
#నిర్వచించు GL_COLOR_ATTACHMENT21             0x8CF5
#నిర్వచించు GL_COLOR_ATTACHMENT22             0x8CF6
#నిర్వచించు GL_COLOR_ATTACHMENT23             0x8CF7
#నిర్వచించు GL_COLOR_ATTACHMENT24             0x8CF8
#నిర్వచించు GL_COLOR_ATTACHMENT25             0x8CF9
#నిర్వచించు GL_COLOR_ATTACHMENT26             0x8CFA
#నిర్వచించు GL_COLOR_ATTACHMENT27             0x8CFB
#నిర్వచించు GL_COLOR_ATTACHMENT28             0x8CFC
#నిర్వచించు GL_COLOR_ATTACHMENT29             0x8CFD
#నిర్వచించు GL_COLOR_ATTACHMENT30             0x8CFE
#నిర్వచించు GL_COLOR_ATTACHMENT31             0x8CFF
#నిర్వచించు GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE 0x8D56
#నిర్వచించు GL_MAX_SAMPLES                    0x8D57
#నిర్వచించు GL_HALF_FLOAT                     0x140B
#నిర్వచించు GL_MAP_READ_బిట్టు                   0x0001
#నిర్వచించు GL_MAP_WRITE_బిట్టు                  0x0002
#నిర్వచించు GL_MAP_INVALIDATE_RANGE_బిట్టు       0x0004
#నిర్వచించు GL_MAP_INVALIDATE_బఫరు_బిట్టు      0x0008
#నిర్వచించు GL_MAP_FLUSH_EXPLICIT_బిట్టు         0x0010
#నిర్వచించు GL_MAP_UNSYNCHRONIZED_బిట్టు         0x0020
#నిర్వచించు GL_RG                             0x8227
#నిర్వచించు GL_RG_INTEGER                     0x8228
#నిర్వచించు GL_R8                             0x8229
#నిర్వచించు GL_RG8                            0x822B
#నిర్వచించు GL_R16F                           0x822D
#నిర్వచించు GL_R32F                           0x822E
#నిర్వచించు GL_RG16F                          0x822F
#నిర్వచించు GL_RG32F                          0x8230
#నిర్వచించు GL_R8I                            0x8231
#నిర్వచించు GL_R8UI                           0x8232
#నిర్వచించు GL_R16I                           0x8233
#నిర్వచించు GL_R16UI                          0x8234
#నిర్వచించు GL_R32I                           0x8235
#నిర్వచించు GL_R32UI                          0x8236
#నిర్వచించు GL_RG8I                           0x8237
#నిర్వచించు GL_RG8UI                          0x8238
#నిర్వచించు GL_RG16I                          0x8239
#నిర్వచించు GL_RG16UI                         0x823A
#నిర్వచించు GL_RG32I                          0x823B
#నిర్వచించు GL_RG32UI                         0x823C
#నిర్వచించు GL_శీర్షం_ARRAY_BINDING           0x85B5
#నిర్వచించు GL_R8_SNORM                       0x8F94
#నిర్వచించు GL_RG8_SNORM                      0x8F95
#నిర్వచించు GL_RGB8_SNORM                     0x8F96
#నిర్వచించు GL_RGBA8_SNORM                    0x8F97
#నిర్వచించు GL_SIGNED_NORMALIZED              0x8F9C
#నిర్వచించు GL_PRIMITIVE_RESTART_FIXED_సూచీ  0x8D69
#నిర్వచించు GL_COPY_READ_బఫరు               0x8F36
#నిర్వచించు GL_COPY_WRITE_బఫరు              0x8F37
#నిర్వచించు GL_COPY_READ_బఫరు_BINDING       0x8F36
#నిర్వచించు GL_COPY_WRITE_బఫరు_BINDING      0x8F37
#నిర్వచించు GL_ఏకరీతి_బఫరు                 0x8A11
#నిర్వచించు GL_ఏకరీతి_బఫరు_BINDING         0x8A28
#నిర్వచించు GL_ఏకరీతి_బఫరు_ప్రారంభం           0x8A29
#నిర్వచించు GL_ఏకరీతి_బఫరు_కొలత            0x8A2A
#నిర్వచించు GL_MAX_శీర్షం_ఏకరీతి_ఖండాలు      0x8A2B
#నిర్వచించు GL_MAX_FRAGMENT_ఏకరీతి_ఖండాలు    0x8A2D
#నిర్వచించు GL_MAX_COMBINED_ఏకరీతి_ఖండాలు    0x8A2E
#నిర్వచించు GL_MAX_ఏకరీతి_బఫరు_BINDINGS    0x8A2F
#నిర్వచించు GL_MAX_ఏకరీతి_ఖండం_కొలత         0x8A30
#నిర్వచించు GL_MAX_COMBINED_శీర్షం_ఏకరీతి_COMPONENTS 0x8A31
#నిర్వచించు GL_MAX_COMBINED_FRAGMENT_ఏకరీతి_COMPONENTS 0x8A33
#నిర్వచించు GL_ఏకరీతి_బఫరు_స్థానభ్రంశం_ALIGNMENT 0x8A34
#నిర్వచించు GL_చురుకైన_ఏకరీతి_ఖండం_MAX_NAME_నిడివి 0x8A35
#నిర్వచించు GL_చురుకైన_ఏకరీతి_ఖండాలు          0x8A36
#నిర్వచించు GL_ఏకరీతి_TYPE                   0x8A37
#నిర్వచించు GL_ఏకరీతి_కొలత                   0x8A38
#నిర్వచించు GL_ఏకరీతి_NAME_నిడివి            0x8A39
#నిర్వచించు GL_ఏకరీతి_ఖండం_సూచీ            0x8A3A
#నిర్వచించు GL_ఏకరీతి_స్థానభ్రంశం                 0x8A3B
#నిర్వచించు GL_ఏకరీతి_ARRAY_STRIDE           0x8A3C
#నిర్వచించు GL_ఏకరీతి_మాతృక_STRIDE          0x8A3D
#నిర్వచించు GL_ఏకరీతి_IS_అడ్డువరుస_MAJOR           0x8A3E
#నిర్వచించు GL_ఏకరీతి_ఖండం_BINDING          0x8A3F
#నిర్వచించు GL_ఏకరీతి_ఖండం_దత్తాంశం_కొలత        0x8A40
#నిర్వచించు GL_ఏకరీతి_ఖండం_NAME_నిడివి      0x8A41
#నిర్వచించు GL_ఏకరీతి_ఖండం_చురుకైన_UNIFORMS  0x8A42
#నిర్వచించు GL_ఏకరీతి_ఖండం_చురుకైన_ఏకరీతి_INDICES 0x8A43
#నిర్వచించు GL_ఏకరీతి_ఖండం_REFERENCED_BY_శీర్షం_SHADER 0x8A44
#నిర్వచించు GL_ఏకరీతి_ఖండం_REFERENCED_BY_FRAGMENT_SHADER 0x8A46
#నిర్వచించు GL_INVALID_సూచీ                  0xFFFFFFFFu
#నిర్వచించు GL_MAX_శీర్షం_OUTPUT_COMPONENTS   0x9122
#నిర్వచించు GL_MAX_FRAGMENT_ఆదానం_COMPONENTS  0x9125
#నిర్వచించు GL_MAX_SERVER_WAIT_TIMEOUT        0x9111
#నిర్వచించు GL_OBJECT_TYPE                    0x9112
#నిర్వచించు GL_SYNC_CONDITION                 0x9113
#నిర్వచించు GL_SYNC_స్థితి                    0x9114
#నిర్వచించు GL_SYNC_FLAGS                     0x9115
#నిర్వచించు GL_SYNC_FENCE                     0x9116
#నిర్వచించు GL_SYNC_GPU_COMMANDS_COMPLETE     0x9117
#నిర్వచించు GL_UNSIGNALED                     0x9118
#నిర్వచించు GL_SIGNALED                       0x9119
#నిర్వచించు GL_ALREADY_SIGNALED               0x911A
#నిర్వచించు GL_TIMEOUT_EXPIRED                0x911B
#నిర్వచించు GL_CONDITION_SATISFIED            0x911C
#నిర్వచించు GL_WAIT_FAILED                    0x911D
#నిర్వచించు GL_SYNC_FLUSH_COMMANDS_బిట్టు        0x00000001
#నిర్వచించు GL_TIMEOUT_IGNORED                0xFFFFFFFFFFFFFFFFull
#నిర్వచించు GL_శీర్షం_ATTRIB_ARRAY_భాజకం    0x88FE
#నిర్వచించు GL_ANY_SAMPLES_PASSED             0x8C2F
#నిర్వచించు GL_ANY_SAMPLES_PASSED_CONSERVATIVE 0x8D6A
#నిర్వచించు GL_SAMPLER_BINDING                0x8919
#నిర్వచించు GL_RGB10_A2UI                     0x906F
#నిర్వచించు GL_TEXTURE_SWIZZLE_R              0x8E42
#నిర్వచించు GL_TEXTURE_SWIZZLE_G              0x8E43
#నిర్వచించు GL_TEXTURE_SWIZZLE_B              0x8E44
#నిర్వచించు GL_TEXTURE_SWIZZLE_A              0x8E45
#నిర్వచించు GL_GREEN                          0x1904
#నిర్వచించు GL_BLUE                           0x1905
#నిర్వచించు GL_INT_2_10_10_10_REV             0x8D9F
#నిర్వచించు GL_TRANSFORM_FEEDBACK             0x8E22
#నిర్వచించు GL_TRANSFORM_FEEDBACK_PAUSED      0x8E23
#నిర్వచించు GL_TRANSFORM_FEEDBACK_చురుకైన      0x8E24
#నిర్వచించు GL_TRANSFORM_FEEDBACK_BINDING     0x8E25
#నిర్వచించు GL_కార్యక్రమం_ద్విమాన_RETRIEVABLE_HINT 0x8257
#నిర్వచించు GL_కార్యక్రమం_ద్విమాన_నిడివి          0x8741
#నిర్వచించు GL_అంకె_కార్యక్రమం_ద్విమాన_FORMATS     0x87FE
#నిర్వచించు GL_కార్యక్రమం_ద్విమాన_FORMATS         0x87FF
#నిర్వచించు GL_COMPRESSED_R11_EAC             0x9270
#నిర్వచించు GL_COMPRESSED_SIGNED_R11_EAC      0x9271
#నిర్వచించు GL_COMPRESSED_RG11_EAC            0x9272
#నిర్వచించు GL_COMPRESSED_SIGNED_RG11_EAC     0x9273
#నిర్వచించు GL_COMPRESSED_RGB8_ETC2           0x9274
#నిర్వచించు GL_COMPRESSED_SRGB8_ETC2          0x9275
#నిర్వచించు GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9276
#నిర్వచించు GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9277
#నిర్వచించు GL_COMPRESSED_RGBA8_ETC2_EAC      0x9278
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC 0x9279
#నిర్వచించు GL_TEXTURE_IMMUTABLE_FORMAT       0x912F
#నిర్వచించు GL_MAX_ELEMENT_సూచీ              0x8D6B
#నిర్వచించు GL_అంకె_SAMPLE_COUNTS              0x9380
#నిర్వచించు GL_TEXTURE_IMMUTABLE_స్థాయిలు       0x82DF
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLREADBUFFERPROC) (GLenum src);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWRANGEELEMENTSPROC) (GLenum బహుళకం, GLuint ప్రారంభం, GLuint చివర, GLsizei లెక్క, GLenum type, స్థిరరాశి శూన్య *indices);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXIMAGE3DPROC) (GLenum లక్ష్యం, GLint level, GLint internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLint border, GLenum format, GLenum type, స్థిరరాశి శూన్య *pixels);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXSUBIMAGE3DPROC) (GLenum లక్ష్యం, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLenum format, GLenum type, స్థిరరాశి శూన్య *pixels);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCOPYTEXSUBIMAGE3DPROC) (GLenum లక్ష్యం, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei వెడల్పు, GLsizei ఎత్తు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCOMPRESSEDTEXIMAGE3DPROC) (GLenum లక్ష్యం, GLint level, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLint border, GLsizei image_కొలత, స్థిరరాశి శూన్య *దత్తాంశం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC) (GLenum లక్ష్యం, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLenum format, GLsizei image_కొలత, స్థిరరాశి శూన్య *దత్తాంశం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGENQUERIESPROC) (GLsizei n, GLuint *ids);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDELETEQUERIESPROC) (GLsizei n, స్థిరరాశి GLuint *ids);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLISQUERYPROC) (GLuint id);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBEGINQUERYPROC) (GLenum లక్ష్యం, GLuint id);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLENDQUERYPROC) (GLenum లక్ష్యం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETQUERYIVPROC) (GLenum లక్ష్యం, GLenum pname, GLint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETQUERYOBJECTUIVPROC) (GLuint id, GLenum pname, GLuint *params);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLUNMAPBUFFERPROC) (GLenum లక్ష్యం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETBUFFERPOINTERVPROC) (GLenum లక్ష్యం, GLenum pname, శూన్య **params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWBUFFERSPROC) (GLsizei n, స్థిరరాశి GLenum *bufs);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORMMATRIX2X3FVPROC) (GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORMMATRIX3X2FVPROC) (GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORMMATRIX2X4FVPROC) (GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORMMATRIX4X2FVPROC) (GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORMMATRIX3X4FVPROC) (GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORMMATRIX4X3FVPROC) (GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBLITFRAMEBUFFERPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield ముసుగు, GLenum filter);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC) (GLenum లక్ష్యం, GLsizei samples, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURELAYERPROC) (GLenum లక్ష్యం, GLenum attachment, GLuint texture, GLint level, GLint layer);
రకనిర్వచనం శూన్య *(GL_APIENTRYP PFNGLMAPBUFFERRANGEPROC) (GLenum లక్ష్యం, GLintptr స్థానభ్రంశం_2, GLsizeiptr నిడివి, GLbitfield access);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEPROC) (GLenum లక్ష్యం, GLintptr స్థానభ్రంశం_2, GLsizeiptr నిడివి);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBINDVERTEXARRAYPROC) (GLuint array);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDELETEVERTEXARRAYSPROC) (GLsizei n, స్థిరరాశి GLuint *arrays);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint *arrays);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLISVERTEXARRAYPROC) (GLuint array);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETINTEGERI_VPROC) (GLenum లక్ష్యం, GLuint సూచీ, GLint *దత్తాంశం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBEGINTRANSFORMFEEDBACKPROC) (GLenum primitive_బహుళకం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLENDTRANSFORMFEEDBACKPROC) (శూన్య);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBINDBUFFERRANGEPROC) (GLenum లక్ష్యం, GLuint సూచీ, GLuint బఫరు_2, GLintptr స్థానభ్రంశం_2, GLsizeiptr కొలత);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBINDBUFFERBASEPROC) (GLenum లక్ష్యం, GLuint సూచీ, GLuint బఫరు_2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTRANSFORMFEEDBACKVARYINGSPROC) (GLuint కార్యక్రమం, GLsizei లెక్క, స్థిరరాశి GLchar *స్థిరరాశి*varyings, GLenum బఫరు_బహుళకం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETTRANSFORMFEEDBACKVARYINGPROC) (GLuint కార్యక్రమం, GLuint సూచీ, GLsizei buf_కొలత, GLsizei *నిడివి, GLsizei *కొలత, GLenum *type, GLchar *name);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLVERTEXATTRIBIPOINTERPROC) (GLuint సూచీ, GLint కొలత, GLenum type, GLsizei stride, స్థిరరాశి శూన్య *సూచిక_2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETVERTEXATTRIBIIVPROC) (GLuint సూచీ, GLenum pname, GLint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETVERTEXATTRIBIUIVPROC) (GLuint సూచీ, GLenum pname, GLuint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLVERTEXATTRIBI4IPROC) (GLuint సూచీ, GLint x, GLint y, GLint z, GLint w);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLVERTEXATTRIBI4UIPROC) (GLuint సూచీ, GLuint x, GLuint y, GLuint z, GLuint w);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLVERTEXATTRIBI4IVPROC) (GLuint సూచీ, స్థిరరాశి GLint *v);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLVERTEXATTRIBI4UIVPROC) (GLuint సూచీ, స్థిరరాశి GLuint *v);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETUNIFORMUIVPROC) (GLuint కార్యక్రమం, GLint location, GLuint *params);
రకనిర్వచనం GLint (GL_APIENTRYP PFNGLGETFRAGDATALOCATIONPROC) (GLuint కార్యక్రమం, స్థిరరాశి GLchar *name);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM1UIPROC) (GLint location, GLuint v0);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM2UIPROC) (GLint location, GLuint v0, GLuint v1);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM3UIPROC) (GLint location, GLuint v0, GLuint v1, GLuint v2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM4UIPROC) (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM1UIVPROC) (GLint location, GLsizei లెక్క, స్థిరరాశి GLuint *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM2UIVPROC) (GLint location, GLsizei లెక్క, స్థిరరాశి GLuint *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM3UIVPROC) (GLint location, GLsizei లెక్క, స్థిరరాశి GLuint *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORM4UIVPROC) (GLint location, GLsizei లెక్క, స్థిరరాశి GLuint *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCLEARBUFFERIVPROC) (GLenum బఫరు_2, GLint drawbuffer, స్థిరరాశి GLint *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCLEARBUFFERUIVPROC) (GLenum బఫరు_2, GLint drawbuffer, స్థిరరాశి GLuint *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCLEARBUFFERFVPROC) (GLenum బఫరు_2, GLint drawbuffer, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCLEARBUFFERFIPROC) (GLenum బఫరు_2, GLint drawbuffer, GLfloat లోతు_2, GLint stencil);
రకనిర్వచనం స్థిరరాశి GLubyte *(GL_APIENTRYP PFNGLGETSTRINGIPROC) (GLenum name, GLuint సూచీ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCOPYBUFFERSUBDATAPROC) (GLenum read_లక్ష్యం, GLenum write_లక్ష్యం, GLintptr read_స్థానభ్రంశం, GLintptr write_స్థానభ్రంశం, GLsizeiptr కొలత);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETUNIFORMINDICESPROC) (GLuint కార్యక్రమం, GLsizei ఏకరీతి_లెక్క, స్థిరరాశి GLchar *స్థిరరాశి*ఏకరీతి_పేర్లు, GLuint *ఏకరీతి_Indices);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETACTIVEUNIFORMSIVPROC) (GLuint కార్యక్రమం, GLsizei ఏకరీతి_లెక్క, స్థిరరాశి GLuint *ఏకరీతి_Indices, GLenum pname, GLint *params);
రకనిర్వచనం GLuint (GL_APIENTRYP PFNGLGETUNIFORMBLOCKINDEXPROC) (GLuint కార్యక్రమం, స్థిరరాశి GLchar *ఏకరీతి_ఖండం_Name);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKIVPROC) (GLuint కార్యక్రమం, GLuint ఏకరీతి_ఖండం_సూచీ, GLenum pname, GLint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC) (GLuint కార్యక్రమం, GLuint ఏకరీతి_ఖండం_సూచీ, GLsizei buf_కొలత, GLsizei *నిడివి, GLchar *ఏకరీతి_ఖండం_Name);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUNIFORMBLOCKBINDINGPROC) (GLuint కార్యక్రమం, GLuint ఏకరీతి_ఖండం_సూచీ, GLuint ఏకరీతి_ఖండం_Binding);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDPROC) (GLenum బహుళకం, GLint మొదటి, GLsizei లెక్క, GLsizei instancecount);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDPROC) (GLenum బహుళకం, GLsizei లెక్క, GLenum type, స్థిరరాశి శూన్య *indices, GLsizei instancecount);
రకనిర్వచనం GLsync (GL_APIENTRYP PFNGLFENCESYNCPROC) (GLenum condition, GLbitfield flags);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLISSYNCPROC) (GLsync sync);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDELETESYNCPROC) (GLsync sync);
రకనిర్వచనం GLenum (GL_APIENTRYP PFNGLCLIENTWAITSYNCPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLWAITSYNCPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETINTEGER64VPROC) (GLenum pname, GLint64 *దత్తాంశం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETSYNCIVPROC) (GLsync sync, GLenum pname, GLsizei లెక్క, GLsizei *నిడివి, GLint *విలువలు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETINTEGER64I_VPROC) (GLenum లక్ష్యం, GLuint సూచీ, GLint64 *దత్తాంశం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETBUFFERPARAMETERI64VPROC) (GLenum లక్ష్యం, GLenum pname, GLint64 *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGENSAMPLERSPROC) (GLsizei లెక్క, GLuint *samplers);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDELETESAMPLERSPROC) (GLsizei లెక్క, స్థిరరాశి GLuint *samplers);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLISSAMPLERPROC) (GLuint sampler);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBINDSAMPLERPROC) (GLuint unit, GLuint sampler);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSAMPLERPARAMETERIPROC) (GLuint sampler, GLenum pname, GLint param);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, స్థిరరాశి GLint *param);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSAMPLERPARAMETERFPROC) (GLuint sampler, GLenum pname, GLfloat param);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, స్థిరరాశి GLfloat *param);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, GLint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, GLfloat *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLVERTEXATTRIBDIVISORPROC) (GLuint సూచీ, GLuint భాజకం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBINDTRANSFORMFEEDBACKPROC) (GLenum లక్ష్యం, GLuint id);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDELETETRANSFORMFEEDBACKSPROC) (GLsizei n, స్థిరరాశి GLuint *ids);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGENTRANSFORMFEEDBACKSPROC) (GLsizei n, GLuint *ids);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLISTRANSFORMFEEDBACKPROC) (GLuint id);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPAUSETRANSFORMFEEDBACKPROC) (శూన్య);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLRESUMETRANSFORMFEEDBACKPROC) (శూన్య);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETPROGRAMBINARYPROC) (GLuint కార్యక్రమం, GLsizei buf_కొలత, GLsizei *నిడివి, GLenum *ద్విమాన_Format, శూన్య *ద్విమాన);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMBINARYPROC) (GLuint కార్యక్రమం, GLenum ద్విమాన_Format, స్థిరరాశి శూన్య *ద్విమాన, GLsizei నిడివి);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMPARAMETERIPROC) (GLuint కార్యక్రమం, GLenum pname, GLint విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLINVALIDATEFRAMEBUFFERPROC) (GLenum లక్ష్యం, GLsizei అంకె_Attachments, స్థిరరాశి GLenum *attachments);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLINVALIDATESUBFRAMEBUFFERPROC) (GLenum లక్ష్యం, GLsizei అంకె_Attachments, స్థిరరాశి GLenum *attachments, GLint x, GLint y, GLsizei వెడల్పు, GLsizei ఎత్తు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXSTORAGE2DPROC) (GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXSTORAGE3DPROC) (GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETINTERNALFORMATIVPROC) (GLenum లక్ష్యం, GLenum internalformat, GLenum pname, GLsizei లెక్క, GLint *params);
#ఒకవేళ GL_GLES_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY gl_Read_బఫరు (GLenum src);
GL_APICALL శూన్య GL_APIENTRY glDrawRangeElements (GLenum బహుళకం, GLuint ప్రారంభం, GLuint చివర, GLsizei లెక్క, GLenum type, స్థిరరాశి శూన్య *indices);
GL_APICALL శూన్య GL_APIENTRY glTexImage3D (GLenum లక్ష్యం, GLint level, GLint internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLint border, GLenum format, GLenum type, స్థిరరాశి శూన్య *pixels);
GL_APICALL శూన్య GL_APIENTRY glTexSubImage3D (GLenum లక్ష్యం, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLenum format, GLenum type, స్థిరరాశి శూన్య *pixels);
GL_APICALL శూన్య GL_APIENTRY glCopyTexSubImage3D (GLenum లక్ష్యం, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei వెడల్పు, GLsizei ఎత్తు);
GL_APICALL శూన్య GL_APIENTRY glCompressedTexImage3D (GLenum లక్ష్యం, GLint level, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLint border, GLsizei image_కొలత, స్థిరరాశి శూన్య *దత్తాంశం);
GL_APICALL శూన్య GL_APIENTRY glCompressedTexSubImage3D (GLenum లక్ష్యం, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLenum format, GLsizei image_కొలత, స్థిరరాశి శూన్య *దత్తాంశం);
GL_APICALL శూన్య GL_APIENTRY glGenQueries (GLsizei n, GLuint *ids);
GL_APICALL శూన్య GL_APIENTRY glDeleteQueries (GLsizei n, స్థిరరాశి GLuint *ids);
GL_APICALL GLboolean GL_APIENTRY glIsQuery (GLuint id);
GL_APICALL శూన్య GL_APIENTRY glBeginQuery (GLenum లక్ష్యం, GLuint id);
GL_APICALL శూన్య GL_APIENTRY gl_చివర_Query (GLenum లక్ష్యం);
GL_APICALL శూన్య GL_APIENTRY glGetQueryiv (GLenum లక్ష్యం, GLenum pname, GLint *params);
GL_APICALL శూన్య GL_APIENTRY glGetQueryObjectuiv (GLuint id, GLenum pname, GLuint *params);
GL_APICALL GLboolean GL_APIENTRY gl_Unmap_బఫరు (GLenum లక్ష్యం);
GL_APICALL శూన్య GL_APIENTRY gl_Get_బఫరు_Pointerv (GLenum లక్ష్యం, GLenum pname, శూన్య **params);
GL_APICALL శూన్య GL_APIENTRY glDrawBuffers (GLsizei n, స్థిరరాశి GLenum *bufs);
GL_APICALL శూన్య GL_APIENTRY gl_ఏకరీతి_Matrix2x3fv (GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_ఏకరీతి_Matrix3x2fv (GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_ఏకరీతి_Matrix2x4fv (GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_ఏకరీతి_Matrix4x2fv (GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_ఏకరీతి_Matrix3x4fv (GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_ఏకరీతి_Matrix4x3fv (GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY glBlitFramebuffer (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield ముసుగు, GLenum filter);
GL_APICALL శూన్య GL_APIENTRY glRenderbufferStorageMultisample (GLenum లక్ష్యం, GLsizei samples, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
GL_APICALL శూన్య GL_APIENTRY glFramebufferTextureLayer (GLenum లక్ష్యం, GLenum attachment, GLuint texture, GLint level, GLint layer);
GL_APICALL శూన్య *GL_APIENTRY gl_Map_బఫరు_Range (GLenum లక్ష్యం, GLintptr స్థానభ్రంశం_2, GLsizeiptr నిడివి, GLbitfield access);
GL_APICALL శూన్య GL_APIENTRY gl_Flush_Mapped_బఫరు_Range (GLenum లక్ష్యం, GLintptr స్థానభ్రంశం_2, GLsizeiptr నిడివి);
GL_APICALL శూన్య GL_APIENTRY gl_Bind_శీర్షం_Array (GLuint array);
GL_APICALL శూన్య GL_APIENTRY gl_Delete_శీర్షం_Arrays (GLsizei n, స్థిరరాశి GLuint *arrays);
GL_APICALL శూన్య GL_APIENTRY gl_Gen_శీర్షం_Arrays (GLsizei n, GLuint *arrays);
GL_APICALL GLboolean GL_APIENTRY gl_Is_శీర్షం_Array (GLuint array);
GL_APICALL శూన్య GL_APIENTRY glGetIntegeri_v (GLenum లక్ష్యం, GLuint సూచీ, GLint *దత్తాంశం);
GL_APICALL శూన్య GL_APIENTRY glBeginTransformFeedback (GLenum primitive_బహుళకం);
GL_APICALL శూన్య GL_APIENTRY gl_చివర_Transform_Feedback (శూన్య);
GL_APICALL శూన్య GL_APIENTRY gl_Bind_బఫరు_Range (GLenum లక్ష్యం, GLuint సూచీ, GLuint బఫరు_2, GLintptr స్థానభ్రంశం_2, GLsizeiptr కొలత);
GL_APICALL శూన్య GL_APIENTRY gl_Bind_బఫరు_పునాది (GLenum లక్ష్యం, GLuint సూచీ, GLuint బఫరు_2);
GL_APICALL శూన్య GL_APIENTRY glTransformFeedbackVaryings (GLuint కార్యక్రమం, GLsizei లెక్క, స్థిరరాశి GLchar *స్థిరరాశి*varyings, GLenum బఫరు_బహుళకం);
GL_APICALL శూన్య GL_APIENTRY glGetTransformFeedbackVarying (GLuint కార్యక్రమం, GLuint సూచీ, GLsizei buf_కొలత, GLsizei *నిడివి, GLsizei *కొలత, GLenum *type, GLchar *name);
GL_APICALL శూన్య GL_APIENTRY gl_శీర్షం_Attrib_IPointer (GLuint సూచీ, GLint కొలత, GLenum type, GLsizei stride, స్థిరరాశి శూన్య *సూచిక_2);
GL_APICALL శూన్య GL_APIENTRY gl_Get_శీర్షం_Attrib_Iiv (GLuint సూచీ, GLenum pname, GLint *params);
GL_APICALL శూన్య GL_APIENTRY gl_Get_శీర్షం_Attrib_Iuiv (GLuint సూచీ, GLenum pname, GLuint *params);
GL_APICALL శూన్య GL_APIENTRY gl_శీర్షం_Attrib_I4i (GLuint సూచీ, GLint x, GLint y, GLint z, GLint w);
GL_APICALL శూన్య GL_APIENTRY gl_శీర్షం_Attrib_I4ui (GLuint సూచీ, GLuint x, GLuint y, GLuint z, GLuint w);
GL_APICALL శూన్య GL_APIENTRY gl_శీర్షం_Attrib_I4iv (GLuint సూచీ, స్థిరరాశి GLint *v);
GL_APICALL శూన్య GL_APIENTRY gl_శీర్షం_Attrib_I4uiv (GLuint సూచీ, స్థిరరాశి GLuint *v);
GL_APICALL శూన్య GL_APIENTRY glGetUniformuiv (GLuint కార్యక్రమం, GLint location, GLuint *params);
GL_APICALL GLint GL_APIENTRY gl_Get_Frag_దత్తాంశం_Location (GLuint కార్యక్రమం, స్థిరరాశి GLchar *name);
GL_APICALL శూన్య GL_APIENTRY glUniform1ui (GLint location, GLuint v0);
GL_APICALL శూన్య GL_APIENTRY glUniform2ui (GLint location, GLuint v0, GLuint v1);
GL_APICALL శూన్య GL_APIENTRY glUniform3ui (GLint location, GLuint v0, GLuint v1, GLuint v2);
GL_APICALL శూన్య GL_APIENTRY glUniform4ui (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
GL_APICALL శూన్య GL_APIENTRY glUniform1uiv (GLint location, GLsizei లెక్క, స్థిరరాశి GLuint *విలువ);
GL_APICALL శూన్య GL_APIENTRY glUniform2uiv (GLint location, GLsizei లెక్క, స్థిరరాశి GLuint *విలువ);
GL_APICALL శూన్య GL_APIENTRY glUniform3uiv (GLint location, GLsizei లెక్క, స్థిరరాశి GLuint *విలువ);
GL_APICALL శూన్య GL_APIENTRY glUniform4uiv (GLint location, GLsizei లెక్క, స్థిరరాశి GLuint *విలువ);
GL_APICALL శూన్య GL_APIENTRY glClearBufferiv (GLenum బఫరు_2, GLint drawbuffer, స్థిరరాశి GLint *విలువ);
GL_APICALL శూన్య GL_APIENTRY glClearBufferuiv (GLenum బఫరు_2, GLint drawbuffer, స్థిరరాశి GLuint *విలువ);
GL_APICALL శూన్య GL_APIENTRY glClearBufferfv (GLenum బఫరు_2, GLint drawbuffer, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY glClearBufferfi (GLenum బఫరు_2, GLint drawbuffer, GLfloat లోతు_2, GLint stencil);
GL_APICALL స్థిరరాశి GLubyte *GL_APIENTRY glGetStringi (GLenum name, GLuint సూచీ);
GL_APICALL శూన్య GL_APIENTRY gl_Copy_బఫరు_Sub_దత్తాంశం (GLenum read_లక్ష్యం, GLenum write_లక్ష్యం, GLintptr read_స్థానభ్రంశం, GLintptr write_స్థానభ్రంశం, GLsizeiptr కొలత);
GL_APICALL శూన్య GL_APIENTRY gl_Get_ఏకరీతి_Indices (GLuint కార్యక్రమం, GLsizei ఏకరీతి_లెక్క, స్థిరరాశి GLchar *స్థిరరాశి*ఏకరీతి_పేర్లు, GLuint *ఏకరీతి_Indices);
GL_APICALL శూన్య GL_APIENTRY gl_Get_చురుకైన_Uniformsiv (GLuint కార్యక్రమం, GLsizei ఏకరీతి_లెక్క, స్థిరరాశి GLuint *ఏకరీతి_Indices, GLenum pname, GLint *params);
GL_APICALL GLuint GL_APIENTRY gl_Get_ఏకరీతి_ఖండం_సూచీ (GLuint కార్యక్రమం, స్థిరరాశి GLchar *ఏకరీతి_ఖండం_Name);
GL_APICALL శూన్య GL_APIENTRY gl_Get_చురుకైన_ఏకరీతి_Blockiv (GLuint కార్యక్రమం, GLuint ఏకరీతి_ఖండం_సూచీ, GLenum pname, GLint *params);
GL_APICALL శూన్య GL_APIENTRY gl_Get_చురుకైన_ఏకరీతి_ఖండం_Name (GLuint కార్యక్రమం, GLuint ఏకరీతి_ఖండం_సూచీ, GLsizei buf_కొలత, GLsizei *నిడివి, GLchar *ఏకరీతి_ఖండం_Name);
GL_APICALL శూన్య GL_APIENTRY gl_ఏకరీతి_ఖండం_Binding (GLuint కార్యక్రమం, GLuint ఏకరీతి_ఖండం_సూచీ, GLuint ఏకరీతి_ఖండం_Binding);
GL_APICALL శూన్య GL_APIENTRY glDrawArraysInstanced (GLenum బహుళకం, GLint మొదటి, GLsizei లెక్క, GLsizei instancecount);
GL_APICALL శూన్య GL_APIENTRY glDrawElementsInstanced (GLenum బహుళకం, GLsizei లెక్క, GLenum type, స్థిరరాశి శూన్య *indices, GLsizei instancecount);
GL_APICALL GLsync GL_APIENTRY glFenceSync (GLenum condition, GLbitfield flags);
GL_APICALL GLboolean GL_APIENTRY glIsSync (GLsync sync);
GL_APICALL శూన్య GL_APIENTRY glDeleteSync (GLsync sync);
GL_APICALL GLenum GL_APIENTRY glClientWaitSync (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_APICALL శూన్య GL_APIENTRY glWaitSync (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_APICALL శూన్య GL_APIENTRY glGetInteger64v (GLenum pname, GLint64 *దత్తాంశం);
GL_APICALL శూన్య GL_APIENTRY glGetSynciv (GLsync sync, GLenum pname, GLsizei లెక్క, GLsizei *నిడివి, GLint *విలువలు);
GL_APICALL శూన్య GL_APIENTRY glGetInteger64i_v (GLenum లక్ష్యం, GLuint సూచీ, GLint64 *దత్తాంశం);
GL_APICALL శూన్య GL_APIENTRY gl_Get_బఫరు_Parameteri64v (GLenum లక్ష్యం, GLenum pname, GLint64 *params);
GL_APICALL శూన్య GL_APIENTRY glGenSamplers (GLsizei లెక్క, GLuint *samplers);
GL_APICALL శూన్య GL_APIENTRY glDeleteSamplers (GLsizei లెక్క, స్థిరరాశి GLuint *samplers);
GL_APICALL GLboolean GL_APIENTRY glIsSampler (GLuint sampler);
GL_APICALL శూన్య GL_APIENTRY glBindSampler (GLuint unit, GLuint sampler);
GL_APICALL శూన్య GL_APIENTRY glSamplerParameteri (GLuint sampler, GLenum pname, GLint param);
GL_APICALL శూన్య GL_APIENTRY glSamplerParameteriv (GLuint sampler, GLenum pname, స్థిరరాశి GLint *param);
GL_APICALL శూన్య GL_APIENTRY glSamplerParameterf (GLuint sampler, GLenum pname, GLfloat param);
GL_APICALL శూన్య GL_APIENTRY glSamplerParameterfv (GLuint sampler, GLenum pname, స్థిరరాశి GLfloat *param);
GL_APICALL శూన్య GL_APIENTRY glGetSamplerParameteriv (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL శూన్య GL_APIENTRY glGetSamplerParameterfv (GLuint sampler, GLenum pname, GLfloat *params);
GL_APICALL శూన్య GL_APIENTRY gl_శీర్షం_Attrib_భాజకం (GLuint సూచీ, GLuint భాజకం);
GL_APICALL శూన్య GL_APIENTRY glBindTransformFeedback (GLenum లక్ష్యం, GLuint id);
GL_APICALL శూన్య GL_APIENTRY glDeleteTransformFeedbacks (GLsizei n, స్థిరరాశి GLuint *ids);
GL_APICALL శూన్య GL_APIENTRY glGenTransformFeedbacks (GLsizei n, GLuint *ids);
GL_APICALL GLboolean GL_APIENTRY glIsTransformFeedback (GLuint id);
GL_APICALL శూన్య GL_APIENTRY glPauseTransformFeedback (శూన్య);
GL_APICALL శూన్య GL_APIENTRY glResumeTransformFeedback (శూన్య);
GL_APICALL శూన్య GL_APIENTRY gl_Get_కార్యక్రమం_ద్విమాన (GLuint కార్యక్రమం, GLsizei buf_కొలత, GLsizei *నిడివి, GLenum *ద్విమాన_Format, శూన్య *ద్విమాన);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_ద్విమాన (GLuint కార్యక్రమం, GLenum ద్విమాన_Format, స్థిరరాశి శూన్య *ద్విమాన, GLsizei నిడివి);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Parameteri (GLuint కార్యక్రమం, GLenum pname, GLint విలువ);
GL_APICALL శూన్య GL_APIENTRY glInvalidateFramebuffer (GLenum లక్ష్యం, GLsizei అంకె_Attachments, స్థిరరాశి GLenum *attachments);
GL_APICALL శూన్య GL_APIENTRY glInvalidateSubFramebuffer (GLenum లక్ష్యం, GLsizei అంకె_Attachments, స్థిరరాశి GLenum *attachments, GLint x, GLint y, GLsizei వెడల్పు, GLsizei ఎత్తు);
GL_APICALL శూన్య GL_APIENTRY glTexStorage2D (GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు);
GL_APICALL శూన్య GL_APIENTRY glTexStorage3D (GLenum లక్ష్యం, GLsizei స్థాయిలు, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2);
GL_APICALL శూన్య GL_APIENTRY glGetInternalformativ (GLenum లక్ష్యం, GLenum internalformat, GLenum pname, GLsizei లెక్క, GLint *params);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_ES_VERSION_3_0 */

#నిర్వచితం_కాకపోతే GL_ES_సంస్కరణ_3_1
#నిర్వచించు GL_ES_సంస్కరణ_3_1 1
#నిర్వచించు GL_COMPUTE_SHADER                 0x91B9
#నిర్వచించు GL_MAX_COMPUTE_ఏకరీతి_ఖండాలు     0x91BB
#నిర్వచించు GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS 0x91BC
#నిర్వచించు GL_MAX_COMPUTE_IMAGE_UNIFORMS     0x91BD
#నిర్వచించు GL_MAX_COMPUTE_SHARED_జ్ఞాపకం_కొలత 0x8262
#నిర్వచించు GL_MAX_COMPUTE_ఏకరీతి_COMPONENTS 0x8263
#నిర్వచించు GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS 0x8264
#నిర్వచించు GL_MAX_COMPUTE_ATOMIC_COUNTERS    0x8265
#నిర్వచించు GL_MAX_COMBINED_COMPUTE_ఏకరీతి_COMPONENTS 0x8266
#నిర్వచించు GL_MAX_COMPUTE_WORK_సమూహం_INVOCATIONS 0x90EB
#నిర్వచించు GL_MAX_COMPUTE_WORK_సమూహం_లెక్క   0x91BE
#నిర్వచించు GL_MAX_COMPUTE_WORK_సమూహం_కొలత    0x91BF
#నిర్వచించు GL_COMPUTE_WORK_సమూహం_కొలత        0x8267
#నిర్వచించు GL_DISPATCH_పరోక్ష_బఫరు       0x90EE
#నిర్వచించు GL_DISPATCH_పరోక్ష_బఫరు_BINDING 0x90EF
#నిర్వచించు GL_COMPUTE_SHADER_బిట్టు             0x00000020
#నిర్వచించు GL_DRAW_పరోక్ష_బఫరు           0x8F3F
#నిర్వచించు GL_DRAW_పరోక్ష_బఫరు_BINDING   0x8F43
#నిర్వచించు GL_MAX_ఏకరీతి_LOCATIONS          0x826E
#నిర్వచించు GL_FRAMEBUFFER_DEFAULT_వెడల్పు      0x9310
#నిర్వచించు GL_FRAMEBUFFER_DEFAULT_ఎత్తు     0x9311
#నిర్వచించు GL_FRAMEBUFFER_DEFAULT_SAMPLES    0x9313
#నిర్వచించు GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS 0x9314
#నిర్వచించు GL_MAX_FRAMEBUFFER_వెడల్పు          0x9315
#నిర్వచించు GL_MAX_FRAMEBUFFER_ఎత్తు         0x9316
#నిర్వచించు GL_MAX_FRAMEBUFFER_SAMPLES        0x9318
#నిర్వచించు GL_ఏకరీతి                        0x92E1
#నిర్వచించు GL_ఏకరీతి_ఖండం                  0x92E2
#నిర్వచించు GL_కార్యక్రమం_ఆదానం                  0x92E3
#నిర్వచించు GL_కార్యక్రమం_OUTPUT                 0x92E4
#నిర్వచించు GL_బఫరు_VARIABLE                0x92E5
#నిర్వచించు GL_SHADER_STORAGE_ఖండం           0x92E6
#నిర్వచించు GL_ATOMIC_COUNTER_బఫరు          0x92C0
#నిర్వచించు GL_TRANSFORM_FEEDBACK_VARYING     0x92F4
#నిర్వచించు GL_చురుకైన_RESOURCES               0x92F5
#నిర్వచించు GL_MAX_NAME_నిడివి                0x92F6
#నిర్వచించు GL_MAX_అంకె_చురుకైన_VARIABLES       0x92F7
#నిర్వచించు GL_NAME_నిడివి                    0x92F9
#నిర్వచించు GL_TYPE                           0x92FA
#నిర్వచించు GL_ARRAY_కొలత                     0x92FB
#నిర్వచించు GL_స్థానభ్రంశం                         0x92FC
#నిర్వచించు GL_ఖండం_సూచీ                    0x92FD
#నిర్వచించు GL_ARRAY_STRIDE                   0x92FE
#నిర్వచించు GL_మాతృక_STRIDE                  0x92FF
#నిర్వచించు GL_IS_అడ్డువరుస_MAJOR                   0x9300
#నిర్వచించు GL_ATOMIC_COUNTER_బఫరు_సూచీ    0x9301
#నిర్వచించు GL_బఫరు_BINDING                 0x9302
#నిర్వచించు GL_బఫరు_దత్తాంశం_కొలత               0x9303
#నిర్వచించు GL_అంకె_చురుకైన_VARIABLES           0x9304
#నిర్వచించు GL_చురుకైన_VARIABLES               0x9305
#నిర్వచించు GL_REFERENCED_BY_శీర్షం_SHADER    0x9306
#నిర్వచించు GL_REFERENCED_BY_FRAGMENT_SHADER  0x930A
#నిర్వచించు GL_REFERENCED_BY_COMPUTE_SHADER   0x930B
#నిర్వచించు GL_శిఖరం_LEVEL_ARRAY_కొలత           0x930C
#నిర్వచించు GL_శిఖరం_LEVEL_ARRAY_STRIDE         0x930D
#నిర్వచించు GL_LOCATION                       0x930E
#నిర్వచించు GL_శీర్షం_SHADER_బిట్టు              0x00000001
#నిర్వచించు GL_FRAGMENT_SHADER_బిట్టు            0x00000002
#నిర్వచించు GL_ALL_SHADER_బిట్లు                0xFFFFFFFF
#నిర్వచించు GL_కార్యక్రమం_SEPARABLE              0x8258
#నిర్వచించు GL_చురుకైన_కార్యక్రమం                 0x8259
#నిర్వచించు GL_కార్యక్రమం_PIPELINE_BINDING       0x825A
#నిర్వచించు GL_ATOMIC_COUNTER_బఫరు_BINDING  0x92C1
#నిర్వచించు GL_ATOMIC_COUNTER_బఫరు_ప్రారంభం    0x92C2
#నిర్వచించు GL_ATOMIC_COUNTER_బఫరు_కొలత     0x92C3
#నిర్వచించు GL_MAX_శీర్షం_ATOMIC_COUNTER_BUFFERS 0x92CC
#నిర్వచించు GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS 0x92D0
#నిర్వచించు GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS 0x92D1
#నిర్వచించు GL_MAX_శీర్షం_ATOMIC_COUNTERS     0x92D2
#నిర్వచించు GL_MAX_FRAGMENT_ATOMIC_COUNTERS   0x92D6
#నిర్వచించు GL_MAX_COMBINED_ATOMIC_COUNTERS   0x92D7
#నిర్వచించు GL_MAX_ATOMIC_COUNTER_బఫరు_కొలత 0x92D8
#నిర్వచించు GL_MAX_ATOMIC_COUNTER_బఫరు_BINDINGS 0x92DC
#నిర్వచించు GL_చురుకైన_ATOMIC_COUNTER_BUFFERS  0x92D9
#నిర్వచించు GL_UNSIGNED_INT_ATOMIC_COUNTER    0x92DB
#నిర్వచించు GL_MAX_IMAGE_UNITS                0x8F38
#నిర్వచించు GL_MAX_శీర్షం_IMAGE_UNIFORMS      0x90CA
#నిర్వచించు GL_MAX_FRAGMENT_IMAGE_UNIFORMS    0x90CE
#నిర్వచించు GL_MAX_COMBINED_IMAGE_UNIFORMS    0x90CF
#నిర్వచించు GL_IMAGE_BINDING_NAME             0x8F3A
#నిర్వచించు GL_IMAGE_BINDING_LEVEL            0x8F3B
#నిర్వచించు GL_IMAGE_BINDING_LAYERED          0x8F3C
#నిర్వచించు GL_IMAGE_BINDING_LAYER            0x8F3D
#నిర్వచించు GL_IMAGE_BINDING_ACCESS           0x8F3E
#నిర్వచించు GL_IMAGE_BINDING_FORMAT           0x906E
#నిర్వచించు GL_శీర్షం_ATTRIB_ARRAY_BARRIER_బిట్టు 0x00000001
#నిర్వచించు GL_ELEMENT_ARRAY_BARRIER_బిట్టు      0x00000002
#నిర్వచించు GL_ఏకరీతి_BARRIER_బిట్టు            0x00000004
#నిర్వచించు GL_TEXTURE_FETCH_BARRIER_బిట్టు      0x00000008
#నిర్వచించు GL_SHADER_IMAGE_ACCESS_BARRIER_బిట్టు 0x00000020
#నిర్వచించు GL_COMMAND_BARRIER_బిట్టు            0x00000040
#నిర్వచించు GL_PIXEL_బఫరు_BARRIER_బిట్టు       0x00000080
#నిర్వచించు GL_TEXTURE_UPDATE_BARRIER_బిట్టు     0x00000100
#నిర్వచించు GL_బఫరు_UPDATE_BARRIER_బిట్టు      0x00000200
#నిర్వచించు GL_FRAMEBUFFER_BARRIER_బిట్టు        0x00000400
#నిర్వచించు GL_TRANSFORM_FEEDBACK_BARRIER_బిట్టు 0x00000800
#నిర్వచించు GL_ATOMIC_COUNTER_BARRIER_బిట్టు     0x00001000
#నిర్వచించు GL_ALL_BARRIER_బిట్లు               0xFFFFFFFF
#నిర్వచించు GL_IMAGE_2D                       0x904D
#నిర్వచించు GL_IMAGE_3D                       0x904E
#నిర్వచించు GL_IMAGE_CUBE                     0x9050
#నిర్వచించు GL_IMAGE_2D_ARRAY                 0x9053
#నిర్వచించు GL_INT_IMAGE_2D                   0x9058
#నిర్వచించు GL_INT_IMAGE_3D                   0x9059
#నిర్వచించు GL_INT_IMAGE_CUBE                 0x905B
#నిర్వచించు GL_INT_IMAGE_2D_ARRAY             0x905E
#నిర్వచించు GL_UNSIGNED_INT_IMAGE_2D          0x9063
#నిర్వచించు GL_UNSIGNED_INT_IMAGE_3D          0x9064
#నిర్వచించు GL_UNSIGNED_INT_IMAGE_CUBE        0x9066
#నిర్వచించు GL_UNSIGNED_INT_IMAGE_2D_ARRAY    0x9069
#నిర్వచించు GL_IMAGE_FORMAT_COMPATIBILITY_TYPE 0x90C7
#నిర్వచించు GL_IMAGE_FORMAT_COMPATIBILITY_BY_కొలత 0x90C8
#నిర్వచించు GL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS 0x90C9
#నిర్వచించు GL_READ_ONLY                      0x88B8
#నిర్వచించు GL_WRITE_ONLY                     0x88B9
#నిర్వచించు GL_READ_WRITE                     0x88BA
#నిర్వచించు GL_SHADER_STORAGE_బఫరు          0x90D2
#నిర్వచించు GL_SHADER_STORAGE_బఫరు_BINDING  0x90D3
#నిర్వచించు GL_SHADER_STORAGE_బఫరు_ప్రారంభం    0x90D4
#నిర్వచించు GL_SHADER_STORAGE_బఫరు_కొలత     0x90D5
#నిర్వచించు GL_MAX_శీర్షం_SHADER_STORAGE_ఖండాలు 0x90D6
#నిర్వచించు GL_MAX_FRAGMENT_SHADER_STORAGE_ఖండాలు 0x90DA
#నిర్వచించు GL_MAX_COMPUTE_SHADER_STORAGE_ఖండాలు 0x90DB
#నిర్వచించు GL_MAX_COMBINED_SHADER_STORAGE_ఖండాలు 0x90DC
#నిర్వచించు GL_MAX_SHADER_STORAGE_బఫరు_BINDINGS 0x90DD
#నిర్వచించు GL_MAX_SHADER_STORAGE_ఖండం_కొలత  0x90DE
#నిర్వచించు GL_SHADER_STORAGE_బఫరు_స్థానభ్రంశం_ALIGNMENT 0x90DF
#నిర్వచించు GL_SHADER_STORAGE_BARRIER_బిట్టు     0x00002000
#నిర్వచించు GL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES 0x8F39
#నిర్వచించు GL_లోతు_STENCIL_TEXTURE_బహుళకం     0x90EA
#నిర్వచించు GL_STENCIL_సూచీ                  0x1901
#నిర్వచించు GL_MIN_కార్యక్రమం_TEXTURE_GATHER_స్థానభ్రంశం 0x8E5E
#నిర్వచించు GL_MAX_కార్యక్రమం_TEXTURE_GATHER_స్థానభ్రంశం 0x8E5F
#నిర్వచించు GL_SAMPLE_POSITION                0x8E50
#నిర్వచించు GL_SAMPLE_ముసుగు                    0x8E51
#నిర్వచించు GL_SAMPLE_ముసుగు_విలువ              0x8E52
#నిర్వచించు GL_TEXTURE_2D_MULTISAMPLE         0x9100
#నిర్వచించు GL_MAX_SAMPLE_ముసుగు_పదాలు          0x8E59
#నిర్వచించు GL_MAX_COLOR_TEXTURE_SAMPLES      0x910E
#నిర్వచించు GL_MAX_లోతు_TEXTURE_SAMPLES      0x910F
#నిర్వచించు GL_MAX_INTEGER_SAMPLES            0x9110
#నిర్వచించు GL_TEXTURE_BINDING_2D_MULTISAMPLE 0x9104
#నిర్వచించు GL_TEXTURE_SAMPLES                0x9106
#నిర్వచించు GL_TEXTURE_FIXED_SAMPLE_LOCATIONS 0x9107
#నిర్వచించు GL_TEXTURE_వెడల్పు                  0x1000
#నిర్వచించు GL_TEXTURE_ఎత్తు                 0x1001
#నిర్వచించు GL_TEXTURE_లోతు                  0x8071
#నిర్వచించు GL_TEXTURE_అంతర్గత_FORMAT        0x1003
#నిర్వచించు GL_TEXTURE_RED_కొలత               0x805C
#నిర్వచించు GL_TEXTURE_GREEN_కొలత             0x805D
#నిర్వచించు GL_TEXTURE_BLUE_కొలత              0x805E
#నిర్వచించు GL_TEXTURE_ALPHA_కొలత             0x805F
#నిర్వచించు GL_TEXTURE_లోతు_కొలత             0x884A
#నిర్వచించు GL_TEXTURE_STENCIL_కొలత           0x88F1
#నిర్వచించు GL_TEXTURE_SHARED_కొలత            0x8C3F
#నిర్వచించు GL_TEXTURE_RED_TYPE               0x8C10
#నిర్వచించు GL_TEXTURE_GREEN_TYPE             0x8C11
#నిర్వచించు GL_TEXTURE_BLUE_TYPE              0x8C12
#నిర్వచించు GL_TEXTURE_ALPHA_TYPE             0x8C13
#నిర్వచించు GL_TEXTURE_లోతు_TYPE             0x8C16
#నిర్వచించు GL_TEXTURE_COMPRESSED             0x86A1
#నిర్వచించు GL_SAMPLER_2D_MULTISAMPLE         0x9108
#నిర్వచించు GL_INT_SAMPLER_2D_MULTISAMPLE     0x9109
#నిర్వచించు GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE 0x910A
#నిర్వచించు GL_శీర్షం_ATTRIB_BINDING          0x82D4
#నిర్వచించు GL_శీర్షం_ATTRIB_RELATIVE_స్థానభ్రంశం  0x82D5
#నిర్వచించు GL_శీర్షం_BINDING_భాజకం         0x82D6
#నిర్వచించు GL_శీర్షం_BINDING_స్థానభ్రంశం          0x82D7
#నిర్వచించు GL_శీర్షం_BINDING_STRIDE          0x82D8
#నిర్వచించు GL_శీర్షం_BINDING_బఫరు          0x8F4F
#నిర్వచించు GL_MAX_శీర్షం_ATTRIB_RELATIVE_స్థానభ్రంశం 0x82D9
#నిర్వచించు GL_MAX_శీర్షం_ATTRIB_BINDINGS     0x82DA
#నిర్వచించు GL_MAX_శీర్షం_ATTRIB_STRIDE       0x82E5
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDISPATCHCOMPUTEPROC) (GLuint అంకె_groups_x, GLuint అంకె_groups_y, GLuint అంకె_groups_z);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDISPATCHCOMPUTEINDIRECTPROC) (GLintptr పరోక్ష);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWARRAYSINDIRECTPROC) (GLenum బహుళకం, స్థిరరాశి శూన్య *పరోక్ష);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWELEMENTSINDIRECTPROC) (GLenum బహుళకం, GLenum type, స్థిరరాశి శూన్య *పరోక్ష);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFRAMEBUFFERPARAMETERIPROC) (GLenum లక్ష్యం, GLenum pname, GLint param);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETFRAMEBUFFERPARAMETERIVPROC) (GLenum లక్ష్యం, GLenum pname, GLint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETPROGRAMINTERFACEIVPROC) (GLuint కార్యక్రమం, GLenum కార్యక్రమం_Interface, GLenum pname, GLint *params);
రకనిర్వచనం GLuint (GL_APIENTRYP PFNGLGETPROGRAMRESOURCEINDEXPROC) (GLuint కార్యక్రమం, GLenum కార్యక్రమం_Interface, స్థిరరాశి GLchar *name);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETPROGRAMRESOURCENAMEPROC) (GLuint కార్యక్రమం, GLenum కార్యక్రమం_Interface, GLuint సూచీ, GLsizei buf_కొలత, GLsizei *నిడివి, GLchar *name);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETPROGRAMRESOURCEIVPROC) (GLuint కార్యక్రమం, GLenum కార్యక్రమం_Interface, GLuint సూచీ, GLsizei prop_లెక్క, స్థిరరాశి GLenum *props, GLsizei లెక్క, GLsizei *నిడివి, GLint *params);
రకనిర్వచనం GLint (GL_APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONPROC) (GLuint కార్యక్రమం, GLenum కార్యక్రమం_Interface, స్థిరరాశి GLchar *name);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLUSEPROGRAMSTAGESPROC) (GLuint pipeline, GLbitfield stages, GLuint కార్యక్రమం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLACTIVESHADERPROGRAMPROC) (GLuint pipeline, GLuint కార్యక్రమం);
రకనిర్వచనం GLuint (GL_APIENTRYP PFNGLCREATESHADERPROGRAMVPROC) (GLenum type, GLsizei లెక్క, స్థిరరాశి GLchar *స్థిరరాశి*అక్షరశ్రేణులు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBINDPROGRAMPIPELINEPROC) (GLuint pipeline);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDELETEPROGRAMPIPELINESPROC) (GLsizei n, స్థిరరాశి GLuint *pipelines);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGENPROGRAMPIPELINESPROC) (GLsizei n, GLuint *pipelines);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLISPROGRAMPIPELINEPROC) (GLuint pipeline);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETPROGRAMPIPELINEIVPROC) (GLuint pipeline, GLenum pname, GLint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM1IPROC) (GLuint కార్యక్రమం, GLint location, GLint v0);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM2IPROC) (GLuint కార్యక్రమం, GLint location, GLint v0, GLint v1);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM3IPROC) (GLuint కార్యక్రమం, GLint location, GLint v0, GLint v1, GLint v2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM4IPROC) (GLuint కార్యక్రమం, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UIPROC) (GLuint కార్యక్రమం, GLint location, GLuint v0);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UIPROC) (GLuint కార్యక్రమం, GLint location, GLuint v0, GLuint v1);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UIPROC) (GLuint కార్యక్రమం, GLint location, GLuint v0, GLuint v1, GLuint v2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UIPROC) (GLuint కార్యక్రమం, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM1FPROC) (GLuint కార్యక్రమం, GLint location, GLfloat v0);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM2FPROC) (GLuint కార్యక్రమం, GLint location, GLfloat v0, GLfloat v1);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM3FPROC) (GLuint కార్యక్రమం, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM4FPROC) (GLuint కార్యక్రమం, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM1IVPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLint *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM2IVPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLint *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM3IVPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLint *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM4IVPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLint *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UIVPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLuint *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UIVPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLuint *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UIVPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLuint *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UIVPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLuint *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM1FVPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM2FVPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM3FVPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORM4FVPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2FVPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3FVPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4FVPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC) (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLVALIDATEPROGRAMPIPELINEPROC) (GLuint pipeline);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETPROGRAMPIPELINEINFOLOGPROC) (GLuint pipeline, GLsizei buf_కొలత, GLsizei *నిడివి, GLchar *infoLog);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBINDIMAGETEXTUREPROC) (GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETBOOLEANI_VPROC) (GLenum లక్ష్యం, GLuint సూచీ, GLboolean *దత్తాంశం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMEMORYBARRIERPROC) (GLbitfield barriers);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMEMORYBARRIERBYREGIONPROC) (GLbitfield barriers);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXSTORAGE2DMULTISAMPLEPROC) (GLenum లక్ష్యం, GLsizei samples, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు, GLboolean fixedsamplelocations);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETMULTISAMPLEFVPROC) (GLenum pname, GLuint సూచీ, GLfloat *val);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSAMPLEMASKIPROC) (GLuint ముసుగు_సంఖ్య, GLbitfield ముసుగు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETTEXLEVELPARAMETERIVPROC) (GLenum లక్ష్యం, GLint level, GLenum pname, GLint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETTEXLEVELPARAMETERFVPROC) (GLenum లక్ష్యం, GLint level, GLenum pname, GLfloat *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBINDVERTEXBUFFERPROC) (GLuint bindingindex, GLuint బఫరు_2, GLintptr స్థానభ్రంశం_2, GLsizei stride);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLVERTEXATTRIBFORMATPROC) (GLuint attribindex, GLint కొలత, GLenum type, GLboolean normalized, GLuint relativeoffset);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLVERTEXATTRIBIFORMATPROC) (GLuint attribindex, GLint కొలత, GLenum type, GLuint relativeoffset);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLVERTEXATTRIBBINDINGPROC) (GLuint attribindex, GLuint bindingindex);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLVERTEXBINDINGDIVISORPROC) (GLuint bindingindex, GLuint భాజకం);
#ఒకవేళ GL_GLES_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glDispatchCompute (GLuint అంకె_groups_x, GLuint అంకె_groups_y, GLuint అంకె_groups_z);
GL_APICALL శూన్య GL_APIENTRY gl_Dispatch_Compute_పరోక్ష (GLintptr పరోక్ష);
GL_APICALL శూన్య GL_APIENTRY gl_Draw_Arrays_పరోక్ష (GLenum బహుళకం, స్థిరరాశి శూన్య *పరోక్ష);
GL_APICALL శూన్య GL_APIENTRY gl_Draw_Elements_పరోక్ష (GLenum బహుళకం, GLenum type, స్థిరరాశి శూన్య *పరోక్ష);
GL_APICALL శూన్య GL_APIENTRY glFramebufferParameteri (GLenum లక్ష్యం, GLenum pname, GLint param);
GL_APICALL శూన్య GL_APIENTRY glGetFramebufferParameteriv (GLenum లక్ష్యం, GLenum pname, GLint *params);
GL_APICALL శూన్య GL_APIENTRY gl_Get_కార్యక్రమం_Interfaceiv (GLuint కార్యక్రమం, GLenum కార్యక్రమం_Interface, GLenum pname, GLint *params);
GL_APICALL GLuint GL_APIENTRY gl_Get_కార్యక్రమం_Resource_సూచీ (GLuint కార్యక్రమం, GLenum కార్యక్రమం_Interface, స్థిరరాశి GLchar *name);
GL_APICALL శూన్య GL_APIENTRY gl_Get_కార్యక్రమం_Resource_Name (GLuint కార్యక్రమం, GLenum కార్యక్రమం_Interface, GLuint సూచీ, GLsizei buf_కొలత, GLsizei *నిడివి, GLchar *name);
GL_APICALL శూన్య GL_APIENTRY gl_Get_కార్యక్రమం_Resourceiv (GLuint కార్యక్రమం, GLenum కార్యక్రమం_Interface, GLuint సూచీ, GLsizei prop_లెక్క, స్థిరరాశి GLenum *props, GLsizei లెక్క, GLsizei *నిడివి, GLint *params);
GL_APICALL GLint GL_APIENTRY gl_Get_కార్యక్రమం_Resource_Location (GLuint కార్యక్రమం, GLenum కార్యక్రమం_Interface, స్థిరరాశి GLchar *name);
GL_APICALL శూన్య GL_APIENTRY gl_Use_కార్యక్రమం_Stages (GLuint pipeline, GLbitfield stages, GLuint కార్యక్రమం);
GL_APICALL శూన్య GL_APIENTRY gl_చురుకైన_Shader_కార్యక్రమం (GLuint pipeline, GLuint కార్యక్రమం);
GL_APICALL GLuint GL_APIENTRY glCreateShaderProgramv (GLenum type, GLsizei లెక్క, స్థిరరాశి GLchar *స్థిరరాశి*అక్షరశ్రేణులు);
GL_APICALL శూన్య GL_APIENTRY gl_Bind_కార్యక్రమం_Pipeline (GLuint pipeline);
GL_APICALL శూన్య GL_APIENTRY gl_Delete_కార్యక్రమం_Pipelines (GLsizei n, స్థిరరాశి GLuint *pipelines);
GL_APICALL శూన్య GL_APIENTRY gl_Gen_కార్యక్రమం_Pipelines (GLsizei n, GLuint *pipelines);
GL_APICALL GLboolean GL_APIENTRY gl_Is_కార్యక్రమం_Pipeline (GLuint pipeline);
GL_APICALL శూన్య GL_APIENTRY gl_Get_కార్యక్రమం_Pipelineiv (GLuint pipeline, GLenum pname, GLint *params);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform1i (GLuint కార్యక్రమం, GLint location, GLint v0);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform2i (GLuint కార్యక్రమం, GLint location, GLint v0, GLint v1);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform3i (GLuint కార్యక్రమం, GLint location, GLint v0, GLint v1, GLint v2);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform4i (GLuint కార్యక్రమం, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform1ui (GLuint కార్యక్రమం, GLint location, GLuint v0);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform2ui (GLuint కార్యక్రమం, GLint location, GLuint v0, GLuint v1);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform3ui (GLuint కార్యక్రమం, GLint location, GLuint v0, GLuint v1, GLuint v2);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform4ui (GLuint కార్యక్రమం, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform1f (GLuint కార్యక్రమం, GLint location, GLfloat v0);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform2f (GLuint కార్యక్రమం, GLint location, GLfloat v0, GLfloat v1);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform3f (GLuint కార్యక్రమం, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform4f (GLuint కార్యక్రమం, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform1iv (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLint *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform2iv (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLint *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform3iv (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLint *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform4iv (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLint *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform1uiv (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLuint *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform2uiv (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLuint *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform3uiv (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLuint *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform4uiv (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLuint *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform1fv (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform2fv (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform3fv (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_Uniform4fv (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_ఏకరీతి_Matrix2fv (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_ఏకరీతి_Matrix3fv (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_ఏకరీతి_Matrix4fv (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_ఏకరీతి_Matrix2x3fv (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_ఏకరీతి_Matrix3x2fv (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_ఏకరీతి_Matrix2x4fv (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_ఏకరీతి_Matrix4x2fv (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_ఏకరీతి_Matrix3x4fv (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_కార్యక్రమం_ఏకరీతి_Matrix4x3fv (GLuint కార్యక్రమం, GLint location, GLsizei లెక్క, GLboolean transpose, స్థిరరాశి GLfloat *విలువ);
GL_APICALL శూన్య GL_APIENTRY gl_Validate_కార్యక్రమం_Pipeline (GLuint pipeline);
GL_APICALL శూన్య GL_APIENTRY gl_Get_కార్యక్రమం_Pipeline_Info_Log (GLuint pipeline, GLsizei buf_కొలత, GLsizei *నిడివి, GLchar *infoLog);
GL_APICALL శూన్య GL_APIENTRY glBindImageTexture (GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
GL_APICALL శూన్య GL_APIENTRY glGetBooleani_v (GLenum లక్ష్యం, GLuint సూచీ, GLboolean *దత్తాంశం);
GL_APICALL శూన్య GL_APIENTRY gl_జ్ఞాపకం_Barrier (GLbitfield barriers);
GL_APICALL శూన్య GL_APIENTRY gl_జ్ఞాపకం_Barrier_By_Region (GLbitfield barriers);
GL_APICALL శూన్య GL_APIENTRY glTexStorage2DMultisample (GLenum లక్ష్యం, GLsizei samples, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు, GLboolean fixedsamplelocations);
GL_APICALL శూన్య GL_APIENTRY glGetMultisamplefv (GLenum pname, GLuint సూచీ, GLfloat *val);
GL_APICALL శూన్య GL_APIENTRY glSampleMaski (GLuint ముసుగు_సంఖ్య, GLbitfield ముసుగు);
GL_APICALL శూన్య GL_APIENTRY glGetTexLevelParameteriv (GLenum లక్ష్యం, GLint level, GLenum pname, GLint *params);
GL_APICALL శూన్య GL_APIENTRY glGetTexLevelParameterfv (GLenum లక్ష్యం, GLint level, GLenum pname, GLfloat *params);
GL_APICALL శూన్య GL_APIENTRY gl_Bind_శీర్షం_బఫరు (GLuint bindingindex, GLuint బఫరు_2, GLintptr స్థానభ్రంశం_2, GLsizei stride);
GL_APICALL శూన్య GL_APIENTRY gl_శీర్షం_Attrib_Format (GLuint attribindex, GLint కొలత, GLenum type, GLboolean normalized, GLuint relativeoffset);
GL_APICALL శూన్య GL_APIENTRY gl_శీర్షం_Attrib_IFormat (GLuint attribindex, GLint కొలత, GLenum type, GLuint relativeoffset);
GL_APICALL శూన్య GL_APIENTRY gl_శీర్షం_Attrib_Binding (GLuint attribindex, GLuint bindingindex);
GL_APICALL శూన్య GL_APIENTRY gl_శీర్షం_Binding_భాజకం (GLuint bindingindex, GLuint భాజకం);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_ES_VERSION_3_1 */

#నిర్వచితం_కాకపోతే GL_ES_సంస్కరణ_3_2
#నిర్వచించు GL_ES_సంస్కరణ_3_2 1
రకనిర్వచనం శూన్య (GL_APIENTRY  *GLDEBUGPROC)(GLenum ఆధారం,GLenum type,GLuint id,GLenum severity,GLsizei నిడివి,స్థిరరాశి GLchar *సందేశం,స్థిరరాశి శూన్య *userParam);
#నిర్వచించు GL_MULTISAMPLE_పంక్తి_వెడల్పు_RANGE   0x9381
#నిర్వచించు GL_MULTISAMPLE_పంక్తి_వెడల్పు_GRANULARITY 0x9382
#నిర్వచించు GL_MULTIPLY                       0x9294
#నిర్వచించు GL_SCREEN                         0x9295
#నిర్వచించు GL_OVERLAY                        0x9296
#నిర్వచించు GL_DARKEN                         0x9297
#నిర్వచించు GL_LIGHTEN                        0x9298
#నిర్వచించు GL_COLORDODGE                     0x9299
#నిర్వచించు GL_COLORBURN                      0x929A
#నిర్వచించు GL_HARDLIGHT                      0x929B
#నిర్వచించు GL_SOFTLIGHT                      0x929C
#నిర్వచించు GL_DIFFERENCE                     0x929E
#నిర్వచించు GL_EXCLUSION                      0x92A0
#నిర్వచించు GL_HSL_HUE                        0x92AD
#నిర్వచించు GL_HSL_SATURATION                 0x92AE
#నిర్వచించు GL_HSL_COLOR                      0x92AF
#నిర్వచించు GL_HSL_LUMINOSITY                 0x92B0
#నిర్వచించు GL_DEBUG_OUTPUT_SYNCHRONOUS       0x8242
#నిర్వచించు GL_DEBUG_తదుపరి_LOGGED_సందేశం_నిడివి 0x8243
#నిర్వచించు GL_DEBUG_CALLBACK_FUNCTION        0x8244
#నిర్వచించు GL_DEBUG_CALLBACK_USER_PARAM      0x8245
#నిర్వచించు GL_DEBUG_ఆధారం_API               0x8246
#నిర్వచించు GL_DEBUG_ఆధారం_కిటికీ_SYSTEM     0x8247
#నిర్వచించు GL_DEBUG_ఆధారం_SHADER_COMPILER   0x8248
#నిర్వచించు GL_DEBUG_ఆధారం_మూడవ_PARTY       0x8249
#నిర్వచించు GL_DEBUG_ఆధారం_APPLICATION       0x824A
#నిర్వచించు GL_DEBUG_ఆధారం_OTHER             0x824B
#నిర్వచించు GL_DEBUG_TYPE_ERROR               0x824C
#నిర్వచించు GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR 0x824D
#నిర్వచించు GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR  0x824E
#నిర్వచించు GL_DEBUG_TYPE_PORTABILITY         0x824F
#నిర్వచించు GL_DEBUG_TYPE_PERFORMANCE         0x8250
#నిర్వచించు GL_DEBUG_TYPE_OTHER               0x8251
#నిర్వచించు GL_DEBUG_TYPE_MARKER              0x8268
#నిర్వచించు GL_DEBUG_TYPE_నెట్టు_సమూహం          0x8269
#నిర్వచించు GL_DEBUG_TYPE_తీయి_సమూహం           0x826A
#నిర్వచించు GL_DEBUG_SEVERITY_NOTIFICATION    0x826B
#నిర్వచించు GL_MAX_DEBUG_సమూహం_దొంతర_లోతు    0x826C
#నిర్వచించు GL_DEBUG_సమూహం_దొంతర_లోతు        0x826D
#నిర్వచించు GL_బఫరు                         0x82E0
#నిర్వచించు GL_SHADER                         0x82E1
#నిర్వచించు GL_కార్యక్రమం                        0x82E2
#నిర్వచించు GL_శీర్షం_ARRAY                   0x8074
#నిర్వచించు GL_QUERY                          0x82E3
#నిర్వచించు GL_కార్యక్రమం_PIPELINE               0x82E4
#నిర్వచించు GL_SAMPLER                        0x82E6
#నిర్వచించు GL_MAX_LABEL_నిడివి               0x82E8
#నిర్వచించు GL_MAX_DEBUG_సందేశం_నిడివి       0x9143
#నిర్వచించు GL_MAX_DEBUG_LOGGED_MESSAGES      0x9144
#నిర్వచించు GL_DEBUG_LOGGED_MESSAGES          0x9145
#నిర్వచించు GL_DEBUG_SEVERITY_ఎగువ            0x9146
#నిర్వచించు GL_DEBUG_SEVERITY_MEDIUM          0x9147
#నిర్వచించు GL_DEBUG_SEVERITY_దిగువ             0x9148
#నిర్వచించు GL_DEBUG_OUTPUT                   0x92E0
#నిర్వచించు GL_CONTEXT_FLAG_DEBUG_బిట్టు         0x00000002
#నిర్వచించు GL_దొంతర_అధికప్రవాహం                 0x0503
#నిర్వచించు GL_దొంతర_UNDERFLOW                0x0504
#నిర్వచించు GL_GEOMETRY_SHADER                0x8DD9
#నిర్వచించు GL_GEOMETRY_SHADER_బిట్టు            0x00000004
#నిర్వచించు GL_GEOMETRY_VERTICES_బహిర్గతం          0x8916
#నిర్వచించు GL_GEOMETRY_ఆదానం_TYPE            0x8917
#నిర్వచించు GL_GEOMETRY_OUTPUT_TYPE           0x8918
#నిర్వచించు GL_GEOMETRY_SHADER_INVOCATIONS    0x887F
#నిర్వచించు GL_LAYER_PROVOKING_శీర్షం         0x825E
#నిర్వచించు GL_పంక్తులు_ADJACENCY                0x000A
#నిర్వచించు GL_పంక్తి_STRIP_ADJACENCY           0x000B
#నిర్వచించు GL_TRIANGLES_ADJACENCY            0x000C
#నిర్వచించు GL_TRIANGLE_STRIP_ADJACENCY       0x000D
#నిర్వచించు GL_MAX_GEOMETRY_ఏకరీతి_COMPONENTS 0x8DDF
#నిర్వచించు GL_MAX_GEOMETRY_ఏకరీతి_ఖండాలు    0x8A2C
#నిర్వచించు GL_MAX_COMBINED_GEOMETRY_ఏకరీతి_COMPONENTS 0x8A32
#నిర్వచించు GL_MAX_GEOMETRY_ఆదానం_COMPONENTS  0x9123
#నిర్వచించు GL_MAX_GEOMETRY_OUTPUT_COMPONENTS 0x9124
#నిర్వచించు GL_MAX_GEOMETRY_OUTPUT_VERTICES   0x8DE0
#నిర్వచించు GL_MAX_GEOMETRY_మొత్తం_OUTPUT_COMPONENTS 0x8DE1
#నిర్వచించు GL_MAX_GEOMETRY_SHADER_INVOCATIONS 0x8E5A
#నిర్వచించు GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS 0x8C29
#నిర్వచించు GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS 0x92CF
#నిర్వచించు GL_MAX_GEOMETRY_ATOMIC_COUNTERS   0x92D5
#నిర్వచించు GL_MAX_GEOMETRY_IMAGE_UNIFORMS    0x90CD
#నిర్వచించు GL_MAX_GEOMETRY_SHADER_STORAGE_ఖండాలు 0x90D7
#నిర్వచించు GL_మొదటి_శీర్షం_CONVENTION        0x8E4D
#నిర్వచించు GL_చివరి_శీర్షం_CONVENTION         0x8E4E
#నిర్వచించు GL_UNDEFINED_శీర్షం               0x8260
#నిర్వచించు GL_PRIMITIVES_GENERATED           0x8C87
#నిర్వచించు GL_FRAMEBUFFER_DEFAULT_LAYERS     0x9312
#నిర్వచించు GL_MAX_FRAMEBUFFER_LAYERS         0x9317
#నిర్వచించు GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS 0x8DA8
#నిర్వచించు GL_FRAMEBUFFER_ATTACHMENT_LAYERED 0x8DA7
#నిర్వచించు GL_REFERENCED_BY_GEOMETRY_SHADER  0x9309
#నిర్వచించు GL_PRIMITIVE_BOUNDING_BOX         0x92BE
#నిర్వచించు GL_CONTEXT_FLAG_ROBUST_ACCESS_బిట్టు 0x00000004
#నిర్వచించు GL_CONTEXT_FLAGS                  0x821E
#నిర్వచించు GL_LOSE_CONTEXT_ON_RESET          0x8252
#నిర్వచించు GL_GUILTY_CONTEXT_RESET           0x8253
#నిర్వచించు GL_INNOCENT_CONTEXT_RESET         0x8254
#నిర్వచించు GL_UNKNOWN_CONTEXT_RESET          0x8255
#నిర్వచించు GL_RESET_NOTIFICATION_STRATEGY    0x8256
#నిర్వచించు GL_NO_RESET_NOTIFICATION          0x8261
#నిర్వచించు GL_CONTEXT_కోల్పోయిన                   0x0507
#నిర్వచించు GL_SAMPLE_SHADING                 0x8C36
#నిర్వచించు GL_MIN_SAMPLE_SHADING_విలువ       0x8C37
#నిర్వచించు GL_MIN_FRAGMENT_INTERPOLATION_స్థానభ్రంశం 0x8E5B
#నిర్వచించు GL_MAX_FRAGMENT_INTERPOLATION_స్థానభ్రంశం 0x8E5C
#నిర్వచించు GL_FRAGMENT_INTERPOLATION_స్థానభ్రంశం_బిట్లు 0x8E5D
#నిర్వచించు GL_PATCHES                        0x000E
#నిర్వచించు GL_PATCH_VERTICES                 0x8E72
#నిర్వచించు GL_TESS_CONTROL_OUTPUT_VERTICES   0x8E75
#నిర్వచించు GL_TESS_GEN_బహుళకం                  0x8E76
#నిర్వచించు GL_TESS_GEN_SPACING               0x8E77
#నిర్వచించు GL_TESS_GEN_శీర్షం_క్రమం          0x8E78
#నిర్వచించు GL_TESS_GEN_బిందువు_బహుళకం            0x8E79
#నిర్వచించు GL_ISOLINES                       0x8E7A
#నిర్వచించు GL_QUADS                          0x0007
#నిర్వచించు GL_FRACTIONAL_ODD                 0x8E7B
#నిర్వచించు GL_FRACTIONAL_EVEN                0x8E7C
#నిర్వచించు GL_MAX_PATCH_VERTICES             0x8E7D
#నిర్వచించు GL_MAX_TESS_GEN_LEVEL             0x8E7E
#నిర్వచించు GL_MAX_TESS_CONTROL_ఏకరీతి_COMPONENTS 0x8E7F
#నిర్వచించు GL_MAX_TESS_EVALUATION_ఏకరీతి_COMPONENTS 0x8E80
#నిర్వచించు GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS 0x8E81
#నిర్వచించు GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS 0x8E82
#నిర్వచించు GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS 0x8E83
#నిర్వచించు GL_MAX_TESS_PATCH_COMPONENTS      0x8E84
#నిర్వచించు GL_MAX_TESS_CONTROL_మొత్తం_OUTPUT_COMPONENTS 0x8E85
#నిర్వచించు GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS 0x8E86
#నిర్వచించు GL_MAX_TESS_CONTROL_ఏకరీతి_ఖండాలు 0x8E89
#నిర్వచించు GL_MAX_TESS_EVALUATION_ఏకరీతి_ఖండాలు 0x8E8A
#నిర్వచించు GL_MAX_TESS_CONTROL_ఆదానం_COMPONENTS 0x886C
#నిర్వచించు GL_MAX_TESS_EVALUATION_ఆదానం_COMPONENTS 0x886D
#నిర్వచించు GL_MAX_COMBINED_TESS_CONTROL_ఏకరీతి_COMPONENTS 0x8E1E
#నిర్వచించు GL_MAX_COMBINED_TESS_EVALUATION_ఏకరీతి_COMPONENTS 0x8E1F
#నిర్వచించు GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS 0x92CD
#నిర్వచించు GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS 0x92CE
#నిర్వచించు GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS 0x92D3
#నిర్వచించు GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS 0x92D4
#నిర్వచించు GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS 0x90CB
#నిర్వచించు GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS 0x90CC
#నిర్వచించు GL_MAX_TESS_CONTROL_SHADER_STORAGE_ఖండాలు 0x90D8
#నిర్వచించు GL_MAX_TESS_EVALUATION_SHADER_STORAGE_ఖండాలు 0x90D9
#నిర్వచించు GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED 0x8221
#నిర్వచించు GL_IS_చొప్పున_PATCH                   0x92E7
#నిర్వచించు GL_REFERENCED_BY_TESS_CONTROL_SHADER 0x9307
#నిర్వచించు GL_REFERENCED_BY_TESS_EVALUATION_SHADER 0x9308
#నిర్వచించు GL_TESS_CONTROL_SHADER            0x8E88
#నిర్వచించు GL_TESS_EVALUATION_SHADER         0x8E87
#నిర్వచించు GL_TESS_CONTROL_SHADER_బిట్టు        0x00000008
#నిర్వచించు GL_TESS_EVALUATION_SHADER_బిట్టు     0x00000010
#నిర్వచించు GL_TEXTURE_BORDER_COLOR           0x1004
#నిర్వచించు GL_CLAMP_గమ్యం_BORDER                0x812D
#నిర్వచించు GL_TEXTURE_బఫరు                 0x8C2A
#నిర్వచించు GL_TEXTURE_బఫరు_BINDING         0x8C2A
#నిర్వచించు GL_MAX_TEXTURE_బఫరు_కొలత        0x8C2B
#నిర్వచించు GL_TEXTURE_BINDING_బఫరు         0x8C2C
#నిర్వచించు GL_TEXTURE_బఫరు_దత్తాంశం_STORE_BINDING 0x8C2D
#నిర్వచించు GL_TEXTURE_బఫరు_స్థానభ్రంశం_ALIGNMENT 0x919F
#నిర్వచించు GL_SAMPLER_బఫరు                 0x8DC2
#నిర్వచించు GL_INT_SAMPLER_బఫరు             0x8DD0
#నిర్వచించు GL_UNSIGNED_INT_SAMPLER_బఫరు    0x8DD8
#నిర్వచించు GL_IMAGE_బఫరు                   0x9051
#నిర్వచించు GL_INT_IMAGE_బఫరు               0x905C
#నిర్వచించు GL_UNSIGNED_INT_IMAGE_బఫరు      0x9067
#నిర్వచించు GL_TEXTURE_బఫరు_స్థానభ్రంశం          0x919D
#నిర్వచించు GL_TEXTURE_బఫరు_కొలత            0x919E
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_4x4       0x93B0
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_5x4       0x93B1
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_5x5       0x93B2
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_6x5       0x93B3
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_6x6       0x93B4
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_8x5       0x93B5
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_8x6       0x93B6
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_8x8       0x93B7
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_10x5      0x93B8
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_10x6      0x93B9
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_10x8      0x93BA
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_10x10     0x93BB
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_12x10     0x93BC
#నిర్వచించు GL_COMPRESSED_RGBA_ASTC_12x12     0x93BD
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4 0x93D0
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4 0x93D1
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5 0x93D2
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5 0x93D3
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6 0x93D4
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5 0x93D5
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6 0x93D6
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8 0x93D7
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5 0x93D8
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6 0x93D9
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8 0x93DA
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10 0x93DB
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10 0x93DC
#నిర్వచించు GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12 0x93DD
#నిర్వచించు GL_TEXTURE_CUBE_MAP_ARRAY         0x9009
#నిర్వచించు GL_TEXTURE_BINDING_CUBE_MAP_ARRAY 0x900A
#నిర్వచించు GL_SAMPLER_CUBE_MAP_ARRAY         0x900C
#నిర్వచించు GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW  0x900D
#నిర్వచించు GL_INT_SAMPLER_CUBE_MAP_ARRAY     0x900E
#నిర్వచించు GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY 0x900F
#నిర్వచించు GL_IMAGE_CUBE_MAP_ARRAY           0x9054
#నిర్వచించు GL_INT_IMAGE_CUBE_MAP_ARRAY       0x905F
#నిర్వచించు GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY 0x906A
#నిర్వచించు GL_TEXTURE_2D_MULTISAMPLE_ARRAY   0x9102
#నిర్వచించు GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY 0x9105
#నిర్వచించు GL_SAMPLER_2D_MULTISAMPLE_ARRAY   0x910B
#నిర్వచించు GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910C
#నిర్వచించు GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910D
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBLENDBARRIERPROC) (శూన్య);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCOPYIMAGESUBDATAPROC) (GLuint srcName, GLenum src_లక్ష్యం, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dst_లక్ష్యం, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei src_వెడల్పు, GLsizei src_ఎత్తు, GLsizei src_లోతు);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDEBUGMESSAGECONTROLPROC) (GLenum ఆధారం, GLenum type, GLenum severity, GLsizei లెక్క, స్థిరరాశి GLuint *ids, GLboolean enabled);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDEBUGMESSAGEINSERTPROC) (GLenum ఆధారం, GLenum type, GLuint id, GLenum severity, GLsizei నిడివి, స్థిరరాశి GLchar *buf);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDEBUGMESSAGECALLBACKPROC) (GLDEBUGPROC callback, స్థిరరాశి శూన్య *userParam);
రకనిర్వచనం GLuint (GL_APIENTRYP PFNGLGETDEBUGMESSAGELOGPROC) (GLuint లెక్క, GLsizei buf_కొలత, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *సందేశం_Log);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPUSHDEBUGGROUPPROC) (GLenum ఆధారం, GLuint id, GLsizei నిడివి, స్థిరరాశి GLchar *సందేశం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPOPDEBUGGROUPPROC) (శూన్య);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLOBJECTLABELPROC) (GLenum identifier, GLuint name, GLsizei నిడివి, స్థిరరాశి GLchar *label);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETOBJECTLABELPROC) (GLenum identifier, GLuint name, GLsizei buf_కొలత, GLsizei *నిడివి, GLchar *label);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLOBJECTPTRLABELPROC) (స్థిరరాశి శూన్య *ptr, GLsizei నిడివి, స్థిరరాశి GLchar *label);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETOBJECTPTRLABELPROC) (స్థిరరాశి శూన్య *ptr, GLsizei buf_కొలత, GLsizei *నిడివి, GLchar *label);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETPOINTERVPROC) (GLenum pname, శూన్య **params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLENABLEIPROC) (GLenum లక్ష్యం, GLuint సూచీ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDISABLEIPROC) (GLenum లక్ష్యం, GLuint సూచీ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBLENDEQUATIONIPROC) (GLuint buf, GLenum బహుళకం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEIPROC) (GLuint buf, GLenum బహుళకం_RGB, GLenum బహుళకం_Alpha);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBLENDFUNCIPROC) (GLuint buf, GLenum src, GLenum dst);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEIPROC) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLCOLORMASKIPROC) (GLuint సూచీ, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
రకనిర్వచనం GLboolean (GL_APIENTRYP PFNGLISENABLEDIPROC) (GLenum లక్ష్యం, GLuint సూచీ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWELEMENTSBASEVERTEXPROC) (GLenum బహుళకం, GLsizei లెక్క, GLenum type, స్థిరరాశి శూన్య *indices, GLint basevertex);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC) (GLenum బహుళకం, GLuint ప్రారంభం, GLuint చివర, GLsizei లెక్క, GLenum type, స్థిరరాశి శూన్య *indices, GLint basevertex);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC) (GLenum బహుళకం, GLsizei లెక్క, GLenum type, స్థిరరాశి శూన్య *indices, GLsizei instancecount, GLint basevertex);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREPROC) (GLenum లక్ష్యం, GLenum attachment, GLuint texture, GLint level);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPRIMITIVEBOUNDINGBOXPROC) (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
రకనిర్వచనం GLenum (GL_APIENTRYP PFNGLGETGRAPHICSRESETSTATUSPROC) (శూన్య);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLREADNPIXELSPROC) (GLint x, GLint y, GLsizei వెడల్పు, GLsizei ఎత్తు, GLenum format, GLenum type, GLsizei buf_కొలత, శూన్య *దత్తాంశం);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETNUNIFORMFVPROC) (GLuint కార్యక్రమం, GLint location, GLsizei buf_కొలత, GLfloat *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETNUNIFORMIVPROC) (GLuint కార్యక్రమం, GLint location, GLsizei buf_కొలత, GLint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETNUNIFORMUIVPROC) (GLuint కార్యక్రమం, GLint location, GLsizei buf_కొలత, GLuint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLMINSAMPLESHADINGPROC) (GLfloat విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLPATCHPARAMETERIPROC) (GLenum pname, GLint విలువ);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXPARAMETERIIVPROC) (GLenum లక్ష్యం, GLenum pname, స్థిరరాశి GLint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXPARAMETERIUIVPROC) (GLenum లక్ష్యం, GLenum pname, స్థిరరాశి GLuint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETTEXPARAMETERIIVPROC) (GLenum లక్ష్యం, GLenum pname, GLint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETTEXPARAMETERIUIVPROC) (GLenum లక్ష్యం, GLenum pname, GLuint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSAMPLERPARAMETERIIVPROC) (GLuint sampler, GLenum pname, స్థిరరాశి GLint *param);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLSAMPLERPARAMETERIUIVPROC) (GLuint sampler, GLenum pname, స్థిరరాశి GLuint *param);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIIVPROC) (GLuint sampler, GLenum pname, GLint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIUIVPROC) (GLuint sampler, GLenum pname, GLuint *params);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXBUFFERPROC) (GLenum లక్ష్యం, GLenum internalformat, GLuint బఫరు_2);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXBUFFERRANGEPROC) (GLenum లక్ష్యం, GLenum internalformat, GLuint బఫరు_2, GLintptr స్థానభ్రంశం_2, GLsizeiptr కొలత);
రకనిర్వచనం శూన్య (GL_APIENTRYP PFNGLTEXSTORAGE3DMULTISAMPLEPROC) (GLenum లక్ష్యం, GLsizei samples, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLboolean fixedsamplelocations);
#ఒకవేళ GL_GLES_PROTOTYPES
GL_APICALL శూన్య GL_APIENTRY glBlendBarrier (శూన్య);
GL_APICALL శూన్య GL_APIENTRY gl_Copy_Image_Sub_దత్తాంశం (GLuint srcName, GLenum src_లక్ష్యం, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dst_లక్ష్యం, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei src_వెడల్పు, GLsizei src_ఎత్తు, GLsizei src_లోతు);
GL_APICALL శూన్య GL_APIENTRY gl_Debug_సందేశం_Control (GLenum ఆధారం, GLenum type, GLenum severity, GLsizei లెక్క, స్థిరరాశి GLuint *ids, GLboolean enabled);
GL_APICALL శూన్య GL_APIENTRY gl_Debug_సందేశం_చొప్పించు (GLenum ఆధారం, GLenum type, GLuint id, GLenum severity, GLsizei నిడివి, స్థిరరాశి GLchar *buf);
GL_APICALL శూన్య GL_APIENTRY gl_Debug_సందేశం_Callback (GLDEBUGPROC callback, స్థిరరాశి శూన్య *userParam);
GL_APICALL GLuint GL_APIENTRY gl_Get_Debug_సందేశం_Log (GLuint లెక్క, GLsizei buf_కొలత, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *సందేశం_Log);
GL_APICALL శూన్య GL_APIENTRY gl_నెట్టు_Debug_సమూహం (GLenum ఆధారం, GLuint id, GLsizei నిడివి, స్థిరరాశి GLchar *సందేశం);
GL_APICALL శూన్య GL_APIENTRY gl_తీయి_Debug_సమూహం (శూన్య);
GL_APICALL శూన్య GL_APIENTRY glObjectLabel (GLenum identifier, GLuint name, GLsizei నిడివి, స్థిరరాశి GLchar *label);
GL_APICALL శూన్య GL_APIENTRY glGetObjectLabel (GLenum identifier, GLuint name, GLsizei buf_కొలత, GLsizei *నిడివి, GLchar *label);
GL_APICALL శూన్య GL_APIENTRY glObjectPtrLabel (స్థిరరాశి శూన్య *ptr, GLsizei నిడివి, స్థిరరాశి GLchar *label);
GL_APICALL శూన్య GL_APIENTRY glGetObjectPtrLabel (స్థిరరాశి శూన్య *ptr, GLsizei buf_కొలత, GLsizei *నిడివి, GLchar *label);
GL_APICALL శూన్య GL_APIENTRY glGetPointerv (GLenum pname, శూన్య **params);
GL_APICALL శూన్య GL_APIENTRY glEnablei (GLenum లక్ష్యం, GLuint సూచీ);
GL_APICALL శూన్య GL_APIENTRY glDisablei (GLenum లక్ష్యం, GLuint సూచీ);
GL_APICALL శూన్య GL_APIENTRY glBlendEquationi (GLuint buf, GLenum బహుళకం);
GL_APICALL శూన్య GL_APIENTRY glBlendEquationSeparatei (GLuint buf, GLenum బహుళకం_RGB, GLenum బహుళకం_Alpha);
GL_APICALL శూన్య GL_APIENTRY glBlendFunci (GLuint buf, GLenum src, GLenum dst);
GL_APICALL శూన్య GL_APIENTRY glBlendFuncSeparatei (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
GL_APICALL శూన్య GL_APIENTRY glColorMaski (GLuint సూచీ, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
GL_APICALL GLboolean GL_APIENTRY glIsEnabledi (GLenum లక్ష్యం, GLuint సూచీ);
GL_APICALL శూన్య GL_APIENTRY gl_Draw_Elements_పునాది_శీర్షం (GLenum బహుళకం, GLsizei లెక్క, GLenum type, స్థిరరాశి శూన్య *indices, GLint basevertex);
GL_APICALL శూన్య GL_APIENTRY gl_Draw_Range_Elements_పునాది_శీర్షం (GLenum బహుళకం, GLuint ప్రారంభం, GLuint చివర, GLsizei లెక్క, GLenum type, స్థిరరాశి శూన్య *indices, GLint basevertex);
GL_APICALL శూన్య GL_APIENTRY gl_Draw_Elements_Instanced_పునాది_శీర్షం (GLenum బహుళకం, GLsizei లెక్క, GLenum type, స్థిరరాశి శూన్య *indices, GLsizei instancecount, GLint basevertex);
GL_APICALL శూన్య GL_APIENTRY glFramebufferTexture (GLenum లక్ష్యం, GLenum attachment, GLuint texture, GLint level);
GL_APICALL శూన్య GL_APIENTRY glPrimitiveBoundingBox (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
GL_APICALL GLenum GL_APIENTRY gl_Get_Graphics_Reset_స్థితి (శూన్య);
GL_APICALL శూన్య GL_APIENTRY glReadnPixels (GLint x, GLint y, GLsizei వెడల్పు, GLsizei ఎత్తు, GLenum format, GLenum type, GLsizei buf_కొలత, శూన్య *దత్తాంశం);
GL_APICALL శూన్య GL_APIENTRY glGetnUniformfv (GLuint కార్యక్రమం, GLint location, GLsizei buf_కొలత, GLfloat *params);
GL_APICALL శూన్య GL_APIENTRY glGetnUniformiv (GLuint కార్యక్రమం, GLint location, GLsizei buf_కొలత, GLint *params);
GL_APICALL శూన్య GL_APIENTRY glGetnUniformuiv (GLuint కార్యక్రమం, GLint location, GLsizei buf_కొలత, GLuint *params);
GL_APICALL శూన్య GL_APIENTRY glMinSampleShading (GLfloat విలువ);
GL_APICALL శూన్య GL_APIENTRY glPatchParameteri (GLenum pname, GLint విలువ);
GL_APICALL శూన్య GL_APIENTRY glTexParameterIiv (GLenum లక్ష్యం, GLenum pname, స్థిరరాశి GLint *params);
GL_APICALL శూన్య GL_APIENTRY glTexParameterIuiv (GLenum లక్ష్యం, GLenum pname, స్థిరరాశి GLuint *params);
GL_APICALL శూన్య GL_APIENTRY glGetTexParameterIiv (GLenum లక్ష్యం, GLenum pname, GLint *params);
GL_APICALL శూన్య GL_APIENTRY glGetTexParameterIuiv (GLenum లక్ష్యం, GLenum pname, GLuint *params);
GL_APICALL శూన్య GL_APIENTRY glSamplerParameterIiv (GLuint sampler, GLenum pname, స్థిరరాశి GLint *param);
GL_APICALL శూన్య GL_APIENTRY glSamplerParameterIuiv (GLuint sampler, GLenum pname, స్థిరరాశి GLuint *param);
GL_APICALL శూన్య GL_APIENTRY glGetSamplerParameterIiv (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL శూన్య GL_APIENTRY glGetSamplerParameterIuiv (GLuint sampler, GLenum pname, GLuint *params);
GL_APICALL శూన్య GL_APIENTRY gl_Tex_బఫరు (GLenum లక్ష్యం, GLenum internalformat, GLuint బఫరు_2);
GL_APICALL శూన్య GL_APIENTRY gl_Tex_బఫరు_Range (GLenum లక్ష్యం, GLenum internalformat, GLuint బఫరు_2, GLintptr స్థానభ్రంశం_2, GLsizeiptr కొలత);
GL_APICALL శూన్య GL_APIENTRY glTexStorage3DMultisample (GLenum లక్ష్యం, GLsizei samples, GLenum internalformat, GLsizei వెడల్పు, GLsizei ఎత్తు, GLsizei లోతు_2, GLboolean fixedsamplelocations);
#అయితే_ముగింపు
#అయితే_ముగింపు /* GL_ES_VERSION_3_2 */

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు
