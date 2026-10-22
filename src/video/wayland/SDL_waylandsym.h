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

#यदि_अपरिभाषितम् SDL_WAYLAND_MODULE
#परिभाषय SDL_WAYLAND_MODULE(modname)
#यदि_अन्तः

#यदि_अपरिभाषितम् SDL_WAYLAND_SYM
#परिभाषय SDL_WAYLAND_SYM(rc,fn,params)
#यदि_अन्तः

#यदि_अपरिभाषितम् SDL_WAYLAND_SYM_OPT
#परिभाषय SDL_WAYLAND_SYM_OPT(rc,fn,params)
#यदि_अन्तः

SDL_WAYLAND_MODULE(WAYLAND_CLIENT)
SDL_WAYLAND_SYM(शून्य, wl_proxy_marshal, (संरचना wl_proxy *, uint32_t, ...))
SDL_WAYLAND_SYM(संरचना wl_proxy *, wl_proxy_create, (संरचना wl_proxy *, ध्रुव संरचना wl_interface *))
SDL_WAYLAND_SYM(शून्य, wl_proxy_destroy, (संरचना wl_proxy *))
SDL_WAYLAND_SYM(पूर्णाङ्क, wl_proxy_सङ्कलय_listener, (संरचना wl_proxy *, शून्य (**)(शून्य), शून्य *))
SDL_WAYLAND_SYM(शून्य, wl_proxy_समुच्चयः_user_दत्त, (संरचना wl_proxy *, शून्य *))
SDL_WAYLAND_SYM(शून्य *, wl_proxy_get_user_दत्त, (संरचना wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_संस्करणम्, (संरचना wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_id, (संरचना wl_proxy *))
SDL_WAYLAND_SYM(ध्रुव वर्ण *, wl_proxy_get_class, (संरचना wl_proxy *))
SDL_WAYLAND_SYM(शून्य, wl_proxy_समुच्चयः_queue, (संरचना wl_proxy *, संरचना wl_event_queue *))
SDL_WAYLAND_SYM(शून्य *, wl_proxy_create_wrapper, (शून्य *))
SDL_WAYLAND_SYM(शून्य, wl_proxy_wrapper_destroy, (शून्य *))
SDL_WAYLAND_SYM(संरचना wl_display *, wl_display_connect, (ध्रुव वर्ण *))
SDL_WAYLAND_SYM(संरचना wl_display *, wl_display_connect_गन्तव्यम्_fd, (पूर्णाङ्क))
SDL_WAYLAND_SYM(शून्य, wl_display_disconnect, (संरचना wl_display *))
SDL_WAYLAND_SYM(पूर्णाङ्क, wl_display_get_fd, (संरचना wl_display *))
SDL_WAYLAND_SYM(पूर्णाङ्क, wl_display_dispatch, (संरचना wl_display *))
SDL_WAYLAND_SYM(पूर्णाङ्क, wl_display_dispatch_queue, (संरचना wl_display *, संरचना wl_event_queue *))
SDL_WAYLAND_SYM(पूर्णाङ्क, wl_display_dispatch_queue_pending, (संरचना wl_display *, संरचना wl_event_queue *))
SDL_WAYLAND_SYM(पूर्णाङ्क, wl_display_dispatch_pending, (संरचना wl_display *))
SDL_WAYLAND_SYM(पूर्णाङ्क, wl_display_prepare_read, (संरचना wl_display *))
SDL_WAYLAND_SYM(पूर्णाङ्क, wl_display_prepare_read_queue, (संरचना wl_display *, संरचना wl_event_queue *))
SDL_WAYLAND_SYM(पूर्णाङ्क, wl_display_read_events, (संरचना wl_display *))
SDL_WAYLAND_SYM(शून्य, wl_display_cancel_read, (संरचना wl_display *))
SDL_WAYLAND_SYM(पूर्णाङ्क, wl_display_get_error, (संरचना wl_display *))
SDL_WAYLAND_SYM(पूर्णाङ्क, wl_display_flush, (संरचना wl_display *))
SDL_WAYLAND_SYM(पूर्णाङ्क, wl_display_roundtrip, (संरचना wl_display *))
SDL_WAYLAND_SYM(संरचना wl_event_queue *, wl_display_create_queue, (संरचना wl_display *))
SDL_WAYLAND_SYM(शून्य, wl_event_queue_destroy, (संरचना wl_event_queue *))
SDL_WAYLAND_SYM(शून्य, wl_log_समुच्चयः_handler_client, (wl_log_func_t))
SDL_WAYLAND_SYM(शून्य, wl_list_init, (संरचना wl_list *))
SDL_WAYLAND_SYM(शून्य, wl_list_निवेशय, (संरचना wl_list *, संरचना wl_list *) )
SDL_WAYLAND_SYM(शून्य, wl_list_remove, (संरचना wl_list *))
SDL_WAYLAND_SYM(पूर्णाङ्क, wl_list_दीर्घता, (ध्रुव संरचना wl_list *))
SDL_WAYLAND_SYM(पूर्णाङ्क, wl_list_रिक्तानि, (ध्रुव संरचना wl_list *))
SDL_WAYLAND_SYM(शून्य, wl_list_निवेशय_list, (संरचना wl_list *, संरचना wl_list *))
SDL_WAYLAND_SYM(शून्य, wl_array_init, (संरचना wl_array *))
SDL_WAYLAND_SYM(शून्य, wl_array_release, (संरचना wl_array *))
SDL_WAYLAND_SYM(शून्य *, wl_array_सङ्कलय, (संरचना wl_array *, size_t))
SDL_WAYLAND_SYM(पूर्णाङ्क, wl_array_copy, (संरचना wl_array *, संरचना wl_array *))
SDL_WAYLAND_SYM(संरचना wl_proxy *, wl_proxy_marshal_constructor, (संरचना wl_proxy *, uint32_t opcode, ध्रुव संरचना wl_interface *interface, ...))
SDL_WAYLAND_SYM(संरचना wl_proxy *, wl_proxy_marshal_constructor_versioned, (संरचना wl_proxy *proxy, uint32_t opcode, ध्रुव संरचना wl_interface *interface, uint32_t संस्करणम्, ...))
SDL_WAYLAND_SYM(शून्य, wl_proxy_समुच्चयः_चिह्नकम्, (संरचना wl_proxy *, ध्रुव वर्ण * ध्रुव *))
SDL_WAYLAND_SYM(ध्रुव वर्ण * ध्रुव *, wl_proxy_get_चिह्नकम्, (संरचना wl_proxy *))

#यदि SDL_WAYLAND_CHECK_संस्करणम्(1, 20, 0)
/* wayland-scanner 1.20 generates code that will call these, so these are
 * non-optional when we are compiling against Wayland 1.20. We don't
 * explicitly call them ourselves, though, so if we are only compiling
 * against Wayland 1.18, they're unnecessary. */
SDL_WAYLAND_SYM(संरचना wl_proxy *, wl_proxy_marshal_flags, (संरचना wl_proxy *proxy, uint32_t opcode, ध्रुव संरचना wl_interface *interface, uint32_t संस्करणम्, uint32_t flags, ...))
SDL_WAYLAND_SYM(संरचना wl_proxy *, wl_proxy_marshal_array_flags, (संरचना wl_proxy *proxy, uint32_t opcode, ध्रुव संरचना wl_interface *interface, uint32_t संस्करणम्,  uint32_t flags, सङ्घ wl_तर्कः *तर्काः))
#यदि_अन्तः

#यदि SDL_WAYLAND_CHECK_संस्करणम्(1, 23, 0) || defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC)
SDL_WAYLAND_SYM_OPT(संरचना wl_event_queue *, wl_display_create_queue_with_name, (संरचना wl_display *display, ध्रुव वर्ण *name))
#यदि_अन्तः

#यदि 0 // TODO RECONNECT: See waylandvideo.c for more information!
#यदि SDL_WAYLAND_CHECK_संस्करणम्(broken, on, purpose)
SDL_WAYLAND_SYM(पूर्णाङ्क, wl_display_reconnect, (संरचना wl_display *))
#यदि_अन्तः
#यदि_अन्तः // 0

SDL_WAYLAND_MODULE(WAYLAND_EGL)
SDL_WAYLAND_SYM(संरचना wl_egl_गवाक्षः *, wl_egl_गवाक्षः_create, (संरचना wl_surface *, पूर्णाङ्क, पूर्णाङ्क))
SDL_WAYLAND_SYM(शून्य, wl_egl_गवाक्षः_destroy, (संरचना wl_egl_गवाक्षः *))
SDL_WAYLAND_SYM(शून्य, wl_egl_गवाक्षः_resize, (संरचना wl_egl_गवाक्षः *, पूर्णाङ्क, पूर्णाङ्क, पूर्णाङ्क, पूर्णाङ्क))
SDL_WAYLAND_SYM(शून्य, wl_egl_गवाक्षः_get_attached_आकार, (संरचना wl_egl_गवाक्षः *, पूर्णाङ्क *, पूर्णाङ्क *))

SDL_WAYLAND_MODULE(WAYLAND_CURSOR)
SDL_WAYLAND_SYM(संरचना wl_cursor_theme *, wl_cursor_theme_आरोपय, (ध्रुव वर्ण *, पूर्णाङ्क , संरचना wl_shm *))
SDL_WAYLAND_SYM(शून्य, wl_cursor_theme_destroy, (संरचना wl_cursor_theme *))
SDL_WAYLAND_SYM(संरचना wl_cursor *, wl_cursor_theme_get_cursor, (संरचना wl_cursor_theme *, ध्रुव वर्ण *))
SDL_WAYLAND_SYM(संरचना wl_बफर *, wl_cursor_image_get_बफर, (संरचना wl_cursor_image *))
SDL_WAYLAND_SYM(पूर्णाङ्क, wl_cursor_frame, (संरचना wl_cursor *, uint32_t))

SDL_WAYLAND_MODULE(WAYLAND_XKB)
SDL_WAYLAND_SYM(पूर्णाङ्क, xkb_state_कुञ्चिका_get_syms, (संरचना xkb_state *, xkb_keycode_t, ध्रुव xkb_keysym_t **))
SDL_WAYLAND_SYM(पूर्णाङ्क, xkb_keysym_गन्तव्यम्_utf8, (xkb_keysym_t, वर्ण *, size_t) )
SDL_WAYLAND_SYM(संरचना xkb_keymap *, xkb_keymap_new_from_string, (संरचना xkb_context *, ध्रुव वर्ण *, गणना xkb_keymap_format, गणना xkb_keymap_compile_flags))
SDL_WAYLAND_SYM(संरचना xkb_state *, xkb_state_new, (संरचना xkb_keymap *) )
SDL_WAYLAND_SYM(पूर्णाङ्क, xkb_keymap_कुञ्चिका_repeats, (संरचना xkb_keymap *keymap, xkb_keycode_t कुञ्चिका) )
SDL_WAYLAND_SYM(शून्य, xkb_keymap_unref, (संरचना xkb_keymap *) )
SDL_WAYLAND_SYM(शून्य, xkb_state_unref, (संरचना xkb_state *) )
SDL_WAYLAND_SYM(शून्य, xkb_context_unref, (संरचना xkb_context *) )
SDL_WAYLAND_SYM(संरचना xkb_context *, xkb_context_new, (गणना xkb_context_flags flags) )
SDL_WAYLAND_SYM(गणना xkb_state_component, xkb_state_update_आवरणम्, (संरचना xkb_state *state,\
                      xkb_mod_आवरणम्_t depressed_mods,\
                      xkb_mod_आवरणम्_t latched_mods,\
                      xkb_mod_आवरणम्_t locked_mods,\
                      xkb_layout_सूचकांक_t depressed_layout,\
                      xkb_layout_सूचकांक_t latched_layout,\
                      xkb_layout_सूचकांक_t locked_layout) )
SDL_WAYLAND_SYM(संरचना xkb_compose_सारणी *, xkb_compose_सारणी_new_from_locale, (संरचना xkb_context *,\
                      ध्रुव वर्ण *locale, गणना xkb_compose_compile_flags) )
SDL_WAYLAND_SYM(शून्य, xkb_compose_state_reset, (संरचना xkb_compose_state *) )
SDL_WAYLAND_SYM(शून्य, xkb_compose_सारणी_unref, (संरचना xkb_compose_सारणी *) )
SDL_WAYLAND_SYM(संरचना xkb_compose_state *, xkb_compose_state_new, (संरचना xkb_compose_सारणी *, गणना xkb_compose_state_flags) )
SDL_WAYLAND_SYM(शून्य, xkb_compose_state_unref, (संरचना xkb_compose_state *) )
SDL_WAYLAND_SYM(गणना xkb_compose_feed_परिणाम, xkb_compose_state_feed, (संरचना xkb_compose_state *, xkb_keysym_t) )
SDL_WAYLAND_SYM(गणना xkb_compose_स्थितिः, xkb_compose_state_get_स्थितिः, (संरचना xkb_compose_state *) )
SDL_WAYLAND_SYM(xkb_keysym_t, xkb_compose_state_get_one_sym, (संरचना xkb_compose_state *) )
SDL_WAYLAND_SYM(शून्य, xkb_keymap_कुञ्चिका_for_each, (संरचना xkb_keymap *, xkb_keymap_कुञ्चिका_iter_t, शून्य *) )
SDL_WAYLAND_SYM(xkb_layout_सूचकांक_t, xkb_keymap_अङ्कः_layouts, (संरचना xkb_keymap *) )
SDL_WAYLAND_SYM(पूर्णाङ्क, xkb_keymap_कुञ्चिका_get_syms_by_level, (संरचना xkb_keymap *, xkb_keycode_t, xkb_layout_सूचकांक_t, xkb_level_सूचकांक_t, ध्रुव xkb_keysym_t **) )
SDL_WAYLAND_SYM(xkb_level_सूचकांक_t, xkb_keymap_अङ्कः_स्तराः_for_कुञ्चिका, (संरचना xkb_keymap *, xkb_keycode_t, xkb_layout_सूचकांक_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keysym_गन्तव्यम्_utf32, (xkb_keysym_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keymap_mod_get_सूचकांक, (संरचना xkb_keymap *, ध्रुव वर्ण *) )
SDL_WAYLAND_SYM(ध्रुव वर्ण *, xkb_keymap_layout_get_name, (संरचना xkb_keymap *, xkb_layout_सूचकांक_t))

#यदि SDL_XKBCOMMON_CHECK_संस्करणम्(1, 0, 0)
SDL_WAYLAND_SYM(size_t, xkb_keymap_कुञ्चिका_get_mods_for_level, (संरचना xkb_keymap *, xkb_keycode_t, xkb_layout_सूचकांक_t, xkb_level_सूचकांक_t, xkb_mod_आवरणम्_t *, size_t) )
#अन्यथा
// Only needed in the fallback replacement for xkb_keymap_key_get_mods_for_level().
SDL_WAYLAND_SYM(xkb_level_सूचकांक_t, xkb_state_कुञ्चिका_get_level, (संरचना xkb_state *, xkb_keycode_t, xkb_layout_सूचकांक_t) )
#यदि_अन्तः

#यदि SDL_XKBCOMMON_CHECK_संस्करणम्(1, 10, 0)
SDL_WAYLAND_SYM(xkb_mod_आवरणम्_t, xkb_keymap_mod_get_आवरणम्, (संरचना xkb_keymap *, ध्रुव वर्ण *))
#यदि_अन्तः

#यदि_परिभाषितम् HAVE_LIBDECOR_H
SDL_WAYLAND_MODULE(WAYLAND_LIBDECOR)

#यदि defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_संस्करणम्(0, 3, 0)
#परिभाषय SDL_libdecor_constsince03 ध्रुव
#अन्यथा
#परिभाषय SDL_libdecor_constsince03 /* nothing */
#यदि_अन्तः

SDL_WAYLAND_SYM(शून्य, libdecor_unref, (संरचना libdecor *))
SDL_WAYLAND_SYM(संरचना libdecor *, libdecor_new, (संरचना wl_display *,\
                                                  SDL_libdecor_constsince03 संरचना libdecor_interface *))
SDL_WAYLAND_SYM(संरचना libdecor_frame *, libdecor_decorate, (संरचना libdecor *,\
                                                             संरचना wl_surface *,\
                                                             SDL_libdecor_constsince03 संरचना libdecor_frame_interface *,\
                                                             शून्य *))
SDL_WAYLAND_SYM(शून्य, libdecor_frame_unref, (संरचना libdecor_frame *))
SDL_WAYLAND_SYM(शून्य, libdecor_frame_समुच्चयः_title, (संरचना libdecor_frame *, ध्रुव वर्ण *))
SDL_WAYLAND_SYM(शून्य, libdecor_frame_समुच्चयः_app_id, (संरचना libdecor_frame *, ध्रुव वर्ण *))
SDL_WAYLAND_SYM(शून्य, libdecor_frame_समुच्चयः_max_content_आकार, (संरचना libdecor_frame *frame,\
                                                            पूर्णाङ्क content_विस्तारः,\
                                                            पूर्णाङ्क content_height))
SDL_WAYLAND_SYM(शून्य, libdecor_frame_समुच्चयः_min_content_आकार, (संरचना libdecor_frame *frame,\
                                                            पूर्णाङ्क content_विस्तारः,\
                                                            पूर्णाङ्क content_height))
SDL_WAYLAND_SYM(शून्य, libdecor_frame_resize, (संरचना libdecor_frame *,\
                                              संरचना wl_seat *,\
                                              uint32_t,\
                                              गणना libdecor_resize_edge))
SDL_WAYLAND_SYM(शून्य, libdecor_frame_move, (संरचना libdecor_frame *,\
                                            संरचना wl_seat *,\
                                            uint32_t))
SDL_WAYLAND_SYM(शून्य, libdecor_frame_commit, (संरचना libdecor_frame *,\
                                              संरचना libdecor_state *,\
                                              संरचना libdecor_configuration *))
SDL_WAYLAND_SYM(शून्य, libdecor_frame_समुच्चयः_minimized, (संरचना libdecor_frame *))
SDL_WAYLAND_SYM(शून्य, libdecor_frame_समुच्चयः_maximized, (संरचना libdecor_frame *))
SDL_WAYLAND_SYM(शून्य, libdecor_frame_unset_maximized, (संरचना libdecor_frame *))
SDL_WAYLAND_SYM(शून्य, libdecor_frame_समुच्चयः_fullscreen, (संरचना libdecor_frame *, संरचना wl_output *))
SDL_WAYLAND_SYM(शून्य, libdecor_frame_unset_fullscreen, (संरचना libdecor_frame *))
SDL_WAYLAND_SYM(शून्य, libdecor_frame_समुच्चयः_capabilities, (संरचना libdecor_frame *, \
                                                        गणना libdecor_capabilities))
SDL_WAYLAND_SYM(शून्य, libdecor_frame_unset_capabilities, (संरचना libdecor_frame *, \
                                                          गणना libdecor_capabilities))
SDL_WAYLAND_SYM(bool, libdecor_frame_has_capability, (संरचना libdecor_frame *, \
                                                      गणना libdecor_capabilities))
SDL_WAYLAND_SYM(शून्य, libdecor_frame_समुच्चयः_visibility, (संरचना libdecor_frame *, bool))
SDL_WAYLAND_SYM(bool, libdecor_frame_is_visible, (संरचना libdecor_frame *))
SDL_WAYLAND_SYM(bool, libdecor_frame_is_floating, (संरचना libdecor_frame *))
SDL_WAYLAND_SYM(शून्य, libdecor_frame_समुच्चयः_parent, (संरचना libdecor_frame *,\
                                                  संरचना libdecor_frame *))
SDL_WAYLAND_SYM(शून्य, libdecor_frame_show_गवाक्षः_menu, (संरचना libdecor_frame *, संरचना wl_seat *, uint32_t, पूर्णाङ्क, पूर्णाङ्क))
SDL_WAYLAND_SYM(संरचना xdg_surface *, libdecor_frame_get_xdg_surface, (संरचना libdecor_frame *))
SDL_WAYLAND_SYM(संरचना xdg_toplevel *, libdecor_frame_get_xdg_toplevel, (संरचना libdecor_frame *))
SDL_WAYLAND_SYM(शून्य, libdecor_frame_translate_coordinate, (संरचना libdecor_frame *, पूर्णाङ्क, पूर्णाङ्क, पूर्णाङ्क *, पूर्णाङ्क *))
SDL_WAYLAND_SYM(शून्य, libdecor_frame_map, (संरचना libdecor_frame *))
SDL_WAYLAND_SYM(संरचना libdecor_state *, libdecor_state_new, (पूर्णाङ्क, पूर्णाङ्क))
SDL_WAYLAND_SYM(शून्य, libdecor_state_free, (संरचना libdecor_state *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_content_आकार, (संरचना libdecor_configuration *,\
                                                                संरचना libdecor_frame *,\
                                                                पूर्णाङ्क *,\
                                                                पूर्णाङ्क *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_गवाक्षः_state, (संरचना libdecor_configuration *,\
                                                                गणना libdecor_गवाक्षः_state *))
SDL_WAYLAND_SYM(पूर्णाङ्क, libdecor_dispatch, (संरचना libdecor *, पूर्णाङ्क))

#यदि defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_संस्करणम्(0, 2, 0)
// Only found in libdecor 0.1.1 or higher, so failure to load them is not fatal.
SDL_WAYLAND_SYM_OPT(शून्य, libdecor_frame_get_min_content_आकार, (ध्रुव संरचना libdecor_frame *,\
                                                            पूर्णाङ्क *,\
                                                            पूर्णाङ्क *))
SDL_WAYLAND_SYM_OPT(शून्य, libdecor_frame_get_max_content_आकार, (ध्रुव संरचना libdecor_frame *,\
                                                            पूर्णाङ्क *,\
                                                            पूर्णाङ्क *))
#यदि_अन्तः

#यदि defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_संस्करणम्(0, 3, 0)
SDL_WAYLAND_SYM_OPT(गणना libdecor_wm_capabilities, libdecor_frame_get_wm_capabilities, (संरचना libdecor_frame *))
#यदि_अन्तः

#अपरिभाषय SDL_libdecor_constsince03

#यदि_अन्तः

#अपरिभाषय SDL_WAYLAND_MODULE
#अपरिभाषय SDL_WAYLAND_SYM
#अपरिभाषय SDL_WAYLAND_SYM_OPT

/* *INDENT-ON* */ // clang-format on
