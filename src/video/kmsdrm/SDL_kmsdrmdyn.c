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

#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_KMSDRM

#تعریف_کرو DEBUG_DYNAMIC_KMSDRM 0

#شامل "SDL_kmsdrmdyn.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC

SDL_ELF_NOTE_DLOPEN(
    "video-kmsdrm",
    "Support for KMSDRM",
    SDL_ELF_NOTE_DLOPEN_ترجیح_SUGGESTED,
    SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
)

قسمتعریف ساخت
{
    خالی *lib;
    ثابت حرف *libname;
} kmsdrmdynlib;

#اگر_غیر_تعریف_شدہ SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM
#تعریف_کرو SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM تہی
#اگر_ختم

ساکن kmsdrmdynlib kmsdrmlibs[] = {
    { تہی, SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM },
    { تہی, SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC }
};

ساکن خالی *KMSDRM_GetSym(ثابت حرف *fnname, صحیح *pHasModule, bool required)
{
    صحیح i;
    خالی *fn = تہی;
    برائے (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
        اگر (kmsdrmlibs[i].lib) {
            fn = SDL_بھرو_Function(kmsdrmlibs[i].lib, fnname);
            اگر (fn) {
                توڑو;
            }
        }
    }

#اگر DEBUG_DYNAMIC_KMSDRM
    اگر (fn)
        SDL_Log("KMSDRM: Found '%s' in %s (%p)", fnname, kmsdrmlibs[i].libname, fn);
    ورنہ
        SDL_Log("KMSDRM: Symbol '%s' NOT FOUND!", fnname);
#اگر_ختم

    اگر (!fn && required) {
        *pHasModule = 0; // kill this module.
    }

    واپس fn;
}

#اگر_ختم // SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC

// Define all the function pointers and wrappers...
#تعریف_کرو SDL_KMSDRM_MODULE(modname)          صحیح SDL_KMSDRM_HAVE_##modname = 0;
#تعریف_کرو SDL_KMSDRM_SYM(rc, fn, params)      SDL_DYNKMSDRMFN_##fn KMSDRM_##fn = تہی;
#تعریف_کرو SDL_KMSDRM_SYM_CONST(type, name)    SDL_DYNKMSDRMCONST_##name KMSDRM_##name = تہی;
#تعریف_کرو SDL_KMSDRM_SYM_OPT(rc, fn, params)  SDL_DYNKMSDRMFN_##fn KMSDRM_##fn = تہی;
#شامل "SDL_kmsdrmsym.h"

ساکن صحیح kmsdrm_بھرو_refcount = 0;

خالی SDL_KMSDRM_UnloadSymbols(خالی)
{
    // Don't actually unload if more than one module is using the libs...
    اگر (kmsdrm_بھرو_refcount > 0) {
        اگر (--kmsdrm_بھرو_refcount == 0) {
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
            صحیح i;
#اگر_ختم

            // set all the function pointers to NULL.
#تعریف_کرو SDL_KMSDRM_MODULE(modname)          SDL_KMSDRM_HAVE_##modname = 0;
#تعریف_کرو SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = تہی;
#تعریف_کرو SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = تہی;
#تعریف_کرو SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = تہی;
#شامل "SDL_kmsdrmsym.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
            برائے (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
                اگر (kmsdrmlibs[i].lib) {
                    SDL_UnloadObject(kmsdrmlibs[i].lib);
                    kmsdrmlibs[i].lib = تہی;
                }
            }
#اگر_ختم
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_KMSDRM_بھرو_Symbols(خالی)
{
    bool نتیجہ = true; // always succeed if not using Dynamic KMSDRM stuff.

    // deal with multiple modules needing these symbols...
    اگر (kmsdrm_بھرو_refcount++ == 0) {
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
        صحیح i;
        صحیح *thismod = تہی;
        برائے (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
            اگر (kmsdrmlibs[i].libname) {
                kmsdrmlibs[i].lib = SDL_بھرو_Object(kmsdrmlibs[i].libname);
            }
        }

#تعریف_کرو SDL_KMSDRM_MODULE(modname) SDL_KMSDRM_HAVE_##modname = 1; // default yes
#شامل "SDL_kmsdrmsym.h"

#تعریف_کرو SDL_KMSDRM_MODULE(modname)          thismod = &SDL_KMSDRM_HAVE_##modname;
#تعریف_کرو SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = (SDL_DYNKMSDRMFN_##fn)KMSDRM_GetSym(#fn, thismod, true);
#تعریف_کرو SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = *(SDL_DYNKMSDRMCONST_##name *)KMSDRM_GetSym(#name, thismod, true);
#تعریف_کرو SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = (SDL_DYNKMSDRMFN_##fn)KMSDRM_GetSym(#fn, thismod, false);
#شامل "SDL_kmsdrmsym.h"

        اگر ((SDL_KMSDRM_HAVE_LIBDRM) && (SDL_KMSDRM_HAVE_GBM)) {
            // all required symbols loaded.
            SDL_ClearError();
        } ورنہ {
            // in case something got loaded...
            SDL_KMSDRM_UnloadSymbols();
            نتیجہ = false;
        }

#ورنہ // no dynamic KMSDRM

#تعریف_کرو SDL_KMSDRM_MODULE(modname)          SDL_KMSDRM_HAVE_##modname = 1; // default yes
#تعریف_کرو SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = fn;
#تعریف_کرو SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = name;
#تعریف_کرو SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = fn;
#شامل "SDL_kmsdrmsym.h"

#اگر_ختم
    }

    واپس نتیجہ;
}

#اگر_ختم // SDL_VIDEO_DRIVER_KMSDRM
