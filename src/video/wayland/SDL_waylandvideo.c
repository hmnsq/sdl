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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_WAYLAND

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

#اگر_تعریف_شده HAVE_LIBDECOR_H
#ضمن <libdecor.h>
#پایان_اگر

#تعریف_کن WAYLANDVID_DRIVER_NAME "wayland"

// Clamp core protocol versions on older versions of libwayland.
#إذا SDL_WAYLAND_CHECK_نسخه(1, 22, 0)
#تعریف_کن SDL_WL_COMPOSITOR_نسخه 6
#وإلا
#تعریف_کن SDL_WL_COMPOSITOR_نسخه 4
#پایان_اگر

#إذا SDL_WAYLAND_CHECK_نسخه(1, 26, 0)
#تعریف_کن SDL_WL_SEAT_نسخه 11
#وإلاإذا SDL_WAYLAND_CHECK_نسخه(1, 24, 0)
#تعریف_کن SDL_WL_SEAT_نسخه 10
#وإلاإذا SDL_WAYLAND_CHECK_نسخه(1, 22, 0)
#تعریف_کن SDL_WL_SEAT_نسخه 9
#وإلاإذا SDL_WAYLAND_CHECK_نسخه(1, 21, 0)
#تعریف_کن SDL_WL_SEAT_نسخه 8
#وإلا
#تعریف_کن SDL_WL_SEAT_نسخه 5
#پایان_اگر

#إذا SDL_WAYLAND_CHECK_نسخه(1, 20, 0)
#تعریف_کن SDL_WL_OUTPUT_نسخه 4
#وإلا
#تعریف_کن SDL_WL_OUTPUT_نسخه 3
#پایان_اگر

#إذا SDL_WAYLAND_CHECK_نسخه(1, 24, 0)
#تعریف_کن SDL_WL_SHM_نسخه 2
#وإلا
#تعریف_کن SDL_WL_SHM_نسخه 1
#پایان_اگر

// The SDL libwayland-client minimum is 1.18, which supports version 3.
#تعریف_کن SDL_WL_داده_DEVICE_نسخه 3

// wl_fixes was introduced in 1.24.0
#إذا SDL_WAYLAND_CHECK_نسخه(1, 26, 0)
#تعریف_کن SDL_WL_FIXES_نسخه 2
#وإلاإذا SDL_WAYLAND_CHECK_نسخه(1, 24, 0)
#تعریف_کن SDL_WL_FIXES_نسخه 1
#پایان_اگر

#اگر_تعریف_شده SDL_USE_LIBDBUS
#ضمن "../../core/linux/SDL_dbus.h"

#تعریف_کن DISPLAY_INFO_گره   "org.gnome.Mutter.DisplayConfig"
#تعریف_کن DISPLAY_INFO_مسیر   "/org/gnome/Mutter/DisplayConfig"
#تعریف_کن DISPLAY_INFO_روش "GetCurrentState"
#پایان_اگر

/* GNOME doesn't expose displays in any particular order, but we can find the
 * primary display and its logical coordinates via a DBus method.
 */
ساكن bool Wayland_GetGNOMEPrimaryDisplayCoordinates(صحيح *x, صحيح *y)
{
#اگر_تعریف_شده SDL_USE_LIBDBUS
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    إذا (dbus == عدم) {
        أرجع false;
    }
    DBus_پیام *پاسخ = عدم;
    DBus_پیام_Iter iter[3];
    DBus_پیام *پیام_2 = dbus->پیام_new_روش_call(DISPLAY_INFO_گره,
                                                     DISPLAY_INFO_مسیر,
                                                     DISPLAY_INFO_گره,
                                                     DISPLAY_INFO_روش);

    إذا (پیام_2) {
        پاسخ = dbus->connection_send_with_پاسخ_and_بلوک(dbus->session_conn, پیام_2, DBUS_TIMEOUT_USE_DEFAULT, عدم);
        dbus->پیام_unref(پیام_2);
    }

    إذا (پاسخ) {
        // Serial (don't care)
        dbus->پیام_iter_init(پاسخ, &iter[0]);
        إذا (dbus->پیام_iter_get_arg_type(&iter[0]) != DBUS_TYPE_UINT32) {
            اذهب error;
        }

        // Physical monitor array (don't care)
        dbus->پیام_iter_بعدی(&iter[0]);
        إذا (dbus->پیام_iter_get_arg_type(&iter[0]) != DBUS_TYPE_ARRAY) {
            اذهب error;
        }

        // Logical monitor array of structs
        dbus->پیام_iter_بعدی(&iter[0]);
        إذا (dbus->پیام_iter_get_arg_type(&iter[0]) != DBUS_TYPE_ARRAY) {
            اذهب error;
        }

        // First logical monitor struct
        dbus->پیام_iter_recurse(&iter[0], &iter[1]);
        إذا (dbus->پیام_iter_get_arg_type(&iter[1]) != DBUS_TYPE_STRUCT) {
            اذهب error;
        }

        افعل {
            صحيح logical_x, logical_y;
            dbus_bool_t primary;

            // Logical X
            dbus->پیام_iter_recurse(&iter[1], &iter[2]);
            إذا (dbus->پیام_iter_get_arg_type(&iter[2]) != DBUS_TYPE_INT32) {
                اذهب error;
            }
            dbus->پیام_iter_get_basic(&iter[2], &logical_x);

            // Logical Y
            dbus->پیام_iter_بعدی(&iter[2]);
            إذا (dbus->پیام_iter_get_arg_type(&iter[2]) != DBUS_TYPE_INT32) {
                اذهب error;
            }
            dbus->پیام_iter_get_basic(&iter[2], &logical_y);

            // Scale (don't care)
            dbus->پیام_iter_بعدی(&iter[2]);
            إذا (dbus->پیام_iter_get_arg_type(&iter[2]) != DBUS_TYPE_DOUBLE) {
                اذهب error;
            }

            // Transform (don't care)
            dbus->پیام_iter_بعدی(&iter[2]);
            إذا (dbus->پیام_iter_get_arg_type(&iter[2]) != DBUS_TYPE_UINT32) {
                اذهب error;
            }

            // Primary display boolean
            dbus->پیام_iter_بعدی(&iter[2]);
            إذا (dbus->پیام_iter_get_arg_type(&iter[2]) != DBUS_TYPE_BOOLEAN) {
                اذهب error;
            }
            dbus->پیام_iter_get_basic(&iter[2], &primary);

            إذا (primary) {
                *x = logical_x;
                *y = logical_y;

                // We found the primary display: success.
                dbus->پیام_unref(پاسخ);
                أرجع true;
            }
        } طالما (dbus->پیام_iter_بعدی(&iter[1]));
    }

error:
    إذا (پاسخ) {
        dbus->پیام_unref(پاسخ);
    }
#پایان_اگر
    أرجع false;
}

