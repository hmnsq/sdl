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
#ضمن "SDL_internal.h"

#که_تعریف_شوی SDL_VIDEO_DRIVER_WAYLAND

#تعریف_کړه DEBUG_DYNAMIC_WAYLAND 0

#ضمن "SDL_waylanddyn.h"

#که_تعریف_شوی SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_لومړیتوب_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
)
#که_تعریف_شوی SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_لومړیتوب_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL
)
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_لومړیتوب_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR
)
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_لومړیتوب_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON
)
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_لومړیتوب_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
)
#د_که_پای

تعريفنوع بنية
{
    SDL_SharedObject *lib;
    ثابت حرف *libname;
    ثابت حرف *hint;
    bool hint_default;
} waylanddynlib;

ساكن waylanddynlib waylandlibs[] = {
    { عدم, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC, عدم, false },
#که_تعریف_شوی SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL
    { عدم, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL, عدم, false },
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR
    { عدم, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR, عدم, false },
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON
    { عدم, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON, عدم, false },
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    { عدم, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR, SDL_HINT_VIDEO_WAYLAND_ALLOW_LIBDECOR, true },
#د_که_پای
    { عدم, عدم, عدم, false }
};

ساكن فراغ *WAYLAND_GetSym(ثابت حرف *fnname, صحيح *pHasModule, bool required)
{
    فراغ *fn = عدم;
    waylanddynlib *dynlib;
    لكل (dynlib = waylandlibs; dynlib->libname; dynlib++) {
        إذا (dynlib->lib) {
            fn = SDL_بارول_Function(dynlib->lib, fnname);
            إذا (fn) {
                اكسر;
            }
        }
    }

#إذا DEBUG_DYNAMIC_WAYLAND
    إذا (fn) {
        SDL_Log("WAYLAND: Found '%s' in %s (%p)", fnname, dynlib->libname, fn);
    } وإلا {
        SDL_Log("WAYLAND: Symbol '%s' NOT FOUND!", fnname);
    }
#د_که_پای

    إذا (!fn && required) {
        *pHasModule = 0; // kill this module.
    }

    أرجع fn;
}

#وإلا

#ضمن <wayland-egl.h>

#د_که_پای // SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

// Define all the function pointers and wrappers...
#تعریف_کړه SDL_WAYLAND_MODULE(modname)         صحيح SDL_WAYLAND_HAVE_##modname = 0;
#تعریف_کړه SDL_WAYLAND_SYM(rc, fn, params)     SDL_DYNWAYLANDFN_##fn WAYLAND_##fn = عدم;
#تعریف_کړه SDL_WAYLAND_SYM_OPT(rc, fn, params) SDL_DYNWAYLANDFN_##fn WAYLAND_##fn = عدم;
#ضمن "SDL_waylandsym.h"

ساكن صحيح wayland_بارول_refcount = 0;

فراغ SDL_WAYLAND_UnloadSymbols(فراغ)
{
    // Don't actually unload if more than one module is using the libs...
    إذا (wayland_بارول_refcount > 0) {
        إذا (--wayland_بارول_refcount == 0) {
#که_تعریف_شوی SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
            صحيح i;
#د_که_پای

            // set all the function pointers to NULL.
#تعریف_کړه SDL_WAYLAND_MODULE(modname)         SDL_WAYLAND_HAVE_##modname = 0;
#تعریف_کړه SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = عدم;
#تعریف_کړه SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = عدم;
#ضمن "SDL_waylandsym.h"

#که_تعریف_شوی SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
            لكل (i = 0; i < SDL_arraysize(waylandlibs); i++) {
                إذا (waylandlibs[i].lib) {
                    SDL_UnloadObject(waylandlibs[i].lib);
                    waylandlibs[i].lib = عدم;
                }
            }
#د_که_پای
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_WAYLAND_بارول_Symbols(فراغ)
{
    bool پایله = true; // always succeed if not using Dynamic WAYLAND stuff.

    // deal with multiple modules (dga, wayland, etc) needing these symbols...
    إذا (wayland_بارول_refcount++ == 0) {
#که_تعریف_شوی SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
        صحيح i;
        صحيح *thismod = عدم;
        لكل (i = 0; i < SDL_arraysize(waylandlibs); i++) {
            إذا (waylandlibs[i].libname) {
                إذا (waylandlibs[i].hint &&
                    !SDL_GetHintBoolean(waylandlibs[i].hint, waylandlibs[i].hint_default)) {
                    استمر;
                }
                waylandlibs[i].lib = SDL_بارول_Object(waylandlibs[i].libname);
            }
        }

#تعریف_کړه SDL_WAYLAND_MODULE(modname) SDL_WAYLAND_HAVE_##modname = 1; // default yes
#ضمن "SDL_waylandsym.h"

#تعریف_کړه SDL_WAYLAND_MODULE(modname)         thismod = &SDL_WAYLAND_HAVE_##modname;
#تعریف_کړه SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = (SDL_DYNWAYLANDFN_##fn)WAYLAND_GetSym(#fn, thismod, true);
#تعریف_کړه SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = (SDL_DYNWAYLANDFN_##fn)WAYLAND_GetSym(#fn, thismod, false);
#ضمن "SDL_waylandsym.h"

        إذا (SDL_WAYLAND_HAVE_WAYLAND_CLIENT &&
            SDL_WAYLAND_HAVE_WAYLAND_CURSOR &&
            SDL_WAYLAND_HAVE_WAYLAND_EGL &&
            SDL_WAYLAND_HAVE_WAYLAND_XKB) {
            // All required symbols loaded, only libdecor is optional.
            SDL_ClearError();
        } وإلا {
            // in case something got loaded...
            SDL_WAYLAND_UnloadSymbols();
            پایله = false;
        }

#وإلا // no dynamic WAYLAND

#تعریف_کړه SDL_WAYLAND_MODULE(modname)         SDL_WAYLAND_HAVE_##modname = 1; // default yes
#تعریف_کړه SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = fn;
#تعریف_کړه SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = fn;
#ضمن "SDL_waylandsym.h"

#د_که_پای
    }

    أرجع پایله;
}

#د_که_پای // SDL_VIDEO_DRIVER_WAYLAND
