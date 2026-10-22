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
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, wl_proxy_marshal, (ସଂରଚନା wl_proxy *, uint32_t, ...))
SDL_WAYLAND_SYM(ସଂରଚନା wl_proxy *, wl_proxy_create, (ସଂରଚନା wl_proxy *, ଅଚଳ ସଂରଚନା wl_interface *))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, wl_proxy_destroy, (ସଂରଚନା wl_proxy *))
SDL_WAYLAND_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, wl_proxy_add_listener, (ସଂରଚନା wl_proxy *, ଶୂନ୍ୟ (**)(ଶୂନ୍ୟ), ଶୂନ୍ୟ *))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, wl_proxy_set_user_data, (ସଂରଚନା wl_proxy *, ଶୂନ୍ୟ *))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ *, wl_proxy_get_user_data, (ସଂରଚନା wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_version, (ସଂରଚନା wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_id, (ସଂରଚନା wl_proxy *))
SDL_WAYLAND_SYM(ଅଚଳ ଅକ୍ଷର *, wl_proxy_get_class, (ସଂରଚନା wl_proxy *))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, wl_proxy_set_queue, (ସଂରଚନା wl_proxy *, ସଂରଚନା wl_event_queue *))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ *, wl_proxy_create_wrapper, (ଶୂନ୍ୟ *))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, wl_proxy_wrapper_destroy, (ଶୂନ୍ୟ *))
SDL_WAYLAND_SYM(ସଂରଚନା wl_display *, wl_display_connect, (ଅଚଳ ଅକ୍ଷର *))
SDL_WAYLAND_SYM(ସଂରଚନା wl_display *, wl_display_connect_to_fd, (ପୂର୍ଣ୍ଣସଂଖ୍ୟା))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, wl_display_disconnect, (ସଂରଚନା wl_display *))
SDL_WAYLAND_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, wl_display_get_fd, (ସଂରଚନା wl_display *))
SDL_WAYLAND_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, wl_display_dispatch, (ସଂରଚନା wl_display *))
SDL_WAYLAND_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, wl_display_dispatch_queue, (ସଂରଚନା wl_display *, ସଂରଚନା wl_event_queue *))
SDL_WAYLAND_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, wl_display_dispatch_queue_pending, (ସଂରଚନା wl_display *, ସଂରଚନା wl_event_queue *))
SDL_WAYLAND_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, wl_display_dispatch_pending, (ସଂରଚନା wl_display *))
SDL_WAYLAND_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, wl_display_prepare_read, (ସଂରଚନା wl_display *))
SDL_WAYLAND_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, wl_display_prepare_read_queue, (ସଂରଚନା wl_display *, ସଂରଚନା wl_event_queue *))
SDL_WAYLAND_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, wl_display_read_events, (ସଂରଚନା wl_display *))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, wl_display_cancel_read, (ସଂରଚନା wl_display *))
SDL_WAYLAND_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, wl_display_get_error, (ସଂରଚନା wl_display *))
SDL_WAYLAND_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, wl_display_flush, (ସଂରଚନା wl_display *))
SDL_WAYLAND_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, wl_display_roundtrip, (ସଂରଚନା wl_display *))
SDL_WAYLAND_SYM(ସଂରଚନା wl_event_queue *, wl_display_create_queue, (ସଂରଚନା wl_display *))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, wl_event_queue_destroy, (ସଂରଚନା wl_event_queue *))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, wl_log_set_handler_client, (wl_log_func_t))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, wl_list_init, (ସଂରଚନା wl_list *))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, wl_list_ଭର୍ତ୍ତି, (ସଂରଚନା wl_list *, ସଂରଚନା wl_list *) )
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, wl_list_remove, (ସଂରଚନା wl_list *))
SDL_WAYLAND_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, wl_list_length, (ଅଚଳ ସଂରଚନା wl_list *))
SDL_WAYLAND_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, wl_list_empty, (ଅଚଳ ସଂରଚନା wl_list *))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, wl_list_ଭର୍ତ୍ତି_list, (ସଂରଚନା wl_list *, ସଂରଚନା wl_list *))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, wl_array_init, (ସଂରଚନା wl_array *))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, wl_array_release, (ସଂରଚନା wl_array *))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ *, wl_array_add, (ସଂରଚନା wl_array *, size_t))
SDL_WAYLAND_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, wl_array_copy, (ସଂରଚନା wl_array *, ସଂରଚନା wl_array *))
SDL_WAYLAND_SYM(ସଂରଚନା wl_proxy *, wl_proxy_marshal_constructor, (ସଂରଚନା wl_proxy *, uint32_t opcode, ଅଚଳ ସଂରଚନା wl_interface *interface, ...))
SDL_WAYLAND_SYM(ସଂରଚନା wl_proxy *, wl_proxy_marshal_constructor_versioned, (ସଂରଚନା wl_proxy *proxy, uint32_t opcode, ଅଚଳ ସଂରଚନା wl_interface *interface, uint32_t version, ...))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, wl_proxy_set_tag, (ସଂରଚନା wl_proxy *, ଅଚଳ ଅକ୍ଷର * ଅଚଳ *))
SDL_WAYLAND_SYM(ଅଚଳ ଅକ୍ଷର * ଅଚଳ *, wl_proxy_get_tag, (ସଂରଚନା wl_proxy *))

