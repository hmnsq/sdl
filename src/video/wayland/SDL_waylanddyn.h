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
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_waylanddyn_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_waylanddyn_h_

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

/* We can't include wayland-client.h here
 * but we need some structs from it
 */
ਬਣਤਰ wl_interface;
ਬਣਤਰ wl_proxy;
ਬਣਤਰ wl_event_ਕਤਾਰ;
ਬਣਤਰ wl_display;
ਬਣਤਰ wl_surface;
ਬਣਤਰ wl_shm;

// We also need some for libdecor
ਬਣਤਰ wl_seat;
ਬਣਤਰ wl_output;
ਬਣਤਰ libdecor;
ਬਣਤਰ libdecor_ਚੌਖਟਾ;
ਬਣਤਰ libdecor_state;
ਬਣਤਰ libdecor_configuration;
ਬਣਤਰ libdecor_interface;
ਬਣਤਰ libdecor_ਚੌਖਟਾ_interface;
ਗਿਣਤੀ libdecor_resize_ਕਿਨਾਰਾ;
ਗਿਣਤੀ libdecor_capabilities;
ਗਿਣਤੀ libdecor_ਖਿੜਕੀ_state;

#ਅਨ੍ਤਰ੍ਭਾਵ "wayland-cursor.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "wayland-util.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "xkbcommon/xkbcommon.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "xkbcommon/xkbcommon-compose.h"

// Must be included before our #defines, see Bugzilla #4957
#ਅਨ੍ਤਰ੍ਭਾਵ "wayland-client-core.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_WAYLAND_CHECK_ਸੰਸਕਰਣ(x, y, z)                        \
    (WAYLAND_ਸੰਸਕਰਣ_MAJOR > x ||                                 \
     (WAYLAND_ਸੰਸਕਰਣ_MAJOR == x && WAYLAND_ਸੰਸਕਰਣ_MINOR > y) || \
     (WAYLAND_ਸੰਸਕਰਣ_MAJOR == x && WAYLAND_ਸੰਸਕਰਣ_MINOR == y && WAYLAND_ਸੰਸਕਰਣ_MICRO >= z))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_XKBCOMMON_CHECK_ਸੰਸਕਰਣ(x, y, z)                                  \
    (SDL_XKBCOMMON_ਸੰਸਕਰਣ_MAJOR > x ||                                       \
     (SDL_XKBCOMMON_ਸੰਸਕਰਣ_MAJOR == x && SDL_XKBCOMMON_ਸੰਸਕਰਣ_MINOR > y) || \
     (SDL_XKBCOMMON_ਸੰਸਕਰਣ_MAJOR == x && SDL_XKBCOMMON_ਸੰਸਕਰਣ_MINOR == y && SDL_XKBCOMMON_ਸੰਸਕਰਣ_PATCH >= z))

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_LIBDECOR_CHECK_ਸੰਸਕਰਣ(x, y, z)                                 \
    (SDL_LIBDECOR_ਸੰਸਕਰਣ_MAJOR > x ||                                      \
     (SDL_LIBDECOR_ਸੰਸਕਰਣ_MAJOR == x && SDL_LIBDECOR_ਸੰਸਕਰਣ_MINOR > y) || \
     (SDL_LIBDECOR_ਸੰਸਕਰਣ_MAJOR == x && SDL_LIBDECOR_ਸੰਸਕਰਣ_MINOR == y && SDL_LIBDECOR_ਸੰਸਕਰਣ_PATCH >= z))
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ

ਬਾਹਰੀ bool SDL_WAYLAND_ਲੱਦੋ_Symbols(ਖਾਲੀ);
ਬਾਹਰੀ ਖਾਲੀ SDL_WAYLAND_UnloadSymbols(ਖਾਲੀ);

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_WAYLAND_MODULE(modname) ਬਾਹਰੀ ਪੂਰਨ SDL_WAYLAND_HAVE_##modname;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_WAYLAND_SYM(rc, fn, params)        \
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ rc(*SDL_DYNWAYLANDFN_##fn) params; \
    ਬਾਹਰੀ SDL_DYNWAYLANDFN_##fn WAYLAND_##fn;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_WAYLAND_SYM_OPT(rc, fn, params)    \
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ rc(*SDL_DYNWAYLANDFN_##fn) params; \
    ਬਾਹਰੀ SDL_DYNWAYLANDFN_##fn WAYLAND_##fn;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_WAYLAND_INTERFACE(iface) ਬਾਹਰੀ ਅਚਲ ਬਣਤਰ wl_interface *WAYLAND_##iface;
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandsym.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

#ਜੇ defined(_WAYLAND_CLIENT_H) || defined(WAYLAND_CLIENT_H)
#ਗਲਤੀ Do not include wayland-client ahead ਦਾ SDL_waylanddyn.h ਵਿੱਚ_2 dynamic loading ਬਹੁਲਕ
#ਜੇ_ਅੰਤ

/* wayland-client-protocol.h included from wayland-client.h
 * has inline functions that require these to be defined in dynamic loading mode
 */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ wl_proxy_create                        (*WAYLAND_wl_proxy_create)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ wl_proxy_destroy                       (*WAYLAND_wl_proxy_destroy)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ wl_proxy_marshal                       (*WAYLAND_wl_proxy_marshal)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ wl_proxy_ਸੈੱਟ_user_ਅੰਕੜੇ                 (*WAYLAND_wl_proxy_ਸੈੱਟ_user_ਅੰਕੜੇ)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ wl_proxy_get_user_ਅੰਕੜੇ                 (*WAYLAND_wl_proxy_get_user_ਅੰਕੜੇ)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ wl_proxy_get_ਸੰਸਕਰਣ                   (*WAYLAND_wl_proxy_get_ਸੰਸਕਰਣ)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ wl_proxy_ਜੋੜੋ_listener                  (*WAYLAND_wl_proxy_ਜੋੜੋ_listener)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ wl_proxy_marshal_constructor           (*WAYLAND_wl_proxy_marshal_constructor)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ wl_proxy_marshal_constructor_versioned (*WAYLAND_wl_proxy_marshal_constructor_versioned)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ wl_proxy_ਸੈੱਟ_ਟੈਗ                       (*WAYLAND_wl_proxy_ਸੈੱਟ_ਟੈਗ)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ wl_proxy_get_ਟੈਗ                       (*WAYLAND_wl_proxy_get_ਟੈਗ)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ wl_proxy_marshal_flags                 (*WAYLAND_wl_proxy_marshal_flags)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ wl_proxy_marshal_array_flags           (*WAYLAND_wl_proxy_marshal_array_flags)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ wl_display_reconnect                   (*WAYLAND_wl_display_reconnect)

/*
 * These must be included before libdecor.h, otherwise the libdecor header
 * pulls in the system Wayland protocol headers instead of ours.
 */
#ਅਨ੍ਤਰ੍ਭਾਵ "wayland-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "wayland-egl.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
// Must be included before our defines
#ਅਨ੍ਤਰ੍ਭਾਵ <libdecor.h>

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_unref                          (*WAYLAND_libdecor_unref)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_new                            (*WAYLAND_libdecor_new)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_decorate                       (*WAYLAND_libdecor_decorate)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_ਚੌਖਟਾ_unref                    (*WAYLAND_libdecor_ਚੌਖਟਾ_unref)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_ਚੌਖਟਾ_ਸੈੱਟ_title                (*WAYLAND_libdecor_ਚੌਖਟਾ_ਸੈੱਟ_title)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_ਚੌਖਟਾ_ਸੈੱਟ_app_id               (*WAYLAND_libdecor_ਚੌਖਟਾ_ਸੈੱਟ_app_id)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_ਚੌਖਟਾ_ਸੈੱਟ_max_content_ਮਾਪ     (*WAYLAND_libdecor_ਚੌਖਟਾ_ਸੈੱਟ_max_content_ਮਾਪ)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_ਚੌਖਟਾ_get_max_content_ਮਾਪ     (*WAYLAND_libdecor_ਚੌਖਟਾ_get_max_content_ਮਾਪ)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_ਚੌਖਟਾ_ਸੈੱਟ_min_content_ਮਾਪ     (*WAYLAND_libdecor_ਚੌਖਟਾ_ਸੈੱਟ_min_content_ਮਾਪ)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_ਚੌਖਟਾ_get_min_content_ਮਾਪ     (*WAYLAND_libdecor_ਚੌਖਟਾ_get_min_content_ਮਾਪ)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_ਚੌਖਟਾ_resize                   (*WAYLAND_libdecor_ਚੌਖਟਾ_resize)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_ਚੌਖਟਾ_move                     (*WAYLAND_libdecor_ਚੌਖਟਾ_move)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_ਚੌਖਟਾ_commit                   (*WAYLAND_libdecor_ਚੌਖਟਾ_commit)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_ਚੌਖਟਾ_ਸੈੱਟ_minimized            (*WAYLAND_libdecor_ਚੌਖਟਾ_ਸੈੱਟ_minimized)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_ਚੌਖਟਾ_ਸੈੱਟ_maximized            (*WAYLAND_libdecor_ਚੌਖਟਾ_ਸੈੱਟ_maximized)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_ਚੌਖਟਾ_unset_maximized          (*WAYLAND_libdecor_ਚੌਖਟਾ_unset_maximized)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_ਚੌਖਟਾ_ਸੈੱਟ_fullscreen           (*WAYLAND_libdecor_ਚੌਖਟਾ_ਸੈੱਟ_fullscreen)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_ਚੌਖਟਾ_unset_fullscreen         (*WAYLAND_libdecor_ਚੌਖਟਾ_unset_fullscreen)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_ਚੌਖਟਾ_ਸੈੱਟ_capabilities         (*WAYLAND_libdecor_ਚੌਖਟਾ_ਸੈੱਟ_capabilities)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_ਚੌਖਟਾ_unset_capabilities       (*WAYLAND_libdecor_ਚੌਖਟਾ_unset_capabilities)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_ਚੌਖਟਾ_has_capability           (*WAYLAND_libdecor_ਚੌਖਟਾ_has_capability)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_ਚੌਖਟਾ_ਸੈੱਟ_visibility           (*WAYLAND_libdecor_ਚੌਖਟਾ_ਸੈੱਟ_visibility)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_ਚੌਖਟਾ_is_visible               (*WAYLAND_libdecor_ਚੌਖਟਾ_is_visible)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_ਚੌਖਟਾ_is_floating              (*WAYLAND_libdecor_ਚੌਖਟਾ_is_floating)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_ਚੌਖਟਾ_ਸੈੱਟ_ਮਾਪਾ               (*WAYLAND_libdecor_ਚੌਖਟਾ_ਸੈੱਟ_ਮਾਪਾ)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_ਚੌਖਟਾ_show_ਖਿੜਕੀ_menu         (*WAYLAND_libdecor_ਚੌਖਟਾ_show_ਖਿੜਕੀ_menu)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_ਚੌਖਟਾ_get_wm_capabilities      (*WAYLAND_libdecor_ਚੌਖਟਾ_get_wm_capabilities)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_ਚੌਖਟਾ_get_xdg_surface          (*WAYLAND_libdecor_ਚੌਖਟਾ_get_xdg_surface)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_ਚੌਖਟਾ_get_xdg_toplevel         (*WAYLAND_libdecor_ਚੌਖਟਾ_get_xdg_toplevel)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_ਚੌਖਟਾ_translate_coordinate     (*WAYLAND_libdecor_ਚੌਖਟਾ_translate_coordinate)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_ਚੌਖਟਾ_map                      (*WAYLAND_libdecor_ਚੌਖਟਾ_map)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_state_new                      (*WAYLAND_libdecor_state_new)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_state_free                     (*WAYLAND_libdecor_state_free)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_configuration_get_content_ਮਾਪ (*WAYLAND_libdecor_configuration_get_content_ਮਾਪ)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_configuration_get_ਖਿੜਕੀ_state (*WAYLAND_libdecor_configuration_get_ਖਿੜਕੀ_state)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libdecor_dispatch                       (*WAYLAND_libdecor_dispatch)
#ਜੇ_ਅੰਤ

#ਨਹੀਂਤਾਂ // SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

/*
 * These must be included before libdecor.h, otherwise the libdecor header
 * pulls in the system Wayland protocol headers instead of ours.
 */
#ਅਨ੍ਤਰ੍ਭਾਵ "wayland-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "wayland-egl.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
#ਅਨ੍ਤਰ੍ਭਾਵ <libdecor.h>
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

#ਜੇ_ਅੰਤ // SDL_waylanddyn_h_
