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
#अगर_अघोषित SDL_waylanddyn_h_
#घोषणा SDL_waylanddyn_h_

#समावेश "SDL_internal.h"

/* We can't include wayland-client.h here
 * but we need some structs from it
 */
काष्ठा wl_interface;
काष्ठा wl_proxy;
काष्ठा wl_event_queue;
काष्ठा wl_display;
काष्ठा wl_surface;
काष्ठा wl_shm;

// We also need some for libdecor
काष्ठा wl_seat;
काष्ठा wl_output;
काष्ठा libdecor;
काष्ठा libdecor_frame;
काष्ठा libdecor_state;
काष्ठा libdecor_configuration;
काष्ठा libdecor_interface;
काष्ठा libdecor_frame_interface;
क्रमागत libdecor_resize_edge;
क्रमागत libdecor_capabilities;
क्रमागत libdecor_window_state;

#समावेश "wayland-cursor.h"
#समावेश "wayland-util.h"
#समावेश "xkbcommon/xkbcommon.h"
#समावेश "xkbcommon/xkbcommon-compose.h"

// Must be included before our #defines, see Bugzilla #4957
#समावेश "wayland-client-core.h"

#घोषणा SDL_WAYLAND_CHECK_VERSION(x, y, z)                        \
    (WAYLAND_VERSION_MAJOR > x ||                                 \
     (WAYLAND_VERSION_MAJOR == x && WAYLAND_VERSION_MINOR > y) || \
     (WAYLAND_VERSION_MAJOR == x && WAYLAND_VERSION_MINOR == y && WAYLAND_VERSION_MICRO >= z))

#घोषणा SDL_XKBCOMMON_CHECK_VERSION(x, y, z)                                  \
    (SDL_XKBCOMMON_VERSION_MAJOR > x ||                                       \
     (SDL_XKBCOMMON_VERSION_MAJOR == x && SDL_XKBCOMMON_VERSION_MINOR > y) || \
     (SDL_XKBCOMMON_VERSION_MAJOR == x && SDL_XKBCOMMON_VERSION_MINOR == y && SDL_XKBCOMMON_VERSION_PATCH >= z))

#अगर_घोषित HAVE_LIBDECOR_H
#घोषणा SDL_LIBDECOR_CHECK_VERSION(x, y, z)                                 \
    (SDL_LIBDECOR_VERSION_MAJOR > x ||                                      \
     (SDL_LIBDECOR_VERSION_MAJOR == x && SDL_LIBDECOR_VERSION_MINOR > y) || \
     (SDL_LIBDECOR_VERSION_MAJOR == x && SDL_LIBDECOR_VERSION_MINOR == y && SDL_LIBDECOR_VERSION_PATCH >= z))
#पूर्ण_अगर

#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर

बाह्य bool SDL_WAYLAND_LoadSymbols(व्योम);
बाह्य व्योम SDL_WAYLAND_UnloadSymbols(व्योम);

