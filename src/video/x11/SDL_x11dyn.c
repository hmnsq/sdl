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

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11

#నిర్వచించు DEBUG_DYNAMIC_X11 0

#అన్తర్భావ "SDL_x11dyn.h"

#ఒకవేళ DEBUG_DYNAMIC_X11
#అన్తర్భావ <stdio.h>
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_DYNAMIC

రకనిర్వచనం నిర్మాణం
{
    SDL_SharedObject *lib;
    స్థిరరాశి అక్షరం *libname;
} x11dynlib;

SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_ప్రాధాన్యత_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC
)

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_ప్రాధాన్యత_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT
)
#లేకపోతే
#నిర్వచించు SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT ఖాళీ
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_ప్రాధాన్యత_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR
)
#లేకపోతే
#నిర్వచించు SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR ఖాళీ
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_ప్రాధాన్యత_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2
)
#లేకపోతే
#నిర్వచించు SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2 ఖాళీ
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_ప్రాధాన్యత_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES
)
#లేకపోతే
#నిర్వచించు SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES ఖాళీ
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_ప్రాధాన్యత_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR
)
#లేకపోతే
#నిర్వచించు SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR ఖాళీ
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_ప్రాధాన్యత_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS
)
#లేకపోతే
#నిర్వచించు SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS ఖాళీ
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_ప్రాధాన్యత_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST
)
#లేకపోతే
#నిర్వచించు SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST ఖాళీ
#అయితే_ముగింపు

స్థిర x11dynlib x11libs[] = {
    { ఖాళీ, SDL_VIDEO_DRIVER_X11_DYNAMIC },
    { ఖాళీ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT },
    { ఖాళీ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR },
    { ఖాళీ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2 },
    { ఖాళీ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES },
    { ఖాళీ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR },
    { ఖాళీ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS },
    { ఖాళీ, SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST }
};

