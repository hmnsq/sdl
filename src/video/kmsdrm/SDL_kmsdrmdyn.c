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

#अन्तर्भाव "SDL_internal.h"

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_KMSDRM

#परिभाषय DEBUG_DYNAMIC_KMSDRM 0

#अन्तर्भाव "SDL_kmsdrmdyn.h"

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC

SDL_ELF_NOTE_DLOPEN(
    "video-kmsdrm",
    "Support for KMSDRM",
    SDL_ELF_NOTE_DLOPEN_प्राथमिकता_SUGGESTED,
    SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
)

प्रकारनिर्देश संरचना
{
    शून्य *lib;
    ध्रुव वर्ण *libname;
} kmsdrmdynlib;

#यदि_अपरिभाषितम् SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM
#परिभाषय SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM रिक्त
#यदि_अन्तः

स्थिर kmsdrmdynlib kmsdrmlibs[] = {
    { रिक्त, SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM },
    { रिक्त, SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC }
};

स्थिर शून्य *KMSDRM_GetSym(ध्रुव वर्ण *fnname, पूर्णाङ्क *pHasModule, bool required)
{
    पूर्णाङ्क i;
    शून्य *fn = रिक्त;
    प्रति (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
        यदि (kmsdrmlibs[i].lib) {
            fn = SDL_आरोपय_Function(kmsdrmlibs[i].lib, fnname);
            यदि (fn) {
                भङ्ग;
            }
        }
    }

#यदि DEBUG_DYNAMIC_KMSDRM
    यदि (fn)
        SDL_Log("KMSDRM: Found '%s' in %s (%p)", fnname, kmsdrmlibs[i].libname, fn);
    अन्यथा
        SDL_Log("KMSDRM: Symbol '%s' NOT FOUND!", fnname);
#यदि_अन्तः

    यदि (!fn && required) {
        *pHasModule = 0; // kill this module.
    }

    प्रत्यागम fn;
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC

// Define all the function pointers and wrappers...
#परिभाषय SDL_KMSDRM_MODULE(modname)          पूर्णाङ्क SDL_KMSDRM_HAVE_##modname = 0;
#परिभाषय SDL_KMSDRM_SYM(rc, fn, params)      SDL_DYNKMSDRMFN_##fn KMSDRM_##fn = रिक्त;
#परिभाषय SDL_KMSDRM_SYM_CONST(type, name)    SDL_DYNKMSDRMCONST_##name KMSDRM_##name = रिक्त;
#परिभाषय SDL_KMSDRM_SYM_OPT(rc, fn, params)  SDL_DYNKMSDRMFN_##fn KMSDRM_##fn = रिक्त;
#अन्तर्भाव "SDL_kmsdrmsym.h"

स्थिर पूर्णाङ्क kmsdrm_आरोपय_refcount = 0;

शून्य SDL_KMSDRM_UnloadSymbols(शून्य)
{
    // Don't actually unload if more than one module is using the libs...
    यदि (kmsdrm_आरोपय_refcount > 0) {
        यदि (--kmsdrm_आरोपय_refcount == 0) {
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
            पूर्णाङ्क i;
#यदि_अन्तः

            // set all the function pointers to NULL.
#परिभाषय SDL_KMSDRM_MODULE(modname)          SDL_KMSDRM_HAVE_##modname = 0;
#परिभाषय SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = रिक्त;
#परिभाषय SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = रिक्त;
#परिभाषय SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = रिक्त;
#अन्तर्भाव "SDL_kmsdrmsym.h"

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
            प्रति (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
                यदि (kmsdrmlibs[i].lib) {
                    SDL_UnloadObject(kmsdrmlibs[i].lib);
                    kmsdrmlibs[i].lib = रिक्त;
                }
            }
#यदि_अन्तः
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_KMSDRM_आरोपय_Symbols(शून्य)
{
    bool परिणाम = true; // always succeed if not using Dynamic KMSDRM stuff.

    // deal with multiple modules needing these symbols...
    यदि (kmsdrm_आरोपय_refcount++ == 0) {
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC
        पूर्णाङ्क i;
        पूर्णाङ्क *thismod = रिक्त;
        प्रति (i = 0; i < SDL_arraysize(kmsdrmlibs); i++) {
            यदि (kmsdrmlibs[i].libname) {
                kmsdrmlibs[i].lib = SDL_आरोपय_Object(kmsdrmlibs[i].libname);
            }
        }

#परिभाषय SDL_KMSDRM_MODULE(modname) SDL_KMSDRM_HAVE_##modname = 1; // default yes
#अन्तर्भाव "SDL_kmsdrmsym.h"

#परिभाषय SDL_KMSDRM_MODULE(modname)          thismod = &SDL_KMSDRM_HAVE_##modname;
#परिभाषय SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = (SDL_DYNKMSDRMFN_##fn)KMSDRM_GetSym(#fn, thismod, true);
#परिभाषय SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = *(SDL_DYNKMSDRMCONST_##name *)KMSDRM_GetSym(#name, thismod, true);
#परिभाषय SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = (SDL_DYNKMSDRMFN_##fn)KMSDRM_GetSym(#fn, thismod, false);
#अन्तर्भाव "SDL_kmsdrmsym.h"

        यदि ((SDL_KMSDRM_HAVE_LIBDRM) && (SDL_KMSDRM_HAVE_GBM)) {
            // all required symbols loaded.
            SDL_ClearError();
        } अन्यथा {
            // in case something got loaded...
            SDL_KMSDRM_UnloadSymbols();
            परिणाम = false;
        }

#अन्यथा // no dynamic KMSDRM

#परिभाषय SDL_KMSDRM_MODULE(modname)          SDL_KMSDRM_HAVE_##modname = 1; // default yes
#परिभाषय SDL_KMSDRM_SYM(rc, fn, params)      KMSDRM_##fn = fn;
#परिभाषय SDL_KMSDRM_SYM_CONST(type, name)    KMSDRM_##name = name;
#परिभाषय SDL_KMSDRM_SYM_OPT(rc, fn, params)  KMSDRM_##fn = fn;
#अन्तर्भाव "SDL_kmsdrmsym.h"

#यदि_अन्तः
    }

    प्रत्यागम परिणाम;
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_KMSDRM
