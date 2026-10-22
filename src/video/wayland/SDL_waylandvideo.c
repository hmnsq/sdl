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

#ifdef SDL_VIDEO_DRIVER_WAYLAND

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

#ifdef HAVE_LIBDECOR_H
#अन्तर्भाव <libdecor.h>
#endif

#define WAYLANDVID_DRIVER_NAME "wayland"

// Clamp core protocol versions on older versions of libwayland.
#यदि SDL_WAYLAND_CHECK_VERSION(1, 22, 0)
#define SDL_WL_COMPOSITOR_VERSION 6
#अन्यथा
#define SDL_WL_COMPOSITOR_VERSION 4
#endif

#यदि SDL_WAYLAND_CHECK_VERSION(1, 26, 0)
#define SDL_WL_SEAT_VERSION 11
#नोचेद्यदि SDL_WAYLAND_CHECK_VERSION(1, 24, 0)
#define SDL_WL_SEAT_VERSION 10
#नोचेद्यदि SDL_WAYLAND_CHECK_VERSION(1, 22, 0)
#define SDL_WL_SEAT_VERSION 9
#नोचेद्यदि SDL_WAYLAND_CHECK_VERSION(1, 21, 0)
#define SDL_WL_SEAT_VERSION 8
#अन्यथा
#define SDL_WL_SEAT_VERSION 5
#endif

#यदि SDL_WAYLAND_CHECK_VERSION(1, 20, 0)
#define SDL_WL_OUTPUT_VERSION 4
#अन्यथा
#define SDL_WL_OUTPUT_VERSION 3
#endif

#यदि SDL_WAYLAND_CHECK_VERSION(1, 24, 0)
#define SDL_WL_SHM_VERSION 2
#अन्यथा
#define SDL_WL_SHM_VERSION 1
#endif

// The SDL libwayland-client minimum is 1.18, which supports version 3.
#define SDL_WL_DATA_DEVICE_VERSION 3

// wl_fixes was introduced in 1.24.0
#यदि SDL_WAYLAND_CHECK_VERSION(1, 26, 0)
#define SDL_WL_FIXES_VERSION 2
#नोचेद्यदि SDL_WAYLAND_CHECK_VERSION(1, 24, 0)
#define SDL_WL_FIXES_VERSION 1
#endif

#ifdef SDL_USE_LIBDBUS
#अन्तर्भाव "../../core/linux/SDL_dbus.h"

#define DISPLAY_INFO_गाँठ   "org.gnome.Mutter.DisplayConfig"
#define DISPLAY_INFO_PATH   "/org/gnome/Mutter/DisplayConfig"
#define DISPLAY_INFO_METHOD "GetCurrentState"
#endif

/* GNOME doesn't expose displays in any particular order, but we can find the
 * primary display and its logical coordinates via a DBus method.
 */
स्थिर bool Wayland_GetGNOMEPrimaryDisplayCoordinates(पूर्णाङ्क *x, पूर्णाङ्क *y)
{
#ifdef SDL_USE_LIBDBUS
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    यदि (dbus == रिक्त) {
        प्रत्यागम false;
    }
    DBusMessage *reply = रिक्त;
    DBusMessageIter iter[3];
    DBusMessage *संदेश = dbus->message_new_method_call(DISPLAY_INFO_गाँठ,
                                                     DISPLAY_INFO_PATH,
                                                     DISPLAY_INFO_गाँठ,
                                                     DISPLAY_INFO_METHOD);

    यदि (संदेश) {
        reply = dbus->connection_send_with_reply_and_block(dbus->session_conn, संदेश, DBUS_TIMEOUT_USE_DEFAULT, रिक्त);
        dbus->message_unref(संदेश);
    }

    यदि (reply) {
        // Serial (don't care)
        dbus->message_iter_init(reply, &iter[0]);
        यदि (dbus->message_iter_get_arg_type(&iter[0]) != DBUS_TYPE_UINT32) {
            गच्छ error;
        }

        // Physical monitor array (don't care)
        dbus->message_iter_next(&iter[0]);
        यदि (dbus->message_iter_get_arg_type(&iter[0]) != DBUS_TYPE_ARRAY) {
            गच्छ error;
        }

        // Logical monitor array of structs
        dbus->message_iter_next(&iter[0]);
        यदि (dbus->message_iter_get_arg_type(&iter[0]) != DBUS_TYPE_ARRAY) {
            गच्छ error;
        }

        // First logical monitor struct
        dbus->message_iter_recurse(&iter[0], &iter[1]);
        यदि (dbus->message_iter_get_arg_type(&iter[1]) != DBUS_TYPE_STRUCT) {
            गच्छ error;
        }

        कुरु {
            पूर्णाङ्क logical_x, logical_y;
            dbus_bool_t primary;

            // Logical X
            dbus->message_iter_recurse(&iter[1], &iter[2]);
            यदि (dbus->message_iter_get_arg_type(&iter[2]) != DBUS_TYPE_INT32) {
                गच्छ error;
            }
            dbus->message_iter_get_basic(&iter[2], &logical_x);

            // Logical Y
            dbus->message_iter_next(&iter[2]);
            यदि (dbus->message_iter_get_arg_type(&iter[2]) != DBUS_TYPE_INT32) {
                गच्छ error;
            }
            dbus->message_iter_get_basic(&iter[2], &logical_y);

            // Scale (don't care)
            dbus->message_iter_next(&iter[2]);
            यदि (dbus->message_iter_get_arg_type(&iter[2]) != DBUS_TYPE_DOUBLE) {
                गच्छ error;
            }

            // Transform (don't care)
            dbus->message_iter_next(&iter[2]);
            यदि (dbus->message_iter_get_arg_type(&iter[2]) != DBUS_TYPE_UINT32) {
                गच्छ error;
            }

            // Primary display boolean
            dbus->message_iter_next(&iter[2]);
            यदि (dbus->message_iter_get_arg_type(&iter[2]) != DBUS_TYPE_BOOLEAN) {
                गच्छ error;
            }
            dbus->message_iter_get_basic(&iter[2], &primary);

            यदि (primary) {
                *x = logical_x;
                *y = logical_y;

                // We found the primary display: success.
                dbus->message_unref(reply);
                प्रत्यागम true;
            }
        } यावत् (dbus->message_iter_next(&iter[1]));
    }

error:
    यदि (reply) {
        dbus->message_unref(reply);
    }
#endif
    प्रत्यागम false;
}

