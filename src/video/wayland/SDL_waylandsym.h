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
SDL_WAYLAND_SYM(শূন্য, wl_proxy_marshal, (সংরচনা wl_proxy *, uint32_t, ...))
SDL_WAYLAND_SYM(সংরচনা wl_proxy *, wl_proxy_create, (সংরচনা wl_proxy *, ধ্রুৱ সংরচনা wl_interface *))
SDL_WAYLAND_SYM(শূন্য, wl_proxy_destroy, (সংরচনা wl_proxy *))
SDL_WAYLAND_SYM(পূর্ণাঙ্ক, wl_proxy_add_listener, (সংরচনা wl_proxy *, শূন্য (**)(শূন্য), শূন্য *))
SDL_WAYLAND_SYM(শূন্য, wl_proxy_set_user_data, (সংরচনা wl_proxy *, শূন্য *))
SDL_WAYLAND_SYM(শূন্য *, wl_proxy_get_user_data, (সংরচনা wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_version, (সংরচনা wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_id, (সংরচনা wl_proxy *))
SDL_WAYLAND_SYM(ধ্রুৱ ৱর্ণ *, wl_proxy_get_class, (সংরচনা wl_proxy *))
SDL_WAYLAND_SYM(শূন্য, wl_proxy_set_queue, (সংরচনা wl_proxy *, সংরচনা wl_event_queue *))
SDL_WAYLAND_SYM(শূন্য *, wl_proxy_create_wrapper, (শূন্য *))
SDL_WAYLAND_SYM(শূন্য, wl_proxy_wrapper_destroy, (শূন্য *))
SDL_WAYLAND_SYM(সংরচনা wl_display *, wl_display_connect, (ধ্রুৱ ৱর্ণ *))
SDL_WAYLAND_SYM(সংরচনা wl_display *, wl_display_connect_to_fd, (পূর্ণাঙ্ক))
SDL_WAYLAND_SYM(শূন্য, wl_display_disconnect, (সংরচনা wl_display *))
SDL_WAYLAND_SYM(পূর্ণাঙ্ক, wl_display_get_fd, (সংরচনা wl_display *))
SDL_WAYLAND_SYM(পূর্ণাঙ্ক, wl_display_dispatch, (সংরচনা wl_display *))
SDL_WAYLAND_SYM(পূর্ণাঙ্ক, wl_display_dispatch_queue, (সংরচনা wl_display *, সংরচনা wl_event_queue *))
SDL_WAYLAND_SYM(পূর্ণাঙ্ক, wl_display_dispatch_queue_pending, (সংরচনা wl_display *, সংরচনা wl_event_queue *))
SDL_WAYLAND_SYM(পূর্ণাঙ্ক, wl_display_dispatch_pending, (সংরচনা wl_display *))
SDL_WAYLAND_SYM(পূর্ণাঙ্ক, wl_display_prepare_read, (সংরচনা wl_display *))
SDL_WAYLAND_SYM(পূর্ণাঙ্ক, wl_display_prepare_read_queue, (সংরচনা wl_display *, সংরচনা wl_event_queue *))
SDL_WAYLAND_SYM(পূর্ণাঙ্ক, wl_display_read_events, (সংরচনা wl_display *))
SDL_WAYLAND_SYM(শূন্য, wl_display_cancel_read, (সংরচনা wl_display *))
SDL_WAYLAND_SYM(পূর্ণাঙ্ক, wl_display_get_error, (সংরচনা wl_display *))
SDL_WAYLAND_SYM(পূর্ণাঙ্ক, wl_display_flush, (সংরচনা wl_display *))
SDL_WAYLAND_SYM(পূর্ণাঙ্ক, wl_display_roundtrip, (সংরচনা wl_display *))
SDL_WAYLAND_SYM(সংরচনা wl_event_queue *, wl_display_create_queue, (সংরচনা wl_display *))
SDL_WAYLAND_SYM(শূন্য, wl_event_queue_destroy, (সংরচনা wl_event_queue *))
SDL_WAYLAND_SYM(শূন্য, wl_log_set_handler_client, (wl_log_func_t))
SDL_WAYLAND_SYM(শূন্য, wl_list_init, (সংরচনা wl_list *))
SDL_WAYLAND_SYM(শূন্য, wl_list_ঢোকাও, (সংরচনা wl_list *, সংরচনা wl_list *) )
SDL_WAYLAND_SYM(শূন্য, wl_list_remove, (সংরচনা wl_list *))
SDL_WAYLAND_SYM(পূর্ণাঙ্ক, wl_list_length, (ধ্রুৱ সংরচনা wl_list *))
SDL_WAYLAND_SYM(পূর্ণাঙ্ক, wl_list_empty, (ধ্রুৱ সংরচনা wl_list *))
SDL_WAYLAND_SYM(শূন্য, wl_list_ঢোকাও_list, (সংরচনা wl_list *, সংরচনা wl_list *))
SDL_WAYLAND_SYM(শূন্য, wl_array_init, (সংরচনা wl_array *))
SDL_WAYLAND_SYM(শূন্য, wl_array_release, (সংরচনা wl_array *))
SDL_WAYLAND_SYM(শূন্য *, wl_array_add, (সংরচনা wl_array *, size_t))
SDL_WAYLAND_SYM(পূর্ণাঙ্ক, wl_array_copy, (সংরচনা wl_array *, সংরচনা wl_array *))
SDL_WAYLAND_SYM(সংরচনা wl_proxy *, wl_proxy_marshal_constructor, (সংরচনা wl_proxy *, uint32_t opcode, ধ্রুৱ সংরচনা wl_interface *interface, ...))
SDL_WAYLAND_SYM(সংরচনা wl_proxy *, wl_proxy_marshal_constructor_versioned, (সংরচনা wl_proxy *proxy, uint32_t opcode, ধ্রুৱ সংরচনা wl_interface *interface, uint32_t version, ...))
SDL_WAYLAND_SYM(শূন্য, wl_proxy_set_tag, (সংরচনা wl_proxy *, ধ্রুৱ ৱর্ণ * ধ্রুৱ *))
SDL_WAYLAND_SYM(ধ্রুৱ ৱর্ণ * ধ্রুৱ *, wl_proxy_get_tag, (সংরচনা wl_proxy *))

#যদি SDL_WAYLAND_CHECK_VERSION(1, 20, 0)
/* wayland-scanner 1.20 generates code that will call these, so these are
 * non-optional when we are compiling against Wayland 1.20. We don't
 * explicitly call them ourselves, though, so if we are only compiling
 * against Wayland 1.18, they're unnecessary. */
SDL_WAYLAND_SYM(সংরচনা wl_proxy *, wl_proxy_marshal_flags, (সংরচনা wl_proxy *proxy, uint32_t opcode, ধ্রুৱ সংরচনা wl_interface *interface, uint32_t version, uint32_t flags, ...))
SDL_WAYLAND_SYM(সংরচনা wl_proxy *, wl_proxy_marshal_array_flags, (সংরচনা wl_proxy *proxy, uint32_t opcode, ধ্রুৱ সংরচনা wl_interface *interface, uint32_t version,  uint32_t flags, সঙ্ঘ wl_argument *args))
#endif

#যদি SDL_WAYLAND_CHECK_VERSION(1, 23, 0) || defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC)
SDL_WAYLAND_SYM_OPT(সংরচনা wl_event_queue *, wl_display_create_queue_with_name, (সংরচনা wl_display *display, ধ্রুৱ ৱর্ণ *name))
#endif

#যদি 0 // TODO RECONNECT: See waylandvideo.c for more information!
#যদি SDL_WAYLAND_CHECK_VERSION(broken, on, purpose)
SDL_WAYLAND_SYM(পূর্ণাঙ্ক, wl_display_reconnect, (সংরচনা wl_display *))
#endif
#endif // 0

SDL_WAYLAND_MODULE(WAYLAND_EGL)
SDL_WAYLAND_SYM(সংরচনা wl_egl_window *, wl_egl_window_create, (সংরচনা wl_surface *, পূর্ণাঙ্ক, পূর্ণাঙ্ক))
SDL_WAYLAND_SYM(শূন্য, wl_egl_window_destroy, (সংরচনা wl_egl_window *))
SDL_WAYLAND_SYM(শূন্য, wl_egl_window_resize, (সংরচনা wl_egl_window *, পূর্ণাঙ্ক, পূর্ণাঙ্ক, পূর্ণাঙ্ক, পূর্ণাঙ্ক))
SDL_WAYLAND_SYM(শূন্য, wl_egl_window_get_attached_size, (সংরচনা wl_egl_window *, পূর্ণাঙ্ক *, পূর্ণাঙ্ক *))

SDL_WAYLAND_MODULE(WAYLAND_CURSOR)
SDL_WAYLAND_SYM(সংরচনা wl_cursor_theme *, wl_cursor_theme_load, (ধ্রুৱ ৱর্ণ *, পূর্ণাঙ্ক , সংরচনা wl_shm *))
SDL_WAYLAND_SYM(শূন্য, wl_cursor_theme_destroy, (সংরচনা wl_cursor_theme *))
SDL_WAYLAND_SYM(সংরচনা wl_cursor *, wl_cursor_theme_get_cursor, (সংরচনা wl_cursor_theme *, ধ্রুৱ ৱর্ণ *))
SDL_WAYLAND_SYM(সংরচনা wl_buffer *, wl_cursor_image_get_buffer, (সংরচনা wl_cursor_image *))
SDL_WAYLAND_SYM(পূর্ণাঙ্ক, wl_cursor_frame, (সংরচনা wl_cursor *, uint32_t))

SDL_WAYLAND_MODULE(WAYLAND_XKB)
SDL_WAYLAND_SYM(পূর্ণাঙ্ক, xkb_state_চাবি_get_syms, (সংরচনা xkb_state *, xkb_keycode_t, ধ্রুৱ xkb_keysym_t **))
SDL_WAYLAND_SYM(পূর্ণাঙ্ক, xkb_keysym_to_utf8, (xkb_keysym_t, ৱর্ণ *, size_t) )
SDL_WAYLAND_SYM(সংরচনা xkb_keymap *, xkb_keymap_new_from_string, (সংরচনা xkb_context *, ধ্রুৱ ৱর্ণ *, গণনা xkb_keymap_format, গণনা xkb_keymap_compile_flags))
SDL_WAYLAND_SYM(সংরচনা xkb_state *, xkb_state_new, (সংরচনা xkb_keymap *) )
SDL_WAYLAND_SYM(পূর্ণাঙ্ক, xkb_keymap_চাবি_repeats, (সংরচনা xkb_keymap *keymap, xkb_keycode_t চাবি) )
SDL_WAYLAND_SYM(শূন্য, xkb_keymap_unref, (সংরচনা xkb_keymap *) )
SDL_WAYLAND_SYM(শূন্য, xkb_state_unref, (সংরচনা xkb_state *) )
SDL_WAYLAND_SYM(শূন্য, xkb_context_unref, (সংরচনা xkb_context *) )
SDL_WAYLAND_SYM(সংরচনা xkb_context *, xkb_context_new, (গণনা xkb_context_flags flags) )
SDL_WAYLAND_SYM(গণনা xkb_state_component, xkb_state_update_mask, (সংরচনা xkb_state *state,\
                      xkb_mod_mask_t depressed_mods,\
                      xkb_mod_mask_t latched_mods,\
                      xkb_mod_mask_t locked_mods,\
                      xkb_layout_index_t depressed_layout,\
                      xkb_layout_index_t latched_layout,\
                      xkb_layout_index_t locked_layout) )
SDL_WAYLAND_SYM(সংরচনা xkb_compose_table *, xkb_compose_table_new_from_locale, (সংরচনা xkb_context *,\
                      ধ্রুৱ ৱর্ণ *locale, গণনা xkb_compose_compile_flags) )
SDL_WAYLAND_SYM(শূন্য, xkb_compose_state_reset, (সংরচনা xkb_compose_state *) )
SDL_WAYLAND_SYM(শূন্য, xkb_compose_table_unref, (সংরচনা xkb_compose_table *) )
SDL_WAYLAND_SYM(সংরচনা xkb_compose_state *, xkb_compose_state_new, (সংরচনা xkb_compose_table *, গণনা xkb_compose_state_flags) )
SDL_WAYLAND_SYM(শূন্য, xkb_compose_state_unref, (সংরচনা xkb_compose_state *) )
SDL_WAYLAND_SYM(গণনা xkb_compose_feed_result, xkb_compose_state_feed, (সংরচনা xkb_compose_state *, xkb_keysym_t) )
SDL_WAYLAND_SYM(গণনা xkb_compose_status, xkb_compose_state_get_status, (সংরচনা xkb_compose_state *) )
SDL_WAYLAND_SYM(xkb_keysym_t, xkb_compose_state_get_one_sym, (সংরচনা xkb_compose_state *) )
SDL_WAYLAND_SYM(শূন্য, xkb_keymap_চাবি_for_each, (সংরচনা xkb_keymap *, xkb_keymap_চাবি_iter_t, শূন্য *) )
SDL_WAYLAND_SYM(xkb_layout_index_t, xkb_keymap_অঙ্ক_layouts, (সংরচনা xkb_keymap *) )
SDL_WAYLAND_SYM(পূর্ণাঙ্ক, xkb_keymap_চাবি_get_syms_by_level, (সংরচনা xkb_keymap *, xkb_keycode_t, xkb_layout_index_t, xkb_level_index_t, ধ্রুৱ xkb_keysym_t **) )
SDL_WAYLAND_SYM(xkb_level_index_t, xkb_keymap_অঙ্ক_levels_for_চাবি, (সংরচনা xkb_keymap *, xkb_keycode_t, xkb_layout_index_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keysym_to_utf32, (xkb_keysym_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keymap_mod_get_index, (সংরচনা xkb_keymap *, ধ্রুৱ ৱর্ণ *) )
SDL_WAYLAND_SYM(ধ্রুৱ ৱর্ণ *, xkb_keymap_layout_get_name, (সংরচনা xkb_keymap *, xkb_layout_index_t))

#যদি SDL_XKBCOMMON_CHECK_VERSION(1, 0, 0)
SDL_WAYLAND_SYM(size_t, xkb_keymap_চাবি_get_mods_for_level, (সংরচনা xkb_keymap *, xkb_keycode_t, xkb_layout_index_t, xkb_level_index_t, xkb_mod_mask_t *, size_t) )
#অন্যথা
// Only needed in the fallback replacement for xkb_keymap_key_get_mods_for_level().
SDL_WAYLAND_SYM(xkb_level_index_t, xkb_state_চাবি_get_level, (সংরচনা xkb_state *, xkb_keycode_t, xkb_layout_index_t) )
#endif

#যদি SDL_XKBCOMMON_CHECK_VERSION(1, 10, 0)
SDL_WAYLAND_SYM(xkb_mod_mask_t, xkb_keymap_mod_get_mask, (সংরচনা xkb_keymap *, ধ্রুৱ ৱর্ণ *))
#endif

#ifdef HAVE_LIBDECOR_H
SDL_WAYLAND_MODULE(WAYLAND_LIBDECOR)

#যদি defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_VERSION(0, 3, 0)
#define SDL_libdecor_constsince03 ধ্রুৱ
#অন্যথা
#define SDL_libdecor_constsince03 /* nothing */
#endif

SDL_WAYLAND_SYM(শূন্য, libdecor_unref, (সংরচনা libdecor *))
SDL_WAYLAND_SYM(সংরচনা libdecor *, libdecor_new, (সংরচনা wl_display *,\
                                                  SDL_libdecor_constsince03 সংরচনা libdecor_interface *))
SDL_WAYLAND_SYM(সংরচনা libdecor_frame *, libdecor_decorate, (সংরচনা libdecor *,\
                                                             সংরচনা wl_surface *,\
                                                             SDL_libdecor_constsince03 সংরচনা libdecor_frame_interface *,\
                                                             শূন্য *))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_unref, (সংরচনা libdecor_frame *))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_set_title, (সংরচনা libdecor_frame *, ধ্রুৱ ৱর্ণ *))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_set_app_id, (সংরচনা libdecor_frame *, ধ্রুৱ ৱর্ণ *))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_set_max_content_size, (সংরচনা libdecor_frame *frame,\
                                                            পূর্ণাঙ্ক content_width,\
                                                            পূর্ণাঙ্ক content_height))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_set_min_content_size, (সংরচনা libdecor_frame *frame,\
                                                            পূর্ণাঙ্ক content_width,\
                                                            পূর্ণাঙ্ক content_height))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_resize, (সংরচনা libdecor_frame *,\
                                              সংরচনা wl_seat *,\
                                              uint32_t,\
                                              গণনা libdecor_resize_edge))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_move, (সংরচনা libdecor_frame *,\
                                            সংরচনা wl_seat *,\
                                            uint32_t))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_commit, (সংরচনা libdecor_frame *,\
                                              সংরচনা libdecor_state *,\
                                              সংরচনা libdecor_configuration *))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_set_minimized, (সংরচনা libdecor_frame *))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_set_maximized, (সংরচনা libdecor_frame *))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_unset_maximized, (সংরচনা libdecor_frame *))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_set_fullscreen, (সংরচনা libdecor_frame *, সংরচনা wl_output *))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_unset_fullscreen, (সংরচনা libdecor_frame *))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_set_capabilities, (সংরচনা libdecor_frame *, \
                                                        গণনা libdecor_capabilities))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_unset_capabilities, (সংরচনা libdecor_frame *, \
                                                          গণনা libdecor_capabilities))
