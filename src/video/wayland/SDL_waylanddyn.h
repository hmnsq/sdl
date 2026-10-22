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
#اگر_تعریف_نشده SDL_waylanddyn_h_
#تعریف_کن SDL_waylanddyn_h_

#ضمن "SDL_internal.h"

/* We can't include wayland-client.h here
 * but we need some structs from it
 */
بنية wl_interface;
بنية wl_proxy;
بنية wl_event_صف;
بنية wl_display;
بنية wl_surface;
بنية wl_shm;

// We also need some for libdecor
بنية wl_seat;
بنية wl_output;
بنية libdecor;
بنية libdecor_قاب;
بنية libdecor_state;
بنية libdecor_configuration;
بنية libdecor_interface;
بنية libdecor_قاب_interface;
تعداد libdecor_resize_یال;
تعداد libdecor_capabilities;
تعداد libdecor_پنجره_state;

#ضمن "wayland-cursor.h"
#ضمن "wayland-util.h"
#ضمن "xkbcommon/xkbcommon.h"
#ضمن "xkbcommon/xkbcommon-compose.h"

// Must be included before our #defines, see Bugzilla #4957
#ضمن "wayland-client-core.h"

#تعریف_کن SDL_WAYLAND_CHECK_نسخه(x, y, z)                        \
    (WAYLAND_نسخه_MAJOR > x ||                                 \
     (WAYLAND_نسخه_MAJOR == x && WAYLAND_نسخه_MINOR > y) || \
     (WAYLAND_نسخه_MAJOR == x && WAYLAND_نسخه_MINOR == y && WAYLAND_نسخه_MICRO >= z))

#تعریف_کن SDL_XKBCOMMON_CHECK_نسخه(x, y, z)                                  \
    (SDL_XKBCOMMON_نسخه_MAJOR > x ||                                       \
     (SDL_XKBCOMMON_نسخه_MAJOR == x && SDL_XKBCOMMON_نسخه_MINOR > y) || \
     (SDL_XKBCOMMON_نسخه_MAJOR == x && SDL_XKBCOMMON_نسخه_MINOR == y && SDL_XKBCOMMON_نسخه_PATCH >= z))

#اگر_تعریف_شده HAVE_LIBDECOR_H
#تعریف_کن SDL_LIBDECOR_CHECK_نسخه(x, y, z)                                 \
    (SDL_LIBDECOR_نسخه_MAJOR > x ||                                      \
     (SDL_LIBDECOR_نسخه_MAJOR == x && SDL_LIBDECOR_نسخه_MINOR > y) || \
     (SDL_LIBDECOR_نسخه_MAJOR == x && SDL_LIBDECOR_نسخه_MINOR == y && SDL_LIBDECOR_نسخه_PATCH >= z))
#پایان_اگر

#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر

خارجي bool SDL_WAYLAND_بارگیری_Symbols(فراغ);
خارجي فراغ SDL_WAYLAND_UnloadSymbols(فراغ);

