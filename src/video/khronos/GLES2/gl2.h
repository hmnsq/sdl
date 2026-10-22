#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __gles2_gl2_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ __gles2_gl2_h_ 1

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

#ਅਨ੍ਤਰ੍ਭਾਵ <GLES2/gl2platform.h>

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
 * Versions considered: 2\.[0-9]
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

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ
