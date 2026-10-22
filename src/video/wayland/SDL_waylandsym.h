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
SDL_WAYLAND_SYM(வெறுமை, wl_proxy_marshal, (கட்டமைப்பு wl_proxy *, uint32_t, ...))
SDL_WAYLAND_SYM(கட்டமைப்பு wl_proxy *, wl_proxy_create, (கட்டமைப்பு wl_proxy *, மாறிலி கட்டமைப்பு wl_interface *))
SDL_WAYLAND_SYM(வெறுமை, wl_proxy_destroy, (கட்டமைப்பு wl_proxy *))
SDL_WAYLAND_SYM(முழு, wl_proxy_add_listener, (கட்டமைப்பு wl_proxy *, வெறுமை (**)(வெறுமை), வெறுமை *))
SDL_WAYLAND_SYM(வெறுமை, wl_proxy_set_user_data, (கட்டமைப்பு wl_proxy *, வெறுமை *))
SDL_WAYLAND_SYM(வெறுமை *, wl_proxy_get_user_data, (கட்டமைப்பு wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_version, (கட்டமைப்பு wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_id, (கட்டமைப்பு wl_proxy *))
SDL_WAYLAND_SYM(மாறிலி எழுத்து *, wl_proxy_get_class, (கட்டமைப்பு wl_proxy *))
SDL_WAYLAND_SYM(வெறுமை, wl_proxy_set_queue, (கட்டமைப்பு wl_proxy *, கட்டமைப்பு wl_event_queue *))
SDL_WAYLAND_SYM(வெறுமை *, wl_proxy_create_wrapper, (வெறுமை *))
SDL_WAYLAND_SYM(வெறுமை, wl_proxy_wrapper_destroy, (வெறுமை *))
SDL_WAYLAND_SYM(கட்டமைப்பு wl_display *, wl_display_connect, (மாறிலி எழுத்து *))
SDL_WAYLAND_SYM(கட்டமைப்பு wl_display *, wl_display_connect_to_fd, (முழு))
SDL_WAYLAND_SYM(வெறுமை, wl_display_disconnect, (கட்டமைப்பு wl_display *))
SDL_WAYLAND_SYM(முழு, wl_display_get_fd, (கட்டமைப்பு wl_display *))
SDL_WAYLAND_SYM(முழு, wl_display_dispatch, (கட்டமைப்பு wl_display *))
SDL_WAYLAND_SYM(முழு, wl_display_dispatch_queue, (கட்டமைப்பு wl_display *, கட்டமைப்பு wl_event_queue *))
SDL_WAYLAND_SYM(முழு, wl_display_dispatch_queue_pending, (கட்டமைப்பு wl_display *, கட்டமைப்பு wl_event_queue *))
SDL_WAYLAND_SYM(முழு, wl_display_dispatch_pending, (கட்டமைப்பு wl_display *))
SDL_WAYLAND_SYM(முழு, wl_display_prepare_read, (கட்டமைப்பு wl_display *))
SDL_WAYLAND_SYM(முழு, wl_display_prepare_read_queue, (கட்டமைப்பு wl_display *, கட்டமைப்பு wl_event_queue *))
SDL_WAYLAND_SYM(முழு, wl_display_read_events, (கட்டமைப்பு wl_display *))
SDL_WAYLAND_SYM(வெறுமை, wl_display_cancel_read, (கட்டமைப்பு wl_display *))
SDL_WAYLAND_SYM(முழு, wl_display_get_error, (கட்டமைப்பு wl_display *))
SDL_WAYLAND_SYM(முழு, wl_display_flush, (கட்டமைப்பு wl_display *))
SDL_WAYLAND_SYM(முழு, wl_display_roundtrip, (கட்டமைப்பு wl_display *))
SDL_WAYLAND_SYM(கட்டமைப்பு wl_event_queue *, wl_display_create_queue, (கட்டமைப்பு wl_display *))
SDL_WAYLAND_SYM(வெறுமை, wl_event_queue_destroy, (கட்டமைப்பு wl_event_queue *))
SDL_WAYLAND_SYM(வெறுமை, wl_log_set_handler_client, (wl_log_func_t))
SDL_WAYLAND_SYM(வெறுமை, wl_list_init, (கட்டமைப்பு wl_list *))
SDL_WAYLAND_SYM(வெறுமை, wl_list_செருகு, (கட்டமைப்பு wl_list *, கட்டமைப்பு wl_list *) )
SDL_WAYLAND_SYM(வெறுமை, wl_list_remove, (கட்டமைப்பு wl_list *))
SDL_WAYLAND_SYM(முழு, wl_list_length, (மாறிலி கட்டமைப்பு wl_list *))
SDL_WAYLAND_SYM(முழு, wl_list_empty, (மாறிலி கட்டமைப்பு wl_list *))
SDL_WAYLAND_SYM(வெறுமை, wl_list_செருகு_list, (கட்டமைப்பு wl_list *, கட்டமைப்பு wl_list *))
SDL_WAYLAND_SYM(வெறுமை, wl_array_init, (கட்டமைப்பு wl_array *))
SDL_WAYLAND_SYM(வெறுமை, wl_array_release, (கட்டமைப்பு wl_array *))
SDL_WAYLAND_SYM(வெறுமை *, wl_array_add, (கட்டமைப்பு wl_array *, size_t))
SDL_WAYLAND_SYM(முழு, wl_array_copy, (கட்டமைப்பு wl_array *, கட்டமைப்பு wl_array *))
SDL_WAYLAND_SYM(கட்டமைப்பு wl_proxy *, wl_proxy_marshal_constructor, (கட்டமைப்பு wl_proxy *, uint32_t opcode, மாறிலி கட்டமைப்பு wl_interface *interface, ...))
SDL_WAYLAND_SYM(கட்டமைப்பு wl_proxy *, wl_proxy_marshal_constructor_versioned, (கட்டமைப்பு wl_proxy *proxy, uint32_t opcode, மாறிலி கட்டமைப்பு wl_interface *interface, uint32_t version, ...))
SDL_WAYLAND_SYM(வெறுமை, wl_proxy_set_tag, (கட்டமைப்பு wl_proxy *, மாறிலி எழுத்து * மாறிலி *))
SDL_WAYLAND_SYM(மாறிலி எழுத்து * மாறிலி *, wl_proxy_get_tag, (கட்டமைப்பு wl_proxy *))

#எனில் SDL_WAYLAND_CHECK_VERSION(1, 20, 0)
/* wayland-scanner 1.20 generates code that will call these, so these are
 * non-optional when we are compiling against Wayland 1.20. We don't
 * explicitly call them ourselves, though, so if we are only compiling
 * against Wayland 1.18, they're unnecessary. */
SDL_WAYLAND_SYM(கட்டமைப்பு wl_proxy *, wl_proxy_marshal_flags, (கட்டமைப்பு wl_proxy *proxy, uint32_t opcode, மாறிலி கட்டமைப்பு wl_interface *interface, uint32_t version, uint32_t flags, ...))
SDL_WAYLAND_SYM(கட்டமைப்பு wl_proxy *, wl_proxy_marshal_array_flags, (கட்டமைப்பு wl_proxy *proxy, uint32_t opcode, மாறிலி கட்டமைப்பு wl_interface *interface, uint32_t version,  uint32_t flags, ஒன்றிப்பு wl_argument *args))
#endif

#எனில் SDL_WAYLAND_CHECK_VERSION(1, 23, 0) || defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC)
SDL_WAYLAND_SYM_OPT(கட்டமைப்பு wl_event_queue *, wl_display_create_queue_with_name, (கட்டமைப்பு wl_display *display, மாறிலி எழுத்து *name))
#endif

#எனில் 0 // TODO RECONNECT: See waylandvideo.c for more information!
#எனில் SDL_WAYLAND_CHECK_VERSION(broken, on, purpose)
SDL_WAYLAND_SYM(முழு, wl_display_reconnect, (கட்டமைப்பு wl_display *))
#endif
#endif // 0

SDL_WAYLAND_MODULE(WAYLAND_EGL)
SDL_WAYLAND_SYM(கட்டமைப்பு wl_egl_window *, wl_egl_window_create, (கட்டமைப்பு wl_surface *, முழு, முழு))
SDL_WAYLAND_SYM(வெறுமை, wl_egl_window_destroy, (கட்டமைப்பு wl_egl_window *))
SDL_WAYLAND_SYM(வெறுமை, wl_egl_window_resize, (கட்டமைப்பு wl_egl_window *, முழு, முழு, முழு, முழு))
SDL_WAYLAND_SYM(வெறுமை, wl_egl_window_get_attached_size, (கட்டமைப்பு wl_egl_window *, முழு *, முழு *))

SDL_WAYLAND_MODULE(WAYLAND_CURSOR)
SDL_WAYLAND_SYM(கட்டமைப்பு wl_cursor_theme *, wl_cursor_theme_load, (மாறிலி எழுத்து *, முழு , கட்டமைப்பு wl_shm *))
SDL_WAYLAND_SYM(வெறுமை, wl_cursor_theme_destroy, (கட்டமைப்பு wl_cursor_theme *))
SDL_WAYLAND_SYM(கட்டமைப்பு wl_cursor *, wl_cursor_theme_get_cursor, (கட்டமைப்பு wl_cursor_theme *, மாறிலி எழுத்து *))
SDL_WAYLAND_SYM(கட்டமைப்பு wl_buffer *, wl_cursor_image_get_buffer, (கட்டமைப்பு wl_cursor_image *))
SDL_WAYLAND_SYM(முழு, wl_cursor_frame, (கட்டமைப்பு wl_cursor *, uint32_t))

SDL_WAYLAND_MODULE(WAYLAND_XKB)
SDL_WAYLAND_SYM(முழு, xkb_state_சாவி_get_syms, (கட்டமைப்பு xkb_state *, xkb_keycode_t, மாறிலி xkb_keysym_t **))
SDL_WAYLAND_SYM(முழு, xkb_keysym_to_utf8, (xkb_keysym_t, எழுத்து *, size_t) )
SDL_WAYLAND_SYM(கட்டமைப்பு xkb_keymap *, xkb_keymap_new_from_string, (கட்டமைப்பு xkb_context *, மாறிலி எழுத்து *, எண்ணிக்கை xkb_keymap_format, எண்ணிக்கை xkb_keymap_compile_flags))
SDL_WAYLAND_SYM(கட்டமைப்பு xkb_state *, xkb_state_new, (கட்டமைப்பு xkb_keymap *) )
SDL_WAYLAND_SYM(முழு, xkb_keymap_சாவி_repeats, (கட்டமைப்பு xkb_keymap *keymap, xkb_keycode_t சாவி) )
SDL_WAYLAND_SYM(வெறுமை, xkb_keymap_unref, (கட்டமைப்பு xkb_keymap *) )
SDL_WAYLAND_SYM(வெறுமை, xkb_state_unref, (கட்டமைப்பு xkb_state *) )
SDL_WAYLAND_SYM(வெறுமை, xkb_context_unref, (கட்டமைப்பு xkb_context *) )
SDL_WAYLAND_SYM(கட்டமைப்பு xkb_context *, xkb_context_new, (எண்ணிக்கை xkb_context_flags flags) )
SDL_WAYLAND_SYM(எண்ணிக்கை xkb_state_component, xkb_state_update_mask, (கட்டமைப்பு xkb_state *state,\
                      xkb_mod_mask_t depressed_mods,\
                      xkb_mod_mask_t latched_mods,\
                      xkb_mod_mask_t locked_mods,\
                      xkb_layout_index_t depressed_layout,\
                      xkb_layout_index_t latched_layout,\
                      xkb_layout_index_t locked_layout) )
SDL_WAYLAND_SYM(கட்டமைப்பு xkb_compose_table *, xkb_compose_table_new_from_locale, (கட்டமைப்பு xkb_context *,\
                      மாறிலி எழுத்து *locale, எண்ணிக்கை xkb_compose_compile_flags) )
SDL_WAYLAND_SYM(வெறுமை, xkb_compose_state_reset, (கட்டமைப்பு xkb_compose_state *) )
SDL_WAYLAND_SYM(வெறுமை, xkb_compose_table_unref, (கட்டமைப்பு xkb_compose_table *) )
SDL_WAYLAND_SYM(கட்டமைப்பு xkb_compose_state *, xkb_compose_state_new, (கட்டமைப்பு xkb_compose_table *, எண்ணிக்கை xkb_compose_state_flags) )
SDL_WAYLAND_SYM(வெறுமை, xkb_compose_state_unref, (கட்டமைப்பு xkb_compose_state *) )
SDL_WAYLAND_SYM(எண்ணிக்கை xkb_compose_feed_result, xkb_compose_state_feed, (கட்டமைப்பு xkb_compose_state *, xkb_keysym_t) )
SDL_WAYLAND_SYM(எண்ணிக்கை xkb_compose_status, xkb_compose_state_get_status, (கட்டமைப்பு xkb_compose_state *) )
SDL_WAYLAND_SYM(xkb_keysym_t, xkb_compose_state_get_one_sym, (கட்டமைப்பு xkb_compose_state *) )
SDL_WAYLAND_SYM(வெறுமை, xkb_keymap_சாவி_for_each, (கட்டமைப்பு xkb_keymap *, xkb_keymap_சாவி_iter_t, வெறுமை *) )
SDL_WAYLAND_SYM(xkb_layout_index_t, xkb_keymap_இலக்கம்_layouts, (கட்டமைப்பு xkb_keymap *) )
SDL_WAYLAND_SYM(முழு, xkb_keymap_சாவி_get_syms_by_level, (கட்டமைப்பு xkb_keymap *, xkb_keycode_t, xkb_layout_index_t, xkb_level_index_t, மாறிலி xkb_keysym_t **) )
SDL_WAYLAND_SYM(xkb_level_index_t, xkb_keymap_இலக்கம்_levels_for_சாவி, (கட்டமைப்பு xkb_keymap *, xkb_keycode_t, xkb_layout_index_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keysym_to_utf32, (xkb_keysym_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keymap_mod_get_index, (கட்டமைப்பு xkb_keymap *, மாறிலி எழுத்து *) )
SDL_WAYLAND_SYM(மாறிலி எழுத்து *, xkb_keymap_layout_get_name, (கட்டமைப்பு xkb_keymap *, xkb_layout_index_t))

#எனில் SDL_XKBCOMMON_CHECK_VERSION(1, 0, 0)
SDL_WAYLAND_SYM(size_t, xkb_keymap_சாவி_get_mods_for_level, (கட்டமைப்பு xkb_keymap *, xkb_keycode_t, xkb_layout_index_t, xkb_level_index_t, xkb_mod_mask_t *, size_t) )
#இல்லையெனில்
// Only needed in the fallback replacement for xkb_keymap_key_get_mods_for_level().
SDL_WAYLAND_SYM(xkb_level_index_t, xkb_state_சாவி_get_level, (கட்டமைப்பு xkb_state *, xkb_keycode_t, xkb_layout_index_t) )
#endif

#எனில் SDL_XKBCOMMON_CHECK_VERSION(1, 10, 0)
SDL_WAYLAND_SYM(xkb_mod_mask_t, xkb_keymap_mod_get_mask, (கட்டமைப்பு xkb_keymap *, மாறிலி எழுத்து *))
#endif

#ifdef HAVE_LIBDECOR_H
SDL_WAYLAND_MODULE(WAYLAND_LIBDECOR)

#எனில் defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_VERSION(0, 3, 0)
#define SDL_libdecor_constsince03 மாறிலி
#இல்லையெனில்
#define SDL_libdecor_constsince03 /* nothing */
#endif

SDL_WAYLAND_SYM(வெறுமை, libdecor_unref, (கட்டமைப்பு libdecor *))
SDL_WAYLAND_SYM(கட்டமைப்பு libdecor *, libdecor_new, (கட்டமைப்பு wl_display *,\
                                                  SDL_libdecor_constsince03 கட்டமைப்பு libdecor_interface *))
SDL_WAYLAND_SYM(கட்டமைப்பு libdecor_frame *, libdecor_decorate, (கட்டமைப்பு libdecor *,\
                                                             கட்டமைப்பு wl_surface *,\
                                                             SDL_libdecor_constsince03 கட்டமைப்பு libdecor_frame_interface *,\
                                                             வெறுமை *))
SDL_WAYLAND_SYM(வெறுமை, libdecor_frame_unref, (கட்டமைப்பு libdecor_frame *))
SDL_WAYLAND_SYM(வெறுமை, libdecor_frame_set_title, (கட்டமைப்பு libdecor_frame *, மாறிலி எழுத்து *))
SDL_WAYLAND_SYM(வெறுமை, libdecor_frame_set_app_id, (கட்டமைப்பு libdecor_frame *, மாறிலி எழுத்து *))
SDL_WAYLAND_SYM(வெறுமை, libdecor_frame_set_max_content_size, (கட்டமைப்பு libdecor_frame *frame,\
                                                            முழு content_width,\
                                                            முழு content_height))
SDL_WAYLAND_SYM(வெறுமை, libdecor_frame_set_min_content_size, (கட்டமைப்பு libdecor_frame *frame,\
                                                            முழு content_width,\
                                                            முழு content_height))
SDL_WAYLAND_SYM(வெறுமை, libdecor_frame_resize, (கட்டமைப்பு libdecor_frame *,\
                                              கட்டமைப்பு wl_seat *,\
                                              uint32_t,\
                                              எண்ணிக்கை libdecor_resize_edge))
SDL_WAYLAND_SYM(வெறுமை, libdecor_frame_move, (கட்டமைப்பு libdecor_frame *,\
                                            கட்டமைப்பு wl_seat *,\
                                            uint32_t))
SDL_WAYLAND_SYM(வெறுமை, libdecor_frame_commit, (கட்டமைப்பு libdecor_frame *,\
                                              கட்டமைப்பு libdecor_state *,\
                                              கட்டமைப்பு libdecor_configuration *))
SDL_WAYLAND_SYM(வெறுமை, libdecor_frame_set_minimized, (கட்டமைப்பு libdecor_frame *))
SDL_WAYLAND_SYM(வெறுமை, libdecor_frame_set_maximized, (கட்டமைப்பு libdecor_frame *))
SDL_WAYLAND_SYM(வெறுமை, libdecor_frame_unset_maximized, (கட்டமைப்பு libdecor_frame *))
SDL_WAYLAND_SYM(வெறுமை, libdecor_frame_set_fullscreen, (கட்டமைப்பு libdecor_frame *, கட்டமைப்பு wl_output *))
SDL_WAYLAND_SYM(வெறுமை, libdecor_frame_unset_fullscreen, (கட்டமைப்பு libdecor_frame *))
SDL_WAYLAND_SYM(வெறுமை, libdecor_frame_set_capabilities, (கட்டமைப்பு libdecor_frame *, \
                                                        எண்ணிக்கை libdecor_capabilities))
SDL_WAYLAND_SYM(வெறுமை, libdecor_frame_unset_capabilities, (கட்டமைப்பு libdecor_frame *, \
                                                          எண்ணிக்கை libdecor_capabilities))
SDL_WAYLAND_SYM(bool, libdecor_frame_has_capability, (கட்டமைப்பு libdecor_frame *, \
                                                      எண்ணிக்கை libdecor_capabilities))
SDL_WAYLAND_SYM(வெறுமை, libdecor_frame_set_visibility, (கட்டமைப்பு libdecor_frame *, bool))
SDL_WAYLAND_SYM(bool, libdecor_frame_is_visible, (கட்டமைப்பு libdecor_frame *))
SDL_WAYLAND_SYM(bool, libdecor_frame_is_floating, (கட்டமைப்பு libdecor_frame *))
SDL_WAYLAND_SYM(வெறுமை, libdecor_frame_set_parent, (கட்டமைப்பு libdecor_frame *,\
                                                  கட்டமைப்பு libdecor_frame *))
SDL_WAYLAND_SYM(வெறுமை, libdecor_frame_show_window_menu, (கட்டமைப்பு libdecor_frame *, கட்டமைப்பு wl_seat *, uint32_t, முழு, முழு))
SDL_WAYLAND_SYM(கட்டமைப்பு xdg_surface *, libdecor_frame_get_xdg_surface, (கட்டமைப்பு libdecor_frame *))
SDL_WAYLAND_SYM(கட்டமைப்பு xdg_toplevel *, libdecor_frame_get_xdg_toplevel, (கட்டமைப்பு libdecor_frame *))
SDL_WAYLAND_SYM(வெறுமை, libdecor_frame_translate_coordinate, (கட்டமைப்பு libdecor_frame *, முழு, முழு, முழு *, முழு *))
SDL_WAYLAND_SYM(வெறுமை, libdecor_frame_map, (கட்டமைப்பு libdecor_frame *))
SDL_WAYLAND_SYM(கட்டமைப்பு libdecor_state *, libdecor_state_new, (முழு, முழு))
SDL_WAYLAND_SYM(வெறுமை, libdecor_state_free, (கட்டமைப்பு libdecor_state *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_content_size, (கட்டமைப்பு libdecor_configuration *,\
                                                                கட்டமைப்பு libdecor_frame *,\
                                                                முழு *,\
                                                                முழு *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_window_state, (கட்டமைப்பு libdecor_configuration *,\
                                                                எண்ணிக்கை libdecor_window_state *))
SDL_WAYLAND_SYM(முழு, libdecor_dispatch, (கட்டமைப்பு libdecor *, முழு))

#எனில் defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_VERSION(0, 2, 0)
// Only found in libdecor 0.1.1 or higher, so failure to load them is not fatal.
SDL_WAYLAND_SYM_OPT(வெறுமை, libdecor_frame_get_min_content_size, (மாறிலி கட்டமைப்பு libdecor_frame *,\
                                                            முழு *,\
                                                            முழு *))
SDL_WAYLAND_SYM_OPT(வெறுமை, libdecor_frame_get_max_content_size, (மாறிலி கட்டமைப்பு libdecor_frame *,\
                                                            முழு *,\
                                                            முழு *))
#endif

#எனில் defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_VERSION(0, 3, 0)
SDL_WAYLAND_SYM_OPT(எண்ணிக்கை libdecor_wm_capabilities, libdecor_frame_get_wm_capabilities, (கட்டமைப்பு libdecor_frame *))
#endif

#undef SDL_libdecor_constsince03

#endif

#undef SDL_WAYLAND_MODULE
#undef SDL_WAYLAND_SYM
#undef SDL_WAYLAND_SYM_OPT

/* *INDENT-ON* */ // clang-format on
