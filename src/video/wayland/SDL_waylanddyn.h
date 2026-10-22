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
#جے_بنا_تعریف SDL_waylanddyn_h_
#تعریف_کرو SDL_waylanddyn_h_

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
بنية libdecor_چوکھٹا;
بنية libdecor_state;
بنية libdecor_configuration;
بنية libdecor_interface;
بنية libdecor_چوکھٹا_interface;
تعداد libdecor_resize_کنارا;
تعداد libdecor_capabilities;
تعداد libdecor_کھڑکی_state;

#ضمن "wayland-cursor.h"
#ضمن "wayland-util.h"
#ضمن "xkbcommon/xkbcommon.h"
#ضمن "xkbcommon/xkbcommon-compose.h"

// Must be included before our #defines, see Bugzilla #4957
#ضمن "wayland-client-core.h"

#تعریف_کرو SDL_WAYLAND_CHECK_نسخہ(x, y, z)                        \
    (WAYLAND_نسخہ_MAJOR > x ||                                 \
     (WAYLAND_نسخہ_MAJOR == x && WAYLAND_نسخہ_MINOR > y) || \
     (WAYLAND_نسخہ_MAJOR == x && WAYLAND_نسخہ_MINOR == y && WAYLAND_نسخہ_MICRO >= z))

#تعریف_کرو SDL_XKBCOMMON_CHECK_نسخہ(x, y, z)                                  \
    (SDL_XKBCOMMON_نسخہ_MAJOR > x ||                                       \
     (SDL_XKBCOMMON_نسخہ_MAJOR == x && SDL_XKBCOMMON_نسخہ_MINOR > y) || \
     (SDL_XKBCOMMON_نسخہ_MAJOR == x && SDL_XKBCOMMON_نسخہ_MINOR == y && SDL_XKBCOMMON_نسخہ_PATCH >= z))

#جے_تعریف_شدہ HAVE_LIBDECOR_H
#تعریف_کرو SDL_LIBDECOR_CHECK_نسخہ(x, y, z)                                 \
    (SDL_LIBDECOR_نسخہ_MAJOR > x ||                                      \
     (SDL_LIBDECOR_نسخہ_MAJOR == x && SDL_LIBDECOR_نسخہ_MINOR > y) || \
     (SDL_LIBDECOR_نسخہ_MAJOR == x && SDL_LIBDECOR_نسخہ_MINOR == y && SDL_LIBDECOR_نسخہ_PATCH >= z))
#جے_انت

#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت

خارجي bool SDL_WAYLAND_لدو_Symbols(فراغ);
خارجي فراغ SDL_WAYLAND_UnloadSymbols(فراغ);

