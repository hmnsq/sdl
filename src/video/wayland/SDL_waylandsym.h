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

#اگر_غیر_تعریف_شدہ SDL_WAYLAND_MODULE
#تعریف_کرو SDL_WAYLAND_MODULE(modname)
#اگر_ختم

#اگر_غیر_تعریف_شدہ SDL_WAYLAND_SYM
#تعریف_کرو SDL_WAYLAND_SYM(rc,fn,params)
#اگر_ختم

#اگر_غیر_تعریف_شدہ SDL_WAYLAND_SYM_OPT
#تعریف_کرو SDL_WAYLAND_SYM_OPT(rc,fn,params)
#اگر_ختم

SDL_WAYLAND_MODULE(WAYLAND_CLIENT)
SDL_WAYLAND_SYM(خالی, wl_proxy_marshal, (ساخت wl_proxy *, uint32_t, ...))
SDL_WAYLAND_SYM(ساخت wl_proxy *, wl_proxy_create, (ساخت wl_proxy *, ثابت ساخت wl_interface *))
SDL_WAYLAND_SYM(خالی, wl_proxy_destroy, (ساخت wl_proxy *))
SDL_WAYLAND_SYM(صحیح, wl_proxy_جوڑو_listener, (ساخت wl_proxy *, خالی (**)(خالی), خالی *))
SDL_WAYLAND_SYM(خالی, wl_proxy_سیٹ_user_ڈیٹا, (ساخت wl_proxy *, خالی *))
SDL_WAYLAND_SYM(خالی *, wl_proxy_get_user_ڈیٹا, (ساخت wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_نسخہ, (ساخت wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_id, (ساخت wl_proxy *))
SDL_WAYLAND_SYM(ثابت حرف *, wl_proxy_get_class, (ساخت wl_proxy *))
SDL_WAYLAND_SYM(خالی, wl_proxy_سیٹ_قطار, (ساخت wl_proxy *, ساخت wl_event_قطار *))
SDL_WAYLAND_SYM(خالی *, wl_proxy_create_wrapper, (خالی *))
SDL_WAYLAND_SYM(خالی, wl_proxy_wrapper_destroy, (خالی *))
SDL_WAYLAND_SYM(ساخت wl_display *, wl_display_connect, (ثابت حرف *))
SDL_WAYLAND_SYM(ساخت wl_display *, wl_display_connect_مقصد_fd, (صحیح))
SDL_WAYLAND_SYM(خالی, wl_display_disconnect, (ساخت wl_display *))
SDL_WAYLAND_SYM(صحیح, wl_display_get_fd, (ساخت wl_display *))
SDL_WAYLAND_SYM(صحیح, wl_display_dispatch, (ساخت wl_display *))
SDL_WAYLAND_SYM(صحیح, wl_display_dispatch_قطار, (ساخت wl_display *, ساخت wl_event_قطار *))
SDL_WAYLAND_SYM(صحیح, wl_display_dispatch_قطار_pending, (ساخت wl_display *, ساخت wl_event_قطار *))
SDL_WAYLAND_SYM(صحیح, wl_display_dispatch_pending, (ساخت wl_display *))
SDL_WAYLAND_SYM(صحیح, wl_display_prepare_read, (ساخت wl_display *))
SDL_WAYLAND_SYM(صحیح, wl_display_prepare_read_قطار, (ساخت wl_display *, ساخت wl_event_قطار *))
SDL_WAYLAND_SYM(صحیح, wl_display_read_events, (ساخت wl_display *))
SDL_WAYLAND_SYM(خالی, wl_display_cancel_read, (ساخت wl_display *))
SDL_WAYLAND_SYM(صحیح, wl_display_get_error, (ساخت wl_display *))
SDL_WAYLAND_SYM(صحیح, wl_display_flush, (ساخت wl_display *))
SDL_WAYLAND_SYM(صحیح, wl_display_roundtrip, (ساخت wl_display *))
SDL_WAYLAND_SYM(ساخت wl_event_قطار *, wl_display_create_قطار, (ساخت wl_display *))
SDL_WAYLAND_SYM(خالی, wl_event_قطار_destroy, (ساخت wl_event_قطار *))
SDL_WAYLAND_SYM(خالی, wl_log_سیٹ_handler_client, (wl_log_func_t))
SDL_WAYLAND_SYM(خالی, wl_list_init, (ساخت wl_list *))
SDL_WAYLAND_SYM(خالی, wl_list_داخل_کرو, (ساخت wl_list *, ساخت wl_list *) )
SDL_WAYLAND_SYM(خالی, wl_list_remove, (ساخت wl_list *))
SDL_WAYLAND_SYM(صحیح, wl_list_لمبائی, (ثابت ساخت wl_list *))
SDL_WAYLAND_SYM(صحیح, wl_list_خالی_خانے, (ثابت ساخت wl_list *))
SDL_WAYLAND_SYM(خالی, wl_list_داخل_کرو_list, (ساخت wl_list *, ساخت wl_list *))
SDL_WAYLAND_SYM(خالی, wl_array_init, (ساخت wl_array *))
SDL_WAYLAND_SYM(خالی, wl_array_release, (ساخت wl_array *))
SDL_WAYLAND_SYM(خالی *, wl_array_جوڑو, (ساخت wl_array *, size_t))
SDL_WAYLAND_SYM(صحیح, wl_array_copy, (ساخت wl_array *, ساخت wl_array *))
SDL_WAYLAND_SYM(ساخت wl_proxy *, wl_proxy_marshal_constructor, (ساخت wl_proxy *, uint32_t opcode, ثابت ساخت wl_interface *interface, ...))
SDL_WAYLAND_SYM(ساخت wl_proxy *, wl_proxy_marshal_constructor_versioned, (ساخت wl_proxy *proxy, uint32_t opcode, ثابت ساخت wl_interface *interface, uint32_t نسخہ, ...))
SDL_WAYLAND_SYM(خالی, wl_proxy_سیٹ_لیبل, (ساخت wl_proxy *, ثابت حرف * ثابت *))
SDL_WAYLAND_SYM(ثابت حرف * ثابت *, wl_proxy_get_لیبل, (ساخت wl_proxy *))

#اگر SDL_WAYLAND_CHECK_نسخہ(1, 20, 0)
/* wayland-scanner 1.20 generates code that will call these, so these are
 * non-optional when we are compiling against Wayland 1.20. We don't
 * explicitly call them ourselves, though, so if we are only compiling
 * against Wayland 1.18, they're unnecessary. */
SDL_WAYLAND_SYM(ساخت wl_proxy *, wl_proxy_marshal_flags, (ساخت wl_proxy *proxy, uint32_t opcode, ثابت ساخت wl_interface *interface, uint32_t نسخہ, uint32_t flags, ...))
SDL_WAYLAND_SYM(ساخت wl_proxy *, wl_proxy_marshal_array_flags, (ساخت wl_proxy *proxy, uint32_t opcode, ثابت ساخت wl_interface *interface, uint32_t نسخہ,  uint32_t flags, اتحاد wl_دلیل *دلائل))
#اگر_ختم

#اگر SDL_WAYLAND_CHECK_نسخہ(1, 23, 0) || defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC)
SDL_WAYLAND_SYM_OPT(ساخت wl_event_قطار *, wl_display_create_قطار_with_name, (ساخت wl_display *display, ثابت حرف *name))
#اگر_ختم

#اگر 0 // TODO RECONNECT: See waylandvideo.c for more information!
#اگر SDL_WAYLAND_CHECK_نسخہ(broken, on, purpose)
SDL_WAYLAND_SYM(صحیح, wl_display_reconnect, (ساخت wl_display *))
#اگر_ختم
#اگر_ختم // 0

SDL_WAYLAND_MODULE(WAYLAND_EGL)
SDL_WAYLAND_SYM(ساخت wl_egl_کھڑکی *, wl_egl_کھڑکی_create, (ساخت wl_surface *, صحیح, صحیح))
SDL_WAYLAND_SYM(خالی, wl_egl_کھڑکی_destroy, (ساخت wl_egl_کھڑکی *))
SDL_WAYLAND_SYM(خالی, wl_egl_کھڑکی_resize, (ساخت wl_egl_کھڑکی *, صحیح, صحیح, صحیح, صحیح))
SDL_WAYLAND_SYM(خالی, wl_egl_کھڑکی_get_attached_سائز, (ساخت wl_egl_کھڑکی *, صحیح *, صحیح *))

SDL_WAYLAND_MODULE(WAYLAND_CURSOR)
SDL_WAYLAND_SYM(ساخت wl_cursor_theme *, wl_cursor_theme_بھرو, (ثابت حرف *, صحیح , ساخت wl_shm *))
SDL_WAYLAND_SYM(خالی, wl_cursor_theme_destroy, (ساخت wl_cursor_theme *))
SDL_WAYLAND_SYM(ساخت wl_cursor *, wl_cursor_theme_get_cursor, (ساخت wl_cursor_theme *, ثابت حرف *))
SDL_WAYLAND_SYM(ساخت wl_بفر *, wl_cursor_image_get_بفر, (ساخت wl_cursor_image *))
SDL_WAYLAND_SYM(صحیح, wl_cursor_چوکھٹا, (ساخت wl_cursor *, uint32_t))

SDL_WAYLAND_MODULE(WAYLAND_XKB)
SDL_WAYLAND_SYM(صحیح, xkb_state_کلید_get_syms, (ساخت xkb_state *, xkb_keycode_t, ثابت xkb_keysym_t **))
SDL_WAYLAND_SYM(صحیح, xkb_keysym_مقصد_utf8, (xkb_keysym_t, حرف *, size_t) )
SDL_WAYLAND_SYM(ساخت xkb_keymap *, xkb_keymap_new_from_string, (ساخت xkb_context *, ثابت حرف *, شمار xkb_keymap_format, شمار xkb_keymap_compile_flags))
SDL_WAYLAND_SYM(ساخت xkb_state *, xkb_state_new, (ساخت xkb_keymap *) )
SDL_WAYLAND_SYM(صحیح, xkb_keymap_کلید_repeats, (ساخت xkb_keymap *keymap, xkb_keycode_t کلید) )
SDL_WAYLAND_SYM(خالی, xkb_keymap_unref, (ساخت xkb_keymap *) )
SDL_WAYLAND_SYM(خالی, xkb_state_unref, (ساخت xkb_state *) )
SDL_WAYLAND_SYM(خالی, xkb_context_unref, (ساخت xkb_context *) )
SDL_WAYLAND_SYM(ساخت xkb_context *, xkb_context_new, (شمار xkb_context_flags flags) )
SDL_WAYLAND_SYM(شمار xkb_state_component, xkb_state_update_نقاب, (ساخت xkb_state *state,\
                      xkb_mod_نقاب_t depressed_mods,\
                      xkb_mod_نقاب_t latched_mods,\
                      xkb_mod_نقاب_t locked_mods,\
                      xkb_layout_اشاریہ_t depressed_layout,\
                      xkb_layout_اشاریہ_t latched_layout,\
                      xkb_layout_اشاریہ_t locked_layout) )
SDL_WAYLAND_SYM(ساخت xkb_compose_جدول *, xkb_compose_جدول_new_from_locale, (ساخت xkb_context *,\
                      ثابت حرف *locale, شمار xkb_compose_compile_flags) )
SDL_WAYLAND_SYM(خالی, xkb_compose_state_reset, (ساخت xkb_compose_state *) )
SDL_WAYLAND_SYM(خالی, xkb_compose_جدول_unref, (ساخت xkb_compose_جدول *) )
SDL_WAYLAND_SYM(ساخت xkb_compose_state *, xkb_compose_state_new, (ساخت xkb_compose_جدول *, شمار xkb_compose_state_flags) )
SDL_WAYLAND_SYM(خالی, xkb_compose_state_unref, (ساخت xkb_compose_state *) )
SDL_WAYLAND_SYM(شمار xkb_compose_feed_نتیجہ, xkb_compose_state_feed, (ساخت xkb_compose_state *, xkb_keysym_t) )
SDL_WAYLAND_SYM(شمار xkb_compose_حالت, xkb_compose_state_get_حالت, (ساخت xkb_compose_state *) )
SDL_WAYLAND_SYM(xkb_keysym_t, xkb_compose_state_get_one_sym, (ساخت xkb_compose_state *) )
SDL_WAYLAND_SYM(خالی, xkb_keymap_کلید_for_each, (ساخت xkb_keymap *, xkb_keymap_کلید_iter_t, خالی *) )
SDL_WAYLAND_SYM(xkb_layout_اشاریہ_t, xkb_keymap_عدد_layouts, (ساخت xkb_keymap *) )
SDL_WAYLAND_SYM(صحیح, xkb_keymap_کلید_get_syms_by_level, (ساخت xkb_keymap *, xkb_keycode_t, xkb_layout_اشاریہ_t, xkb_level_اشاریہ_t, ثابت xkb_keysym_t **) )
SDL_WAYLAND_SYM(xkb_level_اشاریہ_t, xkb_keymap_عدد_سطحیں_for_کلید, (ساخت xkb_keymap *, xkb_keycode_t, xkb_layout_اشاریہ_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keysym_مقصد_utf32, (xkb_keysym_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keymap_mod_get_اشاریہ, (ساخت xkb_keymap *, ثابت حرف *) )
SDL_WAYLAND_SYM(ثابت حرف *, xkb_keymap_layout_get_name, (ساخت xkb_keymap *, xkb_layout_اشاریہ_t))

#اگر SDL_XKBCOMMON_CHECK_نسخہ(1, 0, 0)
SDL_WAYLAND_SYM(size_t, xkb_keymap_کلید_get_mods_for_level, (ساخت xkb_keymap *, xkb_keycode_t, xkb_layout_اشاریہ_t, xkb_level_اشاریہ_t, xkb_mod_نقاب_t *, size_t) )
#ورنہ
// Only needed in the fallback replacement for xkb_keymap_key_get_mods_for_level().
SDL_WAYLAND_SYM(xkb_level_اشاریہ_t, xkb_state_کلید_get_level, (ساخت xkb_state *, xkb_keycode_t, xkb_layout_اشاریہ_t) )
#اگر_ختم

#اگر SDL_XKBCOMMON_CHECK_نسخہ(1, 10, 0)
SDL_WAYLAND_SYM(xkb_mod_نقاب_t, xkb_keymap_mod_get_نقاب, (ساخت xkb_keymap *, ثابت حرف *))
#اگر_ختم

#اگر_تعریف_شدہ HAVE_LIBDECOR_H
SDL_WAYLAND_MODULE(WAYLAND_LIBDECOR)

#اگر defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_نسخہ(0, 3, 0)
#تعریف_کرو SDL_libdecor_constsince03 ثابت
#ورنہ
#تعریف_کرو SDL_libdecor_constsince03 /* nothing */
#اگر_ختم

SDL_WAYLAND_SYM(خالی, libdecor_unref, (ساخت libdecor *))
SDL_WAYLAND_SYM(ساخت libdecor *, libdecor_new, (ساخت wl_display *,\
                                                  SDL_libdecor_constsince03 ساخت libdecor_interface *))
SDL_WAYLAND_SYM(ساخت libdecor_چوکھٹا *, libdecor_decorate, (ساخت libdecor *,\
                                                             ساخت wl_surface *,\
                                                             SDL_libdecor_constsince03 ساخت libdecor_چوکھٹا_interface *,\
                                                             خالی *))
SDL_WAYLAND_SYM(خالی, libdecor_چوکھٹا_unref, (ساخت libdecor_چوکھٹا *))
SDL_WAYLAND_SYM(خالی, libdecor_چوکھٹا_سیٹ_title, (ساخت libdecor_چوکھٹا *, ثابت حرف *))
SDL_WAYLAND_SYM(خالی, libdecor_چوکھٹا_سیٹ_app_id, (ساخت libdecor_چوکھٹا *, ثابت حرف *))
SDL_WAYLAND_SYM(خالی, libdecor_چوکھٹا_سیٹ_max_content_سائز, (ساخت libdecor_چوکھٹا *چوکھٹا,\
                                                            صحیح content_چوڑائی,\
                                                            صحیح content_اونچائی))
SDL_WAYLAND_SYM(خالی, libdecor_چوکھٹا_سیٹ_min_content_سائز, (ساخت libdecor_چوکھٹا *چوکھٹا,\
                                                            صحیح content_چوڑائی,\
                                                            صحیح content_اونچائی))
SDL_WAYLAND_SYM(خالی, libdecor_چوکھٹا_resize, (ساخت libdecor_چوکھٹا *,\
                                              ساخت wl_seat *,\
                                              uint32_t,\
                                              شمار libdecor_resize_کنارہ))
SDL_WAYLAND_SYM(خالی, libdecor_چوکھٹا_move, (ساخت libdecor_چوکھٹا *,\
                                            ساخت wl_seat *,\
                                            uint32_t))
SDL_WAYLAND_SYM(خالی, libdecor_چوکھٹا_commit, (ساخت libdecor_چوکھٹا *,\
                                              ساخت libdecor_state *,\
                                              ساخت libdecor_configuration *))
SDL_WAYLAND_SYM(خالی, libdecor_چوکھٹا_سیٹ_minimized, (ساخت libdecor_چوکھٹا *))
SDL_WAYLAND_SYM(خالی, libdecor_چوکھٹا_سیٹ_maximized, (ساخت libdecor_چوکھٹا *))
SDL_WAYLAND_SYM(خالی, libdecor_چوکھٹا_unset_maximized, (ساخت libdecor_چوکھٹا *))
SDL_WAYLAND_SYM(خالی, libdecor_چوکھٹا_سیٹ_fullscreen, (ساخت libdecor_چوکھٹا *, ساخت wl_output *))
SDL_WAYLAND_SYM(خالی, libdecor_چوکھٹا_unset_fullscreen, (ساخت libdecor_چوکھٹا *))
SDL_WAYLAND_SYM(خالی, libdecor_چوکھٹا_سیٹ_capabilities, (ساخت libdecor_چوکھٹا *, \
                                                        شمار libdecor_capabilities))
SDL_WAYLAND_SYM(خالی, libdecor_چوکھٹا_unset_capabilities, (ساخت libdecor_چوکھٹا *, \
                                                          شمار libdecor_capabilities))
SDL_WAYLAND_SYM(bool, libdecor_چوکھٹا_has_capability, (ساخت libdecor_چوکھٹا *, \
                                                      شمار libdecor_capabilities))
SDL_WAYLAND_SYM(خالی, libdecor_چوکھٹا_سیٹ_visibility, (ساخت libdecor_چوکھٹا *, bool))
SDL_WAYLAND_SYM(bool, libdecor_چوکھٹا_is_visible, (ساخت libdecor_چوکھٹا *))
SDL_WAYLAND_SYM(bool, libdecor_چوکھٹا_is_floating, (ساخت libdecor_چوکھٹا *))
SDL_WAYLAND_SYM(خالی, libdecor_چوکھٹا_سیٹ_والد, (ساخت libdecor_چوکھٹا *,\
                                                  ساخت libdecor_چوکھٹا *))
SDL_WAYLAND_SYM(خالی, libdecor_چوکھٹا_show_کھڑکی_menu, (ساخت libdecor_چوکھٹا *, ساخت wl_seat *, uint32_t, صحیح, صحیح))
SDL_WAYLAND_SYM(ساخت xdg_surface *, libdecor_چوکھٹا_get_xdg_surface, (ساخت libdecor_چوکھٹا *))
SDL_WAYLAND_SYM(ساخت xdg_toplevel *, libdecor_چوکھٹا_get_xdg_toplevel, (ساخت libdecor_چوکھٹا *))
SDL_WAYLAND_SYM(خالی, libdecor_چوکھٹا_translate_coordinate, (ساخت libdecor_چوکھٹا *, صحیح, صحیح, صحیح *, صحیح *))
SDL_WAYLAND_SYM(خالی, libdecor_چوکھٹا_map, (ساخت libdecor_چوکھٹا *))
SDL_WAYLAND_SYM(ساخت libdecor_state *, libdecor_state_new, (صحیح, صحیح))
SDL_WAYLAND_SYM(خالی, libdecor_state_free, (ساخت libdecor_state *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_content_سائز, (ساخت libdecor_configuration *,\
                                                                ساخت libdecor_چوکھٹا *,\
                                                                صحیح *,\
                                                                صحیح *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_کھڑکی_state, (ساخت libdecor_configuration *,\
                                                                شمار libdecor_کھڑکی_state *))
SDL_WAYLAND_SYM(صحیح, libdecor_dispatch, (ساخت libdecor *, صحیح))

#اگر defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_نسخہ(0, 2, 0)
// Only found in libdecor 0.1.1 or higher, so failure to load them is not fatal.
SDL_WAYLAND_SYM_OPT(خالی, libdecor_چوکھٹا_get_min_content_سائز, (ثابت ساخت libdecor_چوکھٹا *,\
                                                            صحیح *,\
                                                            صحیح *))
SDL_WAYLAND_SYM_OPT(خالی, libdecor_چوکھٹا_get_max_content_سائز, (ثابت ساخت libdecor_چوکھٹا *,\
                                                            صحیح *,\
                                                            صحیح *))
#اگر_ختم

#اگر defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_نسخہ(0, 3, 0)
SDL_WAYLAND_SYM_OPT(شمار libdecor_wm_capabilities, libdecor_چوکھٹا_get_wm_capabilities, (ساخت libdecor_چوکھٹا *))
#اگر_ختم

#تعریف_منسوخ SDL_libdecor_constsince03

#اگر_ختم

#تعریف_منسوخ SDL_WAYLAND_MODULE
#تعریف_منسوخ SDL_WAYLAND_SYM
#تعریف_منسوخ SDL_WAYLAND_SYM_OPT

/* *INDENT-ON* */ // clang-format on
