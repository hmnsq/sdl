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

static void *KMSDRM_GetSym(const var_na *fnname, puur_naa_nka *pHasModule, bool required)
{
    puur_naa_nka i;
    void *fn = NULL;
    for (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
        ᱡᱩᱫᱤ (kmsdrmlibs[i].lib) {
            fn = SDL_LoadFunction(kmsdrmlibs[i].lib, fnname);
            ᱡᱩᱫᱤ (fn) {
                bha_nga;
            }
        }
    }

#ᱡᱩᱫᱤ DEBUG_DYNAMIC_KMSDRM
    ᱡᱩᱫᱤ (fn)
        SDL_Log("KMSDRM: Found '%s' in %s (%p)", fnname, kmsdrmlibs[i].libname, fn);
    ᱵᱟᱝ
        SDL_Log("KMSDRM: Symbol '%s' NOT FOUND!", fnname);
#endif

    ᱡᱩᱫᱤ (!fn && required) {
        *pHasModule = 0; // kill this module.
    }

    ᱨᱩᱣᱟᱹᱲ fn;
}

#endif // SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC

// Define all the function pointers and wrappers...
#define SDL_KMSDRM_MODULE(modname)          puur_naa_nka SDL_KMSDRM_HAVE_##modname = 0;
#define SDL_KMSDRM_SYM(rc, fn, params)      SDL_DYNKMSDRMFN_##fn KMSDRM_##fn = NULL;
#define SDL_KMSDRM_SYM_CONST(type, name)    SDL_DYNKMSDRMCONST_##name KMSDRM_##name = NULL;
#define SDL_KMSDRM_SYM_OPT(rc, fn, params)  SDL_DYNKMSDRMFN_##fn KMSDRM_##fn = NULL;
#include "SDL_kmsdrmsym.h"

static puur_naa_nka kmsdrm_load_refcount = 0;

void SDL_KMSDRM_UnloadSymbols(void)
{
    // Don't actually unload if more than one module is using the libs...
    ᱡᱩᱫᱤ (kmsdrm_load_refcount > 0) {
        ᱡᱩᱫᱤ (--kmsdrm_load_refcount == 0) {
#ifdef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
            puur_naa_nka i;
#endif

            // set all the function pointers to NULL.
#define SDL_KMSDRM_MODULE(modname)          SDL_KMSDRM_HAVE_##modname = 0;
#define SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = NULL;
#define SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = NULL;
#define SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = NULL;
#include "SDL_kmsdrmsym.h"

#ifdef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
            for (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
                ᱡᱩᱫᱤ (kmsdrmlibs[i].lib) {
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
    ᱡᱩᱫᱤ (kmsdrm_load_refcount++ == 0) {
#ifdef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
        puur_naa_nka i;
        puur_naa_nka *thismod = NULL;
        for (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
            ᱡᱩᱫᱤ (kmsdrmlibs[i].libname) {
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

        ᱡᱩᱫᱤ ((SDL_KMSDRM_HAVE_LIBDRM) && (SDL_KMSDRM_HAVE_GBM)) {
            // all required symbols loaded.
            SDL_ClearError();
        } ᱵᱟᱝ {
            // in case something got loaded...
            SDL_KMSDRM_UnloadSymbols();
            result = false;
        }

#ᱵᱟᱝ // no dynamic KMSDRM

#define SDL_KMSDRM_MODULE(modname)          SDL_KMSDRM_HAVE_##modname = 1; // default yes
#define SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = fn;
#define SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = name;
#define SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = fn;
#include "SDL_kmsdrmsym.h"

#endif
    }

    ᱨᱩᱣᱟᱹᱲ result;
}

#endif // SDL_VIDEO_DRIVER_KMSDRM
