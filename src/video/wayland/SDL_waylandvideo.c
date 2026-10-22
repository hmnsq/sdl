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

#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND

#شامل "../../core/linux/SDL_system_theme.h"
#شامل "../../core/linux/SDL_progressbar.h"
#شامل "../../events/SDL_events_c.h"

#شامل "SDL_waylandclipboard.h"
#شامل "SDL_waylandcolor.h"
#شامل "SDL_waylandevents_c.h"
#شامل "SDL_waylandkeyboard.h"
#شامل "SDL_waylandmessagebox.h"
#شامل "SDL_waylandmouse.h"
#شامل "SDL_waylandopengles.h"
#شامل "SDL_waylandvideo.h"
#شامل "SDL_waylandvulkan.h"
#شامل "SDL_waylandwindow.h"

#شامل <fcntl.h>
#شامل <sys/types.h>
#شامل <unistd.h>
#شامل <errno.h>
#شامل <xkbcommon/xkbcommon.h>

#شامل <wayland-util.h>

#شامل "alpha-modifier-v1-client-protocol.h"
#شامل "cursor-shape-v1-client-protocol.h"
#شامل "fractional-scale-v1-client-protocol.h"
#شامل "frog-color-management-v1-client-protocol.h"
#شامل "idle-inhibit-unstable-v1-client-protocol.h"
#شامل "input-timestamps-unstable-v1-client-protocol.h"
#شامل "keyboard-shortcuts-inhibit-unstable-v1-client-protocol.h"
#شامل "pointer-constraints-unstable-v1-client-protocol.h"
#شامل "primary-selection-unstable-v1-client-protocol.h"
#شامل "relative-pointer-unstable-v1-client-protocol.h"
#شامل "tablet-v2-client-protocol.h"
#شامل "text-input-unstable-v3-client-protocol.h"
#شامل "viewporter-client-protocol.h"
#شامل "xdg-activation-v1-client-protocol.h"
#شامل "xdg-decoration-unstable-v1-client-protocol.h"
#شامل "xdg-dialog-v1-client-protocol.h"
#شامل "xdg-foreign-unstable-v2-client-protocol.h"
#شامل "xdg-output-unstable-v1-client-protocol.h"
#شامل "xdg-shell-client-protocol.h"
#شامل "xdg-toplevel-icon-v1-client-protocol.h"
#شامل "color-management-v1-client-protocol.h"
#شامل "pointer-warp-v1-client-protocol.h"
#شامل "pointer-gestures-unstable-v1-client-protocol.h"
#شامل "single-pixel-buffer-v1-client-protocol.h"
#شامل "xdg-session-management-v1-client-protocol.h"
#شامل "xdg-toplevel-tag-v1-client-protocol.h"

#اگر_تعریف_شدہ HAVE_LIBDECOR_H
#شامل <libdecor.h>
#اگر_ختم

#تعریف_کرو WAYLANDVID_DRIVER_NAME "wayland"

// Clamp core protocol versions on older versions of libwayland.
#اگر SDL_WAYLAND_CHECK_نسخہ(1, 22, 0)
#تعریف_کرو SDL_WL_COMPOSITOR_نسخہ 6
#ورنہ
#تعریف_کرو SDL_WL_COMPOSITOR_نسخہ 4
#اگر_ختم

#اگر SDL_WAYLAND_CHECK_نسخہ(1, 26, 0)
#تعریف_کرو SDL_WL_SEAT_نسخہ 11
#وگرنہ_اگر SDL_WAYLAND_CHECK_نسخہ(1, 24, 0)
#تعریف_کرو SDL_WL_SEAT_نسخہ 10
#وگرنہ_اگر SDL_WAYLAND_CHECK_نسخہ(1, 22, 0)
#تعریف_کرو SDL_WL_SEAT_نسخہ 9
#وگرنہ_اگر SDL_WAYLAND_CHECK_نسخہ(1, 21, 0)
#تعریف_کرو SDL_WL_SEAT_نسخہ 8
#ورنہ
#تعریف_کرو SDL_WL_SEAT_نسخہ 5
#اگر_ختم

#اگر SDL_WAYLAND_CHECK_نسخہ(1, 20, 0)
#تعریف_کرو SDL_WL_OUTPUT_نسخہ 4
#ورنہ
#تعریف_کرو SDL_WL_OUTPUT_نسخہ 3
#اگر_ختم

#اگر SDL_WAYLAND_CHECK_نسخہ(1, 24, 0)
#تعریف_کرو SDL_WL_SHM_نسخہ 2
#ورنہ
#تعریف_کرو SDL_WL_SHM_نسخہ 1
#اگر_ختم

// The SDL libwayland-client minimum is 1.18, which supports version 3.
#تعریف_کرو SDL_WL_ڈیٹا_DEVICE_نسخہ 3

// wl_fixes was introduced in 1.24.0
#اگر SDL_WAYLAND_CHECK_نسخہ(1, 26, 0)
#تعریف_کرو SDL_WL_FIXES_نسخہ 2
#وگرنہ_اگر SDL_WAYLAND_CHECK_نسخہ(1, 24, 0)
#تعریف_کرو SDL_WL_FIXES_نسخہ 1
#اگر_ختم

#اگر_تعریف_شدہ SDL_USE_LIBDBUS
#شامل "../../core/linux/SDL_dbus.h"

#تعریف_کرو DISPLAY_INFO_گرہ   "org.gnome.Mutter.DisplayConfig"
#تعریف_کرو DISPLAY_INFO_راستہ   "/org/gnome/Mutter/DisplayConfig"
#تعریف_کرو DISPLAY_INFO_طریقہ "GetCurrentState"
#اگر_ختم

/* GNOME doesn't expose displays in any particular order, but we can find the
 * primary display and its logical coordinates via a DBus method.
 */
ساکن bool Wayland_GetGNOMEPrimaryDisplayCoordinates(صحیح *x, صحیح *y)
{
#اگر_تعریف_شدہ SDL_USE_LIBDBUS
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    اگر (dbus == تہی) {
        واپس false;
    }
    DBus_پیغام *جواب = تہی;
    DBus_پیغام_Iter iter[3];
    DBus_پیغام *پیغام_2 = dbus->پیغام_new_طریقہ_call(DISPLAY_INFO_گرہ,
                                                     DISPLAY_INFO_راستہ,
                                                     DISPLAY_INFO_گرہ,
                                                     DISPLAY_INFO_طریقہ);

    اگر (پیغام_2) {
        جواب = dbus->connection_send_with_جواب_and_بلاک(dbus->session_conn, پیغام_2, DBUS_TIMEOUT_USE_DEFAULT, تہی);
        dbus->پیغام_unref(پیغام_2);
    }

    اگر (جواب) {
        // Serial (don't care)
        dbus->پیغام_iter_init(جواب, &iter[0]);
        اگر (dbus->پیغام_iter_get_arg_type(&iter[0]) != DBUS_TYPE_UINT32) {
            جاؤ error;
        }

        // Physical monitor array (don't care)
        dbus->پیغام_iter_اگلا(&iter[0]);
        اگر (dbus->پیغام_iter_get_arg_type(&iter[0]) != DBUS_TYPE_ARRAY) {
            جاؤ error;
        }

        // Logical monitor array of structs
        dbus->پیغام_iter_اگلا(&iter[0]);
        اگر (dbus->پیغام_iter_get_arg_type(&iter[0]) != DBUS_TYPE_ARRAY) {
            جاؤ error;
        }

        // First logical monitor struct
        dbus->پیغام_iter_recurse(&iter[0], &iter[1]);
        اگر (dbus->پیغام_iter_get_arg_type(&iter[1]) != DBUS_TYPE_STRUCT) {
            جاؤ error;
        }

        کرو {
            صحیح logical_x, logical_y;
            dbus_bool_t primary;

            // Logical X
            dbus->پیغام_iter_recurse(&iter[1], &iter[2]);
            اگر (dbus->پیغام_iter_get_arg_type(&iter[2]) != DBUS_TYPE_INT32) {
                جاؤ error;
            }
            dbus->پیغام_iter_get_basic(&iter[2], &logical_x);

            // Logical Y
            dbus->پیغام_iter_اگلا(&iter[2]);
            اگر (dbus->پیغام_iter_get_arg_type(&iter[2]) != DBUS_TYPE_INT32) {
                جاؤ error;
            }
            dbus->پیغام_iter_get_basic(&iter[2], &logical_y);

            // Scale (don't care)
            dbus->پیغام_iter_اگلا(&iter[2]);
            اگر (dbus->پیغام_iter_get_arg_type(&iter[2]) != DBUS_TYPE_DOUBLE) {
                جاؤ error;
            }

            // Transform (don't care)
            dbus->پیغام_iter_اگلا(&iter[2]);
            اگر (dbus->پیغام_iter_get_arg_type(&iter[2]) != DBUS_TYPE_UINT32) {
                جاؤ error;
            }

            // Primary display boolean
            dbus->پیغام_iter_اگلا(&iter[2]);
            اگر (dbus->پیغام_iter_get_arg_type(&iter[2]) != DBUS_TYPE_BOOLEAN) {
                جاؤ error;
            }
            dbus->پیغام_iter_get_basic(&iter[2], &primary);

            اگر (primary) {
                *x = logical_x;
                *y = logical_y;

                // We found the primary display: success.
                dbus->پیغام_unref(جواب);
                واپس true;
            }
        } جب (dbus->پیغام_iter_اگلا(&iter[1]));
    }

error:
    اگر (جواب) {
        dbus->پیغام_unref(جواب);
    }
#اگر_ختم
    واپس false;
}

// Sort the list of displays into a deterministic order
ساکن صحیح SDLCALL Wayland_DisplayPositionCompare(ثابت خالی *a, ثابت خالی *b)
{
    ثابت SDL_Display_ڈیٹا *da = *(SDL_Display_ڈیٹا **)a;
    ثابت SDL_Display_ڈیٹا *db = *(SDL_Display_ڈیٹا **)b;
    ثابت bool a_at_origin = da->logical.x == 0 && da->logical.y == 0;
    ثابت bool b_at_origin = db->logical.x == 0 && db->logical.y == 0;

    // Sort the display at 0,0 to be beginning of the list, as that will be the fallback primary.
    اگر (a_at_origin && !b_at_origin) {
        واپس -1;
    }
    اگر (b_at_origin && !a_at_origin) {
        واپس 1;
    }

    اگر (da->logical.x < db->logical.x) {
        واپس -1;
    }
    اگر (da->logical.x > db->logical.x) {
        واپس 1;
    }
    اگر (da->logical.y < db->logical.y) {
        واپس -1;
    }
    اگر (da->logical.y > db->logical.y) {
        واپس 1;
    }

    // If no position information is available, use the connector name.
    اگر (da->wl_output_name && db->wl_output_name) {
        واپس SDL_strcmp(da->wl_output_name, db->wl_output_name);
    }

    واپس 0;
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
ساکن صحیح Wayland_GetPrimaryDisplay(SDL_Video_ڈیٹا *vid)
{
    ساکن ثابت صحیح REFRESH_DELTA = 4000;

    // Query the DBus interface to see if the coordinates of the primary display are exposed.
    صحیح x, y;
    اگر (Wayland_GetGNOMEPrimaryDisplayCoordinates(&x, &y)) {
        برائے (صحیح i = 0; i < vid->output_گنتی; ++i) {
            اگر (vid->output_list[i]->logical.x == x && vid->output_list[i]->logical.y == y) {
                واپس i;
            }
        }
    }

    // Otherwise, choose the 'best' display.
    صحیح بہترین_چوڑائی = 0;
    صحیح بہترین_اونچائی = 0;
    دوہرا بہترین_scale = 0.0;
    اعشاری بہترین_headroom = 0.0f;
    صحیح بہترین_refresh = 0;
    bool بہترین_is_landscape = false;
    صحیح بہترین_اشاریہ = 0;

    برائے (صحیح i = 0; i < vid->output_گنتی; ++i) {
        ثابت SDL_Display_ڈیٹا *d = vid->output_list[i];
        ثابت bool is_landscape = d->orientation != SDL_ORIENTATION_PORTRAIT && d->orientation != SDL_ORIENTATION_PORTRAIT_FLIPPED;
        bool have_new_بہترین = false;

        اگر (!بہترین_is_landscape && is_landscape) { // Favor landscape over portrait displays.
            have_new_بہترین = true;
        } ورنہ اگر (!بہترین_is_landscape || is_landscape) { // Ignore portrait displays if a landscape was already found.
            اگر (d->pixel.چوڑائی > بہترین_چوڑائی || d->pixel.اونچائی > بہترین_اونچائی) {
                have_new_بہترین = true;
            } ورنہ اگر (d->pixel.چوڑائی == بہترین_چوڑائی && d->pixel.اونچائی == بہترین_اونچائی) {
                اگر (d->HDR.HDR_headroom > بہترین_headroom) { // Favor a higher HDR luminance range
                    have_new_بہترین = true;
                } ورنہ اگر (d->HDR.HDR_headroom == بہترین_headroom) {
                    اگر (d->refresh - بہترین_refresh > REFRESH_DELTA) { // Favor a higher refresh rate, but ignore small differences (e.g. 59.97 vs 60.1)
                        have_new_بہترین = true;
                    } ورنہ اگر (d->scale_ضربی_عدد_2 < بہترین_scale && SDL_abs(d->refresh - بہترین_refresh) <= REFRESH_DELTA) {
                        // Prefer a lower scale display if the difference in refresh rate is small.
                        have_new_بہترین = true;
                    }
                }
            }
        }

        اگر (have_new_بہترین) {
            بہترین_چوڑائی = d->pixel.چوڑائی;
            بہترین_اونچائی = d->pixel.اونچائی;
            بہترین_scale = d->scale_ضربی_عدد_2;
            بہترین_headroom = d->HDR.HDR_headroom;
            بہترین_refresh = d->refresh;
            بہترین_is_landscape = is_landscape;
            بہترین_اشاریہ = i;
        }
    }

    واپس بہترین_اشاریہ;
}

ساکن خالی Wayland_ترتیب_دو_Outputs_By_ترجیح_Hint(SDL_Video_ڈیٹا *vid)
{
    ثابت حرف *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_ترجیح);

    اگر (name_hint) {
        حرف *saveptr;
        حرف *str = SDL_strdup(name_hint);
        SDL_Display_ڈیٹا **sorted_list = SDL_malloc(حجم(SDL_Display_ڈیٹا *) * vid->output_گنتی);

        اگر (str && sorted_list) {
            صحیح sorted_اشاریہ = 0;

            // Sort the requested displays to the front of the list.
            ثابت حرف *token = SDL_strtok_r(str, ",", &saveptr);
            جب (token) {
                برائے (صحیح i = 0; i < vid->output_گنتی; ++i) {
                    SDL_Display_ڈیٹا *d = vid->output_list[i];
                    اگر (d && d->wl_output_name && SDL_strcmp(token, d->wl_output_name) == 0) {
                        sorted_list[sorted_اشاریہ++] = d;
                        vid->output_list[i] = تہی;
                        توڑو;
                    }
                }

                token = SDL_strtok_r(تہی, ",", &saveptr);
            }

            // Append the remaining outputs to the end of the list.
            برائے (صحیح i = 0; i < vid->output_گنتی; ++i) {
                اگر (vid->output_list[i]) {
                    sorted_list[sorted_اشاریہ++] = vid->output_list[i];
                }
            }

            // Copy the sorted list to the output list.
            SDL_memcpy(vid->output_list, sorted_list, حجم(SDL_Display_ڈیٹا *) * vid->output_گنتی);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

ساکن خالی Wayland_DeriveOutputPixelCoordinates(SDL_Video_ڈیٹا *vid)
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
    برائے ( صحیح i = 0; i < vid->output_گنتی; ++i) {
        SDL_Display_ڈیٹا *d = vid->output_list[i];
        d->pixel.x = d->logical.x;
        d->pixel.y = d->logical.y;
    }

    برائے (صحیح i = 0; i < vid->output_گنتی; ++i) {
        SDL_Display_ڈیٹا *d1 = vid->output_list[i];
        اگر (d1->logical.چوڑائی != d1->pixel.چوڑائی || d1->logical.اونچائی != d1->pixel.اونچائی) {
            ثابت صحیح x_adj = d1->pixel.چوڑائی - d1->logical.چوڑائی;
            ثابت صحیح y_adj = d1->pixel.اونچائی - d1->logical.اونچائی;

            // Don't adjust for scale values less than 1.0.
            اگر (x_adj > 0 && y_adj > 0) {
                برائے (صحیح j = 0; j < vid->output_گنتی; ++j) {
                    SDL_Display_ڈیٹا *d2 = vid->output_list[j];
                    اگر (d2->logical.x > d1->logical.x) {
                        d2->pixel.x += x_adj;
                    }
                    اگر (d2->logical.y > d1->logical.y) {
                        d2->pixel.y += y_adj;
                    }
                }
            }
        }
    }
}

ساکن خالی Wayland_ترتیب_دو_Outputs(SDL_Video_ڈیٹا *vid)
{
    // Sort by position or connector name, so the order of outputs is deterministic.
    SDL_qsort(vid->output_list, vid->output_گنتی, حجم(SDL_Display_ڈیٹا *), Wayland_DisplayPositionCompare);

    // Derive the output pixel coordinates if scale to display is enabled.
    اگر (vid->scale_مقصد_display_enabled) {
        Wayland_DeriveOutputPixelCoordinates(vid);
    }

    // Find a suitable primary display and move it to the front of the list.
    ثابت صحیح primary_اشاریہ = Wayland_GetPrimaryDisplay(vid);
    اگر (primary_اشاریہ) {
        SDL_Display_ڈیٹا *primary = vid->output_list[primary_اشاریہ];
        SDL_memmove(&vid->output_list[1], &vid->output_list[0], حجم(SDL_Display_ڈیٹا *) * primary_اشاریہ);
        vid->output_list[0] = primary;
    }

    // Apply the ordering hint, if specified.
    Wayland_ترتیب_دو_Outputs_By_ترجیح_Hint(vid);
}

ساکن خالی Wayland_Refresh_کھڑکی_Positions()
{
    SDL_VideoDevice *vid = SDL_GetVideoDevice();

    برائے (SDL_کھڑکی *w = vid->windows; w; w = w->اگلا) {
        Wayland_Update_کھڑکی_Position(w);
    }
}

ساکن خالی handle_wl_output_مکمل(خالی *ڈیٹا, ساخت wl_output *output);

// Initialization/Query functions
ساکن bool Wayland_VideoInit(SDL_VideoDevice *_this);
ساکن bool Wayland_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
ساکن خالی Wayland_VideoQuit(SDL_VideoDevice *_this);

ساکن ثابت حرف *SDL_WAYLAND_surface_لیبل = "sdl-window";
ساکن ثابت حرف *SDL_WAYLAND_output_لیبل = "sdl-output";

خالی SDL_WAYLAND_رجسٹر_surface(ساخت wl_surface *surface)
{
    wl_proxy_سیٹ_لیبل((ساخت wl_proxy *)surface, &SDL_WAYLAND_surface_لیبل);
}

خالی SDL_WAYLAND_رجسٹر_output(ساخت wl_output *output)
{
    wl_proxy_سیٹ_لیبل((ساخت wl_proxy *)output, &SDL_WAYLAND_output_لیبل);
}

bool SDL_WAYLAND_own_surface(ساخت wl_surface *surface)
{
    واپس wl_proxy_get_لیبل((ساخت wl_proxy *)surface) == &SDL_WAYLAND_surface_لیبل;
}

bool SDL_WAYLAND_own_output(ساخت wl_output *output)
{
    واپس wl_proxy_get_لیبل((ساخت wl_proxy *)output) == &SDL_WAYLAND_output_لیبل;
}

/* External surfaces may have their own user data attached, the modification of which
 * can cause problems with external toolkits. Instead, external windows are kept in
 * their own list, and a search is conducted to find a matching surface.
 */
ساکن ساخت wl_list external_کھڑکی_list;

خالی Wayland_جوڑو_کھڑکی_ڈیٹا_مقصد_External_List(SDL_کھڑکی_ڈیٹا *ڈیٹا)
{
    WAYLAND_wl_list_داخل_کرو(&external_کھڑکی_list, &ڈیٹا->external_کھڑکی_list_link);
}

خالی Wayland_Remove_کھڑکی_ڈیٹا_From_External_List(SDL_کھڑکی_ڈیٹا *ڈیٹا)
{
    WAYLAND_wl_list_remove(&ڈیٹا->external_کھڑکی_list_link);
}

SDL_کھڑکی_ڈیٹا *Wayland_Get_کھڑکی_ڈیٹا_For_Owned_Surface(ساخت wl_surface *surface)
{
    اگر (SDL_WAYLAND_own_surface(surface)) {
        واپس (SDL_کھڑکی_ڈیٹا *)wl_surface_get_user_ڈیٹا(surface);
    } ورنہ اگر (!WAYLAND_wl_list_خالی_خانے(&external_کھڑکی_list)) {
        SDL_کھڑکی_ڈیٹا *p;
        wl_list_for_each (p, &external_کھڑکی_list, external_کھڑکی_list_link) {
            اگر (p->surface == surface) {
                واپس p;
            }
        }
    }

    واپس تہی;
}

ساخت wl_event_قطار *Wayland_Display_Create_قطار(ساخت wl_display *display, ثابت حرف *name)
{
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
    اگر (WAYLAND_wl_display_create_قطار_with_name) {
        واپس WAYLAND_wl_display_create_قطار_with_name(display, name);
    }
#وگرنہ_اگر SDL_WAYLAND_CHECK_نسخہ(1, 23, 0)
    واپس WAYLAND_wl_display_create_قطار_with_name(display, name);
#اگر_ختم
    واپس WAYLAND_wl_display_create_قطار(display);
}

ساکن خالی Wayland_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_Video_ڈیٹا *ڈیٹا = device->اندرونی_2;
    اگر (ڈیٹا->display && !ڈیٹا->display_externally_owned) {
        WAYLAND_wl_display_disconnect(ڈیٹا->display);
        SDL_ClearProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_اشارہ_گر);
    }
    SDL_free(ڈیٹا);
    SDL_free(device);
    SDL_WAYLAND_UnloadSymbols();
}

قسمتعریف ساخت
{
    bool has_fifo_v1;
    ساخت wl_fixes *wl_fixes;
} SDL_Wayland_Preferred_ڈیٹا;

ساکن خالی wayland_preferred_check_handle_global(خالی *ڈیٹا, ساخت wl_registry *registry, uint32_t id,
                                                  ثابت حرف *interface, uint32_t نسخہ)
{
    SDL_Wayland_Preferred_ڈیٹا *d = ڈیٹا;

    اگر (SDL_strcmp(interface, "wp_fifo_manager_v1") == 0) {
        d->has_fifo_v1 = true;
    }
#اگر_تعریف_شدہ SDL_WL_FIXES_نسخہ
    ورنہ اگر (SDL_strcmp(interface, wl_fixes_interface.name) == 0) {
        d->wl_fixes = wl_registry_bind(registry, id, &wl_fixes_interface, SDL_min(SDL_WL_FIXES_نسخہ, نسخہ));
    }
#اگر_ختم
}

ساکن خالی wayland_preferred_check_remove_global(خالی *ڈیٹا, ساخت wl_registry *registry, uint32_t id)
{
    SDL_Wayland_Preferred_ڈیٹا *d = (SDL_Wayland_Preferred_ڈیٹا *)ڈیٹا;

    اگر (d->wl_fixes && wl_fixes_get_نسخہ(d->wl_fixes) >= WL_FIXES_ACK_GLOBAL_REMOVE_SINCE_نسخہ) {
        wl_fixes_ack_global_remove(d->wl_fixes, registry, id);
    }
}

ساکن ثابت ساخت wl_registry_listener preferred_registry_listener = {
    wayland_preferred_check_handle_global,
    wayland_preferred_check_remove_global
};

ساکن bool Wayland_IsPreferred(ساخت wl_display *display)
{
    ساخت wl_registry *registry = wl_display_get_registry(display);
    SDL_Wayland_Preferred_ڈیٹا preferred_ڈیٹا = { 0 };

    اگر (!registry) {
        SDL_سیٹ_Error("Failed to get the Wayland registry");
        واپس false;
    }

    wl_registry_جوڑو_listener(registry, &preferred_registry_listener, &preferred_ڈیٹا);

    WAYLAND_wl_display_roundtrip(display);

    اگر (preferred_ڈیٹا.wl_fixes) {
        wl_fixes_destroy_registry(preferred_ڈیٹا.wl_fixes, registry);
        wl_fixes_destroy(preferred_ڈیٹا.wl_fixes);
    }
    wl_registry_destroy(registry);

    اگر (!preferred_ڈیٹا.has_fifo_v1) {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "This compositor lacks support for the fifo-v1 protocol; falling back to XWayland for GPU performance reasons (set SDL_VIDEO_DRIVER=wayland to override)");
    }
    واپس preferred_ڈیٹا.has_fifo_v1;
}

ساکن SDL_VideoDevice *Wayland_CreateDevice(bool require_preferred_protocols)
{
    SDL_VideoDevice *device;
    SDL_Video_ڈیٹا *ڈیٹا;
    ساخت wl_display *display = SDL_Get_اشارہ_گر_Property(SDL_GetGlobalProperties(),
                                                 SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_اشارہ_گر, تہی);
    bool display_is_external = !!display;

    // Are we trying to connect to, or are currently in, a Wayland session?
    اگر (!SDL_getenv("WAYLAND_DISPLAY")) {
        ثابت حرف *session = SDL_getenv("XDG_SESSION_TYPE");
        اگر (session && SDL_strcasecmp(session, "wayland") != 0) {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Wayland initialization failed: no Wayland session available");
            واپس تہی;
        }
    }

    اگر (!SDL_WAYLAND_بھرو_Symbols()) {
        واپس تہی;
    }

    اگر (!display) {
        display = WAYLAND_wl_display_connect(تہی);
        اگر (!display) {
            SDL_WAYLAND_UnloadSymbols();
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to connect to the Wayland display server: %s", strerror(errno));
            واپس تہی;
        }
    }

    /*
     * If we are checking for preferred Wayland, then let's query for
     * fifo-v1's existence, so we don't regress GPU-bound performance
     * and frame-pacing by default due to swapchain starvation.
     */
    اگر (require_preferred_protocols && !Wayland_IsPreferred(display)) {
        اگر (!display_is_external) {
            WAYLAND_wl_display_disconnect(display);
        }
        SDL_WAYLAND_UnloadSymbols();
        واپس تہی;
    }

    ڈیٹا = SDL_calloc(1, حجم(*ڈیٹا));
    اگر (!ڈیٹا) {
        اگر (!display_is_external) {
            WAYLAND_wl_display_disconnect(display);
        }
        SDL_WAYLAND_UnloadSymbols();
        واپس تہی;
    }

    ڈیٹا->initializing = true;
    ڈیٹا->display = display;
    ڈیٹا->display_externally_owned = display_is_external;
    ڈیٹا->scale_مقصد_display_enabled = SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_SCALE_مقصد_DISPLAY, false);
    WAYLAND_wl_list_init(&ڈیٹا->seat_list);
    WAYLAND_wl_list_init(&external_کھڑکی_list);

    // Initialize all variables that we clean on shutdown
    device = SDL_calloc(1, حجم(SDL_VideoDevice));
    اگر (!device) {
        SDL_free(ڈیٹا);
        اگر (!display_is_external) {
            WAYLAND_wl_display_disconnect(display);
        }
        SDL_WAYLAND_UnloadSymbols();
        واپس تہی;
    }

    اگر (!display_is_external) {
        SDL_سیٹ_اشارہ_گر_Property(SDL_GetGlobalProperties(),
                               SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_اشارہ_گر, display);
    }

    device->اندرونی_2 = ڈیٹا;

    // Set the function pointers
    device->VideoInit = Wayland_VideoInit;
    device->VideoQuit = Wayland_VideoQuit;
    device->GetDisplayBounds = Wayland_GetDisplayBounds;
    device->SuspendScreenSaver = Wayland_SuspendScreenSaver;

    device->PumpEvents = Wayland_PumpEvents;
    device->WaitEventTimeout = Wayland_WaitEventTimeout;
    device->SendWakeupEvent = Wayland_SendWakeupEvent;

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    device->GL_تبادلہ_کھڑکی = Wayland_GLES_تبادلہ_کھڑکی;
    device->GL_Get_تبادلہ_Interval = Wayland_GLES_Get_تبادلہ_Interval;
    device->GL_سیٹ_تبادلہ_Interval = Wayland_GLES_سیٹ_تبادلہ_Interval;
    device->GL_MakeCurrent = Wayland_GLES_MakeCurrent;
    device->GL_CreateContext = Wayland_GLES_CreateContext;
    device->GL_بھرو_Library = Wayland_GLES_بھرو_Library;
    device->GL_UnloadLibrary = Wayland_GLES_UnloadLibrary;
    device->GL_Get_Proc_پتہ = Wayland_GLES_Get_Proc_پتہ;
    device->GL_DestroyContext = Wayland_GLES_DestroyContext;
    device->GL_سیٹ_Default_Profile_Config = Wayland_GLES_سیٹ_Default_Profile_Config;
    device->GL_GetEGLSurface = Wayland_GLES_GetEGLSurface;
#اگر_ختم

    device->CreateSDLWindow = Wayland_Create_کھڑکی;
    device->Show_کھڑکی = Wayland_Show_کھڑکی;
    device->Hide_کھڑکی = Wayland_Hide_کھڑکی;
    device->Raise_کھڑکی = Wayland_Raise_کھڑکی;
    device->سیٹ_کھڑکی_Fullscreen = Wayland_سیٹ_کھڑکی_Fullscreen;
    device->Maximize_کھڑکی = Wayland_Maximize_کھڑکی;
    device->Minimize_کھڑکی = Wayland_Minimize_کھڑکی;
    device->سیٹ_کھڑکی_Mouse_Rect = Wayland_سیٹ_کھڑکی_Mouse_Rect;
    device->سیٹ_کھڑکی_Mouse_Grab = Wayland_سیٹ_کھڑکی_Mouse_Grab;
    device->سیٹ_کھڑکی_Keyboard_Grab = Wayland_سیٹ_کھڑکی_Keyboard_Grab;
    device->Restore_کھڑکی = Wayland_Restore_کھڑکی;
    device->سیٹ_کھڑکی_Bordered = Wayland_سیٹ_کھڑکی_Bordered;
    device->سیٹ_کھڑکی_Resizable = Wayland_سیٹ_کھڑکی_Resizable;
    device->سیٹ_کھڑکی_Position = Wayland_سیٹ_کھڑکی_Position;
    device->سیٹ_کھڑکی_سائز = Wayland_سیٹ_کھڑکی_سائز;
    device->سیٹ_کھڑکی_Aspect_تناسب = Wayland_سیٹ_کھڑکی_Aspect_تناسب;
    device->سیٹ_کھڑکی_Minimum_سائز = Wayland_سیٹ_کھڑکی_Minimum_سائز;
    device->سیٹ_کھڑکی_زیادہ_سے_زیادہ_سائز = Wayland_سیٹ_کھڑکی_زیادہ_سے_زیادہ_سائز;
    device->سیٹ_کھڑکی_والد = Wayland_سیٹ_کھڑکی_والد;
    device->سیٹ_کھڑکی_Modal = Wayland_سیٹ_کھڑکی_Modal;
    device->سیٹ_کھڑکی_Opacity = Wayland_سیٹ_کھڑکی_Opacity;
    device->سیٹ_کھڑکی_Title = Wayland_سیٹ_کھڑکی_Title;
    device->سیٹ_کھڑکی_Icon = Wayland_سیٹ_کھڑکی_Icon;
    device->Get_کھڑکی_سائز_اندر_Pixels = Wayland_Get_کھڑکی_سائز_اندر_Pixels;
    device->Get_کھڑکی_Content_Scale = Wayland_Get_کھڑکی_Content_Scale;
    device->Get_کھڑکی_ICCProfile = Wayland_Get_کھڑکی_ICCProfile;
    device->Get_Display_For_کھڑکی = Wayland_Get_Display_For_کھڑکی;
    device->Destroy_کھڑکی = Wayland_Destroy_کھڑکی;
    device->سیٹ_کھڑکی_کامیابی_Test = Wayland_سیٹ_کھڑکی_کامیابی_Test;
    device->Flash_کھڑکی = Wayland_Flash_کھڑکی;
#اگر_تعریف_شدہ SDL_USE_LIBDBUS
    device->Apply_کھڑکی_پیش_رفت = DBUS_Apply_کھڑکی_پیش_رفت;
#اگر_ختم // SDL_USE_LIBDBUS
    device->HasScreenKeyboardSupport = Wayland_HasScreenKeyboardSupport;
    device->Show_کھڑکی_System_Menu = Wayland_Show_کھڑکی_System_Menu;
    device->Sync_کھڑکی = Wayland_Sync_کھڑکی;
    device->سیٹ_کھڑکی_Focusable = Wayland_سیٹ_کھڑکی_Focusable;
    device->Reconfigure_کھڑکی = Wayland_Reconfigure_کھڑکی;
    device->AcceptDragAndDrop = Wayland_AcceptDragAndDrop;

#اگر_تعریف_شدہ SDL_USE_LIBDBUS
    اگر (SDL_SystemTheme_Init())
        device->system_theme = SDL_SystemTheme_Get();
#اگر_ختم

    device->Get_متن_Mime_Types = Wayland_Get_متن_Mime_Types;
    device->سیٹ_Clipboard_ڈیٹا = Wayland_سیٹ_Clipboard_ڈیٹا;
    device->Get_Clipboard_ڈیٹا = Wayland_Get_Clipboard_ڈیٹا;
    device->Has_Clipboard_ڈیٹا = Wayland_Has_Clipboard_ڈیٹا;
    device->آغاز_متن_داخلہ = Wayland_آغاز_متن_داخلہ;
    device->Stop_متن_داخلہ = Wayland_Stop_متن_داخلہ;
    device->Update_متن_داخلہ_Area = Wayland_Update_متن_داخلہ_Area;

#اگر_تعریف_شدہ SDL_VIDEO_VULKAN
    device->Vulkan_بھرو_Library = Wayland_Vulkan_بھرو_Library;
    device->Vulkan_UnloadLibrary = Wayland_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = Wayland_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = Wayland_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = Wayland_Vulkan_DestroySurface;
    device->Vulkan_GetPresentationSupport = Wayland_Vulkan_GetPresentationSupport;
#اگر_ختم

    device->آزاد = Wayland_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_منوال_SWITCHING_EMULATED |
                          VIDEO_DEVICE_CAPS_HAS_POPUP_کھڑکی_SUPPORT |
                          VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS |
                          VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES |
                          VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES;

    واپس device;
}

ساکن SDL_VideoDevice *Wayland_Preferred_CreateDevice(خالی)
{
    واپس Wayland_CreateDevice(true);
}

ساکن SDL_VideoDevice *Wayland_Fallback_CreateDevice(خالی)
{
    واپس Wayland_CreateDevice(false);
}

VideoBootStrap Wayland_preferred_bootstrap = {
    WAYLANDVID_DRIVER_NAME, "SDL Wayland video driver",
    Wayland_Preferred_CreateDevice,
    Wayland_Show_پیغام_Box,
    true
};

VideoBootStrap Wayland_bootstrap = {
    WAYLANDVID_DRIVER_NAME, "SDL Wayland video driver",
    Wayland_Fallback_CreateDevice,
    Wayland_Show_پیغام_Box,
    false
};

ساکن خالی handle_xdg_output_logical_position(خالی *ڈیٹا, ساخت zxdg_output_v1 *xdg_output, int32_t x, int32_t y)
{
    SDL_Display_ڈیٹا *اندرونی_2 = (SDL_Display_ڈیٹا *)ڈیٹا;

    اندرونی_2->geometry_بدلا |= اندرونی_2->logical.x != x || اندرونی_2->logical.y != y;
    اندرونی_2->logical.x = x;
    اندرونی_2->logical.y = y;
    اندرونی_2->has_logical_position = true;
}

