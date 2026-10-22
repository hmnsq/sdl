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
#اگر_غیر_تعریف_شدہ SDL_waylanddyn_h_
#تعریف_کرو SDL_waylanddyn_h_

#شامل "SDL_internal.h"

/* We can't include wayland-client.h here
 * but we need some structs from it
 */
ساخت wl_interface;
ساخت wl_proxy;
ساخت wl_event_قطار;
ساخت wl_display;
ساخت wl_surface;
ساخت wl_shm;

// We also need some for libdecor
ساخت wl_seat;
ساخت wl_output;
ساخت libdecor;
ساخت libdecor_چوکھٹا;
ساخت libdecor_state;
ساخت libdecor_configuration;
ساخت libdecor_interface;
ساخت libdecor_چوکھٹا_interface;
شمار libdecor_resize_کنارہ;
شمار libdecor_capabilities;
شمار libdecor_کھڑکی_state;

#شامل "wayland-cursor.h"
#شامل "wayland-util.h"
#شامل "xkbcommon/xkbcommon.h"
#شامل "xkbcommon/xkbcommon-compose.h"

// Must be included before our #defines, see Bugzilla #4957
#شامل "wayland-client-core.h"

#تعریف_کرو SDL_WAYLAND_CHECK_نسخہ(x, y, z)                        \
    (WAYLAND_نسخہ_MAJOR > x ||                                 \
     (WAYLAND_نسخہ_MAJOR == x && WAYLAND_نسخہ_MINOR > y) || \
     (WAYLAND_نسخہ_MAJOR == x && WAYLAND_نسخہ_MINOR == y && WAYLAND_نسخہ_MICRO >= z))

#تعریف_کرو SDL_XKBCOMMON_CHECK_نسخہ(x, y, z)                                  \
    (SDL_XKBCOMMON_نسخہ_MAJOR > x ||                                       \
     (SDL_XKBCOMMON_نسخہ_MAJOR == x && SDL_XKBCOMMON_نسخہ_MINOR > y) || \
     (SDL_XKBCOMMON_نسخہ_MAJOR == x && SDL_XKBCOMMON_نسخہ_MINOR == y && SDL_XKBCOMMON_نسخہ_PATCH >= z))

#اگر_تعریف_شدہ HAVE_LIBDECOR_H
#تعریف_کرو SDL_LIBDECOR_CHECK_نسخہ(x, y, z)                                 \
    (SDL_LIBDECOR_نسخہ_MAJOR > x ||                                      \
     (SDL_LIBDECOR_نسخہ_MAJOR == x && SDL_LIBDECOR_نسخہ_MINOR > y) || \
     (SDL_LIBDECOR_نسخہ_MAJOR == x && SDL_LIBDECOR_نسخہ_MINOR == y && SDL_LIBDECOR_نسخہ_PATCH >= z))
#اگر_ختم

#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم

خارجی bool SDL_WAYLAND_بھرو_Symbols(خالی);
خارجی خالی SDL_WAYLAND_UnloadSymbols(خالی);

