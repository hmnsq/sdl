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

#ifndef SDL_kmsdrmdyn_h_
#define SDL_kmsdrmdyn_h_

#அந்தர்பாவ "SDL_internal.h"

#அந்தர்பாவ <xf86drm.h>
#அந்தர்பாவ <xf86drmMode.h>
#அந்தர்பாவ <gbm.h>

#ifdef __cplusplus
வெளி "C" {
#endif

வெளி bool SDL_KMSDRM_LoadSymbols(வெறுமை);
வெளி வெறுமை SDL_KMSDRM_UnloadSymbols(வெறுமை);

// Declare all the function pointers and wrappers...
#define SDL_KMSDRM_SYM(rc, fn, params)        \
    வகைவரை rc(*SDL_DYNKMSDRMFN_##fn) params; \
    வெளி SDL_DYNKMSDRMFN_##fn KMSDRM_##fn;
#define SDL_KMSDRM_SYM_CONST(type, name)    \
    வகைவரை type SDL_DYNKMSDRMCONST_##name; \
    வெளி SDL_DYNKMSDRMCONST_##name KMSDRM_##name;
#define SDL_KMSDRM_SYM_OPT(rc, fn, params)    \
    வகைவரை rc(*SDL_DYNKMSDRMFN_##fn) params; \
    வெளி SDL_DYNKMSDRMFN_##fn KMSDRM_##fn;
#அந்தர்பாவ "SDL_kmsdrmsym.h"

#ifdef __cplusplus
}
#endif

#endif // SDL_kmsdrmdyn_h_