ساکن خالی handle_xdg_output_logical_سائز(خالی *ڈیٹا, ساخت zxdg_output_v1 *xdg_output, int32_t چوڑائی, int32_t اونچائی)
{
    SDL_Display_ڈیٹا *اندرونی_2 = (SDL_Display_ڈیٹا *)ڈیٹا;

    اندرونی_2->geometry_بدلا |= اندرونی_2->logical.چوڑائی != چوڑائی || اندرونی_2->logical.اونچائی != اونچائی;
    اندرونی_2->logical.چوڑائی = چوڑائی;
    اندرونی_2->logical.اونچائی = اونچائی;
    اندرونی_2->has_logical_سائز = true;
}

ساکن خالی handle_xdg_output_مکمل(خالی *ڈیٹا, ساخت zxdg_output_v1 *xdg_output)
{
    SDL_Display_ڈیٹا *اندرونی_2 = ڈیٹا;

    /*
     * xdg-output.done events are deprecated and only apply below version 3 of the protocol.
     * A wl-output.done event will be emitted in version 3 or higher.
     */
    اگر (zxdg_output_v1_get_نسخہ(اندرونی_2->xdg_output) < 3) {
        handle_wl_output_مکمل(ڈیٹا, اندرونی_2->output);
    }
}

ساکن خالی handle_xdg_output_name(خالی *ڈیٹا, ساخت zxdg_output_v1 *xdg_output, ثابت حرف *name)
{
    SDL_Display_ڈیٹا *اندرونی_2 = (SDL_Display_ڈیٹا *)ڈیٹا;

    // Deprecated as of wl_output v4.
    اگر (wl_output_get_نسخہ(اندرونی_2->output) < WL_OUTPUT_NAME_SINCE_نسخہ &&
        اندرونی_2->display == 0) {
        SDL_free(اندرونی_2->wl_output_name);
        اندرونی_2->wl_output_name = SDL_strdup(name);
    }
}

ساکن خالی handle_xdg_output_description(خالی *ڈیٹا, ساخت zxdg_output_v1 *xdg_output, ثابت حرف *description)
{
    SDL_Display_ڈیٹا *اندرونی_2 = (SDL_Display_ڈیٹا *)ڈیٹا;

    // Deprecated as of wl_output v4.
    اگر (wl_output_get_نسخہ(اندرونی_2->output) < WL_OUTPUT_DESCRIPTION_SINCE_نسخہ &&
        اندرونی_2->display == 0) {
        // xdg-output descriptions, if available, supersede wl-output model names.
        SDL_free(اندرونی_2->placeholder.name);
        اندرونی_2->placeholder.name = SDL_strdup(description);
    }
}

ساکن ثابت ساخت zxdg_output_v1_listener xdg_output_listener = {
    handle_xdg_output_logical_position,
    handle_xdg_output_logical_سائز,
    handle_xdg_output_مکمل,
    handle_xdg_output_name,
    handle_xdg_output_description,
};

ساکن خالی جوڑو_Emulated_Modes(SDL_Display_ڈیٹا *dispdata, صحیح native_چوڑائی, صحیح native_اونچائی)
{
    ساخت Emulated_منوال
    {
        صحیح w;
        صحیح h;
    };

    // Resolution lists courtesy of XWayland
    ثابت ساخت Emulated_منوال منوال_list[] = {
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

    صحیح i;
    SDL_Display_منوال منوال;
    SDL_VideoDisplay *dpy = dispdata->display ? SDL_GetVideoDisplay(dispdata->display) : &dispdata->placeholder;
    ثابت bool rot_90 = native_چوڑائی < native_اونچائی; // Reverse width/height for portrait displays.

    برائے (i = 0; i < SDL_arraysize(منوال_list); ++i) {
        SDL_zero(منوال);
        منوال.format = dpy->desktop_منوال.format;
        منوال.refresh_شرح_numerator = dpy->desktop_منوال.refresh_شرح_numerator;
        منوال.refresh_شرح_denominator = dpy->desktop_منوال.refresh_شرح_denominator;

        اگر (rot_90) {
            منوال.w = منوال_list[i].h;
            منوال.h = منوال_list[i].w;
        } ورنہ {
            منوال.w = منوال_list[i].w;
            منوال.h = منوال_list[i].h;
        }

        // Only add modes that are smaller than the native mode.
        اگر ((منوال.w < native_چوڑائی && منوال.h < native_اونچائی) ||
            (منوال.w < native_چوڑائی && منوال.h == native_اونچائی) ||
            (منوال.w == native_چوڑائی && منوال.h < native_اونچائی)) {
            SDL_جوڑو_Fullscreen_Display_منوال(dpy, &منوال);
        }
    }
}

ساکن خالی handle_wl_output_geometry(خالی *ڈیٹا, ساخت wl_output *output, صحیح x, صحیح y,
                                      صحیح physical_چوڑائی_2, صحیح physical_اونچائی_2, صحیح subpixel,
                                      ثابت حرف *make, ثابت حرف *model, صحیح transform)
{
    SDL_Display_ڈیٹا *اندرونی_2 = (SDL_Display_ڈیٹا *)ڈیٹا;

    // Apply the change from wl-output only if xdg-output is not supported
    اگر (!اندرونی_2->has_logical_position) {
        اندرونی_2->geometry_بدلا |= اندرونی_2->logical.x != x || اندرونی_2->logical.y != y;
        اندرونی_2->logical.x = x;
        اندرونی_2->logical.y = y;
    }
    اندرونی_2->physical.چوڑائی_mm = physical_چوڑائی_2;
    اندرونی_2->physical.اونچائی_mm = physical_اونچائی_2;

    // The model is only used for the output name if wl_output or xdg-output haven't provided a description.
    اگر (اندرونی_2->display == 0 && !اندرونی_2->placeholder.name) {
        اندرونی_2->placeholder.name = SDL_strdup(model);
    }

    اندرونی_2->transform = transform;
#تعریف_کرو TF_CASE(اندر_2, برآمد)                                 \
    حالت WL_OUTPUT_TRANSFORM_##in:                       \
        اندرونی_2->orientation = SDL_ORIENTATION_##out; \
        توڑو;
    اگر (اندرونی_2->physical.چوڑائی_mm >= اندرونی_2->physical.اونچائی_mm) {
        انتخاب (transform) {
            TF_CASE(معمول_2, LANDSCAPE)
            TF_CASE(90, PORTRAIT)
            TF_CASE(180, LANDSCAPE_FLIPPED)
            TF_CASE(270, PORTRAIT_FLIPPED)
            TF_CASE(FLIPPED, LANDSCAPE_FLIPPED)
            TF_CASE(FLIPPED_90, PORTRAIT_FLIPPED)
            TF_CASE(FLIPPED_180, LANDSCAPE)
            TF_CASE(FLIPPED_270, PORTRAIT)
        }
    } ورنہ {
        انتخاب (transform) {
            TF_CASE(معمول_2, PORTRAIT)
            TF_CASE(90, LANDSCAPE)
            TF_CASE(180, PORTRAIT_FLIPPED)
            TF_CASE(270, LANDSCAPE_FLIPPED)
            TF_CASE(FLIPPED, PORTRAIT_FLIPPED)
            TF_CASE(FLIPPED_90, LANDSCAPE_FLIPPED)
            TF_CASE(FLIPPED_180, PORTRAIT)
            TF_CASE(FLIPPED_270, LANDSCAPE)
        }
    }
#تعریف_منسوخ TF_CASE
}

ساکن خالی handle_wl_output_منوال(خالی *ڈیٹا, ساخت wl_output *output, uint32_t flags,
                                  صحیح چوڑائی, صحیح اونچائی, صحیح refresh)
{
    SDL_Display_ڈیٹا *اندرونی_2 = (SDL_Display_ڈیٹا *)ڈیٹا;

    اگر (flags & WL_OUTPUT_منوال_CURRENT) {
        اندرونی_2->geometry_بدلا |= اندرونی_2->pixel.چوڑائی != چوڑائی || اندرونی_2->pixel.اونچائی != اونچائی;
        اندرونی_2->pixel.چوڑائی = چوڑائی;
        اندرونی_2->pixel.اونچائی = اونچائی;

        /*
         * Don't rotate this yet, wl-output coordinates are transformed in
         * handle_done and xdg-output coordinates are pre-transformed.
         */
        اگر (!اندرونی_2->has_logical_سائز) {
            اندرونی_2->geometry_بدلا |= اندرونی_2->logical.چوڑائی != چوڑائی || اندرونی_2->logical.اونچائی != اونچائی;
            اندرونی_2->logical.چوڑائی = چوڑائی;
            اندرونی_2->logical.اونچائی = اونچائی;
        }

        اندرونی_2->refresh = refresh;
    }
}

ساکن خالی handle_wl_output_مکمل(خالی *ڈیٹا, ساخت wl_output *output)
{
    ثابت bool منوال_emulation_enabled = SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_منوال_EMULATION, true);
    SDL_Display_ڈیٹا *اندرونی_2 = (SDL_Display_ڈیٹا *)ڈیٹا;
    SDL_Video_ڈیٹا *video = اندرونی_2->videodata;
    SDL_Display_منوال native_منوال, desktop_منوال;

    /*
     * When using xdg-output, two wl-output.done events will be emitted:
     * one at the completion of wl-display and one at the completion of xdg-output.
     *
     * All required events must be received before proceeding.
     */
    ثابت صحیح event_await_گنتی = 1 + (اندرونی_2->xdg_output != تہی);

    اندرونی_2->wl_output_مکمل_گنتی = SDL_min(اندرونی_2->wl_output_مکمل_گنتی + 1, event_await_گنتی + 1);

    اگر (اندرونی_2->wl_output_مکمل_گنتی < event_await_گنتی) {
        واپس;
    }

    // If the display was already created, reset and rebuild the mode list.
    SDL_VideoDisplay *dpy = SDL_GetVideoDisplay(اندرونی_2->display);
    اگر (dpy) {
        SDL_ResetFullscreenDisplayModes(dpy);
    }

    // The native display resolution
    SDL_zero(native_منوال);
    native_منوال.format = SDL_PIXELFORMAT_XRGB8888;

    // Transform the pixel values, if necessary.
    اگر (اندرونی_2->transform & WL_OUTPUT_TRANSFORM_90) {
        native_منوال.w = اندرونی_2->pixel.اونچائی;
        native_منوال.h = اندرونی_2->pixel.چوڑائی;
    } ورنہ {
        native_منوال.w = اندرونی_2->pixel.چوڑائی;
        native_منوال.h = اندرونی_2->pixel.اونچائی;
    }
    native_منوال.refresh_شرح_numerator = اندرونی_2->refresh;
    native_منوال.refresh_شرح_denominator = 1000;

    اگر (اندرونی_2->has_logical_سائز) { // If xdg-output is present...
        اگر (native_منوال.w != اندرونی_2->logical.چوڑائی || native_منوال.h != اندرونی_2->logical.اونچائی) {
            // ...and the compositor scales the logical viewport...
            اگر (video->viewporter) {
                // ...and viewports are supported, calculate the true scale of the output.
                اندرونی_2->scale_ضربی_عدد_2 = (دوہرا)native_منوال.w / (دوہرا)اندرونی_2->logical.چوڑائی;
            } ورنہ {
                // ...otherwise, the 'native' pixel values are a multiple of the logical screen size.
                اندرونی_2->scale_ضربی_عدد_2 = اندرونی_2->integer_scale_ضربی_عدد;
                اندرونی_2->pixel.چوڑائی = اندرونی_2->logical.چوڑائی * اندرونی_2->integer_scale_ضربی_عدد;
                اندرونی_2->pixel.اونچائی = اندرونی_2->logical.اونچائی * اندرونی_2->integer_scale_ضربی_عدد;
            }
        } ورنہ {
            /* ...and the output viewport is not scaled in the global compositing
             * space, the output dimensions need to be divided by the scale factor.
             *
             * NOTE: This path is needed for old versions of GNOME that predate fractional scaling.
             */
            اندرونی_2->scale_ضربی_عدد_2 = اندرونی_2->integer_scale_ضربی_عدد;
            اندرونی_2->logical.چوڑائی /= اندرونی_2->integer_scale_ضربی_عدد;
            اندرونی_2->logical.اونچائی /= اندرونی_2->integer_scale_ضربی_عدد;
        }
    } ورنہ {
        /* Calculate the points from the pixel values, if xdg-output isn't present.
         * Use the native mode pixel values since they are pre-transformed.
         */
        اندرونی_2->scale_ضربی_عدد_2 = اندرونی_2->integer_scale_ضربی_عدد;
        اندرونی_2->logical.چوڑائی = native_منوال.w / اندرونی_2->integer_scale_ضربی_عدد;
        اندرونی_2->logical.اونچائی = native_منوال.h / اندرونی_2->integer_scale_ضربی_عدد;
    }

    // The scaled desktop mode
    SDL_zero(desktop_منوال);
    desktop_منوال.format = SDL_PIXELFORMAT_XRGB8888;

    اگر (!video->scale_مقصد_display_enabled) {
        desktop_منوال.w = اندرونی_2->logical.چوڑائی;
        desktop_منوال.h = اندرونی_2->logical.اونچائی;
        desktop_منوال.pixel_density = (اعشاری)اندرونی_2->scale_ضربی_عدد_2;
    } ورنہ {
        desktop_منوال.w = native_منوال.w;
        desktop_منوال.h = native_منوال.h;
        desktop_منوال.pixel_density = 1.0f;
    }

    desktop_منوال.refresh_شرح_numerator = اندرونی_2->refresh;
    desktop_منوال.refresh_شرح_denominator = 1000;

    اگر (اندرونی_2->display > 0) {
        dpy = SDL_GetVideoDisplay(اندرونی_2->display);
    } ورنہ {
        dpy = &اندرونی_2->placeholder;
    }

    اگر (video->scale_مقصد_display_enabled) {
        SDL_سیٹ_Display_Content_Scale(dpy, (اعشاری)اندرونی_2->scale_ضربی_عدد_2);
    }

    // Set the desktop display mode.
    SDL_سیٹ_Desktop_Display_منوال(dpy, &desktop_منوال);

    // Expose the unscaled, native resolution if the scale is 1.0 or viewports are available...
    اگر (اندرونی_2->scale_ضربی_عدد_2 == 1.0 || video->viewporter) {
        SDL_جوڑو_Fullscreen_Display_منوال(dpy, &native_منوال);
        اگر (native_منوال.w != desktop_منوال.w ||
            native_منوال.h != desktop_منوال.h) {
            SDL_جوڑو_Fullscreen_Display_منوال(dpy, &desktop_منوال);
        }
    } ورنہ {
        // ...otherwise expose the integer scaled variants of the desktop resolution down to 1.
        desktop_منوال.pixel_density = 1.0f;

        برائے (صحیح i = (صحیح)اندرونی_2->scale_ضربی_عدد_2; i > 0; --i) {
            desktop_منوال.w = اندرونی_2->logical.چوڑائی * i;
            desktop_منوال.h = اندرونی_2->logical.اونچائی * i;
            SDL_جوڑو_Fullscreen_Display_منوال(dpy, &desktop_منوال);
        }
    }

    // Add emulated modes if wp_viewporter is supported and mode emulation is enabled.
    اگر (video->viewporter && منوال_emulation_enabled) {
        // The transformed display pixel width/height must be used here.
        جوڑو_Emulated_Modes(اندرونی_2, native_منوال.w, native_منوال.h);
    }

    اگر (اندرونی_2->display == 0) {
        // First time getting display info, initialize the VideoDisplay
        اگر (اندرونی_2->physical.چوڑائی_mm >= اندرونی_2->physical.اونچائی_mm) {
            اندرونی_2->placeholder.natural_orientation = SDL_ORIENTATION_LANDSCAPE;
        } ورنہ {
            اندرونی_2->placeholder.natural_orientation = SDL_ORIENTATION_PORTRAIT;
        }
        اندرونی_2->placeholder.current_orientation = اندرونی_2->orientation;
        اندرونی_2->placeholder.اندرونی_2 = اندرونی_2;

        اندرونی_2->placeholder.props = SDL_CreateProperties();
        SDL_سیٹ_اشارہ_گر_Property(اندرونی_2->placeholder.props, SDL_PROP_DISPLAY_WAYLAND_WL_OUTPUT_اشارہ_گر, اندرونی_2->output);

        // During initialization, the displays will be added after enumeration is complete.
        اگر (!video->initializing) {
            اگر (video->wp_color_manager_v1) {
                Wayland_GetColorInfoForOutput(اندرونی_2, false);
            }
            اگر (video->scale_مقصد_display_enabled) {
                Wayland_DeriveOutputPixelCoordinates(video);
            }

            اندرونی_2->display = SDL_جوڑو_Video_Display(&اندرونی_2->placeholder, true);
            Wayland_Refresh_کھڑکی_Positions();

            SDL_free(اندرونی_2->placeholder.name);
            SDL_zero(اندرونی_2->placeholder);
        }
    } ورنہ {
        SDL_SendDisplayEvent(dpy, SDL_EVENT_DISPLAY_ORIENTATION, اندرونی_2->orientation, 0);

        اگر (اندرونی_2->geometry_بدلا) {
            اگر (video->scale_مقصد_display_enabled) {
                Wayland_DeriveOutputPixelCoordinates(video);
            }

            SDL_SendDisplayEvent(dpy, SDL_EVENT_DISPLAY_MOVED, 0, 0);
            Wayland_Refresh_کھڑکی_Positions();
        }
    }

    اندرونی_2->geometry_بدلا = false;
}

