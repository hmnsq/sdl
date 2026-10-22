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
SDL_WAYLAND_SYM(تهی, wl_proxy_marshal, (ساختار wl_proxy *, uint32_t, ...))
SDL_WAYLAND_SYM(ساختار wl_proxy *, wl_proxy_create, (ساختار wl_proxy *, ثابت ساختار wl_interface *))
SDL_WAYLAND_SYM(تهی, wl_proxy_destroy, (ساختار wl_proxy *))
SDL_WAYLAND_SYM(صحیح, wl_proxy_add_listener, (ساختار wl_proxy *, تهی (**)(تهی), تهی *))
SDL_WAYLAND_SYM(تهی, wl_proxy_set_user_data, (ساختار wl_proxy *, تهی *))
SDL_WAYLAND_SYM(تهی *, wl_proxy_get_user_data, (ساختار wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_version, (ساختار wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_id, (ساختار wl_proxy *))
SDL_WAYLAND_SYM(ثابت نویسه *, wl_proxy_get_class, (ساختار wl_proxy *))
SDL_WAYLAND_SYM(تهی, wl_proxy_set_queue, (ساختار wl_proxy *, ساختار wl_event_queue *))
SDL_WAYLAND_SYM(تهی *, wl_proxy_create_wrapper, (تهی *))
SDL_WAYLAND_SYM(تهی, wl_proxy_wrapper_destroy, (تهی *))
SDL_WAYLAND_SYM(ساختار wl_display *, wl_display_connect, (ثابت نویسه *))
SDL_WAYLAND_SYM(ساختار wl_display *, wl_display_connect_to_fd, (صحیح))
SDL_WAYLAND_SYM(تهی, wl_display_disconnect, (ساختار wl_display *))
SDL_WAYLAND_SYM(صحیح, wl_display_get_fd, (ساختار wl_display *))
SDL_WAYLAND_SYM(صحیح, wl_display_dispatch, (ساختار wl_display *))
SDL_WAYLAND_SYM(صحیح, wl_display_dispatch_queue, (ساختار wl_display *, ساختار wl_event_queue *))
SDL_WAYLAND_SYM(صحیح, wl_display_dispatch_queue_pending, (ساختار wl_display *, ساختار wl_event_queue *))
SDL_WAYLAND_SYM(صحیح, wl_display_dispatch_pending, (ساختار wl_display *))
SDL_WAYLAND_SYM(صحیح, wl_display_prepare_read, (ساختار wl_display *))
SDL_WAYLAND_SYM(صحیح, wl_display_prepare_read_queue, (ساختار wl_display *, ساختار wl_event_queue *))
SDL_WAYLAND_SYM(صحیح, wl_display_read_events, (ساختار wl_display *))
SDL_WAYLAND_SYM(تهی, wl_display_cancel_read, (ساختار wl_display *))
SDL_WAYLAND_SYM(صحیح, wl_display_get_error, (ساختار wl_display *))
SDL_WAYLAND_SYM(صحیح, wl_display_flush, (ساختار wl_display *))
SDL_WAYLAND_SYM(صحیح, wl_display_roundtrip, (ساختار wl_display *))
SDL_WAYLAND_SYM(ساختار wl_event_queue *, wl_display_create_queue, (ساختار wl_display *))
SDL_WAYLAND_SYM(تهی, wl_event_queue_destroy, (ساختار wl_event_queue *))
SDL_WAYLAND_SYM(تهی, wl_log_set_handler_client, (wl_log_func_t))
SDL_WAYLAND_SYM(تهی, wl_list_init, (ساختار wl_list *))
SDL_WAYLAND_SYM(تهی, wl_list_درج, (ساختار wl_list *, ساختار wl_list *) )
SDL_WAYLAND_SYM(تهی, wl_list_remove, (ساختار wl_list *))
SDL_WAYLAND_SYM(صحیح, wl_list_length, (ثابت ساختار wl_list *))
SDL_WAYLAND_SYM(صحیح, wl_list_empty, (ثابت ساختار wl_list *))
SDL_WAYLAND_SYM(تهی, wl_list_درج_list, (ساختار wl_list *, ساختار wl_list *))
SDL_WAYLAND_SYM(تهی, wl_array_init, (ساختار wl_array *))
SDL_WAYLAND_SYM(تهی, wl_array_release, (ساختار wl_array *))
SDL_WAYLAND_SYM(تهی *, wl_array_add, (ساختار wl_array *, size_t))
SDL_WAYLAND_SYM(صحیح, wl_array_copy, (ساختار wl_array *, ساختار wl_array *))
SDL_WAYLAND_SYM(ساختار wl_proxy *, wl_proxy_marshal_constructor, (ساختار wl_proxy *, uint32_t opcode, ثابت ساختار wl_interface *interface, ...))
SDL_WAYLAND_SYM(ساختار wl_proxy *, wl_proxy_marshal_constructor_versioned, (ساختار wl_proxy *proxy, uint32_t opcode, ثابت ساختار wl_interface *interface, uint32_t version, ...))
SDL_WAYLAND_SYM(تهی, wl_proxy_set_tag, (ساختار wl_proxy *, ثابت نویسه * ثابت *))
SDL_WAYLAND_SYM(ثابت نویسه * ثابت *, wl_proxy_get_tag, (ساختار wl_proxy *))

#اگر SDL_WAYLAND_CHECK_VERSION(1, 20, 0)
/* wayland-scanner 1.20 generates code that will call these, so these are
 * non-optional when we are compiling against Wayland 1.20. We don't
 * explicitly call them ourselves, though, so if we are only compiling
 * against Wayland 1.18, they're unnecessary. */
SDL_WAYLAND_SYM(ساختار wl_proxy *, wl_proxy_marshal_flags, (ساختار wl_proxy *proxy, uint32_t opcode, ثابت ساختار wl_interface *interface, uint32_t version, uint32_t flags, ...))
SDL_WAYLAND_SYM(ساختار wl_proxy *, wl_proxy_marshal_array_flags, (ساختار wl_proxy *proxy, uint32_t opcode, ثابت ساختار wl_interface *interface, uint32_t version,  uint32_t flags, اجتماع wl_argument *args))
#endif

#اگر SDL_WAYLAND_CHECK_VERSION(1, 23, 0) || defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC)
SDL_WAYLAND_SYM_OPT(ساختار wl_event_queue *, wl_display_create_queue_with_name, (ساختار wl_display *display, ثابت نویسه *name))
#endif

#اگر 0 // TODO RECONNECT: See waylandvideo.c for more information!
#اگر SDL_WAYLAND_CHECK_VERSION(broken, on, purpose)
SDL_WAYLAND_SYM(صحیح, wl_display_reconnect, (ساختار wl_display *))
#endif
#endif // 0

SDL_WAYLAND_MODULE(WAYLAND_EGL)
SDL_WAYLAND_SYM(ساختار wl_egl_window *, wl_egl_window_create, (ساختار wl_surface *, صحیح, صحیح))
SDL_WAYLAND_SYM(تهی, wl_egl_window_destroy, (ساختار wl_egl_window *))
SDL_WAYLAND_SYM(تهی, wl_egl_window_resize, (ساختار wl_egl_window *, صحیح, صحیح, صحیح, صحیح))
SDL_WAYLAND_SYM(تهی, wl_egl_window_get_attached_size, (ساختار wl_egl_window *, صحیح *, صحیح *))

SDL_WAYLAND_MODULE(WAYLAND_CURSOR)
SDL_WAYLAND_SYM(ساختار wl_cursor_theme *, wl_cursor_theme_load, (ثابت نویسه *, صحیح , ساختار wl_shm *))
SDL_WAYLAND_SYM(تهی, wl_cursor_theme_destroy, (ساختار wl_cursor_theme *))
SDL_WAYLAND_SYM(ساختار wl_cursor *, wl_cursor_theme_get_cursor, (ساختار wl_cursor_theme *, ثابت نویسه *))
SDL_WAYLAND_SYM(ساختار wl_buffer *, wl_cursor_image_get_buffer, (ساختار wl_cursor_image *))
SDL_WAYLAND_SYM(صحیح, wl_cursor_frame, (ساختار wl_cursor *, uint32_t))

SDL_WAYLAND_MODULE(WAYLAND_XKB)
SDL_WAYLAND_SYM(صحیح, xkb_state_کلید_get_syms, (ساختار xkb_state *, xkb_keycode_t, ثابت xkb_keysym_t **))
SDL_WAYLAND_SYM(صحیح, xkb_keysym_to_utf8, (xkb_keysym_t, نویسه *, size_t) )
SDL_WAYLAND_SYM(ساختار xkb_keymap *, xkb_keymap_new_from_string, (ساختار xkb_context *, ثابت نویسه *, شمارش xkb_keymap_format, شمارش xkb_keymap_compile_flags))
SDL_WAYLAND_SYM(ساختار xkb_state *, xkb_state_new, (ساختار xkb_keymap *) )
SDL_WAYLAND_SYM(صحیح, xkb_keymap_کلید_repeats, (ساختار xkb_keymap *keymap, xkb_keycode_t کلید) )
SDL_WAYLAND_SYM(تهی, xkb_keymap_unref, (ساختار xkb_keymap *) )
SDL_WAYLAND_SYM(تهی, xkb_state_unref, (ساختار xkb_state *) )
SDL_WAYLAND_SYM(تهی, xkb_context_unref, (ساختار xkb_context *) )
SDL_WAYLAND_SYM(ساختار xkb_context *, xkb_context_new, (شمارش xkb_context_flags flags) )
SDL_WAYLAND_SYM(شمارش xkb_state_component, xkb_state_update_mask, (ساختار xkb_state *state,\
                      xkb_mod_mask_t depressed_mods,\
                      xkb_mod_mask_t latched_mods,\
                      xkb_mod_mask_t locked_mods,\
                      xkb_layout_index_t depressed_layout,\
                      xkb_layout_index_t latched_layout,\
                      xkb_layout_index_t locked_layout) )
SDL_WAYLAND_SYM(ساختار xkb_compose_table *, xkb_compose_table_new_from_locale, (ساختار xkb_context *,\
                      ثابت نویسه *locale, شمارش xkb_compose_compile_flags) )
SDL_WAYLAND_SYM(تهی, xkb_compose_state_reset, (ساختار xkb_compose_state *) )
SDL_WAYLAND_SYM(تهی, xkb_compose_table_unref, (ساختار xkb_compose_table *) )
SDL_WAYLAND_SYM(ساختار xkb_compose_state *, xkb_compose_state_new, (ساختار xkb_compose_table *, شمارش xkb_compose_state_flags) )
SDL_WAYLAND_SYM(تهی, xkb_compose_state_unref, (ساختار xkb_compose_state *) )
SDL_WAYLAND_SYM(شمارش xkb_compose_feed_result, xkb_compose_state_feed, (ساختار xkb_compose_state *, xkb_keysym_t) )
SDL_WAYLAND_SYM(شمارش xkb_compose_status, xkb_compose_state_get_status, (ساختار xkb_compose_state *) )
SDL_WAYLAND_SYM(xkb_keysym_t, xkb_compose_state_get_one_sym, (ساختار xkb_compose_state *) )
SDL_WAYLAND_SYM(تهی, xkb_keymap_کلید_for_each, (ساختار xkb_keymap *, xkb_keymap_کلید_iter_t, تهی *) )
SDL_WAYLAND_SYM(xkb_layout_index_t, xkb_keymap_رقم_layouts, (ساختار xkb_keymap *) )
SDL_WAYLAND_SYM(صحیح, xkb_keymap_کلید_get_syms_by_level, (ساختار xkb_keymap *, xkb_keycode_t, xkb_layout_index_t, xkb_level_index_t, ثابت xkb_keysym_t **) )
SDL_WAYLAND_SYM(xkb_level_index_t, xkb_keymap_رقم_levels_for_کلید, (ساختار xkb_keymap *, xkb_keycode_t, xkb_layout_index_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keysym_to_utf32, (xkb_keysym_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keymap_mod_get_index, (ساختار xkb_keymap *, ثابت نویسه *) )
SDL_WAYLAND_SYM(ثابت نویسه *, xkb_keymap_layout_get_name, (ساختار xkb_keymap *, xkb_layout_index_t))

#اگر SDL_XKBCOMMON_CHECK_VERSION(1, 0, 0)
SDL_WAYLAND_SYM(size_t, xkb_keymap_کلید_get_mods_for_level, (ساختار xkb_keymap *, xkb_keycode_t, xkb_layout_index_t, xkb_level_index_t, xkb_mod_mask_t *, size_t) )
#وگرنه
// Only needed in the fallback replacement for xkb_keymap_key_get_mods_for_level().
SDL_WAYLAND_SYM(xkb_level_index_t, xkb_state_کلید_get_level, (ساختار xkb_state *, xkb_keycode_t, xkb_layout_index_t) )
#endif

#اگر SDL_XKBCOMMON_CHECK_VERSION(1, 10, 0)
SDL_WAYLAND_SYM(xkb_mod_mask_t, xkb_keymap_mod_get_mask, (ساختار xkb_keymap *, ثابت نویسه *))
#endif

#ifdef HAVE_LIBDECOR_H
SDL_WAYLAND_MODULE(WAYLAND_LIBDECOR)

#اگر defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_VERSION(0, 3, 0)
#define SDL_libdecor_constsince03 ثابت
#وگرنه
#define SDL_libdecor_constsince03 /* nothing */
#endif

SDL_WAYLAND_SYM(تهی, libdecor_unref, (ساختار libdecor *))
SDL_WAYLAND_SYM(ساختار libdecor *, libdecor_new, (ساختار wl_display *,\
                                                  SDL_libdecor_constsince03 ساختار libdecor_interface *))
SDL_WAYLAND_SYM(ساختار libdecor_frame *, libdecor_decorate, (ساختار libdecor *,\
                                                             ساختار wl_surface *,\
                                                             SDL_libdecor_constsince03 ساختار libdecor_frame_interface *,\
                                                             تهی *))
SDL_WAYLAND_SYM(تهی, libdecor_frame_unref, (ساختار libdecor_frame *))
SDL_WAYLAND_SYM(تهی, libdecor_frame_set_title, (ساختار libdecor_frame *, ثابت نویسه *))
SDL_WAYLAND_SYM(تهی, libdecor_frame_set_app_id, (ساختار libdecor_frame *, ثابت نویسه *))
SDL_WAYLAND_SYM(تهی, libdecor_frame_set_max_content_size, (ساختار libdecor_frame *frame,\
                                                            صحیح content_width,\
                                                            صحیح content_height))
SDL_WAYLAND_SYM(تهی, libdecor_frame_set_min_content_size, (ساختار libdecor_frame *frame,\
                                                            صحیح content_width,\
                                                            صحیح content_height))
SDL_WAYLAND_SYM(تهی, libdecor_frame_resize, (ساختار libdecor_frame *,\
                                              ساختار wl_seat *,\
                                              uint32_t,\
                                              شمارش libdecor_resize_edge))
SDL_WAYLAND_SYM(تهی, libdecor_frame_move, (ساختار libdecor_frame *,\
                                            ساختار wl_seat *,\
                                            uint32_t))
SDL_WAYLAND_SYM(تهی, libdecor_frame_commit, (ساختار libdecor_frame *,\
                                              ساختار libdecor_state *,\
                                              ساختار libdecor_configuration *))
SDL_WAYLAND_SYM(تهی, libdecor_frame_set_minimized, (ساختار libdecor_frame *))
SDL_WAYLAND_SYM(تهی, libdecor_frame_set_maximized, (ساختار libdecor_frame *))
SDL_WAYLAND_SYM(تهی, libdecor_frame_unset_maximized, (ساختار libdecor_frame *))
SDL_WAYLAND_SYM(تهی, libdecor_frame_set_fullscreen, (ساختار libdecor_frame *, ساختار wl_output *))
SDL_WAYLAND_SYM(تهی, libdecor_frame_unset_fullscreen, (ساختار libdecor_frame *))
SDL_WAYLAND_SYM(تهی, libdecor_frame_set_capabilities, (ساختار libdecor_frame *, \
                                                        شمارش libdecor_capabilities))
SDL_WAYLAND_SYM(تهی, libdecor_frame_unset_capabilities, (ساختار libdecor_frame *, \
                                                          شمارش libdecor_capabilities))
SDL_WAYLAND_SYM(bool, libdecor_frame_has_capability, (ساختار libdecor_frame *, \
                                                      شمارش libdecor_capabilities))
SDL_WAYLAND_SYM(تهی, libdecor_frame_set_visibility, (ساختار libdecor_frame *, bool))
SDL_WAYLAND_SYM(bool, libdecor_frame_is_visible, (ساختار libdecor_frame *))
SDL_WAYLAND_SYM(bool, libdecor_frame_is_floating, (ساختار libdecor_frame *))
SDL_WAYLAND_SYM(تهی, libdecor_frame_set_parent, (ساختار libdecor_frame *,\
                                                  ساختار libdecor_frame *))
SDL_WAYLAND_SYM(تهی, libdecor_frame_show_window_menu, (ساختار libdecor_frame *, ساختار wl_seat *, uint32_t, صحیح, صحیح))
SDL_WAYLAND_SYM(ساختار xdg_surface *, libdecor_frame_get_xdg_surface, (ساختار libdecor_frame *))
SDL_WAYLAND_SYM(ساختار xdg_toplevel *, libdecor_frame_get_xdg_toplevel, (ساختار libdecor_frame *))
SDL_WAYLAND_SYM(تهی, libdecor_frame_translate_coordinate, (ساختار libdecor_frame *, صحیح, صحیح, صحیح *, صحیح *))
SDL_WAYLAND_SYM(تهی, libdecor_frame_map, (ساختار libdecor_frame *))
SDL_WAYLAND_SYM(ساختار libdecor_state *, libdecor_state_new, (صحیح, صحیح))
SDL_WAYLAND_SYM(تهی, libdecor_state_free, (ساختار libdecor_state *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_content_size, (ساختار libdecor_configuration *,\
                                                                ساختار libdecor_frame *,\
                                                                صحیح *,\
                                                                صحیح *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_window_state, (ساختار libdecor_configuration *,\
                                                                شمارش libdecor_window_state *))
SDL_WAYLAND_SYM(صحیح, libdecor_dispatch, (ساختار libdecor *, صحیح))

#اگر defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_VERSION(0, 2, 0)
// Only found in libdecor 0.1.1 or higher, so failure to load them is not fatal.
SDL_WAYLAND_SYM_OPT(تهی, libdecor_frame_get_min_content_size, (ثابت ساختار libdecor_frame *,\
                                                            صحیح *,\
                                                            صحیح *))
SDL_WAYLAND_SYM_OPT(تهی, libdecor_frame_get_max_content_size, (ثابت ساختار libdecor_frame *,\
                                                            صحیح *,\
                                                            صحیح *))
#endif

#اگر defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_VERSION(0, 3, 0)
SDL_WAYLAND_SYM_OPT(شمارش libdecor_wm_capabilities, libdecor_frame_get_wm_capabilities, (ساختار libdecor_frame *))
#endif

#undef SDL_libdecor_constsince03

#endif

#undef SDL_WAYLAND_MODULE
#undef SDL_WAYLAND_SYM
#undef SDL_WAYLAND_SYM_OPT

/* *INDENT-ON* */ // clang-format on
