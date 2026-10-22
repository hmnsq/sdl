#నిర్వచితం_కాకపోతే __gles2_gl2_h_
#నిర్వచించు __gles2_gl2_h_ 1

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

#అన్తర్భావ <GLES2/gl2platform.h>

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
 * Versions considered: 2\.[0-9]
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

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు
