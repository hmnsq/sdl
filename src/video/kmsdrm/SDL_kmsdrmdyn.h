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

#അന്തര്ഭാവ "SDL_internal.h"

#അന്തര്ഭാവ <xf86drm.h>
#അന്തര്ഭാവ <xf86drmMode.h>
#അന്തര്ഭാവ <gbm.h>

#ifdef __cplusplus
ബാഹ്യ "C" {
#endif

ബാഹ്യ bool SDL_KMSDRM_LoadSymbols(ശൂന്യം);
ബാഹ്യ ശൂന്യം SDL_KMSDRM_UnloadSymbols(ശൂന്യം);

// Declare all the function pointers and wrappers...
#define SDL_KMSDRM_SYM(rc, fn, params)        \
    തരനിർവചനം rc(*SDL_DYNKMSDRMFN_##fn) params; \
    ബാഹ്യ SDL_DYNKMSDRMFN_##fn KMSDRM_##fn;
#define SDL_KMSDRM_SYM_CONST(type, name)    \
    തരനിർവചനം type SDL_DYNKMSDRMCONST_##name; \
    ബാഹ്യ SDL_DYNKMSDRMCONST_##name KMSDRM_##name;
#define SDL_KMSDRM_SYM_OPT(rc, fn, params)    \
    തരനിർവചനം rc(*SDL_DYNKMSDRMFN_##fn) params; \
    ബാഹ്യ SDL_DYNKMSDRMFN_##fn KMSDRM_##fn;
#അന്തര്ഭാവ "SDL_kmsdrmsym.h"

#ifdef __cplusplus
}
#endif

#endif // SDL_kmsdrmdyn_h_
