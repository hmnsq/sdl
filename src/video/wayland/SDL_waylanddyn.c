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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WAYLAND

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEBUG_DYNAMIC_WAYLAND 0

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylanddyn.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_ਤਰਜੀਹ_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
)
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_ਤਰਜੀਹ_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL
)
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_ਤਰਜੀਹ_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR
)
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_ਤਰਜੀਹ_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON
)
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
SDL_ELF_NOTE_DLOPEN(
    "wayland",
    "Support for Wayland video",
    SDL_ELF_NOTE_DLOPEN_ਤਰਜੀਹ_SUGGESTED,
    SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
)
#ਜੇ_ਅੰਤ

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    SDL_SharedObject *lib;
    ਅਚਲ ਅੱਖਰ *libname;
    ਅਚਲ ਅੱਖਰ *hint;
    bool hint_default;
} waylanddynlib;

ਸਥਿਰ waylanddynlib waylandlibs[] = {
    { ਨਿਰਾ, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC, ਨਿਰਾ, false },
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL
    { ਨਿਰਾ, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL, ਨਿਰਾ, false },
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR
    { ਨਿਰਾ, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR, ਨਿਰਾ, false },
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON
    { ਨਿਰਾ, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON, ਨਿਰਾ, false },
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    { ਨਿਰਾ, SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR, SDL_HINT_VIDEO_WAYLAND_ALLOW_LIBDECOR, true },
#ਜੇ_ਅੰਤ
    { ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ, false }
};

ਸਥਿਰ ਖਾਲੀ *WAYLAND_GetSym(ਅਚਲ ਅੱਖਰ *fnname, ਪੂਰਨ *pHasModule, bool required)
{
    ਖਾਲੀ *fn = ਨਿਰਾ;
    waylanddynlib *dynlib;
    ਲਈ (dynlib = waylandlibs; dynlib->libname; dynlib++) {
        ਜੇ (dynlib->lib) {
            fn = SDL_ਲੱਦੋ_Function(dynlib->lib, fnname);
            ਜੇ (fn) {
                ਰੋਕੋ;
            }
        }
    }

#ਜੇ DEBUG_DYNAMIC_WAYLAND
    ਜੇ (fn) {
        SDL_Log("WAYLAND: Found '%s' in %s (%p)", fnname, dynlib->libname, fn);
    } ਨਹੀਂਤਾਂ {
        SDL_Log("WAYLAND: Symbol '%s' NOT FOUND!", fnname);
    }
#ਜੇ_ਅੰਤ

    ਜੇ (!fn && required) {
        *pHasModule = 0; // kill this module.
    }

    ਵਾਪਸ fn;
}

#ਨਹੀਂਤਾਂ

#ਅਨ੍ਤਰ੍ਭਾਵ <wayland-egl.h>

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

// Define all the function pointers and wrappers...
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_WAYLAND_MODULE(modname)         ਪੂਰਨ SDL_WAYLAND_HAVE_##modname = 0;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_WAYLAND_SYM(rc, fn, params)     SDL_DYNWAYLANDFN_##fn WAYLAND_##fn = ਨਿਰਾ;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_WAYLAND_SYM_OPT(rc, fn, params) SDL_DYNWAYLANDFN_##fn WAYLAND_##fn = ਨਿਰਾ;
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandsym.h"

ਸਥਿਰ ਪੂਰਨ wayland_ਲੱਦੋ_refcount = 0;

ਖਾਲੀ SDL_WAYLAND_UnloadSymbols(ਖਾਲੀ)
{
    // Don't actually unload if more than one module is using the libs...
    ਜੇ (wayland_ਲੱਦੋ_refcount > 0) {
        ਜੇ (--wayland_ਲੱਦੋ_refcount == 0) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
            ਪੂਰਨ i;
#ਜੇ_ਅੰਤ

            // set all the function pointers to NULL.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_WAYLAND_MODULE(modname)         SDL_WAYLAND_HAVE_##modname = 0;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = ਨਿਰਾ;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = ਨਿਰਾ;
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandsym.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
            ਲਈ (i = 0; i < SDL_arraysize(waylandlibs); i++) {
                ਜੇ (waylandlibs[i].lib) {
                    SDL_UnloadObject(waylandlibs[i].lib);
                    waylandlibs[i].lib = ਨਿਰਾ;
                }
            }
#ਜੇ_ਅੰਤ
        }
    }
}

// returns non-zero if all needed symbols were loaded.
bool SDL_WAYLAND_ਲੱਦੋ_Symbols(ਖਾਲੀ)
{
    bool ਨਤੀਜਾ = true; // always succeed if not using Dynamic WAYLAND stuff.

    // deal with multiple modules (dga, wayland, etc) needing these symbols...
    ਜੇ (wayland_ਲੱਦੋ_refcount++ == 0) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
        ਪੂਰਨ i;
        ਪੂਰਨ *thismod = ਨਿਰਾ;
        ਲਈ (i = 0; i < SDL_arraysize(waylandlibs); i++) {
            ਜੇ (waylandlibs[i].libname) {
                ਜੇ (waylandlibs[i].hint &&
                    !SDL_GetHintBoolean(waylandlibs[i].hint, waylandlibs[i].hint_default)) {
                    ਜਾਰੀ;
                }
                waylandlibs[i].lib = SDL_ਲੱਦੋ_Object(waylandlibs[i].libname);
            }
        }

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_WAYLAND_MODULE(modname) SDL_WAYLAND_HAVE_##modname = 1; // default yes
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandsym.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_WAYLAND_MODULE(modname)         thismod = &SDL_WAYLAND_HAVE_##modname;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = (SDL_DYNWAYLANDFN_##fn)WAYLAND_GetSym(#fn, thismod, true);
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = (SDL_DYNWAYLANDFN_##fn)WAYLAND_GetSym(#fn, thismod, false);
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandsym.h"

        ਜੇ (SDL_WAYLAND_HAVE_WAYLAND_CLIENT &&
            SDL_WAYLAND_HAVE_WAYLAND_CURSOR &&
            SDL_WAYLAND_HAVE_WAYLAND_EGL &&
            SDL_WAYLAND_HAVE_WAYLAND_XKB) {
            // All required symbols loaded, only libdecor is optional.
            SDL_ClearError();
        } ਨਹੀਂਤਾਂ {
            // in case something got loaded...
            SDL_WAYLAND_UnloadSymbols();
            ਨਤੀਜਾ = false;
        }

#ਨਹੀਂਤਾਂ // no dynamic WAYLAND

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_WAYLAND_MODULE(modname)         SDL_WAYLAND_HAVE_##modname = 1; // default yes
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_WAYLAND_SYM(rc, fn, params)     WAYLAND_##fn = fn;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_WAYLAND_SYM_OPT(rc, fn, params) WAYLAND_##fn = fn;
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandsym.h"

#ਜੇ_ਅੰਤ
    }

    ਵਾਪਸ ਨਤੀਜਾ;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_WAYLAND
