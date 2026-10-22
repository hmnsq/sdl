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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND

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

#جے_تعریف_شدہ HAVE_LIBDECOR_H
#ضمن <libdecor.h>
#جے_انت

#تعریف_کرو WAYLANDVID_DRIVER_NAME "wayland"

// Clamp core protocol versions on older versions of libwayland.
#إذا SDL_WAYLAND_CHECK_نسخہ(1, 22, 0)
#تعریف_کرو SDL_WL_COMPOSITOR_نسخہ 6
#وإلا
#تعریف_کرو SDL_WL_COMPOSITOR_نسخہ 4
#جے_انت

#إذا SDL_WAYLAND_CHECK_نسخہ(1, 26, 0)
#تعریف_کرو SDL_WL_SEAT_نسخہ 11
#وإلاإذا SDL_WAYLAND_CHECK_نسخہ(1, 24, 0)
#تعریف_کرو SDL_WL_SEAT_نسخہ 10
#وإلاإذا SDL_WAYLAND_CHECK_نسخہ(1, 22, 0)
#تعریف_کرو SDL_WL_SEAT_نسخہ 9
#وإلاإذا SDL_WAYLAND_CHECK_نسخہ(1, 21, 0)
#تعریف_کرو SDL_WL_SEAT_نسخہ 8
#وإلا
#تعریف_کرو SDL_WL_SEAT_نسخہ 5
#جے_انت

#إذا SDL_WAYLAND_CHECK_نسخہ(1, 20, 0)
#تعریف_کرو SDL_WL_OUTPUT_نسخہ 4
#وإلا
#تعریف_کرو SDL_WL_OUTPUT_نسخہ 3
#جے_انت

#إذا SDL_WAYLAND_CHECK_نسخہ(1, 24, 0)
#تعریف_کرو SDL_WL_SHM_نسخہ 2
#وإلا
#تعریف_کرو SDL_WL_SHM_نسخہ 1
#جے_انت

// The SDL libwayland-client minimum is 1.18, which supports version 3.
#تعریف_کرو SDL_WL_انکڑے_DEVICE_نسخہ 3

// wl_fixes was introduced in 1.24.0
#إذا SDL_WAYLAND_CHECK_نسخہ(1, 26, 0)
#تعریف_کرو SDL_WL_FIXES_نسخہ 2
#وإلاإذا SDL_WAYLAND_CHECK_نسخہ(1, 24, 0)
#تعریف_کرو SDL_WL_FIXES_نسخہ 1
#جے_انت

#جے_تعریف_شدہ SDL_USE_LIBDBUS
#ضمن "../../core/linux/SDL_dbus.h"

#تعریف_کرو DISPLAY_INFO_گرہ   "org.gnome.Mutter.DisplayConfig"
#تعریف_کرو DISPLAY_INFO_رستہ   "/org/gnome/Mutter/DisplayConfig"
#تعریف_کرو DISPLAY_INFO_طریقہ "GetCurrentState"
#جے_انت

/* GNOME doesn't expose displays in any particular order, but we can find the
 * primary display and its logical coordinates via a DBus method.
 */
ساكن bool Wayland_GetGNOMEPrimaryDisplayCoordinates(صحيح *x, صحيح *y)
{
#جے_تعریف_شدہ SDL_USE_LIBDBUS
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    إذا (dbus == عدم) {
        أرجع false;
    }
    DBus_سنیہا *جواب = عدم;
    DBus_سنیہا_Iter iter[3];
    DBus_سنیہا *پیغام = dbus->سنیہا_new_طریقہ_call(DISPLAY_INFO_گرہ,
                                                     DISPLAY_INFO_رستہ,
                                                     DISPLAY_INFO_گرہ,
                                                     DISPLAY_INFO_طریقہ);

    إذا (پیغام) {
        جواب = dbus->connection_send_with_جواب_and_بلاک(dbus->session_conn, پیغام, DBUS_TIMEOUT_USE_DEFAULT, عدم);
        dbus->سنیہا_unref(پیغام);
    }

    إذا (جواب) {
        // Serial (don't care)
        dbus->سنیہا_iter_init(جواب, &iter[0]);
        إذا (dbus->سنیہا_iter_get_arg_type(&iter[0]) != DBUS_TYPE_UINT32) {
            اذهب error;
        }

        // Physical monitor array (don't care)
        dbus->سنیہا_iter_اگلا(&iter[0]);
        إذا (dbus->سنیہا_iter_get_arg_type(&iter[0]) != DBUS_TYPE_ARRAY) {
            اذهب error;
        }

        // Logical monitor array of structs
        dbus->سنیہا_iter_اگلا(&iter[0]);
        إذا (dbus->سنیہا_iter_get_arg_type(&iter[0]) != DBUS_TYPE_ARRAY) {
            اذهب error;
        }

        // First logical monitor struct
        dbus->سنیہا_iter_recurse(&iter[0], &iter[1]);
        إذا (dbus->سنیہا_iter_get_arg_type(&iter[1]) != DBUS_TYPE_STRUCT) {
            اذهب error;
        }

        افعل {
            صحيح logical_x, logical_y;
            dbus_bool_t primary;

            // Logical X
            dbus->سنیہا_iter_recurse(&iter[1], &iter[2]);
            إذا (dbus->سنیہا_iter_get_arg_type(&iter[2]) != DBUS_TYPE_INT32) {
                اذهب error;
            }
            dbus->سنیہا_iter_get_basic(&iter[2], &logical_x);

            // Logical Y
            dbus->سنیہا_iter_اگلا(&iter[2]);
            إذا (dbus->سنیہا_iter_get_arg_type(&iter[2]) != DBUS_TYPE_INT32) {
                اذهب error;
            }
            dbus->سنیہا_iter_get_basic(&iter[2], &logical_y);

            // Scale (don't care)
            dbus->سنیہا_iter_اگلا(&iter[2]);
            إذا (dbus->سنیہا_iter_get_arg_type(&iter[2]) != DBUS_TYPE_DOUBLE) {
                اذهب error;
            }

            // Transform (don't care)
            dbus->سنیہا_iter_اگلا(&iter[2]);
            إذا (dbus->سنیہا_iter_get_arg_type(&iter[2]) != DBUS_TYPE_UINT32) {
                اذهب error;
            }

            // Primary display boolean
            dbus->سنیہا_iter_اگلا(&iter[2]);
            إذا (dbus->سنیہا_iter_get_arg_type(&iter[2]) != DBUS_TYPE_BOOLEAN) {
                اذهب error;
            }
            dbus->سنیہا_iter_get_basic(&iter[2], &primary);

            إذا (primary) {
                *x = logical_x;
                *y = logical_y;

                // We found the primary display: success.
                dbus->سنیہا_unref(جواب);
                أرجع true;
            }
        } طالما (dbus->سنیہا_iter_اگلا(&iter[1]));
    }

error:
    إذا (جواب) {
        dbus->سنیہا_unref(جواب);
    }
#جے_انت
    أرجع false;
}

// Sort the list of displays into a deterministic order
ساكن صحيح SDLCALL Wayland_DisplayPositionCompare(ثابت فراغ *a, ثابت فراغ *b)
{
    ثابت SDL_Display_انکڑے *da = *(SDL_Display_انکڑے **)a;
    ثابت SDL_Display_انکڑے *db = *(SDL_Display_انکڑے **)b;
    ثابت bool a_at_origin = da->logical.x == 0 && da->logical.y == 0;
    ثابت bool b_at_origin = db->logical.x == 0 && db->logical.y == 0;

    // Sort the display at 0,0 to be beginning of the list, as that will be the fallback primary.
    إذا (a_at_origin && !b_at_origin) {
        أرجع -1;
    }
    إذا (b_at_origin && !a_at_origin) {
        أرجع 1;
    }

    إذا (da->logical.x < db->logical.x) {
        أرجع -1;
    }
    إذا (da->logical.x > db->logical.x) {
        أرجع 1;
    }
    إذا (da->logical.y < db->logical.y) {
        أرجع -1;
    }
    إذا (da->logical.y > db->logical.y) {
        أرجع 1;
    }

    // If no position information is available, use the connector name.
    إذا (da->wl_output_name && db->wl_output_name) {
        أرجع SDL_strcmp(da->wl_output_name, db->wl_output_name);
    }

    أرجع 0;
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
ساكن صحيح Wayland_GetPrimaryDisplay(SDL_Video_انکڑے *vid)
{
    ساكن ثابت صحيح REFRESH_DELTA = 4000;

    // Query the DBus interface to see if the coordinates of the primary display are exposed.
    صحيح x, y;
    إذا (Wayland_GetGNOMEPrimaryDisplayCoordinates(&x, &y)) {
        لكل (صحيح i = 0; i < vid->output_گنتی; ++i) {
            إذا (vid->output_list[i]->logical.x == x && vid->output_list[i]->logical.y == y) {
                أرجع i;
            }
        }
    }

    // Otherwise, choose the 'best' display.
    صحيح بہترین_چوڑائی = 0;
    صحيح بہترین_اچائی = 0;
    مزدوج بہترین_scale = 0.0;
    عائم بہترین_headroom = 0.0f;
    صحيح بہترین_refresh = 0;
    bool بہترین_is_landscape = false;
    صحيح بہترین_اشاریہ = 0;

    لكل (صحيح i = 0; i < vid->output_گنتی; ++i) {
        ثابت SDL_Display_انکڑے *d = vid->output_list[i];
        ثابت bool is_landscape = d->orientation != SDL_ORIENTATION_PORTRAIT && d->orientation != SDL_ORIENTATION_PORTRAIT_FLIPPED;
        bool have_new_بہترین = false;

        إذا (!بہترین_is_landscape && is_landscape) { // Favor landscape over portrait displays.
            have_new_بہترین = true;
        } وإلا إذا (!بہترین_is_landscape || is_landscape) { // Ignore portrait displays if a landscape was already found.
            إذا (d->pixel.چوڑائی > بہترین_چوڑائی || d->pixel.اچائی > بہترین_اچائی) {
                have_new_بہترین = true;
            } وإلا إذا (d->pixel.چوڑائی == بہترین_چوڑائی && d->pixel.اچائی == بہترین_اچائی) {
                إذا (d->HDR.HDR_headroom > بہترین_headroom) { // Favor a higher HDR luminance range
                    have_new_بہترین = true;
                } وإلا إذا (d->HDR.HDR_headroom == بہترین_headroom) {
                    إذا (d->refresh - بہترین_refresh > REFRESH_DELTA) { // Favor a higher refresh rate, but ignore small differences (e.g. 59.97 vs 60.1)
                        have_new_بہترین = true;
                    } وإلا إذا (d->scale_ضارب_2 < بہترین_scale && SDL_abs(d->refresh - بہترین_refresh) <= REFRESH_DELTA) {
                        // Prefer a lower scale display if the difference in refresh rate is small.
                        have_new_بہترین = true;
                    }
                }
            }
        }

        إذا (have_new_بہترین) {
            بہترین_چوڑائی = d->pixel.چوڑائی;
            بہترین_اچائی = d->pixel.اچائی;
            بہترین_scale = d->scale_ضارب_2;
            بہترین_headroom = d->HDR.HDR_headroom;
            بہترین_refresh = d->refresh;
            بہترین_is_landscape = is_landscape;
            بہترین_اشاریہ = i;
        }
    }

    أرجع بہترین_اشاریہ;
}

ساكن فراغ Wayland_ترتیب_دیو_Outputs_By_ترجیح_Hint(SDL_Video_انکڑے *vid)
{
    ثابت حرف *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_ترجیح);

    إذا (name_hint) {
        حرف *saveptr;
        حرف *str = SDL_strdup(name_hint);
        SDL_Display_انکڑے **sorted_list = SDL_malloc(حجم(SDL_Display_انکڑے *) * vid->output_گنتی);

        إذا (str && sorted_list) {
            صحيح sorted_اشاریہ = 0;

            // Sort the requested displays to the front of the list.
            ثابت حرف *token = SDL_strtok_r(str, ",", &saveptr);
            طالما (token) {
                لكل (صحيح i = 0; i < vid->output_گنتی; ++i) {
                    SDL_Display_انکڑے *d = vid->output_list[i];
                    إذا (d && d->wl_output_name && SDL_strcmp(token, d->wl_output_name) == 0) {
                        sorted_list[sorted_اشاریہ++] = d;
                        vid->output_list[i] = عدم;
                        اكسر;
                    }
                }

                token = SDL_strtok_r(عدم, ",", &saveptr);
            }

            // Append the remaining outputs to the end of the list.
            لكل (صحيح i = 0; i < vid->output_گنتی; ++i) {
                إذا (vid->output_list[i]) {
                    sorted_list[sorted_اشاریہ++] = vid->output_list[i];
                }
            }

            // Copy the sorted list to the output list.
            SDL_memcpy(vid->output_list, sorted_list, حجم(SDL_Display_انکڑے *) * vid->output_گنتی);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

ساكن فراغ Wayland_DeriveOutputPixelCoordinates(SDL_Video_انکڑے *vid)
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
    لكل ( صحيح i = 0; i < vid->output_گنتی; ++i) {
        SDL_Display_انکڑے *d = vid->output_list[i];
        d->pixel.x = d->logical.x;
        d->pixel.y = d->logical.y;
    }

    لكل (صحيح i = 0; i < vid->output_گنتی; ++i) {
        SDL_Display_انکڑے *d1 = vid->output_list[i];
        إذا (d1->logical.چوڑائی != d1->pixel.چوڑائی || d1->logical.اچائی != d1->pixel.اچائی) {
            ثابت صحيح x_adj = d1->pixel.چوڑائی - d1->logical.چوڑائی;
            ثابت صحيح y_adj = d1->pixel.اچائی - d1->logical.اچائی;

            // Don't adjust for scale values less than 1.0.
            إذا (x_adj > 0 && y_adj > 0) {
                لكل (صحيح j = 0; j < vid->output_گنتی; ++j) {
                    SDL_Display_انکڑے *d2 = vid->output_list[j];
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

ساكن فراغ Wayland_ترتیب_دیو_Outputs(SDL_Video_انکڑے *vid)
{
    // Sort by position or connector name, so the order of outputs is deterministic.
    SDL_qsort(vid->output_list, vid->output_گنتی, حجم(SDL_Display_انکڑے *), Wayland_DisplayPositionCompare);

    // Derive the output pixel coordinates if scale to display is enabled.
    إذا (vid->scale_منزل_display_enabled) {
        Wayland_DeriveOutputPixelCoordinates(vid);
    }

    // Find a suitable primary display and move it to the front of the list.
    ثابت صحيح primary_اشاریہ = Wayland_GetPrimaryDisplay(vid);
    إذا (primary_اشاریہ) {
        SDL_Display_انکڑے *primary = vid->output_list[primary_اشاریہ];
        SDL_memmove(&vid->output_list[1], &vid->output_list[0], حجم(SDL_Display_انکڑے *) * primary_اشاریہ);
        vid->output_list[0] = primary;
    }

    // Apply the ordering hint, if specified.
    Wayland_ترتیب_دیو_Outputs_By_ترجیح_Hint(vid);
}

ساكن فراغ Wayland_Refresh_کھڑکی_Positions()
{
    SDL_VideoDevice *vid = SDL_GetVideoDevice();

    لكل (SDL_کھڑکی *w = vid->windows; w; w = w->اگلا) {
        Wayland_Update_کھڑکی_Position(w);
    }
}

ساكن فراغ handle_wl_output_پورا(فراغ *انکڑے, بنية wl_output *output);

// Initialization/Query functions
ساكن bool Wayland_VideoInit(SDL_VideoDevice *_this);
ساكن bool Wayland_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
ساكن فراغ Wayland_VideoQuit(SDL_VideoDevice *_this);

ساكن ثابت حرف *SDL_WAYLAND_surface_ٹیگ = "sdl-window";
ساكن ثابت حرف *SDL_WAYLAND_output_ٹیگ = "sdl-output";

فراغ SDL_WAYLAND_رجسٹر_surface(بنية wl_surface *surface)
{
    wl_proxy_سیٹ_ٹیگ((بنية wl_proxy *)surface, &SDL_WAYLAND_surface_ٹیگ);
}

فراغ SDL_WAYLAND_رجسٹر_output(بنية wl_output *output)
{
    wl_proxy_سیٹ_ٹیگ((بنية wl_proxy *)output, &SDL_WAYLAND_output_ٹیگ);
}

bool SDL_WAYLAND_own_surface(بنية wl_surface *surface)
{
    أرجع wl_proxy_get_ٹیگ((بنية wl_proxy *)surface) == &SDL_WAYLAND_surface_ٹیگ;
}

bool SDL_WAYLAND_own_output(بنية wl_output *output)
{
    أرجع wl_proxy_get_ٹیگ((بنية wl_proxy *)output) == &SDL_WAYLAND_output_ٹیگ;
}

/* External surfaces may have their own user data attached, the modification of which
 * can cause problems with external toolkits. Instead, external windows are kept in
 * their own list, and a search is conducted to find a matching surface.
 */
ساكن بنية wl_list external_کھڑکی_list;

فراغ Wayland_جوڑو_کھڑکی_انکڑے_منزل_External_List(SDL_کھڑکی_انکڑے *انکڑے)
{
    WAYLAND_wl_list_داخل_کرو(&external_کھڑکی_list, &انکڑے->external_کھڑکی_list_link);
}

فراغ Wayland_Remove_کھڑکی_انکڑے_From_External_List(SDL_کھڑکی_انکڑے *انکڑے)
{
    WAYLAND_wl_list_remove(&انکڑے->external_کھڑکی_list_link);
}

SDL_کھڑکی_انکڑے *Wayland_Get_کھڑکی_انکڑے_For_Owned_Surface(بنية wl_surface *surface)
{
    إذا (SDL_WAYLAND_own_surface(surface)) {
        أرجع (SDL_کھڑکی_انکڑے *)wl_surface_get_user_انکڑے(surface);
    } وإلا إذا (!WAYLAND_wl_list_خالی_تھاواں(&external_کھڑکی_list)) {
        SDL_کھڑکی_انکڑے *p;
        wl_list_for_each (p, &external_کھڑکی_list, external_کھڑکی_list_link) {
            إذا (p->surface == surface) {
                أرجع p;
            }
        }
    }

    أرجع عدم;
}

بنية wl_event_قطار *Wayland_Display_Create_قطار(بنية wl_display *display, ثابت حرف *name)
{
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
    إذا (WAYLAND_wl_display_create_قطار_with_name) {
        أرجع WAYLAND_wl_display_create_قطار_with_name(display, name);
    }
#وإلاإذا SDL_WAYLAND_CHECK_نسخہ(1, 23, 0)
    أرجع WAYLAND_wl_display_create_قطار_with_name(display, name);
#جے_انت
    أرجع WAYLAND_wl_display_create_قطار(display);
}

ساكن فراغ Wayland_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_Video_انکڑے *انکڑے = device->اندرونی;
    إذا (انکڑے->display && !انکڑے->display_externally_owned) {
        WAYLAND_wl_display_disconnect(انکڑے->display);
        SDL_ClearProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_اشارہ_گر);
    }
    SDL_free(انکڑے);
    SDL_free(device);
    SDL_WAYLAND_UnloadSymbols();
}

تعريفنوع بنية
{
    bool has_fifo_v1;
    بنية wl_fixes *wl_fixes;
} SDL_Wayland_Preferred_انکڑے;

ساكن فراغ wayland_preferred_check_handle_global(فراغ *انکڑے, بنية wl_registry *registry, uint32_t id,
                                                  ثابت حرف *interface, uint32_t نسخہ)
{
    SDL_Wayland_Preferred_انکڑے *d = انکڑے;

    إذا (SDL_strcmp(interface, "wp_fifo_manager_v1") == 0) {
        d->has_fifo_v1 = true;
    }
#جے_تعریف_شدہ SDL_WL_FIXES_نسخہ
    وإلا إذا (SDL_strcmp(interface, wl_fixes_interface.name) == 0) {
        d->wl_fixes = wl_registry_bind(registry, id, &wl_fixes_interface, SDL_min(SDL_WL_FIXES_نسخہ, نسخہ));
    }
#جے_انت
}

ساكن فراغ wayland_preferred_check_remove_global(فراغ *انکڑے, بنية wl_registry *registry, uint32_t id)
{
    SDL_Wayland_Preferred_انکڑے *d = (SDL_Wayland_Preferred_انکڑے *)انکڑے;

    إذا (d->wl_fixes && wl_fixes_get_نسخہ(d->wl_fixes) >= WL_FIXES_ACK_GLOBAL_REMOVE_SINCE_نسخہ) {
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
    SDL_Wayland_Preferred_انکڑے preferred_انکڑے = { 0 };

    إذا (!registry) {
        SDL_سیٹ_Error("Failed to get the Wayland registry");
        أرجع false;
    }

    wl_registry_جوڑو_listener(registry, &preferred_registry_listener, &preferred_انکڑے);

    WAYLAND_wl_display_roundtrip(display);

    إذا (preferred_انکڑے.wl_fixes) {
        wl_fixes_destroy_registry(preferred_انکڑے.wl_fixes, registry);
        wl_fixes_destroy(preferred_انکڑے.wl_fixes);
    }
    wl_registry_destroy(registry);

    إذا (!preferred_انکڑے.has_fifo_v1) {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "This compositor lacks support for the fifo-v1 protocol; falling back to XWayland for GPU performance reasons (set SDL_VIDEO_DRIVER=wayland to override)");
    }
    أرجع preferred_انکڑے.has_fifo_v1;
}

ساكن SDL_VideoDevice *Wayland_CreateDevice(bool require_preferred_protocols)
{
    SDL_VideoDevice *device;
    SDL_Video_انکڑے *انکڑے;
    بنية wl_display *display = SDL_Get_اشارہ_گر_Property(SDL_GetGlobalProperties(),
                                                 SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_اشارہ_گر, عدم);
    bool display_is_external = !!display;

    // Are we trying to connect to, or are currently in, a Wayland session?
    إذا (!SDL_getenv("WAYLAND_DISPLAY")) {
        ثابت حرف *session = SDL_getenv("XDG_SESSION_TYPE");
        إذا (session && SDL_strcasecmp(session, "wayland") != 0) {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Wayland initialization failed: no Wayland session available");
            أرجع عدم;
        }
    }

    إذا (!SDL_WAYLAND_لدو_Symbols()) {
        أرجع عدم;
    }

    إذا (!display) {
        display = WAYLAND_wl_display_connect(عدم);
        إذا (!display) {
            SDL_WAYLAND_UnloadSymbols();
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Failed to connect to the Wayland display server: %s", strerror(errno));
            أرجع عدم;
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
        أرجع عدم;
    }

    انکڑے = SDL_calloc(1, حجم(*انکڑے));
    إذا (!انکڑے) {
        إذا (!display_is_external) {
            WAYLAND_wl_display_disconnect(display);
        }
        SDL_WAYLAND_UnloadSymbols();
        أرجع عدم;
    }

    انکڑے->initializing = true;
    انکڑے->display = display;
    انکڑے->display_externally_owned = display_is_external;
    انکڑے->scale_منزل_display_enabled = SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_SCALE_منزل_DISPLAY, false);
    WAYLAND_wl_list_init(&انکڑے->seat_list);
    WAYLAND_wl_list_init(&external_کھڑکی_list);

    // Initialize all variables that we clean on shutdown
    device = SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (!device) {
        SDL_free(انکڑے);
        إذا (!display_is_external) {
            WAYLAND_wl_display_disconnect(display);
        }
        SDL_WAYLAND_UnloadSymbols();
        أرجع عدم;
    }

    إذا (!display_is_external) {
        SDL_سیٹ_اشارہ_گر_Property(SDL_GetGlobalProperties(),
                               SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_اشارہ_گر, display);
    }

    device->اندرونی = انکڑے;

    // Set the function pointers
    device->VideoInit = Wayland_VideoInit;
    device->VideoQuit = Wayland_VideoQuit;
    device->GetDisplayBounds = Wayland_GetDisplayBounds;
    device->SuspendScreenSaver = Wayland_SuspendScreenSaver;

    device->PumpEvents = Wayland_PumpEvents;
    device->WaitEventTimeout = Wayland_WaitEventTimeout;
    device->SendWakeupEvent = Wayland_SendWakeupEvent;

#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    device->GL_وٹاندرا_کھڑکی = Wayland_GLES_وٹاندرا_کھڑکی;
    device->GL_Get_وٹاندرا_Interval = Wayland_GLES_Get_وٹاندرا_Interval;
    device->GL_سیٹ_وٹاندرا_Interval = Wayland_GLES_سیٹ_وٹاندرا_Interval;
    device->GL_MakeCurrent = Wayland_GLES_MakeCurrent;
    device->GL_CreateContext = Wayland_GLES_CreateContext;
    device->GL_لدو_Library = Wayland_GLES_لدو_Library;
    device->GL_UnloadLibrary = Wayland_GLES_UnloadLibrary;
    device->GL_Get_Proc_پتہ = Wayland_GLES_Get_Proc_پتہ;
    device->GL_DestroyContext = Wayland_GLES_DestroyContext;
    device->GL_سیٹ_Default_Profile_Config = Wayland_GLES_سیٹ_Default_Profile_Config;
    device->GL_GetEGLSurface = Wayland_GLES_GetEGLSurface;
#جے_انت

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
    device->سیٹ_کھڑکی_ناپ = Wayland_سیٹ_کھڑکی_ناپ;
    device->سیٹ_کھڑکی_Aspect_تناسب = Wayland_سیٹ_کھڑکی_Aspect_تناسب;
    device->سیٹ_کھڑکی_Minimum_ناپ = Wayland_سیٹ_کھڑکی_Minimum_ناپ;
    device->سیٹ_کھڑکی_ودھ_توں_ودھ_ناپ = Wayland_سیٹ_کھڑکی_ودھ_توں_ودھ_ناپ;
    device->سیٹ_کھڑکی_ماپا = Wayland_سیٹ_کھڑکی_ماپا;
    device->سیٹ_کھڑکی_Modal = Wayland_سیٹ_کھڑکی_Modal;
    device->سیٹ_کھڑکی_Opacity = Wayland_سیٹ_کھڑکی_Opacity;
    device->سیٹ_کھڑکی_Title = Wayland_سیٹ_کھڑکی_Title;
    device->سیٹ_کھڑکی_Icon = Wayland_سیٹ_کھڑکی_Icon;
    device->Get_کھڑکی_ناپ_وچ_Pixels = Wayland_Get_کھڑکی_ناپ_وچ_Pixels;
    device->Get_کھڑکی_Content_Scale = Wayland_Get_کھڑکی_Content_Scale;
    device->Get_کھڑکی_ICCProfile = Wayland_Get_کھڑکی_ICCProfile;
    device->Get_Display_For_کھڑکی = Wayland_Get_Display_For_کھڑکی;
    device->Destroy_کھڑکی = Wayland_Destroy_کھڑکی;
    device->سیٹ_کھڑکی_کامیابی_Test = Wayland_سیٹ_کھڑکی_کامیابی_Test;
    device->Flash_کھڑکی = Wayland_Flash_کھڑکی;
#جے_تعریف_شدہ SDL_USE_LIBDBUS
    device->Apply_کھڑکی_ترقی = DBUS_Apply_کھڑکی_ترقی;
#جے_انت // SDL_USE_LIBDBUS
    device->HasScreenKeyboardSupport = Wayland_HasScreenKeyboardSupport;
    device->Show_کھڑکی_System_Menu = Wayland_Show_کھڑکی_System_Menu;
    device->Sync_کھڑکی = Wayland_Sync_کھڑکی;
    device->سیٹ_کھڑکی_Focusable = Wayland_سیٹ_کھڑکی_Focusable;
    device->Reconfigure_کھڑکی = Wayland_Reconfigure_کھڑکی;
    device->AcceptDragAndDrop = Wayland_AcceptDragAndDrop;

#جے_تعریف_شدہ SDL_USE_LIBDBUS
    إذا (SDL_SystemTheme_Init())
        device->system_theme = SDL_SystemTheme_Get();
#جے_انت

    device->Get_متن_Mime_Types = Wayland_Get_متن_Mime_Types;
    device->سیٹ_Clipboard_انکڑے = Wayland_سیٹ_Clipboard_انکڑے;
    device->Get_Clipboard_انکڑے = Wayland_Get_Clipboard_انکڑے;
    device->Has_Clipboard_انکڑے = Wayland_Has_Clipboard_انکڑے;
    device->شروع_متن_داخلہ = Wayland_شروع_متن_داخلہ;
    device->Stop_متن_داخلہ = Wayland_Stop_متن_داخلہ;
    device->Update_متن_داخلہ_Area = Wayland_Update_متن_داخلہ_Area;

#جے_تعریف_شدہ SDL_VIDEO_VULKAN
    device->Vulkan_لدو_Library = Wayland_Vulkan_لدو_Library;
    device->Vulkan_UnloadLibrary = Wayland_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = Wayland_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = Wayland_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = Wayland_Vulkan_DestroySurface;
    device->Vulkan_GetPresentationSupport = Wayland_Vulkan_GetPresentationSupport;
#جے_انت

    device->حرر = Wayland_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_منوال_SWITCHING_EMULATED |
                          VIDEO_DEVICE_CAPS_HAS_POPUP_کھڑکی_SUPPORT |
                          VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS |
                          VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES |
                          VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES;

    أرجع device;
}

ساكن SDL_VideoDevice *Wayland_Preferred_CreateDevice(فراغ)
{
    أرجع Wayland_CreateDevice(true);
}

ساكن SDL_VideoDevice *Wayland_Fallback_CreateDevice(فراغ)
{
    أرجع Wayland_CreateDevice(false);
}

VideoBootStrap Wayland_preferred_bootstrap = {
    WAYLANDVID_DRIVER_NAME, "SDL Wayland video driver",
    Wayland_Preferred_CreateDevice,
    Wayland_Show_سنیہا_Box,
    true
};

VideoBootStrap Wayland_bootstrap = {
    WAYLANDVID_DRIVER_NAME, "SDL Wayland video driver",
    Wayland_Fallback_CreateDevice,
    Wayland_Show_سنیہا_Box,
    false
};

ساكن فراغ handle_xdg_output_logical_position(فراغ *انکڑے, بنية zxdg_output_v1 *xdg_output, int32_t x, int32_t y)
{
    SDL_Display_انکڑے *اندرونی = (SDL_Display_انکڑے *)انکڑے;

    اندرونی->geometry_بدلیا |= اندرونی->logical.x != x || اندرونی->logical.y != y;
    اندرونی->logical.x = x;
    اندرونی->logical.y = y;
    اندرونی->has_logical_position = true;
}

ساكن فراغ handle_xdg_output_logical_ناپ(فراغ *انکڑے, بنية zxdg_output_v1 *xdg_output, int32_t چوڑائی, int32_t اچائی)
{
    SDL_Display_انکڑے *اندرونی = (SDL_Display_انکڑے *)انکڑے;

    اندرونی->geometry_بدلیا |= اندرونی->logical.چوڑائی != چوڑائی || اندرونی->logical.اچائی != اچائی;
    اندرونی->logical.چوڑائی = چوڑائی;
    اندرونی->logical.اچائی = اچائی;
    اندرونی->has_logical_ناپ = true;
}

ساكن فراغ handle_xdg_output_پورا(فراغ *انکڑے, بنية zxdg_output_v1 *xdg_output)
{
    SDL_Display_انکڑے *اندرونی = انکڑے;

    /*
     * xdg-output.done events are deprecated and only apply below version 3 of the protocol.
     * A wl-output.done event will be emitted in version 3 or higher.
     */
    إذا (zxdg_output_v1_get_نسخہ(اندرونی->xdg_output) < 3) {
        handle_wl_output_پورا(انکڑے, اندرونی->output);
    }
}

ساكن فراغ handle_xdg_output_name(فراغ *انکڑے, بنية zxdg_output_v1 *xdg_output, ثابت حرف *name)
{
    SDL_Display_انکڑے *اندرونی = (SDL_Display_انکڑے *)انکڑے;

    // Deprecated as of wl_output v4.
    إذا (wl_output_get_نسخہ(اندرونی->output) < WL_OUTPUT_NAME_SINCE_نسخہ &&
        اندرونی->display == 0) {
        SDL_free(اندرونی->wl_output_name);
        اندرونی->wl_output_name = SDL_strdup(name);
    }
}

ساكن فراغ handle_xdg_output_description(فراغ *انکڑے, بنية zxdg_output_v1 *xdg_output, ثابت حرف *description)
{
    SDL_Display_انکڑے *اندرونی = (SDL_Display_انکڑے *)انکڑے;

    // Deprecated as of wl_output v4.
    إذا (wl_output_get_نسخہ(اندرونی->output) < WL_OUTPUT_DESCRIPTION_SINCE_نسخہ &&
        اندرونی->display == 0) {
        // xdg-output descriptions, if available, supersede wl-output model names.
        SDL_free(اندرونی->placeholder.name);
        اندرونی->placeholder.name = SDL_strdup(description);
    }
}

ساكن ثابت بنية zxdg_output_v1_listener xdg_output_listener = {
    handle_xdg_output_logical_position,
    handle_xdg_output_logical_ناپ,
    handle_xdg_output_پورا,
    handle_xdg_output_name,
    handle_xdg_output_description,
};

ساكن فراغ جوڑو_Emulated_Modes(SDL_Display_انکڑے *dispdata, صحيح native_چوڑائی, صحيح native_اچائی)
{
    بنية Emulated_منوال
    {
        صحيح w;
        صحيح h;
    };

    // Resolution lists courtesy of XWayland
    ثابت بنية Emulated_منوال منوال_list[] = {
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
    SDL_Display_منوال منوال;
    SDL_VideoDisplay *dpy = dispdata->display ? SDL_GetVideoDisplay(dispdata->display) : &dispdata->placeholder;
    ثابت bool rot_90 = native_چوڑائی < native_اچائی; // Reverse width/height for portrait displays.

    لكل (i = 0; i < SDL_arraysize(منوال_list); ++i) {
        SDL_zero(منوال);
        منوال.format = dpy->desktop_منوال.format;
        منوال.refresh_شرح_numerator = dpy->desktop_منوال.refresh_شرح_numerator;
        منوال.refresh_شرح_denominator = dpy->desktop_منوال.refresh_شرح_denominator;

        إذا (rot_90) {
            منوال.w = منوال_list[i].h;
            منوال.h = منوال_list[i].w;
        } وإلا {
            منوال.w = منوال_list[i].w;
            منوال.h = منوال_list[i].h;
        }

        // Only add modes that are smaller than the native mode.
        إذا ((منوال.w < native_چوڑائی && منوال.h < native_اچائی) ||
            (منوال.w < native_چوڑائی && منوال.h == native_اچائی) ||
            (منوال.w == native_چوڑائی && منوال.h < native_اچائی)) {
            SDL_جوڑو_Fullscreen_Display_منوال(dpy, &منوال);
        }
    }
}

ساكن فراغ handle_wl_output_geometry(فراغ *انکڑے, بنية wl_output *output, صحيح x, صحيح y,
                                      صحيح physical_چوڑائی_2, صحيح physical_اچائی_2, صحيح subpixel,
                                      ثابت حرف *make, ثابت حرف *model, صحيح transform)
{
    SDL_Display_انکڑے *اندرونی = (SDL_Display_انکڑے *)انکڑے;

    // Apply the change from wl-output only if xdg-output is not supported
    إذا (!اندرونی->has_logical_position) {
        اندرونی->geometry_بدلیا |= اندرونی->logical.x != x || اندرونی->logical.y != y;
        اندرونی->logical.x = x;
        اندرونی->logical.y = y;
    }
    اندرونی->physical.چوڑائی_mm = physical_چوڑائی_2;
    اندرونی->physical.اچائی_mm = physical_اچائی_2;

    // The model is only used for the output name if wl_output or xdg-output haven't provided a description.
    إذا (اندرونی->display == 0 && !اندرونی->placeholder.name) {
        اندرونی->placeholder.name = SDL_strdup(model);
    }

    اندرونی->transform = transform;
#تعریف_کرو TF_CASE(وچ_2, باہرلا)                                 \
    حالة WL_OUTPUT_TRANSFORM_##in:                       \
        اندرونی->orientation = SDL_ORIENTATION_##out; \
        اكسر;
    إذا (اندرونی->physical.چوڑائی_mm >= اندرونی->physical.اچائی_mm) {
        بدل (transform) {
            TF_CASE(عام_3, LANDSCAPE)
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
            TF_CASE(عام_3, PORTRAIT)
            TF_CASE(90, LANDSCAPE)
            TF_CASE(180, PORTRAIT_FLIPPED)
            TF_CASE(270, LANDSCAPE_FLIPPED)
            TF_CASE(FLIPPED, PORTRAIT_FLIPPED)
            TF_CASE(FLIPPED_90, LANDSCAPE_FLIPPED)
            TF_CASE(FLIPPED_180, PORTRAIT)
            TF_CASE(FLIPPED_270, LANDSCAPE)
        }
    }
#تعریف_رد TF_CASE
}

ساكن فراغ handle_wl_output_منوال(فراغ *انکڑے, بنية wl_output *output, uint32_t flags,
                                  صحيح چوڑائی, صحيح اچائی, صحيح refresh)
{
    SDL_Display_انکڑے *اندرونی = (SDL_Display_انکڑے *)انکڑے;

    إذا (flags & WL_OUTPUT_منوال_CURRENT) {
        اندرونی->geometry_بدلیا |= اندرونی->pixel.چوڑائی != چوڑائی || اندرونی->pixel.اچائی != اچائی;
        اندرونی->pixel.چوڑائی = چوڑائی;
        اندرونی->pixel.اچائی = اچائی;

        /*
         * Don't rotate this yet, wl-output coordinates are transformed in
         * handle_done and xdg-output coordinates are pre-transformed.
         */
        إذا (!اندرونی->has_logical_ناپ) {
            اندرونی->geometry_بدلیا |= اندرونی->logical.چوڑائی != چوڑائی || اندرونی->logical.اچائی != اچائی;
            اندرونی->logical.چوڑائی = چوڑائی;
            اندرونی->logical.اچائی = اچائی;
        }

        اندرونی->refresh = refresh;
    }
}

ساكن فراغ handle_wl_output_پورا(فراغ *انکڑے, بنية wl_output *output)
{
    ثابت bool منوال_emulation_enabled = SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_منوال_EMULATION, true);
    SDL_Display_انکڑے *اندرونی = (SDL_Display_انکڑے *)انکڑے;
    SDL_Video_انکڑے *video = اندرونی->videodata;
    SDL_Display_منوال native_منوال, desktop_منوال;

    /*
     * When using xdg-output, two wl-output.done events will be emitted:
     * one at the completion of wl-display and one at the completion of xdg-output.
     *
     * All required events must be received before proceeding.
     */
    ثابت صحيح event_await_گنتی = 1 + (اندرونی->xdg_output != عدم);

    اندرونی->wl_output_پورا_گنتی = SDL_min(اندرونی->wl_output_پورا_گنتی + 1, event_await_گنتی + 1);

    إذا (اندرونی->wl_output_پورا_گنتی < event_await_گنتی) {
        أرجع;
    }

    // If the display was already created, reset and rebuild the mode list.
    SDL_VideoDisplay *dpy = SDL_GetVideoDisplay(اندرونی->display);
    إذا (dpy) {
        SDL_ResetFullscreenDisplayModes(dpy);
    }

    // The native display resolution
    SDL_zero(native_منوال);
    native_منوال.format = SDL_PIXELFORMAT_XRGB8888;

    // Transform the pixel values, if necessary.
    إذا (اندرونی->transform & WL_OUTPUT_TRANSFORM_90) {
        native_منوال.w = اندرونی->pixel.اچائی;
        native_منوال.h = اندرونی->pixel.چوڑائی;
    } وإلا {
        native_منوال.w = اندرونی->pixel.چوڑائی;
        native_منوال.h = اندرونی->pixel.اچائی;
    }
    native_منوال.refresh_شرح_numerator = اندرونی->refresh;
    native_منوال.refresh_شرح_denominator = 1000;

    إذا (اندرونی->has_logical_ناپ) { // If xdg-output is present...
        إذا (native_منوال.w != اندرونی->logical.چوڑائی || native_منوال.h != اندرونی->logical.اچائی) {
            // ...and the compositor scales the logical viewport...
            إذا (video->viewporter) {
                // ...and viewports are supported, calculate the true scale of the output.
                اندرونی->scale_ضارب_2 = (مزدوج)native_منوال.w / (مزدوج)اندرونی->logical.چوڑائی;
            } وإلا {
                // ...otherwise, the 'native' pixel values are a multiple of the logical screen size.
                اندرونی->scale_ضارب_2 = اندرونی->integer_scale_ضارب;
                اندرونی->pixel.چوڑائی = اندرونی->logical.چوڑائی * اندرونی->integer_scale_ضارب;
                اندرونی->pixel.اچائی = اندرونی->logical.اچائی * اندرونی->integer_scale_ضارب;
            }
        } وإلا {
            /* ...and the output viewport is not scaled in the global compositing
             * space, the output dimensions need to be divided by the scale factor.
             *
             * NOTE: This path is needed for old versions of GNOME that predate fractional scaling.
             */
            اندرونی->scale_ضارب_2 = اندرونی->integer_scale_ضارب;
            اندرونی->logical.چوڑائی /= اندرونی->integer_scale_ضارب;
            اندرونی->logical.اچائی /= اندرونی->integer_scale_ضارب;
        }
    } وإلا {
        /* Calculate the points from the pixel values, if xdg-output isn't present.
         * Use the native mode pixel values since they are pre-transformed.
         */
        اندرونی->scale_ضارب_2 = اندرونی->integer_scale_ضارب;
        اندرونی->logical.چوڑائی = native_منوال.w / اندرونی->integer_scale_ضارب;
        اندرونی->logical.اچائی = native_منوال.h / اندرونی->integer_scale_ضارب;
    }

    // The scaled desktop mode
    SDL_zero(desktop_منوال);
    desktop_منوال.format = SDL_PIXELFORMAT_XRGB8888;

    إذا (!video->scale_منزل_display_enabled) {
        desktop_منوال.w = اندرونی->logical.چوڑائی;
        desktop_منوال.h = اندرونی->logical.اچائی;
        desktop_منوال.pixel_density = (عائم)اندرونی->scale_ضارب_2;
    } وإلا {
        desktop_منوال.w = native_منوال.w;
        desktop_منوال.h = native_منوال.h;
        desktop_منوال.pixel_density = 1.0f;
    }

    desktop_منوال.refresh_شرح_numerator = اندرونی->refresh;
    desktop_منوال.refresh_شرح_denominator = 1000;

    إذا (اندرونی->display > 0) {
        dpy = SDL_GetVideoDisplay(اندرونی->display);
    } وإلا {
        dpy = &اندرونی->placeholder;
    }

    إذا (video->scale_منزل_display_enabled) {
        SDL_سیٹ_Display_Content_Scale(dpy, (عائم)اندرونی->scale_ضارب_2);
    }

    // Set the desktop display mode.
    SDL_سیٹ_Desktop_Display_منوال(dpy, &desktop_منوال);

    // Expose the unscaled, native resolution if the scale is 1.0 or viewports are available...
    إذا (اندرونی->scale_ضارب_2 == 1.0 || video->viewporter) {
        SDL_جوڑو_Fullscreen_Display_منوال(dpy, &native_منوال);
        إذا (native_منوال.w != desktop_منوال.w ||
            native_منوال.h != desktop_منوال.h) {
            SDL_جوڑو_Fullscreen_Display_منوال(dpy, &desktop_منوال);
        }
    } وإلا {
        // ...otherwise expose the integer scaled variants of the desktop resolution down to 1.
        desktop_منوال.pixel_density = 1.0f;

        لكل (صحيح i = (صحيح)اندرونی->scale_ضارب_2; i > 0; --i) {
            desktop_منوال.w = اندرونی->logical.چوڑائی * i;
            desktop_منوال.h = اندرونی->logical.اچائی * i;
            SDL_جوڑو_Fullscreen_Display_منوال(dpy, &desktop_منوال);
        }
    }

    // Add emulated modes if wp_viewporter is supported and mode emulation is enabled.
    إذا (video->viewporter && منوال_emulation_enabled) {
        // The transformed display pixel width/height must be used here.
        جوڑو_Emulated_Modes(اندرونی, native_منوال.w, native_منوال.h);
    }

    إذا (اندرونی->display == 0) {
        // First time getting display info, initialize the VideoDisplay
        إذا (اندرونی->physical.چوڑائی_mm >= اندرونی->physical.اچائی_mm) {
            اندرونی->placeholder.natural_orientation = SDL_ORIENTATION_LANDSCAPE;
        } وإلا {
            اندرونی->placeholder.natural_orientation = SDL_ORIENTATION_PORTRAIT;
        }
        اندرونی->placeholder.current_orientation = اندرونی->orientation;
        اندرونی->placeholder.اندرونی = اندرونی;

        اندرونی->placeholder.props = SDL_CreateProperties();
        SDL_سیٹ_اشارہ_گر_Property(اندرونی->placeholder.props, SDL_PROP_DISPLAY_WAYLAND_WL_OUTPUT_اشارہ_گر, اندرونی->output);

        // During initialization, the displays will be added after enumeration is complete.
        إذا (!video->initializing) {
            إذا (video->wp_color_manager_v1) {
                Wayland_GetColorInfoForOutput(اندرونی, false);
            }
            إذا (video->scale_منزل_display_enabled) {
                Wayland_DeriveOutputPixelCoordinates(video);
            }

            اندرونی->display = SDL_جوڑو_Video_Display(&اندرونی->placeholder, true);
            Wayland_Refresh_کھڑکی_Positions();

            SDL_free(اندرونی->placeholder.name);
            SDL_zero(اندرونی->placeholder);
        }
    } وإلا {
        SDL_SendDisplayEvent(dpy, SDL_EVENT_DISPLAY_ORIENTATION, اندرونی->orientation, 0);

        إذا (اندرونی->geometry_بدلیا) {
            إذا (video->scale_منزل_display_enabled) {
                Wayland_DeriveOutputPixelCoordinates(video);
            }

            SDL_SendDisplayEvent(dpy, SDL_EVENT_DISPLAY_MOVED, 0, 0);
            Wayland_Refresh_کھڑکی_Positions();
        }
    }

    اندرونی->geometry_بدلیا = false;
}

ساكن فراغ handle_wl_output_scale(فراغ *انکڑے, بنية wl_output *output, int32_t ضارب)
{
    SDL_Display_انکڑے *اندرونی = (SDL_Display_انکڑے *)انکڑے;
    اندرونی->integer_scale_ضارب = ضارب;
}

ساكن فراغ handle_wl_output_name(فراغ *انکڑے, بنية wl_output *wl_output, ثابت حرف *name)
{
    SDL_Display_انکڑے *اندرونی = (SDL_Display_انکڑے *)انکڑے;

    SDL_free(اندرونی->wl_output_name);
    اندرونی->wl_output_name = SDL_strdup(name);
}

ساكن فراغ handle_wl_output_description(فراغ *انکڑے, بنية wl_output *wl_output, ثابت حرف *description)
{
    SDL_Display_انکڑے *اندرونی = (SDL_Display_انکڑے *)انکڑے;

    إذا (اندرونی->display == 0) {
        // The description, if available, supersedes the model name.
        SDL_free(اندرونی->placeholder.name);
        اندرونی->placeholder.name = SDL_strdup(description);
    }
}

ساكن ثابت بنية wl_output_listener output_listener = {
    handle_wl_output_geometry,   // Version 1
    handle_wl_output_منوال,       // Version 1
    handle_wl_output_پورا,       // Version 2
    handle_wl_output_scale,      // Version 2
    handle_wl_output_name,       // Version 4
    handle_wl_output_description // Version 4
};

ساكن فراغ handle_output_image_description_بدلیا(فراغ *انکڑے,
                                                    بنية wp_color_management_output_v1 *wp_color_management_output_v1)
{
    SDL_Display_انکڑے *display = (SDL_Display_انکڑے *)انکڑے;
    Wayland_GetColorInfoForOutput(display, false);
}

ساكن ثابت بنية wp_color_management_output_v1_listener wp_color_management_output_listener = {
    handle_output_image_description_بدلیا
};

ساكن bool Wayland_جوڑو_display(SDL_Video_انکڑے *d, uint32_t id, uint32_t نسخہ)
{
    بنية wl_output *output;
    SDL_Display_انکڑے *انکڑے;

    output = wl_registry_bind(d->registry, id, &wl_output_interface, نسخہ);
    إذا (!output) {
        أرجع SDL_سیٹ_Error("Failed to retrieve output.");
    }
    انکڑے = (SDL_Display_انکڑے *)SDL_calloc(1, حجم(*انکڑے));
    انکڑے->videodata = d;
    انکڑے->output = output;
    انکڑے->registry_id = id;
    انکڑے->scale_ضارب_2 = 1.0f;
    انکڑے->integer_scale_ضارب = 1;

    wl_output_جوڑو_listener(output, &output_listener, انکڑے);
    SDL_WAYLAND_رجسٹر_output(output);

    // Keep a list of outputs for sorting and deferred protocol initialization.
    إذا (d->output_گنتی == d->output_max) {
        d->output_max += 4;
        d->output_list = SDL_realloc(d->output_list, حجم(SDL_Display_انکڑے *) * d->output_max);
    }
    d->output_list[d->output_گنتی++] = انکڑے;

    إذا (انکڑے->videodata->xdg_output_manager) {
        انکڑے->xdg_output = zxdg_output_manager_v1_get_xdg_output(انکڑے->videodata->xdg_output_manager, output);
        zxdg_output_v1_جوڑو_listener(انکڑے->xdg_output, &xdg_output_listener, انکڑے);
    }
    إذا (انکڑے->videodata->wp_color_manager_v1) {
        انکڑے->wp_color_management_output = wp_color_manager_v1_get_output(انکڑے->videodata->wp_color_manager_v1, output);
        wp_color_management_output_v1_جوڑو_listener(انکڑے->wp_color_management_output, &wp_color_management_output_listener, انکڑے);

        // If not initializing, this will be queried synchronously in wl_output.done.
        إذا (d->initializing) {
            Wayland_GetColorInfoForOutput(انکڑے, true);
        }
    }
    أرجع true;
}

ساكن فراغ Wayland_free_display(SDL_VideoDisplay *display, bool send_event)
{
    إذا (display) {
        SDL_Display_انکڑے *display_انکڑے = display->اندرونی;

        /* A preceding surface leave event is not guaranteed when an output is removed,
         * so ensure that no window continues to hold a reference to a removed output.
         */
        لكل (SDL_کھڑکی *کھڑکی = SDL_GetVideoDevice()->windows; کھڑکی; کھڑکی = کھڑکی->اگلا) {
            Wayland_Remove_Output_From_کھڑکی(کھڑکی->اندرونی, display_انکڑے);
        }

        SDL_free(display_انکڑے->wl_output_name);

        إذا (display_انکڑے->wp_color_management_output) {
            Wayland_FreeColorInfoState(display_انکڑے->color_info_state);
            wp_color_management_output_v1_destroy(display_انکڑے->wp_color_management_output);
        }

        إذا (display_انکڑے->xdg_output) {
            zxdg_output_v1_destroy(display_انکڑے->xdg_output);
        }

        إذا (wl_output_get_نسخہ(display_انکڑے->output) >= WL_OUTPUT_RELEASE_SINCE_نسخہ) {
            wl_output_release(display_انکڑے->output);
        } وإلا {
            wl_output_destroy(display_انکڑے->output);
        }

        SDL_DelVideoDisplay(display->id, send_event);
    }
}

ساكن فراغ Wayland_FinalizeDisplays(SDL_Video_انکڑے *vid)
{
    Wayland_ترتیب_دیو_Outputs(vid);

    لكل(صحيح i = 0; i < vid->output_گنتی; ++i) {
        SDL_Display_انکڑے *d = vid->output_list[i];
        d->display = SDL_جوڑو_Video_Display(&d->placeholder, false);
        SDL_free(d->placeholder.name);
        SDL_zero(d->placeholder);
    }
}

ساكن فراغ Wayland_init_xdg_output(SDL_Video_انکڑے *d)
{
    لكل (صحيح i = 0; i < d->output_گنتی; ++i) {
        SDL_Display_انکڑے *disp = d->output_list[i];
        disp->xdg_output = zxdg_output_manager_v1_get_xdg_output(disp->videodata->xdg_output_manager, disp->output);
        zxdg_output_v1_جوڑو_listener(disp->xdg_output, &xdg_output_listener, disp);
    }
}

ساكن فراغ Wayland_InitColorManager(SDL_Video_انکڑے *d)
{
    لكل (صحيح i = 0; i < d->output_گنتی; ++i) {
        SDL_Display_انکڑے *disp = d->output_list[i];
        disp->wp_color_management_output = wp_color_manager_v1_get_output(disp->videodata->wp_color_manager_v1, disp->output);
        wp_color_management_output_v1_جوڑو_listener(disp->wp_color_management_output, &wp_color_management_output_listener, disp);
        Wayland_GetColorInfoForOutput(disp, true);
    }
}

ساكن فراغ handle_xdg_session_created(فراغ *انکڑے, بنية xdg_session_v1 *xdg_session_v1, ثابت حرف *id)
{
    SDL_سیٹ_String_Property(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, id);
}

ساكن فراغ handle_xdg_session_restored(فراغ *انکڑے, بنية xdg_session_v1 *xdg_session_v1)
{
    // NOP
}

ساكن فراغ handle_xdg_session_replaced(فراغ *انکڑے, بنية xdg_session_v1 *xdg_session_v1)
{
    SDL_VideoDevice *viddev = SDL_GetVideoDevice();
    SDL_Video_انکڑے *viddata = انکڑے;

    // Clean up all session objects, as they have become inert, and should be destroyed.
    SDL_سیٹ_String_Property(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, عدم);

    لكل (SDL_کھڑکی *w = viddev->windows; w; w = w->اگلا) {
        SDL_کھڑکی_انکڑے *d = w->اندرونی;

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

فراغ Wayland_CreateSession(SDL_Video_انکڑے *viddata)
{
    إذا (!viddata->xdg_session_manager) {
        // Set the ID string to null if session management is not available.
        SDL_سیٹ_String_Property(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, عدم);
        أرجع;
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
            xdg_session_v1_جوڑو_listener(viddata->xdg_session, &xdg_session_listener, viddata);
        }
    }
}

ساكن فراغ Wayland_SessionDestroy(SDL_Video_انکڑے *viddata)
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

ساكن فراغ handle_xdg_wm_ادھار_ping(فراغ *انکڑے, بنية xdg_wm_ادھار *xdg, uint32_t serial)
{
    xdg_wm_ادھار_pong(xdg, serial);
}

ساكن ثابت بنية xdg_wm_ادھار_listener xdg_wm_ادھار_listener_2 = {
    handle_xdg_wm_ادھار_ping
};

#جے_تعریف_شدہ HAVE_LIBDECOR_H
ساكن فراغ libdecor_error(بنية libdecor *context,
                           تعداد libdecor_error error,
                           ثابت حرف *سنیہا)
{
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "libdecor error (%d): %s", error, سنیہا);
}

ساكن بنية libdecor_interface libdecor_interface = {
    libdecor_error
};
#جے_انت

ساكن فراغ handle_registry_global(فراغ *انکڑے, بنية wl_registry *registry, uint32_t id,
                                   ثابت حرف *interface, uint32_t نسخہ)
{
    SDL_Video_انکڑے *d = انکڑے;

    إذا (SDL_strcmp(interface, wl_compositor_interface.name) == 0) {
        d->compositor = wl_registry_bind(d->registry, id, &wl_compositor_interface, SDL_min(SDL_WL_COMPOSITOR_نسخہ, نسخہ));
    } وإلا إذا (SDL_strcmp(interface, wl_subcompositor_interface.name) == 0) {
        d->subcompositor = wl_registry_bind(d->registry, id, &wl_subcompositor_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, wl_output_interface.name) == 0) {
        Wayland_جوڑو_display(d, id, SDL_min(نسخہ, SDL_WL_OUTPUT_نسخہ));
    } وإلا إذا (SDL_strcmp(interface, wl_seat_interface.name) == 0) {
        بنية wl_seat *seat = wl_registry_bind(d->registry, id, &wl_seat_interface, SDL_min(SDL_WL_SEAT_نسخہ, نسخہ));
        Wayland_DisplayCreateSeat(d, seat, id);
    } وإلا إذا (SDL_strcmp(interface, xdg_wm_ادھار_interface.name) == 0) {
        d->shell.xdg = wl_registry_bind(d->registry, id, &xdg_wm_ادھار_interface, SDL_min(نسخہ, 7));
        xdg_wm_ادھار_جوڑو_listener(d->shell.xdg, &xdg_wm_ادھار_listener_2, عدم);
    } وإلا إذا (SDL_strcmp(interface, wl_shm_interface.name) == 0) {
        d->shm = wl_registry_bind(registry, id, &wl_shm_interface, SDL_min(SDL_WL_SHM_نسخہ, نسخہ));
    } وإلا إذا (SDL_strcmp(interface, zwp_relative_اشارہ_گر_manager_v1_interface.name) == 0) {
        d->relative_اشارہ_گر_manager = wl_registry_bind(d->registry, id, &zwp_relative_اشارہ_گر_manager_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, zwp_اشارہ_گر_constraints_v1_interface.name) == 0) {
        d->اشارہ_گر_constraints = wl_registry_bind(d->registry, id, &zwp_اشارہ_گر_constraints_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, zwp_keyboard_shortcuts_inhibit_manager_v1_interface.name) == 0) {
        d->کلید_inhibitor_manager = wl_registry_bind(d->registry, id, &zwp_keyboard_shortcuts_inhibit_manager_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, zwp_idle_inhibit_manager_v1_interface.name) == 0) {
        d->idle_inhibit_manager = wl_registry_bind(d->registry, id, &zwp_idle_inhibit_manager_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, xdg_activation_v1_interface.name) == 0) {
        d->activation_manager = wl_registry_bind(d->registry, id, &xdg_activation_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, zwp_متن_داخلہ_manager_v3_interface.name) == 0) {
        d->متن_داخلہ_manager = wl_registry_bind(d->registry, id, &zwp_متن_داخلہ_manager_v3_interface, 1);
        Wayland_Display_Init_متن_داخلہ_Manager(d, id);
    } وإلا إذا (SDL_strcmp(interface, wl_انکڑے_device_manager_interface.name) == 0) {
        d->انکڑے_device_manager = wl_registry_bind(d->registry, id, &wl_انکڑے_device_manager_interface, SDL_min(3, نسخہ));
        Wayland_Display_Init_انکڑے_Device_Manager(d);
    } وإلا إذا (SDL_strcmp(interface, zwp_primary_selection_device_manager_v1_interface.name) == 0) {
        d->primary_selection_device_manager = wl_registry_bind(d->registry, id, &zwp_primary_selection_device_manager_v1_interface, 1);
        Wayland_DisplayInitPrimarySelectionDeviceManager(d);
    } وإلا إذا (SDL_strcmp(interface, zxdg_decoration_manager_v1_interface.name) == 0) {
        d->decoration_manager = wl_registry_bind(d->registry, id, &zxdg_decoration_manager_v1_interface, SDL_min(2, نسخہ));
    } وإلا إذا (SDL_strcmp(interface, zwp_tablet_manager_v2_interface.name) == 0) {
        d->tablet_manager = wl_registry_bind(d->registry, id, &zwp_tablet_manager_v2_interface, 1);
        Wayland_DisplayInitTabletManager(d);
    } وإلا إذا (SDL_strcmp(interface, zxdg_output_manager_v1_interface.name) == 0) {
        نسخہ = SDL_min(نسخہ, 3); // Versions 1 through 3 are supported.
        d->xdg_output_manager = wl_registry_bind(d->registry, id, &zxdg_output_manager_v1_interface, نسخہ);
        Wayland_init_xdg_output(d);
    } وإلا إذا (SDL_strcmp(interface, wp_viewporter_interface.name) == 0) {
        d->viewporter = wl_registry_bind(d->registry, id, &wp_viewporter_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, wp_fractional_scale_manager_v1_interface.name) == 0) {
        d->fractional_scale_manager = wl_registry_bind(d->registry, id, &wp_fractional_scale_manager_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, zwp_داخلہ_timestamps_manager_v1_interface.name) == 0) {
        d->داخلہ_timestamps_manager = wl_registry_bind(d->registry, id, &zwp_داخلہ_timestamps_manager_v1_interface, 1);
        Wayland_Display_Init_داخلہ_Timestamp_Manager(d);
    } وإلا إذا (SDL_strcmp(interface, wp_cursor_shape_manager_v1_interface.name) == 0) {
        d->cursor_shape_manager = wl_registry_bind(d->registry, id, &wp_cursor_shape_manager_v1_interface, SDL_min(نسخہ, 2));
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
        d->wp_color_manager_v1 = wl_registry_bind(d->registry, id, &wp_color_manager_v1_interface, SDL_min(نسخہ, 2));
        Wayland_InitColorManager(d);
    } وإلا إذا (SDL_strcmp(interface, wp_اشارہ_گر_warp_v1_interface.name) == 0) {
        d->wp_اشارہ_گر_warp_v1 = wl_registry_bind(d->registry, id, &wp_اشارہ_گر_warp_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, zwp_اشارہ_گر_gestures_v1_interface.name) == 0) {
        d->zwp_اشارہ_گر_gestures = wl_registry_bind(d->registry, id, &zwp_اشارہ_گر_gestures_v1_interface, SDL_min(نسخہ, 3));
        Wayland_Display_Init_اشارہ_گر_Gesture_Manager(d);
    } وإلا إذا (SDL_strcmp(interface, wp_single_pixel_بفر_manager_v1_interface.name) == 0) {
        d->single_pixel_بفر_manager = wl_registry_bind(d->registry, id, &wp_single_pixel_بفر_manager_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, xdg_session_manager_v1_interface.name) == 0) {
        d->xdg_session_manager = wl_registry_bind(d->registry, id, &xdg_session_manager_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, xdg_toplevel_ٹیگ_manager_v1_interface.name) == 0) {
        d->xdg_toplevel_ٹیگ_manager = wl_registry_bind(d->registry, id, &xdg_toplevel_ٹیگ_manager_v1_interface, 1);
    }
#جے_تعریف_شدہ SDL_WL_FIXES_نسخہ
    وإلا إذا (SDL_strcmp(interface, wl_fixes_interface.name) == 0) {
        d->wl_fixes = wl_registry_bind(d->registry, id, &wl_fixes_interface, SDL_min(SDL_WL_FIXES_نسخہ, نسخہ));
    }
#جے_انت
}

ساكن فراغ handle_registry_remove_global(فراغ *انکڑے, بنية wl_registry *registry, uint32_t id)
{
    SDL_Video_انکڑے *d = انکڑے;

    // We don't get an interface, just an ID, so check outputs and seats.
    لكل (صحيح i = 0; i < d->output_گنتی; ++i) {
        SDL_Display_انکڑے *disp = d->output_list[i];
        إذا (disp->registry_id == id) {
            Wayland_free_display(SDL_GetVideoDisplay(disp->display), true);

            إذا (i < d->output_گنتی) {
                SDL_memmove(&d->output_list[i], &d->output_list[i + 1], حجم(SDL_Display_انکڑے *) * (d->output_گنتی - i - 1));
            }

            d->output_گنتی--;
            اذهب ack_remove;
        }
    }

    SDL_WaylandSeat *seat, *عارضی;
    wl_list_for_each_محفوظ (seat, عارضی, &d->seat_list, link) {
        إذا (seat->registry_id == id) {
            Wayland_SeatDestroy(seat, false);
            اذهب ack_remove;
        }
    }

ack_remove:
    إذا (d->wl_fixes && wl_fixes_get_نسخہ(d->wl_fixes) >= WL_FIXES_ACK_GLOBAL_REMOVE_SINCE_نسخہ) {
        wl_fixes_ack_global_remove(d->wl_fixes, registry, id);
    }
}

ساكن ثابت بنية wl_registry_listener registry_listener = {
    handle_registry_global,
    handle_registry_remove_global
};

#جے_تعریف_شدہ HAVE_LIBDECOR_H
ساكن bool should_use_libdecor(SDL_Video_انکڑے *انکڑے, bool ignore_xdg)
{
    إذا (!SDL_WAYLAND_HAVE_WAYLAND_LIBDECOR) {
        أرجع false;
    }

    إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_PREFER_LIBDECOR, false)) {
        أرجع true;
    }

    إذا (ignore_xdg) {
        أرجع true;
    }

    إذا (انکڑے->decoration_manager) {
        أرجع false;
    }

    أرجع true;
}

ساكن فراغ LibdecorNew(SDL_Video_انکڑے *انکڑے)
{
    انکڑے->shell.libdecor = libdecor_new(انکڑے->display, &libdecor_interface);
}

// Called in another thread, but the UI thread is blocked in SDL_WaitThread
// during that time, so it should be OK to dereference data without locks
ساكن صحيح SDLCALL Libdecor_New_وچ_Thread(فراغ *انکڑے)
{
    LibdecorNew((SDL_Video_انکڑے *)انکڑے);
    أرجع 0;
}
#جے_انت

#جے_تعریف_شدہ HAVE_GETRESUID
#تعریف_کرو SDL_getresuid getresuid
#وإلا
// Non-POSIX, but Linux and some BSDs have it.
// To reduce the number of code paths, if getresuid() isn't available at
// compile-time, we behave as though it existed but failed at runtime.
ساكن مضمن صحيح SDL_getresuid(uid_t *ruid, uid_t *euid, uid_t *suid) {
    errno = ENOSYS;
    أرجع -1;
}
#جے_انت

#جے_تعریف_شدہ HAVE_GETRESGID
#تعریف_کرو SDL_getresgid getresgid
#وإلا
// Same as getresuid() but for the primary group
ساكن مضمن صحيح SDL_getresgid(gid_t *rgid, gid_t *egid, gid_t *sgid) {
    errno = ENOSYS;
    أرجع -1;
}
#جے_انت

bool CanUseGtk(فراغ)
{
    // "Real", "effective" and "saved" IDs: see e.g. Linux credentials(7)
    uid_t ruid = -1, euid = -1, suid = -1;
    gid_t rgid = -1, egid = -1, sgid = -1;

    إذا (!SDL_GetHintBoolean("SDL_ENABLE_GTK", true)) {
        SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "Not using GTK due to hint");
        أرجع false;
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
        أرجع false;
    }

    // Real ID != saved ID means we are setuid or setgid, we previously
    // dropped privileges, but we can regain them; this protects against
    // accidents but does not protect against arbitrary code execution.
    // Again, GTK will refuse to initialize if this is the case.
    إذا (ruid != suid || rgid != sgid) {
        SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "Not using GTK due to saved uid/gid");
        أرجع false;
    }

    أرجع true;
}

bool Wayland_لدو_Libdecor(SDL_Video_انکڑے *انکڑے, bool ignore_xdg)
{
#جے_تعریف_شدہ HAVE_LIBDECOR_H
    إذا (انکڑے->shell.libdecor != عدم) {
        أرجع true; // Already loaded!
    }
    إذا (should_use_libdecor(انکڑے, ignore_xdg)) {
        إذا (CanUseGtk()) {
            LibdecorNew(انکڑے);
        } وإلا {
            // Intentionally initialize libdecor in a non-main thread
            // so that it will not use its GTK plugin, but instead will
            // fall back to the Cairo or dummy plugin
            SDL_Thread *thread = SDL_CreateThread(Libdecor_New_وچ_Thread, "SDL_LibdecorNew", (فراغ *)انکڑے);
            // Note that the other thread now "owns" data until we have
            // waited for it, so don't touch data here
            SDL_WaitThread(thread, عدم);
        }

        أرجع انکڑے->shell.libdecor != عدم;
    }
#جے_انت
    أرجع false;
}

bool Wayland_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;

    انکڑے->event_thread_context = Wayland_CreateEventThread(انکڑے, "SDL Event Thread Queue");
    إذا (!انکڑے->event_thread_context) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Failed to create event thread context");
    }

    انکڑے->کم_thread_context = Wayland_Create_کم_Thread();
    إذا (!انکڑے->کم_thread_context) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Failed to create job thread context");
    }

    انکڑے->xkb_context = WAYLAND_xkb_context_new(0);
    إذا (!انکڑے->xkb_context) {
        أرجع SDL_سیٹ_Error("Failed to create XKB context");
    }

    انکڑے->registry = wl_display_get_registry(انکڑے->display);
    إذا (!انکڑے->registry) {
        أرجع SDL_سیٹ_Error("Failed to get the Wayland registry");
    }

    wl_registry_جوڑو_listener(انکڑے->registry, &registry_listener, انکڑے);

    // First roundtrip to receive all registry objects.
    WAYLAND_wl_display_roundtrip(انکڑے->display);

    // Require viewports and xdg-output for display scaling.
    إذا (انکڑے->scale_منزل_display_enabled) {
        إذا (!انکڑے->viewporter) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Display scaling requires the missing 'wp_viewporter' protocol: disabling");
            انکڑے->scale_منزل_display_enabled = false;
        }
        إذا (!انکڑے->xdg_output_manager) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Display scaling requires the missing 'zxdg_output_manager_v1' protocol: disabling");
            انکڑے->scale_منزل_display_enabled = false;
        }
    }

    // Now that we have all the protocols, load libdecor if applicable
    Wayland_لدو_Libdecor(انکڑے, false);

    // Second roundtrip to receive all output events.
    WAYLAND_wl_display_roundtrip(انکڑے->display);

    Wayland_FinalizeDisplays(انکڑے);

    Wayland_InitMouse(انکڑے);
    Wayland_InitKeyboard(_this);

    إذا (انکڑے->primary_selection_device_manager) {
        _this->سیٹ_Primary_Selection_متن = Wayland_سیٹ_Primary_Selection_متن;
        _this->Get_Primary_Selection_متن = Wayland_Get_Primary_Selection_متن;
        _this->Has_Primary_Selection_متن = Wayland_Has_Primary_Selection_متن;
    }

    انکڑے->initializing = false;

    أرجع true;
}

ساكن bool Wayland_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    SDL_Video_انکڑے *viddata = _this->اندرونی;
    SDL_Display_انکڑے *اندرونی = display->اندرونی;

    إذا (!viddata->scale_منزل_display_enabled) {
        rect->x = اندرونی->logical.x;
        rect->y = اندرونی->logical.y;
    } وإلا {
        rect->x = اندرونی->pixel.x;
        rect->y = اندرونی->pixel.y;
    }

    // When an emulated, exclusive fullscreen window has focus, treat the mode dimensions as the display bounds.
    إذا (display->fullscreen_کھڑکی &&
        display->fullscreen_کھڑکی->fullscreen_exclusive &&
        display->fullscreen_کھڑکی->اندرونی->سرگرم &&
        display->fullscreen_کھڑکی->current_fullscreen_منوال.w != 0 &&
        display->fullscreen_کھڑکی->current_fullscreen_منوال.h != 0) {
        rect->w = display->fullscreen_کھڑکی->current_fullscreen_منوال.w;
        rect->h = display->fullscreen_کھڑکی->current_fullscreen_منوال.h;
    } وإلا {
        إذا (!viddata->scale_منزل_display_enabled) {
            rect->w = display->current_منوال->w;
            rect->h = display->current_منوال->h;
        } وإلا إذا (اندرونی->transform & WL_OUTPUT_TRANSFORM_90) {
            rect->w = اندرونی->pixel.اچائی;
            rect->h = اندرونی->pixel.چوڑائی;
        } وإلا {
            rect->w = اندرونی->pixel.چوڑائی;
            rect->h = اندرونی->pixel.اچائی;
        }
    }
    أرجع true;
}

