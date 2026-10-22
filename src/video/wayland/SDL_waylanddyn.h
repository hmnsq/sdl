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
#నిర్వచితం_కాకపోతే SDL_waylanddyn_h_
#నిర్వచించు SDL_waylanddyn_h_

#అన్తర్భావ "SDL_internal.h"

/* We can't include wayland-client.h here
 * but we need some structs from it
 */
నిర్మాణం wl_interface;
నిర్మాణం wl_proxy;
నిర్మాణం wl_event_వరుస;
నిర్మాణం wl_display;
నిర్మాణం wl_surface;
నిర్మాణం wl_shm;

// We also need some for libdecor
నిర్మాణం wl_seat;
నిర్మాణం wl_output;
నిర్మాణం libdecor;
నిర్మాణం libdecor_చట్రం;
నిర్మాణం libdecor_state;
నిర్మాణం libdecor_configuration;
నిర్మాణం libdecor_interface;
నిర్మాణం libdecor_చట్రం_interface;
గణన libdecor_resize_అంచు;
గణన libdecor_capabilities;
గణన libdecor_కిటికీ_state;

#అన్తర్భావ "wayland-cursor.h"
#అన్తర్భావ "wayland-util.h"
#అన్తర్భావ "xkbcommon/xkbcommon.h"
#అన్తర్భావ "xkbcommon/xkbcommon-compose.h"

// Must be included before our #defines, see Bugzilla #4957
#అన్తర్భావ "wayland-client-core.h"

#నిర్వచించు SDL_WAYLAND_CHECK_సంస్కరణ(x, y, z)                        \
    (WAYLAND_సంస్కరణ_MAJOR > x ||                                 \
     (WAYLAND_సంస్కరణ_MAJOR == x && WAYLAND_సంస్కరణ_MINOR > y) || \
     (WAYLAND_సంస్కరణ_MAJOR == x && WAYLAND_సంస్కరణ_MINOR == y && WAYLAND_సంస్కరణ_MICRO >= z))

#నిర్వచించు SDL_XKBCOMMON_CHECK_సంస్కరణ(x, y, z)                                  \
    (SDL_XKBCOMMON_సంస్కరణ_MAJOR > x ||                                       \
     (SDL_XKBCOMMON_సంస్కరణ_MAJOR == x && SDL_XKBCOMMON_సంస్కరణ_MINOR > y) || \
     (SDL_XKBCOMMON_సంస్కరణ_MAJOR == x && SDL_XKBCOMMON_సంస్కరణ_MINOR == y && SDL_XKBCOMMON_సంస్కరణ_PATCH >= z))

#నిర్వచితమైతే HAVE_LIBDECOR_H
#నిర్వచించు SDL_LIBDECOR_CHECK_సంస్కరణ(x, y, z)                                 \
    (SDL_LIBDECOR_సంస్కరణ_MAJOR > x ||                                      \
     (SDL_LIBDECOR_సంస్కరణ_MAJOR == x && SDL_LIBDECOR_సంస్కరణ_MINOR > y) || \
     (SDL_LIBDECOR_సంస్కరణ_MAJOR == x && SDL_LIBDECOR_సంస్కరణ_MINOR == y && SDL_LIBDECOR_సంస్కరణ_PATCH >= z))
#అయితే_ముగింపు

