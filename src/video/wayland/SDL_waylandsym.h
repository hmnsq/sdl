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

#నిర్వచితం_కాకపోతే SDL_WAYLAND_MODULE
#నిర్వచించు SDL_WAYLAND_MODULE(modname)
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే SDL_WAYLAND_SYM
#నిర్వచించు SDL_WAYLAND_SYM(rc,fn,params)
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే SDL_WAYLAND_SYM_OPT
#నిర్వచించు SDL_WAYLAND_SYM_OPT(rc,fn,params)
#అయితే_ముగింపు

SDL_WAYLAND_MODULE(WAYLAND_CLIENT)
SDL_WAYLAND_SYM(శూన్య, wl_proxy_marshal, (నిర్మాణం wl_proxy *, uint32_t, ...))
SDL_WAYLAND_SYM(నిర్మాణం wl_proxy *, wl_proxy_create, (నిర్మాణం wl_proxy *, స్థిరరాశి నిర్మాణం wl_interface *))
SDL_WAYLAND_SYM(శూన్య, wl_proxy_destroy, (నిర్మాణం wl_proxy *))
SDL_WAYLAND_SYM(పూర్ణాంకం, wl_proxy_కూడు_listener, (నిర్మాణం wl_proxy *, శూన్య (**)(శూన్య), శూన్య *))
SDL_WAYLAND_SYM(శూన్య, wl_proxy_సమితి_user_దత్తాంశం, (నిర్మాణం wl_proxy *, శూన్య *))
SDL_WAYLAND_SYM(శూన్య *, wl_proxy_get_user_దత్తాంశం, (నిర్మాణం wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_సంస్కరణ, (నిర్మాణం wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_id, (నిర్మాణం wl_proxy *))
SDL_WAYLAND_SYM(స్థిరరాశి అక్షరం *, wl_proxy_get_class, (నిర్మాణం wl_proxy *))
SDL_WAYLAND_SYM(శూన్య, wl_proxy_సమితి_వరుస, (నిర్మాణం wl_proxy *, నిర్మాణం wl_event_వరుస *))
SDL_WAYLAND_SYM(శూన్య *, wl_proxy_create_wrapper, (శూన్య *))
SDL_WAYLAND_SYM(శూన్య, wl_proxy_wrapper_destroy, (శూన్య *))
SDL_WAYLAND_SYM(నిర్మాణం wl_display *, wl_display_connect, (స్థిరరాశి అక్షరం *))
SDL_WAYLAND_SYM(నిర్మాణం wl_display *, wl_display_connect_గమ్యం_fd, (పూర్ణాంకం))
SDL_WAYLAND_SYM(శూన్య, wl_display_disconnect, (నిర్మాణం wl_display *))
SDL_WAYLAND_SYM(పూర్ణాంకం, wl_display_get_fd, (నిర్మాణం wl_display *))
SDL_WAYLAND_SYM(పూర్ణాంకం, wl_display_dispatch, (నిర్మాణం wl_display *))
SDL_WAYLAND_SYM(పూర్ణాంకం, wl_display_dispatch_వరుస, (నిర్మాణం wl_display *, నిర్మాణం wl_event_వరుస *))
SDL_WAYLAND_SYM(పూర్ణాంకం, wl_display_dispatch_వరుస_pending, (నిర్మాణం wl_display *, నిర్మాణం wl_event_వరుస *))
SDL_WAYLAND_SYM(పూర్ణాంకం, wl_display_dispatch_pending, (నిర్మాణం wl_display *))
SDL_WAYLAND_SYM(పూర్ణాంకం, wl_display_prepare_read, (నిర్మాణం wl_display *))
SDL_WAYLAND_SYM(పూర్ణాంకం, wl_display_prepare_read_వరుస, (నిర్మాణం wl_display *, నిర్మాణం wl_event_వరుస *))
SDL_WAYLAND_SYM(పూర్ణాంకం, wl_display_read_events, (నిర్మాణం wl_display *))
SDL_WAYLAND_SYM(శూన్య, wl_display_cancel_read, (నిర్మాణం wl_display *))
SDL_WAYLAND_SYM(పూర్ణాంకం, wl_display_get_error, (నిర్మాణం wl_display *))
SDL_WAYLAND_SYM(పూర్ణాంకం, wl_display_flush, (నిర్మాణం wl_display *))
SDL_WAYLAND_SYM(పూర్ణాంకం, wl_display_roundtrip, (నిర్మాణం wl_display *))
SDL_WAYLAND_SYM(నిర్మాణం wl_event_వరుస *, wl_display_create_వరుస, (నిర్మాణం wl_display *))
SDL_WAYLAND_SYM(శూన్య, wl_event_వరుస_destroy, (నిర్మాణం wl_event_వరుస *))
SDL_WAYLAND_SYM(శూన్య, wl_log_సమితి_handler_client, (wl_log_func_t))
SDL_WAYLAND_SYM(శూన్య, wl_list_init, (నిర్మాణం wl_list *))
SDL_WAYLAND_SYM(శూన్య, wl_list_చొప్పించు, (నిర్మాణం wl_list *, నిర్మాణం wl_list *) )
SDL_WAYLAND_SYM(శూన్య, wl_list_remove, (నిర్మాణం wl_list *))
SDL_WAYLAND_SYM(పూర్ణాంకం, wl_list_నిడివి, (స్థిరరాశి నిర్మాణం wl_list *))
SDL_WAYLAND_SYM(పూర్ణాంకం, wl_list_ఖాళీలు, (స్థిరరాశి నిర్మాణం wl_list *))
SDL_WAYLAND_SYM(శూన్య, wl_list_చొప్పించు_list, (నిర్మాణం wl_list *, నిర్మాణం wl_list *))
SDL_WAYLAND_SYM(శూన్య, wl_array_init, (నిర్మాణం wl_array *))
SDL_WAYLAND_SYM(శూన్య, wl_array_release, (నిర్మాణం wl_array *))
SDL_WAYLAND_SYM(శూన్య *, wl_array_కూడు, (నిర్మాణం wl_array *, size_t))
SDL_WAYLAND_SYM(పూర్ణాంకం, wl_array_copy, (నిర్మాణం wl_array *, నిర్మాణం wl_array *))
SDL_WAYLAND_SYM(నిర్మాణం wl_proxy *, wl_proxy_marshal_constructor, (నిర్మాణం wl_proxy *, uint32_t opcode, స్థిరరాశి నిర్మాణం wl_interface *interface, ...))
SDL_WAYLAND_SYM(నిర్మాణం wl_proxy *, wl_proxy_marshal_constructor_versioned, (నిర్మాణం wl_proxy *proxy, uint32_t opcode, స్థిరరాశి నిర్మాణం wl_interface *interface, uint32_t సంస్కరణ, ...))
SDL_WAYLAND_SYM(శూన్య, wl_proxy_సమితి_ట్యాగ్, (నిర్మాణం wl_proxy *, స్థిరరాశి అక్షరం * స్థిరరాశి *))
SDL_WAYLAND_SYM(స్థిరరాశి అక్షరం * స్థిరరాశి *, wl_proxy_get_ట్యాగ్, (నిర్మాణం wl_proxy *))

#ఒకవేళ SDL_WAYLAND_CHECK_సంస్కరణ(1, 20, 0)
/* wayland-scanner 1.20 generates code that will call these, so these are
 * non-optional when we are compiling against Wayland 1.20. We don't
 * explicitly call them ourselves, though, so if we are only compiling
 * against Wayland 1.18, they're unnecessary. */
SDL_WAYLAND_SYM(నిర్మాణం wl_proxy *, wl_proxy_marshal_flags, (నిర్మాణం wl_proxy *proxy, uint32_t opcode, స్థిరరాశి నిర్మాణం wl_interface *interface, uint32_t సంస్కరణ, uint32_t flags, ...))
SDL_WAYLAND_SYM(నిర్మాణం wl_proxy *, wl_proxy_marshal_array_flags, (నిర్మాణం wl_proxy *proxy, uint32_t opcode, స్థిరరాశి నిర్మాణం wl_interface *interface, uint32_t సంస్కరణ,  uint32_t flags, సంఘం wl_వాదం *వాదనలు))
#అయితే_ముగింపు

#ఒకవేళ SDL_WAYLAND_CHECK_సంస్కరణ(1, 23, 0) || defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC)
SDL_WAYLAND_SYM_OPT(నిర్మాణం wl_event_వరుస *, wl_display_create_వరుస_with_name, (నిర్మాణం wl_display *display, స్థిరరాశి అక్షరం *name))
#అయితే_ముగింపు

#ఒకవేళ 0 // TODO RECONNECT: See waylandvideo.c for more information!
#ఒకవేళ SDL_WAYLAND_CHECK_సంస్కరణ(broken, on, purpose)
SDL_WAYLAND_SYM(పూర్ణాంకం, wl_display_reconnect, (నిర్మాణం wl_display *))
#అయితే_ముగింపు
#అయితే_ముగింపు // 0

SDL_WAYLAND_MODULE(WAYLAND_EGL)
SDL_WAYLAND_SYM(నిర్మాణం wl_egl_కిటికీ *, wl_egl_కిటికీ_create, (నిర్మాణం wl_surface *, పూర్ణాంకం, పూర్ణాంకం))
SDL_WAYLAND_SYM(శూన్య, wl_egl_కిటికీ_destroy, (నిర్మాణం wl_egl_కిటికీ *))
SDL_WAYLAND_SYM(శూన్య, wl_egl_కిటికీ_resize, (నిర్మాణం wl_egl_కిటికీ *, పూర్ణాంకం, పూర్ణాంకం, పూర్ణాంకం, పూర్ణాంకం))
SDL_WAYLAND_SYM(శూన్య, wl_egl_కిటికీ_get_attached_కొలత, (నిర్మాణం wl_egl_కిటికీ *, పూర్ణాంకం *, పూర్ణాంకం *))

SDL_WAYLAND_MODULE(WAYLAND_CURSOR)
SDL_WAYLAND_SYM(నిర్మాణం wl_cursor_theme *, wl_cursor_theme_ఎక్కించు, (స్థిరరాశి అక్షరం *, పూర్ణాంకం , నిర్మాణం wl_shm *))
SDL_WAYLAND_SYM(శూన్య, wl_cursor_theme_destroy, (నిర్మాణం wl_cursor_theme *))
SDL_WAYLAND_SYM(నిర్మాణం wl_cursor *, wl_cursor_theme_get_cursor, (నిర్మాణం wl_cursor_theme *, స్థిరరాశి అక్షరం *))
SDL_WAYLAND_SYM(నిర్మాణం wl_బఫరు *, wl_cursor_image_get_బఫరు, (నిర్మాణం wl_cursor_image *))
SDL_WAYLAND_SYM(పూర్ణాంకం, wl_cursor_చట్రం, (నిర్మాణం wl_cursor *, uint32_t))

SDL_WAYLAND_MODULE(WAYLAND_XKB)
SDL_WAYLAND_SYM(పూర్ణాంకం, xkb_state_కీలకం_get_syms, (నిర్మాణం xkb_state *, xkb_keycode_t, స్థిరరాశి xkb_keysym_t **))
SDL_WAYLAND_SYM(పూర్ణాంకం, xkb_keysym_గమ్యం_utf8, (xkb_keysym_t, అక్షరం *, size_t) )
SDL_WAYLAND_SYM(నిర్మాణం xkb_keymap *, xkb_keymap_new_from_string, (నిర్మాణం xkb_context *, స్థిరరాశి అక్షరం *, గణన xkb_keymap_format, గణన xkb_keymap_compile_flags))
SDL_WAYLAND_SYM(నిర్మాణం xkb_state *, xkb_state_new, (నిర్మాణం xkb_keymap *) )
SDL_WAYLAND_SYM(పూర్ణాంకం, xkb_keymap_కీలకం_repeats, (నిర్మాణం xkb_keymap *keymap, xkb_keycode_t కీలకం) )
SDL_WAYLAND_SYM(శూన్య, xkb_keymap_unref, (నిర్మాణం xkb_keymap *) )
SDL_WAYLAND_SYM(శూన్య, xkb_state_unref, (నిర్మాణం xkb_state *) )
SDL_WAYLAND_SYM(శూన్య, xkb_context_unref, (నిర్మాణం xkb_context *) )
SDL_WAYLAND_SYM(నిర్మాణం xkb_context *, xkb_context_new, (గణన xkb_context_flags flags) )
SDL_WAYLAND_SYM(గణన xkb_state_component, xkb_state_update_ముసుగు, (నిర్మాణం xkb_state *state,\
                      xkb_mod_ముసుగు_t depressed_mods,\
                      xkb_mod_ముసుగు_t latched_mods,\
                      xkb_mod_ముసుగు_t locked_mods,\
                      xkb_layout_సూచీ_t depressed_layout,\
                      xkb_layout_సూచీ_t latched_layout,\
                      xkb_layout_సూచీ_t locked_layout) )
SDL_WAYLAND_SYM(నిర్మాణం xkb_compose_పట్టిక *, xkb_compose_పట్టిక_new_from_locale, (నిర్మాణం xkb_context *,\
                      స్థిరరాశి అక్షరం *locale, గణన xkb_compose_compile_flags) )
SDL_WAYLAND_SYM(శూన్య, xkb_compose_state_reset, (నిర్మాణం xkb_compose_state *) )
SDL_WAYLAND_SYM(శూన్య, xkb_compose_పట్టిక_unref, (నిర్మాణం xkb_compose_పట్టిక *) )
SDL_WAYLAND_SYM(నిర్మాణం xkb_compose_state *, xkb_compose_state_new, (నిర్మాణం xkb_compose_పట్టిక *, గణన xkb_compose_state_flags) )
SDL_WAYLAND_SYM(శూన్య, xkb_compose_state_unref, (నిర్మాణం xkb_compose_state *) )
SDL_WAYLAND_SYM(గణన xkb_compose_feed_ఫలితం, xkb_compose_state_feed, (నిర్మాణం xkb_compose_state *, xkb_keysym_t) )
SDL_WAYLAND_SYM(గణన xkb_compose_స్థితి, xkb_compose_state_get_స్థితి, (నిర్మాణం xkb_compose_state *) )
SDL_WAYLAND_SYM(xkb_keysym_t, xkb_compose_state_get_one_sym, (నిర్మాణం xkb_compose_state *) )
SDL_WAYLAND_SYM(శూన్య, xkb_keymap_కీలకం_for_each, (నిర్మాణం xkb_keymap *, xkb_keymap_కీలకం_iter_t, శూన్య *) )
SDL_WAYLAND_SYM(xkb_layout_సూచీ_t, xkb_keymap_అంకె_layouts, (నిర్మాణం xkb_keymap *) )
SDL_WAYLAND_SYM(పూర్ణాంకం, xkb_keymap_కీలకం_get_syms_by_level, (నిర్మాణం xkb_keymap *, xkb_keycode_t, xkb_layout_సూచీ_t, xkb_level_సూచీ_t, స్థిరరాశి xkb_keysym_t **) )
SDL_WAYLAND_SYM(xkb_level_సూచీ_t, xkb_keymap_అంకె_స్థాయిలు_for_కీలకం, (నిర్మాణం xkb_keymap *, xkb_keycode_t, xkb_layout_సూచీ_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keysym_గమ్యం_utf32, (xkb_keysym_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keymap_mod_get_సూచీ, (నిర్మాణం xkb_keymap *, స్థిరరాశి అక్షరం *) )
SDL_WAYLAND_SYM(స్థిరరాశి అక్షరం *, xkb_keymap_layout_get_name, (నిర్మాణం xkb_keymap *, xkb_layout_సూచీ_t))

#ఒకవేళ SDL_XKBCOMMON_CHECK_సంస్కరణ(1, 0, 0)
SDL_WAYLAND_SYM(size_t, xkb_keymap_కీలకం_get_mods_for_level, (నిర్మాణం xkb_keymap *, xkb_keycode_t, xkb_layout_సూచీ_t, xkb_level_సూచీ_t, xkb_mod_ముసుగు_t *, size_t) )
#లేకపోతే
// Only needed in the fallback replacement for xkb_keymap_key_get_mods_for_level().
SDL_WAYLAND_SYM(xkb_level_సూచీ_t, xkb_state_కీలకం_get_level, (నిర్మాణం xkb_state *, xkb_keycode_t, xkb_layout_సూచీ_t) )
#అయితే_ముగింపు

#ఒకవేళ SDL_XKBCOMMON_CHECK_సంస్కరణ(1, 10, 0)
SDL_WAYLAND_SYM(xkb_mod_ముసుగు_t, xkb_keymap_mod_get_ముసుగు, (నిర్మాణం xkb_keymap *, స్థిరరాశి అక్షరం *))
#అయితే_ముగింపు

#నిర్వచితమైతే HAVE_LIBDECOR_H
SDL_WAYLAND_MODULE(WAYLAND_LIBDECOR)

#ఒకవేళ defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_సంస్కరణ(0, 3, 0)
#నిర్వచించు SDL_libdecor_constsince03 స్థిరరాశి
#లేకపోతే
#నిర్వచించు SDL_libdecor_constsince03 /* nothing */
#అయితే_ముగింపు

SDL_WAYLAND_SYM(శూన్య, libdecor_unref, (నిర్మాణం libdecor *))
SDL_WAYLAND_SYM(నిర్మాణం libdecor *, libdecor_new, (నిర్మాణం wl_display *,\
                                                  SDL_libdecor_constsince03 నిర్మాణం libdecor_interface *))
SDL_WAYLAND_SYM(నిర్మాణం libdecor_చట్రం *, libdecor_decorate, (నిర్మాణం libdecor *,\
                                                             నిర్మాణం wl_surface *,\
                                                             SDL_libdecor_constsince03 నిర్మాణం libdecor_చట్రం_interface *,\
                                                             శూన్య *))
SDL_WAYLAND_SYM(శూన్య, libdecor_చట్రం_unref, (నిర్మాణం libdecor_చట్రం *))
SDL_WAYLAND_SYM(శూన్య, libdecor_చట్రం_సమితి_title, (నిర్మాణం libdecor_చట్రం *, స్థిరరాశి అక్షరం *))
SDL_WAYLAND_SYM(శూన్య, libdecor_చట్రం_సమితి_app_id, (నిర్మాణం libdecor_చట్రం *, స్థిరరాశి అక్షరం *))
SDL_WAYLAND_SYM(శూన్య, libdecor_చట్రం_సమితి_max_content_కొలత, (నిర్మాణం libdecor_చట్రం *చట్రం,\
                                                            పూర్ణాంకం content_వెడల్పు,\
                                                            పూర్ణాంకం content_ఎత్తు))
SDL_WAYLAND_SYM(శూన్య, libdecor_చట్రం_సమితి_min_content_కొలత, (నిర్మాణం libdecor_చట్రం *చట్రం,\
                                                            పూర్ణాంకం content_వెడల్పు,\
                                                            పూర్ణాంకం content_ఎత్తు))
SDL_WAYLAND_SYM(శూన్య, libdecor_చట్రం_resize, (నిర్మాణం libdecor_చట్రం *,\
                                              నిర్మాణం wl_seat *,\
                                              uint32_t,\
                                              గణన libdecor_resize_అంచు))
SDL_WAYLAND_SYM(శూన్య, libdecor_చట్రం_move, (నిర్మాణం libdecor_చట్రం *,\
                                            నిర్మాణం wl_seat *,\
                                            uint32_t))
SDL_WAYLAND_SYM(శూన్య, libdecor_చట్రం_commit, (నిర్మాణం libdecor_చట్రం *,\
                                              నిర్మాణం libdecor_state *,\
                                              నిర్మాణం libdecor_configuration *))
SDL_WAYLAND_SYM(శూన్య, libdecor_చట్రం_సమితి_minimized, (నిర్మాణం libdecor_చట్రం *))
SDL_WAYLAND_SYM(శూన్య, libdecor_చట్రం_సమితి_maximized, (నిర్మాణం libdecor_చట్రం *))
SDL_WAYLAND_SYM(శూన్య, libdecor_చట్రం_unset_maximized, (నిర్మాణం libdecor_చట్రం *))
SDL_WAYLAND_SYM(శూన్య, libdecor_చట్రం_సమితి_fullscreen, (నిర్మాణం libdecor_చట్రం *, నిర్మాణం wl_output *))
SDL_WAYLAND_SYM(శూన్య, libdecor_చట్రం_unset_fullscreen, (నిర్మాణం libdecor_చట్రం *))
SDL_WAYLAND_SYM(శూన్య, libdecor_చట్రం_సమితి_capabilities, (నిర్మాణం libdecor_చట్రం *, \
                                                        గణన libdecor_capabilities))
SDL_WAYLAND_SYM(శూన్య, libdecor_చట్రం_unset_capabilities, (నిర్మాణం libdecor_చట్రం *, \
                                                          గణన libdecor_capabilities))
SDL_WAYLAND_SYM(bool, libdecor_చట్రం_has_capability, (నిర్మాణం libdecor_చట్రం *, \
                                                      గణన libdecor_capabilities))
SDL_WAYLAND_SYM(శూన్య, libdecor_చట్రం_సమితి_visibility, (నిర్మాణం libdecor_చట్రం *, bool))
SDL_WAYLAND_SYM(bool, libdecor_చట్రం_is_visible, (నిర్మాణం libdecor_చట్రం *))
SDL_WAYLAND_SYM(bool, libdecor_చట్రం_is_floating, (నిర్మాణం libdecor_చట్రం *))
SDL_WAYLAND_SYM(శూన్య, libdecor_చట్రం_సమితి_మాతృ, (నిర్మాణం libdecor_చట్రం *,\
                                                  నిర్మాణం libdecor_చట్రం *))
SDL_WAYLAND_SYM(శూన్య, libdecor_చట్రం_show_కిటికీ_menu, (నిర్మాణం libdecor_చట్రం *, నిర్మాణం wl_seat *, uint32_t, పూర్ణాంకం, పూర్ణాంకం))
SDL_WAYLAND_SYM(నిర్మాణం xdg_surface *, libdecor_చట్రం_get_xdg_surface, (నిర్మాణం libdecor_చట్రం *))
SDL_WAYLAND_SYM(నిర్మాణం xdg_toplevel *, libdecor_చట్రం_get_xdg_toplevel, (నిర్మాణం libdecor_చట్రం *))
SDL_WAYLAND_SYM(శూన్య, libdecor_చట్రం_translate_coordinate, (నిర్మాణం libdecor_చట్రం *, పూర్ణాంకం, పూర్ణాంకం, పూర్ణాంకం *, పూర్ణాంకం *))
SDL_WAYLAND_SYM(శూన్య, libdecor_చట్రం_map, (నిర్మాణం libdecor_చట్రం *))
SDL_WAYLAND_SYM(నిర్మాణం libdecor_state *, libdecor_state_new, (పూర్ణాంకం, పూర్ణాంకం))
SDL_WAYLAND_SYM(శూన్య, libdecor_state_free, (నిర్మాణం libdecor_state *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_content_కొలత, (నిర్మాణం libdecor_configuration *,\
                                                                నిర్మాణం libdecor_చట్రం *,\
                                                                పూర్ణాంకం *,\
                                                                పూర్ణాంకం *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_కిటికీ_state, (నిర్మాణం libdecor_configuration *,\
                                                                గణన libdecor_కిటికీ_state *))
SDL_WAYLAND_SYM(పూర్ణాంకం, libdecor_dispatch, (నిర్మాణం libdecor *, పూర్ణాంకం))

#ఒకవేళ defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_సంస్కరణ(0, 2, 0)
// Only found in libdecor 0.1.1 or higher, so failure to load them is not fatal.
SDL_WAYLAND_SYM_OPT(శూన్య, libdecor_చట్రం_get_min_content_కొలత, (స్థిరరాశి నిర్మాణం libdecor_చట్రం *,\
                                                            పూర్ణాంకం *,\
                                                            పూర్ణాంకం *))
SDL_WAYLAND_SYM_OPT(శూన్య, libdecor_చట్రం_get_max_content_కొలత, (స్థిరరాశి నిర్మాణం libdecor_చట్రం *,\
                                                            పూర్ణాంకం *,\
                                                            పూర్ణాంకం *))
#అయితే_ముగింపు

#ఒకవేళ defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_సంస్కరణ(0, 3, 0)
SDL_WAYLAND_SYM_OPT(గణన libdecor_wm_capabilities, libdecor_చట్రం_get_wm_capabilities, (నిర్మాణం libdecor_చట్రం *))
#అయితే_ముగింపు

#నిర్వచనం_రద్దు SDL_libdecor_constsince03

#అయితే_ముగింపు

#నిర్వచనం_రద్దు SDL_WAYLAND_MODULE
#నిర్వచనం_రద్దు SDL_WAYLAND_SYM
#నిర్వచనం_రద్దు SDL_WAYLAND_SYM_OPT

/* *INDENT-ON* */ // clang-format on
