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

#ضمن "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#ضمن "../../core/linux/SDL_system_theme.h"
#ضمن "../../core/linux/SDL_progressbar.h"
#ضمن "../../events/SDL_events_c.h"

#ضمن "SDL_waylandclipboard.h"
#ضمن "SDL_waylandcolor.h"
#ضمن "SDL_waylandevents_c.h"
#ضمن "SDL_waylandkeyboard.h"
#ضمن "SDL_waylandmessagebox.h"
#ضمن "SDL_waylandmouse.h"
#ضمن "SDL_waylandopengles.h"
#ضمن "SDL_waylandvideo.h"
#ضمن "SDL_waylandvulkan.h"
#ضمن "SDL_waylandwindow.h"

#ضمن <fcntl.h>
#ضمن <sys/types.h>
#ضمن <unistd.h>
#ضمن <errno.h>
#ضمن <xkbcommon/xkbcommon.h>

#ضمن <wayland-util.h>

#ضمن "alpha-modifier-v1-client-protocol.h"
#ضمن "cursor-shape-v1-client-protocol.h"
#ضمن "fractional-scale-v1-client-protocol.h"
#ضمن "frog-color-management-v1-client-protocol.h"
#ضمن "idle-inhibit-unstable-v1-client-protocol.h"
#ضمن "input-timestamps-unstable-v1-client-protocol.h"
#ضمن "keyboard-shortcuts-inhibit-unstable-v1-client-protocol.h"
#ضمن "pointer-constraints-unstable-v1-client-protocol.h"
#ضمن "primary-selection-unstable-v1-client-protocol.h"
#ضمن "relative-pointer-unstable-v1-client-protocol.h"
#ضمن "tablet-v2-client-protocol.h"
#ضمن "text-input-unstable-v3-client-protocol.h"
#ضمن "viewporter-client-protocol.h"
#ضمن "xdg-activation-v1-client-protocol.h"
#ضمن "xdg-decoration-unstable-v1-client-protocol.h"
#ضمن "xdg-dialog-v1-client-protocol.h"
#ضمن "xdg-foreign-unstable-v2-client-protocol.h"
#ضمن "xdg-output-unstable-v1-client-protocol.h"
#ضمن "xdg-shell-client-protocol.h"
#ضمن "xdg-toplevel-icon-v1-client-protocol.h"
#ضمن "color-management-v1-client-protocol.h"
#ضمن "pointer-warp-v1-client-protocol.h"
#ضمن "pointer-gestures-unstable-v1-client-protocol.h"
#ضمن "single-pixel-buffer-v1-client-protocol.h"
#ضمن "xdg-session-management-v1-client-protocol.h"
#ضمن "xdg-toplevel-tag-v1-client-protocol.h"

#ifdef HAVE_LIBDECOR_H
#ضمن <libdecor.h>
#endif

#define WAYLANDVID_DRIVER_NAME "wayland"

// Clamp core protocol versions on older versions of libwayland.
#إذا SDL_WAYLAND_CHECK_VERSION(1, 22, 0)
#define SDL_WL_COMPOSITOR_VERSION 6
#وإلا
#define SDL_WL_COMPOSITOR_VERSION 4
#endif

#إذا SDL_WAYLAND_CHECK_VERSION(1, 26, 0)
#define SDL_WL_SEAT_VERSION 11
#وإلاإذا SDL_WAYLAND_CHECK_VERSION(1, 24, 0)
#define SDL_WL_SEAT_VERSION 10
#وإلاإذا SDL_WAYLAND_CHECK_VERSION(1, 22, 0)
#define SDL_WL_SEAT_VERSION 9
#وإلاإذا SDL_WAYLAND_CHECK_VERSION(1, 21, 0)
#define SDL_WL_SEAT_VERSION 8
#وإلا
#define SDL_WL_SEAT_VERSION 5
#endif

#إذا SDL_WAYLAND_CHECK_VERSION(1, 20, 0)
#define SDL_WL_OUTPUT_VERSION 4
#وإلا
#define SDL_WL_OUTPUT_VERSION 3
#endif

#إذا SDL_WAYLAND_CHECK_VERSION(1, 24, 0)
#define SDL_WL_SHM_VERSION 2
#وإلا
#define SDL_WL_SHM_VERSION 1
#endif

// The SDL libwayland-client minimum is 1.18, which supports version 3.
#define SDL_WL_DATA_DEVICE_VERSION 3

// wl_fixes was introduced in 1.24.0
#إذا SDL_WAYLAND_CHECK_VERSION(1, 26, 0)
#define SDL_WL_FIXES_VERSION 2
#وإلاإذا SDL_WAYLAND_CHECK_VERSION(1, 24, 0)
#define SDL_WL_FIXES_VERSION 1
#endif

#ifdef SDL_USE_LIBDBUS
#ضمن "../../core/linux/SDL_dbus.h"

#define DISPLAY_INFO_عقدة   "org.gnome.Mutter.DisplayConfig"
#define DISPLAY_INFO_PATH   "/org/gnome/Mutter/DisplayConfig"
#define DISPLAY_INFO_METHOD "GetCurrentState"
#endif

/* GNOME doesn't expose displays in any particular order, but we can find the
 * primary display and its logical coordinates via a DBus method.
 */
ساكن bool Wayland_GetGNOMEPrimaryDisplayCoordinates(صحيح *x, صحيح *y)
{
#ifdef SDL_USE_LIBDBUS
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    إذا (dbus == عدم) {
        إرجاع false;
    }
    DBusMessage *reply = عدم;
    DBusMessageIter iter[3];
    DBusMessage *رسالة = dbus->message_new_method_call(DISPLAY_INFO_عقدة,
                                                     DISPLAY_INFO_PATH,
                                                     DISPLAY_INFO_عقدة,
                                                     DISPLAY_INFO_METHOD);

    إذا (رسالة) {
        reply = dbus->connection_send_with_reply_and_block(dbus->session_conn, رسالة, DBUS_TIMEOUT_USE_DEFAULT, عدم);
        dbus->message_unref(رسالة);
    }

    إذا (reply) {
        // Serial (don't care)
        dbus->message_iter_init(reply, &iter[0]);
        إذا (dbus->message_iter_get_arg_type(&iter[0]) != DBUS_TYPE_UINT32) {
            اذهب error;
        }

        // Physical monitor array (don't care)
        dbus->message_iter_next(&iter[0]);
        إذا (dbus->message_iter_get_arg_type(&iter[0]) != DBUS_TYPE_ARRAY) {
            اذهب error;
        }

        // Logical monitor array of structs
        dbus->message_iter_next(&iter[0]);
        إذا (dbus->message_iter_get_arg_type(&iter[0]) != DBUS_TYPE_ARRAY) {
            اذهب error;
        }

        // First logical monitor struct
        dbus->message_iter_recurse(&iter[0], &iter[1]);
        إذا (dbus->message_iter_get_arg_type(&iter[1]) != DBUS_TYPE_STRUCT) {
            اذهب error;
        }

        افعل {
            صحيح logical_x, logical_y;
            dbus_bool_t primary;

            // Logical X
            dbus->message_iter_recurse(&iter[1], &iter[2]);
            إذا (dbus->message_iter_get_arg_type(&iter[2]) != DBUS_TYPE_INT32) {
                اذهب error;
            }
            dbus->message_iter_get_basic(&iter[2], &logical_x);

            // Logical Y
            dbus->message_iter_next(&iter[2]);
            إذا (dbus->message_iter_get_arg_type(&iter[2]) != DBUS_TYPE_INT32) {
                اذهب error;
            }
            dbus->message_iter_get_basic(&iter[2], &logical_y);

            // Scale (don't care)
            dbus->message_iter_next(&iter[2]);
            إذا (dbus->message_iter_get_arg_type(&iter[2]) != DBUS_TYPE_DOUBLE) {
                اذهب error;
            }

            // Transform (don't care)
            dbus->message_iter_next(&iter[2]);
            إذا (dbus->message_iter_get_arg_type(&iter[2]) != DBUS_TYPE_UINT32) {
                اذهب error;
            }

            // Primary display boolean
            dbus->message_iter_next(&iter[2]);
            إذا (dbus->message_iter_get_arg_type(&iter[2]) != DBUS_TYPE_BOOLEAN) {
                اذهب error;
            }
            dbus->message_iter_get_basic(&iter[2], &primary);

            إذا (primary) {
                *x = logical_x;
                *y = logical_y;

                // We found the primary display: success.
                dbus->message_unref(reply);
                إرجاع true;
            }
        } بينما (dbus->message_iter_next(&iter[1]));
    }

error:
    إذا (reply) {
        dbus->message_unref(reply);
    }
#endif
    إرجاع false;
}

// Sort the list of displays into a deterministic order
ساكن صحيح SDLCALL Wayland_DisplayPositionCompare(ثابت فراغ *a, ثابت فراغ *b)
{
    ثابت SDL_DisplayData *da = *(SDL_DisplayData **)a;
    ثابت SDL_DisplayData *db = *(SDL_DisplayData **)b;
    ثابت bool a_at_origin = da->logical.x == 0 && da->logical.y == 0;
    ثابت bool b_at_origin = db->logical.x == 0 && db->logical.y == 0;

    // Sort the display at 0,0 to be beginning of the list, as that will be the fallback primary.
    إذا (a_at_origin && !b_at_origin) {
        إرجاع -1;
    }
    إذا (b_at_origin && !a_at_origin) {
        إرجاع 1;
    }

    إذا (da->logical.x < db->logical.x) {
        إرجاع -1;
    }
    إذا (da->logical.x > db->logical.x) {
        إرجاع 1;
    }
    إذا (da->logical.y < db->logical.y) {
        إرجاع -1;
    }
    إذا (da->logical.y > db->logical.y) {
        إرجاع 1;
    }

    // If no position information is available, use the connector name.
    إذا (da->wl_output_name && db->wl_output_name) {
        إرجاع SDL_strcmp(da->wl_output_name, db->wl_output_name);
    }

    إرجاع 0;
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
ساكن صحيح Wayland_GetPrimaryDisplay(SDL_VideoData *vid)
{
    ساكن ثابت صحيح REFRESH_DELTA = 4000;

    // Query the DBus interface to see if the coordinates of the primary display are exposed.
    صحيح x, y;
    إذا (Wayland_GetGNOMEPrimaryDisplayCoordinates(&x, &y)) {
        لكل (صحيح i = 0; i < vid->output_تعداد; ++i) {
            إذا (vid->output_list[i]->logical.x == x && vid->output_list[i]->logical.y == y) {
                إرجاع i;
            }
        }
    }

    // Otherwise, choose the 'best' display.
    صحيح best_width = 0;
    صحيح best_height = 0;
    مزدوج best_scale = 0.0;
    عائم best_headroom = 0.0f;
    صحيح best_refresh = 0;
    bool best_is_landscape = false;
    صحيح best_index = 0;

    لكل (صحيح i = 0; i < vid->output_تعداد; ++i) {
        ثابت SDL_DisplayData *d = vid->output_list[i];
        ثابت bool is_landscape = d->orientation != SDL_ORIENTATION_PORTRAIT && d->orientation != SDL_ORIENTATION_PORTRAIT_FLIPPED;
        bool have_new_best = false;

        إذا (!best_is_landscape && is_landscape) { // Favor landscape over portrait displays.
            have_new_best = true;
        } وإلا إذا (!best_is_landscape || is_landscape) { // Ignore portrait displays if a landscape was already found.
            إذا (d->pixel.width > best_width || d->pixel.height > best_height) {
                have_new_best = true;
            } وإلا إذا (d->pixel.width == best_width && d->pixel.height == best_height) {
                إذا (d->HDR.HDR_headroom > best_headroom) { // Favor a higher HDR luminance range
                    have_new_best = true;
                } وإلا إذا (d->HDR.HDR_headroom == best_headroom) {
                    إذا (d->refresh - best_refresh > REFRESH_DELTA) { // Favor a higher refresh rate, but ignore small differences (e.g. 59.97 vs 60.1)
                        have_new_best = true;
                    } وإلا إذا (d->scale_factor < best_scale && SDL_abs(d->refresh - best_refresh) <= REFRESH_DELTA) {
                        // Prefer a lower scale display if the difference in refresh rate is small.
                        have_new_best = true;
                    }
                }
            }
        }

        إذا (have_new_best) {
            best_width = d->pixel.width;
            best_height = d->pixel.height;
            best_scale = d->scale_factor;
            best_headroom = d->HDR.HDR_headroom;
            best_refresh = d->refresh;
            best_is_landscape = is_landscape;
            best_index = i;
        }
    }

    إرجاع best_index;
}

ساكن فراغ Wayland_SortOutputsByPriorityHint(SDL_VideoData *vid)
{
    ثابت حرف *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_PRIORITY);

    إذا (name_hint) {
        حرف *saveptr;
        حرف *str = SDL_strdup(name_hint);
        SDL_DisplayData **sorted_list = SDL_malloc(حجم(SDL_DisplayData *) * vid->output_تعداد);

        إذا (str && sorted_list) {
            صحيح sorted_index = 0;

            // Sort the requested displays to the front of the list.
            ثابت حرف *token = SDL_strtok_r(str, ",", &saveptr);
            بينما (token) {
                لكل (صحيح i = 0; i < vid->output_تعداد; ++i) {
                    SDL_DisplayData *d = vid->output_list[i];
                    إذا (d && d->wl_output_name && SDL_strcmp(token, d->wl_output_name) == 0) {
                        sorted_list[sorted_index++] = d;
                        vid->output_list[i] = عدم;
                        اكسر;
                    }
                }

                token = SDL_strtok_r(عدم, ",", &saveptr);
            }

            // Append the remaining outputs to the end of the list.
            لكل (صحيح i = 0; i < vid->output_تعداد; ++i) {
                إذا (vid->output_list[i]) {
                    sorted_list[sorted_index++] = vid->output_list[i];
                }
            }

            // Copy the sorted list to the output list.
            SDL_memcpy(vid->output_list, sorted_list, حجم(SDL_DisplayData *) * vid->output_تعداد);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

ساكن فراغ Wayland_DeriveOutputPixelCoordinates(SDL_VideoData *vid)
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
    لكل ( صحيح i = 0; i < vid->output_تعداد; ++i) {
        SDL_DisplayData *d = vid->output_list[i];
        d->pixel.x = d->logical.x;
        d->pixel.y = d->logical.y;
    }

    لكل (صحيح i = 0; i < vid->output_تعداد; ++i) {
        SDL_DisplayData *d1 = vid->output_list[i];
        إذا (d1->logical.width != d1->pixel.width || d1->logical.height != d1->pixel.height) {
            ثابت صحيح x_adj = d1->pixel.width - d1->logical.width;
            ثابت صحيح y_adj = d1->pixel.height - d1->logical.height;

            // Don't adjust for scale values less than 1.0.
            إذا (x_adj > 0 && y_adj > 0) {
                لكل (صحيح j = 0; j < vid->output_تعداد; ++j) {
                    SDL_DisplayData *d2 = vid->output_list[j];
                    إذا (d2->logical.x > d1->logical.x) {
                        d2->pixel.x += x_adj;
                    }
                    إذا (d2->logical.y > d1->logical.y) {
                        d2->pixel.y += y_adj;
                    }
                }
            }
        }
    }
}

ساكن فراغ Wayland_SortOutputs(SDL_VideoData *vid)
{
    // Sort by position or connector name, so the order of outputs is deterministic.
    SDL_qsort(vid->output_list, vid->output_تعداد, حجم(SDL_DisplayData *), Wayland_DisplayPositionCompare);

    // Derive the output pixel coordinates if scale to display is enabled.
    إذا (vid->scale_to_display_enabled) {
        Wayland_DeriveOutputPixelCoordinates(vid);
    }

    // Find a suitable primary display and move it to the front of the list.
    ثابت صحيح primary_index = Wayland_GetPrimaryDisplay(vid);
    إذا (primary_index) {
        SDL_DisplayData *primary = vid->output_list[primary_index];
        SDL_memmove(&vid->output_list[1], &vid->output_list[0], حجم(SDL_DisplayData *) * primary_index);
        vid->output_list[0] = primary;
    }

    // Apply the ordering hint, if specified.
    Wayland_SortOutputsByPriorityHint(vid);
}

ساكن فراغ Wayland_RefreshWindowPositions()
{
    SDL_VideoDevice *vid = SDL_GetVideoDevice();

    لكل (SDL_Window *w = vid->windows; w; w = w->next) {
        Wayland_UpdateWindowPosition(w);
    }
}

ساكن فراغ handle_wl_output_done(فراغ *data, بنية wl_output *output);

// Initialization/Query functions
ساكن bool Wayland_VideoInit(SDL_VideoDevice *_this);
ساكن bool Wayland_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
ساكن فراغ Wayland_VideoQuit(SDL_VideoDevice *_this);

ساكن ثابت حرف *SDL_WAYLAND_surface_tag = "sdl-window";
ساكن ثابت حرف *SDL_WAYLAND_output_tag = "sdl-output";

فراغ SDL_WAYLAND_register_surface(بنية wl_surface *surface)
{
    wl_proxy_set_tag((بنية wl_proxy *)surface, &SDL_WAYLAND_surface_tag);
}

فراغ SDL_WAYLAND_register_output(بنية wl_output *output)
{
    wl_proxy_set_tag((بنية wl_proxy *)output, &SDL_WAYLAND_output_tag);
}

bool SDL_WAYLAND_own_surface(بنية wl_surface *surface)
{
    إرجاع wl_proxy_get_tag((بنية wl_proxy *)surface) == &SDL_WAYLAND_surface_tag;
}

bool SDL_WAYLAND_own_output(بنية wl_output *output)
{
    إرجاع wl_proxy_get_tag((بنية wl_proxy *)output) == &SDL_WAYLAND_output_tag;
}

/* External surfaces may have their own user data attached, the modification of which
 * can cause problems with external toolkits. Instead, external windows are kept in
 * their own list, and a search is conducted to find a matching surface.
 */
ساكن بنية wl_list external_window_list;

فراغ Wayland_AddWindowDataToExternalList(SDL_WindowData *data)
{
    WAYLAND_wl_list_أدرج(&external_window_list, &data->external_window_list_link);
}

فراغ Wayland_RemoveWindowDataFromExternalList(SDL_WindowData *data)
{
    WAYLAND_wl_list_remove(&data->external_window_list_link);
}

SDL_WindowData *Wayland_GetWindowDataForOwnedSurface(بنية wl_surface *surface)
{
    إذا (SDL_WAYLAND_own_surface(surface)) {
        إرجاع (SDL_WindowData *)wl_surface_get_user_data(surface);
    } وإلا إذا (!WAYLAND_wl_list_empty(&external_window_list)) {
        SDL_WindowData *p;
        wl_list_for_each (p, &external_window_list, external_window_list_link) {
            إذا (p->surface == surface) {
                إرجاع p;
            }
        }
    }

    إرجاع عدم;
}

بنية wl_event_queue *Wayland_DisplayCreateQueue(بنية wl_display *display, ثابت حرف *name)
{
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
    إذا (WAYLAND_wl_display_create_queue_with_name) {
        إرجاع WAYLAND_wl_display_create_queue_with_name(display, name);
    }
#وإلاإذا SDL_WAYLAND_CHECK_VERSION(1, 23, 0)
    إرجاع WAYLAND_wl_display_create_queue_with_name(display, name);
#endif
    إرجاع WAYLAND_wl_display_create_queue(display);
}

ساكن فراغ Wayland_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_VideoData *data = device->internal;
    إذا (data->display && !data->display_externally_owned) {
        WAYLAND_wl_display_disconnect(data->display);
        SDL_ClearProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_POINTER);
    }
    SDL_free(data);
    SDL_free(device);
    SDL_WAYLAND_UnloadSymbols();
}

تعريفنوع بنية
{
    bool has_fifo_v1;
    بنية wl_fixes *wl_fixes;
} SDL_WaylandPreferredData;

ساكن فراغ wayland_preferred_check_handle_global(فراغ *data, بنية wl_registry *registry, uint32_t id,
                                                  ثابت حرف *interface, uint32_t version)
{
    SDL_WaylandPreferredData *d = data;

    إذا (SDL_strcmp(interface, "wp_fifo_manager_v1") == 0) {
        d->has_fifo_v1 = true;
    }
#ifdef SDL_WL_FIXES_VERSION
    وإلا إذا (SDL_strcmp(interface, wl_fixes_interface.name) == 0) {
        d->wl_fixes = wl_registry_bind(registry, id, &wl_fixes_interface, SDL_min(SDL_WL_FIXES_VERSION, version));
    }
#endif
}

ساكن فراغ wayland_preferred_check_remove_global(فراغ *data, بنية wl_registry *registry, uint32_t id)
{
    SDL_WaylandPreferredData *d = (SDL_WaylandPreferredData *)data;

    إذا (d->wl_fixes && wl_fixes_get_version(d->wl_fixes) >= WL_FIXES_ACK_GLOBAL_REMOVE_SINCE_VERSION) {
        wl_fixes_ack_global_remove(d->wl_fixes, registry, id);
    }
}

ساكن ثابت بنية wl_registry_listener preferred_registry_listener = {
    wayland_preferred_check_handle_global,
    wayland_preferred_check_remove_global
};

ساكن bool Wayland_IsPreferred(بنية wl_display *display)
{
    بنية wl_registry *registry = wl_display_get_registry(display);
    SDL_WaylandPreferredData preferred_data = { 0 };

    إذا (!registry) {
        SDL_SetError("Failed to get the Wayland registry");
        إرجاع false;
    }

    wl_registry_add_listener(registry, &preferred_registry_listener, &preferred_data);

    WAYLAND_wl_display_roundtrip(display);

    إذا (preferred_data.wl_fixes) {
        wl_fixes_destroy_registry(preferred_data.wl_fixes, registry);
        wl_fixes_destroy(preferred_data.wl_fixes);
    }
    wl_registry_destroy(registry);

    إذا (!preferred_data.has_fifo_v1) {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "This compositor lacks support for the fifo-v1 protocol; falling back to XWayland for GPU performance reasons (set SDL_VIDEO_DRIVER=wayland to override)");
    }
    إرجاع preferred_data.has_fifo_v1;
}

ساكن SDL_VideoDevice *Wayland_CreateDevice(bool require_preferred_protocols)
{
    SDL_VideoDevice *device;
    SDL_VideoData *data;
    بنية wl_display *display = SDL_GetPointerProperty(SDL_GetGlobalProperties(),
                                                 SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_POINTER, عدم);
    bool display_is_external = !!display;

    // Are we trying to connect to, or are currently in, a Wayland session?
    إذا (!SDL_getenv("WAYLAND_DISPLAY")) {
        ثابت حرف *session = SDL_getenv("XDG_SESSION_TYPE");
        إذا (session && SDL_strcasecmp(session, "wayland") != 0) {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Wayland initialization failed: no Wayland session available");
            إرجاع عدم;
        }
    }

    إذا (!SDL_WAYLAND_LoadSymbols()) {
        إرجاع عدم;
    }

    إذا (!display) {
        display = WAYLAND_wl_display_connect(عدم);
        إذا (!display) {
            SDL_WAYLAND_UnloadSymbols();
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to connect to the Wayland display server: %s", strerror(errno));
            إرجاع عدم;
        }
    }

    /*
     * If we are checking for preferred Wayland, then let's query for
     * fifo-v1's existence, so we don't regress GPU-bound performance
     * and frame-pacing by default due to swapchain starvation.
     */
    إذا (require_preferred_protocols && !Wayland_IsPreferred(display)) {
        إذا (!display_is_external) {
            WAYLAND_wl_display_disconnect(display);
        }
        SDL_WAYLAND_UnloadSymbols();
        إرجاع عدم;
    }

    data = SDL_calloc(1, حجم(*data));
    إذا (!data) {
        إذا (!display_is_external) {
            WAYLAND_wl_display_disconnect(display);
        }
        SDL_WAYLAND_UnloadSymbols();
        إرجاع عدم;
    }

    data->initializing = true;
    data->display = display;
    data->display_externally_owned = display_is_external;
    data->scale_to_display_enabled = SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_SCALE_TO_DISPLAY, false);
    WAYLAND_wl_list_init(&data->seat_list);
    WAYLAND_wl_list_init(&external_window_list);

    // Initialize all variables that we clean on shutdown
    device = SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (!device) {
        SDL_free(data);
        إذا (!display_is_external) {
            WAYLAND_wl_display_disconnect(display);
        }
        SDL_WAYLAND_UnloadSymbols();
        إرجاع عدم;
    }

    إذا (!display_is_external) {
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
    إذا (SDL_SystemTheme_Init())
        device->system_theme = SDL_SystemTheme_Get();
#endif

    device->GetTextMimeTypes = Wayland_GetTextMimeTypes;
    device->SetClipboardData = Wayland_SetClipboardData;
    device->GetClipboardData = Wayland_GetClipboardData;
    device->HasClipboardData = Wayland_HasClipboardData;
    device->Start_Text_إدخال = Wayland_Start_Text_إدخال;
    device->Stop_Text_إدخال = Wayland_Stop_Text_إدخال;
    device->Update_Text_إدخال_Area = Wayland_Update_Text_إدخال_Area;

#ifdef SDL_VIDEO_VULKAN
    device->Vulkan_LoadLibrary = Wayland_Vulkan_LoadLibrary;
    device->Vulkan_UnloadLibrary = Wayland_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = Wayland_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = Wayland_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = Wayland_Vulkan_DestroySurface;
    device->Vulkan_GetPresentationSupport = Wayland_Vulkan_GetPresentationSupport;
#endif

    device->حرر = Wayland_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_MODE_SWITCHING_EMULATED |
                          VIDEO_DEVICE_CAPS_HAS_POPUP_WINDOW_SUPPORT |
                          VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS |
                          VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES |
                          VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES;

    إرجاع device;
}

ساكن SDL_VideoDevice *Wayland_Preferred_CreateDevice(فراغ)
{
    إرجاع Wayland_CreateDevice(true);
}

