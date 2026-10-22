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

#اگر_تعریف_نشده SDL_sve2_blit_A_h_
#تعریف_کن SDL_sve2_blit_A_h_

#ضمن "../../SDL_internal.h"
#ضمن "../SDL_blit.h"

#اگر_تعریف_شده SDL_SVE2_INTRINSICS

فراغ Blit8888to8888PixelAlphaSwizzleSVE2(SDL_BlitInfo *info);
فراغ Blit8888to565PixelAlphaSwizzleSVE2(SDL_BlitInfo *info);

فراغ Blit565to565SurfaceAlphaSVE2(SDL_BlitInfo *info);

size_t SDL_Get_SVEVector_اندازه(فراغ);

#پایان_اگر /* SDL_SVE2_INTRINSICS */

#پایان_اگر /* SDL_sve2_blitters_h_ */