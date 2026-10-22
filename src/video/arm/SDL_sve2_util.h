/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#جيڪڏهن_وصف_نه_ٿيل SDL_SVE2_UTIL_H
#وصف_ڪريو SDL_SVE2_UTIL_H

#وصف_رد SVE_0_CONNECT2
#وصف_رد SVE_0_CONNECT3
#وصف_رد SVE_0_CONNECT4
#وصف_رد SVE_0_CONNECT5
#وصف_رد SVE_0_CONNECT6
#وصف_رد SVE_0_CONNECT7
#وصف_رد SVE_0_CONNECT8
#وصف_رد SVE_0_CONNECT9

#وصف_رد SVE_CONNECT2
#وصف_رد SVE_CONNECT3
#وصف_رد SVE_CONNECT4
#وصف_رد SVE_CONNECT5
#وصف_رد SVE_CONNECT6
#وصف_رد SVE_CONNECT7
#وصف_رد SVE_CONNECT8
#وصف_رد SVE_CONNECT9
#وصف_رد ALT_SVE_CONNECT2

#وصف_رد SVE_محفوظ_NAME

#وصف_رد SVE_CONNECT

#وصف_ڪريو SVE_0_CONNECT2(ma_A, ma_B)             ma_A##ma_B
#وصف_ڪريو SVE_0_CONNECT3(ma_A, ma_B, ma_C)       ma_A##ma_B##ma_C
#وصف_ڪريو SVE_0_CONNECT4(ma_A, ma_B, ma_C, ma_D) ma_A##ma_B##ma_C##ma_D
#وصف_ڪريو SVE_0_CONNECT5(ma_A, ma_B, ma_C, ma_D, ma_E) \
    ma_A##ma_B##ma_C##ma_D##ma_E
#وصف_ڪريو SVE_0_CONNECT6(ma_A, ma_B, ma_C, ma_D, ma_E, ma_F) \
    ma_A##ma_B##ma_C##ma_D##ma_E##ma_F
#وصف_ڪريو SVE_0_CONNECT7(ma_A, ma_B, ma_C, ma_D, ma_E, ma_F, ma_G) \
    ma_A##ma_B##ma_C##ma_D##ma_E##ma_F##ma_G
#وصف_ڪريو SVE_0_CONNECT8(ma_A, ma_B, ma_C, ma_D, ma_E, ma_F, ma_G, ma_H) \
    ma_A##ma_B##ma_C##ma_D##ma_E##ma_F##ma_G##ma_H
#وصف_ڪريو SVE_0_CONNECT9(ma_A, ma_B, ma_C, ma_D, ma_E, ma_F, ma_G, ma_H, ma_I) \
    ma_A##ma_B##ma_C##ma_D##ma_E##ma_F##ma_G##ma_H##ma_I

#وصف_ڪريو ALT_SVE_CONNECT2(ma_A, ma_B)   SVE_0_CONNECT2(ma_A, ma_B)
#وصف_ڪريو SVE_CONNECT2(ma_A, ma_B)       SVE_0_CONNECT2(ma_A, ma_B)
#وصف_ڪريو SVE_CONNECT3(ma_A, ma_B, ma_C) SVE_0_CONNECT3(ma_A, ma_B, ma_C)
#وصف_ڪريو SVE_CONNECT4(ma_A, ma_B, ma_C, ma_D) \
    SVE_0_CONNECT4(ma_A, ma_B, ma_C, ma_D)
#وصف_ڪريو SVE_CONNECT5(ma_A, ma_B, ma_C, ma_D, ma_E) \
    SVE_0_CONNECT5(ma_A, ma_B, ma_C, ma_D, ma_E)
#وصف_ڪريو SVE_CONNECT6(ma_A, ma_B, ma_C, ma_D, ma_E, ma_F) \
    SVE_0_CONNECT6(ma_A, ma_B, ma_C, ma_D, ma_E, ma_F)
#وصف_ڪريو SVE_CONNECT7(ma_A, ma_B, ma_C, ma_D, ma_E, ma_F, ma_G) \
    SVE_0_CONNECT7(ma_A, ma_B, ma_C, ma_D, ma_E, ma_F, ma_G)
#وصف_ڪريو SVE_CONNECT8(ma_A, ma_B, ma_C, ma_D, ma_E, ma_F, ma_G, ma_H) \
    SVE_0_CONNECT8(ma_A, ma_B, ma_C, ma_D, ma_E, ma_F, ma_G, ma_H)
#وصف_ڪريو SVE_CONNECT9(ma_A, ma_B, ma_C, ma_D, ma_E, ma_F, ma_G, ma_H, ma_I) \
    SVE_0_CONNECT9(ma_A, ma_B, ma_C, ma_D, ma_E, ma_F, ma_G, ma_H, ma_I)

#وصف_ڪريو SVE_CONNECT(...)          \
    ALT_SVE_CONNECT2(SVE_CONNECT, \
                     SVE_VA_انگ_دليلون(__VA_ARGS__))(__VA_ARGS__)

#جيڪڏهن_وصف_نه_ٿيل SVE_VA_انگ_دليلون_IMPL
#وصف_ڪريو SVE_VA_انگ_دليلون_IMPL(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, \
                             _12, _13, _14, _15, _16, ma_N, ...) ma_N
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل SVE_VA_انگ_دليلون
#وصف_ڪريو SVE_VA_انگ_دليلون(...)                                              \
    SVE_VA_انگ_دليلون_IMPL(0, ##__VA_ARGS__, 16, 15, 14, 13, 12, 11, 10, 9, \
                         8, 7, 6, 5, 4, 3, 2, 1, 0)
#جيڪڏهن_پورو

#وصف_ڪريو SVE_محفوظ_NAME(ma_NAME) SVE_CONNECT3(ma_, ma_NAME, ma_LINEma_)

#جيڪڏهن_پورو /* SDL_SVE2_UTIL_H */