// Sort the list of displays into a deterministic order
ساكن صحيح SDLCALL Wayland_DisplayPositionCompare(ثابت فراغ *a, ثابت فراغ *b)
{
    ثابت SDL_Display_داده *da = *(SDL_Display_داده **)a;
    ثابت SDL_Display_داده *db = *(SDL_Display_داده **)b;
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
ساكن صحيح Wayland_GetPrimaryDisplay(SDL_Video_داده *vid)
{
    ساكن ثابت صحيح REFRESH_DELTA = 4000;

    // Query the DBus interface to see if the coordinates of the primary display are exposed.
    صحيح x, y;
    إذا (Wayland_GetGNOMEPrimaryDisplayCoordinates(&x, &y)) {
        لكل (صحيح i = 0; i < vid->output_شمار; ++i) {
            إذا (vid->output_list[i]->logical.x == x && vid->output_list[i]->logical.y == y) {
                أرجع i;
            }
        }
    }

    // Otherwise, choose the 'best' display.
    صحيح بهترین_عرض = 0;
    صحيح بهترین_ارتفاع = 0;
    مزدوج بهترین_scale = 0.0;
    عائم بهترین_headroom = 0.0f;
    صحيح بهترین_refresh = 0;
    bool بهترین_is_landscape = false;
    صحيح بهترین_شاخص = 0;

    لكل (صحيح i = 0; i < vid->output_شمار; ++i) {
        ثابت SDL_Display_داده *d = vid->output_list[i];
        ثابت bool is_landscape = d->orientation != SDL_ORIENTATION_PORTRAIT && d->orientation != SDL_ORIENTATION_PORTRAIT_FLIPPED;
        bool have_new_بهترین = false;

        إذا (!بهترین_is_landscape && is_landscape) { // Favor landscape over portrait displays.
            have_new_بهترین = true;
        } وإلا إذا (!بهترین_is_landscape || is_landscape) { // Ignore portrait displays if a landscape was already found.
            إذا (d->pixel.عرض > بهترین_عرض || d->pixel.ارتفاع > بهترین_ارتفاع) {
                have_new_بهترین = true;
            } وإلا إذا (d->pixel.عرض == بهترین_عرض && d->pixel.ارتفاع == بهترین_ارتفاع) {
                إذا (d->HDR.HDR_headroom > بهترین_headroom) { // Favor a higher HDR luminance range
                    have_new_بهترین = true;
                } وإلا إذا (d->HDR.HDR_headroom == بهترین_headroom) {
                    إذا (d->refresh - بهترین_refresh > REFRESH_DELTA) { // Favor a higher refresh rate, but ignore small differences (e.g. 59.97 vs 60.1)
                        have_new_بهترین = true;
                    } وإلا إذا (d->scale_ضریب_2 < بهترین_scale && SDL_abs(d->refresh - بهترین_refresh) <= REFRESH_DELTA) {
                        // Prefer a lower scale display if the difference in refresh rate is small.
                        have_new_بهترین = true;
                    }
                }
            }
        }

        إذا (have_new_بهترین) {
            بهترین_عرض = d->pixel.عرض;
            بهترین_ارتفاع = d->pixel.ارتفاع;
            بهترین_scale = d->scale_ضریب_2;
            بهترین_headroom = d->HDR.HDR_headroom;
            بهترین_refresh = d->refresh;
            بهترین_is_landscape = is_landscape;
            بهترین_شاخص = i;
        }
    }

    أرجع بهترین_شاخص;
}

ساكن فراغ Wayland_مرتب_سازی_Outputs_By_اولویت_Hint(SDL_Video_داده *vid)
{
    ثابت حرف *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_اولویت);

    إذا (name_hint) {
        حرف *saveptr;
        حرف *str = SDL_strdup(name_hint);
        SDL_Display_داده **sorted_list = SDL_malloc(حجم(SDL_Display_داده *) * vid->output_شمار);

        إذا (str && sorted_list) {
            صحيح sorted_شاخص = 0;

            // Sort the requested displays to the front of the list.
            ثابت حرف *token = SDL_strtok_r(str, ",", &saveptr);
            طالما (token) {
                لكل (صحيح i = 0; i < vid->output_شمار; ++i) {
                    SDL_Display_داده *d = vid->output_list[i];
                    إذا (d && d->wl_output_name && SDL_strcmp(token, d->wl_output_name) == 0) {
                        sorted_list[sorted_شاخص++] = d;
                        vid->output_list[i] = عدم;
                        اكسر;
                    }
                }

                token = SDL_strtok_r(عدم, ",", &saveptr);
            }

            // Append the remaining outputs to the end of the list.
            لكل (صحيح i = 0; i < vid->output_شمار; ++i) {
                إذا (vid->output_list[i]) {
                    sorted_list[sorted_شاخص++] = vid->output_list[i];
                }
            }

            // Copy the sorted list to the output list.
            SDL_memcpy(vid->output_list, sorted_list, حجم(SDL_Display_داده *) * vid->output_شمار);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

ساكن فراغ Wayland_DeriveOutputPixelCoordinates(SDL_Video_داده *vid)
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
    لكل ( صحيح i = 0; i < vid->output_شمار; ++i) {
        SDL_Display_داده *d = vid->output_list[i];
        d->pixel.x = d->logical.x;
        d->pixel.y = d->logical.y;
    }

    لكل (صحيح i = 0; i < vid->output_شمار; ++i) {
        SDL_Display_داده *d1 = vid->output_list[i];
        إذا (d1->logical.عرض != d1->pixel.عرض || d1->logical.ارتفاع != d1->pixel.ارتفاع) {
            ثابت صحيح x_adj = d1->pixel.عرض - d1->logical.عرض;
            ثابت صحيح y_adj = d1->pixel.ارتفاع - d1->logical.ارتفاع;

            // Don't adjust for scale values less than 1.0.
            إذا (x_adj > 0 && y_adj > 0) {
                لكل (صحيح j = 0; j < vid->output_شمار; ++j) {
                    SDL_Display_داده *d2 = vid->output_list[j];
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

ساكن فراغ Wayland_مرتب_سازی_Outputs(SDL_Video_داده *vid)
{
    // Sort by position or connector name, so the order of outputs is deterministic.
    SDL_qsort(vid->output_list, vid->output_شمار, حجم(SDL_Display_داده *), Wayland_DisplayPositionCompare);

    // Derive the output pixel coordinates if scale to display is enabled.
    إذا (vid->scale_مقصد_display_enabled) {
        Wayland_DeriveOutputPixelCoordinates(vid);
    }

    // Find a suitable primary display and move it to the front of the list.
    ثابت صحيح primary_شاخص = Wayland_GetPrimaryDisplay(vid);
    إذا (primary_شاخص) {
        SDL_Display_داده *primary = vid->output_list[primary_شاخص];
        SDL_memmove(&vid->output_list[1], &vid->output_list[0], حجم(SDL_Display_داده *) * primary_شاخص);
        vid->output_list[0] = primary;
    }

    // Apply the ordering hint, if specified.
    Wayland_مرتب_سازی_Outputs_By_اولویت_Hint(vid);
}

ساكن فراغ Wayland_Refresh_پنجره_Positions()
{
    SDL_VideoDevice *vid = SDL_GetVideoDevice();

    لكل (SDL_پنجره *w = vid->windows; w; w = w->بعدی) {
        Wayland_Update_پنجره_Position(w);
    }
}

ساكن فراغ handle_wl_output_انجامشده(فراغ *داده, بنية wl_output *output);

// Initialization/Query functions
ساكن bool Wayland_VideoInit(SDL_VideoDevice *_this);
ساكن bool Wayland_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
ساكن فراغ Wayland_VideoQuit(SDL_VideoDevice *_this);

ساكن ثابت حرف *SDL_WAYLAND_surface_برچسب = "sdl-window";
ساكن ثابت حرف *SDL_WAYLAND_output_برچسب = "sdl-output";

فراغ SDL_WAYLAND_ثبات_surface(بنية wl_surface *surface)
{
    wl_proxy_مجموعه_برچسب((بنية wl_proxy *)surface, &SDL_WAYLAND_surface_برچسب);
}

فراغ SDL_WAYLAND_ثبات_output(بنية wl_output *output)
{
    wl_proxy_مجموعه_برچسب((بنية wl_proxy *)output, &SDL_WAYLAND_output_برچسب);
}

bool SDL_WAYLAND_own_surface(بنية wl_surface *surface)
{
    أرجع wl_proxy_get_برچسب((بنية wl_proxy *)surface) == &SDL_WAYLAND_surface_برچسب;
}

bool SDL_WAYLAND_own_output(بنية wl_output *output)
{
    أرجع wl_proxy_get_برچسب((بنية wl_proxy *)output) == &SDL_WAYLAND_output_برچسب;
}

/* External surfaces may have their own user data attached, the modification of which
 * can cause problems with external toolkits. Instead, external windows are kept in
 * their own list, and a search is conducted to find a matching surface.
 */
ساكن بنية wl_list external_پنجره_list;

فراغ Wayland_جمع_کن_پنجره_داده_مقصد_External_List(SDL_پنجره_داده *داده)
{
    WAYLAND_wl_list_درج(&external_پنجره_list, &داده->external_پنجره_list_link);
}

فراغ Wayland_Remove_پنجره_داده_From_External_List(SDL_پنجره_داده *داده)
{
    WAYLAND_wl_list_remove(&داده->external_پنجره_list_link);
}

SDL_پنجره_داده *Wayland_Get_پنجره_داده_For_Owned_Surface(بنية wl_surface *surface)
{
    إذا (SDL_WAYLAND_own_surface(surface)) {
        أرجع (SDL_پنجره_داده *)wl_surface_get_user_داده(surface);
    } وإلا إذا (!WAYLAND_wl_list_خالی(&external_پنجره_list)) {
        SDL_پنجره_داده *p;
        wl_list_for_each (p, &external_پنجره_list, external_پنجره_list_link) {
            إذا (p->surface == surface) {
                أرجع p;
            }
        }
    }

    أرجع عدم;
}

بنية wl_event_صف *Wayland_Display_Create_صف(بنية wl_display *display, ثابت حرف *name)
{
#اگر_تعریف_شده SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
    إذا (WAYLAND_wl_display_create_صف_with_name) {
        أرجع WAYLAND_wl_display_create_صف_with_name(display, name);
    }
#وإلاإذا SDL_WAYLAND_CHECK_نسخه(1, 23, 0)
    أرجع WAYLAND_wl_display_create_صف_with_name(display, name);
#پایان_اگر
    أرجع WAYLAND_wl_display_create_صف(display);
}

ساكن فراغ Wayland_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_Video_داده *داده = device->داخلی;
    إذا (داده->display && !داده->display_externally_owned) {
        WAYLAND_wl_display_disconnect(داده->display);
        SDL_ClearProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_اشاره_گر);
    }
    SDL_free(داده);
    SDL_free(device);
    SDL_WAYLAND_UnloadSymbols();
}

تعريفنوع بنية
{
    bool has_fifo_v1;
    بنية wl_fixes *wl_fixes;
} SDL_Wayland_Preferred_داده;

ساكن فراغ wayland_preferred_check_handle_global(فراغ *داده, بنية wl_registry *registry, uint32_t id,
                                                  ثابت حرف *interface, uint32_t نسخه)
{
    SDL_Wayland_Preferred_داده *d = داده;

    إذا (SDL_strcmp(interface, "wp_fifo_manager_v1") == 0) {
        d->has_fifo_v1 = true;
    }
#اگر_تعریف_شده SDL_WL_FIXES_نسخه
    وإلا إذا (SDL_strcmp(interface, wl_fixes_interface.name) == 0) {
        d->wl_fixes = wl_registry_bind(registry, id, &wl_fixes_interface, SDL_min(SDL_WL_FIXES_نسخه, نسخه));
    }
#پایان_اگر
}

ساكن فراغ wayland_preferred_check_remove_global(فراغ *داده, بنية wl_registry *registry, uint32_t id)
{
    SDL_Wayland_Preferred_داده *d = (SDL_Wayland_Preferred_داده *)داده;

    إذا (d->wl_fixes && wl_fixes_get_نسخه(d->wl_fixes) >= WL_FIXES_ACK_GLOBAL_REMOVE_SINCE_نسخه) {
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
    SDL_Wayland_Preferred_داده preferred_داده = { 0 };

    إذا (!registry) {
        SDL_مجموعه_Error("Failed to get the Wayland registry");
        أرجع false;
    }

    wl_registry_جمع_کن_listener(registry, &preferred_registry_listener, &preferred_داده);

    WAYLAND_wl_display_roundtrip(display);

    إذا (preferred_داده.wl_fixes) {
        wl_fixes_destroy_registry(preferred_داده.wl_fixes, registry);
        wl_fixes_destroy(preferred_داده.wl_fixes);
    }
    wl_registry_destroy(registry);

    إذا (!preferred_داده.has_fifo_v1) {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "This compositor lacks support for the fifo-v1 protocol; falling back to XWayland for GPU performance reasons (set SDL_VIDEO_DRIVER=wayland to override)");
    }
    أرجع preferred_داده.has_fifo_v1;
}

ساكن SDL_VideoDevice *Wayland_CreateDevice(bool require_preferred_protocols)
{
    SDL_VideoDevice *device;
    SDL_Video_داده *داده;
    بنية wl_display *display = SDL_Get_اشاره_گر_Property(SDL_GetGlobalProperties(),
                                                 SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_اشاره_گر, عدم);
    bool display_is_external = !!display;

    // Are we trying to connect to, or are currently in, a Wayland session?
    إذا (!SDL_getenv("WAYLAND_DISPLAY")) {
        ثابت حرف *session = SDL_getenv("XDG_SESSION_TYPE");
        إذا (session && SDL_strcasecmp(session, "wayland") != 0) {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Wayland initialization failed: no Wayland session available");
            أرجع عدم;
        }
    }

    إذا (!SDL_WAYLAND_بارگیری_Symbols()) {
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

    داده = SDL_calloc(1, حجم(*داده));
    إذا (!داده) {
        إذا (!display_is_external) {
            WAYLAND_wl_display_disconnect(display);
        }
        SDL_WAYLAND_UnloadSymbols();
        أرجع عدم;
    }

    داده->initializing = true;
    داده->display = display;
    داده->display_externally_owned = display_is_external;
    داده->scale_مقصد_display_enabled = SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_SCALE_مقصد_DISPLAY, false);
    WAYLAND_wl_list_init(&داده->seat_list);
    WAYLAND_wl_list_init(&external_پنجره_list);

    // Initialize all variables that we clean on shutdown
    device = SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (!device) {
        SDL_free(داده);
        إذا (!display_is_external) {
            WAYLAND_wl_display_disconnect(display);
        }
        SDL_WAYLAND_UnloadSymbols();
        أرجع عدم;
    }

    إذا (!display_is_external) {
        SDL_مجموعه_اشاره_گر_Property(SDL_GetGlobalProperties(),
                               SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_اشاره_گر, display);
    }

    device->داخلی = داده;

    // Set the function pointers
    device->VideoInit = Wayland_VideoInit;
    device->VideoQuit = Wayland_VideoQuit;
    device->GetDisplayBounds = Wayland_GetDisplayBounds;
    device->SuspendScreenSaver = Wayland_SuspendScreenSaver;

    device->PumpEvents = Wayland_PumpEvents;
    device->WaitEventTimeout = Wayland_WaitEventTimeout;
    device->SendWakeupEvent = Wayland_SendWakeupEvent;

#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
    device->GL_جابجا_پنجره = Wayland_GLES_جابجا_پنجره;
    device->GL_Get_جابجا_Interval = Wayland_GLES_Get_جابجا_Interval;
    device->GL_مجموعه_جابجا_Interval = Wayland_GLES_مجموعه_جابجا_Interval;
    device->GL_MakeCurrent = Wayland_GLES_MakeCurrent;
    device->GL_CreateContext = Wayland_GLES_CreateContext;
    device->GL_بارگیری_Library = Wayland_GLES_بارگیری_Library;
    device->GL_UnloadLibrary = Wayland_GLES_UnloadLibrary;
    device->GL_Get_Proc_آدرس = Wayland_GLES_Get_Proc_آدرس;
    device->GL_DestroyContext = Wayland_GLES_DestroyContext;
    device->GL_مجموعه_Default_Profile_Config = Wayland_GLES_مجموعه_Default_Profile_Config;
    device->GL_GetEGLSurface = Wayland_GLES_GetEGLSurface;
#پایان_اگر

    device->CreateSDLWindow = Wayland_Create_پنجره;
    device->Show_پنجره = Wayland_Show_پنجره;
    device->Hide_پنجره = Wayland_Hide_پنجره;
    device->Raise_پنجره = Wayland_Raise_پنجره;
    device->مجموعه_پنجره_Fullscreen = Wayland_مجموعه_پنجره_Fullscreen;
    device->Maximize_پنجره = Wayland_Maximize_پنجره;
    device->Minimize_پنجره = Wayland_Minimize_پنجره;
    device->مجموعه_پنجره_Mouse_Rect = Wayland_مجموعه_پنجره_Mouse_Rect;
    device->مجموعه_پنجره_Mouse_Grab = Wayland_مجموعه_پنجره_Mouse_Grab;
    device->مجموعه_پنجره_Keyboard_Grab = Wayland_مجموعه_پنجره_Keyboard_Grab;
    device->Restore_پنجره = Wayland_Restore_پنجره;
    device->مجموعه_پنجره_Bordered = Wayland_مجموعه_پنجره_Bordered;
    device->مجموعه_پنجره_Resizable = Wayland_مجموعه_پنجره_Resizable;
    device->مجموعه_پنجره_Position = Wayland_مجموعه_پنجره_Position;
    device->مجموعه_پنجره_اندازه = Wayland_مجموعه_پنجره_اندازه;
    device->مجموعه_پنجره_Aspect_نسبت = Wayland_مجموعه_پنجره_Aspect_نسبت;
    device->مجموعه_پنجره_Minimum_اندازه = Wayland_مجموعه_پنجره_Minimum_اندازه;
    device->مجموعه_پنجره_بیشینه_اندازه = Wayland_مجموعه_پنجره_بیشینه_اندازه;
    device->مجموعه_پنجره_والد = Wayland_مجموعه_پنجره_والد;
    device->مجموعه_پنجره_Modal = Wayland_مجموعه_پنجره_Modal;
    device->مجموعه_پنجره_Opacity = Wayland_مجموعه_پنجره_Opacity;
    device->مجموعه_پنجره_Title = Wayland_مجموعه_پنجره_Title;
    device->مجموعه_پنجره_Icon = Wayland_مجموعه_پنجره_Icon;
    device->Get_پنجره_اندازه_درون_Pixels = Wayland_Get_پنجره_اندازه_درون_Pixels;
    device->Get_پنجره_Content_Scale = Wayland_Get_پنجره_Content_Scale;
    device->Get_پنجره_ICCProfile = Wayland_Get_پنجره_ICCProfile;
    device->Get_Display_For_پنجره = Wayland_Get_Display_For_پنجره;
    device->Destroy_پنجره = Wayland_Destroy_پنجره;
    device->مجموعه_پنجره_اصابت_Test = Wayland_مجموعه_پنجره_اصابت_Test;
    device->Flash_پنجره = Wayland_Flash_پنجره;
#اگر_تعریف_شده SDL_USE_LIBDBUS
    device->Apply_پنجره_پیشرفت = DBUS_Apply_پنجره_پیشرفت;
#پایان_اگر // SDL_USE_LIBDBUS
    device->HasScreenKeyboardSupport = Wayland_HasScreenKeyboardSupport;
    device->Show_پنجره_System_Menu = Wayland_Show_پنجره_System_Menu;
    device->Sync_پنجره = Wayland_Sync_پنجره;
    device->مجموعه_پنجره_Focusable = Wayland_مجموعه_پنجره_Focusable;
    device->Reconfigure_پنجره = Wayland_Reconfigure_پنجره;
    device->AcceptDragAndDrop = Wayland_AcceptDragAndDrop;

#اگر_تعریف_شده SDL_USE_LIBDBUS
    إذا (SDL_SystemTheme_Init())
        device->system_theme = SDL_SystemTheme_Get();
#پایان_اگر

    device->Get_متن_Mime_Types = Wayland_Get_متن_Mime_Types;
    device->مجموعه_Clipboard_داده = Wayland_مجموعه_Clipboard_داده;
    device->Get_Clipboard_داده = Wayland_Get_Clipboard_داده;
    device->Has_Clipboard_داده = Wayland_Has_Clipboard_داده;
    device->شروع_متن_درون_داد = Wayland_شروع_متن_درون_داد;
    device->Stop_متن_درون_داد = Wayland_Stop_متن_درون_داد;
    device->Update_متن_درون_داد_Area = Wayland_Update_متن_درون_داد_Area;

#اگر_تعریف_شده SDL_VIDEO_VULKAN
    device->Vulkan_بارگیری_Library = Wayland_Vulkan_بارگیری_Library;
    device->Vulkan_UnloadLibrary = Wayland_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = Wayland_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = Wayland_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = Wayland_Vulkan_DestroySurface;
    device->Vulkan_GetPresentationSupport = Wayland_Vulkan_GetPresentationSupport;
#پایان_اگر

    device->حرر = Wayland_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_نما_SWITCHING_EMULATED |
                          VIDEO_DEVICE_CAPS_HAS_POPUP_پنجره_SUPPORT |
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
    Wayland_Show_پیام_Box,
    true
};

VideoBootStrap Wayland_bootstrap = {
    WAYLANDVID_DRIVER_NAME, "SDL Wayland video driver",
    Wayland_Fallback_CreateDevice,
    Wayland_Show_پیام_Box,
    false
};

ساكن فراغ handle_xdg_output_logical_position(فراغ *داده, بنية zxdg_output_v1 *xdg_output, int32_t x, int32_t y)
{
    SDL_Display_داده *داخلی = (SDL_Display_داده *)داده;

    داخلی->geometry_تغییریافته |= داخلی->logical.x != x || داخلی->logical.y != y;
    داخلی->logical.x = x;
    داخلی->logical.y = y;
    داخلی->has_logical_position = true;
}

ساكن فراغ handle_xdg_output_logical_اندازه(فراغ *داده, بنية zxdg_output_v1 *xdg_output, int32_t عرض, int32_t ارتفاع)
{
    SDL_Display_داده *داخلی = (SDL_Display_داده *)داده;

    داخلی->geometry_تغییریافته |= داخلی->logical.عرض != عرض || داخلی->logical.ارتفاع != ارتفاع;
    داخلی->logical.عرض = عرض;
    داخلی->logical.ارتفاع = ارتفاع;
    داخلی->has_logical_اندازه = true;
}

ساكن فراغ handle_xdg_output_انجامشده(فراغ *داده, بنية zxdg_output_v1 *xdg_output)
{
    SDL_Display_داده *داخلی = داده;

    /*
     * xdg-output.done events are deprecated and only apply below version 3 of the protocol.
     * A wl-output.done event will be emitted in version 3 or higher.
     */
    إذا (zxdg_output_v1_get_نسخه(داخلی->xdg_output) < 3) {
        handle_wl_output_انجامشده(داده, داخلی->output);
    }
}

ساكن فراغ handle_xdg_output_name(فراغ *داده, بنية zxdg_output_v1 *xdg_output, ثابت حرف *name)
{
    SDL_Display_داده *داخلی = (SDL_Display_داده *)داده;

    // Deprecated as of wl_output v4.
    إذا (wl_output_get_نسخه(داخلی->output) < WL_OUTPUT_NAME_SINCE_نسخه &&
        داخلی->display == 0) {
        SDL_free(داخلی->wl_output_name);
        داخلی->wl_output_name = SDL_strdup(name);
    }
}

ساكن فراغ handle_xdg_output_description(فراغ *داده, بنية zxdg_output_v1 *xdg_output, ثابت حرف *description)
{
    SDL_Display_داده *داخلی = (SDL_Display_داده *)داده;

    // Deprecated as of wl_output v4.
    إذا (wl_output_get_نسخه(داخلی->output) < WL_OUTPUT_DESCRIPTION_SINCE_نسخه &&
        داخلی->display == 0) {
        // xdg-output descriptions, if available, supersede wl-output model names.
        SDL_free(داخلی->placeholder.name);
        داخلی->placeholder.name = SDL_strdup(description);
    }
}

ساكن ثابت بنية zxdg_output_v1_listener xdg_output_listener = {
    handle_xdg_output_logical_position,
    handle_xdg_output_logical_اندازه,
    handle_xdg_output_انجامشده,
    handle_xdg_output_name,
    handle_xdg_output_description,
};

ساكن فراغ جمع_کن_Emulated_Modes(SDL_Display_داده *dispdata, صحيح native_عرض, صحيح native_ارتفاع)
{
    بنية Emulated_نما
    {
        صحيح w;
        صحيح h;
    };

    // Resolution lists courtesy of XWayland
    ثابت بنية Emulated_نما نما_list[] = {
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
    SDL_Display_نما نما;
    SDL_VideoDisplay *dpy = dispdata->display ? SDL_GetVideoDisplay(dispdata->display) : &dispdata->placeholder;
    ثابت bool rot_90 = native_عرض < native_ارتفاع; // Reverse width/height for portrait displays.

    لكل (i = 0; i < SDL_arraysize(نما_list); ++i) {
        SDL_zero(نما);
        نما.format = dpy->desktop_نما.format;
        نما.refresh_نرخ_numerator = dpy->desktop_نما.refresh_نرخ_numerator;
        نما.refresh_نرخ_denominator = dpy->desktop_نما.refresh_نرخ_denominator;

        إذا (rot_90) {
            نما.w = نما_list[i].h;
            نما.h = نما_list[i].w;
        } وإلا {
            نما.w = نما_list[i].w;
            نما.h = نما_list[i].h;
        }

        // Only add modes that are smaller than the native mode.
        إذا ((نما.w < native_عرض && نما.h < native_ارتفاع) ||
            (نما.w < native_عرض && نما.h == native_ارتفاع) ||
            (نما.w == native_عرض && نما.h < native_ارتفاع)) {
            SDL_جمع_کن_Fullscreen_Display_نما(dpy, &نما);
        }
    }
}

ساكن فراغ handle_wl_output_geometry(فراغ *داده, بنية wl_output *output, صحيح x, صحيح y,
                                      صحيح physical_عرض_2, صحيح physical_ارتفاع_2, صحيح subpixel,
                                      ثابت حرف *make, ثابت حرف *model, صحيح transform)
{
    SDL_Display_داده *داخلی = (SDL_Display_داده *)داده;

    // Apply the change from wl-output only if xdg-output is not supported
    إذا (!داخلی->has_logical_position) {
        داخلی->geometry_تغییریافته |= داخلی->logical.x != x || داخلی->logical.y != y;
        داخلی->logical.x = x;
        داخلی->logical.y = y;
    }
    داخلی->physical.عرض_mm = physical_عرض_2;
    داخلی->physical.ارتفاع_mm = physical_ارتفاع_2;

    // The model is only used for the output name if wl_output or xdg-output haven't provided a description.
    إذا (داخلی->display == 0 && !داخلی->placeholder.name) {
        داخلی->placeholder.name = SDL_strdup(model);
    }

    داخلی->transform = transform;
#تعریف_کن TF_CASE(درون_2, بیرون)                                 \
    حالة WL_OUTPUT_TRANSFORM_##in:                       \
        داخلی->orientation = SDL_ORIENTATION_##out; \
        اكسر;
    إذا (داخلی->physical.عرض_mm >= داخلی->physical.ارتفاع_mm) {
        بدل (transform) {
            TF_CASE(نرمال_2, LANDSCAPE)
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
            TF_CASE(نرمال_2, PORTRAIT)
            TF_CASE(90, LANDSCAPE)
            TF_CASE(180, PORTRAIT_FLIPPED)
            TF_CASE(270, LANDSCAPE_FLIPPED)
            TF_CASE(FLIPPED, PORTRAIT_FLIPPED)
            TF_CASE(FLIPPED_90, LANDSCAPE_FLIPPED)
            TF_CASE(FLIPPED_180, PORTRAIT)
            TF_CASE(FLIPPED_270, LANDSCAPE)
        }
    }
#لغو_تعریف TF_CASE
}

ساكن فراغ handle_wl_output_نما(فراغ *داده, بنية wl_output *output, uint32_t flags,
                                  صحيح عرض, صحيح ارتفاع, صحيح refresh)
{
    SDL_Display_داده *داخلی = (SDL_Display_داده *)داده;

    إذا (flags & WL_OUTPUT_نما_CURRENT) {
        داخلی->geometry_تغییریافته |= داخلی->pixel.عرض != عرض || داخلی->pixel.ارتفاع != ارتفاع;
        داخلی->pixel.عرض = عرض;
        داخلی->pixel.ارتفاع = ارتفاع;

        /*
         * Don't rotate this yet, wl-output coordinates are transformed in
         * handle_done and xdg-output coordinates are pre-transformed.
         */
        إذا (!داخلی->has_logical_اندازه) {
            داخلی->geometry_تغییریافته |= داخلی->logical.عرض != عرض || داخلی->logical.ارتفاع != ارتفاع;
            داخلی->logical.عرض = عرض;
            داخلی->logical.ارتفاع = ارتفاع;
        }

        داخلی->refresh = refresh;
    }
}

ساكن فراغ handle_wl_output_انجامشده(فراغ *داده, بنية wl_output *output)
{
    ثابت bool نما_emulation_enabled = SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_نما_EMULATION, true);
    SDL_Display_داده *داخلی = (SDL_Display_داده *)داده;
    SDL_Video_داده *video = داخلی->videodata;
    SDL_Display_نما native_نما, desktop_نما;

    /*
     * When using xdg-output, two wl-output.done events will be emitted:
     * one at the completion of wl-display and one at the completion of xdg-output.
     *
     * All required events must be received before proceeding.
     */
    ثابت صحيح event_await_شمار = 1 + (داخلی->xdg_output != عدم);

    داخلی->wl_output_انجامشده_شمار = SDL_min(داخلی->wl_output_انجامشده_شمار + 1, event_await_شمار + 1);

    إذا (داخلی->wl_output_انجامشده_شمار < event_await_شمار) {
        أرجع;
    }

    // If the display was already created, reset and rebuild the mode list.
    SDL_VideoDisplay *dpy = SDL_GetVideoDisplay(داخلی->display);
    إذا (dpy) {
        SDL_ResetFullscreenDisplayModes(dpy);
    }

    // The native display resolution
    SDL_zero(native_نما);
    native_نما.format = SDL_PIXELFORMAT_XRGB8888;

    // Transform the pixel values, if necessary.
    إذا (داخلی->transform & WL_OUTPUT_TRANSFORM_90) {
        native_نما.w = داخلی->pixel.ارتفاع;
        native_نما.h = داخلی->pixel.عرض;
    } وإلا {
        native_نما.w = داخلی->pixel.عرض;
        native_نما.h = داخلی->pixel.ارتفاع;
    }
    native_نما.refresh_نرخ_numerator = داخلی->refresh;
    native_نما.refresh_نرخ_denominator = 1000;

    إذا (داخلی->has_logical_اندازه) { // If xdg-output is present...
        إذا (native_نما.w != داخلی->logical.عرض || native_نما.h != داخلی->logical.ارتفاع) {
            // ...and the compositor scales the logical viewport...
            إذا (video->viewporter) {
                // ...and viewports are supported, calculate the true scale of the output.
                داخلی->scale_ضریب_2 = (مزدوج)native_نما.w / (مزدوج)داخلی->logical.عرض;
            } وإلا {
                // ...otherwise, the 'native' pixel values are a multiple of the logical screen size.
                داخلی->scale_ضریب_2 = داخلی->integer_scale_ضریب;
                داخلی->pixel.عرض = داخلی->logical.عرض * داخلی->integer_scale_ضریب;
                داخلی->pixel.ارتفاع = داخلی->logical.ارتفاع * داخلی->integer_scale_ضریب;
            }
        } وإلا {
            /* ...and the output viewport is not scaled in the global compositing
             * space, the output dimensions need to be divided by the scale factor.
             *
             * NOTE: This path is needed for old versions of GNOME that predate fractional scaling.
             */
            داخلی->scale_ضریب_2 = داخلی->integer_scale_ضریب;
            داخلی->logical.عرض /= داخلی->integer_scale_ضریب;
            داخلی->logical.ارتفاع /= داخلی->integer_scale_ضریب;
        }
    } وإلا {
        /* Calculate the points from the pixel values, if xdg-output isn't present.
         * Use the native mode pixel values since they are pre-transformed.
         */
        داخلی->scale_ضریب_2 = داخلی->integer_scale_ضریب;
        داخلی->logical.عرض = native_نما.w / داخلی->integer_scale_ضریب;
        داخلی->logical.ارتفاع = native_نما.h / داخلی->integer_scale_ضریب;
    }

    // The scaled desktop mode
    SDL_zero(desktop_نما);
    desktop_نما.format = SDL_PIXELFORMAT_XRGB8888;

    إذا (!video->scale_مقصد_display_enabled) {
        desktop_نما.w = داخلی->logical.عرض;
        desktop_نما.h = داخلی->logical.ارتفاع;
        desktop_نما.pixel_density = (عائم)داخلی->scale_ضریب_2;
    } وإلا {
        desktop_نما.w = native_نما.w;
        desktop_نما.h = native_نما.h;
        desktop_نما.pixel_density = 1.0f;
    }

    desktop_نما.refresh_نرخ_numerator = داخلی->refresh;
    desktop_نما.refresh_نرخ_denominator = 1000;

    إذا (داخلی->display > 0) {
        dpy = SDL_GetVideoDisplay(داخلی->display);
    } وإلا {
        dpy = &داخلی->placeholder;
    }

    إذا (video->scale_مقصد_display_enabled) {
        SDL_مجموعه_Display_Content_Scale(dpy, (عائم)داخلی->scale_ضریب_2);
    }

    // Set the desktop display mode.
    SDL_مجموعه_Desktop_Display_نما(dpy, &desktop_نما);

    // Expose the unscaled, native resolution if the scale is 1.0 or viewports are available...
    إذا (داخلی->scale_ضریب_2 == 1.0 || video->viewporter) {
        SDL_جمع_کن_Fullscreen_Display_نما(dpy, &native_نما);
        إذا (native_نما.w != desktop_نما.w ||
            native_نما.h != desktop_نما.h) {
            SDL_جمع_کن_Fullscreen_Display_نما(dpy, &desktop_نما);
        }
    } وإلا {
        // ...otherwise expose the integer scaled variants of the desktop resolution down to 1.
        desktop_نما.pixel_density = 1.0f;

        لكل (صحيح i = (صحيح)داخلی->scale_ضریب_2; i > 0; --i) {
            desktop_نما.w = داخلی->logical.عرض * i;
            desktop_نما.h = داخلی->logical.ارتفاع * i;
            SDL_جمع_کن_Fullscreen_Display_نما(dpy, &desktop_نما);
        }
    }

    // Add emulated modes if wp_viewporter is supported and mode emulation is enabled.
    إذا (video->viewporter && نما_emulation_enabled) {
        // The transformed display pixel width/height must be used here.
        جمع_کن_Emulated_Modes(داخلی, native_نما.w, native_نما.h);
    }

    إذا (داخلی->display == 0) {
        // First time getting display info, initialize the VideoDisplay
        إذا (داخلی->physical.عرض_mm >= داخلی->physical.ارتفاع_mm) {
            داخلی->placeholder.natural_orientation = SDL_ORIENTATION_LANDSCAPE;
        } وإلا {
            داخلی->placeholder.natural_orientation = SDL_ORIENTATION_PORTRAIT;
        }
        داخلی->placeholder.current_orientation = داخلی->orientation;
        داخلی->placeholder.داخلی = داخلی;

        داخلی->placeholder.props = SDL_CreateProperties();
        SDL_مجموعه_اشاره_گر_Property(داخلی->placeholder.props, SDL_PROP_DISPLAY_WAYLAND_WL_OUTPUT_اشاره_گر, داخلی->output);

        // During initialization, the displays will be added after enumeration is complete.
        إذا (!video->initializing) {
            إذا (video->wp_color_manager_v1) {
                Wayland_GetColorInfoForOutput(داخلی, false);
            }
            إذا (video->scale_مقصد_display_enabled) {
                Wayland_DeriveOutputPixelCoordinates(video);
            }

            داخلی->display = SDL_جمع_کن_Video_Display(&داخلی->placeholder, true);
            Wayland_Refresh_پنجره_Positions();

            SDL_free(داخلی->placeholder.name);
            SDL_zero(داخلی->placeholder);
        }
    } وإلا {
        SDL_SendDisplayEvent(dpy, SDL_EVENT_DISPLAY_ORIENTATION, داخلی->orientation, 0);

        إذا (داخلی->geometry_تغییریافته) {
            إذا (video->scale_مقصد_display_enabled) {
                Wayland_DeriveOutputPixelCoordinates(video);
            }

            SDL_SendDisplayEvent(dpy, SDL_EVENT_DISPLAY_MOVED, 0, 0);
            Wayland_Refresh_پنجره_Positions();
        }
    }

    داخلی->geometry_تغییریافته = false;
}

ساكن فراغ handle_wl_output_scale(فراغ *داده, بنية wl_output *output, int32_t ضریب)
{
    SDL_Display_داده *داخلی = (SDL_Display_داده *)داده;
    داخلی->integer_scale_ضریب = ضریب;
}

ساكن فراغ handle_wl_output_name(فراغ *داده, بنية wl_output *wl_output, ثابت حرف *name)
{
    SDL_Display_داده *داخلی = (SDL_Display_داده *)داده;

    SDL_free(داخلی->wl_output_name);
    داخلی->wl_output_name = SDL_strdup(name);
}

ساكن فراغ handle_wl_output_description(فراغ *داده, بنية wl_output *wl_output, ثابت حرف *description)
{
    SDL_Display_داده *داخلی = (SDL_Display_داده *)داده;

    إذا (داخلی->display == 0) {
        // The description, if available, supersedes the model name.
        SDL_free(داخلی->placeholder.name);
        داخلی->placeholder.name = SDL_strdup(description);
    }
}

ساكن ثابت بنية wl_output_listener output_listener = {
    handle_wl_output_geometry,   // Version 1
    handle_wl_output_نما,       // Version 1
    handle_wl_output_انجامشده,       // Version 2
    handle_wl_output_scale,      // Version 2
    handle_wl_output_name,       // Version 4
    handle_wl_output_description // Version 4
};

ساكن فراغ handle_output_image_description_تغییریافته(فراغ *داده,
                                                    بنية wp_color_management_output_v1 *wp_color_management_output_v1)
{
    SDL_Display_داده *display = (SDL_Display_داده *)داده;
    Wayland_GetColorInfoForOutput(display, false);
}

ساكن ثابت بنية wp_color_management_output_v1_listener wp_color_management_output_listener = {
    handle_output_image_description_تغییریافته
};

ساكن bool Wayland_جمع_کن_display(SDL_Video_داده *d, uint32_t id, uint32_t نسخه)
{
    بنية wl_output *output;
    SDL_Display_داده *داده;

    output = wl_registry_bind(d->registry, id, &wl_output_interface, نسخه);
    إذا (!output) {
        أرجع SDL_مجموعه_Error("Failed to retrieve output.");
    }
    داده = (SDL_Display_داده *)SDL_calloc(1, حجم(*داده));
    داده->videodata = d;
    داده->output = output;
    داده->registry_id = id;
    داده->scale_ضریب_2 = 1.0f;
    داده->integer_scale_ضریب = 1;

    wl_output_جمع_کن_listener(output, &output_listener, داده);
    SDL_WAYLAND_ثبات_output(output);

    // Keep a list of outputs for sorting and deferred protocol initialization.
    إذا (d->output_شمار == d->output_max) {
        d->output_max += 4;
        d->output_list = SDL_realloc(d->output_list, حجم(SDL_Display_داده *) * d->output_max);
    }
    d->output_list[d->output_شمار++] = داده;

    إذا (داده->videodata->xdg_output_manager) {
        داده->xdg_output = zxdg_output_manager_v1_get_xdg_output(داده->videodata->xdg_output_manager, output);
        zxdg_output_v1_جمع_کن_listener(داده->xdg_output, &xdg_output_listener, داده);
    }
    إذا (داده->videodata->wp_color_manager_v1) {
        داده->wp_color_management_output = wp_color_manager_v1_get_output(داده->videodata->wp_color_manager_v1, output);
        wp_color_management_output_v1_جمع_کن_listener(داده->wp_color_management_output, &wp_color_management_output_listener, داده);

        // If not initializing, this will be queried synchronously in wl_output.done.
        إذا (d->initializing) {
            Wayland_GetColorInfoForOutput(داده, true);
        }
    }
    أرجع true;
}

ساكن فراغ Wayland_free_display(SDL_VideoDisplay *display, bool send_event)
{
    إذا (display) {
        SDL_Display_داده *display_داده = display->داخلی;

        /* A preceding surface leave event is not guaranteed when an output is removed,
         * so ensure that no window continues to hold a reference to a removed output.
         */
        لكل (SDL_پنجره *پنجره = SDL_GetVideoDevice()->windows; پنجره; پنجره = پنجره->بعدی) {
            Wayland_Remove_Output_From_پنجره(پنجره->داخلی, display_داده);
        }

        SDL_free(display_داده->wl_output_name);

        إذا (display_داده->wp_color_management_output) {
            Wayland_FreeColorInfoState(display_داده->color_info_state);
            wp_color_management_output_v1_destroy(display_داده->wp_color_management_output);
        }

        إذا (display_داده->xdg_output) {
            zxdg_output_v1_destroy(display_داده->xdg_output);
        }

        إذا (wl_output_get_نسخه(display_داده->output) >= WL_OUTPUT_RELEASE_SINCE_نسخه) {
            wl_output_release(display_داده->output);
        } وإلا {
            wl_output_destroy(display_داده->output);
        }

        SDL_DelVideoDisplay(display->id, send_event);
    }
}

ساكن فراغ Wayland_FinalizeDisplays(SDL_Video_داده *vid)
{
    Wayland_مرتب_سازی_Outputs(vid);

    لكل(صحيح i = 0; i < vid->output_شمار; ++i) {
        SDL_Display_داده *d = vid->output_list[i];
        d->display = SDL_جمع_کن_Video_Display(&d->placeholder, false);
        SDL_free(d->placeholder.name);
        SDL_zero(d->placeholder);
    }
}

ساكن فراغ Wayland_init_xdg_output(SDL_Video_داده *d)
{
    لكل (صحيح i = 0; i < d->output_شمار; ++i) {
        SDL_Display_داده *disp = d->output_list[i];
        disp->xdg_output = zxdg_output_manager_v1_get_xdg_output(disp->videodata->xdg_output_manager, disp->output);
        zxdg_output_v1_جمع_کن_listener(disp->xdg_output, &xdg_output_listener, disp);
    }
}

ساكن فراغ Wayland_InitColorManager(SDL_Video_داده *d)
{
    لكل (صحيح i = 0; i < d->output_شمار; ++i) {
        SDL_Display_داده *disp = d->output_list[i];
        disp->wp_color_management_output = wp_color_manager_v1_get_output(disp->videodata->wp_color_manager_v1, disp->output);
        wp_color_management_output_v1_جمع_کن_listener(disp->wp_color_management_output, &wp_color_management_output_listener, disp);
        Wayland_GetColorInfoForOutput(disp, true);
    }
}

ساكن فراغ handle_xdg_session_created(فراغ *داده, بنية xdg_session_v1 *xdg_session_v1, ثابت حرف *id)
{
    SDL_مجموعه_String_Property(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, id);
}

ساكن فراغ handle_xdg_session_restored(فراغ *داده, بنية xdg_session_v1 *xdg_session_v1)
{
    // NOP
}

ساكن فراغ handle_xdg_session_replaced(فراغ *داده, بنية xdg_session_v1 *xdg_session_v1)
{
    SDL_VideoDevice *viddev = SDL_GetVideoDevice();
    SDL_Video_داده *viddata = داده;

    // Clean up all session objects, as they have become inert, and should be destroyed.
    SDL_مجموعه_String_Property(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, عدم);

    لكل (SDL_پنجره *w = viddev->windows; w; w = w->بعدی) {
        SDL_پنجره_داده *d = w->داخلی;

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

فراغ Wayland_CreateSession(SDL_Video_داده *viddata)
{
    إذا (!viddata->xdg_session_manager) {
        // Set the ID string to null if session management is not available.
        SDL_مجموعه_String_Property(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, عدم);
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
            xdg_session_v1_جمع_کن_listener(viddata->xdg_session, &xdg_session_listener, viddata);
        }
    }
}

ساكن فراغ Wayland_SessionDestroy(SDL_Video_داده *viddata)
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

ساكن فراغ handle_xdg_wm_پایه_ping(فراغ *داده, بنية xdg_wm_پایه *xdg, uint32_t serial)
{
    xdg_wm_پایه_pong(xdg, serial);
}

ساكن ثابت بنية xdg_wm_پایه_listener xdg_wm_پایه_listener_2 = {
    handle_xdg_wm_پایه_ping
};

#اگر_تعریف_شده HAVE_LIBDECOR_H
ساكن فراغ libdecor_error(بنية libdecor *context,
                           تعداد libdecor_error error,
                           ثابت حرف *پیام)
{
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "libdecor error (%d): %s", error, پیام);
}

ساكن بنية libdecor_interface libdecor_interface = {
    libdecor_error
};
#پایان_اگر

ساكن فراغ handle_registry_global(فراغ *داده, بنية wl_registry *registry, uint32_t id,
                                   ثابت حرف *interface, uint32_t نسخه)
{
    SDL_Video_داده *d = داده;

    إذا (SDL_strcmp(interface, wl_compositor_interface.name) == 0) {
        d->compositor = wl_registry_bind(d->registry, id, &wl_compositor_interface, SDL_min(SDL_WL_COMPOSITOR_نسخه, نسخه));
    } وإلا إذا (SDL_strcmp(interface, wl_subcompositor_interface.name) == 0) {
        d->subcompositor = wl_registry_bind(d->registry, id, &wl_subcompositor_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, wl_output_interface.name) == 0) {
        Wayland_جمع_کن_display(d, id, SDL_min(نسخه, SDL_WL_OUTPUT_نسخه));
    } وإلا إذا (SDL_strcmp(interface, wl_seat_interface.name) == 0) {
        بنية wl_seat *seat = wl_registry_bind(d->registry, id, &wl_seat_interface, SDL_min(SDL_WL_SEAT_نسخه, نسخه));
        Wayland_DisplayCreateSeat(d, seat, id);
    } وإلا إذا (SDL_strcmp(interface, xdg_wm_پایه_interface.name) == 0) {
        d->shell.xdg = wl_registry_bind(d->registry, id, &xdg_wm_پایه_interface, SDL_min(نسخه, 7));
        xdg_wm_پایه_جمع_کن_listener(d->shell.xdg, &xdg_wm_پایه_listener_2, عدم);
    } وإلا إذا (SDL_strcmp(interface, wl_shm_interface.name) == 0) {
        d->shm = wl_registry_bind(registry, id, &wl_shm_interface, SDL_min(SDL_WL_SHM_نسخه, نسخه));
    } وإلا إذا (SDL_strcmp(interface, zwp_relative_اشاره_گر_manager_v1_interface.name) == 0) {
        d->relative_اشاره_گر_manager = wl_registry_bind(d->registry, id, &zwp_relative_اشاره_گر_manager_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, zwp_اشاره_گر_constraints_v1_interface.name) == 0) {
        d->اشاره_گر_constraints = wl_registry_bind(d->registry, id, &zwp_اشاره_گر_constraints_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, zwp_keyboard_shortcuts_inhibit_manager_v1_interface.name) == 0) {
        d->کلید_inhibitor_manager = wl_registry_bind(d->registry, id, &zwp_keyboard_shortcuts_inhibit_manager_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, zwp_idle_inhibit_manager_v1_interface.name) == 0) {
        d->idle_inhibit_manager = wl_registry_bind(d->registry, id, &zwp_idle_inhibit_manager_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, xdg_activation_v1_interface.name) == 0) {
        d->activation_manager = wl_registry_bind(d->registry, id, &xdg_activation_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, zwp_متن_درون_داد_manager_v3_interface.name) == 0) {
        d->متن_درون_داد_manager = wl_registry_bind(d->registry, id, &zwp_متن_درون_داد_manager_v3_interface, 1);
        Wayland_Display_Init_متن_درون_داد_Manager(d, id);
    } وإلا إذا (SDL_strcmp(interface, wl_داده_device_manager_interface.name) == 0) {
        d->داده_device_manager = wl_registry_bind(d->registry, id, &wl_داده_device_manager_interface, SDL_min(3, نسخه));
        Wayland_Display_Init_داده_Device_Manager(d);
    } وإلا إذا (SDL_strcmp(interface, zwp_primary_selection_device_manager_v1_interface.name) == 0) {
        d->primary_selection_device_manager = wl_registry_bind(d->registry, id, &zwp_primary_selection_device_manager_v1_interface, 1);
        Wayland_DisplayInitPrimarySelectionDeviceManager(d);
    } وإلا إذا (SDL_strcmp(interface, zxdg_decoration_manager_v1_interface.name) == 0) {
        d->decoration_manager = wl_registry_bind(d->registry, id, &zxdg_decoration_manager_v1_interface, SDL_min(2, نسخه));
    } وإلا إذا (SDL_strcmp(interface, zwp_tablet_manager_v2_interface.name) == 0) {
        d->tablet_manager = wl_registry_bind(d->registry, id, &zwp_tablet_manager_v2_interface, 1);
        Wayland_DisplayInitTabletManager(d);
    } وإلا إذا (SDL_strcmp(interface, zxdg_output_manager_v1_interface.name) == 0) {
        نسخه = SDL_min(نسخه, 3); // Versions 1 through 3 are supported.
        d->xdg_output_manager = wl_registry_bind(d->registry, id, &zxdg_output_manager_v1_interface, نسخه);
        Wayland_init_xdg_output(d);
    } وإلا إذا (SDL_strcmp(interface, wp_viewporter_interface.name) == 0) {
        d->viewporter = wl_registry_bind(d->registry, id, &wp_viewporter_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, wp_fractional_scale_manager_v1_interface.name) == 0) {
        d->fractional_scale_manager = wl_registry_bind(d->registry, id, &wp_fractional_scale_manager_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, zwp_درون_داد_timestamps_manager_v1_interface.name) == 0) {
        d->درون_داد_timestamps_manager = wl_registry_bind(d->registry, id, &zwp_درون_داد_timestamps_manager_v1_interface, 1);
        Wayland_Display_Init_درون_داد_Timestamp_Manager(d);
    } وإلا إذا (SDL_strcmp(interface, wp_cursor_shape_manager_v1_interface.name) == 0) {
        d->cursor_shape_manager = wl_registry_bind(d->registry, id, &wp_cursor_shape_manager_v1_interface, SDL_min(نسخه, 2));
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
        d->wp_color_manager_v1 = wl_registry_bind(d->registry, id, &wp_color_manager_v1_interface, SDL_min(نسخه, 2));
        Wayland_InitColorManager(d);
    } وإلا إذا (SDL_strcmp(interface, wp_اشاره_گر_warp_v1_interface.name) == 0) {
        d->wp_اشاره_گر_warp_v1 = wl_registry_bind(d->registry, id, &wp_اشاره_گر_warp_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, zwp_اشاره_گر_gestures_v1_interface.name) == 0) {
        d->zwp_اشاره_گر_gestures = wl_registry_bind(d->registry, id, &zwp_اشاره_گر_gestures_v1_interface, SDL_min(نسخه, 3));
        Wayland_Display_Init_اشاره_گر_Gesture_Manager(d);
    } وإلا إذا (SDL_strcmp(interface, wp_single_pixel_میانگیر_manager_v1_interface.name) == 0) {
        d->single_pixel_میانگیر_manager = wl_registry_bind(d->registry, id, &wp_single_pixel_میانگیر_manager_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, xdg_session_manager_v1_interface.name) == 0) {
        d->xdg_session_manager = wl_registry_bind(d->registry, id, &xdg_session_manager_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, xdg_toplevel_برچسب_manager_v1_interface.name) == 0) {
        d->xdg_toplevel_برچسب_manager = wl_registry_bind(d->registry, id, &xdg_toplevel_برچسب_manager_v1_interface, 1);
    }
#اگر_تعریف_شده SDL_WL_FIXES_نسخه
    وإلا إذا (SDL_strcmp(interface, wl_fixes_interface.name) == 0) {
        d->wl_fixes = wl_registry_bind(d->registry, id, &wl_fixes_interface, SDL_min(SDL_WL_FIXES_نسخه, نسخه));
    }
#پایان_اگر
}

ساكن فراغ handle_registry_remove_global(فراغ *داده, بنية wl_registry *registry, uint32_t id)
{
    SDL_Video_داده *d = داده;

    // We don't get an interface, just an ID, so check outputs and seats.
    لكل (صحيح i = 0; i < d->output_شمار; ++i) {
        SDL_Display_داده *disp = d->output_list[i];
        إذا (disp->registry_id == id) {
            Wayland_free_display(SDL_GetVideoDisplay(disp->display), true);

            إذا (i < d->output_شمار) {
                SDL_memmove(&d->output_list[i], &d->output_list[i + 1], حجم(SDL_Display_داده *) * (d->output_شمار - i - 1));
            }

            d->output_شمار--;
            اذهب ack_remove;
        }
    }

    SDL_WaylandSeat *seat, *موقت;
    wl_list_for_each_امن (seat, موقت, &d->seat_list, link) {
        إذا (seat->registry_id == id) {
            Wayland_SeatDestroy(seat, false);
            اذهب ack_remove;
        }
    }

ack_remove:
    إذا (d->wl_fixes && wl_fixes_get_نسخه(d->wl_fixes) >= WL_FIXES_ACK_GLOBAL_REMOVE_SINCE_نسخه) {
        wl_fixes_ack_global_remove(d->wl_fixes, registry, id);
    }
}

ساكن ثابت بنية wl_registry_listener registry_listener = {
    handle_registry_global,
    handle_registry_remove_global
};

#اگر_تعریف_شده HAVE_LIBDECOR_H
ساكن bool should_use_libdecor(SDL_Video_داده *داده, bool ignore_xdg)
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

    إذا (داده->decoration_manager) {
        أرجع false;
    }

    أرجع true;
}

ساكن فراغ LibdecorNew(SDL_Video_داده *داده)
{
    داده->shell.libdecor = libdecor_new(داده->display, &libdecor_interface);
}

// Called in another thread, but the UI thread is blocked in SDL_WaitThread
// during that time, so it should be OK to dereference data without locks
ساكن صحيح SDLCALL Libdecor_New_درون_Thread(فراغ *داده)
{
    LibdecorNew((SDL_Video_داده *)داده);
    أرجع 0;
}
#پایان_اگر

#اگر_تعریف_شده HAVE_GETRESUID
#تعریف_کن SDL_getresuid getresuid
#وإلا
// Non-POSIX, but Linux and some BSDs have it.
// To reduce the number of code paths, if getresuid() isn't available at
// compile-time, we behave as though it existed but failed at runtime.
ساكن مضمن صحيح SDL_getresuid(uid_t *ruid, uid_t *euid, uid_t *suid) {
    errno = ENOSYS;
    أرجع -1;
}
#پایان_اگر

#اگر_تعریف_شده HAVE_GETRESGID
#تعریف_کن SDL_getresgid getresgid
#وإلا
// Same as getresuid() but for the primary group
ساكن مضمن صحيح SDL_getresgid(gid_t *rgid, gid_t *egid, gid_t *sgid) {
    errno = ENOSYS;
    أرجع -1;
}
#پایان_اگر

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

bool Wayland_بارگیری_Libdecor(SDL_Video_داده *داده, bool ignore_xdg)
{
#اگر_تعریف_شده HAVE_LIBDECOR_H
    إذا (داده->shell.libdecor != عدم) {
        أرجع true; // Already loaded!
    }
    إذا (should_use_libdecor(داده, ignore_xdg)) {
        إذا (CanUseGtk()) {
            LibdecorNew(داده);
        } وإلا {
            // Intentionally initialize libdecor in a non-main thread
            // so that it will not use its GTK plugin, but instead will
            // fall back to the Cairo or dummy plugin
            SDL_Thread *thread = SDL_CreateThread(Libdecor_New_درون_Thread, "SDL_LibdecorNew", (فراغ *)داده);
            // Note that the other thread now "owns" data until we have
            // waited for it, so don't touch data here
            SDL_WaitThread(thread, عدم);
        }

        أرجع داده->shell.libdecor != عدم;
    }
#پایان_اگر
    أرجع false;
}

bool Wayland_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_داده *داده = _this->داخلی;

    داده->event_thread_context = Wayland_CreateEventThread(داده, "SDL Event Thread Queue");
    إذا (!داده->event_thread_context) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Failed to create event thread context");
    }

    داده->کار_thread_context = Wayland_Create_کار_Thread();
    إذا (!داده->کار_thread_context) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Failed to create job thread context");
    }

    داده->xkb_context = WAYLAND_xkb_context_new(0);
    إذا (!داده->xkb_context) {
        أرجع SDL_مجموعه_Error("Failed to create XKB context");
    }

    داده->registry = wl_display_get_registry(داده->display);
    إذا (!داده->registry) {
        أرجع SDL_مجموعه_Error("Failed to get the Wayland registry");
    }

    wl_registry_جمع_کن_listener(داده->registry, &registry_listener, داده);

    // First roundtrip to receive all registry objects.
    WAYLAND_wl_display_roundtrip(داده->display);

    // Require viewports and xdg-output for display scaling.
    إذا (داده->scale_مقصد_display_enabled) {
        إذا (!داده->viewporter) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Display scaling requires the missing 'wp_viewporter' protocol: disabling");
            داده->scale_مقصد_display_enabled = false;
        }
        إذا (!داده->xdg_output_manager) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Display scaling requires the missing 'zxdg_output_manager_v1' protocol: disabling");
            داده->scale_مقصد_display_enabled = false;
        }
    }

    // Now that we have all the protocols, load libdecor if applicable
    Wayland_بارگیری_Libdecor(داده, false);

    // Second roundtrip to receive all output events.
    WAYLAND_wl_display_roundtrip(داده->display);

    Wayland_FinalizeDisplays(داده);

    Wayland_InitMouse(داده);
    Wayland_InitKeyboard(_this);

    إذا (داده->primary_selection_device_manager) {
        _this->مجموعه_Primary_Selection_متن = Wayland_مجموعه_Primary_Selection_متن;
        _this->Get_Primary_Selection_متن = Wayland_Get_Primary_Selection_متن;
        _this->Has_Primary_Selection_متن = Wayland_Has_Primary_Selection_متن;
    }

    داده->initializing = false;

    أرجع true;
}

ساكن bool Wayland_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    SDL_Video_داده *viddata = _this->داخلی;
    SDL_Display_داده *داخلی = display->داخلی;

    إذا (!viddata->scale_مقصد_display_enabled) {
        rect->x = داخلی->logical.x;
        rect->y = داخلی->logical.y;
    } وإلا {
        rect->x = داخلی->pixel.x;
        rect->y = داخلی->pixel.y;
    }

    // When an emulated, exclusive fullscreen window has focus, treat the mode dimensions as the display bounds.
    إذا (display->fullscreen_پنجره &&
        display->fullscreen_پنجره->fullscreen_exclusive &&
        display->fullscreen_پنجره->داخلی->فعال &&
        display->fullscreen_پنجره->current_fullscreen_نما.w != 0 &&
        display->fullscreen_پنجره->current_fullscreen_نما.h != 0) {
        rect->w = display->fullscreen_پنجره->current_fullscreen_نما.w;
        rect->h = display->fullscreen_پنجره->current_fullscreen_نما.h;
    } وإلا {
        إذا (!viddata->scale_مقصد_display_enabled) {
            rect->w = display->current_نما->w;
            rect->h = display->current_نما->h;
        } وإلا إذا (داخلی->transform & WL_OUTPUT_TRANSFORM_90) {
            rect->w = داخلی->pixel.ارتفاع;
            rect->h = داخلی->pixel.عرض;
        } وإلا {
            rect->w = داخلی->pixel.عرض;
            rect->h = داخلی->pixel.ارتفاع;
        }
    }
    أرجع true;
}

ساكن فراغ Wayland_VideoCleanup(SDL_VideoDevice *_this)
{
    SDL_Video_داده *داده = _this->داخلی;
    SDL_WaylandSeat *seat, *tmp;

    Wayland_SessionDestroy(داده);

    لكل (صحيح i = _this->رقم_displays - 1; i >= 0; --i) {
        SDL_VideoDisplay *display = _this->displays[i];
        Wayland_free_display(display, false);
    }
    SDL_free(داده->output_list);

    wl_list_for_each_امن (seat, tmp, &داده->seat_list, link) {
        Wayland_SeatDestroy(seat, true);
    }

    Wayland_FiniMouse(داده);
    Wayland_QuitKeyboard(_this);

    Wayland_DestroyEventThread(داده->event_thread_context);
    داده->event_thread_context = عدم;

    Wayland_Destroy_کار_Thread(داده->کار_thread_context);
    داده->کار_thread_context = عدم;

    إذا (داده->اشاره_گر_constraints) {
        zwp_اشاره_گر_constraints_v1_destroy(داده->اشاره_گر_constraints);
        داده->اشاره_گر_constraints = عدم;
    }

    إذا (داده->relative_اشاره_گر_manager) {
        zwp_relative_اشاره_گر_manager_v1_destroy(داده->relative_اشاره_گر_manager);
        داده->relative_اشاره_گر_manager = عدم;
    }

    إذا (داده->activation_manager) {
        xdg_activation_v1_destroy(داده->activation_manager);
        داده->activation_manager = عدم;
    }

    إذا (داده->idle_inhibit_manager) {
        zwp_idle_inhibit_manager_v1_destroy(داده->idle_inhibit_manager);
        داده->idle_inhibit_manager = عدم;
    }

    إذا (داده->کلید_inhibitor_manager) {
        zwp_keyboard_shortcuts_inhibit_manager_v1_destroy(داده->کلید_inhibitor_manager);
        داده->کلید_inhibitor_manager = عدم;
    }

    إذا (داده->متن_درون_داد_manager) {
        zwp_متن_درون_داد_manager_v3_destroy(داده->متن_درون_داد_manager);
        داده->متن_درون_داد_manager = عدم;
    }

    إذا (داده->xkb_context) {
        WAYLAND_xkb_context_unref(داده->xkb_context);
        داده->xkb_context = عدم;
    }

    إذا (داده->tablet_manager) {
        zwp_tablet_manager_v2_destroy((بنية zwp_tablet_manager_v2 *)داده->tablet_manager);
        داده->tablet_manager = عدم;
    }

    إذا (داده->داده_device_manager) {
        wl_داده_device_manager_destroy(داده->داده_device_manager);
        داده->داده_device_manager = عدم;
    }

    إذا (داده->shm) {
        إذا (wl_shm_get_نسخه(داده->shm) >= WL_SHM_RELEASE_SINCE_نسخه) {
            wl_shm_release(داده->shm);
        } وإلا {
            wl_shm_destroy(داده->shm);
        }
        داده->shm = عدم;
    }

    إذا (داده->shell.xdg) {
        xdg_wm_پایه_destroy(داده->shell.xdg);
        داده->shell.xdg = عدم;
    }

    إذا (داده->decoration_manager) {
        zxdg_decoration_manager_v1_destroy(داده->decoration_manager);
        داده->decoration_manager = عدم;
    }

    إذا (داده->xdg_output_manager) {
        zxdg_output_manager_v1_destroy(داده->xdg_output_manager);
        داده->xdg_output_manager = عدم;
    }

    إذا (داده->viewporter) {
        wp_viewporter_destroy(داده->viewporter);
        داده->viewporter = عدم;
    }

    إذا (داده->primary_selection_device_manager) {
        zwp_primary_selection_device_manager_v1_destroy(داده->primary_selection_device_manager);
        داده->primary_selection_device_manager = عدم;
    }

    إذا (داده->fractional_scale_manager) {
        wp_fractional_scale_manager_v1_destroy(داده->fractional_scale_manager);
        داده->fractional_scale_manager = عدم;
    }

    إذا (داده->درون_داد_timestamps_manager) {
        zwp_درون_داد_timestamps_manager_v1_destroy(داده->درون_داد_timestamps_manager);
        داده->درون_داد_timestamps_manager = عدم;
    }

    إذا (داده->cursor_shape_manager) {
        wp_cursor_shape_manager_v1_destroy(داده->cursor_shape_manager);
        داده->cursor_shape_manager = عدم;
    }

    إذا (داده->zxdg_exporter_v2) {
        zxdg_exporter_v2_destroy(داده->zxdg_exporter_v2);
        داده->zxdg_exporter_v2 = عدم;
    }

    إذا (داده->xdg_wm_dialog_v1) {
        xdg_wm_dialog_v1_destroy(داده->xdg_wm_dialog_v1);
        داده->xdg_wm_dialog_v1 = عدم;
    }

    إذا (داده->wp_alpha_modifier_v1) {
        wp_alpha_modifier_v1_destroy(داده->wp_alpha_modifier_v1);
        داده->wp_alpha_modifier_v1 = عدم;
    }

    إذا (داده->xdg_toplevel_icon_manager_v1) {
        xdg_toplevel_icon_manager_v1_destroy(داده->xdg_toplevel_icon_manager_v1);
        داده->xdg_toplevel_icon_manager_v1 = عدم;
    }

    إذا (داده->frog_color_management_factory_v1) {
        frog_color_management_factory_v1_destroy(داده->frog_color_management_factory_v1);
        داده->frog_color_management_factory_v1 = عدم;
    }

    إذا (داده->wp_color_manager_v1) {
        wp_color_manager_v1_destroy(داده->wp_color_manager_v1);
        داده->wp_color_manager_v1 = عدم;
    }

    إذا (داده->wp_اشاره_گر_warp_v1) {
        wp_اشاره_گر_warp_v1_destroy(داده->wp_اشاره_گر_warp_v1);
        داده->wp_اشاره_گر_warp_v1 = عدم;
    }

    إذا (داده->zwp_اشاره_گر_gestures) {
        إذا (zwp_اشاره_گر_gestures_v1_get_نسخه(داده->zwp_اشاره_گر_gestures) >= ZWP_اشاره_گر_GESTURES_V1_RELEASE_SINCE_نسخه) {
            zwp_اشاره_گر_gestures_v1_release(داده->zwp_اشاره_گر_gestures);
        } وإلا {
            zwp_اشاره_گر_gestures_v1_destroy(داده->zwp_اشاره_گر_gestures);
        }
        داده->zwp_اشاره_گر_gestures = عدم;
    }

    إذا (داده->single_pixel_میانگیر_manager) {
        wp_single_pixel_میانگیر_manager_v1_destroy(داده->single_pixel_میانگیر_manager);
        داده->single_pixel_میانگیر_manager = عدم;
    }

    إذا (داده->xdg_session_manager) {
        xdg_session_manager_v1_destroy(داده->xdg_session_manager);
        داده->xdg_session_manager = عدم;
    }

    إذا (داده->xdg_toplevel_برچسب_manager) {
        xdg_toplevel_برچسب_manager_v1_destroy(داده->xdg_toplevel_برچسب_manager);
        داده->xdg_toplevel_برچسب_manager = عدم;
    }

    إذا (داده->subcompositor) {
        wl_subcompositor_destroy(داده->subcompositor);
        داده->subcompositor = عدم;
    }

    إذا (داده->compositor) {
        wl_compositor_destroy(داده->compositor);
        داده->compositor = عدم;
    }

    إذا (داده->registry) {
        إذا (داده->wl_fixes) {
            wl_fixes_destroy_registry(داده->wl_fixes, داده->registry);
            wl_fixes_destroy(داده->wl_fixes);
            داده->wl_fixes = عدم;
        }
        wl_registry_destroy(داده->registry);
        داده->registry = عدم;
    }
}

