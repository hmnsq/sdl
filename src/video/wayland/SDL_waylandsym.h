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

#که_نه_تعریف_شوی SDL_WAYLAND_MODULE
#تعریف_کړه SDL_WAYLAND_MODULE(modname)
#د_که_پای

#که_نه_تعریف_شوی SDL_WAYLAND_SYM
#تعریف_کړه SDL_WAYLAND_SYM(rc,fn,params)
#د_که_پای

#که_نه_تعریف_شوی SDL_WAYLAND_SYM_OPT
#تعریف_کړه SDL_WAYLAND_SYM_OPT(rc,fn,params)
#د_که_پای

SDL_WAYLAND_MODULE(WAYLAND_CLIENT)
SDL_WAYLAND_SYM(فراغ, wl_proxy_marshal, (بنية wl_proxy *, uint32_t, ...))
SDL_WAYLAND_SYM(بنية wl_proxy *, wl_proxy_create, (بنية wl_proxy *, ثابت بنية wl_interface *))
SDL_WAYLAND_SYM(فراغ, wl_proxy_destroy, (بنية wl_proxy *))
SDL_WAYLAND_SYM(صحيح, wl_proxy_جمع_کړه_listener, (بنية wl_proxy *, فراغ (**)(فراغ), فراغ *))
SDL_WAYLAND_SYM(فراغ, wl_proxy_سېټ_user_معلومات, (بنية wl_proxy *, فراغ *))
SDL_WAYLAND_SYM(فراغ *, wl_proxy_get_user_معلومات, (بنية wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_نسخه, (بنية wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_id, (بنية wl_proxy *))
SDL_WAYLAND_SYM(ثابت حرف *, wl_proxy_get_class, (بنية wl_proxy *))
SDL_WAYLAND_SYM(فراغ, wl_proxy_سېټ_کتار, (بنية wl_proxy *, بنية wl_event_کتار *))
SDL_WAYLAND_SYM(فراغ *, wl_proxy_create_wrapper, (فراغ *))
SDL_WAYLAND_SYM(فراغ, wl_proxy_wrapper_destroy, (فراغ *))
SDL_WAYLAND_SYM(بنية wl_display *, wl_display_connect, (ثابت حرف *))
SDL_WAYLAND_SYM(بنية wl_display *, wl_display_connect_منزل_fd, (صحيح))
SDL_WAYLAND_SYM(فراغ, wl_display_disconnect, (بنية wl_display *))
SDL_WAYLAND_SYM(صحيح, wl_display_get_fd, (بنية wl_display *))
SDL_WAYLAND_SYM(صحيح, wl_display_dispatch, (بنية wl_display *))
SDL_WAYLAND_SYM(صحيح, wl_display_dispatch_کتار, (بنية wl_display *, بنية wl_event_کتار *))
SDL_WAYLAND_SYM(صحيح, wl_display_dispatch_کتار_pending, (بنية wl_display *, بنية wl_event_کتار *))
SDL_WAYLAND_SYM(صحيح, wl_display_dispatch_pending, (بنية wl_display *))
SDL_WAYLAND_SYM(صحيح, wl_display_prepare_read, (بنية wl_display *))
SDL_WAYLAND_SYM(صحيح, wl_display_prepare_read_کتار, (بنية wl_display *, بنية wl_event_کتار *))
SDL_WAYLAND_SYM(صحيح, wl_display_read_events, (بنية wl_display *))
SDL_WAYLAND_SYM(فراغ, wl_display_cancel_read, (بنية wl_display *))
SDL_WAYLAND_SYM(صحيح, wl_display_get_error, (بنية wl_display *))
SDL_WAYLAND_SYM(صحيح, wl_display_flush, (بنية wl_display *))
SDL_WAYLAND_SYM(صحيح, wl_display_roundtrip, (بنية wl_display *))
SDL_WAYLAND_SYM(بنية wl_event_کتار *, wl_display_create_کتار, (بنية wl_display *))
SDL_WAYLAND_SYM(فراغ, wl_event_کتار_destroy, (بنية wl_event_کتار *))
SDL_WAYLAND_SYM(فراغ, wl_log_سېټ_handler_client, (wl_log_func_t))
SDL_WAYLAND_SYM(فراغ, wl_list_init, (بنية wl_list *))
SDL_WAYLAND_SYM(فراغ, wl_list_ورننباسه, (بنية wl_list *, بنية wl_list *) )
SDL_WAYLAND_SYM(فراغ, wl_list_remove, (بنية wl_list *))
SDL_WAYLAND_SYM(صحيح, wl_list_اوږدتیا, (ثابت بنية wl_list *))
SDL_WAYLAND_SYM(صحيح, wl_list_تشه, (ثابت بنية wl_list *))
SDL_WAYLAND_SYM(فراغ, wl_list_ورننباسه_list, (بنية wl_list *, بنية wl_list *))
SDL_WAYLAND_SYM(فراغ, wl_array_init, (بنية wl_array *))
SDL_WAYLAND_SYM(فراغ, wl_array_release, (بنية wl_array *))
SDL_WAYLAND_SYM(فراغ *, wl_array_جمع_کړه, (بنية wl_array *, size_t))
SDL_WAYLAND_SYM(صحيح, wl_array_copy, (بنية wl_array *, بنية wl_array *))
SDL_WAYLAND_SYM(بنية wl_proxy *, wl_proxy_marshal_constructor, (بنية wl_proxy *, uint32_t opcode, ثابت بنية wl_interface *interface, ...))
SDL_WAYLAND_SYM(بنية wl_proxy *, wl_proxy_marshal_constructor_versioned, (بنية wl_proxy *proxy, uint32_t opcode, ثابت بنية wl_interface *interface, uint32_t نسخه, ...))
SDL_WAYLAND_SYM(فراغ, wl_proxy_سېټ_نښان, (بنية wl_proxy *, ثابت حرف * ثابت *))
SDL_WAYLAND_SYM(ثابت حرف * ثابت *, wl_proxy_get_نښان, (بنية wl_proxy *))

#إذا SDL_WAYLAND_CHECK_نسخه(1, 20, 0)
/* wayland-scanner 1.20 generates code that will call these, so these are
 * non-optional when we are compiling against Wayland 1.20. We don't
 * explicitly call them ourselves, though, so if we are only compiling
 * against Wayland 1.18, they're unnecessary. */
SDL_WAYLAND_SYM(بنية wl_proxy *, wl_proxy_marshal_flags, (بنية wl_proxy *proxy, uint32_t opcode, ثابت بنية wl_interface *interface, uint32_t نسخه, uint32_t flags, ...))
SDL_WAYLAND_SYM(بنية wl_proxy *, wl_proxy_marshal_array_flags, (بنية wl_proxy *proxy, uint32_t opcode, ثابت بنية wl_interface *interface, uint32_t نسخه,  uint32_t flags, اتحاد wl_دلیل *دلیلونه))
#د_که_پای

#إذا SDL_WAYLAND_CHECK_نسخه(1, 23, 0) || defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC)
SDL_WAYLAND_SYM_OPT(بنية wl_event_کتار *, wl_display_create_کتار_with_name, (بنية wl_display *display, ثابت حرف *name))
#د_که_پای

#إذا 0 // TODO RECONNECT: See waylandvideo.c for more information!
#إذا SDL_WAYLAND_CHECK_نسخه(broken, on, purpose)
SDL_WAYLAND_SYM(صحيح, wl_display_reconnect, (بنية wl_display *))
#د_که_پای
#د_که_پای // 0

SDL_WAYLAND_MODULE(WAYLAND_EGL)
SDL_WAYLAND_SYM(بنية wl_egl_کړکۍ *, wl_egl_کړکۍ_create, (بنية wl_surface *, صحيح, صحيح))
SDL_WAYLAND_SYM(فراغ, wl_egl_کړکۍ_destroy, (بنية wl_egl_کړکۍ *))
SDL_WAYLAND_SYM(فراغ, wl_egl_کړکۍ_resize, (بنية wl_egl_کړکۍ *, صحيح, صحيح, صحيح, صحيح))
SDL_WAYLAND_SYM(فراغ, wl_egl_کړکۍ_get_attached_اندازه, (بنية wl_egl_کړکۍ *, صحيح *, صحيح *))

SDL_WAYLAND_MODULE(WAYLAND_CURSOR)
SDL_WAYLAND_SYM(بنية wl_cursor_theme *, wl_cursor_theme_بارول, (ثابت حرف *, صحيح , بنية wl_shm *))
SDL_WAYLAND_SYM(فراغ, wl_cursor_theme_destroy, (بنية wl_cursor_theme *))
SDL_WAYLAND_SYM(بنية wl_cursor *, wl_cursor_theme_get_cursor, (بنية wl_cursor_theme *, ثابت حرف *))
SDL_WAYLAND_SYM(بنية wl_بفر *, wl_cursor_image_get_بفر, (بنية wl_cursor_image *))
SDL_WAYLAND_SYM(صحيح, wl_cursor_چوکاټ, (بنية wl_cursor *, uint32_t))

SDL_WAYLAND_MODULE(WAYLAND_XKB)
SDL_WAYLAND_SYM(صحيح, xkb_state_کلی_get_syms, (بنية xkb_state *, xkb_keycode_t, ثابت xkb_keysym_t **))
SDL_WAYLAND_SYM(صحيح, xkb_keysym_منزل_utf8, (xkb_keysym_t, حرف *, size_t) )
SDL_WAYLAND_SYM(بنية xkb_keymap *, xkb_keymap_new_from_string, (بنية xkb_context *, ثابت حرف *, تعداد xkb_keymap_format, تعداد xkb_keymap_compile_flags))
SDL_WAYLAND_SYM(بنية xkb_state *, xkb_state_new, (بنية xkb_keymap *) )
SDL_WAYLAND_SYM(صحيح, xkb_keymap_کلی_repeats, (بنية xkb_keymap *keymap, xkb_keycode_t کلی) )
SDL_WAYLAND_SYM(فراغ, xkb_keymap_unref, (بنية xkb_keymap *) )
SDL_WAYLAND_SYM(فراغ, xkb_state_unref, (بنية xkb_state *) )
SDL_WAYLAND_SYM(فراغ, xkb_context_unref, (بنية xkb_context *) )
SDL_WAYLAND_SYM(بنية xkb_context *, xkb_context_new, (تعداد xkb_context_flags flags) )
SDL_WAYLAND_SYM(تعداد xkb_state_component, xkb_state_update_ماسک, (بنية xkb_state *state,\
                      xkb_mod_ماسک_t depressed_mods,\
                      xkb_mod_ماسک_t latched_mods,\
                      xkb_mod_ماسک_t locked_mods,\
                      xkb_layout_شاخص_t depressed_layout,\
                      xkb_layout_شاخص_t latched_layout,\
                      xkb_layout_شاخص_t locked_layout) )
SDL_WAYLAND_SYM(بنية xkb_compose_جدول *, xkb_compose_جدول_new_from_locale, (بنية xkb_context *,\
                      ثابت حرف *locale, تعداد xkb_compose_compile_flags) )
SDL_WAYLAND_SYM(فراغ, xkb_compose_state_reset, (بنية xkb_compose_state *) )
SDL_WAYLAND_SYM(فراغ, xkb_compose_جدول_unref, (بنية xkb_compose_جدول *) )
SDL_WAYLAND_SYM(بنية xkb_compose_state *, xkb_compose_state_new, (بنية xkb_compose_جدول *, تعداد xkb_compose_state_flags) )
SDL_WAYLAND_SYM(فراغ, xkb_compose_state_unref, (بنية xkb_compose_state *) )
SDL_WAYLAND_SYM(تعداد xkb_compose_feed_پایله, xkb_compose_state_feed, (بنية xkb_compose_state *, xkb_keysym_t) )
SDL_WAYLAND_SYM(تعداد xkb_compose_حالت, xkb_compose_state_get_حالت, (بنية xkb_compose_state *) )
SDL_WAYLAND_SYM(xkb_keysym_t, xkb_compose_state_get_one_sym, (بنية xkb_compose_state *) )
SDL_WAYLAND_SYM(فراغ, xkb_keymap_کلی_for_each, (بنية xkb_keymap *, xkb_keymap_کلی_iter_t, فراغ *) )
SDL_WAYLAND_SYM(xkb_layout_شاخص_t, xkb_keymap_عدد_layouts, (بنية xkb_keymap *) )
SDL_WAYLAND_SYM(صحيح, xkb_keymap_کلی_get_syms_by_level, (بنية xkb_keymap *, xkb_keycode_t, xkb_layout_شاخص_t, xkb_level_شاخص_t, ثابت xkb_keysym_t **) )
SDL_WAYLAND_SYM(xkb_level_شاخص_t, xkb_keymap_عدد_پوړونه_for_کلی, (بنية xkb_keymap *, xkb_keycode_t, xkb_layout_شاخص_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keysym_منزل_utf32, (xkb_keysym_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keymap_mod_get_شاخص, (بنية xkb_keymap *, ثابت حرف *) )
SDL_WAYLAND_SYM(ثابت حرف *, xkb_keymap_layout_get_name, (بنية xkb_keymap *, xkb_layout_شاخص_t))

#إذا SDL_XKBCOMMON_CHECK_نسخه(1, 0, 0)
SDL_WAYLAND_SYM(size_t, xkb_keymap_کلی_get_mods_for_level, (بنية xkb_keymap *, xkb_keycode_t, xkb_layout_شاخص_t, xkb_level_شاخص_t, xkb_mod_ماسک_t *, size_t) )
#وإلا
// Only needed in the fallback replacement for xkb_keymap_key_get_mods_for_level().
SDL_WAYLAND_SYM(xkb_level_شاخص_t, xkb_state_کلی_get_level, (بنية xkb_state *, xkb_keycode_t, xkb_layout_شاخص_t) )
#د_که_پای

#إذا SDL_XKBCOMMON_CHECK_نسخه(1, 10, 0)
SDL_WAYLAND_SYM(xkb_mod_ماسک_t, xkb_keymap_mod_get_ماسک, (بنية xkb_keymap *, ثابت حرف *))
#د_که_پای

#که_تعریف_شوی HAVE_LIBDECOR_H
SDL_WAYLAND_MODULE(WAYLAND_LIBDECOR)

#إذا defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_نسخه(0, 3, 0)
#تعریف_کړه SDL_libdecor_constsince03 ثابت
#وإلا
#تعریف_کړه SDL_libdecor_constsince03 /* nothing */
#د_که_پای

SDL_WAYLAND_SYM(فراغ, libdecor_unref, (بنية libdecor *))
SDL_WAYLAND_SYM(بنية libdecor *, libdecor_new, (بنية wl_display *,\
                                                  SDL_libdecor_constsince03 بنية libdecor_interface *))
SDL_WAYLAND_SYM(بنية libdecor_چوکاټ *, libdecor_decorate, (بنية libdecor *,\
                                                             بنية wl_surface *,\
                                                             SDL_libdecor_constsince03 بنية libdecor_چوکاټ_interface *,\
                                                             فراغ *))
SDL_WAYLAND_SYM(فراغ, libdecor_چوکاټ_unref, (بنية libdecor_چوکاټ *))
SDL_WAYLAND_SYM(فراغ, libdecor_چوکاټ_سېټ_title, (بنية libdecor_چوکاټ *, ثابت حرف *))
SDL_WAYLAND_SYM(فراغ, libdecor_چوکاټ_سېټ_app_id, (بنية libdecor_چوکاټ *, ثابت حرف *))
SDL_WAYLAND_SYM(فراغ, libdecor_چوکاټ_سېټ_max_content_اندازه, (بنية libdecor_چوکاټ *چوکاټ,\
                                                            صحيح content_پلنوالی,\
                                                            صحيح content_لوړوالی))
SDL_WAYLAND_SYM(فراغ, libdecor_چوکاټ_سېټ_min_content_اندازه, (بنية libdecor_چوکاټ *چوکاټ,\
                                                            صحيح content_پلنوالی,\
                                                            صحيح content_لوړوالی))
SDL_WAYLAND_SYM(فراغ, libdecor_چوکاټ_resize, (بنية libdecor_چوکاټ *,\
                                              بنية wl_seat *,\
                                              uint32_t,\
                                              تعداد libdecor_resize_څنډه))
SDL_WAYLAND_SYM(فراغ, libdecor_چوکاټ_move, (بنية libdecor_چوکاټ *,\
                                            بنية wl_seat *,\
                                            uint32_t))
SDL_WAYLAND_SYM(فراغ, libdecor_چوکاټ_commit, (بنية libdecor_چوکاټ *,\
                                              بنية libdecor_state *,\
                                              بنية libdecor_configuration *))
SDL_WAYLAND_SYM(فراغ, libdecor_چوکاټ_سېټ_minimized, (بنية libdecor_چوکاټ *))
SDL_WAYLAND_SYM(فراغ, libdecor_چوکاټ_سېټ_maximized, (بنية libdecor_چوکاټ *))
SDL_WAYLAND_SYM(فراغ, libdecor_چوکاټ_unset_maximized, (بنية libdecor_چوکاټ *))
SDL_WAYLAND_SYM(فراغ, libdecor_چوکاټ_سېټ_fullscreen, (بنية libdecor_چوکاټ *, بنية wl_output *))
SDL_WAYLAND_SYM(فراغ, libdecor_چوکاټ_unset_fullscreen, (بنية libdecor_چوکاټ *))
SDL_WAYLAND_SYM(فراغ, libdecor_چوکاټ_سېټ_capabilities, (بنية libdecor_چوکاټ *, \
                                                        تعداد libdecor_capabilities))
SDL_WAYLAND_SYM(فراغ, libdecor_چوکاټ_unset_capabilities, (بنية libdecor_چوکاټ *, \
                                                          تعداد libdecor_capabilities))
SDL_WAYLAND_SYM(bool, libdecor_چوکاټ_has_capability, (بنية libdecor_چوکاټ *, \
                                                      تعداد libdecor_capabilities))
SDL_WAYLAND_SYM(فراغ, libdecor_چوکاټ_سېټ_visibility, (بنية libdecor_چوکاټ *, bool))
SDL_WAYLAND_SYM(bool, libdecor_چوکاټ_is_visible, (بنية libdecor_چوکاټ *))
SDL_WAYLAND_SYM(bool, libdecor_چوکاټ_is_floating, (بنية libdecor_چوکاټ *))
SDL_WAYLAND_SYM(فراغ, libdecor_چوکاټ_سېټ_پلار, (بنية libdecor_چوکاټ *,\
                                                  بنية libdecor_چوکاټ *))
SDL_WAYLAND_SYM(فراغ, libdecor_چوکاټ_show_کړکۍ_menu, (بنية libdecor_چوکاټ *, بنية wl_seat *, uint32_t, صحيح, صحيح))
SDL_WAYLAND_SYM(بنية xdg_surface *, libdecor_چوکاټ_get_xdg_surface, (بنية libdecor_چوکاټ *))
SDL_WAYLAND_SYM(بنية xdg_toplevel *, libdecor_چوکاټ_get_xdg_toplevel, (بنية libdecor_چوکاټ *))
SDL_WAYLAND_SYM(فراغ, libdecor_چوکاټ_translate_coordinate, (بنية libdecor_چوکاټ *, صحيح, صحيح, صحيح *, صحيح *))
SDL_WAYLAND_SYM(فراغ, libdecor_چوکاټ_map, (بنية libdecor_چوکاټ *))
SDL_WAYLAND_SYM(بنية libdecor_state *, libdecor_state_new, (صحيح, صحيح))
SDL_WAYLAND_SYM(فراغ, libdecor_state_free, (بنية libdecor_state *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_content_اندازه, (بنية libdecor_configuration *,\
                                                                بنية libdecor_چوکاټ *,\
                                                                صحيح *,\
                                                                صحيح *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_کړکۍ_state, (بنية libdecor_configuration *,\
                                                                تعداد libdecor_کړکۍ_state *))
SDL_WAYLAND_SYM(صحيح, libdecor_dispatch, (بنية libdecor *, صحيح))

#إذا defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_نسخه(0, 2, 0)
// Only found in libdecor 0.1.1 or higher, so failure to load them is not fatal.
SDL_WAYLAND_SYM_OPT(فراغ, libdecor_چوکاټ_get_min_content_اندازه, (ثابت بنية libdecor_چوکاټ *,\
                                                            صحيح *,\
                                                            صحيح *))
SDL_WAYLAND_SYM_OPT(فراغ, libdecor_چوکاټ_get_max_content_اندازه, (ثابت بنية libdecor_چوکاټ *,\
                                                            صحيح *,\
                                                            صحيح *))
#د_که_پای

#إذا defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_نسخه(0, 3, 0)
SDL_WAYLAND_SYM_OPT(تعداد libdecor_wm_capabilities, libdecor_چوکاټ_get_wm_capabilities, (بنية libdecor_چوکاټ *))
#د_که_پای

#تعریف_لغوه SDL_libdecor_constsince03

#د_که_پای

#تعریف_لغوه SDL_WAYLAND_MODULE
#تعریف_لغوه SDL_WAYLAND_SYM
#تعریف_لغوه SDL_WAYLAND_SYM_OPT

/* *INDENT-ON* */ // clang-format on
