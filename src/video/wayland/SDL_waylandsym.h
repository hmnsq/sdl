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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_WAYLAND_MODULE
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_WAYLAND_MODULE(modname)
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_WAYLAND_SYM
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_WAYLAND_SYM(rc,fn,params)
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_WAYLAND_SYM_OPT
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_WAYLAND_SYM_OPT(rc,fn,params)
#ಆದರೆ_ಅಂತ್ಯ

SDL_WAYLAND_MODULE(WAYLAND_CLIENT)
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_proxy_marshal, (ರಚನೆ wl_proxy *, uint32_t, ...))
SDL_WAYLAND_SYM(ರಚನೆ wl_proxy *, wl_proxy_create, (ರಚನೆ wl_proxy *, ಸ್ಥಿರಾಂಕ ರಚನೆ wl_interface *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_proxy_destroy, (ರಚನೆ wl_proxy *))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಂಕ, wl_proxy_ಕೂಡಿಸು_listener, (ರಚನೆ wl_proxy *, ಶೂನ್ಯ (**)(ಶೂನ್ಯ), ಶೂನ್ಯ *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_proxy_ಗಣ_user_ದತ್ತಾಂಶ, (ರಚನೆ wl_proxy *, ಶೂನ್ಯ *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ *, wl_proxy_get_user_ದತ್ತಾಂಶ, (ರಚನೆ wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_ಆವೃತ್ತಿ, (ರಚನೆ wl_proxy *))
SDL_WAYLAND_SYM(uint32_t, wl_proxy_get_id, (ರಚನೆ wl_proxy *))
SDL_WAYLAND_SYM(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, wl_proxy_get_class, (ರಚನೆ wl_proxy *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_proxy_ಗಣ_ಸರತಿ, (ರಚನೆ wl_proxy *, ರಚನೆ wl_event_ಸರತಿ *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ *, wl_proxy_create_wrapper, (ಶೂನ್ಯ *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_proxy_wrapper_destroy, (ಶೂನ್ಯ *))
SDL_WAYLAND_SYM(ರಚನೆ wl_display *, wl_display_connect, (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *))
SDL_WAYLAND_SYM(ರಚನೆ wl_display *, wl_display_connect_ಗಮ್ಯ_fd, (ಪೂರ್ಣಾಂಕ))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_display_disconnect, (ರಚನೆ wl_display *))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಂಕ, wl_display_get_fd, (ರಚನೆ wl_display *))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಂಕ, wl_display_dispatch, (ರಚನೆ wl_display *))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಂಕ, wl_display_dispatch_ಸರತಿ, (ರಚನೆ wl_display *, ರಚನೆ wl_event_ಸರತಿ *))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಂಕ, wl_display_dispatch_ಸರತಿ_pending, (ರಚನೆ wl_display *, ರಚನೆ wl_event_ಸರತಿ *))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಂಕ, wl_display_dispatch_pending, (ರಚನೆ wl_display *))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಂಕ, wl_display_prepare_read, (ರಚನೆ wl_display *))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಂಕ, wl_display_prepare_read_ಸರತಿ, (ರಚನೆ wl_display *, ರಚನೆ wl_event_ಸರತಿ *))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಂಕ, wl_display_read_events, (ರಚನೆ wl_display *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_display_cancel_read, (ರಚನೆ wl_display *))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಂಕ, wl_display_get_error, (ರಚನೆ wl_display *))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಂಕ, wl_display_flush, (ರಚನೆ wl_display *))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಂಕ, wl_display_roundtrip, (ರಚನೆ wl_display *))
SDL_WAYLAND_SYM(ರಚನೆ wl_event_ಸರತಿ *, wl_display_create_ಸರತಿ, (ರಚನೆ wl_display *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_event_ಸರತಿ_destroy, (ರಚನೆ wl_event_ಸರತಿ *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_log_ಗಣ_handler_client, (wl_log_func_t))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_list_init, (ರಚನೆ wl_list *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_list_ಸೇರಿಸು, (ರಚನೆ wl_list *, ರಚನೆ wl_list *) )
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_list_remove, (ರಚನೆ wl_list *))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಂಕ, wl_list_ಉದ್ದಳತೆ, (ಸ್ಥಿರಾಂಕ ರಚನೆ wl_list *))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಂಕ, wl_list_ಖಾಲಿಗಳು, (ಸ್ಥಿರಾಂಕ ರಚನೆ wl_list *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_list_ಸೇರಿಸು_list, (ರಚನೆ wl_list *, ರಚನೆ wl_list *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_array_init, (ರಚನೆ wl_array *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_array_release, (ರಚನೆ wl_array *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ *, wl_array_ಕೂಡಿಸು, (ರಚನೆ wl_array *, size_t))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಂಕ, wl_array_copy, (ರಚನೆ wl_array *, ರಚನೆ wl_array *))
SDL_WAYLAND_SYM(ರಚನೆ wl_proxy *, wl_proxy_marshal_constructor, (ರಚನೆ wl_proxy *, uint32_t opcode, ಸ್ಥಿರಾಂಕ ರಚನೆ wl_interface *interface, ...))
SDL_WAYLAND_SYM(ರಚನೆ wl_proxy *, wl_proxy_marshal_constructor_versioned, (ರಚನೆ wl_proxy *proxy, uint32_t opcode, ಸ್ಥಿರಾಂಕ ರಚನೆ wl_interface *interface, uint32_t ಆವೃತ್ತಿ, ...))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_proxy_ಗಣ_ಟ್ಯಾಗ್, (ರಚನೆ wl_proxy *, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ *))
SDL_WAYLAND_SYM(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ *, wl_proxy_get_ಟ್ಯಾಗ್, (ರಚನೆ wl_proxy *))

#ಆದರೆ SDL_WAYLAND_CHECK_ಆವೃತ್ತಿ(1, 20, 0)
/* wayland-scanner 1.20 generates code that will call these, so these are
 * non-optional when we are compiling against Wayland 1.20. We don't
 * explicitly call them ourselves, though, so if we are only compiling
 * against Wayland 1.18, they're unnecessary. */
SDL_WAYLAND_SYM(ರಚನೆ wl_proxy *, wl_proxy_marshal_flags, (ರಚನೆ wl_proxy *proxy, uint32_t opcode, ಸ್ಥಿರಾಂಕ ರಚನೆ wl_interface *interface, uint32_t ಆವೃತ್ತಿ, uint32_t flags, ...))
SDL_WAYLAND_SYM(ರಚನೆ wl_proxy *, wl_proxy_marshal_array_flags, (ರಚನೆ wl_proxy *proxy, uint32_t opcode, ಸ್ಥಿರಾಂಕ ರಚನೆ wl_interface *interface, uint32_t ಆವೃತ್ತಿ,  uint32_t flags, ಒಕ್ಕೂಟ wl_ವಾದ *ವಾದಗಳು))
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ SDL_WAYLAND_CHECK_ಆವೃತ್ತಿ(1, 23, 0) || defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC)
SDL_WAYLAND_SYM_OPT(ರಚನೆ wl_event_ಸರತಿ *, wl_display_create_ಸರತಿ_with_name, (ರಚನೆ wl_display *display, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name))
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ 0 // TODO RECONNECT: See waylandvideo.c for more information!
#ಆದರೆ SDL_WAYLAND_CHECK_ಆವೃತ್ತಿ(broken, on, purpose)
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಂಕ, wl_display_reconnect, (ರಚನೆ wl_display *))
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ // 0

SDL_WAYLAND_MODULE(WAYLAND_EGL)
SDL_WAYLAND_SYM(ರಚನೆ wl_egl_ಕಿಟಕಿ *, wl_egl_ಕಿಟಕಿ_create, (ರಚನೆ wl_surface *, ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_egl_ಕಿಟಕಿ_destroy, (ರಚನೆ wl_egl_ಕಿಟಕಿ *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_egl_ಕಿಟಕಿ_resize, (ರಚನೆ wl_egl_ಕಿಟಕಿ *, ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_egl_ಕಿಟಕಿ_get_attached_ಗಾತ್ರ, (ರಚನೆ wl_egl_ಕಿಟಕಿ *, ಪೂರ್ಣಾಂಕ *, ಪೂರ್ಣಾಂಕ *))

SDL_WAYLAND_MODULE(WAYLAND_CURSOR)
SDL_WAYLAND_SYM(ರಚನೆ wl_cursor_theme *, wl_cursor_theme_ತುಂಬು, (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, ಪೂರ್ಣಾಂಕ , ರಚನೆ wl_shm *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, wl_cursor_theme_destroy, (ರಚನೆ wl_cursor_theme *))
SDL_WAYLAND_SYM(ರಚನೆ wl_cursor *, wl_cursor_theme_get_cursor, (ರಚನೆ wl_cursor_theme *, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *))
SDL_WAYLAND_SYM(ರಚನೆ wl_ಬಫರ್ *, wl_cursor_image_get_ಬಫರ್, (ರಚನೆ wl_cursor_image *))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಂಕ, wl_cursor_ಚೌಕಟ್ಟು, (ರಚನೆ wl_cursor *, uint32_t))

SDL_WAYLAND_MODULE(WAYLAND_XKB)
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಂಕ, xkb_state_ಕೀಲಿ_get_syms, (ರಚನೆ xkb_state *, xkb_keycode_t, ಸ್ಥಿರಾಂಕ xkb_keysym_t **))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಂಕ, xkb_keysym_ಗಮ್ಯ_utf8, (xkb_keysym_t, ಅಕ್ಷರ *, size_t) )
SDL_WAYLAND_SYM(ರಚನೆ xkb_keymap *, xkb_keymap_new_from_string, (ರಚನೆ xkb_context *, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, ಎಣಿಕೆ xkb_keymap_format, ಎಣಿಕೆ xkb_keymap_compile_flags))
SDL_WAYLAND_SYM(ರಚನೆ xkb_state *, xkb_state_new, (ರಚನೆ xkb_keymap *) )
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಂಕ, xkb_keymap_ಕೀಲಿ_repeats, (ರಚನೆ xkb_keymap *keymap, xkb_keycode_t ಕೀಲಿ) )
SDL_WAYLAND_SYM(ಶೂನ್ಯ, xkb_keymap_unref, (ರಚನೆ xkb_keymap *) )
SDL_WAYLAND_SYM(ಶೂನ್ಯ, xkb_state_unref, (ರಚನೆ xkb_state *) )
SDL_WAYLAND_SYM(ಶೂನ್ಯ, xkb_context_unref, (ರಚನೆ xkb_context *) )
SDL_WAYLAND_SYM(ರಚನೆ xkb_context *, xkb_context_new, (ಎಣಿಕೆ xkb_context_flags flags) )
SDL_WAYLAND_SYM(ಎಣಿಕೆ xkb_state_component, xkb_state_update_ಮುಖವಾಡ, (ರಚನೆ xkb_state *state,\
                      xkb_mod_ಮುಖವಾಡ_t depressed_mods,\
                      xkb_mod_ಮುಖವಾಡ_t latched_mods,\
                      xkb_mod_ಮುಖವಾಡ_t locked_mods,\
                      xkb_layout_ಸೂಚ್ಯಂಕ_t depressed_layout,\
                      xkb_layout_ಸೂಚ್ಯಂಕ_t latched_layout,\
                      xkb_layout_ಸೂಚ್ಯಂಕ_t locked_layout) )
