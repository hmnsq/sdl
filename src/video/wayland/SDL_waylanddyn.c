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
#شامل "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#define DEBUG_DYNAMIC_WAYLAND 0

#شامل "SDL_waylanddyn.h"

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

تعریفنوع ساختار
{
    SDL_SharedObject *lib;
    ثابت نویسه *libname;
    ثابت نویسه *hint;
    bool hint_default;
} waylanddynlib;

ایستا waylanddynlib waylandlibs[] = {
    { پوچ, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC, پوچ, false },
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL
    { پوچ, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL, پوچ, false },
#endif
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR
    { پوچ, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR, پوچ, false },
#endif
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON
    { پوچ, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON, پوچ, false },
#endif
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    { پوچ, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR, SDL_HINT_VIDEO_WAYLAND_ALLOW_LIBDECOR, true },
#endif
    { پوچ, پوچ, پوچ, false }
};

ایستا تهی *WAYLAND_GetSym(ثابت نویسه *fnname, صحیح *pHasModule, bool required)
{
    تهی *fn = پوچ;
    waylanddynlib *dynlib;
    برای (dynlib = waylandlibs; dynlib->libname; dynlib++) {
        اگر (dynlib->lib) {
            fn = SDL_LoadFunction(dynlib->lib, fnname);
            اگر (fn) {
                بشکن;
            }
        }
    }

#اگر DEBUG_DYNAMIC_WAYLAND
    اگر (fn) {
        SDL_Log("WAYLAND: Found '%s' in %s (%p)", fnname, dynlib->libname, fn);
    } وگرنه {
        SDL_Log("WAYLAND: Symbol '%s' NOT FOUND!", fnname);
    }
#endif

    اگر (!fn && required) {
        *pHasModule = 0; // kill this module.
    }

    بازگشت fn;
}

#وگرنه

#شامل <wayland-egl.h>

#endif // SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

// Define all the function pointers and wrappers...
#define SDL_WAYLAND_MODULE(modname)         صحیح SDL_WAYLAND_HAVE_##modname = 0;
#define SDL_WAYLAND_SYM(rc, fn, params)     SDL_DYNWAYLANDFN_##fn WAYLAND_##fn = پوچ;
#define SDL_WAYLAND_SYM_OPT(rc, fn, params) SDL_DYNWAYLANDFN_##fn WAYLAND_##fn = پوچ;
#شامل "SDL_waylandsym.h"

ایستا صحیح wayland_load_refcount = 0;

تهی SDL_WAYLAND_UnloadSymbols(تهی)
{
    // Don't actually unload if more than one module is using the libs...
    اگر (wayland_load_refcount > 0) {
        اگر (--wayland_load_refcount == 0) {
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
            صحیح i;
#endif

            // set all the function pointers to NULL.
#define SDL_WAYLAND_MODULE(modname)         SDL_WAYLAND_HAVE_##modname = 0;
#define SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = پوچ;
#define SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = پوچ;
#شامل "SDL_waylandsym.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
            برای (i = 0; i < SDL_arraysize(waylandlibs); i++) {
                اگر (waylandlibs[i].lib) {
                    SDL_UnloadObject(waylandlibs[i].lib);
                    waylandlibs[i].lib = پوچ;
                }
            }
#endif
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_WAYLAND_LoadSymbols(تهی)
{
    bool result = true; // always succeed if not using Dynamic WAYLAND stuff.

    // deal with multiple modules (dga, wayland, etc) needing these symbols...
    اگر (wayland_load_refcount++ == 0) {
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
        صحیح i;
        صحیح *thismod = پوچ;
        برای (i = 0; i < SDL_arraysize(waylandlibs); i++) {
            اگر (waylandlibs[i].libname) {
                اگر (waylandlibs[i].hint &&
                    !SDL_GetHintBoolean(waylandlibs[i].hint, waylandlibs[i].hint_default)) {
                    ادامه;
                }
                waylandlibs[i].lib = SDL_LoadObject(waylandlibs[i].libname);
            }
        }

#define SDL_WAYLAND_MODULE(modname) SDL_WAYLAND_HAVE_##modname = 1; // default yes
#شامل "SDL_waylandsym.h"

#define SDL_WAYLAND_MODULE(modname)         thismod = &SDL_WAYLAND_HAVE_##modname;
#define SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = (SDL_DYNWAYLANDFN_##fn)WAYLAND_GetSym(#fn, thismod, true);
#define SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = (SDL_DYNWAYLANDFN_##fn)WAYLAND_GetSym(#fn, thismod, false);
#شامل "SDL_waylandsym.h"

        اگر (SDL_WAYLAND_HAVE_WAYLAND_CLIENT &&
            SDL_WAYLAND_HAVE_WAYLAND_CURSOR &&
            SDL_WAYLAND_HAVE_WAYLAND_EGL &&
            SDL_WAYLAND_HAVE_WAYLAND_XKB) {
            // All required symbols loaded, only libdecor is optional.
            SDL_ClearError();
        } وگرنه {
            // in case something got loaded...
            SDL_WAYLAND_UnloadSymbols();
            result = false;
        }

#وگرنه // no dynamic WAYLAND

#define SDL_WAYLAND_MODULE(modname)         SDL_WAYLAND_HAVE_##modname = 1; // default yes
#define SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = fn;
#define SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = fn;
#شامل "SDL_waylandsym.h"

#endif
    }

    بازگشت result;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
