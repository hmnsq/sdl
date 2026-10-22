#که_نه_تعریف_شوی __gles2_gl31_h_
#تعریف_کړه __gles2_gl31_h_ 1

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

#ضمن <GLES3/gl3platform.h>

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
 * Versions considered: 2\.[0-9]|3\.[01]
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

#که_نه_تعریف_شوی GL_ES_نسخه_3_0
#تعریف_کړه GL_ES_نسخه_3_0 1
تعريفنوع khronos_uint16_t GLhalf;
#تعریف_کړه GL_READ_بفر                    0x0C02
#تعریف_کړه GL_UNPACK_لیکه_اوږدتیا              0x0CF2
#تعریف_کړه GL_UNPACK_SKIP_لیکې               0x0CF3
#تعریف_کړه GL_UNPACK_SKIP_PIXELS             0x0CF4
#تعریف_کړه GL_PACK_لیکه_اوږدتیا                0x0D02
#تعریف_کړه GL_PACK_SKIP_لیکې                 0x0D03
#تعریف_کړه GL_PACK_SKIP_PIXELS               0x0D04
#تعریف_کړه GL_COLOR                          0x1800
#تعریف_کړه GL_ژوروالی                          0x1801
#تعریف_کړه GL_STENCIL                        0x1802
#تعریف_کړه GL_RED                            0x1903
#تعریف_کړه GL_RGB8                           0x8051
#تعریف_کړه GL_RGBA8                          0x8058
#تعریف_کړه GL_RGB10_A2                       0x8059
#تعریف_کړه GL_TEXTURE_BINDING_3D             0x806A
#تعریف_کړه GL_UNPACK_SKIP_IMAGES             0x806D
#تعریف_کړه GL_UNPACK_IMAGE_لوړوالی            0x806E
#تعریف_کړه GL_TEXTURE_3D                     0x806F
#تعریف_کړه GL_TEXTURE_WRAP_R                 0x8072
#تعریف_کړه GL_MAX_3_D_TEXTURE_اندازه            0x8073
#تعریف_کړه GL_UNSIGNED_INT_2_10_10_10_REV    0x8368
#تعریف_کړه GL_MAX_ELEMENTS_VERTICES          0x80E8
#تعریف_کړه GL_MAX_ELEMENTS_INDICES           0x80E9
#تعریف_کړه GL_TEXTURE_MIN_LOD                0x813A
#تعریف_کړه GL_TEXTURE_MAX_LOD                0x813B
#تعریف_کړه GL_TEXTURE_بنسټ_LEVEL             0x813C
#تعریف_کړه GL_TEXTURE_MAX_LEVEL              0x813D
#تعریف_کړه GL_MIN                            0x8007
#تعریف_کړه GL_MAX                            0x8008
#تعریف_کړه GL_ژوروالی_COMPONENT24              0x81A6
#تعریف_کړه GL_MAX_TEXTURE_LOD_BIAS           0x84FD
#تعریف_کړه GL_TEXTURE_COMPARE_ډېرپېښ           0x884C
#تعریف_کړه GL_TEXTURE_COMPARE_FUNC           0x884D
#تعریف_کړه GL_CURRENT_QUERY                  0x8865
#تعریف_کړه GL_QUERY_پایله                   0x8866
#تعریف_کړه GL_QUERY_پایله_شته         0x8867
#تعریف_کړه GL_بفر_MAPPED                  0x88BC
#تعریف_کړه GL_بفر_MAP_اشاره_ګر             0x88BD
#تعریف_کړه GL_بهیر_READ                    0x88E1
#تعریف_کړه GL_بهیر_COPY                    0x88E2
#تعریف_کړه GL_STATIC_READ                    0x88E5
#تعریف_کړه GL_STATIC_COPY                    0x88E6
#تعریف_کړه GL_DYNAMIC_READ                   0x88E9
#تعریف_کړه GL_DYNAMIC_COPY                   0x88EA
#تعریف_کړه GL_MAX_DRAW_BUFFERS               0x8824
#تعریف_کړه GL_DRAW_BUFFER0                   0x8825
#تعریف_کړه GL_DRAW_BUFFER1                   0x8826
#تعریف_کړه GL_DRAW_BUFFER2                   0x8827
#تعریف_کړه GL_DRAW_BUFFER3                   0x8828
#تعریف_کړه GL_DRAW_BUFFER4                   0x8829
#تعریف_کړه GL_DRAW_BUFFER5                   0x882A
#تعریف_کړه GL_DRAW_BUFFER6                   0x882B
#تعریف_کړه GL_DRAW_BUFFER7                   0x882C
#تعریف_کړه GL_DRAW_BUFFER8                   0x882D
#تعریف_کړه GL_DRAW_BUFFER9                   0x882E
#تعریف_کړه GL_DRAW_BUFFER10                  0x882F
#تعریف_کړه GL_DRAW_BUFFER11                  0x8830
#تعریف_کړه GL_DRAW_BUFFER12                  0x8831
#تعریف_کړه GL_DRAW_BUFFER13                  0x8832
#تعریف_کړه GL_DRAW_BUFFER14                  0x8833
#تعریف_کړه GL_DRAW_BUFFER15                  0x8834
#تعریف_کړه GL_MAX_FRAGMENT_یوشان_COMPONENTS 0x8B49
#تعریف_کړه GL_MAX_راس_یوشان_COMPONENTS  0x8B4A
#تعریف_کړه GL_SAMPLER_3D                     0x8B5F
#تعریف_کړه GL_SAMPLER_2D_SHADOW              0x8B62
#تعریف_کړه GL_FRAGMENT_SHADER_DERIVATIVE_HINT 0x8B8B
#تعریف_کړه GL_PIXEL_PACK_بفر              0x88EB
#تعریف_کړه GL_PIXEL_UNPACK_بفر            0x88EC
#تعریف_کړه GL_PIXEL_PACK_بفر_BINDING      0x88ED
#تعریف_کړه GL_PIXEL_UNPACK_بفر_BINDING    0x88EF
#تعریف_کړه GL_FLOAT_MAT2x3                   0x8B65
#تعریف_کړه GL_FLOAT_MAT2x4                   0x8B66
#تعریف_کړه GL_FLOAT_MAT3x2                   0x8B67
#تعریف_کړه GL_FLOAT_MAT3x4                   0x8B68
#تعریف_کړه GL_FLOAT_MAT4x2                   0x8B69
#تعریف_کړه GL_FLOAT_MAT4x3                   0x8B6A
#تعریف_کړه GL_SRGB                           0x8C40
#تعریف_کړه GL_SRGB8                          0x8C41
#تعریف_کړه GL_SRGB8_ALPHA8                   0x8C43
#تعریف_کړه GL_COMPARE_REF_منزل_TEXTURE         0x884E
#تعریف_کړه GL_MAJOR_نسخه                  0x821B
#تعریف_کړه GL_MINOR_نسخه                  0x821C
#تعریف_کړه GL_عدد_EXTENSIONS                 0x821D
#تعریف_کړه GL_RGBA32F                        0x8814
#تعریف_کړه GL_RGB32F                         0x8815
#تعریف_کړه GL_RGBA16F                        0x881A
#تعریف_کړه GL_RGB16F                         0x881B
#تعریف_کړه GL_راس_ATTRIB_ARRAY_INTEGER    0x88FD
#تعریف_کړه GL_MAX_ARRAY_TEXTURE_LAYERS       0x88FF
#تعریف_کړه GL_MIN_پروګرام_TEXEL_دننه_واټن       0x8904
#تعریف_کړه GL_MAX_پروګرام_TEXEL_دننه_واټن       0x8905
#تعریف_کړه GL_MAX_VARYING_COMPONENTS         0x8B4B
#تعریف_کړه GL_TEXTURE_2D_ARRAY               0x8C1A
#تعریف_کړه GL_TEXTURE_BINDING_2D_ARRAY       0x8C1D
#تعریف_کړه GL_R11F_G11F_B10F                 0x8C3A
#تعریف_کړه GL_UNSIGNED_INT_10F_11F_11F_REV   0x8C3B
#تعریف_کړه GL_RGB9_E5                        0x8C3D
#تعریف_کړه GL_UNSIGNED_INT_5_9_9_9_REV       0x8C3E
#تعریف_کړه GL_TRANSFORM_FEEDBACK_VARYING_MAX_اوږدتیا 0x8C76
#تعریف_کړه GL_TRANSFORM_FEEDBACK_بفر_ډېرپېښ 0x8C7F
#تعریف_کړه GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS 0x8C80
#تعریف_کړه GL_TRANSFORM_FEEDBACK_VARYINGS    0x8C83
#تعریف_کړه GL_TRANSFORM_FEEDBACK_بفر_پیل 0x8C84
#تعریف_کړه GL_TRANSFORM_FEEDBACK_بفر_اندازه 0x8C85
#تعریف_کړه GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN 0x8C88
#تعریف_کړه GL_RASTERIZER_DISCARD             0x8C89
#تعریف_کړه GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS 0x8C8A
#تعریف_کړه GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS 0x8C8B
#تعریف_کړه GL_INTERLEAVED_ATTRIBS            0x8C8C
#تعریف_کړه GL_SEPARATE_ATTRIBS               0x8C8D
#تعریف_کړه GL_TRANSFORM_FEEDBACK_بفر      0x8C8E
#تعریف_کړه GL_TRANSFORM_FEEDBACK_بفر_BINDING 0x8C8F
#تعریف_کړه GL_RGBA32UI                       0x8D70
#تعریف_کړه GL_RGB32UI                        0x8D71
#تعریف_کړه GL_RGBA16UI                       0x8D76
#تعریف_کړه GL_RGB16UI                        0x8D77
#تعریف_کړه GL_RGBA8UI                        0x8D7C
#تعریف_کړه GL_RGB8UI                         0x8D7D
#تعریف_کړه GL_RGBA32I                        0x8D82
#تعریف_کړه GL_RGB32I                         0x8D83
#تعریف_کړه GL_RGBA16I                        0x8D88
#تعریف_کړه GL_RGB16I                         0x8D89
#تعریف_کړه GL_RGBA8I                         0x8D8E
#تعریف_کړه GL_RGB8I                          0x8D8F
#تعریف_کړه GL_RED_INTEGER                    0x8D94
#تعریف_کړه GL_RGB_INTEGER                    0x8D98
#تعریف_کړه GL_RGBA_INTEGER                   0x8D99
#تعریف_کړه GL_SAMPLER_2D_ARRAY               0x8DC1
#تعریف_کړه GL_SAMPLER_2D_ARRAY_SHADOW        0x8DC4
#تعریف_کړه GL_SAMPLER_CUBE_SHADOW            0x8DC5
#تعریف_کړه GL_UNSIGNED_INT_VEC2              0x8DC6
#تعریف_کړه GL_UNSIGNED_INT_VEC3              0x8DC7
#تعریف_کړه GL_UNSIGNED_INT_VEC4              0x8DC8
#تعریف_کړه GL_INT_SAMPLER_2D                 0x8DCA
#تعریف_کړه GL_INT_SAMPLER_3D                 0x8DCB
#تعریف_کړه GL_INT_SAMPLER_CUBE               0x8DCC
#تعریف_کړه GL_INT_SAMPLER_2D_ARRAY           0x8DCF
#تعریف_کړه GL_UNSIGNED_INT_SAMPLER_2D        0x8DD2
#تعریف_کړه GL_UNSIGNED_INT_SAMPLER_3D        0x8DD3
#تعریف_کړه GL_UNSIGNED_INT_SAMPLER_CUBE      0x8DD4
#تعریف_کړه GL_UNSIGNED_INT_SAMPLER_2D_ARRAY  0x8DD7
#تعریف_کړه GL_بفر_ACCESS_FLAGS            0x911F
#تعریف_کړه GL_بفر_MAP_اوږدتیا              0x9120
#تعریف_کړه GL_بفر_MAP_دننه_واټن              0x9121
#تعریف_کړه GL_ژوروالی_COMPONENT32_F             0x8CAC
#تعریف_کړه GL_DEPTH32F_STENCIL8              0x8CAD
#تعریف_کړه GL_FLOAT_32_UNSIGNED_INT_24_8_REV 0x8DAD
#تعریف_کړه GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING 0x8210
#تعریف_کړه GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE 0x8211
#تعریف_کړه GL_FRAMEBUFFER_ATTACHMENT_RED_اندازه 0x8212
#تعریف_کړه GL_FRAMEBUFFER_ATTACHMENT_GREEN_اندازه 0x8213
#تعریف_کړه GL_FRAMEBUFFER_ATTACHMENT_BLUE_اندازه 0x8214
#تعریف_کړه GL_FRAMEBUFFER_ATTACHMENT_ALPHA_اندازه 0x8215
#تعریف_کړه GL_FRAMEBUFFER_ATTACHMENT_ژوروالی_اندازه 0x8216
#تعریف_کړه GL_FRAMEBUFFER_ATTACHMENT_STENCIL_اندازه 0x8217
#تعریف_کړه GL_FRAMEBUFFER_DEFAULT            0x8218
#تعریف_کړه GL_FRAMEBUFFER_UNDEFINED          0x8219
#تعریف_کړه GL_ژوروالی_STENCIL_ATTACHMENT       0x821A
#تعریف_کړه GL_ژوروالی_STENCIL                  0x84F9
#تعریف_کړه GL_UNSIGNED_INT_24_8              0x84FA
#تعریف_کړه GL_DEPTH24_STENCIL8               0x88F0
#تعریف_کړه GL_UNSIGNED_NORMALIZED            0x8C17
#تعریف_کړه GL_DRAW_FRAMEBUFFER_BINDING       0x8CA6
#تعریف_کړه GL_READ_FRAMEBUFFER               0x8CA8
#تعریف_کړه GL_DRAW_FRAMEBUFFER               0x8CA9
#تعریف_کړه GL_READ_FRAMEBUFFER_BINDING       0x8CAA
#تعریف_کړه GL_RENDERBUFFER_SAMPLES           0x8CAB
#تعریف_کړه GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER 0x8CD4
#تعریف_کړه GL_MAX_COLOR_ATTACHMENTS          0x8CDF
#تعریف_کړه GL_COLOR_ATTACHMENT1              0x8CE1
#تعریف_کړه GL_COLOR_ATTACHMENT2              0x8CE2
#تعریف_کړه GL_COLOR_ATTACHMENT3              0x8CE3
#تعریف_کړه GL_COLOR_ATTACHMENT4              0x8CE4
#تعریف_کړه GL_COLOR_ATTACHMENT5              0x8CE5
#تعریف_کړه GL_COLOR_ATTACHMENT6              0x8CE6
#تعریف_کړه GL_COLOR_ATTACHMENT7              0x8CE7
#تعریف_کړه GL_COLOR_ATTACHMENT8              0x8CE8
#تعریف_کړه GL_COLOR_ATTACHMENT9              0x8CE9
#تعریف_کړه GL_COLOR_ATTACHMENT10             0x8CEA
#تعریف_کړه GL_COLOR_ATTACHMENT11             0x8CEB
#تعریف_کړه GL_COLOR_ATTACHMENT12             0x8CEC
#تعریف_کړه GL_COLOR_ATTACHMENT13             0x8CED
#تعریف_کړه GL_COLOR_ATTACHMENT14             0x8CEE
#تعریف_کړه GL_COLOR_ATTACHMENT15             0x8CEF
#تعریف_کړه GL_COLOR_ATTACHMENT16             0x8CF0
#تعریف_کړه GL_COLOR_ATTACHMENT17             0x8CF1
#تعریف_کړه GL_COLOR_ATTACHMENT18             0x8CF2
#تعریف_کړه GL_COLOR_ATTACHMENT19             0x8CF3
#تعریف_کړه GL_COLOR_ATTACHMENT20             0x8CF4
#تعریف_کړه GL_COLOR_ATTACHMENT21             0x8CF5
#تعریف_کړه GL_COLOR_ATTACHMENT22             0x8CF6
#تعریف_کړه GL_COLOR_ATTACHMENT23             0x8CF7
#تعریف_کړه GL_COLOR_ATTACHMENT24             0x8CF8
#تعریف_کړه GL_COLOR_ATTACHMENT25             0x8CF9
#تعریف_کړه GL_COLOR_ATTACHMENT26             0x8CFA
#تعریف_کړه GL_COLOR_ATTACHMENT27             0x8CFB
#تعریف_کړه GL_COLOR_ATTACHMENT28             0x8CFC
#تعریف_کړه GL_COLOR_ATTACHMENT29             0x8CFD
#تعریف_کړه GL_COLOR_ATTACHMENT30             0x8CFE
#تعریف_کړه GL_COLOR_ATTACHMENT31             0x8CFF
#تعریف_کړه GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE 0x8D56
#تعریف_کړه GL_MAX_SAMPLES                    0x8D57
#تعریف_کړه GL_HALF_FLOAT                     0x140B
#تعریف_کړه GL_MAP_READ_بټ                   0x0001
#تعریف_کړه GL_MAP_WRITE_بټ                  0x0002
#تعریف_کړه GL_MAP_INVALIDATE_RANGE_بټ       0x0004
#تعریف_کړه GL_MAP_INVALIDATE_بفر_بټ      0x0008
#تعریف_کړه GL_MAP_FLUSH_EXPLICIT_بټ         0x0010
#تعریف_کړه GL_MAP_UNSYNCHRONIZED_بټ         0x0020
#تعریف_کړه GL_RG                             0x8227
#تعریف_کړه GL_RG_INTEGER                     0x8228
#تعریف_کړه GL_R8                             0x8229
#تعریف_کړه GL_RG8                            0x822B
#تعریف_کړه GL_R16F                           0x822D
#تعریف_کړه GL_R32F                           0x822E
#تعریف_کړه GL_RG16F                          0x822F
#تعریف_کړه GL_RG32F                          0x8230
#تعریف_کړه GL_R8I                            0x8231
#تعریف_کړه GL_R8UI                           0x8232
#تعریف_کړه GL_R16I                           0x8233
#تعریف_کړه GL_R16UI                          0x8234
#تعریف_کړه GL_R32I                           0x8235
#تعریف_کړه GL_R32UI                          0x8236
#تعریف_کړه GL_RG8I                           0x8237
#تعریف_کړه GL_RG8UI                          0x8238
#تعریف_کړه GL_RG16I                          0x8239
#تعریف_کړه GL_RG16UI                         0x823A
#تعریف_کړه GL_RG32I                          0x823B
#تعریف_کړه GL_RG32UI                         0x823C
#تعریف_کړه GL_راس_ARRAY_BINDING           0x85B5
#تعریف_کړه GL_R8_SNORM                       0x8F94
#تعریف_کړه GL_RG8_SNORM                      0x8F95
#تعریف_کړه GL_RGB8_SNORM                     0x8F96
#تعریف_کړه GL_RGBA8_SNORM                    0x8F97
#تعریف_کړه GL_SIGNED_NORMALIZED              0x8F9C
#تعریف_کړه GL_PRIMITIVE_RESTART_FIXED_شاخص  0x8D69
#تعریف_کړه GL_COPY_READ_بفر               0x8F36
#تعریف_کړه GL_COPY_WRITE_بفر              0x8F37
#تعریف_کړه GL_COPY_READ_بفر_BINDING       0x8F36
#تعریف_کړه GL_COPY_WRITE_بفر_BINDING      0x8F37
#تعریف_کړه GL_یوشان_بفر                 0x8A11
#تعریف_کړه GL_یوشان_بفر_BINDING         0x8A28
#تعریف_کړه GL_یوشان_بفر_پیل           0x8A29
#تعریف_کړه GL_یوشان_بفر_اندازه            0x8A2A
#تعریف_کړه GL_MAX_راس_یوشان_بلاکونه      0x8A2B
#تعریف_کړه GL_MAX_FRAGMENT_یوشان_بلاکونه    0x8A2D
#تعریف_کړه GL_MAX_COMBINED_یوشان_بلاکونه    0x8A2E
#تعریف_کړه GL_MAX_یوشان_بفر_BINDINGS    0x8A2F
#تعریف_کړه GL_MAX_یوشان_بلاک_اندازه         0x8A30
#تعریف_کړه GL_MAX_COMBINED_راس_یوشان_COMPONENTS 0x8A31
#تعریف_کړه GL_MAX_COMBINED_FRAGMENT_یوشان_COMPONENTS 0x8A33
#تعریف_کړه GL_یوشان_بفر_دننه_واټن_ALIGNMENT 0x8A34
#تعریف_کړه GL_فعال_یوشان_بلاک_MAX_NAME_اوږدتیا 0x8A35
#تعریف_کړه GL_فعال_یوشان_بلاکونه          0x8A36
#تعریف_کړه GL_یوشان_TYPE                   0x8A37
#تعریف_کړه GL_یوشان_اندازه                   0x8A38
#تعریف_کړه GL_یوشان_NAME_اوږدتیا            0x8A39
#تعریف_کړه GL_یوشان_بلاک_شاخص            0x8A3A
#تعریف_کړه GL_یوشان_دننه_واټن                 0x8A3B
#تعریف_کړه GL_یوشان_ARRAY_STRIDE           0x8A3C
#تعریف_کړه GL_یوشان_ماتریکس_STRIDE          0x8A3D
#تعریف_کړه GL_یوشان_IS_لیکه_MAJOR           0x8A3E
#تعریف_کړه GL_یوشان_بلاک_BINDING          0x8A3F
#تعریف_کړه GL_یوشان_بلاک_معلومات_اندازه        0x8A40
#تعریف_کړه GL_یوشان_بلاک_NAME_اوږدتیا      0x8A41
#تعریف_کړه GL_یوشان_بلاک_فعال_UNIFORMS  0x8A42
#تعریف_کړه GL_یوشان_بلاک_فعال_یوشان_INDICES 0x8A43
#تعریف_کړه GL_یوشان_بلاک_REFERENCED_BY_راس_SHADER 0x8A44
#تعریف_کړه GL_یوشان_بلاک_REFERENCED_BY_FRAGMENT_SHADER 0x8A46
#تعریف_کړه GL_INVALID_شاخص                  0xFFFFFFFFu
#تعریف_کړه GL_MAX_راس_OUTPUT_COMPONENTS   0x9122
#تعریف_کړه GL_MAX_FRAGMENT_ننوت_COMPONENTS  0x9125
#تعریف_کړه GL_MAX_SERVER_WAIT_TIMEOUT        0x9111
#تعریف_کړه GL_OBJECT_TYPE                    0x9112
#تعریف_کړه GL_SYNC_CONDITION                 0x9113
#تعریف_کړه GL_SYNC_حالت                    0x9114
#تعریف_کړه GL_SYNC_FLAGS                     0x9115
#تعریف_کړه GL_SYNC_FENCE                     0x9116
#تعریف_کړه GL_SYNC_GPU_COMMANDS_COMPLETE     0x9117
#تعریف_کړه GL_UNSIGNALED                     0x9118
#تعریف_کړه GL_SIGNALED                       0x9119
#تعریف_کړه GL_ALREADY_SIGNALED               0x911A
#تعریف_کړه GL_TIMEOUT_EXPIRED                0x911B
#تعریف_کړه GL_CONDITION_SATISFIED            0x911C
#تعریف_کړه GL_WAIT_FAILED                    0x911D
#تعریف_کړه GL_SYNC_FLUSH_COMMANDS_بټ        0x00000001
#تعریف_کړه GL_TIMEOUT_IGNORED                0xFFFFFFFFFFFFFFFFull
#تعریف_کړه GL_راس_ATTRIB_ARRAY_وېشونکی    0x88FE
#تعریف_کړه GL_ANY_SAMPLES_PASSED             0x8C2F
#تعریف_کړه GL_ANY_SAMPLES_PASSED_CONSERVATIVE 0x8D6A
#تعریف_کړه GL_SAMPLER_BINDING                0x8919
#تعریف_کړه GL_RGB10_A2UI                     0x906F
#تعریف_کړه GL_TEXTURE_SWIZZLE_R              0x8E42
#تعریف_کړه GL_TEXTURE_SWIZZLE_G              0x8E43
#تعریف_کړه GL_TEXTURE_SWIZZLE_B              0x8E44
#تعریف_کړه GL_TEXTURE_SWIZZLE_A              0x8E45
#تعریف_کړه GL_GREEN                          0x1904
#تعریف_کړه GL_BLUE                           0x1905
#تعریف_کړه GL_INT_2_10_10_10_REV             0x8D9F
#تعریف_کړه GL_TRANSFORM_FEEDBACK             0x8E22
#تعریف_کړه GL_TRANSFORM_FEEDBACK_PAUSED      0x8E23
#تعریف_کړه GL_TRANSFORM_FEEDBACK_فعال      0x8E24
#تعریف_کړه GL_TRANSFORM_FEEDBACK_BINDING     0x8E25
#تعریف_کړه GL_پروګرام_دوګونی_RETRIEVABLE_HINT 0x8257
#تعریف_کړه GL_پروګرام_دوګونی_اوږدتیا          0x8741
#تعریف_کړه GL_عدد_پروګرام_دوګونی_FORMATS     0x87FE
#تعریف_کړه GL_پروګرام_دوګونی_FORMATS         0x87FF
#تعریف_کړه GL_COMPRESSED_R11_EAC             0x9270
#تعریف_کړه GL_COMPRESSED_SIGNED_R11_EAC      0x9271
#تعریف_کړه GL_COMPRESSED_RG11_EAC            0x9272
#تعریف_کړه GL_COMPRESSED_SIGNED_RG11_EAC     0x9273
#تعریف_کړه GL_COMPRESSED_RGB8_ETC2           0x9274
#تعریف_کړه GL_COMPRESSED_SRGB8_ETC2          0x9275
#تعریف_کړه GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9276
#تعریف_کړه GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9277
#تعریف_کړه GL_COMPRESSED_RGBA8_ETC2_EAC      0x9278
#تعریف_کړه GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC 0x9279
#تعریف_کړه GL_TEXTURE_IMMUTABLE_FORMAT       0x912F
#تعریف_کړه GL_MAX_ELEMENT_شاخص              0x8D6B
#تعریف_کړه GL_عدد_SAMPLE_COUNTS              0x9380
#تعریف_کړه GL_TEXTURE_IMMUTABLE_پوړونه       0x82DF
تعريفنوع فراغ (GL_APIENTRYP PFNGLREADBUFFERPROC) (GLenum src);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWRANGEELEMENTSPROC) (GLenum ډېرپېښ, GLuint پیل, GLuint پای_ټکی, GLsizei شمېر, GLenum type, ثابت فراغ *indices);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXIMAGE3DPROC) (GLenum موخه, GLint level, GLint internalformat, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLint border, GLenum format, GLenum type, ثابت فراغ *pixels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSUBIMAGE3DPROC) (GLenum موخه, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLenum format, GLenum type, ثابت فراغ *pixels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYTEXSUBIMAGE3DPROC) (GLenum موخه, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei پلنوالی, GLsizei لوړوالی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOMPRESSEDTEXIMAGE3DPROC) (GLenum موخه, GLint level, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLint border, GLsizei image_اندازه, ثابت فراغ *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC) (GLenum موخه, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLenum format, GLsizei image_اندازه, ثابت فراغ *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENQUERIESPROC) (GLsizei n, GLuint *ids);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEQUERIESPROC) (GLsizei n, ثابت GLuint *ids);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISQUERYPROC) (GLuint id);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBEGINQUERYPROC) (GLenum موخه, GLuint id);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENDQUERYPROC) (GLenum موخه);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETQUERYIVPROC) (GLenum موخه, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETQUERYOBJECTUIVPROC) (GLuint id, GLenum pname, GLuint *params);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLUNMAPBUFFERPROC) (GLenum موخه);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETBUFFERPOINTERVPROC) (GLenum موخه, GLenum pname, فراغ **params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWBUFFERSPROC) (GLsizei n, ثابت GLenum *bufs);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX2X3FVPROC) (GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX3X2FVPROC) (GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX2X4FVPROC) (GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX4X2FVPROC) (GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX3X4FVPROC) (GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX4X3FVPROC) (GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLITFRAMEBUFFERPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield ماسک, GLenum filter);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC) (GLenum موخه, GLsizei samples, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURELAYERPROC) (GLenum موخه, GLenum attachment, GLuint texture, GLint level, GLint layer);
تعريفنوع فراغ *(GL_APIENTRYP PFNGLMAPBUFFERRANGEPROC) (GLenum موخه, GLintptr دننه_واټن_2, GLsizeiptr اوږدتیا, GLbitfield access);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEPROC) (GLenum موخه, GLintptr دننه_واټن_2, GLsizeiptr اوږدتیا);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDVERTEXARRAYPROC) (GLuint array);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEVERTEXARRAYSPROC) (GLsizei n, ثابت GLuint *arrays);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint *arrays);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISVERTEXARRAYPROC) (GLuint array);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTEGERI_VPROC) (GLenum موخه, GLuint شاخص, GLint *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBEGINTRANSFORMFEEDBACKPROC) (GLenum primitive_ډېرپېښ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENDTRANSFORMFEEDBACKPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDBUFFERRANGEPROC) (GLenum موخه, GLuint شاخص, GLuint بفر_2, GLintptr دننه_واټن_2, GLsizeiptr اندازه);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDBUFFERBASEPROC) (GLenum موخه, GLuint شاخص, GLuint بفر_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTRANSFORMFEEDBACKVARYINGSPROC) (GLuint پروګرام, GLsizei شمېر, ثابت GLchar *ثابت*varyings, GLenum بفر_ډېرپېښ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTRANSFORMFEEDBACKVARYINGPROC) (GLuint پروګرام, GLuint شاخص, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLsizei *اندازه, GLenum *type, GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBIPOINTERPROC) (GLuint شاخص, GLint اندازه, GLenum type, GLsizei stride, ثابت فراغ *اشاره_ګر_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETVERTEXATTRIBIIVPROC) (GLuint شاخص, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETVERTEXATTRIBIUIVPROC) (GLuint شاخص, GLenum pname, GLuint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBI4IPROC) (GLuint شاخص, GLint x, GLint y, GLint z, GLint w);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBI4UIPROC) (GLuint شاخص, GLuint x, GLuint y, GLuint z, GLuint w);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBI4IVPROC) (GLuint شاخص, ثابت GLint *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBI4UIVPROC) (GLuint شاخص, ثابت GLuint *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETUNIFORMUIVPROC) (GLuint پروګرام, GLint location, GLuint *params);
تعريفنوع GLint (GL_APIENTRYP PFNGLGETFRAGDATALOCATIONPROC) (GLuint پروګرام, ثابت GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1UIPROC) (GLint location, GLuint v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2UIPROC) (GLint location, GLuint v0, GLuint v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3UIPROC) (GLint location, GLuint v0, GLuint v1, GLuint v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4UIPROC) (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1UIVPROC) (GLint location, GLsizei شمېر, ثابت GLuint *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2UIVPROC) (GLint location, GLsizei شمېر, ثابت GLuint *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3UIVPROC) (GLint location, GLsizei شمېر, ثابت GLuint *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4UIVPROC) (GLint location, GLsizei شمېر, ثابت GLuint *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARBUFFERIVPROC) (GLenum بفر_2, GLint drawbuffer, ثابت GLint *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARBUFFERUIVPROC) (GLenum بفر_2, GLint drawbuffer, ثابت GLuint *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARBUFFERFVPROC) (GLenum بفر_2, GLint drawbuffer, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARBUFFERFIPROC) (GLenum بفر_2, GLint drawbuffer, GLfloat ژوروالی_2, GLint stencil);
تعريفنوع ثابت GLubyte *(GL_APIENTRYP PFNGLGETSTRINGIPROC) (GLenum name, GLuint شاخص);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYBUFFERSUBDATAPROC) (GLenum read_موخه, GLenum write_موخه, GLintptr read_دننه_واټن, GLintptr write_دننه_واټن, GLsizeiptr اندازه);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETUNIFORMINDICESPROC) (GLuint پروګرام, GLsizei یوشان_شمېر, ثابت GLchar *ثابت*یوشان_نومونه, GLuint *یوشان_Indices);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETACTIVEUNIFORMSIVPROC) (GLuint پروګرام, GLsizei یوشان_شمېر, ثابت GLuint *یوشان_Indices, GLenum pname, GLint *params);
تعريفنوع GLuint (GL_APIENTRYP PFNGLGETUNIFORMBLOCKINDEXPROC) (GLuint پروګرام, ثابت GLchar *یوشان_بلاک_Name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKIVPROC) (GLuint پروګرام, GLuint یوشان_بلاک_شاخص, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC) (GLuint پروګرام, GLuint یوشان_بلاک_شاخص, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLchar *یوشان_بلاک_Name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMBLOCKBINDINGPROC) (GLuint پروګرام, GLuint یوشان_بلاک_شاخص, GLuint یوشان_بلاک_Binding);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDPROC) (GLenum ډېرپېښ, GLint لومړی, GLsizei شمېر, GLsizei instancecount);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDPROC) (GLenum ډېرپېښ, GLsizei شمېر, GLenum type, ثابت فراغ *indices, GLsizei instancecount);
تعريفنوع GLsync (GL_APIENTRYP PFNGLFENCESYNCPROC) (GLenum condition, GLbitfield flags);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISSYNCPROC) (GLsync sync);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETESYNCPROC) (GLsync sync);
تعريفنوع GLenum (GL_APIENTRYP PFNGLCLIENTWAITSYNCPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
تعريفنوع فراغ (GL_APIENTRYP PFNGLWAITSYNCPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTEGER64VPROC) (GLenum pname, GLint64 *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSYNCIVPROC) (GLsync sync, GLenum pname, GLsizei شمېر, GLsizei *اوږدتیا, GLint *ارزښتونه);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTEGER64I_VPROC) (GLenum موخه, GLuint شاخص, GLint64 *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETBUFFERPARAMETERI64VPROC) (GLenum موخه, GLenum pname, GLint64 *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENSAMPLERSPROC) (GLsizei شمېر, GLuint *samplers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETESAMPLERSPROC) (GLsizei شمېر, ثابت GLuint *samplers);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISSAMPLERPROC) (GLuint sampler);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDSAMPLERPROC) (GLuint unit, GLuint sampler);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIPROC) (GLuint sampler, GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, ثابت GLint *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERFPROC) (GLuint sampler, GLenum pname, GLfloat param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, ثابت GLfloat *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBDIVISORPROC) (GLuint شاخص, GLuint وېشونکی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDTRANSFORMFEEDBACKPROC) (GLenum موخه, GLuint id);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETETRANSFORMFEEDBACKSPROC) (GLsizei n, ثابت GLuint *ids);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENTRANSFORMFEEDBACKSPROC) (GLsizei n, GLuint *ids);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISTRANSFORMFEEDBACKPROC) (GLuint id);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPAUSETRANSFORMFEEDBACKPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRESUMETRANSFORMFEEDBACKPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMBINARYPROC) (GLuint پروګرام, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLenum *دوګونی_Format, فراغ *دوګونی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMBINARYPROC) (GLuint پروګرام, GLenum دوګونی_Format, ثابت فراغ *دوګونی, GLsizei اوږدتیا);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMPARAMETERIPROC) (GLuint پروګرام, GLenum pname, GLint ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLINVALIDATEFRAMEBUFFERPROC) (GLenum موخه, GLsizei عدد_Attachments, ثابت GLenum *attachments);
تعريفنوع فراغ (GL_APIENTRYP PFNGLINVALIDATESUBFRAMEBUFFERPROC) (GLenum موخه, GLsizei عدد_Attachments, ثابت GLenum *attachments, GLint x, GLint y, GLsizei پلنوالی, GLsizei لوړوالی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE2DPROC) (GLenum موخه, GLsizei پوړونه, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE3DPROC) (GLenum موخه, GLsizei پوړونه, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTERNALFORMATIVPROC) (GLenum موخه, GLenum internalformat, GLenum pname, GLsizei شمېر, GLint *params);
#إذا GL_GLES_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Read_بفر (GLenum src);
GL_APICALL فراغ GL_APIENTRY glDrawRangeElements (GLenum ډېرپېښ, GLuint پیل, GLuint پای_ټکی, GLsizei شمېر, GLenum type, ثابت فراغ *indices);
GL_APICALL فراغ GL_APIENTRY glTexImage3D (GLenum موخه, GLint level, GLint internalformat, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLint border, GLenum format, GLenum type, ثابت فراغ *pixels);
GL_APICALL فراغ GL_APIENTRY glTexSubImage3D (GLenum موخه, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLenum format, GLenum type, ثابت فراغ *pixels);
GL_APICALL فراغ GL_APIENTRY glCopyTexSubImage3D (GLenum موخه, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei پلنوالی, GLsizei لوړوالی);
GL_APICALL فراغ GL_APIENTRY glCompressedTexImage3D (GLenum موخه, GLint level, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLint border, GLsizei image_اندازه, ثابت فراغ *معلومات);
GL_APICALL فراغ GL_APIENTRY glCompressedTexSubImage3D (GLenum موخه, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2, GLenum format, GLsizei image_اندازه, ثابت فراغ *معلومات);
GL_APICALL فراغ GL_APIENTRY glGenQueries (GLsizei n, GLuint *ids);
GL_APICALL فراغ GL_APIENTRY glDeleteQueries (GLsizei n, ثابت GLuint *ids);
GL_APICALL GLboolean GL_APIENTRY glIsQuery (GLuint id);
GL_APICALL فراغ GL_APIENTRY glBeginQuery (GLenum موخه, GLuint id);
GL_APICALL فراغ GL_APIENTRY gl_پای_ټکی_Query (GLenum موخه);
GL_APICALL فراغ GL_APIENTRY glGetQueryiv (GLenum موخه, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetQueryObjectuiv (GLuint id, GLenum pname, GLuint *params);
GL_APICALL GLboolean GL_APIENTRY gl_Unmap_بفر (GLenum موخه);
GL_APICALL فراغ GL_APIENTRY gl_Get_بفر_Pointerv (GLenum موخه, GLenum pname, فراغ **params);
GL_APICALL فراغ GL_APIENTRY glDrawBuffers (GLsizei n, ثابت GLenum *bufs);
GL_APICALL فراغ GL_APIENTRY gl_یوشان_Matrix2x3fv (GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_یوشان_Matrix3x2fv (GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_یوشان_Matrix2x4fv (GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_یوشان_Matrix4x2fv (GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_یوشان_Matrix3x4fv (GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_یوشان_Matrix4x3fv (GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY glBlitFramebuffer (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield ماسک, GLenum filter);
GL_APICALL فراغ GL_APIENTRY glRenderbufferStorageMultisample (GLenum موخه, GLsizei samples, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
GL_APICALL فراغ GL_APIENTRY glFramebufferTextureLayer (GLenum موخه, GLenum attachment, GLuint texture, GLint level, GLint layer);
GL_APICALL فراغ *GL_APIENTRY gl_Map_بفر_Range (GLenum موخه, GLintptr دننه_واټن_2, GLsizeiptr اوږدتیا, GLbitfield access);
GL_APICALL فراغ GL_APIENTRY gl_Flush_Mapped_بفر_Range (GLenum موخه, GLintptr دننه_واټن_2, GLsizeiptr اوږدتیا);
GL_APICALL فراغ GL_APIENTRY gl_Bind_راس_Array (GLuint array);
GL_APICALL فراغ GL_APIENTRY gl_Delete_راس_Arrays (GLsizei n, ثابت GLuint *arrays);
GL_APICALL فراغ GL_APIENTRY gl_Gen_راس_Arrays (GLsizei n, GLuint *arrays);
GL_APICALL GLboolean GL_APIENTRY gl_Is_راس_Array (GLuint array);
GL_APICALL فراغ GL_APIENTRY glGetIntegeri_v (GLenum موخه, GLuint شاخص, GLint *معلومات);
GL_APICALL فراغ GL_APIENTRY glBeginTransformFeedback (GLenum primitive_ډېرپېښ);
GL_APICALL فراغ GL_APIENTRY gl_پای_ټکی_Transform_Feedback (فراغ);
GL_APICALL فراغ GL_APIENTRY gl_Bind_بفر_Range (GLenum موخه, GLuint شاخص, GLuint بفر_2, GLintptr دننه_واټن_2, GLsizeiptr اندازه);
GL_APICALL فراغ GL_APIENTRY gl_Bind_بفر_بنسټ (GLenum موخه, GLuint شاخص, GLuint بفر_2);
GL_APICALL فراغ GL_APIENTRY glTransformFeedbackVaryings (GLuint پروګرام, GLsizei شمېر, ثابت GLchar *ثابت*varyings, GLenum بفر_ډېرپېښ);
GL_APICALL فراغ GL_APIENTRY glGetTransformFeedbackVarying (GLuint پروګرام, GLuint شاخص, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLsizei *اندازه, GLenum *type, GLchar *name);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib_IPointer (GLuint شاخص, GLint اندازه, GLenum type, GLsizei stride, ثابت فراغ *اشاره_ګر_2);
GL_APICALL فراغ GL_APIENTRY gl_Get_راس_Attrib_Iiv (GLuint شاخص, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY gl_Get_راس_Attrib_Iuiv (GLuint شاخص, GLenum pname, GLuint *params);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib_I4i (GLuint شاخص, GLint x, GLint y, GLint z, GLint w);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib_I4ui (GLuint شاخص, GLuint x, GLuint y, GLuint z, GLuint w);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib_I4iv (GLuint شاخص, ثابت GLint *v);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib_I4uiv (GLuint شاخص, ثابت GLuint *v);
GL_APICALL فراغ GL_APIENTRY glGetUniformuiv (GLuint پروګرام, GLint location, GLuint *params);
GL_APICALL GLint GL_APIENTRY gl_Get_Frag_معلومات_Location (GLuint پروګرام, ثابت GLchar *name);
GL_APICALL فراغ GL_APIENTRY glUniform1ui (GLint location, GLuint v0);
GL_APICALL فراغ GL_APIENTRY glUniform2ui (GLint location, GLuint v0, GLuint v1);
GL_APICALL فراغ GL_APIENTRY glUniform3ui (GLint location, GLuint v0, GLuint v1, GLuint v2);
GL_APICALL فراغ GL_APIENTRY glUniform4ui (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
GL_APICALL فراغ GL_APIENTRY glUniform1uiv (GLint location, GLsizei شمېر, ثابت GLuint *ارزښت);
GL_APICALL فراغ GL_APIENTRY glUniform2uiv (GLint location, GLsizei شمېر, ثابت GLuint *ارزښت);
GL_APICALL فراغ GL_APIENTRY glUniform3uiv (GLint location, GLsizei شمېر, ثابت GLuint *ارزښت);
GL_APICALL فراغ GL_APIENTRY glUniform4uiv (GLint location, GLsizei شمېر, ثابت GLuint *ارزښت);
GL_APICALL فراغ GL_APIENTRY glClearBufferiv (GLenum بفر_2, GLint drawbuffer, ثابت GLint *ارزښت);
GL_APICALL فراغ GL_APIENTRY glClearBufferuiv (GLenum بفر_2, GLint drawbuffer, ثابت GLuint *ارزښت);
GL_APICALL فراغ GL_APIENTRY glClearBufferfv (GLenum بفر_2, GLint drawbuffer, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY glClearBufferfi (GLenum بفر_2, GLint drawbuffer, GLfloat ژوروالی_2, GLint stencil);
GL_APICALL ثابت GLubyte *GL_APIENTRY glGetStringi (GLenum name, GLuint شاخص);
GL_APICALL فراغ GL_APIENTRY gl_Copy_بفر_Sub_معلومات (GLenum read_موخه, GLenum write_موخه, GLintptr read_دننه_واټن, GLintptr write_دننه_واټن, GLsizeiptr اندازه);
GL_APICALL فراغ GL_APIENTRY gl_Get_یوشان_Indices (GLuint پروګرام, GLsizei یوشان_شمېر, ثابت GLchar *ثابت*یوشان_نومونه, GLuint *یوشان_Indices);
GL_APICALL فراغ GL_APIENTRY gl_Get_فعال_Uniformsiv (GLuint پروګرام, GLsizei یوشان_شمېر, ثابت GLuint *یوشان_Indices, GLenum pname, GLint *params);
GL_APICALL GLuint GL_APIENTRY gl_Get_یوشان_بلاک_شاخص (GLuint پروګرام, ثابت GLchar *یوشان_بلاک_Name);
GL_APICALL فراغ GL_APIENTRY gl_Get_فعال_یوشان_Blockiv (GLuint پروګرام, GLuint یوشان_بلاک_شاخص, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY gl_Get_فعال_یوشان_بلاک_Name (GLuint پروګرام, GLuint یوشان_بلاک_شاخص, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLchar *یوشان_بلاک_Name);
GL_APICALL فراغ GL_APIENTRY gl_یوشان_بلاک_Binding (GLuint پروګرام, GLuint یوشان_بلاک_شاخص, GLuint یوشان_بلاک_Binding);
GL_APICALL فراغ GL_APIENTRY glDrawArraysInstanced (GLenum ډېرپېښ, GLint لومړی, GLsizei شمېر, GLsizei instancecount);
GL_APICALL فراغ GL_APIENTRY glDrawElementsInstanced (GLenum ډېرپېښ, GLsizei شمېر, GLenum type, ثابت فراغ *indices, GLsizei instancecount);
GL_APICALL GLsync GL_APIENTRY glFenceSync (GLenum condition, GLbitfield flags);
GL_APICALL GLboolean GL_APIENTRY glIsSync (GLsync sync);
GL_APICALL فراغ GL_APIENTRY glDeleteSync (GLsync sync);
GL_APICALL GLenum GL_APIENTRY glClientWaitSync (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_APICALL فراغ GL_APIENTRY glWaitSync (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_APICALL فراغ GL_APIENTRY glGetInteger64v (GLenum pname, GLint64 *معلومات);
GL_APICALL فراغ GL_APIENTRY glGetSynciv (GLsync sync, GLenum pname, GLsizei شمېر, GLsizei *اوږدتیا, GLint *ارزښتونه);
GL_APICALL فراغ GL_APIENTRY glGetInteger64i_v (GLenum موخه, GLuint شاخص, GLint64 *معلومات);
GL_APICALL فراغ GL_APIENTRY gl_Get_بفر_Parameteri64v (GLenum موخه, GLenum pname, GLint64 *params);
GL_APICALL فراغ GL_APIENTRY glGenSamplers (GLsizei شمېر, GLuint *samplers);
GL_APICALL فراغ GL_APIENTRY glDeleteSamplers (GLsizei شمېر, ثابت GLuint *samplers);
GL_APICALL GLboolean GL_APIENTRY glIsSampler (GLuint sampler);
GL_APICALL فراغ GL_APIENTRY glBindSampler (GLuint unit, GLuint sampler);
GL_APICALL فراغ GL_APIENTRY glSamplerParameteri (GLuint sampler, GLenum pname, GLint param);
GL_APICALL فراغ GL_APIENTRY glSamplerParameteriv (GLuint sampler, GLenum pname, ثابت GLint *param);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterf (GLuint sampler, GLenum pname, GLfloat param);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterfv (GLuint sampler, GLenum pname, ثابت GLfloat *param);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameteriv (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameterfv (GLuint sampler, GLenum pname, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib_وېشونکی (GLuint شاخص, GLuint وېشونکی);
GL_APICALL فراغ GL_APIENTRY glBindTransformFeedback (GLenum موخه, GLuint id);
GL_APICALL فراغ GL_APIENTRY glDeleteTransformFeedbacks (GLsizei n, ثابت GLuint *ids);
GL_APICALL فراغ GL_APIENTRY glGenTransformFeedbacks (GLsizei n, GLuint *ids);
GL_APICALL GLboolean GL_APIENTRY glIsTransformFeedback (GLuint id);
GL_APICALL فراغ GL_APIENTRY glPauseTransformFeedback (فراغ);
GL_APICALL فراغ GL_APIENTRY glResumeTransformFeedback (فراغ);
GL_APICALL فراغ GL_APIENTRY gl_Get_پروګرام_دوګونی (GLuint پروګرام, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLenum *دوګونی_Format, فراغ *دوګونی);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_دوګونی (GLuint پروګرام, GLenum دوګونی_Format, ثابت فراغ *دوګونی, GLsizei اوږدتیا);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Parameteri (GLuint پروګرام, GLenum pname, GLint ارزښت);
GL_APICALL فراغ GL_APIENTRY glInvalidateFramebuffer (GLenum موخه, GLsizei عدد_Attachments, ثابت GLenum *attachments);
GL_APICALL فراغ GL_APIENTRY glInvalidateSubFramebuffer (GLenum موخه, GLsizei عدد_Attachments, ثابت GLenum *attachments, GLint x, GLint y, GLsizei پلنوالی, GLsizei لوړوالی);
GL_APICALL فراغ GL_APIENTRY glTexStorage2D (GLenum موخه, GLsizei پوړونه, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی);
GL_APICALL فراغ GL_APIENTRY glTexStorage3D (GLenum موخه, GLsizei پوړونه, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی, GLsizei ژوروالی_2);
GL_APICALL فراغ GL_APIENTRY glGetInternalformativ (GLenum موخه, GLenum internalformat, GLenum pname, GLsizei شمېر, GLint *params);
#د_که_پای
#د_که_پای /* GL_ES_VERSION_3_0 */

#که_نه_تعریف_شوی GL_ES_نسخه_3_1
#تعریف_کړه GL_ES_نسخه_3_1 1
#تعریف_کړه GL_COMPUTE_SHADER                 0x91B9
#تعریف_کړه GL_MAX_COMPUTE_یوشان_بلاکونه     0x91BB
#تعریف_کړه GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS 0x91BC
#تعریف_کړه GL_MAX_COMPUTE_IMAGE_UNIFORMS     0x91BD
#تعریف_کړه GL_MAX_COMPUTE_SHARED_حافظه_اندازه 0x8262
#تعریف_کړه GL_MAX_COMPUTE_یوشان_COMPONENTS 0x8263
#تعریف_کړه GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS 0x8264
#تعریف_کړه GL_MAX_COMPUTE_ATOMIC_COUNTERS    0x8265
#تعریف_کړه GL_MAX_COMBINED_COMPUTE_یوشان_COMPONENTS 0x8266
#تعریف_کړه GL_MAX_COMPUTE_WORK_ډله_INVOCATIONS 0x90EB
#تعریف_کړه GL_MAX_COMPUTE_WORK_ډله_شمېر   0x91BE
#تعریف_کړه GL_MAX_COMPUTE_WORK_ډله_اندازه    0x91BF
#تعریف_کړه GL_COMPUTE_WORK_ډله_اندازه        0x8267
#تعریف_کړه GL_DISPATCH_غیرمستقیم_بفر       0x90EE
#تعریف_کړه GL_DISPATCH_غیرمستقیم_بفر_BINDING 0x90EF
#تعریف_کړه GL_COMPUTE_SHADER_بټ             0x00000020
#تعریف_کړه GL_DRAW_غیرمستقیم_بفر           0x8F3F
#تعریف_کړه GL_DRAW_غیرمستقیم_بفر_BINDING   0x8F43
#تعریف_کړه GL_MAX_یوشان_LOCATIONS          0x826E
#تعریف_کړه GL_FRAMEBUFFER_DEFAULT_پلنوالی      0x9310
#تعریف_کړه GL_FRAMEBUFFER_DEFAULT_لوړوالی     0x9311
#تعریف_کړه GL_FRAMEBUFFER_DEFAULT_SAMPLES    0x9313
#تعریف_کړه GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS 0x9314
#تعریف_کړه GL_MAX_FRAMEBUFFER_پلنوالی          0x9315
#تعریف_کړه GL_MAX_FRAMEBUFFER_لوړوالی         0x9316
#تعریف_کړه GL_MAX_FRAMEBUFFER_SAMPLES        0x9318
#تعریف_کړه GL_یوشان                        0x92E1
#تعریف_کړه GL_یوشان_بلاک                  0x92E2
#تعریف_کړه GL_پروګرام_ننوت                  0x92E3
#تعریف_کړه GL_پروګرام_OUTPUT                 0x92E4
#تعریف_کړه GL_بفر_VARIABLE                0x92E5
#تعریف_کړه GL_SHADER_STORAGE_بلاک           0x92E6
#تعریف_کړه GL_ATOMIC_COUNTER_بفر          0x92C0
#تعریف_کړه GL_TRANSFORM_FEEDBACK_VARYING     0x92F4
#تعریف_کړه GL_فعال_RESOURCES               0x92F5
#تعریف_کړه GL_MAX_NAME_اوږدتیا                0x92F6
#تعریف_کړه GL_MAX_عدد_فعال_VARIABLES       0x92F7
#تعریف_کړه GL_NAME_اوږدتیا                    0x92F9
#تعریف_کړه GL_TYPE                           0x92FA
#تعریف_کړه GL_ARRAY_اندازه                     0x92FB
#تعریف_کړه GL_دننه_واټن                         0x92FC
#تعریف_کړه GL_بلاک_شاخص                    0x92FD
#تعریف_کړه GL_ARRAY_STRIDE                   0x92FE
#تعریف_کړه GL_ماتریکس_STRIDE                  0x92FF
#تعریف_کړه GL_IS_لیکه_MAJOR                   0x9300
#تعریف_کړه GL_ATOMIC_COUNTER_بفر_شاخص    0x9301
#تعریف_کړه GL_بفر_BINDING                 0x9302
#تعریف_کړه GL_بفر_معلومات_اندازه               0x9303
#تعریف_کړه GL_عدد_فعال_VARIABLES           0x9304
#تعریف_کړه GL_فعال_VARIABLES               0x9305
#تعریف_کړه GL_REFERENCED_BY_راس_SHADER    0x9306
#تعریف_کړه GL_REFERENCED_BY_FRAGMENT_SHADER  0x930A
#تعریف_کړه GL_REFERENCED_BY_COMPUTE_SHADER   0x930B
#تعریف_کړه GL_سر_LEVEL_ARRAY_اندازه           0x930C
#تعریف_کړه GL_سر_LEVEL_ARRAY_STRIDE         0x930D
#تعریف_کړه GL_LOCATION                       0x930E
#تعریف_کړه GL_راس_SHADER_بټ              0x00000001
#تعریف_کړه GL_FRAGMENT_SHADER_بټ            0x00000002
#تعریف_کړه GL_ALL_SHADER_بټونه                0xFFFFFFFF
#تعریف_کړه GL_پروګرام_SEPARABLE              0x8258
#تعریف_کړه GL_فعال_پروګرام                 0x8259
#تعریف_کړه GL_پروګرام_PIPELINE_BINDING       0x825A
#تعریف_کړه GL_ATOMIC_COUNTER_بفر_BINDING  0x92C1
#تعریف_کړه GL_ATOMIC_COUNTER_بفر_پیل    0x92C2
#تعریف_کړه GL_ATOMIC_COUNTER_بفر_اندازه     0x92C3
#تعریف_کړه GL_MAX_راس_ATOMIC_COUNTER_BUFFERS 0x92CC
#تعریف_کړه GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS 0x92D0
#تعریف_کړه GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS 0x92D1
#تعریف_کړه GL_MAX_راس_ATOMIC_COUNTERS     0x92D2
#تعریف_کړه GL_MAX_FRAGMENT_ATOMIC_COUNTERS   0x92D6
#تعریف_کړه GL_MAX_COMBINED_ATOMIC_COUNTERS   0x92D7
#تعریف_کړه GL_MAX_ATOMIC_COUNTER_بفر_اندازه 0x92D8
#تعریف_کړه GL_MAX_ATOMIC_COUNTER_بفر_BINDINGS 0x92DC
#تعریف_کړه GL_فعال_ATOMIC_COUNTER_BUFFERS  0x92D9
#تعریف_کړه GL_UNSIGNED_INT_ATOMIC_COUNTER    0x92DB
#تعریف_کړه GL_MAX_IMAGE_UNITS                0x8F38
#تعریف_کړه GL_MAX_راس_IMAGE_UNIFORMS      0x90CA
#تعریف_کړه GL_MAX_FRAGMENT_IMAGE_UNIFORMS    0x90CE
#تعریف_کړه GL_MAX_COMBINED_IMAGE_UNIFORMS    0x90CF
#تعریف_کړه GL_IMAGE_BINDING_NAME             0x8F3A
#تعریف_کړه GL_IMAGE_BINDING_LEVEL            0x8F3B
#تعریف_کړه GL_IMAGE_BINDING_LAYERED          0x8F3C
#تعریف_کړه GL_IMAGE_BINDING_LAYER            0x8F3D
#تعریف_کړه GL_IMAGE_BINDING_ACCESS           0x8F3E
#تعریف_کړه GL_IMAGE_BINDING_FORMAT           0x906E
#تعریف_کړه GL_راس_ATTRIB_ARRAY_BARRIER_بټ 0x00000001
#تعریف_کړه GL_ELEMENT_ARRAY_BARRIER_بټ      0x00000002
#تعریف_کړه GL_یوشان_BARRIER_بټ            0x00000004
#تعریف_کړه GL_TEXTURE_FETCH_BARRIER_بټ      0x00000008
#تعریف_کړه GL_SHADER_IMAGE_ACCESS_BARRIER_بټ 0x00000020
#تعریف_کړه GL_COMMAND_BARRIER_بټ            0x00000040
#تعریف_کړه GL_PIXEL_بفر_BARRIER_بټ       0x00000080
#تعریف_کړه GL_TEXTURE_UPDATE_BARRIER_بټ     0x00000100
#تعریف_کړه GL_بفر_UPDATE_BARRIER_بټ      0x00000200
#تعریف_کړه GL_FRAMEBUFFER_BARRIER_بټ        0x00000400
#تعریف_کړه GL_TRANSFORM_FEEDBACK_BARRIER_بټ 0x00000800
#تعریف_کړه GL_ATOMIC_COUNTER_BARRIER_بټ     0x00001000
#تعریف_کړه GL_ALL_BARRIER_بټونه               0xFFFFFFFF
#تعریف_کړه GL_IMAGE_2D                       0x904D
#تعریف_کړه GL_IMAGE_3D                       0x904E
#تعریف_کړه GL_IMAGE_CUBE                     0x9050
#تعریف_کړه GL_IMAGE_2D_ARRAY                 0x9053
#تعریف_کړه GL_INT_IMAGE_2D                   0x9058
#تعریف_کړه GL_INT_IMAGE_3D                   0x9059
#تعریف_کړه GL_INT_IMAGE_CUBE                 0x905B
#تعریف_کړه GL_INT_IMAGE_2D_ARRAY             0x905E
#تعریف_کړه GL_UNSIGNED_INT_IMAGE_2D          0x9063
#تعریف_کړه GL_UNSIGNED_INT_IMAGE_3D          0x9064
#تعریف_کړه GL_UNSIGNED_INT_IMAGE_CUBE        0x9066
#تعریف_کړه GL_UNSIGNED_INT_IMAGE_2D_ARRAY    0x9069
#تعریف_کړه GL_IMAGE_FORMAT_COMPATIBILITY_TYPE 0x90C7
#تعریف_کړه GL_IMAGE_FORMAT_COMPATIBILITY_BY_اندازه 0x90C8
#تعریف_کړه GL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS 0x90C9
#تعریف_کړه GL_READ_ONLY                      0x88B8
#تعریف_کړه GL_WRITE_ONLY                     0x88B9
#تعریف_کړه GL_READ_WRITE                     0x88BA
#تعریف_کړه GL_SHADER_STORAGE_بفر          0x90D2
#تعریف_کړه GL_SHADER_STORAGE_بفر_BINDING  0x90D3
#تعریف_کړه GL_SHADER_STORAGE_بفر_پیل    0x90D4
#تعریف_کړه GL_SHADER_STORAGE_بفر_اندازه     0x90D5
#تعریف_کړه GL_MAX_راس_SHADER_STORAGE_بلاکونه 0x90D6
#تعریف_کړه GL_MAX_FRAGMENT_SHADER_STORAGE_بلاکونه 0x90DA
#تعریف_کړه GL_MAX_COMPUTE_SHADER_STORAGE_بلاکونه 0x90DB
#تعریف_کړه GL_MAX_COMBINED_SHADER_STORAGE_بلاکونه 0x90DC
#تعریف_کړه GL_MAX_SHADER_STORAGE_بفر_BINDINGS 0x90DD
#تعریف_کړه GL_MAX_SHADER_STORAGE_بلاک_اندازه  0x90DE
#تعریف_کړه GL_SHADER_STORAGE_بفر_دننه_واټن_ALIGNMENT 0x90DF
#تعریف_کړه GL_SHADER_STORAGE_BARRIER_بټ     0x00002000
#تعریف_کړه GL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES 0x8F39
#تعریف_کړه GL_ژوروالی_STENCIL_TEXTURE_ډېرپېښ     0x90EA
#تعریف_کړه GL_STENCIL_شاخص                  0x1901
#تعریف_کړه GL_MIN_پروګرام_TEXTURE_GATHER_دننه_واټن 0x8E5E
#تعریف_کړه GL_MAX_پروګرام_TEXTURE_GATHER_دننه_واټن 0x8E5F
#تعریف_کړه GL_SAMPLE_POSITION                0x8E50
#تعریف_کړه GL_SAMPLE_ماسک                    0x8E51
#تعریف_کړه GL_SAMPLE_ماسک_ارزښت              0x8E52
#تعریف_کړه GL_TEXTURE_2D_MULTISAMPLE         0x9100
#تعریف_کړه GL_MAX_SAMPLE_ماسک_ټکي          0x8E59
#تعریف_کړه GL_MAX_COLOR_TEXTURE_SAMPLES      0x910E
#تعریف_کړه GL_MAX_ژوروالی_TEXTURE_SAMPLES      0x910F
#تعریف_کړه GL_MAX_INTEGER_SAMPLES            0x9110
#تعریف_کړه GL_TEXTURE_BINDING_2D_MULTISAMPLE 0x9104
#تعریف_کړه GL_TEXTURE_SAMPLES                0x9106
#تعریف_کړه GL_TEXTURE_FIXED_SAMPLE_LOCATIONS 0x9107
#تعریف_کړه GL_TEXTURE_پلنوالی                  0x1000
#تعریف_کړه GL_TEXTURE_لوړوالی                 0x1001
#تعریف_کړه GL_TEXTURE_ژوروالی                  0x8071
#تعریف_کړه GL_TEXTURE_دننی_FORMAT        0x1003
#تعریف_کړه GL_TEXTURE_RED_اندازه               0x805C
#تعریف_کړه GL_TEXTURE_GREEN_اندازه             0x805D
#تعریف_کړه GL_TEXTURE_BLUE_اندازه              0x805E
#تعریف_کړه GL_TEXTURE_ALPHA_اندازه             0x805F
#تعریف_کړه GL_TEXTURE_ژوروالی_اندازه             0x884A
#تعریف_کړه GL_TEXTURE_STENCIL_اندازه           0x88F1
#تعریف_کړه GL_TEXTURE_SHARED_اندازه            0x8C3F
#تعریف_کړه GL_TEXTURE_RED_TYPE               0x8C10
#تعریف_کړه GL_TEXTURE_GREEN_TYPE             0x8C11
#تعریف_کړه GL_TEXTURE_BLUE_TYPE              0x8C12
#تعریف_کړه GL_TEXTURE_ALPHA_TYPE             0x8C13
#تعریف_کړه GL_TEXTURE_ژوروالی_TYPE             0x8C16
#تعریف_کړه GL_TEXTURE_COMPRESSED             0x86A1
#تعریف_کړه GL_SAMPLER_2D_MULTISAMPLE         0x9108
#تعریف_کړه GL_INT_SAMPLER_2D_MULTISAMPLE     0x9109
#تعریف_کړه GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE 0x910A
#تعریف_کړه GL_راس_ATTRIB_BINDING          0x82D4
#تعریف_کړه GL_راس_ATTRIB_RELATIVE_دننه_واټن  0x82D5
#تعریف_کړه GL_راس_BINDING_وېشونکی         0x82D6
#تعریف_کړه GL_راس_BINDING_دننه_واټن          0x82D7
#تعریف_کړه GL_راس_BINDING_STRIDE          0x82D8
#تعریف_کړه GL_راس_BINDING_بفر          0x8F4F
#تعریف_کړه GL_MAX_راس_ATTRIB_RELATIVE_دننه_واټن 0x82D9
#تعریف_کړه GL_MAX_راس_ATTRIB_BINDINGS     0x82DA
#تعریف_کړه GL_MAX_راس_ATTRIB_STRIDE       0x82E5
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISPATCHCOMPUTEPROC) (GLuint عدد_groups_x, GLuint عدد_groups_y, GLuint عدد_groups_z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISPATCHCOMPUTEINDIRECTPROC) (GLintptr غیرمستقیم);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWARRAYSINDIRECTPROC) (GLenum ډېرپېښ, ثابت فراغ *غیرمستقیم);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINDIRECTPROC) (GLenum ډېرپېښ, GLenum type, ثابت فراغ *غیرمستقیم);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERPARAMETERIPROC) (GLenum موخه, GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFRAMEBUFFERPARAMETERIVPROC) (GLenum موخه, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMINTERFACEIVPROC) (GLuint پروګرام, GLenum پروګرام_Interface, GLenum pname, GLint *params);
تعريفنوع GLuint (GL_APIENTRYP PFNGLGETPROGRAMRESOURCEINDEXPROC) (GLuint پروګرام, GLenum پروګرام_Interface, ثابت GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMRESOURCENAMEPROC) (GLuint پروګرام, GLenum پروګرام_Interface, GLuint شاخص, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMRESOURCEIVPROC) (GLuint پروګرام, GLenum پروګرام_Interface, GLuint شاخص, GLsizei prop_شمېر, ثابت GLenum *props, GLsizei شمېر, GLsizei *اوږدتیا, GLint *params);
تعريفنوع GLint (GL_APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONPROC) (GLuint پروګرام, GLenum پروګرام_Interface, ثابت GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUSEPROGRAMSTAGESPROC) (GLuint pipeline, GLbitfield stages, GLuint پروګرام);
تعريفنوع فراغ (GL_APIENTRYP PFNGLACTIVESHADERPROGRAMPROC) (GLuint pipeline, GLuint پروګرام);
تعريفنوع GLuint (GL_APIENTRYP PFNGLCREATESHADERPROGRAMVPROC) (GLenum type, GLsizei شمېر, ثابت GLchar *ثابت*مزي_ګانې);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDPROGRAMPIPELINEPROC) (GLuint pipeline);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEPROGRAMPIPELINESPROC) (GLsizei n, ثابت GLuint *pipelines);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENPROGRAMPIPELINESPROC) (GLsizei n, GLuint *pipelines);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISPROGRAMPIPELINEPROC) (GLuint pipeline);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMPIPELINEIVPROC) (GLuint pipeline, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1IPROC) (GLuint پروګرام, GLint location, GLint v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2IPROC) (GLuint پروګرام, GLint location, GLint v0, GLint v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3IPROC) (GLuint پروګرام, GLint location, GLint v0, GLint v1, GLint v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4IPROC) (GLuint پروګرام, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UIPROC) (GLuint پروګرام, GLint location, GLuint v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UIPROC) (GLuint پروګرام, GLint location, GLuint v0, GLuint v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UIPROC) (GLuint پروګرام, GLint location, GLuint v0, GLuint v1, GLuint v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UIPROC) (GLuint پروګرام, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1FPROC) (GLuint پروګرام, GLint location, GLfloat v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2FPROC) (GLuint پروګرام, GLint location, GLfloat v0, GLfloat v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3FPROC) (GLuint پروګرام, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4FPROC) (GLuint پروګرام, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1IVPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLint *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2IVPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLint *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3IVPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLint *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4IVPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLint *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UIVPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLuint *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UIVPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLuint *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UIVPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLuint *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UIVPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLuint *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1FVPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2FVPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3FVPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4FVPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2FVPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3FVPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4FVPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC) (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVALIDATEPROGRAMPIPELINEPROC) (GLuint pipeline);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMPIPELINEINFOLOGPROC) (GLuint pipeline, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLchar *infoLog);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDIMAGETEXTUREPROC) (GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETBOOLEANI_VPROC) (GLenum موخه, GLuint شاخص, GLboolean *معلومات);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMEMORYBARRIERPROC) (GLbitfield barriers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMEMORYBARRIERBYREGIONPROC) (GLbitfield barriers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE2DMULTISAMPLEPROC) (GLenum موخه, GLsizei samples, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی, GLboolean fixedsamplelocations);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETMULTISAMPLEFVPROC) (GLenum pname, GLuint شاخص, GLfloat *val);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLEMASKIPROC) (GLuint ماسک_شمېره, GLbitfield ماسک);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXLEVELPARAMETERIVPROC) (GLenum موخه, GLint level, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXLEVELPARAMETERFVPROC) (GLenum موخه, GLint level, GLenum pname, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDVERTEXBUFFERPROC) (GLuint bindingindex, GLuint بفر_2, GLintptr دننه_واټن_2, GLsizei stride);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBFORMATPROC) (GLuint attribindex, GLint اندازه, GLenum type, GLboolean normalized, GLuint relativeoffset);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBIFORMATPROC) (GLuint attribindex, GLint اندازه, GLenum type, GLuint relativeoffset);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBBINDINGPROC) (GLuint attribindex, GLuint bindingindex);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXBINDINGDIVISORPROC) (GLuint bindingindex, GLuint وېشونکی);
#إذا GL_GLES_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDispatchCompute (GLuint عدد_groups_x, GLuint عدد_groups_y, GLuint عدد_groups_z);
GL_APICALL فراغ GL_APIENTRY gl_Dispatch_Compute_غیرمستقیم (GLintptr غیرمستقیم);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Arrays_غیرمستقیم (GLenum ډېرپېښ, ثابت فراغ *غیرمستقیم);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Elements_غیرمستقیم (GLenum ډېرپېښ, GLenum type, ثابت فراغ *غیرمستقیم);
GL_APICALL فراغ GL_APIENTRY glFramebufferParameteri (GLenum موخه, GLenum pname, GLint param);
GL_APICALL فراغ GL_APIENTRY glGetFramebufferParameteriv (GLenum موخه, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY gl_Get_پروګرام_Interfaceiv (GLuint پروګرام, GLenum پروګرام_Interface, GLenum pname, GLint *params);
GL_APICALL GLuint GL_APIENTRY gl_Get_پروګرام_Resource_شاخص (GLuint پروګرام, GLenum پروګرام_Interface, ثابت GLchar *name);
GL_APICALL فراغ GL_APIENTRY gl_Get_پروګرام_Resource_Name (GLuint پروګرام, GLenum پروګرام_Interface, GLuint شاخص, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLchar *name);
GL_APICALL فراغ GL_APIENTRY gl_Get_پروګرام_Resourceiv (GLuint پروګرام, GLenum پروګرام_Interface, GLuint شاخص, GLsizei prop_شمېر, ثابت GLenum *props, GLsizei شمېر, GLsizei *اوږدتیا, GLint *params);
GL_APICALL GLint GL_APIENTRY gl_Get_پروګرام_Resource_Location (GLuint پروګرام, GLenum پروګرام_Interface, ثابت GLchar *name);
GL_APICALL فراغ GL_APIENTRY gl_Use_پروګرام_Stages (GLuint pipeline, GLbitfield stages, GLuint پروګرام);
GL_APICALL فراغ GL_APIENTRY gl_فعال_Shader_پروګرام (GLuint pipeline, GLuint پروګرام);
GL_APICALL GLuint GL_APIENTRY glCreateShaderProgramv (GLenum type, GLsizei شمېر, ثابت GLchar *ثابت*مزي_ګانې);
GL_APICALL فراغ GL_APIENTRY gl_Bind_پروګرام_Pipeline (GLuint pipeline);
GL_APICALL فراغ GL_APIENTRY gl_Delete_پروګرام_Pipelines (GLsizei n, ثابت GLuint *pipelines);
GL_APICALL فراغ GL_APIENTRY gl_Gen_پروګرام_Pipelines (GLsizei n, GLuint *pipelines);
GL_APICALL GLboolean GL_APIENTRY gl_Is_پروګرام_Pipeline (GLuint pipeline);
GL_APICALL فراغ GL_APIENTRY gl_Get_پروګرام_Pipelineiv (GLuint pipeline, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform1i (GLuint پروګرام, GLint location, GLint v0);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform2i (GLuint پروګرام, GLint location, GLint v0, GLint v1);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform3i (GLuint پروګرام, GLint location, GLint v0, GLint v1, GLint v2);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform4i (GLuint پروګرام, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform1ui (GLuint پروګرام, GLint location, GLuint v0);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform2ui (GLuint پروګرام, GLint location, GLuint v0, GLuint v1);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform3ui (GLuint پروګرام, GLint location, GLuint v0, GLuint v1, GLuint v2);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform4ui (GLuint پروګرام, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform1f (GLuint پروګرام, GLint location, GLfloat v0);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform2f (GLuint پروګرام, GLint location, GLfloat v0, GLfloat v1);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform3f (GLuint پروګرام, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform4f (GLuint پروګرام, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform1iv (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLint *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform2iv (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLint *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform3iv (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLint *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform4iv (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLint *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform1uiv (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLuint *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform2uiv (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLuint *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform3uiv (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLuint *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform4uiv (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLuint *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform1fv (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform2fv (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform3fv (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_Uniform4fv (GLuint پروګرام, GLint location, GLsizei شمېر, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_یوشان_Matrix2fv (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_یوشان_Matrix3fv (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_یوشان_Matrix4fv (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_یوشان_Matrix2x3fv (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_یوشان_Matrix3x2fv (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_یوشان_Matrix2x4fv (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_یوشان_Matrix4x2fv (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_یوشان_Matrix3x4fv (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_پروګرام_یوشان_Matrix4x3fv (GLuint پروګرام, GLint location, GLsizei شمېر, GLboolean transpose, ثابت GLfloat *ارزښت);
GL_APICALL فراغ GL_APIENTRY gl_Validate_پروګرام_Pipeline (GLuint pipeline);
GL_APICALL فراغ GL_APIENTRY gl_Get_پروګرام_Pipeline_Info_Log (GLuint pipeline, GLsizei buf_اندازه, GLsizei *اوږدتیا, GLchar *infoLog);
GL_APICALL فراغ GL_APIENTRY glBindImageTexture (GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
GL_APICALL فراغ GL_APIENTRY glGetBooleani_v (GLenum موخه, GLuint شاخص, GLboolean *معلومات);
GL_APICALL فراغ GL_APIENTRY gl_حافظه_Barrier (GLbitfield barriers);
GL_APICALL فراغ GL_APIENTRY gl_حافظه_Barrier_By_Region (GLbitfield barriers);
GL_APICALL فراغ GL_APIENTRY glTexStorage2DMultisample (GLenum موخه, GLsizei samples, GLenum internalformat, GLsizei پلنوالی, GLsizei لوړوالی, GLboolean fixedsamplelocations);
GL_APICALL فراغ GL_APIENTRY glGetMultisamplefv (GLenum pname, GLuint شاخص, GLfloat *val);
GL_APICALL فراغ GL_APIENTRY glSampleMaski (GLuint ماسک_شمېره, GLbitfield ماسک);
GL_APICALL فراغ GL_APIENTRY glGetTexLevelParameteriv (GLenum موخه, GLint level, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetTexLevelParameterfv (GLenum موخه, GLint level, GLenum pname, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY gl_Bind_راس_بفر (GLuint bindingindex, GLuint بفر_2, GLintptr دننه_واټن_2, GLsizei stride);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib_Format (GLuint attribindex, GLint اندازه, GLenum type, GLboolean normalized, GLuint relativeoffset);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib_IFormat (GLuint attribindex, GLint اندازه, GLenum type, GLuint relativeoffset);
GL_APICALL فراغ GL_APIENTRY gl_راس_Attrib_Binding (GLuint attribindex, GLuint bindingindex);
GL_APICALL فراغ GL_APIENTRY gl_راس_Binding_وېشونکی (GLuint bindingindex, GLuint وېشونکی);
#د_که_پای
#د_که_پای /* GL_ES_VERSION_3_1 */

#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای
