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
#ifndef SDL_waylanddyn_h_
#define SDL_waylanddyn_h_

#அந்தர்பாவ "SDL_internal.h"

/* We can't include wayland-client.h here
 * but we need some structs from it
 */
கட்டமைப்பு wl_interface;
கட்டமைப்பு wl_proxy;
கட்டமைப்பு wl_event_queue;
கட்டமைப்பு wl_display;
கட்டமைப்பு wl_surface;
கட்டமைப்பு wl_shm;

// We also need some for libdecor
கட்டமைப்பு wl_seat;
கட்டமைப்பு wl_output;
கட்டமைப்பு libdecor;
கட்டமைப்பு libdecor_frame;
கட்டமைப்பு libdecor_state;
கட்டமைப்பு libdecor_configuration;
கட்டமைப்பு libdecor_interface;
கட்டமைப்பு libdecor_frame_interface;
எண்ணிக்கை libdecor_resize_edge;
எண்ணிக்கை libdecor_capabilities;
எண்ணிக்கை libdecor_window_state;

#அந்தர்பாவ "wayland-cursor.h"
#அந்தர்பாவ "wayland-util.h"
#அந்தர்பாவ "xkbcommon/xkbcommon.h"
#அந்தர்பாவ "xkbcommon/xkbcommon-compose.h"

// Must be included before our #defines, see Bugzilla #4957
#அந்தர்பாவ "wayland-client-core.h"

#define SDL_WAYLAND_CHECK_VERSION(x, y, z)                        \
    (WAYLAND_VERSION_MAJOR > x ||                                 \
     (WAYLAND_VERSION_MAJOR == x && WAYLAND_VERSION_MINOR > y) || \
     (WAYLAND_VERSION_MAJOR == x && WAYLAND_VERSION_MINOR == y && WAYLAND_VERSION_MICRO >= z))

#define SDL_XKBCOMMON_CHECK_VERSION(x, y, z)                                  \
    (SDL_XKBCOMMON_VERSION_MAJOR > x ||                                       \
     (SDL_XKBCOMMON_VERSION_MAJOR == x && SDL_XKBCOMMON_VERSION_MINOR > y) || \
     (SDL_XKBCOMMON_VERSION_MAJOR == x && SDL_XKBCOMMON_VERSION_MINOR == y && SDL_XKBCOMMON_VERSION_PATCH >= z))

#ifdef HAVE_LIBDECOR_H
#define SDL_LIBDECOR_CHECK_VERSION(x, y, z)                                 \
    (SDL_LIBDECOR_VERSION_MAJOR > x ||                                      \
     (SDL_LIBDECOR_VERSION_MAJOR == x && SDL_LIBDECOR_VERSION_MINOR > y) || \
     (SDL_LIBDECOR_VERSION_MAJOR == x && SDL_LIBDECOR_VERSION_MINOR == y && SDL_LIBDECOR_VERSION_PATCH >= z))
#endif

#ifdef __cplusplus
வெளி "C" {
#endif

வெளி bool SDL_WAYLAND_LoadSymbols(வெறுமை);
வெளி வெறுமை SDL_WAYLAND_UnloadSymbols(வெறுமை);

#define SDL_WAYLAND_MODULE(modname) வெளி முழு SDL_WAYLAND_HAVE_##modname;
#define SDL_WAYLAND_SYM(rc, fn, params)        \
    வகைவரை rc(*SDL_DYNWAYLANDFN_##fn) params; \
    வெளி SDL_DYNWAYLANDFN_##fn WAYLAND_##fn;
#define SDL_WAYLAND_SYM_OPT(rc, fn, params)    \
    வகைவரை rc(*SDL_DYNWAYLANDFN_##fn) params; \
    வெளி SDL_DYNWAYLANDFN_##fn WAYLAND_##fn;
#define SDL_WAYLAND_INTERFACE(iface) வெளி மாறிலி கட்டமைப்பு wl_interface *WAYLAND_##iface;
#அந்தர்பாவ "SDL_waylandsym.h"

#ifdef __cplusplus
}
#endif

#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

#எனில் defined(_WAYLAND_CLIENT_H) || defined(WAYLAND_CLIENT_H)
#error Do not include wayland-client ahead of SDL_waylanddyn.h in dynamic loading mode
#endif

/* wayland-client-protocol.h included from wayland-client.h
 * has inline functions that require these to be defined in dynamic loading mode
 */

#define wl_proxy_create                        (*WAYLAND_wl_proxy_create)
#define wl_proxy_destroy                       (*WAYLAND_wl_proxy_destroy)
#define wl_proxy_marshal                       (*WAYLAND_wl_proxy_marshal)
#define wl_proxy_set_user_data                 (*WAYLAND_wl_proxy_set_user_data)
#define wl_proxy_get_user_data                 (*WAYLAND_wl_proxy_get_user_data)
#define wl_proxy_get_version                   (*WAYLAND_wl_proxy_get_version)
#define wl_proxy_add_listener                  (*WAYLAND_wl_proxy_add_listener)
#define wl_proxy_marshal_constructor           (*WAYLAND_wl_proxy_marshal_constructor)
#define wl_proxy_marshal_constructor_versioned (*WAYLAND_wl_proxy_marshal_constructor_versioned)
#define wl_proxy_set_tag                       (*WAYLAND_wl_proxy_set_tag)
#define wl_proxy_get_tag                       (*WAYLAND_wl_proxy_get_tag)
#define wl_proxy_marshal_flags                 (*WAYLAND_wl_proxy_marshal_flags)
#define wl_proxy_marshal_array_flags           (*WAYLAND_wl_proxy_marshal_array_flags)
#define wl_display_reconnect                   (*WAYLAND_wl_display_reconnect)

/*
 * These must be included before libdecor.h, otherwise the libdecor header
 * pulls in the system Wayland protocol headers instead of ours.
 */
#அந்தர்பாவ "wayland-client-protocol.h"
#அந்தர்பாவ "wayland-egl.h"

#ifdef HAVE_LIBDECOR_H
// Must be included before our defines
#அந்தர்பாவ <libdecor.h>

#define libdecor_unref                          (*WAYLAND_libdecor_unref)
#define libdecor_new                            (*WAYLAND_libdecor_new)
#define libdecor_decorate                       (*WAYLAND_libdecor_decorate)
#define libdecor_frame_unref                    (*WAYLAND_libdecor_frame_unref)
#define libdecor_frame_set_title                (*WAYLAND_libdecor_frame_set_title)
#define libdecor_frame_set_app_id               (*WAYLAND_libdecor_frame_set_app_id)
#define libdecor_frame_set_max_content_size     (*WAYLAND_libdecor_frame_set_max_content_size)
#define libdecor_frame_get_max_content_size     (*WAYLAND_libdecor_frame_get_max_content_size)
#define libdecor_frame_set_min_content_size     (*WAYLAND_libdecor_frame_set_min_content_size)
#define libdecor_frame_get_min_content_size     (*WAYLAND_libdecor_frame_get_min_content_size)
#define libdecor_frame_resize                   (*WAYLAND_libdecor_frame_resize)
#define libdecor_frame_move                     (*WAYLAND_libdecor_frame_move)
#define libdecor_frame_commit                   (*WAYLAND_libdecor_frame_commit)
#define libdecor_frame_set_minimized            (*WAYLAND_libdecor_frame_set_minimized)
#define libdecor_frame_set_maximized            (*WAYLAND_libdecor_frame_set_maximized)
#define libdecor_frame_unset_maximized          (*WAYLAND_libdecor_frame_unset_maximized)
#define libdecor_frame_set_fullscreen           (*WAYLAND_libdecor_frame_set_fullscreen)
#define libdecor_frame_unset_fullscreen         (*WAYLAND_libdecor_frame_unset_fullscreen)
#define libdecor_frame_set_capabilities         (*WAYLAND_libdecor_frame_set_capabilities)
#define libdecor_frame_unset_capabilities       (*WAYLAND_libdecor_frame_unset_capabilities)
#define libdecor_frame_has_capability           (*WAYLAND_libdecor_frame_has_capability)
#define libdecor_frame_set_visibility           (*WAYLAND_libdecor_frame_set_visibility)
#define libdecor_frame_is_visible               (*WAYLAND_libdecor_frame_is_visible)
#define libdecor_frame_is_floating              (*WAYLAND_libdecor_frame_is_floating)
#define libdecor_frame_set_parent               (*WAYLAND_libdecor_frame_set_parent)
#define libdecor_frame_show_window_menu         (*WAYLAND_libdecor_frame_show_window_menu)
#define libdecor_frame_get_wm_capabilities      (*WAYLAND_libdecor_frame_get_wm_capabilities)
#define libdecor_frame_get_xdg_surface          (*WAYLAND_libdecor_frame_get_xdg_surface)
#define libdecor_frame_get_xdg_toplevel         (*WAYLAND_libdecor_frame_get_xdg_toplevel)
#define libdecor_frame_translate_coordinate     (*WAYLAND_libdecor_frame_translate_coordinate)
#define libdecor_frame_map                      (*WAYLAND_libdecor_frame_map)
#define libdecor_state_new                      (*WAYLAND_libdecor_state_new)
#define libdecor_state_free                     (*WAYLAND_libdecor_state_free)
#define libdecor_configuration_get_content_size (*WAYLAND_libdecor_configuration_get_content_size)
#define libdecor_configuration_get_window_state (*WAYLAND_libdecor_configuration_get_window_state)
#define libdecor_dispatch                       (*WAYLAND_libdecor_dispatch)
#endif

#இல்லையெனில் // SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

/*
 * These must be included before libdecor.h, otherwise the libdecor header
 * pulls in the system Wayland protocol headers instead of ours.
 */
#அந்தர்பாவ "wayland-client-protocol.h"
#அந்தர்பாவ "wayland-egl.h"

#ifdef HAVE_LIBDECOR_H
#அந்தர்பாவ <libdecor.h>
#endif

#endif // SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

#endif // SDL_waylanddyn_h_
