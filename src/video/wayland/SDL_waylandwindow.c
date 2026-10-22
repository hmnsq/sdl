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

#اگر_تعریف_شده HAVE_LIBDECOR_H
#ضمن <libdecor.h>
#پایان_اگر

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

ساكن مزدوج Get_پنجره_Scale(SDL_پنجره *پنجره)
{
    أرجع (پنجره->flags & SDL_پنجره_بالا_PIXEL_DENSITY) || پنجره->داخلی->scale_مقصد_display ? پنجره->داخلی->scale_ضریب_2 : 1.0;
}

// These are point->pixel->point round trip safe; the inverse is not round trip safe due to rounding.
ساكن صحيح نقطه_مقصد_Pixel(SDL_پنجره *پنجره, صحيح نقطه)
{
    /* Rounds halfway away from zero as per the Wayland fractional scaling protocol spec.
     * Wayland scale units are in units of 1/120, so the offset is required to correct for
     * rounding errors when using certain scale values.
     */
    أرجع نقطه ? SDL_max((صحيح)SDL_lround((مزدوج)نقطه * Get_پنجره_Scale(پنجره) + 1e-6), 1) : 0;
}

ساكن صحيح Pixel_مقصد_نقطه(SDL_پنجره *پنجره, صحيح pixel)
{
    أرجع pixel ? SDL_max((صحيح)SDL_lround((مزدوج)pixel / Get_پنجره_Scale(پنجره)), 1) : 0;
}

تعداد Wayland_نما_Scale
{
    WAYLAND_نما_SCALE_UNDEFINED,
    WAYLAND_نما_SCALE_ASPECT,
    WAYLAND_نما_SCALE_STRETCH,
    WAYLAND_نما_SCALE_NONE
};

ساكن تعداد Wayland_نما_Scale Get_نما_Scale_روش(فراغ)
{
    ساكن تعداد Wayland_نما_Scale scale_نما_2 = WAYLAND_نما_SCALE_UNDEFINED;

    إذا (scale_نما_2 == WAYLAND_نما_SCALE_UNDEFINED) {
        ثابت حرف *scale_hint = SDL_GetHint(SDL_HINT_VIDEO_WAYLAND_نما_SCALING);

        إذا (scale_hint) {
            إذا (!SDL_strcasecmp(scale_hint, "stretch")) {
                scale_نما_2 = WAYLAND_نما_SCALE_STRETCH;
            } وإلا إذا (!SDL_strcasecmp(scale_hint, "none")) {
                scale_نما_2 = WAYLAND_نما_SCALE_NONE;
            } وإلا {
                scale_نما_2 = WAYLAND_نما_SCALE_ASPECT;
            }
        } وإلا {
            scale_نما_2 = WAYLAND_نما_SCALE_ASPECT;
        }
    }

    أرجع scale_نما_2;
}

تعريفنوع بنية BorderInsets
{
    صحيح چپ;
    صحيح بالاترین;
    صحيح راست;
    صحيح bottom;
} BorderInsets;

// The border insets from the window properties; they only apply to xdg-toplevel windows.
ساكن فراغ GetBorderInsets(SDL_پنجره *پنجره, BorderInsets *insets)
{
    SDL_zerop(insets);
    إذا (!پنجره->داخلی->enable_insets) {
        أرجع;
    }
    إذا (پنجره->داخلی->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        ثابت SDL_PropertiesID props = SDL_Get_پنجره_Properties(پنجره);
        insets->چپ = (صحيح)SDL_clamp(SDL_Get_عدد_Property(props, SDL_PROP_پنجره_WAYLAND_BORDER_INSET_چپ_عدد, 0), 0, SDL_MAX_SINT16);
        insets->بالاترین = (صحيح)SDL_clamp(SDL_Get_عدد_Property(props, SDL_PROP_پنجره_WAYLAND_BORDER_INSET_بالاترین_عدد, 0), 0, SDL_MAX_SINT16);
        insets->راست = (صحيح)SDL_clamp(SDL_Get_عدد_Property(props, SDL_PROP_پنجره_WAYLAND_BORDER_INSET_راست_عدد, 0), 0, SDL_MAX_SINT16);
        insets->bottom = (صحيح)SDL_clamp(SDL_Get_عدد_Property(props, SDL_PROP_پنجره_WAYLAND_BORDER_INSET_BOTTOM_عدد, 0), 0, SDL_MAX_SINT16);
    }
}

ساكن فراغ مجموعه_Min_Max_Dimensions(SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *wind = پنجره->داخلی;
    صحيح min_عرض_2, min_ارتفاع_2, max_عرض_2, max_ارتفاع_2;

    /* Keep the limits off while the window is in a fixed-size state, or the controls
     * to exit that state may be disabled.
     */
    إذا (پنجره->flags & (SDL_پنجره_FULLSCREEN | SDL_پنجره_MAXIMIZED)) {
        min_عرض_2 = 0;
        min_ارتفاع_2 = 0;
        max_عرض_2 = 0;
        max_ارتفاع_2 = 0;
    } وإلا إذا (پنجره->flags & SDL_پنجره_RESIZABLE) {
        صحيح adj_w = SDL_max(پنجره->min_w, wind->system_limits.min_عرض_2);
        صحيح adj_h = SDL_max(پنجره->min_h, wind->system_limits.min_ارتفاع_2);
        إذا (wind->scale_مقصد_display) {
            adj_w = Pixel_مقصد_نقطه(پنجره, adj_w);
            adj_h = Pixel_مقصد_نقطه(پنجره, adj_h);
        }
        min_عرض_2 = adj_w;
        min_ارتفاع_2 = adj_h;

        adj_w = پنجره->max_w ? SDL_max(پنجره->max_w, wind->system_limits.min_عرض_2) : 0;
        adj_h = پنجره->max_h ? SDL_max(پنجره->max_h, wind->system_limits.min_ارتفاع_2) : 0;
        إذا (wind->scale_مقصد_display) {
            adj_w = Pixel_مقصد_نقطه(پنجره, adj_w);
            adj_h = Pixel_مقصد_نقطه(پنجره, adj_h);
        }
        max_عرض_2 = adj_w;
        max_ارتفاع_2 = adj_h;
    } وإلا {
        min_عرض_2 = wind->current.logical_عرض;
        min_ارتفاع_2 = wind->current.logical_ارتفاع;
        max_عرض_2 = wind->current.logical_عرض;
        max_ارتفاع_2 = wind->current.logical_ارتفاع;
    }

#اگر_تعریف_شده HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (!wind->shell_surface.libdecor.قاب) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }

        إذا (min_عرض_2 && min_ارتفاع_2 && min_عرض_2 == max_عرض_2 && min_ارتفاع_2 == max_ارتفاع_2) {
            libdecor_قاب_unset_capabilities(wind->shell_surface.libdecor.قاب, LIBDECOR_ACTION_RESIZE);
        } وإلا {
            libdecor_قاب_مجموعه_capabilities(wind->shell_surface.libdecor.قاب, LIBDECOR_ACTION_RESIZE);
        }

        /* No need to change these values if the window is non-resizable,
         * as libdecor will just overwrite them internally.
         */
        إذا (libdecor_قاب_has_capability(wind->shell_surface.libdecor.قاب, LIBDECOR_ACTION_RESIZE)) {
            libdecor_قاب_مجموعه_min_content_اندازه(wind->shell_surface.libdecor.قاب,
                                                min_عرض_2,
                                                min_ارتفاع_2);
            libdecor_قاب_مجموعه_max_content_اندازه(wind->shell_surface.libdecor.قاب,
                                                max_عرض_2,
                                                max_ارتفاع_2);
        }
    } وإلا
#پایان_اگر
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        إذا (!wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }
        /* The limits are in window geometry space; keep an existing minimum at 1 or more,
         * or the window can be spuriously closed.
         */
        BorderInsets insets;
        GetBorderInsets(پنجره, &insets);
        min_عرض_2 = SDL_max(min_عرض_2 - (insets.چپ + insets.راست), min_عرض_2 ? 1 : 0);
        min_ارتفاع_2 = SDL_max(min_ارتفاع_2 - (insets.بالاترین + insets.bottom), min_ارتفاع_2 ? 1 : 0);
        إذا (max_عرض_2) {
            max_عرض_2 = SDL_max(max_عرض_2 - (insets.چپ + insets.راست), 1);
        }
        إذا (max_ارتفاع_2) {
            max_ارتفاع_2 = SDL_max(max_ارتفاع_2 - (insets.بالاترین + insets.bottom), 1);
        }
        xdg_toplevel_مجموعه_min_اندازه(wind->shell_surface.xdg.toplevel.xdg_toplevel,
                                  min_عرض_2,
                                  min_ارتفاع_2);
        xdg_toplevel_مجموعه_max_اندازه(wind->shell_surface.xdg.toplevel.xdg_toplevel,
                                  max_عرض_2,
                                  max_ارتفاع_2);
    }
}

ساكن فراغ EnsurePopupPositionIsValid(SDL_پنجره *پنجره, صحيح *x, صحيح *y)
{
    صحيح adj_شمار = 0;

    /* Per the xdg-positioner spec, child popup windows must intersect or at
     * least be partially adjoining the parent window.
     *
     * Failure to ensure this on a compositor that enforces this restriction
     * can result in behavior ranging from the window being spuriously closed
     * to a protocol violation.
     */
    إذا (*x + پنجره->w <= 0) {
        *x = -پنجره->w;
        ++adj_شمار;
    }
    إذا (*y + پنجره->h <= 0) {
        *y = -پنجره->h;
        ++adj_شمار;
    }
    إذا (*x >= پنجره->والد->w) {
        *x = پنجره->والد->w;
        ++adj_شمار;
    }
    إذا (*y >= پنجره->والد->h) {
        *y = پنجره->والد->h;
        ++adj_شمار;
    }

    /* If adjustment was required on the x and y axes, the popup is aligned with
     * the parent corner-to-corner and is neither overlapping nor adjoining, so it
     * must be nudged by 1 to be considered adjoining.
     */
    إذا (adj_شمار > 1) {
        *x += *x < 0 ? 1 : -1;
    }
}

// The window geometry: the explicitly set one, or the full surface if SDL has never set it.
ساكن فراغ Get_پنجره_Geometry(SDL_پنجره_داده *wind, SDL_Rect *geometry)
{
    *geometry = wind->explicit_geometry;
    إذا (SDL_Rect_خالی(geometry)) {
        geometry->x = 0;
        geometry->y = 0;
        geometry->w = wind->current.logical_عرض;
        geometry->h = wind->current.logical_ارتفاع;
    }
}

ساكن فراغ Adjust_Popup_جابه_جایی(SDL_پنجره *popup, صحيح *x, صحيح *y)
{
    // Positioner offsets are relative to the origin of the parent's window geometry.
#اگر_تعریف_شده HAVE_LIBDECOR_H
    إذا (popup->والد->داخلی->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        صحيح adj_x, adj_y;
        libdecor_قاب_translate_coordinate(popup->والد->داخلی->shell_surface.libdecor.قاب,
                                            *x, *y, &adj_x, &adj_y);
        *x = adj_x;
        *y = adj_y;
    } وإلا
#پایان_اگر
    {
        *x -= popup->والد->داخلی->explicit_geometry.x;
        *y -= popup->والد->داخلی->explicit_geometry.y;
    }
}

ساكن فراغ RepositionPopup(SDL_پنجره *پنجره, bool use_current_position)
{
    SDL_پنجره_داده *wind = پنجره->داخلی;

    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP &&
        wind->shell_surface.xdg.popup.xdg_positioner &&
        xdg_popup_get_نسخه(wind->shell_surface.xdg.popup.xdg_popup) >= XDG_POPUP_REPOSITION_SINCE_نسخه) {
        صحيح x = use_current_position ? پنجره->x : پنجره->pending.x;
        صحيح y = use_current_position ? پنجره->y : پنجره->pending.y;

        EnsurePopupPositionIsValid(پنجره, &x, &y);
        إذا (wind->scale_مقصد_display) {
            x = Pixel_مقصد_نقطه(پنجره->والد, x);
            y = Pixel_مقصد_نقطه(پنجره->والد, y);
        }
        Adjust_Popup_جابه_جایی(پنجره, &x, &y);
        SDL_Rect والد_geometry;
        Get_پنجره_Geometry(پنجره->والد->داخلی, &والد_geometry);
        xdg_positioner_مجموعه_anchor_rect(wind->shell_surface.xdg.popup.xdg_positioner, 0, 0, والد_geometry.w, والد_geometry.h);
        xdg_positioner_مجموعه_اندازه(wind->shell_surface.xdg.popup.xdg_positioner, wind->current.logical_عرض, wind->current.logical_ارتفاع);
        xdg_positioner_مجموعه_جابه_جایی(wind->shell_surface.xdg.popup.xdg_positioner, x, y);
        xdg_popup_reposition(wind->shell_surface.xdg.popup.xdg_popup,
                             wind->shell_surface.xdg.popup.xdg_positioner,
                             0);
    }
}

ساكن فراغ مجموعه_Surface_Opaque_Region(بنية wl_surface *surface, صحيح عرض, صحيح ارتفاع)
{
    SDL_Video_داده *viddata = SDL_GetVideoDevice()->داخلی;

    إذا (عرض && ارتفاع) {
        بنية wl_region *region = wl_compositor_create_region(viddata->compositor);
        wl_region_جمع_کن(region, 0, 0, عرض, ارتفاع);
        wl_surface_مجموعه_opaque_region(surface, region);
        wl_region_destroy(region);
    } وإلا {
        wl_surface_مجموعه_opaque_region(surface, عدم);
    }
}

ساكن فراغ Configure_پنجره_Geometry(SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    ثابت مزدوج scale_ضریب_2 = Get_پنجره_Scale(پنجره);
    ثابت مزدوج prev_اشاره_گر_scale_x = داده->اشاره_گر_scale.x;
    ثابت مزدوج prev_اشاره_گر_scale_y = داده->اشاره_گر_scale.y;
    ثابت صحيح old_pixel_عرض = داده->current.pixel_عرض;
    ثابت صحيح old_pixel_ارتفاع = داده->current.pixel_ارتفاع;
    صحيح پنجره_عرض = 0;
    صحيح پنجره_ارتفاع = 0;
    صحيح viewport_عرض, viewport_ارتفاع;
    bool پنجره_اندازه_تغییریافته;
    bool میانگیر_اندازه_تغییریافته;
    ثابت bool is_opaque = !(پنجره->flags & SDL_پنجره_TRANSPARENT) && پنجره->opacity == 1.0f;

    إذا (داده->is_fullscreen && پنجره->fullscreen_exclusive) {
        پنجره_عرض = پنجره->current_fullscreen_نما.w;
        پنجره_ارتفاع = پنجره->current_fullscreen_نما.h;

        viewport_عرض = داده->requested.logical_عرض;
        viewport_ارتفاع = داده->requested.logical_ارتفاع;

        بدل (Get_نما_Scale_روش()) {
        حالة WAYLAND_نما_SCALE_NONE:
            /* The Wayland spec states that the advertised fullscreen dimensions are a maximum.
             * Windows can request a smaller size, but exceeding these dimensions is a protocol violation,
             * thus, modes that exceed the output size still need to be scaled with a viewport.
             */
            إذا (پنجره_عرض <= viewport_عرض && پنجره_ارتفاع <= viewport_ارتفاع) {
                viewport_عرض = پنجره_عرض;
                viewport_ارتفاع = پنجره_ارتفاع;

                اكسر;
            }
            SDL_FALLTHROUGH;
        حالة WAYLAND_نما_SCALE_ASPECT:
        {
            ثابت عائم output_نسبت = (عائم)viewport_عرض / (عائم)viewport_ارتفاع;
            ثابت عائم نما_نسبت = (عائم)پنجره_عرض / (عائم)پنجره_ارتفاع;

            إذا (output_نسبت > نما_نسبت) {
                viewport_عرض = SDL_lroundf((عائم)پنجره_عرض * ((عائم)viewport_ارتفاع / (عائم)پنجره_ارتفاع));
            } وإلا إذا (output_نسبت < نما_نسبت) {
                viewport_ارتفاع = SDL_lroundf((عائم)پنجره_ارتفاع * ((عائم)viewport_عرض / (عائم)پنجره_عرض));
            }
        } اكسر;
        افتراضي:
            اكسر;
        }

        پنجره_اندازه_تغییریافته = پنجره_عرض != پنجره->w ||
                              پنجره_ارتفاع != پنجره->h ||
                              داده->current.viewport_عرض != viewport_عرض ||
                              داده->current.viewport_ارتفاع != viewport_ارتفاع;

        // Exclusive fullscreen window sizes are always in pixel units.
        داده->current.pixel_عرض = پنجره_عرض;
        داده->current.pixel_ارتفاع = پنجره_ارتفاع;
        میانگیر_اندازه_تغییریافته = داده->current.pixel_عرض != old_pixel_عرض ||
                              داده->current.pixel_ارتفاع != old_pixel_ارتفاع;

        إذا (پنجره_اندازه_تغییریافته || میانگیر_اندازه_تغییریافته) {
            إذا (داده->viewport) {
                wp_viewport_مجموعه_destination(داده->viewport, viewport_عرض, viewport_ارتفاع);

                داده->current.logical_عرض = داده->requested.logical_عرض;
                داده->current.logical_ارتفاع = داده->requested.logical_ارتفاع;
                داده->current.viewport_عرض = viewport_عرض;
                داده->current.viewport_ارتفاع = viewport_ارتفاع;
            } وإلا {
                // Calculate the integer scale from the mode and output.
                ثابت int32_t int_scale = SDL_max(پنجره->current_fullscreen_نما.w / viewport_عرض, 1);

                wl_surface_مجموعه_میانگیر_scale(داده->surface, int_scale);
                داده->current.logical_عرض = پنجره->current_fullscreen_نما.w;
                داده->current.logical_ارتفاع = پنجره->current_fullscreen_نما.h;
            }

            داده->اشاره_گر_scale.x = (مزدوج)پنجره_عرض / (مزدوج)viewport_عرض;
            داده->اشاره_گر_scale.y = (مزدوج)پنجره_ارتفاع / (مزدوج)viewport_ارتفاع;
        }
    } وإلا {
        إذا (!داده->scale_مقصد_display) {
            viewport_عرض = داده->requested.logical_عرض;
            viewport_ارتفاع = داده->requested.logical_ارتفاع;
        } وإلا {
            viewport_عرض = داده->requested.pixel_عرض;
            viewport_ارتفاع = داده->requested.pixel_ارتفاع;
        }

        إذا (!داده->enable_insets &&
            داده->shell_surface_وضعیت != WAYLAND_SHELL_SURFACE_وضعیت_HIDDEN &&
            داده->viewport && داده->wayland_داده->subcompositor && !داده->floating && !داده->is_fullscreen) {
            صحيح min_عرض_2, min_ارتفاع_2, max_عرض_2, max_ارتفاع_2;
            إذا (پنجره->flags & SDL_پنجره_RESIZABLE) {
                min_عرض_2 = پنجره->min_w;
                min_ارتفاع_2 = پنجره->min_h;
                max_عرض_2 = پنجره->max_w;
                max_ارتفاع_2 = پنجره->max_h;
            } وإلا {
                // Use the fixed size in the odd case where a non-resizable window somehow wound up tiled or maximized.
                min_عرض_2 = پنجره->floating.w;
                min_ارتفاع_2 = پنجره->floating.h;
                max_عرض_2 = پنجره->floating.w;
                max_ارتفاع_2 = پنجره->floating.h;
            }

            إذا (min_عرض_2) {
                viewport_عرض = SDL_max(viewport_عرض, min_عرض_2);
            }
            إذا (min_ارتفاع_2) {
                viewport_ارتفاع = SDL_max(viewport_ارتفاع, min_ارتفاع_2);
            }
            إذا (max_عرض_2) {
                viewport_عرض = SDL_min(viewport_عرض, max_عرض_2);
            }
            إذا (max_ارتفاع_2) {
                viewport_ارتفاع = SDL_min(viewport_ارتفاع, max_ارتفاع_2);
            }

            عائم aspect = (عائم)viewport_عرض / (عائم)viewport_ارتفاع;
            إذا (پنجره->min_aspect != 0.f && aspect < پنجره->min_aspect) {
                viewport_ارتفاع = SDL_max(SDL_lroundf((عائم)viewport_عرض / پنجره->min_aspect), 1);
            } وإلا إذا (پنجره->max_aspect != 0.f && aspect > پنجره->max_aspect) {
                viewport_عرض = SDL_max(SDL_lroundf((عائم)viewport_ارتفاع * پنجره->max_aspect), 1);
            }

            // At this point, the viewport matches the virtual window dimensions, but the viewport might be clamped to the output window dimensions beyond here.
            پنجره_عرض = viewport_عرض;
            پنجره_ارتفاع = viewport_ارتفاع;

            // If the viewport bounds exceed the window size, scale them while maintaining the aspect ratio.
            إذا (!داده->scale_مقصد_display) {
                إذا (viewport_عرض > داده->requested.logical_عرض || viewport_ارتفاع > داده->requested.logical_ارتفاع) {
                    aspect = (عائم)viewport_عرض / (عائم)viewport_ارتفاع;
                    ثابت عائم پنجره_نسبت = (عائم)داده->requested.logical_عرض / (عائم)داده->requested.logical_ارتفاع;
                    إذا (aspect >= پنجره_نسبت) {
                        viewport_عرض = داده->requested.logical_عرض;
                        viewport_ارتفاع = SDL_lroundf((عائم)viewport_عرض / aspect);
                    } وإلا إذا (aspect < پنجره_نسبت) {
                        viewport_ارتفاع = داده->requested.logical_ارتفاع;
                        viewport_عرض = SDL_lroundf((عائم)viewport_ارتفاع * aspect);
                    }
                }
            } وإلا {
                إذا (viewport_عرض > داده->requested.pixel_عرض || viewport_ارتفاع > داده->requested.pixel_ارتفاع) {
                    aspect = (عائم)viewport_عرض / (عائم)viewport_ارتفاع;
                    ثابت عائم پنجره_نسبت = (عائم)داده->requested.pixel_عرض / (عائم)داده->requested.pixel_ارتفاع;
                    إذا (aspect >= پنجره_نسبت) {
                        viewport_عرض = داده->requested.pixel_عرض;
                        viewport_ارتفاع = SDL_lroundf((عائم)viewport_عرض / aspect);
                    } وإلا إذا (aspect < پنجره_نسبت) {
                        viewport_ارتفاع = داده->requested.pixel_ارتفاع;
                        viewport_عرض = SDL_lroundf((عائم)viewport_ارتفاع * aspect);
                    }
                }
            }

            viewport_عرض = SDL_max(viewport_عرض, 1);
            viewport_ارتفاع = SDL_max(viewport_ارتفاع, 1);
        } وإلا {
            پنجره_عرض = viewport_عرض;
            پنجره_ارتفاع = viewport_ارتفاع;
        }

        إذا (!داده->scale_مقصد_display) {
            داده->current.pixel_عرض = نقطه_مقصد_Pixel(پنجره, پنجره_عرض);
            داده->current.pixel_ارتفاع = نقطه_مقصد_Pixel(پنجره, پنجره_ارتفاع);
        } وإلا {
            // The viewport size is in pixels at this point; convert it to logical units.
            داده->current.pixel_عرض = پنجره_عرض;
            داده->current.pixel_ارتفاع = پنجره_ارتفاع;
            viewport_عرض = Pixel_مقصد_نقطه(پنجره, viewport_عرض);
            viewport_ارتفاع = Pixel_مقصد_نقطه(پنجره, viewport_ارتفاع);
        }

        // Clamp the physical window size to the system minimum required size.
        داده->requested.logical_عرض = SDL_max(داده->requested.logical_عرض, داده->system_limits.min_عرض_2);
        داده->requested.logical_ارتفاع = SDL_max(داده->requested.logical_ارتفاع, داده->system_limits.min_ارتفاع_2);

        پنجره_اندازه_تغییریافته = داده->requested.logical_عرض != داده->current.logical_عرض ||
                              داده->requested.logical_ارتفاع != داده->current.logical_ارتفاع ||
                              viewport_عرض != داده->current.viewport_عرض ||
                              viewport_ارتفاع != داده->current.viewport_ارتفاع;

        میانگیر_اندازه_تغییریافته = داده->current.pixel_عرض != old_pixel_عرض ||
                              داده->current.pixel_ارتفاع != old_pixel_ارتفاع;

        إذا (پنجره_اندازه_تغییریافته || میانگیر_اندازه_تغییریافته) {
            إذا (داده->viewport) {
                wp_viewport_مجموعه_destination(داده->viewport, viewport_عرض, viewport_ارتفاع);
            } وإلا إذا (پنجره->flags & SDL_پنجره_بالا_PIXEL_DENSITY) {
                // Don't change this if the DPI awareness flag is unset, as an application may have set this manually on a custom or external surface.
                wl_surface_مجموعه_میانگیر_scale(داده->surface, (int32_t)scale_ضریب_2);
            }

            داده->current.logical_عرض = داده->requested.logical_عرض;
            داده->current.logical_ارتفاع = داده->requested.logical_ارتفاع;
            داده->current.viewport_عرض = viewport_عرض;
            داده->current.viewport_ارتفاع = viewport_ارتفاع;

            داده->اشاره_گر_scale.x = (مزدوج)پنجره_عرض / (مزدوج)viewport_عرض;
            داده->اشاره_گر_scale.y = (مزدوج)پنجره_ارتفاع / (مزدوج)viewport_ارتفاع;
        }
    }

    إذا (داده->egl_پنجره && میانگیر_اندازه_تغییریافته) {
        WAYLAND_wl_egl_پنجره_resize(داده->egl_پنجره,
                                     داده->current.pixel_عرض,
                                     داده->current.pixel_ارتفاع,
                                     0, 0);
    }

    /* Calculate the mask size and offset.
     * Fullscreen windows are centered and masked automatically by the compositor, unless it lacks the capability.
     */
    إذا (!داده->enable_insets && داده->viewport && داده->wayland_داده->subcompositor && (!داده->is_fullscreen || Should_ماسک_Fullscreen()) &&
        (viewport_عرض != داده->current.logical_عرض || viewport_ارتفاع != داده->current.logical_ارتفاع)) {
        بنية wl_میانگیر *old_میانگیر = عدم;

        إذا (!داده->ماسک.surface) {
            داده->ماسک.surface = wl_compositor_create_surface(داده->wayland_داده->compositor);
            SDL_WAYLAND_ثبات_surface(داده->ماسک.surface);
            wl_surface_مجموعه_user_داده(داده->ماسک.surface, داده);
        }
        إذا (!داده->ماسک.subsurface) {
            داده->ماسک.subsurface = wl_subcompositor_get_subsurface(داده->wayland_داده->subcompositor, داده->ماسک.surface, داده->surface);
        }
        إذا (!داده->ماسک.viewport) {
            داده->ماسک.viewport = wp_viewporter_get_viewport(داده->wayland_داده->viewporter, داده->ماسک.surface);
        }
        إذا (!داده->ماسک.میانگیر_2 || داده->ماسک.opaque != is_opaque) {
            old_میانگیر = داده->ماسک.میانگیر_2;
            داده->ماسک.opaque = is_opaque;
            داده->ماسک.میانگیر_2 = Wayland_Create_Single_Pixel_میانگیر(0, 0, 0, is_opaque ? SDL_MAX_UINT32 : 0);
        }

        wl_surface_attach(داده->ماسک.surface, داده->ماسک.میانگیر_2, 0, 0);

        wl_subsurface_قراربده_زیر(داده->ماسک.subsurface, داده->surface);
        wp_viewport_مجموعه_destination(داده->ماسک.viewport, داده->current.logical_عرض, داده->current.logical_ارتفاع);

        إذا (wl_surface_get_نسخه(داده->ماسک.surface) >= WL_SURFACE_DAMAGE_میانگیر_SINCE_نسخه) {
            wl_surface_damage_میانگیر(داده->ماسک.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        } وإلا {
            wl_surface_damage(داده->ماسک.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        }

        إذا (is_opaque) {
            مجموعه_Surface_Opaque_Region(داده->ماسک.surface, داده->current.logical_عرض, داده->current.logical_ارتفاع);
        } وإلا {
            مجموعه_Surface_Opaque_Region(داده->ماسک.surface, 0, 0);
        }

        // Can't use an offset subsurface with libdecor (yet), or the decorations won't line up properly.
        إذا (داده->shell_surface_type != WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
            داده->ماسک.جابه_جایی_x = -(داده->current.logical_عرض - viewport_عرض) / 2;
            داده->ماسک.جابه_جایی_y = -(داده->current.logical_ارتفاع - viewport_ارتفاع) / 2;
        } وإلا {
            داده->ماسک.جابه_جایی_x = 0;
            داده->ماسک.جابه_جایی_y = 0;
        }

        wl_subsurface_مجموعه_position(داده->ماسک.subsurface, داده->ماسک.جابه_جایی_x, داده->ماسک.جابه_جایی_y);
        wl_surface_commit(داده->ماسک.surface);

        إذا (old_میانگیر) {
            wl_میانگیر_destroy(old_میانگیر);
        }

        داده->ماسک.mapped = true;
    } وإلا إذا (داده->ماسک.mapped) {
        wl_subsurface_مجموعه_position(داده->ماسک.subsurface, 0, 0);
        wl_surface_attach(داده->ماسک.surface, عدم, 0, 0);
        wl_surface_commit(داده->ماسک.surface);

        داده->ماسک.جابه_جایی_x = 0;
        داده->ماسک.جابه_جایی_y = 0;
        داده->ماسک.mapped = false;
    }

    إذا (داده->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && داده->shell_surface.xdg.surface &&
        (داده->enable_insets || !داده->viewport)) {
        /* The window geometry is the surface minus the declared border insets. They don't apply
         * when an exact size is required (maximized/fullscreen).
         */
        BorderInsets insets;
        GetBorderInsets(پنجره, &insets);
        ثابت bool use_insets = (insets.چپ || insets.بالاترین || insets.راست || insets.bottom) &&
                                !(پنجره->flags & (SDL_پنجره_MAXIMIZED | SDL_پنجره_FULLSCREEN));
        SDL_Rect geometry = { 0, 0, داده->current.logical_عرض, داده->current.logical_ارتفاع };
        إذا (use_insets) {
            geometry.x = insets.چپ;
            geometry.y = insets.بالاترین;
            geometry.w = SDL_max(geometry.w - (insets.چپ + insets.راست), 1);
            geometry.h = SDL_max(geometry.h - (insets.بالاترین + insets.bottom), 1);
        }
        /* An explicitly set geometry does not track the surface, so it must be kept in sync
         * once set. Otherwise this is only done when viewports aren't supported and the size
         * has changed (XXX: a hack) to avoid a potential protocol violation if a buffer with
         * an old size is committed.
         */
        إذا ((use_insets || !SDL_Rect_خالی(&داده->explicit_geometry) || (!داده->viewport && پنجره_اندازه_تغییریافته)) &&
            !SDL_RectsEqual(&geometry, &داده->explicit_geometry)) {
            xdg_surface_مجموعه_پنجره_geometry(داده->shell_surface.xdg.surface, geometry.x, geometry.y, geometry.w, geometry.h);
            داده->explicit_geometry = geometry;
        }
    }

    /* The opaque region and pointer confinement region only need to be
     * recalculated if the output size has changed.
     */
    إذا (پنجره_اندازه_تغییریافته) {
        إذا (is_opaque) {
            مجموعه_Surface_Opaque_Region(داده->surface, viewport_عرض, viewport_ارتفاع);
        } وإلا {
            مجموعه_Surface_Opaque_Region(داده->surface, 0, 0);
        }

        // Ensure that child popup windows are still in bounds.
        لكل (SDL_پنجره *فرزند = پنجره->اولی_فرزند; فرزند; فرزند = فرزند->بعدی_sibling) {
            RepositionPopup(فرزند, true);
        }
    }

    // Update the scale for any focused cursors.
    إذا (prev_اشاره_گر_scale_x != داده->اشاره_گر_scale.x || prev_اشاره_گر_scale_y != داده->اشاره_گر_scale.y) {
        Wayland_Display_Update_اشاره_گر_Focused_Scale(داده);
    }

    /* Update the min/max dimensions, primarily if the state was changed, and for non-resizable
     * xdg-toplevel windows where the limits should match the window size.
     */
    مجموعه_Min_Max_Dimensions(پنجره);

    // Unconditionally send the window and drawable size, the video core will deduplicate when required.
    إذا (!داده->scale_مقصد_display) {
        SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_RESIZED, پنجره_عرض, پنجره_ارتفاع);
    } وإلا {
        SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_RESIZED, داده->current.pixel_عرض, داده->current.pixel_ارتفاع);
    }
    SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_PIXEL_اندازه_تغییریافته, داده->current.pixel_عرض, داده->current.pixel_ارتفاع);

    /* Send an exposure event if the window is in the shown state and the size has changed,
     * even if the window is occluded, as the client needs to commit a new frame for the
     * changes to take effect.
     *
     * The occlusion state is immediately set again afterward, if necessary.
     */
    إذا (داده->shell_surface_وضعیت == WAYLAND_SHELL_SURFACE_وضعیت_SHOWN) {
        إذا ((میانگیر_اندازه_تغییریافته || پنجره_اندازه_تغییریافته) ||
            (!داده->suspended && (پنجره->flags & SDL_پنجره_OCCLUDED))) {
            SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_EXPOSED, 0, 0);
        }

        إذا (داده->suspended) {
            SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_OCCLUDED, 0, 0);
        }
    }
}

ساكن فراغ Commit_Libdecor_قاب(SDL_پنجره *پنجره)
{
#اگر_تعریف_شده HAVE_LIBDECOR_H
    SDL_پنجره_داده *wind = پنجره->داخلی;

    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.قاب) {
        بنية libdecor_state *state = libdecor_state_new(wind->current.logical_عرض, wind->current.logical_ارتفاع);
        libdecor_قاب_commit(wind->shell_surface.libdecor.قاب, state, عدم);
        libdecor_state_free(state);
    }
#پایان_اگر
}

ساكن فراغ pending_state_deadline_handler(فراغ *داده, بنية wl_callback *callback, uint32_t callback_داده)
{
    // Get the window from the ID, as it may have been destroyed.
    SDL_پنجره_ID پنجره_ID = (SDL_پنجره_ID)(uintptr_t)داده;
    SDL_پنجره *پنجره = SDL_Get_پنجره_From_ID(پنجره_ID);

    إذا (پنجره && پنجره->داخلی) {
        --پنجره->داخلی->pending_state_deadline_شمار;
    }

    wl_callback_destroy(callback);
}

ساكن بنية wl_callback_listener pending_state_deadline_listener = {
    pending_state_deadline_handler
};

ساكن فراغ جمع_کن_Pending_State_Sync(SDL_پنجره_داده *پنجره_داده_2)
{
    SDL_Video_داده *video_داده = پنجره_داده_2->wayland_داده;
    فراغ *cb_داده = (فراغ *)(uintptr_t)پنجره_داده_2->sdlwindow->id;

    ++پنجره_داده_2->pending_state_deadline_شمار;
    بنية wl_callback *cb = wl_display_sync(video_داده->display);
    wl_callback_جمع_کن_listener(cb, &pending_state_deadline_listener, cb_داده);
}

ساكن فراغ FlushPendingEvents(SDL_پنجره *پنجره)
{
    // Serialize and restore the pending flags, as they may be overwritten while flushing.
    ثابت bool آخرین_position_pending = پنجره->آخرین_position_pending;
    ثابت bool آخرین_اندازه_pending = پنجره->آخرین_اندازه_pending;

    طالما (پنجره->داخلی->pending_state_deadline_شمار) {
        WAYLAND_wl_display_roundtrip(پنجره->داخلی->wayland_داده->display);
    }

    پنجره->آخرین_position_pending = آخرین_position_pending;
    پنجره->آخرین_اندازه_pending = آخرین_اندازه_pending;
}

/* While we can't get window position from the compositor, we do at least know
 * what monitor we're on, so let's send move events that put the window at the
 * center of the whatever display the wl_surface_listener events give us.
 */
فراغ Wayland_Update_پنجره_Position(SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *wind = پنجره->داخلی;
    SDL_Display_داده *display;

    إذا (wind->outputs && wind->رقم_outputs) {
        display = wind->outputs[wind->رقم_outputs - 1];
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
    wind->آخرین_display_ID = display->display;
    إذا (wind->shell_surface_type != WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        إذا (!wind->wayland_داده->scale_مقصد_display_enabled) {
            SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_MOVED, display->logical.x, display->logical.y);
        } وإلا {
            SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_MOVED, display->pixel.x, display->pixel.y);
        }
        SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_DISPLAY_تغییریافته, wind->آخرین_display_ID, 0);
    }
}

ساكن فراغ مجموعه_Fullscreen(SDL_پنجره *پنجره, بنية wl_output *output, bool fullscreen)
{
    SDL_پنجره_داده *wind = پنجره->داخلی;

#اگر_تعریف_شده HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (!wind->shell_surface.libdecor.قاب) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }

        wind->fullscreen_exclusive = output ? پنجره->fullscreen_exclusive : false;
        إذا (fullscreen) {
            libdecor_قاب_مجموعه_fullscreen(wind->shell_surface.libdecor.قاب, output);
        } وإلا {
            libdecor_قاب_unset_fullscreen(wind->shell_surface.libdecor.قاب);
        }
    } وإلا
#پایان_اگر
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        إذا (wind->shell_surface.xdg.toplevel.xdg_toplevel == عدم) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }

        wind->fullscreen_exclusive = output ? پنجره->fullscreen_exclusive : false;
        إذا (fullscreen) {
            xdg_toplevel_مجموعه_fullscreen(wind->shell_surface.xdg.toplevel.xdg_toplevel, output);
        } وإلا {
            xdg_toplevel_unset_fullscreen(wind->shell_surface.xdg.toplevel.xdg_toplevel);
        }
    }

    جمع_کن_Pending_State_Sync(wind);
}

ساكن فراغ Update_پنجره_Fullscreen(SDL_پنجره *پنجره, bool fullscreen)
{
    SDL_پنجره_داده *wind = پنجره->داخلی;

    wind->is_fullscreen = fullscreen;

    إذا (fullscreen) {
        إذا (!(پنجره->flags & SDL_پنجره_FULLSCREEN)) {
            SDL_copyp(&پنجره->current_fullscreen_نما, &پنجره->requested_fullscreen_نما);
            SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_ENTER_FULLSCREEN, 0, 0);
            SDL_Update_Fullscreen_نما(پنجره, SDL_FULLSCREEN_OP_ENTER, false);

            /* Set the output for exclusive fullscreen windows when entering fullscreen from a
             * compositor event, or if the fullscreen parameters were changed between the initial
             * fullscreen request and now, to ensure that the window is on the correct output,
             * as requested by the client.
             */
            إذا (پنجره->fullscreen_exclusive && (!wind->fullscreen_exclusive || !wind->fullscreen_was_positioned)) {
                SDL_VideoDisplay *disp = SDL_GetVideoDisplay(پنجره->current_fullscreen_نما.displayID);
                إذا (disp) {
                    wind->fullscreen_was_positioned = true;
                    مجموعه_Fullscreen(پنجره, disp->داخلی->output, true);
                }
            }
        }
    } وإلا {
        // Don't change the fullscreen flags if the window is hidden or being hidden.
        إذا ((پنجره->flags & SDL_پنجره_FULLSCREEN) && !پنجره->is_hiding && !(پنجره->flags & SDL_پنجره_HIDDEN)) {
            SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_LEAVE_FULLSCREEN, 0, 0);
            SDL_Update_Fullscreen_نما(پنجره, SDL_FULLSCREEN_OP_LEAVE, false);
            wind->fullscreen_was_positioned = false;

            /* Send a move event, in case it was deferred while the fullscreen window was moving and
             * on multiple outputs.
             */
            Wayland_Update_پنجره_Position(پنجره);
        }
    }
}

ساكن ثابت بنية wl_callback_listener surface_قاب_listener;

ساكن فراغ surface_قاب_انجامشده(فراغ *داده, بنية wl_callback *cb, uint32_t زمان)
{
    SDL_پنجره_داده *wind = (SDL_پنجره_داده *)داده;

    /* XXX: This is needed to work around an Nvidia egl-wayland bug due to buffer coordinates
     *      being used with wl_surface_damage, which causes part of the output to not be
     *      updated when using a viewport with an output region larger than the source region.
     */
    إذا (wl_compositor_get_نسخه(wind->wayland_داده->compositor) >= WL_SURFACE_DAMAGE_میانگیر_SINCE_نسخه) {
        wl_surface_damage_میانگیر(wind->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    } وإلا {
        wl_surface_damage(wind->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    }

    wind->pending_state_commit = false;

    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        إذا (wind->pending_config_ack) {
            wind->pending_config_ack = false;
            Configure_پنجره_Geometry(wind->sdlwindow);
            xdg_surface_ack_configure(wind->shell_surface.xdg.surface, wind->shell_surface.xdg.serial);
        }
    } وإلا {
        wind->resizing = false;
    }

    إذا (wind->shell_surface_وضعیت == WAYLAND_SHELL_SURFACE_وضعیت_انتظار_FOR_قاب) {
        wind->shell_surface_وضعیت = WAYLAND_SHELL_SURFACE_وضعیت_SHOWN;

        // If any child windows are waiting on this window to be shown, show them now
        لكل (SDL_پنجره *w = wind->sdlwindow->اولی_فرزند; w; w = w->بعدی_sibling) {
            إذا (w->داخلی->shell_surface_وضعیت == WAYLAND_SHELL_SURFACE_وضعیت_SHOW_PENDING) {
                Wayland_Show_پنجره(SDL_GetVideoDevice(), w);
            } وإلا إذا (w->داخلی->reparenting_required) {
                Wayland_مجموعه_پنجره_والد(SDL_GetVideoDevice(), w, w->والد);
                إذا (w->flags & SDL_پنجره_MODAL) {
                    Wayland_مجموعه_پنجره_Modal(SDL_GetVideoDevice(), w, true);
                }
            }
        }

        /* If the window was initially set to the suspended state, send the occluded event now,
         * as we don't want to mark the window as occluded until at least one frame has been submitted.
         */
        إذا (wind->suspended) {
            SDL_Send_پنجره_Event(wind->sdlwindow, SDL_EVENT_پنجره_OCCLUDED, 0, 0);
        }
    }

    wl_callback_destroy(cb);
    wind->surface_قاب_callback = wl_surface_قاب(wind->surface);
    wl_callback_جمع_کن_listener(wind->surface_قاب_callback, &surface_قاب_listener, داده);
}

ساكن ثابت بنية wl_callback_listener surface_قاب_listener = {
    surface_قاب_انجامشده
};

ساكن ثابت بنية wl_callback_listener gles_جابجا_قاب_listener;

ساكن فراغ gles_جابجا_قاب_انجامشده(فراغ *داده, بنية wl_callback *cb, uint32_t زمان)
{
    SDL_پنجره_داده *wind = (SDL_پنجره_داده *)داده;
    SDL_مجموعه_Atomic_Int(&wind->جابجا_interval_ready, 1); // mark window as ready to present again.

    // reset this callback to fire again once a new frame was presented and compositor wants the next one.
    wind->gles_جابجا_قاب_callback = wl_surface_قاب(wind->gles_جابجا_قاب_surface_wrapper);
    wl_callback_destroy(cb);
    wl_callback_جمع_کن_listener(wind->gles_جابجا_قاب_callback, &gles_جابجا_قاب_listener, داده);
}

ساكن ثابت بنية wl_callback_listener gles_جابجا_قاب_listener = {
    gles_جابجا_قاب_انجامشده
};

ساكن فراغ handle_xdg_surface_configure(فراغ *داده, بنية xdg_surface *xdg, uint32_t serial)
{
    SDL_پنجره_داده *wind = (SDL_پنجره_داده *)داده;
    SDL_پنجره *پنجره = wind->sdlwindow;

    /* Interactive resizes are throttled by acking and committing only the most recent configuration at
     * the next frame callback, or certain combinations of clients and compositors can exhibit severe lag
     * when resizing.
     */
    wind->shell_surface.xdg.serial = serial;
    إذا (!wind->resizing) {
        wind->pending_config_ack = false;
        Configure_پنجره_Geometry(پنجره);
        xdg_surface_ack_configure(xdg, serial);
    } وإلا إذا (!wind->pending_config_ack) {
        wind->pending_config_ack = true;

        // Always send an exposure event during a new frame to ensure forward progress if the frame callback already occurred.
        SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_EXPOSED, 0, 0);
    }

    إذا (wind->shell_surface_وضعیت == WAYLAND_SHELL_SURFACE_وضعیت_انتظار_FOR_CONFIGURE) {
        wind->shell_surface_وضعیت = WAYLAND_SHELL_SURFACE_وضعیت_انتظار_FOR_قاب;
    }
}

ساكن ثابت بنية xdg_surface_listener _xdg_surface_listener = {
    handle_xdg_surface_configure
};

ساكن فراغ ApplyGeometryLimits(SDL_پنجره *پنجره, صحيح req_w, صحيح req_h, صحيح *بیرون_w, صحيح *بیرون_h)
{
    SDL_پنجره_داده *wind = پنجره->داخلی;

    صحيح w = req_w;
    صحيح h = req_h;
    ثابت عائم aspect = (عائم)req_w / (عائم)req_h;

    /* If adjusting for aspect causes the adjusted dimension to exceed the min/max limit, clamp to the limit
     * and attempt to adjust the opposite dimension to compensate.
     */
    إذا (!wind->resizing || (wind->resize_یال & WAYLAND_RESIZE_یال_گوشه) == WAYLAND_RESIZE_یال_گوشه) {
        إذا (پنجره->min_aspect != 0.f && aspect < پنجره->min_aspect) {
            h = SDL_max(SDL_lroundf((عائم)req_w / پنجره->min_aspect), 1);

            إذا (h < پنجره->min_h) {
                w = SDL_max(SDL_lroundf((عائم)پنجره->min_h * پنجره->min_aspect), 1);
            }
            إذا (پنجره->max_h && h > پنجره->max_h) {
                w = SDL_max(SDL_lroundf((عائم)پنجره->max_h * پنجره->min_aspect), 1);
            }
        } وإلا إذا (پنجره->max_aspect != 0.f && aspect > پنجره->max_aspect) {
            w = SDL_max(SDL_lroundf((عائم)req_h * پنجره->max_aspect), 1);

            إذا (w < پنجره->min_w) {
                h = SDL_max(SDL_lroundf((عائم)پنجره->min_w / پنجره->max_aspect), 1);
            }
            إذا (پنجره->max_w && w > پنجره->max_w) {
                h = SDL_max(SDL_lroundf((عائم)پنجره->max_w / پنجره->max_aspect), 1);
            }
        }
    } وإلا إذا (wind->resize_یال & WAYLAND_RESIZE_یال_LR) {
        إذا (پنجره->min_aspect != 0.f && aspect < پنجره->min_aspect) {
            h = SDL_max(SDL_lroundf((عائم)req_w / پنجره->min_aspect), 1);

            إذا (h < پنجره->min_h) {
                w = SDL_max(SDL_lroundf((عائم)پنجره->min_h * پنجره->min_aspect), 1);
            }
            إذا (پنجره->max_h && h > پنجره->max_h) {
                w = SDL_max(SDL_lroundf((عائم)پنجره->max_h * پنجره->min_aspect), 1);
            }
        } وإلا إذا (پنجره->max_aspect != 0.f && aspect > پنجره->max_aspect) {
            h = SDL_max(SDL_lroundf((عائم)req_w / پنجره->max_aspect), 1);

            إذا (h < پنجره->min_h) {
                w = SDL_max(SDL_lroundf((عائم)پنجره->min_h * پنجره->max_aspect), 1);
            }
            إذا (پنجره->max_h && h > پنجره->max_h) {
                w = SDL_max(SDL_lroundf((عائم)پنجره->max_h * پنجره->max_aspect), 1);
            }
        }
    } وإلا إذا (wind->resize_یال & WAYLAND_RESIZE_یال_TB) {
        إذا (پنجره->min_aspect != 0.f && aspect < پنجره->min_aspect) {
            w = SDL_max(SDL_lroundf((عائم)req_h * پنجره->min_aspect), 1);

            إذا (w < پنجره->min_w) {
                h = SDL_max(SDL_lroundf((عائم)پنجره->min_w / پنجره->min_aspect), 1);
            }
            إذا (پنجره->max_w && w > پنجره->max_w) {
                h = SDL_max(SDL_lroundf((عائم)پنجره->max_w / پنجره->min_aspect), 1);
            }
        } وإلا إذا (پنجره->max_aspect != 0.f && aspect > پنجره->max_aspect) {
            w = SDL_max(SDL_lroundf((عائم)req_h * پنجره->max_aspect), 1);

            إذا (w < پنجره->min_w) {
                h = SDL_max(SDL_lroundf((عائم)پنجره->min_w / پنجره->max_aspect), 1);
            }
            إذا (پنجره->max_w && w > پنجره->max_w) {
                h = SDL_max(SDL_lroundf((عائم)پنجره->max_w / پنجره->max_aspect), 1);
            }
        }
    }

    إذا (پنجره->max_w) {
        w = SDL_min(w, پنجره->max_w);
    }
    *بیرون_w = SDL_max(w, پنجره->min_w);

    إذا (پنجره->max_h) {
        h = SDL_min(h, پنجره->max_h);
    }
    *بیرون_h = SDL_max(h, پنجره->min_h);

}

ساكن فراغ DetermineResizeAxis(SDL_پنجره_داده *wind, صحيح عرض, صحيح ارتفاع, bool resizing)
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
        إذا (now >= wind->آخرین_resize_event_زمان_ns + SDL_MS_مقصد_NS(500)) {
            wind->resize_یال = 0;
        }

        wind->آخرین_resize_event_زمان_ns = now;

        إذا (!wind->resize_یال) {
            إذا (عرض != wind->آخرین_configure.عرض || !ارتفاع) {
                wind->resize_یال |= WAYLAND_RESIZE_یال_LR;
            }
            إذا (ارتفاع != wind->آخرین_configure.ارتفاع || !عرض) {
                wind->resize_یال |= WAYLAND_RESIZE_یال_TB;
            }
        }
    } وإلا {
        wind->resize_یال = 0;
    }

    wind->resizing = resizing;
}

ساكن فراغ handle_xdg_toplevel_configure(فراغ *داده,
                                          بنية xdg_toplevel *xdg_toplevel,
                                          int32_t عرض,
                                          int32_t ارتفاع,
                                          بنية wl_array *حالتها)
{
    SDL_پنجره_داده *wind = (SDL_پنجره_داده *)داده;
    SDL_پنجره *پنجره = wind->sdlwindow;

    تعداد xdg_toplevel_state *state;
    bool fullscreen = false;
    bool maximized = false;
    bool floating = true;
    bool tiled = false;
    bool فعال = false;
    bool resizing = false;
    bool suspended = false;
    wind->toplevel_constraints = 0;
    wl_array_for_each (state, حالتها) {
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
        حالة XDG_TOPLEVEL_STATE_TILED_چپ:
        حالة XDG_TOPLEVEL_STATE_TILED_راست:
        حالة XDG_TOPLEVEL_STATE_TILED_بالاترین:
        حالة XDG_TOPLEVEL_STATE_TILED_BOTTOM:
            tiled = true;
            floating = false;
            اكسر;
        حالة XDG_TOPLEVEL_STATE_SUSPENDED:
            suspended = true;
            اكسر;
        حالة XDG_TOPLEVEL_STATE_CONSTRAINED_چپ:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_چپ;
            اكسر;
        حالة XDG_TOPLEVEL_STATE_CONSTRAINED_راست:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_راست;
            اكسر;
        حالة XDG_TOPLEVEL_STATE_CONSTRAINED_بالاترین:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_بالاترین;
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
    ثابت bool new_configure_اندازه = عرض != wind->آخرین_configure.عرض || ارتفاع != wind->آخرین_configure.ارتفاع ||
                                    insets_apply != wind->آخرین_configure.insets_apply;

    BorderInsets insets = { 0, 0, 0, 0 };
    إذا (insets_apply) {
        GetBorderInsets(پنجره, &insets);
    }

    DetermineResizeAxis(wind, عرض, ارتفاع, resizing);
    Update_پنجره_Fullscreen(پنجره, fullscreen);

    /* Always send a maximized/restore event; if the event is redundant it will
     * automatically be discarded (see src/events/SDL_windowevents.c)
     *
     * No, we do not get minimize events from xdg-shell, however, the minimized
     * state can be programmatically set. The meaning of 'minimized' is compositor
     * dependent, but in general, we can assume that the flag should remain set until
     * the next focused configure event occurs.
     */
    إذا (فعال || !(پنجره->flags & SDL_پنجره_MINIMIZED)) {
        إذا (پنجره->flags & SDL_پنجره_MINIMIZED) {
            // If we were minimized, send a restored event before possibly sending maximized.
            SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_RESTORED, 0, 0);
        }
        SDL_Send_پنجره_Event(پنجره,
                            (maximized && !fullscreen) ? SDL_EVENT_پنجره_MAXIMIZED : SDL_EVENT_پنجره_RESTORED,
                            0, 0);
    }

    إذا (!fullscreen) {
        /* xdg_toplevel spec states that this is a suggestion.
         * Ignore if less than or greater than max/min size.
         */
        إذا ((پنجره->flags & SDL_پنجره_RESIZABLE) || maximized) {
            إذا (!عرض) {
                /* This happens when the compositor indicates that the size is
                 * up to the client, so use the cached window size here.
                 */
                إذا (floating) {
                    عرض = پنجره->floating.w;

                    // Clamp the window to the toplevel bounds, if any are set.
                    إذا (wind->shell_surface_وضعیت == WAYLAND_SHELL_SURFACE_وضعیت_انتظار_FOR_CONFIGURE && wind->toplevel_bounds.عرض) {
                        عرض = SDL_min(wind->toplevel_bounds.عرض, عرض);
                    }
                } وإلا {
                    عرض = پنجره->windowed.w;
                }

                إذا (!wind->scale_مقصد_display) {
                    wind->requested.logical_عرض = عرض;
                } وإلا {
                    wind->requested.pixel_عرض = عرض;
                    عرض = wind->requested.logical_عرض = Pixel_مقصد_نقطه(پنجره, عرض);
                }
                عرض = SDL_max(عرض - (insets.چپ + insets.راست), 1);
            } وإلا إذا (new_configure_اندازه) {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 */

                wind->requested.logical_عرض = عرض + (insets.چپ + insets.راست);

                إذا (wind->scale_مقصد_display) {
                    wind->requested.pixel_عرض = نقطه_مقصد_Pixel(پنجره, wind->requested.logical_عرض);
                }
            }
            إذا (!ارتفاع) {
                /* This happens when the compositor indicates that the size is
                 * up to the client, so use the cached window size here.
                 */
                إذا (floating) {
                    ارتفاع = پنجره->floating.h;

                    // Clamp the window to the toplevel bounds, if any are set.
                    إذا (wind->shell_surface_وضعیت == WAYLAND_SHELL_SURFACE_وضعیت_انتظار_FOR_CONFIGURE && wind->toplevel_bounds.ارتفاع) {
                        ارتفاع = SDL_min(wind->toplevel_bounds.ارتفاع, ارتفاع);
                    }
                } وإلا {
                    ارتفاع = پنجره->windowed.h;
                }

                إذا (!wind->scale_مقصد_display) {
                    wind->requested.logical_ارتفاع = ارتفاع;
                } وإلا {
                    wind->requested.pixel_ارتفاع = ارتفاع;
                    ارتفاع = wind->requested.logical_ارتفاع = Pixel_مقصد_نقطه(پنجره, ارتفاع);
                }
                ارتفاع = SDL_max(ارتفاع - (insets.بالاترین + insets.bottom), 1);
            } وإلا إذا (new_configure_اندازه) {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 */
                wind->requested.logical_ارتفاع = ارتفاع + (insets.بالاترین + insets.bottom);

                إذا (wind->scale_مقصد_display) {
                    wind->requested.pixel_ارتفاع = نقطه_مقصد_Pixel(پنجره, wind->requested.logical_ارتفاع);
                }
            }
        } وإلا {
            /* If we're a fixed-size, non-maximized window, we know our size for sure.
             * Always assume the configure is wrong.
             */
            إذا (!wind->scale_مقصد_display) {
                عرض = wind->requested.logical_عرض = پنجره->floating.w;
                ارتفاع = wind->requested.logical_ارتفاع = پنجره->floating.h;
            } وإلا {
                wind->requested.pixel_عرض = پنجره->floating.w;
                wind->requested.pixel_ارتفاع = پنجره->floating.h;
                عرض = wind->requested.logical_عرض = Pixel_مقصد_نقطه(پنجره, پنجره->floating.w);
                ارتفاع = wind->requested.logical_ارتفاع = Pixel_مقصد_نقطه(پنجره, پنجره->floating.h);
            }
            عرض = SDL_max(عرض - (insets.چپ + insets.راست), 1);
            ارتفاع = SDL_max(ارتفاع - (insets.بالاترین + insets.bottom), 1);
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
            إذا (!wind->scale_مقصد_display) {
                ApplyGeometryLimits(پنجره, wind->requested.logical_عرض, wind->requested.logical_ارتفاع, &wind->requested.logical_عرض, &wind->requested.logical_ارتفاع);
            } وإلا {
                ApplyGeometryLimits(پنجره, wind->requested.pixel_عرض, wind->requested.pixel_ارتفاع, &wind->requested.pixel_عرض, &wind->requested.pixel_ارتفاع);

                wind->requested.logical_عرض = Pixel_مقصد_نقطه(پنجره, wind->requested.pixel_عرض);
                wind->requested.logical_ارتفاع = Pixel_مقصد_نقطه(پنجره, wind->requested.pixel_ارتفاع);
            }
        }
    } وإلا {
        // Fullscreen windows know their exact size.
        إذا (عرض == 0 || ارتفاع == 0) {
            عرض = wind->requested.logical_عرض;
            ارتفاع = wind->requested.logical_ارتفاع;
        } وإلا {
            wind->requested.logical_عرض = عرض;
            wind->requested.logical_ارتفاع = ارتفاع;
        }

        إذا (wind->scale_مقصد_display) {
            wind->requested.pixel_عرض = نقطه_مقصد_Pixel(پنجره, عرض);
            wind->requested.pixel_ارتفاع = نقطه_مقصد_Pixel(پنجره, ارتفاع);
        }
    }

    wind->آخرین_configure.عرض = عرض;
    wind->آخرین_configure.ارتفاع = ارتفاع;
    wind->آخرین_configure.insets_apply = insets_apply;
    wind->floating = floating;
    wind->suspended = suspended;
    wind->فعال = فعال;
    پنجره->tiled = tiled;
}

ساكن فراغ handle_xdg_toplevel_close(فراغ *داده, بنية xdg_toplevel *xdg_toplevel)
{
    SDL_پنجره_داده *پنجره = (SDL_پنجره_داده *)داده;
    SDL_Send_پنجره_Event(پنجره->sdlwindow, SDL_EVENT_پنجره_CLOSE_REQUESTED, 0, 0);
}

ساكن فراغ handle_xdg_toplevel_configure_bounds(فراغ *داده,
                                                 بنية xdg_toplevel *xdg_toplevel,
                                                 int32_t عرض, int32_t ارتفاع)
{
    SDL_پنجره_داده *پنجره = (SDL_پنجره_داده *)داده;
    پنجره->toplevel_bounds.عرض = عرض;
    پنجره->toplevel_bounds.ارتفاع = ارتفاع;
}

ساكن فراغ handle_xdg_toplevel_wm_capabilities(فراغ *داده,
                                                بنية xdg_toplevel *xdg_toplevel,
                                                بنية wl_array *capabilities)
{
    SDL_پنجره_داده *wind = (SDL_پنجره_داده *)داده;
    تعداد xdg_toplevel_wm_capabilities *wm_cap;

    wind->wm_caps = 0;

    wl_array_for_each (wm_cap, capabilities) {
        بدل (*wm_cap) {
        حالة XDG_TOPLEVEL_WM_CAPABILITIES_پنجره_MENU:
            wind->wm_caps |= WAYLAND_WM_CAPS_پنجره_MENU;
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

ساكن فراغ handle_xdg_popup_configure(فراغ *داده,
                                       بنية xdg_popup *xdg_popup,
                                       int32_t x,
                                       int32_t y,
                                       int32_t عرض,
                                       int32_t ارتفاع)
{
    SDL_پنجره_داده *wind = (SDL_پنجره_داده *)داده;
    صحيح جابه_جایی_x = 0, جابه_جایی_y = 0;

    // Adjust the position if it was offset for libdecor
    Adjust_Popup_جابه_جایی(wind->sdlwindow, &جابه_جایی_x, &جابه_جایی_y);
    x -= جابه_جایی_x;
    y -= جابه_جایی_y;

    /* This happens when the compositor indicates that the size is
     * up to the client, so use the cached window size here.
     */
    إذا (عرض == 0 || ارتفاع == 0) {
        عرض = wind->sdlwindow->floating.w;
        ارتفاع = wind->sdlwindow->floating.h;
    }

    /* Don't apply the supplied dimensions if they haven't changed from the last configuration
     * event, or a newer size set programmatically can be overwritten by old data.
     */
    إذا (عرض != wind->آخرین_configure.عرض || ارتفاع != wind->آخرین_configure.ارتفاع) {
        wind->requested.logical_عرض = عرض;
        wind->requested.logical_ارتفاع = ارتفاع;

        إذا (wind->scale_مقصد_display) {
            wind->requested.pixel_عرض = نقطه_مقصد_Pixel(wind->sdlwindow, عرض);
            wind->requested.pixel_ارتفاع = نقطه_مقصد_Pixel(wind->sdlwindow, ارتفاع);
        }
    }

    إذا (wind->scale_مقصد_display) {
        x = نقطه_مقصد_Pixel(wind->sdlwindow->والد, x);
        y = نقطه_مقصد_Pixel(wind->sdlwindow->والد, y);
    }

    SDL_Send_پنجره_Event(wind->sdlwindow, SDL_EVENT_پنجره_MOVED, x, y);

    wind->آخرین_configure.عرض = عرض;
    wind->آخرین_configure.ارتفاع = ارتفاع;

    إذا (wind->shell_surface_وضعیت == WAYLAND_SHELL_SURFACE_وضعیت_انتظار_FOR_CONFIGURE) {
        wind->shell_surface_وضعیت = WAYLAND_SHELL_SURFACE_وضعیت_انتظار_FOR_قاب;
    }
}

ساكن فراغ handle_xdg_popup_انجامشده(فراغ *داده, بنية xdg_popup *xdg_popup)
{
    SDL_پنجره_داده *پنجره = (SDL_پنجره_داده *)داده;
    SDL_Send_پنجره_Event(پنجره->sdlwindow, SDL_EVENT_پنجره_CLOSE_REQUESTED, 0, 0);
}

ساكن فراغ handle_xdg_popup_repositioned(فراغ *داده,
                                          بنية xdg_popup *xdg_popup,
                                          uint32_t token)
{
    // No-op, configure does all the work we care about
}

ساكن ثابت بنية xdg_popup_listener _xdg_popup_listener = {
    handle_xdg_popup_configure,
    handle_xdg_popup_انجامشده,
    handle_xdg_popup_repositioned
};

ساكن فراغ handle_xdg_toplevel_decoration_configure(فراغ *داده,
                                                     بنية zxdg_toplevel_decoration_v1 *zxdg_toplevel_decoration_v1,
                                                     uint32_t نما)
{
    SDL_پنجره *پنجره = (SDL_پنجره *)داده;
    SDL_پنجره_داده *داخلی = پنجره->داخلی;
    SDL_VideoDevice *device = SDL_GetVideoDevice();

    /* If the compositor tries to force CSD anyway, bail on direct XDG support
     * and fall back to libdecor, it will handle these events from then on.
     *
     * To do this we have to fully unmap, then map with libdecor loaded.
     */
    إذا (نما == ZXDG_TOPLEVEL_DECORATION_V1_نما_CLIENT_SIDE) {
        إذا (پنجره->flags & SDL_پنجره_BORDERLESS) {
            // borderless windows do request CSD, so we got what we wanted
            أرجع;
        }
        إذا (!Wayland_بارگیری_Libdecor(داخلی->wayland_داده, true)) {
            // libdecor isn't available, so no borders for you... oh well
            أرجع;
        }
        WAYLAND_wl_display_roundtrip(داخلی->wayland_داده->display);

        Wayland_Hide_پنجره(device, پنجره);
        داخلی->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR;
        Wayland_Show_پنجره(device, پنجره);
    }
}

ساكن ثابت بنية zxdg_toplevel_decoration_v1_listener xdg_toplevel_decoration_listener = {
    handle_xdg_toplevel_decoration_configure
};

#اگر_تعریف_شده HAVE_LIBDECOR_H
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
ساكن فراغ OverrideLibdecorLimits(SDL_پنجره *پنجره)
{
#اگر_تعریف_شده SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    إذا (!libdecor_قاب_get_min_content_اندازه) {
        libdecor_قاب_مجموعه_min_content_اندازه(پنجره->داخلی->shell_surface.libdecor.قاب, پنجره->min_w, پنجره->min_h);
    }
#وإلاإذا !SDL_LIBDECOR_CHECK_نسخه(0, 2, 0)
    libdecor_قاب_مجموعه_min_content_اندازه(پنجره->داخلی->shell_surface.libdecor.قاب, پنجره->min_w, پنجره->min_h);
#پایان_اگر
}

/*
 * NOTE: Retrieves the minimum content size limits, if the function for doing so is available.
 *       On versions of libdecor that lack the minimum content size retrieval function, this
 *       function is a no-op.
 *
 *       Can be replaced with a direct call if the minimum required version of libdecor is raised
 *       to 0.1.2 or higher.
 */
ساكن فراغ Libdecor_Get_Min_Content_اندازه(بنية libdecor_قاب *قاب, صحيح *min_w, صحيح *min_h)
{
#اگر_تعریف_شده SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    إذا (libdecor_قاب_get_min_content_اندازه != عدم) {
        libdecor_قاب_get_min_content_اندازه(قاب, min_w, min_h);
    }
#وإلاإذا SDL_LIBDECOR_CHECK_نسخه(0, 2, 0)
    libdecor_قاب_get_min_content_اندازه(قاب, min_w, min_h);
#پایان_اگر
}

ساكن فراغ decoration_قاب_configure(بنية libdecor_قاب *قاب,
                                       بنية libdecor_configuration *configuration,
                                       فراغ *user_داده_2)
{
    SDL_پنجره_داده *wind = (SDL_پنجره_داده *)user_داده_2;
    SDL_پنجره *پنجره = wind->sdlwindow;

    تعداد libdecor_پنجره_state پنجره_state;
    صحيح عرض, ارتفاع;

    bool فعال = false;
    bool fullscreen = false;
    bool maximized = false;
    bool tiled = false;
    bool suspended = false;
    bool resizing = false;
    wind->toplevel_constraints = 0;

    ساكن ثابت تعداد libdecor_پنجره_state tiled_حالتها = (LIBDECOR_پنجره_STATE_TILED_چپ | LIBDECOR_پنجره_STATE_TILED_راست |
                                                            LIBDECOR_پنجره_STATE_TILED_بالاترین | LIBDECOR_پنجره_STATE_TILED_BOTTOM);

    إذا (wind->shell_surface_وضعیت == WAYLAND_SHELL_SURFACE_وضعیت_انتظار_FOR_CONFIGURE) {
        Libdecor_Get_Min_Content_اندازه(قاب, &wind->system_limits.min_عرض_2, &wind->system_limits.min_ارتفاع_2);
    }

    // Window State
    إذا (libdecor_configuration_get_پنجره_state(configuration, &پنجره_state)) {
        fullscreen = (پنجره_state & LIBDECOR_پنجره_STATE_FULLSCREEN) != 0;
        maximized = (پنجره_state & LIBDECOR_پنجره_STATE_MAXIMIZED) != 0;
        فعال = (پنجره_state & LIBDECOR_پنجره_STATE_فعال) != 0;
        tiled = (پنجره_state & tiled_حالتها) != 0;
#إذا SDL_LIBDECOR_CHECK_نسخه(0, 2, 0)
        suspended = (پنجره_state & LIBDECOR_پنجره_STATE_SUSPENDED) != 0;
#پایان_اگر
#إذا SDL_LIBDECOR_CHECK_نسخه(0, 3, 0)
        resizing = (پنجره_state & LIBDECOR_پنجره_STATE_RESIZING) != 0;

        إذا (پنجره_state & LIBDECOR_پنجره_STATE_CONSTRAINED_چپ) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_چپ;
        }
        إذا (پنجره_state & LIBDECOR_پنجره_STATE_CONSTRAINED_راست) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_راست;
        }
        إذا (پنجره_state & LIBDECOR_پنجره_STATE_CONSTRAINED_بالاترین) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_بالاترین;
        }
        إذا (پنجره_state & LIBDECOR_پنجره_STATE_CONSTRAINED_BOTTOM) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM;
        }
#پایان_اگر
    }
    ثابت bool floating = !(fullscreen || maximized || tiled);

    Update_پنجره_Fullscreen(پنجره, fullscreen);

    /* Always send a maximized/restore event; if the event is redundant it will
     * automatically be discarded (see src/events/SDL_windowevents.c)
     *
     * No, we do not get minimize events from libdecor, however, the minimized
     * state can be programmatically set. The meaning of 'minimized' is compositor
     * dependent, but in general, we can assume that the flag should remain set until
     * the next focused configure event occurs.
     */
    إذا (فعال || !(پنجره->flags & SDL_پنجره_MINIMIZED)) {
        إذا (پنجره->flags & SDL_پنجره_MINIMIZED) {
            // If we were minimized, send a restored event before possibly sending maximized.
            SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_RESTORED, 0, 0);
        }
        SDL_Send_پنجره_Event(پنجره,
                            (maximized && !fullscreen) ? SDL_EVENT_پنجره_MAXIMIZED : SDL_EVENT_پنجره_RESTORED,
                            0, 0);
    }

    /* For fullscreen or fixed-size windows we know our size.
     * Always assume the configure is wrong.
     */
    إذا (fullscreen) {
        إذا (!libdecor_configuration_get_content_اندازه(configuration, قاب, &عرض, &ارتفاع)) {
            عرض = wind->requested.logical_عرض;
            ارتفاع = wind->requested.logical_ارتفاع;
        } وإلا {
            // Fullscreen windows know their exact size.
            wind->requested.logical_عرض = عرض;
            wind->requested.logical_ارتفاع = ارتفاع;

            إذا (wind->scale_مقصد_display) {
                wind->requested.pixel_عرض = نقطه_مقصد_Pixel(پنجره, عرض);
                wind->requested.pixel_ارتفاع = نقطه_مقصد_Pixel(پنجره, ارتفاع);
            }
        }
    } وإلا {
        إذا (!(پنجره->flags & SDL_پنجره_RESIZABLE) && !maximized) {
            /* If we're a fixed-size, non-maximized window, we know our size for sure.
             * Always assume the configure is wrong.
             */
            إذا (!wind->scale_مقصد_display) {
                عرض = wind->requested.logical_عرض = پنجره->floating.w;
                ارتفاع = wind->requested.logical_ارتفاع = پنجره->floating.h;
            } وإلا {
                wind->requested.pixel_عرض = پنجره->floating.w;
                wind->requested.pixel_ارتفاع = پنجره->floating.h;
                عرض = wind->requested.logical_عرض = Pixel_مقصد_نقطه(پنجره, پنجره->floating.w);
                ارتفاع = wind->requested.logical_ارتفاع = Pixel_مقصد_نقطه(پنجره, پنجره->floating.h);
            }

            OverrideLibdecorLimits(پنجره);
        } وإلا {
            /* XXX: The libdecor cairo plugin sends bogus content sizes that add the
             *      height of the title bar when transitioning from a fixed-size to
             *      floating state. Ignore the sent window dimensions in this case,
             *      in favor of the cached value to avoid the window increasing in
             *      size after every state transition.
             *
             *      https://gitlab.freedesktop.org/libdecor/libdecor/-/issues/34
             */
            إذا ((floating && (!wind->floating && !(پنجره->flags & SDL_پنجره_BORDERLESS))) ||
                !libdecor_configuration_get_content_اندازه(configuration, قاب, &عرض, &ارتفاع)) {
                عرض = 0;
                ارتفاع = 0;
            }

            ثابت bool new_configure_اندازه = عرض != wind->آخرین_configure.عرض || ارتفاع != wind->آخرین_configure.ارتفاع;
            DetermineResizeAxis(wind, عرض, ارتفاع, resizing);

            إذا (!عرض) {
                /* This happens when we're being restored from a non-floating state,
                 * or the compositor indicates that the size is up to the client, so
                 * used the cached window size here.
                 */
                إذا (floating) {
                    عرض = پنجره->floating.w;

                    // Clamp the window to the toplevel bounds, if any are set.
                    إذا (wind->shell_surface_وضعیت == WAYLAND_SHELL_SURFACE_وضعیت_انتظار_FOR_CONFIGURE && wind->toplevel_bounds.عرض) {
                        عرض = SDL_min(wind->toplevel_bounds.عرض, عرض);
                    }
                } وإلا {
                    عرض = پنجره->windowed.w;
                }

                إذا (!wind->scale_مقصد_display) {
                    wind->requested.logical_عرض = عرض;
                } وإلا {
                    wind->requested.pixel_عرض = عرض;
                    عرض = wind->requested.logical_عرض = Pixel_مقصد_نقطه(پنجره, عرض);
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
                    !(wind->shell_surface_وضعیت == WAYLAND_SHELL_SURFACE_وضعیت_انتظار_FOR_قاب && wind->suspended != suspended)) {
                    wind->requested.logical_عرض = عرض;

                    إذا (wind->scale_مقصد_display) {
                        wind->requested.pixel_عرض = نقطه_مقصد_Pixel(پنجره, عرض);
                    }
                }
            }

            إذا (!ارتفاع) {
                /* This happens when we're being restored from a non-floating state,
                 * or the compositor indicates that the size is up to the client, so
                 * used the cached window size here.
                 */
                إذا (floating) {
                    ارتفاع = پنجره->floating.h;

                    // Clamp the window to the toplevel bounds, if any are set.
                    إذا (wind->shell_surface_وضعیت == WAYLAND_SHELL_SURFACE_وضعیت_انتظار_FOR_CONFIGURE && wind->toplevel_bounds.ارتفاع) {
                        ارتفاع = SDL_min(wind->toplevel_bounds.ارتفاع, ارتفاع);
                    }
                } وإلا {
                    ارتفاع = پنجره->windowed.h;
                }

                إذا (!wind->scale_مقصد_display) {
                    wind->requested.logical_ارتفاع = ارتفاع;
                } وإلا {
                    wind->requested.pixel_ارتفاع = ارتفاع;
                    ارتفاع = wind->requested.logical_ارتفاع = Pixel_مقصد_نقطه(پنجره, ارتفاع);
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
                    !(wind->shell_surface_وضعیت == WAYLAND_SHELL_SURFACE_وضعیت_انتظار_FOR_قاب && wind->suspended != suspended)) {
                    wind->requested.logical_ارتفاع = ارتفاع;

                    إذا (wind->scale_مقصد_display) {
                        wind->requested.pixel_ارتفاع = نقطه_مقصد_Pixel(پنجره, ارتفاع);
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
            إذا (!wind->scale_مقصد_display) {
                ApplyGeometryLimits(پنجره, wind->requested.logical_عرض, wind->requested.logical_ارتفاع, &wind->requested.logical_عرض, &wind->requested.logical_ارتفاع);
            } وإلا {
                ApplyGeometryLimits(پنجره, wind->requested.pixel_عرض, wind->requested.pixel_ارتفاع, &wind->requested.pixel_عرض, &wind->requested.pixel_ارتفاع);

                wind->requested.logical_عرض = Pixel_مقصد_نقطه(پنجره, wind->requested.pixel_عرض);
                wind->requested.logical_ارتفاع = Pixel_مقصد_نقطه(پنجره, wind->requested.pixel_ارتفاع);
            }
        }
    }

    // Store the new state.
    ثابت bool started_resize = !wind->resizing && resizing;
    wind->آخرین_configure.عرض = عرض;
    wind->آخرین_configure.ارتفاع = ارتفاع;
    wind->floating = floating;
    wind->suspended = suspended;
    wind->فعال = فعال;
    پنجره->tiled = tiled;
    wind->resizing = resizing;

    // Update the window manager capabilities.
#إذا SDL_LIBDECOR_CHECK_نسخه(0, 3, 0)
    تعداد libdecor_wm_capabilities caps;
#اگر_تعریف_شده SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    إذا (libdecor_قاب_get_wm_capabilities) {
        caps = libdecor_قاب_get_wm_capabilities(wind->shell_surface.libdecor.قاب);
#وإلا
    caps = libdecor_قاب_get_wm_capabilities(wind->shell_surface.libdecor.قاب);
    {
#پایان_اگر
        wind->wm_caps = 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_پنجره_MENU ? WAYLAND_WM_CAPS_پنجره_MENU : 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_MAXIMIZE ? WAYLAND_WM_CAPS_MAXIMIZE : 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_FULLSCREEN ? WAYLAND_WM_CAPS_FULLSCREEN : 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_MINIMIZE ? WAYLAND_WM_CAPS_MINIMIZE : 0;
    }
#پایان_اگر

    إذا (!wind->resizing || started_resize) {
        /* Calculate the new window geometry and commit the changes on the libdecor side.
         *
         * XXX: This will potentially leave un-acked configurations, but libdecor invalidates the
         *      configuration upon returning from the frame event, so there is nothing that can be
         *      done, unless libdecor adds the ability to copy or refcount the configuration state
         *      to apply later.
         */
        Configure_پنجره_Geometry(پنجره);
        بنية libdecor_state *state = libdecor_state_new(wind->current.logical_عرض, wind->current.logical_ارتفاع);
        libdecor_قاب_commit(قاب, state, configuration);
        libdecor_state_free(state);

        // Always send an exposure event during a new frame to ensure forward progress if the frame callback already occurred.
        إذا (started_resize) {
            SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_EXPOSED, 0, 0);
        }
    }

    إذا (wind->shell_surface_وضعیت == WAYLAND_SHELL_SURFACE_وضعیت_انتظار_FOR_CONFIGURE) {
        wind->shell_surface_وضعیت = WAYLAND_SHELL_SURFACE_وضعیت_انتظار_FOR_قاب;
    }
}

ساكن فراغ decoration_قاب_close(بنية libdecor_قاب *قاب, فراغ *user_داده_2)
{
    SDL_Send_پنجره_Event(((SDL_پنجره_داده *)user_داده_2)->sdlwindow, SDL_EVENT_پنجره_CLOSE_REQUESTED, 0, 0);
}

ساكن فراغ decoration_قاب_commit(بنية libdecor_قاب *قاب, فراغ *user_داده_2)
{
    /* libdecor decoration subsurfaces are synchronous, so the client needs to
     * commit a frame to trigger an update of the decoration surfaces.
     */
    SDL_پنجره_داده *wind = (SDL_پنجره_داده *)user_داده_2;
    إذا (!wind->suspended && wind->shell_surface_وضعیت == WAYLAND_SHELL_SURFACE_وضعیت_SHOWN) {
        SDL_Send_پنجره_Event(wind->sdlwindow, SDL_EVENT_پنجره_EXPOSED, 0, 0);
    }
}

ساكن فراغ decoration_dismiss_popup(بنية libdecor_قاب *قاب, ثابت حرف *seat_name, فراغ *user_داده_2)
{
    // NOP
}

#إذا SDL_LIBDECOR_CHECK_نسخه(0, 3, 0)
ساكن فراغ decoration_قاب_bounds(بنية libdecor_قاب *قاب, صحيح عرض, صحيح ارتفاع, فراغ *user_داده_2)
{
    SDL_پنجره_داده *پنجره = (SDL_پنجره_داده *)user_داده_2;
    پنجره->toplevel_bounds.عرض = عرض;
    پنجره->toplevel_bounds.ارتفاع = ارتفاع;
}
#پایان_اگر

ساكن بنية libdecor_قاب_interface libdecor_قاب_interface = {
    decoration_قاب_configure,
    decoration_قاب_close,
    decoration_قاب_commit,
    decoration_dismiss_popup,
#إذا SDL_LIBDECOR_CHECK_نسخه(0, 3, 0)
    decoration_قاب_bounds
#پایان_اگر
};
#پایان_اگر

ساكن فراغ Wayland_Handle_Preferred_Scale_تغییریافته(SDL_پنجره_داده *پنجره_داده_2, مزدوج ضریب)
{
    ثابت مزدوج old_ضریب = پنجره_داده_2->scale_ضریب_2;

    // Round the scale factor if viewports aren't available.
    إذا (!پنجره_داده_2->viewport) {
        ضریب = SDL_ceil(ضریب);
    }

    إذا (ضریب != old_ضریب) {
        پنجره_داده_2->scale_ضریب_2 = ضریب;

        إذا (پنجره_داده_2->scale_مقصد_display) {
            /* If the window is in the floating state with a user/application specified size, calculate the new
             * logical size from the backbuffer size. Otherwise, use the fixed underlying logical size to calculate
             * the new backbuffer dimensions.
             */
            إذا (پنجره_داده_2->floating) {
                /* Some compositors will send a configure event immediately after a scale event, however,
                 * this event can contain the old logical size, and should be ignored, or the window can
                 * incorrectly change size when moved between displays with differing scale factors.
                 *
                 * Store the last requested logical size as the last configure size, so a configure event
                 * with the old size will be ignored. Configure sizes are in window geometry space,
                 * so subtract any border insets.
                 */
                BorderInsets insets;
                GetBorderInsets(پنجره_داده_2->sdlwindow, &insets);
                پنجره_داده_2->آخرین_configure.عرض = SDL_max(پنجره_داده_2->requested.logical_عرض - (insets.چپ + insets.راست), 1);
                پنجره_داده_2->آخرین_configure.ارتفاع = SDL_max(پنجره_داده_2->requested.logical_ارتفاع - (insets.بالاترین + insets.bottom), 1);

                پنجره_داده_2->requested.logical_عرض = Pixel_مقصد_نقطه(پنجره_داده_2->sdlwindow, پنجره_داده_2->requested.pixel_عرض);
                پنجره_داده_2->requested.logical_ارتفاع = Pixel_مقصد_نقطه(پنجره_داده_2->sdlwindow, پنجره_داده_2->requested.pixel_ارتفاع);
            } وإلا {
                پنجره_داده_2->requested.pixel_عرض = نقطه_مقصد_Pixel(پنجره_داده_2->sdlwindow, پنجره_داده_2->requested.logical_عرض);
                پنجره_داده_2->requested.pixel_ارتفاع = نقطه_مقصد_Pixel(پنجره_داده_2->sdlwindow, پنجره_داده_2->requested.logical_ارتفاع);
            }
        }

        إذا (پنجره_داده_2->sdlwindow->flags & SDL_پنجره_بالا_PIXEL_DENSITY || پنجره_داده_2->scale_مقصد_display) {
            Configure_پنجره_Geometry(پنجره_داده_2->sdlwindow);
            Commit_Libdecor_قاب(پنجره_داده_2->sdlwindow);
        }
    }
}

ساكن فراغ Wayland_Maybe_Update_Scale_ضریب(SDL_پنجره_داده *پنجره)
{
    مزدوج ضریب;
    صحيح i;

    /* If the fractional scale protocol is present or the core protocol supports the
     * preferred buffer scale event, the compositor will explicitly tell the application
     * what scale it wants via these events, so don't try to determine the scale factor
     * from which displays the surface has entered.
     */
    إذا (پنجره->fractional_scale || wl_surface_get_نسخه(پنجره->surface) >= WL_SURFACE_PREFERRED_میانگیر_SCALE_SINCE_نسخه) {
        أرجع;
    }

    إذا (پنجره->رقم_outputs != 0) {
        // Check every display's factor, use the highest
        ضریب = 0.0;
        لكل (i = 0; i < پنجره->رقم_outputs; i++) {
            SDL_Display_داده *داخلی = پنجره->outputs[i];
            ضریب = SDL_max(ضریب, داخلی->scale_ضریب_2);
        }
    } وإلا {
        // All outputs removed, just fall back.
        ضریب = پنجره->scale_ضریب_2;
    }

    Wayland_Handle_Preferred_Scale_تغییریافته(پنجره, ضریب);
}

فراغ Wayland_Remove_Output_From_پنجره(SDL_پنجره_داده *پنجره, SDL_Display_داده *display_داده)
{
    لكل (صحيح i = 0; i < پنجره->رقم_outputs; i++) {
        إذا (پنجره->outputs[i] == display_داده) { // remove this one
            إذا (i == (پنجره->رقم_outputs - 1)) {
                پنجره->outputs[i] = عدم;
            } وإلا {
                SDL_memmove(&پنجره->outputs[i],
                            &پنجره->outputs[i + 1],
                            حجم(SDL_Display_داده *) * ((پنجره->رقم_outputs - i) - 1));
            }
            پنجره->رقم_outputs--;
            i--;
        }
    }

    إذا (پنجره->رقم_outputs == 0) {
        SDL_free(پنجره->outputs);
        پنجره->outputs = عدم;
    } وإلا إذا (!پنجره->is_fullscreen || پنجره->رقم_outputs == 1) {
        Wayland_Update_پنجره_Position(پنجره->sdlwindow);
        Wayland_Maybe_Update_Scale_ضریب(پنجره);
    }
}

ساكن فراغ handle_surface_enter(فراغ *داده, بنية wl_surface *surface, بنية wl_output *output)
{
    SDL_پنجره_داده *پنجره = داده;
    SDL_Display_داده *داخلی = wl_output_get_user_داده(output);
    SDL_Display_داده **new_outputs;

    إذا (!SDL_WAYLAND_own_output(output) || !SDL_WAYLAND_own_surface(surface)) {
        أرجع;
    }

    new_outputs = SDL_realloc(پنجره->outputs,
                              حجم(SDL_Display_داده *) * (پنجره->رقم_outputs + 1));
    إذا (!new_outputs) {
        أرجع;
    }
    پنجره->outputs = new_outputs;
    پنجره->outputs[پنجره->رقم_outputs++] = داخلی;

    // Update the scale factor after the move so that fullscreen outputs are updated.
    إذا (!پنجره->is_fullscreen || پنجره->رقم_outputs == 1) {
        Wayland_Update_پنجره_Position(پنجره->sdlwindow);
        Wayland_Maybe_Update_Scale_ضریب(پنجره);
    }
}

ساكن فراغ handle_surface_leave(فراغ *داده, بنية wl_surface *surface, بنية wl_output *output)
{
    SDL_پنجره_داده *پنجره = (SDL_پنجره_داده *)داده;

    إذا (!SDL_WAYLAND_own_output(output) || !SDL_WAYLAND_own_surface(surface)) {
        أرجع;
    }

    Wayland_Remove_Output_From_پنجره(پنجره, (SDL_Display_داده *)wl_output_get_user_داده(output));
}

ساكن فراغ handle_surface_preferred_میانگیر_scale(فراغ *داده, بنية wl_surface *wl_surface, int32_t ضریب)
{
    SDL_پنجره_داده *wind = داده;

    /* The spec is unclear on how this interacts with the fractional scaling protocol,
     * so, for now, assume that the fractional scaling protocol takes priority and
     * only listen to this event if the fractional scaling protocol is not present.
     */
    إذا (!wind->fractional_scale) {
        Wayland_Handle_Preferred_Scale_تغییریافته(داده, (مزدوج)ضریب);
    }
}

ساكن فراغ handle_surface_preferred_میانگیر_transform(فراغ *داده, بنية wl_surface *wl_surface, uint32_t transform)
{
    // Nothing to do here.
}

ساكن ثابت بنية wl_surface_listener surface_listener = {
    handle_surface_enter,
    handle_surface_leave,
    handle_surface_preferred_میانگیر_scale,
    handle_surface_preferred_میانگیر_transform
};

ساكن فراغ handle_fractional_scale_preferred(فراغ *داده, بنية wp_fractional_scale_v1 *wp_fractional_scale_v1, uint32_t scale)
{
    ثابت مزدوج ضریب = (مزدوج)scale / 120.; // 120 is a magic number defined in the spec as a common denominator
    Wayland_Handle_Preferred_Scale_تغییریافته(داده, ضریب);
}

ساكن ثابت بنية wp_fractional_scale_v1_listener fractional_scale_listener = {
    handle_fractional_scale_preferred
};

ساكن فراغ frog_preferred_metadata_handler(فراغ *داده, بنية frog_color_managed_surface *frog_color_managed_surface, uint32_t transfer_function,
                                            uint32_t output_display_primary_red_x, uint32_t output_display_primary_red_y,
                                            uint32_t output_display_primary_green_x, uint32_t output_display_primary_green_y,
                                            uint32_t output_display_primary_blue_x, uint32_t output_display_primary_blue_y,
                                            uint32_t output_white_نقطه_x, uint32_t output_white_نقطه_y,
                                            uint32_t max_luminance, uint32_t min_luminance,
                                            uint32_t max_پر_قاب_luminance)
{
    SDL_پنجره_داده *wind = (SDL_پنجره_داده *)داده;
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
    SDL_مجموعه_پنجره_HDRProperties(wind->sdlwindow, &HDR, true);
}

ساكن ثابت بنية frog_color_managed_surface_listener frog_surface_listener = {
    frog_preferred_metadata_handler
};


ساكن فراغ handle_surface_feedback_preferred_changed2(فراغ *داده,
                                                       بنية wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback_v1,
                                                       uint32_t عنصر_خنثی_hi, uint32_t عنصر_خنثی_lo)
{
    SDL_پنجره_داده *wind = (SDL_پنجره_داده *)داده;
    Wayland_Get_Color_Info_For_پنجره(wind, false);
}

ساكن فراغ handle_surface_feedback_preferred_تغییریافته(فراغ *داده,
                                                      بنية wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback_v1,
                                                      uint32_t عنصر_خنثی)
{
    handle_surface_feedback_preferred_changed2(داده, wp_color_management_surface_feedback_v1, 0, عنصر_خنثی);
}

ساكن ثابت بنية wp_color_management_surface_feedback_v1_listener color_management_surface_feedback_listener = {
    handle_surface_feedback_preferred_تغییریافته,
    handle_surface_feedback_preferred_changed2
};

ساكن فراغ Wayland_مجموعه_Keyboard_Focus(SDL_پنجره *پنجره, bool مجموعه_focus)
{
    SDL_پنجره *toplevel = پنجره;

    // Find the toplevel parent
    طالما (SDL_پنجره_IS_POPUP(toplevel)) {
        toplevel = toplevel->والد;
    }

    toplevel->keyboard_focus = پنجره;

    إذا (مجموعه_focus && !پنجره->is_hiding && !پنجره->is_destroying) {
        SDL_مجموعه_Keyboard_Focus(پنجره);
    }
}

bool Wayland_مجموعه_پنجره_اصابت_Test(SDL_پنجره *پنجره, bool enabled)
{
    أرجع true; // just succeed, the real work is done elsewhere.
}

ساكن بنية xdg_toplevel *Get_Toplevel_For_پنجره(SDL_پنجره_داده *wind)
{
    إذا (wind) {
        /* Libdecor crashes on attempts to unset the parent by passing null, which is allowed by the
         * toplevel spec, so just use the raw xdg-toplevel instead (that's what libdecor does
         * internally anyways).
         */
#اگر_تعریف_شده HAVE_LIBDECOR_H
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.قاب) {
            أرجع libdecor_قاب_get_xdg_toplevel(wind->shell_surface.libdecor.قاب);
        } وإلا
#پایان_اگر
            إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
                أرجع wind->shell_surface.xdg.toplevel.xdg_toplevel;
            }
    }

    أرجع عدم;
}

bool Wayland_مجموعه_پنجره_والد(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_پنجره *والد_پنجره)
{
    SDL_پنجره_داده *فرزند_داده = پنجره->داخلی;
    SDL_پنجره_داده *والد_داده = والد_پنجره ? والد_پنجره->داخلی : عدم;

    فرزند_داده->reparenting_required = false;

    إذا (والد_داده && والد_داده->shell_surface_وضعیت != WAYLAND_SHELL_SURFACE_وضعیت_SHOWN) {
        // Need to wait for the parent to become mapped, or it's the same as setting a null parent.
        فرزند_داده->reparenting_required = true;
        أرجع true;
    }

    بنية xdg_toplevel *فرزند_toplevel = Get_Toplevel_For_پنجره(فرزند_داده);
    بنية xdg_toplevel *والد_toplevel = Get_Toplevel_For_پنجره(والد_داده);

    إذا (فرزند_toplevel) {
        xdg_toplevel_مجموعه_والد(فرزند_toplevel, والد_toplevel);
    }

    أرجع true;
}

bool Wayland_مجموعه_پنجره_Modal(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool modal)
{
    SDL_Video_داده *viddata = _this->داخلی;
    SDL_پنجره_داده *داده = پنجره->داخلی;
    SDL_پنجره_داده *والد_داده = پنجره->والد->داخلی;

    إذا (والد_داده->shell_surface_وضعیت != WAYLAND_SHELL_SURFACE_وضعیت_SHOWN) {
        // Need to wait for the parent to become mapped before changing modal status.
        داده->reparenting_required = true;
        أرجع true;
    } وإلا {
        داده->reparenting_required = false;
    }

    بنية xdg_toplevel *toplevel = Get_Toplevel_For_پنجره(داده);

    إذا (toplevel) {
        إذا (viddata->xdg_wm_dialog_v1) {
            إذا (modal) {
                إذا (!داده->xdg_dialog_v1) {
                    داده->xdg_dialog_v1 = xdg_wm_dialog_v1_get_xdg_dialog(viddata->xdg_wm_dialog_v1, toplevel);
                }

                xdg_dialog_v1_مجموعه_modal(داده->xdg_dialog_v1);
            } وإلا إذا (داده->xdg_dialog_v1) {
                xdg_dialog_v1_unset_modal(داده->xdg_dialog_v1);
            }
        }
    }

    أرجع true;
}

ساكن فراغ Wayland_ثبات_Toplevel_For_Session(SDL_پنجره_داده *داده)
{
    بنية xdg_toplevel *toplevel = Get_Toplevel_For_پنجره(داده);
    إذا (!toplevel) {
        أرجع;
    }

    ثابت حرف *id = SDL_GetStringProperty(داده->sdlwindow->props, SDL_PROP_پنجره_WAYLAND_پنجره_ID_STRING, عدم);
    إذا (id && *id != '\0') {
        SDL_VideoDevice *viddev = SDL_GetVideoDevice();
        SDL_Video_داده *viddata = viddev->داخلی;

        إذا (viddata->xdg_toplevel_برچسب_manager) {
            xdg_toplevel_برچسب_manager_v1_مجموعه_toplevel_برچسب(viddata->xdg_toplevel_برچسب_manager, toplevel, id);
        }

        إذا (viddata->xdg_session_manager) {
            Wayland_CreateSession(viddata);

            إذا (viddata->xdg_session) {
                CHECK_PARAM (true) {
                    // Windows added to a session must not have a duplicate ID string, or a protocol error will result.
                    لكل (SDL_پنجره *w = viddev->windows; w; w = w->بعدی) {
                        SDL_پنجره_داده *d = w->داخلی;
                        إذا (d->session_id && SDL_strcmp(d->session_id, id) == 0) {
                            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Duplicate window ID string %s found; window will not be added to session", id);
                            أرجع;
                        }
                    }
                }

                داده->xdg_toplevel_session = xdg_session_v1_restore_toplevel(viddata->xdg_session, toplevel, id);
                داده->session_id = SDL_strdup(id);
            }
        }
    }
}

ساكن فراغ Wayland_DestroyToplevelSession(SDL_پنجره_داده *داده)
{
    SDL_Video_داده *viddata = داده->wayland_داده;

    إذا (داده->xdg_toplevel_session) {
        ثابت حرف *id = SDL_GetStringProperty(داده->sdlwindow->props, SDL_PROP_پنجره_WAYLAND_پنجره_ID_STRING, عدم);

        // If the ID string was cleared, remove the window from the session.
        إذا (!id || *id == '\0') {
            xdg_session_v1_remove_toplevel(viddata->xdg_session, داده->session_id);
        }

        xdg_toplevel_session_v1_destroy(داده->xdg_toplevel_session);
        داده->xdg_toplevel_session = عدم;

        SDL_free(داده->session_id);
        داده->session_id = عدم;
    }
}

ساكن فراغ show_hide_sync_handler(فراغ *داده, بنية wl_callback *callback, uint32_t callback_داده)
{
    // Get the window from the ID as it may have been destroyed
    SDL_پنجره_ID پنجره_ID = (SDL_پنجره_ID)((uintptr_t)داده);
    SDL_پنجره *پنجره = SDL_Get_پنجره_From_ID(پنجره_ID);

    إذا (پنجره && پنجره->داخلی) {
        SDL_پنجره_داده *wind = پنجره->داخلی;
        wind->show_hide_sync_required = false;
    }

    wl_callback_destroy(callback);
}

ساكن بنية wl_callback_listener show_hide_sync_listener = {
    show_hide_sync_handler
};

ساكن فراغ exported_handle_handler(فراغ *داده, بنية zxdg_exported_v2 *zxdg_exported_v2, ثابت حرف *handle)
{
    SDL_پنجره_داده *wind = (SDL_پنجره_داده *)داده;
    SDL_PropertiesID props = SDL_Get_پنجره_Properties(wind->sdlwindow);

    SDL_مجموعه_String_Property(props, SDL_PROP_پنجره_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, handle);
}

ساكن بنية zxdg_exported_v2_listener exported_v2_listener = {
    exported_handle_handler
};

فراغ Wayland_Show_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_Video_داده *c = _this->داخلی;
    SDL_پنجره_داده *داده = پنجره->داخلی;
    SDL_PropertiesID props = SDL_Get_پنجره_Properties(پنجره);

    // Custom surfaces don't get toplevels and are always considered 'shown'; nothing to do here.
    إذا (داده->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
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
    إذا (پنجره->والد) {
        إذا (پنجره->والد->داخلی->shell_surface_وضعیت != WAYLAND_SHELL_SURFACE_وضعیت_SHOWN) {
            داده->shell_surface_وضعیت = WAYLAND_SHELL_SURFACE_وضعیت_SHOW_PENDING;
            أرجع;
        }
    }

    // Always roundtrip to ensure there are no pending buffer attachments.
    افعل {
        WAYLAND_wl_display_roundtrip(c->display);
    } طالما (داده->show_hide_sync_required);

    داده->shell_surface_وضعیت = WAYLAND_SHELL_SURFACE_وضعیت_انتظار_FOR_CONFIGURE;

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
    wl_surface_attach(داده->surface, عدم, 0, 0);
    wl_surface_commit(داده->surface);

    // Create the shell surface and map the toplevel/popup
#اگر_تعریف_شده HAVE_LIBDECOR_H
    إذا (داده->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        داده->shell_surface.libdecor.قاب = libdecor_decorate(c->shell.libdecor,
                                                               داده->surface,
                                                               &libdecor_قاب_interface,
                                                               داده);
        إذا (!داده->shell_surface.libdecor.قاب) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Failed to create libdecor frame!");
        } وإلا {
            libdecor_قاب_مجموعه_app_id(داده->shell_surface.libdecor.قاب, داده->app_id);
            libdecor_قاب_map(داده->shell_surface.libdecor.قاب);
            إذا (پنجره->flags & SDL_پنجره_BORDERLESS) {
                // Note: Calling this with 'true' immediately after mapping will cause the libdecor Cairo plugin to crash.
                libdecor_قاب_مجموعه_visibility(داده->shell_surface.libdecor.قاب, false);
            }

            إذا (c->zxdg_exporter_v2) {
                داده->exported = zxdg_exporter_v2_export_toplevel(c->zxdg_exporter_v2, داده->surface);
                zxdg_exported_v2_جمع_کن_listener(داده->exported, &exported_v2_listener, داده);
            }

            إذا (c->xdg_toplevel_icon_manager_v1 && داده->xdg_toplevel_icon_v1) {
                xdg_toplevel_icon_manager_v1_مجموعه_icon(_this->داخلی->xdg_toplevel_icon_manager_v1,
                                                      libdecor_قاب_get_xdg_toplevel(داده->shell_surface.libdecor.قاب),
                                                      داده->xdg_toplevel_icon_v1);
            }

            SDL_مجموعه_اشاره_گر_Property(props, SDL_PROP_پنجره_WAYLAND_XDG_SURFACE_اشاره_گر, libdecor_قاب_get_xdg_surface(داده->shell_surface.libdecor.قاب));
            SDL_مجموعه_اشاره_گر_Property(props, SDL_PROP_پنجره_WAYLAND_XDG_TOPLEVEL_اشاره_گر, libdecor_قاب_get_xdg_toplevel(داده->shell_surface.libdecor.قاب));
        }
    } وإلا
#پایان_اگر
    إذا (داده->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL || داده->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        داده->shell_surface.xdg.surface = xdg_wm_پایه_get_xdg_surface(c->shell.xdg, داده->surface);
        xdg_surface_مجموعه_user_داده(داده->shell_surface.xdg.surface, داده);
        xdg_surface_جمع_کن_listener(داده->shell_surface.xdg.surface, &_xdg_surface_listener, داده);
        SDL_مجموعه_اشاره_گر_Property(SDL_Get_پنجره_Properties(پنجره), SDL_PROP_پنجره_WAYLAND_XDG_SURFACE_اشاره_گر, داده->shell_surface.xdg.surface);

        إذا (داده->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
            SDL_پنجره *والد = پنجره->والد;
            SDL_پنجره_داده *والد_داده = والد->داخلی;
            بنية xdg_surface *والد_xdg_surface = عدم;
            صحيح position_x = 0, position_y = 0;

            // Configure the popup parameters
#اگر_تعریف_شده HAVE_LIBDECOR_H
            إذا (والد_داده->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                والد_xdg_surface = libdecor_قاب_get_xdg_surface(والد_داده->shell_surface.libdecor.قاب);
            } وإلا
#پایان_اگر
            إذا (والد_داده->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL ||
                    والد_داده->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
                والد_xdg_surface = والد_داده->shell_surface.xdg.surface;
            }

            // Set up the positioner for the popup and configure the constraints
            داده->shell_surface.xdg.popup.xdg_positioner = xdg_wm_پایه_create_positioner(c->shell.xdg);
            xdg_positioner_مجموعه_anchor(داده->shell_surface.xdg.popup.xdg_positioner, XDG_POSITIONER_ANCHOR_بالاترین_چپ);
            SDL_Rect والد_geometry;
            Get_پنجره_Geometry(والد->داخلی, &والد_geometry);
            xdg_positioner_مجموعه_anchor_rect(داده->shell_surface.xdg.popup.xdg_positioner, 0, 0, والد_geometry.w, والد_geometry.h);

            ثابت Uint32 constraint = پنجره->constrain_popup ? (XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_SLIDE_X | XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_SLIDE_Y) : XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_NONE;
            xdg_positioner_مجموعه_constraint_adjustment(داده->shell_surface.xdg.popup.xdg_positioner, constraint);
            xdg_positioner_مجموعه_gravity(داده->shell_surface.xdg.popup.xdg_positioner, XDG_POSITIONER_GRAVITY_BOTTOM_راست);
            xdg_positioner_مجموعه_اندازه(داده->shell_surface.xdg.popup.xdg_positioner, داده->current.logical_عرض, داده->current.logical_ارتفاع);

            // Set the popup initial position
            position_x = پنجره->آخرین_position_pending ? پنجره->pending.x : پنجره->x;
            position_y = پنجره->آخرین_position_pending ? پنجره->pending.y : پنجره->y;
            EnsurePopupPositionIsValid(پنجره, &position_x, &position_y);
            إذا (داده->scale_مقصد_display) {
                position_x = Pixel_مقصد_نقطه(پنجره->والد, position_x);
                position_y = Pixel_مقصد_نقطه(پنجره->والد, position_y);
            }
            Adjust_Popup_جابه_جایی(پنجره, &position_x, &position_y);
            xdg_positioner_مجموعه_جابه_جایی(داده->shell_surface.xdg.popup.xdg_positioner, position_x, position_y);

            // Assign the popup role
            داده->shell_surface.xdg.popup.xdg_popup = xdg_surface_get_popup(داده->shell_surface.xdg.surface,
                                                                                والد_xdg_surface,
                                                                                داده->shell_surface.xdg.popup.xdg_positioner);
            xdg_popup_جمع_کن_listener(داده->shell_surface.xdg.popup.xdg_popup, &_xdg_popup_listener, داده);

            إذا (پنجره->flags & SDL_پنجره_TOOLTIP) {
                بنية wl_region *region;

                // Tooltips can't be interacted with, so turn off the input region to avoid blocking anything behind them
                region = wl_compositor_create_region(c->compositor);
                wl_region_جمع_کن(region, 0, 0, 0, 0);
                wl_surface_مجموعه_درون_داد_region(داده->surface, region);
                wl_region_destroy(region);
            } وإلا إذا ((پنجره->flags & SDL_پنجره_POPUP_MENU) && !(پنجره->flags & SDL_پنجره_NOT_FOCUSABLE)) {
                Wayland_مجموعه_Keyboard_Focus(پنجره, true);
            }

            SDL_مجموعه_اشاره_گر_Property(props, SDL_PROP_پنجره_WAYLAND_XDG_POPUP_اشاره_گر, داده->shell_surface.xdg.popup.xdg_popup);
            SDL_مجموعه_اشاره_گر_Property(props, SDL_PROP_پنجره_WAYLAND_XDG_POSITIONER_اشاره_گر, داده->shell_surface.xdg.popup.xdg_positioner);
        } وإلا {
            داده->shell_surface.xdg.toplevel.xdg_toplevel = xdg_surface_get_toplevel(داده->shell_surface.xdg.surface);
            xdg_toplevel_مجموعه_app_id(داده->shell_surface.xdg.toplevel.xdg_toplevel, داده->app_id);
            xdg_toplevel_جمع_کن_listener(داده->shell_surface.xdg.toplevel.xdg_toplevel, &toplevel_listener_xdg, داده);

            // Create the window decorations
            إذا (c->decoration_manager) {
                داده->server_decoration = zxdg_decoration_manager_v1_get_toplevel_decoration(c->decoration_manager, داده->shell_surface.xdg.toplevel.xdg_toplevel);
                zxdg_toplevel_decoration_v1_جمع_کن_listener(داده->server_decoration, &xdg_toplevel_decoration_listener, پنجره);
                ثابت تعداد zxdg_toplevel_decoration_v1_نما نما = !(پنجره->flags & SDL_پنجره_BORDERLESS) ? ZXDG_TOPLEVEL_DECORATION_V1_نما_SERVER_SIDE : ZXDG_TOPLEVEL_DECORATION_V1_نما_CLIENT_SIDE;
                zxdg_toplevel_decoration_v1_مجموعه_نما(داده->server_decoration, نما);
            }

            إذا (c->zxdg_exporter_v2) {
                داده->exported = zxdg_exporter_v2_export_toplevel(c->zxdg_exporter_v2, داده->surface);
                zxdg_exported_v2_جمع_کن_listener(داده->exported, &exported_v2_listener, داده);
            }

            إذا (c->xdg_toplevel_icon_manager_v1 && داده->xdg_toplevel_icon_v1) {
                xdg_toplevel_icon_manager_v1_مجموعه_icon(_this->داخلی->xdg_toplevel_icon_manager_v1,
                                                      داده->shell_surface.xdg.toplevel.xdg_toplevel,
                                                      داده->xdg_toplevel_icon_v1);
            }

            SDL_مجموعه_اشاره_گر_Property(props, SDL_PROP_پنجره_WAYLAND_XDG_TOPLEVEL_اشاره_گر, داده->shell_surface.xdg.toplevel.xdg_toplevel);
        }
    }

    // Restore state that was set prior to this call
    Wayland_ثبات_Toplevel_For_Session(داده);
    Wayland_مجموعه_پنجره_والد(_this, پنجره, پنجره->والد);

    إذا (پنجره->flags & SDL_پنجره_MODAL) {
        Wayland_مجموعه_پنجره_Modal(_this, پنجره, true);
    }

    Wayland_مجموعه_پنجره_Title(_this, پنجره);

    /* We have to wait until the surface gets a "configure" event, or use of
     * this surface will fail. This is a new rule for xdg_shell.
     */
#اگر_تعریف_شده HAVE_LIBDECOR_H
    إذا (داده->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (داده->shell_surface.libdecor.قاب) {
            طالما (داده->shell_surface_وضعیت == WAYLAND_SHELL_SURFACE_وضعیت_انتظار_FOR_CONFIGURE) {
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
#پایان_اگر
        إذا (داده->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP || داده->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        /* Unlike libdecor we need to call this explicitly to prevent a deadlock.
         * libdecor will call this as part of their configure event!
         * -flibit
         */
        wl_surface_commit(داده->surface);
        إذا (داده->shell_surface.xdg.surface) {
            طالما (داده->shell_surface_وضعیت == WAYLAND_SHELL_SURFACE_وضعیت_انتظار_FOR_CONFIGURE) {
                إذا (WAYLAND_wl_display_dispatch(c->display) < 0) {
                    إذا (!Wayland_HandleDisplayDisconnected(_this)) {
                        أرجع;
                    }
                }
            }
        }
    } وإلا {
        // Nothing to see here, just commit.
        wl_surface_commit(داده->surface);
    }

    // Make sure the window can't be resized to 0, or it can be spuriously closed by the window manager.
    داده->system_limits.min_عرض_2 = SDL_max(داده->system_limits.min_عرض_2, 1);
    داده->system_limits.min_ارتفاع_2 = SDL_max(داده->system_limits.min_ارتفاع_2, 1);

    /* Unlike the rest of window state we have to set this _after_ flushing the
     * display, because we need to create the decorations before possibly hiding
     * them immediately afterward.
     */
#اگر_تعریف_شده HAVE_LIBDECOR_H
    إذا (داده->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        // Libdecor plugins can enforce minimum window sizes, so adjust if the initial window size is too small.
        إذا (پنجره->windowed.w < داده->system_limits.min_عرض_2 ||
            پنجره->windowed.h < داده->system_limits.min_ارتفاع_2) {

            // Warn if the window frame will be larger than the content surface.
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO,
                        "Window dimensions (%i, %i) are smaller than the system enforced minimum (%i, %i); window borders will be larger than the content surface.",
                        پنجره->windowed.w, پنجره->windowed.h, داده->system_limits.min_عرض_2, داده->system_limits.min_ارتفاع_2);

            داده->current.logical_عرض = SDL_max(پنجره->windowed.w, داده->system_limits.min_عرض_2);
            داده->current.logical_ارتفاع = SDL_max(پنجره->windowed.h, داده->system_limits.min_ارتفاع_2);
            Commit_Libdecor_قاب(پنجره);
        }
    }
#پایان_اگر
    Wayland_مجموعه_پنجره_Resizable(_this, پنجره, !!(پنجره->flags & SDL_پنجره_RESIZABLE));

    // We're finally done putting the window together, raise if possible
    إذا (c->activation_manager && SDL_GetHintBoolean(SDL_HINT_پنجره_ACTIVATE_WHEN_SHOWN, true)) {
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
                                       داده->surface);

            // Clear this variable, per the protocol's request
            SDL_unsetenv_unsafe("XDG_ACTIVATION_TOKEN");
        } وإلا {
            // Try to generate an activation token for this window.
            Wayland_Raise_پنجره(_this, پنجره);
        }
    } وإلا {
        // Clear the ignored activation token, as it won't be used.
        SDL_unsetenv_unsafe("XDG_ACTIVATION_TOKEN");
    }

    // No frame callback on an external surface, as it may already have one attached.
    إذا (!(پنجره->flags & SDL_پنجره_EXTERNAL)) {
        // Fire a callback when the compositor wants a new frame.
        داده->surface_قاب_callback = wl_surface_قاب(داده->surface);
        wl_callback_جمع_کن_listener(داده->surface_قاب_callback, &surface_قاب_listener, داده);
    }

    داده->show_hide_sync_required = true;
    بنية wl_callback *cb = wl_display_sync(_this->داخلی->display);
    wl_callback_جمع_کن_listener(cb, &show_hide_sync_listener, (فراغ *)((uintptr_t)پنجره->id));

    داده->showing_پنجره = true;
    SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_SHOWN, 0, 0);
    داده->showing_پنجره = false;

    // Send an exposure event to signal that the client should draw.
    SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_EXPOSED, 0, 0);
}

ساكن فراغ Wayland_ReleasePopup(SDL_VideoDevice *_this, SDL_پنجره *popup)
{
    SDL_پنجره_داده *popupdata;

    // Basic sanity checks to weed out the weird popup closures
    إذا (!SDL_ObjectValid(popup, SDL_OBJECT_TYPE_پنجره)) {
        أرجع;
    }
    popupdata = popup->داخلی;
    إذا (!popupdata) {
        أرجع;
    }

    // This may already be freed by a parent popup!
    إذا (popupdata->shell_surface.xdg.popup.xdg_popup == عدم) {
        أرجع;
    }

    إذا ((popup->flags & SDL_پنجره_POPUP_MENU) && !(popup->flags & SDL_پنجره_NOT_FOCUSABLE)) {
        SDL_پنجره *new_focus;
        ثابت bool مجموعه_focus = SDL_ShouldRelinquishPopupFocus(popup, &new_focus);
        Wayland_مجموعه_Keyboard_Focus(new_focus, مجموعه_focus);
    }

    xdg_popup_destroy(popupdata->shell_surface.xdg.popup.xdg_popup);
    xdg_positioner_destroy(popupdata->shell_surface.xdg.popup.xdg_positioner);
    popupdata->shell_surface.xdg.popup.xdg_popup = عدم;
    popupdata->shell_surface.xdg.popup.xdg_positioner = عدم;

    SDL_PropertiesID props = SDL_Get_پنجره_Properties(popup);
    SDL_مجموعه_اشاره_گر_Property(props, SDL_PROP_پنجره_WAYLAND_XDG_POPUP_اشاره_گر, عدم);
    SDL_مجموعه_اشاره_گر_Property(props, SDL_PROP_پنجره_WAYLAND_XDG_POSITIONER_اشاره_گر, عدم);
}

فراغ Wayland_Hide_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_Video_داده *داده = _this->داخلی;
    SDL_پنجره_داده *wind = پنجره->داخلی;
    SDL_PropertiesID props = SDL_Get_پنجره_Properties(پنجره);

    // Custom surfaces have nothing to destroy and are always considered to be 'shown'; nothing to do here.
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        أرجع;
    }

    /* The window was shown, but the sync point hasn't yet been reached.
     * Pump events to avoid a possible protocol violation.
     */
    إذا (wind->show_hide_sync_required) {
        WAYLAND_wl_display_roundtrip(داده->display);
    }

    wind->shell_surface_وضعیت = WAYLAND_SHELL_SURFACE_وضعیت_HIDDEN;

    إذا (wind->surface_قاب_callback) {
        wl_callback_destroy(wind->surface_قاب_callback);
        wind->surface_قاب_callback = عدم;
    }

    إذا (wind->server_decoration) {
        zxdg_toplevel_decoration_v1_destroy(wind->server_decoration);
        wind->server_decoration = عدم;
    }

    // Clean up the export handle.
    إذا (wind->exported) {
        zxdg_exported_v2_destroy(wind->exported);
        wind->exported = عدم;

        SDL_مجموعه_String_Property(props, SDL_PROP_پنجره_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, عدم);
    }

    إذا (wind->xdg_dialog_v1) {
        xdg_dialog_v1_destroy(wind->xdg_dialog_v1);
        wind->xdg_dialog_v1 = عدم;
    }

#اگر_تعریف_شده HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (wind->shell_surface.libdecor.قاب) {
            libdecor_قاب_unref(wind->shell_surface.libdecor.قاب);

            SDL_مجموعه_اشاره_گر_Property(props, SDL_PROP_پنجره_WAYLAND_XDG_SURFACE_اشاره_گر, عدم);
            SDL_مجموعه_اشاره_گر_Property(props, SDL_PROP_پنجره_WAYLAND_XDG_TOPLEVEL_اشاره_گر, عدم);
        }
    } وإلا
#پایان_اگر
    {
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
            Wayland_ReleasePopup(_this, پنجره);
        } وإلا إذا (wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            xdg_toplevel_destroy(wind->shell_surface.xdg.toplevel.xdg_toplevel);
            SDL_مجموعه_اشاره_گر_Property(props, SDL_PROP_پنجره_WAYLAND_XDG_TOPLEVEL_اشاره_گر, عدم);
        }

        إذا (wind->shell_surface.xdg.surface) {
            xdg_surface_destroy(wind->shell_surface.xdg.surface);
            SDL_مجموعه_اشاره_گر_Property(props, SDL_PROP_پنجره_WAYLAND_XDG_SURFACE_اشاره_گر, عدم);
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
    بنية wl_callback *cb = wl_display_sync(_this->داخلی->display);
    wl_callback_جمع_کن_listener(cb, &show_hide_sync_listener, (فراغ *)((uintptr_t)پنجره->id));
}

ساكن فراغ handle_xdg_activation_انجامشده(فراغ *داده,
                                       بنية xdg_activation_token_v1 *xdg_activation_token_v1,
                                       ثابت حرف *token)
{
    SDL_پنجره_داده *پنجره = داده;
    إذا (xdg_activation_token_v1 == پنجره->activation_token) {
        xdg_activation_v1_activate(پنجره->wayland_داده->activation_manager,
                                   token,
                                   پنجره->surface);
        xdg_activation_token_v1_destroy(پنجره->activation_token);
        پنجره->activation_token = عدم;
    }
}

ساكن ثابت بنية xdg_activation_token_v1_listener xdg_activation_listener = {
    handle_xdg_activation_انجامشده
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
ساكن فراغ Wayland_activate_پنجره(SDL_Video_داده *داده, SDL_پنجره_داده *هدف_wind, bool مجموعه_serial)
{
    SDL_WaylandSeat *seat = داده->آخرین_implicit_grab_seat;
    SDL_پنجره_داده *focus = عدم;

    إذا (seat) {
        focus = seat->keyboard.focus;
        إذا (!focus) {
            focus = seat->اشاره_گر_2.focus;
        }
    }

    بنية wl_surface *requesting_surface = focus ? focus->surface : عدم;

    إذا (داده->activation_manager) {
        إذا (هدف_wind->activation_token) {
            // We're about to overwrite this with a new request
            xdg_activation_token_v1_destroy(هدف_wind->activation_token);
        }

        هدف_wind->activation_token = xdg_activation_v1_get_activation_token(داده->activation_manager);
        xdg_activation_token_v1_جمع_کن_listener(هدف_wind->activation_token,
                                             &xdg_activation_listener,
                                             هدف_wind);

        /* Note that we are not setting the app_id here.
         *
         * Hypothetically we could set the app_id from data->classname, but
         * that part of the API is for _external_ programs, not ourselves.
         *
         * -flibit
         */
        إذا (requesting_surface) {
            // This specifies the surface from which the activation request is originating, not the activation target surface.
            xdg_activation_token_v1_مجموعه_surface(هدف_wind->activation_token, requesting_surface);
        }
        إذا (مجموعه_serial && seat && seat->wl_seat) {
            xdg_activation_token_v1_مجموعه_serial(هدف_wind->activation_token, seat->آخرین_implicit_grab_serial, seat->wl_seat);
        }
        xdg_activation_token_v1_commit(هدف_wind->activation_token);
    }
}

فراغ Wayland_Raise_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_Video_داده *viddata = _this->داخلی;
    SDL_پنجره_داده *wind = پنجره->داخلی;

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
    Wayland_activate_پنجره(_this->داخلی, پنجره->داخلی, true);
}

bool Wayland_Flash_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_FlashOperation operation)
{
    /* Not setting the serial will specify 'urgency' without switching focus as per
     * https://gitlab.freedesktop.org/wayland/wayland-protocols/-/merge_requests/9#note_854977
     */
    Wayland_activate_پنجره(_this->داخلی, پنجره->داخلی, false);
    أرجع true;
}

SDL_Fullscreen_نتیجه Wayland_مجموعه_پنجره_Fullscreen(SDL_VideoDevice *_this, SDL_پنجره *پنجره,
                                 SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_پنجره_داده *wind = پنجره->داخلی;
    بنية wl_output *output = display->داخلی->output;

    // Custom surfaces have no toplevel to make fullscreen.
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        أرجع SDL_FULLSCREEN_FAILED;
    }

    // Drop fullscreen leave requests when showing the window.
    إذا (wind->showing_پنجره && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        أرجع SDL_FULLSCREEN_SUCCEEDED;
    }

    إذا (wind->show_hide_sync_required) {
        WAYLAND_wl_display_roundtrip(_this->داخلی->display);
    }

    // Flushing old events pending a new one, ignore this request.
    إذا (wind->drop_fullscreen_درخواستها) {
        أرجع SDL_FULLSCREEN_SUCCEEDED;
    }

    wind->drop_fullscreen_درخواستها = true;
    FlushPendingEvents(پنجره);
    wind->drop_fullscreen_درخواستها = false;

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
        إذا (!پنجره->fullscreen_exclusive) {
            إذا (پنجره->undefined_x || پنجره->undefined_y ||
                (wind->رقم_outputs && !پنجره->آخرین_position_pending)) {
                output = عدم;
            }
        }

        // Commit to set any pending size or limit data.
        إذا (fullscreen && wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        مجموعه_Fullscreen(پنجره, output, !!fullscreen);
    } وإلا إذا (wind->is_fullscreen) {
        /*
         * If the window is already fullscreen, this is likely a request to switch between
         * fullscreen and fullscreen desktop, change outputs, or change the video mode.
         *
         * If the window is already positioned on the target output, just update the
         * window geometry.
         */
        إذا (wind->آخرین_display_ID != display->id) {
            wind->fullscreen_was_positioned = true;
            مجموعه_Fullscreen(پنجره, output, true);
        } وإلا {
            Configure_پنجره_Geometry(پنجره);
            Commit_Libdecor_قاب(پنجره);

            أرجع SDL_FULLSCREEN_SUCCEEDED;
        }
    }

    أرجع SDL_FULLSCREEN_PENDING;
}

فراغ Wayland_Restore_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *wind = پنجره->داخلی;

    // Drop restore requests when showing the window.
    إذا (wind->showing_پنجره) {
        أرجع;
    }

    // Not currently fullscreen or maximized, and no state pending; nothing to do.
    إذا (!(پنجره->flags & (SDL_پنجره_FULLSCREEN | SDL_پنجره_MAXIMIZED)) &&
        !wind->pending_state_deadline_شمار) {
        أرجع;
    }

#اگر_تعریف_شده HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (!wind->shell_surface.libdecor.قاب) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }
        libdecor_قاب_unset_maximized(wind->shell_surface.libdecor.قاب);
        جمع_کن_Pending_State_Sync(wind);
    } وإلا
#پایان_اگر
        // Note that xdg-shell does NOT provide a way to unset minimize!
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
            إذا (wind->shell_surface.xdg.toplevel.xdg_toplevel == عدم) {
                أرجع; // Can't do anything yet, wait for ShowWindow
            }
            xdg_toplevel_unset_maximized(wind->shell_surface.xdg.toplevel.xdg_toplevel);
            جمع_کن_Pending_State_Sync(wind);
        }
}

فراغ Wayland_مجموعه_پنجره_Bordered(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool bordered)
{
    SDL_پنجره_داده *wind = پنجره->داخلی;
    ثابت SDL_Video_داده *viddata = (ثابت SDL_Video_داده *)_this->داخلی;

#اگر_تعریف_شده HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (wind->shell_surface.libdecor.قاب) {
            libdecor_قاب_مجموعه_visibility(wind->shell_surface.libdecor.قاب, bordered);
        }
    } وإلا
#پایان_اگر
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        إذا ((viddata->decoration_manager) && (wind->server_decoration)) {
            ثابت تعداد zxdg_toplevel_decoration_v1_نما نما = bordered ? ZXDG_TOPLEVEL_DECORATION_V1_نما_SERVER_SIDE : ZXDG_TOPLEVEL_DECORATION_V1_نما_CLIENT_SIDE;
            zxdg_toplevel_decoration_v1_مجموعه_نما(wind->server_decoration, نما);
        }
    }
}

فراغ Wayland_مجموعه_پنجره_Resizable(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool resizable)
{
    SDL_پنجره_داده *wind = پنجره->داخلی;

    /* When changing the resize capability on libdecor windows, the limits must always
     * be reapplied, as when libdecor changes states, it overwrites the values internally.
     */
    مجموعه_Min_Max_Dimensions(پنجره);
    Commit_Libdecor_قاب(پنجره);

    إذا (wind->shell_surface_وضعیت == WAYLAND_SHELL_SURFACE_وضعیت_SHOWN) {
        wind->pending_state_commit = true;
    }
}

فراغ Wayland_Maximize_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *wind = پنجره->داخلی;

    إذا (wind->show_hide_sync_required) {
        WAYLAND_wl_display_roundtrip(_this->داخلی->display);
    }

    // Not fullscreen, already maximized, and no state pending; nothing to do.
    إذا (!(پنجره->flags & SDL_پنجره_FULLSCREEN) && (پنجره->flags & SDL_پنجره_MAXIMIZED) &&
        !wind->pending_state_deadline_شمار) {
        أرجع;
    }

#اگر_تعریف_شده HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (!wind->shell_surface.libdecor.قاب) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }

        // Commit to set any pending size or limit data.
        إذا (wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        libdecor_قاب_مجموعه_maximized(wind->shell_surface.libdecor.قاب);
        جمع_کن_Pending_State_Sync(wind);
    } وإلا
#پایان_اگر
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        إذا (wind->shell_surface.xdg.toplevel.xdg_toplevel == عدم) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }

        // Commit to set any pending size or limit data.
        إذا (wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        xdg_toplevel_مجموعه_maximized(wind->shell_surface.xdg.toplevel.xdg_toplevel);
        جمع_کن_Pending_State_Sync(wind);
    }
}

فراغ Wayland_Minimize_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *wind = پنجره->داخلی;

    إذا (!(wind->wm_caps & WAYLAND_WM_CAPS_MINIMIZE)) {
        أرجع;
    }

#اگر_تعریف_شده HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (!wind->shell_surface.libdecor.قاب) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }
        libdecor_قاب_مجموعه_minimized(wind->shell_surface.libdecor.قاب);
        SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_MINIMIZED, 0, 0);
    } وإلا
#پایان_اگر
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        إذا (wind->shell_surface.xdg.toplevel.xdg_toplevel == عدم) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }
        xdg_toplevel_مجموعه_minimized(wind->shell_surface.xdg.toplevel.xdg_toplevel);
        SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_MINIMIZED, 0, 0);
    }
}

bool Wayland_مجموعه_پنجره_Mouse_Rect(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_Video_داده *داده = _this->داخلی;

    /* This may look suspiciously like SetWindowGrab, despite SetMouseRect not
     * implicitly doing a grab. And you're right! Wayland doesn't let us mess
     * around with mouse focus whatsoever, so it just happens to be that the
     * work that we can do in these two functions ends up being the same.
     *
     * Just know that this call lets you confine with a rect, SetWindowGrab
     * lets you confine without a rect.
     */
    إذا (!داده->اشاره_گر_constraints) {
        أرجع SDL_مجموعه_Error("Failed to grab mouse: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }
    Wayland_Display_Update_اشاره_گر_Grabs(داده, پنجره->داخلی);
    أرجع true;
}

bool Wayland_مجموعه_پنجره_Mouse_Grab(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool grabbed)
{
    SDL_Video_داده *داده = _this->داخلی;
    إذا (!داده->اشاره_گر_constraints) {
        أرجع SDL_مجموعه_Error("Failed to grab mouse: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }
    Wayland_Display_Update_اشاره_گر_Grabs(داده, پنجره->داخلی);
    أرجع true;
}

bool Wayland_مجموعه_پنجره_Keyboard_Grab(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool grabbed)
{
    SDL_Video_داده *داده = _this->داخلی;
    إذا (!داده->کلید_inhibitor_manager) {
        أرجع SDL_مجموعه_Error("Failed to grab keyboard: compositor lacks support for the required zwp_keyboard_shortcuts_inhibit_manager_v1 protocol");
    }
    Wayland_DisplayUpdateKeyboardGrabs(داده, پنجره->داخلی);
    أرجع true;
}

bool Wayland_Reconfigure_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_پنجره_Flags flags)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;

    // Don't try to reconfigure mapped windows, unless they are custom or external.
    إذا (داده->shell_surface_وضعیت == WAYLAND_SHELL_SURFACE_وضعیت_SHOWN &&
        داده->shell_surface_type != WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        // Window is already mapped; abort.
        أرجع false;
    }

    /* The caller guarantees that only one of the GL or Vulkan flags will be set.
     * Note that Vulkan doesn't require any specific configuration, so only EGL
     * objects are added and removed as required.
     */
    إذا (flags & SDL_پنجره_OPENGL) {
        إذا (!داده->egl_پنجره) {
            داده->egl_پنجره = WAYLAND_wl_egl_پنجره_create(داده->surface, داده->current.pixel_عرض, داده->current.pixel_ارتفاع);
        }

#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
        داده->egl_surface = SDL_EGL_CreateSurface(_this, پنجره, (Native_پنجره_Type)داده->egl_پنجره);

        إذا (داده->egl_surface == EGL_NO_SURFACE) {
            أرجع false; // SDL_EGL_CreateSurface should have set the error.
        }
#پایان_اگر

        إذا (!داده->gles_جابجا_قاب_event_صف) {
            داده->gles_جابجا_قاب_event_صف = WAYLAND_wl_display_create_صف(داده->wayland_داده->display);
            داده->gles_جابجا_قاب_surface_wrapper = WAYLAND_wl_proxy_create_wrapper(داده->surface);
            WAYLAND_wl_proxy_مجموعه_صف((بنية wl_proxy *)داده->gles_جابجا_قاب_surface_wrapper, داده->gles_جابجا_قاب_event_صف);
            داده->gles_جابجا_قاب_callback = wl_surface_قاب(داده->gles_جابجا_قاب_surface_wrapper);
            wl_callback_جمع_کن_listener(داده->gles_جابجا_قاب_callback, &gles_جابجا_قاب_listener, داده);
        }
    } وإلا {
#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
        إذا (داده->egl_surface) {
            SDL_EGL_DestroySurface(_this, داده->egl_surface);
            داده->egl_surface = EGL_NO_SURFACE;
        }
#پایان_اگر

        إذا (داده->egl_پنجره) {
            WAYLAND_wl_egl_پنجره_destroy(داده->egl_پنجره);
            داده->egl_پنجره = عدم;
        }

        إذا (داده->gles_جابجا_قاب_callback) {
            wl_callback_destroy(داده->gles_جابجا_قاب_callback);
            داده->gles_جابجا_قاب_callback = عدم;
        }

        إذا (داده->gles_جابجا_قاب_surface_wrapper) {
            WAYLAND_wl_proxy_wrapper_destroy(داده->gles_جابجا_قاب_surface_wrapper);
            داده->gles_جابجا_قاب_surface_wrapper = عدم;
        }

        إذا (داده->gles_جابجا_قاب_event_صف) {
            WAYLAND_wl_event_صف_destroy(داده->gles_جابجا_قاب_event_صف);
            داده->gles_جابجا_قاب_event_صف = عدم;
        }
    }

    أرجع true;
}

bool Wayland_Create_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID create_props)
{
    SDL_پنجره_داده *داده;
    SDL_Video_داده *c = _this->داخلی;
    بنية wl_surface *external_surface = (بنية wl_surface *)SDL_Get_اشاره_گر_Property(create_props, SDL_PROP_پنجره_CREATE_WAYLAND_WL_SURFACE_اشاره_گر,
                                                                               (بنية wl_surface *)SDL_Get_اشاره_گر_Property(create_props, "sdl2-compat.external_window", عدم));
    ثابت bool custom_surface_role = (external_surface != عدم) || SDL_GetBooleanProperty(create_props, SDL_PROP_پنجره_CREATE_WAYLAND_SURFACE_ROLE_CUSTOM_BOOLEAN, false);
    ثابت bool create_egl_پنجره = !!(پنجره->flags & SDL_پنجره_OPENGL) ||
                                       SDL_GetBooleanProperty(create_props, SDL_PROP_پنجره_CREATE_WAYLAND_CREATE_EGL_پنجره_BOOLEAN, false);

    داده = SDL_calloc(1, حجم(*داده));
    إذا (!داده) {
        أرجع false;
    }

    پنجره->داخلی = داده;
    داده->enable_insets = SDL_GetBooleanProperty(create_props, SDL_PROP_پنجره_CREATE_WAYLAND_ENABLE_INSETS_BOOLEAN, false);

    إذا (پنجره->x == SDL_WINDOWPOS_UNDEFINED) {
        پنجره->x = 0;
    }
    إذا (پنجره->y == SDL_WINDOWPOS_UNDEFINED) {
        پنجره->y = 0;
    }

    داده->wayland_داده = c;
    داده->sdlwindow = پنجره;

    // Default to all capabilities
    داده->wm_caps = WAYLAND_WM_CAPS_ALL;

    داده->scale_ضریب_2 = 1.0;

    إذا (SDL_پنجره_IS_POPUP(پنجره)) {
        داده->scale_مقصد_display = پنجره->والد->داخلی->scale_مقصد_display;
        داده->scale_ضریب_2 = پنجره->والد->داخلی->scale_ضریب_2;
        EnsurePopupPositionIsValid(پنجره, &پنجره->x, &پنجره->y);
    } وإلا {
        لكل (صحيح i = 0; i < _this->رقم_displays; i++) {
            داده->scale_ضریب_2 = SDL_max(داده->scale_ضریب_2, _this->displays[i]->داخلی->scale_ضریب_2);
        }
    }

    داده->outputs = عدم;
    داده->رقم_outputs = 0;
    داده->scale_مقصد_display = c->scale_مقصد_display_enabled;

    // Cache the app_id at creation time, as it may change before the window is mapped.
    داده->app_id = SDL_strdup(SDL_GetAppID());

    إذا (!داده->scale_مقصد_display) {
        داده->requested.logical_عرض = پنجره->floating.w;
        داده->requested.logical_ارتفاع = پنجره->floating.h;
    } وإلا {
        داده->requested.logical_عرض = Pixel_مقصد_نقطه(پنجره, پنجره->floating.w);
        داده->requested.logical_ارتفاع = Pixel_مقصد_نقطه(پنجره, پنجره->floating.h);
        داده->requested.pixel_عرض = پنجره->floating.w;
        داده->requested.pixel_ارتفاع = پنجره->floating.h;
    }

    إذا (!external_surface) {
        داده->surface = wl_compositor_create_surface(c->compositor);
        wl_surface_جمع_کن_listener(داده->surface, &surface_listener, داده);
        wl_surface_مجموعه_user_داده(داده->surface, داده);
        SDL_WAYLAND_ثبات_surface(داده->surface);
    } وإلا {
        پنجره->flags |= SDL_پنجره_EXTERNAL;
        داده->surface = external_surface;

        /* External surfaces are registered by being put in a list, as changing tags or userdata
         * can cause problems with external toolkits.
         */
        Wayland_جمع_کن_پنجره_داده_مقصد_External_List(داده);
    }

    /* Always attach a viewport and fractional scale manager if available and the surface is not custom/external,
     * or the custom/external surface was explicitly flagged as high pixel density aware, which signals that the
     * application wants SDL to handle scaling.
     */
    إذا (!custom_surface_role || (پنجره->flags & SDL_پنجره_بالا_PIXEL_DENSITY)) {
        إذا (c->viewporter) {
            داده->viewport = wp_viewporter_get_viewport(c->viewporter, داده->surface);

            // The viewport always uses the entire buffer.
            wp_viewport_مجموعه_منبع(داده->viewport,
                                   wl_fixed_from_int(-1), wl_fixed_from_int(-1),
                                   wl_fixed_from_int(-1), wl_fixed_from_int(-1));
        }
        إذا (c->fractional_scale_manager) {
            داده->fractional_scale = wp_fractional_scale_manager_v1_get_fractional_scale(c->fractional_scale_manager, داده->surface);
            wp_fractional_scale_v1_جمع_کن_listener(داده->fractional_scale, &fractional_scale_listener, داده);
        }
    }

    إذا (!custom_surface_role) {
        إذا (c->wp_color_manager_v1) {
            داده->wp_color_management_surface_feedback = wp_color_manager_v1_get_surface_feedback(c->wp_color_manager_v1, داده->surface);
            wp_color_management_surface_feedback_v1_جمع_کن_listener(داده->wp_color_management_surface_feedback, &color_management_surface_feedback_listener, داده);
            Wayland_Get_Color_Info_For_پنجره(داده, true);
        } وإلا إذا (c->frog_color_management_factory_v1) {
            داده->frog_color_managed_surface = frog_color_management_factory_v1_get_color_managed_surface(c->frog_color_management_factory_v1, داده->surface);
            frog_color_managed_surface_جمع_کن_listener(داده->frog_color_managed_surface, &frog_surface_listener, داده);
        }

        إذا (c->wp_alpha_modifier_v1) {
            داده->wp_alpha_modifier_surface_v1 = wp_alpha_modifier_v1_get_surface(c->wp_alpha_modifier_v1, داده->surface);
            wp_alpha_modifier_surface_v1_مجموعه_multiplier(داده->wp_alpha_modifier_surface_v1, SDL_MAX_UINT32);
        }
    }

    // Must be called before EGL configuration to set the drawable backbuffer size.
    Configure_پنجره_Geometry(پنجره);

    /* Fire a callback when the compositor wants a new frame rendered.
     * Right now this only matters for OpenGL; we use this callback to add a
     * wait timeout that avoids getting deadlocked by the compositor when the
     * window isn't visible.
     */
    إذا (پنجره->flags & SDL_پنجره_OPENGL) {
        داده->gles_جابجا_قاب_event_صف = WAYLAND_wl_display_create_صف(داده->wayland_داده->display);
        داده->gles_جابجا_قاب_surface_wrapper = WAYLAND_wl_proxy_create_wrapper(داده->surface);
        WAYLAND_wl_proxy_مجموعه_صف((بنية wl_proxy *)داده->gles_جابجا_قاب_surface_wrapper, داده->gles_جابجا_قاب_event_صف);
        داده->gles_جابجا_قاب_callback = wl_surface_قاب(داده->gles_جابجا_قاب_surface_wrapper);
        wl_callback_جمع_کن_listener(داده->gles_جابجا_قاب_callback, &gles_جابجا_قاب_listener, داده);
    }

    إذا (پنجره->flags & SDL_پنجره_TRANSPARENT) {
        إذا (_this->gl_config.alpha_اندازه == 0) {
            _this->gl_config.alpha_اندازه = 8;
        }
    }

    إذا (create_egl_پنجره) {
        داده->egl_پنجره = WAYLAND_wl_egl_پنجره_create(داده->surface, داده->current.pixel_عرض, داده->current.pixel_ارتفاع);
    }

#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
    إذا (پنجره->flags & SDL_پنجره_OPENGL) {
        // Create the GLES window surface
        داده->egl_surface = SDL_EGL_CreateSurface(_this, پنجره, (Native_پنجره_Type)داده->egl_پنجره);

        إذا (داده->egl_surface == EGL_NO_SURFACE) {
            أرجع false; // SDL_EGL_CreateSurface should have set error
        }
    }
#پایان_اگر

    // We may need to create an idle inhibitor for this new window
    Wayland_SuspendScreenSaver(_this);

    إذا (!custom_surface_role) {
#اگر_تعریف_شده HAVE_LIBDECOR_H
        إذا (c->shell.libdecor && !SDL_پنجره_IS_POPUP(پنجره)) {
            داده->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR;
        } وإلا
#پایان_اگر
            إذا (c->shell.xdg) {
            إذا (SDL_پنجره_IS_POPUP(پنجره)) {
                داده->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP;
            } وإلا {
                داده->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL;
            }
        } // All other cases will be WAYLAND_SURFACE_UNKNOWN
    } وإلا {
        // Roleless and external surfaces are always considered to be in the shown state by the backend.
        داده->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_CUSTOM;
        داده->shell_surface_وضعیت = WAYLAND_SHELL_SURFACE_وضعیت_SHOWN;

        // External windows are presumed to be shown.
        إذا (پنجره->flags & SDL_پنجره_EXTERNAL) {
            پنجره->flags &= ~SDL_پنجره_HIDDEN;
        }
    }

    إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_DOUBLE_میانگیر, false)) {
        داده->double_میانگیر = true;
    }

    SDL_PropertiesID props = SDL_Get_پنجره_Properties(پنجره);
    SDL_مجموعه_اشاره_گر_Property(props, SDL_PROP_پنجره_WAYLAND_DISPLAY_اشاره_گر, داده->wayland_داده->display);
    SDL_مجموعه_اشاره_گر_Property(props, SDL_PROP_پنجره_WAYLAND_SURFACE_اشاره_گر, داده->surface);
    SDL_مجموعه_اشاره_گر_Property(props, SDL_PROP_پنجره_WAYLAND_VIEWPORT_اشاره_گر, داده->viewport);
    SDL_مجموعه_اشاره_گر_Property(props, SDL_PROP_پنجره_WAYLAND_EGL_پنجره_اشاره_گر, داده->egl_پنجره);
    إذا (داده->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL || داده->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ثابت حرف *پنجره_id = SDL_GetStringProperty(create_props, SDL_PROP_پنجره_CREATE_WAYLAND_پنجره_ID_STRING, عدم);
        إذا (پنجره_id && *پنجره_id != '\0') {
            SDL_مجموعه_String_Property(props, SDL_PROP_پنجره_WAYLAND_پنجره_ID_STRING, پنجره_id);
        }
    }

    داده->اصابت_test_نتیجه = SDL_HITTEST_نرمال;

    أرجع true;
}

فراغ Wayland_مجموعه_پنجره_Minimum_اندازه(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    پنجره->داخلی->limits_تغییریافته = true;
}

فراغ Wayland_مجموعه_پنجره_بیشینه_اندازه(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    پنجره->داخلی->limits_تغییریافته = true;
}

