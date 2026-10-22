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
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_waylanddyn_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_waylanddyn_h_

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

/* We can't include wayland-client.h here
 * but we need some structs from it
 */
ರಚನೆ wl_interface;
ರಚನೆ wl_proxy;
ರಚನೆ wl_event_ಸರತಿ;
ರಚನೆ wl_display;
ರಚನೆ wl_surface;
ರಚನೆ wl_shm;

// We also need some for libdecor
ರಚನೆ wl_seat;
ರಚನೆ wl_output;
ರಚನೆ libdecor;
ರಚನೆ libdecor_ಚೌಕಟ್ಟು;
ರಚನೆ libdecor_state;
ರಚನೆ libdecor_configuration;
ರಚನೆ libdecor_interface;
ರಚನೆ libdecor_ಚೌಕಟ್ಟು_interface;
ಎಣಿಕೆ libdecor_resize_ಅಂಚು;
ಎಣಿಕೆ libdecor_capabilities;
ಎಣಿಕೆ libdecor_ಕಿಟಕಿ_state;

#ಅನ್ತರ್ಭಾವ "wayland-cursor.h"
#ಅನ್ತರ್ಭಾವ "wayland-util.h"
#ಅನ್ತರ್ಭಾವ "xkbcommon/xkbcommon.h"
#ಅನ್ತರ್ಭಾವ "xkbcommon/xkbcommon-compose.h"

// Must be included before our #defines, see Bugzilla #4957
#ಅನ್ತರ್ಭಾವ "wayland-client-core.h"

#ವ್ಯಾಖ್ಯಾನಿಸು SDL_WAYLAND_CHECK_ಆವೃತ್ತಿ(x, y, z)                        \
    (WAYLAND_ಆವೃತ್ತಿ_MAJOR > x ||                                 \
     (WAYLAND_ಆವೃತ್ತಿ_MAJOR == x && WAYLAND_ಆವೃತ್ತಿ_MINOR > y) || \
     (WAYLAND_ಆವೃತ್ತಿ_MAJOR == x && WAYLAND_ಆವೃತ್ತಿ_MINOR == y && WAYLAND_ಆವೃತ್ತಿ_MICRO >= z))

#ವ್ಯಾಖ್ಯಾನಿಸು SDL_XKBCOMMON_CHECK_ಆವೃತ್ತಿ(x, y, z)                                  \
    (SDL_XKBCOMMON_ಆವೃತ್ತಿ_MAJOR > x ||                                       \
     (SDL_XKBCOMMON_ಆವೃತ್ತಿ_MAJOR == x && SDL_XKBCOMMON_ಆವೃತ್ತಿ_MINOR > y) || \
     (SDL_XKBCOMMON_ಆವೃತ್ತಿ_MAJOR == x && SDL_XKBCOMMON_ಆವೃತ್ತಿ_MINOR == y && SDL_XKBCOMMON_ಆವೃತ್ತಿ_PATCH >= z))

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_LIBDECOR_CHECK_ಆವೃತ್ತಿ(x, y, z)                                 \
    (SDL_LIBDECOR_ಆವೃತ್ತಿ_MAJOR > x ||                                      \
     (SDL_LIBDECOR_ಆವೃತ್ತಿ_MAJOR == x && SDL_LIBDECOR_ಆವೃತ್ತಿ_MINOR > y) || \
     (SDL_LIBDECOR_ಆವೃತ್ತಿ_MAJOR == x && SDL_LIBDECOR_ಆವೃತ್ತಿ_MINOR == y && SDL_LIBDECOR_ಆವೃತ್ತಿ_PATCH >= z))
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ

ಬಾಹ್ಯ bool SDL_WAYLAND_ತುಂಬು_Symbols(ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_WAYLAND_UnloadSymbols(ಶೂನ್ಯ);

#ವ್ಯಾಖ್ಯಾನಿಸು SDL_WAYLAND_MODULE(modname) ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ SDL_WAYLAND_HAVE_##modname;
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_WAYLAND_SYM(rc, fn, params)        \
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ rc(*SDL_DYNWAYLANDFN_##fn) params; \
    ಬಾಹ್ಯ SDL_DYNWAYLANDFN_##fn WAYLAND_##fn;
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_WAYLAND_SYM_OPT(rc, fn, params)    \
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ rc(*SDL_DYNWAYLANDFN_##fn) params; \
    ಬಾಹ್ಯ SDL_DYNWAYLANDFN_##fn WAYLAND_##fn;
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_WAYLAND_INTERFACE(iface) ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ ರಚನೆ wl_interface *WAYLAND_##iface;
#ಅನ್ತರ್ಭಾವ "SDL_waylandsym.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

#ಆದರೆ defined(_WAYLAND_CLIENT_H) || defined(WAYLAND_CLIENT_H)
#ದೋಷ Do not include wayland-client ahead ದ SDL_waylanddyn.h ಒಳ_2 dynamic loading ಬಹುಲಕ
#ಆದರೆ_ಅಂತ್ಯ

/* wayland-client-protocol.h included from wayland-client.h
 * has inline functions that require these to be defined in dynamic loading mode
 */

#ವ್ಯಾಖ್ಯಾನಿಸು wl_proxy_create                        (*WAYLAND_wl_proxy_create)
#ವ್ಯಾಖ್ಯಾನಿಸು wl_proxy_destroy                       (*WAYLAND_wl_proxy_destroy)
#ವ್ಯಾಖ್ಯಾನಿಸು wl_proxy_marshal                       (*WAYLAND_wl_proxy_marshal)
#ವ್ಯಾಖ್ಯಾನಿಸು wl_proxy_ಗಣ_user_ದತ್ತಾಂಶ                 (*WAYLAND_wl_proxy_ಗಣ_user_ದತ್ತಾಂಶ)
#ವ್ಯಾಖ್ಯಾನಿಸು wl_proxy_get_user_ದತ್ತಾಂಶ                 (*WAYLAND_wl_proxy_get_user_ದತ್ತಾಂಶ)
#ವ್ಯಾಖ್ಯಾನಿಸು wl_proxy_get_ಆವೃತ್ತಿ                   (*WAYLAND_wl_proxy_get_ಆವೃತ್ತಿ)
#ವ್ಯಾಖ್ಯಾನಿಸು wl_proxy_ಕೂಡಿಸು_listener                  (*WAYLAND_wl_proxy_ಕೂಡಿಸು_listener)
#ವ್ಯಾಖ್ಯಾನಿಸು wl_proxy_marshal_constructor           (*WAYLAND_wl_proxy_marshal_constructor)
#ವ್ಯಾಖ್ಯಾನಿಸು wl_proxy_marshal_constructor_versioned (*WAYLAND_wl_proxy_marshal_constructor_versioned)
#ವ್ಯಾಖ್ಯಾನಿಸು wl_proxy_ಗಣ_ಟ್ಯಾಗ್                       (*WAYLAND_wl_proxy_ಗಣ_ಟ್ಯಾಗ್)
#ವ್ಯಾಖ್ಯಾನಿಸು wl_proxy_get_ಟ್ಯಾಗ್                       (*WAYLAND_wl_proxy_get_ಟ್ಯಾಗ್)
#ವ್ಯಾಖ್ಯಾನಿಸು wl_proxy_marshal_flags                 (*WAYLAND_wl_proxy_marshal_flags)
#ವ್ಯಾಖ್ಯಾನಿಸು wl_proxy_marshal_array_flags           (*WAYLAND_wl_proxy_marshal_array_flags)
#ವ್ಯಾಖ್ಯಾನಿಸು wl_display_reconnect                   (*WAYLAND_wl_display_reconnect)

/*
 * These must be included before libdecor.h, otherwise the libdecor header
 * pulls in the system Wayland protocol headers instead of ours.
 */
#ಅನ್ತರ್ಭಾವ "wayland-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "wayland-egl.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
// Must be included before our defines
#ಅನ್ತರ್ಭಾವ <libdecor.h>

#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_unref                          (*WAYLAND_libdecor_unref)
#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_new                            (*WAYLAND_libdecor_new)
#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_decorate                       (*WAYLAND_libdecor_decorate)
#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_ಚೌಕಟ್ಟು_unref                    (*WAYLAND_libdecor_ಚೌಕಟ್ಟು_unref)
#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_ಚೌಕಟ್ಟು_ಗಣ_title                (*WAYLAND_libdecor_ಚೌಕಟ್ಟು_ಗಣ_title)
#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_ಚೌಕಟ್ಟು_ಗಣ_app_id               (*WAYLAND_libdecor_ಚೌಕಟ್ಟು_ಗಣ_app_id)
#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_ಚೌಕಟ್ಟು_ಗಣ_max_content_ಗಾತ್ರ     (*WAYLAND_libdecor_ಚೌಕಟ್ಟು_ಗಣ_max_content_ಗಾತ್ರ)
#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_ಚೌಕಟ್ಟು_get_max_content_ಗಾತ್ರ     (*WAYLAND_libdecor_ಚೌಕಟ್ಟು_get_max_content_ಗಾತ್ರ)
#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_ಚೌಕಟ್ಟು_ಗಣ_min_content_ಗಾತ್ರ     (*WAYLAND_libdecor_ಚೌಕಟ್ಟು_ಗಣ_min_content_ಗಾತ್ರ)
#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_ಚೌಕಟ್ಟು_get_min_content_ಗಾತ್ರ     (*WAYLAND_libdecor_ಚೌಕಟ್ಟು_get_min_content_ಗಾತ್ರ)
#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_ಚೌಕಟ್ಟು_resize                   (*WAYLAND_libdecor_ಚೌಕಟ್ಟು_resize)
#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_ಚೌಕಟ್ಟು_move                     (*WAYLAND_libdecor_ಚೌಕಟ್ಟು_move)
#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_ಚೌಕಟ್ಟು_commit                   (*WAYLAND_libdecor_ಚೌಕಟ್ಟು_commit)
#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_ಚೌಕಟ್ಟು_ಗಣ_minimized            (*WAYLAND_libdecor_ಚೌಕಟ್ಟು_ಗಣ_minimized)
#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_ಚೌಕಟ್ಟು_ಗಣ_maximized            (*WAYLAND_libdecor_ಚೌಕಟ್ಟು_ಗಣ_maximized)
#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_ಚೌಕಟ್ಟು_unset_maximized          (*WAYLAND_libdecor_ಚೌಕಟ್ಟು_unset_maximized)
#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_ಚೌಕಟ್ಟು_ಗಣ_fullscreen           (*WAYLAND_libdecor_ಚೌಕಟ್ಟು_ಗಣ_fullscreen)
#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_ಚೌಕಟ್ಟು_unset_fullscreen         (*WAYLAND_libdecor_ಚೌಕಟ್ಟು_unset_fullscreen)
#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_ಚೌಕಟ್ಟು_ಗಣ_capabilities         (*WAYLAND_libdecor_ಚೌಕಟ್ಟು_ಗಣ_capabilities)
#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_ಚೌಕಟ್ಟು_unset_capabilities       (*WAYLAND_libdecor_ಚೌಕಟ್ಟು_unset_capabilities)
#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_ಚೌಕಟ್ಟು_has_capability           (*WAYLAND_libdecor_ಚೌಕಟ್ಟು_has_capability)
#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_ಚೌಕಟ್ಟು_ಗಣ_visibility           (*WAYLAND_libdecor_ಚೌಕಟ್ಟು_ಗಣ_visibility)
#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_ಚೌಕಟ್ಟು_is_visible               (*WAYLAND_libdecor_ಚೌಕಟ್ಟು_is_visible)
#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_ಚೌಕಟ್ಟು_is_floating              (*WAYLAND_libdecor_ಚೌಕಟ್ಟು_is_floating)
#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_ಚೌಕಟ್ಟು_ಗಣ_ಪೋಷಕ               (*WAYLAND_libdecor_ಚೌಕಟ್ಟು_ಗಣ_ಪೋಷಕ)
#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_ಚೌಕಟ್ಟು_show_ಕಿಟಕಿ_menu         (*WAYLAND_libdecor_ಚೌಕಟ್ಟು_show_ಕಿಟಕಿ_menu)
#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_ಚೌಕಟ್ಟು_get_wm_capabilities      (*WAYLAND_libdecor_ಚೌಕಟ್ಟು_get_wm_capabilities)
#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_ಚೌಕಟ್ಟು_get_xdg_surface          (*WAYLAND_libdecor_ಚೌಕಟ್ಟು_get_xdg_surface)
#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_ಚೌಕಟ್ಟು_get_xdg_toplevel         (*WAYLAND_libdecor_ಚೌಕಟ್ಟು_get_xdg_toplevel)
#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_ಚೌಕಟ್ಟು_translate_coordinate     (*WAYLAND_libdecor_ಚೌಕಟ್ಟು_translate_coordinate)
#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_ಚೌಕಟ್ಟು_map                      (*WAYLAND_libdecor_ಚೌಕಟ್ಟು_map)
#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_state_new                      (*WAYLAND_libdecor_state_new)
#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_state_free                     (*WAYLAND_libdecor_state_free)
#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_configuration_get_content_ಗಾತ್ರ (*WAYLAND_libdecor_configuration_get_content_ಗಾತ್ರ)
#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_configuration_get_ಕಿಟಕಿ_state (*WAYLAND_libdecor_configuration_get_ಕಿಟಕಿ_state)
#ವ್ಯಾಖ್ಯಾನಿಸು libdecor_dispatch                       (*WAYLAND_libdecor_dispatch)
#ಆದರೆ_ಅಂತ್ಯ

#ಇಲ್ಲದಿದ್ದರೆ // SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

/*
 * These must be included before libdecor.h, otherwise the libdecor header
 * pulls in the system Wayland protocol headers instead of ours.
 */
#ಅನ್ತರ್ಭಾವ "wayland-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "wayland-egl.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
#ಅನ್ತರ್ಭಾವ <libdecor.h>
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

#ಆದರೆ_ಅಂತ್ಯ // SDL_waylanddyn_h_