ساكن فراغ Wayland_VideoCleanup(SDL_VideoDevice *_this)
{
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;
    SDL_WaylandSeat *seat, *tmp;

    Wayland_SessionDestroy(انکڑے);

    لكل (صحيح i = _this->عدد_displays - 1; i >= 0; --i) {
        SDL_VideoDisplay *display = _this->displays[i];
        Wayland_free_display(display, false);
    }
    SDL_free(انکڑے->output_list);

    wl_list_for_each_محفوظ (seat, tmp, &انکڑے->seat_list, link) {
        Wayland_SeatDestroy(seat, true);
    }

    Wayland_FiniMouse(انکڑے);
    Wayland_QuitKeyboard(_this);

    Wayland_DestroyEventThread(انکڑے->event_thread_context);
    انکڑے->event_thread_context = عدم;

    Wayland_Destroy_کم_Thread(انکڑے->کم_thread_context);
    انکڑے->کم_thread_context = عدم;

    إذا (انکڑے->اشارہ_گر_constraints) {
        zwp_اشارہ_گر_constraints_v1_destroy(انکڑے->اشارہ_گر_constraints);
        انکڑے->اشارہ_گر_constraints = عدم;
    }

    إذا (انکڑے->relative_اشارہ_گر_manager) {
        zwp_relative_اشارہ_گر_manager_v1_destroy(انکڑے->relative_اشارہ_گر_manager);
        انکڑے->relative_اشارہ_گر_manager = عدم;
    }

    إذا (انکڑے->activation_manager) {
        xdg_activation_v1_destroy(انکڑے->activation_manager);
        انکڑے->activation_manager = عدم;
    }

    إذا (انکڑے->idle_inhibit_manager) {
        zwp_idle_inhibit_manager_v1_destroy(انکڑے->idle_inhibit_manager);
        انکڑے->idle_inhibit_manager = عدم;
    }

    إذا (انکڑے->کلید_inhibitor_manager) {
        zwp_keyboard_shortcuts_inhibit_manager_v1_destroy(انکڑے->کلید_inhibitor_manager);
        انکڑے->کلید_inhibitor_manager = عدم;
    }

    إذا (انکڑے->متن_داخلہ_manager) {
        zwp_متن_داخلہ_manager_v3_destroy(انکڑے->متن_داخلہ_manager);
        انکڑے->متن_داخلہ_manager = عدم;
    }

    إذا (انکڑے->xkb_context) {
        WAYLAND_xkb_context_unref(انکڑے->xkb_context);
        انکڑے->xkb_context = عدم;
    }

    إذا (انکڑے->tablet_manager) {
        zwp_tablet_manager_v2_destroy((بنية zwp_tablet_manager_v2 *)انکڑے->tablet_manager);
        انکڑے->tablet_manager = عدم;
    }

    إذا (انکڑے->انکڑے_device_manager) {
        wl_انکڑے_device_manager_destroy(انکڑے->انکڑے_device_manager);
        انکڑے->انکڑے_device_manager = عدم;
    }

    إذا (انکڑے->shm) {
        إذا (wl_shm_get_نسخہ(انکڑے->shm) >= WL_SHM_RELEASE_SINCE_نسخہ) {
            wl_shm_release(انکڑے->shm);
        } وإلا {
            wl_shm_destroy(انکڑے->shm);
        }
        انکڑے->shm = عدم;
    }

    إذا (انکڑے->shell.xdg) {
        xdg_wm_ادھار_destroy(انکڑے->shell.xdg);
        انکڑے->shell.xdg = عدم;
    }

    إذا (انکڑے->decoration_manager) {
        zxdg_decoration_manager_v1_destroy(انکڑے->decoration_manager);
        انکڑے->decoration_manager = عدم;
    }

    إذا (انکڑے->xdg_output_manager) {
        zxdg_output_manager_v1_destroy(انکڑے->xdg_output_manager);
        انکڑے->xdg_output_manager = عدم;
    }

    إذا (انکڑے->viewporter) {
        wp_viewporter_destroy(انکڑے->viewporter);
        انکڑے->viewporter = عدم;
    }

    إذا (انکڑے->primary_selection_device_manager) {
        zwp_primary_selection_device_manager_v1_destroy(انکڑے->primary_selection_device_manager);
        انکڑے->primary_selection_device_manager = عدم;
    }

    إذا (انکڑے->fractional_scale_manager) {
        wp_fractional_scale_manager_v1_destroy(انکڑے->fractional_scale_manager);
        انکڑے->fractional_scale_manager = عدم;
    }

    إذا (انکڑے->داخلہ_timestamps_manager) {
        zwp_داخلہ_timestamps_manager_v1_destroy(انکڑے->داخلہ_timestamps_manager);
        انکڑے->داخلہ_timestamps_manager = عدم;
    }

    إذا (انکڑے->cursor_shape_manager) {
        wp_cursor_shape_manager_v1_destroy(انکڑے->cursor_shape_manager);
        انکڑے->cursor_shape_manager = عدم;
    }

    إذا (انکڑے->zxdg_exporter_v2) {
        zxdg_exporter_v2_destroy(انکڑے->zxdg_exporter_v2);
        انکڑے->zxdg_exporter_v2 = عدم;
    }

    إذا (انکڑے->xdg_wm_dialog_v1) {
        xdg_wm_dialog_v1_destroy(انکڑے->xdg_wm_dialog_v1);
        انکڑے->xdg_wm_dialog_v1 = عدم;
    }

    إذا (انکڑے->wp_alpha_modifier_v1) {
        wp_alpha_modifier_v1_destroy(انکڑے->wp_alpha_modifier_v1);
        انکڑے->wp_alpha_modifier_v1 = عدم;
    }

    إذا (انکڑے->xdg_toplevel_icon_manager_v1) {
        xdg_toplevel_icon_manager_v1_destroy(انکڑے->xdg_toplevel_icon_manager_v1);
        انکڑے->xdg_toplevel_icon_manager_v1 = عدم;
    }

    إذا (انکڑے->frog_color_management_factory_v1) {
        frog_color_management_factory_v1_destroy(انکڑے->frog_color_management_factory_v1);
        انکڑے->frog_color_management_factory_v1 = عدم;
    }

    إذا (انکڑے->wp_color_manager_v1) {
        wp_color_manager_v1_destroy(انکڑے->wp_color_manager_v1);
        انکڑے->wp_color_manager_v1 = عدم;
    }

    إذا (انکڑے->wp_اشارہ_گر_warp_v1) {
        wp_اشارہ_گر_warp_v1_destroy(انکڑے->wp_اشارہ_گر_warp_v1);
        انکڑے->wp_اشارہ_گر_warp_v1 = عدم;
    }

    إذا (انکڑے->zwp_اشارہ_گر_gestures) {
        إذا (zwp_اشارہ_گر_gestures_v1_get_نسخہ(انکڑے->zwp_اشارہ_گر_gestures) >= ZWP_اشارہ_گر_GESTURES_V1_RELEASE_SINCE_نسخہ) {
            zwp_اشارہ_گر_gestures_v1_release(انکڑے->zwp_اشارہ_گر_gestures);
        } وإلا {
            zwp_اشارہ_گر_gestures_v1_destroy(انکڑے->zwp_اشارہ_گر_gestures);
        }
        انکڑے->zwp_اشارہ_گر_gestures = عدم;
    }

    إذا (انکڑے->single_pixel_بفر_manager) {
        wp_single_pixel_بفر_manager_v1_destroy(انکڑے->single_pixel_بفر_manager);
        انکڑے->single_pixel_بفر_manager = عدم;
    }

    إذا (انکڑے->xdg_session_manager) {
        xdg_session_manager_v1_destroy(انکڑے->xdg_session_manager);
        انکڑے->xdg_session_manager = عدم;
    }

    إذا (انکڑے->xdg_toplevel_ٹیگ_manager) {
        xdg_toplevel_ٹیگ_manager_v1_destroy(انکڑے->xdg_toplevel_ٹیگ_manager);
        انکڑے->xdg_toplevel_ٹیگ_manager = عدم;
    }

    إذا (انکڑے->subcompositor) {
        wl_subcompositor_destroy(انکڑے->subcompositor);
        انکڑے->subcompositor = عدم;
    }

    إذا (انکڑے->compositor) {
        wl_compositor_destroy(انکڑے->compositor);
        انکڑے->compositor = عدم;
    }

    إذا (انکڑے->registry) {
        إذا (انکڑے->wl_fixes) {
            wl_fixes_destroy_registry(انکڑے->wl_fixes, انکڑے->registry);
            wl_fixes_destroy(انکڑے->wl_fixes);
            انکڑے->wl_fixes = عدم;
        }
        wl_registry_destroy(انکڑے->registry);
        انکڑے->registry = عدم;
    }
}

