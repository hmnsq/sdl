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
#ضمن "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#define DEBUG_DYNAMIC_X11 0

#ضمن "SDL_x11dyn.h"

#𐡄𐡍 DEBUG_DYNAMIC_X11
#ضمن <stdio.h>
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC

تعريفنوع بنية
{
    SDL_SharedObject *lib;
    ثابت حرف *libname;
} x11dynlib;

SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC
)

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT
)
#وإلا
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT عدم
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR
)
#وإلا
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR عدم
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2
)
#وإلا
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2 عدم
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES
)
#وإلا
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES عدم
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR
)
#وإلا
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR عدم
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS
)
#وإلا
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS عدم
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST
)
#وإلا
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST عدم
#endif

ساكن x11dynlib x11libs[] = {
    { عدم, SDL_VIDEO_DRIVER_X11_DYNAMIC },
    { عدم, SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT },
    { عدم, SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR },
    { عدم, SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2 },
    { عدم, SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES },
    { عدم, SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR },
    { عدم, SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS },
    { عدم, SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST }
};

ساكن فراغ *X11_GetSym(ثابت حرف *fnname, صحيح *pHasModule)
{
    صحيح i;
    فراغ *fn = عدم;
    لكل (i = 0; i < SDL_arraysize(x11libs); i++) {
        𐡄𐡍 (x11libs[i].lib) {
            fn = SDL_LoadFunction(x11libs[i].lib, fnname);
            𐡄𐡍 (fn) {
                اكسر;
            }
        }
    }

#𐡄𐡍 DEBUG_DYNAMIC_X11
    𐡄𐡍 (fn) {
        SDL_Log("X11: Found '%s' in %s (%p)", fnname, x11libs[i].libname, fn);
    } وإلا {
        SDL_Log("X11: Symbol '%s' NOT FOUND!", fnname);
    }
#endif

    𐡄𐡍 (!fn) {
        *pHasModule = 0; // kill this module.
    }

    أرجع fn;
}

#endif // SDL_VIDEO_DRIVER_X11_DYNAMIC

// Define all the function pointers and wrappers...
#define SDL_X11_SYM(rc, fn, params) SDL_DYNX11FN_##fn X11_##fn = عدم;
#ضمن "SDL_x11sym.h"

/* These SDL_X11_HAVE_* flags are here whether you have dynamic X11 or not. */
#define SDL_X11_MODULE(modname) صحيح SDL_X11_HAVE_##modname = 0;
#ضمن "SDL_x11sym.h"

ساكن صحيح x11_load_refcount = 0;

فراغ SDL_X11_UnloadSymbols(فراغ)
{
    // Don't actually unload if more than one module is using the libs...
    𐡄𐡍 (x11_load_refcount > 0) {
        𐡄𐡍 (--x11_load_refcount == 0) {
#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC
            صحيح i;
#endif

            // set all the function pointers to NULL.
#define SDL_X11_MODULE(modname)                SDL_X11_HAVE_##modname = 0;
#define SDL_X11_SYM(rc, fn, params) X11_##fn = عدم;
#ضمن "SDL_x11sym.h"

#ifdef X_HAVE_UTF8_STRING
            X11_XCreateIC = عدم;
            X11_XGetICValues = عدم;
            X11_XSetICValues = عدم;
            X11_XVaCreateNestedList = عدم;
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC
            لكل (i = 0; i < SDL_arraysize(x11libs); i++) {
                𐡄𐡍 (x11libs[i].lib) {
                    SDL_UnloadObject(x11libs[i].lib);
                    x11libs[i].lib = عدم;
                }
            }
#endif
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_X11_LoadSymbols(فراغ)
{
    bool result = true; // always succeed if not using Dynamic X11 stuff.

    // deal with multiple modules (dga, x11, etc) needing these symbols...
    𐡄𐡍 (x11_load_refcount++ == 0) {
#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC
        صحيح i;
        صحيح *thismod = عدم;
        لكل (i = 0; i < SDL_arraysize(x11libs); i++) {
            𐡄𐡍 (x11libs[i].libname) {
                x11libs[i].lib = SDL_LoadObject(x11libs[i].libname);
            }
        }

#define SDL_X11_MODULE(modname) SDL_X11_HAVE_##modname = 1; // default yes
#ضمن "SDL_x11sym.h"

#define SDL_X11_MODULE(modname)     thismod = &SDL_X11_HAVE_##modname;
#define SDL_X11_SYM(rc, fn, params) X11_##fn = (SDL_DYNX11FN_##fn)X11_GetSym(#fn, thismod);
#ضمن "SDL_x11sym.h"

#ifdef X_HAVE_UTF8_STRING
        X11_XCreateIC = (SDL_DYNX11FN_XCreateIC)
            X11_GetSym("XCreateIC", &SDL_X11_HAVE_UTF8);
        X11_XGetICValues = (SDL_DYNX11FN_XGetICValues)
            X11_GetSym("XGetICValues", &SDL_X11_HAVE_UTF8);
        X11_XSetICValues = (SDL_DYNX11FN_XSetICValues)
            X11_GetSym("XSetICValues", &SDL_X11_HAVE_UTF8);
        X11_XVaCreateNestedList = (SDL_DYNX11FN_XVaCreateNestedList)
            X11_GetSym("XVaCreateNestedList", &SDL_X11_HAVE_UTF8);
#endif

        𐡄𐡍 (SDL_X11_HAVE_BASEXLIB) {
            // all required symbols loaded.
            SDL_ClearError();
        } وإلا {
            // in case something got loaded...
            SDL_X11_UnloadSymbols();
            result = false;
        }

#وإلا // no dynamic X11

#define SDL_X11_MODULE(modname)     SDL_X11_HAVE_##modname = 1; // default yes
#define SDL_X11_SYM(rc, fn, params) X11_##fn = (SDL_DYNX11FN_##fn)fn;
#ضمن "SDL_x11sym.h"

#ifdef X_HAVE_UTF8_STRING
        X11_XCreateIC = XCreateIC;
        X11_XGetICValues = XGetICValues;
        X11_XSetICValues = XSetICValues;
        X11_XVaCreateNestedList = XVaCreateNestedList;
#endif
#endif
    }

    أرجع result;
}

#endif // SDL_VIDEO_DRIVER_X11
