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
#که_نه_تعریف_شوی SDL_waylanddyn_h_
#تعریف_کړه SDL_waylanddyn_h_

#ضمن "SDL_internal.h"

/* We can't include wayland-client.h here
 * but we need some structs from it
 */
بنية wl_interface;
بنية wl_proxy;
بنية wl_event_کتار;
بنية wl_display;
بنية wl_surface;
بنية wl_shm;

// We also need some for libdecor
بنية wl_seat;
بنية wl_output;
بنية libdecor;
بنية libdecor_چوکاټ;
بنية libdecor_state;
بنية libdecor_configuration;
بنية libdecor_interface;
بنية libdecor_چوکاټ_interface;
تعداد libdecor_resize_څنډه;
تعداد libdecor_capabilities;
تعداد libdecor_کړکۍ_state;

#ضمن "wayland-cursor.h"
#ضمن "wayland-util.h"
#ضمن "xkbcommon/xkbcommon.h"
#ضمن "xkbcommon/xkbcommon-compose.h"

// Must be included before our #defines, see Bugzilla #4957
#ضمن "wayland-client-core.h"

#تعریف_کړه SDL_WAYLAND_CHECK_نسخه(x, y, z)                        \
    (WAYLAND_نسخه_MAJOR > x ||                                 \
     (WAYLAND_نسخه_MAJOR == x && WAYLAND_نسخه_MINOR > y) || \
     (WAYLAND_نسخه_MAJOR == x && WAYLAND_نسخه_MINOR == y && WAYLAND_نسخه_MICRO >= z))

#تعریف_کړه SDL_XKBCOMMON_CHECK_نسخه(x, y, z)                                  \
    (SDL_XKBCOMMON_نسخه_MAJOR > x ||                                       \
     (SDL_XKBCOMMON_نسخه_MAJOR == x && SDL_XKBCOMMON_نسخه_MINOR > y) || \
     (SDL_XKBCOMMON_نسخه_MAJOR == x && SDL_XKBCOMMON_نسخه_MINOR == y && SDL_XKBCOMMON_نسخه_PATCH >= z))

#که_تعریف_شوی HAVE_LIBDECOR_H
#تعریف_کړه SDL_LIBDECOR_CHECK_نسخه(x, y, z)                                 \
    (SDL_LIBDECOR_نسخه_MAJOR > x ||                                      \
     (SDL_LIBDECOR_نسخه_MAJOR == x && SDL_LIBDECOR_نسخه_MINOR > y) || \
     (SDL_LIBDECOR_نسخه_MAJOR == x && SDL_LIBDECOR_نسخه_MINOR == y && SDL_LIBDECOR_نسخه_PATCH >= z))
#د_که_پای

