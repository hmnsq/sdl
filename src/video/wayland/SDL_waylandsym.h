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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_WAYLAND_MODULE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_WAYLAND_MODULE(modname)
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_WAYLAND_SYM
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_WAYLAND_SYM(rc,fn,params)
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_WAYLAND_SYM_OPT
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_WAYLAND_SYM_OPT(rc,fn,params)
#ਜੇ_ਅੰਤ

SDL_WAYLAND_MODULE(WAYLAND_CLIENT)
SDL_WAYLAND_SYM(ਖਾਲੀ, wl_proxy_marshal, (ਬਣਤਰ wl_proxy *, uint32_t, ...))
SDL_WAYLAND_SYM(ਬਣਤਰ wl_proxy *, wl_proxy_create, (ਬਣਤਰ wl_proxy *, ਅਚਲ ਬਣਤਰ wl_interface *))
SDL_WAYLAND_SYM(ਖਾਲੀ, wl_proxy_destroy, (ਬਣਤਰ wl_proxy *))
SDL_WAYLAND_SYM(ਪੂਰਨ, wl_proxy_ਜੋੜੋ_listener, (ਬਣਤਰ wl_proxy *, ਖਾਲੀ (**)(ਖਾਲੀ), ਖਾਲੀ *))
SDL_WAYLAND_SYM(ਖਾਲੀ, wl_proxy_ਸੈੱਟ_user_ਅੰਕੜੇ, (ਬਣਤਰ wl_proxy *, ਖਾਲੀ *))
SDL_WAYLAND_SYM(ਖਾਲੀ *, wl_proxy_get_user_ਅੰਕੜੇ, (ਬਣਤਰ wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_ਸੰਸਕਰਣ, (ਬਣਤਰ wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_id, (ਬਣਤਰ wl_proxy *))
SDL_WAYLAND_SYM(ਅਚਲ ਅੱਖਰ *, wl_proxy_get_class, (ਬਣਤਰ wl_proxy *))
SDL_WAYLAND_SYM(ਖਾਲੀ, wl_proxy_ਸੈੱਟ_ਕਤਾਰ, (ਬਣਤਰ wl_proxy *, ਬਣਤਰ wl_event_ਕਤਾਰ *))
SDL_WAYLAND_SYM(ਖਾਲੀ *, wl_proxy_create_wrapper, (ਖਾਲੀ *))
SDL_WAYLAND_SYM(ਖਾਲੀ, wl_proxy_wrapper_destroy, (ਖਾਲੀ *))
SDL_WAYLAND_SYM(ਬਣਤਰ wl_display *, wl_display_connect, (ਅਚਲ ਅੱਖਰ *))
SDL_WAYLAND_SYM(ਬਣਤਰ wl_display *, wl_display_connect_ਮੰਜ਼ਿਲ_fd, (ਪੂਰਨ))
SDL_WAYLAND_SYM(ਖਾਲੀ, wl_display_disconnect, (ਬਣਤਰ wl_display *))
SDL_WAYLAND_SYM(ਪੂਰਨ, wl_display_get_fd, (ਬਣਤਰ wl_display *))
SDL_WAYLAND_SYM(ਪੂਰਨ, wl_display_dispatch, (ਬਣਤਰ wl_display *))
SDL_WAYLAND_SYM(ਪੂਰਨ, wl_display_dispatch_ਕਤਾਰ, (ਬਣਤਰ wl_display *, ਬਣਤਰ wl_event_ਕਤਾਰ *))
SDL_WAYLAND_SYM(ਪੂਰਨ, wl_display_dispatch_ਕਤਾਰ_pending, (ਬਣਤਰ wl_display *, ਬਣਤਰ wl_event_ਕਤਾਰ *))
SDL_WAYLAND_SYM(ਪੂਰਨ, wl_display_dispatch_pending, (ਬਣਤਰ wl_display *))
SDL_WAYLAND_SYM(ਪੂਰਨ, wl_display_prepare_read, (ਬਣਤਰ wl_display *))
SDL_WAYLAND_SYM(ਪੂਰਨ, wl_display_prepare_read_ਕਤਾਰ, (ਬਣਤਰ wl_display *, ਬਣਤਰ wl_event_ਕਤਾਰ *))
SDL_WAYLAND_SYM(ਪੂਰਨ, wl_display_read_events, (ਬਣਤਰ wl_display *))
SDL_WAYLAND_SYM(ਖਾਲੀ, wl_display_cancel_read, (ਬਣਤਰ wl_display *))
SDL_WAYLAND_SYM(ਪੂਰਨ, wl_display_get_error, (ਬਣਤਰ wl_display *))
SDL_WAYLAND_SYM(ਪੂਰਨ, wl_display_flush, (ਬਣਤਰ wl_display *))
SDL_WAYLAND_SYM(ਪੂਰਨ, wl_display_roundtrip, (ਬਣਤਰ wl_display *))
SDL_WAYLAND_SYM(ਬਣਤਰ wl_event_ਕਤਾਰ *, wl_display_create_ਕਤਾਰ, (ਬਣਤਰ wl_display *))
SDL_WAYLAND_SYM(ਖਾਲੀ, wl_event_ਕਤਾਰ_destroy, (ਬਣਤਰ wl_event_ਕਤਾਰ *))
SDL_WAYLAND_SYM(ਖਾਲੀ, wl_log_ਸੈੱਟ_handler_client, (wl_log_func_t))
SDL_WAYLAND_SYM(ਖਾਲੀ, wl_list_init, (ਬਣਤਰ wl_list *))
SDL_WAYLAND_SYM(ਖਾਲੀ, wl_list_ਪਾਓ, (ਬਣਤਰ wl_list *, ਬਣਤਰ wl_list *) )
SDL_WAYLAND_SYM(ਖਾਲੀ, wl_list_remove, (ਬਣਤਰ wl_list *))
SDL_WAYLAND_SYM(ਪੂਰਨ, wl_list_ਲੰਮਾਈ, (ਅਚਲ ਬਣਤਰ wl_list *))
SDL_WAYLAND_SYM(ਪੂਰਨ, wl_list_ਖਾਲੀ_ਥਾਵਾਂ, (ਅਚਲ ਬਣਤਰ wl_list *))
SDL_WAYLAND_SYM(ਖਾਲੀ, wl_list_ਪਾਓ_list, (ਬਣਤਰ wl_list *, ਬਣਤਰ wl_list *))
SDL_WAYLAND_SYM(ਖਾਲੀ, wl_array_init, (ਬਣਤਰ wl_array *))
SDL_WAYLAND_SYM(ਖਾਲੀ, wl_array_release, (ਬਣਤਰ wl_array *))
SDL_WAYLAND_SYM(ਖਾਲੀ *, wl_array_ਜੋੜੋ, (ਬਣਤਰ wl_array *, size_t))
SDL_WAYLAND_SYM(ਪੂਰਨ, wl_array_copy, (ਬਣਤਰ wl_array *, ਬਣਤਰ wl_array *))
SDL_WAYLAND_SYM(ਬਣਤਰ wl_proxy *, wl_proxy_marshal_constructor, (ਬਣਤਰ wl_proxy *, uint32_t opcode, ਅਚਲ ਬਣਤਰ wl_interface *interface, ...))
SDL_WAYLAND_SYM(ਬਣਤਰ wl_proxy *, wl_proxy_marshal_constructor_versioned, (ਬਣਤਰ wl_proxy *proxy, uint32_t opcode, ਅਚਲ ਬਣਤਰ wl_interface *interface, uint32_t ਸੰਸਕਰਣ, ...))
SDL_WAYLAND_SYM(ਖਾਲੀ, wl_proxy_ਸੈੱਟ_ਟੈਗ, (ਬਣਤਰ wl_proxy *, ਅਚਲ ਅੱਖਰ * ਅਚਲ *))
SDL_WAYLAND_SYM(ਅਚਲ ਅੱਖਰ * ਅਚਲ *, wl_proxy_get_ਟੈਗ, (ਬਣਤਰ wl_proxy *))

#ਜੇ SDL_WAYLAND_CHECK_ਸੰਸਕਰਣ(1, 20, 0)
/* wayland-scanner 1.20 generates code that will call these, so these are
 * non-optional when we are compiling against Wayland 1.20. We don't
 * explicitly call them ourselves, though, so if we are only compiling
 * against Wayland 1.18, they're unnecessary. */
SDL_WAYLAND_SYM(ਬਣਤਰ wl_proxy *, wl_proxy_marshal_flags, (ਬਣਤਰ wl_proxy *proxy, uint32_t opcode, ਅਚਲ ਬਣਤਰ wl_interface *interface, uint32_t ਸੰਸਕਰਣ, uint32_t flags, ...))
SDL_WAYLAND_SYM(ਬਣਤਰ wl_proxy *, wl_proxy_marshal_array_flags, (ਬਣਤਰ wl_proxy *proxy, uint32_t opcode, ਅਚਲ ਬਣਤਰ wl_interface *interface, uint32_t ਸੰਸਕਰਣ,  uint32_t flags, ਸੰਘ wl_ਦਲੀਲ *ਦਲੀਲਾਂ))
#ਜੇ_ਅੰਤ

#ਜੇ SDL_WAYLAND_CHECK_ਸੰਸਕਰਣ(1, 23, 0) || defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC)
SDL_WAYLAND_SYM_OPT(ਬਣਤਰ wl_event_ਕਤਾਰ *, wl_display_create_ਕਤਾਰ_with_name, (ਬਣਤਰ wl_display *display, ਅਚਲ ਅੱਖਰ *name))
#ਜੇ_ਅੰਤ

#ਜੇ 0 // TODO RECONNECT: See waylandvideo.c for more information!
#ਜੇ SDL_WAYLAND_CHECK_ਸੰਸਕਰਣ(broken, on, purpose)
SDL_WAYLAND_SYM(ਪੂਰਨ, wl_display_reconnect, (ਬਣਤਰ wl_display *))
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ // 0

SDL_WAYLAND_MODULE(WAYLAND_EGL)
SDL_WAYLAND_SYM(ਬਣਤਰ wl_egl_ਖਿੜਕੀ *, wl_egl_ਖਿੜਕੀ_create, (ਬਣਤਰ wl_surface *, ਪੂਰਨ, ਪੂਰਨ))
SDL_WAYLAND_SYM(ਖਾਲੀ, wl_egl_ਖਿੜਕੀ_destroy, (ਬਣਤਰ wl_egl_ਖਿੜਕੀ *))
SDL_WAYLAND_SYM(ਖਾਲੀ, wl_egl_ਖਿੜਕੀ_resize, (ਬਣਤਰ wl_egl_ਖਿੜਕੀ *, ਪੂਰਨ, ਪੂਰਨ, ਪੂਰਨ, ਪੂਰਨ))
SDL_WAYLAND_SYM(ਖਾਲੀ, wl_egl_ਖਿੜਕੀ_get_attached_ਮਾਪ, (ਬਣਤਰ wl_egl_ਖਿੜਕੀ *, ਪੂਰਨ *, ਪੂਰਨ *))

SDL_WAYLAND_MODULE(WAYLAND_CURSOR)
SDL_WAYLAND_SYM(ਬਣਤਰ wl_cursor_theme *, wl_cursor_theme_ਲੱਦੋ, (ਅਚਲ ਅੱਖਰ *, ਪੂਰਨ , ਬਣਤਰ wl_shm *))
SDL_WAYLAND_SYM(ਖਾਲੀ, wl_cursor_theme_destroy, (ਬਣਤਰ wl_cursor_theme *))
SDL_WAYLAND_SYM(ਬਣਤਰ wl_cursor *, wl_cursor_theme_get_cursor, (ਬਣਤਰ wl_cursor_theme *, ਅਚਲ ਅੱਖਰ *))
SDL_WAYLAND_SYM(ਬਣਤਰ wl_ਬਫਰ *, wl_cursor_image_get_ਬਫਰ, (ਬਣਤਰ wl_cursor_image *))
SDL_WAYLAND_SYM(ਪੂਰਨ, wl_cursor_ਚੌਖਟਾ, (ਬਣਤਰ wl_cursor *, uint32_t))

SDL_WAYLAND_MODULE(WAYLAND_XKB)
SDL_WAYLAND_SYM(ਪੂਰਨ, xkb_state_ਕੁੰਜੀ_get_syms, (ਬਣਤਰ xkb_state *, xkb_keycode_t, ਅਚਲ xkb_keysym_t **))
SDL_WAYLAND_SYM(ਪੂਰਨ, xkb_keysym_ਮੰਜ਼ਿਲ_utf8, (xkb_keysym_t, ਅੱਖਰ *, size_t) )
SDL_WAYLAND_SYM(ਬਣਤਰ xkb_keymap *, xkb_keymap_new_from_string, (ਬਣਤਰ xkb_context *, ਅਚਲ ਅੱਖਰ *, ਗਿਣਤੀ xkb_keymap_format, ਗਿਣਤੀ xkb_keymap_compile_flags))
SDL_WAYLAND_SYM(ਬਣਤਰ xkb_state *, xkb_state_new, (ਬਣਤਰ xkb_keymap *) )
SDL_WAYLAND_SYM(ਪੂਰਨ, xkb_keymap_ਕੁੰਜੀ_repeats, (ਬਣਤਰ xkb_keymap *keymap, xkb_keycode_t ਕੁੰਜੀ) )
SDL_WAYLAND_SYM(ਖਾਲੀ, xkb_keymap_unref, (ਬਣਤਰ xkb_keymap *) )
SDL_WAYLAND_SYM(ਖਾਲੀ, xkb_state_unref, (ਬਣਤਰ xkb_state *) )
SDL_WAYLAND_SYM(ਖਾਲੀ, xkb_context_unref, (ਬਣਤਰ xkb_context *) )
SDL_WAYLAND_SYM(ਬਣਤਰ xkb_context *, xkb_context_new, (ਗਿਣਤੀ xkb_context_flags flags) )
SDL_WAYLAND_SYM(ਗਿਣਤੀ xkb_state_component, xkb_state_update_ਨਕਾਬ, (ਬਣਤਰ xkb_state *state,\
                      xkb_mod_ਨਕਾਬ_t depressed_mods,\
                      xkb_mod_ਨਕਾਬ_t latched_mods,\
                      xkb_mod_ਨਕਾਬ_t locked_mods,\
                      xkb_layout_ਸੂਚਕਾਂਕ_t depressed_layout,\
                      xkb_layout_ਸੂਚਕਾਂਕ_t latched_layout,\
                      xkb_layout_ਸੂਚਕਾਂਕ_t locked_layout) )
SDL_WAYLAND_SYM(ਬਣਤਰ xkb_compose_ਸਾਰਣੀ *, xkb_compose_ਸਾਰਣੀ_new_from_locale, (ਬਣਤਰ xkb_context *,\
                      ਅਚਲ ਅੱਖਰ *locale, ਗਿਣਤੀ xkb_compose_compile_flags) )
SDL_WAYLAND_SYM(ਖਾਲੀ, xkb_compose_state_reset, (ਬਣਤਰ xkb_compose_state *) )
SDL_WAYLAND_SYM(ਖਾਲੀ, xkb_compose_ਸਾਰਣੀ_unref, (ਬਣਤਰ xkb_compose_ਸਾਰਣੀ *) )
SDL_WAYLAND_SYM(ਬਣਤਰ xkb_compose_state *, xkb_compose_state_new, (ਬਣਤਰ xkb_compose_ਸਾਰਣੀ *, ਗਿਣਤੀ xkb_compose_state_flags) )
SDL_WAYLAND_SYM(ਖਾਲੀ, xkb_compose_state_unref, (ਬਣਤਰ xkb_compose_state *) )
SDL_WAYLAND_SYM(ਗਿਣਤੀ xkb_compose_feed_ਨਤੀਜਾ, xkb_compose_state_feed, (ਬਣਤਰ xkb_compose_state *, xkb_keysym_t) )
SDL_WAYLAND_SYM(ਗਿਣਤੀ xkb_compose_ਸਥਿਤੀ, xkb_compose_state_get_ਸਥਿਤੀ, (ਬਣਤਰ xkb_compose_state *) )
SDL_WAYLAND_SYM(xkb_keysym_t, xkb_compose_state_get_one_sym, (ਬਣਤਰ xkb_compose_state *) )
SDL_WAYLAND_SYM(ਖਾਲੀ, xkb_keymap_ਕੁੰਜੀ_for_each, (ਬਣਤਰ xkb_keymap *, xkb_keymap_ਕੁੰਜੀ_iter_t, ਖਾਲੀ *) )
SDL_WAYLAND_SYM(xkb_layout_ਸੂਚਕਾਂਕ_t, xkb_keymap_ਅੰਕ_layouts, (ਬਣਤਰ xkb_keymap *) )
SDL_WAYLAND_SYM(ਪੂਰਨ, xkb_keymap_ਕੁੰਜੀ_get_syms_by_level, (ਬਣਤਰ xkb_keymap *, xkb_keycode_t, xkb_layout_ਸੂਚਕਾਂਕ_t, xkb_level_ਸੂਚਕਾਂਕ_t, ਅਚਲ xkb_keysym_t **) )
SDL_WAYLAND_SYM(xkb_level_ਸੂਚਕਾਂਕ_t, xkb_keymap_ਅੰਕ_ਪੱਧਰ_for_ਕੁੰਜੀ, (ਬਣਤਰ xkb_keymap *, xkb_keycode_t, xkb_layout_ਸੂਚਕਾਂਕ_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keysym_ਮੰਜ਼ਿਲ_utf32, (xkb_keysym_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keymap_mod_get_ਸੂਚਕਾਂਕ, (ਬਣਤਰ xkb_keymap *, ਅਚਲ ਅੱਖਰ *) )
SDL_WAYLAND_SYM(ਅਚਲ ਅੱਖਰ *, xkb_keymap_layout_get_name, (ਬਣਤਰ xkb_keymap *, xkb_layout_ਸੂਚਕਾਂਕ_t))

#ਜੇ SDL_XKBCOMMON_CHECK_ਸੰਸਕਰਣ(1, 0, 0)
SDL_WAYLAND_SYM(size_t, xkb_keymap_ਕੁੰਜੀ_get_mods_for_level, (ਬਣਤਰ xkb_keymap *, xkb_keycode_t, xkb_layout_ਸੂਚਕਾਂਕ_t, xkb_level_ਸੂਚਕਾਂਕ_t, xkb_mod_ਨਕਾਬ_t *, size_t) )
#ਨਹੀਂਤਾਂ
// Only needed in the fallback replacement for xkb_keymap_key_get_mods_for_level().
SDL_WAYLAND_SYM(xkb_level_ਸੂਚਕਾਂਕ_t, xkb_state_ਕੁੰਜੀ_get_level, (ਬਣਤਰ xkb_state *, xkb_keycode_t, xkb_layout_ਸੂਚਕਾਂਕ_t) )
#ਜੇ_ਅੰਤ

#ਜੇ SDL_XKBCOMMON_CHECK_ਸੰਸਕਰਣ(1, 10, 0)
SDL_WAYLAND_SYM(xkb_mod_ਨਕਾਬ_t, xkb_keymap_mod_get_ਨਕਾਬ, (ਬਣਤਰ xkb_keymap *, ਅਚਲ ਅੱਖਰ *))
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
SDL_WAYLAND_MODULE(WAYLAND_LIBDECOR)

#ਜੇ defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_ਸੰਸਕਰਣ(0, 3, 0)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_libdecor_constsince03 ਅਚਲ
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_libdecor_constsince03 /* nothing */
#ਜੇ_ਅੰਤ

SDL_WAYLAND_SYM(ਖਾਲੀ, libdecor_unref, (ਬਣਤਰ libdecor *))
SDL_WAYLAND_SYM(ਬਣਤਰ libdecor *, libdecor_new, (ਬਣਤਰ wl_display *,\
                                                  SDL_libdecor_constsince03 ਬਣਤਰ libdecor_interface *))
SDL_WAYLAND_SYM(ਬਣਤਰ libdecor_ਚੌਖਟਾ *, libdecor_decorate, (ਬਣਤਰ libdecor *,\
                                                             ਬਣਤਰ wl_surface *,\
                                                             SDL_libdecor_constsince03 ਬਣਤਰ libdecor_ਚੌਖਟਾ_interface *,\
                                                             ਖਾਲੀ *))
SDL_WAYLAND_SYM(ਖਾਲੀ, libdecor_ਚੌਖਟਾ_unref, (ਬਣਤਰ libdecor_ਚੌਖਟਾ *))
SDL_WAYLAND_SYM(ਖਾਲੀ, libdecor_ਚੌਖਟਾ_ਸੈੱਟ_title, (ਬਣਤਰ libdecor_ਚੌਖਟਾ *, ਅਚਲ ਅੱਖਰ *))
SDL_WAYLAND_SYM(ਖਾਲੀ, libdecor_ਚੌਖਟਾ_ਸੈੱਟ_app_id, (ਬਣਤਰ libdecor_ਚੌਖਟਾ *, ਅਚਲ ਅੱਖਰ *))
SDL_WAYLAND_SYM(ਖਾਲੀ, libdecor_ਚੌਖਟਾ_ਸੈੱਟ_max_content_ਮਾਪ, (ਬਣਤਰ libdecor_ਚੌਖਟਾ *ਚੌਖਟਾ,\
                                                            ਪੂਰਨ content_ਚੌੜਾਈ,\
                                                            ਪੂਰਨ content_ਉਚਾਈ))
SDL_WAYLAND_SYM(ਖਾਲੀ, libdecor_ਚੌਖਟਾ_ਸੈੱਟ_min_content_ਮਾਪ, (ਬਣਤਰ libdecor_ਚੌਖਟਾ *ਚੌਖਟਾ,\
                                                            ਪੂਰਨ content_ਚੌੜਾਈ,\
                                                            ਪੂਰਨ content_ਉਚਾਈ))
SDL_WAYLAND_SYM(ਖਾਲੀ, libdecor_ਚੌਖਟਾ_resize, (ਬਣਤਰ libdecor_ਚੌਖਟਾ *,\
                                              ਬਣਤਰ wl_seat *,\
                                              uint32_t,\
                                              ਗਿਣਤੀ libdecor_resize_ਕਿਨਾਰਾ))
SDL_WAYLAND_SYM(ਖਾਲੀ, libdecor_ਚੌਖਟਾ_move, (ਬਣਤਰ libdecor_ਚੌਖਟਾ *,\
                                            ਬਣਤਰ wl_seat *,\
                                            uint32_t))
SDL_WAYLAND_SYM(ਖਾਲੀ, libdecor_ਚੌਖਟਾ_commit, (ਬਣਤਰ libdecor_ਚੌਖਟਾ *,\
                                              ਬਣਤਰ libdecor_state *,\
                                              ਬਣਤਰ libdecor_configuration *))
SDL_WAYLAND_SYM(ਖਾਲੀ, libdecor_ਚੌਖਟਾ_ਸੈੱਟ_minimized, (ਬਣਤਰ libdecor_ਚੌਖਟਾ *))
SDL_WAYLAND_SYM(ਖਾਲੀ, libdecor_ਚੌਖਟਾ_ਸੈੱਟ_maximized, (ਬਣਤਰ libdecor_ਚੌਖਟਾ *))
SDL_WAYLAND_SYM(ਖਾਲੀ, libdecor_ਚੌਖਟਾ_unset_maximized, (ਬਣਤਰ libdecor_ਚੌਖਟਾ *))
SDL_WAYLAND_SYM(ਖਾਲੀ, libdecor_ਚੌਖਟਾ_ਸੈੱਟ_fullscreen, (ਬਣਤਰ libdecor_ਚੌਖਟਾ *, ਬਣਤਰ wl_output *))
SDL_WAYLAND_SYM(ਖਾਲੀ, libdecor_ਚੌਖਟਾ_unset_fullscreen, (ਬਣਤਰ libdecor_ਚੌਖਟਾ *))
SDL_WAYLAND_SYM(ਖਾਲੀ, libdecor_ਚੌਖਟਾ_ਸੈੱਟ_capabilities, (ਬਣਤਰ libdecor_ਚੌਖਟਾ *, \
                                                        ਗਿਣਤੀ libdecor_capabilities))
SDL_WAYLAND_SYM(ਖਾਲੀ, libdecor_ਚੌਖਟਾ_unset_capabilities, (ਬਣਤਰ libdecor_ਚੌਖਟਾ *, \
                                                          ਗਿਣਤੀ libdecor_capabilities))
SDL_WAYLAND_SYM(bool, libdecor_ਚੌਖਟਾ_has_capability, (ਬਣਤਰ libdecor_ਚੌਖਟਾ *, \
                                                      ਗਿਣਤੀ libdecor_capabilities))
SDL_WAYLAND_SYM(ਖਾਲੀ, libdecor_ਚੌਖਟਾ_ਸੈੱਟ_visibility, (ਬਣਤਰ libdecor_ਚੌਖਟਾ *, bool))
SDL_WAYLAND_SYM(bool, libdecor_ਚੌਖਟਾ_is_visible, (ਬਣਤਰ libdecor_ਚੌਖਟਾ *))
SDL_WAYLAND_SYM(bool, libdecor_ਚੌਖਟਾ_is_floating, (ਬਣਤਰ libdecor_ਚੌਖਟਾ *))
SDL_WAYLAND_SYM(ਖਾਲੀ, libdecor_ਚੌਖਟਾ_ਸੈੱਟ_ਮਾਪਾ, (ਬਣਤਰ libdecor_ਚੌਖਟਾ *,\
                                                  ਬਣਤਰ libdecor_ਚੌਖਟਾ *))
SDL_WAYLAND_SYM(ਖਾਲੀ, libdecor_ਚੌਖਟਾ_show_ਖਿੜਕੀ_menu, (ਬਣਤਰ libdecor_ਚੌਖਟਾ *, ਬਣਤਰ wl_seat *, uint32_t, ਪੂਰਨ, ਪੂਰਨ))
SDL_WAYLAND_SYM(ਬਣਤਰ xdg_surface *, libdecor_ਚੌਖਟਾ_get_xdg_surface, (ਬਣਤਰ libdecor_ਚੌਖਟਾ *))
SDL_WAYLAND_SYM(ਬਣਤਰ xdg_toplevel *, libdecor_ਚੌਖਟਾ_get_xdg_toplevel, (ਬਣਤਰ libdecor_ਚੌਖਟਾ *))
SDL_WAYLAND_SYM(ਖਾਲੀ, libdecor_ਚੌਖਟਾ_translate_coordinate, (ਬਣਤਰ libdecor_ਚੌਖਟਾ *, ਪੂਰਨ, ਪੂਰਨ, ਪੂਰਨ *, ਪੂਰਨ *))
SDL_WAYLAND_SYM(ਖਾਲੀ, libdecor_ਚੌਖਟਾ_map, (ਬਣਤਰ libdecor_ਚੌਖਟਾ *))
SDL_WAYLAND_SYM(ਬਣਤਰ libdecor_state *, libdecor_state_new, (ਪੂਰਨ, ਪੂਰਨ))
SDL_WAYLAND_SYM(ਖਾਲੀ, libdecor_state_free, (ਬਣਤਰ libdecor_state *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_content_ਮਾਪ, (ਬਣਤਰ libdecor_configuration *,\
                                                                ਬਣਤਰ libdecor_ਚੌਖਟਾ *,\
                                                                ਪੂਰਨ *,\
                                                                ਪੂਰਨ *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_ਖਿੜਕੀ_state, (ਬਣਤਰ libdecor_configuration *,\
                                                                ਗਿਣਤੀ libdecor_ਖਿੜਕੀ_state *))
SDL_WAYLAND_SYM(ਪੂਰਨ, libdecor_dispatch, (ਬਣਤਰ libdecor *, ਪੂਰਨ))

#ਜੇ defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_ਸੰਸਕਰਣ(0, 2, 0)
// Only found in libdecor 0.1.1 or higher, so failure to load them is not fatal.
SDL_WAYLAND_SYM_OPT(ਖਾਲੀ, libdecor_ਚੌਖਟਾ_get_min_content_ਮਾਪ, (ਅਚਲ ਬਣਤਰ libdecor_ਚੌਖਟਾ *,\
                                                            ਪੂਰਨ *,\
                                                            ਪੂਰਨ *))
SDL_WAYLAND_SYM_OPT(ਖਾਲੀ, libdecor_ਚੌਖਟਾ_get_max_content_ਮਾਪ, (ਅਚਲ ਬਣਤਰ libdecor_ਚੌਖਟਾ *,\
                                                            ਪੂਰਨ *,\
                                                            ਪੂਰਨ *))
#ਜੇ_ਅੰਤ

#ਜੇ defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_ਸੰਸਕਰਣ(0, 3, 0)
SDL_WAYLAND_SYM_OPT(ਗਿਣਤੀ libdecor_wm_capabilities, libdecor_ਚੌਖਟਾ_get_wm_capabilities, (ਬਣਤਰ libdecor_ਚੌਖਟਾ *))
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ SDL_libdecor_constsince03

#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ SDL_WAYLAND_MODULE
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ SDL_WAYLAND_SYM
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ SDL_WAYLAND_SYM_OPT

/* *INDENT-ON* */ // clang-format on
