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

#अन्तर्भाव "SDL_internal.h"

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WAYLAND

#अन्तर्भाव "../../core/linux/SDL_system_theme.h"
#अन्तर्भाव "../../core/linux/SDL_progressbar.h"
#अन्तर्भाव "../../events/SDL_events_c.h"

#अन्तर्भाव "SDL_waylandclipboard.h"
#अन्तर्भाव "SDL_waylandcolor.h"
#अन्तर्भाव "SDL_waylandevents_c.h"
#अन्तर्भाव "SDL_waylandkeyboard.h"
#अन्तर्भाव "SDL_waylandmessagebox.h"
#अन्तर्भाव "SDL_waylandmouse.h"
#अन्तर्भाव "SDL_waylandopengles.h"
#अन्तर्भाव "SDL_waylandvideo.h"
#अन्तर्भाव "SDL_waylandvulkan.h"
#अन्तर्भाव "SDL_waylandwindow.h"

#अन्तर्भाव <fcntl.h>
#अन्तर्भाव <sys/types.h>
#अन्तर्भाव <unistd.h>
#अन्तर्भाव <errno.h>
#अन्तर्भाव <xkbcommon/xkbcommon.h>

#अन्तर्भाव <wayland-util.h>

#अन्तर्भाव "alpha-modifier-v1-client-protocol.h"
#अन्तर्भाव "cursor-shape-v1-client-protocol.h"
#अन्तर्भाव "fractional-scale-v1-client-protocol.h"
#अन्तर्भाव "frog-color-management-v1-client-protocol.h"
#अन्तर्भाव "idle-inhibit-unstable-v1-client-protocol.h"
#अन्तर्भाव "input-timestamps-unstable-v1-client-protocol.h"
#अन्तर्भाव "keyboard-shortcuts-inhibit-unstable-v1-client-protocol.h"
#अन्तर्भाव "pointer-constraints-unstable-v1-client-protocol.h"
#अन्तर्भाव "primary-selection-unstable-v1-client-protocol.h"
#अन्तर्भाव "relative-pointer-unstable-v1-client-protocol.h"
#अन्तर्भाव "tablet-v2-client-protocol.h"
#अन्तर्भाव "text-input-unstable-v3-client-protocol.h"
#अन्तर्भाव "viewporter-client-protocol.h"
#अन्तर्भाव "xdg-activation-v1-client-protocol.h"
#अन्तर्भाव "xdg-decoration-unstable-v1-client-protocol.h"
#अन्तर्भाव "xdg-dialog-v1-client-protocol.h"
#अन्तर्भाव "xdg-foreign-unstable-v2-client-protocol.h"
#अन्तर्भाव "xdg-output-unstable-v1-client-protocol.h"
#अन्तर्भाव "xdg-shell-client-protocol.h"
#अन्तर्भाव "xdg-toplevel-icon-v1-client-protocol.h"
#अन्तर्भाव "color-management-v1-client-protocol.h"
#अन्तर्भाव "pointer-warp-v1-client-protocol.h"
#अन्तर्भाव "pointer-gestures-unstable-v1-client-protocol.h"
#अन्तर्भाव "single-pixel-buffer-v1-client-protocol.h"
#अन्तर्भाव "xdg-session-management-v1-client-protocol.h"
#अन्तर्भाव "xdg-toplevel-tag-v1-client-protocol.h"

#यदि_परिभाषितम् HAVE_LIBDECOR_H
#अन्तर्भाव <libdecor.h>
#यदि_अन्तः

#परिभाषय WAYLANDVID_DRIVER_NAME "wayland"

// Clamp core protocol versions on older versions of libwayland.
#यदि SDL_WAYLAND_CHECK_संस्करणम्(1, 22, 0)
#परिभाषय SDL_WL_COMPOSITOR_संस्करणम् 6
#अन्यथा
#परिभाषय SDL_WL_COMPOSITOR_संस्करणम् 4
#यदि_अन्तः

#यदि SDL_WAYLAND_CHECK_संस्करणम्(1, 26, 0)
#परिभाषय SDL_WL_SEAT_संस्करणम् 11
#नोचेद्यदि SDL_WAYLAND_CHECK_संस्करणम्(1, 24, 0)
#परिभाषय SDL_WL_SEAT_संस्करणम् 10
#नोचेद्यदि SDL_WAYLAND_CHECK_संस्करणम्(1, 22, 0)
#परिभाषय SDL_WL_SEAT_संस्करणम् 9
#नोचेद्यदि SDL_WAYLAND_CHECK_संस्करणम्(1, 21, 0)
#परिभाषय SDL_WL_SEAT_संस्करणम् 8
#अन्यथा
#परिभाषय SDL_WL_SEAT_संस्करणम् 5
#यदि_अन्तः

#यदि SDL_WAYLAND_CHECK_संस्करणम्(1, 20, 0)
#परिभाषय SDL_WL_OUTPUT_संस्करणम् 4
#अन्यथा
#परिभाषय SDL_WL_OUTPUT_संस्करणम् 3
#यदि_अन्तः

#यदि SDL_WAYLAND_CHECK_संस्करणम्(1, 24, 0)
#परिभाषय SDL_WL_SHM_संस्करणम् 2
#अन्यथा
#परिभाषय SDL_WL_SHM_संस्करणम् 1
#यदि_अन्तः

// The SDL libwayland-client minimum is 1.18, which supports version 3.
#परिभाषय SDL_WL_दत्त_DEVICE_संस्करणम् 3

// wl_fixes was introduced in 1.24.0
#यदि SDL_WAYLAND_CHECK_संस्करणम्(1, 26, 0)
#परिभाषय SDL_WL_FIXES_संस्करणम् 2
#नोचेद्यदि SDL_WAYLAND_CHECK_संस्करणम्(1, 24, 0)
#परिभाषय SDL_WL_FIXES_संस्करणम् 1
#यदि_अन्तः

#यदि_परिभाषितम् SDL_USE_LIBDBUS
#अन्तर्भाव "../../core/linux/SDL_dbus.h"

#परिभाषय DISPLAY_INFO_ग्रन्थिः   "org.gnome.Mutter.DisplayConfig"
#परिभाषय DISPLAY_INFO_मार्गः   "/org/gnome/Mutter/DisplayConfig"
#परिभाषय DISPLAY_INFO_विधानम् "GetCurrentState"
#यदि_अन्तः

/* GNOME doesn't expose displays in any particular order, but we can find the
 * primary display and its logical coordinates via a DBus method.
 */
स्थिर bool Wayland_GetGNOMEPrimaryDisplayCoordinates(पूर्णाङ्क *x, पूर्णाङ्क *y)
{
#यदि_परिभाषितम् SDL_USE_LIBDBUS
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    यदि (dbus == रिक्त) {
        प्रत्यागम false;
    }
    DBus_सन्देशः *प्रत्युत्तरम् = रिक्त;
    DBus_सन्देशः_Iter iter[3];
    DBus_सन्देशः *सन्देशः_2 = dbus->सन्देशः_new_विधानम्_call(DISPLAY_INFO_ग्रन्थिः,
                                                     DISPLAY_INFO_मार्गः,
                                                     DISPLAY_INFO_ग्रन्थिः,
                                                     DISPLAY_INFO_विधानम्);

    यदि (सन्देशः_2) {
        प्रत्युत्तरम् = dbus->connection_send_with_प्रत्युत्तरम्_and_खण्डम्(dbus->session_conn, सन्देशः_2, DBUS_TIMEOUT_USE_DEFAULT, रिक्त);
        dbus->सन्देशः_unref(सन्देशः_2);
    }

    यदि (प्रत्युत्तरम्) {
        // Serial (don't care)
        dbus->सन्देशः_iter_init(प्रत्युत्तरम्, &iter[0]);
        यदि (dbus->सन्देशः_iter_get_arg_type(&iter[0]) != DBUS_TYPE_UINT32) {
            गच्छ error;
        }

        // Physical monitor array (don't care)
        dbus->सन्देशः_iter_अग्र(&iter[0]);
        यदि (dbus->सन्देशः_iter_get_arg_type(&iter[0]) != DBUS_TYPE_ARRAY) {
            गच्छ error;
        }

        // Logical monitor array of structs
        dbus->सन्देशः_iter_अग्र(&iter[0]);
        यदि (dbus->सन्देशः_iter_get_arg_type(&iter[0]) != DBUS_TYPE_ARRAY) {
            गच्छ error;
        }

        // First logical monitor struct
        dbus->सन्देशः_iter_recurse(&iter[0], &iter[1]);
        यदि (dbus->सन्देशः_iter_get_arg_type(&iter[1]) != DBUS_TYPE_STRUCT) {
            गच्छ error;
        }

        कुरु {
            पूर्णाङ्क logical_x, logical_y;
            dbus_bool_t primary;

            // Logical X
            dbus->सन्देशः_iter_recurse(&iter[1], &iter[2]);
            यदि (dbus->सन्देशः_iter_get_arg_type(&iter[2]) != DBUS_TYPE_INT32) {
                गच्छ error;
            }
            dbus->सन्देशः_iter_get_basic(&iter[2], &logical_x);

            // Logical Y
            dbus->सन्देशः_iter_अग्र(&iter[2]);
            यदि (dbus->सन्देशः_iter_get_arg_type(&iter[2]) != DBUS_TYPE_INT32) {
                गच्छ error;
            }
            dbus->सन्देशः_iter_get_basic(&iter[2], &logical_y);

            // Scale (don't care)
            dbus->सन्देशः_iter_अग्र(&iter[2]);
            यदि (dbus->सन्देशः_iter_get_arg_type(&iter[2]) != DBUS_TYPE_DOUBLE) {
                गच्छ error;
            }

            // Transform (don't care)
            dbus->सन्देशः_iter_अग्र(&iter[2]);
            यदि (dbus->सन्देशः_iter_get_arg_type(&iter[2]) != DBUS_TYPE_UINT32) {
                गच्छ error;
            }

            // Primary display boolean
            dbus->सन्देशः_iter_अग्र(&iter[2]);
            यदि (dbus->सन्देशः_iter_get_arg_type(&iter[2]) != DBUS_TYPE_BOOLEAN) {
                गच्छ error;
            }
            dbus->सन्देशः_iter_get_basic(&iter[2], &primary);

            यदि (primary) {
                *x = logical_x;
                *y = logical_y;

                // We found the primary display: success.
                dbus->सन्देशः_unref(प्रत्युत्तरम्);
                प्रत्यागम true;
            }
        } यावत् (dbus->सन्देशः_iter_अग्र(&iter[1]));
    }

error:
    यदि (प्रत्युत्तरम्) {
        dbus->सन्देशः_unref(प्रत्युत्तरम्);
    }
#यदि_अन्तः
    प्रत्यागम false;
}

// Sort the list of displays into a deterministic order
स्थिर पूर्णाङ्क SDLCALL Wayland_DisplayPositionCompare(ध्रुव शून्य *a, ध्रुव शून्य *b)
{
    ध्रुव SDL_Display_दत्त *da = *(SDL_Display_दत्त **)a;
    ध्रुव SDL_Display_दत्त *db = *(SDL_Display_दत्त **)b;
    ध्रुव bool a_at_origin = da->logical.x == 0 && da->logical.y == 0;
    ध्रुव bool b_at_origin = db->logical.x == 0 && db->logical.y == 0;

    // Sort the display at 0,0 to be beginning of the list, as that will be the fallback primary.
    यदि (a_at_origin && !b_at_origin) {
        प्रत्यागम -1;
    }
    यदि (b_at_origin && !a_at_origin) {
        प्रत्यागम 1;
    }

    यदि (da->logical.x < db->logical.x) {
        प्रत्यागम -1;
    }
    यदि (da->logical.x > db->logical.x) {
        प्रत्यागम 1;
    }
    यदि (da->logical.y < db->logical.y) {
        प्रत्यागम -1;
    }
    यदि (da->logical.y > db->logical.y) {
        प्रत्यागम 1;
    }

    // If no position information is available, use the connector name.
    यदि (da->wl_output_name && db->wl_output_name) {
        प्रत्यागम SDL_strcmp(da->wl_output_name, db->wl_output_name);
    }

    प्रत्यागम 0;
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
स्थिर पूर्णाङ्क Wayland_GetPrimaryDisplay(SDL_Video_दत्त *vid)
{
    स्थिर ध्रुव पूर्णाङ्क REFRESH_DELTA = 4000;

    // Query the DBus interface to see if the coordinates of the primary display are exposed.
    पूर्णाङ्क x, y;
    यदि (Wayland_GetGNOMEPrimaryDisplayCoordinates(&x, &y)) {
        प्रति (पूर्णाङ्क i = 0; i < vid->output_गणनम्; ++i) {
            यदि (vid->output_list[i]->logical.x == x && vid->output_list[i]->logical.y == y) {
                प्रत्यागम i;
            }
        }
    }

    // Otherwise, choose the 'best' display.
    पूर्णाङ्क best_विस्तारः = 0;
    पूर्णाङ्क best_height = 0;
    द्विगुण best_scale = 0.0;
    भिन्न best_headroom = 0.0f;
    पूर्णाङ्क best_refresh = 0;
    bool best_is_landscape = false;
    पूर्णाङ्क best_सूचकांक = 0;

    प्रति (पूर्णाङ्क i = 0; i < vid->output_गणनम्; ++i) {
        ध्रुव SDL_Display_दत्त *d = vid->output_list[i];
        ध्रुव bool is_landscape = d->orientation != SDL_ORIENTATION_PORTRAIT && d->orientation != SDL_ORIENTATION_PORTRAIT_FLIPPED;
        bool have_new_best = false;

        यदि (!best_is_landscape && is_landscape) { // Favor landscape over portrait displays.
            have_new_best = true;
        } अन्यथा यदि (!best_is_landscape || is_landscape) { // Ignore portrait displays if a landscape was already found.
            यदि (d->pixel.विस्तारः > best_विस्तारः || d->pixel.height > best_height) {
                have_new_best = true;
            } अन्यथा यदि (d->pixel.विस्तारः == best_विस्तारः && d->pixel.height == best_height) {
                यदि (d->HDR.HDR_headroom > best_headroom) { // Favor a higher HDR luminance range
                    have_new_best = true;
                } अन्यथा यदि (d->HDR.HDR_headroom == best_headroom) {
                    यदि (d->refresh - best_refresh > REFRESH_DELTA) { // Favor a higher refresh rate, but ignore small differences (e.g. 59.97 vs 60.1)
                        have_new_best = true;
                    } अन्यथा यदि (d->scale_गुणकः_2 < best_scale && SDL_abs(d->refresh - best_refresh) <= REFRESH_DELTA) {
                        // Prefer a lower scale display if the difference in refresh rate is small.
                        have_new_best = true;
                    }
                }
            }
        }

        यदि (have_new_best) {
            best_विस्तारः = d->pixel.विस्तारः;
            best_height = d->pixel.height;
            best_scale = d->scale_गुणकः_2;
            best_headroom = d->HDR.HDR_headroom;
            best_refresh = d->refresh;
            best_is_landscape = is_landscape;
            best_सूचकांक = i;
        }
    }

    प्रत्यागम best_सूचकांक;
}

स्थिर शून्य Wayland_क्रमय_Outputs_By_प्राथमिकता_Hint(SDL_Video_दत्त *vid)
{
    ध्रुव वर्ण *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_प्राथमिकता);

    यदि (name_hint) {
        वर्ण *saveptr;
        वर्ण *str = SDL_strdup(name_hint);
        SDL_Display_दत्त **sorted_list = SDL_malloc(परिमाण(SDL_Display_दत्त *) * vid->output_गणनम्);

        यदि (str && sorted_list) {
            पूर्णाङ्क sorted_सूचकांक = 0;

            // Sort the requested displays to the front of the list.
            ध्रुव वर्ण *token = SDL_strtok_r(str, ",", &saveptr);
            यावत् (token) {
                प्रति (पूर्णाङ्क i = 0; i < vid->output_गणनम्; ++i) {
                    SDL_Display_दत्त *d = vid->output_list[i];
                    यदि (d && d->wl_output_name && SDL_strcmp(token, d->wl_output_name) == 0) {
                        sorted_list[sorted_सूचकांक++] = d;
                        vid->output_list[i] = रिक्त;
                        भङ्ग;
                    }
                }

                token = SDL_strtok_r(रिक्त, ",", &saveptr);
            }

            // Append the remaining outputs to the end of the list.
            प्रति (पूर्णाङ्क i = 0; i < vid->output_गणनम्; ++i) {
                यदि (vid->output_list[i]) {
                    sorted_list[sorted_सूचकांक++] = vid->output_list[i];
                }
            }

            // Copy the sorted list to the output list.
            SDL_memcpy(vid->output_list, sorted_list, परिमाण(SDL_Display_दत्त *) * vid->output_गणनम्);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

स्थिर शून्य Wayland_DeriveOutputPixelCoordinates(SDL_Video_दत्त *vid)
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
    प्रति ( पूर्णाङ्क i = 0; i < vid->output_गणनम्; ++i) {
        SDL_Display_दत्त *d = vid->output_list[i];
        d->pixel.x = d->logical.x;
        d->pixel.y = d->logical.y;
    }

    प्रति (पूर्णाङ्क i = 0; i < vid->output_गणनम्; ++i) {
        SDL_Display_दत्त *d1 = vid->output_list[i];
        यदि (d1->logical.विस्तारः != d1->pixel.विस्तारः || d1->logical.height != d1->pixel.height) {
            ध्रुव पूर्णाङ्क x_adj = d1->pixel.विस्तारः - d1->logical.विस्तारः;
            ध्रुव पूर्णाङ्क y_adj = d1->pixel.height - d1->logical.height;

            // Don't adjust for scale values less than 1.0.
            यदि (x_adj > 0 && y_adj > 0) {
                प्रति (पूर्णाङ्क j = 0; j < vid->output_गणनम्; ++j) {
                    SDL_Display_दत्त *d2 = vid->output_list[j];
                    यदि (d2->logical.x > d1->logical.x) {
                        d2->pixel.x += x_adj;
                    }
                    यदि (d2->logical.y > d1->logical.y) {
                        d2->pixel.y += y_adj;
                    }
                }
            }
        }
    }
}

स्थिर शून्य Wayland_क्रमय_Outputs(SDL_Video_दत्त *vid)
{
    // Sort by position or connector name, so the order of outputs is deterministic.
    SDL_qsort(vid->output_list, vid->output_गणनम्, परिमाण(SDL_Display_दत्त *), Wayland_DisplayPositionCompare);

    // Derive the output pixel coordinates if scale to display is enabled.
    यदि (vid->scale_गन्तव्यम्_display_enabled) {
        Wayland_DeriveOutputPixelCoordinates(vid);
    }

    // Find a suitable primary display and move it to the front of the list.
    ध्रुव पूर्णाङ्क primary_सूचकांक = Wayland_GetPrimaryDisplay(vid);
    यदि (primary_सूचकांक) {
        SDL_Display_दत्त *primary = vid->output_list[primary_सूचकांक];
        SDL_memmove(&vid->output_list[1], &vid->output_list[0], परिमाण(SDL_Display_दत्त *) * primary_सूचकांक);
        vid->output_list[0] = primary;
    }

    // Apply the ordering hint, if specified.
    Wayland_क्रमय_Outputs_By_प्राथमिकता_Hint(vid);
}

स्थिर शून्य Wayland_Refresh_गवाक्षः_Positions()
{
    SDL_VideoDevice *vid = SDL_GetVideoDevice();

    प्रति (SDL_गवाक्षः *w = vid->windows; w; w = w->अग्र) {
        Wayland_Update_गवाक्षः_Position(w);
    }
}

स्थिर शून्य handle_wl_output_समाप्तम्(शून्य *दत्त, संरचना wl_output *output);

// Initialization/Query functions
स्थिर bool Wayland_VideoInit(SDL_VideoDevice *_this);
स्थिर bool Wayland_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
स्थिर शून्य Wayland_VideoQuit(SDL_VideoDevice *_this);

स्थिर ध्रुव वर्ण *SDL_WAYLAND_surface_चिह्नकम् = "sdl-window";
स्थिर ध्रुव वर्ण *SDL_WAYLAND_output_चिह्नकम् = "sdl-output";

शून्य SDL_WAYLAND_पञ्जिकाकोशः_surface(संरचना wl_surface *surface)
{
    wl_proxy_समुच्चयः_चिह्नकम्((संरचना wl_proxy *)surface, &SDL_WAYLAND_surface_चिह्नकम्);
}

शून्य SDL_WAYLAND_पञ्जिकाकोशः_output(संरचना wl_output *output)
{
    wl_proxy_समुच्चयः_चिह्नकम्((संरचना wl_proxy *)output, &SDL_WAYLAND_output_चिह्नकम्);
}

bool SDL_WAYLAND_own_surface(संरचना wl_surface *surface)
{
    प्रत्यागम wl_proxy_get_चिह्नकम्((संरचना wl_proxy *)surface) == &SDL_WAYLAND_surface_चिह्नकम्;
}

bool SDL_WAYLAND_own_output(संरचना wl_output *output)
{
    प्रत्यागम wl_proxy_get_चिह्नकम्((संरचना wl_proxy *)output) == &SDL_WAYLAND_output_चिह्नकम्;
}

/* External surfaces may have their own user data attached, the modification of which
 * can cause problems with external toolkits. Instead, external windows are kept in
 * their own list, and a search is conducted to find a matching surface.
 */
स्थिर संरचना wl_list external_गवाक्षः_list;

शून्य Wayland_सङ्कलय_गवाक्षः_दत्त_गन्तव्यम्_External_List(SDL_गवाक्षः_दत्त *दत्त)
{
    WAYLAND_wl_list_निवेशय(&external_गवाक्षः_list, &दत्त->external_गवाक्षः_list_link);
}

शून्य Wayland_Remove_गवाक्षः_दत्त_From_External_List(SDL_गवाक्षः_दत्त *दत्त)
{
    WAYLAND_wl_list_remove(&दत्त->external_गवाक्षः_list_link);
}

SDL_गवाक्षः_दत्त *Wayland_Get_गवाक्षः_दत्त_For_Owned_Surface(संरचना wl_surface *surface)
{
    यदि (SDL_WAYLAND_own_surface(surface)) {
        प्रत्यागम (SDL_गवाक्षः_दत्त *)wl_surface_get_user_दत्त(surface);
    } अन्यथा यदि (!WAYLAND_wl_list_रिक्तानि(&external_गवाक्षः_list)) {
        SDL_गवाक्षः_दत्त *p;
        wl_list_for_each (p, &external_गवाक्षः_list, external_गवाक्षः_list_link) {
            यदि (p->surface == surface) {
                प्रत्यागम p;
            }
        }
    }

    प्रत्यागम रिक्त;
}

संरचना wl_event_queue *Wayland_DisplayCreateQueue(संरचना wl_display *display, ध्रुव वर्ण *name)
{
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
    यदि (WAYLAND_wl_display_create_queue_with_name) {
        प्रत्यागम WAYLAND_wl_display_create_queue_with_name(display, name);
    }
#नोचेद्यदि SDL_WAYLAND_CHECK_संस्करणम्(1, 23, 0)
    प्रत्यागम WAYLAND_wl_display_create_queue_with_name(display, name);
#यदि_अन्तः
    प्रत्यागम WAYLAND_wl_display_create_queue(display);
}

स्थिर शून्य Wayland_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_Video_दत्त *दत्त = device->आन्तरिकम्;
    यदि (दत्त->display && !दत्त->display_externally_owned) {
        WAYLAND_wl_display_disconnect(दत्त->display);
        SDL_ClearProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_POINTER);
    }
    SDL_free(दत्त);
    SDL_free(device);
    SDL_WAYLAND_UnloadSymbols();
}

प्रकारनिर्देश संरचना
{
    bool has_fifo_v1;
    संरचना wl_fixes *wl_fixes;
} SDL_Wayland_Preferred_दत्त;

स्थिर शून्य wayland_preferred_check_handle_global(शून्य *दत्त, संरचना wl_registry *registry, uint32_t id,
                                                  ध्रुव वर्ण *interface, uint32_t संस्करणम्)
{
    SDL_Wayland_Preferred_दत्त *d = दत्त;

    यदि (SDL_strcmp(interface, "wp_fifo_manager_v1") == 0) {
        d->has_fifo_v1 = true;
    }
#यदि_परिभाषितम् SDL_WL_FIXES_संस्करणम्
    अन्यथा यदि (SDL_strcmp(interface, wl_fixes_interface.name) == 0) {
        d->wl_fixes = wl_registry_bind(registry, id, &wl_fixes_interface, SDL_min(SDL_WL_FIXES_संस्करणम्, संस्करणम्));
    }
#यदि_अन्तः
}

