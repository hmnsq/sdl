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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WAYLAND

#ਅਨ੍ਤਰ੍ਭਾਵ <errno.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_video_c.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/unix/SDL_poll.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_pixels_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandevents_c.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "wayland-cursor.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandmouse.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandshmbuffer.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "cursor-shape-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pointer-constraints-unstable-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "viewporter-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pointer-warp-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "tablet-v2-client-protocol.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "../../SDL_hints_c.h"

ਸਥਿਰ SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_ਖੱਬਾ + 1];

ਸਥਿਰ bool Wayland_ਸੈੱਟ_Relative_Mouse_ਬਹੁਲਕ(bool enabled);

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    ਪੂਰਨ ਚੌੜਾਈ;
    ਪੂਰਨ ਉਚਾਈ;
    ਬਣਤਰ wl_ਬਫਰ *ਬਫਰ_2;
} CustomCursorImage;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    // The base dimensions of the cursor.
    ਪੂਰਨ ਚੌੜਾਈ;
    ਪੂਰਨ ਉਚਾਈ;
    ਪੂਰਨ hot_x;
    ਪੂਰਨ hot_y;

    ਪੂਰਨ images_ਪ੍ਰਤੀ_ਚੌਖਟਾ;
    CustomCursorImage images[];
} Wayland_CustomCursor;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    ਪੂਰਨ ਮਾਪ;
    ਬਣਤਰ wl_list ਗੰਢ;
    ਬਣਤਰ wl_ਬਫਰ *buffers[];
} Wayland_CachedSystemCursor;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    SDL_SystemCursor id;
    ਬਣਤਰ wl_list cursor_ਬਫਰ_cache;
} Wayland_SystemCursor;

ਬਣਤਰ SDL_Cursor_ਅੰਕੜੇ
{
    // Cursor animation data.
    Uint32 *ਚੌਖਟਾ_durations_ms;
    Uint32 ਕੁੱਲ_duration_ms;
    ਪੂਰਨ ਅੰਕ_ਚੌਖਟੇ;
    bool is_system_cursor;

    ਸੰਘ
    {
        Wayland_CustomCursor custom;
        Wayland_SystemCursor system;
    } cursor_ਅੰਕੜੇ;
};

ਸਥਿਰ ਪੂਰਨ dbus_cursor_ਮਾਪ;
ਸਥਿਰ ਅੱਖਰ *dbus_cursor_theme;

ਸਥਿਰ ਖਾਲੀ Wayland_FreeCursorThemes(SDL_Video_ਅੰਕੜੇ *vdata)
{
    ਲਈ (ਪੂਰਨ i = 0; i < vdata->ਅੰਕ_cursor_themes; i += 1) {
        WAYLAND_wl_cursor_theme_destroy(vdata->cursor_themes[i].theme);
    }
    vdata->ਅੰਕ_cursor_themes = 0;
    SDL_free(vdata->cursor_themes);
    vdata->cursor_themes = ਨਿਰਾ;
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_USE_LIBDBUS

#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/linux/SDL_dbus.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CURSOR_ਗੰਢ        "org.freedesktop.portal.Desktop"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CURSOR_ਰਸਤਾ        "/org/freedesktop/portal/desktop"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CURSOR_INTERFACE   "org.freedesktop.portal.Settings"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CURSOR_NAMESPACE   "org.gnome.desktop.interface"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CURSOR_SIGNAL_NAME "SettingChanged"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CURSOR_ਮਾਪ_ਕੁੰਜੀ    "cursor-size"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CURSOR_THEME_ਕੁੰਜੀ   "cursor-theme"

ਸਥਿਰ DBus_ਸੁਨੇਹਾ *Wayland_ReadDBusProperty(SDL_DBusContext *dbus, ਅਚਲ ਅੱਖਰ *ਕੁੰਜੀ)
{
    ਸਥਿਰ ਅਚਲ ਅੱਖਰ *iface = "org.gnome.desktop.interface";

    DBus_ਸੁਨੇਹਾ *ਜਵਾਬ = ਨਿਰਾ;
    DBus_ਸੁਨੇਹਾ *ਸੁਨੇਹਾ_2 = dbus->ਸੁਨੇਹਾ_new_ਵਿਧੀ_call(CURSOR_ਗੰਢ,
                                                     CURSOR_ਰਸਤਾ,
                                                     CURSOR_INTERFACE,
                                                     "Read"); //ਵਿਧੀ

    ਜੇ (ਸੁਨੇਹਾ_2) {
        ਜੇ (dbus->ਸੁਨੇਹਾ_append_ਦਲੀਲਾਂ(ਸੁਨੇਹਾ_2, DBUS_TYPE_STRING, &iface, DBUS_TYPE_STRING, &ਕੁੰਜੀ, DBUS_TYPE_INVALID)) {
            ਜਵਾਬ = dbus->connection_send_with_ਜਵਾਬ_and_ਖੰਡ(dbus->session_conn, ਸੁਨੇਹਾ_2, DBUS_TIMEOUT_USE_DEFAULT, ਨਿਰਾ);
        }
        dbus->ਸੁਨੇਹਾ_unref(ਸੁਨੇਹਾ_2);
    }

    ਵਾਪਸ ਜਵਾਬ;
}

ਸਥਿਰ bool Wayland_Parse_DBus_ਜਵਾਬ(SDL_DBusContext *dbus, DBus_ਸੁਨੇਹਾ *ਜਵਾਬ, ਪੂਰਨ type, ਖਾਲੀ *ਮੁੱਲ)
{
    DBus_ਸੁਨੇਹਾ_Iter iter[3];

    dbus->ਸੁਨੇਹਾ_iter_init(ਜਵਾਬ, &iter[0]);
    ਜੇ (dbus->ਸੁਨੇਹਾ_iter_get_arg_type(&iter[0]) != DBUS_TYPE_VARIANT) {
        ਵਾਪਸ false;
    }

    dbus->ਸੁਨੇਹਾ_iter_recurse(&iter[0], &iter[1]);
    ਜੇ (dbus->ਸੁਨੇਹਾ_iter_get_arg_type(&iter[1]) != DBUS_TYPE_VARIANT) {
        ਵਾਪਸ false;
    }

    dbus->ਸੁਨੇਹਾ_iter_recurse(&iter[1], &iter[2]);
    ਜੇ (dbus->ਸੁਨੇਹਾ_iter_get_arg_type(&iter[2]) != type) {
        ਵਾਪਸ false;
    }

    dbus->ਸੁਨੇਹਾ_iter_get_basic(&iter[2], ਮੁੱਲ);

    ਵਾਪਸ true;
}

ਸਥਿਰ DBus_Handler_ਨਤੀਜਾ Wayland_DBus_Cursor_ਸੁਨੇਹਾ_Filter(DBusConnection *conn, DBus_ਸੁਨੇਹਾ *ਸੁਨੇਹਾ_2, ਖਾਲੀ *ਅੰਕੜੇ)
{
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    SDL_Video_ਅੰਕੜੇ *vdata = (SDL_Video_ਅੰਕੜੇ *)ਅੰਕੜੇ;

    ਜੇ (dbus->ਸੁਨੇਹਾ_is_signal(ਸੁਨੇਹਾ_2, CURSOR_INTERFACE, CURSOR_SIGNAL_NAME)) {
        DBus_ਸੁਨੇਹਾ_Iter signal_iter, variant_iter;
        ਅਚਲ ਅੱਖਰ *namespace, *ਕੁੰਜੀ;

        dbus->ਸੁਨੇਹਾ_iter_init(ਸੁਨੇਹਾ_2, &signal_iter);
        // Check if the parameters are what we expect
        ਜੇ (dbus->ਸੁਨੇਹਾ_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            ਜਾਓ not_our_signal;
        }
        dbus->ਸੁਨੇਹਾ_iter_get_basic(&signal_iter, &namespace);
        ਜੇ (SDL_strcmp(CURSOR_NAMESPACE, namespace) != 0) {
            ਜਾਓ not_our_signal;
        }
        ਜੇ (!dbus->ਸੁਨੇਹਾ_iter_ਅਗਲਾ(&signal_iter)) {
            ਜਾਓ not_our_signal;
        }
        ਜੇ (dbus->ਸੁਨੇਹਾ_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            ਜਾਓ not_our_signal;
        }
        dbus->ਸੁਨੇਹਾ_iter_get_basic(&signal_iter, &ਕੁੰਜੀ);
        ਜੇ (SDL_strcmp(CURSOR_ਮਾਪ_ਕੁੰਜੀ, ਕੁੰਜੀ) == 0) {
            ਪੂਰਨ new_cursor_ਮਾਪ;

            ਜੇ (!dbus->ਸੁਨੇਹਾ_iter_ਅਗਲਾ(&signal_iter)) {
                ਜਾਓ not_our_signal;
            }
            ਜੇ (dbus->ਸੁਨੇਹਾ_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                ਜਾਓ not_our_signal;
            }
            dbus->ਸੁਨੇਹਾ_iter_recurse(&signal_iter, &variant_iter);
            ਜੇ (dbus->ਸੁਨੇਹਾ_iter_get_arg_type(&variant_iter) != DBUS_TYPE_INT32) {
                ਜਾਓ not_our_signal;
            }
            dbus->ਸੁਨੇਹਾ_iter_get_basic(&variant_iter, &new_cursor_ਮਾਪ);

            ਜੇ (dbus_cursor_ਮਾਪ != new_cursor_ਮਾਪ) {
                dbus_cursor_ਮਾਪ = new_cursor_ਮਾਪ;
                SDL_RedrawCursor(); // Force cursor update
            }
        } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(CURSOR_THEME_ਕੁੰਜੀ, ਕੁੰਜੀ) == 0) {
            ਅਚਲ ਅੱਖਰ *new_cursor_theme = ਨਿਰਾ;

            ਜੇ (!dbus->ਸੁਨੇਹਾ_iter_ਅਗਲਾ(&signal_iter)) {
                ਜਾਓ not_our_signal;
            }
            ਜੇ (dbus->ਸੁਨੇਹਾ_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                ਜਾਓ not_our_signal;
            }
            dbus->ਸੁਨੇਹਾ_iter_recurse(&signal_iter, &variant_iter);
            ਜੇ (dbus->ਸੁਨੇਹਾ_iter_get_arg_type(&variant_iter) != DBUS_TYPE_STRING) {
                ਜਾਓ not_our_signal;
            }
            dbus->ਸੁਨੇਹਾ_iter_get_basic(&variant_iter, &new_cursor_theme);

            ਜੇ (!dbus_cursor_theme || !new_cursor_theme || SDL_strcmp(dbus_cursor_theme, new_cursor_theme) != 0) {
                SDL_free(dbus_cursor_theme);
                ਜੇ (new_cursor_theme) {
                    dbus_cursor_theme = SDL_strdup(new_cursor_theme);
                } ਨਹੀਂਤਾਂ {
                    dbus_cursor_theme = ਨਿਰਾ;
                }

                // Purge the current cached themes and force a cursor refresh.
                Wayland_FreeCursorThemes(vdata);
                SDL_RedrawCursor();
            }
        } ਨਹੀਂਤਾਂ {
            ਜਾਓ not_our_signal;
        }

        ਵਾਪਸ DBUS_HANDLER_ਨਤੀਜਾ_HANDLED;
    }

not_our_signal:
    ਵਾਪਸ DBUS_HANDLER_ਨਤੀਜਾ_NOT_YET_HANDLED;
}

ਸਥਿਰ ਖਾਲੀ Wayland_DBusInitCursorProperties(SDL_Video_ਅੰਕੜੇ *vdata)
{
    DBus_ਸੁਨੇਹਾ *ਜਵਾਬ;
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    bool ਜੋੜੋ_filter = false;

    ਜੇ (!dbus) {
        ਵਾਪਸ;
    }

    ਜੇ ((ਜਵਾਬ = Wayland_ReadDBusProperty(dbus, CURSOR_ਮਾਪ_ਕੁੰਜੀ))) {
        ਜੇ (Wayland_Parse_DBus_ਜਵਾਬ(dbus, ਜਵਾਬ, DBUS_TYPE_INT32, &dbus_cursor_ਮਾਪ)) {
            ਜੋੜੋ_filter = true;
        }
        dbus->ਸੁਨੇਹਾ_unref(ਜਵਾਬ);
    }

    ਜੇ ((ਜਵਾਬ = Wayland_ReadDBusProperty(dbus, CURSOR_THEME_ਕੁੰਜੀ))) {
        ਅਚਲ ਅੱਖਰ *ਆਰਜ਼ੀ = ਨਿਰਾ;
        ਜੇ (Wayland_Parse_DBus_ਜਵਾਬ(dbus, ਜਵਾਬ, DBUS_TYPE_STRING, &ਆਰਜ਼ੀ)) {
            ਜੋੜੋ_filter = true;

            ਜੇ (ਆਰਜ਼ੀ) {
                dbus_cursor_theme = SDL_strdup(ਆਰਜ਼ੀ);
            }
        }
        dbus->ਸੁਨੇਹਾ_unref(ਜਵਾਬ);
    }

    // Only add the filter if at least one of the settings we want is present.
    ਜੇ (ਜੋੜੋ_filter) {
        dbus->bus_ਜੋੜੋ_ਮੇਲ(dbus->session_conn,
                            "type='signal', interface='" CURSOR_INTERFACE "',"
                            "member='" CURSOR_SIGNAL_NAME "', arg0='" CURSOR_NAMESPACE "'",
                            ਨਿਰਾ);
        dbus->connection_ਜੋੜੋ_filter(dbus->session_conn, &Wayland_DBus_Cursor_ਸੁਨੇਹਾ_Filter, vdata, ਨਿਰਾ);
        dbus->connection_flush(dbus->session_conn);
    }
}

ਸਥਿਰ ਖਾਲੀ Wayland_DBus_ਅੰਤ_Cursor_Properties(ਖਾਲੀ)
{
    SDL_free(dbus_cursor_theme);
    dbus_cursor_theme = ਨਿਰਾ;
}

#ਜੇ_ਅੰਤ

ਸਥਿਰ ਬਣਤਰ wl_ਬਫਰ *Wayland_Cursor_State_Get_ਚੌਖਟਾ(SDL_WaylandCursorState *state, ਪੂਰਨ ਚੌਖਟਾ_ਸੂਚਕਾਂਕ_2)
{
    SDL_Cursor_ਅੰਕੜੇ *ਅੰਕੜੇ = state->current_cursor;

    ਜੇ (ਅੰਕੜੇ) {
        ਜੇ (!ਅੰਕੜੇ->is_system_cursor) {
            ਅਚਲ ਪੂਰਨ ਵਿੱਥ_2 = ਅੰਕੜੇ->cursor_ਅੰਕੜੇ.custom.images_ਪ੍ਰਤੀ_ਚੌਖਟਾ * ਚੌਖਟਾ_ਸੂਚਕਾਂਕ_2;

            /* Find the closest image. Images that are larger than the
             * desired size are preferred over images that are smaller.
             */
            CustomCursorImage *closest = ਨਿਰਾ;
            ਅਚਲ ਪੂਰਨ ਨਿਸ਼ਾਨਾ_area = SDL_lround(ਅੰਕੜੇ->cursor_ਅੰਕੜੇ.custom.ਚੌੜਾਈ * ਅੰਕੜੇ->cursor_ਅੰਕੜੇ.custom.ਉਚਾਈ * state->scale);
            ਪੂਰਨ closest_area = 0;
            ਲਈ (ਪੂਰਨ i = 0; i < ਅੰਕੜੇ->cursor_ਅੰਕੜੇ.custom.images_ਪ੍ਰਤੀ_ਚੌਖਟਾ && closest_area < ਨਿਸ਼ਾਨਾ_area && ਅੰਕੜੇ->cursor_ਅੰਕੜੇ.custom.images[ਵਿੱਥ_2 + i].ਬਫਰ_2; ++i) {
                closest = &ਅੰਕੜੇ->cursor_ਅੰਕੜੇ.custom.images[ਵਿੱਥ_2 + i];
                closest_area = closest->ਚੌੜਾਈ * closest->ਉਚਾਈ;
            }

            ਵਾਪਸ closest ? closest->ਬਫਰ_2 : ਨਿਰਾ;
        } ਨਹੀਂਤਾਂ {
            ਵਾਪਸ ((Wayland_CachedSystemCursor *)(state->system_cursor_handle))->buffers[ਚੌਖਟਾ_ਸੂਚਕਾਂਕ_2];
        }
    }

    ਵਾਪਸ ਨਿਰਾ;
}

ਸਥਿਰ ਖਾਲੀ cursor_ਚੌਖਟਾ_ਪੂਰਾ(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_callback *cb, uint32_t ਸਮਾਂ);
ਸਥਿਰ ਅਚਲ ਬਣਤਰ wl_callback_listener cursor_ਚੌਖਟਾ_listener = {
    cursor_ਚੌਖਟਾ_ਪੂਰਾ
};

ਸਥਿਰ ਖਾਲੀ cursor_ਚੌਖਟਾ_ਪੂਰਾ(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_callback *cb, uint32_t ਸਮਾਂ)
{
    SDL_WaylandCursorState *state = (SDL_WaylandCursorState *)ਅੰਕੜੇ;
    ਜੇ (!state->current_cursor) {
        ਵਾਪਸ;
    }

    Uint32 *ਚੌਖਟੇ = state->current_cursor->ਚੌਖਟਾ_durations_ms;
    SDL_Cursor_ਅੰਕੜੇ *c = state->current_cursor;

    ਅਚਲ Uint64 now = SDL_GetTicks();
    ਅਚਲ Uint32 elapsed = (now - state->ਆਖਰੀ_ਚੌਖਟਾ_callback_ਸਮਾਂ_ms) % c->ਕੁੱਲ_duration_ms;
    Uint32 advance = 0;
    ਪੂਰਨ ਅਗਲਾ = state->current_ਚੌਖਟਾ;

    state->current_ਚੌਖਟਾ_ਸਮਾਂ_ms += elapsed;

    // Calculate the next frame based on the elapsed duration.
    ਲਈ (Uint32 t = ਚੌਖਟੇ[ਅਗਲਾ]; t <= state->current_ਚੌਖਟਾ_ਸਮਾਂ_ms; t += ਚੌਖਟੇ[ਅਗਲਾ]) {
        ਅਗਲਾ = (ਅਗਲਾ + 1) % c->ਅੰਕ_ਚੌਖਟੇ;
        advance = t;

        // Make sure we don't end up in an infinite loop if a cursor has frame durations of 0.
        ਜੇ (!ਚੌਖਟੇ[ਅਗਲਾ]) {
            ਰੋਕੋ;
        }
    }

    wl_callback_destroy(cb);
    state->ਚੌਖਟਾ_callback = ਨਿਰਾ;

    // Don't queue another callback if this frame time is infinite.
    ਜੇ (ਚੌਖਟੇ[ਅਗਲਾ]) {
        state->ਚੌਖਟਾ_callback = wl_surface_ਚੌਖਟਾ(state->surface);
        wl_callback_ਜੋੜੋ_listener(state->ਚੌਖਟਾ_callback, &cursor_ਚੌਖਟਾ_listener, ਅੰਕੜੇ);
    }

    state->current_ਚੌਖਟਾ_ਸਮਾਂ_ms -= advance;
    state->ਆਖਰੀ_ਚੌਖਟਾ_callback_ਸਮਾਂ_ms = now;
    state->current_ਚੌਖਟਾ = ਅਗਲਾ;

    ਬਣਤਰ wl_ਬਫਰ *ਬਫਰ_2 = Wayland_Cursor_State_Get_ਚੌਖਟਾ(state, ਅਗਲਾ);
    wl_surface_attach(state->surface, ਬਫਰ_2, 0, 0);

    ਜੇ (wl_surface_get_ਸੰਸਕਰਣ(state->surface) >= WL_SURFACE_DAMAGE_ਬਫਰ_SINCE_ਸੰਸਕਰਣ) {
        wl_surface_damage_ਬਫਰ(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    } ਨਹੀਂਤਾਂ {
        wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    }
    wl_surface_commit(state->surface);
}

ਖਾਲੀ Wayland_Cursor_State_ਸੈੱਟ_ਚੌਖਟਾ_Callback(SDL_WaylandCursorState *state, ਖਾਲੀ *userdata)
{
    SDL_Video_ਅੰਕੜੇ *viddata = SDL_GetVideoDevice()->ਅੰਦਰੂਨੀ;
    Wayland_ਤਾਲਾ_Event_Thread(viddata->event_thread_context);

    state->ਚੌਖਟਾ_callback = wl_surface_ਚੌਖਟਾ(state->surface);
    wl_callback_ਜੋੜੋ_listener(state->ਚੌਖਟਾ_callback, &cursor_ਚੌਖਟਾ_listener, userdata);

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

ਖਾਲੀ Wayland_Cursor_State_Destroy_ਚੌਖਟਾ_Callback(SDL_WaylandCursorState *state)
{
    SDL_Video_ਅੰਕੜੇ *viddata = SDL_GetVideoDevice()->ਅੰਦਰੂਨੀ;
    Wayland_ਤਾਲਾ_Event_Thread(viddata->event_thread_context);

    ਜੇ (state->ਚੌਖਟਾ_callback) {
        wl_callback_destroy(state->ਚੌਖਟਾ_callback);
        state->ਚੌਖਟਾ_callback = ਨਿਰਾ;
    }

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

ਸਥਿਰ ਖਾਲੀ Wayland_CursorStateResetAnimationState(SDL_WaylandCursorState *state)
{
    state->ਆਖਰੀ_ਚੌਖਟਾ_callback_ਸਮਾਂ_ms = SDL_GetTicks();
    state->current_ਚੌਖਟਾ_ਸਮਾਂ_ms = 0;
    state->current_ਚੌਖਟਾ = 0;
}

ਸਥਿਰ ਖਾਲੀ Wayland_CursorStateResetAnimation(SDL_WaylandCursorState *state, bool ਤਾਲਾ_2)
{
    ਜੇ (ਤਾਲਾ_2) {
        SDL_Video_ਅੰਕੜੇ *viddata = SDL_GetVideoDevice()->ਅੰਦਰੂਨੀ;
        Wayland_ਤਾਲਾ_Event_Thread(viddata->event_thread_context);
        Wayland_CursorStateResetAnimationState(state);
        Wayland_UnlockEventThread(viddata->event_thread_context);
    } ਨਹੀਂਤਾਂ {
        Wayland_CursorStateResetAnimationState(state);
    }
}

ਖਾਲੀ Wayland_CursorStateRelease(SDL_WaylandCursorState *state)
{
    Wayland_Cursor_State_Destroy_ਚੌਖਟਾ_Callback(state);
    ਜੇ (state->cursor_shape) {
        wp_cursor_shape_device_v1_destroy(state->cursor_shape);
    }
    ਜੇ (state->viewport) {
        wp_viewport_destroy(state->viewport);
    }
    ਜੇ (state->surface) {
        wl_surface_attach(state->surface, ਨਿਰਾ, 0, 0);
        wl_surface_commit(state->surface);
        wl_surface_destroy(state->surface);
    }

    SDL_zerop(state);
}

ਸਥਿਰ Wayland_CachedSystemCursor *Wayland_CacheSystemCursor(SDL_Cursor_ਅੰਕੜੇ *cdata, ਬਣਤਰ wl_cursor *cursor, ਪੂਰਨ ਮਾਪ)
{
    Wayland_CachedSystemCursor *cache = ਨਿਰਾ;

    // Is this cursor already cached at the target scale?
    ਜੇ (!WAYLAND_wl_list_ਖਾਲੀ_ਥਾਵਾਂ(&cdata->cursor_ਅੰਕੜੇ.system.cursor_ਬਫਰ_cache)) {
        Wayland_CachedSystemCursor *c = ਨਿਰਾ;
        wl_list_for_each (c, &cdata->cursor_ਅੰਕੜੇ.system.cursor_ਬਫਰ_cache, ਗੰਢ) {
            ਜੇ (c->ਮਾਪ == ਮਾਪ) {
                cache = c;
                ਰੋਕੋ;
            }
        }
    }

    ਜੇ (!cache) {
        cache = SDL_calloc(1, ਆਕਾਰ(Wayland_CachedSystemCursor) + (ਆਕਾਰ(ਬਣਤਰ wl_ਬਫਰ *) * cdata->ਅੰਕ_ਚੌਖਟੇ));

        cache->ਮਾਪ = ਮਾਪ;
        ਲਈ (ਪੂਰਨ i = 0; i < cdata->ਅੰਕ_ਚੌਖਟੇ; ++i) {
            cache->buffers[i] = WAYLAND_wl_cursor_image_get_ਬਫਰ(cursor->images[i]);
        }

        WAYLAND_wl_list_ਪਾਓ(&cdata->cursor_ਅੰਕੜੇ.system.cursor_ਬਫਰ_cache, &cache->ਗੰਢ);
    }

    ਵਾਪਸ cache;
}

ਸਥਿਰ bool Wayland_GetSystemCursor(SDL_Cursor_ਅੰਕੜੇ *cdata, SDL_WaylandCursorState *state, ਪੂਰਨ *dst_ਮਾਪ, ਪੂਰਨ *hot_x, ਪੂਰਨ *hot_y)
{
    SDL_Video_ਅੰਕੜੇ *vdata = SDL_GetVideoDevice()->ਅੰਦਰੂਨੀ;
    ਬਣਤਰ wl_cursor_theme *theme = ਨਿਰਾ;
    ਅਚਲ ਅੱਖਰ *css_name = "default";
    ਅਚਲ ਅੱਖਰ *fallback_name = ਨਿਰਾ;
    ਦੁੱਗਣਾ scale_ਗੁਣਕ_2 = state->scale;
    ਪੂਰਨ theme_ਮਾਪ = dbus_cursor_ਮਾਪ;

    // Fallback envvar if the DBus properties don't exist
    ਜੇ (theme_ਮਾਪ <= 0) {
        ਅਚਲ ਅੱਖਰ *xcursor_ਮਾਪ = SDL_getenv("XCURSOR_SIZE");
        ਜੇ (xcursor_ਮਾਪ) {
            theme_ਮਾਪ = SDL_atoi(xcursor_ਮਾਪ);
        }
    }
    ਜੇ (theme_ਮਾਪ <= 0) {
        theme_ਮਾਪ = 24;
    }

    // First, find the appropriate theme based on the current scale...
    ਅਚਲ ਪੂਰਨ scaled_ਮਾਪ = (ਪੂਰਨ)SDL_lround(theme_ਮਾਪ * scale_ਗੁਣਕ_2);
    ਲਈ (ਪੂਰਨ i = 0; i < vdata->ਅੰਕ_cursor_themes; ++i) {
        ਜੇ (vdata->cursor_themes[i].ਮਾਪ == scaled_ਮਾਪ) {
            theme = vdata->cursor_themes[i].theme;
            ਰੋਕੋ;
        }
    }
    ਜੇ (!theme) {
        ਅਚਲ ਅੱਖਰ *xcursor_theme = dbus_cursor_theme;

        SDL_WaylandCursorTheme *new_cursor_themes = SDL_realloc(vdata->cursor_themes,
                                                                ਆਕਾਰ(SDL_WaylandCursorTheme) * (vdata->ਅੰਕ_cursor_themes + 1));
        ਜੇ (!new_cursor_themes) {
            ਵਾਪਸ false;
        }
        vdata->cursor_themes = new_cursor_themes;

        // Fallback envvar if the DBus properties don't exist
        ਜੇ (!xcursor_theme) {
            xcursor_theme = SDL_getenv("XCURSOR_THEME");
        }

        theme = WAYLAND_wl_cursor_theme_ਲੱਦੋ(xcursor_theme, scaled_ਮਾਪ, vdata->shm);
        vdata->cursor_themes[vdata->ਅੰਕ_cursor_themes].ਮਾਪ = scaled_ਮਾਪ;
        vdata->cursor_themes[vdata->ਅੰਕ_cursor_themes++].theme = theme;
    }

    css_name = SDL_GetCSSCursorName(cdata->cursor_ਅੰਕੜੇ.system.id, &fallback_name);
    ਬਣਤਰ wl_cursor *cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, css_name);
    ਜੇ (!cursor && fallback_name) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, fallback_name);
    }

    // Fallback to the default cursor if the chosen one wasn't found
    ਜੇ (!cursor) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, "default");
    }
    // Try the old X11 name as a last resort
    ਜੇ (!cursor) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, "left_ptr");
    }
    ਜੇ (!cursor) {
        ਵਾਪਸ false;
    }

    // ... Set the cursor data, finally.
    cdata->ਅੰਕ_ਚੌਖਟੇ = cursor->image_ਗਿਣਤੀ_2;
    Wayland_CachedSystemCursor *c = Wayland_CacheSystemCursor(cdata, cursor, theme_ਮਾਪ);
    state->system_cursor_handle = c;

    ਜੇ (cursor->image_ਗਿਣਤੀ_2 > 1 && !cdata->ਚੌਖਟਾ_durations_ms) {
        cdata->ਕੁੱਲ_duration_ms = 0;
        cdata->ਚੌਖਟਾ_durations_ms = SDL_calloc(cursor->image_ਗਿਣਤੀ_2, ਆਕਾਰ(Uint32));

        ਲਈ (ਪੂਰਨ i = 0; i < cursor->image_ਗਿਣਤੀ_2; ++i) {
            cdata->ਚੌਖਟਾ_durations_ms[i] = cursor->images[i]->delay;
            cdata->ਕੁੱਲ_duration_ms += cursor->images[i]->delay;
        }
    }

    *dst_ਮਾਪ = SDL_lround(cursor->images[0]->ਚੌੜਾਈ / state->scale);
    *hot_x = SDL_lround(cursor->images[0]->hotspot_x / state->scale);
    *hot_y = SDL_lround(cursor->images[0]->hotspot_y / state->scale);

    ਵਾਪਸ true;
}

