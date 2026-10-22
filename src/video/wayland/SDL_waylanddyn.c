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

#अगर_घोषित SDL_VIDEO_DRIVER_WAYLAND

#घोषणा DEBUG_DYNAMIC_WAYLAND 0

#समावेश "SDL_waylanddyn.h"

#अगर_घोषित SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
)
#अगर_घोषित SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL
)
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR
)
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON
)
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
)
#पूर्ण_अगर

प्रकार काष्ठा
{
    SDL_SharedObject *lib;
    स्थिर अक्षर *libname;
    स्थिर अक्षर *hint;
    bool hint_default;
} waylanddynlib;

अटल waylanddynlib waylandlibs[] = {
    { शून्य, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC, शून्य, false },
#अगर_घोषित SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL
    { शून्य, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL, शून्य, false },
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR
    { शून्य, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR, शून्य, false },
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON
    { शून्य, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON, शून्य, false },
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    { शून्य, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR, SDL_HINT_VIDEO_WAYLAND_ALLOW_LIBDECOR, true },
#पूर्ण_अगर
    { शून्य, शून्य, शून्य, false }
};

अटल व्योम *WAYLAND_GetSym(स्थिर अक्षर *fnname, पूर्णांक *pHasModule, bool required)
{
    व्योम *fn = शून्य;
    waylanddynlib *dynlib;
    क्रम (dynlib = waylandlibs; dynlib->libname; dynlib++) {
        अगर (dynlib->lib) {
            fn = SDL_LoadFunction(dynlib->lib, fnname);
            अगर (fn) {
                अवरोध;
            }
        }
    }

#अगर DEBUG_DYNAMIC_WAYLAND
    अगर (fn) {
        SDL_Log("WAYLAND: Found '%s' in %s (%p)", fnname, dynlib->libname, fn);
    } अन्यथा {
        SDL_Log("WAYLAND: Symbol '%s' NOT FOUND!", fnname);
    }
#पूर्ण_अगर

    अगर (!fn && required) {
        *pHasModule = 0; // kill this module.
    }

    वापस fn;
}

#अन्यथा

#समावेश <wayland-egl.h>

#पूर्ण_अगर // SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

// Define all the function pointers and wrappers...
#घोषणा SDL_WAYLAND_MODULE(modname)         पूर्णांक SDL_WAYLAND_HAVE_##modname = 0;
#घोषणा SDL_WAYLAND_SYM(rc, fn, params)     SDL_DYNWAYLANDFN_##fn WAYLAND_##fn = शून्य;
#घोषणा SDL_WAYLAND_SYM_OPT(rc, fn, params) SDL_DYNWAYLANDFN_##fn WAYLAND_##fn = शून्य;
#समावेश "SDL_waylandsym.h"

अटल पूर्णांक wayland_load_refcount = 0;

व्योम SDL_WAYLAND_UnloadSymbols(व्योम)
{
    // Don't actually unload if more than one module is using the libs...
    अगर (wayland_load_refcount > 0) {
        अगर (--wayland_load_refcount == 0) {
#अगर_घोषित SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
            पूर्णांक i;
#पूर्ण_अगर

            // set all the function pointers to NULL.
#घोषणा SDL_WAYLAND_MODULE(modname)         SDL_WAYLAND_HAVE_##modname = 0;
#घोषणा SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = शून्य;
#घोषणा SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = शून्य;
#समावेश "SDL_waylandsym.h"

#अगर_घोषित SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
            क्रम (i = 0; i < SDL_arraysize(waylandlibs); i++) {
                अगर (waylandlibs[i].lib) {
                    SDL_UnloadObject(waylandlibs[i].lib);
                    waylandlibs[i].lib = शून्य;
                }
            }
#पूर्ण_अगर
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_WAYLAND_LoadSymbols(व्योम)
{
    bool परिणाम = true; // always succeed if not using Dynamic WAYLAND stuff.

    // deal with multiple modules (dga, wayland, etc) needing these symbols...
    अगर (wayland_load_refcount++ == 0) {
#अगर_घोषित SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
        पूर्णांक i;
        पूर्णांक *thismod = शून्य;
        क्रम (i = 0; i < SDL_arraysize(waylandlibs); i++) {
            अगर (waylandlibs[i].libname) {
                अगर (waylandlibs[i].hint &&
                    !SDL_GetHintBoolean(waylandlibs[i].hint, waylandlibs[i].hint_default)) {
                    जारी;
                }
                waylandlibs[i].lib = SDL_LoadObject(waylandlibs[i].libname);
            }
        }

#घोषणा SDL_WAYLAND_MODULE(modname) SDL_WAYLAND_HAVE_##modname = 1; // default yes
#समावेश "SDL_waylandsym.h"

#घोषणा SDL_WAYLAND_MODULE(modname)         thismod = &SDL_WAYLAND_HAVE_##modname;
#घोषणा SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = (SDL_DYNWAYLANDFN_##fn)WAYLAND_GetSym(#fn, thismod, true);
#घोषणा SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = (SDL_DYNWAYLANDFN_##fn)WAYLAND_GetSym(#fn, thismod, false);
#समावेश "SDL_waylandsym.h"

        अगर (SDL_WAYLAND_HAVE_WAYLAND_CLIENT &&
            SDL_WAYLAND_HAVE_WAYLAND_CURSOR &&
            SDL_WAYLAND_HAVE_WAYLAND_EGL &&
            SDL_WAYLAND_HAVE_WAYLAND_XKB) {
            // All required symbols loaded, only libdecor is optional.
            SDL_ClearError();
        } अन्यथा {
            // in case something got loaded...
            SDL_WAYLAND_UnloadSymbols();
            परिणाम = false;
        }

#अन्यथा // no dynamic WAYLAND

#घोषणा SDL_WAYLAND_MODULE(modname)         SDL_WAYLAND_HAVE_##modname = 1; // default yes
#घोषणा SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = fn;
#घोषणा SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = fn;
#समावेश "SDL_waylandsym.h"

#पूर्ण_अगर
    }

    वापस परिणाम;
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_WAYLAND
