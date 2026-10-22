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

#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_WAYLAND

#అన్తర్భావ "../../core/linux/SDL_system_theme.h"
#అన్తర్భావ "../../core/linux/SDL_progressbar.h"
#అన్తర్భావ "../../events/SDL_events_c.h"

#అన్తర్భావ "SDL_waylandclipboard.h"
#అన్తర్భావ "SDL_waylandcolor.h"
#అన్తర్భావ "SDL_waylandevents_c.h"
#అన్తర్భావ "SDL_waylandkeyboard.h"
#అన్తర్భావ "SDL_waylandmessagebox.h"
#అన్తర్భావ "SDL_waylandmouse.h"
#అన్తర్భావ "SDL_waylandopengles.h"
#అన్తర్భావ "SDL_waylandvideo.h"
#అన్తర్భావ "SDL_waylandvulkan.h"
#అన్తర్భావ "SDL_waylandwindow.h"

#అన్తర్భావ <fcntl.h>
#అన్తర్భావ <sys/types.h>
#అన్తర్భావ <unistd.h>
#అన్తర్భావ <errno.h>
#అన్తర్భావ <xkbcommon/xkbcommon.h>

#అన్తర్భావ <wayland-util.h>

#అన్తర్భావ "alpha-modifier-v1-client-protocol.h"
#అన్తర్భావ "cursor-shape-v1-client-protocol.h"
#అన్తర్భావ "fractional-scale-v1-client-protocol.h"
#అన్తర్భావ "frog-color-management-v1-client-protocol.h"
#అన్తర్భావ "idle-inhibit-unstable-v1-client-protocol.h"
#అన్తర్భావ "input-timestamps-unstable-v1-client-protocol.h"
#అన్తర్భావ "keyboard-shortcuts-inhibit-unstable-v1-client-protocol.h"
#అన్తర్భావ "pointer-constraints-unstable-v1-client-protocol.h"
#అన్తర్భావ "primary-selection-unstable-v1-client-protocol.h"
#అన్తర్భావ "relative-pointer-unstable-v1-client-protocol.h"
#అన్తర్భావ "tablet-v2-client-protocol.h"
#అన్తర్భావ "text-input-unstable-v3-client-protocol.h"
#అన్తర్భావ "viewporter-client-protocol.h"
#అన్తర్భావ "xdg-activation-v1-client-protocol.h"
#అన్తర్భావ "xdg-decoration-unstable-v1-client-protocol.h"
#అన్తర్భావ "xdg-dialog-v1-client-protocol.h"
#అన్తర్భావ "xdg-foreign-unstable-v2-client-protocol.h"
#అన్తర్భావ "xdg-output-unstable-v1-client-protocol.h"
#అన్తర్భావ "xdg-shell-client-protocol.h"
#అన్తర్భావ "xdg-toplevel-icon-v1-client-protocol.h"
#అన్తర్భావ "color-management-v1-client-protocol.h"
#అన్తర్భావ "pointer-warp-v1-client-protocol.h"
#అన్తర్భావ "pointer-gestures-unstable-v1-client-protocol.h"
#అన్తర్భావ "single-pixel-buffer-v1-client-protocol.h"
#అన్తర్భావ "xdg-session-management-v1-client-protocol.h"
#అన్తర్భావ "xdg-toplevel-tag-v1-client-protocol.h"

#నిర్వచితమైతే HAVE_LIBDECOR_H
#అన్తర్భావ <libdecor.h>
#అయితే_ముగింపు

#నిర్వచించు WAYLANDVID_DRIVER_NAME "wayland"

// Clamp core protocol versions on older versions of libwayland.
#ఒకవేళ SDL_WAYLAND_CHECK_సంస్కరణ(1, 22, 0)
#నిర్వచించు SDL_WL_COMPOSITOR_సంస్కరణ 6
#లేకపోతే
#నిర్వచించు SDL_WL_COMPOSITOR_సంస్కరణ 4
#అయితే_ముగింపు

#ఒకవేళ SDL_WAYLAND_CHECK_సంస్కరణ(1, 26, 0)
#నిర్వచించు SDL_WL_SEAT_సంస్కరణ 11
#లేదావేళ SDL_WAYLAND_CHECK_సంస్కరణ(1, 24, 0)
#నిర్వచించు SDL_WL_SEAT_సంస్కరణ 10
#లేదావేళ SDL_WAYLAND_CHECK_సంస్కరణ(1, 22, 0)
#నిర్వచించు SDL_WL_SEAT_సంస్కరణ 9
#లేదావేళ SDL_WAYLAND_CHECK_సంస్కరణ(1, 21, 0)
#నిర్వచించు SDL_WL_SEAT_సంస్కరణ 8
#లేకపోతే
#నిర్వచించు SDL_WL_SEAT_సంస్కరణ 5
#అయితే_ముగింపు

#ఒకవేళ SDL_WAYLAND_CHECK_సంస్కరణ(1, 20, 0)
#నిర్వచించు SDL_WL_OUTPUT_సంస్కరణ 4
#లేకపోతే
#నిర్వచించు SDL_WL_OUTPUT_సంస్కరణ 3
#అయితే_ముగింపు

#ఒకవేళ SDL_WAYLAND_CHECK_సంస్కరణ(1, 24, 0)
#నిర్వచించు SDL_WL_SHM_సంస్కరణ 2
#లేకపోతే
#నిర్వచించు SDL_WL_SHM_సంస్కరణ 1
#అయితే_ముగింపు

// The SDL libwayland-client minimum is 1.18, which supports version 3.
#నిర్వచించు SDL_WL_దత్తాంశం_DEVICE_సంస్కరణ 3

// wl_fixes was introduced in 1.24.0
#ఒకవేళ SDL_WAYLAND_CHECK_సంస్కరణ(1, 26, 0)
#నిర్వచించు SDL_WL_FIXES_సంస్కరణ 2
#లేదావేళ SDL_WAYLAND_CHECK_సంస్కరణ(1, 24, 0)
#నిర్వచించు SDL_WL_FIXES_సంస్కరణ 1
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_USE_LIBDBUS
#అన్తర్భావ "../../core/linux/SDL_dbus.h"

#నిర్వచించు DISPLAY_INFO_కణుపు   "org.gnome.Mutter.DisplayConfig"
#నిర్వచించు DISPLAY_INFO_మార్గం   "/org/gnome/Mutter/DisplayConfig"
#నిర్వచించు DISPLAY_INFO_పద్ధతి "GetCurrentState"
#అయితే_ముగింపు

/* GNOME doesn't expose displays in any particular order, but we can find the
 * primary display and its logical coordinates via a DBus method.
 */
స్థిర bool Wayland_GetGNOMEPrimaryDisplayCoordinates(పూర్ణాంకం *x, పూర్ణాంకం *y)
{
#నిర్వచితమైతే SDL_USE_LIBDBUS
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    ఒకవేళ (dbus == ఖాళీ) {
        తిరిగి false;
    }
    DBus_సందేశం *జవాబు = ఖాళీ;
    DBus_సందేశం_Iter iter[3];
    DBus_సందేశం *సందేశం_2 = dbus->సందేశం_new_పద్ధతి_call(DISPLAY_INFO_కణుపు,
                                                     DISPLAY_INFO_మార్గం,
                                                     DISPLAY_INFO_కణుపు,
                                                     DISPLAY_INFO_పద్ధతి);

    ఒకవేళ (సందేశం_2) {
        జవాబు = dbus->connection_send_with_జవాబు_and_ఖండం(dbus->session_conn, సందేశం_2, DBUS_TIMEOUT_USE_DEFAULT, ఖాళీ);
        dbus->సందేశం_unref(సందేశం_2);
    }

    ఒకవేళ (జవాబు) {
        // Serial (don't care)
        dbus->సందేశం_iter_init(జవాబు, &iter[0]);
        ఒకవేళ (dbus->సందేశం_iter_get_arg_type(&iter[0]) != DBUS_TYPE_UINT32) {
            వెళ్ళు error;
        }

        // Physical monitor array (don't care)
        dbus->సందేశం_iter_తదుపరి(&iter[0]);
        ఒకవేళ (dbus->సందేశం_iter_get_arg_type(&iter[0]) != DBUS_TYPE_ARRAY) {
            వెళ్ళు error;
        }

        // Logical monitor array of structs
        dbus->సందేశం_iter_తదుపరి(&iter[0]);
        ఒకవేళ (dbus->సందేశం_iter_get_arg_type(&iter[0]) != DBUS_TYPE_ARRAY) {
            వెళ్ళు error;
        }

        // First logical monitor struct
        dbus->సందేశం_iter_recurse(&iter[0], &iter[1]);
        ఒకవేళ (dbus->సందేశం_iter_get_arg_type(&iter[1]) != DBUS_TYPE_STRUCT) {
            వెళ్ళు error;
        }

        చేయి {
            పూర్ణాంకం logical_x, logical_y;
            dbus_bool_t primary;

            // Logical X
            dbus->సందేశం_iter_recurse(&iter[1], &iter[2]);
            ఒకవేళ (dbus->సందేశం_iter_get_arg_type(&iter[2]) != DBUS_TYPE_INT32) {
                వెళ్ళు error;
            }
            dbus->సందేశం_iter_get_basic(&iter[2], &logical_x);

            // Logical Y
            dbus->సందేశం_iter_తదుపరి(&iter[2]);
            ఒకవేళ (dbus->సందేశం_iter_get_arg_type(&iter[2]) != DBUS_TYPE_INT32) {
                వెళ్ళు error;
            }
            dbus->సందేశం_iter_get_basic(&iter[2], &logical_y);

            // Scale (don't care)
            dbus->సందేశం_iter_తదుపరి(&iter[2]);
            ఒకవేళ (dbus->సందేశం_iter_get_arg_type(&iter[2]) != DBUS_TYPE_DOUBLE) {
                వెళ్ళు error;
            }

            // Transform (don't care)
            dbus->సందేశం_iter_తదుపరి(&iter[2]);
            ఒకవేళ (dbus->సందేశం_iter_get_arg_type(&iter[2]) != DBUS_TYPE_UINT32) {
                వెళ్ళు error;
            }

            // Primary display boolean
            dbus->సందేశం_iter_తదుపరి(&iter[2]);
            ఒకవేళ (dbus->సందేశం_iter_get_arg_type(&iter[2]) != DBUS_TYPE_BOOLEAN) {
                వెళ్ళు error;
            }
            dbus->సందేశం_iter_get_basic(&iter[2], &primary);

            ఒకవేళ (primary) {
                *x = logical_x;
                *y = logical_y;

                // We found the primary display: success.
                dbus->సందేశం_unref(జవాబు);
                తిరిగి true;
            }
        } అయితే (dbus->సందేశం_iter_తదుపరి(&iter[1]));
    }

error:
    ఒకవేళ (జవాబు) {
        dbus->సందేశం_unref(జవాబు);
    }
#అయితే_ముగింపు
    తిరిగి false;
}