ਸਥਿਰ ਪੂਰਨ surface_ਛਾਂਟੋ_callback(ਅਚਲ ਖਾਲੀ *a, ਅਚਲ ਖਾਲੀ *b)
{
    ਅਚਲ SDL_Surface *s1 = *(ਅਚਲ SDL_Surface **)a;
    ਅਚਲ SDL_Surface *s2 = *(ਅਚਲ SDL_Surface **)b;

    ਵਾਪਸ (s1->w * s1->h) <= (s2->w * s2->h) ? -1 : 1;
}

ਸਥਿਰ SDL_Cursor *Wayland_CreateAnimatedCursor(SDL_Cursor_ਚੌਖਟਾ_Info *ਚੌਖਟੇ, ਪੂਰਨ ਚੌਖਟਾ_ਗਿਣਤੀ, ਪੂਰਨ hot_x, ਪੂਰਨ hot_y)
{
    SDL_Cursor *cursor = SDL_calloc(1, ਆਕਾਰ(*cursor));
    ਜੇ (!cursor) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    SDL_Cursor_ਅੰਕੜੇ *ਅੰਕੜੇ = ਨਿਰਾ;
    Wayland_SHMPool *shm_pool = ਨਿਰਾ;
    ਪੂਰਨ pool_ਮਾਪ = 0;
    ਪੂਰਨ max_images = 0;
    bool is_ਢੇਰ = false;
    ਬਣਤਰ SurfaceArray
    {
        SDL_Surface **surfaces;
        ਪੂਰਨ ਗਿਣਤੀ_2;
    } *surfaces = SDL_small_alloc(ਬਣਤਰ SurfaceArray, ਚੌਖਟਾ_ਗਿਣਤੀ, &is_ਢੇਰ);
    ਜੇ (!surfaces) {
        ਜਾਓ failed;
    }
    SDL_memset(surfaces, 0, ਆਕਾਰ(ਬਣਤਰ SurfaceArray) * ਚੌਖਟਾ_ਗਿਣਤੀ);

    // Calculate the total allocation size.
    ਲਈ (ਪੂਰਨ i = 0; i < ਚੌਖਟਾ_ਗਿਣਤੀ; ++i) {
        surfaces[i].surfaces = SDL_GetSurfaceImages(ਚੌਖਟੇ[i].surface, &surfaces[i].ਗਿਣਤੀ_2);
        ਜੇ (!surfaces[i].surfaces) {
            ਜਾਓ failed;
        }

        SDL_qsort(surfaces[i].surfaces, surfaces[i].ਗਿਣਤੀ_2, ਆਕਾਰ(SDL_Surface *), surface_ਛਾਂਟੋ_callback);
        max_images = SDL_max(max_images, surfaces[i].ਗਿਣਤੀ_2);
        ਲਈ (ਪੂਰਨ j = 0; j < surfaces[i].ਗਿਣਤੀ_2; ++j) {
            pool_ਮਾਪ += surfaces[i].surfaces[j]->w * surfaces[i].surfaces[j]->h * 4;
        }
    }

    ਅੰਕੜੇ = SDL_calloc(1, ਆਕਾਰ(*ਅੰਕੜੇ) + (ਆਕਾਰ(CustomCursorImage) * max_images * ਚੌਖਟਾ_ਗਿਣਤੀ));
    ਜੇ (!ਅੰਕੜੇ) {
        ਜਾਓ failed;
    }

    ਅੰਕੜੇ->ਚੌਖਟਾ_durations_ms = SDL_calloc(ਚੌਖਟਾ_ਗਿਣਤੀ, ਆਕਾਰ(Uint32));
    ਜੇ (!ਅੰਕੜੇ->ਚੌਖਟਾ_durations_ms) {
        ਜਾਓ failed;
    }

    shm_pool = Wayland_AllocSHMPool(pool_ਮਾਪ);
    ਜੇ (!shm_pool) {
        ਜਾਓ failed;
    }

    cursor->ਅੰਦਰੂਨੀ = ਅੰਕੜੇ;
    ਅੰਕੜੇ->cursor_ਅੰਕੜੇ.custom.ਚੌੜਾਈ = ਚੌਖਟੇ[0].surface->w;
    ਅੰਕੜੇ->cursor_ਅੰਕੜੇ.custom.ਉਚਾਈ = ਚੌਖਟੇ[0].surface->h;
    ਅੰਕੜੇ->cursor_ਅੰਕੜੇ.custom.hot_x = hot_x;
    ਅੰਕੜੇ->cursor_ਅੰਕੜੇ.custom.hot_y = hot_y;
    ਅੰਕੜੇ->cursor_ਅੰਕੜੇ.custom.images_ਪ੍ਰਤੀ_ਚੌਖਟਾ = max_images;
    ਅੰਕੜੇ->ਅੰਕ_ਚੌਖਟੇ = ਚੌਖਟਾ_ਗਿਣਤੀ;

    ਲਈ (ਪੂਰਨ i = 0; i < ਚੌਖਟਾ_ਗਿਣਤੀ; ++i) {
        ਅੰਕੜੇ->ਚੌਖਟਾ_durations_ms[i] = ਚੌਖਟੇ[i].duration;
        ਜੇ (ਅੰਕੜੇ->ਕੁੱਲ_duration_ms < SDL_MAX_UINT32) {
            ਜੇ (ਅੰਕੜੇ->ਚੌਖਟਾ_durations_ms[i] > 0) {
                ਅੰਕੜੇ->ਕੁੱਲ_duration_ms += ਅੰਕੜੇ->ਚੌਖਟਾ_durations_ms[i];
            } ਨਹੀਂਤਾਂ {
                ਅੰਕੜੇ->ਕੁੱਲ_duration_ms = SDL_MAX_UINT32;
            }
        }

        ਅਚਲ ਪੂਰਨ ਵਿੱਥ_2 = i * max_images;
        ਲਈ (ਪੂਰਨ j = 0; j < surfaces[i].ਗਿਣਤੀ_2; ++j) {
            SDL_Surface *surface = surfaces[i].surfaces[j];

            // Convert the surface format, if required.
            ਜੇ (surface->format != SDL_PIXELFORMAT_ARGB8888) {
                surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
                ਜੇ (!surface) {
                    ਜਾਓ failed;
                }
            }

            ਅੰਕੜੇ->cursor_ਅੰਕੜੇ.custom.images[ਵਿੱਥ_2 + j].ਚੌੜਾਈ = surface->w;
            ਅੰਕੜੇ->cursor_ਅੰਕੜੇ.custom.images[ਵਿੱਥ_2 + j].ਉਚਾਈ = surface->h;

            ਖਾਲੀ *buf_ਅੰਕੜੇ;
            ਅੰਕੜੇ->cursor_ਅੰਕੜੇ.custom.images[ਵਿੱਥ_2 + j].ਬਫਰ_2 = Wayland_Alloc_ਬਫਰ_From_Pool(shm_pool, surface->w, surface->h, &buf_ਅੰਕੜੇ);
            // Wayland requires premultiplied alpha for its surfaces.
            SDL_PremultiplyAlpha(surface->w, surface->h,
                                 surface->format, surface->pixels, surface->pitch,
                                 SDL_PIXELFORMAT_ARGB8888, buf_ਅੰਕੜੇ, surface->w * 4, true);

            ਜੇ (surface != surfaces[i].surfaces[j]) {
                SDL_DestroySurface(surface);
            }
        }

        // Free the memory returned by SDL_GetSurfaceImages().
        SDL_free(surfaces[i].surfaces);
    }

    SDL_small_free(surfaces, is_ਢੇਰ);
    Wayland_ReleaseSHMPool(shm_pool);

    ਵਾਪਸ cursor;

failed:
    Wayland_ReleaseSHMPool(shm_pool);
    ਜੇ (ਅੰਕੜੇ) {
        SDL_free(ਅੰਕੜੇ->ਚੌਖਟਾ_durations_ms);
        ਲਈ (ਪੂਰਨ i = 0; i < ਅੰਕੜੇ->cursor_ਅੰਕੜੇ.custom.images_ਪ੍ਰਤੀ_ਚੌਖਟਾ * ਚੌਖਟਾ_ਗਿਣਤੀ; ++i) {
            ਜੇ (ਅੰਕੜੇ->cursor_ਅੰਕੜੇ.custom.images[i].ਬਫਰ_2) {
                wl_ਬਫਰ_destroy(ਅੰਕੜੇ->cursor_ਅੰਕੜੇ.custom.images[i].ਬਫਰ_2);
            }
        }
    }

    SDL_free(ਅੰਕੜੇ);

    ਜੇ (surfaces) {
        ਲਈ (ਪੂਰਨ i = 0; i < ਚੌਖਟਾ_ਗਿਣਤੀ; ++i) {
            SDL_free(surfaces[i].surfaces);
        }
        SDL_small_free(surfaces, is_ਢੇਰ);
    }

    SDL_free(cursor);

    ਵਾਪਸ ਨਿਰਾ;
}

ਸਥਿਰ SDL_Cursor *Wayland_CreateCursor(SDL_Surface *surface, ਪੂਰਨ hot_x, ਪੂਰਨ hot_y)
{
    SDL_Cursor_ਚੌਖਟਾ_Info ਚੌਖਟਾ = {
        surface, 0
    };

    ਵਾਪਸ Wayland_CreateAnimatedCursor(&ਚੌਖਟਾ, 1, hot_x, hot_y);
}

ਸਥਿਰ SDL_Cursor *Wayland_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = SDL_calloc(1, ਆਕਾਰ(*cursor));

    ਜੇ (cursor) {
        SDL_Cursor_ਅੰਕੜੇ *cdata = SDL_calloc(1, ਆਕਾਰ(*cdata));
        ਜੇ (!cdata) {
            SDL_free(cursor);
            ਵਾਪਸ ਨਿਰਾ;
        }
        cursor->ਅੰਦਰੂਨੀ = cdata;

        WAYLAND_wl_list_init(&cdata->cursor_ਅੰਕੜੇ.system.cursor_ਬਫਰ_cache);
        cdata->cursor_ਅੰਕੜੇ.system.id = id;
        cdata->is_system_cursor = true;
    }

    ਵਾਪਸ cursor;
}

ਸਥਿਰ SDL_Cursor *Wayland_CreateDefaultCursor(ਖਾਲੀ)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    ਵਾਪਸ Wayland_CreateSystemCursor(id);
}

ਸਥਿਰ ਖਾਲੀ Wayland_Free_Cursor_ਅੰਕੜੇ(SDL_Cursor_ਅੰਕੜੇ *d)
{
    SDL_VideoDevice *video_device = SDL_GetVideoDevice();
    SDL_Video_ਅੰਕੜੇ *video_ਅੰਕੜੇ = video_device->ਅੰਦਰੂਨੀ;
    SDL_WaylandSeat *seat;

    // Stop any frame callbacks and detach buffers associated with the cursor being destroyed.
    wl_list_for_each (seat, &video_ਅੰਕੜੇ->seat_list, link)
    {
        ਜੇ (seat->ਸੂਚਕ_2.cursor_state.current_cursor == d) {
            Wayland_Cursor_State_Destroy_ਚੌਖਟਾ_Callback(&seat->ਸੂਚਕ_2.cursor_state);

            // Custom cursor buffers are about to be destroyed, so ensure they are detached.
            ਜੇ (!d->is_system_cursor && seat->ਸੂਚਕ_2.cursor_state.surface) {
                wl_surface_attach(seat->ਸੂਚਕ_2.cursor_state.surface, ਨਿਰਾ, 0, 0);
            }

            seat->ਸੂਚਕ_2.cursor_state.current_cursor = ਨਿਰਾ;
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            ਜੇ (tool->cursor_state.current_cursor == d) {
                Wayland_Cursor_State_Destroy_ਚੌਖਟਾ_Callback(&tool->cursor_state);

                // Custom cursor buffers are about to be destroyed, so ensure they are detached.
                ਜੇ (!d->is_system_cursor && tool->cursor_state.surface) {
                    wl_surface_attach(seat->ਸੂਚਕ_2.cursor_state.surface, ਨਿਰਾ, 0, 0);
                }

                tool->cursor_state.current_cursor = ਨਿਰਾ;
            }
        }
    }

    ਜੇ (d->is_system_cursor) {
        Wayland_CachedSystemCursor *c, *ਆਰਜ਼ੀ;
        wl_list_for_each_ਸੁਰੱਖਿਅਤ(c, ਆਰਜ਼ੀ, &d->cursor_ਅੰਕੜੇ.system.cursor_ਬਫਰ_cache, ਗੰਢ) {
            SDL_free(c);
        }
    } ਨਹੀਂਤਾਂ {
        ਲਈ (ਪੂਰਨ i = 0; i < d->ਅੰਕ_ਚੌਖਟੇ * d->cursor_ਅੰਕੜੇ.custom.images_ਪ੍ਰਤੀ_ਚੌਖਟਾ; ++i) {
            ਜੇ (d->cursor_ਅੰਕੜੇ.custom.images[i].ਬਫਰ_2) {
                wl_ਬਫਰ_destroy(d->cursor_ਅੰਕੜੇ.custom.images[i].ਬਫਰ_2);
            }
        }
    }

    SDL_free(d->ਚੌਖਟਾ_durations_ms);
}

ਸਥਿਰ ਖਾਲੀ Wayland_FreeCursor(SDL_Cursor *cursor)
{
    ਜੇ (!cursor) {
        ਵਾਪਸ;
    }

    // Probably not a cursor we own
    ਜੇ (!cursor->ਅੰਦਰੂਨੀ) {
        ਵਾਪਸ;
    }

    Wayland_Free_Cursor_ਅੰਕੜੇ(cursor->ਅੰਦਰੂਨੀ);

    SDL_free(cursor->ਅੰਦਰੂਨੀ);
    SDL_free(cursor);
}

ਸਥਿਰ ਗਿਣਤੀ wp_cursor_shape_device_v1_shape Wayland_GetSystemCursorShape(SDL_SystemCursor id)
{
    Uint32 shape;

    ਚੋਣ (id) {
    ਹਾਲਤ SDL_SYSTEM_CURSOR_DEFAULT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_ਪਾਠ:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ਪਾਠ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_WAIT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_WAIT;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_CROSSHAIR:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CROSSHAIR;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_ਤਰੱਕੀ:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ਤਰੱਕੀ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NWSE_RESIZE;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_NESW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NESW_RESIZE;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_EW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_EW_RESIZE;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_NS_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NS_RESIZE;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_MOVE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_MOVE;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NOT_ALLOWED;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_ਸੂਚਕ:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ਸੂਚਕ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_NW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NW_RESIZE;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_N_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_N_RESIZE;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_NE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NE_RESIZE;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_E_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_E_RESIZE;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_SE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_SE_RESIZE;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_S_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_S_RESIZE;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_SW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_SW_RESIZE;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_W_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_W_RESIZE;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CONTEXT_MENU;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_HELP:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_HELP;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_CELL:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CELL;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_VERTICAL_ਪਾਠ:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_VERTICAL_ਪਾਠ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_ALIAS:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ALIAS;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_COPY:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_COPY;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_NO_DROP:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NO_DROP;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_GRAB:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_GRAB;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_GRABBING:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_GRABBING;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_ਖਾਨਾ_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ਖਾਨਾ_RESIZE;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_ਪੰਕਤੀ_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ਪੰਕਤੀ_RESIZE;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ALL_SCROLL;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_ZOOM_ਵਿੱਚ:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_ਵਿੱਚ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_ZOOM_ਬਾਹਰਲਾ:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_ਬਾਹਰਲਾ;
        ਰੋਕੋ;
    ਮੂਲ:
        SDL_assert(0); // Should never be here...
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
    }

    ਵਾਪਸ shape;
}

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Wayland_ਸੂਚਕ_Object
{
    ਸੰਘ
    {
        ਬਣਤਰ wl_ਸੂਚਕ *wl_ਸੂਚਕ;
        ਬਣਤਰ zwp_tablet_tool_v2 *wl_tool;
    };

    bool is_ਸੂਚਕ;
} Wayland_ਸੂਚਕ_Object;

