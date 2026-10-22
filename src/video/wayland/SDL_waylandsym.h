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
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_proxy_marshal, (ಸಂರಚನಾ wl_proxy *, uint32_t, ...))
SDL_WAYLAND_SYM(ಸಂರಚನಾ wl_proxy *, wl_proxy_create, (ಸಂರಚನಾ wl_proxy *, ಧ್ರುವ ಸಂರಚನಾ wl_interface *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_proxy_destroy, (ಸಂರಚನಾ wl_proxy *))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಙ್ಕ, wl_proxy_add_listener, (ಸಂರಚನಾ wl_proxy *, ಶೂನ್ಯ (**)(ಶೂನ್ಯ), ಶೂನ್ಯ *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_proxy_set_user_data, (ಸಂರಚನಾ wl_proxy *, ಶೂನ್ಯ *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ *, wl_proxy_get_user_data, (ಸಂರಚನಾ wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_version, (ಸಂರಚನಾ wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_id, (ಸಂರಚನಾ wl_proxy *))
SDL_WAYLAND_SYM(ಧ್ರುವ ವರ್ಣ *, wl_proxy_get_class, (ಸಂರಚನಾ wl_proxy *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_proxy_set_queue, (ಸಂರಚನಾ wl_proxy *, ಸಂರಚನಾ wl_event_queue *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ *, wl_proxy_create_wrapper, (ಶೂನ್ಯ *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_proxy_wrapper_destroy, (ಶೂನ್ಯ *))
SDL_WAYLAND_SYM(ಸಂರಚನಾ wl_display *, wl_display_connect, (ಧ್ರುವ ವರ್ಣ *))
SDL_WAYLAND_SYM(ಸಂರಚನಾ wl_display *, wl_display_connect_to_fd, (ಪೂರ್ಣಾಙ್ಕ))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_display_disconnect, (ಸಂರಚನಾ wl_display *))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಙ್ಕ, wl_display_get_fd, (ಸಂರಚನಾ wl_display *))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಙ್ಕ, wl_display_dispatch, (ಸಂರಚನಾ wl_display *))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಙ್ಕ, wl_display_dispatch_queue, (ಸಂರಚನಾ wl_display *, ಸಂರಚನಾ wl_event_queue *))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಙ್ಕ, wl_display_dispatch_queue_pending, (ಸಂರಚನಾ wl_display *, ಸಂರಚನಾ wl_event_queue *))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಙ್ಕ, wl_display_dispatch_pending, (ಸಂರಚನಾ wl_display *))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಙ್ಕ, wl_display_prepare_read, (ಸಂರಚನಾ wl_display *))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಙ್ಕ, wl_display_prepare_read_queue, (ಸಂರಚನಾ wl_display *, ಸಂರಚನಾ wl_event_queue *))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಙ್ಕ, wl_display_read_events, (ಸಂರಚನಾ wl_display *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_display_cancel_read, (ಸಂರಚನಾ wl_display *))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಙ್ಕ, wl_display_get_error, (ಸಂರಚನಾ wl_display *))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಙ್ಕ, wl_display_flush, (ಸಂರಚನಾ wl_display *))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಙ್ಕ, wl_display_roundtrip, (ಸಂರಚನಾ wl_display *))
SDL_WAYLAND_SYM(ಸಂರಚನಾ wl_event_queue *, wl_display_create_queue, (ಸಂರಚನಾ wl_display *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_event_queue_destroy, (ಸಂರಚನಾ wl_event_queue *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_log_set_handler_client, (wl_log_func_t))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_list_init, (ಸಂರಚನಾ wl_list *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_list_ಸೇರಿಸು, (ಸಂರಚನಾ wl_list *, ಸಂರಚನಾ wl_list *) )
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_list_remove, (ಸಂರಚನಾ wl_list *))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಙ್ಕ, wl_list_length, (ಧ್ರುವ ಸಂರಚನಾ wl_list *))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಙ್ಕ, wl_list_empty, (ಧ್ರುವ ಸಂರಚನಾ wl_list *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_list_ಸೇರಿಸು_list, (ಸಂರಚನಾ wl_list *, ಸಂರಚನಾ wl_list *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_array_init, (ಸಂರಚನಾ wl_array *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_array_release, (ಸಂರಚನಾ wl_array *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ *, wl_array_add, (ಸಂರಚನಾ wl_array *, size_t))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಙ್ಕ, wl_array_copy, (ಸಂರಚನಾ wl_array *, ಸಂರಚನಾ wl_array *))
SDL_WAYLAND_SYM(ಸಂರಚನಾ wl_proxy *, wl_proxy_marshal_constructor, (ಸಂರಚನಾ wl_proxy *, uint32_t opcode, ಧ್ರುವ ಸಂರಚನಾ wl_interface *interface, ...))
SDL_WAYLAND_SYM(ಸಂರಚನಾ wl_proxy *, wl_proxy_marshal_constructor_versioned, (ಸಂರಚನಾ wl_proxy *proxy, uint32_t opcode, ಧ್ರುವ ಸಂರಚನಾ wl_interface *interface, uint32_t version, ...))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_proxy_set_tag, (ಸಂರಚನಾ wl_proxy *, ಧ್ರುವ ವರ್ಣ * ಧ್ರುವ *))
SDL_WAYLAND_SYM(ಧ್ರುವ ವರ್ಣ * ಧ್ರುವ *, wl_proxy_get_tag, (ಸಂರಚನಾ wl_proxy *))

#ಯದಿ SDL_WAYLAND_CHECK_VERSION(1, 20, 0)
/* wayland-scanner 1.20 generates code that will call these, so these are
 * non-optional when we are compiling against Wayland 1.20. We don't
 * explicitly call them ourselves, though, so if we are only compiling
 * against Wayland 1.18, they're unnecessary. */
SDL_WAYLAND_SYM(ಸಂರಚನಾ wl_proxy *, wl_proxy_marshal_flags, (ಸಂರಚನಾ wl_proxy *proxy, uint32_t opcode, ಧ್ರುವ ಸಂರಚನಾ wl_interface *interface, uint32_t version, uint32_t flags, ...))
SDL_WAYLAND_SYM(ಸಂರಚನಾ wl_proxy *, wl_proxy_marshal_array_flags, (ಸಂರಚನಾ wl_proxy *proxy, uint32_t opcode, ಧ್ರುವ ಸಂರಚನಾ wl_interface *interface, uint32_t version,  uint32_t flags, ಸಙ್ಘ wl_argument *args))
#endif

#ಯದಿ SDL_WAYLAND_CHECK_VERSION(1, 23, 0) || defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC)
SDL_WAYLAND_SYM_OPT(ಸಂರಚನಾ wl_event_queue *, wl_display_create_queue_with_name, (ಸಂರಚನಾ wl_display *display, ಧ್ರುವ ವರ್ಣ *name))
#endif

#ಯದಿ 0 // TODO RECONNECT: See waylandvideo.c for more information!
#ಯದಿ SDL_WAYLAND_CHECK_VERSION(broken, on, purpose)
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಙ್ಕ, wl_display_reconnect, (ಸಂರಚನಾ wl_display *))
#endif
#endif // 0

SDL_WAYLAND_MODULE(WAYLAND_EGL)
SDL_WAYLAND_SYM(ಸಂರಚನಾ wl_egl_window *, wl_egl_window_create, (ಸಂರಚನಾ wl_surface *, ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_egl_window_destroy, (ಸಂರಚನಾ wl_egl_window *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_egl_window_resize, (ಸಂರಚನಾ wl_egl_window *, ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_egl_window_get_attached_size, (ಸಂರಚನಾ wl_egl_window *, ಪೂರ್ಣಾಙ್ಕ *, ಪೂರ್ಣಾಙ್ಕ *))

SDL_WAYLAND_MODULE(WAYLAND_CURSOR)
SDL_WAYLAND_SYM(ಸಂರಚನಾ wl_cursor_theme *, wl_cursor_theme_load, (ಧ್ರುವ ವರ್ಣ *, ಪೂರ್ಣಾಙ್ಕ , ಸಂರಚನಾ wl_shm *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_cursor_theme_destroy, (ಸಂರಚನಾ wl_cursor_theme *))
SDL_WAYLAND_SYM(ಸಂರಚನಾ wl_cursor *, wl_cursor_theme_get_cursor, (ಸಂರಚನಾ wl_cursor_theme *, ಧ್ರುವ ವರ್ಣ *))
SDL_WAYLAND_SYM(ಸಂರಚನಾ wl_buffer *, wl_cursor_image_get_buffer, (ಸಂರಚನಾ wl_cursor_image *))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಙ್ಕ, wl_cursor_frame, (ಸಂರಚನಾ wl_cursor *, uint32_t))

SDL_WAYLAND_MODULE(WAYLAND_XKB)
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಙ್ಕ, xkb_state_ಕೀಲಿ_get_syms, (ಸಂರಚನಾ xkb_state *, xkb_keycode_t, ಧ್ರುವ xkb_keysym_t **))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಙ್ಕ, xkb_keysym_to_utf8, (xkb_keysym_t, ವರ್ಣ *, size_t) )
SDL_WAYLAND_SYM(ಸಂರಚನಾ xkb_keymap *, xkb_keymap_new_from_string, (ಸಂರಚನಾ xkb_context *, ಧ್ರುವ ವರ್ಣ *, ಗಣನಾ xkb_keymap_format, ಗಣನಾ xkb_keymap_compile_flags))
SDL_WAYLAND_SYM(ಸಂರಚನಾ xkb_state *, xkb_state_new, (ಸಂರಚನಾ xkb_keymap *) )
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಙ್ಕ, xkb_keymap_ಕೀಲಿ_repeats, (ಸಂರಚನಾ xkb_keymap *keymap, xkb_keycode_t ಕೀಲಿ) )
SDL_WAYLAND_SYM(ಶೂನ್ಯ, xkb_keymap_unref, (ಸಂರಚನಾ xkb_keymap *) )
SDL_WAYLAND_SYM(ಶೂನ್ಯ, xkb_state_unref, (ಸಂರಚನಾ xkb_state *) )
SDL_WAYLAND_SYM(ಶೂನ್ಯ, xkb_context_unref, (ಸಂರಚನಾ xkb_context *) )
SDL_WAYLAND_SYM(ಸಂರಚನಾ xkb_context *, xkb_context_new, (ಗಣನಾ xkb_context_flags flags) )
SDL_WAYLAND_SYM(ಗಣನಾ xkb_state_component, xkb_state_update_mask, (ಸಂರಚನಾ xkb_state *state,\
                      xkb_mod_mask_t depressed_mods,\
                      xkb_mod_mask_t latched_mods,\
                      xkb_mod_mask_t locked_mods,\
                      xkb_layout_index_t depressed_layout,\
                      xkb_layout_index_t latched_layout,\
                      xkb_layout_index_t locked_layout) )
SDL_WAYLAND_SYM(ಸಂರಚನಾ xkb_compose_table *, xkb_compose_table_new_from_locale, (ಸಂರಚನಾ xkb_context *,\
                      ಧ್ರುವ ವರ್ಣ *locale, ಗಣನಾ xkb_compose_compile_flags) )
SDL_WAYLAND_SYM(ಶೂನ್ಯ, xkb_compose_state_reset, (ಸಂರಚನಾ xkb_compose_state *) )
SDL_WAYLAND_SYM(ಶೂನ್ಯ, xkb_compose_table_unref, (ಸಂರಚನಾ xkb_compose_table *) )
SDL_WAYLAND_SYM(ಸಂರಚನಾ xkb_compose_state *, xkb_compose_state_new, (ಸಂರಚನಾ xkb_compose_table *, ಗಣನಾ xkb_compose_state_flags) )
SDL_WAYLAND_SYM(ಶೂನ್ಯ, xkb_compose_state_unref, (ಸಂರಚನಾ xkb_compose_state *) )
SDL_WAYLAND_SYM(ಗಣನಾ xkb_compose_feed_result, xkb_compose_state_feed, (ಸಂರಚನಾ xkb_compose_state *, xkb_keysym_t) )
SDL_WAYLAND_SYM(ಗಣನಾ xkb_compose_status, xkb_compose_state_get_status, (ಸಂರಚನಾ xkb_compose_state *) )
SDL_WAYLAND_SYM(xkb_keysym_t, xkb_compose_state_get_one_sym, (ಸಂರಚನಾ xkb_compose_state *) )
SDL_WAYLAND_SYM(ಶೂನ್ಯ, xkb_keymap_ಕೀಲಿ_for_each, (ಸಂರಚನಾ xkb_keymap *, xkb_keymap_ಕೀಲಿ_iter_t, ಶೂನ್ಯ *) )
SDL_WAYLAND_SYM(xkb_layout_index_t, xkb_keymap_ಅಂಕೆ_layouts, (ಸಂರಚನಾ xkb_keymap *) )
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಙ್ಕ, xkb_keymap_ಕೀಲಿ_get_syms_by_level, (ಸಂರಚನಾ xkb_keymap *, xkb_keycode_t, xkb_layout_index_t, xkb_level_index_t, ಧ್ರುವ xkb_keysym_t **) )
SDL_WAYLAND_SYM(xkb_level_index_t, xkb_keymap_ಅಂಕೆ_levels_for_ಕೀಲಿ, (ಸಂರಚನಾ xkb_keymap *, xkb_keycode_t, xkb_layout_index_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keysym_to_utf32, (xkb_keysym_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keymap_mod_get_index, (ಸಂರಚನಾ xkb_keymap *, ಧ್ರುವ ವರ್ಣ *) )
SDL_WAYLAND_SYM(ಧ್ರುವ ವರ್ಣ *, xkb_keymap_layout_get_name, (ಸಂರಚನಾ xkb_keymap *, xkb_layout_index_t))

#ಯದಿ SDL_XKBCOMMON_CHECK_VERSION(1, 0, 0)
SDL_WAYLAND_SYM(size_t, xkb_keymap_ಕೀಲಿ_get_mods_for_level, (ಸಂರಚನಾ xkb_keymap *, xkb_keycode_t, xkb_layout_index_t, xkb_level_index_t, xkb_mod_mask_t *, size_t) )
#ಅನ್ಯಥಾ
// Only needed in the fallback replacement for xkb_keymap_key_get_mods_for_level().
SDL_WAYLAND_SYM(xkb_level_index_t, xkb_state_ಕೀಲಿ_get_level, (ಸಂರಚನಾ xkb_state *, xkb_keycode_t, xkb_layout_index_t) )
#endif

#ಯದಿ SDL_XKBCOMMON_CHECK_VERSION(1, 10, 0)
SDL_WAYLAND_SYM(xkb_mod_mask_t, xkb_keymap_mod_get_mask, (ಸಂರಚನಾ xkb_keymap *, ಧ್ರುವ ವರ್ಣ *))
#endif

#ifdef HAVE_LIBDECOR_H
SDL_WAYLAND_MODULE(WAYLAND_LIBDECOR)

#ಯದಿ defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_VERSION(0, 3, 0)
#define SDL_libdecor_constsince03 ಧ್ರುವ
#ಅನ್ಯಥಾ
#define SDL_libdecor_constsince03 /* nothing */
#endif

SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_unref, (ಸಂರಚನಾ libdecor *))
SDL_WAYLAND_SYM(ಸಂರಚನಾ libdecor *, libdecor_new, (ಸಂರಚನಾ wl_display *,\
                                                  SDL_libdecor_constsince03 ಸಂರಚನಾ libdecor_interface *))
SDL_WAYLAND_SYM(ಸಂರಚನಾ libdecor_frame *, libdecor_decorate, (ಸಂರಚನಾ libdecor *,\
                                                             ಸಂರಚನಾ wl_surface *,\
                                                             SDL_libdecor_constsince03 ಸಂರಚನಾ libdecor_frame_interface *,\
                                                             ಶೂನ್ಯ *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_frame_unref, (ಸಂರಚನಾ libdecor_frame *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_frame_set_title, (ಸಂರಚನಾ libdecor_frame *, ಧ್ರುವ ವರ್ಣ *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_frame_set_app_id, (ಸಂರಚನಾ libdecor_frame *, ಧ್ರುವ ವರ್ಣ *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_frame_set_max_content_size, (ಸಂರಚನಾ libdecor_frame *frame,\
                                                            ಪೂರ್ಣಾಙ್ಕ content_width,\
                                                            ಪೂರ್ಣಾಙ್ಕ content_height))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_frame_set_min_content_size, (ಸಂರಚನಾ libdecor_frame *frame,\
                                                            ಪೂರ್ಣಾಙ್ಕ content_width,\
                                                            ಪೂರ್ಣಾಙ್ಕ content_height))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_frame_resize, (ಸಂರಚನಾ libdecor_frame *,\
                                              ಸಂರಚನಾ wl_seat *,\
                                              uint32_t,\
                                              ಗಣನಾ libdecor_resize_edge))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_frame_move, (ಸಂರಚನಾ libdecor_frame *,\
                                            ಸಂರಚನಾ wl_seat *,\
                                            uint32_t))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_frame_commit, (ಸಂರಚನಾ libdecor_frame *,\
                                              ಸಂರಚನಾ libdecor_state *,\
                                              ಸಂರಚನಾ libdecor_configuration *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_frame_set_minimized, (ಸಂರಚನಾ libdecor_frame *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_frame_set_maximized, (ಸಂರಚನಾ libdecor_frame *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_frame_unset_maximized, (ಸಂರಚನಾ libdecor_frame *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_frame_set_fullscreen, (ಸಂರಚನಾ libdecor_frame *, ಸಂರಚನಾ wl_output *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_frame_unset_fullscreen, (ಸಂರಚನಾ libdecor_frame *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_frame_set_capabilities, (ಸಂರಚನಾ libdecor_frame *, \
                                                        ಗಣನಾ libdecor_capabilities))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_frame_unset_capabilities, (ಸಂರಚನಾ libdecor_frame *, \
                                                          ಗಣನಾ libdecor_capabilities))
SDL_WAYLAND_SYM(bool, libdecor_frame_has_capability, (ಸಂರಚನಾ libdecor_frame *, \
                                                      ಗಣನಾ libdecor_capabilities))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_frame_set_visibility, (ಸಂರಚನಾ libdecor_frame *, bool))
SDL_WAYLAND_SYM(bool, libdecor_frame_is_visible, (ಸಂರಚನಾ libdecor_frame *))
SDL_WAYLAND_SYM(bool, libdecor_frame_is_floating, (ಸಂರಚನಾ libdecor_frame *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_frame_set_parent, (ಸಂರಚನಾ libdecor_frame *,\
                                                  ಸಂರಚನಾ libdecor_frame *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_frame_show_window_menu, (ಸಂರಚನಾ libdecor_frame *, ಸಂರಚನಾ wl_seat *, uint32_t, ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ))
SDL_WAYLAND_SYM(ಸಂರಚನಾ xdg_surface *, libdecor_frame_get_xdg_surface, (ಸಂರಚನಾ libdecor_frame *))
SDL_WAYLAND_SYM(ಸಂರಚನಾ xdg_toplevel *, libdecor_frame_get_xdg_toplevel, (ಸಂರಚನಾ libdecor_frame *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_frame_translate_coordinate, (ಸಂರಚನಾ libdecor_frame *, ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ *, ಪೂರ್ಣಾಙ್ಕ *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_frame_map, (ಸಂರಚನಾ libdecor_frame *))
SDL_WAYLAND_SYM(ಸಂರಚನಾ libdecor_state *, libdecor_state_new, (ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_state_free, (ಸಂರಚನಾ libdecor_state *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_content_size, (ಸಂರಚನಾ libdecor_configuration *,\
                                                                ಸಂರಚನಾ libdecor_frame *,\
                                                                ಪೂರ್ಣಾಙ್ಕ *,\
                                                                ಪೂರ್ಣಾಙ್ಕ *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_window_state, (ಸಂರಚನಾ libdecor_configuration *,\
                                                                ಗಣನಾ libdecor_window_state *))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಙ್ಕ, libdecor_dispatch, (ಸಂರಚನಾ libdecor *, ಪೂರ್ಣಾಙ್ಕ))

#ಯದಿ defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_VERSION(0, 2, 0)
// Only found in libdecor 0.1.1 or higher, so failure to load them is not fatal.
SDL_WAYLAND_SYM_OPT(ಶೂನ್ಯ, libdecor_frame_get_min_content_size, (ಧ್ರುವ ಸಂರಚನಾ libdecor_frame *,\
                                                            ಪೂರ್ಣಾಙ್ಕ *,\
                                                            ಪೂರ್ಣಾಙ್ಕ *))
SDL_WAYLAND_SYM_OPT(ಶೂನ್ಯ, libdecor_frame_get_max_content_size, (ಧ್ರುವ ಸಂರಚನಾ libdecor_frame *,\
                                                            ಪೂರ್ಣಾಙ್ಕ *,\
                                                            ಪೂರ್ಣಾಙ್ಕ *))
#endif

#ಯದಿ defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_VERSION(0, 3, 0)
SDL_WAYLAND_SYM_OPT(ಗಣನಾ libdecor_wm_capabilities, libdecor_frame_get_wm_capabilities, (ಸಂರಚನಾ libdecor_frame *))
#endif

#undef SDL_libdecor_constsince03

#endif

#undef SDL_WAYLAND_MODULE
#undef SDL_WAYLAND_SYM
#undef SDL_WAYLAND_SYM_OPT

/* *INDENT-ON* */ // clang-format on
