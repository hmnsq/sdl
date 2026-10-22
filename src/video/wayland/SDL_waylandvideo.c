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

#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_WAYLAND

#समावेश "../../core/linux/SDL_system_theme.h"
#समावेश "../../core/linux/SDL_progressbar.h"
#समावेश "../../events/SDL_events_c.h"

#समावेश "SDL_waylandclipboard.h"
#समावेश "SDL_waylandcolor.h"
#समावेश "SDL_waylandevents_c.h"
#समावेश "SDL_waylandkeyboard.h"
#समावेश "SDL_waylandmessagebox.h"
#समावेश "SDL_waylandmouse.h"
#समावेश "SDL_waylandopengles.h"
#समावेश "SDL_waylandvideo.h"
#समावेश "SDL_waylandvulkan.h"
#समावेश "SDL_waylandwindow.h"

#समावेश <fcntl.h>
#समावेश <sys/types.h>
#समावेश <unistd.h>
#समावेश <errno.h>
#समावेश <xkbcommon/xkbcommon.h>

#समावेश <wayland-util.h>

#समावेश "alpha-modifier-v1-client-protocol.h"
#समावेश "cursor-shape-v1-client-protocol.h"
#समावेश "fractional-scale-v1-client-protocol.h"
#समावेश "frog-color-management-v1-client-protocol.h"
#समावेश "idle-inhibit-unstable-v1-client-protocol.h"
#समावेश "input-timestamps-unstable-v1-client-protocol.h"
#समावेश "keyboard-shortcuts-inhibit-unstable-v1-client-protocol.h"
#समावेश "pointer-constraints-unstable-v1-client-protocol.h"
#समावेश "primary-selection-unstable-v1-client-protocol.h"
#समावेश "relative-pointer-unstable-v1-client-protocol.h"
#समावेश "tablet-v2-client-protocol.h"
#समावेश "text-input-unstable-v3-client-protocol.h"
#समावेश "viewporter-client-protocol.h"
#समावेश "xdg-activation-v1-client-protocol.h"
#समावेश "xdg-decoration-unstable-v1-client-protocol.h"
#समावेश "xdg-dialog-v1-client-protocol.h"
#समावेश "xdg-foreign-unstable-v2-client-protocol.h"
#समावेश "xdg-output-unstable-v1-client-protocol.h"
#समावेश "xdg-shell-client-protocol.h"
#समावेश "xdg-toplevel-icon-v1-client-protocol.h"
#समावेश "color-management-v1-client-protocol.h"
#समावेश "pointer-warp-v1-client-protocol.h"
#समावेश "pointer-gestures-unstable-v1-client-protocol.h"
#समावेश "single-pixel-buffer-v1-client-protocol.h"
#समावेश "xdg-session-management-v1-client-protocol.h"
#समावेश "xdg-toplevel-tag-v1-client-protocol.h"

#अगर_घोषित HAVE_LIBDECOR_H
#समावेश <libdecor.h>
#पूर्ण_अगर

#घोषणा WAYLANDVID_DRIVER_NAME "wayland"

// Clamp core protocol versions on older versions of libwayland.
#अगर SDL_WAYLAND_CHECK_VERSION(1, 22, 0)
#घोषणा SDL_WL_COMPOSITOR_VERSION 6
#अन्यथा
#घोषणा SDL_WL_COMPOSITOR_VERSION 4
#पूर्ण_अगर

#अगर SDL_WAYLAND_CHECK_VERSION(1, 26, 0)
#घोषणा SDL_WL_SEAT_VERSION 11
#या_अगर SDL_WAYLAND_CHECK_VERSION(1, 24, 0)
#घोषणा SDL_WL_SEAT_VERSION 10
#या_अगर SDL_WAYLAND_CHECK_VERSION(1, 22, 0)
#घोषणा SDL_WL_SEAT_VERSION 9
#या_अगर SDL_WAYLAND_CHECK_VERSION(1, 21, 0)
#घोषणा SDL_WL_SEAT_VERSION 8
#अन्यथा
#घोषणा SDL_WL_SEAT_VERSION 5
#पूर्ण_अगर

#अगर SDL_WAYLAND_CHECK_VERSION(1, 20, 0)
#घोषणा SDL_WL_OUTPUT_VERSION 4
#अन्यथा
#घोषणा SDL_WL_OUTPUT_VERSION 3
#पूर्ण_अगर

#अगर SDL_WAYLAND_CHECK_VERSION(1, 24, 0)
#घोषणा SDL_WL_SHM_VERSION 2
#अन्यथा
#घोषणा SDL_WL_SHM_VERSION 1
#पूर्ण_अगर

// The SDL libwayland-client minimum is 1.18, which supports version 3.
#घोषणा SDL_WL_तथ्य_DEVICE_VERSION 3

// wl_fixes was introduced in 1.24.0
#अगर SDL_WAYLAND_CHECK_VERSION(1, 26, 0)
#घोषणा SDL_WL_FIXES_VERSION 2
#या_अगर SDL_WAYLAND_CHECK_VERSION(1, 24, 0)
#घोषणा SDL_WL_FIXES_VERSION 1
#पूर्ण_अगर

#अगर_घोषित SDL_USE_LIBDBUS
#समावेश "../../core/linux/SDL_dbus.h"

#घोषणा DISPLAY_INFO_गाँठ   "org.gnome.Mutter.DisplayConfig"
#घोषणा DISPLAY_INFO_PATH   "/org/gnome/Mutter/DisplayConfig"
#घोषणा DISPLAY_INFO_METHOD "GetCurrentState"
#पूर्ण_अगर

/* GNOME doesn't expose displays in any particular order, but we can find the
 * primary display and its logical coordinates via a DBus method.
 */
अटल bool Wayland_GetGNOMEPrimaryDisplayCoordinates(पूर्णांक *x, पूर्णांक *y)
{
#अगर_घोषित SDL_USE_LIBDBUS
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    अगर (dbus == शून्य) {
        वापस false;
    }
    DBusMessage *reply = शून्य;
    DBusMessageIter iter[3];
    DBusMessage *संदेश = dbus->message_new_method_call(DISPLAY_INFO_गाँठ,
                                                     DISPLAY_INFO_PATH,
                                                     DISPLAY_INFO_गाँठ,
                                                     DISPLAY_INFO_METHOD);

    अगर (संदेश) {
        reply = dbus->connection_send_with_reply_and_block(dbus->session_conn, संदेश, DBUS_TIMEOUT_USE_DEFAULT, शून्य);
        dbus->message_unref(संदेश);
    }

    अगर (reply) {
        // Serial (don't care)
        dbus->message_iter_init(reply, &iter[0]);
        अगर (dbus->message_iter_get_arg_type(&iter[0]) != DBUS_TYPE_UINT32) {
            जाओ error;
        }

        // Physical monitor array (don't care)
        dbus->message_iter_अग्र(&iter[0]);
        अगर (dbus->message_iter_get_arg_type(&iter[0]) != DBUS_TYPE_ARRAY) {
            जाओ error;
        }

        // Logical monitor array of structs
        dbus->message_iter_अग्र(&iter[0]);
        अगर (dbus->message_iter_get_arg_type(&iter[0]) != DBUS_TYPE_ARRAY) {
            जाओ error;
        }

        // First logical monitor struct
        dbus->message_iter_recurse(&iter[0], &iter[1]);
        अगर (dbus->message_iter_get_arg_type(&iter[1]) != DBUS_TYPE_STRUCT) {
            जाओ error;
        }

        करो {
            पूर्णांक logical_x, logical_y;
            dbus_bool_t primary;

            // Logical X
            dbus->message_iter_recurse(&iter[1], &iter[2]);
            अगर (dbus->message_iter_get_arg_type(&iter[2]) != DBUS_TYPE_INT32) {
                जाओ error;
            }
            dbus->message_iter_get_basic(&iter[2], &logical_x);

            // Logical Y
            dbus->message_iter_अग्र(&iter[2]);
            अगर (dbus->message_iter_get_arg_type(&iter[2]) != DBUS_TYPE_INT32) {
                जाओ error;
            }
            dbus->message_iter_get_basic(&iter[2], &logical_y);

            // Scale (don't care)
            dbus->message_iter_अग्र(&iter[2]);
            अगर (dbus->message_iter_get_arg_type(&iter[2]) != DBUS_TYPE_DOUBLE) {
                जाओ error;
            }

            // Transform (don't care)
            dbus->message_iter_अग्र(&iter[2]);
            अगर (dbus->message_iter_get_arg_type(&iter[2]) != DBUS_TYPE_UINT32) {
                जाओ error;
            }

            // Primary display boolean
            dbus->message_iter_अग्र(&iter[2]);
            अगर (dbus->message_iter_get_arg_type(&iter[2]) != DBUS_TYPE_BOOLEAN) {
                जाओ error;
            }
            dbus->message_iter_get_basic(&iter[2], &primary);

            अगर (primary) {
                *x = logical_x;
                *y = logical_y;

                // We found the primary display: success.
                dbus->message_unref(reply);
                वापस true;
            }
        } जबतक (dbus->message_iter_अग्र(&iter[1]));
    }

error:
    अगर (reply) {
        dbus->message_unref(reply);
    }
#पूर्ण_अगर
    वापस false;
}

