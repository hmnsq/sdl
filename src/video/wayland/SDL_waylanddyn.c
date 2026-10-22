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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WAYLAND

#ವ್ಯಾಖ್ಯಾನಿಸು DEBUG_DYNAMIC_WAYLAND 0

#ಅನ್ತರ್ಭಾವ "SDL_waylanddyn.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_ಆದ್ಯತೆ_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
)
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_ಆದ್ಯತೆ_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL
)
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_ಆದ್ಯತೆ_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR
)
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_ಆದ್ಯತೆ_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON
)
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_ಆದ್ಯತೆ_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
)
#ಆದರೆ_ಅಂತ್ಯ

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    SDL_SharedObject *lib;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *libname;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *hint;
    bool hint_default;
} waylanddynlib;

ಸ್ಥಿರ waylanddynlib waylandlibs[] = {
    { ಖಾಲಿ, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC, ಖಾಲಿ, false },
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL
    { ಖಾಲಿ, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL, ಖಾಲಿ, false },
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR
    { ಖಾಲಿ, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR, ಖಾಲಿ, false },
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON
    { ಖಾಲಿ, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON, ಖಾಲಿ, false },
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    { ಖಾಲಿ, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR, SDL_HINT_VIDEO_WAYLAND_ALLOW_LIBDECOR, true },
#ಆದರೆ_ಅಂತ್ಯ
    { ಖಾಲಿ, ಖಾಲಿ, ಖಾಲಿ, false }
};

ಸ್ಥಿರ ಶೂನ್ಯ *WAYLAND_GetSym(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fnname, ಪೂರ್ಣಾಂಕ *pHasModule, bool required)
{
    ಶೂನ್ಯ *fn = ಖಾಲಿ;
    waylanddynlib *dynlib;
    ಗಾಗಿ (dynlib = waylandlibs; dynlib->libname; dynlib++) {
        ಆದರೆ (dynlib->lib) {
            fn = SDL_ತುಂಬು_Function(dynlib->lib, fnname);
            ಆದರೆ (fn) {
                ನಿಲ್ಲಿಸು;
            }
        }
    }

#ಆದರೆ DEBUG_DYNAMIC_WAYLAND
    ಆದರೆ (fn) {
        SDL_Log("WAYLAND: Found '%s' in %s (%p)", fnname, dynlib->libname, fn);
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_Log("WAYLAND: Symbol '%s' NOT FOUND!", fnname);
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (!fn && required) {
        *pHasModule = 0; // kill this module.
    }

    ಹಿಂತಿರುಗಿ fn;
}

#ಇಲ್ಲದಿದ್ದರೆ

#ಅನ್ತರ್ಭಾವ <wayland-egl.h>

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

// Define all the function pointers and wrappers...
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_WAYLAND_MODULE(modname)         ಪೂರ್ಣಾಂಕ SDL_WAYLAND_HAVE_##modname = 0;
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_WAYLAND_SYM(rc, fn, params)     SDL_DYNWAYLANDFN_##fn WAYLAND_##fn = ಖಾಲಿ;
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_WAYLAND_SYM_OPT(rc, fn, params) SDL_DYNWAYLANDFN_##fn WAYLAND_##fn = ಖಾಲಿ;
#ಅನ್ತರ್ಭಾವ "SDL_waylandsym.h"

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ wayland_ತುಂಬು_refcount = 0;

ಶೂನ್ಯ SDL_WAYLAND_UnloadSymbols(ಶೂನ್ಯ)
{
    // Don't actually unload if more than one module is using the libs...
    ಆದರೆ (wayland_ತುಂಬು_refcount > 0) {
        ಆದರೆ (--wayland_ತುಂಬು_refcount == 0) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
            ಪೂರ್ಣಾಂಕ i;
#ಆದರೆ_ಅಂತ್ಯ

            // set all the function pointers to NULL.
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_WAYLAND_MODULE(modname)         SDL_WAYLAND_HAVE_##modname = 0;
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = ಖಾಲಿ;
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = ಖಾಲಿ;
#ಅನ್ತರ್ಭಾವ "SDL_waylandsym.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
            ಗಾಗಿ (i = 0; i < SDL_arraysize(waylandlibs); i++) {
                ಆದರೆ (waylandlibs[i].lib) {
                    SDL_UnloadObject(waylandlibs[i].lib);
                    waylandlibs[i].lib = ಖಾಲಿ;
                }
            }
#ಆದರೆ_ಅಂತ್ಯ
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_WAYLAND_ತುಂಬು_Symbols(ಶೂನ್ಯ)
{
    bool ಫಲಿತಾಂಶ = true; // always succeed if not using Dynamic WAYLAND stuff.

    // deal with multiple modules (dga, wayland, etc) needing these symbols...
    ಆದರೆ (wayland_ತುಂಬು_refcount++ == 0) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
        ಪೂರ್ಣಾಂಕ i;
        ಪೂರ್ಣಾಂಕ *thismod = ಖಾಲಿ;
        ಗಾಗಿ (i = 0; i < SDL_arraysize(waylandlibs); i++) {
            ಆದರೆ (waylandlibs[i].libname) {
                ಆದರೆ (waylandlibs[i].hint &&
                    !SDL_GetHintBoolean(waylandlibs[i].hint, waylandlibs[i].hint_default)) {
                    ಮುಂದುವರಿ;
                }
                waylandlibs[i].lib = SDL_ತುಂಬು_Object(waylandlibs[i].libname);
            }
        }

#ವ್ಯಾಖ್ಯಾನಿಸು SDL_WAYLAND_MODULE(modname) SDL_WAYLAND_HAVE_##modname = 1; // default yes
#ಅನ್ತರ್ಭಾವ "SDL_waylandsym.h"

#ವ್ಯಾಖ್ಯಾನಿಸು SDL_WAYLAND_MODULE(modname)         thismod = &SDL_WAYLAND_HAVE_##modname;
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = (SDL_DYNWAYLANDFN_##fn)WAYLAND_GetSym(#fn, thismod, true);
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = (SDL_DYNWAYLANDFN_##fn)WAYLAND_GetSym(#fn, thismod, false);
#ಅನ್ತರ್ಭಾವ "SDL_waylandsym.h"

        ಆದರೆ (SDL_WAYLAND_HAVE_WAYLAND_CLIENT &&
            SDL_WAYLAND_HAVE_WAYLAND_CURSOR &&
            SDL_WAYLAND_HAVE_WAYLAND_EGL &&
            SDL_WAYLAND_HAVE_WAYLAND_XKB) {
            // All required symbols loaded, only libdecor is optional.
            SDL_ClearError();
        } ಇಲ್ಲದಿದ್ದರೆ {
            // in case something got loaded...
            SDL_WAYLAND_UnloadSymbols();
            ಫಲಿತಾಂಶ = false;
        }

#ಇಲ್ಲದಿದ್ದರೆ // no dynamic WAYLAND

#ವ್ಯಾಖ್ಯಾನಿಸು SDL_WAYLAND_MODULE(modname)         SDL_WAYLAND_HAVE_##modname = 1; // default yes
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = fn;
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = fn;
#ಅನ್ತರ್ಭಾವ "SDL_waylandsym.h"

#ಆದರೆ_ಅಂತ್ಯ
    }

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_WAYLAND
