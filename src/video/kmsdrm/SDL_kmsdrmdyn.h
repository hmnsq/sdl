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

#অন্তর্ভাব "SDL_internal.h"

#অন্তর্ভাব <xf86drm.h>
#অন্তর্ভাব <xf86drmMode.h>
#অন্তর্ভাব <gbm.h>

#ifdef __cplusplus
বাহ্য "C" {
#endif

বাহ্য bool SDL_KMSDRM_LoadSymbols(শূন্য);
বাহ্য শূন্য SDL_KMSDRM_UnloadSymbols(শূন্য);

// Declare all the function pointers and wrappers...
#define SDL_KMSDRM_SYM(rc, fn, params)        \
    প্রকারনির্দেশ rc(*SDL_DYNKMSDRMFN_##fn) params; \
    বাহ্য SDL_DYNKMSDRMFN_##fn KMSDRM_##fn;
#define SDL_KMSDRM_SYM_CONST(type, name)    \
    প্রকারনির্দেশ type SDL_DYNKMSDRMCONST_##name; \
    বাহ্য SDL_DYNKMSDRMCONST_##name KMSDRM_##name;
#define SDL_KMSDRM_SYM_OPT(rc, fn, params)    \
    প্রকারনির্দেশ rc(*SDL_DYNKMSDRMFN_##fn) params; \
    বাহ্য SDL_DYNKMSDRMFN_##fn KMSDRM_##fn;
#অন্তর্ভাব "SDL_kmsdrmsym.h"

#ifdef __cplusplus
}
#endif

#endif // SDL_kmsdrmdyn_h_
