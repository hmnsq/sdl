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

#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_KMSDRM

#define DEBUG_DYNAMIC_KMSDRM 0

#അന്തര്ഭാവ "SDL_kmsdrmdyn.h"

#ifdef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC

SDL_ELF_NOTE_DLOPEN(
    "video-kmsdrm",
    "Support for KMSDRM",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
)

തരനിർവചനം ഘടന
{
    ശൂന്യം *lib;
    സ്ഥിരം അക്ഷരം *libname;
} kmsdrmdynlib;

#ifndef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM
#define SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM ശൂന്യ
#endif

സ്ഥിതം kmsdrmdynlib kmsdrmlibs[] = {
    { ശൂന്യ, SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM },
    { ശൂന്യ, SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC }
};

സ്ഥിതം ശൂന്യം *KMSDRM_GetSym(സ്ഥിരം അക്ഷരം *fnname, പൂർണ്ണസംഖ്യ *pHasModule, bool required)
{
    പൂർണ്ണസംഖ്യ i;
    ശൂന്യം *fn = ശൂന്യ;
    വേണ്ടി (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
        എങ്കിൽ (kmsdrmlibs[i].lib) {
            fn = SDL_LoadFunction(kmsdrmlibs[i].lib, fnname);
            എങ്കിൽ (fn) {
                നിർത്തുക;
            }
        }
    }

#എങ്കിൽ DEBUG_DYNAMIC_KMSDRM
    എങ്കിൽ (fn)
        SDL_Log("KMSDRM: Found '%s' in %s (%p)", fnname, kmsdrmlibs[i].libname, fn);
    അല്ലെങ്കിൽ
        SDL_Log("KMSDRM: Symbol '%s' NOT FOUND!", fnname);
#endif

    എങ്കിൽ (!fn && required) {
        *pHasModule = 0; // kill this module.
    }

    തിരികെ fn;
}

#endif // SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC

// Define all the function pointers and wrappers...
#define SDL_KMSDRM_MODULE(modname)          പൂർണ്ണസംഖ്യ SDL_KMSDRM_HAVE_##modname = 0;
#define SDL_KMSDRM_SYM(rc, fn, params)      SDL_DYNKMSDRMFN_##fn KMSDRM_##fn = ശൂന്യ;
#define SDL_KMSDRM_SYM_CONST(type, name)    SDL_DYNKMSDRMCONST_##name KMSDRM_##name = ശൂന്യ;
#define SDL_KMSDRM_SYM_OPT(rc, fn, params)  SDL_DYNKMSDRMFN_##fn KMSDRM_##fn = ശൂന്യ;
#അന്തര്ഭാവ "SDL_kmsdrmsym.h"

സ്ഥിതം പൂർണ്ണസംഖ്യ kmsdrm_load_refcount = 0;

ശൂന്യം SDL_KMSDRM_UnloadSymbols(ശൂന്യം)
{
    // Don't actually unload if more than one module is using the libs...
    എങ്കിൽ (kmsdrm_load_refcount > 0) {
        എങ്കിൽ (--kmsdrm_load_refcount == 0) {
#ifdef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
            പൂർണ്ണസംഖ്യ i;
#endif

            // set all the function pointers to NULL.
#define SDL_KMSDRM_MODULE(modname)          SDL_KMSDRM_HAVE_##modname = 0;
#define SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = ശൂന്യ;
#define SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = ശൂന്യ;
#define SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = ശൂന്യ;
#അന്തര്ഭാവ "SDL_kmsdrmsym.h"

#ifdef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
            വേണ്ടി (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
                എങ്കിൽ (kmsdrmlibs[i].lib) {
                    SDL_UnloadObject(kmsdrmlibs[i].lib);
                    kmsdrmlibs[i].lib = ശൂന്യ;
                }
            }
#endif
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_KMSDRM_LoadSymbols(ശൂന്യം)
{
    bool result = true; // always succeed if not using Dynamic KMSDRM stuff.

    // deal with multiple modules needing these symbols...
    എങ്കിൽ (kmsdrm_load_refcount++ == 0) {
#ifdef SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
        പൂർണ്ണസംഖ്യ i;
        പൂർണ്ണസംഖ്യ *thismod = ശൂന്യ;
        വേണ്ടി (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
            എങ്കിൽ (kmsdrmlibs[i].libname) {
                kmsdrmlibs[i].lib = SDL_LoadObject(kmsdrmlibs[i].libname);
            }
        }

#define SDL_KMSDRM_MODULE(modname) SDL_KMSDRM_HAVE_##modname = 1; // default yes
#അന്തര്ഭാവ "SDL_kmsdrmsym.h"

#define SDL_KMSDRM_MODULE(modname)          thismod = &SDL_KMSDRM_HAVE_##modname;
#define SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = (SDL_DYNKMSDRMFN_##fn)KMSDRM_GetSym(#fn, thismod, true);
#define SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = *(SDL_DYNKMSDRMCONST_##name *)KMSDRM_GetSym(#name, thismod, true);
#define SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = (SDL_DYNKMSDRMFN_##fn)KMSDRM_GetSym(#fn, thismod, false);
#അന്തര്ഭാവ "SDL_kmsdrmsym.h"

        എങ്കിൽ ((SDL_KMSDRM_HAVE_LIBDRM) && (SDL_KMSDRM_HAVE_GBM)) {
            // all required symbols loaded.
            SDL_ClearError();
        } അല്ലെങ്കിൽ {
            // in case something got loaded...
            SDL_KMSDRM_UnloadSymbols();
            result = false;
        }

#അല്ലെങ്കിൽ // no dynamic KMSDRM

#define SDL_KMSDRM_MODULE(modname)          SDL_KMSDRM_HAVE_##modname = 1; // default yes
#define SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = fn;
#define SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = name;
#define SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = fn;
#അന്തര്ഭാവ "SDL_kmsdrmsym.h"

#endif
    }

    തിരികെ result;
}

#endif // SDL_VIDEO_DRIVER_KMSDRM