SDL_WAYLAND_SYM(bool, libdecor_frame_has_capability, (সংরচনা libdecor_frame *, \
                                                      গণনা libdecor_capabilities))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_set_visibility, (সংরচনা libdecor_frame *, bool))
SDL_WAYLAND_SYM(bool, libdecor_frame_is_visible, (সংরচনা libdecor_frame *))
SDL_WAYLAND_SYM(bool, libdecor_frame_is_floating, (সংরচনা libdecor_frame *))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_set_parent, (সংরচনা libdecor_frame *,\
                                                  সংরচনা libdecor_frame *))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_show_window_menu, (সংরচনা libdecor_frame *, সংরচনা wl_seat *, uint32_t, পূর্ণাঙ্ক, পূর্ণাঙ্ক))
SDL_WAYLAND_SYM(সংরচনা xdg_surface *, libdecor_frame_get_xdg_surface, (সংরচনা libdecor_frame *))
SDL_WAYLAND_SYM(সংরচনা xdg_toplevel *, libdecor_frame_get_xdg_toplevel, (সংরচনা libdecor_frame *))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_translate_coordinate, (সংরচনা libdecor_frame *, পূর্ণাঙ্ক, পূর্ণাঙ্ক, পূর্ণাঙ্ক *, পূর্ণাঙ্ক *))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_map, (সংরচনা libdecor_frame *))
SDL_WAYLAND_SYM(সংরচনা libdecor_state *, libdecor_state_new, (পূর্ণাঙ্ক, পূর্ণাঙ্ক))
SDL_WAYLAND_SYM(শূন্য, libdecor_state_free, (সংরচনা libdecor_state *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_content_size, (সংরচনা libdecor_configuration *,\
                                                                সংরচনা libdecor_frame *,\
                                                                পূর্ণাঙ্ক *,\
                                                                পূর্ণাঙ্ক *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_window_state, (সংরচনা libdecor_configuration *,\
                                                                গণনা libdecor_window_state *))
SDL_WAYLAND_SYM(পূর্ণাঙ্ক, libdecor_dispatch, (সংরচনা libdecor *, পূর্ণাঙ্ক))

#যদি defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_VERSION(0, 2, 0)
// Only found in libdecor 0.1.1 or higher, so failure to load them is not fatal.
SDL_WAYLAND_SYM_OPT(শূন্য, libdecor_frame_get_min_content_size, (ধ্রুৱ সংরচনা libdecor_frame *,\
                                                            পূর্ণাঙ্ক *,\
                                                            পূর্ণাঙ্ক *))
SDL_WAYLAND_SYM_OPT(শূন্য, libdecor_frame_get_max_content_size, (ধ্রুৱ সংরচনা libdecor_frame *,\
                                                            পূর্ণাঙ্ক *,\
                                                            পূর্ণাঙ্ক *))
#endif

#যদি defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_VERSION(0, 3, 0)
SDL_WAYLAND_SYM_OPT(গণনা libdecor_wm_capabilities, libdecor_frame_get_wm_capabilities, (সংরচনা libdecor_frame *))
#endif

#undef SDL_libdecor_constsince03

#endif

#undef SDL_WAYLAND_MODULE
#undef SDL_WAYLAND_SYM
#undef SDL_WAYLAND_SYM_OPT

/* *INDENT-ON* */ // clang-format on