#ଯଦି SDL_WAYLAND_CHECK_VERSION(1, 20, 0)
/* wayland-scanner 1.20 generates code that will call these, so these are
 * non-optional when we are compiling against Wayland 1.20. We don't
 * explicitly call them ourselves, though, so if we are only compiling
 * against Wayland 1.18, they're unnecessary. */
SDL_WAYLAND_SYM(ସଂରଚନା wl_proxy *, wl_proxy_marshal_flags, (ସଂରଚନା wl_proxy *proxy, uint32_t opcode, ଅଚଳ ସଂରଚନା wl_interface *interface, uint32_t version, uint32_t flags, ...))
SDL_WAYLAND_SYM(ସଂରଚନା wl_proxy *, wl_proxy_marshal_array_flags, (ସଂରଚନା wl_proxy *proxy, uint32_t opcode, ଅଚଳ ସଂରଚନା wl_interface *interface, uint32_t version,  uint32_t flags, ସଂଘ wl_argument *args))
#endif

#ଯଦି SDL_WAYLAND_CHECK_VERSION(1, 23, 0) || defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC)
SDL_WAYLAND_SYM_OPT(ସଂରଚନା wl_event_queue *, wl_display_create_queue_with_name, (ସଂରଚନା wl_display *display, ଅଚଳ ଅକ୍ଷର *name))
#endif

#ଯଦି 0 // TODO RECONNECT: See waylandvideo.c for more information!
#ଯଦି SDL_WAYLAND_CHECK_VERSION(broken, on, purpose)
SDL_WAYLAND_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, wl_display_reconnect, (ସଂରଚନା wl_display *))
#endif
#endif // 0

SDL_WAYLAND_MODULE(WAYLAND_EGL)
SDL_WAYLAND_SYM(ସଂରଚନା wl_egl_window *, wl_egl_window_create, (ସଂରଚନା wl_surface *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, wl_egl_window_destroy, (ସଂରଚନା wl_egl_window *))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, wl_egl_window_resize, (ସଂରଚନା wl_egl_window *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, wl_egl_window_get_attached_size, (ସଂରଚନା wl_egl_window *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *))

SDL_WAYLAND_MODULE(WAYLAND_CURSOR)
SDL_WAYLAND_SYM(ସଂରଚନା wl_cursor_theme *, wl_cursor_theme_load, (ଅଚଳ ଅକ୍ଷର *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା , ସଂରଚନା wl_shm *))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, wl_cursor_theme_destroy, (ସଂରଚନା wl_cursor_theme *))
SDL_WAYLAND_SYM(ସଂରଚନା wl_cursor *, wl_cursor_theme_get_cursor, (ସଂରଚନା wl_cursor_theme *, ଅଚଳ ଅକ୍ଷର *))
SDL_WAYLAND_SYM(ସଂରଚନା wl_buffer *, wl_cursor_image_get_buffer, (ସଂରଚନା wl_cursor_image *))
SDL_WAYLAND_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, wl_cursor_frame, (ସଂରଚନା wl_cursor *, uint32_t))

SDL_WAYLAND_MODULE(WAYLAND_XKB)
SDL_WAYLAND_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, xkb_state_ଚାବି_get_syms, (ସଂରଚନା xkb_state *, xkb_keycode_t, ଅଚଳ xkb_keysym_t **))
SDL_WAYLAND_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, xkb_keysym_to_utf8, (xkb_keysym_t, ଅକ୍ଷର *, size_t) )
SDL_WAYLAND_SYM(ସଂରଚନା xkb_keymap *, xkb_keymap_new_from_string, (ସଂରଚନା xkb_context *, ଅଚଳ ଅକ୍ଷର *, ଗଣନା xkb_keymap_format, ଗଣନା xkb_keymap_compile_flags))
SDL_WAYLAND_SYM(ସଂରଚନା xkb_state *, xkb_state_new, (ସଂରଚନା xkb_keymap *) )
SDL_WAYLAND_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, xkb_keymap_ଚାବି_repeats, (ସଂରଚନା xkb_keymap *keymap, xkb_keycode_t ଚାବି) )
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, xkb_keymap_unref, (ସଂରଚନା xkb_keymap *) )
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, xkb_state_unref, (ସଂରଚନା xkb_state *) )
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, xkb_context_unref, (ସଂରଚନା xkb_context *) )
SDL_WAYLAND_SYM(ସଂରଚନା xkb_context *, xkb_context_new, (ଗଣନା xkb_context_flags flags) )
SDL_WAYLAND_SYM(ଗଣନା xkb_state_component, xkb_state_update_mask, (ସଂରଚନା xkb_state *state,\
                      xkb_mod_mask_t depressed_mods,\
                      xkb_mod_mask_t latched_mods,\
                      xkb_mod_mask_t locked_mods,\
                      xkb_layout_index_t depressed_layout,\
                      xkb_layout_index_t latched_layout,\
                      xkb_layout_index_t locked_layout) )
