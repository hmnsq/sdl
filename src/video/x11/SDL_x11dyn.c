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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_X11

#घोषणा DEBUG_DYNAMIC_X11 0

#समावेश "SDL_x11dyn.h"

#अगर DEBUG_DYNAMIC_X11
#समावेश <stdio.h>
#पूर्ण_अगर

#अगर_घोषित SDL_VIDEO_DRIVER_X11_DYNAMIC

प्रकार काष्ठा
{
    SDL_SharedObject *lib;
    स्थिर अक्षर *libname;
} x11dynlib;

SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC
)

#अगर_घोषित SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT
)
#अन्यथा
#घोषणा SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT शून्य
#पूर्ण_अगर

#अगर_घोषित SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR
)
#अन्यथा
#घोषणा SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR शून्य
#पूर्ण_अगर

#अगर_घोषित SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2
)
#अन्यथा
#घोषणा SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2 शून्य
#पूर्ण_अगर

#अगर_घोषित SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES
)
#अन्यथा
#घोषणा SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES शून्य
#पूर्ण_अगर

#अगर_घोषित SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR
)
#अन्यथा
#घोषणा SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR शून्य
#पूर्ण_अगर

#अगर_घोषित SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS
)
#अन्यथा
#घोषणा SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS शून्य
#पूर्ण_अगर

#अगर_घोषित SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST
SDL_ELF_NOTE_DLOPEN(
    "x11",
    "Support for video through X11 backend",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_RECOMMENDED,
    SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST
)
#अन्यथा
#घोषणा SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST शून्य
#पूर्ण_अगर

अटल x11dynlib x11libs[] = {
    { शून्य, SDL_VIDEO_DRIVER_X11_DYNAMIC },
    { शून्य, SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT },
    { शून्य, SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR },
    { शून्य, SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2 },
    { शून्य, SDL_VIDEO_DRIVER_X11_DYNAMIC_XFIXES },
    { शून्य, SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR },
    { शून्य, SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS },
    { शून्य, SDL_VIDEO_DRIVER_X11_DYNAMIC_XTEST }
};

अटल व्योम *X11_GetSym(स्थिर अक्षर *fnname, पूर्णांक *pHasModule)
{
    पूर्णांक i;
    व्योम *fn = शून्य;
    क्रम (i = 0; i < SDL_arraysize(x11libs); i++) {
        अगर (x11libs[i].lib) {
            fn = SDL_LoadFunction(x11libs[i].lib, fnname);
            अगर (fn) {
                अवरोध;
            }
        }
    }

#अगर DEBUG_DYNAMIC_X11
    अगर (fn) {
        SDL_Log("X11: Found '%s' in %s (%p)", fnname, x11libs[i].libname, fn);
    } अन्यथा {
        SDL_Log("X11: Symbol '%s' NOT FOUND!", fnname);
    }
#पूर्ण_अगर

    अगर (!fn) {
        *pHasModule = 0; // kill this module.
    }

    वापस fn;
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11_DYNAMIC

// Define all the function pointers and wrappers...
#घोषणा SDL_X11_SYM(rc, fn, params) SDL_DYNX11FN_##fn X11_##fn = शून्य;
#समावेश "SDL_x11sym.h"

/* These SDL_X11_HAVE_* flags are here whether you have dynamic X11 or not. */
#घोषणा SDL_X11_MODULE(modname) पूर्णांक SDL_X11_HAVE_##modname = 0;
#समावेश "SDL_x11sym.h"

अटल पूर्णांक x11_load_refcount = 0;

व्योम SDL_X11_UnloadSymbols(व्योम)
{
    // Don't actually unload if more than one module is using the libs...
    अगर (x11_load_refcount > 0) {
        अगर (--x11_load_refcount == 0) {
#अगर_घोषित SDL_VIDEO_DRIVER_X11_DYNAMIC
            पूर्णांक i;
#पूर्ण_अगर

            // set all the function pointers to NULL.
#घोषणा SDL_X11_MODULE(modname)                SDL_X11_HAVE_##modname = 0;
#घोषणा SDL_X11_SYM(rc, fn, params) X11_##fn = शून्य;
#समावेश "SDL_x11sym.h"

#अगर_घोषित X_HAVE_UTF8_STRING
            X11_XCreateIC = शून्य;
            X11_XGetICValues = शून्य;
            X11_XSetICValues = शून्य;
            X11_XVaCreateNestedList = शून्य;
#पूर्ण_अगर

#अगर_घोषित SDL_VIDEO_DRIVER_X11_DYNAMIC
            क्रम (i = 0; i < SDL_arraysize(x11libs); i++) {
                अगर (x11libs[i].lib) {
                    SDL_UnloadObject(x11libs[i].lib);
                    x11libs[i].lib = शून्य;
                }
            }
#पूर्ण_अगर
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_X11_LoadSymbols(व्योम)
{
    bool परिणाम = true; // always succeed if not using Dynamic X11 stuff.

    // deal with multiple modules (dga, x11, etc) needing these symbols...
    अगर (x11_load_refcount++ == 0) {
#अगर_घोषित SDL_VIDEO_DRIVER_X11_DYNAMIC
        पूर्णांक i;
        पूर्णांक *thismod = शून्य;
        क्रम (i = 0; i < SDL_arraysize(x11libs); i++) {
            अगर (x11libs[i].libname) {
                x11libs[i].lib = SDL_LoadObject(x11libs[i].libname);
            }
        }

#घोषणा SDL_X11_MODULE(modname) SDL_X11_HAVE_##modname = 1; // default yes
#समावेश "SDL_x11sym.h"

#घोषणा SDL_X11_MODULE(modname)     thismod = &SDL_X11_HAVE_##modname;
#घोषणा SDL_X11_SYM(rc, fn, params) X11_##fn = (SDL_DYNX11FN_##fn)X11_GetSym(#fn, thismod);
#समावेश "SDL_x11sym.h"

#अगर_घोषित X_HAVE_UTF8_STRING
        X11_XCreateIC = (SDL_DYNX11FN_XCreateIC)
            X11_GetSym("XCreateIC", &SDL_X11_HAVE_UTF8);
        X11_XGetICValues = (SDL_DYNX11FN_XGetICValues)
            X11_GetSym("XGetICValues", &SDL_X11_HAVE_UTF8);
        X11_XSetICValues = (SDL_DYNX11FN_XSetICValues)
            X11_GetSym("XSetICValues", &SDL_X11_HAVE_UTF8);
        X11_XVaCreateNestedList = (SDL_DYNX11FN_XVaCreateNestedList)
            X11_GetSym("XVaCreateNestedList", &SDL_X11_HAVE_UTF8);
#पूर्ण_अगर

        अगर (SDL_X11_HAVE_BASEXLIB) {
            // all required symbols loaded.
            SDL_ClearError();
        } अन्यथा {
            // in case something got loaded...
            SDL_X11_UnloadSymbols();
            परिणाम = false;
        }

#अन्यथा // no dynamic X11

#घोषणा SDL_X11_MODULE(modname)     SDL_X11_HAVE_##modname = 1; // default yes
#घोषणा SDL_X11_SYM(rc, fn, params) X11_##fn = (SDL_DYNX11FN_##fn)fn;
#समावेश "SDL_x11sym.h"

#अगर_घोषित X_HAVE_UTF8_STRING
        X11_XCreateIC = XCreateIC;
        X11_XGetICValues = XGetICValues;
        X11_XSetICValues = XSetICValues;
        X11_XVaCreateNestedList = XVaCreateNestedList;
#पूर्ण_अगर
#पूर्ण_अगर
    }

    वापस परिणाम;
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11