ساكن bool Wayland_VideoReconnect(SDL_VideoDevice *_this)
{
#إذا 0 // TODO RECONNECT: Uncomment all when https://invent.kde.org/plasma/kwin/-/wikis/Restarting is completed
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;

    SDL_کھڑکی *کھڑکی = عدم;

    SDL_GLContext current_ctx = SDL_GL_GetCurrentContext();
    SDL_کھڑکی *current_کھڑکی = SDL_GL_Get_Current_کھڑکی();

    SDL_GL_MakeCurrent(عدم, عدم);
    Wayland_VideoCleanup(_this);

    SDL_ResetKeyboard();
    SDL_ResetMouse();
    إذا (WAYLAND_wl_display_reconnect(انکڑے->display) < 0) {
        أرجع false;
    }

    Wayland_VideoInit(_this);

    کھڑکی = _this->windows;
    طالما (کھڑکی) {
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

    إذا (current_کھڑکی && current_ctx) {
        SDL_GL_MakeCurrent (current_کھڑکی, current_ctx);
    }
    أرجع true;
#وإلا
    أرجع false;
#جے_انت // 0
}

bool Wayland_HandleDisplayDisconnected(SDL_VideoDevice *_this)
{
    SDL_Video_انکڑے *video_انکڑے = _this->اندرونی;

    /* Something has failed with the Wayland connection -- for example,
     * the compositor may have shut down and closed its end of the socket,
     * or there is a library-specific error.
     *
     * Try to recover once, then quit.
     */
    إذا (video_انکڑے->display_disconnected) {
        أرجع false;
    }

    إذا (Wayland_VideoReconnect(_this)) {
        أرجع true;
    }

    video_انکڑے->display_disconnected = true;
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Wayland display connection closed by server (fatal)");

    // Only send a single quit message, as application shutdown might call SDL_PumpEvents().
    SDL_SendQuit();

    أرجع false;
}

فراغ Wayland_VideoQuit(SDL_VideoDevice *_this)
{
    Wayland_VideoCleanup(_this);

#جے_تعریف_شدہ HAVE_LIBDECOR_H
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;
    إذا (انکڑے->shell.libdecor) {
        libdecor_unref(انکڑے->shell.libdecor);
        انکڑے->shell.libdecor = عدم;
    }
#جے_انت
}

#جے_انت // SDL_VIDEO_DRIVER_WAYLAND