#تعریف_کرو SDL_WAYLAND_MODULE(modname) خارجی صحیح SDL_WAYLAND_HAVE_##modname;
#تعریف_کرو SDL_WAYLAND_SYM(rc, fn, params)        \
    قسمتعریف rc(*SDL_DYNWAYLANDFN_##fn) params; \
    خارجی SDL_DYNWAYLANDFN_##fn WAYLAND_##fn;
#تعریف_کرو SDL_WAYLAND_SYM_OPT(rc, fn, params)    \
    قسمتعریف rc(*SDL_DYNWAYLANDFN_##fn) params; \
    خارجی SDL_DYNWAYLANDFN_##fn WAYLAND_##fn;
#تعریف_کرو SDL_WAYLAND_INTERFACE(iface) خارجی ثابت ساخت wl_interface *WAYLAND_##iface;
#شامل "SDL_waylandsym.h"

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

#اگر defined(_WAYLAND_CLIENT_H) || defined(WAYLAND_CLIENT_H)
#غلطی Do not include wayland-client ahead کا SDL_waylanddyn.h اندر_2 dynamic loading منوال
#اگر_ختم

/* wayland-client-protocol.h included from wayland-client.h
 * has inline functions that require these to be defined in dynamic loading mode
 */

#تعریف_کرو wl_proxy_create                        (*WAYLAND_wl_proxy_create)
#تعریف_کرو wl_proxy_destroy                       (*WAYLAND_wl_proxy_destroy)
#تعریف_کرو wl_proxy_marshal                       (*WAYLAND_wl_proxy_marshal)
#تعریف_کرو wl_proxy_سیٹ_user_ڈیٹا                 (*WAYLAND_wl_proxy_سیٹ_user_ڈیٹا)
#تعریف_کرو wl_proxy_get_user_ڈیٹا                 (*WAYLAND_wl_proxy_get_user_ڈیٹا)
#تعریف_کرو wl_proxy_get_نسخہ                   (*WAYLAND_wl_proxy_get_نسخہ)
#تعریف_کرو wl_proxy_جوڑو_listener                  (*WAYLAND_wl_proxy_جوڑو_listener)
#تعریف_کرو wl_proxy_marshal_constructor           (*WAYLAND_wl_proxy_marshal_constructor)
#تعریف_کرو wl_proxy_marshal_constructor_versioned (*WAYLAND_wl_proxy_marshal_constructor_versioned)
#تعریف_کرو wl_proxy_سیٹ_لیبل                       (*WAYLAND_wl_proxy_سیٹ_لیبل)
#تعریف_کرو wl_proxy_get_لیبل                       (*WAYLAND_wl_proxy_get_لیبل)
#تعریف_کرو wl_proxy_marshal_flags                 (*WAYLAND_wl_proxy_marshal_flags)
#تعریف_کرو wl_proxy_marshal_array_flags           (*WAYLAND_wl_proxy_marshal_array_flags)
#تعریف_کرو wl_display_reconnect                   (*WAYLAND_wl_display_reconnect)

/*
 * These must be included before libdecor.h, otherwise the libdecor header
 * pulls in the system Wayland protocol headers instead of ours.
 */
#شامل "wayland-client-protocol.h"
#شامل "wayland-egl.h"

#اگر_تعریف_شدہ HAVE_LIBDECOR_H
// Must be included before our defines
#شامل <libdecor.h>

#تعریف_کرو libdecor_unref                          (*WAYLAND_libdecor_unref)
#تعریف_کرو libdecor_new                            (*WAYLAND_libdecor_new)
#تعریف_کرو libdecor_decorate                       (*WAYLAND_libdecor_decorate)
#تعریف_کرو libdecor_چوکھٹا_unref                    (*WAYLAND_libdecor_چوکھٹا_unref)
#تعریف_کرو libdecor_چوکھٹا_سیٹ_title                (*WAYLAND_libdecor_چوکھٹا_سیٹ_title)
#تعریف_کرو libdecor_چوکھٹا_سیٹ_app_id               (*WAYLAND_libdecor_چوکھٹا_سیٹ_app_id)
#تعریف_کرو libdecor_چوکھٹا_سیٹ_max_content_سائز     (*WAYLAND_libdecor_چوکھٹا_سیٹ_max_content_سائز)
#تعریف_کرو libdecor_چوکھٹا_get_max_content_سائز     (*WAYLAND_libdecor_چوکھٹا_get_max_content_سائز)
#تعریف_کرو libdecor_چوکھٹا_سیٹ_min_content_سائز     (*WAYLAND_libdecor_چوکھٹا_سیٹ_min_content_سائز)
#تعریف_کرو libdecor_چوکھٹا_get_min_content_سائز     (*WAYLAND_libdecor_چوکھٹا_get_min_content_سائز)
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
#تعریف_کرو libdecor_چوکھٹا_سیٹ_والد               (*WAYLAND_libdecor_چوکھٹا_سیٹ_والد)
#تعریف_کرو libdecor_چوکھٹا_show_کھڑکی_menu         (*WAYLAND_libdecor_چوکھٹا_show_کھڑکی_menu)
#تعریف_کرو libdecor_چوکھٹا_get_wm_capabilities      (*WAYLAND_libdecor_چوکھٹا_get_wm_capabilities)
#تعریف_کرو libdecor_چوکھٹا_get_xdg_surface          (*WAYLAND_libdecor_چوکھٹا_get_xdg_surface)
#تعریف_کرو libdecor_چوکھٹا_get_xdg_toplevel         (*WAYLAND_libdecor_چوکھٹا_get_xdg_toplevel)
#تعریف_کرو libdecor_چوکھٹا_translate_coordinate     (*WAYLAND_libdecor_چوکھٹا_translate_coordinate)
#تعریف_کرو libdecor_چوکھٹا_map                      (*WAYLAND_libdecor_چوکھٹا_map)
#تعریف_کرو libdecor_state_new                      (*WAYLAND_libdecor_state_new)
#تعریف_کرو libdecor_state_free                     (*WAYLAND_libdecor_state_free)
#تعریف_کرو libdecor_configuration_get_content_سائز (*WAYLAND_libdecor_configuration_get_content_سائز)
#تعریف_کرو libdecor_configuration_get_کھڑکی_state (*WAYLAND_libdecor_configuration_get_کھڑکی_state)
#تعریف_کرو libdecor_dispatch                       (*WAYLAND_libdecor_dispatch)
#اگر_ختم

#ورنہ // SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

/*
 * These must be included before libdecor.h, otherwise the libdecor header
 * pulls in the system Wayland protocol headers instead of ours.
 */
#شامل "wayland-client-protocol.h"
#شامل "wayland-egl.h"

#اگر_تعریف_شدہ HAVE_LIBDECOR_H
#شامل <libdecor.h>
#اگر_ختم

#اگر_ختم // SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

#اگر_ختم // SDL_waylanddyn_h_