స్థిర శూన్య *X11_GetSym(స్థిరరాశి అక్షరం *fnname, పూర్ణాంకం *pHasModule)
{
    పూర్ణాంకం i;
    శూన్య *fn = ఖాళీ;
    కొరకు (i = 0; i < SDL_arraysize(x11libs); i++) {
        ఒకవేళ (x11libs[i].lib) {
            fn = SDL_ఎక్కించు_Function(x11libs[i].lib, fnname);
            ఒకవేళ (fn) {
                ఆపు;
            }
        }
    }

#ఒకవేళ DEBUG_DYNAMIC_X11
    ఒకవేళ (fn) {
        SDL_Log("X11: Found '%s' in %s (%p)", fnname, x11libs[i].libname, fn);
    } లేకపోతే {
        SDL_Log("X11: Symbol '%s' NOT FOUND!", fnname);
    }
#అయితే_ముగింపు

    ఒకవేళ (!fn) {
        *pHasModule = 0; // kill this module.
    }

    తిరిగి fn;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11_DYNAMIC

// Define all the function pointers and wrappers...
#నిర్వచించు SDL_X11_SYM(rc, fn, params) SDL_DYNX11FN_##fn X11_##fn = ఖాళీ;
#అన్తర్భావ "SDL_x11sym.h"

/* These SDL_X11_HAVE_* flags are here whether you have dynamic X11 or not. */
#నిర్వచించు SDL_X11_MODULE(modname) పూర్ణాంకం SDL_X11_HAVE_##modname = 0;
#అన్తర్భావ "SDL_x11sym.h"

స్థిర పూర్ణాంకం x11_ఎక్కించు_refcount = 0;

శూన్య SDL_X11_UnloadSymbols(శూన్య)
{
    // Don't actually unload if more than one module is using the libs...
    ఒకవేళ (x11_ఎక్కించు_refcount > 0) {
        ఒకవేళ (--x11_ఎక్కించు_refcount == 0) {
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_DYNAMIC
            పూర్ణాంకం i;
#అయితే_ముగింపు

            // set all the function pointers to NULL.
#నిర్వచించు SDL_X11_MODULE(modname)                SDL_X11_HAVE_##modname = 0;
#నిర్వచించు SDL_X11_SYM(rc, fn, params) X11_##fn = ఖాళీ;
#అన్తర్భావ "SDL_x11sym.h"

#నిర్వచితమైతే X_HAVE_UTF8_STRING
            X11_XCreateIC = ఖాళీ;
            X11_XGetICValues = ఖాళీ;
            X11_XSetICValues = ఖాళీ;
            X11_XVaCreateNestedList = ఖాళీ;
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_DYNAMIC
            కొరకు (i = 0; i < SDL_arraysize(x11libs); i++) {
                ఒకవేళ (x11libs[i].lib) {
                    SDL_UnloadObject(x11libs[i].lib);
                    x11libs[i].lib = ఖాళీ;
                }
            }
#అయితే_ముగింపు
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_X11_ఎక్కించు_Symbols(శూన్య)
{
    bool ఫలితం = true; // always succeed if not using Dynamic X11 stuff.

    // deal with multiple modules (dga, x11, etc) needing these symbols...
    ఒకవేళ (x11_ఎక్కించు_refcount++ == 0) {
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_DYNAMIC
        పూర్ణాంకం i;
        పూర్ణాంకం *thismod = ఖాళీ;
        కొరకు (i = 0; i < SDL_arraysize(x11libs); i++) {
            ఒకవేళ (x11libs[i].libname) {
                x11libs[i].lib = SDL_ఎక్కించు_Object(x11libs[i].libname);
            }
        }

#నిర్వచించు SDL_X11_MODULE(modname) SDL_X11_HAVE_##modname = 1; // default yes
#అన్తర్భావ "SDL_x11sym.h"

#నిర్వచించు SDL_X11_MODULE(modname)     thismod = &SDL_X11_HAVE_##modname;
#నిర్వచించు SDL_X11_SYM(rc, fn, params) X11_##fn = (SDL_DYNX11FN_##fn)X11_GetSym(#fn, thismod);
#అన్తర్భావ "SDL_x11sym.h"

#నిర్వచితమైతే X_HAVE_UTF8_STRING
        X11_XCreateIC = (SDL_DYNX11FN_XCreateIC)
            X11_GetSym("XCreateIC", &SDL_X11_HAVE_UTF8);
        X11_XGetICValues = (SDL_DYNX11FN_XGetICValues)
            X11_GetSym("XGetICValues", &SDL_X11_HAVE_UTF8);
        X11_XSetICValues = (SDL_DYNX11FN_XSetICValues)
            X11_GetSym("XSetICValues", &SDL_X11_HAVE_UTF8);
        X11_XVaCreateNestedList = (SDL_DYNX11FN_XVaCreateNestedList)
            X11_GetSym("XVaCreateNestedList", &SDL_X11_HAVE_UTF8);
#అయితే_ముగింపు

        ఒకవేళ (SDL_X11_HAVE_BASEXLIB) {
            // all required symbols loaded.
            SDL_ClearError();
        } లేకపోతే {
            // in case something got loaded...
            SDL_X11_UnloadSymbols();
            ఫలితం = false;
        }

#లేకపోతే // no dynamic X11

#నిర్వచించు SDL_X11_MODULE(modname)     SDL_X11_HAVE_##modname = 1; // default yes
#నిర్వచించు SDL_X11_SYM(rc, fn, params) X11_##fn = (SDL_DYNX11FN_##fn)fn;
#అన్తర్భావ "SDL_x11sym.h"

#నిర్వచితమైతే X_HAVE_UTF8_STRING
        X11_XCreateIC = XCreateIC;
        X11_XGetICValues = XGetICValues;
        X11_XSetICValues = XSetICValues;
        X11_XVaCreateNestedList = XVaCreateNestedList;
#అయితే_ముగింపు
#అయితే_ముగింపు
    }

    తిరిగి ఫలితం;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11