SDL_WAYLAND_SYM(ರಚನೆ xkb_compose_ಕೋಷ್ಟಕ *, xkb_compose_ಕೋಷ್ಟಕ_new_from_locale, (ರಚನೆ xkb_context *,\
                      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *locale, ಎಣಿಕೆ xkb_compose_compile_flags) )
SDL_WAYLAND_SYM(ಶೂನ್ಯ, xkb_compose_state_reset, (ರಚನೆ xkb_compose_state *) )
SDL_WAYLAND_SYM(ಶೂನ್ಯ, xkb_compose_ಕೋಷ್ಟಕ_unref, (ರಚನೆ xkb_compose_ಕೋಷ್ಟಕ *) )
SDL_WAYLAND_SYM(ರಚನೆ xkb_compose_state *, xkb_compose_state_new, (ರಚನೆ xkb_compose_ಕೋಷ್ಟಕ *, ಎಣಿಕೆ xkb_compose_state_flags) )
SDL_WAYLAND_SYM(ಶೂನ್ಯ, xkb_compose_state_unref, (ರಚನೆ xkb_compose_state *) )
SDL_WAYLAND_SYM(ಎಣಿಕೆ xkb_compose_feed_ಫಲಿತಾಂಶ, xkb_compose_state_feed, (ರಚನೆ xkb_compose_state *, xkb_keysym_t) )
SDL_WAYLAND_SYM(ಎಣಿಕೆ xkb_compose_ಸ್ಥಿತಿ, xkb_compose_state_get_ಸ್ಥಿತಿ, (ರಚನೆ xkb_compose_state *) )
SDL_WAYLAND_SYM(xkb_keysym_t, xkb_compose_state_get_one_sym, (ರಚನೆ xkb_compose_state *) )
SDL_WAYLAND_SYM(ಶೂನ್ಯ, xkb_keymap_ಕೀಲಿ_for_each, (ರಚನೆ xkb_keymap *, xkb_keymap_ಕೀಲಿ_iter_t, ಶೂನ್ಯ *) )
SDL_WAYLAND_SYM(xkb_layout_ಸೂಚ್ಯಂಕ_t, xkb_keymap_ಅಂಕೆ_layouts, (ರಚನೆ xkb_keymap *) )
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಂಕ, xkb_keymap_ಕೀಲಿ_get_syms_by_level, (ರಚನೆ xkb_keymap *, xkb_keycode_t, xkb_layout_ಸೂಚ್ಯಂಕ_t, xkb_level_ಸೂಚ್ಯಂಕ_t, ಸ್ಥಿರಾಂಕ xkb_keysym_t **) )
SDL_WAYLAND_SYM(xkb_level_ಸೂಚ್ಯಂಕ_t, xkb_keymap_ಅಂಕೆ_ಮಟ್ಟಗಳು_for_ಕೀಲಿ, (ರಚನೆ xkb_keymap *, xkb_keycode_t, xkb_layout_ಸೂಚ್ಯಂಕ_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keysym_ಗಮ್ಯ_utf32, (xkb_keysym_t) )
SDL_WAYLAND_SYM(uint32_t, xkb_keymap_mod_get_ಸೂಚ್ಯಂಕ, (ರಚನೆ xkb_keymap *, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *) )
SDL_WAYLAND_SYM(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, xkb_keymap_layout_get_name, (ರಚನೆ xkb_keymap *, xkb_layout_ಸೂಚ್ಯಂಕ_t))

#ಆದರೆ SDL_XKBCOMMON_CHECK_ಆವೃತ್ತಿ(1, 0, 0)
SDL_WAYLAND_SYM(size_t, xkb_keymap_ಕೀಲಿ_get_mods_for_level, (ರಚನೆ xkb_keymap *, xkb_keycode_t, xkb_layout_ಸೂಚ್ಯಂಕ_t, xkb_level_ಸೂಚ್ಯಂಕ_t, xkb_mod_ಮುಖವಾಡ_t *, size_t) )
#ಇಲ್ಲದಿದ್ದರೆ
// Only needed in the fallback replacement for xkb_keymap_key_get_mods_for_level().
SDL_WAYLAND_SYM(xkb_level_ಸೂಚ್ಯಂಕ_t, xkb_state_ಕೀಲಿ_get_level, (ರಚನೆ xkb_state *, xkb_keycode_t, xkb_layout_ಸೂಚ್ಯಂಕ_t) )
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ SDL_XKBCOMMON_CHECK_ಆವೃತ್ತಿ(1, 10, 0)
SDL_WAYLAND_SYM(xkb_mod_ಮುಖವಾಡ_t, xkb_keymap_mod_get_ಮುಖವಾಡ, (ರಚನೆ xkb_keymap *, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *))
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
SDL_WAYLAND_MODULE(WAYLAND_LIBDECOR)

#ಆದರೆ defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_ಆವೃತ್ತಿ(0, 3, 0)
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_libdecor_constsince03 ಸ್ಥಿರಾಂಕ
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_libdecor_constsince03 /* nothing */
#ಆದರೆ_ಅಂತ್ಯ

SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_unref, (ರಚನೆ libdecor *))
SDL_WAYLAND_SYM(ರಚನೆ libdecor *, libdecor_new, (ರಚನೆ wl_display *,\
                                                  SDL_libdecor_constsince03 ರಚನೆ libdecor_interface *))