فراغ Wayland_مجموعه_پنجره_Aspect_نسبت(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    پنجره->داخلی->limits_تغییریافته = true;
}

bool Wayland_مجموعه_پنجره_Position(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *wind = پنجره->داخلی;

    // Only popup windows can be positioned relative to the parent.
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        إذا (wind->shell_surface.xdg.popup.xdg_popup &&
            xdg_popup_get_نسخه(wind->shell_surface.xdg.popup.xdg_popup) < XDG_POPUP_REPOSITION_SINCE_نسخه) {
            أرجع SDL_Unsupported();
        }

        RepositionPopup(پنجره, false);
        أرجع true;
    } وإلا إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR || wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        /* Catch up on any pending state before attempting to change the fullscreen window
         * display via a set fullscreen call to make sure the window doesn't have a pending
         * leave fullscreen event that it might override.
         */
        FlushPendingEvents(پنجره);

        إذا (wind->is_fullscreen) {
            SDL_VideoDisplay *display = SDL_Get_Video_Display_For_Fullscreen_پنجره(پنجره);
            إذا (display && wind->آخرین_display_ID != display->id) {
                بنية wl_output *output = display->داخلی->output;
                مجموعه_Fullscreen(پنجره, output, true);

                أرجع true;
            }
        }
    }
    أرجع SDL_مجموعه_Error("wayland cannot position non-popup windows");
}

فراغ Wayland_مجموعه_پنجره_اندازه(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *wind = پنجره->داخلی;

    /* Flush any pending state operations, as fullscreen windows do not get
     * explicitly resized, not strictly obeying the size of a maximized window
     * is a protocol violation, and pending restore events might result in a
     * configure event overwriting the requested size.
     *
     * Calling this on a custom surface is informative, so the size must
     * always be passed through.
     */
    FlushPendingEvents(پنجره);

    ثابت bool maximized = (پنجره->flags & SDL_پنجره_MAXIMIZED) != 0;
    ثابت bool resizable_state = !(پنجره->flags & (SDL_پنجره_MAXIMIZED | SDL_پنجره_FULLSCREEN));

    /* Maximized and fullscreen windows don't get resized, and the new size is ignored
     * if this is just to recalculate the min/max or aspect limits on a tiled window.
     *
     * Some compositors will mark tiled windows as maximized. In these cases, the content
     * size is recalculated, but window size itself is left alone, as the spec states that
     * the configure size of a maximized window must be obeyed.
     */
    إذا (resizable_state || (پنجره->tiled && !wind->limits_تغییریافته) ||
        wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {

        // Don't change the window size if maximized and tiled.
        إذا (!maximized) {
            إذا (!wind->scale_مقصد_display) {
                wind->requested.logical_عرض = پنجره->pending.w;
                wind->requested.logical_ارتفاع = پنجره->pending.h;
            } وإلا {
                wind->requested.logical_عرض = Pixel_مقصد_نقطه(پنجره, پنجره->pending.w);
                wind->requested.logical_ارتفاع = Pixel_مقصد_نقطه(پنجره, پنجره->pending.h);
                wind->requested.pixel_عرض = پنجره->pending.w;
                wind->requested.pixel_ارتفاع = پنجره->pending.h;
            }
        }

        /* If a non-resizable window somehow wound up in the tiled state, store the new
         * size in the floating parameters so the size will be preserved for future
         * configure events.
         *
         * This shouldn't happen, but apparently it can on at least one compositor...
         */
        إذا (پنجره->tiled && !(پنجره->flags & SDL_پنجره_RESIZABLE)) {
            پنجره->floating.w = پنجره->pending.w;
            پنجره->floating.h = پنجره->pending.h;
        }
    } وإلا {
        // Can't resize the window.
        پنجره->آخرین_اندازه_pending = false;
    }

    wind->limits_تغییریافته = false;
    إذا (wind->shell_surface_وضعیت == WAYLAND_SHELL_SURFACE_وضعیت_SHOWN) {
        wind->pending_state_commit = true;
    }

    // Always recalculate the geometry, as this may be in response to a min/max limit change.
    Configure_پنجره_Geometry(پنجره);
    Commit_Libdecor_قاب(پنجره);
}

فراغ Wayland_Get_پنجره_اندازه_درون_Pixels(SDL_VideoDevice *_this, SDL_پنجره *پنجره, صحيح *w, صحيح *h)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;

    *w = داده->current.pixel_عرض;
    *h = داده->current.pixel_ارتفاع;
}

عائم Wayland_Get_پنجره_Content_Scale(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *wind = پنجره->داخلی;

    إذا (پنجره->flags & SDL_پنجره_بالا_PIXEL_DENSITY || wind->scale_مقصد_display || wind->fullscreen_exclusive) {
        أرجع (عائم)wind->scale_ضریب_2;
    }

    أرجع 1.0f;
}

SDL_DisplayID Wayland_Get_Display_For_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *wind = پنجره->داخلی;

    إذا (wind) {
        أرجع wind->آخرین_display_ID;
    }

    أرجع 0;
}

bool Wayland_مجموعه_پنجره_Opacity(SDL_VideoDevice *_this, SDL_پنجره *پنجره, عائم opacity)
{
    SDL_پنجره_داده *wind = پنجره->داخلی;

    إذا (wind->wp_alpha_modifier_surface_v1) {
        ثابت bool is_opaque = !(پنجره->flags & SDL_پنجره_TRANSPARENT) && opacity == 1.0f;

        إذا (wind->ماسک.mapped && wind->ماسک.opaque != is_opaque) {
            بنية wl_میانگیر *old_میانگیر = wind->ماسک.میانگیر_2;
            wind->ماسک.opaque = is_opaque;
            wind->ماسک.میانگیر_2 = Wayland_Create_Single_Pixel_میانگیر(0, 0, 0, is_opaque ? SDL_MAX_UINT32 : 0);

            wl_surface_attach(wind->ماسک.surface, wind->ماسک.میانگیر_2, 0, 0);
            إذا (wl_surface_get_نسخه(wind->ماسک.surface) >= WL_SURFACE_DAMAGE_میانگیر_SINCE_نسخه) {
                wl_surface_damage_میانگیر(wind->ماسک.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
            } وإلا {
                wl_surface_damage(wind->ماسک.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
            }

            إذا (is_opaque) {
                مجموعه_Surface_Opaque_Region(wind->ماسک.surface, wind->current.logical_عرض, wind->current.logical_ارتفاع);
            } وإلا {
                مجموعه_Surface_Opaque_Region(wind->ماسک.surface, 0, 0);
            }

            wl_surface_commit(wind->ماسک.surface);

            إذا (old_میانگیر) {
                wl_میانگیر_destroy(old_میانگیر);
            }
        }

        إذا (is_opaque) {
            مجموعه_Surface_Opaque_Region(wind->surface, wind->current.viewport_عرض, wind->current.viewport_ارتفاع);
        } وإلا {
            مجموعه_Surface_Opaque_Region(wind->surface, 0, 0);
        }

        wp_alpha_modifier_surface_v1_مجموعه_multiplier(wind->wp_alpha_modifier_surface_v1, (Uint32)((مزدوج)SDL_MAX_UINT32 * (مزدوج)opacity));

        أرجع true;
    }

    أرجع SDL_مجموعه_Error("wayland: set window opacity failed; compositor lacks support for the required wp_alpha_modifier_v1 protocol");
}

فراغ Wayland_مجموعه_پنجره_Title(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *wind = پنجره->داخلی;
    ثابت حرف *title = پنجره->title ? پنجره->title : "";

#اگر_تعریف_شده HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.قاب) {
        libdecor_قاب_مجموعه_title(wind->shell_surface.libdecor.قاب, title);
    } وإلا
#پایان_اگر
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
        xdg_toplevel_مجموعه_title(wind->shell_surface.xdg.toplevel.xdg_toplevel, title);
    }
}

ساكن صحيح icon_مرتب_سازی_callback(ثابت فراغ *a, ثابت فراغ *b)
{
    ثابت SDL_Surface *s1 = *(ثابت SDL_Surface **)a;
    ثابت SDL_Surface *s2 = *(ثابت SDL_Surface **)b;

    أرجع (s1->w * s1->h) <= (s2->w * s2->h) ? -1 : 1;
}

bool Wayland_مجموعه_پنجره_Icon(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_Surface *icon)
{
    SDL_پنجره_داده *wind = پنجره->داخلی;
    Wayland_SHMPool *shm_pool = عدم;
    بنية xdg_toplevel *toplevel = عدم;

    إذا (!_this->داخلی->xdg_toplevel_icon_manager_v1) {
        أرجع SDL_مجموعه_Error("wayland: cannot set icon; required xdg_toplevel_icon_v1 protocol not supported");
    }

    صحيح image_شمار_2 = 0;
    SDL_Surface **images = SDL_GetSurfaceImages(icon, &image_شمار_2);
    إذا (!images || !image_شمار_2) {
        أرجع false;
    }

    // Release the old icon resources.
    إذا (wind->xdg_toplevel_icon_v1) {
        xdg_toplevel_icon_v1_destroy(wind->xdg_toplevel_icon_v1);
        wind->xdg_toplevel_icon_v1 = عدم;
    }

    لكل (صحيح i = 0; i < wind->icon_میانگیر_شمار; ++i) {
        wl_میانگیر_destroy(wind->icon_buffers[i]);
    }
    wind->icon_میانگیر_شمار = 0;

    wind->xdg_toplevel_icon_v1 = xdg_toplevel_icon_manager_v1_create_icon(_this->داخلی->xdg_toplevel_icon_manager_v1);
    wind->icon_buffers = SDL_realloc(wind->icon_buffers, image_شمار_2 * حجم(بنية wl_میانگیر *));
    إذا (!wind->icon_buffers) {
        اذهب failure_cleanup;
    }

    // Calculate the size of the buffer pool.
    size_t pool_اندازه = 0;
    لكل (صحيح i = 0; i < image_شمار_2; ++i) {
        // Images must be square. Non-square images will be centered.
        ثابت صحيح اندازه = SDL_max(images[i]->w, images[i]->h);
        pool_اندازه += اندازه * اندازه * 4;
    }

    // Sort the images in ascending order by size.
    SDL_qsort(images, image_شمار_2, حجم(SDL_Surface *), icon_مرتب_سازی_callback);

    shm_pool = Wayland_AllocSHMPool(pool_اندازه);
    إذا (!shm_pool) {
        SDL_مجموعه_Error("wayland: failed to allocate an SHM pool for the icon");
        اذهب failure_cleanup;
    }

    ثابت مزدوج پایه_اندازه = (مزدوج)SDL_max(icon->w, icon->h);
    لكل (صحيح i = 0; i < image_شمار_2; ++i) {
        SDL_Surface *surface = images[i];

        // Choose the largest image for each integer scale, ignoring any below the base size.
        ثابت صحيح level_اندازه = SDL_max(surface->w, surface->h);
        ثابت صحيح scale = (صحيح)SDL_floor((مزدوج)level_اندازه / پایه_اندازه);
        إذا (!scale) {
            استمر;
        }

        إذا (surface->format != SDL_PIXELFORMAT_ARGB8888) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
            إذا (!surface) {
                SDL_مجموعه_Error("wayland: failed to convert the icon image to ARGB8888 format");
                اذهب failure_cleanup;
            }
        }

        فراغ *میانگیر_mem;
        بنية wl_میانگیر *میانگیر_2 = Wayland_Alloc_میانگیر_From_Pool(shm_pool, level_اندازه, level_اندازه, &میانگیر_mem);
        إذا (!میانگیر_2) {
            // Clean up the temporary conversion surface.
            إذا (surface != images[i]) {
                SDL_DestroySurface(surface);
            }
            SDL_مجموعه_Error("wayland: failed to allocate a wl_buffer for the icon");
            اذهب failure_cleanup;
        }

        wind->icon_buffers[wind->icon_میانگیر_شمار++] = میانگیر_2;

        // Center non-square images.
        إذا (surface->w < level_اندازه) {
            SDL_memset(میانگیر_mem, 0, level_اندازه * level_اندازه * 4);
            میانگیر_mem = (Uint8 *)میانگیر_mem + (((level_اندازه - surface->w) / 2) * 4);
        } وإلا إذا (surface->h < level_اندازه) {
            SDL_memset(میانگیر_mem, 0, level_اندازه * level_اندازه * 4);
            میانگیر_mem = (Uint8 *)میانگیر_mem + (((level_اندازه - surface->h) / 2) * (level_اندازه * 4));
        }

        SDL_PremultiplyAlpha(surface->w, surface->h, surface->format, surface->pixels, surface->pitch,
                             SDL_PIXELFORMAT_ARGB8888, میانگیر_mem, level_اندازه * 4, true);

        xdg_toplevel_icon_v1_جمع_کن_میانگیر(wind->xdg_toplevel_icon_v1, میانگیر_2, scale);

        // Clean up the temporary scaled or conversion surface.
        إذا (surface != images[i]) {
            SDL_DestroySurface(surface);
        }
    }

#اگر_تعریف_شده HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.قاب) {
        toplevel = libdecor_قاب_get_xdg_toplevel(wind->shell_surface.libdecor.قاب);
    } وإلا
#پایان_اگر
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
        toplevel = wind->shell_surface.xdg.toplevel.xdg_toplevel;
    }

    إذا (toplevel) {
        xdg_toplevel_icon_manager_v1_مجموعه_icon(_this->داخلی->xdg_toplevel_icon_manager_v1, toplevel, wind->xdg_toplevel_icon_v1);
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

    لكل (صحيح i = 0; i < wind->icon_میانگیر_شمار; ++i) {
        wl_میانگیر_destroy(wind->icon_buffers[i]);
    }
    SDL_free(wind->icon_buffers);
    wind->icon_buffers = عدم;
    wind->icon_میانگیر_شمار = 0;

    أرجع false;
}

فراغ *Wayland_Get_پنجره_ICCProfile(SDL_VideoDevice *_this, SDL_پنجره *پنجره, size_t *اندازه)
{
    SDL_پنجره_داده *wind = پنجره->داخلی;
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

bool Wayland_Sync_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *wind = پنجره->داخلی;

    افعل {
        WAYLAND_wl_display_roundtrip(_this->داخلی->display);
    } طالما (wind->pending_state_deadline_شمار);

    أرجع true;
}

فراغ Wayland_AcceptDragAndDrop(SDL_پنجره *پنجره, bool accept)
{
    پنجره->داخلی->میپذیرد_drag_and_drop = accept;
}

bool Wayland_مجموعه_پنجره_Focusable(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool focusable)
{
    إذا (پنجره->flags & SDL_پنجره_POPUP_MENU) {
        إذا (!(پنجره->flags & SDL_پنجره_HIDDEN)) {
            إذا (!focusable && (پنجره->flags & SDL_پنجره_درون_داد_FOCUS)) {
                SDL_پنجره *new_focus;
                ثابت bool مجموعه_focus = SDL_ShouldRelinquishPopupFocus(پنجره, &new_focus);
                Wayland_مجموعه_Keyboard_Focus(new_focus, مجموعه_focus);
            } وإلا إذا (focusable) {
                إذا (SDL_ShouldFocusPopup(پنجره)) {
                    Wayland_مجموعه_Keyboard_Focus(پنجره, true);
                }
            }
        }

        أرجع true;
    }

    أرجع SDL_مجموعه_Error("wayland: focus can only be toggled on popup menu windows");
}

فراغ Wayland_Show_پنجره_System_Menu(SDL_پنجره *پنجره, صحيح x, صحيح y)
{
    SDL_پنجره_داده *wind = پنجره->داخلی;
    SDL_WaylandSeat *seat = wind->wayland_داده->آخرین_implicit_grab_seat;

    إذا (!seat) {
        أرجع;
    }

    إذا (wind->scale_مقصد_display) {
        x = Pixel_مقصد_نقطه(پنجره, x);
        y = Pixel_مقصد_نقطه(پنجره, y);
    }

#اگر_تعریف_شده HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (wind->shell_surface.libdecor.قاب) {
            libdecor_قاب_show_پنجره_menu(wind->shell_surface.libdecor.قاب, seat->wl_seat, seat->آخرین_implicit_grab_serial, x, y);
        }
    } وإلا
#پایان_اگر
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        إذا (wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            xdg_toplevel_show_پنجره_menu(wind->shell_surface.xdg.toplevel.xdg_toplevel, seat->wl_seat, seat->آخرین_implicit_grab_serial, x, y);
        }
    }
}

bool Wayland_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    SDL_Video_داده *داده = _this->داخلی;

#اگر_تعریف_شده SDL_USE_LIBDBUS
    إذا (SDL_DBus_ScreensaverInhibit(_this->suspend_screensaver)) {
        أرجع true;
    }
#پایان_اگر

    /* The idle_inhibit_unstable_v1 protocol suspends the screensaver
       on a per wl_surface basis, but SDL assumes that suspending
       the screensaver can be done independently of any window.

       To reconcile these differences, we propagate the idle inhibit
       state to each window. If there is no window active, we will
       be able to inhibit idle once the first window is created.
    */
    إذا (داده->idle_inhibit_manager) {
        SDL_پنجره *پنجره = _this->windows;
        طالما (پنجره) {
            SDL_پنجره_داده *win_داده = پنجره->داخلی;

            إذا (_this->suspend_screensaver && !win_داده->idle_inhibitor) {
                win_داده->idle_inhibitor =
                    zwp_idle_inhibit_manager_v1_create_inhibitor(داده->idle_inhibit_manager,
                                                                 win_داده->surface);
            } وإلا إذا (!_this->suspend_screensaver && win_داده->idle_inhibitor) {
                zwp_idle_inhibitor_v1_destroy(win_داده->idle_inhibitor);
                win_داده->idle_inhibitor = عدم;
            }

            پنجره = پنجره->بعدی;
        }
    }

    أرجع true;
}

فراغ Wayland_Destroy_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_Video_داده *داده = _this->داخلی;
    SDL_پنجره_داده *wind = پنجره->داخلی;

    إذا (داده && wind) {
        /* Roundtrip before destroying the window to make sure that it has received input leave events, so that
         * no internal structures are left pointing to the destroyed window.
         */
        إذا (wind->show_hide_sync_required) {
            /* Make sure hit test isn't executed during roundtrip */
            پنجره->اصابت_test = عدم;
            WAYLAND_wl_display_roundtrip(داده->display);
        }

        /* The compositor should have relinquished keyboard, pointer, touch, and tablet tool focus when the toplevel
         * window was destroyed upon being hidden, but there is no guarantee of this, so ensure that all references
         * to the window held by seats are released before destroying the underlying surface and struct.
         */
        Wayland_Display_Remove_پنجره_References_From_Seats(داده, wind);

        إذا (wind->ماسک.viewport) {
            wp_viewport_destroy(wind->ماسک.viewport);
        }
        إذا (wind->ماسک.میانگیر_2) {
            wl_میانگیر_destroy(wind->ماسک.میانگیر_2);
        }
        إذا (wind->ماسک.subsurface) {
            wl_subsurface_destroy(wind->ماسک.subsurface);
        }
        إذا (wind->ماسک.surface) {
            wl_surface_destroy(wind->ماسک.surface);
        }
#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
        إذا (wind->egl_surface) {
            SDL_EGL_DestroySurface(_this, wind->egl_surface);
        }
#پایان_اگر
        إذا (wind->egl_پنجره) {
            WAYLAND_wl_egl_پنجره_destroy(wind->egl_پنجره);
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

        إذا (wind->gles_جابجا_قاب_callback) {
            wl_callback_destroy(wind->gles_جابجا_قاب_callback);
            WAYLAND_wl_proxy_wrapper_destroy(wind->gles_جابجا_قاب_surface_wrapper);
            WAYLAND_wl_event_صف_destroy(wind->gles_جابجا_قاب_event_صف);
        }

        إذا (!(پنجره->flags & SDL_پنجره_EXTERNAL)) {
            wl_surface_destroy(wind->surface);
        } وإلا {
            Wayland_Remove_پنجره_داده_From_External_List(wind);
        }

        إذا (wind->xdg_toplevel_icon_v1) {
            xdg_toplevel_icon_v1_destroy(wind->xdg_toplevel_icon_v1);
        }

        لكل (صحيح i = 0; i < wind->icon_میانگیر_شمار; ++i) {
            wl_میانگیر_destroy(wind->icon_buffers[i]);
        }
        SDL_free(wind->icon_buffers);
        wind->icon_میانگیر_شمار = 0;

        SDL_free(wind);
    }
    پنجره->داخلی = عدم;
}

#پایان_اگر // SDL_VIDEO_DRIVER_WAYLAND
