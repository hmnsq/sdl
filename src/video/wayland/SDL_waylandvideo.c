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

#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#অন্তর্ভাব "../../core/linux/SDL_system_theme.h"
#অন্তর্ভাব "../../core/linux/SDL_progressbar.h"
#অন্তর্ভাব "../../events/SDL_events_c.h"

#অন্তর্ভাব "SDL_waylandclipboard.h"
#অন্তর্ভাব "SDL_waylandcolor.h"
#অন্তর্ভাব "SDL_waylandevents_c.h"
#অন্তর্ভাব "SDL_waylandkeyboard.h"
#অন্তর্ভাব "SDL_waylandmessagebox.h"
#অন্তর্ভাব "SDL_waylandmouse.h"
#অন্তর্ভাব "SDL_waylandopengles.h"
#অন্তর্ভাব "SDL_waylandvideo.h"
#অন্তর্ভাব "SDL_waylandvulkan.h"
#অন্তর্ভাব "SDL_waylandwindow.h"

#অন্তর্ভাব <fcntl.h>
#অন্তর্ভাব <sys/types.h>
#অন্তর্ভাব <unistd.h>
#অন্তর্ভাব <errno.h>
#অন্তর্ভাব <xkbcommon/xkbcommon.h>

#অন্তর্ভাব <wayland-util.h>

#অন্তর্ভাব "alpha-modifier-v1-client-protocol.h"
#অন্তর্ভাব "cursor-shape-v1-client-protocol.h"
#অন্তর্ভাব "fractional-scale-v1-client-protocol.h"
#অন্তর্ভাব "frog-color-management-v1-client-protocol.h"
#অন্তর্ভাব "idle-inhibit-unstable-v1-client-protocol.h"
#অন্তর্ভাব "input-timestamps-unstable-v1-client-protocol.h"
#অন্তর্ভাব "keyboard-shortcuts-inhibit-unstable-v1-client-protocol.h"
#অন্তর্ভাব "pointer-constraints-unstable-v1-client-protocol.h"
#অন্তর্ভাব "primary-selection-unstable-v1-client-protocol.h"
#অন্তর্ভাব "relative-pointer-unstable-v1-client-protocol.h"
#অন্তর্ভাব "tablet-v2-client-protocol.h"
#অন্তর্ভাব "text-input-unstable-v3-client-protocol.h"
#অন্তর্ভাব "viewporter-client-protocol.h"
#অন্তর্ভাব "xdg-activation-v1-client-protocol.h"
#অন্তর্ভাব "xdg-decoration-unstable-v1-client-protocol.h"
#অন্তর্ভাব "xdg-dialog-v1-client-protocol.h"
#অন্তর্ভাব "xdg-foreign-unstable-v2-client-protocol.h"
#অন্তর্ভাব "xdg-output-unstable-v1-client-protocol.h"
#অন্তর্ভাব "xdg-shell-client-protocol.h"
#অন্তর্ভাব "xdg-toplevel-icon-v1-client-protocol.h"
#অন্তর্ভাব "color-management-v1-client-protocol.h"
#অন্তর্ভাব "pointer-warp-v1-client-protocol.h"
#অন্তর্ভাব "pointer-gestures-unstable-v1-client-protocol.h"
#অন্তর্ভাব "single-pixel-buffer-v1-client-protocol.h"
#অন্তর্ভাব "xdg-session-management-v1-client-protocol.h"
#অন্তর্ভাব "xdg-toplevel-tag-v1-client-protocol.h"

#ifdef HAVE_LIBDECOR_H
#অন্তর্ভাব <libdecor.h>
#endif

#define WAYLANDVID_DRIVER_NAME "wayland"

// Clamp core protocol versions on older versions of libwayland.
#যদি SDL_WAYLAND_CHECK_VERSION(1, 22, 0)
#define SDL_WL_COMPOSITOR_VERSION 6
#অন্যথা
#define SDL_WL_COMPOSITOR_VERSION 4
#endif

#যদি SDL_WAYLAND_CHECK_VERSION(1, 26, 0)
#define SDL_WL_SEAT_VERSION 11
#নতুবা_যদি SDL_WAYLAND_CHECK_VERSION(1, 24, 0)
#define SDL_WL_SEAT_VERSION 10
#নতুবা_যদি SDL_WAYLAND_CHECK_VERSION(1, 22, 0)
#define SDL_WL_SEAT_VERSION 9
#নতুবা_যদি SDL_WAYLAND_CHECK_VERSION(1, 21, 0)
#define SDL_WL_SEAT_VERSION 8
#অন্যথা
#define SDL_WL_SEAT_VERSION 5
#endif

#যদি SDL_WAYLAND_CHECK_VERSION(1, 20, 0)
#define SDL_WL_OUTPUT_VERSION 4
#অন্যথা
#define SDL_WL_OUTPUT_VERSION 3
#endif

#যদি SDL_WAYLAND_CHECK_VERSION(1, 24, 0)
#define SDL_WL_SHM_VERSION 2
#অন্যথা
#define SDL_WL_SHM_VERSION 1
#endif

// The SDL libwayland-client minimum is 1.18, which supports version 3.
#define SDL_WL_তথ্য_DEVICE_VERSION 3

// wl_fixes was introduced in 1.24.0
#যদি SDL_WAYLAND_CHECK_VERSION(1, 26, 0)
#define SDL_WL_FIXES_VERSION 2
#নতুবা_যদি SDL_WAYLAND_CHECK_VERSION(1, 24, 0)
#define SDL_WL_FIXES_VERSION 1
#endif

#ifdef SDL_USE_LIBDBUS
#অন্তর্ভাব "../../core/linux/SDL_dbus.h"

#define DISPLAY_INFO_গ্রন্থি   "org.gnome.Mutter.DisplayConfig"
#define DISPLAY_INFO_PATH   "/org/gnome/Mutter/DisplayConfig"
#define DISPLAY_INFO_METHOD "GetCurrentState"
#endif

/* GNOME doesn't expose displays in any particular order, but we can find the
 * primary display and its logical coordinates via a DBus method.
 */
স্থির bool Wayland_GetGNOMEPrimaryDisplayCoordinates(পূর্ণসংখ্যা *x, পূর্ণসংখ্যা *y)
{
#ifdef SDL_USE_LIBDBUS
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    যদি (dbus == ফাঁকা) {
        ফেরত false;
    }
    DBusMessage *reply = ফাঁকা;
    DBusMessageIter iter[3];
    DBusMessage *বার্তা = dbus->message_new_method_call(DISPLAY_INFO_গ্রন্থি,
                                                     DISPLAY_INFO_PATH,
                                                     DISPLAY_INFO_গ্রন্থি,
                                                     DISPLAY_INFO_METHOD);

    যদি (বার্তা) {
        reply = dbus->connection_send_with_reply_and_block(dbus->session_conn, বার্তা, DBUS_TIMEOUT_USE_DEFAULT, ফাঁকা);
        dbus->message_unref(বার্তা);
    }

    যদি (reply) {
        // Serial (don't care)
        dbus->message_iter_init(reply, &iter[0]);
        যদি (dbus->message_iter_get_arg_type(&iter[0]) != DBUS_TYPE_UINT32) {
            যাও error;
        }

        // Physical monitor array (don't care)
        dbus->message_iter_পরবর্তী(&iter[0]);
        যদি (dbus->message_iter_get_arg_type(&iter[0]) != DBUS_TYPE_ARRAY) {
            যাও error;
        }

        // Logical monitor array of structs
        dbus->message_iter_পরবর্তী(&iter[0]);
        যদি (dbus->message_iter_get_arg_type(&iter[0]) != DBUS_TYPE_ARRAY) {
            যাও error;
        }

        // First logical monitor struct
        dbus->message_iter_recurse(&iter[0], &iter[1]);
        যদি (dbus->message_iter_get_arg_type(&iter[1]) != DBUS_TYPE_STRUCT) {
            যাও error;
        }

        করো {
            পূর্ণসংখ্যা logical_x, logical_y;
            dbus_bool_t primary;

            // Logical X
            dbus->message_iter_recurse(&iter[1], &iter[2]);
            যদি (dbus->message_iter_get_arg_type(&iter[2]) != DBUS_TYPE_INT32) {
                যাও error;
            }
            dbus->message_iter_get_basic(&iter[2], &logical_x);

            // Logical Y
            dbus->message_iter_পরবর্তী(&iter[2]);
            যদি (dbus->message_iter_get_arg_type(&iter[2]) != DBUS_TYPE_INT32) {
                যাও error;
            }
            dbus->message_iter_get_basic(&iter[2], &logical_y);

            // Scale (don't care)
            dbus->message_iter_পরবর্তী(&iter[2]);
            যদি (dbus->message_iter_get_arg_type(&iter[2]) != DBUS_TYPE_DOUBLE) {
                যাও error;
            }

            // Transform (don't care)
            dbus->message_iter_পরবর্তী(&iter[2]);
            যদি (dbus->message_iter_get_arg_type(&iter[2]) != DBUS_TYPE_UINT32) {
                যাও error;
            }

            // Primary display boolean
            dbus->message_iter_পরবর্তী(&iter[2]);
            যদি (dbus->message_iter_get_arg_type(&iter[2]) != DBUS_TYPE_BOOLEAN) {
                যাও error;
            }
            dbus->message_iter_get_basic(&iter[2], &primary);

            যদি (primary) {
                *x = logical_x;
                *y = logical_y;

                // We found the primary display: success.
                dbus->message_unref(reply);
                ফেরত true;
            }
        } যখন (dbus->message_iter_পরবর্তী(&iter[1]));
    }

error:
    যদি (reply) {
        dbus->message_unref(reply);
    }
#endif
    ফেরত false;
}

