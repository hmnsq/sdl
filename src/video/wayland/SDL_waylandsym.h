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
SDL_WAYLAND_SYM(ശൂന്യം, wl_proxy_marshal, (ഘടന wl_proxy *, uint32_t, ...))
SDL_WAYLAND_SYM(ഘടന wl_proxy *, wl_proxy_create, (ഘടന wl_proxy *, സ്ഥിരം ഘടന wl_interface *))
SDL_WAYLAND_SYM(ശൂന്യം, wl_proxy_destroy, (ഘടന wl_proxy *))
SDL_WAYLAND_SYM(പൂർണ്ണസംഖ്യ, wl_proxy_add_listener, (ഘടന wl_proxy *, ശൂന്യം (**)(ശൂന്യം), ശൂന്യം *))
SDL_WAYLAND_SYM(ശൂന്യം, wl_proxy_set_user_data, (ഘടന wl_proxy *, ശൂന്യം *))
SDL_WAYLAND_SYM(ശൂന്യം *, wl_proxy_get_user_data, (ഘടന wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_version, (ഘടന wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_id, (ഘടന wl_proxy *))
SDL_WAYLAND_SYM(സ്ഥിരം അക്ഷരം *, wl_proxy_get_class, (ഘടന wl_proxy *))
SDL_WAYLAND_SYM(ശൂന്യം, wl_proxy_set_queue, (ഘടന wl_proxy *, ഘടന wl_event_queue *))
SDL_WAYLAND_SYM(ശൂന്യം *, wl_proxy_create_wrapper, (ശൂന്യം *))
SDL_WAYLAND_SYM(ശൂന്യം, wl_proxy_wrapper_destroy, (ശൂന്യം *))
SDL_WAYLAND_SYM(ഘടന wl_display *, wl_display_connect, (സ്ഥിരം അക്ഷരം *))
SDL_WAYLAND_SYM(ഘടന wl_display *, wl_display_connect_to_fd, (പൂർണ്ണസംഖ്യ))
SDL_WAYLAND_SYM(ശൂന്യം, wl_display_disconnect, (ഘടന wl_display *))
SDL_WAYLAND_SYM(പൂർണ്ണസംഖ്യ, wl_display_get_fd, (ഘടന wl_display *))
SDL_WAYLAND_SYM(പൂർണ്ണസംഖ്യ, wl_display_dispatch, (ഘടന wl_display *))
SDL_WAYLAND_SYM(പൂർണ്ണസംഖ്യ, wl_display_dispatch_queue, (ഘടന wl_display *, ഘടന wl_event_queue *))
SDL_WAYLAND_SYM(പൂർണ്ണസംഖ്യ, wl_display_dispatch_queue_pending, (ഘടന wl_display *, ഘടന wl_event_queue *))
SDL_WAYLAND_SYM(പൂർണ്ണസംഖ്യ, wl_display_dispatch_pending, (ഘടന wl_display *))
SDL_WAYLAND_SYM(പൂർണ്ണസംഖ്യ, wl_display_prepare_read, (ഘടന wl_display *))
SDL_WAYLAND_SYM(പൂർണ്ണസംഖ്യ, wl_display_prepare_read_queue, (ഘടന wl_display *, ഘടന wl_event_queue *))
SDL_WAYLAND_SYM(പൂർണ്ണസംഖ്യ, wl_display_read_events, (ഘടന wl_display *))
SDL_WAYLAND_SYM(ശൂന്യം, wl_display_cancel_read, (ഘടന wl_display *))
SDL_WAYLAND_SYM(പൂർണ്ണസംഖ്യ, wl_display_get_error, (ഘടന wl_display *))
SDL_WAYLAND_SYM(പൂർണ്ണസംഖ്യ, wl_display_flush, (ഘടന wl_display *))
SDL_WAYLAND_SYM(പൂർണ്ണസംഖ്യ, wl_display_roundtrip, (ഘടന wl_display *))
SDL_WAYLAND_SYM(ഘടന wl_event_queue *, wl_display_create_queue, (ഘടന wl_display *))
SDL_WAYLAND_SYM(ശൂന്യം, wl_event_queue_destroy, (ഘടന wl_event_queue *))
SDL_WAYLAND_SYM(ശൂന്യം, wl_log_set_handler_client, (wl_log_func_t))
SDL_WAYLAND_SYM(ശൂന്യം, wl_list_init, (ഘടന wl_list *))
SDL_WAYLAND_SYM(ശൂന്യം, wl_list_തിരുകുക, (ഘടന wl_list *, ഘടന wl_list *) )
SDL_WAYLAND_SYM(ശൂന്യം, wl_list_remove, (ഘടന wl_list *))
SDL_WAYLAND_SYM(പൂർണ്ണസംഖ്യ, wl_list_length, (സ്ഥിരം ഘടന wl_list *))
SDL_WAYLAND_SYM(പൂർണ്ണസംഖ്യ, wl_list_empty, (സ്ഥിരം ഘടന wl_list *))
SDL_WAYLAND_SYM(ശൂന്യം, wl_list_തിരുകുക_list, (ഘടന wl_list *, ഘടന wl_list *))
SDL_WAYLAND_SYM(ശൂന്യം, wl_array_init, (ഘടന wl_array *))
SDL_WAYLAND_SYM(ശൂന്യം, wl_array_release, (ഘടന wl_array *))
SDL_WAYLAND_SYM(ശൂന്യം *, wl_array_add, (ഘടന wl_array *, size_t))
SDL_WAYLAND_SYM(പൂർണ്ണസംഖ്യ, wl_array_copy, (ഘടന wl_array *, ഘടന wl_array *))
SDL_WAYLAND_SYM(ഘടന wl_proxy *, wl_proxy_marshal_constructor, (ഘടന wl_proxy *, uint32_t opcode, സ്ഥിരം ഘടന wl_interface *interface, ...))
SDL_WAYLAND_SYM(ഘടന wl_proxy *, wl_proxy_marshal_constructor_versioned, (ഘടന wl_proxy *proxy, uint32_t opcode, സ്ഥിരം ഘടന wl_interface *interface, uint32_t version, ...))
SDL_WAYLAND_SYM(ശൂന്യം, wl_proxy_set_tag, (ഘടന wl_proxy *, സ്ഥിരം അക്ഷരം * സ്ഥിരം *))
SDL_WAYLAND_SYM(സ്ഥിരം അക്ഷരം * സ്ഥിരം *, wl_proxy_get_tag, (ഘടന wl_proxy *))

#എങ്കിൽ SDL_WAYLAND_CHECK_VERSION(1, 20, 0)
/* wayland-scanner 1.20 generates code that will call these, so these are
 * non-optional when we are compiling against Wayland 1.20. We don't
 * explicitly call them ourselves, though, so if we are only compiling
 * against Wayland 1.18, they're unnecessary. */
SDL_WAYLAND_SYM(ഘടന wl_proxy *, wl_proxy_marshal_flags, (ഘടന wl_proxy *proxy, uint32_t opcode, സ്ഥിരം ഘടന wl_interface *interface, uint32_t version, uint32_t flags, ...))
SDL_WAYLAND_SYM(ഘടന wl_proxy *, wl_proxy_marshal_array_flags, (ഘടന wl_proxy *proxy, uint32_t opcode, സ്ഥിരം ഘടന wl_interface *interface, uint32_t version,  uint32_t flags, സംഘം wl_argument *args))
#endif

#എങ്കിൽ SDL_WAYLAND_CHECK_VERSION(1, 23, 0) || defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC)
SDL_WAYLAND_SYM_OPT(ഘടന wl_event_queue *, wl_display_create_queue_with_name, (ഘടന wl_display *display, സ്ഥിരം അക്ഷരം *name))
#endif

#എങ്കിൽ 0 // TODO RECONNECT: See waylandvideo.c for more information!
#എങ്കിൽ SDL_WAYLAND_CHECK_VERSION(broken, on, purpose)
SDL_WAYLAND_SYM(പൂർണ്ണസംഖ്യ, wl_display_reconnect, (ഘടന wl_display *))
#endif
#endif // 0

SDL_WAYLAND_MODULE(WAYLAND_EGL)
SDL_WAYLAND_SYM(ഘടന wl_egl_window *, wl_egl_window_create, (ഘടന wl_surface *, പൂർണ്ണസംഖ്യ, പൂർണ്ണസംഖ്യ))
SDL_WAYLAND_SYM(ശൂന്യം, wl_egl_window_destroy, (ഘടന wl_egl_window *))
SDL_WAYLAND_SYM(ശൂന്യം, wl_egl_window_resize, (ഘടന wl_egl_window *, പൂർണ്ണസംഖ്യ, പൂർണ്ണസംഖ്യ, പൂർണ്ണസംഖ്യ, പൂർണ്ണസംഖ്യ))
SDL_WAYLAND_SYM(ശൂന്യം, wl_egl_window_get_attached_size, (ഘടന wl_egl_window *, പൂർണ്ണസംഖ്യ *, പൂർണ്ണസംഖ്യ *))

SDL_WAYLAND_MODULE(WAYLAND_CURSOR)
SDL_WAYLAND_SYM(ഘടന wl_cursor_theme *, wl_cursor_theme_load, (സ്ഥിരം അക്ഷരം *, പൂർണ്ണസംഖ്യ , ഘടന wl_shm *))
SDL_WAYLAND_SYM(ശൂന്യം, wl_cursor_theme_destroy, (ഘടന wl_cursor_theme *))
SDL_WAYLAND_SYM(ഘടന wl_cursor *, wl_cursor_theme_get_cursor, (ഘടന wl_cursor_theme *, സ്ഥിരം അക്ഷരം *))
SDL_WAYLAND_SYM(ഘടന wl_buffer *, wl_cursor_image_get_buffer, (ഘടന wl_cursor_image *))
SDL_WAYLAND_SYM(പൂർണ്ണസംഖ്യ, wl_cursor_frame, (ഘടന wl_cursor *, uint32_t))

SDL_WAYLAND_MODULE(WAYLAND_XKB)
SDL_WAYLAND_SYM(പൂർണ്ണസംഖ്യ, xkb_state_താക്കോൽ_get_syms, (ഘടന xkb_state *, xkb_keycode_t, സ്ഥിരം xkb_keysym_t **))
SDL_WAYLAND_SYM(പൂർണ്ണസംഖ്യ, xkb_keysym_to_utf8, (xkb_keysym_t, അക്ഷരം *, size_t) )
SDL_WAYLAND_SYM(ഘടന xkb_keymap *, xkb_keymap_new_from_string, (ഘടന xkb_context *, സ്ഥിരം അക്ഷരം *, എണ്ണൽ xkb_keymap_format, എണ്ണൽ xkb_keymap_compile_flags))
SDL_WAYLAND_SYM(ഘടന xkb_state *, xkb_state_new, (ഘടന xkb_keymap *) )
SDL_WAYLAND_SYM(പൂർണ്ണസംഖ്യ, xkb_keymap_താക്കോൽ_repeats, (ഘടന xkb_keymap *keymap, xkb_keycode_t താക്കോൽ) )
SDL_WAYLAND_SYM(ശൂന്യം, xkb_keymap_unref, (ഘടന xkb_keymap *) )
SDL_WAYLAND_SYM(ശൂന്യം, xkb_state_unref, (ഘടന xkb_state *) )
SDL_WAYLAND_SYM(ശൂന്യം, xkb_context_unref, (ഘടന xkb_context *) )
SDL_WAYLAND_SYM(ഘടന xkb_context *, xkb_context_new, (എണ്ണൽ xkb_context_flags flags) )
SDL_WAYLAND_SYM(എണ്ണൽ xkb_state_component, xkb_state_update_mask, (ഘടന xkb_state *state,\
                      xkb_mod_mask_t depressed_mods,\
                      xkb_mod_mask_t latched_mods,\
                      xkb_mod_mask_t locked_mods,\
                      xkb_layout_index_t depressed_layout,\
                      xkb_layout_index_t latched_layout,\
                      xkb_layout_index_t locked_layout) )
SDL_WAYLAND_SYM(ഘടന xkb_compose_table *, xkb_compose_table_new_from_locale, (ഘടന xkb_context *,\
                      സ്ഥിരം അക്ഷരം *locale, എണ്ണൽ xkb_compose_compile_flags) )
SDL_WAYLAND_SYM(ശൂന്യം, xkb_compose_state_reset, (ഘടന xkb_compose_state *) )
SDL_WAYLAND_SYM(ശൂന്യം, xkb_compose_table_unref, (ഘടന xkb_compose_table *) )
SDL_WAYLAND_SYM(ഘടന xkb_compose_state *, xkb_compose_state_new, (ഘടന xkb_compose_table *, എണ്ണൽ xkb_compose_state_flags) )
SDL_WAYLAND_SYM(ശൂന്യം, xkb_compose_state_unref, (ഘടന xkb_compose_state *) )
SDL_WAYLAND_SYM(എണ്ണൽ xkb_compose_feed_result, xkb_compose_state_feed, (ഘടന xkb_compose_state *, xkb_keysym_t) )
SDL_WAYLAND_SYM(എണ്ണൽ xkb_compose_status, xkb_compose_state_get_status, (ഘടന xkb_compose_state *) )
SDL_WAYLAND_SYM(xkb_keysym_t, xkb_compose_state_get_one_sym, (ഘടന xkb_compose_state *) )
SDL_WAYLAND_SYM(ശൂന്യം, xkb_keymap_താക്കോൽ_for_each, (ഘടന xkb_keymap *, xkb_keymap_താക്കോൽ_iter_t, ശൂന്യം *) )
SDL_WAYLAND_SYM(xkb_layout_index_t, xkb_keymap_അക്കം_layouts, (ഘടന xkb_keymap *) )
SDL_WAYLAND_SYM(പൂർണ്ണസംഖ്യ, xkb_keymap_താക്കോൽ_get_syms_by_level, (ഘടന xkb_keymap *, xkb_keycode_t, xkb_layout_index_t, xkb_level_index_t, സ്ഥിരം xkb_keysym_t **) )
SDL_WAYLAND_SYM(xkb_level_index_t, xkb_keymap_അക്കം_levels_for_താക്കോൽ, (ഘടന xkb_keymap *, xkb_keycode_t, xkb_layout_index_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keysym_to_utf32, (xkb_keysym_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keymap_mod_get_index, (ഘടന xkb_keymap *, സ്ഥിരം അക്ഷരം *) )
SDL_WAYLAND_SYM(സ്ഥിരം അക്ഷരം *, xkb_keymap_layout_get_name, (ഘടന xkb_keymap *, xkb_layout_index_t))

#എങ്കിൽ SDL_XKBCOMMON_CHECK_VERSION(1, 0, 0)
SDL_WAYLAND_SYM(size_t, xkb_keymap_താക്കോൽ_get_mods_for_level, (ഘടന xkb_keymap *, xkb_keycode_t, xkb_layout_index_t, xkb_level_index_t, xkb_mod_mask_t *, size_t) )
#അല്ലെങ്കിൽ
// Only needed in the fallback replacement for xkb_keymap_key_get_mods_for_level().
SDL_WAYLAND_SYM(xkb_level_index_t, xkb_state_താക്കോൽ_get_level, (ഘടന xkb_state *, xkb_keycode_t, xkb_layout_index_t) )
#endif

#എങ്കിൽ SDL_XKBCOMMON_CHECK_VERSION(1, 10, 0)
SDL_WAYLAND_SYM(xkb_mod_mask_t, xkb_keymap_mod_get_mask, (ഘടന xkb_keymap *, സ്ഥിരം അക്ഷരം *))
#endif

#ifdef HAVE_LIBDECOR_H
SDL_WAYLAND_MODULE(WAYLAND_LIBDECOR)

#എങ്കിൽ defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_VERSION(0, 3, 0)
#define SDL_libdecor_constsince03 സ്ഥിരം
#അല്ലെങ്കിൽ
#define SDL_libdecor_constsince03 /* nothing */
#endif

SDL_WAYLAND_SYM(ശൂന്യം, libdecor_unref, (ഘടന libdecor *))
SDL_WAYLAND_SYM(ഘടന libdecor *, libdecor_new, (ഘടന wl_display *,\
                                                  SDL_libdecor_constsince03 ഘടന libdecor_interface *))
SDL_WAYLAND_SYM(ഘടന libdecor_frame *, libdecor_decorate, (ഘടന libdecor *,\
                                                             ഘടന wl_surface *,\
                                                             SDL_libdecor_constsince03 ഘടന libdecor_frame_interface *,\
                                                             ശൂന്യം *))
SDL_WAYLAND_SYM(ശൂന്യം, libdecor_frame_unref, (ഘടന libdecor_frame *))
SDL_WAYLAND_SYM(ശൂന്യം, libdecor_frame_set_title, (ഘടന libdecor_frame *, സ്ഥിരം അക്ഷരം *))
SDL_WAYLAND_SYM(ശൂന്യം, libdecor_frame_set_app_id, (ഘടന libdecor_frame *, സ്ഥിരം അക്ഷരം *))
SDL_WAYLAND_SYM(ശൂന്യം, libdecor_frame_set_max_content_size, (ഘടന libdecor_frame *frame,\
                                                            പൂർണ്ണസംഖ്യ content_width,\
                                                            പൂർണ്ണസംഖ്യ content_height))
SDL_WAYLAND_SYM(ശൂന്യം, libdecor_frame_set_min_content_size, (ഘടന libdecor_frame *frame,\
                                                            പൂർണ്ണസംഖ്യ content_width,\
                                                            പൂർണ്ണസംഖ്യ content_height))
SDL_WAYLAND_SYM(ശൂന്യം, libdecor_frame_resize, (ഘടന libdecor_frame *,\
                                              ഘടന wl_seat *,\
                                              uint32_t,\
                                              എണ്ണൽ libdecor_resize_edge))
SDL_WAYLAND_SYM(ശൂന്യം, libdecor_frame_move, (ഘടന libdecor_frame *,\
                                            ഘടന wl_seat *,\
                                            uint32_t))
SDL_WAYLAND_SYM(ശൂന്യം, libdecor_frame_commit, (ഘടന libdecor_frame *,\
                                              ഘടന libdecor_state *,\
                                              ഘടന libdecor_configuration *))
SDL_WAYLAND_SYM(ശൂന്യം, libdecor_frame_set_minimized, (ഘടന libdecor_frame *))
SDL_WAYLAND_SYM(ശൂന്യം, libdecor_frame_set_maximized, (ഘടന libdecor_frame *))
SDL_WAYLAND_SYM(ശൂന്യം, libdecor_frame_unset_maximized, (ഘടന libdecor_frame *))
SDL_WAYLAND_SYM(ശൂന്യം, libdecor_frame_set_fullscreen, (ഘടന libdecor_frame *, ഘടന wl_output *))
SDL_WAYLAND_SYM(ശൂന്യം, libdecor_frame_unset_fullscreen, (ഘടന libdecor_frame *))
SDL_WAYLAND_SYM(ശൂന്യം, libdecor_frame_set_capabilities, (ഘടന libdecor_frame *, \
                                                        എണ്ണൽ libdecor_capabilities))
SDL_WAYLAND_SYM(ശൂന്യം, libdecor_frame_unset_capabilities, (ഘടന libdecor_frame *, \
                                                          എണ്ണൽ libdecor_capabilities))
SDL_WAYLAND_SYM(bool, libdecor_frame_has_capability, (ഘടന libdecor_frame *, \
                                                      എണ്ണൽ libdecor_capabilities))
SDL_WAYLAND_SYM(ശൂന്യം, libdecor_frame_set_visibility, (ഘടന libdecor_frame *, bool))
SDL_WAYLAND_SYM(bool, libdecor_frame_is_visible, (ഘടന libdecor_frame *))
SDL_WAYLAND_SYM(bool, libdecor_frame_is_floating, (ഘടന libdecor_frame *))
SDL_WAYLAND_SYM(ശൂന്യം, libdecor_frame_set_parent, (ഘടന libdecor_frame *,\
                                                  ഘടന libdecor_frame *))
SDL_WAYLAND_SYM(ശൂന്യം, libdecor_frame_show_window_menu, (ഘടന libdecor_frame *, ഘടന wl_seat *, uint32_t, പൂർണ്ണസംഖ്യ, പൂർണ്ണസംഖ്യ))
SDL_WAYLAND_SYM(ഘടന xdg_surface *, libdecor_frame_get_xdg_surface, (ഘടന libdecor_frame *))
SDL_WAYLAND_SYM(ഘടന xdg_toplevel *, libdecor_frame_get_xdg_toplevel, (ഘടന libdecor_frame *))
SDL_WAYLAND_SYM(ശൂന്യം, libdecor_frame_translate_coordinate, (ഘടന libdecor_frame *, പൂർണ്ണസംഖ്യ, പൂർണ്ണസംഖ്യ, പൂർണ്ണസംഖ്യ *, പൂർണ്ണസംഖ്യ *))
SDL_WAYLAND_SYM(ശൂന്യം, libdecor_frame_map, (ഘടന libdecor_frame *))
SDL_WAYLAND_SYM(ഘടന libdecor_state *, libdecor_state_new, (പൂർണ്ണസംഖ്യ, പൂർണ്ണസംഖ്യ))
SDL_WAYLAND_SYM(ശൂന്യം, libdecor_state_free, (ഘടന libdecor_state *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_content_size, (ഘടന libdecor_configuration *,\
                                                                ഘടന libdecor_frame *,\
                                                                പൂർണ്ണസംഖ്യ *,\
                                                                പൂർണ്ണസംഖ്യ *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_window_state, (ഘടന libdecor_configuration *,\
                                                                എണ്ണൽ libdecor_window_state *))
SDL_WAYLAND_SYM(പൂർണ്ണസംഖ്യ, libdecor_dispatch, (ഘടന libdecor *, പൂർണ്ണസംഖ്യ))

#എങ്കിൽ defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_VERSION(0, 2, 0)
// Only found in libdecor 0.1.1 or higher, so failure to load them is not fatal.
SDL_WAYLAND_SYM_OPT(ശൂന്യം, libdecor_frame_get_min_content_size, (സ്ഥിരം ഘടന libdecor_frame *,\
                                                            പൂർണ്ണസംഖ്യ *,\
                                                            പൂർണ്ണസംഖ്യ *))
SDL_WAYLAND_SYM_OPT(ശൂന്യം, libdecor_frame_get_max_content_size, (സ്ഥിരം ഘടന libdecor_frame *,\
                                                            പൂർണ്ണസംഖ്യ *,\
                                                            പൂർണ്ണസംഖ്യ *))
#endif

#എങ്കിൽ defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_VERSION(0, 3, 0)
SDL_WAYLAND_SYM_OPT(എണ്ണൽ libdecor_wm_capabilities, libdecor_frame_get_wm_capabilities, (ഘടന libdecor_frame *))
#endif

#undef SDL_libdecor_constsince03

#endif

#undef SDL_WAYLAND_MODULE
#undef SDL_WAYLAND_SYM
#undef SDL_WAYLAND_SYM_OPT

/* *INDENT-ON* */ // clang-format on
