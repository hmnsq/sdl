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

#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/linux/SDL_system_theme.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/linux/SDL_progressbar.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_events_c.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandclipboard.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandcolor.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandevents_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandkeyboard.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandmessagebox.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandmouse.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandopengles.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandvulkan.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandwindow.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <fcntl.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/types.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <unistd.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <errno.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <xkbcommon/xkbcommon.h>

#ਅਨ੍ਤਰ੍ਭਾਵ <wayland-util.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "alpha-modifier-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "cursor-shape-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "fractional-scale-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "frog-color-management-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "idle-inhibit-unstable-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "input-timestamps-unstable-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "keyboard-shortcuts-inhibit-unstable-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pointer-constraints-unstable-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "primary-selection-unstable-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "relative-pointer-unstable-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "tablet-v2-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "text-input-unstable-v3-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "viewporter-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "xdg-activation-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "xdg-decoration-unstable-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "xdg-dialog-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "xdg-foreign-unstable-v2-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "xdg-output-unstable-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "xdg-shell-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "xdg-toplevel-icon-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "color-management-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pointer-warp-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pointer-gestures-unstable-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "single-pixel-buffer-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "xdg-session-management-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "xdg-toplevel-tag-v1-client-protocol.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
#ਅਨ੍ਤਰ੍ਭਾਵ <libdecor.h>
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WAYLANDVID_DRIVER_NAME "wayland"

// Clamp core protocol versions on older versions of libwayland.
#ਜੇ SDL_WAYLAND_CHECK_ਸੰਸਕਰਣ(1, 22, 0)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_WL_COMPOSITOR_ਸੰਸਕਰਣ 6
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_WL_COMPOSITOR_ਸੰਸਕਰਣ 4
#ਜੇ_ਅੰਤ

#ਜੇ SDL_WAYLAND_CHECK_ਸੰਸਕਰਣ(1, 26, 0)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_WL_SEAT_ਸੰਸਕਰਣ 11
#ਜਾਂਜੇ SDL_WAYLAND_CHECK_ਸੰਸਕਰਣ(1, 24, 0)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_WL_SEAT_ਸੰਸਕਰਣ 10
#ਜਾਂਜੇ SDL_WAYLAND_CHECK_ਸੰਸਕਰਣ(1, 22, 0)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_WL_SEAT_ਸੰਸਕਰਣ 9
#ਜਾਂਜੇ SDL_WAYLAND_CHECK_ਸੰਸਕਰਣ(1, 21, 0)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_WL_SEAT_ਸੰਸਕਰਣ 8
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_WL_SEAT_ਸੰਸਕਰਣ 5
#ਜੇ_ਅੰਤ

#ਜੇ SDL_WAYLAND_CHECK_ਸੰਸਕਰਣ(1, 20, 0)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_WL_OUTPUT_ਸੰਸਕਰਣ 4
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_WL_OUTPUT_ਸੰਸਕਰਣ 3
#ਜੇ_ਅੰਤ

#ਜੇ SDL_WAYLAND_CHECK_ਸੰਸਕਰਣ(1, 24, 0)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_WL_SHM_ਸੰਸਕਰਣ 2
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_WL_SHM_ਸੰਸਕਰਣ 1
#ਜੇ_ਅੰਤ

// The SDL libwayland-client minimum is 1.18, which supports version 3.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_WL_ਅੰਕੜੇ_DEVICE_ਸੰਸਕਰਣ 3

// wl_fixes was introduced in 1.24.0
#ਜੇ SDL_WAYLAND_CHECK_ਸੰਸਕਰਣ(1, 26, 0)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_WL_FIXES_ਸੰਸਕਰਣ 2
#ਜਾਂਜੇ SDL_WAYLAND_CHECK_ਸੰਸਕਰਣ(1, 24, 0)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_WL_FIXES_ਸੰਸਕਰਣ 1
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_USE_LIBDBUS
#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/linux/SDL_dbus.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DISPLAY_INFO_ਗੰਢ   "org.gnome.Mutter.DisplayConfig"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DISPLAY_INFO_ਰਸਤਾ   "/org/gnome/Mutter/DisplayConfig"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DISPLAY_INFO_ਵਿਧੀ "GetCurrentState"
#ਜੇ_ਅੰਤ

/* GNOME doesn't expose displays in any particular order, but we can find the
 * primary display and its logical coordinates via a DBus method.
 */
ਸਥਿਰ bool Wayland_GetGNOMEPrimaryDisplayCoordinates(ਪੂਰਨ *x, ਪੂਰਨ *y)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_USE_LIBDBUS
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    ਜੇ (dbus == ਨਿਰਾ) {
        ਵਾਪਸ false;
    }
    DBus_ਸੁਨੇਹਾ *ਜਵਾਬ = ਨਿਰਾ;
    DBus_ਸੁਨੇਹਾ_Iter iter[3];
    DBus_ਸੁਨੇਹਾ *ਸੁਨੇਹਾ_2 = dbus->ਸੁਨੇਹਾ_new_ਵਿਧੀ_call(DISPLAY_INFO_ਗੰਢ,
                                                     DISPLAY_INFO_ਰਸਤਾ,
                                                     DISPLAY_INFO_ਗੰਢ,
                                                     DISPLAY_INFO_ਵਿਧੀ);

    ਜੇ (ਸੁਨੇਹਾ_2) {
        ਜਵਾਬ = dbus->connection_send_with_ਜਵਾਬ_and_ਖੰਡ(dbus->session_conn, ਸੁਨੇਹਾ_2, DBUS_TIMEOUT_USE_DEFAULT, ਨਿਰਾ);
        dbus->ਸੁਨੇਹਾ_unref(ਸੁਨੇਹਾ_2);
    }

    ਜੇ (ਜਵਾਬ) {
        // Serial (don't care)
        dbus->ਸੁਨੇਹਾ_iter_init(ਜਵਾਬ, &iter[0]);
        ਜੇ (dbus->ਸੁਨੇਹਾ_iter_get_arg_type(&iter[0]) != DBUS_TYPE_UINT32) {
            ਜਾਓ error;
        }

        // Physical monitor array (don't care)
        dbus->ਸੁਨੇਹਾ_iter_ਅਗਲਾ(&iter[0]);
        ਜੇ (dbus->ਸੁਨੇਹਾ_iter_get_arg_type(&iter[0]) != DBUS_TYPE_ARRAY) {
            ਜਾਓ error;
        }

        // Logical monitor array of structs
        dbus->ਸੁਨੇਹਾ_iter_ਅਗਲਾ(&iter[0]);
        ਜੇ (dbus->ਸੁਨੇਹਾ_iter_get_arg_type(&iter[0]) != DBUS_TYPE_ARRAY) {
            ਜਾਓ error;
        }

        // First logical monitor struct
        dbus->ਸੁਨੇਹਾ_iter_recurse(&iter[0], &iter[1]);
        ਜੇ (dbus->ਸੁਨੇਹਾ_iter_get_arg_type(&iter[1]) != DBUS_TYPE_STRUCT) {
            ਜਾਓ error;
        }

        ਕਰੋ {
            ਪੂਰਨ logical_x, logical_y;
            dbus_bool_t primary;

            // Logical X
            dbus->ਸੁਨੇਹਾ_iter_recurse(&iter[1], &iter[2]);
            ਜੇ (dbus->ਸੁਨੇਹਾ_iter_get_arg_type(&iter[2]) != DBUS_TYPE_INT32) {
                ਜਾਓ error;
            }
            dbus->ਸੁਨੇਹਾ_iter_get_basic(&iter[2], &logical_x);

            // Logical Y
            dbus->ਸੁਨੇਹਾ_iter_ਅਗਲਾ(&iter[2]);
            ਜੇ (dbus->ਸੁਨੇਹਾ_iter_get_arg_type(&iter[2]) != DBUS_TYPE_INT32) {
                ਜਾਓ error;
            }
            dbus->ਸੁਨੇਹਾ_iter_get_basic(&iter[2], &logical_y);

            // Scale (don't care)
            dbus->ਸੁਨੇਹਾ_iter_ਅਗਲਾ(&iter[2]);
            ਜੇ (dbus->ਸੁਨੇਹਾ_iter_get_arg_type(&iter[2]) != DBUS_TYPE_DOUBLE) {
                ਜਾਓ error;
            }

            // Transform (don't care)
            dbus->ਸੁਨੇਹਾ_iter_ਅਗਲਾ(&iter[2]);
            ਜੇ (dbus->ਸੁਨੇਹਾ_iter_get_arg_type(&iter[2]) != DBUS_TYPE_UINT32) {
                ਜਾਓ error;
            }

            // Primary display boolean
            dbus->ਸੁਨੇਹਾ_iter_ਅਗਲਾ(&iter[2]);
            ਜੇ (dbus->ਸੁਨੇਹਾ_iter_get_arg_type(&iter[2]) != DBUS_TYPE_BOOLEAN) {
                ਜਾਓ error;
            }
            dbus->ਸੁਨੇਹਾ_iter_get_basic(&iter[2], &primary);

            ਜੇ (primary) {
                *x = logical_x;
                *y = logical_y;

                // We found the primary display: success.
                dbus->ਸੁਨੇਹਾ_unref(ਜਵਾਬ);
                ਵਾਪਸ true;
            }
        } ਜਦੋਂ (dbus->ਸੁਨੇਹਾ_iter_ਅਗਲਾ(&iter[1]));
    }

error:
    ਜੇ (ਜਵਾਬ) {
        dbus->ਸੁਨੇਹਾ_unref(ਜਵਾਬ);
    }
#ਜੇ_ਅੰਤ
    ਵਾਪਸ false;
}

// Sort the list of displays into a deterministic order
ਸਥਿਰ ਪੂਰਨ SDLCALL Wayland_DisplayPositionCompare(ਅਚਲ ਖਾਲੀ *a, ਅਚਲ ਖਾਲੀ *b)
{
    ਅਚਲ SDL_Display_ਅੰਕੜੇ *da = *(SDL_Display_ਅੰਕੜੇ **)a;
    ਅਚਲ SDL_Display_ਅੰਕੜੇ *db = *(SDL_Display_ਅੰਕੜੇ **)b;
    ਅਚਲ bool a_at_origin = da->logical.x == 0 && da->logical.y == 0;
    ਅਚਲ bool b_at_origin = db->logical.x == 0 && db->logical.y == 0;

    // Sort the display at 0,0 to be beginning of the list, as that will be the fallback primary.
    ਜੇ (a_at_origin && !b_at_origin) {
        ਵਾਪਸ -1;
    }
    ਜੇ (b_at_origin && !a_at_origin) {
        ਵਾਪਸ 1;
    }

    ਜੇ (da->logical.x < db->logical.x) {
        ਵਾਪਸ -1;
    }
    ਜੇ (da->logical.x > db->logical.x) {
        ਵਾਪਸ 1;
    }
    ਜੇ (da->logical.y < db->logical.y) {
        ਵਾਪਸ -1;
    }
    ਜੇ (da->logical.y > db->logical.y) {
        ਵਾਪਸ 1;
    }

    // If no position information is available, use the connector name.
    ਜੇ (da->wl_output_name && db->wl_output_name) {
        ਵਾਪਸ SDL_strcmp(da->wl_output_name, db->wl_output_name);
    }

    ਵਾਪਸ 0;
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
ਸਥਿਰ ਪੂਰਨ Wayland_GetPrimaryDisplay(SDL_Video_ਅੰਕੜੇ *vid)
{
    ਸਥਿਰ ਅਚਲ ਪੂਰਨ REFRESH_DELTA = 4000;

    // Query the DBus interface to see if the coordinates of the primary display are exposed.
    ਪੂਰਨ x, y;
    ਜੇ (Wayland_GetGNOMEPrimaryDisplayCoordinates(&x, &y)) {
        ਲਈ (ਪੂਰਨ i = 0; i < vid->output_ਗਿਣਤੀ; ++i) {
            ਜੇ (vid->output_list[i]->logical.x == x && vid->output_list[i]->logical.y == y) {
                ਵਾਪਸ i;
            }
        }
    }

    // Otherwise, choose the 'best' display.
    ਪੂਰਨ ਉੱਤਮ_ਚੌੜਾਈ = 0;
    ਪੂਰਨ ਉੱਤਮ_ਉਚਾਈ = 0;
    ਦੁੱਗਣਾ ਉੱਤਮ_scale = 0.0;
    ਦਸ਼ਮਲਵ ਉੱਤਮ_headroom = 0.0f;
    ਪੂਰਨ ਉੱਤਮ_refresh = 0;
    bool ਉੱਤਮ_is_landscape = false;
    ਪੂਰਨ ਉੱਤਮ_ਸੂਚਕਾਂਕ = 0;

    ਲਈ (ਪੂਰਨ i = 0; i < vid->output_ਗਿਣਤੀ; ++i) {
        ਅਚਲ SDL_Display_ਅੰਕੜੇ *d = vid->output_list[i];
        ਅਚਲ bool is_landscape = d->orientation != SDL_ORIENTATION_PORTRAIT && d->orientation != SDL_ORIENTATION_PORTRAIT_FLIPPED;
        bool have_new_ਉੱਤਮ = false;

        ਜੇ (!ਉੱਤਮ_is_landscape && is_landscape) { // Favor landscape over portrait displays.
            have_new_ਉੱਤਮ = true;
        } ਨਹੀਂਤਾਂ ਜੇ (!ਉੱਤਮ_is_landscape || is_landscape) { // Ignore portrait displays if a landscape was already found.
            ਜੇ (d->pixel.ਚੌੜਾਈ > ਉੱਤਮ_ਚੌੜਾਈ || d->pixel.ਉਚਾਈ > ਉੱਤਮ_ਉਚਾਈ) {
                have_new_ਉੱਤਮ = true;
            } ਨਹੀਂਤਾਂ ਜੇ (d->pixel.ਚੌੜਾਈ == ਉੱਤਮ_ਚੌੜਾਈ && d->pixel.ਉਚਾਈ == ਉੱਤਮ_ਉਚਾਈ) {
                ਜੇ (d->HDR.HDR_headroom > ਉੱਤਮ_headroom) { // Favor a higher HDR luminance range
                    have_new_ਉੱਤਮ = true;
                } ਨਹੀਂਤਾਂ ਜੇ (d->HDR.HDR_headroom == ਉੱਤਮ_headroom) {
                    ਜੇ (d->refresh - ਉੱਤਮ_refresh > REFRESH_DELTA) { // Favor a higher refresh rate, but ignore small differences (e.g. 59.97 vs 60.1)
                        have_new_ਉੱਤਮ = true;
                    } ਨਹੀਂਤਾਂ ਜੇ (d->scale_ਗੁਣਕ_2 < ਉੱਤਮ_scale && SDL_abs(d->refresh - ਉੱਤਮ_refresh) <= REFRESH_DELTA) {
                        // Prefer a lower scale display if the difference in refresh rate is small.
                        have_new_ਉੱਤਮ = true;
                    }
                }
            }
        }

        ਜੇ (have_new_ਉੱਤਮ) {
            ਉੱਤਮ_ਚੌੜਾਈ = d->pixel.ਚੌੜਾਈ;
            ਉੱਤਮ_ਉਚਾਈ = d->pixel.ਉਚਾਈ;
            ਉੱਤਮ_scale = d->scale_ਗੁਣਕ_2;
            ਉੱਤਮ_headroom = d->HDR.HDR_headroom;
            ਉੱਤਮ_refresh = d->refresh;
            ਉੱਤਮ_is_landscape = is_landscape;
            ਉੱਤਮ_ਸੂਚਕਾਂਕ = i;
        }
    }

    ਵਾਪਸ ਉੱਤਮ_ਸੂਚਕਾਂਕ;
}

ਸਥਿਰ ਖਾਲੀ Wayland_ਛਾਂਟੋ_Outputs_By_ਤਰਜੀਹ_Hint(SDL_Video_ਅੰਕੜੇ *vid)
{
    ਅਚਲ ਅੱਖਰ *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_ਤਰਜੀਹ);

    ਜੇ (name_hint) {
        ਅੱਖਰ *saveptr;
        ਅੱਖਰ *str = SDL_strdup(name_hint);
        SDL_Display_ਅੰਕੜੇ **sorted_list = SDL_malloc(ਆਕਾਰ(SDL_Display_ਅੰਕੜੇ *) * vid->output_ਗਿਣਤੀ);

        ਜੇ (str && sorted_list) {
            ਪੂਰਨ sorted_ਸੂਚਕਾਂਕ = 0;

            // Sort the requested displays to the front of the list.
            ਅਚਲ ਅੱਖਰ *token = SDL_strtok_r(str, ",", &saveptr);
            ਜਦੋਂ (token) {
                ਲਈ (ਪੂਰਨ i = 0; i < vid->output_ਗਿਣਤੀ; ++i) {
                    SDL_Display_ਅੰਕੜੇ *d = vid->output_list[i];
                    ਜੇ (d && d->wl_output_name && SDL_strcmp(token, d->wl_output_name) == 0) {
                        sorted_list[sorted_ਸੂਚਕਾਂਕ++] = d;
                        vid->output_list[i] = ਨਿਰਾ;
                        ਰੋਕੋ;
                    }
                }

                token = SDL_strtok_r(ਨਿਰਾ, ",", &saveptr);
            }

            // Append the remaining outputs to the end of the list.
            ਲਈ (ਪੂਰਨ i = 0; i < vid->output_ਗਿਣਤੀ; ++i) {
                ਜੇ (vid->output_list[i]) {
                    sorted_list[sorted_ਸੂਚਕਾਂਕ++] = vid->output_list[i];
                }
            }

            // Copy the sorted list to the output list.
            SDL_memcpy(vid->output_list, sorted_list, ਆਕਾਰ(SDL_Display_ਅੰਕੜੇ *) * vid->output_ਗਿਣਤੀ);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

ਸਥਿਰ ਖਾਲੀ Wayland_DeriveOutputPixelCoordinates(SDL_Video_ਅੰਕੜੇ *vid)
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
    ਲਈ ( ਪੂਰਨ i = 0; i < vid->output_ਗਿਣਤੀ; ++i) {
        SDL_Display_ਅੰਕੜੇ *d = vid->output_list[i];
        d->pixel.x = d->logical.x;
        d->pixel.y = d->logical.y;
    }

    ਲਈ (ਪੂਰਨ i = 0; i < vid->output_ਗਿਣਤੀ; ++i) {
        SDL_Display_ਅੰਕੜੇ *d1 = vid->output_list[i];
        ਜੇ (d1->logical.ਚੌੜਾਈ != d1->pixel.ਚੌੜਾਈ || d1->logical.ਉਚਾਈ != d1->pixel.ਉਚਾਈ) {
            ਅਚਲ ਪੂਰਨ x_adj = d1->pixel.ਚੌੜਾਈ - d1->logical.ਚੌੜਾਈ;
            ਅਚਲ ਪੂਰਨ y_adj = d1->pixel.ਉਚਾਈ - d1->logical.ਉਚਾਈ;

            // Don't adjust for scale values less than 1.0.
            ਜੇ (x_adj > 0 && y_adj > 0) {
                ਲਈ (ਪੂਰਨ j = 0; j < vid->output_ਗਿਣਤੀ; ++j) {
                    SDL_Display_ਅੰਕੜੇ *d2 = vid->output_list[j];
                    ਜੇ (d2->logical.x > d1->logical.x) {
                        d2->pixel.x += x_adj;
                    }
                    ਜੇ (d2->logical.y > d1->logical.y) {
                        d2->pixel.y += y_adj;
                    }
                }
            }
        }
    }
}

ਸਥਿਰ ਖਾਲੀ Wayland_ਛਾਂਟੋ_Outputs(SDL_Video_ਅੰਕੜੇ *vid)
{
    // Sort by position or connector name, so the order of outputs is deterministic.
    SDL_qsort(vid->output_list, vid->output_ਗਿਣਤੀ, ਆਕਾਰ(SDL_Display_ਅੰਕੜੇ *), Wayland_DisplayPositionCompare);

    // Derive the output pixel coordinates if scale to display is enabled.
    ਜੇ (vid->scale_ਮੰਜ਼ਿਲ_display_enabled) {
        Wayland_DeriveOutputPixelCoordinates(vid);
    }

    // Find a suitable primary display and move it to the front of the list.
    ਅਚਲ ਪੂਰਨ primary_ਸੂਚਕਾਂਕ = Wayland_GetPrimaryDisplay(vid);
    ਜੇ (primary_ਸੂਚਕਾਂਕ) {
        SDL_Display_ਅੰਕੜੇ *primary = vid->output_list[primary_ਸੂਚਕਾਂਕ];
        SDL_memmove(&vid->output_list[1], &vid->output_list[0], ਆਕਾਰ(SDL_Display_ਅੰਕੜੇ *) * primary_ਸੂਚਕਾਂਕ);
        vid->output_list[0] = primary;
    }

    // Apply the ordering hint, if specified.
    Wayland_ਛਾਂਟੋ_Outputs_By_ਤਰਜੀਹ_Hint(vid);
}

ਸਥਿਰ ਖਾਲੀ Wayland_Refresh_ਖਿੜਕੀ_Positions()
{
    SDL_VideoDevice *vid = SDL_GetVideoDevice();

    ਲਈ (SDL_ਖਿੜਕੀ *w = vid->windows; w; w = w->ਅਗਲਾ) {
        Wayland_Update_ਖਿੜਕੀ_Position(w);
    }
}

ਸਥਿਰ ਖਾਲੀ handle_wl_output_ਪੂਰਾ(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_output *output);

// Initialization/Query functions
ਸਥਿਰ bool Wayland_VideoInit(SDL_VideoDevice *_this);
ਸਥਿਰ bool Wayland_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
ਸਥਿਰ ਖਾਲੀ Wayland_VideoQuit(SDL_VideoDevice *_this);

ਸਥਿਰ ਅਚਲ ਅੱਖਰ *SDL_WAYLAND_surface_ਟੈਗ = "sdl-window";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ *SDL_WAYLAND_output_ਟੈਗ = "sdl-output";

ਖਾਲੀ SDL_WAYLAND_ਰਜਿਸਟਰ_surface(ਬਣਤਰ wl_surface *surface)
{
    wl_proxy_ਸੈੱਟ_ਟੈਗ((ਬਣਤਰ wl_proxy *)surface, &SDL_WAYLAND_surface_ਟੈਗ);
}

ਖਾਲੀ SDL_WAYLAND_ਰਜਿਸਟਰ_output(ਬਣਤਰ wl_output *output)
{
    wl_proxy_ਸੈੱਟ_ਟੈਗ((ਬਣਤਰ wl_proxy *)output, &SDL_WAYLAND_output_ਟੈਗ);
}

bool SDL_WAYLAND_own_surface(ਬਣਤਰ wl_surface *surface)
{
    ਵਾਪਸ wl_proxy_get_ਟੈਗ((ਬਣਤਰ wl_proxy *)surface) == &SDL_WAYLAND_surface_ਟੈਗ;
}

bool SDL_WAYLAND_own_output(ਬਣਤਰ wl_output *output)
{
    ਵਾਪਸ wl_proxy_get_ਟੈਗ((ਬਣਤਰ wl_proxy *)output) == &SDL_WAYLAND_output_ਟੈਗ;
}

/* External surfaces may have their own user data attached, the modification of which
 * can cause problems with external toolkits. Instead, external windows are kept in
 * their own list, and a search is conducted to find a matching surface.
 */
ਸਥਿਰ ਬਣਤਰ wl_list external_ਖਿੜਕੀ_list;

ਖਾਲੀ Wayland_ਜੋੜੋ_ਖਿੜਕੀ_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ_External_List(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ)
{
    WAYLAND_wl_list_ਪਾਓ(&external_ਖਿੜਕੀ_list, &ਅੰਕੜੇ->external_ਖਿੜਕੀ_list_link);
}

ਖਾਲੀ Wayland_Remove_ਖਿੜਕੀ_ਅੰਕੜੇ_From_External_List(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ)
{
    WAYLAND_wl_list_remove(&ਅੰਕੜੇ->external_ਖਿੜਕੀ_list_link);
}

SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *Wayland_Get_ਖਿੜਕੀ_ਅੰਕੜੇ_For_Owned_Surface(ਬਣਤਰ wl_surface *surface)
{
    ਜੇ (SDL_WAYLAND_own_surface(surface)) {
        ਵਾਪਸ (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)wl_surface_get_user_ਅੰਕੜੇ(surface);
    } ਨਹੀਂਤਾਂ ਜੇ (!WAYLAND_wl_list_ਖਾਲੀ_ਥਾਵਾਂ(&external_ਖਿੜਕੀ_list)) {
        SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *p;
        wl_list_for_each (p, &external_ਖਿੜਕੀ_list, external_ਖਿੜਕੀ_list_link) {
            ਜੇ (p->surface == surface) {
                ਵਾਪਸ p;
            }
        }
    }

    ਵਾਪਸ ਨਿਰਾ;
}

ਬਣਤਰ wl_event_ਕਤਾਰ *Wayland_Display_Create_ਕਤਾਰ(ਬਣਤਰ wl_display *display, ਅਚਲ ਅੱਖਰ *name)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
    ਜੇ (WAYLAND_wl_display_create_ਕਤਾਰ_with_name) {
        ਵਾਪਸ WAYLAND_wl_display_create_ਕਤਾਰ_with_name(display, name);
    }
#ਜਾਂਜੇ SDL_WAYLAND_CHECK_ਸੰਸਕਰਣ(1, 23, 0)
    ਵਾਪਸ WAYLAND_wl_display_create_ਕਤਾਰ_with_name(display, name);
#ਜੇ_ਅੰਤ
    ਵਾਪਸ WAYLAND_wl_display_create_ਕਤਾਰ(display);
}

ਸਥਿਰ ਖਾਲੀ Wayland_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = device->ਅੰਦਰੂਨੀ;
    ਜੇ (ਅੰਕੜੇ->display && !ਅੰਕੜੇ->display_externally_owned) {
        WAYLAND_wl_display_disconnect(ਅੰਕੜੇ->display);
        SDL_ClearProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_ਸੂਚਕ);
    }
    SDL_free(ਅੰਕੜੇ);
    SDL_free(device);
    SDL_WAYLAND_UnloadSymbols();
}

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    bool has_fifo_v1;
    ਬਣਤਰ wl_fixes *wl_fixes;
} SDL_Wayland_Preferred_ਅੰਕੜੇ;

ਸਥਿਰ ਖਾਲੀ wayland_preferred_check_handle_global(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_registry *registry, uint32_t id,
                                                  ਅਚਲ ਅੱਖਰ *interface, uint32_t ਸੰਸਕਰਣ)
{
    SDL_Wayland_Preferred_ਅੰਕੜੇ *d = ਅੰਕੜੇ;

    ਜੇ (SDL_strcmp(interface, "wp_fifo_manager_v1") == 0) {
        d->has_fifo_v1 = true;
    }
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_WL_FIXES_ਸੰਸਕਰਣ
    ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(interface, wl_fixes_interface.name) == 0) {
        d->wl_fixes = wl_registry_bind(registry, id, &wl_fixes_interface, SDL_min(SDL_WL_FIXES_ਸੰਸਕਰਣ, ਸੰਸਕਰਣ));
    }
#ਜੇ_ਅੰਤ
}

ਸਥਿਰ ਖਾਲੀ wayland_preferred_check_remove_global(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_registry *registry, uint32_t id)
{
    SDL_Wayland_Preferred_ਅੰਕੜੇ *d = (SDL_Wayland_Preferred_ਅੰਕੜੇ *)ਅੰਕੜੇ;

    ਜੇ (d->wl_fixes && wl_fixes_get_ਸੰਸਕਰਣ(d->wl_fixes) >= WL_FIXES_ACK_GLOBAL_REMOVE_SINCE_ਸੰਸਕਰਣ) {
        wl_fixes_ack_global_remove(d->wl_fixes, registry, id);
    }
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ wl_registry_listener preferred_registry_listener = {
    wayland_preferred_check_handle_global,
    wayland_preferred_check_remove_global
};

ਸਥਿਰ bool Wayland_IsPreferred(ਬਣਤਰ wl_display *display)
{
    ਬਣਤਰ wl_registry *registry = wl_display_get_registry(display);
    SDL_Wayland_Preferred_ਅੰਕੜੇ preferred_ਅੰਕੜੇ = { 0 };

    ਜੇ (!registry) {
        SDL_ਸੈੱਟ_Error("Failed to get the Wayland registry");
        ਵਾਪਸ false;
    }

    wl_registry_ਜੋੜੋ_listener(registry, &preferred_registry_listener, &preferred_ਅੰਕੜੇ);

    WAYLAND_wl_display_roundtrip(display);

    ਜੇ (preferred_ਅੰਕੜੇ.wl_fixes) {
        wl_fixes_destroy_registry(preferred_ਅੰਕੜੇ.wl_fixes, registry);
        wl_fixes_destroy(preferred_ਅੰਕੜੇ.wl_fixes);
    }
    wl_registry_destroy(registry);

    ਜੇ (!preferred_ਅੰਕੜੇ.has_fifo_v1) {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "This compositor lacks support for the fifo-v1 protocol; falling back to XWayland for GPU performance reasons (set SDL_VIDEO_DRIVER=wayland to override)");
    }
    ਵਾਪਸ preferred_ਅੰਕੜੇ.has_fifo_v1;
}

ਸਥਿਰ SDL_VideoDevice *Wayland_CreateDevice(bool require_preferred_protocols)
{
    SDL_VideoDevice *device;
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ;
    ਬਣਤਰ wl_display *display = SDL_Get_ਸੂਚਕ_Property(SDL_GetGlobalProperties(),
                                                 SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_ਸੂਚਕ, ਨਿਰਾ);
    bool display_is_external = !!display;

    // Are we trying to connect to, or are currently in, a Wayland session?
    ਜੇ (!SDL_getenv("WAYLAND_DISPLAY")) {
        ਅਚਲ ਅੱਖਰ *session = SDL_getenv("XDG_SESSION_TYPE");
        ਜੇ (session && SDL_strcasecmp(session, "wayland") != 0) {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Wayland initialization failed: no Wayland session available");
            ਵਾਪਸ ਨਿਰਾ;
        }
    }

    ਜੇ (!SDL_WAYLAND_ਲੱਦੋ_Symbols()) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਜੇ (!display) {
        display = WAYLAND_wl_display_connect(ਨਿਰਾ);
        ਜੇ (!display) {
            SDL_WAYLAND_UnloadSymbols();
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to connect to the Wayland display server: %s", strerror(errno));
            ਵਾਪਸ ਨਿਰਾ;
        }
    }

    /*
     * If we are checking for preferred Wayland, then let's query for
     * fifo-v1's existence, so we don't regress GPU-bound performance
     * and frame-pacing by default due to swapchain starvation.
     */
    ਜੇ (require_preferred_protocols && !Wayland_IsPreferred(display)) {
        ਜੇ (!display_is_external) {
            WAYLAND_wl_display_disconnect(display);
        }
        SDL_WAYLAND_UnloadSymbols();
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਅੰਕੜੇ = SDL_calloc(1, ਆਕਾਰ(*ਅੰਕੜੇ));
    ਜੇ (!ਅੰਕੜੇ) {
        ਜੇ (!display_is_external) {
            WAYLAND_wl_display_disconnect(display);
        }
        SDL_WAYLAND_UnloadSymbols();
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਅੰਕੜੇ->initializing = true;
    ਅੰਕੜੇ->display = display;
    ਅੰਕੜੇ->display_externally_owned = display_is_external;
    ਅੰਕੜੇ->scale_ਮੰਜ਼ਿਲ_display_enabled = SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_SCALE_ਮੰਜ਼ਿਲ_DISPLAY, false);
    WAYLAND_wl_list_init(&ਅੰਕੜੇ->seat_list);
    WAYLAND_wl_list_init(&external_ਖਿੜਕੀ_list);

    // Initialize all variables that we clean on shutdown
    device = SDL_calloc(1, ਆਕਾਰ(SDL_VideoDevice));
    ਜੇ (!device) {
        SDL_free(ਅੰਕੜੇ);
        ਜੇ (!display_is_external) {
            WAYLAND_wl_display_disconnect(display);
        }
        SDL_WAYLAND_UnloadSymbols();
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਜੇ (!display_is_external) {
        SDL_ਸੈੱਟ_ਸੂਚਕ_Property(SDL_GetGlobalProperties(),
                               SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_ਸੂਚਕ, display);
    }

    device->ਅੰਦਰੂਨੀ = ਅੰਕੜੇ;

    // Set the function pointers
    device->VideoInit = Wayland_VideoInit;
    device->VideoQuit = Wayland_VideoQuit;
    device->GetDisplayBounds = Wayland_GetDisplayBounds;
    device->SuspendScreenSaver = Wayland_SuspendScreenSaver;

    device->PumpEvents = Wayland_PumpEvents;
    device->WaitEventTimeout = Wayland_WaitEventTimeout;
    device->SendWakeupEvent = Wayland_SendWakeupEvent;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
    device->GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ = Wayland_GLES_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ;
    device->GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval = Wayland_GLES_Get_ਅਦਲਾ_ਬਦਲੀ_Interval;
    device->GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval = Wayland_GLES_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval;
    device->GL_MakeCurrent = Wayland_GLES_MakeCurrent;
    device->GL_CreateContext = Wayland_GLES_CreateContext;
    device->GL_ਲੱਦੋ_Library = Wayland_GLES_ਲੱਦੋ_Library;
    device->GL_UnloadLibrary = Wayland_GLES_UnloadLibrary;
    device->GL_Get_Proc_ਪਤਾ = Wayland_GLES_Get_Proc_ਪਤਾ;
    device->GL_DestroyContext = Wayland_GLES_DestroyContext;
    device->GL_ਸੈੱਟ_Default_Profile_Config = Wayland_GLES_ਸੈੱਟ_Default_Profile_Config;
    device->GL_GetEGLSurface = Wayland_GLES_GetEGLSurface;
#ਜੇ_ਅੰਤ

    device->CreateSDLWindow = Wayland_Create_ਖਿੜਕੀ;
    device->Show_ਖਿੜਕੀ = Wayland_Show_ਖਿੜਕੀ;
    device->Hide_ਖਿੜਕੀ = Wayland_Hide_ਖਿੜਕੀ;
    device->Raise_ਖਿੜਕੀ = Wayland_Raise_ਖਿੜਕੀ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen = Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen;
    device->Maximize_ਖਿੜਕੀ = Wayland_Maximize_ਖਿੜਕੀ;
    device->Minimize_ਖਿੜਕੀ = Wayland_Minimize_ਖਿੜਕੀ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Rect = Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Rect;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Grab = Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Grab;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Keyboard_Grab = Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Keyboard_Grab;
    device->Restore_ਖਿੜਕੀ = Wayland_Restore_ਖਿੜਕੀ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Bordered = Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Bordered;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Resizable = Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Resizable;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Position = Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Position;
    device->ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ = Wayland_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Aspect_ਅਨੁਪਾਤ = Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Aspect_ਅਨੁਪਾਤ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Minimum_ਮਾਪ = Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Minimum_ਮਾਪ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_ਵੱਧ_ਤੋਂ_ਵੱਧ_ਮਾਪ = Wayland_ਸੈੱਟ_ਖਿੜਕੀ_ਵੱਧ_ਤੋਂ_ਵੱਧ_ਮਾਪ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪਾ = Wayland_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪਾ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Modal = Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Modal;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Opacity = Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Opacity;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Title = Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Title;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Icon = Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Icon;
    device->Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels = Wayland_Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels;
    device->Get_ਖਿੜਕੀ_Content_Scale = Wayland_Get_ਖਿੜਕੀ_Content_Scale;
    device->Get_ਖਿੜਕੀ_ICCProfile = Wayland_Get_ਖਿੜਕੀ_ICCProfile;
    device->Get_Display_For_ਖਿੜਕੀ = Wayland_Get_Display_For_ਖਿੜਕੀ;
    device->Destroy_ਖਿੜਕੀ = Wayland_Destroy_ਖਿੜਕੀ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_ਪ੍ਰਾਪਤੀ_Test = Wayland_ਸੈੱਟ_ਖਿੜਕੀ_ਪ੍ਰਾਪਤੀ_Test;
    device->Flash_ਖਿੜਕੀ = Wayland_Flash_ਖਿੜਕੀ;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_USE_LIBDBUS
    device->Apply_ਖਿੜਕੀ_ਤਰੱਕੀ = DBUS_Apply_ਖਿੜਕੀ_ਤਰੱਕੀ;
#ਜੇ_ਅੰਤ // SDL_USE_LIBDBUS
    device->HasScreenKeyboardSupport = Wayland_HasScreenKeyboardSupport;
    device->Show_ਖਿੜਕੀ_System_Menu = Wayland_Show_ਖਿੜਕੀ_System_Menu;
    device->Sync_ਖਿੜਕੀ = Wayland_Sync_ਖਿੜਕੀ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Focusable = Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Focusable;
    device->Reconfigure_ਖਿੜਕੀ = Wayland_Reconfigure_ਖਿੜਕੀ;
    device->AcceptDragAndDrop = Wayland_AcceptDragAndDrop;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_USE_LIBDBUS
    ਜੇ (SDL_SystemTheme_Init())
        device->system_theme = SDL_SystemTheme_Get();
#ਜੇ_ਅੰਤ

    device->Get_ਪਾਠ_Mime_Types = Wayland_Get_ਪਾਠ_Mime_Types;
    device->ਸੈੱਟ_Clipboard_ਅੰਕੜੇ = Wayland_ਸੈੱਟ_Clipboard_ਅੰਕੜੇ;
    device->Get_Clipboard_ਅੰਕੜੇ = Wayland_Get_Clipboard_ਅੰਕੜੇ;
    device->Has_Clipboard_ਅੰਕੜੇ = Wayland_Has_Clipboard_ਅੰਕੜੇ;
    device->ਸ਼ੁਰੂ_ਪਾਠ_ਨਿਵੇਸ਼ = Wayland_ਸ਼ੁਰੂ_ਪਾਠ_ਨਿਵੇਸ਼;
    device->Stop_ਪਾਠ_ਨਿਵੇਸ਼ = Wayland_Stop_ਪਾਠ_ਨਿਵੇਸ਼;
    device->Update_ਪਾਠ_ਨਿਵੇਸ਼_Area = Wayland_Update_ਪਾਠ_ਨਿਵੇਸ਼_Area;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_VULKAN
    device->Vulkan_ਲੱਦੋ_Library = Wayland_Vulkan_ਲੱਦੋ_Library;
    device->Vulkan_UnloadLibrary = Wayland_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = Wayland_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = Wayland_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = Wayland_Vulkan_DestroySurface;
    device->Vulkan_GetPresentationSupport = Wayland_Vulkan_GetPresentationSupport;
#ਜੇ_ਅੰਤ

    device->ਮੁਕਤ = Wayland_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_ਬਹੁਲਕ_SWITCHING_EMULATED |
                          VIDEO_DEVICE_CAPS_HAS_POPUP_ਖਿੜਕੀ_SUPPORT |
                          VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS |
                          VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES |
                          VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES;

    ਵਾਪਸ device;
}

ਸਥਿਰ SDL_VideoDevice *Wayland_Preferred_CreateDevice(ਖਾਲੀ)
{
    ਵਾਪਸ Wayland_CreateDevice(true);
}

ਸਥਿਰ SDL_VideoDevice *Wayland_Fallback_CreateDevice(ਖਾਲੀ)
{
    ਵਾਪਸ Wayland_CreateDevice(false);
}

VideoBootStrap Wayland_preferred_bootstrap = {
    WAYLANDVID_DRIVER_NAME, "SDL Wayland video driver",
    Wayland_Preferred_CreateDevice,
    Wayland_Show_ਸੁਨੇਹਾ_Box,
    true
};

VideoBootStrap Wayland_bootstrap = {
    WAYLANDVID_DRIVER_NAME, "SDL Wayland video driver",
    Wayland_Fallback_CreateDevice,
    Wayland_Show_ਸੁਨੇਹਾ_Box,
    false
};

ਸਥਿਰ ਖਾਲੀ handle_xdg_output_logical_position(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zxdg_output_v1 *xdg_output, int32_t x, int32_t y)
{
    SDL_Display_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ = (SDL_Display_ਅੰਕੜੇ *)ਅੰਕੜੇ;

    ਅੰਦਰੂਨੀ->geometry_ਬਦਲਿਆ |= ਅੰਦਰੂਨੀ->logical.x != x || ਅੰਦਰੂਨੀ->logical.y != y;
    ਅੰਦਰੂਨੀ->logical.x = x;
    ਅੰਦਰੂਨੀ->logical.y = y;
    ਅੰਦਰੂਨੀ->has_logical_position = true;
}

ਸਥਿਰ ਖਾਲੀ handle_xdg_output_logical_ਮਾਪ(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zxdg_output_v1 *xdg_output, int32_t ਚੌੜਾਈ, int32_t ਉਚਾਈ)
{
    SDL_Display_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ = (SDL_Display_ਅੰਕੜੇ *)ਅੰਕੜੇ;

    ਅੰਦਰੂਨੀ->geometry_ਬਦਲਿਆ |= ਅੰਦਰੂਨੀ->logical.ਚੌੜਾਈ != ਚੌੜਾਈ || ਅੰਦਰੂਨੀ->logical.ਉਚਾਈ != ਉਚਾਈ;
    ਅੰਦਰੂਨੀ->logical.ਚੌੜਾਈ = ਚੌੜਾਈ;
    ਅੰਦਰੂਨੀ->logical.ਉਚਾਈ = ਉਚਾਈ;
    ਅੰਦਰੂਨੀ->has_logical_ਮਾਪ = true;
}

ਸਥਿਰ ਖਾਲੀ handle_xdg_output_ਪੂਰਾ(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zxdg_output_v1 *xdg_output)
{
    SDL_Display_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ = ਅੰਕੜੇ;

    /*
     * xdg-output.done events are deprecated and only apply below version 3 of the protocol.
     * A wl-output.done event will be emitted in version 3 or higher.
     */
    ਜੇ (zxdg_output_v1_get_ਸੰਸਕਰਣ(ਅੰਦਰੂਨੀ->xdg_output) < 3) {
        handle_wl_output_ਪੂਰਾ(ਅੰਕੜੇ, ਅੰਦਰੂਨੀ->output);
    }
}

ਸਥਿਰ ਖਾਲੀ handle_xdg_output_name(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zxdg_output_v1 *xdg_output, ਅਚਲ ਅੱਖਰ *name)
{
    SDL_Display_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ = (SDL_Display_ਅੰਕੜੇ *)ਅੰਕੜੇ;

    // Deprecated as of wl_output v4.
    ਜੇ (wl_output_get_ਸੰਸਕਰਣ(ਅੰਦਰੂਨੀ->output) < WL_OUTPUT_NAME_SINCE_ਸੰਸਕਰਣ &&
        ਅੰਦਰੂਨੀ->display == 0) {
        SDL_free(ਅੰਦਰੂਨੀ->wl_output_name);
        ਅੰਦਰੂਨੀ->wl_output_name = SDL_strdup(name);
    }
}

ਸਥਿਰ ਖਾਲੀ handle_xdg_output_description(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zxdg_output_v1 *xdg_output, ਅਚਲ ਅੱਖਰ *description)
{
    SDL_Display_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ = (SDL_Display_ਅੰਕੜੇ *)ਅੰਕੜੇ;

    // Deprecated as of wl_output v4.
    ਜੇ (wl_output_get_ਸੰਸਕਰਣ(ਅੰਦਰੂਨੀ->output) < WL_OUTPUT_DESCRIPTION_SINCE_ਸੰਸਕਰਣ &&
        ਅੰਦਰੂਨੀ->display == 0) {
        // xdg-output descriptions, if available, supersede wl-output model names.
        SDL_free(ਅੰਦਰੂਨੀ->placeholder.name);
        ਅੰਦਰੂਨੀ->placeholder.name = SDL_strdup(description);
    }
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ zxdg_output_v1_listener xdg_output_listener = {
    handle_xdg_output_logical_position,
    handle_xdg_output_logical_ਮਾਪ,
    handle_xdg_output_ਪੂਰਾ,
    handle_xdg_output_name,
    handle_xdg_output_description,
};

ਸਥਿਰ ਖਾਲੀ ਜੋੜੋ_Emulated_Modes(SDL_Display_ਅੰਕੜੇ *dispdata, ਪੂਰਨ native_ਚੌੜਾਈ, ਪੂਰਨ native_ਉਚਾਈ)
{
    ਬਣਤਰ Emulated_ਬਹੁਲਕ
    {
        ਪੂਰਨ w;
        ਪੂਰਨ h;
    };

    // Resolution lists courtesy of XWayland
    ਅਚਲ ਬਣਤਰ Emulated_ਬਹੁਲਕ ਬਹੁਲਕ_list[] = {
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

    ਪੂਰਨ i;
    SDL_Display_ਬਹੁਲਕ ਬਹੁਲਕ;
    SDL_VideoDisplay *dpy = dispdata->display ? SDL_GetVideoDisplay(dispdata->display) : &dispdata->placeholder;
    ਅਚਲ bool rot_90 = native_ਚੌੜਾਈ < native_ਉਚਾਈ; // Reverse width/height for portrait displays.

    ਲਈ (i = 0; i < SDL_arraysize(ਬਹੁਲਕ_list); ++i) {
        SDL_zero(ਬਹੁਲਕ);
        ਬਹੁਲਕ.format = dpy->desktop_ਬਹੁਲਕ.format;
        ਬਹੁਲਕ.refresh_ਦਰ_numerator = dpy->desktop_ਬਹੁਲਕ.refresh_ਦਰ_numerator;
        ਬਹੁਲਕ.refresh_ਦਰ_denominator = dpy->desktop_ਬਹੁਲਕ.refresh_ਦਰ_denominator;

        ਜੇ (rot_90) {
            ਬਹੁਲਕ.w = ਬਹੁਲਕ_list[i].h;
            ਬਹੁਲਕ.h = ਬਹੁਲਕ_list[i].w;
        } ਨਹੀਂਤਾਂ {
            ਬਹੁਲਕ.w = ਬਹੁਲਕ_list[i].w;
            ਬਹੁਲਕ.h = ਬਹੁਲਕ_list[i].h;
        }

        // Only add modes that are smaller than the native mode.
        ਜੇ ((ਬਹੁਲਕ.w < native_ਚੌੜਾਈ && ਬਹੁਲਕ.h < native_ਉਚਾਈ) ||
            (ਬਹੁਲਕ.w < native_ਚੌੜਾਈ && ਬਹੁਲਕ.h == native_ਉਚਾਈ) ||
            (ਬਹੁਲਕ.w == native_ਚੌੜਾਈ && ਬਹੁਲਕ.h < native_ਉਚਾਈ)) {
            SDL_ਜੋੜੋ_Fullscreen_Display_ਬਹੁਲਕ(dpy, &ਬਹੁਲਕ);
        }
    }
}

ਸਥਿਰ ਖਾਲੀ handle_wl_output_geometry(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_output *output, ਪੂਰਨ x, ਪੂਰਨ y,
                                      ਪੂਰਨ physical_ਚੌੜਾਈ_2, ਪੂਰਨ physical_ਉਚਾਈ_2, ਪੂਰਨ subpixel,
                                      ਅਚਲ ਅੱਖਰ *make, ਅਚਲ ਅੱਖਰ *model, ਪੂਰਨ transform)
{
    SDL_Display_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ = (SDL_Display_ਅੰਕੜੇ *)ਅੰਕੜੇ;

    // Apply the change from wl-output only if xdg-output is not supported
    ਜੇ (!ਅੰਦਰੂਨੀ->has_logical_position) {
        ਅੰਦਰੂਨੀ->geometry_ਬਦਲਿਆ |= ਅੰਦਰੂਨੀ->logical.x != x || ਅੰਦਰੂਨੀ->logical.y != y;
        ਅੰਦਰੂਨੀ->logical.x = x;
        ਅੰਦਰੂਨੀ->logical.y = y;
    }
    ਅੰਦਰੂਨੀ->physical.ਚੌੜਾਈ_mm = physical_ਚੌੜਾਈ_2;
    ਅੰਦਰੂਨੀ->physical.ਉਚਾਈ_mm = physical_ਉਚਾਈ_2;

    // The model is only used for the output name if wl_output or xdg-output haven't provided a description.
    ਜੇ (ਅੰਦਰੂਨੀ->display == 0 && !ਅੰਦਰੂਨੀ->placeholder.name) {
        ਅੰਦਰੂਨੀ->placeholder.name = SDL_strdup(model);
    }

    ਅੰਦਰੂਨੀ->transform = transform;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TF_CASE(ਵਿੱਚ_2, ਬਾਹਰਲਾ)                                 \
    ਹਾਲਤ WL_OUTPUT_TRANSFORM_##in:                       \
        ਅੰਦਰੂਨੀ->orientation = SDL_ORIENTATION_##out; \
        ਰੋਕੋ;
    ਜੇ (ਅੰਦਰੂਨੀ->physical.ਚੌੜਾਈ_mm >= ਅੰਦਰੂਨੀ->physical.ਉਚਾਈ_mm) {
        ਚੋਣ (transform) {
            TF_CASE(ਸਾਧਾਰਨ_2, LANDSCAPE)
            TF_CASE(90, PORTRAIT)
            TF_CASE(180, LANDSCAPE_FLIPPED)
            TF_CASE(270, PORTRAIT_FLIPPED)
            TF_CASE(FLIPPED, LANDSCAPE_FLIPPED)
            TF_CASE(FLIPPED_90, PORTRAIT_FLIPPED)
            TF_CASE(FLIPPED_180, LANDSCAPE)
            TF_CASE(FLIPPED_270, PORTRAIT)
        }
    } ਨਹੀਂਤਾਂ {
        ਚੋਣ (transform) {
            TF_CASE(ਸਾਧਾਰਨ_2, PORTRAIT)
            TF_CASE(90, LANDSCAPE)
            TF_CASE(180, PORTRAIT_FLIPPED)
            TF_CASE(270, LANDSCAPE_FLIPPED)
            TF_CASE(FLIPPED, PORTRAIT_FLIPPED)
            TF_CASE(FLIPPED_90, LANDSCAPE_FLIPPED)
            TF_CASE(FLIPPED_180, PORTRAIT)
            TF_CASE(FLIPPED_270, LANDSCAPE)
        }
    }
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ TF_CASE
}

ਸਥਿਰ ਖਾਲੀ handle_wl_output_ਬਹੁਲਕ(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_output *output, uint32_t flags,
                                  ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਪੂਰਨ refresh)
{
    SDL_Display_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ = (SDL_Display_ਅੰਕੜੇ *)ਅੰਕੜੇ;

    ਜੇ (flags & WL_OUTPUT_ਬਹੁਲਕ_CURRENT) {
        ਅੰਦਰੂਨੀ->geometry_ਬਦਲਿਆ |= ਅੰਦਰੂਨੀ->pixel.ਚੌੜਾਈ != ਚੌੜਾਈ || ਅੰਦਰੂਨੀ->pixel.ਉਚਾਈ != ਉਚਾਈ;
        ਅੰਦਰੂਨੀ->pixel.ਚੌੜਾਈ = ਚੌੜਾਈ;
        ਅੰਦਰੂਨੀ->pixel.ਉਚਾਈ = ਉਚਾਈ;

        /*
         * Don't rotate this yet, wl-output coordinates are transformed in
         * handle_done and xdg-output coordinates are pre-transformed.
         */
        ਜੇ (!ਅੰਦਰੂਨੀ->has_logical_ਮਾਪ) {
            ਅੰਦਰੂਨੀ->geometry_ਬਦਲਿਆ |= ਅੰਦਰੂਨੀ->logical.ਚੌੜਾਈ != ਚੌੜਾਈ || ਅੰਦਰੂਨੀ->logical.ਉਚਾਈ != ਉਚਾਈ;
            ਅੰਦਰੂਨੀ->logical.ਚੌੜਾਈ = ਚੌੜਾਈ;
            ਅੰਦਰੂਨੀ->logical.ਉਚਾਈ = ਉਚਾਈ;
        }

        ਅੰਦਰੂਨੀ->refresh = refresh;
    }
}

ਸਥਿਰ ਖਾਲੀ handle_wl_output_ਪੂਰਾ(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_output *output)
{
    ਅਚਲ bool ਬਹੁਲਕ_emulation_enabled = SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_ਬਹੁਲਕ_EMULATION, true);
    SDL_Display_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ = (SDL_Display_ਅੰਕੜੇ *)ਅੰਕੜੇ;
    SDL_Video_ਅੰਕੜੇ *video = ਅੰਦਰੂਨੀ->videodata;
    SDL_Display_ਬਹੁਲਕ native_ਬਹੁਲਕ, desktop_ਬਹੁਲਕ;

    /*
     * When using xdg-output, two wl-output.done events will be emitted:
     * one at the completion of wl-display and one at the completion of xdg-output.
     *
     * All required events must be received before proceeding.
     */
    ਅਚਲ ਪੂਰਨ event_await_ਗਿਣਤੀ = 1 + (ਅੰਦਰੂਨੀ->xdg_output != ਨਿਰਾ);

    ਅੰਦਰੂਨੀ->wl_output_ਪੂਰਾ_ਗਿਣਤੀ = SDL_min(ਅੰਦਰੂਨੀ->wl_output_ਪੂਰਾ_ਗਿਣਤੀ + 1, event_await_ਗਿਣਤੀ + 1);

    ਜੇ (ਅੰਦਰੂਨੀ->wl_output_ਪੂਰਾ_ਗਿਣਤੀ < event_await_ਗਿਣਤੀ) {
        ਵਾਪਸ;
    }

    // If the display was already created, reset and rebuild the mode list.
    SDL_VideoDisplay *dpy = SDL_GetVideoDisplay(ਅੰਦਰੂਨੀ->display);
    ਜੇ (dpy) {
        SDL_ResetFullscreenDisplayModes(dpy);
    }

    // The native display resolution
    SDL_zero(native_ਬਹੁਲਕ);
    native_ਬਹੁਲਕ.format = SDL_PIXELFORMAT_XRGB8888;

    // Transform the pixel values, if necessary.
    ਜੇ (ਅੰਦਰੂਨੀ->transform & WL_OUTPUT_TRANSFORM_90) {
        native_ਬਹੁਲਕ.w = ਅੰਦਰੂਨੀ->pixel.ਉਚਾਈ;
        native_ਬਹੁਲਕ.h = ਅੰਦਰੂਨੀ->pixel.ਚੌੜਾਈ;
    } ਨਹੀਂਤਾਂ {
        native_ਬਹੁਲਕ.w = ਅੰਦਰੂਨੀ->pixel.ਚੌੜਾਈ;
        native_ਬਹੁਲਕ.h = ਅੰਦਰੂਨੀ->pixel.ਉਚਾਈ;
    }
    native_ਬਹੁਲਕ.refresh_ਦਰ_numerator = ਅੰਦਰੂਨੀ->refresh;
    native_ਬਹੁਲਕ.refresh_ਦਰ_denominator = 1000;

    ਜੇ (ਅੰਦਰੂਨੀ->has_logical_ਮਾਪ) { // If xdg-output is present...
        ਜੇ (native_ਬਹੁਲਕ.w != ਅੰਦਰੂਨੀ->logical.ਚੌੜਾਈ || native_ਬਹੁਲਕ.h != ਅੰਦਰੂਨੀ->logical.ਉਚਾਈ) {
            // ...and the compositor scales the logical viewport...
            ਜੇ (video->viewporter) {
                // ...and viewports are supported, calculate the true scale of the output.
                ਅੰਦਰੂਨੀ->scale_ਗੁਣਕ_2 = (ਦੁੱਗਣਾ)native_ਬਹੁਲਕ.w / (ਦੁੱਗਣਾ)ਅੰਦਰੂਨੀ->logical.ਚੌੜਾਈ;
            } ਨਹੀਂਤਾਂ {
                // ...otherwise, the 'native' pixel values are a multiple of the logical screen size.
                ਅੰਦਰੂਨੀ->scale_ਗੁਣਕ_2 = ਅੰਦਰੂਨੀ->integer_scale_ਗੁਣਕ;
                ਅੰਦਰੂਨੀ->pixel.ਚੌੜਾਈ = ਅੰਦਰੂਨੀ->logical.ਚੌੜਾਈ * ਅੰਦਰੂਨੀ->integer_scale_ਗੁਣਕ;
                ਅੰਦਰੂਨੀ->pixel.ਉਚਾਈ = ਅੰਦਰੂਨੀ->logical.ਉਚਾਈ * ਅੰਦਰੂਨੀ->integer_scale_ਗੁਣਕ;
            }
        } ਨਹੀਂਤਾਂ {
            /* ...and the output viewport is not scaled in the global compositing
             * space, the output dimensions need to be divided by the scale factor.
             *
             * NOTE: This path is needed for old versions of GNOME that predate fractional scaling.
             */
            ਅੰਦਰੂਨੀ->scale_ਗੁਣਕ_2 = ਅੰਦਰੂਨੀ->integer_scale_ਗੁਣਕ;
            ਅੰਦਰੂਨੀ->logical.ਚੌੜਾਈ /= ਅੰਦਰੂਨੀ->integer_scale_ਗੁਣਕ;
            ਅੰਦਰੂਨੀ->logical.ਉਚਾਈ /= ਅੰਦਰੂਨੀ->integer_scale_ਗੁਣਕ;
        }
    } ਨਹੀਂਤਾਂ {
        /* Calculate the points from the pixel values, if xdg-output isn't present.
         * Use the native mode pixel values since they are pre-transformed.
         */
        ਅੰਦਰੂਨੀ->scale_ਗੁਣਕ_2 = ਅੰਦਰੂਨੀ->integer_scale_ਗੁਣਕ;
        ਅੰਦਰੂਨੀ->logical.ਚੌੜਾਈ = native_ਬਹੁਲਕ.w / ਅੰਦਰੂਨੀ->integer_scale_ਗੁਣਕ;
        ਅੰਦਰੂਨੀ->logical.ਉਚਾਈ = native_ਬਹੁਲਕ.h / ਅੰਦਰੂਨੀ->integer_scale_ਗੁਣਕ;
    }

    // The scaled desktop mode
    SDL_zero(desktop_ਬਹੁਲਕ);
    desktop_ਬਹੁਲਕ.format = SDL_PIXELFORMAT_XRGB8888;

    ਜੇ (!video->scale_ਮੰਜ਼ਿਲ_display_enabled) {
        desktop_ਬਹੁਲਕ.w = ਅੰਦਰੂਨੀ->logical.ਚੌੜਾਈ;
        desktop_ਬਹੁਲਕ.h = ਅੰਦਰੂਨੀ->logical.ਉਚਾਈ;
        desktop_ਬਹੁਲਕ.pixel_density = (ਦਸ਼ਮਲਵ)ਅੰਦਰੂਨੀ->scale_ਗੁਣਕ_2;
    } ਨਹੀਂਤਾਂ {
        desktop_ਬਹੁਲਕ.w = native_ਬਹੁਲਕ.w;
        desktop_ਬਹੁਲਕ.h = native_ਬਹੁਲਕ.h;
        desktop_ਬਹੁਲਕ.pixel_density = 1.0f;
    }

    desktop_ਬਹੁਲਕ.refresh_ਦਰ_numerator = ਅੰਦਰੂਨੀ->refresh;
    desktop_ਬਹੁਲਕ.refresh_ਦਰ_denominator = 1000;

    ਜੇ (ਅੰਦਰੂਨੀ->display > 0) {
        dpy = SDL_GetVideoDisplay(ਅੰਦਰੂਨੀ->display);
    } ਨਹੀਂਤਾਂ {
        dpy = &ਅੰਦਰੂਨੀ->placeholder;
    }

    ਜੇ (video->scale_ਮੰਜ਼ਿਲ_display_enabled) {
        SDL_ਸੈੱਟ_Display_Content_Scale(dpy, (ਦਸ਼ਮਲਵ)ਅੰਦਰੂਨੀ->scale_ਗੁਣਕ_2);
    }

    // Set the desktop display mode.
    SDL_ਸੈੱਟ_Desktop_Display_ਬਹੁਲਕ(dpy, &desktop_ਬਹੁਲਕ);

    // Expose the unscaled, native resolution if the scale is 1.0 or viewports are available...
    ਜੇ (ਅੰਦਰੂਨੀ->scale_ਗੁਣਕ_2 == 1.0 || video->viewporter) {
        SDL_ਜੋੜੋ_Fullscreen_Display_ਬਹੁਲਕ(dpy, &native_ਬਹੁਲਕ);
        ਜੇ (native_ਬਹੁਲਕ.w != desktop_ਬਹੁਲਕ.w ||
            native_ਬਹੁਲਕ.h != desktop_ਬਹੁਲਕ.h) {
            SDL_ਜੋੜੋ_Fullscreen_Display_ਬਹੁਲਕ(dpy, &desktop_ਬਹੁਲਕ);
        }
    } ਨਹੀਂਤਾਂ {
        // ...otherwise expose the integer scaled variants of the desktop resolution down to 1.
        desktop_ਬਹੁਲਕ.pixel_density = 1.0f;

        ਲਈ (ਪੂਰਨ i = (ਪੂਰਨ)ਅੰਦਰੂਨੀ->scale_ਗੁਣਕ_2; i > 0; --i) {
            desktop_ਬਹੁਲਕ.w = ਅੰਦਰੂਨੀ->logical.ਚੌੜਾਈ * i;
            desktop_ਬਹੁਲਕ.h = ਅੰਦਰੂਨੀ->logical.ਉਚਾਈ * i;
            SDL_ਜੋੜੋ_Fullscreen_Display_ਬਹੁਲਕ(dpy, &desktop_ਬਹੁਲਕ);
        }
    }

    // Add emulated modes if wp_viewporter is supported and mode emulation is enabled.
    ਜੇ (video->viewporter && ਬਹੁਲਕ_emulation_enabled) {
        // The transformed display pixel width/height must be used here.
        ਜੋੜੋ_Emulated_Modes(ਅੰਦਰੂਨੀ, native_ਬਹੁਲਕ.w, native_ਬਹੁਲਕ.h);
    }

    ਜੇ (ਅੰਦਰੂਨੀ->display == 0) {
        // First time getting display info, initialize the VideoDisplay
        ਜੇ (ਅੰਦਰੂਨੀ->physical.ਚੌੜਾਈ_mm >= ਅੰਦਰੂਨੀ->physical.ਉਚਾਈ_mm) {
            ਅੰਦਰੂਨੀ->placeholder.natural_orientation = SDL_ORIENTATION_LANDSCAPE;
        } ਨਹੀਂਤਾਂ {
            ਅੰਦਰੂਨੀ->placeholder.natural_orientation = SDL_ORIENTATION_PORTRAIT;
        }
        ਅੰਦਰੂਨੀ->placeholder.current_orientation = ਅੰਦਰੂਨੀ->orientation;
        ਅੰਦਰੂਨੀ->placeholder.ਅੰਦਰੂਨੀ = ਅੰਦਰੂਨੀ;

        ਅੰਦਰੂਨੀ->placeholder.props = SDL_CreateProperties();
        SDL_ਸੈੱਟ_ਸੂਚਕ_Property(ਅੰਦਰੂਨੀ->placeholder.props, SDL_PROP_DISPLAY_WAYLAND_WL_OUTPUT_ਸੂਚਕ, ਅੰਦਰੂਨੀ->output);

        // During initialization, the displays will be added after enumeration is complete.
        ਜੇ (!video->initializing) {
            ਜੇ (video->wp_color_manager_v1) {
                Wayland_GetColorInfoForOutput(ਅੰਦਰੂਨੀ, false);
            }
            ਜੇ (video->scale_ਮੰਜ਼ਿਲ_display_enabled) {
                Wayland_DeriveOutputPixelCoordinates(video);
            }

            ਅੰਦਰੂਨੀ->display = SDL_ਜੋੜੋ_Video_Display(&ਅੰਦਰੂਨੀ->placeholder, true);
            Wayland_Refresh_ਖਿੜਕੀ_Positions();

            SDL_free(ਅੰਦਰੂਨੀ->placeholder.name);
            SDL_zero(ਅੰਦਰੂਨੀ->placeholder);
        }
    } ਨਹੀਂਤਾਂ {
        SDL_SendDisplayEvent(dpy, SDL_EVENT_DISPLAY_ORIENTATION, ਅੰਦਰੂਨੀ->orientation, 0);

        ਜੇ (ਅੰਦਰੂਨੀ->geometry_ਬਦਲਿਆ) {
            ਜੇ (video->scale_ਮੰਜ਼ਿਲ_display_enabled) {
                Wayland_DeriveOutputPixelCoordinates(video);
            }

            SDL_SendDisplayEvent(dpy, SDL_EVENT_DISPLAY_MOVED, 0, 0);
            Wayland_Refresh_ਖਿੜਕੀ_Positions();
        }
    }

    ਅੰਦਰੂਨੀ->geometry_ਬਦਲਿਆ = false;
}

ਸਥਿਰ ਖਾਲੀ handle_wl_output_scale(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_output *output, int32_t ਗੁਣਕ)
{
    SDL_Display_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ = (SDL_Display_ਅੰਕੜੇ *)ਅੰਕੜੇ;
    ਅੰਦਰੂਨੀ->integer_scale_ਗੁਣਕ = ਗੁਣਕ;
}

ਸਥਿਰ ਖਾਲੀ handle_wl_output_name(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_output *wl_output, ਅਚਲ ਅੱਖਰ *name)
{
    SDL_Display_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ = (SDL_Display_ਅੰਕੜੇ *)ਅੰਕੜੇ;

    SDL_free(ਅੰਦਰੂਨੀ->wl_output_name);
    ਅੰਦਰੂਨੀ->wl_output_name = SDL_strdup(name);
}

ਸਥਿਰ ਖਾਲੀ handle_wl_output_description(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_output *wl_output, ਅਚਲ ਅੱਖਰ *description)
{
    SDL_Display_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ = (SDL_Display_ਅੰਕੜੇ *)ਅੰਕੜੇ;

    ਜੇ (ਅੰਦਰੂਨੀ->display == 0) {
        // The description, if available, supersedes the model name.
        SDL_free(ਅੰਦਰੂਨੀ->placeholder.name);
        ਅੰਦਰੂਨੀ->placeholder.name = SDL_strdup(description);
    }
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ wl_output_listener output_listener = {
    handle_wl_output_geometry,   // Version 1
    handle_wl_output_ਬਹੁਲਕ,       // Version 1
    handle_wl_output_ਪੂਰਾ,       // Version 2
    handle_wl_output_scale,      // Version 2
    handle_wl_output_name,       // Version 4
    handle_wl_output_description // Version 4
};

ਸਥਿਰ ਖਾਲੀ handle_output_image_description_ਬਦਲਿਆ(ਖਾਲੀ *ਅੰਕੜੇ,
                                                    ਬਣਤਰ wp_color_management_output_v1 *wp_color_management_output_v1)
{
    SDL_Display_ਅੰਕੜੇ *display = (SDL_Display_ਅੰਕੜੇ *)ਅੰਕੜੇ;
    Wayland_GetColorInfoForOutput(display, false);
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ wp_color_management_output_v1_listener wp_color_management_output_listener = {
    handle_output_image_description_ਬਦਲਿਆ
};

ਸਥਿਰ bool Wayland_ਜੋੜੋ_display(SDL_Video_ਅੰਕੜੇ *d, uint32_t id, uint32_t ਸੰਸਕਰਣ)
{
    ਬਣਤਰ wl_output *output;
    SDL_Display_ਅੰਕੜੇ *ਅੰਕੜੇ;

    output = wl_registry_bind(d->registry, id, &wl_output_interface, ਸੰਸਕਰਣ);
    ਜੇ (!output) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Failed to retrieve output.");
    }
    ਅੰਕੜੇ = (SDL_Display_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(*ਅੰਕੜੇ));
    ਅੰਕੜੇ->videodata = d;
    ਅੰਕੜੇ->output = output;
    ਅੰਕੜੇ->registry_id = id;
    ਅੰਕੜੇ->scale_ਗੁਣਕ_2 = 1.0f;
    ਅੰਕੜੇ->integer_scale_ਗੁਣਕ = 1;

    wl_output_ਜੋੜੋ_listener(output, &output_listener, ਅੰਕੜੇ);
    SDL_WAYLAND_ਰਜਿਸਟਰ_output(output);

    // Keep a list of outputs for sorting and deferred protocol initialization.
    ਜੇ (d->output_ਗਿਣਤੀ == d->output_max) {
        d->output_max += 4;
        d->output_list = SDL_realloc(d->output_list, ਆਕਾਰ(SDL_Display_ਅੰਕੜੇ *) * d->output_max);
    }
    d->output_list[d->output_ਗਿਣਤੀ++] = ਅੰਕੜੇ;

    ਜੇ (ਅੰਕੜੇ->videodata->xdg_output_manager) {
        ਅੰਕੜੇ->xdg_output = zxdg_output_manager_v1_get_xdg_output(ਅੰਕੜੇ->videodata->xdg_output_manager, output);
        zxdg_output_v1_ਜੋੜੋ_listener(ਅੰਕੜੇ->xdg_output, &xdg_output_listener, ਅੰਕੜੇ);
    }
    ਜੇ (ਅੰਕੜੇ->videodata->wp_color_manager_v1) {
        ਅੰਕੜੇ->wp_color_management_output = wp_color_manager_v1_get_output(ਅੰਕੜੇ->videodata->wp_color_manager_v1, output);
        wp_color_management_output_v1_ਜੋੜੋ_listener(ਅੰਕੜੇ->wp_color_management_output, &wp_color_management_output_listener, ਅੰਕੜੇ);

        // If not initializing, this will be queried synchronously in wl_output.done.
        ਜੇ (d->initializing) {
            Wayland_GetColorInfoForOutput(ਅੰਕੜੇ, true);
        }
    }
    ਵਾਪਸ true;
}

ਸਥਿਰ ਖਾਲੀ Wayland_free_display(SDL_VideoDisplay *display, bool send_event)
{
    ਜੇ (display) {
        SDL_Display_ਅੰਕੜੇ *display_ਅੰਕੜੇ = display->ਅੰਦਰੂਨੀ;

        /* A preceding surface leave event is not guaranteed when an output is removed,
         * so ensure that no window continues to hold a reference to a removed output.
         */
        ਲਈ (SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = SDL_GetVideoDevice()->windows; ਖਿੜਕੀ; ਖਿੜਕੀ = ਖਿੜਕੀ->ਅਗਲਾ) {
            Wayland_Remove_Output_From_ਖਿੜਕੀ(ਖਿੜਕੀ->ਅੰਦਰੂਨੀ, display_ਅੰਕੜੇ);
        }

        SDL_free(display_ਅੰਕੜੇ->wl_output_name);

        ਜੇ (display_ਅੰਕੜੇ->wp_color_management_output) {
            Wayland_FreeColorInfoState(display_ਅੰਕੜੇ->color_info_state);
            wp_color_management_output_v1_destroy(display_ਅੰਕੜੇ->wp_color_management_output);
        }

        ਜੇ (display_ਅੰਕੜੇ->xdg_output) {
            zxdg_output_v1_destroy(display_ਅੰਕੜੇ->xdg_output);
        }

        ਜੇ (wl_output_get_ਸੰਸਕਰਣ(display_ਅੰਕੜੇ->output) >= WL_OUTPUT_RELEASE_SINCE_ਸੰਸਕਰਣ) {
            wl_output_release(display_ਅੰਕੜੇ->output);
        } ਨਹੀਂਤਾਂ {
            wl_output_destroy(display_ਅੰਕੜੇ->output);
        }

        SDL_DelVideoDisplay(display->id, send_event);
    }
}

ਸਥਿਰ ਖਾਲੀ Wayland_FinalizeDisplays(SDL_Video_ਅੰਕੜੇ *vid)
{
    Wayland_ਛਾਂਟੋ_Outputs(vid);

    ਲਈ(ਪੂਰਨ i = 0; i < vid->output_ਗਿਣਤੀ; ++i) {
        SDL_Display_ਅੰਕੜੇ *d = vid->output_list[i];
        d->display = SDL_ਜੋੜੋ_Video_Display(&d->placeholder, false);
        SDL_free(d->placeholder.name);
        SDL_zero(d->placeholder);
    }
}

ਸਥਿਰ ਖਾਲੀ Wayland_init_xdg_output(SDL_Video_ਅੰਕੜੇ *d)
{
    ਲਈ (ਪੂਰਨ i = 0; i < d->output_ਗਿਣਤੀ; ++i) {
        SDL_Display_ਅੰਕੜੇ *disp = d->output_list[i];
        disp->xdg_output = zxdg_output_manager_v1_get_xdg_output(disp->videodata->xdg_output_manager, disp->output);
        zxdg_output_v1_ਜੋੜੋ_listener(disp->xdg_output, &xdg_output_listener, disp);
    }
}

ਸਥਿਰ ਖਾਲੀ Wayland_InitColorManager(SDL_Video_ਅੰਕੜੇ *d)
{
    ਲਈ (ਪੂਰਨ i = 0; i < d->output_ਗਿਣਤੀ; ++i) {
        SDL_Display_ਅੰਕੜੇ *disp = d->output_list[i];
        disp->wp_color_management_output = wp_color_manager_v1_get_output(disp->videodata->wp_color_manager_v1, disp->output);
        wp_color_management_output_v1_ਜੋੜੋ_listener(disp->wp_color_management_output, &wp_color_management_output_listener, disp);
        Wayland_GetColorInfoForOutput(disp, true);
    }
}

ਸਥਿਰ ਖਾਲੀ handle_xdg_session_created(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ xdg_session_v1 *xdg_session_v1, ਅਚਲ ਅੱਖਰ *id)
{
    SDL_ਸੈੱਟ_String_Property(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, id);
}

ਸਥਿਰ ਖਾਲੀ handle_xdg_session_restored(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ xdg_session_v1 *xdg_session_v1)
{
    // NOP
}

ਸਥਿਰ ਖਾਲੀ handle_xdg_session_replaced(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ xdg_session_v1 *xdg_session_v1)
{
    SDL_VideoDevice *viddev = SDL_GetVideoDevice();
    SDL_Video_ਅੰਕੜੇ *viddata = ਅੰਕੜੇ;

    // Clean up all session objects, as they have become inert, and should be destroyed.
    SDL_ਸੈੱਟ_String_Property(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, ਨਿਰਾ);

    ਲਈ (SDL_ਖਿੜਕੀ *w = viddev->windows; w; w = w->ਅਗਲਾ) {
        SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *d = w->ਅੰਦਰੂਨੀ;

        ਜੇ (d->xdg_toplevel_session) {
            xdg_toplevel_session_v1_destroy(d->xdg_toplevel_session);
            d->xdg_toplevel_session = ਨਿਰਾ;

            SDL_free(d->session_id);
            d->session_id = ਨਿਰਾ;
        }
    }

    ਜੇ (viddata->xdg_session) {
        xdg_session_v1_destroy(viddata->xdg_session);
        viddata->xdg_session = ਨਿਰਾ;
    }
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ xdg_session_v1_listener xdg_session_listener = {
    .created  = handle_xdg_session_created,
    .restored = handle_xdg_session_restored,
    .replaced = handle_xdg_session_replaced
};

ਖਾਲੀ Wayland_CreateSession(SDL_Video_ਅੰਕੜੇ *viddata)
{
    ਜੇ (!viddata->xdg_session_manager) {
        // Set the ID string to null if session management is not available.
        SDL_ਸੈੱਟ_String_Property(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, ਨਿਰਾ);
        ਵਾਪਸ;
    }

    // Register a new session, if one does not yet exist.
    ਜੇ (!viddata->xdg_session) {
        ਅਚਲ ਅੱਖਰ *session_id = SDL_GetStringProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, ਨਿਰਾ);
        ਜੇ (session_id) {
            ਜੇ (*session_id == '\0') {
                // Create a new session if the ID string is empty.
                session_id = ਨਿਰਾ;
            }

            ਅਚਲ ਗਿਣਤੀ xdg_session_manager_v1_reason reason = session_id ? XDG_SESSION_MANAGER_V1_REASON_SESSION_RESTORE : XDG_SESSION_MANAGER_V1_REASON_LAUNCH;
            viddata->xdg_session = xdg_session_manager_v1_get_session(viddata->xdg_session_manager, reason, session_id);
            xdg_session_v1_ਜੋੜੋ_listener(viddata->xdg_session, &xdg_session_listener, viddata);
        }
    }
}

ਸਥਿਰ ਖਾਲੀ Wayland_SessionDestroy(SDL_Video_ਅੰਕੜੇ *viddata)
{
    // If the session string was cleared, remove the session.
    ਜੇ (viddata->xdg_session) {
        ਅਚਲ ਅੱਖਰ *session_id = SDL_GetStringProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, ਨਿਰਾ);
        ਜੇ (!session_id || *session_id == '\0') {
            xdg_session_v1_remove(viddata->xdg_session);

            WAYLAND_wl_display_roundtrip(viddata->display);
        } ਨਹੀਂਤਾਂ {
            xdg_session_v1_destroy(viddata->xdg_session);
        }

        viddata->xdg_session = ਨਿਰਾ;
    }
}

ਸਥਿਰ ਖਾਲੀ handle_xdg_wm_ਅਧਾਰ_ping(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ xdg_wm_ਅਧਾਰ *xdg, uint32_t serial)
{
    xdg_wm_ਅਧਾਰ_pong(xdg, serial);
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ xdg_wm_ਅਧਾਰ_listener xdg_wm_ਅਧਾਰ_listener_2 = {
    handle_xdg_wm_ਅਧਾਰ_ping
};

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
ਸਥਿਰ ਖਾਲੀ libdecor_error(ਬਣਤਰ libdecor *context,
                           ਗਿਣਤੀ libdecor_error error,
                           ਅਚਲ ਅੱਖਰ *ਸੁਨੇਹਾ)
{
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "libdecor error (%d): %s", error, ਸੁਨੇਹਾ);
}

ਸਥਿਰ ਬਣਤਰ libdecor_interface libdecor_interface = {
    libdecor_error
};
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਖਾਲੀ handle_registry_global(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_registry *registry, uint32_t id,
                                   ਅਚਲ ਅੱਖਰ *interface, uint32_t ਸੰਸਕਰਣ)
{
    SDL_Video_ਅੰਕੜੇ *d = ਅੰਕੜੇ;

    ਜੇ (SDL_strcmp(interface, wl_compositor_interface.name) == 0) {
        d->compositor = wl_registry_bind(d->registry, id, &wl_compositor_interface, SDL_min(SDL_WL_COMPOSITOR_ਸੰਸਕਰਣ, ਸੰਸਕਰਣ));
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(interface, wl_subcompositor_interface.name) == 0) {
        d->subcompositor = wl_registry_bind(d->registry, id, &wl_subcompositor_interface, 1);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(interface, wl_output_interface.name) == 0) {
        Wayland_ਜੋੜੋ_display(d, id, SDL_min(ਸੰਸਕਰਣ, SDL_WL_OUTPUT_ਸੰਸਕਰਣ));
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(interface, wl_seat_interface.name) == 0) {
        ਬਣਤਰ wl_seat *seat = wl_registry_bind(d->registry, id, &wl_seat_interface, SDL_min(SDL_WL_SEAT_ਸੰਸਕਰਣ, ਸੰਸਕਰਣ));
        Wayland_DisplayCreateSeat(d, seat, id);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(interface, xdg_wm_ਅਧਾਰ_interface.name) == 0) {
        d->shell.xdg = wl_registry_bind(d->registry, id, &xdg_wm_ਅਧਾਰ_interface, SDL_min(ਸੰਸਕਰਣ, 7));
        xdg_wm_ਅਧਾਰ_ਜੋੜੋ_listener(d->shell.xdg, &xdg_wm_ਅਧਾਰ_listener_2, ਨਿਰਾ);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(interface, wl_shm_interface.name) == 0) {
        d->shm = wl_registry_bind(registry, id, &wl_shm_interface, SDL_min(SDL_WL_SHM_ਸੰਸਕਰਣ, ਸੰਸਕਰਣ));
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(interface, zwp_relative_ਸੂਚਕ_manager_v1_interface.name) == 0) {
        d->relative_ਸੂਚਕ_manager = wl_registry_bind(d->registry, id, &zwp_relative_ਸੂਚਕ_manager_v1_interface, 1);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(interface, zwp_ਸੂਚਕ_constraints_v1_interface.name) == 0) {
        d->ਸੂਚਕ_constraints = wl_registry_bind(d->registry, id, &zwp_ਸੂਚਕ_constraints_v1_interface, 1);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(interface, zwp_keyboard_shortcuts_inhibit_manager_v1_interface.name) == 0) {
        d->ਕੁੰਜੀ_inhibitor_manager = wl_registry_bind(d->registry, id, &zwp_keyboard_shortcuts_inhibit_manager_v1_interface, 1);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(interface, zwp_idle_inhibit_manager_v1_interface.name) == 0) {
        d->idle_inhibit_manager = wl_registry_bind(d->registry, id, &zwp_idle_inhibit_manager_v1_interface, 1);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(interface, xdg_activation_v1_interface.name) == 0) {
        d->activation_manager = wl_registry_bind(d->registry, id, &xdg_activation_v1_interface, 1);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(interface, zwp_ਪਾਠ_ਨਿਵੇਸ਼_manager_v3_interface.name) == 0) {
        d->ਪਾਠ_ਨਿਵੇਸ਼_manager = wl_registry_bind(d->registry, id, &zwp_ਪਾਠ_ਨਿਵੇਸ਼_manager_v3_interface, 1);
        Wayland_Display_Init_ਪਾਠ_ਨਿਵੇਸ਼_Manager(d, id);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(interface, wl_ਅੰਕੜੇ_device_manager_interface.name) == 0) {
        d->ਅੰਕੜੇ_device_manager = wl_registry_bind(d->registry, id, &wl_ਅੰਕੜੇ_device_manager_interface, SDL_min(3, ਸੰਸਕਰਣ));
        Wayland_Display_Init_ਅੰਕੜੇ_Device_Manager(d);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(interface, zwp_primary_selection_device_manager_v1_interface.name) == 0) {
        d->primary_selection_device_manager = wl_registry_bind(d->registry, id, &zwp_primary_selection_device_manager_v1_interface, 1);
        Wayland_DisplayInitPrimarySelectionDeviceManager(d);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(interface, zxdg_decoration_manager_v1_interface.name) == 0) {
        d->decoration_manager = wl_registry_bind(d->registry, id, &zxdg_decoration_manager_v1_interface, SDL_min(2, ਸੰਸਕਰਣ));
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(interface, zwp_tablet_manager_v2_interface.name) == 0) {
        d->tablet_manager = wl_registry_bind(d->registry, id, &zwp_tablet_manager_v2_interface, 1);
        Wayland_DisplayInitTabletManager(d);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(interface, zxdg_output_manager_v1_interface.name) == 0) {
        ਸੰਸਕਰਣ = SDL_min(ਸੰਸਕਰਣ, 3); // Versions 1 through 3 are supported.
        d->xdg_output_manager = wl_registry_bind(d->registry, id, &zxdg_output_manager_v1_interface, ਸੰਸਕਰਣ);
        Wayland_init_xdg_output(d);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(interface, wp_viewporter_interface.name) == 0) {
        d->viewporter = wl_registry_bind(d->registry, id, &wp_viewporter_interface, 1);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(interface, wp_fractional_scale_manager_v1_interface.name) == 0) {
        d->fractional_scale_manager = wl_registry_bind(d->registry, id, &wp_fractional_scale_manager_v1_interface, 1);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(interface, zwp_ਨਿਵੇਸ਼_timestamps_manager_v1_interface.name) == 0) {
        d->ਨਿਵੇਸ਼_timestamps_manager = wl_registry_bind(d->registry, id, &zwp_ਨਿਵੇਸ਼_timestamps_manager_v1_interface, 1);
        Wayland_Display_Init_ਨਿਵੇਸ਼_Timestamp_Manager(d);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(interface, wp_cursor_shape_manager_v1_interface.name) == 0) {
        d->cursor_shape_manager = wl_registry_bind(d->registry, id, &wp_cursor_shape_manager_v1_interface, SDL_min(ਸੰਸਕਰਣ, 2));
        Wayland_DisplayInitCursorShapeManager(d);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(interface, zxdg_exporter_v2_interface.name) == 0) {
        d->zxdg_exporter_v2 = wl_registry_bind(d->registry, id, &zxdg_exporter_v2_interface, 1);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(interface, xdg_wm_dialog_v1_interface.name) == 0) {
        d->xdg_wm_dialog_v1 = wl_registry_bind(d->registry, id, &xdg_wm_dialog_v1_interface, 1);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(interface, wp_alpha_modifier_v1_interface.name) == 0) {
        d->wp_alpha_modifier_v1 = wl_registry_bind(d->registry, id, &wp_alpha_modifier_v1_interface, 1);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(interface, xdg_toplevel_icon_manager_v1_interface.name) == 0) {
        d->xdg_toplevel_icon_manager_v1 = wl_registry_bind(d->registry, id, &xdg_toplevel_icon_manager_v1_interface, 1);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(interface, frog_color_management_factory_v1_interface.name) == 0) {
        d->frog_color_management_factory_v1 = wl_registry_bind(d->registry, id, &frog_color_management_factory_v1_interface, 1);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(interface, wp_color_manager_v1_interface.name) == 0) {
        d->wp_color_manager_v1 = wl_registry_bind(d->registry, id, &wp_color_manager_v1_interface, SDL_min(ਸੰਸਕਰਣ, 2));
        Wayland_InitColorManager(d);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(interface, wp_ਸੂਚਕ_warp_v1_interface.name) == 0) {
        d->wp_ਸੂਚਕ_warp_v1 = wl_registry_bind(d->registry, id, &wp_ਸੂਚਕ_warp_v1_interface, 1);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(interface, zwp_ਸੂਚਕ_gestures_v1_interface.name) == 0) {
        d->zwp_ਸੂਚਕ_gestures = wl_registry_bind(d->registry, id, &zwp_ਸੂਚਕ_gestures_v1_interface, SDL_min(ਸੰਸਕਰਣ, 3));
        Wayland_Display_Init_ਸੂਚਕ_Gesture_Manager(d);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(interface, wp_single_pixel_ਬਫਰ_manager_v1_interface.name) == 0) {
        d->single_pixel_ਬਫਰ_manager = wl_registry_bind(d->registry, id, &wp_single_pixel_ਬਫਰ_manager_v1_interface, 1);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(interface, xdg_session_manager_v1_interface.name) == 0) {
        d->xdg_session_manager = wl_registry_bind(d->registry, id, &xdg_session_manager_v1_interface, 1);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(interface, xdg_toplevel_ਟੈਗ_manager_v1_interface.name) == 0) {
        d->xdg_toplevel_ਟੈਗ_manager = wl_registry_bind(d->registry, id, &xdg_toplevel_ਟੈਗ_manager_v1_interface, 1);
    }
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_WL_FIXES_ਸੰਸਕਰਣ
    ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(interface, wl_fixes_interface.name) == 0) {
        d->wl_fixes = wl_registry_bind(d->registry, id, &wl_fixes_interface, SDL_min(SDL_WL_FIXES_ਸੰਸਕਰਣ, ਸੰਸਕਰਣ));
    }
#ਜੇ_ਅੰਤ
}

ਸਥਿਰ ਖਾਲੀ handle_registry_remove_global(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_registry *registry, uint32_t id)
{
    SDL_Video_ਅੰਕੜੇ *d = ਅੰਕੜੇ;

    // We don't get an interface, just an ID, so check outputs and seats.
    ਲਈ (ਪੂਰਨ i = 0; i < d->output_ਗਿਣਤੀ; ++i) {
        SDL_Display_ਅੰਕੜੇ *disp = d->output_list[i];
        ਜੇ (disp->registry_id == id) {
            Wayland_free_display(SDL_GetVideoDisplay(disp->display), true);

            ਜੇ (i < d->output_ਗਿਣਤੀ) {
                SDL_memmove(&d->output_list[i], &d->output_list[i + 1], ਆਕਾਰ(SDL_Display_ਅੰਕੜੇ *) * (d->output_ਗਿਣਤੀ - i - 1));
            }

            d->output_ਗਿਣਤੀ--;
            ਜਾਓ ack_remove;
        }
    }

    SDL_WaylandSeat *seat, *ਆਰਜ਼ੀ;
    wl_list_for_each_ਸੁਰੱਖਿਅਤ (seat, ਆਰਜ਼ੀ, &d->seat_list, link) {
        ਜੇ (seat->registry_id == id) {
            Wayland_SeatDestroy(seat, false);
            ਜਾਓ ack_remove;
        }
    }

ack_remove:
    ਜੇ (d->wl_fixes && wl_fixes_get_ਸੰਸਕਰਣ(d->wl_fixes) >= WL_FIXES_ACK_GLOBAL_REMOVE_SINCE_ਸੰਸਕਰਣ) {
        wl_fixes_ack_global_remove(d->wl_fixes, registry, id);
    }
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ wl_registry_listener registry_listener = {
    handle_registry_global,
    handle_registry_remove_global
};

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
ਸਥਿਰ bool should_use_libdecor(SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ, bool ignore_xdg)
{
    ਜੇ (!SDL_WAYLAND_HAVE_WAYLAND_LIBDECOR) {
        ਵਾਪਸ false;
    }

    ਜੇ (SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_PREFER_LIBDECOR, false)) {
        ਵਾਪਸ true;
    }

    ਜੇ (ignore_xdg) {
        ਵਾਪਸ true;
    }

    ਜੇ (ਅੰਕੜੇ->decoration_manager) {
        ਵਾਪਸ false;
    }

    ਵਾਪਸ true;
}

ਸਥਿਰ ਖਾਲੀ LibdecorNew(SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ)
{
    ਅੰਕੜੇ->shell.libdecor = libdecor_new(ਅੰਕੜੇ->display, &libdecor_interface);
}

// Called in another thread, but the UI thread is blocked in SDL_WaitThread
// during that time, so it should be OK to dereference data without locks
ਸਥਿਰ ਪੂਰਨ SDLCALL Libdecor_New_ਵਿੱਚ_Thread(ਖਾਲੀ *ਅੰਕੜੇ)
{
    LibdecorNew((SDL_Video_ਅੰਕੜੇ *)ਅੰਕੜੇ);
    ਵਾਪਸ 0;
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_GETRESUID
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_getresuid getresuid
#ਨਹੀਂਤਾਂ
// Non-POSIX, but Linux and some BSDs have it.
// To reduce the number of code paths, if getresuid() isn't available at
// compile-time, we behave as though it existed but failed at runtime.
ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ SDL_getresuid(uid_t *ruid, uid_t *euid, uid_t *suid) {
    errno = ENOSYS;
    ਵਾਪਸ -1;
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_GETRESGID
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_getresgid getresgid
#ਨਹੀਂਤਾਂ
// Same as getresuid() but for the primary group
ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ SDL_getresgid(gid_t *rgid, gid_t *egid, gid_t *sgid) {
    errno = ENOSYS;
    ਵਾਪਸ -1;
}
#ਜੇ_ਅੰਤ

bool CanUseGtk(ਖਾਲੀ)
{
    // "Real", "effective" and "saved" IDs: see e.g. Linux credentials(7)
    uid_t ruid = -1, euid = -1, suid = -1;
    gid_t rgid = -1, egid = -1, sgid = -1;

    ਜੇ (!SDL_GetHintBoolean("SDL_ENABLE_GTK", true)) {
        SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "Not using GTK due to hint");
        ਵਾਪਸ false;
    }

    // This is intended to match the check in gtkmain.c, rather than being
    // an exhaustive check for having elevated privileges: as a result
    // we don't use Linux getauxval() or prctl PR_GET_DUMPABLE,
    // BSD issetugid(), or similar OS-specific detection

    ਜੇ (SDL_getresuid(&ruid, &euid, &suid) != 0) {
        ruid = suid = getuid();
        euid = geteuid();
    }

    ਜੇ (SDL_getresgid(&rgid, &egid, &sgid) != 0) {
        rgid = sgid = getgid();
        egid = getegid();
    }

    // Real ID != effective ID means we are setuid or setgid:
    // GTK will refuse to initialize, and instead will call exit().
    ਜੇ (ruid != euid || rgid != egid) {
        SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "Not using GTK due to setuid/setgid");
        ਵਾਪਸ false;
    }

    // Real ID != saved ID means we are setuid or setgid, we previously
    // dropped privileges, but we can regain them; this protects against
    // accidents but does not protect against arbitrary code execution.
    // Again, GTK will refuse to initialize if this is the case.
    ਜੇ (ruid != suid || rgid != sgid) {
        SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "Not using GTK due to saved uid/gid");
        ਵਾਪਸ false;
    }

    ਵਾਪਸ true;
}

bool Wayland_ਲੱਦੋ_Libdecor(SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ, bool ignore_xdg)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
    ਜੇ (ਅੰਕੜੇ->shell.libdecor != ਨਿਰਾ) {
        ਵਾਪਸ true; // Already loaded!
    }
    ਜੇ (should_use_libdecor(ਅੰਕੜੇ, ignore_xdg)) {
        ਜੇ (CanUseGtk()) {
            LibdecorNew(ਅੰਕੜੇ);
        } ਨਹੀਂਤਾਂ {
            // Intentionally initialize libdecor in a non-main thread
            // so that it will not use its GTK plugin, but instead will
            // fall back to the Cairo or dummy plugin
            SDL_Thread *thread = SDL_CreateThread(Libdecor_New_ਵਿੱਚ_Thread, "SDL_LibdecorNew", (ਖਾਲੀ *)ਅੰਕੜੇ);
            // Note that the other thread now "owns" data until we have
            // waited for it, so don't touch data here
            SDL_WaitThread(thread, ਨਿਰਾ);
        }

        ਵਾਪਸ ਅੰਕੜੇ->shell.libdecor != ਨਿਰਾ;
    }
#ਜੇ_ਅੰਤ
    ਵਾਪਸ false;
}

bool Wayland_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;

    ਅੰਕੜੇ->event_thread_context = Wayland_CreateEventThread(ਅੰਕੜੇ, "SDL Event Thread Queue");
    ਜੇ (!ਅੰਕੜੇ->event_thread_context) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Failed to create event thread context");
    }

    ਅੰਕੜੇ->ਕੰਮ_thread_context = Wayland_Create_ਕੰਮ_Thread();
    ਜੇ (!ਅੰਕੜੇ->ਕੰਮ_thread_context) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Failed to create job thread context");
    }

    ਅੰਕੜੇ->xkb_context = WAYLAND_xkb_context_new(0);
    ਜੇ (!ਅੰਕੜੇ->xkb_context) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Failed to create XKB context");
    }

    ਅੰਕੜੇ->registry = wl_display_get_registry(ਅੰਕੜੇ->display);
    ਜੇ (!ਅੰਕੜੇ->registry) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Failed to get the Wayland registry");
    }

    wl_registry_ਜੋੜੋ_listener(ਅੰਕੜੇ->registry, &registry_listener, ਅੰਕੜੇ);

    // First roundtrip to receive all registry objects.
    WAYLAND_wl_display_roundtrip(ਅੰਕੜੇ->display);

    // Require viewports and xdg-output for display scaling.
    ਜੇ (ਅੰਕੜੇ->scale_ਮੰਜ਼ਿਲ_display_enabled) {
        ਜੇ (!ਅੰਕੜੇ->viewporter) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Display scaling requires the missing 'wp_viewporter' protocol: disabling");
            ਅੰਕੜੇ->scale_ਮੰਜ਼ਿਲ_display_enabled = false;
        }
        ਜੇ (!ਅੰਕੜੇ->xdg_output_manager) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Display scaling requires the missing 'zxdg_output_manager_v1' protocol: disabling");
            ਅੰਕੜੇ->scale_ਮੰਜ਼ਿਲ_display_enabled = false;
        }
    }

    // Now that we have all the protocols, load libdecor if applicable
    Wayland_ਲੱਦੋ_Libdecor(ਅੰਕੜੇ, false);

    // Second roundtrip to receive all output events.
    WAYLAND_wl_display_roundtrip(ਅੰਕੜੇ->display);

    Wayland_FinalizeDisplays(ਅੰਕੜੇ);

    Wayland_InitMouse(ਅੰਕੜੇ);
    Wayland_InitKeyboard(_this);

    ਜੇ (ਅੰਕੜੇ->primary_selection_device_manager) {
        _this->ਸੈੱਟ_Primary_Selection_ਪਾਠ = Wayland_ਸੈੱਟ_Primary_Selection_ਪਾਠ;
        _this->Get_Primary_Selection_ਪਾਠ = Wayland_Get_Primary_Selection_ਪਾਠ;
        _this->Has_Primary_Selection_ਪਾਠ = Wayland_Has_Primary_Selection_ਪਾਠ;
    }

    ਅੰਕੜੇ->initializing = false;

    ਵਾਪਸ true;
}

ਸਥਿਰ bool Wayland_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    SDL_Video_ਅੰਕੜੇ *viddata = _this->ਅੰਦਰੂਨੀ;
    SDL_Display_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ = display->ਅੰਦਰੂਨੀ;

    ਜੇ (!viddata->scale_ਮੰਜ਼ਿਲ_display_enabled) {
        rect->x = ਅੰਦਰੂਨੀ->logical.x;
        rect->y = ਅੰਦਰੂਨੀ->logical.y;
    } ਨਹੀਂਤਾਂ {
        rect->x = ਅੰਦਰੂਨੀ->pixel.x;
        rect->y = ਅੰਦਰੂਨੀ->pixel.y;
    }

    // When an emulated, exclusive fullscreen window has focus, treat the mode dimensions as the display bounds.
    ਜੇ (display->fullscreen_ਖਿੜਕੀ &&
        display->fullscreen_ਖਿੜਕੀ->fullscreen_exclusive &&
        display->fullscreen_ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->ਸਰਗਰਮ &&
        display->fullscreen_ਖਿੜਕੀ->current_fullscreen_ਬਹੁਲਕ.w != 0 &&
        display->fullscreen_ਖਿੜਕੀ->current_fullscreen_ਬਹੁਲਕ.h != 0) {
        rect->w = display->fullscreen_ਖਿੜਕੀ->current_fullscreen_ਬਹੁਲਕ.w;
        rect->h = display->fullscreen_ਖਿੜਕੀ->current_fullscreen_ਬਹੁਲਕ.h;
    } ਨਹੀਂਤਾਂ {
        ਜੇ (!viddata->scale_ਮੰਜ਼ਿਲ_display_enabled) {
            rect->w = display->current_ਬਹੁਲਕ->w;
            rect->h = display->current_ਬਹੁਲਕ->h;
        } ਨਹੀਂਤਾਂ ਜੇ (ਅੰਦਰੂਨੀ->transform & WL_OUTPUT_TRANSFORM_90) {
            rect->w = ਅੰਦਰੂਨੀ->pixel.ਉਚਾਈ;
            rect->h = ਅੰਦਰੂਨੀ->pixel.ਚੌੜਾਈ;
        } ਨਹੀਂਤਾਂ {
            rect->w = ਅੰਦਰੂਨੀ->pixel.ਚੌੜਾਈ;
            rect->h = ਅੰਦਰੂਨੀ->pixel.ਉਚਾਈ;
        }
    }
    ਵਾਪਸ true;
}