#تعریف_کن SDL_WAYLAND_MODULE(modname) خارجي صحيح SDL_WAYLAND_HAVE_##modname;
#تعریف_کن SDL_WAYLAND_SYM(rc, fn, params)        \
    تعريفنوع rc(*SDL_DYNWAYLANDFN_##fn) params; \
    خارجي SDL_DYNWAYLANDFN_##fn WAYLAND_##fn;
#تعریف_کن SDL_WAYLAND_SYM_OPT(rc, fn, params)    \
    تعريفنوع rc(*SDL_DYNWAYLANDFN_##fn) params; \
    خارجي SDL_DYNWAYLANDFN_##fn WAYLAND_##fn;
#تعریف_کن SDL_WAYLAND_INTERFACE(iface) خارجي ثابت بنية wl_interface *WAYLAND_##iface;
#ضمن "SDL_waylandsym.h"

#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#اگر_تعریف_شده SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

#إذا defined(_WAYLAND_CLIENT_H) || defined(WAYLAND_CLIENT_H)
#خطا Do not include wayland-client ahead از SDL_waylanddyn.h درون_2 dynamic loading نما
#پایان_اگر

/* wayland-client-protocol.h included from wayland-client.h
 * has inline functions that require these to be defined in dynamic loading mode
 */

#تعریف_کن wl_proxy_create                        (*WAYLAND_wl_proxy_create)
#تعریف_کن wl_proxy_destroy                       (*WAYLAND_wl_proxy_destroy)
#تعریف_کن wl_proxy_marshal                       (*WAYLAND_wl_proxy_marshal)
#تعریف_کن wl_proxy_مجموعه_user_داده                 (*WAYLAND_wl_proxy_مجموعه_user_داده)
#تعریف_کن wl_proxy_get_user_داده                 (*WAYLAND_wl_proxy_get_user_داده)
#تعریف_کن wl_proxy_get_نسخه                   (*WAYLAND_wl_proxy_get_نسخه)
#تعریف_کن wl_proxy_جمع_کن_listener                  (*WAYLAND_wl_proxy_جمع_کن_listener)
#تعریف_کن wl_proxy_marshal_constructor           (*WAYLAND_wl_proxy_marshal_constructor)
#تعریف_کن wl_proxy_marshal_constructor_versioned (*WAYLAND_wl_proxy_marshal_constructor_versioned)
#تعریف_کن wl_proxy_مجموعه_برچسب                       (*WAYLAND_wl_proxy_مجموعه_برچسب)
#تعریف_کن wl_proxy_get_برچسب                       (*WAYLAND_wl_proxy_get_برچسب)
#تعریف_کن wl_proxy_marshal_flags                 (*WAYLAND_wl_proxy_marshal_flags)
#تعریف_کن wl_proxy_marshal_array_flags           (*WAYLAND_wl_proxy_marshal_array_flags)
#تعریف_کن wl_display_reconnect                   (*WAYLAND_wl_display_reconnect)

/*
 * These must be included before libdecor.h, otherwise the libdecor header
 * pulls in the system Wayland protocol headers instead of ours.
 */
#ضمن "wayland-client-protocol.h"
#ضمن "wayland-egl.h"

#اگر_تعریف_شده HAVE_LIBDECOR_H
// Must be included before our defines
#ضمن <libdecor.h>

#تعریف_کن libdecor_unref                          (*WAYLAND_libdecor_unref)
#تعریف_کن libdecor_new                            (*WAYLAND_libdecor_new)
#تعریف_کن libdecor_decorate                       (*WAYLAND_libdecor_decorate)
#تعریف_کن libdecor_قاب_unref                    (*WAYLAND_libdecor_قاب_unref)
#تعریف_کن libdecor_قاب_مجموعه_title                (*WAYLAND_libdecor_قاب_مجموعه_title)
#تعریف_کن libdecor_قاب_مجموعه_app_id               (*WAYLAND_libdecor_قاب_مجموعه_app_id)
#تعریف_کن libdecor_قاب_مجموعه_max_content_اندازه     (*WAYLAND_libdecor_قاب_مجموعه_max_content_اندازه)
#تعریف_کن libdecor_قاب_get_max_content_اندازه     (*WAYLAND_libdecor_قاب_get_max_content_اندازه)
#تعریف_کن libdecor_قاب_مجموعه_min_content_اندازه     (*WAYLAND_libdecor_قاب_مجموعه_min_content_اندازه)
#تعریف_کن libdecor_قاب_get_min_content_اندازه     (*WAYLAND_libdecor_قاب_get_min_content_اندازه)
#تعریف_کن libdecor_قاب_resize                   (*WAYLAND_libdecor_قاب_resize)
#تعریف_کن libdecor_قاب_move                     (*WAYLAND_libdecor_قاب_move)
#تعریف_کن libdecor_قاب_commit                   (*WAYLAND_libdecor_قاب_commit)
#تعریف_کن libdecor_قاب_مجموعه_minimized            (*WAYLAND_libdecor_قاب_مجموعه_minimized)
#تعریف_کن libdecor_قاب_مجموعه_maximized            (*WAYLAND_libdecor_قاب_مجموعه_maximized)
#تعریف_کن libdecor_قاب_unset_maximized          (*WAYLAND_libdecor_قاب_unset_maximized)
#تعریف_کن libdecor_قاب_مجموعه_fullscreen           (*WAYLAND_libdecor_قاب_مجموعه_fullscreen)
#تعریف_کن libdecor_قاب_unset_fullscreen         (*WAYLAND_libdecor_قاب_unset_fullscreen)
#تعریف_کن libdecor_قاب_مجموعه_capabilities         (*WAYLAND_libdecor_قاب_مجموعه_capabilities)
#تعریف_کن libdecor_قاب_unset_capabilities       (*WAYLAND_libdecor_قاب_unset_capabilities)
#تعریف_کن libdecor_قاب_has_capability           (*WAYLAND_libdecor_قاب_has_capability)
#تعریف_کن libdecor_قاب_مجموعه_visibility           (*WAYLAND_libdecor_قاب_مجموعه_visibility)
#تعریف_کن libdecor_قاب_is_visible               (*WAYLAND_libdecor_قاب_is_visible)
#تعریف_کن libdecor_قاب_is_floating              (*WAYLAND_libdecor_قاب_is_floating)
#تعریف_کن libdecor_قاب_مجموعه_والد               (*WAYLAND_libdecor_قاب_مجموعه_والد)
#تعریف_کن libdecor_قاب_show_پنجره_menu         (*WAYLAND_libdecor_قاب_show_پنجره_menu)
#تعریف_کن libdecor_قاب_get_wm_capabilities      (*WAYLAND_libdecor_قاب_get_wm_capabilities)
#تعریف_کن libdecor_قاب_get_xdg_surface          (*WAYLAND_libdecor_قاب_get_xdg_surface)
#تعریف_کن libdecor_قاب_get_xdg_toplevel         (*WAYLAND_libdecor_قاب_get_xdg_toplevel)
#تعریف_کن libdecor_قاب_translate_coordinate     (*WAYLAND_libdecor_قاب_translate_coordinate)
#تعریف_کن libdecor_قاب_map                      (*WAYLAND_libdecor_قاب_map)
#تعریف_کن libdecor_state_new                      (*WAYLAND_libdecor_state_new)
#تعریف_کن libdecor_state_free                     (*WAYLAND_libdecor_state_free)
#تعریف_کن libdecor_configuration_get_content_اندازه (*WAYLAND_libdecor_configuration_get_content_اندازه)
#تعریف_کن libdecor_configuration_get_پنجره_state (*WAYLAND_libdecor_configuration_get_پنجره_state)
#تعریف_کن libdecor_dispatch                       (*WAYLAND_libdecor_dispatch)
#پایان_اگر

#وإلا // SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

/*
 * These must be included before libdecor.h, otherwise the libdecor header
 * pulls in the system Wayland protocol headers instead of ours.
 */
#ضمن "wayland-client-protocol.h"
#ضمن "wayland-egl.h"

#اگر_تعریف_شده HAVE_LIBDECOR_H
#ضمن <libdecor.h>
#پایان_اگر

#پایان_اگر // SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

#پایان_اگر // SDL_waylanddyn_h_