SDL_WAYLAND_SYM(ರಚನೆ libdecor_ಚೌಕಟ್ಟು *, libdecor_decorate, (ರಚನೆ libdecor *,\
                                                             ರಚನೆ wl_surface *,\
                                                             SDL_libdecor_constsince03 ರಚನೆ libdecor_ಚೌಕಟ್ಟು_interface *,\
                                                             ಶೂನ್ಯ *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_ಚೌಕಟ್ಟು_unref, (ರಚನೆ libdecor_ಚೌಕಟ್ಟು *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_ಚೌಕಟ್ಟು_ಗಣ_title, (ರಚನೆ libdecor_ಚೌಕಟ್ಟು *, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_ಚೌಕಟ್ಟು_ಗಣ_app_id, (ರಚನೆ libdecor_ಚೌಕಟ್ಟು *, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_ಚೌಕಟ್ಟು_ಗಣ_max_content_ಗಾತ್ರ, (ರಚನೆ libdecor_ಚೌಕಟ್ಟು *ಚೌಕಟ್ಟು,\
                                                            ಪೂರ್ಣಾಂಕ content_ಅಗಲ,\
                                                            ಪೂರ್ಣಾಂಕ content_ಎತ್ತರ))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_ಚೌಕಟ್ಟು_ಗಣ_min_content_ಗಾತ್ರ, (ರಚನೆ libdecor_ಚೌಕಟ್ಟು *ಚೌಕಟ್ಟು,\
                                                            ಪೂರ್ಣಾಂಕ content_ಅಗಲ,\
                                                            ಪೂರ್ಣಾಂಕ content_ಎತ್ತರ))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_ಚೌಕಟ್ಟು_resize, (ರಚನೆ libdecor_ಚೌಕಟ್ಟು *,\
                                              ರಚನೆ wl_seat *,\
                                              uint32_t,\
                                              ಎಣಿಕೆ libdecor_resize_ಅಂಚು))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_ಚೌಕಟ್ಟು_move, (ರಚನೆ libdecor_ಚೌಕಟ್ಟು *,\
                                            ರಚನೆ wl_seat *,\
                                            uint32_t))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_ಚೌಕಟ್ಟು_commit, (ರಚನೆ libdecor_ಚೌಕಟ್ಟು *,\
                                              ರಚನೆ libdecor_state *,\
                                              ರಚನೆ libdecor_configuration *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_ಚೌಕಟ್ಟು_ಗಣ_minimized, (ರಚನೆ libdecor_ಚೌಕಟ್ಟು *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_ಚೌಕಟ್ಟು_ಗಣ_maximized, (ರಚನೆ libdecor_ಚೌಕಟ್ಟು *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_ಚೌಕಟ್ಟು_unset_maximized, (ರಚನೆ libdecor_ಚೌಕಟ್ಟು *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_ಚೌಕಟ್ಟು_ಗಣ_fullscreen, (ರಚನೆ libdecor_ಚೌಕಟ್ಟು *, ರಚನೆ wl_output *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_ಚೌಕಟ್ಟು_unset_fullscreen, (ರಚನೆ libdecor_ಚೌಕಟ್ಟು *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_ಚೌಕಟ್ಟು_ಗಣ_capabilities, (ರಚನೆ libdecor_ಚೌಕಟ್ಟು *, \
                                                        ಎಣಿಕೆ libdecor_capabilities))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_ಚೌಕಟ್ಟು_unset_capabilities, (ರಚನೆ libdecor_ಚೌಕಟ್ಟು *, \
                                                          ಎಣಿಕೆ libdecor_capabilities))
SDL_WAYLAND_SYM(bool, libdecor_ಚೌಕಟ್ಟು_has_capability, (ರಚನೆ libdecor_ಚೌಕಟ್ಟು *, \
                                                      ಎಣಿಕೆ libdecor_capabilities))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_ಚೌಕಟ್ಟು_ಗಣ_visibility, (ರಚನೆ libdecor_ಚೌಕಟ್ಟು *, bool))
SDL_WAYLAND_SYM(bool, libdecor_ಚೌಕಟ್ಟು_is_visible, (ರಚನೆ libdecor_ಚೌಕಟ್ಟು *))
SDL_WAYLAND_SYM(bool, libdecor_ಚೌಕಟ್ಟು_is_floating, (ರಚನೆ libdecor_ಚೌಕಟ್ಟು *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_ಚೌಕಟ್ಟು_ಗಣ_ಪೋಷಕ, (ರಚನೆ libdecor_ಚೌಕಟ್ಟು *,\
                                                  ರಚನೆ libdecor_ಚೌಕಟ್ಟು *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_ಚೌಕಟ್ಟು_show_ಕಿಟಕಿ_menu, (ರಚನೆ libdecor_ಚೌಕಟ್ಟು *, ರಚನೆ wl_seat *, uint32_t, ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ))
SDL_WAYLAND_SYM(ರಚನೆ xdg_surface *, libdecor_ಚೌಕಟ್ಟು_get_xdg_surface, (ರಚನೆ libdecor_ಚೌಕಟ್ಟು *))
SDL_WAYLAND_SYM(ರಚನೆ xdg_toplevel *, libdecor_ಚೌಕಟ್ಟು_get_xdg_toplevel, (ರಚನೆ libdecor_ಚೌಕಟ್ಟು *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_ಚೌಕಟ್ಟು_translate_coordinate, (ರಚನೆ libdecor_ಚೌಕಟ್ಟು *, ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ *, ಪೂರ್ಣಾಂಕ *))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_ಚೌಕಟ್ಟು_map, (ರಚನೆ libdecor_ಚೌಕಟ್ಟು *))
SDL_WAYLAND_SYM(ರಚನೆ libdecor_state *, libdecor_state_new, (ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ))
SDL_WAYLAND_SYM(ಶೂನ್ಯ, libdecor_state_free, (ರಚನೆ libdecor_state *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_content_ಗಾತ್ರ, (ರಚನೆ libdecor_configuration *,\
                                                                ರಚನೆ libdecor_ಚೌಕಟ್ಟು *,\
                                                                ಪೂರ್ಣಾಂಕ *,\
                                                                ಪೂರ್ಣಾಂಕ *))
SDL_WAYLAND_SYM(bool, libdecor_configuration_get_ಕಿಟಕಿ_state, (ರಚನೆ libdecor_configuration *,\
                                                                ಎಣಿಕೆ libdecor_ಕಿಟಕಿ_state *))
SDL_WAYLAND_SYM(ಪೂರ್ಣಾಂಕ, libdecor_dispatch, (ರಚನೆ libdecor *, ಪೂರ್ಣಾಂಕ))

#ಆದರೆ defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_ಆವೃತ್ತಿ(0, 2, 0)
// Only found in libdecor 0.1.1 or higher, so failure to load them is not fatal.
SDL_WAYLAND_SYM_OPT(ಶೂನ್ಯ, libdecor_ಚೌಕಟ್ಟು_get_min_content_ಗಾತ್ರ, (ಸ್ಥಿರಾಂಕ ರಚನೆ libdecor_ಚೌಕಟ್ಟು *,\
                                                            ಪೂರ್ಣಾಂಕ *,\
                                                            ಪೂರ್ಣಾಂಕ *))
SDL_WAYLAND_SYM_OPT(ಶೂನ್ಯ, libdecor_ಚೌಕಟ್ಟು_get_max_content_ಗಾತ್ರ, (ಸ್ಥಿರಾಂಕ ರಚನೆ libdecor_ಚೌಕಟ್ಟು *,\
                                                            ಪೂರ್ಣಾಂಕ *,\
                                                            ಪೂರ್ಣಾಂಕ *))
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ defined(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR) || SDL_LIBDECOR_CHECK_ಆವೃತ್ತಿ(0, 3, 0)
SDL_WAYLAND_SYM_OPT(ಎಣಿಕೆ libdecor_wm_capabilities, libdecor_ಚೌಕಟ್ಟು_get_wm_capabilities, (ರಚನೆ libdecor_ಚೌಕಟ್ಟು *))
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು SDL_libdecor_constsince03

#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು SDL_WAYLAND_MODULE
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು SDL_WAYLAND_SYM
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು SDL_WAYLAND_SYM_OPT

/* *INDENT-ON* */ // clang-format on
