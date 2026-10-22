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

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WAYLAND

#ಅನ್ತರ್ಭಾವ <errno.h>

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../SDL_video_c.h"

#ಅನ್ತರ್ಭಾವ "../../core/unix/SDL_poll.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandvideo.h"
#ಅನ್ತರ್ಭಾವ "../SDL_pixels_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandevents_c.h"

#ಅನ್ತರ್ಭಾವ "wayland-cursor.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandmouse.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandshmbuffer.h"

#ಅನ್ತರ್ಭಾವ "cursor-shape-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "pointer-constraints-unstable-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "viewporter-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "pointer-warp-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "tablet-v2-client-protocol.h"

#ಅನ್ತರ್ಭಾವ "../../SDL_hints_c.h"

ಸ್ಥಿರ SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_ಎಡ + 1];

ಸ್ಥಿರ bool Wayland_ಗಣ_Relative_Mouse_ಬಹುಲಕ(bool enabled);

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    ಪೂರ್ಣಾಂಕ ಅಗಲ;
    ಪೂರ್ಣಾಂಕ ಎತ್ತರ;
    ರಚನೆ wl_ಬಫರ್ *ಬಫರ್_2;
} CustomCursorImage;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    // The base dimensions of the cursor.
    ಪೂರ್ಣಾಂಕ ಅಗಲ;
    ಪೂರ್ಣಾಂಕ ಎತ್ತರ;
    ಪೂರ್ಣಾಂಕ hot_x;
    ಪೂರ್ಣಾಂಕ hot_y;

    ಪೂರ್ಣಾಂಕ images_ಪ್ರತಿ_ಚೌಕಟ್ಟು;
    CustomCursorImage images[];
} Wayland_CustomCursor;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2;
    ರಚನೆ wl_list ಗಂಟು;
    ರಚನೆ wl_ಬಫರ್ *buffers[];
} Wayland_CachedSystemCursor;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    SDL_SystemCursor id;
    ರಚನೆ wl_list cursor_ಬಫರ್_cache;
} Wayland_SystemCursor;

ರಚನೆ SDL_Cursor_ದತ್ತಾಂಶ
{
    // Cursor animation data.
    Uint32 *ಚೌಕಟ್ಟು_durations_ms;
    Uint32 ಒಟ್ಟು_duration_ms;
    ಪೂರ್ಣಾಂಕ ಅಂಕೆ_ಚೌಕಟ್ಟುಗಳು;
    bool is_system_cursor;

    ಒಕ್ಕೂಟ
    {
        Wayland_CustomCursor custom;
        Wayland_SystemCursor system;
    } cursor_ದತ್ತಾಂಶ;
};

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ dbus_cursor_ಗಾತ್ರ;
ಸ್ಥಿರ ಅಕ್ಷರ *dbus_cursor_theme;

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_FreeCursorThemes(SDL_Video_ದತ್ತಾಂಶ *vdata)
{
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < vdata->ಅಂಕೆ_cursor_themes; i += 1) {
        WAYLAND_wl_cursor_theme_destroy(vdata->cursor_themes[i].theme);
    }
    vdata->ಅಂಕೆ_cursor_themes = 0;
    SDL_free(vdata->cursor_themes);
    vdata->cursor_themes = ಖಾಲಿ;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_USE_LIBDBUS

#ಅನ್ತರ್ಭಾವ "../../core/linux/SDL_dbus.h"

#ವ್ಯಾಖ್ಯಾನಿಸು CURSOR_ಗಂಟು        "org.freedesktop.portal.Desktop"
#ವ್ಯಾಖ್ಯಾನಿಸು CURSOR_ಮಾರ್ಗ        "/org/freedesktop/portal/desktop"
#ವ್ಯಾಖ್ಯಾನಿಸು CURSOR_INTERFACE   "org.freedesktop.portal.Settings"
#ವ್ಯಾಖ್ಯಾನಿಸು CURSOR_NAMESPACE   "org.gnome.desktop.interface"
#ವ್ಯಾಖ್ಯಾನಿಸು CURSOR_SIGNAL_NAME "SettingChanged"
#ವ್ಯಾಖ್ಯಾನಿಸು CURSOR_ಗಾತ್ರ_ಕೀಲಿ    "cursor-size"
#ವ್ಯಾಖ್ಯಾನಿಸು CURSOR_THEME_ಕೀಲಿ   "cursor-theme"

ಸ್ಥಿರ DBus_ಸಂದೇಶ *Wayland_ReadDBusProperty(SDL_DBusContext *dbus, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಕೀಲಿ)
{
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *iface = "org.gnome.desktop.interface";

    DBus_ಸಂದೇಶ *ಉತ್ತರ = ಖಾಲಿ;
    DBus_ಸಂದೇಶ *ಸಂದೇಶ_2 = dbus->ಸಂದೇಶ_new_ವಿಧಾನ_call(CURSOR_ಗಂಟು,
                                                     CURSOR_ಮಾರ್ಗ,
                                                     CURSOR_INTERFACE,
                                                     "Read"); //ವಿಧಾನ

    ಆದರೆ (ಸಂದೇಶ_2) {
        ಆದರೆ (dbus->ಸಂದೇಶ_append_ವಾದಗಳು(ಸಂದೇಶ_2, DBUS_TYPE_STRING, &iface, DBUS_TYPE_STRING, &ಕೀಲಿ, DBUS_TYPE_INVALID)) {
            ಉತ್ತರ = dbus->connection_send_with_ಉತ್ತರ_and_ಖಂಡ(dbus->session_conn, ಸಂದೇಶ_2, DBUS_TIMEOUT_USE_DEFAULT, ಖಾಲಿ);
        }
        dbus->ಸಂದೇಶ_unref(ಸಂದೇಶ_2);
    }

    ಹಿಂತಿರುಗಿ ಉತ್ತರ;
}

ಸ್ಥಿರ bool Wayland_Parse_DBus_ಉತ್ತರ(SDL_DBusContext *dbus, DBus_ಸಂದೇಶ *ಉತ್ತರ, ಪೂರ್ಣಾಂಕ type, ಶೂನ್ಯ *ಮೌಲ್ಯ)
{
    DBus_ಸಂದೇಶ_Iter iter[3];

    dbus->ಸಂದೇಶ_iter_init(ಉತ್ತರ, &iter[0]);
    ಆದರೆ (dbus->ಸಂದೇಶ_iter_get_arg_type(&iter[0]) != DBUS_TYPE_VARIANT) {
        ಹಿಂತಿರುಗಿ false;
    }

    dbus->ಸಂದೇಶ_iter_recurse(&iter[0], &iter[1]);
    ಆದರೆ (dbus->ಸಂದೇಶ_iter_get_arg_type(&iter[1]) != DBUS_TYPE_VARIANT) {
        ಹಿಂತಿರುಗಿ false;
    }

    dbus->ಸಂದೇಶ_iter_recurse(&iter[1], &iter[2]);
    ಆದರೆ (dbus->ಸಂದೇಶ_iter_get_arg_type(&iter[2]) != type) {
        ಹಿಂತಿರುಗಿ false;
    }

    dbus->ಸಂದೇಶ_iter_get_basic(&iter[2], ಮೌಲ್ಯ);

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ DBus_Handler_ಫಲಿತಾಂಶ Wayland_DBus_Cursor_ಸಂದೇಶ_Filter(DBusConnection *conn, DBus_ಸಂದೇಶ *ಸಂದೇಶ_2, ಶೂನ್ಯ *ದತ್ತಾಂಶ)
{
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    SDL_Video_ದತ್ತಾಂಶ *vdata = (SDL_Video_ದತ್ತಾಂಶ *)ದತ್ತಾಂಶ;

    ಆದರೆ (dbus->ಸಂದೇಶ_is_signal(ಸಂದೇಶ_2, CURSOR_INTERFACE, CURSOR_SIGNAL_NAME)) {
        DBus_ಸಂದೇಶ_Iter signal_iter, variant_iter;
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *namespace, *ಕೀಲಿ;

        dbus->ಸಂದೇಶ_iter_init(ಸಂದೇಶ_2, &signal_iter);
        // Check if the parameters are what we expect
        ಆದರೆ (dbus->ಸಂದೇಶ_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            ಹೋಗು not_our_signal;
        }
        dbus->ಸಂದೇಶ_iter_get_basic(&signal_iter, &namespace);
        ಆದರೆ (SDL_strcmp(CURSOR_NAMESPACE, namespace) != 0) {
            ಹೋಗು not_our_signal;
        }
        ಆದರೆ (!dbus->ಸಂದೇಶ_iter_ಮುಂದಿನ(&signal_iter)) {
            ಹೋಗು not_our_signal;
        }
        ಆದರೆ (dbus->ಸಂದೇಶ_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            ಹೋಗು not_our_signal;
        }
        dbus->ಸಂದೇಶ_iter_get_basic(&signal_iter, &ಕೀಲಿ);
        ಆದರೆ (SDL_strcmp(CURSOR_ಗಾತ್ರ_ಕೀಲಿ, ಕೀಲಿ) == 0) {
            ಪೂರ್ಣಾಂಕ new_cursor_ಗಾತ್ರ;

            ಆದರೆ (!dbus->ಸಂದೇಶ_iter_ಮುಂದಿನ(&signal_iter)) {
                ಹೋಗು not_our_signal;
            }
            ಆದರೆ (dbus->ಸಂದೇಶ_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                ಹೋಗು not_our_signal;
            }
            dbus->ಸಂದೇಶ_iter_recurse(&signal_iter, &variant_iter);
            ಆದರೆ (dbus->ಸಂದೇಶ_iter_get_arg_type(&variant_iter) != DBUS_TYPE_INT32) {
                ಹೋಗು not_our_signal;
            }
            dbus->ಸಂದೇಶ_iter_get_basic(&variant_iter, &new_cursor_ಗಾತ್ರ);

            ಆದರೆ (dbus_cursor_ಗಾತ್ರ != new_cursor_ಗಾತ್ರ) {
                dbus_cursor_ಗಾತ್ರ = new_cursor_ಗಾತ್ರ;
                SDL_RedrawCursor(); // Force cursor update
            }
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(CURSOR_THEME_ಕೀಲಿ, ಕೀಲಿ) == 0) {
            ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *new_cursor_theme = ಖಾಲಿ;

            ಆದರೆ (!dbus->ಸಂದೇಶ_iter_ಮುಂದಿನ(&signal_iter)) {
                ಹೋಗು not_our_signal;
            }
            ಆದರೆ (dbus->ಸಂದೇಶ_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                ಹೋಗು not_our_signal;
            }
            dbus->ಸಂದೇಶ_iter_recurse(&signal_iter, &variant_iter);
            ಆದರೆ (dbus->ಸಂದೇಶ_iter_get_arg_type(&variant_iter) != DBUS_TYPE_STRING) {
                ಹೋಗು not_our_signal;
            }
            dbus->ಸಂದೇಶ_iter_get_basic(&variant_iter, &new_cursor_theme);

            ಆದರೆ (!dbus_cursor_theme || !new_cursor_theme || SDL_strcmp(dbus_cursor_theme, new_cursor_theme) != 0) {
                SDL_free(dbus_cursor_theme);
                ಆದರೆ (new_cursor_theme) {
                    dbus_cursor_theme = SDL_strdup(new_cursor_theme);
                } ಇಲ್ಲದಿದ್ದರೆ {
                    dbus_cursor_theme = ಖಾಲಿ;
                }

                // Purge the current cached themes and force a cursor refresh.
                Wayland_FreeCursorThemes(vdata);
                SDL_RedrawCursor();
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಹೋಗು not_our_signal;
        }

        ಹಿಂತಿರುಗಿ DBUS_HANDLER_ಫಲಿತಾಂಶ_HANDLED;
    }

not_our_signal:
    ಹಿಂತಿರುಗಿ DBUS_HANDLER_ಫಲಿತಾಂಶ_NOT_YET_HANDLED;
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_DBusInitCursorProperties(SDL_Video_ದತ್ತಾಂಶ *vdata)
{
    DBus_ಸಂದೇಶ *ಉತ್ತರ;
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    bool ಕೂಡಿಸು_filter = false;

    ಆದರೆ (!dbus) {
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ ((ಉತ್ತರ = Wayland_ReadDBusProperty(dbus, CURSOR_ಗಾತ್ರ_ಕೀಲಿ))) {
        ಆದರೆ (Wayland_Parse_DBus_ಉತ್ತರ(dbus, ಉತ್ತರ, DBUS_TYPE_INT32, &dbus_cursor_ಗಾತ್ರ)) {
            ಕೂಡಿಸು_filter = true;
        }
        dbus->ಸಂದೇಶ_unref(ಉತ್ತರ);
    }

    ಆದರೆ ((ಉತ್ತರ = Wayland_ReadDBusProperty(dbus, CURSOR_THEME_ಕೀಲಿ))) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ತಾತ್ಕಾಲಿಕ = ಖಾಲಿ;
        ಆದರೆ (Wayland_Parse_DBus_ಉತ್ತರ(dbus, ಉತ್ತರ, DBUS_TYPE_STRING, &ತಾತ್ಕಾಲಿಕ)) {
            ಕೂಡಿಸು_filter = true;

            ಆದರೆ (ತಾತ್ಕಾಲಿಕ) {
                dbus_cursor_theme = SDL_strdup(ತಾತ್ಕಾಲಿಕ);
            }
        }
        dbus->ಸಂದೇಶ_unref(ಉತ್ತರ);
    }

    // Only add the filter if at least one of the settings we want is present.
    ಆದರೆ (ಕೂಡಿಸು_filter) {
        dbus->bus_ಕೂಡಿಸು_ಹೊಂದಿಕೆ(dbus->session_conn,
                            "type='signal', interface='" CURSOR_INTERFACE "',"
                            "member='" CURSOR_SIGNAL_NAME "', arg0='" CURSOR_NAMESPACE "'",
                            ಖಾಲಿ);
        dbus->connection_ಕೂಡಿಸು_filter(dbus->session_conn, &Wayland_DBus_Cursor_ಸಂದೇಶ_Filter, vdata, ಖಾಲಿ);
        dbus->connection_flush(dbus->session_conn);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_DBus_ಮುಕ್ತಾಯ_Cursor_Properties(ಶೂನ್ಯ)
{
    SDL_free(dbus_cursor_theme);
    dbus_cursor_theme = ಖಾಲಿ;
}

#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ರಚನೆ wl_ಬಫರ್ *Wayland_Cursor_State_Get_ಚೌಕಟ್ಟು(SDL_WaylandCursorState *state, ಪೂರ್ಣಾಂಕ ಚೌಕಟ್ಟು_ಸೂಚ್ಯಂಕ_2)
{
    SDL_Cursor_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = state->current_cursor;

    ಆದರೆ (ದತ್ತಾಂಶ) {
        ಆದರೆ (!ದತ್ತಾಂಶ->is_system_cursor) {
            ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ಸ್ಥಾನಾಂತರ_2 = ದತ್ತಾಂಶ->cursor_ದತ್ತಾಂಶ.custom.images_ಪ್ರತಿ_ಚೌಕಟ್ಟು * ಚೌಕಟ್ಟು_ಸೂಚ್ಯಂಕ_2;

            /* Find the closest image. Images that are larger than the
             * desired size are preferred over images that are smaller.
             */
            CustomCursorImage *closest = ಖಾಲಿ;
            ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ಗುರಿ_area = SDL_lround(ದತ್ತಾಂಶ->cursor_ದತ್ತಾಂಶ.custom.ಅಗಲ * ದತ್ತಾಂಶ->cursor_ದತ್ತಾಂಶ.custom.ಎತ್ತರ * state->scale);
            ಪೂರ್ಣಾಂಕ closest_area = 0;
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ದತ್ತಾಂಶ->cursor_ದತ್ತಾಂಶ.custom.images_ಪ್ರತಿ_ಚೌಕಟ್ಟು && closest_area < ಗುರಿ_area && ದತ್ತಾಂಶ->cursor_ದತ್ತಾಂಶ.custom.images[ಸ್ಥಾನಾಂತರ_2 + i].ಬಫರ್_2; ++i) {
                closest = &ದತ್ತಾಂಶ->cursor_ದತ್ತಾಂಶ.custom.images[ಸ್ಥಾನಾಂತರ_2 + i];
                closest_area = closest->ಅಗಲ * closest->ಎತ್ತರ;
            }

            ಹಿಂತಿರುಗಿ closest ? closest->ಬಫರ್_2 : ಖಾಲಿ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಹಿಂತಿರುಗಿ ((Wayland_CachedSystemCursor *)(state->system_cursor_handle))->buffers[ಚೌಕಟ್ಟು_ಸೂಚ್ಯಂಕ_2];
        }
    }

    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಸ್ಥಿರ ಶೂನ್ಯ cursor_ಚೌಕಟ್ಟು_ಮುಗಿದ(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_callback *cb, uint32_t ಸಮಯ);
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ wl_callback_listener cursor_ಚೌಕಟ್ಟು_listener = {
    cursor_ಚೌಕಟ್ಟು_ಮುಗಿದ
};

ಸ್ಥಿರ ಶೂನ್ಯ cursor_ಚೌಕಟ್ಟು_ಮುಗಿದ(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_callback *cb, uint32_t ಸಮಯ)
{
    SDL_WaylandCursorState *state = (SDL_WaylandCursorState *)ದತ್ತಾಂಶ;
    ಆದರೆ (!state->current_cursor) {
        ಹಿಂತಿರುಗಿ;
    }

    Uint32 *ಚೌಕಟ್ಟುಗಳು = state->current_cursor->ಚೌಕಟ್ಟು_durations_ms;
    SDL_Cursor_ದತ್ತಾಂಶ *c = state->current_cursor;

    ಸ್ಥಿರಾಂಕ Uint64 now = SDL_GetTicks();
    ಸ್ಥಿರಾಂಕ Uint32 elapsed = (now - state->ಕೊನೆಯ_ಚೌಕಟ್ಟು_callback_ಸಮಯ_ms) % c->ಒಟ್ಟು_duration_ms;
    Uint32 advance = 0;
    ಪೂರ್ಣಾಂಕ ಮುಂದಿನ = state->current_ಚೌಕಟ್ಟು;

    state->current_ಚೌಕಟ್ಟು_ಸಮಯ_ms += elapsed;

    // Calculate the next frame based on the elapsed duration.
    ಗಾಗಿ (Uint32 t = ಚೌಕಟ್ಟುಗಳು[ಮುಂದಿನ]; t <= state->current_ಚೌಕಟ್ಟು_ಸಮಯ_ms; t += ಚೌಕಟ್ಟುಗಳು[ಮುಂದಿನ]) {
        ಮುಂದಿನ = (ಮುಂದಿನ + 1) % c->ಅಂಕೆ_ಚೌಕಟ್ಟುಗಳು;
        advance = t;

        // Make sure we don't end up in an infinite loop if a cursor has frame durations of 0.
        ಆದರೆ (!ಚೌಕಟ್ಟುಗಳು[ಮುಂದಿನ]) {
            ನಿಲ್ಲಿಸು;
        }
    }

    wl_callback_destroy(cb);
    state->ಚೌಕಟ್ಟು_callback = ಖಾಲಿ;

    // Don't queue another callback if this frame time is infinite.
    ಆದರೆ (ಚೌಕಟ್ಟುಗಳು[ಮುಂದಿನ]) {
        state->ಚೌಕಟ್ಟು_callback = wl_surface_ಚೌಕಟ್ಟು(state->surface);
        wl_callback_ಕೂಡಿಸು_listener(state->ಚೌಕಟ್ಟು_callback, &cursor_ಚೌಕಟ್ಟು_listener, ದತ್ತಾಂಶ);
    }

    state->current_ಚೌಕಟ್ಟು_ಸಮಯ_ms -= advance;
    state->ಕೊನೆಯ_ಚೌಕಟ್ಟು_callback_ಸಮಯ_ms = now;
    state->current_ಚೌಕಟ್ಟು = ಮುಂದಿನ;

    ರಚನೆ wl_ಬಫರ್ *ಬಫರ್_2 = Wayland_Cursor_State_Get_ಚೌಕಟ್ಟು(state, ಮುಂದಿನ);
    wl_surface_attach(state->surface, ಬಫರ್_2, 0, 0);

    ಆದರೆ (wl_surface_get_ಆವೃತ್ತಿ(state->surface) >= WL_SURFACE_DAMAGE_ಬಫರ್_SINCE_ಆವೃತ್ತಿ) {
        wl_surface_damage_ಬಫರ್(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    } ಇಲ್ಲದಿದ್ದರೆ {
        wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    }
    wl_surface_commit(state->surface);
}

ಶೂನ್ಯ Wayland_Cursor_State_ಗಣ_ಚೌಕಟ್ಟು_Callback(SDL_WaylandCursorState *state, ಶೂನ್ಯ *userdata)
{
    SDL_Video_ದತ್ತಾಂಶ *viddata = SDL_GetVideoDevice()->ಆಂತರಿಕ;
    Wayland_ಬೀಗ_Event_Thread(viddata->event_thread_context);

    state->ಚೌಕಟ್ಟು_callback = wl_surface_ಚೌಕಟ್ಟು(state->surface);
    wl_callback_ಕೂಡಿಸು_listener(state->ಚೌಕಟ್ಟು_callback, &cursor_ಚೌಕಟ್ಟು_listener, userdata);

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

ಶೂನ್ಯ Wayland_Cursor_State_Destroy_ಚೌಕಟ್ಟು_Callback(SDL_WaylandCursorState *state)
{
    SDL_Video_ದತ್ತಾಂಶ *viddata = SDL_GetVideoDevice()->ಆಂತರಿಕ;
    Wayland_ಬೀಗ_Event_Thread(viddata->event_thread_context);

    ಆದರೆ (state->ಚೌಕಟ್ಟು_callback) {
        wl_callback_destroy(state->ಚೌಕಟ್ಟು_callback);
        state->ಚೌಕಟ್ಟು_callback = ಖಾಲಿ;
    }

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_CursorStateResetAnimationState(SDL_WaylandCursorState *state)
{
    state->ಕೊನೆಯ_ಚೌಕಟ್ಟು_callback_ಸಮಯ_ms = SDL_GetTicks();
    state->current_ಚೌಕಟ್ಟು_ಸಮಯ_ms = 0;
    state->current_ಚೌಕಟ್ಟು = 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_CursorStateResetAnimation(SDL_WaylandCursorState *state, bool ಬೀಗ_2)
{
    ಆದರೆ (ಬೀಗ_2) {
        SDL_Video_ದತ್ತಾಂಶ *viddata = SDL_GetVideoDevice()->ಆಂತರಿಕ;
        Wayland_ಬೀಗ_Event_Thread(viddata->event_thread_context);
        Wayland_CursorStateResetAnimationState(state);
        Wayland_UnlockEventThread(viddata->event_thread_context);
    } ಇಲ್ಲದಿದ್ದರೆ {
        Wayland_CursorStateResetAnimationState(state);
    }
}

ಶೂನ್ಯ Wayland_CursorStateRelease(SDL_WaylandCursorState *state)
{
    Wayland_Cursor_State_Destroy_ಚೌಕಟ್ಟು_Callback(state);
    ಆದರೆ (state->cursor_shape) {
        wp_cursor_shape_device_v1_destroy(state->cursor_shape);
    }
    ಆದರೆ (state->viewport) {
        wp_viewport_destroy(state->viewport);
    }
    ಆದರೆ (state->surface) {
        wl_surface_attach(state->surface, ಖಾಲಿ, 0, 0);
        wl_surface_commit(state->surface);
        wl_surface_destroy(state->surface);
    }

    SDL_zerop(state);
}

ಸ್ಥಿರ Wayland_CachedSystemCursor *Wayland_CacheSystemCursor(SDL_Cursor_ದತ್ತಾಂಶ *cdata, ರಚನೆ wl_cursor *cursor, ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2)
{
    Wayland_CachedSystemCursor *cache = ಖಾಲಿ;

    // Is this cursor already cached at the target scale?
    ಆದರೆ (!WAYLAND_wl_list_ಖಾಲಿಗಳು(&cdata->cursor_ದತ್ತಾಂಶ.system.cursor_ಬಫರ್_cache)) {
        Wayland_CachedSystemCursor *c = ಖಾಲಿ;
        wl_list_for_each (c, &cdata->cursor_ದತ್ತಾಂಶ.system.cursor_ಬಫರ್_cache, ಗಂಟು) {
            ಆದರೆ (c->ಗಾತ್ರ_2 == ಗಾತ್ರ_2) {
                cache = c;
                ನಿಲ್ಲಿಸು;
            }
        }
    }

    ಆದರೆ (!cache) {
        cache = SDL_calloc(1, ಗಾತ್ರ(Wayland_CachedSystemCursor) + (ಗಾತ್ರ(ರಚನೆ wl_ಬಫರ್ *) * cdata->ಅಂಕೆ_ಚೌಕಟ್ಟುಗಳು));

        cache->ಗಾತ್ರ_2 = ಗಾತ್ರ_2;
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < cdata->ಅಂಕೆ_ಚೌಕಟ್ಟುಗಳು; ++i) {
            cache->buffers[i] = WAYLAND_wl_cursor_image_get_ಬಫರ್(cursor->images[i]);
        }

        WAYLAND_wl_list_ಸೇರಿಸು(&cdata->cursor_ದತ್ತಾಂಶ.system.cursor_ಬಫರ್_cache, &cache->ಗಂಟು);
    }

    ಹಿಂತಿರುಗಿ cache;
}

ಸ್ಥಿರ bool Wayland_GetSystemCursor(SDL_Cursor_ದತ್ತಾಂಶ *cdata, SDL_WaylandCursorState *state, ಪೂರ್ಣಾಂಕ *dst_ಗಾತ್ರ, ಪೂರ್ಣಾಂಕ *hot_x, ಪೂರ್ಣಾಂಕ *hot_y)
{
    SDL_Video_ದತ್ತಾಂಶ *vdata = SDL_GetVideoDevice()->ಆಂತರಿಕ;
    ರಚನೆ wl_cursor_theme *theme = ಖಾಲಿ;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *css_name = "default";
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fallback_name = ಖಾಲಿ;
    ದ್ವಿಗುಣ scale_ಗುಣಕ_2 = state->scale;
    ಪೂರ್ಣಾಂಕ theme_ಗಾತ್ರ = dbus_cursor_ಗಾತ್ರ;

    // Fallback envvar if the DBus properties don't exist
    ಆದರೆ (theme_ಗಾತ್ರ <= 0) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *xcursor_ಗಾತ್ರ = SDL_getenv("XCURSOR_SIZE");
        ಆದರೆ (xcursor_ಗಾತ್ರ) {
            theme_ಗಾತ್ರ = SDL_atoi(xcursor_ಗಾತ್ರ);
        }
    }
    ಆದರೆ (theme_ಗಾತ್ರ <= 0) {
        theme_ಗಾತ್ರ = 24;
    }

    // First, find the appropriate theme based on the current scale...
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ scaled_ಗಾತ್ರ = (ಪೂರ್ಣಾಂಕ)SDL_lround(theme_ಗಾತ್ರ * scale_ಗುಣಕ_2);
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < vdata->ಅಂಕೆ_cursor_themes; ++i) {
        ಆದರೆ (vdata->cursor_themes[i].ಗಾತ್ರ_2 == scaled_ಗಾತ್ರ) {
            theme = vdata->cursor_themes[i].theme;
            ನಿಲ್ಲಿಸು;
        }
    }
    ಆದರೆ (!theme) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *xcursor_theme = dbus_cursor_theme;

        SDL_WaylandCursorTheme *new_cursor_themes = SDL_realloc(vdata->cursor_themes,
                                                                ಗಾತ್ರ(SDL_WaylandCursorTheme) * (vdata->ಅಂಕೆ_cursor_themes + 1));
        ಆದರೆ (!new_cursor_themes) {
            ಹಿಂತಿರುಗಿ false;
        }
        vdata->cursor_themes = new_cursor_themes;

        // Fallback envvar if the DBus properties don't exist
        ಆದರೆ (!xcursor_theme) {
            xcursor_theme = SDL_getenv("XCURSOR_THEME");
        }

        theme = WAYLAND_wl_cursor_theme_ತುಂಬು(xcursor_theme, scaled_ಗಾತ್ರ, vdata->shm);
        vdata->cursor_themes[vdata->ಅಂಕೆ_cursor_themes].ಗಾತ್ರ_2 = scaled_ಗಾತ್ರ;
        vdata->cursor_themes[vdata->ಅಂಕೆ_cursor_themes++].theme = theme;
    }

    css_name = SDL_GetCSSCursorName(cdata->cursor_ದತ್ತಾಂಶ.system.id, &fallback_name);
    ರಚನೆ wl_cursor *cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, css_name);
    ಆದರೆ (!cursor && fallback_name) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, fallback_name);
    }

    // Fallback to the default cursor if the chosen one wasn't found
    ಆದರೆ (!cursor) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, "default");
    }
    // Try the old X11 name as a last resort
    ಆದರೆ (!cursor) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, "left_ptr");
    }
    ಆದರೆ (!cursor) {
        ಹಿಂತಿರುಗಿ false;
    }

    // ... Set the cursor data, finally.
    cdata->ಅಂಕೆ_ಚೌಕಟ್ಟುಗಳು = cursor->image_ಎಣಿಕೆ_2;
    Wayland_CachedSystemCursor *c = Wayland_CacheSystemCursor(cdata, cursor, theme_ಗಾತ್ರ);
    state->system_cursor_handle = c;

    ಆದರೆ (cursor->image_ಎಣಿಕೆ_2 > 1 && !cdata->ಚೌಕಟ್ಟು_durations_ms) {
        cdata->ಒಟ್ಟು_duration_ms = 0;
        cdata->ಚೌಕಟ್ಟು_durations_ms = SDL_calloc(cursor->image_ಎಣಿಕೆ_2, ಗಾತ್ರ(Uint32));

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < cursor->image_ಎಣಿಕೆ_2; ++i) {
            cdata->ಚೌಕಟ್ಟು_durations_ms[i] = cursor->images[i]->delay;
            cdata->ಒಟ್ಟು_duration_ms += cursor->images[i]->delay;
        }
    }

    *dst_ಗಾತ್ರ = SDL_lround(cursor->images[0]->ಅಗಲ / state->scale);
    *hot_x = SDL_lround(cursor->images[0]->hotspot_x / state->scale);
    *hot_y = SDL_lround(cursor->images[0]->hotspot_y / state->scale);

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ surface_ವಿಂಗಡಿಸು_callback(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *a, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *b)
{
    ಸ್ಥಿರಾಂಕ SDL_Surface *s1 = *(ಸ್ಥಿರಾಂಕ SDL_Surface **)a;
    ಸ್ಥಿರಾಂಕ SDL_Surface *s2 = *(ಸ್ಥಿರಾಂಕ SDL_Surface **)b;

    ಹಿಂತಿರುಗಿ (s1->w * s1->h) <= (s2->w * s2->h) ? -1 : 1;
}

ಸ್ಥಿರ SDL_Cursor *Wayland_CreateAnimatedCursor(SDL_Cursor_ಚೌಕಟ್ಟು_Info *ಚೌಕಟ್ಟುಗಳು, ಪೂರ್ಣಾಂಕ ಚೌಕಟ್ಟು_ಎಣಿಕೆ, ಪೂರ್ಣಾಂಕ hot_x, ಪೂರ್ಣಾಂಕ hot_y)
{
    SDL_Cursor *cursor = SDL_calloc(1, ಗಾತ್ರ(*cursor));
    ಆದರೆ (!cursor) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    SDL_Cursor_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಖಾಲಿ;
    Wayland_SHMPool *shm_pool = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ pool_ಗಾತ್ರ = 0;
    ಪೂರ್ಣಾಂಕ max_images = 0;
    bool is_ರಾಶಿ = false;
    ರಚನೆ SurfaceArray
    {
        SDL_Surface **surfaces;
        ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2;
    } *surfaces = SDL_small_alloc(ರಚನೆ SurfaceArray, ಚೌಕಟ್ಟು_ಎಣಿಕೆ, &is_ರಾಶಿ);
    ಆದರೆ (!surfaces) {
        ಹೋಗು failed;
    }
    SDL_memset(surfaces, 0, ಗಾತ್ರ(ರಚನೆ SurfaceArray) * ಚೌಕಟ್ಟು_ಎಣಿಕೆ);

    // Calculate the total allocation size.
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಚೌಕಟ್ಟು_ಎಣಿಕೆ; ++i) {
        surfaces[i].surfaces = SDL_GetSurfaceImages(ಚೌಕಟ್ಟುಗಳು[i].surface, &surfaces[i].ಎಣಿಕೆ_2);
        ಆದರೆ (!surfaces[i].surfaces) {
            ಹೋಗು failed;
        }

        SDL_qsort(surfaces[i].surfaces, surfaces[i].ಎಣಿಕೆ_2, ಗಾತ್ರ(SDL_Surface *), surface_ವಿಂಗಡಿಸು_callback);
        max_images = SDL_max(max_images, surfaces[i].ಎಣಿಕೆ_2);
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < surfaces[i].ಎಣಿಕೆ_2; ++j) {
            pool_ಗಾತ್ರ += surfaces[i].surfaces[j]->w * surfaces[i].surfaces[j]->h * 4;
        }
    }

    ದತ್ತಾಂಶ = SDL_calloc(1, ಗಾತ್ರ(*ದತ್ತಾಂಶ) + (ಗಾತ್ರ(CustomCursorImage) * max_images * ಚೌಕಟ್ಟು_ಎಣಿಕೆ));
    ಆದರೆ (!ದತ್ತಾಂಶ) {
        ಹೋಗು failed;
    }

    ದತ್ತಾಂಶ->ಚೌಕಟ್ಟು_durations_ms = SDL_calloc(ಚೌಕಟ್ಟು_ಎಣಿಕೆ, ಗಾತ್ರ(Uint32));
    ಆದರೆ (!ದತ್ತಾಂಶ->ಚೌಕಟ್ಟು_durations_ms) {
        ಹೋಗು failed;
    }

    shm_pool = Wayland_AllocSHMPool(pool_ಗಾತ್ರ);
    ಆದರೆ (!shm_pool) {
        ಹೋಗು failed;
    }

    cursor->ಆಂತರಿಕ = ದತ್ತಾಂಶ;
    ದತ್ತಾಂಶ->cursor_ದತ್ತಾಂಶ.custom.ಅಗಲ = ಚೌಕಟ್ಟುಗಳು[0].surface->w;
    ದತ್ತಾಂಶ->cursor_ದತ್ತಾಂಶ.custom.ಎತ್ತರ = ಚೌಕಟ್ಟುಗಳು[0].surface->h;
    ದತ್ತಾಂಶ->cursor_ದತ್ತಾಂಶ.custom.hot_x = hot_x;
    ದತ್ತಾಂಶ->cursor_ದತ್ತಾಂಶ.custom.hot_y = hot_y;
    ದತ್ತಾಂಶ->cursor_ದತ್ತಾಂಶ.custom.images_ಪ್ರತಿ_ಚೌಕಟ್ಟು = max_images;
    ದತ್ತಾಂಶ->ಅಂಕೆ_ಚೌಕಟ್ಟುಗಳು = ಚೌಕಟ್ಟು_ಎಣಿಕೆ;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಚೌಕಟ್ಟು_ಎಣಿಕೆ; ++i) {
        ದತ್ತಾಂಶ->ಚೌಕಟ್ಟು_durations_ms[i] = ಚೌಕಟ್ಟುಗಳು[i].duration;
        ಆದರೆ (ದತ್ತಾಂಶ->ಒಟ್ಟು_duration_ms < SDL_MAX_UINT32) {
            ಆದರೆ (ದತ್ತಾಂಶ->ಚೌಕಟ್ಟು_durations_ms[i] > 0) {
                ದತ್ತಾಂಶ->ಒಟ್ಟು_duration_ms += ದತ್ತಾಂಶ->ಚೌಕಟ್ಟು_durations_ms[i];
            } ಇಲ್ಲದಿದ್ದರೆ {
                ದತ್ತಾಂಶ->ಒಟ್ಟು_duration_ms = SDL_MAX_UINT32;
            }
        }

        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ಸ್ಥಾನಾಂತರ_2 = i * max_images;
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < surfaces[i].ಎಣಿಕೆ_2; ++j) {
            SDL_Surface *surface = surfaces[i].surfaces[j];

            // Convert the surface format, if required.
            ಆದರೆ (surface->format != SDL_PIXELFORMAT_ARGB8888) {
                surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
                ಆದರೆ (!surface) {
                    ಹೋಗು failed;
                }
            }

            ದತ್ತಾಂಶ->cursor_ದತ್ತಾಂಶ.custom.images[ಸ್ಥಾನಾಂತರ_2 + j].ಅಗಲ = surface->w;
            ದತ್ತಾಂಶ->cursor_ದತ್ತಾಂಶ.custom.images[ಸ್ಥಾನಾಂತರ_2 + j].ಎತ್ತರ = surface->h;

            ಶೂನ್ಯ *buf_ದತ್ತಾಂಶ;
            ದತ್ತಾಂಶ->cursor_ದತ್ತಾಂಶ.custom.images[ಸ್ಥಾನಾಂತರ_2 + j].ಬಫರ್_2 = Wayland_Alloc_ಬಫರ್_From_Pool(shm_pool, surface->w, surface->h, &buf_ದತ್ತಾಂಶ);
            // Wayland requires premultiplied alpha for its surfaces.
            SDL_PremultiplyAlpha(surface->w, surface->h,
                                 surface->format, surface->pixels, surface->pitch,
                                 SDL_PIXELFORMAT_ARGB8888, buf_ದತ್ತಾಂಶ, surface->w * 4, true);

            ಆದರೆ (surface != surfaces[i].surfaces[j]) {
                SDL_DestroySurface(surface);
            }
        }

        // Free the memory returned by SDL_GetSurfaceImages().
        SDL_free(surfaces[i].surfaces);
    }

    SDL_small_free(surfaces, is_ರಾಶಿ);
    Wayland_ReleaseSHMPool(shm_pool);

    ಹಿಂತಿರುಗಿ cursor;

failed:
    Wayland_ReleaseSHMPool(shm_pool);
    ಆದರೆ (ದತ್ತಾಂಶ) {
        SDL_free(ದತ್ತಾಂಶ->ಚೌಕಟ್ಟು_durations_ms);
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ದತ್ತಾಂಶ->cursor_ದತ್ತಾಂಶ.custom.images_ಪ್ರತಿ_ಚೌಕಟ್ಟು * ಚೌಕಟ್ಟು_ಎಣಿಕೆ; ++i) {
            ಆದರೆ (ದತ್ತಾಂಶ->cursor_ದತ್ತಾಂಶ.custom.images[i].ಬಫರ್_2) {
                wl_ಬಫರ್_destroy(ದತ್ತಾಂಶ->cursor_ದತ್ತಾಂಶ.custom.images[i].ಬಫರ್_2);
            }
        }
    }

    SDL_free(ದತ್ತಾಂಶ);

    ಆದರೆ (surfaces) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಚೌಕಟ್ಟು_ಎಣಿಕೆ; ++i) {
            SDL_free(surfaces[i].surfaces);
        }
        SDL_small_free(surfaces, is_ರಾಶಿ);
    }

    SDL_free(cursor);

    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಸ್ಥಿರ SDL_Cursor *Wayland_CreateCursor(SDL_Surface *surface, ಪೂರ್ಣಾಂಕ hot_x, ಪೂರ್ಣಾಂಕ hot_y)
{
    SDL_Cursor_ಚೌಕಟ್ಟು_Info ಚೌಕಟ್ಟು = {
        surface, 0
    };

    ಹಿಂತಿರುಗಿ Wayland_CreateAnimatedCursor(&ಚೌಕಟ್ಟು, 1, hot_x, hot_y);
}

ಸ್ಥಿರ SDL_Cursor *Wayland_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = SDL_calloc(1, ಗಾತ್ರ(*cursor));

    ಆದರೆ (cursor) {
        SDL_Cursor_ದತ್ತಾಂಶ *cdata = SDL_calloc(1, ಗಾತ್ರ(*cdata));
        ಆದರೆ (!cdata) {
            SDL_free(cursor);
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }
        cursor->ಆಂತರಿಕ = cdata;

        WAYLAND_wl_list_init(&cdata->cursor_ದತ್ತಾಂಶ.system.cursor_ಬಫರ್_cache);
        cdata->cursor_ದತ್ತಾಂಶ.system.id = id;
        cdata->is_system_cursor = true;
    }

    ಹಿಂತಿರುಗಿ cursor;
}

ಸ್ಥಿರ SDL_Cursor *Wayland_CreateDefaultCursor(ಶೂನ್ಯ)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    ಹಿಂತಿರುಗಿ Wayland_CreateSystemCursor(id);
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_Free_Cursor_ದತ್ತಾಂಶ(SDL_Cursor_ದತ್ತಾಂಶ *d)
{
    SDL_VideoDevice *video_device = SDL_GetVideoDevice();
    SDL_Video_ದತ್ತಾಂಶ *video_ದತ್ತಾಂಶ = video_device->ಆಂತರಿಕ;
    SDL_WaylandSeat *seat;

    // Stop any frame callbacks and detach buffers associated with the cursor being destroyed.
    wl_list_for_each (seat, &video_ದತ್ತಾಂಶ->seat_list, link)
    {
        ಆದರೆ (seat->ಸೂಚಕ_2.cursor_state.current_cursor == d) {
            Wayland_Cursor_State_Destroy_ಚೌಕಟ್ಟು_Callback(&seat->ಸೂಚಕ_2.cursor_state);

            // Custom cursor buffers are about to be destroyed, so ensure they are detached.
            ಆದರೆ (!d->is_system_cursor && seat->ಸೂಚಕ_2.cursor_state.surface) {
                wl_surface_attach(seat->ಸೂಚಕ_2.cursor_state.surface, ಖಾಲಿ, 0, 0);
            }

            seat->ಸೂಚಕ_2.cursor_state.current_cursor = ಖಾಲಿ;
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            ಆದರೆ (tool->cursor_state.current_cursor == d) {
                Wayland_Cursor_State_Destroy_ಚೌಕಟ್ಟು_Callback(&tool->cursor_state);

                // Custom cursor buffers are about to be destroyed, so ensure they are detached.
                ಆದರೆ (!d->is_system_cursor && tool->cursor_state.surface) {
                    wl_surface_attach(seat->ಸೂಚಕ_2.cursor_state.surface, ಖಾಲಿ, 0, 0);
                }

                tool->cursor_state.current_cursor = ಖಾಲಿ;
            }
        }
    }

    ಆದರೆ (d->is_system_cursor) {
        Wayland_CachedSystemCursor *c, *ತಾತ್ಕಾಲಿಕ;
        wl_list_for_each_ಸುರಕ್ಷಿತ(c, ತಾತ್ಕಾಲಿಕ, &d->cursor_ದತ್ತಾಂಶ.system.cursor_ಬಫರ್_cache, ಗಂಟು) {
            SDL_free(c);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < d->ಅಂಕೆ_ಚೌಕಟ್ಟುಗಳು * d->cursor_ದತ್ತಾಂಶ.custom.images_ಪ್ರತಿ_ಚೌಕಟ್ಟು; ++i) {
            ಆದರೆ (d->cursor_ದತ್ತಾಂಶ.custom.images[i].ಬಫರ್_2) {
                wl_ಬಫರ್_destroy(d->cursor_ದತ್ತಾಂಶ.custom.images[i].ಬಫರ್_2);
            }
        }
    }

    SDL_free(d->ಚೌಕಟ್ಟು_durations_ms);
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_FreeCursor(SDL_Cursor *cursor)
{
    ಆದರೆ (!cursor) {
        ಹಿಂತಿರುಗಿ;
    }

    // Probably not a cursor we own
    ಆದರೆ (!cursor->ಆಂತರಿಕ) {
        ಹಿಂತಿರುಗಿ;
    }

    Wayland_Free_Cursor_ದತ್ತಾಂಶ(cursor->ಆಂತರಿಕ);

    SDL_free(cursor->ಆಂತರಿಕ);
    SDL_free(cursor);
}

ಸ್ಥಿರ ಎಣಿಕೆ wp_cursor_shape_device_v1_shape Wayland_GetSystemCursorShape(SDL_SystemCursor id)
{
    Uint32 shape;

    ಆಯ್ಕೆ (id) {
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_DEFAULT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ಪಠ್ಯ:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ಪಠ್ಯ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_WAIT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_WAIT;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_CROSSHAIR:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CROSSHAIR;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ಪ್ರಗತಿ:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ಪ್ರಗತಿ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NWSE_RESIZE;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_NESW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NESW_RESIZE;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_EW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_EW_RESIZE;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_NS_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NS_RESIZE;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_MOVE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_MOVE;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NOT_ALLOWED;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ಸೂಚಕ:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ಸೂಚಕ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_NW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NW_RESIZE;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_N_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_N_RESIZE;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_NE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NE_RESIZE;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_E_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_E_RESIZE;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_SE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_SE_RESIZE;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_S_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_S_RESIZE;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_SW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_SW_RESIZE;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_W_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_W_RESIZE;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CONTEXT_MENU;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_HELP:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_HELP;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_CELL:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CELL;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_VERTICAL_ಪಠ್ಯ:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_VERTICAL_ಪಠ್ಯ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ALIAS:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ALIAS;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_COPY:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_COPY;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_NO_DROP:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NO_DROP;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_GRAB:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_GRAB;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_GRABBING:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_GRABBING;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ಲಂಬಸಾಲು_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ಲಂಬಸಾಲು_RESIZE;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ಅಡ್ಡಸಾಲು_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ಅಡ್ಡಸಾಲು_RESIZE;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ALL_SCROLL;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ZOOM_ಒಳ:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_ಒಳ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ZOOM_ಹೊರಹೋಗು:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_ಹೊರಹೋಗು;
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        SDL_assert(0); // Should never be here...
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
    }

    ಹಿಂತಿರುಗಿ shape;
}

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Wayland_ಸೂಚಕ_Object
{
    ಒಕ್ಕೂಟ
    {
        ರಚನೆ wl_ಸೂಚಕ *wl_ಸೂಚಕ;
        ರಚನೆ zwp_tablet_tool_v2 *wl_tool;
    };

    bool is_ಸೂಚಕ;
} Wayland_ಸೂಚಕ_Object;

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_Cursor_State_ಗಣ_Cursor(SDL_WaylandCursorState *state, ಸ್ಥಿರಾಂಕ Wayland_ಸೂಚಕ_Object *obj, SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *focus, Uint32 serial, SDL_Cursor *cursor)
{
    SDL_Video_ದತ್ತಾಂಶ *viddata = SDL_GetVideoDevice()->ಆಂತರಿಕ;
    SDL_Cursor_ದತ್ತಾಂಶ *cursor_ದತ್ತಾಂಶ = cursor ? cursor->ಆಂತರಿಕ : ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ dst_ಅಗಲ = 0;
    ಪೂರ್ಣಾಂಕ dst_ಎತ್ತರ = 0;
    ಪೂರ್ಣಾಂಕ hot_x;
    ಪೂರ್ಣಾಂಕ hot_y;

    // Stop the frame callback for old animated cursors.
    ಆದರೆ (cursor_ದತ್ತಾಂಶ != state->current_cursor) {
        Wayland_Cursor_State_Destroy_ಚೌಕಟ್ಟು_Callback(state);
    }

    ಆದರೆ (cursor) {
        ಆದರೆ (cursor_ದತ್ತಾಂಶ == state->current_cursor && state->current_ಚೌಕಟ್ಟು >= 0) {
            // Restart the animation sequence if the cursor didn't change.
            ಆದರೆ (cursor_ದತ್ತಾಂಶ->ಅಂಕೆ_ಚೌಕಟ್ಟುಗಳು > 1) {
                Wayland_CursorStateResetAnimation(state, true);
            }

            ಹಿಂತಿರುಗಿ;
        }

        ಆದರೆ (cursor_ದತ್ತಾಂಶ->is_system_cursor) {
            // If the cursor shape protocol is supported, the compositor will draw nicely scaled cursors for us, so nothing more to do.
            ಆದರೆ (state->cursor_shape) {
                // Don't need the surface or viewport if using the cursor shape protocol.
                ಆದರೆ (state->surface) {
                    wl_surface_attach(state->surface, ಖಾಲಿ, 0, 0);
                    wl_surface_commit(state->surface);

                    ಆದರೆ (obj->is_ಸೂಚಕ) {
                        wl_ಸೂಚಕ_ಗಣ_cursor(obj->wl_ಸೂಚಕ, serial, ಖಾಲಿ, 0, 0);
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        zwp_tablet_tool_v2_ಗಣ_cursor(obj->wl_tool, serial, ಖಾಲಿ, 0, 0);
                    }

                    ಆದರೆ (state->viewport) {
                        wp_viewport_destroy(state->viewport);
                        state->viewport = ಖಾಲಿ;
                    }

                    wl_surface_destroy(state->surface);
                    state->surface = ಖಾಲಿ;
                }

                ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ wp_cursor_shape_device_v1_shape shape = Wayland_GetSystemCursorShape(cursor_ದತ್ತಾಂಶ->cursor_ದತ್ತಾಂಶ.system.id);
                wp_cursor_shape_device_v1_ಗಣ_shape(state->cursor_shape, serial, shape);
                state->current_cursor = cursor_ದತ್ತಾಂಶ;
                state->current_ಚೌಕಟ್ಟು = 0;

                ಹಿಂತಿರುಗಿ;
            }

            // If viewports aren't available, the scale is always 1.0.
            state->scale = viddata->viewporter && focus ? focus->scale_ಗುಣಕ_2 : 1.0;
            ಆದರೆ (!Wayland_GetSystemCursor(cursor_ದತ್ತಾಂಶ, state, &dst_ಅಗಲ, &hot_x, &hot_y)) {
                ಹಿಂತಿರುಗಿ;
            }

            dst_ಎತ್ತರ = dst_ಅಗಲ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            /* If viewports aren't available, the scale is always 1.0.
             *
             * If the pointer scale values are 1.0, the preferred backing buffer scale is the window scale.
             *
             * If the pointer is scaled, the dimensions are scaled by the pointer scale, so custom cursors will be scaled
             * relative to the viewport size.
             */
            ಆದರೆ (!focus || (focus->ಸೂಚಕ_scale.x == 1.0 && focus->ಸೂಚಕ_scale.y == 1.0)) {
                state->scale = viddata->viewporter && focus ? focus->scale_ಗುಣಕ_2 : 1.0;
                dst_ಅಗಲ = cursor_ದತ್ತಾಂಶ->cursor_ದತ್ತಾಂಶ.custom.ಅಗಲ;
                dst_ಎತ್ತರ = cursor_ದತ್ತಾಂಶ->cursor_ದತ್ತಾಂಶ.custom.ಎತ್ತರ;
                hot_x = cursor_ದತ್ತಾಂಶ->cursor_ದತ್ತಾಂಶ.custom.hot_x;
                hot_y = cursor_ದತ್ತಾಂಶ->cursor_ದತ್ತಾಂಶ.custom.hot_y;
            } ಇಲ್ಲದಿದ್ದರೆ {
                // The preferred buffer scale is the inverse of the pointer scale.
                state->scale = 1.0 / SDL_min(focus->ಸೂಚಕ_scale.x, focus->ಸೂಚಕ_scale.y);
                dst_ಅಗಲ = SDL_max((ಪೂರ್ಣಾಂಕ)SDL_lround((ದ್ವಿಗುಣ)cursor_ದತ್ತಾಂಶ->cursor_ದತ್ತಾಂಶ.custom.ಅಗಲ / focus->ಸೂಚಕ_scale.x), 1);
                dst_ಎತ್ತರ = SDL_max((ಪೂರ್ಣಾಂಕ)SDL_lround((ದ್ವಿಗುಣ)cursor_ದತ್ತಾಂಶ->cursor_ದತ್ತಾಂಶ.custom.ಎತ್ತರ / focus->ಸೂಚಕ_scale.y), 1);
                hot_x = (ಪೂರ್ಣಾಂಕ)SDL_lround((ದ್ವಿಗುಣ)cursor_ದತ್ತಾಂಶ->cursor_ದತ್ತಾಂಶ.custom.hot_x / focus->ಸೂಚಕ_scale.x);
                hot_y = (ಪೂರ್ಣಾಂಕ)SDL_lround((ದ್ವಿಗುಣ)cursor_ದತ್ತಾಂಶ->cursor_ದತ್ತಾಂಶ.custom.hot_y / focus->ಸೂಚಕ_scale.y);
            }

        }

        state->current_cursor = cursor_ದತ್ತಾಂಶ;

        ಆದರೆ (!state->surface) {
            ರಚನೆ wl_compositor *compositor_wrapper = Wayland_CreateEventThreadProxyWrapper(viddata->event_thread_context, viddata->compositor);
            state->surface = wl_compositor_create_surface(compositor_wrapper);
            WAYLAND_wl_proxy_wrapper_destroy(compositor_wrapper);
        }

        ರಚನೆ wl_ಬಫರ್ *ಬಫರ್_2 = Wayland_Cursor_State_Get_ಚೌಕಟ್ಟು(state, 0);
        wl_surface_attach(state->surface, ಬಫರ್_2, 0, 0);
        state->current_ಚೌಕಟ್ಟು = 0;

        ಆದರೆ (state->scale != 1.0) {
            ಆದರೆ (!state->viewport) {
                state->viewport = wp_viewporter_get_viewport(viddata->viewporter, state->surface);
            }

            wp_viewport_ಗಣ_ಮೂಲ(state->viewport, wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1));
            wp_viewport_ಗಣ_destination(state->viewport, dst_ಅಗಲ, dst_ಎತ್ತರ);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (state->viewport) {
            wp_viewport_destroy(state->viewport);
            state->viewport = ಖಾಲಿ;
        }

        ಆದರೆ (obj->is_ಸೂಚಕ) {
            wl_ಸೂಚಕ_ಗಣ_cursor(obj->wl_ಸೂಚಕ, serial, state->surface, hot_x, hot_y);
        } ಇಲ್ಲದಿದ್ದರೆ {
            zwp_tablet_tool_v2_ಗಣ_cursor(obj->wl_tool, serial, state->surface, hot_x, hot_y);
        }

        ಆದರೆ (wl_surface_get_ಆವೃತ್ತಿ(state->surface) >= WL_SURFACE_DAMAGE_ಬಫರ್_SINCE_ಆವೃತ್ತಿ) {
            wl_surface_damage_ಬಫರ್(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        } ಇಲ್ಲದಿದ್ದರೆ {
            wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        }

        // If more than one frame is available, create a frame callback to run the animation.
        ಆದರೆ (cursor_ದತ್ತಾಂಶ->ಅಂಕೆ_ಚೌಕಟ್ಟುಗಳು > 1) {
            Wayland_CursorStateResetAnimation(state, false);
            Wayland_Cursor_State_ಗಣ_ಚೌಕಟ್ಟು_Callback(state, state);
        }

        wl_surface_commit(state->surface);
    } ಇಲ್ಲದಿದ್ದರೆ {
        Wayland_Cursor_State_Destroy_ಚೌಕಟ್ಟು_Callback(state);
        state->current_cursor = ಖಾಲಿ;

        ಆದರೆ (state->surface) {
            wl_surface_attach(state->surface, ಖಾಲಿ, 0, 0);
            wl_surface_commit(state->surface);
        }

        ಆದರೆ (obj->is_ಸೂಚಕ) {
            wl_ಸೂಚಕ_ಗಣ_cursor(obj->wl_ಸೂಚಕ, serial, ಖಾಲಿ, 0, 0);
        } ಇಲ್ಲದಿದ್ದರೆ {
            zwp_tablet_tool_v2_ಗಣ_cursor(obj->wl_tool, serial, ಖಾಲಿ, 0, 0);
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_CursorStateResetCursor(SDL_WaylandCursorState *state)
{
    // Stop the frame callback and set the reset status.
    Wayland_Cursor_State_Destroy_ಚೌಕಟ್ಟು_Callback(state);
    state->current_ಚೌಕಟ್ಟು = -1;
}

ಶೂನ್ಯ Wayland_Display_Update_ಸೂಚಕ_Focused_Scale(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *updated_ಕಿಟಕಿ)
{
    SDL_Video_ದತ್ತಾಂಶ *viddata = updated_ಕಿಟಕಿ->wayland_ದತ್ತಾಂಶ;
    SDL_WaylandSeat *seat;
    ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ new_scale = SDL_min(updated_ಕಿಟಕಿ->ಸೂಚಕ_scale.x, updated_ಕಿಟಕಿ->ಸೂಚಕ_scale.y);

    wl_list_for_each (seat, &viddata->seat_list, link) {
        ಆದರೆ (seat->ಸೂಚಕ_2.focus == updated_ಕಿಟಕಿ) {
            SDL_WaylandCursorState *state = &seat->ಸೂಚಕ_2.cursor_state;
            ಆದರೆ (state->current_cursor && !state->current_cursor->is_system_cursor && state->scale != new_scale) {
                Wayland_CursorStateResetCursor(state);
                Wayland_Seat_Update_ಸೂಚಕ_Cursor(seat);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            ಆದರೆ (tool->focus == updated_ಕಿಟಕಿ) {
                SDL_WaylandCursorState *state = &tool->cursor_state;
                ಆದರೆ (state->current_cursor && !state->current_cursor->is_system_cursor && state->scale != new_scale) {
                    Wayland_CursorStateResetCursor(&tool->cursor_state);
                    Wayland_TabletToolUpdateCursor(tool);
                }
            }
        }
    }
}

ಸ್ಥಿರ bool Wayland_ShowCursor(SDL_Cursor *cursor)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_ದತ್ತಾಂಶ *d = vd->ಆಂತರಿಕ;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WaylandSeat *seat;
    Wayland_ಸೂಚಕ_Object obj;

    wl_list_for_each (seat, &d->seat_list, link) {
        ಆದರೆ (seat->ಸೂಚಕ_2.wl_ಸೂಚಕ) {
            obj.wl_ಸೂಚಕ = seat->ಸೂಚಕ_2.wl_ಸೂಚಕ;
            obj.is_ಸೂಚಕ = true;
            ಆದರೆ (mouse->focus && mouse->focus->ಆಂತರಿಕ == seat->ಸೂಚಕ_2.focus) {
                Wayland_Cursor_State_ಗಣ_Cursor(&seat->ಸೂಚಕ_2.cursor_state, &obj, seat->ಸೂಚಕ_2.focus, seat->ಸೂಚಕ_2.enter_serial, cursor);
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!seat->ಸೂಚಕ_2.focus) {
                Wayland_CursorStateResetCursor(&seat->ಸೂಚಕ_2.cursor_state);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each(tool, &seat->tablet.tool_list, link) {
            obj.wl_tool = tool->wltool;
            obj.is_ಸೂಚಕ = false;

            /* The current cursor is explicitly set on tablet tools, as there may be no pointer device, or
             * the pointer may not have focus, which would instead cause the default cursor to be set.
             */
            ಆದರೆ (tool->focus && (!mouse->focus || mouse->focus->ಆಂತರಿಕ == tool->focus)) {
                Wayland_Cursor_State_ಗಣ_Cursor(&tool->cursor_state, &obj, tool->focus, tool->proximity_serial, mouse->cur_cursor);
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!tool->focus) {
                Wayland_CursorStateResetCursor(&tool->cursor_state);
            }
        }
    }

    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ Wayland_SeatWarpMouse(SDL_WaylandSeat *seat, SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ, ದಶಮಾಂಶ x, ದಶಮಾಂಶ y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_ದತ್ತಾಂಶ *d = vd->ಆಂತರಿಕ;

    ಆದರೆ (seat->ಸೂಚಕ_2.wl_ಸೂಚಕ) {
        ಆದರೆ (d->wp_ಸೂಚಕ_warp_v1) {
            // It's a protocol error to warp the pointer outside of the surface, so clamp the position.
            ಸ್ಥಿರಾಂಕ wl_fixed_t f_x = wl_fixed_from_double(SDL_clamp(x / ಕಿಟಕಿ->ಸೂಚಕ_scale.x, 0, ಕಿಟಕಿ->current.logical_ಅಗಲ));
            ಸ್ಥಿರಾಂಕ wl_fixed_t f_y = wl_fixed_from_double(SDL_clamp(y / ಕಿಟಕಿ->ಸೂಚಕ_scale.y, 0, ಕಿಟಕಿ->current.logical_ಎತ್ತರ));
            wp_ಸೂಚಕ_warp_v1_warp_ಸೂಚಕ(d->wp_ಸೂಚಕ_warp_v1, ಕಿಟಕಿ->surface, seat->ಸೂಚಕ_2.wl_ಸೂಚಕ, f_x, f_y, seat->ಸೂಚಕ_2.enter_serial);
        } ಇಲ್ಲದಿದ್ದರೆ {
            bool update_grabs = false;

            // Pointers can only have one confinement type active on a surface at one time.
            ಆದರೆ (seat->ಸೂಚಕ_2.confined_ಸೂಚಕ) {
                zwp_confined_ಸೂಚಕ_v1_destroy(seat->ಸೂಚಕ_2.confined_ಸೂಚಕ);
                seat->ಸೂಚಕ_2.confined_ಸೂಚಕ = ಖಾಲಿ;
                update_grabs = true;
            }
            ಆದರೆ (seat->ಸೂಚಕ_2.locked_ಸೂಚಕ) {
                zwp_locked_ಸೂಚಕ_v1_destroy(seat->ಸೂಚಕ_2.locked_ಸೂಚಕ);
                seat->ಸೂಚಕ_2.locked_ಸೂಚಕ = ಖಾಲಿ;
                update_grabs = true;
            }

            /* The pointer confinement protocol allows setting a hint to warp the pointer,
             * but only when the pointer is locked.
             *
             * Lock the pointer, set the position hint, unlock, and hope for the best.
             */
            ರಚನೆ zwp_locked_ಸೂಚಕ_v1 *warp_ಬೀಗ =
                zwp_ಸೂಚಕ_constraints_v1_ಬೀಗ_ಸೂಚಕ(d->ಸೂಚಕ_constraints, ಕಿಟಕಿ->surface,
                                                        seat->ಸೂಚಕ_2.wl_ಸೂಚಕ, ಖಾಲಿ,
                                                        ZWP_ಸೂಚಕ_CONSTRAINTS_V1_LIFETIME_ONESHOT);

            ಸ್ಥಿರಾಂಕ wl_fixed_t f_x = wl_fixed_from_double(x / ಕಿಟಕಿ->ಸೂಚಕ_scale.x);
            ಸ್ಥಿರಾಂಕ wl_fixed_t f_y = wl_fixed_from_double(y / ಕಿಟಕಿ->ಸೂಚಕ_scale.y);
            zwp_locked_ಸೂಚಕ_v1_ಗಣ_cursor_position_hint(warp_ಬೀಗ, f_x, f_y);
            wl_surface_commit(ಕಿಟಕಿ->surface);

            zwp_locked_ಸೂಚಕ_v1_destroy(warp_ಬೀಗ);

            ಆದರೆ (update_grabs) {
                Wayland_Seat_Update_ಸೂಚಕ_Grab(seat);
            }
        }

        ಆದರೆ (wl_ಸೂಚಕ_get_ಆವೃತ್ತಿ(seat->ಸೂಚಕ_2.wl_ಸೂಚಕ) < WL_ಸೂಚಕ_WARP_SINCE_ಆವೃತ್ತಿ) {
            SDL_SendMouseWarp(0, ಕಿಟಕಿ->sdlwindow, seat->ಸೂಚಕ_2.sdl_id, x, y);
        }
    }
}

ಸ್ಥಿರ bool Wayland_WarpMouseRelative(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ದಶಮಾಂಶ x, ದಶಮಾಂಶ y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_ದತ್ತಾಂಶ *d = vd->ಆಂತರಿಕ;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = ಕಿಟಕಿ->ಆಂತರಿಕ;
    SDL_WaylandSeat *seat;

    ಆದರೆ (d->wp_ಸೂಚಕ_warp_v1 || d->ಸೂಚಕ_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            ಆದರೆ (wind == seat->ಸೂಚಕ_2.focus) {
                Wayland_SeatWarpMouse(seat, wind, x, y);
            }
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool Wayland_WarpMouseGlobal(ದಶಮಾಂಶ x, ದಶಮಾಂಶ y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_ದತ್ತಾಂಶ *d = vd->ಆಂತರಿಕ;
    SDL_WaylandSeat *seat;

    ಆದರೆ (d->wp_ಸೂಚಕ_warp_v1 || d->ಸೂಚಕ_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = seat->ಸೂಚಕ_2.focus ? seat->ಸೂಚಕ_2.focus : seat->keyboard.focus;

            // If the client wants the coordinates warped to within a focused window, just convert the coordinates to relative.
            ಆದರೆ (wind) {
                SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = wind->sdlwindow;

                ಪೂರ್ಣಾಂಕ abs_x, abs_y;
                SDL_Relative_ಗಮ್ಯ_Global_For_ಕಿಟಕಿ(ಕಿಟಕಿ, ಕಿಟಕಿ->x, ಕಿಟಕಿ->y, &abs_x, &abs_y);

                ಸ್ಥಿರಾಂಕ SDL_FPoint p = { x, y };
                ಸ್ಥಿರಾಂಕ SDL_FRect r = { abs_x, abs_y, ಕಿಟಕಿ->w, ಕಿಟಕಿ->h };

                // Try to warp the cursor if the point is within the seat's focused window.
                ಆದರೆ (SDL_ಬಿಂದು_ಒಳ_Rect_Float(&p, &r)) {
                    Wayland_SeatWarpMouse(seat, wind, p.x - abs_x, p.y - abs_y);
                }
            }
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool Wayland_ಗಣ_Relative_Mouse_ಬಹುಲಕ(bool enabled)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = vd->ಆಂತರಿಕ;

    // Relative mode requires both the relative motion and pointer confinement protocols.
    ಆದರೆ (!ದತ್ತಾಂಶ->relative_ಸೂಚಕ_manager) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Failed to enable relative mode: compositor lacks support for the required zwp_relative_pointer_manager_v1 protocol");
    }
    ಆದರೆ (!ದತ್ತಾಂಶ->ಸೂಚಕ_constraints) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Failed to enable relative mode: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }

    // Windows have a relative mode flag, so just update the grabs on a state change.
    Wayland_Display_Update_ಸೂಚಕ_Grabs(ದತ್ತಾಂಶ, ಖಾಲಿ);
    ಹಿಂತಿರುಗಿ true;
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
ಸ್ಥಿರ SDL_MouseButtonFlags SDLCALL Wayland_GetGlobalMouseState(ದಶಮಾಂಶ *x, ದಶಮಾಂಶ *y)
{
    ಸ್ಥಿರಾಂಕ SDL_Mouse *mouse = SDL_GetMouse();
    SDL_MouseButtonFlags ಫಲಿತಾಂಶ = 0;

    // If there is no window with mouse focus, we have no idea what the actual position or button state is.
    ಆದರೆ (mouse->focus) {
        SDL_Video_ದತ್ತಾಂಶ *video_ದತ್ತಾಂಶ = SDL_GetVideoDevice()->ಆಂತರಿಕ;
        SDL_WaylandSeat *seat;
        ಪೂರ್ಣಾಂಕ off_x, off_y;
        SDL_Relative_ಗಮ್ಯ_Global_For_ಕಿಟಕಿ(mouse->focus, mouse->focus->x, mouse->focus->y, &off_x, &off_y);
        *x = mouse->x + off_x;
        *y = mouse->y + off_y;

        // Query the buttons from the seats directly, as this may be called from within a hit test handler.
        wl_list_for_each (seat, &video_ದತ್ತಾಂಶ->seat_list, link) {
            ಫಲಿತಾಂಶ |= seat->ಸೂಚಕ_2.buttons_pressed;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        *x = 0.f;
        *y = 0.f;
    }

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

#ಆದರೆ 0  // TODO RECONNECT: See waylandvideo.c for more information!
ಸ್ಥಿರ ಶೂನ್ಯ Wayland_RecreateCursor(SDL_Cursor *cursor, SDL_Video_ದತ್ತಾಂಶ *vdata)
{
    SDL_Cursor_ದತ್ತಾಂಶ *cdata = cursor->ಆಂತರಿಕ;

    // Probably not a cursor we own
    ಆದರೆ (cdata == ಖಾಲಿ) {
        ಹಿಂತಿರುಗಿ;
    }

    Wayland_Free_Cursor_ದತ್ತಾಂಶ(cdata);

    // We're not currently freeing this, so... yolo?
    ಆದರೆ (cdata->shm_ದತ್ತಾಂಶ != ಖಾಲಿ) {
        ಶೂನ್ಯ *old_ದತ್ತಾಂಶ_ಸೂಚಕ = cdata->shm_ದತ್ತಾಂಶ;
        ಪೂರ್ಣಾಂಕ stride = cdata->w * 4;

        create_ಬಫರ್_from_shm(cdata, cdata->w, cdata->h, WL_SHM_FORMAT_ARGB8888);

        SDL_memcpy(cdata->shm_ದತ್ತಾಂಶ, old_ದತ್ತಾಂಶ_ಸೂಚಕ, stride * cdata->h);
    }
    cdata->surface = wl_compositor_create_surface(vdata->compositor);
    wl_surface_ಗಣ_user_ದತ್ತಾಂಶ(cdata->surface, ಖಾಲಿ);
}

ಶೂನ್ಯ Wayland_RecreateCursors(ಶೂನ್ಯ)
{
    SDL_Cursor *cursor;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Video_ದತ್ತಾಂಶ *vdata = SDL_GetVideoDevice()->ಆಂತರಿಕ;

    ಆದರೆ (vdata && vdata->cursor_themes) {
        SDL_free(vdata->cursor_themes);
        vdata->cursor_themes = ಖಾಲಿ;
        vdata->ಅಂಕೆ_cursor_themes = 0;
    }

    ಆದರೆ (mouse == ಖಾಲಿ) {
        ಹಿಂತಿರುಗಿ;
    }

    ಗಾಗಿ (cursor = mouse->cursors; cursor != ಖಾಲಿ; cursor = cursor->ಮುಂದಿನ) {
        Wayland_RecreateCursor(cursor, vdata);
    }
    ಆದರೆ (mouse->def_cursor) {
        Wayland_RecreateCursor(mouse->def_cursor, vdata);
    }
    ಆದರೆ (mouse->cur_cursor) {
        Wayland_RecreateCursor(mouse->cur_cursor, vdata);
        ಆದರೆ (mouse->cursor_visible) {
            Wayland_ShowCursor(mouse->cur_cursor);
        }
    }
}
#ಆದರೆ_ಅಂತ್ಯ // 0

ಶೂನ್ಯ Wayland_InitMouse(SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    mouse->CreateCursor = Wayland_CreateCursor;
    mouse->CreateAnimatedCursor = Wayland_CreateAnimatedCursor;
    mouse->CreateSystemCursor = Wayland_CreateSystemCursor;
    mouse->ShowCursor = Wayland_ShowCursor;
    mouse->FreeCursor = Wayland_FreeCursor;
    mouse->WarpMouse = Wayland_WarpMouseRelative;
    mouse->WarpMouseGlobal = Wayland_WarpMouseGlobal;
    mouse->ಗಣ_Relative_Mouse_ಬಹುಲಕ = Wayland_ಗಣ_Relative_Mouse_ಬಹುಲಕ;
    mouse->GetGlobalMouseState = Wayland_GetGlobalMouseState;

    mouse->have_explicit_warp_event = true;

    SDL_ದೊರಕಿತು_Test_ಫಲಿತಾಂಶ r = SDL_HITTEST_ಸಾಮಾನ್ಯ;
    ಆಗ (r <= SDL_HITTEST_RESIZE_ಎಡ) {
        ಆಯ್ಕೆ (r) {
        ಸ್ಥಿತಿ SDL_HITTEST_ಸಾಮಾನ್ಯ:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_HITTEST_DRAGGABLE:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_TOPLEFT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE);
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_ತುದಿ:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE);
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_TOPRIGHT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE);
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_ಬಲ:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE);
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_BOTTOMRIGHT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE);
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_BOTTOM:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE);
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_BOTTOMLEFT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE);
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_ಎಡ:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE);
            ನಿಲ್ಲಿಸು;
        }
        r++;
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_USE_LIBDBUS
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_ದತ್ತಾಂಶ *d = vd->ಆಂತರಿಕ;

    /* The D-Bus cursor properties are only needed when manually loading themes and system cursors.
     * If the cursor shape protocol is present, the compositor will handle it internally.
     */
    ಆದರೆ (!d->cursor_shape_manager) {
        Wayland_DBusInitCursorProperties(d);
    }
#ಆದರೆ_ಅಂತ್ಯ

    SDL_ಗಣ_Default_Cursor(Wayland_CreateDefaultCursor());
}

ಶೂನ್ಯ Wayland_FiniMouse(SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ)
{
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < SDL_arraysize(sys_cursors); i++) {
        Wayland_FreeCursor(sys_cursors[i]);
        sys_cursors[i] = ಖಾಲಿ;
    }

    Wayland_FreeCursorThemes(ದತ್ತಾಂಶ);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_USE_LIBDBUS
    Wayland_DBus_ಮುಕ್ತಾಯ_Cursor_Properties();
#ಆದರೆ_ಅಂತ್ಯ
}

ಶೂನ್ಯ Wayland_SeatResetCursor(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateResetCursor(&seat->ಸೂಚಕ_2.cursor_state);
}

ಶೂನ್ಯ Wayland_Seat_ಗಣ_Default_Cursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಸೂಚಕ_focus = seat->ಸೂಚಕ_2.focus;
    ಸ್ಥಿರಾಂಕ Wayland_ಸೂಚಕ_Object obj = {
        .wl_ಸೂಚಕ = seat->ಸೂಚಕ_2.wl_ಸೂಚಕ,
        .is_ಸೂಚಕ = true
    };

    Wayland_Cursor_State_ಗಣ_Cursor(&seat->ಸೂಚಕ_2.cursor_state, &obj, ಸೂಚಕ_focus, seat->ಸೂಚಕ_2.enter_serial, mouse->def_cursor);
}

ಶೂನ್ಯ Wayland_Seat_Update_ಸೂಚಕ_Cursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಸೂಚಕ_focus = seat->ಸೂಚಕ_2.focus;
    ಸ್ಥಿರಾಂಕ Wayland_ಸೂಚಕ_Object obj = {
        .wl_ಸೂಚಕ = seat->ಸೂಚಕ_2.wl_ಸೂಚಕ,
        .is_ಸೂಚಕ = true
    };

    ಆದರೆ (ಸೂಚಕ_focus) {
        ಆದರೆ (mouse->cursor_visible) {
            ಆದರೆ (!seat->ಸೂಚಕ_2.relative_ಸೂಚಕ || !mouse->relative_ಬಹುಲಕ_hide_cursor) {
                ಸ್ಥಿರಾಂಕ SDL_ದೊರಕಿತು_Test_ಫಲಿತಾಂಶ rc = ಸೂಚಕ_focus->ದೊರಕಿತು_test_ಫಲಿತಾಂಶ;

                ಆದರೆ (seat->ಸೂಚಕ_2.relative_ಸೂಚಕ || rc == SDL_HITTEST_ಸಾಮಾನ್ಯ || rc == SDL_HITTEST_DRAGGABLE) {
                    Wayland_Cursor_State_ಗಣ_Cursor(&seat->ಸೂಚಕ_2.cursor_state, &obj, ಸೂಚಕ_focus, seat->ಸೂಚಕ_2.enter_serial, mouse->cur_cursor);
                } ಇಲ್ಲದಿದ್ದರೆ {
                    Wayland_Cursor_State_ಗಣ_Cursor(&seat->ಸೂಚಕ_2.cursor_state, &obj, ಸೂಚಕ_focus, seat->ಸೂಚಕ_2.enter_serial, sys_cursors[rc]);
                }
            } ಇಲ್ಲದಿದ್ದರೆ {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_Cursor_State_ಗಣ_Cursor(&seat->ಸೂಚಕ_2.cursor_state, &obj, ಸೂಚಕ_focus, seat->ಸೂಚಕ_2.enter_serial, ಖಾಲಿ);
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            Wayland_Cursor_State_ಗಣ_Cursor(&seat->ಸೂಚಕ_2.cursor_state, &obj, ಸೂಚಕ_focus, seat->ಸೂಚಕ_2.enter_serial, ಖಾಲಿ);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        Wayland_CursorStateResetCursor(&seat->ಸೂಚಕ_2.cursor_state);
    }
}

ಶೂನ್ಯ Wayland_TabletToolUpdateCursor(SDL_WaylandPenTool *tool)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *tool_focus = tool->focus;
    ಸ್ಥಿರಾಂಕ Wayland_ಸೂಚಕ_Object obj = {
        .wl_tool = tool->wltool,
        .is_ಸೂಚಕ = false
    };

    ಆದರೆ (tool_focus) {
        ಆದರೆ (mouse->cursor_visible) {
            // Relative mode is only relevant if the tool sends pointer events.
            ಸ್ಥಿರಾಂಕ bool relative = mouse->pen_mouse_events && (tool_focus->sdlwindow->flags & SDL_ಕಿಟಕಿ_MOUSE_RELATIVE_ಬಹುಲಕ);

            ಆದರೆ (!relative || !mouse->relative_ಬಹುಲಕ_hide_cursor) {
                Wayland_Cursor_State_ಗಣ_Cursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, mouse->cur_cursor);
            } ಇಲ್ಲದಿದ್ದರೆ {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_Cursor_State_ಗಣ_Cursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, ಖಾಲಿ);
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            Wayland_Cursor_State_ಗಣ_Cursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, ಖಾಲಿ);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        Wayland_CursorStateResetCursor(&tool->cursor_state);
    }
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_WAYLAND
