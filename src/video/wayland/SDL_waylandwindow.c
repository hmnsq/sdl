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

#که_تعریف_شوی SDL_VIDEO_DRIVER_WAYLAND

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

#که_تعریف_شوی HAVE_LIBDECOR_H
#ضمن <libdecor.h>
#د_که_پای

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
ساكن bool Should_ماسک_Fullscreen()
{
    ساكن صحيح ماسک_required = -1;

    إذا (ماسک_required >= 0) {
        أرجع ماسک_required != 0;
    }

    ثابت حرف *desktop = SDL_getenv("XDG_CURRENT_DESKTOP");
    إذا (desktop && SDL_strstr(desktop, "KDE") != عدم) {
        ماسک_required = 1;
    } وإلا {
        ماسک_required = 0;
    }

    أرجع ماسک_required != 0;
}

ساكن مزدوج Get_کړکۍ_Scale(SDL_کړکۍ *کړکۍ)
{
    أرجع (کړکۍ->flags & SDL_کړکۍ_لوړ_PIXEL_DENSITY) || کړکۍ->دننی->scale_منزل_display ? کړکۍ->دننی->scale_ضریب_2 : 1.0;
}

// These are point->pixel->point round trip safe; the inverse is not round trip safe due to rounding.
ساكن صحيح ټکی_منزل_Pixel(SDL_کړکۍ *کړکۍ, صحيح ټکی)
{
    /* Rounds halfway away from zero as per the Wayland fractional scaling protocol spec.
     * Wayland scale units are in units of 1/120, so the offset is required to correct for
     * rounding errors when using certain scale values.
     */
    أرجع ټکی ? SDL_max((صحيح)SDL_lround((مزدوج)ټکی * Get_کړکۍ_Scale(کړکۍ) + 1e-6), 1) : 0;
}

ساكن صحيح Pixel_منزل_ټکی(SDL_کړکۍ *کړکۍ, صحيح pixel)
{
    أرجع pixel ? SDL_max((صحيح)SDL_lround((مزدوج)pixel / Get_کړکۍ_Scale(کړکۍ)), 1) : 0;
}

تعداد Wayland_ډېرپېښ_Scale
{
    WAYLAND_ډېرپېښ_SCALE_UNDEFINED,
    WAYLAND_ډېرپېښ_SCALE_ASPECT,
    WAYLAND_ډېرپېښ_SCALE_STRETCH,
    WAYLAND_ډېرپېښ_SCALE_NONE
};

ساكن تعداد Wayland_ډېرپېښ_Scale Get_ډېرپېښ_Scale_لاره(فراغ)
{
    ساكن تعداد Wayland_ډېرپېښ_Scale scale_ډېرپېښ_2 = WAYLAND_ډېرپېښ_SCALE_UNDEFINED;

    إذا (scale_ډېرپېښ_2 == WAYLAND_ډېرپېښ_SCALE_UNDEFINED) {
        ثابت حرف *scale_hint = SDL_GetHint(SDL_HINT_VIDEO_WAYLAND_ډېرپېښ_SCALING);

        إذا (scale_hint) {
            إذا (!SDL_strcasecmp(scale_hint, "stretch")) {
                scale_ډېرپېښ_2 = WAYLAND_ډېرپېښ_SCALE_STRETCH;
            } وإلا إذا (!SDL_strcasecmp(scale_hint, "none")) {
                scale_ډېرپېښ_2 = WAYLAND_ډېرپېښ_SCALE_NONE;
            } وإلا {
                scale_ډېرپېښ_2 = WAYLAND_ډېرپېښ_SCALE_ASPECT;
            }
        } وإلا {
            scale_ډېرپېښ_2 = WAYLAND_ډېرپېښ_SCALE_ASPECT;
        }
    }

    أرجع scale_ډېرپېښ_2;
}

تعريفنوع بنية BorderInsets
{
    صحيح کیڼ;
    صحيح سر;
    صحيح ښی;
    صحيح bottom;
} BorderInsets;

// The border insets from the window properties; they only apply to xdg-toplevel windows.
ساكن فراغ GetBorderInsets(SDL_کړکۍ *کړکۍ, BorderInsets *insets)
{
    SDL_zerop(insets);
    إذا (!کړکۍ->دننی->enable_insets) {
        أرجع;
    }
    إذا (کړکۍ->دننی->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        ثابت SDL_PropertiesID props = SDL_Get_کړکۍ_Properties(کړکۍ);
        insets->کیڼ = (صحيح)SDL_clamp(SDL_Get_شمېره_Property(props, SDL_PROP_کړکۍ_WAYLAND_BORDER_INSET_کیڼ_شمېره, 0), 0, SDL_MAX_SINT16);
        insets->سر = (صحيح)SDL_clamp(SDL_Get_شمېره_Property(props, SDL_PROP_کړکۍ_WAYLAND_BORDER_INSET_سر_شمېره, 0), 0, SDL_MAX_SINT16);
        insets->ښی = (صحيح)SDL_clamp(SDL_Get_شمېره_Property(props, SDL_PROP_کړکۍ_WAYLAND_BORDER_INSET_ښی_شمېره, 0), 0, SDL_MAX_SINT16);
        insets->bottom = (صحيح)SDL_clamp(SDL_Get_شمېره_Property(props, SDL_PROP_کړکۍ_WAYLAND_BORDER_INSET_BOTTOM_شمېره, 0), 0, SDL_MAX_SINT16);
    }
}

ساكن فراغ سېټ_Min_Max_Dimensions(SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *wind = کړکۍ->دننی;
    صحيح min_پلنوالی_2, min_لوړوالی_2, max_پلنوالی_2, max_لوړوالی_2;

    /* Keep the limits off while the window is in a fixed-size state, or the controls
     * to exit that state may be disabled.
     */
    إذا (کړکۍ->flags & (SDL_کړکۍ_FULLSCREEN | SDL_کړکۍ_MAXIMIZED)) {
        min_پلنوالی_2 = 0;
        min_لوړوالی_2 = 0;
        max_پلنوالی_2 = 0;
        max_لوړوالی_2 = 0;
    } وإلا إذا (کړکۍ->flags & SDL_کړکۍ_RESIZABLE) {
        صحيح adj_w = SDL_max(کړکۍ->min_w, wind->system_limits.min_پلنوالی_2);
        صحيح adj_h = SDL_max(کړکۍ->min_h, wind->system_limits.min_لوړوالی_2);
        إذا (wind->scale_منزل_display) {
            adj_w = Pixel_منزل_ټکی(کړکۍ, adj_w);
            adj_h = Pixel_منزل_ټکی(کړکۍ, adj_h);
        }
        min_پلنوالی_2 = adj_w;
        min_لوړوالی_2 = adj_h;

        adj_w = کړکۍ->max_w ? SDL_max(کړکۍ->max_w, wind->system_limits.min_پلنوالی_2) : 0;
        adj_h = کړکۍ->max_h ? SDL_max(کړکۍ->max_h, wind->system_limits.min_لوړوالی_2) : 0;
        إذا (wind->scale_منزل_display) {
            adj_w = Pixel_منزل_ټکی(کړکۍ, adj_w);
            adj_h = Pixel_منزل_ټکی(کړکۍ, adj_h);
        }
        max_پلنوالی_2 = adj_w;
        max_لوړوالی_2 = adj_h;
    } وإلا {
        min_پلنوالی_2 = wind->current.logical_پلنوالی;
        min_لوړوالی_2 = wind->current.logical_لوړوالی;
        max_پلنوالی_2 = wind->current.logical_پلنوالی;
        max_لوړوالی_2 = wind->current.logical_لوړوالی;
    }

#که_تعریف_شوی HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (!wind->shell_surface.libdecor.چوکاټ) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }

        إذا (min_پلنوالی_2 && min_لوړوالی_2 && min_پلنوالی_2 == max_پلنوالی_2 && min_لوړوالی_2 == max_لوړوالی_2) {
            libdecor_چوکاټ_unset_capabilities(wind->shell_surface.libdecor.چوکاټ, LIBDECOR_ACTION_RESIZE);
        } وإلا {
            libdecor_چوکاټ_سېټ_capabilities(wind->shell_surface.libdecor.چوکاټ, LIBDECOR_ACTION_RESIZE);
        }

        /* No need to change these values if the window is non-resizable,
         * as libdecor will just overwrite them internally.
         */
        إذا (libdecor_چوکاټ_has_capability(wind->shell_surface.libdecor.چوکاټ, LIBDECOR_ACTION_RESIZE)) {
            libdecor_چوکاټ_سېټ_min_content_اندازه(wind->shell_surface.libdecor.چوکاټ,
                                                min_پلنوالی_2,
                                                min_لوړوالی_2);
            libdecor_چوکاټ_سېټ_max_content_اندازه(wind->shell_surface.libdecor.چوکاټ,
                                                max_پلنوالی_2,
                                                max_لوړوالی_2);
        }
    } وإلا
#د_که_پای
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        إذا (!wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }
        /* The limits are in window geometry space; keep an existing minimum at 1 or more,
         * or the window can be spuriously closed.
         */
        BorderInsets insets;
        GetBorderInsets(کړکۍ, &insets);
        min_پلنوالی_2 = SDL_max(min_پلنوالی_2 - (insets.کیڼ + insets.ښی), min_پلنوالی_2 ? 1 : 0);
        min_لوړوالی_2 = SDL_max(min_لوړوالی_2 - (insets.سر + insets.bottom), min_لوړوالی_2 ? 1 : 0);
        إذا (max_پلنوالی_2) {
            max_پلنوالی_2 = SDL_max(max_پلنوالی_2 - (insets.کیڼ + insets.ښی), 1);
        }
        إذا (max_لوړوالی_2) {
            max_لوړوالی_2 = SDL_max(max_لوړوالی_2 - (insets.سر + insets.bottom), 1);
        }
        xdg_toplevel_سېټ_min_اندازه(wind->shell_surface.xdg.toplevel.xdg_toplevel,
                                  min_پلنوالی_2,
                                  min_لوړوالی_2);
        xdg_toplevel_سېټ_max_اندازه(wind->shell_surface.xdg.toplevel.xdg_toplevel,
                                  max_پلنوالی_2,
                                  max_لوړوالی_2);
    }
}

ساكن فراغ EnsurePopupPositionIsValid(SDL_کړکۍ *کړکۍ, صحيح *x, صحيح *y)
{
    صحيح adj_شمېر = 0;

    /* Per the xdg-positioner spec, child popup windows must intersect or at
     * least be partially adjoining the parent window.
     *
     * Failure to ensure this on a compositor that enforces this restriction
     * can result in behavior ranging from the window being spuriously closed
     * to a protocol violation.
     */
    إذا (*x + کړکۍ->w <= 0) {
        *x = -کړکۍ->w;
        ++adj_شمېر;
    }
    إذا (*y + کړکۍ->h <= 0) {
        *y = -کړکۍ->h;
        ++adj_شمېر;
    }
    إذا (*x >= کړکۍ->پلار->w) {
        *x = کړکۍ->پلار->w;
        ++adj_شمېر;
    }
    إذا (*y >= کړکۍ->پلار->h) {
        *y = کړکۍ->پلار->h;
        ++adj_شمېر;
    }

    /* If adjustment was required on the x and y axes, the popup is aligned with
     * the parent corner-to-corner and is neither overlapping nor adjoining, so it
     * must be nudged by 1 to be considered adjoining.
     */
    إذا (adj_شمېر > 1) {
        *x += *x < 0 ? 1 : -1;
    }
}

// The window geometry: the explicitly set one, or the full surface if SDL has never set it.
ساكن فراغ Get_کړکۍ_Geometry(SDL_کړکۍ_معلومات *wind, SDL_Rect *geometry)
{
    *geometry = wind->explicit_geometry;
    إذا (SDL_Rect_تشه(geometry)) {
        geometry->x = 0;
        geometry->y = 0;
        geometry->w = wind->current.logical_پلنوالی;
        geometry->h = wind->current.logical_لوړوالی;
    }
}

ساكن فراغ Adjust_Popup_دننه_واټن(SDL_کړکۍ *popup, صحيح *x, صحيح *y)
{
    // Positioner offsets are relative to the origin of the parent's window geometry.
#که_تعریف_شوی HAVE_LIBDECOR_H
    إذا (popup->پلار->دننی->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        صحيح adj_x, adj_y;
        libdecor_چوکاټ_translate_coordinate(popup->پلار->دننی->shell_surface.libdecor.چوکاټ,
                                            *x, *y, &adj_x, &adj_y);
        *x = adj_x;
        *y = adj_y;
    } وإلا
#د_که_پای
    {
        *x -= popup->پلار->دننی->explicit_geometry.x;
        *y -= popup->پلار->دننی->explicit_geometry.y;
    }
}

ساكن فراغ RepositionPopup(SDL_کړکۍ *کړکۍ, bool use_current_position)
{
    SDL_کړکۍ_معلومات *wind = کړکۍ->دننی;

    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP &&
        wind->shell_surface.xdg.popup.xdg_positioner &&
        xdg_popup_get_نسخه(wind->shell_surface.xdg.popup.xdg_popup) >= XDG_POPUP_REPOSITION_SINCE_نسخه) {
        صحيح x = use_current_position ? کړکۍ->x : کړکۍ->pending.x;
        صحيح y = use_current_position ? کړکۍ->y : کړکۍ->pending.y;

        EnsurePopupPositionIsValid(کړکۍ, &x, &y);
        إذا (wind->scale_منزل_display) {
            x = Pixel_منزل_ټکی(کړکۍ->پلار, x);
            y = Pixel_منزل_ټکی(کړکۍ->پلار, y);
        }
        Adjust_Popup_دننه_واټن(کړکۍ, &x, &y);
        SDL_Rect پلار_geometry;
        Get_کړکۍ_Geometry(کړکۍ->پلار->دننی, &پلار_geometry);
        xdg_positioner_سېټ_anchor_rect(wind->shell_surface.xdg.popup.xdg_positioner, 0, 0, پلار_geometry.w, پلار_geometry.h);
        xdg_positioner_سېټ_اندازه(wind->shell_surface.xdg.popup.xdg_positioner, wind->current.logical_پلنوالی, wind->current.logical_لوړوالی);
        xdg_positioner_سېټ_دننه_واټن(wind->shell_surface.xdg.popup.xdg_positioner, x, y);
        xdg_popup_reposition(wind->shell_surface.xdg.popup.xdg_popup,
                             wind->shell_surface.xdg.popup.xdg_positioner,
                             0);
    }
}

ساكن فراغ سېټ_Surface_Opaque_Region(بنية wl_surface *surface, صحيح پلنوالی, صحيح لوړوالی)
{
    SDL_Video_معلومات *viddata = SDL_GetVideoDevice()->دننی;

    إذا (پلنوالی && لوړوالی) {
        بنية wl_region *region = wl_compositor_create_region(viddata->compositor);
        wl_region_جمع_کړه(region, 0, 0, پلنوالی, لوړوالی);
        wl_surface_سېټ_opaque_region(surface, region);
        wl_region_destroy(region);
    } وإلا {
        wl_surface_سېټ_opaque_region(surface, عدم);
    }
}

ساكن فراغ Configure_کړکۍ_Geometry(SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    ثابت مزدوج scale_ضریب_2 = Get_کړکۍ_Scale(کړکۍ);
    ثابت مزدوج prev_اشاره_ګر_scale_x = معلومات->اشاره_ګر_scale.x;
    ثابت مزدوج prev_اشاره_ګر_scale_y = معلومات->اشاره_ګر_scale.y;
    ثابت صحيح old_pixel_پلنوالی = معلومات->current.pixel_پلنوالی;
    ثابت صحيح old_pixel_لوړوالی = معلومات->current.pixel_لوړوالی;
    صحيح کړکۍ_پلنوالی = 0;
    صحيح کړکۍ_لوړوالی = 0;
    صحيح viewport_پلنوالی, viewport_لوړوالی;
    bool کړکۍ_اندازه_بدل_شوی;
    bool بفر_اندازه_بدل_شوی;
    ثابت bool is_opaque = !(کړکۍ->flags & SDL_کړکۍ_TRANSPARENT) && کړکۍ->opacity == 1.0f;

    إذا (معلومات->is_fullscreen && کړکۍ->fullscreen_exclusive) {
        کړکۍ_پلنوالی = کړکۍ->current_fullscreen_ډېرپېښ.w;
        کړکۍ_لوړوالی = کړکۍ->current_fullscreen_ډېرپېښ.h;

        viewport_پلنوالی = معلومات->requested.logical_پلنوالی;
        viewport_لوړوالی = معلومات->requested.logical_لوړوالی;

        بدل (Get_ډېرپېښ_Scale_لاره()) {
        حالة WAYLAND_ډېرپېښ_SCALE_NONE:
            /* The Wayland spec states that the advertised fullscreen dimensions are a maximum.
             * Windows can request a smaller size, but exceeding these dimensions is a protocol violation,
             * thus, modes that exceed the output size still need to be scaled with a viewport.
             */
            إذا (کړکۍ_پلنوالی <= viewport_پلنوالی && کړکۍ_لوړوالی <= viewport_لوړوالی) {
                viewport_پلنوالی = کړکۍ_پلنوالی;
                viewport_لوړوالی = کړکۍ_لوړوالی;

                اكسر;
            }
            SDL_FALLTHROUGH;
        حالة WAYLAND_ډېرپېښ_SCALE_ASPECT:
        {
            ثابت عائم output_نسبت = (عائم)viewport_پلنوالی / (عائم)viewport_لوړوالی;
            ثابت عائم ډېرپېښ_نسبت = (عائم)کړکۍ_پلنوالی / (عائم)کړکۍ_لوړوالی;

            إذا (output_نسبت > ډېرپېښ_نسبت) {
                viewport_پلنوالی = SDL_lroundf((عائم)کړکۍ_پلنوالی * ((عائم)viewport_لوړوالی / (عائم)کړکۍ_لوړوالی));
            } وإلا إذا (output_نسبت < ډېرپېښ_نسبت) {
                viewport_لوړوالی = SDL_lroundf((عائم)کړکۍ_لوړوالی * ((عائم)viewport_پلنوالی / (عائم)کړکۍ_پلنوالی));
            }
        } اكسر;
        افتراضي:
            اكسر;
        }

        کړکۍ_اندازه_بدل_شوی = کړکۍ_پلنوالی != کړکۍ->w ||
                              کړکۍ_لوړوالی != کړکۍ->h ||
                              معلومات->current.viewport_پلنوالی != viewport_پلنوالی ||
                              معلومات->current.viewport_لوړوالی != viewport_لوړوالی;

        // Exclusive fullscreen window sizes are always in pixel units.
        معلومات->current.pixel_پلنوالی = کړکۍ_پلنوالی;
        معلومات->current.pixel_لوړوالی = کړکۍ_لوړوالی;
        بفر_اندازه_بدل_شوی = معلومات->current.pixel_پلنوالی != old_pixel_پلنوالی ||
                              معلومات->current.pixel_لوړوالی != old_pixel_لوړوالی;

        إذا (کړکۍ_اندازه_بدل_شوی || بفر_اندازه_بدل_شوی) {
            إذا (معلومات->viewport) {
                wp_viewport_سېټ_destination(معلومات->viewport, viewport_پلنوالی, viewport_لوړوالی);

                معلومات->current.logical_پلنوالی = معلومات->requested.logical_پلنوالی;
                معلومات->current.logical_لوړوالی = معلومات->requested.logical_لوړوالی;
                معلومات->current.viewport_پلنوالی = viewport_پلنوالی;
                معلومات->current.viewport_لوړوالی = viewport_لوړوالی;
            } وإلا {
                // Calculate the integer scale from the mode and output.
                ثابت int32_t int_scale = SDL_max(کړکۍ->current_fullscreen_ډېرپېښ.w / viewport_پلنوالی, 1);

                wl_surface_سېټ_بفر_scale(معلومات->surface, int_scale);
                معلومات->current.logical_پلنوالی = کړکۍ->current_fullscreen_ډېرپېښ.w;
                معلومات->current.logical_لوړوالی = کړکۍ->current_fullscreen_ډېرپېښ.h;
            }

            معلومات->اشاره_ګر_scale.x = (مزدوج)کړکۍ_پلنوالی / (مزدوج)viewport_پلنوالی;
            معلومات->اشاره_ګر_scale.y = (مزدوج)کړکۍ_لوړوالی / (مزدوج)viewport_لوړوالی;
        }
    } وإلا {
        إذا (!معلومات->scale_منزل_display) {
            viewport_پلنوالی = معلومات->requested.logical_پلنوالی;
            viewport_لوړوالی = معلومات->requested.logical_لوړوالی;
        } وإلا {
            viewport_پلنوالی = معلومات->requested.pixel_پلنوالی;
            viewport_لوړوالی = معلومات->requested.pixel_لوړوالی;
        }

        إذا (!معلومات->enable_insets &&
            معلومات->shell_surface_حالت != WAYLAND_SHELL_SURFACE_حالت_HIDDEN &&
            معلومات->viewport && معلومات->wayland_معلومات->subcompositor && !معلومات->floating && !معلومات->is_fullscreen) {
            صحيح min_پلنوالی_2, min_لوړوالی_2, max_پلنوالی_2, max_لوړوالی_2;
            إذا (کړکۍ->flags & SDL_کړکۍ_RESIZABLE) {
                min_پلنوالی_2 = کړکۍ->min_w;
                min_لوړوالی_2 = کړکۍ->min_h;
                max_پلنوالی_2 = کړکۍ->max_w;
                max_لوړوالی_2 = کړکۍ->max_h;
            } وإلا {
                // Use the fixed size in the odd case where a non-resizable window somehow wound up tiled or maximized.
                min_پلنوالی_2 = کړکۍ->floating.w;
                min_لوړوالی_2 = کړکۍ->floating.h;
                max_پلنوالی_2 = کړکۍ->floating.w;
                max_لوړوالی_2 = کړکۍ->floating.h;
            }

            إذا (min_پلنوالی_2) {
                viewport_پلنوالی = SDL_max(viewport_پلنوالی, min_پلنوالی_2);
            }
            إذا (min_لوړوالی_2) {
                viewport_لوړوالی = SDL_max(viewport_لوړوالی, min_لوړوالی_2);
            }
            إذا (max_پلنوالی_2) {
                viewport_پلنوالی = SDL_min(viewport_پلنوالی, max_پلنوالی_2);
            }
            إذا (max_لوړوالی_2) {
                viewport_لوړوالی = SDL_min(viewport_لوړوالی, max_لوړوالی_2);
            }

            عائم aspect = (عائم)viewport_پلنوالی / (عائم)viewport_لوړوالی;
            إذا (کړکۍ->min_aspect != 0.f && aspect < کړکۍ->min_aspect) {
                viewport_لوړوالی = SDL_max(SDL_lroundf((عائم)viewport_پلنوالی / کړکۍ->min_aspect), 1);
            } وإلا إذا (کړکۍ->max_aspect != 0.f && aspect > کړکۍ->max_aspect) {
                viewport_پلنوالی = SDL_max(SDL_lroundf((عائم)viewport_لوړوالی * کړکۍ->max_aspect), 1);
            }

            // At this point, the viewport matches the virtual window dimensions, but the viewport might be clamped to the output window dimensions beyond here.
            کړکۍ_پلنوالی = viewport_پلنوالی;
            کړکۍ_لوړوالی = viewport_لوړوالی;

            // If the viewport bounds exceed the window size, scale them while maintaining the aspect ratio.
            إذا (!معلومات->scale_منزل_display) {
                إذا (viewport_پلنوالی > معلومات->requested.logical_پلنوالی || viewport_لوړوالی > معلومات->requested.logical_لوړوالی) {
                    aspect = (عائم)viewport_پلنوالی / (عائم)viewport_لوړوالی;
                    ثابت عائم کړکۍ_نسبت = (عائم)معلومات->requested.logical_پلنوالی / (عائم)معلومات->requested.logical_لوړوالی;
                    إذا (aspect >= کړکۍ_نسبت) {
                        viewport_پلنوالی = معلومات->requested.logical_پلنوالی;
                        viewport_لوړوالی = SDL_lroundf((عائم)viewport_پلنوالی / aspect);
                    } وإلا إذا (aspect < کړکۍ_نسبت) {
                        viewport_لوړوالی = معلومات->requested.logical_لوړوالی;
                        viewport_پلنوالی = SDL_lroundf((عائم)viewport_لوړوالی * aspect);
                    }
                }
            } وإلا {
                إذا (viewport_پلنوالی > معلومات->requested.pixel_پلنوالی || viewport_لوړوالی > معلومات->requested.pixel_لوړوالی) {
                    aspect = (عائم)viewport_پلنوالی / (عائم)viewport_لوړوالی;
                    ثابت عائم کړکۍ_نسبت = (عائم)معلومات->requested.pixel_پلنوالی / (عائم)معلومات->requested.pixel_لوړوالی;
                    إذا (aspect >= کړکۍ_نسبت) {
                        viewport_پلنوالی = معلومات->requested.pixel_پلنوالی;
                        viewport_لوړوالی = SDL_lroundf((عائم)viewport_پلنوالی / aspect);
                    } وإلا إذا (aspect < کړکۍ_نسبت) {
                        viewport_لوړوالی = معلومات->requested.pixel_لوړوالی;
                        viewport_پلنوالی = SDL_lroundf((عائم)viewport_لوړوالی * aspect);
                    }
                }
            }

            viewport_پلنوالی = SDL_max(viewport_پلنوالی, 1);
            viewport_لوړوالی = SDL_max(viewport_لوړوالی, 1);
        } وإلا {
            کړکۍ_پلنوالی = viewport_پلنوالی;
            کړکۍ_لوړوالی = viewport_لوړوالی;
        }

        إذا (!معلومات->scale_منزل_display) {
            معلومات->current.pixel_پلنوالی = ټکی_منزل_Pixel(کړکۍ, کړکۍ_پلنوالی);
            معلومات->current.pixel_لوړوالی = ټکی_منزل_Pixel(کړکۍ, کړکۍ_لوړوالی);
        } وإلا {
            // The viewport size is in pixels at this point; convert it to logical units.
            معلومات->current.pixel_پلنوالی = کړکۍ_پلنوالی;
            معلومات->current.pixel_لوړوالی = کړکۍ_لوړوالی;
            viewport_پلنوالی = Pixel_منزل_ټکی(کړکۍ, viewport_پلنوالی);
            viewport_لوړوالی = Pixel_منزل_ټکی(کړکۍ, viewport_لوړوالی);
        }

        // Clamp the physical window size to the system minimum required size.
        معلومات->requested.logical_پلنوالی = SDL_max(معلومات->requested.logical_پلنوالی, معلومات->system_limits.min_پلنوالی_2);
        معلومات->requested.logical_لوړوالی = SDL_max(معلومات->requested.logical_لوړوالی, معلومات->system_limits.min_لوړوالی_2);

        کړکۍ_اندازه_بدل_شوی = معلومات->requested.logical_پلنوالی != معلومات->current.logical_پلنوالی ||
                              معلومات->requested.logical_لوړوالی != معلومات->current.logical_لوړوالی ||
                              viewport_پلنوالی != معلومات->current.viewport_پلنوالی ||
                              viewport_لوړوالی != معلومات->current.viewport_لوړوالی;

        بفر_اندازه_بدل_شوی = معلومات->current.pixel_پلنوالی != old_pixel_پلنوالی ||
                              معلومات->current.pixel_لوړوالی != old_pixel_لوړوالی;

        إذا (کړکۍ_اندازه_بدل_شوی || بفر_اندازه_بدل_شوی) {
            إذا (معلومات->viewport) {
                wp_viewport_سېټ_destination(معلومات->viewport, viewport_پلنوالی, viewport_لوړوالی);
            } وإلا إذا (کړکۍ->flags & SDL_کړکۍ_لوړ_PIXEL_DENSITY) {
                // Don't change this if the DPI awareness flag is unset, as an application may have set this manually on a custom or external surface.
                wl_surface_سېټ_بفر_scale(معلومات->surface, (int32_t)scale_ضریب_2);
            }

            معلومات->current.logical_پلنوالی = معلومات->requested.logical_پلنوالی;
            معلومات->current.logical_لوړوالی = معلومات->requested.logical_لوړوالی;
            معلومات->current.viewport_پلنوالی = viewport_پلنوالی;
            معلومات->current.viewport_لوړوالی = viewport_لوړوالی;

            معلومات->اشاره_ګر_scale.x = (مزدوج)کړکۍ_پلنوالی / (مزدوج)viewport_پلنوالی;
            معلومات->اشاره_ګر_scale.y = (مزدوج)کړکۍ_لوړوالی / (مزدوج)viewport_لوړوالی;
        }
    }

    إذا (معلومات->egl_کړکۍ && بفر_اندازه_بدل_شوی) {
        WAYLAND_wl_egl_کړکۍ_resize(معلومات->egl_کړکۍ,
                                     معلومات->current.pixel_پلنوالی,
                                     معلومات->current.pixel_لوړوالی,
                                     0, 0);
    }

    /* Calculate the mask size and offset.
     * Fullscreen windows are centered and masked automatically by the compositor, unless it lacks the capability.
     */
    إذا (!معلومات->enable_insets && معلومات->viewport && معلومات->wayland_معلومات->subcompositor && (!معلومات->is_fullscreen || Should_ماسک_Fullscreen()) &&
        (viewport_پلنوالی != معلومات->current.logical_پلنوالی || viewport_لوړوالی != معلومات->current.logical_لوړوالی)) {
        بنية wl_بفر *old_بفر = عدم;

        إذا (!معلومات->ماسک.surface) {
            معلومات->ماسک.surface = wl_compositor_create_surface(معلومات->wayland_معلومات->compositor);
            SDL_WAYLAND_ثبتوونکی_surface(معلومات->ماسک.surface);
            wl_surface_سېټ_user_معلومات(معلومات->ماسک.surface, معلومات);
        }
        إذا (!معلومات->ماسک.subsurface) {
            معلومات->ماسک.subsurface = wl_subcompositor_get_subsurface(معلومات->wayland_معلومات->subcompositor, معلومات->ماسک.surface, معلومات->surface);
        }
        إذا (!معلومات->ماسک.viewport) {
            معلومات->ماسک.viewport = wp_viewporter_get_viewport(معلومات->wayland_معلومات->viewporter, معلومات->ماسک.surface);
        }
        إذا (!معلومات->ماسک.بفر_2 || معلومات->ماسک.opaque != is_opaque) {
            old_بفر = معلومات->ماسک.بفر_2;
            معلومات->ماسک.opaque = is_opaque;
            معلومات->ماسک.بفر_2 = Wayland_Create_Single_Pixel_بفر(0, 0, 0, is_opaque ? SDL_MAX_UINT32 : 0);
        }

        wl_surface_attach(معلومات->ماسک.surface, معلومات->ماسک.بفر_2, 0, 0);

        wl_subsurface_ځای_پرځای_کړه_لاندې(معلومات->ماسک.subsurface, معلومات->surface);
        wp_viewport_سېټ_destination(معلومات->ماسک.viewport, معلومات->current.logical_پلنوالی, معلومات->current.logical_لوړوالی);

        إذا (wl_surface_get_نسخه(معلومات->ماسک.surface) >= WL_SURFACE_DAMAGE_بفر_SINCE_نسخه) {
            wl_surface_damage_بفر(معلومات->ماسک.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        } وإلا {
            wl_surface_damage(معلومات->ماسک.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        }

        إذا (is_opaque) {
            سېټ_Surface_Opaque_Region(معلومات->ماسک.surface, معلومات->current.logical_پلنوالی, معلومات->current.logical_لوړوالی);
        } وإلا {
            سېټ_Surface_Opaque_Region(معلومات->ماسک.surface, 0, 0);
        }

        // Can't use an offset subsurface with libdecor (yet), or the decorations won't line up properly.
        إذا (معلومات->shell_surface_type != WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
            معلومات->ماسک.دننه_واټن_x = -(معلومات->current.logical_پلنوالی - viewport_پلنوالی) / 2;
            معلومات->ماسک.دننه_واټن_y = -(معلومات->current.logical_لوړوالی - viewport_لوړوالی) / 2;
        } وإلا {
            معلومات->ماسک.دننه_واټن_x = 0;
            معلومات->ماسک.دننه_واټن_y = 0;
        }

        wl_subsurface_سېټ_position(معلومات->ماسک.subsurface, معلومات->ماسک.دننه_واټن_x, معلومات->ماسک.دننه_واټن_y);
        wl_surface_commit(معلومات->ماسک.surface);

        إذا (old_بفر) {
            wl_بفر_destroy(old_بفر);
        }

        معلومات->ماسک.mapped = true;
    } وإلا إذا (معلومات->ماسک.mapped) {
        wl_subsurface_سېټ_position(معلومات->ماسک.subsurface, 0, 0);
        wl_surface_attach(معلومات->ماسک.surface, عدم, 0, 0);
        wl_surface_commit(معلومات->ماسک.surface);

        معلومات->ماسک.دننه_واټن_x = 0;
        معلومات->ماسک.دننه_واټن_y = 0;
        معلومات->ماسک.mapped = false;
    }

    إذا (معلومات->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && معلومات->shell_surface.xdg.surface &&
        (معلومات->enable_insets || !معلومات->viewport)) {
        /* The window geometry is the surface minus the declared border insets. They don't apply
         * when an exact size is required (maximized/fullscreen).
         */
        BorderInsets insets;
        GetBorderInsets(کړکۍ, &insets);
        ثابت bool use_insets = (insets.کیڼ || insets.سر || insets.ښی || insets.bottom) &&
                                !(کړکۍ->flags & (SDL_کړکۍ_MAXIMIZED | SDL_کړکۍ_FULLSCREEN));
        SDL_Rect geometry = { 0, 0, معلومات->current.logical_پلنوالی, معلومات->current.logical_لوړوالی };
        إذا (use_insets) {
            geometry.x = insets.کیڼ;
            geometry.y = insets.سر;
            geometry.w = SDL_max(geometry.w - (insets.کیڼ + insets.ښی), 1);
            geometry.h = SDL_max(geometry.h - (insets.سر + insets.bottom), 1);
        }
        /* An explicitly set geometry does not track the surface, so it must be kept in sync
         * once set. Otherwise this is only done when viewports aren't supported and the size
         * has changed (XXX: a hack) to avoid a potential protocol violation if a buffer with
         * an old size is committed.
         */
        إذا ((use_insets || !SDL_Rect_تشه(&معلومات->explicit_geometry) || (!معلومات->viewport && کړکۍ_اندازه_بدل_شوی)) &&
            !SDL_RectsEqual(&geometry, &معلومات->explicit_geometry)) {
            xdg_surface_سېټ_کړکۍ_geometry(معلومات->shell_surface.xdg.surface, geometry.x, geometry.y, geometry.w, geometry.h);
            معلومات->explicit_geometry = geometry;
        }
    }

    /* The opaque region and pointer confinement region only need to be
     * recalculated if the output size has changed.
     */
    إذا (کړکۍ_اندازه_بدل_شوی) {
        إذا (is_opaque) {
            سېټ_Surface_Opaque_Region(معلومات->surface, viewport_پلنوالی, viewport_لوړوالی);
        } وإلا {
            سېټ_Surface_Opaque_Region(معلومات->surface, 0, 0);
        }

        // Ensure that child popup windows are still in bounds.
        لكل (SDL_کړکۍ *ماشوم = کړکۍ->لومړی_ماشوم; ماشوم; ماشوم = ماشوم->بل_sibling) {
            RepositionPopup(ماشوم, true);
        }
    }

    // Update the scale for any focused cursors.
    إذا (prev_اشاره_ګر_scale_x != معلومات->اشاره_ګر_scale.x || prev_اشاره_ګر_scale_y != معلومات->اشاره_ګر_scale.y) {
        Wayland_Display_Update_اشاره_ګر_Focused_Scale(معلومات);
    }

    /* Update the min/max dimensions, primarily if the state was changed, and for non-resizable
     * xdg-toplevel windows where the limits should match the window size.
     */
    سېټ_Min_Max_Dimensions(کړکۍ);

    // Unconditionally send the window and drawable size, the video core will deduplicate when required.
    إذا (!معلومات->scale_منزل_display) {
        SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_RESIZED, کړکۍ_پلنوالی, کړکۍ_لوړوالی);
    } وإلا {
        SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_RESIZED, معلومات->current.pixel_پلنوالی, معلومات->current.pixel_لوړوالی);
    }
    SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_PIXEL_اندازه_بدل_شوی, معلومات->current.pixel_پلنوالی, معلومات->current.pixel_لوړوالی);

    /* Send an exposure event if the window is in the shown state and the size has changed,
     * even if the window is occluded, as the client needs to commit a new frame for the
     * changes to take effect.
     *
     * The occlusion state is immediately set again afterward, if necessary.
     */
    إذا (معلومات->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_SHOWN) {
        إذا ((بفر_اندازه_بدل_شوی || کړکۍ_اندازه_بدل_شوی) ||
            (!معلومات->suspended && (کړکۍ->flags & SDL_کړکۍ_OCCLUDED))) {
            SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_EXPOSED, 0, 0);
        }

        إذا (معلومات->suspended) {
            SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_OCCLUDED, 0, 0);
        }
    }
}

ساكن فراغ Commit_Libdecor_چوکاټ(SDL_کړکۍ *کړکۍ)
{
#که_تعریف_شوی HAVE_LIBDECOR_H
    SDL_کړکۍ_معلومات *wind = کړکۍ->دننی;

    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.چوکاټ) {
        بنية libdecor_state *state = libdecor_state_new(wind->current.logical_پلنوالی, wind->current.logical_لوړوالی);
        libdecor_چوکاټ_commit(wind->shell_surface.libdecor.چوکاټ, state, عدم);
        libdecor_state_free(state);
    }
#د_که_پای
}

ساكن فراغ pending_state_deadline_handler(فراغ *معلومات, بنية wl_callback *callback, uint32_t callback_معلومات)
{
    // Get the window from the ID, as it may have been destroyed.
    SDL_کړکۍ_ID کړکۍ_ID = (SDL_کړکۍ_ID)(uintptr_t)معلومات;
    SDL_کړکۍ *کړکۍ = SDL_Get_کړکۍ_From_ID(کړکۍ_ID);

    إذا (کړکۍ && کړکۍ->دننی) {
        --کړکۍ->دننی->pending_state_deadline_شمېر;
    }

    wl_callback_destroy(callback);
}

ساكن بنية wl_callback_listener pending_state_deadline_listener = {
    pending_state_deadline_handler
};

ساكن فراغ جمع_کړه_Pending_State_Sync(SDL_کړکۍ_معلومات *کړکۍ_معلومات_2)
{
    SDL_Video_معلومات *video_معلومات = کړکۍ_معلومات_2->wayland_معلومات;
    فراغ *cb_معلومات = (فراغ *)(uintptr_t)کړکۍ_معلومات_2->sdlwindow->id;

    ++کړکۍ_معلومات_2->pending_state_deadline_شمېر;
    بنية wl_callback *cb = wl_display_sync(video_معلومات->display);
    wl_callback_جمع_کړه_listener(cb, &pending_state_deadline_listener, cb_معلومات);
}

ساكن فراغ FlushPendingEvents(SDL_کړکۍ *کړکۍ)
{
    // Serialize and restore the pending flags, as they may be overwritten while flushing.
    ثابت bool وروستی_position_pending = کړکۍ->وروستی_position_pending;
    ثابت bool وروستی_اندازه_pending = کړکۍ->وروستی_اندازه_pending;

    طالما (کړکۍ->دننی->pending_state_deadline_شمېر) {
        WAYLAND_wl_display_roundtrip(کړکۍ->دننی->wayland_معلومات->display);
    }

    کړکۍ->وروستی_position_pending = وروستی_position_pending;
    کړکۍ->وروستی_اندازه_pending = وروستی_اندازه_pending;
}

/* While we can't get window position from the compositor, we do at least know
 * what monitor we're on, so let's send move events that put the window at the
 * center of the whatever display the wl_surface_listener events give us.
 */
فراغ Wayland_Update_کړکۍ_Position(SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *wind = کړکۍ->دننی;
    SDL_Display_معلومات *display;

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
    wind->وروستی_display_ID = display->display;
    إذا (wind->shell_surface_type != WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        إذا (!wind->wayland_معلومات->scale_منزل_display_enabled) {
            SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_MOVED, display->logical.x, display->logical.y);
        } وإلا {
            SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_MOVED, display->pixel.x, display->pixel.y);
        }
        SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_DISPLAY_بدل_شوی, wind->وروستی_display_ID, 0);
    }
}

ساكن فراغ سېټ_Fullscreen(SDL_کړکۍ *کړکۍ, بنية wl_output *output, bool fullscreen)
{
    SDL_کړکۍ_معلومات *wind = کړکۍ->دننی;

#که_تعریف_شوی HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (!wind->shell_surface.libdecor.چوکاټ) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }

        wind->fullscreen_exclusive = output ? کړکۍ->fullscreen_exclusive : false;
        إذا (fullscreen) {
            libdecor_چوکاټ_سېټ_fullscreen(wind->shell_surface.libdecor.چوکاټ, output);
        } وإلا {
            libdecor_چوکاټ_unset_fullscreen(wind->shell_surface.libdecor.چوکاټ);
        }
    } وإلا
#د_که_پای
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        إذا (wind->shell_surface.xdg.toplevel.xdg_toplevel == عدم) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }

        wind->fullscreen_exclusive = output ? کړکۍ->fullscreen_exclusive : false;
        إذا (fullscreen) {
            xdg_toplevel_سېټ_fullscreen(wind->shell_surface.xdg.toplevel.xdg_toplevel, output);
        } وإلا {
            xdg_toplevel_unset_fullscreen(wind->shell_surface.xdg.toplevel.xdg_toplevel);
        }
    }

    جمع_کړه_Pending_State_Sync(wind);
}

ساكن فراغ Update_کړکۍ_Fullscreen(SDL_کړکۍ *کړکۍ, bool fullscreen)
{
    SDL_کړکۍ_معلومات *wind = کړکۍ->دننی;

    wind->is_fullscreen = fullscreen;

    إذا (fullscreen) {
        إذا (!(کړکۍ->flags & SDL_کړکۍ_FULLSCREEN)) {
            SDL_copyp(&کړکۍ->current_fullscreen_ډېرپېښ, &کړکۍ->requested_fullscreen_ډېرپېښ);
            SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_ENTER_FULLSCREEN, 0, 0);
            SDL_Update_Fullscreen_ډېرپېښ(کړکۍ, SDL_FULLSCREEN_OP_ENTER, false);

            /* Set the output for exclusive fullscreen windows when entering fullscreen from a
             * compositor event, or if the fullscreen parameters were changed between the initial
             * fullscreen request and now, to ensure that the window is on the correct output,
             * as requested by the client.
             */
            إذا (کړکۍ->fullscreen_exclusive && (!wind->fullscreen_exclusive || !wind->fullscreen_was_positioned)) {
                SDL_VideoDisplay *disp = SDL_GetVideoDisplay(کړکۍ->current_fullscreen_ډېرپېښ.displayID);
                إذا (disp) {
                    wind->fullscreen_was_positioned = true;
                    سېټ_Fullscreen(کړکۍ, disp->دننی->output, true);
                }
            }
        }
    } وإلا {
        // Don't change the fullscreen flags if the window is hidden or being hidden.
        إذا ((کړکۍ->flags & SDL_کړکۍ_FULLSCREEN) && !کړکۍ->is_hiding && !(کړکۍ->flags & SDL_کړکۍ_HIDDEN)) {
            SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_LEAVE_FULLSCREEN, 0, 0);
            SDL_Update_Fullscreen_ډېرپېښ(کړکۍ, SDL_FULLSCREEN_OP_LEAVE, false);
            wind->fullscreen_was_positioned = false;

            /* Send a move event, in case it was deferred while the fullscreen window was moving and
             * on multiple outputs.
             */
            Wayland_Update_کړکۍ_Position(کړکۍ);
        }
    }
}

