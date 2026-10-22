#اگر_تعریف_نشده __gles2_gl31_h_
#تعریف_کن __gles2_gl31_h_ 1

#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر

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

#اگر_تعریف_نشده GL_APIENTRYP
#تعریف_کن GL_APIENTRYP GL_APIENTRY*
#پایان_اگر

#اگر_تعریف_نشده GL_GLES_PROTOTYPES
#تعریف_کن GL_GLES_PROTOTYPES 1
#پایان_اگر

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

#اگر_تعریف_نشده GL_ES_نسخه_2_0
#تعریف_کن GL_ES_نسخه_2_0 1
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
تعريفنوع بیعلامت صحيح GLenum;
تعريفنوع بیعلامت صحيح GLuint;
تعريفنوع حرف GLchar;
تعريفنوع khronos_float_t GLfloat;
تعريفنوع khronos_ssize_t GLsizeiptr;
تعريفنوع khronos_intptr_t GLintptr;
تعريفنوع بیعلامت صحيح GLbitfield;
تعريفنوع صحيح GLint;
تعريفنوع بیعلامت حرف GLboolean;
تعريفنوع صحيح GLsizei;
تعريفنوع khronos_uint8_t GLubyte;
#تعریف_کن GL_عمق_میانگیر_بیت               0x00000100
#تعریف_کن GL_STENCIL_میانگیر_بیت             0x00000400
#تعریف_کن GL_COLOR_میانگیر_بیت               0x00004000
#تعریف_کن GL_FALSE                          0
#تعریف_کن GL_TRUE                           1
#تعریف_کن GL_POINTS                         0x0000
#تعریف_کن GL_سطرها                          0x0001
#تعریف_کن GL_سطر_LOOP                      0x0002
#تعریف_کن GL_سطر_STRIP                     0x0003
#تعریف_کن GL_TRIANGLES                      0x0004
#تعریف_کن GL_TRIANGLE_STRIP                 0x0005
#تعریف_کن GL_TRIANGLE_FAN                   0x0006
#تعریف_کن GL_ZERO                           0
#تعریف_کن GL_ONE                            1
#تعریف_کن GL_SRC_COLOR                      0x0300
#تعریف_کن GL_ONE_MINUS_SRC_COLOR            0x0301
#تعریف_کن GL_SRC_ALPHA                      0x0302
#تعریف_کن GL_ONE_MINUS_SRC_ALPHA            0x0303
#تعریف_کن GL_DST_ALPHA                      0x0304
#تعریف_کن GL_ONE_MINUS_DST_ALPHA            0x0305
#تعریف_کن GL_DST_COLOR                      0x0306
#تعریف_کن GL_ONE_MINUS_DST_COLOR            0x0307
#تعریف_کن GL_SRC_ALPHA_SATURATE             0x0308
#تعریف_کن GL_FUNC_جمع_کن                       0x8006
#تعریف_کن GL_BLEND_EQUATION                 0x8009
#تعریف_کن GL_BLEND_EQUATION_RGB             0x8009
#تعریف_کن GL_BLEND_EQUATION_ALPHA           0x883D
#تعریف_کن GL_FUNC_تفریق                  0x800A
#تعریف_کن GL_FUNC_معکوس_تفریق          0x800B
#تعریف_کن GL_BLEND_DST_RGB                  0x80C8
#تعریف_کن GL_BLEND_SRC_RGB                  0x80C9
#تعریف_کن GL_BLEND_DST_ALPHA                0x80CA
#تعریف_کن GL_BLEND_SRC_ALPHA                0x80CB
#تعریف_کن GL_CONSTANT_COLOR                 0x8001
#تعریف_کن GL_ONE_MINUS_CONSTANT_COLOR       0x8002
#تعریف_کن GL_CONSTANT_ALPHA                 0x8003
#تعریف_کن GL_ONE_MINUS_CONSTANT_ALPHA       0x8004
#تعریف_کن GL_BLEND_COLOR                    0x8005
#تعریف_کن GL_ARRAY_میانگیر                   0x8892
#تعریف_کن GL_ELEMENT_ARRAY_میانگیر           0x8893
#تعریف_کن GL_ARRAY_میانگیر_BINDING           0x8894
#تعریف_کن GL_ELEMENT_ARRAY_میانگیر_BINDING   0x8895
#تعریف_کن GL_جریان_DRAW                    0x88E0
#تعریف_کن GL_STATIC_DRAW                    0x88E4
#تعریف_کن GL_DYNAMIC_DRAW                   0x88E8
#تعریف_کن GL_میانگیر_اندازه                    0x8764
#تعریف_کن GL_میانگیر_USAGE                   0x8765
#تعریف_کن GL_CURRENT_رأس_ATTRIB          0x8626
#تعریف_کن GL_FRONT                          0x0404
#تعریف_کن GL_پشت                           0x0405
#تعریف_کن GL_FRONT_AND_پشت                 0x0408
#تعریف_کن GL_TEXTURE_2D                     0x0DE1
#تعریف_کن GL_CULL_FACE                      0x0B44
#تعریف_کن GL_BLEND                          0x0BE2
#تعریف_کن GL_DITHER                         0x0BD0
#تعریف_کن GL_STENCIL_TEST                   0x0B90
#تعریف_کن GL_عمق_TEST                     0x0B71
#تعریف_کن GL_SCISSOR_TEST                   0x0C11
#تعریف_کن GL_POLYGON_جابه_جایی_FILL            0x8037
#تعریف_کن GL_SAMPLE_ALPHA_مقصد_COVERAGE       0x809E
#تعریف_کن GL_SAMPLE_COVERAGE                0x80A0
#تعریف_کن GL_NO_ERROR                       0
#تعریف_کن GL_INVALID_ENUM                   0x0500
#تعریف_کن GL_INVALID_مقدار                  0x0501
#تعریف_کن GL_INVALID_OPERATION              0x0502
#تعریف_کن GL_بیرون_از_حافظه                  0x0505
#تعریف_کن GL_CW                             0x0900
#تعریف_کن GL_CCW                            0x0901
#تعریف_کن GL_سطر_عرض                     0x0B21
#تعریف_کن GL_ALIASED_نقطه_اندازه_RANGE       0x846D
#تعریف_کن GL_ALIASED_سطر_عرض_RANGE       0x846E
#تعریف_کن GL_CULL_FACE_نما                 0x0B45
#تعریف_کن GL_FRONT_FACE                     0x0B46
#تعریف_کن GL_عمق_RANGE                    0x0B70
#تعریف_کن GL_عمق_WRITEMASK                0x0B72
#تعریف_کن GL_عمق_CLEAR_مقدار              0x0B73
#تعریف_کن GL_عمق_FUNC                     0x0B74
#تعریف_کن GL_STENCIL_CLEAR_مقدار            0x0B91
#تعریف_کن GL_STENCIL_FUNC                   0x0B92
#تعریف_کن GL_STENCIL_FAIL                   0x0B94
#تعریف_کن GL_STENCIL_PASS_عمق_FAIL        0x0B95
#تعریف_کن GL_STENCIL_PASS_عمق_PASS        0x0B96
#تعریف_کن GL_STENCIL_REF                    0x0B97
#تعریف_کن GL_STENCIL_مقدار_ماسک             0x0B93
#تعریف_کن GL_STENCIL_WRITEMASK              0x0B98
#تعریف_کن GL_STENCIL_پشت_FUNC              0x8800
#تعریف_کن GL_STENCIL_پشت_FAIL              0x8801
#تعریف_کن GL_STENCIL_پشت_PASS_عمق_FAIL   0x8802
#تعریف_کن GL_STENCIL_پشت_PASS_عمق_PASS   0x8803
#تعریف_کن GL_STENCIL_پشت_REF               0x8CA3
#تعریف_کن GL_STENCIL_پشت_مقدار_ماسک        0x8CA4
#تعریف_کن GL_STENCIL_پشت_WRITEMASK         0x8CA5
#تعریف_کن GL_VIEWPORT                       0x0BA2
#تعریف_کن GL_SCISSOR_BOX                    0x0C10
#تعریف_کن GL_COLOR_CLEAR_مقدار              0x0C22
#تعریف_کن GL_COLOR_WRITEMASK                0x0C23
#تعریف_کن GL_UNPACK_ALIGNMENT               0x0CF5
#تعریف_کن GL_PACK_ALIGNMENT                 0x0D05
#تعریف_کن GL_MAX_TEXTURE_اندازه               0x0D33
#تعریف_کن GL_MAX_VIEWPORT_DIMS              0x0D3A
#تعریف_کن GL_SUBPIXEL_بیتها                  0x0D50
#تعریف_کن GL_RED_بیتها                       0x0D52
#تعریف_کن GL_GREEN_بیتها                     0x0D53
#تعریف_کن GL_BLUE_بیتها                      0x0D54
#تعریف_کن GL_ALPHA_بیتها                     0x0D55
#تعریف_کن GL_عمق_بیتها                     0x0D56
#تعریف_کن GL_STENCIL_بیتها                   0x0D57
#تعریف_کن GL_POLYGON_جابه_جایی_UNITS           0x2A00
#تعریف_کن GL_POLYGON_جابه_جایی_ضریب          0x8038
#تعریف_کن GL_TEXTURE_BINDING_2D             0x8069
#تعریف_کن GL_SAMPLE_BUFFERS                 0x80A8
#تعریف_کن GL_SAMPLES                        0x80A9
#تعریف_کن GL_SAMPLE_COVERAGE_مقدار          0x80AA
#تعریف_کن GL_SAMPLE_COVERAGE_INVERT         0x80AB
#تعریف_کن GL_رقم_COMPRESSED_TEXTURE_FORMATS 0x86A2
#تعریف_کن GL_COMPRESSED_TEXTURE_FORMATS     0x86A3
#تعریف_کن GL_DONT_CARE                      0x1100
#تعریف_کن GL_FASTEST                        0x1101
#تعریف_کن GL_NICEST                         0x1102
#تعریف_کن GL_GENERATE_MIPMAP_HINT           0x8192
#تعریف_کن GL_BYTE                           0x1400
#تعریف_کن GL_UNSIGNED_BYTE                  0x1401
#تعریف_کن GL_SHORT                          0x1402
#تعریف_کن GL_UNSIGNED_SHORT                 0x1403
#تعریف_کن GL_INT                            0x1404
#تعریف_کن GL_UNSIGNED_INT                   0x1405
#تعریف_کن GL_FLOAT                          0x1406
#تعریف_کن GL_FIXED                          0x140C
#تعریف_کن GL_عمق_COMPONENT                0x1902
#تعریف_کن GL_ALPHA                          0x1906
#تعریف_کن GL_RGB                            0x1907
#تعریف_کن GL_RGBA                           0x1908
#تعریف_کن GL_LUMINANCE                      0x1909
#تعریف_کن GL_LUMINANCE_ALPHA                0x190A
#تعریف_کن GL_UNSIGNED_SHORT_4_4_4_4         0x8033
#تعریف_کن GL_UNSIGNED_SHORT_5_5_5_1         0x8034
#تعریف_کن GL_UNSIGNED_SHORT_5_6_5           0x8363
#تعریف_کن GL_FRAGMENT_SHADER                0x8B30
#تعریف_کن GL_رأس_SHADER                  0x8B31
#تعریف_کن GL_MAX_رأس_ATTRIBS             0x8869
#تعریف_کن GL_MAX_رأس_یکنواخت_VECTORS     0x8DFB
#تعریف_کن GL_MAX_VARYING_VECTORS            0x8DFC
#تعریف_کن GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 0x8B4D
#تعریف_کن GL_MAX_رأس_TEXTURE_IMAGE_UNITS 0x8B4C
#تعریف_کن GL_MAX_TEXTURE_IMAGE_UNITS        0x8872
#تعریف_کن GL_MAX_FRAGMENT_یکنواخت_VECTORS   0x8DFD
#تعریف_کن GL_SHADER_TYPE                    0x8B4F
#تعریف_کن GL_DELETE_وضعیت                  0x8B80
#تعریف_کن GL_LINK_وضعیت                    0x8B82
#تعریف_کن GL_VALIDATE_وضعیت                0x8B83
#تعریف_کن GL_ATTACHED_SHADERS               0x8B85
#تعریف_کن GL_فعال_UNIFORMS                0x8B86
#تعریف_کن GL_فعال_یکنواخت_MAX_درازی      0x8B87
#تعریف_کن GL_فعال_صفات              0x8B89
#تعریف_کن GL_فعال_ATTRIBUTE_MAX_درازی    0x8B8A
#تعریف_کن GL_SHADING_LANGUAGE_نسخه       0x8B8C
#تعریف_کن GL_CURRENT_برنامه                0x8B8D
#تعریف_کن GL_NEVER                          0x0200
#تعریف_کن GL_LESS                           0x0201
#تعریف_کن GL_EQUAL                          0x0202
#تعریف_کن GL_LEQUAL                         0x0203
#تعریف_کن GL_GREATER                        0x0204
#تعریف_کن GL_NOTEQUAL                       0x0205
#تعریف_کن GL_GEQUAL                         0x0206
#تعریف_کن GL_ALWAYS                         0x0207
#تعریف_کن GL_KEEP                           0x1E00
#تعریف_کن GL_REPLACE                        0x1E01
#تعریف_کن GL_INCR                           0x1E02
#تعریف_کن GL_DECR                           0x1E03
#تعریف_کن GL_INVERT                         0x150A
#تعریف_کن GL_INCR_WRAP                      0x8507
#تعریف_کن GL_DECR_WRAP                      0x8508
#تعریف_کن GL_VENDOR                         0x1F00
#تعریف_کن GL_RENDERER                       0x1F01
#تعریف_کن GL_نسخه                        0x1F02
#تعریف_کن GL_EXTENSIONS                     0x1F03
#تعریف_کن GL_نزدیکترین                        0x2600
#تعریف_کن GL_خطی                         0x2601
#تعریف_کن GL_نزدیکترین_MIPMAP_نزدیکترین         0x2700
#تعریف_کن GL_خطی_MIPMAP_نزدیکترین          0x2701
#تعریف_کن GL_نزدیکترین_MIPMAP_خطی          0x2702
#تعریف_کن GL_خطی_MIPMAP_خطی           0x2703
#تعریف_کن GL_TEXTURE_MAG_FILTER             0x2800
#تعریف_کن GL_TEXTURE_MIN_FILTER             0x2801
#تعریف_کن GL_TEXTURE_WRAP_S                 0x2802
#تعریف_کن GL_TEXTURE_WRAP_T                 0x2803
#تعریف_کن GL_TEXTURE                        0x1702
#تعریف_کن GL_TEXTURE_CUBE_MAP               0x8513
#تعریف_کن GL_TEXTURE_BINDING_CUBE_MAP       0x8514
#تعریف_کن GL_TEXTURE_CUBE_MAP_مثبت_X    0x8515
#تعریف_کن GL_TEXTURE_CUBE_MAP_NEGATIVE_X    0x8516
#تعریف_کن GL_TEXTURE_CUBE_MAP_مثبت_Y    0x8517
#تعریف_کن GL_TEXTURE_CUBE_MAP_NEGATIVE_Y    0x8518
#تعریف_کن GL_TEXTURE_CUBE_MAP_مثبت_Z    0x8519
#تعریف_کن GL_TEXTURE_CUBE_MAP_NEGATIVE_Z    0x851A
#تعریف_کن GL_MAX_CUBE_MAP_TEXTURE_اندازه      0x851C
#تعریف_کن GL_TEXTURE0                       0x84C0
#تعریف_کن GL_TEXTURE1                       0x84C1
#تعریف_کن GL_TEXTURE2                       0x84C2
#تعریف_کن GL_TEXTURE3                       0x84C3
#تعریف_کن GL_TEXTURE4                       0x84C4
#تعریف_کن GL_TEXTURE5                       0x84C5
#تعریف_کن GL_TEXTURE6                       0x84C6
#تعریف_کن GL_TEXTURE7                       0x84C7
#تعریف_کن GL_TEXTURE8                       0x84C8
#تعریف_کن GL_TEXTURE9                       0x84C9
#تعریف_کن GL_TEXTURE10                      0x84CA
#تعریف_کن GL_TEXTURE11                      0x84CB
#تعریف_کن GL_TEXTURE12                      0x84CC
#تعریف_کن GL_TEXTURE13                      0x84CD
#تعریف_کن GL_TEXTURE14                      0x84CE
#تعریف_کن GL_TEXTURE15                      0x84CF
#تعریف_کن GL_TEXTURE16                      0x84D0
#تعریف_کن GL_TEXTURE17                      0x84D1
#تعریف_کن GL_TEXTURE18                      0x84D2
#تعریف_کن GL_TEXTURE19                      0x84D3
#تعریف_کن GL_TEXTURE20                      0x84D4
#تعریف_کن GL_TEXTURE21                      0x84D5
#تعریف_کن GL_TEXTURE22                      0x84D6
#تعریف_کن GL_TEXTURE23                      0x84D7
#تعریف_کن GL_TEXTURE24                      0x84D8
#تعریف_کن GL_TEXTURE25                      0x84D9
#تعریف_کن GL_TEXTURE26                      0x84DA
#تعریف_کن GL_TEXTURE27                      0x84DB
#تعریف_کن GL_TEXTURE28                      0x84DC
#تعریف_کن GL_TEXTURE29                      0x84DD
#تعریف_کن GL_TEXTURE30                      0x84DE
#تعریف_کن GL_TEXTURE31                      0x84DF
#تعریف_کن GL_فعال_TEXTURE                 0x84E0
#تعریف_کن GL_REPEAT                         0x2901
#تعریف_کن GL_CLAMP_مقصد_یال                  0x812F
#تعریف_کن GL_MIRRORED_REPEAT                0x8370
#تعریف_کن GL_FLOAT_VEC2                     0x8B50
#تعریف_کن GL_FLOAT_VEC3                     0x8B51
#تعریف_کن GL_FLOAT_VEC4                     0x8B52
#تعریف_کن GL_INT_VEC2                       0x8B53
#تعریف_کن GL_INT_VEC3                       0x8B54
#تعریف_کن GL_INT_VEC4                       0x8B55
#تعریف_کن GL_BOOL                           0x8B56
#تعریف_کن GL_BOOL_VEC2                      0x8B57
#تعریف_کن GL_BOOL_VEC3                      0x8B58
#تعریف_کن GL_BOOL_VEC4                      0x8B59
#تعریف_کن GL_FLOAT_MAT2                     0x8B5A
#تعریف_کن GL_FLOAT_MAT3                     0x8B5B
#تعریف_کن GL_FLOAT_MAT4                     0x8B5C
#تعریف_کن GL_SAMPLER_2D                     0x8B5E
#تعریف_کن GL_SAMPLER_CUBE                   0x8B60
#تعریف_کن GL_رأس_ATTRIB_ARRAY_ENABLED    0x8622
#تعریف_کن GL_رأس_ATTRIB_ARRAY_اندازه       0x8623
#تعریف_کن GL_رأس_ATTRIB_ARRAY_STRIDE     0x8624
#تعریف_کن GL_رأس_ATTRIB_ARRAY_TYPE       0x8625
#تعریف_کن GL_رأس_ATTRIB_ARRAY_NORMALIZED 0x886A
#تعریف_کن GL_رأس_ATTRIB_ARRAY_اشاره_گر    0x8645
#تعریف_کن GL_رأس_ATTRIB_ARRAY_میانگیر_BINDING 0x889F
#تعریف_کن GL_IMPLEMENTATION_COLOR_READ_TYPE 0x8B9A
#تعریف_کن GL_IMPLEMENTATION_COLOR_READ_FORMAT 0x8B9B
#تعریف_کن GL_COMPILE_وضعیت                 0x8B81
#تعریف_کن GL_INFO_LOG_درازی                0x8B84
#تعریف_کن GL_SHADER_منبع_درازی           0x8B88
#تعریف_کن GL_SHADER_COMPILER                0x8DFA
#تعریف_کن GL_SHADER_دودویی_FORMATS          0x8DF8
#تعریف_کن GL_رقم_SHADER_دودویی_FORMATS      0x8DF9
#تعریف_کن GL_کم_FLOAT                      0x8DF0
#تعریف_کن GL_MEDIUM_FLOAT                   0x8DF1
#تعریف_کن GL_بالا_FLOAT                     0x8DF2
#تعریف_کن GL_کم_INT                        0x8DF3
#تعریف_کن GL_MEDIUM_INT                     0x8DF4
#تعریف_کن GL_بالا_INT                       0x8DF5
#تعریف_کن GL_FRAMEBUFFER                    0x8D40
#تعریف_کن GL_RENDERBUFFER                   0x8D41
#تعریف_کن GL_RGBA4                          0x8056
#تعریف_کن GL_RGB5_A1                        0x8057
#تعریف_کن GL_RGB565                         0x8D62
#تعریف_کن GL_عمق_COMPONENT16              0x81A5
#تعریف_کن GL_STENCIL_INDEX8                 0x8D48
#تعریف_کن GL_RENDERBUFFER_عرض             0x8D42
#تعریف_کن GL_RENDERBUFFER_ارتفاع            0x8D43
#تعریف_کن GL_RENDERBUFFER_داخلی_FORMAT   0x8D44
#تعریف_کن GL_RENDERBUFFER_RED_اندازه          0x8D50
#تعریف_کن GL_RENDERBUFFER_GREEN_اندازه        0x8D51
#تعریف_کن GL_RENDERBUFFER_BLUE_اندازه         0x8D52
#تعریف_کن GL_RENDERBUFFER_ALPHA_اندازه        0x8D53
#تعریف_کن GL_RENDERBUFFER_عمق_اندازه        0x8D54
#تعریف_کن GL_RENDERBUFFER_STENCIL_اندازه      0x8D55
#تعریف_کن GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE 0x8CD0
#تعریف_کن GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME 0x8CD1
#تعریف_کن GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL 0x8CD2
#تعریف_کن GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE 0x8CD3
#تعریف_کن GL_COLOR_ATTACHMENT0              0x8CE0
#تعریف_کن GL_عمق_ATTACHMENT               0x8D00
#تعریف_کن GL_STENCIL_ATTACHMENT             0x8D20
#تعریف_کن GL_NONE                           0
#تعریف_کن GL_FRAMEBUFFER_COMPLETE           0x8CD5
#تعریف_کن GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT 0x8CD6
#تعریف_کن GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 0x8CD7
#تعریف_کن GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS 0x8CD9
#تعریف_کن GL_FRAMEBUFFER_UNSUPPORTED        0x8CDD
#تعریف_کن GL_FRAMEBUFFER_BINDING            0x8CA6
#تعریف_کن GL_RENDERBUFFER_BINDING           0x8CA7
#تعریف_کن GL_MAX_RENDERBUFFER_اندازه          0x84E8
#تعریف_کن GL_INVALID_FRAMEBUFFER_OPERATION  0x0506
تعريفنوع فراغ (GL_APIENTRYP PFNGLACTIVETEXTUREPROC) (GLenum texture);
تعريفنوع فراغ (GL_APIENTRYP PFNGLATTACHSHADERPROC) (GLuint برنامه, GLuint shader);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDATTRIBLOCATIONPROC) (GLuint برنامه, GLuint شاخص, ثابت GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDBUFFERPROC) (GLenum هدف, GLuint میانگیر_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDFRAMEBUFFERPROC) (GLenum هدف, GLuint framebuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDRENDERBUFFERPROC) (GLenum هدف, GLuint renderbuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDTEXTUREPROC) (GLenum هدف, GLuint texture);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONPROC) (GLenum نما);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEPROC) (GLenum نما_RGB, GLenum نما_Alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDFUNCPROC) (GLenum sfactor, GLenum dfactor);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEPROC) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBUFFERDATAPROC) (GLenum هدف, GLsizeiptr اندازه, ثابت فراغ *داده, GLenum usage);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBUFFERSUBDATAPROC) (GLenum هدف, GLintptr جابه_جایی_2, GLsizeiptr اندازه, ثابت فراغ *داده);
تعريفنوع GLenum (GL_APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSPROC) (GLenum هدف);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARPROC) (GLbitfield ماسک);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARDEPTHFPROC) (GLfloat d);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARSTENCILPROC) (GLint s);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOLORMASKPROC) (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOMPILESHADERPROC) (GLuint shader);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOMPRESSEDTEXIMAGE2DPROC) (GLenum هدف, GLint level, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع, GLint border, GLsizei image_اندازه, ثابت فراغ *داده);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLsizei عرض, GLsizei ارتفاع, GLenum format, GLsizei image_اندازه, ثابت فراغ *داده);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYTEXIMAGE2DPROC) (GLenum هدف, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei عرض, GLsizei ارتفاع, GLint border);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYTEXSUBIMAGE2DPROC) (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei عرض, GLsizei ارتفاع);
تعريفنوع GLuint (GL_APIENTRYP PFNGLCREATEPROGRAMPROC) (فراغ);
تعريفنوع GLuint (GL_APIENTRYP PFNGLCREATESHADERPROC) (GLenum type);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCULLFACEPROC) (GLenum نما);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEBUFFERSPROC) (GLsizei n, ثابت GLuint *buffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEFRAMEBUFFERSPROC) (GLsizei n, ثابت GLuint *framebuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEPROGRAMPROC) (GLuint برنامه);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETERENDERBUFFERSPROC) (GLsizei n, ثابت GLuint *renderbuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETESHADERPROC) (GLuint shader);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETETEXTURESPROC) (GLsizei n, ثابت GLuint *textures);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHFUNCPROC) (GLenum func);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHMASKPROC) (GLboolean flag);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDEPTHRANGEFPROC) (GLfloat n, GLfloat f);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDETACHSHADERPROC) (GLuint برنامه, GLuint shader);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISABLEPROC) (GLenum cap);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint شاخص);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWARRAYSPROC) (GLenum نما, GLint اولی, GLsizei شمار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSPROC) (GLenum نما, GLsizei شمار, GLenum type, ثابت فراغ *indices);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENABLEPROC) (GLenum cap);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint شاخص);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFINISHPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFLUSHPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFERPROC) (GLenum هدف, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DPROC) (GLenum هدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRONTFACEPROC) (GLenum نما);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENBUFFERSPROC) (GLsizei n, GLuint *buffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENERATEMIPMAPPROC) (GLenum هدف);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENFRAMEBUFFERSPROC) (GLsizei n, GLuint *framebuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENRENDERBUFFERSPROC) (GLsizei n, GLuint *renderbuffers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENTEXTURESPROC) (GLsizei n, GLuint *textures);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETACTIVEATTRIBPROC) (GLuint برنامه, GLuint شاخص, GLsizei buf_اندازه, GLsizei *درازی, GLint *اندازه, GLenum *type, GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETACTIVEUNIFORMPROC) (GLuint برنامه, GLuint شاخص, GLsizei buf_اندازه, GLsizei *درازی, GLint *اندازه, GLenum *type, GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETATTACHEDSHADERSPROC) (GLuint برنامه, GLsizei max_شمار, GLsizei *شمار, GLuint *shaders);
تعريفنوع GLint (GL_APIENTRYP PFNGLGETATTRIBLOCATIONPROC) (GLuint برنامه, ثابت GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETBOOLEANVPROC) (GLenum pname, GLboolean *داده);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETBUFFERPARAMETERIVPROC) (GLenum هدف, GLenum pname, GLint *params);
تعريفنوع GLenum (GL_APIENTRYP PFNGLGETERRORPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFLOATVPROC) (GLenum pname, GLfloat *داده);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) (GLenum هدف, GLenum attachment, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTEGERVPROC) (GLenum pname, GLint *داده);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMIVPROC) (GLuint برنامه, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMINFOLOGPROC) (GLuint برنامه, GLsizei buf_اندازه, GLsizei *درازی, GLchar *infoLog);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVPROC) (GLenum هدف, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei buf_اندازه, GLsizei *درازی, GLchar *infoLog);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSHADERPRECISIONFORMATPROC) (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSHADERSOURCEPROC) (GLuint shader, GLsizei buf_اندازه, GLsizei *درازی, GLchar *منبع);
تعريفنوع ثابت GLubyte *(GL_APIENTRYP PFNGLGETSTRINGPROC) (GLenum name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXPARAMETERFVPROC) (GLenum هدف, GLenum pname, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXPARAMETERIVPROC) (GLenum هدف, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETUNIFORMFVPROC) (GLuint برنامه, GLint location, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETUNIFORMIVPROC) (GLuint برنامه, GLint location, GLint *params);
تعريفنوع GLint (GL_APIENTRYP PFNGLGETUNIFORMLOCATIONPROC) (GLuint برنامه, ثابت GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETVERTEXATTRIBFVPROC) (GLuint شاخص, GLenum pname, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETVERTEXATTRIBIVPROC) (GLuint شاخص, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETVERTEXATTRIBPOINTERVPROC) (GLuint شاخص, GLenum pname, فراغ **اشاره_گر_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLHINTPROC) (GLenum هدف, GLenum نما);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISBUFFERPROC) (GLuint میانگیر_2);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISENABLEDPROC) (GLenum cap);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISFRAMEBUFFERPROC) (GLuint framebuffer);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISPROGRAMPROC) (GLuint برنامه);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISRENDERBUFFERPROC) (GLuint renderbuffer);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISSHADERPROC) (GLuint shader);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISTEXTUREPROC) (GLuint texture);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLINEWIDTHPROC) (GLfloat عرض);
تعريفنوع فراغ (GL_APIENTRYP PFNGLLINKPROGRAMPROC) (GLuint برنامه);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPIXELSTOREIPROC) (GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPOLYGONOFFSETPROC) (GLfloat ضریب, GLfloat units);
تعريفنوع فراغ (GL_APIENTRYP PFNGLREADPIXELSPROC) (GLint x, GLint y, GLsizei عرض, GLsizei ارتفاع, GLenum format, GLenum type, فراغ *pixels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRELEASESHADERCOMPILERPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEPROC) (GLenum هدف, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLECOVERAGEPROC) (GLfloat مقدار, GLboolean invert);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSCISSORPROC) (GLint x, GLint y, GLsizei عرض, GLsizei ارتفاع);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADERBINARYPROC) (GLsizei شمار, ثابت GLuint *shaders, GLenum دودویی_Format, ثابت فراغ *دودویی, GLsizei درازی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei شمار, ثابت GLchar *ثابت*string, ثابت GLint *درازی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILFUNCPROC) (GLenum func, GLint ref, GLuint ماسک);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILFUNCSEPARATEPROC) (GLenum face, GLenum func, GLint ref, GLuint ماسک);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILMASKPROC) (GLuint ماسک);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILMASKSEPARATEPROC) (GLenum face, GLuint ماسک);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILOPPROC) (GLenum fail, GLenum zfail, GLenum zpass);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSTENCILOPSEPARATEPROC) (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXIMAGE2DPROC) (GLenum هدف, GLint level, GLint internalformat, GLsizei عرض, GLsizei ارتفاع, GLint border, GLenum format, GLenum type, ثابت فراغ *pixels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERFPROC) (GLenum هدف, GLenum pname, GLfloat param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERFVPROC) (GLenum هدف, GLenum pname, ثابت GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERIPROC) (GLenum هدف, GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXPARAMETERIVPROC) (GLenum هدف, GLenum pname, ثابت GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSUBIMAGE2DPROC) (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLsizei عرض, GLsizei ارتفاع, GLenum format, GLenum type, ثابت فراغ *pixels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1FPROC) (GLint location, GLfloat v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1FVPROC) (GLint location, GLsizei شمار, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1IPROC) (GLint location, GLint v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1IVPROC) (GLint location, GLsizei شمار, ثابت GLint *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2FPROC) (GLint location, GLfloat v0, GLfloat v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2FVPROC) (GLint location, GLsizei شمار, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2IPROC) (GLint location, GLint v0, GLint v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2IVPROC) (GLint location, GLsizei شمار, ثابت GLint *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3FVPROC) (GLint location, GLsizei شمار, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3IPROC) (GLint location, GLint v0, GLint v1, GLint v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3IVPROC) (GLint location, GLsizei شمار, ثابت GLint *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4FVPROC) (GLint location, GLsizei شمار, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4IPROC) (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4IVPROC) (GLint location, GLsizei شمار, ثابت GLint *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX2FVPROC) (GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX3FVPROC) (GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUSEPROGRAMPROC) (GLuint برنامه);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVALIDATEPROGRAMPROC) (GLuint برنامه);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB1FPROC) (GLuint شاخص, GLfloat x);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB1FVPROC) (GLuint شاخص, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB2FPROC) (GLuint شاخص, GLfloat x, GLfloat y);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB2FVPROC) (GLuint شاخص, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB3FPROC) (GLuint شاخص, GLfloat x, GLfloat y, GLfloat z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB3FVPROC) (GLuint شاخص, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB4FPROC) (GLuint شاخص, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIB4FVPROC) (GLuint شاخص, ثابت GLfloat *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC) (GLuint شاخص, GLint اندازه, GLenum type, GLboolean normalized, GLsizei stride, ثابت فراغ *اشاره_گر_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVIEWPORTPROC) (GLint x, GLint y, GLsizei عرض, GLsizei ارتفاع);
#إذا GL_GLES_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_فعال_Texture (GLenum texture);
GL_APICALL فراغ GL_APIENTRY glAttachShader (GLuint برنامه, GLuint shader);
GL_APICALL فراغ GL_APIENTRY glBindAttribLocation (GLuint برنامه, GLuint شاخص, ثابت GLchar *name);
GL_APICALL فراغ GL_APIENTRY gl_Bind_میانگیر (GLenum هدف, GLuint میانگیر_2);
GL_APICALL فراغ GL_APIENTRY glBindFramebuffer (GLenum هدف, GLuint framebuffer);
GL_APICALL فراغ GL_APIENTRY glBindRenderbuffer (GLenum هدف, GLuint renderbuffer);
GL_APICALL فراغ GL_APIENTRY glBindTexture (GLenum هدف, GLuint texture);
GL_APICALL فراغ GL_APIENTRY glBlendColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_APICALL فراغ GL_APIENTRY glBlendEquation (GLenum نما);
GL_APICALL فراغ GL_APIENTRY glBlendEquationSeparate (GLenum نما_RGB, GLenum نما_Alpha);
GL_APICALL فراغ GL_APIENTRY glBlendFunc (GLenum sfactor, GLenum dfactor);
GL_APICALL فراغ GL_APIENTRY glBlendFuncSeparate (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
GL_APICALL فراغ GL_APIENTRY gl_میانگیر_داده (GLenum هدف, GLsizeiptr اندازه, ثابت فراغ *داده, GLenum usage);
GL_APICALL فراغ GL_APIENTRY gl_میانگیر_Sub_داده (GLenum هدف, GLintptr جابه_جایی_2, GLsizeiptr اندازه, ثابت فراغ *داده);
GL_APICALL GLenum GL_APIENTRY gl_Check_Framebuffer_وضعیت (GLenum هدف);
GL_APICALL فراغ GL_APIENTRY glClear (GLbitfield ماسک);
GL_APICALL فراغ GL_APIENTRY glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_APICALL فراغ GL_APIENTRY glClearDepthf (GLfloat d);
GL_APICALL فراغ GL_APIENTRY glClearStencil (GLint s);
GL_APICALL فراغ GL_APIENTRY gl_Color_ماسک (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
GL_APICALL فراغ GL_APIENTRY glCompileShader (GLuint shader);
GL_APICALL فراغ GL_APIENTRY glCompressedTexImage2D (GLenum هدف, GLint level, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع, GLint border, GLsizei image_اندازه, ثابت فراغ *داده);
GL_APICALL فراغ GL_APIENTRY glCompressedTexSubImage2D (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLsizei عرض, GLsizei ارتفاع, GLenum format, GLsizei image_اندازه, ثابت فراغ *داده);
GL_APICALL فراغ GL_APIENTRY glCopyTexImage2D (GLenum هدف, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei عرض, GLsizei ارتفاع, GLint border);
GL_APICALL فراغ GL_APIENTRY glCopyTexSubImage2D (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei عرض, GLsizei ارتفاع);
GL_APICALL GLuint GL_APIENTRY gl_Create_برنامه (فراغ);
GL_APICALL GLuint GL_APIENTRY glCreateShader (GLenum type);
GL_APICALL فراغ GL_APIENTRY glCullFace (GLenum نما);
GL_APICALL فراغ GL_APIENTRY glDeleteBuffers (GLsizei n, ثابت GLuint *buffers);
GL_APICALL فراغ GL_APIENTRY glDeleteFramebuffers (GLsizei n, ثابت GLuint *framebuffers);
GL_APICALL فراغ GL_APIENTRY gl_Delete_برنامه (GLuint برنامه);
GL_APICALL فراغ GL_APIENTRY glDeleteRenderbuffers (GLsizei n, ثابت GLuint *renderbuffers);
GL_APICALL فراغ GL_APIENTRY glDeleteShader (GLuint shader);
GL_APICALL فراغ GL_APIENTRY glDeleteTextures (GLsizei n, ثابت GLuint *textures);
GL_APICALL فراغ GL_APIENTRY gl_عمق_Func (GLenum func);
GL_APICALL فراغ GL_APIENTRY gl_عمق_ماسک (GLboolean flag);
GL_APICALL فراغ GL_APIENTRY gl_عمق_Rangef (GLfloat n, GLfloat f);
GL_APICALL فراغ GL_APIENTRY glDetachShader (GLuint برنامه, GLuint shader);
GL_APICALL فراغ GL_APIENTRY glDisable (GLenum cap);
GL_APICALL فراغ GL_APIENTRY gl_Disable_رأس_Attrib_Array (GLuint شاخص);
GL_APICALL فراغ GL_APIENTRY glDrawArrays (GLenum نما, GLint اولی, GLsizei شمار);
GL_APICALL فراغ GL_APIENTRY glDrawElements (GLenum نما, GLsizei شمار, GLenum type, ثابت فراغ *indices);
GL_APICALL فراغ GL_APIENTRY glEnable (GLenum cap);
GL_APICALL فراغ GL_APIENTRY gl_Enable_رأس_Attrib_Array (GLuint شاخص);
GL_APICALL فراغ GL_APIENTRY gl_پایان (فراغ);
GL_APICALL فراغ GL_APIENTRY glFlush (فراغ);
GL_APICALL فراغ GL_APIENTRY glFramebufferRenderbuffer (GLenum هدف, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
GL_APICALL فراغ GL_APIENTRY glFramebufferTexture2D (GLenum هدف, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GL_APICALL فراغ GL_APIENTRY glFrontFace (GLenum نما);
GL_APICALL فراغ GL_APIENTRY glGenBuffers (GLsizei n, GLuint *buffers);
GL_APICALL فراغ GL_APIENTRY glGenerateMipmap (GLenum هدف);
GL_APICALL فراغ GL_APIENTRY glGenFramebuffers (GLsizei n, GLuint *framebuffers);
GL_APICALL فراغ GL_APIENTRY glGenRenderbuffers (GLsizei n, GLuint *renderbuffers);
GL_APICALL فراغ GL_APIENTRY glGenTextures (GLsizei n, GLuint *textures);
GL_APICALL فراغ GL_APIENTRY gl_Get_فعال_Attrib (GLuint برنامه, GLuint شاخص, GLsizei buf_اندازه, GLsizei *درازی, GLint *اندازه, GLenum *type, GLchar *name);
GL_APICALL فراغ GL_APIENTRY gl_Get_فعال_یکنواخت (GLuint برنامه, GLuint شاخص, GLsizei buf_اندازه, GLsizei *درازی, GLint *اندازه, GLenum *type, GLchar *name);
GL_APICALL فراغ GL_APIENTRY glGetAttachedShaders (GLuint برنامه, GLsizei max_شمار, GLsizei *شمار, GLuint *shaders);
GL_APICALL GLint GL_APIENTRY glGetAttribLocation (GLuint برنامه, ثابت GLchar *name);
GL_APICALL فراغ GL_APIENTRY glGetBooleanv (GLenum pname, GLboolean *داده);
GL_APICALL فراغ GL_APIENTRY gl_Get_میانگیر_Parameteriv (GLenum هدف, GLenum pname, GLint *params);
GL_APICALL GLenum GL_APIENTRY glGetError (فراغ);
GL_APICALL فراغ GL_APIENTRY glGetFloatv (GLenum pname, GLfloat *داده);
GL_APICALL فراغ GL_APIENTRY glGetFramebufferAttachmentParameteriv (GLenum هدف, GLenum attachment, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetIntegerv (GLenum pname, GLint *داده);
GL_APICALL فراغ GL_APIENTRY glGetProgramiv (GLuint برنامه, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY gl_Get_برنامه_Info_Log (GLuint برنامه, GLsizei buf_اندازه, GLsizei *درازی, GLchar *infoLog);
GL_APICALL فراغ GL_APIENTRY glGetRenderbufferParameteriv (GLenum هدف, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetShaderiv (GLuint shader, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetShaderInfoLog (GLuint shader, GLsizei buf_اندازه, GLsizei *درازی, GLchar *infoLog);
GL_APICALL فراغ GL_APIENTRY glGetShaderPrecisionFormat (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
GL_APICALL فراغ GL_APIENTRY gl_Get_Shader_منبع (GLuint shader, GLsizei buf_اندازه, GLsizei *درازی, GLchar *منبع);
GL_APICALL ثابت GLubyte *GL_APIENTRY glGetString (GLenum name);
GL_APICALL فراغ GL_APIENTRY glGetTexParameterfv (GLenum هدف, GLenum pname, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY glGetTexParameteriv (GLenum هدف, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetUniformfv (GLuint برنامه, GLint location, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY glGetUniformiv (GLuint برنامه, GLint location, GLint *params);
GL_APICALL GLint GL_APIENTRY gl_Get_یکنواخت_Location (GLuint برنامه, ثابت GLchar *name);
GL_APICALL فراغ GL_APIENTRY gl_Get_رأس_Attribfv (GLuint شاخص, GLenum pname, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY gl_Get_رأس_Attribiv (GLuint شاخص, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY gl_Get_رأس_Attrib_Pointerv (GLuint شاخص, GLenum pname, فراغ **اشاره_گر_2);
GL_APICALL فراغ GL_APIENTRY glHint (GLenum هدف, GLenum نما);
GL_APICALL GLboolean GL_APIENTRY gl_Is_میانگیر (GLuint میانگیر_2);
GL_APICALL GLboolean GL_APIENTRY glIsEnabled (GLenum cap);
GL_APICALL GLboolean GL_APIENTRY glIsFramebuffer (GLuint framebuffer);
GL_APICALL GLboolean GL_APIENTRY gl_Is_برنامه (GLuint برنامه);
GL_APICALL GLboolean GL_APIENTRY glIsRenderbuffer (GLuint renderbuffer);
GL_APICALL GLboolean GL_APIENTRY glIsShader (GLuint shader);
GL_APICALL GLboolean GL_APIENTRY glIsTexture (GLuint texture);
GL_APICALL فراغ GL_APIENTRY gl_سطر_عرض (GLfloat عرض);
GL_APICALL فراغ GL_APIENTRY gl_Link_برنامه (GLuint برنامه);
GL_APICALL فراغ GL_APIENTRY glPixelStorei (GLenum pname, GLint param);
GL_APICALL فراغ GL_APIENTRY gl_Polygon_جابه_جایی (GLfloat ضریب, GLfloat units);
GL_APICALL فراغ GL_APIENTRY glReadPixels (GLint x, GLint y, GLsizei عرض, GLsizei ارتفاع, GLenum format, GLenum type, فراغ *pixels);
GL_APICALL فراغ GL_APIENTRY glReleaseShaderCompiler (فراغ);
GL_APICALL فراغ GL_APIENTRY glRenderbufferStorage (GLenum هدف, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
GL_APICALL فراغ GL_APIENTRY glSampleCoverage (GLfloat مقدار, GLboolean invert);
GL_APICALL فراغ GL_APIENTRY glScissor (GLint x, GLint y, GLsizei عرض, GLsizei ارتفاع);
GL_APICALL فراغ GL_APIENTRY gl_Shader_دودویی (GLsizei شمار, ثابت GLuint *shaders, GLenum دودویی_Format, ثابت فراغ *دودویی, GLsizei درازی);
GL_APICALL فراغ GL_APIENTRY gl_Shader_منبع (GLuint shader, GLsizei شمار, ثابت GLchar *ثابت*string, ثابت GLint *درازی);
GL_APICALL فراغ GL_APIENTRY glStencilFunc (GLenum func, GLint ref, GLuint ماسک);
GL_APICALL فراغ GL_APIENTRY glStencilFuncSeparate (GLenum face, GLenum func, GLint ref, GLuint ماسک);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_ماسک (GLuint ماسک);
GL_APICALL فراغ GL_APIENTRY gl_Stencil_ماسک_Separate (GLenum face, GLuint ماسک);
GL_APICALL فراغ GL_APIENTRY glStencilOp (GLenum fail, GLenum zfail, GLenum zpass);
GL_APICALL فراغ GL_APIENTRY glStencilOpSeparate (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
GL_APICALL فراغ GL_APIENTRY glTexImage2D (GLenum هدف, GLint level, GLint internalformat, GLsizei عرض, GLsizei ارتفاع, GLint border, GLenum format, GLenum type, ثابت فراغ *pixels);
GL_APICALL فراغ GL_APIENTRY glTexParameterf (GLenum هدف, GLenum pname, GLfloat param);
GL_APICALL فراغ GL_APIENTRY glTexParameterfv (GLenum هدف, GLenum pname, ثابت GLfloat *params);
GL_APICALL فراغ GL_APIENTRY glTexParameteri (GLenum هدف, GLenum pname, GLint param);
GL_APICALL فراغ GL_APIENTRY glTexParameteriv (GLenum هدف, GLenum pname, ثابت GLint *params);
GL_APICALL فراغ GL_APIENTRY glTexSubImage2D (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLsizei عرض, GLsizei ارتفاع, GLenum format, GLenum type, ثابت فراغ *pixels);
GL_APICALL فراغ GL_APIENTRY glUniform1f (GLint location, GLfloat v0);
GL_APICALL فراغ GL_APIENTRY glUniform1fv (GLint location, GLsizei شمار, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY glUniform1i (GLint location, GLint v0);
GL_APICALL فراغ GL_APIENTRY glUniform1iv (GLint location, GLsizei شمار, ثابت GLint *مقدار);
GL_APICALL فراغ GL_APIENTRY glUniform2f (GLint location, GLfloat v0, GLfloat v1);
GL_APICALL فراغ GL_APIENTRY glUniform2fv (GLint location, GLsizei شمار, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY glUniform2i (GLint location, GLint v0, GLint v1);
GL_APICALL فراغ GL_APIENTRY glUniform2iv (GLint location, GLsizei شمار, ثابت GLint *مقدار);
GL_APICALL فراغ GL_APIENTRY glUniform3f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
GL_APICALL فراغ GL_APIENTRY glUniform3fv (GLint location, GLsizei شمار, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY glUniform3i (GLint location, GLint v0, GLint v1, GLint v2);
GL_APICALL فراغ GL_APIENTRY glUniform3iv (GLint location, GLsizei شمار, ثابت GLint *مقدار);
GL_APICALL فراغ GL_APIENTRY glUniform4f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
GL_APICALL فراغ GL_APIENTRY glUniform4fv (GLint location, GLsizei شمار, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY glUniform4i (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
GL_APICALL فراغ GL_APIENTRY glUniform4iv (GLint location, GLsizei شمار, ثابت GLint *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_یکنواخت_Matrix2fv (GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_یکنواخت_Matrix3fv (GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_یکنواخت_Matrix4fv (GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_Use_برنامه (GLuint برنامه);
GL_APICALL فراغ GL_APIENTRY gl_Validate_برنامه (GLuint برنامه);
GL_APICALL فراغ GL_APIENTRY gl_رأس_Attrib1f (GLuint شاخص, GLfloat x);
GL_APICALL فراغ GL_APIENTRY gl_رأس_Attrib1fv (GLuint شاخص, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY gl_رأس_Attrib2f (GLuint شاخص, GLfloat x, GLfloat y);
GL_APICALL فراغ GL_APIENTRY gl_رأس_Attrib2fv (GLuint شاخص, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY gl_رأس_Attrib3f (GLuint شاخص, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL فراغ GL_APIENTRY gl_رأس_Attrib3fv (GLuint شاخص, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY gl_رأس_Attrib4f (GLuint شاخص, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
GL_APICALL فراغ GL_APIENTRY gl_رأس_Attrib4fv (GLuint شاخص, ثابت GLfloat *v);
GL_APICALL فراغ GL_APIENTRY gl_رأس_Attrib_اشاره_گر (GLuint شاخص, GLint اندازه, GLenum type, GLboolean normalized, GLsizei stride, ثابت فراغ *اشاره_گر_2);
GL_APICALL فراغ GL_APIENTRY glViewport (GLint x, GLint y, GLsizei عرض, GLsizei ارتفاع);
#پایان_اگر
#پایان_اگر /* GL_ES_VERSION_2_0 */

#اگر_تعریف_نشده GL_ES_نسخه_3_0
#تعریف_کن GL_ES_نسخه_3_0 1
تعريفنوع khronos_uint16_t GLhalf;
#تعریف_کن GL_READ_میانگیر                    0x0C02
#تعریف_کن GL_UNPACK_ردیف_درازی              0x0CF2
#تعریف_کن GL_UNPACK_SKIP_ردیفها               0x0CF3
#تعریف_کن GL_UNPACK_SKIP_PIXELS             0x0CF4
#تعریف_کن GL_PACK_ردیف_درازی                0x0D02
#تعریف_کن GL_PACK_SKIP_ردیفها                 0x0D03
#تعریف_کن GL_PACK_SKIP_PIXELS               0x0D04
#تعریف_کن GL_COLOR                          0x1800
#تعریف_کن GL_عمق                          0x1801
#تعریف_کن GL_STENCIL                        0x1802
#تعریف_کن GL_RED                            0x1903
#تعریف_کن GL_RGB8                           0x8051
#تعریف_کن GL_RGBA8                          0x8058
#تعریف_کن GL_RGB10_A2                       0x8059
#تعریف_کن GL_TEXTURE_BINDING_3D             0x806A
#تعریف_کن GL_UNPACK_SKIP_IMAGES             0x806D
#تعریف_کن GL_UNPACK_IMAGE_ارتفاع            0x806E
#تعریف_کن GL_TEXTURE_3D                     0x806F
#تعریف_کن GL_TEXTURE_WRAP_R                 0x8072
#تعریف_کن GL_MAX_3_D_TEXTURE_اندازه            0x8073
#تعریف_کن GL_UNSIGNED_INT_2_10_10_10_REV    0x8368
#تعریف_کن GL_MAX_ELEMENTS_VERTICES          0x80E8
#تعریف_کن GL_MAX_ELEMENTS_INDICES           0x80E9
#تعریف_کن GL_TEXTURE_MIN_LOD                0x813A
#تعریف_کن GL_TEXTURE_MAX_LOD                0x813B
#تعریف_کن GL_TEXTURE_پایه_LEVEL             0x813C
#تعریف_کن GL_TEXTURE_MAX_LEVEL              0x813D
#تعریف_کن GL_MIN                            0x8007
#تعریف_کن GL_MAX                            0x8008
#تعریف_کن GL_عمق_COMPONENT24              0x81A6
#تعریف_کن GL_MAX_TEXTURE_LOD_BIAS           0x84FD
#تعریف_کن GL_TEXTURE_COMPARE_نما           0x884C
#تعریف_کن GL_TEXTURE_COMPARE_FUNC           0x884D
#تعریف_کن GL_CURRENT_QUERY                  0x8865
#تعریف_کن GL_QUERY_نتیجه                   0x8866
#تعریف_کن GL_QUERY_نتیجه_موجود         0x8867
#تعریف_کن GL_میانگیر_MAPPED                  0x88BC
#تعریف_کن GL_میانگیر_MAP_اشاره_گر             0x88BD
#تعریف_کن GL_جریان_READ                    0x88E1
#تعریف_کن GL_جریان_COPY                    0x88E2
#تعریف_کن GL_STATIC_READ                    0x88E5
#تعریف_کن GL_STATIC_COPY                    0x88E6
#تعریف_کن GL_DYNAMIC_READ                   0x88E9
#تعریف_کن GL_DYNAMIC_COPY                   0x88EA
#تعریف_کن GL_MAX_DRAW_BUFFERS               0x8824
#تعریف_کن GL_DRAW_BUFFER0                   0x8825
#تعریف_کن GL_DRAW_BUFFER1                   0x8826
#تعریف_کن GL_DRAW_BUFFER2                   0x8827
#تعریف_کن GL_DRAW_BUFFER3                   0x8828
#تعریف_کن GL_DRAW_BUFFER4                   0x8829
#تعریف_کن GL_DRAW_BUFFER5                   0x882A
#تعریف_کن GL_DRAW_BUFFER6                   0x882B
#تعریف_کن GL_DRAW_BUFFER7                   0x882C
#تعریف_کن GL_DRAW_BUFFER8                   0x882D
#تعریف_کن GL_DRAW_BUFFER9                   0x882E
#تعریف_کن GL_DRAW_BUFFER10                  0x882F
#تعریف_کن GL_DRAW_BUFFER11                  0x8830
#تعریف_کن GL_DRAW_BUFFER12                  0x8831
#تعریف_کن GL_DRAW_BUFFER13                  0x8832
#تعریف_کن GL_DRAW_BUFFER14                  0x8833
#تعریف_کن GL_DRAW_BUFFER15                  0x8834
#تعریف_کن GL_MAX_FRAGMENT_یکنواخت_COMPONENTS 0x8B49
#تعریف_کن GL_MAX_رأس_یکنواخت_COMPONENTS  0x8B4A
#تعریف_کن GL_SAMPLER_3D                     0x8B5F
#تعریف_کن GL_SAMPLER_2D_SHADOW              0x8B62
#تعریف_کن GL_FRAGMENT_SHADER_DERIVATIVE_HINT 0x8B8B
#تعریف_کن GL_PIXEL_PACK_میانگیر              0x88EB
#تعریف_کن GL_PIXEL_UNPACK_میانگیر            0x88EC
#تعریف_کن GL_PIXEL_PACK_میانگیر_BINDING      0x88ED
#تعریف_کن GL_PIXEL_UNPACK_میانگیر_BINDING    0x88EF
#تعریف_کن GL_FLOAT_MAT2x3                   0x8B65
#تعریف_کن GL_FLOAT_MAT2x4                   0x8B66
#تعریف_کن GL_FLOAT_MAT3x2                   0x8B67
#تعریف_کن GL_FLOAT_MAT3x4                   0x8B68
#تعریف_کن GL_FLOAT_MAT4x2                   0x8B69
#تعریف_کن GL_FLOAT_MAT4x3                   0x8B6A
#تعریف_کن GL_SRGB                           0x8C40
#تعریف_کن GL_SRGB8                          0x8C41
#تعریف_کن GL_SRGB8_ALPHA8                   0x8C43
#تعریف_کن GL_COMPARE_REF_مقصد_TEXTURE         0x884E
#تعریف_کن GL_MAJOR_نسخه                  0x821B
#تعریف_کن GL_MINOR_نسخه                  0x821C
#تعریف_کن GL_رقم_EXTENSIONS                 0x821D
#تعریف_کن GL_RGBA32F                        0x8814
#تعریف_کن GL_RGB32F                         0x8815
#تعریف_کن GL_RGBA16F                        0x881A
#تعریف_کن GL_RGB16F                         0x881B
#تعریف_کن GL_رأس_ATTRIB_ARRAY_INTEGER    0x88FD
#تعریف_کن GL_MAX_ARRAY_TEXTURE_LAYERS       0x88FF
#تعریف_کن GL_MIN_برنامه_TEXEL_جابه_جایی       0x8904
#تعریف_کن GL_MAX_برنامه_TEXEL_جابه_جایی       0x8905
#تعریف_کن GL_MAX_VARYING_COMPONENTS         0x8B4B
#تعریف_کن GL_TEXTURE_2D_ARRAY               0x8C1A
#تعریف_کن GL_TEXTURE_BINDING_2D_ARRAY       0x8C1D
#تعریف_کن GL_R11F_G11F_B10F                 0x8C3A
#تعریف_کن GL_UNSIGNED_INT_10F_11F_11F_REV   0x8C3B
#تعریف_کن GL_RGB9_E5                        0x8C3D
#تعریف_کن GL_UNSIGNED_INT_5_9_9_9_REV       0x8C3E
#تعریف_کن GL_TRANSFORM_FEEDBACK_VARYING_MAX_درازی 0x8C76
#تعریف_کن GL_TRANSFORM_FEEDBACK_میانگیر_نما 0x8C7F
#تعریف_کن GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS 0x8C80
#تعریف_کن GL_TRANSFORM_FEEDBACK_VARYINGS    0x8C83
#تعریف_کن GL_TRANSFORM_FEEDBACK_میانگیر_شروع 0x8C84
#تعریف_کن GL_TRANSFORM_FEEDBACK_میانگیر_اندازه 0x8C85
#تعریف_کن GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN 0x8C88
#تعریف_کن GL_RASTERIZER_DISCARD             0x8C89
#تعریف_کن GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS 0x8C8A
#تعریف_کن GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS 0x8C8B
#تعریف_کن GL_INTERLEAVED_ATTRIBS            0x8C8C
#تعریف_کن GL_SEPARATE_ATTRIBS               0x8C8D
#تعریف_کن GL_TRANSFORM_FEEDBACK_میانگیر      0x8C8E
#تعریف_کن GL_TRANSFORM_FEEDBACK_میانگیر_BINDING 0x8C8F
#تعریف_کن GL_RGBA32UI                       0x8D70
#تعریف_کن GL_RGB32UI                        0x8D71
#تعریف_کن GL_RGBA16UI                       0x8D76
#تعریف_کن GL_RGB16UI                        0x8D77
#تعریف_کن GL_RGBA8UI                        0x8D7C
#تعریف_کن GL_RGB8UI                         0x8D7D
#تعریف_کن GL_RGBA32I                        0x8D82
#تعریف_کن GL_RGB32I                         0x8D83
#تعریف_کن GL_RGBA16I                        0x8D88
#تعریف_کن GL_RGB16I                         0x8D89
#تعریف_کن GL_RGBA8I                         0x8D8E
#تعریف_کن GL_RGB8I                          0x8D8F
#تعریف_کن GL_RED_INTEGER                    0x8D94
#تعریف_کن GL_RGB_INTEGER                    0x8D98
#تعریف_کن GL_RGBA_INTEGER                   0x8D99
#تعریف_کن GL_SAMPLER_2D_ARRAY               0x8DC1
#تعریف_کن GL_SAMPLER_2D_ARRAY_SHADOW        0x8DC4
#تعریف_کن GL_SAMPLER_CUBE_SHADOW            0x8DC5
#تعریف_کن GL_UNSIGNED_INT_VEC2              0x8DC6
#تعریف_کن GL_UNSIGNED_INT_VEC3              0x8DC7
#تعریف_کن GL_UNSIGNED_INT_VEC4              0x8DC8
#تعریف_کن GL_INT_SAMPLER_2D                 0x8DCA
#تعریف_کن GL_INT_SAMPLER_3D                 0x8DCB
#تعریف_کن GL_INT_SAMPLER_CUBE               0x8DCC
#تعریف_کن GL_INT_SAMPLER_2D_ARRAY           0x8DCF
#تعریف_کن GL_UNSIGNED_INT_SAMPLER_2D        0x8DD2
#تعریف_کن GL_UNSIGNED_INT_SAMPLER_3D        0x8DD3
#تعریف_کن GL_UNSIGNED_INT_SAMPLER_CUBE      0x8DD4
#تعریف_کن GL_UNSIGNED_INT_SAMPLER_2D_ARRAY  0x8DD7
#تعریف_کن GL_میانگیر_ACCESS_FLAGS            0x911F
#تعریف_کن GL_میانگیر_MAP_درازی              0x9120
#تعریف_کن GL_میانگیر_MAP_جابه_جایی              0x9121
#تعریف_کن GL_عمق_COMPONENT32_F             0x8CAC
#تعریف_کن GL_DEPTH32F_STENCIL8              0x8CAD
#تعریف_کن GL_FLOAT_32_UNSIGNED_INT_24_8_REV 0x8DAD
#تعریف_کن GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING 0x8210
#تعریف_کن GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE 0x8211
#تعریف_کن GL_FRAMEBUFFER_ATTACHMENT_RED_اندازه 0x8212
#تعریف_کن GL_FRAMEBUFFER_ATTACHMENT_GREEN_اندازه 0x8213
#تعریف_کن GL_FRAMEBUFFER_ATTACHMENT_BLUE_اندازه 0x8214
#تعریف_کن GL_FRAMEBUFFER_ATTACHMENT_ALPHA_اندازه 0x8215
#تعریف_کن GL_FRAMEBUFFER_ATTACHMENT_عمق_اندازه 0x8216
#تعریف_کن GL_FRAMEBUFFER_ATTACHMENT_STENCIL_اندازه 0x8217
#تعریف_کن GL_FRAMEBUFFER_DEFAULT            0x8218
#تعریف_کن GL_FRAMEBUFFER_UNDEFINED          0x8219
#تعریف_کن GL_عمق_STENCIL_ATTACHMENT       0x821A
#تعریف_کن GL_عمق_STENCIL                  0x84F9
#تعریف_کن GL_UNSIGNED_INT_24_8              0x84FA
#تعریف_کن GL_DEPTH24_STENCIL8               0x88F0
#تعریف_کن GL_UNSIGNED_NORMALIZED            0x8C17
#تعریف_کن GL_DRAW_FRAMEBUFFER_BINDING       0x8CA6
#تعریف_کن GL_READ_FRAMEBUFFER               0x8CA8
#تعریف_کن GL_DRAW_FRAMEBUFFER               0x8CA9
#تعریف_کن GL_READ_FRAMEBUFFER_BINDING       0x8CAA
#تعریف_کن GL_RENDERBUFFER_SAMPLES           0x8CAB
#تعریف_کن GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER 0x8CD4
#تعریف_کن GL_MAX_COLOR_ATTACHMENTS          0x8CDF
#تعریف_کن GL_COLOR_ATTACHMENT1              0x8CE1
#تعریف_کن GL_COLOR_ATTACHMENT2              0x8CE2
#تعریف_کن GL_COLOR_ATTACHMENT3              0x8CE3
#تعریف_کن GL_COLOR_ATTACHMENT4              0x8CE4
#تعریف_کن GL_COLOR_ATTACHMENT5              0x8CE5
#تعریف_کن GL_COLOR_ATTACHMENT6              0x8CE6
#تعریف_کن GL_COLOR_ATTACHMENT7              0x8CE7
#تعریف_کن GL_COLOR_ATTACHMENT8              0x8CE8
#تعریف_کن GL_COLOR_ATTACHMENT9              0x8CE9
#تعریف_کن GL_COLOR_ATTACHMENT10             0x8CEA
#تعریف_کن GL_COLOR_ATTACHMENT11             0x8CEB
#تعریف_کن GL_COLOR_ATTACHMENT12             0x8CEC
#تعریف_کن GL_COLOR_ATTACHMENT13             0x8CED
#تعریف_کن GL_COLOR_ATTACHMENT14             0x8CEE
#تعریف_کن GL_COLOR_ATTACHMENT15             0x8CEF
#تعریف_کن GL_COLOR_ATTACHMENT16             0x8CF0
#تعریف_کن GL_COLOR_ATTACHMENT17             0x8CF1
#تعریف_کن GL_COLOR_ATTACHMENT18             0x8CF2
#تعریف_کن GL_COLOR_ATTACHMENT19             0x8CF3
#تعریف_کن GL_COLOR_ATTACHMENT20             0x8CF4
#تعریف_کن GL_COLOR_ATTACHMENT21             0x8CF5
#تعریف_کن GL_COLOR_ATTACHMENT22             0x8CF6
#تعریف_کن GL_COLOR_ATTACHMENT23             0x8CF7
#تعریف_کن GL_COLOR_ATTACHMENT24             0x8CF8
#تعریف_کن GL_COLOR_ATTACHMENT25             0x8CF9
#تعریف_کن GL_COLOR_ATTACHMENT26             0x8CFA
#تعریف_کن GL_COLOR_ATTACHMENT27             0x8CFB
#تعریف_کن GL_COLOR_ATTACHMENT28             0x8CFC
#تعریف_کن GL_COLOR_ATTACHMENT29             0x8CFD
#تعریف_کن GL_COLOR_ATTACHMENT30             0x8CFE
#تعریف_کن GL_COLOR_ATTACHMENT31             0x8CFF
#تعریف_کن GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE 0x8D56
#تعریف_کن GL_MAX_SAMPLES                    0x8D57
#تعریف_کن GL_HALF_FLOAT                     0x140B
#تعریف_کن GL_MAP_READ_بیت                   0x0001
#تعریف_کن GL_MAP_WRITE_بیت                  0x0002
#تعریف_کن GL_MAP_INVALIDATE_RANGE_بیت       0x0004
#تعریف_کن GL_MAP_INVALIDATE_میانگیر_بیت      0x0008
#تعریف_کن GL_MAP_FLUSH_EXPLICIT_بیت         0x0010
#تعریف_کن GL_MAP_UNSYNCHRONIZED_بیت         0x0020
#تعریف_کن GL_RG                             0x8227
#تعریف_کن GL_RG_INTEGER                     0x8228
#تعریف_کن GL_R8                             0x8229
#تعریف_کن GL_RG8                            0x822B
#تعریف_کن GL_R16F                           0x822D
#تعریف_کن GL_R32F                           0x822E
#تعریف_کن GL_RG16F                          0x822F
#تعریف_کن GL_RG32F                          0x8230
#تعریف_کن GL_R8I                            0x8231
#تعریف_کن GL_R8UI                           0x8232
#تعریف_کن GL_R16I                           0x8233
#تعریف_کن GL_R16UI                          0x8234
#تعریف_کن GL_R32I                           0x8235
#تعریف_کن GL_R32UI                          0x8236
#تعریف_کن GL_RG8I                           0x8237
#تعریف_کن GL_RG8UI                          0x8238
#تعریف_کن GL_RG16I                          0x8239
#تعریف_کن GL_RG16UI                         0x823A
#تعریف_کن GL_RG32I                          0x823B
#تعریف_کن GL_RG32UI                         0x823C
#تعریف_کن GL_رأس_ARRAY_BINDING           0x85B5
#تعریف_کن GL_R8_SNORM                       0x8F94
#تعریف_کن GL_RG8_SNORM                      0x8F95
#تعریف_کن GL_RGB8_SNORM                     0x8F96
#تعریف_کن GL_RGBA8_SNORM                    0x8F97
#تعریف_کن GL_SIGNED_NORMALIZED              0x8F9C
#تعریف_کن GL_PRIMITIVE_RESTART_FIXED_شاخص  0x8D69
#تعریف_کن GL_COPY_READ_میانگیر               0x8F36
#تعریف_کن GL_COPY_WRITE_میانگیر              0x8F37
#تعریف_کن GL_COPY_READ_میانگیر_BINDING       0x8F36
#تعریف_کن GL_COPY_WRITE_میانگیر_BINDING      0x8F37
#تعریف_کن GL_یکنواخت_میانگیر                 0x8A11
#تعریف_کن GL_یکنواخت_میانگیر_BINDING         0x8A28
#تعریف_کن GL_یکنواخت_میانگیر_شروع           0x8A29
#تعریف_کن GL_یکنواخت_میانگیر_اندازه            0x8A2A
#تعریف_کن GL_MAX_رأس_یکنواخت_بلوکها      0x8A2B
#تعریف_کن GL_MAX_FRAGMENT_یکنواخت_بلوکها    0x8A2D
#تعریف_کن GL_MAX_COMBINED_یکنواخت_بلوکها    0x8A2E
#تعریف_کن GL_MAX_یکنواخت_میانگیر_BINDINGS    0x8A2F
#تعریف_کن GL_MAX_یکنواخت_بلوک_اندازه         0x8A30
#تعریف_کن GL_MAX_COMBINED_رأس_یکنواخت_COMPONENTS 0x8A31
#تعریف_کن GL_MAX_COMBINED_FRAGMENT_یکنواخت_COMPONENTS 0x8A33
#تعریف_کن GL_یکنواخت_میانگیر_جابه_جایی_ALIGNMENT 0x8A34
#تعریف_کن GL_فعال_یکنواخت_بلوک_MAX_NAME_درازی 0x8A35
#تعریف_کن GL_فعال_یکنواخت_بلوکها          0x8A36
#تعریف_کن GL_یکنواخت_TYPE                   0x8A37
#تعریف_کن GL_یکنواخت_اندازه                   0x8A38
#تعریف_کن GL_یکنواخت_NAME_درازی            0x8A39
#تعریف_کن GL_یکنواخت_بلوک_شاخص            0x8A3A
#تعریف_کن GL_یکنواخت_جابه_جایی                 0x8A3B
#تعریف_کن GL_یکنواخت_ARRAY_STRIDE           0x8A3C
#تعریف_کن GL_یکنواخت_ماتریس_STRIDE          0x8A3D
#تعریف_کن GL_یکنواخت_IS_ردیف_MAJOR           0x8A3E
#تعریف_کن GL_یکنواخت_بلوک_BINDING          0x8A3F
#تعریف_کن GL_یکنواخت_بلوک_داده_اندازه        0x8A40
#تعریف_کن GL_یکنواخت_بلوک_NAME_درازی      0x8A41
#تعریف_کن GL_یکنواخت_بلوک_فعال_UNIFORMS  0x8A42
#تعریف_کن GL_یکنواخت_بلوک_فعال_یکنواخت_INDICES 0x8A43
#تعریف_کن GL_یکنواخت_بلوک_REFERENCED_BY_رأس_SHADER 0x8A44
#تعریف_کن GL_یکنواخت_بلوک_REFERENCED_BY_FRAGMENT_SHADER 0x8A46
#تعریف_کن GL_INVALID_شاخص                  0xFFFFFFFFu
#تعریف_کن GL_MAX_رأس_OUTPUT_COMPONENTS   0x9122
#تعریف_کن GL_MAX_FRAGMENT_درون_داد_COMPONENTS  0x9125
#تعریف_کن GL_MAX_SERVER_WAIT_TIMEOUT        0x9111
#تعریف_کن GL_OBJECT_TYPE                    0x9112
#تعریف_کن GL_SYNC_CONDITION                 0x9113
#تعریف_کن GL_SYNC_وضعیت                    0x9114
#تعریف_کن GL_SYNC_FLAGS                     0x9115
#تعریف_کن GL_SYNC_FENCE                     0x9116
#تعریف_کن GL_SYNC_GPU_COMMANDS_COMPLETE     0x9117
#تعریف_کن GL_UNSIGNALED                     0x9118
#تعریف_کن GL_SIGNALED                       0x9119
#تعریف_کن GL_ALREADY_SIGNALED               0x911A
#تعریف_کن GL_TIMEOUT_EXPIRED                0x911B
#تعریف_کن GL_CONDITION_SATISFIED            0x911C
#تعریف_کن GL_WAIT_FAILED                    0x911D
#تعریف_کن GL_SYNC_FLUSH_COMMANDS_بیت        0x00000001
#تعریف_کن GL_TIMEOUT_IGNORED                0xFFFFFFFFFFFFFFFFull
#تعریف_کن GL_رأس_ATTRIB_ARRAY_مقسوم_علیه    0x88FE
#تعریف_کن GL_ANY_SAMPLES_PASSED             0x8C2F
#تعریف_کن GL_ANY_SAMPLES_PASSED_CONSERVATIVE 0x8D6A
#تعریف_کن GL_SAMPLER_BINDING                0x8919
#تعریف_کن GL_RGB10_A2UI                     0x906F
#تعریف_کن GL_TEXTURE_SWIZZLE_R              0x8E42
#تعریف_کن GL_TEXTURE_SWIZZLE_G              0x8E43
#تعریف_کن GL_TEXTURE_SWIZZLE_B              0x8E44
#تعریف_کن GL_TEXTURE_SWIZZLE_A              0x8E45
#تعریف_کن GL_GREEN                          0x1904
#تعریف_کن GL_BLUE                           0x1905
#تعریف_کن GL_INT_2_10_10_10_REV             0x8D9F
#تعریف_کن GL_TRANSFORM_FEEDBACK             0x8E22
#تعریف_کن GL_TRANSFORM_FEEDBACK_PAUSED      0x8E23
#تعریف_کن GL_TRANSFORM_FEEDBACK_فعال      0x8E24
#تعریف_کن GL_TRANSFORM_FEEDBACK_BINDING     0x8E25
#تعریف_کن GL_برنامه_دودویی_RETRIEVABLE_HINT 0x8257
#تعریف_کن GL_برنامه_دودویی_درازی          0x8741
#تعریف_کن GL_رقم_برنامه_دودویی_FORMATS     0x87FE
#تعریف_کن GL_برنامه_دودویی_FORMATS         0x87FF
#تعریف_کن GL_COMPRESSED_R11_EAC             0x9270
#تعریف_کن GL_COMPRESSED_SIGNED_R11_EAC      0x9271
#تعریف_کن GL_COMPRESSED_RG11_EAC            0x9272
#تعریف_کن GL_COMPRESSED_SIGNED_RG11_EAC     0x9273
#تعریف_کن GL_COMPRESSED_RGB8_ETC2           0x9274
#تعریف_کن GL_COMPRESSED_SRGB8_ETC2          0x9275
#تعریف_کن GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9276
#تعریف_کن GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9277
#تعریف_کن GL_COMPRESSED_RGBA8_ETC2_EAC      0x9278
#تعریف_کن GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC 0x9279
#تعریف_کن GL_TEXTURE_IMMUTABLE_FORMAT       0x912F
#تعریف_کن GL_MAX_ELEMENT_شاخص              0x8D6B
#تعریف_کن GL_رقم_SAMPLE_COUNTS              0x9380
#تعریف_کن GL_TEXTURE_IMMUTABLE_سطوح       0x82DF
تعريفنوع فراغ (GL_APIENTRYP PFNGLREADBUFFERPROC) (GLenum src);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWRANGEELEMENTSPROC) (GLenum نما, GLuint شروع, GLuint انتها, GLsizei شمار, GLenum type, ثابت فراغ *indices);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXIMAGE3DPROC) (GLenum هدف, GLint level, GLint internalformat, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLint border, GLenum format, GLenum type, ثابت فراغ *pixels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSUBIMAGE3DPROC) (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLenum format, GLenum type, ثابت فراغ *pixels);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYTEXSUBIMAGE3DPROC) (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei عرض, GLsizei ارتفاع);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOMPRESSEDTEXIMAGE3DPROC) (GLenum هدف, GLint level, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLint border, GLsizei image_اندازه, ثابت فراغ *داده);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC) (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLenum format, GLsizei image_اندازه, ثابت فراغ *داده);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENQUERIESPROC) (GLsizei n, GLuint *ids);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEQUERIESPROC) (GLsizei n, ثابت GLuint *ids);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISQUERYPROC) (GLuint id);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBEGINQUERYPROC) (GLenum هدف, GLuint id);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENDQUERYPROC) (GLenum هدف);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETQUERYIVPROC) (GLenum هدف, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETQUERYOBJECTUIVPROC) (GLuint id, GLenum pname, GLuint *params);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLUNMAPBUFFERPROC) (GLenum هدف);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETBUFFERPOINTERVPROC) (GLenum هدف, GLenum pname, فراغ **params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWBUFFERSPROC) (GLsizei n, ثابت GLenum *bufs);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX2X3FVPROC) (GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX3X2FVPROC) (GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX2X4FVPROC) (GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX4X2FVPROC) (GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX3X4FVPROC) (GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMMATRIX4X3FVPROC) (GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBLITFRAMEBUFFERPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield ماسک, GLenum filter);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC) (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURELAYERPROC) (GLenum هدف, GLenum attachment, GLuint texture, GLint level, GLint layer);
تعريفنوع فراغ *(GL_APIENTRYP PFNGLMAPBUFFERRANGEPROC) (GLenum هدف, GLintptr جابه_جایی_2, GLsizeiptr درازی, GLbitfield access);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEPROC) (GLenum هدف, GLintptr جابه_جایی_2, GLsizeiptr درازی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDVERTEXARRAYPROC) (GLuint array);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEVERTEXARRAYSPROC) (GLsizei n, ثابت GLuint *arrays);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint *arrays);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISVERTEXARRAYPROC) (GLuint array);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTEGERI_VPROC) (GLenum هدف, GLuint شاخص, GLint *داده);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBEGINTRANSFORMFEEDBACKPROC) (GLenum primitive_نما);
تعريفنوع فراغ (GL_APIENTRYP PFNGLENDTRANSFORMFEEDBACKPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDBUFFERRANGEPROC) (GLenum هدف, GLuint شاخص, GLuint میانگیر_2, GLintptr جابه_جایی_2, GLsizeiptr اندازه);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDBUFFERBASEPROC) (GLenum هدف, GLuint شاخص, GLuint میانگیر_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTRANSFORMFEEDBACKVARYINGSPROC) (GLuint برنامه, GLsizei شمار, ثابت GLchar *ثابت*varyings, GLenum میانگیر_نما);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTRANSFORMFEEDBACKVARYINGPROC) (GLuint برنامه, GLuint شاخص, GLsizei buf_اندازه, GLsizei *درازی, GLsizei *اندازه, GLenum *type, GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBIPOINTERPROC) (GLuint شاخص, GLint اندازه, GLenum type, GLsizei stride, ثابت فراغ *اشاره_گر_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETVERTEXATTRIBIIVPROC) (GLuint شاخص, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETVERTEXATTRIBIUIVPROC) (GLuint شاخص, GLenum pname, GLuint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBI4IPROC) (GLuint شاخص, GLint x, GLint y, GLint z, GLint w);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBI4UIPROC) (GLuint شاخص, GLuint x, GLuint y, GLuint z, GLuint w);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBI4IVPROC) (GLuint شاخص, ثابت GLint *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBI4UIVPROC) (GLuint شاخص, ثابت GLuint *v);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETUNIFORMUIVPROC) (GLuint برنامه, GLint location, GLuint *params);
تعريفنوع GLint (GL_APIENTRYP PFNGLGETFRAGDATALOCATIONPROC) (GLuint برنامه, ثابت GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1UIPROC) (GLint location, GLuint v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2UIPROC) (GLint location, GLuint v0, GLuint v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3UIPROC) (GLint location, GLuint v0, GLuint v1, GLuint v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4UIPROC) (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM1UIVPROC) (GLint location, GLsizei شمار, ثابت GLuint *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM2UIVPROC) (GLint location, GLsizei شمار, ثابت GLuint *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM3UIVPROC) (GLint location, GLsizei شمار, ثابت GLuint *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORM4UIVPROC) (GLint location, GLsizei شمار, ثابت GLuint *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARBUFFERIVPROC) (GLenum میانگیر_2, GLint drawbuffer, ثابت GLint *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARBUFFERUIVPROC) (GLenum میانگیر_2, GLint drawbuffer, ثابت GLuint *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARBUFFERFVPROC) (GLenum میانگیر_2, GLint drawbuffer, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCLEARBUFFERFIPROC) (GLenum میانگیر_2, GLint drawbuffer, GLfloat عمق_2, GLint stencil);
تعريفنوع ثابت GLubyte *(GL_APIENTRYP PFNGLGETSTRINGIPROC) (GLenum name, GLuint شاخص);
تعريفنوع فراغ (GL_APIENTRYP PFNGLCOPYBUFFERSUBDATAPROC) (GLenum read_هدف, GLenum write_هدف, GLintptr read_جابه_جایی, GLintptr write_جابه_جایی, GLsizeiptr اندازه);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETUNIFORMINDICESPROC) (GLuint برنامه, GLsizei یکنواخت_شمار, ثابت GLchar *ثابت*یکنواخت_نامها, GLuint *یکنواخت_Indices);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETACTIVEUNIFORMSIVPROC) (GLuint برنامه, GLsizei یکنواخت_شمار, ثابت GLuint *یکنواخت_Indices, GLenum pname, GLint *params);
تعريفنوع GLuint (GL_APIENTRYP PFNGLGETUNIFORMBLOCKINDEXPROC) (GLuint برنامه, ثابت GLchar *یکنواخت_بلوک_Name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKIVPROC) (GLuint برنامه, GLuint یکنواخت_بلوک_شاخص, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC) (GLuint برنامه, GLuint یکنواخت_بلوک_شاخص, GLsizei buf_اندازه, GLsizei *درازی, GLchar *یکنواخت_بلوک_Name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUNIFORMBLOCKBINDINGPROC) (GLuint برنامه, GLuint یکنواخت_بلوک_شاخص, GLuint یکنواخت_بلوک_Binding);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDPROC) (GLenum نما, GLint اولی, GLsizei شمار, GLsizei instancecount);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDPROC) (GLenum نما, GLsizei شمار, GLenum type, ثابت فراغ *indices, GLsizei instancecount);
تعريفنوع GLsync (GL_APIENTRYP PFNGLFENCESYNCPROC) (GLenum condition, GLbitfield flags);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISSYNCPROC) (GLsync sync);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETESYNCPROC) (GLsync sync);
تعريفنوع GLenum (GL_APIENTRYP PFNGLCLIENTWAITSYNCPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
تعريفنوع فراغ (GL_APIENTRYP PFNGLWAITSYNCPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTEGER64VPROC) (GLenum pname, GLint64 *داده);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSYNCIVPROC) (GLsync sync, GLenum pname, GLsizei شمار, GLsizei *درازی, GLint *مقادیر);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTEGER64I_VPROC) (GLenum هدف, GLuint شاخص, GLint64 *داده);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETBUFFERPARAMETERI64VPROC) (GLenum هدف, GLenum pname, GLint64 *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENSAMPLERSPROC) (GLsizei شمار, GLuint *samplers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETESAMPLERSPROC) (GLsizei شمار, ثابت GLuint *samplers);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISSAMPLERPROC) (GLuint sampler);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDSAMPLERPROC) (GLuint unit, GLuint sampler);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIPROC) (GLuint sampler, GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, ثابت GLint *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERFPROC) (GLuint sampler, GLenum pname, GLfloat param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, ثابت GLfloat *param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBDIVISORPROC) (GLuint شاخص, GLuint مقسوم_علیه);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDTRANSFORMFEEDBACKPROC) (GLenum هدف, GLuint id);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETETRANSFORMFEEDBACKSPROC) (GLsizei n, ثابت GLuint *ids);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENTRANSFORMFEEDBACKSPROC) (GLsizei n, GLuint *ids);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISTRANSFORMFEEDBACKPROC) (GLuint id);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPAUSETRANSFORMFEEDBACKPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLRESUMETRANSFORMFEEDBACKPROC) (فراغ);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMBINARYPROC) (GLuint برنامه, GLsizei buf_اندازه, GLsizei *درازی, GLenum *دودویی_Format, فراغ *دودویی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMBINARYPROC) (GLuint برنامه, GLenum دودویی_Format, ثابت فراغ *دودویی, GLsizei درازی);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMPARAMETERIPROC) (GLuint برنامه, GLenum pname, GLint مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLINVALIDATEFRAMEBUFFERPROC) (GLenum هدف, GLsizei رقم_Attachments, ثابت GLenum *attachments);
تعريفنوع فراغ (GL_APIENTRYP PFNGLINVALIDATESUBFRAMEBUFFERPROC) (GLenum هدف, GLsizei رقم_Attachments, ثابت GLenum *attachments, GLint x, GLint y, GLsizei عرض, GLsizei ارتفاع);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE2DPROC) (GLenum هدف, GLsizei سطوح, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE3DPROC) (GLenum هدف, GLsizei سطوح, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETINTERNALFORMATIVPROC) (GLenum هدف, GLenum internalformat, GLenum pname, GLsizei شمار, GLint *params);
#إذا GL_GLES_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY gl_Read_میانگیر (GLenum src);
GL_APICALL فراغ GL_APIENTRY glDrawRangeElements (GLenum نما, GLuint شروع, GLuint انتها, GLsizei شمار, GLenum type, ثابت فراغ *indices);
GL_APICALL فراغ GL_APIENTRY glTexImage3D (GLenum هدف, GLint level, GLint internalformat, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLint border, GLenum format, GLenum type, ثابت فراغ *pixels);
GL_APICALL فراغ GL_APIENTRY glTexSubImage3D (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLenum format, GLenum type, ثابت فراغ *pixels);
GL_APICALL فراغ GL_APIENTRY glCopyTexSubImage3D (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei عرض, GLsizei ارتفاع);
GL_APICALL فراغ GL_APIENTRY glCompressedTexImage3D (GLenum هدف, GLint level, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLint border, GLsizei image_اندازه, ثابت فراغ *داده);
GL_APICALL فراغ GL_APIENTRY glCompressedTexSubImage3D (GLenum هدف, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2, GLenum format, GLsizei image_اندازه, ثابت فراغ *داده);
GL_APICALL فراغ GL_APIENTRY glGenQueries (GLsizei n, GLuint *ids);
GL_APICALL فراغ GL_APIENTRY glDeleteQueries (GLsizei n, ثابت GLuint *ids);
GL_APICALL GLboolean GL_APIENTRY glIsQuery (GLuint id);
GL_APICALL فراغ GL_APIENTRY glBeginQuery (GLenum هدف, GLuint id);
GL_APICALL فراغ GL_APIENTRY gl_انتها_Query (GLenum هدف);
GL_APICALL فراغ GL_APIENTRY glGetQueryiv (GLenum هدف, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetQueryObjectuiv (GLuint id, GLenum pname, GLuint *params);
GL_APICALL GLboolean GL_APIENTRY gl_Unmap_میانگیر (GLenum هدف);
GL_APICALL فراغ GL_APIENTRY gl_Get_میانگیر_Pointerv (GLenum هدف, GLenum pname, فراغ **params);
GL_APICALL فراغ GL_APIENTRY glDrawBuffers (GLsizei n, ثابت GLenum *bufs);
GL_APICALL فراغ GL_APIENTRY gl_یکنواخت_Matrix2x3fv (GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_یکنواخت_Matrix3x2fv (GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_یکنواخت_Matrix2x4fv (GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_یکنواخت_Matrix4x2fv (GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_یکنواخت_Matrix3x4fv (GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_یکنواخت_Matrix4x3fv (GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY glBlitFramebuffer (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield ماسک, GLenum filter);
GL_APICALL فراغ GL_APIENTRY glRenderbufferStorageMultisample (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
GL_APICALL فراغ GL_APIENTRY glFramebufferTextureLayer (GLenum هدف, GLenum attachment, GLuint texture, GLint level, GLint layer);
GL_APICALL فراغ *GL_APIENTRY gl_Map_میانگیر_Range (GLenum هدف, GLintptr جابه_جایی_2, GLsizeiptr درازی, GLbitfield access);
GL_APICALL فراغ GL_APIENTRY gl_Flush_Mapped_میانگیر_Range (GLenum هدف, GLintptr جابه_جایی_2, GLsizeiptr درازی);
GL_APICALL فراغ GL_APIENTRY gl_Bind_رأس_Array (GLuint array);
GL_APICALL فراغ GL_APIENTRY gl_Delete_رأس_Arrays (GLsizei n, ثابت GLuint *arrays);
GL_APICALL فراغ GL_APIENTRY gl_Gen_رأس_Arrays (GLsizei n, GLuint *arrays);
GL_APICALL GLboolean GL_APIENTRY gl_Is_رأس_Array (GLuint array);
GL_APICALL فراغ GL_APIENTRY glGetIntegeri_v (GLenum هدف, GLuint شاخص, GLint *داده);
GL_APICALL فراغ GL_APIENTRY glBeginTransformFeedback (GLenum primitive_نما);
GL_APICALL فراغ GL_APIENTRY gl_انتها_Transform_Feedback (فراغ);
GL_APICALL فراغ GL_APIENTRY gl_Bind_میانگیر_Range (GLenum هدف, GLuint شاخص, GLuint میانگیر_2, GLintptr جابه_جایی_2, GLsizeiptr اندازه);
GL_APICALL فراغ GL_APIENTRY gl_Bind_میانگیر_پایه (GLenum هدف, GLuint شاخص, GLuint میانگیر_2);
GL_APICALL فراغ GL_APIENTRY glTransformFeedbackVaryings (GLuint برنامه, GLsizei شمار, ثابت GLchar *ثابت*varyings, GLenum میانگیر_نما);
GL_APICALL فراغ GL_APIENTRY glGetTransformFeedbackVarying (GLuint برنامه, GLuint شاخص, GLsizei buf_اندازه, GLsizei *درازی, GLsizei *اندازه, GLenum *type, GLchar *name);
GL_APICALL فراغ GL_APIENTRY gl_رأس_Attrib_IPointer (GLuint شاخص, GLint اندازه, GLenum type, GLsizei stride, ثابت فراغ *اشاره_گر_2);
GL_APICALL فراغ GL_APIENTRY gl_Get_رأس_Attrib_Iiv (GLuint شاخص, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY gl_Get_رأس_Attrib_Iuiv (GLuint شاخص, GLenum pname, GLuint *params);
GL_APICALL فراغ GL_APIENTRY gl_رأس_Attrib_I4i (GLuint شاخص, GLint x, GLint y, GLint z, GLint w);
GL_APICALL فراغ GL_APIENTRY gl_رأس_Attrib_I4ui (GLuint شاخص, GLuint x, GLuint y, GLuint z, GLuint w);
GL_APICALL فراغ GL_APIENTRY gl_رأس_Attrib_I4iv (GLuint شاخص, ثابت GLint *v);
GL_APICALL فراغ GL_APIENTRY gl_رأس_Attrib_I4uiv (GLuint شاخص, ثابت GLuint *v);
GL_APICALL فراغ GL_APIENTRY glGetUniformuiv (GLuint برنامه, GLint location, GLuint *params);
GL_APICALL GLint GL_APIENTRY gl_Get_Frag_داده_Location (GLuint برنامه, ثابت GLchar *name);
GL_APICALL فراغ GL_APIENTRY glUniform1ui (GLint location, GLuint v0);
GL_APICALL فراغ GL_APIENTRY glUniform2ui (GLint location, GLuint v0, GLuint v1);
GL_APICALL فراغ GL_APIENTRY glUniform3ui (GLint location, GLuint v0, GLuint v1, GLuint v2);
GL_APICALL فراغ GL_APIENTRY glUniform4ui (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
GL_APICALL فراغ GL_APIENTRY glUniform1uiv (GLint location, GLsizei شمار, ثابت GLuint *مقدار);
GL_APICALL فراغ GL_APIENTRY glUniform2uiv (GLint location, GLsizei شمار, ثابت GLuint *مقدار);
GL_APICALL فراغ GL_APIENTRY glUniform3uiv (GLint location, GLsizei شمار, ثابت GLuint *مقدار);
GL_APICALL فراغ GL_APIENTRY glUniform4uiv (GLint location, GLsizei شمار, ثابت GLuint *مقدار);
GL_APICALL فراغ GL_APIENTRY glClearBufferiv (GLenum میانگیر_2, GLint drawbuffer, ثابت GLint *مقدار);
GL_APICALL فراغ GL_APIENTRY glClearBufferuiv (GLenum میانگیر_2, GLint drawbuffer, ثابت GLuint *مقدار);
GL_APICALL فراغ GL_APIENTRY glClearBufferfv (GLenum میانگیر_2, GLint drawbuffer, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY glClearBufferfi (GLenum میانگیر_2, GLint drawbuffer, GLfloat عمق_2, GLint stencil);
GL_APICALL ثابت GLubyte *GL_APIENTRY glGetStringi (GLenum name, GLuint شاخص);
GL_APICALL فراغ GL_APIENTRY gl_Copy_میانگیر_Sub_داده (GLenum read_هدف, GLenum write_هدف, GLintptr read_جابه_جایی, GLintptr write_جابه_جایی, GLsizeiptr اندازه);
GL_APICALL فراغ GL_APIENTRY gl_Get_یکنواخت_Indices (GLuint برنامه, GLsizei یکنواخت_شمار, ثابت GLchar *ثابت*یکنواخت_نامها, GLuint *یکنواخت_Indices);
GL_APICALL فراغ GL_APIENTRY gl_Get_فعال_Uniformsiv (GLuint برنامه, GLsizei یکنواخت_شمار, ثابت GLuint *یکنواخت_Indices, GLenum pname, GLint *params);
GL_APICALL GLuint GL_APIENTRY gl_Get_یکنواخت_بلوک_شاخص (GLuint برنامه, ثابت GLchar *یکنواخت_بلوک_Name);
GL_APICALL فراغ GL_APIENTRY gl_Get_فعال_یکنواخت_Blockiv (GLuint برنامه, GLuint یکنواخت_بلوک_شاخص, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY gl_Get_فعال_یکنواخت_بلوک_Name (GLuint برنامه, GLuint یکنواخت_بلوک_شاخص, GLsizei buf_اندازه, GLsizei *درازی, GLchar *یکنواخت_بلوک_Name);
GL_APICALL فراغ GL_APIENTRY gl_یکنواخت_بلوک_Binding (GLuint برنامه, GLuint یکنواخت_بلوک_شاخص, GLuint یکنواخت_بلوک_Binding);
GL_APICALL فراغ GL_APIENTRY glDrawArraysInstanced (GLenum نما, GLint اولی, GLsizei شمار, GLsizei instancecount);
GL_APICALL فراغ GL_APIENTRY glDrawElementsInstanced (GLenum نما, GLsizei شمار, GLenum type, ثابت فراغ *indices, GLsizei instancecount);
GL_APICALL GLsync GL_APIENTRY glFenceSync (GLenum condition, GLbitfield flags);
GL_APICALL GLboolean GL_APIENTRY glIsSync (GLsync sync);
GL_APICALL فراغ GL_APIENTRY glDeleteSync (GLsync sync);
GL_APICALL GLenum GL_APIENTRY glClientWaitSync (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_APICALL فراغ GL_APIENTRY glWaitSync (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_APICALL فراغ GL_APIENTRY glGetInteger64v (GLenum pname, GLint64 *داده);
GL_APICALL فراغ GL_APIENTRY glGetSynciv (GLsync sync, GLenum pname, GLsizei شمار, GLsizei *درازی, GLint *مقادیر);
GL_APICALL فراغ GL_APIENTRY glGetInteger64i_v (GLenum هدف, GLuint شاخص, GLint64 *داده);
GL_APICALL فراغ GL_APIENTRY gl_Get_میانگیر_Parameteri64v (GLenum هدف, GLenum pname, GLint64 *params);
GL_APICALL فراغ GL_APIENTRY glGenSamplers (GLsizei شمار, GLuint *samplers);
GL_APICALL فراغ GL_APIENTRY glDeleteSamplers (GLsizei شمار, ثابت GLuint *samplers);
GL_APICALL GLboolean GL_APIENTRY glIsSampler (GLuint sampler);
GL_APICALL فراغ GL_APIENTRY glBindSampler (GLuint unit, GLuint sampler);
GL_APICALL فراغ GL_APIENTRY glSamplerParameteri (GLuint sampler, GLenum pname, GLint param);
GL_APICALL فراغ GL_APIENTRY glSamplerParameteriv (GLuint sampler, GLenum pname, ثابت GLint *param);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterf (GLuint sampler, GLenum pname, GLfloat param);
GL_APICALL فراغ GL_APIENTRY glSamplerParameterfv (GLuint sampler, GLenum pname, ثابت GLfloat *param);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameteriv (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetSamplerParameterfv (GLuint sampler, GLenum pname, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY gl_رأس_Attrib_مقسوم_علیه (GLuint شاخص, GLuint مقسوم_علیه);
GL_APICALL فراغ GL_APIENTRY glBindTransformFeedback (GLenum هدف, GLuint id);
GL_APICALL فراغ GL_APIENTRY glDeleteTransformFeedbacks (GLsizei n, ثابت GLuint *ids);
GL_APICALL فراغ GL_APIENTRY glGenTransformFeedbacks (GLsizei n, GLuint *ids);
GL_APICALL GLboolean GL_APIENTRY glIsTransformFeedback (GLuint id);
GL_APICALL فراغ GL_APIENTRY glPauseTransformFeedback (فراغ);
GL_APICALL فراغ GL_APIENTRY glResumeTransformFeedback (فراغ);
GL_APICALL فراغ GL_APIENTRY gl_Get_برنامه_دودویی (GLuint برنامه, GLsizei buf_اندازه, GLsizei *درازی, GLenum *دودویی_Format, فراغ *دودویی);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_دودویی (GLuint برنامه, GLenum دودویی_Format, ثابت فراغ *دودویی, GLsizei درازی);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Parameteri (GLuint برنامه, GLenum pname, GLint مقدار);
GL_APICALL فراغ GL_APIENTRY glInvalidateFramebuffer (GLenum هدف, GLsizei رقم_Attachments, ثابت GLenum *attachments);
GL_APICALL فراغ GL_APIENTRY glInvalidateSubFramebuffer (GLenum هدف, GLsizei رقم_Attachments, ثابت GLenum *attachments, GLint x, GLint y, GLsizei عرض, GLsizei ارتفاع);
GL_APICALL فراغ GL_APIENTRY glTexStorage2D (GLenum هدف, GLsizei سطوح, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع);
GL_APICALL فراغ GL_APIENTRY glTexStorage3D (GLenum هدف, GLsizei سطوح, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع, GLsizei عمق_2);
GL_APICALL فراغ GL_APIENTRY glGetInternalformativ (GLenum هدف, GLenum internalformat, GLenum pname, GLsizei شمار, GLint *params);
#پایان_اگر
#پایان_اگر /* GL_ES_VERSION_3_0 */

#اگر_تعریف_نشده GL_ES_نسخه_3_1
#تعریف_کن GL_ES_نسخه_3_1 1
#تعریف_کن GL_COMPUTE_SHADER                 0x91B9
#تعریف_کن GL_MAX_COMPUTE_یکنواخت_بلوکها     0x91BB
#تعریف_کن GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS 0x91BC
#تعریف_کن GL_MAX_COMPUTE_IMAGE_UNIFORMS     0x91BD
#تعریف_کن GL_MAX_COMPUTE_SHARED_حافظه_اندازه 0x8262
#تعریف_کن GL_MAX_COMPUTE_یکنواخت_COMPONENTS 0x8263
#تعریف_کن GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS 0x8264
#تعریف_کن GL_MAX_COMPUTE_ATOMIC_COUNTERS    0x8265
#تعریف_کن GL_MAX_COMBINED_COMPUTE_یکنواخت_COMPONENTS 0x8266
#تعریف_کن GL_MAX_COMPUTE_WORK_گروه_INVOCATIONS 0x90EB
#تعریف_کن GL_MAX_COMPUTE_WORK_گروه_شمار   0x91BE
#تعریف_کن GL_MAX_COMPUTE_WORK_گروه_اندازه    0x91BF
#تعریف_کن GL_COMPUTE_WORK_گروه_اندازه        0x8267
#تعریف_کن GL_DISPATCH_غیرمستقیم_میانگیر       0x90EE
#تعریف_کن GL_DISPATCH_غیرمستقیم_میانگیر_BINDING 0x90EF
#تعریف_کن GL_COMPUTE_SHADER_بیت             0x00000020
#تعریف_کن GL_DRAW_غیرمستقیم_میانگیر           0x8F3F
#تعریف_کن GL_DRAW_غیرمستقیم_میانگیر_BINDING   0x8F43
#تعریف_کن GL_MAX_یکنواخت_LOCATIONS          0x826E
#تعریف_کن GL_FRAMEBUFFER_DEFAULT_عرض      0x9310
#تعریف_کن GL_FRAMEBUFFER_DEFAULT_ارتفاع     0x9311
#تعریف_کن GL_FRAMEBUFFER_DEFAULT_SAMPLES    0x9313
#تعریف_کن GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS 0x9314
#تعریف_کن GL_MAX_FRAMEBUFFER_عرض          0x9315
#تعریف_کن GL_MAX_FRAMEBUFFER_ارتفاع         0x9316
#تعریف_کن GL_MAX_FRAMEBUFFER_SAMPLES        0x9318
#تعریف_کن GL_یکنواخت                        0x92E1
#تعریف_کن GL_یکنواخت_بلوک                  0x92E2
#تعریف_کن GL_برنامه_درون_داد                  0x92E3
#تعریف_کن GL_برنامه_OUTPUT                 0x92E4
#تعریف_کن GL_میانگیر_VARIABLE                0x92E5
#تعریف_کن GL_SHADER_STORAGE_بلوک           0x92E6
#تعریف_کن GL_ATOMIC_COUNTER_میانگیر          0x92C0
#تعریف_کن GL_TRANSFORM_FEEDBACK_VARYING     0x92F4
#تعریف_کن GL_فعال_RESOURCES               0x92F5
#تعریف_کن GL_MAX_NAME_درازی                0x92F6
#تعریف_کن GL_MAX_رقم_فعال_VARIABLES       0x92F7
#تعریف_کن GL_NAME_درازی                    0x92F9
#تعریف_کن GL_TYPE                           0x92FA
#تعریف_کن GL_ARRAY_اندازه                     0x92FB
#تعریف_کن GL_جابه_جایی                         0x92FC
#تعریف_کن GL_بلوک_شاخص                    0x92FD
#تعریف_کن GL_ARRAY_STRIDE                   0x92FE
#تعریف_کن GL_ماتریس_STRIDE                  0x92FF
#تعریف_کن GL_IS_ردیف_MAJOR                   0x9300
#تعریف_کن GL_ATOMIC_COUNTER_میانگیر_شاخص    0x9301
#تعریف_کن GL_میانگیر_BINDING                 0x9302
#تعریف_کن GL_میانگیر_داده_اندازه               0x9303
#تعریف_کن GL_رقم_فعال_VARIABLES           0x9304
#تعریف_کن GL_فعال_VARIABLES               0x9305
#تعریف_کن GL_REFERENCED_BY_رأس_SHADER    0x9306
#تعریف_کن GL_REFERENCED_BY_FRAGMENT_SHADER  0x930A
#تعریف_کن GL_REFERENCED_BY_COMPUTE_SHADER   0x930B
#تعریف_کن GL_بالاترین_LEVEL_ARRAY_اندازه           0x930C
#تعریف_کن GL_بالاترین_LEVEL_ARRAY_STRIDE         0x930D
#تعریف_کن GL_LOCATION                       0x930E
#تعریف_کن GL_رأس_SHADER_بیت              0x00000001
#تعریف_کن GL_FRAGMENT_SHADER_بیت            0x00000002
#تعریف_کن GL_ALL_SHADER_بیتها                0xFFFFFFFF
#تعریف_کن GL_برنامه_SEPARABLE              0x8258
#تعریف_کن GL_فعال_برنامه                 0x8259
#تعریف_کن GL_برنامه_PIPELINE_BINDING       0x825A
#تعریف_کن GL_ATOMIC_COUNTER_میانگیر_BINDING  0x92C1
#تعریف_کن GL_ATOMIC_COUNTER_میانگیر_شروع    0x92C2
#تعریف_کن GL_ATOMIC_COUNTER_میانگیر_اندازه     0x92C3
#تعریف_کن GL_MAX_رأس_ATOMIC_COUNTER_BUFFERS 0x92CC
#تعریف_کن GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS 0x92D0
#تعریف_کن GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS 0x92D1
#تعریف_کن GL_MAX_رأس_ATOMIC_COUNTERS     0x92D2
#تعریف_کن GL_MAX_FRAGMENT_ATOMIC_COUNTERS   0x92D6
#تعریف_کن GL_MAX_COMBINED_ATOMIC_COUNTERS   0x92D7
#تعریف_کن GL_MAX_ATOMIC_COUNTER_میانگیر_اندازه 0x92D8
#تعریف_کن GL_MAX_ATOMIC_COUNTER_میانگیر_BINDINGS 0x92DC
#تعریف_کن GL_فعال_ATOMIC_COUNTER_BUFFERS  0x92D9
#تعریف_کن GL_UNSIGNED_INT_ATOMIC_COUNTER    0x92DB
#تعریف_کن GL_MAX_IMAGE_UNITS                0x8F38
#تعریف_کن GL_MAX_رأس_IMAGE_UNIFORMS      0x90CA
#تعریف_کن GL_MAX_FRAGMENT_IMAGE_UNIFORMS    0x90CE
#تعریف_کن GL_MAX_COMBINED_IMAGE_UNIFORMS    0x90CF
#تعریف_کن GL_IMAGE_BINDING_NAME             0x8F3A
#تعریف_کن GL_IMAGE_BINDING_LEVEL            0x8F3B
#تعریف_کن GL_IMAGE_BINDING_LAYERED          0x8F3C
#تعریف_کن GL_IMAGE_BINDING_LAYER            0x8F3D
#تعریف_کن GL_IMAGE_BINDING_ACCESS           0x8F3E
#تعریف_کن GL_IMAGE_BINDING_FORMAT           0x906E
#تعریف_کن GL_رأس_ATTRIB_ARRAY_BARRIER_بیت 0x00000001
#تعریف_کن GL_ELEMENT_ARRAY_BARRIER_بیت      0x00000002
#تعریف_کن GL_یکنواخت_BARRIER_بیت            0x00000004
#تعریف_کن GL_TEXTURE_FETCH_BARRIER_بیت      0x00000008
#تعریف_کن GL_SHADER_IMAGE_ACCESS_BARRIER_بیت 0x00000020
#تعریف_کن GL_COMMAND_BARRIER_بیت            0x00000040
#تعریف_کن GL_PIXEL_میانگیر_BARRIER_بیت       0x00000080
#تعریف_کن GL_TEXTURE_UPDATE_BARRIER_بیت     0x00000100
#تعریف_کن GL_میانگیر_UPDATE_BARRIER_بیت      0x00000200
#تعریف_کن GL_FRAMEBUFFER_BARRIER_بیت        0x00000400
#تعریف_کن GL_TRANSFORM_FEEDBACK_BARRIER_بیت 0x00000800
#تعریف_کن GL_ATOMIC_COUNTER_BARRIER_بیت     0x00001000
#تعریف_کن GL_ALL_BARRIER_بیتها               0xFFFFFFFF
#تعریف_کن GL_IMAGE_2D                       0x904D
#تعریف_کن GL_IMAGE_3D                       0x904E
#تعریف_کن GL_IMAGE_CUBE                     0x9050
#تعریف_کن GL_IMAGE_2D_ARRAY                 0x9053
#تعریف_کن GL_INT_IMAGE_2D                   0x9058
#تعریف_کن GL_INT_IMAGE_3D                   0x9059
#تعریف_کن GL_INT_IMAGE_CUBE                 0x905B
#تعریف_کن GL_INT_IMAGE_2D_ARRAY             0x905E
#تعریف_کن GL_UNSIGNED_INT_IMAGE_2D          0x9063
#تعریف_کن GL_UNSIGNED_INT_IMAGE_3D          0x9064
#تعریف_کن GL_UNSIGNED_INT_IMAGE_CUBE        0x9066
#تعریف_کن GL_UNSIGNED_INT_IMAGE_2D_ARRAY    0x9069
#تعریف_کن GL_IMAGE_FORMAT_COMPATIBILITY_TYPE 0x90C7
#تعریف_کن GL_IMAGE_FORMAT_COMPATIBILITY_BY_اندازه 0x90C8
#تعریف_کن GL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS 0x90C9
#تعریف_کن GL_READ_ONLY                      0x88B8
#تعریف_کن GL_WRITE_ONLY                     0x88B9
#تعریف_کن GL_READ_WRITE                     0x88BA
#تعریف_کن GL_SHADER_STORAGE_میانگیر          0x90D2
#تعریف_کن GL_SHADER_STORAGE_میانگیر_BINDING  0x90D3
#تعریف_کن GL_SHADER_STORAGE_میانگیر_شروع    0x90D4
#تعریف_کن GL_SHADER_STORAGE_میانگیر_اندازه     0x90D5
#تعریف_کن GL_MAX_رأس_SHADER_STORAGE_بلوکها 0x90D6
#تعریف_کن GL_MAX_FRAGMENT_SHADER_STORAGE_بلوکها 0x90DA
#تعریف_کن GL_MAX_COMPUTE_SHADER_STORAGE_بلوکها 0x90DB
#تعریف_کن GL_MAX_COMBINED_SHADER_STORAGE_بلوکها 0x90DC
#تعریف_کن GL_MAX_SHADER_STORAGE_میانگیر_BINDINGS 0x90DD
#تعریف_کن GL_MAX_SHADER_STORAGE_بلوک_اندازه  0x90DE
#تعریف_کن GL_SHADER_STORAGE_میانگیر_جابه_جایی_ALIGNMENT 0x90DF
#تعریف_کن GL_SHADER_STORAGE_BARRIER_بیت     0x00002000
#تعریف_کن GL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES 0x8F39
#تعریف_کن GL_عمق_STENCIL_TEXTURE_نما     0x90EA
#تعریف_کن GL_STENCIL_شاخص                  0x1901
#تعریف_کن GL_MIN_برنامه_TEXTURE_GATHER_جابه_جایی 0x8E5E
#تعریف_کن GL_MAX_برنامه_TEXTURE_GATHER_جابه_جایی 0x8E5F
#تعریف_کن GL_SAMPLE_POSITION                0x8E50
#تعریف_کن GL_SAMPLE_ماسک                    0x8E51
#تعریف_کن GL_SAMPLE_ماسک_مقدار              0x8E52
#تعریف_کن GL_TEXTURE_2D_MULTISAMPLE         0x9100
#تعریف_کن GL_MAX_SAMPLE_ماسک_واژگان          0x8E59
#تعریف_کن GL_MAX_COLOR_TEXTURE_SAMPLES      0x910E
#تعریف_کن GL_MAX_عمق_TEXTURE_SAMPLES      0x910F
#تعریف_کن GL_MAX_INTEGER_SAMPLES            0x9110
#تعریف_کن GL_TEXTURE_BINDING_2D_MULTISAMPLE 0x9104
#تعریف_کن GL_TEXTURE_SAMPLES                0x9106
#تعریف_کن GL_TEXTURE_FIXED_SAMPLE_LOCATIONS 0x9107
#تعریف_کن GL_TEXTURE_عرض                  0x1000
#تعریف_کن GL_TEXTURE_ارتفاع                 0x1001
#تعریف_کن GL_TEXTURE_عمق                  0x8071
#تعریف_کن GL_TEXTURE_داخلی_FORMAT        0x1003
#تعریف_کن GL_TEXTURE_RED_اندازه               0x805C
#تعریف_کن GL_TEXTURE_GREEN_اندازه             0x805D
#تعریف_کن GL_TEXTURE_BLUE_اندازه              0x805E
#تعریف_کن GL_TEXTURE_ALPHA_اندازه             0x805F
#تعریف_کن GL_TEXTURE_عمق_اندازه             0x884A
#تعریف_کن GL_TEXTURE_STENCIL_اندازه           0x88F1
#تعریف_کن GL_TEXTURE_SHARED_اندازه            0x8C3F
#تعریف_کن GL_TEXTURE_RED_TYPE               0x8C10
#تعریف_کن GL_TEXTURE_GREEN_TYPE             0x8C11
#تعریف_کن GL_TEXTURE_BLUE_TYPE              0x8C12
#تعریف_کن GL_TEXTURE_ALPHA_TYPE             0x8C13
#تعریف_کن GL_TEXTURE_عمق_TYPE             0x8C16
#تعریف_کن GL_TEXTURE_COMPRESSED             0x86A1
#تعریف_کن GL_SAMPLER_2D_MULTISAMPLE         0x9108
#تعریف_کن GL_INT_SAMPLER_2D_MULTISAMPLE     0x9109
#تعریف_کن GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE 0x910A
#تعریف_کن GL_رأس_ATTRIB_BINDING          0x82D4
#تعریف_کن GL_رأس_ATTRIB_RELATIVE_جابه_جایی  0x82D5
#تعریف_کن GL_رأس_BINDING_مقسوم_علیه         0x82D6
#تعریف_کن GL_رأس_BINDING_جابه_جایی          0x82D7
#تعریف_کن GL_رأس_BINDING_STRIDE          0x82D8
#تعریف_کن GL_رأس_BINDING_میانگیر          0x8F4F
#تعریف_کن GL_MAX_رأس_ATTRIB_RELATIVE_جابه_جایی 0x82D9
#تعریف_کن GL_MAX_رأس_ATTRIB_BINDINGS     0x82DA
#تعریف_کن GL_MAX_رأس_ATTRIB_STRIDE       0x82E5
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISPATCHCOMPUTEPROC) (GLuint رقم_groups_x, GLuint رقم_groups_y, GLuint رقم_groups_z);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDISPATCHCOMPUTEINDIRECTPROC) (GLintptr غیرمستقیم);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWARRAYSINDIRECTPROC) (GLenum نما, ثابت فراغ *غیرمستقیم);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDRAWELEMENTSINDIRECTPROC) (GLenum نما, GLenum type, ثابت فراغ *غیرمستقیم);
تعريفنوع فراغ (GL_APIENTRYP PFNGLFRAMEBUFFERPARAMETERIPROC) (GLenum هدف, GLenum pname, GLint param);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETFRAMEBUFFERPARAMETERIVPROC) (GLenum هدف, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMINTERFACEIVPROC) (GLuint برنامه, GLenum برنامه_Interface, GLenum pname, GLint *params);
تعريفنوع GLuint (GL_APIENTRYP PFNGLGETPROGRAMRESOURCEINDEXPROC) (GLuint برنامه, GLenum برنامه_Interface, ثابت GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMRESOURCENAMEPROC) (GLuint برنامه, GLenum برنامه_Interface, GLuint شاخص, GLsizei buf_اندازه, GLsizei *درازی, GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMRESOURCEIVPROC) (GLuint برنامه, GLenum برنامه_Interface, GLuint شاخص, GLsizei prop_شمار, ثابت GLenum *props, GLsizei شمار, GLsizei *درازی, GLint *params);
تعريفنوع GLint (GL_APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONPROC) (GLuint برنامه, GLenum برنامه_Interface, ثابت GLchar *name);
تعريفنوع فراغ (GL_APIENTRYP PFNGLUSEPROGRAMSTAGESPROC) (GLuint pipeline, GLbitfield stages, GLuint برنامه);
تعريفنوع فراغ (GL_APIENTRYP PFNGLACTIVESHADERPROGRAMPROC) (GLuint pipeline, GLuint برنامه);
تعريفنوع GLuint (GL_APIENTRYP PFNGLCREATESHADERPROGRAMVPROC) (GLenum type, GLsizei شمار, ثابت GLchar *ثابت*رشتهها);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDPROGRAMPIPELINEPROC) (GLuint pipeline);
تعريفنوع فراغ (GL_APIENTRYP PFNGLDELETEPROGRAMPIPELINESPROC) (GLsizei n, ثابت GLuint *pipelines);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGENPROGRAMPIPELINESPROC) (GLsizei n, GLuint *pipelines);
تعريفنوع GLboolean (GL_APIENTRYP PFNGLISPROGRAMPIPELINEPROC) (GLuint pipeline);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMPIPELINEIVPROC) (GLuint pipeline, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1IPROC) (GLuint برنامه, GLint location, GLint v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2IPROC) (GLuint برنامه, GLint location, GLint v0, GLint v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3IPROC) (GLuint برنامه, GLint location, GLint v0, GLint v1, GLint v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4IPROC) (GLuint برنامه, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UIPROC) (GLuint برنامه, GLint location, GLuint v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UIPROC) (GLuint برنامه, GLint location, GLuint v0, GLuint v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UIPROC) (GLuint برنامه, GLint location, GLuint v0, GLuint v1, GLuint v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UIPROC) (GLuint برنامه, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1FPROC) (GLuint برنامه, GLint location, GLfloat v0);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2FPROC) (GLuint برنامه, GLint location, GLfloat v0, GLfloat v1);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3FPROC) (GLuint برنامه, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4FPROC) (GLuint برنامه, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1IVPROC) (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLint *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2IVPROC) (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLint *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3IVPROC) (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLint *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4IVPROC) (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLint *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UIVPROC) (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLuint *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UIVPROC) (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLuint *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UIVPROC) (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLuint *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UIVPROC) (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLuint *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1FVPROC) (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2FVPROC) (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3FVPROC) (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4FVPROC) (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2FVPROC) (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3FVPROC) (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4FVPROC) (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC) (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC) (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC) (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC) (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC) (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC) (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVALIDATEPROGRAMPIPELINEPROC) (GLuint pipeline);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETPROGRAMPIPELINEINFOLOGPROC) (GLuint pipeline, GLsizei buf_اندازه, GLsizei *درازی, GLchar *infoLog);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDIMAGETEXTUREPROC) (GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETBOOLEANI_VPROC) (GLenum هدف, GLuint شاخص, GLboolean *داده);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMEMORYBARRIERPROC) (GLbitfield barriers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLMEMORYBARRIERBYREGIONPROC) (GLbitfield barriers);
تعريفنوع فراغ (GL_APIENTRYP PFNGLTEXSTORAGE2DMULTISAMPLEPROC) (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع, GLboolean fixedsamplelocations);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETMULTISAMPLEFVPROC) (GLenum pname, GLuint شاخص, GLfloat *val);
تعريفنوع فراغ (GL_APIENTRYP PFNGLSAMPLEMASKIPROC) (GLuint ماسک_عدد, GLbitfield ماسک);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXLEVELPARAMETERIVPROC) (GLenum هدف, GLint level, GLenum pname, GLint *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLGETTEXLEVELPARAMETERFVPROC) (GLenum هدف, GLint level, GLenum pname, GLfloat *params);
تعريفنوع فراغ (GL_APIENTRYP PFNGLBINDVERTEXBUFFERPROC) (GLuint bindingindex, GLuint میانگیر_2, GLintptr جابه_جایی_2, GLsizei stride);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBFORMATPROC) (GLuint attribindex, GLint اندازه, GLenum type, GLboolean normalized, GLuint relativeoffset);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBIFORMATPROC) (GLuint attribindex, GLint اندازه, GLenum type, GLuint relativeoffset);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXATTRIBBINDINGPROC) (GLuint attribindex, GLuint bindingindex);
تعريفنوع فراغ (GL_APIENTRYP PFNGLVERTEXBINDINGDIVISORPROC) (GLuint bindingindex, GLuint مقسوم_علیه);
#إذا GL_GLES_PROTOTYPES
GL_APICALL فراغ GL_APIENTRY glDispatchCompute (GLuint رقم_groups_x, GLuint رقم_groups_y, GLuint رقم_groups_z);
GL_APICALL فراغ GL_APIENTRY gl_Dispatch_Compute_غیرمستقیم (GLintptr غیرمستقیم);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Arrays_غیرمستقیم (GLenum نما, ثابت فراغ *غیرمستقیم);
GL_APICALL فراغ GL_APIENTRY gl_Draw_Elements_غیرمستقیم (GLenum نما, GLenum type, ثابت فراغ *غیرمستقیم);
GL_APICALL فراغ GL_APIENTRY glFramebufferParameteri (GLenum هدف, GLenum pname, GLint param);
GL_APICALL فراغ GL_APIENTRY glGetFramebufferParameteriv (GLenum هدف, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY gl_Get_برنامه_Interfaceiv (GLuint برنامه, GLenum برنامه_Interface, GLenum pname, GLint *params);
GL_APICALL GLuint GL_APIENTRY gl_Get_برنامه_Resource_شاخص (GLuint برنامه, GLenum برنامه_Interface, ثابت GLchar *name);
GL_APICALL فراغ GL_APIENTRY gl_Get_برنامه_Resource_Name (GLuint برنامه, GLenum برنامه_Interface, GLuint شاخص, GLsizei buf_اندازه, GLsizei *درازی, GLchar *name);
GL_APICALL فراغ GL_APIENTRY gl_Get_برنامه_Resourceiv (GLuint برنامه, GLenum برنامه_Interface, GLuint شاخص, GLsizei prop_شمار, ثابت GLenum *props, GLsizei شمار, GLsizei *درازی, GLint *params);
GL_APICALL GLint GL_APIENTRY gl_Get_برنامه_Resource_Location (GLuint برنامه, GLenum برنامه_Interface, ثابت GLchar *name);
GL_APICALL فراغ GL_APIENTRY gl_Use_برنامه_Stages (GLuint pipeline, GLbitfield stages, GLuint برنامه);
GL_APICALL فراغ GL_APIENTRY gl_فعال_Shader_برنامه (GLuint pipeline, GLuint برنامه);
GL_APICALL GLuint GL_APIENTRY glCreateShaderProgramv (GLenum type, GLsizei شمار, ثابت GLchar *ثابت*رشتهها);
GL_APICALL فراغ GL_APIENTRY gl_Bind_برنامه_Pipeline (GLuint pipeline);
GL_APICALL فراغ GL_APIENTRY gl_Delete_برنامه_Pipelines (GLsizei n, ثابت GLuint *pipelines);
GL_APICALL فراغ GL_APIENTRY gl_Gen_برنامه_Pipelines (GLsizei n, GLuint *pipelines);
GL_APICALL GLboolean GL_APIENTRY gl_Is_برنامه_Pipeline (GLuint pipeline);
GL_APICALL فراغ GL_APIENTRY gl_Get_برنامه_Pipelineiv (GLuint pipeline, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform1i (GLuint برنامه, GLint location, GLint v0);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform2i (GLuint برنامه, GLint location, GLint v0, GLint v1);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform3i (GLuint برنامه, GLint location, GLint v0, GLint v1, GLint v2);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform4i (GLuint برنامه, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform1ui (GLuint برنامه, GLint location, GLuint v0);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform2ui (GLuint برنامه, GLint location, GLuint v0, GLuint v1);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform3ui (GLuint برنامه, GLint location, GLuint v0, GLuint v1, GLuint v2);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform4ui (GLuint برنامه, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform1f (GLuint برنامه, GLint location, GLfloat v0);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform2f (GLuint برنامه, GLint location, GLfloat v0, GLfloat v1);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform3f (GLuint برنامه, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform4f (GLuint برنامه, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform1iv (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLint *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform2iv (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLint *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform3iv (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLint *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform4iv (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLint *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform1uiv (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLuint *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform2uiv (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLuint *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform3uiv (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLuint *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform4uiv (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLuint *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform1fv (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform2fv (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform3fv (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_Uniform4fv (GLuint برنامه, GLint location, GLsizei شمار, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_یکنواخت_Matrix2fv (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_یکنواخت_Matrix3fv (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_یکنواخت_Matrix4fv (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_یکنواخت_Matrix2x3fv (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_یکنواخت_Matrix3x2fv (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_یکنواخت_Matrix2x4fv (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_یکنواخت_Matrix4x2fv (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_یکنواخت_Matrix3x4fv (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_برنامه_یکنواخت_Matrix4x3fv (GLuint برنامه, GLint location, GLsizei شمار, GLboolean transpose, ثابت GLfloat *مقدار);
GL_APICALL فراغ GL_APIENTRY gl_Validate_برنامه_Pipeline (GLuint pipeline);
GL_APICALL فراغ GL_APIENTRY gl_Get_برنامه_Pipeline_Info_Log (GLuint pipeline, GLsizei buf_اندازه, GLsizei *درازی, GLchar *infoLog);
GL_APICALL فراغ GL_APIENTRY glBindImageTexture (GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
GL_APICALL فراغ GL_APIENTRY glGetBooleani_v (GLenum هدف, GLuint شاخص, GLboolean *داده);
GL_APICALL فراغ GL_APIENTRY gl_حافظه_Barrier (GLbitfield barriers);
GL_APICALL فراغ GL_APIENTRY gl_حافظه_Barrier_By_Region (GLbitfield barriers);
GL_APICALL فراغ GL_APIENTRY glTexStorage2DMultisample (GLenum هدف, GLsizei samples, GLenum internalformat, GLsizei عرض, GLsizei ارتفاع, GLboolean fixedsamplelocations);
GL_APICALL فراغ GL_APIENTRY glGetMultisamplefv (GLenum pname, GLuint شاخص, GLfloat *val);
GL_APICALL فراغ GL_APIENTRY glSampleMaski (GLuint ماسک_عدد, GLbitfield ماسک);
GL_APICALL فراغ GL_APIENTRY glGetTexLevelParameteriv (GLenum هدف, GLint level, GLenum pname, GLint *params);
GL_APICALL فراغ GL_APIENTRY glGetTexLevelParameterfv (GLenum هدف, GLint level, GLenum pname, GLfloat *params);
GL_APICALL فراغ GL_APIENTRY gl_Bind_رأس_میانگیر (GLuint bindingindex, GLuint میانگیر_2, GLintptr جابه_جایی_2, GLsizei stride);
GL_APICALL فراغ GL_APIENTRY gl_رأس_Attrib_Format (GLuint attribindex, GLint اندازه, GLenum type, GLboolean normalized, GLuint relativeoffset);
GL_APICALL فراغ GL_APIENTRY gl_رأس_Attrib_IFormat (GLuint attribindex, GLint اندازه, GLenum type, GLuint relativeoffset);
GL_APICALL فراغ GL_APIENTRY gl_رأس_Attrib_Binding (GLuint attribindex, GLuint bindingindex);
GL_APICALL فراغ GL_APIENTRY gl_رأس_Binding_مقسوم_علیه (GLuint bindingindex, GLuint مقسوم_علیه);
#پایان_اگر
#پایان_اگر /* GL_ES_VERSION_3_1 */

#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر
