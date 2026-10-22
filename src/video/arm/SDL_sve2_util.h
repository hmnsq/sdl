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

#جے_بنا_تعریف SDL_SVE2_UTIL_H
#تعریف_کرو SDL_SVE2_UTIL_H

#تعریف_رد SVE_0_CONNECT2
#تعریف_رد SVE_0_CONNECT3
#تعریف_رد SVE_0_CONNECT4
#تعریف_رد SVE_0_CONNECT5
#تعریف_رد SVE_0_CONNECT6
#تعریف_رد SVE_0_CONNECT7
#تعریف_رد SVE_0_CONNECT8
#تعریف_رد SVE_0_CONNECT9

#تعریف_رد SVE_CONNECT2
#تعریف_رد SVE_CONNECT3
#تعریف_رد SVE_CONNECT4
#تعریف_رد SVE_CONNECT5
#تعریف_رد SVE_CONNECT6
#تعریف_رد SVE_CONNECT7
#تعریف_رد SVE_CONNECT8
#تعریف_رد SVE_CONNECT9
#تعریف_رد ALT_SVE_CONNECT2

#تعریف_رد SVE_محفوظ_NAME

#تعریف_رد SVE_CONNECT

#تعریف_کرو SVE_0_CONNECT2(ma_A, ma_B)             ma_A##ma_B
#تعریف_کرو SVE_0_CONNECT3(ma_A, ma_B, ma_C)       ma_A##ma_B##ma_C
#تعریف_کرو SVE_0_CONNECT4(ma_A, ma_B, ma_C, ma_D) ma_A##ma_B##ma_C##ma_D
#تعریف_کرو SVE_0_CONNECT5(ma_A, ma_B, ma_C, ma_D, ma_E) \
    ma_A##ma_B##ma_C##ma_D##ma_E
#تعریف_کرو SVE_0_CONNECT6(ma_A, ma_B, ma_C, ma_D, ma_E, ma_F) \
    ma_A##ma_B##ma_C##ma_D##ma_E##ma_F
#تعریف_کرو SVE_0_CONNECT7(ma_A, ma_B, ma_C, ma_D, ma_E, ma_F, ma_G) \
    ma_A##ma_B##ma_C##ma_D##ma_E##ma_F##ma_G
#تعریف_کرو SVE_0_CONNECT8(ma_A, ma_B, ma_C, ma_D, ma_E, ma_F, ma_G, ma_H) \
    ma_A##ma_B##ma_C##ma_D##ma_E##ma_F##ma_G##ma_H
#تعریف_کرو SVE_0_CONNECT9(ma_A, ma_B, ma_C, ma_D, ma_E, ma_F, ma_G, ma_H, ma_I) \
    ma_A##ma_B##ma_C##ma_D##ma_E##ma_F##ma_G##ma_H##ma_I

#تعریف_کرو ALT_SVE_CONNECT2(ma_A, ma_B)   SVE_0_CONNECT2(ma_A, ma_B)
#تعریف_کرو SVE_CONNECT2(ma_A, ma_B)       SVE_0_CONNECT2(ma_A, ma_B)
#تعریف_کرو SVE_CONNECT3(ma_A, ma_B, ma_C) SVE_0_CONNECT3(ma_A, ma_B, ma_C)
#تعریف_کرو SVE_CONNECT4(ma_A, ma_B, ma_C, ma_D) \
    SVE_0_CONNECT4(ma_A, ma_B, ma_C, ma_D)
#تعریف_کرو SVE_CONNECT5(ma_A, ma_B, ma_C, ma_D, ma_E) \
    SVE_0_CONNECT5(ma_A, ma_B, ma_C, ma_D, ma_E)
#تعریف_کرو SVE_CONNECT6(ma_A, ma_B, ma_C, ma_D, ma_E, ma_F) \
    SVE_0_CONNECT6(ma_A, ma_B, ma_C, ma_D, ma_E, ma_F)
#تعریف_کرو SVE_CONNECT7(ma_A, ma_B, ma_C, ma_D, ma_E, ma_F, ma_G) \
    SVE_0_CONNECT7(ma_A, ma_B, ma_C, ma_D, ma_E, ma_F, ma_G)
#تعریف_کرو SVE_CONNECT8(ma_A, ma_B, ma_C, ma_D, ma_E, ma_F, ma_G, ma_H) \
    SVE_0_CONNECT8(ma_A, ma_B, ma_C, ma_D, ma_E, ma_F, ma_G, ma_H)
#تعریف_کرو SVE_CONNECT9(ma_A, ma_B, ma_C, ma_D, ma_E, ma_F, ma_G, ma_H, ma_I) \
    SVE_0_CONNECT9(ma_A, ma_B, ma_C, ma_D, ma_E, ma_F, ma_G, ma_H, ma_I)

#تعریف_کرو SVE_CONNECT(...)          \
    ALT_SVE_CONNECT2(SVE_CONNECT, \
                     SVE_VA_عدد_دلیلاں(__VA_ARGS__))(__VA_ARGS__)

#جے_بنا_تعریف SVE_VA_عدد_دلیلاں_IMPL
#تعریف_کرو SVE_VA_عدد_دلیلاں_IMPL(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, \
                             _12, _13, _14, _15, _16, ma_N, ...) ma_N
#جے_انت

#جے_بنا_تعریف SVE_VA_عدد_دلیلاں
#تعریف_کرو SVE_VA_عدد_دلیلاں(...)                                              \
    SVE_VA_عدد_دلیلاں_IMPL(0, ##__VA_ARGS__, 16, 15, 14, 13, 12, 11, 10, 9, \
                         8, 7, 6, 5, 4, 3, 2, 1, 0)
#جے_انت

#تعریف_کرو SVE_محفوظ_NAME(ma_NAME) SVE_CONNECT3(ma_, ma_NAME, ma_LINEma_)

#جے_انت /* SDL_SVE2_UTIL_H */
