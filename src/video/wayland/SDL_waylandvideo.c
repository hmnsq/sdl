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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_WAYLAND

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

#جيڪڏهن_وصف_ٿيل HAVE_LIBDECOR_H
#ضمن <libdecor.h>
#جيڪڏهن_پورو

#وصف_ڪريو WAYLANDVID_DRIVER_NAME "wayland"

// Clamp core protocol versions on older versions of libwayland.
#إذا SDL_WAYLAND_CHECK_نسخو(1, 22, 0)
#وصف_ڪريو SDL_WL_COMPOSITOR_نسخو 6
#وإلا
#وصف_ڪريو SDL_WL_COMPOSITOR_نسخو 4
#جيڪڏهن_پورو

#إذا SDL_WAYLAND_CHECK_نسخو(1, 26, 0)
#وصف_ڪريو SDL_WL_SEAT_نسخو 11
#وإلاإذا SDL_WAYLAND_CHECK_نسخو(1, 24, 0)
#وصف_ڪريو SDL_WL_SEAT_نسخو 10
#وإلاإذا SDL_WAYLAND_CHECK_نسخو(1, 22, 0)
#وصف_ڪريو SDL_WL_SEAT_نسخو 9
#وإلاإذا SDL_WAYLAND_CHECK_نسخو(1, 21, 0)
#وصف_ڪريو SDL_WL_SEAT_نسخو 8
#وإلا
#وصف_ڪريو SDL_WL_SEAT_نسخو 5
#جيڪڏهن_پورو

#إذا SDL_WAYLAND_CHECK_نسخو(1, 20, 0)
#وصف_ڪريو SDL_WL_OUTPUT_نسخو 4
#وإلا
#وصف_ڪريو SDL_WL_OUTPUT_نسخو 3
#جيڪڏهن_پورو

#إذا SDL_WAYLAND_CHECK_نسخو(1, 24, 0)
#وصف_ڪريو SDL_WL_SHM_نسخو 2
#وإلا
#وصف_ڪريو SDL_WL_SHM_نسخو 1
#جيڪڏهن_پورو

// The SDL libwayland-client minimum is 1.18, which supports version 3.
#وصف_ڪريو SDL_WL_معلومات_DEVICE_نسخو 3

// wl_fixes was introduced in 1.24.0
#إذا SDL_WAYLAND_CHECK_نسخو(1, 26, 0)
#وصف_ڪريو SDL_WL_FIXES_نسخو 2
#وإلاإذا SDL_WAYLAND_CHECK_نسخو(1, 24, 0)
#وصف_ڪريو SDL_WL_FIXES_نسخو 1
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل SDL_USE_LIBDBUS
#ضمن "../../core/linux/SDL_dbus.h"

#وصف_ڪريو DISPLAY_INFO_ڳنڍ   "org.gnome.Mutter.DisplayConfig"
#وصف_ڪريو DISPLAY_INFO_رستو   "/org/gnome/Mutter/DisplayConfig"
#وصف_ڪريو DISPLAY_INFO_طريقو "GetCurrentState"
#جيڪڏهن_پورو

/* GNOME doesn't expose displays in any particular order, but we can find the
 * primary display and its logical coordinates via a DBus method.
 */
ساكن bool Wayland_GetGNOMEPrimaryDisplayCoordinates(صحيح *x, صحيح *y)
{
#جيڪڏهن_وصف_ٿيل SDL_USE_LIBDBUS
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    إذا (dbus == عدم) {
        أرجع false;
    }
    DBus_پيغام *جواب = عدم;
    DBus_پيغام_Iter iter[3];
    DBus_پيغام *نياپو = dbus->پيغام_new_طريقو_call(DISPLAY_INFO_ڳنڍ,
                                                     DISPLAY_INFO_رستو,
                                                     DISPLAY_INFO_ڳنڍ,
                                                     DISPLAY_INFO_طريقو);

    إذا (نياپو) {
        جواب = dbus->connection_send_with_جواب_and_بلاڪ(dbus->session_conn, نياپو, DBUS_TIMEOUT_USE_DEFAULT, عدم);
        dbus->پيغام_unref(نياپو);
    }

    إذا (جواب) {
        // Serial (don't care)
        dbus->پيغام_iter_init(جواب, &iter[0]);
        إذا (dbus->پيغام_iter_get_arg_type(&iter[0]) != DBUS_TYPE_UINT32) {
            اذهب error;
        }

        // Physical monitor array (don't care)
        dbus->پيغام_iter_ايندڙ(&iter[0]);
        إذا (dbus->پيغام_iter_get_arg_type(&iter[0]) != DBUS_TYPE_ARRAY) {
            اذهب error;
        }

        // Logical monitor array of structs
        dbus->پيغام_iter_ايندڙ(&iter[0]);
        إذا (dbus->پيغام_iter_get_arg_type(&iter[0]) != DBUS_TYPE_ARRAY) {
            اذهب error;
        }

        // First logical monitor struct
        dbus->پيغام_iter_recurse(&iter[0], &iter[1]);
        إذا (dbus->پيغام_iter_get_arg_type(&iter[1]) != DBUS_TYPE_STRUCT) {
            اذهب error;
        }

        افعل {
            صحيح logical_x, logical_y;
            dbus_bool_t primary;

            // Logical X
            dbus->پيغام_iter_recurse(&iter[1], &iter[2]);
            إذا (dbus->پيغام_iter_get_arg_type(&iter[2]) != DBUS_TYPE_INT32) {
                اذهب error;
            }
            dbus->پيغام_iter_get_basic(&iter[2], &logical_x);

            // Logical Y
            dbus->پيغام_iter_ايندڙ(&iter[2]);
            إذا (dbus->پيغام_iter_get_arg_type(&iter[2]) != DBUS_TYPE_INT32) {
                اذهب error;
            }
            dbus->پيغام_iter_get_basic(&iter[2], &logical_y);

            // Scale (don't care)
            dbus->پيغام_iter_ايندڙ(&iter[2]);
            إذا (dbus->پيغام_iter_get_arg_type(&iter[2]) != DBUS_TYPE_DOUBLE) {
                اذهب error;
            }

            // Transform (don't care)
            dbus->پيغام_iter_ايندڙ(&iter[2]);
            إذا (dbus->پيغام_iter_get_arg_type(&iter[2]) != DBUS_TYPE_UINT32) {
                اذهب error;
            }

            // Primary display boolean
            dbus->پيغام_iter_ايندڙ(&iter[2]);
            إذا (dbus->پيغام_iter_get_arg_type(&iter[2]) != DBUS_TYPE_BOOLEAN) {
                اذهب error;
            }
            dbus->پيغام_iter_get_basic(&iter[2], &primary);

            إذا (primary) {
                *x = logical_x;
                *y = logical_y;

                // We found the primary display: success.
                dbus->پيغام_unref(جواب);
                أرجع true;
            }
        } طالما (dbus->پيغام_iter_ايندڙ(&iter[1]));
    }

error:
    إذا (جواب) {
        dbus->پيغام_unref(جواب);
    }
#جيڪڏهن_پورو
    أرجع false;
}

// Sort the list of displays into a deterministic order
ساكن صحيح SDLCALL Wayland_DisplayPositionCompare(ثابت فراغ *a, ثابت فراغ *b)
{
    ثابت SDL_Display_معلومات *da = *(SDL_Display_معلومات **)a;
    ثابت SDL_Display_معلومات *db = *(SDL_Display_معلومات **)b;
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
ساكن صحيح Wayland_GetPrimaryDisplay(SDL_Video_معلومات *vid)
{
    ساكن ثابت صحيح REFRESH_DELTA = 4000;

    // Query the DBus interface to see if the coordinates of the primary display are exposed.
    صحيح x, y;
    إذا (Wayland_GetGNOMEPrimaryDisplayCoordinates(&x, &y)) {
        لكل (صحيح i = 0; i < vid->output_ڳڻپ; ++i) {
            إذا (vid->output_list[i]->logical.x == x && vid->output_list[i]->logical.y == y) {
                أرجع i;
            }
        }
    }

    // Otherwise, choose the 'best' display.
    صحيح بهترين_ويڪر = 0;
    صحيح بهترين_اوچائي = 0;
    مزدوج بهترين_scale = 0.0;
    عائم بهترين_headroom = 0.0f;
    صحيح بهترين_refresh = 0;
    bool بهترين_is_landscape = false;
    صحيح بهترين_اشاريو = 0;

    لكل (صحيح i = 0; i < vid->output_ڳڻپ; ++i) {
        ثابت SDL_Display_معلومات *d = vid->output_list[i];
        ثابت bool is_landscape = d->orientation != SDL_ORIENTATION_PORTRAIT && d->orientation != SDL_ORIENTATION_PORTRAIT_FLIPPED;
        bool have_new_بهترين = false;

        إذا (!بهترين_is_landscape && is_landscape) { // Favor landscape over portrait displays.
            have_new_بهترين = true;
        } وإلا إذا (!بهترين_is_landscape || is_landscape) { // Ignore portrait displays if a landscape was already found.
            إذا (d->pixel.ويڪر > بهترين_ويڪر || d->pixel.اوچائي > بهترين_اوچائي) {
                have_new_بهترين = true;
            } وإلا إذا (d->pixel.ويڪر == بهترين_ويڪر && d->pixel.اوچائي == بهترين_اوچائي) {
                إذا (d->HDR.HDR_headroom > بهترين_headroom) { // Favor a higher HDR luminance range
                    have_new_بهترين = true;
                } وإلا إذا (d->HDR.HDR_headroom == بهترين_headroom) {
                    إذا (d->refresh - بهترين_refresh > REFRESH_DELTA) { // Favor a higher refresh rate, but ignore small differences (e.g. 59.97 vs 60.1)
                        have_new_بهترين = true;
                    } وإلا إذا (d->scale_ضرب_ڪندڙ_2 < بهترين_scale && SDL_abs(d->refresh - بهترين_refresh) <= REFRESH_DELTA) {
                        // Prefer a lower scale display if the difference in refresh rate is small.
                        have_new_بهترين = true;
                    }
                }
            }
        }

        إذا (have_new_بهترين) {
            بهترين_ويڪر = d->pixel.ويڪر;
            بهترين_اوچائي = d->pixel.اوچائي;
            بهترين_scale = d->scale_ضرب_ڪندڙ_2;
            بهترين_headroom = d->HDR.HDR_headroom;
            بهترين_refresh = d->refresh;
            بهترين_is_landscape = is_landscape;
            بهترين_اشاريو = i;
        }
    }

    أرجع بهترين_اشاريو;
}

ساكن فراغ Wayland_ترتيب_ڏيو_Outputs_By_ترجيح_Hint(SDL_Video_معلومات *vid)
{
    ثابت حرف *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_ترجيح);

    إذا (name_hint) {
        حرف *saveptr;
        حرف *str = SDL_strdup(name_hint);
        SDL_Display_معلومات **sorted_list = SDL_malloc(حجم(SDL_Display_معلومات *) * vid->output_ڳڻپ);

        إذا (str && sorted_list) {
            صحيح sorted_اشاريو = 0;

            // Sort the requested displays to the front of the list.
            ثابت حرف *token = SDL_strtok_r(str, ",", &saveptr);
            طالما (token) {
                لكل (صحيح i = 0; i < vid->output_ڳڻپ; ++i) {
                    SDL_Display_معلومات *d = vid->output_list[i];
                    إذا (d && d->wl_output_name && SDL_strcmp(token, d->wl_output_name) == 0) {
                        sorted_list[sorted_اشاريو++] = d;
                        vid->output_list[i] = عدم;
                        اكسر;
                    }
                }

                token = SDL_strtok_r(عدم, ",", &saveptr);
            }

            // Append the remaining outputs to the end of the list.
            لكل (صحيح i = 0; i < vid->output_ڳڻپ; ++i) {
                إذا (vid->output_list[i]) {
                    sorted_list[sorted_اشاريو++] = vid->output_list[i];
                }
            }

            // Copy the sorted list to the output list.
            SDL_memcpy(vid->output_list, sorted_list, حجم(SDL_Display_معلومات *) * vid->output_ڳڻپ);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

ساكن فراغ Wayland_DeriveOutputPixelCoordinates(SDL_Video_معلومات *vid)
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
    لكل ( صحيح i = 0; i < vid->output_ڳڻپ; ++i) {
        SDL_Display_معلومات *d = vid->output_list[i];
        d->pixel.x = d->logical.x;
        d->pixel.y = d->logical.y;
    }

    لكل (صحيح i = 0; i < vid->output_ڳڻپ; ++i) {
        SDL_Display_معلومات *d1 = vid->output_list[i];
        إذا (d1->logical.ويڪر != d1->pixel.ويڪر || d1->logical.اوچائي != d1->pixel.اوچائي) {
            ثابت صحيح x_adj = d1->pixel.ويڪر - d1->logical.ويڪر;
            ثابت صحيح y_adj = d1->pixel.اوچائي - d1->logical.اوچائي;

            // Don't adjust for scale values less than 1.0.
            إذا (x_adj > 0 && y_adj > 0) {
                لكل (صحيح j = 0; j < vid->output_ڳڻپ; ++j) {
                    SDL_Display_معلومات *d2 = vid->output_list[j];
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

ساكن فراغ Wayland_ترتيب_ڏيو_Outputs(SDL_Video_معلومات *vid)
{
    // Sort by position or connector name, so the order of outputs is deterministic.
    SDL_qsort(vid->output_list, vid->output_ڳڻپ, حجم(SDL_Display_معلومات *), Wayland_DisplayPositionCompare);

    // Derive the output pixel coordinates if scale to display is enabled.
    إذا (vid->scale_منزل_display_enabled) {
        Wayland_DeriveOutputPixelCoordinates(vid);
    }

    // Find a suitable primary display and move it to the front of the list.
    ثابت صحيح primary_اشاريو = Wayland_GetPrimaryDisplay(vid);
    إذا (primary_اشاريو) {
        SDL_Display_معلومات *primary = vid->output_list[primary_اشاريو];
        SDL_memmove(&vid->output_list[1], &vid->output_list[0], حجم(SDL_Display_معلومات *) * primary_اشاريو);
        vid->output_list[0] = primary;
    }

    // Apply the ordering hint, if specified.
    Wayland_ترتيب_ڏيو_Outputs_By_ترجيح_Hint(vid);
}

ساكن فراغ Wayland_Refresh_دري_Positions()
{
    SDL_VideoDevice *vid = SDL_GetVideoDevice();

    لكل (SDL_دري *w = vid->windows; w; w = w->ايندڙ) {
        Wayland_Update_دري_Position(w);
    }
}

ساكن فراغ handle_wl_output_پورو(فراغ *معلومات, بنية wl_output *output);

// Initialization/Query functions
ساكن bool Wayland_VideoInit(SDL_VideoDevice *_this);
ساكن bool Wayland_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect);
ساكن فراغ Wayland_VideoQuit(SDL_VideoDevice *_this);

ساكن ثابت حرف *SDL_WAYLAND_surface_ٽيگ = "sdl-window";
ساكن ثابت حرف *SDL_WAYLAND_output_ٽيگ = "sdl-output";

فراغ SDL_WAYLAND_رجسٽر_surface(بنية wl_surface *surface)
{
    wl_proxy_سيٽ_ٽيگ((بنية wl_proxy *)surface, &SDL_WAYLAND_surface_ٽيگ);
}

فراغ SDL_WAYLAND_رجسٽر_output(بنية wl_output *output)
{
    wl_proxy_سيٽ_ٽيگ((بنية wl_proxy *)output, &SDL_WAYLAND_output_ٽيگ);
}

bool SDL_WAYLAND_own_surface(بنية wl_surface *surface)
{
    أرجع wl_proxy_get_ٽيگ((بنية wl_proxy *)surface) == &SDL_WAYLAND_surface_ٽيگ;
}

bool SDL_WAYLAND_own_output(بنية wl_output *output)
{
    أرجع wl_proxy_get_ٽيگ((بنية wl_proxy *)output) == &SDL_WAYLAND_output_ٽيگ;
}

/* External surfaces may have their own user data attached, the modification of which
 * can cause problems with external toolkits. Instead, external windows are kept in
 * their own list, and a search is conducted to find a matching surface.
 */
ساكن بنية wl_list external_دري_list;

فراغ Wayland_جوڙيو_دري_معلومات_منزل_External_List(SDL_دري_معلومات *معلومات)
{
    WAYLAND_wl_list_وجهو(&external_دري_list, &معلومات->external_دري_list_link);
}

فراغ Wayland_Remove_دري_معلومات_From_External_List(SDL_دري_معلومات *معلومات)
{
    WAYLAND_wl_list_remove(&معلومات->external_دري_list_link);
}

SDL_دري_معلومات *Wayland_Get_دري_معلومات_For_Owned_Surface(بنية wl_surface *surface)
{
    إذا (SDL_WAYLAND_own_surface(surface)) {
        أرجع (SDL_دري_معلومات *)wl_surface_get_user_معلومات(surface);
    } وإلا إذا (!WAYLAND_wl_list_خالي_جايون(&external_دري_list)) {
        SDL_دري_معلومات *p;
        wl_list_for_each (p, &external_دري_list, external_دري_list_link) {
            إذا (p->surface == surface) {
                أرجع p;
            }
        }
    }

    أرجع عدم;
}

بنية wl_event_قطار *Wayland_Display_Create_قطار(بنية wl_display *display, ثابت حرف *name)
{
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC
    إذا (WAYLAND_wl_display_create_قطار_with_name) {
        أرجع WAYLAND_wl_display_create_قطار_with_name(display, name);
    }
#وإلاإذا SDL_WAYLAND_CHECK_نسخو(1, 23, 0)
    أرجع WAYLAND_wl_display_create_قطار_with_name(display, name);
#جيڪڏهن_پورو
    أرجع WAYLAND_wl_display_create_قطار(display);
}

ساكن فراغ Wayland_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_Video_معلومات *معلومات = device->اندروني;
    إذا (معلومات->display && !معلومات->display_externally_owned) {
        WAYLAND_wl_display_disconnect(معلومات->display);
        SDL_ClearProperty(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_اشارو);
    }
    SDL_free(معلومات);
    SDL_free(device);
    SDL_WAYLAND_UnloadSymbols();
}

تعريفنوع بنية
{
    bool has_fifo_v1;
    بنية wl_fixes *wl_fixes;
} SDL_Wayland_Preferred_معلومات;

ساكن فراغ wayland_preferred_check_handle_global(فراغ *معلومات, بنية wl_registry *registry, uint32_t id,
                                                  ثابت حرف *interface, uint32_t نسخو)
{
    SDL_Wayland_Preferred_معلومات *d = معلومات;

    إذا (SDL_strcmp(interface, "wp_fifo_manager_v1") == 0) {
        d->has_fifo_v1 = true;
    }
#جيڪڏهن_وصف_ٿيل SDL_WL_FIXES_نسخو
    وإلا إذا (SDL_strcmp(interface, wl_fixes_interface.name) == 0) {
        d->wl_fixes = wl_registry_bind(registry, id, &wl_fixes_interface, SDL_min(SDL_WL_FIXES_نسخو, نسخو));
    }
#جيڪڏهن_پورو
}

ساكن فراغ wayland_preferred_check_remove_global(فراغ *معلومات, بنية wl_registry *registry, uint32_t id)
{
    SDL_Wayland_Preferred_معلومات *d = (SDL_Wayland_Preferred_معلومات *)معلومات;

    إذا (d->wl_fixes && wl_fixes_get_نسخو(d->wl_fixes) >= WL_FIXES_ACK_GLOBAL_REMOVE_SINCE_نسخو) {
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
    SDL_Wayland_Preferred_معلومات preferred_معلومات = { 0 };

    إذا (!registry) {
        SDL_سيٽ_Error("Failed to get the Wayland registry");
        أرجع false;
    }

    wl_registry_جوڙيو_listener(registry, &preferred_registry_listener, &preferred_معلومات);

    WAYLAND_wl_display_roundtrip(display);

    إذا (preferred_معلومات.wl_fixes) {
        wl_fixes_destroy_registry(preferred_معلومات.wl_fixes, registry);
        wl_fixes_destroy(preferred_معلومات.wl_fixes);
    }
    wl_registry_destroy(registry);

    إذا (!preferred_معلومات.has_fifo_v1) {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "This compositor lacks support for the fifo-v1 protocol; falling back to XWayland for GPU performance reasons (set SDL_VIDEO_DRIVER=wayland to override)");
    }
    أرجع preferred_معلومات.has_fifo_v1;
}

ساكن SDL_VideoDevice *Wayland_CreateDevice(bool require_preferred_protocols)
{
    SDL_VideoDevice *device;
    SDL_Video_معلومات *معلومات;
    بنية wl_display *display = SDL_Get_اشارو_Property(SDL_GetGlobalProperties(),
                                                 SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_اشارو, عدم);
    bool display_is_external = !!display;

    // Are we trying to connect to, or are currently in, a Wayland session?
    إذا (!SDL_getenv("WAYLAND_DISPLAY")) {
        ثابت حرف *session = SDL_getenv("XDG_SESSION_TYPE");
        إذا (session && SDL_strcasecmp(session, "wayland") != 0) {
            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "Wayland initialization failed: no Wayland session available");
            أرجع عدم;
        }
    }

    إذا (!SDL_WAYLAND_ڀريو_Symbols()) {
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

    معلومات = SDL_calloc(1, حجم(*معلومات));
    إذا (!معلومات) {
        إذا (!display_is_external) {
            WAYLAND_wl_display_disconnect(display);
        }
        SDL_WAYLAND_UnloadSymbols();
        أرجع عدم;
    }

    معلومات->initializing = true;
    معلومات->display = display;
    معلومات->display_externally_owned = display_is_external;
    معلومات->scale_منزل_display_enabled = SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_SCALE_منزل_DISPLAY, false);
    WAYLAND_wl_list_init(&معلومات->seat_list);
    WAYLAND_wl_list_init(&external_دري_list);

    // Initialize all variables that we clean on shutdown
    device = SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (!device) {
        SDL_free(معلومات);
        إذا (!display_is_external) {
            WAYLAND_wl_display_disconnect(display);
        }
        SDL_WAYLAND_UnloadSymbols();
        أرجع عدم;
    }

    إذا (!display_is_external) {
        SDL_سيٽ_اشارو_Property(SDL_GetGlobalProperties(),
                               SDL_PROP_GLOBAL_VIDEO_WAYLAND_WL_DISPLAY_اشارو, display);
    }

    device->اندروني = معلومات;

    // Set the function pointers
    device->VideoInit = Wayland_VideoInit;
    device->VideoQuit = Wayland_VideoQuit;
    device->GetDisplayBounds = Wayland_GetDisplayBounds;
    device->SuspendScreenSaver = Wayland_SuspendScreenSaver;

    device->PumpEvents = Wayland_PumpEvents;
    device->WaitEventTimeout = Wayland_WaitEventTimeout;
    device->SendWakeupEvent = Wayland_SendWakeupEvent;

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
    device->GL_مٽا_سٽا_دري = Wayland_GLES_مٽا_سٽا_دري;
    device->GL_Get_مٽا_سٽا_Interval = Wayland_GLES_Get_مٽا_سٽا_Interval;
    device->GL_سيٽ_مٽا_سٽا_Interval = Wayland_GLES_سيٽ_مٽا_سٽا_Interval;
    device->GL_MakeCurrent = Wayland_GLES_MakeCurrent;
    device->GL_CreateContext = Wayland_GLES_CreateContext;
    device->GL_ڀريو_Library = Wayland_GLES_ڀريو_Library;
    device->GL_UnloadLibrary = Wayland_GLES_UnloadLibrary;
    device->GL_Get_Proc_پتو = Wayland_GLES_Get_Proc_پتو;
    device->GL_DestroyContext = Wayland_GLES_DestroyContext;
    device->GL_سيٽ_Default_Profile_Config = Wayland_GLES_سيٽ_Default_Profile_Config;
    device->GL_GetEGLSurface = Wayland_GLES_GetEGLSurface;
#جيڪڏهن_پورو

    device->CreateSDLWindow = Wayland_Create_دري;
    device->Show_دري = Wayland_Show_دري;
    device->Hide_دري = Wayland_Hide_دري;
    device->Raise_دري = Wayland_Raise_دري;
    device->سيٽ_دري_Fullscreen = Wayland_سيٽ_دري_Fullscreen;
    device->Maximize_دري = Wayland_Maximize_دري;
    device->Minimize_دري = Wayland_Minimize_دري;
    device->سيٽ_دري_Mouse_Rect = Wayland_سيٽ_دري_Mouse_Rect;
    device->سيٽ_دري_Mouse_Grab = Wayland_سيٽ_دري_Mouse_Grab;
    device->سيٽ_دري_Keyboard_Grab = Wayland_سيٽ_دري_Keyboard_Grab;
    device->Restore_دري = Wayland_Restore_دري;
    device->سيٽ_دري_Bordered = Wayland_سيٽ_دري_Bordered;
    device->سيٽ_دري_Resizable = Wayland_سيٽ_دري_Resizable;
    device->سيٽ_دري_Position = Wayland_سيٽ_دري_Position;
    device->سيٽ_دري_سائيز = Wayland_سيٽ_دري_سائيز;
    device->سيٽ_دري_Aspect_تناسب = Wayland_سيٽ_دري_Aspect_تناسب;
    device->سيٽ_دري_Minimum_سائيز = Wayland_سيٽ_دري_Minimum_سائيز;
    device->سيٽ_دري_وڌ_کان_وڌ_سائيز = Wayland_سيٽ_دري_وڌ_کان_وڌ_سائيز;
    device->سيٽ_دري_والد = Wayland_سيٽ_دري_والد;
    device->سيٽ_دري_Modal = Wayland_سيٽ_دري_Modal;
    device->سيٽ_دري_Opacity = Wayland_سيٽ_دري_Opacity;
    device->سيٽ_دري_Title = Wayland_سيٽ_دري_Title;
    device->سيٽ_دري_Icon = Wayland_سيٽ_دري_Icon;
    device->Get_دري_سائيز_اندريون_Pixels = Wayland_Get_دري_سائيز_اندريون_Pixels;
    device->Get_دري_Content_Scale = Wayland_Get_دري_Content_Scale;
    device->Get_دري_ICCProfile = Wayland_Get_دري_ICCProfile;
    device->Get_Display_For_دري = Wayland_Get_Display_For_دري;
    device->Destroy_دري = Wayland_Destroy_دري;
    device->سيٽ_دري_ڪاميابي_Test = Wayland_سيٽ_دري_ڪاميابي_Test;
    device->Flash_دري = Wayland_Flash_دري;
#جيڪڏهن_وصف_ٿيل SDL_USE_LIBDBUS
    device->Apply_دري_ترقي = DBUS_Apply_دري_ترقي;
#جيڪڏهن_پورو // SDL_USE_LIBDBUS
    device->HasScreenKeyboardSupport = Wayland_HasScreenKeyboardSupport;
    device->Show_دري_System_Menu = Wayland_Show_دري_System_Menu;
    device->Sync_دري = Wayland_Sync_دري;
    device->سيٽ_دري_Focusable = Wayland_سيٽ_دري_Focusable;
    device->Reconfigure_دري = Wayland_Reconfigure_دري;
    device->AcceptDragAndDrop = Wayland_AcceptDragAndDrop;

#جيڪڏهن_وصف_ٿيل SDL_USE_LIBDBUS
    إذا (SDL_SystemTheme_Init())
        device->system_theme = SDL_SystemTheme_Get();
#جيڪڏهن_پورو

    device->Get_متن_Mime_Types = Wayland_Get_متن_Mime_Types;
    device->سيٽ_Clipboard_معلومات = Wayland_سيٽ_Clipboard_معلومات;
    device->Get_Clipboard_معلومات = Wayland_Get_Clipboard_معلومات;
    device->Has_Clipboard_معلومات = Wayland_Has_Clipboard_معلومات;
    device->شروعات_متن_داخلا = Wayland_شروعات_متن_داخلا;
    device->Stop_متن_داخلا = Wayland_Stop_متن_داخلا;
    device->Update_متن_داخلا_Area = Wayland_Update_متن_داخلا_Area;

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_VULKAN
    device->Vulkan_ڀريو_Library = Wayland_Vulkan_ڀريو_Library;
    device->Vulkan_UnloadLibrary = Wayland_Vulkan_UnloadLibrary;
    device->Vulkan_GetInstanceExtensions = Wayland_Vulkan_GetInstanceExtensions;
    device->Vulkan_CreateSurface = Wayland_Vulkan_CreateSurface;
    device->Vulkan_DestroySurface = Wayland_Vulkan_DestroySurface;
    device->Vulkan_GetPresentationSupport = Wayland_Vulkan_GetPresentationSupport;
#جيڪڏهن_پورو

    device->حرر = Wayland_DeleteDevice;

    device->device_caps = VIDEO_DEVICE_CAPS_گهڻائي_SWITCHING_EMULATED |
                          VIDEO_DEVICE_CAPS_HAS_POPUP_دري_SUPPORT |
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
    Wayland_Show_پيغام_Box,
    true
};

VideoBootStrap Wayland_bootstrap = {
    WAYLANDVID_DRIVER_NAME, "SDL Wayland video driver",
    Wayland_Fallback_CreateDevice,
    Wayland_Show_پيغام_Box,
    false
};

ساكن فراغ handle_xdg_output_logical_position(فراغ *معلومات, بنية zxdg_output_v1 *xdg_output, int32_t x, int32_t y)
{
    SDL_Display_معلومات *اندروني = (SDL_Display_معلومات *)معلومات;

    اندروني->geometry_بدليو |= اندروني->logical.x != x || اندروني->logical.y != y;
    اندروني->logical.x = x;
    اندروني->logical.y = y;
    اندروني->has_logical_position = true;
}

ساكن فراغ handle_xdg_output_logical_سائيز(فراغ *معلومات, بنية zxdg_output_v1 *xdg_output, int32_t ويڪر, int32_t اوچائي)
{
    SDL_Display_معلومات *اندروني = (SDL_Display_معلومات *)معلومات;

    اندروني->geometry_بدليو |= اندروني->logical.ويڪر != ويڪر || اندروني->logical.اوچائي != اوچائي;
    اندروني->logical.ويڪر = ويڪر;
    اندروني->logical.اوچائي = اوچائي;
    اندروني->has_logical_سائيز = true;
}

ساكن فراغ handle_xdg_output_پورو(فراغ *معلومات, بنية zxdg_output_v1 *xdg_output)
{
    SDL_Display_معلومات *اندروني = معلومات;

    /*
     * xdg-output.done events are deprecated and only apply below version 3 of the protocol.
     * A wl-output.done event will be emitted in version 3 or higher.
     */
    إذا (zxdg_output_v1_get_نسخو(اندروني->xdg_output) < 3) {
        handle_wl_output_پورو(معلومات, اندروني->output);
    }
}

ساكن فراغ handle_xdg_output_name(فراغ *معلومات, بنية zxdg_output_v1 *xdg_output, ثابت حرف *name)
{
    SDL_Display_معلومات *اندروني = (SDL_Display_معلومات *)معلومات;

    // Deprecated as of wl_output v4.
    إذا (wl_output_get_نسخو(اندروني->output) < WL_OUTPUT_NAME_SINCE_نسخو &&
        اندروني->display == 0) {
        SDL_free(اندروني->wl_output_name);
        اندروني->wl_output_name = SDL_strdup(name);
    }
}

ساكن فراغ handle_xdg_output_description(فراغ *معلومات, بنية zxdg_output_v1 *xdg_output, ثابت حرف *description)
{
    SDL_Display_معلومات *اندروني = (SDL_Display_معلومات *)معلومات;

    // Deprecated as of wl_output v4.
    إذا (wl_output_get_نسخو(اندروني->output) < WL_OUTPUT_DESCRIPTION_SINCE_نسخو &&
        اندروني->display == 0) {
        // xdg-output descriptions, if available, supersede wl-output model names.
        SDL_free(اندروني->placeholder.name);
        اندروني->placeholder.name = SDL_strdup(description);
    }
}

ساكن ثابت بنية zxdg_output_v1_listener xdg_output_listener = {
    handle_xdg_output_logical_position,
    handle_xdg_output_logical_سائيز,
    handle_xdg_output_پورو,
    handle_xdg_output_name,
    handle_xdg_output_description,
};

ساكن فراغ جوڙيو_Emulated_Modes(SDL_Display_معلومات *dispdata, صحيح native_ويڪر, صحيح native_اوچائي)
{
    بنية Emulated_گهڻائي
    {
        صحيح w;
        صحيح h;
    };

    // Resolution lists courtesy of XWayland
    ثابت بنية Emulated_گهڻائي گهڻائي_list[] = {
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
    SDL_Display_گهڻائي گهڻائي;
    SDL_VideoDisplay *dpy = dispdata->display ? SDL_GetVideoDisplay(dispdata->display) : &dispdata->placeholder;
    ثابت bool rot_90 = native_ويڪر < native_اوچائي; // Reverse width/height for portrait displays.

    لكل (i = 0; i < SDL_arraysize(گهڻائي_list); ++i) {
        SDL_zero(گهڻائي);
        گهڻائي.format = dpy->desktop_گهڻائي.format;
        گهڻائي.refresh_شرح_numerator = dpy->desktop_گهڻائي.refresh_شرح_numerator;
        گهڻائي.refresh_شرح_denominator = dpy->desktop_گهڻائي.refresh_شرح_denominator;

        إذا (rot_90) {
            گهڻائي.w = گهڻائي_list[i].h;
            گهڻائي.h = گهڻائي_list[i].w;
        } وإلا {
            گهڻائي.w = گهڻائي_list[i].w;
            گهڻائي.h = گهڻائي_list[i].h;
        }

        // Only add modes that are smaller than the native mode.
        إذا ((گهڻائي.w < native_ويڪر && گهڻائي.h < native_اوچائي) ||
            (گهڻائي.w < native_ويڪر && گهڻائي.h == native_اوچائي) ||
            (گهڻائي.w == native_ويڪر && گهڻائي.h < native_اوچائي)) {
            SDL_جوڙيو_Fullscreen_Display_گهڻائي(dpy, &گهڻائي);
        }
    }
}

ساكن فراغ handle_wl_output_geometry(فراغ *معلومات, بنية wl_output *output, صحيح x, صحيح y,
                                      صحيح physical_ويڪر_2, صحيح physical_اوچائي_2, صحيح subpixel,
                                      ثابت حرف *make, ثابت حرف *model, صحيح transform)
{
    SDL_Display_معلومات *اندروني = (SDL_Display_معلومات *)معلومات;

    // Apply the change from wl-output only if xdg-output is not supported
    إذا (!اندروني->has_logical_position) {
        اندروني->geometry_بدليو |= اندروني->logical.x != x || اندروني->logical.y != y;
        اندروني->logical.x = x;
        اندروني->logical.y = y;
    }
    اندروني->physical.ويڪر_mm = physical_ويڪر_2;
    اندروني->physical.اوچائي_mm = physical_اوچائي_2;

    // The model is only used for the output name if wl_output or xdg-output haven't provided a description.
    إذا (اندروني->display == 0 && !اندروني->placeholder.name) {
        اندروني->placeholder.name = SDL_strdup(model);
    }

    اندروني->transform = transform;
#وصف_ڪريو TF_CASE(اندريون_2, ٻاهريون)                                 \
    حالة WL_OUTPUT_TRANSFORM_##in:                       \
        اندروني->orientation = SDL_ORIENTATION_##out; \
        اكسر;
    إذا (اندروني->physical.ويڪر_mm >= اندروني->physical.اوچائي_mm) {
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
#وصف_رد TF_CASE
}

ساكن فراغ handle_wl_output_گهڻائي(فراغ *معلومات, بنية wl_output *output, uint32_t flags,
                                  صحيح ويڪر, صحيح اوچائي, صحيح refresh)
{
    SDL_Display_معلومات *اندروني = (SDL_Display_معلومات *)معلومات;

    إذا (flags & WL_OUTPUT_گهڻائي_CURRENT) {
        اندروني->geometry_بدليو |= اندروني->pixel.ويڪر != ويڪر || اندروني->pixel.اوچائي != اوچائي;
        اندروني->pixel.ويڪر = ويڪر;
        اندروني->pixel.اوچائي = اوچائي;

        /*
         * Don't rotate this yet, wl-output coordinates are transformed in
         * handle_done and xdg-output coordinates are pre-transformed.
         */
        إذا (!اندروني->has_logical_سائيز) {
            اندروني->geometry_بدليو |= اندروني->logical.ويڪر != ويڪر || اندروني->logical.اوچائي != اوچائي;
            اندروني->logical.ويڪر = ويڪر;
            اندروني->logical.اوچائي = اوچائي;
        }

        اندروني->refresh = refresh;
    }
}

ساكن فراغ handle_wl_output_پورو(فراغ *معلومات, بنية wl_output *output)
{
    ثابت bool گهڻائي_emulation_enabled = SDL_GetHintBoolean(SDL_HINT_VIDEO_WAYLAND_گهڻائي_EMULATION, true);
    SDL_Display_معلومات *اندروني = (SDL_Display_معلومات *)معلومات;
    SDL_Video_معلومات *video = اندروني->videodata;
    SDL_Display_گهڻائي native_گهڻائي, desktop_گهڻائي;

    /*
     * When using xdg-output, two wl-output.done events will be emitted:
     * one at the completion of wl-display and one at the completion of xdg-output.
     *
     * All required events must be received before proceeding.
     */
    ثابت صحيح event_await_ڳڻپ = 1 + (اندروني->xdg_output != عدم);

    اندروني->wl_output_پورو_ڳڻپ = SDL_min(اندروني->wl_output_پورو_ڳڻپ + 1, event_await_ڳڻپ + 1);

    إذا (اندروني->wl_output_پورو_ڳڻپ < event_await_ڳڻپ) {
        أرجع;
    }

    // If the display was already created, reset and rebuild the mode list.
    SDL_VideoDisplay *dpy = SDL_GetVideoDisplay(اندروني->display);
    إذا (dpy) {
        SDL_ResetFullscreenDisplayModes(dpy);
    }

    // The native display resolution
    SDL_zero(native_گهڻائي);
    native_گهڻائي.format = SDL_PIXELFORMAT_XRGB8888;

    // Transform the pixel values, if necessary.
    إذا (اندروني->transform & WL_OUTPUT_TRANSFORM_90) {
        native_گهڻائي.w = اندروني->pixel.اوچائي;
        native_گهڻائي.h = اندروني->pixel.ويڪر;
    } وإلا {
        native_گهڻائي.w = اندروني->pixel.ويڪر;
        native_گهڻائي.h = اندروني->pixel.اوچائي;
    }
    native_گهڻائي.refresh_شرح_numerator = اندروني->refresh;
    native_گهڻائي.refresh_شرح_denominator = 1000;

    إذا (اندروني->has_logical_سائيز) { // If xdg-output is present...
        إذا (native_گهڻائي.w != اندروني->logical.ويڪر || native_گهڻائي.h != اندروني->logical.اوچائي) {
            // ...and the compositor scales the logical viewport...
            إذا (video->viewporter) {
                // ...and viewports are supported, calculate the true scale of the output.
                اندروني->scale_ضرب_ڪندڙ_2 = (مزدوج)native_گهڻائي.w / (مزدوج)اندروني->logical.ويڪر;
            } وإلا {
                // ...otherwise, the 'native' pixel values are a multiple of the logical screen size.
                اندروني->scale_ضرب_ڪندڙ_2 = اندروني->integer_scale_ضرب_ڪندڙ;
                اندروني->pixel.ويڪر = اندروني->logical.ويڪر * اندروني->integer_scale_ضرب_ڪندڙ;
                اندروني->pixel.اوچائي = اندروني->logical.اوچائي * اندروني->integer_scale_ضرب_ڪندڙ;
            }
        } وإلا {
            /* ...and the output viewport is not scaled in the global compositing
             * space, the output dimensions need to be divided by the scale factor.
             *
             * NOTE: This path is needed for old versions of GNOME that predate fractional scaling.
             */
            اندروني->scale_ضرب_ڪندڙ_2 = اندروني->integer_scale_ضرب_ڪندڙ;
            اندروني->logical.ويڪر /= اندروني->integer_scale_ضرب_ڪندڙ;
            اندروني->logical.اوچائي /= اندروني->integer_scale_ضرب_ڪندڙ;
        }
    } وإلا {
        /* Calculate the points from the pixel values, if xdg-output isn't present.
         * Use the native mode pixel values since they are pre-transformed.
         */
        اندروني->scale_ضرب_ڪندڙ_2 = اندروني->integer_scale_ضرب_ڪندڙ;
        اندروني->logical.ويڪر = native_گهڻائي.w / اندروني->integer_scale_ضرب_ڪندڙ;
        اندروني->logical.اوچائي = native_گهڻائي.h / اندروني->integer_scale_ضرب_ڪندڙ;
    }

    // The scaled desktop mode
    SDL_zero(desktop_گهڻائي);
    desktop_گهڻائي.format = SDL_PIXELFORMAT_XRGB8888;

    إذا (!video->scale_منزل_display_enabled) {
        desktop_گهڻائي.w = اندروني->logical.ويڪر;
        desktop_گهڻائي.h = اندروني->logical.اوچائي;
        desktop_گهڻائي.pixel_density = (عائم)اندروني->scale_ضرب_ڪندڙ_2;
    } وإلا {
        desktop_گهڻائي.w = native_گهڻائي.w;
        desktop_گهڻائي.h = native_گهڻائي.h;
        desktop_گهڻائي.pixel_density = 1.0f;
    }

    desktop_گهڻائي.refresh_شرح_numerator = اندروني->refresh;
    desktop_گهڻائي.refresh_شرح_denominator = 1000;

    إذا (اندروني->display > 0) {
        dpy = SDL_GetVideoDisplay(اندروني->display);
    } وإلا {
        dpy = &اندروني->placeholder;
    }

    إذا (video->scale_منزل_display_enabled) {
        SDL_سيٽ_Display_Content_Scale(dpy, (عائم)اندروني->scale_ضرب_ڪندڙ_2);
    }

    // Set the desktop display mode.
    SDL_سيٽ_Desktop_Display_گهڻائي(dpy, &desktop_گهڻائي);

    // Expose the unscaled, native resolution if the scale is 1.0 or viewports are available...
    إذا (اندروني->scale_ضرب_ڪندڙ_2 == 1.0 || video->viewporter) {
        SDL_جوڙيو_Fullscreen_Display_گهڻائي(dpy, &native_گهڻائي);
        إذا (native_گهڻائي.w != desktop_گهڻائي.w ||
            native_گهڻائي.h != desktop_گهڻائي.h) {
            SDL_جوڙيو_Fullscreen_Display_گهڻائي(dpy, &desktop_گهڻائي);
        }
    } وإلا {
        // ...otherwise expose the integer scaled variants of the desktop resolution down to 1.
        desktop_گهڻائي.pixel_density = 1.0f;

        لكل (صحيح i = (صحيح)اندروني->scale_ضرب_ڪندڙ_2; i > 0; --i) {
            desktop_گهڻائي.w = اندروني->logical.ويڪر * i;
            desktop_گهڻائي.h = اندروني->logical.اوچائي * i;
            SDL_جوڙيو_Fullscreen_Display_گهڻائي(dpy, &desktop_گهڻائي);
        }
    }

    // Add emulated modes if wp_viewporter is supported and mode emulation is enabled.
    إذا (video->viewporter && گهڻائي_emulation_enabled) {
        // The transformed display pixel width/height must be used here.
        جوڙيو_Emulated_Modes(اندروني, native_گهڻائي.w, native_گهڻائي.h);
    }

    إذا (اندروني->display == 0) {
        // First time getting display info, initialize the VideoDisplay
        إذا (اندروني->physical.ويڪر_mm >= اندروني->physical.اوچائي_mm) {
            اندروني->placeholder.natural_orientation = SDL_ORIENTATION_LANDSCAPE;
        } وإلا {
            اندروني->placeholder.natural_orientation = SDL_ORIENTATION_PORTRAIT;
        }
        اندروني->placeholder.current_orientation = اندروني->orientation;
        اندروني->placeholder.اندروني = اندروني;

        اندروني->placeholder.props = SDL_CreateProperties();
        SDL_سيٽ_اشارو_Property(اندروني->placeholder.props, SDL_PROP_DISPLAY_WAYLAND_WL_OUTPUT_اشارو, اندروني->output);

        // During initialization, the displays will be added after enumeration is complete.
        إذا (!video->initializing) {
            إذا (video->wp_color_manager_v1) {
                Wayland_GetColorInfoForOutput(اندروني, false);
            }
            إذا (video->scale_منزل_display_enabled) {
                Wayland_DeriveOutputPixelCoordinates(video);
            }

            اندروني->display = SDL_جوڙيو_Video_Display(&اندروني->placeholder, true);
            Wayland_Refresh_دري_Positions();

            SDL_free(اندروني->placeholder.name);
            SDL_zero(اندروني->placeholder);
        }
    } وإلا {
        SDL_SendDisplayEvent(dpy, SDL_EVENT_DISPLAY_ORIENTATION, اندروني->orientation, 0);

        إذا (اندروني->geometry_بدليو) {
            إذا (video->scale_منزل_display_enabled) {
                Wayland_DeriveOutputPixelCoordinates(video);
            }

            SDL_SendDisplayEvent(dpy, SDL_EVENT_DISPLAY_MOVED, 0, 0);
            Wayland_Refresh_دري_Positions();
        }
    }

    اندروني->geometry_بدليو = false;
}

ساكن فراغ handle_wl_output_scale(فراغ *معلومات, بنية wl_output *output, int32_t ضرب_ڪندڙ)
{
    SDL_Display_معلومات *اندروني = (SDL_Display_معلومات *)معلومات;
    اندروني->integer_scale_ضرب_ڪندڙ = ضرب_ڪندڙ;
}

ساكن فراغ handle_wl_output_name(فراغ *معلومات, بنية wl_output *wl_output, ثابت حرف *name)
{
    SDL_Display_معلومات *اندروني = (SDL_Display_معلومات *)معلومات;

    SDL_free(اندروني->wl_output_name);
    اندروني->wl_output_name = SDL_strdup(name);
}

ساكن فراغ handle_wl_output_description(فراغ *معلومات, بنية wl_output *wl_output, ثابت حرف *description)
{
    SDL_Display_معلومات *اندروني = (SDL_Display_معلومات *)معلومات;

    إذا (اندروني->display == 0) {
        // The description, if available, supersedes the model name.
        SDL_free(اندروني->placeholder.name);
        اندروني->placeholder.name = SDL_strdup(description);
    }
}

ساكن ثابت بنية wl_output_listener output_listener = {
    handle_wl_output_geometry,   // Version 1
    handle_wl_output_گهڻائي,       // Version 1
    handle_wl_output_پورو,       // Version 2
    handle_wl_output_scale,      // Version 2
    handle_wl_output_name,       // Version 4
    handle_wl_output_description // Version 4
};

ساكن فراغ handle_output_image_description_بدليو(فراغ *معلومات,
                                                    بنية wp_color_management_output_v1 *wp_color_management_output_v1)
{
    SDL_Display_معلومات *display = (SDL_Display_معلومات *)معلومات;
    Wayland_GetColorInfoForOutput(display, false);
}

ساكن ثابت بنية wp_color_management_output_v1_listener wp_color_management_output_listener = {
    handle_output_image_description_بدليو
};

ساكن bool Wayland_جوڙيو_display(SDL_Video_معلومات *d, uint32_t id, uint32_t نسخو)
{
    بنية wl_output *output;
    SDL_Display_معلومات *معلومات;

    output = wl_registry_bind(d->registry, id, &wl_output_interface, نسخو);
    إذا (!output) {
        أرجع SDL_سيٽ_Error("Failed to retrieve output.");
    }
    معلومات = (SDL_Display_معلومات *)SDL_calloc(1, حجم(*معلومات));
    معلومات->videodata = d;
    معلومات->output = output;
    معلومات->registry_id = id;
    معلومات->scale_ضرب_ڪندڙ_2 = 1.0f;
    معلومات->integer_scale_ضرب_ڪندڙ = 1;

    wl_output_جوڙيو_listener(output, &output_listener, معلومات);
    SDL_WAYLAND_رجسٽر_output(output);

    // Keep a list of outputs for sorting and deferred protocol initialization.
    إذا (d->output_ڳڻپ == d->output_max) {
        d->output_max += 4;
        d->output_list = SDL_realloc(d->output_list, حجم(SDL_Display_معلومات *) * d->output_max);
    }
    d->output_list[d->output_ڳڻپ++] = معلومات;

    إذا (معلومات->videodata->xdg_output_manager) {
        معلومات->xdg_output = zxdg_output_manager_v1_get_xdg_output(معلومات->videodata->xdg_output_manager, output);
        zxdg_output_v1_جوڙيو_listener(معلومات->xdg_output, &xdg_output_listener, معلومات);
    }
    إذا (معلومات->videodata->wp_color_manager_v1) {
        معلومات->wp_color_management_output = wp_color_manager_v1_get_output(معلومات->videodata->wp_color_manager_v1, output);
        wp_color_management_output_v1_جوڙيو_listener(معلومات->wp_color_management_output, &wp_color_management_output_listener, معلومات);

        // If not initializing, this will be queried synchronously in wl_output.done.
        إذا (d->initializing) {
            Wayland_GetColorInfoForOutput(معلومات, true);
        }
    }
    أرجع true;
}

ساكن فراغ Wayland_free_display(SDL_VideoDisplay *display, bool send_event)
{
    إذا (display) {
        SDL_Display_معلومات *display_معلومات = display->اندروني;

        /* A preceding surface leave event is not guaranteed when an output is removed,
         * so ensure that no window continues to hold a reference to a removed output.
         */
        لكل (SDL_دري *دري = SDL_GetVideoDevice()->windows; دري; دري = دري->ايندڙ) {
            Wayland_Remove_Output_From_دري(دري->اندروني, display_معلومات);
        }

        SDL_free(display_معلومات->wl_output_name);

        إذا (display_معلومات->wp_color_management_output) {
            Wayland_FreeColorInfoState(display_معلومات->color_info_state);
            wp_color_management_output_v1_destroy(display_معلومات->wp_color_management_output);
        }

        إذا (display_معلومات->xdg_output) {
            zxdg_output_v1_destroy(display_معلومات->xdg_output);
        }

        إذا (wl_output_get_نسخو(display_معلومات->output) >= WL_OUTPUT_RELEASE_SINCE_نسخو) {
            wl_output_release(display_معلومات->output);
        } وإلا {
            wl_output_destroy(display_معلومات->output);
        }

        SDL_DelVideoDisplay(display->id, send_event);
    }
}

ساكن فراغ Wayland_FinalizeDisplays(SDL_Video_معلومات *vid)
{
    Wayland_ترتيب_ڏيو_Outputs(vid);

    لكل(صحيح i = 0; i < vid->output_ڳڻپ; ++i) {
        SDL_Display_معلومات *d = vid->output_list[i];
        d->display = SDL_جوڙيو_Video_Display(&d->placeholder, false);
        SDL_free(d->placeholder.name);
        SDL_zero(d->placeholder);
    }
}

ساكن فراغ Wayland_init_xdg_output(SDL_Video_معلومات *d)
{
    لكل (صحيح i = 0; i < d->output_ڳڻپ; ++i) {
        SDL_Display_معلومات *disp = d->output_list[i];
        disp->xdg_output = zxdg_output_manager_v1_get_xdg_output(disp->videodata->xdg_output_manager, disp->output);
        zxdg_output_v1_جوڙيو_listener(disp->xdg_output, &xdg_output_listener, disp);
    }
}

ساكن فراغ Wayland_InitColorManager(SDL_Video_معلومات *d)
{
    لكل (صحيح i = 0; i < d->output_ڳڻپ; ++i) {
        SDL_Display_معلومات *disp = d->output_list[i];
        disp->wp_color_management_output = wp_color_manager_v1_get_output(disp->videodata->wp_color_manager_v1, disp->output);
        wp_color_management_output_v1_جوڙيو_listener(disp->wp_color_management_output, &wp_color_management_output_listener, disp);
        Wayland_GetColorInfoForOutput(disp, true);
    }
}

ساكن فراغ handle_xdg_session_created(فراغ *معلومات, بنية xdg_session_v1 *xdg_session_v1, ثابت حرف *id)
{
    SDL_سيٽ_String_Property(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, id);
}

ساكن فراغ handle_xdg_session_restored(فراغ *معلومات, بنية xdg_session_v1 *xdg_session_v1)
{
    // NOP
}

ساكن فراغ handle_xdg_session_replaced(فراغ *معلومات, بنية xdg_session_v1 *xdg_session_v1)
{
    SDL_VideoDevice *viddev = SDL_GetVideoDevice();
    SDL_Video_معلومات *viddata = معلومات;

    // Clean up all session objects, as they have become inert, and should be destroyed.
    SDL_سيٽ_String_Property(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, عدم);

    لكل (SDL_دري *w = viddev->windows; w; w = w->ايندڙ) {
        SDL_دري_معلومات *d = w->اندروني;

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

فراغ Wayland_CreateSession(SDL_Video_معلومات *viddata)
{
    إذا (!viddata->xdg_session_manager) {
        // Set the ID string to null if session management is not available.
        SDL_سيٽ_String_Property(SDL_GetGlobalProperties(), SDL_PROP_GLOBAL_VIDEO_WAYLAND_SESSION_ID_STRING, عدم);
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
            xdg_session_v1_جوڙيو_listener(viddata->xdg_session, &xdg_session_listener, viddata);
        }
    }
}

ساكن فراغ Wayland_SessionDestroy(SDL_Video_معلومات *viddata)
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

ساكن فراغ handle_xdg_wm_بنياد_ping(فراغ *معلومات, بنية xdg_wm_بنياد *xdg, uint32_t serial)
{
    xdg_wm_بنياد_pong(xdg, serial);
}

ساكن ثابت بنية xdg_wm_بنياد_listener xdg_wm_بنياد_listener_2 = {
    handle_xdg_wm_بنياد_ping
};

#جيڪڏهن_وصف_ٿيل HAVE_LIBDECOR_H
ساكن فراغ libdecor_error(بنية libdecor *context,
                           تعداد libdecor_error error,
                           ثابت حرف *پيغام)
{
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "libdecor error (%d): %s", error, پيغام);
}

ساكن بنية libdecor_interface libdecor_interface = {
    libdecor_error
};
#جيڪڏهن_پورو

ساكن فراغ handle_registry_global(فراغ *معلومات, بنية wl_registry *registry, uint32_t id,
                                   ثابت حرف *interface, uint32_t نسخو)
{
    SDL_Video_معلومات *d = معلومات;

    إذا (SDL_strcmp(interface, wl_compositor_interface.name) == 0) {
        d->compositor = wl_registry_bind(d->registry, id, &wl_compositor_interface, SDL_min(SDL_WL_COMPOSITOR_نسخو, نسخو));
    } وإلا إذا (SDL_strcmp(interface, wl_subcompositor_interface.name) == 0) {
        d->subcompositor = wl_registry_bind(d->registry, id, &wl_subcompositor_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, wl_output_interface.name) == 0) {
        Wayland_جوڙيو_display(d, id, SDL_min(نسخو, SDL_WL_OUTPUT_نسخو));
    } وإلا إذا (SDL_strcmp(interface, wl_seat_interface.name) == 0) {
        بنية wl_seat *seat = wl_registry_bind(d->registry, id, &wl_seat_interface, SDL_min(SDL_WL_SEAT_نسخو, نسخو));
        Wayland_DisplayCreateSeat(d, seat, id);
    } وإلا إذا (SDL_strcmp(interface, xdg_wm_بنياد_interface.name) == 0) {
        d->shell.xdg = wl_registry_bind(d->registry, id, &xdg_wm_بنياد_interface, SDL_min(نسخو, 7));
        xdg_wm_بنياد_جوڙيو_listener(d->shell.xdg, &xdg_wm_بنياد_listener_2, عدم);
    } وإلا إذا (SDL_strcmp(interface, wl_shm_interface.name) == 0) {
        d->shm = wl_registry_bind(registry, id, &wl_shm_interface, SDL_min(SDL_WL_SHM_نسخو, نسخو));
    } وإلا إذا (SDL_strcmp(interface, zwp_relative_اشارو_manager_v1_interface.name) == 0) {
        d->relative_اشارو_manager = wl_registry_bind(d->registry, id, &zwp_relative_اشارو_manager_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, zwp_اشارو_constraints_v1_interface.name) == 0) {
        d->اشارو_constraints = wl_registry_bind(d->registry, id, &zwp_اشارو_constraints_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, zwp_keyboard_shortcuts_inhibit_manager_v1_interface.name) == 0) {
        d->ڪنجي_inhibitor_manager = wl_registry_bind(d->registry, id, &zwp_keyboard_shortcuts_inhibit_manager_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, zwp_idle_inhibit_manager_v1_interface.name) == 0) {
        d->idle_inhibit_manager = wl_registry_bind(d->registry, id, &zwp_idle_inhibit_manager_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, xdg_activation_v1_interface.name) == 0) {
        d->activation_manager = wl_registry_bind(d->registry, id, &xdg_activation_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, zwp_متن_داخلا_manager_v3_interface.name) == 0) {
        d->متن_داخلا_manager = wl_registry_bind(d->registry, id, &zwp_متن_داخلا_manager_v3_interface, 1);
        Wayland_Display_Init_متن_داخلا_Manager(d, id);
    } وإلا إذا (SDL_strcmp(interface, wl_معلومات_device_manager_interface.name) == 0) {
        d->معلومات_device_manager = wl_registry_bind(d->registry, id, &wl_معلومات_device_manager_interface, SDL_min(3, نسخو));
        Wayland_Display_Init_معلومات_Device_Manager(d);
    } وإلا إذا (SDL_strcmp(interface, zwp_primary_selection_device_manager_v1_interface.name) == 0) {
        d->primary_selection_device_manager = wl_registry_bind(d->registry, id, &zwp_primary_selection_device_manager_v1_interface, 1);
        Wayland_DisplayInitPrimarySelectionDeviceManager(d);
    } وإلا إذا (SDL_strcmp(interface, zxdg_decoration_manager_v1_interface.name) == 0) {
        d->decoration_manager = wl_registry_bind(d->registry, id, &zxdg_decoration_manager_v1_interface, SDL_min(2, نسخو));
    } وإلا إذا (SDL_strcmp(interface, zwp_tablet_manager_v2_interface.name) == 0) {
        d->tablet_manager = wl_registry_bind(d->registry, id, &zwp_tablet_manager_v2_interface, 1);
        Wayland_DisplayInitTabletManager(d);
    } وإلا إذا (SDL_strcmp(interface, zxdg_output_manager_v1_interface.name) == 0) {
        نسخو = SDL_min(نسخو, 3); // Versions 1 through 3 are supported.
        d->xdg_output_manager = wl_registry_bind(d->registry, id, &zxdg_output_manager_v1_interface, نسخو);
        Wayland_init_xdg_output(d);
    } وإلا إذا (SDL_strcmp(interface, wp_viewporter_interface.name) == 0) {
        d->viewporter = wl_registry_bind(d->registry, id, &wp_viewporter_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, wp_fractional_scale_manager_v1_interface.name) == 0) {
        d->fractional_scale_manager = wl_registry_bind(d->registry, id, &wp_fractional_scale_manager_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, zwp_داخلا_timestamps_manager_v1_interface.name) == 0) {
        d->داخلا_timestamps_manager = wl_registry_bind(d->registry, id, &zwp_داخلا_timestamps_manager_v1_interface, 1);
        Wayland_Display_Init_داخلا_Timestamp_Manager(d);
    } وإلا إذا (SDL_strcmp(interface, wp_cursor_shape_manager_v1_interface.name) == 0) {
        d->cursor_shape_manager = wl_registry_bind(d->registry, id, &wp_cursor_shape_manager_v1_interface, SDL_min(نسخو, 2));
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
        d->wp_color_manager_v1 = wl_registry_bind(d->registry, id, &wp_color_manager_v1_interface, SDL_min(نسخو, 2));
        Wayland_InitColorManager(d);
    } وإلا إذا (SDL_strcmp(interface, wp_اشارو_warp_v1_interface.name) == 0) {
        d->wp_اشارو_warp_v1 = wl_registry_bind(d->registry, id, &wp_اشارو_warp_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, zwp_اشارو_gestures_v1_interface.name) == 0) {
        d->zwp_اشارو_gestures = wl_registry_bind(d->registry, id, &zwp_اشارو_gestures_v1_interface, SDL_min(نسخو, 3));
        Wayland_Display_Init_اشارو_Gesture_Manager(d);
    } وإلا إذا (SDL_strcmp(interface, wp_single_pixel_بفر_manager_v1_interface.name) == 0) {
        d->single_pixel_بفر_manager = wl_registry_bind(d->registry, id, &wp_single_pixel_بفر_manager_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, xdg_session_manager_v1_interface.name) == 0) {
        d->xdg_session_manager = wl_registry_bind(d->registry, id, &xdg_session_manager_v1_interface, 1);
    } وإلا إذا (SDL_strcmp(interface, xdg_toplevel_ٽيگ_manager_v1_interface.name) == 0) {
        d->xdg_toplevel_ٽيگ_manager = wl_registry_bind(d->registry, id, &xdg_toplevel_ٽيگ_manager_v1_interface, 1);
    }
#جيڪڏهن_وصف_ٿيل SDL_WL_FIXES_نسخو
    وإلا إذا (SDL_strcmp(interface, wl_fixes_interface.name) == 0) {
        d->wl_fixes = wl_registry_bind(d->registry, id, &wl_fixes_interface, SDL_min(SDL_WL_FIXES_نسخو, نسخو));
    }
#جيڪڏهن_پورو
}

ساكن فراغ handle_registry_remove_global(فراغ *معلومات, بنية wl_registry *registry, uint32_t id)
{
    SDL_Video_معلومات *d = معلومات;

    // We don't get an interface, just an ID, so check outputs and seats.
    لكل (صحيح i = 0; i < d->output_ڳڻپ; ++i) {
        SDL_Display_معلومات *disp = d->output_list[i];
        إذا (disp->registry_id == id) {
            Wayland_free_display(SDL_GetVideoDisplay(disp->display), true);

            إذا (i < d->output_ڳڻپ) {
                SDL_memmove(&d->output_list[i], &d->output_list[i + 1], حجم(SDL_Display_معلومات *) * (d->output_ڳڻپ - i - 1));
            }

            d->output_ڳڻپ--;
            اذهب ack_remove;
        }
    }

    SDL_WaylandSeat *seat, *عارضي;
    wl_list_for_each_محفوظ (seat, عارضي, &d->seat_list, link) {
        إذا (seat->registry_id == id) {
            Wayland_SeatDestroy(seat, false);
            اذهب ack_remove;
        }
    }

ack_remove:
    إذا (d->wl_fixes && wl_fixes_get_نسخو(d->wl_fixes) >= WL_FIXES_ACK_GLOBAL_REMOVE_SINCE_نسخو) {
        wl_fixes_ack_global_remove(d->wl_fixes, registry, id);
    }
}

ساكن ثابت بنية wl_registry_listener registry_listener = {
    handle_registry_global,
    handle_registry_remove_global
};

#جيڪڏهن_وصف_ٿيل HAVE_LIBDECOR_H
ساكن bool should_use_libdecor(SDL_Video_معلومات *معلومات, bool ignore_xdg)
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

    إذا (معلومات->decoration_manager) {
        أرجع false;
    }

    أرجع true;
}

ساكن فراغ LibdecorNew(SDL_Video_معلومات *معلومات)
{
    معلومات->shell.libdecor = libdecor_new(معلومات->display, &libdecor_interface);
}

// Called in another thread, but the UI thread is blocked in SDL_WaitThread
// during that time, so it should be OK to dereference data without locks
ساكن صحيح SDLCALL Libdecor_New_اندريون_Thread(فراغ *معلومات)
{
    LibdecorNew((SDL_Video_معلومات *)معلومات);
    أرجع 0;
}
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل HAVE_GETRESUID
#وصف_ڪريو SDL_getresuid getresuid
#وإلا
// Non-POSIX, but Linux and some BSDs have it.
// To reduce the number of code paths, if getresuid() isn't available at
// compile-time, we behave as though it existed but failed at runtime.
ساكن مضمن صحيح SDL_getresuid(uid_t *ruid, uid_t *euid, uid_t *suid) {
    errno = ENOSYS;
    أرجع -1;
}
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل HAVE_GETRESGID
#وصف_ڪريو SDL_getresgid getresgid
#وإلا
// Same as getresuid() but for the primary group
ساكن مضمن صحيح SDL_getresgid(gid_t *rgid, gid_t *egid, gid_t *sgid) {
    errno = ENOSYS;
    أرجع -1;
}
#جيڪڏهن_پورو

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

bool Wayland_ڀريو_Libdecor(SDL_Video_معلومات *معلومات, bool ignore_xdg)
{
#جيڪڏهن_وصف_ٿيل HAVE_LIBDECOR_H
    إذا (معلومات->shell.libdecor != عدم) {
        أرجع true; // Already loaded!
    }
    إذا (should_use_libdecor(معلومات, ignore_xdg)) {
        إذا (CanUseGtk()) {
            LibdecorNew(معلومات);
        } وإلا {
            // Intentionally initialize libdecor in a non-main thread
            // so that it will not use its GTK plugin, but instead will
            // fall back to the Cairo or dummy plugin
            SDL_Thread *thread = SDL_CreateThread(Libdecor_New_اندريون_Thread, "SDL_LibdecorNew", (فراغ *)معلومات);
            // Note that the other thread now "owns" data until we have
            // waited for it, so don't touch data here
            SDL_WaitThread(thread, عدم);
        }

        أرجع معلومات->shell.libdecor != عدم;
    }
#جيڪڏهن_پورو
    أرجع false;
}

bool Wayland_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *معلومات = _this->اندروني;

    معلومات->event_thread_context = Wayland_CreateEventThread(معلومات, "SDL Event Thread Queue");
    إذا (!معلومات->event_thread_context) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Failed to create event thread context");
    }

    معلومات->ڪم_thread_context = Wayland_Create_ڪم_Thread();
    إذا (!معلومات->ڪم_thread_context) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Failed to create job thread context");
    }

    معلومات->xkb_context = WAYLAND_xkb_context_new(0);
    إذا (!معلومات->xkb_context) {
        أرجع SDL_سيٽ_Error("Failed to create XKB context");
    }

    معلومات->registry = wl_display_get_registry(معلومات->display);
    إذا (!معلومات->registry) {
        أرجع SDL_سيٽ_Error("Failed to get the Wayland registry");
    }

    wl_registry_جوڙيو_listener(معلومات->registry, &registry_listener, معلومات);

    // First roundtrip to receive all registry objects.
    WAYLAND_wl_display_roundtrip(معلومات->display);

    // Require viewports and xdg-output for display scaling.
    إذا (معلومات->scale_منزل_display_enabled) {
        إذا (!معلومات->viewporter) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Display scaling requires the missing 'wp_viewporter' protocol: disabling");
            معلومات->scale_منزل_display_enabled = false;
        }
        إذا (!معلومات->xdg_output_manager) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "wayland: Display scaling requires the missing 'zxdg_output_manager_v1' protocol: disabling");
            معلومات->scale_منزل_display_enabled = false;
        }
    }

    // Now that we have all the protocols, load libdecor if applicable
    Wayland_ڀريو_Libdecor(معلومات, false);

    // Second roundtrip to receive all output events.
    WAYLAND_wl_display_roundtrip(معلومات->display);

    Wayland_FinalizeDisplays(معلومات);

    Wayland_InitMouse(معلومات);
    Wayland_InitKeyboard(_this);

    إذا (معلومات->primary_selection_device_manager) {
        _this->سيٽ_Primary_Selection_متن = Wayland_سيٽ_Primary_Selection_متن;
        _this->Get_Primary_Selection_متن = Wayland_Get_Primary_Selection_متن;
        _this->Has_Primary_Selection_متن = Wayland_Has_Primary_Selection_متن;
    }

    معلومات->initializing = false;

    أرجع true;
}

ساكن bool Wayland_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    SDL_Video_معلومات *viddata = _this->اندروني;
    SDL_Display_معلومات *اندروني = display->اندروني;

    إذا (!viddata->scale_منزل_display_enabled) {
        rect->x = اندروني->logical.x;
        rect->y = اندروني->logical.y;
    } وإلا {
        rect->x = اندروني->pixel.x;
        rect->y = اندروني->pixel.y;
    }

    // When an emulated, exclusive fullscreen window has focus, treat the mode dimensions as the display bounds.
    إذا (display->fullscreen_دري &&
        display->fullscreen_دري->fullscreen_exclusive &&
        display->fullscreen_دري->اندروني->سرگرم &&
        display->fullscreen_دري->current_fullscreen_گهڻائي.w != 0 &&
        display->fullscreen_دري->current_fullscreen_گهڻائي.h != 0) {
        rect->w = display->fullscreen_دري->current_fullscreen_گهڻائي.w;
        rect->h = display->fullscreen_دري->current_fullscreen_گهڻائي.h;
    } وإلا {
        إذا (!viddata->scale_منزل_display_enabled) {
            rect->w = display->current_گهڻائي->w;
            rect->h = display->current_گهڻائي->h;
        } وإلا إذا (اندروني->transform & WL_OUTPUT_TRANSFORM_90) {
            rect->w = اندروني->pixel.اوچائي;
            rect->h = اندروني->pixel.ويڪر;
        } وإلا {
            rect->w = اندروني->pixel.ويڪر;
            rect->h = اندروني->pixel.اوچائي;
        }
    }
    أرجع true;
}

ساكن فراغ Wayland_VideoCleanup(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *معلومات = _this->اندروني;
    SDL_WaylandSeat *seat, *tmp;

    Wayland_SessionDestroy(معلومات);

    لكل (صحيح i = _this->انگ_displays - 1; i >= 0; --i) {
        SDL_VideoDisplay *display = _this->displays[i];
        Wayland_free_display(display, false);
    }
    SDL_free(معلومات->output_list);

    wl_list_for_each_محفوظ (seat, tmp, &معلومات->seat_list, link) {
        Wayland_SeatDestroy(seat, true);
    }

    Wayland_FiniMouse(معلومات);
    Wayland_QuitKeyboard(_this);

    Wayland_DestroyEventThread(معلومات->event_thread_context);
    معلومات->event_thread_context = عدم;

    Wayland_Destroy_ڪم_Thread(معلومات->ڪم_thread_context);
    معلومات->ڪم_thread_context = عدم;

    إذا (معلومات->اشارو_constraints) {
        zwp_اشارو_constraints_v1_destroy(معلومات->اشارو_constraints);
        معلومات->اشارو_constraints = عدم;
    }

    إذا (معلومات->relative_اشارو_manager) {
        zwp_relative_اشارو_manager_v1_destroy(معلومات->relative_اشارو_manager);
        معلومات->relative_اشارو_manager = عدم;
    }

    إذا (معلومات->activation_manager) {
        xdg_activation_v1_destroy(معلومات->activation_manager);
        معلومات->activation_manager = عدم;
    }

    إذا (معلومات->idle_inhibit_manager) {
        zwp_idle_inhibit_manager_v1_destroy(معلومات->idle_inhibit_manager);
        معلومات->idle_inhibit_manager = عدم;
    }

    إذا (معلومات->ڪنجي_inhibitor_manager) {
        zwp_keyboard_shortcuts_inhibit_manager_v1_destroy(معلومات->ڪنجي_inhibitor_manager);
        معلومات->ڪنجي_inhibitor_manager = عدم;
    }

    إذا (معلومات->متن_داخلا_manager) {
        zwp_متن_داخلا_manager_v3_destroy(معلومات->متن_داخلا_manager);
        معلومات->متن_داخلا_manager = عدم;
    }

    إذا (معلومات->xkb_context) {
        WAYLAND_xkb_context_unref(معلومات->xkb_context);
        معلومات->xkb_context = عدم;
    }

    إذا (معلومات->tablet_manager) {
        zwp_tablet_manager_v2_destroy((بنية zwp_tablet_manager_v2 *)معلومات->tablet_manager);
        معلومات->tablet_manager = عدم;
    }

    إذا (معلومات->معلومات_device_manager) {
        wl_معلومات_device_manager_destroy(معلومات->معلومات_device_manager);
        معلومات->معلومات_device_manager = عدم;
    }

    إذا (معلومات->shm) {
        إذا (wl_shm_get_نسخو(معلومات->shm) >= WL_SHM_RELEASE_SINCE_نسخو) {
            wl_shm_release(معلومات->shm);
        } وإلا {
            wl_shm_destroy(معلومات->shm);
        }
        معلومات->shm = عدم;
    }

    إذا (معلومات->shell.xdg) {
        xdg_wm_بنياد_destroy(معلومات->shell.xdg);
        معلومات->shell.xdg = عدم;
    }

    إذا (معلومات->decoration_manager) {
        zxdg_decoration_manager_v1_destroy(معلومات->decoration_manager);
        معلومات->decoration_manager = عدم;
    }

    إذا (معلومات->xdg_output_manager) {
        zxdg_output_manager_v1_destroy(معلومات->xdg_output_manager);
        معلومات->xdg_output_manager = عدم;
    }

    إذا (معلومات->viewporter) {
        wp_viewporter_destroy(معلومات->viewporter);
        معلومات->viewporter = عدم;
    }

    إذا (معلومات->primary_selection_device_manager) {
        zwp_primary_selection_device_manager_v1_destroy(معلومات->primary_selection_device_manager);
        معلومات->primary_selection_device_manager = عدم;
    }

    إذا (معلومات->fractional_scale_manager) {
        wp_fractional_scale_manager_v1_destroy(معلومات->fractional_scale_manager);
        معلومات->fractional_scale_manager = عدم;
    }

    إذا (معلومات->داخلا_timestamps_manager) {
        zwp_داخلا_timestamps_manager_v1_destroy(معلومات->داخلا_timestamps_manager);
        معلومات->داخلا_timestamps_manager = عدم;
    }

    إذا (معلومات->cursor_shape_manager) {
        wp_cursor_shape_manager_v1_destroy(معلومات->cursor_shape_manager);
        معلومات->cursor_shape_manager = عدم;
    }

    إذا (معلومات->zxdg_exporter_v2) {
        zxdg_exporter_v2_destroy(معلومات->zxdg_exporter_v2);
        معلومات->zxdg_exporter_v2 = عدم;
    }

    إذا (معلومات->xdg_wm_dialog_v1) {
        xdg_wm_dialog_v1_destroy(معلومات->xdg_wm_dialog_v1);
        معلومات->xdg_wm_dialog_v1 = عدم;
    }

    إذا (معلومات->wp_alpha_modifier_v1) {
        wp_alpha_modifier_v1_destroy(معلومات->wp_alpha_modifier_v1);
        معلومات->wp_alpha_modifier_v1 = عدم;
    }

    إذا (معلومات->xdg_toplevel_icon_manager_v1) {
        xdg_toplevel_icon_manager_v1_destroy(معلومات->xdg_toplevel_icon_manager_v1);
        معلومات->xdg_toplevel_icon_manager_v1 = عدم;
    }

    إذا (معلومات->frog_color_management_factory_v1) {
        frog_color_management_factory_v1_destroy(معلومات->frog_color_management_factory_v1);
        معلومات->frog_color_management_factory_v1 = عدم;
    }

    إذا (معلومات->wp_color_manager_v1) {
        wp_color_manager_v1_destroy(معلومات->wp_color_manager_v1);
        معلومات->wp_color_manager_v1 = عدم;
    }

    إذا (معلومات->wp_اشارو_warp_v1) {
        wp_اشارو_warp_v1_destroy(معلومات->wp_اشارو_warp_v1);
        معلومات->wp_اشارو_warp_v1 = عدم;
    }

    إذا (معلومات->zwp_اشارو_gestures) {
        إذا (zwp_اشارو_gestures_v1_get_نسخو(معلومات->zwp_اشارو_gestures) >= ZWP_اشارو_GESTURES_V1_RELEASE_SINCE_نسخو) {
            zwp_اشارو_gestures_v1_release(معلومات->zwp_اشارو_gestures);
        } وإلا {
            zwp_اشارو_gestures_v1_destroy(معلومات->zwp_اشارو_gestures);
        }
        معلومات->zwp_اشارو_gestures = عدم;
    }

    إذا (معلومات->single_pixel_بفر_manager) {
        wp_single_pixel_بفر_manager_v1_destroy(معلومات->single_pixel_بفر_manager);
        معلومات->single_pixel_بفر_manager = عدم;
    }

    إذا (معلومات->xdg_session_manager) {
        xdg_session_manager_v1_destroy(معلومات->xdg_session_manager);
        معلومات->xdg_session_manager = عدم;
    }

    إذا (معلومات->xdg_toplevel_ٽيگ_manager) {
        xdg_toplevel_ٽيگ_manager_v1_destroy(معلومات->xdg_toplevel_ٽيگ_manager);
        معلومات->xdg_toplevel_ٽيگ_manager = عدم;
    }

    إذا (معلومات->subcompositor) {
        wl_subcompositor_destroy(معلومات->subcompositor);
        معلومات->subcompositor = عدم;
    }

    إذا (معلومات->compositor) {
        wl_compositor_destroy(معلومات->compositor);
        معلومات->compositor = عدم;
    }

    إذا (معلومات->registry) {
        إذا (معلومات->wl_fixes) {
            wl_fixes_destroy_registry(معلومات->wl_fixes, معلومات->registry);
            wl_fixes_destroy(معلومات->wl_fixes);
            معلومات->wl_fixes = عدم;
        }
        wl_registry_destroy(معلومات->registry);
        معلومات->registry = عدم;
    }
}