// Sort the list of displays into a deterministic order
अटल पूर्णांक SDLCALL Wayland_DisplayPositionCompare(स्थिर व्योम *a, स्थिर व्योम *b)
{
    स्थिर SDL_Display_तथ्य *da = *(SDL_Display_तथ्य **)a;
    स्थिर SDL_Display_तथ्य *db = *(SDL_Display_तथ्य **)b;
    स्थिर bool a_at_origin = da->logical.x == 0 && da->logical.y == 0;
    स्थिर bool b_at_origin = db->logical.x == 0 && db->logical.y == 0;

    // Sort the display at 0,0 to be beginning of the list, as that will be the fallback primary.
    अगर (a_at_origin && !b_at_origin) {
        वापस -1;
    }
    अगर (b_at_origin && !a_at_origin) {
        वापस 1;
    }

    अगर (da->logical.x < db->logical.x) {
        वापस -1;
    }
    अगर (da->logical.x > db->logical.x) {
        वापस 1;
    }
    अगर (da->logical.y < db->logical.y) {
        वापस -1;
    }
    अगर (da->logical.y > db->logical.y) {
        वापस 1;
    }

    // If no position information is available, use the connector name.
    अगर (da->wl_output_name && db->wl_output_name) {
        वापस SDL_strcmp(da->wl_output_name, db->wl_output_name);
    }

    वापस 0;
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
अटल पूर्णांक Wayland_GetPrimaryDisplay(SDL_Video_तथ्य *vid)
{
    अटल स्थिर पूर्णांक REFRESH_DELTA = 4000;

    // Query the DBus interface to see if the coordinates of the primary display are exposed.
    पूर्णांक x, y;
    अगर (Wayland_GetGNOMEPrimaryDisplayCoordinates(&x, &y)) {
        क्रम (पूर्णांक i = 0; i < vid->output_गिनती; ++i) {
            अगर (vid->output_list[i]->logical.x == x && vid->output_list[i]->logical.y == y) {
                वापस i;
            }
        }
    }

    // Otherwise, choose the 'best' display.
    पूर्णांक best_width = 0;
    पूर्णांक best_height = 0;
    द्विगुन best_scale = 0.0;
    भग्न best_headroom = 0.0f;
    पूर्णांक best_refresh = 0;
    bool best_is_landscape = false;
    पूर्णांक best_सूचकांक = 0;

    क्रम (पूर्णांक i = 0; i < vid->output_गिनती; ++i) {
        स्थिर SDL_Display_तथ्य *d = vid->output_list[i];
        स्थिर bool is_landscape = d->orientation != SDL_ORIENTATION_PORTRAIT && d->orientation != SDL_ORIENTATION_PORTRAIT_FLIPPED;
        bool have_new_best = false;

        अगर (!best_is_landscape && is_landscape) { // Favor landscape over portrait displays.
            have_new_best = true;
        } अन्यथा अगर (!best_is_landscape || is_landscape) { // Ignore portrait displays if a landscape was already found.
            अगर (d->pixel.width > best_width || d->pixel.height > best_height) {
                have_new_best = true;
            } अन्यथा अगर (d->pixel.width == best_width && d->pixel.height == best_height) {
                अगर (d->HDR.HDR_headroom > best_headroom) { // Favor a higher HDR luminance range
                    have_new_best = true;
                } अन्यथा अगर (d->HDR.HDR_headroom == best_headroom) {
                    अगर (d->refresh - best_refresh > REFRESH_DELTA) { // Favor a higher refresh rate, but ignore small differences (e.g. 59.97 vs 60.1)
                        have_new_best = true;
                    } अन्यथा अगर (d->scale_factor < best_scale && SDL_abs(d->refresh - best_refresh) <= REFRESH_DELTA) {
                        // Prefer a lower scale display if the difference in refresh rate is small.
                        have_new_best = true;
                    }
                }
            }
        }

        अगर (have_new_best) {
            best_width = d->pixel.width;
            best_height = d->pixel.height;
            best_scale = d->scale_factor;
            best_headroom = d->HDR.HDR_headroom;
            best_refresh = d->refresh;
            best_is_landscape = is_landscape;
            best_सूचकांक = i;
        }
    }

    वापस best_सूचकांक;
}

अटल व्योम Wayland_SortOutputsByPriorityHint(SDL_Video_तथ्य *vid)
{
    स्थिर अक्षर *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_PRIORITY);

    अगर (name_hint) {
        अक्षर *saveptr;
        अक्षर *str = SDL_strdup(name_hint);
        SDL_Display_तथ्य **sorted_list = SDL_malloc(माप(SDL_Display_तथ्य *) * vid->output_गिनती);

        अगर (str && sorted_list) {
            पूर्णांक sorted_सूचकांक = 0;

            // Sort the requested displays to the front of the list.
            स्थिर अक्षर *token = SDL_strtok_r(str, ",", &saveptr);
            जबतक (token) {
                क्रम (पूर्णांक i = 0; i < vid->output_गिनती; ++i) {
                    SDL_Display_तथ्य *d = vid->output_list[i];
                    अगर (d && d->wl_output_name && SDL_strcmp(token, d->wl_output_name) == 0) {
                        sorted_list[sorted_सूचकांक++] = d;
                        vid->output_list[i] = शून्य;
                        अवरोध;
                    }
                }

                token = SDL_strtok_r(शून्य, ",", &saveptr);
            }

            // Append the remaining outputs to the end of the list.
            क्रम (पूर्णांक i = 0; i < vid->output_गिनती; ++i) {
                अगर (vid->output_list[i]) {
                    sorted_list[sorted_सूचकांक++] = vid->output_list[i];
                }
            }

            // Copy the sorted list to the output list.
            SDL_memcpy(vid->output_list, sorted_list, माप(SDL_Display_तथ्य *) * vid->output_गिनती);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

अटल व्योम Wayland_DeriveOutputPixelCoordinates(SDL_Video_तथ्य *vid)
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
    क्रम ( पूर्णांक i = 0; i < vid->output_गिनती; ++i) {
        SDL_Display_तथ्य *d = vid->output_list[i];
        d->pixel.x = d->logical.x;
        d->pixel.y = d->logical.y;
    }

    क्रम (पूर्णांक i = 0; i < vid->output_गिनती; ++i) {
        SDL_Display_तथ्य *d1 = vid->output_list[i];
        अगर (d1->logical.width != d1->pixel.width || d1->logical.height != d1->pixel.height) {
            स्थिर पूर्णांक x_adj = d1->pixel.width - d1->logical.width;
            स्थिर पूर्णांक y_adj = d1->pixel.height - d1->logical.height;

            // Don't adjust for scale values less than 1.0.
            अगर (x_adj > 0 && y_adj > 0) {
                क्रम (पूर्णांक j = 0; j < vid->output_गिनती; ++j) {
                    SDL_Display_तथ्य *d2 = vid->output_list[j];
                    अगर (d2->logical.x > d1->logical.x) {
                        d2->pixel.x += x_adj;
                    }
                    अगर (d2->logical.y > d1->logical.y) {
                        d2->pixel.y += y_adj;
                    }
                }
            }
        }
    }
}

अटल व्योम Wayland_SortOutputs(SDL_Video_तथ्य *vid)
{
    // Sort by position or connector name, so the order of outputs is deterministic.
    SDL_qsort(vid->output_list, vid->output_गिनती, माप(SDL_Display_तथ्य *), Wayland_DisplayPositionCompare);

    // Derive the output pixel coordinates if scale to display is enabled.
    अगर (vid->scale_to_display_enabled) {
        Wayland_DeriveOutputPixelCoordinates(vid);
    }

    // Find a suitable primary display and move it to the front of the list.
    स्थिर पूर्णांक primary_सूचकांक = Wayland_GetPrimaryDisplay(vid);
    अगर (primary_सूचकांक) {
        SDL_Display_तथ्य *primary = vid->output_list[primary_सूचकांक];
        SDL_memmove(&vid->output_list[1], &vid->output_list[0], माप(SDL_Display_तथ्य *) * primary_सूचकांक);
        vid->output_list[0] = primary;
    }

    // Apply the ordering hint, if specified.
    Wayland_SortOutputsByPriorityHint(vid);
}

अटल व्योम Wayland_RefreshWindowPositions()
{
    SDL_VideoDevice *vid = SDL_GetVideoDevice();

    क्रम (SDL_Window *w = vid->windows; w; w = w->अग्र) {
        Wayland_UpdateWindowPosition(w);
    }
}

अटल व्योम handle_wl_output_done(व्योम *तथ्य, काष्ठा wl_output *output);

// Initialization/Query functions
अटल bool Wayland_VideoInit(SDL_VideoDevice *_this);
अटल bool Wayland_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
अटल व्योम Wayland_VideoQuit(SDL_VideoDevice *_this);

अटल स्थिर अक्षर *SDL_WAYLAND_surface_tag = "sdl-window";
अटल स्थिर अक्षर *SDL_WAYLAND_output_tag = "sdl-output";

व्योम SDL_WAYLAND_register_surface(काष्ठा wl_surface *surface)
{
    wl_proxy_set_tag((काष्ठा wl_proxy *)surface, &SDL_WAYLAND_surface_tag);
}

व्योम SDL_WAYLAND_register_output(काष्ठा wl_output *output)
{
    wl_proxy_set_tag((काष्ठा wl_proxy *)output, &SDL_WAYLAND_output_tag);
}

bool SDL_WAYLAND_own_surface(काष्ठा wl_surface *surface)
{
    वापस wl_proxy_get_tag((काष्ठा wl_proxy *)surface) == &SDL_WAYLAND_surface_tag;
}

bool SDL_WAYLAND_own_output(काष्ठा wl_output *output)
{
    वापस wl_proxy_get_tag((काष्ठा wl_proxy *)output) == &SDL_WAYLAND_output_tag;
}

/* External surfaces may have their own user data attached, the modification of which
 * can cause problems with external toolkits. Instead, external windows are kept in
 * their own list, and a search is conducted to find a matching surface.
 */
अटल काष्ठा wl_list external_window_list;

व्योम Wayland_Add_Window_तथ्य_To_External_List(SDL_Window_तथ्य *तथ्य)
{
    WAYLAND_wl_list_जोड़ो(&external_window_list, &तथ्य->external_window_list_link);
}

व्योम Wayland_Remove_Window_तथ्य_From_External_List(SDL_Window_तथ्य *तथ्य)
{
    WAYLAND_wl_list_remove(&तथ्य->external_window_list_link);
}

SDL_Window_तथ्य *Wayland_Get_Window_तथ्य_For_Owned_Surface(काष्ठा wl_surface *surface)
{
    अगर (SDL_WAYLAND_own_surface(surface)) {
        वापस (SDL_Window_तथ्य *)wl_surface_get_user_तथ्य(surface);
    } अन्यथा अगर (!WAYLAND_wl_list_empty(&external_window_list)) {
        SDL_Window_तथ्य *p;
        wl_list_for_each (p, &external_window_list, external_window_list_link) {
            अगर (p->surface == surface) {
                वापस p;
            }
        }
    }

    वापस शून्य;
}

काष्ठा wl_event_queue *Wayland_DisplayCreateQueue(काष्ठा wl_display *display, स्थिर अक्षर *name)
{
#अगर_घोषित SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
    अगर (WAYLAND_wl_display_create_queue_with_name) {
        वापस WAYLAND_wl_display_create_queue_with_name(display, name);
    }
#या_अगर SDL_WAYLAND_CHECK_VERSION(1, 23, 0)
    वापस WAYLAND_wl_display_create_queue_with_name(display, name);
#पूर्ण_अगर
    वापस WAYLAND_wl_display_create_queue(display);
}

अटल व्योम Wayland_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_Video_तथ्य *तथ्य = device->internal;
    अगर (तथ्य->display && !तथ्य->display_externally_owned) {
        WAYLAND_wl_display_disconnect(तथ्य->display);
        SDL_ClearProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_POINTER);
    }
    SDL_free(तथ्य);
    SDL_free(device);
    SDL_WAYLAND_UnloadSymbols();
}

प्रकार काष्ठा
{
    bool has_fifo_v1;
    काष्ठा wl_fixes *wl_fixes;
} SDL_Wayland_Preferred_तथ्य;

अटल व्योम wayland_preferred_check_handle_global(व्योम *तथ्य, काष्ठा wl_registry *registry, uint32_t id,
                                                  स्थिर अक्षर *interface, uint32_t version)
{
    SDL_Wayland_Preferred_तथ्य *d = तथ्य;

    अगर (SDL_strcmp(interface, "wp_fifo_manager_v1") == 0) {
        d->has_fifo_v1 = true;
    }
#अगर_घोषित SDL_WL_FIXES_VERSION
    अन्यथा अगर (SDL_strcmp(interface, wl_fixes_interface.name) == 0) {
        d->wl_fixes = wl_registry_bind(registry, id, &wl_fixes_interface, SDL_min(SDL_WL_FIXES_VERSION, version));
    }
#पूर्ण_अगर
}

अटल व्योम wayland_preferred_check_remove_global(व्योम *तथ्य, काष्ठा wl_registry *registry, uint32_t id)
{
    SDL_Wayland_Preferred_तथ्य *d = (SDL_Wayland_Preferred_तथ्य *)तथ्य;

    अगर (d->wl_fixes && wl_fixes_get_version(d->wl_fixes) >= WL_FIXES_ACK_GLOBAL_REMOVE_SINCE_VERSION) {
        wl_fixes_ack_global_remove(d->wl_fixes, registry, id);
    }
}

अटल स्थिर काष्ठा wl_registry_listener preferred_registry_listener = {
    wayland_preferred_check_handle_global,
    wayland_preferred_check_remove_global
};

अटल bool Wayland_IsPreferred(काष्ठा wl_display *display)
{
    काष्ठा wl_registry *registry = wl_display_get_registry(display);
    SDL_Wayland_Preferred_तथ्य preferred_तथ्य = { 0 };

    अगर (!registry) {
        SDL_SetError("Failed to get the Wayland registry");
        वापस false;
    }

    wl_registry_add_listener(registry, &preferred_registry_listener, &preferred_तथ्य);

    WAYLAND_wl_display_roundtrip(display);

    अगर (preferred_तथ्य.wl_fixes) {
        wl_fixes_destroy_registry(preferred_तथ्य.wl_fixes, registry);
        wl_fixes_destroy(preferred_तथ्य.wl_fixes);
    }
    wl_registry_destroy(registry);

    अगर (!preferred_तथ्य.has_fifo_v1) {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "This compositor lacks support for the fifo-v1 protocol; falling back to XWayland for GPU performance reasons (set SDL_VIDEO_DRIVER=wayland to override)");
    }
    वापस preferred_तथ्य.has_fifo_v1;
}

अटल SDL_VideoDevice *Wayland_CreateDevice(bool require_preferred_protocols)
{
    SDL_VideoDevice *device;
    SDL_Video_तथ्य *तथ्य;
    काष्ठा wl_display *display = SDL_GetPointerProperty(SDL_GetGlobalProperties(),
                                                 SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_POINTER, शून्य);
    bool display_is_external = !!display;

    // Are we trying to connect to, or are currently in, a Wayland session?
    अगर (!SDL_getenv("WAYLAND_DISPLAY")) {
        स्थिर अक्षर *session = SDL_getenv("XDG_SESSION_TYPE");
        अगर (session && SDL_strcasecmp(session, "wayland") != 0) {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Wayland initialization failed: no Wayland session available");
            वापस शून्य;
        }
    }

    अगर (!SDL_WAYLAND_LoadSymbols()) {
        वापस शून्य;
    }

    अगर (!display) {
        display = WAYLAND_wl_display_connect(शून्य);
        अगर (!display) {
            SDL_WAYLAND_UnloadSymbols();
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to connect to the Wayland display server: %s", म_त्रुटि(त्रुटि_सं));
            वापस शून्य;
        }
    }

    /*
     * If we are checking for preferred Wayland, then let's query for
     * fifo-v1's existence, so we don't regress GPU-bound performance
     * and frame-pacing by default due to swapchain starvation.
     */
    अगर (require_preferred_protocols && !Wayland_IsPreferred(display)) {
        अगर (!display_is_external) {
            WAYLAND_wl_display_disconnect(display);
        }
        SDL_WAYLAND_UnloadSymbols();
        वापस शून्य;
    }

    तथ्य = SDL_calloc(1, माप(*तथ्य));
    अगर (!तथ्य) {
        अगर (!display_is_external) {
            WAYLAND_wl_display_disconnect(display);
        }
        SDL_WAYLAND_UnloadSymbols();
        वापस शून्य;
    }

    तथ्य->initializing = true;
    तथ्य->display = display;
    तथ्य->display_externally_owned = display_is_external;
    तथ्य->scale_to_display_enabled = SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_SCALE_TO_DISPLAY, false);
    WAYLAND_wl_list_init(&तथ्य->seat_list);
    WAYLAND_wl_list_init(&external_window_list);

    // Initialize all variables that we clean on shutdown
    device = SDL_calloc(1, माप(SDL_VideoDevice));
    अगर (!device) {
        SDL_free(तथ्य);
        अगर (!display_is_external) {
            WAYLAND_wl_display_disconnect(display);
        }
        SDL_WAYLAND_UnloadSymbols();
        वापस शून्य;
    }

    अगर (!display_is_external) {
        SDL_SetPointerProperty(SDL_GetGlobalProperties(),
                               SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_POINTER, display);
    }

    device->internal = तथ्य;

    // Set the function pointers
    device->VideoInit = Wayland_VideoInit;
    device->VideoQuit = Wayland_VideoQuit;
    device->GetDisplayBounds = Wayland_GetDisplayBounds;
    device->SuspendScreenSaver = Wayland_SuspendScreenSaver;

    device->PumpEvents = Wayland_PumpEvents;
    device->WaitEventTimeout = Wayland_WaitEventTimeout;
    device->SendWakeupEvent = Wayland_SendWakeupEvent;

#अगर_घोषित SDL_VIDEO_OPENGL_EGL
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
#पूर्ण_अगर

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
    device->Set_Window_आकार = Wayland_Set_Window_आकार;
    device->SetWindowAspectRatio = Wayland_SetWindowAspectRatio;
    device->Set_Window_Minimum_आकार = Wayland_Set_Window_Minimum_आकार;
    device->Set_Window_Maximum_आकार = Wayland_Set_Window_Maximum_आकार;
    device->SetWindowParent = Wayland_SetWindowParent;
    device->SetWindowModal = Wayland_SetWindowModal;
    device->SetWindowOpacity = Wayland_SetWindowOpacity;
    device->SetWindowTitle = Wayland_SetWindowTitle;
    device->SetWindowIcon = Wayland_SetWindowIcon;
    device->Get_Window_आकार_In_Pixels = Wayland_Get_Window_आकार_In_Pixels;
    device->GetWindowContentScale = Wayland_GetWindowContentScale;
    device->GetWindowICCProfile = Wayland_GetWindowICCProfile;
    device->GetDisplayForWindow = Wayland_GetDisplayForWindow;
    device->DestroyWindow = Wayland_DestroyWindow;
    device->SetWindowHitTest = Wayland_SetWindowHitTest;
    device->FlashWindow = Wayland_FlashWindow;
#अगर_घोषित SDL_USE_LIBDBUS
    device->ApplyWindowProgress = DBUS_ApplyWindowProgress;
#पूर्ण_अगर // SDL_USE_LIBDBUS
    device->HasScreenKeyboardSupport = Wayland_HasScreenKeyboardSupport;
    device->ShowWindowSystemMenu = Wayland_ShowWindowSystemMenu;
    device->SyncWindow = Wayland_SyncWindow;
    device->SetWindowFocusable = Wayland_SetWindowFocusable;
    device->ReconfigureWindow = Wayland_ReconfigureWindow;
    device->AcceptDragAndDrop = Wayland_AcceptDragAndDrop;

#अगर_घोषित SDL_USE_LIBDBUS
    अगर (SDL_SystemTheme_Init())
        device->system_theme = SDL_SystemTheme_Get();
#पूर्ण_अगर

    device->GetTextMimeTypes = Wayland_GetTextMimeTypes;
    device->Set_Clipboard_तथ्य = Wayland_Set_Clipboard_तथ्य;
    device->Get_Clipboard_तथ्य = Wayland_Get_Clipboard_तथ्य;
    device->Has_Clipboard_तथ्य = Wayland_Has_Clipboard_तथ्य;
    device->Start_Text_निवेश = Wayland_Start_Text_निवेश;
    device->Stop_Text_निवेश = Wayland_Stop_Text_निवेश;
    device->Update_Text_निवेश_Area = Wayland_Update_Text_निवेश_Area;

#अगर_घोषित SDL_VIDEO_VULKAN
    device->Vulkan_LoadLibrary = Wayland_Vulkan_LoadLibrary;
    device->Vulkan_UnloadLibrary = Wayland_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = Wayland_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = Wayland_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = Wayland_Vulkan_DestroySurface;
    device->Vulkan_GetPresentationSupport = Wayland_Vulkan_GetPresentationSupport;
#पूर्ण_अगर

    device->मुक्त = Wayland_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_MODE_SWITCHING_EMULATED |
                          VIDEO_DEVICE_CAPS_HAS_POPUP_WINDOW_SUPPORT |
                          VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS |
                          VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES |
                          VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES;

    वापस device;
}

अटल SDL_VideoDevice *Wayland_Preferred_CreateDevice(व्योम)
{
    वापस Wayland_CreateDevice(true);
}

अटल SDL_VideoDevice *Wayland_Fallback_CreateDevice(व्योम)
{
    वापस Wayland_CreateDevice(false);
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

अटल व्योम handle_xdg_output_logical_position(व्योम *तथ्य, काष्ठा zxdg_output_v1 *xdg_output, int32_t x, int32_t y)
{
    SDL_Display_तथ्य *internal = (SDL_Display_तथ्य *)तथ्य;

    internal->geometry_changed |= internal->logical.x != x || internal->logical.y != y;
    internal->logical.x = x;
    internal->logical.y = y;
    internal->has_logical_position = true;
}

अटल व्योम handle_xdg_output_logical_आकार(व्योम *तथ्य, काष्ठा zxdg_output_v1 *xdg_output, int32_t width, int32_t height)
{
    SDL_Display_तथ्य *internal = (SDL_Display_तथ्य *)तथ्य;

    internal->geometry_changed |= internal->logical.width != width || internal->logical.height != height;
    internal->logical.width = width;
    internal->logical.height = height;
    internal->has_logical_आकार = true;
}

अटल व्योम handle_xdg_output_done(व्योम *तथ्य, काष्ठा zxdg_output_v1 *xdg_output)
{
    SDL_Display_तथ्य *internal = तथ्य;

    /*
     * xdg-output.done events are deprecated and only apply below version 3 of the protocol.
     * A wl-output.done event will be emitted in version 3 or higher.
     */
    अगर (zxdg_output_v1_get_version(internal->xdg_output) < 3) {
        handle_wl_output_done(तथ्य, internal->output);
    }
}

अटल व्योम handle_xdg_output_name(व्योम *तथ्य, काष्ठा zxdg_output_v1 *xdg_output, स्थिर अक्षर *name)
{
    SDL_Display_तथ्य *internal = (SDL_Display_तथ्य *)तथ्य;

    // Deprecated as of wl_output v4.
    अगर (wl_output_get_version(internal->output) < WL_OUTPUT_NAME_SINCE_VERSION &&
        internal->display == 0) {
        SDL_free(internal->wl_output_name);
        internal->wl_output_name = SDL_strdup(name);
    }
}

अटल व्योम handle_xdg_output_description(व्योम *तथ्य, काष्ठा zxdg_output_v1 *xdg_output, स्थिर अक्षर *description)
{
    SDL_Display_तथ्य *internal = (SDL_Display_तथ्य *)तथ्य;

    // Deprecated as of wl_output v4.
    अगर (wl_output_get_version(internal->output) < WL_OUTPUT_DESCRIPTION_SINCE_VERSION &&
        internal->display == 0) {
        // xdg-output descriptions, if available, supersede wl-output model names.
        SDL_free(internal->placeholder.name);
        internal->placeholder.name = SDL_strdup(description);
    }
}

अटल स्थिर काष्ठा zxdg_output_v1_listener xdg_output_listener = {
    handle_xdg_output_logical_position,
    handle_xdg_output_logical_आकार,
    handle_xdg_output_done,
    handle_xdg_output_name,
    handle_xdg_output_description,
};

अटल व्योम AddEmulatedModes(SDL_Display_तथ्य *dispdata, पूर्णांक native_width, पूर्णांक native_height)
{
    काष्ठा EmulatedMode
    {
        पूर्णांक w;
        पूर्णांक h;
    };

    // Resolution lists courtesy of XWayland
    स्थिर काष्ठा EmulatedMode mode_list[] = {
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

    पूर्णांक i;
    SDL_DisplayMode mode;
    SDL_VideoDisplay *dpy = dispdata->display ? SDL_GetVideoDisplay(dispdata->display) : &dispdata->placeholder;
    स्थिर bool rot_90 = native_width < native_height; // Reverse width/height for portrait displays.

    क्रम (i = 0; i < SDL_arraysize(mode_list); ++i) {
        SDL_zero(mode);
        mode.format = dpy->desktop_mode.format;
        mode.refresh_rate_numerator = dpy->desktop_mode.refresh_rate_numerator;
        mode.refresh_rate_denominator = dpy->desktop_mode.refresh_rate_denominator;

        अगर (rot_90) {
            mode.w = mode_list[i].h;
            mode.h = mode_list[i].w;
        } अन्यथा {
            mode.w = mode_list[i].w;
            mode.h = mode_list[i].h;
        }

        // Only add modes that are smaller than the native mode.
        अगर ((mode.w < native_width && mode.h < native_height) ||
            (mode.w < native_width && mode.h == native_height) ||
            (mode.w == native_width && mode.h < native_height)) {
            SDL_AddFullscreenDisplayMode(dpy, &mode);
        }
    }
}

अटल व्योम handle_wl_output_geometry(व्योम *तथ्य, काष्ठा wl_output *output, पूर्णांक x, पूर्णांक y,
                                      पूर्णांक physical_width, पूर्णांक physical_height, पूर्णांक subpixel,
                                      स्थिर अक्षर *make, स्थिर अक्षर *model, पूर्णांक transform)
{
    SDL_Display_तथ्य *internal = (SDL_Display_तथ्य *)तथ्य;

    // Apply the change from wl-output only if xdg-output is not supported
    अगर (!internal->has_logical_position) {
        internal->geometry_changed |= internal->logical.x != x || internal->logical.y != y;
        internal->logical.x = x;
        internal->logical.y = y;
    }
    internal->physical.width_mm = physical_width;
    internal->physical.height_mm = physical_height;

    // The model is only used for the output name if wl_output or xdg-output haven't provided a description.
    अगर (internal->display == 0 && !internal->placeholder.name) {
        internal->placeholder.name = SDL_strdup(model);
    }

    internal->transform = transform;
#घोषणा TF_CASE(in, out)                                 \
    हाल WL_OUTPUT_TRANSFORM_##in:                       \
        internal->orientation = SDL_ORIENTATION_##out; \
        अवरोध;
    अगर (internal->physical.width_mm >= internal->physical.height_mm) {
        चयन (transform) {
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
        चयन (transform) {
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
#अघोषित TF_CASE
}

अटल व्योम handle_wl_output_mode(व्योम *तथ्य, काष्ठा wl_output *output, uint32_t flags,
                                  पूर्णांक width, पूर्णांक height, पूर्णांक refresh)
{
    SDL_Display_तथ्य *internal = (SDL_Display_तथ्य *)तथ्य;

    अगर (flags & WL_OUTPUT_MODE_CURRENT) {
        internal->geometry_changed |= internal->pixel.width != width || internal->pixel.height != height;
        internal->pixel.width = width;
        internal->pixel.height = height;

        /*
         * Don't rotate this yet, wl-output coordinates are transformed in
         * handle_done and xdg-output coordinates are pre-transformed.
         */
        अगर (!internal->has_logical_आकार) {
            internal->geometry_changed |= internal->logical.width != width || internal->logical.height != height;
            internal->logical.width = width;
            internal->logical.height = height;
        }

        internal->refresh = refresh;
    }
}

अटल व्योम handle_wl_output_done(व्योम *तथ्य, काष्ठा wl_output *output)
{
    स्थिर bool mode_emulation_enabled = SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_MODE_EMULATION, true);
    SDL_Display_तथ्य *internal = (SDL_Display_तथ्य *)तथ्य;
    SDL_Video_तथ्य *video = internal->videodata;
    SDL_DisplayMode native_mode, desktop_mode;

    /*
     * When using xdg-output, two wl-output.done events will be emitted:
     * one at the completion of wl-display and one at the completion of xdg-output.
     *
     * All required events must be received before proceeding.
     */
    स्थिर पूर्णांक event_await_गिनती = 1 + (internal->xdg_output != शून्य);

    internal->wl_output_done_गिनती = SDL_min(internal->wl_output_done_गिनती + 1, event_await_गिनती + 1);

    अगर (internal->wl_output_done_गिनती < event_await_गिनती) {
        वापस;
    }

    // If the display was already created, reset and rebuild the mode list.
    SDL_VideoDisplay *dpy = SDL_GetVideoDisplay(internal->display);
    अगर (dpy) {
        SDL_ResetFullscreenDisplayModes(dpy);
    }

    // The native display resolution
    SDL_zero(native_mode);
    native_mode.format = SDL_PIXELFORMAT_XRGB8888;

    // Transform the pixel values, if necessary.
    अगर (internal->transform & WL_OUTPUT_TRANSFORM_90) {
        native_mode.w = internal->pixel.height;
        native_mode.h = internal->pixel.width;
    } अन्यथा {
        native_mode.w = internal->pixel.width;
        native_mode.h = internal->pixel.height;
    }
    native_mode.refresh_rate_numerator = internal->refresh;
    native_mode.refresh_rate_denominator = 1000;

    अगर (internal->has_logical_आकार) { // If xdg-output is present...
        अगर (native_mode.w != internal->logical.width || native_mode.h != internal->logical.height) {
            // ...and the compositor scales the logical viewport...
            अगर (video->viewporter) {
                // ...and viewports are supported, calculate the true scale of the output.
                internal->scale_factor = (द्विगुन)native_mode.w / (द्विगुन)internal->logical.width;
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

    अगर (!video->scale_to_display_enabled) {
        desktop_mode.w = internal->logical.width;
        desktop_mode.h = internal->logical.height;
        desktop_mode.pixel_density = (भग्न)internal->scale_factor;
    } अन्यथा {
        desktop_mode.w = native_mode.w;
        desktop_mode.h = native_mode.h;
        desktop_mode.pixel_density = 1.0f;
    }

    desktop_mode.refresh_rate_numerator = internal->refresh;
    desktop_mode.refresh_rate_denominator = 1000;

    अगर (internal->display > 0) {
        dpy = SDL_GetVideoDisplay(internal->display);
    } अन्यथा {
        dpy = &internal->placeholder;
    }

    अगर (video->scale_to_display_enabled) {
        SDL_SetDisplayContentScale(dpy, (भग्न)internal->scale_factor);
    }

    // Set the desktop display mode.
    SDL_SetDesktopDisplayMode(dpy, &desktop_mode);

    // Expose the unscaled, native resolution if the scale is 1.0 or viewports are available...
    अगर (internal->scale_factor == 1.0 || video->viewporter) {
        SDL_AddFullscreenDisplayMode(dpy, &native_mode);
        अगर (native_mode.w != desktop_mode.w ||
            native_mode.h != desktop_mode.h) {
            SDL_AddFullscreenDisplayMode(dpy, &desktop_mode);
        }
    } अन्यथा {
        // ...otherwise expose the integer scaled variants of the desktop resolution down to 1.
        desktop_mode.pixel_density = 1.0f;

        क्रम (पूर्णांक i = (पूर्णांक)internal->scale_factor; i > 0; --i) {
            desktop_mode.w = internal->logical.width * i;
            desktop_mode.h = internal->logical.height * i;
            SDL_AddFullscreenDisplayMode(dpy, &desktop_mode);
        }
    }

    // Add emulated modes if wp_viewporter is supported and mode emulation is enabled.
    अगर (video->viewporter && mode_emulation_enabled) {
        // The transformed display pixel width/height must be used here.
        AddEmulatedModes(internal, native_mode.w, native_mode.h);
    }

    अगर (internal->display == 0) {
        // First time getting display info, initialize the VideoDisplay
        अगर (internal->physical.width_mm >= internal->physical.height_mm) {
            internal->placeholder.natural_orientation = SDL_ORIENTATION_LANDSCAPE;
        } अन्यथा {
            internal->placeholder.natural_orientation = SDL_ORIENTATION_PORTRAIT;
        }
        internal->placeholder.current_orientation = internal->orientation;
        internal->placeholder.internal = internal;

        internal->placeholder.props = SDL_CreateProperties();
        SDL_SetPointerProperty(internal->placeholder.props, SDL_PROP_DISPLAY_WAYLAND_WL_OUTPUT_POINTER, internal->output);

        // During initialization, the displays will be added after enumeration is complete.
        अगर (!video->initializing) {
            अगर (video->wp_color_manager_v1) {
                Wayland_GetColorInfoForOutput(internal, false);
            }
            अगर (video->scale_to_display_enabled) {
                Wayland_DeriveOutputPixelCoordinates(video);
            }

            internal->display = SDL_AddVideoDisplay(&internal->placeholder, true);
            Wayland_RefreshWindowPositions();

            SDL_free(internal->placeholder.name);
            SDL_zero(internal->placeholder);
        }
    } अन्यथा {
        SDL_SendDisplayEvent(dpy, SDL_EVENT_DISPLAY_ORIENTATION, internal->orientation, 0);

        अगर (internal->geometry_changed) {
            अगर (video->scale_to_display_enabled) {
                Wayland_DeriveOutputPixelCoordinates(video);
            }

            SDL_SendDisplayEvent(dpy, SDL_EVENT_DISPLAY_MOVED, 0, 0);
            Wayland_RefreshWindowPositions();
        }
    }

    internal->geometry_changed = false;
}

अटल व्योम handle_wl_output_scale(व्योम *तथ्य, काष्ठा wl_output *output, int32_t factor)
{
    SDL_Display_तथ्य *internal = (SDL_Display_तथ्य *)तथ्य;
    internal->integer_scale_factor = factor;
}

अटल व्योम handle_wl_output_name(व्योम *तथ्य, काष्ठा wl_output *wl_output, स्थिर अक्षर *name)
{
    SDL_Display_तथ्य *internal = (SDL_Display_तथ्य *)तथ्य;

    SDL_free(internal->wl_output_name);
    internal->wl_output_name = SDL_strdup(name);
}

अटल व्योम handle_wl_output_description(व्योम *तथ्य, काष्ठा wl_output *wl_output, स्थिर अक्षर *description)
{
    SDL_Display_तथ्य *internal = (SDL_Display_तथ्य *)तथ्य;

    अगर (internal->display == 0) {
        // The description, if available, supersedes the model name.
        SDL_free(internal->placeholder.name);
        internal->placeholder.name = SDL_strdup(description);
    }
}

अटल स्थिर काष्ठा wl_output_listener output_listener = {
    handle_wl_output_geometry,   // Version 1
    handle_wl_output_mode,       // Version 1
    handle_wl_output_done,       // Version 2
    handle_wl_output_scale,      // Version 2
    handle_wl_output_name,       // Version 4
    handle_wl_output_description // Version 4
};

अटल व्योम handle_output_image_description_changed(व्योम *तथ्य,
                                                    काष्ठा wp_color_management_output_v1 *wp_color_management_output_v1)
{
    SDL_Display_तथ्य *display = (SDL_Display_तथ्य *)तथ्य;
    Wayland_GetColorInfoForOutput(display, false);
}

अटल स्थिर काष्ठा wp_color_management_output_v1_listener wp_color_management_output_listener = {
    handle_output_image_description_changed
};

अटल bool Wayland_add_display(SDL_Video_तथ्य *d, uint32_t id, uint32_t version)
{
    काष्ठा wl_output *output;
    SDL_Display_तथ्य *तथ्य;

    output = wl_registry_bind(d->registry, id, &wl_output_interface, version);
    अगर (!output) {
        वापस SDL_SetError("Failed to retrieve output.");
    }
    तथ्य = (SDL_Display_तथ्य *)SDL_calloc(1, माप(*तथ्य));
    तथ्य->videodata = d;
    तथ्य->output = output;
    तथ्य->registry_id = id;
    तथ्य->scale_factor = 1.0f;
    तथ्य->integer_scale_factor = 1;

    wl_output_add_listener(output, &output_listener, तथ्य);
    SDL_WAYLAND_register_output(output);

    // Keep a list of outputs for sorting and deferred protocol initialization.
    अगर (d->output_गिनती == d->output_max) {
        d->output_max += 4;
        d->output_list = SDL_realloc(d->output_list, माप(SDL_Display_तथ्य *) * d->output_max);
    }
    d->output_list[d->output_गिनती++] = तथ्य;

    अगर (तथ्य->videodata->xdg_output_manager) {
        तथ्य->xdg_output = zxdg_output_manager_v1_get_xdg_output(तथ्य->videodata->xdg_output_manager, output);
        zxdg_output_v1_add_listener(तथ्य->xdg_output, &xdg_output_listener, तथ्य);
    }
    अगर (तथ्य->videodata->wp_color_manager_v1) {
        तथ्य->wp_color_management_output = wp_color_manager_v1_get_output(तथ्य->videodata->wp_color_manager_v1, output);
        wp_color_management_output_v1_add_listener(तथ्य->wp_color_management_output, &wp_color_management_output_listener, तथ्य);

        // If not initializing, this will be queried synchronously in wl_output.done.
        अगर (d->initializing) {
            Wayland_GetColorInfoForOutput(तथ्य, true);
        }
    }
    वापस true;
}

अटल व्योम Wayland_free_display(SDL_VideoDisplay *display, bool send_event)
{
    अगर (display) {
        SDL_Display_तथ्य *display_तथ्य = display->internal;

        /* A preceding surface leave event is not guaranteed when an output is removed,
         * so ensure that no window continues to hold a reference to a removed output.
         */
        क्रम (SDL_Window *window = SDL_GetVideoDevice()->windows; window; window = window->अग्र) {
            Wayland_RemoveOutputFromWindow(window->internal, display_तथ्य);
        }

        SDL_free(display_तथ्य->wl_output_name);

        अगर (display_तथ्य->wp_color_management_output) {
            Wayland_FreeColorInfoState(display_तथ्य->color_info_state);
            wp_color_management_output_v1_destroy(display_तथ्य->wp_color_management_output);
        }

        अगर (display_तथ्य->xdg_output) {
            zxdg_output_v1_destroy(display_तथ्य->xdg_output);
        }

        अगर (wl_output_get_version(display_तथ्य->output) >= WL_OUTPUT_RELEASE_SINCE_VERSION) {
            wl_output_release(display_तथ्य->output);
        } अन्यथा {
            wl_output_destroy(display_तथ्य->output);
        }

        SDL_DelVideoDisplay(display->id, send_event);
    }
}

अटल व्योम Wayland_FinalizeDisplays(SDL_Video_तथ्य *vid)
{
    Wayland_SortOutputs(vid);

    क्रम(पूर्णांक i = 0; i < vid->output_गिनती; ++i) {
        SDL_Display_तथ्य *d = vid->output_list[i];
        d->display = SDL_AddVideoDisplay(&d->placeholder, false);
        SDL_free(d->placeholder.name);
        SDL_zero(d->placeholder);
    }
}

अटल व्योम Wayland_init_xdg_output(SDL_Video_तथ्य *d)
{
    क्रम (पूर्णांक i = 0; i < d->output_गिनती; ++i) {
        SDL_Display_तथ्य *disp = d->output_list[i];
        disp->xdg_output = zxdg_output_manager_v1_get_xdg_output(disp->videodata->xdg_output_manager, disp->output);
        zxdg_output_v1_add_listener(disp->xdg_output, &xdg_output_listener, disp);
    }
}

अटल व्योम Wayland_InitColorManager(SDL_Video_तथ्य *d)
{
    क्रम (पूर्णांक i = 0; i < d->output_गिनती; ++i) {
        SDL_Display_तथ्य *disp = d->output_list[i];
        disp->wp_color_management_output = wp_color_manager_v1_get_output(disp->videodata->wp_color_manager_v1, disp->output);
        wp_color_management_output_v1_add_listener(disp->wp_color_management_output, &wp_color_management_output_listener, disp);
        Wayland_GetColorInfoForOutput(disp, true);
    }
}

अटल व्योम handle_xdg_session_created(व्योम *तथ्य, काष्ठा xdg_session_v1 *xdg_session_v1, स्थिर अक्षर *id)
{
    SDL_SetStringProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, id);
}

अटल व्योम handle_xdg_session_restored(व्योम *तथ्य, काष्ठा xdg_session_v1 *xdg_session_v1)
{
    // NOP
}

अटल व्योम handle_xdg_session_replaced(व्योम *तथ्य, काष्ठा xdg_session_v1 *xdg_session_v1)
{
    SDL_VideoDevice *viddev = SDL_GetVideoDevice();
    SDL_Video_तथ्य *viddata = तथ्य;

    // Clean up all session objects, as they have become inert, and should be destroyed.
    SDL_SetStringProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, शून्य);

    क्रम (SDL_Window *w = viddev->windows; w; w = w->अग्र) {
        SDL_Window_तथ्य *d = w->internal;

        अगर (d->xdg_toplevel_session) {
            xdg_toplevel_session_v1_destroy(d->xdg_toplevel_session);
            d->xdg_toplevel_session = शून्य;

            SDL_free(d->session_id);
            d->session_id = शून्य;
        }
    }

    अगर (viddata->xdg_session) {
        xdg_session_v1_destroy(viddata->xdg_session);
        viddata->xdg_session = शून्य;
    }
}

अटल स्थिर काष्ठा xdg_session_v1_listener xdg_session_listener = {
    .created  = handle_xdg_session_created,
    .restored = handle_xdg_session_restored,
    .replaced = handle_xdg_session_replaced
};

व्योम Wayland_CreateSession(SDL_Video_तथ्य *viddata)
{
    अगर (!viddata->xdg_session_manager) {
        // Set the ID string to null if session management is not available.
        SDL_SetStringProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, शून्य);
        वापस;
    }

    // Register a new session, if one does not yet exist.
    अगर (!viddata->xdg_session) {
        स्थिर अक्षर *session_id = SDL_GetStringProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, शून्य);
        अगर (session_id) {
            अगर (*session_id == '\0') {
                // Create a new session if the ID string is empty.
                session_id = शून्य;
            }

            स्थिर क्रमागत xdg_session_manager_v1_reason reason = session_id ? XDG_SESSION_MANAGER_V1_REASON_SESSION_RESTORE : XDG_SESSION_MANAGER_V1_REASON_LAUNCH;
            viddata->xdg_session = xdg_session_manager_v1_get_session(viddata->xdg_session_manager, reason, session_id);
            xdg_session_v1_add_listener(viddata->xdg_session, &xdg_session_listener, viddata);
        }
    }
}

अटल व्योम Wayland_SessionDestroy(SDL_Video_तथ्य *viddata)
{
    // If the session string was cleared, remove the session.
    अगर (viddata->xdg_session) {
        स्थिर अक्षर *session_id = SDL_GetStringProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, शून्य);
        अगर (!session_id || *session_id == '\0') {
            xdg_session_v1_remove(viddata->xdg_session);

            WAYLAND_wl_display_roundtrip(viddata->display);
        } अन्यथा {
            xdg_session_v1_destroy(viddata->xdg_session);
        }

        viddata->xdg_session = शून्य;
    }
}

अटल व्योम handle_xdg_wm_base_ping(व्योम *तथ्य, काष्ठा xdg_wm_base *xdg, uint32_t serial)
{
    xdg_wm_base_pong(xdg, serial);
}

अटल स्थिर काष्ठा xdg_wm_base_listener _xdg_wm_base_listener = {
    handle_xdg_wm_base_ping
};

#अगर_घोषित HAVE_LIBDECOR_H
अटल व्योम libdecor_error(काष्ठा libdecor *context,
                           क्रमागत libdecor_error error,
                           स्थिर अक्षर *message)
{
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "libdecor error (%d): %s", error, message);
}

अटल काष्ठा libdecor_interface libdecor_interface = {
    libdecor_error
};
#पूर्ण_अगर

अटल व्योम handle_registry_global(व्योम *तथ्य, काष्ठा wl_registry *registry, uint32_t id,
                                   स्थिर अक्षर *interface, uint32_t version)
{
    SDL_Video_तथ्य *d = तथ्य;

    अगर (SDL_strcmp(interface, wl_compositor_interface.name) == 0) {
        d->compositor = wl_registry_bind(d->registry, id, &wl_compositor_interface, SDL_min(SDL_WL_COMPOSITOR_VERSION, version));
    } अन्यथा अगर (SDL_strcmp(interface, wl_subcompositor_interface.name) == 0) {
        d->subcompositor = wl_registry_bind(d->registry, id, &wl_subcompositor_interface, 1);
    } अन्यथा अगर (SDL_strcmp(interface, wl_output_interface.name) == 0) {
        Wayland_add_display(d, id, SDL_min(version, SDL_WL_OUTPUT_VERSION));
    } अन्यथा अगर (SDL_strcmp(interface, wl_seat_interface.name) == 0) {
        काष्ठा wl_seat *seat = wl_registry_bind(d->registry, id, &wl_seat_interface, SDL_min(SDL_WL_SEAT_VERSION, version));
        Wayland_DisplayCreateSeat(d, seat, id);
    } अन्यथा अगर (SDL_strcmp(interface, xdg_wm_base_interface.name) == 0) {
        d->shell.xdg = wl_registry_bind(d->registry, id, &xdg_wm_base_interface, SDL_min(version, 7));
        xdg_wm_base_add_listener(d->shell.xdg, &_xdg_wm_base_listener, शून्य);
    } अन्यथा अगर (SDL_strcmp(interface, wl_shm_interface.name) == 0) {
        d->shm = wl_registry_bind(registry, id, &wl_shm_interface, SDL_min(SDL_WL_SHM_VERSION, version));
    } अन्यथा अगर (SDL_strcmp(interface, zwp_relative_pointer_manager_v1_interface.name) == 0) {
        d->relative_pointer_manager = wl_registry_bind(d->registry, id, &zwp_relative_pointer_manager_v1_interface, 1);
    } अन्यथा अगर (SDL_strcmp(interface, zwp_pointer_constraints_v1_interface.name) == 0) {
        d->pointer_constraints = wl_registry_bind(d->registry, id, &zwp_pointer_constraints_v1_interface, 1);
    } अन्यथा अगर (SDL_strcmp(interface, zwp_keyboard_shortcuts_inhibit_manager_v1_interface.name) == 0) {
        d->कुंजी_inhibitor_manager = wl_registry_bind(d->registry, id, &zwp_keyboard_shortcuts_inhibit_manager_v1_interface, 1);
    } अन्यथा अगर (SDL_strcmp(interface, zwp_idle_inhibit_manager_v1_interface.name) == 0) {
        d->idle_inhibit_manager = wl_registry_bind(d->registry, id, &zwp_idle_inhibit_manager_v1_interface, 1);
    } अन्यथा अगर (SDL_strcmp(interface, xdg_activation_v1_interface.name) == 0) {
        d->activation_manager = wl_registry_bind(d->registry, id, &xdg_activation_v1_interface, 1);
    } अन्यथा अगर (SDL_strcmp(interface, zwp_text_निवेश_manager_v3_interface.name) == 0) {
        d->text_निवेश_manager = wl_registry_bind(d->registry, id, &zwp_text_निवेश_manager_v3_interface, 1);
        Wayland_Display_Init_Text_निवेश_Manager(d, id);
    } अन्यथा अगर (SDL_strcmp(interface, wl_तथ्य_device_manager_interface.name) == 0) {
        d->तथ्य_device_manager = wl_registry_bind(d->registry, id, &wl_तथ्य_device_manager_interface, SDL_min(3, version));
        Wayland_Display_Init_तथ्य_Device_Manager(d);
    } अन्यथा अगर (SDL_strcmp(interface, zwp_primary_selection_device_manager_v1_interface.name) == 0) {
        d->primary_selection_device_manager = wl_registry_bind(d->registry, id, &zwp_primary_selection_device_manager_v1_interface, 1);
        Wayland_DisplayInitPrimarySelectionDeviceManager(d);
    } अन्यथा अगर (SDL_strcmp(interface, zxdg_decoration_manager_v1_interface.name) == 0) {
        d->decoration_manager = wl_registry_bind(d->registry, id, &zxdg_decoration_manager_v1_interface, SDL_min(2, version));
    } अन्यथा अगर (SDL_strcmp(interface, zwp_tablet_manager_v2_interface.name) == 0) {
        d->tablet_manager = wl_registry_bind(d->registry, id, &zwp_tablet_manager_v2_interface, 1);
        Wayland_DisplayInitTabletManager(d);
    } अन्यथा अगर (SDL_strcmp(interface, zxdg_output_manager_v1_interface.name) == 0) {
        version = SDL_min(version, 3); // Versions 1 through 3 are supported.
        d->xdg_output_manager = wl_registry_bind(d->registry, id, &zxdg_output_manager_v1_interface, version);
        Wayland_init_xdg_output(d);
    } अन्यथा अगर (SDL_strcmp(interface, wp_viewporter_interface.name) == 0) {
        d->viewporter = wl_registry_bind(d->registry, id, &wp_viewporter_interface, 1);
    } अन्यथा अगर (SDL_strcmp(interface, wp_fractional_scale_manager_v1_interface.name) == 0) {
        d->fractional_scale_manager = wl_registry_bind(d->registry, id, &wp_fractional_scale_manager_v1_interface, 1);
    } अन्यथा अगर (SDL_strcmp(interface, zwp_निवेश_timestamps_manager_v1_interface.name) == 0) {
        d->निवेश_timestamps_manager = wl_registry_bind(d->registry, id, &zwp_निवेश_timestamps_manager_v1_interface, 1);
        Wayland_Display_Init_निवेश_Timestamp_Manager(d);
    } अन्यथा अगर (SDL_strcmp(interface, wp_cursor_shape_manager_v1_interface.name) == 0) {
        d->cursor_shape_manager = wl_registry_bind(d->registry, id, &wp_cursor_shape_manager_v1_interface, SDL_min(version, 2));
        Wayland_DisplayInitCursorShapeManager(d);
    } अन्यथा अगर (SDL_strcmp(interface, zxdg_exporter_v2_interface.name) == 0) {
        d->zxdg_exporter_v2 = wl_registry_bind(d->registry, id, &zxdg_exporter_v2_interface, 1);
    } अन्यथा अगर (SDL_strcmp(interface, xdg_wm_dialog_v1_interface.name) == 0) {
        d->xdg_wm_dialog_v1 = wl_registry_bind(d->registry, id, &xdg_wm_dialog_v1_interface, 1);
    } अन्यथा अगर (SDL_strcmp(interface, wp_alpha_modifier_v1_interface.name) == 0) {
        d->wp_alpha_modifier_v1 = wl_registry_bind(d->registry, id, &wp_alpha_modifier_v1_interface, 1);
    } अन्यथा अगर (SDL_strcmp(interface, xdg_toplevel_icon_manager_v1_interface.name) == 0) {
        d->xdg_toplevel_icon_manager_v1 = wl_registry_bind(d->registry, id, &xdg_toplevel_icon_manager_v1_interface, 1);
    } अन्यथा अगर (SDL_strcmp(interface, frog_color_management_factory_v1_interface.name) == 0) {
        d->frog_color_management_factory_v1 = wl_registry_bind(d->registry, id, &frog_color_management_factory_v1_interface, 1);
    } अन्यथा अगर (SDL_strcmp(interface, wp_color_manager_v1_interface.name) == 0) {
        d->wp_color_manager_v1 = wl_registry_bind(d->registry, id, &wp_color_manager_v1_interface, SDL_min(version, 2));
        Wayland_InitColorManager(d);
    } अन्यथा अगर (SDL_strcmp(interface, wp_pointer_warp_v1_interface.name) == 0) {
        d->wp_pointer_warp_v1 = wl_registry_bind(d->registry, id, &wp_pointer_warp_v1_interface, 1);
    } अन्यथा अगर (SDL_strcmp(interface, zwp_pointer_gestures_v1_interface.name) == 0) {
        d->zwp_pointer_gestures = wl_registry_bind(d->registry, id, &zwp_pointer_gestures_v1_interface, SDL_min(version, 3));
        Wayland_DisplayInitPointerGestureManager(d);
    } अन्यथा अगर (SDL_strcmp(interface, wp_single_pixel_बफर_manager_v1_interface.name) == 0) {
        d->single_pixel_बफर_manager = wl_registry_bind(d->registry, id, &wp_single_pixel_बफर_manager_v1_interface, 1);
    } अन्यथा अगर (SDL_strcmp(interface, xdg_session_manager_v1_interface.name) == 0) {
        d->xdg_session_manager = wl_registry_bind(d->registry, id, &xdg_session_manager_v1_interface, 1);
    } अन्यथा अगर (SDL_strcmp(interface, xdg_toplevel_tag_manager_v1_interface.name) == 0) {
        d->xdg_toplevel_tag_manager = wl_registry_bind(d->registry, id, &xdg_toplevel_tag_manager_v1_interface, 1);
    }
#अगर_घोषित SDL_WL_FIXES_VERSION
    अन्यथा अगर (SDL_strcmp(interface, wl_fixes_interface.name) == 0) {
        d->wl_fixes = wl_registry_bind(d->registry, id, &wl_fixes_interface, SDL_min(SDL_WL_FIXES_VERSION, version));
    }
#पूर्ण_अगर
}

अटल व्योम handle_registry_remove_global(व्योम *तथ्य, काष्ठा wl_registry *registry, uint32_t id)
{
    SDL_Video_तथ्य *d = तथ्य;

    // We don't get an interface, just an ID, so check outputs and seats.
    क्रम (पूर्णांक i = 0; i < d->output_गिनती; ++i) {
        SDL_Display_तथ्य *disp = d->output_list[i];
        अगर (disp->registry_id == id) {
            Wayland_free_display(SDL_GetVideoDisplay(disp->display), true);

            अगर (i < d->output_गिनती) {
                SDL_memmove(&d->output_list[i], &d->output_list[i + 1], माप(SDL_Display_तथ्य *) * (d->output_गिनती - i - 1));
            }

            d->output_गिनती--;
            जाओ ack_remove;
        }
    }

    SDL_WaylandSeat *seat, *अस्थायी;
    wl_list_for_each_safe (seat, अस्थायी, &d->seat_list, link) {
        अगर (seat->registry_id == id) {
            Wayland_SeatDestroy(seat, false);
            जाओ ack_remove;
        }
    }

ack_remove:
    अगर (d->wl_fixes && wl_fixes_get_version(d->wl_fixes) >= WL_FIXES_ACK_GLOBAL_REMOVE_SINCE_VERSION) {
        wl_fixes_ack_global_remove(d->wl_fixes, registry, id);
    }
}

अटल स्थिर काष्ठा wl_registry_listener registry_listener = {
    handle_registry_global,
    handle_registry_remove_global
};

#अगर_घोषित HAVE_LIBDECOR_H
अटल bool should_use_libdecor(SDL_Video_तथ्य *तथ्य, bool ignore_xdg)
{
    अगर (!SDL_WAYLAND_HAVE_WAYLAND_LIBDECOR) {
        वापस false;
    }

    अगर (SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_PREFER_LIBDECOR, false)) {
        वापस true;
    }

    अगर (ignore_xdg) {
        वापस true;
    }

    अगर (तथ्य->decoration_manager) {
        वापस false;
    }

    वापस true;
}

