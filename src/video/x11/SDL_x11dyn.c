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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#define DEBUG_DYNAMIC_X11 0

#ଅନ୍ତର୍ଭାଵ "SDL_x11dyn.h"

#ଯଦି DEBUG_DYNAMIC_X11
#ଅନ୍ତର୍ଭାଵ <stdio.h>
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା
{
    SDL_SharedObject *lib;
    ଅଚଳ ଅକ୍ଷର *libname;
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
#ଅନ୍ୟଥା
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT ଖାଲି
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR
)
#ଅନ୍ୟଥା
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR ଖାଲି
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2
)
#ଅନ୍ୟଥା
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2 ଖାଲି
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES
)
#ଅନ୍ୟଥା
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES ଖାଲି
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR
)
#ଅନ୍ୟଥା
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR ଖାଲି
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS
)
#ଅନ୍ୟଥା
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS ଖାଲି
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST
)
#ଅନ୍ୟଥା
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST ଖାଲି
#endif

ସ୍ଥିର x11dynlib x11libs[] = {
    { ଖାଲି, SDL_VIDEO_DRIVER_X11_DYNAMIC },
    { ଖାଲି, SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT },
    { ଖାଲି, SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR },
    { ଖାଲି, SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2 },
    { ଖାଲି, SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES },
    { ଖାଲି, SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR },
    { ଖାଲି, SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS },
    { ଖାଲି, SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST }
};

ସ୍ଥିର ଶୂନ୍ୟ *X11_GetSym(ଅଚଳ ଅକ୍ଷର *fnname, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *pHasModule)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ଶୂନ୍ୟ *fn = ଖାଲି;
    ପାଇଁ (i = 0; i < SDL_arraysize(x11libs); i++) {
        ଯଦି (x11libs[i].lib) {
            fn = SDL_LoadFunction(x11libs[i].lib, fnname);
            ଯଦି (fn) {
                ଭାଙ୍ଗ;
            }
        }
    }

#ଯଦି DEBUG_DYNAMIC_X11
    ଯଦି (fn) {
        SDL_Log("X11: Found '%s' in %s (%p)", fnname, x11libs[i].libname, fn);
    } ଅନ୍ୟଥା {
        SDL_Log("X11: Symbol '%s' NOT FOUND!", fnname);
    }
#endif

    ଯଦି (!fn) {
        *pHasModule = 0; // kill this module.
    }

    ଫେରନ୍ତୁ fn;
}

#endif // SDL_VIDEO_DRIVER_X11_DYNAMIC

// Define all the function pointers and wrappers...
#define SDL_X11_SYM(rc, fn, params) SDL_DYNX11FN_##fn X11_##fn = ଖାଲି;
#ଅନ୍ତର୍ଭାଵ "SDL_x11sym.h"

/* These SDL_X11_HAVE_* flags are here whether you have dynamic X11 or not. */
#define SDL_X11_MODULE(modname) ପୂର୍ଣ୍ଣସଂଖ୍ୟା SDL_X11_HAVE_##modname = 0;
#ଅନ୍ତର୍ଭାଵ "SDL_x11sym.h"

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା x11_load_refcount = 0;

ଶୂନ୍ୟ SDL_X11_UnloadSymbols(ଶୂନ୍ୟ)
{
    // Don't actually unload if more than one module is using the libs...
    ଯଦି (x11_load_refcount > 0) {
        ଯଦି (--x11_load_refcount == 0) {
#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
#endif

            // set all the function pointers to NULL.
#define SDL_X11_MODULE(modname)                SDL_X11_HAVE_##modname = 0;
#define SDL_X11_SYM(rc, fn, params) X11_##fn = ଖାଲି;
#ଅନ୍ତର୍ଭାଵ "SDL_x11sym.h"

#ifdef X_HAVE_UTF8_STRING
            X11_XCreateIC = ଖାଲି;
            X11_XGetICValues = ଖାଲି;
            X11_XSetICValues = ଖାଲି;
            X11_XVaCreateNestedList = ଖାଲି;
#endif

#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC
            ପାଇଁ (i = 0; i < SDL_arraysize(x11libs); i++) {
                ଯଦି (x11libs[i].lib) {
                    SDL_UnloadObject(x11libs[i].lib);
                    x11libs[i].lib = ଖାଲି;
                }
            }
#endif
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_X11_LoadSymbols(ଶୂନ୍ୟ)
{
    bool result = true; // always succeed if not using Dynamic X11 stuff.

    // deal with multiple modules (dga, x11, etc) needing these symbols...
    ଯଦି (x11_load_refcount++ == 0) {
#ifdef SDL_VIDEO_DRIVER_X11_DYNAMIC
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା *thismod = ଖାଲି;
        ପାଇଁ (i = 0; i < SDL_arraysize(x11libs); i++) {
            ଯଦି (x11libs[i].libname) {
                x11libs[i].lib = SDL_LoadObject(x11libs[i].libname);
            }
        }

#define SDL_X11_MODULE(modname) SDL_X11_HAVE_##modname = 1; // default yes
#ଅନ୍ତର୍ଭାଵ "SDL_x11sym.h"

#define SDL_X11_MODULE(modname)     thismod = &SDL_X11_HAVE_##modname;
#define SDL_X11_SYM(rc, fn, params) X11_##fn = (SDL_DYNX11FN_##fn)X11_GetSym(#fn, thismod);
#ଅନ୍ତର୍ଭାଵ "SDL_x11sym.h"

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

        ଯଦି (SDL_X11_HAVE_BASEXLIB) {
            // all required symbols loaded.
            SDL_ClearError();
        } ଅନ୍ୟଥା {
            // in case something got loaded...
            SDL_X11_UnloadSymbols();
            result = false;
        }

#ଅନ୍ୟଥା // no dynamic X11

#define SDL_X11_MODULE(modname)     SDL_X11_HAVE_##modname = 1; // default yes
#define SDL_X11_SYM(rc, fn, params) X11_##fn = (SDL_DYNX11FN_##fn)fn;
#ଅନ୍ତର୍ଭାଵ "SDL_x11sym.h"

#ifdef X_HAVE_UTF8_STRING
        X11_XCreateIC = XCreateIC;
        X11_XGetICValues = XGetICValues;
        X11_XSetICValues = XSetICValues;
        X11_XVaCreateNestedList = XVaCreateNestedList;
#endif
#endif
    }

    ଫେରନ୍ତୁ result;
}

#endif // SDL_VIDEO_DRIVER_X11
