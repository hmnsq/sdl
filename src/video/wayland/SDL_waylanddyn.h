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
#جيڪڏهن_وصف_نه_ٿيل SDL_waylanddyn_h_
#وصف_ڪريو SDL_waylanddyn_h_

#ضمن "SDL_internal.h"

/* We can't include wayland-client.h here
 * but we need some structs from it
 */
بنية wl_interface;
بنية wl_proxy;
بنية wl_event_قطار;
بنية wl_display;
بنية wl_surface;
بنية wl_shm;

// We also need some for libdecor
بنية wl_seat;
بنية wl_output;
بنية libdecor;
بنية libdecor_چوکٺو;
بنية libdecor_state;
بنية libdecor_configuration;
بنية libdecor_interface;
بنية libdecor_چوکٺو_interface;
تعداد libdecor_resize_ڪنارو;
تعداد libdecor_capabilities;
تعداد libdecor_دري_state;

#ضمن "wayland-cursor.h"
#ضمن "wayland-util.h"
#ضمن "xkbcommon/xkbcommon.h"
#ضمن "xkbcommon/xkbcommon-compose.h"

// Must be included before our #defines, see Bugzilla #4957
#ضمن "wayland-client-core.h"

#وصف_ڪريو SDL_WAYLAND_CHECK_نسخو(x, y, z)                        \
    (WAYLAND_نسخو_MAJOR > x ||                                 \
     (WAYLAND_نسخو_MAJOR == x && WAYLAND_نسخو_MINOR > y) || \
     (WAYLAND_نسخو_MAJOR == x && WAYLAND_نسخو_MINOR == y && WAYLAND_نسخو_MICRO >= z))

#وصف_ڪريو SDL_XKBCOMMON_CHECK_نسخو(x, y, z)                                  \
    (SDL_XKBCOMMON_نسخو_MAJOR > x ||                                       \
     (SDL_XKBCOMMON_نسخو_MAJOR == x && SDL_XKBCOMMON_نسخو_MINOR > y) || \
     (SDL_XKBCOMMON_نسخو_MAJOR == x && SDL_XKBCOMMON_نسخو_MINOR == y && SDL_XKBCOMMON_نسخو_PATCH >= z))

