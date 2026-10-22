#که_نه_تعریف_شوی __gles2_gl2_h_
#تعریف_کړه __gles2_gl2_h_ 1

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

#ضمن <GLES2/gl2platform.h>

#که_نه_تعریف_شوی GL_APIENTRYP
#تعریف_کړه GL_APIENTRYP GL_APIENTRY*
#د_که_پای

#که_نه_تعریف_شوی GL_GLES_PROTOTYPES
#تعریف_کړه GL_GLES_PROTOTYPES 1
#د_که_پای

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

#که_نه_تعریف_شوی GL_ES_نسخه_2_0
#تعریف_کړه GL_ES_نسخه_2_0 1
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
تعريفنوع بینښه صحيح GLenum;
تعريفنوع بینښه صحيح GLuint;
تعريفنوع حرف GLchar;
تعريفنوع khronos_float_t GLfloat;
تعريفنوع khronos_ssize_t GLsizeiptr;
تعريفنوع khronos_intptr_t GLintptr;
تعريفنوع بینښه صحيح GLbitfield;
تعريفنوع صحيح GLint;
تعريفنوع بینښه حرف GLboolean;
تعريفنوع صحيح GLsizei;
تعريفنوع khronos_uint8_t GLubyte;
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
#تعریف_کړه GL_FUNC_جمع_کړه                       0x8006
#تعریف_کړه GL_BLEND_EQUATION                 0x8009
#تعریف_کړه GL_BLEND_EQUATION_RGB             0x8009
#تعریف_کړه GL_BLEND_EQUATION_ALPHA           0x883D
#تعریف_کړه GL_FUNC_کمول                  0x800A
#تعریف_کړه GL_FUNC_سرچپه_کمول          0x800B
#تعریف_کړه GL_BLEND_DST_RGB                  0x80C8
#تعریف_کړه GL_BLEND_SRC_RGB                  0x80C9
#تعریف_کړه GL_BLEND_DST_ALPHA                0x80CA
#تعریف_کړه GL_BLEND_SRC_ALPHA                0x80CB
#تعریف_کړه GL_CONSTANT_COLOR                 0x8001
#تعریف_کړه GL_ONE_MINUS_CONSTANT_COLOR       0x8002
#تعریف_کړه GL_CONSTANT_ALPHA                 0x8003
#تعریف_کړه GL_ONE_MINUS_CONSTANT_ALPHA       0x8004
#تعریف_کړه GL_BLEND_COLOR                    0x8005
#تعریف_کړه GL_ARRAY_بفر                   0x8892
#تعریف_کړه GL_ELEMENT_ARRAY_بفر           0x8893
#تعریف_کړه GL_ARRAY_بفر_BINDING           0x8894
#تعریف_کړه GL_ELEMENT_ARRAY_بفر_BINDING   0x8895
#تعریف_کړه GL_بهیر_DRAW                    0x88E0
#تعریف_کړه GL_STATIC_DRAW                    0x88E4
#تعریف_کړه GL_DYNAMIC_DRAW                   0x88E8
#تعریف_کړه GL_بفر_اندازه                    0x8764
#تعریف_کړه GL_بفر_USAGE                   0x8765
#تعریف_کړه GL_CURRENT_راس_ATTRIB          0x8626
#تعریف_کړه GL_FRONT                          0x0404
#تعریف_کړه GL_شا                           0x0405
#تعریف_کړه GL_FRONT_AND_شا                 0x0408
#تعریف_کړه GL_TEXTURE_2D                     0x0DE1
#تعریف_کړه GL_CULL_FACE                      0x0B44
#تعریف_کړه GL_BLEND                          0x0BE2
#تعریف_کړه GL_DITHER                         0x0BD0
#تعریف_کړه GL_STENCIL_TEST                   0x0B90
#تعریف_کړه GL_ژوروالی_TEST                     0x0B71
#تعریف_کړه GL_SCISSOR_TEST                   0x0C11
#تعریف_کړه GL_POLYGON_دننه_واټن_FILL            0x8037
#تعریف_کړه GL_SAMPLE_ALPHA_منزل_COVERAGE       0x809E
#تعریف_کړه GL_SAMPLE_COVERAGE                0x80A0
#تعریف_کړه GL_NO_ERROR                       0
#تعریف_کړه GL_INVALID_ENUM                   0x0500
#تعریف_کړه GL_INVALID_ارزښت                  0x0501
#تعریف_کړه GL_INVALID_OPERATION              0x0502
#تعریف_کړه GL_بهر_د_حافظه                  0x0505
#تعریف_کړه GL_CW                             0x0900
#تعریف_کړه GL_CCW                            0x0901
#تعریف_کړه GL_کرښه_پلنوالی                     0x0B21
#تعریف_کړه GL_ALIASED_ټکی_اندازه_RANGE       0x846D
#تعریف_کړه GL_ALIASED_کرښه_پلنوالی_RANGE       0x846E
#تعریف_کړه GL_CULL_FACE_ډېرپېښ                 0x0B45
#تعریف_کړه GL_FRONT_FACE                     0x0B46
#تعریف_کړه GL_ژوروالی_RANGE                    0x0B70
#تعریف_کړه GL_ژوروالی_WRITEMASK                0x0B72
#تعریف_کړه GL_ژوروالی_CLEAR_ارزښت              0x0B73
#تعریف_کړه GL_ژوروالی_FUNC                     0x0B74
#تعریف_کړه GL_STENCIL_CLEAR_ارزښت            0x0B91
#تعریف_کړه GL_STENCIL_FUNC                   0x0B92
#تعریف_کړه GL_STENCIL_FAIL                   0x0B94
#تعریف_کړه GL_STENCIL_PASS_ژوروالی_FAIL        0x0B95
#تعریف_کړه GL_STENCIL_PASS_ژوروالی_PASS        0x0B96
#تعریف_کړه GL_STENCIL_REF                    0x0B97
#تعریف_کړه GL_STENCIL_ارزښت_ماسک             0x0B93
#تعریف_کړه GL_STENCIL_WRITEMASK              0x0B98
#تعریف_کړه GL_STENCIL_شا_FUNC              0x8800
#تعریف_کړه GL_STENCIL_شا_FAIL              0x8801
#تعریف_کړه GL_STENCIL_شا_PASS_ژوروالی_FAIL   0x8802
#تعریف_کړه GL_STENCIL_شا_PASS_ژوروالی_PASS   0x8803
#تعریف_کړه GL_STENCIL_شا_REF               0x8CA3
#تعریف_کړه GL_STENCIL_شا_ارزښت_ماسک        0x8CA4
#تعریف_کړه GL_STENCIL_شا_WRITEMASK         0x8CA5
#تعریف_کړه GL_VIEWPORT                       0x0BA2
#تعریف_کړه GL_SCISSOR_BOX                    0x0C10
#تعریف_کړه GL_COLOR_CLEAR_ارزښت              0x0C22
#تعریف_کړه GL_COLOR_WRITEMASK                0x0C23
#تعریف_کړه GL_UNPACK_ALIGNMENT               0x0CF5
#تعریف_کړه GL_PACK_ALIGNMENT                 0x0D05
#تعریف_کړه GL_MAX_TEXTURE_اندازه               0x0D33
#تعریف_کړه GL_MAX_VIEWPORT_DIMS              0x0D3A
#تعریف_کړه GL_SUBPIXEL_بټونه                  0x0D50
#تعریف_کړه GL_RED_بټونه                       0x0D52
#تعریف_کړه GL_GREEN_بټونه                     0x0D53
#تعریف_کړه GL_BLUE_بټونه                      0x0D54
#تعریف_کړه GL_ALPHA_بټونه                     0x0D55
#تعریف_کړه GL_ژوروالی_بټونه                     0x0D56
#تعریف_کړه GL_STENCIL_بټونه                   0x0D57
#تعریف_کړه GL_POLYGON_دننه_واټن_UNITS           0x2A00
#تعریف_کړه GL_POLYGON_دننه_واټن_ضریب          0x8038
#تعریف_کړه GL_TEXTURE_BINDING_2D             0x8069
#تعریف_کړه GL_SAMPLE_BUFFERS                 0x80A8
#تعریف_کړه GL_SAMPLES                        0x80A9
#تعریف_کړه GL_SAMPLE_COVERAGE_ارزښت          0x80AA
#تعریف_کړه GL_SAMPLE_COVERAGE_INVERT         0x80AB
#تعریف_کړه GL_عدد_COMPRESSED_TEXTURE_FORMATS 0x86A2
#تعریف_کړه GL_COMPRESSED_TEXTURE_FORMATS     0x86A3
#تعریف_کړه GL_DONT_CARE                      0x1100
#تعریف_کړه GL_FASTEST                        0x1101
#تعریف_کړه GL_NICEST                         0x1102
#تعریف_کړه GL_GENERATE_MIPMAP_HINT           0x8192
#تعریف_کړه GL_BYTE                           0x1400
#تعریف_کړه GL_UNSIGNED_BYTE                  0x1401
#تعریف_کړه GL_SHORT                          0x1402
#تعریف_کړه GL_UNSIGNED_SHORT                 0x1403
#تعریف_کړه GL_INT                            0x1404
#تعریف_کړه GL_UNSIGNED_INT                   0x1405
#تعریف_کړه GL_FLOAT                          0x1406
#تعریف_کړه GL_FIXED                          0x140C
#تعریف_کړه GL_ژوروالی_COMPONENT                0x1902
#تعریف_کړه GL_ALPHA                          0x1906
#تعریف_کړه GL_RGB                            0x1907
#تعریف_کړه GL_RGBA                           0x1908
#تعریف_کړه GL_LUMINANCE                      0x1909
#تعریف_کړه GL_LUMINANCE_ALPHA                0x190A
#تعریف_کړه GL_UNSIGNED_SHORT_4_4_4_4         0x8033
#تعریف_کړه GL_UNSIGNED_SHORT_5_5_5_1         0x8034
#تعریف_کړه GL_UNSIGNED_SHORT_5_6_5           0x8363
#تعریف_کړه GL_FRAGMENT_SHADER                0x8B30
#تعریف_کړه GL_راس_SHADER                  0x8B31
#تعریف_کړه GL_MAX_راس_ATTRIBS             0x8869
#تعریف_کړه GL_MAX_راس_یوشان_VECTORS     0x8DFB
#تعریف_کړه GL_MAX_VARYING_VECTORS            0x8DFC
#تعریف_کړه GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 0x8B4D
#تعریف_کړه GL_MAX_راس_TEXTURE_IMAGE_UNITS 0x8B4C
#تعریف_کړه GL_MAX_TEXTURE_IMAGE_UNITS        0x8872
#تعریف_کړه GL_MAX_FRAGMENT_یوشان_VECTORS   0x8DFD
#تعریف_کړه GL_SHADER_TYPE                    0x8B4F
#تعریف_کړه GL_DELETE_حالت                  0x8B80
#تعریف_کړه GL_LINK_حالت                    0x8B82
#تعریف_کړه GL_VALIDATE_حالت                0x8B83
#تعریف_کړه GL_ATTACHED_SHADERS               0x8B85
#تعریف_کړه GL_فعال_UNIFORMS                0x8B86
#تعریف_کړه GL_فعال_یوشان_MAX_اوږدتیا      0x8B87
#تعریف_کړه GL_فعال_ځانګړتیاوې              0x8B89
#تعریف_کړه GL_فعال_ATTRIBUTE_MAX_اوږدتیا    0x8B8A
#تعریف_کړه GL_SHADING_LANGUAGE_نسخه       0x8B8C
#تعریف_کړه GL_CURRENT_پروګرام                0x8B8D
#تعریف_کړه GL_NEVER                          0x0200
#تعریف_کړه GL_LESS                           0x0201
#تعریف_کړه GL_EQUAL                          0x0202
#تعریف_کړه GL_LEQUAL                         0x0203
#تعریف_کړه GL_GREATER                        0x0204
#تعریف_کړه GL_NOTEQUAL                       0x0205
#تعریف_کړه GL_GEQUAL                         0x0206
#تعریف_کړه GL_ALWAYS                         0x0207
#تعریف_کړه GL_KEEP                           0x1E00
#تعریف_کړه GL_REPLACE                        0x1E01
#تعریف_کړه GL_INCR                           0x1E02
#تعریف_کړه GL_DECR                           0x1E03
#تعریف_کړه GL_INVERT                         0x150A
#تعریف_کړه GL_INCR_WRAP                      0x8507
#تعریف_کړه GL_DECR_WRAP                      0x8508
#تعریف_کړه GL_VENDOR                         0x1F00
#تعریف_کړه GL_RENDERER                       0x1F01
#تعریف_کړه GL_نسخه                        0x1F02
#تعریف_کړه GL_EXTENSIONS                     0x1F03
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
#تعریف_کړه GL_TEXTURE                        0x1702
#تعریف_کړه GL_TEXTURE_CUBE_MAP               0x8513
#تعریف_کړه GL_TEXTURE_BINDING_CUBE_MAP       0x8514
#تعریف_کړه GL_TEXTURE_CUBE_MAP_مثبت_X    0x8515
#تعریف_کړه GL_TEXTURE_CUBE_MAP_NEGATIVE_X    0x8516
#تعریف_کړه GL_TEXTURE_CUBE_MAP_مثبت_Y    0x8517
#تعریف_کړه GL_TEXTURE_CUBE_MAP_NEGATIVE_Y    0x8518
#تعریف_کړه GL_TEXTURE_CUBE_MAP_مثبت_Z    0x8519
#تعریف_کړه GL_TEXTURE_CUBE_MAP_NEGATIVE_Z    0x851A
#تعریف_کړه GL_MAX_CUBE_MAP_TEXTURE_اندازه      0x851C
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
#تعریف_کړه GL_REPEAT                         0x2901
#تعریف_کړه GL_CLAMP_منزل_څنډه                  0x812F
#تعریف_کړه GL_MIRRORED_REPEAT                0x8370
#تعریف_کړه GL_FLOAT_VEC2                     0x8B50
#تعریف_کړه GL_FLOAT_VEC3                     0x8B51
#تعریف_کړه GL_FLOAT_VEC4                     0x8B52
#تعریف_کړه GL_INT_VEC2                       0x8B53
#تعریف_کړه GL_INT_VEC3                       0x8B54
#تعریف_کړه GL_INT_VEC4                       0x8B55
#تعریف_کړه GL_BOOL                           0x8B56
#تعریف_کړه GL_BOOL_VEC2                      0x8B57
#تعریف_کړه GL_BOOL_VEC3                      0x8B58
#تعریف_کړه GL_BOOL_VEC4                      0x8B59
#تعریف_کړه GL_FLOAT_MAT2                     0x8B5A
#تعریف_کړه GL_FLOAT_MAT3                     0x8B5B
#تعریف_کړه GL_FLOAT_MAT4                     0x8B5C
#تعریف_کړه GL_SAMPLER_2D                     0x8B5E
#تعریف_کړه GL_SAMPLER_CUBE                   0x8B60
#تعریف_کړه GL_راس_ATTRIB_ARRAY_ENABLED    0x8622
#تعریف_کړه GL_راس_ATTRIB_ARRAY_اندازه       0x8623
#تعریف_کړه GL_راس_ATTRIB_ARRAY_STRIDE     0x8624
#تعریف_کړه GL_راس_ATTRIB_ARRAY_TYPE       0x8625
#تعریف_کړه GL_راس_ATTRIB_ARRAY_NORMALIZED 0x886A
#تعریف_کړه GL_راس_ATTRIB_ARRAY_اشاره_ګر    0x8645
#تعریف_کړه GL_راس_ATTRIB_ARRAY_بفر_BINDING 0x889F
#تعریف_کړه GL_IMPLEMENTATION_COLOR_READ_TYPE 0x8B9A
#تعریف_کړه GL_IMPLEMENTATION_COLOR_READ_FORMAT 0x8B9B
#تعریف_کړه GL_COMPILE_حالت                 0x8B81
#تعریف_کړه GL_INFO_LOG_اوږدتیا                0x8B84
#تعریف_کړه GL_SHADER_سرچینه_اوږدتیا           0x8B88
#تعریف_کړه GL_SHADER_COMPILER                0x8DFA
#تعریف_کړه GL_SHADER_دوګونی_FORMATS          0x8DF8
#تعریف_کړه GL_عدد_SHADER_دوګونی_FORMATS      0x8DF9
#تعریف_کړه GL_ټیټ_FLOAT                      0x8DF0
#تعریف_کړه GL_MEDIUM_FLOAT                   0x8DF1
#تعریف_کړه GL_لوړ_FLOAT                     0x8DF2
#تعریف_کړه GL_ټیټ_INT                        0x8DF3
#تعریف_کړه GL_MEDIUM_INT                     0x8DF4
#تعریف_کړه GL_لوړ_INT                       0x8DF5
#تعریف_کړه GL_FRAMEBUFFER                    0x8D40
#تعریف_کړه GL_RENDERBUFFER                   0x8D41
#تعریف_کړه GL_RGBA4                          0x8056
#تعریف_کړه GL_RGB5_A1                        0x8057
#تعریف_کړه GL_RGB565                         0x8D62
#تعریف_کړه GL_ژوروالی_COMPONENT16              0x81A5
#تعریف_کړه GL_STENCIL_INDEX8                 0x8D48
#تعریف_کړه GL_RENDERBUFFER_پلنوالی             0x8D42
#تعریف_کړه GL_RENDERBUFFER_لوړوالی            0x8D43
#تعریف_کړه GL_RENDERBUFFER_دننی_FORMAT   0x8D44
#تعریف_کړه GL_RENDERBUFFER_RED_اندازه          0x8D50
#تعریف_کړه GL_RENDERBUFFER_GREEN_اندازه        0x8D51
#تعریف_کړه GL_RENDERBUFFER_BLUE_اندازه         0x8D52
#تعریف_کړه GL_RENDERBUFFER_ALPHA_اندازه        0x8D53
#تعریف_کړه GL_RENDERBUFFER_ژوروالی_اندازه        0x8D54
#تعریف_کړه GL_RENDERBUFFER_STENCIL_اندازه      0x8D55
#تعریف_کړه GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE 0x8CD0
#تعریف_کړه GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME 0x8CD1
#تعریف_کړه GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL 0x8CD2
#تعریف_کړه GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE 0x8CD3
#تعریف_کړه GL_COLOR_ATTACHMENT0              0x8CE0
#تعریف_کړه GL_ژوروالی_ATTACHMENT               0x8D00
#تعریف_کړه GL_STENCIL_ATTACHMENT             0x8D20
#تعریف_کړه GL_NONE                           0
#تعریف_کړه GL_FRAMEBUFFER_COMPLETE           0x8CD5
#تعریف_کړه GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT 0x8CD6
#تعریف_کړه GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 0x8CD7
#تعریف_کړه GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS 0x8CD9
#تعریف_کړه GL_FRAMEBUFFER_UNSUPPORTED        0x8CDD
#تعریف_کړه GL_FRAMEBUFFER_BINDING            0x8CA6
#تعریف_کړه GL_RENDERBUFFER_BINDING           0x8CA7
#تعریف_کړه GL_MAX_RENDERBUFFER_اندازه          0x84E8
#تعریف_کړه GL_INVALID_FRAMEBUFFER_OPERATION  0x0506
تعريفنوع فراغ (GL_APIENTRYP PFNGLACTIVETEXTUREPROC) (GLenum texture);
تعريفنوع فراغ (GL_APIENTRYP PFNGLATTACHSHADERPROC) (GLuint پروګرام, GLuint shader);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDATTRIBLOCATIONPROC) (GLuint پروګرام, GLuint شاخص, ثابت GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDBUFFERPROC) (GLenum موخه, GLuint بفر_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDFRAMEBUFFERPROC) (GLenum موخه, GLuint framebuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDRENDERBUFFERPROC) (GLenum موخه, GLuint renderbuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDTEXTUREPROC) (GLenum موخه, GLuint texture);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONPROC) (GLenum ډېرپېښ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEPROC) (GLenum ډېرپېښ_RGB, GLenum ډېرپېښ_Alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDFUNCPROC) (GLenum sfactor, GLenum dfactor);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEPROC) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBUFFERDATAPROC) (GLenum موخه, GLsizeiptr اندازه, ثابت فراغ *معلومات, GLenum usage);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBUFFERSUBDATAPROC) (GLenum موخه, GLintptr دننه_واټن_2, GLsizeiptr اندازه, ثابت فراغ *معلومات);
تعريفنوع GLenum (GL_APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSPROC) (GLenum موخه);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARPROC) (GLbitfield ماسک);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARDEPTHFPROC) (GLfloat d);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARSTENCILPROC) (GLint s);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOLORMASKPROC) (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOMPILESHADERPROC) (GLuint shader);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOMPRESSEDTEXIMAGE2DPROC) (GLenum موخه, GLint level, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی, GLint border, GLsizei image_اندازه, ثابت فراغ *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) (GLenum موخه, GLint level, GLint xoffset, GLint yoffset, GLsizei پلنوالی, GLsizei لوړوالی, GLenum format, GLsizei image_اندازه, ثابت فراغ *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYTEXIMAGE2DPROC) (GLenum موخه, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei پلنوالی, GLsizei لوړوالی, GLint border);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYTEXSUBIMAGE2DPROC) (GLenum موخه, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei پلنوالی, GLsizei لوړوالی);
تعريفنوع GLuint (GL_APIENTRYP PFNGLCREATEPROGRAMPROC) (فراغ);
تعريفنوع GLuint (GL_APIENTRYP PFNGLCREATESHADERPROC) (GLenum type);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCULLFACEPROC) (GLenum ډېرپېښ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEBUFFERSPROC) (GLsizei n, ثابت GLuint *buffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEFRAMEBUFFERSPROC) (GLsizei n, ثابت GLuint *framebuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEPROGRAMPROC) (GLuint پروګرام);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETERENDERBUFFERSPROC) (GLsizei n, ثابت GLuint *renderbuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETESHADERPROC) (GLuint shader);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETETEXTURESPROC) (GLsizei n, ثابت GLuint *textures);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHFUNCPROC) (GLenum func);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHMASKPROC) (GLboolean flag);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHRANGEFPROC) (GLfloat n, GLfloat f);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDETACHSHADERPROC) (GLuint پروګرام, GLuint shader);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISABLEPROC) (GLenum cap);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint شاخص);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWARRAYSPROC) (GLenum ډېرپېښ, GLint لومړی, GLsizei شمېر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSPROC) (GLenum ډېرپېښ, GLsizei شمېر, GLenum type, ثابت فراغ *indices);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENABLEPROC) (GLenum cap);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint شاخص);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFINISHPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFLUSHPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFERPROC) (GLenum موخه, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DPROC) (GLenum موخه, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRONTFACEPROC) (GLenum ډېرپېښ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENBUFFERSPROC) (GLsizei n, GLuint *buffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENERATEMIPMAPPROC) (GLenum موخه);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENFRAMEBUFFERSPROC) (GLsizei n, GLuint *framebuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENRENDERBUFFERSPROC) (GLsizei n, GLuint *renderbuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENTEXTURESPROC) (GLsizei n, GLuint *textures);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETACTIVEATTRIBPROC) (GLuint پروګرام, GLuint شاخص, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLint *اندازه, GLenum *type, GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETACTIVEUNIFORMPROC) (GLuint پروګرام, GLuint شاخص, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLint *اندازه, GLenum *type, GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETATTACHEDSHADERSPROC) (GLuint پروګرام, GLsizei max_شمېر, GLsizei *شمېر, GLuint *shaders);
تعريفنوع GLint (GL_APIENTRYP PFNGLGETATTRIBLOCATIONPROC) (GLuint پروګرام, ثابت GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETBOOLEANVPROC) (GLenum pname, GLboolean *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETBUFFERPARAMETERIVPROC) (GLenum موخه, GLenum pname, GLint *params);
تعريفنوع GLenum (GL_APIENTRYP PFNGLGETERRORPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFLOATVPROC) (GLenum pname, GLfloat *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) (GLenum موخه, GLenum attachment, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTEGERVPROC) (GLenum pname, GLint *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMIVPROC) (GLuint پروګرام, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMINFOLOGPROC) (GLuint پروګرام, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLchar *infoLog);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVPROC) (GLenum موخه, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLchar *infoLog);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSHADERPRECISIONFORMATPROC) (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSHADERSOURCEPROC) (GLuint shader, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLchar *سرچینه);
تعريفنوع ثابت GLubyte *(GL_APIENTRYP PFNGLGETSTRINGPROC) (GLenum name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXPARAMETERFVPROC) (GLenum موخه, GLenum pname, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXPARAMETERIVPROC) (GLenum موخه, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETUNIFORMFVPROC) (GLuint پروګرام, GLint location, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETUNIFORMIVPROC) (GLuint پروګرام, GLint location, GLint *params);
تعريفنوع GLint (GL_APIENTRYP PFNGLGETUNIFORMLOCATIONPROC) (GLuint پروګرام, ثابت GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETVERTEXATTRIBFVPROC) (GLuint شاخص, GLenum pname, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETVERTEXATTRIBIVPROC) (GLuint شاخص, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETVERTEXATTRIBPOINTERVPROC) (GLuint شاخص, GLenum pname, فراغ **اشاره_ګر_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLHINTPROC) (GLenum موخه, GLenum ډېرپېښ);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISBUFFERPROC) (GLuint بفر_2);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISENABLEDPROC) (GLenum cap);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISFRAMEBUFFERPROC) (GLuint framebuffer);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISPROGRAMPROC) (GLuint پروګرام);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISRENDERBUFFERPROC) (GLuint renderbuffer);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISSHADERPROC) (GLuint shader);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISTEXTUREPROC) (GLuint texture);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLINEWIDTHPROC) (GLfloat پلنوالی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLINKPROGRAMPROC) (GLuint پروګرام);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPIXELSTOREIPROC) (GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOLYGONOFFSETPROC) (GLfloat ضریب, GLfloat units);
تعريفنوع فراغ (GL_APIENTRYP PFNGLREADPIXELSPROC) (GLint x, GLint y, GLsizei پلنوالی, GLsizei لوړوالی, GLenum format, GLenum type, فراغ *pixels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRELEASESHADERCOMPILERPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEPROC) (GLenum موخه, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLECOVERAGEPROC) (GLfloat ارزښت, GLboolean invert);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSORPROC) (GLint x, GLint y, GLsizei پلنوالی, GLsizei لوړوالی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADERBINARYPROC) (GLsizei شمېر, ثابت GLuint *shaders, GLenum دوګونی_Format, ثابت فراغ *دوګونی, GLsizei اوږدتیا);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei شمېر, ثابت GLchar *ثابت*string, ثابت GLint *اوږدتیا);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILFUNCPROC) (GLenum func, GLint ref, GLuint ماسک);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILFUNCSEPARATEPROC) (GLenum face, GLenum func, GLint ref, GLuint ماسک);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILMASKPROC) (GLuint ماسک);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILMASKSEPARATEPROC) (GLenum face, GLuint ماسک);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILOPPROC) (GLenum fail, GLenum zfail, GLenum zpass);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILOPSEPARATEPROC) (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXIMAGE2DPROC) (GLenum موخه, GLint level, GLint internalformat, GLsizei پلنوالی, GLsizei لوړوالی, GLint border, GLenum format, GLenum type, ثابت فراغ *pixels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERFPROC) (GLenum موخه, GLenum pname, GLfloat param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERFVPROC) (GLenum موخه, GLenum pname, ثابت GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERIPROC) (GLenum موخه, GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERIVPROC) (GLenum موخه, GLenum pname, ثابت GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSUBIMAGE2DPROC) (GLenum موخه, GLint level, GLint xoffset, GLint yoffset, GLsizei پلنوالی, GLsizei لوړوالی, GLenum format, GLenum type, ثابت فراغ *pixels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1FPROC) (GLint location, GLfloat v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1FVPROC) (GLint location, GLsizei شمېر, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1IPROC) (GLint location, GLint v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1IVPROC) (GLint location, GLsizei شمېر, ثابت GLint *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2FPROC) (GLint location, GLfloat v0, GLfloat v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2FVPROC) (GLint location, GLsizei شمېر, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2IPROC) (GLint location, GLint v0, GLint v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2IVPROC) (GLint location, GLsizei شمېر, ثابت GLint *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3FVPROC) (GLint location, GLsizei شمېر, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3IPROC) (GLint location, GLint v0, GLint v1, GLint v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3IVPROC) (GLint location, GLsizei شمېر, ثابت GLint *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4FVPROC) (GLint location, GLsizei شمېر, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4IPROC) (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4IVPROC) (GLint location, GLsizei شمېر, ثابت GLint *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX2FVPROC) (GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX3FVPROC) (GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUSEPROGRAMPROC) (GLuint پروګرام);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVALIDATEPROGRAMPROC) (GLuint پروګرام);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB1FPROC) (GLuint شاخص, GLfloat x);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB1FVPROC) (GLuint شاخص, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB2FPROC) (GLuint شاخص, GLfloat x, GLfloat y);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB2FVPROC) (GLuint شاخص, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB3FPROC) (GLuint شاخص, GLfloat x, GLfloat y, GLfloat z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB3FVPROC) (GLuint شاخص, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB4FPROC) (GLuint شاخص, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB4FVPROC) (GLuint شاخص, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC) (GLuint شاخص, GLint اندازه, GLenum type, GLboolean normalized, GLsizei stride, ثابت فراغ *اشاره_ګر_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTPROC) (GLint x, GLint y, GLsizei پلنوالی, GLsizei لوړوالی);
#إذا GL_GLES_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_فعال_Texture (GLenum texture);
GL_APICALL فراغ GL_APIENTRY glAttachShader (GLuint پروګرام, GLuint shader);
GL_APICALL فراغ GL_APIENTRY glBindAttribLocation (GLuint پروګرام, GLuint شاخص, ثابت GLchar *name);
GL_APICALL فراغ GL_APIENTRY gl_Bind_بفر (GLenum موخه, GLuint بفر_2);
GL_APICALL فراغ GL_APIENTRY glBindFramebuffer (GLenum موخه, GLuint framebuffer);
GL_APICALL فراغ GL_APIENTRY glBindRenderbuffer (GLenum موخه, GLuint renderbuffer);
GL_APICALL فراغ GL_APIENTRY glBindTexture (GLenum موخه, GLuint texture);
GL_APICALL فراغ GL_APIENTRY glBlendColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_APICALL فراغ GL_APIENTRY glBlendEquation (GLenum ډېرپېښ);
GL_APICALL فراغ GL_APIENTRY glBlendEquationSeparate (GLenum ډېرپېښ_RGB, GLenum ډېرپېښ_Alpha);
GL_APICALL فراغ GL_APIENTRY glBlendFunc (GLenum sfactor, GLenum dfactor);
GL_APICALL فراغ GL_APIENTRY glBlendFuncSeparate (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
GL_APICALL فراغ GL_APIENTRY gl_بفر_معلومات (GLenum موخه, GLsizeiptr اندازه, ثابت فراغ *معلومات, GLenum usage);
GL_APICALL فراغ GL_APIENTRY gl_بفر_Sub_معلومات (GLenum موخه, GLintptr دننه_واټن_2, GLsizeiptr اندازه, ثابت فراغ *معلومات);
GL_APICALL GLenum GL_APIENTRY gl_Check_Framebuffer_حالت (GLenum موخه);
GL_APICALL فراغ GL_APIENTRY glClear (GLbitfield ماسک);
GL_APICALL فراغ GL_APIENTRY glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_APICALL فراغ GL_APIENTRY glClearDepthf (GLfloat d);
GL_APICALL فراغ GL_APIENTRY glClearStencil (GLint s);
GL_APICALL فراغ GL_APIENTRY gl_Color_ماسک (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
GL_APICALL فراغ GL_APIENTRY glCompileShader (GLuint shader);
GL_APICALL فراغ GL_APIENTRY glCompressedTexImage2D (GLenum موخه, GLint level, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی, GLint border, GLsizei image_اندازه, ثابت فراغ *معلومات);
GL_APICALL فراغ GL_APIENTRY glCompressedTexSubImage2D (GLenum موخه, GLint level, GLint xoffset, GLint yoffset, GLsizei پلنوالی, GLsizei لوړوالی, GLenum format, GLsizei image_اندازه, ثابت فراغ *معلومات);
GL_APICALL فراغ GL_APIENTRY glCopyTexImage2D (GLenum موخه, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei پلنوالی, GLsizei لوړوالی, GLint border);
GL_APICALL فراغ GL_APIENTRY glCopyTexSubImage2D (GLenum موخه, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei پلنوالی, GLsizei لوړوالی);
GL_APICALL GLuint GL_APIENTRY gl_Create_پروګرام (فراغ);
GL_APICALL GLuint GL_APIENTRY glCreateShader (GLenum type);
GL_APICALL فراغ GL_APIENTRY glCullFace (GLenum ډېرپېښ);
GL_APICALL فراغ GL_APIENTRY glDeleteBuffers (GLsizei n, ثابت GLuint *buffers);
GL_APICALL فراغ GL_APIENTRY glDeleteFramebuffers (GLsizei n, ثابت GLuint *framebuffers);
GL_APICALL فراغ GL_APIENTRY gl_Delete_پروګرام (GLuint پروګرام);
GL_APICALL فراغ GL_APIENTRY glDeleteRenderbuffers (GLsizei n, ثابت GLuint *renderbuffers);
GL_APICALL فراغ GL_APIENTRY glDeleteShader (GLuint shader);
GL_APICALL فراغ GL_APIENTRY glDeleteTextures (GLsizei n, ثابت GLuint *textures);
GL_APICALL فراغ GL_APIENTRY gl_ژوروالی_Func (GLenum func);
GL_APICALL فراغ GL_APIENTRY gl_ژوروالی_ماسک (GLboolean flag);
GL_APICALL فراغ GL_APIENTRY gl_ژوروالی_Rangef (GLfloat n, GLfloat f);
GL_APICALL فراغ GL_APIENTRY glDetachShader (GLuint پروګرام, GLuint shader);
GL_APICALL فراغ GL_APIENTRY glDisable (GLenum cap);
GL_APICALL فراغ GL_APIENTRY gl_Disable_راس_Attrib_Array (GLuint شاخص);
GL_APICALL فراغ GL_APIENTRY glDrawArrays (GLenum ډېرپېښ, GLint لومړی, GLsizei شمېر);
GL_APICALL فراغ GL_APIENTRY glDrawElements (GLenum ډېرپېښ, GLsizei شمېر, GLenum type, ثابت فراغ *indices);
GL_APICALL فراغ GL_APIENTRY glEnable (GLenum cap);
GL_APICALL فراغ GL_APIENTRY gl_Enable_راس_Attrib_Array (GLuint شاخص);
GL_APICALL فراغ GL_APIENTRY gl_پای (فراغ);
GL_APICALL فراغ GL_APIENTRY glFlush (فراغ);
GL_APICALL فراغ GL_APIENTRY glFramebufferRenderbuffer (GLenum موخه, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
GL_APICALL فراغ GL_APIENTRY glFramebufferTexture2D (GLenum موخه, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GL_APICALL فراغ GL_APIENTRY glFrontFace (GLenum ډېرپېښ);
GL_APICALL فراغ GL_APIENTRY glGenBuffers (GLsizei n, GLuint *buffers);
GL_APICALL فراغ GL_APIENTRY glGenerateMipmap (GLenum موخه);
GL_APICALL فراغ GL_APIENTRY glGenFramebuffers (GLsizei n, GLuint *framebuffers);
GL_APICALL فراغ GL_APIENTRY glGenRenderbuffers (GLsizei n, GLuint *renderbuffers);
GL_APICALL فراغ GL_APIENTRY glGenTextures (GLsizei n, GLuint *textures);
GL_APICALL فراغ GL_APIENTRY gl_Get_فعال_Attrib (GLuint پروګرام, GLuint شاخص, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLint *اندازه, GLenum *type, GLchar *name);
GL_APICALL فراغ GL_APIENTRY gl_Get_فعال_یوشان (GLuint پروګرام, GLuint شاخص, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLint *اندازه, GLenum *type, GLchar *name);
GL_APICALL فراغ GL_APIENTRY glGetAttachedShaders (GLuint پروګرام, GLsizei max_شمېر, GLsizei *شمېر, GLuint *shaders);
GL_APICALL GLint GL_APIENTRY glGetAttribLocation (GLuint پروګرام, ثابت GLchar *name);
GL_APICALL فراغ GL_APIENTRY glGetBooleanv (GLenum pname, GLboolean *معلومات);
GL_APICALL فراغ GL_APIENTRY gl_Get_بفر_Parameteriv (GLenum موخه, GLenum pname, GLint *params);
GL_APICALL GLenum GL_APIENTRY glGetError (فراغ);
GL_APICALL فراغ GL_APIENTRY glGetFloatv (GLenum pname, GLfloat *معلومات);
GL_APICALL فراغ GL_APIENTRY glGetFramebufferAttachmentParameteriv (GLenum موخه, GLenum attachment, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetIntegerv (GLenum pname, GLint *معلومات);
GL_APICALL فراغ GL_APIENTRY glGetProgramiv (GLuint پروګرام, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY gl_Get_پروګرام_Info_Log (GLuint پروګرام, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLchar *infoLog);
GL_APICALL فراغ GL_APIENTRY glGetRenderbufferParameteriv (GLenum موخه, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetShaderiv (GLuint shader, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetShaderInfoLog (GLuint shader, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLchar *infoLog);
GL_APICALL فراغ GL_APIENTRY glGetShaderPrecisionFormat (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
GL_APICALL فراغ GL_APIENTRY gl_Get_Shader_سرچینه (GLuint shader, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLchar *سرچینه);
GL_APICALL ثابت GLubyte *GL_APIENTRY glGetString (GLenum name);
GL_APICALL فراغ GL_APIENTRY glGetTexParameterfv (GLenum موخه, GLenum pname, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY glGetTexParameteriv (GLenum موخه, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetUniformfv (GLuint پروګرام, GLint location, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY glGetUniformiv (GLuint پروګرام, GLint location, GLint *params);
GL_APICALL GLint GL_APIENTRY gl_Get_یوشان_Location (GLuint پروګرام, ثابت GLchar *name);
GL_APICALL فراغ GL_APIENTRY gl_Get_راس_Attribfv (GLuint شاخص, GLenum pname, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY gl_Get_راس_Attribiv (GLuint شاخص, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY gl_Get_راس_Attrib_Pointerv (GLuint شاخص, GLenum pname, فراغ **اشاره_ګر_2);
GL_APICALL فراغ GL_APIENTRY glHint (GLenum موخه, GLenum ډېرپېښ);
GL_APICALL GLboolean GL_APIENTRY gl_Is_بفر (GLuint بفر_2);
GL_APICALL GLboolean GL_APIENTRY glIsEnabled (GLenum cap);
GL_APICALL GLboolean GL_APIENTRY glIsFramebuffer (GLuint framebuffer);
GL_APICALL GLboolean GL_APIENTRY gl_Is_پروګرام (GLuint پروګرام);
GL_APICALL GLboolean GL_APIENTRY glIsRenderbuffer (GLuint renderbuffer);
GL_APICALL GLboolean GL_APIENTRY glIsShader (GLuint shader);
GL_APICALL GLboolean GL_APIENTRY glIsTexture (GLuint texture);
GL_APICALL فراغ GL_APIENTRY gl_کرښه_پلنوالی (GLfloat پلنوالی);
GL_APICALL فراغ GL_APIENTRY gl_Link_پروګرام (GLuint پروګرام);
GL_APICALL فراغ GL_APIENTRY glPixelStorei (GLenum pname, GLint param);
GL_APICALL فراغ GL_APIENTRY gl_Polygon_دننه_واټن (GLfloat ضریب, GLfloat units);
GL_APICALL فراغ GL_APIENTRY glReadPixels (GLint x, GLint y, GLsizei پلنوالی, GLsizei لوړوالی, GLenum format, GLenum type, فراغ *pixels);
GL_APICALL فراغ GL_APIENTRY glReleaseShaderCompiler (فراغ);
GL_APICALL فراغ GL_APIENTRY glRenderbufferStorage (GLenum موخه, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
GL_APICALL فراغ GL_APIENTRY glSampleCoverage (GLfloat ارزښت, GLboolean invert);
GL_APICALL فراغ GL_APIENTRY glScissor (GLint x, GLint y, GLsizei پلنوالی, GLsizei لوړوالی);
GL_APICALL فراغ GL_APIENTRY gl_Shader_دوګونی (GLsizei شمېر, ثابت GLuint *shaders, GLenum دوګونی_Format, ثابت فراغ *دوګونی, GLsizei اوږدتیا);
GL_APICALL فراغ GL_APIENTRY gl_Shader_سرچینه (GLuint shader, GLsizei شمېر, ثابت GLchar *ثابت*string, ثابت GLint *اوږدتیا);
GL_APICALL فراغ GL_APIENTRY glStencilFunc (GLenum func, GLint ref, GLuint ماسک);
GL_APICALL فراغ GL_APIENTRY glStencilFuncSeparate (GLenum face, GLenum func, GLint ref, GLuint ماسک);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_ماسک (GLuint ماسک);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_ماسک_Separate (GLenum face, GLuint ماسک);
GL_APICALL فراغ GL_APIENTRY glStencilOp (GLenum fail, GLenum zfail, GLenum zpass);
GL_APICALL فراغ GL_APIENTRY glStencilOpSeparate (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
GL_APICALL فراغ GL_APIENTRY glTexImage2D (GLenum موخه, GLint level, GLint internalformat, GLsizei پلنوالی, GLsizei لوړوالی, GLint border, GLenum format, GLenum type, ثابت فراغ *pixels);
GL_APICALL فراغ GL_APIENTRY glTexParameterf (GLenum موخه, GLenum pname, GLfloat param);
GL_APICALL فراغ GL_APIENTRY glTexParameterfv (GLenum موخه, GLenum pname, ثابت GLfloat *params);
GL_APICALL فراغ GL_APIENTRY glTexParameteri (GLenum موخه, GLenum pname, GLint param);
GL_APICALL فراغ GL_APIENTRY glTexParameteriv (GLenum موخه, GLenum pname, ثابت GLint *params);
GL_APICALL فراغ GL_APIENTRY glTexSubImage2D (GLenum موخه, GLint level, GLint xoffset, GLint yoffset, GLsizei پلنوالی, GLsizei لوړوالی, GLenum format, GLenum type, ثابت فراغ *pixels);
GL_APICALL فراغ GL_APIENTRY glUniform1f (GLint location, GLfloat v0);
GL_APICALL فراغ GL_APIENTRY glUniform1fv (GLint location, GLsizei شمېر, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY glUniform1i (GLint location, GLint v0);
GL_APICALL فراغ GL_APIENTRY glUniform1iv (GLint location, GLsizei شمېر, ثابت GLint *ارزښت);
GL_APICALL فراغ GL_APIENTRY glUniform2f (GLint location, GLfloat v0, GLfloat v1);
GL_APICALL فراغ GL_APIENTRY glUniform2fv (GLint location, GLsizei شمېر, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY glUniform2i (GLint location, GLint v0, GLint v1);
GL_APICALL فراغ GL_APIENTRY glUniform2iv (GLint location, GLsizei شمېر, ثابت GLint *ارزښت);
GL_APICALL فراغ GL_APIENTRY glUniform3f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
GL_APICALL فراغ GL_APIENTRY glUniform3fv (GLint location, GLsizei شمېر, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY glUniform3i (GLint location, GLint v0, GLint v1, GLint v2);
GL_APICALL فراغ GL_APIENTRY glUniform3iv (GLint location, GLsizei شمېر, ثابت GLint *ارزښت);
GL_APICALL فراغ GL_APIENTRY glUniform4f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
GL_APICALL فراغ GL_APIENTRY glUniform4fv (GLint location, GLsizei شمېر, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY glUniform4i (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
GL_APICALL فراغ GL_APIENTRY glUniform4iv (GLint location, GLsizei شمېر, ثابت GLint *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_یوشان_Matrix2fv (GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_یوشان_Matrix3fv (GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_یوشان_Matrix4fv (GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_Use_پروګرام (GLuint پروګرام);
GL_APICALL فراغ GL_APIENTRY gl_Validate_پروګرام (GLuint پروګرام);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib1f (GLuint شاخص, GLfloat x);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib1fv (GLuint شاخص, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib2f (GLuint شاخص, GLfloat x, GLfloat y);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib2fv (GLuint شاخص, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib3f (GLuint شاخص, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib3fv (GLuint شاخص, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib4f (GLuint شاخص, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib4fv (GLuint شاخص, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib_اشاره_ګر (GLuint شاخص, GLint اندازه, GLenum type, GLboolean normalized, GLsizei stride, ثابت فراغ *اشاره_ګر_2);
GL_APICALL فراغ GL_APIENTRY glViewport (GLint x, GLint y, GLsizei پلنوالی, GLsizei لوړوالی);
#د_که_پای
#د_که_پای /* GL_ES_VERSION_2_0 */

#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای
