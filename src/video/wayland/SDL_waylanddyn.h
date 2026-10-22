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
#यदि_अपरिभाषितम् SDL_waylanddyn_h_
#परिभाषय SDL_waylanddyn_h_

#अन्तर्भाव "SDL_internal.h"

/* We can't include wayland-client.h here
 * but we need some structs from it
 */
संरचना wl_interface;
संरचना wl_proxy;
संरचना wl_event_queue;
संरचना wl_display;
संरचना wl_surface;
संरचना wl_shm;

// We also need some for libdecor
संरचना wl_seat;
संरचना wl_output;
संरचना libdecor;
संरचना libdecor_frame;
संरचना libdecor_state;
संरचना libdecor_configuration;
संरचना libdecor_interface;
संरचना libdecor_frame_interface;
गणना libdecor_resize_edge;
गणना libdecor_capabilities;
गणना libdecor_गवाक्षः_state;

#अन्तर्भाव "wayland-cursor.h"
#अन्तर्भाव "wayland-util.h"
#अन्तर्भाव "xkbcommon/xkbcommon.h"
#अन्तर्भाव "xkbcommon/xkbcommon-compose.h"

// Must be included before our #defines, see Bugzilla #4957
#अन्तर्भाव "wayland-client-core.h"

#परिभाषय SDL_WAYLAND_CHECK_संस्करणम्(x, y, z)                        \
    (WAYLAND_संस्करणम्_MAJOR > x ||                                 \
     (WAYLAND_संस्करणम्_MAJOR == x && WAYLAND_संस्करणम्_MINOR > y) || \
     (WAYLAND_संस्करणम्_MAJOR == x && WAYLAND_संस्करणम्_MINOR == y && WAYLAND_संस्करणम्_MICRO >= z))

#परिभाषय SDL_XKBCOMMON_CHECK_संस्करणम्(x, y, z)                                  \
    (SDL_XKBCOMMON_संस्करणम्_MAJOR > x ||                                       \
     (SDL_XKBCOMMON_संस्करणम्_MAJOR == x && SDL_XKBCOMMON_संस्करणम्_MINOR > y) || \
     (SDL_XKBCOMMON_संस्करणम्_MAJOR == x && SDL_XKBCOMMON_संस्करणम्_MINOR == y && SDL_XKBCOMMON_संस्करणम्_PATCH >= z))

#यदि_परिभाषितम् HAVE_LIBDECOR_H
#परिभाषय SDL_LIBDECOR_CHECK_संस्करणम्(x, y, z)                                 \
    (SDL_LIBDECOR_संस्करणम्_MAJOR > x ||                                      \
     (SDL_LIBDECOR_संस्करणम्_MAJOR == x && SDL_LIBDECOR_संस्करणम्_MINOR > y) || \
     (SDL_LIBDECOR_संस्करणम्_MAJOR == x && SDL_LIBDECOR_संस्करणम्_MINOR == y && SDL_LIBDECOR_संस्करणम्_PATCH >= z))
#यदि_अन्तः

#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः

बाह्य bool SDL_WAYLAND_आरोपय_Symbols(शून्य);
बाह्य शून्य SDL_WAYLAND_UnloadSymbols(शून्य);