ਸਥਿਰ ਖਾਲੀ Wayland_VideoCleanup(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    SDL_WaylandSeat *seat, *tmp;

    Wayland_SessionDestroy(ਅੰਕੜੇ);

    ਲਈ (ਪੂਰਨ i = _this->ਅੰਕ_displays - 1; i >= 0; --i) {
        SDL_VideoDisplay *display = _this->displays[i];
        Wayland_free_display(display, false);
    }
    SDL_free(ਅੰਕੜੇ->output_list);

    wl_list_for_each_ਸੁਰੱਖਿਅਤ (seat, tmp, &ਅੰਕੜੇ->seat_list, link) {
        Wayland_SeatDestroy(seat, true);
    }

    Wayland_FiniMouse(ਅੰਕੜੇ);
    Wayland_QuitKeyboard(_this);

    Wayland_DestroyEventThread(ਅੰਕੜੇ->event_thread_context);
    ਅੰਕੜੇ->event_thread_context = ਨਿਰਾ;

    Wayland_Destroy_ਕੰਮ_Thread(ਅੰਕੜੇ->ਕੰਮ_thread_context);
    ਅੰਕੜੇ->ਕੰਮ_thread_context = ਨਿਰਾ;

    ਜੇ (ਅੰਕੜੇ->ਸੂਚਕ_constraints) {
        zwp_ਸੂਚਕ_constraints_v1_destroy(ਅੰਕੜੇ->ਸੂਚਕ_constraints);
        ਅੰਕੜੇ->ਸੂਚਕ_constraints = ਨਿਰਾ;
    }

    ਜੇ (ਅੰਕੜੇ->relative_ਸੂਚਕ_manager) {
        zwp_relative_ਸੂਚਕ_manager_v1_destroy(ਅੰਕੜੇ->relative_ਸੂਚਕ_manager);
        ਅੰਕੜੇ->relative_ਸੂਚਕ_manager = ਨਿਰਾ;
    }

    ਜੇ (ਅੰਕੜੇ->activation_manager) {
        xdg_activation_v1_destroy(ਅੰਕੜੇ->activation_manager);
        ਅੰਕੜੇ->activation_manager = ਨਿਰਾ;
    }

    ਜੇ (ਅੰਕੜੇ->idle_inhibit_manager) {
        zwp_idle_inhibit_manager_v1_destroy(ਅੰਕੜੇ->idle_inhibit_manager);
        ਅੰਕੜੇ->idle_inhibit_manager = ਨਿਰਾ;
    }

    ਜੇ (ਅੰਕੜੇ->ਕੁੰਜੀ_inhibitor_manager) {
        zwp_keyboard_shortcuts_inhibit_manager_v1_destroy(ਅੰਕੜੇ->ਕੁੰਜੀ_inhibitor_manager);
        ਅੰਕੜੇ->ਕੁੰਜੀ_inhibitor_manager = ਨਿਰਾ;
    }

    ਜੇ (ਅੰਕੜੇ->ਪਾਠ_ਨਿਵੇਸ਼_manager) {
        zwp_ਪਾਠ_ਨਿਵੇਸ਼_manager_v3_destroy(ਅੰਕੜੇ->ਪਾਠ_ਨਿਵੇਸ਼_manager);
        ਅੰਕੜੇ->ਪਾਠ_ਨਿਵੇਸ਼_manager = ਨਿਰਾ;
    }

    ਜੇ (ਅੰਕੜੇ->xkb_context) {
        WAYLAND_xkb_context_unref(ਅੰਕੜੇ->xkb_context);
        ਅੰਕੜੇ->xkb_context = ਨਿਰਾ;
    }

    ਜੇ (ਅੰਕੜੇ->tablet_manager) {
        zwp_tablet_manager_v2_destroy((ਬਣਤਰ zwp_tablet_manager_v2 *)ਅੰਕੜੇ->tablet_manager);
        ਅੰਕੜੇ->tablet_manager = ਨਿਰਾ;
    }

    ਜੇ (ਅੰਕੜੇ->ਅੰਕੜੇ_device_manager) {
        wl_ਅੰਕੜੇ_device_manager_destroy(ਅੰਕੜੇ->ਅੰਕੜੇ_device_manager);
        ਅੰਕੜੇ->ਅੰਕੜੇ_device_manager = ਨਿਰਾ;
    }

    ਜੇ (ਅੰਕੜੇ->shm) {
        ਜੇ (wl_shm_get_ਸੰਸਕਰਣ(ਅੰਕੜੇ->shm) >= WL_SHM_RELEASE_SINCE_ਸੰਸਕਰਣ) {
            wl_shm_release(ਅੰਕੜੇ->shm);
        } ਨਹੀਂਤਾਂ {
            wl_shm_destroy(ਅੰਕੜੇ->shm);
        }
        ਅੰਕੜੇ->shm = ਨਿਰਾ;
    }

    ਜੇ (ਅੰਕੜੇ->shell.xdg) {
        xdg_wm_ਅਧਾਰ_destroy(ਅੰਕੜੇ->shell.xdg);
        ਅੰਕੜੇ->shell.xdg = ਨਿਰਾ;
    }

    ਜੇ (ਅੰਕੜੇ->decoration_manager) {
        zxdg_decoration_manager_v1_destroy(ਅੰਕੜੇ->decoration_manager);
        ਅੰਕੜੇ->decoration_manager = ਨਿਰਾ;
    }

    ਜੇ (ਅੰਕੜੇ->xdg_output_manager) {
        zxdg_output_manager_v1_destroy(ਅੰਕੜੇ->xdg_output_manager);
        ਅੰਕੜੇ->xdg_output_manager = ਨਿਰਾ;
    }

    ਜੇ (ਅੰਕੜੇ->viewporter) {
        wp_viewporter_destroy(ਅੰਕੜੇ->viewporter);
        ਅੰਕੜੇ->viewporter = ਨਿਰਾ;
    }

    ਜੇ (ਅੰਕੜੇ->primary_selection_device_manager) {
        zwp_primary_selection_device_manager_v1_destroy(ਅੰਕੜੇ->primary_selection_device_manager);
        ਅੰਕੜੇ->primary_selection_device_manager = ਨਿਰਾ;
    }

    ਜੇ (ਅੰਕੜੇ->fractional_scale_manager) {
        wp_fractional_scale_manager_v1_destroy(ਅੰਕੜੇ->fractional_scale_manager);
        ਅੰਕੜੇ->fractional_scale_manager = ਨਿਰਾ;
    }

    ਜੇ (ਅੰਕੜੇ->ਨਿਵੇਸ਼_timestamps_manager) {
        zwp_ਨਿਵੇਸ਼_timestamps_manager_v1_destroy(ਅੰਕੜੇ->ਨਿਵੇਸ਼_timestamps_manager);
        ਅੰਕੜੇ->ਨਿਵੇਸ਼_timestamps_manager = ਨਿਰਾ;
    }

    ਜੇ (ਅੰਕੜੇ->cursor_shape_manager) {
        wp_cursor_shape_manager_v1_destroy(ਅੰਕੜੇ->cursor_shape_manager);
        ਅੰਕੜੇ->cursor_shape_manager = ਨਿਰਾ;
    }

    ਜੇ (ਅੰਕੜੇ->zxdg_exporter_v2) {
        zxdg_exporter_v2_destroy(ਅੰਕੜੇ->zxdg_exporter_v2);
        ਅੰਕੜੇ->zxdg_exporter_v2 = ਨਿਰਾ;
    }

    ਜੇ (ਅੰਕੜੇ->xdg_wm_dialog_v1) {
        xdg_wm_dialog_v1_destroy(ਅੰਕੜੇ->xdg_wm_dialog_v1);
        ਅੰਕੜੇ->xdg_wm_dialog_v1 = ਨਿਰਾ;
    }

    ਜੇ (ਅੰਕੜੇ->wp_alpha_modifier_v1) {
        wp_alpha_modifier_v1_destroy(ਅੰਕੜੇ->wp_alpha_modifier_v1);
        ਅੰਕੜੇ->wp_alpha_modifier_v1 = ਨਿਰਾ;
    }

    ਜੇ (ਅੰਕੜੇ->xdg_toplevel_icon_manager_v1) {
        xdg_toplevel_icon_manager_v1_destroy(ਅੰਕੜੇ->xdg_toplevel_icon_manager_v1);
        ਅੰਕੜੇ->xdg_toplevel_icon_manager_v1 = ਨਿਰਾ;
    }

    ਜੇ (ਅੰਕੜੇ->frog_color_management_factory_v1) {
        frog_color_management_factory_v1_destroy(ਅੰਕੜੇ->frog_color_management_factory_v1);
        ਅੰਕੜੇ->frog_color_management_factory_v1 = ਨਿਰਾ;
    }

    ਜੇ (ਅੰਕੜੇ->wp_color_manager_v1) {
        wp_color_manager_v1_destroy(ਅੰਕੜੇ->wp_color_manager_v1);
        ਅੰਕੜੇ->wp_color_manager_v1 = ਨਿਰਾ;
    }

    ਜੇ (ਅੰਕੜੇ->wp_ਸੂਚਕ_warp_v1) {
        wp_ਸੂਚਕ_warp_v1_destroy(ਅੰਕੜੇ->wp_ਸੂਚਕ_warp_v1);
        ਅੰਕੜੇ->wp_ਸੂਚਕ_warp_v1 = ਨਿਰਾ;
    }

    ਜੇ (ਅੰਕੜੇ->zwp_ਸੂਚਕ_gestures) {
        ਜੇ (zwp_ਸੂਚਕ_gestures_v1_get_ਸੰਸਕਰਣ(ਅੰਕੜੇ->zwp_ਸੂਚਕ_gestures) >= ZWP_ਸੂਚਕ_GESTURES_V1_RELEASE_SINCE_ਸੰਸਕਰਣ) {
            zwp_ਸੂਚਕ_gestures_v1_release(ਅੰਕੜੇ->zwp_ਸੂਚਕ_gestures);
        } ਨਹੀਂਤਾਂ {
            zwp_ਸੂਚਕ_gestures_v1_destroy(ਅੰਕੜੇ->zwp_ਸੂਚਕ_gestures);
        }
        ਅੰਕੜੇ->zwp_ਸੂਚਕ_gestures = ਨਿਰਾ;
    }

    ਜੇ (ਅੰਕੜੇ->single_pixel_ਬਫਰ_manager) {
        wp_single_pixel_ਬਫਰ_manager_v1_destroy(ਅੰਕੜੇ->single_pixel_ਬਫਰ_manager);
        ਅੰਕੜੇ->single_pixel_ਬਫਰ_manager = ਨਿਰਾ;
    }

    ਜੇ (ਅੰਕੜੇ->xdg_session_manager) {
        xdg_session_manager_v1_destroy(ਅੰਕੜੇ->xdg_session_manager);
        ਅੰਕੜੇ->xdg_session_manager = ਨਿਰਾ;
    }

    ਜੇ (ਅੰਕੜੇ->xdg_toplevel_ਟੈਗ_manager) {
        xdg_toplevel_ਟੈਗ_manager_v1_destroy(ਅੰਕੜੇ->xdg_toplevel_ਟੈਗ_manager);
        ਅੰਕੜੇ->xdg_toplevel_ਟੈਗ_manager = ਨਿਰਾ;
    }

    ਜੇ (ਅੰਕੜੇ->subcompositor) {
        wl_subcompositor_destroy(ਅੰਕੜੇ->subcompositor);
        ਅੰਕੜੇ->subcompositor = ਨਿਰਾ;
    }

    ਜੇ (ਅੰਕੜੇ->compositor) {
        wl_compositor_destroy(ਅੰਕੜੇ->compositor);
        ਅੰਕੜੇ->compositor = ਨਿਰਾ;
    }

    ਜੇ (ਅੰਕੜੇ->registry) {
        ਜੇ (ਅੰਕੜੇ->wl_fixes) {
            wl_fixes_destroy_registry(ਅੰਕੜੇ->wl_fixes, ਅੰਕੜੇ->registry);
            wl_fixes_destroy(ਅੰਕੜੇ->wl_fixes);
            ਅੰਕੜੇ->wl_fixes = ਨਿਰਾ;
        }
        wl_registry_destroy(ਅੰਕੜੇ->registry);
        ਅੰਕੜੇ->registry = ਨਿਰਾ;
    }
}

ਸਥਿਰ bool Wayland_VideoReconnect(SDL_VideoDevice *_this)
{
#ਜੇ 0 // TODO RECONNECT: Uncomment all when https://invent.kde.org/plasma/kwin/-/wikis/Restarting is completed
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;

    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = ਨਿਰਾ;

    SDL_GLContext current_ctx = SDL_GL_GetCurrentContext();
    SDL_ਖਿੜਕੀ *current_ਖਿੜਕੀ = SDL_GL_Get_Current_ਖਿੜਕੀ();

    SDL_GL_MakeCurrent(ਨਿਰਾ, ਨਿਰਾ);
    Wayland_VideoCleanup(_this);

    SDL_ResetKeyboard();
    SDL_ResetMouse();
    ਜੇ (WAYLAND_wl_display_reconnect(ਅੰਕੜੇ->display) < 0) {
        ਵਾਪਸ false;
    }

    Wayland_VideoInit(_this);

    ਖਿੜਕੀ = _this->windows;
    ਜਦੋਂ (ਖਿੜਕੀ) {
        /* We're going to cheat _just_ for a second and strip the OpenGL flag.
         * The Wayland driver actually forces it in CreateWindow, and
         * RecreateWindow does a bunch of unloading/loading of libGL, so just
         * strip the flag so RecreateWindow doesn't mess with the GL context,
         * and CreateWindow will add it right back!
         * -flibit
         */
        ਖਿੜਕੀ->flags &= ~SDL_ਖਿੜਕੀ_OPENGL;

        SDL_Recreate_ਖਿੜਕੀ(ਖਿੜਕੀ, ਖਿੜਕੀ->flags);
        ਖਿੜਕੀ = ਖਿੜਕੀ->ਅਗਲਾ;
    }

    Wayland_RecreateCursors();

    ਜੇ (current_ਖਿੜਕੀ && current_ctx) {
        SDL_GL_MakeCurrent (current_ਖਿੜਕੀ, current_ctx);
    }
    ਵਾਪਸ true;
#ਨਹੀਂਤਾਂ
    ਵਾਪਸ false;
#ਜੇ_ਅੰਤ // 0
}

bool Wayland_HandleDisplayDisconnected(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *video_ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;

    /* Something has failed with the Wayland connection -- for example,
     * the compositor may have shut down and closed its end of the socket,
     * or there is a library-specific error.
     *
     * Try to recover once, then quit.
     */
    ਜੇ (video_ਅੰਕੜੇ->display_disconnected) {
        ਵਾਪਸ false;
    }

    ਜੇ (Wayland_VideoReconnect(_this)) {
        ਵਾਪਸ true;
    }

    video_ਅੰਕੜੇ->display_disconnected = true;
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Wayland display connection closed by server (fatal)");

    // Only send a single quit message, as application shutdown might call SDL_PumpEvents().
    SDL_SendQuit();

    ਵਾਪਸ false;
}

ਖਾਲੀ Wayland_VideoQuit(SDL_VideoDevice *_this)
{
    Wayland_VideoCleanup(_this);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    ਜੇ (ਅੰਕੜੇ->shell.libdecor) {
        libdecor_unref(ਅੰਕੜੇ->shell.libdecor);
        ਅੰਕੜੇ->shell.libdecor = ਨਿਰਾ;
    }
#ਜੇ_ਅੰਤ
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_WAYLAND
