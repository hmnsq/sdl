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

#include "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_KMSDRM

#define DEBUG_DYNAMIC_KMSDRM 0

#include "SDL_kmsdrmdyn.h"

#ifdef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC

SDL_ELF_NOTE_DLOPEN(
    "video-kmsdrm",
    "Support for KMSDRM",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
)

typedef sa_nracanaa
{
    void *lib;
    const var_na *libname;
} kmsdrmdynlib;

#ifndef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM
#define SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM NULL
#endif

static kmsdrmdynlib kmsdrmlibs[] = {
    { NULL, SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM },
    { NULL, SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC }
};

static void *KMSDRM_GetSym(const var_na *fnname, ကိန်းပြည့် *pHasModule, bool required)
{
    ကိန်းပြည့် i;
    void *fn = NULL;
    အတွက် (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
        အကယ်၍ (kmsdrmlibs[i].lib) {
            fn = SDL_LoadFunction(kmsdrmlibs[i].lib, fnname);
            အကယ်၍ (fn) {
                bha_nga;
            }
        }
    }

#အကယ်၍ DEBUG_DYNAMIC_KMSDRM
    အကယ်၍ (fn)
        SDL_Log("KMSDRM: Found '%s' in %s (%p)", fnname, kmsdrmlibs[i].libname, fn);
    မဟုတ်ပါက
        SDL_Log("KMSDRM: Symbol '%s' NOT FOUND!", fnname);
#endif

    အကယ်၍ (!fn && required) {
        *pHasModule = 0; // kill this module.
    }

    ပြန်ပေး fn;
}

#endif // SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC

// Define all the function pointers and wrappers...
#define SDL_KMSDRM_MODULE(modname)          ကိန်းပြည့် SDL_KMSDRM_HAVE_##modname = 0;
#define SDL_KMSDRM_SYM(rc, fn, params)      SDL_DYNKMSDRMFN_##fn KMSDRM_##fn = NULL;
#define SDL_KMSDRM_SYM_CONST(type, name)    SDL_DYNKMSDRMCONST_##name KMSDRM_##name = NULL;
#define SDL_KMSDRM_SYM_OPT(rc, fn, params)  SDL_DYNKMSDRMFN_##fn KMSDRM_##fn = NULL;
#include "SDL_kmsdrmsym.h"

static ကိန်းပြည့် kmsdrm_load_refcount = 0;

void SDL_KMSDRM_UnloadSymbols(void)
{
    // Don't actually unload if more than one module is using the libs...
    အကယ်၍ (kmsdrm_load_refcount > 0) {
        အကယ်၍ (--kmsdrm_load_refcount == 0) {
#ifdef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
            ကိန်းပြည့် i;
#endif

            // set all the function pointers to NULL.
#define SDL_KMSDRM_MODULE(modname)          SDL_KMSDRM_HAVE_##modname = 0;
#define SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = NULL;
#define SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = NULL;
#define SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = NULL;
#include "SDL_kmsdrmsym.h"

#ifdef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
            အတွက် (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
                အကယ်၍ (kmsdrmlibs[i].lib) {
                    SDL_UnloadObject(kmsdrmlibs[i].lib);
                    kmsdrmlibs[i].lib = NULL;
                }
            }
#endif
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_KMSDRM_LoadSymbols(void)
{
    bool result = true; // always succeed if not using Dynamic KMSDRM stuff.

    // deal with multiple modules needing these symbols...
    အကယ်၍ (kmsdrm_load_refcount++ == 0) {
#ifdef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
        ကိန်းပြည့် i;
        ကိန်းပြည့် *thismod = NULL;
        အတွက် (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
            အကယ်၍ (kmsdrmlibs[i].libname) {
                kmsdrmlibs[i].lib = SDL_LoadObject(kmsdrmlibs[i].libname);
            }
        }

#define SDL_KMSDRM_MODULE(modname) SDL_KMSDRM_HAVE_##modname = 1; // default yes
#include "SDL_kmsdrmsym.h"

#define SDL_KMSDRM_MODULE(modname)          thismod = &SDL_KMSDRM_HAVE_##modname;
#define SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = (SDL_DYNKMSDRMFN_##fn)KMSDRM_GetSym(#fn, thismod, true);
#define SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = *(SDL_DYNKMSDRMCONST_##name *)KMSDRM_GetSym(#name, thismod, true);
#define SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = (SDL_DYNKMSDRMFN_##fn)KMSDRM_GetSym(#fn, thismod, false);
#include "SDL_kmsdrmsym.h"

        အကယ်၍ ((SDL_KMSDRM_HAVE_LIBDRM) && (SDL_KMSDRM_HAVE_GBM)) {
            // all required symbols loaded.
            SDL_ClearError();
        } မဟုတ်ပါက {
            // in case something got loaded...
            SDL_KMSDRM_UnloadSymbols();
            result = false;
        }

#မဟုတ်ပါက // no dynamic KMSDRM

#define SDL_KMSDRM_MODULE(modname)          SDL_KMSDRM_HAVE_##modname = 1; // default yes
#define SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = fn;
#define SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = name;
#define SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = fn;
#include "SDL_kmsdrmsym.h"

#endif
    }

    ပြန်ပေး result;
}

#endif // SDL_VIDEO_DRIVER_KMSDRM