ساکن خالی handle_wl_output_scale(خالی *ڈیٹا, ساخت wl_output *output, int32_t ضربی_عدد)
{
    SDL_Display_ڈیٹا *اندرونی_2 = (SDL_Display_ڈیٹا *)ڈیٹا;
    اندرونی_2->integer_scale_ضربی_عدد = ضربی_عدد;
}

ساکن خالی handle_wl_output_name(خالی *ڈیٹا, ساخت wl_output *wl_output, ثابت حرف *name)
{
    SDL_Display_ڈیٹا *اندرونی_2 = (SDL_Display_ڈیٹا *)ڈیٹا;

    SDL_free(اندرونی_2->wl_output_name);
    اندرونی_2->wl_output_name = SDL_strdup(name);
}

ساکن خالی handle_wl_output_description(خالی *ڈیٹا, ساخت wl_output *wl_output, ثابت حرف *description)
{
    SDL_Display_ڈیٹا *اندرونی_2 = (SDL_Display_ڈیٹا *)ڈیٹا;

    اگر (اندرونی_2->display == 0) {
        // The description, if available, supersedes the model name.
        SDL_free(اندرونی_2->placeholder.name);
        اندرونی_2->placeholder.name = SDL_strdup(description);
    }
}

ساکن ثابت ساخت wl_output_listener output_listener = {
    handle_wl_output_geometry,   // Version 1
    handle_wl_output_منوال,       // Version 1
    handle_wl_output_مکمل,       // Version 2
    handle_wl_output_scale,      // Version 2
    handle_wl_output_name,       // Version 4
    handle_wl_output_description // Version 4
};

ساکن خالی handle_output_image_description_بدلا(خالی *ڈیٹا,
                                                    ساخت wp_color_management_output_v1 *wp_color_management_output_v1)
{
    SDL_Display_ڈیٹا *display = (SDL_Display_ڈیٹا *)ڈیٹا;
    Wayland_GetColorInfoForOutput(display, false);
}

ساکن ثابت ساخت wp_color_management_output_v1_listener wp_color_management_output_listener = {
    handle_output_image_description_بدلا
};

ساکن bool Wayland_جوڑو_display(SDL_Video_ڈیٹا *d, uint32_t id, uint32_t نسخہ)
{
    ساخت wl_output *output;
    SDL_Display_ڈیٹا *ڈیٹا;

    output = wl_registry_bind(d->registry, id, &wl_output_interface, نسخہ);
    اگر (!output) {
        واپس SDL_سیٹ_Error("Failed to retrieve output.");
    }
    ڈیٹا = (SDL_Display_ڈیٹا *)SDL_calloc(1, حجم(*ڈیٹا));
    ڈیٹا->videodata = d;
    ڈیٹا->output = output;
    ڈیٹا->registry_id = id;
    ڈیٹا->scale_ضربی_عدد_2 = 1.0f;
    ڈیٹا->integer_scale_ضربی_عدد = 1;

    wl_output_جوڑو_listener(output, &output_listener, ڈیٹا);
    SDL_WAYLAND_رجسٹر_output(output);

    // Keep a list of outputs for sorting and deferred protocol initialization.
    اگر (d->output_گنتی == d->output_max) {
        d->output_max += 4;
        d->output_list = SDL_realloc(d->output_list, حجم(SDL_Display_ڈیٹا *) * d->output_max);
    }
    d->output_list[d->output_گنتی++] = ڈیٹا;

    اگر (ڈیٹا->videodata->xdg_output_manager) {
        ڈیٹا->xdg_output = zxdg_output_manager_v1_get_xdg_output(ڈیٹا->videodata->xdg_output_manager, output);
        zxdg_output_v1_جوڑو_listener(ڈیٹا->xdg_output, &xdg_output_listener, ڈیٹا);
    }
    اگر (ڈیٹا->videodata->wp_color_manager_v1) {
        ڈیٹا->wp_color_management_output = wp_color_manager_v1_get_output(ڈیٹا->videodata->wp_color_manager_v1, output);
        wp_color_management_output_v1_جوڑو_listener(ڈیٹا->wp_color_management_output, &wp_color_management_output_listener, ڈیٹا);

        // If not initializing, this will be queried synchronously in wl_output.done.
        اگر (d->initializing) {
            Wayland_GetColorInfoForOutput(ڈیٹا, true);
        }
    }
    واپس true;
}

ساکن خالی Wayland_free_display(SDL_VideoDisplay *display, bool send_event)
{
    اگر (display) {
        SDL_Display_ڈیٹا *display_ڈیٹا = display->اندرونی_2;

        /* A preceding surface leave event is not guaranteed when an output is removed,
         * so ensure that no window continues to hold a reference to a removed output.
         */
        برائے (SDL_کھڑکی *کھڑکی = SDL_GetVideoDevice()->windows; کھڑکی; کھڑکی = کھڑکی->اگلا) {
            Wayland_Remove_Output_From_کھڑکی(کھڑکی->اندرونی_2, display_ڈیٹا);
        }

        SDL_free(display_ڈیٹا->wl_output_name);

        اگر (display_ڈیٹا->wp_color_management_output) {
            Wayland_FreeColorInfoState(display_ڈیٹا->color_info_state);
            wp_color_management_output_v1_destroy(display_ڈیٹا->wp_color_management_output);
        }

        اگر (display_ڈیٹا->xdg_output) {
            zxdg_output_v1_destroy(display_ڈیٹا->xdg_output);
        }

        اگر (wl_output_get_نسخہ(display_ڈیٹا->output) >= WL_OUTPUT_RELEASE_SINCE_نسخہ) {
            wl_output_release(display_ڈیٹا->output);
        } ورنہ {
            wl_output_destroy(display_ڈیٹا->output);
        }

        SDL_DelVideoDisplay(display->id, send_event);
    }
}

ساکن خالی Wayland_FinalizeDisplays(SDL_Video_ڈیٹا *vid)
{
    Wayland_ترتیب_دو_Outputs(vid);

    برائے(صحیح i = 0; i < vid->output_گنتی; ++i) {
        SDL_Display_ڈیٹا *d = vid->output_list[i];
        d->display = SDL_جوڑو_Video_Display(&d->placeholder, false);
        SDL_free(d->placeholder.name);
        SDL_zero(d->placeholder);
    }
}

ساکن خالی Wayland_init_xdg_output(SDL_Video_ڈیٹا *d)
{
    برائے (صحیح i = 0; i < d->output_گنتی; ++i) {
        SDL_Display_ڈیٹا *disp = d->output_list[i];
        disp->xdg_output = zxdg_output_manager_v1_get_xdg_output(disp->videodata->xdg_output_manager, disp->output);
        zxdg_output_v1_جوڑو_listener(disp->xdg_output, &xdg_output_listener, disp);
    }
}

