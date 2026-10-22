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
SDL_WAYLAND_SYM(শূন্য, wl_proxy_marshal, (কাঠামো wl_proxy *, uint32_t, ...))
SDL_WAYLAND_SYM(কাঠামো wl_proxy *, wl_proxy_create, (কাঠামো wl_proxy *, ধ্রুবক কাঠামো wl_interface *))
SDL_WAYLAND_SYM(শূন্য, wl_proxy_destroy, (কাঠামো wl_proxy *))
SDL_WAYLAND_SYM(পূর্ণসংখ্যা, wl_proxy_add_listener, (কাঠামো wl_proxy *, শূন্য (**)(শূন্য), শূন্য *))
SDL_WAYLAND_SYM(শূন্য, wl_proxy_set_user_তথ্য, (কাঠামো wl_proxy *, শূন্য *))
SDL_WAYLAND_SYM(শূন্য *, wl_proxy_get_user_তথ্য, (কাঠামো wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_version, (কাঠামো wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_id, (কাঠামো wl_proxy *))
SDL_WAYLAND_SYM(ধ্রুবক অক্ষর *, wl_proxy_get_class, (কাঠামো wl_proxy *))
SDL_WAYLAND_SYM(শূন্য, wl_proxy_set_queue, (কাঠামো wl_proxy *, কাঠামো wl_event_queue *))
SDL_WAYLAND_SYM(শূন্য *, wl_proxy_create_wrapper, (শূন্য *))
SDL_WAYLAND_SYM(শূন্য, wl_proxy_wrapper_destroy, (শূন্য *))
SDL_WAYLAND_SYM(কাঠামো wl_display *, wl_display_connect, (ধ্রুবক অক্ষর *))
SDL_WAYLAND_SYM(কাঠামো wl_display *, wl_display_connect_to_fd, (পূর্ণসংখ্যা))
SDL_WAYLAND_SYM(শূন্য, wl_display_disconnect, (কাঠামো wl_display *))
SDL_WAYLAND_SYM(পূর্ণসংখ্যা, wl_display_get_fd, (কাঠামো wl_display *))
SDL_WAYLAND_SYM(পূর্ণসংখ্যা, wl_display_dispatch, (কাঠামো wl_display *))
SDL_WAYLAND_SYM(পূর্ণসংখ্যা, wl_display_dispatch_queue, (কাঠামো wl_display *, কাঠামো wl_event_queue *))
SDL_WAYLAND_SYM(পূর্ণসংখ্যা, wl_display_dispatch_queue_pending, (কাঠামো wl_display *, কাঠামো wl_event_queue *))
SDL_WAYLAND_SYM(পূর্ণসংখ্যা, wl_display_dispatch_pending, (কাঠামো wl_display *))
SDL_WAYLAND_SYM(পূর্ণসংখ্যা, wl_display_prepare_read, (কাঠামো wl_display *))
SDL_WAYLAND_SYM(পূর্ণসংখ্যা, wl_display_prepare_read_queue, (কাঠামো wl_display *, কাঠামো wl_event_queue *))
SDL_WAYLAND_SYM(পূর্ণসংখ্যা, wl_display_read_events, (কাঠামো wl_display *))
SDL_WAYLAND_SYM(শূন্য, wl_display_cancel_read, (কাঠামো wl_display *))
SDL_WAYLAND_SYM(পূর্ণসংখ্যা, wl_display_get_error, (কাঠামো wl_display *))
SDL_WAYLAND_SYM(পূর্ণসংখ্যা, wl_display_flush, (কাঠামো wl_display *))
SDL_WAYLAND_SYM(পূর্ণসংখ্যা, wl_display_roundtrip, (কাঠামো wl_display *))
SDL_WAYLAND_SYM(কাঠামো wl_event_queue *, wl_display_create_queue, (কাঠামো wl_display *))
SDL_WAYLAND_SYM(শূন্য, wl_event_queue_destroy, (কাঠামো wl_event_queue *))
SDL_WAYLAND_SYM(শূন্য, wl_log_set_handler_client, (wl_log_func_t))
SDL_WAYLAND_SYM(শূন্য, wl_list_init, (কাঠামো wl_list *))
SDL_WAYLAND_SYM(শূন্য, wl_list_ঢোকাও, (কাঠামো wl_list *, কাঠামো wl_list *) )
SDL_WAYLAND_SYM(শূন্য, wl_list_remove, (কাঠামো wl_list *))
SDL_WAYLAND_SYM(পূর্ণসংখ্যা, wl_list_দৈর্ঘ্য, (ধ্রুবক কাঠামো wl_list *))
SDL_WAYLAND_SYM(পূর্ণসংখ্যা, wl_list_empty, (ধ্রুবক কাঠামো wl_list *))
SDL_WAYLAND_SYM(শূন্য, wl_list_ঢোকাও_list, (কাঠামো wl_list *, কাঠামো wl_list *))
SDL_WAYLAND_SYM(শূন্য, wl_array_init, (কাঠামো wl_array *))
SDL_WAYLAND_SYM(শূন্য, wl_array_release, (কাঠামো wl_array *))
SDL_WAYLAND_SYM(শূন্য *, wl_array_add, (কাঠামো wl_array *, size_t))
SDL_WAYLAND_SYM(পূর্ণসংখ্যা, wl_array_copy, (কাঠামো wl_array *, কাঠামো wl_array *))
SDL_WAYLAND_SYM(কাঠামো wl_proxy *, wl_proxy_marshal_constructor, (কাঠামো wl_proxy *, uint32_t opcode, ধ্রুবক কাঠামো wl_interface *interface, ...))
SDL_WAYLAND_SYM(কাঠামো wl_proxy *, wl_proxy_marshal_constructor_versioned, (কাঠামো wl_proxy *proxy, uint32_t opcode, ধ্রুবক কাঠামো wl_interface *interface, uint32_t version, ...))
SDL_WAYLAND_SYM(শূন্য, wl_proxy_set_tag, (কাঠামো wl_proxy *, ধ্রুবক অক্ষর * ধ্রুবক *))
SDL_WAYLAND_SYM(ধ্রুবক অক্ষর * ধ্রুবক *, wl_proxy_get_tag, (কাঠামো wl_proxy *))

#যদি SDL_WAYLAND_CHECK_VERSION(1, 20, 0)
/* wayland-scanner 1.20 generates code that will call these, so these are
 * non-optional when we are compiling against Wayland 1.20. We don't
 * explicitly call them ourselves, though, so if we are only compiling
 * against Wayland 1.18, they're unnecessary. */
SDL_WAYLAND_SYM(কাঠামো wl_proxy *, wl_proxy_marshal_flags, (কাঠামো wl_proxy *proxy, uint32_t opcode, ধ্রুবক কাঠামো wl_interface *interface, uint32_t version, uint32_t flags, ...))
SDL_WAYLAND_SYM(কাঠামো wl_proxy *, wl_proxy_marshal_array_flags, (কাঠামো wl_proxy *proxy, uint32_t opcode, ধ্রুবক কাঠামো wl_interface *interface, uint32_t version,  uint32_t flags, সংঘ wl_argument *args))
#endif

#যদি SDL_WAYLAND_CHECK_VERSION(1, 23, 0) || defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC)
SDL_WAYLAND_SYM_OPT(কাঠামো wl_event_queue *, wl_display_create_queue_with_name, (কাঠামো wl_display *display, ধ্রুবক অক্ষর *name))
#endif

#যদি 0 // TODO RECONNECT: See waylandvideo.c for more information!
#যদি SDL_WAYLAND_CHECK_VERSION(broken, on, purpose)
SDL_WAYLAND_SYM(পূর্ণসংখ্যা, wl_display_reconnect, (কাঠামো wl_display *))
#endif
#endif // 0

SDL_WAYLAND_MODULE(WAYLAND_EGL)
SDL_WAYLAND_SYM(কাঠামো wl_egl_window *, wl_egl_window_create, (কাঠামো wl_surface *, পূর্ণসংখ্যা, পূর্ণসংখ্যা))
SDL_WAYLAND_SYM(শূন্য, wl_egl_window_destroy, (কাঠামো wl_egl_window *))
SDL_WAYLAND_SYM(শূন্য, wl_egl_window_resize, (কাঠামো wl_egl_window *, পূর্ণসংখ্যা, পূর্ণসংখ্যা, পূর্ণসংখ্যা, পূর্ণসংখ্যা))
SDL_WAYLAND_SYM(শূন্য, wl_egl_window_get_attached_আকার, (কাঠামো wl_egl_window *, পূর্ণসংখ্যা *, পূর্ণসংখ্যা *))

SDL_WAYLAND_MODULE(WAYLAND_CURSOR)
SDL_WAYLAND_SYM(কাঠামো wl_cursor_theme *, wl_cursor_theme_load, (ধ্রুবক অক্ষর *, পূর্ণসংখ্যা , কাঠামো wl_shm *))
SDL_WAYLAND_SYM(শূন্য, wl_cursor_theme_destroy, (কাঠামো wl_cursor_theme *))
SDL_WAYLAND_SYM(কাঠামো wl_cursor *, wl_cursor_theme_get_cursor, (কাঠামো wl_cursor_theme *, ধ্রুবক অক্ষর *))
SDL_WAYLAND_SYM(কাঠামো wl_বাফার *, wl_cursor_image_get_বাফার, (কাঠামো wl_cursor_image *))
SDL_WAYLAND_SYM(পূর্ণসংখ্যা, wl_cursor_frame, (কাঠামো wl_cursor *, uint32_t))

SDL_WAYLAND_MODULE(WAYLAND_XKB)
SDL_WAYLAND_SYM(পূর্ণসংখ্যা, xkb_state_চাবি_get_syms, (কাঠামো xkb_state *, xkb_keycode_t, ধ্রুবক xkb_keysym_t **))
SDL_WAYLAND_SYM(পূর্ণসংখ্যা, xkb_keysym_to_utf8, (xkb_keysym_t, অক্ষর *, size_t) )
SDL_WAYLAND_SYM(কাঠামো xkb_keymap *, xkb_keymap_new_from_string, (কাঠামো xkb_context *, ধ্রুবক অক্ষর *, গণনা xkb_keymap_format, গণনা xkb_keymap_compile_flags))
SDL_WAYLAND_SYM(কাঠামো xkb_state *, xkb_state_new, (কাঠামো xkb_keymap *) )
SDL_WAYLAND_SYM(পূর্ণসংখ্যা, xkb_keymap_চাবি_repeats, (কাঠামো xkb_keymap *keymap, xkb_keycode_t চাবি) )
SDL_WAYLAND_SYM(শূন্য, xkb_keymap_unref, (কাঠামো xkb_keymap *) )
SDL_WAYLAND_SYM(শূন্য, xkb_state_unref, (কাঠামো xkb_state *) )
SDL_WAYLAND_SYM(শূন্য, xkb_context_unref, (কাঠামো xkb_context *) )
SDL_WAYLAND_SYM(কাঠামো xkb_context *, xkb_context_new, (গণনা xkb_context_flags flags) )
SDL_WAYLAND_SYM(গণনা xkb_state_component, xkb_state_update_mask, (কাঠামো xkb_state *state,\
                      xkb_mod_mask_t depressed_mods,\
                      xkb_mod_mask_t latched_mods,\
                      xkb_mod_mask_t locked_mods,\
                      xkb_layout_সূচক_t depressed_layout,\
                      xkb_layout_সূচক_t latched_layout,\
                      xkb_layout_সূচক_t locked_layout) )
SDL_WAYLAND_SYM(কাঠামো xkb_compose_table *, xkb_compose_table_new_from_locale, (কাঠামো xkb_context *,\
                      ধ্রুবক অক্ষর *locale, গণনা xkb_compose_compile_flags) )
SDL_WAYLAND_SYM(শূন্য, xkb_compose_state_reset, (কাঠামো xkb_compose_state *) )
SDL_WAYLAND_SYM(শূন্য, xkb_compose_table_unref, (কাঠামো xkb_compose_table *) )
SDL_WAYLAND_SYM(কাঠামো xkb_compose_state *, xkb_compose_state_new, (কাঠামো xkb_compose_table *, গণনা xkb_compose_state_flags) )
SDL_WAYLAND_SYM(শূন্য, xkb_compose_state_unref, (কাঠামো xkb_compose_state *) )
SDL_WAYLAND_SYM(গণনা xkb_compose_feed_ফলাফল, xkb_compose_state_feed, (কাঠামো xkb_compose_state *, xkb_keysym_t) )
SDL_WAYLAND_SYM(গণনা xkb_compose_status, xkb_compose_state_get_status, (কাঠামো xkb_compose_state *) )
SDL_WAYLAND_SYM(xkb_keysym_t, xkb_compose_state_get_one_sym, (কাঠামো xkb_compose_state *) )
SDL_WAYLAND_SYM(শূন্য, xkb_keymap_চাবি_for_each, (কাঠামো xkb_keymap *, xkb_keymap_চাবি_iter_t, শূন্য *) )
SDL_WAYLAND_SYM(xkb_layout_সূচক_t, xkb_keymap_অঙ্ক_layouts, (কাঠামো xkb_keymap *) )
SDL_WAYLAND_SYM(পূর্ণসংখ্যা, xkb_keymap_চাবি_get_syms_by_level, (কাঠামো xkb_keymap *, xkb_keycode_t, xkb_layout_সূচক_t, xkb_level_সূচক_t, ধ্রুবক xkb_keysym_t **) )
SDL_WAYLAND_SYM(xkb_level_সূচক_t, xkb_keymap_অঙ্ক_levels_for_চাবি, (কাঠামো xkb_keymap *, xkb_keycode_t, xkb_layout_সূচক_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keysym_to_utf32, (xkb_keysym_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keymap_mod_get_সূচক, (কাঠামো xkb_keymap *, ধ্রুবক অক্ষর *) )
SDL_WAYLAND_SYM(ধ্রুবক অক্ষর *, xkb_keymap_layout_get_name, (কাঠামো xkb_keymap *, xkb_layout_সূচক_t))

#যদি SDL_XKBCOMMON_CHECK_VERSION(1, 0, 0)
SDL_WAYLAND_SYM(size_t, xkb_keymap_চাবি_get_mods_for_level, (কাঠামো xkb_keymap *, xkb_keycode_t, xkb_layout_সূচক_t, xkb_level_সূচক_t, xkb_mod_mask_t *, size_t) )
#অন্যথা
// Only needed in the fallback replacement for xkb_keymap_key_get_mods_for_level().
SDL_WAYLAND_SYM(xkb_level_সূচক_t, xkb_state_চাবি_get_level, (কাঠামো xkb_state *, xkb_keycode_t, xkb_layout_সূচক_t) )
#endif

#যদি SDL_XKBCOMMON_CHECK_VERSION(1, 10, 0)
SDL_WAYLAND_SYM(xkb_mod_mask_t, xkb_keymap_mod_get_mask, (কাঠামো xkb_keymap *, ধ্রুবক অক্ষর *))
#endif

#ifdef HAVE_LIBDECOR_H
SDL_WAYLAND_MODULE(WAYLAND_LIBDECOR)

#যদি defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_VERSION(0, 3, 0)
#define SDL_libdecor_constsince03 ধ্রুবক
#অন্যথা
#define SDL_libdecor_constsince03 /* nothing */
#endif

SDL_WAYLAND_SYM(শূন্য, libdecor_unref, (কাঠামো libdecor *))
SDL_WAYLAND_SYM(কাঠামো libdecor *, libdecor_new, (কাঠামো wl_display *,\
                                                  SDL_libdecor_constsince03 কাঠামো libdecor_interface *))
SDL_WAYLAND_SYM(কাঠামো libdecor_frame *, libdecor_decorate, (কাঠামো libdecor *,\
                                                             কাঠামো wl_surface *,\
                                                             SDL_libdecor_constsince03 কাঠামো libdecor_frame_interface *,\
                                                             শূন্য *))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_unref, (কাঠামো libdecor_frame *))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_set_title, (কাঠামো libdecor_frame *, ধ্রুবক অক্ষর *))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_set_app_id, (কাঠামো libdecor_frame *, ধ্রুবক অক্ষর *))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_set_max_content_আকার, (কাঠামো libdecor_frame *frame,\
                                                            পূর্ণসংখ্যা content_width,\
                                                            পূর্ণসংখ্যা content_height))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_set_min_content_আকার, (কাঠামো libdecor_frame *frame,\
                                                            পূর্ণসংখ্যা content_width,\
                                                            পূর্ণসংখ্যা content_height))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_resize, (কাঠামো libdecor_frame *,\
                                              কাঠামো wl_seat *,\
                                              uint32_t,\
                                              গণনা libdecor_resize_edge))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_move, (কাঠামো libdecor_frame *,\
                                            কাঠামো wl_seat *,\
                                            uint32_t))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_commit, (কাঠামো libdecor_frame *,\
                                              কাঠামো libdecor_state *,\
                                              কাঠামো libdecor_configuration *))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_set_minimized, (কাঠামো libdecor_frame *))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_set_maximized, (কাঠামো libdecor_frame *))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_unset_maximized, (কাঠামো libdecor_frame *))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_set_fullscreen, (কাঠামো libdecor_frame *, কাঠামো wl_output *))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_unset_fullscreen, (কাঠামো libdecor_frame *))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_set_capabilities, (কাঠামো libdecor_frame *, \
                                                        গণনা libdecor_capabilities))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_unset_capabilities, (কাঠামো libdecor_frame *, \
                                                          গণনা libdecor_capabilities))
