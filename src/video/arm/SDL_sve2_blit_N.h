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

#నిర్వచితం_కాకపోతే SDL_sve2_blit_N_h_
#నిర్వచించు SDL_sve2_blit_N_h_

#అన్తర్భావ "../../SDL_internal.h"
#అన్తర్భావ "../SDL_blit.h"

#నిర్వచితమైతే SDL_SVE2_INTRINSICS

శూన్య Blit8888to8888PixelSwizzleSVE2(SDL_BlitInfo *info);
శూన్య Blit8888to565PixelSwizzleSVE2(SDL_BlitInfo *info);
శూన్య Blit2to2_కీలకం_SVE2(SDL_BlitInfo *info);
శూన్య Blit4to4_కీలకం_SVE2(SDL_BlitInfo *info);

#అయితే_ముగింపు /* SDL_SVE2_INTRINSICS */

#అయితే_ముగింపు /* SDL_sve2_blitters_h_ */