SDL_WAYLAND_SYM(ସଂରଚନା xkb_compose_table *, xkb_compose_table_new_from_locale, (ସଂରଚନା xkb_context *,\
                      ଅଚଳ ଅକ୍ଷର *locale, ଗଣନା xkb_compose_compile_flags) )
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, xkb_compose_state_reset, (ସଂରଚନା xkb_compose_state *) )
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, xkb_compose_table_unref, (ସଂରଚନା xkb_compose_table *) )
SDL_WAYLAND_SYM(ସଂରଚନା xkb_compose_state *, xkb_compose_state_new, (ସଂରଚନା xkb_compose_table *, ଗଣନା xkb_compose_state_flags) )
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, xkb_compose_state_unref, (ସଂରଚନା xkb_compose_state *) )
SDL_WAYLAND_SYM(ଗଣନା xkb_compose_feed_result, xkb_compose_state_feed, (ସଂରଚନା xkb_compose_state *, xkb_keysym_t) )
SDL_WAYLAND_SYM(ଗଣନା xkb_compose_status, xkb_compose_state_get_status, (ସଂରଚନା xkb_compose_state *) )
SDL_WAYLAND_SYM(xkb_keysym_t, xkb_compose_state_get_one_sym, (ସଂରଚନା xkb_compose_state *) )
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, xkb_keymap_ଚାବି_for_each, (ସଂରଚନା xkb_keymap *, xkb_keymap_ଚାବି_iter_t, ଶୂନ୍ୟ *) )
SDL_WAYLAND_SYM(xkb_layout_index_t, xkb_keymap_ଅଙ୍କ_layouts, (ସଂରଚନା xkb_keymap *) )
SDL_WAYLAND_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, xkb_keymap_ଚାବି_get_syms_by_level, (ସଂରଚନା xkb_keymap *, xkb_keycode_t, xkb_layout_index_t, xkb_level_index_t, ଅଚଳ xkb_keysym_t **) )
SDL_WAYLAND_SYM(xkb_level_index_t, xkb_keymap_ଅଙ୍କ_levels_for_ଚାବି, (ସଂରଚନା xkb_keymap *, xkb_keycode_t, xkb_layout_index_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keysym_to_utf32, (xkb_keysym_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keymap_mod_get_index, (ସଂରଚନା xkb_keymap *, ଅଚଳ ଅକ୍ଷର *) )
SDL_WAYLAND_SYM(ଅଚଳ ଅକ୍ଷର *, xkb_keymap_layout_get_name, (ସଂରଚନା xkb_keymap *, xkb_layout_index_t))

#ଯଦି SDL_XKBCOMMON_CHECK_VERSION(1, 0, 0)
SDL_WAYLAND_SYM(size_t, xkb_keymap_ଚାବି_get_mods_for_level, (ସଂରଚନା xkb_keymap *, xkb_keycode_t, xkb_layout_index_t, xkb_level_index_t, xkb_mod_mask_t *, size_t) )
#ଅନ୍ୟଥା
// Only needed in the fallback replacement for xkb_keymap_key_get_mods_for_level().
SDL_WAYLAND_SYM(xkb_level_index_t, xkb_state_ଚାବି_get_level, (ସଂରଚନା xkb_state *, xkb_keycode_t, xkb_layout_index_t) )
#endif

#ଯଦି SDL_XKBCOMMON_CHECK_VERSION(1, 10, 0)
SDL_WAYLAND_SYM(xkb_mod_mask_t, xkb_keymap_mod_get_mask, (ସଂରଚନା xkb_keymap *, ଅଚଳ ଅକ୍ଷର *))
#endif

#ifdef HAVE_LIBDECOR_H
SDL_WAYLAND_MODULE(WAYLAND_LIBDECOR)

#ଯଦି defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_VERSION(0, 3, 0)
#define SDL_libdecor_constsince03 ଅଚଳ
#ଅନ୍ୟଥା
#define SDL_libdecor_constsince03 /* nothing */
#endif

SDL_WAYLAND_SYM(ଶୂନ୍ୟ, libdecor_unref, (ସଂରଚନା libdecor *))
SDL_WAYLAND_SYM(ସଂରଚନା libdecor *, libdecor_new, (ସଂରଚନା wl_display *,\
                                                  SDL_libdecor_constsince03 ସଂରଚନା libdecor_interface *))
SDL_WAYLAND_SYM(ସଂରଚନା libdecor_frame *, libdecor_decorate, (ସଂରଚନା libdecor *,\
                                                             ସଂରଚନା wl_surface *,\
                                                             SDL_libdecor_constsince03 ସଂରଚନା libdecor_frame_interface *,\
                                                             ଶୂନ୍ୟ *))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, libdecor_frame_unref, (ସଂରଚନା libdecor_frame *))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, libdecor_frame_set_title, (ସଂରଚନା libdecor_frame *, ଅଚଳ ଅକ୍ଷର *))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, libdecor_frame_set_app_id, (ସଂରଚନା libdecor_frame *, ଅଚଳ ଅକ୍ଷର *))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, libdecor_frame_set_max_content_size, (ସଂରଚନା libdecor_frame *frame,\
                                                            ପୂର୍ଣ୍ଣସଂଖ୍ୟା content_width,\
                                                            ପୂର୍ଣ୍ଣସଂଖ୍ୟା content_height))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, libdecor_frame_set_min_content_size, (ସଂରଚନା libdecor_frame *frame,\
                                                            ପୂର୍ଣ୍ଣସଂଖ୍ୟା content_width,\
                                                            ପୂର୍ଣ୍ଣସଂଖ୍ୟା content_height))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, libdecor_frame_resize, (ସଂରଚନା libdecor_frame *,\
                                              ସଂରଚନା wl_seat *,\
                                              uint32_t,\
                                              ଗଣନା libdecor_resize_edge))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, libdecor_frame_move, (ସଂରଚନା libdecor_frame *,\
                                            ସଂରଚନା wl_seat *,\
                                            uint32_t))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, libdecor_frame_commit, (ସଂରଚନା libdecor_frame *,\
                                              ସଂରଚନା libdecor_state *,\
                                              ସଂରଚନା libdecor_configuration *))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, libdecor_frame_set_minimized, (ସଂରଚନା libdecor_frame *))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, libdecor_frame_set_maximized, (ସଂରଚନା libdecor_frame *))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, libdecor_frame_unset_maximized, (ସଂରଚନା libdecor_frame *))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, libdecor_frame_set_fullscreen, (ସଂରଚନା libdecor_frame *, ସଂରଚନା wl_output *))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, libdecor_frame_unset_fullscreen, (ସଂରଚନା libdecor_frame *))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, libdecor_frame_set_capabilities, (ସଂରଚନା libdecor_frame *, \
                                                        ଗଣନା libdecor_capabilities))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, libdecor_frame_unset_capabilities, (ସଂରଚନା libdecor_frame *, \
                                                          ଗଣନା libdecor_capabilities))