SDL_WAYLAND_SYM(bool, libdecor_frame_has_capability, (কাঠামো libdecor_frame *, \
                                                      গণনা libdecor_capabilities))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_set_visibility, (কাঠামো libdecor_frame *, bool))
SDL_WAYLAND_SYM(bool, libdecor_frame_is_visible, (কাঠামো libdecor_frame *))
SDL_WAYLAND_SYM(bool, libdecor_frame_is_floating, (কাঠামো libdecor_frame *))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_set_parent, (কাঠামো libdecor_frame *,\
                                                  কাঠামো libdecor_frame *))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_show_window_menu, (কাঠামো libdecor_frame *, কাঠামো wl_seat *, uint32_t, পূর্ণসংখ্যা, পূর্ণসংখ্যা))
SDL_WAYLAND_SYM(কাঠামো xdg_surface *, libdecor_frame_get_xdg_surface, (কাঠামো libdecor_frame *))
SDL_WAYLAND_SYM(কাঠামো xdg_toplevel *, libdecor_frame_get_xdg_toplevel, (কাঠামো libdecor_frame *))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_translate_coordinate, (কাঠামো libdecor_frame *, পূর্ণসংখ্যা, পূর্ণসংখ্যা, পূর্ণসংখ্যা *, পূর্ণসংখ্যা *))
SDL_WAYLAND_SYM(শূন্য, libdecor_frame_map, (কাঠামো libdecor_frame *))
SDL_WAYLAND_SYM(কাঠামো libdecor_state *, libdecor_state_new, (পূর্ণসংখ্যা, পূর্ণসংখ্যা))
SDL_WAYLAND_SYM(শূন্য, libdecor_state_free, (কাঠামো libdecor_state *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_content_আকার, (কাঠামো libdecor_configuration *,\
                                                                কাঠামো libdecor_frame *,\
                                                                পূর্ণসংখ্যা *,\
                                                                পূর্ণসংখ্যা *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_window_state, (কাঠামো libdecor_configuration *,\
                                                                গণনা libdecor_window_state *))
SDL_WAYLAND_SYM(পূর্ণসংখ্যা, libdecor_dispatch, (কাঠামো libdecor *, পূর্ণসংখ্যা))

#যদি defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_VERSION(0, 2, 0)
// Only found in libdecor 0.1.1 or higher, so failure to load them is not fatal.
SDL_WAYLAND_SYM_OPT(শূন্য, libdecor_frame_get_min_content_আকার, (ধ্রুবক কাঠামো libdecor_frame *,\
                                                            পূর্ণসংখ্যা *,\
                                                            পূর্ণসংখ্যা *))
SDL_WAYLAND_SYM_OPT(শূন্য, libdecor_frame_get_max_content_আকার, (ধ্রুবক কাঠামো libdecor_frame *,\
                                                            পূর্ণসংখ্যা *,\
                                                            পূর্ণসংখ্যা *))
#endif

#যদি defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_VERSION(0, 3, 0)
SDL_WAYLAND_SYM_OPT(গণনা libdecor_wm_capabilities, libdecor_frame_get_wm_capabilities, (কাঠামো libdecor_frame *))
#endif

#undef SDL_libdecor_constsince03

#endif

#undef SDL_WAYLAND_MODULE
#undef SDL_WAYLAND_SYM
#undef SDL_WAYLAND_SYM_OPT

/* *INDENT-ON* */ // clang-format on