स्थिर शून्य wayland_preferred_check_remove_global(शून्य *दत्त, संरचना wl_registry *registry, uint32_t id)
{
    SDL_Wayland_Preferred_दत्त *d = (SDL_Wayland_Preferred_दत्त *)दत्त;

    यदि (d->wl_fixes && wl_fixes_get_संस्करणम्(d->wl_fixes) >= WL_FIXES_ACK_GLOBAL_REMOVE_SINCE_संस्करणम्) {
        wl_fixes_ack_global_remove(d->wl_fixes, registry, id);
    }
}

स्थिर ध्रुव संरचना wl_registry_listener preferred_registry_listener = {
    wayland_preferred_check_handle_global,
    wayland_preferred_check_remove_global
};

स्थिर bool Wayland_IsPreferred(संरचना wl_display *display)
{
    संरचना wl_registry *registry = wl_display_get_registry(display);
    SDL_Wayland_Preferred_दत्त preferred_दत्त = { 0 };

    यदि (!registry) {
        SDL_समुच्चयः_Error("Failed to get the Wayland registry");
        प्रत्यागम false;
    }

    wl_registry_सङ्कलय_listener(registry, &preferred_registry_listener, &preferred_दत्त);

    WAYLAND_wl_display_roundtrip(display);

    यदि (preferred_दत्त.wl_fixes) {
        wl_fixes_destroy_registry(preferred_दत्त.wl_fixes, registry);
        wl_fixes_destroy(preferred_दत्त.wl_fixes);
    }
    wl_registry_destroy(registry);

    यदि (!preferred_दत्त.has_fifo_v1) {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "This compositor lacks support for the fifo-v1 protocol; falling back to XWayland for GPU performance reasons (set SDL_VIDEO_DRIVER=wayland to override)");
    }
    प्रत्यागम preferred_दत्त.has_fifo_v1;
}

स्थिर SDL_VideoDevice *Wayland_CreateDevice(bool require_preferred_protocols)
{
    SDL_VideoDevice *device;
    SDL_Video_दत्त *दत्त;
    संरचना wl_display *display = SDL_GetPointerProperty(SDL_GetGlobalProperties(),
                                                 SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_POINTER, रिक्त);
    bool display_is_external = !!display;

    // Are we trying to connect to, or are currently in, a Wayland session?
    यदि (!SDL_getenv("WAYLAND_DISPLAY")) {
        ध्रुव वर्ण *session = SDL_getenv("XDG_SESSION_TYPE");
        यदि (session && SDL_strcasecmp(session, "wayland") != 0) {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Wayland initialization failed: no Wayland session available");
            प्रत्यागम रिक्त;
        }
    }

    यदि (!SDL_WAYLAND_आरोपय_Symbols()) {
        प्रत्यागम रिक्त;
    }

    यदि (!display) {
        display = WAYLAND_wl_display_connect(रिक्त);
        यदि (!display) {
            SDL_WAYLAND_UnloadSymbols();
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to connect to the Wayland display server: %s", strerror(errno));
            प्रत्यागम रिक्त;
        }
    }

    /*
     * If we are checking for preferred Wayland, then let's query for
     * fifo-v1's existence, so we don't regress GPU-bound performance
     * and frame-pacing by default due to swapchain starvation.
     */
    यदि (require_preferred_protocols && !Wayland_IsPreferred(display)) {
        यदि (!display_is_external) {
            WAYLAND_wl_display_disconnect(display);
        }
        SDL_WAYLAND_UnloadSymbols();
        प्रत्यागम रिक्त;
    }

    दत्त = SDL_calloc(1, परिमाण(*दत्त));
    यदि (!दत्त) {
        यदि (!display_is_external) {
            WAYLAND_wl_display_disconnect(display);
        }
        SDL_WAYLAND_UnloadSymbols();
        प्रत्यागम रिक्त;
    }

    दत्त->initializing = true;
    दत्त->display = display;
    दत्त->display_externally_owned = display_is_external;
    दत्त->scale_गन्तव्यम्_display_enabled = SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_SCALE_गन्तव्यम्_DISPLAY, false);
    WAYLAND_wl_list_init(&दत्त->seat_list);
    WAYLAND_wl_list_init(&external_गवाक्षः_list);

    // Initialize all variables that we clean on shutdown
    device = SDL_calloc(1, परिमाण(SDL_VideoDevice));
    यदि (!device) {
        SDL_free(दत्त);
        यदि (!display_is_external) {
            WAYLAND_wl_display_disconnect(display);
        }
        SDL_WAYLAND_UnloadSymbols();
        प्रत्यागम रिक्त;
    }

    यदि (!display_is_external) {
        SDL_समुच्चयः_Pointer_Property(SDL_GetGlobalProperties(),
                               SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_POINTER, display);
    }

    device->आन्तरिकम् = दत्त;

    // Set the function pointers
    device->VideoInit = Wayland_VideoInit;
    device->VideoQuit = Wayland_VideoQuit;
    device->GetDisplayBounds = Wayland_GetDisplayBounds;
    device->SuspendScreenSaver = Wayland_SuspendScreenSaver;

    device->PumpEvents = Wayland_PumpEvents;
    device->WaitEventTimeout = Wayland_WaitEventTimeout;
    device->SendWakeupEvent = Wayland_SendWakeupEvent;

#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
    device->GL_Swap_गवाक्षः = Wayland_GLES_Swap_गवाक्षः;
    device->GL_GetSwapInterval = Wayland_GLES_GetSwapInterval;
    device->GL_समुच्चयः_Swap_Interval = Wayland_GLES_समुच्चयः_Swap_Interval;
    device->GL_MakeCurrent = Wayland_GLES_MakeCurrent;
    device->GL_CreateContext = Wayland_GLES_CreateContext;
    device->GL_आरोपय_Library = Wayland_GLES_आरोपय_Library;
    device->GL_UnloadLibrary = Wayland_GLES_UnloadLibrary;
    device->GL_Get_Proc_स्थानाङ्कः = Wayland_GLES_Get_Proc_स्थानाङ्कः;
    device->GL_DestroyContext = Wayland_GLES_DestroyContext;
    device->GL_समुच्चयः_Default_Profile_Config = Wayland_GLES_समुच्चयः_Default_Profile_Config;
    device->GL_GetEGLSurface = Wayland_GLES_GetEGLSurface;
#यदि_अन्तः

    device->CreateSDLWindow = Wayland_Create_गवाक्षः;
    device->Show_गवाक्षः = Wayland_Show_गवाक्षः;
    device->Hide_गवाक्षः = Wayland_Hide_गवाक्षः;
    device->Raise_गवाक्षः = Wayland_Raise_गवाक्षः;
    device->समुच्चयः_गवाक्षः_Fullscreen = Wayland_समुच्चयः_गवाक्षः_Fullscreen;
    device->Maximize_गवाक्षः = Wayland_Maximize_गवाक्षः;
    device->Minimize_गवाक्षः = Wayland_Minimize_गवाक्षः;
    device->समुच्चयः_गवाक्षः_Mouse_Rect = Wayland_समुच्चयः_गवाक्षः_Mouse_Rect;
    device->समुच्चयः_गवाक्षः_Mouse_Grab = Wayland_समुच्चयः_गवाक्षः_Mouse_Grab;
    device->समुच्चयः_गवाक्षः_Keyboard_Grab = Wayland_समुच्चयः_गवाक्षः_Keyboard_Grab;
    device->Restore_गवाक्षः = Wayland_Restore_गवाक्षः;
    device->समुच्चयः_गवाक्षः_Bordered = Wayland_समुच्चयः_गवाक्षः_Bordered;
    device->समुच्चयः_गवाक्षः_Resizable = Wayland_समुच्चयः_गवाक्षः_Resizable;
    device->समुच्चयः_गवाक्षः_Position = Wayland_समुच्चयः_गवाक्षः_Position;
    device->समुच्चयः_गवाक्षः_आकार = Wayland_समुच्चयः_गवाक्षः_आकार;
    device->समुच्चयः_गवाक्षः_Aspect_अनुपातः = Wayland_समुच्चयः_गवाक्षः_Aspect_अनुपातः;
    device->समुच्चयः_गवाक्षः_Minimum_आकार = Wayland_समुच्चयः_गवाक्षः_Minimum_आकार;
    device->समुच्चयः_गवाक्षः_अधिकतमम्_आकार = Wayland_समुच्चयः_गवाक्षः_अधिकतमम्_आकार;
    device->समुच्चयः_गवाक्षः_Parent = Wayland_समुच्चयः_गवाक्षः_Parent;
    device->समुच्चयः_गवाक्षः_Modal = Wayland_समुच्चयः_गवाक्षः_Modal;
    device->समुच्चयः_गवाक्षः_Opacity = Wayland_समुच्चयः_गवाक्षः_Opacity;
    device->समुच्चयः_गवाक्षः_Title = Wayland_समुच्चयः_गवाक्षः_Title;
    device->समुच्चयः_गवाक्षः_Icon = Wayland_समुच्चयः_गवाक्षः_Icon;
    device->Get_गवाक्षः_आकार_अन्तर्_Pixels = Wayland_Get_गवाक्षः_आकार_अन्तर्_Pixels;
    device->Get_गवाक्षः_Content_Scale = Wayland_Get_गवाक्षः_Content_Scale;
    device->Get_गवाक्षः_ICCProfile = Wayland_Get_गवाक्षः_ICCProfile;
    device->Get_Display_For_गवाक्षः = Wayland_Get_Display_For_गवाक्षः;
    device->Destroy_गवाक्षः = Wayland_Destroy_गवाक्षः;
    device->समुच्चयः_गवाक्षः_लब्धम्_Test = Wayland_समुच्चयः_गवाक्षः_लब्धम्_Test;
    device->Flash_गवाक्षः = Wayland_Flash_गवाक्षः;
#यदि_परिभाषितम् SDL_USE_LIBDBUS
    device->Apply_गवाक्षः_प्रगतिः = DBUS_Apply_गवाक्षः_प्रगतिः;
#यदि_अन्तः // SDL_USE_LIBDBUS
    device->HasScreenKeyboardSupport = Wayland_HasScreenKeyboardSupport;
    device->Show_गवाक्षः_System_Menu = Wayland_Show_गवाक्षः_System_Menu;
    device->Sync_गवाक्षः = Wayland_Sync_गवाक्षः;
    device->समुच्चयः_गवाक्षः_Focusable = Wayland_समुच्चयः_गवाक्षः_Focusable;
    device->Reconfigure_गवाक्षः = Wayland_Reconfigure_गवाक्षः;
    device->AcceptDragAndDrop = Wayland_AcceptDragAndDrop;

#यदि_परिभाषितम् SDL_USE_LIBDBUS
    यदि (SDL_SystemTheme_Init())
        device->system_theme = SDL_SystemTheme_Get();
#यदि_अन्तः

    device->GetTextMimeTypes = Wayland_GetTextMimeTypes;
    device->समुच्चयः_Clipboard_दत्त = Wayland_समुच्चयः_Clipboard_दत्त;
    device->Get_Clipboard_दत्त = Wayland_Get_Clipboard_दत्त;
    device->Has_Clipboard_दत्त = Wayland_Has_Clipboard_दत्त;
    device->Start_Text_निवेशः = Wayland_Start_Text_निवेशः;
    device->Stop_Text_निवेशः = Wayland_Stop_Text_निवेशः;
    device->Update_Text_निवेशः_Area = Wayland_Update_Text_निवेशः_Area;

#यदि_परिभाषितम् SDL_VIDEO_VULKAN
    device->Vulkan_आरोपय_Library = Wayland_Vulkan_आरोपय_Library;
    device->Vulkan_UnloadLibrary = Wayland_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = Wayland_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = Wayland_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = Wayland_Vulkan_DestroySurface;
    device->Vulkan_GetPresentationSupport = Wayland_Vulkan_GetPresentationSupport;
#यदि_अन्तः

    device->मुक्त = Wayland_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_बहुलकम्_SWITCHING_EMULATED |
                          VIDEO_DEVICE_CAPS_HAS_POPUP_गवाक्षः_SUPPORT |
                          VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS |
                          VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES |
                          VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES;

    प्रत्यागम device;
}

स्थिर SDL_VideoDevice *Wayland_Preferred_CreateDevice(शून्य)
{
    प्रत्यागम Wayland_CreateDevice(true);
}

स्थिर SDL_VideoDevice *Wayland_Fallback_CreateDevice(शून्य)
{
    प्रत्यागम Wayland_CreateDevice(false);
}

VideoBootStrap Wayland_preferred_bootstrap = {
    WAYLANDVID_DRIVER_NAME, "SDL Wayland video driver",
    Wayland_Preferred_CreateDevice,
    Wayland_Show_सन्देशः_Box,
    true
};

VideoBootStrap Wayland_bootstrap = {
    WAYLANDVID_DRIVER_NAME, "SDL Wayland video driver",
    Wayland_Fallback_CreateDevice,
    Wayland_Show_सन्देशः_Box,
    false
};

स्थिर शून्य handle_xdg_output_logical_position(शून्य *दत्त, संरचना zxdg_output_v1 *xdg_output, int32_t x, int32_t y)
{
    SDL_Display_दत्त *आन्तरिकम् = (SDL_Display_दत्त *)दत्त;

    आन्तरिकम्->geometry_परिवर्तितम् |= आन्तरिकम्->logical.x != x || आन्तरिकम्->logical.y != y;
    आन्तरिकम्->logical.x = x;
    आन्तरिकम्->logical.y = y;
    आन्तरिकम्->has_logical_position = true;
}

स्थिर शून्य handle_xdg_output_logical_आकार(शून्य *दत्त, संरचना zxdg_output_v1 *xdg_output, int32_t विस्तारः, int32_t height)
{
    SDL_Display_दत्त *आन्तरिकम् = (SDL_Display_दत्त *)दत्त;

    आन्तरिकम्->geometry_परिवर्तितम् |= आन्तरिकम्->logical.विस्तारः != विस्तारः || आन्तरिकम्->logical.height != height;
    आन्तरिकम्->logical.विस्तारः = विस्तारः;
    आन्तरिकम्->logical.height = height;
    आन्तरिकम्->has_logical_आकार = true;
}

स्थिर शून्य handle_xdg_output_समाप्तम्(शून्य *दत्त, संरचना zxdg_output_v1 *xdg_output)
{
    SDL_Display_दत्त *आन्तरिकम् = दत्त;

    /*
     * xdg-output.done events are deprecated and only apply below version 3 of the protocol.
     * A wl-output.done event will be emitted in version 3 or higher.
     */
    यदि (zxdg_output_v1_get_संस्करणम्(आन्तरिकम्->xdg_output) < 3) {
        handle_wl_output_समाप्तम्(दत्त, आन्तरिकम्->output);
    }
}

स्थिर शून्य handle_xdg_output_name(शून्य *दत्त, संरचना zxdg_output_v1 *xdg_output, ध्रुव वर्ण *name)
{
    SDL_Display_दत्त *आन्तरिकम् = (SDL_Display_दत्त *)दत्त;

    // Deprecated as of wl_output v4.
    यदि (wl_output_get_संस्करणम्(आन्तरिकम्->output) < WL_OUTPUT_NAME_SINCE_संस्करणम् &&
        आन्तरिकम्->display == 0) {
        SDL_free(आन्तरिकम्->wl_output_name);
        आन्तरिकम्->wl_output_name = SDL_strdup(name);
    }
}

स्थिर शून्य handle_xdg_output_description(शून्य *दत्त, संरचना zxdg_output_v1 *xdg_output, ध्रुव वर्ण *description)
{
    SDL_Display_दत्त *आन्तरिकम् = (SDL_Display_दत्त *)दत्त;

    // Deprecated as of wl_output v4.
    यदि (wl_output_get_संस्करणम्(आन्तरिकम्->output) < WL_OUTPUT_DESCRIPTION_SINCE_संस्करणम् &&
        आन्तरिकम्->display == 0) {
        // xdg-output descriptions, if available, supersede wl-output model names.
        SDL_free(आन्तरिकम्->placeholder.name);
        आन्तरिकम्->placeholder.name = SDL_strdup(description);
    }
}

स्थिर ध्रुव संरचना zxdg_output_v1_listener xdg_output_listener = {
    handle_xdg_output_logical_position,
    handle_xdg_output_logical_आकार,
    handle_xdg_output_समाप्तम्,
    handle_xdg_output_name,
    handle_xdg_output_description,
};

स्थिर शून्य सङ्कलय_Emulated_Modes(SDL_Display_दत्त *dispdata, पूर्णाङ्क native_विस्तारः, पूर्णाङ्क native_height)
{
    संरचना Emulated_बहुलकम्
    {
        पूर्णाङ्क w;
        पूर्णाङ्क h;
    };

    // Resolution lists courtesy of XWayland
    ध्रुव संरचना Emulated_बहुलकम् बहुलकम्_list[] = {
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

    पूर्णाङ्क i;
    SDL_Display_बहुलकम् बहुलकम्;
    SDL_VideoDisplay *dpy = dispdata->display ? SDL_GetVideoDisplay(dispdata->display) : &dispdata->placeholder;
    ध्रुव bool rot_90 = native_विस्तारः < native_height; // Reverse width/height for portrait displays.

    प्रति (i = 0; i < SDL_arraysize(बहुलकम्_list); ++i) {
        SDL_zero(बहुलकम्);
        बहुलकम्.format = dpy->desktop_बहुलकम्.format;
        बहुलकम्.refresh_दरः_numerator = dpy->desktop_बहुलकम्.refresh_दरः_numerator;
        बहुलकम्.refresh_दरः_denominator = dpy->desktop_बहुलकम्.refresh_दरः_denominator;

        यदि (rot_90) {
            बहुलकम्.w = बहुलकम्_list[i].h;
            बहुलकम्.h = बहुलकम्_list[i].w;
        } अन्यथा {
            बहुलकम्.w = बहुलकम्_list[i].w;
            बहुलकम्.h = बहुलकम्_list[i].h;
        }

        // Only add modes that are smaller than the native mode.
        यदि ((बहुलकम्.w < native_विस्तारः && बहुलकम्.h < native_height) ||
            (बहुलकम्.w < native_विस्तारः && बहुलकम्.h == native_height) ||
            (बहुलकम्.w == native_विस्तारः && बहुलकम्.h < native_height)) {
            SDL_सङ्कलय_Fullscreen_Display_बहुलकम्(dpy, &बहुलकम्);
        }
    }
}

स्थिर शून्य handle_wl_output_geometry(शून्य *दत्त, संरचना wl_output *output, पूर्णाङ्क x, पूर्णाङ्क y,
                                      पूर्णाङ्क physical_विस्तारः_2, पूर्णाङ्क physical_height, पूर्णाङ्क subpixel,
                                      ध्रुव वर्ण *make, ध्रुव वर्ण *model, पूर्णाङ्क transform)
{
    SDL_Display_दत्त *आन्तरिकम् = (SDL_Display_दत्त *)दत्त;

    // Apply the change from wl-output only if xdg-output is not supported
    यदि (!आन्तरिकम्->has_logical_position) {
        आन्तरिकम्->geometry_परिवर्तितम् |= आन्तरिकम्->logical.x != x || आन्तरिकम्->logical.y != y;
        आन्तरिकम्->logical.x = x;
        आन्तरिकम्->logical.y = y;
    }
    आन्तरिकम्->physical.विस्तारः_mm = physical_विस्तारः_2;
    आन्तरिकम्->physical.height_mm = physical_height;

    // The model is only used for the output name if wl_output or xdg-output haven't provided a description.
    यदि (आन्तरिकम्->display == 0 && !आन्तरिकम्->placeholder.name) {
        आन्तरिकम्->placeholder.name = SDL_strdup(model);
    }

    आन्तरिकम्->transform = transform;
#परिभाषय TF_CASE(अन्तर्_2, बहिर्गमनम्)                                 \
    पक्ष WL_OUTPUT_TRANSFORM_##in:                       \
        आन्तरिकम्->orientation = SDL_ORIENTATION_##out; \
        भङ्ग;
    यदि (आन्तरिकम्->physical.विस्तारः_mm >= आन्तरिकम्->physical.height_mm) {
        विकल्प (transform) {
            TF_CASE(प्रसामान्यम्_2, LANDSCAPE)
            TF_CASE(90, PORTRAIT)
            TF_CASE(180, LANDSCAPE_FLIPPED)
            TF_CASE(270, PORTRAIT_FLIPPED)
            TF_CASE(FLIPPED, LANDSCAPE_FLIPPED)
            TF_CASE(FLIPPED_90, PORTRAIT_FLIPPED)
            TF_CASE(FLIPPED_180, LANDSCAPE)
            TF_CASE(FLIPPED_270, PORTRAIT)
        }
    } अन्यथा {
        विकल्प (transform) {
            TF_CASE(प्रसामान्यम्_2, PORTRAIT)
            TF_CASE(90, LANDSCAPE)
            TF_CASE(180, PORTRAIT_FLIPPED)
            TF_CASE(270, LANDSCAPE_FLIPPED)
            TF_CASE(FLIPPED, PORTRAIT_FLIPPED)
            TF_CASE(FLIPPED_90, LANDSCAPE_FLIPPED)
            TF_CASE(FLIPPED_180, PORTRAIT)
            TF_CASE(FLIPPED_270, LANDSCAPE)
        }
    }
#अपरिभाषय TF_CASE
}

स्थिर शून्य handle_wl_output_बहुलकम्(शून्य *दत्त, संरचना wl_output *output, uint32_t flags,
                                  पूर्णाङ्क विस्तारः, पूर्णाङ्क height, पूर्णाङ्क refresh)
{
    SDL_Display_दत्त *आन्तरिकम् = (SDL_Display_दत्त *)दत्त;

    यदि (flags & WL_OUTPUT_बहुलकम्_CURRENT) {
        आन्तरिकम्->geometry_परिवर्तितम् |= आन्तरिकम्->pixel.विस्तारः != विस्तारः || आन्तरिकम्->pixel.height != height;
        आन्तरिकम्->pixel.विस्तारः = विस्तारः;
        आन्तरिकम्->pixel.height = height;

        /*
         * Don't rotate this yet, wl-output coordinates are transformed in
         * handle_done and xdg-output coordinates are pre-transformed.
         */
        यदि (!आन्तरिकम्->has_logical_आकार) {
            आन्तरिकम्->geometry_परिवर्तितम् |= आन्तरिकम्->logical.विस्तारः != विस्तारः || आन्तरिकम्->logical.height != height;
            आन्तरिकम्->logical.विस्तारः = विस्तारः;
            आन्तरिकम्->logical.height = height;
        }

        आन्तरिकम्->refresh = refresh;
    }
}

स्थिर शून्य handle_wl_output_समाप्तम्(शून्य *दत्त, संरचना wl_output *output)
{
    ध्रुव bool बहुलकम्_emulation_enabled = SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_बहुलकम्_EMULATION, true);
    SDL_Display_दत्त *आन्तरिकम् = (SDL_Display_दत्त *)दत्त;
    SDL_Video_दत्त *video = आन्तरिकम्->videodata;
    SDL_Display_बहुलकम् native_बहुलकम्, desktop_बहुलकम्;

    /*
     * When using xdg-output, two wl-output.done events will be emitted:
     * one at the completion of wl-display and one at the completion of xdg-output.
     *
     * All required events must be received before proceeding.
     */
    ध्रुव पूर्णाङ्क event_await_गणनम् = 1 + (आन्तरिकम्->xdg_output != रिक्त);

    आन्तरिकम्->wl_output_समाप्तम्_गणनम् = SDL_min(आन्तरिकम्->wl_output_समाप्तम्_गणनम् + 1, event_await_गणनम् + 1);

    यदि (आन्तरिकम्->wl_output_समाप्तम्_गणनम् < event_await_गणनम्) {
        प्रत्यागम;
    }

    // If the display was already created, reset and rebuild the mode list.
    SDL_VideoDisplay *dpy = SDL_GetVideoDisplay(आन्तरिकम्->display);
    यदि (dpy) {
        SDL_ResetFullscreenDisplayModes(dpy);
    }

    // The native display resolution
    SDL_zero(native_बहुलकम्);
    native_बहुलकम्.format = SDL_PIXELFORMAT_XRGB8888;

    // Transform the pixel values, if necessary.
    यदि (आन्तरिकम्->transform & WL_OUTPUT_TRANSFORM_90) {
        native_बहुलकम्.w = आन्तरिकम्->pixel.height;
        native_बहुलकम्.h = आन्तरिकम्->pixel.विस्तारः;
    } अन्यथा {
        native_बहुलकम्.w = आन्तरिकम्->pixel.विस्तारः;
        native_बहुलकम्.h = आन्तरिकम्->pixel.height;
    }
    native_बहुलकम्.refresh_दरः_numerator = आन्तरिकम्->refresh;
    native_बहुलकम्.refresh_दरः_denominator = 1000;

    यदि (आन्तरिकम्->has_logical_आकार) { // If xdg-output is present...
        यदि (native_बहुलकम्.w != आन्तरिकम्->logical.विस्तारः || native_बहुलकम्.h != आन्तरिकम्->logical.height) {
            // ...and the compositor scales the logical viewport...
            यदि (video->viewporter) {
                // ...and viewports are supported, calculate the true scale of the output.
                आन्तरिकम्->scale_गुणकः_2 = (द्विगुण)native_बहुलकम्.w / (द्विगुण)आन्तरिकम्->logical.विस्तारः;
            } अन्यथा {
                // ...otherwise, the 'native' pixel values are a multiple of the logical screen size.
                आन्तरिकम्->scale_गुणकः_2 = आन्तरिकम्->integer_scale_गुणकः;
                आन्तरिकम्->pixel.विस्तारः = आन्तरिकम्->logical.विस्तारः * आन्तरिकम्->integer_scale_गुणकः;
                आन्तरिकम्->pixel.height = आन्तरिकम्->logical.height * आन्तरिकम्->integer_scale_गुणकः;
            }
        } अन्यथा {
            /* ...and the output viewport is not scaled in the global compositing
             * space, the output dimensions need to be divided by the scale factor.
             *
             * NOTE: This path is needed for old versions of GNOME that predate fractional scaling.
             */
            आन्तरिकम्->scale_गुणकः_2 = आन्तरिकम्->integer_scale_गुणकः;
            आन्तरिकम्->logical.विस्तारः /= आन्तरिकम्->integer_scale_गुणकः;
            आन्तरिकम्->logical.height /= आन्तरिकम्->integer_scale_गुणकः;
        }
    } अन्यथा {
        /* Calculate the points from the pixel values, if xdg-output isn't present.
         * Use the native mode pixel values since they are pre-transformed.
         */
        आन्तरिकम्->scale_गुणकः_2 = आन्तरिकम्->integer_scale_गुणकः;
        आन्तरिकम्->logical.विस्तारः = native_बहुलकम्.w / आन्तरिकम्->integer_scale_गुणकः;
        आन्तरिकम्->logical.height = native_बहुलकम्.h / आन्तरिकम्->integer_scale_गुणकः;
    }

    // The scaled desktop mode
    SDL_zero(desktop_बहुलकम्);
    desktop_बहुलकम्.format = SDL_PIXELFORMAT_XRGB8888;

    यदि (!video->scale_गन्तव्यम्_display_enabled) {
        desktop_बहुलकम्.w = आन्तरिकम्->logical.विस्तारः;
        desktop_बहुलकम्.h = आन्तरिकम्->logical.height;
        desktop_बहुलकम्.pixel_density = (भिन्न)आन्तरिकम्->scale_गुणकः_2;
    } अन्यथा {
        desktop_बहुलकम्.w = native_बहुलकम्.w;
        desktop_बहुलकम्.h = native_बहुलकम्.h;
        desktop_बहुलकम्.pixel_density = 1.0f;
    }

    desktop_बहुलकम्.refresh_दरः_numerator = आन्तरिकम्->refresh;
    desktop_बहुलकम्.refresh_दरः_denominator = 1000;

    यदि (आन्तरिकम्->display > 0) {
        dpy = SDL_GetVideoDisplay(आन्तरिकम्->display);
    } अन्यथा {
        dpy = &आन्तरिकम्->placeholder;
    }

    यदि (video->scale_गन्तव्यम्_display_enabled) {
        SDL_समुच्चयः_Display_Content_Scale(dpy, (भिन्न)आन्तरिकम्->scale_गुणकः_2);
    }

    // Set the desktop display mode.
    SDL_समुच्चयः_Desktop_Display_बहुलकम्(dpy, &desktop_बहुलकम्);

    // Expose the unscaled, native resolution if the scale is 1.0 or viewports are available...
    यदि (आन्तरिकम्->scale_गुणकः_2 == 1.0 || video->viewporter) {
        SDL_सङ्कलय_Fullscreen_Display_बहुलकम्(dpy, &native_बहुलकम्);
        यदि (native_बहुलकम्.w != desktop_बहुलकम्.w ||
            native_बहुलकम्.h != desktop_बहुलकम्.h) {
            SDL_सङ्कलय_Fullscreen_Display_बहुलकम्(dpy, &desktop_बहुलकम्);
        }
    } अन्यथा {
        // ...otherwise expose the integer scaled variants of the desktop resolution down to 1.
        desktop_बहुलकम्.pixel_density = 1.0f;

        प्रति (पूर्णाङ्क i = (पूर्णाङ्क)आन्तरिकम्->scale_गुणकः_2; i > 0; --i) {
            desktop_बहुलकम्.w = आन्तरिकम्->logical.विस्तारः * i;
            desktop_बहुलकम्.h = आन्तरिकम्->logical.height * i;
            SDL_सङ्कलय_Fullscreen_Display_बहुलकम्(dpy, &desktop_बहुलकम्);
        }
    }

    // Add emulated modes if wp_viewporter is supported and mode emulation is enabled.
    यदि (video->viewporter && बहुलकम्_emulation_enabled) {
        // The transformed display pixel width/height must be used here.
        सङ्कलय_Emulated_Modes(आन्तरिकम्, native_बहुलकम्.w, native_बहुलकम्.h);
    }

    यदि (आन्तरिकम्->display == 0) {
        // First time getting display info, initialize the VideoDisplay
        यदि (आन्तरिकम्->physical.विस्तारः_mm >= आन्तरिकम्->physical.height_mm) {
            आन्तरिकम्->placeholder.natural_orientation = SDL_ORIENTATION_LANDSCAPE;
        } अन्यथा {
            आन्तरिकम्->placeholder.natural_orientation = SDL_ORIENTATION_PORTRAIT;
        }
        आन्तरिकम्->placeholder.current_orientation = आन्तरिकम्->orientation;
        आन्तरिकम्->placeholder.आन्तरिकम् = आन्तरिकम्;

        आन्तरिकम्->placeholder.props = SDL_CreateProperties();
        SDL_समुच्चयः_Pointer_Property(आन्तरिकम्->placeholder.props, SDL_PROP_DISPLAY_WAYLAND_WL_OUTPUT_POINTER, आन्तरिकम्->output);

        // During initialization, the displays will be added after enumeration is complete.
        यदि (!video->initializing) {
            यदि (video->wp_color_manager_v1) {
                Wayland_GetColorInfoForOutput(आन्तरिकम्, false);
            }
            यदि (video->scale_गन्तव्यम्_display_enabled) {
                Wayland_DeriveOutputPixelCoordinates(video);
            }

            आन्तरिकम्->display = SDL_सङ्कलय_Video_Display(&आन्तरिकम्->placeholder, true);
            Wayland_Refresh_गवाक्षः_Positions();

            SDL_free(आन्तरिकम्->placeholder.name);
            SDL_zero(आन्तरिकम्->placeholder);
        }
    } अन्यथा {
        SDL_SendDisplayEvent(dpy, SDL_EVENT_DISPLAY_ORIENTATION, आन्तरिकम्->orientation, 0);

        यदि (आन्तरिकम्->geometry_परिवर्तितम्) {
            यदि (video->scale_गन्तव्यम्_display_enabled) {
                Wayland_DeriveOutputPixelCoordinates(video);
            }

            SDL_SendDisplayEvent(dpy, SDL_EVENT_DISPLAY_MOVED, 0, 0);
            Wayland_Refresh_गवाक्षः_Positions();
        }
    }

    आन्तरिकम्->geometry_परिवर्तितम् = false;
}

स्थिर शून्य handle_wl_output_scale(शून्य *दत्त, संरचना wl_output *output, int32_t गुणकः)
{
    SDL_Display_दत्त *आन्तरिकम् = (SDL_Display_दत्त *)दत्त;
    आन्तरिकम्->integer_scale_गुणकः = गुणकः;
}

स्थिर शून्य handle_wl_output_name(शून्य *दत्त, संरचना wl_output *wl_output, ध्रुव वर्ण *name)
{
    SDL_Display_दत्त *आन्तरिकम् = (SDL_Display_दत्त *)दत्त;

    SDL_free(आन्तरिकम्->wl_output_name);
    आन्तरिकम्->wl_output_name = SDL_strdup(name);
}

स्थिर शून्य handle_wl_output_description(शून्य *दत्त, संरचना wl_output *wl_output, ध्रुव वर्ण *description)
{
    SDL_Display_दत्त *आन्तरिकम् = (SDL_Display_दत्त *)दत्त;

    यदि (आन्तरिकम्->display == 0) {
        // The description, if available, supersedes the model name.
        SDL_free(आन्तरिकम्->placeholder.name);
        आन्तरिकम्->placeholder.name = SDL_strdup(description);
    }
}

स्थिर ध्रुव संरचना wl_output_listener output_listener = {
    handle_wl_output_geometry,   // Version 1
    handle_wl_output_बहुलकम्,       // Version 1
    handle_wl_output_समाप्तम्,       // Version 2
    handle_wl_output_scale,      // Version 2
    handle_wl_output_name,       // Version 4
    handle_wl_output_description // Version 4
};

स्थिर शून्य handle_output_image_description_परिवर्तितम्(शून्य *दत्त,
                                                    संरचना wp_color_management_output_v1 *wp_color_management_output_v1)
{
    SDL_Display_दत्त *display = (SDL_Display_दत्त *)दत्त;
    Wayland_GetColorInfoForOutput(display, false);
}

स्थिर ध्रुव संरचना wp_color_management_output_v1_listener wp_color_management_output_listener = {
    handle_output_image_description_परिवर्तितम्
};

स्थिर bool Wayland_सङ्कलय_display(SDL_Video_दत्त *d, uint32_t id, uint32_t संस्करणम्)
{
    संरचना wl_output *output;
    SDL_Display_दत्त *दत्त;

    output = wl_registry_bind(d->registry, id, &wl_output_interface, संस्करणम्);
    यदि (!output) {
        प्रत्यागम SDL_समुच्चयः_Error("Failed to retrieve output.");
    }
    दत्त = (SDL_Display_दत्त *)SDL_calloc(1, परिमाण(*दत्त));
    दत्त->videodata = d;
    दत्त->output = output;
    दत्त->registry_id = id;
    दत्त->scale_गुणकः_2 = 1.0f;
    दत्त->integer_scale_गुणकः = 1;

    wl_output_सङ्कलय_listener(output, &output_listener, दत्त);
    SDL_WAYLAND_पञ्जिकाकोशः_output(output);

    // Keep a list of outputs for sorting and deferred protocol initialization.
    यदि (d->output_गणनम् == d->output_max) {
        d->output_max += 4;
        d->output_list = SDL_realloc(d->output_list, परिमाण(SDL_Display_दत्त *) * d->output_max);
    }
    d->output_list[d->output_गणनम्++] = दत्त;

    यदि (दत्त->videodata->xdg_output_manager) {
        दत्त->xdg_output = zxdg_output_manager_v1_get_xdg_output(दत्त->videodata->xdg_output_manager, output);
        zxdg_output_v1_सङ्कलय_listener(दत्त->xdg_output, &xdg_output_listener, दत्त);
    }
    यदि (दत्त->videodata->wp_color_manager_v1) {
        दत्त->wp_color_management_output = wp_color_manager_v1_get_output(दत्त->videodata->wp_color_manager_v1, output);
        wp_color_management_output_v1_सङ्कलय_listener(दत्त->wp_color_management_output, &wp_color_management_output_listener, दत्त);

        // If not initializing, this will be queried synchronously in wl_output.done.
        यदि (d->initializing) {
            Wayland_GetColorInfoForOutput(दत्त, true);
        }
    }
    प्रत्यागम true;
}

स्थिर शून्य Wayland_free_display(SDL_VideoDisplay *display, bool send_event)
{
    यदि (display) {
        SDL_Display_दत्त *display_दत्त = display->आन्तरिकम्;

        /* A preceding surface leave event is not guaranteed when an output is removed,
         * so ensure that no window continues to hold a reference to a removed output.
         */
        प्रति (SDL_गवाक्षः *गवाक्षः = SDL_GetVideoDevice()->windows; गवाक्षः; गवाक्षः = गवाक्षः->अग्र) {
            Wayland_Remove_Output_From_गवाक्षः(गवाक्षः->आन्तरिकम्, display_दत्त);
        }

        SDL_free(display_दत्त->wl_output_name);

        यदि (display_दत्त->wp_color_management_output) {
            Wayland_FreeColorInfoState(display_दत्त->color_info_state);
            wp_color_management_output_v1_destroy(display_दत्त->wp_color_management_output);
        }

        यदि (display_दत्त->xdg_output) {
            zxdg_output_v1_destroy(display_दत्त->xdg_output);
        }

        यदि (wl_output_get_संस्करणम्(display_दत्त->output) >= WL_OUTPUT_RELEASE_SINCE_संस्करणम्) {
            wl_output_release(display_दत्त->output);
        } अन्यथा {
            wl_output_destroy(display_दत्त->output);
        }

        SDL_DelVideoDisplay(display->id, send_event);
    }
}

स्थिर शून्य Wayland_FinalizeDisplays(SDL_Video_दत्त *vid)
{
    Wayland_क्रमय_Outputs(vid);

    प्रति(पूर्णाङ्क i = 0; i < vid->output_गणनम्; ++i) {
        SDL_Display_दत्त *d = vid->output_list[i];
        d->display = SDL_सङ्कलय_Video_Display(&d->placeholder, false);
        SDL_free(d->placeholder.name);
        SDL_zero(d->placeholder);
    }
}

स्थिर शून्य Wayland_init_xdg_output(SDL_Video_दत्त *d)
{
    प्रति (पूर्णाङ्क i = 0; i < d->output_गणनम्; ++i) {
        SDL_Display_दत्त *disp = d->output_list[i];
        disp->xdg_output = zxdg_output_manager_v1_get_xdg_output(disp->videodata->xdg_output_manager, disp->output);
        zxdg_output_v1_सङ्कलय_listener(disp->xdg_output, &xdg_output_listener, disp);
    }
}

स्थिर शून्य Wayland_InitColorManager(SDL_Video_दत्त *d)
{
    प्रति (पूर्णाङ्क i = 0; i < d->output_गणनम्; ++i) {
        SDL_Display_दत्त *disp = d->output_list[i];
        disp->wp_color_management_output = wp_color_manager_v1_get_output(disp->videodata->wp_color_manager_v1, disp->output);
        wp_color_management_output_v1_सङ्कलय_listener(disp->wp_color_management_output, &wp_color_management_output_listener, disp);
        Wayland_GetColorInfoForOutput(disp, true);
    }
}

स्थिर शून्य handle_xdg_session_created(शून्य *दत्त, संरचना xdg_session_v1 *xdg_session_v1, ध्रुव वर्ण *id)
{
    SDL_समुच्चयः_String_Property(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, id);
}

स्थिर शून्य handle_xdg_session_restored(शून्य *दत्त, संरचना xdg_session_v1 *xdg_session_v1)
{
    // NOP
}

स्थिर शून्य handle_xdg_session_replaced(शून्य *दत्त, संरचना xdg_session_v1 *xdg_session_v1)
{
    SDL_VideoDevice *viddev = SDL_GetVideoDevice();
    SDL_Video_दत्त *viddata = दत्त;

    // Clean up all session objects, as they have become inert, and should be destroyed.
    SDL_समुच्चयः_String_Property(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, रिक्त);

    प्रति (SDL_गवाक्षः *w = viddev->windows; w; w = w->अग्र) {
        SDL_गवाक्षः_दत्त *d = w->आन्तरिकम्;

        यदि (d->xdg_toplevel_session) {
            xdg_toplevel_session_v1_destroy(d->xdg_toplevel_session);
            d->xdg_toplevel_session = रिक्त;

            SDL_free(d->session_id);
            d->session_id = रिक्त;
        }
    }

    यदि (viddata->xdg_session) {
        xdg_session_v1_destroy(viddata->xdg_session);
        viddata->xdg_session = रिक्त;
    }
}

स्थिर ध्रुव संरचना xdg_session_v1_listener xdg_session_listener = {
    .created  = handle_xdg_session_created,
    .restored = handle_xdg_session_restored,
    .replaced = handle_xdg_session_replaced
};

शून्य Wayland_CreateSession(SDL_Video_दत्त *viddata)
{
    यदि (!viddata->xdg_session_manager) {
        // Set the ID string to null if session management is not available.
        SDL_समुच्चयः_String_Property(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, रिक्त);
        प्रत्यागम;
    }

    // Register a new session, if one does not yet exist.
    यदि (!viddata->xdg_session) {
        ध्रुव वर्ण *session_id = SDL_GetStringProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, रिक्त);
        यदि (session_id) {
            यदि (*session_id == '\0') {
                // Create a new session if the ID string is empty.
                session_id = रिक्त;
            }

            ध्रुव गणना xdg_session_manager_v1_reason reason = session_id ? XDG_SESSION_MANAGER_V1_REASON_SESSION_RESTORE : XDG_SESSION_MANAGER_V1_REASON_LAUNCH;
            viddata->xdg_session = xdg_session_manager_v1_get_session(viddata->xdg_session_manager, reason, session_id);
            xdg_session_v1_सङ्कलय_listener(viddata->xdg_session, &xdg_session_listener, viddata);
        }
    }
}

स्थिर शून्य Wayland_SessionDestroy(SDL_Video_दत्त *viddata)
{
    // If the session string was cleared, remove the session.
    यदि (viddata->xdg_session) {
        ध्रुव वर्ण *session_id = SDL_GetStringProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, रिक्त);
        यदि (!session_id || *session_id == '\0') {
            xdg_session_v1_remove(viddata->xdg_session);

            WAYLAND_wl_display_roundtrip(viddata->display);
        } अन्यथा {
            xdg_session_v1_destroy(viddata->xdg_session);
        }

        viddata->xdg_session = रिक्त;
    }
}

स्थिर शून्य handle_xdg_wm_आधारः_ping(शून्य *दत्त, संरचना xdg_wm_आधारः *xdg, uint32_t serial)
{
    xdg_wm_आधारः_pong(xdg, serial);
}

स्थिर ध्रुव संरचना xdg_wm_आधारः_listener xdg_wm_आधारः_listener_2 = {
    handle_xdg_wm_आधारः_ping
};

#यदि_परिभाषितम् HAVE_LIBDECOR_H
स्थिर शून्य libdecor_error(संरचना libdecor *context,
                           गणना libdecor_error error,
                           ध्रुव वर्ण *सन्देशः)
{
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "libdecor error (%d): %s", error, सन्देशः);
}

स्थिर संरचना libdecor_interface libdecor_interface = {
    libdecor_error
};
#यदि_अन्तः

स्थिर शून्य handle_registry_global(शून्य *दत्त, संरचना wl_registry *registry, uint32_t id,
                                   ध्रुव वर्ण *interface, uint32_t संस्करणम्)
{
    SDL_Video_दत्त *d = दत्त;

    यदि (SDL_strcmp(interface, wl_compositor_interface.name) == 0) {
        d->compositor = wl_registry_bind(d->registry, id, &wl_compositor_interface, SDL_min(SDL_WL_COMPOSITOR_संस्करणम्, संस्करणम्));
    } अन्यथा यदि (SDL_strcmp(interface, wl_subcompositor_interface.name) == 0) {
        d->subcompositor = wl_registry_bind(d->registry, id, &wl_subcompositor_interface, 1);
    } अन्यथा यदि (SDL_strcmp(interface, wl_output_interface.name) == 0) {
        Wayland_सङ्कलय_display(d, id, SDL_min(संस्करणम्, SDL_WL_OUTPUT_संस्करणम्));
    } अन्यथा यदि (SDL_strcmp(interface, wl_seat_interface.name) == 0) {
        संरचना wl_seat *seat = wl_registry_bind(d->registry, id, &wl_seat_interface, SDL_min(SDL_WL_SEAT_संस्करणम्, संस्करणम्));
        Wayland_DisplayCreateSeat(d, seat, id);
    } अन्यथा यदि (SDL_strcmp(interface, xdg_wm_आधारः_interface.name) == 0) {
        d->shell.xdg = wl_registry_bind(d->registry, id, &xdg_wm_आधारः_interface, SDL_min(संस्करणम्, 7));
        xdg_wm_आधारः_सङ्कलय_listener(d->shell.xdg, &xdg_wm_आधारः_listener_2, रिक्त);
    } अन्यथा यदि (SDL_strcmp(interface, wl_shm_interface.name) == 0) {
        d->shm = wl_registry_bind(registry, id, &wl_shm_interface, SDL_min(SDL_WL_SHM_संस्करणम्, संस्करणम्));
    } अन्यथा यदि (SDL_strcmp(interface, zwp_relative_pointer_manager_v1_interface.name) == 0) {
        d->relative_pointer_manager = wl_registry_bind(d->registry, id, &zwp_relative_pointer_manager_v1_interface, 1);
    } अन्यथा यदि (SDL_strcmp(interface, zwp_pointer_constraints_v1_interface.name) == 0) {
        d->pointer_constraints = wl_registry_bind(d->registry, id, &zwp_pointer_constraints_v1_interface, 1);
    } अन्यथा यदि (SDL_strcmp(interface, zwp_keyboard_shortcuts_inhibit_manager_v1_interface.name) == 0) {
        d->कुञ्चिका_inhibitor_manager = wl_registry_bind(d->registry, id, &zwp_keyboard_shortcuts_inhibit_manager_v1_interface, 1);
    } अन्यथा यदि (SDL_strcmp(interface, zwp_idle_inhibit_manager_v1_interface.name) == 0) {
        d->idle_inhibit_manager = wl_registry_bind(d->registry, id, &zwp_idle_inhibit_manager_v1_interface, 1);
    } अन्यथा यदि (SDL_strcmp(interface, xdg_activation_v1_interface.name) == 0) {
        d->activation_manager = wl_registry_bind(d->registry, id, &xdg_activation_v1_interface, 1);
    } अन्यथा यदि (SDL_strcmp(interface, zwp_text_निवेशः_manager_v3_interface.name) == 0) {
        d->text_निवेशः_manager = wl_registry_bind(d->registry, id, &zwp_text_निवेशः_manager_v3_interface, 1);
        Wayland_Display_Init_Text_निवेशः_Manager(d, id);
    } अन्यथा यदि (SDL_strcmp(interface, wl_दत्त_device_manager_interface.name) == 0) {
        d->दत्त_device_manager = wl_registry_bind(d->registry, id, &wl_दत्त_device_manager_interface, SDL_min(3, संस्करणम्));
        Wayland_Display_Init_दत्त_Device_Manager(d);
    } अन्यथा यदि (SDL_strcmp(interface, zwp_primary_selection_device_manager_v1_interface.name) == 0) {
        d->primary_selection_device_manager = wl_registry_bind(d->registry, id, &zwp_primary_selection_device_manager_v1_interface, 1);
        Wayland_DisplayInitPrimarySelectionDeviceManager(d);
    } अन्यथा यदि (SDL_strcmp(interface, zxdg_decoration_manager_v1_interface.name) == 0) {
        d->decoration_manager = wl_registry_bind(d->registry, id, &zxdg_decoration_manager_v1_interface, SDL_min(2, संस्करणम्));
    } अन्यथा यदि (SDL_strcmp(interface, zwp_tablet_manager_v2_interface.name) == 0) {
        d->tablet_manager = wl_registry_bind(d->registry, id, &zwp_tablet_manager_v2_interface, 1);
        Wayland_DisplayInitTabletManager(d);
    } अन्यथा यदि (SDL_strcmp(interface, zxdg_output_manager_v1_interface.name) == 0) {
        संस्करणम् = SDL_min(संस्करणम्, 3); // Versions 1 through 3 are supported.
        d->xdg_output_manager = wl_registry_bind(d->registry, id, &zxdg_output_manager_v1_interface, संस्करणम्);
        Wayland_init_xdg_output(d);
    } अन्यथा यदि (SDL_strcmp(interface, wp_viewporter_interface.name) == 0) {
        d->viewporter = wl_registry_bind(d->registry, id, &wp_viewporter_interface, 1);
    } अन्यथा यदि (SDL_strcmp(interface, wp_fractional_scale_manager_v1_interface.name) == 0) {
        d->fractional_scale_manager = wl_registry_bind(d->registry, id, &wp_fractional_scale_manager_v1_interface, 1);
    } अन्यथा यदि (SDL_strcmp(interface, zwp_निवेशः_timestamps_manager_v1_interface.name) == 0) {
        d->निवेशः_timestamps_manager = wl_registry_bind(d->registry, id, &zwp_निवेशः_timestamps_manager_v1_interface, 1);
        Wayland_Display_Init_निवेशः_Timestamp_Manager(d);
    } अन्यथा यदि (SDL_strcmp(interface, wp_cursor_shape_manager_v1_interface.name) == 0) {
        d->cursor_shape_manager = wl_registry_bind(d->registry, id, &wp_cursor_shape_manager_v1_interface, SDL_min(संस्करणम्, 2));
        Wayland_DisplayInitCursorShapeManager(d);
    } अन्यथा यदि (SDL_strcmp(interface, zxdg_exporter_v2_interface.name) == 0) {
        d->zxdg_exporter_v2 = wl_registry_bind(d->registry, id, &zxdg_exporter_v2_interface, 1);
    } अन्यथा यदि (SDL_strcmp(interface, xdg_wm_dialog_v1_interface.name) == 0) {
        d->xdg_wm_dialog_v1 = wl_registry_bind(d->registry, id, &xdg_wm_dialog_v1_interface, 1);
    } अन्यथा यदि (SDL_strcmp(interface, wp_alpha_modifier_v1_interface.name) == 0) {
        d->wp_alpha_modifier_v1 = wl_registry_bind(d->registry, id, &wp_alpha_modifier_v1_interface, 1);
    } अन्यथा यदि (SDL_strcmp(interface, xdg_toplevel_icon_manager_v1_interface.name) == 0) {
        d->xdg_toplevel_icon_manager_v1 = wl_registry_bind(d->registry, id, &xdg_toplevel_icon_manager_v1_interface, 1);
    } अन्यथा यदि (SDL_strcmp(interface, frog_color_management_factory_v1_interface.name) == 0) {
        d->frog_color_management_factory_v1 = wl_registry_bind(d->registry, id, &frog_color_management_factory_v1_interface, 1);
    } अन्यथा यदि (SDL_strcmp(interface, wp_color_manager_v1_interface.name) == 0) {
        d->wp_color_manager_v1 = wl_registry_bind(d->registry, id, &wp_color_manager_v1_interface, SDL_min(संस्करणम्, 2));
        Wayland_InitColorManager(d);
    } अन्यथा यदि (SDL_strcmp(interface, wp_pointer_warp_v1_interface.name) == 0) {
        d->wp_pointer_warp_v1 = wl_registry_bind(d->registry, id, &wp_pointer_warp_v1_interface, 1);
    } अन्यथा यदि (SDL_strcmp(interface, zwp_pointer_gestures_v1_interface.name) == 0) {
        d->zwp_pointer_gestures = wl_registry_bind(d->registry, id, &zwp_pointer_gestures_v1_interface, SDL_min(संस्करणम्, 3));
        Wayland_DisplayInitPointerGestureManager(d);
    } अन्यथा यदि (SDL_strcmp(interface, wp_single_pixel_बफर_manager_v1_interface.name) == 0) {
        d->single_pixel_बफर_manager = wl_registry_bind(d->registry, id, &wp_single_pixel_बफर_manager_v1_interface, 1);
    } अन्यथा यदि (SDL_strcmp(interface, xdg_session_manager_v1_interface.name) == 0) {
        d->xdg_session_manager = wl_registry_bind(d->registry, id, &xdg_session_manager_v1_interface, 1);
    } अन्यथा यदि (SDL_strcmp(interface, xdg_toplevel_चिह्नकम्_manager_v1_interface.name) == 0) {
        d->xdg_toplevel_चिह्नकम्_manager = wl_registry_bind(d->registry, id, &xdg_toplevel_चिह्नकम्_manager_v1_interface, 1);
    }
#यदि_परिभाषितम् SDL_WL_FIXES_संस्करणम्
    अन्यथा यदि (SDL_strcmp(interface, wl_fixes_interface.name) == 0) {
        d->wl_fixes = wl_registry_bind(d->registry, id, &wl_fixes_interface, SDL_min(SDL_WL_FIXES_संस्करणम्, संस्करणम्));
    }
#यदि_अन्तः
}

स्थिर शून्य handle_registry_remove_global(शून्य *दत्त, संरचना wl_registry *registry, uint32_t id)
{
    SDL_Video_दत्त *d = दत्त;

    // We don't get an interface, just an ID, so check outputs and seats.
    प्रति (पूर्णाङ्क i = 0; i < d->output_गणनम्; ++i) {
        SDL_Display_दत्त *disp = d->output_list[i];
        यदि (disp->registry_id == id) {
            Wayland_free_display(SDL_GetVideoDisplay(disp->display), true);

            यदि (i < d->output_गणनम्) {
                SDL_memmove(&d->output_list[i], &d->output_list[i + 1], परिमाण(SDL_Display_दत्त *) * (d->output_गणनम् - i - 1));
            }

            d->output_गणनम्--;
            गच्छ ack_remove;
        }
    }

    SDL_WaylandSeat *seat, *अस्थायी;
    wl_list_for_each_safe (seat, अस्थायी, &d->seat_list, link) {
        यदि (seat->registry_id == id) {
            Wayland_SeatDestroy(seat, false);
            गच्छ ack_remove;
        }
    }

ack_remove:
    यदि (d->wl_fixes && wl_fixes_get_संस्करणम्(d->wl_fixes) >= WL_FIXES_ACK_GLOBAL_REMOVE_SINCE_संस्करणम्) {
        wl_fixes_ack_global_remove(d->wl_fixes, registry, id);
    }
}

स्थिर ध्रुव संरचना wl_registry_listener registry_listener = {
    handle_registry_global,
    handle_registry_remove_global
};

#यदि_परिभाषितम् HAVE_LIBDECOR_H
स्थिर bool should_use_libdecor(SDL_Video_दत्त *दत्त, bool ignore_xdg)
{
    यदि (!SDL_WAYLAND_HAVE_WAYLAND_LIBDECOR) {
        प्रत्यागम false;
    }

    यदि (SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_PREFER_LIBDECOR, false)) {
        प्रत्यागम true;
    }

    यदि (ignore_xdg) {
        प्रत्यागम true;
    }

    यदि (दत्त->decoration_manager) {
        प्रत्यागम false;
    }

    प्रत्यागम true;
}

स्थिर शून्य LibdecorNew(SDL_Video_दत्त *दत्त)
{
    दत्त->shell.libdecor = libdecor_new(दत्त->display, &libdecor_interface);
}

// Called in another thread, but the UI thread is blocked in SDL_WaitThread
// during that time, so it should be OK to dereference data without locks
स्थिर पूर्णाङ्क SDLCALL Libdecor_New_अन्तर्_Thread(शून्य *दत्त)
{
    LibdecorNew((SDL_Video_दत्त *)दत्त);
    प्रत्यागम 0;
}
#यदि_अन्तः

#यदि_परिभाषितम् HAVE_GETRESUID
#परिभाषय SDL_getresuid getresuid
#अन्यथा
// Non-POSIX, but Linux and some BSDs have it.
// To reduce the number of code paths, if getresuid() isn't available at
// compile-time, we behave as though it existed but failed at runtime.
स्थिर अन्तःस्थ पूर्णाङ्क SDL_getresuid(uid_t *ruid, uid_t *euid, uid_t *suid) {
    errno = ENOSYS;
    प्रत्यागम -1;
}
#यदि_अन्तः

#यदि_परिभाषितम् HAVE_GETRESGID
#परिभाषय SDL_getresgid getresgid
#अन्यथा
// Same as getresuid() but for the primary group
स्थिर अन्तःस्थ पूर्णाङ्क SDL_getresgid(gid_t *rgid, gid_t *egid, gid_t *sgid) {
    errno = ENOSYS;
    प्रत्यागम -1;
}
#यदि_अन्तः

bool CanUseGtk(शून्य)
{
    // "Real", "effective" and "saved" IDs: see e.g. Linux credentials(7)
    uid_t ruid = -1, euid = -1, suid = -1;
    gid_t rgid = -1, egid = -1, sgid = -1;

    यदि (!SDL_GetHintBoolean("SDL_ENABLE_GTK", true)) {
        SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "Not using GTK due to hint");
        प्रत्यागम false;
    }

    // This is intended to match the check in gtkmain.c, rather than being
    // an exhaustive check for having elevated privileges: as a result
    // we don't use Linux getauxval() or prctl PR_GET_DUMPABLE,
    // BSD issetugid(), or similar OS-specific detection

    यदि (SDL_getresuid(&ruid, &euid, &suid) != 0) {
        ruid = suid = getuid();
        euid = geteuid();
    }

    यदि (SDL_getresgid(&rgid, &egid, &sgid) != 0) {
        rgid = sgid = getgid();
        egid = getegid();
    }

    // Real ID != effective ID means we are setuid or setgid:
    // GTK will refuse to initialize, and instead will call exit().
    यदि (ruid != euid || rgid != egid) {
        SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "Not using GTK due to setuid/setgid");
        प्रत्यागम false;
    }

    // Real ID != saved ID means we are setuid or setgid, we previously
    // dropped privileges, but we can regain them; this protects against
    // accidents but does not protect against arbitrary code execution.
    // Again, GTK will refuse to initialize if this is the case.
    यदि (ruid != suid || rgid != sgid) {
        SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "Not using GTK due to saved uid/gid");
        प्रत्यागम false;
    }

    प्रत्यागम true;
}

bool Wayland_आरोपय_Libdecor(SDL_Video_दत्त *दत्त, bool ignore_xdg)
{
#यदि_परिभाषितम् HAVE_LIBDECOR_H
    यदि (दत्त->shell.libdecor != रिक्त) {
        प्रत्यागम true; // Already loaded!
    }
    यदि (should_use_libdecor(दत्त, ignore_xdg)) {
        यदि (CanUseGtk()) {
            LibdecorNew(दत्त);
        } अन्यथा {
            // Intentionally initialize libdecor in a non-main thread
            // so that it will not use its GTK plugin, but instead will
            // fall back to the Cairo or dummy plugin
            SDL_Thread *thread = SDL_CreateThread(Libdecor_New_अन्तर्_Thread, "SDL_LibdecorNew", (शून्य *)दत्त);
            // Note that the other thread now "owns" data until we have
            // waited for it, so don't touch data here
            SDL_WaitThread(thread, रिक्त);
        }

        प्रत्यागम दत्त->shell.libdecor != रिक्त;
    }
#यदि_अन्तः
    प्रत्यागम false;
}

bool Wayland_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;

    दत्त->event_thread_context = Wayland_CreateEventThread(दत्त, "SDL Event Thread Queue");
    यदि (!दत्त->event_thread_context) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Failed to create event thread context");
    }

    दत्त->job_thread_context = Wayland_CreateJobThread();
    यदि (!दत्त->job_thread_context) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Failed to create job thread context");
    }

    दत्त->xkb_context = WAYLAND_xkb_context_new(0);
    यदि (!दत्त->xkb_context) {
        प्रत्यागम SDL_समुच्चयः_Error("Failed to create XKB context");
    }

    दत्त->registry = wl_display_get_registry(दत्त->display);
    यदि (!दत्त->registry) {
        प्रत्यागम SDL_समुच्चयः_Error("Failed to get the Wayland registry");
    }

    wl_registry_सङ्कलय_listener(दत्त->registry, &registry_listener, दत्त);

    // First roundtrip to receive all registry objects.
    WAYLAND_wl_display_roundtrip(दत्त->display);

    // Require viewports and xdg-output for display scaling.
    यदि (दत्त->scale_गन्तव्यम्_display_enabled) {
        यदि (!दत्त->viewporter) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Display scaling requires the missing 'wp_viewporter' protocol: disabling");
            दत्त->scale_गन्तव्यम्_display_enabled = false;
        }
        यदि (!दत्त->xdg_output_manager) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Display scaling requires the missing 'zxdg_output_manager_v1' protocol: disabling");
            दत्त->scale_गन्तव्यम्_display_enabled = false;
        }
    }

    // Now that we have all the protocols, load libdecor if applicable
    Wayland_आरोपय_Libdecor(दत्त, false);

    // Second roundtrip to receive all output events.
    WAYLAND_wl_display_roundtrip(दत्त->display);

    Wayland_FinalizeDisplays(दत्त);

    Wayland_InitMouse(दत्त);
    Wayland_InitKeyboard(_this);

    यदि (दत्त->primary_selection_device_manager) {
        _this->समुच्चयः_Primary_Selection_Text = Wayland_समुच्चयः_Primary_Selection_Text;
        _this->GetPrimarySelectionText = Wayland_GetPrimarySelectionText;
        _this->HasPrimarySelectionText = Wayland_HasPrimarySelectionText;
    }

    दत्त->initializing = false;

    प्रत्यागम true;
}

स्थिर bool Wayland_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    SDL_Video_दत्त *viddata = _this->आन्तरिकम्;
    SDL_Display_दत्त *आन्तरिकम् = display->आन्तरिकम्;

    यदि (!viddata->scale_गन्तव्यम्_display_enabled) {
        rect->x = आन्तरिकम्->logical.x;
        rect->y = आन्तरिकम्->logical.y;
    } अन्यथा {
        rect->x = आन्तरिकम्->pixel.x;
        rect->y = आन्तरिकम्->pixel.y;
    }

    // When an emulated, exclusive fullscreen window has focus, treat the mode dimensions as the display bounds.
    यदि (display->fullscreen_गवाक्षः &&
        display->fullscreen_गवाक्षः->fullscreen_exclusive &&
        display->fullscreen_गवाक्षः->आन्तरिकम्->सक्रिय &&
        display->fullscreen_गवाक्षः->current_fullscreen_बहुलकम्.w != 0 &&
        display->fullscreen_गवाक्षः->current_fullscreen_बहुलकम्.h != 0) {
        rect->w = display->fullscreen_गवाक्षः->current_fullscreen_बहुलकम्.w;
        rect->h = display->fullscreen_गवाक्षः->current_fullscreen_बहुलकम्.h;
    } अन्यथा {
        यदि (!viddata->scale_गन्तव्यम्_display_enabled) {
            rect->w = display->current_बहुलकम्->w;
            rect->h = display->current_बहुलकम्->h;
        } अन्यथा यदि (आन्तरिकम्->transform & WL_OUTPUT_TRANSFORM_90) {
            rect->w = आन्तरिकम्->pixel.height;
            rect->h = आन्तरिकम्->pixel.विस्तारः;
        } अन्यथा {
            rect->w = आन्तरिकम्->pixel.विस्तारः;
            rect->h = आन्तरिकम्->pixel.height;
        }
    }
    प्रत्यागम true;
}

स्थिर शून्य Wayland_VideoCleanup(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
    SDL_WaylandSeat *seat, *tmp;

    Wayland_SessionDestroy(दत्त);

    प्रति (पूर्णाङ्क i = _this->अङ्कः_displays - 1; i >= 0; --i) {
        SDL_VideoDisplay *display = _this->displays[i];
        Wayland_free_display(display, false);
    }
    SDL_free(दत्त->output_list);

    wl_list_for_each_safe (seat, tmp, &दत्त->seat_list, link) {
        Wayland_SeatDestroy(seat, true);
    }

    Wayland_FiniMouse(दत्त);
    Wayland_QuitKeyboard(_this);

    Wayland_DestroyEventThread(दत्त->event_thread_context);
    दत्त->event_thread_context = रिक्त;

    Wayland_DestroyJobThread(दत्त->job_thread_context);
    दत्त->job_thread_context = रिक्त;

    यदि (दत्त->pointer_constraints) {
        zwp_pointer_constraints_v1_destroy(दत्त->pointer_constraints);
        दत्त->pointer_constraints = रिक्त;
    }

    यदि (दत्त->relative_pointer_manager) {
        zwp_relative_pointer_manager_v1_destroy(दत्त->relative_pointer_manager);
        दत्त->relative_pointer_manager = रिक्त;
    }

    यदि (दत्त->activation_manager) {
        xdg_activation_v1_destroy(दत्त->activation_manager);
        दत्त->activation_manager = रिक्त;
    }

    यदि (दत्त->idle_inhibit_manager) {
        zwp_idle_inhibit_manager_v1_destroy(दत्त->idle_inhibit_manager);
        दत्त->idle_inhibit_manager = रिक्त;
    }

    यदि (दत्त->कुञ्चिका_inhibitor_manager) {
        zwp_keyboard_shortcuts_inhibit_manager_v1_destroy(दत्त->कुञ्चिका_inhibitor_manager);
        दत्त->कुञ्चिका_inhibitor_manager = रिक्त;
    }

    यदि (दत्त->text_निवेशः_manager) {
        zwp_text_निवेशः_manager_v3_destroy(दत्त->text_निवेशः_manager);
        दत्त->text_निवेशः_manager = रिक्त;
    }

    यदि (दत्त->xkb_context) {
        WAYLAND_xkb_context_unref(दत्त->xkb_context);
        दत्त->xkb_context = रिक्त;
    }

    यदि (दत्त->tablet_manager) {
        zwp_tablet_manager_v2_destroy((संरचना zwp_tablet_manager_v2 *)दत्त->tablet_manager);
        दत्त->tablet_manager = रिक्त;
    }

    यदि (दत्त->दत्त_device_manager) {
        wl_दत्त_device_manager_destroy(दत्त->दत्त_device_manager);
        दत्त->दत्त_device_manager = रिक्त;
    }

    यदि (दत्त->shm) {
        यदि (wl_shm_get_संस्करणम्(दत्त->shm) >= WL_SHM_RELEASE_SINCE_संस्करणम्) {
            wl_shm_release(दत्त->shm);
        } अन्यथा {
            wl_shm_destroy(दत्त->shm);
        }
        दत्त->shm = रिक्त;
    }

    यदि (दत्त->shell.xdg) {
        xdg_wm_आधारः_destroy(दत्त->shell.xdg);
        दत्त->shell.xdg = रिक्त;
    }

    यदि (दत्त->decoration_manager) {
        zxdg_decoration_manager_v1_destroy(दत्त->decoration_manager);
        दत्त->decoration_manager = रिक्त;
    }

    यदि (दत्त->xdg_output_manager) {
        zxdg_output_manager_v1_destroy(दत्त->xdg_output_manager);
        दत्त->xdg_output_manager = रिक्त;
    }

    यदि (दत्त->viewporter) {
        wp_viewporter_destroy(दत्त->viewporter);
        दत्त->viewporter = रिक्त;
    }

    यदि (दत्त->primary_selection_device_manager) {
        zwp_primary_selection_device_manager_v1_destroy(दत्त->primary_selection_device_manager);
        दत्त->primary_selection_device_manager = रिक्त;
    }

    यदि (दत्त->fractional_scale_manager) {
        wp_fractional_scale_manager_v1_destroy(दत्त->fractional_scale_manager);
        दत्त->fractional_scale_manager = रिक्त;
    }

    यदि (दत्त->निवेशः_timestamps_manager) {
        zwp_निवेशः_timestamps_manager_v1_destroy(दत्त->निवेशः_timestamps_manager);
        दत्त->निवेशः_timestamps_manager = रिक्त;
    }

    यदि (दत्त->cursor_shape_manager) {
        wp_cursor_shape_manager_v1_destroy(दत्त->cursor_shape_manager);
        दत्त->cursor_shape_manager = रिक्त;
    }

    यदि (दत्त->zxdg_exporter_v2) {
        zxdg_exporter_v2_destroy(दत्त->zxdg_exporter_v2);
        दत्त->zxdg_exporter_v2 = रिक्त;
    }

    यदि (दत्त->xdg_wm_dialog_v1) {
        xdg_wm_dialog_v1_destroy(दत्त->xdg_wm_dialog_v1);
        दत्त->xdg_wm_dialog_v1 = रिक्त;
    }

    यदि (दत्त->wp_alpha_modifier_v1) {
        wp_alpha_modifier_v1_destroy(दत्त->wp_alpha_modifier_v1);
        दत्त->wp_alpha_modifier_v1 = रिक्त;
    }

    यदि (दत्त->xdg_toplevel_icon_manager_v1) {
        xdg_toplevel_icon_manager_v1_destroy(दत्त->xdg_toplevel_icon_manager_v1);
        दत्त->xdg_toplevel_icon_manager_v1 = रिक्त;
    }

    यदि (दत्त->frog_color_management_factory_v1) {
        frog_color_management_factory_v1_destroy(दत्त->frog_color_management_factory_v1);
        दत्त->frog_color_management_factory_v1 = रिक्त;
    }

    यदि (दत्त->wp_color_manager_v1) {
        wp_color_manager_v1_destroy(दत्त->wp_color_manager_v1);
        दत्त->wp_color_manager_v1 = रिक्त;
    }

    यदि (दत्त->wp_pointer_warp_v1) {
        wp_pointer_warp_v1_destroy(दत्त->wp_pointer_warp_v1);
        दत्त->wp_pointer_warp_v1 = रिक्त;
    }

    यदि (दत्त->zwp_pointer_gestures) {
        यदि (zwp_pointer_gestures_v1_get_संस्करणम्(दत्त->zwp_pointer_gestures) >= ZWP_POINTER_GESTURES_V1_RELEASE_SINCE_संस्करणम्) {
            zwp_pointer_gestures_v1_release(दत्त->zwp_pointer_gestures);
        } अन्यथा {
            zwp_pointer_gestures_v1_destroy(दत्त->zwp_pointer_gestures);
        }
        दत्त->zwp_pointer_gestures = रिक्त;
    }

    यदि (दत्त->single_pixel_बफर_manager) {
        wp_single_pixel_बफर_manager_v1_destroy(दत्त->single_pixel_बफर_manager);
        दत्त->single_pixel_बफर_manager = रिक्त;
    }

    यदि (दत्त->xdg_session_manager) {
        xdg_session_manager_v1_destroy(दत्त->xdg_session_manager);
        दत्त->xdg_session_manager = रिक्त;
    }

    यदि (दत्त->xdg_toplevel_चिह्नकम्_manager) {
        xdg_toplevel_चिह्नकम्_manager_v1_destroy(दत्त->xdg_toplevel_चिह्नकम्_manager);
        दत्त->xdg_toplevel_चिह्नकम्_manager = रिक्त;
    }

    यदि (दत्त->subcompositor) {
        wl_subcompositor_destroy(दत्त->subcompositor);
        दत्त->subcompositor = रिक्त;
    }

    यदि (दत्त->compositor) {
        wl_compositor_destroy(दत्त->compositor);
        दत्त->compositor = रिक्त;
    }

    यदि (दत्त->registry) {
        यदि (दत्त->wl_fixes) {
            wl_fixes_destroy_registry(दत्त->wl_fixes, दत्त->registry);
            wl_fixes_destroy(दत्त->wl_fixes);
            दत्त->wl_fixes = रिक्त;
        }
        wl_registry_destroy(दत्त->registry);
        दत्त->registry = रिक्त;
    }
}

स्थिर bool Wayland_VideoReconnect(SDL_VideoDevice *_this)
{
#यदि 0 // TODO RECONNECT: Uncomment all when https://invent.kde.org/plasma/kwin/-/wikis/Restarting is completed
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;

    SDL_गवाक्षः *गवाक्षः = रिक्त;

    SDL_GLContext current_ctx = SDL_GL_GetCurrentContext();
    SDL_गवाक्षः *current_गवाक्षः = SDL_GL_Get_Current_गवाक्षः();

    SDL_GL_MakeCurrent(रिक्त, रिक्त);
    Wayland_VideoCleanup(_this);

    SDL_ResetKeyboard();
    SDL_ResetMouse();
    यदि (WAYLAND_wl_display_reconnect(दत्त->display) < 0) {
        प्रत्यागम false;
    }

    Wayland_VideoInit(_this);

    गवाक्षः = _this->windows;
    यावत् (गवाक्षः) {
        /* We're going to cheat _just_ for a second and strip the OpenGL flag.
         * The Wayland driver actually forces it in CreateWindow, and
         * RecreateWindow does a bunch of unloading/loading of libGL, so just
         * strip the flag so RecreateWindow doesn't mess with the GL context,
         * and CreateWindow will add it right back!
         * -flibit
         */
        गवाक्षः->flags &= ~SDL_गवाक्षः_OPENGL;

        SDL_Recreate_गवाक्षः(गवाक्षः, गवाक्षः->flags);
        गवाक्षः = गवाक्षः->अग्र;
    }

    Wayland_RecreateCursors();

    यदि (current_गवाक्षः && current_ctx) {
        SDL_GL_MakeCurrent (current_गवाक्षः, current_ctx);
    }
    प्रत्यागम true;
#अन्यथा
    प्रत्यागम false;
#यदि_अन्तः // 0
}

bool Wayland_HandleDisplayDisconnected(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *video_दत्त = _this->आन्तरिकम्;

    /* Something has failed with the Wayland connection -- for example,
     * the compositor may have shut down and closed its end of the socket,
     * or there is a library-specific error.
     *
     * Try to recover once, then quit.
     */
    यदि (video_दत्त->display_disconnected) {
        प्रत्यागम false;
    }

    यदि (Wayland_VideoReconnect(_this)) {
        प्रत्यागम true;
    }

    video_दत्त->display_disconnected = true;
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Wayland display connection closed by server (fatal)");

    // Only send a single quit message, as application shutdown might call SDL_PumpEvents().
    SDL_SendQuit();

    प्रत्यागम false;
}

शून्य Wayland_VideoQuit(SDL_VideoDevice *_this)
{
    Wayland_VideoCleanup(_this);

#यदि_परिभाषितम् HAVE_LIBDECOR_H
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
    यदि (दत्त->shell.libdecor) {
        libdecor_unref(दत्त->shell.libdecor);
        दत्त->shell.libdecor = रिक्त;
    }
#यदि_अन्तः
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_WAYLAND