#నిర్వచితమైతే __cplusplus
బాహ్య "C" {
#అయితే_ముగింపు

బాహ్య bool SDL_WAYLAND_ఎక్కించు_Symbols(శూన్య);
బాహ్య శూన్య SDL_WAYLAND_UnloadSymbols(శూన్య);

#నిర్వచించు SDL_WAYLAND_MODULE(modname) బాహ్య పూర్ణాంకం SDL_WAYLAND_HAVE_##modname;
#నిర్వచించు SDL_WAYLAND_SYM(rc, fn, params)        \
    రకనిర్వచనం rc(*SDL_DYNWAYLANDFN_##fn) params; \
    బాహ్య SDL_DYNWAYLANDFN_##fn WAYLAND_##fn;
#నిర్వచించు SDL_WAYLAND_SYM_OPT(rc, fn, params)    \
    రకనిర్వచనం rc(*SDL_DYNWAYLANDFN_##fn) params; \
    బాహ్య SDL_DYNWAYLANDFN_##fn WAYLAND_##fn;
#నిర్వచించు SDL_WAYLAND_INTERFACE(iface) బాహ్య స్థిరరాశి నిర్మాణం wl_interface *WAYLAND_##iface;
#అన్తర్భావ "SDL_waylandsym.h"

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

#ఒకవేళ defined(_WAYLAND_CLIENT_H) || defined(WAYLAND_CLIENT_H)
#దోషం Do not include wayland-client ahead యొక్క SDL_waylanddyn.h లోపల_2 dynamic loading బహుళకం
#అయితే_ముగింపు

/* wayland-client-protocol.h included from wayland-client.h
 * has inline functions that require these to be defined in dynamic loading mode
 */

#నిర్వచించు wl_proxy_create                        (*WAYLAND_wl_proxy_create)
#నిర్వచించు wl_proxy_destroy                       (*WAYLAND_wl_proxy_destroy)
#నిర్వచించు wl_proxy_marshal                       (*WAYLAND_wl_proxy_marshal)
#నిర్వచించు wl_proxy_సమితి_user_దత్తాంశం                 (*WAYLAND_wl_proxy_సమితి_user_దత్తాంశం)
#నిర్వచించు wl_proxy_get_user_దత్తాంశం                 (*WAYLAND_wl_proxy_get_user_దత్తాంశం)
#నిర్వచించు wl_proxy_get_సంస్కరణ                   (*WAYLAND_wl_proxy_get_సంస్కరణ)
#నిర్వచించు wl_proxy_కూడు_listener                  (*WAYLAND_wl_proxy_కూడు_listener)
#నిర్వచించు wl_proxy_marshal_constructor           (*WAYLAND_wl_proxy_marshal_constructor)
#నిర్వచించు wl_proxy_marshal_constructor_versioned (*WAYLAND_wl_proxy_marshal_constructor_versioned)
#నిర్వచించు wl_proxy_సమితి_ట్యాగ్                       (*WAYLAND_wl_proxy_సమితి_ట్యాగ్)
#నిర్వచించు wl_proxy_get_ట్యాగ్                       (*WAYLAND_wl_proxy_get_ట్యాగ్)
#నిర్వచించు wl_proxy_marshal_flags                 (*WAYLAND_wl_proxy_marshal_flags)
#నిర్వచించు wl_proxy_marshal_array_flags           (*WAYLAND_wl_proxy_marshal_array_flags)
#నిర్వచించు wl_display_reconnect                   (*WAYLAND_wl_display_reconnect)

/*
 * These must be included before libdecor.h, otherwise the libdecor header
 * pulls in the system Wayland protocol headers instead of ours.
 */
#అన్తర్భావ "wayland-client-protocol.h"
#అన్తర్భావ "wayland-egl.h"

#నిర్వచితమైతే HAVE_LIBDECOR_H
// Must be included before our defines
#అన్తర్భావ <libdecor.h>

#నిర్వచించు libdecor_unref                          (*WAYLAND_libdecor_unref)
#నిర్వచించు libdecor_new                            (*WAYLAND_libdecor_new)
#నిర్వచించు libdecor_decorate                       (*WAYLAND_libdecor_decorate)
#నిర్వచించు libdecor_చట్రం_unref                    (*WAYLAND_libdecor_చట్రం_unref)
#నిర్వచించు libdecor_చట్రం_సమితి_title                (*WAYLAND_libdecor_చట్రం_సమితి_title)
#నిర్వచించు libdecor_చట్రం_సమితి_app_id               (*WAYLAND_libdecor_చట్రం_సమితి_app_id)
#నిర్వచించు libdecor_చట్రం_సమితి_max_content_కొలత     (*WAYLAND_libdecor_చట్రం_సమితి_max_content_కొలత)
#నిర్వచించు libdecor_చట్రం_get_max_content_కొలత     (*WAYLAND_libdecor_చట్రం_get_max_content_కొలత)
#నిర్వచించు libdecor_చట్రం_సమితి_min_content_కొలత     (*WAYLAND_libdecor_చట్రం_సమితి_min_content_కొలత)
#నిర్వచించు libdecor_చట్రం_get_min_content_కొలత     (*WAYLAND_libdecor_చట్రం_get_min_content_కొలత)
#నిర్వచించు libdecor_చట్రం_resize                   (*WAYLAND_libdecor_చట్రం_resize)
#నిర్వచించు libdecor_చట్రం_move                     (*WAYLAND_libdecor_చట్రం_move)
#నిర్వచించు libdecor_చట్రం_commit                   (*WAYLAND_libdecor_చట్రం_commit)
#నిర్వచించు libdecor_చట్రం_సమితి_minimized            (*WAYLAND_libdecor_చట్రం_సమితి_minimized)
#నిర్వచించు libdecor_చట్రం_సమితి_maximized            (*WAYLAND_libdecor_చట్రం_సమితి_maximized)
#నిర్వచించు libdecor_చట్రం_unset_maximized          (*WAYLAND_libdecor_చట్రం_unset_maximized)
#నిర్వచించు libdecor_చట్రం_సమితి_fullscreen           (*WAYLAND_libdecor_చట్రం_సమితి_fullscreen)
#నిర్వచించు libdecor_చట్రం_unset_fullscreen         (*WAYLAND_libdecor_చట్రం_unset_fullscreen)
#నిర్వచించు libdecor_చట్రం_సమితి_capabilities         (*WAYLAND_libdecor_చట్రం_సమితి_capabilities)
#నిర్వచించు libdecor_చట్రం_unset_capabilities       (*WAYLAND_libdecor_చట్రం_unset_capabilities)
#నిర్వచించు libdecor_చట్రం_has_capability           (*WAYLAND_libdecor_చట్రం_has_capability)
#నిర్వచించు libdecor_చట్రం_సమితి_visibility           (*WAYLAND_libdecor_చట్రం_సమితి_visibility)
#నిర్వచించు libdecor_చట్రం_is_visible               (*WAYLAND_libdecor_చట్రం_is_visible)
#నిర్వచించు libdecor_చట్రం_is_floating              (*WAYLAND_libdecor_చట్రం_is_floating)
#నిర్వచించు libdecor_చట్రం_సమితి_మాతృ               (*WAYLAND_libdecor_చట్రం_సమితి_మాతృ)
#నిర్వచించు libdecor_చట్రం_show_కిటికీ_menu         (*WAYLAND_libdecor_చట్రం_show_కిటికీ_menu)
#నిర్వచించు libdecor_చట్రం_get_wm_capabilities      (*WAYLAND_libdecor_చట్రం_get_wm_capabilities)
#నిర్వచించు libdecor_చట్రం_get_xdg_surface          (*WAYLAND_libdecor_చట్రం_get_xdg_surface)
#నిర్వచించు libdecor_చట్రం_get_xdg_toplevel         (*WAYLAND_libdecor_చట్రం_get_xdg_toplevel)
#నిర్వచించు libdecor_చట్రం_translate_coordinate     (*WAYLAND_libdecor_చట్రం_translate_coordinate)
#నిర్వచించు libdecor_చట్రం_map                      (*WAYLAND_libdecor_చట్రం_map)
#నిర్వచించు libdecor_state_new                      (*WAYLAND_libdecor_state_new)
#నిర్వచించు libdecor_state_free                     (*WAYLAND_libdecor_state_free)
#నిర్వచించు libdecor_configuration_get_content_కొలత (*WAYLAND_libdecor_configuration_get_content_కొలత)
#నిర్వచించు libdecor_configuration_get_కిటికీ_state (*WAYLAND_libdecor_configuration_get_కిటికీ_state)
#నిర్వచించు libdecor_dispatch                       (*WAYLAND_libdecor_dispatch)
#అయితే_ముగింపు

#లేకపోతే // SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

/*
 * These must be included before libdecor.h, otherwise the libdecor header
 * pulls in the system Wayland protocol headers instead of ours.
 */
#అన్తర్భావ "wayland-client-protocol.h"
#అన్తర్భావ "wayland-egl.h"

#నిర్వచితమైతే HAVE_LIBDECOR_H
#అన్తర్భావ <libdecor.h>
#అయితే_ముగింపు

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

#అయితే_ముగింపు // SDL_waylanddyn_h_