ساکن خالی Wayland_InitColorManager(SDL_Video_ڈیٹا *d)
{
    برائے (صحیح i = 0; i < d->output_گنتی; ++i) {
        SDL_Display_ڈیٹا *disp = d->output_list[i];
        disp->wp_color_management_output = wp_color_manager_v1_get_output(disp->videodata->wp_color_manager_v1, disp->output);
        wp_color_management_output_v1_جوڑو_listener(disp->wp_color_management_output, &wp_color_management_output_listener, disp);
        Wayland_GetColorInfoForOutput(disp, true);
    }
}

ساکن خالی handle_xdg_session_created(خالی *ڈیٹا, ساخت xdg_session_v1 *xdg_session_v1, ثابت حرف *id)
{
    SDL_سیٹ_String_Property(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, id);
}

ساکن خالی handle_xdg_session_restored(خالی *ڈیٹا, ساخت xdg_session_v1 *xdg_session_v1)
{
    // NOP
}

ساکن خالی handle_xdg_session_replaced(خالی *ڈیٹا, ساخت xdg_session_v1 *xdg_session_v1)
{
    SDL_VideoDevice *viddev = SDL_GetVideoDevice();
    SDL_Video_ڈیٹا *viddata = ڈیٹا;

    // Clean up all session objects, as they have become inert, and should be destroyed.
    SDL_سیٹ_String_Property(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, تہی);

    برائے (SDL_کھڑکی *w = viddev->windows; w; w = w->اگلا) {
        SDL_کھڑکی_ڈیٹا *d = w->اندرونی_2;

        اگر (d->xdg_toplevel_session) {
            xdg_toplevel_session_v1_destroy(d->xdg_toplevel_session);
            d->xdg_toplevel_session = تہی;

            SDL_free(d->session_id);
            d->session_id = تہی;
        }
    }

    اگر (viddata->xdg_session) {
        xdg_session_v1_destroy(viddata->xdg_session);
        viddata->xdg_session = تہی;
    }
}

ساکن ثابت ساخت xdg_session_v1_listener xdg_session_listener = {
    .created  = handle_xdg_session_created,
    .restored = handle_xdg_session_restored,
    .replaced = handle_xdg_session_replaced
};

خالی Wayland_CreateSession(SDL_Video_ڈیٹا *viddata)
{
    اگر (!viddata->xdg_session_manager) {
        // Set the ID string to null if session management is not available.
        SDL_سیٹ_String_Property(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, تہی);
        واپس;
    }

    // Register a new session, if one does not yet exist.
    اگر (!viddata->xdg_session) {
        ثابت حرف *session_id = SDL_GetStringProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, تہی);
        اگر (session_id) {
            اگر (*session_id == '\0') {
                // Create a new session if the ID string is empty.
                session_id = تہی;
            }

            ثابت شمار xdg_session_manager_v1_reason reason = session_id ? XDG_SESSION_MANAGER_V1_REASON_SESSION_RESTORE : XDG_SESSION_MANAGER_V1_REASON_LAUNCH;
            viddata->xdg_session = xdg_session_manager_v1_get_session(viddata->xdg_session_manager, reason, session_id);
            xdg_session_v1_جوڑو_listener(viddata->xdg_session, &xdg_session_listener, viddata);
        }
    }
}

ساکن خالی Wayland_SessionDestroy(SDL_Video_ڈیٹا *viddata)
{
    // If the session string was cleared, remove the session.
    اگر (viddata->xdg_session) {
        ثابت حرف *session_id = SDL_GetStringProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, تہی);
        اگر (!session_id || *session_id == '\0') {
            xdg_session_v1_remove(viddata->xdg_session);

            WAYLAND_wl_display_roundtrip(viddata->display);
        } ورنہ {
            xdg_session_v1_destroy(viddata->xdg_session);
        }

        viddata->xdg_session = تہی;
    }
}

ساکن خالی handle_xdg_wm_بنیاد_ping(خالی *ڈیٹا, ساخت xdg_wm_بنیاد *xdg, uint32_t serial)
{
    xdg_wm_بنیاد_pong(xdg, serial);
}

ساکن ثابت ساخت xdg_wm_بنیاد_listener xdg_wm_بنیاد_listener_2 = {
    handle_xdg_wm_بنیاد_ping
};

#اگر_تعریف_شدہ HAVE_LIBDECOR_H
ساکن خالی libdecor_error(ساخت libdecor *context,
                           شمار libdecor_error error,
                           ثابت حرف *پیغام)
{
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "libdecor error (%d): %s", error, پیغام);
}

ساکن ساخت libdecor_interface libdecor_interface = {
    libdecor_error
};
#اگر_ختم

ساکن خالی handle_registry_global(خالی *ڈیٹا, ساخت wl_registry *registry, uint32_t id,
                                   ثابت حرف *interface, uint32_t نسخہ)
{
    SDL_Video_ڈیٹا *d = ڈیٹا;

    اگر (SDL_strcmp(interface, wl_compositor_interface.name) == 0) {
        d->compositor = wl_registry_bind(d->registry, id, &wl_compositor_interface, SDL_min(SDL_WL_COMPOSITOR_نسخہ, نسخہ));
    } ورنہ اگر (SDL_strcmp(interface, wl_subcompositor_interface.name) == 0) {
        d->subcompositor = wl_registry_bind(d->registry, id, &wl_subcompositor_interface, 1);
    } ورنہ اگر (SDL_strcmp(interface, wl_output_interface.name) == 0) {
        Wayland_جوڑو_display(d, id, SDL_min(نسخہ, SDL_WL_OUTPUT_نسخہ));
    } ورنہ اگر (SDL_strcmp(interface, wl_seat_interface.name) == 0) {
        ساخت wl_seat *seat = wl_registry_bind(d->registry, id, &wl_seat_interface, SDL_min(SDL_WL_SEAT_نسخہ, نسخہ));
        Wayland_DisplayCreateSeat(d, seat, id);
    } ورنہ اگر (SDL_strcmp(interface, xdg_wm_بنیاد_interface.name) == 0) {
        d->shell.xdg = wl_registry_bind(d->registry, id, &xdg_wm_بنیاد_interface, SDL_min(نسخہ, 7));
        xdg_wm_بنیاد_جوڑو_listener(d->shell.xdg, &xdg_wm_بنیاد_listener_2, تہی);
    } ورنہ اگر (SDL_strcmp(interface, wl_shm_interface.name) == 0) {
        d->shm = wl_registry_bind(registry, id, &wl_shm_interface, SDL_min(SDL_WL_SHM_نسخہ, نسخہ));
    } ورنہ اگر (SDL_strcmp(interface, zwp_relative_اشارہ_گر_manager_v1_interface.name) == 0) {
        d->relative_اشارہ_گر_manager = wl_registry_bind(d->registry, id, &zwp_relative_اشارہ_گر_manager_v1_interface, 1);
    } ورنہ اگر (SDL_strcmp(interface, zwp_اشارہ_گر_constraints_v1_interface.name) == 0) {
        d->اشارہ_گر_constraints = wl_registry_bind(d->registry, id, &zwp_اشارہ_گر_constraints_v1_interface, 1);
    } ورنہ اگر (SDL_strcmp(interface, zwp_keyboard_shortcuts_inhibit_manager_v1_interface.name) == 0) {
        d->کلید_inhibitor_manager = wl_registry_bind(d->registry, id, &zwp_keyboard_shortcuts_inhibit_manager_v1_interface, 1);
    } ورنہ اگر (SDL_strcmp(interface, zwp_idle_inhibit_manager_v1_interface.name) == 0) {
        d->idle_inhibit_manager = wl_registry_bind(d->registry, id, &zwp_idle_inhibit_manager_v1_interface, 1);
    } ورنہ اگر (SDL_strcmp(interface, xdg_activation_v1_interface.name) == 0) {
        d->activation_manager = wl_registry_bind(d->registry, id, &xdg_activation_v1_interface, 1);
    } ورنہ اگر (SDL_strcmp(interface, zwp_متن_داخلہ_manager_v3_interface.name) == 0) {
        d->متن_داخلہ_manager = wl_registry_bind(d->registry, id, &zwp_متن_داخلہ_manager_v3_interface, 1);
        Wayland_Display_Init_متن_داخلہ_Manager(d, id);
    } ورنہ اگر (SDL_strcmp(interface, wl_ڈیٹا_device_manager_interface.name) == 0) {
        d->ڈیٹا_device_manager = wl_registry_bind(d->registry, id, &wl_ڈیٹا_device_manager_interface, SDL_min(3, نسخہ));
        Wayland_Display_Init_ڈیٹا_Device_Manager(d);
    } ورنہ اگر (SDL_strcmp(interface, zwp_primary_selection_device_manager_v1_interface.name) == 0) {
        d->primary_selection_device_manager = wl_registry_bind(d->registry, id, &zwp_primary_selection_device_manager_v1_interface, 1);
        Wayland_DisplayInitPrimarySelectionDeviceManager(d);
    } ورنہ اگر (SDL_strcmp(interface, zxdg_decoration_manager_v1_interface.name) == 0) {
        d->decoration_manager = wl_registry_bind(d->registry, id, &zxdg_decoration_manager_v1_interface, SDL_min(2, نسخہ));
    } ورنہ اگر (SDL_strcmp(interface, zwp_tablet_manager_v2_interface.name) == 0) {
        d->tablet_manager = wl_registry_bind(d->registry, id, &zwp_tablet_manager_v2_interface, 1);
        Wayland_DisplayInitTabletManager(d);
    } ورنہ اگر (SDL_strcmp(interface, zxdg_output_manager_v1_interface.name) == 0) {
        نسخہ = SDL_min(نسخہ, 3); // Versions 1 through 3 are supported.
        d->xdg_output_manager = wl_registry_bind(d->registry, id, &zxdg_output_manager_v1_interface, نسخہ);
        Wayland_init_xdg_output(d);
    } ورنہ اگر (SDL_strcmp(interface, wp_viewporter_interface.name) == 0) {
        d->viewporter = wl_registry_bind(d->registry, id, &wp_viewporter_interface, 1);
    } ورنہ اگر (SDL_strcmp(interface, wp_fractional_scale_manager_v1_interface.name) == 0) {
        d->fractional_scale_manager = wl_registry_bind(d->registry, id, &wp_fractional_scale_manager_v1_interface, 1);
    } ورنہ اگر (SDL_strcmp(interface, zwp_داخلہ_timestamps_manager_v1_interface.name) == 0) {
        d->داخلہ_timestamps_manager = wl_registry_bind(d->registry, id, &zwp_داخلہ_timestamps_manager_v1_interface, 1);
        Wayland_Display_Init_داخلہ_Timestamp_Manager(d);
    } ورنہ اگر (SDL_strcmp(interface, wp_cursor_shape_manager_v1_interface.name) == 0) {
        d->cursor_shape_manager = wl_registry_bind(d->registry, id, &wp_cursor_shape_manager_v1_interface, SDL_min(نسخہ, 2));
        Wayland_DisplayInitCursorShapeManager(d);
    } ورنہ اگر (SDL_strcmp(interface, zxdg_exporter_v2_interface.name) == 0) {
        d->zxdg_exporter_v2 = wl_registry_bind(d->registry, id, &zxdg_exporter_v2_interface, 1);
    } ورنہ اگر (SDL_strcmp(interface, xdg_wm_dialog_v1_interface.name) == 0) {
        d->xdg_wm_dialog_v1 = wl_registry_bind(d->registry, id, &xdg_wm_dialog_v1_interface, 1);
    } ورنہ اگر (SDL_strcmp(interface, wp_alpha_modifier_v1_interface.name) == 0) {
        d->wp_alpha_modifier_v1 = wl_registry_bind(d->registry, id, &wp_alpha_modifier_v1_interface, 1);
    } ورنہ اگر (SDL_strcmp(interface, xdg_toplevel_icon_manager_v1_interface.name) == 0) {
        d->xdg_toplevel_icon_manager_v1 = wl_registry_bind(d->registry, id, &xdg_toplevel_icon_manager_v1_interface, 1);
    } ورنہ اگر (SDL_strcmp(interface, frog_color_management_factory_v1_interface.name) == 0) {
        d->frog_color_management_factory_v1 = wl_registry_bind(d->registry, id, &frog_color_management_factory_v1_interface, 1);
    } ورنہ اگر (SDL_strcmp(interface, wp_color_manager_v1_interface.name) == 0) {
        d->wp_color_manager_v1 = wl_registry_bind(d->registry, id, &wp_color_manager_v1_interface, SDL_min(نسخہ, 2));
        Wayland_InitColorManager(d);
    } ورنہ اگر (SDL_strcmp(interface, wp_اشارہ_گر_warp_v1_interface.name) == 0) {
        d->wp_اشارہ_گر_warp_v1 = wl_registry_bind(d->registry, id, &wp_اشارہ_گر_warp_v1_interface, 1);
    } ورنہ اگر (SDL_strcmp(interface, zwp_اشارہ_گر_gestures_v1_interface.name) == 0) {
        d->zwp_اشارہ_گر_gestures = wl_registry_bind(d->registry, id, &zwp_اشارہ_گر_gestures_v1_interface, SDL_min(نسخہ, 3));
        Wayland_Display_Init_اشارہ_گر_Gesture_Manager(d);
    } ورنہ اگر (SDL_strcmp(interface, wp_single_pixel_بفر_manager_v1_interface.name) == 0) {
        d->single_pixel_بفر_manager = wl_registry_bind(d->registry, id, &wp_single_pixel_بفر_manager_v1_interface, 1);
    } ورنہ اگر (SDL_strcmp(interface, xdg_session_manager_v1_interface.name) == 0) {
        d->xdg_session_manager = wl_registry_bind(d->registry, id, &xdg_session_manager_v1_interface, 1);
    } ورنہ اگر (SDL_strcmp(interface, xdg_toplevel_لیبل_manager_v1_interface.name) == 0) {
        d->xdg_toplevel_لیبل_manager = wl_registry_bind(d->registry, id, &xdg_toplevel_لیبل_manager_v1_interface, 1);
    }
#اگر_تعریف_شدہ SDL_WL_FIXES_نسخہ
    ورنہ اگر (SDL_strcmp(interface, wl_fixes_interface.name) == 0) {
        d->wl_fixes = wl_registry_bind(d->registry, id, &wl_fixes_interface, SDL_min(SDL_WL_FIXES_نسخہ, نسخہ));
    }
#اگر_ختم
}