ساكن SDL_VideoDevice *Wayland_Fallback_CreateDevice(فراغ)
{
    إرجاع Wayland_CreateDevice(false);
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

ساكن فراغ handle_xdg_output_logical_position(فراغ *data, بنية zxdg_output_v1 *xdg_output, int32_t x, int32_t y)
{
    SDL_DisplayData *internal = (SDL_DisplayData *)data;

    internal->geometry_changed |= internal->logical.x != x || internal->logical.y != y;
    internal->logical.x = x;
    internal->logical.y = y;
    internal->has_logical_position = true;
}

ساكن فراغ handle_xdg_output_logical_size(فراغ *data, بنية zxdg_output_v1 *xdg_output, int32_t width, int32_t height)
{
    SDL_DisplayData *internal = (SDL_DisplayData *)data;

    internal->geometry_changed |= internal->logical.width != width || internal->logical.height != height;
    internal->logical.width = width;
    internal->logical.height = height;
    internal->has_logical_size = true;
}

ساكن فراغ handle_xdg_output_done(فراغ *data, بنية zxdg_output_v1 *xdg_output)
{
    SDL_DisplayData *internal = data;

    /*
     * xdg-output.done events are deprecated and only apply below version 3 of the protocol.
     * A wl-output.done event will be emitted in version 3 or higher.
     */
    إذا (zxdg_output_v1_get_version(internal->xdg_output) < 3) {
        handle_wl_output_done(data, internal->output);
    }
}

ساكن فراغ handle_xdg_output_name(فراغ *data, بنية zxdg_output_v1 *xdg_output, ثابت حرف *name)
{
    SDL_DisplayData *internal = (SDL_DisplayData *)data;

    // Deprecated as of wl_output v4.
    إذا (wl_output_get_version(internal->output) < WL_OUTPUT_NAME_SINCE_VERSION &&
        internal->display == 0) {
        SDL_free(internal->wl_output_name);
        internal->wl_output_name = SDL_strdup(name);
    }
}

ساكن فراغ handle_xdg_output_description(فراغ *data, بنية zxdg_output_v1 *xdg_output, ثابت حرف *description)
{
    SDL_DisplayData *internal = (SDL_DisplayData *)data;

    // Deprecated as of wl_output v4.
    إذا (wl_output_get_version(internal->output) < WL_OUTPUT_DESCRIPTION_SINCE_VERSION &&
        internal->display == 0) {
        // xdg-output descriptions, if available, supersede wl-output model names.
        SDL_free(internal->placeholder.name);
        internal->placeholder.name = SDL_strdup(description);
    }
}

ساكن ثابت بنية zxdg_output_v1_listener xdg_output_listener = {
    handle_xdg_output_logical_position,
    handle_xdg_output_logical_size,
    handle_xdg_output_done,
    handle_xdg_output_name,
    handle_xdg_output_description,
};

ساكن فراغ AddEmulatedModes(SDL_DisplayData *dispdata, صحيح native_width, صحيح native_height)
{
    بنية EmulatedMode
    {
        صحيح w;
        صحيح h;
    };

    // Resolution lists courtesy of XWayland
    ثابت بنية EmulatedMode mode_list[] = {
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

    صحيح i;
    SDL_DisplayMode mode;
    SDL_VideoDisplay *dpy = dispdata->display ? SDL_GetVideoDisplay(dispdata->display) : &dispdata->placeholder;
    ثابت bool rot_90 = native_width < native_height; // Reverse width/height for portrait displays.

    لكل (i = 0; i < SDL_arraysize(mode_list); ++i) {
        SDL_zero(mode);
        mode.format = dpy->desktop_mode.format;
        mode.refresh_rate_numerator = dpy->desktop_mode.refresh_rate_numerator;
        mode.refresh_rate_denominator = dpy->desktop_mode.refresh_rate_denominator;

        إذا (rot_90) {
            mode.w = mode_list[i].h;
            mode.h = mode_list[i].w;
        } وإلا {
            mode.w = mode_list[i].w;
            mode.h = mode_list[i].h;
        }

        // Only add modes that are smaller than the native mode.
        إذا ((mode.w < native_width && mode.h < native_height) ||
            (mode.w < native_width && mode.h == native_height) ||
            (mode.w == native_width && mode.h < native_height)) {
            SDL_AddFullscreenDisplayMode(dpy, &mode);
        }
    }
}

ساكن فراغ handle_wl_output_geometry(فراغ *data, بنية wl_output *output, صحيح x, صحيح y,
                                      صحيح physical_width, صحيح physical_height, صحيح subpixel,
                                      ثابت حرف *make, ثابت حرف *model, صحيح transform)
{
    SDL_DisplayData *internal = (SDL_DisplayData *)data;

    // Apply the change from wl-output only if xdg-output is not supported
    إذا (!internal->has_logical_position) {
        internal->geometry_changed |= internal->logical.x != x || internal->logical.y != y;
        internal->logical.x = x;
        internal->logical.y = y;
    }
    internal->physical.width_mm = physical_width;
    internal->physical.height_mm = physical_height;

    // The model is only used for the output name if wl_output or xdg-output haven't provided a description.
    إذا (internal->display == 0 && !internal->placeholder.name) {
        internal->placeholder.name = SDL_strdup(model);
    }

    internal->transform = transform;
#define TF_CASE(in, out)                                 \
    حالة WL_OUTPUT_TRANSFORM_##in:                       \
        internal->orientation = SDL_ORIENTATION_##out; \
        اكسر;
    إذا (internal->physical.width_mm >= internal->physical.height_mm) {
        بدل (transform) {
            TF_CASE(NORMAL, LANDSCAPE)
            TF_CASE(90, PORTRAIT)
            TF_CASE(180, LANDSCAPE_FLIPPED)
            TF_CASE(270, PORTRAIT_FLIPPED)
            TF_CASE(FLIPPED, LANDSCAPE_FLIPPED)
            TF_CASE(FLIPPED_90, PORTRAIT_FLIPPED)
            TF_CASE(FLIPPED_180, LANDSCAPE)
            TF_CASE(FLIPPED_270, PORTRAIT)
        }
    } وإلا {
        بدل (transform) {
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

ساكن فراغ handle_wl_output_mode(فراغ *data, بنية wl_output *output, uint32_t flags,
                                  صحيح width, صحيح height, صحيح refresh)
{
    SDL_DisplayData *internal = (SDL_DisplayData *)data;

    إذا (flags & WL_OUTPUT_MODE_CURRENT) {
        internal->geometry_changed |= internal->pixel.width != width || internal->pixel.height != height;
        internal->pixel.width = width;
        internal->pixel.height = height;

        /*
         * Don't rotate this yet, wl-output coordinates are transformed in
         * handle_done and xdg-output coordinates are pre-transformed.
         */
        إذا (!internal->has_logical_size) {
            internal->geometry_changed |= internal->logical.width != width || internal->logical.height != height;
            internal->logical.width = width;
            internal->logical.height = height;
        }

        internal->refresh = refresh;
    }
}

ساكن فراغ handle_wl_output_done(فراغ *data, بنية wl_output *output)
{
    ثابت bool mode_emulation_enabled = SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_MODE_EMULATION, true);
    SDL_DisplayData *internal = (SDL_DisplayData *)data;
    SDL_VideoData *video = internal->videodata;
    SDL_DisplayMode native_mode, desktop_mode;

    /*
     * When using xdg-output, two wl-output.done events will be emitted:
     * one at the completion of wl-display and one at the completion of xdg-output.
     *
     * All required events must be received before proceeding.
     */
    ثابت صحيح event_await_تعداد = 1 + (internal->xdg_output != عدم);

    internal->wl_output_done_تعداد = SDL_min(internal->wl_output_done_تعداد + 1, event_await_تعداد + 1);

    إذا (internal->wl_output_done_تعداد < event_await_تعداد) {
        إرجاع;
    }

    // If the display was already created, reset and rebuild the mode list.
    SDL_VideoDisplay *dpy = SDL_GetVideoDisplay(internal->display);
    إذا (dpy) {
        SDL_ResetFullscreenDisplayModes(dpy);
    }

    // The native display resolution
    SDL_zero(native_mode);
    native_mode.format = SDL_PIXELFORMAT_XRGB8888;

    // Transform the pixel values, if necessary.
    إذا (internal->transform & WL_OUTPUT_TRANSFORM_90) {
        native_mode.w = internal->pixel.height;
        native_mode.h = internal->pixel.width;
    } وإلا {
        native_mode.w = internal->pixel.width;
        native_mode.h = internal->pixel.height;
    }
    native_mode.refresh_rate_numerator = internal->refresh;
    native_mode.refresh_rate_denominator = 1000;

    إذا (internal->has_logical_size) { // If xdg-output is present...
        إذا (native_mode.w != internal->logical.width || native_mode.h != internal->logical.height) {
            // ...and the compositor scales the logical viewport...
            إذا (video->viewporter) {
                // ...and viewports are supported, calculate the true scale of the output.
                internal->scale_factor = (مزدوج)native_mode.w / (مزدوج)internal->logical.width;
            } وإلا {
                // ...otherwise, the 'native' pixel values are a multiple of the logical screen size.
                internal->scale_factor = internal->integer_scale_factor;
                internal->pixel.width = internal->logical.width * internal->integer_scale_factor;
                internal->pixel.height = internal->logical.height * internal->integer_scale_factor;
            }
        } وإلا {
            /* ...and the output viewport is not scaled in the global compositing
             * space, the output dimensions need to be divided by the scale factor.
             *
             * NOTE: This path is needed for old versions of GNOME that predate fractional scaling.
             */
            internal->scale_factor = internal->integer_scale_factor;
            internal->logical.width /= internal->integer_scale_factor;
            internal->logical.height /= internal->integer_scale_factor;
        }
    } وإلا {
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

    إذا (!video->scale_to_display_enabled) {
        desktop_mode.w = internal->logical.width;
        desktop_mode.h = internal->logical.height;
        desktop_mode.pixel_density = (عائم)internal->scale_factor;
    } وإلا {
        desktop_mode.w = native_mode.w;
        desktop_mode.h = native_mode.h;
        desktop_mode.pixel_density = 1.0f;
    }

    desktop_mode.refresh_rate_numerator = internal->refresh;
    desktop_mode.refresh_rate_denominator = 1000;

    إذا (internal->display > 0) {
        dpy = SDL_GetVideoDisplay(internal->display);
    } وإلا {
        dpy = &internal->placeholder;
    }

    إذا (video->scale_to_display_enabled) {
        SDL_SetDisplayContentScale(dpy, (عائم)internal->scale_factor);
    }

    // Set the desktop display mode.
    SDL_SetDesktopDisplayMode(dpy, &desktop_mode);

    // Expose the unscaled, native resolution if the scale is 1.0 or viewports are available...
    إذا (internal->scale_factor == 1.0 || video->viewporter) {
        SDL_AddFullscreenDisplayMode(dpy, &native_mode);
        إذا (native_mode.w != desktop_mode.w ||
            native_mode.h != desktop_mode.h) {
            SDL_AddFullscreenDisplayMode(dpy, &desktop_mode);
        }
    } وإلا {
        // ...otherwise expose the integer scaled variants of the desktop resolution down to 1.
        desktop_mode.pixel_density = 1.0f;

        لكل (صحيح i = (صحيح)internal->scale_factor; i > 0; --i) {
            desktop_mode.w = internal->logical.width * i;
            desktop_mode.h = internal->logical.height * i;
            SDL_AddFullscreenDisplayMode(dpy, &desktop_mode);
        }
    }

    // Add emulated modes if wp_viewporter is supported and mode emulation is enabled.
    إذا (video->viewporter && mode_emulation_enabled) {
        // The transformed display pixel width/height must be used here.
        AddEmulatedModes(internal, native_mode.w, native_mode.h);
    }

    إذا (internal->display == 0) {
        // First time getting display info, initialize the VideoDisplay
        إذا (internal->physical.width_mm >= internal->physical.height_mm) {
            internal->placeholder.natural_orientation = SDL_ORIENTATION_LANDSCAPE;
        } وإلا {
            internal->placeholder.natural_orientation = SDL_ORIENTATION_PORTRAIT;
        }
        internal->placeholder.current_orientation = internal->orientation;
        internal->placeholder.internal = internal;

        internal->placeholder.props = SDL_CreateProperties();
        SDL_SetPointerProperty(internal->placeholder.props, SDL_PROP_DISPLAY_WAYLAND_WL_OUTPUT_POINTER, internal->output);

        // During initialization, the displays will be added after enumeration is complete.
        إذا (!video->initializing) {
            إذا (video->wp_color_manager_v1) {
                Wayland_GetColorInfoForOutput(internal, false);
            }
            إذا (video->scale_to_display_enabled) {
                Wayland_DeriveOutputPixelCoordinates(video);
            }

            internal->display = SDL_AddVideoDisplay(&internal->placeholder, true);
            Wayland_RefreshWindowPositions();

            SDL_free(internal->placeholder.name);
            SDL_zero(internal->placeholder);
        }
    } وإلا {
        SDL_SendDisplayEvent(dpy, SDL_EVENT_DISPLAY_ORIENTATION, internal->orientation, 0);

        إذا (internal->geometry_changed) {
            إذا (video->scale_to_display_enabled) {
                Wayland_DeriveOutputPixelCoordinates(video);
            }

            SDL_SendDisplayEvent(dpy, SDL_EVENT_DISPLAY_MOVED, 0, 0);
            Wayland_RefreshWindowPositions();
        }
    }

    internal->geometry_changed = false;
}

ساكن فراغ handle_wl_output_scale(فراغ *data, بنية wl_output *output, int32_t factor)
{
    SDL_DisplayData *internal = (SDL_DisplayData *)data;
    internal->integer_scale_factor = factor;
}

ساكن فراغ handle_wl_output_name(فراغ *data, بنية wl_output *wl_output, ثابت حرف *name)
{
    SDL_DisplayData *internal = (SDL_DisplayData *)data;

    SDL_free(internal->wl_output_name);
    internal->wl_output_name = SDL_strdup(name);
}

ساكن فراغ handle_wl_output_description(فراغ *data, بنية wl_output *wl_output, ثابت حرف *description)
{
    SDL_DisplayData *internal = (SDL_DisplayData *)data;

    إذا (internal->display == 0) {
        // The description, if available, supersedes the model name.
        SDL_free(internal->placeholder.name);
        internal->placeholder.name = SDL_strdup(description);
    }
}

ساكن ثابت بنية wl_output_listener output_listener = {
    handle_wl_output_geometry,   // Version 1
    handle_wl_output_mode,       // Version 1
    handle_wl_output_done,       // Version 2
    handle_wl_output_scale,      // Version 2
    handle_wl_output_name,       // Version 4
    handle_wl_output_description // Version 4
};

ساكن فراغ handle_output_image_description_changed(فراغ *data,
                                                    بنية wp_color_management_output_v1 *wp_color_management_output_v1)
{
    SDL_DisplayData *display = (SDL_DisplayData *)data;
    Wayland_GetColorInfoForOutput(display, false);
}

ساكن ثابت بنية wp_color_management_output_v1_listener wp_color_management_output_listener = {
    handle_output_image_description_changed
};

ساكن bool Wayland_add_display(SDL_VideoData *d, uint32_t id, uint32_t version)
{
    بنية wl_output *output;
    SDL_DisplayData *data;

    output = wl_registry_bind(d->registry, id, &wl_output_interface, version);
    إذا (!output) {
        إرجاع SDL_SetError("Failed to retrieve output.");
    }
    data = (SDL_DisplayData *)SDL_calloc(1, حجم(*data));
    data->videodata = d;
    data->output = output;
    data->registry_id = id;
    data->scale_factor = 1.0f;
    data->integer_scale_factor = 1;

    wl_output_add_listener(output, &output_listener, data);
    SDL_WAYLAND_register_output(output);

    // Keep a list of outputs for sorting and deferred protocol initialization.
    إذا (d->output_تعداد == d->output_max) {
        d->output_max += 4;
        d->output_list = SDL_realloc(d->output_list, حجم(SDL_DisplayData *) * d->output_max);
    }
    d->output_list[d->output_تعداد++] = data;

    إذا (data->videodata->xdg_output_manager) {
        data->xdg_output = zxdg_output_manager_v1_get_xdg_output(data->videodata->xdg_output_manager, output);
        zxdg_output_v1_add_listener(data->xdg_output, &xdg_output_listener, data);
    }
    إذا (data->videodata->wp_color_manager_v1) {
        data->wp_color_management_output = wp_color_manager_v1_get_output(data->videodata->wp_color_manager_v1, output);
        wp_color_management_output_v1_add_listener(data->wp_color_management_output, &wp_color_management_output_listener, data);

        // If not initializing, this will be queried synchronously in wl_output.done.
        إذا (d->initializing) {
            Wayland_GetColorInfoForOutput(data, true);
        }
    }
    إرجاع true;
}

ساكن فراغ Wayland_free_display(SDL_VideoDisplay *display, bool send_event)
{
    إذا (display) {
        SDL_DisplayData *display_data = display->internal;

        /* A preceding surface leave event is not guaranteed when an output is removed,
         * so ensure that no window continues to hold a reference to a removed output.
         */
        لكل (SDL_Window *window = SDL_GetVideoDevice()->windows; window; window = window->next) {
            Wayland_RemoveOutputFromWindow(window->internal, display_data);
        }

        SDL_free(display_data->wl_output_name);

        إذا (display_data->wp_color_management_output) {
            Wayland_FreeColorInfoState(display_data->color_info_state);
            wp_color_management_output_v1_destroy(display_data->wp_color_management_output);
        }

        إذا (display_data->xdg_output) {
            zxdg_output_v1_destroy(display_data->xdg_output);
        }

        إذا (wl_output_get_version(display_data->output) >= WL_OUTPUT_RELEASE_SINCE_VERSION) {
            wl_output_release(display_data->output);
        } وإلا {
            wl_output_destroy(display_data->output);
        }

        SDL_DelVideoDisplay(display->id, send_event);
    }
}

ساكن فراغ Wayland_FinalizeDisplays(SDL_VideoData *vid)
{
    Wayland_SortOutputs(vid);

    لكل(صحيح i = 0; i < vid->output_تعداد; ++i) {
        SDL_DisplayData *d = vid->output_list[i];
        d->display = SDL_AddVideoDisplay(&d->placeholder, false);
        SDL_free(d->placeholder.name);
        SDL_zero(d->placeholder);
    }
}

ساكن فراغ Wayland_init_xdg_output(SDL_VideoData *d)
{
    لكل (صحيح i = 0; i < d->output_تعداد; ++i) {
        SDL_DisplayData *disp = d->output_list[i];
        disp->xdg_output = zxdg_output_manager_v1_get_xdg_output(disp->videodata->xdg_output_manager, disp->output);
        zxdg_output_v1_add_listener(disp->xdg_output, &xdg_output_listener, disp);
    }
}

ساكن فراغ Wayland_InitColorManager(SDL_VideoData *d)
{
    لكل (صحيح i = 0; i < d->output_تعداد; ++i) {
        SDL_DisplayData *disp = d->output_list[i];
        disp->wp_color_management_output = wp_color_manager_v1_get_output(disp->videodata->wp_color_manager_v1, disp->output);
        wp_color_management_output_v1_add_listener(disp->wp_color_management_output, &wp_color_management_output_listener, disp);
        Wayland_GetColorInfoForOutput(disp, true);
    }
}

ساكن فراغ handle_xdg_session_created(فراغ *data, بنية xdg_session_v1 *xdg_session_v1, ثابت حرف *id)
{
    SDL_SetStringProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, id);
}

ساكن فراغ handle_xdg_session_restored(فراغ *data, بنية xdg_session_v1 *xdg_session_v1)
{
    // NOP
}

ساكن فراغ handle_xdg_session_replaced(فراغ *data, بنية xdg_session_v1 *xdg_session_v1)
{
    SDL_VideoDevice *viddev = SDL_GetVideoDevice();
    SDL_VideoData *viddata = data;

    // Clean up all session objects, as they have become inert, and should be destroyed.
    SDL_SetStringProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, عدم);

    لكل (SDL_Window *w = viddev->windows; w; w = w->next) {
        SDL_WindowData *d = w->internal;

        إذا (d->xdg_toplevel_session) {
            xdg_toplevel_session_v1_destroy(d->xdg_toplevel_session);
            d->xdg_toplevel_session = عدم;

            SDL_free(d->session_id);
            d->session_id = عدم;
        }
    }

    إذا (viddata->xdg_session) {
        xdg_session_v1_destroy(viddata->xdg_session);
        viddata->xdg_session = عدم;
    }
}

ساكن ثابت بنية xdg_session_v1_listener xdg_session_listener = {
    .created  = handle_xdg_session_created,
    .restored = handle_xdg_session_restored,
    .replaced = handle_xdg_session_replaced
};

فراغ Wayland_CreateSession(SDL_VideoData *viddata)
{
    إذا (!viddata->xdg_session_manager) {
        // Set the ID string to null if session management is not available.
        SDL_SetStringProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, عدم);
        إرجاع;
    }

    // Register a new session, if one does not yet exist.
    إذا (!viddata->xdg_session) {
        ثابت حرف *session_id = SDL_GetStringProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, عدم);
        إذا (session_id) {
            إذا (*session_id == '\0') {
                // Create a new session if the ID string is empty.
                session_id = عدم;
            }

            ثابت تعداد xdg_session_manager_v1_reason reason = session_id ? XDG_SESSION_MANAGER_V1_REASON_SESSION_RESTORE : XDG_SESSION_MANAGER_V1_REASON_LAUNCH;
            viddata->xdg_session = xdg_session_manager_v1_get_session(viddata->xdg_session_manager, reason, session_id);
            xdg_session_v1_add_listener(viddata->xdg_session, &xdg_session_listener, viddata);
        }
    }
}

ساكن فراغ Wayland_SessionDestroy(SDL_VideoData *viddata)
{
    // If the session string was cleared, remove the session.
    إذا (viddata->xdg_session) {
        ثابت حرف *session_id = SDL_GetStringProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, عدم);
        إذا (!session_id || *session_id == '\0') {
            xdg_session_v1_remove(viddata->xdg_session);

            WAYLAND_wl_display_roundtrip(viddata->display);
        } وإلا {
            xdg_session_v1_destroy(viddata->xdg_session);
        }

        viddata->xdg_session = عدم;
    }
}

ساكن فراغ handle_xdg_wm_base_ping(فراغ *data, بنية xdg_wm_base *xdg, uint32_t serial)
{
    xdg_wm_base_pong(xdg, serial);
}

ساكن ثابت بنية xdg_wm_base_listener _xdg_wm_base_listener = {
    handle_xdg_wm_base_ping
};

#ifdef HAVE_LIBDECOR_H
ساكن فراغ libdecor_error(بنية libdecor *context,
                           تعداد libdecor_error error,
                           ثابت حرف *message)
{
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "libdecor error (%d): %s", error, message);
}

ساكن بنية libdecor_interface libdecor_interface = {
    libdecor_error
};
#endif

ساكن فراغ handle_registry_global(فراغ *data, بنية wl_registry *registry, uint32_t id,
                                   ثابت حرف *interface, uint32_t version)
{
    SDL_VideoData *d = data;

    إذا (SDL_strcmp(interface, wl_compositor_interface.name) == 0) {
        d->compositor = wl_registry_bind(d->registry, id, &wl_compositor_interface, SDL_min(SDL_WL_COMPOSITOR_VERSION, version));
    } وإلا إذا (SDL_strcmp(interface, wl_subcompositor_interface.name) == 0) {
        d->subcompositor = wl_registry_bind(d->registry, id, &wl_subcompositor_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, wl_output_interface.name) == 0) {
        Wayland_add_display(d, id, SDL_min(version, SDL_WL_OUTPUT_VERSION));
    } وإلا إذا (SDL_strcmp(interface, wl_seat_interface.name) == 0) {
        بنية wl_seat *seat = wl_registry_bind(d->registry, id, &wl_seat_interface, SDL_min(SDL_WL_SEAT_VERSION, version));
        Wayland_DisplayCreateSeat(d, seat, id);
    } وإلا إذا (SDL_strcmp(interface, xdg_wm_base_interface.name) == 0) {
        d->shell.xdg = wl_registry_bind(d->registry, id, &xdg_wm_base_interface, SDL_min(version, 7));
        xdg_wm_base_add_listener(d->shell.xdg, &_xdg_wm_base_listener, عدم);
    } وإلا إذا (SDL_strcmp(interface, wl_shm_interface.name) == 0) {
        d->shm = wl_registry_bind(registry, id, &wl_shm_interface, SDL_min(SDL_WL_SHM_VERSION, version));
    } وإلا إذا (SDL_strcmp(interface, zwp_relative_pointer_manager_v1_interface.name) == 0) {
        d->relative_pointer_manager = wl_registry_bind(d->registry, id, &zwp_relative_pointer_manager_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, zwp_pointer_constraints_v1_interface.name) == 0) {
        d->pointer_constraints = wl_registry_bind(d->registry, id, &zwp_pointer_constraints_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, zwp_keyboard_shortcuts_inhibit_manager_v1_interface.name) == 0) {
        d->مفتاح_inhibitor_manager = wl_registry_bind(d->registry, id, &zwp_keyboard_shortcuts_inhibit_manager_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, zwp_idle_inhibit_manager_v1_interface.name) == 0) {
        d->idle_inhibit_manager = wl_registry_bind(d->registry, id, &zwp_idle_inhibit_manager_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, xdg_activation_v1_interface.name) == 0) {
        d->activation_manager = wl_registry_bind(d->registry, id, &xdg_activation_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, zwp_text_إدخال_manager_v3_interface.name) == 0) {
        d->text_إدخال_manager = wl_registry_bind(d->registry, id, &zwp_text_إدخال_manager_v3_interface, 1);
        Wayland_Display_Init_Text_إدخال_Manager(d, id);
    } وإلا إذا (SDL_strcmp(interface, wl_data_device_manager_interface.name) == 0) {
        d->data_device_manager = wl_registry_bind(d->registry, id, &wl_data_device_manager_interface, SDL_min(3, version));
        Wayland_DisplayInitDataDeviceManager(d);
    } وإلا إذا (SDL_strcmp(interface, zwp_primary_selection_device_manager_v1_interface.name) == 0) {
        d->primary_selection_device_manager = wl_registry_bind(d->registry, id, &zwp_primary_selection_device_manager_v1_interface, 1);
        Wayland_DisplayInitPrimarySelectionDeviceManager(d);
    } وإلا إذا (SDL_strcmp(interface, zxdg_decoration_manager_v1_interface.name) == 0) {
        d->decoration_manager = wl_registry_bind(d->registry, id, &zxdg_decoration_manager_v1_interface, SDL_min(2, version));
    } وإلا إذا (SDL_strcmp(interface, zwp_tablet_manager_v2_interface.name) == 0) {
        d->tablet_manager = wl_registry_bind(d->registry, id, &zwp_tablet_manager_v2_interface, 1);
        Wayland_DisplayInitTabletManager(d);
    } وإلا إذا (SDL_strcmp(interface, zxdg_output_manager_v1_interface.name) == 0) {
        version = SDL_min(version, 3); // Versions 1 through 3 are supported.
        d->xdg_output_manager = wl_registry_bind(d->registry, id, &zxdg_output_manager_v1_interface, version);
        Wayland_init_xdg_output(d);
    } وإلا إذا (SDL_strcmp(interface, wp_viewporter_interface.name) == 0) {
        d->viewporter = wl_registry_bind(d->registry, id, &wp_viewporter_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, wp_fractional_scale_manager_v1_interface.name) == 0) {
        d->fractional_scale_manager = wl_registry_bind(d->registry, id, &wp_fractional_scale_manager_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, zwp_إدخال_timestamps_manager_v1_interface.name) == 0) {
        d->إدخال_timestamps_manager = wl_registry_bind(d->registry, id, &zwp_إدخال_timestamps_manager_v1_interface, 1);
        Wayland_Display_Init_إدخال_Timestamp_Manager(d);
    } وإلا إذا (SDL_strcmp(interface, wp_cursor_shape_manager_v1_interface.name) == 0) {
        d->cursor_shape_manager = wl_registry_bind(d->registry, id, &wp_cursor_shape_manager_v1_interface, SDL_min(version, 2));
        Wayland_DisplayInitCursorShapeManager(d);
    } وإلا إذا (SDL_strcmp(interface, zxdg_exporter_v2_interface.name) == 0) {
        d->zxdg_exporter_v2 = wl_registry_bind(d->registry, id, &zxdg_exporter_v2_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, xdg_wm_dialog_v1_interface.name) == 0) {
        d->xdg_wm_dialog_v1 = wl_registry_bind(d->registry, id, &xdg_wm_dialog_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, wp_alpha_modifier_v1_interface.name) == 0) {
        d->wp_alpha_modifier_v1 = wl_registry_bind(d->registry, id, &wp_alpha_modifier_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, xdg_toplevel_icon_manager_v1_interface.name) == 0) {
        d->xdg_toplevel_icon_manager_v1 = wl_registry_bind(d->registry, id, &xdg_toplevel_icon_manager_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, frog_color_management_factory_v1_interface.name) == 0) {
        d->frog_color_management_factory_v1 = wl_registry_bind(d->registry, id, &frog_color_management_factory_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, wp_color_manager_v1_interface.name) == 0) {
        d->wp_color_manager_v1 = wl_registry_bind(d->registry, id, &wp_color_manager_v1_interface, SDL_min(version, 2));
        Wayland_InitColorManager(d);
    } وإلا إذا (SDL_strcmp(interface, wp_pointer_warp_v1_interface.name) == 0) {
        d->wp_pointer_warp_v1 = wl_registry_bind(d->registry, id, &wp_pointer_warp_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, zwp_pointer_gestures_v1_interface.name) == 0) {
        d->zwp_pointer_gestures = wl_registry_bind(d->registry, id, &zwp_pointer_gestures_v1_interface, SDL_min(version, 3));
        Wayland_DisplayInitPointerGestureManager(d);
    } وإلا إذا (SDL_strcmp(interface, wp_single_pixel_buffer_manager_v1_interface.name) == 0) {
        d->single_pixel_buffer_manager = wl_registry_bind(d->registry, id, &wp_single_pixel_buffer_manager_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, xdg_session_manager_v1_interface.name) == 0) {
        d->xdg_session_manager = wl_registry_bind(d->registry, id, &xdg_session_manager_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, xdg_toplevel_tag_manager_v1_interface.name) == 0) {
        d->xdg_toplevel_tag_manager = wl_registry_bind(d->registry, id, &xdg_toplevel_tag_manager_v1_interface, 1);
    }
#ifdef SDL_WL_FIXES_VERSION
    وإلا إذا (SDL_strcmp(interface, wl_fixes_interface.name) == 0) {
        d->wl_fixes = wl_registry_bind(d->registry, id, &wl_fixes_interface, SDL_min(SDL_WL_FIXES_VERSION, version));
    }
#endif
}

ساكن فراغ handle_registry_remove_global(فراغ *data, بنية wl_registry *registry, uint32_t id)
{
    SDL_VideoData *d = data;

    // We don't get an interface, just an ID, so check outputs and seats.
    لكل (صحيح i = 0; i < d->output_تعداد; ++i) {
        SDL_DisplayData *disp = d->output_list[i];
        إذا (disp->registry_id == id) {
            Wayland_free_display(SDL_GetVideoDisplay(disp->display), true);

            إذا (i < d->output_تعداد) {
                SDL_memmove(&d->output_list[i], &d->output_list[i + 1], حجم(SDL_DisplayData *) * (d->output_تعداد - i - 1));
            }

            d->output_تعداد--;
            اذهب ack_remove;
        }
    }

    SDL_WaylandSeat *seat, *temp;
    wl_list_for_each_safe (seat, temp, &d->seat_list, link) {
        إذا (seat->registry_id == id) {
            Wayland_SeatDestroy(seat, false);
            اذهب ack_remove;
        }
    }

ack_remove:
    إذا (d->wl_fixes && wl_fixes_get_version(d->wl_fixes) >= WL_FIXES_ACK_GLOBAL_REMOVE_SINCE_VERSION) {
        wl_fixes_ack_global_remove(d->wl_fixes, registry, id);
    }
}

ساكن ثابت بنية wl_registry_listener registry_listener = {
    handle_registry_global,
    handle_registry_remove_global
};

#ifdef HAVE_LIBDECOR_H
ساكن bool should_use_libdecor(SDL_VideoData *data, bool ignore_xdg)
{
    إذا (!SDL_WAYLAND_HAVE_WAYLAND_LIBDECOR) {
        إرجاع false;
    }

    إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_PREFER_LIBDECOR, false)) {
        إرجاع true;
    }

    إذا (ignore_xdg) {
        إرجاع true;
    }

    إذا (data->decoration_manager) {
        إرجاع false;
    }

    إرجاع true;
}

ساكن فراغ LibdecorNew(SDL_VideoData *data)
{
    data->shell.libdecor = libdecor_new(data->display, &libdecor_interface);
}

// Called in another thread, but the UI thread is blocked in SDL_WaitThread
// during that time, so it should be OK to dereference data without locks
ساكن صحيح SDLCALL LibdecorNewInThread(فراغ *data)
{
    LibdecorNew((SDL_VideoData *)data);
    إرجاع 0;
}
#endif

#ifdef HAVE_GETRESUID
#define SDL_getresuid getresuid
#وإلا
// Non-POSIX, but Linux and some BSDs have it.
// To reduce the number of code paths, if getresuid() isn't available at
// compile-time, we behave as though it existed but failed at runtime.
ساكن مضمن صحيح SDL_getresuid(uid_t *ruid, uid_t *euid, uid_t *suid) {
    errno = ENOSYS;
    إرجاع -1;
}
#endif

#ifdef HAVE_GETRESGID
#define SDL_getresgid getresgid
#وإلا
// Same as getresuid() but for the primary group
ساكن مضمن صحيح SDL_getresgid(gid_t *rgid, gid_t *egid, gid_t *sgid) {
    errno = ENOSYS;
    إرجاع -1;
}
#endif

bool CanUseGtk(فراغ)
{
    // "Real", "effective" and "saved" IDs: see e.g. Linux credentials(7)
    uid_t ruid = -1, euid = -1, suid = -1;
    gid_t rgid = -1, egid = -1, sgid = -1;

    إذا (!SDL_GetHintBoolean("SDL_ENABLE_GTK", true)) {
        SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "Not using GTK due to hint");
        إرجاع false;
    }

    // This is intended to match the check in gtkmain.c, rather than being
    // an exhaustive check for having elevated privileges: as a result
    // we don't use Linux getauxval() or prctl PR_GET_DUMPABLE,
    // BSD issetugid(), or similar OS-specific detection

    إذا (SDL_getresuid(&ruid, &euid, &suid) != 0) {
        ruid = suid = getuid();
        euid = geteuid();
    }

    إذا (SDL_getresgid(&rgid, &egid, &sgid) != 0) {
        rgid = sgid = getgid();
        egid = getegid();
    }

    // Real ID != effective ID means we are setuid or setgid:
    // GTK will refuse to initialize, and instead will call exit().
    إذا (ruid != euid || rgid != egid) {
        SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "Not using GTK due to setuid/setgid");
        إرجاع false;
    }

    // Real ID != saved ID means we are setuid or setgid, we previously
    // dropped privileges, but we can regain them; this protects against
    // accidents but does not protect against arbitrary code execution.
    // Again, GTK will refuse to initialize if this is the case.
    إذا (ruid != suid || rgid != sgid) {
        SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "Not using GTK due to saved uid/gid");
        إرجاع false;
    }

    إرجاع true;
}

bool Wayland_LoadLibdecor(SDL_VideoData *data, bool ignore_xdg)
{
#ifdef HAVE_LIBDECOR_H
    إذا (data->shell.libdecor != عدم) {
        إرجاع true; // Already loaded!
    }
    إذا (should_use_libdecor(data, ignore_xdg)) {
        إذا (CanUseGtk()) {
            LibdecorNew(data);
        } وإلا {
            // Intentionally initialize libdecor in a non-main thread
            // so that it will not use its GTK plugin, but instead will
            // fall back to the Cairo or dummy plugin
            SDL_Thread *thread = SDL_CreateThread(LibdecorNewInThread, "SDL_LibdecorNew", (فراغ *)data);
            // Note that the other thread now "owns" data until we have
            // waited for it, so don't touch data here
            SDL_WaitThread(thread, عدم);
        }

        إرجاع data->shell.libdecor != عدم;
    }
#endif
    إرجاع false;
}

bool Wayland_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

    data->event_thread_context = Wayland_CreateEventThread(data, "SDL Event Thread Queue");
    إذا (!data->event_thread_context) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Failed to create event thread context");
    }

    data->job_thread_context = Wayland_CreateJobThread();
    إذا (!data->job_thread_context) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Failed to create job thread context");
    }

    data->xkb_context = WAYLAND_xkb_context_new(0);
    إذا (!data->xkb_context) {
        إرجاع SDL_SetError("Failed to create XKB context");
    }

    data->registry = wl_display_get_registry(data->display);
    إذا (!data->registry) {
        إرجاع SDL_SetError("Failed to get the Wayland registry");
    }

    wl_registry_add_listener(data->registry, &registry_listener, data);

    // First roundtrip to receive all registry objects.
    WAYLAND_wl_display_roundtrip(data->display);

    // Require viewports and xdg-output for display scaling.
    إذا (data->scale_to_display_enabled) {
        إذا (!data->viewporter) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Display scaling requires the missing 'wp_viewporter' protocol: disabling");
            data->scale_to_display_enabled = false;
        }
        إذا (!data->xdg_output_manager) {
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

    إذا (data->primary_selection_device_manager) {
        _this->SetPrimarySelectionText = Wayland_SetPrimarySelectionText;
        _this->GetPrimarySelectionText = Wayland_GetPrimarySelectionText;
        _this->HasPrimarySelectionText = Wayland_HasPrimarySelectionText;
    }

    data->initializing = false;

    إرجاع true;
}

ساكن bool Wayland_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    SDL_VideoData *viddata = _this->internal;
    SDL_DisplayData *internal = display->internal;

    إذا (!viddata->scale_to_display_enabled) {
        rect->x = internal->logical.x;
        rect->y = internal->logical.y;
    } وإلا {
        rect->x = internal->pixel.x;
        rect->y = internal->pixel.y;
    }

    // When an emulated, exclusive fullscreen window has focus, treat the mode dimensions as the display bounds.
    إذا (display->fullscreen_window &&
        display->fullscreen_window->fullscreen_exclusive &&
        display->fullscreen_window->internal->active &&
        display->fullscreen_window->current_fullscreen_mode.w != 0 &&
        display->fullscreen_window->current_fullscreen_mode.h != 0) {
        rect->w = display->fullscreen_window->current_fullscreen_mode.w;
        rect->h = display->fullscreen_window->current_fullscreen_mode.h;
    } وإلا {
        إذا (!viddata->scale_to_display_enabled) {
            rect->w = display->current_mode->w;
            rect->h = display->current_mode->h;
        } وإلا إذا (internal->transform & WL_OUTPUT_TRANSFORM_90) {
            rect->w = internal->pixel.height;
            rect->h = internal->pixel.width;
        } وإلا {
            rect->w = internal->pixel.width;
            rect->h = internal->pixel.height;
        }
    }
    إرجاع true;
}

ساكن فراغ Wayland_VideoCleanup(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    SDL_WaylandSeat *seat, *tmp;

    Wayland_SessionDestroy(data);

    لكل (صحيح i = _this->رقم_displays - 1; i >= 0; --i) {
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
    data->event_thread_context = عدم;

    Wayland_DestroyJobThread(data->job_thread_context);
    data->job_thread_context = عدم;

    إذا (data->pointer_constraints) {
        zwp_pointer_constraints_v1_destroy(data->pointer_constraints);
        data->pointer_constraints = عدم;
    }

    إذا (data->relative_pointer_manager) {
        zwp_relative_pointer_manager_v1_destroy(data->relative_pointer_manager);
        data->relative_pointer_manager = عدم;
    }

    إذا (data->activation_manager) {
        xdg_activation_v1_destroy(data->activation_manager);
        data->activation_manager = عدم;
    }

    إذا (data->idle_inhibit_manager) {
        zwp_idle_inhibit_manager_v1_destroy(data->idle_inhibit_manager);
        data->idle_inhibit_manager = عدم;
    }

    إذا (data->مفتاح_inhibitor_manager) {
        zwp_keyboard_shortcuts_inhibit_manager_v1_destroy(data->مفتاح_inhibitor_manager);
        data->مفتاح_inhibitor_manager = عدم;
    }

    إذا (data->text_إدخال_manager) {
        zwp_text_إدخال_manager_v3_destroy(data->text_إدخال_manager);
        data->text_إدخال_manager = عدم;
    }

    إذا (data->xkb_context) {
        WAYLAND_xkb_context_unref(data->xkb_context);
        data->xkb_context = عدم;
    }

    إذا (data->tablet_manager) {
        zwp_tablet_manager_v2_destroy((بنية zwp_tablet_manager_v2 *)data->tablet_manager);
        data->tablet_manager = عدم;
    }

    إذا (data->data_device_manager) {
        wl_data_device_manager_destroy(data->data_device_manager);
        data->data_device_manager = عدم;
    }

    إذا (data->shm) {
        إذا (wl_shm_get_version(data->shm) >= WL_SHM_RELEASE_SINCE_VERSION) {
            wl_shm_release(data->shm);
        } وإلا {
            wl_shm_destroy(data->shm);
        }
        data->shm = عدم;
    }

    إذا (data->shell.xdg) {
        xdg_wm_base_destroy(data->shell.xdg);
        data->shell.xdg = عدم;
    }

    إذا (data->decoration_manager) {
        zxdg_decoration_manager_v1_destroy(data->decoration_manager);
        data->decoration_manager = عدم;
    }

    إذا (data->xdg_output_manager) {
        zxdg_output_manager_v1_destroy(data->xdg_output_manager);
        data->xdg_output_manager = عدم;
    }

    إذا (data->viewporter) {
        wp_viewporter_destroy(data->viewporter);
        data->viewporter = عدم;
    }

    إذا (data->primary_selection_device_manager) {
        zwp_primary_selection_device_manager_v1_destroy(data->primary_selection_device_manager);
        data->primary_selection_device_manager = عدم;
    }

    إذا (data->fractional_scale_manager) {
        wp_fractional_scale_manager_v1_destroy(data->fractional_scale_manager);
        data->fractional_scale_manager = عدم;
    }

    إذا (data->إدخال_timestamps_manager) {
        zwp_إدخال_timestamps_manager_v1_destroy(data->إدخال_timestamps_manager);
        data->إدخال_timestamps_manager = عدم;
    }

    إذا (data->cursor_shape_manager) {
        wp_cursor_shape_manager_v1_destroy(data->cursor_shape_manager);
        data->cursor_shape_manager = عدم;
    }

    إذا (data->zxdg_exporter_v2) {
        zxdg_exporter_v2_destroy(data->zxdg_exporter_v2);
        data->zxdg_exporter_v2 = عدم;
    }

    إذا (data->xdg_wm_dialog_v1) {
        xdg_wm_dialog_v1_destroy(data->xdg_wm_dialog_v1);
        data->xdg_wm_dialog_v1 = عدم;
    }

    إذا (data->wp_alpha_modifier_v1) {
        wp_alpha_modifier_v1_destroy(data->wp_alpha_modifier_v1);
        data->wp_alpha_modifier_v1 = عدم;
    }

    إذا (data->xdg_toplevel_icon_manager_v1) {
        xdg_toplevel_icon_manager_v1_destroy(data->xdg_toplevel_icon_manager_v1);
        data->xdg_toplevel_icon_manager_v1 = عدم;
    }

    إذا (data->frog_color_management_factory_v1) {
        frog_color_management_factory_v1_destroy(data->frog_color_management_factory_v1);
        data->frog_color_management_factory_v1 = عدم;
    }

    إذا (data->wp_color_manager_v1) {
        wp_color_manager_v1_destroy(data->wp_color_manager_v1);
        data->wp_color_manager_v1 = عدم;
    }

    إذا (data->wp_pointer_warp_v1) {
        wp_pointer_warp_v1_destroy(data->wp_pointer_warp_v1);
        data->wp_pointer_warp_v1 = عدم;
    }

    إذا (data->zwp_pointer_gestures) {
        إذا (zwp_pointer_gestures_v1_get_version(data->zwp_pointer_gestures) >= ZWP_POINTER_GESTURES_V1_RELEASE_SINCE_VERSION) {
            zwp_pointer_gestures_v1_release(data->zwp_pointer_gestures);
        } وإلا {
            zwp_pointer_gestures_v1_destroy(data->zwp_pointer_gestures);
        }
        data->zwp_pointer_gestures = عدم;
    }

    إذا (data->single_pixel_buffer_manager) {
        wp_single_pixel_buffer_manager_v1_destroy(data->single_pixel_buffer_manager);
        data->single_pixel_buffer_manager = عدم;
    }

    إذا (data->xdg_session_manager) {
        xdg_session_manager_v1_destroy(data->xdg_session_manager);
        data->xdg_session_manager = عدم;
    }

    إذا (data->xdg_toplevel_tag_manager) {
        xdg_toplevel_tag_manager_v1_destroy(data->xdg_toplevel_tag_manager);
        data->xdg_toplevel_tag_manager = عدم;
    }

    إذا (data->subcompositor) {
        wl_subcompositor_destroy(data->subcompositor);
        data->subcompositor = عدم;
    }

    إذا (data->compositor) {
        wl_compositor_destroy(data->compositor);
        data->compositor = عدم;
    }

    إذا (data->registry) {
        إذا (data->wl_fixes) {
            wl_fixes_destroy_registry(data->wl_fixes, data->registry);
            wl_fixes_destroy(data->wl_fixes);
            data->wl_fixes = عدم;
        }
        wl_registry_destroy(data->registry);
        data->registry = عدم;
    }
}

ساكن bool Wayland_VideoReconnect(SDL_VideoDevice *_this)
{
#إذا 0 // TODO RECONNECT: Uncomment all when https://invent.kde.org/plasma/kwin/-/wikis/Restarting is completed
    SDL_VideoData *data = _this->internal;

    SDL_Window *window = عدم;

    SDL_GLContext current_ctx = SDL_GL_GetCurrentContext();
    SDL_Window *current_window = SDL_GL_GetCurrentWindow();

    SDL_GL_MakeCurrent(عدم, عدم);
    Wayland_VideoCleanup(_this);

    SDL_ResetKeyboard();
    SDL_ResetMouse();
    إذا (WAYLAND_wl_display_reconnect(data->display) < 0) {
        إرجاع false;
    }

    Wayland_VideoInit(_this);

    window = _this->windows;
    بينما (window) {
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

    إذا (current_window && current_ctx) {
        SDL_GL_MakeCurrent (current_window, current_ctx);
    }
    إرجاع true;
#وإلا
    إرجاع false;
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
    إذا (video_data->display_disconnected) {
        إرجاع false;
    }

    إذا (Wayland_VideoReconnect(_this)) {
        إرجاع true;
    }

    video_data->display_disconnected = true;
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Wayland display connection closed by server (fatal)");

    // Only send a single quit message, as application shutdown might call SDL_PumpEvents().
    SDL_SendQuit();

    إرجاع false;
}

فراغ Wayland_VideoQuit(SDL_VideoDevice *_this)
{
    Wayland_VideoCleanup(_this);

#ifdef HAVE_LIBDECOR_H
    SDL_VideoData *data = _this->internal;
    إذا (data->shell.libdecor) {
        libdecor_unref(data->shell.libdecor);
        data->shell.libdecor = عدم;
    }
#endif
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
