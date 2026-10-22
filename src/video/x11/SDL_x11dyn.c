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
#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#define DEBUG_DYNAMIC_X11 0

#અન્તર્ભાવ "SDL_x11dyn.h"

#જો DEBUG_DYNAMIC_X11
#અન્તર્ભાવ <stdio.h>
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC

પ્રકારવ્યાખ્યા સંરચના
{
    SDL_SharedObject *lib;
    અચલ અક્ષર *libname;
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
#નહીંતર
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT ખાલી
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR
)
#નહીંતર
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR ખાલી
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2
)
#નહીંતર
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2 ખાલી
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES
)
#નહીંતર
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES ખાલી
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR
)
#નહીંતર
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR ખાલી
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS
)
#નહીંતર
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS ખાલી
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST
)
#નહીંતર
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST ખાલી
#endif

સ્થિર x11dynlib x11libs[] = {
    { ખાલી, SDL_VIDEO_DRIVER_X11_DYNAMIC },
    { ખાલી, SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT },
    { ખાલી, SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR },
    { ખાલી, SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2 },
    { ખાલી, SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES },
    { ખાલી, SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR },
    { ખાલી, SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS },
    { ખાલી, SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST }
};

સ્થિર શૂન્ય *X11_GetSym(અચલ અક્ષર *fnname, પૂર્ણાંક *pHasModule)
{
    પૂર્ણાંક i;
    શૂન્ય *fn = ખાલી;
    માટે (i = 0; i < SDL_arraysize(x11libs); i++) {
        જો (x11libs[i].lib) {
            fn = SDL_LoadFunction(x11libs[i].lib, fnname);
            જો (fn) {
                તોડો;
            }
        }
    }

#જો DEBUG_DYNAMIC_X11
    જો (fn) {
        SDL_Log("X11: Found '%s' in %s (%p)", fnname, x11libs[i].libname, fn);
    } નહીંતર {
        SDL_Log("X11: Symbol '%s' NOT FOUND!", fnname);
    }
#endif

    જો (!fn) {
        *pHasModule = 0; // kill this module.
    }

    પાછા fn;
}

#endif // SDL_VIDEO_DRIVER_X11_DYNAMIC

// Define all the function pointers and wrappers...
#define SDL_X11_SYM(rc, fn, params) SDL_DYNX11FN_##fn X11_##fn = ખાલી;
#અન્તર્ભાવ "SDL_x11sym.h"

/* These SDL_X11_HAVE_* flags are here whether you have dynamic X11 or not. */
#define SDL_X11_MODULE(modname) પૂર્ણાંક SDL_X11_HAVE_##modname = 0;
#અન્તર્ભાવ "SDL_x11sym.h"

સ્થિર પૂર્ણાંક x11_load_refcount = 0;

શૂન્ય SDL_X11_UnloadSymbols(શૂન્ય)
{
    // Don't actually unload if more than one module is using the libs...
    જો (x11_load_refcount > 0) {
        જો (--x11_load_refcount == 0) {
#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC
            પૂર્ણાંક i;
#endif

            // set all the function pointers to NULL.
#define SDL_X11_MODULE(modname)                SDL_X11_HAVE_##modname = 0;
#define SDL_X11_SYM(rc, fn, params) X11_##fn = ખાલી;
#અન્તર્ભાવ "SDL_x11sym.h"

#ifdef X_HAVE_UTF8_STRING
            X11_XCreateIC = ખાલી;
            X11_XGetICValues = ખાલી;
            X11_XSetICValues = ખાલી;
            X11_XVaCreateNestedList = ખાલી;
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC
            માટે (i = 0; i < SDL_arraysize(x11libs); i++) {
                જો (x11libs[i].lib) {
                    SDL_UnloadObject(x11libs[i].lib);
                    x11libs[i].lib = ખાલી;
                }
            }
#endif
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_X11_LoadSymbols(શૂન્ય)
{
    bool result = true; // always succeed if not using Dynamic X11 stuff.

    // deal with multiple modules (dga, x11, etc) needing these symbols...
    જો (x11_load_refcount++ == 0) {
#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC
        પૂર્ણાંક i;
        પૂર્ણાંક *thismod = ખાલી;
        માટે (i = 0; i < SDL_arraysize(x11libs); i++) {
            જો (x11libs[i].libname) {
                x11libs[i].lib = SDL_LoadObject(x11libs[i].libname);
            }
        }

#define SDL_X11_MODULE(modname) SDL_X11_HAVE_##modname = 1; // default yes
#અન્તર્ભાવ "SDL_x11sym.h"

#define SDL_X11_MODULE(modname)     thismod = &SDL_X11_HAVE_##modname;
#define SDL_X11_SYM(rc, fn, params) X11_##fn = (SDL_DYNX11FN_##fn)X11_GetSym(#fn, thismod);
#અન્તર્ભાવ "SDL_x11sym.h"

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

        જો (SDL_X11_HAVE_BASEXLIB) {
            // all required symbols loaded.
            SDL_ClearError();
        } નહીંતર {
            // in case something got loaded...
            SDL_X11_UnloadSymbols();
            result = false;
        }

#નહીંતર // no dynamic X11

#define SDL_X11_MODULE(modname)     SDL_X11_HAVE_##modname = 1; // default yes
#define SDL_X11_SYM(rc, fn, params) X11_##fn = (SDL_DYNX11FN_##fn)fn;
#અન્તર્ભાવ "SDL_x11sym.h"

#ifdef X_HAVE_UTF8_STRING
        X11_XCreateIC = XCreateIC;
        X11_XGetICValues = XGetICValues;
        X11_XSetICValues = XSetICValues;
        X11_XVaCreateNestedList = XVaCreateNestedList;
#endif
#endif
    }

    પાછા result;
}

#endif // SDL_VIDEO_DRIVER_X11