अटल व्योम LibdecorNew(SDL_Video_तथ्य *तथ्य)
{
    तथ्य->shell.libdecor = libdecor_new(तथ्य->display, &libdecor_interface);
}

// Called in another thread, but the UI thread is blocked in SDL_WaitThread
// during that time, so it should be OK to dereference data without locks
अटल पूर्णांक SDLCALL LibdecorNewInThread(व्योम *तथ्य)
{
    LibdecorNew((SDL_Video_तथ्य *)तथ्य);
    वापस 0;
}
#पूर्ण_अगर

#अगर_घोषित HAVE_GETRESUID
#घोषणा SDL_getresuid getresuid
#अन्यथा
// Non-POSIX, but Linux and some BSDs have it.
// To reduce the number of code paths, if getresuid() isn't available at
// compile-time, we behave as though it existed but failed at runtime.
अटल अंतरभूत पूर्णांक SDL_getresuid(uid_t *ruid, uid_t *euid, uid_t *suid) {
    त्रुटि_सं = ENOSYS;
    वापस -1;
}
#पूर्ण_अगर

#अगर_घोषित HAVE_GETRESGID
#घोषणा SDL_getresgid getresgid
#अन्यथा
// Same as getresuid() but for the primary group
अटल अंतरभूत पूर्णांक SDL_getresgid(gid_t *rgid, gid_t *egid, gid_t *sgid) {
    त्रुटि_सं = ENOSYS;
    वापस -1;
}
#पूर्ण_अगर

bool CanUseGtk(व्योम)
{
    // "Real", "effective" and "saved" IDs: see e.g. Linux credentials(7)
    uid_t ruid = -1, euid = -1, suid = -1;
    gid_t rgid = -1, egid = -1, sgid = -1;

    अगर (!SDL_GetHintBoolean("SDL_ENABLE_GTK", true)) {
        SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "Not using GTK due to hint");
        वापस false;
    }

    // This is intended to match the check in gtkmain.c, rather than being
    // an exhaustive check for having elevated privileges: as a result
    // we don't use Linux getauxval() or prctl PR_GET_DUMPABLE,
    // BSD issetugid(), or similar OS-specific detection

    अगर (SDL_getresuid(&ruid, &euid, &suid) != 0) {
        ruid = suid = getuid();
        euid = geteuid();
    }

    अगर (SDL_getresgid(&rgid, &egid, &sgid) != 0) {
        rgid = sgid = getgid();
        egid = getegid();
    }

    // Real ID != effective ID means we are setuid or setgid:
    // GTK will refuse to initialize, and instead will call exit().
    अगर (ruid != euid || rgid != egid) {
        SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "Not using GTK due to setuid/setgid");
        वापस false;
    }

    // Real ID != saved ID means we are setuid or setgid, we previously
    // dropped privileges, but we can regain them; this protects against
    // accidents but does not protect against arbitrary code execution.
    // Again, GTK will refuse to initialize if this is the case.
    अगर (ruid != suid || rgid != sgid) {
        SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "Not using GTK due to saved uid/gid");
        वापस false;
    }

    वापस true;
}

bool Wayland_LoadLibdecor(SDL_Video_तथ्य *तथ्य, bool ignore_xdg)
{
#अगर_घोषित HAVE_LIBDECOR_H
    अगर (तथ्य->shell.libdecor != शून्य) {
        वापस true; // Already loaded!
    }
    अगर (should_use_libdecor(तथ्य, ignore_xdg)) {
        अगर (CanUseGtk()) {
            LibdecorNew(तथ्य);
        } अन्यथा {
            // Intentionally initialize libdecor in a non-main thread
            // so that it will not use its GTK plugin, but instead will
            // fall back to the Cairo or dummy plugin
            SDL_Thread *thread = SDL_CreateThread(LibdecorNewInThread, "SDL_LibdecorNew", (व्योम *)तथ्य);
            // Note that the other thread now "owns" data until we have
            // waited for it, so don't touch data here
            SDL_WaitThread(thread, शून्य);
        }

        वापस तथ्य->shell.libdecor != शून्य;
    }
#पूर्ण_अगर
    वापस false;
}

bool Wayland_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;

    तथ्य->event_thread_context = Wayland_CreateEventThread(तथ्य, "SDL Event Thread Queue");
    अगर (!तथ्य->event_thread_context) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Failed to create event thread context");
    }

    तथ्य->job_thread_context = Wayland_CreateJobThread();
    अगर (!तथ्य->job_thread_context) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Failed to create job thread context");
    }

    तथ्य->xkb_context = WAYLAND_xkb_context_new(0);
    अगर (!तथ्य->xkb_context) {
        वापस SDL_SetError("Failed to create XKB context");
    }

    तथ्य->registry = wl_display_get_registry(तथ्य->display);
    अगर (!तथ्य->registry) {
        वापस SDL_SetError("Failed to get the Wayland registry");
    }

    wl_registry_add_listener(तथ्य->registry, &registry_listener, तथ्य);

    // First roundtrip to receive all registry objects.
    WAYLAND_wl_display_roundtrip(तथ्य->display);

    // Require viewports and xdg-output for display scaling.
    अगर (तथ्य->scale_to_display_enabled) {
        अगर (!तथ्य->viewporter) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Display scaling requires the missing 'wp_viewporter' protocol: disabling");
            तथ्य->scale_to_display_enabled = false;
        }
        अगर (!तथ्य->xdg_output_manager) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Display scaling requires the missing 'zxdg_output_manager_v1' protocol: disabling");
            तथ्य->scale_to_display_enabled = false;
        }
    }

    // Now that we have all the protocols, load libdecor if applicable
    Wayland_LoadLibdecor(तथ्य, false);

    // Second roundtrip to receive all output events.
    WAYLAND_wl_display_roundtrip(तथ्य->display);

    Wayland_FinalizeDisplays(तथ्य);

    Wayland_InitMouse(तथ्य);
    Wayland_InitKeyboard(_this);

    अगर (तथ्य->primary_selection_device_manager) {
        _this->SetPrimarySelectionText = Wayland_SetPrimarySelectionText;
        _this->GetPrimarySelectionText = Wayland_GetPrimarySelectionText;
        _this->HasPrimarySelectionText = Wayland_HasPrimarySelectionText;
    }

    तथ्य->initializing = false;

    वापस true;
}

अटल bool Wayland_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    SDL_Video_तथ्य *viddata = _this->internal;
    SDL_Display_तथ्य *internal = display->internal;

    अगर (!viddata->scale_to_display_enabled) {
        rect->x = internal->logical.x;
        rect->y = internal->logical.y;
    } अन्यथा {
        rect->x = internal->pixel.x;
        rect->y = internal->pixel.y;
    }

    // When an emulated, exclusive fullscreen window has focus, treat the mode dimensions as the display bounds.
    अगर (display->fullscreen_window &&
        display->fullscreen_window->fullscreen_exclusive &&
        display->fullscreen_window->internal->active &&
        display->fullscreen_window->current_fullscreen_mode.w != 0 &&
        display->fullscreen_window->current_fullscreen_mode.h != 0) {
        rect->w = display->fullscreen_window->current_fullscreen_mode.w;
        rect->h = display->fullscreen_window->current_fullscreen_mode.h;
    } अन्यथा {
        अगर (!viddata->scale_to_display_enabled) {
            rect->w = display->current_mode->w;
            rect->h = display->current_mode->h;
        } अन्यथा अगर (internal->transform & WL_OUTPUT_TRANSFORM_90) {
            rect->w = internal->pixel.height;
            rect->h = internal->pixel.width;
        } अन्यथा {
            rect->w = internal->pixel.width;
            rect->h = internal->pixel.height;
        }
    }
    वापस true;
}