ساكن bool Wayland_VideoReconnect(SDL_VideoDevice *_this)
{
#إذا 0 // TODO RECONNECT: Uncomment all when https://invent.kde.org/plasma/kwin/-/wikis/Restarting is completed
    SDL_Video_داده *داده = _this->داخلی;

    SDL_پنجره *پنجره = عدم;

    SDL_GLContext current_ctx = SDL_GL_GetCurrentContext();
    SDL_پنجره *current_پنجره = SDL_GL_Get_Current_پنجره();

    SDL_GL_MakeCurrent(عدم, عدم);
    Wayland_VideoCleanup(_this);

    SDL_ResetKeyboard();
    SDL_ResetMouse();
    إذا (WAYLAND_wl_display_reconnect(داده->display) < 0) {
        أرجع false;
    }

    Wayland_VideoInit(_this);

    پنجره = _this->windows;
    طالما (پنجره) {
        /* We're going to cheat _just_ for a second and strip the OpenGL flag.
         * The Wayland driver actually forces it in CreateWindow, and
         * RecreateWindow does a bunch of unloading/loading of libGL, so just
         * strip the flag so RecreateWindow doesn't mess with the GL context,
         * and CreateWindow will add it right back!
         * -flibit
         */
        پنجره->flags &= ~SDL_پنجره_OPENGL;

        SDL_Recreate_پنجره(پنجره, پنجره->flags);
        پنجره = پنجره->بعدی;
    }

    Wayland_RecreateCursors();

    إذا (current_پنجره && current_ctx) {
        SDL_GL_MakeCurrent (current_پنجره, current_ctx);
    }
    أرجع true;
#وإلا
    أرجع false;
#پایان_اگر // 0
}

bool Wayland_HandleDisplayDisconnected(SDL_VideoDevice *_this)
{
    SDL_Video_داده *video_داده = _this->داخلی;

    /* Something has failed with the Wayland connection -- for example,
     * the compositor may have shut down and closed its end of the socket,
     * or there is a library-specific error.
     *
     * Try to recover once, then quit.
     */
    إذا (video_داده->display_disconnected) {
        أرجع false;
    }

    إذا (Wayland_VideoReconnect(_this)) {
        أرجع true;
    }

    video_داده->display_disconnected = true;
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Wayland display connection closed by server (fatal)");

    // Only send a single quit message, as application shutdown might call SDL_PumpEvents().
    SDL_SendQuit();

    أرجع false;
}

فراغ Wayland_VideoQuit(SDL_VideoDevice *_this)
{
    Wayland_VideoCleanup(_this);

#اگر_تعریف_شده HAVE_LIBDECOR_H
    SDL_Video_داده *داده = _this->داخلی;
    إذا (داده->shell.libdecor) {
        libdecor_unref(داده->shell.libdecor);
        داده->shell.libdecor = عدم;
    }
#پایان_اگر
}

#پایان_اگر // SDL_VIDEO_DRIVER_WAYLAND