#تعریف_کرو SDL_WAYLAND_MODULE(modname) خارجي صحيح SDL_WAYLAND_HAVE_##modname;
#تعریف_کرو SDL_WAYLAND_SYM(rc, fn, params)        \
    تعريفنوع rc(*SDL_DYNWAYLANDFN_##fn) params; \
    خارجي SDL_DYNWAYLANDFN_##fn WAYLAND_##fn;
#تعریف_کرو SDL_WAYLAND_SYM_OPT(rc, fn, params)    \
    تعريفنوع rc(*SDL_DYNWAYLANDFN_##fn) params; \
    خارجي SDL_DYNWAYLANDFN_##fn WAYLAND_##fn;
#تعریف_کرو SDL_WAYLAND_INTERFACE(iface) خارجي ثابت بنية wl_interface *WAYLAND_##iface;
#ضمن "SDL_waylandsym.h"

#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

#إذا defined(_WAYLAND_CLIENT_H) || defined(WAYLAND_CLIENT_H)
#غلطی Do not include wayland-client ahead دا SDL_waylanddyn.h وچ_2 dynamic loading منوال
#جے_انت

/* wayland-client-protocol.h included from wayland-client.h
 * has inline functions that require these to be defined in dynamic loading mode
 */

#تعریف_کرو wl_proxy_create                        (*WAYLAND_wl_proxy_create)
#تعریف_کرو wl_proxy_destroy                       (*WAYLAND_wl_proxy_destroy)
#تعریف_کرو wl_proxy_marshal                       (*WAYLAND_wl_proxy_marshal)
#تعریف_کرو wl_proxy_سیٹ_user_انکڑے                 (*WAYLAND_wl_proxy_سیٹ_user_انکڑے)
#تعریف_کرو wl_proxy_get_user_انکڑے                 (*WAYLAND_wl_proxy_get_user_انکڑے)
#تعریف_کرو wl_proxy_get_نسخہ                   (*WAYLAND_wl_proxy_get_نسخہ)
#تعریف_کرو wl_proxy_جوڑو_listener                  (*WAYLAND_wl_proxy_جوڑو_listener)
#تعریف_کرو wl_proxy_marshal_constructor           (*WAYLAND_wl_proxy_marshal_constructor)
#تعریف_کرو wl_proxy_marshal_constructor_versioned (*WAYLAND_wl_proxy_marshal_constructor_versioned)
#تعریف_کرو wl_proxy_سیٹ_ٹیگ                       (*WAYLAND_wl_proxy_سیٹ_ٹیگ)
#تعریف_کرو wl_proxy_get_ٹیگ                       (*WAYLAND_wl_proxy_get_ٹیگ)
#تعریف_کرو wl_proxy_marshal_flags                 (*WAYLAND_wl_proxy_marshal_flags)
#تعریف_کرو wl_proxy_marshal_array_flags           (*WAYLAND_wl_proxy_marshal_array_flags)
#تعریف_کرو wl_display_reconnect                   (*WAYLAND_wl_display_reconnect)

/*
 * These must be included before libdecor.h, otherwise the libdecor header
 * pulls in the system Wayland protocol headers instead of ours.
 */
#ضمن "wayland-client-protocol.h"
#ضمن "wayland-egl.h"

#جے_تعریف_شدہ HAVE_LIBDECOR_H
// Must be included before our defines
#ضمن <libdecor.h>

#تعریف_کرو libdecor_unref                          (*WAYLAND_libdecor_unref)
#تعریف_کرو libdecor_new                            (*WAYLAND_libdecor_new)
#تعریف_کرو libdecor_decorate                       (*WAYLAND_libdecor_decorate)
#تعریف_کرو libdecor_چوکھٹا_unref                    (*WAYLAND_libdecor_چوکھٹا_unref)
#تعریف_کرو libdecor_چوکھٹا_سیٹ_title                (*WAYLAND_libdecor_چوکھٹا_سیٹ_title)
#تعریف_کرو libdecor_چوکھٹا_سیٹ_app_id               (*WAYLAND_libdecor_چوکھٹا_سیٹ_app_id)
#تعریف_کرو libdecor_چوکھٹا_سیٹ_max_content_ناپ     (*WAYLAND_libdecor_چوکھٹا_سیٹ_max_content_ناپ)
#تعریف_کرو libdecor_چوکھٹا_get_max_content_ناپ     (*WAYLAND_libdecor_چوکھٹا_get_max_content_ناپ)
#تعریف_کرو libdecor_چوکھٹا_سیٹ_min_content_ناپ     (*WAYLAND_libdecor_چوکھٹا_سیٹ_min_content_ناپ)
#تعریف_کرو libdecor_چوکھٹا_get_min_content_ناپ     (*WAYLAND_libdecor_چوکھٹا_get_min_content_ناپ)
#تعریف_کرو libdecor_چوکھٹا_resize                   (*WAYLAND_libdecor_چوکھٹا_resize)
#تعریف_کرو libdecor_چوکھٹا_move                     (*WAYLAND_libdecor_چوکھٹا_move)
#تعریف_کرو libdecor_چوکھٹا_commit                   (*WAYLAND_libdecor_چوکھٹا_commit)
#تعریف_کرو libdecor_چوکھٹا_سیٹ_minimized            (*WAYLAND_libdecor_چوکھٹا_سیٹ_minimized)
#تعریف_کرو libdecor_چوکھٹا_سیٹ_maximized            (*WAYLAND_libdecor_چوکھٹا_سیٹ_maximized)
#تعریف_کرو libdecor_چوکھٹا_unset_maximized          (*WAYLAND_libdecor_چوکھٹا_unset_maximized)
#تعریف_کرو libdecor_چوکھٹا_سیٹ_fullscreen           (*WAYLAND_libdecor_چوکھٹا_سیٹ_fullscreen)
#تعریف_کرو libdecor_چوکھٹا_unset_fullscreen         (*WAYLAND_libdecor_چوکھٹا_unset_fullscreen)
#تعریف_کرو libdecor_چوکھٹا_سیٹ_capabilities         (*WAYLAND_libdecor_چوکھٹا_سیٹ_capabilities)
#تعریف_کرو libdecor_چوکھٹا_unset_capabilities       (*WAYLAND_libdecor_چوکھٹا_unset_capabilities)
#تعریف_کرو libdecor_چوکھٹا_has_capability           (*WAYLAND_libdecor_چوکھٹا_has_capability)
#تعریف_کرو libdecor_چوکھٹا_سیٹ_visibility           (*WAYLAND_libdecor_چوکھٹا_سیٹ_visibility)
#تعریف_کرو libdecor_چوکھٹا_is_visible               (*WAYLAND_libdecor_چوکھٹا_is_visible)
#تعریف_کرو libdecor_چوکھٹا_is_floating              (*WAYLAND_libdecor_چوکھٹا_is_floating)
#تعریف_کرو libdecor_چوکھٹا_سیٹ_ماپا               (*WAYLAND_libdecor_چوکھٹا_سیٹ_ماپا)
#تعریف_کرو libdecor_چوکھٹا_show_کھڑکی_menu         (*WAYLAND_libdecor_چوکھٹا_show_کھڑکی_menu)
#تعریف_کرو libdecor_چوکھٹا_get_wm_capabilities      (*WAYLAND_libdecor_چوکھٹا_get_wm_capabilities)
#تعریف_کرو libdecor_چوکھٹا_get_xdg_surface          (*WAYLAND_libdecor_چوکھٹا_get_xdg_surface)
#تعریف_کرو libdecor_چوکھٹا_get_xdg_toplevel         (*WAYLAND_libdecor_چوکھٹا_get_xdg_toplevel)
#تعریف_کرو libdecor_چوکھٹا_translate_coordinate     (*WAYLAND_libdecor_چوکھٹا_translate_coordinate)
#تعریف_کرو libdecor_چوکھٹا_map                      (*WAYLAND_libdecor_چوکھٹا_map)
#تعریف_کرو libdecor_state_new                      (*WAYLAND_libdecor_state_new)
#تعریف_کرو libdecor_state_free                     (*WAYLAND_libdecor_state_free)
#تعریف_کرو libdecor_configuration_get_content_ناپ (*WAYLAND_libdecor_configuration_get_content_ناپ)
#تعریف_کرو libdecor_configuration_get_کھڑکی_state (*WAYLAND_libdecor_configuration_get_کھڑکی_state)
#تعریف_کرو libdecor_dispatch                       (*WAYLAND_libdecor_dispatch)
#جے_انت

#وإلا // SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

/*
 * These must be included before libdecor.h, otherwise the libdecor header
 * pulls in the system Wayland protocol headers instead of ours.
 */
#ضمن "wayland-client-protocol.h"
#ضمن "wayland-egl.h"

#جے_تعریف_شدہ HAVE_LIBDECOR_H
#ضمن <libdecor.h>
#جے_انت

#جے_انت // SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

#جے_انت // SDL_waylanddyn_h_
