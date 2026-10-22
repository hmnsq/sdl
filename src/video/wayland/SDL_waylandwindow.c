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

#ضمن <sys/mman.h>

#ضمن "../SDL_sysvideo.h"
#ضمن "../../events/SDL_events_c.h"
#ضمن "../../core/unix/SDL_appid.h"
#ضمن "../../notification/SDL_notification_c.h"
#ضمن "../SDL_egl_c.h"
#ضمن "SDL_waylandevents_c.h"
#ضمن "SDL_waylandmouse.h"
#ضمن "SDL_waylandwindow.h"
#ضمن "SDL_waylandvideo.h"
#ضمن "../../SDL_hints_c.h"
#ضمن "SDL_waylandcolor.h"

#ضمن "alpha-modifier-v1-client-protocol.h"
#ضمن "xdg-shell-client-protocol.h"
#ضمن "xdg-decoration-unstable-v1-client-protocol.h"
#ضمن "idle-inhibit-unstable-v1-client-protocol.h"
#ضمن "xdg-activation-v1-client-protocol.h"
#ضمن "viewporter-client-protocol.h"
#ضمن "fractional-scale-v1-client-protocol.h"
#ضمن "xdg-foreign-unstable-v2-client-protocol.h"
#ضمن "xdg-dialog-v1-client-protocol.h"
#ضمن "frog-color-management-v1-client-protocol.h"
#ضمن "xdg-toplevel-icon-v1-client-protocol.h"
#ضمن "color-management-v1-client-protocol.h"
#ضمن "xdg-session-management-v1-client-protocol.h"
#ضمن "xdg-toplevel-tag-v1-client-protocol.h"

#جے_تعریف_شدہ HAVE_LIBDECOR_H
#ضمن <libdecor.h>
#جے_انت

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
ساكن bool Should_نقاب_Fullscreen()
{
    ساكن صحيح نقاب_required = -1;

    إذا (نقاب_required >= 0) {
        أرجع نقاب_required != 0;
    }

    ثابت حرف *desktop = SDL_getenv("XDG_CURRENT_DESKTOP");
    إذا (desktop && SDL_strstr(desktop, "KDE") != عدم) {
        نقاب_required = 1;
    } وإلا {
        نقاب_required = 0;
    }

    أرجع نقاب_required != 0;
}

ساكن مزدوج Get_کھڑکی_Scale(SDL_کھڑکی *کھڑکی)
{
    أرجع (کھڑکی->flags & SDL_کھڑکی_بلند_PIXEL_DENSITY) || کھڑکی->اندرونی->scale_منزل_display ? کھڑکی->اندرونی->scale_ضارب_2 : 1.0;
}

// These are point->pixel->point round trip safe; the inverse is not round trip safe due to rounding.
ساكن صحيح نقطہ_منزل_Pixel(SDL_کھڑکی *کھڑکی, صحيح نقطہ)
{
    /* Rounds halfway away from zero as per the Wayland fractional scaling protocol spec.
     * Wayland scale units are in units of 1/120, so the offset is required to correct for
     * rounding errors when using certain scale values.
     */
    أرجع نقطہ ? SDL_max((صحيح)SDL_lround((مزدوج)نقطہ * Get_کھڑکی_Scale(کھڑکی) + 1e-6), 1) : 0;
}

ساكن صحيح Pixel_منزل_نقطہ(SDL_کھڑکی *کھڑکی, صحيح pixel)
{
    أرجع pixel ? SDL_max((صحيح)SDL_lround((مزدوج)pixel / Get_کھڑکی_Scale(کھڑکی)), 1) : 0;
}

تعداد Wayland_منوال_Scale
{
    WAYLAND_منوال_SCALE_UNDEFINED,
    WAYLAND_منوال_SCALE_ASPECT,
    WAYLAND_منوال_SCALE_STRETCH,
    WAYLAND_منوال_SCALE_NONE
};

ساكن تعداد Wayland_منوال_Scale Get_منوال_Scale_طریقہ(فراغ)
{
    ساكن تعداد Wayland_منوال_Scale scale_منوال_2 = WAYLAND_منوال_SCALE_UNDEFINED;

    إذا (scale_منوال_2 == WAYLAND_منوال_SCALE_UNDEFINED) {
        ثابت حرف *scale_hint = SDL_GetHint(SDL_HINT_VIDEO_WAYLAND_منوال_SCALING);

        إذا (scale_hint) {
            إذا (!SDL_strcasecmp(scale_hint, "stretch")) {
                scale_منوال_2 = WAYLAND_منوال_SCALE_STRETCH;
            } وإلا إذا (!SDL_strcasecmp(scale_hint, "none")) {
                scale_منوال_2 = WAYLAND_منوال_SCALE_NONE;
            } وإلا {
                scale_منوال_2 = WAYLAND_منوال_SCALE_ASPECT;
            }
        } وإلا {
            scale_منوال_2 = WAYLAND_منوال_SCALE_ASPECT;
        }
    }

    أرجع scale_منوال_2;
}

تعريفنوع بنية BorderInsets
{
    صحيح بایاں;
    صحيح چوٹی;
    صحيح دایاں;
    صحيح bottom;
} BorderInsets;

// The border insets from the window properties; they only apply to xdg-toplevel windows.
ساكن فراغ GetBorderInsets(SDL_کھڑکی *کھڑکی, BorderInsets *insets)
{
    SDL_zerop(insets);
    إذا (!کھڑکی->اندرونی->enable_insets) {
        أرجع;
    }
    إذا (کھڑکی->اندرونی->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        ثابت SDL_PropertiesID props = SDL_Get_کھڑکی_Properties(کھڑکی);
        insets->بایاں = (صحيح)SDL_clamp(SDL_Get_نمبر_Property(props, SDL_PROP_کھڑکی_WAYLAND_BORDER_INSET_بایاں_نمبر, 0), 0, SDL_MAX_SINT16);
        insets->چوٹی = (صحيح)SDL_clamp(SDL_Get_نمبر_Property(props, SDL_PROP_کھڑکی_WAYLAND_BORDER_INSET_چوٹی_نمبر, 0), 0, SDL_MAX_SINT16);
        insets->دایاں = (صحيح)SDL_clamp(SDL_Get_نمبر_Property(props, SDL_PROP_کھڑکی_WAYLAND_BORDER_INSET_دایاں_نمبر, 0), 0, SDL_MAX_SINT16);
        insets->bottom = (صحيح)SDL_clamp(SDL_Get_نمبر_Property(props, SDL_PROP_کھڑکی_WAYLAND_BORDER_INSET_BOTTOM_نمبر, 0), 0, SDL_MAX_SINT16);
    }
}

ساكن فراغ سیٹ_Min_Max_Dimensions(SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *wind = کھڑکی->اندرونی;
    صحيح min_چوڑائی_2, min_اچائی_2, max_چوڑائی_2, max_اچائی_2;

    /* Keep the limits off while the window is in a fixed-size state, or the controls
     * to exit that state may be disabled.
     */
    إذا (کھڑکی->flags & (SDL_کھڑکی_FULLSCREEN | SDL_کھڑکی_MAXIMIZED)) {
        min_چوڑائی_2 = 0;
        min_اچائی_2 = 0;
        max_چوڑائی_2 = 0;
        max_اچائی_2 = 0;
    } وإلا إذا (کھڑکی->flags & SDL_کھڑکی_RESIZABLE) {
        صحيح adj_w = SDL_max(کھڑکی->min_w, wind->system_limits.min_چوڑائی_2);
        صحيح adj_h = SDL_max(کھڑکی->min_h, wind->system_limits.min_اچائی_2);
        إذا (wind->scale_منزل_display) {
            adj_w = Pixel_منزل_نقطہ(کھڑکی, adj_w);
            adj_h = Pixel_منزل_نقطہ(کھڑکی, adj_h);
        }
        min_چوڑائی_2 = adj_w;
        min_اچائی_2 = adj_h;

        adj_w = کھڑکی->max_w ? SDL_max(کھڑکی->max_w, wind->system_limits.min_چوڑائی_2) : 0;
        adj_h = کھڑکی->max_h ? SDL_max(کھڑکی->max_h, wind->system_limits.min_اچائی_2) : 0;
        إذا (wind->scale_منزل_display) {
            adj_w = Pixel_منزل_نقطہ(کھڑکی, adj_w);
            adj_h = Pixel_منزل_نقطہ(کھڑکی, adj_h);
        }
        max_چوڑائی_2 = adj_w;
        max_اچائی_2 = adj_h;
    } وإلا {
        min_چوڑائی_2 = wind->current.logical_چوڑائی;
        min_اچائی_2 = wind->current.logical_اچائی;
        max_چوڑائی_2 = wind->current.logical_چوڑائی;
        max_اچائی_2 = wind->current.logical_اچائی;
    }

#جے_تعریف_شدہ HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (!wind->shell_surface.libdecor.چوکھٹا) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }

        إذا (min_چوڑائی_2 && min_اچائی_2 && min_چوڑائی_2 == max_چوڑائی_2 && min_اچائی_2 == max_اچائی_2) {
            libdecor_چوکھٹا_unset_capabilities(wind->shell_surface.libdecor.چوکھٹا, LIBDECOR_ACTION_RESIZE);
        } وإلا {
            libdecor_چوکھٹا_سیٹ_capabilities(wind->shell_surface.libdecor.چوکھٹا, LIBDECOR_ACTION_RESIZE);
        }

        /* No need to change these values if the window is non-resizable,
         * as libdecor will just overwrite them internally.
         */
        إذا (libdecor_چوکھٹا_has_capability(wind->shell_surface.libdecor.چوکھٹا, LIBDECOR_ACTION_RESIZE)) {
            libdecor_چوکھٹا_سیٹ_min_content_ناپ(wind->shell_surface.libdecor.چوکھٹا,
                                                min_چوڑائی_2,
                                                min_اچائی_2);
            libdecor_چوکھٹا_سیٹ_max_content_ناپ(wind->shell_surface.libdecor.چوکھٹا,
                                                max_چوڑائی_2,
                                                max_اچائی_2);
        }
    } وإلا
#جے_انت
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        إذا (!wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }
        /* The limits are in window geometry space; keep an existing minimum at 1 or more,
         * or the window can be spuriously closed.
         */
        BorderInsets insets;
        GetBorderInsets(کھڑکی, &insets);
        min_چوڑائی_2 = SDL_max(min_چوڑائی_2 - (insets.بایاں + insets.دایاں), min_چوڑائی_2 ? 1 : 0);
        min_اچائی_2 = SDL_max(min_اچائی_2 - (insets.چوٹی + insets.bottom), min_اچائی_2 ? 1 : 0);
        إذا (max_چوڑائی_2) {
            max_چوڑائی_2 = SDL_max(max_چوڑائی_2 - (insets.بایاں + insets.دایاں), 1);
        }
        إذا (max_اچائی_2) {
            max_اچائی_2 = SDL_max(max_اچائی_2 - (insets.چوٹی + insets.bottom), 1);
        }
        xdg_toplevel_سیٹ_min_ناپ(wind->shell_surface.xdg.toplevel.xdg_toplevel,
                                  min_چوڑائی_2,
                                  min_اچائی_2);
        xdg_toplevel_سیٹ_max_ناپ(wind->shell_surface.xdg.toplevel.xdg_toplevel,
                                  max_چوڑائی_2,
                                  max_اچائی_2);
    }
}

ساكن فراغ EnsurePopupPositionIsValid(SDL_کھڑکی *کھڑکی, صحيح *x, صحيح *y)
{
    صحيح adj_گنتی = 0;

    /* Per the xdg-positioner spec, child popup windows must intersect or at
     * least be partially adjoining the parent window.
     *
     * Failure to ensure this on a compositor that enforces this restriction
     * can result in behavior ranging from the window being spuriously closed
     * to a protocol violation.
     */
    إذا (*x + کھڑکی->w <= 0) {
        *x = -کھڑکی->w;
        ++adj_گنتی;
    }
    إذا (*y + کھڑکی->h <= 0) {
        *y = -کھڑکی->h;
        ++adj_گنتی;
    }
    إذا (*x >= کھڑکی->ماپا->w) {
        *x = کھڑکی->ماپا->w;
        ++adj_گنتی;
    }
    إذا (*y >= کھڑکی->ماپا->h) {
        *y = کھڑکی->ماپا->h;
        ++adj_گنتی;
    }

    /* If adjustment was required on the x and y axes, the popup is aligned with
     * the parent corner-to-corner and is neither overlapping nor adjoining, so it
     * must be nudged by 1 to be considered adjoining.
     */
    إذا (adj_گنتی > 1) {
        *x += *x < 0 ? 1 : -1;
    }
}

// The window geometry: the explicitly set one, or the full surface if SDL has never set it.
ساكن فراغ Get_کھڑکی_Geometry(SDL_کھڑکی_انکڑے *wind, SDL_Rect *geometry)
{
    *geometry = wind->explicit_geometry;
    إذا (SDL_Rect_خالی_تھاواں(geometry)) {
        geometry->x = 0;
        geometry->y = 0;
        geometry->w = wind->current.logical_چوڑائی;
        geometry->h = wind->current.logical_اچائی;
    }
}

ساكن فراغ Adjust_Popup_وتھ(SDL_کھڑکی *popup, صحيح *x, صحيح *y)
{
    // Positioner offsets are relative to the origin of the parent's window geometry.
#جے_تعریف_شدہ HAVE_LIBDECOR_H
    إذا (popup->ماپا->اندرونی->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        صحيح adj_x, adj_y;
        libdecor_چوکھٹا_translate_coordinate(popup->ماپا->اندرونی->shell_surface.libdecor.چوکھٹا,
                                            *x, *y, &adj_x, &adj_y);
        *x = adj_x;
        *y = adj_y;
    } وإلا
#جے_انت
    {
        *x -= popup->ماپا->اندرونی->explicit_geometry.x;
        *y -= popup->ماپا->اندرونی->explicit_geometry.y;
    }
}

ساكن فراغ RepositionPopup(SDL_کھڑکی *کھڑکی, bool use_current_position)
{
    SDL_کھڑکی_انکڑے *wind = کھڑکی->اندرونی;

    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP &&
        wind->shell_surface.xdg.popup.xdg_positioner &&
        xdg_popup_get_نسخہ(wind->shell_surface.xdg.popup.xdg_popup) >= XDG_POPUP_REPOSITION_SINCE_نسخہ) {
        صحيح x = use_current_position ? کھڑکی->x : کھڑکی->pending.x;
        صحيح y = use_current_position ? کھڑکی->y : کھڑکی->pending.y;

        EnsurePopupPositionIsValid(کھڑکی, &x, &y);
        إذا (wind->scale_منزل_display) {
            x = Pixel_منزل_نقطہ(کھڑکی->ماپا, x);
            y = Pixel_منزل_نقطہ(کھڑکی->ماپا, y);
        }
        Adjust_Popup_وتھ(کھڑکی, &x, &y);
        SDL_Rect ماپا_geometry;
        Get_کھڑکی_Geometry(کھڑکی->ماپا->اندرونی, &ماپا_geometry);
        xdg_positioner_سیٹ_anchor_rect(wind->shell_surface.xdg.popup.xdg_positioner, 0, 0, ماپا_geometry.w, ماپا_geometry.h);
        xdg_positioner_سیٹ_ناپ(wind->shell_surface.xdg.popup.xdg_positioner, wind->current.logical_چوڑائی, wind->current.logical_اچائی);
        xdg_positioner_سیٹ_وتھ(wind->shell_surface.xdg.popup.xdg_positioner, x, y);
        xdg_popup_reposition(wind->shell_surface.xdg.popup.xdg_popup,
                             wind->shell_surface.xdg.popup.xdg_positioner,
                             0);
    }
}

ساكن فراغ سیٹ_Surface_Opaque_Region(بنية wl_surface *surface, صحيح چوڑائی, صحيح اچائی)
{
    SDL_Video_انکڑے *viddata = SDL_GetVideoDevice()->اندرونی;

    إذا (چوڑائی && اچائی) {
        بنية wl_region *region = wl_compositor_create_region(viddata->compositor);
        wl_region_جوڑو(region, 0, 0, چوڑائی, اچائی);
        wl_surface_سیٹ_opaque_region(surface, region);
        wl_region_destroy(region);
    } وإلا {
        wl_surface_سیٹ_opaque_region(surface, عدم);
    }
}

ساكن فراغ Configure_کھڑکی_Geometry(SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    ثابت مزدوج scale_ضارب_2 = Get_کھڑکی_Scale(کھڑکی);
    ثابت مزدوج prev_اشارہ_گر_scale_x = انکڑے->اشارہ_گر_scale.x;
    ثابت مزدوج prev_اشارہ_گر_scale_y = انکڑے->اشارہ_گر_scale.y;
    ثابت صحيح old_pixel_چوڑائی = انکڑے->current.pixel_چوڑائی;
    ثابت صحيح old_pixel_اچائی = انکڑے->current.pixel_اچائی;
    صحيح کھڑکی_چوڑائی = 0;
    صحيح کھڑکی_اچائی = 0;
    صحيح viewport_چوڑائی, viewport_اچائی;
    bool کھڑکی_ناپ_بدلیا;
    bool بفر_ناپ_بدلیا;
    ثابت bool is_opaque = !(کھڑکی->flags & SDL_کھڑکی_TRANSPARENT) && کھڑکی->opacity == 1.0f;

    إذا (انکڑے->is_fullscreen && کھڑکی->fullscreen_exclusive) {
        کھڑکی_چوڑائی = کھڑکی->current_fullscreen_منوال.w;
        کھڑکی_اچائی = کھڑکی->current_fullscreen_منوال.h;

        viewport_چوڑائی = انکڑے->requested.logical_چوڑائی;
        viewport_اچائی = انکڑے->requested.logical_اچائی;

        بدل (Get_منوال_Scale_طریقہ()) {
        حالة WAYLAND_منوال_SCALE_NONE:
            /* The Wayland spec states that the advertised fullscreen dimensions are a maximum.
             * Windows can request a smaller size, but exceeding these dimensions is a protocol violation,
             * thus, modes that exceed the output size still need to be scaled with a viewport.
             */
            إذا (کھڑکی_چوڑائی <= viewport_چوڑائی && کھڑکی_اچائی <= viewport_اچائی) {
                viewport_چوڑائی = کھڑکی_چوڑائی;
                viewport_اچائی = کھڑکی_اچائی;

                اكسر;
            }
            SDL_FALLTHROUGH;
        حالة WAYLAND_منوال_SCALE_ASPECT:
        {
            ثابت عائم output_تناسب = (عائم)viewport_چوڑائی / (عائم)viewport_اچائی;
            ثابت عائم منوال_تناسب = (عائم)کھڑکی_چوڑائی / (عائم)کھڑکی_اچائی;

            إذا (output_تناسب > منوال_تناسب) {
                viewport_چوڑائی = SDL_lroundf((عائم)کھڑکی_چوڑائی * ((عائم)viewport_اچائی / (عائم)کھڑکی_اچائی));
            } وإلا إذا (output_تناسب < منوال_تناسب) {
                viewport_اچائی = SDL_lroundf((عائم)کھڑکی_اچائی * ((عائم)viewport_چوڑائی / (عائم)کھڑکی_چوڑائی));
            }
        } اكسر;
        افتراضي:
            اكسر;
        }

        کھڑکی_ناپ_بدلیا = کھڑکی_چوڑائی != کھڑکی->w ||
                              کھڑکی_اچائی != کھڑکی->h ||
                              انکڑے->current.viewport_چوڑائی != viewport_چوڑائی ||
                              انکڑے->current.viewport_اچائی != viewport_اچائی;

        // Exclusive fullscreen window sizes are always in pixel units.
        انکڑے->current.pixel_چوڑائی = کھڑکی_چوڑائی;
        انکڑے->current.pixel_اچائی = کھڑکی_اچائی;
        بفر_ناپ_بدلیا = انکڑے->current.pixel_چوڑائی != old_pixel_چوڑائی ||
                              انکڑے->current.pixel_اچائی != old_pixel_اچائی;

        إذا (کھڑکی_ناپ_بدلیا || بفر_ناپ_بدلیا) {
            إذا (انکڑے->viewport) {
                wp_viewport_سیٹ_destination(انکڑے->viewport, viewport_چوڑائی, viewport_اچائی);

                انکڑے->current.logical_چوڑائی = انکڑے->requested.logical_چوڑائی;
                انکڑے->current.logical_اچائی = انکڑے->requested.logical_اچائی;
                انکڑے->current.viewport_چوڑائی = viewport_چوڑائی;
                انکڑے->current.viewport_اچائی = viewport_اچائی;
            } وإلا {
                // Calculate the integer scale from the mode and output.
                ثابت int32_t int_scale = SDL_max(کھڑکی->current_fullscreen_منوال.w / viewport_چوڑائی, 1);

                wl_surface_سیٹ_بفر_scale(انکڑے->surface, int_scale);
                انکڑے->current.logical_چوڑائی = کھڑکی->current_fullscreen_منوال.w;
                انکڑے->current.logical_اچائی = کھڑکی->current_fullscreen_منوال.h;
            }

            انکڑے->اشارہ_گر_scale.x = (مزدوج)کھڑکی_چوڑائی / (مزدوج)viewport_چوڑائی;
            انکڑے->اشارہ_گر_scale.y = (مزدوج)کھڑکی_اچائی / (مزدوج)viewport_اچائی;
        }
    } وإلا {
        إذا (!انکڑے->scale_منزل_display) {
            viewport_چوڑائی = انکڑے->requested.logical_چوڑائی;
            viewport_اچائی = انکڑے->requested.logical_اچائی;
        } وإلا {
            viewport_چوڑائی = انکڑے->requested.pixel_چوڑائی;
            viewport_اچائی = انکڑے->requested.pixel_اچائی;
        }

        إذا (!انکڑے->enable_insets &&
            انکڑے->shell_surface_حالت != WAYLAND_SHELL_SURFACE_حالت_HIDDEN &&
            انکڑے->viewport && انکڑے->wayland_انکڑے->subcompositor && !انکڑے->floating && !انکڑے->is_fullscreen) {
            صحيح min_چوڑائی_2, min_اچائی_2, max_چوڑائی_2, max_اچائی_2;
            إذا (کھڑکی->flags & SDL_کھڑکی_RESIZABLE) {
                min_چوڑائی_2 = کھڑکی->min_w;
                min_اچائی_2 = کھڑکی->min_h;
                max_چوڑائی_2 = کھڑکی->max_w;
                max_اچائی_2 = کھڑکی->max_h;
            } وإلا {
                // Use the fixed size in the odd case where a non-resizable window somehow wound up tiled or maximized.
                min_چوڑائی_2 = کھڑکی->floating.w;
                min_اچائی_2 = کھڑکی->floating.h;
                max_چوڑائی_2 = کھڑکی->floating.w;
                max_اچائی_2 = کھڑکی->floating.h;
            }

            إذا (min_چوڑائی_2) {
                viewport_چوڑائی = SDL_max(viewport_چوڑائی, min_چوڑائی_2);
            }
            إذا (min_اچائی_2) {
                viewport_اچائی = SDL_max(viewport_اچائی, min_اچائی_2);
            }
            إذا (max_چوڑائی_2) {
                viewport_چوڑائی = SDL_min(viewport_چوڑائی, max_چوڑائی_2);
            }
            إذا (max_اچائی_2) {
                viewport_اچائی = SDL_min(viewport_اچائی, max_اچائی_2);
            }

            عائم aspect = (عائم)viewport_چوڑائی / (عائم)viewport_اچائی;
            إذا (کھڑکی->min_aspect != 0.f && aspect < کھڑکی->min_aspect) {
                viewport_اچائی = SDL_max(SDL_lroundf((عائم)viewport_چوڑائی / کھڑکی->min_aspect), 1);
            } وإلا إذا (کھڑکی->max_aspect != 0.f && aspect > کھڑکی->max_aspect) {
                viewport_چوڑائی = SDL_max(SDL_lroundf((عائم)viewport_اچائی * کھڑکی->max_aspect), 1);
            }

            // At this point, the viewport matches the virtual window dimensions, but the viewport might be clamped to the output window dimensions beyond here.
            کھڑکی_چوڑائی = viewport_چوڑائی;
            کھڑکی_اچائی = viewport_اچائی;

            // If the viewport bounds exceed the window size, scale them while maintaining the aspect ratio.
            إذا (!انکڑے->scale_منزل_display) {
                إذا (viewport_چوڑائی > انکڑے->requested.logical_چوڑائی || viewport_اچائی > انکڑے->requested.logical_اچائی) {
                    aspect = (عائم)viewport_چوڑائی / (عائم)viewport_اچائی;
                    ثابت عائم کھڑکی_تناسب = (عائم)انکڑے->requested.logical_چوڑائی / (عائم)انکڑے->requested.logical_اچائی;
                    إذا (aspect >= کھڑکی_تناسب) {
                        viewport_چوڑائی = انکڑے->requested.logical_چوڑائی;
                        viewport_اچائی = SDL_lroundf((عائم)viewport_چوڑائی / aspect);
                    } وإلا إذا (aspect < کھڑکی_تناسب) {
                        viewport_اچائی = انکڑے->requested.logical_اچائی;
                        viewport_چوڑائی = SDL_lroundf((عائم)viewport_اچائی * aspect);
                    }
                }
            } وإلا {
                إذا (viewport_چوڑائی > انکڑے->requested.pixel_چوڑائی || viewport_اچائی > انکڑے->requested.pixel_اچائی) {
                    aspect = (عائم)viewport_چوڑائی / (عائم)viewport_اچائی;
                    ثابت عائم کھڑکی_تناسب = (عائم)انکڑے->requested.pixel_چوڑائی / (عائم)انکڑے->requested.pixel_اچائی;
                    إذا (aspect >= کھڑکی_تناسب) {
                        viewport_چوڑائی = انکڑے->requested.pixel_چوڑائی;
                        viewport_اچائی = SDL_lroundf((عائم)viewport_چوڑائی / aspect);
                    } وإلا إذا (aspect < کھڑکی_تناسب) {
                        viewport_اچائی = انکڑے->requested.pixel_اچائی;
                        viewport_چوڑائی = SDL_lroundf((عائم)viewport_اچائی * aspect);
                    }
                }
            }

            viewport_چوڑائی = SDL_max(viewport_چوڑائی, 1);
            viewport_اچائی = SDL_max(viewport_اچائی, 1);
        } وإلا {
            کھڑکی_چوڑائی = viewport_چوڑائی;
            کھڑکی_اچائی = viewport_اچائی;
        }

        إذا (!انکڑے->scale_منزل_display) {
            انکڑے->current.pixel_چوڑائی = نقطہ_منزل_Pixel(کھڑکی, کھڑکی_چوڑائی);
            انکڑے->current.pixel_اچائی = نقطہ_منزل_Pixel(کھڑکی, کھڑکی_اچائی);
        } وإلا {
            // The viewport size is in pixels at this point; convert it to logical units.
            انکڑے->current.pixel_چوڑائی = کھڑکی_چوڑائی;
            انکڑے->current.pixel_اچائی = کھڑکی_اچائی;
            viewport_چوڑائی = Pixel_منزل_نقطہ(کھڑکی, viewport_چوڑائی);
            viewport_اچائی = Pixel_منزل_نقطہ(کھڑکی, viewport_اچائی);
        }

        // Clamp the physical window size to the system minimum required size.
        انکڑے->requested.logical_چوڑائی = SDL_max(انکڑے->requested.logical_چوڑائی, انکڑے->system_limits.min_چوڑائی_2);
        انکڑے->requested.logical_اچائی = SDL_max(انکڑے->requested.logical_اچائی, انکڑے->system_limits.min_اچائی_2);

        کھڑکی_ناپ_بدلیا = انکڑے->requested.logical_چوڑائی != انکڑے->current.logical_چوڑائی ||
                              انکڑے->requested.logical_اچائی != انکڑے->current.logical_اچائی ||
                              viewport_چوڑائی != انکڑے->current.viewport_چوڑائی ||
                              viewport_اچائی != انکڑے->current.viewport_اچائی;

        بفر_ناپ_بدلیا = انکڑے->current.pixel_چوڑائی != old_pixel_چوڑائی ||
                              انکڑے->current.pixel_اچائی != old_pixel_اچائی;

        إذا (کھڑکی_ناپ_بدلیا || بفر_ناپ_بدلیا) {
            إذا (انکڑے->viewport) {
                wp_viewport_سیٹ_destination(انکڑے->viewport, viewport_چوڑائی, viewport_اچائی);
            } وإلا إذا (کھڑکی->flags & SDL_کھڑکی_بلند_PIXEL_DENSITY) {
                // Don't change this if the DPI awareness flag is unset, as an application may have set this manually on a custom or external surface.
                wl_surface_سیٹ_بفر_scale(انکڑے->surface, (int32_t)scale_ضارب_2);
            }

            انکڑے->current.logical_چوڑائی = انکڑے->requested.logical_چوڑائی;
            انکڑے->current.logical_اچائی = انکڑے->requested.logical_اچائی;
            انکڑے->current.viewport_چوڑائی = viewport_چوڑائی;
            انکڑے->current.viewport_اچائی = viewport_اچائی;

            انکڑے->اشارہ_گر_scale.x = (مزدوج)کھڑکی_چوڑائی / (مزدوج)viewport_چوڑائی;
            انکڑے->اشارہ_گر_scale.y = (مزدوج)کھڑکی_اچائی / (مزدوج)viewport_اچائی;
        }
    }

    إذا (انکڑے->egl_کھڑکی && بفر_ناپ_بدلیا) {
        WAYLAND_wl_egl_کھڑکی_resize(انکڑے->egl_کھڑکی,
                                     انکڑے->current.pixel_چوڑائی,
                                     انکڑے->current.pixel_اچائی,
                                     0, 0);
    }

    /* Calculate the mask size and offset.
     * Fullscreen windows are centered and masked automatically by the compositor, unless it lacks the capability.
     */
    إذا (!انکڑے->enable_insets && انکڑے->viewport && انکڑے->wayland_انکڑے->subcompositor && (!انکڑے->is_fullscreen || Should_نقاب_Fullscreen()) &&
        (viewport_چوڑائی != انکڑے->current.logical_چوڑائی || viewport_اچائی != انکڑے->current.logical_اچائی)) {
        بنية wl_بفر *old_بفر = عدم;

        إذا (!انکڑے->نقاب.surface) {
            انکڑے->نقاب.surface = wl_compositor_create_surface(انکڑے->wayland_انکڑے->compositor);
            SDL_WAYLAND_رجسٹر_surface(انکڑے->نقاب.surface);
            wl_surface_سیٹ_user_انکڑے(انکڑے->نقاب.surface, انکڑے);
        }
        إذا (!انکڑے->نقاب.subsurface) {
            انکڑے->نقاب.subsurface = wl_subcompositor_get_subsurface(انکڑے->wayland_انکڑے->subcompositor, انکڑے->نقاب.surface, انکڑے->surface);
        }
        إذا (!انکڑے->نقاب.viewport) {
            انکڑے->نقاب.viewport = wp_viewporter_get_viewport(انکڑے->wayland_انکڑے->viewporter, انکڑے->نقاب.surface);
        }
        إذا (!انکڑے->نقاب.بفر_2 || انکڑے->نقاب.opaque != is_opaque) {
            old_بفر = انکڑے->نقاب.بفر_2;
            انکڑے->نقاب.opaque = is_opaque;
            انکڑے->نقاب.بفر_2 = Wayland_Create_Single_Pixel_بفر(0, 0, 0, is_opaque ? SDL_MAX_UINT32 : 0);
        }

        wl_surface_attach(انکڑے->نقاب.surface, انکڑے->نقاب.بفر_2, 0, 0);

        wl_subsurface_رکھو_ہیٹھاں(انکڑے->نقاب.subsurface, انکڑے->surface);
        wp_viewport_سیٹ_destination(انکڑے->نقاب.viewport, انکڑے->current.logical_چوڑائی, انکڑے->current.logical_اچائی);

        إذا (wl_surface_get_نسخہ(انکڑے->نقاب.surface) >= WL_SURFACE_DAMAGE_بفر_SINCE_نسخہ) {
            wl_surface_damage_بفر(انکڑے->نقاب.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        } وإلا {
            wl_surface_damage(انکڑے->نقاب.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        }

        إذا (is_opaque) {
            سیٹ_Surface_Opaque_Region(انکڑے->نقاب.surface, انکڑے->current.logical_چوڑائی, انکڑے->current.logical_اچائی);
        } وإلا {
            سیٹ_Surface_Opaque_Region(انکڑے->نقاب.surface, 0, 0);
        }

        // Can't use an offset subsurface with libdecor (yet), or the decorations won't line up properly.
        إذا (انکڑے->shell_surface_type != WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
            انکڑے->نقاب.وتھ_x = -(انکڑے->current.logical_چوڑائی - viewport_چوڑائی) / 2;
            انکڑے->نقاب.وتھ_y = -(انکڑے->current.logical_اچائی - viewport_اچائی) / 2;
        } وإلا {
            انکڑے->نقاب.وتھ_x = 0;
            انکڑے->نقاب.وتھ_y = 0;
        }

        wl_subsurface_سیٹ_position(انکڑے->نقاب.subsurface, انکڑے->نقاب.وتھ_x, انکڑے->نقاب.وتھ_y);
        wl_surface_commit(انکڑے->نقاب.surface);

        إذا (old_بفر) {
            wl_بفر_destroy(old_بفر);
        }

        انکڑے->نقاب.mapped = true;
    } وإلا إذا (انکڑے->نقاب.mapped) {
        wl_subsurface_سیٹ_position(انکڑے->نقاب.subsurface, 0, 0);
        wl_surface_attach(انکڑے->نقاب.surface, عدم, 0, 0);
        wl_surface_commit(انکڑے->نقاب.surface);

        انکڑے->نقاب.وتھ_x = 0;
        انکڑے->نقاب.وتھ_y = 0;
        انکڑے->نقاب.mapped = false;
    }

    إذا (انکڑے->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && انکڑے->shell_surface.xdg.surface &&
        (انکڑے->enable_insets || !انکڑے->viewport)) {
        /* The window geometry is the surface minus the declared border insets. They don't apply
         * when an exact size is required (maximized/fullscreen).
         */
        BorderInsets insets;
        GetBorderInsets(کھڑکی, &insets);
        ثابت bool use_insets = (insets.بایاں || insets.چوٹی || insets.دایاں || insets.bottom) &&
                                !(کھڑکی->flags & (SDL_کھڑکی_MAXIMIZED | SDL_کھڑکی_FULLSCREEN));
        SDL_Rect geometry = { 0, 0, انکڑے->current.logical_چوڑائی, انکڑے->current.logical_اچائی };
        إذا (use_insets) {
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
        إذا ((use_insets || !SDL_Rect_خالی_تھاواں(&انکڑے->explicit_geometry) || (!انکڑے->viewport && کھڑکی_ناپ_بدلیا)) &&
            !SDL_RectsEqual(&geometry, &انکڑے->explicit_geometry)) {
            xdg_surface_سیٹ_کھڑکی_geometry(انکڑے->shell_surface.xdg.surface, geometry.x, geometry.y, geometry.w, geometry.h);
            انکڑے->explicit_geometry = geometry;
        }
    }

    /* The opaque region and pointer confinement region only need to be
     * recalculated if the output size has changed.
     */
    إذا (کھڑکی_ناپ_بدلیا) {
        إذا (is_opaque) {
            سیٹ_Surface_Opaque_Region(انکڑے->surface, viewport_چوڑائی, viewport_اچائی);
        } وإلا {
            سیٹ_Surface_Opaque_Region(انکڑے->surface, 0, 0);
        }

        // Ensure that child popup windows are still in bounds.
        لكل (SDL_کھڑکی *بچہ = کھڑکی->پہلا_بچہ; بچہ; بچہ = بچہ->اگلا_sibling) {
            RepositionPopup(بچہ, true);
        }
    }

    // Update the scale for any focused cursors.
    إذا (prev_اشارہ_گر_scale_x != انکڑے->اشارہ_گر_scale.x || prev_اشارہ_گر_scale_y != انکڑے->اشارہ_گر_scale.y) {
        Wayland_Display_Update_اشارہ_گر_Focused_Scale(انکڑے);
    }

    /* Update the min/max dimensions, primarily if the state was changed, and for non-resizable
     * xdg-toplevel windows where the limits should match the window size.
     */
    سیٹ_Min_Max_Dimensions(کھڑکی);

    // Unconditionally send the window and drawable size, the video core will deduplicate when required.
    إذا (!انکڑے->scale_منزل_display) {
        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESIZED, کھڑکی_چوڑائی, کھڑکی_اچائی);
    } وإلا {
        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESIZED, انکڑے->current.pixel_چوڑائی, انکڑے->current.pixel_اچائی);
    }
    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_PIXEL_ناپ_بدلیا, انکڑے->current.pixel_چوڑائی, انکڑے->current.pixel_اچائی);

    /* Send an exposure event if the window is in the shown state and the size has changed,
     * even if the window is occluded, as the client needs to commit a new frame for the
     * changes to take effect.
     *
     * The occlusion state is immediately set again afterward, if necessary.
     */
    إذا (انکڑے->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_SHOWN) {
        إذا ((بفر_ناپ_بدلیا || کھڑکی_ناپ_بدلیا) ||
            (!انکڑے->suspended && (کھڑکی->flags & SDL_کھڑکی_OCCLUDED))) {
            SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_EXPOSED, 0, 0);
        }

        إذا (انکڑے->suspended) {
            SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_OCCLUDED, 0, 0);
        }
    }
}

ساكن فراغ Commit_Libdecor_چوکھٹا(SDL_کھڑکی *کھڑکی)
{
#جے_تعریف_شدہ HAVE_LIBDECOR_H
    SDL_کھڑکی_انکڑے *wind = کھڑکی->اندرونی;

    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.چوکھٹا) {
        بنية libdecor_state *state = libdecor_state_new(wind->current.logical_چوڑائی, wind->current.logical_اچائی);
        libdecor_چوکھٹا_commit(wind->shell_surface.libdecor.چوکھٹا, state, عدم);
        libdecor_state_free(state);
    }
#جے_انت
}

ساكن فراغ pending_state_deadline_handler(فراغ *انکڑے, بنية wl_callback *callback, uint32_t callback_انکڑے)
{
    // Get the window from the ID, as it may have been destroyed.
    SDL_کھڑکی_ID کھڑکی_ID = (SDL_کھڑکی_ID)(uintptr_t)انکڑے;
    SDL_کھڑکی *کھڑکی = SDL_Get_کھڑکی_From_ID(کھڑکی_ID);

    إذا (کھڑکی && کھڑکی->اندرونی) {
        --کھڑکی->اندرونی->pending_state_deadline_گنتی;
    }

    wl_callback_destroy(callback);
}

ساكن بنية wl_callback_listener pending_state_deadline_listener = {
    pending_state_deadline_handler
};

ساكن فراغ جوڑو_Pending_State_Sync(SDL_کھڑکی_انکڑے *کھڑکی_انکڑے_2)
{
    SDL_Video_انکڑے *video_انکڑے = کھڑکی_انکڑے_2->wayland_انکڑے;
    فراغ *cb_انکڑے = (فراغ *)(uintptr_t)کھڑکی_انکڑے_2->sdlwindow->id;

    ++کھڑکی_انکڑے_2->pending_state_deadline_گنتی;
    بنية wl_callback *cb = wl_display_sync(video_انکڑے->display);
    wl_callback_جوڑو_listener(cb, &pending_state_deadline_listener, cb_انکڑے);
}

ساكن فراغ FlushPendingEvents(SDL_کھڑکی *کھڑکی)
{
    // Serialize and restore the pending flags, as they may be overwritten while flushing.
    ثابت bool آخری_position_pending = کھڑکی->آخری_position_pending;
    ثابت bool آخری_ناپ_pending = کھڑکی->آخری_ناپ_pending;

    طالما (کھڑکی->اندرونی->pending_state_deadline_گنتی) {
        WAYLAND_wl_display_roundtrip(کھڑکی->اندرونی->wayland_انکڑے->display);
    }

    کھڑکی->آخری_position_pending = آخری_position_pending;
    کھڑکی->آخری_ناپ_pending = آخری_ناپ_pending;
}

/* While we can't get window position from the compositor, we do at least know
 * what monitor we're on, so let's send move events that put the window at the
 * center of the whatever display the wl_surface_listener events give us.
 */
فراغ Wayland_Update_کھڑکی_Position(SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *wind = کھڑکی->اندرونی;
    SDL_Display_انکڑے *display;

    إذا (wind->outputs && wind->عدد_outputs) {
        display = wind->outputs[wind->عدد_outputs - 1];
    } وإلا {
        // A window may not be on any displays if minimized.
        أرجع;
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
    إذا (wind->shell_surface_type != WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        إذا (!wind->wayland_انکڑے->scale_منزل_display_enabled) {
            SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_MOVED, display->logical.x, display->logical.y);
        } وإلا {
            SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_MOVED, display->pixel.x, display->pixel.y);
        }
        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_DISPLAY_بدلیا, wind->آخری_display_ID, 0);
    }
}

ساكن فراغ سیٹ_Fullscreen(SDL_کھڑکی *کھڑکی, بنية wl_output *output, bool fullscreen)
{
    SDL_کھڑکی_انکڑے *wind = کھڑکی->اندرونی;

#جے_تعریف_شدہ HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (!wind->shell_surface.libdecor.چوکھٹا) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }

        wind->fullscreen_exclusive = output ? کھڑکی->fullscreen_exclusive : false;
        إذا (fullscreen) {
            libdecor_چوکھٹا_سیٹ_fullscreen(wind->shell_surface.libdecor.چوکھٹا, output);
        } وإلا {
            libdecor_چوکھٹا_unset_fullscreen(wind->shell_surface.libdecor.چوکھٹا);
        }
    } وإلا
#جے_انت
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        إذا (wind->shell_surface.xdg.toplevel.xdg_toplevel == عدم) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }

        wind->fullscreen_exclusive = output ? کھڑکی->fullscreen_exclusive : false;
        إذا (fullscreen) {
            xdg_toplevel_سیٹ_fullscreen(wind->shell_surface.xdg.toplevel.xdg_toplevel, output);
        } وإلا {
            xdg_toplevel_unset_fullscreen(wind->shell_surface.xdg.toplevel.xdg_toplevel);
        }
    }

    جوڑو_Pending_State_Sync(wind);
}

ساكن فراغ Update_کھڑکی_Fullscreen(SDL_کھڑکی *کھڑکی, bool fullscreen)
{
    SDL_کھڑکی_انکڑے *wind = کھڑکی->اندرونی;

    wind->is_fullscreen = fullscreen;

    إذا (fullscreen) {
        إذا (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
            SDL_copyp(&کھڑکی->current_fullscreen_منوال, &کھڑکی->requested_fullscreen_منوال);
            SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_ENTER_FULLSCREEN, 0, 0);
            SDL_Update_Fullscreen_منوال(کھڑکی, SDL_FULLSCREEN_OP_ENTER, false);

            /* Set the output for exclusive fullscreen windows when entering fullscreen from a
             * compositor event, or if the fullscreen parameters were changed between the initial
             * fullscreen request and now, to ensure that the window is on the correct output,
             * as requested by the client.
             */
            إذا (کھڑکی->fullscreen_exclusive && (!wind->fullscreen_exclusive || !wind->fullscreen_was_positioned)) {
                SDL_VideoDisplay *disp = SDL_GetVideoDisplay(کھڑکی->current_fullscreen_منوال.displayID);
                إذا (disp) {
                    wind->fullscreen_was_positioned = true;
                    سیٹ_Fullscreen(کھڑکی, disp->اندرونی->output, true);
                }
            }
        }
    } وإلا {
        // Don't change the fullscreen flags if the window is hidden or being hidden.
        إذا ((کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) && !کھڑکی->is_hiding && !(کھڑکی->flags & SDL_کھڑکی_HIDDEN)) {
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

ساكن ثابت بنية wl_callback_listener surface_چوکھٹا_listener;

ساكن فراغ surface_چوکھٹا_پورا(فراغ *انکڑے, بنية wl_callback *cb, uint32_t ویلا)
{
    SDL_کھڑکی_انکڑے *wind = (SDL_کھڑکی_انکڑے *)انکڑے;

    /* XXX: This is needed to work around an Nvidia egl-wayland bug due to buffer coordinates
     *      being used with wl_surface_damage, which causes part of the output to not be
     *      updated when using a viewport with an output region larger than the source region.
     */
    إذا (wl_compositor_get_نسخہ(wind->wayland_انکڑے->compositor) >= WL_SURFACE_DAMAGE_بفر_SINCE_نسخہ) {
        wl_surface_damage_بفر(wind->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    } وإلا {
        wl_surface_damage(wind->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    }

    wind->pending_state_commit = false;

    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        إذا (wind->pending_config_ack) {
            wind->pending_config_ack = false;
            Configure_کھڑکی_Geometry(wind->sdlwindow);
            xdg_surface_ack_configure(wind->shell_surface.xdg.surface, wind->shell_surface.xdg.serial);
        }
    } وإلا {
        wind->resizing = false;
    }

    إذا (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_اڈیک_FOR_چوکھٹا) {
        wind->shell_surface_حالت = WAYLAND_SHELL_SURFACE_حالت_SHOWN;

        // If any child windows are waiting on this window to be shown, show them now
        لكل (SDL_کھڑکی *w = wind->sdlwindow->پہلا_بچہ; w; w = w->اگلا_sibling) {
            إذا (w->اندرونی->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_SHOW_PENDING) {
                Wayland_Show_کھڑکی(SDL_GetVideoDevice(), w);
            } وإلا إذا (w->اندرونی->reparenting_required) {
                Wayland_سیٹ_کھڑکی_ماپا(SDL_GetVideoDevice(), w, w->ماپا);
                إذا (w->flags & SDL_کھڑکی_MODAL) {
                    Wayland_سیٹ_کھڑکی_Modal(SDL_GetVideoDevice(), w, true);
                }
            }
        }

        /* If the window was initially set to the suspended state, send the occluded event now,
         * as we don't want to mark the window as occluded until at least one frame has been submitted.
         */
        إذا (wind->suspended) {
            SDL_Send_کھڑکی_Event(wind->sdlwindow, SDL_EVENT_کھڑکی_OCCLUDED, 0, 0);
        }
    }

    wl_callback_destroy(cb);
    wind->surface_چوکھٹا_callback = wl_surface_چوکھٹا(wind->surface);
    wl_callback_جوڑو_listener(wind->surface_چوکھٹا_callback, &surface_چوکھٹا_listener, انکڑے);
}

ساكن ثابت بنية wl_callback_listener surface_چوکھٹا_listener = {
    surface_چوکھٹا_پورا
};

ساكن ثابت بنية wl_callback_listener gles_وٹاندرا_چوکھٹا_listener;

ساكن فراغ gles_وٹاندرا_چوکھٹا_پورا(فراغ *انکڑے, بنية wl_callback *cb, uint32_t ویلا)
{
    SDL_کھڑکی_انکڑے *wind = (SDL_کھڑکی_انکڑے *)انکڑے;
    SDL_سیٹ_Atomic_Int(&wind->وٹاندرا_interval_ready, 1); // mark window as ready to present again.

    // reset this callback to fire again once a new frame was presented and compositor wants the next one.
    wind->gles_وٹاندرا_چوکھٹا_callback = wl_surface_چوکھٹا(wind->gles_وٹاندرا_چوکھٹا_surface_wrapper);
    wl_callback_destroy(cb);
    wl_callback_جوڑو_listener(wind->gles_وٹاندرا_چوکھٹا_callback, &gles_وٹاندرا_چوکھٹا_listener, انکڑے);
}

ساكن ثابت بنية wl_callback_listener gles_وٹاندرا_چوکھٹا_listener = {
    gles_وٹاندرا_چوکھٹا_پورا
};

ساكن فراغ handle_xdg_surface_configure(فراغ *انکڑے, بنية xdg_surface *xdg, uint32_t serial)
{
    SDL_کھڑکی_انکڑے *wind = (SDL_کھڑکی_انکڑے *)انکڑے;
    SDL_کھڑکی *کھڑکی = wind->sdlwindow;

    /* Interactive resizes are throttled by acking and committing only the most recent configuration at
     * the next frame callback, or certain combinations of clients and compositors can exhibit severe lag
     * when resizing.
     */
    wind->shell_surface.xdg.serial = serial;
    إذا (!wind->resizing) {
        wind->pending_config_ack = false;
        Configure_کھڑکی_Geometry(کھڑکی);
        xdg_surface_ack_configure(xdg, serial);
    } وإلا إذا (!wind->pending_config_ack) {
        wind->pending_config_ack = true;

        // Always send an exposure event during a new frame to ensure forward progress if the frame callback already occurred.
        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_EXPOSED, 0, 0);
    }

    إذا (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_اڈیک_FOR_CONFIGURE) {
        wind->shell_surface_حالت = WAYLAND_SHELL_SURFACE_حالت_اڈیک_FOR_چوکھٹا;
    }
}

ساكن ثابت بنية xdg_surface_listener _xdg_surface_listener = {
    handle_xdg_surface_configure
};

ساكن فراغ ApplyGeometryLimits(SDL_کھڑکی *کھڑکی, صحيح req_w, صحيح req_h, صحيح *باہرلا_w, صحيح *باہرلا_h)
{
    SDL_کھڑکی_انکڑے *wind = کھڑکی->اندرونی;

    صحيح w = req_w;
    صحيح h = req_h;
    ثابت عائم aspect = (عائم)req_w / (عائم)req_h;

    /* If adjusting for aspect causes the adjusted dimension to exceed the min/max limit, clamp to the limit
     * and attempt to adjust the opposite dimension to compensate.
     */
    إذا (!wind->resizing || (wind->resize_کنارا & WAYLAND_RESIZE_کنارا_کونا) == WAYLAND_RESIZE_کنارا_کونا) {
        إذا (کھڑکی->min_aspect != 0.f && aspect < کھڑکی->min_aspect) {
            h = SDL_max(SDL_lroundf((عائم)req_w / کھڑکی->min_aspect), 1);

            إذا (h < کھڑکی->min_h) {
                w = SDL_max(SDL_lroundf((عائم)کھڑکی->min_h * کھڑکی->min_aspect), 1);
            }
            إذا (کھڑکی->max_h && h > کھڑکی->max_h) {
                w = SDL_max(SDL_lroundf((عائم)کھڑکی->max_h * کھڑکی->min_aspect), 1);
            }
        } وإلا إذا (کھڑکی->max_aspect != 0.f && aspect > کھڑکی->max_aspect) {
            w = SDL_max(SDL_lroundf((عائم)req_h * کھڑکی->max_aspect), 1);

            إذا (w < کھڑکی->min_w) {
                h = SDL_max(SDL_lroundf((عائم)کھڑکی->min_w / کھڑکی->max_aspect), 1);
            }
            إذا (کھڑکی->max_w && w > کھڑکی->max_w) {
                h = SDL_max(SDL_lroundf((عائم)کھڑکی->max_w / کھڑکی->max_aspect), 1);
            }
        }
    } وإلا إذا (wind->resize_کنارا & WAYLAND_RESIZE_کنارا_LR) {
        إذا (کھڑکی->min_aspect != 0.f && aspect < کھڑکی->min_aspect) {
            h = SDL_max(SDL_lroundf((عائم)req_w / کھڑکی->min_aspect), 1);

            إذا (h < کھڑکی->min_h) {
                w = SDL_max(SDL_lroundf((عائم)کھڑکی->min_h * کھڑکی->min_aspect), 1);
            }
            إذا (کھڑکی->max_h && h > کھڑکی->max_h) {
                w = SDL_max(SDL_lroundf((عائم)کھڑکی->max_h * کھڑکی->min_aspect), 1);
            }
        } وإلا إذا (کھڑکی->max_aspect != 0.f && aspect > کھڑکی->max_aspect) {
            h = SDL_max(SDL_lroundf((عائم)req_w / کھڑکی->max_aspect), 1);

            إذا (h < کھڑکی->min_h) {
                w = SDL_max(SDL_lroundf((عائم)کھڑکی->min_h * کھڑکی->max_aspect), 1);
            }
            إذا (کھڑکی->max_h && h > کھڑکی->max_h) {
                w = SDL_max(SDL_lroundf((عائم)کھڑکی->max_h * کھڑکی->max_aspect), 1);
            }
        }
    } وإلا إذا (wind->resize_کنارا & WAYLAND_RESIZE_کنارا_TB) {
        إذا (کھڑکی->min_aspect != 0.f && aspect < کھڑکی->min_aspect) {
            w = SDL_max(SDL_lroundf((عائم)req_h * کھڑکی->min_aspect), 1);

            إذا (w < کھڑکی->min_w) {
                h = SDL_max(SDL_lroundf((عائم)کھڑکی->min_w / کھڑکی->min_aspect), 1);
            }
            إذا (کھڑکی->max_w && w > کھڑکی->max_w) {
                h = SDL_max(SDL_lroundf((عائم)کھڑکی->max_w / کھڑکی->min_aspect), 1);
            }
        } وإلا إذا (کھڑکی->max_aspect != 0.f && aspect > کھڑکی->max_aspect) {
            w = SDL_max(SDL_lroundf((عائم)req_h * کھڑکی->max_aspect), 1);

            إذا (w < کھڑکی->min_w) {
                h = SDL_max(SDL_lroundf((عائم)کھڑکی->min_w / کھڑکی->max_aspect), 1);
            }
            إذا (کھڑکی->max_w && w > کھڑکی->max_w) {
                h = SDL_max(SDL_lroundf((عائم)کھڑکی->max_w / کھڑکی->max_aspect), 1);
            }
        }
    }

    إذا (کھڑکی->max_w) {
        w = SDL_min(w, کھڑکی->max_w);
    }
    *باہرلا_w = SDL_max(w, کھڑکی->min_w);

    إذا (کھڑکی->max_h) {
        h = SDL_min(h, کھڑکی->max_h);
    }
    *باہرلا_h = SDL_max(h, کھڑکی->min_h);

}

ساكن فراغ DetermineResizeAxis(SDL_کھڑکی_انکڑے *wind, صحيح چوڑائی, صحيح اچائی, bool resizing)
{
    /* Try to determine the axis along which the window is being resized.
     *
     * Every compositor is different, and some will start sending strange values once the resize
     * begins, so only the first change is safe to try and determine the resize edge.
     *
     * Some compositors don't send a configure event with the resize flag cleared when the resize ends,
     * so a reset timer is required.
     */
    إذا (resizing) {
        ثابت Uint64 now = SDL_GetTicksNS();
        إذا (now >= wind->آخری_resize_event_ویلا_ns + SDL_MS_منزل_NS(500)) {
            wind->resize_کنارا = 0;
        }

        wind->آخری_resize_event_ویلا_ns = now;

        إذا (!wind->resize_کنارا) {
            إذا (چوڑائی != wind->آخری_configure.چوڑائی || !اچائی) {
                wind->resize_کنارا |= WAYLAND_RESIZE_کنارا_LR;
            }
            إذا (اچائی != wind->آخری_configure.اچائی || !چوڑائی) {
                wind->resize_کنارا |= WAYLAND_RESIZE_کنارا_TB;
            }
        }
    } وإلا {
        wind->resize_کنارا = 0;
    }

    wind->resizing = resizing;
}

ساكن فراغ handle_xdg_toplevel_configure(فراغ *انکڑے,
                                          بنية xdg_toplevel *xdg_toplevel,
                                          int32_t چوڑائی,
                                          int32_t اچائی,
                                          بنية wl_array *حالتاں)
{
    SDL_کھڑکی_انکڑے *wind = (SDL_کھڑکی_انکڑے *)انکڑے;
    SDL_کھڑکی *کھڑکی = wind->sdlwindow;

    تعداد xdg_toplevel_state *state;
    bool fullscreen = false;
    bool maximized = false;
    bool floating = true;
    bool tiled = false;
    bool سرگرم = false;
    bool resizing = false;
    bool suspended = false;
    wind->toplevel_constraints = 0;
    wl_array_for_each (state, حالتاں) {
        بدل (*state) {
        حالة XDG_TOPLEVEL_STATE_FULLSCREEN:
            fullscreen = true;
            floating = false;
            اكسر;
        حالة XDG_TOPLEVEL_STATE_MAXIMIZED:
            maximized = true;
            floating = false;
            اكسر;
        حالة XDG_TOPLEVEL_STATE_RESIZING:
            resizing = true;
            اكسر;
        حالة XDG_TOPLEVEL_STATE_ACTIVATED:
            سرگرم = true;
            اكسر;
        حالة XDG_TOPLEVEL_STATE_TILED_بایاں:
        حالة XDG_TOPLEVEL_STATE_TILED_دایاں:
        حالة XDG_TOPLEVEL_STATE_TILED_چوٹی:
        حالة XDG_TOPLEVEL_STATE_TILED_BOTTOM:
            tiled = true;
            floating = false;
            اكسر;
        حالة XDG_TOPLEVEL_STATE_SUSPENDED:
            suspended = true;
            اكسر;
        حالة XDG_TOPLEVEL_STATE_CONSTRAINED_بایاں:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_بایاں;
            اكسر;
        حالة XDG_TOPLEVEL_STATE_CONSTRAINED_دایاں:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_دایاں;
            اكسر;
        حالة XDG_TOPLEVEL_STATE_CONSTRAINED_چوٹی:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_چوٹی;
            اكسر;
        حالة XDG_TOPLEVEL_STATE_CONSTRAINED_BOTTOM:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM;
            اكسر;
        افتراضي:
            اكسر;
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
    ثابت bool new_configure_ناپ = چوڑائی != wind->آخری_configure.چوڑائی || اچائی != wind->آخری_configure.اچائی ||
                                    insets_apply != wind->آخری_configure.insets_apply;

    BorderInsets insets = { 0, 0, 0, 0 };
    إذا (insets_apply) {
        GetBorderInsets(کھڑکی, &insets);
    }

    DetermineResizeAxis(wind, چوڑائی, اچائی, resizing);
    Update_کھڑکی_Fullscreen(کھڑکی, fullscreen);

    /* Always send a maximized/restore event; if the event is redundant it will
     * automatically be discarded (see src/events/SDL_windowevents.c)
     *
     * No, we do not get minimize events from xdg-shell, however, the minimized
     * state can be programmatically set. The meaning of 'minimized' is compositor
     * dependent, but in general, we can assume that the flag should remain set until
     * the next focused configure event occurs.
     */
    إذا (سرگرم || !(کھڑکی->flags & SDL_کھڑکی_MINIMIZED)) {
        إذا (کھڑکی->flags & SDL_کھڑکی_MINIMIZED) {
            // If we were minimized, send a restored event before possibly sending maximized.
            SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESTORED, 0, 0);
        }
        SDL_Send_کھڑکی_Event(کھڑکی,
                            (maximized && !fullscreen) ? SDL_EVENT_کھڑکی_MAXIMIZED : SDL_EVENT_کھڑکی_RESTORED,
                            0, 0);
    }

    إذا (!fullscreen) {
        /* xdg_toplevel spec states that this is a suggestion.
         * Ignore if less than or greater than max/min size.
         */
        إذا ((کھڑکی->flags & SDL_کھڑکی_RESIZABLE) || maximized) {
            إذا (!چوڑائی) {
                /* This happens when the compositor indicates that the size is
                 * up to the client, so use the cached window size here.
                 */
                إذا (floating) {
                    چوڑائی = کھڑکی->floating.w;

                    // Clamp the window to the toplevel bounds, if any are set.
                    إذا (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_اڈیک_FOR_CONFIGURE && wind->toplevel_bounds.چوڑائی) {
                        چوڑائی = SDL_min(wind->toplevel_bounds.چوڑائی, چوڑائی);
                    }
                } وإلا {
                    چوڑائی = کھڑکی->windowed.w;
                }

                إذا (!wind->scale_منزل_display) {
                    wind->requested.logical_چوڑائی = چوڑائی;
                } وإلا {
                    wind->requested.pixel_چوڑائی = چوڑائی;
                    چوڑائی = wind->requested.logical_چوڑائی = Pixel_منزل_نقطہ(کھڑکی, چوڑائی);
                }
                چوڑائی = SDL_max(چوڑائی - (insets.بایاں + insets.دایاں), 1);
            } وإلا إذا (new_configure_ناپ) {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 */

                wind->requested.logical_چوڑائی = چوڑائی + (insets.بایاں + insets.دایاں);

                إذا (wind->scale_منزل_display) {
                    wind->requested.pixel_چوڑائی = نقطہ_منزل_Pixel(کھڑکی, wind->requested.logical_چوڑائی);
                }
            }
            إذا (!اچائی) {
                /* This happens when the compositor indicates that the size is
                 * up to the client, so use the cached window size here.
                 */
                إذا (floating) {
                    اچائی = کھڑکی->floating.h;

                    // Clamp the window to the toplevel bounds, if any are set.
                    إذا (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_اڈیک_FOR_CONFIGURE && wind->toplevel_bounds.اچائی) {
                        اچائی = SDL_min(wind->toplevel_bounds.اچائی, اچائی);
                    }
                } وإلا {
                    اچائی = کھڑکی->windowed.h;
                }

                إذا (!wind->scale_منزل_display) {
                    wind->requested.logical_اچائی = اچائی;
                } وإلا {
                    wind->requested.pixel_اچائی = اچائی;
                    اچائی = wind->requested.logical_اچائی = Pixel_منزل_نقطہ(کھڑکی, اچائی);
                }
                اچائی = SDL_max(اچائی - (insets.چوٹی + insets.bottom), 1);
            } وإلا إذا (new_configure_ناپ) {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 */
                wind->requested.logical_اچائی = اچائی + (insets.چوٹی + insets.bottom);

                إذا (wind->scale_منزل_display) {
                    wind->requested.pixel_اچائی = نقطہ_منزل_Pixel(کھڑکی, wind->requested.logical_اچائی);
                }
            }
        } وإلا {
            /* If we're a fixed-size, non-maximized window, we know our size for sure.
             * Always assume the configure is wrong.
             */
            إذا (!wind->scale_منزل_display) {
                چوڑائی = wind->requested.logical_چوڑائی = کھڑکی->floating.w;
                اچائی = wind->requested.logical_اچائی = کھڑکی->floating.h;
            } وإلا {
                wind->requested.pixel_چوڑائی = کھڑکی->floating.w;
                wind->requested.pixel_اچائی = کھڑکی->floating.h;
                چوڑائی = wind->requested.logical_چوڑائی = Pixel_منزل_نقطہ(کھڑکی, کھڑکی->floating.w);
                اچائی = wind->requested.logical_اچائی = Pixel_منزل_نقطہ(کھڑکی, کھڑکی->floating.h);
            }
            چوڑائی = SDL_max(چوڑائی - (insets.بایاں + insets.دایاں), 1);
            اچائی = SDL_max(اچائی - (insets.چوٹی + insets.bottom), 1);
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
        إذا (floating) {
            إذا (!wind->scale_منزل_display) {
                ApplyGeometryLimits(کھڑکی, wind->requested.logical_چوڑائی, wind->requested.logical_اچائی, &wind->requested.logical_چوڑائی, &wind->requested.logical_اچائی);
            } وإلا {
                ApplyGeometryLimits(کھڑکی, wind->requested.pixel_چوڑائی, wind->requested.pixel_اچائی, &wind->requested.pixel_چوڑائی, &wind->requested.pixel_اچائی);

                wind->requested.logical_چوڑائی = Pixel_منزل_نقطہ(کھڑکی, wind->requested.pixel_چوڑائی);
                wind->requested.logical_اچائی = Pixel_منزل_نقطہ(کھڑکی, wind->requested.pixel_اچائی);
            }
        }
    } وإلا {
        // Fullscreen windows know their exact size.
        إذا (چوڑائی == 0 || اچائی == 0) {
            چوڑائی = wind->requested.logical_چوڑائی;
            اچائی = wind->requested.logical_اچائی;
        } وإلا {
            wind->requested.logical_چوڑائی = چوڑائی;
            wind->requested.logical_اچائی = اچائی;
        }

        إذا (wind->scale_منزل_display) {
            wind->requested.pixel_چوڑائی = نقطہ_منزل_Pixel(کھڑکی, چوڑائی);
            wind->requested.pixel_اچائی = نقطہ_منزل_Pixel(کھڑکی, اچائی);
        }
    }

    wind->آخری_configure.چوڑائی = چوڑائی;
    wind->آخری_configure.اچائی = اچائی;
    wind->آخری_configure.insets_apply = insets_apply;
    wind->floating = floating;
    wind->suspended = suspended;
    wind->سرگرم = سرگرم;
    کھڑکی->tiled = tiled;
}

ساكن فراغ handle_xdg_toplevel_close(فراغ *انکڑے, بنية xdg_toplevel *xdg_toplevel)
{
    SDL_کھڑکی_انکڑے *کھڑکی = (SDL_کھڑکی_انکڑے *)انکڑے;
    SDL_Send_کھڑکی_Event(کھڑکی->sdlwindow, SDL_EVENT_کھڑکی_CLOSE_REQUESTED, 0, 0);
}

ساكن فراغ handle_xdg_toplevel_configure_bounds(فراغ *انکڑے,
                                                 بنية xdg_toplevel *xdg_toplevel,
                                                 int32_t چوڑائی, int32_t اچائی)
{
    SDL_کھڑکی_انکڑے *کھڑکی = (SDL_کھڑکی_انکڑے *)انکڑے;
    کھڑکی->toplevel_bounds.چوڑائی = چوڑائی;
    کھڑکی->toplevel_bounds.اچائی = اچائی;
}

ساكن فراغ handle_xdg_toplevel_wm_capabilities(فراغ *انکڑے,
                                                بنية xdg_toplevel *xdg_toplevel,
                                                بنية wl_array *capabilities)
{
    SDL_کھڑکی_انکڑے *wind = (SDL_کھڑکی_انکڑے *)انکڑے;
    تعداد xdg_toplevel_wm_capabilities *wm_cap;

    wind->wm_caps = 0;

    wl_array_for_each (wm_cap, capabilities) {
        بدل (*wm_cap) {
        حالة XDG_TOPLEVEL_WM_CAPABILITIES_کھڑکی_MENU:
            wind->wm_caps |= WAYLAND_WM_CAPS_کھڑکی_MENU;
            اكسر;
        حالة XDG_TOPLEVEL_WM_CAPABILITIES_MAXIMIZE:
            wind->wm_caps |= WAYLAND_WM_CAPS_MAXIMIZE;
            اكسر;
        حالة XDG_TOPLEVEL_WM_CAPABILITIES_FULLSCREEN:
            wind->wm_caps |= WAYLAND_WM_CAPS_FULLSCREEN;
            اكسر;
        حالة XDG_TOPLEVEL_WM_CAPABILITIES_MINIMIZE:
            wind->wm_caps |= WAYLAND_WM_CAPS_MINIMIZE;
            اكسر;
        افتراضي:
            اكسر;
        }
    }
}

ساكن ثابت بنية xdg_toplevel_listener toplevel_listener_xdg = {
    handle_xdg_toplevel_configure,
    handle_xdg_toplevel_close,
    handle_xdg_toplevel_configure_bounds, // Version 4
    handle_xdg_toplevel_wm_capabilities   // Version 5
};

ساكن فراغ handle_xdg_popup_configure(فراغ *انکڑے,
                                       بنية xdg_popup *xdg_popup,
                                       int32_t x,
                                       int32_t y,
                                       int32_t چوڑائی,
                                       int32_t اچائی)
{
    SDL_کھڑکی_انکڑے *wind = (SDL_کھڑکی_انکڑے *)انکڑے;
    صحيح وتھ_x = 0, وتھ_y = 0;

    // Adjust the position if it was offset for libdecor
    Adjust_Popup_وتھ(wind->sdlwindow, &وتھ_x, &وتھ_y);
    x -= وتھ_x;
    y -= وتھ_y;

    /* This happens when the compositor indicates that the size is
     * up to the client, so use the cached window size here.
     */
    إذا (چوڑائی == 0 || اچائی == 0) {
        چوڑائی = wind->sdlwindow->floating.w;
        اچائی = wind->sdlwindow->floating.h;
    }

    /* Don't apply the supplied dimensions if they haven't changed from the last configuration
     * event, or a newer size set programmatically can be overwritten by old data.
     */
    إذا (چوڑائی != wind->آخری_configure.چوڑائی || اچائی != wind->آخری_configure.اچائی) {
        wind->requested.logical_چوڑائی = چوڑائی;
        wind->requested.logical_اچائی = اچائی;

        إذا (wind->scale_منزل_display) {
            wind->requested.pixel_چوڑائی = نقطہ_منزل_Pixel(wind->sdlwindow, چوڑائی);
            wind->requested.pixel_اچائی = نقطہ_منزل_Pixel(wind->sdlwindow, اچائی);
        }
    }

    إذا (wind->scale_منزل_display) {
        x = نقطہ_منزل_Pixel(wind->sdlwindow->ماپا, x);
        y = نقطہ_منزل_Pixel(wind->sdlwindow->ماپا, y);
    }

    SDL_Send_کھڑکی_Event(wind->sdlwindow, SDL_EVENT_کھڑکی_MOVED, x, y);

    wind->آخری_configure.چوڑائی = چوڑائی;
    wind->آخری_configure.اچائی = اچائی;

    إذا (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_اڈیک_FOR_CONFIGURE) {
        wind->shell_surface_حالت = WAYLAND_SHELL_SURFACE_حالت_اڈیک_FOR_چوکھٹا;
    }
}

ساكن فراغ handle_xdg_popup_پورا(فراغ *انکڑے, بنية xdg_popup *xdg_popup)
{
    SDL_کھڑکی_انکڑے *کھڑکی = (SDL_کھڑکی_انکڑے *)انکڑے;
    SDL_Send_کھڑکی_Event(کھڑکی->sdlwindow, SDL_EVENT_کھڑکی_CLOSE_REQUESTED, 0, 0);
}

ساكن فراغ handle_xdg_popup_repositioned(فراغ *انکڑے,
                                          بنية xdg_popup *xdg_popup,
                                          uint32_t token)
{
    // No-op, configure does all the work we care about
}

ساكن ثابت بنية xdg_popup_listener _xdg_popup_listener = {
    handle_xdg_popup_configure,
    handle_xdg_popup_پورا,
    handle_xdg_popup_repositioned
};

ساكن فراغ handle_xdg_toplevel_decoration_configure(فراغ *انکڑے,
                                                     بنية zxdg_toplevel_decoration_v1 *zxdg_toplevel_decoration_v1,
                                                     uint32_t منوال)
{
    SDL_کھڑکی *کھڑکی = (SDL_کھڑکی *)انکڑے;
    SDL_کھڑکی_انکڑے *اندرونی = کھڑکی->اندرونی;
    SDL_VideoDevice *device = SDL_GetVideoDevice();

    /* If the compositor tries to force CSD anyway, bail on direct XDG support
     * and fall back to libdecor, it will handle these events from then on.
     *
     * To do this we have to fully unmap, then map with libdecor loaded.
     */
    إذا (منوال == ZXDG_TOPLEVEL_DECORATION_V1_منوال_CLIENT_SIDE) {
        إذا (کھڑکی->flags & SDL_کھڑکی_BORDERLESS) {
            // borderless windows do request CSD, so we got what we wanted
            أرجع;
        }
        إذا (!Wayland_لدو_Libdecor(اندرونی->wayland_انکڑے, true)) {
            // libdecor isn't available, so no borders for you... oh well
            أرجع;
        }
        WAYLAND_wl_display_roundtrip(اندرونی->wayland_انکڑے->display);

        Wayland_Hide_کھڑکی(device, کھڑکی);
        اندرونی->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR;
        Wayland_Show_کھڑکی(device, کھڑکی);
    }
}

ساكن ثابت بنية zxdg_toplevel_decoration_v1_listener xdg_toplevel_decoration_listener = {
    handle_xdg_toplevel_decoration_configure
};

#جے_تعریف_شدہ HAVE_LIBDECOR_H
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
ساكن فراغ OverrideLibdecorLimits(SDL_کھڑکی *کھڑکی)
{
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    إذا (!libdecor_چوکھٹا_get_min_content_ناپ) {
        libdecor_چوکھٹا_سیٹ_min_content_ناپ(کھڑکی->اندرونی->shell_surface.libdecor.چوکھٹا, کھڑکی->min_w, کھڑکی->min_h);
    }
#وإلاإذا !SDL_LIBDECOR_CHECK_نسخہ(0, 2, 0)
    libdecor_چوکھٹا_سیٹ_min_content_ناپ(کھڑکی->اندرونی->shell_surface.libdecor.چوکھٹا, کھڑکی->min_w, کھڑکی->min_h);
#جے_انت
}

/*
 * NOTE: Retrieves the minimum content size limits, if the function for doing so is available.
 *       On versions of libdecor that lack the minimum content size retrieval function, this
 *       function is a no-op.
 *
 *       Can be replaced with a direct call if the minimum required version of libdecor is raised
 *       to 0.1.2 or higher.
 */
ساكن فراغ Libdecor_Get_Min_Content_ناپ(بنية libdecor_چوکھٹا *چوکھٹا, صحيح *min_w, صحيح *min_h)
{
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    إذا (libdecor_چوکھٹا_get_min_content_ناپ != عدم) {
        libdecor_چوکھٹا_get_min_content_ناپ(چوکھٹا, min_w, min_h);
    }
#وإلاإذا SDL_LIBDECOR_CHECK_نسخہ(0, 2, 0)
    libdecor_چوکھٹا_get_min_content_ناپ(چوکھٹا, min_w, min_h);
#جے_انت
}

ساكن فراغ decoration_چوکھٹا_configure(بنية libdecor_چوکھٹا *چوکھٹا,
                                       بنية libdecor_configuration *configuration,
                                       فراغ *user_انکڑے_2)
{
    SDL_کھڑکی_انکڑے *wind = (SDL_کھڑکی_انکڑے *)user_انکڑے_2;
    SDL_کھڑکی *کھڑکی = wind->sdlwindow;

    تعداد libdecor_کھڑکی_state کھڑکی_state;
    صحيح چوڑائی, اچائی;

    bool سرگرم = false;
    bool fullscreen = false;
    bool maximized = false;
    bool tiled = false;
    bool suspended = false;
    bool resizing = false;
    wind->toplevel_constraints = 0;

    ساكن ثابت تعداد libdecor_کھڑکی_state tiled_حالتاں = (LIBDECOR_کھڑکی_STATE_TILED_بایاں | LIBDECOR_کھڑکی_STATE_TILED_دایاں |
                                                            LIBDECOR_کھڑکی_STATE_TILED_چوٹی | LIBDECOR_کھڑکی_STATE_TILED_BOTTOM);

    إذا (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_اڈیک_FOR_CONFIGURE) {
        Libdecor_Get_Min_Content_ناپ(چوکھٹا, &wind->system_limits.min_چوڑائی_2, &wind->system_limits.min_اچائی_2);
    }

    // Window State
    إذا (libdecor_configuration_get_کھڑکی_state(configuration, &کھڑکی_state)) {
        fullscreen = (کھڑکی_state & LIBDECOR_کھڑکی_STATE_FULLSCREEN) != 0;
        maximized = (کھڑکی_state & LIBDECOR_کھڑکی_STATE_MAXIMIZED) != 0;
        سرگرم = (کھڑکی_state & LIBDECOR_کھڑکی_STATE_سرگرم) != 0;
        tiled = (کھڑکی_state & tiled_حالتاں) != 0;
#إذا SDL_LIBDECOR_CHECK_نسخہ(0, 2, 0)
        suspended = (کھڑکی_state & LIBDECOR_کھڑکی_STATE_SUSPENDED) != 0;
#جے_انت
#إذا SDL_LIBDECOR_CHECK_نسخہ(0, 3, 0)
        resizing = (کھڑکی_state & LIBDECOR_کھڑکی_STATE_RESIZING) != 0;

        إذا (کھڑکی_state & LIBDECOR_کھڑکی_STATE_CONSTRAINED_بایاں) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_بایاں;
        }
        إذا (کھڑکی_state & LIBDECOR_کھڑکی_STATE_CONSTRAINED_دایاں) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_دایاں;
        }
        إذا (کھڑکی_state & LIBDECOR_کھڑکی_STATE_CONSTRAINED_چوٹی) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_چوٹی;
        }
        إذا (کھڑکی_state & LIBDECOR_کھڑکی_STATE_CONSTRAINED_BOTTOM) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM;
        }
#جے_انت
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
    إذا (سرگرم || !(کھڑکی->flags & SDL_کھڑکی_MINIMIZED)) {
        إذا (کھڑکی->flags & SDL_کھڑکی_MINIMIZED) {
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
    إذا (fullscreen) {
        إذا (!libdecor_configuration_get_content_ناپ(configuration, چوکھٹا, &چوڑائی, &اچائی)) {
            چوڑائی = wind->requested.logical_چوڑائی;
            اچائی = wind->requested.logical_اچائی;
        } وإلا {
            // Fullscreen windows know their exact size.
            wind->requested.logical_چوڑائی = چوڑائی;
            wind->requested.logical_اچائی = اچائی;

            إذا (wind->scale_منزل_display) {
                wind->requested.pixel_چوڑائی = نقطہ_منزل_Pixel(کھڑکی, چوڑائی);
                wind->requested.pixel_اچائی = نقطہ_منزل_Pixel(کھڑکی, اچائی);
            }
        }
    } وإلا {
        إذا (!(کھڑکی->flags & SDL_کھڑکی_RESIZABLE) && !maximized) {
            /* If we're a fixed-size, non-maximized window, we know our size for sure.
             * Always assume the configure is wrong.
             */
            إذا (!wind->scale_منزل_display) {
                چوڑائی = wind->requested.logical_چوڑائی = کھڑکی->floating.w;
                اچائی = wind->requested.logical_اچائی = کھڑکی->floating.h;
            } وإلا {
                wind->requested.pixel_چوڑائی = کھڑکی->floating.w;
                wind->requested.pixel_اچائی = کھڑکی->floating.h;
                چوڑائی = wind->requested.logical_چوڑائی = Pixel_منزل_نقطہ(کھڑکی, کھڑکی->floating.w);
                اچائی = wind->requested.logical_اچائی = Pixel_منزل_نقطہ(کھڑکی, کھڑکی->floating.h);
            }

            OverrideLibdecorLimits(کھڑکی);
        } وإلا {
            /* XXX: The libdecor cairo plugin sends bogus content sizes that add the
             *      height of the title bar when transitioning from a fixed-size to
             *      floating state. Ignore the sent window dimensions in this case,
             *      in favor of the cached value to avoid the window increasing in
             *      size after every state transition.
             *
             *      https://gitlab.freedesktop.org/libdecor/libdecor/-/issues/34
             */
            إذا ((floating && (!wind->floating && !(کھڑکی->flags & SDL_کھڑکی_BORDERLESS))) ||
                !libdecor_configuration_get_content_ناپ(configuration, چوکھٹا, &چوڑائی, &اچائی)) {
                چوڑائی = 0;
                اچائی = 0;
            }

            ثابت bool new_configure_ناپ = چوڑائی != wind->آخری_configure.چوڑائی || اچائی != wind->آخری_configure.اچائی;
            DetermineResizeAxis(wind, چوڑائی, اچائی, resizing);

            إذا (!چوڑائی) {
                /* This happens when we're being restored from a non-floating state,
                 * or the compositor indicates that the size is up to the client, so
                 * used the cached window size here.
                 */
                إذا (floating) {
                    چوڑائی = کھڑکی->floating.w;

                    // Clamp the window to the toplevel bounds, if any are set.
                    إذا (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_اڈیک_FOR_CONFIGURE && wind->toplevel_bounds.چوڑائی) {
                        چوڑائی = SDL_min(wind->toplevel_bounds.چوڑائی, چوڑائی);
                    }
                } وإلا {
                    چوڑائی = کھڑکی->windowed.w;
                }

                إذا (!wind->scale_منزل_display) {
                    wind->requested.logical_چوڑائی = چوڑائی;
                } وإلا {
                    wind->requested.pixel_چوڑائی = چوڑائی;
                    چوڑائی = wind->requested.logical_چوڑائی = Pixel_منزل_نقطہ(کھڑکی, چوڑائی);
                }
            } وإلا {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 *
                 * If a client takes a long time to present the first frame after creating the window, a
                 * configure event to set the suspended state may arrive with the content size increased
                 * by the decoration dimensions, which should also be ignored.
                 */
                إذا (new_configure_ناپ &&
                    !(wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_اڈیک_FOR_چوکھٹا && wind->suspended != suspended)) {
                    wind->requested.logical_چوڑائی = چوڑائی;

                    إذا (wind->scale_منزل_display) {
                        wind->requested.pixel_چوڑائی = نقطہ_منزل_Pixel(کھڑکی, چوڑائی);
                    }
                }
            }

            إذا (!اچائی) {
                /* This happens when we're being restored from a non-floating state,
                 * or the compositor indicates that the size is up to the client, so
                 * used the cached window size here.
                 */
                إذا (floating) {
                    اچائی = کھڑکی->floating.h;

                    // Clamp the window to the toplevel bounds, if any are set.
                    إذا (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_اڈیک_FOR_CONFIGURE && wind->toplevel_bounds.اچائی) {
                        اچائی = SDL_min(wind->toplevel_bounds.اچائی, اچائی);
                    }
                } وإلا {
                    اچائی = کھڑکی->windowed.h;
                }

                إذا (!wind->scale_منزل_display) {
                    wind->requested.logical_اچائی = اچائی;
                } وإلا {
                    wind->requested.pixel_اچائی = اچائی;
                    اچائی = wind->requested.logical_اچائی = Pixel_منزل_نقطہ(کھڑکی, اچائی);
                }
            } وإلا {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 *
                 * If a client takes a long time to present the first frame after creating the window, a
                 * configure event to set the suspended state may arrive with the content size increased
                 * by the decoration dimensions, which should also be ignored.
                 */
                إذا (new_configure_ناپ &&
                    !(wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_اڈیک_FOR_چوکھٹا && wind->suspended != suspended)) {
                    wind->requested.logical_اچائی = اچائی;

                    إذا (wind->scale_منزل_display) {
                        wind->requested.pixel_اچائی = نقطہ_منزل_Pixel(کھڑکی, اچائی);
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
        إذا (floating) {
            إذا (!wind->scale_منزل_display) {
                ApplyGeometryLimits(کھڑکی, wind->requested.logical_چوڑائی, wind->requested.logical_اچائی, &wind->requested.logical_چوڑائی, &wind->requested.logical_اچائی);
            } وإلا {
                ApplyGeometryLimits(کھڑکی, wind->requested.pixel_چوڑائی, wind->requested.pixel_اچائی, &wind->requested.pixel_چوڑائی, &wind->requested.pixel_اچائی);

                wind->requested.logical_چوڑائی = Pixel_منزل_نقطہ(کھڑکی, wind->requested.pixel_چوڑائی);
                wind->requested.logical_اچائی = Pixel_منزل_نقطہ(کھڑکی, wind->requested.pixel_اچائی);
            }
        }
    }

    // Store the new state.
    ثابت bool started_resize = !wind->resizing && resizing;
    wind->آخری_configure.چوڑائی = چوڑائی;
    wind->آخری_configure.اچائی = اچائی;
    wind->floating = floating;
    wind->suspended = suspended;
    wind->سرگرم = سرگرم;
    کھڑکی->tiled = tiled;
    wind->resizing = resizing;

    // Update the window manager capabilities.
#إذا SDL_LIBDECOR_CHECK_نسخہ(0, 3, 0)
    تعداد libdecor_wm_capabilities caps;
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    إذا (libdecor_چوکھٹا_get_wm_capabilities) {
        caps = libdecor_چوکھٹا_get_wm_capabilities(wind->shell_surface.libdecor.چوکھٹا);
#وإلا
    caps = libdecor_چوکھٹا_get_wm_capabilities(wind->shell_surface.libdecor.چوکھٹا);
    {
#جے_انت
        wind->wm_caps = 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_کھڑکی_MENU ? WAYLAND_WM_CAPS_کھڑکی_MENU : 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_MAXIMIZE ? WAYLAND_WM_CAPS_MAXIMIZE : 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_FULLSCREEN ? WAYLAND_WM_CAPS_FULLSCREEN : 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_MINIMIZE ? WAYLAND_WM_CAPS_MINIMIZE : 0;
    }
#جے_انت

    إذا (!wind->resizing || started_resize) {
        /* Calculate the new window geometry and commit the changes on the libdecor side.
         *
         * XXX: This will potentially leave un-acked configurations, but libdecor invalidates the
         *      configuration upon returning from the frame event, so there is nothing that can be
         *      done, unless libdecor adds the ability to copy or refcount the configuration state
         *      to apply later.
         */
        Configure_کھڑکی_Geometry(کھڑکی);
        بنية libdecor_state *state = libdecor_state_new(wind->current.logical_چوڑائی, wind->current.logical_اچائی);
        libdecor_چوکھٹا_commit(چوکھٹا, state, configuration);
        libdecor_state_free(state);

        // Always send an exposure event during a new frame to ensure forward progress if the frame callback already occurred.
        إذا (started_resize) {
            SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_EXPOSED, 0, 0);
        }
    }

    إذا (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_اڈیک_FOR_CONFIGURE) {
        wind->shell_surface_حالت = WAYLAND_SHELL_SURFACE_حالت_اڈیک_FOR_چوکھٹا;
    }
}

ساكن فراغ decoration_چوکھٹا_close(بنية libdecor_چوکھٹا *چوکھٹا, فراغ *user_انکڑے_2)
{
    SDL_Send_کھڑکی_Event(((SDL_کھڑکی_انکڑے *)user_انکڑے_2)->sdlwindow, SDL_EVENT_کھڑکی_CLOSE_REQUESTED, 0, 0);
}

ساكن فراغ decoration_چوکھٹا_commit(بنية libdecor_چوکھٹا *چوکھٹا, فراغ *user_انکڑے_2)
{
    /* libdecor decoration subsurfaces are synchronous, so the client needs to
     * commit a frame to trigger an update of the decoration surfaces.
     */
    SDL_کھڑکی_انکڑے *wind = (SDL_کھڑکی_انکڑے *)user_انکڑے_2;
    إذا (!wind->suspended && wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_SHOWN) {
        SDL_Send_کھڑکی_Event(wind->sdlwindow, SDL_EVENT_کھڑکی_EXPOSED, 0, 0);
    }
}

ساكن فراغ decoration_dismiss_popup(بنية libdecor_چوکھٹا *چوکھٹا, ثابت حرف *seat_name, فراغ *user_انکڑے_2)
{
    // NOP
}

#إذا SDL_LIBDECOR_CHECK_نسخہ(0, 3, 0)
ساكن فراغ decoration_چوکھٹا_bounds(بنية libdecor_چوکھٹا *چوکھٹا, صحيح چوڑائی, صحيح اچائی, فراغ *user_انکڑے_2)
{
    SDL_کھڑکی_انکڑے *کھڑکی = (SDL_کھڑکی_انکڑے *)user_انکڑے_2;
    کھڑکی->toplevel_bounds.چوڑائی = چوڑائی;
    کھڑکی->toplevel_bounds.اچائی = اچائی;
}
#جے_انت

ساكن بنية libdecor_چوکھٹا_interface libdecor_چوکھٹا_interface = {
    decoration_چوکھٹا_configure,
    decoration_چوکھٹا_close,
    decoration_چوکھٹا_commit,
    decoration_dismiss_popup,
#إذا SDL_LIBDECOR_CHECK_نسخہ(0, 3, 0)
    decoration_چوکھٹا_bounds
#جے_انت
};
#جے_انت

ساكن فراغ Wayland_Handle_Preferred_Scale_بدلیا(SDL_کھڑکی_انکڑے *کھڑکی_انکڑے_2, مزدوج ضارب)
{
    ثابت مزدوج old_ضارب = کھڑکی_انکڑے_2->scale_ضارب_2;

    // Round the scale factor if viewports aren't available.
    إذا (!کھڑکی_انکڑے_2->viewport) {
        ضارب = SDL_ceil(ضارب);
    }

    إذا (ضارب != old_ضارب) {
        کھڑکی_انکڑے_2->scale_ضارب_2 = ضارب;

        إذا (کھڑکی_انکڑے_2->scale_منزل_display) {
            /* If the window is in the floating state with a user/application specified size, calculate the new
             * logical size from the backbuffer size. Otherwise, use the fixed underlying logical size to calculate
             * the new backbuffer dimensions.
             */
            إذا (کھڑکی_انکڑے_2->floating) {
                /* Some compositors will send a configure event immediately after a scale event, however,
                 * this event can contain the old logical size, and should be ignored, or the window can
                 * incorrectly change size when moved between displays with differing scale factors.
                 *
                 * Store the last requested logical size as the last configure size, so a configure event
                 * with the old size will be ignored. Configure sizes are in window geometry space,
                 * so subtract any border insets.
                 */
                BorderInsets insets;
                GetBorderInsets(کھڑکی_انکڑے_2->sdlwindow, &insets);
                کھڑکی_انکڑے_2->آخری_configure.چوڑائی = SDL_max(کھڑکی_انکڑے_2->requested.logical_چوڑائی - (insets.بایاں + insets.دایاں), 1);
                کھڑکی_انکڑے_2->آخری_configure.اچائی = SDL_max(کھڑکی_انکڑے_2->requested.logical_اچائی - (insets.چوٹی + insets.bottom), 1);

                کھڑکی_انکڑے_2->requested.logical_چوڑائی = Pixel_منزل_نقطہ(کھڑکی_انکڑے_2->sdlwindow, کھڑکی_انکڑے_2->requested.pixel_چوڑائی);
                کھڑکی_انکڑے_2->requested.logical_اچائی = Pixel_منزل_نقطہ(کھڑکی_انکڑے_2->sdlwindow, کھڑکی_انکڑے_2->requested.pixel_اچائی);
            } وإلا {
                کھڑکی_انکڑے_2->requested.pixel_چوڑائی = نقطہ_منزل_Pixel(کھڑکی_انکڑے_2->sdlwindow, کھڑکی_انکڑے_2->requested.logical_چوڑائی);
                کھڑکی_انکڑے_2->requested.pixel_اچائی = نقطہ_منزل_Pixel(کھڑکی_انکڑے_2->sdlwindow, کھڑکی_انکڑے_2->requested.logical_اچائی);
            }
        }

        إذا (کھڑکی_انکڑے_2->sdlwindow->flags & SDL_کھڑکی_بلند_PIXEL_DENSITY || کھڑکی_انکڑے_2->scale_منزل_display) {
            Configure_کھڑکی_Geometry(کھڑکی_انکڑے_2->sdlwindow);
            Commit_Libdecor_چوکھٹا(کھڑکی_انکڑے_2->sdlwindow);
        }
    }
}

ساكن فراغ Wayland_Maybe_Update_Scale_ضارب(SDL_کھڑکی_انکڑے *کھڑکی)
{
    مزدوج ضارب;
    صحيح i;

    /* If the fractional scale protocol is present or the core protocol supports the
     * preferred buffer scale event, the compositor will explicitly tell the application
     * what scale it wants via these events, so don't try to determine the scale factor
     * from which displays the surface has entered.
     */
    إذا (کھڑکی->fractional_scale || wl_surface_get_نسخہ(کھڑکی->surface) >= WL_SURFACE_PREFERRED_بفر_SCALE_SINCE_نسخہ) {
        أرجع;
    }

    إذا (کھڑکی->عدد_outputs != 0) {
        // Check every display's factor, use the highest
        ضارب = 0.0;
        لكل (i = 0; i < کھڑکی->عدد_outputs; i++) {
            SDL_Display_انکڑے *اندرونی = کھڑکی->outputs[i];
            ضارب = SDL_max(ضارب, اندرونی->scale_ضارب_2);
        }
    } وإلا {
        // All outputs removed, just fall back.
        ضارب = کھڑکی->scale_ضارب_2;
    }

    Wayland_Handle_Preferred_Scale_بدلیا(کھڑکی, ضارب);
}

فراغ Wayland_Remove_Output_From_کھڑکی(SDL_کھڑکی_انکڑے *کھڑکی, SDL_Display_انکڑے *display_انکڑے)
{
    لكل (صحيح i = 0; i < کھڑکی->عدد_outputs; i++) {
        إذا (کھڑکی->outputs[i] == display_انکڑے) { // remove this one
            إذا (i == (کھڑکی->عدد_outputs - 1)) {
                کھڑکی->outputs[i] = عدم;
            } وإلا {
                SDL_memmove(&کھڑکی->outputs[i],
                            &کھڑکی->outputs[i + 1],
                            حجم(SDL_Display_انکڑے *) * ((کھڑکی->عدد_outputs - i) - 1));
            }
            کھڑکی->عدد_outputs--;
            i--;
        }
    }

    إذا (کھڑکی->عدد_outputs == 0) {
        SDL_free(کھڑکی->outputs);
        کھڑکی->outputs = عدم;
    } وإلا إذا (!کھڑکی->is_fullscreen || کھڑکی->عدد_outputs == 1) {
        Wayland_Update_کھڑکی_Position(کھڑکی->sdlwindow);
        Wayland_Maybe_Update_Scale_ضارب(کھڑکی);
    }
}

ساكن فراغ handle_surface_enter(فراغ *انکڑے, بنية wl_surface *surface, بنية wl_output *output)
{
    SDL_کھڑکی_انکڑے *کھڑکی = انکڑے;
    SDL_Display_انکڑے *اندرونی = wl_output_get_user_انکڑے(output);
    SDL_Display_انکڑے **new_outputs;

    إذا (!SDL_WAYLAND_own_output(output) || !SDL_WAYLAND_own_surface(surface)) {
        أرجع;
    }

    new_outputs = SDL_realloc(کھڑکی->outputs,
                              حجم(SDL_Display_انکڑے *) * (کھڑکی->عدد_outputs + 1));
    إذا (!new_outputs) {
        أرجع;
    }
    کھڑکی->outputs = new_outputs;
    کھڑکی->outputs[کھڑکی->عدد_outputs++] = اندرونی;

    // Update the scale factor after the move so that fullscreen outputs are updated.
    إذا (!کھڑکی->is_fullscreen || کھڑکی->عدد_outputs == 1) {
        Wayland_Update_کھڑکی_Position(کھڑکی->sdlwindow);
        Wayland_Maybe_Update_Scale_ضارب(کھڑکی);
    }
}

ساكن فراغ handle_surface_leave(فراغ *انکڑے, بنية wl_surface *surface, بنية wl_output *output)
{
    SDL_کھڑکی_انکڑے *کھڑکی = (SDL_کھڑکی_انکڑے *)انکڑے;

    إذا (!SDL_WAYLAND_own_output(output) || !SDL_WAYLAND_own_surface(surface)) {
        أرجع;
    }

    Wayland_Remove_Output_From_کھڑکی(کھڑکی, (SDL_Display_انکڑے *)wl_output_get_user_انکڑے(output));
}

ساكن فراغ handle_surface_preferred_بفر_scale(فراغ *انکڑے, بنية wl_surface *wl_surface, int32_t ضارب)
{
    SDL_کھڑکی_انکڑے *wind = انکڑے;

    /* The spec is unclear on how this interacts with the fractional scaling protocol,
     * so, for now, assume that the fractional scaling protocol takes priority and
     * only listen to this event if the fractional scaling protocol is not present.
     */
    إذا (!wind->fractional_scale) {
        Wayland_Handle_Preferred_Scale_بدلیا(انکڑے, (مزدوج)ضارب);
    }
}

ساكن فراغ handle_surface_preferred_بفر_transform(فراغ *انکڑے, بنية wl_surface *wl_surface, uint32_t transform)
{
    // Nothing to do here.
}

ساكن ثابت بنية wl_surface_listener surface_listener = {
    handle_surface_enter,
    handle_surface_leave,
    handle_surface_preferred_بفر_scale,
    handle_surface_preferred_بفر_transform
};

ساكن فراغ handle_fractional_scale_preferred(فراغ *انکڑے, بنية wp_fractional_scale_v1 *wp_fractional_scale_v1, uint32_t scale)
{
    ثابت مزدوج ضارب = (مزدوج)scale / 120.; // 120 is a magic number defined in the spec as a common denominator
    Wayland_Handle_Preferred_Scale_بدلیا(انکڑے, ضارب);
}

ساكن ثابت بنية wp_fractional_scale_v1_listener fractional_scale_listener = {
    handle_fractional_scale_preferred
};

ساكن فراغ frog_preferred_metadata_handler(فراغ *انکڑے, بنية frog_color_managed_surface *frog_color_managed_surface, uint32_t transfer_function,
                                            uint32_t output_display_primary_red_x, uint32_t output_display_primary_red_y,
                                            uint32_t output_display_primary_green_x, uint32_t output_display_primary_green_y,
                                            uint32_t output_display_primary_blue_x, uint32_t output_display_primary_blue_y,
                                            uint32_t output_white_نقطہ_x, uint32_t output_white_نقطہ_y,
                                            uint32_t max_luminance, uint32_t min_luminance,
                                            uint32_t max_بھریا_چوکھٹا_luminance)
{
    SDL_کھڑکی_انکڑے *wind = (SDL_کھڑکی_انکڑے *)انکڑے;
    SDL_HDROutputProperties HDR;

    SDL_zero(HDR);

    بدل (transfer_function) {
    حالة FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_ST2084_PQ:
        /* ITU-R BT.2408-7 (Sept 2023) has the reference PQ white level at 203 nits,
         * while older Dolby documentation claims a reference level of 100 nits.
         *
         * Use 203 nits for now.
         */
        HDR.HDR_headroom = max_luminance / 203.0f;
        اكسر;
    حالة FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_SCRGB_خطی:
        HDR.HDR_headroom = max_luminance / 80.0f;
        اكسر;
    حالة FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_UNDEFINED:
    حالة FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_SRGB:
    حالة FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_GAMMA_22:
    افتراضي:
        HDR.HDR_headroom = 1.0f;
        اكسر;
    }

    HDR.SDR_white_level = 1.0f;
    SDL_سیٹ_کھڑکی_HDRProperties(wind->sdlwindow, &HDR, true);
}

ساكن ثابت بنية frog_color_managed_surface_listener frog_surface_listener = {
    frog_preferred_metadata_handler
};


ساكن فراغ handle_surface_feedback_preferred_changed2(فراغ *انکڑے,
                                                       بنية wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback_v1,
                                                       uint32_t پچھان_تت_hi, uint32_t پچھان_تت_lo)
{
    SDL_کھڑکی_انکڑے *wind = (SDL_کھڑکی_انکڑے *)انکڑے;
    Wayland_Get_Color_Info_For_کھڑکی(wind, false);
}

ساكن فراغ handle_surface_feedback_preferred_بدلیا(فراغ *انکڑے,
                                                      بنية wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback_v1,
                                                      uint32_t پچھان_تت)
{
    handle_surface_feedback_preferred_changed2(انکڑے, wp_color_management_surface_feedback_v1, 0, پچھان_تت);
}

ساكن ثابت بنية wp_color_management_surface_feedback_v1_listener color_management_surface_feedback_listener = {
    handle_surface_feedback_preferred_بدلیا,
    handle_surface_feedback_preferred_changed2
};

ساكن فراغ Wayland_سیٹ_Keyboard_Focus(SDL_کھڑکی *کھڑکی, bool سیٹ_focus)
{
    SDL_کھڑکی *toplevel = کھڑکی;

    // Find the toplevel parent
    طالما (SDL_کھڑکی_IS_POPUP(toplevel)) {
        toplevel = toplevel->ماپا;
    }

    toplevel->keyboard_focus = کھڑکی;

    إذا (سیٹ_focus && !کھڑکی->is_hiding && !کھڑکی->is_destroying) {
        SDL_سیٹ_Keyboard_Focus(کھڑکی);
    }
}

bool Wayland_سیٹ_کھڑکی_کامیابی_Test(SDL_کھڑکی *کھڑکی, bool enabled)
{
    أرجع true; // just succeed, the real work is done elsewhere.
}

ساكن بنية xdg_toplevel *Get_Toplevel_For_کھڑکی(SDL_کھڑکی_انکڑے *wind)
{
    إذا (wind) {
        /* Libdecor crashes on attempts to unset the parent by passing null, which is allowed by the
         * toplevel spec, so just use the raw xdg-toplevel instead (that's what libdecor does
         * internally anyways).
         */
#جے_تعریف_شدہ HAVE_LIBDECOR_H
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.چوکھٹا) {
            أرجع libdecor_چوکھٹا_get_xdg_toplevel(wind->shell_surface.libdecor.چوکھٹا);
        } وإلا
#جے_انت
            إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
                أرجع wind->shell_surface.xdg.toplevel.xdg_toplevel;
            }
    }

    أرجع عدم;
}

bool Wayland_سیٹ_کھڑکی_ماپا(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_کھڑکی *ماپا_کھڑکی)
{
    SDL_کھڑکی_انکڑے *بچہ_انکڑے = کھڑکی->اندرونی;
    SDL_کھڑکی_انکڑے *ماپا_انکڑے = ماپا_کھڑکی ? ماپا_کھڑکی->اندرونی : عدم;

    بچہ_انکڑے->reparenting_required = false;

    إذا (ماپا_انکڑے && ماپا_انکڑے->shell_surface_حالت != WAYLAND_SHELL_SURFACE_حالت_SHOWN) {
        // Need to wait for the parent to become mapped, or it's the same as setting a null parent.
        بچہ_انکڑے->reparenting_required = true;
        أرجع true;
    }

    بنية xdg_toplevel *بچہ_toplevel = Get_Toplevel_For_کھڑکی(بچہ_انکڑے);
    بنية xdg_toplevel *ماپا_toplevel = Get_Toplevel_For_کھڑکی(ماپا_انکڑے);

    إذا (بچہ_toplevel) {
        xdg_toplevel_سیٹ_ماپا(بچہ_toplevel, ماپا_toplevel);
    }

    أرجع true;
}

bool Wayland_سیٹ_کھڑکی_Modal(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool modal)
{
    SDL_Video_انکڑے *viddata = _this->اندرونی;
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    SDL_کھڑکی_انکڑے *ماپا_انکڑے = کھڑکی->ماپا->اندرونی;

    إذا (ماپا_انکڑے->shell_surface_حالت != WAYLAND_SHELL_SURFACE_حالت_SHOWN) {
        // Need to wait for the parent to become mapped before changing modal status.
        انکڑے->reparenting_required = true;
        أرجع true;
    } وإلا {
        انکڑے->reparenting_required = false;
    }

    بنية xdg_toplevel *toplevel = Get_Toplevel_For_کھڑکی(انکڑے);

    إذا (toplevel) {
        إذا (viddata->xdg_wm_dialog_v1) {
            إذا (modal) {
                إذا (!انکڑے->xdg_dialog_v1) {
                    انکڑے->xdg_dialog_v1 = xdg_wm_dialog_v1_get_xdg_dialog(viddata->xdg_wm_dialog_v1, toplevel);
                }

                xdg_dialog_v1_سیٹ_modal(انکڑے->xdg_dialog_v1);
            } وإلا إذا (انکڑے->xdg_dialog_v1) {
                xdg_dialog_v1_unset_modal(انکڑے->xdg_dialog_v1);
            }
        }
    }

    أرجع true;
}

ساكن فراغ Wayland_رجسٹر_Toplevel_For_Session(SDL_کھڑکی_انکڑے *انکڑے)
{
    بنية xdg_toplevel *toplevel = Get_Toplevel_For_کھڑکی(انکڑے);
    إذا (!toplevel) {
        أرجع;
    }

    ثابت حرف *id = SDL_GetStringProperty(انکڑے->sdlwindow->props, SDL_PROP_کھڑکی_WAYLAND_کھڑکی_ID_STRING, عدم);
    إذا (id && *id != '\0') {
        SDL_VideoDevice *viddev = SDL_GetVideoDevice();
        SDL_Video_انکڑے *viddata = viddev->اندرونی;

        إذا (viddata->xdg_toplevel_ٹیگ_manager) {
            xdg_toplevel_ٹیگ_manager_v1_سیٹ_toplevel_ٹیگ(viddata->xdg_toplevel_ٹیگ_manager, toplevel, id);
        }

        إذا (viddata->xdg_session_manager) {
            Wayland_CreateSession(viddata);

            إذا (viddata->xdg_session) {
                CHECK_PARAM (true) {
                    // Windows added to a session must not have a duplicate ID string, or a protocol error will result.
                    لكل (SDL_کھڑکی *w = viddev->windows; w; w = w->اگلا) {
                        SDL_کھڑکی_انکڑے *d = w->اندرونی;
                        إذا (d->session_id && SDL_strcmp(d->session_id, id) == 0) {
                            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Duplicate window ID string %s found; window will not be added to session", id);
                            أرجع;
                        }
                    }
                }

                انکڑے->xdg_toplevel_session = xdg_session_v1_restore_toplevel(viddata->xdg_session, toplevel, id);
                انکڑے->session_id = SDL_strdup(id);
            }
        }
    }
}

ساكن فراغ Wayland_DestroyToplevelSession(SDL_کھڑکی_انکڑے *انکڑے)
{
    SDL_Video_انکڑے *viddata = انکڑے->wayland_انکڑے;

    إذا (انکڑے->xdg_toplevel_session) {
        ثابت حرف *id = SDL_GetStringProperty(انکڑے->sdlwindow->props, SDL_PROP_کھڑکی_WAYLAND_کھڑکی_ID_STRING, عدم);

        // If the ID string was cleared, remove the window from the session.
        إذا (!id || *id == '\0') {
            xdg_session_v1_remove_toplevel(viddata->xdg_session, انکڑے->session_id);
        }

        xdg_toplevel_session_v1_destroy(انکڑے->xdg_toplevel_session);
        انکڑے->xdg_toplevel_session = عدم;

        SDL_free(انکڑے->session_id);
        انکڑے->session_id = عدم;
    }
}

ساكن فراغ show_hide_sync_handler(فراغ *انکڑے, بنية wl_callback *callback, uint32_t callback_انکڑے)
{
    // Get the window from the ID as it may have been destroyed
    SDL_کھڑکی_ID کھڑکی_ID = (SDL_کھڑکی_ID)((uintptr_t)انکڑے);
    SDL_کھڑکی *کھڑکی = SDL_Get_کھڑکی_From_ID(کھڑکی_ID);

    إذا (کھڑکی && کھڑکی->اندرونی) {
        SDL_کھڑکی_انکڑے *wind = کھڑکی->اندرونی;
        wind->show_hide_sync_required = false;
    }

    wl_callback_destroy(callback);
}

ساكن بنية wl_callback_listener show_hide_sync_listener = {
    show_hide_sync_handler
};

ساكن فراغ exported_handle_handler(فراغ *انکڑے, بنية zxdg_exported_v2 *zxdg_exported_v2, ثابت حرف *handle)
{
    SDL_کھڑکی_انکڑے *wind = (SDL_کھڑکی_انکڑے *)انکڑے;
    SDL_PropertiesID props = SDL_Get_کھڑکی_Properties(wind->sdlwindow);

    SDL_سیٹ_String_Property(props, SDL_PROP_کھڑکی_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, handle);
}

ساكن بنية zxdg_exported_v2_listener exported_v2_listener = {
    exported_handle_handler
};

فراغ Wayland_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_انکڑے *c = _this->اندرونی;
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    SDL_PropertiesID props = SDL_Get_کھڑکی_Properties(کھڑکی);

    // Custom surfaces don't get toplevels and are always considered 'shown'; nothing to do here.
    إذا (انکڑے->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        أرجع;
    }

    /* If this is a child window, the parent *must* be in the final shown state,
     * meaning that it has received a configure event, followed by a frame callback.
     * If not, a race condition can result, with effects ranging from the child
     * window to spuriously closing to protocol errors.
     *
     * If waiting on the parent window, set the pending status and the window will
     * be shown when the parent is in the shown state.
     */
    إذا (کھڑکی->ماپا) {
        إذا (کھڑکی->ماپا->اندرونی->shell_surface_حالت != WAYLAND_SHELL_SURFACE_حالت_SHOWN) {
            انکڑے->shell_surface_حالت = WAYLAND_SHELL_SURFACE_حالت_SHOW_PENDING;
            أرجع;
        }
    }

    // Always roundtrip to ensure there are no pending buffer attachments.
    افعل {
        WAYLAND_wl_display_roundtrip(c->display);
    } طالما (انکڑے->show_hide_sync_required);

    انکڑے->shell_surface_حالت = WAYLAND_SHELL_SURFACE_حالت_اڈیک_FOR_CONFIGURE;

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
    wl_surface_attach(انکڑے->surface, عدم, 0, 0);
    wl_surface_commit(انکڑے->surface);

    // Create the shell surface and map the toplevel/popup
#جے_تعریف_شدہ HAVE_LIBDECOR_H
    إذا (انکڑے->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        انکڑے->shell_surface.libdecor.چوکھٹا = libdecor_decorate(c->shell.libdecor,
                                                               انکڑے->surface,
                                                               &libdecor_چوکھٹا_interface,
                                                               انکڑے);
        إذا (!انکڑے->shell_surface.libdecor.چوکھٹا) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Failed to create libdecor frame!");
        } وإلا {
            libdecor_چوکھٹا_سیٹ_app_id(انکڑے->shell_surface.libdecor.چوکھٹا, انکڑے->app_id);
            libdecor_چوکھٹا_map(انکڑے->shell_surface.libdecor.چوکھٹا);
            إذا (کھڑکی->flags & SDL_کھڑکی_BORDERLESS) {
                // Note: Calling this with 'true' immediately after mapping will cause the libdecor Cairo plugin to crash.
                libdecor_چوکھٹا_سیٹ_visibility(انکڑے->shell_surface.libdecor.چوکھٹا, false);
            }

            إذا (c->zxdg_exporter_v2) {
                انکڑے->exported = zxdg_exporter_v2_export_toplevel(c->zxdg_exporter_v2, انکڑے->surface);
                zxdg_exported_v2_جوڑو_listener(انکڑے->exported, &exported_v2_listener, انکڑے);
            }

            إذا (c->xdg_toplevel_icon_manager_v1 && انکڑے->xdg_toplevel_icon_v1) {
                xdg_toplevel_icon_manager_v1_سیٹ_icon(_this->اندرونی->xdg_toplevel_icon_manager_v1,
                                                      libdecor_چوکھٹا_get_xdg_toplevel(انکڑے->shell_surface.libdecor.چوکھٹا),
                                                      انکڑے->xdg_toplevel_icon_v1);
            }

            SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WAYLAND_XDG_SURFACE_اشارہ_گر, libdecor_چوکھٹا_get_xdg_surface(انکڑے->shell_surface.libdecor.چوکھٹا));
            SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WAYLAND_XDG_TOPLEVEL_اشارہ_گر, libdecor_چوکھٹا_get_xdg_toplevel(انکڑے->shell_surface.libdecor.چوکھٹا));
        }
    } وإلا
#جے_انت
    إذا (انکڑے->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL || انکڑے->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        انکڑے->shell_surface.xdg.surface = xdg_wm_ادھار_get_xdg_surface(c->shell.xdg, انکڑے->surface);
        xdg_surface_سیٹ_user_انکڑے(انکڑے->shell_surface.xdg.surface, انکڑے);
        xdg_surface_جوڑو_listener(انکڑے->shell_surface.xdg.surface, &_xdg_surface_listener, انکڑے);
        SDL_سیٹ_اشارہ_گر_Property(SDL_Get_کھڑکی_Properties(کھڑکی), SDL_PROP_کھڑکی_WAYLAND_XDG_SURFACE_اشارہ_گر, انکڑے->shell_surface.xdg.surface);

        إذا (انکڑے->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
            SDL_کھڑکی *ماپا = کھڑکی->ماپا;
            SDL_کھڑکی_انکڑے *ماپا_انکڑے = ماپا->اندرونی;
            بنية xdg_surface *ماپا_xdg_surface = عدم;
            صحيح position_x = 0, position_y = 0;

            // Configure the popup parameters
#جے_تعریف_شدہ HAVE_LIBDECOR_H
            إذا (ماپا_انکڑے->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                ماپا_xdg_surface = libdecor_چوکھٹا_get_xdg_surface(ماپا_انکڑے->shell_surface.libdecor.چوکھٹا);
            } وإلا
#جے_انت
            إذا (ماپا_انکڑے->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL ||
                    ماپا_انکڑے->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
                ماپا_xdg_surface = ماپا_انکڑے->shell_surface.xdg.surface;
            }

            // Set up the positioner for the popup and configure the constraints
            انکڑے->shell_surface.xdg.popup.xdg_positioner = xdg_wm_ادھار_create_positioner(c->shell.xdg);
            xdg_positioner_سیٹ_anchor(انکڑے->shell_surface.xdg.popup.xdg_positioner, XDG_POSITIONER_ANCHOR_چوٹی_بایاں);
            SDL_Rect ماپا_geometry;
            Get_کھڑکی_Geometry(ماپا->اندرونی, &ماپا_geometry);
            xdg_positioner_سیٹ_anchor_rect(انکڑے->shell_surface.xdg.popup.xdg_positioner, 0, 0, ماپا_geometry.w, ماپا_geometry.h);

            ثابت Uint32 constraint = کھڑکی->constrain_popup ? (XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_SLIDE_X | XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_SLIDE_Y) : XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_NONE;
            xdg_positioner_سیٹ_constraint_adjustment(انکڑے->shell_surface.xdg.popup.xdg_positioner, constraint);
            xdg_positioner_سیٹ_gravity(انکڑے->shell_surface.xdg.popup.xdg_positioner, XDG_POSITIONER_GRAVITY_BOTTOM_دایاں);
            xdg_positioner_سیٹ_ناپ(انکڑے->shell_surface.xdg.popup.xdg_positioner, انکڑے->current.logical_چوڑائی, انکڑے->current.logical_اچائی);

            // Set the popup initial position
            position_x = کھڑکی->آخری_position_pending ? کھڑکی->pending.x : کھڑکی->x;
            position_y = کھڑکی->آخری_position_pending ? کھڑکی->pending.y : کھڑکی->y;
            EnsurePopupPositionIsValid(کھڑکی, &position_x, &position_y);
            إذا (انکڑے->scale_منزل_display) {
                position_x = Pixel_منزل_نقطہ(کھڑکی->ماپا, position_x);
                position_y = Pixel_منزل_نقطہ(کھڑکی->ماپا, position_y);
            }
            Adjust_Popup_وتھ(کھڑکی, &position_x, &position_y);
            xdg_positioner_سیٹ_وتھ(انکڑے->shell_surface.xdg.popup.xdg_positioner, position_x, position_y);

            // Assign the popup role
            انکڑے->shell_surface.xdg.popup.xdg_popup = xdg_surface_get_popup(انکڑے->shell_surface.xdg.surface,
                                                                                ماپا_xdg_surface,
                                                                                انکڑے->shell_surface.xdg.popup.xdg_positioner);
            xdg_popup_جوڑو_listener(انکڑے->shell_surface.xdg.popup.xdg_popup, &_xdg_popup_listener, انکڑے);

            إذا (کھڑکی->flags & SDL_کھڑکی_TOOLTIP) {
                بنية wl_region *region;

                // Tooltips can't be interacted with, so turn off the input region to avoid blocking anything behind them
                region = wl_compositor_create_region(c->compositor);
                wl_region_جوڑو(region, 0, 0, 0, 0);
                wl_surface_سیٹ_داخلہ_region(انکڑے->surface, region);
                wl_region_destroy(region);
            } وإلا إذا ((کھڑکی->flags & SDL_کھڑکی_POPUP_MENU) && !(کھڑکی->flags & SDL_کھڑکی_NOT_FOCUSABLE)) {
                Wayland_سیٹ_Keyboard_Focus(کھڑکی, true);
            }

            SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WAYLAND_XDG_POPUP_اشارہ_گر, انکڑے->shell_surface.xdg.popup.xdg_popup);
            SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WAYLAND_XDG_POSITIONER_اشارہ_گر, انکڑے->shell_surface.xdg.popup.xdg_positioner);
        } وإلا {
            انکڑے->shell_surface.xdg.toplevel.xdg_toplevel = xdg_surface_get_toplevel(انکڑے->shell_surface.xdg.surface);
            xdg_toplevel_سیٹ_app_id(انکڑے->shell_surface.xdg.toplevel.xdg_toplevel, انکڑے->app_id);
            xdg_toplevel_جوڑو_listener(انکڑے->shell_surface.xdg.toplevel.xdg_toplevel, &toplevel_listener_xdg, انکڑے);

            // Create the window decorations
            إذا (c->decoration_manager) {
                انکڑے->server_decoration = zxdg_decoration_manager_v1_get_toplevel_decoration(c->decoration_manager, انکڑے->shell_surface.xdg.toplevel.xdg_toplevel);
                zxdg_toplevel_decoration_v1_جوڑو_listener(انکڑے->server_decoration, &xdg_toplevel_decoration_listener, کھڑکی);
                ثابت تعداد zxdg_toplevel_decoration_v1_منوال منوال = !(کھڑکی->flags & SDL_کھڑکی_BORDERLESS) ? ZXDG_TOPLEVEL_DECORATION_V1_منوال_SERVER_SIDE : ZXDG_TOPLEVEL_DECORATION_V1_منوال_CLIENT_SIDE;
                zxdg_toplevel_decoration_v1_سیٹ_منوال(انکڑے->server_decoration, منوال);
            }

            إذا (c->zxdg_exporter_v2) {
                انکڑے->exported = zxdg_exporter_v2_export_toplevel(c->zxdg_exporter_v2, انکڑے->surface);
                zxdg_exported_v2_جوڑو_listener(انکڑے->exported, &exported_v2_listener, انکڑے);
            }

            إذا (c->xdg_toplevel_icon_manager_v1 && انکڑے->xdg_toplevel_icon_v1) {
                xdg_toplevel_icon_manager_v1_سیٹ_icon(_this->اندرونی->xdg_toplevel_icon_manager_v1,
                                                      انکڑے->shell_surface.xdg.toplevel.xdg_toplevel,
                                                      انکڑے->xdg_toplevel_icon_v1);
            }

            SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WAYLAND_XDG_TOPLEVEL_اشارہ_گر, انکڑے->shell_surface.xdg.toplevel.xdg_toplevel);
        }
    }

    // Restore state that was set prior to this call
    Wayland_رجسٹر_Toplevel_For_Session(انکڑے);
    Wayland_سیٹ_کھڑکی_ماپا(_this, کھڑکی, کھڑکی->ماپا);

    إذا (کھڑکی->flags & SDL_کھڑکی_MODAL) {
        Wayland_سیٹ_کھڑکی_Modal(_this, کھڑکی, true);
    }

    Wayland_سیٹ_کھڑکی_Title(_this, کھڑکی);

    /* We have to wait until the surface gets a "configure" event, or use of
     * this surface will fail. This is a new rule for xdg_shell.
     */
#جے_تعریف_شدہ HAVE_LIBDECOR_H
    إذا (انکڑے->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (انکڑے->shell_surface.libdecor.چوکھٹا) {
            طالما (انکڑے->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_اڈیک_FOR_CONFIGURE) {
                إذا (libdecor_dispatch(c->shell.libdecor, -1) < 0) {
                    إذا (!Wayland_HandleDisplayDisconnected(_this)) {
                        أرجع;
                    }
                }
                إذا (WAYLAND_wl_display_dispatch_pending(c->display) < 0) {
                    إذا (!Wayland_HandleDisplayDisconnected(_this)) {
                        أرجع;
                    }
                }
            }
        }
    } وإلا
#جے_انت
        إذا (انکڑے->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP || انکڑے->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        /* Unlike libdecor we need to call this explicitly to prevent a deadlock.
         * libdecor will call this as part of their configure event!
         * -flibit
         */
        wl_surface_commit(انکڑے->surface);
        إذا (انکڑے->shell_surface.xdg.surface) {
            طالما (انکڑے->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_اڈیک_FOR_CONFIGURE) {
                إذا (WAYLAND_wl_display_dispatch(c->display) < 0) {
                    إذا (!Wayland_HandleDisplayDisconnected(_this)) {
                        أرجع;
                    }
                }
            }
        }
    } وإلا {
        // Nothing to see here, just commit.
        wl_surface_commit(انکڑے->surface);
    }

    // Make sure the window can't be resized to 0, or it can be spuriously closed by the window manager.
    انکڑے->system_limits.min_چوڑائی_2 = SDL_max(انکڑے->system_limits.min_چوڑائی_2, 1);
    انکڑے->system_limits.min_اچائی_2 = SDL_max(انکڑے->system_limits.min_اچائی_2, 1);

    /* Unlike the rest of window state we have to set this _after_ flushing the
     * display, because we need to create the decorations before possibly hiding
     * them immediately afterward.
     */
#جے_تعریف_شدہ HAVE_LIBDECOR_H
    إذا (انکڑے->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        // Libdecor plugins can enforce minimum window sizes, so adjust if the initial window size is too small.
        إذا (کھڑکی->windowed.w < انکڑے->system_limits.min_چوڑائی_2 ||
            کھڑکی->windowed.h < انکڑے->system_limits.min_اچائی_2) {

            // Warn if the window frame will be larger than the content surface.
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO,
                        "Window dimensions (%i, %i) are smaller than the system enforced minimum (%i, %i); window borders will be larger than the content surface.",
                        کھڑکی->windowed.w, کھڑکی->windowed.h, انکڑے->system_limits.min_چوڑائی_2, انکڑے->system_limits.min_اچائی_2);

            انکڑے->current.logical_چوڑائی = SDL_max(کھڑکی->windowed.w, انکڑے->system_limits.min_چوڑائی_2);
            انکڑے->current.logical_اچائی = SDL_max(کھڑکی->windowed.h, انکڑے->system_limits.min_اچائی_2);
            Commit_Libdecor_چوکھٹا(کھڑکی);
        }
    }
#جے_انت
    Wayland_سیٹ_کھڑکی_Resizable(_this, کھڑکی, !!(کھڑکی->flags & SDL_کھڑکی_RESIZABLE));

    // We're finally done putting the window together, raise if possible
    إذا (c->activation_manager && SDL_GetHintBoolean(SDL_HINT_کھڑکی_ACTIVATE_WHEN_SHOWN, true)) {
        /* if the process was passed an activation token, use it when showing
         * the initial window.
         *
         * Note that we don't check for empty strings, as that is still
         * considered a valid activation token!
         */
        ثابت حرف *activation_token = SDL_getenv("XDG_ACTIVATION_TOKEN");
        إذا (activation_token) {
            xdg_activation_v1_activate(c->activation_manager,
                                       activation_token,
                                       انکڑے->surface);

            // Clear this variable, per the protocol's request
            SDL_unsetenv_unsafe("XDG_ACTIVATION_TOKEN");
        } وإلا {
            // Try to generate an activation token for this window.
            Wayland_Raise_کھڑکی(_this, کھڑکی);
        }
    } وإلا {
        // Clear the ignored activation token, as it won't be used.
        SDL_unsetenv_unsafe("XDG_ACTIVATION_TOKEN");
    }

    // No frame callback on an external surface, as it may already have one attached.
    إذا (!(کھڑکی->flags & SDL_کھڑکی_EXTERNAL)) {
        // Fire a callback when the compositor wants a new frame.
        انکڑے->surface_چوکھٹا_callback = wl_surface_چوکھٹا(انکڑے->surface);
        wl_callback_جوڑو_listener(انکڑے->surface_چوکھٹا_callback, &surface_چوکھٹا_listener, انکڑے);
    }

    انکڑے->show_hide_sync_required = true;
    بنية wl_callback *cb = wl_display_sync(_this->اندرونی->display);
    wl_callback_جوڑو_listener(cb, &show_hide_sync_listener, (فراغ *)((uintptr_t)کھڑکی->id));

    انکڑے->showing_کھڑکی = true;
    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_SHOWN, 0, 0);
    انکڑے->showing_کھڑکی = false;

    // Send an exposure event to signal that the client should draw.
    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_EXPOSED, 0, 0);
}

ساكن فراغ Wayland_ReleasePopup(SDL_VideoDevice *_this, SDL_کھڑکی *popup)
{
    SDL_کھڑکی_انکڑے *popupdata;

    // Basic sanity checks to weed out the weird popup closures
    إذا (!SDL_ObjectValid(popup, SDL_OBJECT_TYPE_کھڑکی)) {
        أرجع;
    }
    popupdata = popup->اندرونی;
    إذا (!popupdata) {
        أرجع;
    }

    // This may already be freed by a parent popup!
    إذا (popupdata->shell_surface.xdg.popup.xdg_popup == عدم) {
        أرجع;
    }

    إذا ((popup->flags & SDL_کھڑکی_POPUP_MENU) && !(popup->flags & SDL_کھڑکی_NOT_FOCUSABLE)) {
        SDL_کھڑکی *new_focus;
        ثابت bool سیٹ_focus = SDL_ShouldRelinquishPopupFocus(popup, &new_focus);
        Wayland_سیٹ_Keyboard_Focus(new_focus, سیٹ_focus);
    }

    xdg_popup_destroy(popupdata->shell_surface.xdg.popup.xdg_popup);
    xdg_positioner_destroy(popupdata->shell_surface.xdg.popup.xdg_positioner);
    popupdata->shell_surface.xdg.popup.xdg_popup = عدم;
    popupdata->shell_surface.xdg.popup.xdg_positioner = عدم;

    SDL_PropertiesID props = SDL_Get_کھڑکی_Properties(popup);
    SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WAYLAND_XDG_POPUP_اشارہ_گر, عدم);
    SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WAYLAND_XDG_POSITIONER_اشارہ_گر, عدم);
}

فراغ Wayland_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;
    SDL_کھڑکی_انکڑے *wind = کھڑکی->اندرونی;
    SDL_PropertiesID props = SDL_Get_کھڑکی_Properties(کھڑکی);

    // Custom surfaces have nothing to destroy and are always considered to be 'shown'; nothing to do here.
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        أرجع;
    }

    /* The window was shown, but the sync point hasn't yet been reached.
     * Pump events to avoid a possible protocol violation.
     */
    إذا (wind->show_hide_sync_required) {
        WAYLAND_wl_display_roundtrip(انکڑے->display);
    }

    wind->shell_surface_حالت = WAYLAND_SHELL_SURFACE_حالت_HIDDEN;

    إذا (wind->surface_چوکھٹا_callback) {
        wl_callback_destroy(wind->surface_چوکھٹا_callback);
        wind->surface_چوکھٹا_callback = عدم;
    }

    إذا (wind->server_decoration) {
        zxdg_toplevel_decoration_v1_destroy(wind->server_decoration);
        wind->server_decoration = عدم;
    }

    // Clean up the export handle.
    إذا (wind->exported) {
        zxdg_exported_v2_destroy(wind->exported);
        wind->exported = عدم;

        SDL_سیٹ_String_Property(props, SDL_PROP_کھڑکی_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, عدم);
    }

    إذا (wind->xdg_dialog_v1) {
        xdg_dialog_v1_destroy(wind->xdg_dialog_v1);
        wind->xdg_dialog_v1 = عدم;
    }

#جے_تعریف_شدہ HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (wind->shell_surface.libdecor.چوکھٹا) {
            libdecor_چوکھٹا_unref(wind->shell_surface.libdecor.چوکھٹا);

            SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WAYLAND_XDG_SURFACE_اشارہ_گر, عدم);
            SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WAYLAND_XDG_TOPLEVEL_اشارہ_گر, عدم);
        }
    } وإلا
#جے_انت
    {
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
            Wayland_ReleasePopup(_this, کھڑکی);
        } وإلا إذا (wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            xdg_toplevel_destroy(wind->shell_surface.xdg.toplevel.xdg_toplevel);
            SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WAYLAND_XDG_TOPLEVEL_اشارہ_گر, عدم);
        }

        إذا (wind->shell_surface.xdg.surface) {
            xdg_surface_destroy(wind->shell_surface.xdg.surface);
            SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WAYLAND_XDG_SURFACE_اشارہ_گر, عدم);
        }
    }

    // Attach a null buffer to unmap the surface.
    إذا (wind->نقاب.surface) {
        wl_surface_attach(wind->نقاب.surface, عدم, 0, 0);
        wl_surface_commit(wind->نقاب.surface);
    }
    wl_surface_attach(wind->surface, عدم, 0, 0);
    wl_surface_commit(wind->surface);

    // Need to destroy the session object after unmapping the window, or the state may not be saved.
    Wayland_DestroyToplevelSession(wind);

    SDL_zero(wind->shell_surface);
    SDL_zero(wind->explicit_geometry);
    wind->show_hide_sync_required = true;
    بنية wl_callback *cb = wl_display_sync(_this->اندرونی->display);
    wl_callback_جوڑو_listener(cb, &show_hide_sync_listener, (فراغ *)((uintptr_t)کھڑکی->id));
}

ساكن فراغ handle_xdg_activation_پورا(فراغ *انکڑے,
                                       بنية xdg_activation_token_v1 *xdg_activation_token_v1,
                                       ثابت حرف *token)
{
    SDL_کھڑکی_انکڑے *کھڑکی = انکڑے;
    إذا (xdg_activation_token_v1 == کھڑکی->activation_token) {
        xdg_activation_v1_activate(کھڑکی->wayland_انکڑے->activation_manager,
                                   token,
                                   کھڑکی->surface);
        xdg_activation_token_v1_destroy(کھڑکی->activation_token);
        کھڑکی->activation_token = عدم;
    }
}

ساكن ثابت بنية xdg_activation_token_v1_listener xdg_activation_listener = {
    handle_xdg_activation_پورا
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
ساكن فراغ Wayland_activate_کھڑکی(SDL_Video_انکڑے *انکڑے, SDL_کھڑکی_انکڑے *نشانہ_wind, bool سیٹ_serial)
{
    SDL_WaylandSeat *seat = انکڑے->آخری_implicit_grab_seat;
    SDL_کھڑکی_انکڑے *focus = عدم;

    إذا (seat) {
        focus = seat->keyboard.focus;
        إذا (!focus) {
            focus = seat->اشارہ_گر_2.focus;
        }
    }

    بنية wl_surface *requesting_surface = focus ? focus->surface : عدم;

    إذا (انکڑے->activation_manager) {
        إذا (نشانہ_wind->activation_token) {
            // We're about to overwrite this with a new request
            xdg_activation_token_v1_destroy(نشانہ_wind->activation_token);
        }

        نشانہ_wind->activation_token = xdg_activation_v1_get_activation_token(انکڑے->activation_manager);
        xdg_activation_token_v1_جوڑو_listener(نشانہ_wind->activation_token,
                                             &xdg_activation_listener,
                                             نشانہ_wind);

        /* Note that we are not setting the app_id here.
         *
         * Hypothetically we could set the app_id from data->classname, but
         * that part of the API is for _external_ programs, not ourselves.
         *
         * -flibit
         */
        إذا (requesting_surface) {
            // This specifies the surface from which the activation request is originating, not the activation target surface.
            xdg_activation_token_v1_سیٹ_surface(نشانہ_wind->activation_token, requesting_surface);
        }
        إذا (سیٹ_serial && seat && seat->wl_seat) {
            xdg_activation_token_v1_سیٹ_serial(نشانہ_wind->activation_token, seat->آخری_implicit_grab_serial, seat->wl_seat);
        }
        xdg_activation_token_v1_commit(نشانہ_wind->activation_token);
    }
}

فراغ Wayland_Raise_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_انکڑے *viddata = _this->اندرونی;
    SDL_کھڑکی_انکڑے *wind = کھڑکی->اندرونی;

    إذا (viddata->activation_manager) {
        /* Check for an activation token, in case the window is being
         * raised in response to a system notification.
         *
         * Note that we don't check for empty strings, as that is still
         * considered a valid activation token!
         */
        ثابت حرف *activation_token = SDL_GetNotificationActivationToken();
        إذا (activation_token) {
            xdg_activation_v1_activate(viddata->activation_manager,
                                       activation_token,
                                       wind->surface);
            أرجع;
        }
    }

    // No token? Try to activate the window via an event serial.
    Wayland_activate_کھڑکی(_this->اندرونی, کھڑکی->اندرونی, true);
}

bool Wayland_Flash_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_FlashOperation operation)
{
    /* Not setting the serial will specify 'urgency' without switching focus as per
     * https://gitlab.freedesktop.org/wayland/wayland-protocols/-/merge_requests/9#note_854977
     */
    Wayland_activate_کھڑکی(_this->اندرونی, کھڑکی->اندرونی, false);
    أرجع true;
}

SDL_Fullscreen_نتیجہ Wayland_سیٹ_کھڑکی_Fullscreen(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی,
                                 SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_کھڑکی_انکڑے *wind = کھڑکی->اندرونی;
    بنية wl_output *output = display->اندرونی->output;

    // Custom surfaces have no toplevel to make fullscreen.
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        أرجع SDL_FULLSCREEN_FAILED;
    }

    // Drop fullscreen leave requests when showing the window.
    إذا (wind->showing_کھڑکی && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        أرجع SDL_FULLSCREEN_SUCCEEDED;
    }

    إذا (wind->show_hide_sync_required) {
        WAYLAND_wl_display_roundtrip(_this->اندرونی->display);
    }

    // Flushing old events pending a new one, ignore this request.
    إذا (wind->drop_fullscreen_بینتیاں) {
        أرجع SDL_FULLSCREEN_SUCCEEDED;
    }

    wind->drop_fullscreen_بینتیاں = true;
    FlushPendingEvents(کھڑکی);
    wind->drop_fullscreen_بینتیاں = false;

    // Nothing to do if the window is not fullscreen, and this isn't an explicit enter request.
    إذا (!wind->is_fullscreen) {
        إذا (fullscreen == SDL_FULLSCREEN_OP_UPDATE) {
            // Request was out of date; signal the video core not to update any state.
            أرجع SDL_FULLSCREEN_PENDING;
        } وإلا إذا (fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
            // Already not fullscreen; nothing to do.
            أرجع SDL_FULLSCREEN_SUCCEEDED;
        }
    }

    // Don't send redundant fullscreen set/unset events.
    إذا (!!fullscreen != wind->is_fullscreen) {
        wind->fullscreen_was_positioned = !!fullscreen;

        /* Only use the specified output if an exclusive mode is being used, or a position was explicitly requested
         * before entering fullscreen desktop. Otherwise, let the compositor handle placement, as it has more
         * information about where the window is and where it should go, particularly if fullscreen is being requested
         * before the window is mapped, or the window spans multiple outputs.
         */
        إذا (!کھڑکی->fullscreen_exclusive) {
            إذا (کھڑکی->undefined_x || کھڑکی->undefined_y ||
                (wind->عدد_outputs && !کھڑکی->آخری_position_pending)) {
                output = عدم;
            }
        }

        // Commit to set any pending size or limit data.
        إذا (fullscreen && wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        سیٹ_Fullscreen(کھڑکی, output, !!fullscreen);
    } وإلا إذا (wind->is_fullscreen) {
        /*
         * If the window is already fullscreen, this is likely a request to switch between
         * fullscreen and fullscreen desktop, change outputs, or change the video mode.
         *
         * If the window is already positioned on the target output, just update the
         * window geometry.
         */
        إذا (wind->آخری_display_ID != display->id) {
            wind->fullscreen_was_positioned = true;
            سیٹ_Fullscreen(کھڑکی, output, true);
        } وإلا {
            Configure_کھڑکی_Geometry(کھڑکی);
            Commit_Libdecor_چوکھٹا(کھڑکی);

            أرجع SDL_FULLSCREEN_SUCCEEDED;
        }
    }

    أرجع SDL_FULLSCREEN_PENDING;
}

فراغ Wayland_Restore_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *wind = کھڑکی->اندرونی;

    // Drop restore requests when showing the window.
    إذا (wind->showing_کھڑکی) {
        أرجع;
    }

    // Not currently fullscreen or maximized, and no state pending; nothing to do.
    إذا (!(کھڑکی->flags & (SDL_کھڑکی_FULLSCREEN | SDL_کھڑکی_MAXIMIZED)) &&
        !wind->pending_state_deadline_گنتی) {
        أرجع;
    }

#جے_تعریف_شدہ HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (!wind->shell_surface.libdecor.چوکھٹا) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }
        libdecor_چوکھٹا_unset_maximized(wind->shell_surface.libdecor.چوکھٹا);
        جوڑو_Pending_State_Sync(wind);
    } وإلا
#جے_انت
        // Note that xdg-shell does NOT provide a way to unset minimize!
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
            إذا (wind->shell_surface.xdg.toplevel.xdg_toplevel == عدم) {
                أرجع; // Can't do anything yet, wait for ShowWindow
            }
            xdg_toplevel_unset_maximized(wind->shell_surface.xdg.toplevel.xdg_toplevel);
            جوڑو_Pending_State_Sync(wind);
        }
}

فراغ Wayland_سیٹ_کھڑکی_Bordered(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool bordered)
{
    SDL_کھڑکی_انکڑے *wind = کھڑکی->اندرونی;
    ثابت SDL_Video_انکڑے *viddata = (ثابت SDL_Video_انکڑے *)_this->اندرونی;

#جے_تعریف_شدہ HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (wind->shell_surface.libdecor.چوکھٹا) {
            libdecor_چوکھٹا_سیٹ_visibility(wind->shell_surface.libdecor.چوکھٹا, bordered);
        }
    } وإلا
#جے_انت
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        إذا ((viddata->decoration_manager) && (wind->server_decoration)) {
            ثابت تعداد zxdg_toplevel_decoration_v1_منوال منوال = bordered ? ZXDG_TOPLEVEL_DECORATION_V1_منوال_SERVER_SIDE : ZXDG_TOPLEVEL_DECORATION_V1_منوال_CLIENT_SIDE;
            zxdg_toplevel_decoration_v1_سیٹ_منوال(wind->server_decoration, منوال);
        }
    }
}

فراغ Wayland_سیٹ_کھڑکی_Resizable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool resizable)
{
    SDL_کھڑکی_انکڑے *wind = کھڑکی->اندرونی;

    /* When changing the resize capability on libdecor windows, the limits must always
     * be reapplied, as when libdecor changes states, it overwrites the values internally.
     */
    سیٹ_Min_Max_Dimensions(کھڑکی);
    Commit_Libdecor_چوکھٹا(کھڑکی);

    إذا (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_SHOWN) {
        wind->pending_state_commit = true;
    }
}

فراغ Wayland_Maximize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *wind = کھڑکی->اندرونی;

    إذا (wind->show_hide_sync_required) {
        WAYLAND_wl_display_roundtrip(_this->اندرونی->display);
    }

    // Not fullscreen, already maximized, and no state pending; nothing to do.
    إذا (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) && (کھڑکی->flags & SDL_کھڑکی_MAXIMIZED) &&
        !wind->pending_state_deadline_گنتی) {
        أرجع;
    }

#جے_تعریف_شدہ HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (!wind->shell_surface.libdecor.چوکھٹا) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }

        // Commit to set any pending size or limit data.
        إذا (wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        libdecor_چوکھٹا_سیٹ_maximized(wind->shell_surface.libdecor.چوکھٹا);
        جوڑو_Pending_State_Sync(wind);
    } وإلا
#جے_انت
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        إذا (wind->shell_surface.xdg.toplevel.xdg_toplevel == عدم) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }

        // Commit to set any pending size or limit data.
        إذا (wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        xdg_toplevel_سیٹ_maximized(wind->shell_surface.xdg.toplevel.xdg_toplevel);
        جوڑو_Pending_State_Sync(wind);
    }
}

فراغ Wayland_Minimize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *wind = کھڑکی->اندرونی;

    إذا (!(wind->wm_caps & WAYLAND_WM_CAPS_MINIMIZE)) {
        أرجع;
    }

#جے_تعریف_شدہ HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (!wind->shell_surface.libdecor.چوکھٹا) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }
        libdecor_چوکھٹا_سیٹ_minimized(wind->shell_surface.libdecor.چوکھٹا);
        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_MINIMIZED, 0, 0);
    } وإلا
#جے_انت
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        إذا (wind->shell_surface.xdg.toplevel.xdg_toplevel == عدم) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }
        xdg_toplevel_سیٹ_minimized(wind->shell_surface.xdg.toplevel.xdg_toplevel);
        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_MINIMIZED, 0, 0);
    }
}

bool Wayland_سیٹ_کھڑکی_Mouse_Rect(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;

    /* This may look suspiciously like SetWindowGrab, despite SetMouseRect not
     * implicitly doing a grab. And you're right! Wayland doesn't let us mess
     * around with mouse focus whatsoever, so it just happens to be that the
     * work that we can do in these two functions ends up being the same.
     *
     * Just know that this call lets you confine with a rect, SetWindowGrab
     * lets you confine without a rect.
     */
    إذا (!انکڑے->اشارہ_گر_constraints) {
        أرجع SDL_سیٹ_Error("Failed to grab mouse: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }
    Wayland_Display_Update_اشارہ_گر_Grabs(انکڑے, کھڑکی->اندرونی);
    أرجع true;
}

bool Wayland_سیٹ_کھڑکی_Mouse_Grab(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool grabbed)
{
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;
    إذا (!انکڑے->اشارہ_گر_constraints) {
        أرجع SDL_سیٹ_Error("Failed to grab mouse: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }
    Wayland_Display_Update_اشارہ_گر_Grabs(انکڑے, کھڑکی->اندرونی);
    أرجع true;
}

bool Wayland_سیٹ_کھڑکی_Keyboard_Grab(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool grabbed)
{
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;
    إذا (!انکڑے->کلید_inhibitor_manager) {
        أرجع SDL_سیٹ_Error("Failed to grab keyboard: compositor lacks support for the required zwp_keyboard_shortcuts_inhibit_manager_v1 protocol");
    }
    Wayland_DisplayUpdateKeyboardGrabs(انکڑے, کھڑکی->اندرونی);
    أرجع true;
}

bool Wayland_Reconfigure_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_کھڑکی_Flags flags)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;

    // Don't try to reconfigure mapped windows, unless they are custom or external.
    إذا (انکڑے->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_SHOWN &&
        انکڑے->shell_surface_type != WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        // Window is already mapped; abort.
        أرجع false;
    }

    /* The caller guarantees that only one of the GL or Vulkan flags will be set.
     * Note that Vulkan doesn't require any specific configuration, so only EGL
     * objects are added and removed as required.
     */
    إذا (flags & SDL_کھڑکی_OPENGL) {
        إذا (!انکڑے->egl_کھڑکی) {
            انکڑے->egl_کھڑکی = WAYLAND_wl_egl_کھڑکی_create(انکڑے->surface, انکڑے->current.pixel_چوڑائی, انکڑے->current.pixel_اچائی);
        }

#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
        انکڑے->egl_surface = SDL_EGL_CreateSurface(_this, کھڑکی, (Native_کھڑکی_Type)انکڑے->egl_کھڑکی);

        إذا (انکڑے->egl_surface == EGL_NO_SURFACE) {
            أرجع false; // SDL_EGL_CreateSurface should have set the error.
        }
#جے_انت

        إذا (!انکڑے->gles_وٹاندرا_چوکھٹا_event_قطار) {
            انکڑے->gles_وٹاندرا_چوکھٹا_event_قطار = WAYLAND_wl_display_create_قطار(انکڑے->wayland_انکڑے->display);
            انکڑے->gles_وٹاندرا_چوکھٹا_surface_wrapper = WAYLAND_wl_proxy_create_wrapper(انکڑے->surface);
            WAYLAND_wl_proxy_سیٹ_قطار((بنية wl_proxy *)انکڑے->gles_وٹاندرا_چوکھٹا_surface_wrapper, انکڑے->gles_وٹاندرا_چوکھٹا_event_قطار);
            انکڑے->gles_وٹاندرا_چوکھٹا_callback = wl_surface_چوکھٹا(انکڑے->gles_وٹاندرا_چوکھٹا_surface_wrapper);
            wl_callback_جوڑو_listener(انکڑے->gles_وٹاندرا_چوکھٹا_callback, &gles_وٹاندرا_چوکھٹا_listener, انکڑے);
        }
    } وإلا {
#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
        إذا (انکڑے->egl_surface) {
            SDL_EGL_DestroySurface(_this, انکڑے->egl_surface);
            انکڑے->egl_surface = EGL_NO_SURFACE;
        }
#جے_انت

        إذا (انکڑے->egl_کھڑکی) {
            WAYLAND_wl_egl_کھڑکی_destroy(انکڑے->egl_کھڑکی);
            انکڑے->egl_کھڑکی = عدم;
        }

        إذا (انکڑے->gles_وٹاندرا_چوکھٹا_callback) {
            wl_callback_destroy(انکڑے->gles_وٹاندرا_چوکھٹا_callback);
            انکڑے->gles_وٹاندرا_چوکھٹا_callback = عدم;
        }

        إذا (انکڑے->gles_وٹاندرا_چوکھٹا_surface_wrapper) {
            WAYLAND_wl_proxy_wrapper_destroy(انکڑے->gles_وٹاندرا_چوکھٹا_surface_wrapper);
            انکڑے->gles_وٹاندرا_چوکھٹا_surface_wrapper = عدم;
        }

        إذا (انکڑے->gles_وٹاندرا_چوکھٹا_event_قطار) {
            WAYLAND_wl_event_قطار_destroy(انکڑے->gles_وٹاندرا_چوکھٹا_event_قطار);
            انکڑے->gles_وٹاندرا_چوکھٹا_event_قطار = عدم;
        }
    }

    أرجع true;
}

bool Wayland_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props)
{
    SDL_کھڑکی_انکڑے *انکڑے;
    SDL_Video_انکڑے *c = _this->اندرونی;
    بنية wl_surface *external_surface = (بنية wl_surface *)SDL_Get_اشارہ_گر_Property(create_props, SDL_PROP_کھڑکی_CREATE_WAYLAND_WL_SURFACE_اشارہ_گر,
                                                                               (بنية wl_surface *)SDL_Get_اشارہ_گر_Property(create_props, "sdl2-compat.external_window", عدم));
    ثابت bool custom_surface_role = (external_surface != عدم) || SDL_GetBooleanProperty(create_props, SDL_PROP_کھڑکی_CREATE_WAYLAND_SURFACE_ROLE_CUSTOM_BOOLEAN, false);
    ثابت bool create_egl_کھڑکی = !!(کھڑکی->flags & SDL_کھڑکی_OPENGL) ||
                                       SDL_GetBooleanProperty(create_props, SDL_PROP_کھڑکی_CREATE_WAYLAND_CREATE_EGL_کھڑکی_BOOLEAN, false);

    انکڑے = SDL_calloc(1, حجم(*انکڑے));
    إذا (!انکڑے) {
        أرجع false;
    }

    کھڑکی->اندرونی = انکڑے;
    انکڑے->enable_insets = SDL_GetBooleanProperty(create_props, SDL_PROP_کھڑکی_CREATE_WAYLAND_ENABLE_INSETS_BOOLEAN, false);

    إذا (کھڑکی->x == SDL_WINDOWPOS_UNDEFINED) {
        کھڑکی->x = 0;
    }
    إذا (کھڑکی->y == SDL_WINDOWPOS_UNDEFINED) {
        کھڑکی->y = 0;
    }

    انکڑے->wayland_انکڑے = c;
    انکڑے->sdlwindow = کھڑکی;

    // Default to all capabilities
    انکڑے->wm_caps = WAYLAND_WM_CAPS_ALL;

    انکڑے->scale_ضارب_2 = 1.0;

    إذا (SDL_کھڑکی_IS_POPUP(کھڑکی)) {
        انکڑے->scale_منزل_display = کھڑکی->ماپا->اندرونی->scale_منزل_display;
        انکڑے->scale_ضارب_2 = کھڑکی->ماپا->اندرونی->scale_ضارب_2;
        EnsurePopupPositionIsValid(کھڑکی, &کھڑکی->x, &کھڑکی->y);
    } وإلا {
        لكل (صحيح i = 0; i < _this->عدد_displays; i++) {
            انکڑے->scale_ضارب_2 = SDL_max(انکڑے->scale_ضارب_2, _this->displays[i]->اندرونی->scale_ضارب_2);
        }
    }

    انکڑے->outputs = عدم;
    انکڑے->عدد_outputs = 0;
    انکڑے->scale_منزل_display = c->scale_منزل_display_enabled;

    // Cache the app_id at creation time, as it may change before the window is mapped.
    انکڑے->app_id = SDL_strdup(SDL_GetAppID());

    إذا (!انکڑے->scale_منزل_display) {
        انکڑے->requested.logical_چوڑائی = کھڑکی->floating.w;
        انکڑے->requested.logical_اچائی = کھڑکی->floating.h;
    } وإلا {
        انکڑے->requested.logical_چوڑائی = Pixel_منزل_نقطہ(کھڑکی, کھڑکی->floating.w);
        انکڑے->requested.logical_اچائی = Pixel_منزل_نقطہ(کھڑکی, کھڑکی->floating.h);
        انکڑے->requested.pixel_چوڑائی = کھڑکی->floating.w;
        انکڑے->requested.pixel_اچائی = کھڑکی->floating.h;
    }

    إذا (!external_surface) {
        انکڑے->surface = wl_compositor_create_surface(c->compositor);
        wl_surface_جوڑو_listener(انکڑے->surface, &surface_listener, انکڑے);
        wl_surface_سیٹ_user_انکڑے(انکڑے->surface, انکڑے);
        SDL_WAYLAND_رجسٹر_surface(انکڑے->surface);
    } وإلا {
        کھڑکی->flags |= SDL_کھڑکی_EXTERNAL;
        انکڑے->surface = external_surface;

        /* External surfaces are registered by being put in a list, as changing tags or userdata
         * can cause problems with external toolkits.
         */
        Wayland_جوڑو_کھڑکی_انکڑے_منزل_External_List(انکڑے);
    }

    /* Always attach a viewport and fractional scale manager if available and the surface is not custom/external,
     * or the custom/external surface was explicitly flagged as high pixel density aware, which signals that the
     * application wants SDL to handle scaling.
     */
    إذا (!custom_surface_role || (کھڑکی->flags & SDL_کھڑکی_بلند_PIXEL_DENSITY)) {
        إذا (c->viewporter) {
            انکڑے->viewport = wp_viewporter_get_viewport(c->viewporter, انکڑے->surface);

            // The viewport always uses the entire buffer.
            wp_viewport_سیٹ_سروت(انکڑے->viewport,
                                   wl_fixed_from_int(-1), wl_fixed_from_int(-1),
                                   wl_fixed_from_int(-1), wl_fixed_from_int(-1));
        }
        إذا (c->fractional_scale_manager) {
            انکڑے->fractional_scale = wp_fractional_scale_manager_v1_get_fractional_scale(c->fractional_scale_manager, انکڑے->surface);
            wp_fractional_scale_v1_جوڑو_listener(انکڑے->fractional_scale, &fractional_scale_listener, انکڑے);
        }
    }

    إذا (!custom_surface_role) {
        إذا (c->wp_color_manager_v1) {
            انکڑے->wp_color_management_surface_feedback = wp_color_manager_v1_get_surface_feedback(c->wp_color_manager_v1, انکڑے->surface);
            wp_color_management_surface_feedback_v1_جوڑو_listener(انکڑے->wp_color_management_surface_feedback, &color_management_surface_feedback_listener, انکڑے);
            Wayland_Get_Color_Info_For_کھڑکی(انکڑے, true);
        } وإلا إذا (c->frog_color_management_factory_v1) {
            انکڑے->frog_color_managed_surface = frog_color_management_factory_v1_get_color_managed_surface(c->frog_color_management_factory_v1, انکڑے->surface);
            frog_color_managed_surface_جوڑو_listener(انکڑے->frog_color_managed_surface, &frog_surface_listener, انکڑے);
        }

        إذا (c->wp_alpha_modifier_v1) {
            انکڑے->wp_alpha_modifier_surface_v1 = wp_alpha_modifier_v1_get_surface(c->wp_alpha_modifier_v1, انکڑے->surface);
            wp_alpha_modifier_surface_v1_سیٹ_multiplier(انکڑے->wp_alpha_modifier_surface_v1, SDL_MAX_UINT32);
        }
    }

    // Must be called before EGL configuration to set the drawable backbuffer size.
    Configure_کھڑکی_Geometry(کھڑکی);

    /* Fire a callback when the compositor wants a new frame rendered.
     * Right now this only matters for OpenGL; we use this callback to add a
     * wait timeout that avoids getting deadlocked by the compositor when the
     * window isn't visible.
     */
    إذا (کھڑکی->flags & SDL_کھڑکی_OPENGL) {
        انکڑے->gles_وٹاندرا_چوکھٹا_event_قطار = WAYLAND_wl_display_create_قطار(انکڑے->wayland_انکڑے->display);
        انکڑے->gles_وٹاندرا_چوکھٹا_surface_wrapper = WAYLAND_wl_proxy_create_wrapper(انکڑے->surface);
        WAYLAND_wl_proxy_سیٹ_قطار((بنية wl_proxy *)انکڑے->gles_وٹاندرا_چوکھٹا_surface_wrapper, انکڑے->gles_وٹاندرا_چوکھٹا_event_قطار);
        انکڑے->gles_وٹاندرا_چوکھٹا_callback = wl_surface_چوکھٹا(انکڑے->gles_وٹاندرا_چوکھٹا_surface_wrapper);
        wl_callback_جوڑو_listener(انکڑے->gles_وٹاندرا_چوکھٹا_callback, &gles_وٹاندرا_چوکھٹا_listener, انکڑے);
    }

    إذا (کھڑکی->flags & SDL_کھڑکی_TRANSPARENT) {
        إذا (_this->gl_config.alpha_ناپ == 0) {
            _this->gl_config.alpha_ناپ = 8;
        }
    }

    إذا (create_egl_کھڑکی) {
        انکڑے->egl_کھڑکی = WAYLAND_wl_egl_کھڑکی_create(انکڑے->surface, انکڑے->current.pixel_چوڑائی, انکڑے->current.pixel_اچائی);
    }

#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    إذا (کھڑکی->flags & SDL_کھڑکی_OPENGL) {
        // Create the GLES window surface
        انکڑے->egl_surface = SDL_EGL_CreateSurface(_this, کھڑکی, (Native_کھڑکی_Type)انکڑے->egl_کھڑکی);

        إذا (انکڑے->egl_surface == EGL_NO_SURFACE) {
            أرجع false; // SDL_EGL_CreateSurface should have set error
        }
    }
#جے_انت

    // We may need to create an idle inhibitor for this new window
    Wayland_SuspendScreenSaver(_this);

    إذا (!custom_surface_role) {
#جے_تعریف_شدہ HAVE_LIBDECOR_H
        إذا (c->shell.libdecor && !SDL_کھڑکی_IS_POPUP(کھڑکی)) {
            انکڑے->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR;
        } وإلا
#جے_انت
            إذا (c->shell.xdg) {
            إذا (SDL_کھڑکی_IS_POPUP(کھڑکی)) {
                انکڑے->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP;
            } وإلا {
                انکڑے->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL;
            }
        } // All other cases will be WAYLAND_SURFACE_UNKNOWN
    } وإلا {
        // Roleless and external surfaces are always considered to be in the shown state by the backend.
        انکڑے->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_CUSTOM;
        انکڑے->shell_surface_حالت = WAYLAND_SHELL_SURFACE_حالت_SHOWN;

        // External windows are presumed to be shown.
        إذا (کھڑکی->flags & SDL_کھڑکی_EXTERNAL) {
            کھڑکی->flags &= ~SDL_کھڑکی_HIDDEN;
        }
    }

    إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_DOUBLE_بفر, false)) {
        انکڑے->double_بفر = true;
    }

    SDL_PropertiesID props = SDL_Get_کھڑکی_Properties(کھڑکی);
    SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WAYLAND_DISPLAY_اشارہ_گر, انکڑے->wayland_انکڑے->display);
    SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WAYLAND_SURFACE_اشارہ_گر, انکڑے->surface);
    SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WAYLAND_VIEWPORT_اشارہ_گر, انکڑے->viewport);
    SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_WAYLAND_EGL_کھڑکی_اشارہ_گر, انکڑے->egl_کھڑکی);
    إذا (انکڑے->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL || انکڑے->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ثابت حرف *کھڑکی_id = SDL_GetStringProperty(create_props, SDL_PROP_کھڑکی_CREATE_WAYLAND_کھڑکی_ID_STRING, عدم);
        إذا (کھڑکی_id && *کھڑکی_id != '\0') {
            SDL_سیٹ_String_Property(props, SDL_PROP_کھڑکی_WAYLAND_کھڑکی_ID_STRING, کھڑکی_id);
        }
    }

    انکڑے->کامیابی_test_نتیجہ = SDL_HITTEST_عام;

    أرجع true;
}

فراغ Wayland_سیٹ_کھڑکی_Minimum_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    کھڑکی->اندرونی->limits_بدلیا = true;
}

فراغ Wayland_سیٹ_کھڑکی_ودھ_توں_ودھ_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    کھڑکی->اندرونی->limits_بدلیا = true;
}

فراغ Wayland_سیٹ_کھڑکی_Aspect_تناسب(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    کھڑکی->اندرونی->limits_بدلیا = true;
}

bool Wayland_سیٹ_کھڑکی_Position(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *wind = کھڑکی->اندرونی;

    // Only popup windows can be positioned relative to the parent.
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        إذا (wind->shell_surface.xdg.popup.xdg_popup &&
            xdg_popup_get_نسخہ(wind->shell_surface.xdg.popup.xdg_popup) < XDG_POPUP_REPOSITION_SINCE_نسخہ) {
            أرجع SDL_Unsupported();
        }

        RepositionPopup(کھڑکی, false);
        أرجع true;
    } وإلا إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR || wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        /* Catch up on any pending state before attempting to change the fullscreen window
         * display via a set fullscreen call to make sure the window doesn't have a pending
         * leave fullscreen event that it might override.
         */
        FlushPendingEvents(کھڑکی);

        إذا (wind->is_fullscreen) {
            SDL_VideoDisplay *display = SDL_Get_Video_Display_For_Fullscreen_کھڑکی(کھڑکی);
            إذا (display && wind->آخری_display_ID != display->id) {
                بنية wl_output *output = display->اندرونی->output;
                سیٹ_Fullscreen(کھڑکی, output, true);

                أرجع true;
            }
        }
    }
    أرجع SDL_سیٹ_Error("wayland cannot position non-popup windows");
}

فراغ Wayland_سیٹ_کھڑکی_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *wind = کھڑکی->اندرونی;

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
    إذا (resizable_state || (کھڑکی->tiled && !wind->limits_بدلیا) ||
        wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {

        // Don't change the window size if maximized and tiled.
        إذا (!maximized) {
            إذا (!wind->scale_منزل_display) {
                wind->requested.logical_چوڑائی = کھڑکی->pending.w;
                wind->requested.logical_اچائی = کھڑکی->pending.h;
            } وإلا {
                wind->requested.logical_چوڑائی = Pixel_منزل_نقطہ(کھڑکی, کھڑکی->pending.w);
                wind->requested.logical_اچائی = Pixel_منزل_نقطہ(کھڑکی, کھڑکی->pending.h);
                wind->requested.pixel_چوڑائی = کھڑکی->pending.w;
                wind->requested.pixel_اچائی = کھڑکی->pending.h;
            }
        }

        /* If a non-resizable window somehow wound up in the tiled state, store the new
         * size in the floating parameters so the size will be preserved for future
         * configure events.
         *
         * This shouldn't happen, but apparently it can on at least one compositor...
         */
        إذا (کھڑکی->tiled && !(کھڑکی->flags & SDL_کھڑکی_RESIZABLE)) {
            کھڑکی->floating.w = کھڑکی->pending.w;
            کھڑکی->floating.h = کھڑکی->pending.h;
        }
    } وإلا {
        // Can't resize the window.
        کھڑکی->آخری_ناپ_pending = false;
    }

    wind->limits_بدلیا = false;
    إذا (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_SHOWN) {
        wind->pending_state_commit = true;
    }

    // Always recalculate the geometry, as this may be in response to a min/max limit change.
    Configure_کھڑکی_Geometry(کھڑکی);
    Commit_Libdecor_چوکھٹا(کھڑکی);
}

فراغ Wayland_Get_کھڑکی_ناپ_وچ_Pixels(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحيح *w, صحيح *h)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;

    *w = انکڑے->current.pixel_چوڑائی;
    *h = انکڑے->current.pixel_اچائی;
}

عائم Wayland_Get_کھڑکی_Content_Scale(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *wind = کھڑکی->اندرونی;

    إذا (کھڑکی->flags & SDL_کھڑکی_بلند_PIXEL_DENSITY || wind->scale_منزل_display || wind->fullscreen_exclusive) {
        أرجع (عائم)wind->scale_ضارب_2;
    }

    أرجع 1.0f;
}

SDL_DisplayID Wayland_Get_Display_For_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *wind = کھڑکی->اندرونی;

    إذا (wind) {
        أرجع wind->آخری_display_ID;
    }

    أرجع 0;
}

bool Wayland_سیٹ_کھڑکی_Opacity(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, عائم opacity)
{
    SDL_کھڑکی_انکڑے *wind = کھڑکی->اندرونی;

    إذا (wind->wp_alpha_modifier_surface_v1) {
        ثابت bool is_opaque = !(کھڑکی->flags & SDL_کھڑکی_TRANSPARENT) && opacity == 1.0f;

        إذا (wind->نقاب.mapped && wind->نقاب.opaque != is_opaque) {
            بنية wl_بفر *old_بفر = wind->نقاب.بفر_2;
            wind->نقاب.opaque = is_opaque;
            wind->نقاب.بفر_2 = Wayland_Create_Single_Pixel_بفر(0, 0, 0, is_opaque ? SDL_MAX_UINT32 : 0);

            wl_surface_attach(wind->نقاب.surface, wind->نقاب.بفر_2, 0, 0);
            إذا (wl_surface_get_نسخہ(wind->نقاب.surface) >= WL_SURFACE_DAMAGE_بفر_SINCE_نسخہ) {
                wl_surface_damage_بفر(wind->نقاب.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
            } وإلا {
                wl_surface_damage(wind->نقاب.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
            }

            إذا (is_opaque) {
                سیٹ_Surface_Opaque_Region(wind->نقاب.surface, wind->current.logical_چوڑائی, wind->current.logical_اچائی);
            } وإلا {
                سیٹ_Surface_Opaque_Region(wind->نقاب.surface, 0, 0);
            }

            wl_surface_commit(wind->نقاب.surface);

            إذا (old_بفر) {
                wl_بفر_destroy(old_بفر);
            }
        }

        إذا (is_opaque) {
            سیٹ_Surface_Opaque_Region(wind->surface, wind->current.viewport_چوڑائی, wind->current.viewport_اچائی);
        } وإلا {
            سیٹ_Surface_Opaque_Region(wind->surface, 0, 0);
        }

        wp_alpha_modifier_surface_v1_سیٹ_multiplier(wind->wp_alpha_modifier_surface_v1, (Uint32)((مزدوج)SDL_MAX_UINT32 * (مزدوج)opacity));

        أرجع true;
    }

    أرجع SDL_سیٹ_Error("wayland: set window opacity failed; compositor lacks support for the required wp_alpha_modifier_v1 protocol");
}

فراغ Wayland_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *wind = کھڑکی->اندرونی;
    ثابت حرف *title = کھڑکی->title ? کھڑکی->title : "";

#جے_تعریف_شدہ HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.چوکھٹا) {
        libdecor_چوکھٹا_سیٹ_title(wind->shell_surface.libdecor.چوکھٹا, title);
    } وإلا
#جے_انت
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
        xdg_toplevel_سیٹ_title(wind->shell_surface.xdg.toplevel.xdg_toplevel, title);
    }
}

ساكن صحيح icon_ترتیب_دیو_callback(ثابت فراغ *a, ثابت فراغ *b)
{
    ثابت SDL_Surface *s1 = *(ثابت SDL_Surface **)a;
    ثابت SDL_Surface *s2 = *(ثابت SDL_Surface **)b;

    أرجع (s1->w * s1->h) <= (s2->w * s2->h) ? -1 : 1;
}

bool Wayland_سیٹ_کھڑکی_Icon(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_Surface *icon)
{
    SDL_کھڑکی_انکڑے *wind = کھڑکی->اندرونی;
    Wayland_SHMPool *shm_pool = عدم;
    بنية xdg_toplevel *toplevel = عدم;

    إذا (!_this->اندرونی->xdg_toplevel_icon_manager_v1) {
        أرجع SDL_سیٹ_Error("wayland: cannot set icon; required xdg_toplevel_icon_v1 protocol not supported");
    }

    صحيح image_گنتی_2 = 0;
    SDL_Surface **images = SDL_GetSurfaceImages(icon, &image_گنتی_2);
    إذا (!images || !image_گنتی_2) {
        أرجع false;
    }

    // Release the old icon resources.
    إذا (wind->xdg_toplevel_icon_v1) {
        xdg_toplevel_icon_v1_destroy(wind->xdg_toplevel_icon_v1);
        wind->xdg_toplevel_icon_v1 = عدم;
    }

    لكل (صحيح i = 0; i < wind->icon_بفر_گنتی; ++i) {
        wl_بفر_destroy(wind->icon_buffers[i]);
    }
    wind->icon_بفر_گنتی = 0;

    wind->xdg_toplevel_icon_v1 = xdg_toplevel_icon_manager_v1_create_icon(_this->اندرونی->xdg_toplevel_icon_manager_v1);
    wind->icon_buffers = SDL_realloc(wind->icon_buffers, image_گنتی_2 * حجم(بنية wl_بفر *));
    إذا (!wind->icon_buffers) {
        اذهب failure_cleanup;
    }

    // Calculate the size of the buffer pool.
    size_t pool_ناپ = 0;
    لكل (صحيح i = 0; i < image_گنتی_2; ++i) {
        // Images must be square. Non-square images will be centered.
        ثابت صحيح ناپ = SDL_max(images[i]->w, images[i]->h);
        pool_ناپ += ناپ * ناپ * 4;
    }

    // Sort the images in ascending order by size.
    SDL_qsort(images, image_گنتی_2, حجم(SDL_Surface *), icon_ترتیب_دیو_callback);

    shm_pool = Wayland_AllocSHMPool(pool_ناپ);
    إذا (!shm_pool) {
        SDL_سیٹ_Error("wayland: failed to allocate an SHM pool for the icon");
        اذهب failure_cleanup;
    }

    ثابت مزدوج ادھار_ناپ = (مزدوج)SDL_max(icon->w, icon->h);
    لكل (صحيح i = 0; i < image_گنتی_2; ++i) {
        SDL_Surface *surface = images[i];

        // Choose the largest image for each integer scale, ignoring any below the base size.
        ثابت صحيح level_ناپ = SDL_max(surface->w, surface->h);
        ثابت صحيح scale = (صحيح)SDL_floor((مزدوج)level_ناپ / ادھار_ناپ);
        إذا (!scale) {
            استمر;
        }

        إذا (surface->format != SDL_PIXELFORMAT_ARGB8888) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
            إذا (!surface) {
                SDL_سیٹ_Error("wayland: failed to convert the icon image to ARGB8888 format");
                اذهب failure_cleanup;
            }
        }

        فراغ *بفر_mem;
        بنية wl_بفر *بفر_2 = Wayland_Alloc_بفر_From_Pool(shm_pool, level_ناپ, level_ناپ, &بفر_mem);
        إذا (!بفر_2) {
            // Clean up the temporary conversion surface.
            إذا (surface != images[i]) {
                SDL_DestroySurface(surface);
            }
            SDL_سیٹ_Error("wayland: failed to allocate a wl_buffer for the icon");
            اذهب failure_cleanup;
        }

        wind->icon_buffers[wind->icon_بفر_گنتی++] = بفر_2;

        // Center non-square images.
        إذا (surface->w < level_ناپ) {
            SDL_memset(بفر_mem, 0, level_ناپ * level_ناپ * 4);
            بفر_mem = (Uint8 *)بفر_mem + (((level_ناپ - surface->w) / 2) * 4);
        } وإلا إذا (surface->h < level_ناپ) {
            SDL_memset(بفر_mem, 0, level_ناپ * level_ناپ * 4);
            بفر_mem = (Uint8 *)بفر_mem + (((level_ناپ - surface->h) / 2) * (level_ناپ * 4));
        }

        SDL_PremultiplyAlpha(surface->w, surface->h, surface->format, surface->pixels, surface->pitch,
                             SDL_PIXELFORMAT_ARGB8888, بفر_mem, level_ناپ * 4, true);

        xdg_toplevel_icon_v1_جوڑو_بفر(wind->xdg_toplevel_icon_v1, بفر_2, scale);

        // Clean up the temporary scaled or conversion surface.
        إذا (surface != images[i]) {
            SDL_DestroySurface(surface);
        }
    }

#جے_تعریف_شدہ HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.چوکھٹا) {
        toplevel = libdecor_چوکھٹا_get_xdg_toplevel(wind->shell_surface.libdecor.چوکھٹا);
    } وإلا
#جے_انت
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
        toplevel = wind->shell_surface.xdg.toplevel.xdg_toplevel;
    }

    إذا (toplevel) {
        xdg_toplevel_icon_manager_v1_سیٹ_icon(_this->اندرونی->xdg_toplevel_icon_manager_v1, toplevel, wind->xdg_toplevel_icon_v1);
    }

    Wayland_ReleaseSHMPool(shm_pool);
    SDL_free(images);

    أرجع true;

failure_cleanup:

    SDL_free(images);

    إذا (wind->xdg_toplevel_icon_v1) {
        xdg_toplevel_icon_v1_destroy(wind->xdg_toplevel_icon_v1);
        wind->xdg_toplevel_icon_v1 = عدم;
    }

    Wayland_ReleaseSHMPool(shm_pool);

    لكل (صحيح i = 0; i < wind->icon_بفر_گنتی; ++i) {
        wl_بفر_destroy(wind->icon_buffers[i]);
    }
    SDL_free(wind->icon_buffers);
    wind->icon_buffers = عدم;
    wind->icon_بفر_گنتی = 0;

    أرجع false;
}

فراغ *Wayland_Get_کھڑکی_ICCProfile(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, size_t *ناپ)
{
    SDL_کھڑکی_انکڑے *wind = کھڑکی->اندرونی;
    فراغ *ret = عدم;

    إذا (wind->icc_ناپ > 0) {
        فراغ *icc_map = mmap(عدم, wind->icc_ناپ, PROT_READ, MAP_PRIVATE, wind->icc_fd, 0);
        إذا (icc_map != MAP_FAILED) {
            ret = SDL_malloc(wind->icc_ناپ);
            إذا (ret) {
                *ناپ = wind->icc_ناپ;
                SDL_memcpy(ret, icc_map, *ناپ);
            }
            munmap(icc_map, wind->icc_ناپ);
        }
    }

    أرجع ret;
}

bool Wayland_Sync_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *wind = کھڑکی->اندرونی;

    افعل {
        WAYLAND_wl_display_roundtrip(_this->اندرونی->display);
    } طالما (wind->pending_state_deadline_گنتی);

    أرجع true;
}

فراغ Wayland_AcceptDragAndDrop(SDL_کھڑکی *کھڑکی, bool accept)
{
    کھڑکی->اندرونی->مندا_drag_and_drop = accept;
}

bool Wayland_سیٹ_کھڑکی_Focusable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool focusable)
{
    إذا (کھڑکی->flags & SDL_کھڑکی_POPUP_MENU) {
        إذا (!(کھڑکی->flags & SDL_کھڑکی_HIDDEN)) {
            إذا (!focusable && (کھڑکی->flags & SDL_کھڑکی_داخلہ_FOCUS)) {
                SDL_کھڑکی *new_focus;
                ثابت bool سیٹ_focus = SDL_ShouldRelinquishPopupFocus(کھڑکی, &new_focus);
                Wayland_سیٹ_Keyboard_Focus(new_focus, سیٹ_focus);
            } وإلا إذا (focusable) {
                إذا (SDL_ShouldFocusPopup(کھڑکی)) {
                    Wayland_سیٹ_Keyboard_Focus(کھڑکی, true);
                }
            }
        }

        أرجع true;
    }

    أرجع SDL_سیٹ_Error("wayland: focus can only be toggled on popup menu windows");
}

فراغ Wayland_Show_کھڑکی_System_Menu(SDL_کھڑکی *کھڑکی, صحيح x, صحيح y)
{
    SDL_کھڑکی_انکڑے *wind = کھڑکی->اندرونی;
    SDL_WaylandSeat *seat = wind->wayland_انکڑے->آخری_implicit_grab_seat;

    إذا (!seat) {
        أرجع;
    }

    إذا (wind->scale_منزل_display) {
        x = Pixel_منزل_نقطہ(کھڑکی, x);
        y = Pixel_منزل_نقطہ(کھڑکی, y);
    }

#جے_تعریف_شدہ HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (wind->shell_surface.libdecor.چوکھٹا) {
            libdecor_چوکھٹا_show_کھڑکی_menu(wind->shell_surface.libdecor.چوکھٹا, seat->wl_seat, seat->آخری_implicit_grab_serial, x, y);
        }
    } وإلا
#جے_انت
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        إذا (wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            xdg_toplevel_show_کھڑکی_menu(wind->shell_surface.xdg.toplevel.xdg_toplevel, seat->wl_seat, seat->آخری_implicit_grab_serial, x, y);
        }
    }
}

bool Wayland_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;

#جے_تعریف_شدہ SDL_USE_LIBDBUS
    إذا (SDL_DBus_ScreensaverInhibit(_this->suspend_screensaver)) {
        أرجع true;
    }
#جے_انت

    /* The idle_inhibit_unstable_v1 protocol suspends the screensaver
       on a per wl_surface basis, but SDL assumes that suspending
       the screensaver can be done independently of any window.

       To reconcile these differences, we propagate the idle inhibit
       state to each window. If there is no window active, we will
       be able to inhibit idle once the first window is created.
    */
    إذا (انکڑے->idle_inhibit_manager) {
        SDL_کھڑکی *کھڑکی = _this->windows;
        طالما (کھڑکی) {
            SDL_کھڑکی_انکڑے *win_انکڑے = کھڑکی->اندرونی;

            إذا (_this->suspend_screensaver && !win_انکڑے->idle_inhibitor) {
                win_انکڑے->idle_inhibitor =
                    zwp_idle_inhibit_manager_v1_create_inhibitor(انکڑے->idle_inhibit_manager,
                                                                 win_انکڑے->surface);
            } وإلا إذا (!_this->suspend_screensaver && win_انکڑے->idle_inhibitor) {
                zwp_idle_inhibitor_v1_destroy(win_انکڑے->idle_inhibitor);
                win_انکڑے->idle_inhibitor = عدم;
            }

            کھڑکی = کھڑکی->اگلا;
        }
    }

    أرجع true;
}

فراغ Wayland_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;
    SDL_کھڑکی_انکڑے *wind = کھڑکی->اندرونی;

    إذا (انکڑے && wind) {
        /* Roundtrip before destroying the window to make sure that it has received input leave events, so that
         * no internal structures are left pointing to the destroyed window.
         */
        إذا (wind->show_hide_sync_required) {
            /* Make sure hit test isn't executed during roundtrip */
            کھڑکی->کامیابی_test = عدم;
            WAYLAND_wl_display_roundtrip(انکڑے->display);
        }

        /* The compositor should have relinquished keyboard, pointer, touch, and tablet tool focus when the toplevel
         * window was destroyed upon being hidden, but there is no guarantee of this, so ensure that all references
         * to the window held by seats are released before destroying the underlying surface and struct.
         */
        Wayland_Display_Remove_کھڑکی_References_From_Seats(انکڑے, wind);

        إذا (wind->نقاب.viewport) {
            wp_viewport_destroy(wind->نقاب.viewport);
        }
        إذا (wind->نقاب.بفر_2) {
            wl_بفر_destroy(wind->نقاب.بفر_2);
        }
        إذا (wind->نقاب.subsurface) {
            wl_subsurface_destroy(wind->نقاب.subsurface);
        }
        إذا (wind->نقاب.surface) {
            wl_surface_destroy(wind->نقاب.surface);
        }
#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
        إذا (wind->egl_surface) {
            SDL_EGL_DestroySurface(_this, wind->egl_surface);
        }
#جے_انت
        إذا (wind->egl_کھڑکی) {
            WAYLAND_wl_egl_کھڑکی_destroy(wind->egl_کھڑکی);
        }

        إذا (wind->idle_inhibitor) {
            zwp_idle_inhibitor_v1_destroy(wind->idle_inhibitor);
        }

        إذا (wind->activation_token) {
            xdg_activation_token_v1_destroy(wind->activation_token);
        }

        إذا (wind->viewport) {
            wp_viewport_destroy(wind->viewport);
        }

        إذا (wind->fractional_scale) {
            wp_fractional_scale_v1_destroy(wind->fractional_scale);
        }

        إذا (wind->wp_alpha_modifier_surface_v1) {
            wp_alpha_modifier_surface_v1_destroy(wind->wp_alpha_modifier_surface_v1);
        }

        إذا (wind->frog_color_managed_surface) {
            frog_color_managed_surface_destroy(wind->frog_color_managed_surface);
        }

        إذا (wind->wp_color_management_surface_feedback) {
            Wayland_FreeColorInfoState(wind->color_info_state);
            wp_color_management_surface_feedback_v1_destroy(wind->wp_color_management_surface_feedback);
        }

        SDL_free(wind->outputs);
        SDL_free(wind->app_id);

        إذا (wind->gles_وٹاندرا_چوکھٹا_callback) {
            wl_callback_destroy(wind->gles_وٹاندرا_چوکھٹا_callback);
            WAYLAND_wl_proxy_wrapper_destroy(wind->gles_وٹاندرا_چوکھٹا_surface_wrapper);
            WAYLAND_wl_event_قطار_destroy(wind->gles_وٹاندرا_چوکھٹا_event_قطار);
        }

        إذا (!(کھڑکی->flags & SDL_کھڑکی_EXTERNAL)) {
            wl_surface_destroy(wind->surface);
        } وإلا {
            Wayland_Remove_کھڑکی_انکڑے_From_External_List(wind);
        }

        إذا (wind->xdg_toplevel_icon_v1) {
            xdg_toplevel_icon_v1_destroy(wind->xdg_toplevel_icon_v1);
        }

        لكل (صحيح i = 0; i < wind->icon_بفر_گنتی; ++i) {
            wl_بفر_destroy(wind->icon_buffers[i]);
        }
        SDL_free(wind->icon_buffers);
        wind->icon_بفر_گنتی = 0;

        SDL_free(wind);
    }
    کھڑکی->اندرونی = عدم;
}

#جے_انت // SDL_VIDEO_DRIVER_WAYLAND