// Sort the list of displays into a deterministic order
స్థిర పూర్ణాంకం SDLCALL Wayland_DisplayPositionCompare(స్థిరరాశి శూన్య *a, స్థిరరాశి శూన్య *b)
{
    స్థిరరాశి SDL_Display_దత్తాంశం *da = *(SDL_Display_దత్తాంశం **)a;
    స్థిరరాశి SDL_Display_దత్తాంశం *db = *(SDL_Display_దత్తాంశం **)b;
    స్థిరరాశి bool a_at_origin = da->logical.x == 0 && da->logical.y == 0;
    స్థిరరాశి bool b_at_origin = db->logical.x == 0 && db->logical.y == 0;

    // Sort the display at 0,0 to be beginning of the list, as that will be the fallback primary.
    ఒకవేళ (a_at_origin && !b_at_origin) {
        తిరిగి -1;
    }
    ఒకవేళ (b_at_origin && !a_at_origin) {
        తిరిగి 1;
    }

    ఒకవేళ (da->logical.x < db->logical.x) {
        తిరిగి -1;
    }
    ఒకవేళ (da->logical.x > db->logical.x) {
        తిరిగి 1;
    }
    ఒకవేళ (da->logical.y < db->logical.y) {
        తిరిగి -1;
    }
    ఒకవేళ (da->logical.y > db->logical.y) {
        తిరిగి 1;
    }

    // If no position information is available, use the connector name.
    ఒకవేళ (da->wl_output_name && db->wl_output_name) {
        తిరిగి SDL_strcmp(da->wl_output_name, db->wl_output_name);
    }

    తిరిగి 0;
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
స్థిర పూర్ణాంకం Wayland_GetPrimaryDisplay(SDL_Video_దత్తాంశం *vid)
{
    స్థిర స్థిరరాశి పూర్ణాంకం REFRESH_DELTA = 4000;

    // Query the DBus interface to see if the coordinates of the primary display are exposed.
    పూర్ణాంకం x, y;
    ఒకవేళ (Wayland_GetGNOMEPrimaryDisplayCoordinates(&x, &y)) {
        కొరకు (పూర్ణాంకం i = 0; i < vid->output_లెక్క; ++i) {
            ఒకవేళ (vid->output_list[i]->logical.x == x && vid->output_list[i]->logical.y == y) {
                తిరిగి i;
            }
        }
    }

    // Otherwise, choose the 'best' display.
    పూర్ణాంకం ఉత్తమ_వెడల్పు = 0;
    పూర్ణాంకం ఉత్తమ_ఎత్తు = 0;
    ద్విగుణ ఉత్తమ_scale = 0.0;
    దశాంశం ఉత్తమ_headroom = 0.0f;
    పూర్ణాంకం ఉత్తమ_refresh = 0;
    bool ఉత్తమ_is_landscape = false;
    పూర్ణాంకం ఉత్తమ_సూచీ = 0;

    కొరకు (పూర్ణాంకం i = 0; i < vid->output_లెక్క; ++i) {
        స్థిరరాశి SDL_Display_దత్తాంశం *d = vid->output_list[i];
        స్థిరరాశి bool is_landscape = d->orientation != SDL_ORIENTATION_PORTRAIT && d->orientation != SDL_ORIENTATION_PORTRAIT_FLIPPED;
        bool have_new_ఉత్తమ = false;

        ఒకవేళ (!ఉత్తమ_is_landscape && is_landscape) { // Favor landscape over portrait displays.
            have_new_ఉత్తమ = true;
        } లేకపోతే ఒకవేళ (!ఉత్తమ_is_landscape || is_landscape) { // Ignore portrait displays if a landscape was already found.
            ఒకవేళ (d->pixel.వెడల్పు > ఉత్తమ_వెడల్పు || d->pixel.ఎత్తు > ఉత్తమ_ఎత్తు) {
                have_new_ఉత్తమ = true;
            } లేకపోతే ఒకవేళ (d->pixel.వెడల్పు == ఉత్తమ_వెడల్పు && d->pixel.ఎత్తు == ఉత్తమ_ఎత్తు) {
                ఒకవేళ (d->HDR.HDR_headroom > ఉత్తమ_headroom) { // Favor a higher HDR luminance range
                    have_new_ఉత్తమ = true;
                } లేకపోతే ఒకవేళ (d->HDR.HDR_headroom == ఉత్తమ_headroom) {
                    ఒకవేళ (d->refresh - ఉత్తమ_refresh > REFRESH_DELTA) { // Favor a higher refresh rate, but ignore small differences (e.g. 59.97 vs 60.1)
                        have_new_ఉత్తమ = true;
                    } లేకపోతే ఒకవేళ (d->scale_గుణకం_2 < ఉత్తమ_scale && SDL_abs(d->refresh - ఉత్తమ_refresh) <= REFRESH_DELTA) {
                        // Prefer a lower scale display if the difference in refresh rate is small.
                        have_new_ఉత్తమ = true;
                    }
                }
            }
        }

        ఒకవేళ (have_new_ఉత్తమ) {
            ఉత్తమ_వెడల్పు = d->pixel.వెడల్పు;
            ఉత్తమ_ఎత్తు = d->pixel.ఎత్తు;
            ఉత్తమ_scale = d->scale_గుణకం_2;
            ఉత్తమ_headroom = d->HDR.HDR_headroom;
            ఉత్తమ_refresh = d->refresh;
            ఉత్తమ_is_landscape = is_landscape;
            ఉత్తమ_సూచీ = i;
        }
    }

    తిరిగి ఉత్తమ_సూచీ;
}

స్థిర శూన్య Wayland_క్రమీకరించు_Outputs_By_ప్రాధాన్యత_Hint(SDL_Video_దత్తాంశం *vid)
{
    స్థిరరాశి అక్షరం *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_ప్రాధాన్యత);

    ఒకవేళ (name_hint) {
        అక్షరం *saveptr;
        అక్షరం *str = SDL_strdup(name_hint);
        SDL_Display_దత్తాంశం **sorted_list = SDL_malloc(పరిమాణం(SDL_Display_దత్తాంశం *) * vid->output_లెక్క);

        ఒకవేళ (str && sorted_list) {
            పూర్ణాంకం sorted_సూచీ = 0;

            // Sort the requested displays to the front of the list.
            స్థిరరాశి అక్షరం *token = SDL_strtok_r(str, ",", &saveptr);
            అయితే (token) {
                కొరకు (పూర్ణాంకం i = 0; i < vid->output_లెక్క; ++i) {
                    SDL_Display_దత్తాంశం *d = vid->output_list[i];
                    ఒకవేళ (d && d->wl_output_name && SDL_strcmp(token, d->wl_output_name) == 0) {
                        sorted_list[sorted_సూచీ++] = d;
                        vid->output_list[i] = ఖాళీ;
                        ఆపు;
                    }
                }

                token = SDL_strtok_r(ఖాళీ, ",", &saveptr);
            }

            // Append the remaining outputs to the end of the list.
            కొరకు (పూర్ణాంకం i = 0; i < vid->output_లెక్క; ++i) {
                ఒకవేళ (vid->output_list[i]) {
                    sorted_list[sorted_సూచీ++] = vid->output_list[i];
                }
            }

            // Copy the sorted list to the output list.
            SDL_memcpy(vid->output_list, sorted_list, పరిమాణం(SDL_Display_దత్తాంశం *) * vid->output_లెక్క);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

స్థిర శూన్య Wayland_DeriveOutputPixelCoordinates(SDL_Video_దత్తాంశం *vid)
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
    కొరకు ( పూర్ణాంకం i = 0; i < vid->output_లెక్క; ++i) {
        SDL_Display_దత్తాంశం *d = vid->output_list[i];
        d->pixel.x = d->logical.x;
        d->pixel.y = d->logical.y;
    }

    కొరకు (పూర్ణాంకం i = 0; i < vid->output_లెక్క; ++i) {
        SDL_Display_దత్తాంశం *d1 = vid->output_list[i];
        ఒకవేళ (d1->logical.వెడల్పు != d1->pixel.వెడల్పు || d1->logical.ఎత్తు != d1->pixel.ఎత్తు) {
            స్థిరరాశి పూర్ణాంకం x_adj = d1->pixel.వెడల్పు - d1->logical.వెడల్పు;
            స్థిరరాశి పూర్ణాంకం y_adj = d1->pixel.ఎత్తు - d1->logical.ఎత్తు;

            // Don't adjust for scale values less than 1.0.
            ఒకవేళ (x_adj > 0 && y_adj > 0) {
                కొరకు (పూర్ణాంకం j = 0; j < vid->output_లెక్క; ++j) {
                    SDL_Display_దత్తాంశం *d2 = vid->output_list[j];
                    ఒకవేళ (d2->logical.x > d1->logical.x) {
                        d2->pixel.x += x_adj;
                    }
                    ఒకవేళ (d2->logical.y > d1->logical.y) {
                        d2->pixel.y += y_adj;
                    }
                }
            }
        }
    }
}

స్థిర శూన్య Wayland_క్రమీకరించు_Outputs(SDL_Video_దత్తాంశం *vid)
{
    // Sort by position or connector name, so the order of outputs is deterministic.
    SDL_qsort(vid->output_list, vid->output_లెక్క, పరిమాణం(SDL_Display_దత్తాంశం *), Wayland_DisplayPositionCompare);

    // Derive the output pixel coordinates if scale to display is enabled.
    ఒకవేళ (vid->scale_గమ్యం_display_enabled) {
        Wayland_DeriveOutputPixelCoordinates(vid);
    }

    // Find a suitable primary display and move it to the front of the list.
    స్థిరరాశి పూర్ణాంకం primary_సూచీ = Wayland_GetPrimaryDisplay(vid);
    ఒకవేళ (primary_సూచీ) {
        SDL_Display_దత్తాంశం *primary = vid->output_list[primary_సూచీ];
        SDL_memmove(&vid->output_list[1], &vid->output_list[0], పరిమాణం(SDL_Display_దత్తాంశం *) * primary_సూచీ);
        vid->output_list[0] = primary;
    }

    // Apply the ordering hint, if specified.
    Wayland_క్రమీకరించు_Outputs_By_ప్రాధాన్యత_Hint(vid);
}

స్థిర శూన్య Wayland_Refresh_కిటికీ_Positions()
{
    SDL_VideoDevice *vid = SDL_GetVideoDevice();

    కొరకు (SDL_కిటికీ *w = vid->windows; w; w = w->తదుపరి) {
        Wayland_Update_కిటికీ_Position(w);
    }
}

స్థిర శూన్య handle_wl_output_పూర్తి(శూన్య *దత్తాంశం, నిర్మాణం wl_output *output);

// Initialization/Query functions
స్థిర bool Wayland_VideoInit(SDL_VideoDevice *_this);
స్థిర bool Wayland_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
స్థిర శూన్య Wayland_VideoQuit(SDL_VideoDevice *_this);

స్థిర స్థిరరాశి అక్షరం *SDL_WAYLAND_surface_ట్యాగ్ = "sdl-window";
స్థిర స్థిరరాశి అక్షరం *SDL_WAYLAND_output_ట్యాగ్ = "sdl-output";

శూన్య SDL_WAYLAND_రిజిస్టరు_surface(నిర్మాణం wl_surface *surface)
{
    wl_proxy_సమితి_ట్యాగ్((నిర్మాణం wl_proxy *)surface, &SDL_WAYLAND_surface_ట్యాగ్);
}

శూన్య SDL_WAYLAND_రిజిస్టరు_output(నిర్మాణం wl_output *output)
{
    wl_proxy_సమితి_ట్యాగ్((నిర్మాణం wl_proxy *)output, &SDL_WAYLAND_output_ట్యాగ్);
}

bool SDL_WAYLAND_own_surface(నిర్మాణం wl_surface *surface)
{
    తిరిగి wl_proxy_get_ట్యాగ్((నిర్మాణం wl_proxy *)surface) == &SDL_WAYLAND_surface_ట్యాగ్;
}

bool SDL_WAYLAND_own_output(నిర్మాణం wl_output *output)
{
    తిరిగి wl_proxy_get_ట్యాగ్((నిర్మాణం wl_proxy *)output) == &SDL_WAYLAND_output_ట్యాగ్;
}

/* External surfaces may have their own user data attached, the modification of which
 * can cause problems with external toolkits. Instead, external windows are kept in
 * their own list, and a search is conducted to find a matching surface.
 */
స్థిర నిర్మాణం wl_list external_కిటికీ_list;

శూన్య Wayland_కూడు_కిటికీ_దత్తాంశం_గమ్యం_External_List(SDL_కిటికీ_దత్తాంశం *దత్తాంశం)
{
    WAYLAND_wl_list_చొప్పించు(&external_కిటికీ_list, &దత్తాంశం->external_కిటికీ_list_link);
}

శూన్య Wayland_Remove_కిటికీ_దత్తాంశం_From_External_List(SDL_కిటికీ_దత్తాంశం *దత్తాంశం)
{
    WAYLAND_wl_list_remove(&దత్తాంశం->external_కిటికీ_list_link);
}

SDL_కిటికీ_దత్తాంశం *Wayland_Get_కిటికీ_దత్తాంశం_For_Owned_Surface(నిర్మాణం wl_surface *surface)
{
    ఒకవేళ (SDL_WAYLAND_own_surface(surface)) {
        తిరిగి (SDL_కిటికీ_దత్తాంశం *)wl_surface_get_user_దత్తాంశం(surface);
    } లేకపోతే ఒకవేళ (!WAYLAND_wl_list_ఖాళీలు(&external_కిటికీ_list)) {
        SDL_కిటికీ_దత్తాంశం *p;
        wl_list_for_each (p, &external_కిటికీ_list, external_కిటికీ_list_link) {
            ఒకవేళ (p->surface == surface) {
                తిరిగి p;
            }
        }
    }

    తిరిగి ఖాళీ;
}

నిర్మాణం wl_event_వరుస *Wayland_Display_Create_వరుస(నిర్మాణం wl_display *display, స్థిరరాశి అక్షరం *name)
{
#నిర్వచితమైతే SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
    ఒకవేళ (WAYLAND_wl_display_create_వరుస_with_name) {
        తిరిగి WAYLAND_wl_display_create_వరుస_with_name(display, name);
    }
#లేదావేళ SDL_WAYLAND_CHECK_సంస్కరణ(1, 23, 0)
    తిరిగి WAYLAND_wl_display_create_వరుస_with_name(display, name);
#అయితే_ముగింపు
    తిరిగి WAYLAND_wl_display_create_వరుస(display);
}

స్థిర శూన్య Wayland_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = device->అంతర్గత;
    ఒకవేళ (దత్తాంశం->display && !దత్తాంశం->display_externally_owned) {
        WAYLAND_wl_display_disconnect(దత్తాంశం->display);
        SDL_ClearProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_సూచిక);
    }
    SDL_free(దత్తాంశం);
    SDL_free(device);
    SDL_WAYLAND_UnloadSymbols();
}

రకనిర్వచనం నిర్మాణం
{
    bool has_fifo_v1;
    నిర్మాణం wl_fixes *wl_fixes;
} SDL_Wayland_Preferred_దత్తాంశం;

స్థిర శూన్య wayland_preferred_check_handle_global(శూన్య *దత్తాంశం, నిర్మాణం wl_registry *registry, uint32_t id,
                                                  స్థిరరాశి అక్షరం *interface, uint32_t సంస్కరణ)
{
    SDL_Wayland_Preferred_దత్తాంశం *d = దత్తాంశం;

    ఒకవేళ (SDL_strcmp(interface, "wp_fifo_manager_v1") == 0) {
        d->has_fifo_v1 = true;
    }
#నిర్వచితమైతే SDL_WL_FIXES_సంస్కరణ
    లేకపోతే ఒకవేళ (SDL_strcmp(interface, wl_fixes_interface.name) == 0) {
        d->wl_fixes = wl_registry_bind(registry, id, &wl_fixes_interface, SDL_min(SDL_WL_FIXES_సంస్కరణ, సంస్కరణ));
    }
#అయితే_ముగింపు
}

స్థిర శూన్య wayland_preferred_check_remove_global(శూన్య *దత్తాంశం, నిర్మాణం wl_registry *registry, uint32_t id)
{
    SDL_Wayland_Preferred_దత్తాంశం *d = (SDL_Wayland_Preferred_దత్తాంశం *)దత్తాంశం;

    ఒకవేళ (d->wl_fixes && wl_fixes_get_సంస్కరణ(d->wl_fixes) >= WL_FIXES_ACK_GLOBAL_REMOVE_SINCE_సంస్కరణ) {
        wl_fixes_ack_global_remove(d->wl_fixes, registry, id);
    }
}

స్థిర స్థిరరాశి నిర్మాణం wl_registry_listener preferred_registry_listener = {
    wayland_preferred_check_handle_global,
    wayland_preferred_check_remove_global
};

స్థిర bool Wayland_IsPreferred(నిర్మాణం wl_display *display)
{
    నిర్మాణం wl_registry *registry = wl_display_get_registry(display);
    SDL_Wayland_Preferred_దత్తాంశం preferred_దత్తాంశం = { 0 };

    ఒకవేళ (!registry) {
        SDL_సమితి_Error("Failed to get the Wayland registry");
        తిరిగి false;
    }

    wl_registry_కూడు_listener(registry, &preferred_registry_listener, &preferred_దత్తాంశం);

    WAYLAND_wl_display_roundtrip(display);

    ఒకవేళ (preferred_దత్తాంశం.wl_fixes) {
        wl_fixes_destroy_registry(preferred_దత్తాంశం.wl_fixes, registry);
        wl_fixes_destroy(preferred_దత్తాంశం.wl_fixes);
    }
    wl_registry_destroy(registry);

    ఒకవేళ (!preferred_దత్తాంశం.has_fifo_v1) {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "This compositor lacks support for the fifo-v1 protocol; falling back to XWayland for GPU performance reasons (set SDL_VIDEO_DRIVER=wayland to override)");
    }
    తిరిగి preferred_దత్తాంశం.has_fifo_v1;
}

స్థిర SDL_VideoDevice *Wayland_CreateDevice(bool require_preferred_protocols)
{
    SDL_VideoDevice *device;
    SDL_Video_దత్తాంశం *దత్తాంశం;
    నిర్మాణం wl_display *display = SDL_Get_సూచిక_Property(SDL_GetGlobalProperties(),
                                                 SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_సూచిక, ఖాళీ);
    bool display_is_external = !!display;

    // Are we trying to connect to, or are currently in, a Wayland session?
    ఒకవేళ (!SDL_getenv("WAYLAND_DISPLAY")) {
        స్థిరరాశి అక్షరం *session = SDL_getenv("XDG_SESSION_TYPE");
        ఒకవేళ (session && SDL_strcasecmp(session, "wayland") != 0) {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Wayland initialization failed: no Wayland session available");
            తిరిగి ఖాళీ;
        }
    }

    ఒకవేళ (!SDL_WAYLAND_ఎక్కించు_Symbols()) {
        తిరిగి ఖాళీ;
    }

    ఒకవేళ (!display) {
        display = WAYLAND_wl_display_connect(ఖాళీ);
        ఒకవేళ (!display) {
            SDL_WAYLAND_UnloadSymbols();
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to connect to the Wayland display server: %s", strerror(errno));
            తిరిగి ఖాళీ;
        }
    }

    /*
     * If we are checking for preferred Wayland, then let's query for
     * fifo-v1's existence, so we don't regress GPU-bound performance
     * and frame-pacing by default due to swapchain starvation.
     */
    ఒకవేళ (require_preferred_protocols && !Wayland_IsPreferred(display)) {
        ఒకవేళ (!display_is_external) {
            WAYLAND_wl_display_disconnect(display);
        }
        SDL_WAYLAND_UnloadSymbols();
        తిరిగి ఖాళీ;
    }

    దత్తాంశం = SDL_calloc(1, పరిమాణం(*దత్తాంశం));
    ఒకవేళ (!దత్తాంశం) {
        ఒకవేళ (!display_is_external) {
            WAYLAND_wl_display_disconnect(display);
        }
        SDL_WAYLAND_UnloadSymbols();
        తిరిగి ఖాళీ;
    }

    దత్తాంశం->initializing = true;
    దత్తాంశం->display = display;
    దత్తాంశం->display_externally_owned = display_is_external;
    దత్తాంశం->scale_గమ్యం_display_enabled = SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_SCALE_గమ్యం_DISPLAY, false);
    WAYLAND_wl_list_init(&దత్తాంశం->seat_list);
    WAYLAND_wl_list_init(&external_కిటికీ_list);

    // Initialize all variables that we clean on shutdown
    device = SDL_calloc(1, పరిమాణం(SDL_VideoDevice));
    ఒకవేళ (!device) {
        SDL_free(దత్తాంశం);
        ఒకవేళ (!display_is_external) {
            WAYLAND_wl_display_disconnect(display);
        }
        SDL_WAYLAND_UnloadSymbols();
        తిరిగి ఖాళీ;
    }

    ఒకవేళ (!display_is_external) {
        SDL_సమితి_సూచిక_Property(SDL_GetGlobalProperties(),
                               SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_సూచిక, display);
    }

    device->అంతర్గత = దత్తాంశం;

    // Set the function pointers
    device->VideoInit = Wayland_VideoInit;
    device->VideoQuit = Wayland_VideoQuit;
    device->GetDisplayBounds = Wayland_GetDisplayBounds;
    device->SuspendScreenSaver = Wayland_SuspendScreenSaver;

    device->PumpEvents = Wayland_PumpEvents;
    device->WaitEventTimeout = Wayland_WaitEventTimeout;
    device->SendWakeupEvent = Wayland_SendWakeupEvent;

#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
    device->GL_మార్పిడి_కిటికీ = Wayland_GLES_మార్పిడి_కిటికీ;
    device->GL_Get_మార్పిడి_Interval = Wayland_GLES_Get_మార్పిడి_Interval;
    device->GL_సమితి_మార్పిడి_Interval = Wayland_GLES_సమితి_మార్పిడి_Interval;
    device->GL_MakeCurrent = Wayland_GLES_MakeCurrent;
    device->GL_CreateContext = Wayland_GLES_CreateContext;
    device->GL_ఎక్కించు_Library = Wayland_GLES_ఎక్కించు_Library;
    device->GL_UnloadLibrary = Wayland_GLES_UnloadLibrary;
    device->GL_Get_Proc_చిరునామా = Wayland_GLES_Get_Proc_చిరునామా;
    device->GL_DestroyContext = Wayland_GLES_DestroyContext;
    device->GL_సమితి_Default_Profile_Config = Wayland_GLES_సమితి_Default_Profile_Config;
    device->GL_GetEGLSurface = Wayland_GLES_GetEGLSurface;
#అయితే_ముగింపు

    device->CreateSDLWindow = Wayland_Create_కిటికీ;
    device->Show_కిటికీ = Wayland_Show_కిటికీ;
    device->Hide_కిటికీ = Wayland_Hide_కిటికీ;
    device->Raise_కిటికీ = Wayland_Raise_కిటికీ;
    device->సమితి_కిటికీ_Fullscreen = Wayland_సమితి_కిటికీ_Fullscreen;
    device->Maximize_కిటికీ = Wayland_Maximize_కిటికీ;
    device->Minimize_కిటికీ = Wayland_Minimize_కిటికీ;
    device->సమితి_కిటికీ_Mouse_Rect = Wayland_సమితి_కిటికీ_Mouse_Rect;
    device->సమితి_కిటికీ_Mouse_Grab = Wayland_సమితి_కిటికీ_Mouse_Grab;
    device->సమితి_కిటికీ_Keyboard_Grab = Wayland_సమితి_కిటికీ_Keyboard_Grab;
    device->Restore_కిటికీ = Wayland_Restore_కిటికీ;
    device->సమితి_కిటికీ_Bordered = Wayland_సమితి_కిటికీ_Bordered;
    device->సమితి_కిటికీ_Resizable = Wayland_సమితి_కిటికీ_Resizable;
    device->సమితి_కిటికీ_Position = Wayland_సమితి_కిటికీ_Position;
    device->సమితి_కిటికీ_కొలత = Wayland_సమితి_కిటికీ_కొలత;
    device->సమితి_కిటికీ_Aspect_నిష్పత్తి = Wayland_సమితి_కిటికీ_Aspect_నిష్పత్తి;
    device->సమితి_కిటికీ_Minimum_కొలత = Wayland_సమితి_కిటికీ_Minimum_కొలత;
    device->సమితి_కిటికీ_గరిష్ఠ_కొలత = Wayland_సమితి_కిటికీ_గరిష్ఠ_కొలత;
    device->సమితి_కిటికీ_మాతృ = Wayland_సమితి_కిటికీ_మాతృ;
    device->సమితి_కిటికీ_Modal = Wayland_సమితి_కిటికీ_Modal;
    device->సమితి_కిటికీ_Opacity = Wayland_సమితి_కిటికీ_Opacity;
    device->సమితి_కిటికీ_Title = Wayland_సమితి_కిటికీ_Title;
    device->సమితి_కిటికీ_Icon = Wayland_సమితి_కిటికీ_Icon;
    device->Get_కిటికీ_కొలత_లోపల_Pixels = Wayland_Get_కిటికీ_కొలత_లోపల_Pixels;
    device->Get_కిటికీ_Content_Scale = Wayland_Get_కిటికీ_Content_Scale;
    device->Get_కిటికీ_ICCProfile = Wayland_Get_కిటికీ_ICCProfile;
    device->Get_Display_For_కిటికీ = Wayland_Get_Display_For_కిటికీ;
    device->Destroy_కిటికీ = Wayland_Destroy_కిటికీ;
    device->సమితి_కిటికీ_తగిలింది_Test = Wayland_సమితి_కిటికీ_తగిలింది_Test;
    device->Flash_కిటికీ = Wayland_Flash_కిటికీ;
#నిర్వచితమైతే SDL_USE_LIBDBUS
    device->Apply_కిటికీ_పురోగతి = DBUS_Apply_కిటికీ_పురోగతి;
#అయితే_ముగింపు // SDL_USE_LIBDBUS
    device->HasScreenKeyboardSupport = Wayland_HasScreenKeyboardSupport;
    device->Show_కిటికీ_System_Menu = Wayland_Show_కిటికీ_System_Menu;
    device->Sync_కిటికీ = Wayland_Sync_కిటికీ;
    device->సమితి_కిటికీ_Focusable = Wayland_సమితి_కిటికీ_Focusable;
    device->Reconfigure_కిటికీ = Wayland_Reconfigure_కిటికీ;
    device->AcceptDragAndDrop = Wayland_AcceptDragAndDrop;

#నిర్వచితమైతే SDL_USE_LIBDBUS
    ఒకవేళ (SDL_SystemTheme_Init())
        device->system_theme = SDL_SystemTheme_Get();
#అయితే_ముగింపు

    device->Get_పాఠ్యం_Mime_Types = Wayland_Get_పాఠ్యం_Mime_Types;
    device->సమితి_Clipboard_దత్తాంశం = Wayland_సమితి_Clipboard_దత్తాంశం;
    device->Get_Clipboard_దత్తాంశం = Wayland_Get_Clipboard_దత్తాంశం;
    device->Has_Clipboard_దత్తాంశం = Wayland_Has_Clipboard_దత్తాంశం;
    device->ప్రారంభం_పాఠ్యం_ఆదానం = Wayland_ప్రారంభం_పాఠ్యం_ఆదానం;
    device->Stop_పాఠ్యం_ఆదానం = Wayland_Stop_పాఠ్యం_ఆదానం;
    device->Update_పాఠ్యం_ఆదానం_Area = Wayland_Update_పాఠ్యం_ఆదానం_Area;

#నిర్వచితమైతే SDL_VIDEO_VULKAN
    device->Vulkan_ఎక్కించు_Library = Wayland_Vulkan_ఎక్కించు_Library;
    device->Vulkan_UnloadLibrary = Wayland_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = Wayland_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = Wayland_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = Wayland_Vulkan_DestroySurface;
    device->Vulkan_GetPresentationSupport = Wayland_Vulkan_GetPresentationSupport;
#అయితే_ముగింపు

    device->విడుదల = Wayland_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_బహుళకం_SWITCHING_EMULATED |
                          VIDEO_DEVICE_CAPS_HAS_POPUP_కిటికీ_SUPPORT |
                          VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS |
                          VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES |
                          VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES;

    తిరిగి device;
}

స్థిర SDL_VideoDevice *Wayland_Preferred_CreateDevice(శూన్య)
{
    తిరిగి Wayland_CreateDevice(true);
}

స్థిర SDL_VideoDevice *Wayland_Fallback_CreateDevice(శూన్య)
{
    తిరిగి Wayland_CreateDevice(false);
}

VideoBootStrap Wayland_preferred_bootstrap = {
    WAYLANDVID_DRIVER_NAME, "SDL Wayland video driver",
    Wayland_Preferred_CreateDevice,
    Wayland_Show_సందేశం_Box,
    true
};

VideoBootStrap Wayland_bootstrap = {
    WAYLANDVID_DRIVER_NAME, "SDL Wayland video driver",
    Wayland_Fallback_CreateDevice,
    Wayland_Show_సందేశం_Box,
    false
};