ਸਥਿਰ ਖਾਲੀ Wayland_Cursor_State_ਸੈੱਟ_Cursor(SDL_WaylandCursorState *state, ਅਚਲ Wayland_ਸੂਚਕ_Object *obj, SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *focus, Uint32 serial, SDL_Cursor *cursor)
{
    SDL_Video_ਅੰਕੜੇ *viddata = SDL_GetVideoDevice()->ਅੰਦਰੂਨੀ;
    SDL_Cursor_ਅੰਕੜੇ *cursor_ਅੰਕੜੇ = cursor ? cursor->ਅੰਦਰੂਨੀ : ਨਿਰਾ;
    ਪੂਰਨ dst_ਚੌੜਾਈ = 0;
    ਪੂਰਨ dst_ਉਚਾਈ = 0;
    ਪੂਰਨ hot_x;
    ਪੂਰਨ hot_y;

    // Stop the frame callback for old animated cursors.
    ਜੇ (cursor_ਅੰਕੜੇ != state->current_cursor) {
        Wayland_Cursor_State_Destroy_ਚੌਖਟਾ_Callback(state);
    }

    ਜੇ (cursor) {
        ਜੇ (cursor_ਅੰਕੜੇ == state->current_cursor && state->current_ਚੌਖਟਾ >= 0) {
            // Restart the animation sequence if the cursor didn't change.
            ਜੇ (cursor_ਅੰਕੜੇ->ਅੰਕ_ਚੌਖਟੇ > 1) {
                Wayland_CursorStateResetAnimation(state, true);
            }

            ਵਾਪਸ;
        }

        ਜੇ (cursor_ਅੰਕੜੇ->is_system_cursor) {
            // If the cursor shape protocol is supported, the compositor will draw nicely scaled cursors for us, so nothing more to do.
            ਜੇ (state->cursor_shape) {
                // Don't need the surface or viewport if using the cursor shape protocol.
                ਜੇ (state->surface) {
                    wl_surface_attach(state->surface, ਨਿਰਾ, 0, 0);
                    wl_surface_commit(state->surface);

                    ਜੇ (obj->is_ਸੂਚਕ) {
                        wl_ਸੂਚਕ_ਸੈੱਟ_cursor(obj->wl_ਸੂਚਕ, serial, ਨਿਰਾ, 0, 0);
                    } ਨਹੀਂਤਾਂ {
                        zwp_tablet_tool_v2_ਸੈੱਟ_cursor(obj->wl_tool, serial, ਨਿਰਾ, 0, 0);
                    }

                    ਜੇ (state->viewport) {
                        wp_viewport_destroy(state->viewport);
                        state->viewport = ਨਿਰਾ;
                    }

                    wl_surface_destroy(state->surface);
                    state->surface = ਨਿਰਾ;
                }

                ਅਚਲ ਗਿਣਤੀ wp_cursor_shape_device_v1_shape shape = Wayland_GetSystemCursorShape(cursor_ਅੰਕੜੇ->cursor_ਅੰਕੜੇ.system.id);
                wp_cursor_shape_device_v1_ਸੈੱਟ_shape(state->cursor_shape, serial, shape);
                state->current_cursor = cursor_ਅੰਕੜੇ;
                state->current_ਚੌਖਟਾ = 0;

                ਵਾਪਸ;
            }

            // If viewports aren't available, the scale is always 1.0.
            state->scale = viddata->viewporter && focus ? focus->scale_ਗੁਣਕ_2 : 1.0;
            ਜੇ (!Wayland_GetSystemCursor(cursor_ਅੰਕੜੇ, state, &dst_ਚੌੜਾਈ, &hot_x, &hot_y)) {
                ਵਾਪਸ;
            }

            dst_ਉਚਾਈ = dst_ਚੌੜਾਈ;
        } ਨਹੀਂਤਾਂ {
            /* If viewports aren't available, the scale is always 1.0.
             *
             * If the pointer scale values are 1.0, the preferred backing buffer scale is the window scale.
             *
             * If the pointer is scaled, the dimensions are scaled by the pointer scale, so custom cursors will be scaled
             * relative to the viewport size.
             */
            ਜੇ (!focus || (focus->ਸੂਚਕ_scale.x == 1.0 && focus->ਸੂਚਕ_scale.y == 1.0)) {
                state->scale = viddata->viewporter && focus ? focus->scale_ਗੁਣਕ_2 : 1.0;
                dst_ਚੌੜਾਈ = cursor_ਅੰਕੜੇ->cursor_ਅੰਕੜੇ.custom.ਚੌੜਾਈ;
                dst_ਉਚਾਈ = cursor_ਅੰਕੜੇ->cursor_ਅੰਕੜੇ.custom.ਉਚਾਈ;
                hot_x = cursor_ਅੰਕੜੇ->cursor_ਅੰਕੜੇ.custom.hot_x;
                hot_y = cursor_ਅੰਕੜੇ->cursor_ਅੰਕੜੇ.custom.hot_y;
            } ਨਹੀਂਤਾਂ {
                // The preferred buffer scale is the inverse of the pointer scale.
                state->scale = 1.0 / SDL_min(focus->ਸੂਚਕ_scale.x, focus->ਸੂਚਕ_scale.y);
                dst_ਚੌੜਾਈ = SDL_max((ਪੂਰਨ)SDL_lround((ਦੁੱਗਣਾ)cursor_ਅੰਕੜੇ->cursor_ਅੰਕੜੇ.custom.ਚੌੜਾਈ / focus->ਸੂਚਕ_scale.x), 1);
                dst_ਉਚਾਈ = SDL_max((ਪੂਰਨ)SDL_lround((ਦੁੱਗਣਾ)cursor_ਅੰਕੜੇ->cursor_ਅੰਕੜੇ.custom.ਉਚਾਈ / focus->ਸੂਚਕ_scale.y), 1);
                hot_x = (ਪੂਰਨ)SDL_lround((ਦੁੱਗਣਾ)cursor_ਅੰਕੜੇ->cursor_ਅੰਕੜੇ.custom.hot_x / focus->ਸੂਚਕ_scale.x);
                hot_y = (ਪੂਰਨ)SDL_lround((ਦੁੱਗਣਾ)cursor_ਅੰਕੜੇ->cursor_ਅੰਕੜੇ.custom.hot_y / focus->ਸੂਚਕ_scale.y);
            }

        }

        state->current_cursor = cursor_ਅੰਕੜੇ;

        ਜੇ (!state->surface) {
            ਬਣਤਰ wl_compositor *compositor_wrapper = Wayland_CreateEventThreadProxyWrapper(viddata->event_thread_context, viddata->compositor);
            state->surface = wl_compositor_create_surface(compositor_wrapper);
            WAYLAND_wl_proxy_wrapper_destroy(compositor_wrapper);
        }

        ਬਣਤਰ wl_ਬਫਰ *ਬਫਰ_2 = Wayland_Cursor_State_Get_ਚੌਖਟਾ(state, 0);
        wl_surface_attach(state->surface, ਬਫਰ_2, 0, 0);
        state->current_ਚੌਖਟਾ = 0;

        ਜੇ (state->scale != 1.0) {
            ਜੇ (!state->viewport) {
                state->viewport = wp_viewporter_get_viewport(viddata->viewporter, state->surface);
            }

            wp_viewport_ਸੈੱਟ_ਸਰੋਤ(state->viewport, wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1));
            wp_viewport_ਸੈੱਟ_destination(state->viewport, dst_ਚੌੜਾਈ, dst_ਉਚਾਈ);
        } ਨਹੀਂਤਾਂ ਜੇ (state->viewport) {
            wp_viewport_destroy(state->viewport);
            state->viewport = ਨਿਰਾ;
        }

        ਜੇ (obj->is_ਸੂਚਕ) {
            wl_ਸੂਚਕ_ਸੈੱਟ_cursor(obj->wl_ਸੂਚਕ, serial, state->surface, hot_x, hot_y);
        } ਨਹੀਂਤਾਂ {
            zwp_tablet_tool_v2_ਸੈੱਟ_cursor(obj->wl_tool, serial, state->surface, hot_x, hot_y);
        }

        ਜੇ (wl_surface_get_ਸੰਸਕਰਣ(state->surface) >= WL_SURFACE_DAMAGE_ਬਫਰ_SINCE_ਸੰਸਕਰਣ) {
            wl_surface_damage_ਬਫਰ(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        } ਨਹੀਂਤਾਂ {
            wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        }

        // If more than one frame is available, create a frame callback to run the animation.
        ਜੇ (cursor_ਅੰਕੜੇ->ਅੰਕ_ਚੌਖਟੇ > 1) {
            Wayland_CursorStateResetAnimation(state, false);
            Wayland_Cursor_State_ਸੈੱਟ_ਚੌਖਟਾ_Callback(state, state);
        }

        wl_surface_commit(state->surface);
    } ਨਹੀਂਤਾਂ {
        Wayland_Cursor_State_Destroy_ਚੌਖਟਾ_Callback(state);
        state->current_cursor = ਨਿਰਾ;

        ਜੇ (state->surface) {
            wl_surface_attach(state->surface, ਨਿਰਾ, 0, 0);
            wl_surface_commit(state->surface);
        }

        ਜੇ (obj->is_ਸੂਚਕ) {
            wl_ਸੂਚਕ_ਸੈੱਟ_cursor(obj->wl_ਸੂਚਕ, serial, ਨਿਰਾ, 0, 0);
        } ਨਹੀਂਤਾਂ {
            zwp_tablet_tool_v2_ਸੈੱਟ_cursor(obj->wl_tool, serial, ਨਿਰਾ, 0, 0);
        }
    }
}

ਸਥਿਰ ਖਾਲੀ Wayland_CursorStateResetCursor(SDL_WaylandCursorState *state)
{
    // Stop the frame callback and set the reset status.
    Wayland_Cursor_State_Destroy_ਚੌਖਟਾ_Callback(state);
    state->current_ਚੌਖਟਾ = -1;
}

