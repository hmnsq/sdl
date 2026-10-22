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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11

#परिभाषय DEBUG_DYNAMIC_X11 0

#अन्तर्भाव "SDL_x11dyn.h"

#यदि DEBUG_DYNAMIC_X11
#अन्तर्भाव <stdio.h>
#यदि_अन्तः

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_DYNAMIC

प्रकारनिर्देश संरचना
{
    SDL_SharedObject *lib;
    ध्रुव वर्ण *libname;
} x11dynlib;

SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_प्राथमिकता_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC
)

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_प्राथमिकता_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT
)
#अन्यथा
#परिभाषय SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT रिक्त
#यदि_अन्तः

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_प्राथमिकता_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR
)
#अन्यथा
#परिभाषय SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR रिक्त
#यदि_अन्तः

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_प्राथमिकता_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2
)
#अन्यथा
#परिभाषय SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2 रिक्त
#यदि_अन्तः

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_प्राथमिकता_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES
)
#अन्यथा
#परिभाषय SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES रिक्त
#यदि_अन्तः

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_प्राथमिकता_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR
)
#अन्यथा
#परिभाषय SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR रिक्त
#यदि_अन्तः

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_प्राथमिकता_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS
)
#अन्यथा
#परिभाषय SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS रिक्त
#यदि_अन्तः

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_प्राथमिकता_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST
)
#अन्यथा
#परिभाषय SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST रिक्त
#यदि_अन्तः

स्थिर x11dynlib x11libs[] = {
    { रिक्त, SDL_VIDEO_DRIVER_X11_DYNAMIC },
    { रिक्त, SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT },
    { रिक्त, SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR },
    { रिक्त, SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2 },
    { रिक्त, SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES },
    { रिक्त, SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR },
    { रिक्त, SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS },
    { रिक्त, SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST }
};

स्थिर शून्य *X11_GetSym(ध्रुव वर्ण *fnname, पूर्णाङ्क *pHasModule)
{
    पूर्णाङ्क i;
    शून्य *fn = रिक्त;
    प्रति (i = 0; i < SDL_arraysize(x11libs); i++) {
        यदि (x11libs[i].lib) {
            fn = SDL_आरोपय_Function(x11libs[i].lib, fnname);
            यदि (fn) {
                भङ्ग;
            }
        }
    }

#यदि DEBUG_DYNAMIC_X11
    यदि (fn) {
        SDL_Log("X11: Found '%s' in %s (%p)", fnname, x11libs[i].libname, fn);
    } अन्यथा {
        SDL_Log("X11: Symbol '%s' NOT FOUND!", fnname);
    }
#यदि_अन्तः

    यदि (!fn) {
        *pHasModule = 0; // kill this module.
    }

    प्रत्यागम fn;
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_X11_DYNAMIC

// Define all the function pointers and wrappers...
#परिभाषय SDL_X11_SYM(rc, fn, params) SDL_DYNX11FN_##fn X11_##fn = रिक्त;
#अन्तर्भाव "SDL_x11sym.h"

/* These SDL_X11_HAVE_* flags are here whether you have dynamic X11 or not. */
#परिभाषय SDL_X11_MODULE(modname) पूर्णाङ्क SDL_X11_HAVE_##modname = 0;
#अन्तर्भाव "SDL_x11sym.h"

स्थिर पूर्णाङ्क x11_आरोपय_refcount = 0;

शून्य SDL_X11_UnloadSymbols(शून्य)
{
    // Don't actually unload if more than one module is using the libs...
    यदि (x11_आरोपय_refcount > 0) {
        यदि (--x11_आरोपय_refcount == 0) {
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_DYNAMIC
            पूर्णाङ्क i;
#यदि_अन्तः

            // set all the function pointers to NULL.
#परिभाषय SDL_X11_MODULE(modname)                SDL_X11_HAVE_##modname = 0;
#परिभाषय SDL_X11_SYM(rc, fn, params) X11_##fn = रिक्त;
#अन्तर्भाव "SDL_x11sym.h"

#यदि_परिभाषितम् X_HAVE_UTF8_STRING
            X11_XCreateIC = रिक्त;
            X11_XGetICValues = रिक्त;
            X11_XSetICValues = रिक्त;
            X11_XVaCreateNestedList = रिक्त;
#यदि_अन्तः

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_DYNAMIC
            प्रति (i = 0; i < SDL_arraysize(x11libs); i++) {
                यदि (x11libs[i].lib) {
                    SDL_UnloadObject(x11libs[i].lib);
                    x11libs[i].lib = रिक्त;
                }
            }
#यदि_अन्तः
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_X11_आरोपय_Symbols(शून्य)
{
    bool परिणाम = true; // always succeed if not using Dynamic X11 stuff.

    // deal with multiple modules (dga, x11, etc) needing these symbols...
    यदि (x11_आरोपय_refcount++ == 0) {
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_DYNAMIC
        पूर्णाङ्क i;
        पूर्णाङ्क *thismod = रिक्त;
        प्रति (i = 0; i < SDL_arraysize(x11libs); i++) {
            यदि (x11libs[i].libname) {
                x11libs[i].lib = SDL_आरोपय_Object(x11libs[i].libname);
            }
        }

#परिभाषय SDL_X11_MODULE(modname) SDL_X11_HAVE_##modname = 1; // default yes
#अन्तर्भाव "SDL_x11sym.h"

#परिभाषय SDL_X11_MODULE(modname)     thismod = &SDL_X11_HAVE_##modname;
#परिभाषय SDL_X11_SYM(rc, fn, params) X11_##fn = (SDL_DYNX11FN_##fn)X11_GetSym(#fn, thismod);
#अन्तर्भाव "SDL_x11sym.h"

#यदि_परिभाषितम् X_HAVE_UTF8_STRING
        X11_XCreateIC = (SDL_DYNX11FN_XCreateIC)
            X11_GetSym("XCreateIC", &SDL_X11_HAVE_UTF8);
        X11_XGetICValues = (SDL_DYNX11FN_XGetICValues)
            X11_GetSym("XGetICValues", &SDL_X11_HAVE_UTF8);
        X11_XSetICValues = (SDL_DYNX11FN_XSetICValues)
            X11_GetSym("XSetICValues", &SDL_X11_HAVE_UTF8);
        X11_XVaCreateNestedList = (SDL_DYNX11FN_XVaCreateNestedList)
            X11_GetSym("XVaCreateNestedList", &SDL_X11_HAVE_UTF8);
#यदि_अन्तः

        यदि (SDL_X11_HAVE_BASEXLIB) {
            // all required symbols loaded.
            SDL_ClearError();
        } अन्यथा {
            // in case something got loaded...
            SDL_X11_UnloadSymbols();
            परिणाम = false;
        }

#अन्यथा // no dynamic X11

#परिभाषय SDL_X11_MODULE(modname)     SDL_X11_HAVE_##modname = 1; // default yes
#परिभाषय SDL_X11_SYM(rc, fn, params) X11_##fn = (SDL_DYNX11FN_##fn)fn;
#अन्तर्भाव "SDL_x11sym.h"

#यदि_परिभाषितम् X_HAVE_UTF8_STRING
        X11_XCreateIC = XCreateIC;
        X11_XGetICValues = XGetICValues;
        X11_XSetICValues = XSetICValues;
        X11_XVaCreateNestedList = XVaCreateNestedList;
#यदि_अन्तः
#यदि_अन्तः
    }

    प्रत्यागम परिणाम;
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_X11
