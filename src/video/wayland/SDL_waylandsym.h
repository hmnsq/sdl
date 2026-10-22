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
SDL_WAYLAND_SYM(فراغ, wl_proxy_marshal, (بنية wl_proxy *, uint32_t, ...))
SDL_WAYLAND_SYM(بنية wl_proxy *, wl_proxy_create, (بنية wl_proxy *, ثابت بنية wl_interface *))
SDL_WAYLAND_SYM(فراغ, wl_proxy_destroy, (بنية wl_proxy *))
SDL_WAYLAND_SYM(صحيح, wl_proxy_add_listener, (بنية wl_proxy *, فراغ (**)(فراغ), فراغ *))
SDL_WAYLAND_SYM(فراغ, wl_proxy_set_user_data, (بنية wl_proxy *, فراغ *))
SDL_WAYLAND_SYM(فراغ *, wl_proxy_get_user_data, (بنية wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_version, (بنية wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_id, (بنية wl_proxy *))
SDL_WAYLAND_SYM(ثابت حرف *, wl_proxy_get_class, (بنية wl_proxy *))
SDL_WAYLAND_SYM(فراغ, wl_proxy_set_queue, (بنية wl_proxy *, بنية wl_event_queue *))
SDL_WAYLAND_SYM(فراغ *, wl_proxy_create_wrapper, (فراغ *))
SDL_WAYLAND_SYM(فراغ, wl_proxy_wrapper_destroy, (فراغ *))
SDL_WAYLAND_SYM(بنية wl_display *, wl_display_connect, (ثابت حرف *))
SDL_WAYLAND_SYM(بنية wl_display *, wl_display_connect_to_fd, (صحيح))
SDL_WAYLAND_SYM(فراغ, wl_display_disconnect, (بنية wl_display *))
SDL_WAYLAND_SYM(صحيح, wl_display_get_fd, (بنية wl_display *))
SDL_WAYLAND_SYM(صحيح, wl_display_dispatch, (بنية wl_display *))
SDL_WAYLAND_SYM(صحيح, wl_display_dispatch_queue, (بنية wl_display *, بنية wl_event_queue *))
SDL_WAYLAND_SYM(صحيح, wl_display_dispatch_queue_pending, (بنية wl_display *, بنية wl_event_queue *))
SDL_WAYLAND_SYM(صحيح, wl_display_dispatch_pending, (بنية wl_display *))
SDL_WAYLAND_SYM(صحيح, wl_display_prepare_read, (بنية wl_display *))
SDL_WAYLAND_SYM(صحيح, wl_display_prepare_read_queue, (بنية wl_display *, بنية wl_event_queue *))
SDL_WAYLAND_SYM(صحيح, wl_display_read_events, (بنية wl_display *))
SDL_WAYLAND_SYM(فراغ, wl_display_cancel_read, (بنية wl_display *))
SDL_WAYLAND_SYM(صحيح, wl_display_get_error, (بنية wl_display *))
SDL_WAYLAND_SYM(صحيح, wl_display_flush, (بنية wl_display *))
SDL_WAYLAND_SYM(صحيح, wl_display_roundtrip, (بنية wl_display *))
SDL_WAYLAND_SYM(بنية wl_event_queue *, wl_display_create_queue, (بنية wl_display *))
SDL_WAYLAND_SYM(فراغ, wl_event_queue_destroy, (بنية wl_event_queue *))
SDL_WAYLAND_SYM(فراغ, wl_log_set_handler_client, (wl_log_func_t))
SDL_WAYLAND_SYM(فراغ, wl_list_init, (بنية wl_list *))
SDL_WAYLAND_SYM(فراغ, wl_list_insert, (بنية wl_list *, بنية wl_list *) )
SDL_WAYLAND_SYM(فراغ, wl_list_remove, (بنية wl_list *))
SDL_WAYLAND_SYM(صحيح, wl_list_length, (ثابت بنية wl_list *))
SDL_WAYLAND_SYM(صحيح, wl_list_empty, (ثابت بنية wl_list *))
SDL_WAYLAND_SYM(فراغ, wl_list_insert_list, (بنية wl_list *, بنية wl_list *))
SDL_WAYLAND_SYM(فراغ, wl_array_init, (بنية wl_array *))
SDL_WAYLAND_SYM(فراغ, wl_array_release, (بنية wl_array *))
SDL_WAYLAND_SYM(فراغ *, wl_array_add, (بنية wl_array *, size_t))
SDL_WAYLAND_SYM(صحيح, wl_array_copy, (بنية wl_array *, بنية wl_array *))
SDL_WAYLAND_SYM(بنية wl_proxy *, wl_proxy_marshal_constructor, (بنية wl_proxy *, uint32_t opcode, ثابت بنية wl_interface *interface, ...))
SDL_WAYLAND_SYM(بنية wl_proxy *, wl_proxy_marshal_constructor_versioned, (بنية wl_proxy *proxy, uint32_t opcode, ثابت بنية wl_interface *interface, uint32_t version, ...))
SDL_WAYLAND_SYM(فراغ, wl_proxy_set_tag, (بنية wl_proxy *, ثابت حرف * ثابت *))
SDL_WAYLAND_SYM(ثابت حرف * ثابت *, wl_proxy_get_tag, (بنية wl_proxy *))

#אם SDL_WAYLAND_CHECK_VERSION(1, 20, 0)
/* wayland-scanner 1.20 generates code that will call these, so these are
 * non-optional when we are compiling against Wayland 1.20. We don't
 * explicitly call them ourselves, though, so if we are only compiling
 * against Wayland 1.18, they're unnecessary. */
SDL_WAYLAND_SYM(بنية wl_proxy *, wl_proxy_marshal_flags, (بنية wl_proxy *proxy, uint32_t opcode, ثابت بنية wl_interface *interface, uint32_t version, uint32_t flags, ...))
SDL_WAYLAND_SYM(بنية wl_proxy *, wl_proxy_marshal_array_flags, (بنية wl_proxy *proxy, uint32_t opcode, ثابت بنية wl_interface *interface, uint32_t version,  uint32_t flags, اتحاد wl_argument *args))
#endif

#אם SDL_WAYLAND_CHECK_VERSION(1, 23, 0) || defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC)
SDL_WAYLAND_SYM_OPT(بنية wl_event_queue *, wl_display_create_queue_with_name, (بنية wl_display *display, ثابت حرف *name))
#endif

#אם 0 // TODO RECONNECT: See waylandvideo.c for more information!
#אם SDL_WAYLAND_CHECK_VERSION(broken, on, purpose)
SDL_WAYLAND_SYM(صحيح, wl_display_reconnect, (بنية wl_display *))
#endif
#endif // 0

SDL_WAYLAND_MODULE(WAYLAND_EGL)
SDL_WAYLAND_SYM(بنية wl_egl_window *, wl_egl_window_create, (بنية wl_surface *, صحيح, صحيح))
SDL_WAYLAND_SYM(فراغ, wl_egl_window_destroy, (بنية wl_egl_window *))
SDL_WAYLAND_SYM(فراغ, wl_egl_window_resize, (بنية wl_egl_window *, صحيح, صحيح, صحيح, صحيح))
SDL_WAYLAND_SYM(فراغ, wl_egl_window_get_attached_size, (بنية wl_egl_window *, صحيح *, صحيح *))

SDL_WAYLAND_MODULE(WAYLAND_CURSOR)
SDL_WAYLAND_SYM(بنية wl_cursor_theme *, wl_cursor_theme_load, (ثابت حرف *, صحيح , بنية wl_shm *))
SDL_WAYLAND_SYM(فراغ, wl_cursor_theme_destroy, (بنية wl_cursor_theme *))
SDL_WAYLAND_SYM(بنية wl_cursor *, wl_cursor_theme_get_cursor, (بنية wl_cursor_theme *, ثابت حرف *))
SDL_WAYLAND_SYM(بنية wl_buffer *, wl_cursor_image_get_buffer, (بنية wl_cursor_image *))
SDL_WAYLAND_SYM(صحيح, wl_cursor_frame, (بنية wl_cursor *, uint32_t))

SDL_WAYLAND_MODULE(WAYLAND_XKB)
SDL_WAYLAND_SYM(صحيح, xkb_state_key_get_syms, (بنية xkb_state *, xkb_keycode_t, ثابت xkb_keysym_t **))
SDL_WAYLAND_SYM(صحيح, xkb_keysym_to_utf8, (xkb_keysym_t, حرف *, size_t) )
SDL_WAYLAND_SYM(بنية xkb_keymap *, xkb_keymap_new_from_string, (بنية xkb_context *, ثابت حرف *, تعداد xkb_keymap_format, تعداد xkb_keymap_compile_flags))
SDL_WAYLAND_SYM(بنية xkb_state *, xkb_state_new, (بنية xkb_keymap *) )
SDL_WAYLAND_SYM(صحيح, xkb_keymap_key_repeats, (بنية xkb_keymap *keymap, xkb_keycode_t key) )
SDL_WAYLAND_SYM(فراغ, xkb_keymap_unref, (بنية xkb_keymap *) )
SDL_WAYLAND_SYM(فراغ, xkb_state_unref, (بنية xkb_state *) )
SDL_WAYLAND_SYM(فراغ, xkb_context_unref, (بنية xkb_context *) )
SDL_WAYLAND_SYM(بنية xkb_context *, xkb_context_new, (تعداد xkb_context_flags flags) )
SDL_WAYLAND_SYM(تعداد xkb_state_component, xkb_state_update_mask, (بنية xkb_state *state,\
                      xkb_mod_mask_t depressed_mods,\
                      xkb_mod_mask_t latched_mods,\
                      xkb_mod_mask_t locked_mods,\
                      xkb_layout_index_t depressed_layout,\
                      xkb_layout_index_t latched_layout,\
                      xkb_layout_index_t locked_layout) )
SDL_WAYLAND_SYM(بنية xkb_compose_table *, xkb_compose_table_new_from_locale, (بنية xkb_context *,\
                      ثابت حرف *locale, تعداد xkb_compose_compile_flags) )
SDL_WAYLAND_SYM(فراغ, xkb_compose_state_reset, (بنية xkb_compose_state *) )
SDL_WAYLAND_SYM(فراغ, xkb_compose_table_unref, (بنية xkb_compose_table *) )
SDL_WAYLAND_SYM(بنية xkb_compose_state *, xkb_compose_state_new, (بنية xkb_compose_table *, تعداد xkb_compose_state_flags) )
SDL_WAYLAND_SYM(فراغ, xkb_compose_state_unref, (بنية xkb_compose_state *) )
SDL_WAYLAND_SYM(تعداد xkb_compose_feed_result, xkb_compose_state_feed, (بنية xkb_compose_state *, xkb_keysym_t) )
SDL_WAYLAND_SYM(تعداد xkb_compose_status, xkb_compose_state_get_status, (بنية xkb_compose_state *) )
SDL_WAYLAND_SYM(xkb_keysym_t, xkb_compose_state_get_one_sym, (بنية xkb_compose_state *) )
SDL_WAYLAND_SYM(فراغ, xkb_keymap_key_for_each, (بنية xkb_keymap *, xkb_keymap_key_iter_t, فراغ *) )
SDL_WAYLAND_SYM(xkb_layout_index_t, xkb_keymap_num_layouts, (بنية xkb_keymap *) )
SDL_WAYLAND_SYM(صحيح, xkb_keymap_key_get_syms_by_level, (بنية xkb_keymap *, xkb_keycode_t, xkb_layout_index_t, xkb_level_index_t, ثابت xkb_keysym_t **) )
SDL_WAYLAND_SYM(xkb_level_index_t, xkb_keymap_num_levels_for_key, (بنية xkb_keymap *, xkb_keycode_t, xkb_layout_index_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keysym_to_utf32, (xkb_keysym_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keymap_mod_get_index, (بنية xkb_keymap *, ثابت حرف *) )
SDL_WAYLAND_SYM(ثابت حرف *, xkb_keymap_layout_get_name, (بنية xkb_keymap *, xkb_layout_index_t))

#אם SDL_XKBCOMMON_CHECK_VERSION(1, 0, 0)
SDL_WAYLAND_SYM(size_t, xkb_keymap_key_get_mods_for_level, (بنية xkb_keymap *, xkb_keycode_t, xkb_layout_index_t, xkb_level_index_t, xkb_mod_mask_t *, size_t) )
#אחרת
// Only needed in the fallback replacement for xkb_keymap_key_get_mods_for_level().
SDL_WAYLAND_SYM(xkb_level_index_t, xkb_state_key_get_level, (بنية xkb_state *, xkb_keycode_t, xkb_layout_index_t) )
#endif

#אם SDL_XKBCOMMON_CHECK_VERSION(1, 10, 0)
SDL_WAYLAND_SYM(xkb_mod_mask_t, xkb_keymap_mod_get_mask, (بنية xkb_keymap *, ثابت حرف *))
#endif

#ifdef HAVE_LIBDECOR_H
SDL_WAYLAND_MODULE(WAYLAND_LIBDECOR)

#אם defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_VERSION(0, 3, 0)
#define SDL_libdecor_constsince03 ثابت
#אחרת
#define SDL_libdecor_constsince03 /* nothing */
#endif

SDL_WAYLAND_SYM(فراغ, libdecor_unref, (بنية libdecor *))
SDL_WAYLAND_SYM(بنية libdecor *, libdecor_new, (بنية wl_display *,\
                                                  SDL_libdecor_constsince03 بنية libdecor_interface *))
SDL_WAYLAND_SYM(بنية libdecor_frame *, libdecor_decorate, (بنية libdecor *,\
                                                             بنية wl_surface *,\
                                                             SDL_libdecor_constsince03 بنية libdecor_frame_interface *,\
                                                             فراغ *))
SDL_WAYLAND_SYM(فراغ, libdecor_frame_unref, (بنية libdecor_frame *))
SDL_WAYLAND_SYM(فراغ, libdecor_frame_set_title, (بنية libdecor_frame *, ثابت حرف *))
SDL_WAYLAND_SYM(فراغ, libdecor_frame_set_app_id, (بنية libdecor_frame *, ثابت حرف *))
SDL_WAYLAND_SYM(فراغ, libdecor_frame_set_max_content_size, (بنية libdecor_frame *frame,\
                                                            صحيح content_width,\
                                                            صحيح content_height))
SDL_WAYLAND_SYM(فراغ, libdecor_frame_set_min_content_size, (بنية libdecor_frame *frame,\
                                                            صحيح content_width,\
                                                            صحيح content_height))
SDL_WAYLAND_SYM(فراغ, libdecor_frame_resize, (بنية libdecor_frame *,\
                                              بنية wl_seat *,\
                                              uint32_t,\
                                              تعداد libdecor_resize_edge))
SDL_WAYLAND_SYM(فراغ, libdecor_frame_move, (بنية libdecor_frame *,\
                                            بنية wl_seat *,\
                                            uint32_t))
SDL_WAYLAND_SYM(فراغ, libdecor_frame_commit, (بنية libdecor_frame *,\
                                              بنية libdecor_state *,\
                                              بنية libdecor_configuration *))
SDL_WAYLAND_SYM(فراغ, libdecor_frame_set_minimized, (بنية libdecor_frame *))
SDL_WAYLAND_SYM(فراغ, libdecor_frame_set_maximized, (بنية libdecor_frame *))
SDL_WAYLAND_SYM(فراغ, libdecor_frame_unset_maximized, (بنية libdecor_frame *))
SDL_WAYLAND_SYM(فراغ, libdecor_frame_set_fullscreen, (بنية libdecor_frame *, بنية wl_output *))
SDL_WAYLAND_SYM(فراغ, libdecor_frame_unset_fullscreen, (بنية libdecor_frame *))
SDL_WAYLAND_SYM(فراغ, libdecor_frame_set_capabilities, (بنية libdecor_frame *, \
                                                        تعداد libdecor_capabilities))
SDL_WAYLAND_SYM(فراغ, libdecor_frame_unset_capabilities, (بنية libdecor_frame *, \
                                                          تعداد libdecor_capabilities))
SDL_WAYLAND_SYM(bool, libdecor_frame_has_capability, (بنية libdecor_frame *, \
                                                      تعداد libdecor_capabilities))
SDL_WAYLAND_SYM(فراغ, libdecor_frame_set_visibility, (بنية libdecor_frame *, bool))
SDL_WAYLAND_SYM(bool, libdecor_frame_is_visible, (بنية libdecor_frame *))
SDL_WAYLAND_SYM(bool, libdecor_frame_is_floating, (بنية libdecor_frame *))
SDL_WAYLAND_SYM(فراغ, libdecor_frame_set_parent, (بنية libdecor_frame *,\
                                                  بنية libdecor_frame *))
SDL_WAYLAND_SYM(فراغ, libdecor_frame_show_window_menu, (بنية libdecor_frame *, بنية wl_seat *, uint32_t, صحيح, صحيح))
SDL_WAYLAND_SYM(بنية xdg_surface *, libdecor_frame_get_xdg_surface, (بنية libdecor_frame *))
SDL_WAYLAND_SYM(بنية xdg_toplevel *, libdecor_frame_get_xdg_toplevel, (بنية libdecor_frame *))
SDL_WAYLAND_SYM(فراغ, libdecor_frame_translate_coordinate, (بنية libdecor_frame *, صحيح, صحيح, صحيح *, صحيح *))
SDL_WAYLAND_SYM(فراغ, libdecor_frame_map, (بنية libdecor_frame *))
SDL_WAYLAND_SYM(بنية libdecor_state *, libdecor_state_new, (صحيح, صحيح))
SDL_WAYLAND_SYM(فراغ, libdecor_state_free, (بنية libdecor_state *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_content_size, (بنية libdecor_configuration *,\
                                                                بنية libdecor_frame *,\
                                                                صحيح *,\
                                                                صحيح *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_window_state, (بنية libdecor_configuration *,\
                                                                تعداد libdecor_window_state *))
SDL_WAYLAND_SYM(صحيح, libdecor_dispatch, (بنية libdecor *, صحيح))

#אם defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_VERSION(0, 2, 0)
// Only found in libdecor 0.1.1 or higher, so failure to load them is not fatal.
SDL_WAYLAND_SYM_OPT(فراغ, libdecor_frame_get_min_content_size, (ثابت بنية libdecor_frame *,\
                                                            صحيح *,\
                                                            صحيح *))
SDL_WAYLAND_SYM_OPT(فراغ, libdecor_frame_get_max_content_size, (ثابت بنية libdecor_frame *,\
                                                            صحيح *,\
                                                            صحيح *))
#endif

#אם defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_VERSION(0, 3, 0)
SDL_WAYLAND_SYM_OPT(تعداد libdecor_wm_capabilities, libdecor_frame_get_wm_capabilities, (بنية libdecor_frame *))
#endif

#undef SDL_libdecor_constsince03

#endif

#undef SDL_WAYLAND_MODULE
#undef SDL_WAYLAND_SYM
#undef SDL_WAYLAND_SYM_OPT

/* *INDENT-ON* */ // clang-format on