ساکن خالی handle_registry_remove_global(خالی *ڈیٹا, ساخت wl_registry *registry, uint32_t id)
{
    SDL_Video_ڈیٹا *d = ڈیٹا;

    // We don't get an interface, just an ID, so check outputs and seats.
    برائے (صحیح i = 0; i < d->output_گنتی; ++i) {
        SDL_Display_ڈیٹا *disp = d->output_list[i];
        اگر (disp->registry_id == id) {
            Wayland_free_display(SDL_GetVideoDisplay(disp->display), true);

            اگر (i < d->output_گنتی) {
                SDL_memmove(&d->output_list[i], &d->output_list[i + 1], حجم(SDL_Display_ڈیٹا *) * (d->output_گنتی - i - 1));
            }

            d->output_گنتی--;
            جاؤ ack_remove;
        }
    }

    SDL_WaylandSeat *seat, *عارضی;
    wl_list_for_each_محفوظ (seat, عارضی, &d->seat_list, link) {
        اگر (seat->registry_id == id) {
            Wayland_SeatDestroy(seat, false);
            جاؤ ack_remove;
        }
    }

ack_remove:
    اگر (d->wl_fixes && wl_fixes_get_نسخہ(d->wl_fixes) >= WL_FIXES_ACK_GLOBAL_REMOVE_SINCE_نسخہ) {
        wl_fixes_ack_global_remove(d->wl_fixes, registry, id);
    }
}

ساکن ثابت ساخت wl_registry_listener registry_listener = {
    handle_registry_global,
    handle_registry_remove_global
};

#اگر_تعریف_شدہ HAVE_LIBDECOR_H
ساکن bool should_use_libdecor(SDL_Video_ڈیٹا *ڈیٹا, bool ignore_xdg)
{
    اگر (!SDL_WAYLAND_HAVE_WAYLAND_LIBDECOR) {
        واپس false;
    }

    اگر (SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_PREFER_LIBDECOR, false)) {
        واپس true;
    }

    اگر (ignore_xdg) {
        واپس true;
    }

    اگر (ڈیٹا->decoration_manager) {
        واپس false;
    }

    واپس true;
}

ساکن خالی LibdecorNew(SDL_Video_ڈیٹا *ڈیٹا)
{
    ڈیٹا->shell.libdecor = libdecor_new(ڈیٹا->display, &libdecor_interface);
}

// Called in another thread, but the UI thread is blocked in SDL_WaitThread
// during that time, so it should be OK to dereference data without locks
ساکن صحیح SDLCALL Libdecor_New_اندر_Thread(خالی *ڈیٹا)
{
    LibdecorNew((SDL_Video_ڈیٹا *)ڈیٹا);
    واپس 0;
}
#اگر_ختم

#اگر_تعریف_شدہ HAVE_GETRESUID
#تعریف_کرو SDL_getresuid getresuid
#ورنہ
// Non-POSIX, but Linux and some BSDs have it.
// To reduce the number of code paths, if getresuid() isn't available at
// compile-time, we behave as though it existed but failed at runtime.
ساکن اندرونی صحیح SDL_getresuid(uid_t *ruid, uid_t *euid, uid_t *suid) {
    errno = ENOSYS;
    واپس -1;
}
#اگر_ختم

#اگر_تعریف_شدہ HAVE_GETRESGID
#تعریف_کرو SDL_getresgid getresgid
#ورنہ
// Same as getresuid() but for the primary group
ساکن اندرونی صحیح SDL_getresgid(gid_t *rgid, gid_t *egid, gid_t *sgid) {
    errno = ENOSYS;
    واپس -1;
}
#اگر_ختم

bool CanUseGtk(خالی)
{
    // "Real", "effective" and "saved" IDs: see e.g. Linux credentials(7)
    uid_t ruid = -1, euid = -1, suid = -1;
    gid_t rgid = -1, egid = -1, sgid = -1;

    اگر (!SDL_GetHintBoolean("SDL_ENABLE_GTK", true)) {
        SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "Not using GTK due to hint");
        واپس false;
    }

    // This is intended to match the check in gtkmain.c, rather than being
    // an exhaustive check for having elevated privileges: as a result
    // we don't use Linux getauxval() or prctl PR_GET_DUMPABLE,
    // BSD issetugid(), or similar OS-specific detection

    اگر (SDL_getresuid(&ruid, &euid, &suid) != 0) {
        ruid = suid = getuid();
        euid = geteuid();
    }

    اگر (SDL_getresgid(&rgid, &egid, &sgid) != 0) {
        rgid = sgid = getgid();
        egid = getegid();
    }

    // Real ID != effective ID means we are setuid or setgid:
    // GTK will refuse to initialize, and instead will call exit().
    اگر (ruid != euid || rgid != egid) {
        SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "Not using GTK due to setuid/setgid");
        واپس false;
    }

    // Real ID != saved ID means we are setuid or setgid, we previously
    // dropped privileges, but we can regain them; this protects against
    // accidents but does not protect against arbitrary code execution.
    // Again, GTK will refuse to initialize if this is the case.
    اگر (ruid != suid || rgid != sgid) {
        SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "Not using GTK due to saved uid/gid");
        واپس false;
    }

    واپس true;
}

bool Wayland_بھرو_Libdecor(SDL_Video_ڈیٹا *ڈیٹا, bool ignore_xdg)
{
#اگر_تعریف_شدہ HAVE_LIBDECOR_H
    اگر (ڈیٹا->shell.libdecor != تہی) {
        واپس true; // Already loaded!
    }
    اگر (should_use_libdecor(ڈیٹا, ignore_xdg)) {
        اگر (CanUseGtk()) {
            LibdecorNew(ڈیٹا);
        } ورنہ {
            // Intentionally initialize libdecor in a non-main thread
            // so that it will not use its GTK plugin, but instead will
            // fall back to the Cairo or dummy plugin
            SDL_Thread *thread = SDL_CreateThread(Libdecor_New_اندر_Thread, "SDL_LibdecorNew", (خالی *)ڈیٹا);
            // Note that the other thread now "owns" data until we have
            // waited for it, so don't touch data here
            SDL_WaitThread(thread, تہی);
        }

        واپس ڈیٹا->shell.libdecor != تہی;
    }
#اگر_ختم
    واپس false;
}

bool Wayland_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;

    ڈیٹا->event_thread_context = Wayland_CreateEventThread(ڈیٹا, "SDL Event Thread Queue");
    اگر (!ڈیٹا->event_thread_context) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Failed to create event thread context");
    }

    ڈیٹا->کام_thread_context = Wayland_Create_کام_Thread();
    اگر (!ڈیٹا->کام_thread_context) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Failed to create job thread context");
    }

    ڈیٹا->xkb_context = WAYLAND_xkb_context_new(0);
    اگر (!ڈیٹا->xkb_context) {
        واپس SDL_سیٹ_Error("Failed to create XKB context");
    }

    ڈیٹا->registry = wl_display_get_registry(ڈیٹا->display);
    اگر (!ڈیٹا->registry) {
        واپس SDL_سیٹ_Error("Failed to get the Wayland registry");
    }

    wl_registry_جوڑو_listener(ڈیٹا->registry, &registry_listener, ڈیٹا);

    // First roundtrip to receive all registry objects.
    WAYLAND_wl_display_roundtrip(ڈیٹا->display);

    // Require viewports and xdg-output for display scaling.
    اگر (ڈیٹا->scale_مقصد_display_enabled) {
        اگر (!ڈیٹا->viewporter) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Display scaling requires the missing 'wp_viewporter' protocol: disabling");
            ڈیٹا->scale_مقصد_display_enabled = false;
        }
        اگر (!ڈیٹا->xdg_output_manager) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Display scaling requires the missing 'zxdg_output_manager_v1' protocol: disabling");
            ڈیٹا->scale_مقصد_display_enabled = false;
        }
    }

    // Now that we have all the protocols, load libdecor if applicable
    Wayland_بھرو_Libdecor(ڈیٹا, false);

    // Second roundtrip to receive all output events.
    WAYLAND_wl_display_roundtrip(ڈیٹا->display);

    Wayland_FinalizeDisplays(ڈیٹا);

    Wayland_InitMouse(ڈیٹا);
    Wayland_InitKeyboard(_this);

    اگر (ڈیٹا->primary_selection_device_manager) {
        _this->سیٹ_Primary_Selection_متن = Wayland_سیٹ_Primary_Selection_متن;
        _this->Get_Primary_Selection_متن = Wayland_Get_Primary_Selection_متن;
        _this->Has_Primary_Selection_متن = Wayland_Has_Primary_Selection_متن;
    }

    ڈیٹا->initializing = false;

    واپس true;
}

ساکن bool Wayland_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    SDL_Video_ڈیٹا *viddata = _this->اندرونی_2;
    SDL_Display_ڈیٹا *اندرونی_2 = display->اندرونی_2;

    اگر (!viddata->scale_مقصد_display_enabled) {
        rect->x = اندرونی_2->logical.x;
        rect->y = اندرونی_2->logical.y;
    } ورنہ {
        rect->x = اندرونی_2->pixel.x;
        rect->y = اندرونی_2->pixel.y;
    }

    // When an emulated, exclusive fullscreen window has focus, treat the mode dimensions as the display bounds.
    اگر (display->fullscreen_کھڑکی &&
        display->fullscreen_کھڑکی->fullscreen_exclusive &&
        display->fullscreen_کھڑکی->اندرونی_2->فعال &&
        display->fullscreen_کھڑکی->current_fullscreen_منوال.w != 0 &&
        display->fullscreen_کھڑکی->current_fullscreen_منوال.h != 0) {
        rect->w = display->fullscreen_کھڑکی->current_fullscreen_منوال.w;
        rect->h = display->fullscreen_کھڑکی->current_fullscreen_منوال.h;
    } ورنہ {
        اگر (!viddata->scale_مقصد_display_enabled) {
            rect->w = display->current_منوال->w;
            rect->h = display->current_منوال->h;
        } ورنہ اگر (اندرونی_2->transform & WL_OUTPUT_TRANSFORM_90) {
            rect->w = اندرونی_2->pixel.اونچائی;
            rect->h = اندرونی_2->pixel.چوڑائی;
        } ورنہ {
            rect->w = اندرونی_2->pixel.چوڑائی;
            rect->h = اندرونی_2->pixel.اونچائی;
        }
    }
    واپس true;
}