// Sort the list of displays into a deterministic order
স্থির পূর্ণসংখ্যা SDLCALL Wayland_DisplayPositionCompare(ধ্রুবক শূন্য *a, ধ্রুবক শূন্য *b)
{
    ধ্রুবক SDL_Display_তথ্য *da = *(SDL_Display_তথ্য **)a;
    ধ্রুবক SDL_Display_তথ্য *db = *(SDL_Display_তথ্য **)b;
    ধ্রুবক bool a_at_origin = da->logical.x == 0 && da->logical.y == 0;
    ধ্রুবক bool b_at_origin = db->logical.x == 0 && db->logical.y == 0;

    // Sort the display at 0,0 to be beginning of the list, as that will be the fallback primary.
    যদি (a_at_origin && !b_at_origin) {
        ফেরত -1;
    }
    যদি (b_at_origin && !a_at_origin) {
        ফেরত 1;
    }

    যদি (da->logical.x < db->logical.x) {
        ফেরত -1;
    }
    যদি (da->logical.x > db->logical.x) {
        ফেরত 1;
    }
    যদি (da->logical.y < db->logical.y) {
        ফেরত -1;
    }
    যদি (da->logical.y > db->logical.y) {
        ফেরত 1;
    }

    // If no position information is available, use the connector name.
    যদি (da->wl_output_name && db->wl_output_name) {
        ফেরত SDL_strcmp(da->wl_output_name, db->wl_output_name);
    }

    ফেরত 0;
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
স্থির পূর্ণসংখ্যা Wayland_GetPrimaryDisplay(SDL_Video_তথ্য *vid)
{
    স্থির ধ্রুবক পূর্ণসংখ্যা REFRESH_DELTA = 4000;

    // Query the DBus interface to see if the coordinates of the primary display are exposed.
    পূর্ণসংখ্যা x, y;
    যদি (Wayland_GetGNOMEPrimaryDisplayCoordinates(&x, &y)) {
        জন্য (পূর্ণসংখ্যা i = 0; i < vid->output_গুনতি; ++i) {
            যদি (vid->output_list[i]->logical.x == x && vid->output_list[i]->logical.y == y) {
                ফেরত i;
            }
        }
    }

    // Otherwise, choose the 'best' display.
    পূর্ণসংখ্যা best_width = 0;
    পূর্ণসংখ্যা best_height = 0;
    দ্বিগুণ best_scale = 0.0;
    দশমিক best_headroom = 0.0f;
    পূর্ণসংখ্যা best_refresh = 0;
    bool best_is_landscape = false;
    পূর্ণসংখ্যা best_সূচক = 0;

    জন্য (পূর্ণসংখ্যা i = 0; i < vid->output_গুনতি; ++i) {
        ধ্রুবক SDL_Display_তথ্য *d = vid->output_list[i];
        ধ্রুবক bool is_landscape = d->orientation != SDL_ORIENTATION_PORTRAIT && d->orientation != SDL_ORIENTATION_PORTRAIT_FLIPPED;
        bool have_new_best = false;

        যদি (!best_is_landscape && is_landscape) { // Favor landscape over portrait displays.
            have_new_best = true;
        } অন্যথা যদি (!best_is_landscape || is_landscape) { // Ignore portrait displays if a landscape was already found.
            যদি (d->pixel.width > best_width || d->pixel.height > best_height) {
                have_new_best = true;
            } অন্যথা যদি (d->pixel.width == best_width && d->pixel.height == best_height) {
                যদি (d->HDR.HDR_headroom > best_headroom) { // Favor a higher HDR luminance range
                    have_new_best = true;
                } অন্যথা যদি (d->HDR.HDR_headroom == best_headroom) {
                    যদি (d->refresh - best_refresh > REFRESH_DELTA) { // Favor a higher refresh rate, but ignore small differences (e.g. 59.97 vs 60.1)
                        have_new_best = true;
                    } অন্যথা যদি (d->scale_factor < best_scale && SDL_abs(d->refresh - best_refresh) <= REFRESH_DELTA) {
                        // Prefer a lower scale display if the difference in refresh rate is small.
                        have_new_best = true;
                    }
                }
            }
        }

        যদি (have_new_best) {
            best_width = d->pixel.width;
            best_height = d->pixel.height;
            best_scale = d->scale_factor;
            best_headroom = d->HDR.HDR_headroom;
            best_refresh = d->refresh;
            best_is_landscape = is_landscape;
            best_সূচক = i;
        }
    }

    ফেরত best_সূচক;
}

স্থির শূন্য Wayland_SortOutputsByPriorityHint(SDL_Video_তথ্য *vid)
{
    ধ্রুবক অক্ষর *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_PRIORITY);

    যদি (name_hint) {
        অক্ষর *saveptr;
        অক্ষর *str = SDL_strdup(name_hint);
        SDL_Display_তথ্য **sorted_list = SDL_malloc(আকার(SDL_Display_তথ্য *) * vid->output_গুনতি);

        যদি (str && sorted_list) {
            পূর্ণসংখ্যা sorted_সূচক = 0;

            // Sort the requested displays to the front of the list.
            ধ্রুবক অক্ষর *token = SDL_strtok_r(str, ",", &saveptr);
            যখন (token) {
                জন্য (পূর্ণসংখ্যা i = 0; i < vid->output_গুনতি; ++i) {
                    SDL_Display_তথ্য *d = vid->output_list[i];
                    যদি (d && d->wl_output_name && SDL_strcmp(token, d->wl_output_name) == 0) {
                        sorted_list[sorted_সূচক++] = d;
                        vid->output_list[i] = ফাঁকা;
                        বিরতি;
                    }
                }

                token = SDL_strtok_r(ফাঁকা, ",", &saveptr);
            }

            // Append the remaining outputs to the end of the list.
            জন্য (পূর্ণসংখ্যা i = 0; i < vid->output_গুনতি; ++i) {
                যদি (vid->output_list[i]) {
                    sorted_list[sorted_সূচক++] = vid->output_list[i];
                }
            }

            // Copy the sorted list to the output list.
            SDL_memcpy(vid->output_list, sorted_list, আকার(SDL_Display_তথ্য *) * vid->output_গুনতি);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

স্থির শূন্য Wayland_DeriveOutputPixelCoordinates(SDL_Video_তথ্য *vid)
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
    জন্য ( পূর্ণসংখ্যা i = 0; i < vid->output_গুনতি; ++i) {
        SDL_Display_তথ্য *d = vid->output_list[i];
        d->pixel.x = d->logical.x;
        d->pixel.y = d->logical.y;
    }

    জন্য (পূর্ণসংখ্যা i = 0; i < vid->output_গুনতি; ++i) {
        SDL_Display_তথ্য *d1 = vid->output_list[i];
        যদি (d1->logical.width != d1->pixel.width || d1->logical.height != d1->pixel.height) {
            ধ্রুবক পূর্ণসংখ্যা x_adj = d1->pixel.width - d1->logical.width;
            ধ্রুবক পূর্ণসংখ্যা y_adj = d1->pixel.height - d1->logical.height;

            // Don't adjust for scale values less than 1.0.
            যদি (x_adj > 0 && y_adj > 0) {
                জন্য (পূর্ণসংখ্যা j = 0; j < vid->output_গুনতি; ++j) {
                    SDL_Display_তথ্য *d2 = vid->output_list[j];
                    যদি (d2->logical.x > d1->logical.x) {
                        d2->pixel.x += x_adj;
                    }
                    যদি (d2->logical.y > d1->logical.y) {
                        d2->pixel.y += y_adj;
                    }
                }
            }
        }
    }
}

স্থির শূন্য Wayland_SortOutputs(SDL_Video_তথ্য *vid)
{
    // Sort by position or connector name, so the order of outputs is deterministic.
    SDL_qsort(vid->output_list, vid->output_গুনতি, আকার(SDL_Display_তথ্য *), Wayland_DisplayPositionCompare);

    // Derive the output pixel coordinates if scale to display is enabled.
    যদি (vid->scale_to_display_enabled) {
        Wayland_DeriveOutputPixelCoordinates(vid);
    }

    // Find a suitable primary display and move it to the front of the list.
    ধ্রুবক পূর্ণসংখ্যা primary_সূচক = Wayland_GetPrimaryDisplay(vid);
    যদি (primary_সূচক) {
        SDL_Display_তথ্য *primary = vid->output_list[primary_সূচক];
        SDL_memmove(&vid->output_list[1], &vid->output_list[0], আকার(SDL_Display_তথ্য *) * primary_সূচক);
        vid->output_list[0] = primary;
    }

    // Apply the ordering hint, if specified.
    Wayland_SortOutputsByPriorityHint(vid);
}

স্থির শূন্য Wayland_RefreshWindowPositions()
{
    SDL_VideoDevice *vid = SDL_GetVideoDevice();

    জন্য (SDL_Window *w = vid->windows; w; w = w->পরবর্তী) {
        Wayland_UpdateWindowPosition(w);
    }
}

স্থির শূন্য handle_wl_output_done(শূন্য *তথ্য, কাঠামো wl_output *output);

// Initialization/Query functions
স্থির bool Wayland_VideoInit(SDL_VideoDevice *_this);
স্থির bool Wayland_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
স্থির শূন্য Wayland_VideoQuit(SDL_VideoDevice *_this);

স্থির ধ্রুবক অক্ষর *SDL_WAYLAND_surface_tag = "sdl-window";
স্থির ধ্রুবক অক্ষর *SDL_WAYLAND_output_tag = "sdl-output";

শূন্য SDL_WAYLAND_register_surface(কাঠামো wl_surface *surface)
{
    wl_proxy_set_tag((কাঠামো wl_proxy *)surface, &SDL_WAYLAND_surface_tag);
}

শূন্য SDL_WAYLAND_register_output(কাঠামো wl_output *output)
{
    wl_proxy_set_tag((কাঠামো wl_proxy *)output, &SDL_WAYLAND_output_tag);
}

bool SDL_WAYLAND_own_surface(কাঠামো wl_surface *surface)
{
    ফেরত wl_proxy_get_tag((কাঠামো wl_proxy *)surface) == &SDL_WAYLAND_surface_tag;
}

bool SDL_WAYLAND_own_output(কাঠামো wl_output *output)
{
    ফেরত wl_proxy_get_tag((কাঠামো wl_proxy *)output) == &SDL_WAYLAND_output_tag;
}

/* External surfaces may have their own user data attached, the modification of which
 * can cause problems with external toolkits. Instead, external windows are kept in
 * their own list, and a search is conducted to find a matching surface.
 */
স্থির কাঠামো wl_list external_window_list;

শূন্য Wayland_Add_Window_তথ্য_To_External_List(SDL_Window_তথ্য *তথ্য)
{
    WAYLAND_wl_list_ঢোকাও(&external_window_list, &তথ্য->external_window_list_link);
}

শূন্য Wayland_Remove_Window_তথ্য_From_External_List(SDL_Window_তথ্য *তথ্য)
{
    WAYLAND_wl_list_remove(&তথ্য->external_window_list_link);
}

SDL_Window_তথ্য *Wayland_Get_Window_তথ্য_For_Owned_Surface(কাঠামো wl_surface *surface)
{
    যদি (SDL_WAYLAND_own_surface(surface)) {
        ফেরত (SDL_Window_তথ্য *)wl_surface_get_user_তথ্য(surface);
    } অন্যথা যদি (!WAYLAND_wl_list_empty(&external_window_list)) {
        SDL_Window_তথ্য *p;
        wl_list_for_each (p, &external_window_list, external_window_list_link) {
            যদি (p->surface == surface) {
                ফেরত p;
            }
        }
    }

    ফেরত ফাঁকা;
}

কাঠামো wl_event_queue *Wayland_DisplayCreateQueue(কাঠামো wl_display *display, ধ্রুবক অক্ষর *name)
{
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
    যদি (WAYLAND_wl_display_create_queue_with_name) {
        ফেরত WAYLAND_wl_display_create_queue_with_name(display, name);
    }
#নতুবা_যদি SDL_WAYLAND_CHECK_VERSION(1, 23, 0)
    ফেরত WAYLAND_wl_display_create_queue_with_name(display, name);
#endif
    ফেরত WAYLAND_wl_display_create_queue(display);
}

স্থির শূন্য Wayland_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_Video_তথ্য *তথ্য = device->internal;
    যদি (তথ্য->display && !তথ্য->display_externally_owned) {
        WAYLAND_wl_display_disconnect(তথ্য->display);
        SDL_ClearProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_POINTER);
    }
    SDL_free(তথ্য);
    SDL_free(device);
    SDL_WAYLAND_UnloadSymbols();
}

প্রকারলেখ কাঠামো
{
    bool has_fifo_v1;
    কাঠামো wl_fixes *wl_fixes;
} SDL_Wayland_Preferred_তথ্য;

স্থির শূন্য wayland_preferred_check_handle_global(শূন্য *তথ্য, কাঠামো wl_registry *registry, uint32_t id,
                                                  ধ্রুবক অক্ষর *interface, uint32_t version)
{
    SDL_Wayland_Preferred_তথ্য *d = তথ্য;

    যদি (SDL_strcmp(interface, "wp_fifo_manager_v1") == 0) {
        d->has_fifo_v1 = true;
    }
#ifdef SDL_WL_FIXES_VERSION
    অন্যথা যদি (SDL_strcmp(interface, wl_fixes_interface.name) == 0) {
        d->wl_fixes = wl_registry_bind(registry, id, &wl_fixes_interface, SDL_min(SDL_WL_FIXES_VERSION, version));
    }
#endif
}

স্থির শূন্য wayland_preferred_check_remove_global(শূন্য *তথ্য, কাঠামো wl_registry *registry, uint32_t id)
{
    SDL_Wayland_Preferred_তথ্য *d = (SDL_Wayland_Preferred_তথ্য *)তথ্য;

    যদি (d->wl_fixes && wl_fixes_get_version(d->wl_fixes) >= WL_FIXES_ACK_GLOBAL_REMOVE_SINCE_VERSION) {
        wl_fixes_ack_global_remove(d->wl_fixes, registry, id);
    }
}

স্থির ধ্রুবক কাঠামো wl_registry_listener preferred_registry_listener = {
    wayland_preferred_check_handle_global,
    wayland_preferred_check_remove_global
};

স্থির bool Wayland_IsPreferred(কাঠামো wl_display *display)
{
    কাঠামো wl_registry *registry = wl_display_get_registry(display);
    SDL_Wayland_Preferred_তথ্য preferred_তথ্য = { 0 };

    যদি (!registry) {
        SDL_SetError("Failed to get the Wayland registry");
        ফেরত false;
    }

    wl_registry_add_listener(registry, &preferred_registry_listener, &preferred_তথ্য);

    WAYLAND_wl_display_roundtrip(display);

    যদি (preferred_তথ্য.wl_fixes) {
        wl_fixes_destroy_registry(preferred_তথ্য.wl_fixes, registry);
        wl_fixes_destroy(preferred_তথ্য.wl_fixes);
    }
    wl_registry_destroy(registry);

    যদি (!preferred_তথ্য.has_fifo_v1) {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "This compositor lacks support for the fifo-v1 protocol; falling back to XWayland for GPU performance reasons (set SDL_VIDEO_DRIVER=wayland to override)");
    }
    ফেরত preferred_তথ্য.has_fifo_v1;
}

স্থির SDL_VideoDevice *Wayland_CreateDevice(bool require_preferred_protocols)
{
    SDL_VideoDevice *device;
    SDL_Video_তথ্য *তথ্য;
    কাঠামো wl_display *display = SDL_GetPointerProperty(SDL_GetGlobalProperties(),
                                                 SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_POINTER, ফাঁকা);
    bool display_is_external = !!display;

    // Are we trying to connect to, or are currently in, a Wayland session?
    যদি (!SDL_getenv("WAYLAND_DISPLAY")) {
        ধ্রুবক অক্ষর *session = SDL_getenv("XDG_SESSION_TYPE");
        যদি (session && SDL_strcasecmp(session, "wayland") != 0) {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Wayland initialization failed: no Wayland session available");
            ফেরত ফাঁকা;
        }
    }

    যদি (!SDL_WAYLAND_LoadSymbols()) {
        ফেরত ফাঁকা;
    }

    যদি (!display) {
        display = WAYLAND_wl_display_connect(ফাঁকা);
        যদি (!display) {
            SDL_WAYLAND_UnloadSymbols();
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to connect to the Wayland display server: %s", strerror(errno));
            ফেরত ফাঁকা;
        }
    }

    /*
     * If we are checking for preferred Wayland, then let's query for
     * fifo-v1's existence, so we don't regress GPU-bound performance
     * and frame-pacing by default due to swapchain starvation.
     */
    যদি (require_preferred_protocols && !Wayland_IsPreferred(display)) {
        যদি (!display_is_external) {
            WAYLAND_wl_display_disconnect(display);
        }
        SDL_WAYLAND_UnloadSymbols();
        ফেরত ফাঁকা;
    }

    তথ্য = SDL_calloc(1, আকার(*তথ্য));
    যদি (!তথ্য) {
        যদি (!display_is_external) {
            WAYLAND_wl_display_disconnect(display);
        }
        SDL_WAYLAND_UnloadSymbols();
        ফেরত ফাঁকা;
    }

    তথ্য->initializing = true;
    তথ্য->display = display;
    তথ্য->display_externally_owned = display_is_external;
    তথ্য->scale_to_display_enabled = SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_SCALE_TO_DISPLAY, false);
    WAYLAND_wl_list_init(&তথ্য->seat_list);
    WAYLAND_wl_list_init(&external_window_list);

    // Initialize all variables that we clean on shutdown
    device = SDL_calloc(1, আকার(SDL_VideoDevice));
    যদি (!device) {
        SDL_free(তথ্য);
        যদি (!display_is_external) {
            WAYLAND_wl_display_disconnect(display);
        }
        SDL_WAYLAND_UnloadSymbols();
        ফেরত ফাঁকা;
    }

    যদি (!display_is_external) {
        SDL_SetPointerProperty(SDL_GetGlobalProperties(),
                               SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_POINTER, display);
    }

    device->internal = তথ্য;

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
    device->Set_Window_আকার = Wayland_Set_Window_আকার;
    device->SetWindowAspectRatio = Wayland_SetWindowAspectRatio;
    device->Set_Window_Minimum_আকার = Wayland_Set_Window_Minimum_আকার;
    device->Set_Window_Maximum_আকার = Wayland_Set_Window_Maximum_আকার;
    device->SetWindowParent = Wayland_SetWindowParent;
    device->SetWindowModal = Wayland_SetWindowModal;
    device->SetWindowOpacity = Wayland_SetWindowOpacity;
    device->SetWindowTitle = Wayland_SetWindowTitle;
    device->SetWindowIcon = Wayland_SetWindowIcon;
    device->Get_Window_আকার_In_Pixels = Wayland_Get_Window_আকার_In_Pixels;
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
    যদি (SDL_SystemTheme_Init())
        device->system_theme = SDL_SystemTheme_Get();
#endif

    device->GetTextMimeTypes = Wayland_GetTextMimeTypes;
    device->Set_Clipboard_তথ্য = Wayland_Set_Clipboard_তথ্য;
    device->Get_Clipboard_তথ্য = Wayland_Get_Clipboard_তথ্য;
    device->Has_Clipboard_তথ্য = Wayland_Has_Clipboard_তথ্য;
    device->Start_Text_প্রবেশ = Wayland_Start_Text_প্রবেশ;
    device->Stop_Text_প্রবেশ = Wayland_Stop_Text_প্রবেশ;
    device->Update_Text_প্রবেশ_Area = Wayland_Update_Text_প্রবেশ_Area;

#ifdef SDL_VIDEO_VULKAN
    device->Vulkan_LoadLibrary = Wayland_Vulkan_LoadLibrary;
    device->Vulkan_UnloadLibrary = Wayland_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = Wayland_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = Wayland_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = Wayland_Vulkan_DestroySurface;
    device->Vulkan_GetPresentationSupport = Wayland_Vulkan_GetPresentationSupport;
#endif

    device->মুক্ত = Wayland_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_MODE_SWITCHING_EMULATED |
                          VIDEO_DEVICE_CAPS_HAS_POPUP_WINDOW_SUPPORT |
                          VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS |
                          VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES |
                          VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES;

    ফেরত device;
}

স্থির SDL_VideoDevice *Wayland_Preferred_CreateDevice(শূন্য)
{
    ফেরত Wayland_CreateDevice(true);
}

স্থির SDL_VideoDevice *Wayland_Fallback_CreateDevice(শূন্য)
{
    ফেরত Wayland_CreateDevice(false);
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

স্থির শূন্য handle_xdg_output_logical_position(শূন্য *তথ্য, কাঠামো zxdg_output_v1 *xdg_output, int32_t x, int32_t y)
{
    SDL_Display_তথ্য *internal = (SDL_Display_তথ্য *)তথ্য;

    internal->geometry_changed |= internal->logical.x != x || internal->logical.y != y;
    internal->logical.x = x;
    internal->logical.y = y;
    internal->has_logical_position = true;
}

স্থির শূন্য handle_xdg_output_logical_আকার(শূন্য *তথ্য, কাঠামো zxdg_output_v1 *xdg_output, int32_t width, int32_t height)
{
    SDL_Display_তথ্য *internal = (SDL_Display_তথ্য *)তথ্য;

    internal->geometry_changed |= internal->logical.width != width || internal->logical.height != height;
    internal->logical.width = width;
    internal->logical.height = height;
    internal->has_logical_আকার = true;
}

স্থির শূন্য handle_xdg_output_done(শূন্য *তথ্য, কাঠামো zxdg_output_v1 *xdg_output)
{
    SDL_Display_তথ্য *internal = তথ্য;

    /*
     * xdg-output.done events are deprecated and only apply below version 3 of the protocol.
     * A wl-output.done event will be emitted in version 3 or higher.
     */
    যদি (zxdg_output_v1_get_version(internal->xdg_output) < 3) {
        handle_wl_output_done(তথ্য, internal->output);
    }
}

স্থির শূন্য handle_xdg_output_name(শূন্য *তথ্য, কাঠামো zxdg_output_v1 *xdg_output, ধ্রুবক অক্ষর *name)
{
    SDL_Display_তথ্য *internal = (SDL_Display_তথ্য *)তথ্য;

    // Deprecated as of wl_output v4.
    যদি (wl_output_get_version(internal->output) < WL_OUTPUT_NAME_SINCE_VERSION &&
        internal->display == 0) {
        SDL_free(internal->wl_output_name);
        internal->wl_output_name = SDL_strdup(name);
    }
}

স্থির শূন্য handle_xdg_output_description(শূন্য *তথ্য, কাঠামো zxdg_output_v1 *xdg_output, ধ্রুবক অক্ষর *description)
{
    SDL_Display_তথ্য *internal = (SDL_Display_তথ্য *)তথ্য;

    // Deprecated as of wl_output v4.
    যদি (wl_output_get_version(internal->output) < WL_OUTPUT_DESCRIPTION_SINCE_VERSION &&
        internal->display == 0) {
        // xdg-output descriptions, if available, supersede wl-output model names.
        SDL_free(internal->placeholder.name);
        internal->placeholder.name = SDL_strdup(description);
    }
}

স্থির ধ্রুবক কাঠামো zxdg_output_v1_listener xdg_output_listener = {
    handle_xdg_output_logical_position,
    handle_xdg_output_logical_আকার,
    handle_xdg_output_done,
    handle_xdg_output_name,
    handle_xdg_output_description,
};

স্থির শূন্য AddEmulatedModes(SDL_Display_তথ্য *dispdata, পূর্ণসংখ্যা native_width, পূর্ণসংখ্যা native_height)
{
    কাঠামো EmulatedMode
    {
        পূর্ণসংখ্যা w;
        পূর্ণসংখ্যা h;
    };

    // Resolution lists courtesy of XWayland
    ধ্রুবক কাঠামো EmulatedMode mode_list[] = {
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

    পূর্ণসংখ্যা i;
    SDL_DisplayMode mode;
    SDL_VideoDisplay *dpy = dispdata->display ? SDL_GetVideoDisplay(dispdata->display) : &dispdata->placeholder;
    ধ্রুবক bool rot_90 = native_width < native_height; // Reverse width/height for portrait displays.

    জন্য (i = 0; i < SDL_arraysize(mode_list); ++i) {
        SDL_zero(mode);
        mode.format = dpy->desktop_mode.format;
        mode.refresh_rate_numerator = dpy->desktop_mode.refresh_rate_numerator;
        mode.refresh_rate_denominator = dpy->desktop_mode.refresh_rate_denominator;

        যদি (rot_90) {
            mode.w = mode_list[i].h;
            mode.h = mode_list[i].w;
        } অন্যথা {
            mode.w = mode_list[i].w;
            mode.h = mode_list[i].h;
        }

        // Only add modes that are smaller than the native mode.
        যদি ((mode.w < native_width && mode.h < native_height) ||
            (mode.w < native_width && mode.h == native_height) ||
            (mode.w == native_width && mode.h < native_height)) {
            SDL_AddFullscreenDisplayMode(dpy, &mode);
        }
    }
}

স্থির শূন্য handle_wl_output_geometry(শূন্য *তথ্য, কাঠামো wl_output *output, পূর্ণসংখ্যা x, পূর্ণসংখ্যা y,
                                      পূর্ণসংখ্যা physical_width, পূর্ণসংখ্যা physical_height, পূর্ণসংখ্যা subpixel,
                                      ধ্রুবক অক্ষর *make, ধ্রুবক অক্ষর *model, পূর্ণসংখ্যা transform)
{
    SDL_Display_তথ্য *internal = (SDL_Display_তথ্য *)তথ্য;

    // Apply the change from wl-output only if xdg-output is not supported
    যদি (!internal->has_logical_position) {
        internal->geometry_changed |= internal->logical.x != x || internal->logical.y != y;
        internal->logical.x = x;
        internal->logical.y = y;
    }
    internal->physical.width_mm = physical_width;
    internal->physical.height_mm = physical_height;

    // The model is only used for the output name if wl_output or xdg-output haven't provided a description.
    যদি (internal->display == 0 && !internal->placeholder.name) {
        internal->placeholder.name = SDL_strdup(model);
    }

    internal->transform = transform;
#define TF_CASE(in, out)                                 \
    ক্ষেত্র WL_OUTPUT_TRANSFORM_##in:                       \
        internal->orientation = SDL_ORIENTATION_##out; \
        বিরতি;
    যদি (internal->physical.width_mm >= internal->physical.height_mm) {
        নির্বাচন (transform) {
            TF_CASE(NORMAL, LANDSCAPE)
            TF_CASE(90, PORTRAIT)
            TF_CASE(180, LANDSCAPE_FLIPPED)
            TF_CASE(270, PORTRAIT_FLIPPED)
            TF_CASE(FLIPPED, LANDSCAPE_FLIPPED)
            TF_CASE(FLIPPED_90, PORTRAIT_FLIPPED)
            TF_CASE(FLIPPED_180, LANDSCAPE)
            TF_CASE(FLIPPED_270, PORTRAIT)
        }
    } অন্যথা {
        নির্বাচন (transform) {
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

স্থির শূন্য handle_wl_output_mode(শূন্য *তথ্য, কাঠামো wl_output *output, uint32_t flags,
                                  পূর্ণসংখ্যা width, পূর্ণসংখ্যা height, পূর্ণসংখ্যা refresh)
{
    SDL_Display_তথ্য *internal = (SDL_Display_তথ্য *)তথ্য;

    যদি (flags & WL_OUTPUT_MODE_CURRENT) {
        internal->geometry_changed |= internal->pixel.width != width || internal->pixel.height != height;
        internal->pixel.width = width;
        internal->pixel.height = height;

        /*
         * Don't rotate this yet, wl-output coordinates are transformed in
         * handle_done and xdg-output coordinates are pre-transformed.
         */
        যদি (!internal->has_logical_আকার) {
            internal->geometry_changed |= internal->logical.width != width || internal->logical.height != height;
            internal->logical.width = width;
            internal->logical.height = height;
        }

        internal->refresh = refresh;
    }
}

স্থির শূন্য handle_wl_output_done(শূন্য *তথ্য, কাঠামো wl_output *output)
{
    ধ্রুবক bool mode_emulation_enabled = SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_MODE_EMULATION, true);
    SDL_Display_তথ্য *internal = (SDL_Display_তথ্য *)তথ্য;
    SDL_Video_তথ্য *video = internal->videodata;
    SDL_DisplayMode native_mode, desktop_mode;

    /*
     * When using xdg-output, two wl-output.done events will be emitted:
     * one at the completion of wl-display and one at the completion of xdg-output.
     *
     * All required events must be received before proceeding.
     */
    ধ্রুবক পূর্ণসংখ্যা event_await_গুনতি = 1 + (internal->xdg_output != ফাঁকা);

    internal->wl_output_done_গুনতি = SDL_min(internal->wl_output_done_গুনতি + 1, event_await_গুনতি + 1);

    যদি (internal->wl_output_done_গুনতি < event_await_গুনতি) {
        ফেরত;
    }

    // If the display was already created, reset and rebuild the mode list.
    SDL_VideoDisplay *dpy = SDL_GetVideoDisplay(internal->display);
    যদি (dpy) {
        SDL_ResetFullscreenDisplayModes(dpy);
    }

    // The native display resolution
    SDL_zero(native_mode);
    native_mode.format = SDL_PIXELFORMAT_XRGB8888;

    // Transform the pixel values, if necessary.
    যদি (internal->transform & WL_OUTPUT_TRANSFORM_90) {
        native_mode.w = internal->pixel.height;
        native_mode.h = internal->pixel.width;
    } অন্যথা {
        native_mode.w = internal->pixel.width;
        native_mode.h = internal->pixel.height;
    }
    native_mode.refresh_rate_numerator = internal->refresh;
    native_mode.refresh_rate_denominator = 1000;

    যদি (internal->has_logical_আকার) { // If xdg-output is present...
        যদি (native_mode.w != internal->logical.width || native_mode.h != internal->logical.height) {
            // ...and the compositor scales the logical viewport...
            যদি (video->viewporter) {
                // ...and viewports are supported, calculate the true scale of the output.
                internal->scale_factor = (দ্বিগুণ)native_mode.w / (দ্বিগুণ)internal->logical.width;
            } অন্যথা {
                // ...otherwise, the 'native' pixel values are a multiple of the logical screen size.
                internal->scale_factor = internal->integer_scale_factor;
                internal->pixel.width = internal->logical.width * internal->integer_scale_factor;
                internal->pixel.height = internal->logical.height * internal->integer_scale_factor;
            }
        } অন্যথা {
            /* ...and the output viewport is not scaled in the global compositing
             * space, the output dimensions need to be divided by the scale factor.
             *
             * NOTE: This path is needed for old versions of GNOME that predate fractional scaling.
             */
            internal->scale_factor = internal->integer_scale_factor;
            internal->logical.width /= internal->integer_scale_factor;
            internal->logical.height /= internal->integer_scale_factor;
        }
    } অন্যথা {
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

    যদি (!video->scale_to_display_enabled) {
        desktop_mode.w = internal->logical.width;
        desktop_mode.h = internal->logical.height;
        desktop_mode.pixel_density = (দশমিক)internal->scale_factor;
    } অন্যথা {
        desktop_mode.w = native_mode.w;
        desktop_mode.h = native_mode.h;
        desktop_mode.pixel_density = 1.0f;
    }

    desktop_mode.refresh_rate_numerator = internal->refresh;
    desktop_mode.refresh_rate_denominator = 1000;

    যদি (internal->display > 0) {
        dpy = SDL_GetVideoDisplay(internal->display);
    } অন্যথা {
        dpy = &internal->placeholder;
    }

    যদি (video->scale_to_display_enabled) {
        SDL_SetDisplayContentScale(dpy, (দশমিক)internal->scale_factor);
    }

    // Set the desktop display mode.
    SDL_SetDesktopDisplayMode(dpy, &desktop_mode);

    // Expose the unscaled, native resolution if the scale is 1.0 or viewports are available...
    যদি (internal->scale_factor == 1.0 || video->viewporter) {
        SDL_AddFullscreenDisplayMode(dpy, &native_mode);
        যদি (native_mode.w != desktop_mode.w ||
            native_mode.h != desktop_mode.h) {
            SDL_AddFullscreenDisplayMode(dpy, &desktop_mode);
        }
    } অন্যথা {
        // ...otherwise expose the integer scaled variants of the desktop resolution down to 1.
        desktop_mode.pixel_density = 1.0f;

        জন্য (পূর্ণসংখ্যা i = (পূর্ণসংখ্যা)internal->scale_factor; i > 0; --i) {
            desktop_mode.w = internal->logical.width * i;
            desktop_mode.h = internal->logical.height * i;
            SDL_AddFullscreenDisplayMode(dpy, &desktop_mode);
        }
    }

    // Add emulated modes if wp_viewporter is supported and mode emulation is enabled.
    যদি (video->viewporter && mode_emulation_enabled) {
        // The transformed display pixel width/height must be used here.
        AddEmulatedModes(internal, native_mode.w, native_mode.h);
    }

    যদি (internal->display == 0) {
        // First time getting display info, initialize the VideoDisplay
        যদি (internal->physical.width_mm >= internal->physical.height_mm) {
            internal->placeholder.natural_orientation = SDL_ORIENTATION_LANDSCAPE;
        } অন্যথা {
            internal->placeholder.natural_orientation = SDL_ORIENTATION_PORTRAIT;
        }
        internal->placeholder.current_orientation = internal->orientation;
        internal->placeholder.internal = internal;

        internal->placeholder.props = SDL_CreateProperties();
        SDL_SetPointerProperty(internal->placeholder.props, SDL_PROP_DISPLAY_WAYLAND_WL_OUTPUT_POINTER, internal->output);

        // During initialization, the displays will be added after enumeration is complete.
        যদি (!video->initializing) {
            যদি (video->wp_color_manager_v1) {
                Wayland_GetColorInfoForOutput(internal, false);
            }
            যদি (video->scale_to_display_enabled) {
                Wayland_DeriveOutputPixelCoordinates(video);
            }

            internal->display = SDL_AddVideoDisplay(&internal->placeholder, true);
            Wayland_RefreshWindowPositions();

            SDL_free(internal->placeholder.name);
            SDL_zero(internal->placeholder);
        }
    } অন্যথা {
        SDL_SendDisplayEvent(dpy, SDL_EVENT_DISPLAY_ORIENTATION, internal->orientation, 0);

        যদি (internal->geometry_changed) {
            যদি (video->scale_to_display_enabled) {
                Wayland_DeriveOutputPixelCoordinates(video);
            }

            SDL_SendDisplayEvent(dpy, SDL_EVENT_DISPLAY_MOVED, 0, 0);
            Wayland_RefreshWindowPositions();
        }
    }

    internal->geometry_changed = false;
}

স্থির শূন্য handle_wl_output_scale(শূন্য *তথ্য, কাঠামো wl_output *output, int32_t factor)
{
    SDL_Display_তথ্য *internal = (SDL_Display_তথ্য *)তথ্য;
    internal->integer_scale_factor = factor;
}

স্থির শূন্য handle_wl_output_name(শূন্য *তথ্য, কাঠামো wl_output *wl_output, ধ্রুবক অক্ষর *name)
{
    SDL_Display_তথ্য *internal = (SDL_Display_তথ্য *)তথ্য;

    SDL_free(internal->wl_output_name);
    internal->wl_output_name = SDL_strdup(name);
}

স্থির শূন্য handle_wl_output_description(শূন্য *তথ্য, কাঠামো wl_output *wl_output, ধ্রুবক অক্ষর *description)
{
    SDL_Display_তথ্য *internal = (SDL_Display_তথ্য *)তথ্য;

    যদি (internal->display == 0) {
        // The description, if available, supersedes the model name.
        SDL_free(internal->placeholder.name);
        internal->placeholder.name = SDL_strdup(description);
    }
}

স্থির ধ্রুবক কাঠামো wl_output_listener output_listener = {
    handle_wl_output_geometry,   // Version 1
    handle_wl_output_mode,       // Version 1
    handle_wl_output_done,       // Version 2
    handle_wl_output_scale,      // Version 2
    handle_wl_output_name,       // Version 4
    handle_wl_output_description // Version 4
};

স্থির শূন্য handle_output_image_description_changed(শূন্য *তথ্য,
                                                    কাঠামো wp_color_management_output_v1 *wp_color_management_output_v1)
{
    SDL_Display_তথ্য *display = (SDL_Display_তথ্য *)তথ্য;
    Wayland_GetColorInfoForOutput(display, false);
}

স্থির ধ্রুবক কাঠামো wp_color_management_output_v1_listener wp_color_management_output_listener = {
    handle_output_image_description_changed
};

স্থির bool Wayland_add_display(SDL_Video_তথ্য *d, uint32_t id, uint32_t version)
{
    কাঠামো wl_output *output;
    SDL_Display_তথ্য *তথ্য;

    output = wl_registry_bind(d->registry, id, &wl_output_interface, version);
    যদি (!output) {
        ফেরত SDL_SetError("Failed to retrieve output.");
    }
    তথ্য = (SDL_Display_তথ্য *)SDL_calloc(1, আকার(*তথ্য));
    তথ্য->videodata = d;
    তথ্য->output = output;
    তথ্য->registry_id = id;
    তথ্য->scale_factor = 1.0f;
    তথ্য->integer_scale_factor = 1;

    wl_output_add_listener(output, &output_listener, তথ্য);
    SDL_WAYLAND_register_output(output);

    // Keep a list of outputs for sorting and deferred protocol initialization.
    যদি (d->output_গুনতি == d->output_max) {
        d->output_max += 4;
        d->output_list = SDL_realloc(d->output_list, আকার(SDL_Display_তথ্য *) * d->output_max);
    }
    d->output_list[d->output_গুনতি++] = তথ্য;

    যদি (তথ্য->videodata->xdg_output_manager) {
        তথ্য->xdg_output = zxdg_output_manager_v1_get_xdg_output(তথ্য->videodata->xdg_output_manager, output);
        zxdg_output_v1_add_listener(তথ্য->xdg_output, &xdg_output_listener, তথ্য);
    }
    যদি (তথ্য->videodata->wp_color_manager_v1) {
        তথ্য->wp_color_management_output = wp_color_manager_v1_get_output(তথ্য->videodata->wp_color_manager_v1, output);
        wp_color_management_output_v1_add_listener(তথ্য->wp_color_management_output, &wp_color_management_output_listener, তথ্য);

        // If not initializing, this will be queried synchronously in wl_output.done.
        যদি (d->initializing) {
            Wayland_GetColorInfoForOutput(তথ্য, true);
        }
    }
    ফেরত true;
}

স্থির শূন্য Wayland_free_display(SDL_VideoDisplay *display, bool send_event)
{
    যদি (display) {
        SDL_Display_তথ্য *display_তথ্য = display->internal;

        /* A preceding surface leave event is not guaranteed when an output is removed,
         * so ensure that no window continues to hold a reference to a removed output.
         */
        জন্য (SDL_Window *window = SDL_GetVideoDevice()->windows; window; window = window->পরবর্তী) {
            Wayland_RemoveOutputFromWindow(window->internal, display_তথ্য);
        }

        SDL_free(display_তথ্য->wl_output_name);

        যদি (display_তথ্য->wp_color_management_output) {
            Wayland_FreeColorInfoState(display_তথ্য->color_info_state);
            wp_color_management_output_v1_destroy(display_তথ্য->wp_color_management_output);
        }

        যদি (display_তথ্য->xdg_output) {
            zxdg_output_v1_destroy(display_তথ্য->xdg_output);
        }

        যদি (wl_output_get_version(display_তথ্য->output) >= WL_OUTPUT_RELEASE_SINCE_VERSION) {
            wl_output_release(display_তথ্য->output);
        } অন্যথা {
            wl_output_destroy(display_তথ্য->output);
        }

        SDL_DelVideoDisplay(display->id, send_event);
    }
}

স্থির শূন্য Wayland_FinalizeDisplays(SDL_Video_তথ্য *vid)
{
    Wayland_SortOutputs(vid);

    জন্য(পূর্ণসংখ্যা i = 0; i < vid->output_গুনতি; ++i) {
        SDL_Display_তথ্য *d = vid->output_list[i];
        d->display = SDL_AddVideoDisplay(&d->placeholder, false);
        SDL_free(d->placeholder.name);
        SDL_zero(d->placeholder);
    }
}

স্থির শূন্য Wayland_init_xdg_output(SDL_Video_তথ্য *d)
{
    জন্য (পূর্ণসংখ্যা i = 0; i < d->output_গুনতি; ++i) {
        SDL_Display_তথ্য *disp = d->output_list[i];
        disp->xdg_output = zxdg_output_manager_v1_get_xdg_output(disp->videodata->xdg_output_manager, disp->output);
        zxdg_output_v1_add_listener(disp->xdg_output, &xdg_output_listener, disp);
    }
}

স্থির শূন্য Wayland_InitColorManager(SDL_Video_তথ্য *d)
{
    জন্য (পূর্ণসংখ্যা i = 0; i < d->output_গুনতি; ++i) {
        SDL_Display_তথ্য *disp = d->output_list[i];
        disp->wp_color_management_output = wp_color_manager_v1_get_output(disp->videodata->wp_color_manager_v1, disp->output);
        wp_color_management_output_v1_add_listener(disp->wp_color_management_output, &wp_color_management_output_listener, disp);
        Wayland_GetColorInfoForOutput(disp, true);
    }
}

স্থির শূন্য handle_xdg_session_created(শূন্য *তথ্য, কাঠামো xdg_session_v1 *xdg_session_v1, ধ্রুবক অক্ষর *id)
{
    SDL_SetStringProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, id);
}

স্থির শূন্য handle_xdg_session_restored(শূন্য *তথ্য, কাঠামো xdg_session_v1 *xdg_session_v1)
{
    // NOP
}

স্থির শূন্য handle_xdg_session_replaced(শূন্য *তথ্য, কাঠামো xdg_session_v1 *xdg_session_v1)
{
    SDL_VideoDevice *viddev = SDL_GetVideoDevice();
    SDL_Video_তথ্য *viddata = তথ্য;

    // Clean up all session objects, as they have become inert, and should be destroyed.
    SDL_SetStringProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, ফাঁকা);

    জন্য (SDL_Window *w = viddev->windows; w; w = w->পরবর্তী) {
        SDL_Window_তথ্য *d = w->internal;

        যদি (d->xdg_toplevel_session) {
            xdg_toplevel_session_v1_destroy(d->xdg_toplevel_session);
            d->xdg_toplevel_session = ফাঁকা;

            SDL_free(d->session_id);
            d->session_id = ফাঁকা;
        }
    }

    যদি (viddata->xdg_session) {
        xdg_session_v1_destroy(viddata->xdg_session);
        viddata->xdg_session = ফাঁকা;
    }
}

স্থির ধ্রুবক কাঠামো xdg_session_v1_listener xdg_session_listener = {
    .created  = handle_xdg_session_created,
    .restored = handle_xdg_session_restored,
    .replaced = handle_xdg_session_replaced
};

শূন্য Wayland_CreateSession(SDL_Video_তথ্য *viddata)
{
    যদি (!viddata->xdg_session_manager) {
        // Set the ID string to null if session management is not available.
        SDL_SetStringProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, ফাঁকা);
        ফেরত;
    }

    // Register a new session, if one does not yet exist.
    যদি (!viddata->xdg_session) {
        ধ্রুবক অক্ষর *session_id = SDL_GetStringProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, ফাঁকা);
        যদি (session_id) {
            যদি (*session_id == '\0') {
                // Create a new session if the ID string is empty.
                session_id = ফাঁকা;
            }

            ধ্রুবক গণনা xdg_session_manager_v1_reason reason = session_id ? XDG_SESSION_MANAGER_V1_REASON_SESSION_RESTORE : XDG_SESSION_MANAGER_V1_REASON_LAUNCH;
            viddata->xdg_session = xdg_session_manager_v1_get_session(viddata->xdg_session_manager, reason, session_id);
            xdg_session_v1_add_listener(viddata->xdg_session, &xdg_session_listener, viddata);
        }
    }
}

স্থির শূন্য Wayland_SessionDestroy(SDL_Video_তথ্য *viddata)
{
    // If the session string was cleared, remove the session.
    যদি (viddata->xdg_session) {
        ধ্রুবক অক্ষর *session_id = SDL_GetStringProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, ফাঁকা);
        যদি (!session_id || *session_id == '\0') {
            xdg_session_v1_remove(viddata->xdg_session);

            WAYLAND_wl_display_roundtrip(viddata->display);
        } অন্যথা {
            xdg_session_v1_destroy(viddata->xdg_session);
        }

        viddata->xdg_session = ফাঁকা;
    }
}

স্থির শূন্য handle_xdg_wm_base_ping(শূন্য *তথ্য, কাঠামো xdg_wm_base *xdg, uint32_t serial)
{
    xdg_wm_base_pong(xdg, serial);
}

স্থির ধ্রুবক কাঠামো xdg_wm_base_listener _xdg_wm_base_listener = {
    handle_xdg_wm_base_ping
};

#ifdef HAVE_LIBDECOR_H
স্থির শূন্য libdecor_error(কাঠামো libdecor *context,
                           গণনা libdecor_error error,
                           ধ্রুবক অক্ষর *message)
{
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "libdecor error (%d): %s", error, message);
}

স্থির কাঠামো libdecor_interface libdecor_interface = {
    libdecor_error
};
#endif

স্থির শূন্য handle_registry_global(শূন্য *তথ্য, কাঠামো wl_registry *registry, uint32_t id,
                                   ধ্রুবক অক্ষর *interface, uint32_t version)
{
    SDL_Video_তথ্য *d = তথ্য;

    যদি (SDL_strcmp(interface, wl_compositor_interface.name) == 0) {
        d->compositor = wl_registry_bind(d->registry, id, &wl_compositor_interface, SDL_min(SDL_WL_COMPOSITOR_VERSION, version));
    } অন্যথা যদি (SDL_strcmp(interface, wl_subcompositor_interface.name) == 0) {
        d->subcompositor = wl_registry_bind(d->registry, id, &wl_subcompositor_interface, 1);
    } অন্যথা যদি (SDL_strcmp(interface, wl_output_interface.name) == 0) {
        Wayland_add_display(d, id, SDL_min(version, SDL_WL_OUTPUT_VERSION));
    } অন্যথা যদি (SDL_strcmp(interface, wl_seat_interface.name) == 0) {
        কাঠামো wl_seat *seat = wl_registry_bind(d->registry, id, &wl_seat_interface, SDL_min(SDL_WL_SEAT_VERSION, version));
        Wayland_DisplayCreateSeat(d, seat, id);
    } অন্যথা যদি (SDL_strcmp(interface, xdg_wm_base_interface.name) == 0) {
        d->shell.xdg = wl_registry_bind(d->registry, id, &xdg_wm_base_interface, SDL_min(version, 7));
        xdg_wm_base_add_listener(d->shell.xdg, &_xdg_wm_base_listener, ফাঁকা);
    } অন্যথা যদি (SDL_strcmp(interface, wl_shm_interface.name) == 0) {
        d->shm = wl_registry_bind(registry, id, &wl_shm_interface, SDL_min(SDL_WL_SHM_VERSION, version));
    } অন্যথা যদি (SDL_strcmp(interface, zwp_relative_pointer_manager_v1_interface.name) == 0) {
        d->relative_pointer_manager = wl_registry_bind(d->registry, id, &zwp_relative_pointer_manager_v1_interface, 1);
    } অন্যথা যদি (SDL_strcmp(interface, zwp_pointer_constraints_v1_interface.name) == 0) {
        d->pointer_constraints = wl_registry_bind(d->registry, id, &zwp_pointer_constraints_v1_interface, 1);
    } অন্যথা যদি (SDL_strcmp(interface, zwp_keyboard_shortcuts_inhibit_manager_v1_interface.name) == 0) {
        d->চাবি_inhibitor_manager = wl_registry_bind(d->registry, id, &zwp_keyboard_shortcuts_inhibit_manager_v1_interface, 1);
    } অন্যথা যদি (SDL_strcmp(interface, zwp_idle_inhibit_manager_v1_interface.name) == 0) {
        d->idle_inhibit_manager = wl_registry_bind(d->registry, id, &zwp_idle_inhibit_manager_v1_interface, 1);
    } অন্যথা যদি (SDL_strcmp(interface, xdg_activation_v1_interface.name) == 0) {
        d->activation_manager = wl_registry_bind(d->registry, id, &xdg_activation_v1_interface, 1);
    } অন্যথা যদি (SDL_strcmp(interface, zwp_text_প্রবেশ_manager_v3_interface.name) == 0) {
        d->text_প্রবেশ_manager = wl_registry_bind(d->registry, id, &zwp_text_প্রবেশ_manager_v3_interface, 1);
        Wayland_Display_Init_Text_প্রবেশ_Manager(d, id);
    } অন্যথা যদি (SDL_strcmp(interface, wl_তথ্য_device_manager_interface.name) == 0) {
        d->তথ্য_device_manager = wl_registry_bind(d->registry, id, &wl_তথ্য_device_manager_interface, SDL_min(3, version));
        Wayland_Display_Init_তথ্য_Device_Manager(d);
    } অন্যথা যদি (SDL_strcmp(interface, zwp_primary_selection_device_manager_v1_interface.name) == 0) {
        d->primary_selection_device_manager = wl_registry_bind(d->registry, id, &zwp_primary_selection_device_manager_v1_interface, 1);
        Wayland_DisplayInitPrimarySelectionDeviceManager(d);
    } অন্যথা যদি (SDL_strcmp(interface, zxdg_decoration_manager_v1_interface.name) == 0) {
        d->decoration_manager = wl_registry_bind(d->registry, id, &zxdg_decoration_manager_v1_interface, SDL_min(2, version));
    } অন্যথা যদি (SDL_strcmp(interface, zwp_tablet_manager_v2_interface.name) == 0) {
        d->tablet_manager = wl_registry_bind(d->registry, id, &zwp_tablet_manager_v2_interface, 1);
        Wayland_DisplayInitTabletManager(d);
    } অন্যথা যদি (SDL_strcmp(interface, zxdg_output_manager_v1_interface.name) == 0) {
        version = SDL_min(version, 3); // Versions 1 through 3 are supported.
        d->xdg_output_manager = wl_registry_bind(d->registry, id, &zxdg_output_manager_v1_interface, version);
        Wayland_init_xdg_output(d);
    } অন্যথা যদি (SDL_strcmp(interface, wp_viewporter_interface.name) == 0) {
        d->viewporter = wl_registry_bind(d->registry, id, &wp_viewporter_interface, 1);
    } অন্যথা যদি (SDL_strcmp(interface, wp_fractional_scale_manager_v1_interface.name) == 0) {
        d->fractional_scale_manager = wl_registry_bind(d->registry, id, &wp_fractional_scale_manager_v1_interface, 1);
    } অন্যথা যদি (SDL_strcmp(interface, zwp_প্রবেশ_timestamps_manager_v1_interface.name) == 0) {
        d->প্রবেশ_timestamps_manager = wl_registry_bind(d->registry, id, &zwp_প্রবেশ_timestamps_manager_v1_interface, 1);
        Wayland_Display_Init_প্রবেশ_Timestamp_Manager(d);
    } অন্যথা যদি (SDL_strcmp(interface, wp_cursor_shape_manager_v1_interface.name) == 0) {
        d->cursor_shape_manager = wl_registry_bind(d->registry, id, &wp_cursor_shape_manager_v1_interface, SDL_min(version, 2));
        Wayland_DisplayInitCursorShapeManager(d);
    } অন্যথা যদি (SDL_strcmp(interface, zxdg_exporter_v2_interface.name) == 0) {
        d->zxdg_exporter_v2 = wl_registry_bind(d->registry, id, &zxdg_exporter_v2_interface, 1);
    } অন্যথা যদি (SDL_strcmp(interface, xdg_wm_dialog_v1_interface.name) == 0) {
        d->xdg_wm_dialog_v1 = wl_registry_bind(d->registry, id, &xdg_wm_dialog_v1_interface, 1);
    } অন্যথা যদি (SDL_strcmp(interface, wp_alpha_modifier_v1_interface.name) == 0) {
        d->wp_alpha_modifier_v1 = wl_registry_bind(d->registry, id, &wp_alpha_modifier_v1_interface, 1);
    } অন্যথা যদি (SDL_strcmp(interface, xdg_toplevel_icon_manager_v1_interface.name) == 0) {
        d->xdg_toplevel_icon_manager_v1 = wl_registry_bind(d->registry, id, &xdg_toplevel_icon_manager_v1_interface, 1);
    } অন্যথা যদি (SDL_strcmp(interface, frog_color_management_factory_v1_interface.name) == 0) {
        d->frog_color_management_factory_v1 = wl_registry_bind(d->registry, id, &frog_color_management_factory_v1_interface, 1);
    } অন্যথা যদি (SDL_strcmp(interface, wp_color_manager_v1_interface.name) == 0) {
        d->wp_color_manager_v1 = wl_registry_bind(d->registry, id, &wp_color_manager_v1_interface, SDL_min(version, 2));
        Wayland_InitColorManager(d);
    } অন্যথা যদি (SDL_strcmp(interface, wp_pointer_warp_v1_interface.name) == 0) {
        d->wp_pointer_warp_v1 = wl_registry_bind(d->registry, id, &wp_pointer_warp_v1_interface, 1);
    } অন্যথা যদি (SDL_strcmp(interface, zwp_pointer_gestures_v1_interface.name) == 0) {
        d->zwp_pointer_gestures = wl_registry_bind(d->registry, id, &zwp_pointer_gestures_v1_interface, SDL_min(version, 3));
        Wayland_DisplayInitPointerGestureManager(d);
    } অন্যথা যদি (SDL_strcmp(interface, wp_single_pixel_বাফার_manager_v1_interface.name) == 0) {
        d->single_pixel_বাফার_manager = wl_registry_bind(d->registry, id, &wp_single_pixel_বাফার_manager_v1_interface, 1);
    } অন্যথা যদি (SDL_strcmp(interface, xdg_session_manager_v1_interface.name) == 0) {
        d->xdg_session_manager = wl_registry_bind(d->registry, id, &xdg_session_manager_v1_interface, 1);
    } অন্যথা যদি (SDL_strcmp(interface, xdg_toplevel_tag_manager_v1_interface.name) == 0) {
        d->xdg_toplevel_tag_manager = wl_registry_bind(d->registry, id, &xdg_toplevel_tag_manager_v1_interface, 1);
    }
#ifdef SDL_WL_FIXES_VERSION
    অন্যথা যদি (SDL_strcmp(interface, wl_fixes_interface.name) == 0) {
        d->wl_fixes = wl_registry_bind(d->registry, id, &wl_fixes_interface, SDL_min(SDL_WL_FIXES_VERSION, version));
    }
#endif
}

স্থির শূন্য handle_registry_remove_global(শূন্য *তথ্য, কাঠামো wl_registry *registry, uint32_t id)
{
    SDL_Video_তথ্য *d = তথ্য;

    // We don't get an interface, just an ID, so check outputs and seats.
    জন্য (পূর্ণসংখ্যা i = 0; i < d->output_গুনতি; ++i) {
        SDL_Display_তথ্য *disp = d->output_list[i];
        যদি (disp->registry_id == id) {
            Wayland_free_display(SDL_GetVideoDisplay(disp->display), true);

            যদি (i < d->output_গুনতি) {
                SDL_memmove(&d->output_list[i], &d->output_list[i + 1], আকার(SDL_Display_তথ্য *) * (d->output_গুনতি - i - 1));
            }

            d->output_গুনতি--;
            যাও ack_remove;
        }
    }

    SDL_WaylandSeat *seat, *অস্থায়ী;
    wl_list_for_each_safe (seat, অস্থায়ী, &d->seat_list, link) {
        যদি (seat->registry_id == id) {
            Wayland_SeatDestroy(seat, false);
            যাও ack_remove;
        }
    }

ack_remove:
    যদি (d->wl_fixes && wl_fixes_get_version(d->wl_fixes) >= WL_FIXES_ACK_GLOBAL_REMOVE_SINCE_VERSION) {
        wl_fixes_ack_global_remove(d->wl_fixes, registry, id);
    }
}

স্থির ধ্রুবক কাঠামো wl_registry_listener registry_listener = {
    handle_registry_global,
    handle_registry_remove_global
};

#ifdef HAVE_LIBDECOR_H
স্থির bool should_use_libdecor(SDL_Video_তথ্য *তথ্য, bool ignore_xdg)
{
    যদি (!SDL_WAYLAND_HAVE_WAYLAND_LIBDECOR) {
        ফেরত false;
    }

    যদি (SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_PREFER_LIBDECOR, false)) {
        ফেরত true;
    }

    যদি (ignore_xdg) {
        ফেরত true;
    }

    যদি (তথ্য->decoration_manager) {
        ফেরত false;
    }

    ফেরত true;
}

স্থির শূন্য LibdecorNew(SDL_Video_তথ্য *তথ্য)
{
    তথ্য->shell.libdecor = libdecor_new(তথ্য->display, &libdecor_interface);
}

// Called in another thread, but the UI thread is blocked in SDL_WaitThread
// during that time, so it should be OK to dereference data without locks
স্থির পূর্ণসংখ্যা SDLCALL LibdecorNewInThread(শূন্য *তথ্য)
{
    LibdecorNew((SDL_Video_তথ্য *)তথ্য);
    ফেরত 0;
}
#endif

#ifdef HAVE_GETRESUID
#define SDL_getresuid getresuid
#অন্যথা
// Non-POSIX, but Linux and some BSDs have it.
// To reduce the number of code paths, if getresuid() isn't available at
// compile-time, we behave as though it existed but failed at runtime.
স্থির অন্তঃরেখ পূর্ণসংখ্যা SDL_getresuid(uid_t *ruid, uid_t *euid, uid_t *suid) {
    errno = ENOSYS;
    ফেরত -1;
}
#endif

#ifdef HAVE_GETRESGID
#define SDL_getresgid getresgid
#অন্যথা
// Same as getresuid() but for the primary group
স্থির অন্তঃরেখ পূর্ণসংখ্যা SDL_getresgid(gid_t *rgid, gid_t *egid, gid_t *sgid) {
    errno = ENOSYS;
    ফেরত -1;
}
#endif

bool CanUseGtk(শূন্য)
{
    // "Real", "effective" and "saved" IDs: see e.g. Linux credentials(7)
    uid_t ruid = -1, euid = -1, suid = -1;
    gid_t rgid = -1, egid = -1, sgid = -1;

    যদি (!SDL_GetHintBoolean("SDL_ENABLE_GTK", true)) {
        SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "Not using GTK due to hint");
        ফেরত false;
    }

    // This is intended to match the check in gtkmain.c, rather than being
    // an exhaustive check for having elevated privileges: as a result
    // we don't use Linux getauxval() or prctl PR_GET_DUMPABLE,
    // BSD issetugid(), or similar OS-specific detection

    যদি (SDL_getresuid(&ruid, &euid, &suid) != 0) {
        ruid = suid = getuid();
        euid = geteuid();
    }

    যদি (SDL_getresgid(&rgid, &egid, &sgid) != 0) {
        rgid = sgid = getgid();
        egid = getegid();
    }

    // Real ID != effective ID means we are setuid or setgid:
    // GTK will refuse to initialize, and instead will call exit().
    যদি (ruid != euid || rgid != egid) {
        SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "Not using GTK due to setuid/setgid");
        ফেরত false;
    }

    // Real ID != saved ID means we are setuid or setgid, we previously
    // dropped privileges, but we can regain them; this protects against
    // accidents but does not protect against arbitrary code execution.
    // Again, GTK will refuse to initialize if this is the case.
    যদি (ruid != suid || rgid != sgid) {
        SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "Not using GTK due to saved uid/gid");
        ফেরত false;
    }

    ফেরত true;
}

bool Wayland_LoadLibdecor(SDL_Video_তথ্য *তথ্য, bool ignore_xdg)
{
#ifdef HAVE_LIBDECOR_H
    যদি (তথ্য->shell.libdecor != ফাঁকা) {
        ফেরত true; // Already loaded!
    }
    যদি (should_use_libdecor(তথ্য, ignore_xdg)) {
        যদি (CanUseGtk()) {
            LibdecorNew(তথ্য);
        } অন্যথা {
            // Intentionally initialize libdecor in a non-main thread
            // so that it will not use its GTK plugin, but instead will
            // fall back to the Cairo or dummy plugin
            SDL_Thread *thread = SDL_CreateThread(LibdecorNewInThread, "SDL_LibdecorNew", (শূন্য *)তথ্য);
            // Note that the other thread now "owns" data until we have
            // waited for it, so don't touch data here
            SDL_WaitThread(thread, ফাঁকা);
        }

        ফেরত তথ্য->shell.libdecor != ফাঁকা;
    }
#endif
    ফেরত false;
}

bool Wayland_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_তথ্য *তথ্য = _this->internal;

    তথ্য->event_thread_context = Wayland_CreateEventThread(তথ্য, "SDL Event Thread Queue");
    যদি (!তথ্য->event_thread_context) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Failed to create event thread context");
    }

    তথ্য->job_thread_context = Wayland_CreateJobThread();
    যদি (!তথ্য->job_thread_context) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Failed to create job thread context");
    }

    তথ্য->xkb_context = WAYLAND_xkb_context_new(0);
    যদি (!তথ্য->xkb_context) {
        ফেরত SDL_SetError("Failed to create XKB context");
    }

    তথ্য->registry = wl_display_get_registry(তথ্য->display);
    যদি (!তথ্য->registry) {
        ফেরত SDL_SetError("Failed to get the Wayland registry");
    }

    wl_registry_add_listener(তথ্য->registry, &registry_listener, তথ্য);

    // First roundtrip to receive all registry objects.
    WAYLAND_wl_display_roundtrip(তথ্য->display);

    // Require viewports and xdg-output for display scaling.
    যদি (তথ্য->scale_to_display_enabled) {
        যদি (!তথ্য->viewporter) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Display scaling requires the missing 'wp_viewporter' protocol: disabling");
            তথ্য->scale_to_display_enabled = false;
        }
        যদি (!তথ্য->xdg_output_manager) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Display scaling requires the missing 'zxdg_output_manager_v1' protocol: disabling");
            তথ্য->scale_to_display_enabled = false;
        }
    }

    // Now that we have all the protocols, load libdecor if applicable
    Wayland_LoadLibdecor(তথ্য, false);

    // Second roundtrip to receive all output events.
    WAYLAND_wl_display_roundtrip(তথ্য->display);

    Wayland_FinalizeDisplays(তথ্য);

    Wayland_InitMouse(তথ্য);
    Wayland_InitKeyboard(_this);

    যদি (তথ্য->primary_selection_device_manager) {
        _this->SetPrimarySelectionText = Wayland_SetPrimarySelectionText;
        _this->GetPrimarySelectionText = Wayland_GetPrimarySelectionText;
        _this->HasPrimarySelectionText = Wayland_HasPrimarySelectionText;
    }

    তথ্য->initializing = false;

    ফেরত true;
}

স্থির bool Wayland_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    SDL_Video_তথ্য *viddata = _this->internal;
    SDL_Display_তথ্য *internal = display->internal;

    যদি (!viddata->scale_to_display_enabled) {
        rect->x = internal->logical.x;
        rect->y = internal->logical.y;
    } অন্যথা {
        rect->x = internal->pixel.x;
        rect->y = internal->pixel.y;
    }

    // When an emulated, exclusive fullscreen window has focus, treat the mode dimensions as the display bounds.
    যদি (display->fullscreen_window &&
        display->fullscreen_window->fullscreen_exclusive &&
        display->fullscreen_window->internal->active &&
        display->fullscreen_window->current_fullscreen_mode.w != 0 &&
        display->fullscreen_window->current_fullscreen_mode.h != 0) {
        rect->w = display->fullscreen_window->current_fullscreen_mode.w;
        rect->h = display->fullscreen_window->current_fullscreen_mode.h;
    } অন্যথা {
        যদি (!viddata->scale_to_display_enabled) {
            rect->w = display->current_mode->w;
            rect->h = display->current_mode->h;
        } অন্যথা যদি (internal->transform & WL_OUTPUT_TRANSFORM_90) {
            rect->w = internal->pixel.height;
            rect->h = internal->pixel.width;
        } অন্যথা {
            rect->w = internal->pixel.width;
            rect->h = internal->pixel.height;
        }
    }
    ফেরত true;
}

স্থির শূন্য Wayland_VideoCleanup(SDL_VideoDevice *_this)
{
    SDL_Video_তথ্য *তথ্য = _this->internal;
    SDL_WaylandSeat *seat, *tmp;

    Wayland_SessionDestroy(তথ্য);

    জন্য (পূর্ণসংখ্যা i = _this->অঙ্ক_displays - 1; i >= 0; --i) {
        SDL_VideoDisplay *display = _this->displays[i];
        Wayland_free_display(display, false);
    }
    SDL_free(তথ্য->output_list);

    wl_list_for_each_safe (seat, tmp, &তথ্য->seat_list, link) {
        Wayland_SeatDestroy(seat, true);
    }

    Wayland_FiniMouse(তথ্য);
    Wayland_QuitKeyboard(_this);

    Wayland_DestroyEventThread(তথ্য->event_thread_context);
    তথ্য->event_thread_context = ফাঁকা;

    Wayland_DestroyJobThread(তথ্য->job_thread_context);
    তথ্য->job_thread_context = ফাঁকা;

    যদি (তথ্য->pointer_constraints) {
        zwp_pointer_constraints_v1_destroy(তথ্য->pointer_constraints);
        তথ্য->pointer_constraints = ফাঁকা;
    }

    যদি (তথ্য->relative_pointer_manager) {
        zwp_relative_pointer_manager_v1_destroy(তথ্য->relative_pointer_manager);
        তথ্য->relative_pointer_manager = ফাঁকা;
    }

    যদি (তথ্য->activation_manager) {
        xdg_activation_v1_destroy(তথ্য->activation_manager);
        তথ্য->activation_manager = ফাঁকা;
    }

    যদি (তথ্য->idle_inhibit_manager) {
        zwp_idle_inhibit_manager_v1_destroy(তথ্য->idle_inhibit_manager);
        তথ্য->idle_inhibit_manager = ফাঁকা;
    }

    যদি (তথ্য->চাবি_inhibitor_manager) {
        zwp_keyboard_shortcuts_inhibit_manager_v1_destroy(তথ্য->চাবি_inhibitor_manager);
        তথ্য->চাবি_inhibitor_manager = ফাঁকা;
    }

    যদি (তথ্য->text_প্রবেশ_manager) {
        zwp_text_প্রবেশ_manager_v3_destroy(তথ্য->text_প্রবেশ_manager);
        তথ্য->text_প্রবেশ_manager = ফাঁকা;
    }

    যদি (তথ্য->xkb_context) {
        WAYLAND_xkb_context_unref(তথ্য->xkb_context);
        তথ্য->xkb_context = ফাঁকা;
    }

    যদি (তথ্য->tablet_manager) {
        zwp_tablet_manager_v2_destroy((কাঠামো zwp_tablet_manager_v2 *)তথ্য->tablet_manager);
        তথ্য->tablet_manager = ফাঁকা;
    }

    যদি (তথ্য->তথ্য_device_manager) {
        wl_তথ্য_device_manager_destroy(তথ্য->তথ্য_device_manager);
        তথ্য->তথ্য_device_manager = ফাঁকা;
    }

    যদি (তথ্য->shm) {
        যদি (wl_shm_get_version(তথ্য->shm) >= WL_SHM_RELEASE_SINCE_VERSION) {
            wl_shm_release(তথ্য->shm);
        } অন্যথা {
            wl_shm_destroy(তথ্য->shm);
        }
        তথ্য->shm = ফাঁকা;
    }

    যদি (তথ্য->shell.xdg) {
        xdg_wm_base_destroy(তথ্য->shell.xdg);
        তথ্য->shell.xdg = ফাঁকা;
    }

    যদি (তথ্য->decoration_manager) {
        zxdg_decoration_manager_v1_destroy(তথ্য->decoration_manager);
        তথ্য->decoration_manager = ফাঁকা;
    }

    যদি (তথ্য->xdg_output_manager) {
        zxdg_output_manager_v1_destroy(তথ্য->xdg_output_manager);
        তথ্য->xdg_output_manager = ফাঁকা;
    }

    যদি (তথ্য->viewporter) {
        wp_viewporter_destroy(তথ্য->viewporter);
        তথ্য->viewporter = ফাঁকা;
    }

    যদি (তথ্য->primary_selection_device_manager) {
        zwp_primary_selection_device_manager_v1_destroy(তথ্য->primary_selection_device_manager);
        তথ্য->primary_selection_device_manager = ফাঁকা;
    }

    যদি (তথ্য->fractional_scale_manager) {
        wp_fractional_scale_manager_v1_destroy(তথ্য->fractional_scale_manager);
        তথ্য->fractional_scale_manager = ফাঁকা;
    }

    যদি (তথ্য->প্রবেশ_timestamps_manager) {
        zwp_প্রবেশ_timestamps_manager_v1_destroy(তথ্য->প্রবেশ_timestamps_manager);
        তথ্য->প্রবেশ_timestamps_manager = ফাঁকা;
    }

    যদি (তথ্য->cursor_shape_manager) {
        wp_cursor_shape_manager_v1_destroy(তথ্য->cursor_shape_manager);
        তথ্য->cursor_shape_manager = ফাঁকা;
    }

    যদি (তথ্য->zxdg_exporter_v2) {
        zxdg_exporter_v2_destroy(তথ্য->zxdg_exporter_v2);
        তথ্য->zxdg_exporter_v2 = ফাঁকা;
    }

    যদি (তথ্য->xdg_wm_dialog_v1) {
        xdg_wm_dialog_v1_destroy(তথ্য->xdg_wm_dialog_v1);
        তথ্য->xdg_wm_dialog_v1 = ফাঁকা;
    }

    যদি (তথ্য->wp_alpha_modifier_v1) {
        wp_alpha_modifier_v1_destroy(তথ্য->wp_alpha_modifier_v1);
        তথ্য->wp_alpha_modifier_v1 = ফাঁকা;
    }

    যদি (তথ্য->xdg_toplevel_icon_manager_v1) {
        xdg_toplevel_icon_manager_v1_destroy(তথ্য->xdg_toplevel_icon_manager_v1);
        তথ্য->xdg_toplevel_icon_manager_v1 = ফাঁকা;
    }

    যদি (তথ্য->frog_color_management_factory_v1) {
        frog_color_management_factory_v1_destroy(তথ্য->frog_color_management_factory_v1);
        তথ্য->frog_color_management_factory_v1 = ফাঁকা;
    }

    যদি (তথ্য->wp_color_manager_v1) {
        wp_color_manager_v1_destroy(তথ্য->wp_color_manager_v1);
        তথ্য->wp_color_manager_v1 = ফাঁকা;
    }

    যদি (তথ্য->wp_pointer_warp_v1) {
        wp_pointer_warp_v1_destroy(তথ্য->wp_pointer_warp_v1);
        তথ্য->wp_pointer_warp_v1 = ফাঁকা;
    }

    যদি (তথ্য->zwp_pointer_gestures) {
        যদি (zwp_pointer_gestures_v1_get_version(তথ্য->zwp_pointer_gestures) >= ZWP_POINTER_GESTURES_V1_RELEASE_SINCE_VERSION) {
            zwp_pointer_gestures_v1_release(তথ্য->zwp_pointer_gestures);
        } অন্যথা {
            zwp_pointer_gestures_v1_destroy(তথ্য->zwp_pointer_gestures);
        }
        তথ্য->zwp_pointer_gestures = ফাঁকা;
    }

    যদি (তথ্য->single_pixel_বাফার_manager) {
        wp_single_pixel_বাফার_manager_v1_destroy(তথ্য->single_pixel_বাফার_manager);
        তথ্য->single_pixel_বাফার_manager = ফাঁকা;
    }

    যদি (তথ্য->xdg_session_manager) {
        xdg_session_manager_v1_destroy(তথ্য->xdg_session_manager);
        তথ্য->xdg_session_manager = ফাঁকা;
    }

    যদি (তথ্য->xdg_toplevel_tag_manager) {
        xdg_toplevel_tag_manager_v1_destroy(তথ্য->xdg_toplevel_tag_manager);
        তথ্য->xdg_toplevel_tag_manager = ফাঁকা;
    }

    যদি (তথ্য->subcompositor) {
        wl_subcompositor_destroy(তথ্য->subcompositor);
        তথ্য->subcompositor = ফাঁকা;
    }

    যদি (তথ্য->compositor) {
        wl_compositor_destroy(তথ্য->compositor);
        তথ্য->compositor = ফাঁকা;
    }

    যদি (তথ্য->registry) {
        যদি (তথ্য->wl_fixes) {
            wl_fixes_destroy_registry(তথ্য->wl_fixes, তথ্য->registry);
            wl_fixes_destroy(তথ্য->wl_fixes);
            তথ্য->wl_fixes = ফাঁকা;
        }
        wl_registry_destroy(তথ্য->registry);
        তথ্য->registry = ফাঁকা;
    }
}

স্থির bool Wayland_VideoReconnect(SDL_VideoDevice *_this)
{
#যদি 0 // TODO RECONNECT: Uncomment all when https://invent.kde.org/plasma/kwin/-/wikis/Restarting is completed
    SDL_Video_তথ্য *তথ্য = _this->internal;

    SDL_Window *window = ফাঁকা;

    SDL_GLContext current_ctx = SDL_GL_GetCurrentContext();
    SDL_Window *current_window = SDL_GL_GetCurrentWindow();

    SDL_GL_MakeCurrent(ফাঁকা, ফাঁকা);
    Wayland_VideoCleanup(_this);

    SDL_ResetKeyboard();
    SDL_ResetMouse();
    যদি (WAYLAND_wl_display_reconnect(তথ্য->display) < 0) {
        ফেরত false;
    }

    Wayland_VideoInit(_this);

    window = _this->windows;
    যখন (window) {
        /* We're going to cheat _just_ for a second and strip the OpenGL flag.
         * The Wayland driver actually forces it in CreateWindow, and
         * RecreateWindow does a bunch of unloading/loading of libGL, so just
         * strip the flag so RecreateWindow doesn't mess with the GL context,
         * and CreateWindow will add it right back!
         * -flibit
         */
        window->flags &= ~SDL_WINDOW_OPENGL;

        SDL_RecreateWindow(window, window->flags);
        window = window->পরবর্তী;
    }

    Wayland_RecreateCursors();

    যদি (current_window && current_ctx) {
        SDL_GL_MakeCurrent (current_window, current_ctx);
    }
    ফেরত true;
#অন্যথা
    ফেরত false;
#endif // 0
}

bool Wayland_HandleDisplayDisconnected(SDL_VideoDevice *_this)
{
    SDL_Video_তথ্য *video_তথ্য = _this->internal;

    /* Something has failed with the Wayland connection -- for example,
     * the compositor may have shut down and closed its end of the socket,
     * or there is a library-specific error.
     *
     * Try to recover once, then quit.
     */
    যদি (video_তথ্য->display_disconnected) {
        ফেরত false;
    }

    যদি (Wayland_VideoReconnect(_this)) {
        ফেরত true;
    }

    video_তথ্য->display_disconnected = true;
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Wayland display connection closed by server (fatal)");

    // Only send a single quit message, as application shutdown might call SDL_PumpEvents().
    SDL_SendQuit();

    ফেরত false;
}

শূন্য Wayland_VideoQuit(SDL_VideoDevice *_this)
{
    Wayland_VideoCleanup(_this);

#ifdef HAVE_LIBDECOR_H
    SDL_Video_তথ্য *তথ্য = _this->internal;
    যদি (তথ্য->shell.libdecor) {
        libdecor_unref(তথ্য->shell.libdecor);
        তথ্য->shell.libdecor = ফাঁকা;
    }
#endif
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