अटल व्योम Wayland_VideoCleanup(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;
    SDL_WaylandSeat *seat, *tmp;

    Wayland_SessionDestroy(तथ्य);

    क्रम (पूर्णांक i = _this->अंक_displays - 1; i >= 0; --i) {
        SDL_VideoDisplay *display = _this->displays[i];
        Wayland_free_display(display, false);
    }
    SDL_free(तथ्य->output_list);

    wl_list_for_each_safe (seat, tmp, &तथ्य->seat_list, link) {
        Wayland_SeatDestroy(seat, true);
    }

    Wayland_FiniMouse(तथ्य);
    Wayland_QuitKeyboard(_this);

    Wayland_DestroyEventThread(तथ्य->event_thread_context);
    तथ्य->event_thread_context = शून्य;

    Wayland_DestroyJobThread(तथ्य->job_thread_context);
    तथ्य->job_thread_context = शून्य;

    अगर (तथ्य->pointer_constraints) {
        zwp_pointer_constraints_v1_destroy(तथ्य->pointer_constraints);
        तथ्य->pointer_constraints = शून्य;
    }

    अगर (तथ्य->relative_pointer_manager) {
        zwp_relative_pointer_manager_v1_destroy(तथ्य->relative_pointer_manager);
        तथ्य->relative_pointer_manager = शून्य;
    }

    अगर (तथ्य->activation_manager) {
        xdg_activation_v1_destroy(तथ्य->activation_manager);
        तथ्य->activation_manager = शून्य;
    }

    अगर (तथ्य->idle_inhibit_manager) {
        zwp_idle_inhibit_manager_v1_destroy(तथ्य->idle_inhibit_manager);
        तथ्य->idle_inhibit_manager = शून्य;
    }

    अगर (तथ्य->कुंजी_inhibitor_manager) {
        zwp_keyboard_shortcuts_inhibit_manager_v1_destroy(तथ्य->कुंजी_inhibitor_manager);
        तथ्य->कुंजी_inhibitor_manager = शून्य;
    }

    अगर (तथ्य->text_निवेश_manager) {
        zwp_text_निवेश_manager_v3_destroy(तथ्य->text_निवेश_manager);
        तथ्य->text_निवेश_manager = शून्य;
    }

    अगर (तथ्य->xkb_context) {
        WAYLAND_xkb_context_unref(तथ्य->xkb_context);
        तथ्य->xkb_context = शून्य;
    }

    अगर (तथ्य->tablet_manager) {
        zwp_tablet_manager_v2_destroy((काष्ठा zwp_tablet_manager_v2 *)तथ्य->tablet_manager);
        तथ्य->tablet_manager = शून्य;
    }

    अगर (तथ्य->तथ्य_device_manager) {
        wl_तथ्य_device_manager_destroy(तथ्य->तथ्य_device_manager);
        तथ्य->तथ्य_device_manager = शून्य;
    }

    अगर (तथ्य->shm) {
        अगर (wl_shm_get_version(तथ्य->shm) >= WL_SHM_RELEASE_SINCE_VERSION) {
            wl_shm_release(तथ्य->shm);
        } अन्यथा {
            wl_shm_destroy(तथ्य->shm);
        }
        तथ्य->shm = शून्य;
    }

    अगर (तथ्य->shell.xdg) {
        xdg_wm_base_destroy(तथ्य->shell.xdg);
        तथ्य->shell.xdg = शून्य;
    }

    अगर (तथ्य->decoration_manager) {
        zxdg_decoration_manager_v1_destroy(तथ्य->decoration_manager);
        तथ्य->decoration_manager = शून्य;
    }

    अगर (तथ्य->xdg_output_manager) {
        zxdg_output_manager_v1_destroy(तथ्य->xdg_output_manager);
        तथ्य->xdg_output_manager = शून्य;
    }

    अगर (तथ्य->viewporter) {
        wp_viewporter_destroy(तथ्य->viewporter);
        तथ्य->viewporter = शून्य;
    }

    अगर (तथ्य->primary_selection_device_manager) {
        zwp_primary_selection_device_manager_v1_destroy(तथ्य->primary_selection_device_manager);
        तथ्य->primary_selection_device_manager = शून्य;
    }

    अगर (तथ्य->fractional_scale_manager) {
        wp_fractional_scale_manager_v1_destroy(तथ्य->fractional_scale_manager);
        तथ्य->fractional_scale_manager = शून्य;
    }

    अगर (तथ्य->निवेश_timestamps_manager) {
        zwp_निवेश_timestamps_manager_v1_destroy(तथ्य->निवेश_timestamps_manager);
        तथ्य->निवेश_timestamps_manager = शून्य;
    }

    अगर (तथ्य->cursor_shape_manager) {
        wp_cursor_shape_manager_v1_destroy(तथ्य->cursor_shape_manager);
        तथ्य->cursor_shape_manager = शून्य;
    }

    अगर (तथ्य->zxdg_exporter_v2) {
        zxdg_exporter_v2_destroy(तथ्य->zxdg_exporter_v2);
        तथ्य->zxdg_exporter_v2 = शून्य;
    }

    अगर (तथ्य->xdg_wm_dialog_v1) {
        xdg_wm_dialog_v1_destroy(तथ्य->xdg_wm_dialog_v1);
        तथ्य->xdg_wm_dialog_v1 = शून्य;
    }

    अगर (तथ्य->wp_alpha_modifier_v1) {
        wp_alpha_modifier_v1_destroy(तथ्य->wp_alpha_modifier_v1);
        तथ्य->wp_alpha_modifier_v1 = शून्य;
    }

    अगर (तथ्य->xdg_toplevel_icon_manager_v1) {
        xdg_toplevel_icon_manager_v1_destroy(तथ्य->xdg_toplevel_icon_manager_v1);
        तथ्य->xdg_toplevel_icon_manager_v1 = शून्य;
    }

    अगर (तथ्य->frog_color_management_factory_v1) {
        frog_color_management_factory_v1_destroy(तथ्य->frog_color_management_factory_v1);
        तथ्य->frog_color_management_factory_v1 = शून्य;
    }

    अगर (तथ्य->wp_color_manager_v1) {
        wp_color_manager_v1_destroy(तथ्य->wp_color_manager_v1);
        तथ्य->wp_color_manager_v1 = शून्य;
    }

    अगर (तथ्य->wp_pointer_warp_v1) {
        wp_pointer_warp_v1_destroy(तथ्य->wp_pointer_warp_v1);
        तथ्य->wp_pointer_warp_v1 = शून्य;
    }

    अगर (तथ्य->zwp_pointer_gestures) {
        अगर (zwp_pointer_gestures_v1_get_version(तथ्य->zwp_pointer_gestures) >= ZWP_POINTER_GESTURES_V1_RELEASE_SINCE_VERSION) {
            zwp_pointer_gestures_v1_release(तथ्य->zwp_pointer_gestures);
        } अन्यथा {
            zwp_pointer_gestures_v1_destroy(तथ्य->zwp_pointer_gestures);
        }
        तथ्य->zwp_pointer_gestures = शून्य;
    }

    अगर (तथ्य->single_pixel_बफर_manager) {
        wp_single_pixel_बफर_manager_v1_destroy(तथ्य->single_pixel_बफर_manager);
        तथ्य->single_pixel_बफर_manager = शून्य;
    }

    अगर (तथ्य->xdg_session_manager) {
        xdg_session_manager_v1_destroy(तथ्य->xdg_session_manager);
        तथ्य->xdg_session_manager = शून्य;
    }

    अगर (तथ्य->xdg_toplevel_tag_manager) {
        xdg_toplevel_tag_manager_v1_destroy(तथ्य->xdg_toplevel_tag_manager);
        तथ्य->xdg_toplevel_tag_manager = शून्य;
    }

    अगर (तथ्य->subcompositor) {
        wl_subcompositor_destroy(तथ्य->subcompositor);
        तथ्य->subcompositor = शून्य;
    }

    अगर (तथ्य->compositor) {
        wl_compositor_destroy(तथ्य->compositor);
        तथ्य->compositor = शून्य;
    }

    अगर (तथ्य->registry) {
        अगर (तथ्य->wl_fixes) {
            wl_fixes_destroy_registry(तथ्य->wl_fixes, तथ्य->registry);
            wl_fixes_destroy(तथ्य->wl_fixes);
            तथ्य->wl_fixes = शून्य;
        }
        wl_registry_destroy(तथ्य->registry);
        तथ्य->registry = शून्य;
    }
}

अटल bool Wayland_VideoReconnect(SDL_VideoDevice *_this)
{
#अगर 0 // TODO RECONNECT: Uncomment all when https://invent.kde.org/plasma/kwin/-/wikis/Restarting is completed
    SDL_Video_तथ्य *तथ्य = _this->internal;

    SDL_Window *window = शून्य;

    SDL_GLContext current_ctx = SDL_GL_GetCurrentContext();
    SDL_Window *current_window = SDL_GL_GetCurrentWindow();

    SDL_GL_MakeCurrent(शून्य, शून्य);
    Wayland_VideoCleanup(_this);

    SDL_ResetKeyboard();
    SDL_ResetMouse();
    अगर (WAYLAND_wl_display_reconnect(तथ्य->display) < 0) {
        वापस false;
    }

    Wayland_VideoInit(_this);

    window = _this->windows;
    जबतक (window) {
        /* We're going to cheat _just_ for a second and strip the OpenGL flag.
         * The Wayland driver actually forces it in CreateWindow, and
         * RecreateWindow does a bunch of unloading/loading of libGL, so just
         * strip the flag so RecreateWindow doesn't mess with the GL context,
         * and CreateWindow will add it right back!
         * -flibit
         */
        window->flags &= ~SDL_WINDOW_OPENGL;

        SDL_RecreateWindow(window, window->flags);
        window = window->अग्र;
    }

    Wayland_RecreateCursors();

    अगर (current_window && current_ctx) {
        SDL_GL_MakeCurrent (current_window, current_ctx);
    }
    वापस true;
#अन्यथा
    वापस false;
#पूर्ण_अगर // 0
}

bool Wayland_HandleDisplayDisconnected(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *video_तथ्य = _this->internal;

    /* Something has failed with the Wayland connection -- for example,
     * the compositor may have shut down and closed its end of the socket,
     * or there is a library-specific error.
     *
     * Try to recover once, then quit.
     */
    अगर (video_तथ्य->display_disconnected) {
        वापस false;
    }

    अगर (Wayland_VideoReconnect(_this)) {
        वापस true;
    }

    video_तथ्य->display_disconnected = true;
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Wayland display connection closed by server (fatal)");

    // Only send a single quit message, as application shutdown might call SDL_PumpEvents().
    SDL_SendQuit();

    वापस false;
}

व्योम Wayland_VideoQuit(SDL_VideoDevice *_this)
{
    Wayland_VideoCleanup(_this);

#अगर_घोषित HAVE_LIBDECOR_H
    SDL_Video_तथ्य *तथ्य = _this->internal;
    अगर (तथ्य->shell.libdecor) {
        libdecor_unref(तथ्य->shell.libdecor);
        तथ्य->shell.libdecor = शून्य;
    }
#पूर्ण_अगर
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_WAYLAND