#جيڪڏهن_وصف_ٿيل HAVE_LIBDECOR_H
#وصف_ڪريو SDL_LIBDECOR_CHECK_نسخو(x, y, z)                                 \
    (SDL_LIBDECOR_نسخو_MAJOR > x ||                                      \
     (SDL_LIBDECOR_نسخو_MAJOR == x && SDL_LIBDECOR_نسخو_MINOR > y) || \
     (SDL_LIBDECOR_نسخو_MAJOR == x && SDL_LIBDECOR_نسخو_MINOR == y && SDL_LIBDECOR_نسخو_PATCH >= z))
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل __cplusplus
خارجي "C" {
#جيڪڏهن_پورو

خارجي bool SDL_WAYLAND_ڀريو_Symbols(فراغ);
خارجي فراغ SDL_WAYLAND_UnloadSymbols(فراغ);

#وصف_ڪريو SDL_WAYLAND_MODULE(modname) خارجي صحيح SDL_WAYLAND_HAVE_##modname;
#وصف_ڪريو SDL_WAYLAND_SYM(rc, fn, params)        \
    تعريفنوع rc(*SDL_DYNWAYLANDFN_##fn) params; \
    خارجي SDL_DYNWAYLANDFN_##fn WAYLAND_##fn;
#وصف_ڪريو SDL_WAYLAND_SYM_OPT(rc, fn, params)    \
    تعريفنوع rc(*SDL_DYNWAYLANDFN_##fn) params; \
    خارجي SDL_DYNWAYLANDFN_##fn WAYLAND_##fn;
#وصف_ڪريو SDL_WAYLAND_INTERFACE(iface) خارجي ثابت بنية wl_interface *WAYLAND_##iface;
#ضمن "SDL_waylandsym.h"

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

#إذا defined(_WAYLAND_CLIENT_H) || defined(WAYLAND_CLIENT_H)
#غلطي Do not include wayland-client ahead جو SDL_waylanddyn.h اندريون_2 dynamic loading گهڻائي
#جيڪڏهن_پورو

/* wayland-client-protocol.h included from wayland-client.h
 * has inline functions that require these to be defined in dynamic loading mode
 */

#وصف_ڪريو wl_proxy_create                        (*WAYLAND_wl_proxy_create)
#وصف_ڪريو wl_proxy_destroy                       (*WAYLAND_wl_proxy_destroy)
#وصف_ڪريو wl_proxy_marshal                       (*WAYLAND_wl_proxy_marshal)
#وصف_ڪريو wl_proxy_سيٽ_user_معلومات                 (*WAYLAND_wl_proxy_سيٽ_user_معلومات)
#وصف_ڪريو wl_proxy_get_user_معلومات                 (*WAYLAND_wl_proxy_get_user_معلومات)
#وصف_ڪريو wl_proxy_get_نسخو                   (*WAYLAND_wl_proxy_get_نسخو)
#وصف_ڪريو wl_proxy_جوڙيو_listener                  (*WAYLAND_wl_proxy_جوڙيو_listener)
#وصف_ڪريو wl_proxy_marshal_constructor           (*WAYLAND_wl_proxy_marshal_constructor)
#وصف_ڪريو wl_proxy_marshal_constructor_versioned (*WAYLAND_wl_proxy_marshal_constructor_versioned)
#وصف_ڪريو wl_proxy_سيٽ_ٽيگ                       (*WAYLAND_wl_proxy_سيٽ_ٽيگ)
#وصف_ڪريو wl_proxy_get_ٽيگ                       (*WAYLAND_wl_proxy_get_ٽيگ)
#وصف_ڪريو wl_proxy_marshal_flags                 (*WAYLAND_wl_proxy_marshal_flags)
#وصف_ڪريو wl_proxy_marshal_array_flags           (*WAYLAND_wl_proxy_marshal_array_flags)
#وصف_ڪريو wl_display_reconnect                   (*WAYLAND_wl_display_reconnect)

/*
 * These must be included before libdecor.h, otherwise the libdecor header
 * pulls in the system Wayland protocol headers instead of ours.
 */
#ضمن "wayland-client-protocol.h"
#ضمن "wayland-egl.h"

#جيڪڏهن_وصف_ٿيل HAVE_LIBDECOR_H
// Must be included before our defines
#ضمن <libdecor.h>

#وصف_ڪريو libdecor_unref                          (*WAYLAND_libdecor_unref)
#وصف_ڪريو libdecor_new                            (*WAYLAND_libdecor_new)
#وصف_ڪريو libdecor_decorate                       (*WAYLAND_libdecor_decorate)
#وصف_ڪريو libdecor_چوکٺو_unref                    (*WAYLAND_libdecor_چوکٺو_unref)
#وصف_ڪريو libdecor_چوکٺو_سيٽ_title                (*WAYLAND_libdecor_چوکٺو_سيٽ_title)
#وصف_ڪريو libdecor_چوکٺو_سيٽ_app_id               (*WAYLAND_libdecor_چوکٺو_سيٽ_app_id)
#وصف_ڪريو libdecor_چوکٺو_سيٽ_max_content_سائيز     (*WAYLAND_libdecor_چوکٺو_سيٽ_max_content_سائيز)
#وصف_ڪريو libdecor_چوکٺو_get_max_content_سائيز     (*WAYLAND_libdecor_چوکٺو_get_max_content_سائيز)
#وصف_ڪريو libdecor_چوکٺو_سيٽ_min_content_سائيز     (*WAYLAND_libdecor_چوکٺو_سيٽ_min_content_سائيز)
#وصف_ڪريو libdecor_چوکٺو_get_min_content_سائيز     (*WAYLAND_libdecor_چوکٺو_get_min_content_سائيز)
#وصف_ڪريو libdecor_چوکٺو_resize                   (*WAYLAND_libdecor_چوکٺو_resize)
#وصف_ڪريو libdecor_چوکٺو_move                     (*WAYLAND_libdecor_چوکٺو_move)
#وصف_ڪريو libdecor_چوکٺو_commit                   (*WAYLAND_libdecor_چوکٺو_commit)
#وصف_ڪريو libdecor_چوکٺو_سيٽ_minimized            (*WAYLAND_libdecor_چوکٺو_سيٽ_minimized)
#وصف_ڪريو libdecor_چوکٺو_سيٽ_maximized            (*WAYLAND_libdecor_چوکٺو_سيٽ_maximized)
#وصف_ڪريو libdecor_چوکٺو_unset_maximized          (*WAYLAND_libdecor_چوکٺو_unset_maximized)
#وصف_ڪريو libdecor_چوکٺو_سيٽ_fullscreen           (*WAYLAND_libdecor_چوکٺو_سيٽ_fullscreen)
#وصف_ڪريو libdecor_چوکٺو_unset_fullscreen         (*WAYLAND_libdecor_چوکٺو_unset_fullscreen)
#وصف_ڪريو libdecor_چوکٺو_سيٽ_capabilities         (*WAYLAND_libdecor_چوکٺو_سيٽ_capabilities)
#وصف_ڪريو libdecor_چوکٺو_unset_capabilities       (*WAYLAND_libdecor_چوکٺو_unset_capabilities)
#وصف_ڪريو libdecor_چوکٺو_has_capability           (*WAYLAND_libdecor_چوکٺو_has_capability)
#وصف_ڪريو libdecor_چوکٺو_سيٽ_visibility           (*WAYLAND_libdecor_چوکٺو_سيٽ_visibility)
#وصف_ڪريو libdecor_چوکٺو_is_visible               (*WAYLAND_libdecor_چوکٺو_is_visible)
#وصف_ڪريو libdecor_چوکٺو_is_floating              (*WAYLAND_libdecor_چوکٺو_is_floating)
#وصف_ڪريو libdecor_چوکٺو_سيٽ_والد               (*WAYLAND_libdecor_چوکٺو_سيٽ_والد)
#وصف_ڪريو libdecor_چوکٺو_show_دري_menu         (*WAYLAND_libdecor_چوکٺو_show_دري_menu)
#وصف_ڪريو libdecor_چوکٺو_get_wm_capabilities      (*WAYLAND_libdecor_چوکٺو_get_wm_capabilities)
#وصف_ڪريو libdecor_چوکٺو_get_xdg_surface          (*WAYLAND_libdecor_چوکٺو_get_xdg_surface)
#وصف_ڪريو libdecor_چوکٺو_get_xdg_toplevel         (*WAYLAND_libdecor_چوکٺو_get_xdg_toplevel)
#وصف_ڪريو libdecor_چوکٺو_translate_coordinate     (*WAYLAND_libdecor_چوکٺو_translate_coordinate)
#وصف_ڪريو libdecor_چوکٺو_map                      (*WAYLAND_libdecor_چوکٺو_map)
#وصف_ڪريو libdecor_state_new                      (*WAYLAND_libdecor_state_new)
#وصف_ڪريو libdecor_state_free                     (*WAYLAND_libdecor_state_free)
#وصف_ڪريو libdecor_configuration_get_content_سائيز (*WAYLAND_libdecor_configuration_get_content_سائيز)
#وصف_ڪريو libdecor_configuration_get_دري_state (*WAYLAND_libdecor_configuration_get_دري_state)
#وصف_ڪريو libdecor_dispatch                       (*WAYLAND_libdecor_dispatch)
#جيڪڏهن_پورو

#وإلا // SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

/*
 * These must be included before libdecor.h, otherwise the libdecor header
 * pulls in the system Wayland protocol headers instead of ours.
 */
#ضمن "wayland-client-protocol.h"
#ضمن "wayland-egl.h"

#جيڪڏهن_وصف_ٿيل HAVE_LIBDECOR_H
#ضمن <libdecor.h>
#جيڪڏهن_پورو

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

#جيڪڏهن_پورو // SDL_waylanddyn_h_
