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

#अगर_अघोषित SDL_WAYLAND_MODULE
#घोषणा SDL_WAYLAND_MODULE(modname)
#पूर्ण_अगर

#अगर_अघोषित SDL_WAYLAND_SYM
#घोषणा SDL_WAYLAND_SYM(rc,fn,params)
#पूर्ण_अगर

#अगर_अघोषित SDL_WAYLAND_SYM_OPT
#घोषणा SDL_WAYLAND_SYM_OPT(rc,fn,params)
#पूर्ण_अगर

SDL_WAYLAND_MODULE(WAYLAND_CLIENT)
SDL_WAYLAND_SYM(व्योम, wl_proxy_marshal, (काष्ठा wl_proxy *, uint32_t, ...))
SDL_WAYLAND_SYM(काष्ठा wl_proxy *, wl_proxy_create, (काष्ठा wl_proxy *, स्थिर काष्ठा wl_interface *))
SDL_WAYLAND_SYM(व्योम, wl_proxy_destroy, (काष्ठा wl_proxy *))
SDL_WAYLAND_SYM(पूर्णांक, wl_proxy_add_listener, (काष्ठा wl_proxy *, व्योम (**)(व्योम), व्योम *))
SDL_WAYLAND_SYM(व्योम, wl_proxy_set_user_तथ्य, (काष्ठा wl_proxy *, व्योम *))
SDL_WAYLAND_SYM(व्योम *, wl_proxy_get_user_तथ्य, (काष्ठा wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_version, (काष्ठा wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_id, (काष्ठा wl_proxy *))
SDL_WAYLAND_SYM(स्थिर अक्षर *, wl_proxy_get_class, (काष्ठा wl_proxy *))
SDL_WAYLAND_SYM(व्योम, wl_proxy_set_queue, (काष्ठा wl_proxy *, काष्ठा wl_event_queue *))
SDL_WAYLAND_SYM(व्योम *, wl_proxy_create_wrapper, (व्योम *))
SDL_WAYLAND_SYM(व्योम, wl_proxy_wrapper_destroy, (व्योम *))
SDL_WAYLAND_SYM(काष्ठा wl_display *, wl_display_connect, (स्थिर अक्षर *))
SDL_WAYLAND_SYM(काष्ठा wl_display *, wl_display_connect_to_fd, (पूर्णांक))
SDL_WAYLAND_SYM(व्योम, wl_display_disconnect, (काष्ठा wl_display *))
SDL_WAYLAND_SYM(पूर्णांक, wl_display_get_fd, (काष्ठा wl_display *))
SDL_WAYLAND_SYM(पूर्णांक, wl_display_dispatch, (काष्ठा wl_display *))
SDL_WAYLAND_SYM(पूर्णांक, wl_display_dispatch_queue, (काष्ठा wl_display *, काष्ठा wl_event_queue *))
SDL_WAYLAND_SYM(पूर्णांक, wl_display_dispatch_queue_pending, (काष्ठा wl_display *, काष्ठा wl_event_queue *))
SDL_WAYLAND_SYM(पूर्णांक, wl_display_dispatch_pending, (काष्ठा wl_display *))
SDL_WAYLAND_SYM(पूर्णांक, wl_display_prepare_read, (काष्ठा wl_display *))
SDL_WAYLAND_SYM(पूर्णांक, wl_display_prepare_read_queue, (काष्ठा wl_display *, काष्ठा wl_event_queue *))
SDL_WAYLAND_SYM(पूर्णांक, wl_display_read_events, (काष्ठा wl_display *))
SDL_WAYLAND_SYM(व्योम, wl_display_cancel_read, (काष्ठा wl_display *))
SDL_WAYLAND_SYM(पूर्णांक, wl_display_get_error, (काष्ठा wl_display *))
SDL_WAYLAND_SYM(पूर्णांक, wl_display_flush, (काष्ठा wl_display *))
SDL_WAYLAND_SYM(पूर्णांक, wl_display_roundtrip, (काष्ठा wl_display *))
SDL_WAYLAND_SYM(काष्ठा wl_event_queue *, wl_display_create_queue, (काष्ठा wl_display *))
SDL_WAYLAND_SYM(व्योम, wl_event_queue_destroy, (काष्ठा wl_event_queue *))
SDL_WAYLAND_SYM(व्योम, wl_log_set_handler_client, (wl_log_func_t))
SDL_WAYLAND_SYM(व्योम, wl_list_init, (काष्ठा wl_list *))
SDL_WAYLAND_SYM(व्योम, wl_list_जोड़ो, (काष्ठा wl_list *, काष्ठा wl_list *) )
SDL_WAYLAND_SYM(व्योम, wl_list_remove, (काष्ठा wl_list *))
SDL_WAYLAND_SYM(पूर्णांक, wl_list_लंबाई, (स्थिर काष्ठा wl_list *))
SDL_WAYLAND_SYM(पूर्णांक, wl_list_empty, (स्थिर काष्ठा wl_list *))
SDL_WAYLAND_SYM(व्योम, wl_list_जोड़ो_list, (काष्ठा wl_list *, काष्ठा wl_list *))
SDL_WAYLAND_SYM(व्योम, wl_array_init, (काष्ठा wl_array *))
SDL_WAYLAND_SYM(व्योम, wl_array_release, (काष्ठा wl_array *))
SDL_WAYLAND_SYM(व्योम *, wl_array_add, (काष्ठा wl_array *, माप_प्रकार))
SDL_WAYLAND_SYM(पूर्णांक, wl_array_copy, (काष्ठा wl_array *, काष्ठा wl_array *))
SDL_WAYLAND_SYM(काष्ठा wl_proxy *, wl_proxy_marshal_constructor, (काष्ठा wl_proxy *, uint32_t opcode, स्थिर काष्ठा wl_interface *interface, ...))
SDL_WAYLAND_SYM(काष्ठा wl_proxy *, wl_proxy_marshal_constructor_versioned, (काष्ठा wl_proxy *proxy, uint32_t opcode, स्थिर काष्ठा wl_interface *interface, uint32_t version, ...))
SDL_WAYLAND_SYM(व्योम, wl_proxy_set_tag, (काष्ठा wl_proxy *, स्थिर अक्षर * स्थिर *))
SDL_WAYLAND_SYM(स्थिर अक्षर * स्थिर *, wl_proxy_get_tag, (काष्ठा wl_proxy *))

#अगर SDL_WAYLAND_CHECK_VERSION(1, 20, 0)
/* wayland-scanner 1.20 generates code that will call these, so these are
 * non-optional when we are compiling against Wayland 1.20. We don't
 * explicitly call them ourselves, though, so if we are only compiling
 * against Wayland 1.18, they're unnecessary. */
SDL_WAYLAND_SYM(काष्ठा wl_proxy *, wl_proxy_marshal_flags, (काष्ठा wl_proxy *proxy, uint32_t opcode, स्थिर काष्ठा wl_interface *interface, uint32_t version, uint32_t flags, ...))
SDL_WAYLAND_SYM(काष्ठा wl_proxy *, wl_proxy_marshal_array_flags, (काष्ठा wl_proxy *proxy, uint32_t opcode, स्थिर काष्ठा wl_interface *interface, uint32_t version,  uint32_t flags, जोड़ wl_argument *args))
#पूर्ण_अगर

#अगर SDL_WAYLAND_CHECK_VERSION(1, 23, 0) || defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC)
SDL_WAYLAND_SYM_OPT(काष्ठा wl_event_queue *, wl_display_create_queue_with_name, (काष्ठा wl_display *display, स्थिर अक्षर *name))
#पूर्ण_अगर

#अगर 0 // TODO RECONNECT: See waylandvideo.c for more information!
#अगर SDL_WAYLAND_CHECK_VERSION(broken, on, purpose)
SDL_WAYLAND_SYM(पूर्णांक, wl_display_reconnect, (काष्ठा wl_display *))
#पूर्ण_अगर
#पूर्ण_अगर // 0

SDL_WAYLAND_MODULE(WAYLAND_EGL)
SDL_WAYLAND_SYM(काष्ठा wl_egl_window *, wl_egl_window_create, (काष्ठा wl_surface *, पूर्णांक, पूर्णांक))
SDL_WAYLAND_SYM(व्योम, wl_egl_window_destroy, (काष्ठा wl_egl_window *))
SDL_WAYLAND_SYM(व्योम, wl_egl_window_resize, (काष्ठा wl_egl_window *, पूर्णांक, पूर्णांक, पूर्णांक, पूर्णांक))
SDL_WAYLAND_SYM(व्योम, wl_egl_window_get_attached_आकार, (काष्ठा wl_egl_window *, पूर्णांक *, पूर्णांक *))

SDL_WAYLAND_MODULE(WAYLAND_CURSOR)
SDL_WAYLAND_SYM(काष्ठा wl_cursor_theme *, wl_cursor_theme_load, (स्थिर अक्षर *, पूर्णांक , काष्ठा wl_shm *))
SDL_WAYLAND_SYM(व्योम, wl_cursor_theme_destroy, (काष्ठा wl_cursor_theme *))
SDL_WAYLAND_SYM(काष्ठा wl_cursor *, wl_cursor_theme_get_cursor, (काष्ठा wl_cursor_theme *, स्थिर अक्षर *))
SDL_WAYLAND_SYM(काष्ठा wl_बफर *, wl_cursor_image_get_बफर, (काष्ठा wl_cursor_image *))
SDL_WAYLAND_SYM(पूर्णांक, wl_cursor_frame, (काष्ठा wl_cursor *, uint32_t))

SDL_WAYLAND_MODULE(WAYLAND_XKB)
SDL_WAYLAND_SYM(पूर्णांक, xkb_state_कुंजी_get_syms, (काष्ठा xkb_state *, xkb_keycode_t, स्थिर xkb_keysym_t **))
SDL_WAYLAND_SYM(पूर्णांक, xkb_keysym_to_utf8, (xkb_keysym_t, अक्षर *, माप_प्रकार) )
SDL_WAYLAND_SYM(काष्ठा xkb_keymap *, xkb_keymap_new_from_string, (काष्ठा xkb_context *, स्थिर अक्षर *, क्रमागत xkb_keymap_format, क्रमागत xkb_keymap_compile_flags))
SDL_WAYLAND_SYM(काष्ठा xkb_state *, xkb_state_new, (काष्ठा xkb_keymap *) )
SDL_WAYLAND_SYM(पूर्णांक, xkb_keymap_कुंजी_repeats, (काष्ठा xkb_keymap *keymap, xkb_keycode_t कुंजी) )
SDL_WAYLAND_SYM(व्योम, xkb_keymap_unref, (काष्ठा xkb_keymap *) )
SDL_WAYLAND_SYM(व्योम, xkb_state_unref, (काष्ठा xkb_state *) )
SDL_WAYLAND_SYM(व्योम, xkb_context_unref, (काष्ठा xkb_context *) )
SDL_WAYLAND_SYM(काष्ठा xkb_context *, xkb_context_new, (क्रमागत xkb_context_flags flags) )
SDL_WAYLAND_SYM(क्रमागत xkb_state_component, xkb_state_update_mask, (काष्ठा xkb_state *state,\
                      xkb_mod_mask_t depressed_mods,\
                      xkb_mod_mask_t latched_mods,\
                      xkb_mod_mask_t locked_mods,\
                      xkb_layout_सूचकांक_t depressed_layout,\
                      xkb_layout_सूचकांक_t latched_layout,\
                      xkb_layout_सूचकांक_t locked_layout) )
SDL_WAYLAND_SYM(काष्ठा xkb_compose_table *, xkb_compose_table_new_from_locale, (काष्ठा xkb_context *,\
                      स्थिर अक्षर *locale, क्रमागत xkb_compose_compile_flags) )
SDL_WAYLAND_SYM(व्योम, xkb_compose_state_reset, (काष्ठा xkb_compose_state *) )
SDL_WAYLAND_SYM(व्योम, xkb_compose_table_unref, (काष्ठा xkb_compose_table *) )
SDL_WAYLAND_SYM(काष्ठा xkb_compose_state *, xkb_compose_state_new, (काष्ठा xkb_compose_table *, क्रमागत xkb_compose_state_flags) )
SDL_WAYLAND_SYM(व्योम, xkb_compose_state_unref, (काष्ठा xkb_compose_state *) )
SDL_WAYLAND_SYM(क्रमागत xkb_compose_feed_परिणाम, xkb_compose_state_feed, (काष्ठा xkb_compose_state *, xkb_keysym_t) )
SDL_WAYLAND_SYM(क्रमागत xkb_compose_status, xkb_compose_state_get_status, (काष्ठा xkb_compose_state *) )
SDL_WAYLAND_SYM(xkb_keysym_t, xkb_compose_state_get_one_sym, (काष्ठा xkb_compose_state *) )
SDL_WAYLAND_SYM(व्योम, xkb_keymap_कुंजी_for_each, (काष्ठा xkb_keymap *, xkb_keymap_कुंजी_iter_t, व्योम *) )
SDL_WAYLAND_SYM(xkb_layout_सूचकांक_t, xkb_keymap_अंक_layouts, (काष्ठा xkb_keymap *) )
SDL_WAYLAND_SYM(पूर्णांक, xkb_keymap_कुंजी_get_syms_by_level, (काष्ठा xkb_keymap *, xkb_keycode_t, xkb_layout_सूचकांक_t, xkb_level_सूचकांक_t, स्थिर xkb_keysym_t **) )
SDL_WAYLAND_SYM(xkb_level_सूचकांक_t, xkb_keymap_अंक_levels_for_कुंजी, (काष्ठा xkb_keymap *, xkb_keycode_t, xkb_layout_सूचकांक_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keysym_to_utf32, (xkb_keysym_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keymap_mod_get_सूचकांक, (काष्ठा xkb_keymap *, स्थिर अक्षर *) )
SDL_WAYLAND_SYM(स्थिर अक्षर *, xkb_keymap_layout_get_name, (काष्ठा xkb_keymap *, xkb_layout_सूचकांक_t))

#अगर SDL_XKBCOMMON_CHECK_VERSION(1, 0, 0)
SDL_WAYLAND_SYM(माप_प्रकार, xkb_keymap_कुंजी_get_mods_for_level, (काष्ठा xkb_keymap *, xkb_keycode_t, xkb_layout_सूचकांक_t, xkb_level_सूचकांक_t, xkb_mod_mask_t *, माप_प्रकार) )
#अन्यथा
// Only needed in the fallback replacement for xkb_keymap_key_get_mods_for_level().
SDL_WAYLAND_SYM(xkb_level_सूचकांक_t, xkb_state_कुंजी_get_level, (काष्ठा xkb_state *, xkb_keycode_t, xkb_layout_सूचकांक_t) )
#पूर्ण_अगर

#अगर SDL_XKBCOMMON_CHECK_VERSION(1, 10, 0)
SDL_WAYLAND_SYM(xkb_mod_mask_t, xkb_keymap_mod_get_mask, (काष्ठा xkb_keymap *, स्थिर अक्षर *))
#पूर्ण_अगर

#अगर_घोषित HAVE_LIBDECOR_H
SDL_WAYLAND_MODULE(WAYLAND_LIBDECOR)

#अगर defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_VERSION(0, 3, 0)
#घोषणा SDL_libdecor_constsince03 स्थिर
#अन्यथा
#घोषणा SDL_libdecor_constsince03 /* nothing */
#पूर्ण_अगर

SDL_WAYLAND_SYM(व्योम, libdecor_unref, (काष्ठा libdecor *))
SDL_WAYLAND_SYM(काष्ठा libdecor *, libdecor_new, (काष्ठा wl_display *,\
                                                  SDL_libdecor_constsince03 काष्ठा libdecor_interface *))
SDL_WAYLAND_SYM(काष्ठा libdecor_frame *, libdecor_decorate, (काष्ठा libdecor *,\
                                                             काष्ठा wl_surface *,\
                                                             SDL_libdecor_constsince03 काष्ठा libdecor_frame_interface *,\
                                                             व्योम *))
SDL_WAYLAND_SYM(व्योम, libdecor_frame_unref, (काष्ठा libdecor_frame *))
SDL_WAYLAND_SYM(व्योम, libdecor_frame_set_title, (काष्ठा libdecor_frame *, स्थिर अक्षर *))
SDL_WAYLAND_SYM(व्योम, libdecor_frame_set_app_id, (काष्ठा libdecor_frame *, स्थिर अक्षर *))
SDL_WAYLAND_SYM(व्योम, libdecor_frame_set_max_content_आकार, (काष्ठा libdecor_frame *frame,\
                                                            पूर्णांक content_width,\
                                                            पूर्णांक content_height))
SDL_WAYLAND_SYM(व्योम, libdecor_frame_set_min_content_आकार, (काष्ठा libdecor_frame *frame,\
                                                            पूर्णांक content_width,\
                                                            पूर्णांक content_height))
SDL_WAYLAND_SYM(व्योम, libdecor_frame_resize, (काष्ठा libdecor_frame *,\
                                              काष्ठा wl_seat *,\
                                              uint32_t,\
                                              क्रमागत libdecor_resize_edge))
SDL_WAYLAND_SYM(व्योम, libdecor_frame_move, (काष्ठा libdecor_frame *,\
                                            काष्ठा wl_seat *,\
                                            uint32_t))
SDL_WAYLAND_SYM(व्योम, libdecor_frame_commit, (काष्ठा libdecor_frame *,\
                                              काष्ठा libdecor_state *,\
                                              काष्ठा libdecor_configuration *))
SDL_WAYLAND_SYM(व्योम, libdecor_frame_set_minimized, (काष्ठा libdecor_frame *))
SDL_WAYLAND_SYM(व्योम, libdecor_frame_set_maximized, (काष्ठा libdecor_frame *))
SDL_WAYLAND_SYM(व्योम, libdecor_frame_unset_maximized, (काष्ठा libdecor_frame *))
SDL_WAYLAND_SYM(व्योम, libdecor_frame_set_fullscreen, (काष्ठा libdecor_frame *, काष्ठा wl_output *))
SDL_WAYLAND_SYM(व्योम, libdecor_frame_unset_fullscreen, (काष्ठा libdecor_frame *))
SDL_WAYLAND_SYM(व्योम, libdecor_frame_set_capabilities, (काष्ठा libdecor_frame *, \
                                                        क्रमागत libdecor_capabilities))
SDL_WAYLAND_SYM(व्योम, libdecor_frame_unset_capabilities, (काष्ठा libdecor_frame *, \
                                                          क्रमागत libdecor_capabilities))
SDL_WAYLAND_SYM(bool, libdecor_frame_has_capability, (काष्ठा libdecor_frame *, \
                                                      क्रमागत libdecor_capabilities))
SDL_WAYLAND_SYM(व्योम, libdecor_frame_set_visibility, (काष्ठा libdecor_frame *, bool))
SDL_WAYLAND_SYM(bool, libdecor_frame_is_visible, (काष्ठा libdecor_frame *))
SDL_WAYLAND_SYM(bool, libdecor_frame_is_floating, (काष्ठा libdecor_frame *))
SDL_WAYLAND_SYM(व्योम, libdecor_frame_set_parent, (काष्ठा libdecor_frame *,\
                                                  काष्ठा libdecor_frame *))
SDL_WAYLAND_SYM(व्योम, libdecor_frame_show_window_menu, (काष्ठा libdecor_frame *, काष्ठा wl_seat *, uint32_t, पूर्णांक, पूर्णांक))
SDL_WAYLAND_SYM(काष्ठा xdg_surface *, libdecor_frame_get_xdg_surface, (काष्ठा libdecor_frame *))
SDL_WAYLAND_SYM(काष्ठा xdg_toplevel *, libdecor_frame_get_xdg_toplevel, (काष्ठा libdecor_frame *))
SDL_WAYLAND_SYM(व्योम, libdecor_frame_translate_coordinate, (काष्ठा libdecor_frame *, पूर्णांक, पूर्णांक, पूर्णांक *, पूर्णांक *))
SDL_WAYLAND_SYM(व्योम, libdecor_frame_map, (काष्ठा libdecor_frame *))
SDL_WAYLAND_SYM(काष्ठा libdecor_state *, libdecor_state_new, (पूर्णांक, पूर्णांक))
SDL_WAYLAND_SYM(व्योम, libdecor_state_free, (काष्ठा libdecor_state *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_content_आकार, (काष्ठा libdecor_configuration *,\
                                                                काष्ठा libdecor_frame *,\
                                                                पूर्णांक *,\
                                                                पूर्णांक *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_window_state, (काष्ठा libdecor_configuration *,\
                                                                क्रमागत libdecor_window_state *))
SDL_WAYLAND_SYM(पूर्णांक, libdecor_dispatch, (काष्ठा libdecor *, पूर्णांक))

#अगर defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_VERSION(0, 2, 0)
// Only found in libdecor 0.1.1 or higher, so failure to load them is not fatal.
SDL_WAYLAND_SYM_OPT(व्योम, libdecor_frame_get_min_content_आकार, (स्थिर काष्ठा libdecor_frame *,\
                                                            पूर्णांक *,\
                                                            पूर्णांक *))
SDL_WAYLAND_SYM_OPT(व्योम, libdecor_frame_get_max_content_आकार, (स्थिर काष्ठा libdecor_frame *,\
                                                            पूर्णांक *,\
                                                            पूर्णांक *))
#पूर्ण_अगर

#अगर defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_VERSION(0, 3, 0)
SDL_WAYLAND_SYM_OPT(क्रमागत libdecor_wm_capabilities, libdecor_frame_get_wm_capabilities, (काष्ठा libdecor_frame *))
#पूर्ण_अगर

#अघोषित SDL_libdecor_constsince03

#पूर्ण_अगर

#अघोषित SDL_WAYLAND_MODULE
#अघोषित SDL_WAYLAND_SYM
#अघोषित SDL_WAYLAND_SYM_OPT

/* *INDENT-ON* */ // clang-format on
