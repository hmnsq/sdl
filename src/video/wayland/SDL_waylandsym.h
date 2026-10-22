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
SDL_WAYLAND_SYM(void, wl_proxy_marshal, (sa_nracanaa wl_proxy *, uint32_t, ...))
SDL_WAYLAND_SYM(sa_nracanaa wl_proxy *, wl_proxy_create, (sa_nracanaa wl_proxy *, const sa_nracanaa wl_interface *))
SDL_WAYLAND_SYM(void, wl_proxy_destroy, (sa_nracanaa wl_proxy *))
SDL_WAYLAND_SYM(ကိန်းပြည့်, wl_proxy_add_listener, (sa_nracanaa wl_proxy *, void (**)(void), void *))
SDL_WAYLAND_SYM(void, wl_proxy_set_user_data, (sa_nracanaa wl_proxy *, void *))
SDL_WAYLAND_SYM(void *, wl_proxy_get_user_data, (sa_nracanaa wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_version, (sa_nracanaa wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_id, (sa_nracanaa wl_proxy *))
SDL_WAYLAND_SYM(const var_na *, wl_proxy_get_class, (sa_nracanaa wl_proxy *))
SDL_WAYLAND_SYM(void, wl_proxy_set_queue, (sa_nracanaa wl_proxy *, sa_nracanaa wl_event_queue *))
SDL_WAYLAND_SYM(void *, wl_proxy_create_wrapper, (void *))
SDL_WAYLAND_SYM(void, wl_proxy_wrapper_destroy, (void *))
SDL_WAYLAND_SYM(sa_nracanaa wl_display *, wl_display_connect, (const var_na *))
SDL_WAYLAND_SYM(sa_nracanaa wl_display *, wl_display_connect_to_fd, (ကိန်းပြည့်))
SDL_WAYLAND_SYM(void, wl_display_disconnect, (sa_nracanaa wl_display *))
SDL_WAYLAND_SYM(ကိန်းပြည့်, wl_display_get_fd, (sa_nracanaa wl_display *))
SDL_WAYLAND_SYM(ကိန်းပြည့်, wl_display_dispatch, (sa_nracanaa wl_display *))
SDL_WAYLAND_SYM(ကိန်းပြည့်, wl_display_dispatch_queue, (sa_nracanaa wl_display *, sa_nracanaa wl_event_queue *))
SDL_WAYLAND_SYM(ကိန်းပြည့်, wl_display_dispatch_queue_pending, (sa_nracanaa wl_display *, sa_nracanaa wl_event_queue *))
SDL_WAYLAND_SYM(ကိန်းပြည့်, wl_display_dispatch_pending, (sa_nracanaa wl_display *))
SDL_WAYLAND_SYM(ကိန်းပြည့်, wl_display_prepare_read, (sa_nracanaa wl_display *))
SDL_WAYLAND_SYM(ကိန်းပြည့်, wl_display_prepare_read_queue, (sa_nracanaa wl_display *, sa_nracanaa wl_event_queue *))
SDL_WAYLAND_SYM(ကိန်းပြည့်, wl_display_read_events, (sa_nracanaa wl_display *))
SDL_WAYLAND_SYM(void, wl_display_cancel_read, (sa_nracanaa wl_display *))
SDL_WAYLAND_SYM(ကိန်းပြည့်, wl_display_get_error, (sa_nracanaa wl_display *))
SDL_WAYLAND_SYM(ကိန်းပြည့်, wl_display_flush, (sa_nracanaa wl_display *))
SDL_WAYLAND_SYM(ကိန်းပြည့်, wl_display_roundtrip, (sa_nracanaa wl_display *))
SDL_WAYLAND_SYM(sa_nracanaa wl_event_queue *, wl_display_create_queue, (sa_nracanaa wl_display *))
SDL_WAYLAND_SYM(void, wl_event_queue_destroy, (sa_nracanaa wl_event_queue *))
SDL_WAYLAND_SYM(void, wl_log_set_handler_client, (wl_log_func_t))
SDL_WAYLAND_SYM(void, wl_list_init, (sa_nracanaa wl_list *))
SDL_WAYLAND_SYM(void, wl_list_insert, (sa_nracanaa wl_list *, sa_nracanaa wl_list *) )
SDL_WAYLAND_SYM(void, wl_list_remove, (sa_nracanaa wl_list *))
SDL_WAYLAND_SYM(ကိန်းပြည့်, wl_list_length, (const sa_nracanaa wl_list *))
SDL_WAYLAND_SYM(ကိန်းပြည့်, wl_list_empty, (const sa_nracanaa wl_list *))
SDL_WAYLAND_SYM(void, wl_list_insert_list, (sa_nracanaa wl_list *, sa_nracanaa wl_list *))
SDL_WAYLAND_SYM(void, wl_array_init, (sa_nracanaa wl_array *))
SDL_WAYLAND_SYM(void, wl_array_release, (sa_nracanaa wl_array *))
SDL_WAYLAND_SYM(void *, wl_array_add, (sa_nracanaa wl_array *, size_t))
SDL_WAYLAND_SYM(ကိန်းပြည့်, wl_array_copy, (sa_nracanaa wl_array *, sa_nracanaa wl_array *))
SDL_WAYLAND_SYM(sa_nracanaa wl_proxy *, wl_proxy_marshal_constructor, (sa_nracanaa wl_proxy *, uint32_t opcode, const sa_nracanaa wl_interface *interface, ...))
SDL_WAYLAND_SYM(sa_nracanaa wl_proxy *, wl_proxy_marshal_constructor_versioned, (sa_nracanaa wl_proxy *proxy, uint32_t opcode, const sa_nracanaa wl_interface *interface, uint32_t version, ...))
SDL_WAYLAND_SYM(void, wl_proxy_set_tag, (sa_nracanaa wl_proxy *, const var_na * const *))
SDL_WAYLAND_SYM(const var_na * const *, wl_proxy_get_tag, (sa_nracanaa wl_proxy *))

#အကယ်၍ SDL_WAYLAND_CHECK_VERSION(1, 20, 0)
/* wayland-scanner 1.20 generates code that will call these, so these are
 * non-optional when we are compiling against Wayland 1.20. We don't
 * explicitly call them ourselves, though, so if we are only compiling
 * against Wayland 1.18, they're unnecessary. */
SDL_WAYLAND_SYM(sa_nracanaa wl_proxy *, wl_proxy_marshal_flags, (sa_nracanaa wl_proxy *proxy, uint32_t opcode, const sa_nracanaa wl_interface *interface, uint32_t version, uint32_t flags, ...))
SDL_WAYLAND_SYM(sa_nracanaa wl_proxy *, wl_proxy_marshal_array_flags, (sa_nracanaa wl_proxy *proxy, uint32_t opcode, const sa_nracanaa wl_interface *interface, uint32_t version,  uint32_t flags, sa_ngha wl_argument *args))
#endif

#အကယ်၍ SDL_WAYLAND_CHECK_VERSION(1, 23, 0) || defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC)
SDL_WAYLAND_SYM_OPT(sa_nracanaa wl_event_queue *, wl_display_create_queue_with_name, (sa_nracanaa wl_display *display, const var_na *name))
#endif

#အကယ်၍ 0 // TODO RECONNECT: See waylandvideo.c for more information!
#အကယ်၍ SDL_WAYLAND_CHECK_VERSION(broken, on, purpose)
SDL_WAYLAND_SYM(ကိန်းပြည့်, wl_display_reconnect, (sa_nracanaa wl_display *))
#endif
#endif // 0

SDL_WAYLAND_MODULE(WAYLAND_EGL)
SDL_WAYLAND_SYM(sa_nracanaa wl_egl_window *, wl_egl_window_create, (sa_nracanaa wl_surface *, ကိန်းပြည့်, ကိန်းပြည့်))
SDL_WAYLAND_SYM(void, wl_egl_window_destroy, (sa_nracanaa wl_egl_window *))
SDL_WAYLAND_SYM(void, wl_egl_window_resize, (sa_nracanaa wl_egl_window *, ကိန်းပြည့်, ကိန်းပြည့်, ကိန်းပြည့်, ကိန်းပြည့်))
SDL_WAYLAND_SYM(void, wl_egl_window_get_attached_size, (sa_nracanaa wl_egl_window *, ကိန်းပြည့် *, ကိန်းပြည့် *))

SDL_WAYLAND_MODULE(WAYLAND_CURSOR)
SDL_WAYLAND_SYM(sa_nracanaa wl_cursor_theme *, wl_cursor_theme_load, (const var_na *, ကိန်းပြည့် , sa_nracanaa wl_shm *))
SDL_WAYLAND_SYM(void, wl_cursor_theme_destroy, (sa_nracanaa wl_cursor_theme *))
SDL_WAYLAND_SYM(sa_nracanaa wl_cursor *, wl_cursor_theme_get_cursor, (sa_nracanaa wl_cursor_theme *, const var_na *))
SDL_WAYLAND_SYM(sa_nracanaa wl_buffer *, wl_cursor_image_get_buffer, (sa_nracanaa wl_cursor_image *))
SDL_WAYLAND_SYM(ကိန်းပြည့်, wl_cursor_frame, (sa_nracanaa wl_cursor *, uint32_t))

SDL_WAYLAND_MODULE(WAYLAND_XKB)
SDL_WAYLAND_SYM(ကိန်းပြည့်, xkb_state_key_get_syms, (sa_nracanaa xkb_state *, xkb_keycode_t, const xkb_keysym_t **))
SDL_WAYLAND_SYM(ကိန်းပြည့်, xkb_keysym_to_utf8, (xkb_keysym_t, var_na *, size_t) )
SDL_WAYLAND_SYM(sa_nracanaa xkb_keymap *, xkb_keymap_new_from_string, (sa_nracanaa xkb_context *, const var_na *, ga_nanaa xkb_keymap_format, ga_nanaa xkb_keymap_compile_flags))
SDL_WAYLAND_SYM(sa_nracanaa xkb_state *, xkb_state_new, (sa_nracanaa xkb_keymap *) )
SDL_WAYLAND_SYM(ကိန်းပြည့်, xkb_keymap_key_repeats, (sa_nracanaa xkb_keymap *keymap, xkb_keycode_t key) )
SDL_WAYLAND_SYM(void, xkb_keymap_unref, (sa_nracanaa xkb_keymap *) )
SDL_WAYLAND_SYM(void, xkb_state_unref, (sa_nracanaa xkb_state *) )
SDL_WAYLAND_SYM(void, xkb_context_unref, (sa_nracanaa xkb_context *) )
SDL_WAYLAND_SYM(sa_nracanaa xkb_context *, xkb_context_new, (ga_nanaa xkb_context_flags flags) )
SDL_WAYLAND_SYM(ga_nanaa xkb_state_component, xkb_state_update_mask, (sa_nracanaa xkb_state *state,\
                      xkb_mod_mask_t depressed_mods,\
                      xkb_mod_mask_t latched_mods,\
                      xkb_mod_mask_t locked_mods,\
                      xkb_layout_index_t depressed_layout,\
                      xkb_layout_index_t latched_layout,\
                      xkb_layout_index_t locked_layout) )
SDL_WAYLAND_SYM(sa_nracanaa xkb_compose_table *, xkb_compose_table_new_from_locale, (sa_nracanaa xkb_context *,\
                      const var_na *locale, ga_nanaa xkb_compose_compile_flags) )
SDL_WAYLAND_SYM(void, xkb_compose_state_reset, (sa_nracanaa xkb_compose_state *) )
SDL_WAYLAND_SYM(void, xkb_compose_table_unref, (sa_nracanaa xkb_compose_table *) )
SDL_WAYLAND_SYM(sa_nracanaa xkb_compose_state *, xkb_compose_state_new, (sa_nracanaa xkb_compose_table *, ga_nanaa xkb_compose_state_flags) )
SDL_WAYLAND_SYM(void, xkb_compose_state_unref, (sa_nracanaa xkb_compose_state *) )
SDL_WAYLAND_SYM(ga_nanaa xkb_compose_feed_result, xkb_compose_state_feed, (sa_nracanaa xkb_compose_state *, xkb_keysym_t) )
SDL_WAYLAND_SYM(ga_nanaa xkb_compose_status, xkb_compose_state_get_status, (sa_nracanaa xkb_compose_state *) )
SDL_WAYLAND_SYM(xkb_keysym_t, xkb_compose_state_get_one_sym, (sa_nracanaa xkb_compose_state *) )
SDL_WAYLAND_SYM(void, xkb_keymap_key_for_each, (sa_nracanaa xkb_keymap *, xkb_keymap_key_iter_t, void *) )
SDL_WAYLAND_SYM(xkb_layout_index_t, xkb_keymap_num_layouts, (sa_nracanaa xkb_keymap *) )
SDL_WAYLAND_SYM(ကိန်းပြည့်, xkb_keymap_key_get_syms_by_level, (sa_nracanaa xkb_keymap *, xkb_keycode_t, xkb_layout_index_t, xkb_level_index_t, const xkb_keysym_t **) )
SDL_WAYLAND_SYM(xkb_level_index_t, xkb_keymap_num_levels_for_key, (sa_nracanaa xkb_keymap *, xkb_keycode_t, xkb_layout_index_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keysym_to_utf32, (xkb_keysym_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keymap_mod_get_index, (sa_nracanaa xkb_keymap *, const var_na *) )
SDL_WAYLAND_SYM(const var_na *, xkb_keymap_layout_get_name, (sa_nracanaa xkb_keymap *, xkb_layout_index_t))

#အကယ်၍ SDL_XKBCOMMON_CHECK_VERSION(1, 0, 0)
SDL_WAYLAND_SYM(size_t, xkb_keymap_key_get_mods_for_level, (sa_nracanaa xkb_keymap *, xkb_keycode_t, xkb_layout_index_t, xkb_level_index_t, xkb_mod_mask_t *, size_t) )
#မဟုတ်ပါက
// Only needed in the fallback replacement for xkb_keymap_key_get_mods_for_level().
SDL_WAYLAND_SYM(xkb_level_index_t, xkb_state_key_get_level, (sa_nracanaa xkb_state *, xkb_keycode_t, xkb_layout_index_t) )
#endif

#အကယ်၍ SDL_XKBCOMMON_CHECK_VERSION(1, 10, 0)
SDL_WAYLAND_SYM(xkb_mod_mask_t, xkb_keymap_mod_get_mask, (sa_nracanaa xkb_keymap *, const var_na *))
#endif

#ifdef HAVE_LIBDECOR_H
SDL_WAYLAND_MODULE(WAYLAND_LIBDECOR)

#အကယ်၍ defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_VERSION(0, 3, 0)
#define SDL_libdecor_constsince03 const
#မဟုတ်ပါက
#define SDL_libdecor_constsince03 /* nothing */
#endif

SDL_WAYLAND_SYM(void, libdecor_unref, (sa_nracanaa libdecor *))
SDL_WAYLAND_SYM(sa_nracanaa libdecor *, libdecor_new, (sa_nracanaa wl_display *,\
                                                  SDL_libdecor_constsince03 sa_nracanaa libdecor_interface *))
SDL_WAYLAND_SYM(sa_nracanaa libdecor_frame *, libdecor_decorate, (sa_nracanaa libdecor *,\
                                                             sa_nracanaa wl_surface *,\
                                                             SDL_libdecor_constsince03 sa_nracanaa libdecor_frame_interface *,\
                                                             void *))
SDL_WAYLAND_SYM(void, libdecor_frame_unref, (sa_nracanaa libdecor_frame *))
SDL_WAYLAND_SYM(void, libdecor_frame_set_title, (sa_nracanaa libdecor_frame *, const var_na *))
SDL_WAYLAND_SYM(void, libdecor_frame_set_app_id, (sa_nracanaa libdecor_frame *, const var_na *))
SDL_WAYLAND_SYM(void, libdecor_frame_set_max_content_size, (sa_nracanaa libdecor_frame *frame,\
                                                            ကိန်းပြည့် content_width,\
                                                            ကိန်းပြည့် content_height))
SDL_WAYLAND_SYM(void, libdecor_frame_set_min_content_size, (sa_nracanaa libdecor_frame *frame,\
                                                            ကိန်းပြည့် content_width,\
                                                            ကိန်းပြည့် content_height))
SDL_WAYLAND_SYM(void, libdecor_frame_resize, (sa_nracanaa libdecor_frame *,\
                                              sa_nracanaa wl_seat *,\
                                              uint32_t,\
                                              ga_nanaa libdecor_resize_edge))
SDL_WAYLAND_SYM(void, libdecor_frame_move, (sa_nracanaa libdecor_frame *,\
                                            sa_nracanaa wl_seat *,\
                                            uint32_t))
SDL_WAYLAND_SYM(void, libdecor_frame_commit, (sa_nracanaa libdecor_frame *,\
                                              sa_nracanaa libdecor_state *,\
                                              sa_nracanaa libdecor_configuration *))
SDL_WAYLAND_SYM(void, libdecor_frame_set_minimized, (sa_nracanaa libdecor_frame *))
SDL_WAYLAND_SYM(void, libdecor_frame_set_maximized, (sa_nracanaa libdecor_frame *))
SDL_WAYLAND_SYM(void, libdecor_frame_unset_maximized, (sa_nracanaa libdecor_frame *))
SDL_WAYLAND_SYM(void, libdecor_frame_set_fullscreen, (sa_nracanaa libdecor_frame *, sa_nracanaa wl_output *))
SDL_WAYLAND_SYM(void, libdecor_frame_unset_fullscreen, (sa_nracanaa libdecor_frame *))
SDL_WAYLAND_SYM(void, libdecor_frame_set_capabilities, (sa_nracanaa libdecor_frame *, \
                                                        ga_nanaa libdecor_capabilities))
SDL_WAYLAND_SYM(void, libdecor_frame_unset_capabilities, (sa_nracanaa libdecor_frame *, \
                                                          ga_nanaa libdecor_capabilities))
SDL_WAYLAND_SYM(bool, libdecor_frame_has_capability, (sa_nracanaa libdecor_frame *, \
                                                      ga_nanaa libdecor_capabilities))
SDL_WAYLAND_SYM(void, libdecor_frame_set_visibility, (sa_nracanaa libdecor_frame *, bool))
SDL_WAYLAND_SYM(bool, libdecor_frame_is_visible, (sa_nracanaa libdecor_frame *))
SDL_WAYLAND_SYM(bool, libdecor_frame_is_floating, (sa_nracanaa libdecor_frame *))
SDL_WAYLAND_SYM(void, libdecor_frame_set_parent, (sa_nracanaa libdecor_frame *,\
                                                  sa_nracanaa libdecor_frame *))
SDL_WAYLAND_SYM(void, libdecor_frame_show_window_menu, (sa_nracanaa libdecor_frame *, sa_nracanaa wl_seat *, uint32_t, ကိန်းပြည့်, ကိန်းပြည့်))
SDL_WAYLAND_SYM(sa_nracanaa xdg_surface *, libdecor_frame_get_xdg_surface, (sa_nracanaa libdecor_frame *))
SDL_WAYLAND_SYM(sa_nracanaa xdg_toplevel *, libdecor_frame_get_xdg_toplevel, (sa_nracanaa libdecor_frame *))
SDL_WAYLAND_SYM(void, libdecor_frame_translate_coordinate, (sa_nracanaa libdecor_frame *, ကိန်းပြည့်, ကိန်းပြည့်, ကိန်းပြည့် *, ကိန်းပြည့် *))
SDL_WAYLAND_SYM(void, libdecor_frame_map, (sa_nracanaa libdecor_frame *))
SDL_WAYLAND_SYM(sa_nracanaa libdecor_state *, libdecor_state_new, (ကိန်းပြည့်, ကိန်းပြည့်))
SDL_WAYLAND_SYM(void, libdecor_state_free, (sa_nracanaa libdecor_state *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_content_size, (sa_nracanaa libdecor_configuration *,\
                                                                sa_nracanaa libdecor_frame *,\
                                                                ကိန်းပြည့် *,\
                                                                ကိန်းပြည့် *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_window_state, (sa_nracanaa libdecor_configuration *,\
                                                                ga_nanaa libdecor_window_state *))
SDL_WAYLAND_SYM(ကိန်းပြည့်, libdecor_dispatch, (sa_nracanaa libdecor *, ကိန်းပြည့်))

#အကယ်၍ defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_VERSION(0, 2, 0)
// Only found in libdecor 0.1.1 or higher, so failure to load them is not fatal.
SDL_WAYLAND_SYM_OPT(void, libdecor_frame_get_min_content_size, (const sa_nracanaa libdecor_frame *,\
                                                            ကိန်းပြည့် *,\
                                                            ကိန်းပြည့် *))
SDL_WAYLAND_SYM_OPT(void, libdecor_frame_get_max_content_size, (const sa_nracanaa libdecor_frame *,\
                                                            ကိန်းပြည့် *,\
                                                            ကိန်းပြည့် *))
#endif

#အကယ်၍ defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_VERSION(0, 3, 0)
SDL_WAYLAND_SYM_OPT(ga_nanaa libdecor_wm_capabilities, libdecor_frame_get_wm_capabilities, (sa_nracanaa libdecor_frame *))
#endif

#undef SDL_libdecor_constsince03

#endif

#undef SDL_WAYLAND_MODULE
#undef SDL_WAYLAND_SYM
#undef SDL_WAYLAND_SYM_OPT

/* *INDENT-ON* */ // clang-format on
