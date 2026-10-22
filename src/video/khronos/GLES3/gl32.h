#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __gles2_gl32_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ __gles2_gl32_h_ 1

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ

/*
** Copyright 2013-2026 The Khronos Group Inc.
** SPDX-License-Identifier: MIT
**
** This header is generated from the Khronos OpenGL / OpenGL ES XML
** API Registry. The current version of the Registry, generator scripts
** used to make the header, and the header can be found at
**   https://github.com/KhronosGroup/OpenGL-Registry
*/

#ਅਨ੍ਤਰ੍ਭਾਵ <GLES3/gl3platform.h>

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_APIENTRYP
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_APIENTRYP GL_APIENTRY*
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_GLES_PROTOTYPES
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_GLES_PROTOTYPES 1
#ਜੇ_ਅੰਤ

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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_ES_ਸੰਸਕਰਣ_2_0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ES_ਸੰਸਕਰਣ_2_0 1
#ਅਨ੍ਤਰ੍ਭਾਵ <KHR/khrplatform.h>
ਕਿਸਮਪਰਿਭਾਸ਼ਾ khronos_int8_t GLbyte;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ khronos_float_t GLclampf;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ khronos_int32_t GLfixed;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ khronos_int16_t GLshort;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ khronos_uint16_t GLushort;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ GLvoid;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ __GLsync *GLsync;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ khronos_int64_t GLint64;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ khronos_uint64_t GLuint64;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ GLenum;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ GLuint;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਅੱਖਰ GLchar;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ khronos_float_t GLfloat;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ khronos_ssize_t GLsizeiptr;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ khronos_intptr_t GLintptr;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ GLbitfield;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੂਰਨ GLint;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ GLboolean;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੂਰਨ GLsizei;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ khronos_uint8_t GLubyte;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਡੂੰਘਾਈ_ਬਫਰ_ਦੋਆਧਾਰੀ_ਅੰਕ               0x00000100
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STENCIL_ਬਫਰ_ਦੋਆਧਾਰੀ_ਅੰਕ             0x00000400
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ਬਫਰ_ਦੋਆਧਾਰੀ_ਅੰਕ               0x00004000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FALSE                          0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TRUE                           1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_POINTS                         0x0000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸਤਰਾਂ                          0x0001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸਤਰ_LOOP                      0x0002
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸਤਰ_STRIP                     0x0003
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TRIANGLES                      0x0004
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TRIANGLE_STRIP                 0x0005
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TRIANGLE_FAN                   0x0006
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ZERO                           0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ONE                            1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SRC_COLOR                      0x0300
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ONE_MINUS_SRC_COLOR            0x0301
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SRC_ALPHA                      0x0302
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ONE_MINUS_SRC_ALPHA            0x0303
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DST_ALPHA                      0x0304
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ONE_MINUS_DST_ALPHA            0x0305
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DST_COLOR                      0x0306
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ONE_MINUS_DST_COLOR            0x0307
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SRC_ALPHA_SATURATE             0x0308
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FUNC_ਜੋੜੋ                       0x8006
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_BLEND_EQUATION                 0x8009
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_BLEND_EQUATION_RGB             0x8009
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_BLEND_EQUATION_ALPHA           0x883D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FUNC_ਘਟਾਓ                  0x800A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FUNC_ਉਲਟ_ਘਟਾਓ          0x800B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_BLEND_DST_RGB                  0x80C8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_BLEND_SRC_RGB                  0x80C9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_BLEND_DST_ALPHA                0x80CA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_BLEND_SRC_ALPHA                0x80CB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_CONSTANT_COLOR                 0x8001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ONE_MINUS_CONSTANT_COLOR       0x8002
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_CONSTANT_ALPHA                 0x8003
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ONE_MINUS_CONSTANT_ALPHA       0x8004
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_BLEND_COLOR                    0x8005
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ARRAY_ਬਫਰ                   0x8892
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ELEMENT_ARRAY_ਬਫਰ           0x8893
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ARRAY_ਬਫਰ_BINDING           0x8894
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ELEMENT_ARRAY_ਬਫਰ_BINDING   0x8895
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਧਾਰਾ_DRAW                    0x88E0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STATIC_DRAW                    0x88E4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DYNAMIC_DRAW                   0x88E8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਬਫਰ_ਮਾਪ                    0x8764
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਬਫਰ_USAGE                   0x8765
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_CURRENT_ਸ਼ੀਰਸ਼_ATTRIB          0x8626
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRONT                          0x0404
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਪਿੱਠ                           0x0405
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRONT_AND_ਪਿੱਠ                 0x0408
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_2D                     0x0DE1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_CULL_FACE                      0x0B44
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_BLEND                          0x0BE2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DITHER                         0x0BD0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STENCIL_TEST                   0x0B90
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਡੂੰਘਾਈ_TEST                     0x0B71
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SCISSOR_TEST                   0x0C11
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_POLYGON_ਵਿੱਥ_FILL            0x8037
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SAMPLE_ALPHA_ਮੰਜ਼ਿਲ_COVERAGE       0x809E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SAMPLE_COVERAGE                0x80A0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_NO_ERROR                       0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_INVALID_ENUM                   0x0500
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_INVALID_ਮੁੱਲ                  0x0501
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_INVALID_OPERATION              0x0502
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਬਾਹਰਲਾ_ਦਾ_ਸਮ੍ਰਿਤੀ                  0x0505
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_CW                             0x0900
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_CCW                            0x0901
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸਤਰ_ਚੌੜਾਈ                     0x0B21
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ALIASED_ਬਿੰਦੂ_ਮਾਪ_RANGE       0x846D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ALIASED_ਸਤਰ_ਚੌੜਾਈ_RANGE       0x846E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_CULL_FACE_ਬਹੁਲਕ                 0x0B45
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRONT_FACE                     0x0B46
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਡੂੰਘਾਈ_RANGE                    0x0B70
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਡੂੰਘਾਈ_WRITEMASK                0x0B72
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਡੂੰਘਾਈ_CLEAR_ਮੁੱਲ              0x0B73
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਡੂੰਘਾਈ_FUNC                     0x0B74
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STENCIL_CLEAR_ਮੁੱਲ            0x0B91
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STENCIL_FUNC                   0x0B92
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STENCIL_FAIL                   0x0B94
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STENCIL_PASS_ਡੂੰਘਾਈ_FAIL        0x0B95
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STENCIL_PASS_ਡੂੰਘਾਈ_PASS        0x0B96
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STENCIL_REF                    0x0B97
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STENCIL_ਮੁੱਲ_ਨਕਾਬ             0x0B93
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STENCIL_WRITEMASK              0x0B98
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STENCIL_ਪਿੱਠ_FUNC              0x8800
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STENCIL_ਪਿੱਠ_FAIL              0x8801
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STENCIL_ਪਿੱਠ_PASS_ਡੂੰਘਾਈ_FAIL   0x8802
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STENCIL_ਪਿੱਠ_PASS_ਡੂੰਘਾਈ_PASS   0x8803
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STENCIL_ਪਿੱਠ_REF               0x8CA3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STENCIL_ਪਿੱਠ_ਮੁੱਲ_ਨਕਾਬ        0x8CA4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STENCIL_ਪਿੱਠ_WRITEMASK         0x8CA5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_VIEWPORT                       0x0BA2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SCISSOR_BOX                    0x0C10
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_CLEAR_ਮੁੱਲ              0x0C22
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_WRITEMASK                0x0C23
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNPACK_ALIGNMENT               0x0CF5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_PACK_ALIGNMENT                 0x0D05
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_TEXTURE_ਮਾਪ               0x0D33
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_VIEWPORT_DIMS              0x0D3A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SUBPIXEL_ਬਿੱਟ                  0x0D50
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RED_ਬਿੱਟ                       0x0D52
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_GREEN_ਬਿੱਟ                     0x0D53
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_BLUE_ਬਿੱਟ                      0x0D54
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ALPHA_ਬਿੱਟ                     0x0D55
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਡੂੰਘਾਈ_ਬਿੱਟ                     0x0D56
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STENCIL_ਬਿੱਟ                   0x0D57
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_POLYGON_ਵਿੱਥ_UNITS           0x2A00
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_POLYGON_ਵਿੱਥ_ਗੁਣਕ          0x8038
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_BINDING_2D             0x8069
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SAMPLE_BUFFERS                 0x80A8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SAMPLES                        0x80A9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SAMPLE_COVERAGE_ਮੁੱਲ          0x80AA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SAMPLE_COVERAGE_INVERT         0x80AB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਅੰਕ_COMPRESSED_TEXTURE_FORMATS 0x86A2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_TEXTURE_FORMATS     0x86A3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DONT_CARE                      0x1100
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FASTEST                        0x1101
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_NICEST                         0x1102
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_GENERATE_MIPMAP_HINT           0x8192
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_BYTE                           0x1400
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNED_BYTE                  0x1401
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SHORT                          0x1402
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNED_SHORT                 0x1403
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_INT                            0x1404
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNED_INT                   0x1405
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FLOAT                          0x1406
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FIXED                          0x140C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਡੂੰਘਾਈ_COMPONENT                0x1902
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ALPHA                          0x1906
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGB                            0x1907
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGBA                           0x1908
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_LUMINANCE                      0x1909
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_LUMINANCE_ALPHA                0x190A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNED_SHORT_4_4_4_4         0x8033
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNED_SHORT_5_5_5_1         0x8034
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNED_SHORT_5_6_5           0x8363
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAGMENT_SHADER                0x8B30
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸ਼ੀਰਸ਼_SHADER                  0x8B31
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_ਸ਼ੀਰਸ਼_ATTRIBS             0x8869
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_ਸ਼ੀਰਸ਼_ਇਕਸਾਰ_VECTORS     0x8DFB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_VARYING_VECTORS            0x8DFC
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 0x8B4D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_ਸ਼ੀਰਸ਼_TEXTURE_IMAGE_UNITS 0x8B4C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_TEXTURE_IMAGE_UNITS        0x8872
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_FRAGMENT_ਇਕਸਾਰ_VECTORS   0x8DFD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SHADER_TYPE                    0x8B4F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DELETE_ਸਥਿਤੀ                  0x8B80
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_LINK_ਸਥਿਤੀ                    0x8B82
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_VALIDATE_ਸਥਿਤੀ                0x8B83
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ATTACHED_SHADERS               0x8B85
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸਰਗਰਮ_UNIFORMS                0x8B86
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸਰਗਰਮ_ਇਕਸਾਰ_MAX_ਲੰਮਾਈ      0x8B87
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸਰਗਰਮ_ਗੁਣ              0x8B89
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸਰਗਰਮ_ATTRIBUTE_MAX_ਲੰਮਾਈ    0x8B8A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SHADING_LANGUAGE_ਸੰਸਕਰਣ       0x8B8C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_CURRENT_ਪ੍ਰੋਗਰਾਮ                0x8B8D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_NEVER                          0x0200
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_LESS                           0x0201
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_EQUAL                          0x0202
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_LEQUAL                         0x0203
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_GREATER                        0x0204
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_NOTEQUAL                       0x0205
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_GEQUAL                         0x0206
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ALWAYS                         0x0207
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_KEEP                           0x1E00
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_REPLACE                        0x1E01
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_INCR                           0x1E02
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DECR                           0x1E03
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_INVERT                         0x150A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_INCR_WRAP                      0x8507
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DECR_WRAP                      0x8508
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_VENDOR                         0x1F00
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RENDERER                       0x1F01
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸੰਸਕਰਣ                        0x1F02
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_EXTENSIONS                     0x1F03
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸਭ_ਤੋਂ_ਨੇੜੇ                        0x2600
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਰੇਖਿਕ                         0x2601
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸਭ_ਤੋਂ_ਨੇੜੇ_MIPMAP_ਸਭ_ਤੋਂ_ਨੇੜੇ         0x2700
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਰੇਖਿਕ_MIPMAP_ਸਭ_ਤੋਂ_ਨੇੜੇ          0x2701
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸਭ_ਤੋਂ_ਨੇੜੇ_MIPMAP_ਰੇਖਿਕ          0x2702
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਰੇਖਿਕ_MIPMAP_ਰੇਖਿਕ           0x2703
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_MAG_FILTER             0x2800
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_MIN_FILTER             0x2801
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_WRAP_S                 0x2802
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_WRAP_T                 0x2803
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE                        0x1702
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_CUBE_MAP               0x8513
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_BINDING_CUBE_MAP       0x8514
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_CUBE_MAP_ਸਕਾਰਾਤਮਕ_X    0x8515
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_CUBE_MAP_NEGATIVE_X    0x8516
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_CUBE_MAP_ਸਕਾਰਾਤਮਕ_Y    0x8517
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_CUBE_MAP_NEGATIVE_Y    0x8518
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_CUBE_MAP_ਸਕਾਰਾਤਮਕ_Z    0x8519
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_CUBE_MAP_NEGATIVE_Z    0x851A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_CUBE_MAP_TEXTURE_ਮਾਪ      0x851C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE0                       0x84C0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE1                       0x84C1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE2                       0x84C2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE3                       0x84C3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE4                       0x84C4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE5                       0x84C5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE6                       0x84C6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE7                       0x84C7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE8                       0x84C8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE9                       0x84C9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE10                      0x84CA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE11                      0x84CB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE12                      0x84CC
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE13                      0x84CD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE14                      0x84CE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE15                      0x84CF
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE16                      0x84D0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE17                      0x84D1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE18                      0x84D2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE19                      0x84D3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE20                      0x84D4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE21                      0x84D5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE22                      0x84D6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE23                      0x84D7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE24                      0x84D8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE25                      0x84D9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE26                      0x84DA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE27                      0x84DB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE28                      0x84DC
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE29                      0x84DD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE30                      0x84DE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE31                      0x84DF
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸਰਗਰਮ_TEXTURE                 0x84E0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_REPEAT                         0x2901
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_CLAMP_ਮੰਜ਼ਿਲ_ਕਿਨਾਰਾ                  0x812F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MIRRORED_REPEAT                0x8370
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FLOAT_VEC2                     0x8B50
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FLOAT_VEC3                     0x8B51
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FLOAT_VEC4                     0x8B52
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_INT_VEC2                       0x8B53
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_INT_VEC3                       0x8B54
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_INT_VEC4                       0x8B55
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_BOOL                           0x8B56
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_BOOL_VEC2                      0x8B57
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_BOOL_VEC3                      0x8B58
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_BOOL_VEC4                      0x8B59
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FLOAT_MAT2                     0x8B5A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FLOAT_MAT3                     0x8B5B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FLOAT_MAT4                     0x8B5C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SAMPLER_2D                     0x8B5E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SAMPLER_CUBE                   0x8B60
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸ਼ੀਰਸ਼_ATTRIB_ARRAY_ENABLED    0x8622
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸ਼ੀਰਸ਼_ATTRIB_ARRAY_ਮਾਪ       0x8623
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸ਼ੀਰਸ਼_ATTRIB_ARRAY_STRIDE     0x8624
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸ਼ੀਰਸ਼_ATTRIB_ARRAY_TYPE       0x8625
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸ਼ੀਰਸ਼_ATTRIB_ARRAY_NORMALIZED 0x886A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸ਼ੀਰਸ਼_ATTRIB_ARRAY_ਸੂਚਕ    0x8645
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸ਼ੀਰਸ਼_ATTRIB_ARRAY_ਬਫਰ_BINDING 0x889F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_IMPLEMENTATION_COLOR_READ_TYPE 0x8B9A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_IMPLEMENTATION_COLOR_READ_FORMAT 0x8B9B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPILE_ਸਥਿਤੀ                 0x8B81
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_INFO_LOG_ਲੰਮਾਈ                0x8B84
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SHADER_ਸਰੋਤ_ਲੰਮਾਈ           0x8B88
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SHADER_COMPILER                0x8DFA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SHADER_ਦੁਆਧਾਰੀ_FORMATS          0x8DF8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਅੰਕ_SHADER_ਦੁਆਧਾਰੀ_FORMATS      0x8DF9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਨੀਵਾਂ_FLOAT                      0x8DF0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MEDIUM_FLOAT                   0x8DF1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਉੱਚਾ_FLOAT                     0x8DF2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਨੀਵਾਂ_INT                        0x8DF3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MEDIUM_INT                     0x8DF4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਉੱਚਾ_INT                       0x8DF5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER                    0x8D40
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RENDERBUFFER                   0x8D41
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGBA4                          0x8056
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGB5_A1                        0x8057
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGB565                         0x8D62
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਡੂੰਘਾਈ_COMPONENT16              0x81A5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STENCIL_INDEX8                 0x8D48
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RENDERBUFFER_ਚੌੜਾਈ             0x8D42
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RENDERBUFFER_ਉਚਾਈ            0x8D43
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RENDERBUFFER_ਅੰਦਰੂਨੀ_FORMAT   0x8D44
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RENDERBUFFER_RED_ਮਾਪ          0x8D50
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RENDERBUFFER_GREEN_ਮਾਪ        0x8D51
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RENDERBUFFER_BLUE_ਮਾਪ         0x8D52
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RENDERBUFFER_ALPHA_ਮਾਪ        0x8D53
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RENDERBUFFER_ਡੂੰਘਾਈ_ਮਾਪ        0x8D54
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RENDERBUFFER_STENCIL_ਮਾਪ      0x8D55
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE 0x8CD0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME 0x8CD1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL 0x8CD2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE 0x8CD3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ATTACHMENT0              0x8CE0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਡੂੰਘਾਈ_ATTACHMENT               0x8D00
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STENCIL_ATTACHMENT             0x8D20
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_NONE                           0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_COMPLETE           0x8CD5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT 0x8CD6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 0x8CD7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS 0x8CD9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_UNSUPPORTED        0x8CDD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_BINDING            0x8CA6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RENDERBUFFER_BINDING           0x8CA7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_RENDERBUFFER_ਮਾਪ          0x84E8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_INVALID_FRAMEBUFFER_OPERATION  0x0506
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLACTIVETEXTUREPROC) (GLenum texture);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLATTACHSHADERPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLuint shader);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLBINDATTRIBLOCATIONPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLuint ਸੂਚਕਾਂਕ, ਅਚਲ GLchar *name);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLBINDBUFFERPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLuint ਬਫਰ_2);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLBINDFRAMEBUFFERPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLuint framebuffer);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLBINDRENDERBUFFERPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLuint renderbuffer);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLBINDTEXTUREPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLuint texture);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLBLENDCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLBLENDEQUATIONPROC) (GLenum ਬਹੁਲਕ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEPROC) (GLenum ਬਹੁਲਕ_RGB, GLenum ਬਹੁਲਕ_Alpha);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLBLENDFUNCPROC) (GLenum sfactor, GLenum dfactor);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEPROC) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLBUFFERDATAPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLsizeiptr ਮਾਪ, ਅਚਲ ਖਾਲੀ *ਅੰਕੜੇ, GLenum usage);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLBUFFERSUBDATAPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLintptr ਵਿੱਥ_2, GLsizeiptr ਮਾਪ, ਅਚਲ ਖਾਲੀ *ਅੰਕੜੇ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLenum (GL_APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSPROC) (GLenum ਨਿਸ਼ਾਨਾ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLCLEARPROC) (GLbitfield ਨਕਾਬ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLCLEARCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLCLEARDEPTHFPROC) (GLfloat d);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLCLEARSTENCILPROC) (GLint s);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLCOLORMASKPROC) (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLCOMPILESHADERPROC) (GLuint shader);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLCOMPRESSEDTEXIMAGE2DPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLint level, GLenum internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLint border, GLsizei image_ਮਾਪ, ਅਚਲ ਖਾਲੀ *ਅੰਕੜੇ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLint level, GLint xoffset, GLint yoffset, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLenum format, GLsizei image_ਮਾਪ, ਅਚਲ ਖਾਲੀ *ਅੰਕੜੇ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLCOPYTEXIMAGE2DPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLint border);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLCOPYTEXSUBIMAGE2DPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLuint (GL_APIENTRYP PFNGLCREATEPROGRAMPROC) (ਖਾਲੀ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLuint (GL_APIENTRYP PFNGLCREATESHADERPROC) (GLenum type);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLCULLFACEPROC) (GLenum ਬਹੁਲਕ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDELETEBUFFERSPROC) (GLsizei n, ਅਚਲ GLuint *buffers);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDELETEFRAMEBUFFERSPROC) (GLsizei n, ਅਚਲ GLuint *framebuffers);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDELETEPROGRAMPROC) (GLuint ਪ੍ਰੋਗਰਾਮ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDELETERENDERBUFFERSPROC) (GLsizei n, ਅਚਲ GLuint *renderbuffers);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDELETESHADERPROC) (GLuint shader);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDELETETEXTURESPROC) (GLsizei n, ਅਚਲ GLuint *textures);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDEPTHFUNCPROC) (GLenum func);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDEPTHMASKPROC) (GLboolean flag);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDEPTHRANGEFPROC) (GLfloat n, GLfloat f);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDETACHSHADERPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLuint shader);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDISABLEPROC) (GLenum cap);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint ਸੂਚਕਾਂਕ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDRAWARRAYSPROC) (GLenum ਬਹੁਲਕ, GLint ਪਹਿਲਾ, GLsizei ਗਿਣਤੀ_2);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDRAWELEMENTSPROC) (GLenum ਬਹੁਲਕ, GLsizei ਗਿਣਤੀ_2, GLenum type, ਅਚਲ ਖਾਲੀ *indices);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLENABLEPROC) (GLenum cap);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint ਸੂਚਕਾਂਕ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLFINISHPROC) (ਖਾਲੀ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLFLUSHPROC) (ਖਾਲੀ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFERPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLFRONTFACEPROC) (GLenum ਬਹੁਲਕ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGENBUFFERSPROC) (GLsizei n, GLuint *buffers);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGENERATEMIPMAPPROC) (GLenum ਨਿਸ਼ਾਨਾ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGENFRAMEBUFFERSPROC) (GLsizei n, GLuint *framebuffers);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGENRENDERBUFFERSPROC) (GLsizei n, GLuint *renderbuffers);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGENTEXTURESPROC) (GLsizei n, GLuint *textures);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETACTIVEATTRIBPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLuint ਸੂਚਕਾਂਕ, GLsizei buf_ਮਾਪ, GLsizei *ਲੰਮਾਈ, GLint *ਮਾਪ, GLenum *type, GLchar *name);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETACTIVEUNIFORMPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLuint ਸੂਚਕਾਂਕ, GLsizei buf_ਮਾਪ, GLsizei *ਲੰਮਾਈ, GLint *ਮਾਪ, GLenum *type, GLchar *name);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETATTACHEDSHADERSPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLsizei max_ਗਿਣਤੀ, GLsizei *ਗਿਣਤੀ_2, GLuint *shaders);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLint (GL_APIENTRYP PFNGLGETATTRIBLOCATIONPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, ਅਚਲ GLchar *name);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETBOOLEANVPROC) (GLenum pname, GLboolean *ਅੰਕੜੇ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETBUFFERPARAMETERIVPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLenum (GL_APIENTRYP PFNGLGETERRORPROC) (ਖਾਲੀ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETFLOATVPROC) (GLenum pname, GLfloat *ਅੰਕੜੇ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum attachment, GLenum pname, GLint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETINTEGERVPROC) (GLenum pname, GLint *ਅੰਕੜੇ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETPROGRAMIVPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLenum pname, GLint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETPROGRAMINFOLOGPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLsizei buf_ਮਾਪ, GLsizei *ਲੰਮਾਈ, GLchar *infoLog);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei buf_ਮਾਪ, GLsizei *ਲੰਮਾਈ, GLchar *infoLog);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETSHADERPRECISIONFORMATPROC) (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETSHADERSOURCEPROC) (GLuint shader, GLsizei buf_ਮਾਪ, GLsizei *ਲੰਮਾਈ, GLchar *ਸਰੋਤ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਅਚਲ GLubyte *(GL_APIENTRYP PFNGLGETSTRINGPROC) (GLenum name);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETTEXPARAMETERFVPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLfloat *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETTEXPARAMETERIVPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETUNIFORMFVPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLfloat *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETUNIFORMIVPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLint (GL_APIENTRYP PFNGLGETUNIFORMLOCATIONPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, ਅਚਲ GLchar *name);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETVERTEXATTRIBFVPROC) (GLuint ਸੂਚਕਾਂਕ, GLenum pname, GLfloat *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETVERTEXATTRIBIVPROC) (GLuint ਸੂਚਕਾਂਕ, GLenum pname, GLint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETVERTEXATTRIBPOINTERVPROC) (GLuint ਸੂਚਕਾਂਕ, GLenum pname, ਖਾਲੀ **ਸੂਚਕ_2);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLHINTPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum ਬਹੁਲਕ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLboolean (GL_APIENTRYP PFNGLISBUFFERPROC) (GLuint ਬਫਰ_2);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLboolean (GL_APIENTRYP PFNGLISENABLEDPROC) (GLenum cap);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLboolean (GL_APIENTRYP PFNGLISFRAMEBUFFERPROC) (GLuint framebuffer);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLboolean (GL_APIENTRYP PFNGLISPROGRAMPROC) (GLuint ਪ੍ਰੋਗਰਾਮ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLboolean (GL_APIENTRYP PFNGLISRENDERBUFFERPROC) (GLuint renderbuffer);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLboolean (GL_APIENTRYP PFNGLISSHADERPROC) (GLuint shader);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLboolean (GL_APIENTRYP PFNGLISTEXTUREPROC) (GLuint texture);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLLINEWIDTHPROC) (GLfloat ਚੌੜਾਈ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLLINKPROGRAMPROC) (GLuint ਪ੍ਰੋਗਰਾਮ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPIXELSTOREIPROC) (GLenum pname, GLint param);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPOLYGONOFFSETPROC) (GLfloat ਗੁਣਕ, GLfloat units);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLREADPIXELSPROC) (GLint x, GLint y, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLenum format, GLenum type, ਖਾਲੀ *pixels);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLRELEASESHADERCOMPILERPROC) (ਖਾਲੀ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLSAMPLECOVERAGEPROC) (GLfloat ਮੁੱਲ, GLboolean invert);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLSCISSORPROC) (GLint x, GLint y, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLSHADERBINARYPROC) (GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLuint *shaders, GLenum ਦੁਆਧਾਰੀ_Format, ਅਚਲ ਖਾਲੀ *ਦੁਆਧਾਰੀ, GLsizei ਲੰਮਾਈ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLchar *ਅਚਲ*string, ਅਚਲ GLint *ਲੰਮਾਈ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLSTENCILFUNCPROC) (GLenum func, GLint ref, GLuint ਨਕਾਬ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLSTENCILFUNCSEPARATEPROC) (GLenum face, GLenum func, GLint ref, GLuint ਨਕਾਬ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLSTENCILMASKPROC) (GLuint ਨਕਾਬ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLSTENCILMASKSEPARATEPROC) (GLenum face, GLuint ਨਕਾਬ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLSTENCILOPPROC) (GLenum fail, GLenum zfail, GLenum zpass);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLSTENCILOPSEPARATEPROC) (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLTEXIMAGE2DPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLint level, GLint internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLint border, GLenum format, GLenum type, ਅਚਲ ਖਾਲੀ *pixels);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLTEXPARAMETERFPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLfloat param);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLTEXPARAMETERFVPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, ਅਚਲ GLfloat *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLTEXPARAMETERIPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLint param);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLTEXPARAMETERIVPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, ਅਚਲ GLint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLTEXSUBIMAGE2DPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLint level, GLint xoffset, GLint yoffset, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLenum format, GLenum type, ਅਚਲ ਖਾਲੀ *pixels);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUNIFORM1FPROC) (GLint location, GLfloat v0);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUNIFORM1FVPROC) (GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLfloat *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUNIFORM1IPROC) (GLint location, GLint v0);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUNIFORM1IVPROC) (GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLint *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUNIFORM2FPROC) (GLint location, GLfloat v0, GLfloat v1);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUNIFORM2FVPROC) (GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLfloat *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUNIFORM2IPROC) (GLint location, GLint v0, GLint v1);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUNIFORM2IVPROC) (GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLint *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUNIFORM3FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUNIFORM3FVPROC) (GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLfloat *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUNIFORM3IPROC) (GLint location, GLint v0, GLint v1, GLint v2);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUNIFORM3IVPROC) (GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLint *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUNIFORM4FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUNIFORM4FVPROC) (GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLfloat *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUNIFORM4IPROC) (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUNIFORM4IVPROC) (GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLint *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUNIFORMMATRIX2FVPROC) (GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUNIFORMMATRIX3FVPROC) (GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUSEPROGRAMPROC) (GLuint ਪ੍ਰੋਗਰਾਮ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLVALIDATEPROGRAMPROC) (GLuint ਪ੍ਰੋਗਰਾਮ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLVERTEXATTRIB1FPROC) (GLuint ਸੂਚਕਾਂਕ, GLfloat x);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLVERTEXATTRIB1FVPROC) (GLuint ਸੂਚਕਾਂਕ, ਅਚਲ GLfloat *v);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLVERTEXATTRIB2FPROC) (GLuint ਸੂਚਕਾਂਕ, GLfloat x, GLfloat y);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLVERTEXATTRIB2FVPROC) (GLuint ਸੂਚਕਾਂਕ, ਅਚਲ GLfloat *v);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLVERTEXATTRIB3FPROC) (GLuint ਸੂਚਕਾਂਕ, GLfloat x, GLfloat y, GLfloat z);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLVERTEXATTRIB3FVPROC) (GLuint ਸੂਚਕਾਂਕ, ਅਚਲ GLfloat *v);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLVERTEXATTRIB4FPROC) (GLuint ਸੂਚਕਾਂਕ, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLVERTEXATTRIB4FVPROC) (GLuint ਸੂਚਕਾਂਕ, ਅਚਲ GLfloat *v);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC) (GLuint ਸੂਚਕਾਂਕ, GLint ਮਾਪ, GLenum type, GLboolean normalized, GLsizei stride, ਅਚਲ ਖਾਲੀ *ਸੂਚਕ_2);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLVIEWPORTPROC) (GLint x, GLint y, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ);
#ਜੇ GL_GLES_PROTOTYPES
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਸਰਗਰਮ_Texture (GLenum texture);
GL_APICALL ਖਾਲੀ GL_APIENTRY glAttachShader (GLuint ਪ੍ਰੋਗਰਾਮ, GLuint shader);
GL_APICALL ਖਾਲੀ GL_APIENTRY glBindAttribLocation (GLuint ਪ੍ਰੋਗਰਾਮ, GLuint ਸੂਚਕਾਂਕ, ਅਚਲ GLchar *name);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Bind_ਬਫਰ (GLenum ਨਿਸ਼ਾਨਾ, GLuint ਬਫਰ_2);
GL_APICALL ਖਾਲੀ GL_APIENTRY glBindFramebuffer (GLenum ਨਿਸ਼ਾਨਾ, GLuint framebuffer);
GL_APICALL ਖਾਲੀ GL_APIENTRY glBindRenderbuffer (GLenum ਨਿਸ਼ਾਨਾ, GLuint renderbuffer);
GL_APICALL ਖਾਲੀ GL_APIENTRY glBindTexture (GLenum ਨਿਸ਼ਾਨਾ, GLuint texture);
GL_APICALL ਖਾਲੀ GL_APIENTRY glBlendColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_APICALL ਖਾਲੀ GL_APIENTRY glBlendEquation (GLenum ਬਹੁਲਕ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glBlendEquationSeparate (GLenum ਬਹੁਲਕ_RGB, GLenum ਬਹੁਲਕ_Alpha);
GL_APICALL ਖਾਲੀ GL_APIENTRY glBlendFunc (GLenum sfactor, GLenum dfactor);
GL_APICALL ਖਾਲੀ GL_APIENTRY glBlendFuncSeparate (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਬਫਰ_ਅੰਕੜੇ (GLenum ਨਿਸ਼ਾਨਾ, GLsizeiptr ਮਾਪ, ਅਚਲ ਖਾਲੀ *ਅੰਕੜੇ, GLenum usage);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਬਫਰ_Sub_ਅੰਕੜੇ (GLenum ਨਿਸ਼ਾਨਾ, GLintptr ਵਿੱਥ_2, GLsizeiptr ਮਾਪ, ਅਚਲ ਖਾਲੀ *ਅੰਕੜੇ);
GL_APICALL GLenum GL_APIENTRY gl_Check_Framebuffer_ਸਥਿਤੀ (GLenum ਨਿਸ਼ਾਨਾ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glClear (GLbitfield ਨਕਾਬ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_APICALL ਖਾਲੀ GL_APIENTRY glClearDepthf (GLfloat d);
GL_APICALL ਖਾਲੀ GL_APIENTRY glClearStencil (GLint s);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Color_ਨਕਾਬ (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
GL_APICALL ਖਾਲੀ GL_APIENTRY glCompileShader (GLuint shader);
GL_APICALL ਖਾਲੀ GL_APIENTRY glCompressedTexImage2D (GLenum ਨਿਸ਼ਾਨਾ, GLint level, GLenum internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLint border, GLsizei image_ਮਾਪ, ਅਚਲ ਖਾਲੀ *ਅੰਕੜੇ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glCompressedTexSubImage2D (GLenum ਨਿਸ਼ਾਨਾ, GLint level, GLint xoffset, GLint yoffset, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLenum format, GLsizei image_ਮਾਪ, ਅਚਲ ਖਾਲੀ *ਅੰਕੜੇ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glCopyTexImage2D (GLenum ਨਿਸ਼ਾਨਾ, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLint border);
GL_APICALL ਖਾਲੀ GL_APIENTRY glCopyTexSubImage2D (GLenum ਨਿਸ਼ਾਨਾ, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ);
GL_APICALL GLuint GL_APIENTRY gl_Create_ਪ੍ਰੋਗਰਾਮ (ਖਾਲੀ);
GL_APICALL GLuint GL_APIENTRY glCreateShader (GLenum type);
GL_APICALL ਖਾਲੀ GL_APIENTRY glCullFace (GLenum ਬਹੁਲਕ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glDeleteBuffers (GLsizei n, ਅਚਲ GLuint *buffers);
GL_APICALL ਖਾਲੀ GL_APIENTRY glDeleteFramebuffers (GLsizei n, ਅਚਲ GLuint *framebuffers);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Delete_ਪ੍ਰੋਗਰਾਮ (GLuint ਪ੍ਰੋਗਰਾਮ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glDeleteRenderbuffers (GLsizei n, ਅਚਲ GLuint *renderbuffers);
GL_APICALL ਖਾਲੀ GL_APIENTRY glDeleteShader (GLuint shader);
GL_APICALL ਖਾਲੀ GL_APIENTRY glDeleteTextures (GLsizei n, ਅਚਲ GLuint *textures);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਡੂੰਘਾਈ_Func (GLenum func);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਡੂੰਘਾਈ_ਨਕਾਬ (GLboolean flag);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਡੂੰਘਾਈ_Rangef (GLfloat n, GLfloat f);
GL_APICALL ਖਾਲੀ GL_APIENTRY glDetachShader (GLuint ਪ੍ਰੋਗਰਾਮ, GLuint shader);
GL_APICALL ਖਾਲੀ GL_APIENTRY glDisable (GLenum cap);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Disable_ਸ਼ੀਰਸ਼_Attrib_Array (GLuint ਸੂਚਕਾਂਕ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glDrawArrays (GLenum ਬਹੁਲਕ, GLint ਪਹਿਲਾ, GLsizei ਗਿਣਤੀ_2);
GL_APICALL ਖਾਲੀ GL_APIENTRY glDrawElements (GLenum ਬਹੁਲਕ, GLsizei ਗਿਣਤੀ_2, GLenum type, ਅਚਲ ਖਾਲੀ *indices);
GL_APICALL ਖਾਲੀ GL_APIENTRY glEnable (GLenum cap);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Enable_ਸ਼ੀਰਸ਼_Attrib_Array (GLuint ਸੂਚਕਾਂਕ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਅੰਤ (ਖਾਲੀ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glFlush (ਖਾਲੀ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glFramebufferRenderbuffer (GLenum ਨਿਸ਼ਾਨਾ, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
GL_APICALL ਖਾਲੀ GL_APIENTRY glFramebufferTexture2D (GLenum ਨਿਸ਼ਾਨਾ, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GL_APICALL ਖਾਲੀ GL_APIENTRY glFrontFace (GLenum ਬਹੁਲਕ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGenBuffers (GLsizei n, GLuint *buffers);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGenerateMipmap (GLenum ਨਿਸ਼ਾਨਾ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGenFramebuffers (GLsizei n, GLuint *framebuffers);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGenRenderbuffers (GLsizei n, GLuint *renderbuffers);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGenTextures (GLsizei n, GLuint *textures);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Get_ਸਰਗਰਮ_Attrib (GLuint ਪ੍ਰੋਗਰਾਮ, GLuint ਸੂਚਕਾਂਕ, GLsizei buf_ਮਾਪ, GLsizei *ਲੰਮਾਈ, GLint *ਮਾਪ, GLenum *type, GLchar *name);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Get_ਸਰਗਰਮ_ਇਕਸਾਰ (GLuint ਪ੍ਰੋਗਰਾਮ, GLuint ਸੂਚਕਾਂਕ, GLsizei buf_ਮਾਪ, GLsizei *ਲੰਮਾਈ, GLint *ਮਾਪ, GLenum *type, GLchar *name);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetAttachedShaders (GLuint ਪ੍ਰੋਗਰਾਮ, GLsizei max_ਗਿਣਤੀ, GLsizei *ਗਿਣਤੀ_2, GLuint *shaders);
GL_APICALL GLint GL_APIENTRY glGetAttribLocation (GLuint ਪ੍ਰੋਗਰਾਮ, ਅਚਲ GLchar *name);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetBooleanv (GLenum pname, GLboolean *ਅੰਕੜੇ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Get_ਬਫਰ_Parameteriv (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLint *params);
GL_APICALL GLenum GL_APIENTRY glGetError (ਖਾਲੀ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetFloatv (GLenum pname, GLfloat *ਅੰਕੜੇ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetFramebufferAttachmentParameteriv (GLenum ਨਿਸ਼ਾਨਾ, GLenum attachment, GLenum pname, GLint *params);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetIntegerv (GLenum pname, GLint *ਅੰਕੜੇ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetProgramiv (GLuint ਪ੍ਰੋਗਰਾਮ, GLenum pname, GLint *params);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Get_ਪ੍ਰੋਗਰਾਮ_Info_Log (GLuint ਪ੍ਰੋਗਰਾਮ, GLsizei buf_ਮਾਪ, GLsizei *ਲੰਮਾਈ, GLchar *infoLog);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetRenderbufferParameteriv (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLint *params);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetShaderiv (GLuint shader, GLenum pname, GLint *params);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetShaderInfoLog (GLuint shader, GLsizei buf_ਮਾਪ, GLsizei *ਲੰਮਾਈ, GLchar *infoLog);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetShaderPrecisionFormat (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Get_Shader_ਸਰੋਤ (GLuint shader, GLsizei buf_ਮਾਪ, GLsizei *ਲੰਮਾਈ, GLchar *ਸਰੋਤ);
GL_APICALL ਅਚਲ GLubyte *GL_APIENTRY glGetString (GLenum name);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetTexParameterfv (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLfloat *params);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetTexParameteriv (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLint *params);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetUniformfv (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLfloat *params);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetUniformiv (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLint *params);
GL_APICALL GLint GL_APIENTRY gl_Get_ਇਕਸਾਰ_Location (GLuint ਪ੍ਰੋਗਰਾਮ, ਅਚਲ GLchar *name);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Get_ਸ਼ੀਰਸ਼_Attribfv (GLuint ਸੂਚਕਾਂਕ, GLenum pname, GLfloat *params);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Get_ਸ਼ੀਰਸ਼_Attribiv (GLuint ਸੂਚਕਾਂਕ, GLenum pname, GLint *params);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Get_ਸ਼ੀਰਸ਼_Attrib_Pointerv (GLuint ਸੂਚਕਾਂਕ, GLenum pname, ਖਾਲੀ **ਸੂਚਕ_2);
GL_APICALL ਖਾਲੀ GL_APIENTRY glHint (GLenum ਨਿਸ਼ਾਨਾ, GLenum ਬਹੁਲਕ);
GL_APICALL GLboolean GL_APIENTRY gl_Is_ਬਫਰ (GLuint ਬਫਰ_2);
GL_APICALL GLboolean GL_APIENTRY glIsEnabled (GLenum cap);
GL_APICALL GLboolean GL_APIENTRY glIsFramebuffer (GLuint framebuffer);
GL_APICALL GLboolean GL_APIENTRY gl_Is_ਪ੍ਰੋਗਰਾਮ (GLuint ਪ੍ਰੋਗਰਾਮ);
GL_APICALL GLboolean GL_APIENTRY glIsRenderbuffer (GLuint renderbuffer);
GL_APICALL GLboolean GL_APIENTRY glIsShader (GLuint shader);
GL_APICALL GLboolean GL_APIENTRY glIsTexture (GLuint texture);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਸਤਰ_ਚੌੜਾਈ (GLfloat ਚੌੜਾਈ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Link_ਪ੍ਰੋਗਰਾਮ (GLuint ਪ੍ਰੋਗਰਾਮ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glPixelStorei (GLenum pname, GLint param);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Polygon_ਵਿੱਥ (GLfloat ਗੁਣਕ, GLfloat units);
GL_APICALL ਖਾਲੀ GL_APIENTRY glReadPixels (GLint x, GLint y, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLenum format, GLenum type, ਖਾਲੀ *pixels);
GL_APICALL ਖਾਲੀ GL_APIENTRY glReleaseShaderCompiler (ਖਾਲੀ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glRenderbufferStorage (GLenum ਨਿਸ਼ਾਨਾ, GLenum internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glSampleCoverage (GLfloat ਮੁੱਲ, GLboolean invert);
GL_APICALL ਖਾਲੀ GL_APIENTRY glScissor (GLint x, GLint y, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Shader_ਦੁਆਧਾਰੀ (GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLuint *shaders, GLenum ਦੁਆਧਾਰੀ_Format, ਅਚਲ ਖਾਲੀ *ਦੁਆਧਾਰੀ, GLsizei ਲੰਮਾਈ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Shader_ਸਰੋਤ (GLuint shader, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLchar *ਅਚਲ*string, ਅਚਲ GLint *ਲੰਮਾਈ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glStencilFunc (GLenum func, GLint ref, GLuint ਨਕਾਬ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glStencilFuncSeparate (GLenum face, GLenum func, GLint ref, GLuint ਨਕਾਬ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Stencil_ਨਕਾਬ (GLuint ਨਕਾਬ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Stencil_ਨਕਾਬ_Separate (GLenum face, GLuint ਨਕਾਬ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glStencilOp (GLenum fail, GLenum zfail, GLenum zpass);
GL_APICALL ਖਾਲੀ GL_APIENTRY glStencilOpSeparate (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
GL_APICALL ਖਾਲੀ GL_APIENTRY glTexImage2D (GLenum ਨਿਸ਼ਾਨਾ, GLint level, GLint internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLint border, GLenum format, GLenum type, ਅਚਲ ਖਾਲੀ *pixels);
GL_APICALL ਖਾਲੀ GL_APIENTRY glTexParameterf (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLfloat param);
GL_APICALL ਖਾਲੀ GL_APIENTRY glTexParameterfv (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, ਅਚਲ GLfloat *params);
GL_APICALL ਖਾਲੀ GL_APIENTRY glTexParameteri (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLint param);
GL_APICALL ਖਾਲੀ GL_APIENTRY glTexParameteriv (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, ਅਚਲ GLint *params);
GL_APICALL ਖਾਲੀ GL_APIENTRY glTexSubImage2D (GLenum ਨਿਸ਼ਾਨਾ, GLint level, GLint xoffset, GLint yoffset, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLenum format, GLenum type, ਅਚਲ ਖਾਲੀ *pixels);
GL_APICALL ਖਾਲੀ GL_APIENTRY glUniform1f (GLint location, GLfloat v0);
GL_APICALL ਖਾਲੀ GL_APIENTRY glUniform1fv (GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLfloat *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glUniform1i (GLint location, GLint v0);
GL_APICALL ਖਾਲੀ GL_APIENTRY glUniform1iv (GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLint *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glUniform2f (GLint location, GLfloat v0, GLfloat v1);
GL_APICALL ਖਾਲੀ GL_APIENTRY glUniform2fv (GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLfloat *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glUniform2i (GLint location, GLint v0, GLint v1);
GL_APICALL ਖਾਲੀ GL_APIENTRY glUniform2iv (GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLint *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glUniform3f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
GL_APICALL ਖਾਲੀ GL_APIENTRY glUniform3fv (GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLfloat *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glUniform3i (GLint location, GLint v0, GLint v1, GLint v2);
GL_APICALL ਖਾਲੀ GL_APIENTRY glUniform3iv (GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLint *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glUniform4f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
GL_APICALL ਖਾਲੀ GL_APIENTRY glUniform4fv (GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLfloat *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glUniform4i (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
GL_APICALL ਖਾਲੀ GL_APIENTRY glUniform4iv (GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLint *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਇਕਸਾਰ_Matrix2fv (GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਇਕਸਾਰ_Matrix3fv (GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਇਕਸਾਰ_Matrix4fv (GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Use_ਪ੍ਰੋਗਰਾਮ (GLuint ਪ੍ਰੋਗਰਾਮ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Validate_ਪ੍ਰੋਗਰਾਮ (GLuint ਪ੍ਰੋਗਰਾਮ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਸ਼ੀਰਸ਼_Attrib1f (GLuint ਸੂਚਕਾਂਕ, GLfloat x);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਸ਼ੀਰਸ਼_Attrib1fv (GLuint ਸੂਚਕਾਂਕ, ਅਚਲ GLfloat *v);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਸ਼ੀਰਸ਼_Attrib2f (GLuint ਸੂਚਕਾਂਕ, GLfloat x, GLfloat y);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਸ਼ੀਰਸ਼_Attrib2fv (GLuint ਸੂਚਕਾਂਕ, ਅਚਲ GLfloat *v);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਸ਼ੀਰਸ਼_Attrib3f (GLuint ਸੂਚਕਾਂਕ, GLfloat x, GLfloat y, GLfloat z);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਸ਼ੀਰਸ਼_Attrib3fv (GLuint ਸੂਚਕਾਂਕ, ਅਚਲ GLfloat *v);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਸ਼ੀਰਸ਼_Attrib4f (GLuint ਸੂਚਕਾਂਕ, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਸ਼ੀਰਸ਼_Attrib4fv (GLuint ਸੂਚਕਾਂਕ, ਅਚਲ GLfloat *v);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਸ਼ੀਰਸ਼_Attrib_ਸੂਚਕ (GLuint ਸੂਚਕਾਂਕ, GLint ਮਾਪ, GLenum type, GLboolean normalized, GLsizei stride, ਅਚਲ ਖਾਲੀ *ਸੂਚਕ_2);
GL_APICALL ਖਾਲੀ GL_APIENTRY glViewport (GLint x, GLint y, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* GL_ES_VERSION_2_0 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_ES_ਸੰਸਕਰਣ_3_0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ES_ਸੰਸਕਰਣ_3_0 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ khronos_uint16_t GLhalf;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_READ_ਬਫਰ                    0x0C02
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNPACK_ਪੰਕਤੀ_ਲੰਮਾਈ              0x0CF2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNPACK_SKIP_ਪੰਕਤੀਆਂ               0x0CF3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNPACK_SKIP_PIXELS             0x0CF4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_PACK_ਪੰਕਤੀ_ਲੰਮਾਈ                0x0D02
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_PACK_SKIP_ਪੰਕਤੀਆਂ                 0x0D03
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_PACK_SKIP_PIXELS               0x0D04
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR                          0x1800
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਡੂੰਘਾਈ                          0x1801
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STENCIL                        0x1802
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RED                            0x1903
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGB8                           0x8051
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGBA8                          0x8058
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGB10_A2                       0x8059
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_BINDING_3D             0x806A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNPACK_SKIP_IMAGES             0x806D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNPACK_IMAGE_ਉਚਾਈ            0x806E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_3D                     0x806F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_WRAP_R                 0x8072
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_3_D_TEXTURE_ਮਾਪ            0x8073
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNED_INT_2_10_10_10_REV    0x8368
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_ELEMENTS_VERTICES          0x80E8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_ELEMENTS_INDICES           0x80E9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_MIN_LOD                0x813A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_MAX_LOD                0x813B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_ਅਧਾਰ_LEVEL             0x813C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_MAX_LEVEL              0x813D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MIN                            0x8007
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX                            0x8008
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਡੂੰਘਾਈ_COMPONENT24              0x81A6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_TEXTURE_LOD_BIAS           0x84FD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_COMPARE_ਬਹੁਲਕ           0x884C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_COMPARE_FUNC           0x884D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_CURRENT_QUERY                  0x8865
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_QUERY_ਨਤੀਜਾ                   0x8866
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_QUERY_ਨਤੀਜਾ_ਉਪਲਬਧ         0x8867
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਬਫਰ_MAPPED                  0x88BC
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਬਫਰ_MAP_ਸੂਚਕ             0x88BD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਧਾਰਾ_READ                    0x88E1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਧਾਰਾ_COPY                    0x88E2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STATIC_READ                    0x88E5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STATIC_COPY                    0x88E6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DYNAMIC_READ                   0x88E9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DYNAMIC_COPY                   0x88EA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_DRAW_BUFFERS               0x8824
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DRAW_BUFFER0                   0x8825
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DRAW_BUFFER1                   0x8826
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DRAW_BUFFER2                   0x8827
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DRAW_BUFFER3                   0x8828
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DRAW_BUFFER4                   0x8829
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DRAW_BUFFER5                   0x882A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DRAW_BUFFER6                   0x882B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DRAW_BUFFER7                   0x882C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DRAW_BUFFER8                   0x882D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DRAW_BUFFER9                   0x882E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DRAW_BUFFER10                  0x882F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DRAW_BUFFER11                  0x8830
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DRAW_BUFFER12                  0x8831
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DRAW_BUFFER13                  0x8832
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DRAW_BUFFER14                  0x8833
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DRAW_BUFFER15                  0x8834
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_FRAGMENT_ਇਕਸਾਰ_COMPONENTS 0x8B49
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_ਸ਼ੀਰਸ਼_ਇਕਸਾਰ_COMPONENTS  0x8B4A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SAMPLER_3D                     0x8B5F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SAMPLER_2D_SHADOW              0x8B62
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAGMENT_SHADER_DERIVATIVE_HINT 0x8B8B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_PIXEL_PACK_ਬਫਰ              0x88EB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_PIXEL_UNPACK_ਬਫਰ            0x88EC
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_PIXEL_PACK_ਬਫਰ_BINDING      0x88ED
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_PIXEL_UNPACK_ਬਫਰ_BINDING    0x88EF
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FLOAT_MAT2x3                   0x8B65
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FLOAT_MAT2x4                   0x8B66
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FLOAT_MAT3x2                   0x8B67
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FLOAT_MAT3x4                   0x8B68
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FLOAT_MAT4x2                   0x8B69
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FLOAT_MAT4x3                   0x8B6A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SRGB                           0x8C40
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SRGB8                          0x8C41
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SRGB8_ALPHA8                   0x8C43
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPARE_REF_ਮੰਜ਼ਿਲ_TEXTURE         0x884E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAJOR_ਸੰਸਕਰਣ                  0x821B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MINOR_ਸੰਸਕਰਣ                  0x821C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਅੰਕ_EXTENSIONS                 0x821D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGBA32F                        0x8814
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGB32F                         0x8815
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGBA16F                        0x881A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGB16F                         0x881B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸ਼ੀਰਸ਼_ATTRIB_ARRAY_INTEGER    0x88FD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_ARRAY_TEXTURE_LAYERS       0x88FF
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MIN_ਪ੍ਰੋਗਰਾਮ_TEXEL_ਵਿੱਥ       0x8904
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_ਪ੍ਰੋਗਰਾਮ_TEXEL_ਵਿੱਥ       0x8905
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_VARYING_COMPONENTS         0x8B4B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_2D_ARRAY               0x8C1A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_BINDING_2D_ARRAY       0x8C1D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_R11F_G11F_B10F                 0x8C3A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNED_INT_10F_11F_11F_REV   0x8C3B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGB9_E5                        0x8C3D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNED_INT_5_9_9_9_REV       0x8C3E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TRANSFORM_FEEDBACK_VARYING_MAX_ਲੰਮਾਈ 0x8C76
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TRANSFORM_FEEDBACK_ਬਫਰ_ਬਹੁਲਕ 0x8C7F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS 0x8C80
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TRANSFORM_FEEDBACK_VARYINGS    0x8C83
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TRANSFORM_FEEDBACK_ਬਫਰ_ਸ਼ੁਰੂ 0x8C84
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TRANSFORM_FEEDBACK_ਬਫਰ_ਮਾਪ 0x8C85
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN 0x8C88
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RASTERIZER_DISCARD             0x8C89
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS 0x8C8A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS 0x8C8B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_INTERLEAVED_ATTRIBS            0x8C8C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SEPARATE_ATTRIBS               0x8C8D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TRANSFORM_FEEDBACK_ਬਫਰ      0x8C8E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TRANSFORM_FEEDBACK_ਬਫਰ_BINDING 0x8C8F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGBA32UI                       0x8D70
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGB32UI                        0x8D71
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGBA16UI                       0x8D76
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGB16UI                        0x8D77
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGBA8UI                        0x8D7C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGB8UI                         0x8D7D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGBA32I                        0x8D82
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGB32I                         0x8D83
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGBA16I                        0x8D88
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGB16I                         0x8D89
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGBA8I                         0x8D8E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGB8I                          0x8D8F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RED_INTEGER                    0x8D94
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGB_INTEGER                    0x8D98
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGBA_INTEGER                   0x8D99
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SAMPLER_2D_ARRAY               0x8DC1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SAMPLER_2D_ARRAY_SHADOW        0x8DC4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SAMPLER_CUBE_SHADOW            0x8DC5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNED_INT_VEC2              0x8DC6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNED_INT_VEC3              0x8DC7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNED_INT_VEC4              0x8DC8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_INT_SAMPLER_2D                 0x8DCA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_INT_SAMPLER_3D                 0x8DCB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_INT_SAMPLER_CUBE               0x8DCC
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_INT_SAMPLER_2D_ARRAY           0x8DCF
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNED_INT_SAMPLER_2D        0x8DD2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNED_INT_SAMPLER_3D        0x8DD3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNED_INT_SAMPLER_CUBE      0x8DD4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNED_INT_SAMPLER_2D_ARRAY  0x8DD7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਬਫਰ_ACCESS_FLAGS            0x911F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਬਫਰ_MAP_ਲੰਮਾਈ              0x9120
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਬਫਰ_MAP_ਵਿੱਥ              0x9121
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਡੂੰਘਾਈ_COMPONENT32_F             0x8CAC
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DEPTH32F_STENCIL8              0x8CAD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FLOAT_32_UNSIGNED_INT_24_8_REV 0x8DAD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING 0x8210
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE 0x8211
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_ATTACHMENT_RED_ਮਾਪ 0x8212
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_ATTACHMENT_GREEN_ਮਾਪ 0x8213
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_ATTACHMENT_BLUE_ਮਾਪ 0x8214
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_ATTACHMENT_ALPHA_ਮਾਪ 0x8215
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_ATTACHMENT_ਡੂੰਘਾਈ_ਮਾਪ 0x8216
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_ATTACHMENT_STENCIL_ਮਾਪ 0x8217
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_DEFAULT            0x8218
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_UNDEFINED          0x8219
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਡੂੰਘਾਈ_STENCIL_ATTACHMENT       0x821A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਡੂੰਘਾਈ_STENCIL                  0x84F9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNED_INT_24_8              0x84FA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DEPTH24_STENCIL8               0x88F0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNED_NORMALIZED            0x8C17
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DRAW_FRAMEBUFFER_BINDING       0x8CA6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_READ_FRAMEBUFFER               0x8CA8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DRAW_FRAMEBUFFER               0x8CA9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_READ_FRAMEBUFFER_BINDING       0x8CAA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RENDERBUFFER_SAMPLES           0x8CAB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER 0x8CD4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_COLOR_ATTACHMENTS          0x8CDF
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ATTACHMENT1              0x8CE1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ATTACHMENT2              0x8CE2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ATTACHMENT3              0x8CE3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ATTACHMENT4              0x8CE4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ATTACHMENT5              0x8CE5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ATTACHMENT6              0x8CE6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ATTACHMENT7              0x8CE7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ATTACHMENT8              0x8CE8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ATTACHMENT9              0x8CE9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ATTACHMENT10             0x8CEA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ATTACHMENT11             0x8CEB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ATTACHMENT12             0x8CEC
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ATTACHMENT13             0x8CED
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ATTACHMENT14             0x8CEE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ATTACHMENT15             0x8CEF
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ATTACHMENT16             0x8CF0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ATTACHMENT17             0x8CF1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ATTACHMENT18             0x8CF2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ATTACHMENT19             0x8CF3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ATTACHMENT20             0x8CF4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ATTACHMENT21             0x8CF5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ATTACHMENT22             0x8CF6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ATTACHMENT23             0x8CF7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ATTACHMENT24             0x8CF8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ATTACHMENT25             0x8CF9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ATTACHMENT26             0x8CFA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ATTACHMENT27             0x8CFB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ATTACHMENT28             0x8CFC
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ATTACHMENT29             0x8CFD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ATTACHMENT30             0x8CFE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLOR_ATTACHMENT31             0x8CFF
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE 0x8D56
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_SAMPLES                    0x8D57
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_HALF_FLOAT                     0x140B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAP_READ_ਦੋਆਧਾਰੀ_ਅੰਕ                   0x0001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAP_WRITE_ਦੋਆਧਾਰੀ_ਅੰਕ                  0x0002
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAP_INVALIDATE_RANGE_ਦੋਆਧਾਰੀ_ਅੰਕ       0x0004
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAP_INVALIDATE_ਬਫਰ_ਦੋਆਧਾਰੀ_ਅੰਕ      0x0008
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAP_FLUSH_EXPLICIT_ਦੋਆਧਾਰੀ_ਅੰਕ         0x0010
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAP_UNSYNCHRONIZED_ਦੋਆਧਾਰੀ_ਅੰਕ         0x0020
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RG                             0x8227
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RG_INTEGER                     0x8228
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_R8                             0x8229
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RG8                            0x822B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_R16F                           0x822D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_R32F                           0x822E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RG16F                          0x822F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RG32F                          0x8230
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_R8I                            0x8231
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_R8UI                           0x8232
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_R16I                           0x8233
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_R16UI                          0x8234
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_R32I                           0x8235
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_R32UI                          0x8236
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RG8I                           0x8237
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RG8UI                          0x8238
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RG16I                          0x8239
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RG16UI                         0x823A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RG32I                          0x823B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RG32UI                         0x823C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸ਼ੀਰਸ਼_ARRAY_BINDING           0x85B5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_R8_SNORM                       0x8F94
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RG8_SNORM                      0x8F95
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGB8_SNORM                     0x8F96
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGBA8_SNORM                    0x8F97
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SIGNED_NORMALIZED              0x8F9C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_PRIMITIVE_RESTART_FIXED_ਸੂਚਕਾਂਕ  0x8D69
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COPY_READ_ਬਫਰ               0x8F36
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COPY_WRITE_ਬਫਰ              0x8F37
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COPY_READ_ਬਫਰ_BINDING       0x8F36
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COPY_WRITE_ਬਫਰ_BINDING      0x8F37
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਇਕਸਾਰ_ਬਫਰ                 0x8A11
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਇਕਸਾਰ_ਬਫਰ_BINDING         0x8A28
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਇਕਸਾਰ_ਬਫਰ_ਸ਼ੁਰੂ           0x8A29
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਇਕਸਾਰ_ਬਫਰ_ਮਾਪ            0x8A2A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_ਸ਼ੀਰਸ਼_ਇਕਸਾਰ_ਖੰਡਾਂ      0x8A2B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_FRAGMENT_ਇਕਸਾਰ_ਖੰਡਾਂ    0x8A2D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_COMBINED_ਇਕਸਾਰ_ਖੰਡਾਂ    0x8A2E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_ਇਕਸਾਰ_ਬਫਰ_BINDINGS    0x8A2F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_ਇਕਸਾਰ_ਖੰਡ_ਮਾਪ         0x8A30
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_COMBINED_ਸ਼ੀਰਸ਼_ਇਕਸਾਰ_COMPONENTS 0x8A31
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_COMBINED_FRAGMENT_ਇਕਸਾਰ_COMPONENTS 0x8A33
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਇਕਸਾਰ_ਬਫਰ_ਵਿੱਥ_ALIGNMENT 0x8A34
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸਰਗਰਮ_ਇਕਸਾਰ_ਖੰਡ_MAX_NAME_ਲੰਮਾਈ 0x8A35
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸਰਗਰਮ_ਇਕਸਾਰ_ਖੰਡਾਂ          0x8A36
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਇਕਸਾਰ_TYPE                   0x8A37
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਇਕਸਾਰ_ਮਾਪ                   0x8A38
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਇਕਸਾਰ_NAME_ਲੰਮਾਈ            0x8A39
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਇਕਸਾਰ_ਖੰਡ_ਸੂਚਕਾਂਕ            0x8A3A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਇਕਸਾਰ_ਵਿੱਥ                 0x8A3B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਇਕਸਾਰ_ARRAY_STRIDE           0x8A3C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਇਕਸਾਰ_ਮੈਟ੍ਰਿਕਸ_STRIDE          0x8A3D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਇਕਸਾਰ_IS_ਪੰਕਤੀ_MAJOR           0x8A3E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਇਕਸਾਰ_ਖੰਡ_BINDING          0x8A3F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਇਕਸਾਰ_ਖੰਡ_ਅੰਕੜੇ_ਮਾਪ        0x8A40
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਇਕਸਾਰ_ਖੰਡ_NAME_ਲੰਮਾਈ      0x8A41
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਇਕਸਾਰ_ਖੰਡ_ਸਰਗਰਮ_UNIFORMS  0x8A42
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਇਕਸਾਰ_ਖੰਡ_ਸਰਗਰਮ_ਇਕਸਾਰ_INDICES 0x8A43
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਇਕਸਾਰ_ਖੰਡ_REFERENCED_BY_ਸ਼ੀਰਸ਼_SHADER 0x8A44
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਇਕਸਾਰ_ਖੰਡ_REFERENCED_BY_FRAGMENT_SHADER 0x8A46
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_INVALID_ਸੂਚਕਾਂਕ                  0xFFFFFFFFu
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_ਸ਼ੀਰਸ਼_OUTPUT_COMPONENTS   0x9122
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_FRAGMENT_ਨਿਵੇਸ਼_COMPONENTS  0x9125
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_SERVER_WAIT_TIMEOUT        0x9111
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OBJECT_TYPE                    0x9112
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SYNC_CONDITION                 0x9113
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SYNC_ਸਥਿਤੀ                    0x9114
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SYNC_FLAGS                     0x9115
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SYNC_FENCE                     0x9116
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SYNC_GPU_COMMANDS_COMPLETE     0x9117
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNALED                     0x9118
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SIGNALED                       0x9119
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ALREADY_SIGNALED               0x911A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TIMEOUT_EXPIRED                0x911B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_CONDITION_SATISFIED            0x911C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_WAIT_FAILED                    0x911D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SYNC_FLUSH_COMMANDS_ਦੋਆਧਾਰੀ_ਅੰਕ        0x00000001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TIMEOUT_IGNORED                0xFFFFFFFFFFFFFFFFull
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸ਼ੀਰਸ਼_ATTRIB_ARRAY_ਭਾਜਕ    0x88FE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ANY_SAMPLES_PASSED             0x8C2F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ANY_SAMPLES_PASSED_CONSERVATIVE 0x8D6A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SAMPLER_BINDING                0x8919
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGB10_A2UI                     0x906F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_SWIZZLE_R              0x8E42
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_SWIZZLE_G              0x8E43
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_SWIZZLE_B              0x8E44
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_SWIZZLE_A              0x8E45
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_GREEN                          0x1904
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_BLUE                           0x1905
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_INT_2_10_10_10_REV             0x8D9F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TRANSFORM_FEEDBACK             0x8E22
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TRANSFORM_FEEDBACK_PAUSED      0x8E23
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TRANSFORM_FEEDBACK_ਸਰਗਰਮ      0x8E24
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TRANSFORM_FEEDBACK_BINDING     0x8E25
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਪ੍ਰੋਗਰਾਮ_ਦੁਆਧਾਰੀ_RETRIEVABLE_HINT 0x8257
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਪ੍ਰੋਗਰਾਮ_ਦੁਆਧਾਰੀ_ਲੰਮਾਈ          0x8741
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਅੰਕ_ਪ੍ਰੋਗਰਾਮ_ਦੁਆਧਾਰੀ_FORMATS     0x87FE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਪ੍ਰੋਗਰਾਮ_ਦੁਆਧਾਰੀ_FORMATS         0x87FF
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_R11_EAC             0x9270
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_SIGNED_R11_EAC      0x9271
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_RG11_EAC            0x9272
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_SIGNED_RG11_EAC     0x9273
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_RGB8_ETC2           0x9274
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_SRGB8_ETC2          0x9275
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9276
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9277
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_RGBA8_ETC2_EAC      0x9278
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC 0x9279
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_IMMUTABLE_FORMAT       0x912F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_ELEMENT_ਸੂਚਕਾਂਕ              0x8D6B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਅੰਕ_SAMPLE_COUNTS              0x9380
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_IMMUTABLE_ਪੱਧਰ       0x82DF
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLREADBUFFERPROC) (GLenum src);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDRAWRANGEELEMENTSPROC) (GLenum ਬਹੁਲਕ, GLuint ਸ਼ੁਰੂ, GLuint ਸਿਰਾ, GLsizei ਗਿਣਤੀ_2, GLenum type, ਅਚਲ ਖਾਲੀ *indices);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLTEXIMAGE3DPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLint level, GLint internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLsizei ਡੂੰਘਾਈ_2, GLint border, GLenum format, GLenum type, ਅਚਲ ਖਾਲੀ *pixels);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLTEXSUBIMAGE3DPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLsizei ਡੂੰਘਾਈ_2, GLenum format, GLenum type, ਅਚਲ ਖਾਲੀ *pixels);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLCOPYTEXSUBIMAGE3DPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLCOMPRESSEDTEXIMAGE3DPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLint level, GLenum internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLsizei ਡੂੰਘਾਈ_2, GLint border, GLsizei image_ਮਾਪ, ਅਚਲ ਖਾਲੀ *ਅੰਕੜੇ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLsizei ਡੂੰਘਾਈ_2, GLenum format, GLsizei image_ਮਾਪ, ਅਚਲ ਖਾਲੀ *ਅੰਕੜੇ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGENQUERIESPROC) (GLsizei n, GLuint *ids);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDELETEQUERIESPROC) (GLsizei n, ਅਚਲ GLuint *ids);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLboolean (GL_APIENTRYP PFNGLISQUERYPROC) (GLuint id);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLBEGINQUERYPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLuint id);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLENDQUERYPROC) (GLenum ਨਿਸ਼ਾਨਾ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETQUERYIVPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETQUERYOBJECTUIVPROC) (GLuint id, GLenum pname, GLuint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLboolean (GL_APIENTRYP PFNGLUNMAPBUFFERPROC) (GLenum ਨਿਸ਼ਾਨਾ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETBUFFERPOINTERVPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, ਖਾਲੀ **params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDRAWBUFFERSPROC) (GLsizei n, ਅਚਲ GLenum *bufs);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUNIFORMMATRIX2X3FVPROC) (GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUNIFORMMATRIX3X2FVPROC) (GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUNIFORMMATRIX2X4FVPROC) (GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUNIFORMMATRIX4X2FVPROC) (GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUNIFORMMATRIX3X4FVPROC) (GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUNIFORMMATRIX4X3FVPROC) (GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLBLITFRAMEBUFFERPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield ਨਕਾਬ, GLenum filter);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLsizei samples, GLenum internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURELAYERPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum attachment, GLuint texture, GLint level, GLint layer);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ *(GL_APIENTRYP PFNGLMAPBUFFERRANGEPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLintptr ਵਿੱਥ_2, GLsizeiptr ਲੰਮਾਈ, GLbitfield access);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLintptr ਵਿੱਥ_2, GLsizeiptr ਲੰਮਾਈ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLBINDVERTEXARRAYPROC) (GLuint array);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDELETEVERTEXARRAYSPROC) (GLsizei n, ਅਚਲ GLuint *arrays);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint *arrays);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLboolean (GL_APIENTRYP PFNGLISVERTEXARRAYPROC) (GLuint array);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETINTEGERI_VPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLuint ਸੂਚਕਾਂਕ, GLint *ਅੰਕੜੇ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLBEGINTRANSFORMFEEDBACKPROC) (GLenum primitive_ਬਹੁਲਕ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLENDTRANSFORMFEEDBACKPROC) (ਖਾਲੀ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLBINDBUFFERRANGEPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLuint ਸੂਚਕਾਂਕ, GLuint ਬਫਰ_2, GLintptr ਵਿੱਥ_2, GLsizeiptr ਮਾਪ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLBINDBUFFERBASEPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLuint ਸੂਚਕਾਂਕ, GLuint ਬਫਰ_2);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLTRANSFORMFEEDBACKVARYINGSPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLchar *ਅਚਲ*varyings, GLenum ਬਫਰ_ਬਹੁਲਕ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETTRANSFORMFEEDBACKVARYINGPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLuint ਸੂਚਕਾਂਕ, GLsizei buf_ਮਾਪ, GLsizei *ਲੰਮਾਈ, GLsizei *ਮਾਪ, GLenum *type, GLchar *name);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLVERTEXATTRIBIPOINTERPROC) (GLuint ਸੂਚਕਾਂਕ, GLint ਮਾਪ, GLenum type, GLsizei stride, ਅਚਲ ਖਾਲੀ *ਸੂਚਕ_2);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETVERTEXATTRIBIIVPROC) (GLuint ਸੂਚਕਾਂਕ, GLenum pname, GLint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETVERTEXATTRIBIUIVPROC) (GLuint ਸੂਚਕਾਂਕ, GLenum pname, GLuint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLVERTEXATTRIBI4IPROC) (GLuint ਸੂਚਕਾਂਕ, GLint x, GLint y, GLint z, GLint w);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLVERTEXATTRIBI4UIPROC) (GLuint ਸੂਚਕਾਂਕ, GLuint x, GLuint y, GLuint z, GLuint w);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLVERTEXATTRIBI4IVPROC) (GLuint ਸੂਚਕਾਂਕ, ਅਚਲ GLint *v);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLVERTEXATTRIBI4UIVPROC) (GLuint ਸੂਚਕਾਂਕ, ਅਚਲ GLuint *v);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETUNIFORMUIVPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLuint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLint (GL_APIENTRYP PFNGLGETFRAGDATALOCATIONPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, ਅਚਲ GLchar *name);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUNIFORM1UIPROC) (GLint location, GLuint v0);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUNIFORM2UIPROC) (GLint location, GLuint v0, GLuint v1);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUNIFORM3UIPROC) (GLint location, GLuint v0, GLuint v1, GLuint v2);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUNIFORM4UIPROC) (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUNIFORM1UIVPROC) (GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLuint *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUNIFORM2UIVPROC) (GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLuint *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUNIFORM3UIVPROC) (GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLuint *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUNIFORM4UIVPROC) (GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLuint *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLCLEARBUFFERIVPROC) (GLenum ਬਫਰ_2, GLint drawbuffer, ਅਚਲ GLint *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLCLEARBUFFERUIVPROC) (GLenum ਬਫਰ_2, GLint drawbuffer, ਅਚਲ GLuint *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLCLEARBUFFERFVPROC) (GLenum ਬਫਰ_2, GLint drawbuffer, ਅਚਲ GLfloat *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLCLEARBUFFERFIPROC) (GLenum ਬਫਰ_2, GLint drawbuffer, GLfloat ਡੂੰਘਾਈ_2, GLint stencil);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਅਚਲ GLubyte *(GL_APIENTRYP PFNGLGETSTRINGIPROC) (GLenum name, GLuint ਸੂਚਕਾਂਕ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLCOPYBUFFERSUBDATAPROC) (GLenum read_ਨਿਸ਼ਾਨਾ, GLenum write_ਨਿਸ਼ਾਨਾ, GLintptr read_ਵਿੱਥ, GLintptr write_ਵਿੱਥ, GLsizeiptr ਮਾਪ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETUNIFORMINDICESPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLsizei ਇਕਸਾਰ_ਗਿਣਤੀ, ਅਚਲ GLchar *ਅਚਲ*ਇਕਸਾਰ_ਨਾਂ, GLuint *ਇਕਸਾਰ_Indices);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETACTIVEUNIFORMSIVPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLsizei ਇਕਸਾਰ_ਗਿਣਤੀ, ਅਚਲ GLuint *ਇਕਸਾਰ_Indices, GLenum pname, GLint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLuint (GL_APIENTRYP PFNGLGETUNIFORMBLOCKINDEXPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, ਅਚਲ GLchar *ਇਕਸਾਰ_ਖੰਡ_Name);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKIVPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLuint ਇਕਸਾਰ_ਖੰਡ_ਸੂਚਕਾਂਕ, GLenum pname, GLint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLuint ਇਕਸਾਰ_ਖੰਡ_ਸੂਚਕਾਂਕ, GLsizei buf_ਮਾਪ, GLsizei *ਲੰਮਾਈ, GLchar *ਇਕਸਾਰ_ਖੰਡ_Name);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUNIFORMBLOCKBINDINGPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLuint ਇਕਸਾਰ_ਖੰਡ_ਸੂਚਕਾਂਕ, GLuint ਇਕਸਾਰ_ਖੰਡ_Binding);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDPROC) (GLenum ਬਹੁਲਕ, GLint ਪਹਿਲਾ, GLsizei ਗਿਣਤੀ_2, GLsizei instancecount);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDPROC) (GLenum ਬਹੁਲਕ, GLsizei ਗਿਣਤੀ_2, GLenum type, ਅਚਲ ਖਾਲੀ *indices, GLsizei instancecount);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLsync (GL_APIENTRYP PFNGLFENCESYNCPROC) (GLenum condition, GLbitfield flags);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLboolean (GL_APIENTRYP PFNGLISSYNCPROC) (GLsync sync);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDELETESYNCPROC) (GLsync sync);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLenum (GL_APIENTRYP PFNGLCLIENTWAITSYNCPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLWAITSYNCPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETINTEGER64VPROC) (GLenum pname, GLint64 *ਅੰਕੜੇ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETSYNCIVPROC) (GLsync sync, GLenum pname, GLsizei ਗਿਣਤੀ_2, GLsizei *ਲੰਮਾਈ, GLint *ਮੁੱਲਾਂ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETINTEGER64I_VPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLuint ਸੂਚਕਾਂਕ, GLint64 *ਅੰਕੜੇ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETBUFFERPARAMETERI64VPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLint64 *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGENSAMPLERSPROC) (GLsizei ਗਿਣਤੀ_2, GLuint *samplers);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDELETESAMPLERSPROC) (GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLuint *samplers);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLboolean (GL_APIENTRYP PFNGLISSAMPLERPROC) (GLuint sampler);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLBINDSAMPLERPROC) (GLuint unit, GLuint sampler);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIPROC) (GLuint sampler, GLenum pname, GLint param);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, ਅਚਲ GLint *param);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLSAMPLERPARAMETERFPROC) (GLuint sampler, GLenum pname, GLfloat param);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, ਅਚਲ GLfloat *param);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, GLint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, GLfloat *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLVERTEXATTRIBDIVISORPROC) (GLuint ਸੂਚਕਾਂਕ, GLuint ਭਾਜਕ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLBINDTRANSFORMFEEDBACKPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLuint id);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDELETETRANSFORMFEEDBACKSPROC) (GLsizei n, ਅਚਲ GLuint *ids);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGENTRANSFORMFEEDBACKSPROC) (GLsizei n, GLuint *ids);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLboolean (GL_APIENTRYP PFNGLISTRANSFORMFEEDBACKPROC) (GLuint id);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPAUSETRANSFORMFEEDBACKPROC) (ਖਾਲੀ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLRESUMETRANSFORMFEEDBACKPROC) (ਖਾਲੀ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETPROGRAMBINARYPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLsizei buf_ਮਾਪ, GLsizei *ਲੰਮਾਈ, GLenum *ਦੁਆਧਾਰੀ_Format, ਖਾਲੀ *ਦੁਆਧਾਰੀ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPROGRAMBINARYPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLenum ਦੁਆਧਾਰੀ_Format, ਅਚਲ ਖਾਲੀ *ਦੁਆਧਾਰੀ, GLsizei ਲੰਮਾਈ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPROGRAMPARAMETERIPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLenum pname, GLint ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLINVALIDATEFRAMEBUFFERPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLsizei ਅੰਕ_Attachments, ਅਚਲ GLenum *attachments);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLINVALIDATESUBFRAMEBUFFERPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLsizei ਅੰਕ_Attachments, ਅਚਲ GLenum *attachments, GLint x, GLint y, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLTEXSTORAGE2DPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLsizei ਪੱਧਰ, GLenum internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLTEXSTORAGE3DPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLsizei ਪੱਧਰ, GLenum internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLsizei ਡੂੰਘਾਈ_2);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETINTERNALFORMATIVPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum internalformat, GLenum pname, GLsizei ਗਿਣਤੀ_2, GLint *params);
#ਜੇ GL_GLES_PROTOTYPES
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Read_ਬਫਰ (GLenum src);
GL_APICALL ਖਾਲੀ GL_APIENTRY glDrawRangeElements (GLenum ਬਹੁਲਕ, GLuint ਸ਼ੁਰੂ, GLuint ਸਿਰਾ, GLsizei ਗਿਣਤੀ_2, GLenum type, ਅਚਲ ਖਾਲੀ *indices);
GL_APICALL ਖਾਲੀ GL_APIENTRY glTexImage3D (GLenum ਨਿਸ਼ਾਨਾ, GLint level, GLint internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLsizei ਡੂੰਘਾਈ_2, GLint border, GLenum format, GLenum type, ਅਚਲ ਖਾਲੀ *pixels);
GL_APICALL ਖਾਲੀ GL_APIENTRY glTexSubImage3D (GLenum ਨਿਸ਼ਾਨਾ, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLsizei ਡੂੰਘਾਈ_2, GLenum format, GLenum type, ਅਚਲ ਖਾਲੀ *pixels);
GL_APICALL ਖਾਲੀ GL_APIENTRY glCopyTexSubImage3D (GLenum ਨਿਸ਼ਾਨਾ, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glCompressedTexImage3D (GLenum ਨਿਸ਼ਾਨਾ, GLint level, GLenum internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLsizei ਡੂੰਘਾਈ_2, GLint border, GLsizei image_ਮਾਪ, ਅਚਲ ਖਾਲੀ *ਅੰਕੜੇ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glCompressedTexSubImage3D (GLenum ਨਿਸ਼ਾਨਾ, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLsizei ਡੂੰਘਾਈ_2, GLenum format, GLsizei image_ਮਾਪ, ਅਚਲ ਖਾਲੀ *ਅੰਕੜੇ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGenQueries (GLsizei n, GLuint *ids);
GL_APICALL ਖਾਲੀ GL_APIENTRY glDeleteQueries (GLsizei n, ਅਚਲ GLuint *ids);
GL_APICALL GLboolean GL_APIENTRY glIsQuery (GLuint id);
GL_APICALL ਖਾਲੀ GL_APIENTRY glBeginQuery (GLenum ਨਿਸ਼ਾਨਾ, GLuint id);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਸਿਰਾ_Query (GLenum ਨਿਸ਼ਾਨਾ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetQueryiv (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLint *params);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetQueryObjectuiv (GLuint id, GLenum pname, GLuint *params);
GL_APICALL GLboolean GL_APIENTRY gl_Unmap_ਬਫਰ (GLenum ਨਿਸ਼ਾਨਾ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Get_ਬਫਰ_Pointerv (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, ਖਾਲੀ **params);
GL_APICALL ਖਾਲੀ GL_APIENTRY glDrawBuffers (GLsizei n, ਅਚਲ GLenum *bufs);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਇਕਸਾਰ_Matrix2x3fv (GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਇਕਸਾਰ_Matrix3x2fv (GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਇਕਸਾਰ_Matrix2x4fv (GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਇਕਸਾਰ_Matrix4x2fv (GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਇਕਸਾਰ_Matrix3x4fv (GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਇਕਸਾਰ_Matrix4x3fv (GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glBlitFramebuffer (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield ਨਕਾਬ, GLenum filter);
GL_APICALL ਖਾਲੀ GL_APIENTRY glRenderbufferStorageMultisample (GLenum ਨਿਸ਼ਾਨਾ, GLsizei samples, GLenum internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glFramebufferTextureLayer (GLenum ਨਿਸ਼ਾਨਾ, GLenum attachment, GLuint texture, GLint level, GLint layer);
GL_APICALL ਖਾਲੀ *GL_APIENTRY gl_Map_ਬਫਰ_Range (GLenum ਨਿਸ਼ਾਨਾ, GLintptr ਵਿੱਥ_2, GLsizeiptr ਲੰਮਾਈ, GLbitfield access);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Flush_Mapped_ਬਫਰ_Range (GLenum ਨਿਸ਼ਾਨਾ, GLintptr ਵਿੱਥ_2, GLsizeiptr ਲੰਮਾਈ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Bind_ਸ਼ੀਰਸ਼_Array (GLuint array);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Delete_ਸ਼ੀਰਸ਼_Arrays (GLsizei n, ਅਚਲ GLuint *arrays);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Gen_ਸ਼ੀਰਸ਼_Arrays (GLsizei n, GLuint *arrays);
GL_APICALL GLboolean GL_APIENTRY gl_Is_ਸ਼ੀਰਸ਼_Array (GLuint array);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetIntegeri_v (GLenum ਨਿਸ਼ਾਨਾ, GLuint ਸੂਚਕਾਂਕ, GLint *ਅੰਕੜੇ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glBeginTransformFeedback (GLenum primitive_ਬਹੁਲਕ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਸਿਰਾ_Transform_Feedback (ਖਾਲੀ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Bind_ਬਫਰ_Range (GLenum ਨਿਸ਼ਾਨਾ, GLuint ਸੂਚਕਾਂਕ, GLuint ਬਫਰ_2, GLintptr ਵਿੱਥ_2, GLsizeiptr ਮਾਪ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Bind_ਬਫਰ_ਅਧਾਰ (GLenum ਨਿਸ਼ਾਨਾ, GLuint ਸੂਚਕਾਂਕ, GLuint ਬਫਰ_2);
GL_APICALL ਖਾਲੀ GL_APIENTRY glTransformFeedbackVaryings (GLuint ਪ੍ਰੋਗਰਾਮ, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLchar *ਅਚਲ*varyings, GLenum ਬਫਰ_ਬਹੁਲਕ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetTransformFeedbackVarying (GLuint ਪ੍ਰੋਗਰਾਮ, GLuint ਸੂਚਕਾਂਕ, GLsizei buf_ਮਾਪ, GLsizei *ਲੰਮਾਈ, GLsizei *ਮਾਪ, GLenum *type, GLchar *name);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਸ਼ੀਰਸ਼_Attrib_IPointer (GLuint ਸੂਚਕਾਂਕ, GLint ਮਾਪ, GLenum type, GLsizei stride, ਅਚਲ ਖਾਲੀ *ਸੂਚਕ_2);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Get_ਸ਼ੀਰਸ਼_Attrib_Iiv (GLuint ਸੂਚਕਾਂਕ, GLenum pname, GLint *params);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Get_ਸ਼ੀਰਸ਼_Attrib_Iuiv (GLuint ਸੂਚਕਾਂਕ, GLenum pname, GLuint *params);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਸ਼ੀਰਸ਼_Attrib_I4i (GLuint ਸੂਚਕਾਂਕ, GLint x, GLint y, GLint z, GLint w);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਸ਼ੀਰਸ਼_Attrib_I4ui (GLuint ਸੂਚਕਾਂਕ, GLuint x, GLuint y, GLuint z, GLuint w);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਸ਼ੀਰਸ਼_Attrib_I4iv (GLuint ਸੂਚਕਾਂਕ, ਅਚਲ GLint *v);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਸ਼ੀਰਸ਼_Attrib_I4uiv (GLuint ਸੂਚਕਾਂਕ, ਅਚਲ GLuint *v);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetUniformuiv (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLuint *params);
GL_APICALL GLint GL_APIENTRY gl_Get_Frag_ਅੰਕੜੇ_Location (GLuint ਪ੍ਰੋਗਰਾਮ, ਅਚਲ GLchar *name);
GL_APICALL ਖਾਲੀ GL_APIENTRY glUniform1ui (GLint location, GLuint v0);
GL_APICALL ਖਾਲੀ GL_APIENTRY glUniform2ui (GLint location, GLuint v0, GLuint v1);
GL_APICALL ਖਾਲੀ GL_APIENTRY glUniform3ui (GLint location, GLuint v0, GLuint v1, GLuint v2);
GL_APICALL ਖਾਲੀ GL_APIENTRY glUniform4ui (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
GL_APICALL ਖਾਲੀ GL_APIENTRY glUniform1uiv (GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLuint *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glUniform2uiv (GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLuint *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glUniform3uiv (GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLuint *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glUniform4uiv (GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLuint *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glClearBufferiv (GLenum ਬਫਰ_2, GLint drawbuffer, ਅਚਲ GLint *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glClearBufferuiv (GLenum ਬਫਰ_2, GLint drawbuffer, ਅਚਲ GLuint *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glClearBufferfv (GLenum ਬਫਰ_2, GLint drawbuffer, ਅਚਲ GLfloat *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glClearBufferfi (GLenum ਬਫਰ_2, GLint drawbuffer, GLfloat ਡੂੰਘਾਈ_2, GLint stencil);
GL_APICALL ਅਚਲ GLubyte *GL_APIENTRY glGetStringi (GLenum name, GLuint ਸੂਚਕਾਂਕ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Copy_ਬਫਰ_Sub_ਅੰਕੜੇ (GLenum read_ਨਿਸ਼ਾਨਾ, GLenum write_ਨਿਸ਼ਾਨਾ, GLintptr read_ਵਿੱਥ, GLintptr write_ਵਿੱਥ, GLsizeiptr ਮਾਪ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Get_ਇਕਸਾਰ_Indices (GLuint ਪ੍ਰੋਗਰਾਮ, GLsizei ਇਕਸਾਰ_ਗਿਣਤੀ, ਅਚਲ GLchar *ਅਚਲ*ਇਕਸਾਰ_ਨਾਂ, GLuint *ਇਕਸਾਰ_Indices);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Get_ਸਰਗਰਮ_Uniformsiv (GLuint ਪ੍ਰੋਗਰਾਮ, GLsizei ਇਕਸਾਰ_ਗਿਣਤੀ, ਅਚਲ GLuint *ਇਕਸਾਰ_Indices, GLenum pname, GLint *params);
GL_APICALL GLuint GL_APIENTRY gl_Get_ਇਕਸਾਰ_ਖੰਡ_ਸੂਚਕਾਂਕ (GLuint ਪ੍ਰੋਗਰਾਮ, ਅਚਲ GLchar *ਇਕਸਾਰ_ਖੰਡ_Name);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Get_ਸਰਗਰਮ_ਇਕਸਾਰ_Blockiv (GLuint ਪ੍ਰੋਗਰਾਮ, GLuint ਇਕਸਾਰ_ਖੰਡ_ਸੂਚਕਾਂਕ, GLenum pname, GLint *params);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Get_ਸਰਗਰਮ_ਇਕਸਾਰ_ਖੰਡ_Name (GLuint ਪ੍ਰੋਗਰਾਮ, GLuint ਇਕਸਾਰ_ਖੰਡ_ਸੂਚਕਾਂਕ, GLsizei buf_ਮਾਪ, GLsizei *ਲੰਮਾਈ, GLchar *ਇਕਸਾਰ_ਖੰਡ_Name);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਇਕਸਾਰ_ਖੰਡ_Binding (GLuint ਪ੍ਰੋਗਰਾਮ, GLuint ਇਕਸਾਰ_ਖੰਡ_ਸੂਚਕਾਂਕ, GLuint ਇਕਸਾਰ_ਖੰਡ_Binding);
GL_APICALL ਖਾਲੀ GL_APIENTRY glDrawArraysInstanced (GLenum ਬਹੁਲਕ, GLint ਪਹਿਲਾ, GLsizei ਗਿਣਤੀ_2, GLsizei instancecount);
GL_APICALL ਖਾਲੀ GL_APIENTRY glDrawElementsInstanced (GLenum ਬਹੁਲਕ, GLsizei ਗਿਣਤੀ_2, GLenum type, ਅਚਲ ਖਾਲੀ *indices, GLsizei instancecount);
GL_APICALL GLsync GL_APIENTRY glFenceSync (GLenum condition, GLbitfield flags);
GL_APICALL GLboolean GL_APIENTRY glIsSync (GLsync sync);
GL_APICALL ਖਾਲੀ GL_APIENTRY glDeleteSync (GLsync sync);
GL_APICALL GLenum GL_APIENTRY glClientWaitSync (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_APICALL ਖਾਲੀ GL_APIENTRY glWaitSync (GLsync sync, GLbitfield flags, GLuint64 timeout);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetInteger64v (GLenum pname, GLint64 *ਅੰਕੜੇ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetSynciv (GLsync sync, GLenum pname, GLsizei ਗਿਣਤੀ_2, GLsizei *ਲੰਮਾਈ, GLint *ਮੁੱਲਾਂ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetInteger64i_v (GLenum ਨਿਸ਼ਾਨਾ, GLuint ਸੂਚਕਾਂਕ, GLint64 *ਅੰਕੜੇ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Get_ਬਫਰ_Parameteri64v (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLint64 *params);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGenSamplers (GLsizei ਗਿਣਤੀ_2, GLuint *samplers);
GL_APICALL ਖਾਲੀ GL_APIENTRY glDeleteSamplers (GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLuint *samplers);
GL_APICALL GLboolean GL_APIENTRY glIsSampler (GLuint sampler);
GL_APICALL ਖਾਲੀ GL_APIENTRY glBindSampler (GLuint unit, GLuint sampler);
GL_APICALL ਖਾਲੀ GL_APIENTRY glSamplerParameteri (GLuint sampler, GLenum pname, GLint param);
GL_APICALL ਖਾਲੀ GL_APIENTRY glSamplerParameteriv (GLuint sampler, GLenum pname, ਅਚਲ GLint *param);
GL_APICALL ਖਾਲੀ GL_APIENTRY glSamplerParameterf (GLuint sampler, GLenum pname, GLfloat param);
GL_APICALL ਖਾਲੀ GL_APIENTRY glSamplerParameterfv (GLuint sampler, GLenum pname, ਅਚਲ GLfloat *param);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetSamplerParameteriv (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetSamplerParameterfv (GLuint sampler, GLenum pname, GLfloat *params);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਸ਼ੀਰਸ਼_Attrib_ਭਾਜਕ (GLuint ਸੂਚਕਾਂਕ, GLuint ਭਾਜਕ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glBindTransformFeedback (GLenum ਨਿਸ਼ਾਨਾ, GLuint id);
GL_APICALL ਖਾਲੀ GL_APIENTRY glDeleteTransformFeedbacks (GLsizei n, ਅਚਲ GLuint *ids);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGenTransformFeedbacks (GLsizei n, GLuint *ids);
GL_APICALL GLboolean GL_APIENTRY glIsTransformFeedback (GLuint id);
GL_APICALL ਖਾਲੀ GL_APIENTRY glPauseTransformFeedback (ਖਾਲੀ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glResumeTransformFeedback (ਖਾਲੀ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Get_ਪ੍ਰੋਗਰਾਮ_ਦੁਆਧਾਰੀ (GLuint ਪ੍ਰੋਗਰਾਮ, GLsizei buf_ਮਾਪ, GLsizei *ਲੰਮਾਈ, GLenum *ਦੁਆਧਾਰੀ_Format, ਖਾਲੀ *ਦੁਆਧਾਰੀ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਪ੍ਰੋਗਰਾਮ_ਦੁਆਧਾਰੀ (GLuint ਪ੍ਰੋਗਰਾਮ, GLenum ਦੁਆਧਾਰੀ_Format, ਅਚਲ ਖਾਲੀ *ਦੁਆਧਾਰੀ, GLsizei ਲੰਮਾਈ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਪ੍ਰੋਗਰਾਮ_Parameteri (GLuint ਪ੍ਰੋਗਰਾਮ, GLenum pname, GLint ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glInvalidateFramebuffer (GLenum ਨਿਸ਼ਾਨਾ, GLsizei ਅੰਕ_Attachments, ਅਚਲ GLenum *attachments);
GL_APICALL ਖਾਲੀ GL_APIENTRY glInvalidateSubFramebuffer (GLenum ਨਿਸ਼ਾਨਾ, GLsizei ਅੰਕ_Attachments, ਅਚਲ GLenum *attachments, GLint x, GLint y, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glTexStorage2D (GLenum ਨਿਸ਼ਾਨਾ, GLsizei ਪੱਧਰ, GLenum internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glTexStorage3D (GLenum ਨਿਸ਼ਾਨਾ, GLsizei ਪੱਧਰ, GLenum internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLsizei ਡੂੰਘਾਈ_2);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetInternalformativ (GLenum ਨਿਸ਼ਾਨਾ, GLenum internalformat, GLenum pname, GLsizei ਗਿਣਤੀ_2, GLint *params);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* GL_ES_VERSION_3_0 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_ES_ਸੰਸਕਰਣ_3_1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ES_ਸੰਸਕਰਣ_3_1 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPUTE_SHADER                 0x91B9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_COMPUTE_ਇਕਸਾਰ_ਖੰਡਾਂ     0x91BB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS 0x91BC
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_COMPUTE_IMAGE_UNIFORMS     0x91BD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_COMPUTE_SHARED_ਸਮ੍ਰਿਤੀ_ਮਾਪ 0x8262
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_COMPUTE_ਇਕਸਾਰ_COMPONENTS 0x8263
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS 0x8264
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_COMPUTE_ATOMIC_COUNTERS    0x8265
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_COMBINED_COMPUTE_ਇਕਸਾਰ_COMPONENTS 0x8266
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_COMPUTE_WORK_ਸਮੂਹ_INVOCATIONS 0x90EB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_COMPUTE_WORK_ਸਮੂਹ_ਗਿਣਤੀ   0x91BE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_COMPUTE_WORK_ਸਮੂਹ_ਮਾਪ    0x91BF
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPUTE_WORK_ਸਮੂਹ_ਮਾਪ        0x8267
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DISPATCH_ਅਸਿੱਧਾ_ਬਫਰ       0x90EE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DISPATCH_ਅਸਿੱਧਾ_ਬਫਰ_BINDING 0x90EF
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPUTE_SHADER_ਦੋਆਧਾਰੀ_ਅੰਕ             0x00000020
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DRAW_ਅਸਿੱਧਾ_ਬਫਰ           0x8F3F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DRAW_ਅਸਿੱਧਾ_ਬਫਰ_BINDING   0x8F43
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_ਇਕਸਾਰ_LOCATIONS          0x826E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_DEFAULT_ਚੌੜਾਈ      0x9310
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_DEFAULT_ਉਚਾਈ     0x9311
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_DEFAULT_SAMPLES    0x9313
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS 0x9314
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_FRAMEBUFFER_ਚੌੜਾਈ          0x9315
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_FRAMEBUFFER_ਉਚਾਈ         0x9316
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_FRAMEBUFFER_SAMPLES        0x9318
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਇਕਸਾਰ                        0x92E1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਇਕਸਾਰ_ਖੰਡ                  0x92E2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਪ੍ਰੋਗਰਾਮ_ਨਿਵੇਸ਼                  0x92E3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਪ੍ਰੋਗਰਾਮ_OUTPUT                 0x92E4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਬਫਰ_VARIABLE                0x92E5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SHADER_STORAGE_ਖੰਡ           0x92E6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ATOMIC_COUNTER_ਬਫਰ          0x92C0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TRANSFORM_FEEDBACK_VARYING     0x92F4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸਰਗਰਮ_RESOURCES               0x92F5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_NAME_ਲੰਮਾਈ                0x92F6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_ਅੰਕ_ਸਰਗਰਮ_VARIABLES       0x92F7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_NAME_ਲੰਮਾਈ                    0x92F9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TYPE                           0x92FA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ARRAY_ਮਾਪ                     0x92FB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਵਿੱਥ                         0x92FC
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਖੰਡ_ਸੂਚਕਾਂਕ                    0x92FD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ARRAY_STRIDE                   0x92FE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਮੈਟ੍ਰਿਕਸ_STRIDE                  0x92FF
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_IS_ਪੰਕਤੀ_MAJOR                   0x9300
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ATOMIC_COUNTER_ਬਫਰ_ਸੂਚਕਾਂਕ    0x9301
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਬਫਰ_BINDING                 0x9302
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਬਫਰ_ਅੰਕੜੇ_ਮਾਪ               0x9303
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਅੰਕ_ਸਰਗਰਮ_VARIABLES           0x9304
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸਰਗਰਮ_VARIABLES               0x9305
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_REFERENCED_BY_ਸ਼ੀਰਸ਼_SHADER    0x9306
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_REFERENCED_BY_FRAGMENT_SHADER  0x930A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_REFERENCED_BY_COMPUTE_SHADER   0x930B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸਿਖਰ_LEVEL_ARRAY_ਮਾਪ           0x930C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸਿਖਰ_LEVEL_ARRAY_STRIDE         0x930D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_LOCATION                       0x930E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸ਼ੀਰਸ਼_SHADER_ਦੋਆਧਾਰੀ_ਅੰਕ              0x00000001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAGMENT_SHADER_ਦੋਆਧਾਰੀ_ਅੰਕ            0x00000002
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ALL_SHADER_ਬਿੱਟ                0xFFFFFFFF
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਪ੍ਰੋਗਰਾਮ_SEPARABLE              0x8258
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸਰਗਰਮ_ਪ੍ਰੋਗਰਾਮ                 0x8259
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਪ੍ਰੋਗਰਾਮ_PIPELINE_BINDING       0x825A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ATOMIC_COUNTER_ਬਫਰ_BINDING  0x92C1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ATOMIC_COUNTER_ਬਫਰ_ਸ਼ੁਰੂ    0x92C2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ATOMIC_COUNTER_ਬਫਰ_ਮਾਪ     0x92C3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_ਸ਼ੀਰਸ਼_ATOMIC_COUNTER_BUFFERS 0x92CC
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS 0x92D0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS 0x92D1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_ਸ਼ੀਰਸ਼_ATOMIC_COUNTERS     0x92D2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_FRAGMENT_ATOMIC_COUNTERS   0x92D6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_COMBINED_ATOMIC_COUNTERS   0x92D7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_ATOMIC_COUNTER_ਬਫਰ_ਮਾਪ 0x92D8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_ATOMIC_COUNTER_ਬਫਰ_BINDINGS 0x92DC
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸਰਗਰਮ_ATOMIC_COUNTER_BUFFERS  0x92D9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNED_INT_ATOMIC_COUNTER    0x92DB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_IMAGE_UNITS                0x8F38
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_ਸ਼ੀਰਸ਼_IMAGE_UNIFORMS      0x90CA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_FRAGMENT_IMAGE_UNIFORMS    0x90CE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_COMBINED_IMAGE_UNIFORMS    0x90CF
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_IMAGE_BINDING_NAME             0x8F3A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_IMAGE_BINDING_LEVEL            0x8F3B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_IMAGE_BINDING_LAYERED          0x8F3C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_IMAGE_BINDING_LAYER            0x8F3D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_IMAGE_BINDING_ACCESS           0x8F3E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_IMAGE_BINDING_FORMAT           0x906E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸ਼ੀਰਸ਼_ATTRIB_ARRAY_BARRIER_ਦੋਆਧਾਰੀ_ਅੰਕ 0x00000001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ELEMENT_ARRAY_BARRIER_ਦੋਆਧਾਰੀ_ਅੰਕ      0x00000002
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਇਕਸਾਰ_BARRIER_ਦੋਆਧਾਰੀ_ਅੰਕ            0x00000004
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_FETCH_BARRIER_ਦੋਆਧਾਰੀ_ਅੰਕ      0x00000008
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SHADER_IMAGE_ACCESS_BARRIER_ਦੋਆਧਾਰੀ_ਅੰਕ 0x00000020
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMMAND_BARRIER_ਦੋਆਧਾਰੀ_ਅੰਕ            0x00000040
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_PIXEL_ਬਫਰ_BARRIER_ਦੋਆਧਾਰੀ_ਅੰਕ       0x00000080
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_UPDATE_BARRIER_ਦੋਆਧਾਰੀ_ਅੰਕ     0x00000100
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਬਫਰ_UPDATE_BARRIER_ਦੋਆਧਾਰੀ_ਅੰਕ      0x00000200
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_BARRIER_ਦੋਆਧਾਰੀ_ਅੰਕ        0x00000400
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TRANSFORM_FEEDBACK_BARRIER_ਦੋਆਧਾਰੀ_ਅੰਕ 0x00000800
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ATOMIC_COUNTER_BARRIER_ਦੋਆਧਾਰੀ_ਅੰਕ     0x00001000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ALL_BARRIER_ਬਿੱਟ               0xFFFFFFFF
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_IMAGE_2D                       0x904D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_IMAGE_3D                       0x904E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_IMAGE_CUBE                     0x9050
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_IMAGE_2D_ARRAY                 0x9053
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_INT_IMAGE_2D                   0x9058
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_INT_IMAGE_3D                   0x9059
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_INT_IMAGE_CUBE                 0x905B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_INT_IMAGE_2D_ARRAY             0x905E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNED_INT_IMAGE_2D          0x9063
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNED_INT_IMAGE_3D          0x9064
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNED_INT_IMAGE_CUBE        0x9066
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNED_INT_IMAGE_2D_ARRAY    0x9069
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_IMAGE_FORMAT_COMPATIBILITY_TYPE 0x90C7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_IMAGE_FORMAT_COMPATIBILITY_BY_ਮਾਪ 0x90C8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS 0x90C9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_READ_ONLY                      0x88B8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_WRITE_ONLY                     0x88B9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_READ_WRITE                     0x88BA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SHADER_STORAGE_ਬਫਰ          0x90D2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SHADER_STORAGE_ਬਫਰ_BINDING  0x90D3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SHADER_STORAGE_ਬਫਰ_ਸ਼ੁਰੂ    0x90D4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SHADER_STORAGE_ਬਫਰ_ਮਾਪ     0x90D5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_ਸ਼ੀਰਸ਼_SHADER_STORAGE_ਖੰਡਾਂ 0x90D6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_FRAGMENT_SHADER_STORAGE_ਖੰਡਾਂ 0x90DA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_COMPUTE_SHADER_STORAGE_ਖੰਡਾਂ 0x90DB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_COMBINED_SHADER_STORAGE_ਖੰਡਾਂ 0x90DC
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_SHADER_STORAGE_ਬਫਰ_BINDINGS 0x90DD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_SHADER_STORAGE_ਖੰਡ_ਮਾਪ  0x90DE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SHADER_STORAGE_ਬਫਰ_ਵਿੱਥ_ALIGNMENT 0x90DF
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SHADER_STORAGE_BARRIER_ਦੋਆਧਾਰੀ_ਅੰਕ     0x00002000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES 0x8F39
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਡੂੰਘਾਈ_STENCIL_TEXTURE_ਬਹੁਲਕ     0x90EA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_STENCIL_ਸੂਚਕਾਂਕ                  0x1901
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MIN_ਪ੍ਰੋਗਰਾਮ_TEXTURE_GATHER_ਵਿੱਥ 0x8E5E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_ਪ੍ਰੋਗਰਾਮ_TEXTURE_GATHER_ਵਿੱਥ 0x8E5F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SAMPLE_POSITION                0x8E50
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SAMPLE_ਨਕਾਬ                    0x8E51
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SAMPLE_ਨਕਾਬ_ਮੁੱਲ              0x8E52
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_2D_MULTISAMPLE         0x9100
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_SAMPLE_ਨਕਾਬ_ਸ਼ਬਦ          0x8E59
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_COLOR_TEXTURE_SAMPLES      0x910E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_ਡੂੰਘਾਈ_TEXTURE_SAMPLES      0x910F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_INTEGER_SAMPLES            0x9110
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_BINDING_2D_MULTISAMPLE 0x9104
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_SAMPLES                0x9106
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_FIXED_SAMPLE_LOCATIONS 0x9107
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_ਚੌੜਾਈ                  0x1000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_ਉਚਾਈ                 0x1001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_ਡੂੰਘਾਈ                  0x8071
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_ਅੰਦਰੂਨੀ_FORMAT        0x1003
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_RED_ਮਾਪ               0x805C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_GREEN_ਮਾਪ             0x805D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_BLUE_ਮਾਪ              0x805E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_ALPHA_ਮਾਪ             0x805F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_ਡੂੰਘਾਈ_ਮਾਪ             0x884A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_STENCIL_ਮਾਪ           0x88F1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_SHARED_ਮਾਪ            0x8C3F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_RED_TYPE               0x8C10
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_GREEN_TYPE             0x8C11
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_BLUE_TYPE              0x8C12
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_ALPHA_TYPE             0x8C13
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_ਡੂੰਘਾਈ_TYPE             0x8C16
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_COMPRESSED             0x86A1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SAMPLER_2D_MULTISAMPLE         0x9108
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_INT_SAMPLER_2D_MULTISAMPLE     0x9109
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE 0x910A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸ਼ੀਰਸ਼_ATTRIB_BINDING          0x82D4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸ਼ੀਰਸ਼_ATTRIB_RELATIVE_ਵਿੱਥ  0x82D5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸ਼ੀਰਸ਼_BINDING_ਭਾਜਕ         0x82D6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸ਼ੀਰਸ਼_BINDING_ਵਿੱਥ          0x82D7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸ਼ੀਰਸ਼_BINDING_STRIDE          0x82D8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸ਼ੀਰਸ਼_BINDING_ਬਫਰ          0x8F4F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_ਸ਼ੀਰਸ਼_ATTRIB_RELATIVE_ਵਿੱਥ 0x82D9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_ਸ਼ੀਰਸ਼_ATTRIB_BINDINGS     0x82DA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_ਸ਼ੀਰਸ਼_ATTRIB_STRIDE       0x82E5
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDISPATCHCOMPUTEPROC) (GLuint ਅੰਕ_groups_x, GLuint ਅੰਕ_groups_y, GLuint ਅੰਕ_groups_z);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDISPATCHCOMPUTEINDIRECTPROC) (GLintptr ਅਸਿੱਧਾ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDRAWARRAYSINDIRECTPROC) (GLenum ਬਹੁਲਕ, ਅਚਲ ਖਾਲੀ *ਅਸਿੱਧਾ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDRAWELEMENTSINDIRECTPROC) (GLenum ਬਹੁਲਕ, GLenum type, ਅਚਲ ਖਾਲੀ *ਅਸਿੱਧਾ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLFRAMEBUFFERPARAMETERIPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLint param);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETFRAMEBUFFERPARAMETERIVPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETPROGRAMINTERFACEIVPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLenum ਪ੍ਰੋਗਰਾਮ_Interface, GLenum pname, GLint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLuint (GL_APIENTRYP PFNGLGETPROGRAMRESOURCEINDEXPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLenum ਪ੍ਰੋਗਰਾਮ_Interface, ਅਚਲ GLchar *name);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETPROGRAMRESOURCENAMEPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLenum ਪ੍ਰੋਗਰਾਮ_Interface, GLuint ਸੂਚਕਾਂਕ, GLsizei buf_ਮਾਪ, GLsizei *ਲੰਮਾਈ, GLchar *name);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETPROGRAMRESOURCEIVPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLenum ਪ੍ਰੋਗਰਾਮ_Interface, GLuint ਸੂਚਕਾਂਕ, GLsizei prop_ਗਿਣਤੀ, ਅਚਲ GLenum *props, GLsizei ਗਿਣਤੀ_2, GLsizei *ਲੰਮਾਈ, GLint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLint (GL_APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLenum ਪ੍ਰੋਗਰਾਮ_Interface, ਅਚਲ GLchar *name);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLUSEPROGRAMSTAGESPROC) (GLuint pipeline, GLbitfield stages, GLuint ਪ੍ਰੋਗਰਾਮ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLACTIVESHADERPROGRAMPROC) (GLuint pipeline, GLuint ਪ੍ਰੋਗਰਾਮ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLuint (GL_APIENTRYP PFNGLCREATESHADERPROGRAMVPROC) (GLenum type, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLchar *ਅਚਲ*ਲੜੀਆਂ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLBINDPROGRAMPIPELINEPROC) (GLuint pipeline);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDELETEPROGRAMPIPELINESPROC) (GLsizei n, ਅਚਲ GLuint *pipelines);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGENPROGRAMPIPELINESPROC) (GLsizei n, GLuint *pipelines);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLboolean (GL_APIENTRYP PFNGLISPROGRAMPIPELINEPROC) (GLuint pipeline);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETPROGRAMPIPELINEIVPROC) (GLuint pipeline, GLenum pname, GLint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1IPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLint v0);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2IPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLint v0, GLint v1);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3IPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLint v0, GLint v1, GLint v2);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4IPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UIPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLuint v0);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UIPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLuint v0, GLuint v1);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UIPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLuint v0, GLuint v1, GLuint v2);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UIPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1FPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLfloat v0);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2FPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLfloat v0, GLfloat v1);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3FPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4FPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1IVPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLint *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2IVPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLint *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3IVPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLint *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4IVPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLint *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1UIVPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLuint *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2UIVPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLuint *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3UIVPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLuint *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4UIVPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLuint *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPROGRAMUNIFORM1FVPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLfloat *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPROGRAMUNIFORM2FVPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLfloat *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPROGRAMUNIFORM3FVPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLfloat *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPROGRAMUNIFORM4FVPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLfloat *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2FVPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3FVPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4FVPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLVALIDATEPROGRAMPIPELINEPROC) (GLuint pipeline);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETPROGRAMPIPELINEINFOLOGPROC) (GLuint pipeline, GLsizei buf_ਮਾਪ, GLsizei *ਲੰਮਾਈ, GLchar *infoLog);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLBINDIMAGETEXTUREPROC) (GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETBOOLEANI_VPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLuint ਸੂਚਕਾਂਕ, GLboolean *ਅੰਕੜੇ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLMEMORYBARRIERPROC) (GLbitfield barriers);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLMEMORYBARRIERBYREGIONPROC) (GLbitfield barriers);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLTEXSTORAGE2DMULTISAMPLEPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLsizei samples, GLenum internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLboolean fixedsamplelocations);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETMULTISAMPLEFVPROC) (GLenum pname, GLuint ਸੂਚਕਾਂਕ, GLfloat *val);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLSAMPLEMASKIPROC) (GLuint ਨਕਾਬ_ਸੰਖਿਆ, GLbitfield ਨਕਾਬ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETTEXLEVELPARAMETERIVPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLint level, GLenum pname, GLint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETTEXLEVELPARAMETERFVPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLint level, GLenum pname, GLfloat *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLBINDVERTEXBUFFERPROC) (GLuint bindingindex, GLuint ਬਫਰ_2, GLintptr ਵਿੱਥ_2, GLsizei stride);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLVERTEXATTRIBFORMATPROC) (GLuint attribindex, GLint ਮਾਪ, GLenum type, GLboolean normalized, GLuint relativeoffset);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLVERTEXATTRIBIFORMATPROC) (GLuint attribindex, GLint ਮਾਪ, GLenum type, GLuint relativeoffset);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLVERTEXATTRIBBINDINGPROC) (GLuint attribindex, GLuint bindingindex);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLVERTEXBINDINGDIVISORPROC) (GLuint bindingindex, GLuint ਭਾਜਕ);
#ਜੇ GL_GLES_PROTOTYPES
GL_APICALL ਖਾਲੀ GL_APIENTRY glDispatchCompute (GLuint ਅੰਕ_groups_x, GLuint ਅੰਕ_groups_y, GLuint ਅੰਕ_groups_z);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Dispatch_Compute_ਅਸਿੱਧਾ (GLintptr ਅਸਿੱਧਾ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Draw_Arrays_ਅਸਿੱਧਾ (GLenum ਬਹੁਲਕ, ਅਚਲ ਖਾਲੀ *ਅਸਿੱਧਾ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Draw_Elements_ਅਸਿੱਧਾ (GLenum ਬਹੁਲਕ, GLenum type, ਅਚਲ ਖਾਲੀ *ਅਸਿੱਧਾ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glFramebufferParameteri (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLint param);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetFramebufferParameteriv (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLint *params);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Get_ਪ੍ਰੋਗਰਾਮ_Interfaceiv (GLuint ਪ੍ਰੋਗਰਾਮ, GLenum ਪ੍ਰੋਗਰਾਮ_Interface, GLenum pname, GLint *params);
GL_APICALL GLuint GL_APIENTRY gl_Get_ਪ੍ਰੋਗਰਾਮ_Resource_ਸੂਚਕਾਂਕ (GLuint ਪ੍ਰੋਗਰਾਮ, GLenum ਪ੍ਰੋਗਰਾਮ_Interface, ਅਚਲ GLchar *name);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Get_ਪ੍ਰੋਗਰਾਮ_Resource_Name (GLuint ਪ੍ਰੋਗਰਾਮ, GLenum ਪ੍ਰੋਗਰਾਮ_Interface, GLuint ਸੂਚਕਾਂਕ, GLsizei buf_ਮਾਪ, GLsizei *ਲੰਮਾਈ, GLchar *name);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Get_ਪ੍ਰੋਗਰਾਮ_Resourceiv (GLuint ਪ੍ਰੋਗਰਾਮ, GLenum ਪ੍ਰੋਗਰਾਮ_Interface, GLuint ਸੂਚਕਾਂਕ, GLsizei prop_ਗਿਣਤੀ, ਅਚਲ GLenum *props, GLsizei ਗਿਣਤੀ_2, GLsizei *ਲੰਮਾਈ, GLint *params);
GL_APICALL GLint GL_APIENTRY gl_Get_ਪ੍ਰੋਗਰਾਮ_Resource_Location (GLuint ਪ੍ਰੋਗਰਾਮ, GLenum ਪ੍ਰੋਗਰਾਮ_Interface, ਅਚਲ GLchar *name);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Use_ਪ੍ਰੋਗਰਾਮ_Stages (GLuint pipeline, GLbitfield stages, GLuint ਪ੍ਰੋਗਰਾਮ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਸਰਗਰਮ_Shader_ਪ੍ਰੋਗਰਾਮ (GLuint pipeline, GLuint ਪ੍ਰੋਗਰਾਮ);
GL_APICALL GLuint GL_APIENTRY glCreateShaderProgramv (GLenum type, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLchar *ਅਚਲ*ਲੜੀਆਂ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Bind_ਪ੍ਰੋਗਰਾਮ_Pipeline (GLuint pipeline);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Delete_ਪ੍ਰੋਗਰਾਮ_Pipelines (GLsizei n, ਅਚਲ GLuint *pipelines);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Gen_ਪ੍ਰੋਗਰਾਮ_Pipelines (GLsizei n, GLuint *pipelines);
GL_APICALL GLboolean GL_APIENTRY gl_Is_ਪ੍ਰੋਗਰਾਮ_Pipeline (GLuint pipeline);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Get_ਪ੍ਰੋਗਰਾਮ_Pipelineiv (GLuint pipeline, GLenum pname, GLint *params);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਪ੍ਰੋਗਰਾਮ_Uniform1i (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLint v0);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਪ੍ਰੋਗਰਾਮ_Uniform2i (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLint v0, GLint v1);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਪ੍ਰੋਗਰਾਮ_Uniform3i (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLint v0, GLint v1, GLint v2);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਪ੍ਰੋਗਰਾਮ_Uniform4i (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਪ੍ਰੋਗਰਾਮ_Uniform1ui (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLuint v0);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਪ੍ਰੋਗਰਾਮ_Uniform2ui (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLuint v0, GLuint v1);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਪ੍ਰੋਗਰਾਮ_Uniform3ui (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLuint v0, GLuint v1, GLuint v2);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਪ੍ਰੋਗਰਾਮ_Uniform4ui (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਪ੍ਰੋਗਰਾਮ_Uniform1f (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLfloat v0);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਪ੍ਰੋਗਰਾਮ_Uniform2f (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLfloat v0, GLfloat v1);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਪ੍ਰੋਗਰਾਮ_Uniform3f (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਪ੍ਰੋਗਰਾਮ_Uniform4f (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਪ੍ਰੋਗਰਾਮ_Uniform1iv (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLint *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਪ੍ਰੋਗਰਾਮ_Uniform2iv (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLint *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਪ੍ਰੋਗਰਾਮ_Uniform3iv (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLint *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਪ੍ਰੋਗਰਾਮ_Uniform4iv (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLint *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਪ੍ਰੋਗਰਾਮ_Uniform1uiv (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLuint *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਪ੍ਰੋਗਰਾਮ_Uniform2uiv (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLuint *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਪ੍ਰੋਗਰਾਮ_Uniform3uiv (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLuint *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਪ੍ਰੋਗਰਾਮ_Uniform4uiv (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLuint *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਪ੍ਰੋਗਰਾਮ_Uniform1fv (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLfloat *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਪ੍ਰੋਗਰਾਮ_Uniform2fv (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLfloat *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਪ੍ਰੋਗਰਾਮ_Uniform3fv (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLfloat *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਪ੍ਰੋਗਰਾਮ_Uniform4fv (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLfloat *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਪ੍ਰੋਗਰਾਮ_ਇਕਸਾਰ_Matrix2fv (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਪ੍ਰੋਗਰਾਮ_ਇਕਸਾਰ_Matrix3fv (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਪ੍ਰੋਗਰਾਮ_ਇਕਸਾਰ_Matrix4fv (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਪ੍ਰੋਗਰਾਮ_ਇਕਸਾਰ_Matrix2x3fv (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਪ੍ਰੋਗਰਾਮ_ਇਕਸਾਰ_Matrix3x2fv (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਪ੍ਰੋਗਰਾਮ_ਇਕਸਾਰ_Matrix2x4fv (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਪ੍ਰੋਗਰਾਮ_ਇਕਸਾਰ_Matrix4x2fv (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਪ੍ਰੋਗਰਾਮ_ਇਕਸਾਰ_Matrix3x4fv (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਪ੍ਰੋਗਰਾਮ_ਇਕਸਾਰ_Matrix4x3fv (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei ਗਿਣਤੀ_2, GLboolean transpose, ਅਚਲ GLfloat *ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Validate_ਪ੍ਰੋਗਰਾਮ_Pipeline (GLuint pipeline);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Get_ਪ੍ਰੋਗਰਾਮ_Pipeline_Info_Log (GLuint pipeline, GLsizei buf_ਮਾਪ, GLsizei *ਲੰਮਾਈ, GLchar *infoLog);
GL_APICALL ਖਾਲੀ GL_APIENTRY glBindImageTexture (GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetBooleani_v (GLenum ਨਿਸ਼ਾਨਾ, GLuint ਸੂਚਕਾਂਕ, GLboolean *ਅੰਕੜੇ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਸਮ੍ਰਿਤੀ_Barrier (GLbitfield barriers);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਸਮ੍ਰਿਤੀ_Barrier_By_Region (GLbitfield barriers);
GL_APICALL ਖਾਲੀ GL_APIENTRY glTexStorage2DMultisample (GLenum ਨਿਸ਼ਾਨਾ, GLsizei samples, GLenum internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLboolean fixedsamplelocations);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetMultisamplefv (GLenum pname, GLuint ਸੂਚਕਾਂਕ, GLfloat *val);
GL_APICALL ਖਾਲੀ GL_APIENTRY glSampleMaski (GLuint ਨਕਾਬ_ਸੰਖਿਆ, GLbitfield ਨਕਾਬ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetTexLevelParameteriv (GLenum ਨਿਸ਼ਾਨਾ, GLint level, GLenum pname, GLint *params);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetTexLevelParameterfv (GLenum ਨਿਸ਼ਾਨਾ, GLint level, GLenum pname, GLfloat *params);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Bind_ਸ਼ੀਰਸ਼_ਬਫਰ (GLuint bindingindex, GLuint ਬਫਰ_2, GLintptr ਵਿੱਥ_2, GLsizei stride);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਸ਼ੀਰਸ਼_Attrib_Format (GLuint attribindex, GLint ਮਾਪ, GLenum type, GLboolean normalized, GLuint relativeoffset);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਸ਼ੀਰਸ਼_Attrib_IFormat (GLuint attribindex, GLint ਮਾਪ, GLenum type, GLuint relativeoffset);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਸ਼ੀਰਸ਼_Attrib_Binding (GLuint attribindex, GLuint bindingindex);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਸ਼ੀਰਸ਼_Binding_ਭਾਜਕ (GLuint bindingindex, GLuint ਭਾਜਕ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* GL_ES_VERSION_3_1 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_ES_ਸੰਸਕਰਣ_3_2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ES_ਸੰਸਕਰਣ_3_2 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRY  *GLDEBUGPROC)(GLenum ਸਰੋਤ,GLenum type,GLuint id,GLenum severity,GLsizei ਲੰਮਾਈ,ਅਚਲ GLchar *ਸੁਨੇਹਾ,ਅਚਲ ਖਾਲੀ *userParam);
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MULTISAMPLE_ਸਤਰ_ਚੌੜਾਈ_RANGE   0x9381
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MULTISAMPLE_ਸਤਰ_ਚੌੜਾਈ_GRANULARITY 0x9382
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MULTIPLY                       0x9294
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SCREEN                         0x9295
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_OVERLAY                        0x9296
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DARKEN                         0x9297
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_LIGHTEN                        0x9298
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLORDODGE                     0x9299
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COLORBURN                      0x929A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_HARDLIGHT                      0x929B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SOFTLIGHT                      0x929C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DIFFERENCE                     0x929E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_EXCLUSION                      0x92A0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_HSL_HUE                        0x92AD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_HSL_SATURATION                 0x92AE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_HSL_COLOR                      0x92AF
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_HSL_LUMINOSITY                 0x92B0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DEBUG_OUTPUT_SYNCHRONOUS       0x8242
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DEBUG_ਅਗਲਾ_LOGGED_ਸੁਨੇਹਾ_ਲੰਮਾਈ 0x8243
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DEBUG_CALLBACK_FUNCTION        0x8244
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DEBUG_CALLBACK_USER_PARAM      0x8245
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DEBUG_ਸਰੋਤ_API               0x8246
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DEBUG_ਸਰੋਤ_ਖਿੜਕੀ_SYSTEM     0x8247
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DEBUG_ਸਰੋਤ_SHADER_COMPILER   0x8248
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DEBUG_ਸਰੋਤ_ਤੀਜਾ_PARTY       0x8249
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DEBUG_ਸਰੋਤ_APPLICATION       0x824A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DEBUG_ਸਰੋਤ_OTHER             0x824B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DEBUG_TYPE_ERROR               0x824C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR 0x824D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR  0x824E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DEBUG_TYPE_PORTABILITY         0x824F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DEBUG_TYPE_PERFORMANCE         0x8250
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DEBUG_TYPE_OTHER               0x8251
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DEBUG_TYPE_MARKER              0x8268
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DEBUG_TYPE_ਧੱਕੋ_ਸਮੂਹ          0x8269
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DEBUG_TYPE_ਕੱਢੋ_ਸਮੂਹ           0x826A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DEBUG_SEVERITY_NOTIFICATION    0x826B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_DEBUG_ਸਮੂਹ_ਢੇਰ_ਡੂੰਘਾਈ    0x826C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DEBUG_ਸਮੂਹ_ਢੇਰ_ਡੂੰਘਾਈ        0x826D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਬਫਰ                         0x82E0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SHADER                         0x82E1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਪ੍ਰੋਗਰਾਮ                        0x82E2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸ਼ੀਰਸ਼_ARRAY                   0x8074
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_QUERY                          0x82E3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਪ੍ਰੋਗਰਾਮ_PIPELINE               0x82E4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SAMPLER                        0x82E6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_LABEL_ਲੰਮਾਈ               0x82E8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_DEBUG_ਸੁਨੇਹਾ_ਲੰਮਾਈ       0x9143
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_DEBUG_LOGGED_MESSAGES      0x9144
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DEBUG_LOGGED_MESSAGES          0x9145
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DEBUG_SEVERITY_ਉੱਚਾ            0x9146
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DEBUG_SEVERITY_MEDIUM          0x9147
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DEBUG_SEVERITY_ਨੀਵਾਂ             0x9148
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_DEBUG_OUTPUT                   0x92E0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_CONTEXT_FLAG_DEBUG_ਦੋਆਧਾਰੀ_ਅੰਕ         0x00000002
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਢੇਰ_ਉਛਾਲ                 0x0503
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਢੇਰ_UNDERFLOW                0x0504
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_GEOMETRY_SHADER                0x8DD9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_GEOMETRY_SHADER_ਦੋਆਧਾਰੀ_ਅੰਕ            0x00000004
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_GEOMETRY_VERTICES_ਬਾਹਰਲਾ          0x8916
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_GEOMETRY_ਨਿਵੇਸ਼_TYPE            0x8917
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_GEOMETRY_OUTPUT_TYPE           0x8918
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_GEOMETRY_SHADER_INVOCATIONS    0x887F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_LAYER_PROVOKING_ਸ਼ੀਰਸ਼         0x825E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸਤਰਾਂ_ADJACENCY                0x000A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਸਤਰ_STRIP_ADJACENCY           0x000B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TRIANGLES_ADJACENCY            0x000C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TRIANGLE_STRIP_ADJACENCY       0x000D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_GEOMETRY_ਇਕਸਾਰ_COMPONENTS 0x8DDF
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_GEOMETRY_ਇਕਸਾਰ_ਖੰਡਾਂ    0x8A2C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_COMBINED_GEOMETRY_ਇਕਸਾਰ_COMPONENTS 0x8A32
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_GEOMETRY_ਨਿਵੇਸ਼_COMPONENTS  0x9123
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_GEOMETRY_OUTPUT_COMPONENTS 0x9124
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_GEOMETRY_OUTPUT_VERTICES   0x8DE0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_GEOMETRY_ਕੁੱਲ_OUTPUT_COMPONENTS 0x8DE1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_GEOMETRY_SHADER_INVOCATIONS 0x8E5A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS 0x8C29
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS 0x92CF
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_GEOMETRY_ATOMIC_COUNTERS   0x92D5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_GEOMETRY_IMAGE_UNIFORMS    0x90CD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_GEOMETRY_SHADER_STORAGE_ਖੰਡਾਂ 0x90D7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਪਹਿਲਾ_ਸ਼ੀਰਸ਼_CONVENTION        0x8E4D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਆਖਰੀ_ਸ਼ੀਰਸ਼_CONVENTION         0x8E4E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNDEFINED_ਸ਼ੀਰਸ਼               0x8260
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_PRIMITIVES_GENERATED           0x8C87
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_DEFAULT_LAYERS     0x9312
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_FRAMEBUFFER_LAYERS         0x9317
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS 0x8DA8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_ATTACHMENT_LAYERED 0x8DA7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_REFERENCED_BY_GEOMETRY_SHADER  0x9309
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_PRIMITIVE_BOUNDING_BOX         0x92BE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_CONTEXT_FLAG_ROBUST_ACCESS_ਦੋਆਧਾਰੀ_ਅੰਕ 0x00000004
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_CONTEXT_FLAGS                  0x821E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_LOSE_CONTEXT_ON_RESET          0x8252
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_GUILTY_CONTEXT_RESET           0x8253
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_INNOCENT_CONTEXT_RESET         0x8254
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNKNOWN_CONTEXT_RESET          0x8255
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RESET_NOTIFICATION_STRATEGY    0x8256
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_NO_RESET_NOTIFICATION          0x8261
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_CONTEXT_ਗੁਆਚਾ                   0x0507
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SAMPLE_SHADING                 0x8C36
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MIN_SAMPLE_SHADING_ਮੁੱਲ       0x8C37
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MIN_FRAGMENT_INTERPOLATION_ਵਿੱਥ 0x8E5B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_FRAGMENT_INTERPOLATION_ਵਿੱਥ 0x8E5C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAGMENT_INTERPOLATION_ਵਿੱਥ_ਬਿੱਟ 0x8E5D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_PATCHES                        0x000E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_PATCH_VERTICES                 0x8E72
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TESS_CONTROL_OUTPUT_VERTICES   0x8E75
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TESS_GEN_ਬਹੁਲਕ                  0x8E76
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TESS_GEN_SPACING               0x8E77
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TESS_GEN_ਸ਼ੀਰਸ਼_ਕ੍ਰਮ          0x8E78
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TESS_GEN_ਬਿੰਦੂ_ਬਹੁਲਕ            0x8E79
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ISOLINES                       0x8E7A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_QUADS                          0x0007
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRACTIONAL_ODD                 0x8E7B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRACTIONAL_EVEN                0x8E7C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_PATCH_VERTICES             0x8E7D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_TESS_GEN_LEVEL             0x8E7E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_TESS_CONTROL_ਇਕਸਾਰ_COMPONENTS 0x8E7F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_TESS_EVALUATION_ਇਕਸਾਰ_COMPONENTS 0x8E80
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS 0x8E81
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS 0x8E82
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS 0x8E83
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_TESS_PATCH_COMPONENTS      0x8E84
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_TESS_CONTROL_ਕੁੱਲ_OUTPUT_COMPONENTS 0x8E85
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS 0x8E86
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_TESS_CONTROL_ਇਕਸਾਰ_ਖੰਡਾਂ 0x8E89
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_TESS_EVALUATION_ਇਕਸਾਰ_ਖੰਡਾਂ 0x8E8A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_TESS_CONTROL_ਨਿਵੇਸ਼_COMPONENTS 0x886C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_TESS_EVALUATION_ਨਿਵੇਸ਼_COMPONENTS 0x886D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_COMBINED_TESS_CONTROL_ਇਕਸਾਰ_COMPONENTS 0x8E1E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_COMBINED_TESS_EVALUATION_ਇਕਸਾਰ_COMPONENTS 0x8E1F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS 0x92CD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS 0x92CE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS 0x92D3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS 0x92D4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS 0x90CB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS 0x90CC
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_TESS_CONTROL_SHADER_STORAGE_ਖੰਡਾਂ 0x90D8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_TESS_EVALUATION_SHADER_STORAGE_ਖੰਡਾਂ 0x90D9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED 0x8221
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_IS_ਪ੍ਰਤੀ_PATCH                   0x92E7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_REFERENCED_BY_TESS_CONTROL_SHADER 0x9307
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_REFERENCED_BY_TESS_EVALUATION_SHADER 0x9308
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TESS_CONTROL_SHADER            0x8E88
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TESS_EVALUATION_SHADER         0x8E87
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TESS_CONTROL_SHADER_ਦੋਆਧਾਰੀ_ਅੰਕ        0x00000008
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TESS_EVALUATION_SHADER_ਦੋਆਧਾਰੀ_ਅੰਕ     0x00000010
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_BORDER_COLOR           0x1004
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_CLAMP_ਮੰਜ਼ਿਲ_BORDER                0x812D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_ਬਫਰ                 0x8C2A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_ਬਫਰ_BINDING         0x8C2A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_MAX_TEXTURE_ਬਫਰ_ਮਾਪ        0x8C2B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_BINDING_ਬਫਰ         0x8C2C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_ਬਫਰ_ਅੰਕੜੇ_STORE_BINDING 0x8C2D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_ਬਫਰ_ਵਿੱਥ_ALIGNMENT 0x919F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SAMPLER_ਬਫਰ                 0x8DC2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_INT_SAMPLER_ਬਫਰ             0x8DD0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNED_INT_SAMPLER_ਬਫਰ    0x8DD8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_IMAGE_ਬਫਰ                   0x9051
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_INT_IMAGE_ਬਫਰ               0x905C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNED_INT_IMAGE_ਬਫਰ      0x9067
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_ਬਫਰ_ਵਿੱਥ          0x919D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_ਬਫਰ_ਮਾਪ            0x919E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_RGBA_ASTC_4x4       0x93B0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_RGBA_ASTC_5x4       0x93B1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_RGBA_ASTC_5x5       0x93B2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_RGBA_ASTC_6x5       0x93B3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_RGBA_ASTC_6x6       0x93B4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_RGBA_ASTC_8x5       0x93B5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_RGBA_ASTC_8x6       0x93B6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_RGBA_ASTC_8x8       0x93B7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_RGBA_ASTC_10x5      0x93B8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_RGBA_ASTC_10x6      0x93B9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_RGBA_ASTC_10x8      0x93BA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_RGBA_ASTC_10x10     0x93BB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_RGBA_ASTC_12x10     0x93BC
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_RGBA_ASTC_12x12     0x93BD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4 0x93D0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4 0x93D1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5 0x93D2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5 0x93D3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6 0x93D4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5 0x93D5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6 0x93D6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8 0x93D7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5 0x93D8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6 0x93D9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8 0x93DA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10 0x93DB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10 0x93DC
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12 0x93DD
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_CUBE_MAP_ARRAY         0x9009
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_BINDING_CUBE_MAP_ARRAY 0x900A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SAMPLER_CUBE_MAP_ARRAY         0x900C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW  0x900D
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_INT_SAMPLER_CUBE_MAP_ARRAY     0x900E
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY 0x900F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_IMAGE_CUBE_MAP_ARRAY           0x9054
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_INT_IMAGE_CUBE_MAP_ARRAY       0x905F
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY 0x906A
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_2D_MULTISAMPLE_ARRAY   0x9102
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY 0x9105
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_SAMPLER_2D_MULTISAMPLE_ARRAY   0x910B
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910D
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLBLENDBARRIERPROC) (ਖਾਲੀ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLCOPYIMAGESUBDATAPROC) (GLuint srcName, GLenum src_ਨਿਸ਼ਾਨਾ, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dst_ਨਿਸ਼ਾਨਾ, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei src_ਚੌੜਾਈ, GLsizei src_ਉਚਾਈ, GLsizei src_ਡੂੰਘਾਈ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDEBUGMESSAGECONTROLPROC) (GLenum ਸਰੋਤ, GLenum type, GLenum severity, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLuint *ids, GLboolean enabled);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDEBUGMESSAGEINSERTPROC) (GLenum ਸਰੋਤ, GLenum type, GLuint id, GLenum severity, GLsizei ਲੰਮਾਈ, ਅਚਲ GLchar *buf);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDEBUGMESSAGECALLBACKPROC) (GLDEBUGPROC callback, ਅਚਲ ਖਾਲੀ *userParam);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLuint (GL_APIENTRYP PFNGLGETDEBUGMESSAGELOGPROC) (GLuint ਗਿਣਤੀ_2, GLsizei buf_ਮਾਪ, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *ਸੁਨੇਹਾ_Log);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPUSHDEBUGGROUPPROC) (GLenum ਸਰੋਤ, GLuint id, GLsizei ਲੰਮਾਈ, ਅਚਲ GLchar *ਸੁਨੇਹਾ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPOPDEBUGGROUPPROC) (ਖਾਲੀ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLOBJECTLABELPROC) (GLenum identifier, GLuint name, GLsizei ਲੰਮਾਈ, ਅਚਲ GLchar *label);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETOBJECTLABELPROC) (GLenum identifier, GLuint name, GLsizei buf_ਮਾਪ, GLsizei *ਲੰਮਾਈ, GLchar *label);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLOBJECTPTRLABELPROC) (ਅਚਲ ਖਾਲੀ *ptr, GLsizei ਲੰਮਾਈ, ਅਚਲ GLchar *label);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETOBJECTPTRLABELPROC) (ਅਚਲ ਖਾਲੀ *ptr, GLsizei buf_ਮਾਪ, GLsizei *ਲੰਮਾਈ, GLchar *label);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETPOINTERVPROC) (GLenum pname, ਖਾਲੀ **params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLENABLEIPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLuint ਸੂਚਕਾਂਕ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDISABLEIPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLuint ਸੂਚਕਾਂਕ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLBLENDEQUATIONIPROC) (GLuint buf, GLenum ਬਹੁਲਕ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEIPROC) (GLuint buf, GLenum ਬਹੁਲਕ_RGB, GLenum ਬਹੁਲਕ_Alpha);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLBLENDFUNCIPROC) (GLuint buf, GLenum src, GLenum dst);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEIPROC) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLCOLORMASKIPROC) (GLuint ਸੂਚਕਾਂਕ, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLboolean (GL_APIENTRYP PFNGLISENABLEDIPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLuint ਸੂਚਕਾਂਕ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDRAWELEMENTSBASEVERTEXPROC) (GLenum ਬਹੁਲਕ, GLsizei ਗਿਣਤੀ_2, GLenum type, ਅਚਲ ਖਾਲੀ *indices, GLint basevertex);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC) (GLenum ਬਹੁਲਕ, GLuint ਸ਼ੁਰੂ, GLuint ਸਿਰਾ, GLsizei ਗਿਣਤੀ_2, GLenum type, ਅਚਲ ਖਾਲੀ *indices, GLint basevertex);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC) (GLenum ਬਹੁਲਕ, GLsizei ਗਿਣਤੀ_2, GLenum type, ਅਚਲ ਖਾਲੀ *indices, GLsizei instancecount, GLint basevertex);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTUREPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum attachment, GLuint texture, GLint level);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPRIMITIVEBOUNDINGBOXPROC) (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLenum (GL_APIENTRYP PFNGLGETGRAPHICSRESETSTATUSPROC) (ਖਾਲੀ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLREADNPIXELSPROC) (GLint x, GLint y, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLenum format, GLenum type, GLsizei buf_ਮਾਪ, ਖਾਲੀ *ਅੰਕੜੇ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETNUNIFORMFVPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei buf_ਮਾਪ, GLfloat *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETNUNIFORMIVPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei buf_ਮਾਪ, GLint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETNUNIFORMUIVPROC) (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei buf_ਮਾਪ, GLuint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLMINSAMPLESHADINGPROC) (GLfloat ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLPATCHPARAMETERIPROC) (GLenum pname, GLint ਮੁੱਲ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLTEXPARAMETERIIVPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, ਅਚਲ GLint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLTEXPARAMETERIUIVPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, ਅਚਲ GLuint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETTEXPARAMETERIIVPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETTEXPARAMETERIUIVPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLuint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIIVPROC) (GLuint sampler, GLenum pname, ਅਚਲ GLint *param);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLSAMPLERPARAMETERIUIVPROC) (GLuint sampler, GLenum pname, ਅਚਲ GLuint *param);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIIVPROC) (GLuint sampler, GLenum pname, GLint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLGETSAMPLERPARAMETERIUIVPROC) (GLuint sampler, GLenum pname, GLuint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLTEXBUFFERPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum internalformat, GLuint ਬਫਰ_2);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLTEXBUFFERRANGEPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLenum internalformat, GLuint ਬਫਰ_2, GLintptr ਵਿੱਥ_2, GLsizeiptr ਮਾਪ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (GL_APIENTRYP PFNGLTEXSTORAGE3DMULTISAMPLEPROC) (GLenum ਨਿਸ਼ਾਨਾ, GLsizei samples, GLenum internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLsizei ਡੂੰਘਾਈ_2, GLboolean fixedsamplelocations);
#ਜੇ GL_GLES_PROTOTYPES
GL_APICALL ਖਾਲੀ GL_APIENTRY glBlendBarrier (ਖਾਲੀ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Copy_Image_Sub_ਅੰਕੜੇ (GLuint srcName, GLenum src_ਨਿਸ਼ਾਨਾ, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dst_ਨਿਸ਼ਾਨਾ, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei src_ਚੌੜਾਈ, GLsizei src_ਉਚਾਈ, GLsizei src_ਡੂੰਘਾਈ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Debug_ਸੁਨੇਹਾ_Control (GLenum ਸਰੋਤ, GLenum type, GLenum severity, GLsizei ਗਿਣਤੀ_2, ਅਚਲ GLuint *ids, GLboolean enabled);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Debug_ਸੁਨੇਹਾ_ਪਾਓ (GLenum ਸਰੋਤ, GLenum type, GLuint id, GLenum severity, GLsizei ਲੰਮਾਈ, ਅਚਲ GLchar *buf);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Debug_ਸੁਨੇਹਾ_Callback (GLDEBUGPROC callback, ਅਚਲ ਖਾਲੀ *userParam);
GL_APICALL GLuint GL_APIENTRY gl_Get_Debug_ਸੁਨੇਹਾ_Log (GLuint ਗਿਣਤੀ_2, GLsizei buf_ਮਾਪ, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *ਸੁਨੇਹਾ_Log);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਧੱਕੋ_Debug_ਸਮੂਹ (GLenum ਸਰੋਤ, GLuint id, GLsizei ਲੰਮਾਈ, ਅਚਲ GLchar *ਸੁਨੇਹਾ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_ਕੱਢੋ_Debug_ਸਮੂਹ (ਖਾਲੀ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glObjectLabel (GLenum identifier, GLuint name, GLsizei ਲੰਮਾਈ, ਅਚਲ GLchar *label);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetObjectLabel (GLenum identifier, GLuint name, GLsizei buf_ਮਾਪ, GLsizei *ਲੰਮਾਈ, GLchar *label);
GL_APICALL ਖਾਲੀ GL_APIENTRY glObjectPtrLabel (ਅਚਲ ਖਾਲੀ *ptr, GLsizei ਲੰਮਾਈ, ਅਚਲ GLchar *label);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetObjectPtrLabel (ਅਚਲ ਖਾਲੀ *ptr, GLsizei buf_ਮਾਪ, GLsizei *ਲੰਮਾਈ, GLchar *label);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetPointerv (GLenum pname, ਖਾਲੀ **params);
GL_APICALL ਖਾਲੀ GL_APIENTRY glEnablei (GLenum ਨਿਸ਼ਾਨਾ, GLuint ਸੂਚਕਾਂਕ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glDisablei (GLenum ਨਿਸ਼ਾਨਾ, GLuint ਸੂਚਕਾਂਕ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glBlendEquationi (GLuint buf, GLenum ਬਹੁਲਕ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glBlendEquationSeparatei (GLuint buf, GLenum ਬਹੁਲਕ_RGB, GLenum ਬਹੁਲਕ_Alpha);
GL_APICALL ਖਾਲੀ GL_APIENTRY glBlendFunci (GLuint buf, GLenum src, GLenum dst);
GL_APICALL ਖਾਲੀ GL_APIENTRY glBlendFuncSeparatei (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
GL_APICALL ਖਾਲੀ GL_APIENTRY glColorMaski (GLuint ਸੂਚਕਾਂਕ, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
GL_APICALL GLboolean GL_APIENTRY glIsEnabledi (GLenum ਨਿਸ਼ਾਨਾ, GLuint ਸੂਚਕਾਂਕ);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Draw_Elements_ਅਧਾਰ_ਸ਼ੀਰਸ਼ (GLenum ਬਹੁਲਕ, GLsizei ਗਿਣਤੀ_2, GLenum type, ਅਚਲ ਖਾਲੀ *indices, GLint basevertex);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Draw_Range_Elements_ਅਧਾਰ_ਸ਼ੀਰਸ਼ (GLenum ਬਹੁਲਕ, GLuint ਸ਼ੁਰੂ, GLuint ਸਿਰਾ, GLsizei ਗਿਣਤੀ_2, GLenum type, ਅਚਲ ਖਾਲੀ *indices, GLint basevertex);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Draw_Elements_Instanced_ਅਧਾਰ_ਸ਼ੀਰਸ਼ (GLenum ਬਹੁਲਕ, GLsizei ਗਿਣਤੀ_2, GLenum type, ਅਚਲ ਖਾਲੀ *indices, GLsizei instancecount, GLint basevertex);
GL_APICALL ਖਾਲੀ GL_APIENTRY glFramebufferTexture (GLenum ਨਿਸ਼ਾਨਾ, GLenum attachment, GLuint texture, GLint level);
GL_APICALL ਖਾਲੀ GL_APIENTRY glPrimitiveBoundingBox (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
GL_APICALL GLenum GL_APIENTRY gl_Get_Graphics_Reset_ਸਥਿਤੀ (ਖਾਲੀ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glReadnPixels (GLint x, GLint y, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLenum format, GLenum type, GLsizei buf_ਮਾਪ, ਖਾਲੀ *ਅੰਕੜੇ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetnUniformfv (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei buf_ਮਾਪ, GLfloat *params);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetnUniformiv (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei buf_ਮਾਪ, GLint *params);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetnUniformuiv (GLuint ਪ੍ਰੋਗਰਾਮ, GLint location, GLsizei buf_ਮਾਪ, GLuint *params);
GL_APICALL ਖਾਲੀ GL_APIENTRY glMinSampleShading (GLfloat ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glPatchParameteri (GLenum pname, GLint ਮੁੱਲ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glTexParameterIiv (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, ਅਚਲ GLint *params);
GL_APICALL ਖਾਲੀ GL_APIENTRY glTexParameterIuiv (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, ਅਚਲ GLuint *params);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetTexParameterIiv (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLint *params);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetTexParameterIuiv (GLenum ਨਿਸ਼ਾਨਾ, GLenum pname, GLuint *params);
GL_APICALL ਖਾਲੀ GL_APIENTRY glSamplerParameterIiv (GLuint sampler, GLenum pname, ਅਚਲ GLint *param);
GL_APICALL ਖਾਲੀ GL_APIENTRY glSamplerParameterIuiv (GLuint sampler, GLenum pname, ਅਚਲ GLuint *param);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetSamplerParameterIiv (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL ਖਾਲੀ GL_APIENTRY glGetSamplerParameterIuiv (GLuint sampler, GLenum pname, GLuint *params);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Tex_ਬਫਰ (GLenum ਨਿਸ਼ਾਨਾ, GLenum internalformat, GLuint ਬਫਰ_2);
GL_APICALL ਖਾਲੀ GL_APIENTRY gl_Tex_ਬਫਰ_Range (GLenum ਨਿਸ਼ਾਨਾ, GLenum internalformat, GLuint ਬਫਰ_2, GLintptr ਵਿੱਥ_2, GLsizeiptr ਮਾਪ);
GL_APICALL ਖਾਲੀ GL_APIENTRY glTexStorage3DMultisample (GLenum ਨਿਸ਼ਾਨਾ, GLsizei samples, GLenum internalformat, GLsizei ਚੌੜਾਈ, GLsizei ਉਚਾਈ, GLsizei ਡੂੰਘਾਈ_2, GLboolean fixedsamplelocations);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* GL_ES_VERSION_3_2 */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ
