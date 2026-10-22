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

#شامل <sys/mman.h>

#شامل "../SDL_sysvideo.h"
#شامل "../../events/SDL_events_c.h"
#شامل "../../core/unix/SDL_appid.h"
#شامل "../../notification/SDL_notification_c.h"
#شامل "../SDL_egl_c.h"
#شامل "SDL_waylandevents_c.h"
#شامل "SDL_waylandmouse.h"
#شامل "SDL_waylandwindow.h"
#شامل "SDL_waylandvideo.h"
#شامل "../../SDL_hints_c.h"
#شامل "SDL_waylandcolor.h"

#شامل "alpha-modifier-v1-client-protocol.h"
#شامل "xdg-shell-client-protocol.h"
#شامل "xdg-decoration-unstable-v1-client-protocol.h"
#شامل "idle-inhibit-unstable-v1-client-protocol.h"
#شامل "xdg-activation-v1-client-protocol.h"
#شامل "viewporter-client-protocol.h"
#شامل "fractional-scale-v1-client-protocol.h"
#شامل "xdg-foreign-unstable-v2-client-protocol.h"
#شامل "xdg-dialog-v1-client-protocol.h"
#شامل "frog-color-management-v1-client-protocol.h"
#شامل "xdg-toplevel-icon-v1-client-protocol.h"
#شامل "color-management-v1-client-protocol.h"
#شامل "xdg-session-management-v1-client-protocol.h"
#شامل "xdg-toplevel-tag-v1-client-protocol.h"

#اگر_تعریف_شدہ HAVE_LIBDECOR_H
#شامل <libdecor.h>
#اگر_ختم

/* According to the Wayland spec:
 *
 * "If the [fullscreen] surface doesn't cover the whole output, the compositor will
 * position the surface in the center of the output and compensate with border fill
 * covering the rest of the output. The content of the border fill is undefined, but
 * should be assumed to be in some way that attempts to blend into the surrounding area
 * (e.g. solid black)."
 *
 * KDE (6.7 at the time of writing) doesn't do this (https://invent.kde.org/plasma/kwin/-/merge_requests/6953),
 * so fullscreen modes that don't cover the output need to be manually masked.
 *
 * This must not be done universally, as some compositors do not correctly honor subsurface
 * offsets on fullscreen windows, but those also follow the spec regarding automatic masking
 * around fullscreen windows, so SDL doesn't need to apply its own mask.
 *
 * TODO: Remove this once KDE is spec-compliant.
 */
ساکن bool Should_نقاب_Fullscreen()
{
    ساکن صحیح نقاب_required = -1;

    اگر (نقاب_required >= 0) {
        واپس نقاب_required != 0;
    }

    ثابت حرف *desktop = SDL_getenv("XDG_CURRENT_DESKTOP");
    اگر (desktop && SDL_strstr(desktop, "KDE") != تہی) {
        نقاب_required = 1;
    } ورنہ {
        نقاب_required = 0;
    }

    واپس نقاب_required != 0;
}

ساکن دوہرا Get_کھڑکی_Scale(SDL_کھڑکی *کھڑکی)
{
    واپس (کھڑکی->flags & SDL_کھڑکی_بلند_PIXEL_DENSITY) || کھڑکی->اندرونی_2->scale_مقصد_display ? کھڑکی->اندرونی_2->scale_ضربی_عدد_2 : 1.0;
}

// These are point->pixel->point round trip safe; the inverse is not round trip safe due to rounding.
ساکن صحیح نقطہ_مقصد_Pixel(SDL_کھڑکی *کھڑکی, صحیح نقطہ)
{
    /* Rounds halfway away from zero as per the Wayland fractional scaling protocol spec.
     * Wayland scale units are in units of 1/120, so the offset is required to correct for
     * rounding errors when using certain scale values.
     */
    واپس نقطہ ? SDL_max((صحیح)SDL_lround((دوہرا)نقطہ * Get_کھڑکی_Scale(کھڑکی) + 1e-6), 1) : 0;
}

ساکن صحیح Pixel_مقصد_نقطہ(SDL_کھڑکی *کھڑکی, صحیح pixel)
{
    واپس pixel ? SDL_max((صحیح)SDL_lround((دوہرا)pixel / Get_کھڑکی_Scale(کھڑکی)), 1) : 0;
}

شمار Wayland_منوال_Scale
{
    WAYLAND_منوال_SCALE_UNDEFINED,
    WAYLAND_منوال_SCALE_ASPECT,
    WAYLAND_منوال_SCALE_STRETCH,
    WAYLAND_منوال_SCALE_NONE
};

ساکن شمار Wayland_منوال_Scale Get_منوال_Scale_طریقہ(خالی)
{
    ساکن شمار Wayland_منوال_Scale scale_منوال_2 = WAYLAND_منوال_SCALE_UNDEFINED;

    اگر (scale_منوال_2 == WAYLAND_منوال_SCALE_UNDEFINED) {
        ثابت حرف *scale_hint = SDL_GetHint(SDL_HINT_VIDEO_WAYLAND_منوال_SCALING);

        اگر (scale_hint) {
            اگر (!SDL_strcasecmp(scale_hint, "stretch")) {
                scale_منوال_2 = WAYLAND_منوال_SCALE_STRETCH;
            } ورنہ اگر (!SDL_strcasecmp(scale_hint, "none")) {
                scale_منوال_2 = WAYLAND_منوال_SCALE_NONE;
            } ورنہ {
                scale_منوال_2 = WAYLAND_منوال_SCALE_ASPECT;
            }
        } ورنہ {
            scale_منوال_2 = WAYLAND_منوال_SCALE_ASPECT;
        }
    }

    واپس scale_منوال_2;
}

قسمتعریف ساخت BorderInsets
{
    صحیح بایاں;
    صحیح چوٹی;
    صحیح دایاں;
    صحیح bottom;
} BorderInsets;

// The border insets from the window properties; they only apply to xdg-toplevel windows.
ساکن خالی GetBorderInsets(SDL_کھڑکی *کھڑکی, BorderInsets *insets)
{
    SDL_zerop(insets);
    اگر (!کھڑکی->اندرونی_2->enable_insets) {
        واپس;
    }
    اگر (کھڑکی->اندرونی_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        ثابت SDL_PropertiesID props = SDL_Get_کھڑکی_Properties(کھڑکی);
        insets->بایاں = (صحیح)SDL_clamp(SDL_Get_نمبر_Property(props, SDL_PROP_کھڑکی_WAYLAND_BORDER_INSET_بایاں_نمبر, 0), 0, SDL_MAX_SINT16);
        insets->چوٹی = (صحیح)SDL_clamp(SDL_Get_نمبر_Property(props, SDL_PROP_کھڑکی_WAYLAND_BORDER_INSET_چوٹی_نمبر, 0), 0, SDL_MAX_SINT16);
        insets->دایاں = (صحیح)SDL_clamp(SDL_Get_نمبر_Property(props, SDL_PROP_کھڑکی_WAYLAND_BORDER_INSET_دایاں_نمبر, 0), 0, SDL_MAX_SINT16);
        insets->bottom = (صحیح)SDL_clamp(SDL_Get_نمبر_Property(props, SDL_PROP_کھڑکی_WAYLAND_BORDER_INSET_BOTTOM_نمبر, 0), 0, SDL_MAX_SINT16);
    }
}

ساکن خالی سیٹ_Min_Max_Dimensions(SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *wind = کھڑکی->اندرونی_2;
    صحیح min_چوڑائی_2, min_اونچائی_2, max_چوڑائی_2, max_اونچائی_2;

    /* Keep the limits off while the window is in a fixed-size state, or the controls
     * to exit that state may be disabled.
     */
    اگر (کھڑکی->flags & (SDL_کھڑکی_FULLSCREEN | SDL_کھڑکی_MAXIMIZED)) {
        min_چوڑائی_2 = 0;
        min_اونچائی_2 = 0;
        max_چوڑائی_2 = 0;
        max_اونچائی_2 = 0;
    } ورنہ اگر (کھڑکی->flags & SDL_کھڑکی_RESIZABLE) {
        صحیح adj_w = SDL_max(کھڑکی->min_w, wind->system_limits.min_چوڑائی_2);
        صحیح adj_h = SDL_max(کھڑکی->min_h, wind->system_limits.min_اونچائی_2);
        اگر (wind->scale_مقصد_display) {
            adj_w = Pixel_مقصد_نقطہ(کھڑکی, adj_w);
            adj_h = Pixel_مقصد_نقطہ(کھڑکی, adj_h);
        }
        min_چوڑائی_2 = adj_w;
        min_اونچائی_2 = adj_h;

        adj_w = کھڑکی->max_w ? SDL_max(کھڑکی->max_w, wind->system_limits.min_چوڑائی_2) : 0;
        adj_h = کھڑکی->max_h ? SDL_max(کھڑکی->max_h, wind->system_limits.min_اونچائی_2) : 0;
        اگر (wind->scale_مقصد_display) {
            adj_w = Pixel_مقصد_نقطہ(کھڑکی, adj_w);
            adj_h = Pixel_مقصد_نقطہ(کھڑکی, adj_h);
        }
        max_چوڑائی_2 = adj_w;
        max_اونچائی_2 = adj_h;
    } ورنہ {
        min_چوڑائی_2 = wind->current.logical_چوڑائی;
        min_اونچائی_2 = wind->current.logical_اونچائی;
        max_چوڑائی_2 = wind->current.logical_چوڑائی;
        max_اونچائی_2 = wind->current.logical_اونچائی;
    }

#اگر_تعریف_شدہ HAVE_LIBDECOR_H
    اگر (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        اگر (!wind->shell_surface.libdecor.چوکھٹا) {
            واپس; // Can't do anything yet, wait for ShowWindow
        }

        اگر (min_چوڑائی_2 && min_اونچائی_2 && min_چوڑائی_2 == max_چوڑائی_2 && min_اونچائی_2 == max_اونچائی_2) {
            libdecor_چوکھٹا_unset_capabilities(wind->shell_surface.libdecor.چوکھٹا, LIBDECOR_ACTION_RESIZE);
        } ورنہ {
            libdecor_چوکھٹا_سیٹ_capabilities(wind->shell_surface.libdecor.چوکھٹا, LIBDECOR_ACTION_RESIZE);
        }

        /* No need to change these values if the window is non-resizable,
         * as libdecor will just overwrite them internally.
         */
        اگر (libdecor_چوکھٹا_has_capability(wind->shell_surface.libdecor.چوکھٹا, LIBDECOR_ACTION_RESIZE)) {
            libdecor_چوکھٹا_سیٹ_min_content_سائز(wind->shell_surface.libdecor.چوکھٹا,
                                                min_چوڑائی_2,
                                                min_اونچائی_2);
            libdecor_چوکھٹا_سیٹ_max_content_سائز(wind->shell_surface.libdecor.چوکھٹا,
                                                max_چوڑائی_2,
                                                max_اونچائی_2);
        }
    } ورنہ
#اگر_ختم
        اگر (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        اگر (!wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            واپس; // Can't do anything yet, wait for ShowWindow
        }
        /* The limits are in window geometry space; keep an existing minimum at 1 or more,
         * or the window can be spuriously closed.
         */
        BorderInsets insets;
        GetBorderInsets(کھڑکی, &insets);
        min_چوڑائی_2 = SDL_max(min_چوڑائی_2 - (insets.بایاں + insets.دایاں), min_چوڑائی_2 ? 1 : 0);
        min_اونچائی_2 = SDL_max(min_اونچائی_2 - (insets.چوٹی + insets.bottom), min_اونچائی_2 ? 1 : 0);
        اگر (max_چوڑائی_2) {
            max_چوڑائی_2 = SDL_max(max_چوڑائی_2 - (insets.بایاں + insets.دایاں), 1);
        }
        اگر (max_اونچائی_2) {
            max_اونچائی_2 = SDL_max(max_اونچائی_2 - (insets.چوٹی + insets.bottom), 1);
        }
        xdg_toplevel_سیٹ_min_سائز(wind->shell_surface.xdg.toplevel.xdg_toplevel,
                                  min_چوڑائی_2,
                                  min_اونچائی_2);
        xdg_toplevel_سیٹ_max_سائز(wind->shell_surface.xdg.toplevel.xdg_toplevel,
                                  max_چوڑائی_2,
                                  max_اونچائی_2);
    }
}

ساکن خالی EnsurePopupPositionIsValid(SDL_کھڑکی *کھڑکی, صحیح *x, صحیح *y)
{
    صحیح adj_گنتی = 0;

    /* Per the xdg-positioner spec, child popup windows must intersect or at
     * least be partially adjoining the parent window.
     *
     * Failure to ensure this on a compositor that enforces this restriction
     * can result in behavior ranging from the window being spuriously closed
     * to a protocol violation.
     */
    اگر (*x + کھڑکی->w <= 0) {
        *x = -کھڑکی->w;
        ++adj_گنتی;
    }
    اگر (*y + کھڑکی->h <= 0) {
        *y = -کھڑکی->h;
        ++adj_گنتی;
    }
    اگر (*x >= کھڑکی->والد->w) {
        *x = کھڑکی->والد->w;
        ++adj_گنتی;
    }
    اگر (*y >= کھڑکی->والد->h) {
        *y = کھڑکی->والد->h;
        ++adj_گنتی;
    }

    /* If adjustment was required on the x and y axes, the popup is aligned with
     * the parent corner-to-corner and is neither overlapping nor adjoining, so it
     * must be nudged by 1 to be considered adjoining.
     */
    اگر (adj_گنتی > 1) {
        *x += *x < 0 ? 1 : -1;
    }
}

// The window geometry: the explicitly set one, or the full surface if SDL has never set it.
ساکن خالی Get_کھڑکی_Geometry(SDL_کھڑکی_ڈیٹا *wind, SDL_Rect *geometry)
{
    *geometry = wind->explicit_geometry;
    اگر (SDL_Rect_خالی_خانے(geometry)) {
        geometry->x = 0;
        geometry->y = 0;
        geometry->w = wind->current.logical_چوڑائی;
        geometry->h = wind->current.logical_اونچائی;
    }
}

ساکن خالی Adjust_Popup_انحراف(SDL_کھڑکی *popup, صحیح *x, صحیح *y)
{
    // Positioner offsets are relative to the origin of the parent's window geometry.
#اگر_تعریف_شدہ HAVE_LIBDECOR_H
    اگر (popup->والد->اندرونی_2->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        صحیح adj_x, adj_y;
        libdecor_چوکھٹا_translate_coordinate(popup->والد->اندرونی_2->shell_surface.libdecor.چوکھٹا,
                                            *x, *y, &adj_x, &adj_y);
        *x = adj_x;
        *y = adj_y;
    } ورنہ
#اگر_ختم
    {
        *x -= popup->والد->اندرونی_2->explicit_geometry.x;
        *y -= popup->والد->اندرونی_2->explicit_geometry.y;
    }
}

ساکن خالی RepositionPopup(SDL_کھڑکی *کھڑکی, bool use_current_position)
{
    SDL_کھڑکی_ڈیٹا *wind = کھڑکی->اندرونی_2;

    اگر (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP &&
        wind->shell_surface.xdg.popup.xdg_positioner &&
        xdg_popup_get_نسخہ(wind->shell_surface.xdg.popup.xdg_popup) >= XDG_POPUP_REPOSITION_SINCE_نسخہ) {
        صحیح x = use_current_position ? کھڑکی->x : کھڑکی->pending.x;
        صحیح y = use_current_position ? کھڑکی->y : کھڑکی->pending.y;

        EnsurePopupPositionIsValid(کھڑکی, &x, &y);
        اگر (wind->scale_مقصد_display) {
            x = Pixel_مقصد_نقطہ(کھڑکی->والد, x);
            y = Pixel_مقصد_نقطہ(کھڑکی->والد, y);
        }
        Adjust_Popup_انحراف(کھڑکی, &x, &y);
        SDL_Rect والد_geometry;
        Get_کھڑکی_Geometry(کھڑکی->والد->اندرونی_2, &والد_geometry);
        xdg_positioner_سیٹ_anchor_rect(wind->shell_surface.xdg.popup.xdg_positioner, 0, 0, والد_geometry.w, والد_geometry.h);
        xdg_positioner_سیٹ_سائز(wind->shell_surface.xdg.popup.xdg_positioner, wind->current.logical_چوڑائی, wind->current.logical_اونچائی);
        xdg_positioner_سیٹ_انحراف(wind->shell_surface.xdg.popup.xdg_positioner, x, y);
        xdg_popup_reposition(wind->shell_surface.xdg.popup.xdg_popup,
                             wind->shell_surface.xdg.popup.xdg_positioner,
                             0);
    }
}

ساکن خالی سیٹ_Surface_Opaque_Region(ساخت wl_surface *surface, صحیح چوڑائی, صحیح اونچائی)
{
    SDL_Video_ڈیٹا *viddata = SDL_GetVideoDevice()->اندرونی_2;

    اگر (چوڑائی && اونچائی) {
        ساخت wl_region *region = wl_compositor_create_region(viddata->compositor);
        wl_region_جوڑو(region, 0, 0, چوڑائی, اونچائی);
        wl_surface_سیٹ_opaque_region(surface, region);
        wl_region_destroy(region);
    } ورنہ {
        wl_surface_سیٹ_opaque_region(surface, تہی);
    }
}

ساکن خالی Configure_کھڑکی_Geometry(SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    ثابت دوہرا scale_ضربی_عدد_2 = Get_کھڑکی_Scale(کھڑکی);
    ثابت دوہرا پچھلا_اشارہ_گر_scale_x = ڈیٹا->اشارہ_گر_scale.x;
    ثابت دوہرا پچھلا_اشارہ_گر_scale_y = ڈیٹا->اشارہ_گر_scale.y;
    ثابت صحیح old_pixel_چوڑائی = ڈیٹا->current.pixel_چوڑائی;
    ثابت صحیح old_pixel_اونچائی = ڈیٹا->current.pixel_اونچائی;
    صحیح کھڑکی_چوڑائی = 0;
    صحیح کھڑکی_اونچائی = 0;
    صحیح viewport_چوڑائی, viewport_اونچائی;
    bool کھڑکی_سائز_بدلا;
    bool بفر_سائز_بدلا;
    ثابت bool is_opaque = !(کھڑکی->flags & SDL_کھڑکی_TRANSPARENT) && کھڑکی->opacity == 1.0f;

    اگر (ڈیٹا->is_fullscreen && کھڑکی->fullscreen_exclusive) {
        کھڑکی_چوڑائی = کھڑکی->current_fullscreen_منوال.w;
        کھڑکی_اونچائی = کھڑکی->current_fullscreen_منوال.h;

        viewport_چوڑائی = ڈیٹا->requested.logical_چوڑائی;
        viewport_اونچائی = ڈیٹا->requested.logical_اونچائی;

        انتخاب (Get_منوال_Scale_طریقہ()) {
        حالت WAYLAND_منوال_SCALE_NONE:
            /* The Wayland spec states that the advertised fullscreen dimensions are a maximum.
             * Windows can request a smaller size, but exceeding these dimensions is a protocol violation,
             * thus, modes that exceed the output size still need to be scaled with a viewport.
             */
            اگر (کھڑکی_چوڑائی <= viewport_چوڑائی && کھڑکی_اونچائی <= viewport_اونچائی) {
                viewport_چوڑائی = کھڑکی_چوڑائی;
                viewport_اونچائی = کھڑکی_اونچائی;

                توڑو;
            }
            SDL_FALLTHROUGH;
        حالت WAYLAND_منوال_SCALE_ASPECT:
        {
            ثابت اعشاری output_تناسب = (اعشاری)viewport_چوڑائی / (اعشاری)viewport_اونچائی;
            ثابت اعشاری منوال_تناسب = (اعشاری)کھڑکی_چوڑائی / (اعشاری)کھڑکی_اونچائی;

            اگر (output_تناسب > منوال_تناسب) {
                viewport_چوڑائی = SDL_lroundf((اعشاری)کھڑکی_چوڑائی * ((اعشاری)viewport_اونچائی / (اعشاری)کھڑکی_اونچائی));
            } ورنہ اگر (output_تناسب < منوال_تناسب) {
                viewport_اونچائی = SDL_lroundf((اعشاری)کھڑکی_اونچائی * ((اعشاری)viewport_چوڑائی / (اعشاری)کھڑکی_چوڑائی));
            }
        } توڑو;
        طےشدہ:
            توڑو;
        }

        کھڑکی_سائز_بدلا = کھڑکی_چوڑائی != کھڑکی->w ||
                              کھڑکی_اونچائی != کھڑکی->h ||
                              ڈیٹا->current.viewport_چوڑائی != viewport_چوڑائی ||
                              ڈیٹا->current.viewport_اونچائی != viewport_اونچائی;

        // Exclusive fullscreen window sizes are always in pixel units.
        ڈیٹا->current.pixel_چوڑائی = کھڑکی_چوڑائی;
        ڈیٹا->current.pixel_اونچائی = کھڑکی_اونچائی;
        بفر_سائز_بدلا = ڈیٹا->current.pixel_چوڑائی != old_pixel_چوڑائی ||
                              ڈیٹا->current.pixel_اونچائی != old_pixel_اونچائی;

        اگر (کھڑکی_سائز_بدلا || بفر_سائز_بدلا) {
            اگر (ڈیٹا->viewport) {
                wp_viewport_سیٹ_destination(ڈیٹا->viewport, viewport_چوڑائی, viewport_اونچائی);

                ڈیٹا->current.logical_چوڑائی = ڈیٹا->requested.logical_چوڑائی;
                ڈیٹا->current.logical_اونچائی = ڈیٹا->requested.logical_اونچائی;
                ڈیٹا->current.viewport_چوڑائی = viewport_چوڑائی;
                ڈیٹا->current.viewport_اونچائی = viewport_اونچائی;
            } ورنہ {
                // Calculate the integer scale from the mode and output.
                ثابت int32_t int_scale = SDL_max(کھڑکی->current_fullscreen_منوال.w / viewport_چوڑائی, 1);

                wl_surface_سیٹ_بفر_scale(ڈیٹا->surface, int_scale);
                ڈیٹا->current.logical_چوڑائی = کھڑکی->current_fullscreen_منوال.w;
                ڈیٹا->current.logical_اونچائی = کھڑکی->current_fullscreen_منوال.h;
            }

            ڈیٹا->اشارہ_گر_scale.x = (دوہرا)کھڑکی_چوڑائی / (دوہرا)viewport_چوڑائی;
            ڈیٹا->اشارہ_گر_scale.y = (دوہرا)کھڑکی_اونچائی / (دوہرا)viewport_اونچائی;
        }
    } ورنہ {
        اگر (!ڈیٹا->scale_مقصد_display) {
            viewport_چوڑائی = ڈیٹا->requested.logical_چوڑائی;
            viewport_اونچائی = ڈیٹا->requested.logical_اونچائی;
        } ورنہ {
            viewport_چوڑائی = ڈیٹا->requested.pixel_چوڑائی;
            viewport_اونچائی = ڈیٹا->requested.pixel_اونچائی;
        }

        اگر (!ڈیٹا->enable_insets &&
            ڈیٹا->shell_surface_حالت != WAYLAND_SHELL_SURFACE_حالت_HIDDEN &&
            ڈیٹا->viewport && ڈیٹا->wayland_ڈیٹا->subcompositor && !ڈیٹا->floating && !ڈیٹا->is_fullscreen) {
            صحیح min_چوڑائی_2, min_اونچائی_2, max_چوڑائی_2, max_اونچائی_2;
            اگر (کھڑکی->flags & SDL_کھڑکی_RESIZABLE) {
                min_چوڑائی_2 = کھڑکی->min_w;
                min_اونچائی_2 = کھڑکی->min_h;
                max_چوڑائی_2 = کھڑکی->max_w;
                max_اونچائی_2 = کھڑکی->max_h;
            } ورنہ {
                // Use the fixed size in the odd case where a non-resizable window somehow wound up tiled or maximized.
                min_چوڑائی_2 = کھڑکی->floating.w;
                min_اونچائی_2 = کھڑکی->floating.h;
                max_چوڑائی_2 = کھڑکی->floating.w;
                max_اونچائی_2 = کھڑکی->floating.h;
            }

            اگر (min_چوڑائی_2) {
                viewport_چوڑائی = SDL_max(viewport_چوڑائی, min_چوڑائی_2);
            }
            اگر (min_اونچائی_2) {
                viewport_اونچائی = SDL_max(viewport_اونچائی, min_اونچائی_2);
            }
            اگر (max_چوڑائی_2) {
                viewport_چوڑائی = SDL_min(viewport_چوڑائی, max_چوڑائی_2);
            }
            اگر (max_اونچائی_2) {
                viewport_اونچائی = SDL_min(viewport_اونچائی, max_اونچائی_2);
            }

            اعشاری aspect = (اعشاری)viewport_چوڑائی / (اعشاری)viewport_اونچائی;
            اگر (کھڑکی->min_aspect != 0.f && aspect < کھڑکی->min_aspect) {
                viewport_اونچائی = SDL_max(SDL_lroundf((اعشاری)viewport_چوڑائی / کھڑکی->min_aspect), 1);
            } ورنہ اگر (کھڑکی->max_aspect != 0.f && aspect > کھڑکی->max_aspect) {
                viewport_چوڑائی = SDL_max(SDL_lroundf((اعشاری)viewport_اونچائی * کھڑکی->max_aspect), 1);
            }

            // At this point, the viewport matches the virtual window dimensions, but the viewport might be clamped to the output window dimensions beyond here.
            کھڑکی_چوڑائی = viewport_چوڑائی;
            کھڑکی_اونچائی = viewport_اونچائی;

            // If the viewport bounds exceed the window size, scale them while maintaining the aspect ratio.
            اگر (!ڈیٹا->scale_مقصد_display) {
                اگر (viewport_چوڑائی > ڈیٹا->requested.logical_چوڑائی || viewport_اونچائی > ڈیٹا->requested.logical_اونچائی) {
                    aspect = (اعشاری)viewport_چوڑائی / (اعشاری)viewport_اونچائی;
                    ثابت اعشاری کھڑکی_تناسب = (اعشاری)ڈیٹا->requested.logical_چوڑائی / (اعشاری)ڈیٹا->requested.logical_اونچائی;
                    اگر (aspect >= کھڑکی_تناسب) {
                        viewport_چوڑائی = ڈیٹا->requested.logical_چوڑائی;
                        viewport_اونچائی = SDL_lroundf((اعشاری)viewport_چوڑائی / aspect);
                    } ورنہ اگر (aspect < کھڑکی_تناسب) {
                        viewport_اونچائی = ڈیٹا->requested.logical_اونچائی;
                        viewport_چوڑائی = SDL_lroundf((اعشاری)viewport_اونچائی * aspect);
                    }
                }
            } ورنہ {
                اگر (viewport_چوڑائی > ڈیٹا->requested.pixel_چوڑائی || viewport_اونچائی > ڈیٹا->requested.pixel_اونچائی) {
                    aspect = (اعشاری)viewport_چوڑائی / (اعشاری)viewport_اونچائی;
                    ثابت اعشاری کھڑکی_تناسب = (اعشاری)ڈیٹا->requested.pixel_چوڑائی / (اعشاری)ڈیٹا->requested.pixel_اونچائی;
                    اگر (aspect >= کھڑکی_تناسب) {
                        viewport_چوڑائی = ڈیٹا->requested.pixel_چوڑائی;
                        viewport_اونچائی = SDL_lroundf((اعشاری)viewport_چوڑائی / aspect);
                    } ورنہ اگر (aspect < کھڑکی_تناسب) {
                        viewport_اونچائی = ڈیٹا->requested.pixel_اونچائی;
                        viewport_چوڑائی = SDL_lroundf((اعشاری)viewport_اونچائی * aspect);
                    }
                }
            }

            viewport_چوڑائی = SDL_max(viewport_چوڑائی, 1);
            viewport_اونچائی = SDL_max(viewport_اونچائی, 1);
        } ورنہ {
            کھڑکی_چوڑائی = viewport_چوڑائی;
            کھڑکی_اونچائی = viewport_اونچائی;
        }

        اگر (!ڈیٹا->scale_مقصد_display) {
            ڈیٹا->current.pixel_چوڑائی = نقطہ_مقصد_Pixel(کھڑکی, کھڑکی_چوڑائی);
            ڈیٹا->current.pixel_اونچائی = نقطہ_مقصد_Pixel(کھڑکی, کھڑکی_اونچائی);
        } ورنہ {
            // The viewport size is in pixels at this point; convert it to logical units.
            ڈیٹا->current.pixel_چوڑائی = کھڑکی_چوڑائی;
            ڈیٹا->current.pixel_اونچائی = کھڑکی_اونچائی;
            viewport_چوڑائی = Pixel_مقصد_نقطہ(کھڑکی, viewport_چوڑائی);
            viewport_اونچائی = Pixel_مقصد_نقطہ(کھڑکی, viewport_اونچائی);
        }

        // Clamp the physical window size to the system minimum required size.
        ڈیٹا->requested.logical_چوڑائی = SDL_max(ڈیٹا->requested.logical_چوڑائی, ڈیٹا->system_limits.min_چوڑائی_2);
        ڈیٹا->requested.logical_اونچائی = SDL_max(ڈیٹا->requested.logical_اونچائی, ڈیٹا->system_limits.min_اونچائی_2);

        کھڑکی_سائز_بدلا = ڈیٹا->requested.logical_چوڑائی != ڈیٹا->current.logical_چوڑائی ||
                              ڈیٹا->requested.logical_اونچائی != ڈیٹا->current.logical_اونچائی ||
                              viewport_چوڑائی != ڈیٹا->current.viewport_چوڑائی ||
                              viewport_اونچائی != ڈیٹا->current.viewport_اونچائی;

        بفر_سائز_بدلا = ڈیٹا->current.pixel_چوڑائی != old_pixel_چوڑائی ||
                              ڈیٹا->current.pixel_اونچائی != old_pixel_اونچائی;

        اگر (کھڑکی_سائز_بدلا || بفر_سائز_بدلا) {
            اگر (ڈیٹا->viewport) {
                wp_viewport_سیٹ_destination(ڈیٹا->viewport, viewport_چوڑائی, viewport_اونچائی);
            } ورنہ اگر (کھڑکی->flags & SDL_کھڑکی_بلند_PIXEL_DENSITY) {
                // Don't change this if the DPI awareness flag is unset, as an application may have set this manually on a custom or external surface.
                wl_surface_سیٹ_بفر_scale(ڈیٹا->surface, (int32_t)scale_ضربی_عدد_2);
            }

            ڈیٹا->current.logical_چوڑائی = ڈیٹا->requested.logical_چوڑائی;
            ڈیٹا->current.logical_اونچائی = ڈیٹا->requested.logical_اونچائی;
            ڈیٹا->current.viewport_چوڑائی = viewport_چوڑائی;
            ڈیٹا->current.viewport_اونچائی = viewport_اونچائی;

            ڈیٹا->اشارہ_گر_scale.x = (دوہرا)کھڑکی_چوڑائی / (دوہرا)viewport_چوڑائی;
            ڈیٹا->اشارہ_گر_scale.y = (دوہرا)کھڑکی_اونچائی / (دوہرا)viewport_اونچائی;
        }
    }

    اگر (ڈیٹا->egl_کھڑکی && بفر_سائز_بدلا) {
        WAYLAND_wl_egl_کھڑکی_resize(ڈیٹا->egl_کھڑکی,
                                     ڈیٹا->current.pixel_چوڑائی,
                                     ڈیٹا->current.pixel_اونچائی,
                                     0, 0);
    }

    /* Calculate the mask size and offset.
     * Fullscreen windows are centered and masked automatically by the compositor, unless it lacks the capability.
     */
    اگر (!ڈیٹا->enable_insets && ڈیٹا->viewport && ڈیٹا->wayland_ڈیٹا->subcompositor && (!ڈیٹا->is_fullscreen || Should_نقاب_Fullscreen()) &&
        (viewport_چوڑائی != ڈیٹا->current.logical_چوڑائی || viewport_اونچائی != ڈیٹا->current.logical_اونچائی)) {
        ساخت wl_بفر *old_بفر = تہی;

        اگر (!ڈیٹا->نقاب.surface) {
            ڈیٹا->نقاب.surface = wl_compositor_create_surface(ڈیٹا->wayland_ڈیٹا->compositor);
            SDL_WAYLAND_رجسٹر_surface(ڈیٹا->نقاب.surface);
            wl_surface_سیٹ_user_ڈیٹا(ڈیٹا->نقاب.surface, ڈیٹا);
        }
        اگر (!ڈیٹا->نقاب.subsurface) {
            ڈیٹا->نقاب.subsurface = wl_subcompositor_get_subsurface(ڈیٹا->wayland_ڈیٹا->subcompositor, ڈیٹا->نقاب.surface, ڈیٹا->surface);
        }
        اگر (!ڈیٹا->نقاب.viewport) {
            ڈیٹا->نقاب.viewport = wp_viewporter_get_viewport(ڈیٹا->wayland_ڈیٹا->viewporter, ڈیٹا->نقاب.surface);
        }
        اگر (!ڈیٹا->نقاب.بفر_2 || ڈیٹا->نقاب.opaque != is_opaque) {
            old_بفر = ڈیٹا->نقاب.بفر_2;
            ڈیٹا->نقاب.opaque = is_opaque;
            ڈیٹا->نقاب.بفر_2 = Wayland_Create_Single_Pixel_بفر(0, 0, 0, is_opaque ? SDL_MAX_UINT32 : 0);
        }

        wl_surface_attach(ڈیٹا->نقاب.surface, ڈیٹا->نقاب.بفر_2, 0, 0);

        wl_subsurface_رکھو_نیچے(ڈیٹا->نقاب.subsurface, ڈیٹا->surface);
        wp_viewport_سیٹ_destination(ڈیٹا->نقاب.viewport, ڈیٹا->current.logical_چوڑائی, ڈیٹا->current.logical_اونچائی);

        اگر (wl_surface_get_نسخہ(ڈیٹا->نقاب.surface) >= WL_SURFACE_DAMAGE_بفر_SINCE_نسخہ) {
            wl_surface_damage_بفر(ڈیٹا->نقاب.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        } ورنہ {
            wl_surface_damage(ڈیٹا->نقاب.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        }

        اگر (is_opaque) {
            سیٹ_Surface_Opaque_Region(ڈیٹا->نقاب.surface, ڈیٹا->current.logical_چوڑائی, ڈیٹا->current.logical_اونچائی);
        } ورنہ {
            سیٹ_Surface_Opaque_Region(ڈیٹا->نقاب.surface, 0, 0);
        }

        // Can't use an offset subsurface with libdecor (yet), or the decorations won't line up properly.
        اگر (ڈیٹا->shell_surface_type != WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
            ڈیٹا->نقاب.انحراف_x = -(ڈیٹا->current.logical_چوڑائی - viewport_چوڑائی) / 2;
            ڈیٹا->نقاب.انحراف_y = -(ڈیٹا->current.logical_اونچائی - viewport_اونچائی) / 2;
        } ورنہ {
            ڈیٹا->نقاب.انحراف_x = 0;
            ڈیٹا->نقاب.انحراف_y = 0;
        }

        wl_subsurface_سیٹ_position(ڈیٹا->نقاب.subsurface, ڈیٹا->نقاب.انحراف_x, ڈیٹا->نقاب.انحراف_y);
        wl_surface_commit(ڈیٹا->نقاب.surface);

        اگر (old_بفر) {
            wl_بفر_destroy(old_بفر);
        }

        ڈیٹا->نقاب.mapped = true;
    } ورنہ اگر (ڈیٹا->نقاب.mapped) {
        wl_subsurface_سیٹ_position(ڈیٹا->نقاب.subsurface, 0, 0);
        wl_surface_attach(ڈیٹا->نقاب.surface, تہی, 0, 0);
        wl_surface_commit(ڈیٹا->نقاب.surface);

        ڈیٹا->نقاب.انحراف_x = 0;
        ڈیٹا->نقاب.انحراف_y = 0;
        ڈیٹا->نقاب.mapped = false;
    }

    اگر (ڈیٹا->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && ڈیٹا->shell_surface.xdg.surface &&
        (ڈیٹا->enable_insets || !ڈیٹا->viewport)) {
        /* The window geometry is the surface minus the declared border insets. They don't apply
         * when an exact size is required (maximized/fullscreen).
         */
        BorderInsets insets;
        GetBorderInsets(کھڑکی, &insets);
        ثابت bool use_insets = (insets.بایاں || insets.چوٹی || insets.دایاں || insets.bottom) &&
                                !(کھڑکی->flags & (SDL_کھڑکی_MAXIMIZED | SDL_کھڑکی_FULLSCREEN));
        SDL_Rect geometry = { 0, 0, ڈیٹا->current.logical_چوڑائی, ڈیٹا->current.logical_اونچائی };
        اگر (use_insets) {
            geometry.x = insets.بایاں;
            geometry.y = insets.چوٹی;
            geometry.w = SDL_max(geometry.w - (insets.بایاں + insets.دایاں), 1);
            geometry.h = SDL_max(geometry.h - (insets.چوٹی + insets.bottom), 1);
        }
        /* An explicitly set geometry does not track the surface, so it must be kept in sync
         * once set. Otherwise this is only done when viewports aren't supported and the size
         * has changed (XXX: a hack) to avoid a potential protocol violation if a buffer with
         * an old size is committed.
         */
        اگر ((use_insets || !SDL_Rect_خالی_خانے(&ڈیٹا->explicit_geometry) || (!ڈیٹا->viewport && کھڑکی_سائز_بدلا)) &&
            !SDL_RectsEqual(&geometry, &ڈیٹا->explicit_geometry)) {
            xdg_surface_سیٹ_کھڑکی_geometry(ڈیٹا->shell_surface.xdg.surface, geometry.x, geometry.y, geometry.w, geometry.h);
            ڈیٹا->explicit_geometry = geometry;
        }
    }

    /* The opaque region and pointer confinement region only need to be
     * recalculated if the output size has changed.
     */
    اگر (کھڑکی_سائز_بدلا) {
        اگر (is_opaque) {
            سیٹ_Surface_Opaque_Region(ڈیٹا->surface, viewport_چوڑائی, viewport_اونچائی);
        } ورنہ {
            سیٹ_Surface_Opaque_Region(ڈیٹا->surface, 0, 0);
        }

        // Ensure that child popup windows are still in bounds.
        برائے (SDL_کھڑکی *بچہ = کھڑکی->پہلا_بچہ; بچہ; بچہ = بچہ->اگلا_sibling) {
            RepositionPopup(بچہ, true);
        }
    }

    // Update the scale for any focused cursors.
    اگر (پچھلا_اشارہ_گر_scale_x != ڈیٹا->اشارہ_گر_scale.x || پچھلا_اشارہ_گر_scale_y != ڈیٹا->اشارہ_گر_scale.y) {
        Wayland_Display_Update_اشارہ_گر_Focused_Scale(ڈیٹا);
    }

    /* Update the min/max dimensions, primarily if the state was changed, and for non-resizable
     * xdg-toplevel windows where the limits should match the window size.
     */
    سیٹ_Min_Max_Dimensions(کھڑکی);

    // Unconditionally send the window and drawable size, the video core will deduplicate when required.
    اگر (!ڈیٹا->scale_مقصد_display) {
        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESIZED, کھڑکی_چوڑائی, کھڑکی_اونچائی);
    } ورنہ {
        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESIZED, ڈیٹا->current.pixel_چوڑائی, ڈیٹا->current.pixel_اونچائی);
    }
    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_PIXEL_سائز_بدلا, ڈیٹا->current.pixel_چوڑائی, ڈیٹا->current.pixel_اونچائی);

    /* Send an exposure event if the window is in the shown state and the size has changed,
     * even if the window is occluded, as the client needs to commit a new frame for the
     * changes to take effect.
     *
     * The occlusion state is immediately set again afterward, if necessary.
     */
    اگر (ڈیٹا->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_SHOWN) {
        اگر ((بفر_سائز_بدلا || کھڑکی_سائز_بدلا) ||
            (!ڈیٹا->suspended && (کھڑکی->flags & SDL_کھڑکی_OCCLUDED))) {
            SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_EXPOSED, 0, 0);
        }

        اگر (ڈیٹا->suspended) {
            SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_OCCLUDED, 0, 0);
        }
    }
}

ساکن خالی Commit_Libdecor_چوکھٹا(SDL_کھڑکی *کھڑکی)
{
#اگر_تعریف_شدہ HAVE_LIBDECOR_H
    SDL_کھڑکی_ڈیٹا *wind = کھڑکی->اندرونی_2;

    اگر (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.چوکھٹا) {
        ساخت libdecor_state *state = libdecor_state_new(wind->current.logical_چوڑائی, wind->current.logical_اونچائی);
        libdecor_چوکھٹا_commit(wind->shell_surface.libdecor.چوکھٹا, state, تہی);
        libdecor_state_free(state);
    }
#اگر_ختم
}

ساکن خالی pending_state_deadline_handler(خالی *ڈیٹا, ساخت wl_callback *callback, uint32_t callback_ڈیٹا)
{
    // Get the window from the ID, as it may have been destroyed.
    SDL_کھڑکی_ID کھڑکی_ID = (SDL_کھڑکی_ID)(uintptr_t)ڈیٹا;
    SDL_کھڑکی *کھڑکی = SDL_Get_کھڑکی_From_ID(کھڑکی_ID);

    اگر (کھڑکی && کھڑکی->اندرونی_2) {
        --کھڑکی->اندرونی_2->pending_state_deadline_گنتی;
    }

    wl_callback_destroy(callback);
}

ساکن ساخت wl_callback_listener pending_state_deadline_listener = {
    pending_state_deadline_handler
};

ساکن خالی جوڑو_Pending_State_Sync(SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2)
{
    SDL_Video_ڈیٹا *video_ڈیٹا = کھڑکی_ڈیٹا_2->wayland_ڈیٹا;
    خالی *cb_ڈیٹا = (خالی *)(uintptr_t)کھڑکی_ڈیٹا_2->sdlwindow->id;

    ++کھڑکی_ڈیٹا_2->pending_state_deadline_گنتی;
    ساخت wl_callback *cb = wl_display_sync(video_ڈیٹا->display);
    wl_callback_جوڑو_listener(cb, &pending_state_deadline_listener, cb_ڈیٹا);
}

ساکن خالی FlushPendingEvents(SDL_کھڑکی *کھڑکی)
{
    // Serialize and restore the pending flags, as they may be overwritten while flushing.
    ثابت bool آخری_position_pending = کھڑکی->آخری_position_pending;
    ثابت bool آخری_سائز_pending = کھڑکی->آخری_سائز_pending;

    جب (کھڑکی->اندرونی_2->pending_state_deadline_گنتی) {
        WAYLAND_wl_display_roundtrip(کھڑکی->اندرونی_2->wayland_ڈیٹا->display);
    }

    کھڑکی->آخری_position_pending = آخری_position_pending;
    کھڑکی->آخری_سائز_pending = آخری_سائز_pending;
}

/* While we can't get window position from the compositor, we do at least know
 * what monitor we're on, so let's send move events that put the window at the
 * center of the whatever display the wl_surface_listener events give us.
 */
خالی Wayland_Update_کھڑکی_Position(SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *wind = کھڑکی->اندرونی_2;
    SDL_Display_ڈیٹا *display;

    اگر (wind->outputs && wind->عدد_outputs) {
        display = wind->outputs[wind->عدد_outputs - 1];
    } ورنہ {
        // A window may not be on any displays if minimized.
        واپس;
    }

    /* We want to send a very very specific combination here:
     *
     * 1. A coordinate that tells the application what display we're on
     * 2. Exactly (0, 0)
     *
     * Part 1 is useful information but is also really important for
     * ensuring we end up on the right display for fullscreen, while
     * part 2 is important because numerous applications use a specific
     * combination of GetWindowPosition and GetGlobalMouseState, and of
     * course neither are supported by Wayland. Since global mouse will
     * fall back to just GetMouseState, we need the window position to
     * be zero so the cursor math works without it going off in some
     * random direction. See UE5 Editor for a notable example of this!
     *
     * This may be an issue some day if we're ever able to implement
     * SDL_GetDisplayUsableBounds!
     *
     * -flibit
     */
    wind->آخری_display_ID = display->display;
    اگر (wind->shell_surface_type != WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        اگر (!wind->wayland_ڈیٹا->scale_مقصد_display_enabled) {
            SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_MOVED, display->logical.x, display->logical.y);
        } ورنہ {
            SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_MOVED, display->pixel.x, display->pixel.y);
        }
        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_DISPLAY_بدلا, wind->آخری_display_ID, 0);
    }
}

ساکن خالی سیٹ_Fullscreen(SDL_کھڑکی *کھڑکی, ساخت wl_output *output, bool fullscreen)
{
    SDL_کھڑکی_ڈیٹا *wind = کھڑکی->اندرونی_2;

#اگر_تعریف_شدہ HAVE_LIBDECOR_H
    اگر (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        اگر (!wind->shell_surface.libdecor.چوکھٹا) {
            واپس; // Can't do anything yet, wait for ShowWindow
        }

        wind->fullscreen_exclusive = output ? کھڑکی->fullscreen_exclusive : false;
        اگر (fullscreen) {
            libdecor_چوکھٹا_سیٹ_fullscreen(wind->shell_surface.libdecor.چوکھٹا, output);
        } ورنہ {
            libdecor_چوکھٹا_unset_fullscreen(wind->shell_surface.libdecor.چوکھٹا);
        }
    } ورنہ
#اگر_ختم
        اگر (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        اگر (wind->shell_surface.xdg.toplevel.xdg_toplevel == تہی) {
            واپس; // Can't do anything yet, wait for ShowWindow
        }

        wind->fullscreen_exclusive = output ? کھڑکی->fullscreen_exclusive : false;
        اگر (fullscreen) {
            xdg_toplevel_سیٹ_fullscreen(wind->shell_surface.xdg.toplevel.xdg_toplevel, output);
        } ورنہ {
            xdg_toplevel_unset_fullscreen(wind->shell_surface.xdg.toplevel.xdg_toplevel);
        }
    }

    جوڑو_Pending_State_Sync(wind);
}

ساکن خالی Update_کھڑکی_Fullscreen(SDL_کھڑکی *کھڑکی, bool fullscreen)
{
    SDL_کھڑکی_ڈیٹا *wind = کھڑکی->اندرونی_2;

    wind->is_fullscreen = fullscreen;

    اگر (fullscreen) {
        اگر (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
            SDL_copyp(&کھڑکی->current_fullscreen_منوال, &کھڑکی->requested_fullscreen_منوال);
            SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_ENTER_FULLSCREEN, 0, 0);
            SDL_Update_Fullscreen_منوال(کھڑکی, SDL_FULLSCREEN_OP_ENTER, false);

            /* Set the output for exclusive fullscreen windows when entering fullscreen from a
             * compositor event, or if the fullscreen parameters were changed between the initial
             * fullscreen request and now, to ensure that the window is on the correct output,
             * as requested by the client.
             */
            اگر (کھڑکی->fullscreen_exclusive && (!wind->fullscreen_exclusive || !wind->fullscreen_was_positioned)) {
                SDL_VideoDisplay *disp = SDL_GetVideoDisplay(کھڑکی->current_fullscreen_منوال.displayID);
                اگر (disp) {
                    wind->fullscreen_was_positioned = true;
                    سیٹ_Fullscreen(کھڑکی, disp->اندرونی_2->output, true);
                }
            }
        }
    } ورنہ {
        // Don't change the fullscreen flags if the window is hidden or being hidden.
        اگر ((کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) && !کھڑکی->is_hiding && !(کھڑکی->flags & SDL_کھڑکی_HIDDEN)) {
            SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_LEAVE_FULLSCREEN, 0, 0);
            SDL_Update_Fullscreen_منوال(کھڑکی, SDL_FULLSCREEN_OP_LEAVE, false);
            wind->fullscreen_was_positioned = false;

            /* Send a move event, in case it was deferred while the fullscreen window was moving and
             * on multiple outputs.
             */
            Wayland_Update_کھڑکی_Position(کھڑکی);
        }
    }
}

ساکن ثابت ساخت wl_callback_listener surface_چوکھٹا_listener;

ساکن خالی surface_چوکھٹا_مکمل(خالی *ڈیٹا, ساخت wl_callback *cb, uint32_t وقت)
{
    SDL_کھڑکی_ڈیٹا *wind = (SDL_کھڑکی_ڈیٹا *)ڈیٹا;

    /* XXX: This is needed to work around an Nvidia egl-wayland bug due to buffer coordinates
     *      being used with wl_surface_damage, which causes part of the output to not be
     *      updated when using a viewport with an output region larger than the source region.
     */
    اگر (wl_compositor_get_نسخہ(wind->wayland_ڈیٹا->compositor) >= WL_SURFACE_DAMAGE_بفر_SINCE_نسخہ) {
        wl_surface_damage_بفر(wind->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    } ورنہ {
        wl_surface_damage(wind->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    }

    wind->pending_state_commit = false;

    اگر (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        اگر (wind->pending_config_ack) {
            wind->pending_config_ack = false;
            Configure_کھڑکی_Geometry(wind->sdlwindow);
            xdg_surface_ack_configure(wind->shell_surface.xdg.surface, wind->shell_surface.xdg.serial);
        }
    } ورنہ {
        wind->resizing = false;
    }

    اگر (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_چوکھٹا) {
        wind->shell_surface_حالت = WAYLAND_SHELL_SURFACE_حالت_SHOWN;

        // If any child windows are waiting on this window to be shown, show them now
        برائے (SDL_کھڑکی *w = wind->sdlwindow->پہلا_بچہ; w; w = w->اگلا_sibling) {
            اگر (w->اندرونی_2->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_SHOW_PENDING) {
                Wayland_Show_کھڑکی(SDL_GetVideoDevice(), w);
            } ورنہ اگر (w->اندرونی_2->reparenting_required) {
                Wayland_سیٹ_کھڑکی_والد(SDL_GetVideoDevice(), w, w->والد);
                اگر (w->flags & SDL_کھڑکی_MODAL) {
                    Wayland_سیٹ_کھڑکی_Modal(SDL_GetVideoDevice(), w, true);
                }
            }
        }

        /* If the window was initially set to the suspended state, send the occluded event now,
         * as we don't want to mark the window as occluded until at least one frame has been submitted.
         */
        اگر (wind->suspended) {
            SDL_Send_کھڑکی_Event(wind->sdlwindow, SDL_EVENT_کھڑکی_OCCLUDED, 0, 0);
        }
    }

    wl_callback_destroy(cb);
    wind->surface_چوکھٹا_callback = wl_surface_چوکھٹا(wind->surface);
    wl_callback_جوڑو_listener(wind->surface_چوکھٹا_callback, &surface_چوکھٹا_listener, ڈیٹا);
}

ساکن ثابت ساخت wl_callback_listener surface_چوکھٹا_listener = {
    surface_چوکھٹا_مکمل
};

ساکن ثابت ساخت wl_callback_listener gles_تبادلہ_چوکھٹا_listener;

ساکن خالی gles_تبادلہ_چوکھٹا_مکمل(خالی *ڈیٹا, ساخت wl_callback *cb, uint32_t وقت)
{
    SDL_کھڑکی_ڈیٹا *wind = (SDL_کھڑکی_ڈیٹا *)ڈیٹا;
    SDL_سیٹ_Atomic_Int(&wind->تبادلہ_interval_ready, 1); // mark window as ready to present again.

    // reset this callback to fire again once a new frame was presented and compositor wants the next one.
    wind->gles_تبادلہ_چوکھٹا_callback = wl_surface_چوکھٹا(wind->gles_تبادلہ_چوکھٹا_surface_wrapper);
    wl_callback_destroy(cb);
    wl_callback_جوڑو_listener(wind->gles_تبادلہ_چوکھٹا_callback, &gles_تبادلہ_چوکھٹا_listener, ڈیٹا);
}

ساکن ثابت ساخت wl_callback_listener gles_تبادلہ_چوکھٹا_listener = {
    gles_تبادلہ_چوکھٹا_مکمل
};

ساکن خالی handle_xdg_surface_configure(خالی *ڈیٹا, ساخت xdg_surface *xdg, uint32_t serial)
{
    SDL_کھڑکی_ڈیٹا *wind = (SDL_کھڑکی_ڈیٹا *)ڈیٹا;
    SDL_کھڑکی *کھڑکی = wind->sdlwindow;

    /* Interactive resizes are throttled by acking and committing only the most recent configuration at
     * the next frame callback, or certain combinations of clients and compositors can exhibit severe lag
     * when resizing.
     */
    wind->shell_surface.xdg.serial = serial;
    اگر (!wind->resizing) {
        wind->pending_config_ack = false;
        Configure_کھڑکی_Geometry(کھڑکی);
        xdg_surface_ack_configure(xdg, serial);
    } ورنہ اگر (!wind->pending_config_ack) {
        wind->pending_config_ack = true;

        // Always send an exposure event during a new frame to ensure forward progress if the frame callback already occurred.
        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_EXPOSED, 0, 0);
    }

    اگر (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_CONFIGURE) {
        wind->shell_surface_حالت = WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_چوکھٹا;
    }
}

ساکن ثابت ساخت xdg_surface_listener _xdg_surface_listener = {
    handle_xdg_surface_configure
};

ساکن خالی ApplyGeometryLimits(SDL_کھڑکی *کھڑکی, صحیح req_w, صحیح req_h, صحیح *برآمد_w, صحیح *برآمد_h)
{
    SDL_کھڑکی_ڈیٹا *wind = کھڑکی->اندرونی_2;

    صحیح w = req_w;
    صحیح h = req_h;
    ثابت اعشاری aspect = (اعشاری)req_w / (اعشاری)req_h;

    /* If adjusting for aspect causes the adjusted dimension to exceed the min/max limit, clamp to the limit
     * and attempt to adjust the opposite dimension to compensate.
     */
    اگر (!wind->resizing || (wind->resize_کنارہ & WAYLAND_RESIZE_کنارہ_کونا) == WAYLAND_RESIZE_کنارہ_کونا) {
        اگر (کھڑکی->min_aspect != 0.f && aspect < کھڑکی->min_aspect) {
            h = SDL_max(SDL_lroundf((اعشاری)req_w / کھڑکی->min_aspect), 1);

            اگر (h < کھڑکی->min_h) {
                w = SDL_max(SDL_lroundf((اعشاری)کھڑکی->min_h * کھڑکی->min_aspect), 1);
            }
            اگر (کھڑکی->max_h && h > کھڑکی->max_h) {
                w = SDL_max(SDL_lroundf((اعشاری)کھڑکی->max_h * کھڑکی->min_aspect), 1);
            }
        } ورنہ اگر (کھڑکی->max_aspect != 0.f && aspect > کھڑکی->max_aspect) {
            w = SDL_max(SDL_lroundf((اعشاری)req_h * کھڑکی->max_aspect), 1);

            اگر (w < کھڑکی->min_w) {
                h = SDL_max(SDL_lroundf((اعشاری)کھڑکی->min_w / کھڑکی->max_aspect), 1);
            }
            اگر (کھڑکی->max_w && w > کھڑکی->max_w) {
                h = SDL_max(SDL_lroundf((اعشاری)کھڑکی->max_w / کھڑکی->max_aspect), 1);
            }
        }
    } ورنہ اگر (wind->resize_کنارہ & WAYLAND_RESIZE_کنارہ_LR) {
        اگر (کھڑکی->min_aspect != 0.f && aspect < کھڑکی->min_aspect) {
            h = SDL_max(SDL_lroundf((اعشاری)req_w / کھڑکی->min_aspect), 1);

            اگر (h < کھڑکی->min_h) {
                w = SDL_max(SDL_lroundf((اعشاری)کھڑکی->min_h * کھڑکی->min_aspect), 1);
            }
            اگر (کھڑکی->max_h && h > کھڑکی->max_h) {
                w = SDL_max(SDL_lroundf((اعشاری)کھڑکی->max_h * کھڑکی->min_aspect), 1);
            }
        } ورنہ اگر (کھڑکی->max_aspect != 0.f && aspect > کھڑکی->max_aspect) {
            h = SDL_max(SDL_lroundf((اعشاری)req_w / کھڑکی->max_aspect), 1);

            اگر (h < کھڑکی->min_h) {
                w = SDL_max(SDL_lroundf((اعشاری)کھڑکی->min_h * کھڑکی->max_aspect), 1);
            }
            اگر (کھڑکی->max_h && h > کھڑکی->max_h) {
                w = SDL_max(SDL_lroundf((اعشاری)کھڑکی->max_h * کھڑکی->max_aspect), 1);
            }
        }
    } ورنہ اگر (wind->resize_کنارہ & WAYLAND_RESIZE_کنارہ_TB) {
        اگر (کھڑکی->min_aspect != 0.f && aspect < کھڑکی->min_aspect) {
            w = SDL_max(SDL_lroundf((اعشاری)req_h * کھڑکی->min_aspect), 1);

            اگر (w < کھڑکی->min_w) {
                h = SDL_max(SDL_lroundf((اعشاری)کھڑکی->min_w / کھڑکی->min_aspect), 1);
            }
            اگر (کھڑکی->max_w && w > کھڑکی->max_w) {
                h = SDL_max(SDL_lroundf((اعشاری)کھڑکی->max_w / کھڑکی->min_aspect), 1);
            }
        } ورنہ اگر (کھڑکی->max_aspect != 0.f && aspect > کھڑکی->max_aspect) {
            w = SDL_max(SDL_lroundf((اعشاری)req_h * کھڑکی->max_aspect), 1);

            اگر (w < کھڑکی->min_w) {
                h = SDL_max(SDL_lroundf((اعشاری)کھڑکی->min_w / کھڑکی->max_aspect), 1);
            }
            اگر (کھڑکی->max_w && w > کھڑکی->max_w) {
                h = SDL_max(SDL_lroundf((اعشاری)کھڑکی->max_w / کھڑکی->max_aspect), 1);
            }
        }
    }

    اگر (کھڑکی->max_w) {
        w = SDL_min(w, کھڑکی->max_w);
    }
    *برآمد_w = SDL_max(w, کھڑکی->min_w);

    اگر (کھڑکی->max_h) {
        h = SDL_min(h, کھڑکی->max_h);
    }
    *برآمد_h = SDL_max(h, کھڑکی->min_h);

}

ساکن خالی DetermineResizeAxis(SDL_کھڑکی_ڈیٹا *wind, صحیح چوڑائی, صحیح اونچائی, bool resizing)
{
    /* Try to determine the axis along which the window is being resized.
     *
     * Every compositor is different, and some will start sending strange values once the resize
     * begins, so only the first change is safe to try and determine the resize edge.
     *
     * Some compositors don't send a configure event with the resize flag cleared when the resize ends,
     * so a reset timer is required.
     */
    اگر (resizing) {
        ثابت Uint64 now = SDL_GetTicksNS();
        اگر (now >= wind->آخری_resize_event_وقت_ns + SDL_MS_مقصد_NS(500)) {
            wind->resize_کنارہ = 0;
        }

        wind->آخری_resize_event_وقت_ns = now;

        اگر (!wind->resize_کنارہ) {
            اگر (چوڑائی != wind->آخری_configure.چوڑائی || !اونچائی) {
                wind->resize_کنارہ |= WAYLAND_RESIZE_کنارہ_LR;
            }
            اگر (اونچائی != wind->آخری_configure.اونچائی || !چوڑائی) {
                wind->resize_کنارہ |= WAYLAND_RESIZE_کنارہ_TB;
            }
        }
    } ورنہ {
        wind->resize_کنارہ = 0;
    }

    wind->resizing = resizing;
}

ساکن خالی handle_xdg_toplevel_configure(خالی *ڈیٹا,
                                          ساخت xdg_toplevel *xdg_toplevel,
                                          int32_t چوڑائی,
                                          int32_t اونچائی,
                                          ساخت wl_array *حالتیں)
{
    SDL_کھڑکی_ڈیٹا *wind = (SDL_کھڑکی_ڈیٹا *)ڈیٹا;
    SDL_کھڑکی *کھڑکی = wind->sdlwindow;

    شمار xdg_toplevel_state *state;
    bool fullscreen = false;
    bool maximized = false;
    bool floating = true;
    bool tiled = false;
    bool فعال = false;
    bool resizing = false;
    bool suspended = false;
    wind->toplevel_constraints = 0;
    wl_array_for_each (state, حالتیں) {
        انتخاب (*state) {
        حالت XDG_TOPLEVEL_STATE_FULLSCREEN:
            fullscreen = true;
            floating = false;
            توڑو;
        حالت XDG_TOPLEVEL_STATE_MAXIMIZED:
            maximized = true;
            floating = false;
            توڑو;
        حالت XDG_TOPLEVEL_STATE_RESIZING:
            resizing = true;
            توڑو;
        حالت XDG_TOPLEVEL_STATE_ACTIVATED:
            فعال = true;
            توڑو;
        حالت XDG_TOPLEVEL_STATE_TILED_بایاں:
        حالت XDG_TOPLEVEL_STATE_TILED_دایاں:
        حالت XDG_TOPLEVEL_STATE_TILED_چوٹی:
        حالت XDG_TOPLEVEL_STATE_TILED_BOTTOM:
            tiled = true;
            floating = false;
            توڑو;
        حالت XDG_TOPLEVEL_STATE_SUSPENDED:
            suspended = true;
            توڑو;
        حالت XDG_TOPLEVEL_STATE_CONSTRAINED_بایاں:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_بایاں;
            توڑو;
        حالت XDG_TOPLEVEL_STATE_CONSTRAINED_دایاں:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_دایاں;
            توڑو;
        حالت XDG_TOPLEVEL_STATE_CONSTRAINED_چوٹی:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_چوٹی;
            توڑو;
        حالت XDG_TOPLEVEL_STATE_CONSTRAINED_BOTTOM:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM;
            توڑو;
        طےشدہ:
            توڑو;
        }
    }

    /* Configure sizes are in window geometry space; add the border insets, if any, to get
     * the surface size. Maximized and fullscreen windows must use the configured size as-is,
     * so a change in inset applicability requires re-adopting even an unchanged size, and
     * sizes adopted from the cached window size are converted back to geometry space for
     * the last_configure store.
     */
    ثابت bool insets_apply = wind->enable_insets && !fullscreen && !maximized;

    // When resizing, dimensions other than 0 are a maximum.
    ثابت bool new_configure_سائز = چوڑائی != wind->آخری_configure.چوڑائی || اونچائی != wind->آخری_configure.اونچائی ||
                                    insets_apply != wind->آخری_configure.insets_apply;

    BorderInsets insets = { 0, 0, 0, 0 };
    اگر (insets_apply) {
        GetBorderInsets(کھڑکی, &insets);
    }

    DetermineResizeAxis(wind, چوڑائی, اونچائی, resizing);
    Update_کھڑکی_Fullscreen(کھڑکی, fullscreen);

    /* Always send a maximized/restore event; if the event is redundant it will
     * automatically be discarded (see src/events/SDL_windowevents.c)
     *
     * No, we do not get minimize events from xdg-shell, however, the minimized
     * state can be programmatically set. The meaning of 'minimized' is compositor
     * dependent, but in general, we can assume that the flag should remain set until
     * the next focused configure event occurs.
     */
    اگر (فعال || !(کھڑکی->flags & SDL_کھڑکی_MINIMIZED)) {
        اگر (کھڑکی->flags & SDL_کھڑکی_MINIMIZED) {
            // If we were minimized, send a restored event before possibly sending maximized.
            SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESTORED, 0, 0);
        }
        SDL_Send_کھڑکی_Event(کھڑکی,
                            (maximized && !fullscreen) ? SDL_EVENT_کھڑکی_MAXIMIZED : SDL_EVENT_کھڑکی_RESTORED,
                            0, 0);
    }

    اگر (!fullscreen) {
        /* xdg_toplevel spec states that this is a suggestion.
         * Ignore if less than or greater than max/min size.
         */
        اگر ((کھڑکی->flags & SDL_کھڑکی_RESIZABLE) || maximized) {
            اگر (!چوڑائی) {
                /* This happens when the compositor indicates that the size is
                 * up to the client, so use the cached window size here.
                 */
                اگر (floating) {
                    چوڑائی = کھڑکی->floating.w;

                    // Clamp the window to the toplevel bounds, if any are set.
                    اگر (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_CONFIGURE && wind->toplevel_bounds.چوڑائی) {
                        چوڑائی = SDL_min(wind->toplevel_bounds.چوڑائی, چوڑائی);
                    }
                } ورنہ {
                    چوڑائی = کھڑکی->windowed.w;
                }

                اگر (!wind->scale_مقصد_display) {
                    wind->requested.logical_چوڑائی = چوڑائی;
                } ورنہ {
                    wind->requested.pixel_چوڑائی = چوڑائی;
                    چوڑائی = wind->requested.logical_چوڑائی = Pixel_مقصد_نقطہ(کھڑکی, چوڑائی);
                }
                چوڑائی = SDL_max(چوڑائی - (insets.بایاں + insets.دایاں), 1);
            } ورنہ اگر (new_configure_سائز) {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 */

                wind->requested.logical_چوڑائی = چوڑائی + (insets.بایاں + insets.دایاں);

                اگر (wind->scale_مقصد_display) {
                    wind->requested.pixel_چوڑائی = نقطہ_مقصد_Pixel(کھڑکی, wind->requested.logical_چوڑائی);
                }
            }
            اگر (!اونچائی) {
                /* This happens when the compositor indicates that the size is
                 * up to the client, so use the cached window size here.
                 */
                اگر (floating) {
                    اونچائی = کھڑکی->floating.h;

                    // Clamp the window to the toplevel bounds, if any are set.
                    اگر (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_CONFIGURE && wind->toplevel_bounds.اونچائی) {
                        اونچائی = SDL_min(wind->toplevel_bounds.اونچائی, اونچائی);
                    }
                } ورنہ {
                    اونچائی = کھڑکی->windowed.h;
                }

                اگر (!wind->scale_مقصد_display) {
                    wind->requested.logical_اونچائی = اونچائی;
                } ورنہ {
                    wind->requested.pixel_اونچائی = اونچائی;
                    اونچائی = wind->requested.logical_اونچائی = Pixel_مقصد_نقطہ(کھڑکی, اونچائی);
                }
                اونچائی = SDL_max(اونچائی - (insets.چوٹی + insets.bottom), 1);
            } ورنہ اگر (new_configure_سائز) {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 */
                wind->requested.logical_اونچائی = اونچائی + (insets.چوٹی + insets.bottom);

                اگر (wind->scale_مقصد_display) {
                    wind->requested.pixel_اونچائی = نقطہ_مقصد_Pixel(کھڑکی, wind->requested.logical_اونچائی);
                }
            }
        } ورنہ {
            /* If we're a fixed-size, non-maximized window, we know our size for sure.
             * Always assume the configure is wrong.
             */
            اگر (!wind->scale_مقصد_display) {
                چوڑائی = wind->requested.logical_چوڑائی = کھڑکی->floating.w;
                اونچائی = wind->requested.logical_اونچائی = کھڑکی->floating.h;
            } ورنہ {
                wind->requested.pixel_چوڑائی = کھڑکی->floating.w;
                wind->requested.pixel_اونچائی = کھڑکی->floating.h;
                چوڑائی = wind->requested.logical_چوڑائی = Pixel_مقصد_نقطہ(کھڑکی, کھڑکی->floating.w);
                اونچائی = wind->requested.logical_اونچائی = Pixel_مقصد_نقطہ(کھڑکی, کھڑکی->floating.h);
            }
            چوڑائی = SDL_max(چوڑائی - (insets.بایاں + insets.دایاں), 1);
            اونچائی = SDL_max(اونچائی - (insets.چوٹی + insets.bottom), 1);
        }

        /* Notes on the spec and implementations:
         *
         * - The content limits are only a hint, which the compositor is free to ignore,
         *   so apply them manually when appropriate.
         *
         * - Only floating windows are truly safe to resize: maximized windows must have
         *   their exact dimensions respected, or a protocol violation can occur, and tiled
         *   windows can technically use dimensions smaller than the ones supplied by the
         *   compositor, but doing so can cause visual glitches and odd behavior. In these cases
         *   it's best to use the supplied dimensions and use a viewport + mask to enforce the
         *   size limits and/or aspect ratio.
         */
        اگر (floating) {
            اگر (!wind->scale_مقصد_display) {
                ApplyGeometryLimits(کھڑکی, wind->requested.logical_چوڑائی, wind->requested.logical_اونچائی, &wind->requested.logical_چوڑائی, &wind->requested.logical_اونچائی);
            } ورنہ {
                ApplyGeometryLimits(کھڑکی, wind->requested.pixel_چوڑائی, wind->requested.pixel_اونچائی, &wind->requested.pixel_چوڑائی, &wind->requested.pixel_اونچائی);

                wind->requested.logical_چوڑائی = Pixel_مقصد_نقطہ(کھڑکی, wind->requested.pixel_چوڑائی);
                wind->requested.logical_اونچائی = Pixel_مقصد_نقطہ(کھڑکی, wind->requested.pixel_اونچائی);
            }
        }
    } ورنہ {
        // Fullscreen windows know their exact size.
        اگر (چوڑائی == 0 || اونچائی == 0) {
            چوڑائی = wind->requested.logical_چوڑائی;
            اونچائی = wind->requested.logical_اونچائی;
        } ورنہ {
            wind->requested.logical_چوڑائی = چوڑائی;
            wind->requested.logical_اونچائی = اونچائی;
        }

        اگر (wind->scale_مقصد_display) {
            wind->requested.pixel_چوڑائی = نقطہ_مقصد_Pixel(کھڑکی, چوڑائی);
            wind->requested.pixel_اونچائی = نقطہ_مقصد_Pixel(کھڑکی, اونچائی);
        }
    }

    wind->آخری_configure.چوڑائی = چوڑائی;
    wind->آخری_configure.اونچائی = اونچائی;
    wind->آخری_configure.insets_apply = insets_apply;
    wind->floating = floating;
    wind->suspended = suspended;
    wind->فعال = فعال;
    کھڑکی->tiled = tiled;
}

ساکن خالی handle_xdg_toplevel_close(خالی *ڈیٹا, ساخت xdg_toplevel *xdg_toplevel)
{
    SDL_کھڑکی_ڈیٹا *کھڑکی = (SDL_کھڑکی_ڈیٹا *)ڈیٹا;
    SDL_Send_کھڑکی_Event(کھڑکی->sdlwindow, SDL_EVENT_کھڑکی_CLOSE_REQUESTED, 0, 0);
}

ساکن خالی handle_xdg_toplevel_configure_bounds(خالی *ڈیٹا,
                                                 ساخت xdg_toplevel *xdg_toplevel,
                                                 int32_t چوڑائی, int32_t اونچائی)
{
    SDL_کھڑکی_ڈیٹا *کھڑکی = (SDL_کھڑکی_ڈیٹا *)ڈیٹا;
    کھڑکی->toplevel_bounds.چوڑائی = چوڑائی;
    کھڑکی->toplevel_bounds.اونچائی = اونچائی;
}

ساکن خالی handle_xdg_toplevel_wm_capabilities(خالی *ڈیٹا,
                                                ساخت xdg_toplevel *xdg_toplevel,
                                                ساخت wl_array *capabilities)
{
    SDL_کھڑکی_ڈیٹا *wind = (SDL_کھڑکی_ڈیٹا *)ڈیٹا;
    شمار xdg_toplevel_wm_capabilities *wm_cap;

    wind->wm_caps = 0;

    wl_array_for_each (wm_cap, capabilities) {
        انتخاب (*wm_cap) {
        حالت XDG_TOPLEVEL_WM_CAPABILITIES_کھڑکی_MENU:
            wind->wm_caps |= WAYLAND_WM_CAPS_کھڑکی_MENU;
            توڑو;
        حالت XDG_TOPLEVEL_WM_CAPABILITIES_MAXIMIZE:
            wind->wm_caps |= WAYLAND_WM_CAPS_MAXIMIZE;
            توڑو;
        حالت XDG_TOPLEVEL_WM_CAPABILITIES_FULLSCREEN:
            wind->wm_caps |= WAYLAND_WM_CAPS_FULLSCREEN;
            توڑو;
        حالت XDG_TOPLEVEL_WM_CAPABILITIES_MINIMIZE:
            wind->wm_caps |= WAYLAND_WM_CAPS_MINIMIZE;
            توڑو;
        طےشدہ:
            توڑو;
        }
    }
}

ساکن ثابت ساخت xdg_toplevel_listener toplevel_listener_xdg = {
    handle_xdg_toplevel_configure,
    handle_xdg_toplevel_close,
    handle_xdg_toplevel_configure_bounds, // Version 4
    handle_xdg_toplevel_wm_capabilities   // Version 5
};

ساکن خالی handle_xdg_popup_configure(خالی *ڈیٹا,
                                       ساخت xdg_popup *xdg_popup,
                                       int32_t x,
                                       int32_t y,
                                       int32_t چوڑائی,
                                       int32_t اونچائی)
{
    SDL_کھڑکی_ڈیٹا *wind = (SDL_کھڑکی_ڈیٹا *)ڈیٹا;
    صحیح انحراف_x = 0, انحراف_y = 0;

    // Adjust the position if it was offset for libdecor
    Adjust_Popup_انحراف(wind->sdlwindow, &انحراف_x, &انحراف_y);
    x -= انحراف_x;
    y -= انحراف_y;

    /* This happens when the compositor indicates that the size is
     * up to the client, so use the cached window size here.
     */
    اگر (چوڑائی == 0 || اونچائی == 0) {
        چوڑائی = wind->sdlwindow->floating.w;
        اونچائی = wind->sdlwindow->floating.h;
    }

    /* Don't apply the supplied dimensions if they haven't changed from the last configuration
     * event, or a newer size set programmatically can be overwritten by old data.
     */
    اگر (چوڑائی != wind->آخری_configure.چوڑائی || اونچائی != wind->آخری_configure.اونچائی) {
        wind->requested.logical_چوڑائی = چوڑائی;
        wind->requested.logical_اونچائی = اونچائی;

        اگر (wind->scale_مقصد_display) {
            wind->requested.pixel_چوڑائی = نقطہ_مقصد_Pixel(wind->sdlwindow, چوڑائی);
            wind->requested.pixel_اونچائی = نقطہ_مقصد_Pixel(wind->sdlwindow, اونچائی);
        }
    }

    اگر (wind->scale_مقصد_display) {
        x = نقطہ_مقصد_Pixel(wind->sdlwindow->والد, x);
        y = نقطہ_مقصد_Pixel(wind->sdlwindow->والد, y);
    }

    SDL_Send_کھڑکی_Event(wind->sdlwindow, SDL_EVENT_کھڑکی_MOVED, x, y);

    wind->آخری_configure.چوڑائی = چوڑائی;
    wind->آخری_configure.اونچائی = اونچائی;

    اگر (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_CONFIGURE) {
        wind->shell_surface_حالت = WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_چوکھٹا;
    }
}

ساکن خالی handle_xdg_popup_مکمل(خالی *ڈیٹا, ساخت xdg_popup *xdg_popup)
{
    SDL_کھڑکی_ڈیٹا *کھڑکی = (SDL_کھڑکی_ڈیٹا *)ڈیٹا;
    SDL_Send_کھڑکی_Event(کھڑکی->sdlwindow, SDL_EVENT_کھڑکی_CLOSE_REQUESTED, 0, 0);
}

ساکن خالی handle_xdg_popup_repositioned(خالی *ڈیٹا,
                                          ساخت xdg_popup *xdg_popup,
                                          uint32_t token)
{
    // No-op, configure does all the work we care about
}

ساکن ثابت ساخت xdg_popup_listener _xdg_popup_listener = {
    handle_xdg_popup_configure,
    handle_xdg_popup_مکمل,
    handle_xdg_popup_repositioned
};

ساکن خالی handle_xdg_toplevel_decoration_configure(خالی *ڈیٹا,
                                                     ساخت zxdg_toplevel_decoration_v1 *zxdg_toplevel_decoration_v1,
                                                     uint32_t منوال)
{
    SDL_کھڑکی *کھڑکی = (SDL_کھڑکی *)ڈیٹا;
    SDL_کھڑکی_ڈیٹا *اندرونی_2 = کھڑکی->اندرونی_2;
    SDL_VideoDevice *device = SDL_GetVideoDevice();

    /* If the compositor tries to force CSD anyway, bail on direct XDG support
     * and fall back to libdecor, it will handle these events from then on.
     *
     * To do this we have to fully unmap, then map with libdecor loaded.
     */
    اگر (منوال == ZXDG_TOPLEVEL_DECORATION_V1_منوال_CLIENT_SIDE) {
        اگر (کھڑکی->flags & SDL_کھڑکی_BORDERLESS) {
            // borderless windows do request CSD, so we got what we wanted
            واپس;
        }
        اگر (!Wayland_بھرو_Libdecor(اندرونی_2->wayland_ڈیٹا, true)) {
            // libdecor isn't available, so no borders for you... oh well
            واپس;
        }
        WAYLAND_wl_display_roundtrip(اندرونی_2->wayland_ڈیٹا->display);

        Wayland_Hide_کھڑکی(device, کھڑکی);
        اندرونی_2->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR;
        Wayland_Show_کھڑکی(device, کھڑکی);
    }
}

ساکن ثابت ساخت zxdg_toplevel_decoration_v1_listener xdg_toplevel_decoration_listener = {
    handle_xdg_toplevel_decoration_configure
};

#اگر_تعریف_شدہ HAVE_LIBDECOR_H
/*
 * XXX: Hack for older versions of libdecor that lack the function to query the
 *      minimum content size limit. The internal limits must always be overridden
 *      to ensure that very small windows don't cause errors or crashes.
 *
 *      On libdecor >= 0.1.2, which exposes the function to get the minimum content
 *      size limit, this function is a no-op.
 *
 *      Can be removed if the minimum required version of libdecor is raised to
 *      0.1.2 or higher.
 */
ساکن خالی OverrideLibdecorLimits(SDL_کھڑکی *کھڑکی)
{
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    اگر (!libdecor_چوکھٹا_get_min_content_سائز) {
        libdecor_چوکھٹا_سیٹ_min_content_سائز(کھڑکی->اندرونی_2->shell_surface.libdecor.چوکھٹا, کھڑکی->min_w, کھڑکی->min_h);
    }
#وگرنہ_اگر !SDL_LIBDECOR_CHECK_نسخہ(0, 2, 0)
    libdecor_چوکھٹا_سیٹ_min_content_سائز(کھڑکی->اندرونی_2->shell_surface.libdecor.چوکھٹا, کھڑکی->min_w, کھڑکی->min_h);
#اگر_ختم
}

/*
 * NOTE: Retrieves the minimum content size limits, if the function for doing so is available.
 *       On versions of libdecor that lack the minimum content size retrieval function, this
 *       function is a no-op.
 *
 *       Can be replaced with a direct call if the minimum required version of libdecor is raised
 *       to 0.1.2 or higher.
 */
ساکن خالی Libdecor_Get_Min_Content_سائز(ساخت libdecor_چوکھٹا *چوکھٹا, صحیح *min_w, صحیح *min_h)
{
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    اگر (libdecor_چوکھٹا_get_min_content_سائز != تہی) {
        libdecor_چوکھٹا_get_min_content_سائز(چوکھٹا, min_w, min_h);
    }
#وگرنہ_اگر SDL_LIBDECOR_CHECK_نسخہ(0, 2, 0)
    libdecor_چوکھٹا_get_min_content_سائز(چوکھٹا, min_w, min_h);
#اگر_ختم
}

ساکن خالی decoration_چوکھٹا_configure(ساخت libdecor_چوکھٹا *چوکھٹا,
                                       ساخت libdecor_configuration *configuration,
                                       خالی *user_ڈیٹا_2)
{
    SDL_کھڑکی_ڈیٹا *wind = (SDL_کھڑکی_ڈیٹا *)user_ڈیٹا_2;
    SDL_کھڑکی *کھڑکی = wind->sdlwindow;

    شمار libdecor_کھڑکی_state کھڑکی_state;
    صحیح چوڑائی, اونچائی;

    bool فعال = false;
    bool fullscreen = false;
    bool maximized = false;
    bool tiled = false;
    bool suspended = false;
    bool resizing = false;
    wind->toplevel_constraints = 0;

    ساکن ثابت شمار libdecor_کھڑکی_state tiled_حالتیں = (LIBDECOR_کھڑکی_STATE_TILED_بایاں | LIBDECOR_کھڑکی_STATE_TILED_دایاں |
                                                            LIBDECOR_کھڑکی_STATE_TILED_چوٹی | LIBDECOR_کھڑکی_STATE_TILED_BOTTOM);

    اگر (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_CONFIGURE) {
        Libdecor_Get_Min_Content_سائز(چوکھٹا, &wind->system_limits.min_چوڑائی_2, &wind->system_limits.min_اونچائی_2);
    }

    // Window State
    اگر (libdecor_configuration_get_کھڑکی_state(configuration, &کھڑکی_state)) {
        fullscreen = (کھڑکی_state & LIBDECOR_کھڑکی_STATE_FULLSCREEN) != 0;
        maximized = (کھڑکی_state & LIBDECOR_کھڑکی_STATE_MAXIMIZED) != 0;
        فعال = (کھڑکی_state & LIBDECOR_کھڑکی_STATE_فعال) != 0;
        tiled = (کھڑکی_state & tiled_حالتیں) != 0;
#اگر SDL_LIBDECOR_CHECK_نسخہ(0, 2, 0)
        suspended = (کھڑکی_state & LIBDECOR_کھڑکی_STATE_SUSPENDED) != 0;
#اگر_ختم
#اگر SDL_LIBDECOR_CHECK_نسخہ(0, 3, 0)
        resizing = (کھڑکی_state & LIBDECOR_کھڑکی_STATE_RESIZING) != 0;

        اگر (کھڑکی_state & LIBDECOR_کھڑکی_STATE_CONSTRAINED_بایاں) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_بایاں;
        }
        اگر (کھڑکی_state & LIBDECOR_کھڑکی_STATE_CONSTRAINED_دایاں) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_دایاں;
        }
        اگر (کھڑکی_state & LIBDECOR_کھڑکی_STATE_CONSTRAINED_چوٹی) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_چوٹی;
        }
        اگر (کھڑکی_state & LIBDECOR_کھڑکی_STATE_CONSTRAINED_BOTTOM) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM;
        }
#اگر_ختم
    }
    ثابت bool floating = !(fullscreen || maximized || tiled);

    Update_کھڑکی_Fullscreen(کھڑکی, fullscreen);

    /* Always send a maximized/restore event; if the event is redundant it will
     * automatically be discarded (see src/events/SDL_windowevents.c)
     *
     * No, we do not get minimize events from libdecor, however, the minimized
     * state can be programmatically set. The meaning of 'minimized' is compositor
     * dependent, but in general, we can assume that the flag should remain set until
     * the next focused configure event occurs.
     */
    اگر (فعال || !(کھڑکی->flags & SDL_کھڑکی_MINIMIZED)) {
        اگر (کھڑکی->flags & SDL_کھڑکی_MINIMIZED) {
            // If we were minimized, send a restored event before possibly sending maximized.
            SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESTORED, 0, 0);
        }
        SDL_Send_کھڑکی_Event(کھڑکی,
                            (maximized && !fullscreen) ? SDL_EVENT_کھڑکی_MAXIMIZED : SDL_EVENT_کھڑکی_RESTORED,
                            0, 0);
    }

    /* For fullscreen or fixed-size windows we know our size.
     * Always assume the configure is wrong.
     */
    اگر (fullscreen) {
        اگر (!libdecor_configuration_get_content_سائز(configuration, چوکھٹا, &چوڑائی, &اونچائی)) {
            چوڑائی = wind->requested.logical_چوڑائی;
            اونچائی = wind->requested.logical_اونچائی;
        } ورنہ {
            // Fullscreen windows know their exact size.
            wind->requested.logical_چوڑائی = چوڑائی;
            wind->requested.logical_اونچائی = اونچائی;

            اگر (wind->scale_مقصد_display) {
                wind->requested.pixel_چوڑائی = نقطہ_مقصد_Pixel(کھڑکی, چوڑائی);
                wind->requested.pixel_اونچائی = نقطہ_مقصد_Pixel(کھڑکی, اونچائی);
            }
        }
    } ورنہ {
        اگر (!(کھڑکی->flags & SDL_کھڑکی_RESIZABLE) && !maximized) {
            /* If we're a fixed-size, non-maximized window, we know our size for sure.
             * Always assume the configure is wrong.
             */
            اگر (!wind->scale_مقصد_display) {
                چوڑائی = wind->requested.logical_چوڑائی = کھڑکی->floating.w;
                اونچائی = wind->requested.logical_اونچائی = کھڑکی->floating.h;
            } ورنہ {
                wind->requested.pixel_چوڑائی = کھڑکی->floating.w;
                wind->requested.pixel_اونچائی = کھڑکی->floating.h;
                چوڑائی = wind->requested.logical_چوڑائی = Pixel_مقصد_نقطہ(کھڑکی, کھڑکی->floating.w);
                اونچائی = wind->requested.logical_اونچائی = Pixel_مقصد_نقطہ(کھڑکی, کھڑکی->floating.h);
            }

            OverrideLibdecorLimits(کھڑکی);
        } ورنہ {
            /* XXX: The libdecor cairo plugin sends bogus content sizes that add the
             *      height of the title bar when transitioning from a fixed-size to
             *      floating state. Ignore the sent window dimensions in this case,
             *      in favor of the cached value to avoid the window increasing in
             *      size after every state transition.
             *
             *      https://gitlab.freedesktop.org/libdecor/libdecor/-/issues/34
             */
            اگر ((floating && (!wind->floating && !(کھڑکی->flags & SDL_کھڑکی_BORDERLESS))) ||
                !libdecor_configuration_get_content_سائز(configuration, چوکھٹا, &چوڑائی, &اونچائی)) {
                چوڑائی = 0;
                اونچائی = 0;
            }

            ثابت bool new_configure_سائز = چوڑائی != wind->آخری_configure.چوڑائی || اونچائی != wind->آخری_configure.اونچائی;
            DetermineResizeAxis(wind, چوڑائی, اونچائی, resizing);

            اگر (!چوڑائی) {
                /* This happens when we're being restored from a non-floating state,
                 * or the compositor indicates that the size is up to the client, so
                 * used the cached window size here.
                 */
                اگر (floating) {
                    چوڑائی = کھڑکی->floating.w;

                    // Clamp the window to the toplevel bounds, if any are set.
                    اگر (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_CONFIGURE && wind->toplevel_bounds.چوڑائی) {
                        چوڑائی = SDL_min(wind->toplevel_bounds.چوڑائی, چوڑائی);
                    }
                } ورنہ {
                    چوڑائی = کھڑکی->windowed.w;
                }

                اگر (!wind->scale_مقصد_display) {
                    wind->requested.logical_چوڑائی = چوڑائی;
                } ورنہ {
                    wind->requested.pixel_چوڑائی = چوڑائی;
                    چوڑائی = wind->requested.logical_چوڑائی = Pixel_مقصد_نقطہ(کھڑکی, چوڑائی);
                }
            } ورنہ {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 *
                 * If a client takes a long time to present the first frame after creating the window, a
                 * configure event to set the suspended state may arrive with the content size increased
                 * by the decoration dimensions, which should also be ignored.
                 */
                اگر (new_configure_سائز &&
                    !(wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_چوکھٹا && wind->suspended != suspended)) {
                    wind->requested.logical_چوڑائی = چوڑائی;

                    اگر (wind->scale_مقصد_display) {
                        wind->requested.pixel_چوڑائی = نقطہ_مقصد_Pixel(کھڑکی, چوڑائی);
                    }
                }
            }

            اگر (!اونچائی) {
                /* This happens when we're being restored from a non-floating state,
                 * or the compositor indicates that the size is up to the client, so
                 * used the cached window size here.
                 */
                اگر (floating) {
                    اونچائی = کھڑکی->floating.h;

                    // Clamp the window to the toplevel bounds, if any are set.
                    اگر (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_CONFIGURE && wind->toplevel_bounds.اونچائی) {
                        اونچائی = SDL_min(wind->toplevel_bounds.اونچائی, اونچائی);
                    }
                } ورنہ {
                    اونچائی = کھڑکی->windowed.h;
                }

                اگر (!wind->scale_مقصد_display) {
                    wind->requested.logical_اونچائی = اونچائی;
                } ورنہ {
                    wind->requested.pixel_اونچائی = اونچائی;
                    اونچائی = wind->requested.logical_اونچائی = Pixel_مقصد_نقطہ(کھڑکی, اونچائی);
                }
            } ورنہ {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 *
                 * If a client takes a long time to present the first frame after creating the window, a
                 * configure event to set the suspended state may arrive with the content size increased
                 * by the decoration dimensions, which should also be ignored.
                 */
                اگر (new_configure_سائز &&
                    !(wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_چوکھٹا && wind->suspended != suspended)) {
                    wind->requested.logical_اونچائی = اونچائی;

                    اگر (wind->scale_مقصد_display) {
                        wind->requested.pixel_اونچائی = نقطہ_مقصد_Pixel(کھڑکی, اونچائی);
                    }
                }
            }
        }

        /* Notes on the spec and implementations:
         *
         * - The content limits are only a hint, which the compositor is free to ignore,
         *   so apply them manually when appropriate.
         *
         * - Only floating windows are truly safe to resize: maximized windows must have
         *   their exact dimensions respected, or a protocol violation can occur, and tiled
         *   windows can technically use dimensions smaller than the ones supplied by the
         *   compositor, but doing so can cause odd behavior. In these cases it's best to use
         *   the supplied dimensions and use a viewport + mask to enforce the size limits and/or
         *   aspect ratio.
         */
        اگر (floating) {
            اگر (!wind->scale_مقصد_display) {
                ApplyGeometryLimits(کھڑکی, wind->requested.logical_چوڑائی, wind->requested.logical_اونچائی, &wind->requested.logical_چوڑائی, &wind->requested.logical_اونچائی);
            } ورنہ {
                ApplyGeometryLimits(کھڑکی, wind->requested.pixel_چوڑائی, wind->requested.pixel_اونچائی, &wind->requested.pixel_چوڑائی, &wind->requested.pixel_اونچائی);

                wind->requested.logical_چوڑائی = Pixel_مقصد_نقطہ(کھڑکی, wind->requested.pixel_چوڑائی);
                wind->requested.logical_اونچائی = Pixel_مقصد_نقطہ(کھڑکی, wind->requested.pixel_اونچائی);
            }
        }
    }

    // Store the new state.
    ثابت bool started_resize = !wind->resizing && resizing;
    wind->آخری_configure.چوڑائی = چوڑائی;
    wind->آخری_configure.اونچائی = اونچائی;
    wind->floating = floating;
    wind->suspended = suspended;
    wind->فعال = فعال;
    کھڑکی->tiled = tiled;
    wind->resizing = resizing;

    // Update the window manager capabilities.
#اگر SDL_LIBDECOR_CHECK_نسخہ(0, 3, 0)
    شمار libdecor_wm_capabilities caps;
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    اگر (libdecor_چوکھٹا_get_wm_capabilities) {
        caps = libdecor_چوکھٹا_get_wm_capabilities(wind->shell_surface.libdecor.چوکھٹا);
#ورنہ
    caps = libdecor_چوکھٹا_get_wm_capabilities(wind->shell_surface.libdecor.چوکھٹا);
    {
#اگر_ختم
        wind->wm_caps = 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_کھڑکی_MENU ? WAYLAND_WM_CAPS_کھڑکی_MENU : 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_MAXIMIZE ? WAYLAND_WM_CAPS_MAXIMIZE : 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_FULLSCREEN ? WAYLAND_WM_CAPS_FULLSCREEN : 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_MINIMIZE ? WAYLAND_WM_CAPS_MINIMIZE : 0;
    }
#اگر_ختم

    اگر (!wind->resizing || started_resize) {
        /* Calculate the new window geometry and commit the changes on the libdecor side.
         *
         * XXX: This will potentially leave un-acked configurations, but libdecor invalidates the
         *      configuration upon returning from the frame event, so there is nothing that can be
         *      done, unless libdecor adds the ability to copy or refcount the configuration state
         *      to apply later.
         */
        Configure_کھڑکی_Geometry(کھڑکی);
        ساخت libdecor_state *state = libdecor_state_new(wind->current.logical_چوڑائی, wind->current.logical_اونچائی);
        libdecor_چوکھٹا_commit(چوکھٹا, state, configuration);
        libdecor_state_free(state);

        // Always send an exposure event during a new frame to ensure forward progress if the frame callback already occurred.
        اگر (started_resize) {
            SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_EXPOSED, 0, 0);
        }
    }

    اگر (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_CONFIGURE) {
        wind->shell_surface_حالت = WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_چوکھٹا;
    }
}

ساکن خالی decoration_چوکھٹا_close(ساخت libdecor_چوکھٹا *چوکھٹا, خالی *user_ڈیٹا_2)
{
    SDL_Send_کھڑکی_Event(((SDL_کھڑکی_ڈیٹا *)user_ڈیٹا_2)->sdlwindow, SDL_EVENT_کھڑکی_CLOSE_REQUESTED, 0, 0);
}

ساکن خالی decoration_چوکھٹا_commit(ساخت libdecor_چوکھٹا *چوکھٹا, خالی *user_ڈیٹا_2)
{
    /* libdecor decoration subsurfaces are synchronous, so the client needs to
     * commit a frame to trigger an update of the decoration surfaces.
     */
    SDL_کھڑکی_ڈیٹا *wind = (SDL_کھڑکی_ڈیٹا *)user_ڈیٹا_2;
    اگر (!wind->suspended && wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_SHOWN) {
        SDL_Send_کھڑکی_Event(wind->sdlwindow, SDL_EVENT_کھڑکی_EXPOSED, 0, 0);
    }
}

ساکن خالی decoration_dismiss_popup(ساخت libdecor_چوکھٹا *چوکھٹا, ثابت حرف *seat_name, خالی *user_ڈیٹا_2)
{
    // NOP
}

#اگر SDL_LIBDECOR_CHECK_نسخہ(0, 3, 0)
ساکن خالی decoration_چوکھٹا_bounds(ساخت libdecor_چوکھٹا *چوکھٹا, صحیح چوڑائی, صحیح اونچائی, خالی *user_ڈیٹا_2)
{
    SDL_کھڑکی_ڈیٹا *کھڑکی = (SDL_کھڑکی_ڈیٹا *)user_ڈیٹا_2;
    کھڑکی->toplevel_bounds.چوڑائی = چوڑائی;
    کھڑکی->toplevel_bounds.اونچائی = اونچائی;
}
#اگر_ختم

ساکن ساخت libdecor_چوکھٹا_interface libdecor_چوکھٹا_interface = {
    decoration_چوکھٹا_configure,
    decoration_چوکھٹا_close,
    decoration_چوکھٹا_commit,
    decoration_dismiss_popup,
#اگر SDL_LIBDECOR_CHECK_نسخہ(0, 3, 0)
    decoration_چوکھٹا_bounds
#اگر_ختم
};
#اگر_ختم

ساکن خالی Wayland_Handle_Preferred_Scale_بدلا(SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2, دوہرا ضربی_عدد)
{
    ثابت دوہرا old_ضربی_عدد = کھڑکی_ڈیٹا_2->scale_ضربی_عدد_2;

    // Round the scale factor if viewports aren't available.
    اگر (!کھڑکی_ڈیٹا_2->viewport) {
        ضربی_عدد = SDL_ceil(ضربی_عدد);
    }

    اگر (ضربی_عدد != old_ضربی_عدد) {
        کھڑکی_ڈیٹا_2->scale_ضربی_عدد_2 = ضربی_عدد;

        اگر (کھڑکی_ڈیٹا_2->scale_مقصد_display) {
            /* If the window is in the floating state with a user/application specified size, calculate the new
             * logical size from the backbuffer size. Otherwise, use the fixed underlying logical size to calculate
             * the new backbuffer dimensions.
             */
            اگر (کھڑکی_ڈیٹا_2->floating) {
                /* Some compositors will send a configure event immediately after a scale event, however,
                 * this event can contain the old logical size, and should be ignored, or the window can
                 * incorrectly change size when moved between displays with differing scale factors.
                 *
                 * Store the last requested logical size as the last configure size, so a configure event
                 * with the old size will be ignored. Configure sizes are in window geometry space,
                 * so subtract any border insets.
                 */
                BorderInsets insets;
                GetBorderInsets(کھڑکی_ڈیٹا_2->sdlwindow, &insets);
                کھڑکی_ڈیٹا_2->آخری_configure.چوڑائی = SDL_max(کھڑکی_ڈیٹا_2->requested.logical_چوڑائی - (insets.بایاں + insets.دایاں), 1);
                کھڑکی_ڈیٹا_2->آخری_configure.اونچائی = SDL_max(کھڑکی_ڈیٹا_2->requested.logical_اونچائی - (insets.چوٹی + insets.bottom), 1);

                کھڑکی_ڈیٹا_2->requested.logical_چوڑائی = Pixel_مقصد_نقطہ(کھڑکی_ڈیٹا_2->sdlwindow, کھڑکی_ڈیٹا_2->requested.pixel_چوڑائی);
                کھڑکی_ڈیٹا_2->requested.logical_اونچائی = Pixel_مقصد_نقطہ(کھڑکی_ڈیٹا_2->sdlwindow, کھڑکی_ڈیٹا_2->requested.pixel_اونچائی);
            } ورنہ {
                کھڑکی_ڈیٹا_2->requested.pixel_چوڑائی = نقطہ_مقصد_Pixel(کھڑکی_ڈیٹا_2->sdlwindow, کھڑکی_ڈیٹا_2->requested.logical_چوڑائی);
                کھڑکی_ڈیٹا_2->requested.pixel_اونچائی = نقطہ_مقصد_Pixel(کھڑکی_ڈیٹا_2->sdlwindow, کھڑکی_ڈیٹا_2->requested.logical_اونچائی);
            }
        }

        اگر (کھڑکی_ڈیٹا_2->sdlwindow->flags & SDL_کھڑکی_بلند_PIXEL_DENSITY || کھڑکی_ڈیٹا_2->scale_مقصد_display) {
            Configure_کھڑکی_Geometry(کھڑکی_ڈیٹا_2->sdlwindow);
            Commit_Libdecor_چوکھٹا(کھڑکی_ڈیٹا_2->sdlwindow);
        }
    }
}

ساکن خالی Wayland_Maybe_Update_Scale_ضربی_عدد(SDL_کھڑکی_ڈیٹا *کھڑکی)
{
    دوہرا ضربی_عدد;
    صحیح i;

    /* If the fractional scale protocol is present or the core protocol supports the
     * preferred buffer scale event, the compositor will explicitly tell the application
     * what scale it wants via these events, so don't try to determine the scale factor
     * from which displays the surface has entered.
     */
    اگر (کھڑکی->fractional_scale || wl_surface_get_نسخہ(کھڑکی->surface) >= WL_SURFACE_PREFERRED_بفر_SCALE_SINCE_نسخہ) {
        واپس;
    }

    اگر (کھڑکی->عدد_outputs != 0) {
        // Check every display's factor, use the highest
        ضربی_عدد = 0.0;
        برائے (i = 0; i < کھڑکی->عدد_outputs; i++) {
            SDL_Display_ڈیٹا *اندرونی_2 = کھڑکی->outputs[i];
            ضربی_عدد = SDL_max(ضربی_عدد, اندرونی_2->scale_ضربی_عدد_2);
        }
    } ورنہ {
        // All outputs removed, just fall back.
        ضربی_عدد = کھڑکی->scale_ضربی_عدد_2;
    }

    Wayland_Handle_Preferred_Scale_بدلا(کھڑکی, ضربی_عدد);
}

خالی Wayland_Remove_Output_From_کھڑکی(SDL_کھڑکی_ڈیٹا *کھڑکی, SDL_Display_ڈیٹا *display_ڈیٹا)
{
    برائے (صحیح i = 0; i < کھڑکی->عدد_outputs; i++) {
        اگر (کھڑکی->outputs[i] == display_ڈیٹا) { // remove this one
            اگر (i == (کھڑکی->عدد_outputs - 1)) {
                کھڑکی->outputs[i] = تہی;
            } ورنہ {
                SDL_memmove(&کھڑکی->outputs[i],
                            &کھڑکی->outputs[i + 1],
                            حجم(SDL_Display_ڈیٹا *) * ((کھڑکی->عدد_outputs - i) - 1));
            }
            کھڑکی->عدد_outputs--;
            i--;
        }
    }

    اگر (کھڑکی->عدد_outputs == 0) {
        SDL_free(کھڑکی->outputs);
        کھڑکی->outputs = تہی;
    } ورنہ اگر (!کھڑکی->is_fullscreen || کھڑکی->عدد_outputs == 1) {
        Wayland_Update_کھڑکی_Position(کھڑکی->sdlwindow);
        Wayland_Maybe_Update_Scale_ضربی_عدد(کھڑکی);
    }
}

ساکن خالی handle_surface_enter(خالی *ڈیٹا, ساخت wl_surface *surface, ساخت wl_output *output)
{
    SDL_کھڑکی_ڈیٹا *کھڑکی = ڈیٹا;
    SDL_Display_ڈیٹا *اندرونی_2 = wl_output_get_user_ڈیٹا(output);
    SDL_Display_ڈیٹا **new_outputs;

    اگر (!SDL_WAYLAND_own_output(output) || !SDL_WAYLAND_own_surface(surface)) {
        واپس;
    }

    new_outputs = SDL_realloc(کھڑکی->outputs,
                              حجم(SDL_Display_ڈیٹا *) * (کھڑکی->عدد_outputs + 1));
    اگر (!new_outputs) {
        واپس;
    }
    کھڑکی->outputs = new_outputs;
    کھڑکی->outputs[کھڑکی->عدد_outputs++] = اندرونی_2;

    // Update the scale factor after the move so that fullscreen outputs are updated.
    اگر (!کھڑکی->is_fullscreen || کھڑکی->عدد_outputs == 1) {
        Wayland_Update_کھڑکی_Position(کھڑکی->sdlwindow);
        Wayland_Maybe_Update_Scale_ضربی_عدد(کھڑکی);
    }
}

ساکن خالی handle_surface_leave(خالی *ڈیٹا, ساخت wl_surface *surface, ساخت wl_output *output)
{
    SDL_کھڑکی_ڈیٹا *کھڑکی = (SDL_کھڑکی_ڈیٹا *)ڈیٹا;

    اگر (!SDL_WAYLAND_own_output(output) || !SDL_WAYLAND_own_surface(surface)) {
        واپس;
    }

    Wayland_Remove_Output_From_کھڑکی(کھڑکی, (SDL_Display_ڈیٹا *)wl_output_get_user_ڈیٹا(output));
}

ساکن خالی handle_surface_preferred_بفر_scale(خالی *ڈیٹا, ساخت wl_surface *wl_surface, int32_t ضربی_عدد)
{
    SDL_کھڑکی_ڈیٹا *wind = ڈیٹا;

    /* The spec is unclear on how this interacts with the fractional scaling protocol,
     * so, for now, assume that the fractional scaling protocol takes priority and
     * only listen to this event if the fractional scaling protocol is not present.
     */
    اگر (!wind->fractional_scale) {
        Wayland_Handle_Preferred_Scale_بدلا(ڈیٹا, (دوہرا)ضربی_عدد);
    }
}

ساکن خالی handle_surface_preferred_بفر_transform(خالی *ڈیٹا, ساخت wl_surface *wl_surface, uint32_t transform)
{
    // Nothing to do here.
}

ساکن ثابت ساخت wl_surface_listener surface_listener = {
    handle_surface_enter,
    handle_surface_leave,
    handle_surface_preferred_بفر_scale,
    handle_surface_preferred_بفر_transform
};

ساکن خالی handle_fractional_scale_preferred(خالی *ڈیٹا, ساخت wp_fractional_scale_v1 *wp_fractional_scale_v1, uint32_t scale)
{
    ثابت دوہرا ضربی_عدد = (دوہرا)scale / 120.; // 120 is a magic number defined in the spec as a common denominator
    Wayland_Handle_Preferred_Scale_بدلا(ڈیٹا, ضربی_عدد);
}

ساکن ثابت ساخت wp_fractional_scale_v1_listener fractional_scale_listener = {
    handle_fractional_scale_preferred
};

ساکن خالی frog_preferred_metadata_handler(خالی *ڈیٹا, ساخت frog_color_managed_surface *frog_color_managed_surface, uint32_t transfer_function,
                                            uint32_t output_display_primary_red_x, uint32_t output_display_primary_red_y,
                                            uint32_t output_display_primary_green_x, uint32_t output_display_primary_green_y,
                                            uint32_t output_display_primary_blue_x, uint32_t output_display_primary_blue_y,
                                            uint32_t output_white_نقطہ_x, uint32_t output_white_نقطہ_y,
                                            uint32_t max_luminance, uint32_t min_luminance,
                                            uint32_t max_بھرا_چوکھٹا_luminance)
{
    SDL_کھڑکی_ڈیٹا *wind = (SDL_کھڑکی_ڈیٹا *)ڈیٹا;
    SDL_HDROutputProperties HDR;

    SDL_zero(HDR);

    انتخاب (transfer_function) {
    حالت FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_ST2084_PQ:
        /* ITU-R BT.2408-7 (Sept 2023) has the reference PQ white level at 203 nits,
         * while older Dolby documentation claims a reference level of 100 nits.
         *
         * Use 203 nits for now.
         */
        HDR.HDR_headroom = max_luminance / 203.0f;
        توڑو;
    حالت FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_SCRGB_خطی:
        HDR.HDR_headroom = max_luminance / 80.0f;
        توڑو;
    حالت FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_UNDEFINED:
    حالت FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_SRGB:
    حالت FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_GAMMA_22:
    طےشدہ:
        HDR.HDR_headroom = 1.0f;
        توڑو;
    }

    HDR.SDR_white_level = 1.0f;
    SDL_سیٹ_کھڑکی_HDRProperties(wind->sdlwindow, &HDR, true);
}

ساکن ثابت ساخت frog_color_managed_surface_listener frog_surface_listener = {
    frog_preferred_metadata_handler
};


ساکن خالی handle_surface_feedback_preferred_changed2(خالی *ڈیٹا,
                                                       ساخت wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback_v1,
                                                       uint32_t شناختی_عنصر_hi, uint32_t شناختی_عنصر_lo)
{
    SDL_کھڑکی_ڈیٹا *wind = (SDL_کھڑکی_ڈیٹا *)ڈیٹا;
    Wayland_Get_Color_Info_For_کھڑکی(wind, false);
}

ساکن خالی handle_surface_feedback_preferred_بدلا(خالی *ڈیٹا,
                                                      ساخت wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback_v1,
                                                      uint32_t شناختی_عنصر)
{
    handle_surface_feedback_preferred_changed2(ڈیٹا, wp_color_management_surface_feedback_v1, 0, شناختی_عنصر);
}

ساکن ثابت ساخت wp_color_management_surface_feedback_v1_listener color_management_surface_feedback_listener = {
    handle_surface_feedback_preferred_بدلا,
    handle_surface_feedback_preferred_changed2
};

ساکن خالی Wayland_سیٹ_Keyboard_Focus(SDL_کھڑکی *کھڑکی, bool سیٹ_focus)
{
    SDL_کھڑکی *toplevel = کھڑکی;

    // Find the toplevel parent
    جب (SDL_کھڑکی_IS_POPUP(toplevel)) {
        toplevel = toplevel->والد;
    }

    toplevel->keyboard_focus = کھڑکی;

    اگر (سیٹ_focus && !کھڑکی->is_hiding && !کھڑکی->is_destroying) {
        SDL_سیٹ_Keyboard_Focus(کھڑکی);
    }
}

bool Wayland_سیٹ_کھڑکی_کامیابی_Test(SDL_کھڑکی *کھڑکی, bool enabled)
{
    واپس true; // just succeed, the real work is done elsewhere.
}

ساکن ساخت xdg_toplevel *Get_Toplevel_For_کھڑکی(SDL_کھڑکی_ڈیٹا *wind)
{
    اگر (wind) {
        /* Libdecor crashes on attempts to unset the parent by passing null, which is allowed by the
         * toplevel spec, so just use the raw xdg-toplevel instead (that's what libdecor does
         * internally anyways).
         */
#اگر_تعریف_شدہ HAVE_LIBDECOR_H
        اگر (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.چوکھٹا) {
            واپس libdecor_چوکھٹا_get_xdg_toplevel(wind->shell_surface.libdecor.چوکھٹا);
        } ورنہ
#اگر_ختم
            اگر (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
                واپس wind->shell_surface.xdg.toplevel.xdg_toplevel;
            }
    }

    واپس تہی;
}

bool Wayland_سیٹ_کھڑکی_والد(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_کھڑکی *والد_کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *بچہ_ڈیٹا = کھڑکی->اندرونی_2;
    SDL_کھڑکی_ڈیٹا *والد_ڈیٹا = والد_کھڑکی ? والد_کھڑکی->اندرونی_2 : تہی;

    بچہ_ڈیٹا->reparenting_required = false;

    اگر (والد_ڈیٹا && والد_ڈیٹا->shell_surface_حالت != WAYLAND_SHELL_SURFACE_حالت_SHOWN) {
        // Need to wait for the parent to become mapped, or it's the same as setting a null parent.
        بچہ_ڈیٹا->reparenting_required = true;
        واپس true;
    }

    ساخت xdg_toplevel *بچہ_toplevel = Get_Toplevel_For_کھڑکی(بچہ_ڈیٹا);
    ساخت xdg_toplevel *والد_toplevel = Get_Toplevel_For_کھڑکی(والد_ڈیٹا);

    اگر (بچہ_toplevel) {
        xdg_toplevel_سیٹ_والد(بچہ_toplevel, والد_toplevel);
    }

    واپس true;
}

bool Wayland_سیٹ_کھڑکی_Modal(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool modal)
{
    SDL_Video_ڈیٹا *viddata = _this->اندرونی_2;
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    SDL_کھڑکی_ڈیٹا *والد_ڈیٹا = کھڑکی->والد->اندرونی_2;

    اگر (والد_ڈیٹا->shell_surface_حالت != WAYLAND_SHELL_SURFACE_حالت_SHOWN) {
        // Need to wait for the parent to become mapped before changing modal status.
        ڈیٹا->reparenting_required = true;
        واپس true;
    } ورنہ {
        ڈیٹا->reparenting_required = false;
    }

    ساخت xdg_toplevel *toplevel = Get_Toplevel_For_کھڑکی(ڈیٹا);

    اگر (toplevel) {
        اگر (viddata->xdg_wm_dialog_v1) {
            اگر (modal) {
                اگر (!ڈیٹا->xdg_dialog_v1) {
                    ڈیٹا->xdg_dialog_v1 = xdg_wm_dialog_v1_get_xdg_dialog(viddata->xdg_wm_dialog_v1, toplevel);
                }

                xdg_dialog_v1_سیٹ_modal(ڈیٹا->xdg_dialog_v1);
            } ورنہ اگر (ڈیٹا->xdg_dialog_v1) {
                xdg_dialog_v1_unset_modal(ڈیٹا->xdg_dialog_v1);
            }
        }
    }

    واپس true;
}

ساکن خالی Wayland_رجسٹر_Toplevel_For_Session(SDL_کھڑکی_ڈیٹا *ڈیٹا)
{
    ساخت xdg_toplevel *toplevel = Get_Toplevel_For_کھڑکی(ڈیٹا);
    اگر (!toplevel) {
        واپس;
    }

    ثابت حرف *id = SDL_GetStringProperty(ڈیٹا->sdlwindow->props, SDL_PROP_کھڑکی_WAYLAND_کھڑکی_ID_STRING, تہی);
    اگر (id && *id != '\0') {
        SDL_VideoDevice *viddev = SDL_GetVideoDevice();
        SDL_Video_ڈیٹا *viddata = viddev->اندرونی_2;

        اگر (viddata->xdg_toplevel_لیبل_manager) {
            xdg_toplevel_لیبل_manager_v1_سیٹ_toplevel_لیبل(viddata->xdg_toplevel_لیبل_manager, toplevel, id);
        }

        اگر (viddata->xdg_session_manager) {
            Wayland_CreateSession(viddata);

            اگر (viddata->xdg_session) {
                CHECK_PARAM (true) {
                    // Windows added to a session must not have a duplicate ID string, or a protocol error will result.
                    برائے (SDL_کھڑکی *w = viddev->windows; w; w = w->اگلا) {
                        SDL_کھڑکی_ڈیٹا *d = w->اندرونی_2;
                        اگر (d->session_id && SDL_strcmp(d->session_id, id) == 0) {
                            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Duplicate window ID string %s found; window will not be added to session", id);
                            واپس;
                        }
                    }
                }

                ڈیٹا->xdg_toplevel_session = xdg_session_v1_restore_toplevel(viddata->xdg_session, toplevel, id);
                ڈیٹا->session_id = SDL_strdup(id);
            }
        }
    }
}

ساکن خالی Wayland_DestroyToplevelSession(SDL_کھڑکی_ڈیٹا *ڈیٹا)
{
    SDL_Video_ڈیٹا *viddata = ڈیٹا->wayland_ڈیٹا;

    اگر (ڈیٹا->xdg_toplevel_session) {
        ثابت حرف *id = SDL_GetStringProperty(ڈیٹا->sdlwindow->props, SDL_PROP_کھڑکی_WAYLAND_کھڑکی_ID_STRING, تہی);

        // If the ID string was cleared, remove the window from the session.
        اگر (!id || *id == '\0') {
            xdg_session_v1_remove_toplevel(viddata->xdg_session, ڈیٹا->session_id);
        }

        xdg_toplevel_session_v1_destroy(ڈیٹا->xdg_toplevel_session);
        ڈیٹا->xdg_toplevel_session = تہی;

        SDL_free(ڈیٹا->session_id);
        ڈیٹا->session_id = تہی;
    }
}

ساکن خالی show_hide_sync_handler(خالی *ڈیٹا, ساخت wl_callback *callback, uint32_t callback_ڈیٹا)
{
    // Get the window from the ID as it may have been destroyed
    SDL_کھڑکی_ID کھڑکی_ID = (SDL_کھڑکی_ID)((uintptr_t)ڈیٹا);
    SDL_کھڑکی *کھڑکی = SDL_Get_کھڑکی_From_ID(کھڑکی_ID);

    اگر (کھڑکی && کھڑکی->اندرونی_2) {
        SDL_کھڑکی_ڈیٹا *wind = کھڑکی->اندرونی_2;
        wind->show_hide_sync_required = false;
    }

    wl_callback_destroy(callback);
}

ساکن ساخت wl_callback_listener show_hide_sync_listener = {
    show_hide_sync_handler
};

ساکن خالی exported_handle_handler(خالی *ڈیٹا, ساخت zxdg_exported_v2 *zxdg_exported_v2, ثابت حرف *handle)
{
    SDL_کھڑکی_ڈیٹا *wind = (SDL_کھڑکی_ڈیٹا *)ڈیٹا;
    SDL_PropertiesID props = SDL_Get_کھڑکی_Properties(wind->sdlwindow);

    SDL_سیٹ_String_Property(props, SDL_PROP_کھڑکی_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, handle);
}

ساکن ساخت zxdg_exported_v2_listener exported_v2_listener = {
    exported_handle_handler
};

خالی Wayland_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_ڈیٹا *c = _this->اندرونی_2;
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    SDL_PropertiesID props = SDL_Get_کھڑکی_Properties(کھڑکی);

    // Custom surfaces don't get toplevels and are always considered 'shown'; nothing to do here.
    اگر (ڈیٹا->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        واپس;
    }

    /* If this is a child window, the parent *must* be in the final shown state,
     * meaning that it has received a configure event, followed by a frame callback.
     * If not, a race condition can result, with effects ranging from the child
     * window to spuriously closing to protocol errors.
     *
     * If waiting on the parent window, set the pending status and the window will
     * be shown when the parent is in the shown state.
     */
    اگر (کھڑکی->والد) {
        اگر (کھڑکی->والد->اندرونی_2->shell_surface_حالت != WAYLAND_SHELL_SURFACE_حالت_SHOWN) {
            ڈیٹا->shell_surface_حالت = WAYLAND_SHELL_SURFACE_حالت_SHOW_PENDING;
            واپس;
        }
    }

    // Always roundtrip to ensure there are no pending buffer attachments.
    کرو {
        WAYLAND_wl_display_roundtrip(c->display);
    } جب (ڈیٹا->show_hide_sync_required);

    ڈیٹا->shell_surface_حالت = WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_CONFIGURE;

    /* Detach any previous buffers before resetting everything, otherwise when
     * calling this a second time you'll get an annoying protocol error!
     *
     * FIXME: This was originally moved to HideWindow, which _should_ make
     * sense, but for whatever reason UE5's popups require that this actually
     * be in both places at once? Possibly from renderers making commits? I can't
     * fully remember if this location caused crashes or if I was fixing a pair
     * of Hide/Show calls. In any case, UE gives us a pretty good test and having
     * both detach calls passes. This bug may be relevant if I'm wrong:
     *
     * https://bugs.kde.org/show_bug.cgi?id=448856
     *
     * -flibit
     */
    wl_surface_attach(ڈیٹا->surface, تہی, 0, 0);
    wl_surface_commit(ڈیٹا->surface);

    // Create the shell surface and map the toplevel/popup
#اگر_تعریف_شدہ HAVE_LIBDECOR_H
    اگر (ڈیٹا->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ڈیٹا->shell_surface.libdecor.چوکھٹا = libdecor_decorate(c->shell.libdecor,
                                                               ڈیٹا->surface,
                                                               &libdecor_چوکھٹا_interface,
                                                               ڈیٹا);
        اگر (!ڈیٹا->shell_surface.libdecor.چوکھٹا) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Failed to create libdecor frame!");
        } ورنہ {
            libdecor_چوکھٹا_سیٹ_app_id(ڈیٹا->shell_surface.libdecor.چوکھٹا, ڈیٹا->app_id);
            libdecor_چوکھٹا_map(ڈیٹا->shell_surface.libdecor.چوکھٹا);
            اگر (کھڑکی->flags & SDL_کھڑکی_BORDERLESS) {
                // Note: Calling this with 'true' immediately after mapping will cause the libdecor Cairo plugin to crash.
                libdecor_چوکھٹا_سیٹ_visibility(ڈیٹا->shell_surface.libdecor.چوکھٹا, false);
            }

            اگر (c->zxdg_exporter_v2) {
                ڈیٹا->exported = zxdg_exporter_v2_export_toplevel(c->zxdg_exporter_v2, ڈیٹا->surface);
                zxdg_exported_v2_جوڑو_listener(ڈیٹا->exported, &exported_v2_listener, ڈیٹا);
            }

            اگر (c->xdg_toplevel_icon_manager_v1 && ڈیٹا->xdg_toplevel_icon_v1) {
                xdg_toplevel_icon_manager_v1_سیٹ_icon(_this->اندرونی_2->xdg_toplevel_icon_manager_v1,
                                                      libdecor_چوکھٹا_get_xdg_toplevel(ڈیٹا->shell_surface.libdecor.چوکھٹا),
                                                      ڈیٹا->xdg_toplevel_icon_v1);
            }

            SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WAYLAND_XDG_SURFACE_اشارہ_گر, libdecor_چوکھٹا_get_xdg_surface(ڈیٹا->shell_surface.libdecor.چوکھٹا));
            SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WAYLAND_XDG_TOPLEVEL_اشارہ_گر, libdecor_چوکھٹا_get_xdg_toplevel(ڈیٹا->shell_surface.libdecor.چوکھٹا));
        }
    } ورنہ
#اگر_ختم
    اگر (ڈیٹا->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL || ڈیٹا->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        ڈیٹا->shell_surface.xdg.surface = xdg_wm_بنیاد_get_xdg_surface(c->shell.xdg, ڈیٹا->surface);
        xdg_surface_سیٹ_user_ڈیٹا(ڈیٹا->shell_surface.xdg.surface, ڈیٹا);
        xdg_surface_جوڑو_listener(ڈیٹا->shell_surface.xdg.surface, &_xdg_surface_listener, ڈیٹا);
        SDL_سیٹ_اشارہ_گر_Property(SDL_Get_کھڑکی_Properties(کھڑکی), SDL_PROP_کھڑکی_WAYLAND_XDG_SURFACE_اشارہ_گر, ڈیٹا->shell_surface.xdg.surface);

        اگر (ڈیٹا->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
            SDL_کھڑکی *والد = کھڑکی->والد;
            SDL_کھڑکی_ڈیٹا *والد_ڈیٹا = والد->اندرونی_2;
            ساخت xdg_surface *والد_xdg_surface = تہی;
            صحیح position_x = 0, position_y = 0;

            // Configure the popup parameters
#اگر_تعریف_شدہ HAVE_LIBDECOR_H
            اگر (والد_ڈیٹا->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                والد_xdg_surface = libdecor_چوکھٹا_get_xdg_surface(والد_ڈیٹا->shell_surface.libdecor.چوکھٹا);
            } ورنہ
#اگر_ختم
            اگر (والد_ڈیٹا->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL ||
                    والد_ڈیٹا->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
                والد_xdg_surface = والد_ڈیٹا->shell_surface.xdg.surface;
            }

            // Set up the positioner for the popup and configure the constraints
            ڈیٹا->shell_surface.xdg.popup.xdg_positioner = xdg_wm_بنیاد_create_positioner(c->shell.xdg);
            xdg_positioner_سیٹ_anchor(ڈیٹا->shell_surface.xdg.popup.xdg_positioner, XDG_POSITIONER_ANCHOR_چوٹی_بایاں);
            SDL_Rect والد_geometry;
            Get_کھڑکی_Geometry(والد->اندرونی_2, &والد_geometry);
            xdg_positioner_سیٹ_anchor_rect(ڈیٹا->shell_surface.xdg.popup.xdg_positioner, 0, 0, والد_geometry.w, والد_geometry.h);

            ثابت Uint32 constraint = کھڑکی->constrain_popup ? (XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_SLIDE_X | XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_SLIDE_Y) : XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_NONE;
            xdg_positioner_سیٹ_constraint_adjustment(ڈیٹا->shell_surface.xdg.popup.xdg_positioner, constraint);
            xdg_positioner_سیٹ_gravity(ڈیٹا->shell_surface.xdg.popup.xdg_positioner, XDG_POSITIONER_GRAVITY_BOTTOM_دایاں);
            xdg_positioner_سیٹ_سائز(ڈیٹا->shell_surface.xdg.popup.xdg_positioner, ڈیٹا->current.logical_چوڑائی, ڈیٹا->current.logical_اونچائی);

            // Set the popup initial position
            position_x = کھڑکی->آخری_position_pending ? کھڑکی->pending.x : کھڑکی->x;
            position_y = کھڑکی->آخری_position_pending ? کھڑکی->pending.y : کھڑکی->y;
            EnsurePopupPositionIsValid(کھڑکی, &position_x, &position_y);
            اگر (ڈیٹا->scale_مقصد_display) {
                position_x = Pixel_مقصد_نقطہ(کھڑکی->والد, position_x);
                position_y = Pixel_مقصد_نقطہ(کھڑکی->والد, position_y);
            }
            Adjust_Popup_انحراف(کھڑکی, &position_x, &position_y);
            xdg_positioner_سیٹ_انحراف(ڈیٹا->shell_surface.xdg.popup.xdg_positioner, position_x, position_y);

            // Assign the popup role
            ڈیٹا->shell_surface.xdg.popup.xdg_popup = xdg_surface_get_popup(ڈیٹا->shell_surface.xdg.surface,
                                                                                والد_xdg_surface,
                                                                                ڈیٹا->shell_surface.xdg.popup.xdg_positioner);
            xdg_popup_جوڑو_listener(ڈیٹا->shell_surface.xdg.popup.xdg_popup, &_xdg_popup_listener, ڈیٹا);

            اگر (کھڑکی->flags & SDL_کھڑکی_TOOLTIP) {
                ساخت wl_region *region;

                // Tooltips can't be interacted with, so turn off the input region to avoid blocking anything behind them
                region = wl_compositor_create_region(c->compositor);
                wl_region_جوڑو(region, 0, 0, 0, 0);
                wl_surface_سیٹ_داخلہ_region(ڈیٹا->surface, region);
                wl_region_destroy(region);
            } ورنہ اگر ((کھڑکی->flags & SDL_کھڑکی_POPUP_MENU) && !(کھڑکی->flags & SDL_کھڑکی_NOT_FOCUSABLE)) {
                Wayland_سیٹ_Keyboard_Focus(کھڑکی, true);
            }

            SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WAYLAND_XDG_POPUP_اشارہ_گر, ڈیٹا->shell_surface.xdg.popup.xdg_popup);
            SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WAYLAND_XDG_POSITIONER_اشارہ_گر, ڈیٹا->shell_surface.xdg.popup.xdg_positioner);
        } ورنہ {
            ڈیٹا->shell_surface.xdg.toplevel.xdg_toplevel = xdg_surface_get_toplevel(ڈیٹا->shell_surface.xdg.surface);
            xdg_toplevel_سیٹ_app_id(ڈیٹا->shell_surface.xdg.toplevel.xdg_toplevel, ڈیٹا->app_id);
            xdg_toplevel_جوڑو_listener(ڈیٹا->shell_surface.xdg.toplevel.xdg_toplevel, &toplevel_listener_xdg, ڈیٹا);

            // Create the window decorations
            اگر (c->decoration_manager) {
                ڈیٹا->server_decoration = zxdg_decoration_manager_v1_get_toplevel_decoration(c->decoration_manager, ڈیٹا->shell_surface.xdg.toplevel.xdg_toplevel);
                zxdg_toplevel_decoration_v1_جوڑو_listener(ڈیٹا->server_decoration, &xdg_toplevel_decoration_listener, کھڑکی);
                ثابت شمار zxdg_toplevel_decoration_v1_منوال منوال = !(کھڑکی->flags & SDL_کھڑکی_BORDERLESS) ? ZXDG_TOPLEVEL_DECORATION_V1_منوال_SERVER_SIDE : ZXDG_TOPLEVEL_DECORATION_V1_منوال_CLIENT_SIDE;
                zxdg_toplevel_decoration_v1_سیٹ_منوال(ڈیٹا->server_decoration, منوال);
            }

            اگر (c->zxdg_exporter_v2) {
                ڈیٹا->exported = zxdg_exporter_v2_export_toplevel(c->zxdg_exporter_v2, ڈیٹا->surface);
                zxdg_exported_v2_جوڑو_listener(ڈیٹا->exported, &exported_v2_listener, ڈیٹا);
            }

            اگر (c->xdg_toplevel_icon_manager_v1 && ڈیٹا->xdg_toplevel_icon_v1) {
                xdg_toplevel_icon_manager_v1_سیٹ_icon(_this->اندرونی_2->xdg_toplevel_icon_manager_v1,
                                                      ڈیٹا->shell_surface.xdg.toplevel.xdg_toplevel,
                                                      ڈیٹا->xdg_toplevel_icon_v1);
            }

            SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WAYLAND_XDG_TOPLEVEL_اشارہ_گر, ڈیٹا->shell_surface.xdg.toplevel.xdg_toplevel);
        }
    }

    // Restore state that was set prior to this call
    Wayland_رجسٹر_Toplevel_For_Session(ڈیٹا);
    Wayland_سیٹ_کھڑکی_والد(_this, کھڑکی, کھڑکی->والد);

    اگر (کھڑکی->flags & SDL_کھڑکی_MODAL) {
        Wayland_سیٹ_کھڑکی_Modal(_this, کھڑکی, true);
    }

    Wayland_سیٹ_کھڑکی_Title(_this, کھڑکی);

    /* We have to wait until the surface gets a "configure" event, or use of
     * this surface will fail. This is a new rule for xdg_shell.
     */
#اگر_تعریف_شدہ HAVE_LIBDECOR_H
    اگر (ڈیٹا->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        اگر (ڈیٹا->shell_surface.libdecor.چوکھٹا) {
            جب (ڈیٹا->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_CONFIGURE) {
                اگر (libdecor_dispatch(c->shell.libdecor, -1) < 0) {
                    اگر (!Wayland_HandleDisplayDisconnected(_this)) {
                        واپس;
                    }
                }
                اگر (WAYLAND_wl_display_dispatch_pending(c->display) < 0) {
                    اگر (!Wayland_HandleDisplayDisconnected(_this)) {
                        واپس;
                    }
                }
            }
        }
    } ورنہ
#اگر_ختم
        اگر (ڈیٹا->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP || ڈیٹا->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        /* Unlike libdecor we need to call this explicitly to prevent a deadlock.
         * libdecor will call this as part of their configure event!
         * -flibit
         */
        wl_surface_commit(ڈیٹا->surface);
        اگر (ڈیٹا->shell_surface.xdg.surface) {
            جب (ڈیٹا->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_CONFIGURE) {
                اگر (WAYLAND_wl_display_dispatch(c->display) < 0) {
                    اگر (!Wayland_HandleDisplayDisconnected(_this)) {
                        واپس;
                    }
                }
            }
        }
    } ورنہ {
        // Nothing to see here, just commit.
        wl_surface_commit(ڈیٹا->surface);
    }

    // Make sure the window can't be resized to 0, or it can be spuriously closed by the window manager.
    ڈیٹا->system_limits.min_چوڑائی_2 = SDL_max(ڈیٹا->system_limits.min_چوڑائی_2, 1);
    ڈیٹا->system_limits.min_اونچائی_2 = SDL_max(ڈیٹا->system_limits.min_اونچائی_2, 1);

    /* Unlike the rest of window state we have to set this _after_ flushing the
     * display, because we need to create the decorations before possibly hiding
     * them immediately afterward.
     */
#اگر_تعریف_شدہ HAVE_LIBDECOR_H
    اگر (ڈیٹا->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        // Libdecor plugins can enforce minimum window sizes, so adjust if the initial window size is too small.
        اگر (کھڑکی->windowed.w < ڈیٹا->system_limits.min_چوڑائی_2 ||
            کھڑکی->windowed.h < ڈیٹا->system_limits.min_اونچائی_2) {

            // Warn if the window frame will be larger than the content surface.
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO,
                        "Window dimensions (%i, %i) are smaller than the system enforced minimum (%i, %i); window borders will be larger than the content surface.",
                        کھڑکی->windowed.w, کھڑکی->windowed.h, ڈیٹا->system_limits.min_چوڑائی_2, ڈیٹا->system_limits.min_اونچائی_2);

            ڈیٹا->current.logical_چوڑائی = SDL_max(کھڑکی->windowed.w, ڈیٹا->system_limits.min_چوڑائی_2);
            ڈیٹا->current.logical_اونچائی = SDL_max(کھڑکی->windowed.h, ڈیٹا->system_limits.min_اونچائی_2);
            Commit_Libdecor_چوکھٹا(کھڑکی);
        }
    }
#اگر_ختم
    Wayland_سیٹ_کھڑکی_Resizable(_this, کھڑکی, !!(کھڑکی->flags & SDL_کھڑکی_RESIZABLE));

    // We're finally done putting the window together, raise if possible
    اگر (c->activation_manager && SDL_GetHintBoolean(SDL_HINT_کھڑکی_ACTIVATE_WHEN_SHOWN, true)) {
        /* if the process was passed an activation token, use it when showing
         * the initial window.
         *
         * Note that we don't check for empty strings, as that is still
         * considered a valid activation token!
         */
        ثابت حرف *activation_token = SDL_getenv("XDG_ACTIVATION_TOKEN");
        اگر (activation_token) {
            xdg_activation_v1_activate(c->activation_manager,
                                       activation_token,
                                       ڈیٹا->surface);

            // Clear this variable, per the protocol's request
            SDL_unsetenv_unsafe("XDG_ACTIVATION_TOKEN");
        } ورنہ {
            // Try to generate an activation token for this window.
            Wayland_Raise_کھڑکی(_this, کھڑکی);
        }
    } ورنہ {
        // Clear the ignored activation token, as it won't be used.
        SDL_unsetenv_unsafe("XDG_ACTIVATION_TOKEN");
    }

    // No frame callback on an external surface, as it may already have one attached.
    اگر (!(کھڑکی->flags & SDL_کھڑکی_EXTERNAL)) {
        // Fire a callback when the compositor wants a new frame.
        ڈیٹا->surface_چوکھٹا_callback = wl_surface_چوکھٹا(ڈیٹا->surface);
        wl_callback_جوڑو_listener(ڈیٹا->surface_چوکھٹا_callback, &surface_چوکھٹا_listener, ڈیٹا);
    }

    ڈیٹا->show_hide_sync_required = true;
    ساخت wl_callback *cb = wl_display_sync(_this->اندرونی_2->display);
    wl_callback_جوڑو_listener(cb, &show_hide_sync_listener, (خالی *)((uintptr_t)کھڑکی->id));

    ڈیٹا->showing_کھڑکی = true;
    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_SHOWN, 0, 0);
    ڈیٹا->showing_کھڑکی = false;

    // Send an exposure event to signal that the client should draw.
    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_EXPOSED, 0, 0);
}

ساکن خالی Wayland_ReleasePopup(SDL_VideoDevice *_this, SDL_کھڑکی *popup)
{
    SDL_کھڑکی_ڈیٹا *popupdata;

    // Basic sanity checks to weed out the weird popup closures
    اگر (!SDL_ObjectValid(popup, SDL_OBJECT_TYPE_کھڑکی)) {
        واپس;
    }
    popupdata = popup->اندرونی_2;
    اگر (!popupdata) {
        واپس;
    }

    // This may already be freed by a parent popup!
    اگر (popupdata->shell_surface.xdg.popup.xdg_popup == تہی) {
        واپس;
    }

    اگر ((popup->flags & SDL_کھڑکی_POPUP_MENU) && !(popup->flags & SDL_کھڑکی_NOT_FOCUSABLE)) {
        SDL_کھڑکی *new_focus;
        ثابت bool سیٹ_focus = SDL_ShouldRelinquishPopupFocus(popup, &new_focus);
        Wayland_سیٹ_Keyboard_Focus(new_focus, سیٹ_focus);
    }

    xdg_popup_destroy(popupdata->shell_surface.xdg.popup.xdg_popup);
    xdg_positioner_destroy(popupdata->shell_surface.xdg.popup.xdg_positioner);
    popupdata->shell_surface.xdg.popup.xdg_popup = تہی;
    popupdata->shell_surface.xdg.popup.xdg_positioner = تہی;

    SDL_PropertiesID props = SDL_Get_کھڑکی_Properties(popup);
    SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WAYLAND_XDG_POPUP_اشارہ_گر, تہی);
    SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WAYLAND_XDG_POSITIONER_اشارہ_گر, تہی);
}

خالی Wayland_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    SDL_کھڑکی_ڈیٹا *wind = کھڑکی->اندرونی_2;
    SDL_PropertiesID props = SDL_Get_کھڑکی_Properties(کھڑکی);

    // Custom surfaces have nothing to destroy and are always considered to be 'shown'; nothing to do here.
    اگر (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        واپس;
    }

    /* The window was shown, but the sync point hasn't yet been reached.
     * Pump events to avoid a possible protocol violation.
     */
    اگر (wind->show_hide_sync_required) {
        WAYLAND_wl_display_roundtrip(ڈیٹا->display);
    }

    wind->shell_surface_حالت = WAYLAND_SHELL_SURFACE_حالت_HIDDEN;

    اگر (wind->surface_چوکھٹا_callback) {
        wl_callback_destroy(wind->surface_چوکھٹا_callback);
        wind->surface_چوکھٹا_callback = تہی;
    }

    اگر (wind->server_decoration) {
        zxdg_toplevel_decoration_v1_destroy(wind->server_decoration);
        wind->server_decoration = تہی;
    }

    // Clean up the export handle.
    اگر (wind->exported) {
        zxdg_exported_v2_destroy(wind->exported);
        wind->exported = تہی;

        SDL_سیٹ_String_Property(props, SDL_PROP_کھڑکی_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, تہی);
    }

    اگر (wind->xdg_dialog_v1) {
        xdg_dialog_v1_destroy(wind->xdg_dialog_v1);
        wind->xdg_dialog_v1 = تہی;
    }

#اگر_تعریف_شدہ HAVE_LIBDECOR_H
    اگر (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        اگر (wind->shell_surface.libdecor.چوکھٹا) {
            libdecor_چوکھٹا_unref(wind->shell_surface.libdecor.چوکھٹا);

            SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WAYLAND_XDG_SURFACE_اشارہ_گر, تہی);
            SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WAYLAND_XDG_TOPLEVEL_اشارہ_گر, تہی);
        }
    } ورنہ
#اگر_ختم
    {
        اگر (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
            Wayland_ReleasePopup(_this, کھڑکی);
        } ورنہ اگر (wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            xdg_toplevel_destroy(wind->shell_surface.xdg.toplevel.xdg_toplevel);
            SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WAYLAND_XDG_TOPLEVEL_اشارہ_گر, تہی);
        }

        اگر (wind->shell_surface.xdg.surface) {
            xdg_surface_destroy(wind->shell_surface.xdg.surface);
            SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WAYLAND_XDG_SURFACE_اشارہ_گر, تہی);
        }
    }

    // Attach a null buffer to unmap the surface.
    اگر (wind->نقاب.surface) {
        wl_surface_attach(wind->نقاب.surface, تہی, 0, 0);
        wl_surface_commit(wind->نقاب.surface);
    }
    wl_surface_attach(wind->surface, تہی, 0, 0);
    wl_surface_commit(wind->surface);

    // Need to destroy the session object after unmapping the window, or the state may not be saved.
    Wayland_DestroyToplevelSession(wind);

    SDL_zero(wind->shell_surface);
    SDL_zero(wind->explicit_geometry);
    wind->show_hide_sync_required = true;
    ساخت wl_callback *cb = wl_display_sync(_this->اندرونی_2->display);
    wl_callback_جوڑو_listener(cb, &show_hide_sync_listener, (خالی *)((uintptr_t)کھڑکی->id));
}

ساکن خالی handle_xdg_activation_مکمل(خالی *ڈیٹا,
                                       ساخت xdg_activation_token_v1 *xdg_activation_token_v1,
                                       ثابت حرف *token)
{
    SDL_کھڑکی_ڈیٹا *کھڑکی = ڈیٹا;
    اگر (xdg_activation_token_v1 == کھڑکی->activation_token) {
        xdg_activation_v1_activate(کھڑکی->wayland_ڈیٹا->activation_manager,
                                   token,
                                   کھڑکی->surface);
        xdg_activation_token_v1_destroy(کھڑکی->activation_token);
        کھڑکی->activation_token = تہی;
    }
}

ساکن ثابت ساخت xdg_activation_token_v1_listener xdg_activation_listener = {
    handle_xdg_activation_مکمل
};

/* The xdg-activation protocol considers "activation" to be one of two things:
 *
 * 1: Raising a window to the top and flashing the titlebar
 * 2: Flashing the titlebar while keeping the window where it is
 *
 * As you might expect from Wayland, the general policy is to go with #2 unless
 * the client can prove to the compositor beyond a reasonable doubt that raising
 * the window will not be malicious behavior.
 *
 * For SDL this means RaiseWindow and FlashWindow both use the same protocol,
 * but in different ways: RaiseWindow will provide as _much_ information as
 * possible while FlashWindow will provide as _little_ information as possible,
 * to nudge the compositor into doing what we want.
 *
 * This isn't _strictly_ what the protocol says will happen, but this is what
 * current implementations are doing (as of writing, YMMV in the far distant
 * future).
 *
 * -flibit
 */
ساکن خالی Wayland_activate_کھڑکی(SDL_Video_ڈیٹا *ڈیٹا, SDL_کھڑکی_ڈیٹا *ہدف_wind, bool سیٹ_serial)
{
    SDL_WaylandSeat *seat = ڈیٹا->آخری_implicit_grab_seat;
    SDL_کھڑکی_ڈیٹا *focus = تہی;

    اگر (seat) {
        focus = seat->keyboard.focus;
        اگر (!focus) {
            focus = seat->اشارہ_گر_2.focus;
        }
    }

    ساخت wl_surface *requesting_surface = focus ? focus->surface : تہی;

    اگر (ڈیٹا->activation_manager) {
        اگر (ہدف_wind->activation_token) {
            // We're about to overwrite this with a new request
            xdg_activation_token_v1_destroy(ہدف_wind->activation_token);
        }

        ہدف_wind->activation_token = xdg_activation_v1_get_activation_token(ڈیٹا->activation_manager);
        xdg_activation_token_v1_جوڑو_listener(ہدف_wind->activation_token,
                                             &xdg_activation_listener,
                                             ہدف_wind);

        /* Note that we are not setting the app_id here.
         *
         * Hypothetically we could set the app_id from data->classname, but
         * that part of the API is for _external_ programs, not ourselves.
         *
         * -flibit
         */
        اگر (requesting_surface) {
            // This specifies the surface from which the activation request is originating, not the activation target surface.
            xdg_activation_token_v1_سیٹ_surface(ہدف_wind->activation_token, requesting_surface);
        }
        اگر (سیٹ_serial && seat && seat->wl_seat) {
            xdg_activation_token_v1_سیٹ_serial(ہدف_wind->activation_token, seat->آخری_implicit_grab_serial, seat->wl_seat);
        }
        xdg_activation_token_v1_commit(ہدف_wind->activation_token);
    }
}

خالی Wayland_Raise_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_ڈیٹا *viddata = _this->اندرونی_2;
    SDL_کھڑکی_ڈیٹا *wind = کھڑکی->اندرونی_2;

    اگر (viddata->activation_manager) {
        /* Check for an activation token, in case the window is being
         * raised in response to a system notification.
         *
         * Note that we don't check for empty strings, as that is still
         * considered a valid activation token!
         */
        ثابت حرف *activation_token = SDL_GetNotificationActivationToken();
        اگر (activation_token) {
            xdg_activation_v1_activate(viddata->activation_manager,
                                       activation_token,
                                       wind->surface);
            واپس;
        }
    }

    // No token? Try to activate the window via an event serial.
    Wayland_activate_کھڑکی(_this->اندرونی_2, کھڑکی->اندرونی_2, true);
}

bool Wayland_Flash_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_FlashOperation operation)
{
    /* Not setting the serial will specify 'urgency' without switching focus as per
     * https://gitlab.freedesktop.org/wayland/wayland-protocols/-/merge_requests/9#note_854977
     */
    Wayland_activate_کھڑکی(_this->اندرونی_2, کھڑکی->اندرونی_2, false);
    واپس true;
}

SDL_Fullscreen_نتیجہ Wayland_سیٹ_کھڑکی_Fullscreen(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی,
                                 SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_کھڑکی_ڈیٹا *wind = کھڑکی->اندرونی_2;
    ساخت wl_output *output = display->اندرونی_2->output;

    // Custom surfaces have no toplevel to make fullscreen.
    اگر (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        واپس SDL_FULLSCREEN_FAILED;
    }

    // Drop fullscreen leave requests when showing the window.
    اگر (wind->showing_کھڑکی && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        واپس SDL_FULLSCREEN_SUCCEEDED;
    }

    اگر (wind->show_hide_sync_required) {
        WAYLAND_wl_display_roundtrip(_this->اندرونی_2->display);
    }

    // Flushing old events pending a new one, ignore this request.
    اگر (wind->drop_fullscreen_درخواستیں) {
        واپس SDL_FULLSCREEN_SUCCEEDED;
    }

    wind->drop_fullscreen_درخواستیں = true;
    FlushPendingEvents(کھڑکی);
    wind->drop_fullscreen_درخواستیں = false;

    // Nothing to do if the window is not fullscreen, and this isn't an explicit enter request.
    اگر (!wind->is_fullscreen) {
        اگر (fullscreen == SDL_FULLSCREEN_OP_UPDATE) {
            // Request was out of date; signal the video core not to update any state.
            واپس SDL_FULLSCREEN_PENDING;
        } ورنہ اگر (fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
            // Already not fullscreen; nothing to do.
            واپس SDL_FULLSCREEN_SUCCEEDED;
        }
    }

    // Don't send redundant fullscreen set/unset events.
    اگر (!!fullscreen != wind->is_fullscreen) {
        wind->fullscreen_was_positioned = !!fullscreen;

        /* Only use the specified output if an exclusive mode is being used, or a position was explicitly requested
         * before entering fullscreen desktop. Otherwise, let the compositor handle placement, as it has more
         * information about where the window is and where it should go, particularly if fullscreen is being requested
         * before the window is mapped, or the window spans multiple outputs.
         */
        اگر (!کھڑکی->fullscreen_exclusive) {
            اگر (کھڑکی->undefined_x || کھڑکی->undefined_y ||
                (wind->عدد_outputs && !کھڑکی->آخری_position_pending)) {
                output = تہی;
            }
        }

        // Commit to set any pending size or limit data.
        اگر (fullscreen && wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        سیٹ_Fullscreen(کھڑکی, output, !!fullscreen);
    } ورنہ اگر (wind->is_fullscreen) {
        /*
         * If the window is already fullscreen, this is likely a request to switch between
         * fullscreen and fullscreen desktop, change outputs, or change the video mode.
         *
         * If the window is already positioned on the target output, just update the
         * window geometry.
         */
        اگر (wind->آخری_display_ID != display->id) {
            wind->fullscreen_was_positioned = true;
            سیٹ_Fullscreen(کھڑکی, output, true);
        } ورنہ {
            Configure_کھڑکی_Geometry(کھڑکی);
            Commit_Libdecor_چوکھٹا(کھڑکی);

            واپس SDL_FULLSCREEN_SUCCEEDED;
        }
    }

    واپس SDL_FULLSCREEN_PENDING;
}

خالی Wayland_Restore_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *wind = کھڑکی->اندرونی_2;

    // Drop restore requests when showing the window.
    اگر (wind->showing_کھڑکی) {
        واپس;
    }

    // Not currently fullscreen or maximized, and no state pending; nothing to do.
    اگر (!(کھڑکی->flags & (SDL_کھڑکی_FULLSCREEN | SDL_کھڑکی_MAXIMIZED)) &&
        !wind->pending_state_deadline_گنتی) {
        واپس;
    }

#اگر_تعریف_شدہ HAVE_LIBDECOR_H
    اگر (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        اگر (!wind->shell_surface.libdecor.چوکھٹا) {
            واپس; // Can't do anything yet, wait for ShowWindow
        }
        libdecor_چوکھٹا_unset_maximized(wind->shell_surface.libdecor.چوکھٹا);
        جوڑو_Pending_State_Sync(wind);
    } ورنہ
#اگر_ختم
        // Note that xdg-shell does NOT provide a way to unset minimize!
        اگر (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
            اگر (wind->shell_surface.xdg.toplevel.xdg_toplevel == تہی) {
                واپس; // Can't do anything yet, wait for ShowWindow
            }
            xdg_toplevel_unset_maximized(wind->shell_surface.xdg.toplevel.xdg_toplevel);
            جوڑو_Pending_State_Sync(wind);
        }
}

خالی Wayland_سیٹ_کھڑکی_Bordered(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool bordered)
{
    SDL_کھڑکی_ڈیٹا *wind = کھڑکی->اندرونی_2;
    ثابت SDL_Video_ڈیٹا *viddata = (ثابت SDL_Video_ڈیٹا *)_this->اندرونی_2;

#اگر_تعریف_شدہ HAVE_LIBDECOR_H
    اگر (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        اگر (wind->shell_surface.libdecor.چوکھٹا) {
            libdecor_چوکھٹا_سیٹ_visibility(wind->shell_surface.libdecor.چوکھٹا, bordered);
        }
    } ورنہ
#اگر_ختم
        اگر (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        اگر ((viddata->decoration_manager) && (wind->server_decoration)) {
            ثابت شمار zxdg_toplevel_decoration_v1_منوال منوال = bordered ? ZXDG_TOPLEVEL_DECORATION_V1_منوال_SERVER_SIDE : ZXDG_TOPLEVEL_DECORATION_V1_منوال_CLIENT_SIDE;
            zxdg_toplevel_decoration_v1_سیٹ_منوال(wind->server_decoration, منوال);
        }
    }
}

خالی Wayland_سیٹ_کھڑکی_Resizable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool resizable)
{
    SDL_کھڑکی_ڈیٹا *wind = کھڑکی->اندرونی_2;

    /* When changing the resize capability on libdecor windows, the limits must always
     * be reapplied, as when libdecor changes states, it overwrites the values internally.
     */
    سیٹ_Min_Max_Dimensions(کھڑکی);
    Commit_Libdecor_چوکھٹا(کھڑکی);

    اگر (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_SHOWN) {
        wind->pending_state_commit = true;
    }
}

خالی Wayland_Maximize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *wind = کھڑکی->اندرونی_2;

    اگر (wind->show_hide_sync_required) {
        WAYLAND_wl_display_roundtrip(_this->اندرونی_2->display);
    }

    // Not fullscreen, already maximized, and no state pending; nothing to do.
    اگر (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) && (کھڑکی->flags & SDL_کھڑکی_MAXIMIZED) &&
        !wind->pending_state_deadline_گنتی) {
        واپس;
    }

#اگر_تعریف_شدہ HAVE_LIBDECOR_H
    اگر (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        اگر (!wind->shell_surface.libdecor.چوکھٹا) {
            واپس; // Can't do anything yet, wait for ShowWindow
        }

        // Commit to set any pending size or limit data.
        اگر (wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        libdecor_چوکھٹا_سیٹ_maximized(wind->shell_surface.libdecor.چوکھٹا);
        جوڑو_Pending_State_Sync(wind);
    } ورنہ
#اگر_ختم
        اگر (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        اگر (wind->shell_surface.xdg.toplevel.xdg_toplevel == تہی) {
            واپس; // Can't do anything yet, wait for ShowWindow
        }

        // Commit to set any pending size or limit data.
        اگر (wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        xdg_toplevel_سیٹ_maximized(wind->shell_surface.xdg.toplevel.xdg_toplevel);
        جوڑو_Pending_State_Sync(wind);
    }
}

خالی Wayland_Minimize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *wind = کھڑکی->اندرونی_2;

    اگر (!(wind->wm_caps & WAYLAND_WM_CAPS_MINIMIZE)) {
        واپس;
    }

#اگر_تعریف_شدہ HAVE_LIBDECOR_H
    اگر (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        اگر (!wind->shell_surface.libdecor.چوکھٹا) {
            واپس; // Can't do anything yet, wait for ShowWindow
        }
        libdecor_چوکھٹا_سیٹ_minimized(wind->shell_surface.libdecor.چوکھٹا);
        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_MINIMIZED, 0, 0);
    } ورنہ
#اگر_ختم
        اگر (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        اگر (wind->shell_surface.xdg.toplevel.xdg_toplevel == تہی) {
            واپس; // Can't do anything yet, wait for ShowWindow
        }
        xdg_toplevel_سیٹ_minimized(wind->shell_surface.xdg.toplevel.xdg_toplevel);
        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_MINIMIZED, 0, 0);
    }
}

bool Wayland_سیٹ_کھڑکی_Mouse_Rect(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;

    /* This may look suspiciously like SetWindowGrab, despite SetMouseRect not
     * implicitly doing a grab. And you're right! Wayland doesn't let us mess
     * around with mouse focus whatsoever, so it just happens to be that the
     * work that we can do in these two functions ends up being the same.
     *
     * Just know that this call lets you confine with a rect, SetWindowGrab
     * lets you confine without a rect.
     */
    اگر (!ڈیٹا->اشارہ_گر_constraints) {
        واپس SDL_سیٹ_Error("Failed to grab mouse: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }
    Wayland_Display_Update_اشارہ_گر_Grabs(ڈیٹا, کھڑکی->اندرونی_2);
    واپس true;
}

bool Wayland_سیٹ_کھڑکی_Mouse_Grab(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool grabbed)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    اگر (!ڈیٹا->اشارہ_گر_constraints) {
        واپس SDL_سیٹ_Error("Failed to grab mouse: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }
    Wayland_Display_Update_اشارہ_گر_Grabs(ڈیٹا, کھڑکی->اندرونی_2);
    واپس true;
}

bool Wayland_سیٹ_کھڑکی_Keyboard_Grab(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool grabbed)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    اگر (!ڈیٹا->کلید_inhibitor_manager) {
        واپس SDL_سیٹ_Error("Failed to grab keyboard: compositor lacks support for the required zwp_keyboard_shortcuts_inhibit_manager_v1 protocol");
    }
    Wayland_DisplayUpdateKeyboardGrabs(ڈیٹا, کھڑکی->اندرونی_2);
    واپس true;
}

bool Wayland_Reconfigure_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_کھڑکی_Flags flags)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;

    // Don't try to reconfigure mapped windows, unless they are custom or external.
    اگر (ڈیٹا->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_SHOWN &&
        ڈیٹا->shell_surface_type != WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        // Window is already mapped; abort.
        واپس false;
    }

    /* The caller guarantees that only one of the GL or Vulkan flags will be set.
     * Note that Vulkan doesn't require any specific configuration, so only EGL
     * objects are added and removed as required.
     */
    اگر (flags & SDL_کھڑکی_OPENGL) {
        اگر (!ڈیٹا->egl_کھڑکی) {
            ڈیٹا->egl_کھڑکی = WAYLAND_wl_egl_کھڑکی_create(ڈیٹا->surface, ڈیٹا->current.pixel_چوڑائی, ڈیٹا->current.pixel_اونچائی);
        }

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
        ڈیٹا->egl_surface = SDL_EGL_CreateSurface(_this, کھڑکی, (Native_کھڑکی_Type)ڈیٹا->egl_کھڑکی);

        اگر (ڈیٹا->egl_surface == EGL_NO_SURFACE) {
            واپس false; // SDL_EGL_CreateSurface should have set the error.
        }
#اگر_ختم

        اگر (!ڈیٹا->gles_تبادلہ_چوکھٹا_event_قطار) {
            ڈیٹا->gles_تبادلہ_چوکھٹا_event_قطار = WAYLAND_wl_display_create_قطار(ڈیٹا->wayland_ڈیٹا->display);
            ڈیٹا->gles_تبادلہ_چوکھٹا_surface_wrapper = WAYLAND_wl_proxy_create_wrapper(ڈیٹا->surface);
            WAYLAND_wl_proxy_سیٹ_قطار((ساخت wl_proxy *)ڈیٹا->gles_تبادلہ_چوکھٹا_surface_wrapper, ڈیٹا->gles_تبادلہ_چوکھٹا_event_قطار);
            ڈیٹا->gles_تبادلہ_چوکھٹا_callback = wl_surface_چوکھٹا(ڈیٹا->gles_تبادلہ_چوکھٹا_surface_wrapper);
            wl_callback_جوڑو_listener(ڈیٹا->gles_تبادلہ_چوکھٹا_callback, &gles_تبادلہ_چوکھٹا_listener, ڈیٹا);
        }
    } ورنہ {
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
        اگر (ڈیٹا->egl_surface) {
            SDL_EGL_DestroySurface(_this, ڈیٹا->egl_surface);
            ڈیٹا->egl_surface = EGL_NO_SURFACE;
        }
#اگر_ختم

        اگر (ڈیٹا->egl_کھڑکی) {
            WAYLAND_wl_egl_کھڑکی_destroy(ڈیٹا->egl_کھڑکی);
            ڈیٹا->egl_کھڑکی = تہی;
        }

        اگر (ڈیٹا->gles_تبادلہ_چوکھٹا_callback) {
            wl_callback_destroy(ڈیٹا->gles_تبادلہ_چوکھٹا_callback);
            ڈیٹا->gles_تبادلہ_چوکھٹا_callback = تہی;
        }

        اگر (ڈیٹا->gles_تبادلہ_چوکھٹا_surface_wrapper) {
            WAYLAND_wl_proxy_wrapper_destroy(ڈیٹا->gles_تبادلہ_چوکھٹا_surface_wrapper);
            ڈیٹا->gles_تبادلہ_چوکھٹا_surface_wrapper = تہی;
        }

        اگر (ڈیٹا->gles_تبادلہ_چوکھٹا_event_قطار) {
            WAYLAND_wl_event_قطار_destroy(ڈیٹا->gles_تبادلہ_چوکھٹا_event_قطار);
            ڈیٹا->gles_تبادلہ_چوکھٹا_event_قطار = تہی;
        }
    }

    واپس true;
}

bool Wayland_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا;
    SDL_Video_ڈیٹا *c = _this->اندرونی_2;
    ساخت wl_surface *external_surface = (ساخت wl_surface *)SDL_Get_اشارہ_گر_Property(create_props, SDL_PROP_کھڑکی_CREATE_WAYLAND_WL_SURFACE_اشارہ_گر,
                                                                               (ساخت wl_surface *)SDL_Get_اشارہ_گر_Property(create_props, "sdl2-compat.external_window", تہی));
    ثابت bool custom_surface_role = (external_surface != تہی) || SDL_GetBooleanProperty(create_props, SDL_PROP_کھڑکی_CREATE_WAYLAND_SURFACE_ROLE_CUSTOM_BOOLEAN, false);
    ثابت bool create_egl_کھڑکی = !!(کھڑکی->flags & SDL_کھڑکی_OPENGL) ||
                                       SDL_GetBooleanProperty(create_props, SDL_PROP_کھڑکی_CREATE_WAYLAND_CREATE_EGL_کھڑکی_BOOLEAN, false);

    ڈیٹا = SDL_calloc(1, حجم(*ڈیٹا));
    اگر (!ڈیٹا) {
        واپس false;
    }

    کھڑکی->اندرونی_2 = ڈیٹا;
    ڈیٹا->enable_insets = SDL_GetBooleanProperty(create_props, SDL_PROP_کھڑکی_CREATE_WAYLAND_ENABLE_INSETS_BOOLEAN, false);

    اگر (کھڑکی->x == SDL_WINDOWPOS_UNDEFINED) {
        کھڑکی->x = 0;
    }
    اگر (کھڑکی->y == SDL_WINDOWPOS_UNDEFINED) {
        کھڑکی->y = 0;
    }

    ڈیٹا->wayland_ڈیٹا = c;
    ڈیٹا->sdlwindow = کھڑکی;

    // Default to all capabilities
    ڈیٹا->wm_caps = WAYLAND_WM_CAPS_ALL;

    ڈیٹا->scale_ضربی_عدد_2 = 1.0;

    اگر (SDL_کھڑکی_IS_POPUP(کھڑکی)) {
        ڈیٹا->scale_مقصد_display = کھڑکی->والد->اندرونی_2->scale_مقصد_display;
        ڈیٹا->scale_ضربی_عدد_2 = کھڑکی->والد->اندرونی_2->scale_ضربی_عدد_2;
        EnsurePopupPositionIsValid(کھڑکی, &کھڑکی->x, &کھڑکی->y);
    } ورنہ {
        برائے (صحیح i = 0; i < _this->عدد_displays; i++) {
            ڈیٹا->scale_ضربی_عدد_2 = SDL_max(ڈیٹا->scale_ضربی_عدد_2, _this->displays[i]->اندرونی_2->scale_ضربی_عدد_2);
        }
    }

    ڈیٹا->outputs = تہی;
    ڈیٹا->عدد_outputs = 0;
    ڈیٹا->scale_مقصد_display = c->scale_مقصد_display_enabled;

    // Cache the app_id at creation time, as it may change before the window is mapped.
    ڈیٹا->app_id = SDL_strdup(SDL_GetAppID());

    اگر (!ڈیٹا->scale_مقصد_display) {
        ڈیٹا->requested.logical_چوڑائی = کھڑکی->floating.w;
        ڈیٹا->requested.logical_اونچائی = کھڑکی->floating.h;
    } ورنہ {
        ڈیٹا->requested.logical_چوڑائی = Pixel_مقصد_نقطہ(کھڑکی, کھڑکی->floating.w);
        ڈیٹا->requested.logical_اونچائی = Pixel_مقصد_نقطہ(کھڑکی, کھڑکی->floating.h);
        ڈیٹا->requested.pixel_چوڑائی = کھڑکی->floating.w;
        ڈیٹا->requested.pixel_اونچائی = کھڑکی->floating.h;
    }

    اگر (!external_surface) {
        ڈیٹا->surface = wl_compositor_create_surface(c->compositor);
        wl_surface_جوڑو_listener(ڈیٹا->surface, &surface_listener, ڈیٹا);
        wl_surface_سیٹ_user_ڈیٹا(ڈیٹا->surface, ڈیٹا);
        SDL_WAYLAND_رجسٹر_surface(ڈیٹا->surface);
    } ورنہ {
        کھڑکی->flags |= SDL_کھڑکی_EXTERNAL;
        ڈیٹا->surface = external_surface;

        /* External surfaces are registered by being put in a list, as changing tags or userdata
         * can cause problems with external toolkits.
         */
        Wayland_جوڑو_کھڑکی_ڈیٹا_مقصد_External_List(ڈیٹا);
    }

    /* Always attach a viewport and fractional scale manager if available and the surface is not custom/external,
     * or the custom/external surface was explicitly flagged as high pixel density aware, which signals that the
     * application wants SDL to handle scaling.
     */
    اگر (!custom_surface_role || (کھڑکی->flags & SDL_کھڑکی_بلند_PIXEL_DENSITY)) {
        اگر (c->viewporter) {
            ڈیٹا->viewport = wp_viewporter_get_viewport(c->viewporter, ڈیٹا->surface);

            // The viewport always uses the entire buffer.
            wp_viewport_سیٹ_ماخذ(ڈیٹا->viewport,
                                   wl_fixed_from_int(-1), wl_fixed_from_int(-1),
                                   wl_fixed_from_int(-1), wl_fixed_from_int(-1));
        }
        اگر (c->fractional_scale_manager) {
            ڈیٹا->fractional_scale = wp_fractional_scale_manager_v1_get_fractional_scale(c->fractional_scale_manager, ڈیٹا->surface);
            wp_fractional_scale_v1_جوڑو_listener(ڈیٹا->fractional_scale, &fractional_scale_listener, ڈیٹا);
        }
    }

    اگر (!custom_surface_role) {
        اگر (c->wp_color_manager_v1) {
            ڈیٹا->wp_color_management_surface_feedback = wp_color_manager_v1_get_surface_feedback(c->wp_color_manager_v1, ڈیٹا->surface);
            wp_color_management_surface_feedback_v1_جوڑو_listener(ڈیٹا->wp_color_management_surface_feedback, &color_management_surface_feedback_listener, ڈیٹا);
            Wayland_Get_Color_Info_For_کھڑکی(ڈیٹا, true);
        } ورنہ اگر (c->frog_color_management_factory_v1) {
            ڈیٹا->frog_color_managed_surface = frog_color_management_factory_v1_get_color_managed_surface(c->frog_color_management_factory_v1, ڈیٹا->surface);
            frog_color_managed_surface_جوڑو_listener(ڈیٹا->frog_color_managed_surface, &frog_surface_listener, ڈیٹا);
        }

        اگر (c->wp_alpha_modifier_v1) {
            ڈیٹا->wp_alpha_modifier_surface_v1 = wp_alpha_modifier_v1_get_surface(c->wp_alpha_modifier_v1, ڈیٹا->surface);
            wp_alpha_modifier_surface_v1_سیٹ_multiplier(ڈیٹا->wp_alpha_modifier_surface_v1, SDL_MAX_UINT32);
        }
    }

    // Must be called before EGL configuration to set the drawable backbuffer size.
    Configure_کھڑکی_Geometry(کھڑکی);

    /* Fire a callback when the compositor wants a new frame rendered.
     * Right now this only matters for OpenGL; we use this callback to add a
     * wait timeout that avoids getting deadlocked by the compositor when the
     * window isn't visible.
     */
    اگر (کھڑکی->flags & SDL_کھڑکی_OPENGL) {
        ڈیٹا->gles_تبادلہ_چوکھٹا_event_قطار = WAYLAND_wl_display_create_قطار(ڈیٹا->wayland_ڈیٹا->display);
        ڈیٹا->gles_تبادلہ_چوکھٹا_surface_wrapper = WAYLAND_wl_proxy_create_wrapper(ڈیٹا->surface);
        WAYLAND_wl_proxy_سیٹ_قطار((ساخت wl_proxy *)ڈیٹا->gles_تبادلہ_چوکھٹا_surface_wrapper, ڈیٹا->gles_تبادلہ_چوکھٹا_event_قطار);
        ڈیٹا->gles_تبادلہ_چوکھٹا_callback = wl_surface_چوکھٹا(ڈیٹا->gles_تبادلہ_چوکھٹا_surface_wrapper);
        wl_callback_جوڑو_listener(ڈیٹا->gles_تبادلہ_چوکھٹا_callback, &gles_تبادلہ_چوکھٹا_listener, ڈیٹا);
    }

    اگر (کھڑکی->flags & SDL_کھڑکی_TRANSPARENT) {
        اگر (_this->gl_config.alpha_سائز == 0) {
            _this->gl_config.alpha_سائز = 8;
        }
    }

    اگر (create_egl_کھڑکی) {
        ڈیٹا->egl_کھڑکی = WAYLAND_wl_egl_کھڑکی_create(ڈیٹا->surface, ڈیٹا->current.pixel_چوڑائی, ڈیٹا->current.pixel_اونچائی);
    }

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    اگر (کھڑکی->flags & SDL_کھڑکی_OPENGL) {
        // Create the GLES window surface
        ڈیٹا->egl_surface = SDL_EGL_CreateSurface(_this, کھڑکی, (Native_کھڑکی_Type)ڈیٹا->egl_کھڑکی);

        اگر (ڈیٹا->egl_surface == EGL_NO_SURFACE) {
            واپس false; // SDL_EGL_CreateSurface should have set error
        }
    }
#اگر_ختم

    // We may need to create an idle inhibitor for this new window
    Wayland_SuspendScreenSaver(_this);

    اگر (!custom_surface_role) {
#اگر_تعریف_شدہ HAVE_LIBDECOR_H
        اگر (c->shell.libdecor && !SDL_کھڑکی_IS_POPUP(کھڑکی)) {
            ڈیٹا->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR;
        } ورنہ
#اگر_ختم
            اگر (c->shell.xdg) {
            اگر (SDL_کھڑکی_IS_POPUP(کھڑکی)) {
                ڈیٹا->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP;
            } ورنہ {
                ڈیٹا->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL;
            }
        } // All other cases will be WAYLAND_SURFACE_UNKNOWN
    } ورنہ {
        // Roleless and external surfaces are always considered to be in the shown state by the backend.
        ڈیٹا->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_CUSTOM;
        ڈیٹا->shell_surface_حالت = WAYLAND_SHELL_SURFACE_حالت_SHOWN;

        // External windows are presumed to be shown.
        اگر (کھڑکی->flags & SDL_کھڑکی_EXTERNAL) {
            کھڑکی->flags &= ~SDL_کھڑکی_HIDDEN;
        }
    }

    اگر (SDL_GetHintBoolean(SDL_HINT_VIDEO_DOUBLE_بفر, false)) {
        ڈیٹا->double_بفر = true;
    }

    SDL_PropertiesID props = SDL_Get_کھڑکی_Properties(کھڑکی);
    SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WAYLAND_DISPLAY_اشارہ_گر, ڈیٹا->wayland_ڈیٹا->display);
    SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WAYLAND_SURFACE_اشارہ_گر, ڈیٹا->surface);
    SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WAYLAND_VIEWPORT_اشارہ_گر, ڈیٹا->viewport);
    SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WAYLAND_EGL_کھڑکی_اشارہ_گر, ڈیٹا->egl_کھڑکی);
    اگر (ڈیٹا->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL || ڈیٹا->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ثابت حرف *کھڑکی_id = SDL_GetStringProperty(create_props, SDL_PROP_کھڑکی_CREATE_WAYLAND_کھڑکی_ID_STRING, تہی);
        اگر (کھڑکی_id && *کھڑکی_id != '\0') {
            SDL_سیٹ_String_Property(props, SDL_PROP_کھڑکی_WAYLAND_کھڑکی_ID_STRING, کھڑکی_id);
        }
    }

    ڈیٹا->کامیابی_test_نتیجہ = SDL_HITTEST_معمول;

    واپس true;
}

