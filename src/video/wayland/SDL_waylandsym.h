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

#اگر_تعریف_نشده SDL_WAYLAND_MODULE
#تعریف_کن SDL_WAYLAND_MODULE(modname)
#پایان_اگر

#اگر_تعریف_نشده SDL_WAYLAND_SYM
#تعریف_کن SDL_WAYLAND_SYM(rc,fn,params)
#پایان_اگر

#اگر_تعریف_نشده SDL_WAYLAND_SYM_OPT
#تعریف_کن SDL_WAYLAND_SYM_OPT(rc,fn,params)
#پایان_اگر

SDL_WAYLAND_MODULE(WAYLAND_CLIENT)
SDL_WAYLAND_SYM(فراغ, wl_proxy_marshal, (بنية wl_proxy *, uint32_t, ...))
SDL_WAYLAND_SYM(بنية wl_proxy *, wl_proxy_create, (بنية wl_proxy *, ثابت بنية wl_interface *))
SDL_WAYLAND_SYM(فراغ, wl_proxy_destroy, (بنية wl_proxy *))
SDL_WAYLAND_SYM(صحيح, wl_proxy_جمع_کن_listener, (بنية wl_proxy *, فراغ (**)(فراغ), فراغ *))
SDL_WAYLAND_SYM(فراغ, wl_proxy_مجموعه_user_داده, (بنية wl_proxy *, فراغ *))
SDL_WAYLAND_SYM(فراغ *, wl_proxy_get_user_داده, (بنية wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_نسخه, (بنية wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_id, (بنية wl_proxy *))
SDL_WAYLAND_SYM(ثابت حرف *, wl_proxy_get_class, (بنية wl_proxy *))
SDL_WAYLAND_SYM(فراغ, wl_proxy_مجموعه_صف, (بنية wl_proxy *, بنية wl_event_صف *))
SDL_WAYLAND_SYM(فراغ *, wl_proxy_create_wrapper, (فراغ *))
SDL_WAYLAND_SYM(فراغ, wl_proxy_wrapper_destroy, (فراغ *))
SDL_WAYLAND_SYM(بنية wl_display *, wl_display_connect, (ثابت حرف *))
SDL_WAYLAND_SYM(بنية wl_display *, wl_display_connect_مقصد_fd, (صحيح))
SDL_WAYLAND_SYM(فراغ, wl_display_disconnect, (بنية wl_display *))
SDL_WAYLAND_SYM(صحيح, wl_display_get_fd, (بنية wl_display *))
SDL_WAYLAND_SYM(صحيح, wl_display_dispatch, (بنية wl_display *))
SDL_WAYLAND_SYM(صحيح, wl_display_dispatch_صف, (بنية wl_display *, بنية wl_event_صف *))
SDL_WAYLAND_SYM(صحيح, wl_display_dispatch_صف_pending, (بنية wl_display *, بنية wl_event_صف *))
SDL_WAYLAND_SYM(صحيح, wl_display_dispatch_pending, (بنية wl_display *))
SDL_WAYLAND_SYM(صحيح, wl_display_prepare_read, (بنية wl_display *))
SDL_WAYLAND_SYM(صحيح, wl_display_prepare_read_صف, (بنية wl_display *, بنية wl_event_صف *))
SDL_WAYLAND_SYM(صحيح, wl_display_read_events, (بنية wl_display *))
SDL_WAYLAND_SYM(فراغ, wl_display_cancel_read, (بنية wl_display *))
SDL_WAYLAND_SYM(صحيح, wl_display_get_error, (بنية wl_display *))
SDL_WAYLAND_SYM(صحيح, wl_display_flush, (بنية wl_display *))
SDL_WAYLAND_SYM(صحيح, wl_display_roundtrip, (بنية wl_display *))
SDL_WAYLAND_SYM(بنية wl_event_صف *, wl_display_create_صف, (بنية wl_display *))
SDL_WAYLAND_SYM(فراغ, wl_event_صف_destroy, (بنية wl_event_صف *))
SDL_WAYLAND_SYM(فراغ, wl_log_مجموعه_handler_client, (wl_log_func_t))
SDL_WAYLAND_SYM(فراغ, wl_list_init, (بنية wl_list *))
SDL_WAYLAND_SYM(فراغ, wl_list_درج, (بنية wl_list *, بنية wl_list *) )
SDL_WAYLAND_SYM(فراغ, wl_list_remove, (بنية wl_list *))
SDL_WAYLAND_SYM(صحيح, wl_list_درازی, (ثابت بنية wl_list *))
SDL_WAYLAND_SYM(صحيح, wl_list_خالی, (ثابت بنية wl_list *))
SDL_WAYLAND_SYM(فراغ, wl_list_درج_list, (بنية wl_list *, بنية wl_list *))
SDL_WAYLAND_SYM(فراغ, wl_array_init, (بنية wl_array *))
SDL_WAYLAND_SYM(فراغ, wl_array_release, (بنية wl_array *))
SDL_WAYLAND_SYM(فراغ *, wl_array_جمع_کن, (بنية wl_array *, size_t))
SDL_WAYLAND_SYM(صحيح, wl_array_copy, (بنية wl_array *, بنية wl_array *))
SDL_WAYLAND_SYM(بنية wl_proxy *, wl_proxy_marshal_constructor, (بنية wl_proxy *, uint32_t opcode, ثابت بنية wl_interface *interface, ...))
SDL_WAYLAND_SYM(بنية wl_proxy *, wl_proxy_marshal_constructor_versioned, (بنية wl_proxy *proxy, uint32_t opcode, ثابت بنية wl_interface *interface, uint32_t نسخه, ...))
SDL_WAYLAND_SYM(فراغ, wl_proxy_مجموعه_برچسب, (بنية wl_proxy *, ثابت حرف * ثابت *))
SDL_WAYLAND_SYM(ثابت حرف * ثابت *, wl_proxy_get_برچسب, (بنية wl_proxy *))

#إذا SDL_WAYLAND_CHECK_نسخه(1, 20, 0)
/* wayland-scanner 1.20 generates code that will call these, so these are
 * non-optional when we are compiling against Wayland 1.20. We don't
 * explicitly call them ourselves, though, so if we are only compiling
 * against Wayland 1.18, they're unnecessary. */
SDL_WAYLAND_SYM(بنية wl_proxy *, wl_proxy_marshal_flags, (بنية wl_proxy *proxy, uint32_t opcode, ثابت بنية wl_interface *interface, uint32_t نسخه, uint32_t flags, ...))
SDL_WAYLAND_SYM(بنية wl_proxy *, wl_proxy_marshal_array_flags, (بنية wl_proxy *proxy, uint32_t opcode, ثابت بنية wl_interface *interface, uint32_t نسخه,  uint32_t flags, اتحاد wl_آرگومان *آرگومانها))
#پایان_اگر

#إذا SDL_WAYLAND_CHECK_نسخه(1, 23, 0) || defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC)
SDL_WAYLAND_SYM_OPT(بنية wl_event_صف *, wl_display_create_صف_with_name, (بنية wl_display *display, ثابت حرف *name))
#پایان_اگر

#إذا 0 // TODO RECONNECT: See waylandvideo.c for more information!
#إذا SDL_WAYLAND_CHECK_نسخه(broken, on, purpose)
SDL_WAYLAND_SYM(صحيح, wl_display_reconnect, (بنية wl_display *))
#پایان_اگر
#پایان_اگر // 0

SDL_WAYLAND_MODULE(WAYLAND_EGL)
SDL_WAYLAND_SYM(بنية wl_egl_پنجره *, wl_egl_پنجره_create, (بنية wl_surface *, صحيح, صحيح))
SDL_WAYLAND_SYM(فراغ, wl_egl_پنجره_destroy, (بنية wl_egl_پنجره *))
SDL_WAYLAND_SYM(فراغ, wl_egl_پنجره_resize, (بنية wl_egl_پنجره *, صحيح, صحيح, صحيح, صحيح))
SDL_WAYLAND_SYM(فراغ, wl_egl_پنجره_get_attached_اندازه, (بنية wl_egl_پنجره *, صحيح *, صحيح *))

SDL_WAYLAND_MODULE(WAYLAND_CURSOR)
SDL_WAYLAND_SYM(بنية wl_cursor_theme *, wl_cursor_theme_بارگیری, (ثابت حرف *, صحيح , بنية wl_shm *))
SDL_WAYLAND_SYM(فراغ, wl_cursor_theme_destroy, (بنية wl_cursor_theme *))
SDL_WAYLAND_SYM(بنية wl_cursor *, wl_cursor_theme_get_cursor, (بنية wl_cursor_theme *, ثابت حرف *))
SDL_WAYLAND_SYM(بنية wl_میانگیر *, wl_cursor_image_get_میانگیر, (بنية wl_cursor_image *))
SDL_WAYLAND_SYM(صحيح, wl_cursor_قاب, (بنية wl_cursor *, uint32_t))

SDL_WAYLAND_MODULE(WAYLAND_XKB)
SDL_WAYLAND_SYM(صحيح, xkb_state_کلید_get_syms, (بنية xkb_state *, xkb_keycode_t, ثابت xkb_keysym_t **))
SDL_WAYLAND_SYM(صحيح, xkb_keysym_مقصد_utf8, (xkb_keysym_t, حرف *, size_t) )
SDL_WAYLAND_SYM(بنية xkb_keymap *, xkb_keymap_new_from_string, (بنية xkb_context *, ثابت حرف *, تعداد xkb_keymap_format, تعداد xkb_keymap_compile_flags))
SDL_WAYLAND_SYM(بنية xkb_state *, xkb_state_new, (بنية xkb_keymap *) )
SDL_WAYLAND_SYM(صحيح, xkb_keymap_کلید_repeats, (بنية xkb_keymap *keymap, xkb_keycode_t کلید) )
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
SDL_WAYLAND_SYM(تعداد xkb_compose_feed_نتیجه, xkb_compose_state_feed, (بنية xkb_compose_state *, xkb_keysym_t) )
SDL_WAYLAND_SYM(تعداد xkb_compose_وضعیت, xkb_compose_state_get_وضعیت, (بنية xkb_compose_state *) )
SDL_WAYLAND_SYM(xkb_keysym_t, xkb_compose_state_get_one_sym, (بنية xkb_compose_state *) )
SDL_WAYLAND_SYM(فراغ, xkb_keymap_کلید_for_each, (بنية xkb_keymap *, xkb_keymap_کلید_iter_t, فراغ *) )
SDL_WAYLAND_SYM(xkb_layout_شاخص_t, xkb_keymap_رقم_layouts, (بنية xkb_keymap *) )
SDL_WAYLAND_SYM(صحيح, xkb_keymap_کلید_get_syms_by_level, (بنية xkb_keymap *, xkb_keycode_t, xkb_layout_شاخص_t, xkb_level_شاخص_t, ثابت xkb_keysym_t **) )
SDL_WAYLAND_SYM(xkb_level_شاخص_t, xkb_keymap_رقم_سطوح_for_کلید, (بنية xkb_keymap *, xkb_keycode_t, xkb_layout_شاخص_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keysym_مقصد_utf32, (xkb_keysym_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keymap_mod_get_شاخص, (بنية xkb_keymap *, ثابت حرف *) )
SDL_WAYLAND_SYM(ثابت حرف *, xkb_keymap_layout_get_name, (بنية xkb_keymap *, xkb_layout_شاخص_t))

#إذا SDL_XKBCOMMON_CHECK_نسخه(1, 0, 0)
SDL_WAYLAND_SYM(size_t, xkb_keymap_کلید_get_mods_for_level, (بنية xkb_keymap *, xkb_keycode_t, xkb_layout_شاخص_t, xkb_level_شاخص_t, xkb_mod_ماسک_t *, size_t) )
#وإلا
// Only needed in the fallback replacement for xkb_keymap_key_get_mods_for_level().
SDL_WAYLAND_SYM(xkb_level_شاخص_t, xkb_state_کلید_get_level, (بنية xkb_state *, xkb_keycode_t, xkb_layout_شاخص_t) )
#پایان_اگر

#إذا SDL_XKBCOMMON_CHECK_نسخه(1, 10, 0)
SDL_WAYLAND_SYM(xkb_mod_ماسک_t, xkb_keymap_mod_get_ماسک, (بنية xkb_keymap *, ثابت حرف *))
#پایان_اگر

#اگر_تعریف_شده HAVE_LIBDECOR_H
SDL_WAYLAND_MODULE(WAYLAND_LIBDECOR)

#إذا defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_نسخه(0, 3, 0)
#تعریف_کن SDL_libdecor_constsince03 ثابت
#وإلا
#تعریف_کن SDL_libdecor_constsince03 /* nothing */
#پایان_اگر

SDL_WAYLAND_SYM(فراغ, libdecor_unref, (بنية libdecor *))
SDL_WAYLAND_SYM(بنية libdecor *, libdecor_new, (بنية wl_display *,\
                                                  SDL_libdecor_constsince03 بنية libdecor_interface *))
SDL_WAYLAND_SYM(بنية libdecor_قاب *, libdecor_decorate, (بنية libdecor *,\
                                                             بنية wl_surface *,\
                                                             SDL_libdecor_constsince03 بنية libdecor_قاب_interface *,\
                                                             فراغ *))
SDL_WAYLAND_SYM(فراغ, libdecor_قاب_unref, (بنية libdecor_قاب *))
SDL_WAYLAND_SYM(فراغ, libdecor_قاب_مجموعه_title, (بنية libdecor_قاب *, ثابت حرف *))
SDL_WAYLAND_SYM(فراغ, libdecor_قاب_مجموعه_app_id, (بنية libdecor_قاب *, ثابت حرف *))
SDL_WAYLAND_SYM(فراغ, libdecor_قاب_مجموعه_max_content_اندازه, (بنية libdecor_قاب *قاب,\
                                                            صحيح content_عرض,\
                                                            صحيح content_ارتفاع))
SDL_WAYLAND_SYM(فراغ, libdecor_قاب_مجموعه_min_content_اندازه, (بنية libdecor_قاب *قاب,\
                                                            صحيح content_عرض,\
                                                            صحيح content_ارتفاع))
SDL_WAYLAND_SYM(فراغ, libdecor_قاب_resize, (بنية libdecor_قاب *,\
                                              بنية wl_seat *,\
                                              uint32_t,\
                                              تعداد libdecor_resize_یال))
SDL_WAYLAND_SYM(فراغ, libdecor_قاب_move, (بنية libdecor_قاب *,\
                                            بنية wl_seat *,\
                                            uint32_t))
SDL_WAYLAND_SYM(فراغ, libdecor_قاب_commit, (بنية libdecor_قاب *,\
                                              بنية libdecor_state *,\
                                              بنية libdecor_configuration *))
SDL_WAYLAND_SYM(فراغ, libdecor_قاب_مجموعه_minimized, (بنية libdecor_قاب *))
SDL_WAYLAND_SYM(فراغ, libdecor_قاب_مجموعه_maximized, (بنية libdecor_قاب *))
SDL_WAYLAND_SYM(فراغ, libdecor_قاب_unset_maximized, (بنية libdecor_قاب *))
SDL_WAYLAND_SYM(فراغ, libdecor_قاب_مجموعه_fullscreen, (بنية libdecor_قاب *, بنية wl_output *))
SDL_WAYLAND_SYM(فراغ, libdecor_قاب_unset_fullscreen, (بنية libdecor_قاب *))
SDL_WAYLAND_SYM(فراغ, libdecor_قاب_مجموعه_capabilities, (بنية libdecor_قاب *, \
                                                        تعداد libdecor_capabilities))
SDL_WAYLAND_SYM(فراغ, libdecor_قاب_unset_capabilities, (بنية libdecor_قاب *, \
                                                          تعداد libdecor_capabilities))
SDL_WAYLAND_SYM(bool, libdecor_قاب_has_capability, (بنية libdecor_قاب *, \
                                                      تعداد libdecor_capabilities))
SDL_WAYLAND_SYM(فراغ, libdecor_قاب_مجموعه_visibility, (بنية libdecor_قاب *, bool))
SDL_WAYLAND_SYM(bool, libdecor_قاب_is_visible, (بنية libdecor_قاب *))
SDL_WAYLAND_SYM(bool, libdecor_قاب_is_floating, (بنية libdecor_قاب *))
SDL_WAYLAND_SYM(فراغ, libdecor_قاب_مجموعه_والد, (بنية libdecor_قاب *,\
                                                  بنية libdecor_قاب *))
SDL_WAYLAND_SYM(فراغ, libdecor_قاب_show_پنجره_menu, (بنية libdecor_قاب *, بنية wl_seat *, uint32_t, صحيح, صحيح))
SDL_WAYLAND_SYM(بنية xdg_surface *, libdecor_قاب_get_xdg_surface, (بنية libdecor_قاب *))
SDL_WAYLAND_SYM(بنية xdg_toplevel *, libdecor_قاب_get_xdg_toplevel, (بنية libdecor_قاب *))
SDL_WAYLAND_SYM(فراغ, libdecor_قاب_translate_coordinate, (بنية libdecor_قاب *, صحيح, صحيح, صحيح *, صحيح *))
SDL_WAYLAND_SYM(فراغ, libdecor_قاب_map, (بنية libdecor_قاب *))
SDL_WAYLAND_SYM(بنية libdecor_state *, libdecor_state_new, (صحيح, صحيح))
SDL_WAYLAND_SYM(فراغ, libdecor_state_free, (بنية libdecor_state *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_content_اندازه, (بنية libdecor_configuration *,\
                                                                بنية libdecor_قاب *,\
                                                                صحيح *,\
                                                                صحيح *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_پنجره_state, (بنية libdecor_configuration *,\
                                                                تعداد libdecor_پنجره_state *))
SDL_WAYLAND_SYM(صحيح, libdecor_dispatch, (بنية libdecor *, صحيح))

#إذا defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_نسخه(0, 2, 0)
// Only found in libdecor 0.1.1 or higher, so failure to load them is not fatal.
SDL_WAYLAND_SYM_OPT(فراغ, libdecor_قاب_get_min_content_اندازه, (ثابت بنية libdecor_قاب *,\
                                                            صحيح *,\
                                                            صحيح *))
SDL_WAYLAND_SYM_OPT(فراغ, libdecor_قاب_get_max_content_اندازه, (ثابت بنية libdecor_قاب *,\
                                                            صحيح *,\
                                                            صحيح *))
#پایان_اگر

#إذا defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_نسخه(0, 3, 0)
SDL_WAYLAND_SYM_OPT(تعداد libdecor_wm_capabilities, libdecor_قاب_get_wm_capabilities, (بنية libdecor_قاب *))
#پایان_اگر

#لغو_تعریف SDL_libdecor_constsince03

#پایان_اگر

#لغو_تعریف SDL_WAYLAND_MODULE
#لغو_تعریف SDL_WAYLAND_SYM
#لغو_تعریف SDL_WAYLAND_SYM_OPT

/* *INDENT-ON* */ // clang-format on