ساکن خالی Wayland_VideoCleanup(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    SDL_WaylandSeat *seat, *tmp;

    Wayland_SessionDestroy(ڈیٹا);

    برائے (صحیح i = _this->عدد_displays - 1; i >= 0; --i) {
        SDL_VideoDisplay *display = _this->displays[i];
        Wayland_free_display(display, false);
    }
    SDL_free(ڈیٹا->output_list);

    wl_list_for_each_محفوظ (seat, tmp, &ڈیٹا->seat_list, link) {
        Wayland_SeatDestroy(seat, true);
    }

    Wayland_FiniMouse(ڈیٹا);
    Wayland_QuitKeyboard(_this);

    Wayland_DestroyEventThread(ڈیٹا->event_thread_context);
    ڈیٹا->event_thread_context = تہی;

    Wayland_Destroy_کام_Thread(ڈیٹا->کام_thread_context);
    ڈیٹا->کام_thread_context = تہی;

    اگر (ڈیٹا->اشارہ_گر_constraints) {
        zwp_اشارہ_گر_constraints_v1_destroy(ڈیٹا->اشارہ_گر_constraints);
        ڈیٹا->اشارہ_گر_constraints = تہی;
    }

    اگر (ڈیٹا->relative_اشارہ_گر_manager) {
        zwp_relative_اشارہ_گر_manager_v1_destroy(ڈیٹا->relative_اشارہ_گر_manager);
        ڈیٹا->relative_اشارہ_گر_manager = تہی;
    }

    اگر (ڈیٹا->activation_manager) {
        xdg_activation_v1_destroy(ڈیٹا->activation_manager);
        ڈیٹا->activation_manager = تہی;
    }

    اگر (ڈیٹا->idle_inhibit_manager) {
        zwp_idle_inhibit_manager_v1_destroy(ڈیٹا->idle_inhibit_manager);
        ڈیٹا->idle_inhibit_manager = تہی;
    }

    اگر (ڈیٹا->کلید_inhibitor_manager) {
        zwp_keyboard_shortcuts_inhibit_manager_v1_destroy(ڈیٹا->کلید_inhibitor_manager);
        ڈیٹا->کلید_inhibitor_manager = تہی;
    }

    اگر (ڈیٹا->متن_داخلہ_manager) {
        zwp_متن_داخلہ_manager_v3_destroy(ڈیٹا->متن_داخلہ_manager);
        ڈیٹا->متن_داخلہ_manager = تہی;
    }

    اگر (ڈیٹا->xkb_context) {
        WAYLAND_xkb_context_unref(ڈیٹا->xkb_context);
        ڈیٹا->xkb_context = تہی;
    }

    اگر (ڈیٹا->tablet_manager) {
        zwp_tablet_manager_v2_destroy((ساخت zwp_tablet_manager_v2 *)ڈیٹا->tablet_manager);
        ڈیٹا->tablet_manager = تہی;
    }

    اگر (ڈیٹا->ڈیٹا_device_manager) {
        wl_ڈیٹا_device_manager_destroy(ڈیٹا->ڈیٹا_device_manager);
        ڈیٹا->ڈیٹا_device_manager = تہی;
    }

    اگر (ڈیٹا->shm) {
        اگر (wl_shm_get_نسخہ(ڈیٹا->shm) >= WL_SHM_RELEASE_SINCE_نسخہ) {
            wl_shm_release(ڈیٹا->shm);
        } ورنہ {
            wl_shm_destroy(ڈیٹا->shm);
        }
        ڈیٹا->shm = تہی;
    }

    اگر (ڈیٹا->shell.xdg) {
        xdg_wm_بنیاد_destroy(ڈیٹا->shell.xdg);
        ڈیٹا->shell.xdg = تہی;
    }

    اگر (ڈیٹا->decoration_manager) {
        zxdg_decoration_manager_v1_destroy(ڈیٹا->decoration_manager);
        ڈیٹا->decoration_manager = تہی;
    }

    اگر (ڈیٹا->xdg_output_manager) {
        zxdg_output_manager_v1_destroy(ڈیٹا->xdg_output_manager);
        ڈیٹا->xdg_output_manager = تہی;
    }

    اگر (ڈیٹا->viewporter) {
        wp_viewporter_destroy(ڈیٹا->viewporter);
        ڈیٹا->viewporter = تہی;
    }

    اگر (ڈیٹا->primary_selection_device_manager) {
        zwp_primary_selection_device_manager_v1_destroy(ڈیٹا->primary_selection_device_manager);
        ڈیٹا->primary_selection_device_manager = تہی;
    }

    اگر (ڈیٹا->fractional_scale_manager) {
        wp_fractional_scale_manager_v1_destroy(ڈیٹا->fractional_scale_manager);
        ڈیٹا->fractional_scale_manager = تہی;
    }

    اگر (ڈیٹا->داخلہ_timestamps_manager) {
        zwp_داخلہ_timestamps_manager_v1_destroy(ڈیٹا->داخلہ_timestamps_manager);
        ڈیٹا->داخلہ_timestamps_manager = تہی;
    }

    اگر (ڈیٹا->cursor_shape_manager) {
        wp_cursor_shape_manager_v1_destroy(ڈیٹا->cursor_shape_manager);
        ڈیٹا->cursor_shape_manager = تہی;
    }

    اگر (ڈیٹا->zxdg_exporter_v2) {
        zxdg_exporter_v2_destroy(ڈیٹا->zxdg_exporter_v2);
        ڈیٹا->zxdg_exporter_v2 = تہی;
    }

    اگر (ڈیٹا->xdg_wm_dialog_v1) {
        xdg_wm_dialog_v1_destroy(ڈیٹا->xdg_wm_dialog_v1);
        ڈیٹا->xdg_wm_dialog_v1 = تہی;
    }

    اگر (ڈیٹا->wp_alpha_modifier_v1) {
        wp_alpha_modifier_v1_destroy(ڈیٹا->wp_alpha_modifier_v1);
        ڈیٹا->wp_alpha_modifier_v1 = تہی;
    }

    اگر (ڈیٹا->xdg_toplevel_icon_manager_v1) {
        xdg_toplevel_icon_manager_v1_destroy(ڈیٹا->xdg_toplevel_icon_manager_v1);
        ڈیٹا->xdg_toplevel_icon_manager_v1 = تہی;
    }

    اگر (ڈیٹا->frog_color_management_factory_v1) {
        frog_color_management_factory_v1_destroy(ڈیٹا->frog_color_management_factory_v1);
        ڈیٹا->frog_color_management_factory_v1 = تہی;
    }

    اگر (ڈیٹا->wp_color_manager_v1) {
        wp_color_manager_v1_destroy(ڈیٹا->wp_color_manager_v1);
        ڈیٹا->wp_color_manager_v1 = تہی;
    }

    اگر (ڈیٹا->wp_اشارہ_گر_warp_v1) {
        wp_اشارہ_گر_warp_v1_destroy(ڈیٹا->wp_اشارہ_گر_warp_v1);
        ڈیٹا->wp_اشارہ_گر_warp_v1 = تہی;
    }

    اگر (ڈیٹا->zwp_اشارہ_گر_gestures) {
        اگر (zwp_اشارہ_گر_gestures_v1_get_نسخہ(ڈیٹا->zwp_اشارہ_گر_gestures) >= ZWP_اشارہ_گر_GESTURES_V1_RELEASE_SINCE_نسخہ) {
            zwp_اشارہ_گر_gestures_v1_release(ڈیٹا->zwp_اشارہ_گر_gestures);
        } ورنہ {
            zwp_اشارہ_گر_gestures_v1_destroy(ڈیٹا->zwp_اشارہ_گر_gestures);
        }
        ڈیٹا->zwp_اشارہ_گر_gestures = تہی;
    }

    اگر (ڈیٹا->single_pixel_بفر_manager) {
        wp_single_pixel_بفر_manager_v1_destroy(ڈیٹا->single_pixel_بفر_manager);
        ڈیٹا->single_pixel_بفر_manager = تہی;
    }

    اگر (ڈیٹا->xdg_session_manager) {
        xdg_session_manager_v1_destroy(ڈیٹا->xdg_session_manager);
        ڈیٹا->xdg_session_manager = تہی;
    }

    اگر (ڈیٹا->xdg_toplevel_لیبل_manager) {
        xdg_toplevel_لیبل_manager_v1_destroy(ڈیٹا->xdg_toplevel_لیبل_manager);
        ڈیٹا->xdg_toplevel_لیبل_manager = تہی;
    }

    اگر (ڈیٹا->subcompositor) {
        wl_subcompositor_destroy(ڈیٹا->subcompositor);
        ڈیٹا->subcompositor = تہی;
    }

    اگر (ڈیٹا->compositor) {
        wl_compositor_destroy(ڈیٹا->compositor);
        ڈیٹا->compositor = تہی;
    }

    اگر (ڈیٹا->registry) {
        اگر (ڈیٹا->wl_fixes) {
            wl_fixes_destroy_registry(ڈیٹا->wl_fixes, ڈیٹا->registry);
            wl_fixes_destroy(ڈیٹا->wl_fixes);
            ڈیٹا->wl_fixes = تہی;
        }
        wl_registry_destroy(ڈیٹا->registry);
        ڈیٹا->registry = تہی;
    }
}

ساکن bool Wayland_VideoReconnect(SDL_VideoDevice *_this)
{
#اگر 0 // TODO RECONNECT: Uncomment all when https://invent.kde.org/plasma/kwin/-/wikis/Restarting is completed
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;

    SDL_کھڑکی *کھڑکی = تہی;

    SDL_GLContext current_ctx = SDL_GL_GetCurrentContext();
    SDL_کھڑکی *current_کھڑکی = SDL_GL_Get_Current_کھڑکی();

    SDL_GL_MakeCurrent(تہی, تہی);
    Wayland_VideoCleanup(_this);

    SDL_ResetKeyboard();
    SDL_ResetMouse();
    اگر (WAYLAND_wl_display_reconnect(ڈیٹا->display) < 0) {
        واپس false;
    }

    Wayland_VideoInit(_this);

    کھڑکی = _this->windows;
    جب (کھڑکی) {
        /* We're going to cheat _just_ for a second and strip the OpenGL flag.
         * The Wayland driver actually forces it in CreateWindow, and
         * RecreateWindow does a bunch of unloading/loading of libGL, so just
         * strip the flag so RecreateWindow doesn't mess with the GL context,
         * and CreateWindow will add it right back!
         * -flibit
         */
        کھڑکی->flags &= ~SDL_کھڑکی_OPENGL;

        SDL_Recreate_کھڑکی(کھڑکی, کھڑکی->flags);
        کھڑکی = کھڑکی->اگلا;
    }

    Wayland_RecreateCursors();

    اگر (current_کھڑکی && current_ctx) {
        SDL_GL_MakeCurrent (current_کھڑکی, current_ctx);
    }
    واپس true;
#ورنہ
    واپس false;
#اگر_ختم // 0
}

bool Wayland_HandleDisplayDisconnected(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *video_ڈیٹا = _this->اندرونی_2;

    /* Something has failed with the Wayland connection -- for example,
     * the compositor may have shut down and closed its end of the socket,
     * or there is a library-specific error.
     *
     * Try to recover once, then quit.
     */
    اگر (video_ڈیٹا->display_disconnected) {
        واپس false;
    }

    اگر (Wayland_VideoReconnect(_this)) {
        واپس true;
    }

    video_ڈیٹا->display_disconnected = true;
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Wayland display connection closed by server (fatal)");

    // Only send a single quit message, as application shutdown might call SDL_PumpEvents().
    SDL_SendQuit();

    واپس false;
}

خالی Wayland_VideoQuit(SDL_VideoDevice *_this)
{
    Wayland_VideoCleanup(_this);

#اگر_تعریف_شدہ HAVE_LIBDECOR_H
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    اگر (ڈیٹا->shell.libdecor) {
        libdecor_unref(ڈیٹا->shell.libdecor);
        ڈیٹا->shell.libdecor = تہی;
    }
#اگر_ختم
}

#اگر_ختم // SDL_VIDEO_DRIVER_WAYLAND