#که_تعریف_شوی __cplusplus
خارجي "C" {
#د_که_پای

خارجي bool SDL_WAYLAND_بارول_Symbols(فراغ);
خارجي فراغ SDL_WAYLAND_UnloadSymbols(فراغ);

#تعریف_کړه SDL_WAYLAND_MODULE(modname) خارجي صحيح SDL_WAYLAND_HAVE_##modname;
#تعریف_کړه SDL_WAYLAND_SYM(rc, fn, params)        \
    تعريفنوع rc(*SDL_DYNWAYLANDFN_##fn) params; \
    خارجي SDL_DYNWAYLANDFN_##fn WAYLAND_##fn;
#تعریف_کړه SDL_WAYLAND_SYM_OPT(rc, fn, params)    \
    تعريفنوع rc(*SDL_DYNWAYLANDFN_##fn) params; \
    خارجي SDL_DYNWAYLANDFN_##fn WAYLAND_##fn;
#تعریف_کړه SDL_WAYLAND_INTERFACE(iface) خارجي ثابت بنية wl_interface *WAYLAND_##iface;
#ضمن "SDL_waylandsym.h"

#که_تعریف_شوی __cplusplus
}
#د_که_پای

#که_تعریف_شوی SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

#إذا defined(_WAYLAND_CLIENT_H) || defined(WAYLAND_CLIENT_H)
#تېروتنه Do not include wayland-client ahead د SDL_waylanddyn.h دننه_2 dynamic loading ډېرپېښ
#د_که_پای

/* wayland-client-protocol.h included from wayland-client.h
 * has inline functions that require these to be defined in dynamic loading mode
 */

#تعریف_کړه wl_proxy_create                        (*WAYLAND_wl_proxy_create)
#تعریف_کړه wl_proxy_destroy                       (*WAYLAND_wl_proxy_destroy)
#تعریف_کړه wl_proxy_marshal                       (*WAYLAND_wl_proxy_marshal)
#تعریف_کړه wl_proxy_سېټ_user_معلومات                 (*WAYLAND_wl_proxy_سېټ_user_معلومات)
#تعریف_کړه wl_proxy_get_user_معلومات                 (*WAYLAND_wl_proxy_get_user_معلومات)
#تعریف_کړه wl_proxy_get_نسخه                   (*WAYLAND_wl_proxy_get_نسخه)
#تعریف_کړه wl_proxy_جمع_کړه_listener                  (*WAYLAND_wl_proxy_جمع_کړه_listener)
#تعریف_کړه wl_proxy_marshal_constructor           (*WAYLAND_wl_proxy_marshal_constructor)
#تعریف_کړه wl_proxy_marshal_constructor_versioned (*WAYLAND_wl_proxy_marshal_constructor_versioned)
#تعریف_کړه wl_proxy_سېټ_نښان                       (*WAYLAND_wl_proxy_سېټ_نښان)
#تعریف_کړه wl_proxy_get_نښان                       (*WAYLAND_wl_proxy_get_نښان)
#تعریف_کړه wl_proxy_marshal_flags                 (*WAYLAND_wl_proxy_marshal_flags)
#تعریف_کړه wl_proxy_marshal_array_flags           (*WAYLAND_wl_proxy_marshal_array_flags)
#تعریف_کړه wl_display_reconnect                   (*WAYLAND_wl_display_reconnect)

/*
 * These must be included before libdecor.h, otherwise the libdecor header
 * pulls in the system Wayland protocol headers instead of ours.
 */
#ضمن "wayland-client-protocol.h"
#ضمن "wayland-egl.h"

#که_تعریف_شوی HAVE_LIBDECOR_H
// Must be included before our defines
#ضمن <libdecor.h>

#تعریف_کړه libdecor_unref                          (*WAYLAND_libdecor_unref)
#تعریف_کړه libdecor_new                            (*WAYLAND_libdecor_new)
#تعریف_کړه libdecor_decorate                       (*WAYLAND_libdecor_decorate)
#تعریف_کړه libdecor_چوکاټ_unref                    (*WAYLAND_libdecor_چوکاټ_unref)
#تعریف_کړه libdecor_چوکاټ_سېټ_title                (*WAYLAND_libdecor_چوکاټ_سېټ_title)
#تعریف_کړه libdecor_چوکاټ_سېټ_app_id               (*WAYLAND_libdecor_چوکاټ_سېټ_app_id)
#تعریف_کړه libdecor_چوکاټ_سېټ_max_content_اندازه     (*WAYLAND_libdecor_چوکاټ_سېټ_max_content_اندازه)
#تعریف_کړه libdecor_چوکاټ_get_max_content_اندازه     (*WAYLAND_libdecor_چوکاټ_get_max_content_اندازه)
#تعریف_کړه libdecor_چوکاټ_سېټ_min_content_اندازه     (*WAYLAND_libdecor_چوکاټ_سېټ_min_content_اندازه)
#تعریف_کړه libdecor_چوکاټ_get_min_content_اندازه     (*WAYLAND_libdecor_چوکاټ_get_min_content_اندازه)
#تعریف_کړه libdecor_چوکاټ_resize                   (*WAYLAND_libdecor_چوکاټ_resize)
#تعریف_کړه libdecor_چوکاټ_move                     (*WAYLAND_libdecor_چوکاټ_move)
#تعریف_کړه libdecor_چوکاټ_commit                   (*WAYLAND_libdecor_چوکاټ_commit)
#تعریف_کړه libdecor_چوکاټ_سېټ_minimized            (*WAYLAND_libdecor_چوکاټ_سېټ_minimized)
#تعریف_کړه libdecor_چوکاټ_سېټ_maximized            (*WAYLAND_libdecor_چوکاټ_سېټ_maximized)
#تعریف_کړه libdecor_چوکاټ_unset_maximized          (*WAYLAND_libdecor_چوکاټ_unset_maximized)
#تعریف_کړه libdecor_چوکاټ_سېټ_fullscreen           (*WAYLAND_libdecor_چوکاټ_سېټ_fullscreen)
#تعریف_کړه libdecor_چوکاټ_unset_fullscreen         (*WAYLAND_libdecor_چوکاټ_unset_fullscreen)
#تعریف_کړه libdecor_چوکاټ_سېټ_capabilities         (*WAYLAND_libdecor_چوکاټ_سېټ_capabilities)
#تعریف_کړه libdecor_چوکاټ_unset_capabilities       (*WAYLAND_libdecor_چوکاټ_unset_capabilities)
#تعریف_کړه libdecor_چوکاټ_has_capability           (*WAYLAND_libdecor_چوکاټ_has_capability)
#تعریف_کړه libdecor_چوکاټ_سېټ_visibility           (*WAYLAND_libdecor_چوکاټ_سېټ_visibility)
#تعریف_کړه libdecor_چوکاټ_is_visible               (*WAYLAND_libdecor_چوکاټ_is_visible)
#تعریف_کړه libdecor_چوکاټ_is_floating              (*WAYLAND_libdecor_چوکاټ_is_floating)
#تعریف_کړه libdecor_چوکاټ_سېټ_پلار               (*WAYLAND_libdecor_چوکاټ_سېټ_پلار)
#تعریف_کړه libdecor_چوکاټ_show_کړکۍ_menu         (*WAYLAND_libdecor_چوکاټ_show_کړکۍ_menu)
#تعریف_کړه libdecor_چوکاټ_get_wm_capabilities      (*WAYLAND_libdecor_چوکاټ_get_wm_capabilities)
#تعریف_کړه libdecor_چوکاټ_get_xdg_surface          (*WAYLAND_libdecor_چوکاټ_get_xdg_surface)
#تعریف_کړه libdecor_چوکاټ_get_xdg_toplevel         (*WAYLAND_libdecor_چوکاټ_get_xdg_toplevel)
#تعریف_کړه libdecor_چوکاټ_translate_coordinate     (*WAYLAND_libdecor_چوکاټ_translate_coordinate)
#تعریف_کړه libdecor_چوکاټ_map                      (*WAYLAND_libdecor_چوکاټ_map)
#تعریف_کړه libdecor_state_new                      (*WAYLAND_libdecor_state_new)
#تعریف_کړه libdecor_state_free                     (*WAYLAND_libdecor_state_free)
#تعریف_کړه libdecor_configuration_get_content_اندازه (*WAYLAND_libdecor_configuration_get_content_اندازه)
#تعریف_کړه libdecor_configuration_get_کړکۍ_state (*WAYLAND_libdecor_configuration_get_کړکۍ_state)
#تعریف_کړه libdecor_dispatch                       (*WAYLAND_libdecor_dispatch)
#د_که_پای

#وإلا // SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

/*
 * These must be included before libdecor.h, otherwise the libdecor header
 * pulls in the system Wayland protocol headers instead of ours.
 */
#ضمن "wayland-client-protocol.h"
#ضمن "wayland-egl.h"

#که_تعریف_شوی HAVE_LIBDECOR_H
#ضمن <libdecor.h>
#د_که_پای

#د_که_پای // SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

#د_که_پای // SDL_waylanddyn_h_
