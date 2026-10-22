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

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#define DEBUG_DYNAMIC_WAYLAND 0

#അന്തര്ഭാവ "SDL_waylanddyn.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
)
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL
)
#endif
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR
)
#endif
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON
)
#endif
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_PRIORITY_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
)
#endif

തരനിർവചനം ഘടന
{
    SDL_SharedObject *lib;
    സ്ഥിരം അക്ഷരം *libname;
    സ്ഥിരം അക്ഷരം *hint;
    bool hint_default;
} waylanddynlib;

സ്ഥിതം waylanddynlib waylandlibs[] = {
    { ശൂന്യ, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC, ശൂന്യ, false },
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL
    { ശൂന്യ, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL, ശൂന്യ, false },
#endif
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR
    { ശൂന്യ, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR, ശൂന്യ, false },
#endif
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON
    { ശൂന്യ, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON, ശൂന്യ, false },
#endif
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    { ശൂന്യ, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR, SDL_HINT_VIDEO_WAYLAND_ALLOW_LIBDECOR, true },
#endif
    { ശൂന്യ, ശൂന്യ, ശൂന്യ, false }
};

സ്ഥിതം ശൂന്യം *WAYLAND_GetSym(സ്ഥിരം അക്ഷരം *fnname, പൂർണ്ണസംഖ്യ *pHasModule, bool required)
{
    ശൂന്യം *fn = ശൂന്യ;
    waylanddynlib *dynlib;
    വേണ്ടി (dynlib = waylandlibs; dynlib->libname; dynlib++) {
        എങ്കിൽ (dynlib->lib) {
            fn = SDL_LoadFunction(dynlib->lib, fnname);
            എങ്കിൽ (fn) {
                നിർത്തുക;
            }
        }
    }

#എങ്കിൽ DEBUG_DYNAMIC_WAYLAND
    എങ്കിൽ (fn) {
        SDL_Log("WAYLAND: Found '%s' in %s (%p)", fnname, dynlib->libname, fn);
    } അല്ലെങ്കിൽ {
        SDL_Log("WAYLAND: Symbol '%s' NOT FOUND!", fnname);
    }
#endif

    എങ്കിൽ (!fn && required) {
        *pHasModule = 0; // kill this module.
    }

    തിരികെ fn;
}

#അല്ലെങ്കിൽ

#അന്തര്ഭാവ <wayland-egl.h>

#endif // SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

// Define all the function pointers and wrappers...
#define SDL_WAYLAND_MODULE(modname)         പൂർണ്ണസംഖ്യ SDL_WAYLAND_HAVE_##modname = 0;
#define SDL_WAYLAND_SYM(rc, fn, params)     SDL_DYNWAYLANDFN_##fn WAYLAND_##fn = ശൂന്യ;
#define SDL_WAYLAND_SYM_OPT(rc, fn, params) SDL_DYNWAYLANDFN_##fn WAYLAND_##fn = ശൂന്യ;
#അന്തര്ഭാവ "SDL_waylandsym.h"

സ്ഥിതം പൂർണ്ണസംഖ്യ wayland_load_refcount = 0;

ശൂന്യം SDL_WAYLAND_UnloadSymbols(ശൂന്യം)
{
    // Don't actually unload if more than one module is using the libs...
    എങ്കിൽ (wayland_load_refcount > 0) {
        എങ്കിൽ (--wayland_load_refcount == 0) {
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
            പൂർണ്ണസംഖ്യ i;
#endif

            // set all the function pointers to NULL.
#define SDL_WAYLAND_MODULE(modname)         SDL_WAYLAND_HAVE_##modname = 0;
#define SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = ശൂന്യ;
#define SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = ശൂന്യ;
#അന്തര്ഭാവ "SDL_waylandsym.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
            വേണ്ടി (i = 0; i < SDL_arraysize(waylandlibs); i++) {
                എങ്കിൽ (waylandlibs[i].lib) {
                    SDL_UnloadObject(waylandlibs[i].lib);
                    waylandlibs[i].lib = ശൂന്യ;
                }
            }
#endif
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_WAYLAND_LoadSymbols(ശൂന്യം)
{
    bool result = true; // always succeed if not using Dynamic WAYLAND stuff.

    // deal with multiple modules (dga, wayland, etc) needing these symbols...
    എങ്കിൽ (wayland_load_refcount++ == 0) {
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
        പൂർണ്ണസംഖ്യ i;
        പൂർണ്ണസംഖ്യ *thismod = ശൂന്യ;
        വേണ്ടി (i = 0; i < SDL_arraysize(waylandlibs); i++) {
            എങ്കിൽ (waylandlibs[i].libname) {
                എങ്കിൽ (waylandlibs[i].hint &&
                    !SDL_GetHintBoolean(waylandlibs[i].hint, waylandlibs[i].hint_default)) {
                    തുടരുക;
                }
                waylandlibs[i].lib = SDL_LoadObject(waylandlibs[i].libname);
            }
        }

#define SDL_WAYLAND_MODULE(modname) SDL_WAYLAND_HAVE_##modname = 1; // default yes
#അന്തര്ഭാവ "SDL_waylandsym.h"

#define SDL_WAYLAND_MODULE(modname)         thismod = &SDL_WAYLAND_HAVE_##modname;
#define SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = (SDL_DYNWAYLANDFN_##fn)WAYLAND_GetSym(#fn, thismod, true);
#define SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = (SDL_DYNWAYLANDFN_##fn)WAYLAND_GetSym(#fn, thismod, false);
#അന്തര്ഭാവ "SDL_waylandsym.h"

        എങ്കിൽ (SDL_WAYLAND_HAVE_WAYLAND_CLIENT &&
            SDL_WAYLAND_HAVE_WAYLAND_CURSOR &&
            SDL_WAYLAND_HAVE_WAYLAND_EGL &&
            SDL_WAYLAND_HAVE_WAYLAND_XKB) {
            // All required symbols loaded, only libdecor is optional.
            SDL_ClearError();
        } അല്ലെങ്കിൽ {
            // in case something got loaded...
            SDL_WAYLAND_UnloadSymbols();
            result = false;
        }

#അല്ലെങ്കിൽ // no dynamic WAYLAND

#define SDL_WAYLAND_MODULE(modname)         SDL_WAYLAND_HAVE_##modname = 1; // default yes
#define SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = fn;
#define SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = fn;
#അന്തര്ഭാവ "SDL_waylandsym.h"

#endif
    }

    തിരികെ result;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