ਖਾਲੀ Wayland_Display_Update_ਸੂਚਕ_Focused_Scale(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *updated_ਖਿੜਕੀ)
{
    SDL_Video_ਅੰਕੜੇ *viddata = updated_ਖਿੜਕੀ->wayland_ਅੰਕੜੇ;
    SDL_WaylandSeat *seat;
    ਅਚਲ ਦੁੱਗਣਾ new_scale = SDL_min(updated_ਖਿੜਕੀ->ਸੂਚਕ_scale.x, updated_ਖਿੜਕੀ->ਸੂਚਕ_scale.y);

    wl_list_for_each (seat, &viddata->seat_list, link) {
        ਜੇ (seat->ਸੂਚਕ_2.focus == updated_ਖਿੜਕੀ) {
            SDL_WaylandCursorState *state = &seat->ਸੂਚਕ_2.cursor_state;
            ਜੇ (state->current_cursor && !state->current_cursor->is_system_cursor && state->scale != new_scale) {
                Wayland_CursorStateResetCursor(state);
                Wayland_Seat_Update_ਸੂਚਕ_Cursor(seat);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            ਜੇ (tool->focus == updated_ਖਿੜਕੀ) {
                SDL_WaylandCursorState *state = &tool->cursor_state;
                ਜੇ (state->current_cursor && !state->current_cursor->is_system_cursor && state->scale != new_scale) {
                    Wayland_CursorStateResetCursor(&tool->cursor_state);
                    Wayland_TabletToolUpdateCursor(tool);
                }
            }
        }
    }
}

ਸਥਿਰ bool Wayland_ShowCursor(SDL_Cursor *cursor)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_ਅੰਕੜੇ *d = vd->ਅੰਦਰੂਨੀ;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WaylandSeat *seat;
    Wayland_ਸੂਚਕ_Object obj;

    wl_list_for_each (seat, &d->seat_list, link) {
        ਜੇ (seat->ਸੂਚਕ_2.wl_ਸੂਚਕ) {
            obj.wl_ਸੂਚਕ = seat->ਸੂਚਕ_2.wl_ਸੂਚਕ;
            obj.is_ਸੂਚਕ = true;
            ਜੇ (mouse->focus && mouse->focus->ਅੰਦਰੂਨੀ == seat->ਸੂਚਕ_2.focus) {
                Wayland_Cursor_State_ਸੈੱਟ_Cursor(&seat->ਸੂਚਕ_2.cursor_state, &obj, seat->ਸੂਚਕ_2.focus, seat->ਸੂਚਕ_2.enter_serial, cursor);
            } ਨਹੀਂਤਾਂ ਜੇ (!seat->ਸੂਚਕ_2.focus) {
                Wayland_CursorStateResetCursor(&seat->ਸੂਚਕ_2.cursor_state);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each(tool, &seat->tablet.tool_list, link) {
            obj.wl_tool = tool->wltool;
            obj.is_ਸੂਚਕ = false;

            /* The current cursor is explicitly set on tablet tools, as there may be no pointer device, or
             * the pointer may not have focus, which would instead cause the default cursor to be set.
             */
            ਜੇ (tool->focus && (!mouse->focus || mouse->focus->ਅੰਦਰੂਨੀ == tool->focus)) {
                Wayland_Cursor_State_ਸੈੱਟ_Cursor(&tool->cursor_state, &obj, tool->focus, tool->proximity_serial, mouse->cur_cursor);
            } ਨਹੀਂਤਾਂ ਜੇ (!tool->focus) {
                Wayland_CursorStateResetCursor(&tool->cursor_state);
            }
        }
    }

    ਵਾਪਸ true;
}

ਖਾਲੀ Wayland_SeatWarpMouse(SDL_WaylandSeat *seat, SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ, ਦਸ਼ਮਲਵ x, ਦਸ਼ਮਲਵ y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_ਅੰਕੜੇ *d = vd->ਅੰਦਰੂਨੀ;

    ਜੇ (seat->ਸੂਚਕ_2.wl_ਸੂਚਕ) {
        ਜੇ (d->wp_ਸੂਚਕ_warp_v1) {
            // It's a protocol error to warp the pointer outside of the surface, so clamp the position.
            ਅਚਲ wl_fixed_t f_x = wl_fixed_from_double(SDL_clamp(x / ਖਿੜਕੀ->ਸੂਚਕ_scale.x, 0, ਖਿੜਕੀ->current.logical_ਚੌੜਾਈ));
            ਅਚਲ wl_fixed_t f_y = wl_fixed_from_double(SDL_clamp(y / ਖਿੜਕੀ->ਸੂਚਕ_scale.y, 0, ਖਿੜਕੀ->current.logical_ਉਚਾਈ));
            wp_ਸੂਚਕ_warp_v1_warp_ਸੂਚਕ(d->wp_ਸੂਚਕ_warp_v1, ਖਿੜਕੀ->surface, seat->ਸੂਚਕ_2.wl_ਸੂਚਕ, f_x, f_y, seat->ਸੂਚਕ_2.enter_serial);
        } ਨਹੀਂਤਾਂ {
            bool update_grabs = false;

            // Pointers can only have one confinement type active on a surface at one time.
            ਜੇ (seat->ਸੂਚਕ_2.confined_ਸੂਚਕ) {
                zwp_confined_ਸੂਚਕ_v1_destroy(seat->ਸੂਚਕ_2.confined_ਸੂਚਕ);
                seat->ਸੂਚਕ_2.confined_ਸੂਚਕ = ਨਿਰਾ;
                update_grabs = true;
            }
            ਜੇ (seat->ਸੂਚਕ_2.locked_ਸੂਚਕ) {
                zwp_locked_ਸੂਚਕ_v1_destroy(seat->ਸੂਚਕ_2.locked_ਸੂਚਕ);
                seat->ਸੂਚਕ_2.locked_ਸੂਚਕ = ਨਿਰਾ;
                update_grabs = true;
            }

            /* The pointer confinement protocol allows setting a hint to warp the pointer,
             * but only when the pointer is locked.
             *
             * Lock the pointer, set the position hint, unlock, and hope for the best.
             */
            ਬਣਤਰ zwp_locked_ਸੂਚਕ_v1 *warp_ਤਾਲਾ =
                zwp_ਸੂਚਕ_constraints_v1_ਤਾਲਾ_ਸੂਚਕ(d->ਸੂਚਕ_constraints, ਖਿੜਕੀ->surface,
                                                        seat->ਸੂਚਕ_2.wl_ਸੂਚਕ, ਨਿਰਾ,
                                                        ZWP_ਸੂਚਕ_CONSTRAINTS_V1_LIFETIME_ONESHOT);

            ਅਚਲ wl_fixed_t f_x = wl_fixed_from_double(x / ਖਿੜਕੀ->ਸੂਚਕ_scale.x);
            ਅਚਲ wl_fixed_t f_y = wl_fixed_from_double(y / ਖਿੜਕੀ->ਸੂਚਕ_scale.y);
            zwp_locked_ਸੂਚਕ_v1_ਸੈੱਟ_cursor_position_hint(warp_ਤਾਲਾ, f_x, f_y);
            wl_surface_commit(ਖਿੜਕੀ->surface);

            zwp_locked_ਸੂਚਕ_v1_destroy(warp_ਤਾਲਾ);

            ਜੇ (update_grabs) {
                Wayland_Seat_Update_ਸੂਚਕ_Grab(seat);
            }
        }

        ਜੇ (wl_ਸੂਚਕ_get_ਸੰਸਕਰਣ(seat->ਸੂਚਕ_2.wl_ਸੂਚਕ) < WL_ਸੂਚਕ_WARP_SINCE_ਸੰਸਕਰਣ) {
            SDL_SendMouseWarp(0, ਖਿੜਕੀ->sdlwindow, seat->ਸੂਚਕ_2.sdl_id, x, y);
        }
    }
}

ਸਥਿਰ bool Wayland_WarpMouseRelative(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਦਸ਼ਮਲਵ x, ਦਸ਼ਮਲਵ y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_ਅੰਕੜੇ *d = vd->ਅੰਦਰੂਨੀ;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    SDL_WaylandSeat *seat;

    ਜੇ (d->wp_ਸੂਚਕ_warp_v1 || d->ਸੂਚਕ_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            ਜੇ (wind == seat->ਸੂਚਕ_2.focus) {
                Wayland_SeatWarpMouse(seat, wind, x, y);
            }
        }
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    ਵਾਪਸ true;
}

ਸਥਿਰ bool Wayland_WarpMouseGlobal(ਦਸ਼ਮਲਵ x, ਦਸ਼ਮਲਵ y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_ਅੰਕੜੇ *d = vd->ਅੰਦਰੂਨੀ;
    SDL_WaylandSeat *seat;

    ਜੇ (d->wp_ਸੂਚਕ_warp_v1 || d->ਸੂਚਕ_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = seat->ਸੂਚਕ_2.focus ? seat->ਸੂਚਕ_2.focus : seat->keyboard.focus;

            // If the client wants the coordinates warped to within a focused window, just convert the coordinates to relative.
            ਜੇ (wind) {
                SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = wind->sdlwindow;

                ਪੂਰਨ abs_x, abs_y;
                SDL_Relative_ਮੰਜ਼ਿਲ_Global_For_ਖਿੜਕੀ(ਖਿੜਕੀ, ਖਿੜਕੀ->x, ਖਿੜਕੀ->y, &abs_x, &abs_y);

                ਅਚਲ SDL_FPoint p = { x, y };
                ਅਚਲ SDL_FRect r = { abs_x, abs_y, ਖਿੜਕੀ->w, ਖਿੜਕੀ->h };

                // Try to warp the cursor if the point is within the seat's focused window.
                ਜੇ (SDL_ਬਿੰਦੂ_ਵਿੱਚ_Rect_Float(&p, &r)) {
                    Wayland_SeatWarpMouse(seat, wind, p.x - abs_x, p.y - abs_y);
                }
            }
        }
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    ਵਾਪਸ true;
}

ਸਥਿਰ bool Wayland_ਸੈੱਟ_Relative_Mouse_ਬਹੁਲਕ(bool enabled)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = vd->ਅੰਦਰੂਨੀ;

    // Relative mode requires both the relative motion and pointer confinement protocols.
    ਜੇ (!ਅੰਕੜੇ->relative_ਸੂਚਕ_manager) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Failed to enable relative mode: compositor lacks support for the required zwp_relative_pointer_manager_v1 protocol");
    }
    ਜੇ (!ਅੰਕੜੇ->ਸੂਚਕ_constraints) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Failed to enable relative mode: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }

    // Windows have a relative mode flag, so just update the grabs on a state change.
    Wayland_Display_Update_ਸੂਚਕ_Grabs(ਅੰਕੜੇ, ਨਿਰਾ);
    ਵਾਪਸ true;
}

/* Wayland doesn't support getting the true global cursor position, but it can
 * be faked well enough for what most applications use it for: querying the
 * global cursor coordinates and transforming them to the window-relative
 * coordinates manually.
 *
 * The global position is derived by taking the cursor position relative to the
 * toplevel window, and offsetting it by the origin of the output the window is
 * currently considered to be on. The cursor position and button state when the
 * cursor is outside an application window are unknown, but this gives 'correct'
 * coordinates when the window has focus, which is good enough for most
 * applications.
 */
ਸਥਿਰ SDL_MouseButtonFlags SDLCALL Wayland_GetGlobalMouseState(ਦਸ਼ਮਲਵ *x, ਦਸ਼ਮਲਵ *y)
{
    ਅਚਲ SDL_Mouse *mouse = SDL_GetMouse();
    SDL_MouseButtonFlags ਨਤੀਜਾ = 0;

    // If there is no window with mouse focus, we have no idea what the actual position or button state is.
    ਜੇ (mouse->focus) {
        SDL_Video_ਅੰਕੜੇ *video_ਅੰਕੜੇ = SDL_GetVideoDevice()->ਅੰਦਰੂਨੀ;
        SDL_WaylandSeat *seat;
        ਪੂਰਨ off_x, off_y;
        SDL_Relative_ਮੰਜ਼ਿਲ_Global_For_ਖਿੜਕੀ(mouse->focus, mouse->focus->x, mouse->focus->y, &off_x, &off_y);
        *x = mouse->x + off_x;
        *y = mouse->y + off_y;

        // Query the buttons from the seats directly, as this may be called from within a hit test handler.
        wl_list_for_each (seat, &video_ਅੰਕੜੇ->seat_list, link) {
            ਨਤੀਜਾ |= seat->ਸੂਚਕ_2.buttons_pressed;
        }
    } ਨਹੀਂਤਾਂ {
        *x = 0.f;
        *y = 0.f;
    }

    ਵਾਪਸ ਨਤੀਜਾ;
}

#ਜੇ 0  // TODO RECONNECT: See waylandvideo.c for more information!
ਸਥਿਰ ਖਾਲੀ Wayland_RecreateCursor(SDL_Cursor *cursor, SDL_Video_ਅੰਕੜੇ *vdata)
{
    SDL_Cursor_ਅੰਕੜੇ *cdata = cursor->ਅੰਦਰੂਨੀ;

    // Probably not a cursor we own
    ਜੇ (cdata == ਨਿਰਾ) {
        ਵਾਪਸ;
    }

    Wayland_Free_Cursor_ਅੰਕੜੇ(cdata);

    // We're not currently freeing this, so... yolo?
    ਜੇ (cdata->shm_ਅੰਕੜੇ != ਨਿਰਾ) {
        ਖਾਲੀ *old_ਅੰਕੜੇ_ਸੂਚਕ = cdata->shm_ਅੰਕੜੇ;
        ਪੂਰਨ stride = cdata->w * 4;

        create_ਬਫਰ_from_shm(cdata, cdata->w, cdata->h, WL_SHM_FORMAT_ARGB8888);

        SDL_memcpy(cdata->shm_ਅੰਕੜੇ, old_ਅੰਕੜੇ_ਸੂਚਕ, stride * cdata->h);
    }
    cdata->surface = wl_compositor_create_surface(vdata->compositor);
    wl_surface_ਸੈੱਟ_user_ਅੰਕੜੇ(cdata->surface, ਨਿਰਾ);
}

