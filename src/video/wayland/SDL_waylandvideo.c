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

#ಅನ್ತರ್ಭಾವ "../../core/linux/SDL_system_theme.h"
#ಅನ್ತರ್ಭಾವ "../../core/linux/SDL_progressbar.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"

#ಅನ್ತರ್ಭಾವ "SDL_waylandclipboard.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandcolor.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandevents_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandkeyboard.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandmessagebox.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandmouse.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandopengles.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandvulkan.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandwindow.h"

#ಅನ್ತರ್ಭಾವ <fcntl.h>
#ಅನ್ತರ್ಭಾವ <sys/types.h>
#ಅನ್ತರ್ಭಾವ <unistd.h>
#ಅನ್ತರ್ಭಾವ <errno.h>
#ಅನ್ತರ್ಭಾವ <xkbcommon/xkbcommon.h>

#ಅನ್ತರ್ಭಾವ <wayland-util.h>

#ಅನ್ತರ್ಭಾವ "alpha-modifier-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "cursor-shape-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "fractional-scale-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "frog-color-management-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "idle-inhibit-unstable-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "input-timestamps-unstable-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "keyboard-shortcuts-inhibit-unstable-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "pointer-constraints-unstable-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "primary-selection-unstable-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "relative-pointer-unstable-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "tablet-v2-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "text-input-unstable-v3-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "viewporter-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "xdg-activation-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "xdg-decoration-unstable-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "xdg-dialog-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "xdg-foreign-unstable-v2-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "xdg-output-unstable-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "xdg-shell-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "xdg-toplevel-icon-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "color-management-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "pointer-warp-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "pointer-gestures-unstable-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "single-pixel-buffer-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "xdg-session-management-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "xdg-toplevel-tag-v1-client-protocol.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
#ಅನ್ತರ್ಭಾವ <libdecor.h>
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು WAYLANDVID_DRIVER_NAME "wayland"

// Clamp core protocol versions on older versions of libwayland.
#ಆದರೆ SDL_WAYLAND_CHECK_ಆವೃತ್ತಿ(1, 22, 0)
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_WL_COMPOSITOR_ಆವೃತ್ತಿ 6
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_WL_COMPOSITOR_ಆವೃತ್ತಿ 4
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ SDL_WAYLAND_CHECK_ಆವೃತ್ತಿ(1, 26, 0)
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_WL_SEAT_ಆವೃತ್ತಿ 11
#ಅಥವಾಆದರೆ SDL_WAYLAND_CHECK_ಆವೃತ್ತಿ(1, 24, 0)
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_WL_SEAT_ಆವೃತ್ತಿ 10
#ಅಥವಾಆದರೆ SDL_WAYLAND_CHECK_ಆವೃತ್ತಿ(1, 22, 0)
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_WL_SEAT_ಆವೃತ್ತಿ 9
#ಅಥವಾಆದರೆ SDL_WAYLAND_CHECK_ಆವೃತ್ತಿ(1, 21, 0)
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_WL_SEAT_ಆವೃತ್ತಿ 8
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_WL_SEAT_ಆವೃತ್ತಿ 5
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ SDL_WAYLAND_CHECK_ಆವೃತ್ತಿ(1, 20, 0)
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_WL_OUTPUT_ಆವೃತ್ತಿ 4
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_WL_OUTPUT_ಆವೃತ್ತಿ 3
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ SDL_WAYLAND_CHECK_ಆವೃತ್ತಿ(1, 24, 0)
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_WL_SHM_ಆವೃತ್ತಿ 2
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_WL_SHM_ಆವೃತ್ತಿ 1
#ಆದರೆ_ಅಂತ್ಯ

// The SDL libwayland-client minimum is 1.18, which supports version 3.
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_WL_ದತ್ತಾಂಶ_DEVICE_ಆವೃತ್ತಿ 3

// wl_fixes was introduced in 1.24.0
#ಆದರೆ SDL_WAYLAND_CHECK_ಆವೃತ್ತಿ(1, 26, 0)
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_WL_FIXES_ಆವೃತ್ತಿ 2
#ಅಥವಾಆದರೆ SDL_WAYLAND_CHECK_ಆವೃತ್ತಿ(1, 24, 0)
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_WL_FIXES_ಆವೃತ್ತಿ 1
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_USE_LIBDBUS
#ಅನ್ತರ್ಭಾವ "../../core/linux/SDL_dbus.h"

#ವ್ಯಾಖ್ಯಾನಿಸು DISPLAY_INFO_ಗಂಟು   "org.gnome.Mutter.DisplayConfig"
#ವ್ಯಾಖ್ಯಾನಿಸು DISPLAY_INFO_ಮಾರ್ಗ   "/org/gnome/Mutter/DisplayConfig"
#ವ್ಯಾಖ್ಯಾನಿಸು DISPLAY_INFO_ವಿಧಾನ "GetCurrentState"
#ಆದರೆ_ಅಂತ್ಯ

/* GNOME doesn't expose displays in any particular order, but we can find the
 * primary display and its logical coordinates via a DBus method.
 */
ಸ್ಥಿರ bool Wayland_GetGNOMEPrimaryDisplayCoordinates(ಪೂರ್ಣಾಂಕ *x, ಪೂರ್ಣಾಂಕ *y)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_USE_LIBDBUS
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    ಆದರೆ (dbus == ಖಾಲಿ) {
        ಹಿಂತಿರುಗಿ false;
    }
    DBus_ಸಂದೇಶ *ಉತ್ತರ = ಖಾಲಿ;
    DBus_ಸಂದೇಶ_Iter iter[3];
    DBus_ಸಂದೇಶ *ಸಂದೇಶ_2 = dbus->ಸಂದೇಶ_new_ವಿಧಾನ_call(DISPLAY_INFO_ಗಂಟು,
                                                     DISPLAY_INFO_ಮಾರ್ಗ,
                                                     DISPLAY_INFO_ಗಂಟು,
                                                     DISPLAY_INFO_ವಿಧಾನ);

    ಆದರೆ (ಸಂದೇಶ_2) {
        ಉತ್ತರ = dbus->connection_send_with_ಉತ್ತರ_and_ಖಂಡ(dbus->session_conn, ಸಂದೇಶ_2, DBUS_TIMEOUT_USE_DEFAULT, ಖಾಲಿ);
        dbus->ಸಂದೇಶ_unref(ಸಂದೇಶ_2);
    }

    ಆದರೆ (ಉತ್ತರ) {
        // Serial (don't care)
        dbus->ಸಂದೇಶ_iter_init(ಉತ್ತರ, &iter[0]);
        ಆದರೆ (dbus->ಸಂದೇಶ_iter_get_arg_type(&iter[0]) != DBUS_TYPE_UINT32) {
            ಹೋಗು error;
        }

        // Physical monitor array (don't care)
        dbus->ಸಂದೇಶ_iter_ಮುಂದಿನ(&iter[0]);
        ಆದರೆ (dbus->ಸಂದೇಶ_iter_get_arg_type(&iter[0]) != DBUS_TYPE_ARRAY) {
            ಹೋಗು error;
        }

        // Logical monitor array of structs
        dbus->ಸಂದೇಶ_iter_ಮುಂದಿನ(&iter[0]);
        ಆದರೆ (dbus->ಸಂದೇಶ_iter_get_arg_type(&iter[0]) != DBUS_TYPE_ARRAY) {
            ಹೋಗು error;
        }

        // First logical monitor struct
        dbus->ಸಂದೇಶ_iter_recurse(&iter[0], &iter[1]);
        ಆದರೆ (dbus->ಸಂದೇಶ_iter_get_arg_type(&iter[1]) != DBUS_TYPE_STRUCT) {
            ಹೋಗು error;
        }

        ಮಾಡು {
            ಪೂರ್ಣಾಂಕ logical_x, logical_y;
            dbus_bool_t primary;

            // Logical X
            dbus->ಸಂದೇಶ_iter_recurse(&iter[1], &iter[2]);
            ಆದರೆ (dbus->ಸಂದೇಶ_iter_get_arg_type(&iter[2]) != DBUS_TYPE_INT32) {
                ಹೋಗು error;
            }
            dbus->ಸಂದೇಶ_iter_get_basic(&iter[2], &logical_x);

            // Logical Y
            dbus->ಸಂದೇಶ_iter_ಮುಂದಿನ(&iter[2]);
            ಆದರೆ (dbus->ಸಂದೇಶ_iter_get_arg_type(&iter[2]) != DBUS_TYPE_INT32) {
                ಹೋಗು error;
            }
            dbus->ಸಂದೇಶ_iter_get_basic(&iter[2], &logical_y);

            // Scale (don't care)
            dbus->ಸಂದೇಶ_iter_ಮುಂದಿನ(&iter[2]);
            ಆದರೆ (dbus->ಸಂದೇಶ_iter_get_arg_type(&iter[2]) != DBUS_TYPE_DOUBLE) {
                ಹೋಗು error;
            }

            // Transform (don't care)
            dbus->ಸಂದೇಶ_iter_ಮುಂದಿನ(&iter[2]);
            ಆದರೆ (dbus->ಸಂದೇಶ_iter_get_arg_type(&iter[2]) != DBUS_TYPE_UINT32) {
                ಹೋಗು error;
            }

            // Primary display boolean
            dbus->ಸಂದೇಶ_iter_ಮುಂದಿನ(&iter[2]);
            ಆದರೆ (dbus->ಸಂದೇಶ_iter_get_arg_type(&iter[2]) != DBUS_TYPE_BOOLEAN) {
                ಹೋಗು error;
            }
            dbus->ಸಂದೇಶ_iter_get_basic(&iter[2], &primary);

            ಆದರೆ (primary) {
                *x = logical_x;
                *y = logical_y;

                // We found the primary display: success.
                dbus->ಸಂದೇಶ_unref(ಉತ್ತರ);
                ಹಿಂತಿರುಗಿ true;
            }
        } ಆಗ (dbus->ಸಂದೇಶ_iter_ಮುಂದಿನ(&iter[1]));
    }

error:
    ಆದರೆ (ಉತ್ತರ) {
        dbus->ಸಂದೇಶ_unref(ಉತ್ತರ);
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ false;
}

// Sort the list of displays into a deterministic order
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ SDLCALL Wayland_DisplayPositionCompare(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *a, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *b)
{
    ಸ್ಥಿರಾಂಕ SDL_Display_ದತ್ತಾಂಶ *da = *(SDL_Display_ದತ್ತಾಂಶ **)a;
    ಸ್ಥಿರಾಂಕ SDL_Display_ದತ್ತಾಂಶ *db = *(SDL_Display_ದತ್ತಾಂಶ **)b;
    ಸ್ಥಿರಾಂಕ bool a_at_origin = da->logical.x == 0 && da->logical.y == 0;
    ಸ್ಥಿರಾಂಕ bool b_at_origin = db->logical.x == 0 && db->logical.y == 0;

    // Sort the display at 0,0 to be beginning of the list, as that will be the fallback primary.
    ಆದರೆ (a_at_origin && !b_at_origin) {
        ಹಿಂತಿರುಗಿ -1;
    }
    ಆದರೆ (b_at_origin && !a_at_origin) {
        ಹಿಂತಿರುಗಿ 1;
    }

    ಆದರೆ (da->logical.x < db->logical.x) {
        ಹಿಂತಿರುಗಿ -1;
    }
    ಆದರೆ (da->logical.x > db->logical.x) {
        ಹಿಂತಿರುಗಿ 1;
    }
    ಆದರೆ (da->logical.y < db->logical.y) {
        ಹಿಂತಿರುಗಿ -1;
    }
    ಆದರೆ (da->logical.y > db->logical.y) {
        ಹಿಂತಿರುಗಿ 1;
    }

    // If no position information is available, use the connector name.
    ಆದರೆ (da->wl_output_name && db->wl_output_name) {
        ಹಿಂತಿರುಗಿ SDL_strcmp(da->wl_output_name, db->wl_output_name);
    }

    ಹಿಂತಿರುಗಿ 0;
}

/* Wayland doesn't have the native concept of a primary display, but there are clients that
 * will base their resolution lists on, or automatically make themselves fullscreen on, the
 * first listed output, which can lead to problems if the first listed output isn't
 * necessarily the best display for this. This attempts to find a primary display, first by
 * querying the GNOME DBus property, then trying to determine the 'best' display if that fails.
 * If all displays are equal, the one at position 0,0 will become the primary.
 *
 * The primary is determined by the following criteria, in order:
 * - Landscape is preferred over portrait
 * - The highest native resolution
 * - A higher HDR range is preferred
 * - Higher refresh is preferred (ignoring small differences)
 * - Lower scale values are preferred (larger display)
 */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ Wayland_GetPrimaryDisplay(SDL_Video_ದತ್ತಾಂಶ *vid)
{
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ REFRESH_DELTA = 4000;

    // Query the DBus interface to see if the coordinates of the primary display are exposed.
    ಪೂರ್ಣಾಂಕ x, y;
    ಆದರೆ (Wayland_GetGNOMEPrimaryDisplayCoordinates(&x, &y)) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < vid->output_ಎಣಿಕೆ; ++i) {
            ಆದರೆ (vid->output_list[i]->logical.x == x && vid->output_list[i]->logical.y == y) {
                ಹಿಂತಿರುಗಿ i;
            }
        }
    }

    // Otherwise, choose the 'best' display.
    ಪೂರ್ಣಾಂಕ ಉತ್ತಮ_ಅಗಲ = 0;
    ಪೂರ್ಣಾಂಕ ಉತ್ತಮ_ಎತ್ತರ = 0;
    ದ್ವಿಗುಣ ಉತ್ತಮ_scale = 0.0;
    ದಶಮಾಂಶ ಉತ್ತಮ_headroom = 0.0f;
    ಪೂರ್ಣಾಂಕ ಉತ್ತಮ_refresh = 0;
    bool ಉತ್ತಮ_is_landscape = false;
    ಪೂರ್ಣಾಂಕ ಉತ್ತಮ_ಸೂಚ್ಯಂಕ = 0;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < vid->output_ಎಣಿಕೆ; ++i) {
        ಸ್ಥಿರಾಂಕ SDL_Display_ದತ್ತಾಂಶ *d = vid->output_list[i];
        ಸ್ಥಿರಾಂಕ bool is_landscape = d->orientation != SDL_ORIENTATION_PORTRAIT && d->orientation != SDL_ORIENTATION_PORTRAIT_FLIPPED;
        bool have_new_ಉತ್ತಮ = false;

        ಆದರೆ (!ಉತ್ತಮ_is_landscape && is_landscape) { // Favor landscape over portrait displays.
            have_new_ಉತ್ತಮ = true;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!ಉತ್ತಮ_is_landscape || is_landscape) { // Ignore portrait displays if a landscape was already found.
            ಆದರೆ (d->pixel.ಅಗಲ > ಉತ್ತಮ_ಅಗಲ || d->pixel.ಎತ್ತರ > ಉತ್ತಮ_ಎತ್ತರ) {
                have_new_ಉತ್ತಮ = true;
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (d->pixel.ಅಗಲ == ಉತ್ತಮ_ಅಗಲ && d->pixel.ಎತ್ತರ == ಉತ್ತಮ_ಎತ್ತರ) {
                ಆದರೆ (d->HDR.HDR_headroom > ಉತ್ತಮ_headroom) { // Favor a higher HDR luminance range
                    have_new_ಉತ್ತಮ = true;
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (d->HDR.HDR_headroom == ಉತ್ತಮ_headroom) {
                    ಆದರೆ (d->refresh - ಉತ್ತಮ_refresh > REFRESH_DELTA) { // Favor a higher refresh rate, but ignore small differences (e.g. 59.97 vs 60.1)
                        have_new_ಉತ್ತಮ = true;
                    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (d->scale_ಗುಣಕ_2 < ಉತ್ತಮ_scale && SDL_abs(d->refresh - ಉತ್ತಮ_refresh) <= REFRESH_DELTA) {
                        // Prefer a lower scale display if the difference in refresh rate is small.
                        have_new_ಉತ್ತಮ = true;
                    }
                }
            }
        }

        ಆದರೆ (have_new_ಉತ್ತಮ) {
            ಉತ್ತಮ_ಅಗಲ = d->pixel.ಅಗಲ;
            ಉತ್ತಮ_ಎತ್ತರ = d->pixel.ಎತ್ತರ;
            ಉತ್ತಮ_scale = d->scale_ಗುಣಕ_2;
            ಉತ್ತಮ_headroom = d->HDR.HDR_headroom;
            ಉತ್ತಮ_refresh = d->refresh;
            ಉತ್ತಮ_is_landscape = is_landscape;
            ಉತ್ತಮ_ಸೂಚ್ಯಂಕ = i;
        }
    }

    ಹಿಂತಿರುಗಿ ಉತ್ತಮ_ಸೂಚ್ಯಂಕ;
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_ವಿಂಗಡಿಸು_Outputs_By_ಆದ್ಯತೆ_Hint(SDL_Video_ದತ್ತಾಂಶ *vid)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_ಆದ್ಯತೆ);

    ಆದರೆ (name_hint) {
        ಅಕ್ಷರ *saveptr;
        ಅಕ್ಷರ *str = SDL_strdup(name_hint);
        SDL_Display_ದತ್ತಾಂಶ **sorted_list = SDL_malloc(ಗಾತ್ರ(SDL_Display_ದತ್ತಾಂಶ *) * vid->output_ಎಣಿಕೆ);

        ಆದರೆ (str && sorted_list) {
            ಪೂರ್ಣಾಂಕ sorted_ಸೂಚ್ಯಂಕ = 0;

            // Sort the requested displays to the front of the list.
            ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *token = SDL_strtok_r(str, ",", &saveptr);
            ಆಗ (token) {
                ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < vid->output_ಎಣಿಕೆ; ++i) {
                    SDL_Display_ದತ್ತಾಂಶ *d = vid->output_list[i];
                    ಆದರೆ (d && d->wl_output_name && SDL_strcmp(token, d->wl_output_name) == 0) {
                        sorted_list[sorted_ಸೂಚ್ಯಂಕ++] = d;
                        vid->output_list[i] = ಖಾಲಿ;
                        ನಿಲ್ಲಿಸು;
                    }
                }

                token = SDL_strtok_r(ಖಾಲಿ, ",", &saveptr);
            }

            // Append the remaining outputs to the end of the list.
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < vid->output_ಎಣಿಕೆ; ++i) {
                ಆದರೆ (vid->output_list[i]) {
                    sorted_list[sorted_ಸೂಚ್ಯಂಕ++] = vid->output_list[i];
                }
            }

            // Copy the sorted list to the output list.
            SDL_memcpy(vid->output_list, sorted_list, ಗಾತ್ರ(SDL_Display_ದತ್ತಾಂಶ *) * vid->output_ಎಣಿಕೆ);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_DeriveOutputPixelCoordinates(SDL_Video_ದತ್ತಾಂಶ *vid)
{
    /* Ensure outputs are not overlapping in the pixel coordinate space.
     *
     * This is a simple algorithm that offsets display positions by the
     * logical/pixel difference if they are to the right of and/or below a scaled
     * display. It can leave gaps in certain scenarios, but it works well enough
     * in most cases.
     *
     * Patches for a more sophisticated algorithm are welcome.
     */
    ಗಾಗಿ ( ಪೂರ್ಣಾಂಕ i = 0; i < vid->output_ಎಣಿಕೆ; ++i) {
        SDL_Display_ದತ್ತಾಂಶ *d = vid->output_list[i];
        d->pixel.x = d->logical.x;
        d->pixel.y = d->logical.y;
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < vid->output_ಎಣಿಕೆ; ++i) {
        SDL_Display_ದತ್ತಾಂಶ *d1 = vid->output_list[i];
        ಆದರೆ (d1->logical.ಅಗಲ != d1->pixel.ಅಗಲ || d1->logical.ಎತ್ತರ != d1->pixel.ಎತ್ತರ) {
            ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ x_adj = d1->pixel.ಅಗಲ - d1->logical.ಅಗಲ;
            ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ y_adj = d1->pixel.ಎತ್ತರ - d1->logical.ಎತ್ತರ;

            // Don't adjust for scale values less than 1.0.
            ಆದರೆ (x_adj > 0 && y_adj > 0) {
                ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < vid->output_ಎಣಿಕೆ; ++j) {
                    SDL_Display_ದತ್ತಾಂಶ *d2 = vid->output_list[j];
                    ಆದರೆ (d2->logical.x > d1->logical.x) {
                        d2->pixel.x += x_adj;
                    }
                    ಆದರೆ (d2->logical.y > d1->logical.y) {
                        d2->pixel.y += y_adj;
                    }
                }
            }
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_ವಿಂಗಡಿಸು_Outputs(SDL_Video_ದತ್ತಾಂಶ *vid)
{
    // Sort by position or connector name, so the order of outputs is deterministic.
    SDL_qsort(vid->output_list, vid->output_ಎಣಿಕೆ, ಗಾತ್ರ(SDL_Display_ದತ್ತಾಂಶ *), Wayland_DisplayPositionCompare);

    // Derive the output pixel coordinates if scale to display is enabled.
    ಆದರೆ (vid->scale_ಗಮ್ಯ_display_enabled) {
        Wayland_DeriveOutputPixelCoordinates(vid);
    }

    // Find a suitable primary display and move it to the front of the list.
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ primary_ಸೂಚ್ಯಂಕ = Wayland_GetPrimaryDisplay(vid);
    ಆದರೆ (primary_ಸೂಚ್ಯಂಕ) {
        SDL_Display_ದತ್ತಾಂಶ *primary = vid->output_list[primary_ಸೂಚ್ಯಂಕ];
        SDL_memmove(&vid->output_list[1], &vid->output_list[0], ಗಾತ್ರ(SDL_Display_ದತ್ತಾಂಶ *) * primary_ಸೂಚ್ಯಂಕ);
        vid->output_list[0] = primary;
    }

    // Apply the ordering hint, if specified.
    Wayland_ವಿಂಗಡಿಸು_Outputs_By_ಆದ್ಯತೆ_Hint(vid);
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_Refresh_ಕಿಟಕಿ_Positions()
{
    SDL_VideoDevice *vid = SDL_GetVideoDevice();

    ಗಾಗಿ (SDL_ಕಿಟಕಿ *w = vid->windows; w; w = w->ಮುಂದಿನ) {
        Wayland_Update_ಕಿಟಕಿ_Position(w);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ handle_wl_output_ಮುಗಿದ(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_output *output);

// Initialization/Query functions
ಸ್ಥಿರ bool Wayland_VideoInit(SDL_VideoDevice *_this);
ಸ್ಥಿರ bool Wayland_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
ಸ್ಥಿರ ಶೂನ್ಯ Wayland_VideoQuit(SDL_VideoDevice *_this);

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *SDL_WAYLAND_surface_ಟ್ಯಾಗ್ = "sdl-window";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *SDL_WAYLAND_output_ಟ್ಯಾಗ್ = "sdl-output";

ಶೂನ್ಯ SDL_WAYLAND_ರಿಜಿಸ್ಟರ್_surface(ರಚನೆ wl_surface *surface)
{
    wl_proxy_ಗಣ_ಟ್ಯಾಗ್((ರಚನೆ wl_proxy *)surface, &SDL_WAYLAND_surface_ಟ್ಯಾಗ್);
}

ಶೂನ್ಯ SDL_WAYLAND_ರಿಜಿಸ್ಟರ್_output(ರಚನೆ wl_output *output)
{
    wl_proxy_ಗಣ_ಟ್ಯಾಗ್((ರಚನೆ wl_proxy *)output, &SDL_WAYLAND_output_ಟ್ಯಾಗ್);
}

bool SDL_WAYLAND_own_surface(ರಚನೆ wl_surface *surface)
{
    ಹಿಂತಿರುಗಿ wl_proxy_get_ಟ್ಯಾಗ್((ರಚನೆ wl_proxy *)surface) == &SDL_WAYLAND_surface_ಟ್ಯಾಗ್;
}

bool SDL_WAYLAND_own_output(ರಚನೆ wl_output *output)
{
    ಹಿಂತಿರುಗಿ wl_proxy_get_ಟ್ಯಾಗ್((ರಚನೆ wl_proxy *)output) == &SDL_WAYLAND_output_ಟ್ಯಾಗ್;
}

/* External surfaces may have their own user data attached, the modification of which
 * can cause problems with external toolkits. Instead, external windows are kept in
 * their own list, and a search is conducted to find a matching surface.
 */
ಸ್ಥಿರ ರಚನೆ wl_list external_ಕಿಟಕಿ_list;

ಶೂನ್ಯ Wayland_ಕೂಡಿಸು_ಕಿಟಕಿ_ದತ್ತಾಂಶ_ಗಮ್ಯ_External_List(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ)
{
    WAYLAND_wl_list_ಸೇರಿಸು(&external_ಕಿಟಕಿ_list, &ದತ್ತಾಂಶ->external_ಕಿಟಕಿ_list_link);
}

ಶೂನ್ಯ Wayland_Remove_ಕಿಟಕಿ_ದತ್ತಾಂಶ_From_External_List(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ)
{
    WAYLAND_wl_list_remove(&ದತ್ತಾಂಶ->external_ಕಿಟಕಿ_list_link);
}

SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *Wayland_Get_ಕಿಟಕಿ_ದತ್ತಾಂಶ_For_Owned_Surface(ರಚನೆ wl_surface *surface)
{
    ಆದರೆ (SDL_WAYLAND_own_surface(surface)) {
        ಹಿಂತಿರುಗಿ (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)wl_surface_get_user_ದತ್ತಾಂಶ(surface);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!WAYLAND_wl_list_ಖಾಲಿಗಳು(&external_ಕಿಟಕಿ_list)) {
        SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *p;
        wl_list_for_each (p, &external_ಕಿಟಕಿ_list, external_ಕಿಟಕಿ_list_link) {
            ಆದರೆ (p->surface == surface) {
                ಹಿಂತಿರುಗಿ p;
            }
        }
    }

    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ರಚನೆ wl_event_ಸರತಿ *Wayland_Display_Create_ಸರತಿ(ರಚನೆ wl_display *display, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
    ಆದರೆ (WAYLAND_wl_display_create_ಸರತಿ_with_name) {
        ಹಿಂತಿರುಗಿ WAYLAND_wl_display_create_ಸರತಿ_with_name(display, name);
    }
#ಅಥವಾಆದರೆ SDL_WAYLAND_CHECK_ಆವೃತ್ತಿ(1, 23, 0)
    ಹಿಂತಿರುಗಿ WAYLAND_wl_display_create_ಸರತಿ_with_name(display, name);
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ WAYLAND_wl_display_create_ಸರತಿ(display);
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = device->ಆಂತರಿಕ;
    ಆದರೆ (ದತ್ತಾಂಶ->display && !ದತ್ತಾಂಶ->display_externally_owned) {
        WAYLAND_wl_display_disconnect(ದತ್ತಾಂಶ->display);
        SDL_ClearProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_ಸೂಚಕ);
    }
    SDL_free(ದತ್ತಾಂಶ);
    SDL_free(device);
    SDL_WAYLAND_UnloadSymbols();
}

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    bool has_fifo_v1;
    ರಚನೆ wl_fixes *wl_fixes;
} SDL_Wayland_Preferred_ದತ್ತಾಂಶ;

ಸ್ಥಿರ ಶೂನ್ಯ wayland_preferred_check_handle_global(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_registry *registry, uint32_t id,
                                                  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *interface, uint32_t ಆವೃತ್ತಿ)
{
    SDL_Wayland_Preferred_ದತ್ತಾಂಶ *d = ದತ್ತಾಂಶ;

    ಆದರೆ (SDL_strcmp(interface, "wp_fifo_manager_v1") == 0) {
        d->has_fifo_v1 = true;
    }
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_WL_FIXES_ಆವೃತ್ತಿ
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(interface, wl_fixes_interface.name) == 0) {
        d->wl_fixes = wl_registry_bind(registry, id, &wl_fixes_interface, SDL_min(SDL_WL_FIXES_ಆವೃತ್ತಿ, ಆವೃತ್ತಿ));
    }
#ಆದರೆ_ಅಂತ್ಯ
}

ಸ್ಥಿರ ಶೂನ್ಯ wayland_preferred_check_remove_global(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_registry *registry, uint32_t id)
{
    SDL_Wayland_Preferred_ದತ್ತಾಂಶ *d = (SDL_Wayland_Preferred_ದತ್ತಾಂಶ *)ದತ್ತಾಂಶ;

    ಆದರೆ (d->wl_fixes && wl_fixes_get_ಆವೃತ್ತಿ(d->wl_fixes) >= WL_FIXES_ACK_GLOBAL_REMOVE_SINCE_ಆವೃತ್ತಿ) {
        wl_fixes_ack_global_remove(d->wl_fixes, registry, id);
    }
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ wl_registry_listener preferred_registry_listener = {
    wayland_preferred_check_handle_global,
    wayland_preferred_check_remove_global
};

ಸ್ಥಿರ bool Wayland_IsPreferred(ರಚನೆ wl_display *display)
{
    ರಚನೆ wl_registry *registry = wl_display_get_registry(display);
    SDL_Wayland_Preferred_ದತ್ತಾಂಶ preferred_ದತ್ತಾಂಶ = { 0 };

    ಆದರೆ (!registry) {
        SDL_ಗಣ_Error("Failed to get the Wayland registry");
        ಹಿಂತಿರುಗಿ false;
    }

    wl_registry_ಕೂಡಿಸು_listener(registry, &preferred_registry_listener, &preferred_ದತ್ತಾಂಶ);

    WAYLAND_wl_display_roundtrip(display);

    ಆದರೆ (preferred_ದತ್ತಾಂಶ.wl_fixes) {
        wl_fixes_destroy_registry(preferred_ದತ್ತಾಂಶ.wl_fixes, registry);
        wl_fixes_destroy(preferred_ದತ್ತಾಂಶ.wl_fixes);
    }
    wl_registry_destroy(registry);

    ಆದರೆ (!preferred_ದತ್ತಾಂಶ.has_fifo_v1) {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "This compositor lacks support for the fifo-v1 protocol; falling back to XWayland for GPU performance reasons (set SDL_VIDEO_DRIVER=wayland to override)");
    }
    ಹಿಂತಿರುಗಿ preferred_ದತ್ತಾಂಶ.has_fifo_v1;
}

ಸ್ಥಿರ SDL_VideoDevice *Wayland_CreateDevice(bool require_preferred_protocols)
{
    SDL_VideoDevice *device;
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ;
    ರಚನೆ wl_display *display = SDL_Get_ಸೂಚಕ_Property(SDL_GetGlobalProperties(),
                                                 SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_ಸೂಚಕ, ಖಾಲಿ);
    bool display_is_external = !!display;

    // Are we trying to connect to, or are currently in, a Wayland session?
    ಆದರೆ (!SDL_getenv("WAYLAND_DISPLAY")) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *session = SDL_getenv("XDG_SESSION_TYPE");
        ಆದರೆ (session && SDL_strcasecmp(session, "wayland") != 0) {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Wayland initialization failed: no Wayland session available");
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }
    }

    ಆದರೆ (!SDL_WAYLAND_ತುಂಬು_Symbols()) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ (!display) {
        display = WAYLAND_wl_display_connect(ಖಾಲಿ);
        ಆದರೆ (!display) {
            SDL_WAYLAND_UnloadSymbols();
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to connect to the Wayland display server: %s", strerror(errno));
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }
    }

    /*
     * If we are checking for preferred Wayland, then let's query for
     * fifo-v1's existence, so we don't regress GPU-bound performance
     * and frame-pacing by default due to swapchain starvation.
     */
    ಆದರೆ (require_preferred_protocols && !Wayland_IsPreferred(display)) {
        ಆದರೆ (!display_is_external) {
            WAYLAND_wl_display_disconnect(display);
        }
        SDL_WAYLAND_UnloadSymbols();
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ದತ್ತಾಂಶ = SDL_calloc(1, ಗಾತ್ರ(*ದತ್ತಾಂಶ));
    ಆದರೆ (!ದತ್ತಾಂಶ) {
        ಆದರೆ (!display_is_external) {
            WAYLAND_wl_display_disconnect(display);
        }
        SDL_WAYLAND_UnloadSymbols();
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ದತ್ತಾಂಶ->initializing = true;
    ದತ್ತಾಂಶ->display = display;
    ದತ್ತಾಂಶ->display_externally_owned = display_is_external;
    ದತ್ತಾಂಶ->scale_ಗಮ್ಯ_display_enabled = SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_SCALE_ಗಮ್ಯ_DISPLAY, false);
    WAYLAND_wl_list_init(&ದತ್ತಾಂಶ->seat_list);
    WAYLAND_wl_list_init(&external_ಕಿಟಕಿ_list);

    // Initialize all variables that we clean on shutdown
    device = SDL_calloc(1, ಗಾತ್ರ(SDL_VideoDevice));
    ಆದರೆ (!device) {
        SDL_free(ದತ್ತಾಂಶ);
        ಆದರೆ (!display_is_external) {
            WAYLAND_wl_display_disconnect(display);
        }
        SDL_WAYLAND_UnloadSymbols();
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ (!display_is_external) {
        SDL_ಗಣ_ಸೂಚಕ_Property(SDL_GetGlobalProperties(),
                               SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_ಸೂಚಕ, display);
    }

    device->ಆಂತರಿಕ = ದತ್ತಾಂಶ;

    // Set the function pointers
    device->VideoInit = Wayland_VideoInit;
    device->VideoQuit = Wayland_VideoQuit;
    device->GetDisplayBounds = Wayland_GetDisplayBounds;
    device->SuspendScreenSaver = Wayland_SuspendScreenSaver;

    device->PumpEvents = Wayland_PumpEvents;
    device->WaitEventTimeout = Wayland_WaitEventTimeout;
    device->SendWakeupEvent = Wayland_SendWakeupEvent;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
    device->GL_ಅದಲುಬದಲು_ಕಿಟಕಿ = Wayland_GLES_ಅದಲುಬದಲು_ಕಿಟಕಿ;
    device->GL_Get_ಅದಲುಬದಲು_Interval = Wayland_GLES_Get_ಅದಲುಬದಲು_Interval;
    device->GL_ಗಣ_ಅದಲುಬದಲು_Interval = Wayland_GLES_ಗಣ_ಅದಲುಬದಲು_Interval;
    device->GL_MakeCurrent = Wayland_GLES_MakeCurrent;
    device->GL_CreateContext = Wayland_GLES_CreateContext;
    device->GL_ತುಂಬು_Library = Wayland_GLES_ತುಂಬು_Library;
    device->GL_UnloadLibrary = Wayland_GLES_UnloadLibrary;
    device->GL_Get_Proc_ವಿಳಾಸ = Wayland_GLES_Get_Proc_ವಿಳಾಸ;
    device->GL_DestroyContext = Wayland_GLES_DestroyContext;
    device->GL_ಗಣ_Default_Profile_Config = Wayland_GLES_ಗಣ_Default_Profile_Config;
    device->GL_GetEGLSurface = Wayland_GLES_GetEGLSurface;
#ಆದರೆ_ಅಂತ್ಯ

    device->CreateSDLWindow = Wayland_Create_ಕಿಟಕಿ;
    device->Show_ಕಿಟಕಿ = Wayland_Show_ಕಿಟಕಿ;
    device->Hide_ಕಿಟಕಿ = Wayland_Hide_ಕಿಟಕಿ;
    device->Raise_ಕಿಟಕಿ = Wayland_Raise_ಕಿಟಕಿ;
    device->ಗಣ_ಕಿಟಕಿ_Fullscreen = Wayland_ಗಣ_ಕಿಟಕಿ_Fullscreen;
    device->Maximize_ಕಿಟಕಿ = Wayland_Maximize_ಕಿಟಕಿ;
    device->Minimize_ಕಿಟಕಿ = Wayland_Minimize_ಕಿಟಕಿ;
    device->ಗಣ_ಕಿಟಕಿ_Mouse_Rect = Wayland_ಗಣ_ಕಿಟಕಿ_Mouse_Rect;
    device->ಗಣ_ಕಿಟಕಿ_Mouse_Grab = Wayland_ಗಣ_ಕಿಟಕಿ_Mouse_Grab;
    device->ಗಣ_ಕಿಟಕಿ_Keyboard_Grab = Wayland_ಗಣ_ಕಿಟಕಿ_Keyboard_Grab;
    device->Restore_ಕಿಟಕಿ = Wayland_Restore_ಕಿಟಕಿ;
    device->ಗಣ_ಕಿಟಕಿ_Bordered = Wayland_ಗಣ_ಕಿಟಕಿ_Bordered;
    device->ಗಣ_ಕಿಟಕಿ_Resizable = Wayland_ಗಣ_ಕಿಟಕಿ_Resizable;
    device->ಗಣ_ಕಿಟಕಿ_Position = Wayland_ಗಣ_ಕಿಟಕಿ_Position;
    device->ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ = Wayland_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ;
    device->ಗಣ_ಕಿಟಕಿ_Aspect_ಅನುಪಾತ = Wayland_ಗಣ_ಕಿಟಕಿ_Aspect_ಅನುಪಾತ;
    device->ಗಣ_ಕಿಟಕಿ_Minimum_ಗಾತ್ರ = Wayland_ಗಣ_ಕಿಟಕಿ_Minimum_ಗಾತ್ರ;
    device->ಗಣ_ಕಿಟಕಿ_ಗರಿಷ್ಠ_ಗಾತ್ರ = Wayland_ಗಣ_ಕಿಟಕಿ_ಗರಿಷ್ಠ_ಗಾತ್ರ;
    device->ಗಣ_ಕಿಟಕಿ_ಪೋಷಕ = Wayland_ಗಣ_ಕಿಟಕಿ_ಪೋಷಕ;
    device->ಗಣ_ಕಿಟಕಿ_Modal = Wayland_ಗಣ_ಕಿಟಕಿ_Modal;
    device->ಗಣ_ಕಿಟಕಿ_Opacity = Wayland_ಗಣ_ಕಿಟಕಿ_Opacity;
    device->ಗಣ_ಕಿಟಕಿ_Title = Wayland_ಗಣ_ಕಿಟಕಿ_Title;
    device->ಗಣ_ಕಿಟಕಿ_Icon = Wayland_ಗಣ_ಕಿಟಕಿ_Icon;
    device->Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels = Wayland_Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels;
    device->Get_ಕಿಟಕಿ_Content_Scale = Wayland_Get_ಕಿಟಕಿ_Content_Scale;
    device->Get_ಕಿಟಕಿ_ICCProfile = Wayland_Get_ಕಿಟಕಿ_ICCProfile;
    device->Get_Display_For_ಕಿಟಕಿ = Wayland_Get_Display_For_ಕಿಟಕಿ;
    device->Destroy_ಕಿಟಕಿ = Wayland_Destroy_ಕಿಟಕಿ;
    device->ಗಣ_ಕಿಟಕಿ_ದೊರಕಿತು_Test = Wayland_ಗಣ_ಕಿಟಕಿ_ದೊರಕಿತು_Test;
    device->Flash_ಕಿಟಕಿ = Wayland_Flash_ಕಿಟಕಿ;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_USE_LIBDBUS
    device->Apply_ಕಿಟಕಿ_ಪ್ರಗತಿ = DBUS_Apply_ಕಿಟಕಿ_ಪ್ರಗತಿ;
#ಆದರೆ_ಅಂತ್ಯ // SDL_USE_LIBDBUS
    device->HasScreenKeyboardSupport = Wayland_HasScreenKeyboardSupport;
    device->Show_ಕಿಟಕಿ_System_Menu = Wayland_Show_ಕಿಟಕಿ_System_Menu;
    device->Sync_ಕಿಟಕಿ = Wayland_Sync_ಕಿಟಕಿ;
    device->ಗಣ_ಕಿಟಕಿ_Focusable = Wayland_ಗಣ_ಕಿಟಕಿ_Focusable;
    device->Reconfigure_ಕಿಟಕಿ = Wayland_Reconfigure_ಕಿಟಕಿ;
    device->AcceptDragAndDrop = Wayland_AcceptDragAndDrop;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_USE_LIBDBUS
    ಆದರೆ (SDL_SystemTheme_Init())
        device->system_theme = SDL_SystemTheme_Get();
#ಆದರೆ_ಅಂತ್ಯ

    device->Get_ಪಠ್ಯ_Mime_Types = Wayland_Get_ಪಠ್ಯ_Mime_Types;
    device->ಗಣ_Clipboard_ದತ್ತಾಂಶ = Wayland_ಗಣ_Clipboard_ದತ್ತಾಂಶ;
    device->Get_Clipboard_ದತ್ತಾಂಶ = Wayland_Get_Clipboard_ದತ್ತಾಂಶ;
    device->Has_Clipboard_ದತ್ತಾಂಶ = Wayland_Has_Clipboard_ದತ್ತಾಂಶ;
    device->ಆರಂಭ_ಪಠ್ಯ_ಒಳಹರಿವು = Wayland_ಆರಂಭ_ಪಠ್ಯ_ಒಳಹರಿವು;
    device->Stop_ಪಠ್ಯ_ಒಳಹರಿವು = Wayland_Stop_ಪಠ್ಯ_ಒಳಹರಿವು;
    device->Update_ಪಠ್ಯ_ಒಳಹರಿವು_Area = Wayland_Update_ಪಠ್ಯ_ಒಳಹರಿವು_Area;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_VULKAN
    device->Vulkan_ತುಂಬು_Library = Wayland_Vulkan_ತುಂಬು_Library;
    device->Vulkan_UnloadLibrary = Wayland_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = Wayland_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = Wayland_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = Wayland_Vulkan_DestroySurface;
    device->Vulkan_GetPresentationSupport = Wayland_Vulkan_GetPresentationSupport;
#ಆದರೆ_ಅಂತ್ಯ

    device->ಬಿಡುಗಡೆ = Wayland_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_ಬಹುಲಕ_SWITCHING_EMULATED |
                          VIDEO_DEVICE_CAPS_HAS_POPUP_ಕಿಟಕಿ_SUPPORT |
                          VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS |
                          VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES |
                          VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES;

    ಹಿಂತಿರುಗಿ device;
}

ಸ್ಥಿರ SDL_VideoDevice *Wayland_Preferred_CreateDevice(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ Wayland_CreateDevice(true);
}

ಸ್ಥಿರ SDL_VideoDevice *Wayland_Fallback_CreateDevice(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ Wayland_CreateDevice(false);
}

VideoBootStrap Wayland_preferred_bootstrap = {
    WAYLANDVID_DRIVER_NAME, "SDL Wayland video driver",
    Wayland_Preferred_CreateDevice,
    Wayland_Show_ಸಂದೇಶ_Box,
    true
};

VideoBootStrap Wayland_bootstrap = {
    WAYLANDVID_DRIVER_NAME, "SDL Wayland video driver",
    Wayland_Fallback_CreateDevice,
    Wayland_Show_ಸಂದೇಶ_Box,
    false
};

ಸ್ಥಿರ ಶೂನ್ಯ handle_xdg_output_logical_position(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zxdg_output_v1 *xdg_output, int32_t x, int32_t y)
{
    SDL_Display_ದತ್ತಾಂಶ *ಆಂತರಿಕ = (SDL_Display_ದತ್ತಾಂಶ *)ದತ್ತಾಂಶ;

    ಆಂತರಿಕ->geometry_ಬದಲಾಯಿತು |= ಆಂತರಿಕ->logical.x != x || ಆಂತರಿಕ->logical.y != y;
    ಆಂತರಿಕ->logical.x = x;
    ಆಂತರಿಕ->logical.y = y;
    ಆಂತರಿಕ->has_logical_position = true;
}

ಸ್ಥಿರ ಶೂನ್ಯ handle_xdg_output_logical_ಗಾತ್ರ(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zxdg_output_v1 *xdg_output, int32_t ಅಗಲ, int32_t ಎತ್ತರ)
{
    SDL_Display_ದತ್ತಾಂಶ *ಆಂತರಿಕ = (SDL_Display_ದತ್ತಾಂಶ *)ದತ್ತಾಂಶ;

    ಆಂತರಿಕ->geometry_ಬದಲಾಯಿತು |= ಆಂತರಿಕ->logical.ಅಗಲ != ಅಗಲ || ಆಂತರಿಕ->logical.ಎತ್ತರ != ಎತ್ತರ;
    ಆಂತರಿಕ->logical.ಅಗಲ = ಅಗಲ;
    ಆಂತರಿಕ->logical.ಎತ್ತರ = ಎತ್ತರ;
    ಆಂತರಿಕ->has_logical_ಗಾತ್ರ = true;
}

ಸ್ಥಿರ ಶೂನ್ಯ handle_xdg_output_ಮುಗಿದ(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zxdg_output_v1 *xdg_output)
{
    SDL_Display_ದತ್ತಾಂಶ *ಆಂತರಿಕ = ದತ್ತಾಂಶ;

    /*
     * xdg-output.done events are deprecated and only apply below version 3 of the protocol.
     * A wl-output.done event will be emitted in version 3 or higher.
     */
    ಆದರೆ (zxdg_output_v1_get_ಆವೃತ್ತಿ(ಆಂತರಿಕ->xdg_output) < 3) {
        handle_wl_output_ಮುಗಿದ(ದತ್ತಾಂಶ, ಆಂತರಿಕ->output);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ handle_xdg_output_name(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zxdg_output_v1 *xdg_output, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name)
{
    SDL_Display_ದತ್ತಾಂಶ *ಆಂತರಿಕ = (SDL_Display_ದತ್ತಾಂಶ *)ದತ್ತಾಂಶ;

    // Deprecated as of wl_output v4.
    ಆದರೆ (wl_output_get_ಆವೃತ್ತಿ(ಆಂತರಿಕ->output) < WL_OUTPUT_NAME_SINCE_ಆವೃತ್ತಿ &&
        ಆಂತರಿಕ->display == 0) {
        SDL_free(ಆಂತರಿಕ->wl_output_name);
        ಆಂತರಿಕ->wl_output_name = SDL_strdup(name);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ handle_xdg_output_description(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zxdg_output_v1 *xdg_output, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *description)
{
    SDL_Display_ದತ್ತಾಂಶ *ಆಂತರಿಕ = (SDL_Display_ದತ್ತಾಂಶ *)ದತ್ತಾಂಶ;

    // Deprecated as of wl_output v4.
    ಆದರೆ (wl_output_get_ಆವೃತ್ತಿ(ಆಂತರಿಕ->output) < WL_OUTPUT_DESCRIPTION_SINCE_ಆವೃತ್ತಿ &&
        ಆಂತರಿಕ->display == 0) {
        // xdg-output descriptions, if available, supersede wl-output model names.
        SDL_free(ಆಂತರಿಕ->placeholder.name);
        ಆಂತರಿಕ->placeholder.name = SDL_strdup(description);
    }
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ zxdg_output_v1_listener xdg_output_listener = {
    handle_xdg_output_logical_position,
    handle_xdg_output_logical_ಗಾತ್ರ,
    handle_xdg_output_ಮುಗಿದ,
    handle_xdg_output_name,
    handle_xdg_output_description,
};

ಸ್ಥಿರ ಶೂನ್ಯ ಕೂಡಿಸು_Emulated_Modes(SDL_Display_ದತ್ತಾಂಶ *dispdata, ಪೂರ್ಣಾಂಕ native_ಅಗಲ, ಪೂರ್ಣಾಂಕ native_ಎತ್ತರ)
{
    ರಚನೆ Emulated_ಬಹುಲಕ
    {
        ಪೂರ್ಣಾಂಕ w;
        ಪೂರ್ಣಾಂಕ h;
    };

    // Resolution lists courtesy of XWayland
    ಸ್ಥಿರಾಂಕ ರಚನೆ Emulated_ಬಹುಲಕ ಬಹುಲಕ_list[] = {
        // 16:9 (1.77)
        { 7680, 4320 },
        { 6144, 3160 },
        { 5120, 2880 },
        { 4096, 2304 },
        { 3840, 2160 },
        { 3200, 1800 },
        { 2880, 1620 },
        { 2560, 1440 },
        { 2048, 1152 },
        { 1920, 1080 },
        { 1600, 900 },
        { 1368, 768 },
        { 1280, 720 },
        { 864, 486 },

        // 16:10 (1.6)
        { 2560, 1600 },
        { 1920, 1200 },
        { 1680, 1050 },
        { 1440, 900 },
        { 1280, 800 },

        // 3:2 (1.5)
        { 720, 480 },

        // 4:3 (1.33)
        { 2048, 1536 },
        { 1920, 1440 },
        { 1600, 1200 },
        { 1440, 1080 },
        { 1400, 1050 },
        { 1280, 1024 },
        { 1280, 960 },
        { 1152, 864 },
        { 1024, 768 },
        { 800, 600 },
        { 640, 480 }
    };

    ಪೂರ್ಣಾಂಕ i;
    SDL_Display_ಬಹುಲಕ ಬಹುಲಕ;
    SDL_VideoDisplay *dpy = dispdata->display ? SDL_GetVideoDisplay(dispdata->display) : &dispdata->placeholder;
    ಸ್ಥಿರಾಂಕ bool rot_90 = native_ಅಗಲ < native_ಎತ್ತರ; // Reverse width/height for portrait displays.

    ಗಾಗಿ (i = 0; i < SDL_arraysize(ಬಹುಲಕ_list); ++i) {
        SDL_zero(ಬಹುಲಕ);
        ಬಹುಲಕ.format = dpy->desktop_ಬಹುಲಕ.format;
        ಬಹುಲಕ.refresh_ದರ_numerator = dpy->desktop_ಬಹುಲಕ.refresh_ದರ_numerator;
        ಬಹುಲಕ.refresh_ದರ_denominator = dpy->desktop_ಬಹುಲಕ.refresh_ದರ_denominator;

        ಆದರೆ (rot_90) {
            ಬಹುಲಕ.w = ಬಹುಲಕ_list[i].h;
            ಬಹುಲಕ.h = ಬಹುಲಕ_list[i].w;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಬಹುಲಕ.w = ಬಹುಲಕ_list[i].w;
            ಬಹುಲಕ.h = ಬಹುಲಕ_list[i].h;
        }

        // Only add modes that are smaller than the native mode.
        ಆದರೆ ((ಬಹುಲಕ.w < native_ಅಗಲ && ಬಹುಲಕ.h < native_ಎತ್ತರ) ||
            (ಬಹುಲಕ.w < native_ಅಗಲ && ಬಹುಲಕ.h == native_ಎತ್ತರ) ||
            (ಬಹುಲಕ.w == native_ಅಗಲ && ಬಹುಲಕ.h < native_ಎತ್ತರ)) {
            SDL_ಕೂಡಿಸು_Fullscreen_Display_ಬಹುಲಕ(dpy, &ಬಹುಲಕ);
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ handle_wl_output_geometry(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_output *output, ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ y,
                                      ಪೂರ್ಣಾಂಕ physical_ಅಗಲ_2, ಪೂರ್ಣಾಂಕ physical_ಎತ್ತರ_2, ಪೂರ್ಣಾಂಕ subpixel,
                                      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *make, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *model, ಪೂರ್ಣಾಂಕ transform)
{
    SDL_Display_ದತ್ತಾಂಶ *ಆಂತರಿಕ = (SDL_Display_ದತ್ತಾಂಶ *)ದತ್ತಾಂಶ;

    // Apply the change from wl-output only if xdg-output is not supported
    ಆದರೆ (!ಆಂತರಿಕ->has_logical_position) {
        ಆಂತರಿಕ->geometry_ಬದಲಾಯಿತು |= ಆಂತರಿಕ->logical.x != x || ಆಂತರಿಕ->logical.y != y;
        ಆಂತರಿಕ->logical.x = x;
        ಆಂತರಿಕ->logical.y = y;
    }
    ಆಂತರಿಕ->physical.ಅಗಲ_mm = physical_ಅಗಲ_2;
    ಆಂತರಿಕ->physical.ಎತ್ತರ_mm = physical_ಎತ್ತರ_2;

    // The model is only used for the output name if wl_output or xdg-output haven't provided a description.
    ಆದರೆ (ಆಂತರಿಕ->display == 0 && !ಆಂತರಿಕ->placeholder.name) {
        ಆಂತರಿಕ->placeholder.name = SDL_strdup(model);
    }

    ಆಂತರಿಕ->transform = transform;
#ವ್ಯಾಖ್ಯಾನಿಸು TF_CASE(ಒಳ_2, ಹೊರಹೋಗು)                                 \
    ಸ್ಥಿತಿ WL_OUTPUT_TRANSFORM_##in:                       \
        ಆಂತರಿಕ->orientation = SDL_ORIENTATION_##out; \
        ನಿಲ್ಲಿಸು;
    ಆದರೆ (ಆಂತರಿಕ->physical.ಅಗಲ_mm >= ಆಂತರಿಕ->physical.ಎತ್ತರ_mm) {
        ಆಯ್ಕೆ (transform) {
            TF_CASE(ಸಾಮಾನ್ಯ_2, LANDSCAPE)
            TF_CASE(90, PORTRAIT)
            TF_CASE(180, LANDSCAPE_FLIPPED)
            TF_CASE(270, PORTRAIT_FLIPPED)
            TF_CASE(FLIPPED, LANDSCAPE_FLIPPED)
            TF_CASE(FLIPPED_90, PORTRAIT_FLIPPED)
            TF_CASE(FLIPPED_180, LANDSCAPE)
            TF_CASE(FLIPPED_270, PORTRAIT)
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆಯ್ಕೆ (transform) {
            TF_CASE(ಸಾಮಾನ್ಯ_2, PORTRAIT)
            TF_CASE(90, LANDSCAPE)
            TF_CASE(180, PORTRAIT_FLIPPED)
            TF_CASE(270, LANDSCAPE_FLIPPED)
            TF_CASE(FLIPPED, PORTRAIT_FLIPPED)
            TF_CASE(FLIPPED_90, LANDSCAPE_FLIPPED)
            TF_CASE(FLIPPED_180, PORTRAIT)
            TF_CASE(FLIPPED_270, LANDSCAPE)
        }
    }
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು TF_CASE
}

ಸ್ಥಿರ ಶೂನ್ಯ handle_wl_output_ಬಹುಲಕ(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_output *output, uint32_t flags,
                                  ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಪೂರ್ಣಾಂಕ refresh)
{
    SDL_Display_ದತ್ತಾಂಶ *ಆಂತರಿಕ = (SDL_Display_ದತ್ತಾಂಶ *)ದತ್ತಾಂಶ;

    ಆದರೆ (flags & WL_OUTPUT_ಬಹುಲಕ_CURRENT) {
        ಆಂತರಿಕ->geometry_ಬದಲಾಯಿತು |= ಆಂತರಿಕ->pixel.ಅಗಲ != ಅಗಲ || ಆಂತರಿಕ->pixel.ಎತ್ತರ != ಎತ್ತರ;
        ಆಂತರಿಕ->pixel.ಅಗಲ = ಅಗಲ;
        ಆಂತರಿಕ->pixel.ಎತ್ತರ = ಎತ್ತರ;

        /*
         * Don't rotate this yet, wl-output coordinates are transformed in
         * handle_done and xdg-output coordinates are pre-transformed.
         */
        ಆದರೆ (!ಆಂತರಿಕ->has_logical_ಗಾತ್ರ) {
            ಆಂತರಿಕ->geometry_ಬದಲಾಯಿತು |= ಆಂತರಿಕ->logical.ಅಗಲ != ಅಗಲ || ಆಂತರಿಕ->logical.ಎತ್ತರ != ಎತ್ತರ;
            ಆಂತರಿಕ->logical.ಅಗಲ = ಅಗಲ;
            ಆಂತರಿಕ->logical.ಎತ್ತರ = ಎತ್ತರ;
        }

        ಆಂತರಿಕ->refresh = refresh;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ handle_wl_output_ಮುಗಿದ(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_output *output)
{
    ಸ್ಥಿರಾಂಕ bool ಬಹುಲಕ_emulation_enabled = SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_ಬಹುಲಕ_EMULATION, true);
    SDL_Display_ದತ್ತಾಂಶ *ಆಂತರಿಕ = (SDL_Display_ದತ್ತಾಂಶ *)ದತ್ತಾಂಶ;
    SDL_Video_ದತ್ತಾಂಶ *video = ಆಂತರಿಕ->videodata;
    SDL_Display_ಬಹುಲಕ native_ಬಹುಲಕ, desktop_ಬಹುಲಕ;

    /*
     * When using xdg-output, two wl-output.done events will be emitted:
     * one at the completion of wl-display and one at the completion of xdg-output.
     *
     * All required events must be received before proceeding.
     */
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ event_await_ಎಣಿಕೆ = 1 + (ಆಂತರಿಕ->xdg_output != ಖಾಲಿ);

    ಆಂತರಿಕ->wl_output_ಮುಗಿದ_ಎಣಿಕೆ = SDL_min(ಆಂತರಿಕ->wl_output_ಮುಗಿದ_ಎಣಿಕೆ + 1, event_await_ಎಣಿಕೆ + 1);

    ಆದರೆ (ಆಂತರಿಕ->wl_output_ಮುಗಿದ_ಎಣಿಕೆ < event_await_ಎಣಿಕೆ) {
        ಹಿಂತಿರುಗಿ;
    }

    // If the display was already created, reset and rebuild the mode list.
    SDL_VideoDisplay *dpy = SDL_GetVideoDisplay(ಆಂತರಿಕ->display);
    ಆದರೆ (dpy) {
        SDL_ResetFullscreenDisplayModes(dpy);
    }

    // The native display resolution
    SDL_zero(native_ಬಹುಲಕ);
    native_ಬಹುಲಕ.format = SDL_PIXELFORMAT_XRGB8888;

    // Transform the pixel values, if necessary.
    ಆದರೆ (ಆಂತರಿಕ->transform & WL_OUTPUT_TRANSFORM_90) {
        native_ಬಹುಲಕ.w = ಆಂತರಿಕ->pixel.ಎತ್ತರ;
        native_ಬಹುಲಕ.h = ಆಂತರಿಕ->pixel.ಅಗಲ;
    } ಇಲ್ಲದಿದ್ದರೆ {
        native_ಬಹುಲಕ.w = ಆಂತರಿಕ->pixel.ಅಗಲ;
        native_ಬಹುಲಕ.h = ಆಂತರಿಕ->pixel.ಎತ್ತರ;
    }
    native_ಬಹುಲಕ.refresh_ದರ_numerator = ಆಂತರಿಕ->refresh;
    native_ಬಹುಲಕ.refresh_ದರ_denominator = 1000;

    ಆದರೆ (ಆಂತರಿಕ->has_logical_ಗಾತ್ರ) { // If xdg-output is present...
        ಆದರೆ (native_ಬಹುಲಕ.w != ಆಂತರಿಕ->logical.ಅಗಲ || native_ಬಹುಲಕ.h != ಆಂತರಿಕ->logical.ಎತ್ತರ) {
            // ...and the compositor scales the logical viewport...
            ಆದರೆ (video->viewporter) {
                // ...and viewports are supported, calculate the true scale of the output.
                ಆಂತರಿಕ->scale_ಗುಣಕ_2 = (ದ್ವಿಗುಣ)native_ಬಹುಲಕ.w / (ದ್ವಿಗುಣ)ಆಂತರಿಕ->logical.ಅಗಲ;
            } ಇಲ್ಲದಿದ್ದರೆ {
                // ...otherwise, the 'native' pixel values are a multiple of the logical screen size.
                ಆಂತರಿಕ->scale_ಗುಣಕ_2 = ಆಂತರಿಕ->integer_scale_ಗುಣಕ;
                ಆಂತರಿಕ->pixel.ಅಗಲ = ಆಂತರಿಕ->logical.ಅಗಲ * ಆಂತರಿಕ->integer_scale_ಗುಣಕ;
                ಆಂತರಿಕ->pixel.ಎತ್ತರ = ಆಂತರಿಕ->logical.ಎತ್ತರ * ಆಂತರಿಕ->integer_scale_ಗುಣಕ;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            /* ...and the output viewport is not scaled in the global compositing
             * space, the output dimensions need to be divided by the scale factor.
             *
             * NOTE: This path is needed for old versions of GNOME that predate fractional scaling.
             */
            ಆಂತರಿಕ->scale_ಗುಣಕ_2 = ಆಂತರಿಕ->integer_scale_ಗುಣಕ;
            ಆಂತರಿಕ->logical.ಅಗಲ /= ಆಂತರಿಕ->integer_scale_ಗುಣಕ;
            ಆಂತರಿಕ->logical.ಎತ್ತರ /= ಆಂತರಿಕ->integer_scale_ಗುಣಕ;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        /* Calculate the points from the pixel values, if xdg-output isn't present.
         * Use the native mode pixel values since they are pre-transformed.
         */
        ಆಂತರಿಕ->scale_ಗುಣಕ_2 = ಆಂತರಿಕ->integer_scale_ಗುಣಕ;
        ಆಂತರಿಕ->logical.ಅಗಲ = native_ಬಹುಲಕ.w / ಆಂತರಿಕ->integer_scale_ಗುಣಕ;
        ಆಂತರಿಕ->logical.ಎತ್ತರ = native_ಬಹುಲಕ.h / ಆಂತರಿಕ->integer_scale_ಗುಣಕ;
    }

    // The scaled desktop mode
    SDL_zero(desktop_ಬಹುಲಕ);
    desktop_ಬಹುಲಕ.format = SDL_PIXELFORMAT_XRGB8888;

    ಆದರೆ (!video->scale_ಗಮ್ಯ_display_enabled) {
        desktop_ಬಹುಲಕ.w = ಆಂತರಿಕ->logical.ಅಗಲ;
        desktop_ಬಹುಲಕ.h = ಆಂತರಿಕ->logical.ಎತ್ತರ;
        desktop_ಬಹುಲಕ.pixel_density = (ದಶಮಾಂಶ)ಆಂತರಿಕ->scale_ಗುಣಕ_2;
    } ಇಲ್ಲದಿದ್ದರೆ {
        desktop_ಬಹುಲಕ.w = native_ಬಹುಲಕ.w;
        desktop_ಬಹುಲಕ.h = native_ಬಹುಲಕ.h;
        desktop_ಬಹುಲಕ.pixel_density = 1.0f;
    }

    desktop_ಬಹುಲಕ.refresh_ದರ_numerator = ಆಂತರಿಕ->refresh;
    desktop_ಬಹುಲಕ.refresh_ದರ_denominator = 1000;

    ಆದರೆ (ಆಂತರಿಕ->display > 0) {
        dpy = SDL_GetVideoDisplay(ಆಂತರಿಕ->display);
    } ಇಲ್ಲದಿದ್ದರೆ {
        dpy = &ಆಂತರಿಕ->placeholder;
    }

    ಆದರೆ (video->scale_ಗಮ್ಯ_display_enabled) {
        SDL_ಗಣ_Display_Content_Scale(dpy, (ದಶಮಾಂಶ)ಆಂತರಿಕ->scale_ಗುಣಕ_2);
    }

    // Set the desktop display mode.
    SDL_ಗಣ_Desktop_Display_ಬಹುಲಕ(dpy, &desktop_ಬಹುಲಕ);

    // Expose the unscaled, native resolution if the scale is 1.0 or viewports are available...
    ಆದರೆ (ಆಂತರಿಕ->scale_ಗುಣಕ_2 == 1.0 || video->viewporter) {
        SDL_ಕೂಡಿಸು_Fullscreen_Display_ಬಹುಲಕ(dpy, &native_ಬಹುಲಕ);
        ಆದರೆ (native_ಬಹುಲಕ.w != desktop_ಬಹುಲಕ.w ||
            native_ಬಹುಲಕ.h != desktop_ಬಹುಲಕ.h) {
            SDL_ಕೂಡಿಸು_Fullscreen_Display_ಬಹುಲಕ(dpy, &desktop_ಬಹುಲಕ);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        // ...otherwise expose the integer scaled variants of the desktop resolution down to 1.
        desktop_ಬಹುಲಕ.pixel_density = 1.0f;

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = (ಪೂರ್ಣಾಂಕ)ಆಂತರಿಕ->scale_ಗುಣಕ_2; i > 0; --i) {
            desktop_ಬಹುಲಕ.w = ಆಂತರಿಕ->logical.ಅಗಲ * i;
            desktop_ಬಹುಲಕ.h = ಆಂತರಿಕ->logical.ಎತ್ತರ * i;
            SDL_ಕೂಡಿಸು_Fullscreen_Display_ಬಹುಲಕ(dpy, &desktop_ಬಹುಲಕ);
        }
    }

    // Add emulated modes if wp_viewporter is supported and mode emulation is enabled.
    ಆದರೆ (video->viewporter && ಬಹುಲಕ_emulation_enabled) {
        // The transformed display pixel width/height must be used here.
        ಕೂಡಿಸು_Emulated_Modes(ಆಂತರಿಕ, native_ಬಹುಲಕ.w, native_ಬಹುಲಕ.h);
    }

    ಆದರೆ (ಆಂತರಿಕ->display == 0) {
        // First time getting display info, initialize the VideoDisplay
        ಆದರೆ (ಆಂತರಿಕ->physical.ಅಗಲ_mm >= ಆಂತರಿಕ->physical.ಎತ್ತರ_mm) {
            ಆಂತರಿಕ->placeholder.natural_orientation = SDL_ORIENTATION_LANDSCAPE;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಆಂತರಿಕ->placeholder.natural_orientation = SDL_ORIENTATION_PORTRAIT;
        }
        ಆಂತರಿಕ->placeholder.current_orientation = ಆಂತರಿಕ->orientation;
        ಆಂತರಿಕ->placeholder.ಆಂತರಿಕ = ಆಂತರಿಕ;

        ಆಂತರಿಕ->placeholder.props = SDL_CreateProperties();
        SDL_ಗಣ_ಸೂಚಕ_Property(ಆಂತರಿಕ->placeholder.props, SDL_PROP_DISPLAY_WAYLAND_WL_OUTPUT_ಸೂಚಕ, ಆಂತರಿಕ->output);

        // During initialization, the displays will be added after enumeration is complete.
        ಆದರೆ (!video->initializing) {
            ಆದರೆ (video->wp_color_manager_v1) {
                Wayland_GetColorInfoForOutput(ಆಂತರಿಕ, false);
            }
            ಆದರೆ (video->scale_ಗಮ್ಯ_display_enabled) {
                Wayland_DeriveOutputPixelCoordinates(video);
            }

            ಆಂತರಿಕ->display = SDL_ಕೂಡಿಸು_Video_Display(&ಆಂತರಿಕ->placeholder, true);
            Wayland_Refresh_ಕಿಟಕಿ_Positions();

            SDL_free(ಆಂತರಿಕ->placeholder.name);
            SDL_zero(ಆಂತರಿಕ->placeholder);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_SendDisplayEvent(dpy, SDL_EVENT_DISPLAY_ORIENTATION, ಆಂತರಿಕ->orientation, 0);

        ಆದರೆ (ಆಂತರಿಕ->geometry_ಬದಲಾಯಿತು) {
            ಆದರೆ (video->scale_ಗಮ್ಯ_display_enabled) {
                Wayland_DeriveOutputPixelCoordinates(video);
            }

            SDL_SendDisplayEvent(dpy, SDL_EVENT_DISPLAY_MOVED, 0, 0);
            Wayland_Refresh_ಕಿಟಕಿ_Positions();
        }
    }

    ಆಂತರಿಕ->geometry_ಬದಲಾಯಿತು = false;
}

ಸ್ಥಿರ ಶೂನ್ಯ handle_wl_output_scale(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_output *output, int32_t ಗುಣಕ)
{
    SDL_Display_ದತ್ತಾಂಶ *ಆಂತರಿಕ = (SDL_Display_ದತ್ತಾಂಶ *)ದತ್ತಾಂಶ;
    ಆಂತರಿಕ->integer_scale_ಗುಣಕ = ಗುಣಕ;
}

ಸ್ಥಿರ ಶೂನ್ಯ handle_wl_output_name(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_output *wl_output, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name)
{
    SDL_Display_ದತ್ತಾಂಶ *ಆಂತರಿಕ = (SDL_Display_ದತ್ತಾಂಶ *)ದತ್ತಾಂಶ;

    SDL_free(ಆಂತರಿಕ->wl_output_name);
    ಆಂತರಿಕ->wl_output_name = SDL_strdup(name);
}

ಸ್ಥಿರ ಶೂನ್ಯ handle_wl_output_description(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_output *wl_output, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *description)
{
    SDL_Display_ದತ್ತಾಂಶ *ಆಂತರಿಕ = (SDL_Display_ದತ್ತಾಂಶ *)ದತ್ತಾಂಶ;

    ಆದರೆ (ಆಂತರಿಕ->display == 0) {
        // The description, if available, supersedes the model name.
        SDL_free(ಆಂತರಿಕ->placeholder.name);
        ಆಂತರಿಕ->placeholder.name = SDL_strdup(description);
    }
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ wl_output_listener output_listener = {
    handle_wl_output_geometry,   // Version 1
    handle_wl_output_ಬಹುಲಕ,       // Version 1
    handle_wl_output_ಮುಗಿದ,       // Version 2
    handle_wl_output_scale,      // Version 2
    handle_wl_output_name,       // Version 4
    handle_wl_output_description // Version 4
};

ಸ್ಥಿರ ಶೂನ್ಯ handle_output_image_description_ಬದಲಾಯಿತು(ಶೂನ್ಯ *ದತ್ತಾಂಶ,
                                                    ರಚನೆ wp_color_management_output_v1 *wp_color_management_output_v1)
{
    SDL_Display_ದತ್ತಾಂಶ *display = (SDL_Display_ದತ್ತಾಂಶ *)ದತ್ತಾಂಶ;
    Wayland_GetColorInfoForOutput(display, false);
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ wp_color_management_output_v1_listener wp_color_management_output_listener = {
    handle_output_image_description_ಬದಲಾಯಿತು
};

ಸ್ಥಿರ bool Wayland_ಕೂಡಿಸು_display(SDL_Video_ದತ್ತಾಂಶ *d, uint32_t id, uint32_t ಆವೃತ್ತಿ)
{
    ರಚನೆ wl_output *output;
    SDL_Display_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ;

    output = wl_registry_bind(d->registry, id, &wl_output_interface, ಆವೃತ್ತಿ);
    ಆದರೆ (!output) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Failed to retrieve output.");
    }
    ದತ್ತಾಂಶ = (SDL_Display_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(*ದತ್ತಾಂಶ));
    ದತ್ತಾಂಶ->videodata = d;
    ದತ್ತಾಂಶ->output = output;
    ದತ್ತಾಂಶ->registry_id = id;
    ದತ್ತಾಂಶ->scale_ಗುಣಕ_2 = 1.0f;
    ದತ್ತಾಂಶ->integer_scale_ಗುಣಕ = 1;

    wl_output_ಕೂಡಿಸು_listener(output, &output_listener, ದತ್ತಾಂಶ);
    SDL_WAYLAND_ರಿಜಿಸ್ಟರ್_output(output);

    // Keep a list of outputs for sorting and deferred protocol initialization.
    ಆದರೆ (d->output_ಎಣಿಕೆ == d->output_max) {
        d->output_max += 4;
        d->output_list = SDL_realloc(d->output_list, ಗಾತ್ರ(SDL_Display_ದತ್ತಾಂಶ *) * d->output_max);
    }
    d->output_list[d->output_ಎಣಿಕೆ++] = ದತ್ತಾಂಶ;

    ಆದರೆ (ದತ್ತಾಂಶ->videodata->xdg_output_manager) {
        ದತ್ತಾಂಶ->xdg_output = zxdg_output_manager_v1_get_xdg_output(ದತ್ತಾಂಶ->videodata->xdg_output_manager, output);
        zxdg_output_v1_ಕೂಡಿಸು_listener(ದತ್ತಾಂಶ->xdg_output, &xdg_output_listener, ದತ್ತಾಂಶ);
    }
    ಆದರೆ (ದತ್ತಾಂಶ->videodata->wp_color_manager_v1) {
        ದತ್ತಾಂಶ->wp_color_management_output = wp_color_manager_v1_get_output(ದತ್ತಾಂಶ->videodata->wp_color_manager_v1, output);
        wp_color_management_output_v1_ಕೂಡಿಸು_listener(ದತ್ತಾಂಶ->wp_color_management_output, &wp_color_management_output_listener, ದತ್ತಾಂಶ);

        // If not initializing, this will be queried synchronously in wl_output.done.
        ಆದರೆ (d->initializing) {
            Wayland_GetColorInfoForOutput(ದತ್ತಾಂಶ, true);
        }
    }
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_free_display(SDL_VideoDisplay *display, bool send_event)
{
    ಆದರೆ (display) {
        SDL_Display_ದತ್ತಾಂಶ *display_ದತ್ತಾಂಶ = display->ಆಂತರಿಕ;

        /* A preceding surface leave event is not guaranteed when an output is removed,
         * so ensure that no window continues to hold a reference to a removed output.
         */
        ಗಾಗಿ (SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = SDL_GetVideoDevice()->windows; ಕಿಟಕಿ; ಕಿಟಕಿ = ಕಿಟಕಿ->ಮುಂದಿನ) {
            Wayland_Remove_Output_From_ಕಿಟಕಿ(ಕಿಟಕಿ->ಆಂತರಿಕ, display_ದತ್ತಾಂಶ);
        }

        SDL_free(display_ದತ್ತಾಂಶ->wl_output_name);

        ಆದರೆ (display_ದತ್ತಾಂಶ->wp_color_management_output) {
            Wayland_FreeColorInfoState(display_ದತ್ತಾಂಶ->color_info_state);
            wp_color_management_output_v1_destroy(display_ದತ್ತಾಂಶ->wp_color_management_output);
        }

        ಆದರೆ (display_ದತ್ತಾಂಶ->xdg_output) {
            zxdg_output_v1_destroy(display_ದತ್ತಾಂಶ->xdg_output);
        }

        ಆದರೆ (wl_output_get_ಆವೃತ್ತಿ(display_ದತ್ತಾಂಶ->output) >= WL_OUTPUT_RELEASE_SINCE_ಆವೃತ್ತಿ) {
            wl_output_release(display_ದತ್ತಾಂಶ->output);
        } ಇಲ್ಲದಿದ್ದರೆ {
            wl_output_destroy(display_ದತ್ತಾಂಶ->output);
        }

        SDL_DelVideoDisplay(display->id, send_event);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_FinalizeDisplays(SDL_Video_ದತ್ತಾಂಶ *vid)
{
    Wayland_ವಿಂಗಡಿಸು_Outputs(vid);

    ಗಾಗಿ(ಪೂರ್ಣಾಂಕ i = 0; i < vid->output_ಎಣಿಕೆ; ++i) {
        SDL_Display_ದತ್ತಾಂಶ *d = vid->output_list[i];
        d->display = SDL_ಕೂಡಿಸು_Video_Display(&d->placeholder, false);
        SDL_free(d->placeholder.name);
        SDL_zero(d->placeholder);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_init_xdg_output(SDL_Video_ದತ್ತಾಂಶ *d)
{
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < d->output_ಎಣಿಕೆ; ++i) {
        SDL_Display_ದತ್ತಾಂಶ *disp = d->output_list[i];
        disp->xdg_output = zxdg_output_manager_v1_get_xdg_output(disp->videodata->xdg_output_manager, disp->output);
        zxdg_output_v1_ಕೂಡಿಸು_listener(disp->xdg_output, &xdg_output_listener, disp);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_InitColorManager(SDL_Video_ದತ್ತಾಂಶ *d)
{
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < d->output_ಎಣಿಕೆ; ++i) {
        SDL_Display_ದತ್ತಾಂಶ *disp = d->output_list[i];
        disp->wp_color_management_output = wp_color_manager_v1_get_output(disp->videodata->wp_color_manager_v1, disp->output);
        wp_color_management_output_v1_ಕೂಡಿಸು_listener(disp->wp_color_management_output, &wp_color_management_output_listener, disp);
        Wayland_GetColorInfoForOutput(disp, true);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ handle_xdg_session_created(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ xdg_session_v1 *xdg_session_v1, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *id)
{
    SDL_ಗಣ_String_Property(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, id);
}

ಸ್ಥಿರ ಶೂನ್ಯ handle_xdg_session_restored(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ xdg_session_v1 *xdg_session_v1)
{
    // NOP
}

ಸ್ಥಿರ ಶೂನ್ಯ handle_xdg_session_replaced(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ xdg_session_v1 *xdg_session_v1)
{
    SDL_VideoDevice *viddev = SDL_GetVideoDevice();
    SDL_Video_ದತ್ತಾಂಶ *viddata = ದತ್ತಾಂಶ;

    // Clean up all session objects, as they have become inert, and should be destroyed.
    SDL_ಗಣ_String_Property(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, ಖಾಲಿ);

    ಗಾಗಿ (SDL_ಕಿಟಕಿ *w = viddev->windows; w; w = w->ಮುಂದಿನ) {
        SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *d = w->ಆಂತರಿಕ;

        ಆದರೆ (d->xdg_toplevel_session) {
            xdg_toplevel_session_v1_destroy(d->xdg_toplevel_session);
            d->xdg_toplevel_session = ಖಾಲಿ;

            SDL_free(d->session_id);
            d->session_id = ಖಾಲಿ;
        }
    }

    ಆದರೆ (viddata->xdg_session) {
        xdg_session_v1_destroy(viddata->xdg_session);
        viddata->xdg_session = ಖಾಲಿ;
    }
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ xdg_session_v1_listener xdg_session_listener = {
    .created  = handle_xdg_session_created,
    .restored = handle_xdg_session_restored,
    .replaced = handle_xdg_session_replaced
};

ಶೂನ್ಯ Wayland_CreateSession(SDL_Video_ದತ್ತಾಂಶ *viddata)
{
    ಆದರೆ (!viddata->xdg_session_manager) {
        // Set the ID string to null if session management is not available.
        SDL_ಗಣ_String_Property(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, ಖಾಲಿ);
        ಹಿಂತಿರುಗಿ;
    }

    // Register a new session, if one does not yet exist.
    ಆದರೆ (!viddata->xdg_session) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *session_id = SDL_GetStringProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, ಖಾಲಿ);
        ಆದರೆ (session_id) {
            ಆದರೆ (*session_id == '\0') {
                // Create a new session if the ID string is empty.
                session_id = ಖಾಲಿ;
            }

            ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ xdg_session_manager_v1_reason reason = session_id ? XDG_SESSION_MANAGER_V1_REASON_SESSION_RESTORE : XDG_SESSION_MANAGER_V1_REASON_LAUNCH;
            viddata->xdg_session = xdg_session_manager_v1_get_session(viddata->xdg_session_manager, reason, session_id);
            xdg_session_v1_ಕೂಡಿಸು_listener(viddata->xdg_session, &xdg_session_listener, viddata);
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_SessionDestroy(SDL_Video_ದತ್ತಾಂಶ *viddata)
{
    // If the session string was cleared, remove the session.
    ಆದರೆ (viddata->xdg_session) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *session_id = SDL_GetStringProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, ಖಾಲಿ);
        ಆದರೆ (!session_id || *session_id == '\0') {
            xdg_session_v1_remove(viddata->xdg_session);

            WAYLAND_wl_display_roundtrip(viddata->display);
        } ಇಲ್ಲದಿದ್ದರೆ {
            xdg_session_v1_destroy(viddata->xdg_session);
        }

        viddata->xdg_session = ಖಾಲಿ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ handle_xdg_wm_ತಳ_ping(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ xdg_wm_ತಳ *xdg, uint32_t serial)
{
    xdg_wm_ತಳ_pong(xdg, serial);
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ xdg_wm_ತಳ_listener xdg_wm_ತಳ_listener_2 = {
    handle_xdg_wm_ತಳ_ping
};

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
ಸ್ಥಿರ ಶೂನ್ಯ libdecor_error(ರಚನೆ libdecor *context,
                           ಎಣಿಕೆ libdecor_error error,
                           ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸಂದೇಶ)
{
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "libdecor error (%d): %s", error, ಸಂದೇಶ);
}

ಸ್ಥಿರ ರಚನೆ libdecor_interface libdecor_interface = {
    libdecor_error
};
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಶೂನ್ಯ handle_registry_global(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_registry *registry, uint32_t id,
                                   ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *interface, uint32_t ಆವೃತ್ತಿ)
{
    SDL_Video_ದತ್ತಾಂಶ *d = ದತ್ತಾಂಶ;

    ಆದರೆ (SDL_strcmp(interface, wl_compositor_interface.name) == 0) {
        d->compositor = wl_registry_bind(d->registry, id, &wl_compositor_interface, SDL_min(SDL_WL_COMPOSITOR_ಆವೃತ್ತಿ, ಆವೃತ್ತಿ));
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(interface, wl_subcompositor_interface.name) == 0) {
        d->subcompositor = wl_registry_bind(d->registry, id, &wl_subcompositor_interface, 1);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(interface, wl_output_interface.name) == 0) {
        Wayland_ಕೂಡಿಸು_display(d, id, SDL_min(ಆವೃತ್ತಿ, SDL_WL_OUTPUT_ಆವೃತ್ತಿ));
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(interface, wl_seat_interface.name) == 0) {
        ರಚನೆ wl_seat *seat = wl_registry_bind(d->registry, id, &wl_seat_interface, SDL_min(SDL_WL_SEAT_ಆವೃತ್ತಿ, ಆವೃತ್ತಿ));
        Wayland_DisplayCreateSeat(d, seat, id);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(interface, xdg_wm_ತಳ_interface.name) == 0) {
        d->shell.xdg = wl_registry_bind(d->registry, id, &xdg_wm_ತಳ_interface, SDL_min(ಆವೃತ್ತಿ, 7));
        xdg_wm_ತಳ_ಕೂಡಿಸು_listener(d->shell.xdg, &xdg_wm_ತಳ_listener_2, ಖಾಲಿ);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(interface, wl_shm_interface.name) == 0) {
        d->shm = wl_registry_bind(registry, id, &wl_shm_interface, SDL_min(SDL_WL_SHM_ಆವೃತ್ತಿ, ಆವೃತ್ತಿ));
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(interface, zwp_relative_ಸೂಚಕ_manager_v1_interface.name) == 0) {
        d->relative_ಸೂಚಕ_manager = wl_registry_bind(d->registry, id, &zwp_relative_ಸೂಚಕ_manager_v1_interface, 1);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(interface, zwp_ಸೂಚಕ_constraints_v1_interface.name) == 0) {
        d->ಸೂಚಕ_constraints = wl_registry_bind(d->registry, id, &zwp_ಸೂಚಕ_constraints_v1_interface, 1);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(interface, zwp_keyboard_shortcuts_inhibit_manager_v1_interface.name) == 0) {
        d->ಕೀಲಿ_inhibitor_manager = wl_registry_bind(d->registry, id, &zwp_keyboard_shortcuts_inhibit_manager_v1_interface, 1);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(interface, zwp_idle_inhibit_manager_v1_interface.name) == 0) {
        d->idle_inhibit_manager = wl_registry_bind(d->registry, id, &zwp_idle_inhibit_manager_v1_interface, 1);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(interface, xdg_activation_v1_interface.name) == 0) {
        d->activation_manager = wl_registry_bind(d->registry, id, &xdg_activation_v1_interface, 1);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(interface, zwp_ಪಠ್ಯ_ಒಳಹರಿವು_manager_v3_interface.name) == 0) {
        d->ಪಠ್ಯ_ಒಳಹರಿವು_manager = wl_registry_bind(d->registry, id, &zwp_ಪಠ್ಯ_ಒಳಹರಿವು_manager_v3_interface, 1);
        Wayland_Display_Init_ಪಠ್ಯ_ಒಳಹರಿವು_Manager(d, id);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(interface, wl_ದತ್ತಾಂಶ_device_manager_interface.name) == 0) {
        d->ದತ್ತಾಂಶ_device_manager = wl_registry_bind(d->registry, id, &wl_ದತ್ತಾಂಶ_device_manager_interface, SDL_min(3, ಆವೃತ್ತಿ));
        Wayland_Display_Init_ದತ್ತಾಂಶ_Device_Manager(d);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(interface, zwp_primary_selection_device_manager_v1_interface.name) == 0) {
        d->primary_selection_device_manager = wl_registry_bind(d->registry, id, &zwp_primary_selection_device_manager_v1_interface, 1);
        Wayland_DisplayInitPrimarySelectionDeviceManager(d);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(interface, zxdg_decoration_manager_v1_interface.name) == 0) {
        d->decoration_manager = wl_registry_bind(d->registry, id, &zxdg_decoration_manager_v1_interface, SDL_min(2, ಆವೃತ್ತಿ));
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(interface, zwp_tablet_manager_v2_interface.name) == 0) {
        d->tablet_manager = wl_registry_bind(d->registry, id, &zwp_tablet_manager_v2_interface, 1);
        Wayland_DisplayInitTabletManager(d);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(interface, zxdg_output_manager_v1_interface.name) == 0) {
        ಆವೃತ್ತಿ = SDL_min(ಆವೃತ್ತಿ, 3); // Versions 1 through 3 are supported.
        d->xdg_output_manager = wl_registry_bind(d->registry, id, &zxdg_output_manager_v1_interface, ಆವೃತ್ತಿ);
        Wayland_init_xdg_output(d);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(interface, wp_viewporter_interface.name) == 0) {
        d->viewporter = wl_registry_bind(d->registry, id, &wp_viewporter_interface, 1);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(interface, wp_fractional_scale_manager_v1_interface.name) == 0) {
        d->fractional_scale_manager = wl_registry_bind(d->registry, id, &wp_fractional_scale_manager_v1_interface, 1);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(interface, zwp_ಒಳಹರಿವು_timestamps_manager_v1_interface.name) == 0) {
        d->ಒಳಹರಿವು_timestamps_manager = wl_registry_bind(d->registry, id, &zwp_ಒಳಹರಿವು_timestamps_manager_v1_interface, 1);
        Wayland_Display_Init_ಒಳಹರಿವು_Timestamp_Manager(d);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(interface, wp_cursor_shape_manager_v1_interface.name) == 0) {
        d->cursor_shape_manager = wl_registry_bind(d->registry, id, &wp_cursor_shape_manager_v1_interface, SDL_min(ಆವೃತ್ತಿ, 2));
        Wayland_DisplayInitCursorShapeManager(d);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(interface, zxdg_exporter_v2_interface.name) == 0) {
        d->zxdg_exporter_v2 = wl_registry_bind(d->registry, id, &zxdg_exporter_v2_interface, 1);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(interface, xdg_wm_dialog_v1_interface.name) == 0) {
        d->xdg_wm_dialog_v1 = wl_registry_bind(d->registry, id, &xdg_wm_dialog_v1_interface, 1);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(interface, wp_alpha_modifier_v1_interface.name) == 0) {
        d->wp_alpha_modifier_v1 = wl_registry_bind(d->registry, id, &wp_alpha_modifier_v1_interface, 1);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(interface, xdg_toplevel_icon_manager_v1_interface.name) == 0) {
        d->xdg_toplevel_icon_manager_v1 = wl_registry_bind(d->registry, id, &xdg_toplevel_icon_manager_v1_interface, 1);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(interface, frog_color_management_factory_v1_interface.name) == 0) {
        d->frog_color_management_factory_v1 = wl_registry_bind(d->registry, id, &frog_color_management_factory_v1_interface, 1);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(interface, wp_color_manager_v1_interface.name) == 0) {
        d->wp_color_manager_v1 = wl_registry_bind(d->registry, id, &wp_color_manager_v1_interface, SDL_min(ಆವೃತ್ತಿ, 2));
        Wayland_InitColorManager(d);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(interface, wp_ಸೂಚಕ_warp_v1_interface.name) == 0) {
        d->wp_ಸೂಚಕ_warp_v1 = wl_registry_bind(d->registry, id, &wp_ಸೂಚಕ_warp_v1_interface, 1);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(interface, zwp_ಸೂಚಕ_gestures_v1_interface.name) == 0) {
        d->zwp_ಸೂಚಕ_gestures = wl_registry_bind(d->registry, id, &zwp_ಸೂಚಕ_gestures_v1_interface, SDL_min(ಆವೃತ್ತಿ, 3));
        Wayland_Display_Init_ಸೂಚಕ_Gesture_Manager(d);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(interface, wp_single_pixel_ಬಫರ್_manager_v1_interface.name) == 0) {
        d->single_pixel_ಬಫರ್_manager = wl_registry_bind(d->registry, id, &wp_single_pixel_ಬಫರ್_manager_v1_interface, 1);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(interface, xdg_session_manager_v1_interface.name) == 0) {
        d->xdg_session_manager = wl_registry_bind(d->registry, id, &xdg_session_manager_v1_interface, 1);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(interface, xdg_toplevel_ಟ್ಯಾಗ್_manager_v1_interface.name) == 0) {
        d->xdg_toplevel_ಟ್ಯಾಗ್_manager = wl_registry_bind(d->registry, id, &xdg_toplevel_ಟ್ಯಾಗ್_manager_v1_interface, 1);
    }
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_WL_FIXES_ಆವೃತ್ತಿ
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcmp(interface, wl_fixes_interface.name) == 0) {
        d->wl_fixes = wl_registry_bind(d->registry, id, &wl_fixes_interface, SDL_min(SDL_WL_FIXES_ಆವೃತ್ತಿ, ಆವೃತ್ತಿ));
    }
#ಆದರೆ_ಅಂತ್ಯ
}

ಸ್ಥಿರ ಶೂನ್ಯ handle_registry_remove_global(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_registry *registry, uint32_t id)
{
    SDL_Video_ದತ್ತಾಂಶ *d = ದತ್ತಾಂಶ;

    // We don't get an interface, just an ID, so check outputs and seats.
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < d->output_ಎಣಿಕೆ; ++i) {
        SDL_Display_ದತ್ತಾಂಶ *disp = d->output_list[i];
        ಆದರೆ (disp->registry_id == id) {
            Wayland_free_display(SDL_GetVideoDisplay(disp->display), true);

            ಆದರೆ (i < d->output_ಎಣಿಕೆ) {
                SDL_memmove(&d->output_list[i], &d->output_list[i + 1], ಗಾತ್ರ(SDL_Display_ದತ್ತಾಂಶ *) * (d->output_ಎಣಿಕೆ - i - 1));
            }

            d->output_ಎಣಿಕೆ--;
            ಹೋಗು ack_remove;
        }
    }

    SDL_WaylandSeat *seat, *ತಾತ್ಕಾಲಿಕ;
    wl_list_for_each_ಸುರಕ್ಷಿತ (seat, ತಾತ್ಕಾಲಿಕ, &d->seat_list, link) {
        ಆದರೆ (seat->registry_id == id) {
            Wayland_SeatDestroy(seat, false);
            ಹೋಗು ack_remove;
        }
    }

ack_remove:
    ಆದರೆ (d->wl_fixes && wl_fixes_get_ಆವೃತ್ತಿ(d->wl_fixes) >= WL_FIXES_ACK_GLOBAL_REMOVE_SINCE_ಆವೃತ್ತಿ) {
        wl_fixes_ack_global_remove(d->wl_fixes, registry, id);
    }
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ wl_registry_listener registry_listener = {
    handle_registry_global,
    handle_registry_remove_global
};

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
ಸ್ಥಿರ bool should_use_libdecor(SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ, bool ignore_xdg)
{
    ಆದರೆ (!SDL_WAYLAND_HAVE_WAYLAND_LIBDECOR) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_PREFER_LIBDECOR, false)) {
        ಹಿಂತಿರುಗಿ true;
    }

    ಆದರೆ (ignore_xdg) {
        ಹಿಂತಿರುಗಿ true;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->decoration_manager) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ LibdecorNew(SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ)
{
    ದತ್ತಾಂಶ->shell.libdecor = libdecor_new(ದತ್ತಾಂಶ->display, &libdecor_interface);
}

// Called in another thread, but the UI thread is blocked in SDL_WaitThread
// during that time, so it should be OK to dereference data without locks
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ SDLCALL Libdecor_New_ಒಳ_Thread(ಶೂನ್ಯ *ದತ್ತಾಂಶ)
{
    LibdecorNew((SDL_Video_ದತ್ತಾಂಶ *)ದತ್ತಾಂಶ);
    ಹಿಂತಿರುಗಿ 0;
}
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_GETRESUID
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_getresuid getresuid
#ಇಲ್ಲದಿದ್ದರೆ
// Non-POSIX, but Linux and some BSDs have it.
// To reduce the number of code paths, if getresuid() isn't available at
// compile-time, we behave as though it existed but failed at runtime.
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ SDL_getresuid(uid_t *ruid, uid_t *euid, uid_t *suid) {
    errno = ENOSYS;
    ಹಿಂತಿರುಗಿ -1;
}
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_GETRESGID
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_getresgid getresgid
#ಇಲ್ಲದಿದ್ದರೆ
// Same as getresuid() but for the primary group
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ SDL_getresgid(gid_t *rgid, gid_t *egid, gid_t *sgid) {
    errno = ENOSYS;
    ಹಿಂತಿರುಗಿ -1;
}
#ಆದರೆ_ಅಂತ್ಯ

bool CanUseGtk(ಶೂನ್ಯ)
{
    // "Real", "effective" and "saved" IDs: see e.g. Linux credentials(7)
    uid_t ruid = -1, euid = -1, suid = -1;
    gid_t rgid = -1, egid = -1, sgid = -1;

    ಆದರೆ (!SDL_GetHintBoolean("SDL_ENABLE_GTK", true)) {
        SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "Not using GTK due to hint");
        ಹಿಂತಿರುಗಿ false;
    }

    // This is intended to match the check in gtkmain.c, rather than being
    // an exhaustive check for having elevated privileges: as a result
    // we don't use Linux getauxval() or prctl PR_GET_DUMPABLE,
    // BSD issetugid(), or similar OS-specific detection

    ಆದರೆ (SDL_getresuid(&ruid, &euid, &suid) != 0) {
        ruid = suid = getuid();
        euid = geteuid();
    }

    ಆದರೆ (SDL_getresgid(&rgid, &egid, &sgid) != 0) {
        rgid = sgid = getgid();
        egid = getegid();
    }

    // Real ID != effective ID means we are setuid or setgid:
    // GTK will refuse to initialize, and instead will call exit().
    ಆದರೆ (ruid != euid || rgid != egid) {
        SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "Not using GTK due to setuid/setgid");
        ಹಿಂತಿರುಗಿ false;
    }

    // Real ID != saved ID means we are setuid or setgid, we previously
    // dropped privileges, but we can regain them; this protects against
    // accidents but does not protect against arbitrary code execution.
    // Again, GTK will refuse to initialize if this is the case.
    ಆದರೆ (ruid != suid || rgid != sgid) {
        SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "Not using GTK due to saved uid/gid");
        ಹಿಂತಿರುಗಿ false;
    }

    ಹಿಂತಿರುಗಿ true;
}

bool Wayland_ತುಂಬು_Libdecor(SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ, bool ignore_xdg)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
    ಆದರೆ (ದತ್ತಾಂಶ->shell.libdecor != ಖಾಲಿ) {
        ಹಿಂತಿರುಗಿ true; // Already loaded!
    }
    ಆದರೆ (should_use_libdecor(ದತ್ತಾಂಶ, ignore_xdg)) {
        ಆದರೆ (CanUseGtk()) {
            LibdecorNew(ದತ್ತಾಂಶ);
        } ಇಲ್ಲದಿದ್ದರೆ {
            // Intentionally initialize libdecor in a non-main thread
            // so that it will not use its GTK plugin, but instead will
            // fall back to the Cairo or dummy plugin
            SDL_Thread *thread = SDL_CreateThread(Libdecor_New_ಒಳ_Thread, "SDL_LibdecorNew", (ಶೂನ್ಯ *)ದತ್ತಾಂಶ);
            // Note that the other thread now "owns" data until we have
            // waited for it, so don't touch data here
            SDL_WaitThread(thread, ಖಾಲಿ);
        }

        ಹಿಂತಿರುಗಿ ದತ್ತಾಂಶ->shell.libdecor != ಖಾಲಿ;
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ false;
}

bool Wayland_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;

    ದತ್ತಾಂಶ->event_thread_context = Wayland_CreateEventThread(ದತ್ತಾಂಶ, "SDL Event Thread Queue");
    ಆದರೆ (!ದತ್ತಾಂಶ->event_thread_context) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Failed to create event thread context");
    }

    ದತ್ತಾಂಶ->ಕೆಲಸ_thread_context = Wayland_Create_ಕೆಲಸ_Thread();
    ಆದರೆ (!ದತ್ತಾಂಶ->ಕೆಲಸ_thread_context) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Failed to create job thread context");
    }

    ದತ್ತಾಂಶ->xkb_context = WAYLAND_xkb_context_new(0);
    ಆದರೆ (!ದತ್ತಾಂಶ->xkb_context) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Failed to create XKB context");
    }

    ದತ್ತಾಂಶ->registry = wl_display_get_registry(ದತ್ತಾಂಶ->display);
    ಆದರೆ (!ದತ್ತಾಂಶ->registry) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Failed to get the Wayland registry");
    }

    wl_registry_ಕೂಡಿಸು_listener(ದತ್ತಾಂಶ->registry, &registry_listener, ದತ್ತಾಂಶ);

    // First roundtrip to receive all registry objects.
    WAYLAND_wl_display_roundtrip(ದತ್ತಾಂಶ->display);

    // Require viewports and xdg-output for display scaling.
    ಆದರೆ (ದತ್ತಾಂಶ->scale_ಗಮ್ಯ_display_enabled) {
        ಆದರೆ (!ದತ್ತಾಂಶ->viewporter) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Display scaling requires the missing 'wp_viewporter' protocol: disabling");
            ದತ್ತಾಂಶ->scale_ಗಮ್ಯ_display_enabled = false;
        }
        ಆದರೆ (!ದತ್ತಾಂಶ->xdg_output_manager) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Display scaling requires the missing 'zxdg_output_manager_v1' protocol: disabling");
            ದತ್ತಾಂಶ->scale_ಗಮ್ಯ_display_enabled = false;
        }
    }

    // Now that we have all the protocols, load libdecor if applicable
    Wayland_ತುಂಬು_Libdecor(ದತ್ತಾಂಶ, false);

    // Second roundtrip to receive all output events.
    WAYLAND_wl_display_roundtrip(ದತ್ತಾಂಶ->display);

    Wayland_FinalizeDisplays(ದತ್ತಾಂಶ);

    Wayland_InitMouse(ದತ್ತಾಂಶ);
    Wayland_InitKeyboard(_this);

    ಆದರೆ (ದತ್ತಾಂಶ->primary_selection_device_manager) {
        _this->ಗಣ_Primary_Selection_ಪಠ್ಯ = Wayland_ಗಣ_Primary_Selection_ಪಠ್ಯ;
        _this->Get_Primary_Selection_ಪಠ್ಯ = Wayland_Get_Primary_Selection_ಪಠ್ಯ;
        _this->Has_Primary_Selection_ಪಠ್ಯ = Wayland_Has_Primary_Selection_ಪಠ್ಯ;
    }

    ದತ್ತಾಂಶ->initializing = false;

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool Wayland_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    SDL_Video_ದತ್ತಾಂಶ *viddata = _this->ಆಂತರಿಕ;
    SDL_Display_ದತ್ತಾಂಶ *ಆಂತರಿಕ = display->ಆಂತರಿಕ;

    ಆದರೆ (!viddata->scale_ಗಮ್ಯ_display_enabled) {
        rect->x = ಆಂತರಿಕ->logical.x;
        rect->y = ಆಂತರಿಕ->logical.y;
    } ಇಲ್ಲದಿದ್ದರೆ {
        rect->x = ಆಂತರಿಕ->pixel.x;
        rect->y = ಆಂತರಿಕ->pixel.y;
    }

    // When an emulated, exclusive fullscreen window has focus, treat the mode dimensions as the display bounds.
    ಆದರೆ (display->fullscreen_ಕಿಟಕಿ &&
        display->fullscreen_ಕಿಟಕಿ->fullscreen_exclusive &&
        display->fullscreen_ಕಿಟಕಿ->ಆಂತರಿಕ->ಸಕ್ರಿಯ &&
        display->fullscreen_ಕಿಟಕಿ->current_fullscreen_ಬಹುಲಕ.w != 0 &&
        display->fullscreen_ಕಿಟಕಿ->current_fullscreen_ಬಹುಲಕ.h != 0) {
        rect->w = display->fullscreen_ಕಿಟಕಿ->current_fullscreen_ಬಹುಲಕ.w;
        rect->h = display->fullscreen_ಕಿಟಕಿ->current_fullscreen_ಬಹುಲಕ.h;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (!viddata->scale_ಗಮ್ಯ_display_enabled) {
            rect->w = display->current_ಬಹುಲಕ->w;
            rect->h = display->current_ಬಹುಲಕ->h;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಆಂತರಿಕ->transform & WL_OUTPUT_TRANSFORM_90) {
            rect->w = ಆಂತರಿಕ->pixel.ಎತ್ತರ;
            rect->h = ಆಂತರಿಕ->pixel.ಅಗಲ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            rect->w = ಆಂತರಿಕ->pixel.ಅಗಲ;
            rect->h = ಆಂತರಿಕ->pixel.ಎತ್ತರ;
        }
    }
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_VideoCleanup(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    SDL_WaylandSeat *seat, *tmp;

    Wayland_SessionDestroy(ದತ್ತಾಂಶ);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = _this->ಅಂಕೆ_displays - 1; i >= 0; --i) {
        SDL_VideoDisplay *display = _this->displays[i];
        Wayland_free_display(display, false);
    }
    SDL_free(ದತ್ತಾಂಶ->output_list);

    wl_list_for_each_ಸುರಕ್ಷಿತ (seat, tmp, &ದತ್ತಾಂಶ->seat_list, link) {
        Wayland_SeatDestroy(seat, true);
    }

    Wayland_FiniMouse(ದತ್ತಾಂಶ);
    Wayland_QuitKeyboard(_this);

    Wayland_DestroyEventThread(ದತ್ತಾಂಶ->event_thread_context);
    ದತ್ತಾಂಶ->event_thread_context = ಖಾಲಿ;

    Wayland_Destroy_ಕೆಲಸ_Thread(ದತ್ತಾಂಶ->ಕೆಲಸ_thread_context);
    ದತ್ತಾಂಶ->ಕೆಲಸ_thread_context = ಖಾಲಿ;

    ಆದರೆ (ದತ್ತಾಂಶ->ಸೂಚಕ_constraints) {
        zwp_ಸೂಚಕ_constraints_v1_destroy(ದತ್ತಾಂಶ->ಸೂಚಕ_constraints);
        ದತ್ತಾಂಶ->ಸೂಚಕ_constraints = ಖಾಲಿ;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->relative_ಸೂಚಕ_manager) {
        zwp_relative_ಸೂಚಕ_manager_v1_destroy(ದತ್ತಾಂಶ->relative_ಸೂಚಕ_manager);
        ದತ್ತಾಂಶ->relative_ಸೂಚಕ_manager = ಖಾಲಿ;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->activation_manager) {
        xdg_activation_v1_destroy(ದತ್ತಾಂಶ->activation_manager);
        ದತ್ತಾಂಶ->activation_manager = ಖಾಲಿ;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->idle_inhibit_manager) {
        zwp_idle_inhibit_manager_v1_destroy(ದತ್ತಾಂಶ->idle_inhibit_manager);
        ದತ್ತಾಂಶ->idle_inhibit_manager = ಖಾಲಿ;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->ಕೀಲಿ_inhibitor_manager) {
        zwp_keyboard_shortcuts_inhibit_manager_v1_destroy(ದತ್ತಾಂಶ->ಕೀಲಿ_inhibitor_manager);
        ದತ್ತಾಂಶ->ಕೀಲಿ_inhibitor_manager = ಖಾಲಿ;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->ಪಠ್ಯ_ಒಳಹರಿವು_manager) {
        zwp_ಪಠ್ಯ_ಒಳಹರಿವು_manager_v3_destroy(ದತ್ತಾಂಶ->ಪಠ್ಯ_ಒಳಹರಿವು_manager);
        ದತ್ತಾಂಶ->ಪಠ್ಯ_ಒಳಹರಿವು_manager = ಖಾಲಿ;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->xkb_context) {
        WAYLAND_xkb_context_unref(ದತ್ತಾಂಶ->xkb_context);
        ದತ್ತಾಂಶ->xkb_context = ಖಾಲಿ;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->tablet_manager) {
        zwp_tablet_manager_v2_destroy((ರಚನೆ zwp_tablet_manager_v2 *)ದತ್ತಾಂಶ->tablet_manager);
        ದತ್ತಾಂಶ->tablet_manager = ಖಾಲಿ;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->ದತ್ತಾಂಶ_device_manager) {
        wl_ದತ್ತಾಂಶ_device_manager_destroy(ದತ್ತಾಂಶ->ದತ್ತಾಂಶ_device_manager);
        ದತ್ತಾಂಶ->ದತ್ತಾಂಶ_device_manager = ಖಾಲಿ;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->shm) {
        ಆದರೆ (wl_shm_get_ಆವೃತ್ತಿ(ದತ್ತಾಂಶ->shm) >= WL_SHM_RELEASE_SINCE_ಆವೃತ್ತಿ) {
            wl_shm_release(ದತ್ತಾಂಶ->shm);
        } ಇಲ್ಲದಿದ್ದರೆ {
            wl_shm_destroy(ದತ್ತಾಂಶ->shm);
        }
        ದತ್ತಾಂಶ->shm = ಖಾಲಿ;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->shell.xdg) {
        xdg_wm_ತಳ_destroy(ದತ್ತಾಂಶ->shell.xdg);
        ದತ್ತಾಂಶ->shell.xdg = ಖಾಲಿ;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->decoration_manager) {
        zxdg_decoration_manager_v1_destroy(ದತ್ತಾಂಶ->decoration_manager);
        ದತ್ತಾಂಶ->decoration_manager = ಖಾಲಿ;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->xdg_output_manager) {
        zxdg_output_manager_v1_destroy(ದತ್ತಾಂಶ->xdg_output_manager);
        ದತ್ತಾಂಶ->xdg_output_manager = ಖಾಲಿ;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->viewporter) {
        wp_viewporter_destroy(ದತ್ತಾಂಶ->viewporter);
        ದತ್ತಾಂಶ->viewporter = ಖಾಲಿ;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->primary_selection_device_manager) {
        zwp_primary_selection_device_manager_v1_destroy(ದತ್ತಾಂಶ->primary_selection_device_manager);
        ದತ್ತಾಂಶ->primary_selection_device_manager = ಖಾಲಿ;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->fractional_scale_manager) {
        wp_fractional_scale_manager_v1_destroy(ದತ್ತಾಂಶ->fractional_scale_manager);
        ದತ್ತಾಂಶ->fractional_scale_manager = ಖಾಲಿ;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->ಒಳಹರಿವು_timestamps_manager) {
        zwp_ಒಳಹರಿವು_timestamps_manager_v1_destroy(ದತ್ತಾಂಶ->ಒಳಹರಿವು_timestamps_manager);
        ದತ್ತಾಂಶ->ಒಳಹರಿವು_timestamps_manager = ಖಾಲಿ;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->cursor_shape_manager) {
        wp_cursor_shape_manager_v1_destroy(ದತ್ತಾಂಶ->cursor_shape_manager);
        ದತ್ತಾಂಶ->cursor_shape_manager = ಖಾಲಿ;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->zxdg_exporter_v2) {
        zxdg_exporter_v2_destroy(ದತ್ತಾಂಶ->zxdg_exporter_v2);
        ದತ್ತಾಂಶ->zxdg_exporter_v2 = ಖಾಲಿ;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->xdg_wm_dialog_v1) {
        xdg_wm_dialog_v1_destroy(ದತ್ತಾಂಶ->xdg_wm_dialog_v1);
        ದತ್ತಾಂಶ->xdg_wm_dialog_v1 = ಖಾಲಿ;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->wp_alpha_modifier_v1) {
        wp_alpha_modifier_v1_destroy(ದತ್ತಾಂಶ->wp_alpha_modifier_v1);
        ದತ್ತಾಂಶ->wp_alpha_modifier_v1 = ಖಾಲಿ;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->xdg_toplevel_icon_manager_v1) {
        xdg_toplevel_icon_manager_v1_destroy(ದತ್ತಾಂಶ->xdg_toplevel_icon_manager_v1);
        ದತ್ತಾಂಶ->xdg_toplevel_icon_manager_v1 = ಖಾಲಿ;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->frog_color_management_factory_v1) {
        frog_color_management_factory_v1_destroy(ದತ್ತಾಂಶ->frog_color_management_factory_v1);
        ದತ್ತಾಂಶ->frog_color_management_factory_v1 = ಖಾಲಿ;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->wp_color_manager_v1) {
        wp_color_manager_v1_destroy(ದತ್ತಾಂಶ->wp_color_manager_v1);
        ದತ್ತಾಂಶ->wp_color_manager_v1 = ಖಾಲಿ;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->wp_ಸೂಚಕ_warp_v1) {
        wp_ಸೂಚಕ_warp_v1_destroy(ದತ್ತಾಂಶ->wp_ಸೂಚಕ_warp_v1);
        ದತ್ತಾಂಶ->wp_ಸೂಚಕ_warp_v1 = ಖಾಲಿ;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->zwp_ಸೂಚಕ_gestures) {
        ಆದರೆ (zwp_ಸೂಚಕ_gestures_v1_get_ಆವೃತ್ತಿ(ದತ್ತಾಂಶ->zwp_ಸೂಚಕ_gestures) >= ZWP_ಸೂಚಕ_GESTURES_V1_RELEASE_SINCE_ಆವೃತ್ತಿ) {
            zwp_ಸೂಚಕ_gestures_v1_release(ದತ್ತಾಂಶ->zwp_ಸೂಚಕ_gestures);
        } ಇಲ್ಲದಿದ್ದರೆ {
            zwp_ಸೂಚಕ_gestures_v1_destroy(ದತ್ತಾಂಶ->zwp_ಸೂಚಕ_gestures);
        }
        ದತ್ತಾಂಶ->zwp_ಸೂಚಕ_gestures = ಖಾಲಿ;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->single_pixel_ಬಫರ್_manager) {
        wp_single_pixel_ಬಫರ್_manager_v1_destroy(ದತ್ತಾಂಶ->single_pixel_ಬಫರ್_manager);
        ದತ್ತಾಂಶ->single_pixel_ಬಫರ್_manager = ಖಾಲಿ;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->xdg_session_manager) {
        xdg_session_manager_v1_destroy(ದತ್ತಾಂಶ->xdg_session_manager);
        ದತ್ತಾಂಶ->xdg_session_manager = ಖಾಲಿ;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->xdg_toplevel_ಟ್ಯಾಗ್_manager) {
        xdg_toplevel_ಟ್ಯಾಗ್_manager_v1_destroy(ದತ್ತಾಂಶ->xdg_toplevel_ಟ್ಯಾಗ್_manager);
        ದತ್ತಾಂಶ->xdg_toplevel_ಟ್ಯಾಗ್_manager = ಖಾಲಿ;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->subcompositor) {
        wl_subcompositor_destroy(ದತ್ತಾಂಶ->subcompositor);
        ದತ್ತಾಂಶ->subcompositor = ಖಾಲಿ;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->compositor) {
        wl_compositor_destroy(ದತ್ತಾಂಶ->compositor);
        ದತ್ತಾಂಶ->compositor = ಖಾಲಿ;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->registry) {
        ಆದರೆ (ದತ್ತಾಂಶ->wl_fixes) {
            wl_fixes_destroy_registry(ದತ್ತಾಂಶ->wl_fixes, ದತ್ತಾಂಶ->registry);
            wl_fixes_destroy(ದತ್ತಾಂಶ->wl_fixes);
            ದತ್ತಾಂಶ->wl_fixes = ಖಾಲಿ;
        }
        wl_registry_destroy(ದತ್ತಾಂಶ->registry);
        ದತ್ತಾಂಶ->registry = ಖಾಲಿ;
    }
}

ಸ್ಥಿರ bool Wayland_VideoReconnect(SDL_VideoDevice *_this)
{
#ಆದರೆ 0 // TODO RECONNECT: Uncomment all when https://invent.kde.org/plasma/kwin/-/wikis/Restarting is completed
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;

    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = ಖಾಲಿ;

    SDL_GLContext current_ctx = SDL_GL_GetCurrentContext();
    SDL_ಕಿಟಕಿ *current_ಕಿಟಕಿ = SDL_GL_Get_Current_ಕಿಟಕಿ();

    SDL_GL_MakeCurrent(ಖಾಲಿ, ಖಾಲಿ);
    Wayland_VideoCleanup(_this);

    SDL_ResetKeyboard();
    SDL_ResetMouse();
    ಆದರೆ (WAYLAND_wl_display_reconnect(ದತ್ತಾಂಶ->display) < 0) {
        ಹಿಂತಿರುಗಿ false;
    }

    Wayland_VideoInit(_this);

    ಕಿಟಕಿ = _this->windows;
    ಆಗ (ಕಿಟಕಿ) {
        /* We're going to cheat _just_ for a second and strip the OpenGL flag.
         * The Wayland driver actually forces it in CreateWindow, and
         * RecreateWindow does a bunch of unloading/loading of libGL, so just
         * strip the flag so RecreateWindow doesn't mess with the GL context,
         * and CreateWindow will add it right back!
         * -flibit
         */
        ಕಿಟಕಿ->flags &= ~SDL_ಕಿಟಕಿ_OPENGL;

        SDL_Recreate_ಕಿಟಕಿ(ಕಿಟಕಿ, ಕಿಟಕಿ->flags);
        ಕಿಟಕಿ = ಕಿಟಕಿ->ಮುಂದಿನ;
    }

    Wayland_RecreateCursors();

    ಆದರೆ (current_ಕಿಟಕಿ && current_ctx) {
        SDL_GL_MakeCurrent (current_ಕಿಟಕಿ, current_ctx);
    }
    ಹಿಂತಿರುಗಿ true;
#ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ false;
#ಆದರೆ_ಅಂತ್ಯ // 0
}

bool Wayland_HandleDisplayDisconnected(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *video_ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;

    /* Something has failed with the Wayland connection -- for example,
     * the compositor may have shut down and closed its end of the socket,
     * or there is a library-specific error.
     *
     * Try to recover once, then quit.
     */
    ಆದರೆ (video_ದತ್ತಾಂಶ->display_disconnected) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (Wayland_VideoReconnect(_this)) {
        ಹಿಂತಿರುಗಿ true;
    }

    video_ದತ್ತಾಂಶ->display_disconnected = true;
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Wayland display connection closed by server (fatal)");

    // Only send a single quit message, as application shutdown might call SDL_PumpEvents().
    SDL_SendQuit();

    ಹಿಂತಿರುಗಿ false;
}

ಶೂನ್ಯ Wayland_VideoQuit(SDL_VideoDevice *_this)
{
    Wayland_VideoCleanup(_this);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    ಆದರೆ (ದತ್ತಾಂಶ->shell.libdecor) {
        libdecor_unref(ದತ್ತಾಂಶ->shell.libdecor);
        ದತ್ತಾಂಶ->shell.libdecor = ಖಾಲಿ;
    }
#ಆದರೆ_ಅಂತ್ಯ
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_WAYLAND
