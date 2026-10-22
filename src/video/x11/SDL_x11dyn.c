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

#ifdef SDL_VIDEO_DRIVER_X11

#define DEBUG_DYNAMIC_X11 0

#অন্তর্ভাৱ "SDL_x11dyn.h"

#যদি DEBUG_DYNAMIC_X11
#অন্তর্ভাৱ <stdio.h>
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC

প্রকারনির্দেশ সংরচনা
{
    SDL_SharedObject *lib;
    ধ্রুৱ ৱর্ণ *libname;
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
#অন্যথা
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT রিক্ত
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR
)
#অন্যথা
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR রিক্ত
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2
)
#অন্যথা
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2 রিক্ত
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES
)
#অন্যথা
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES রিক্ত
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR
)
#অন্যথা
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR রিক্ত
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS
)
#অন্যথা
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS রিক্ত
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST
)
#অন্যথা
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST রিক্ত
#endif

স্থির x11dynlib x11libs[] = {
    { রিক্ত, SDL_VIDEO_DRIVER_X11_DYNAMIC },
    { রিক্ত, SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT },
    { রিক্ত, SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR },
    { রিক্ত, SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2 },
    { রিক্ত, SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES },
    { রিক্ত, SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR },
    { রিক্ত, SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS },
    { রিক্ত, SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST }
};

স্থির শূন্য *X11_GetSym(ধ্রুৱ ৱর্ণ *fnname, পূর্ণাঙ্ক *pHasModule)
{
    পূর্ণাঙ্ক i;
    শূন্য *fn = রিক্ত;
    বাবে (i = 0; i < SDL_arraysize(x11libs); i++) {
        যদি (x11libs[i].lib) {
            fn = SDL_LoadFunction(x11libs[i].lib, fnname);
            যদি (fn) {
                ভঙ্গ;
            }
        }
    }

#যদি DEBUG_DYNAMIC_X11
    যদি (fn) {
        SDL_Log("X11: Found '%s' in %s (%p)", fnname, x11libs[i].libname, fn);
    } অন্যথা {
        SDL_Log("X11: Symbol '%s' NOT FOUND!", fnname);
    }
#endif

    যদি (!fn) {
        *pHasModule = 0; // kill this module.
    }

    ঘূৰাই fn;
}

#endif // SDL_VIDEO_DRIVER_X11_DYNAMIC

// Define all the function pointers and wrappers...
#define SDL_X11_SYM(rc, fn, params) SDL_DYNX11FN_##fn X11_##fn = রিক্ত;
#অন্তর্ভাৱ "SDL_x11sym.h"

/* These SDL_X11_HAVE_* flags are here whether you have dynamic X11 or not. */
#define SDL_X11_MODULE(modname) পূর্ণাঙ্ক SDL_X11_HAVE_##modname = 0;
#অন্তর্ভাৱ "SDL_x11sym.h"

স্থির পূর্ণাঙ্ক x11_load_refcount = 0;

শূন্য SDL_X11_UnloadSymbols(শূন্য)
{
    // Don't actually unload if more than one module is using the libs...
    যদি (x11_load_refcount > 0) {
        যদি (--x11_load_refcount == 0) {
#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC
            পূর্ণাঙ্ক i;
#endif

            // set all the function pointers to NULL.
#define SDL_X11_MODULE(modname)                SDL_X11_HAVE_##modname = 0;
#define SDL_X11_SYM(rc, fn, params) X11_##fn = রিক্ত;
#অন্তর্ভাৱ "SDL_x11sym.h"

#ifdef X_HAVE_UTF8_STRING
            X11_XCreateIC = রিক্ত;
            X11_XGetICValues = রিক্ত;
            X11_XSetICValues = রিক্ত;
            X11_XVaCreateNestedList = রিক্ত;
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC
            বাবে (i = 0; i < SDL_arraysize(x11libs); i++) {
                যদি (x11libs[i].lib) {
                    SDL_UnloadObject(x11libs[i].lib);
                    x11libs[i].lib = রিক্ত;
                }
            }
#endif
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_X11_LoadSymbols(শূন্য)
{
    bool result = true; // always succeed if not using Dynamic X11 stuff.

    // deal with multiple modules (dga, x11, etc) needing these symbols...
    যদি (x11_load_refcount++ == 0) {
#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC
        পূর্ণাঙ্ক i;
        পূর্ণাঙ্ক *thismod = রিক্ত;
        বাবে (i = 0; i < SDL_arraysize(x11libs); i++) {
            যদি (x11libs[i].libname) {
                x11libs[i].lib = SDL_LoadObject(x11libs[i].libname);
            }
        }

#define SDL_X11_MODULE(modname) SDL_X11_HAVE_##modname = 1; // default yes
#অন্তর্ভাৱ "SDL_x11sym.h"

#define SDL_X11_MODULE(modname)     thismod = &SDL_X11_HAVE_##modname;
#define SDL_X11_SYM(rc, fn, params) X11_##fn = (SDL_DYNX11FN_##fn)X11_GetSym(#fn, thismod);
#অন্তর্ভাৱ "SDL_x11sym.h"

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

        যদি (SDL_X11_HAVE_BASEXLIB) {
            // all required symbols loaded.
            SDL_ClearError();
        } অন্যথা {
            // in case something got loaded...
            SDL_X11_UnloadSymbols();
            result = false;
        }

#অন্যথা // no dynamic X11

#define SDL_X11_MODULE(modname)     SDL_X11_HAVE_##modname = 1; // default yes
#define SDL_X11_SYM(rc, fn, params) X11_##fn = (SDL_DYNX11FN_##fn)fn;
#অন্তর্ভাৱ "SDL_x11sym.h"

#ifdef X_HAVE_UTF8_STRING
        X11_XCreateIC = XCreateIC;
        X11_XGetICValues = XGetICValues;
        X11_XSetICValues = XSetICValues;
        X11_XVaCreateNestedList = XVaCreateNestedList;
#endif
#endif
    }

    ঘূৰাই result;
}

#endif // SDL_VIDEO_DRIVER_X11
