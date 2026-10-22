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

#నిర్వచితం_కాకపోతే SDL_kmsdrmdyn_h_
#నిర్వచించు SDL_kmsdrmdyn_h_

#అన్తర్భావ "SDL_internal.h"

#అన్తర్భావ <xf86drm.h>
#అన్తర్భావ <xf86drmMode.h>
#అన్తర్భావ <gbm.h>

#నిర్వచితమైతే __cplusplus
బాహ్య "C" {
#అయితే_ముగింపు

బాహ్య bool SDL_KMSDRM_ఎక్కించు_Symbols(శూన్య);
బాహ్య శూన్య SDL_KMSDRM_UnloadSymbols(శూన్య);

// Declare all the function pointers and wrappers...
#నిర్వచించు SDL_KMSDRM_SYM(rc, fn, params)        \
    రకనిర్వచనం rc(*SDL_DYNKMSDRMFN_##fn) params; \
    బాహ్య SDL_DYNKMSDRMFN_##fn KMSDRM_##fn;
#నిర్వచించు SDL_KMSDRM_SYM_CONST(type, name)    \
    రకనిర్వచనం type SDL_DYNKMSDRMCONST_##name; \
    బాహ్య SDL_DYNKMSDRMCONST_##name KMSDRM_##name;
#నిర్వచించు SDL_KMSDRM_SYM_OPT(rc, fn, params)    \
    రకనిర్వచనం rc(*SDL_DYNKMSDRMFN_##fn) params; \
    బాహ్య SDL_DYNKMSDRMFN_##fn KMSDRM_##fn;
#అన్తర్భావ "SDL_kmsdrmsym.h"

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు // SDL_kmsdrmdyn_h_
