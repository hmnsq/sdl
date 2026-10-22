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

#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#அந்தர்பாவ "../../core/linux/SDL_system_theme.h"
#அந்தர்பாவ "../../core/linux/SDL_progressbar.h"
#அந்தர்பாவ "../../events/SDL_events_c.h"

#அந்தர்பாவ "SDL_waylandclipboard.h"
#அந்தர்பாவ "SDL_waylandcolor.h"
#அந்தர்பாவ "SDL_waylandevents_c.h"
#அந்தர்பாவ "SDL_waylandkeyboard.h"
#அந்தர்பாவ "SDL_waylandmessagebox.h"
#அந்தர்பாவ "SDL_waylandmouse.h"
#அந்தர்பாவ "SDL_waylandopengles.h"
#அந்தர்பாவ "SDL_waylandvideo.h"
#அந்தர்பாவ "SDL_waylandvulkan.h"
#அந்தர்பாவ "SDL_waylandwindow.h"

#அந்தர்பாவ <fcntl.h>
#அந்தர்பாவ <sys/types.h>
#அந்தர்பாவ <unistd.h>
#அந்தர்பாவ <errno.h>
#அந்தர்பாவ <xkbcommon/xkbcommon.h>

#அந்தர்பாவ <wayland-util.h>

#அந்தர்பாவ "alpha-modifier-v1-client-protocol.h"
#அந்தர்பாவ "cursor-shape-v1-client-protocol.h"
#அந்தர்பாவ "fractional-scale-v1-client-protocol.h"
#அந்தர்பாவ "frog-color-management-v1-client-protocol.h"
#அந்தர்பாவ "idle-inhibit-unstable-v1-client-protocol.h"
#அந்தர்பாவ "input-timestamps-unstable-v1-client-protocol.h"
#அந்தர்பாவ "keyboard-shortcuts-inhibit-unstable-v1-client-protocol.h"
#அந்தர்பாவ "pointer-constraints-unstable-v1-client-protocol.h"
#அந்தர்பாவ "primary-selection-unstable-v1-client-protocol.h"
#அந்தர்பாவ "relative-pointer-unstable-v1-client-protocol.h"
#அந்தர்பாவ "tablet-v2-client-protocol.h"
#அந்தர்பாவ "text-input-unstable-v3-client-protocol.h"
#அந்தர்பாவ "viewporter-client-protocol.h"
#அந்தர்பாவ "xdg-activation-v1-client-protocol.h"
#அந்தர்பாவ "xdg-decoration-unstable-v1-client-protocol.h"
#அந்தர்பாவ "xdg-dialog-v1-client-protocol.h"
#அந்தர்பாவ "xdg-foreign-unstable-v2-client-protocol.h"
#அந்தர்பாவ "xdg-output-unstable-v1-client-protocol.h"
#அந்தர்பாவ "xdg-shell-client-protocol.h"
#அந்தர்பாவ "xdg-toplevel-icon-v1-client-protocol.h"
#அந்தர்பாவ "color-management-v1-client-protocol.h"
#அந்தர்பாவ "pointer-warp-v1-client-protocol.h"
#அந்தர்பாவ "pointer-gestures-unstable-v1-client-protocol.h"
#அந்தர்பாவ "single-pixel-buffer-v1-client-protocol.h"
#அந்தர்பாவ "xdg-session-management-v1-client-protocol.h"
#அந்தர்பாவ "xdg-toplevel-tag-v1-client-protocol.h"

#ifdef HAVE_LIBDECOR_H
#அந்தர்பாவ <libdecor.h>
#endif

#define WAYLANDVID_DRIVER_NAME "wayland"

// Clamp core protocol versions on older versions of libwayland.
#எனில் SDL_WAYLAND_CHECK_VERSION(1, 22, 0)
#define SDL_WL_COMPOSITOR_VERSION 6
#இல்லையெனில்
#define SDL_WL_COMPOSITOR_VERSION 4
#endif

#எனில் SDL_WAYLAND_CHECK_VERSION(1, 26, 0)
#define SDL_WL_SEAT_VERSION 11
#அல்லதெனில் SDL_WAYLAND_CHECK_VERSION(1, 24, 0)
#define SDL_WL_SEAT_VERSION 10
#அல்லதெனில் SDL_WAYLAND_CHECK_VERSION(1, 22, 0)
#define SDL_WL_SEAT_VERSION 9
#அல்லதெனில் SDL_WAYLAND_CHECK_VERSION(1, 21, 0)
#define SDL_WL_SEAT_VERSION 8
#இல்லையெனில்
#define SDL_WL_SEAT_VERSION 5
#endif

#எனில் SDL_WAYLAND_CHECK_VERSION(1, 20, 0)
#define SDL_WL_OUTPUT_VERSION 4
#இல்லையெனில்
#define SDL_WL_OUTPUT_VERSION 3
#endif

#எனில் SDL_WAYLAND_CHECK_VERSION(1, 24, 0)
#define SDL_WL_SHM_VERSION 2
#இல்லையெனில்
#define SDL_WL_SHM_VERSION 1
#endif

// The SDL libwayland-client minimum is 1.18, which supports version 3.
#define SDL_WL_DATA_DEVICE_VERSION 3

// wl_fixes was introduced in 1.24.0
#எனில் SDL_WAYLAND_CHECK_VERSION(1, 26, 0)
#define SDL_WL_FIXES_VERSION 2
#அல்லதெனில் SDL_WAYLAND_CHECK_VERSION(1, 24, 0)
#define SDL_WL_FIXES_VERSION 1
#endif

#ifdef SDL_USE_LIBDBUS
#அந்தர்பாவ "../../core/linux/SDL_dbus.h"

#define DISPLAY_INFO_முனை   "org.gnome.Mutter.DisplayConfig"
#define DISPLAY_INFO_PATH   "/org/gnome/Mutter/DisplayConfig"
#define DISPLAY_INFO_METHOD "GetCurrentState"
#endif

/* GNOME doesn't expose displays in any particular order, but we can find the
 * primary display and its logical coordinates via a DBus method.
 */
நிலையான bool Wayland_GetGNOMEPrimaryDisplayCoordinates(முழு *x, முழு *y)
{
#ifdef SDL_USE_LIBDBUS
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    எனில் (dbus == வெற்று) {
        திரும்பு false;
    }
    DBusMessage *reply = வெற்று;
    DBusMessageIter iter[3];
    DBusMessage *செய்தி = dbus->message_new_method_call(DISPLAY_INFO_முனை,
                                                     DISPLAY_INFO_PATH,
                                                     DISPLAY_INFO_முனை,
                                                     DISPLAY_INFO_METHOD);

    எனில் (செய்தி) {
        reply = dbus->connection_send_with_reply_and_block(dbus->session_conn, செய்தி, DBUS_TIMEOUT_USE_DEFAULT, வெற்று);
        dbus->message_unref(செய்தி);
    }

    எனில் (reply) {
        // Serial (don't care)
        dbus->message_iter_init(reply, &iter[0]);
        எனில் (dbus->message_iter_get_arg_type(&iter[0]) != DBUS_TYPE_UINT32) {
            செல் error;
        }

        // Physical monitor array (don't care)
        dbus->message_iter_next(&iter[0]);
        எனில் (dbus->message_iter_get_arg_type(&iter[0]) != DBUS_TYPE_ARRAY) {
            செல் error;
        }

        // Logical monitor array of structs
        dbus->message_iter_next(&iter[0]);
        எனில் (dbus->message_iter_get_arg_type(&iter[0]) != DBUS_TYPE_ARRAY) {
            செல் error;
        }

        // First logical monitor struct
        dbus->message_iter_recurse(&iter[0], &iter[1]);
        எனில் (dbus->message_iter_get_arg_type(&iter[1]) != DBUS_TYPE_STRUCT) {
            செல் error;
        }

        செய் {
            முழு logical_x, logical_y;
            dbus_bool_t primary;

            // Logical X
            dbus->message_iter_recurse(&iter[1], &iter[2]);
            எனில் (dbus->message_iter_get_arg_type(&iter[2]) != DBUS_TYPE_INT32) {
                செல் error;
            }
            dbus->message_iter_get_basic(&iter[2], &logical_x);

            // Logical Y
            dbus->message_iter_next(&iter[2]);
            எனில் (dbus->message_iter_get_arg_type(&iter[2]) != DBUS_TYPE_INT32) {
                செல் error;
            }
            dbus->message_iter_get_basic(&iter[2], &logical_y);

            // Scale (don't care)
            dbus->message_iter_next(&iter[2]);
            எனில் (dbus->message_iter_get_arg_type(&iter[2]) != DBUS_TYPE_DOUBLE) {
                செல் error;
            }

            // Transform (don't care)
            dbus->message_iter_next(&iter[2]);
            எனில் (dbus->message_iter_get_arg_type(&iter[2]) != DBUS_TYPE_UINT32) {
                செல் error;
            }

            // Primary display boolean
            dbus->message_iter_next(&iter[2]);
            எனில் (dbus->message_iter_get_arg_type(&iter[2]) != DBUS_TYPE_BOOLEAN) {
                செல் error;
            }
            dbus->message_iter_get_basic(&iter[2], &primary);

            எனில் (primary) {
                *x = logical_x;
                *y = logical_y;

                // We found the primary display: success.
                dbus->message_unref(reply);
                திரும்பு true;
            }
        } போது (dbus->message_iter_next(&iter[1]));
    }

error:
    எனில் (reply) {
        dbus->message_unref(reply);
    }
#endif
    திரும்பு false;
}

// Sort the list of displays into a deterministic order
நிலையான முழு SDLCALL Wayland_DisplayPositionCompare(மாறிலி வெறுமை *a, மாறிலி வெறுமை *b)
{
    மாறிலி SDL_DisplayData *da = *(SDL_DisplayData **)a;
    மாறிலி SDL_DisplayData *db = *(SDL_DisplayData **)b;
    மாறிலி bool a_at_origin = da->logical.x == 0 && da->logical.y == 0;
    மாறிலி bool b_at_origin = db->logical.x == 0 && db->logical.y == 0;

    // Sort the display at 0,0 to be beginning of the list, as that will be the fallback primary.
    எனில் (a_at_origin && !b_at_origin) {
        திரும்பு -1;
    }
    எனில் (b_at_origin && !a_at_origin) {
        திரும்பு 1;
    }

    எனில் (da->logical.x < db->logical.x) {
        திரும்பு -1;
    }
    எனில் (da->logical.x > db->logical.x) {
        திரும்பு 1;
    }
    எனில் (da->logical.y < db->logical.y) {
        திரும்பு -1;
    }
    எனில் (da->logical.y > db->logical.y) {
        திரும்பு 1;
    }

    // If no position information is available, use the connector name.
    எனில் (da->wl_output_name && db->wl_output_name) {
        திரும்பு SDL_strcmp(da->wl_output_name, db->wl_output_name);
    }

    திரும்பு 0;
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
நிலையான முழு Wayland_GetPrimaryDisplay(SDL_VideoData *vid)
{
    நிலையான மாறிலி முழு REFRESH_DELTA = 4000;

    // Query the DBus interface to see if the coordinates of the primary display are exposed.
    முழு x, y;
    எனில் (Wayland_GetGNOMEPrimaryDisplayCoordinates(&x, &y)) {
        க்கு (முழு i = 0; i < vid->output_மொத்தம்; ++i) {
            எனில் (vid->output_list[i]->logical.x == x && vid->output_list[i]->logical.y == y) {
                திரும்பு i;
            }
        }
    }

    // Otherwise, choose the 'best' display.
    முழு best_width = 0;
    முழு best_height = 0;
    இரட்டை best_scale = 0.0;
    தசம best_headroom = 0.0f;
    முழு best_refresh = 0;
    bool best_is_landscape = false;
    முழு best_index = 0;

    க்கு (முழு i = 0; i < vid->output_மொத்தம்; ++i) {
        மாறிலி SDL_DisplayData *d = vid->output_list[i];
        மாறிலி bool is_landscape = d->orientation != SDL_ORIENTATION_PORTRAIT && d->orientation != SDL_ORIENTATION_PORTRAIT_FLIPPED;
        bool have_new_best = false;

        எனில் (!best_is_landscape && is_landscape) { // Favor landscape over portrait displays.
            have_new_best = true;
        } இல்லையெனில் எனில் (!best_is_landscape || is_landscape) { // Ignore portrait displays if a landscape was already found.
            எனில் (d->pixel.width > best_width || d->pixel.height > best_height) {
                have_new_best = true;
            } இல்லையெனில் எனில் (d->pixel.width == best_width && d->pixel.height == best_height) {
                எனில் (d->HDR.HDR_headroom > best_headroom) { // Favor a higher HDR luminance range
                    have_new_best = true;
                } இல்லையெனில் எனில் (d->HDR.HDR_headroom == best_headroom) {
                    எனில் (d->refresh - best_refresh > REFRESH_DELTA) { // Favor a higher refresh rate, but ignore small differences (e.g. 59.97 vs 60.1)
                        have_new_best = true;
                    } இல்லையெனில் எனில் (d->scale_factor < best_scale && SDL_abs(d->refresh - best_refresh) <= REFRESH_DELTA) {
                        // Prefer a lower scale display if the difference in refresh rate is small.
                        have_new_best = true;
                    }
                }
            }
        }

        எனில் (have_new_best) {
            best_width = d->pixel.width;
            best_height = d->pixel.height;
            best_scale = d->scale_factor;
            best_headroom = d->HDR.HDR_headroom;
            best_refresh = d->refresh;
            best_is_landscape = is_landscape;
            best_index = i;
        }
    }

    திரும்பு best_index;
}

நிலையான வெறுமை Wayland_SortOutputsByPriorityHint(SDL_VideoData *vid)
{
    மாறிலி எழுத்து *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_PRIORITY);

    எனில் (name_hint) {
        எழுத்து *saveptr;
        எழுத்து *str = SDL_strdup(name_hint);
        SDL_DisplayData **sorted_list = SDL_malloc(அளவு(SDL_DisplayData *) * vid->output_மொத்தம்);

        எனில் (str && sorted_list) {
            முழு sorted_index = 0;

            // Sort the requested displays to the front of the list.
            மாறிலி எழுத்து *token = SDL_strtok_r(str, ",", &saveptr);
            போது (token) {
                க்கு (முழு i = 0; i < vid->output_மொத்தம்; ++i) {
                    SDL_DisplayData *d = vid->output_list[i];
                    எனில் (d && d->wl_output_name && SDL_strcmp(token, d->wl_output_name) == 0) {
                        sorted_list[sorted_index++] = d;
                        vid->output_list[i] = வெற்று;
                        நிறுத்து;
                    }
                }

                token = SDL_strtok_r(வெற்று, ",", &saveptr);
            }

            // Append the remaining outputs to the end of the list.
            க்கு (முழு i = 0; i < vid->output_மொத்தம்; ++i) {
                எனில் (vid->output_list[i]) {
                    sorted_list[sorted_index++] = vid->output_list[i];
                }
            }

            // Copy the sorted list to the output list.
            SDL_memcpy(vid->output_list, sorted_list, அளவு(SDL_DisplayData *) * vid->output_மொத்தம்);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

நிலையான வெறுமை Wayland_DeriveOutputPixelCoordinates(SDL_VideoData *vid)
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
    க்கு ( முழு i = 0; i < vid->output_மொத்தம்; ++i) {
        SDL_DisplayData *d = vid->output_list[i];
        d->pixel.x = d->logical.x;
        d->pixel.y = d->logical.y;
    }

    க்கு (முழு i = 0; i < vid->output_மொத்தம்; ++i) {
        SDL_DisplayData *d1 = vid->output_list[i];
        எனில் (d1->logical.width != d1->pixel.width || d1->logical.height != d1->pixel.height) {
            மாறிலி முழு x_adj = d1->pixel.width - d1->logical.width;
            மாறிலி முழு y_adj = d1->pixel.height - d1->logical.height;

            // Don't adjust for scale values less than 1.0.
            எனில் (x_adj > 0 && y_adj > 0) {
                க்கு (முழு j = 0; j < vid->output_மொத்தம்; ++j) {
                    SDL_DisplayData *d2 = vid->output_list[j];
                    எனில் (d2->logical.x > d1->logical.x) {
                        d2->pixel.x += x_adj;
                    }
                    எனில் (d2->logical.y > d1->logical.y) {
                        d2->pixel.y += y_adj;
                    }
                }
            }
        }
    }
}

நிலையான வெறுமை Wayland_SortOutputs(SDL_VideoData *vid)
{
    // Sort by position or connector name, so the order of outputs is deterministic.
    SDL_qsort(vid->output_list, vid->output_மொத்தம், அளவு(SDL_DisplayData *), Wayland_DisplayPositionCompare);

    // Derive the output pixel coordinates if scale to display is enabled.
    எனில் (vid->scale_to_display_enabled) {
        Wayland_DeriveOutputPixelCoordinates(vid);
    }

    // Find a suitable primary display and move it to the front of the list.
    மாறிலி முழு primary_index = Wayland_GetPrimaryDisplay(vid);
    எனில் (primary_index) {
        SDL_DisplayData *primary = vid->output_list[primary_index];
        SDL_memmove(&vid->output_list[1], &vid->output_list[0], அளவு(SDL_DisplayData *) * primary_index);
        vid->output_list[0] = primary;
    }

    // Apply the ordering hint, if specified.
    Wayland_SortOutputsByPriorityHint(vid);
}

நிலையான வெறுமை Wayland_RefreshWindowPositions()
{
    SDL_VideoDevice *vid = SDL_GetVideoDevice();

    க்கு (SDL_Window *w = vid->windows; w; w = w->next) {
        Wayland_UpdateWindowPosition(w);
    }
}

நிலையான வெறுமை handle_wl_output_done(வெறுமை *data, கட்டமைப்பு wl_output *output);

// Initialization/Query functions
நிலையான bool Wayland_VideoInit(SDL_VideoDevice *_this);
நிலையான bool Wayland_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
நிலையான வெறுமை Wayland_VideoQuit(SDL_VideoDevice *_this);

நிலையான மாறிலி எழுத்து *SDL_WAYLAND_surface_tag = "sdl-window";
நிலையான மாறிலி எழுத்து *SDL_WAYLAND_output_tag = "sdl-output";

வெறுமை SDL_WAYLAND_register_surface(கட்டமைப்பு wl_surface *surface)
{
    wl_proxy_set_tag((கட்டமைப்பு wl_proxy *)surface, &SDL_WAYLAND_surface_tag);
}

வெறுமை SDL_WAYLAND_register_output(கட்டமைப்பு wl_output *output)
{
    wl_proxy_set_tag((கட்டமைப்பு wl_proxy *)output, &SDL_WAYLAND_output_tag);
}

bool SDL_WAYLAND_own_surface(கட்டமைப்பு wl_surface *surface)
{
    திரும்பு wl_proxy_get_tag((கட்டமைப்பு wl_proxy *)surface) == &SDL_WAYLAND_surface_tag;
}

bool SDL_WAYLAND_own_output(கட்டமைப்பு wl_output *output)
{
    திரும்பு wl_proxy_get_tag((கட்டமைப்பு wl_proxy *)output) == &SDL_WAYLAND_output_tag;
}

/* External surfaces may have their own user data attached, the modification of which
 * can cause problems with external toolkits. Instead, external windows are kept in
 * their own list, and a search is conducted to find a matching surface.
 */
நிலையான கட்டமைப்பு wl_list external_window_list;

வெறுமை Wayland_AddWindowDataToExternalList(SDL_WindowData *data)
{
    WAYLAND_wl_list_செருகு(&external_window_list, &data->external_window_list_link);
}

வெறுமை Wayland_RemoveWindowDataFromExternalList(SDL_WindowData *data)
{
    WAYLAND_wl_list_remove(&data->external_window_list_link);
}

SDL_WindowData *Wayland_GetWindowDataForOwnedSurface(கட்டமைப்பு wl_surface *surface)
{
    எனில் (SDL_WAYLAND_own_surface(surface)) {
        திரும்பு (SDL_WindowData *)wl_surface_get_user_data(surface);
    } இல்லையெனில் எனில் (!WAYLAND_wl_list_empty(&external_window_list)) {
        SDL_WindowData *p;
        wl_list_for_each (p, &external_window_list, external_window_list_link) {
            எனில் (p->surface == surface) {
                திரும்பு p;
            }
        }
    }

    திரும்பு வெற்று;
}

கட்டமைப்பு wl_event_queue *Wayland_DisplayCreateQueue(கட்டமைப்பு wl_display *display, மாறிலி எழுத்து *name)
{
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
    எனில் (WAYLAND_wl_display_create_queue_with_name) {
        திரும்பு WAYLAND_wl_display_create_queue_with_name(display, name);
    }
#அல்லதெனில் SDL_WAYLAND_CHECK_VERSION(1, 23, 0)
    திரும்பு WAYLAND_wl_display_create_queue_with_name(display, name);
#endif
    திரும்பு WAYLAND_wl_display_create_queue(display);
}

நிலையான வெறுமை Wayland_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_VideoData *data = device->internal;
    எனில் (data->display && !data->display_externally_owned) {
        WAYLAND_wl_display_disconnect(data->display);
        SDL_ClearProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_POINTER);
    }
    SDL_free(data);
    SDL_free(device);
    SDL_WAYLAND_UnloadSymbols();
}

வகைவரை கட்டமைப்பு
{
    bool has_fifo_v1;
    கட்டமைப்பு wl_fixes *wl_fixes;
} SDL_WaylandPreferredData;

நிலையான வெறுமை wayland_preferred_check_handle_global(வெறுமை *data, கட்டமைப்பு wl_registry *registry, uint32_t id,
                                                  மாறிலி எழுத்து *interface, uint32_t version)
{
    SDL_WaylandPreferredData *d = data;

    எனில் (SDL_strcmp(interface, "wp_fifo_manager_v1") == 0) {
        d->has_fifo_v1 = true;
    }
#ifdef SDL_WL_FIXES_VERSION
    இல்லையெனில் எனில் (SDL_strcmp(interface, wl_fixes_interface.name) == 0) {
        d->wl_fixes = wl_registry_bind(registry, id, &wl_fixes_interface, SDL_min(SDL_WL_FIXES_VERSION, version));
    }
#endif
}

நிலையான வெறுமை wayland_preferred_check_remove_global(வெறுமை *data, கட்டமைப்பு wl_registry *registry, uint32_t id)
{
    SDL_WaylandPreferredData *d = (SDL_WaylandPreferredData *)data;

    எனில் (d->wl_fixes && wl_fixes_get_version(d->wl_fixes) >= WL_FIXES_ACK_GLOBAL_REMOVE_SINCE_VERSION) {
        wl_fixes_ack_global_remove(d->wl_fixes, registry, id);
    }
}

நிலையான மாறிலி கட்டமைப்பு wl_registry_listener preferred_registry_listener = {
    wayland_preferred_check_handle_global,
    wayland_preferred_check_remove_global
};

நிலையான bool Wayland_IsPreferred(கட்டமைப்பு wl_display *display)
{
    கட்டமைப்பு wl_registry *registry = wl_display_get_registry(display);
    SDL_WaylandPreferredData preferred_data = { 0 };

    எனில் (!registry) {
        SDL_SetError("Failed to get the Wayland registry");
        திரும்பு false;
    }

    wl_registry_add_listener(registry, &preferred_registry_listener, &preferred_data);

    WAYLAND_wl_display_roundtrip(display);

    எனில் (preferred_data.wl_fixes) {
        wl_fixes_destroy_registry(preferred_data.wl_fixes, registry);
        wl_fixes_destroy(preferred_data.wl_fixes);
    }
    wl_registry_destroy(registry);

    எனில் (!preferred_data.has_fifo_v1) {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "This compositor lacks support for the fifo-v1 protocol; falling back to XWayland for GPU performance reasons (set SDL_VIDEO_DRIVER=wayland to override)");
    }
    திரும்பு preferred_data.has_fifo_v1;
}

நிலையான SDL_VideoDevice *Wayland_CreateDevice(bool require_preferred_protocols)
{
    SDL_VideoDevice *device;
    SDL_VideoData *data;
    கட்டமைப்பு wl_display *display = SDL_GetPointerProperty(SDL_GetGlobalProperties(),
                                                 SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_POINTER, வெற்று);
    bool display_is_external = !!display;

    // Are we trying to connect to, or are currently in, a Wayland session?
    எனில் (!SDL_getenv("WAYLAND_DISPLAY")) {
        மாறிலி எழுத்து *session = SDL_getenv("XDG_SESSION_TYPE");
        எனில் (session && SDL_strcasecmp(session, "wayland") != 0) {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Wayland initialization failed: no Wayland session available");
            திரும்பு வெற்று;
        }
    }

    எனில் (!SDL_WAYLAND_LoadSymbols()) {
        திரும்பு வெற்று;
    }

    எனில் (!display) {
        display = WAYLAND_wl_display_connect(வெற்று);
        எனில் (!display) {
            SDL_WAYLAND_UnloadSymbols();
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to connect to the Wayland display server: %s", strerror(errno));
            திரும்பு வெற்று;
        }
    }

    /*
     * If we are checking for preferred Wayland, then let's query for
     * fifo-v1's existence, so we don't regress GPU-bound performance
     * and frame-pacing by default due to swapchain starvation.
     */
    எனில் (require_preferred_protocols && !Wayland_IsPreferred(display)) {
        எனில் (!display_is_external) {
            WAYLAND_wl_display_disconnect(display);
        }
        SDL_WAYLAND_UnloadSymbols();
        திரும்பு வெற்று;
    }

    data = SDL_calloc(1, அளவு(*data));
    எனில் (!data) {
        எனில் (!display_is_external) {
            WAYLAND_wl_display_disconnect(display);
        }
        SDL_WAYLAND_UnloadSymbols();
        திரும்பு வெற்று;
    }

    data->initializing = true;
    data->display = display;
    data->display_externally_owned = display_is_external;
    data->scale_to_display_enabled = SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_SCALE_TO_DISPLAY, false);
    WAYLAND_wl_list_init(&data->seat_list);
    WAYLAND_wl_list_init(&external_window_list);

    // Initialize all variables that we clean on shutdown
    device = SDL_calloc(1, அளவு(SDL_VideoDevice));
    எனில் (!device) {
        SDL_free(data);
        எனில் (!display_is_external) {
            WAYLAND_wl_display_disconnect(display);
        }
        SDL_WAYLAND_UnloadSymbols();
        திரும்பு வெற்று;
    }

    எனில் (!display_is_external) {
        SDL_SetPointerProperty(SDL_GetGlobalProperties(),
                               SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_POINTER, display);
    }

    device->internal = data;

    // Set the function pointers
    device->VideoInit = Wayland_VideoInit;
    device->VideoQuit = Wayland_VideoQuit;
    device->GetDisplayBounds = Wayland_GetDisplayBounds;
    device->SuspendScreenSaver = Wayland_SuspendScreenSaver;

    device->PumpEvents = Wayland_PumpEvents;
    device->WaitEventTimeout = Wayland_WaitEventTimeout;
    device->SendWakeupEvent = Wayland_SendWakeupEvent;

#ifdef SDL_VIDEO_OPENGL_EGL
    device->GL_SwapWindow = Wayland_GLES_SwapWindow;
    device->GL_GetSwapInterval = Wayland_GLES_GetSwapInterval;
    device->GL_SetSwapInterval = Wayland_GLES_SetSwapInterval;
    device->GL_MakeCurrent = Wayland_GLES_MakeCurrent;
    device->GL_CreateContext = Wayland_GLES_CreateContext;
    device->GL_LoadLibrary = Wayland_GLES_LoadLibrary;
    device->GL_UnloadLibrary = Wayland_GLES_UnloadLibrary;
    device->GL_GetProcAddress = Wayland_GLES_GetProcAddress;
    device->GL_DestroyContext = Wayland_GLES_DestroyContext;
    device->GL_SetDefaultProfileConfig = Wayland_GLES_SetDefaultProfileConfig;
    device->GL_GetEGLSurface = Wayland_GLES_GetEGLSurface;
#endif

    device->CreateSDLWindow = Wayland_CreateWindow;
    device->ShowWindow = Wayland_ShowWindow;
    device->HideWindow = Wayland_HideWindow;
    device->RaiseWindow = Wayland_RaiseWindow;
    device->SetWindowFullscreen = Wayland_SetWindowFullscreen;
    device->MaximizeWindow = Wayland_MaximizeWindow;
    device->MinimizeWindow = Wayland_MinimizeWindow;
    device->SetWindowMouseRect = Wayland_SetWindowMouseRect;
    device->SetWindowMouseGrab = Wayland_SetWindowMouseGrab;
    device->SetWindowKeyboardGrab = Wayland_SetWindowKeyboardGrab;
    device->RestoreWindow = Wayland_RestoreWindow;
    device->SetWindowBordered = Wayland_SetWindowBordered;
    device->SetWindowResizable = Wayland_SetWindowResizable;
    device->SetWindowPosition = Wayland_SetWindowPosition;
    device->SetWindowSize = Wayland_SetWindowSize;
    device->SetWindowAspectRatio = Wayland_SetWindowAspectRatio;
    device->SetWindowMinimumSize = Wayland_SetWindowMinimumSize;
    device->SetWindowMaximumSize = Wayland_SetWindowMaximumSize;
    device->SetWindowParent = Wayland_SetWindowParent;
    device->SetWindowModal = Wayland_SetWindowModal;
    device->SetWindowOpacity = Wayland_SetWindowOpacity;
    device->SetWindowTitle = Wayland_SetWindowTitle;
    device->SetWindowIcon = Wayland_SetWindowIcon;
    device->GetWindowSizeInPixels = Wayland_GetWindowSizeInPixels;
    device->GetWindowContentScale = Wayland_GetWindowContentScale;
    device->GetWindowICCProfile = Wayland_GetWindowICCProfile;
    device->GetDisplayForWindow = Wayland_GetDisplayForWindow;
    device->DestroyWindow = Wayland_DestroyWindow;
    device->SetWindowHitTest = Wayland_SetWindowHitTest;
    device->FlashWindow = Wayland_FlashWindow;
#ifdef SDL_USE_LIBDBUS
    device->ApplyWindowProgress = DBUS_ApplyWindowProgress;
#endif // SDL_USE_LIBDBUS
    device->HasScreenKeyboardSupport = Wayland_HasScreenKeyboardSupport;
    device->ShowWindowSystemMenu = Wayland_ShowWindowSystemMenu;
    device->SyncWindow = Wayland_SyncWindow;
    device->SetWindowFocusable = Wayland_SetWindowFocusable;
    device->ReconfigureWindow = Wayland_ReconfigureWindow;
    device->AcceptDragAndDrop = Wayland_AcceptDragAndDrop;

#ifdef SDL_USE_LIBDBUS
    எனில் (SDL_SystemTheme_Init())
        device->system_theme = SDL_SystemTheme_Get();
#endif

    device->GetTextMimeTypes = Wayland_GetTextMimeTypes;
    device->SetClipboardData = Wayland_SetClipboardData;
    device->GetClipboardData = Wayland_GetClipboardData;
    device->HasClipboardData = Wayland_HasClipboardData;
    device->Start_Text_உள்ளீடு = Wayland_Start_Text_உள்ளீடு;
    device->Stop_Text_உள்ளீடு = Wayland_Stop_Text_உள்ளீடு;
    device->Update_Text_உள்ளீடு_Area = Wayland_Update_Text_உள்ளீடு_Area;

#ifdef SDL_VIDEO_VULKAN
    device->Vulkan_LoadLibrary = Wayland_Vulkan_LoadLibrary;
    device->Vulkan_UnloadLibrary = Wayland_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = Wayland_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = Wayland_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = Wayland_Vulkan_DestroySurface;
    device->Vulkan_GetPresentationSupport = Wayland_Vulkan_GetPresentationSupport;
#endif

    device->விடுவி = Wayland_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_MODE_SWITCHING_EMULATED |
                          VIDEO_DEVICE_CAPS_HAS_POPUP_WINDOW_SUPPORT |
                          VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS |
                          VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES |
                          VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES;

    திரும்பு device;
}

நிலையான SDL_VideoDevice *Wayland_Preferred_CreateDevice(வெறுமை)
{
    திரும்பு Wayland_CreateDevice(true);
}

நிலையான SDL_VideoDevice *Wayland_Fallback_CreateDevice(வெறுமை)
{
    திரும்பு Wayland_CreateDevice(false);
}

VideoBootStrap Wayland_preferred_bootstrap = {
    WAYLANDVID_DRIVER_NAME, "SDL Wayland video driver",
    Wayland_Preferred_CreateDevice,
    Wayland_ShowMessageBox,
    true
};

VideoBootStrap Wayland_bootstrap = {
    WAYLANDVID_DRIVER_NAME, "SDL Wayland video driver",
    Wayland_Fallback_CreateDevice,
    Wayland_ShowMessageBox,
    false
};

நிலையான வெறுமை handle_xdg_output_logical_position(வெறுமை *data, கட்டமைப்பு zxdg_output_v1 *xdg_output, int32_t x, int32_t y)
{
    SDL_DisplayData *internal = (SDL_DisplayData *)data;

    internal->geometry_changed |= internal->logical.x != x || internal->logical.y != y;
    internal->logical.x = x;
    internal->logical.y = y;
    internal->has_logical_position = true;
}

நிலையான வெறுமை handle_xdg_output_logical_size(வெறுமை *data, கட்டமைப்பு zxdg_output_v1 *xdg_output, int32_t width, int32_t height)
{
    SDL_DisplayData *internal = (SDL_DisplayData *)data;

    internal->geometry_changed |= internal->logical.width != width || internal->logical.height != height;
    internal->logical.width = width;
    internal->logical.height = height;
    internal->has_logical_size = true;
}

நிலையான வெறுமை handle_xdg_output_done(வெறுமை *data, கட்டமைப்பு zxdg_output_v1 *xdg_output)
{
    SDL_DisplayData *internal = data;

    /*
     * xdg-output.done events are deprecated and only apply below version 3 of the protocol.
     * A wl-output.done event will be emitted in version 3 or higher.
     */
    எனில் (zxdg_output_v1_get_version(internal->xdg_output) < 3) {
        handle_wl_output_done(data, internal->output);
    }
}

நிலையான வெறுமை handle_xdg_output_name(வெறுமை *data, கட்டமைப்பு zxdg_output_v1 *xdg_output, மாறிலி எழுத்து *name)
{
    SDL_DisplayData *internal = (SDL_DisplayData *)data;

    // Deprecated as of wl_output v4.
    எனில் (wl_output_get_version(internal->output) < WL_OUTPUT_NAME_SINCE_VERSION &&
        internal->display == 0) {
        SDL_free(internal->wl_output_name);
        internal->wl_output_name = SDL_strdup(name);
    }
}

நிலையான வெறுமை handle_xdg_output_description(வெறுமை *data, கட்டமைப்பு zxdg_output_v1 *xdg_output, மாறிலி எழுத்து *description)
{
    SDL_DisplayData *internal = (SDL_DisplayData *)data;

    // Deprecated as of wl_output v4.
    எனில் (wl_output_get_version(internal->output) < WL_OUTPUT_DESCRIPTION_SINCE_VERSION &&
        internal->display == 0) {
        // xdg-output descriptions, if available, supersede wl-output model names.
        SDL_free(internal->placeholder.name);
        internal->placeholder.name = SDL_strdup(description);
    }
}

நிலையான மாறிலி கட்டமைப்பு zxdg_output_v1_listener xdg_output_listener = {
    handle_xdg_output_logical_position,
    handle_xdg_output_logical_size,
    handle_xdg_output_done,
    handle_xdg_output_name,
    handle_xdg_output_description,
};

நிலையான வெறுமை AddEmulatedModes(SDL_DisplayData *dispdata, முழு native_width, முழு native_height)
{
    கட்டமைப்பு EmulatedMode
    {
        முழு w;
        முழு h;
    };

    // Resolution lists courtesy of XWayland
    மாறிலி கட்டமைப்பு EmulatedMode mode_list[] = {
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

    முழு i;
    SDL_DisplayMode mode;
    SDL_VideoDisplay *dpy = dispdata->display ? SDL_GetVideoDisplay(dispdata->display) : &dispdata->placeholder;
    மாறிலி bool rot_90 = native_width < native_height; // Reverse width/height for portrait displays.

    க்கு (i = 0; i < SDL_arraysize(mode_list); ++i) {
        SDL_zero(mode);
        mode.format = dpy->desktop_mode.format;
        mode.refresh_rate_numerator = dpy->desktop_mode.refresh_rate_numerator;
        mode.refresh_rate_denominator = dpy->desktop_mode.refresh_rate_denominator;

        எனில் (rot_90) {
            mode.w = mode_list[i].h;
            mode.h = mode_list[i].w;
        } இல்லையெனில் {
            mode.w = mode_list[i].w;
            mode.h = mode_list[i].h;
        }

        // Only add modes that are smaller than the native mode.
        எனில் ((mode.w < native_width && mode.h < native_height) ||
            (mode.w < native_width && mode.h == native_height) ||
            (mode.w == native_width && mode.h < native_height)) {
            SDL_AddFullscreenDisplayMode(dpy, &mode);
        }
    }
}

நிலையான வெறுமை handle_wl_output_geometry(வெறுமை *data, கட்டமைப்பு wl_output *output, முழு x, முழு y,
                                      முழு physical_width, முழு physical_height, முழு subpixel,
                                      மாறிலி எழுத்து *make, மாறிலி எழுத்து *model, முழு transform)
{
    SDL_DisplayData *internal = (SDL_DisplayData *)data;

    // Apply the change from wl-output only if xdg-output is not supported
    எனில் (!internal->has_logical_position) {
        internal->geometry_changed |= internal->logical.x != x || internal->logical.y != y;
        internal->logical.x = x;
        internal->logical.y = y;
    }
    internal->physical.width_mm = physical_width;
    internal->physical.height_mm = physical_height;

    // The model is only used for the output name if wl_output or xdg-output haven't provided a description.
    எனில் (internal->display == 0 && !internal->placeholder.name) {
        internal->placeholder.name = SDL_strdup(model);
    }

    internal->transform = transform;
#define TF_CASE(in, out)                                 \
    நிலை WL_OUTPUT_TRANSFORM_##in:                       \
        internal->orientation = SDL_ORIENTATION_##out; \
        நிறுத்து;
    எனில் (internal->physical.width_mm >= internal->physical.height_mm) {
        தேர்வு (transform) {
            TF_CASE(NORMAL, LANDSCAPE)
            TF_CASE(90, PORTRAIT)
            TF_CASE(180, LANDSCAPE_FLIPPED)
            TF_CASE(270, PORTRAIT_FLIPPED)
            TF_CASE(FLIPPED, LANDSCAPE_FLIPPED)
            TF_CASE(FLIPPED_90, PORTRAIT_FLIPPED)
            TF_CASE(FLIPPED_180, LANDSCAPE)
            TF_CASE(FLIPPED_270, PORTRAIT)
        }
    } இல்லையெனில் {
        தேர்வு (transform) {
            TF_CASE(NORMAL, PORTRAIT)
            TF_CASE(90, LANDSCAPE)
            TF_CASE(180, PORTRAIT_FLIPPED)
            TF_CASE(270, LANDSCAPE_FLIPPED)
            TF_CASE(FLIPPED, PORTRAIT_FLIPPED)
            TF_CASE(FLIPPED_90, LANDSCAPE_FLIPPED)
            TF_CASE(FLIPPED_180, PORTRAIT)
            TF_CASE(FLIPPED_270, LANDSCAPE)
        }
    }
#undef TF_CASE
}

நிலையான வெறுமை handle_wl_output_mode(வெறுமை *data, கட்டமைப்பு wl_output *output, uint32_t flags,
                                  முழு width, முழு height, முழு refresh)
{
    SDL_DisplayData *internal = (SDL_DisplayData *)data;

    எனில் (flags & WL_OUTPUT_MODE_CURRENT) {
        internal->geometry_changed |= internal->pixel.width != width || internal->pixel.height != height;
        internal->pixel.width = width;
        internal->pixel.height = height;

        /*
         * Don't rotate this yet, wl-output coordinates are transformed in
         * handle_done and xdg-output coordinates are pre-transformed.
         */
        எனில் (!internal->has_logical_size) {
            internal->geometry_changed |= internal->logical.width != width || internal->logical.height != height;
            internal->logical.width = width;
            internal->logical.height = height;
        }

        internal->refresh = refresh;
    }
}

நிலையான வெறுமை handle_wl_output_done(வெறுமை *data, கட்டமைப்பு wl_output *output)
{
    மாறிலி bool mode_emulation_enabled = SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_MODE_EMULATION, true);
    SDL_DisplayData *internal = (SDL_DisplayData *)data;
    SDL_VideoData *video = internal->videodata;
    SDL_DisplayMode native_mode, desktop_mode;

    /*
     * When using xdg-output, two wl-output.done events will be emitted:
     * one at the completion of wl-display and one at the completion of xdg-output.
     *
     * All required events must be received before proceeding.
     */
    மாறிலி முழு event_await_மொத்தம் = 1 + (internal->xdg_output != வெற்று);

    internal->wl_output_done_மொத்தம் = SDL_min(internal->wl_output_done_மொத்தம் + 1, event_await_மொத்தம் + 1);

    எனில் (internal->wl_output_done_மொத்தம் < event_await_மொத்தம்) {
        திரும்பு;
    }

    // If the display was already created, reset and rebuild the mode list.
    SDL_VideoDisplay *dpy = SDL_GetVideoDisplay(internal->display);
    எனில் (dpy) {
        SDL_ResetFullscreenDisplayModes(dpy);
    }

    // The native display resolution
    SDL_zero(native_mode);
    native_mode.format = SDL_PIXELFORMAT_XRGB8888;

    // Transform the pixel values, if necessary.
    எனில் (internal->transform & WL_OUTPUT_TRANSFORM_90) {
        native_mode.w = internal->pixel.height;
        native_mode.h = internal->pixel.width;
    } இல்லையெனில் {
        native_mode.w = internal->pixel.width;
        native_mode.h = internal->pixel.height;
    }
    native_mode.refresh_rate_numerator = internal->refresh;
    native_mode.refresh_rate_denominator = 1000;

    எனில் (internal->has_logical_size) { // If xdg-output is present...
        எனில் (native_mode.w != internal->logical.width || native_mode.h != internal->logical.height) {
            // ...and the compositor scales the logical viewport...
            எனில் (video->viewporter) {
                // ...and viewports are supported, calculate the true scale of the output.
                internal->scale_factor = (இரட்டை)native_mode.w / (இரட்டை)internal->logical.width;
            } இல்லையெனில் {
                // ...otherwise, the 'native' pixel values are a multiple of the logical screen size.
                internal->scale_factor = internal->integer_scale_factor;
                internal->pixel.width = internal->logical.width * internal->integer_scale_factor;
                internal->pixel.height = internal->logical.height * internal->integer_scale_factor;
            }
        } இல்லையெனில் {
            /* ...and the output viewport is not scaled in the global compositing
             * space, the output dimensions need to be divided by the scale factor.
             *
             * NOTE: This path is needed for old versions of GNOME that predate fractional scaling.
             */
            internal->scale_factor = internal->integer_scale_factor;
            internal->logical.width /= internal->integer_scale_factor;
            internal->logical.height /= internal->integer_scale_factor;
        }
    } இல்லையெனில் {
        /* Calculate the points from the pixel values, if xdg-output isn't present.
         * Use the native mode pixel values since they are pre-transformed.
         */
        internal->scale_factor = internal->integer_scale_factor;
        internal->logical.width = native_mode.w / internal->integer_scale_factor;
        internal->logical.height = native_mode.h / internal->integer_scale_factor;
    }

    // The scaled desktop mode
    SDL_zero(desktop_mode);
    desktop_mode.format = SDL_PIXELFORMAT_XRGB8888;

    எனில் (!video->scale_to_display_enabled) {
        desktop_mode.w = internal->logical.width;
        desktop_mode.h = internal->logical.height;
        desktop_mode.pixel_density = (தசம)internal->scale_factor;
    } இல்லையெனில் {
        desktop_mode.w = native_mode.w;
        desktop_mode.h = native_mode.h;
        desktop_mode.pixel_density = 1.0f;
    }

    desktop_mode.refresh_rate_numerator = internal->refresh;
    desktop_mode.refresh_rate_denominator = 1000;

    எனில் (internal->display > 0) {
        dpy = SDL_GetVideoDisplay(internal->display);
    } இல்லையெனில் {
        dpy = &internal->placeholder;
    }

    எனில் (video->scale_to_display_enabled) {
        SDL_SetDisplayContentScale(dpy, (தசம)internal->scale_factor);
    }

    // Set the desktop display mode.
    SDL_SetDesktopDisplayMode(dpy, &desktop_mode);

    // Expose the unscaled, native resolution if the scale is 1.0 or viewports are available...
    எனில் (internal->scale_factor == 1.0 || video->viewporter) {
        SDL_AddFullscreenDisplayMode(dpy, &native_mode);
        எனில் (native_mode.w != desktop_mode.w ||
            native_mode.h != desktop_mode.h) {
            SDL_AddFullscreenDisplayMode(dpy, &desktop_mode);
        }
    } இல்லையெனில் {
        // ...otherwise expose the integer scaled variants of the desktop resolution down to 1.
        desktop_mode.pixel_density = 1.0f;

        க்கு (முழு i = (முழு)internal->scale_factor; i > 0; --i) {
            desktop_mode.w = internal->logical.width * i;
            desktop_mode.h = internal->logical.height * i;
            SDL_AddFullscreenDisplayMode(dpy, &desktop_mode);
        }
    }

    // Add emulated modes if wp_viewporter is supported and mode emulation is enabled.
    எனில் (video->viewporter && mode_emulation_enabled) {
        // The transformed display pixel width/height must be used here.
        AddEmulatedModes(internal, native_mode.w, native_mode.h);
    }

    எனில் (internal->display == 0) {
        // First time getting display info, initialize the VideoDisplay
        எனில் (internal->physical.width_mm >= internal->physical.height_mm) {
            internal->placeholder.natural_orientation = SDL_ORIENTATION_LANDSCAPE;
        } இல்லையெனில் {
            internal->placeholder.natural_orientation = SDL_ORIENTATION_PORTRAIT;
        }
        internal->placeholder.current_orientation = internal->orientation;
        internal->placeholder.internal = internal;

        internal->placeholder.props = SDL_CreateProperties();
        SDL_SetPointerProperty(internal->placeholder.props, SDL_PROP_DISPLAY_WAYLAND_WL_OUTPUT_POINTER, internal->output);

        // During initialization, the displays will be added after enumeration is complete.
        எனில் (!video->initializing) {
            எனில் (video->wp_color_manager_v1) {
                Wayland_GetColorInfoForOutput(internal, false);
            }
            எனில் (video->scale_to_display_enabled) {
                Wayland_DeriveOutputPixelCoordinates(video);
            }

            internal->display = SDL_AddVideoDisplay(&internal->placeholder, true);
            Wayland_RefreshWindowPositions();

            SDL_free(internal->placeholder.name);
            SDL_zero(internal->placeholder);
        }
    } இல்லையெனில் {
        SDL_SendDisplayEvent(dpy, SDL_EVENT_DISPLAY_ORIENTATION, internal->orientation, 0);

        எனில் (internal->geometry_changed) {
            எனில் (video->scale_to_display_enabled) {
                Wayland_DeriveOutputPixelCoordinates(video);
            }

            SDL_SendDisplayEvent(dpy, SDL_EVENT_DISPLAY_MOVED, 0, 0);
            Wayland_RefreshWindowPositions();
        }
    }

    internal->geometry_changed = false;
}

நிலையான வெறுமை handle_wl_output_scale(வெறுமை *data, கட்டமைப்பு wl_output *output, int32_t factor)
{
    SDL_DisplayData *internal = (SDL_DisplayData *)data;
    internal->integer_scale_factor = factor;
}

நிலையான வெறுமை handle_wl_output_name(வெறுமை *data, கட்டமைப்பு wl_output *wl_output, மாறிலி எழுத்து *name)
{
    SDL_DisplayData *internal = (SDL_DisplayData *)data;

    SDL_free(internal->wl_output_name);
    internal->wl_output_name = SDL_strdup(name);
}

நிலையான வெறுமை handle_wl_output_description(வெறுமை *data, கட்டமைப்பு wl_output *wl_output, மாறிலி எழுத்து *description)
{
    SDL_DisplayData *internal = (SDL_DisplayData *)data;

    எனில் (internal->display == 0) {
        // The description, if available, supersedes the model name.
        SDL_free(internal->placeholder.name);
        internal->placeholder.name = SDL_strdup(description);
    }
}

நிலையான மாறிலி கட்டமைப்பு wl_output_listener output_listener = {
    handle_wl_output_geometry,   // Version 1
    handle_wl_output_mode,       // Version 1
    handle_wl_output_done,       // Version 2
    handle_wl_output_scale,      // Version 2
    handle_wl_output_name,       // Version 4
    handle_wl_output_description // Version 4
};

நிலையான வெறுமை handle_output_image_description_changed(வெறுமை *data,
                                                    கட்டமைப்பு wp_color_management_output_v1 *wp_color_management_output_v1)
{
    SDL_DisplayData *display = (SDL_DisplayData *)data;
    Wayland_GetColorInfoForOutput(display, false);
}

நிலையான மாறிலி கட்டமைப்பு wp_color_management_output_v1_listener wp_color_management_output_listener = {
    handle_output_image_description_changed
};

நிலையான bool Wayland_add_display(SDL_VideoData *d, uint32_t id, uint32_t version)
{
    கட்டமைப்பு wl_output *output;
    SDL_DisplayData *data;

    output = wl_registry_bind(d->registry, id, &wl_output_interface, version);
    எனில் (!output) {
        திரும்பு SDL_SetError("Failed to retrieve output.");
    }
    data = (SDL_DisplayData *)SDL_calloc(1, அளவு(*data));
    data->videodata = d;
    data->output = output;
    data->registry_id = id;
    data->scale_factor = 1.0f;
    data->integer_scale_factor = 1;

    wl_output_add_listener(output, &output_listener, data);
    SDL_WAYLAND_register_output(output);

    // Keep a list of outputs for sorting and deferred protocol initialization.
    எனில் (d->output_மொத்தம் == d->output_max) {
        d->output_max += 4;
        d->output_list = SDL_realloc(d->output_list, அளவு(SDL_DisplayData *) * d->output_max);
    }
    d->output_list[d->output_மொத்தம்++] = data;

    எனில் (data->videodata->xdg_output_manager) {
        data->xdg_output = zxdg_output_manager_v1_get_xdg_output(data->videodata->xdg_output_manager, output);
        zxdg_output_v1_add_listener(data->xdg_output, &xdg_output_listener, data);
    }
    எனில் (data->videodata->wp_color_manager_v1) {
        data->wp_color_management_output = wp_color_manager_v1_get_output(data->videodata->wp_color_manager_v1, output);
        wp_color_management_output_v1_add_listener(data->wp_color_management_output, &wp_color_management_output_listener, data);

        // If not initializing, this will be queried synchronously in wl_output.done.
        எனில் (d->initializing) {
            Wayland_GetColorInfoForOutput(data, true);
        }
    }
    திரும்பு true;
}

நிலையான வெறுமை Wayland_free_display(SDL_VideoDisplay *display, bool send_event)
{
    எனில் (display) {
        SDL_DisplayData *display_data = display->internal;

        /* A preceding surface leave event is not guaranteed when an output is removed,
         * so ensure that no window continues to hold a reference to a removed output.
         */
        க்கு (SDL_Window *window = SDL_GetVideoDevice()->windows; window; window = window->next) {
            Wayland_RemoveOutputFromWindow(window->internal, display_data);
        }

        SDL_free(display_data->wl_output_name);

        எனில் (display_data->wp_color_management_output) {
            Wayland_FreeColorInfoState(display_data->color_info_state);
            wp_color_management_output_v1_destroy(display_data->wp_color_management_output);
        }

        எனில் (display_data->xdg_output) {
            zxdg_output_v1_destroy(display_data->xdg_output);
        }

        எனில் (wl_output_get_version(display_data->output) >= WL_OUTPUT_RELEASE_SINCE_VERSION) {
            wl_output_release(display_data->output);
        } இல்லையெனில் {
            wl_output_destroy(display_data->output);
        }

        SDL_DelVideoDisplay(display->id, send_event);
    }
}

நிலையான வெறுமை Wayland_FinalizeDisplays(SDL_VideoData *vid)
{
    Wayland_SortOutputs(vid);

    க்கு(முழு i = 0; i < vid->output_மொத்தம்; ++i) {
        SDL_DisplayData *d = vid->output_list[i];
        d->display = SDL_AddVideoDisplay(&d->placeholder, false);
        SDL_free(d->placeholder.name);
        SDL_zero(d->placeholder);
    }
}

நிலையான வெறுமை Wayland_init_xdg_output(SDL_VideoData *d)
{
    க்கு (முழு i = 0; i < d->output_மொத்தம்; ++i) {
        SDL_DisplayData *disp = d->output_list[i];
        disp->xdg_output = zxdg_output_manager_v1_get_xdg_output(disp->videodata->xdg_output_manager, disp->output);
        zxdg_output_v1_add_listener(disp->xdg_output, &xdg_output_listener, disp);
    }
}

நிலையான வெறுமை Wayland_InitColorManager(SDL_VideoData *d)
{
    க்கு (முழு i = 0; i < d->output_மொத்தம்; ++i) {
        SDL_DisplayData *disp = d->output_list[i];
        disp->wp_color_management_output = wp_color_manager_v1_get_output(disp->videodata->wp_color_manager_v1, disp->output);
        wp_color_management_output_v1_add_listener(disp->wp_color_management_output, &wp_color_management_output_listener, disp);
        Wayland_GetColorInfoForOutput(disp, true);
    }
}

நிலையான வெறுமை handle_xdg_session_created(வெறுமை *data, கட்டமைப்பு xdg_session_v1 *xdg_session_v1, மாறிலி எழுத்து *id)
{
    SDL_SetStringProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, id);
}

நிலையான வெறுமை handle_xdg_session_restored(வெறுமை *data, கட்டமைப்பு xdg_session_v1 *xdg_session_v1)
{
    // NOP
}

நிலையான வெறுமை handle_xdg_session_replaced(வெறுமை *data, கட்டமைப்பு xdg_session_v1 *xdg_session_v1)
{
    SDL_VideoDevice *viddev = SDL_GetVideoDevice();
    SDL_VideoData *viddata = data;

    // Clean up all session objects, as they have become inert, and should be destroyed.
    SDL_SetStringProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, வெற்று);

    க்கு (SDL_Window *w = viddev->windows; w; w = w->next) {
        SDL_WindowData *d = w->internal;

        எனில் (d->xdg_toplevel_session) {
            xdg_toplevel_session_v1_destroy(d->xdg_toplevel_session);
            d->xdg_toplevel_session = வெற்று;

            SDL_free(d->session_id);
            d->session_id = வெற்று;
        }
    }

    எனில் (viddata->xdg_session) {
        xdg_session_v1_destroy(viddata->xdg_session);
        viddata->xdg_session = வெற்று;
    }
}

நிலையான மாறிலி கட்டமைப்பு xdg_session_v1_listener xdg_session_listener = {
    .created  = handle_xdg_session_created,
    .restored = handle_xdg_session_restored,
    .replaced = handle_xdg_session_replaced
};

வெறுமை Wayland_CreateSession(SDL_VideoData *viddata)
{
    எனில் (!viddata->xdg_session_manager) {
        // Set the ID string to null if session management is not available.
        SDL_SetStringProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, வெற்று);
        திரும்பு;
    }

    // Register a new session, if one does not yet exist.
    எனில் (!viddata->xdg_session) {
        மாறிலி எழுத்து *session_id = SDL_GetStringProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, வெற்று);
        எனில் (session_id) {
            எனில் (*session_id == '\0') {
                // Create a new session if the ID string is empty.
                session_id = வெற்று;
            }

            மாறிலி எண்ணிக்கை xdg_session_manager_v1_reason reason = session_id ? XDG_SESSION_MANAGER_V1_REASON_SESSION_RESTORE : XDG_SESSION_MANAGER_V1_REASON_LAUNCH;
            viddata->xdg_session = xdg_session_manager_v1_get_session(viddata->xdg_session_manager, reason, session_id);
            xdg_session_v1_add_listener(viddata->xdg_session, &xdg_session_listener, viddata);
        }
    }
}

நிலையான வெறுமை Wayland_SessionDestroy(SDL_VideoData *viddata)
{
    // If the session string was cleared, remove the session.
    எனில் (viddata->xdg_session) {
        மாறிலி எழுத்து *session_id = SDL_GetStringProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, வெற்று);
        எனில் (!session_id || *session_id == '\0') {
            xdg_session_v1_remove(viddata->xdg_session);

            WAYLAND_wl_display_roundtrip(viddata->display);
        } இல்லையெனில் {
            xdg_session_v1_destroy(viddata->xdg_session);
        }

        viddata->xdg_session = வெற்று;
    }
}

நிலையான வெறுமை handle_xdg_wm_base_ping(வெறுமை *data, கட்டமைப்பு xdg_wm_base *xdg, uint32_t serial)
{
    xdg_wm_base_pong(xdg, serial);
}

நிலையான மாறிலி கட்டமைப்பு xdg_wm_base_listener _xdg_wm_base_listener = {
    handle_xdg_wm_base_ping
};

#ifdef HAVE_LIBDECOR_H
நிலையான வெறுமை libdecor_error(கட்டமைப்பு libdecor *context,
                           எண்ணிக்கை libdecor_error error,
                           மாறிலி எழுத்து *message)
{
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "libdecor error (%d): %s", error, message);
}

நிலையான கட்டமைப்பு libdecor_interface libdecor_interface = {
    libdecor_error
};
#endif

நிலையான வெறுமை handle_registry_global(வெறுமை *data, கட்டமைப்பு wl_registry *registry, uint32_t id,
                                   மாறிலி எழுத்து *interface, uint32_t version)
{
    SDL_VideoData *d = data;

    எனில் (SDL_strcmp(interface, wl_compositor_interface.name) == 0) {
        d->compositor = wl_registry_bind(d->registry, id, &wl_compositor_interface, SDL_min(SDL_WL_COMPOSITOR_VERSION, version));
    } இல்லையெனில் எனில் (SDL_strcmp(interface, wl_subcompositor_interface.name) == 0) {
        d->subcompositor = wl_registry_bind(d->registry, id, &wl_subcompositor_interface, 1);
    } இல்லையெனில் எனில் (SDL_strcmp(interface, wl_output_interface.name) == 0) {
        Wayland_add_display(d, id, SDL_min(version, SDL_WL_OUTPUT_VERSION));
    } இல்லையெனில் எனில் (SDL_strcmp(interface, wl_seat_interface.name) == 0) {
        கட்டமைப்பு wl_seat *seat = wl_registry_bind(d->registry, id, &wl_seat_interface, SDL_min(SDL_WL_SEAT_VERSION, version));
        Wayland_DisplayCreateSeat(d, seat, id);
    } இல்லையெனில் எனில் (SDL_strcmp(interface, xdg_wm_base_interface.name) == 0) {
        d->shell.xdg = wl_registry_bind(d->registry, id, &xdg_wm_base_interface, SDL_min(version, 7));
        xdg_wm_base_add_listener(d->shell.xdg, &_xdg_wm_base_listener, வெற்று);
    } இல்லையெனில் எனில் (SDL_strcmp(interface, wl_shm_interface.name) == 0) {
        d->shm = wl_registry_bind(registry, id, &wl_shm_interface, SDL_min(SDL_WL_SHM_VERSION, version));
    } இல்லையெனில் எனில் (SDL_strcmp(interface, zwp_relative_pointer_manager_v1_interface.name) == 0) {
        d->relative_pointer_manager = wl_registry_bind(d->registry, id, &zwp_relative_pointer_manager_v1_interface, 1);
    } இல்லையெனில் எனில் (SDL_strcmp(interface, zwp_pointer_constraints_v1_interface.name) == 0) {
        d->pointer_constraints = wl_registry_bind(d->registry, id, &zwp_pointer_constraints_v1_interface, 1);
    } இல்லையெனில் எனில் (SDL_strcmp(interface, zwp_keyboard_shortcuts_inhibit_manager_v1_interface.name) == 0) {
        d->சாவி_inhibitor_manager = wl_registry_bind(d->registry, id, &zwp_keyboard_shortcuts_inhibit_manager_v1_interface, 1);
    } இல்லையெனில் எனில் (SDL_strcmp(interface, zwp_idle_inhibit_manager_v1_interface.name) == 0) {
        d->idle_inhibit_manager = wl_registry_bind(d->registry, id, &zwp_idle_inhibit_manager_v1_interface, 1);
    } இல்லையெனில் எனில் (SDL_strcmp(interface, xdg_activation_v1_interface.name) == 0) {
        d->activation_manager = wl_registry_bind(d->registry, id, &xdg_activation_v1_interface, 1);
    } இல்லையெனில் எனில் (SDL_strcmp(interface, zwp_text_உள்ளீடு_manager_v3_interface.name) == 0) {
        d->text_உள்ளீடு_manager = wl_registry_bind(d->registry, id, &zwp_text_உள்ளீடு_manager_v3_interface, 1);
        Wayland_Display_Init_Text_உள்ளீடு_Manager(d, id);
    } இல்லையெனில் எனில் (SDL_strcmp(interface, wl_data_device_manager_interface.name) == 0) {
        d->data_device_manager = wl_registry_bind(d->registry, id, &wl_data_device_manager_interface, SDL_min(3, version));
        Wayland_DisplayInitDataDeviceManager(d);
    } இல்லையெனில் எனில் (SDL_strcmp(interface, zwp_primary_selection_device_manager_v1_interface.name) == 0) {
        d->primary_selection_device_manager = wl_registry_bind(d->registry, id, &zwp_primary_selection_device_manager_v1_interface, 1);
        Wayland_DisplayInitPrimarySelectionDeviceManager(d);
    } இல்லையெனில் எனில் (SDL_strcmp(interface, zxdg_decoration_manager_v1_interface.name) == 0) {
        d->decoration_manager = wl_registry_bind(d->registry, id, &zxdg_decoration_manager_v1_interface, SDL_min(2, version));
    } இல்லையெனில் எனில் (SDL_strcmp(interface, zwp_tablet_manager_v2_interface.name) == 0) {
        d->tablet_manager = wl_registry_bind(d->registry, id, &zwp_tablet_manager_v2_interface, 1);
        Wayland_DisplayInitTabletManager(d);
    } இல்லையெனில் எனில் (SDL_strcmp(interface, zxdg_output_manager_v1_interface.name) == 0) {
        version = SDL_min(version, 3); // Versions 1 through 3 are supported.
        d->xdg_output_manager = wl_registry_bind(d->registry, id, &zxdg_output_manager_v1_interface, version);
        Wayland_init_xdg_output(d);
    } இல்லையெனில் எனில் (SDL_strcmp(interface, wp_viewporter_interface.name) == 0) {
        d->viewporter = wl_registry_bind(d->registry, id, &wp_viewporter_interface, 1);
    } இல்லையெனில் எனில் (SDL_strcmp(interface, wp_fractional_scale_manager_v1_interface.name) == 0) {
        d->fractional_scale_manager = wl_registry_bind(d->registry, id, &wp_fractional_scale_manager_v1_interface, 1);
    } இல்லையெனில் எனில் (SDL_strcmp(interface, zwp_உள்ளீடு_timestamps_manager_v1_interface.name) == 0) {
        d->உள்ளீடு_timestamps_manager = wl_registry_bind(d->registry, id, &zwp_உள்ளீடு_timestamps_manager_v1_interface, 1);
        Wayland_Display_Init_உள்ளீடு_Timestamp_Manager(d);
    } இல்லையெனில் எனில் (SDL_strcmp(interface, wp_cursor_shape_manager_v1_interface.name) == 0) {
        d->cursor_shape_manager = wl_registry_bind(d->registry, id, &wp_cursor_shape_manager_v1_interface, SDL_min(version, 2));
        Wayland_DisplayInitCursorShapeManager(d);
    } இல்லையெனில் எனில் (SDL_strcmp(interface, zxdg_exporter_v2_interface.name) == 0) {
        d->zxdg_exporter_v2 = wl_registry_bind(d->registry, id, &zxdg_exporter_v2_interface, 1);
    } இல்லையெனில் எனில் (SDL_strcmp(interface, xdg_wm_dialog_v1_interface.name) == 0) {
        d->xdg_wm_dialog_v1 = wl_registry_bind(d->registry, id, &xdg_wm_dialog_v1_interface, 1);
    } இல்லையெனில் எனில் (SDL_strcmp(interface, wp_alpha_modifier_v1_interface.name) == 0) {
        d->wp_alpha_modifier_v1 = wl_registry_bind(d->registry, id, &wp_alpha_modifier_v1_interface, 1);
    } இல்லையெனில் எனில் (SDL_strcmp(interface, xdg_toplevel_icon_manager_v1_interface.name) == 0) {
        d->xdg_toplevel_icon_manager_v1 = wl_registry_bind(d->registry, id, &xdg_toplevel_icon_manager_v1_interface, 1);
    } இல்லையெனில் எனில் (SDL_strcmp(interface, frog_color_management_factory_v1_interface.name) == 0) {
        d->frog_color_management_factory_v1 = wl_registry_bind(d->registry, id, &frog_color_management_factory_v1_interface, 1);
    } இல்லையெனில் எனில் (SDL_strcmp(interface, wp_color_manager_v1_interface.name) == 0) {
        d->wp_color_manager_v1 = wl_registry_bind(d->registry, id, &wp_color_manager_v1_interface, SDL_min(version, 2));
        Wayland_InitColorManager(d);
    } இல்லையெனில் எனில் (SDL_strcmp(interface, wp_pointer_warp_v1_interface.name) == 0) {
        d->wp_pointer_warp_v1 = wl_registry_bind(d->registry, id, &wp_pointer_warp_v1_interface, 1);
    } இல்லையெனில் எனில் (SDL_strcmp(interface, zwp_pointer_gestures_v1_interface.name) == 0) {
        d->zwp_pointer_gestures = wl_registry_bind(d->registry, id, &zwp_pointer_gestures_v1_interface, SDL_min(version, 3));
        Wayland_DisplayInitPointerGestureManager(d);
    } இல்லையெனில் எனில் (SDL_strcmp(interface, wp_single_pixel_buffer_manager_v1_interface.name) == 0) {
        d->single_pixel_buffer_manager = wl_registry_bind(d->registry, id, &wp_single_pixel_buffer_manager_v1_interface, 1);
    } இல்லையெனில் எனில் (SDL_strcmp(interface, xdg_session_manager_v1_interface.name) == 0) {
        d->xdg_session_manager = wl_registry_bind(d->registry, id, &xdg_session_manager_v1_interface, 1);
    } இல்லையெனில் எனில் (SDL_strcmp(interface, xdg_toplevel_tag_manager_v1_interface.name) == 0) {
        d->xdg_toplevel_tag_manager = wl_registry_bind(d->registry, id, &xdg_toplevel_tag_manager_v1_interface, 1);
    }
#ifdef SDL_WL_FIXES_VERSION
    இல்லையெனில் எனில் (SDL_strcmp(interface, wl_fixes_interface.name) == 0) {
        d->wl_fixes = wl_registry_bind(d->registry, id, &wl_fixes_interface, SDL_min(SDL_WL_FIXES_VERSION, version));
    }
#endif
}

நிலையான வெறுமை handle_registry_remove_global(வெறுமை *data, கட்டமைப்பு wl_registry *registry, uint32_t id)
{
    SDL_VideoData *d = data;

    // We don't get an interface, just an ID, so check outputs and seats.
    க்கு (முழு i = 0; i < d->output_மொத்தம்; ++i) {
        SDL_DisplayData *disp = d->output_list[i];
        எனில் (disp->registry_id == id) {
            Wayland_free_display(SDL_GetVideoDisplay(disp->display), true);

            எனில் (i < d->output_மொத்தம்) {
                SDL_memmove(&d->output_list[i], &d->output_list[i + 1], அளவு(SDL_DisplayData *) * (d->output_மொத்தம் - i - 1));
            }

            d->output_மொத்தம்--;
            செல் ack_remove;
        }
    }

    SDL_WaylandSeat *seat, *temp;
    wl_list_for_each_safe (seat, temp, &d->seat_list, link) {
        எனில் (seat->registry_id == id) {
            Wayland_SeatDestroy(seat, false);
            செல் ack_remove;
        }
    }

ack_remove:
    எனில் (d->wl_fixes && wl_fixes_get_version(d->wl_fixes) >= WL_FIXES_ACK_GLOBAL_REMOVE_SINCE_VERSION) {
        wl_fixes_ack_global_remove(d->wl_fixes, registry, id);
    }
}

நிலையான மாறிலி கட்டமைப்பு wl_registry_listener registry_listener = {
    handle_registry_global,
    handle_registry_remove_global
};

#ifdef HAVE_LIBDECOR_H
நிலையான bool should_use_libdecor(SDL_VideoData *data, bool ignore_xdg)
{
    எனில் (!SDL_WAYLAND_HAVE_WAYLAND_LIBDECOR) {
        திரும்பு false;
    }

    எனில் (SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_PREFER_LIBDECOR, false)) {
        திரும்பு true;
    }

    எனில் (ignore_xdg) {
        திரும்பு true;
    }

    எனில் (data->decoration_manager) {
        திரும்பு false;
    }

    திரும்பு true;
}

நிலையான வெறுமை LibdecorNew(SDL_VideoData *data)
{
    data->shell.libdecor = libdecor_new(data->display, &libdecor_interface);
}

// Called in another thread, but the UI thread is blocked in SDL_WaitThread
// during that time, so it should be OK to dereference data without locks
நிலையான முழு SDLCALL LibdecorNewInThread(வெறுமை *data)
{
    LibdecorNew((SDL_VideoData *)data);
    திரும்பு 0;
}
#endif

#ifdef HAVE_GETRESUID
#define SDL_getresuid getresuid
#இல்லையெனில்
// Non-POSIX, but Linux and some BSDs have it.
// To reduce the number of code paths, if getresuid() isn't available at
// compile-time, we behave as though it existed but failed at runtime.
நிலையான உள்வரி முழு SDL_getresuid(uid_t *ruid, uid_t *euid, uid_t *suid) {
    errno = ENOSYS;
    திரும்பு -1;
}
#endif

#ifdef HAVE_GETRESGID
#define SDL_getresgid getresgid
#இல்லையெனில்
// Same as getresuid() but for the primary group
நிலையான உள்வரி முழு SDL_getresgid(gid_t *rgid, gid_t *egid, gid_t *sgid) {
    errno = ENOSYS;
    திரும்பு -1;
}
#endif

bool CanUseGtk(வெறுமை)
{
    // "Real", "effective" and "saved" IDs: see e.g. Linux credentials(7)
    uid_t ruid = -1, euid = -1, suid = -1;
    gid_t rgid = -1, egid = -1, sgid = -1;

    எனில் (!SDL_GetHintBoolean("SDL_ENABLE_GTK", true)) {
        SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "Not using GTK due to hint");
        திரும்பு false;
    }

    // This is intended to match the check in gtkmain.c, rather than being
    // an exhaustive check for having elevated privileges: as a result
    // we don't use Linux getauxval() or prctl PR_GET_DUMPABLE,
    // BSD issetugid(), or similar OS-specific detection

    எனில் (SDL_getresuid(&ruid, &euid, &suid) != 0) {
        ruid = suid = getuid();
        euid = geteuid();
    }

    எனில் (SDL_getresgid(&rgid, &egid, &sgid) != 0) {
        rgid = sgid = getgid();
        egid = getegid();
    }

    // Real ID != effective ID means we are setuid or setgid:
    // GTK will refuse to initialize, and instead will call exit().
    எனில் (ruid != euid || rgid != egid) {
        SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "Not using GTK due to setuid/setgid");
        திரும்பு false;
    }

    // Real ID != saved ID means we are setuid or setgid, we previously
    // dropped privileges, but we can regain them; this protects against
    // accidents but does not protect against arbitrary code execution.
    // Again, GTK will refuse to initialize if this is the case.
    எனில் (ruid != suid || rgid != sgid) {
        SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "Not using GTK due to saved uid/gid");
        திரும்பு false;
    }

    திரும்பு true;
}

bool Wayland_LoadLibdecor(SDL_VideoData *data, bool ignore_xdg)
{
#ifdef HAVE_LIBDECOR_H
    எனில் (data->shell.libdecor != வெற்று) {
        திரும்பு true; // Already loaded!
    }
    எனில் (should_use_libdecor(data, ignore_xdg)) {
        எனில் (CanUseGtk()) {
            LibdecorNew(data);
        } இல்லையெனில் {
            // Intentionally initialize libdecor in a non-main thread
            // so that it will not use its GTK plugin, but instead will
            // fall back to the Cairo or dummy plugin
            SDL_Thread *thread = SDL_CreateThread(LibdecorNewInThread, "SDL_LibdecorNew", (வெறுமை *)data);
            // Note that the other thread now "owns" data until we have
            // waited for it, so don't touch data here
            SDL_WaitThread(thread, வெற்று);
        }

        திரும்பு data->shell.libdecor != வெற்று;
    }
#endif
    திரும்பு false;
}

bool Wayland_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

    data->event_thread_context = Wayland_CreateEventThread(data, "SDL Event Thread Queue");
    எனில் (!data->event_thread_context) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Failed to create event thread context");
    }

    data->job_thread_context = Wayland_CreateJobThread();
    எனில் (!data->job_thread_context) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Failed to create job thread context");
    }

    data->xkb_context = WAYLAND_xkb_context_new(0);
    எனில் (!data->xkb_context) {
        திரும்பு SDL_SetError("Failed to create XKB context");
    }

    data->registry = wl_display_get_registry(data->display);
    எனில் (!data->registry) {
        திரும்பு SDL_SetError("Failed to get the Wayland registry");
    }

    wl_registry_add_listener(data->registry, &registry_listener, data);

    // First roundtrip to receive all registry objects.
    WAYLAND_wl_display_roundtrip(data->display);

    // Require viewports and xdg-output for display scaling.
    எனில் (data->scale_to_display_enabled) {
        எனில் (!data->viewporter) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Display scaling requires the missing 'wp_viewporter' protocol: disabling");
            data->scale_to_display_enabled = false;
        }
        எனில் (!data->xdg_output_manager) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Display scaling requires the missing 'zxdg_output_manager_v1' protocol: disabling");
            data->scale_to_display_enabled = false;
        }
    }

    // Now that we have all the protocols, load libdecor if applicable
    Wayland_LoadLibdecor(data, false);

    // Second roundtrip to receive all output events.
    WAYLAND_wl_display_roundtrip(data->display);

    Wayland_FinalizeDisplays(data);

    Wayland_InitMouse(data);
    Wayland_InitKeyboard(_this);

    எனில் (data->primary_selection_device_manager) {
        _this->SetPrimarySelectionText = Wayland_SetPrimarySelectionText;
        _this->GetPrimarySelectionText = Wayland_GetPrimarySelectionText;
        _this->HasPrimarySelectionText = Wayland_HasPrimarySelectionText;
    }

    data->initializing = false;

    திரும்பு true;
}

நிலையான bool Wayland_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    SDL_VideoData *viddata = _this->internal;
    SDL_DisplayData *internal = display->internal;

    எனில் (!viddata->scale_to_display_enabled) {
        rect->x = internal->logical.x;
        rect->y = internal->logical.y;
    } இல்லையெனில் {
        rect->x = internal->pixel.x;
        rect->y = internal->pixel.y;
    }

    // When an emulated, exclusive fullscreen window has focus, treat the mode dimensions as the display bounds.
    எனில் (display->fullscreen_window &&
        display->fullscreen_window->fullscreen_exclusive &&
        display->fullscreen_window->internal->active &&
        display->fullscreen_window->current_fullscreen_mode.w != 0 &&
        display->fullscreen_window->current_fullscreen_mode.h != 0) {
        rect->w = display->fullscreen_window->current_fullscreen_mode.w;
        rect->h = display->fullscreen_window->current_fullscreen_mode.h;
    } இல்லையெனில் {
        எனில் (!viddata->scale_to_display_enabled) {
            rect->w = display->current_mode->w;
            rect->h = display->current_mode->h;
        } இல்லையெனில் எனில் (internal->transform & WL_OUTPUT_TRANSFORM_90) {
            rect->w = internal->pixel.height;
            rect->h = internal->pixel.width;
        } இல்லையெனில் {
            rect->w = internal->pixel.width;
            rect->h = internal->pixel.height;
        }
    }
    திரும்பு true;
}

நிலையான வெறுமை Wayland_VideoCleanup(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    SDL_WaylandSeat *seat, *tmp;

    Wayland_SessionDestroy(data);

    க்கு (முழு i = _this->இலக்கம்_displays - 1; i >= 0; --i) {
        SDL_VideoDisplay *display = _this->displays[i];
        Wayland_free_display(display, false);
    }
    SDL_free(data->output_list);

    wl_list_for_each_safe (seat, tmp, &data->seat_list, link) {
        Wayland_SeatDestroy(seat, true);
    }

    Wayland_FiniMouse(data);
    Wayland_QuitKeyboard(_this);

    Wayland_DestroyEventThread(data->event_thread_context);
    data->event_thread_context = வெற்று;

    Wayland_DestroyJobThread(data->job_thread_context);
    data->job_thread_context = வெற்று;

    எனில் (data->pointer_constraints) {
        zwp_pointer_constraints_v1_destroy(data->pointer_constraints);
        data->pointer_constraints = வெற்று;
    }

    எனில் (data->relative_pointer_manager) {
        zwp_relative_pointer_manager_v1_destroy(data->relative_pointer_manager);
        data->relative_pointer_manager = வெற்று;
    }

    எனில் (data->activation_manager) {
        xdg_activation_v1_destroy(data->activation_manager);
        data->activation_manager = வெற்று;
    }

    எனில் (data->idle_inhibit_manager) {
        zwp_idle_inhibit_manager_v1_destroy(data->idle_inhibit_manager);
        data->idle_inhibit_manager = வெற்று;
    }

    எனில் (data->சாவி_inhibitor_manager) {
        zwp_keyboard_shortcuts_inhibit_manager_v1_destroy(data->சாவி_inhibitor_manager);
        data->சாவி_inhibitor_manager = வெற்று;
    }

    எனில் (data->text_உள்ளீடு_manager) {
        zwp_text_உள்ளீடு_manager_v3_destroy(data->text_உள்ளீடு_manager);
        data->text_உள்ளீடு_manager = வெற்று;
    }

    எனில் (data->xkb_context) {
        WAYLAND_xkb_context_unref(data->xkb_context);
        data->xkb_context = வெற்று;
    }

    எனில் (data->tablet_manager) {
        zwp_tablet_manager_v2_destroy((கட்டமைப்பு zwp_tablet_manager_v2 *)data->tablet_manager);
        data->tablet_manager = வெற்று;
    }

    எனில் (data->data_device_manager) {
        wl_data_device_manager_destroy(data->data_device_manager);
        data->data_device_manager = வெற்று;
    }

    எனில் (data->shm) {
        எனில் (wl_shm_get_version(data->shm) >= WL_SHM_RELEASE_SINCE_VERSION) {
            wl_shm_release(data->shm);
        } இல்லையெனில் {
            wl_shm_destroy(data->shm);
        }
        data->shm = வெற்று;
    }

    எனில் (data->shell.xdg) {
        xdg_wm_base_destroy(data->shell.xdg);
        data->shell.xdg = வெற்று;
    }

    எனில் (data->decoration_manager) {
        zxdg_decoration_manager_v1_destroy(data->decoration_manager);
        data->decoration_manager = வெற்று;
    }

    எனில் (data->xdg_output_manager) {
        zxdg_output_manager_v1_destroy(data->xdg_output_manager);
        data->xdg_output_manager = வெற்று;
    }

    எனில் (data->viewporter) {
        wp_viewporter_destroy(data->viewporter);
        data->viewporter = வெற்று;
    }

    எனில் (data->primary_selection_device_manager) {
        zwp_primary_selection_device_manager_v1_destroy(data->primary_selection_device_manager);
        data->primary_selection_device_manager = வெற்று;
    }

    எனில் (data->fractional_scale_manager) {
        wp_fractional_scale_manager_v1_destroy(data->fractional_scale_manager);
        data->fractional_scale_manager = வெற்று;
    }

    எனில் (data->உள்ளீடு_timestamps_manager) {
        zwp_உள்ளீடு_timestamps_manager_v1_destroy(data->உள்ளீடு_timestamps_manager);
        data->உள்ளீடு_timestamps_manager = வெற்று;
    }

    எனில் (data->cursor_shape_manager) {
        wp_cursor_shape_manager_v1_destroy(data->cursor_shape_manager);
        data->cursor_shape_manager = வெற்று;
    }

    எனில் (data->zxdg_exporter_v2) {
        zxdg_exporter_v2_destroy(data->zxdg_exporter_v2);
        data->zxdg_exporter_v2 = வெற்று;
    }

    எனில் (data->xdg_wm_dialog_v1) {
        xdg_wm_dialog_v1_destroy(data->xdg_wm_dialog_v1);
        data->xdg_wm_dialog_v1 = வெற்று;
    }

    எனில் (data->wp_alpha_modifier_v1) {
        wp_alpha_modifier_v1_destroy(data->wp_alpha_modifier_v1);
        data->wp_alpha_modifier_v1 = வெற்று;
    }

    எனில் (data->xdg_toplevel_icon_manager_v1) {
        xdg_toplevel_icon_manager_v1_destroy(data->xdg_toplevel_icon_manager_v1);
        data->xdg_toplevel_icon_manager_v1 = வெற்று;
    }

    எனில் (data->frog_color_management_factory_v1) {
        frog_color_management_factory_v1_destroy(data->frog_color_management_factory_v1);
        data->frog_color_management_factory_v1 = வெற்று;
    }

    எனில் (data->wp_color_manager_v1) {
        wp_color_manager_v1_destroy(data->wp_color_manager_v1);
        data->wp_color_manager_v1 = வெற்று;
    }

    எனில் (data->wp_pointer_warp_v1) {
        wp_pointer_warp_v1_destroy(data->wp_pointer_warp_v1);
        data->wp_pointer_warp_v1 = வெற்று;
    }

    எனில் (data->zwp_pointer_gestures) {
        எனில் (zwp_pointer_gestures_v1_get_version(data->zwp_pointer_gestures) >= ZWP_POINTER_GESTURES_V1_RELEASE_SINCE_VERSION) {
            zwp_pointer_gestures_v1_release(data->zwp_pointer_gestures);
        } இல்லையெனில் {
            zwp_pointer_gestures_v1_destroy(data->zwp_pointer_gestures);
        }
        data->zwp_pointer_gestures = வெற்று;
    }

    எனில் (data->single_pixel_buffer_manager) {
        wp_single_pixel_buffer_manager_v1_destroy(data->single_pixel_buffer_manager);
        data->single_pixel_buffer_manager = வெற்று;
    }

    எனில் (data->xdg_session_manager) {
        xdg_session_manager_v1_destroy(data->xdg_session_manager);
        data->xdg_session_manager = வெற்று;
    }

    எனில் (data->xdg_toplevel_tag_manager) {
        xdg_toplevel_tag_manager_v1_destroy(data->xdg_toplevel_tag_manager);
        data->xdg_toplevel_tag_manager = வெற்று;
    }

    எனில் (data->subcompositor) {
        wl_subcompositor_destroy(data->subcompositor);
        data->subcompositor = வெற்று;
    }

    எனில் (data->compositor) {
        wl_compositor_destroy(data->compositor);
        data->compositor = வெற்று;
    }

    எனில் (data->registry) {
        எனில் (data->wl_fixes) {
            wl_fixes_destroy_registry(data->wl_fixes, data->registry);
            wl_fixes_destroy(data->wl_fixes);
            data->wl_fixes = வெற்று;
        }
        wl_registry_destroy(data->registry);
        data->registry = வெற்று;
    }
}

நிலையான bool Wayland_VideoReconnect(SDL_VideoDevice *_this)
{
#எனில் 0 // TODO RECONNECT: Uncomment all when https://invent.kde.org/plasma/kwin/-/wikis/Restarting is completed
    SDL_VideoData *data = _this->internal;

    SDL_Window *window = வெற்று;

    SDL_GLContext current_ctx = SDL_GL_GetCurrentContext();
    SDL_Window *current_window = SDL_GL_GetCurrentWindow();

    SDL_GL_MakeCurrent(வெற்று, வெற்று);
    Wayland_VideoCleanup(_this);

    SDL_ResetKeyboard();
    SDL_ResetMouse();
    எனில் (WAYLAND_wl_display_reconnect(data->display) < 0) {
        திரும்பு false;
    }

    Wayland_VideoInit(_this);

    window = _this->windows;
    போது (window) {
        /* We're going to cheat _just_ for a second and strip the OpenGL flag.
         * The Wayland driver actually forces it in CreateWindow, and
         * RecreateWindow does a bunch of unloading/loading of libGL, so just
         * strip the flag so RecreateWindow doesn't mess with the GL context,
         * and CreateWindow will add it right back!
         * -flibit
         */
        window->flags &= ~SDL_WINDOW_OPENGL;

        SDL_RecreateWindow(window, window->flags);
        window = window->next;
    }

    Wayland_RecreateCursors();

    எனில் (current_window && current_ctx) {
        SDL_GL_MakeCurrent (current_window, current_ctx);
    }
    திரும்பு true;
#இல்லையெனில்
    திரும்பு false;
#endif // 0
}

bool Wayland_HandleDisplayDisconnected(SDL_VideoDevice *_this)
{
    SDL_VideoData *video_data = _this->internal;

    /* Something has failed with the Wayland connection -- for example,
     * the compositor may have shut down and closed its end of the socket,
     * or there is a library-specific error.
     *
     * Try to recover once, then quit.
     */
    எனில் (video_data->display_disconnected) {
        திரும்பு false;
    }

    எனில் (Wayland_VideoReconnect(_this)) {
        திரும்பு true;
    }

    video_data->display_disconnected = true;
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Wayland display connection closed by server (fatal)");

    // Only send a single quit message, as application shutdown might call SDL_PumpEvents().
    SDL_SendQuit();

    திரும்பு false;
}

வெறுமை Wayland_VideoQuit(SDL_VideoDevice *_this)
{
    Wayland_VideoCleanup(_this);

#ifdef HAVE_LIBDECOR_H
    SDL_VideoData *data = _this->internal;
    எனில் (data->shell.libdecor) {
        libdecor_unref(data->shell.libdecor);
        data->shell.libdecor = வெற்று;
    }
#endif
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
