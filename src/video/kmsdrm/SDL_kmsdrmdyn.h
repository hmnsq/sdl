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

#अगर_अघोषित SDL_kmsdrmdyn_h_
#घोषणा SDL_kmsdrmdyn_h_

#समावेश "SDL_internal.h"

#समावेश <xf86drm.h>
#समावेश <xf86drmMode.h>
#समावेश <gbm.h>

#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर

बाह्य bool SDL_KMSDRM_LoadSymbols(व्योम);
बाह्य व्योम SDL_KMSDRM_UnloadSymbols(व्योम);

// Declare all the function pointers and wrappers...
#घोषणा SDL_KMSDRM_SYM(rc, fn, params)        \
    प्रकार rc(*SDL_DYNKMSDRMFN_##fn) params; \
    बाह्य SDL_DYNKMSDRMFN_##fn KMSDRM_##fn;
#घोषणा SDL_KMSDRM_SYM_CONST(type, name)    \
    प्रकार type SDL_DYNKMSDRMCONST_##name; \
    बाह्य SDL_DYNKMSDRMCONST_##name KMSDRM_##name;
#घोषणा SDL_KMSDRM_SYM_OPT(rc, fn, params)    \
    प्रकार rc(*SDL_DYNKMSDRMFN_##fn) params; \
    बाह्य SDL_DYNKMSDRMFN_##fn KMSDRM_##fn;
#समावेश "SDL_kmsdrmsym.h"

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर // SDL_kmsdrmdyn_h_
