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

#অন্তর্ভাৱ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_KMSDRM

#define DEBUG_DYNAMIC_KMSDRM 0

#অন্তর্ভাৱ "SDL_kmsdrmdyn.h"

#ifdef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC

SDL_ELF_NOTE_DLOPEN(
    "video-kmsdrm",
    "Support for KMSDRM",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
)

প্রকারনির্দেশ সংরচনা
{
    শূন্য *lib;
    ধ্রুৱ ৱর্ণ *libname;
} kmsdrmdynlib;

#ifndef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM
#define SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM রিক্ত
#endif

স্থির kmsdrmdynlib kmsdrmlibs[] = {
    { রিক্ত, SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM },
    { রিক্ত, SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC }
};

স্থির শূন্য *KMSDRM_GetSym(ধ্রুৱ ৱর্ণ *fnname, পূর্ণাঙ্ক *pHasModule, bool required)
{
    পূর্ণাঙ্ক i;
    শূন্য *fn = রিক্ত;
    বাবে (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
        যদি (kmsdrmlibs[i].lib) {
            fn = SDL_LoadFunction(kmsdrmlibs[i].lib, fnname);
            যদি (fn) {
                ভঙ্গ;
            }
        }
    }

#যদি DEBUG_DYNAMIC_KMSDRM
    যদি (fn)
        SDL_Log("KMSDRM: Found '%s' in %s (%p)", fnname, kmsdrmlibs[i].libname, fn);
    অন্যথা
        SDL_Log("KMSDRM: Symbol '%s' NOT FOUND!", fnname);
#endif

    যদি (!fn && required) {
        *pHasModule = 0; // kill this module.
    }

    ঘূৰাই fn;
}

#endif // SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC

// Define all the function pointers and wrappers...
#define SDL_KMSDRM_MODULE(modname)          পূর্ণাঙ্ক SDL_KMSDRM_HAVE_##modname = 0;
#define SDL_KMSDRM_SYM(rc, fn, params)      SDL_DYNKMSDRMFN_##fn KMSDRM_##fn = রিক্ত;
#define SDL_KMSDRM_SYM_CONST(type, name)    SDL_DYNKMSDRMCONST_##name KMSDRM_##name = রিক্ত;
#define SDL_KMSDRM_SYM_OPT(rc, fn, params)  SDL_DYNKMSDRMFN_##fn KMSDRM_##fn = রিক্ত;
#অন্তর্ভাৱ "SDL_kmsdrmsym.h"

স্থির পূর্ণাঙ্ক kmsdrm_load_refcount = 0;

শূন্য SDL_KMSDRM_UnloadSymbols(শূন্য)
{
    // Don't actually unload if more than one module is using the libs...
    যদি (kmsdrm_load_refcount > 0) {
        যদি (--kmsdrm_load_refcount == 0) {
#ifdef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
            পূর্ণাঙ্ক i;
#endif

            // set all the function pointers to NULL.
#define SDL_KMSDRM_MODULE(modname)          SDL_KMSDRM_HAVE_##modname = 0;
#define SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = রিক্ত;
#define SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = রিক্ত;
#define SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = রিক্ত;
#অন্তর্ভাৱ "SDL_kmsdrmsym.h"

#ifdef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
            বাবে (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
                যদি (kmsdrmlibs[i].lib) {
                    SDL_UnloadObject(kmsdrmlibs[i].lib);
                    kmsdrmlibs[i].lib = রিক্ত;
                }
            }
#endif
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_KMSDRM_LoadSymbols(শূন্য)
{
    bool result = true; // always succeed if not using Dynamic KMSDRM stuff.

    // deal with multiple modules needing these symbols...
    যদি (kmsdrm_load_refcount++ == 0) {
#ifdef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
        পূর্ণাঙ্ক i;
        পূর্ণাঙ্ক *thismod = রিক্ত;
        বাবে (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
            যদি (kmsdrmlibs[i].libname) {
                kmsdrmlibs[i].lib = SDL_LoadObject(kmsdrmlibs[i].libname);
            }
        }

#define SDL_KMSDRM_MODULE(modname) SDL_KMSDRM_HAVE_##modname = 1; // default yes
#অন্তর্ভাৱ "SDL_kmsdrmsym.h"

#define SDL_KMSDRM_MODULE(modname)          thismod = &SDL_KMSDRM_HAVE_##modname;
#define SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = (SDL_DYNKMSDRMFN_##fn)KMSDRM_GetSym(#fn, thismod, true);
#define SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = *(SDL_DYNKMSDRMCONST_##name *)KMSDRM_GetSym(#name, thismod, true);
#define SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = (SDL_DYNKMSDRMFN_##fn)KMSDRM_GetSym(#fn, thismod, false);
#অন্তর্ভাৱ "SDL_kmsdrmsym.h"

        যদি ((SDL_KMSDRM_HAVE_LIBDRM) && (SDL_KMSDRM_HAVE_GBM)) {
            // all required symbols loaded.
            SDL_ClearError();
        } অন্যথা {
            // in case something got loaded...
            SDL_KMSDRM_UnloadSymbols();
            result = false;
        }

#অন্যথা // no dynamic KMSDRM

#define SDL_KMSDRM_MODULE(modname)          SDL_KMSDRM_HAVE_##modname = 1; // default yes
#define SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = fn;
#define SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = name;
#define SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = fn;
#অন্তর্ভাৱ "SDL_kmsdrmsym.h"

#endif
    }

    ঘূৰাই result;
}

#endif // SDL_VIDEO_DRIVER_KMSDRM