ساكن ثابت بنية wl_callback_listener surface_چوکاټ_listener;

ساكن فراغ surface_چوکاټ_بشپړ(فراغ *معلومات, بنية wl_callback *cb, uint32_t وخت)
{
    SDL_کړکۍ_معلومات *wind = (SDL_کړکۍ_معلومات *)معلومات;

    /* XXX: This is needed to work around an Nvidia egl-wayland bug due to buffer coordinates
     *      being used with wl_surface_damage, which causes part of the output to not be
     *      updated when using a viewport with an output region larger than the source region.
     */
    إذا (wl_compositor_get_نسخه(wind->wayland_معلومات->compositor) >= WL_SURFACE_DAMAGE_بفر_SINCE_نسخه) {
        wl_surface_damage_بفر(wind->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    } وإلا {
        wl_surface_damage(wind->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    }

    wind->pending_state_commit = false;

    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        إذا (wind->pending_config_ack) {
            wind->pending_config_ack = false;
            Configure_کړکۍ_Geometry(wind->sdlwindow);
            xdg_surface_ack_configure(wind->shell_surface.xdg.surface, wind->shell_surface.xdg.serial);
        }
    } وإلا {
        wind->resizing = false;
    }

    إذا (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_چوکاټ) {
        wind->shell_surface_حالت = WAYLAND_SHELL_SURFACE_حالت_SHOWN;

        // If any child windows are waiting on this window to be shown, show them now
        لكل (SDL_کړکۍ *w = wind->sdlwindow->لومړی_ماشوم; w; w = w->بل_sibling) {
            إذا (w->دننی->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_SHOW_PENDING) {
                Wayland_Show_کړکۍ(SDL_GetVideoDevice(), w);
            } وإلا إذا (w->دننی->reparenting_required) {
                Wayland_سېټ_کړکۍ_پلار(SDL_GetVideoDevice(), w, w->پلار);
                إذا (w->flags & SDL_کړکۍ_MODAL) {
                    Wayland_سېټ_کړکۍ_Modal(SDL_GetVideoDevice(), w, true);
                }
            }
        }

        /* If the window was initially set to the suspended state, send the occluded event now,
         * as we don't want to mark the window as occluded until at least one frame has been submitted.
         */
        إذا (wind->suspended) {
            SDL_Send_کړکۍ_Event(wind->sdlwindow, SDL_EVENT_کړکۍ_OCCLUDED, 0, 0);
        }
    }

    wl_callback_destroy(cb);
    wind->surface_چوکاټ_callback = wl_surface_چوکاټ(wind->surface);
    wl_callback_جمع_کړه_listener(wind->surface_چوکاټ_callback, &surface_چوکاټ_listener, معلومات);
}

ساكن ثابت بنية wl_callback_listener surface_چوکاټ_listener = {
    surface_چوکاټ_بشپړ
};

ساكن ثابت بنية wl_callback_listener gles_بدلون_چوکاټ_listener;

ساكن فراغ gles_بدلون_چوکاټ_بشپړ(فراغ *معلومات, بنية wl_callback *cb, uint32_t وخت)
{
    SDL_کړکۍ_معلومات *wind = (SDL_کړکۍ_معلومات *)معلومات;
    SDL_سېټ_Atomic_Int(&wind->بدلون_interval_ready, 1); // mark window as ready to present again.

    // reset this callback to fire again once a new frame was presented and compositor wants the next one.
    wind->gles_بدلون_چوکاټ_callback = wl_surface_چوکاټ(wind->gles_بدلون_چوکاټ_surface_wrapper);
    wl_callback_destroy(cb);
    wl_callback_جمع_کړه_listener(wind->gles_بدلون_چوکاټ_callback, &gles_بدلون_چوکاټ_listener, معلومات);
}

ساكن ثابت بنية wl_callback_listener gles_بدلون_چوکاټ_listener = {
    gles_بدلون_چوکاټ_بشپړ
};

ساكن فراغ handle_xdg_surface_configure(فراغ *معلومات, بنية xdg_surface *xdg, uint32_t serial)
{
    SDL_کړکۍ_معلومات *wind = (SDL_کړکۍ_معلومات *)معلومات;
    SDL_کړکۍ *کړکۍ = wind->sdlwindow;

    /* Interactive resizes are throttled by acking and committing only the most recent configuration at
     * the next frame callback, or certain combinations of clients and compositors can exhibit severe lag
     * when resizing.
     */
    wind->shell_surface.xdg.serial = serial;
    إذا (!wind->resizing) {
        wind->pending_config_ack = false;
        Configure_کړکۍ_Geometry(کړکۍ);
        xdg_surface_ack_configure(xdg, serial);
    } وإلا إذا (!wind->pending_config_ack) {
        wind->pending_config_ack = true;

        // Always send an exposure event during a new frame to ensure forward progress if the frame callback already occurred.
        SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_EXPOSED, 0, 0);
    }

    إذا (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_CONFIGURE) {
        wind->shell_surface_حالت = WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_چوکاټ;
    }
}

ساكن ثابت بنية xdg_surface_listener _xdg_surface_listener = {
    handle_xdg_surface_configure
};

ساكن فراغ ApplyGeometryLimits(SDL_کړکۍ *کړکۍ, صحيح req_w, صحيح req_h, صحيح *بهر_w, صحيح *بهر_h)
{
    SDL_کړکۍ_معلومات *wind = کړکۍ->دننی;

    صحيح w = req_w;
    صحيح h = req_h;
    ثابت عائم aspect = (عائم)req_w / (عائم)req_h;

    /* If adjusting for aspect causes the adjusted dimension to exceed the min/max limit, clamp to the limit
     * and attempt to adjust the opposite dimension to compensate.
     */
    إذا (!wind->resizing || (wind->resize_څنډه & WAYLAND_RESIZE_څنډه_کونج) == WAYLAND_RESIZE_څنډه_کونج) {
        إذا (کړکۍ->min_aspect != 0.f && aspect < کړکۍ->min_aspect) {
            h = SDL_max(SDL_lroundf((عائم)req_w / کړکۍ->min_aspect), 1);

            إذا (h < کړکۍ->min_h) {
                w = SDL_max(SDL_lroundf((عائم)کړکۍ->min_h * کړکۍ->min_aspect), 1);
            }
            إذا (کړکۍ->max_h && h > کړکۍ->max_h) {
                w = SDL_max(SDL_lroundf((عائم)کړکۍ->max_h * کړکۍ->min_aspect), 1);
            }
        } وإلا إذا (کړکۍ->max_aspect != 0.f && aspect > کړکۍ->max_aspect) {
            w = SDL_max(SDL_lroundf((عائم)req_h * کړکۍ->max_aspect), 1);

            إذا (w < کړکۍ->min_w) {
                h = SDL_max(SDL_lroundf((عائم)کړکۍ->min_w / کړکۍ->max_aspect), 1);
            }
            إذا (کړکۍ->max_w && w > کړکۍ->max_w) {
                h = SDL_max(SDL_lroundf((عائم)کړکۍ->max_w / کړکۍ->max_aspect), 1);
            }
        }
    } وإلا إذا (wind->resize_څنډه & WAYLAND_RESIZE_څنډه_LR) {
        إذا (کړکۍ->min_aspect != 0.f && aspect < کړکۍ->min_aspect) {
            h = SDL_max(SDL_lroundf((عائم)req_w / کړکۍ->min_aspect), 1);

            إذا (h < کړکۍ->min_h) {
                w = SDL_max(SDL_lroundf((عائم)کړکۍ->min_h * کړکۍ->min_aspect), 1);
            }
            إذا (کړکۍ->max_h && h > کړکۍ->max_h) {
                w = SDL_max(SDL_lroundf((عائم)کړکۍ->max_h * کړکۍ->min_aspect), 1);
            }
        } وإلا إذا (کړکۍ->max_aspect != 0.f && aspect > کړکۍ->max_aspect) {
            h = SDL_max(SDL_lroundf((عائم)req_w / کړکۍ->max_aspect), 1);

            إذا (h < کړکۍ->min_h) {
                w = SDL_max(SDL_lroundf((عائم)کړکۍ->min_h * کړکۍ->max_aspect), 1);
            }
            إذا (کړکۍ->max_h && h > کړکۍ->max_h) {
                w = SDL_max(SDL_lroundf((عائم)کړکۍ->max_h * کړکۍ->max_aspect), 1);
            }
        }
    } وإلا إذا (wind->resize_څنډه & WAYLAND_RESIZE_څنډه_TB) {
        إذا (کړکۍ->min_aspect != 0.f && aspect < کړکۍ->min_aspect) {
            w = SDL_max(SDL_lroundf((عائم)req_h * کړکۍ->min_aspect), 1);

            إذا (w < کړکۍ->min_w) {
                h = SDL_max(SDL_lroundf((عائم)کړکۍ->min_w / کړکۍ->min_aspect), 1);
            }
            إذا (کړکۍ->max_w && w > کړکۍ->max_w) {
                h = SDL_max(SDL_lroundf((عائم)کړکۍ->max_w / کړکۍ->min_aspect), 1);
            }
        } وإلا إذا (کړکۍ->max_aspect != 0.f && aspect > کړکۍ->max_aspect) {
            w = SDL_max(SDL_lroundf((عائم)req_h * کړکۍ->max_aspect), 1);

            إذا (w < کړکۍ->min_w) {
                h = SDL_max(SDL_lroundf((عائم)کړکۍ->min_w / کړکۍ->max_aspect), 1);
            }
            إذا (کړکۍ->max_w && w > کړکۍ->max_w) {
                h = SDL_max(SDL_lroundf((عائم)کړکۍ->max_w / کړکۍ->max_aspect), 1);
            }
        }
    }

    إذا (کړکۍ->max_w) {
        w = SDL_min(w, کړکۍ->max_w);
    }
    *بهر_w = SDL_max(w, کړکۍ->min_w);

    إذا (کړکۍ->max_h) {
        h = SDL_min(h, کړکۍ->max_h);
    }
    *بهر_h = SDL_max(h, کړکۍ->min_h);

}

ساكن فراغ DetermineResizeAxis(SDL_کړکۍ_معلومات *wind, صحيح پلنوالی, صحيح لوړوالی, bool resizing)
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
        إذا (now >= wind->وروستی_resize_event_وخت_ns + SDL_MS_منزل_NS(500)) {
            wind->resize_څنډه = 0;
        }

        wind->وروستی_resize_event_وخت_ns = now;

        إذا (!wind->resize_څنډه) {
            إذا (پلنوالی != wind->وروستی_configure.پلنوالی || !لوړوالی) {
                wind->resize_څنډه |= WAYLAND_RESIZE_څنډه_LR;
            }
            إذا (لوړوالی != wind->وروستی_configure.لوړوالی || !پلنوالی) {
                wind->resize_څنډه |= WAYLAND_RESIZE_څنډه_TB;
            }
        }
    } وإلا {
        wind->resize_څنډه = 0;
    }

    wind->resizing = resizing;
}

ساكن فراغ handle_xdg_toplevel_configure(فراغ *معلومات,
                                          بنية xdg_toplevel *xdg_toplevel,
                                          int32_t پلنوالی,
                                          int32_t لوړوالی,
                                          بنية wl_array *حالتونه)
{
    SDL_کړکۍ_معلومات *wind = (SDL_کړکۍ_معلومات *)معلومات;
    SDL_کړکۍ *کړکۍ = wind->sdlwindow;

    تعداد xdg_toplevel_state *state;
    bool fullscreen = false;
    bool maximized = false;
    bool floating = true;
    bool tiled = false;
    bool فعال = false;
    bool resizing = false;
    bool suspended = false;
    wind->toplevel_constraints = 0;
    wl_array_for_each (state, حالتونه) {
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
            فعال = true;
            اكسر;
        حالة XDG_TOPLEVEL_STATE_TILED_کیڼ:
        حالة XDG_TOPLEVEL_STATE_TILED_ښی:
        حالة XDG_TOPLEVEL_STATE_TILED_سر:
        حالة XDG_TOPLEVEL_STATE_TILED_BOTTOM:
            tiled = true;
            floating = false;
            اكسر;
        حالة XDG_TOPLEVEL_STATE_SUSPENDED:
            suspended = true;
            اكسر;
        حالة XDG_TOPLEVEL_STATE_CONSTRAINED_کیڼ:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_کیڼ;
            اكسر;
        حالة XDG_TOPLEVEL_STATE_CONSTRAINED_ښی:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_ښی;
            اكسر;
        حالة XDG_TOPLEVEL_STATE_CONSTRAINED_سر:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_سر;
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
    ثابت bool new_configure_اندازه = پلنوالی != wind->وروستی_configure.پلنوالی || لوړوالی != wind->وروستی_configure.لوړوالی ||
                                    insets_apply != wind->وروستی_configure.insets_apply;

    BorderInsets insets = { 0, 0, 0, 0 };
    إذا (insets_apply) {
        GetBorderInsets(کړکۍ, &insets);
    }

    DetermineResizeAxis(wind, پلنوالی, لوړوالی, resizing);
    Update_کړکۍ_Fullscreen(کړکۍ, fullscreen);

    /* Always send a maximized/restore event; if the event is redundant it will
     * automatically be discarded (see src/events/SDL_windowevents.c)
     *
     * No, we do not get minimize events from xdg-shell, however, the minimized
     * state can be programmatically set. The meaning of 'minimized' is compositor
     * dependent, but in general, we can assume that the flag should remain set until
     * the next focused configure event occurs.
     */
    إذا (فعال || !(کړکۍ->flags & SDL_کړکۍ_MINIMIZED)) {
        إذا (کړکۍ->flags & SDL_کړکۍ_MINIMIZED) {
            // If we were minimized, send a restored event before possibly sending maximized.
            SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_RESTORED, 0, 0);
        }
        SDL_Send_کړکۍ_Event(کړکۍ,
                            (maximized && !fullscreen) ? SDL_EVENT_کړکۍ_MAXIMIZED : SDL_EVENT_کړکۍ_RESTORED,
                            0, 0);
    }

    إذا (!fullscreen) {
        /* xdg_toplevel spec states that this is a suggestion.
         * Ignore if less than or greater than max/min size.
         */
        إذا ((کړکۍ->flags & SDL_کړکۍ_RESIZABLE) || maximized) {
            إذا (!پلنوالی) {
                /* This happens when the compositor indicates that the size is
                 * up to the client, so use the cached window size here.
                 */
                إذا (floating) {
                    پلنوالی = کړکۍ->floating.w;

                    // Clamp the window to the toplevel bounds, if any are set.
                    إذا (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_CONFIGURE && wind->toplevel_bounds.پلنوالی) {
                        پلنوالی = SDL_min(wind->toplevel_bounds.پلنوالی, پلنوالی);
                    }
                } وإلا {
                    پلنوالی = کړکۍ->windowed.w;
                }

                إذا (!wind->scale_منزل_display) {
                    wind->requested.logical_پلنوالی = پلنوالی;
                } وإلا {
                    wind->requested.pixel_پلنوالی = پلنوالی;
                    پلنوالی = wind->requested.logical_پلنوالی = Pixel_منزل_ټکی(کړکۍ, پلنوالی);
                }
                پلنوالی = SDL_max(پلنوالی - (insets.کیڼ + insets.ښی), 1);
            } وإلا إذا (new_configure_اندازه) {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 */

                wind->requested.logical_پلنوالی = پلنوالی + (insets.کیڼ + insets.ښی);

                إذا (wind->scale_منزل_display) {
                    wind->requested.pixel_پلنوالی = ټکی_منزل_Pixel(کړکۍ, wind->requested.logical_پلنوالی);
                }
            }
            إذا (!لوړوالی) {
                /* This happens when the compositor indicates that the size is
                 * up to the client, so use the cached window size here.
                 */
                إذا (floating) {
                    لوړوالی = کړکۍ->floating.h;

                    // Clamp the window to the toplevel bounds, if any are set.
                    إذا (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_CONFIGURE && wind->toplevel_bounds.لوړوالی) {
                        لوړوالی = SDL_min(wind->toplevel_bounds.لوړوالی, لوړوالی);
                    }
                } وإلا {
                    لوړوالی = کړکۍ->windowed.h;
                }

                إذا (!wind->scale_منزل_display) {
                    wind->requested.logical_لوړوالی = لوړوالی;
                } وإلا {
                    wind->requested.pixel_لوړوالی = لوړوالی;
                    لوړوالی = wind->requested.logical_لوړوالی = Pixel_منزل_ټکی(کړکۍ, لوړوالی);
                }
                لوړوالی = SDL_max(لوړوالی - (insets.سر + insets.bottom), 1);
            } وإلا إذا (new_configure_اندازه) {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 */
                wind->requested.logical_لوړوالی = لوړوالی + (insets.سر + insets.bottom);

                إذا (wind->scale_منزل_display) {
                    wind->requested.pixel_لوړوالی = ټکی_منزل_Pixel(کړکۍ, wind->requested.logical_لوړوالی);
                }
            }
        } وإلا {
            /* If we're a fixed-size, non-maximized window, we know our size for sure.
             * Always assume the configure is wrong.
             */
            إذا (!wind->scale_منزل_display) {
                پلنوالی = wind->requested.logical_پلنوالی = کړکۍ->floating.w;
                لوړوالی = wind->requested.logical_لوړوالی = کړکۍ->floating.h;
            } وإلا {
                wind->requested.pixel_پلنوالی = کړکۍ->floating.w;
                wind->requested.pixel_لوړوالی = کړکۍ->floating.h;
                پلنوالی = wind->requested.logical_پلنوالی = Pixel_منزل_ټکی(کړکۍ, کړکۍ->floating.w);
                لوړوالی = wind->requested.logical_لوړوالی = Pixel_منزل_ټکی(کړکۍ, کړکۍ->floating.h);
            }
            پلنوالی = SDL_max(پلنوالی - (insets.کیڼ + insets.ښی), 1);
            لوړوالی = SDL_max(لوړوالی - (insets.سر + insets.bottom), 1);
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
                ApplyGeometryLimits(کړکۍ, wind->requested.logical_پلنوالی, wind->requested.logical_لوړوالی, &wind->requested.logical_پلنوالی, &wind->requested.logical_لوړوالی);
            } وإلا {
                ApplyGeometryLimits(کړکۍ, wind->requested.pixel_پلنوالی, wind->requested.pixel_لوړوالی, &wind->requested.pixel_پلنوالی, &wind->requested.pixel_لوړوالی);

                wind->requested.logical_پلنوالی = Pixel_منزل_ټکی(کړکۍ, wind->requested.pixel_پلنوالی);
                wind->requested.logical_لوړوالی = Pixel_منزل_ټکی(کړکۍ, wind->requested.pixel_لوړوالی);
            }
        }
    } وإلا {
        // Fullscreen windows know their exact size.
        إذا (پلنوالی == 0 || لوړوالی == 0) {
            پلنوالی = wind->requested.logical_پلنوالی;
            لوړوالی = wind->requested.logical_لوړوالی;
        } وإلا {
            wind->requested.logical_پلنوالی = پلنوالی;
            wind->requested.logical_لوړوالی = لوړوالی;
        }

        إذا (wind->scale_منزل_display) {
            wind->requested.pixel_پلنوالی = ټکی_منزل_Pixel(کړکۍ, پلنوالی);
            wind->requested.pixel_لوړوالی = ټکی_منزل_Pixel(کړکۍ, لوړوالی);
        }
    }

    wind->وروستی_configure.پلنوالی = پلنوالی;
    wind->وروستی_configure.لوړوالی = لوړوالی;
    wind->وروستی_configure.insets_apply = insets_apply;
    wind->floating = floating;
    wind->suspended = suspended;
    wind->فعال = فعال;
    کړکۍ->tiled = tiled;
}

ساكن فراغ handle_xdg_toplevel_close(فراغ *معلومات, بنية xdg_toplevel *xdg_toplevel)
{
    SDL_کړکۍ_معلومات *کړکۍ = (SDL_کړکۍ_معلومات *)معلومات;
    SDL_Send_کړکۍ_Event(کړکۍ->sdlwindow, SDL_EVENT_کړکۍ_CLOSE_REQUESTED, 0, 0);
}

ساكن فراغ handle_xdg_toplevel_configure_bounds(فراغ *معلومات,
                                                 بنية xdg_toplevel *xdg_toplevel,
                                                 int32_t پلنوالی, int32_t لوړوالی)
{
    SDL_کړکۍ_معلومات *کړکۍ = (SDL_کړکۍ_معلومات *)معلومات;
    کړکۍ->toplevel_bounds.پلنوالی = پلنوالی;
    کړکۍ->toplevel_bounds.لوړوالی = لوړوالی;
}

ساكن فراغ handle_xdg_toplevel_wm_capabilities(فراغ *معلومات,
                                                بنية xdg_toplevel *xdg_toplevel,
                                                بنية wl_array *capabilities)
{
    SDL_کړکۍ_معلومات *wind = (SDL_کړکۍ_معلومات *)معلومات;
    تعداد xdg_toplevel_wm_capabilities *wm_cap;

    wind->wm_caps = 0;

    wl_array_for_each (wm_cap, capabilities) {
        بدل (*wm_cap) {
        حالة XDG_TOPLEVEL_WM_CAPABILITIES_کړکۍ_MENU:
            wind->wm_caps |= WAYLAND_WM_CAPS_کړکۍ_MENU;
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

ساكن فراغ handle_xdg_popup_configure(فراغ *معلومات,
                                       بنية xdg_popup *xdg_popup,
                                       int32_t x,
                                       int32_t y,
                                       int32_t پلنوالی,
                                       int32_t لوړوالی)
{
    SDL_کړکۍ_معلومات *wind = (SDL_کړکۍ_معلومات *)معلومات;
    صحيح دننه_واټن_x = 0, دننه_واټن_y = 0;

    // Adjust the position if it was offset for libdecor
    Adjust_Popup_دننه_واټن(wind->sdlwindow, &دننه_واټن_x, &دننه_واټن_y);
    x -= دننه_واټن_x;
    y -= دننه_واټن_y;

    /* This happens when the compositor indicates that the size is
     * up to the client, so use the cached window size here.
     */
    إذا (پلنوالی == 0 || لوړوالی == 0) {
        پلنوالی = wind->sdlwindow->floating.w;
        لوړوالی = wind->sdlwindow->floating.h;
    }

    /* Don't apply the supplied dimensions if they haven't changed from the last configuration
     * event, or a newer size set programmatically can be overwritten by old data.
     */
    إذا (پلنوالی != wind->وروستی_configure.پلنوالی || لوړوالی != wind->وروستی_configure.لوړوالی) {
        wind->requested.logical_پلنوالی = پلنوالی;
        wind->requested.logical_لوړوالی = لوړوالی;

        إذا (wind->scale_منزل_display) {
            wind->requested.pixel_پلنوالی = ټکی_منزل_Pixel(wind->sdlwindow, پلنوالی);
            wind->requested.pixel_لوړوالی = ټکی_منزل_Pixel(wind->sdlwindow, لوړوالی);
        }
    }

    إذا (wind->scale_منزل_display) {
        x = ټکی_منزل_Pixel(wind->sdlwindow->پلار, x);
        y = ټکی_منزل_Pixel(wind->sdlwindow->پلار, y);
    }

    SDL_Send_کړکۍ_Event(wind->sdlwindow, SDL_EVENT_کړکۍ_MOVED, x, y);

    wind->وروستی_configure.پلنوالی = پلنوالی;
    wind->وروستی_configure.لوړوالی = لوړوالی;

    إذا (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_CONFIGURE) {
        wind->shell_surface_حالت = WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_چوکاټ;
    }
}

ساكن فراغ handle_xdg_popup_بشپړ(فراغ *معلومات, بنية xdg_popup *xdg_popup)
{
    SDL_کړکۍ_معلومات *کړکۍ = (SDL_کړکۍ_معلومات *)معلومات;
    SDL_Send_کړکۍ_Event(کړکۍ->sdlwindow, SDL_EVENT_کړکۍ_CLOSE_REQUESTED, 0, 0);
}

ساكن فراغ handle_xdg_popup_repositioned(فراغ *معلومات,
                                          بنية xdg_popup *xdg_popup,
                                          uint32_t token)
{
    // No-op, configure does all the work we care about
}

ساكن ثابت بنية xdg_popup_listener _xdg_popup_listener = {
    handle_xdg_popup_configure,
    handle_xdg_popup_بشپړ,
    handle_xdg_popup_repositioned
};

ساكن فراغ handle_xdg_toplevel_decoration_configure(فراغ *معلومات,
                                                     بنية zxdg_toplevel_decoration_v1 *zxdg_toplevel_decoration_v1,
                                                     uint32_t ډېرپېښ)
{
    SDL_کړکۍ *کړکۍ = (SDL_کړکۍ *)معلومات;
    SDL_کړکۍ_معلومات *دننی = کړکۍ->دننی;
    SDL_VideoDevice *device = SDL_GetVideoDevice();

    /* If the compositor tries to force CSD anyway, bail on direct XDG support
     * and fall back to libdecor, it will handle these events from then on.
     *
     * To do this we have to fully unmap, then map with libdecor loaded.
     */
    إذا (ډېرپېښ == ZXDG_TOPLEVEL_DECORATION_V1_ډېرپېښ_CLIENT_SIDE) {
        إذا (کړکۍ->flags & SDL_کړکۍ_BORDERLESS) {
            // borderless windows do request CSD, so we got what we wanted
            أرجع;
        }
        إذا (!Wayland_بارول_Libdecor(دننی->wayland_معلومات, true)) {
            // libdecor isn't available, so no borders for you... oh well
            أرجع;
        }
        WAYLAND_wl_display_roundtrip(دننی->wayland_معلومات->display);

        Wayland_Hide_کړکۍ(device, کړکۍ);
        دننی->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR;
        Wayland_Show_کړکۍ(device, کړکۍ);
    }
}

ساكن ثابت بنية zxdg_toplevel_decoration_v1_listener xdg_toplevel_decoration_listener = {
    handle_xdg_toplevel_decoration_configure
};

#که_تعریف_شوی HAVE_LIBDECOR_H
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
ساكن فراغ OverrideLibdecorLimits(SDL_کړکۍ *کړکۍ)
{
#که_تعریف_شوی SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    إذا (!libdecor_چوکاټ_get_min_content_اندازه) {
        libdecor_چوکاټ_سېټ_min_content_اندازه(کړکۍ->دننی->shell_surface.libdecor.چوکاټ, کړکۍ->min_w, کړکۍ->min_h);
    }
#وإلاإذا !SDL_LIBDECOR_CHECK_نسخه(0, 2, 0)
    libdecor_چوکاټ_سېټ_min_content_اندازه(کړکۍ->دننی->shell_surface.libdecor.چوکاټ, کړکۍ->min_w, کړکۍ->min_h);
#د_که_پای
}

/*
 * NOTE: Retrieves the minimum content size limits, if the function for doing so is available.
 *       On versions of libdecor that lack the minimum content size retrieval function, this
 *       function is a no-op.
 *
 *       Can be replaced with a direct call if the minimum required version of libdecor is raised
 *       to 0.1.2 or higher.
 */
ساكن فراغ Libdecor_Get_Min_Content_اندازه(بنية libdecor_چوکاټ *چوکاټ, صحيح *min_w, صحيح *min_h)
{
#که_تعریف_شوی SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    إذا (libdecor_چوکاټ_get_min_content_اندازه != عدم) {
        libdecor_چوکاټ_get_min_content_اندازه(چوکاټ, min_w, min_h);
    }
#وإلاإذا SDL_LIBDECOR_CHECK_نسخه(0, 2, 0)
    libdecor_چوکاټ_get_min_content_اندازه(چوکاټ, min_w, min_h);
#د_که_پای
}

ساكن فراغ decoration_چوکاټ_configure(بنية libdecor_چوکاټ *چوکاټ,
                                       بنية libdecor_configuration *configuration,
                                       فراغ *user_معلومات_2)
{
    SDL_کړکۍ_معلومات *wind = (SDL_کړکۍ_معلومات *)user_معلومات_2;
    SDL_کړکۍ *کړکۍ = wind->sdlwindow;

    تعداد libdecor_کړکۍ_state کړکۍ_state;
    صحيح پلنوالی, لوړوالی;

    bool فعال = false;
    bool fullscreen = false;
    bool maximized = false;
    bool tiled = false;
    bool suspended = false;
    bool resizing = false;
    wind->toplevel_constraints = 0;

    ساكن ثابت تعداد libdecor_کړکۍ_state tiled_حالتونه = (LIBDECOR_کړکۍ_STATE_TILED_کیڼ | LIBDECOR_کړکۍ_STATE_TILED_ښی |
                                                            LIBDECOR_کړکۍ_STATE_TILED_سر | LIBDECOR_کړکۍ_STATE_TILED_BOTTOM);

    إذا (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_CONFIGURE) {
        Libdecor_Get_Min_Content_اندازه(چوکاټ, &wind->system_limits.min_پلنوالی_2, &wind->system_limits.min_لوړوالی_2);
    }

    // Window State
    إذا (libdecor_configuration_get_کړکۍ_state(configuration, &کړکۍ_state)) {
        fullscreen = (کړکۍ_state & LIBDECOR_کړکۍ_STATE_FULLSCREEN) != 0;
        maximized = (کړکۍ_state & LIBDECOR_کړکۍ_STATE_MAXIMIZED) != 0;
        فعال = (کړکۍ_state & LIBDECOR_کړکۍ_STATE_فعال) != 0;
        tiled = (کړکۍ_state & tiled_حالتونه) != 0;
#إذا SDL_LIBDECOR_CHECK_نسخه(0, 2, 0)
        suspended = (کړکۍ_state & LIBDECOR_کړکۍ_STATE_SUSPENDED) != 0;
#د_که_پای
#إذا SDL_LIBDECOR_CHECK_نسخه(0, 3, 0)
        resizing = (کړکۍ_state & LIBDECOR_کړکۍ_STATE_RESIZING) != 0;

        إذا (کړکۍ_state & LIBDECOR_کړکۍ_STATE_CONSTRAINED_کیڼ) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_کیڼ;
        }
        إذا (کړکۍ_state & LIBDECOR_کړکۍ_STATE_CONSTRAINED_ښی) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_ښی;
        }
        إذا (کړکۍ_state & LIBDECOR_کړکۍ_STATE_CONSTRAINED_سر) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_سر;
        }
        إذا (کړکۍ_state & LIBDECOR_کړکۍ_STATE_CONSTRAINED_BOTTOM) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM;
        }
#د_که_پای
    }
    ثابت bool floating = !(fullscreen || maximized || tiled);

    Update_کړکۍ_Fullscreen(کړکۍ, fullscreen);

    /* Always send a maximized/restore event; if the event is redundant it will
     * automatically be discarded (see src/events/SDL_windowevents.c)
     *
     * No, we do not get minimize events from libdecor, however, the minimized
     * state can be programmatically set. The meaning of 'minimized' is compositor
     * dependent, but in general, we can assume that the flag should remain set until
     * the next focused configure event occurs.
     */
    إذا (فعال || !(کړکۍ->flags & SDL_کړکۍ_MINIMIZED)) {
        إذا (کړکۍ->flags & SDL_کړکۍ_MINIMIZED) {
            // If we were minimized, send a restored event before possibly sending maximized.
            SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_RESTORED, 0, 0);
        }
        SDL_Send_کړکۍ_Event(کړکۍ,
                            (maximized && !fullscreen) ? SDL_EVENT_کړکۍ_MAXIMIZED : SDL_EVENT_کړکۍ_RESTORED,
                            0, 0);
    }

    /* For fullscreen or fixed-size windows we know our size.
     * Always assume the configure is wrong.
     */
    إذا (fullscreen) {
        إذا (!libdecor_configuration_get_content_اندازه(configuration, چوکاټ, &پلنوالی, &لوړوالی)) {
            پلنوالی = wind->requested.logical_پلنوالی;
            لوړوالی = wind->requested.logical_لوړوالی;
        } وإلا {
            // Fullscreen windows know their exact size.
            wind->requested.logical_پلنوالی = پلنوالی;
            wind->requested.logical_لوړوالی = لوړوالی;

            إذا (wind->scale_منزل_display) {
                wind->requested.pixel_پلنوالی = ټکی_منزل_Pixel(کړکۍ, پلنوالی);
                wind->requested.pixel_لوړوالی = ټکی_منزل_Pixel(کړکۍ, لوړوالی);
            }
        }
    } وإلا {
        إذا (!(کړکۍ->flags & SDL_کړکۍ_RESIZABLE) && !maximized) {
            /* If we're a fixed-size, non-maximized window, we know our size for sure.
             * Always assume the configure is wrong.
             */
            إذا (!wind->scale_منزل_display) {
                پلنوالی = wind->requested.logical_پلنوالی = کړکۍ->floating.w;
                لوړوالی = wind->requested.logical_لوړوالی = کړکۍ->floating.h;
            } وإلا {
                wind->requested.pixel_پلنوالی = کړکۍ->floating.w;
                wind->requested.pixel_لوړوالی = کړکۍ->floating.h;
                پلنوالی = wind->requested.logical_پلنوالی = Pixel_منزل_ټکی(کړکۍ, کړکۍ->floating.w);
                لوړوالی = wind->requested.logical_لوړوالی = Pixel_منزل_ټکی(کړکۍ, کړکۍ->floating.h);
            }

            OverrideLibdecorLimits(کړکۍ);
        } وإلا {
            /* XXX: The libdecor cairo plugin sends bogus content sizes that add the
             *      height of the title bar when transitioning from a fixed-size to
             *      floating state. Ignore the sent window dimensions in this case,
             *      in favor of the cached value to avoid the window increasing in
             *      size after every state transition.
             *
             *      https://gitlab.freedesktop.org/libdecor/libdecor/-/issues/34
             */
            إذا ((floating && (!wind->floating && !(کړکۍ->flags & SDL_کړکۍ_BORDERLESS))) ||
                !libdecor_configuration_get_content_اندازه(configuration, چوکاټ, &پلنوالی, &لوړوالی)) {
                پلنوالی = 0;
                لوړوالی = 0;
            }

            ثابت bool new_configure_اندازه = پلنوالی != wind->وروستی_configure.پلنوالی || لوړوالی != wind->وروستی_configure.لوړوالی;
            DetermineResizeAxis(wind, پلنوالی, لوړوالی, resizing);

            إذا (!پلنوالی) {
                /* This happens when we're being restored from a non-floating state,
                 * or the compositor indicates that the size is up to the client, so
                 * used the cached window size here.
                 */
                إذا (floating) {
                    پلنوالی = کړکۍ->floating.w;

                    // Clamp the window to the toplevel bounds, if any are set.
                    إذا (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_CONFIGURE && wind->toplevel_bounds.پلنوالی) {
                        پلنوالی = SDL_min(wind->toplevel_bounds.پلنوالی, پلنوالی);
                    }
                } وإلا {
                    پلنوالی = کړکۍ->windowed.w;
                }

                إذا (!wind->scale_منزل_display) {
                    wind->requested.logical_پلنوالی = پلنوالی;
                } وإلا {
                    wind->requested.pixel_پلنوالی = پلنوالی;
                    پلنوالی = wind->requested.logical_پلنوالی = Pixel_منزل_ټکی(کړکۍ, پلنوالی);
                }
            } وإلا {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 *
                 * If a client takes a long time to present the first frame after creating the window, a
                 * configure event to set the suspended state may arrive with the content size increased
                 * by the decoration dimensions, which should also be ignored.
                 */
                إذا (new_configure_اندازه &&
                    !(wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_چوکاټ && wind->suspended != suspended)) {
                    wind->requested.logical_پلنوالی = پلنوالی;

                    إذا (wind->scale_منزل_display) {
                        wind->requested.pixel_پلنوالی = ټکی_منزل_Pixel(کړکۍ, پلنوالی);
                    }
                }
            }

            إذا (!لوړوالی) {
                /* This happens when we're being restored from a non-floating state,
                 * or the compositor indicates that the size is up to the client, so
                 * used the cached window size here.
                 */
                إذا (floating) {
                    لوړوالی = کړکۍ->floating.h;

                    // Clamp the window to the toplevel bounds, if any are set.
                    إذا (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_CONFIGURE && wind->toplevel_bounds.لوړوالی) {
                        لوړوالی = SDL_min(wind->toplevel_bounds.لوړوالی, لوړوالی);
                    }
                } وإلا {
                    لوړوالی = کړکۍ->windowed.h;
                }

                إذا (!wind->scale_منزل_display) {
                    wind->requested.logical_لوړوالی = لوړوالی;
                } وإلا {
                    wind->requested.pixel_لوړوالی = لوړوالی;
                    لوړوالی = wind->requested.logical_لوړوالی = Pixel_منزل_ټکی(کړکۍ, لوړوالی);
                }
            } وإلا {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 *
                 * If a client takes a long time to present the first frame after creating the window, a
                 * configure event to set the suspended state may arrive with the content size increased
                 * by the decoration dimensions, which should also be ignored.
                 */
                إذا (new_configure_اندازه &&
                    !(wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_چوکاټ && wind->suspended != suspended)) {
                    wind->requested.logical_لوړوالی = لوړوالی;

                    إذا (wind->scale_منزل_display) {
                        wind->requested.pixel_لوړوالی = ټکی_منزل_Pixel(کړکۍ, لوړوالی);
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
                ApplyGeometryLimits(کړکۍ, wind->requested.logical_پلنوالی, wind->requested.logical_لوړوالی, &wind->requested.logical_پلنوالی, &wind->requested.logical_لوړوالی);
            } وإلا {
                ApplyGeometryLimits(کړکۍ, wind->requested.pixel_پلنوالی, wind->requested.pixel_لوړوالی, &wind->requested.pixel_پلنوالی, &wind->requested.pixel_لوړوالی);

                wind->requested.logical_پلنوالی = Pixel_منزل_ټکی(کړکۍ, wind->requested.pixel_پلنوالی);
                wind->requested.logical_لوړوالی = Pixel_منزل_ټکی(کړکۍ, wind->requested.pixel_لوړوالی);
            }
        }
    }

    // Store the new state.
    ثابت bool started_resize = !wind->resizing && resizing;
    wind->وروستی_configure.پلنوالی = پلنوالی;
    wind->وروستی_configure.لوړوالی = لوړوالی;
    wind->floating = floating;
    wind->suspended = suspended;
    wind->فعال = فعال;
    کړکۍ->tiled = tiled;
    wind->resizing = resizing;

    // Update the window manager capabilities.
#إذا SDL_LIBDECOR_CHECK_نسخه(0, 3, 0)
    تعداد libdecor_wm_capabilities caps;
#که_تعریف_شوی SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    إذا (libdecor_چوکاټ_get_wm_capabilities) {
        caps = libdecor_چوکاټ_get_wm_capabilities(wind->shell_surface.libdecor.چوکاټ);
#وإلا
    caps = libdecor_چوکاټ_get_wm_capabilities(wind->shell_surface.libdecor.چوکاټ);
    {
#د_که_پای
        wind->wm_caps = 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_کړکۍ_MENU ? WAYLAND_WM_CAPS_کړکۍ_MENU : 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_MAXIMIZE ? WAYLAND_WM_CAPS_MAXIMIZE : 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_FULLSCREEN ? WAYLAND_WM_CAPS_FULLSCREEN : 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_MINIMIZE ? WAYLAND_WM_CAPS_MINIMIZE : 0;
    }
#د_که_پای

    إذا (!wind->resizing || started_resize) {
        /* Calculate the new window geometry and commit the changes on the libdecor side.
         *
         * XXX: This will potentially leave un-acked configurations, but libdecor invalidates the
         *      configuration upon returning from the frame event, so there is nothing that can be
         *      done, unless libdecor adds the ability to copy or refcount the configuration state
         *      to apply later.
         */
        Configure_کړکۍ_Geometry(کړکۍ);
        بنية libdecor_state *state = libdecor_state_new(wind->current.logical_پلنوالی, wind->current.logical_لوړوالی);
        libdecor_چوکاټ_commit(چوکاټ, state, configuration);
        libdecor_state_free(state);

        // Always send an exposure event during a new frame to ensure forward progress if the frame callback already occurred.
        إذا (started_resize) {
            SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_EXPOSED, 0, 0);
        }
    }

    إذا (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_CONFIGURE) {
        wind->shell_surface_حالت = WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_چوکاټ;
    }
}

ساكن فراغ decoration_چوکاټ_close(بنية libdecor_چوکاټ *چوکاټ, فراغ *user_معلومات_2)
{
    SDL_Send_کړکۍ_Event(((SDL_کړکۍ_معلومات *)user_معلومات_2)->sdlwindow, SDL_EVENT_کړکۍ_CLOSE_REQUESTED, 0, 0);
}

ساكن فراغ decoration_چوکاټ_commit(بنية libdecor_چوکاټ *چوکاټ, فراغ *user_معلومات_2)
{
    /* libdecor decoration subsurfaces are synchronous, so the client needs to
     * commit a frame to trigger an update of the decoration surfaces.
     */
    SDL_کړکۍ_معلومات *wind = (SDL_کړکۍ_معلومات *)user_معلومات_2;
    إذا (!wind->suspended && wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_SHOWN) {
        SDL_Send_کړکۍ_Event(wind->sdlwindow, SDL_EVENT_کړکۍ_EXPOSED, 0, 0);
    }
}

ساكن فراغ decoration_dismiss_popup(بنية libdecor_چوکاټ *چوکاټ, ثابت حرف *seat_name, فراغ *user_معلومات_2)
{
    // NOP
}

#إذا SDL_LIBDECOR_CHECK_نسخه(0, 3, 0)
ساكن فراغ decoration_چوکاټ_bounds(بنية libdecor_چوکاټ *چوکاټ, صحيح پلنوالی, صحيح لوړوالی, فراغ *user_معلومات_2)
{
    SDL_کړکۍ_معلومات *کړکۍ = (SDL_کړکۍ_معلومات *)user_معلومات_2;
    کړکۍ->toplevel_bounds.پلنوالی = پلنوالی;
    کړکۍ->toplevel_bounds.لوړوالی = لوړوالی;
}
#د_که_پای

ساكن بنية libdecor_چوکاټ_interface libdecor_چوکاټ_interface = {
    decoration_چوکاټ_configure,
    decoration_چوکاټ_close,
    decoration_چوکاټ_commit,
    decoration_dismiss_popup,
#إذا SDL_LIBDECOR_CHECK_نسخه(0, 3, 0)
    decoration_چوکاټ_bounds
#د_که_پای
};
#د_که_پای

ساكن فراغ Wayland_Handle_Preferred_Scale_بدل_شوی(SDL_کړکۍ_معلومات *کړکۍ_معلومات_2, مزدوج ضریب)
{
    ثابت مزدوج old_ضریب = کړکۍ_معلومات_2->scale_ضریب_2;

    // Round the scale factor if viewports aren't available.
    إذا (!کړکۍ_معلومات_2->viewport) {
        ضریب = SDL_ceil(ضریب);
    }

    إذا (ضریب != old_ضریب) {
        کړکۍ_معلومات_2->scale_ضریب_2 = ضریب;

        إذا (کړکۍ_معلومات_2->scale_منزل_display) {
            /* If the window is in the floating state with a user/application specified size, calculate the new
             * logical size from the backbuffer size. Otherwise, use the fixed underlying logical size to calculate
             * the new backbuffer dimensions.
             */
            إذا (کړکۍ_معلومات_2->floating) {
                /* Some compositors will send a configure event immediately after a scale event, however,
                 * this event can contain the old logical size, and should be ignored, or the window can
                 * incorrectly change size when moved between displays with differing scale factors.
                 *
                 * Store the last requested logical size as the last configure size, so a configure event
                 * with the old size will be ignored. Configure sizes are in window geometry space,
                 * so subtract any border insets.
                 */
                BorderInsets insets;
                GetBorderInsets(کړکۍ_معلومات_2->sdlwindow, &insets);
                کړکۍ_معلومات_2->وروستی_configure.پلنوالی = SDL_max(کړکۍ_معلومات_2->requested.logical_پلنوالی - (insets.کیڼ + insets.ښی), 1);
                کړکۍ_معلومات_2->وروستی_configure.لوړوالی = SDL_max(کړکۍ_معلومات_2->requested.logical_لوړوالی - (insets.سر + insets.bottom), 1);

                کړکۍ_معلومات_2->requested.logical_پلنوالی = Pixel_منزل_ټکی(کړکۍ_معلومات_2->sdlwindow, کړکۍ_معلومات_2->requested.pixel_پلنوالی);
                کړکۍ_معلومات_2->requested.logical_لوړوالی = Pixel_منزل_ټکی(کړکۍ_معلومات_2->sdlwindow, کړکۍ_معلومات_2->requested.pixel_لوړوالی);
            } وإلا {
                کړکۍ_معلومات_2->requested.pixel_پلنوالی = ټکی_منزل_Pixel(کړکۍ_معلومات_2->sdlwindow, کړکۍ_معلومات_2->requested.logical_پلنوالی);
                کړکۍ_معلومات_2->requested.pixel_لوړوالی = ټکی_منزل_Pixel(کړکۍ_معلومات_2->sdlwindow, کړکۍ_معلومات_2->requested.logical_لوړوالی);
            }
        }

        إذا (کړکۍ_معلومات_2->sdlwindow->flags & SDL_کړکۍ_لوړ_PIXEL_DENSITY || کړکۍ_معلومات_2->scale_منزل_display) {
            Configure_کړکۍ_Geometry(کړکۍ_معلومات_2->sdlwindow);
            Commit_Libdecor_چوکاټ(کړکۍ_معلومات_2->sdlwindow);
        }
    }
}

ساكن فراغ Wayland_Maybe_Update_Scale_ضریب(SDL_کړکۍ_معلومات *کړکۍ)
{
    مزدوج ضریب;
    صحيح i;

    /* If the fractional scale protocol is present or the core protocol supports the
     * preferred buffer scale event, the compositor will explicitly tell the application
     * what scale it wants via these events, so don't try to determine the scale factor
     * from which displays the surface has entered.
     */
    إذا (کړکۍ->fractional_scale || wl_surface_get_نسخه(کړکۍ->surface) >= WL_SURFACE_PREFERRED_بفر_SCALE_SINCE_نسخه) {
        أرجع;
    }

    إذا (کړکۍ->عدد_outputs != 0) {
        // Check every display's factor, use the highest
        ضریب = 0.0;
        لكل (i = 0; i < کړکۍ->عدد_outputs; i++) {
            SDL_Display_معلومات *دننی = کړکۍ->outputs[i];
            ضریب = SDL_max(ضریب, دننی->scale_ضریب_2);
        }
    } وإلا {
        // All outputs removed, just fall back.
        ضریب = کړکۍ->scale_ضریب_2;
    }

    Wayland_Handle_Preferred_Scale_بدل_شوی(کړکۍ, ضریب);
}

فراغ Wayland_Remove_Output_From_کړکۍ(SDL_کړکۍ_معلومات *کړکۍ, SDL_Display_معلومات *display_معلومات)
{
    لكل (صحيح i = 0; i < کړکۍ->عدد_outputs; i++) {
        إذا (کړکۍ->outputs[i] == display_معلومات) { // remove this one
            إذا (i == (کړکۍ->عدد_outputs - 1)) {
                کړکۍ->outputs[i] = عدم;
            } وإلا {
                SDL_memmove(&کړکۍ->outputs[i],
                            &کړکۍ->outputs[i + 1],
                            حجم(SDL_Display_معلومات *) * ((کړکۍ->عدد_outputs - i) - 1));
            }
            کړکۍ->عدد_outputs--;
            i--;
        }
    }

    إذا (کړکۍ->عدد_outputs == 0) {
        SDL_free(کړکۍ->outputs);
        کړکۍ->outputs = عدم;
    } وإلا إذا (!کړکۍ->is_fullscreen || کړکۍ->عدد_outputs == 1) {
        Wayland_Update_کړکۍ_Position(کړکۍ->sdlwindow);
        Wayland_Maybe_Update_Scale_ضریب(کړکۍ);
    }
}

ساكن فراغ handle_surface_enter(فراغ *معلومات, بنية wl_surface *surface, بنية wl_output *output)
{
    SDL_کړکۍ_معلومات *کړکۍ = معلومات;
    SDL_Display_معلومات *دننی = wl_output_get_user_معلومات(output);
    SDL_Display_معلومات **new_outputs;

    إذا (!SDL_WAYLAND_own_output(output) || !SDL_WAYLAND_own_surface(surface)) {
        أرجع;
    }

    new_outputs = SDL_realloc(کړکۍ->outputs,
                              حجم(SDL_Display_معلومات *) * (کړکۍ->عدد_outputs + 1));
    إذا (!new_outputs) {
        أرجع;
    }
    کړکۍ->outputs = new_outputs;
    کړکۍ->outputs[کړکۍ->عدد_outputs++] = دننی;

    // Update the scale factor after the move so that fullscreen outputs are updated.
    إذا (!کړکۍ->is_fullscreen || کړکۍ->عدد_outputs == 1) {
        Wayland_Update_کړکۍ_Position(کړکۍ->sdlwindow);
        Wayland_Maybe_Update_Scale_ضریب(کړکۍ);
    }
}

ساكن فراغ handle_surface_leave(فراغ *معلومات, بنية wl_surface *surface, بنية wl_output *output)
{
    SDL_کړکۍ_معلومات *کړکۍ = (SDL_کړکۍ_معلومات *)معلومات;

    إذا (!SDL_WAYLAND_own_output(output) || !SDL_WAYLAND_own_surface(surface)) {
        أرجع;
    }

    Wayland_Remove_Output_From_کړکۍ(کړکۍ, (SDL_Display_معلومات *)wl_output_get_user_معلومات(output));
}

ساكن فراغ handle_surface_preferred_بفر_scale(فراغ *معلومات, بنية wl_surface *wl_surface, int32_t ضریب)
{
    SDL_کړکۍ_معلومات *wind = معلومات;

    /* The spec is unclear on how this interacts with the fractional scaling protocol,
     * so, for now, assume that the fractional scaling protocol takes priority and
     * only listen to this event if the fractional scaling protocol is not present.
     */
    إذا (!wind->fractional_scale) {
        Wayland_Handle_Preferred_Scale_بدل_شوی(معلومات, (مزدوج)ضریب);
    }
}

ساكن فراغ handle_surface_preferred_بفر_transform(فراغ *معلومات, بنية wl_surface *wl_surface, uint32_t transform)
{
    // Nothing to do here.
}

ساكن ثابت بنية wl_surface_listener surface_listener = {
    handle_surface_enter,
    handle_surface_leave,
    handle_surface_preferred_بفر_scale,
    handle_surface_preferred_بفر_transform
};

ساكن فراغ handle_fractional_scale_preferred(فراغ *معلومات, بنية wp_fractional_scale_v1 *wp_fractional_scale_v1, uint32_t scale)
{
    ثابت مزدوج ضریب = (مزدوج)scale / 120.; // 120 is a magic number defined in the spec as a common denominator
    Wayland_Handle_Preferred_Scale_بدل_شوی(معلومات, ضریب);
}

ساكن ثابت بنية wp_fractional_scale_v1_listener fractional_scale_listener = {
    handle_fractional_scale_preferred
};

ساكن فراغ frog_preferred_metadata_handler(فراغ *معلومات, بنية frog_color_managed_surface *frog_color_managed_surface, uint32_t transfer_function,
                                            uint32_t output_display_primary_red_x, uint32_t output_display_primary_red_y,
                                            uint32_t output_display_primary_green_x, uint32_t output_display_primary_green_y,
                                            uint32_t output_display_primary_blue_x, uint32_t output_display_primary_blue_y,
                                            uint32_t output_white_ټکی_x, uint32_t output_white_ټکی_y,
                                            uint32_t max_luminance, uint32_t min_luminance,
                                            uint32_t max_ډک_چوکاټ_luminance)
{
    SDL_کړکۍ_معلومات *wind = (SDL_کړکۍ_معلومات *)معلومات;
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
    حالة FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_SCRGB_خطي:
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
    SDL_سېټ_کړکۍ_HDRProperties(wind->sdlwindow, &HDR, true);
}

ساكن ثابت بنية frog_color_managed_surface_listener frog_surface_listener = {
    frog_preferred_metadata_handler
};


ساكن فراغ handle_surface_feedback_preferred_changed2(فراغ *معلومات,
                                                       بنية wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback_v1,
                                                       uint32_t بې_اغېزه_عنصر_hi, uint32_t بې_اغېزه_عنصر_lo)
{
    SDL_کړکۍ_معلومات *wind = (SDL_کړکۍ_معلومات *)معلومات;
    Wayland_Get_Color_Info_For_کړکۍ(wind, false);
}

ساكن فراغ handle_surface_feedback_preferred_بدل_شوی(فراغ *معلومات,
                                                      بنية wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback_v1,
                                                      uint32_t بې_اغېزه_عنصر)
{
    handle_surface_feedback_preferred_changed2(معلومات, wp_color_management_surface_feedback_v1, 0, بې_اغېزه_عنصر);
}

ساكن ثابت بنية wp_color_management_surface_feedback_v1_listener color_management_surface_feedback_listener = {
    handle_surface_feedback_preferred_بدل_شوی,
    handle_surface_feedback_preferred_changed2
};

ساكن فراغ Wayland_سېټ_Keyboard_Focus(SDL_کړکۍ *کړکۍ, bool سېټ_focus)
{
    SDL_کړکۍ *toplevel = کړکۍ;

    // Find the toplevel parent
    طالما (SDL_کړکۍ_IS_POPUP(toplevel)) {
        toplevel = toplevel->پلار;
    }

    toplevel->keyboard_focus = کړکۍ;

    إذا (سېټ_focus && !کړکۍ->is_hiding && !کړکۍ->is_destroying) {
        SDL_سېټ_Keyboard_Focus(کړکۍ);
    }
}

bool Wayland_سېټ_کړکۍ_موندنه_Test(SDL_کړکۍ *کړکۍ, bool enabled)
{
    أرجع true; // just succeed, the real work is done elsewhere.
}

ساكن بنية xdg_toplevel *Get_Toplevel_For_کړکۍ(SDL_کړکۍ_معلومات *wind)
{
    إذا (wind) {
        /* Libdecor crashes on attempts to unset the parent by passing null, which is allowed by the
         * toplevel spec, so just use the raw xdg-toplevel instead (that's what libdecor does
         * internally anyways).
         */
#که_تعریف_شوی HAVE_LIBDECOR_H
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.چوکاټ) {
            أرجع libdecor_چوکاټ_get_xdg_toplevel(wind->shell_surface.libdecor.چوکاټ);
        } وإلا
#د_که_پای
            إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
                أرجع wind->shell_surface.xdg.toplevel.xdg_toplevel;
            }
    }

    أرجع عدم;
}

bool Wayland_سېټ_کړکۍ_پلار(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_کړکۍ *پلار_کړکۍ)
{
    SDL_کړکۍ_معلومات *ماشوم_معلومات = کړکۍ->دننی;
    SDL_کړکۍ_معلومات *پلار_معلومات = پلار_کړکۍ ? پلار_کړکۍ->دننی : عدم;

    ماشوم_معلومات->reparenting_required = false;

    إذا (پلار_معلومات && پلار_معلومات->shell_surface_حالت != WAYLAND_SHELL_SURFACE_حالت_SHOWN) {
        // Need to wait for the parent to become mapped, or it's the same as setting a null parent.
        ماشوم_معلومات->reparenting_required = true;
        أرجع true;
    }

    بنية xdg_toplevel *ماشوم_toplevel = Get_Toplevel_For_کړکۍ(ماشوم_معلومات);
    بنية xdg_toplevel *پلار_toplevel = Get_Toplevel_For_کړکۍ(پلار_معلومات);

    إذا (ماشوم_toplevel) {
        xdg_toplevel_سېټ_پلار(ماشوم_toplevel, پلار_toplevel);
    }

    أرجع true;
}

bool Wayland_سېټ_کړکۍ_Modal(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool modal)
{
    SDL_Video_معلومات *viddata = _this->دننی;
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    SDL_کړکۍ_معلومات *پلار_معلومات = کړکۍ->پلار->دننی;

    إذا (پلار_معلومات->shell_surface_حالت != WAYLAND_SHELL_SURFACE_حالت_SHOWN) {
        // Need to wait for the parent to become mapped before changing modal status.
        معلومات->reparenting_required = true;
        أرجع true;
    } وإلا {
        معلومات->reparenting_required = false;
    }

    بنية xdg_toplevel *toplevel = Get_Toplevel_For_کړکۍ(معلومات);

    إذا (toplevel) {
        إذا (viddata->xdg_wm_dialog_v1) {
            إذا (modal) {
                إذا (!معلومات->xdg_dialog_v1) {
                    معلومات->xdg_dialog_v1 = xdg_wm_dialog_v1_get_xdg_dialog(viddata->xdg_wm_dialog_v1, toplevel);
                }

                xdg_dialog_v1_سېټ_modal(معلومات->xdg_dialog_v1);
            } وإلا إذا (معلومات->xdg_dialog_v1) {
                xdg_dialog_v1_unset_modal(معلومات->xdg_dialog_v1);
            }
        }
    }

    أرجع true;
}

ساكن فراغ Wayland_ثبتوونکی_Toplevel_For_Session(SDL_کړکۍ_معلومات *معلومات)
{
    بنية xdg_toplevel *toplevel = Get_Toplevel_For_کړکۍ(معلومات);
    إذا (!toplevel) {
        أرجع;
    }

    ثابت حرف *id = SDL_GetStringProperty(معلومات->sdlwindow->props, SDL_PROP_کړکۍ_WAYLAND_کړکۍ_ID_STRING, عدم);
    إذا (id && *id != '\0') {
        SDL_VideoDevice *viddev = SDL_GetVideoDevice();
        SDL_Video_معلومات *viddata = viddev->دننی;

        إذا (viddata->xdg_toplevel_نښان_manager) {
            xdg_toplevel_نښان_manager_v1_سېټ_toplevel_نښان(viddata->xdg_toplevel_نښان_manager, toplevel, id);
        }

        إذا (viddata->xdg_session_manager) {
            Wayland_CreateSession(viddata);

            إذا (viddata->xdg_session) {
                CHECK_PARAM (true) {
                    // Windows added to a session must not have a duplicate ID string, or a protocol error will result.
                    لكل (SDL_کړکۍ *w = viddev->windows; w; w = w->بل) {
                        SDL_کړکۍ_معلومات *d = w->دننی;
                        إذا (d->session_id && SDL_strcmp(d->session_id, id) == 0) {
                            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Duplicate window ID string %s found; window will not be added to session", id);
                            أرجع;
                        }
                    }
                }

                معلومات->xdg_toplevel_session = xdg_session_v1_restore_toplevel(viddata->xdg_session, toplevel, id);
                معلومات->session_id = SDL_strdup(id);
            }
        }
    }
}

ساكن فراغ Wayland_DestroyToplevelSession(SDL_کړکۍ_معلومات *معلومات)
{
    SDL_Video_معلومات *viddata = معلومات->wayland_معلومات;

    إذا (معلومات->xdg_toplevel_session) {
        ثابت حرف *id = SDL_GetStringProperty(معلومات->sdlwindow->props, SDL_PROP_کړکۍ_WAYLAND_کړکۍ_ID_STRING, عدم);

        // If the ID string was cleared, remove the window from the session.
        إذا (!id || *id == '\0') {
            xdg_session_v1_remove_toplevel(viddata->xdg_session, معلومات->session_id);
        }

        xdg_toplevel_session_v1_destroy(معلومات->xdg_toplevel_session);
        معلومات->xdg_toplevel_session = عدم;

        SDL_free(معلومات->session_id);
        معلومات->session_id = عدم;
    }
}

ساكن فراغ show_hide_sync_handler(فراغ *معلومات, بنية wl_callback *callback, uint32_t callback_معلومات)
{
    // Get the window from the ID as it may have been destroyed
    SDL_کړکۍ_ID کړکۍ_ID = (SDL_کړکۍ_ID)((uintptr_t)معلومات);
    SDL_کړکۍ *کړکۍ = SDL_Get_کړکۍ_From_ID(کړکۍ_ID);

    إذا (کړکۍ && کړکۍ->دننی) {
        SDL_کړکۍ_معلومات *wind = کړکۍ->دننی;
        wind->show_hide_sync_required = false;
    }

    wl_callback_destroy(callback);
}

ساكن بنية wl_callback_listener show_hide_sync_listener = {
    show_hide_sync_handler
};

ساكن فراغ exported_handle_handler(فراغ *معلومات, بنية zxdg_exported_v2 *zxdg_exported_v2, ثابت حرف *handle)
{
    SDL_کړکۍ_معلومات *wind = (SDL_کړکۍ_معلومات *)معلومات;
    SDL_PropertiesID props = SDL_Get_کړکۍ_Properties(wind->sdlwindow);

    SDL_سېټ_String_Property(props, SDL_PROP_کړکۍ_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, handle);
}

ساكن بنية zxdg_exported_v2_listener exported_v2_listener = {
    exported_handle_handler
};

فراغ Wayland_Show_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_Video_معلومات *c = _this->دننی;
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    SDL_PropertiesID props = SDL_Get_کړکۍ_Properties(کړکۍ);

    // Custom surfaces don't get toplevels and are always considered 'shown'; nothing to do here.
    إذا (معلومات->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
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
    إذا (کړکۍ->پلار) {
        إذا (کړکۍ->پلار->دننی->shell_surface_حالت != WAYLAND_SHELL_SURFACE_حالت_SHOWN) {
            معلومات->shell_surface_حالت = WAYLAND_SHELL_SURFACE_حالت_SHOW_PENDING;
            أرجع;
        }
    }

    // Always roundtrip to ensure there are no pending buffer attachments.
    افعل {
        WAYLAND_wl_display_roundtrip(c->display);
    } طالما (معلومات->show_hide_sync_required);

    معلومات->shell_surface_حالت = WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_CONFIGURE;

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
    wl_surface_attach(معلومات->surface, عدم, 0, 0);
    wl_surface_commit(معلومات->surface);

    // Create the shell surface and map the toplevel/popup
#که_تعریف_شوی HAVE_LIBDECOR_H
    إذا (معلومات->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        معلومات->shell_surface.libdecor.چوکاټ = libdecor_decorate(c->shell.libdecor,
                                                               معلومات->surface,
                                                               &libdecor_چوکاټ_interface,
                                                               معلومات);
        إذا (!معلومات->shell_surface.libdecor.چوکاټ) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Failed to create libdecor frame!");
        } وإلا {
            libdecor_چوکاټ_سېټ_app_id(معلومات->shell_surface.libdecor.چوکاټ, معلومات->app_id);
            libdecor_چوکاټ_map(معلومات->shell_surface.libdecor.چوکاټ);
            إذا (کړکۍ->flags & SDL_کړکۍ_BORDERLESS) {
                // Note: Calling this with 'true' immediately after mapping will cause the libdecor Cairo plugin to crash.
                libdecor_چوکاټ_سېټ_visibility(معلومات->shell_surface.libdecor.چوکاټ, false);
            }

            إذا (c->zxdg_exporter_v2) {
                معلومات->exported = zxdg_exporter_v2_export_toplevel(c->zxdg_exporter_v2, معلومات->surface);
                zxdg_exported_v2_جمع_کړه_listener(معلومات->exported, &exported_v2_listener, معلومات);
            }

            إذا (c->xdg_toplevel_icon_manager_v1 && معلومات->xdg_toplevel_icon_v1) {
                xdg_toplevel_icon_manager_v1_سېټ_icon(_this->دننی->xdg_toplevel_icon_manager_v1,
                                                      libdecor_چوکاټ_get_xdg_toplevel(معلومات->shell_surface.libdecor.چوکاټ),
                                                      معلومات->xdg_toplevel_icon_v1);
            }

            SDL_سېټ_اشاره_ګر_Property(props, SDL_PROP_کړکۍ_WAYLAND_XDG_SURFACE_اشاره_ګر, libdecor_چوکاټ_get_xdg_surface(معلومات->shell_surface.libdecor.چوکاټ));
            SDL_سېټ_اشاره_ګر_Property(props, SDL_PROP_کړکۍ_WAYLAND_XDG_TOPLEVEL_اشاره_ګر, libdecor_چوکاټ_get_xdg_toplevel(معلومات->shell_surface.libdecor.چوکاټ));
        }
    } وإلا
#د_که_پای
    إذا (معلومات->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL || معلومات->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        معلومات->shell_surface.xdg.surface = xdg_wm_بنسټ_get_xdg_surface(c->shell.xdg, معلومات->surface);
        xdg_surface_سېټ_user_معلومات(معلومات->shell_surface.xdg.surface, معلومات);
        xdg_surface_جمع_کړه_listener(معلومات->shell_surface.xdg.surface, &_xdg_surface_listener, معلومات);
        SDL_سېټ_اشاره_ګر_Property(SDL_Get_کړکۍ_Properties(کړکۍ), SDL_PROP_کړکۍ_WAYLAND_XDG_SURFACE_اشاره_ګر, معلومات->shell_surface.xdg.surface);

        إذا (معلومات->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
            SDL_کړکۍ *پلار = کړکۍ->پلار;
            SDL_کړکۍ_معلومات *پلار_معلومات = پلار->دننی;
            بنية xdg_surface *پلار_xdg_surface = عدم;
            صحيح position_x = 0, position_y = 0;

            // Configure the popup parameters
#که_تعریف_شوی HAVE_LIBDECOR_H
            إذا (پلار_معلومات->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                پلار_xdg_surface = libdecor_چوکاټ_get_xdg_surface(پلار_معلومات->shell_surface.libdecor.چوکاټ);
            } وإلا
#د_که_پای
            إذا (پلار_معلومات->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL ||
                    پلار_معلومات->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
                پلار_xdg_surface = پلار_معلومات->shell_surface.xdg.surface;
            }

            // Set up the positioner for the popup and configure the constraints
            معلومات->shell_surface.xdg.popup.xdg_positioner = xdg_wm_بنسټ_create_positioner(c->shell.xdg);
            xdg_positioner_سېټ_anchor(معلومات->shell_surface.xdg.popup.xdg_positioner, XDG_POSITIONER_ANCHOR_سر_کیڼ);
            SDL_Rect پلار_geometry;
            Get_کړکۍ_Geometry(پلار->دننی, &پلار_geometry);
            xdg_positioner_سېټ_anchor_rect(معلومات->shell_surface.xdg.popup.xdg_positioner, 0, 0, پلار_geometry.w, پلار_geometry.h);

            ثابت Uint32 constraint = کړکۍ->constrain_popup ? (XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_SLIDE_X | XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_SLIDE_Y) : XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_NONE;
            xdg_positioner_سېټ_constraint_adjustment(معلومات->shell_surface.xdg.popup.xdg_positioner, constraint);
            xdg_positioner_سېټ_gravity(معلومات->shell_surface.xdg.popup.xdg_positioner, XDG_POSITIONER_GRAVITY_BOTTOM_ښی);
            xdg_positioner_سېټ_اندازه(معلومات->shell_surface.xdg.popup.xdg_positioner, معلومات->current.logical_پلنوالی, معلومات->current.logical_لوړوالی);

            // Set the popup initial position
            position_x = کړکۍ->وروستی_position_pending ? کړکۍ->pending.x : کړکۍ->x;
            position_y = کړکۍ->وروستی_position_pending ? کړکۍ->pending.y : کړکۍ->y;
            EnsurePopupPositionIsValid(کړکۍ, &position_x, &position_y);
            إذا (معلومات->scale_منزل_display) {
                position_x = Pixel_منزل_ټکی(کړکۍ->پلار, position_x);
                position_y = Pixel_منزل_ټکی(کړکۍ->پلار, position_y);
            }
            Adjust_Popup_دننه_واټن(کړکۍ, &position_x, &position_y);
            xdg_positioner_سېټ_دننه_واټن(معلومات->shell_surface.xdg.popup.xdg_positioner, position_x, position_y);

            // Assign the popup role
            معلومات->shell_surface.xdg.popup.xdg_popup = xdg_surface_get_popup(معلومات->shell_surface.xdg.surface,
                                                                                پلار_xdg_surface,
                                                                                معلومات->shell_surface.xdg.popup.xdg_positioner);
            xdg_popup_جمع_کړه_listener(معلومات->shell_surface.xdg.popup.xdg_popup, &_xdg_popup_listener, معلومات);

            إذا (کړکۍ->flags & SDL_کړکۍ_TOOLTIP) {
                بنية wl_region *region;

                // Tooltips can't be interacted with, so turn off the input region to avoid blocking anything behind them
                region = wl_compositor_create_region(c->compositor);
                wl_region_جمع_کړه(region, 0, 0, 0, 0);
                wl_surface_سېټ_ننوت_region(معلومات->surface, region);
                wl_region_destroy(region);
            } وإلا إذا ((کړکۍ->flags & SDL_کړکۍ_POPUP_MENU) && !(کړکۍ->flags & SDL_کړکۍ_NOT_FOCUSABLE)) {
                Wayland_سېټ_Keyboard_Focus(کړکۍ, true);
            }

            SDL_سېټ_اشاره_ګر_Property(props, SDL_PROP_کړکۍ_WAYLAND_XDG_POPUP_اشاره_ګر, معلومات->shell_surface.xdg.popup.xdg_popup);
            SDL_سېټ_اشاره_ګر_Property(props, SDL_PROP_کړکۍ_WAYLAND_XDG_POSITIONER_اشاره_ګر, معلومات->shell_surface.xdg.popup.xdg_positioner);
        } وإلا {
            معلومات->shell_surface.xdg.toplevel.xdg_toplevel = xdg_surface_get_toplevel(معلومات->shell_surface.xdg.surface);
            xdg_toplevel_سېټ_app_id(معلومات->shell_surface.xdg.toplevel.xdg_toplevel, معلومات->app_id);
            xdg_toplevel_جمع_کړه_listener(معلومات->shell_surface.xdg.toplevel.xdg_toplevel, &toplevel_listener_xdg, معلومات);

            // Create the window decorations
            إذا (c->decoration_manager) {
                معلومات->server_decoration = zxdg_decoration_manager_v1_get_toplevel_decoration(c->decoration_manager, معلومات->shell_surface.xdg.toplevel.xdg_toplevel);
                zxdg_toplevel_decoration_v1_جمع_کړه_listener(معلومات->server_decoration, &xdg_toplevel_decoration_listener, کړکۍ);
                ثابت تعداد zxdg_toplevel_decoration_v1_ډېرپېښ ډېرپېښ = !(کړکۍ->flags & SDL_کړکۍ_BORDERLESS) ? ZXDG_TOPLEVEL_DECORATION_V1_ډېرپېښ_SERVER_SIDE : ZXDG_TOPLEVEL_DECORATION_V1_ډېرپېښ_CLIENT_SIDE;
                zxdg_toplevel_decoration_v1_سېټ_ډېرپېښ(معلومات->server_decoration, ډېرپېښ);
            }

            إذا (c->zxdg_exporter_v2) {
                معلومات->exported = zxdg_exporter_v2_export_toplevel(c->zxdg_exporter_v2, معلومات->surface);
                zxdg_exported_v2_جمع_کړه_listener(معلومات->exported, &exported_v2_listener, معلومات);
            }

            إذا (c->xdg_toplevel_icon_manager_v1 && معلومات->xdg_toplevel_icon_v1) {
                xdg_toplevel_icon_manager_v1_سېټ_icon(_this->دننی->xdg_toplevel_icon_manager_v1,
                                                      معلومات->shell_surface.xdg.toplevel.xdg_toplevel,
                                                      معلومات->xdg_toplevel_icon_v1);
            }

            SDL_سېټ_اشاره_ګر_Property(props, SDL_PROP_کړکۍ_WAYLAND_XDG_TOPLEVEL_اشاره_ګر, معلومات->shell_surface.xdg.toplevel.xdg_toplevel);
        }
    }

    // Restore state that was set prior to this call
    Wayland_ثبتوونکی_Toplevel_For_Session(معلومات);
    Wayland_سېټ_کړکۍ_پلار(_this, کړکۍ, کړکۍ->پلار);

    إذا (کړکۍ->flags & SDL_کړکۍ_MODAL) {
        Wayland_سېټ_کړکۍ_Modal(_this, کړکۍ, true);
    }

    Wayland_سېټ_کړکۍ_Title(_this, کړکۍ);

    /* We have to wait until the surface gets a "configure" event, or use of
     * this surface will fail. This is a new rule for xdg_shell.
     */
#که_تعریف_شوی HAVE_LIBDECOR_H
    إذا (معلومات->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (معلومات->shell_surface.libdecor.چوکاټ) {
            طالما (معلومات->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_CONFIGURE) {
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
#د_که_پای
        إذا (معلومات->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP || معلومات->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        /* Unlike libdecor we need to call this explicitly to prevent a deadlock.
         * libdecor will call this as part of their configure event!
         * -flibit
         */
        wl_surface_commit(معلومات->surface);
        إذا (معلومات->shell_surface.xdg.surface) {
            طالما (معلومات->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_CONFIGURE) {
                إذا (WAYLAND_wl_display_dispatch(c->display) < 0) {
                    إذا (!Wayland_HandleDisplayDisconnected(_this)) {
                        أرجع;
                    }
                }
            }
        }
    } وإلا {
        // Nothing to see here, just commit.
        wl_surface_commit(معلومات->surface);
    }

    // Make sure the window can't be resized to 0, or it can be spuriously closed by the window manager.
    معلومات->system_limits.min_پلنوالی_2 = SDL_max(معلومات->system_limits.min_پلنوالی_2, 1);
    معلومات->system_limits.min_لوړوالی_2 = SDL_max(معلومات->system_limits.min_لوړوالی_2, 1);

    /* Unlike the rest of window state we have to set this _after_ flushing the
     * display, because we need to create the decorations before possibly hiding
     * them immediately afterward.
     */
#که_تعریف_شوی HAVE_LIBDECOR_H
    إذا (معلومات->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        // Libdecor plugins can enforce minimum window sizes, so adjust if the initial window size is too small.
        إذا (کړکۍ->windowed.w < معلومات->system_limits.min_پلنوالی_2 ||
            کړکۍ->windowed.h < معلومات->system_limits.min_لوړوالی_2) {

            // Warn if the window frame will be larger than the content surface.
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO,
                        "Window dimensions (%i, %i) are smaller than the system enforced minimum (%i, %i); window borders will be larger than the content surface.",
                        کړکۍ->windowed.w, کړکۍ->windowed.h, معلومات->system_limits.min_پلنوالی_2, معلومات->system_limits.min_لوړوالی_2);

            معلومات->current.logical_پلنوالی = SDL_max(کړکۍ->windowed.w, معلومات->system_limits.min_پلنوالی_2);
            معلومات->current.logical_لوړوالی = SDL_max(کړکۍ->windowed.h, معلومات->system_limits.min_لوړوالی_2);
            Commit_Libdecor_چوکاټ(کړکۍ);
        }
    }
#د_که_پای
    Wayland_سېټ_کړکۍ_Resizable(_this, کړکۍ, !!(کړکۍ->flags & SDL_کړکۍ_RESIZABLE));

    // We're finally done putting the window together, raise if possible
    إذا (c->activation_manager && SDL_GetHintBoolean(SDL_HINT_کړکۍ_ACTIVATE_WHEN_SHOWN, true)) {
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
                                       معلومات->surface);

            // Clear this variable, per the protocol's request
            SDL_unsetenv_unsafe("XDG_ACTIVATION_TOKEN");
        } وإلا {
            // Try to generate an activation token for this window.
            Wayland_Raise_کړکۍ(_this, کړکۍ);
        }
    } وإلا {
        // Clear the ignored activation token, as it won't be used.
        SDL_unsetenv_unsafe("XDG_ACTIVATION_TOKEN");
    }

    // No frame callback on an external surface, as it may already have one attached.
    إذا (!(کړکۍ->flags & SDL_کړکۍ_EXTERNAL)) {
        // Fire a callback when the compositor wants a new frame.
        معلومات->surface_چوکاټ_callback = wl_surface_چوکاټ(معلومات->surface);
        wl_callback_جمع_کړه_listener(معلومات->surface_چوکاټ_callback, &surface_چوکاټ_listener, معلومات);
    }

    معلومات->show_hide_sync_required = true;
    بنية wl_callback *cb = wl_display_sync(_this->دننی->display);
    wl_callback_جمع_کړه_listener(cb, &show_hide_sync_listener, (فراغ *)((uintptr_t)کړکۍ->id));

    معلومات->showing_کړکۍ = true;
    SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_SHOWN, 0, 0);
    معلومات->showing_کړکۍ = false;

    // Send an exposure event to signal that the client should draw.
    SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_EXPOSED, 0, 0);
}

ساكن فراغ Wayland_ReleasePopup(SDL_VideoDevice *_this, SDL_کړکۍ *popup)
{
    SDL_کړکۍ_معلومات *popupdata;

    // Basic sanity checks to weed out the weird popup closures
    إذا (!SDL_ObjectValid(popup, SDL_OBJECT_TYPE_کړکۍ)) {
        أرجع;
    }
    popupdata = popup->دننی;
    إذا (!popupdata) {
        أرجع;
    }

    // This may already be freed by a parent popup!
    إذا (popupdata->shell_surface.xdg.popup.xdg_popup == عدم) {
        أرجع;
    }

    إذا ((popup->flags & SDL_کړکۍ_POPUP_MENU) && !(popup->flags & SDL_کړکۍ_NOT_FOCUSABLE)) {
        SDL_کړکۍ *new_focus;
        ثابت bool سېټ_focus = SDL_ShouldRelinquishPopupFocus(popup, &new_focus);
        Wayland_سېټ_Keyboard_Focus(new_focus, سېټ_focus);
    }

    xdg_popup_destroy(popupdata->shell_surface.xdg.popup.xdg_popup);
    xdg_positioner_destroy(popupdata->shell_surface.xdg.popup.xdg_positioner);
    popupdata->shell_surface.xdg.popup.xdg_popup = عدم;
    popupdata->shell_surface.xdg.popup.xdg_positioner = عدم;

    SDL_PropertiesID props = SDL_Get_کړکۍ_Properties(popup);
    SDL_سېټ_اشاره_ګر_Property(props, SDL_PROP_کړکۍ_WAYLAND_XDG_POPUP_اشاره_ګر, عدم);
    SDL_سېټ_اشاره_ګر_Property(props, SDL_PROP_کړکۍ_WAYLAND_XDG_POSITIONER_اشاره_ګر, عدم);
}

فراغ Wayland_Hide_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_Video_معلومات *معلومات = _this->دننی;
    SDL_کړکۍ_معلومات *wind = کړکۍ->دننی;
    SDL_PropertiesID props = SDL_Get_کړکۍ_Properties(کړکۍ);

    // Custom surfaces have nothing to destroy and are always considered to be 'shown'; nothing to do here.
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        أرجع;
    }

    /* The window was shown, but the sync point hasn't yet been reached.
     * Pump events to avoid a possible protocol violation.
     */
    إذا (wind->show_hide_sync_required) {
        WAYLAND_wl_display_roundtrip(معلومات->display);
    }

    wind->shell_surface_حالت = WAYLAND_SHELL_SURFACE_حالت_HIDDEN;

    إذا (wind->surface_چوکاټ_callback) {
        wl_callback_destroy(wind->surface_چوکاټ_callback);
        wind->surface_چوکاټ_callback = عدم;
    }

    إذا (wind->server_decoration) {
        zxdg_toplevel_decoration_v1_destroy(wind->server_decoration);
        wind->server_decoration = عدم;
    }

    // Clean up the export handle.
    إذا (wind->exported) {
        zxdg_exported_v2_destroy(wind->exported);
        wind->exported = عدم;

        SDL_سېټ_String_Property(props, SDL_PROP_کړکۍ_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, عدم);
    }

    إذا (wind->xdg_dialog_v1) {
        xdg_dialog_v1_destroy(wind->xdg_dialog_v1);
        wind->xdg_dialog_v1 = عدم;
    }

#که_تعریف_شوی HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (wind->shell_surface.libdecor.چوکاټ) {
            libdecor_چوکاټ_unref(wind->shell_surface.libdecor.چوکاټ);

            SDL_سېټ_اشاره_ګر_Property(props, SDL_PROP_کړکۍ_WAYLAND_XDG_SURFACE_اشاره_ګر, عدم);
            SDL_سېټ_اشاره_ګر_Property(props, SDL_PROP_کړکۍ_WAYLAND_XDG_TOPLEVEL_اشاره_ګر, عدم);
        }
    } وإلا
#د_که_پای
    {
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
            Wayland_ReleasePopup(_this, کړکۍ);
        } وإلا إذا (wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            xdg_toplevel_destroy(wind->shell_surface.xdg.toplevel.xdg_toplevel);
            SDL_سېټ_اشاره_ګر_Property(props, SDL_PROP_کړکۍ_WAYLAND_XDG_TOPLEVEL_اشاره_ګر, عدم);
        }

        إذا (wind->shell_surface.xdg.surface) {
            xdg_surface_destroy(wind->shell_surface.xdg.surface);
            SDL_سېټ_اشاره_ګر_Property(props, SDL_PROP_کړکۍ_WAYLAND_XDG_SURFACE_اشاره_ګر, عدم);
        }
    }

    // Attach a null buffer to unmap the surface.
    إذا (wind->ماسک.surface) {
        wl_surface_attach(wind->ماسک.surface, عدم, 0, 0);
        wl_surface_commit(wind->ماسک.surface);
    }
    wl_surface_attach(wind->surface, عدم, 0, 0);
    wl_surface_commit(wind->surface);

    // Need to destroy the session object after unmapping the window, or the state may not be saved.
    Wayland_DestroyToplevelSession(wind);

    SDL_zero(wind->shell_surface);
    SDL_zero(wind->explicit_geometry);
    wind->show_hide_sync_required = true;
    بنية wl_callback *cb = wl_display_sync(_this->دننی->display);
    wl_callback_جمع_کړه_listener(cb, &show_hide_sync_listener, (فراغ *)((uintptr_t)کړکۍ->id));
}

ساكن فراغ handle_xdg_activation_بشپړ(فراغ *معلومات,
                                       بنية xdg_activation_token_v1 *xdg_activation_token_v1,
                                       ثابت حرف *token)
{
    SDL_کړکۍ_معلومات *کړکۍ = معلومات;
    إذا (xdg_activation_token_v1 == کړکۍ->activation_token) {
        xdg_activation_v1_activate(کړکۍ->wayland_معلومات->activation_manager,
                                   token,
                                   کړکۍ->surface);
        xdg_activation_token_v1_destroy(کړکۍ->activation_token);
        کړکۍ->activation_token = عدم;
    }
}

ساكن ثابت بنية xdg_activation_token_v1_listener xdg_activation_listener = {
    handle_xdg_activation_بشپړ
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
ساكن فراغ Wayland_activate_کړکۍ(SDL_Video_معلومات *معلومات, SDL_کړکۍ_معلومات *موخه_wind, bool سېټ_serial)
{
    SDL_WaylandSeat *seat = معلومات->وروستی_implicit_grab_seat;
    SDL_کړکۍ_معلومات *focus = عدم;

    إذا (seat) {
        focus = seat->keyboard.focus;
        إذا (!focus) {
            focus = seat->اشاره_ګر_2.focus;
        }
    }

    بنية wl_surface *requesting_surface = focus ? focus->surface : عدم;

    إذا (معلومات->activation_manager) {
        إذا (موخه_wind->activation_token) {
            // We're about to overwrite this with a new request
            xdg_activation_token_v1_destroy(موخه_wind->activation_token);
        }

        موخه_wind->activation_token = xdg_activation_v1_get_activation_token(معلومات->activation_manager);
        xdg_activation_token_v1_جمع_کړه_listener(موخه_wind->activation_token,
                                             &xdg_activation_listener,
                                             موخه_wind);

        /* Note that we are not setting the app_id here.
         *
         * Hypothetically we could set the app_id from data->classname, but
         * that part of the API is for _external_ programs, not ourselves.
         *
         * -flibit
         */
        إذا (requesting_surface) {
            // This specifies the surface from which the activation request is originating, not the activation target surface.
            xdg_activation_token_v1_سېټ_surface(موخه_wind->activation_token, requesting_surface);
        }
        إذا (سېټ_serial && seat && seat->wl_seat) {
            xdg_activation_token_v1_سېټ_serial(موخه_wind->activation_token, seat->وروستی_implicit_grab_serial, seat->wl_seat);
        }
        xdg_activation_token_v1_commit(موخه_wind->activation_token);
    }
}

فراغ Wayland_Raise_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_Video_معلومات *viddata = _this->دننی;
    SDL_کړکۍ_معلومات *wind = کړکۍ->دننی;

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
    Wayland_activate_کړکۍ(_this->دننی, کړکۍ->دننی, true);
}

bool Wayland_Flash_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_FlashOperation operation)
{
    /* Not setting the serial will specify 'urgency' without switching focus as per
     * https://gitlab.freedesktop.org/wayland/wayland-protocols/-/merge_requests/9#note_854977
     */
    Wayland_activate_کړکۍ(_this->دننی, کړکۍ->دننی, false);
    أرجع true;
}

SDL_Fullscreen_پایله Wayland_سېټ_کړکۍ_Fullscreen(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ,
                                 SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_کړکۍ_معلومات *wind = کړکۍ->دننی;
    بنية wl_output *output = display->دننی->output;

    // Custom surfaces have no toplevel to make fullscreen.
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        أرجع SDL_FULLSCREEN_FAILED;
    }

    // Drop fullscreen leave requests when showing the window.
    إذا (wind->showing_کړکۍ && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        أرجع SDL_FULLSCREEN_SUCCEEDED;
    }

    إذا (wind->show_hide_sync_required) {
        WAYLAND_wl_display_roundtrip(_this->دننی->display);
    }

    // Flushing old events pending a new one, ignore this request.
    إذا (wind->drop_fullscreen_غوښتنې) {
        أرجع SDL_FULLSCREEN_SUCCEEDED;
    }

    wind->drop_fullscreen_غوښتنې = true;
    FlushPendingEvents(کړکۍ);
    wind->drop_fullscreen_غوښتنې = false;

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
        إذا (!کړکۍ->fullscreen_exclusive) {
            إذا (کړکۍ->undefined_x || کړکۍ->undefined_y ||
                (wind->عدد_outputs && !کړکۍ->وروستی_position_pending)) {
                output = عدم;
            }
        }

        // Commit to set any pending size or limit data.
        إذا (fullscreen && wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        سېټ_Fullscreen(کړکۍ, output, !!fullscreen);
    } وإلا إذا (wind->is_fullscreen) {
        /*
         * If the window is already fullscreen, this is likely a request to switch between
         * fullscreen and fullscreen desktop, change outputs, or change the video mode.
         *
         * If the window is already positioned on the target output, just update the
         * window geometry.
         */
        إذا (wind->وروستی_display_ID != display->id) {
            wind->fullscreen_was_positioned = true;
            سېټ_Fullscreen(کړکۍ, output, true);
        } وإلا {
            Configure_کړکۍ_Geometry(کړکۍ);
            Commit_Libdecor_چوکاټ(کړکۍ);

            أرجع SDL_FULLSCREEN_SUCCEEDED;
        }
    }

    أرجع SDL_FULLSCREEN_PENDING;
}

فراغ Wayland_Restore_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *wind = کړکۍ->دننی;

    // Drop restore requests when showing the window.
    إذا (wind->showing_کړکۍ) {
        أرجع;
    }

    // Not currently fullscreen or maximized, and no state pending; nothing to do.
    إذا (!(کړکۍ->flags & (SDL_کړکۍ_FULLSCREEN | SDL_کړکۍ_MAXIMIZED)) &&
        !wind->pending_state_deadline_شمېر) {
        أرجع;
    }

#که_تعریف_شوی HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (!wind->shell_surface.libdecor.چوکاټ) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }
        libdecor_چوکاټ_unset_maximized(wind->shell_surface.libdecor.چوکاټ);
        جمع_کړه_Pending_State_Sync(wind);
    } وإلا
#د_که_پای
        // Note that xdg-shell does NOT provide a way to unset minimize!
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
            إذا (wind->shell_surface.xdg.toplevel.xdg_toplevel == عدم) {
                أرجع; // Can't do anything yet, wait for ShowWindow
            }
            xdg_toplevel_unset_maximized(wind->shell_surface.xdg.toplevel.xdg_toplevel);
            جمع_کړه_Pending_State_Sync(wind);
        }
}

فراغ Wayland_سېټ_کړکۍ_Bordered(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool bordered)
{
    SDL_کړکۍ_معلومات *wind = کړکۍ->دننی;
    ثابت SDL_Video_معلومات *viddata = (ثابت SDL_Video_معلومات *)_this->دننی;

#که_تعریف_شوی HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (wind->shell_surface.libdecor.چوکاټ) {
            libdecor_چوکاټ_سېټ_visibility(wind->shell_surface.libdecor.چوکاټ, bordered);
        }
    } وإلا
#د_که_پای
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        إذا ((viddata->decoration_manager) && (wind->server_decoration)) {
            ثابت تعداد zxdg_toplevel_decoration_v1_ډېرپېښ ډېرپېښ = bordered ? ZXDG_TOPLEVEL_DECORATION_V1_ډېرپېښ_SERVER_SIDE : ZXDG_TOPLEVEL_DECORATION_V1_ډېرپېښ_CLIENT_SIDE;
            zxdg_toplevel_decoration_v1_سېټ_ډېرپېښ(wind->server_decoration, ډېرپېښ);
        }
    }
}

فراغ Wayland_سېټ_کړکۍ_Resizable(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool resizable)
{
    SDL_کړکۍ_معلومات *wind = کړکۍ->دننی;

    /* When changing the resize capability on libdecor windows, the limits must always
     * be reapplied, as when libdecor changes states, it overwrites the values internally.
     */
    سېټ_Min_Max_Dimensions(کړکۍ);
    Commit_Libdecor_چوکاټ(کړکۍ);

    إذا (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_SHOWN) {
        wind->pending_state_commit = true;
    }
}

فراغ Wayland_Maximize_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *wind = کړکۍ->دننی;

    إذا (wind->show_hide_sync_required) {
        WAYLAND_wl_display_roundtrip(_this->دننی->display);
    }

    // Not fullscreen, already maximized, and no state pending; nothing to do.
    إذا (!(کړکۍ->flags & SDL_کړکۍ_FULLSCREEN) && (کړکۍ->flags & SDL_کړکۍ_MAXIMIZED) &&
        !wind->pending_state_deadline_شمېر) {
        أرجع;
    }

#که_تعریف_شوی HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (!wind->shell_surface.libdecor.چوکاټ) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }

        // Commit to set any pending size or limit data.
        إذا (wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        libdecor_چوکاټ_سېټ_maximized(wind->shell_surface.libdecor.چوکاټ);
        جمع_کړه_Pending_State_Sync(wind);
    } وإلا
#د_که_پای
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        إذا (wind->shell_surface.xdg.toplevel.xdg_toplevel == عدم) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }

        // Commit to set any pending size or limit data.
        إذا (wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        xdg_toplevel_سېټ_maximized(wind->shell_surface.xdg.toplevel.xdg_toplevel);
        جمع_کړه_Pending_State_Sync(wind);
    }
}

فراغ Wayland_Minimize_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *wind = کړکۍ->دننی;

    إذا (!(wind->wm_caps & WAYLAND_WM_CAPS_MINIMIZE)) {
        أرجع;
    }

#که_تعریف_شوی HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (!wind->shell_surface.libdecor.چوکاټ) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }
        libdecor_چوکاټ_سېټ_minimized(wind->shell_surface.libdecor.چوکاټ);
        SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_MINIMIZED, 0, 0);
    } وإلا
#د_که_پای
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        إذا (wind->shell_surface.xdg.toplevel.xdg_toplevel == عدم) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }
        xdg_toplevel_سېټ_minimized(wind->shell_surface.xdg.toplevel.xdg_toplevel);
        SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_MINIMIZED, 0, 0);
    }
}

bool Wayland_سېټ_کړکۍ_Mouse_Rect(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_Video_معلومات *معلومات = _this->دننی;

    /* This may look suspiciously like SetWindowGrab, despite SetMouseRect not
     * implicitly doing a grab. And you're right! Wayland doesn't let us mess
     * around with mouse focus whatsoever, so it just happens to be that the
     * work that we can do in these two functions ends up being the same.
     *
     * Just know that this call lets you confine with a rect, SetWindowGrab
     * lets you confine without a rect.
     */
    إذا (!معلومات->اشاره_ګر_constraints) {
        أرجع SDL_سېټ_Error("Failed to grab mouse: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }
    Wayland_Display_Update_اشاره_ګر_Grabs(معلومات, کړکۍ->دننی);
    أرجع true;
}

bool Wayland_سېټ_کړکۍ_Mouse_Grab(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool grabbed)
{
    SDL_Video_معلومات *معلومات = _this->دننی;
    إذا (!معلومات->اشاره_ګر_constraints) {
        أرجع SDL_سېټ_Error("Failed to grab mouse: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }
    Wayland_Display_Update_اشاره_ګر_Grabs(معلومات, کړکۍ->دننی);
    أرجع true;
}

bool Wayland_سېټ_کړکۍ_Keyboard_Grab(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool grabbed)
{
    SDL_Video_معلومات *معلومات = _this->دننی;
    إذا (!معلومات->کلی_inhibitor_manager) {
        أرجع SDL_سېټ_Error("Failed to grab keyboard: compositor lacks support for the required zwp_keyboard_shortcuts_inhibit_manager_v1 protocol");
    }
    Wayland_DisplayUpdateKeyboardGrabs(معلومات, کړکۍ->دننی);
    أرجع true;
}

bool Wayland_Reconfigure_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_کړکۍ_Flags flags)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;

    // Don't try to reconfigure mapped windows, unless they are custom or external.
    إذا (معلومات->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_SHOWN &&
        معلومات->shell_surface_type != WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        // Window is already mapped; abort.
        أرجع false;
    }

    /* The caller guarantees that only one of the GL or Vulkan flags will be set.
     * Note that Vulkan doesn't require any specific configuration, so only EGL
     * objects are added and removed as required.
     */
    إذا (flags & SDL_کړکۍ_OPENGL) {
        إذا (!معلومات->egl_کړکۍ) {
            معلومات->egl_کړکۍ = WAYLAND_wl_egl_کړکۍ_create(معلومات->surface, معلومات->current.pixel_پلنوالی, معلومات->current.pixel_لوړوالی);
        }

#که_تعریف_شوی SDL_VIDEO_OPENGL_EGL
        معلومات->egl_surface = SDL_EGL_CreateSurface(_this, کړکۍ, (Native_کړکۍ_Type)معلومات->egl_کړکۍ);

        إذا (معلومات->egl_surface == EGL_NO_SURFACE) {
            أرجع false; // SDL_EGL_CreateSurface should have set the error.
        }
#د_که_پای

        إذا (!معلومات->gles_بدلون_چوکاټ_event_کتار) {
            معلومات->gles_بدلون_چوکاټ_event_کتار = WAYLAND_wl_display_create_کتار(معلومات->wayland_معلومات->display);
            معلومات->gles_بدلون_چوکاټ_surface_wrapper = WAYLAND_wl_proxy_create_wrapper(معلومات->surface);
            WAYLAND_wl_proxy_سېټ_کتار((بنية wl_proxy *)معلومات->gles_بدلون_چوکاټ_surface_wrapper, معلومات->gles_بدلون_چوکاټ_event_کتار);
            معلومات->gles_بدلون_چوکاټ_callback = wl_surface_چوکاټ(معلومات->gles_بدلون_چوکاټ_surface_wrapper);
            wl_callback_جمع_کړه_listener(معلومات->gles_بدلون_چوکاټ_callback, &gles_بدلون_چوکاټ_listener, معلومات);
        }
    } وإلا {
#که_تعریف_شوی SDL_VIDEO_OPENGL_EGL
        إذا (معلومات->egl_surface) {
            SDL_EGL_DestroySurface(_this, معلومات->egl_surface);
            معلومات->egl_surface = EGL_NO_SURFACE;
        }
#د_که_پای

        إذا (معلومات->egl_کړکۍ) {
            WAYLAND_wl_egl_کړکۍ_destroy(معلومات->egl_کړکۍ);
            معلومات->egl_کړکۍ = عدم;
        }

        إذا (معلومات->gles_بدلون_چوکاټ_callback) {
            wl_callback_destroy(معلومات->gles_بدلون_چوکاټ_callback);
            معلومات->gles_بدلون_چوکاټ_callback = عدم;
        }

        إذا (معلومات->gles_بدلون_چوکاټ_surface_wrapper) {
            WAYLAND_wl_proxy_wrapper_destroy(معلومات->gles_بدلون_چوکاټ_surface_wrapper);
            معلومات->gles_بدلون_چوکاټ_surface_wrapper = عدم;
        }

        إذا (معلومات->gles_بدلون_چوکاټ_event_کتار) {
            WAYLAND_wl_event_کتار_destroy(معلومات->gles_بدلون_چوکاټ_event_کتار);
            معلومات->gles_بدلون_چوکاټ_event_کتار = عدم;
        }
    }

    أرجع true;
}

bool Wayland_Create_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID create_props)
{
    SDL_کړکۍ_معلومات *معلومات;
    SDL_Video_معلومات *c = _this->دننی;
    بنية wl_surface *external_surface = (بنية wl_surface *)SDL_Get_اشاره_ګر_Property(create_props, SDL_PROP_کړکۍ_CREATE_WAYLAND_WL_SURFACE_اشاره_ګر,
                                                                               (بنية wl_surface *)SDL_Get_اشاره_ګر_Property(create_props, "sdl2-compat.external_window", عدم));
    ثابت bool custom_surface_role = (external_surface != عدم) || SDL_GetBooleanProperty(create_props, SDL_PROP_کړکۍ_CREATE_WAYLAND_SURFACE_ROLE_CUSTOM_BOOLEAN, false);
    ثابت bool create_egl_کړکۍ = !!(کړکۍ->flags & SDL_کړکۍ_OPENGL) ||
                                       SDL_GetBooleanProperty(create_props, SDL_PROP_کړکۍ_CREATE_WAYLAND_CREATE_EGL_کړکۍ_BOOLEAN, false);

    معلومات = SDL_calloc(1, حجم(*معلومات));
    إذا (!معلومات) {
        أرجع false;
    }

    کړکۍ->دننی = معلومات;
    معلومات->enable_insets = SDL_GetBooleanProperty(create_props, SDL_PROP_کړکۍ_CREATE_WAYLAND_ENABLE_INSETS_BOOLEAN, false);

    إذا (کړکۍ->x == SDL_WINDOWPOS_UNDEFINED) {
        کړکۍ->x = 0;
    }
    إذا (کړکۍ->y == SDL_WINDOWPOS_UNDEFINED) {
        کړکۍ->y = 0;
    }

    معلومات->wayland_معلومات = c;
    معلومات->sdlwindow = کړکۍ;

    // Default to all capabilities
    معلومات->wm_caps = WAYLAND_WM_CAPS_ALL;

    معلومات->scale_ضریب_2 = 1.0;

    إذا (SDL_کړکۍ_IS_POPUP(کړکۍ)) {
        معلومات->scale_منزل_display = کړکۍ->پلار->دننی->scale_منزل_display;
        معلومات->scale_ضریب_2 = کړکۍ->پلار->دننی->scale_ضریب_2;
        EnsurePopupPositionIsValid(کړکۍ, &کړکۍ->x, &کړکۍ->y);
    } وإلا {
        لكل (صحيح i = 0; i < _this->عدد_displays; i++) {
            معلومات->scale_ضریب_2 = SDL_max(معلومات->scale_ضریب_2, _this->displays[i]->دننی->scale_ضریب_2);
        }
    }

    معلومات->outputs = عدم;
    معلومات->عدد_outputs = 0;
    معلومات->scale_منزل_display = c->scale_منزل_display_enabled;

    // Cache the app_id at creation time, as it may change before the window is mapped.
    معلومات->app_id = SDL_strdup(SDL_GetAppID());

    إذا (!معلومات->scale_منزل_display) {
        معلومات->requested.logical_پلنوالی = کړکۍ->floating.w;
        معلومات->requested.logical_لوړوالی = کړکۍ->floating.h;
    } وإلا {
        معلومات->requested.logical_پلنوالی = Pixel_منزل_ټکی(کړکۍ, کړکۍ->floating.w);
        معلومات->requested.logical_لوړوالی = Pixel_منزل_ټکی(کړکۍ, کړکۍ->floating.h);
        معلومات->requested.pixel_پلنوالی = کړکۍ->floating.w;
        معلومات->requested.pixel_لوړوالی = کړکۍ->floating.h;
    }

    إذا (!external_surface) {
        معلومات->surface = wl_compositor_create_surface(c->compositor);
        wl_surface_جمع_کړه_listener(معلومات->surface, &surface_listener, معلومات);
        wl_surface_سېټ_user_معلومات(معلومات->surface, معلومات);
        SDL_WAYLAND_ثبتوونکی_surface(معلومات->surface);
    } وإلا {
        کړکۍ->flags |= SDL_کړکۍ_EXTERNAL;
        معلومات->surface = external_surface;

        /* External surfaces are registered by being put in a list, as changing tags or userdata
         * can cause problems with external toolkits.
         */
        Wayland_جمع_کړه_کړکۍ_معلومات_منزل_External_List(معلومات);
    }

    /* Always attach a viewport and fractional scale manager if available and the surface is not custom/external,
     * or the custom/external surface was explicitly flagged as high pixel density aware, which signals that the
     * application wants SDL to handle scaling.
     */
    إذا (!custom_surface_role || (کړکۍ->flags & SDL_کړکۍ_لوړ_PIXEL_DENSITY)) {
        إذا (c->viewporter) {
            معلومات->viewport = wp_viewporter_get_viewport(c->viewporter, معلومات->surface);

            // The viewport always uses the entire buffer.
            wp_viewport_سېټ_سرچینه(معلومات->viewport,
                                   wl_fixed_from_int(-1), wl_fixed_from_int(-1),
                                   wl_fixed_from_int(-1), wl_fixed_from_int(-1));
        }
        إذا (c->fractional_scale_manager) {
            معلومات->fractional_scale = wp_fractional_scale_manager_v1_get_fractional_scale(c->fractional_scale_manager, معلومات->surface);
            wp_fractional_scale_v1_جمع_کړه_listener(معلومات->fractional_scale, &fractional_scale_listener, معلومات);
        }
    }

    إذا (!custom_surface_role) {
        إذا (c->wp_color_manager_v1) {
            معلومات->wp_color_management_surface_feedback = wp_color_manager_v1_get_surface_feedback(c->wp_color_manager_v1, معلومات->surface);
            wp_color_management_surface_feedback_v1_جمع_کړه_listener(معلومات->wp_color_management_surface_feedback, &color_management_surface_feedback_listener, معلومات);
            Wayland_Get_Color_Info_For_کړکۍ(معلومات, true);
        } وإلا إذا (c->frog_color_management_factory_v1) {
            معلومات->frog_color_managed_surface = frog_color_management_factory_v1_get_color_managed_surface(c->frog_color_management_factory_v1, معلومات->surface);
            frog_color_managed_surface_جمع_کړه_listener(معلومات->frog_color_managed_surface, &frog_surface_listener, معلومات);
        }

        إذا (c->wp_alpha_modifier_v1) {
            معلومات->wp_alpha_modifier_surface_v1 = wp_alpha_modifier_v1_get_surface(c->wp_alpha_modifier_v1, معلومات->surface);
            wp_alpha_modifier_surface_v1_سېټ_multiplier(معلومات->wp_alpha_modifier_surface_v1, SDL_MAX_UINT32);
        }
    }

    // Must be called before EGL configuration to set the drawable backbuffer size.
    Configure_کړکۍ_Geometry(کړکۍ);

    /* Fire a callback when the compositor wants a new frame rendered.
     * Right now this only matters for OpenGL; we use this callback to add a
     * wait timeout that avoids getting deadlocked by the compositor when the
     * window isn't visible.
     */
    إذا (کړکۍ->flags & SDL_کړکۍ_OPENGL) {
        معلومات->gles_بدلون_چوکاټ_event_کتار = WAYLAND_wl_display_create_کتار(معلومات->wayland_معلومات->display);
        معلومات->gles_بدلون_چوکاټ_surface_wrapper = WAYLAND_wl_proxy_create_wrapper(معلومات->surface);
        WAYLAND_wl_proxy_سېټ_کتار((بنية wl_proxy *)معلومات->gles_بدلون_چوکاټ_surface_wrapper, معلومات->gles_بدلون_چوکاټ_event_کتار);
        معلومات->gles_بدلون_چوکاټ_callback = wl_surface_چوکاټ(معلومات->gles_بدلون_چوکاټ_surface_wrapper);
        wl_callback_جمع_کړه_listener(معلومات->gles_بدلون_چوکاټ_callback, &gles_بدلون_چوکاټ_listener, معلومات);
    }

    إذا (کړکۍ->flags & SDL_کړکۍ_TRANSPARENT) {
        إذا (_this->gl_config.alpha_اندازه == 0) {
            _this->gl_config.alpha_اندازه = 8;
        }
    }

    إذا (create_egl_کړکۍ) {
        معلومات->egl_کړکۍ = WAYLAND_wl_egl_کړکۍ_create(معلومات->surface, معلومات->current.pixel_پلنوالی, معلومات->current.pixel_لوړوالی);
    }

#که_تعریف_شوی SDL_VIDEO_OPENGL_EGL
    إذا (کړکۍ->flags & SDL_کړکۍ_OPENGL) {
        // Create the GLES window surface
        معلومات->egl_surface = SDL_EGL_CreateSurface(_this, کړکۍ, (Native_کړکۍ_Type)معلومات->egl_کړکۍ);

        إذا (معلومات->egl_surface == EGL_NO_SURFACE) {
            أرجع false; // SDL_EGL_CreateSurface should have set error
        }
    }
#د_که_پای

    // We may need to create an idle inhibitor for this new window
    Wayland_SuspendScreenSaver(_this);

    إذا (!custom_surface_role) {
#که_تعریف_شوی HAVE_LIBDECOR_H
        إذا (c->shell.libdecor && !SDL_کړکۍ_IS_POPUP(کړکۍ)) {
            معلومات->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR;
        } وإلا
#د_که_پای
            إذا (c->shell.xdg) {
            إذا (SDL_کړکۍ_IS_POPUP(کړکۍ)) {
                معلومات->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP;
            } وإلا {
                معلومات->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL;
            }
        } // All other cases will be WAYLAND_SURFACE_UNKNOWN
    } وإلا {
        // Roleless and external surfaces are always considered to be in the shown state by the backend.
        معلومات->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_CUSTOM;
        معلومات->shell_surface_حالت = WAYLAND_SHELL_SURFACE_حالت_SHOWN;

        // External windows are presumed to be shown.
        إذا (کړکۍ->flags & SDL_کړکۍ_EXTERNAL) {
            کړکۍ->flags &= ~SDL_کړکۍ_HIDDEN;
        }
    }

    إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_DOUBLE_بفر, false)) {
        معلومات->double_بفر = true;
    }

    SDL_PropertiesID props = SDL_Get_کړکۍ_Properties(کړکۍ);
    SDL_سېټ_اشاره_ګر_Property(props, SDL_PROP_کړکۍ_WAYLAND_DISPLAY_اشاره_ګر, معلومات->wayland_معلومات->display);
    SDL_سېټ_اشاره_ګر_Property(props, SDL_PROP_کړکۍ_WAYLAND_SURFACE_اشاره_ګر, معلومات->surface);
    SDL_سېټ_اشاره_ګر_Property(props, SDL_PROP_کړکۍ_WAYLAND_VIEWPORT_اشاره_ګر, معلومات->viewport);
    SDL_سېټ_اشاره_ګر_Property(props, SDL_PROP_کړکۍ_WAYLAND_EGL_کړکۍ_اشاره_ګر, معلومات->egl_کړکۍ);
    إذا (معلومات->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL || معلومات->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ثابت حرف *کړکۍ_id = SDL_GetStringProperty(create_props, SDL_PROP_کړکۍ_CREATE_WAYLAND_کړکۍ_ID_STRING, عدم);
        إذا (کړکۍ_id && *کړکۍ_id != '\0') {
            SDL_سېټ_String_Property(props, SDL_PROP_کړکۍ_WAYLAND_کړکۍ_ID_STRING, کړکۍ_id);
        }
    }

    معلومات->موندنه_test_پایله = SDL_HITTEST_نورمال;

    أرجع true;
}

فراغ Wayland_سېټ_کړکۍ_Minimum_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    کړکۍ->دننی->limits_بدل_شوی = true;
}

فراغ Wayland_سېټ_کړکۍ_اعظمي_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    کړکۍ->دننی->limits_بدل_شوی = true;
}

فراغ Wayland_سېټ_کړکۍ_Aspect_نسبت(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    کړکۍ->دننی->limits_بدل_شوی = true;
}

bool Wayland_سېټ_کړکۍ_Position(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *wind = کړکۍ->دننی;

    // Only popup windows can be positioned relative to the parent.
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        إذا (wind->shell_surface.xdg.popup.xdg_popup &&
            xdg_popup_get_نسخه(wind->shell_surface.xdg.popup.xdg_popup) < XDG_POPUP_REPOSITION_SINCE_نسخه) {
            أرجع SDL_Unsupported();
        }

        RepositionPopup(کړکۍ, false);
        أرجع true;
    } وإلا إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR || wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        /* Catch up on any pending state before attempting to change the fullscreen window
         * display via a set fullscreen call to make sure the window doesn't have a pending
         * leave fullscreen event that it might override.
         */
        FlushPendingEvents(کړکۍ);

        إذا (wind->is_fullscreen) {
            SDL_VideoDisplay *display = SDL_Get_Video_Display_For_Fullscreen_کړکۍ(کړکۍ);
            إذا (display && wind->وروستی_display_ID != display->id) {
                بنية wl_output *output = display->دننی->output;
                سېټ_Fullscreen(کړکۍ, output, true);

                أرجع true;
            }
        }
    }
    أرجع SDL_سېټ_Error("wayland cannot position non-popup windows");
}

فراغ Wayland_سېټ_کړکۍ_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *wind = کړکۍ->دننی;

    /* Flush any pending state operations, as fullscreen windows do not get
     * explicitly resized, not strictly obeying the size of a maximized window
     * is a protocol violation, and pending restore events might result in a
     * configure event overwriting the requested size.
     *
     * Calling this on a custom surface is informative, so the size must
     * always be passed through.
     */
    FlushPendingEvents(کړکۍ);

    ثابت bool maximized = (کړکۍ->flags & SDL_کړکۍ_MAXIMIZED) != 0;
    ثابت bool resizable_state = !(کړکۍ->flags & (SDL_کړکۍ_MAXIMIZED | SDL_کړکۍ_FULLSCREEN));

    /* Maximized and fullscreen windows don't get resized, and the new size is ignored
     * if this is just to recalculate the min/max or aspect limits on a tiled window.
     *
     * Some compositors will mark tiled windows as maximized. In these cases, the content
     * size is recalculated, but window size itself is left alone, as the spec states that
     * the configure size of a maximized window must be obeyed.
     */
    إذا (resizable_state || (کړکۍ->tiled && !wind->limits_بدل_شوی) ||
        wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {

        // Don't change the window size if maximized and tiled.
        إذا (!maximized) {
            إذا (!wind->scale_منزل_display) {
                wind->requested.logical_پلنوالی = کړکۍ->pending.w;
                wind->requested.logical_لوړوالی = کړکۍ->pending.h;
            } وإلا {
                wind->requested.logical_پلنوالی = Pixel_منزل_ټکی(کړکۍ, کړکۍ->pending.w);
                wind->requested.logical_لوړوالی = Pixel_منزل_ټکی(کړکۍ, کړکۍ->pending.h);
                wind->requested.pixel_پلنوالی = کړکۍ->pending.w;
                wind->requested.pixel_لوړوالی = کړکۍ->pending.h;
            }
        }

        /* If a non-resizable window somehow wound up in the tiled state, store the new
         * size in the floating parameters so the size will be preserved for future
         * configure events.
         *
         * This shouldn't happen, but apparently it can on at least one compositor...
         */
        إذا (کړکۍ->tiled && !(کړکۍ->flags & SDL_کړکۍ_RESIZABLE)) {
            کړکۍ->floating.w = کړکۍ->pending.w;
            کړکۍ->floating.h = کړکۍ->pending.h;
        }
    } وإلا {
        // Can't resize the window.
        کړکۍ->وروستی_اندازه_pending = false;
    }

    wind->limits_بدل_شوی = false;
    إذا (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_SHOWN) {
        wind->pending_state_commit = true;
    }

    // Always recalculate the geometry, as this may be in response to a min/max limit change.
    Configure_کړکۍ_Geometry(کړکۍ);
    Commit_Libdecor_چوکاټ(کړکۍ);
}

فراغ Wayland_Get_کړکۍ_اندازه_دننه_Pixels(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, صحيح *w, صحيح *h)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;

    *w = معلومات->current.pixel_پلنوالی;
    *h = معلومات->current.pixel_لوړوالی;
}

عائم Wayland_Get_کړکۍ_Content_Scale(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *wind = کړکۍ->دننی;

    إذا (کړکۍ->flags & SDL_کړکۍ_لوړ_PIXEL_DENSITY || wind->scale_منزل_display || wind->fullscreen_exclusive) {
        أرجع (عائم)wind->scale_ضریب_2;
    }

    أرجع 1.0f;
}

SDL_DisplayID Wayland_Get_Display_For_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *wind = کړکۍ->دننی;

    إذا (wind) {
        أرجع wind->وروستی_display_ID;
    }

    أرجع 0;
}

bool Wayland_سېټ_کړکۍ_Opacity(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, عائم opacity)
{
    SDL_کړکۍ_معلومات *wind = کړکۍ->دننی;

    إذا (wind->wp_alpha_modifier_surface_v1) {
        ثابت bool is_opaque = !(کړکۍ->flags & SDL_کړکۍ_TRANSPARENT) && opacity == 1.0f;

        إذا (wind->ماسک.mapped && wind->ماسک.opaque != is_opaque) {
            بنية wl_بفر *old_بفر = wind->ماسک.بفر_2;
            wind->ماسک.opaque = is_opaque;
            wind->ماسک.بفر_2 = Wayland_Create_Single_Pixel_بفر(0, 0, 0, is_opaque ? SDL_MAX_UINT32 : 0);

            wl_surface_attach(wind->ماسک.surface, wind->ماسک.بفر_2, 0, 0);
            إذا (wl_surface_get_نسخه(wind->ماسک.surface) >= WL_SURFACE_DAMAGE_بفر_SINCE_نسخه) {
                wl_surface_damage_بفر(wind->ماسک.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
            } وإلا {
                wl_surface_damage(wind->ماسک.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
            }

            إذا (is_opaque) {
                سېټ_Surface_Opaque_Region(wind->ماسک.surface, wind->current.logical_پلنوالی, wind->current.logical_لوړوالی);
            } وإلا {
                سېټ_Surface_Opaque_Region(wind->ماسک.surface, 0, 0);
            }

            wl_surface_commit(wind->ماسک.surface);

            إذا (old_بفر) {
                wl_بفر_destroy(old_بفر);
            }
        }

        إذا (is_opaque) {
            سېټ_Surface_Opaque_Region(wind->surface, wind->current.viewport_پلنوالی, wind->current.viewport_لوړوالی);
        } وإلا {
            سېټ_Surface_Opaque_Region(wind->surface, 0, 0);
        }

        wp_alpha_modifier_surface_v1_سېټ_multiplier(wind->wp_alpha_modifier_surface_v1, (Uint32)((مزدوج)SDL_MAX_UINT32 * (مزدوج)opacity));

        أرجع true;
    }

    أرجع SDL_سېټ_Error("wayland: set window opacity failed; compositor lacks support for the required wp_alpha_modifier_v1 protocol");
}

فراغ Wayland_سېټ_کړکۍ_Title(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *wind = کړکۍ->دننی;
    ثابت حرف *title = کړکۍ->title ? کړکۍ->title : "";

#که_تعریف_شوی HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.چوکاټ) {
        libdecor_چوکاټ_سېټ_title(wind->shell_surface.libdecor.چوکاټ, title);
    } وإلا
#د_که_پای
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
        xdg_toplevel_سېټ_title(wind->shell_surface.xdg.toplevel.xdg_toplevel, title);
    }
}

ساكن صحيح icon_ترتیبول_callback(ثابت فراغ *a, ثابت فراغ *b)
{
    ثابت SDL_Surface *s1 = *(ثابت SDL_Surface **)a;
    ثابت SDL_Surface *s2 = *(ثابت SDL_Surface **)b;

    أرجع (s1->w * s1->h) <= (s2->w * s2->h) ? -1 : 1;
}

bool Wayland_سېټ_کړکۍ_Icon(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_Surface *icon)
{
    SDL_کړکۍ_معلومات *wind = کړکۍ->دننی;
    Wayland_SHMPool *shm_pool = عدم;
    بنية xdg_toplevel *toplevel = عدم;

    إذا (!_this->دننی->xdg_toplevel_icon_manager_v1) {
        أرجع SDL_سېټ_Error("wayland: cannot set icon; required xdg_toplevel_icon_v1 protocol not supported");
    }

    صحيح image_شمېر_2 = 0;
    SDL_Surface **images = SDL_GetSurfaceImages(icon, &image_شمېر_2);
    إذا (!images || !image_شمېر_2) {
        أرجع false;
    }

    // Release the old icon resources.
    إذا (wind->xdg_toplevel_icon_v1) {
        xdg_toplevel_icon_v1_destroy(wind->xdg_toplevel_icon_v1);
        wind->xdg_toplevel_icon_v1 = عدم;
    }

    لكل (صحيح i = 0; i < wind->icon_بفر_شمېر; ++i) {
        wl_بفر_destroy(wind->icon_buffers[i]);
    }
    wind->icon_بفر_شمېر = 0;

    wind->xdg_toplevel_icon_v1 = xdg_toplevel_icon_manager_v1_create_icon(_this->دننی->xdg_toplevel_icon_manager_v1);
    wind->icon_buffers = SDL_realloc(wind->icon_buffers, image_شمېر_2 * حجم(بنية wl_بفر *));
    إذا (!wind->icon_buffers) {
        اذهب failure_cleanup;
    }

    // Calculate the size of the buffer pool.
    size_t pool_اندازه = 0;
    لكل (صحيح i = 0; i < image_شمېر_2; ++i) {
        // Images must be square. Non-square images will be centered.
        ثابت صحيح اندازه = SDL_max(images[i]->w, images[i]->h);
        pool_اندازه += اندازه * اندازه * 4;
    }

    // Sort the images in ascending order by size.
    SDL_qsort(images, image_شمېر_2, حجم(SDL_Surface *), icon_ترتیبول_callback);

    shm_pool = Wayland_AllocSHMPool(pool_اندازه);
    إذا (!shm_pool) {
        SDL_سېټ_Error("wayland: failed to allocate an SHM pool for the icon");
        اذهب failure_cleanup;
    }

    ثابت مزدوج بنسټ_اندازه = (مزدوج)SDL_max(icon->w, icon->h);
    لكل (صحيح i = 0; i < image_شمېر_2; ++i) {
        SDL_Surface *surface = images[i];

        // Choose the largest image for each integer scale, ignoring any below the base size.
        ثابت صحيح level_اندازه = SDL_max(surface->w, surface->h);
        ثابت صحيح scale = (صحيح)SDL_floor((مزدوج)level_اندازه / بنسټ_اندازه);
        إذا (!scale) {
            استمر;
        }

        إذا (surface->format != SDL_PIXELFORMAT_ARGB8888) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
            إذا (!surface) {
                SDL_سېټ_Error("wayland: failed to convert the icon image to ARGB8888 format");
                اذهب failure_cleanup;
            }
        }

        فراغ *بفر_mem;
        بنية wl_بفر *بفر_2 = Wayland_Alloc_بفر_From_Pool(shm_pool, level_اندازه, level_اندازه, &بفر_mem);
        إذا (!بفر_2) {
            // Clean up the temporary conversion surface.
            إذا (surface != images[i]) {
                SDL_DestroySurface(surface);
            }
            SDL_سېټ_Error("wayland: failed to allocate a wl_buffer for the icon");
            اذهب failure_cleanup;
        }

        wind->icon_buffers[wind->icon_بفر_شمېر++] = بفر_2;

        // Center non-square images.
        إذا (surface->w < level_اندازه) {
            SDL_memset(بفر_mem, 0, level_اندازه * level_اندازه * 4);
            بفر_mem = (Uint8 *)بفر_mem + (((level_اندازه - surface->w) / 2) * 4);
        } وإلا إذا (surface->h < level_اندازه) {
            SDL_memset(بفر_mem, 0, level_اندازه * level_اندازه * 4);
            بفر_mem = (Uint8 *)بفر_mem + (((level_اندازه - surface->h) / 2) * (level_اندازه * 4));
        }

        SDL_PremultiplyAlpha(surface->w, surface->h, surface->format, surface->pixels, surface->pitch,
                             SDL_PIXELFORMAT_ARGB8888, بفر_mem, level_اندازه * 4, true);

        xdg_toplevel_icon_v1_جمع_کړه_بفر(wind->xdg_toplevel_icon_v1, بفر_2, scale);

        // Clean up the temporary scaled or conversion surface.
        إذا (surface != images[i]) {
            SDL_DestroySurface(surface);
        }
    }

#که_تعریف_شوی HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.چوکاټ) {
        toplevel = libdecor_چوکاټ_get_xdg_toplevel(wind->shell_surface.libdecor.چوکاټ);
    } وإلا
#د_که_پای
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
        toplevel = wind->shell_surface.xdg.toplevel.xdg_toplevel;
    }

    إذا (toplevel) {
        xdg_toplevel_icon_manager_v1_سېټ_icon(_this->دننی->xdg_toplevel_icon_manager_v1, toplevel, wind->xdg_toplevel_icon_v1);
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

    لكل (صحيح i = 0; i < wind->icon_بفر_شمېر; ++i) {
        wl_بفر_destroy(wind->icon_buffers[i]);
    }
    SDL_free(wind->icon_buffers);
    wind->icon_buffers = عدم;
    wind->icon_بفر_شمېر = 0;

    أرجع false;
}

فراغ *Wayland_Get_کړکۍ_ICCProfile(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, size_t *اندازه)
{
    SDL_کړکۍ_معلومات *wind = کړکۍ->دننی;
    فراغ *ret = عدم;

    إذا (wind->icc_اندازه > 0) {
        فراغ *icc_map = mmap(عدم, wind->icc_اندازه, PROT_READ, MAP_PRIVATE, wind->icc_fd, 0);
        إذا (icc_map != MAP_FAILED) {
            ret = SDL_malloc(wind->icc_اندازه);
            إذا (ret) {
                *اندازه = wind->icc_اندازه;
                SDL_memcpy(ret, icc_map, *اندازه);
            }
            munmap(icc_map, wind->icc_اندازه);
        }
    }

    أرجع ret;
}

bool Wayland_Sync_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *wind = کړکۍ->دننی;

    افعل {
        WAYLAND_wl_display_roundtrip(_this->دننی->display);
    } طالما (wind->pending_state_deadline_شمېر);

    أرجع true;
}

فراغ Wayland_AcceptDragAndDrop(SDL_کړکۍ *کړکۍ, bool accept)
{
    کړکۍ->دننی->مني_drag_and_drop = accept;
}

bool Wayland_سېټ_کړکۍ_Focusable(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool focusable)
{
    إذا (کړکۍ->flags & SDL_کړکۍ_POPUP_MENU) {
        إذا (!(کړکۍ->flags & SDL_کړکۍ_HIDDEN)) {
            إذا (!focusable && (کړکۍ->flags & SDL_کړکۍ_ننوت_FOCUS)) {
                SDL_کړکۍ *new_focus;
                ثابت bool سېټ_focus = SDL_ShouldRelinquishPopupFocus(کړکۍ, &new_focus);
                Wayland_سېټ_Keyboard_Focus(new_focus, سېټ_focus);
            } وإلا إذا (focusable) {
                إذا (SDL_ShouldFocusPopup(کړکۍ)) {
                    Wayland_سېټ_Keyboard_Focus(کړکۍ, true);
                }
            }
        }

        أرجع true;
    }

    أرجع SDL_سېټ_Error("wayland: focus can only be toggled on popup menu windows");
}

فراغ Wayland_Show_کړکۍ_System_Menu(SDL_کړکۍ *کړکۍ, صحيح x, صحيح y)
{
    SDL_کړکۍ_معلومات *wind = کړکۍ->دننی;
    SDL_WaylandSeat *seat = wind->wayland_معلومات->وروستی_implicit_grab_seat;

    إذا (!seat) {
        أرجع;
    }

    إذا (wind->scale_منزل_display) {
        x = Pixel_منزل_ټکی(کړکۍ, x);
        y = Pixel_منزل_ټکی(کړکۍ, y);
    }

#که_تعریف_شوی HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (wind->shell_surface.libdecor.چوکاټ) {
            libdecor_چوکاټ_show_کړکۍ_menu(wind->shell_surface.libdecor.چوکاټ, seat->wl_seat, seat->وروستی_implicit_grab_serial, x, y);
        }
    } وإلا
#د_که_پای
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        إذا (wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            xdg_toplevel_show_کړکۍ_menu(wind->shell_surface.xdg.toplevel.xdg_toplevel, seat->wl_seat, seat->وروستی_implicit_grab_serial, x, y);
        }
    }
}

bool Wayland_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *معلومات = _this->دننی;

#که_تعریف_شوی SDL_USE_LIBDBUS
    إذا (SDL_DBus_ScreensaverInhibit(_this->suspend_screensaver)) {
        أرجع true;
    }
#د_که_پای

    /* The idle_inhibit_unstable_v1 protocol suspends the screensaver
       on a per wl_surface basis, but SDL assumes that suspending
       the screensaver can be done independently of any window.

       To reconcile these differences, we propagate the idle inhibit
       state to each window. If there is no window active, we will
       be able to inhibit idle once the first window is created.
    */
    إذا (معلومات->idle_inhibit_manager) {
        SDL_کړکۍ *کړکۍ = _this->windows;
        طالما (کړکۍ) {
            SDL_کړکۍ_معلومات *win_معلومات = کړکۍ->دننی;

            إذا (_this->suspend_screensaver && !win_معلومات->idle_inhibitor) {
                win_معلومات->idle_inhibitor =
                    zwp_idle_inhibit_manager_v1_create_inhibitor(معلومات->idle_inhibit_manager,
                                                                 win_معلومات->surface);
            } وإلا إذا (!_this->suspend_screensaver && win_معلومات->idle_inhibitor) {
                zwp_idle_inhibitor_v1_destroy(win_معلومات->idle_inhibitor);
                win_معلومات->idle_inhibitor = عدم;
            }

            کړکۍ = کړکۍ->بل;
        }
    }

    أرجع true;
}

فراغ Wayland_Destroy_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_Video_معلومات *معلومات = _this->دننی;
    SDL_کړکۍ_معلومات *wind = کړکۍ->دننی;

    إذا (معلومات && wind) {
        /* Roundtrip before destroying the window to make sure that it has received input leave events, so that
         * no internal structures are left pointing to the destroyed window.
         */
        إذا (wind->show_hide_sync_required) {
            /* Make sure hit test isn't executed during roundtrip */
            کړکۍ->موندنه_test = عدم;
            WAYLAND_wl_display_roundtrip(معلومات->display);
        }

        /* The compositor should have relinquished keyboard, pointer, touch, and tablet tool focus when the toplevel
         * window was destroyed upon being hidden, but there is no guarantee of this, so ensure that all references
         * to the window held by seats are released before destroying the underlying surface and struct.
         */
        Wayland_Display_Remove_کړکۍ_References_From_Seats(معلومات, wind);

        إذا (wind->ماسک.viewport) {
            wp_viewport_destroy(wind->ماسک.viewport);
        }
        إذا (wind->ماسک.بفر_2) {
            wl_بفر_destroy(wind->ماسک.بفر_2);
        }
        إذا (wind->ماسک.subsurface) {
            wl_subsurface_destroy(wind->ماسک.subsurface);
        }
        إذا (wind->ماسک.surface) {
            wl_surface_destroy(wind->ماسک.surface);
        }
#که_تعریف_شوی SDL_VIDEO_OPENGL_EGL
        إذا (wind->egl_surface) {
            SDL_EGL_DestroySurface(_this, wind->egl_surface);
        }
#د_که_پای
        إذا (wind->egl_کړکۍ) {
            WAYLAND_wl_egl_کړکۍ_destroy(wind->egl_کړکۍ);
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

        إذا (wind->gles_بدلون_چوکاټ_callback) {
            wl_callback_destroy(wind->gles_بدلون_چوکاټ_callback);
            WAYLAND_wl_proxy_wrapper_destroy(wind->gles_بدلون_چوکاټ_surface_wrapper);
            WAYLAND_wl_event_کتار_destroy(wind->gles_بدلون_چوکاټ_event_کتار);
        }

        إذا (!(کړکۍ->flags & SDL_کړکۍ_EXTERNAL)) {
            wl_surface_destroy(wind->surface);
        } وإلا {
            Wayland_Remove_کړکۍ_معلومات_From_External_List(wind);
        }

        إذا (wind->xdg_toplevel_icon_v1) {
            xdg_toplevel_icon_v1_destroy(wind->xdg_toplevel_icon_v1);
        }

        لكل (صحيح i = 0; i < wind->icon_بفر_شمېر; ++i) {
            wl_بفر_destroy(wind->icon_buffers[i]);
        }
        SDL_free(wind->icon_buffers);
        wind->icon_بفر_شمېر = 0;

        SDL_free(wind);
    }
    کړکۍ->دننی = عدم;
}

#د_که_پای // SDL_VIDEO_DRIVER_WAYLAND