SDL_WAYLAND_SYM(bool, libdecor_frame_has_capability, (ସଂରଚନା libdecor_frame *, \
                                                      ଗଣନା libdecor_capabilities))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, libdecor_frame_set_visibility, (ସଂରଚନା libdecor_frame *, bool))
SDL_WAYLAND_SYM(bool, libdecor_frame_is_visible, (ସଂରଚନା libdecor_frame *))
SDL_WAYLAND_SYM(bool, libdecor_frame_is_floating, (ସଂରଚନା libdecor_frame *))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, libdecor_frame_set_parent, (ସଂରଚନା libdecor_frame *,\
                                                  ସଂରଚନା libdecor_frame *))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, libdecor_frame_show_window_menu, (ସଂରଚନା libdecor_frame *, ସଂରଚନା wl_seat *, uint32_t, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା))
SDL_WAYLAND_SYM(ସଂରଚନା xdg_surface *, libdecor_frame_get_xdg_surface, (ସଂରଚନା libdecor_frame *))
SDL_WAYLAND_SYM(ସଂରଚନା xdg_toplevel *, libdecor_frame_get_xdg_toplevel, (ସଂରଚନା libdecor_frame *))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, libdecor_frame_translate_coordinate, (ସଂରଚନା libdecor_frame *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, libdecor_frame_map, (ସଂରଚନା libdecor_frame *))
SDL_WAYLAND_SYM(ସଂରଚନା libdecor_state *, libdecor_state_new, (ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା))
SDL_WAYLAND_SYM(ଶୂନ୍ୟ, libdecor_state_free, (ସଂରଚନା libdecor_state *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_content_size, (ସଂରଚନା libdecor_configuration *,\
                                                                ସଂରଚନା libdecor_frame *,\
                                                                ପୂର୍ଣ୍ଣସଂଖ୍ୟା *,\
                                                                ପୂର୍ଣ୍ଣସଂଖ୍ୟା *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_window_state, (ସଂରଚନା libdecor_configuration *,\
                                                                ଗଣନା libdecor_window_state *))
SDL_WAYLAND_SYM(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, libdecor_dispatch, (ସଂରଚନା libdecor *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା))

#ଯଦି defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_VERSION(0, 2, 0)
// Only found in libdecor 0.1.1 or higher, so failure to load them is not fatal.
SDL_WAYLAND_SYM_OPT(ଶୂନ୍ୟ, libdecor_frame_get_min_content_size, (ଅଚଳ ସଂରଚନା libdecor_frame *,\
                                                            ପୂର୍ଣ୍ଣସଂଖ୍ୟା *,\
                                                            ପୂର୍ଣ୍ଣସଂଖ୍ୟା *))
SDL_WAYLAND_SYM_OPT(ଶୂନ୍ୟ, libdecor_frame_get_max_content_size, (ଅଚଳ ସଂରଚନା libdecor_frame *,\
                                                            ପୂର୍ଣ୍ଣସଂଖ୍ୟା *,\
                                                            ପୂର୍ଣ୍ଣସଂଖ୍ୟା *))
#endif

#ଯଦି defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_VERSION(0, 3, 0)
SDL_WAYLAND_SYM_OPT(ଗଣନା libdecor_wm_capabilities, libdecor_frame_get_wm_capabilities, (ସଂରଚନା libdecor_frame *))
#endif

#undef SDL_libdecor_constsince03

#endif

#undef SDL_WAYLAND_MODULE
#undef SDL_WAYLAND_SYM
#undef SDL_WAYLAND_SYM_OPT

/* *INDENT-ON* */ // clang-format on