// Sort the list of displays into a deterministic order
स्थिर पूर्णाङ्क SDLCALL Wayland_DisplayPositionCompare(ध्रुव शून्य *a, ध्रुव शून्य *b)
{
    ध्रुव SDL_DisplayData *da = *(SDL_DisplayData **)a;
    ध्रुव SDL_DisplayData *db = *(SDL_DisplayData **)b;
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
स्थिर पूर्णाङ्क Wayland_GetPrimaryDisplay(SDL_VideoData *vid)
{
    स्थिर ध्रुव पूर्णाङ्क REFRESH_DELTA = 4000;

    // Query the DBus interface to see if the coordinates of the primary display are exposed.
    पूर्णाङ्क x, y;
    यदि (Wayland_GetGNOMEPrimaryDisplayCoordinates(&x, &y)) {
        प्रति (पूर्णाङ्क i = 0; i < vid->output_गिनती; ++i) {
            यदि (vid->output_list[i]->logical.x == x && vid->output_list[i]->logical.y == y) {
                प्रत्यागम i;
            }
        }
    }

    // Otherwise, choose the 'best' display.
    पूर्णाङ्क best_width = 0;
    पूर्णाङ्क best_height = 0;
    द्विगुण best_scale = 0.0;
    भिन्न best_headroom = 0.0f;
    पूर्णाङ्क best_refresh = 0;
    bool best_is_landscape = false;
    पूर्णाङ्क best_index = 0;

    प्रति (पूर्णाङ्क i = 0; i < vid->output_गिनती; ++i) {
        ध्रुव SDL_DisplayData *d = vid->output_list[i];
        ध्रुव bool is_landscape = d->orientation != SDL_ORIENTATION_PORTRAIT && d->orientation != SDL_ORIENTATION_PORTRAIT_FLIPPED;
        bool have_new_best = false;

        यदि (!best_is_landscape && is_landscape) { // Favor landscape over portrait displays.
            have_new_best = true;
        } अन्यथा यदि (!best_is_landscape || is_landscape) { // Ignore portrait displays if a landscape was already found.
            यदि (d->pixel.width > best_width || d->pixel.height > best_height) {
                have_new_best = true;
            } अन्यथा यदि (d->pixel.width == best_width && d->pixel.height == best_height) {
                यदि (d->HDR.HDR_headroom > best_headroom) { // Favor a higher HDR luminance range
                    have_new_best = true;
                } अन्यथा यदि (d->HDR.HDR_headroom == best_headroom) {
                    यदि (d->refresh - best_refresh > REFRESH_DELTA) { // Favor a higher refresh rate, but ignore small differences (e.g. 59.97 vs 60.1)
                        have_new_best = true;
                    } अन्यथा यदि (d->scale_factor < best_scale && SDL_abs(d->refresh - best_refresh) <= REFRESH_DELTA) {
                        // Prefer a lower scale display if the difference in refresh rate is small.
                        have_new_best = true;
                    }
                }
            }
        }

        यदि (have_new_best) {
            best_width = d->pixel.width;
            best_height = d->pixel.height;
            best_scale = d->scale_factor;
            best_headroom = d->HDR.HDR_headroom;
            best_refresh = d->refresh;
            best_is_landscape = is_landscape;
            best_index = i;
        }
    }

    प्रत्यागम best_index;
}

स्थिर शून्य Wayland_SortOutputsByPriorityHint(SDL_VideoData *vid)
{
    ध्रुव वर्ण *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_PRIORITY);

    यदि (name_hint) {
        वर्ण *saveptr;
        वर्ण *str = SDL_strdup(name_hint);
        SDL_DisplayData **sorted_list = SDL_malloc(परिमाण(SDL_DisplayData *) * vid->output_गिनती);

        यदि (str && sorted_list) {
            पूर्णाङ्क sorted_index = 0;

            // Sort the requested displays to the front of the list.
            ध्रुव वर्ण *token = SDL_strtok_r(str, ",", &saveptr);
            यावत् (token) {
                प्रति (पूर्णाङ्क i = 0; i < vid->output_गिनती; ++i) {
                    SDL_DisplayData *d = vid->output_list[i];
                    यदि (d && d->wl_output_name && SDL_strcmp(token, d->wl_output_name) == 0) {
                        sorted_list[sorted_index++] = d;
                        vid->output_list[i] = रिक्त;
                        भङ्ग;
                    }
                }

                token = SDL_strtok_r(रिक्त, ",", &saveptr);
            }

            // Append the remaining outputs to the end of the list.
            प्रति (पूर्णाङ्क i = 0; i < vid->output_गिनती; ++i) {
                यदि (vid->output_list[i]) {
                    sorted_list[sorted_index++] = vid->output_list[i];
                }
            }

            // Copy the sorted list to the output list.
            SDL_memcpy(vid->output_list, sorted_list, परिमाण(SDL_DisplayData *) * vid->output_गिनती);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

स्थिर शून्य Wayland_DeriveOutputPixelCoordinates(SDL_VideoData *vid)
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
    प्रति ( पूर्णाङ्क i = 0; i < vid->output_गिनती; ++i) {
        SDL_DisplayData *d = vid->output_list[i];
        d->pixel.x = d->logical.x;
        d->pixel.y = d->logical.y;
    }

    प्रति (पूर्णाङ्क i = 0; i < vid->output_गिनती; ++i) {
        SDL_DisplayData *d1 = vid->output_list[i];
        यदि (d1->logical.width != d1->pixel.width || d1->logical.height != d1->pixel.height) {
            ध्रुव पूर्णाङ्क x_adj = d1->pixel.width - d1->logical.width;
            ध्रुव पूर्णाङ्क y_adj = d1->pixel.height - d1->logical.height;

            // Don't adjust for scale values less than 1.0.
            यदि (x_adj > 0 && y_adj > 0) {
                प्रति (पूर्णाङ्क j = 0; j < vid->output_गिनती; ++j) {
                    SDL_DisplayData *d2 = vid->output_list[j];
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

स्थिर शून्य Wayland_SortOutputs(SDL_VideoData *vid)
{
    // Sort by position or connector name, so the order of outputs is deterministic.
    SDL_qsort(vid->output_list, vid->output_गिनती, परिमाण(SDL_DisplayData *), Wayland_DisplayPositionCompare);

    // Derive the output pixel coordinates if scale to display is enabled.
    यदि (vid->scale_to_display_enabled) {
        Wayland_DeriveOutputPixelCoordinates(vid);
    }

    // Find a suitable primary display and move it to the front of the list.
    ध्रुव पूर्णाङ्क primary_index = Wayland_GetPrimaryDisplay(vid);
    यदि (primary_index) {
        SDL_DisplayData *primary = vid->output_list[primary_index];
        SDL_memmove(&vid->output_list[1], &vid->output_list[0], परिमाण(SDL_DisplayData *) * primary_index);
        vid->output_list[0] = primary;
    }

    // Apply the ordering hint, if specified.
    Wayland_SortOutputsByPriorityHint(vid);
}

स्थिर शून्य Wayland_RefreshWindowPositions()
{
    SDL_VideoDevice *vid = SDL_GetVideoDevice();

    प्रति (SDL_Window *w = vid->windows; w; w = w->next) {
        Wayland_UpdateWindowPosition(w);
    }
}

स्थिर शून्य handle_wl_output_done(शून्य *data, संरचना wl_output *output);

// Initialization/Query functions
स्थिर bool Wayland_VideoInit(SDL_VideoDevice *_this);
स्थिर bool Wayland_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
स्थिर शून्य Wayland_VideoQuit(SDL_VideoDevice *_this);

स्थिर ध्रुव वर्ण *SDL_WAYLAND_surface_tag = "sdl-window";
स्थिर ध्रुव वर्ण *SDL_WAYLAND_output_tag = "sdl-output";

शून्य SDL_WAYLAND_register_surface(संरचना wl_surface *surface)
{
    wl_proxy_set_tag((संरचना wl_proxy *)surface, &SDL_WAYLAND_surface_tag);
}

शून्य SDL_WAYLAND_register_output(संरचना wl_output *output)
{
    wl_proxy_set_tag((संरचना wl_proxy *)output, &SDL_WAYLAND_output_tag);
}

bool SDL_WAYLAND_own_surface(संरचना wl_surface *surface)
{
    प्रत्यागम wl_proxy_get_tag((संरचना wl_proxy *)surface) == &SDL_WAYLAND_surface_tag;
}

bool SDL_WAYLAND_own_output(संरचना wl_output *output)
{
    प्रत्यागम wl_proxy_get_tag((संरचना wl_proxy *)output) == &SDL_WAYLAND_output_tag;
}

/* External surfaces may have their own user data attached, the modification of which
 * can cause problems with external toolkits. Instead, external windows are kept in
 * their own list, and a search is conducted to find a matching surface.
 */
स्थिर संरचना wl_list external_window_list;

शून्य Wayland_AddWindowDataToExternalList(SDL_WindowData *data)
{
    WAYLAND_wl_list_जोड़ो(&external_window_list, &data->external_window_list_link);
}

शून्य Wayland_RemoveWindowDataFromExternalList(SDL_WindowData *data)
{
    WAYLAND_wl_list_remove(&data->external_window_list_link);
}

SDL_WindowData *Wayland_GetWindowDataForOwnedSurface(संरचना wl_surface *surface)
{
    यदि (SDL_WAYLAND_own_surface(surface)) {
        प्रत्यागम (SDL_WindowData *)wl_surface_get_user_data(surface);
    } अन्यथा यदि (!WAYLAND_wl_list_empty(&external_window_list)) {
        SDL_WindowData *p;
        wl_list_for_each (p, &external_window_list, external_window_list_link) {
            यदि (p->surface == surface) {
                प्रत्यागम p;
            }
        }
    }

    प्रत्यागम रिक्त;
}

संरचना wl_event_queue *Wayland_DisplayCreateQueue(संरचना wl_display *display, ध्रुव वर्ण *name)
{
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
    यदि (WAYLAND_wl_display_create_queue_with_name) {
        प्रत्यागम WAYLAND_wl_display_create_queue_with_name(display, name);
    }
#नोचेद्यदि SDL_WAYLAND_CHECK_VERSION(1, 23, 0)
    प्रत्यागम WAYLAND_wl_display_create_queue_with_name(display, name);
#endif
    प्रत्यागम WAYLAND_wl_display_create_queue(display);
}

स्थिर शून्य Wayland_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_VideoData *data = device->internal;
    यदि (data->display && !data->display_externally_owned) {
        WAYLAND_wl_display_disconnect(data->display);
        SDL_ClearProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_POINTER);
    }
    SDL_free(data);
    SDL_free(device);
    SDL_WAYLAND_UnloadSymbols();
}

प्रकारनिर्देश संरचना
{
    bool has_fifo_v1;
    संरचना wl_fixes *wl_fixes;
} SDL_WaylandPreferredData;

स्थिर शून्य wayland_preferred_check_handle_global(शून्य *data, संरचना wl_registry *registry, uint32_t id,
                                                  ध्रुव वर्ण *interface, uint32_t version)
{
    SDL_WaylandPreferredData *d = data;

    यदि (SDL_strcmp(interface, "wp_fifo_manager_v1") == 0) {
        d->has_fifo_v1 = true;
    }
#ifdef SDL_WL_FIXES_VERSION
    अन्यथा यदि (SDL_strcmp(interface, wl_fixes_interface.name) == 0) {
        d->wl_fixes = wl_registry_bind(registry, id, &wl_fixes_interface, SDL_min(SDL_WL_FIXES_VERSION, version));
    }
#endif
}

स्थिर शून्य wayland_preferred_check_remove_global(शून्य *data, संरचना wl_registry *registry, uint32_t id)
{
    SDL_WaylandPreferredData *d = (SDL_WaylandPreferredData *)data;

    यदि (d->wl_fixes && wl_fixes_get_version(d->wl_fixes) >= WL_FIXES_ACK_GLOBAL_REMOVE_SINCE_VERSION) {
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
    SDL_WaylandPreferredData preferred_data = { 0 };

    यदि (!registry) {
        SDL_SetError("Failed to get the Wayland registry");
        प्रत्यागम false;
    }

    wl_registry_add_listener(registry, &preferred_registry_listener, &preferred_data);

    WAYLAND_wl_display_roundtrip(display);

    यदि (preferred_data.wl_fixes) {
        wl_fixes_destroy_registry(preferred_data.wl_fixes, registry);
        wl_fixes_destroy(preferred_data.wl_fixes);
    }
    wl_registry_destroy(registry);

    यदि (!preferred_data.has_fifo_v1) {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "This compositor lacks support for the fifo-v1 protocol; falling back to XWayland for GPU performance reasons (set SDL_VIDEO_DRIVER=wayland to override)");
    }
    प्रत्यागम preferred_data.has_fifo_v1;
}

स्थिर SDL_VideoDevice *Wayland_CreateDevice(bool require_preferred_protocols)
{
    SDL_VideoDevice *device;
    SDL_VideoData *data;
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

    यदि (!SDL_WAYLAND_LoadSymbols()) {
        प्रत्यागम रिक्त;
    }

    यदि (!display) {
        display = WAYLAND_wl_display_connect(रिक्त);
        यदि (!display) {
            SDL_WAYLAND_UnloadSymbols();
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to connect to the Wayland display server: %s", म_त्रुटि(त्रुटि_सं));
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

    data = SDL_calloc(1, परिमाण(*data));
    यदि (!data) {
        यदि (!display_is_external) {
            WAYLAND_wl_display_disconnect(display);
        }
        SDL_WAYLAND_UnloadSymbols();
        प्रत्यागम रिक्त;
    }

    data->initializing = true;
    data->display = display;
    data->display_externally_owned = display_is_external;
    data->scale_to_display_enabled = SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_SCALE_TO_DISPLAY, false);
    WAYLAND_wl_list_init(&data->seat_list);
    WAYLAND_wl_list_init(&external_window_list);

    // Initialize all variables that we clean on shutdown
    device = SDL_calloc(1, परिमाण(SDL_VideoDevice));
    यदि (!device) {
        SDL_free(data);
        यदि (!display_is_external) {
            WAYLAND_wl_display_disconnect(display);
        }
        SDL_WAYLAND_UnloadSymbols();
        प्रत्यागम रिक्त;
    }

    यदि (!display_is_external) {
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
    यदि (SDL_SystemTheme_Init())
        device->system_theme = SDL_SystemTheme_Get();
#endif

    device->GetTextMimeTypes = Wayland_GetTextMimeTypes;
    device->SetClipboardData = Wayland_SetClipboardData;
    device->GetClipboardData = Wayland_GetClipboardData;
    device->HasClipboardData = Wayland_HasClipboardData;
    device->Start_Text_निवेश = Wayland_Start_Text_निवेश;
    device->Stop_Text_निवेश = Wayland_Stop_Text_निवेश;
    device->Update_Text_निवेश_Area = Wayland_Update_Text_निवेश_Area;

#ifdef SDL_VIDEO_VULKAN
    device->Vulkan_LoadLibrary = Wayland_Vulkan_LoadLibrary;
    device->Vulkan_UnloadLibrary = Wayland_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = Wayland_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = Wayland_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = Wayland_Vulkan_DestroySurface;
    device->Vulkan_GetPresentationSupport = Wayland_Vulkan_GetPresentationSupport;
#endif

    device->मुक्त = Wayland_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_MODE_SWITCHING_EMULATED |
                          VIDEO_DEVICE_CAPS_HAS_POPUP_WINDOW_SUPPORT |
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
    Wayland_ShowMessageBox,
    true
};

VideoBootStrap Wayland_bootstrap = {
    WAYLANDVID_DRIVER_NAME, "SDL Wayland video driver",
    Wayland_Fallback_CreateDevice,
    Wayland_ShowMessageBox,
    false
};

स्थिर शून्य handle_xdg_output_logical_position(शून्य *data, संरचना zxdg_output_v1 *xdg_output, int32_t x, int32_t y)
{
    SDL_DisplayData *internal = (SDL_DisplayData *)data;

    internal->geometry_changed |= internal->logical.x != x || internal->logical.y != y;
    internal->logical.x = x;
    internal->logical.y = y;
    internal->has_logical_position = true;
}

स्थिर शून्य handle_xdg_output_logical_size(शून्य *data, संरचना zxdg_output_v1 *xdg_output, int32_t width, int32_t height)
{
    SDL_DisplayData *internal = (SDL_DisplayData *)data;

    internal->geometry_changed |= internal->logical.width != width || internal->logical.height != height;
    internal->logical.width = width;
    internal->logical.height = height;
    internal->has_logical_size = true;
}

स्थिर शून्य handle_xdg_output_done(शून्य *data, संरचना zxdg_output_v1 *xdg_output)
{
    SDL_DisplayData *internal = data;

    /*
     * xdg-output.done events are deprecated and only apply below version 3 of the protocol.
     * A wl-output.done event will be emitted in version 3 or higher.
     */
    यदि (zxdg_output_v1_get_version(internal->xdg_output) < 3) {
        handle_wl_output_done(data, internal->output);
    }
}

स्थिर शून्य handle_xdg_output_name(शून्य *data, संरचना zxdg_output_v1 *xdg_output, ध्रुव वर्ण *name)
{
    SDL_DisplayData *internal = (SDL_DisplayData *)data;

    // Deprecated as of wl_output v4.
    यदि (wl_output_get_version(internal->output) < WL_OUTPUT_NAME_SINCE_VERSION &&
        internal->display == 0) {
        SDL_free(internal->wl_output_name);
        internal->wl_output_name = SDL_strdup(name);
    }
}

स्थिर शून्य handle_xdg_output_description(शून्य *data, संरचना zxdg_output_v1 *xdg_output, ध्रुव वर्ण *description)
{
    SDL_DisplayData *internal = (SDL_DisplayData *)data;

    // Deprecated as of wl_output v4.
    यदि (wl_output_get_version(internal->output) < WL_OUTPUT_DESCRIPTION_SINCE_VERSION &&
        internal->display == 0) {
        // xdg-output descriptions, if available, supersede wl-output model names.
        SDL_free(internal->placeholder.name);
        internal->placeholder.name = SDL_strdup(description);
    }
}

स्थिर ध्रुव संरचना zxdg_output_v1_listener xdg_output_listener = {
    handle_xdg_output_logical_position,
    handle_xdg_output_logical_size,
    handle_xdg_output_done,
    handle_xdg_output_name,
    handle_xdg_output_description,
};

स्थिर शून्य AddEmulatedModes(SDL_DisplayData *dispdata, पूर्णाङ्क native_width, पूर्णाङ्क native_height)
{
    संरचना EmulatedMode
    {
        पूर्णाङ्क w;
        पूर्णाङ्क h;
    };

    // Resolution lists courtesy of XWayland
    ध्रुव संरचना EmulatedMode mode_list[] = {
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
    SDL_DisplayMode mode;
    SDL_VideoDisplay *dpy = dispdata->display ? SDL_GetVideoDisplay(dispdata->display) : &dispdata->placeholder;
    ध्रुव bool rot_90 = native_width < native_height; // Reverse width/height for portrait displays.

    प्रति (i = 0; i < SDL_arraysize(mode_list); ++i) {
        SDL_zero(mode);
        mode.format = dpy->desktop_mode.format;
        mode.refresh_rate_numerator = dpy->desktop_mode.refresh_rate_numerator;
        mode.refresh_rate_denominator = dpy->desktop_mode.refresh_rate_denominator;

        यदि (rot_90) {
            mode.w = mode_list[i].h;
            mode.h = mode_list[i].w;
        } अन्यथा {
            mode.w = mode_list[i].w;
            mode.h = mode_list[i].h;
        }

        // Only add modes that are smaller than the native mode.
        यदि ((mode.w < native_width && mode.h < native_height) ||
            (mode.w < native_width && mode.h == native_height) ||
            (mode.w == native_width && mode.h < native_height)) {
            SDL_AddFullscreenDisplayMode(dpy, &mode);
        }
    }
}

स्थिर शून्य handle_wl_output_geometry(शून्य *data, संरचना wl_output *output, पूर्णाङ्क x, पूर्णाङ्क y,
                                      पूर्णाङ्क physical_width, पूर्णाङ्क physical_height, पूर्णाङ्क subpixel,
                                      ध्रुव वर्ण *make, ध्रुव वर्ण *model, पूर्णाङ्क transform)
{
    SDL_DisplayData *internal = (SDL_DisplayData *)data;

    // Apply the change from wl-output only if xdg-output is not supported
    यदि (!internal->has_logical_position) {
        internal->geometry_changed |= internal->logical.x != x || internal->logical.y != y;
        internal->logical.x = x;
        internal->logical.y = y;
    }
    internal->physical.width_mm = physical_width;
    internal->physical.height_mm = physical_height;

    // The model is only used for the output name if wl_output or xdg-output haven't provided a description.
    यदि (internal->display == 0 && !internal->placeholder.name) {
        internal->placeholder.name = SDL_strdup(model);
    }

    internal->transform = transform;
#define TF_CASE(in, out)                                 \
    पक्ष WL_OUTPUT_TRANSFORM_##in:                       \
        internal->orientation = SDL_ORIENTATION_##out; \
        भङ्ग;
    यदि (internal->physical.width_mm >= internal->physical.height_mm) {
        विकल्प (transform) {
            TF_CASE(NORMAL, LANDSCAPE)
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

स्थिर शून्य handle_wl_output_mode(शून्य *data, संरचना wl_output *output, uint32_t flags,
                                  पूर्णाङ्क width, पूर्णाङ्क height, पूर्णाङ्क refresh)
{
    SDL_DisplayData *internal = (SDL_DisplayData *)data;

    यदि (flags & WL_OUTPUT_MODE_CURRENT) {
        internal->geometry_changed |= internal->pixel.width != width || internal->pixel.height != height;
        internal->pixel.width = width;
        internal->pixel.height = height;

        /*
         * Don't rotate this yet, wl-output coordinates are transformed in
         * handle_done and xdg-output coordinates are pre-transformed.
         */
        यदि (!internal->has_logical_size) {
            internal->geometry_changed |= internal->logical.width != width || internal->logical.height != height;
            internal->logical.width = width;
            internal->logical.height = height;
        }

        internal->refresh = refresh;
    }
}

स्थिर शून्य handle_wl_output_done(शून्य *data, संरचना wl_output *output)
{
    ध्रुव bool mode_emulation_enabled = SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_MODE_EMULATION, true);
    SDL_DisplayData *internal = (SDL_DisplayData *)data;
    SDL_VideoData *video = internal->videodata;
    SDL_DisplayMode native_mode, desktop_mode;

    /*
     * When using xdg-output, two wl-output.done events will be emitted:
     * one at the completion of wl-display and one at the completion of xdg-output.
     *
     * All required events must be received before proceeding.
     */
    ध्रुव पूर्णाङ्क event_await_गिनती = 1 + (internal->xdg_output != रिक्त);

    internal->wl_output_done_गिनती = SDL_min(internal->wl_output_done_गिनती + 1, event_await_गिनती + 1);

    यदि (internal->wl_output_done_गिनती < event_await_गिनती) {
        प्रत्यागम;
    }

    // If the display was already created, reset and rebuild the mode list.
    SDL_VideoDisplay *dpy = SDL_GetVideoDisplay(internal->display);
    यदि (dpy) {
        SDL_ResetFullscreenDisplayModes(dpy);
    }

    // The native display resolution
    SDL_zero(native_mode);
    native_mode.format = SDL_PIXELFORMAT_XRGB8888;

    // Transform the pixel values, if necessary.
    यदि (internal->transform & WL_OUTPUT_TRANSFORM_90) {
        native_mode.w = internal->pixel.height;
        native_mode.h = internal->pixel.width;
    } अन्यथा {
        native_mode.w = internal->pixel.width;
        native_mode.h = internal->pixel.height;
    }
    native_mode.refresh_rate_numerator = internal->refresh;
    native_mode.refresh_rate_denominator = 1000;

    यदि (internal->has_logical_size) { // If xdg-output is present...
        यदि (native_mode.w != internal->logical.width || native_mode.h != internal->logical.height) {
            // ...and the compositor scales the logical viewport...
            यदि (video->viewporter) {
                // ...and viewports are supported, calculate the true scale of the output.
                internal->scale_factor = (द्विगुण)native_mode.w / (द्विगुण)internal->logical.width;
            } अन्यथा {
                // ...otherwise, the 'native' pixel values are a multiple of the logical screen size.
                internal->scale_factor = internal->integer_scale_factor;
                internal->pixel.width = internal->logical.width * internal->integer_scale_factor;
                internal->pixel.height = internal->logical.height * internal->integer_scale_factor;
            }
        } अन्यथा {
            /* ...and the output viewport is not scaled in the global compositing
             * space, the output dimensions need to be divided by the scale factor.
             *
             * NOTE: This path is needed for old versions of GNOME that predate fractional scaling.
             */
            internal->scale_factor = internal->integer_scale_factor;
            internal->logical.width /= internal->integer_scale_factor;
            internal->logical.height /= internal->integer_scale_factor;
        }
    } अन्यथा {
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

    यदि (!video->scale_to_display_enabled) {
        desktop_mode.w = internal->logical.width;
        desktop_mode.h = internal->logical.height;
        desktop_mode.pixel_density = (भिन्न)internal->scale_factor;
    } अन्यथा {
        desktop_mode.w = native_mode.w;
        desktop_mode.h = native_mode.h;
        desktop_mode.pixel_density = 1.0f;
    }

    desktop_mode.refresh_rate_numerator = internal->refresh;
    desktop_mode.refresh_rate_denominator = 1000;

    यदि (internal->display > 0) {
        dpy = SDL_GetVideoDisplay(internal->display);
    } अन्यथा {
        dpy = &internal->placeholder;
    }

    यदि (video->scale_to_display_enabled) {
        SDL_SetDisplayContentScale(dpy, (भिन्न)internal->scale_factor);
    }

    // Set the desktop display mode.
    SDL_SetDesktopDisplayMode(dpy, &desktop_mode);

    // Expose the unscaled, native resolution if the scale is 1.0 or viewports are available...
    यदि (internal->scale_factor == 1.0 || video->viewporter) {
        SDL_AddFullscreenDisplayMode(dpy, &native_mode);
        यदि (native_mode.w != desktop_mode.w ||
            native_mode.h != desktop_mode.h) {
            SDL_AddFullscreenDisplayMode(dpy, &desktop_mode);
        }
    } अन्यथा {
        // ...otherwise expose the integer scaled variants of the desktop resolution down to 1.
        desktop_mode.pixel_density = 1.0f;

        प्रति (पूर्णाङ्क i = (पूर्णाङ्क)internal->scale_factor; i > 0; --i) {
            desktop_mode.w = internal->logical.width * i;
            desktop_mode.h = internal->logical.height * i;
            SDL_AddFullscreenDisplayMode(dpy, &desktop_mode);
        }
    }

    // Add emulated modes if wp_viewporter is supported and mode emulation is enabled.
    यदि (video->viewporter && mode_emulation_enabled) {
        // The transformed display pixel width/height must be used here.
        AddEmulatedModes(internal, native_mode.w, native_mode.h);
    }

    यदि (internal->display == 0) {
        // First time getting display info, initialize the VideoDisplay
        यदि (internal->physical.width_mm >= internal->physical.height_mm) {
            internal->placeholder.natural_orientation = SDL_ORIENTATION_LANDSCAPE;
        } अन्यथा {
            internal->placeholder.natural_orientation = SDL_ORIENTATION_PORTRAIT;
        }
        internal->placeholder.current_orientation = internal->orientation;
        internal->placeholder.internal = internal;

        internal->placeholder.props = SDL_CreateProperties();
        SDL_SetPointerProperty(internal->placeholder.props, SDL_PROP_DISPLAY_WAYLAND_WL_OUTPUT_POINTER, internal->output);

        // During initialization, the displays will be added after enumeration is complete.
        यदि (!video->initializing) {
            यदि (video->wp_color_manager_v1) {
                Wayland_GetColorInfoForOutput(internal, false);
            }
            यदि (video->scale_to_display_enabled) {
                Wayland_DeriveOutputPixelCoordinates(video);
            }

            internal->display = SDL_AddVideoDisplay(&internal->placeholder, true);
            Wayland_RefreshWindowPositions();

            SDL_free(internal->placeholder.name);
            SDL_zero(internal->placeholder);
        }
    } अन्यथा {
        SDL_SendDisplayEvent(dpy, SDL_EVENT_DISPLAY_ORIENTATION, internal->orientation, 0);

        यदि (internal->geometry_changed) {
            यदि (video->scale_to_display_enabled) {
                Wayland_DeriveOutputPixelCoordinates(video);
            }

            SDL_SendDisplayEvent(dpy, SDL_EVENT_DISPLAY_MOVED, 0, 0);
            Wayland_RefreshWindowPositions();
        }
    }

    internal->geometry_changed = false;
}

स्थिर शून्य handle_wl_output_scale(शून्य *data, संरचना wl_output *output, int32_t factor)
{
    SDL_DisplayData *internal = (SDL_DisplayData *)data;
    internal->integer_scale_factor = factor;
}

स्थिर शून्य handle_wl_output_name(शून्य *data, संरचना wl_output *wl_output, ध्रुव वर्ण *name)
{
    SDL_DisplayData *internal = (SDL_DisplayData *)data;

    SDL_free(internal->wl_output_name);
    internal->wl_output_name = SDL_strdup(name);
}

स्थिर शून्य handle_wl_output_description(शून्य *data, संरचना wl_output *wl_output, ध्रुव वर्ण *description)
{
    SDL_DisplayData *internal = (SDL_DisplayData *)data;

    यदि (internal->display == 0) {
        // The description, if available, supersedes the model name.
        SDL_free(internal->placeholder.name);
        internal->placeholder.name = SDL_strdup(description);
    }
}

स्थिर ध्रुव संरचना wl_output_listener output_listener = {
    handle_wl_output_geometry,   // Version 1
    handle_wl_output_mode,       // Version 1
    handle_wl_output_done,       // Version 2
    handle_wl_output_scale,      // Version 2
    handle_wl_output_name,       // Version 4
    handle_wl_output_description // Version 4
};

स्थिर शून्य handle_output_image_description_changed(शून्य *data,
                                                    संरचना wp_color_management_output_v1 *wp_color_management_output_v1)
{
    SDL_DisplayData *display = (SDL_DisplayData *)data;
    Wayland_GetColorInfoForOutput(display, false);
}

स्थिर ध्रुव संरचना wp_color_management_output_v1_listener wp_color_management_output_listener = {
    handle_output_image_description_changed
};

स्थिर bool Wayland_add_display(SDL_VideoData *d, uint32_t id, uint32_t version)
{
    संरचना wl_output *output;
    SDL_DisplayData *data;

    output = wl_registry_bind(d->registry, id, &wl_output_interface, version);
    यदि (!output) {
        प्रत्यागम SDL_SetError("Failed to retrieve output.");
    }
    data = (SDL_DisplayData *)SDL_calloc(1, परिमाण(*data));
    data->videodata = d;
    data->output = output;
    data->registry_id = id;
    data->scale_factor = 1.0f;
    data->integer_scale_factor = 1;

    wl_output_add_listener(output, &output_listener, data);
    SDL_WAYLAND_register_output(output);

    // Keep a list of outputs for sorting and deferred protocol initialization.
    यदि (d->output_गिनती == d->output_max) {
        d->output_max += 4;
        d->output_list = SDL_realloc(d->output_list, परिमाण(SDL_DisplayData *) * d->output_max);
    }
    d->output_list[d->output_गिनती++] = data;

    यदि (data->videodata->xdg_output_manager) {
        data->xdg_output = zxdg_output_manager_v1_get_xdg_output(data->videodata->xdg_output_manager, output);
        zxdg_output_v1_add_listener(data->xdg_output, &xdg_output_listener, data);
    }
    यदि (data->videodata->wp_color_manager_v1) {
        data->wp_color_management_output = wp_color_manager_v1_get_output(data->videodata->wp_color_manager_v1, output);
        wp_color_management_output_v1_add_listener(data->wp_color_management_output, &wp_color_management_output_listener, data);

        // If not initializing, this will be queried synchronously in wl_output.done.
        यदि (d->initializing) {
            Wayland_GetColorInfoForOutput(data, true);
        }
    }
    प्रत्यागम true;
}

स्थिर शून्य Wayland_free_display(SDL_VideoDisplay *display, bool send_event)
{
    यदि (display) {
        SDL_DisplayData *display_data = display->internal;

        /* A preceding surface leave event is not guaranteed when an output is removed,
         * so ensure that no window continues to hold a reference to a removed output.
         */
        प्रति (SDL_Window *window = SDL_GetVideoDevice()->windows; window; window = window->next) {
            Wayland_RemoveOutputFromWindow(window->internal, display_data);
        }

        SDL_free(display_data->wl_output_name);

        यदि (display_data->wp_color_management_output) {
            Wayland_FreeColorInfoState(display_data->color_info_state);
            wp_color_management_output_v1_destroy(display_data->wp_color_management_output);
        }

        यदि (display_data->xdg_output) {
            zxdg_output_v1_destroy(display_data->xdg_output);
        }

        यदि (wl_output_get_version(display_data->output) >= WL_OUTPUT_RELEASE_SINCE_VERSION) {
            wl_output_release(display_data->output);
        } अन्यथा {
            wl_output_destroy(display_data->output);
        }

        SDL_DelVideoDisplay(display->id, send_event);
    }
}

स्थिर शून्य Wayland_FinalizeDisplays(SDL_VideoData *vid)
{
    Wayland_SortOutputs(vid);

    प्रति(पूर्णाङ्क i = 0; i < vid->output_गिनती; ++i) {
        SDL_DisplayData *d = vid->output_list[i];
        d->display = SDL_AddVideoDisplay(&d->placeholder, false);
        SDL_free(d->placeholder.name);
        SDL_zero(d->placeholder);
    }
}

स्थिर शून्य Wayland_init_xdg_output(SDL_VideoData *d)
{
    प्रति (पूर्णाङ्क i = 0; i < d->output_गिनती; ++i) {
        SDL_DisplayData *disp = d->output_list[i];
        disp->xdg_output = zxdg_output_manager_v1_get_xdg_output(disp->videodata->xdg_output_manager, disp->output);
        zxdg_output_v1_add_listener(disp->xdg_output, &xdg_output_listener, disp);
    }
}

स्थिर शून्य Wayland_InitColorManager(SDL_VideoData *d)
{
    प्रति (पूर्णाङ्क i = 0; i < d->output_गिनती; ++i) {
        SDL_DisplayData *disp = d->output_list[i];
        disp->wp_color_management_output = wp_color_manager_v1_get_output(disp->videodata->wp_color_manager_v1, disp->output);
        wp_color_management_output_v1_add_listener(disp->wp_color_management_output, &wp_color_management_output_listener, disp);
        Wayland_GetColorInfoForOutput(disp, true);
    }
}

स्थिर शून्य handle_xdg_session_created(शून्य *data, संरचना xdg_session_v1 *xdg_session_v1, ध्रुव वर्ण *id)
{
    SDL_SetStringProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, id);
}

स्थिर शून्य handle_xdg_session_restored(शून्य *data, संरचना xdg_session_v1 *xdg_session_v1)
{
    // NOP
}

स्थिर शून्य handle_xdg_session_replaced(शून्य *data, संरचना xdg_session_v1 *xdg_session_v1)
{
    SDL_VideoDevice *viddev = SDL_GetVideoDevice();
    SDL_VideoData *viddata = data;

    // Clean up all session objects, as they have become inert, and should be destroyed.
    SDL_SetStringProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, रिक्त);

    प्रति (SDL_Window *w = viddev->windows; w; w = w->next) {
        SDL_WindowData *d = w->internal;

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

शून्य Wayland_CreateSession(SDL_VideoData *viddata)
{
    यदि (!viddata->xdg_session_manager) {
        // Set the ID string to null if session management is not available.
        SDL_SetStringProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, रिक्त);
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
            xdg_session_v1_add_listener(viddata->xdg_session, &xdg_session_listener, viddata);
        }
    }
}

स्थिर शून्य Wayland_SessionDestroy(SDL_VideoData *viddata)
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

स्थिर शून्य handle_xdg_wm_base_ping(शून्य *data, संरचना xdg_wm_base *xdg, uint32_t serial)
{
    xdg_wm_base_pong(xdg, serial);
}

स्थिर ध्रुव संरचना xdg_wm_base_listener _xdg_wm_base_listener = {
    handle_xdg_wm_base_ping
};

#ifdef HAVE_LIBDECOR_H
स्थिर शून्य libdecor_error(संरचना libdecor *context,
                           गणना libdecor_error error,
                           ध्रुव वर्ण *message)
{
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "libdecor error (%d): %s", error, message);
}

स्थिर संरचना libdecor_interface libdecor_interface = {
    libdecor_error
};
#endif

स्थिर शून्य handle_registry_global(शून्य *data, संरचना wl_registry *registry, uint32_t id,
                                   ध्रुव वर्ण *interface, uint32_t version)
{
    SDL_VideoData *d = data;

    यदि (SDL_strcmp(interface, wl_compositor_interface.name) == 0) {
        d->compositor = wl_registry_bind(d->registry, id, &wl_compositor_interface, SDL_min(SDL_WL_COMPOSITOR_VERSION, version));
    } अन्यथा यदि (SDL_strcmp(interface, wl_subcompositor_interface.name) == 0) {
        d->subcompositor = wl_registry_bind(d->registry, id, &wl_subcompositor_interface, 1);
    } अन्यथा यदि (SDL_strcmp(interface, wl_output_interface.name) == 0) {
        Wayland_add_display(d, id, SDL_min(version, SDL_WL_OUTPUT_VERSION));
    } अन्यथा यदि (SDL_strcmp(interface, wl_seat_interface.name) == 0) {
        संरचना wl_seat *seat = wl_registry_bind(d->registry, id, &wl_seat_interface, SDL_min(SDL_WL_SEAT_VERSION, version));
        Wayland_DisplayCreateSeat(d, seat, id);
    } अन्यथा यदि (SDL_strcmp(interface, xdg_wm_base_interface.name) == 0) {
        d->shell.xdg = wl_registry_bind(d->registry, id, &xdg_wm_base_interface, SDL_min(version, 7));
        xdg_wm_base_add_listener(d->shell.xdg, &_xdg_wm_base_listener, रिक्त);
    } अन्यथा यदि (SDL_strcmp(interface, wl_shm_interface.name) == 0) {
        d->shm = wl_registry_bind(registry, id, &wl_shm_interface, SDL_min(SDL_WL_SHM_VERSION, version));
    } अन्यथा यदि (SDL_strcmp(interface, zwp_relative_pointer_manager_v1_interface.name) == 0) {
        d->relative_pointer_manager = wl_registry_bind(d->registry, id, &zwp_relative_pointer_manager_v1_interface, 1);
    } अन्यथा यदि (SDL_strcmp(interface, zwp_pointer_constraints_v1_interface.name) == 0) {
        d->pointer_constraints = wl_registry_bind(d->registry, id, &zwp_pointer_constraints_v1_interface, 1);
    } अन्यथा यदि (SDL_strcmp(interface, zwp_keyboard_shortcuts_inhibit_manager_v1_interface.name) == 0) {
        d->कुंजी_inhibitor_manager = wl_registry_bind(d->registry, id, &zwp_keyboard_shortcuts_inhibit_manager_v1_interface, 1);
    } अन्यथा यदि (SDL_strcmp(interface, zwp_idle_inhibit_manager_v1_interface.name) == 0) {
        d->idle_inhibit_manager = wl_registry_bind(d->registry, id, &zwp_idle_inhibit_manager_v1_interface, 1);
    } अन्यथा यदि (SDL_strcmp(interface, xdg_activation_v1_interface.name) == 0) {
        d->activation_manager = wl_registry_bind(d->registry, id, &xdg_activation_v1_interface, 1);
    } अन्यथा यदि (SDL_strcmp(interface, zwp_text_निवेश_manager_v3_interface.name) == 0) {
        d->text_निवेश_manager = wl_registry_bind(d->registry, id, &zwp_text_निवेश_manager_v3_interface, 1);
        Wayland_Display_Init_Text_निवेश_Manager(d, id);
    } अन्यथा यदि (SDL_strcmp(interface, wl_data_device_manager_interface.name) == 0) {
        d->data_device_manager = wl_registry_bind(d->registry, id, &wl_data_device_manager_interface, SDL_min(3, version));
        Wayland_DisplayInitDataDeviceManager(d);
    } अन्यथा यदि (SDL_strcmp(interface, zwp_primary_selection_device_manager_v1_interface.name) == 0) {
        d->primary_selection_device_manager = wl_registry_bind(d->registry, id, &zwp_primary_selection_device_manager_v1_interface, 1);
        Wayland_DisplayInitPrimarySelectionDeviceManager(d);
    } अन्यथा यदि (SDL_strcmp(interface, zxdg_decoration_manager_v1_interface.name) == 0) {
        d->decoration_manager = wl_registry_bind(d->registry, id, &zxdg_decoration_manager_v1_interface, SDL_min(2, version));
    } अन्यथा यदि (SDL_strcmp(interface, zwp_tablet_manager_v2_interface.name) == 0) {
        d->tablet_manager = wl_registry_bind(d->registry, id, &zwp_tablet_manager_v2_interface, 1);
        Wayland_DisplayInitTabletManager(d);
    } अन्यथा यदि (SDL_strcmp(interface, zxdg_output_manager_v1_interface.name) == 0) {
        version = SDL_min(version, 3); // Versions 1 through 3 are supported.
        d->xdg_output_manager = wl_registry_bind(d->registry, id, &zxdg_output_manager_v1_interface, version);
        Wayland_init_xdg_output(d);
    } अन्यथा यदि (SDL_strcmp(interface, wp_viewporter_interface.name) == 0) {
        d->viewporter = wl_registry_bind(d->registry, id, &wp_viewporter_interface, 1);
    } अन्यथा यदि (SDL_strcmp(interface, wp_fractional_scale_manager_v1_interface.name) == 0) {
        d->fractional_scale_manager = wl_registry_bind(d->registry, id, &wp_fractional_scale_manager_v1_interface, 1);
    } अन्यथा यदि (SDL_strcmp(interface, zwp_निवेश_timestamps_manager_v1_interface.name) == 0) {
        d->निवेश_timestamps_manager = wl_registry_bind(d->registry, id, &zwp_निवेश_timestamps_manager_v1_interface, 1);
        Wayland_Display_Init_निवेश_Timestamp_Manager(d);
    } अन्यथा यदि (SDL_strcmp(interface, wp_cursor_shape_manager_v1_interface.name) == 0) {
        d->cursor_shape_manager = wl_registry_bind(d->registry, id, &wp_cursor_shape_manager_v1_interface, SDL_min(version, 2));
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
        d->wp_color_manager_v1 = wl_registry_bind(d->registry, id, &wp_color_manager_v1_interface, SDL_min(version, 2));
        Wayland_InitColorManager(d);
    } अन्यथा यदि (SDL_strcmp(interface, wp_pointer_warp_v1_interface.name) == 0) {
        d->wp_pointer_warp_v1 = wl_registry_bind(d->registry, id, &wp_pointer_warp_v1_interface, 1);
    } अन्यथा यदि (SDL_strcmp(interface, zwp_pointer_gestures_v1_interface.name) == 0) {
        d->zwp_pointer_gestures = wl_registry_bind(d->registry, id, &zwp_pointer_gestures_v1_interface, SDL_min(version, 3));
        Wayland_DisplayInitPointerGestureManager(d);
    } अन्यथा यदि (SDL_strcmp(interface, wp_single_pixel_buffer_manager_v1_interface.name) == 0) {
        d->single_pixel_buffer_manager = wl_registry_bind(d->registry, id, &wp_single_pixel_buffer_manager_v1_interface, 1);
    } अन्यथा यदि (SDL_strcmp(interface, xdg_session_manager_v1_interface.name) == 0) {
        d->xdg_session_manager = wl_registry_bind(d->registry, id, &xdg_session_manager_v1_interface, 1);
    } अन्यथा यदि (SDL_strcmp(interface, xdg_toplevel_tag_manager_v1_interface.name) == 0) {
        d->xdg_toplevel_tag_manager = wl_registry_bind(d->registry, id, &xdg_toplevel_tag_manager_v1_interface, 1);
    }
#ifdef SDL_WL_FIXES_VERSION
    अन्यथा यदि (SDL_strcmp(interface, wl_fixes_interface.name) == 0) {
        d->wl_fixes = wl_registry_bind(d->registry, id, &wl_fixes_interface, SDL_min(SDL_WL_FIXES_VERSION, version));
    }
#endif
}

स्थिर शून्य handle_registry_remove_global(शून्य *data, संरचना wl_registry *registry, uint32_t id)
{
    SDL_VideoData *d = data;

    // We don't get an interface, just an ID, so check outputs and seats.
    प्रति (पूर्णाङ्क i = 0; i < d->output_गिनती; ++i) {
        SDL_DisplayData *disp = d->output_list[i];
        यदि (disp->registry_id == id) {
            Wayland_free_display(SDL_GetVideoDisplay(disp->display), true);

            यदि (i < d->output_गिनती) {
                SDL_memmove(&d->output_list[i], &d->output_list[i + 1], परिमाण(SDL_DisplayData *) * (d->output_गिनती - i - 1));
            }

            d->output_गिनती--;
            गच्छ ack_remove;
        }
    }

    SDL_WaylandSeat *seat, *temp;
    wl_list_for_each_safe (seat, temp, &d->seat_list, link) {
        यदि (seat->registry_id == id) {
            Wayland_SeatDestroy(seat, false);
            गच्छ ack_remove;
        }
    }

ack_remove:
    यदि (d->wl_fixes && wl_fixes_get_version(d->wl_fixes) >= WL_FIXES_ACK_GLOBAL_REMOVE_SINCE_VERSION) {
        wl_fixes_ack_global_remove(d->wl_fixes, registry, id);
    }
}

स्थिर ध्रुव संरचना wl_registry_listener registry_listener = {
    handle_registry_global,
    handle_registry_remove_global
};

#ifdef HAVE_LIBDECOR_H
स्थिर bool should_use_libdecor(SDL_VideoData *data, bool ignore_xdg)
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

    यदि (data->decoration_manager) {
        प्रत्यागम false;
    }

    प्रत्यागम true;
}

स्थिर शून्य LibdecorNew(SDL_VideoData *data)
{
    data->shell.libdecor = libdecor_new(data->display, &libdecor_interface);
}

// Called in another thread, but the UI thread is blocked in SDL_WaitThread
// during that time, so it should be OK to dereference data without locks
स्थिर पूर्णाङ्क SDLCALL LibdecorNewInThread(शून्य *data)
{
    LibdecorNew((SDL_VideoData *)data);
    प्रत्यागम 0;
}
#endif

#ifdef HAVE_GETRESUID
#define SDL_getresuid getresuid
#अन्यथा
// Non-POSIX, but Linux and some BSDs have it.
// To reduce the number of code paths, if getresuid() isn't available at
// compile-time, we behave as though it existed but failed at runtime.
स्थिर अन्तःस्थ पूर्णाङ्क SDL_getresuid(uid_t *ruid, uid_t *euid, uid_t *suid) {
    त्रुटि_सं = ENOSYS;
    प्रत्यागम -1;
}
#endif

#ifdef HAVE_GETRESGID
#define SDL_getresgid getresgid
#अन्यथा
// Same as getresuid() but for the primary group
स्थिर अन्तःस्थ पूर्णाङ्क SDL_getresgid(gid_t *rgid, gid_t *egid, gid_t *sgid) {
    त्रुटि_सं = ENOSYS;
    प्रत्यागम -1;
}
#endif

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

bool Wayland_LoadLibdecor(SDL_VideoData *data, bool ignore_xdg)
{
#ifdef HAVE_LIBDECOR_H
    यदि (data->shell.libdecor != रिक्त) {
        प्रत्यागम true; // Already loaded!
    }
    यदि (should_use_libdecor(data, ignore_xdg)) {
        यदि (CanUseGtk()) {
            LibdecorNew(data);
        } अन्यथा {
            // Intentionally initialize libdecor in a non-main thread
            // so that it will not use its GTK plugin, but instead will
            // fall back to the Cairo or dummy plugin
            SDL_Thread *thread = SDL_CreateThread(LibdecorNewInThread, "SDL_LibdecorNew", (शून्य *)data);
            // Note that the other thread now "owns" data until we have
            // waited for it, so don't touch data here
            SDL_WaitThread(thread, रिक्त);
        }

        प्रत्यागम data->shell.libdecor != रिक्त;
    }
#endif
    प्रत्यागम false;
}

bool Wayland_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

    data->event_thread_context = Wayland_CreateEventThread(data, "SDL Event Thread Queue");
    यदि (!data->event_thread_context) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Failed to create event thread context");
    }

    data->job_thread_context = Wayland_CreateJobThread();
    यदि (!data->job_thread_context) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Failed to create job thread context");
    }

    data->xkb_context = WAYLAND_xkb_context_new(0);
    यदि (!data->xkb_context) {
        प्रत्यागम SDL_SetError("Failed to create XKB context");
    }

    data->registry = wl_display_get_registry(data->display);
    यदि (!data->registry) {
        प्रत्यागम SDL_SetError("Failed to get the Wayland registry");
    }

    wl_registry_add_listener(data->registry, &registry_listener, data);

    // First roundtrip to receive all registry objects.
    WAYLAND_wl_display_roundtrip(data->display);

    // Require viewports and xdg-output for display scaling.
    यदि (data->scale_to_display_enabled) {
        यदि (!data->viewporter) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Display scaling requires the missing 'wp_viewporter' protocol: disabling");
            data->scale_to_display_enabled = false;
        }
        यदि (!data->xdg_output_manager) {
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

    यदि (data->primary_selection_device_manager) {
        _this->SetPrimarySelectionText = Wayland_SetPrimarySelectionText;
        _this->GetPrimarySelectionText = Wayland_GetPrimarySelectionText;
        _this->HasPrimarySelectionText = Wayland_HasPrimarySelectionText;
    }

    data->initializing = false;

    प्रत्यागम true;
}

स्थिर bool Wayland_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    SDL_VideoData *viddata = _this->internal;
    SDL_DisplayData *internal = display->internal;

    यदि (!viddata->scale_to_display_enabled) {
        rect->x = internal->logical.x;
        rect->y = internal->logical.y;
    } अन्यथा {
        rect->x = internal->pixel.x;
        rect->y = internal->pixel.y;
    }

    // When an emulated, exclusive fullscreen window has focus, treat the mode dimensions as the display bounds.
    यदि (display->fullscreen_window &&
        display->fullscreen_window->fullscreen_exclusive &&
        display->fullscreen_window->internal->active &&
        display->fullscreen_window->current_fullscreen_mode.w != 0 &&
        display->fullscreen_window->current_fullscreen_mode.h != 0) {
        rect->w = display->fullscreen_window->current_fullscreen_mode.w;
        rect->h = display->fullscreen_window->current_fullscreen_mode.h;
    } अन्यथा {
        यदि (!viddata->scale_to_display_enabled) {
            rect->w = display->current_mode->w;
            rect->h = display->current_mode->h;
        } अन्यथा यदि (internal->transform & WL_OUTPUT_TRANSFORM_90) {
            rect->w = internal->pixel.height;
            rect->h = internal->pixel.width;
        } अन्यथा {
            rect->w = internal->pixel.width;
            rect->h = internal->pixel.height;
        }
    }
    प्रत्यागम true;
}

स्थिर शून्य Wayland_VideoCleanup(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    SDL_WaylandSeat *seat, *tmp;

    Wayland_SessionDestroy(data);

    प्रति (पूर्णाङ्क i = _this->अंक_displays - 1; i >= 0; --i) {
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
    data->event_thread_context = रिक्त;

    Wayland_DestroyJobThread(data->job_thread_context);
    data->job_thread_context = रिक्त;

    यदि (data->pointer_constraints) {
        zwp_pointer_constraints_v1_destroy(data->pointer_constraints);
        data->pointer_constraints = रिक्त;
    }

    यदि (data->relative_pointer_manager) {
        zwp_relative_pointer_manager_v1_destroy(data->relative_pointer_manager);
        data->relative_pointer_manager = रिक्त;
    }

    यदि (data->activation_manager) {
        xdg_activation_v1_destroy(data->activation_manager);
        data->activation_manager = रिक्त;
    }

    यदि (data->idle_inhibit_manager) {
        zwp_idle_inhibit_manager_v1_destroy(data->idle_inhibit_manager);
        data->idle_inhibit_manager = रिक्त;
    }

    यदि (data->कुंजी_inhibitor_manager) {
        zwp_keyboard_shortcuts_inhibit_manager_v1_destroy(data->कुंजी_inhibitor_manager);
        data->कुंजी_inhibitor_manager = रिक्त;
    }

    यदि (data->text_निवेश_manager) {
        zwp_text_निवेश_manager_v3_destroy(data->text_निवेश_manager);
        data->text_निवेश_manager = रिक्त;
    }

    यदि (data->xkb_context) {
        WAYLAND_xkb_context_unref(data->xkb_context);
        data->xkb_context = रिक्त;
    }

    यदि (data->tablet_manager) {
        zwp_tablet_manager_v2_destroy((संरचना zwp_tablet_manager_v2 *)data->tablet_manager);
        data->tablet_manager = रिक्त;
    }

    यदि (data->data_device_manager) {
        wl_data_device_manager_destroy(data->data_device_manager);
        data->data_device_manager = रिक्त;
    }

    यदि (data->shm) {
        यदि (wl_shm_get_version(data->shm) >= WL_SHM_RELEASE_SINCE_VERSION) {
            wl_shm_release(data->shm);
        } अन्यथा {
            wl_shm_destroy(data->shm);
        }
        data->shm = रिक्त;
    }

    यदि (data->shell.xdg) {
        xdg_wm_base_destroy(data->shell.xdg);
        data->shell.xdg = रिक्त;
    }

    यदि (data->decoration_manager) {
        zxdg_decoration_manager_v1_destroy(data->decoration_manager);
        data->decoration_manager = रिक्त;
    }

    यदि (data->xdg_output_manager) {
        zxdg_output_manager_v1_destroy(data->xdg_output_manager);
        data->xdg_output_manager = रिक्त;
    }

    यदि (data->viewporter) {
        wp_viewporter_destroy(data->viewporter);
        data->viewporter = रिक्त;
    }

    यदि (data->primary_selection_device_manager) {
        zwp_primary_selection_device_manager_v1_destroy(data->primary_selection_device_manager);
        data->primary_selection_device_manager = रिक्त;
    }

    यदि (data->fractional_scale_manager) {
        wp_fractional_scale_manager_v1_destroy(data->fractional_scale_manager);
        data->fractional_scale_manager = रिक्त;
    }

    यदि (data->निवेश_timestamps_manager) {
        zwp_निवेश_timestamps_manager_v1_destroy(data->निवेश_timestamps_manager);
        data->निवेश_timestamps_manager = रिक्त;
    }

    यदि (data->cursor_shape_manager) {
        wp_cursor_shape_manager_v1_destroy(data->cursor_shape_manager);
        data->cursor_shape_manager = रिक्त;
    }

    यदि (data->zxdg_exporter_v2) {
        zxdg_exporter_v2_destroy(data->zxdg_exporter_v2);
        data->zxdg_exporter_v2 = रिक्त;
    }

    यदि (data->xdg_wm_dialog_v1) {
        xdg_wm_dialog_v1_destroy(data->xdg_wm_dialog_v1);
        data->xdg_wm_dialog_v1 = रिक्त;
    }

    यदि (data->wp_alpha_modifier_v1) {
        wp_alpha_modifier_v1_destroy(data->wp_alpha_modifier_v1);
        data->wp_alpha_modifier_v1 = रिक्त;
    }

    यदि (data->xdg_toplevel_icon_manager_v1) {
        xdg_toplevel_icon_manager_v1_destroy(data->xdg_toplevel_icon_manager_v1);
        data->xdg_toplevel_icon_manager_v1 = रिक्त;
    }

    यदि (data->frog_color_management_factory_v1) {
        frog_color_management_factory_v1_destroy(data->frog_color_management_factory_v1);
        data->frog_color_management_factory_v1 = रिक्त;
    }

    यदि (data->wp_color_manager_v1) {
        wp_color_manager_v1_destroy(data->wp_color_manager_v1);
        data->wp_color_manager_v1 = रिक्त;
    }

    यदि (data->wp_pointer_warp_v1) {
        wp_pointer_warp_v1_destroy(data->wp_pointer_warp_v1);
        data->wp_pointer_warp_v1 = रिक्त;
    }

    यदि (data->zwp_pointer_gestures) {
        यदि (zwp_pointer_gestures_v1_get_version(data->zwp_pointer_gestures) >= ZWP_POINTER_GESTURES_V1_RELEASE_SINCE_VERSION) {
            zwp_pointer_gestures_v1_release(data->zwp_pointer_gestures);
        } अन्यथा {
            zwp_pointer_gestures_v1_destroy(data->zwp_pointer_gestures);
        }
        data->zwp_pointer_gestures = रिक्त;
    }

    यदि (data->single_pixel_buffer_manager) {
        wp_single_pixel_buffer_manager_v1_destroy(data->single_pixel_buffer_manager);
        data->single_pixel_buffer_manager = रिक्त;
    }

    यदि (data->xdg_session_manager) {
        xdg_session_manager_v1_destroy(data->xdg_session_manager);
        data->xdg_session_manager = रिक्त;
    }

    यदि (data->xdg_toplevel_tag_manager) {
        xdg_toplevel_tag_manager_v1_destroy(data->xdg_toplevel_tag_manager);
        data->xdg_toplevel_tag_manager = रिक्त;
    }

    यदि (data->subcompositor) {
        wl_subcompositor_destroy(data->subcompositor);
        data->subcompositor = रिक्त;
    }

    यदि (data->compositor) {
        wl_compositor_destroy(data->compositor);
        data->compositor = रिक्त;
    }

    यदि (data->registry) {
        यदि (data->wl_fixes) {
            wl_fixes_destroy_registry(data->wl_fixes, data->registry);
            wl_fixes_destroy(data->wl_fixes);
            data->wl_fixes = रिक्त;
        }
        wl_registry_destroy(data->registry);
        data->registry = रिक्त;
    }
}

स्थिर bool Wayland_VideoReconnect(SDL_VideoDevice *_this)
{
#यदि 0 // TODO RECONNECT: Uncomment all when https://invent.kde.org/plasma/kwin/-/wikis/Restarting is completed
    SDL_VideoData *data = _this->internal;

    SDL_Window *window = रिक्त;

    SDL_GLContext current_ctx = SDL_GL_GetCurrentContext();
    SDL_Window *current_window = SDL_GL_GetCurrentWindow();

    SDL_GL_MakeCurrent(रिक्त, रिक्त);
    Wayland_VideoCleanup(_this);

    SDL_ResetKeyboard();
    SDL_ResetMouse();
    यदि (WAYLAND_wl_display_reconnect(data->display) < 0) {
        प्रत्यागम false;
    }

    Wayland_VideoInit(_this);

    window = _this->windows;
    यावत् (window) {
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

    यदि (current_window && current_ctx) {
        SDL_GL_MakeCurrent (current_window, current_ctx);
    }
    प्रत्यागम true;
#अन्यथा
    प्रत्यागम false;
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
    यदि (video_data->display_disconnected) {
        प्रत्यागम false;
    }

    यदि (Wayland_VideoReconnect(_this)) {
        प्रत्यागम true;
    }

    video_data->display_disconnected = true;
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Wayland display connection closed by server (fatal)");

    // Only send a single quit message, as application shutdown might call SDL_PumpEvents().
    SDL_SendQuit();

    प्रत्यागम false;
}

शून्य Wayland_VideoQuit(SDL_VideoDevice *_this)
{
    Wayland_VideoCleanup(_this);

#ifdef HAVE_LIBDECOR_H
    SDL_VideoData *data = _this->internal;
    यदि (data->shell.libdecor) {
        libdecor_unref(data->shell.libdecor);
        data->shell.libdecor = रिक्त;
    }
#endif
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
