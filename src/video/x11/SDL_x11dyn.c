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

#ifdef SDL_VIDEO_DRIVER_X11

#define DEBUG_DYNAMIC_X11 0

#അന്തര്ഭാവ "SDL_x11dyn.h"

#എങ്കിൽ DEBUG_DYNAMIC_X11
#അന്തര്ഭാവ <stdio.h>
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC

തരനിർവചനം ഘടന
{
    SDL_SharedObject *lib;
    സ്ഥിരം അക്ഷരം *libname;
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
#അല്ലെങ്കിൽ
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT ശൂന്യ
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR
)
#അല്ലെങ്കിൽ
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR ശൂന്യ
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2
)
#അല്ലെങ്കിൽ
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2 ശൂന്യ
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES
)
#അല്ലെങ്കിൽ
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES ശൂന്യ
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR
)
#അല്ലെങ്കിൽ
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR ശൂന്യ
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS
)
#അല്ലെങ്കിൽ
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS ശൂന്യ
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST
)
#അല്ലെങ്കിൽ
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST ശൂന്യ
#endif

സ്ഥിതം x11dynlib x11libs[] = {
    { ശൂന്യ, SDL_VIDEO_DRIVER_X11_DYNAMIC },
    { ശൂന്യ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT },
    { ശൂന്യ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR },
    { ശൂന്യ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2 },
    { ശൂന്യ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES },
    { ശൂന്യ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR },
    { ശൂന്യ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS },
    { ശൂന്യ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST }
};

സ്ഥിതം ശൂന്യം *X11_GetSym(സ്ഥിരം അക്ഷരം *fnname, പൂർണ്ണസംഖ്യ *pHasModule)
{
    പൂർണ്ണസംഖ്യ i;
    ശൂന്യം *fn = ശൂന്യ;
    വേണ്ടി (i = 0; i < SDL_arraysize(x11libs); i++) {
        എങ്കിൽ (x11libs[i].lib) {
            fn = SDL_LoadFunction(x11libs[i].lib, fnname);
            എങ്കിൽ (fn) {
                നിർത്തുക;
            }
        }
    }

#എങ്കിൽ DEBUG_DYNAMIC_X11
    എങ്കിൽ (fn) {
        SDL_Log("X11: Found '%s' in %s (%p)", fnname, x11libs[i].libname, fn);
    } അല്ലെങ്കിൽ {
        SDL_Log("X11: Symbol '%s' NOT FOUND!", fnname);
    }
#endif

    എങ്കിൽ (!fn) {
        *pHasModule = 0; // kill this module.
    }

    തിരികെ fn;
}

#endif // SDL_VIDEO_DRIVER_X11_DYNAMIC

// Define all the function pointers and wrappers...
#define SDL_X11_SYM(rc, fn, params) SDL_DYNX11FN_##fn X11_##fn = ശൂന്യ;
#അന്തര്ഭാവ "SDL_x11sym.h"

/* These SDL_X11_HAVE_* flags are here whether you have dynamic X11 or not. */
#define SDL_X11_MODULE(modname) പൂർണ്ണസംഖ്യ SDL_X11_HAVE_##modname = 0;
#അന്തര്ഭാവ "SDL_x11sym.h"

സ്ഥിതം പൂർണ്ണസംഖ്യ x11_load_refcount = 0;

ശൂന്യം SDL_X11_UnloadSymbols(ശൂന്യം)
{
    // Don't actually unload if more than one module is using the libs...
    എങ്കിൽ (x11_load_refcount > 0) {
        എങ്കിൽ (--x11_load_refcount == 0) {
#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC
            പൂർണ്ണസംഖ്യ i;
#endif

            // set all the function pointers to NULL.
#define SDL_X11_MODULE(modname)                SDL_X11_HAVE_##modname = 0;
#define SDL_X11_SYM(rc, fn, params) X11_##fn = ശൂന്യ;
#അന്തര്ഭാവ "SDL_x11sym.h"

#ifdef X_HAVE_UTF8_STRING
            X11_XCreateIC = ശൂന്യ;
            X11_XGetICValues = ശൂന്യ;
            X11_XSetICValues = ശൂന്യ;
            X11_XVaCreateNestedList = ശൂന്യ;
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC
            വേണ്ടി (i = 0; i < SDL_arraysize(x11libs); i++) {
                എങ്കിൽ (x11libs[i].lib) {
                    SDL_UnloadObject(x11libs[i].lib);
                    x11libs[i].lib = ശൂന്യ;
                }
            }
#endif
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_X11_LoadSymbols(ശൂന്യം)
{
    bool result = true; // always succeed if not using Dynamic X11 stuff.

    // deal with multiple modules (dga, x11, etc) needing these symbols...
    എങ്കിൽ (x11_load_refcount++ == 0) {
#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC
        പൂർണ്ണസംഖ്യ i;
        പൂർണ്ണസംഖ്യ *thismod = ശൂന്യ;
        വേണ്ടി (i = 0; i < SDL_arraysize(x11libs); i++) {
            എങ്കിൽ (x11libs[i].libname) {
                x11libs[i].lib = SDL_LoadObject(x11libs[i].libname);
            }
        }

#define SDL_X11_MODULE(modname) SDL_X11_HAVE_##modname = 1; // default yes
#അന്തര്ഭാവ "SDL_x11sym.h"

#define SDL_X11_MODULE(modname)     thismod = &SDL_X11_HAVE_##modname;
#define SDL_X11_SYM(rc, fn, params) X11_##fn = (SDL_DYNX11FN_##fn)X11_GetSym(#fn, thismod);
#അന്തര്ഭാവ "SDL_x11sym.h"

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

        എങ്കിൽ (SDL_X11_HAVE_BASEXLIB) {
            // all required symbols loaded.
            SDL_ClearError();
        } അല്ലെങ്കിൽ {
            // in case something got loaded...
            SDL_X11_UnloadSymbols();
            result = false;
        }

#അല്ലെങ്കിൽ // no dynamic X11

#define SDL_X11_MODULE(modname)     SDL_X11_HAVE_##modname = 1; // default yes
#define SDL_X11_SYM(rc, fn, params) X11_##fn = (SDL_DYNX11FN_##fn)fn;
#അന്തര്ഭാവ "SDL_x11sym.h"

#ifdef X_HAVE_UTF8_STRING
        X11_XCreateIC = XCreateIC;
        X11_XGetICValues = XGetICValues;
        X11_XSetICValues = XSetICValues;
        X11_XVaCreateNestedList = XVaCreateNestedList;
#endif
#endif
    }

    തിരികെ result;
}

#endif // SDL_VIDEO_DRIVER_X11