ساكن bool Wayland_VideoReconnect(SDL_VideoDevice *_this)
{
#إذا 0 // TODO RECONNECT: Uncomment all when https://invent.kde.org/plasma/kwin/-/wikis/Restarting is completed
    SDL_Video_معلومات *معلومات = _this->اندروني;

    SDL_دري *دري = عدم;

    SDL_GLContext current_ctx = SDL_GL_GetCurrentContext();
    SDL_دري *current_دري = SDL_GL_Get_Current_دري();

    SDL_GL_MakeCurrent(عدم, عدم);
    Wayland_VideoCleanup(_this);

    SDL_ResetKeyboard();
    SDL_ResetMouse();
    إذا (WAYLAND_wl_display_reconnect(معلومات->display) < 0) {
        أرجع false;
    }

    Wayland_VideoInit(_this);

    دري = _this->windows;
    طالما (دري) {
        /* We're going to cheat _just_ for a second and strip the OpenGL flag.
         * The Wayland driver actually forces it in CreateWindow, and
         * RecreateWindow does a bunch of unloading/loading of libGL, so just
         * strip the flag so RecreateWindow doesn't mess with the GL context,
         * and CreateWindow will add it right back!
         * -flibit
         */
        دري->flags &= ~SDL_دري_OPENGL;

        SDL_Recreate_دري(دري, دري->flags);
        دري = دري->ايندڙ;
    }

    Wayland_RecreateCursors();

    إذا (current_دري && current_ctx) {
        SDL_GL_MakeCurrent (current_دري, current_ctx);
    }
    أرجع true;
#وإلا
    أرجع false;
#جيڪڏهن_پورو // 0
}

bool Wayland_HandleDisplayDisconnected(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *video_معلومات = _this->اندروني;

    /* Something has failed with the Wayland connection -- for example,
     * the compositor may have shut down and closed its end of the socket,
     * or there is a library-specific error.
     *
     * Try to recover once, then quit.
     */
    إذا (video_معلومات->display_disconnected) {
        أرجع false;
    }

    إذا (Wayland_VideoReconnect(_this)) {
        أرجع true;
    }

    video_معلومات->display_disconnected = true;
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Wayland display connection closed by server (fatal)");

    // Only send a single quit message, as application shutdown might call SDL_PumpEvents().
    SDL_SendQuit();

    أرجع false;
}

فراغ Wayland_VideoQuit(SDL_VideoDevice *_this)
{
    Wayland_VideoCleanup(_this);

#جيڪڏهن_وصف_ٿيل HAVE_LIBDECOR_H
    SDL_Video_معلومات *معلومات = _this->اندروني;
    إذا (معلومات->shell.libdecor) {
        libdecor_unref(معلومات->shell.libdecor);
        معلومات->shell.libdecor = عدم;
    }
#جيڪڏهن_پورو
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_WAYLAND