స్థిర శూన్య handle_xdg_output_logical_position(శూన్య *దత్తాంశం, నిర్మాణం zxdg_output_v1 *xdg_output, int32_t x, int32_t y)
{
    SDL_Display_దత్తాంశం *అంతర్గత = (SDL_Display_దత్తాంశం *)దత్తాంశం;

    అంతర్గత->geometry_మారింది |= అంతర్గత->logical.x != x || అంతర్గత->logical.y != y;
    అంతర్గత->logical.x = x;
    అంతర్గత->logical.y = y;
    అంతర్గత->has_logical_position = true;
}

స్థిర శూన్య handle_xdg_output_logical_కొలత(శూన్య *దత్తాంశం, నిర్మాణం zxdg_output_v1 *xdg_output, int32_t వెడల్పు, int32_t ఎత్తు)
{
    SDL_Display_దత్తాంశం *అంతర్గత = (SDL_Display_దత్తాంశం *)దత్తాంశం;

    అంతర్గత->geometry_మారింది |= అంతర్గత->logical.వెడల్పు != వెడల్పు || అంతర్గత->logical.ఎత్తు != ఎత్తు;
    అంతర్గత->logical.వెడల్పు = వెడల్పు;
    అంతర్గత->logical.ఎత్తు = ఎత్తు;
    అంతర్గత->has_logical_కొలత = true;
}

స్థిర శూన్య handle_xdg_output_పూర్తి(శూన్య *దత్తాంశం, నిర్మాణం zxdg_output_v1 *xdg_output)
{
    SDL_Display_దత్తాంశం *అంతర్గత = దత్తాంశం;

    /*
     * xdg-output.done events are deprecated and only apply below version 3 of the protocol.
     * A wl-output.done event will be emitted in version 3 or higher.
     */
    ఒకవేళ (zxdg_output_v1_get_సంస్కరణ(అంతర్గత->xdg_output) < 3) {
        handle_wl_output_పూర్తి(దత్తాంశం, అంతర్గత->output);
    }
}

స్థిర శూన్య handle_xdg_output_name(శూన్య *దత్తాంశం, నిర్మాణం zxdg_output_v1 *xdg_output, స్థిరరాశి అక్షరం *name)
{
    SDL_Display_దత్తాంశం *అంతర్గత = (SDL_Display_దత్తాంశం *)దత్తాంశం;

    // Deprecated as of wl_output v4.
    ఒకవేళ (wl_output_get_సంస్కరణ(అంతర్గత->output) < WL_OUTPUT_NAME_SINCE_సంస్కరణ &&
        అంతర్గత->display == 0) {
        SDL_free(అంతర్గత->wl_output_name);
        అంతర్గత->wl_output_name = SDL_strdup(name);
    }
}

స్థిర శూన్య handle_xdg_output_description(శూన్య *దత్తాంశం, నిర్మాణం zxdg_output_v1 *xdg_output, స్థిరరాశి అక్షరం *description)
{
    SDL_Display_దత్తాంశం *అంతర్గత = (SDL_Display_దత్తాంశం *)దత్తాంశం;

    // Deprecated as of wl_output v4.
    ఒకవేళ (wl_output_get_సంస్కరణ(అంతర్గత->output) < WL_OUTPUT_DESCRIPTION_SINCE_సంస్కరణ &&
        అంతర్గత->display == 0) {
        // xdg-output descriptions, if available, supersede wl-output model names.
        SDL_free(అంతర్గత->placeholder.name);
        అంతర్గత->placeholder.name = SDL_strdup(description);
    }
}

స్థిర స్థిరరాశి నిర్మాణం zxdg_output_v1_listener xdg_output_listener = {
    handle_xdg_output_logical_position,
    handle_xdg_output_logical_కొలత,
    handle_xdg_output_పూర్తి,
    handle_xdg_output_name,
    handle_xdg_output_description,
};

స్థిర శూన్య కూడు_Emulated_Modes(SDL_Display_దత్తాంశం *dispdata, పూర్ణాంకం native_వెడల్పు, పూర్ణాంకం native_ఎత్తు)
{
    నిర్మాణం Emulated_బహుళకం
    {
        పూర్ణాంకం w;
        పూర్ణాంకం h;
    };

    // Resolution lists courtesy of XWayland
    స్థిరరాశి నిర్మాణం Emulated_బహుళకం బహుళకం_list[] = {
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

    పూర్ణాంకం i;
    SDL_Display_బహుళకం బహుళకం;
    SDL_VideoDisplay *dpy = dispdata->display ? SDL_GetVideoDisplay(dispdata->display) : &dispdata->placeholder;
    స్థిరరాశి bool rot_90 = native_వెడల్పు < native_ఎత్తు; // Reverse width/height for portrait displays.

    కొరకు (i = 0; i < SDL_arraysize(బహుళకం_list); ++i) {
        SDL_zero(బహుళకం);
        బహుళకం.format = dpy->desktop_బహుళకం.format;
        బహుళకం.refresh_రేటు_numerator = dpy->desktop_బహుళకం.refresh_రేటు_numerator;
        బహుళకం.refresh_రేటు_denominator = dpy->desktop_బహుళకం.refresh_రేటు_denominator;

        ఒకవేళ (rot_90) {
            బహుళకం.w = బహుళకం_list[i].h;
            బహుళకం.h = బహుళకం_list[i].w;
        } లేకపోతే {
            బహుళకం.w = బహుళకం_list[i].w;
            బహుళకం.h = బహుళకం_list[i].h;
        }

        // Only add modes that are smaller than the native mode.
        ఒకవేళ ((బహుళకం.w < native_వెడల్పు && బహుళకం.h < native_ఎత్తు) ||
            (బహుళకం.w < native_వెడల్పు && బహుళకం.h == native_ఎత్తు) ||
            (బహుళకం.w == native_వెడల్పు && బహుళకం.h < native_ఎత్తు)) {
            SDL_కూడు_Fullscreen_Display_బహుళకం(dpy, &బహుళకం);
        }
    }
}

స్థిర శూన్య handle_wl_output_geometry(శూన్య *దత్తాంశం, నిర్మాణం wl_output *output, పూర్ణాంకం x, పూర్ణాంకం y,
                                      పూర్ణాంకం physical_వెడల్పు_2, పూర్ణాంకం physical_ఎత్తు_2, పూర్ణాంకం subpixel,
                                      స్థిరరాశి అక్షరం *make, స్థిరరాశి అక్షరం *model, పూర్ణాంకం transform)
{
    SDL_Display_దత్తాంశం *అంతర్గత = (SDL_Display_దత్తాంశం *)దత్తాంశం;

    // Apply the change from wl-output only if xdg-output is not supported
    ఒకవేళ (!అంతర్గత->has_logical_position) {
        అంతర్గత->geometry_మారింది |= అంతర్గత->logical.x != x || అంతర్గత->logical.y != y;
        అంతర్గత->logical.x = x;
        అంతర్గత->logical.y = y;
    }
    అంతర్గత->physical.వెడల్పు_mm = physical_వెడల్పు_2;
    అంతర్గత->physical.ఎత్తు_mm = physical_ఎత్తు_2;

    // The model is only used for the output name if wl_output or xdg-output haven't provided a description.
    ఒకవేళ (అంతర్గత->display == 0 && !అంతర్గత->placeholder.name) {
        అంతర్గత->placeholder.name = SDL_strdup(model);
    }

    అంతర్గత->transform = transform;
#నిర్వచించు TF_CASE(లోపల_2, బహిర్గతం)                                 \
    స్థితి WL_OUTPUT_TRANSFORM_##in:                       \
        అంతర్గత->orientation = SDL_ORIENTATION_##out; \
        ఆపు;
    ఒకవేళ (అంతర్గత->physical.వెడల్పు_mm >= అంతర్గత->physical.ఎత్తు_mm) {
        ఎంపిక (transform) {
            TF_CASE(సాధారణ_2, LANDSCAPE)
            TF_CASE(90, PORTRAIT)
            TF_CASE(180, LANDSCAPE_FLIPPED)
            TF_CASE(270, PORTRAIT_FLIPPED)
            TF_CASE(FLIPPED, LANDSCAPE_FLIPPED)
            TF_CASE(FLIPPED_90, PORTRAIT_FLIPPED)
            TF_CASE(FLIPPED_180, LANDSCAPE)
            TF_CASE(FLIPPED_270, PORTRAIT)
        }
    } లేకపోతే {
        ఎంపిక (transform) {
            TF_CASE(సాధారణ_2, PORTRAIT)
            TF_CASE(90, LANDSCAPE)
            TF_CASE(180, PORTRAIT_FLIPPED)
            TF_CASE(270, LANDSCAPE_FLIPPED)
            TF_CASE(FLIPPED, PORTRAIT_FLIPPED)
            TF_CASE(FLIPPED_90, LANDSCAPE_FLIPPED)
            TF_CASE(FLIPPED_180, PORTRAIT)
            TF_CASE(FLIPPED_270, LANDSCAPE)
        }
    }
#నిర్వచనం_రద్దు TF_CASE
}

స్థిర శూన్య handle_wl_output_బహుళకం(శూన్య *దత్తాంశం, నిర్మాణం wl_output *output, uint32_t flags,
                                  పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, పూర్ణాంకం refresh)
{
    SDL_Display_దత్తాంశం *అంతర్గత = (SDL_Display_దత్తాంశం *)దత్తాంశం;

    ఒకవేళ (flags & WL_OUTPUT_బహుళకం_CURRENT) {
        అంతర్గత->geometry_మారింది |= అంతర్గత->pixel.వెడల్పు != వెడల్పు || అంతర్గత->pixel.ఎత్తు != ఎత్తు;
        అంతర్గత->pixel.వెడల్పు = వెడల్పు;
        అంతర్గత->pixel.ఎత్తు = ఎత్తు;

        /*
         * Don't rotate this yet, wl-output coordinates are transformed in
         * handle_done and xdg-output coordinates are pre-transformed.
         */
        ఒకవేళ (!అంతర్గత->has_logical_కొలత) {
            అంతర్గత->geometry_మారింది |= అంతర్గత->logical.వెడల్పు != వెడల్పు || అంతర్గత->logical.ఎత్తు != ఎత్తు;
            అంతర్గత->logical.వెడల్పు = వెడల్పు;
            అంతర్గత->logical.ఎత్తు = ఎత్తు;
        }

        అంతర్గత->refresh = refresh;
    }
}

స్థిర శూన్య handle_wl_output_పూర్తి(శూన్య *దత్తాంశం, నిర్మాణం wl_output *output)
{
    స్థిరరాశి bool బహుళకం_emulation_enabled = SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_బహుళకం_EMULATION, true);
    SDL_Display_దత్తాంశం *అంతర్గత = (SDL_Display_దత్తాంశం *)దత్తాంశం;
    SDL_Video_దత్తాంశం *video = అంతర్గత->videodata;
    SDL_Display_బహుళకం native_బహుళకం, desktop_బహుళకం;

    /*
     * When using xdg-output, two wl-output.done events will be emitted:
     * one at the completion of wl-display and one at the completion of xdg-output.
     *
     * All required events must be received before proceeding.
     */
    స్థిరరాశి పూర్ణాంకం event_await_లెక్క = 1 + (అంతర్గత->xdg_output != ఖాళీ);

    అంతర్గత->wl_output_పూర్తి_లెక్క = SDL_min(అంతర్గత->wl_output_పూర్తి_లెక్క + 1, event_await_లెక్క + 1);

    ఒకవేళ (అంతర్గత->wl_output_పూర్తి_లెక్క < event_await_లెక్క) {
        తిరిగి;
    }

    // If the display was already created, reset and rebuild the mode list.
    SDL_VideoDisplay *dpy = SDL_GetVideoDisplay(అంతర్గత->display);
    ఒకవేళ (dpy) {
        SDL_ResetFullscreenDisplayModes(dpy);
    }

    // The native display resolution
    SDL_zero(native_బహుళకం);
    native_బహుళకం.format = SDL_PIXELFORMAT_XRGB8888;

    // Transform the pixel values, if necessary.
    ఒకవేళ (అంతర్గత->transform & WL_OUTPUT_TRANSFORM_90) {
        native_బహుళకం.w = అంతర్గత->pixel.ఎత్తు;
        native_బహుళకం.h = అంతర్గత->pixel.వెడల్పు;
    } లేకపోతే {
        native_బహుళకం.w = అంతర్గత->pixel.వెడల్పు;
        native_బహుళకం.h = అంతర్గత->pixel.ఎత్తు;
    }
    native_బహుళకం.refresh_రేటు_numerator = అంతర్గత->refresh;
    native_బహుళకం.refresh_రేటు_denominator = 1000;

    ఒకవేళ (అంతర్గత->has_logical_కొలత) { // If xdg-output is present...
        ఒకవేళ (native_బహుళకం.w != అంతర్గత->logical.వెడల్పు || native_బహుళకం.h != అంతర్గత->logical.ఎత్తు) {
            // ...and the compositor scales the logical viewport...
            ఒకవేళ (video->viewporter) {
                // ...and viewports are supported, calculate the true scale of the output.
                అంతర్గత->scale_గుణకం_2 = (ద్విగుణ)native_బహుళకం.w / (ద్విగుణ)అంతర్గత->logical.వెడల్పు;
            } లేకపోతే {
                // ...otherwise, the 'native' pixel values are a multiple of the logical screen size.
                అంతర్గత->scale_గుణకం_2 = అంతర్గత->integer_scale_గుణకం;
                అంతర్గత->pixel.వెడల్పు = అంతర్గత->logical.వెడల్పు * అంతర్గత->integer_scale_గుణకం;
                అంతర్గత->pixel.ఎత్తు = అంతర్గత->logical.ఎత్తు * అంతర్గత->integer_scale_గుణకం;
            }
        } లేకపోతే {
            /* ...and the output viewport is not scaled in the global compositing
             * space, the output dimensions need to be divided by the scale factor.
             *
             * NOTE: This path is needed for old versions of GNOME that predate fractional scaling.
             */
            అంతర్గత->scale_గుణకం_2 = అంతర్గత->integer_scale_గుణకం;
            అంతర్గత->logical.వెడల్పు /= అంతర్గత->integer_scale_గుణకం;
            అంతర్గత->logical.ఎత్తు /= అంతర్గత->integer_scale_గుణకం;
        }
    } లేకపోతే {
        /* Calculate the points from the pixel values, if xdg-output isn't present.
         * Use the native mode pixel values since they are pre-transformed.
         */
        అంతర్గత->scale_గుణకం_2 = అంతర్గత->integer_scale_గుణకం;
        అంతర్గత->logical.వెడల్పు = native_బహుళకం.w / అంతర్గత->integer_scale_గుణకం;
        అంతర్గత->logical.ఎత్తు = native_బహుళకం.h / అంతర్గత->integer_scale_గుణకం;
    }

    // The scaled desktop mode
    SDL_zero(desktop_బహుళకం);
    desktop_బహుళకం.format = SDL_PIXELFORMAT_XRGB8888;

    ఒకవేళ (!video->scale_గమ్యం_display_enabled) {
        desktop_బహుళకం.w = అంతర్గత->logical.వెడల్పు;
        desktop_బహుళకం.h = అంతర్గత->logical.ఎత్తు;
        desktop_బహుళకం.pixel_density = (దశాంశం)అంతర్గత->scale_గుణకం_2;
    } లేకపోతే {
        desktop_బహుళకం.w = native_బహుళకం.w;
        desktop_బహుళకం.h = native_బహుళకం.h;
        desktop_బహుళకం.pixel_density = 1.0f;
    }

    desktop_బహుళకం.refresh_రేటు_numerator = అంతర్గత->refresh;
    desktop_బహుళకం.refresh_రేటు_denominator = 1000;

    ఒకవేళ (అంతర్గత->display > 0) {
        dpy = SDL_GetVideoDisplay(అంతర్గత->display);
    } లేకపోతే {
        dpy = &అంతర్గత->placeholder;
    }

    ఒకవేళ (video->scale_గమ్యం_display_enabled) {
        SDL_సమితి_Display_Content_Scale(dpy, (దశాంశం)అంతర్గత->scale_గుణకం_2);
    }

    // Set the desktop display mode.
    SDL_సమితి_Desktop_Display_బహుళకం(dpy, &desktop_బహుళకం);

    // Expose the unscaled, native resolution if the scale is 1.0 or viewports are available...
    ఒకవేళ (అంతర్గత->scale_గుణకం_2 == 1.0 || video->viewporter) {
        SDL_కూడు_Fullscreen_Display_బహుళకం(dpy, &native_బహుళకం);
        ఒకవేళ (native_బహుళకం.w != desktop_బహుళకం.w ||
            native_బహుళకం.h != desktop_బహుళకం.h) {
            SDL_కూడు_Fullscreen_Display_బహుళకం(dpy, &desktop_బహుళకం);
        }
    } లేకపోతే {
        // ...otherwise expose the integer scaled variants of the desktop resolution down to 1.
        desktop_బహుళకం.pixel_density = 1.0f;

        కొరకు (పూర్ణాంకం i = (పూర్ణాంకం)అంతర్గత->scale_గుణకం_2; i > 0; --i) {
            desktop_బహుళకం.w = అంతర్గత->logical.వెడల్పు * i;
            desktop_బహుళకం.h = అంతర్గత->logical.ఎత్తు * i;
            SDL_కూడు_Fullscreen_Display_బహుళకం(dpy, &desktop_బహుళకం);
        }
    }

    // Add emulated modes if wp_viewporter is supported and mode emulation is enabled.
    ఒకవేళ (video->viewporter && బహుళకం_emulation_enabled) {
        // The transformed display pixel width/height must be used here.
        కూడు_Emulated_Modes(అంతర్గత, native_బహుళకం.w, native_బహుళకం.h);
    }

    ఒకవేళ (అంతర్గత->display == 0) {
        // First time getting display info, initialize the VideoDisplay
        ఒకవేళ (అంతర్గత->physical.వెడల్పు_mm >= అంతర్గత->physical.ఎత్తు_mm) {
            అంతర్గత->placeholder.natural_orientation = SDL_ORIENTATION_LANDSCAPE;
        } లేకపోతే {
            అంతర్గత->placeholder.natural_orientation = SDL_ORIENTATION_PORTRAIT;
        }
        అంతర్గత->placeholder.current_orientation = అంతర్గత->orientation;
        అంతర్గత->placeholder.అంతర్గత = అంతర్గత;

        అంతర్గత->placeholder.props = SDL_CreateProperties();
        SDL_సమితి_సూచిక_Property(అంతర్గత->placeholder.props, SDL_PROP_DISPLAY_WAYLAND_WL_OUTPUT_సూచిక, అంతర్గత->output);

        // During initialization, the displays will be added after enumeration is complete.
        ఒకవేళ (!video->initializing) {
            ఒకవేళ (video->wp_color_manager_v1) {
                Wayland_GetColorInfoForOutput(అంతర్గత, false);
            }
            ఒకవేళ (video->scale_గమ్యం_display_enabled) {
                Wayland_DeriveOutputPixelCoordinates(video);
            }

            అంతర్గత->display = SDL_కూడు_Video_Display(&అంతర్గత->placeholder, true);
            Wayland_Refresh_కిటికీ_Positions();

            SDL_free(అంతర్గత->placeholder.name);
            SDL_zero(అంతర్గత->placeholder);
        }
    } లేకపోతే {
        SDL_SendDisplayEvent(dpy, SDL_EVENT_DISPLAY_ORIENTATION, అంతర్గత->orientation, 0);

        ఒకవేళ (అంతర్గత->geometry_మారింది) {
            ఒకవేళ (video->scale_గమ్యం_display_enabled) {
                Wayland_DeriveOutputPixelCoordinates(video);
            }

            SDL_SendDisplayEvent(dpy, SDL_EVENT_DISPLAY_MOVED, 0, 0);
            Wayland_Refresh_కిటికీ_Positions();
        }
    }

    అంతర్గత->geometry_మారింది = false;
}

స్థిర శూన్య handle_wl_output_scale(శూన్య *దత్తాంశం, నిర్మాణం wl_output *output, int32_t గుణకం)
{
    SDL_Display_దత్తాంశం *అంతర్గత = (SDL_Display_దత్తాంశం *)దత్తాంశం;
    అంతర్గత->integer_scale_గుణకం = గుణకం;
}

స్థిర శూన్య handle_wl_output_name(శూన్య *దత్తాంశం, నిర్మాణం wl_output *wl_output, స్థిరరాశి అక్షరం *name)
{
    SDL_Display_దత్తాంశం *అంతర్గత = (SDL_Display_దత్తాంశం *)దత్తాంశం;

    SDL_free(అంతర్గత->wl_output_name);
    అంతర్గత->wl_output_name = SDL_strdup(name);
}

స్థిర శూన్య handle_wl_output_description(శూన్య *దత్తాంశం, నిర్మాణం wl_output *wl_output, స్థిరరాశి అక్షరం *description)
{
    SDL_Display_దత్తాంశం *అంతర్గత = (SDL_Display_దత్తాంశం *)దత్తాంశం;

    ఒకవేళ (అంతర్గత->display == 0) {
        // The description, if available, supersedes the model name.
        SDL_free(అంతర్గత->placeholder.name);
        అంతర్గత->placeholder.name = SDL_strdup(description);
    }
}

స్థిర స్థిరరాశి నిర్మాణం wl_output_listener output_listener = {
    handle_wl_output_geometry,   // Version 1
    handle_wl_output_బహుళకం,       // Version 1
    handle_wl_output_పూర్తి,       // Version 2
    handle_wl_output_scale,      // Version 2
    handle_wl_output_name,       // Version 4
    handle_wl_output_description // Version 4
};

స్థిర శూన్య handle_output_image_description_మారింది(శూన్య *దత్తాంశం,
                                                    నిర్మాణం wp_color_management_output_v1 *wp_color_management_output_v1)
{
    SDL_Display_దత్తాంశం *display = (SDL_Display_దత్తాంశం *)దత్తాంశం;
    Wayland_GetColorInfoForOutput(display, false);
}

స్థిర స్థిరరాశి నిర్మాణం wp_color_management_output_v1_listener wp_color_management_output_listener = {
    handle_output_image_description_మారింది
};

స్థిర bool Wayland_కూడు_display(SDL_Video_దత్తాంశం *d, uint32_t id, uint32_t సంస్కరణ)
{
    నిర్మాణం wl_output *output;
    SDL_Display_దత్తాంశం *దత్తాంశం;

    output = wl_registry_bind(d->registry, id, &wl_output_interface, సంస్కరణ);
    ఒకవేళ (!output) {
        తిరిగి SDL_సమితి_Error("Failed to retrieve output.");
    }
    దత్తాంశం = (SDL_Display_దత్తాంశం *)SDL_calloc(1, పరిమాణం(*దత్తాంశం));
    దత్తాంశం->videodata = d;
    దత్తాంశం->output = output;
    దత్తాంశం->registry_id = id;
    దత్తాంశం->scale_గుణకం_2 = 1.0f;
    దత్తాంశం->integer_scale_గుణకం = 1;

    wl_output_కూడు_listener(output, &output_listener, దత్తాంశం);
    SDL_WAYLAND_రిజిస్టరు_output(output);

    // Keep a list of outputs for sorting and deferred protocol initialization.
    ఒకవేళ (d->output_లెక్క == d->output_max) {
        d->output_max += 4;
        d->output_list = SDL_realloc(d->output_list, పరిమాణం(SDL_Display_దత్తాంశం *) * d->output_max);
    }
    d->output_list[d->output_లెక్క++] = దత్తాంశం;

    ఒకవేళ (దత్తాంశం->videodata->xdg_output_manager) {
        దత్తాంశం->xdg_output = zxdg_output_manager_v1_get_xdg_output(దత్తాంశం->videodata->xdg_output_manager, output);
        zxdg_output_v1_కూడు_listener(దత్తాంశం->xdg_output, &xdg_output_listener, దత్తాంశం);
    }
    ఒకవేళ (దత్తాంశం->videodata->wp_color_manager_v1) {
        దత్తాంశం->wp_color_management_output = wp_color_manager_v1_get_output(దత్తాంశం->videodata->wp_color_manager_v1, output);
        wp_color_management_output_v1_కూడు_listener(దత్తాంశం->wp_color_management_output, &wp_color_management_output_listener, దత్తాంశం);

        // If not initializing, this will be queried synchronously in wl_output.done.
        ఒకవేళ (d->initializing) {
            Wayland_GetColorInfoForOutput(దత్తాంశం, true);
        }
    }
    తిరిగి true;
}

స్థిర శూన్య Wayland_free_display(SDL_VideoDisplay *display, bool send_event)
{
    ఒకవేళ (display) {
        SDL_Display_దత్తాంశం *display_దత్తాంశం = display->అంతర్గత;

        /* A preceding surface leave event is not guaranteed when an output is removed,
         * so ensure that no window continues to hold a reference to a removed output.
         */
        కొరకు (SDL_కిటికీ *కిటికీ = SDL_GetVideoDevice()->windows; కిటికీ; కిటికీ = కిటికీ->తదుపరి) {
            Wayland_Remove_Output_From_కిటికీ(కిటికీ->అంతర్గత, display_దత్తాంశం);
        }

        SDL_free(display_దత్తాంశం->wl_output_name);

        ఒకవేళ (display_దత్తాంశం->wp_color_management_output) {
            Wayland_FreeColorInfoState(display_దత్తాంశం->color_info_state);
            wp_color_management_output_v1_destroy(display_దత్తాంశం->wp_color_management_output);
        }

        ఒకవేళ (display_దత్తాంశం->xdg_output) {
            zxdg_output_v1_destroy(display_దత్తాంశం->xdg_output);
        }

        ఒకవేళ (wl_output_get_సంస్కరణ(display_దత్తాంశం->output) >= WL_OUTPUT_RELEASE_SINCE_సంస్కరణ) {
            wl_output_release(display_దత్తాంశం->output);
        } లేకపోతే {
            wl_output_destroy(display_దత్తాంశం->output);
        }

        SDL_DelVideoDisplay(display->id, send_event);
    }
}

స్థిర శూన్య Wayland_FinalizeDisplays(SDL_Video_దత్తాంశం *vid)
{
    Wayland_క్రమీకరించు_Outputs(vid);

    కొరకు(పూర్ణాంకం i = 0; i < vid->output_లెక్క; ++i) {
        SDL_Display_దత్తాంశం *d = vid->output_list[i];
        d->display = SDL_కూడు_Video_Display(&d->placeholder, false);
        SDL_free(d->placeholder.name);
        SDL_zero(d->placeholder);
    }
}

స్థిర శూన్య Wayland_init_xdg_output(SDL_Video_దత్తాంశం *d)
{
    కొరకు (పూర్ణాంకం i = 0; i < d->output_లెక్క; ++i) {
        SDL_Display_దత్తాంశం *disp = d->output_list[i];
        disp->xdg_output = zxdg_output_manager_v1_get_xdg_output(disp->videodata->xdg_output_manager, disp->output);
        zxdg_output_v1_కూడు_listener(disp->xdg_output, &xdg_output_listener, disp);
    }
}