#घोषणा SDL_WAYLAND_MODULE(modname) बाह्य पूर्णांक SDL_WAYLAND_HAVE_##modname;
#घोषणा SDL_WAYLAND_SYM(rc, fn, params)        \
    प्रकार rc(*SDL_DYNWAYLANDFN_##fn) params; \
    बाह्य SDL_DYNWAYLANDFN_##fn WAYLAND_##fn;
#घोषणा SDL_WAYLAND_SYM_OPT(rc, fn, params)    \
    प्रकार rc(*SDL_DYNWAYLANDFN_##fn) params; \
    बाह्य SDL_DYNWAYLANDFN_##fn WAYLAND_##fn;
#घोषणा SDL_WAYLAND_INTERFACE(iface) बाह्य स्थिर काष्ठा wl_interface *WAYLAND_##iface;
#समावेश "SDL_waylandsym.h"

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#अगर_घोषित SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

#अगर defined(_WAYLAND_CLIENT_H) || defined(WAYLAND_CLIENT_H)
#त्रुटि Do not include wayland-client ahead of SDL_waylanddyn.h in dynamic loading mode
#पूर्ण_अगर

/* wayland-client-protocol.h included from wayland-client.h
 * has inline functions that require these to be defined in dynamic loading mode
 */

#घोषणा wl_proxy_create                        (*WAYLAND_wl_proxy_create)
#घोषणा wl_proxy_destroy                       (*WAYLAND_wl_proxy_destroy)
#घोषणा wl_proxy_marshal                       (*WAYLAND_wl_proxy_marshal)
#घोषणा wl_proxy_set_user_तथ्य                 (*WAYLAND_wl_proxy_set_user_तथ्य)
#घोषणा wl_proxy_get_user_तथ्य                 (*WAYLAND_wl_proxy_get_user_तथ्य)
#घोषणा wl_proxy_get_version                   (*WAYLAND_wl_proxy_get_version)
#घोषणा wl_proxy_add_listener                  (*WAYLAND_wl_proxy_add_listener)
#घोषणा wl_proxy_marshal_constructor           (*WAYLAND_wl_proxy_marshal_constructor)
#घोषणा wl_proxy_marshal_constructor_versioned (*WAYLAND_wl_proxy_marshal_constructor_versioned)
#घोषणा wl_proxy_set_tag                       (*WAYLAND_wl_proxy_set_tag)
#घोषणा wl_proxy_get_tag                       (*WAYLAND_wl_proxy_get_tag)
#घोषणा wl_proxy_marshal_flags                 (*WAYLAND_wl_proxy_marshal_flags)
#घोषणा wl_proxy_marshal_array_flags           (*WAYLAND_wl_proxy_marshal_array_flags)
#घोषणा wl_display_reconnect                   (*WAYLAND_wl_display_reconnect)

/*
 * These must be included before libdecor.h, otherwise the libdecor header
 * pulls in the system Wayland protocol headers instead of ours.
 */
#समावेश "wayland-client-protocol.h"
#समावेश "wayland-egl.h"

#अगर_घोषित HAVE_LIBDECOR_H
// Must be included before our defines
#समावेश <libdecor.h>

#घोषणा libdecor_unref                          (*WAYLAND_libdecor_unref)
#घोषणा libdecor_new                            (*WAYLAND_libdecor_new)
#घोषणा libdecor_decorate                       (*WAYLAND_libdecor_decorate)
#घोषणा libdecor_frame_unref                    (*WAYLAND_libdecor_frame_unref)
#घोषणा libdecor_frame_set_title                (*WAYLAND_libdecor_frame_set_title)
#घोषणा libdecor_frame_set_app_id               (*WAYLAND_libdecor_frame_set_app_id)
#घोषणा libdecor_frame_set_max_content_आकार     (*WAYLAND_libdecor_frame_set_max_content_आकार)
#घोषणा libdecor_frame_get_max_content_आकार     (*WAYLAND_libdecor_frame_get_max_content_आकार)
#घोषणा libdecor_frame_set_min_content_आकार     (*WAYLAND_libdecor_frame_set_min_content_आकार)
#घोषणा libdecor_frame_get_min_content_आकार     (*WAYLAND_libdecor_frame_get_min_content_आकार)
#घोषणा libdecor_frame_resize                   (*WAYLAND_libdecor_frame_resize)
#घोषणा libdecor_frame_move                     (*WAYLAND_libdecor_frame_move)
#घोषणा libdecor_frame_commit                   (*WAYLAND_libdecor_frame_commit)
#घोषणा libdecor_frame_set_minimized            (*WAYLAND_libdecor_frame_set_minimized)
#घोषणा libdecor_frame_set_maximized            (*WAYLAND_libdecor_frame_set_maximized)
#घोषणा libdecor_frame_unset_maximized          (*WAYLAND_libdecor_frame_unset_maximized)
#घोषणा libdecor_frame_set_fullscreen           (*WAYLAND_libdecor_frame_set_fullscreen)
#घोषणा libdecor_frame_unset_fullscreen         (*WAYLAND_libdecor_frame_unset_fullscreen)
#घोषणा libdecor_frame_set_capabilities         (*WAYLAND_libdecor_frame_set_capabilities)
#घोषणा libdecor_frame_unset_capabilities       (*WAYLAND_libdecor_frame_unset_capabilities)
#घोषणा libdecor_frame_has_capability           (*WAYLAND_libdecor_frame_has_capability)
#घोषणा libdecor_frame_set_visibility           (*WAYLAND_libdecor_frame_set_visibility)
#घोषणा libdecor_frame_is_visible               (*WAYLAND_libdecor_frame_is_visible)
#घोषणा libdecor_frame_is_floating              (*WAYLAND_libdecor_frame_is_floating)
#घोषणा libdecor_frame_set_parent               (*WAYLAND_libdecor_frame_set_parent)
#घोषणा libdecor_frame_show_window_menu         (*WAYLAND_libdecor_frame_show_window_menu)
#घोषणा libdecor_frame_get_wm_capabilities      (*WAYLAND_libdecor_frame_get_wm_capabilities)
#घोषणा libdecor_frame_get_xdg_surface          (*WAYLAND_libdecor_frame_get_xdg_surface)
#घोषणा libdecor_frame_get_xdg_toplevel         (*WAYLAND_libdecor_frame_get_xdg_toplevel)
#घोषणा libdecor_frame_translate_coordinate     (*WAYLAND_libdecor_frame_translate_coordinate)
#घोषणा libdecor_frame_map                      (*WAYLAND_libdecor_frame_map)
#घोषणा libdecor_state_new                      (*WAYLAND_libdecor_state_new)
#घोषणा libdecor_state_free                     (*WAYLAND_libdecor_state_free)
#घोषणा libdecor_configuration_get_content_आकार (*WAYLAND_libdecor_configuration_get_content_आकार)
#घोषणा libdecor_configuration_get_window_state (*WAYLAND_libdecor_configuration_get_window_state)
#घोषणा libdecor_dispatch                       (*WAYLAND_libdecor_dispatch)
#पूर्ण_अगर

#अन्यथा // SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

/*
 * These must be included before libdecor.h, otherwise the libdecor header
 * pulls in the system Wayland protocol headers instead of ours.
 */
#समावेश "wayland-client-protocol.h"
#समावेश "wayland-egl.h"

#अगर_घोषित HAVE_LIBDECOR_H
#समावेश <libdecor.h>
#पूर्ण_अगर

#पूर्ण_अगर // SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC

#पूर्ण_अगर // SDL_waylanddyn_h_
