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

/* *INDENT-OFF* */ // clang-format off

#ifndef SDL_WAYLAND_MODULE
#define SDL_WAYLAND_MODULE(modname)
#endif

#ifndef SDL_WAYLAND_SYM
#define SDL_WAYLAND_SYM(rc,fn,params)
#endif

#ifndef SDL_WAYLAND_SYM_OPT
#define SDL_WAYLAND_SYM_OPT(rc,fn,params)
#endif

SDL_WAYLAND_MODULE(WAYLAND_CLIENT)
SDL_WAYLAND_SYM(શૂન્ય, wl_proxy_marshal, (સંરચના wl_proxy *, uint32_t, ...))
SDL_WAYLAND_SYM(સંરચના wl_proxy *, wl_proxy_create, (સંરચના wl_proxy *, અચલ સંરચના wl_interface *))
SDL_WAYLAND_SYM(શૂન્ય, wl_proxy_destroy, (સંરચના wl_proxy *))
SDL_WAYLAND_SYM(પૂર્ણાંક, wl_proxy_add_listener, (સંરચના wl_proxy *, શૂન્ય (**)(શૂન્ય), શૂન્ય *))
SDL_WAYLAND_SYM(શૂન્ય, wl_proxy_set_user_data, (સંરચના wl_proxy *, શૂન્ય *))
SDL_WAYLAND_SYM(શૂન્ય *, wl_proxy_get_user_data, (સંરચના wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_version, (સંરચના wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_id, (સંરચના wl_proxy *))
SDL_WAYLAND_SYM(અચલ અક્ષર *, wl_proxy_get_class, (સંરચના wl_proxy *))
SDL_WAYLAND_SYM(શૂન્ય, wl_proxy_set_queue, (સંરચના wl_proxy *, સંરચના wl_event_queue *))
SDL_WAYLAND_SYM(શૂન્ય *, wl_proxy_create_wrapper, (શૂન્ય *))
SDL_WAYLAND_SYM(શૂન્ય, wl_proxy_wrapper_destroy, (શૂન્ય *))
SDL_WAYLAND_SYM(સંરચના wl_display *, wl_display_connect, (અચલ અક્ષર *))
SDL_WAYLAND_SYM(સંરચના wl_display *, wl_display_connect_to_fd, (પૂર્ણાંક))
SDL_WAYLAND_SYM(શૂન્ય, wl_display_disconnect, (સંરચના wl_display *))
SDL_WAYLAND_SYM(પૂર્ણાંક, wl_display_get_fd, (સંરચના wl_display *))
SDL_WAYLAND_SYM(પૂર્ણાંક, wl_display_dispatch, (સંરચના wl_display *))
SDL_WAYLAND_SYM(પૂર્ણાંક, wl_display_dispatch_queue, (સંરચના wl_display *, સંરચના wl_event_queue *))
SDL_WAYLAND_SYM(પૂર્ણાંક, wl_display_dispatch_queue_pending, (સંરચના wl_display *, સંરચના wl_event_queue *))
SDL_WAYLAND_SYM(પૂર્ણાંક, wl_display_dispatch_pending, (સંરચના wl_display *))
SDL_WAYLAND_SYM(પૂર્ણાંક, wl_display_prepare_read, (સંરચના wl_display *))
SDL_WAYLAND_SYM(પૂર્ણાંક, wl_display_prepare_read_queue, (સંરચના wl_display *, સંરચના wl_event_queue *))
SDL_WAYLAND_SYM(પૂર્ણાંક, wl_display_read_events, (સંરચના wl_display *))
SDL_WAYLAND_SYM(શૂન્ય, wl_display_cancel_read, (સંરચના wl_display *))
SDL_WAYLAND_SYM(પૂર્ણાંક, wl_display_get_error, (સંરચના wl_display *))
SDL_WAYLAND_SYM(પૂર્ણાંક, wl_display_flush, (સંરચના wl_display *))
SDL_WAYLAND_SYM(પૂર્ણાંક, wl_display_roundtrip, (સંરચના wl_display *))
SDL_WAYLAND_SYM(સંરચના wl_event_queue *, wl_display_create_queue, (સંરચના wl_display *))
SDL_WAYLAND_SYM(શૂન્ય, wl_event_queue_destroy, (સંરચના wl_event_queue *))
SDL_WAYLAND_SYM(શૂન્ય, wl_log_set_handler_client, (wl_log_func_t))
SDL_WAYLAND_SYM(શૂન્ય, wl_list_init, (સંરચના wl_list *))
SDL_WAYLAND_SYM(શૂન્ય, wl_list_ઉમેરો, (સંરચના wl_list *, સંરચના wl_list *) )
SDL_WAYLAND_SYM(શૂન્ય, wl_list_remove, (સંરચના wl_list *))
SDL_WAYLAND_SYM(પૂર્ણાંક, wl_list_length, (અચલ સંરચના wl_list *))
SDL_WAYLAND_SYM(પૂર્ણાંક, wl_list_empty, (અચલ સંરચના wl_list *))
SDL_WAYLAND_SYM(શૂન્ય, wl_list_ઉમેરો_list, (સંરચના wl_list *, સંરચના wl_list *))
SDL_WAYLAND_SYM(શૂન્ય, wl_array_init, (સંરચના wl_array *))
SDL_WAYLAND_SYM(શૂન્ય, wl_array_release, (સંરચના wl_array *))
SDL_WAYLAND_SYM(શૂન્ય *, wl_array_add, (સંરચના wl_array *, size_t))
SDL_WAYLAND_SYM(પૂર્ણાંક, wl_array_copy, (સંરચના wl_array *, સંરચના wl_array *))
SDL_WAYLAND_SYM(સંરચના wl_proxy *, wl_proxy_marshal_constructor, (સંરચના wl_proxy *, uint32_t opcode, અચલ સંરચના wl_interface *interface, ...))
SDL_WAYLAND_SYM(સંરચના wl_proxy *, wl_proxy_marshal_constructor_versioned, (સંરચના wl_proxy *proxy, uint32_t opcode, અચલ સંરચના wl_interface *interface, uint32_t version, ...))
SDL_WAYLAND_SYM(શૂન્ય, wl_proxy_set_tag, (સંરચના wl_proxy *, અચલ અક્ષર * અચલ *))
SDL_WAYLAND_SYM(અચલ અક્ષર * અચલ *, wl_proxy_get_tag, (સંરચના wl_proxy *))

#જો SDL_WAYLAND_CHECK_VERSION(1, 20, 0)
/* wayland-scanner 1.20 generates code that will call these, so these are
 * non-optional when we are compiling against Wayland 1.20. We don't
 * explicitly call them ourselves, though, so if we are only compiling
 * against Wayland 1.18, they're unnecessary. */
SDL_WAYLAND_SYM(સંરચના wl_proxy *, wl_proxy_marshal_flags, (સંરચના wl_proxy *proxy, uint32_t opcode, અચલ સંરચના wl_interface *interface, uint32_t version, uint32_t flags, ...))
SDL_WAYLAND_SYM(સંરચના wl_proxy *, wl_proxy_marshal_array_flags, (સંરચના wl_proxy *proxy, uint32_t opcode, અચલ સંરચના wl_interface *interface, uint32_t version,  uint32_t flags, સંઘ wl_argument *args))
#endif

#જો SDL_WAYLAND_CHECK_VERSION(1, 23, 0) || defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC)
SDL_WAYLAND_SYM_OPT(સંરચના wl_event_queue *, wl_display_create_queue_with_name, (સંરચના wl_display *display, અચલ અક્ષર *name))
#endif

#જો 0 // TODO RECONNECT: See waylandvideo.c for more information!
#જો SDL_WAYLAND_CHECK_VERSION(broken, on, purpose)
SDL_WAYLAND_SYM(પૂર્ણાંક, wl_display_reconnect, (સંરચના wl_display *))
#endif
#endif // 0

SDL_WAYLAND_MODULE(WAYLAND_EGL)
SDL_WAYLAND_SYM(સંરચના wl_egl_window *, wl_egl_window_create, (સંરચના wl_surface *, પૂર્ણાંક, પૂર્ણાંક))
SDL_WAYLAND_SYM(શૂન્ય, wl_egl_window_destroy, (સંરચના wl_egl_window *))
SDL_WAYLAND_SYM(શૂન્ય, wl_egl_window_resize, (સંરચના wl_egl_window *, પૂર્ણાંક, પૂર્ણાંક, પૂર્ણાંક, પૂર્ણાંક))
SDL_WAYLAND_SYM(શૂન્ય, wl_egl_window_get_attached_size, (સંરચના wl_egl_window *, પૂર્ણાંક *, પૂર્ણાંક *))

SDL_WAYLAND_MODULE(WAYLAND_CURSOR)
SDL_WAYLAND_SYM(સંરચના wl_cursor_theme *, wl_cursor_theme_load, (અચલ અક્ષર *, પૂર્ણાંક , સંરચના wl_shm *))
SDL_WAYLAND_SYM(શૂન્ય, wl_cursor_theme_destroy, (સંરચના wl_cursor_theme *))
SDL_WAYLAND_SYM(સંરચના wl_cursor *, wl_cursor_theme_get_cursor, (સંરચના wl_cursor_theme *, અચલ અક્ષર *))
SDL_WAYLAND_SYM(સંરચના wl_buffer *, wl_cursor_image_get_buffer, (સંરચના wl_cursor_image *))
SDL_WAYLAND_SYM(પૂર્ણાંક, wl_cursor_frame, (સંરચના wl_cursor *, uint32_t))

SDL_WAYLAND_MODULE(WAYLAND_XKB)
SDL_WAYLAND_SYM(પૂર્ણાંક, xkb_state_ચાવી_get_syms, (સંરચના xkb_state *, xkb_keycode_t, અચલ xkb_keysym_t **))
SDL_WAYLAND_SYM(પૂર્ણાંક, xkb_keysym_to_utf8, (xkb_keysym_t, અક્ષર *, size_t) )
SDL_WAYLAND_SYM(સંરચના xkb_keymap *, xkb_keymap_new_from_string, (સંરચના xkb_context *, અચલ અક્ષર *, ગણના xkb_keymap_format, ગણના xkb_keymap_compile_flags))
SDL_WAYLAND_SYM(સંરચના xkb_state *, xkb_state_new, (સંરચના xkb_keymap *) )
SDL_WAYLAND_SYM(પૂર્ણાંક, xkb_keymap_ચાવી_repeats, (સંરચના xkb_keymap *keymap, xkb_keycode_t ચાવી) )
SDL_WAYLAND_SYM(શૂન્ય, xkb_keymap_unref, (સંરચના xkb_keymap *) )
SDL_WAYLAND_SYM(શૂન્ય, xkb_state_unref, (સંરચના xkb_state *) )
SDL_WAYLAND_SYM(શૂન્ય, xkb_context_unref, (સંરચના xkb_context *) )
SDL_WAYLAND_SYM(સંરચના xkb_context *, xkb_context_new, (ગણના xkb_context_flags flags) )
SDL_WAYLAND_SYM(ગણના xkb_state_component, xkb_state_update_mask, (સંરચના xkb_state *state,\
                      xkb_mod_mask_t depressed_mods,\
                      xkb_mod_mask_t latched_mods,\
                      xkb_mod_mask_t locked_mods,\
                      xkb_layout_index_t depressed_layout,\
                      xkb_layout_index_t latched_layout,\
                      xkb_layout_index_t locked_layout) )
SDL_WAYLAND_SYM(સંરચના xkb_compose_table *, xkb_compose_table_new_from_locale, (સંરચના xkb_context *,\
                      અચલ અક્ષર *locale, ગણના xkb_compose_compile_flags) )
SDL_WAYLAND_SYM(શૂન્ય, xkb_compose_state_reset, (સંરચના xkb_compose_state *) )
SDL_WAYLAND_SYM(શૂન્ય, xkb_compose_table_unref, (સંરચના xkb_compose_table *) )
SDL_WAYLAND_SYM(સંરચના xkb_compose_state *, xkb_compose_state_new, (સંરચના xkb_compose_table *, ગણના xkb_compose_state_flags) )
SDL_WAYLAND_SYM(શૂન્ય, xkb_compose_state_unref, (સંરચના xkb_compose_state *) )
SDL_WAYLAND_SYM(ગણના xkb_compose_feed_result, xkb_compose_state_feed, (સંરચના xkb_compose_state *, xkb_keysym_t) )
SDL_WAYLAND_SYM(ગણના xkb_compose_status, xkb_compose_state_get_status, (સંરચના xkb_compose_state *) )
SDL_WAYLAND_SYM(xkb_keysym_t, xkb_compose_state_get_one_sym, (સંરચના xkb_compose_state *) )
SDL_WAYLAND_SYM(શૂન્ય, xkb_keymap_ચાવી_for_each, (સંરચના xkb_keymap *, xkb_keymap_ચાવી_iter_t, શૂન્ય *) )
SDL_WAYLAND_SYM(xkb_layout_index_t, xkb_keymap_અંક_layouts, (સંરચના xkb_keymap *) )
SDL_WAYLAND_SYM(પૂર્ણાંક, xkb_keymap_ચાવી_get_syms_by_level, (સંરચના xkb_keymap *, xkb_keycode_t, xkb_layout_index_t, xkb_level_index_t, અચલ xkb_keysym_t **) )
SDL_WAYLAND_SYM(xkb_level_index_t, xkb_keymap_અંક_levels_for_ચાવી, (સંરચના xkb_keymap *, xkb_keycode_t, xkb_layout_index_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keysym_to_utf32, (xkb_keysym_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keymap_mod_get_index, (સંરચના xkb_keymap *, અચલ અક્ષર *) )
SDL_WAYLAND_SYM(અચલ અક્ષર *, xkb_keymap_layout_get_name, (સંરચના xkb_keymap *, xkb_layout_index_t))

#જો SDL_XKBCOMMON_CHECK_VERSION(1, 0, 0)
SDL_WAYLAND_SYM(size_t, xkb_keymap_ચાવી_get_mods_for_level, (સંરચના xkb_keymap *, xkb_keycode_t, xkb_layout_index_t, xkb_level_index_t, xkb_mod_mask_t *, size_t) )
#નહીંતર
// Only needed in the fallback replacement for xkb_keymap_key_get_mods_for_level().
SDL_WAYLAND_SYM(xkb_level_index_t, xkb_state_ચાવી_get_level, (સંરચના xkb_state *, xkb_keycode_t, xkb_layout_index_t) )
#endif

#જો SDL_XKBCOMMON_CHECK_VERSION(1, 10, 0)
SDL_WAYLAND_SYM(xkb_mod_mask_t, xkb_keymap_mod_get_mask, (સંરચના xkb_keymap *, અચલ અક્ષર *))
#endif

#ifdef HAVE_LIBDECOR_H
SDL_WAYLAND_MODULE(WAYLAND_LIBDECOR)

#જો defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_VERSION(0, 3, 0)
#define SDL_libdecor_constsince03 અચલ
#નહીંતર
#define SDL_libdecor_constsince03 /* nothing */
#endif

SDL_WAYLAND_SYM(શૂન્ય, libdecor_unref, (સંરચના libdecor *))
SDL_WAYLAND_SYM(સંરચના libdecor *, libdecor_new, (સંરચના wl_display *,\
                                                  SDL_libdecor_constsince03 સંરચના libdecor_interface *))
SDL_WAYLAND_SYM(સંરચના libdecor_frame *, libdecor_decorate, (સંરચના libdecor *,\
                                                             સંરચના wl_surface *,\
                                                             SDL_libdecor_constsince03 સંરચના libdecor_frame_interface *,\
                                                             શૂન્ય *))
SDL_WAYLAND_SYM(શૂન્ય, libdecor_frame_unref, (સંરચના libdecor_frame *))
SDL_WAYLAND_SYM(શૂન્ય, libdecor_frame_set_title, (સંરચના libdecor_frame *, અચલ અક્ષર *))
SDL_WAYLAND_SYM(શૂન્ય, libdecor_frame_set_app_id, (સંરચના libdecor_frame *, અચલ અક્ષર *))
SDL_WAYLAND_SYM(શૂન્ય, libdecor_frame_set_max_content_size, (સંરચના libdecor_frame *frame,\
                                                            પૂર્ણાંક content_width,\
                                                            પૂર્ણાંક content_height))
SDL_WAYLAND_SYM(શૂન્ય, libdecor_frame_set_min_content_size, (સંરચના libdecor_frame *frame,\
                                                            પૂર્ણાંક content_width,\
                                                            પૂર્ણાંક content_height))
SDL_WAYLAND_SYM(શૂન્ય, libdecor_frame_resize, (સંરચના libdecor_frame *,\
                                              સંરચના wl_seat *,\
                                              uint32_t,\
                                              ગણના libdecor_resize_edge))
SDL_WAYLAND_SYM(શૂન્ય, libdecor_frame_move, (સંરચના libdecor_frame *,\
                                            સંરચના wl_seat *,\
                                            uint32_t))
SDL_WAYLAND_SYM(શૂન્ય, libdecor_frame_commit, (સંરચના libdecor_frame *,\
                                              સંરચના libdecor_state *,\
                                              સંરચના libdecor_configuration *))
SDL_WAYLAND_SYM(શૂન્ય, libdecor_frame_set_minimized, (સંરચના libdecor_frame *))
SDL_WAYLAND_SYM(શૂન્ય, libdecor_frame_set_maximized, (સંરચના libdecor_frame *))
SDL_WAYLAND_SYM(શૂન્ય, libdecor_frame_unset_maximized, (સંરચના libdecor_frame *))
SDL_WAYLAND_SYM(શૂન્ય, libdecor_frame_set_fullscreen, (સંરચના libdecor_frame *, સંરચના wl_output *))
SDL_WAYLAND_SYM(શૂન્ય, libdecor_frame_unset_fullscreen, (સંરચના libdecor_frame *))
SDL_WAYLAND_SYM(શૂન્ય, libdecor_frame_set_capabilities, (સંરચના libdecor_frame *, \
                                                        ગણના libdecor_capabilities))
SDL_WAYLAND_SYM(શૂન્ય, libdecor_frame_unset_capabilities, (સંરચના libdecor_frame *, \
                                                          ગણના libdecor_capabilities))
SDL_WAYLAND_SYM(bool, libdecor_frame_has_capability, (સંરચના libdecor_frame *, \
                                                      ગણના libdecor_capabilities))
SDL_WAYLAND_SYM(શૂન્ય, libdecor_frame_set_visibility, (સંરચના libdecor_frame *, bool))
SDL_WAYLAND_SYM(bool, libdecor_frame_is_visible, (સંરચના libdecor_frame *))
SDL_WAYLAND_SYM(bool, libdecor_frame_is_floating, (સંરચના libdecor_frame *))
SDL_WAYLAND_SYM(શૂન્ય, libdecor_frame_set_parent, (સંરચના libdecor_frame *,\
                                                  સંરચના libdecor_frame *))
SDL_WAYLAND_SYM(શૂન્ય, libdecor_frame_show_window_menu, (સંરચના libdecor_frame *, સંરચના wl_seat *, uint32_t, પૂર્ણાંક, પૂર્ણાંક))
SDL_WAYLAND_SYM(સંરચના xdg_surface *, libdecor_frame_get_xdg_surface, (સંરચના libdecor_frame *))
SDL_WAYLAND_SYM(સંરચના xdg_toplevel *, libdecor_frame_get_xdg_toplevel, (સંરચના libdecor_frame *))
SDL_WAYLAND_SYM(શૂન્ય, libdecor_frame_translate_coordinate, (સંરચના libdecor_frame *, પૂર્ણાંક, પૂર્ણાંક, પૂર્ણાંક *, પૂર્ણાંક *))
SDL_WAYLAND_SYM(શૂન્ય, libdecor_frame_map, (સંરચના libdecor_frame *))
SDL_WAYLAND_SYM(સંરચના libdecor_state *, libdecor_state_new, (પૂર્ણાંક, પૂર્ણાંક))
SDL_WAYLAND_SYM(શૂન્ય, libdecor_state_free, (સંરચના libdecor_state *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_content_size, (સંરચના libdecor_configuration *,\
                                                                સંરચના libdecor_frame *,\
                                                                પૂર્ણાંક *,\
                                                                પૂર્ણાંક *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_window_state, (સંરચના libdecor_configuration *,\
                                                                ગણના libdecor_window_state *))
SDL_WAYLAND_SYM(પૂર્ણાંક, libdecor_dispatch, (સંરચના libdecor *, પૂર્ણાંક))

#જો defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_VERSION(0, 2, 0)
// Only found in libdecor 0.1.1 or higher, so failure to load them is not fatal.
SDL_WAYLAND_SYM_OPT(શૂન્ય, libdecor_frame_get_min_content_size, (અચલ સંરચના libdecor_frame *,\
                                                            પૂર્ણાંક *,\
                                                            પૂર્ણાંક *))
SDL_WAYLAND_SYM_OPT(શૂન્ય, libdecor_frame_get_max_content_size, (અચલ સંરચના libdecor_frame *,\
                                                            પૂર્ણાંક *,\
                                                            પૂર્ણાંક *))
#endif

#જો defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_VERSION(0, 3, 0)
SDL_WAYLAND_SYM_OPT(ગણના libdecor_wm_capabilities, libdecor_frame_get_wm_capabilities, (સંરચના libdecor_frame *))
#endif

#undef SDL_libdecor_constsince03

#endif

#undef SDL_WAYLAND_MODULE
#undef SDL_WAYLAND_SYM
#undef SDL_WAYLAND_SYM_OPT

/* *INDENT-ON* */ // clang-format on