خالی Wayland_سیٹ_کھڑکی_Minimum_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    کھڑکی->اندرونی_2->limits_بدلا = true;
}

خالی Wayland_سیٹ_کھڑکی_زیادہ_سے_زیادہ_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    کھڑکی->اندرونی_2->limits_بدلا = true;
}

خالی Wayland_سیٹ_کھڑکی_Aspect_تناسب(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    کھڑکی->اندرونی_2->limits_بدلا = true;
}

bool Wayland_سیٹ_کھڑکی_Position(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *wind = کھڑکی->اندرونی_2;

    // Only popup windows can be positioned relative to the parent.
    اگر (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        اگر (wind->shell_surface.xdg.popup.xdg_popup &&
            xdg_popup_get_نسخہ(wind->shell_surface.xdg.popup.xdg_popup) < XDG_POPUP_REPOSITION_SINCE_نسخہ) {
            واپس SDL_Unsupported();
        }

        RepositionPopup(کھڑکی, false);
        واپس true;
    } ورنہ اگر (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR || wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        /* Catch up on any pending state before attempting to change the fullscreen window
         * display via a set fullscreen call to make sure the window doesn't have a pending
         * leave fullscreen event that it might override.
         */
        FlushPendingEvents(کھڑکی);

        اگر (wind->is_fullscreen) {
            SDL_VideoDisplay *display = SDL_Get_Video_Display_For_Fullscreen_کھڑکی(کھڑکی);
            اگر (display && wind->آخری_display_ID != display->id) {
                ساخت wl_output *output = display->اندرونی_2->output;
                سیٹ_Fullscreen(کھڑکی, output, true);

                واپس true;
            }
        }
    }
    واپس SDL_سیٹ_Error("wayland cannot position non-popup windows");
}

خالی Wayland_سیٹ_کھڑکی_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *wind = کھڑکی->اندرونی_2;

    /* Flush any pending state operations, as fullscreen windows do not get
     * explicitly resized, not strictly obeying the size of a maximized window
     * is a protocol violation, and pending restore events might result in a
     * configure event overwriting the requested size.
     *
     * Calling this on a custom surface is informative, so the size must
     * always be passed through.
     */
    FlushPendingEvents(کھڑکی);

    ثابت bool maximized = (کھڑکی->flags & SDL_کھڑکی_MAXIMIZED) != 0;
    ثابت bool resizable_state = !(کھڑکی->flags & (SDL_کھڑکی_MAXIMIZED | SDL_کھڑکی_FULLSCREEN));

    /* Maximized and fullscreen windows don't get resized, and the new size is ignored
     * if this is just to recalculate the min/max or aspect limits on a tiled window.
     *
     * Some compositors will mark tiled windows as maximized. In these cases, the content
     * size is recalculated, but window size itself is left alone, as the spec states that
     * the configure size of a maximized window must be obeyed.
     */
    اگر (resizable_state || (کھڑکی->tiled && !wind->limits_بدلا) ||
        wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {

        // Don't change the window size if maximized and tiled.
        اگر (!maximized) {
            اگر (!wind->scale_مقصد_display) {
                wind->requested.logical_چوڑائی = کھڑکی->pending.w;
                wind->requested.logical_اونچائی = کھڑکی->pending.h;
            } ورنہ {
                wind->requested.logical_چوڑائی = Pixel_مقصد_نقطہ(کھڑکی, کھڑکی->pending.w);
                wind->requested.logical_اونچائی = Pixel_مقصد_نقطہ(کھڑکی, کھڑکی->pending.h);
                wind->requested.pixel_چوڑائی = کھڑکی->pending.w;
                wind->requested.pixel_اونچائی = کھڑکی->pending.h;
            }
        }

        /* If a non-resizable window somehow wound up in the tiled state, store the new
         * size in the floating parameters so the size will be preserved for future
         * configure events.
         *
         * This shouldn't happen, but apparently it can on at least one compositor...
         */
        اگر (کھڑکی->tiled && !(کھڑکی->flags & SDL_کھڑکی_RESIZABLE)) {
            کھڑکی->floating.w = کھڑکی->pending.w;
            کھڑکی->floating.h = کھڑکی->pending.h;
        }
    } ورنہ {
        // Can't resize the window.
        کھڑکی->آخری_سائز_pending = false;
    }

    wind->limits_بدلا = false;
    اگر (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_SHOWN) {
        wind->pending_state_commit = true;
    }

    // Always recalculate the geometry, as this may be in response to a min/max limit change.
    Configure_کھڑکی_Geometry(کھڑکی);
    Commit_Libdecor_چوکھٹا(کھڑکی);
}

خالی Wayland_Get_کھڑکی_سائز_اندر_Pixels(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحیح *w, صحیح *h)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;

    *w = ڈیٹا->current.pixel_چوڑائی;
    *h = ڈیٹا->current.pixel_اونچائی;
}

اعشاری Wayland_Get_کھڑکی_Content_Scale(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *wind = کھڑکی->اندرونی_2;

    اگر (کھڑکی->flags & SDL_کھڑکی_بلند_PIXEL_DENSITY || wind->scale_مقصد_display || wind->fullscreen_exclusive) {
        واپس (اعشاری)wind->scale_ضربی_عدد_2;
    }

    واپس 1.0f;
}

SDL_DisplayID Wayland_Get_Display_For_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *wind = کھڑکی->اندرونی_2;

    اگر (wind) {
        واپس wind->آخری_display_ID;
    }

    واپس 0;
}

bool Wayland_سیٹ_کھڑکی_Opacity(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, اعشاری opacity)
{
    SDL_کھڑکی_ڈیٹا *wind = کھڑکی->اندرونی_2;

    اگر (wind->wp_alpha_modifier_surface_v1) {
        ثابت bool is_opaque = !(کھڑکی->flags & SDL_کھڑکی_TRANSPARENT) && opacity == 1.0f;

        اگر (wind->نقاب.mapped && wind->نقاب.opaque != is_opaque) {
            ساخت wl_بفر *old_بفر = wind->نقاب.بفر_2;
            wind->نقاب.opaque = is_opaque;
            wind->نقاب.بفر_2 = Wayland_Create_Single_Pixel_بفر(0, 0, 0, is_opaque ? SDL_MAX_UINT32 : 0);

            wl_surface_attach(wind->نقاب.surface, wind->نقاب.بفر_2, 0, 0);
            اگر (wl_surface_get_نسخہ(wind->نقاب.surface) >= WL_SURFACE_DAMAGE_بفر_SINCE_نسخہ) {
                wl_surface_damage_بفر(wind->نقاب.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
            } ورنہ {
                wl_surface_damage(wind->نقاب.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
            }

            اگر (is_opaque) {
                سیٹ_Surface_Opaque_Region(wind->نقاب.surface, wind->current.logical_چوڑائی, wind->current.logical_اونچائی);
            } ورنہ {
                سیٹ_Surface_Opaque_Region(wind->نقاب.surface, 0, 0);
            }

            wl_surface_commit(wind->نقاب.surface);

            اگر (old_بفر) {
                wl_بفر_destroy(old_بفر);
            }
        }

        اگر (is_opaque) {
            سیٹ_Surface_Opaque_Region(wind->surface, wind->current.viewport_چوڑائی, wind->current.viewport_اونچائی);
        } ورنہ {
            سیٹ_Surface_Opaque_Region(wind->surface, 0, 0);
        }

        wp_alpha_modifier_surface_v1_سیٹ_multiplier(wind->wp_alpha_modifier_surface_v1, (Uint32)((دوہرا)SDL_MAX_UINT32 * (دوہرا)opacity));

        واپس true;
    }

    واپس SDL_سیٹ_Error("wayland: set window opacity failed; compositor lacks support for the required wp_alpha_modifier_v1 protocol");
}

خالی Wayland_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *wind = کھڑکی->اندرونی_2;
    ثابت حرف *title = کھڑکی->title ? کھڑکی->title : "";

#اگر_تعریف_شدہ HAVE_LIBDECOR_H
    اگر (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.چوکھٹا) {
        libdecor_چوکھٹا_سیٹ_title(wind->shell_surface.libdecor.چوکھٹا, title);
    } ورنہ
#اگر_ختم
        اگر (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
        xdg_toplevel_سیٹ_title(wind->shell_surface.xdg.toplevel.xdg_toplevel, title);
    }
}

ساکن صحیح icon_ترتیب_دو_callback(ثابت خالی *a, ثابت خالی *b)
{
    ثابت SDL_Surface *s1 = *(ثابت SDL_Surface **)a;
    ثابت SDL_Surface *s2 = *(ثابت SDL_Surface **)b;

    واپس (s1->w * s1->h) <= (s2->w * s2->h) ? -1 : 1;
}

bool Wayland_سیٹ_کھڑکی_Icon(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_Surface *icon)
{
    SDL_کھڑکی_ڈیٹا *wind = کھڑکی->اندرونی_2;
    Wayland_SHMPool *shm_pool = تہی;
    ساخت xdg_toplevel *toplevel = تہی;

    اگر (!_this->اندرونی_2->xdg_toplevel_icon_manager_v1) {
        واپس SDL_سیٹ_Error("wayland: cannot set icon; required xdg_toplevel_icon_v1 protocol not supported");
    }

    صحیح image_گنتی_2 = 0;
    SDL_Surface **images = SDL_GetSurfaceImages(icon, &image_گنتی_2);
    اگر (!images || !image_گنتی_2) {
        واپس false;
    }

    // Release the old icon resources.
    اگر (wind->xdg_toplevel_icon_v1) {
        xdg_toplevel_icon_v1_destroy(wind->xdg_toplevel_icon_v1);
        wind->xdg_toplevel_icon_v1 = تہی;
    }

    برائے (صحیح i = 0; i < wind->icon_بفر_گنتی; ++i) {
        wl_بفر_destroy(wind->icon_buffers[i]);
    }
    wind->icon_بفر_گنتی = 0;

    wind->xdg_toplevel_icon_v1 = xdg_toplevel_icon_manager_v1_create_icon(_this->اندرونی_2->xdg_toplevel_icon_manager_v1);
    wind->icon_buffers = SDL_realloc(wind->icon_buffers, image_گنتی_2 * حجم(ساخت wl_بفر *));
    اگر (!wind->icon_buffers) {
        جاؤ failure_cleanup;
    }

    // Calculate the size of the buffer pool.
    size_t pool_سائز = 0;
    برائے (صحیح i = 0; i < image_گنتی_2; ++i) {
        // Images must be square. Non-square images will be centered.
        ثابت صحیح سائز = SDL_max(images[i]->w, images[i]->h);
        pool_سائز += سائز * سائز * 4;
    }

    // Sort the images in ascending order by size.
    SDL_qsort(images, image_گنتی_2, حجم(SDL_Surface *), icon_ترتیب_دو_callback);

    shm_pool = Wayland_AllocSHMPool(pool_سائز);
    اگر (!shm_pool) {
        SDL_سیٹ_Error("wayland: failed to allocate an SHM pool for the icon");
        جاؤ failure_cleanup;
    }

    ثابت دوہرا بنیاد_سائز = (دوہرا)SDL_max(icon->w, icon->h);
    برائے (صحیح i = 0; i < image_گنتی_2; ++i) {
        SDL_Surface *surface = images[i];

        // Choose the largest image for each integer scale, ignoring any below the base size.
        ثابت صحیح level_سائز = SDL_max(surface->w, surface->h);
        ثابت صحیح scale = (صحیح)SDL_floor((دوہرا)level_سائز / بنیاد_سائز);
        اگر (!scale) {
            جاری;
        }

        اگر (surface->format != SDL_PIXELFORMAT_ARGB8888) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
            اگر (!surface) {
                SDL_سیٹ_Error("wayland: failed to convert the icon image to ARGB8888 format");
                جاؤ failure_cleanup;
            }
        }

        خالی *بفر_mem;
        ساخت wl_بفر *بفر_2 = Wayland_Alloc_بفر_From_Pool(shm_pool, level_سائز, level_سائز, &بفر_mem);
        اگر (!بفر_2) {
            // Clean up the temporary conversion surface.
            اگر (surface != images[i]) {
                SDL_DestroySurface(surface);
            }
            SDL_سیٹ_Error("wayland: failed to allocate a wl_buffer for the icon");
            جاؤ failure_cleanup;
        }

        wind->icon_buffers[wind->icon_بفر_گنتی++] = بفر_2;

        // Center non-square images.
        اگر (surface->w < level_سائز) {
            SDL_memset(بفر_mem, 0, level_سائز * level_سائز * 4);
            بفر_mem = (Uint8 *)بفر_mem + (((level_سائز - surface->w) / 2) * 4);
        } ورنہ اگر (surface->h < level_سائز) {
            SDL_memset(بفر_mem, 0, level_سائز * level_سائز * 4);
            بفر_mem = (Uint8 *)بفر_mem + (((level_سائز - surface->h) / 2) * (level_سائز * 4));
        }

        SDL_PremultiplyAlpha(surface->w, surface->h, surface->format, surface->pixels, surface->pitch,
                             SDL_PIXELFORMAT_ARGB8888, بفر_mem, level_سائز * 4, true);

        xdg_toplevel_icon_v1_جوڑو_بفر(wind->xdg_toplevel_icon_v1, بفر_2, scale);

        // Clean up the temporary scaled or conversion surface.
        اگر (surface != images[i]) {
            SDL_DestroySurface(surface);
        }
    }

#اگر_تعریف_شدہ HAVE_LIBDECOR_H
    اگر (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.چوکھٹا) {
        toplevel = libdecor_چوکھٹا_get_xdg_toplevel(wind->shell_surface.libdecor.چوکھٹا);
    } ورنہ
#اگر_ختم
        اگر (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
        toplevel = wind->shell_surface.xdg.toplevel.xdg_toplevel;
    }

    اگر (toplevel) {
        xdg_toplevel_icon_manager_v1_سیٹ_icon(_this->اندرونی_2->xdg_toplevel_icon_manager_v1, toplevel, wind->xdg_toplevel_icon_v1);
    }

    Wayland_ReleaseSHMPool(shm_pool);
    SDL_free(images);

    واپس true;

failure_cleanup:

    SDL_free(images);

    اگر (wind->xdg_toplevel_icon_v1) {
        xdg_toplevel_icon_v1_destroy(wind->xdg_toplevel_icon_v1);
        wind->xdg_toplevel_icon_v1 = تہی;
    }

    Wayland_ReleaseSHMPool(shm_pool);

    برائے (صحیح i = 0; i < wind->icon_بفر_گنتی; ++i) {
        wl_بفر_destroy(wind->icon_buffers[i]);
    }
    SDL_free(wind->icon_buffers);
    wind->icon_buffers = تہی;
    wind->icon_بفر_گنتی = 0;

    واپس false;
}

خالی *Wayland_Get_کھڑکی_ICCProfile(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, size_t *سائز)
{
    SDL_کھڑکی_ڈیٹا *wind = کھڑکی->اندرونی_2;
    خالی *ret = تہی;

    اگر (wind->icc_سائز > 0) {
        خالی *icc_map = mmap(تہی, wind->icc_سائز, PROT_READ, MAP_PRIVATE, wind->icc_fd, 0);
        اگر (icc_map != MAP_FAILED) {
            ret = SDL_malloc(wind->icc_سائز);
            اگر (ret) {
                *سائز = wind->icc_سائز;
                SDL_memcpy(ret, icc_map, *سائز);
            }
            munmap(icc_map, wind->icc_سائز);
        }
    }

    واپس ret;
}

bool Wayland_Sync_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *wind = کھڑکی->اندرونی_2;

    کرو {
        WAYLAND_wl_display_roundtrip(_this->اندرونی_2->display);
    } جب (wind->pending_state_deadline_گنتی);

    واپس true;
}

خالی Wayland_AcceptDragAndDrop(SDL_کھڑکی *کھڑکی, bool accept)
{
    کھڑکی->اندرونی_2->قبول_کرتا_drag_and_drop = accept;
}

bool Wayland_سیٹ_کھڑکی_Focusable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool focusable)
{
    اگر (کھڑکی->flags & SDL_کھڑکی_POPUP_MENU) {
        اگر (!(کھڑکی->flags & SDL_کھڑکی_HIDDEN)) {
            اگر (!focusable && (کھڑکی->flags & SDL_کھڑکی_داخلہ_FOCUS)) {
                SDL_کھڑکی *new_focus;
                ثابت bool سیٹ_focus = SDL_ShouldRelinquishPopupFocus(کھڑکی, &new_focus);
                Wayland_سیٹ_Keyboard_Focus(new_focus, سیٹ_focus);
            } ورنہ اگر (focusable) {
                اگر (SDL_ShouldFocusPopup(کھڑکی)) {
                    Wayland_سیٹ_Keyboard_Focus(کھڑکی, true);
                }
            }
        }

        واپس true;
    }

    واپس SDL_سیٹ_Error("wayland: focus can only be toggled on popup menu windows");
}

خالی Wayland_Show_کھڑکی_System_Menu(SDL_کھڑکی *کھڑکی, صحیح x, صحیح y)
{
    SDL_کھڑکی_ڈیٹا *wind = کھڑکی->اندرونی_2;
    SDL_WaylandSeat *seat = wind->wayland_ڈیٹا->آخری_implicit_grab_seat;

    اگر (!seat) {
        واپس;
    }

    اگر (wind->scale_مقصد_display) {
        x = Pixel_مقصد_نقطہ(کھڑکی, x);
        y = Pixel_مقصد_نقطہ(کھڑکی, y);
    }

#اگر_تعریف_شدہ HAVE_LIBDECOR_H
    اگر (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        اگر (wind->shell_surface.libdecor.چوکھٹا) {
            libdecor_چوکھٹا_show_کھڑکی_menu(wind->shell_surface.libdecor.چوکھٹا, seat->wl_seat, seat->آخری_implicit_grab_serial, x, y);
        }
    } ورنہ
#اگر_ختم
    اگر (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        اگر (wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            xdg_toplevel_show_کھڑکی_menu(wind->shell_surface.xdg.toplevel.xdg_toplevel, seat->wl_seat, seat->آخری_implicit_grab_serial, x, y);
        }
    }
}

bool Wayland_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;

#اگر_تعریف_شدہ SDL_USE_LIBDBUS
    اگر (SDL_DBus_ScreensaverInhibit(_this->suspend_screensaver)) {
        واپس true;
    }
#اگر_ختم

    /* The idle_inhibit_unstable_v1 protocol suspends the screensaver
       on a per wl_surface basis, but SDL assumes that suspending
       the screensaver can be done independently of any window.

       To reconcile these differences, we propagate the idle inhibit
       state to each window. If there is no window active, we will
       be able to inhibit idle once the first window is created.
    */
    اگر (ڈیٹا->idle_inhibit_manager) {
        SDL_کھڑکی *کھڑکی = _this->windows;
        جب (کھڑکی) {
            SDL_کھڑکی_ڈیٹا *win_ڈیٹا = کھڑکی->اندرونی_2;

            اگر (_this->suspend_screensaver && !win_ڈیٹا->idle_inhibitor) {
                win_ڈیٹا->idle_inhibitor =
                    zwp_idle_inhibit_manager_v1_create_inhibitor(ڈیٹا->idle_inhibit_manager,
                                                                 win_ڈیٹا->surface);
            } ورنہ اگر (!_this->suspend_screensaver && win_ڈیٹا->idle_inhibitor) {
                zwp_idle_inhibitor_v1_destroy(win_ڈیٹا->idle_inhibitor);
                win_ڈیٹا->idle_inhibitor = تہی;
            }

            کھڑکی = کھڑکی->اگلا;
        }
    }

    واپس true;
}

خالی Wayland_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    SDL_کھڑکی_ڈیٹا *wind = کھڑکی->اندرونی_2;

    اگر (ڈیٹا && wind) {
        /* Roundtrip before destroying the window to make sure that it has received input leave events, so that
         * no internal structures are left pointing to the destroyed window.
         */
        اگر (wind->show_hide_sync_required) {
            /* Make sure hit test isn't executed during roundtrip */
            کھڑکی->کامیابی_test = تہی;
            WAYLAND_wl_display_roundtrip(ڈیٹا->display);
        }

        /* The compositor should have relinquished keyboard, pointer, touch, and tablet tool focus when the toplevel
         * window was destroyed upon being hidden, but there is no guarantee of this, so ensure that all references
         * to the window held by seats are released before destroying the underlying surface and struct.
         */
        Wayland_Display_Remove_کھڑکی_References_From_Seats(ڈیٹا, wind);

        اگر (wind->نقاب.viewport) {
            wp_viewport_destroy(wind->نقاب.viewport);
        }
        اگر (wind->نقاب.بفر_2) {
            wl_بفر_destroy(wind->نقاب.بفر_2);
        }
        اگر (wind->نقاب.subsurface) {
            wl_subsurface_destroy(wind->نقاب.subsurface);
        }
        اگر (wind->نقاب.surface) {
            wl_surface_destroy(wind->نقاب.surface);
        }
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
        اگر (wind->egl_surface) {
            SDL_EGL_DestroySurface(_this, wind->egl_surface);
        }
#اگر_ختم
        اگر (wind->egl_کھڑکی) {
            WAYLAND_wl_egl_کھڑکی_destroy(wind->egl_کھڑکی);
        }

        اگر (wind->idle_inhibitor) {
            zwp_idle_inhibitor_v1_destroy(wind->idle_inhibitor);
        }

        اگر (wind->activation_token) {
            xdg_activation_token_v1_destroy(wind->activation_token);
        }

        اگر (wind->viewport) {
            wp_viewport_destroy(wind->viewport);
        }

        اگر (wind->fractional_scale) {
            wp_fractional_scale_v1_destroy(wind->fractional_scale);
        }

        اگر (wind->wp_alpha_modifier_surface_v1) {
            wp_alpha_modifier_surface_v1_destroy(wind->wp_alpha_modifier_surface_v1);
        }

        اگر (wind->frog_color_managed_surface) {
            frog_color_managed_surface_destroy(wind->frog_color_managed_surface);
        }

        اگر (wind->wp_color_management_surface_feedback) {
            Wayland_FreeColorInfoState(wind->color_info_state);
            wp_color_management_surface_feedback_v1_destroy(wind->wp_color_management_surface_feedback);
        }

        SDL_free(wind->outputs);
        SDL_free(wind->app_id);

        اگر (wind->gles_تبادلہ_چوکھٹا_callback) {
            wl_callback_destroy(wind->gles_تبادلہ_چوکھٹا_callback);
            WAYLAND_wl_proxy_wrapper_destroy(wind->gles_تبادلہ_چوکھٹا_surface_wrapper);
            WAYLAND_wl_event_قطار_destroy(wind->gles_تبادلہ_چوکھٹا_event_قطار);
        }

        اگر (!(کھڑکی->flags & SDL_کھڑکی_EXTERNAL)) {
            wl_surface_destroy(wind->surface);
        } ورنہ {
            Wayland_Remove_کھڑکی_ڈیٹا_From_External_List(wind);
        }

        اگر (wind->xdg_toplevel_icon_v1) {
            xdg_toplevel_icon_v1_destroy(wind->xdg_toplevel_icon_v1);
        }

        برائے (صحیح i = 0; i < wind->icon_بفر_گنتی; ++i) {
            wl_بفر_destroy(wind->icon_buffers[i]);
        }
        SDL_free(wind->icon_buffers);
        wind->icon_بفر_گنتی = 0;

        SDL_free(wind);
    }
    کھڑکی->اندرونی_2 = تہی;
}

#اگر_ختم // SDL_VIDEO_DRIVER_WAYLAND