స్థిర శూన్య Wayland_InitColorManager(SDL_Video_దత్తాంశం *d)
{
    కొరకు (పూర్ణాంకం i = 0; i < d->output_లెక్క; ++i) {
        SDL_Display_దత్తాంశం *disp = d->output_list[i];
        disp->wp_color_management_output = wp_color_manager_v1_get_output(disp->videodata->wp_color_manager_v1, disp->output);
        wp_color_management_output_v1_కూడు_listener(disp->wp_color_management_output, &wp_color_management_output_listener, disp);
        Wayland_GetColorInfoForOutput(disp, true);
    }
}

స్థిర శూన్య handle_xdg_session_created(శూన్య *దత్తాంశం, నిర్మాణం xdg_session_v1 *xdg_session_v1, స్థిరరాశి అక్షరం *id)
{
    SDL_సమితి_String_Property(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, id);
}

స్థిర శూన్య handle_xdg_session_restored(శూన్య *దత్తాంశం, నిర్మాణం xdg_session_v1 *xdg_session_v1)
{
    // NOP
}

స్థిర శూన్య handle_xdg_session_replaced(శూన్య *దత్తాంశం, నిర్మాణం xdg_session_v1 *xdg_session_v1)
{
    SDL_VideoDevice *viddev = SDL_GetVideoDevice();
    SDL_Video_దత్తాంశం *viddata = దత్తాంశం;

    // Clean up all session objects, as they have become inert, and should be destroyed.
    SDL_సమితి_String_Property(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, ఖాళీ);

    కొరకు (SDL_కిటికీ *w = viddev->windows; w; w = w->తదుపరి) {
        SDL_కిటికీ_దత్తాంశం *d = w->అంతర్గత;

        ఒకవేళ (d->xdg_toplevel_session) {
            xdg_toplevel_session_v1_destroy(d->xdg_toplevel_session);
            d->xdg_toplevel_session = ఖాళీ;

            SDL_free(d->session_id);
            d->session_id = ఖాళీ;
        }
    }

    ఒకవేళ (viddata->xdg_session) {
        xdg_session_v1_destroy(viddata->xdg_session);
        viddata->xdg_session = ఖాళీ;
    }
}

స్థిర స్థిరరాశి నిర్మాణం xdg_session_v1_listener xdg_session_listener = {
    .created  = handle_xdg_session_created,
    .restored = handle_xdg_session_restored,
    .replaced = handle_xdg_session_replaced
};

శూన్య Wayland_CreateSession(SDL_Video_దత్తాంశం *viddata)
{
    ఒకవేళ (!viddata->xdg_session_manager) {
        // Set the ID string to null if session management is not available.
        SDL_సమితి_String_Property(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, ఖాళీ);
        తిరిగి;
    }

    // Register a new session, if one does not yet exist.
    ఒకవేళ (!viddata->xdg_session) {
        స్థిరరాశి అక్షరం *session_id = SDL_GetStringProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, ఖాళీ);
        ఒకవేళ (session_id) {
            ఒకవేళ (*session_id == '\0') {
                // Create a new session if the ID string is empty.
                session_id = ఖాళీ;
            }

            స్థిరరాశి గణన xdg_session_manager_v1_reason reason = session_id ? XDG_SESSION_MANAGER_V1_REASON_SESSION_RESTORE : XDG_SESSION_MANAGER_V1_REASON_LAUNCH;
            viddata->xdg_session = xdg_session_manager_v1_get_session(viddata->xdg_session_manager, reason, session_id);
            xdg_session_v1_కూడు_listener(viddata->xdg_session, &xdg_session_listener, viddata);
        }
    }
}

స్థిర శూన్య Wayland_SessionDestroy(SDL_Video_దత్తాంశం *viddata)
{
    // If the session string was cleared, remove the session.
    ఒకవేళ (viddata->xdg_session) {
        స్థిరరాశి అక్షరం *session_id = SDL_GetStringProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, ఖాళీ);
        ఒకవేళ (!session_id || *session_id == '\0') {
            xdg_session_v1_remove(viddata->xdg_session);

            WAYLAND_wl_display_roundtrip(viddata->display);
        } లేకపోతే {
            xdg_session_v1_destroy(viddata->xdg_session);
        }

        viddata->xdg_session = ఖాళీ;
    }
}

స్థిర శూన్య handle_xdg_wm_పునాది_ping(శూన్య *దత్తాంశం, నిర్మాణం xdg_wm_పునాది *xdg, uint32_t serial)
{
    xdg_wm_పునాది_pong(xdg, serial);
}

స్థిర స్థిరరాశి నిర్మాణం xdg_wm_పునాది_listener xdg_wm_పునాది_listener_2 = {
    handle_xdg_wm_పునాది_ping
};

#నిర్వచితమైతే HAVE_LIBDECOR_H
స్థిర శూన్య libdecor_error(నిర్మాణం libdecor *context,
                           గణన libdecor_error error,
                           స్థిరరాశి అక్షరం *సందేశం)
{
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "libdecor error (%d): %s", error, సందేశం);
}

స్థిర నిర్మాణం libdecor_interface libdecor_interface = {
    libdecor_error
};
#అయితే_ముగింపు

స్థిర శూన్య handle_registry_global(శూన్య *దత్తాంశం, నిర్మాణం wl_registry *registry, uint32_t id,
                                   స్థిరరాశి అక్షరం *interface, uint32_t సంస్కరణ)
{
    SDL_Video_దత్తాంశం *d = దత్తాంశం;

    ఒకవేళ (SDL_strcmp(interface, wl_compositor_interface.name) == 0) {
        d->compositor = wl_registry_bind(d->registry, id, &wl_compositor_interface, SDL_min(SDL_WL_COMPOSITOR_సంస్కరణ, సంస్కరణ));
    } లేకపోతే ఒకవేళ (SDL_strcmp(interface, wl_subcompositor_interface.name) == 0) {
        d->subcompositor = wl_registry_bind(d->registry, id, &wl_subcompositor_interface, 1);
    } లేకపోతే ఒకవేళ (SDL_strcmp(interface, wl_output_interface.name) == 0) {
        Wayland_కూడు_display(d, id, SDL_min(సంస్కరణ, SDL_WL_OUTPUT_సంస్కరణ));
    } లేకపోతే ఒకవేళ (SDL_strcmp(interface, wl_seat_interface.name) == 0) {
        నిర్మాణం wl_seat *seat = wl_registry_bind(d->registry, id, &wl_seat_interface, SDL_min(SDL_WL_SEAT_సంస్కరణ, సంస్కరణ));
        Wayland_DisplayCreateSeat(d, seat, id);
    } లేకపోతే ఒకవేళ (SDL_strcmp(interface, xdg_wm_పునాది_interface.name) == 0) {
        d->shell.xdg = wl_registry_bind(d->registry, id, &xdg_wm_పునాది_interface, SDL_min(సంస్కరణ, 7));
        xdg_wm_పునాది_కూడు_listener(d->shell.xdg, &xdg_wm_పునాది_listener_2, ఖాళీ);
    } లేకపోతే ఒకవేళ (SDL_strcmp(interface, wl_shm_interface.name) == 0) {
        d->shm = wl_registry_bind(registry, id, &wl_shm_interface, SDL_min(SDL_WL_SHM_సంస్కరణ, సంస్కరణ));
    } లేకపోతే ఒకవేళ (SDL_strcmp(interface, zwp_relative_సూచిక_manager_v1_interface.name) == 0) {
        d->relative_సూచిక_manager = wl_registry_bind(d->registry, id, &zwp_relative_సూచిక_manager_v1_interface, 1);
    } లేకపోతే ఒకవేళ (SDL_strcmp(interface, zwp_సూచిక_constraints_v1_interface.name) == 0) {
        d->సూచిక_constraints = wl_registry_bind(d->registry, id, &zwp_సూచిక_constraints_v1_interface, 1);
    } లేకపోతే ఒకవేళ (SDL_strcmp(interface, zwp_keyboard_shortcuts_inhibit_manager_v1_interface.name) == 0) {
        d->కీలకం_inhibitor_manager = wl_registry_bind(d->registry, id, &zwp_keyboard_shortcuts_inhibit_manager_v1_interface, 1);
    } లేకపోతే ఒకవేళ (SDL_strcmp(interface, zwp_idle_inhibit_manager_v1_interface.name) == 0) {
        d->idle_inhibit_manager = wl_registry_bind(d->registry, id, &zwp_idle_inhibit_manager_v1_interface, 1);
    } లేకపోతే ఒకవేళ (SDL_strcmp(interface, xdg_activation_v1_interface.name) == 0) {
        d->activation_manager = wl_registry_bind(d->registry, id, &xdg_activation_v1_interface, 1);
    } లేకపోతే ఒకవేళ (SDL_strcmp(interface, zwp_పాఠ్యం_ఆదానం_manager_v3_interface.name) == 0) {
        d->పాఠ్యం_ఆదానం_manager = wl_registry_bind(d->registry, id, &zwp_పాఠ్యం_ఆదానం_manager_v3_interface, 1);
        Wayland_Display_Init_పాఠ్యం_ఆదానం_Manager(d, id);
    } లేకపోతే ఒకవేళ (SDL_strcmp(interface, wl_దత్తాంశం_device_manager_interface.name) == 0) {
        d->దత్తాంశం_device_manager = wl_registry_bind(d->registry, id, &wl_దత్తాంశం_device_manager_interface, SDL_min(3, సంస్కరణ));
        Wayland_Display_Init_దత్తాంశం_Device_Manager(d);
    } లేకపోతే ఒకవేళ (SDL_strcmp(interface, zwp_primary_selection_device_manager_v1_interface.name) == 0) {
        d->primary_selection_device_manager = wl_registry_bind(d->registry, id, &zwp_primary_selection_device_manager_v1_interface, 1);
        Wayland_DisplayInitPrimarySelectionDeviceManager(d);
    } లేకపోతే ఒకవేళ (SDL_strcmp(interface, zxdg_decoration_manager_v1_interface.name) == 0) {
        d->decoration_manager = wl_registry_bind(d->registry, id, &zxdg_decoration_manager_v1_interface, SDL_min(2, సంస్కరణ));
    } లేకపోతే ఒకవేళ (SDL_strcmp(interface, zwp_tablet_manager_v2_interface.name) == 0) {
        d->tablet_manager = wl_registry_bind(d->registry, id, &zwp_tablet_manager_v2_interface, 1);
        Wayland_DisplayInitTabletManager(d);
    } లేకపోతే ఒకవేళ (SDL_strcmp(interface, zxdg_output_manager_v1_interface.name) == 0) {
        సంస్కరణ = SDL_min(సంస్కరణ, 3); // Versions 1 through 3 are supported.
        d->xdg_output_manager = wl_registry_bind(d->registry, id, &zxdg_output_manager_v1_interface, సంస్కరణ);
        Wayland_init_xdg_output(d);
    } లేకపోతే ఒకవేళ (SDL_strcmp(interface, wp_viewporter_interface.name) == 0) {
        d->viewporter = wl_registry_bind(d->registry, id, &wp_viewporter_interface, 1);
    } లేకపోతే ఒకవేళ (SDL_strcmp(interface, wp_fractional_scale_manager_v1_interface.name) == 0) {
        d->fractional_scale_manager = wl_registry_bind(d->registry, id, &wp_fractional_scale_manager_v1_interface, 1);
    } లేకపోతే ఒకవేళ (SDL_strcmp(interface, zwp_ఆదానం_timestamps_manager_v1_interface.name) == 0) {
        d->ఆదానం_timestamps_manager = wl_registry_bind(d->registry, id, &zwp_ఆదానం_timestamps_manager_v1_interface, 1);
        Wayland_Display_Init_ఆదానం_Timestamp_Manager(d);
    } లేకపోతే ఒకవేళ (SDL_strcmp(interface, wp_cursor_shape_manager_v1_interface.name) == 0) {
        d->cursor_shape_manager = wl_registry_bind(d->registry, id, &wp_cursor_shape_manager_v1_interface, SDL_min(సంస్కరణ, 2));
        Wayland_DisplayInitCursorShapeManager(d);
    } లేకపోతే ఒకవేళ (SDL_strcmp(interface, zxdg_exporter_v2_interface.name) == 0) {
        d->zxdg_exporter_v2 = wl_registry_bind(d->registry, id, &zxdg_exporter_v2_interface, 1);
    } లేకపోతే ఒకవేళ (SDL_strcmp(interface, xdg_wm_dialog_v1_interface.name) == 0) {
        d->xdg_wm_dialog_v1 = wl_registry_bind(d->registry, id, &xdg_wm_dialog_v1_interface, 1);
    } లేకపోతే ఒకవేళ (SDL_strcmp(interface, wp_alpha_modifier_v1_interface.name) == 0) {
        d->wp_alpha_modifier_v1 = wl_registry_bind(d->registry, id, &wp_alpha_modifier_v1_interface, 1);
    } లేకపోతే ఒకవేళ (SDL_strcmp(interface, xdg_toplevel_icon_manager_v1_interface.name) == 0) {
        d->xdg_toplevel_icon_manager_v1 = wl_registry_bind(d->registry, id, &xdg_toplevel_icon_manager_v1_interface, 1);
    } లేకపోతే ఒకవేళ (SDL_strcmp(interface, frog_color_management_factory_v1_interface.name) == 0) {
        d->frog_color_management_factory_v1 = wl_registry_bind(d->registry, id, &frog_color_management_factory_v1_interface, 1);
    } లేకపోతే ఒకవేళ (SDL_strcmp(interface, wp_color_manager_v1_interface.name) == 0) {
        d->wp_color_manager_v1 = wl_registry_bind(d->registry, id, &wp_color_manager_v1_interface, SDL_min(సంస్కరణ, 2));
        Wayland_InitColorManager(d);
    } లేకపోతే ఒకవేళ (SDL_strcmp(interface, wp_సూచిక_warp_v1_interface.name) == 0) {
        d->wp_సూచిక_warp_v1 = wl_registry_bind(d->registry, id, &wp_సూచిక_warp_v1_interface, 1);
    } లేకపోతే ఒకవేళ (SDL_strcmp(interface, zwp_సూచిక_gestures_v1_interface.name) == 0) {
        d->zwp_సూచిక_gestures = wl_registry_bind(d->registry, id, &zwp_సూచిక_gestures_v1_interface, SDL_min(సంస్కరణ, 3));
        Wayland_Display_Init_సూచిక_Gesture_Manager(d);
    } లేకపోతే ఒకవేళ (SDL_strcmp(interface, wp_single_pixel_బఫరు_manager_v1_interface.name) == 0) {
        d->single_pixel_బఫరు_manager = wl_registry_bind(d->registry, id, &wp_single_pixel_బఫరు_manager_v1_interface, 1);
    } లేకపోతే ఒకవేళ (SDL_strcmp(interface, xdg_session_manager_v1_interface.name) == 0) {
        d->xdg_session_manager = wl_registry_bind(d->registry, id, &xdg_session_manager_v1_interface, 1);
    } లేకపోతే ఒకవేళ (SDL_strcmp(interface, xdg_toplevel_ట్యాగ్_manager_v1_interface.name) == 0) {
        d->xdg_toplevel_ట్యాగ్_manager = wl_registry_bind(d->registry, id, &xdg_toplevel_ట్యాగ్_manager_v1_interface, 1);
    }
#నిర్వచితమైతే SDL_WL_FIXES_సంస్కరణ
    లేకపోతే ఒకవేళ (SDL_strcmp(interface, wl_fixes_interface.name) == 0) {
        d->wl_fixes = wl_registry_bind(d->registry, id, &wl_fixes_interface, SDL_min(SDL_WL_FIXES_సంస్కరణ, సంస్కరణ));
    }
#అయితే_ముగింపు
}

స్థిర శూన్య handle_registry_remove_global(శూన్య *దత్తాంశం, నిర్మాణం wl_registry *registry, uint32_t id)
{
    SDL_Video_దత్తాంశం *d = దత్తాంశం;

    // We don't get an interface, just an ID, so check outputs and seats.
    కొరకు (పూర్ణాంకం i = 0; i < d->output_లెక్క; ++i) {
        SDL_Display_దత్తాంశం *disp = d->output_list[i];
        ఒకవేళ (disp->registry_id == id) {
            Wayland_free_display(SDL_GetVideoDisplay(disp->display), true);

            ఒకవేళ (i < d->output_లెక్క) {
                SDL_memmove(&d->output_list[i], &d->output_list[i + 1], పరిమాణం(SDL_Display_దత్తాంశం *) * (d->output_లెక్క - i - 1));
            }

            d->output_లెక్క--;
            వెళ్ళు ack_remove;
        }
    }

    SDL_WaylandSeat *seat, *తాత్కాలిక;
    wl_list_for_each_సురక్షిత (seat, తాత్కాలిక, &d->seat_list, link) {
        ఒకవేళ (seat->registry_id == id) {
            Wayland_SeatDestroy(seat, false);
            వెళ్ళు ack_remove;
        }
    }

ack_remove:
    ఒకవేళ (d->wl_fixes && wl_fixes_get_సంస్కరణ(d->wl_fixes) >= WL_FIXES_ACK_GLOBAL_REMOVE_SINCE_సంస్కరణ) {
        wl_fixes_ack_global_remove(d->wl_fixes, registry, id);
    }
}

స్థిర స్థిరరాశి నిర్మాణం wl_registry_listener registry_listener = {
    handle_registry_global,
    handle_registry_remove_global
};

#నిర్వచితమైతే HAVE_LIBDECOR_H
స్థిర bool should_use_libdecor(SDL_Video_దత్తాంశం *దత్తాంశం, bool ignore_xdg)
{
    ఒకవేళ (!SDL_WAYLAND_HAVE_WAYLAND_LIBDECOR) {
        తిరిగి false;
    }

    ఒకవేళ (SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_PREFER_LIBDECOR, false)) {
        తిరిగి true;
    }

    ఒకవేళ (ignore_xdg) {
        తిరిగి true;
    }

    ఒకవేళ (దత్తాంశం->decoration_manager) {
        తిరిగి false;
    }

    తిరిగి true;
}

స్థిర శూన్య LibdecorNew(SDL_Video_దత్తాంశం *దత్తాంశం)
{
    దత్తాంశం->shell.libdecor = libdecor_new(దత్తాంశం->display, &libdecor_interface);
}

// Called in another thread, but the UI thread is blocked in SDL_WaitThread
// during that time, so it should be OK to dereference data without locks
స్థిర పూర్ణాంకం SDLCALL Libdecor_New_లోపల_Thread(శూన్య *దత్తాంశం)
{
    LibdecorNew((SDL_Video_దత్తాంశం *)దత్తాంశం);
    తిరిగి 0;
}
#అయితే_ముగింపు

#నిర్వచితమైతే HAVE_GETRESUID
#నిర్వచించు SDL_getresuid getresuid
#లేకపోతే
// Non-POSIX, but Linux and some BSDs have it.
// To reduce the number of code paths, if getresuid() isn't available at
// compile-time, we behave as though it existed but failed at runtime.
స్థిర అంతఃవరుస పూర్ణాంకం SDL_getresuid(uid_t *ruid, uid_t *euid, uid_t *suid) {
    errno = ENOSYS;
    తిరిగి -1;
}
#అయితే_ముగింపు

#నిర్వచితమైతే HAVE_GETRESGID
#నిర్వచించు SDL_getresgid getresgid
#లేకపోతే
// Same as getresuid() but for the primary group
స్థిర అంతఃవరుస పూర్ణాంకం SDL_getresgid(gid_t *rgid, gid_t *egid, gid_t *sgid) {
    errno = ENOSYS;
    తిరిగి -1;
}
#అయితే_ముగింపు

bool CanUseGtk(శూన్య)
{
    // "Real", "effective" and "saved" IDs: see e.g. Linux credentials(7)
    uid_t ruid = -1, euid = -1, suid = -1;
    gid_t rgid = -1, egid = -1, sgid = -1;

    ఒకవేళ (!SDL_GetHintBoolean("SDL_ENABLE_GTK", true)) {
        SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "Not using GTK due to hint");
        తిరిగి false;
    }

    // This is intended to match the check in gtkmain.c, rather than being
    // an exhaustive check for having elevated privileges: as a result
    // we don't use Linux getauxval() or prctl PR_GET_DUMPABLE,
    // BSD issetugid(), or similar OS-specific detection

    ఒకవేళ (SDL_getresuid(&ruid, &euid, &suid) != 0) {
        ruid = suid = getuid();
        euid = geteuid();
    }

    ఒకవేళ (SDL_getresgid(&rgid, &egid, &sgid) != 0) {
        rgid = sgid = getgid();
        egid = getegid();
    }

    // Real ID != effective ID means we are setuid or setgid:
    // GTK will refuse to initialize, and instead will call exit().
    ఒకవేళ (ruid != euid || rgid != egid) {
        SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "Not using GTK due to setuid/setgid");
        తిరిగి false;
    }

    // Real ID != saved ID means we are setuid or setgid, we previously
    // dropped privileges, but we can regain them; this protects against
    // accidents but does not protect against arbitrary code execution.
    // Again, GTK will refuse to initialize if this is the case.
    ఒకవేళ (ruid != suid || rgid != sgid) {
        SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "Not using GTK due to saved uid/gid");
        తిరిగి false;
    }

    తిరిగి true;
}

bool Wayland_ఎక్కించు_Libdecor(SDL_Video_దత్తాంశం *దత్తాంశం, bool ignore_xdg)
{
#నిర్వచితమైతే HAVE_LIBDECOR_H
    ఒకవేళ (దత్తాంశం->shell.libdecor != ఖాళీ) {
        తిరిగి true; // Already loaded!
    }
    ఒకవేళ (should_use_libdecor(దత్తాంశం, ignore_xdg)) {
        ఒకవేళ (CanUseGtk()) {
            LibdecorNew(దత్తాంశం);
        } లేకపోతే {
            // Intentionally initialize libdecor in a non-main thread
            // so that it will not use its GTK plugin, but instead will
            // fall back to the Cairo or dummy plugin
            SDL_Thread *thread = SDL_CreateThread(Libdecor_New_లోపల_Thread, "SDL_LibdecorNew", (శూన్య *)దత్తాంశం);
            // Note that the other thread now "owns" data until we have
            // waited for it, so don't touch data here
            SDL_WaitThread(thread, ఖాళీ);
        }

        తిరిగి దత్తాంశం->shell.libdecor != ఖాళీ;
    }
#అయితే_ముగింపు
    తిరిగి false;
}

bool Wayland_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;

    దత్తాంశం->event_thread_context = Wayland_CreateEventThread(దత్తాంశం, "SDL Event Thread Queue");
    ఒకవేళ (!దత్తాంశం->event_thread_context) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Failed to create event thread context");
    }

    దత్తాంశం->పని_thread_context = Wayland_Create_పని_Thread();
    ఒకవేళ (!దత్తాంశం->పని_thread_context) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Failed to create job thread context");
    }

    దత్తాంశం->xkb_context = WAYLAND_xkb_context_new(0);
    ఒకవేళ (!దత్తాంశం->xkb_context) {
        తిరిగి SDL_సమితి_Error("Failed to create XKB context");
    }

    దత్తాంశం->registry = wl_display_get_registry(దత్తాంశం->display);
    ఒకవేళ (!దత్తాంశం->registry) {
        తిరిగి SDL_సమితి_Error("Failed to get the Wayland registry");
    }

    wl_registry_కూడు_listener(దత్తాంశం->registry, &registry_listener, దత్తాంశం);

    // First roundtrip to receive all registry objects.
    WAYLAND_wl_display_roundtrip(దత్తాంశం->display);

    // Require viewports and xdg-output for display scaling.
    ఒకవేళ (దత్తాంశం->scale_గమ్యం_display_enabled) {
        ఒకవేళ (!దత్తాంశం->viewporter) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Display scaling requires the missing 'wp_viewporter' protocol: disabling");
            దత్తాంశం->scale_గమ్యం_display_enabled = false;
        }
        ఒకవేళ (!దత్తాంశం->xdg_output_manager) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Display scaling requires the missing 'zxdg_output_manager_v1' protocol: disabling");
            దత్తాంశం->scale_గమ్యం_display_enabled = false;
        }
    }

    // Now that we have all the protocols, load libdecor if applicable
    Wayland_ఎక్కించు_Libdecor(దత్తాంశం, false);

    // Second roundtrip to receive all output events.
    WAYLAND_wl_display_roundtrip(దత్తాంశం->display);

    Wayland_FinalizeDisplays(దత్తాంశం);

    Wayland_InitMouse(దత్తాంశం);
    Wayland_InitKeyboard(_this);

    ఒకవేళ (దత్తాంశం->primary_selection_device_manager) {
        _this->సమితి_Primary_Selection_పాఠ్యం = Wayland_సమితి_Primary_Selection_పాఠ్యం;
        _this->Get_Primary_Selection_పాఠ్యం = Wayland_Get_Primary_Selection_పాఠ్యం;
        _this->Has_Primary_Selection_పాఠ్యం = Wayland_Has_Primary_Selection_పాఠ్యం;
    }

    దత్తాంశం->initializing = false;

    తిరిగి true;
}

స్థిర bool Wayland_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    SDL_Video_దత్తాంశం *viddata = _this->అంతర్గత;
    SDL_Display_దత్తాంశం *అంతర్గత = display->అంతర్గత;

    ఒకవేళ (!viddata->scale_గమ్యం_display_enabled) {
        rect->x = అంతర్గత->logical.x;
        rect->y = అంతర్గత->logical.y;
    } లేకపోతే {
        rect->x = అంతర్గత->pixel.x;
        rect->y = అంతర్గత->pixel.y;
    }

    // When an emulated, exclusive fullscreen window has focus, treat the mode dimensions as the display bounds.
    ఒకవేళ (display->fullscreen_కిటికీ &&
        display->fullscreen_కిటికీ->fullscreen_exclusive &&
        display->fullscreen_కిటికీ->అంతర్గత->చురుకైన &&
        display->fullscreen_కిటికీ->current_fullscreen_బహుళకం.w != 0 &&
        display->fullscreen_కిటికీ->current_fullscreen_బహుళకం.h != 0) {
        rect->w = display->fullscreen_కిటికీ->current_fullscreen_బహుళకం.w;
        rect->h = display->fullscreen_కిటికీ->current_fullscreen_బహుళకం.h;
    } లేకపోతే {
        ఒకవేళ (!viddata->scale_గమ్యం_display_enabled) {
            rect->w = display->current_బహుళకం->w;
            rect->h = display->current_బహుళకం->h;
        } లేకపోతే ఒకవేళ (అంతర్గత->transform & WL_OUTPUT_TRANSFORM_90) {
            rect->w = అంతర్గత->pixel.ఎత్తు;
            rect->h = అంతర్గత->pixel.వెడల్పు;
        } లేకపోతే {
            rect->w = అంతర్గత->pixel.వెడల్పు;
            rect->h = అంతర్గత->pixel.ఎత్తు;
        }
    }
    తిరిగి true;
}

స్థిర శూన్య Wayland_VideoCleanup(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    SDL_WaylandSeat *seat, *tmp;

    Wayland_SessionDestroy(దత్తాంశం);

    కొరకు (పూర్ణాంకం i = _this->అంకె_displays - 1; i >= 0; --i) {
        SDL_VideoDisplay *display = _this->displays[i];
        Wayland_free_display(display, false);
    }
    SDL_free(దత్తాంశం->output_list);

    wl_list_for_each_సురక్షిత (seat, tmp, &దత్తాంశం->seat_list, link) {
        Wayland_SeatDestroy(seat, true);
    }

    Wayland_FiniMouse(దత్తాంశం);
    Wayland_QuitKeyboard(_this);

    Wayland_DestroyEventThread(దత్తాంశం->event_thread_context);
    దత్తాంశం->event_thread_context = ఖాళీ;

    Wayland_Destroy_పని_Thread(దత్తాంశం->పని_thread_context);
    దత్తాంశం->పని_thread_context = ఖాళీ;

    ఒకవేళ (దత్తాంశం->సూచిక_constraints) {
        zwp_సూచిక_constraints_v1_destroy(దత్తాంశం->సూచిక_constraints);
        దత్తాంశం->సూచిక_constraints = ఖాళీ;
    }

    ఒకవేళ (దత్తాంశం->relative_సూచిక_manager) {
        zwp_relative_సూచిక_manager_v1_destroy(దత్తాంశం->relative_సూచిక_manager);
        దత్తాంశం->relative_సూచిక_manager = ఖాళీ;
    }

    ఒకవేళ (దత్తాంశం->activation_manager) {
        xdg_activation_v1_destroy(దత్తాంశం->activation_manager);
        దత్తాంశం->activation_manager = ఖాళీ;
    }

    ఒకవేళ (దత్తాంశం->idle_inhibit_manager) {
        zwp_idle_inhibit_manager_v1_destroy(దత్తాంశం->idle_inhibit_manager);
        దత్తాంశం->idle_inhibit_manager = ఖాళీ;
    }

    ఒకవేళ (దత్తాంశం->కీలకం_inhibitor_manager) {
        zwp_keyboard_shortcuts_inhibit_manager_v1_destroy(దత్తాంశం->కీలకం_inhibitor_manager);
        దత్తాంశం->కీలకం_inhibitor_manager = ఖాళీ;
    }

    ఒకవేళ (దత్తాంశం->పాఠ్యం_ఆదానం_manager) {
        zwp_పాఠ్యం_ఆదానం_manager_v3_destroy(దత్తాంశం->పాఠ్యం_ఆదానం_manager);
        దత్తాంశం->పాఠ్యం_ఆదానం_manager = ఖాళీ;
    }

    ఒకవేళ (దత్తాంశం->xkb_context) {
        WAYLAND_xkb_context_unref(దత్తాంశం->xkb_context);
        దత్తాంశం->xkb_context = ఖాళీ;
    }

    ఒకవేళ (దత్తాంశం->tablet_manager) {
        zwp_tablet_manager_v2_destroy((నిర్మాణం zwp_tablet_manager_v2 *)దత్తాంశం->tablet_manager);
        దత్తాంశం->tablet_manager = ఖాళీ;
    }

    ఒకవేళ (దత్తాంశం->దత్తాంశం_device_manager) {
        wl_దత్తాంశం_device_manager_destroy(దత్తాంశం->దత్తాంశం_device_manager);
        దత్తాంశం->దత్తాంశం_device_manager = ఖాళీ;
    }

    ఒకవేళ (దత్తాంశం->shm) {
        ఒకవేళ (wl_shm_get_సంస్కరణ(దత్తాంశం->shm) >= WL_SHM_RELEASE_SINCE_సంస్కరణ) {
            wl_shm_release(దత్తాంశం->shm);
        } లేకపోతే {
            wl_shm_destroy(దత్తాంశం->shm);
        }
        దత్తాంశం->shm = ఖాళీ;
    }

    ఒకవేళ (దత్తాంశం->shell.xdg) {
        xdg_wm_పునాది_destroy(దత్తాంశం->shell.xdg);
        దత్తాంశం->shell.xdg = ఖాళీ;
    }

    ఒకవేళ (దత్తాంశం->decoration_manager) {
        zxdg_decoration_manager_v1_destroy(దత్తాంశం->decoration_manager);
        దత్తాంశం->decoration_manager = ఖాళీ;
    }

    ఒకవేళ (దత్తాంశం->xdg_output_manager) {
        zxdg_output_manager_v1_destroy(దత్తాంశం->xdg_output_manager);
        దత్తాంశం->xdg_output_manager = ఖాళీ;
    }

    ఒకవేళ (దత్తాంశం->viewporter) {
        wp_viewporter_destroy(దత్తాంశం->viewporter);
        దత్తాంశం->viewporter = ఖాళీ;
    }

    ఒకవేళ (దత్తాంశం->primary_selection_device_manager) {
        zwp_primary_selection_device_manager_v1_destroy(దత్తాంశం->primary_selection_device_manager);
        దత్తాంశం->primary_selection_device_manager = ఖాళీ;
    }

    ఒకవేళ (దత్తాంశం->fractional_scale_manager) {
        wp_fractional_scale_manager_v1_destroy(దత్తాంశం->fractional_scale_manager);
        దత్తాంశం->fractional_scale_manager = ఖాళీ;
    }

    ఒకవేళ (దత్తాంశం->ఆదానం_timestamps_manager) {
        zwp_ఆదానం_timestamps_manager_v1_destroy(దత్తాంశం->ఆదానం_timestamps_manager);
        దత్తాంశం->ఆదానం_timestamps_manager = ఖాళీ;
    }

    ఒకవేళ (దత్తాంశం->cursor_shape_manager) {
        wp_cursor_shape_manager_v1_destroy(దత్తాంశం->cursor_shape_manager);
        దత్తాంశం->cursor_shape_manager = ఖాళీ;
    }

    ఒకవేళ (దత్తాంశం->zxdg_exporter_v2) {
        zxdg_exporter_v2_destroy(దత్తాంశం->zxdg_exporter_v2);
        దత్తాంశం->zxdg_exporter_v2 = ఖాళీ;
    }

    ఒకవేళ (దత్తాంశం->xdg_wm_dialog_v1) {
        xdg_wm_dialog_v1_destroy(దత్తాంశం->xdg_wm_dialog_v1);
        దత్తాంశం->xdg_wm_dialog_v1 = ఖాళీ;
    }

    ఒకవేళ (దత్తాంశం->wp_alpha_modifier_v1) {
        wp_alpha_modifier_v1_destroy(దత్తాంశం->wp_alpha_modifier_v1);
        దత్తాంశం->wp_alpha_modifier_v1 = ఖాళీ;
    }

    ఒకవేళ (దత్తాంశం->xdg_toplevel_icon_manager_v1) {
        xdg_toplevel_icon_manager_v1_destroy(దత్తాంశం->xdg_toplevel_icon_manager_v1);
        దత్తాంశం->xdg_toplevel_icon_manager_v1 = ఖాళీ;
    }

    ఒకవేళ (దత్తాంశం->frog_color_management_factory_v1) {
        frog_color_management_factory_v1_destroy(దత్తాంశం->frog_color_management_factory_v1);
        దత్తాంశం->frog_color_management_factory_v1 = ఖాళీ;
    }

    ఒకవేళ (దత్తాంశం->wp_color_manager_v1) {
        wp_color_manager_v1_destroy(దత్తాంశం->wp_color_manager_v1);
        దత్తాంశం->wp_color_manager_v1 = ఖాళీ;
    }

    ఒకవేళ (దత్తాంశం->wp_సూచిక_warp_v1) {
        wp_సూచిక_warp_v1_destroy(దత్తాంశం->wp_సూచిక_warp_v1);
        దత్తాంశం->wp_సూచిక_warp_v1 = ఖాళీ;
    }

    ఒకవేళ (దత్తాంశం->zwp_సూచిక_gestures) {
        ఒకవేళ (zwp_సూచిక_gestures_v1_get_సంస్కరణ(దత్తాంశం->zwp_సూచిక_gestures) >= ZWP_సూచిక_GESTURES_V1_RELEASE_SINCE_సంస్కరణ) {
            zwp_సూచిక_gestures_v1_release(దత్తాంశం->zwp_సూచిక_gestures);
        } లేకపోతే {
            zwp_సూచిక_gestures_v1_destroy(దత్తాంశం->zwp_సూచిక_gestures);
        }
        దత్తాంశం->zwp_సూచిక_gestures = ఖాళీ;
    }

    ఒకవేళ (దత్తాంశం->single_pixel_బఫరు_manager) {
        wp_single_pixel_బఫరు_manager_v1_destroy(దత్తాంశం->single_pixel_బఫరు_manager);
        దత్తాంశం->single_pixel_బఫరు_manager = ఖాళీ;
    }

    ఒకవేళ (దత్తాంశం->xdg_session_manager) {
        xdg_session_manager_v1_destroy(దత్తాంశం->xdg_session_manager);
        దత్తాంశం->xdg_session_manager = ఖాళీ;
    }

    ఒకవేళ (దత్తాంశం->xdg_toplevel_ట్యాగ్_manager) {
        xdg_toplevel_ట్యాగ్_manager_v1_destroy(దత్తాంశం->xdg_toplevel_ట్యాగ్_manager);
        దత్తాంశం->xdg_toplevel_ట్యాగ్_manager = ఖాళీ;
    }

    ఒకవేళ (దత్తాంశం->subcompositor) {
        wl_subcompositor_destroy(దత్తాంశం->subcompositor);
        దత్తాంశం->subcompositor = ఖాళీ;
    }

    ఒకవేళ (దత్తాంశం->compositor) {
        wl_compositor_destroy(దత్తాంశం->compositor);
        దత్తాంశం->compositor = ఖాళీ;
    }

    ఒకవేళ (దత్తాంశం->registry) {
        ఒకవేళ (దత్తాంశం->wl_fixes) {
            wl_fixes_destroy_registry(దత్తాంశం->wl_fixes, దత్తాంశం->registry);
            wl_fixes_destroy(దత్తాంశం->wl_fixes);
            దత్తాంశం->wl_fixes = ఖాళీ;
        }
        wl_registry_destroy(దత్తాంశం->registry);
        దత్తాంశం->registry = ఖాళీ;
    }
}

స్థిర bool Wayland_VideoReconnect(SDL_VideoDevice *_this)
{
#ఒకవేళ 0 // TODO RECONNECT: Uncomment all when https://invent.kde.org/plasma/kwin/-/wikis/Restarting is completed
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;

    SDL_కిటికీ *కిటికీ = ఖాళీ;

    SDL_GLContext current_ctx = SDL_GL_GetCurrentContext();
    SDL_కిటికీ *current_కిటికీ = SDL_GL_Get_Current_కిటికీ();

    SDL_GL_MakeCurrent(ఖాళీ, ఖాళీ);
    Wayland_VideoCleanup(_this);

    SDL_ResetKeyboard();
    SDL_ResetMouse();
    ఒకవేళ (WAYLAND_wl_display_reconnect(దత్తాంశం->display) < 0) {
        తిరిగి false;
    }

    Wayland_VideoInit(_this);

    కిటికీ = _this->windows;
    అయితే (కిటికీ) {
        /* We're going to cheat _just_ for a second and strip the OpenGL flag.
         * The Wayland driver actually forces it in CreateWindow, and
         * RecreateWindow does a bunch of unloading/loading of libGL, so just
         * strip the flag so RecreateWindow doesn't mess with the GL context,
         * and CreateWindow will add it right back!
         * -flibit
         */
        కిటికీ->flags &= ~SDL_కిటికీ_OPENGL;

        SDL_Recreate_కిటికీ(కిటికీ, కిటికీ->flags);
        కిటికీ = కిటికీ->తదుపరి;
    }

    Wayland_RecreateCursors();

    ఒకవేళ (current_కిటికీ && current_ctx) {
        SDL_GL_MakeCurrent (current_కిటికీ, current_ctx);
    }
    తిరిగి true;
#లేకపోతే
    తిరిగి false;
#అయితే_ముగింపు // 0
}

bool Wayland_HandleDisplayDisconnected(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *video_దత్తాంశం = _this->అంతర్గత;

    /* Something has failed with the Wayland connection -- for example,
     * the compositor may have shut down and closed its end of the socket,
     * or there is a library-specific error.
     *
     * Try to recover once, then quit.
     */
    ఒకవేళ (video_దత్తాంశం->display_disconnected) {
        తిరిగి false;
    }

    ఒకవేళ (Wayland_VideoReconnect(_this)) {
        తిరిగి true;
    }

    video_దత్తాంశం->display_disconnected = true;
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Wayland display connection closed by server (fatal)");

    // Only send a single quit message, as application shutdown might call SDL_PumpEvents().
    SDL_SendQuit();

    తిరిగి false;
}

శూన్య Wayland_VideoQuit(SDL_VideoDevice *_this)
{
    Wayland_VideoCleanup(_this);

#నిర్వచితమైతే HAVE_LIBDECOR_H
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    ఒకవేళ (దత్తాంశం->shell.libdecor) {
        libdecor_unref(దత్తాంశం->shell.libdecor);
        దత్తాంశం->shell.libdecor = ఖాళీ;
    }
#అయితే_ముగింపు
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_WAYLAND