ਖਾਲੀ Wayland_RecreateCursors(ਖਾਲੀ)
{
    SDL_Cursor *cursor;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Video_ਅੰਕੜੇ *vdata = SDL_GetVideoDevice()->ਅੰਦਰੂਨੀ;

    ਜੇ (vdata && vdata->cursor_themes) {
        SDL_free(vdata->cursor_themes);
        vdata->cursor_themes = ਨਿਰਾ;
        vdata->ਅੰਕ_cursor_themes = 0;
    }

    ਜੇ (mouse == ਨਿਰਾ) {
        ਵਾਪਸ;
    }

    ਲਈ (cursor = mouse->cursors; cursor != ਨਿਰਾ; cursor = cursor->ਅਗਲਾ) {
        Wayland_RecreateCursor(cursor, vdata);
    }
    ਜੇ (mouse->def_cursor) {
        Wayland_RecreateCursor(mouse->def_cursor, vdata);
    }
    ਜੇ (mouse->cur_cursor) {
        Wayland_RecreateCursor(mouse->cur_cursor, vdata);
        ਜੇ (mouse->cursor_visible) {
            Wayland_ShowCursor(mouse->cur_cursor);
        }
    }
}
#ਜੇ_ਅੰਤ // 0

ਖਾਲੀ Wayland_InitMouse(SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    mouse->CreateCursor = Wayland_CreateCursor;
    mouse->CreateAnimatedCursor = Wayland_CreateAnimatedCursor;
    mouse->CreateSystemCursor = Wayland_CreateSystemCursor;
    mouse->ShowCursor = Wayland_ShowCursor;
    mouse->FreeCursor = Wayland_FreeCursor;
    mouse->WarpMouse = Wayland_WarpMouseRelative;
    mouse->WarpMouseGlobal = Wayland_WarpMouseGlobal;
    mouse->ਸੈੱਟ_Relative_Mouse_ਬਹੁਲਕ = Wayland_ਸੈੱਟ_Relative_Mouse_ਬਹੁਲਕ;
    mouse->GetGlobalMouseState = Wayland_GetGlobalMouseState;

    mouse->have_explicit_warp_event = true;

    SDL_ਪ੍ਰਾਪਤੀ_Test_ਨਤੀਜਾ r = SDL_HITTEST_ਸਾਧਾਰਨ;
    ਜਦੋਂ (r <= SDL_HITTEST_RESIZE_ਖੱਬਾ) {
        ਚੋਣ (r) {
        ਹਾਲਤ SDL_HITTEST_ਸਾਧਾਰਨ:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            ਰੋਕੋ;
        ਹਾਲਤ SDL_HITTEST_DRAGGABLE:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            ਰੋਕੋ;
        ਹਾਲਤ SDL_HITTEST_RESIZE_TOPLEFT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE);
            ਰੋਕੋ;
        ਹਾਲਤ SDL_HITTEST_RESIZE_ਸਿਖਰ:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE);
            ਰੋਕੋ;
        ਹਾਲਤ SDL_HITTEST_RESIZE_TOPRIGHT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE);
            ਰੋਕੋ;
        ਹਾਲਤ SDL_HITTEST_RESIZE_ਸੱਜਾ:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE);
            ਰੋਕੋ;
        ਹਾਲਤ SDL_HITTEST_RESIZE_BOTTOMRIGHT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE);
            ਰੋਕੋ;
        ਹਾਲਤ SDL_HITTEST_RESIZE_BOTTOM:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE);
            ਰੋਕੋ;
        ਹਾਲਤ SDL_HITTEST_RESIZE_BOTTOMLEFT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE);
            ਰੋਕੋ;
        ਹਾਲਤ SDL_HITTEST_RESIZE_ਖੱਬਾ:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE);
            ਰੋਕੋ;
        }
        r++;
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_USE_LIBDBUS
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_ਅੰਕੜੇ *d = vd->ਅੰਦਰੂਨੀ;

    /* The D-Bus cursor properties are only needed when manually loading themes and system cursors.
     * If the cursor shape protocol is present, the compositor will handle it internally.
     */
    ਜੇ (!d->cursor_shape_manager) {
        Wayland_DBusInitCursorProperties(d);
    }
#ਜੇ_ਅੰਤ

    SDL_ਸੈੱਟ_Default_Cursor(Wayland_CreateDefaultCursor());
}

ਖਾਲੀ Wayland_FiniMouse(SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ)
{
    ਲਈ (ਪੂਰਨ i = 0; i < SDL_arraysize(sys_cursors); i++) {
        Wayland_FreeCursor(sys_cursors[i]);
        sys_cursors[i] = ਨਿਰਾ;
    }

    Wayland_FreeCursorThemes(ਅੰਕੜੇ);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_USE_LIBDBUS
    Wayland_DBus_ਅੰਤ_Cursor_Properties();
#ਜੇ_ਅੰਤ
}

ਖਾਲੀ Wayland_SeatResetCursor(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateResetCursor(&seat->ਸੂਚਕ_2.cursor_state);
}

ਖਾਲੀ Wayland_Seat_ਸੈੱਟ_Default_Cursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਸੂਚਕ_focus = seat->ਸੂਚਕ_2.focus;
    ਅਚਲ Wayland_ਸੂਚਕ_Object obj = {
        .wl_ਸੂਚਕ = seat->ਸੂਚਕ_2.wl_ਸੂਚਕ,
        .is_ਸੂਚਕ = true
    };

    Wayland_Cursor_State_ਸੈੱਟ_Cursor(&seat->ਸੂਚਕ_2.cursor_state, &obj, ਸੂਚਕ_focus, seat->ਸੂਚਕ_2.enter_serial, mouse->def_cursor);
}

ਖਾਲੀ Wayland_Seat_Update_ਸੂਚਕ_Cursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਸੂਚਕ_focus = seat->ਸੂਚਕ_2.focus;
    ਅਚਲ Wayland_ਸੂਚਕ_Object obj = {
        .wl_ਸੂਚਕ = seat->ਸੂਚਕ_2.wl_ਸੂਚਕ,
        .is_ਸੂਚਕ = true
    };

    ਜੇ (ਸੂਚਕ_focus) {
        ਜੇ (mouse->cursor_visible) {
            ਜੇ (!seat->ਸੂਚਕ_2.relative_ਸੂਚਕ || !mouse->relative_ਬਹੁਲਕ_hide_cursor) {
                ਅਚਲ SDL_ਪ੍ਰਾਪਤੀ_Test_ਨਤੀਜਾ rc = ਸੂਚਕ_focus->ਪ੍ਰਾਪਤੀ_test_ਨਤੀਜਾ;

                ਜੇ (seat->ਸੂਚਕ_2.relative_ਸੂਚਕ || rc == SDL_HITTEST_ਸਾਧਾਰਨ || rc == SDL_HITTEST_DRAGGABLE) {
                    Wayland_Cursor_State_ਸੈੱਟ_Cursor(&seat->ਸੂਚਕ_2.cursor_state, &obj, ਸੂਚਕ_focus, seat->ਸੂਚਕ_2.enter_serial, mouse->cur_cursor);
                } ਨਹੀਂਤਾਂ {
                    Wayland_Cursor_State_ਸੈੱਟ_Cursor(&seat->ਸੂਚਕ_2.cursor_state, &obj, ਸੂਚਕ_focus, seat->ਸੂਚਕ_2.enter_serial, sys_cursors[rc]);
                }
            } ਨਹੀਂਤਾਂ {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_Cursor_State_ਸੈੱਟ_Cursor(&seat->ਸੂਚਕ_2.cursor_state, &obj, ਸੂਚਕ_focus, seat->ਸੂਚਕ_2.enter_serial, ਨਿਰਾ);
            }
        } ਨਹੀਂਤਾਂ {
            Wayland_Cursor_State_ਸੈੱਟ_Cursor(&seat->ਸੂਚਕ_2.cursor_state, &obj, ਸੂਚਕ_focus, seat->ਸੂਚਕ_2.enter_serial, ਨਿਰਾ);
        }
    } ਨਹੀਂਤਾਂ {
        Wayland_CursorStateResetCursor(&seat->ਸੂਚਕ_2.cursor_state);
    }
}

ਖਾਲੀ Wayland_TabletToolUpdateCursor(SDL_WaylandPenTool *tool)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *tool_focus = tool->focus;
    ਅਚਲ Wayland_ਸੂਚਕ_Object obj = {
        .wl_tool = tool->wltool,
        .is_ਸੂਚਕ = false
    };

    ਜੇ (tool_focus) {
        ਜੇ (mouse->cursor_visible) {
            // Relative mode is only relevant if the tool sends pointer events.
            ਅਚਲ bool relative = mouse->pen_mouse_events && (tool_focus->sdlwindow->flags & SDL_ਖਿੜਕੀ_MOUSE_RELATIVE_ਬਹੁਲਕ);

            ਜੇ (!relative || !mouse->relative_ਬਹੁਲਕ_hide_cursor) {
                Wayland_Cursor_State_ਸੈੱਟ_Cursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, mouse->cur_cursor);
            } ਨਹੀਂਤਾਂ {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_Cursor_State_ਸੈੱਟ_Cursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, ਨਿਰਾ);
            }
        } ਨਹੀਂਤਾਂ {
            Wayland_Cursor_State_ਸੈੱਟ_Cursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, ਨਿਰਾ);
        }
    } ਨਹੀਂਤਾਂ {
        Wayland_CursorStateResetCursor(&tool->cursor_state);
    }
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_WAYLAND
