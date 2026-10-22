#اگر_تعریف_نشده __gles2_gl2_h_
#تعریف_کن __gles2_gl2_h_ 1

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

#ضمن <GLES2/gl2platform.h>

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
 * Versions considered: 2\.[0-9]
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

#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر
