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

#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_KMSDRM

#నిర్వచించు DEBUG_DYNAMIC_KMSDRM 0

#అన్తర్భావ "SDL_kmsdrmdyn.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC

SDL_ELF_NOTE_DLOPEN(
    "video-kmsdrm",
    "Support for KMSDRM",
    SDL_ELF_NOTE_DLOPEN_ప్రాధాన్యత_SUGGESTED,
    SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
)

రకనిర్వచనం నిర్మాణం
{
    శూన్య *lib;
    స్థిరరాశి అక్షరం *libname;
} kmsdrmdynlib;

#నిర్వచితం_కాకపోతే SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM
#నిర్వచించు SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM ఖాళీ
#అయితే_ముగింపు

స్థిర kmsdrmdynlib kmsdrmlibs[] = {
    { ఖాళీ, SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM },
    { ఖాళీ, SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC }
};

స్థిర శూన్య *KMSDRM_GetSym(స్థిరరాశి అక్షరం *fnname, పూర్ణాంకం *pHasModule, bool required)
{
    పూర్ణాంకం i;
    శూన్య *fn = ఖాళీ;
    కొరకు (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
        ఒకవేళ (kmsdrmlibs[i].lib) {
            fn = SDL_ఎక్కించు_Function(kmsdrmlibs[i].lib, fnname);
            ఒకవేళ (fn) {
                ఆపు;
            }
        }
    }

#ఒకవేళ DEBUG_DYNAMIC_KMSDRM
    ఒకవేళ (fn)
        SDL_Log("KMSDRM: Found '%s' in %s (%p)", fnname, kmsdrmlibs[i].libname, fn);
    లేకపోతే
        SDL_Log("KMSDRM: Symbol '%s' NOT FOUND!", fnname);
#అయితే_ముగింపు

    ఒకవేళ (!fn && required) {
        *pHasModule = 0; // kill this module.
    }

    తిరిగి fn;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC

// Define all the function pointers and wrappers...
#నిర్వచించు SDL_KMSDRM_MODULE(modname)          పూర్ణాంకం SDL_KMSDRM_HAVE_##modname = 0;
#నిర్వచించు SDL_KMSDRM_SYM(rc, fn, params)      SDL_DYNKMSDRMFN_##fn KMSDRM_##fn = ఖాళీ;
#నిర్వచించు SDL_KMSDRM_SYM_CONST(type, name)    SDL_DYNKMSDRMCONST_##name KMSDRM_##name = ఖాళీ;
#నిర్వచించు SDL_KMSDRM_SYM_OPT(rc, fn, params)  SDL_DYNKMSDRMFN_##fn KMSDRM_##fn = ఖాళీ;
#అన్తర్భావ "SDL_kmsdrmsym.h"

స్థిర పూర్ణాంకం kmsdrm_ఎక్కించు_refcount = 0;

శూన్య SDL_KMSDRM_UnloadSymbols(శూన్య)
{
    // Don't actually unload if more than one module is using the libs...
    ఒకవేళ (kmsdrm_ఎక్కించు_refcount > 0) {
        ఒకవేళ (--kmsdrm_ఎక్కించు_refcount == 0) {
#నిర్వచితమైతే SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
            పూర్ణాంకం i;
#అయితే_ముగింపు

            // set all the function pointers to NULL.
#నిర్వచించు SDL_KMSDRM_MODULE(modname)          SDL_KMSDRM_HAVE_##modname = 0;
#నిర్వచించు SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = ఖాళీ;
#నిర్వచించు SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = ఖాళీ;
#నిర్వచించు SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = ఖాళీ;
#అన్తర్భావ "SDL_kmsdrmsym.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
            కొరకు (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
                ఒకవేళ (kmsdrmlibs[i].lib) {
                    SDL_UnloadObject(kmsdrmlibs[i].lib);
                    kmsdrmlibs[i].lib = ఖాళీ;
                }
            }
#అయితే_ముగింపు
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_KMSDRM_ఎక్కించు_Symbols(శూన్య)
{
    bool ఫలితం = true; // always succeed if not using Dynamic KMSDRM stuff.

    // deal with multiple modules needing these symbols...
    ఒకవేళ (kmsdrm_ఎక్కించు_refcount++ == 0) {
#నిర్వచితమైతే SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
        పూర్ణాంకం i;
        పూర్ణాంకం *thismod = ఖాళీ;
        కొరకు (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
            ఒకవేళ (kmsdrmlibs[i].libname) {
                kmsdrmlibs[i].lib = SDL_ఎక్కించు_Object(kmsdrmlibs[i].libname);
            }
        }

#నిర్వచించు SDL_KMSDRM_MODULE(modname) SDL_KMSDRM_HAVE_##modname = 1; // default yes
#అన్తర్భావ "SDL_kmsdrmsym.h"

#నిర్వచించు SDL_KMSDRM_MODULE(modname)          thismod = &SDL_KMSDRM_HAVE_##modname;
#నిర్వచించు SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = (SDL_DYNKMSDRMFN_##fn)KMSDRM_GetSym(#fn, thismod, true);
#నిర్వచించు SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = *(SDL_DYNKMSDRMCONST_##name *)KMSDRM_GetSym(#name, thismod, true);
#నిర్వచించు SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = (SDL_DYNKMSDRMFN_##fn)KMSDRM_GetSym(#fn, thismod, false);
#అన్తర్భావ "SDL_kmsdrmsym.h"

        ఒకవేళ ((SDL_KMSDRM_HAVE_LIBDRM) && (SDL_KMSDRM_HAVE_GBM)) {
            // all required symbols loaded.
            SDL_ClearError();
        } లేకపోతే {
            // in case something got loaded...
            SDL_KMSDRM_UnloadSymbols();
            ఫలితం = false;
        }

#లేకపోతే // no dynamic KMSDRM

#నిర్వచించు SDL_KMSDRM_MODULE(modname)          SDL_KMSDRM_HAVE_##modname = 1; // default yes
#నిర్వచించు SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = fn;
#నిర్వచించు SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = name;
#నిర్వచించు SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = fn;
#అన్తర్భావ "SDL_kmsdrmsym.h"

#అయితే_ముగింపు
    }

    తిరిగి ఫలితం;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_KMSDRM