#परिभाषय SDL_WAYLAND_MODULE(modname) बाह्य पूर्णाङ्क SDL_WAYLAND_HAVE_##modname;
#परिभाषय SDL_WAYLAND_SYM(rc, fn, params)        \
    प्रकारनिर्देश rc(*SDL_DYNWAYLANDFN_##fn) params; \
    बाह्य SDL_DYNWAYLANDFN_##fn WAYLAND_##fn;
#परिभाषय SDL_WAYLAND_SYM_OPT(rc, fn, params)    \
    प्रकारनिर्देश rc(*SDL_DYNWAYLANDFN_##fn) params; \
    बाह्य SDL_DYNWAYLANDFN_##fn WAYLAND_##fn;
#परिभाषय SDL_WAYLAND_INTERFACE(iface) बाह्य ध्रुव संरचना wl_interface *WAYLAND_##iface;
#अन्तर्भाव "SDL_waylandsym.h"

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

#यदि defined(_WAYLAND_CLIENT_H) || defined(WAYLAND_CLIENT_H)
#दोषः Do not include wayland-client ahead सम्बन्धि SDL_waylanddyn.h अन्तर्_2 dynamic loading बहुलकम्
#यदि_अन्तः

/* wayland-client-protocol.h included from wayland-client.h
 * has inline functions that require these to be defined in dynamic loading mode
 */

#परिभाषय wl_proxy_create                        (*WAYLAND_wl_proxy_create)
#परिभाषय wl_proxy_destroy                       (*WAYLAND_wl_proxy_destroy)
#परिभाषय wl_proxy_marshal                       (*WAYLAND_wl_proxy_marshal)
#परिभाषय wl_proxy_समुच्चयः_user_दत्त                 (*WAYLAND_wl_proxy_समुच्चयः_user_दत्त)
#परिभाषय wl_proxy_get_user_दत्त                 (*WAYLAND_wl_proxy_get_user_दत्त)
#परिभाषय wl_proxy_get_संस्करणम्                   (*WAYLAND_wl_proxy_get_संस्करणम्)
#परिभाषय wl_proxy_सङ्कलय_listener                  (*WAYLAND_wl_proxy_सङ्कलय_listener)
#परिभाषय wl_proxy_marshal_constructor           (*WAYLAND_wl_proxy_marshal_constructor)
#परिभाषय wl_proxy_marshal_constructor_versioned (*WAYLAND_wl_proxy_marshal_constructor_versioned)
#परिभाषय wl_proxy_समुच्चयः_चिह्नकम्                       (*WAYLAND_wl_proxy_समुच्चयः_चिह्नकम्)
#परिभाषय wl_proxy_get_चिह्नकम्                       (*WAYLAND_wl_proxy_get_चिह्नकम्)
#परिभाषय wl_proxy_marshal_flags                 (*WAYLAND_wl_proxy_marshal_flags)
#परिभाषय wl_proxy_marshal_array_flags           (*WAYLAND_wl_proxy_marshal_array_flags)
#परिभाषय wl_display_reconnect                   (*WAYLAND_wl_display_reconnect)

/*
 * These must be included before libdecor.h, otherwise the libdecor header
 * pulls in the system Wayland protocol headers instead of ours.
 */
#अन्तर्भाव "wayland-client-protocol.h"
#अन्तर्भाव "wayland-egl.h"

#यदि_परिभाषितम् HAVE_LIBDECOR_H
// Must be included before our defines
#अन्तर्भाव <libdecor.h>

#परिभाषय libdecor_unref                          (*WAYLAND_libdecor_unref)
#परिभाषय libdecor_new                            (*WAYLAND_libdecor_new)
#परिभाषय libdecor_decorate                       (*WAYLAND_libdecor_decorate)
#परिभाषय libdecor_frame_unref                    (*WAYLAND_libdecor_frame_unref)
#परिभाषय libdecor_frame_समुच्चयः_title                (*WAYLAND_libdecor_frame_समुच्चयः_title)
#परिभाषय libdecor_frame_समुच्चयः_app_id               (*WAYLAND_libdecor_frame_समुच्चयः_app_id)
#परिभाषय libdecor_frame_समुच्चयः_max_content_आकार     (*WAYLAND_libdecor_frame_समुच्चयः_max_content_आकार)
#परिभाषय libdecor_frame_get_max_content_आकार     (*WAYLAND_libdecor_frame_get_max_content_आकार)
#परिभाषय libdecor_frame_समुच्चयः_min_content_आकार     (*WAYLAND_libdecor_frame_समुच्चयः_min_content_आकार)
#परिभाषय libdecor_frame_get_min_content_आकार     (*WAYLAND_libdecor_frame_get_min_content_आकार)
#परिभाषय libdecor_frame_resize                   (*WAYLAND_libdecor_frame_resize)
#परिभाषय libdecor_frame_move                     (*WAYLAND_libdecor_frame_move)
#परिभाषय libdecor_frame_commit                   (*WAYLAND_libdecor_frame_commit)
#परिभाषय libdecor_frame_समुच्चयः_minimized            (*WAYLAND_libdecor_frame_समुच्चयः_minimized)
#परिभाषय libdecor_frame_समुच्चयः_maximized            (*WAYLAND_libdecor_frame_समुच्चयः_maximized)
#परिभाषय libdecor_frame_unset_maximized          (*WAYLAND_libdecor_frame_unset_maximized)
#परिभाषय libdecor_frame_समुच्चयः_fullscreen           (*WAYLAND_libdecor_frame_समुच्चयः_fullscreen)
#परिभाषय libdecor_frame_unset_fullscreen         (*WAYLAND_libdecor_frame_unset_fullscreen)
#परिभाषय libdecor_frame_समुच्चयः_capabilities         (*WAYLAND_libdecor_frame_समुच्चयः_capabilities)
#परिभाषय libdecor_frame_unset_capabilities       (*WAYLAND_libdecor_frame_unset_capabilities)
#परिभाषय libdecor_frame_has_capability           (*WAYLAND_libdecor_frame_has_capability)
#परिभाषय libdecor_frame_समुच्चयः_visibility           (*WAYLAND_libdecor_frame_समुच्चयः_visibility)
#परिभाषय libdecor_frame_is_visible               (*WAYLAND_libdecor_frame_is_visible)
#परिभाषय libdecor_frame_is_floating              (*WAYLAND_libdecor_frame_is_floating)
#परिभाषय libdecor_frame_समुच्चयः_parent               (*WAYLAND_libdecor_frame_समुच्चयः_parent)
#परिभाषय libdecor_frame_show_गवाक्षः_menu         (*WAYLAND_libdecor_frame_show_गवाक्षः_menu)
#परिभाषय libdecor_frame_get_wm_capabilities      (*WAYLAND_libdecor_frame_get_wm_capabilities)
#परिभाषय libdecor_frame_get_xdg_surface          (*WAYLAND_libdecor_frame_get_xdg_surface)
#परिभाषय libdecor_frame_get_xdg_toplevel         (*WAYLAND_libdecor_frame_get_xdg_toplevel)
#परिभाषय libdecor_frame_translate_coordinate     (*WAYLAND_libdecor_frame_translate_coordinate)
#परिभाषय libdecor_frame_map                      (*WAYLAND_libdecor_frame_map)
#परिभाषय libdecor_state_new                      (*WAYLAND_libdecor_state_new)
#परिभाषय libdecor_state_free                     (*WAYLAND_libdecor_state_free)
#परिभाषय libdecor_configuration_get_content_आकार (*WAYLAND_libdecor_configuration_get_content_आकार)
#परिभाषय libdecor_configuration_get_गवाक्षः_state (*WAYLAND_libdecor_configuration_get_गवाक्षः_state)
#परिभाषय libdecor_dispatch                       (*WAYLAND_libdecor_dispatch)
#यदि_अन्तः

#अन्यथा // SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

/*
 * These must be included before libdecor.h, otherwise the libdecor header
 * pulls in the system Wayland protocol headers instead of ours.
 */
#अन्तर्भाव "wayland-client-protocol.h"
#अन्तर्भाव "wayland-egl.h"

#यदि_परिभाषितम् HAVE_LIBDECOR_H
#अन्तर्भाव <libdecor.h>
#यदि_अन्तः

#यदि_अन्तः // SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

#यदि_अन्तः // SDL_waylanddyn_h_
